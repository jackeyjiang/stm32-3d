/*======================================================================  
maker  :jiaxing.shen
date   :2014.12.10
email  :55954781@qq.com
======================================================================*/
#include "m_include.h"
#include "sdReader.h"
//
//===================================================
// 初始化sd
//===================================================
void c_sdReader::init(void) {
        close();
        cardErrCode = finit(NULL);
        (cardErrCode) ? (cardOk = false) : (cardOk = true);
}
//
//===================================================
// 初始化sd
//===================================================
void c_sdReader::getStatus() {
    if (cardOk) {
        serialCommu.print("SD printing byte ");
        serialCommu.print(sdPos);
        serialCommu.print("/");
        serialCommu.println(info.size);
    } else {
        serialCommu.println("Not SD printing");
    }
}
//
//===================================================
// sd 打印完成度
//===================================================
uint8 c_sdReader::getPercentDone() {
    if (pFile == NULL || !cardOk || !printing) 
        return 0;
    return sdPos/((info.size+99)/100);
}
//
//===================================================
// 开启打印
//===================================================
void c_sdReader::setStartPrint(bool status) {
    if (cardOk) {
        printing = status;
    }
}
//
//===================================================
// sd 打印
//===================================================
void c_sdReader::sdPrint(void) {
    int8 d, cout=0, comment=false, upZ = false;
    static  float   savePos[MAX_AXIS];
    
    if (pFile == NULL || !cardOk || !printing) 
        return;
    
    sdPos = 0;
    while (1) {
        if (pFile==NULL || !cardOk){
            break;
        } else if (feof(pFile)) {
            close();
            break;
        } else if (!printing) {
            if (upZ == false) {
                stepMoto.waitFinish();
                savePos[X_AXIS]  = gcode.getCurPos(X_AXIS);
                savePos[Y_AXIS]  = gcode.getCurPos(Y_AXIS);
                savePos[Z_AXIS]  = gcode.getCurPos(Z_AXIS);
                savePos[E1_AXIS] = gcode.getCurPos(E1_AXIS);
                gcode.moveRelative(0, 0, 15, 0, para.motion.maxSpeed[X_AXIS]/2);
                upZ = true;
            }
            os_dly_wait(10);
            continue;
        } else if (upZ == true) {
            stepMoto.waitFinish();
            gcode.setCurPos(savePos[X_AXIS], savePos[Y_AXIS], savePos[Z_AXIS], savePos[E1_AXIS]);
            upZ = false;
        }
        
        d = fgetc(pFile);
        sdPos ++;
//
//=========================================   
//== 文件读取错误||停止打印|| #停止符
        if ((d == -1) || (d=='#' && comment==false)) {
            cout=0; comment=false;
            break;
        }
//
//=========================================
//== 字符过长异常
        if (cout >= (COMMU_BUFFER_SIZE-1)) {
            cout=0; comment=false;
            break;
        }
//
//=========================================
//== 换行
        if (d=='\r' || d=='\n' || (d==':' && comment==false)) {
            getBuf[cout] = 0;
            if (cout) {
                if (commu.parseAscii((char *)getBuf, pSdBuf,  false)) {
                    pSdBuf = commu.checkAndPushCommand(pSdBuf);
                }
            }
            cout = comment = 0;
            continue;
        }
//
//=========================================
//== 注释符
        if (d == ';')   {
            comment=true;
            continue;
        }
        if (!comment) {
            getBuf[cout++] = d;
        }
    }
    serialCommu.println("Done printing file");
    close();
}
//
//===================================================
// 初始化sd
//===================================================
void c_sdReader::uinit(void) {
    if (cardOk) {
        close();    // 关闭文件
        cardErrCode = funinit(NULL);
        cardOk = false;
    }
}
//
//===================================================
// 删除文件
//===================================================
void c_sdReader::removeFile(char *fn) {
    if (cardOk ) {
        if (fdelete(fn) == 0) {
            serialCommu.print  ("File deleted: ");
            serialCommu.println(fn);
        } else {
            serialCommu.print  ("Deletion failed, File: ");
            serialCommu.print  (fn);
            serialCommu.println(".");
        }
    }
    saving = false;
}
//
//===================================================
// 写文件
//===================================================
void c_sdReader::writeCmdEnd() {
    if (cardOk && pFile) {
        fclose(pFile);
        serialCommu.println("Done saving file.");
    }
    saving = false;
}
//
//===================================================
// 写文件
//===================================================
void c_sdReader::writeCmd(char *buf) {
    char *begin = buf;
    char *npos  = 0;
    char *end   = buf + strlen(buf) - 1;
    char len;
    
    if ((npos = strchr(buf, 'N')) != NULL) {
        begin = strchr(npos, ' ') + 1;
        end   = strchr(npos, '*') - 1;
    }
    end[1] = '\r';  end[2] = '\n';  end[3] = '\0';
    len = end-begin+3;
    if (cardOk && pFile) {
        if (fwrite ((const void *)begin, 1, len, pFile) != len) {
            serialCommu.println("error writing to file");
        }
    } else {
        serialCommu.println("Card err");
    }
}
//
//===================================================
// 写文件
//===================================================
void c_sdReader::write(const char *fn) {
    if (cardOk) {
        if (pFile) {
            fclose(pFile);
        }
        pFile = fopen(fn, "w");
        if (pFile) {
            serialCommu.print("Writing to file: ");
            serialCommu.println(fn);
            saving = true;
        } else {
            serialCommu.print("open failed, File: ");
            serialCommu.print(fn);
            serialCommu.println(".");
        }
    } else {
        serialCommu.println("Card err");
    }
}
//
//===================================================
// 关闭文件
//===================================================
void c_sdReader::close() {
    if (cardOk) {
        if (pFile) {
            if (printing == true) {
                gcode.delectWait();
                stepMoto.waitFinish();
                lcd.function_cooldown();
                printing = false;
                if (lcd.laserModle == false) {
                    gcode.moveRelative(0, 0, 15, 0, para.motion.maxSpeed[X_AXIS]/2);
                }
            }
            fclose(pFile);
            pFile = NULL;
        }
    } 
}
//
//===================================================
// 打开文件
// mode = "r", "w", "a", "b"
//===================================================
void c_sdReader::open(const char *fn, const char *mode) {
    if (cardOk) {
        if (pFile) {
            fclose(pFile);
        }
        pFile = fopen(fn, mode);
        if (pFile) {
            serialCommu.print("File opened: ");
            serialCommu.print(fn);
            serialCommu.print(" Size: ");
            info.fileID = 0;
            ffind(fn, &info);
            serialCommu.println(info.size);
        } else {
            serialCommu.print("open failed, File: ");
            serialCommu.print(fn);
            serialCommu.println(".");
        }
    } else {
        serialCommu.println("Card err");
    }
}
//
//===================================================
// 列出文件目录
//===================================================
void c_sdReader::ls(void) {
    if (!cardOk) 
        return;
    info.fileID = 0;
    while(ffind("*.*",&info)==0) {
        serialCommu.println((const char *)info.name);
    }
}
//
//===================================================
// 检测自动运行文件
//===================================================
void c_sdReader::checkAutoStart(bool force) {
    
}
//
//===================================================
__task void sdReaderTask(void) {
    sdReader.taskRunEnable = true;
    while (taskRunEnable() == false) os_dly_wait(1);
    sdReader.pSdBuf = commu.getMbxBuf();
    while (1) {
        sdReader.sdPrint();
        os_dly_wait(10);
    }
}
//
//===================================================
c_sdReader  sdReader;






