/************************************************
* 文件描述: grub修复前命令拼接线程。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "pre_repair.h"

/************************************************
* 函数名称：PreRepair
* 功能描述：构造函数
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
PreRepair::PreRepair(const bool& hasPwd,const QString& userPwd, QObject *parent)
    : QObject(parent), hasPassWord(hasPwd), userPassWord(userPwd)
{
    currentBootRepair = nullptr;
}

/************************************************
* 函数名称：~PreRepair
* 功能描述：析构函数
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
PreRepair::~PreRepair()
{
    currentDevice->deleteLater();
    currentBootRepair->deleteLater();
}

/************************************************
* 函数名称：start_pushButton_clicked
* 功能描述：开始修复按钮按下后的实际执行函数
* 输入参数：QStringList list, uint num
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void PreRepair::start_pushButton_clicked(const QStringList& list, const uint& num)
{
    qDebug() << "start_pushButton_clicked";
    hardDisklist = list;
    hardDiskNum  = num;
    for(QString &s:hardDisklist)
    {
        qDebug() << "当前分区名：" << s;
        qDebug() << "创建新的名为 " << s << " 的partionDevice类";
        currentDevice = new PartionDevice(hasPassWord,userPassWord,s);
        if(nullptr == currentDevice)
        {
            qDebug() << "PartionDevice对象创建失败！";
            emit failAndReturn();
            return;
        }
        connect(currentDevice,&PartionDevice::failAndReturn,this,&PreRepair::failAndReturn);
        currentDevice->readFstabInfo();                         //读取fstab文件中linux分区信息
        if(currentDevice->isRootPartion)                        //只有是根目录的时候才进行处理
        {
            systemNumOnDisk++;                                  //计算安装的linux系统数量

            qDebug() << "主线程中： 当前分区为root分区";


            linuxSystemInfo currentSystem;                      //创建字符串结构体

            currentSystem.deviceName = currentDevice->DeviceName;
            qDebug() << "root分区分区名 ：" << currentSystem.deviceName;


            currentSystem.rootPath = currentDevice->rootPath;
            qDebug() << "root分区当前装载在 ：" << currentSystem.rootPath;
            currentSystem.umountAllCmd += " ";
            currentSystem.umountAllCmd += currentSystem.rootPath;

            currentSystem.bootIsSeparate = currentDevice->bootIsSeparate;
            if (currentSystem.bootIsSeparate)
            {
                qDebug() << "boot分区单独分区了！";
                currentSystem.bootPath = currentDevice->selfBootDeviceName;
                qDebug() << "boot分区当前装载在 ：" << currentSystem.bootPath;
                currentSystem.umountAllCmd += " ";
                currentSystem.umountAllCmd += currentSystem.bootPath;
            }
            else
            {
                qDebug() << "boot分区没有单独分区！";
            }

            currentSystem.rootPath = currentDevice->rootPath;
            qDebug() << "root分区当前装载在 ：" << currentSystem.rootPath;

            currentSystem.homeIsSeparate = currentDevice->homeIsSeparate;
            if (currentSystem.homeIsSeparate)
            {
                qDebug() << "home分区单独分区了！";
                currentSystem.homePath = currentDevice->selfHomeDeviceName;
                qDebug() << "boot分区当前装载在 ：" << currentSystem.homePath;
            }
            else
            {
                qDebug() << "boot分区没有单独分区！";
            }

            currentSystem.efiPath = currentDevice->selfEfiDeviceName;

            qDebug() << "efi分区当前装载在 ：" << currentSystem.efiPath;
            currentSystem.umountAllCmd += " ";
            currentSystem.umountAllCmd += currentSystem.efiPath;

            currentSystem.umountAllCmd += " ";
            currentSystem.umountAllCmd += currentSystem.rootPath;
            currentSystem.umountAllCmd += "/proc";

            currentSystem.umountAllCmd += " ";
            currentSystem.umountAllCmd += currentSystem.rootPath;
            currentSystem.umountAllCmd += "/sys";

            currentSystem.umountAllCmd += " ";
            currentSystem.umountAllCmd += currentSystem.rootPath;
            currentSystem.umountAllCmd += "/dev";

            //legacy与uefi启动方式不同，legacy无efi分区，修复时亦无需grub-install
            currentSystem.isUEFIBoot = currentDevice->isUEFIBoot;
            if(true == currentSystem.isUEFIBoot)
            {
                qDebug() << "当前系统是uefi启动";
            }
            else
            {
                qDebug() << "当前系统非uefi启动";
            }


            currentSystem.efiMountCmd += currentSystem.efiPath;
            currentSystem.efiMountCmd += " /tmp/kylin";
            currentSystem.efiMountCmd += currentDevice->DeviceName;
            currentSystem.efiMountCmd += "/boot/efi";

            currentSystem.rootMkdirCmd += currentDevice->DeviceName;
            qDebug() << "创建root目录的命令是 ：" << currentSystem.rootMkdirCmd;

            QString rootMountCmdTemp = currentDevice->DeviceName;
            currentSystem.rootMountCmd += rootMountCmdTemp;
            currentSystem.rootMountCmd += " /tmp/kylin";
            currentSystem.rootMountCmd += rootMountCmdTemp;

            qDebug() << "挂载root目录的命令是 ：" << currentSystem.rootMountCmd;

            if (currentSystem.bootIsSeparate)
            {
                qDebug() << "挂载boot目录" ;
                currentSystem.bootMountCmd += currentDevice->bootPath;
                currentSystem.bootMountCmd += " /tmp/kylin";
                currentSystem.bootMountCmd += rootMountCmdTemp;
                currentSystem.bootMountCmd += "/boot";

                qDebug() << "挂载boot目录的命令是 ：" << currentSystem.bootMountCmd;
            }

            if (currentSystem.homeIsSeparate)
            {
                qDebug() << "挂载home目录" ;
                currentSystem.homeMountCmd += currentDevice->homePath;
                currentSystem.homeMountCmd += " /tmp/kylin";
                currentSystem.homeMountCmd += rootMountCmdTemp;
                currentSystem.homeMountCmd += "/home";

                qDebug() << "挂载home目录的命令是 ：" << currentSystem.homeMountCmd;
            }

            currentSystem.devMountCmd += currentDevice->DeviceName;
            currentSystem.devMountCmd += "/dev";

            currentSystem.procMountCmd += currentDevice->DeviceName;
            currentSystem.procMountCmd += "/proc";

            currentSystem.sysMountCmd += currentDevice->DeviceName;
            currentSystem.sysMountCmd += "/sys";

            currentSystem.chrootCmd += currentDevice->DeviceName;

            currentSystem.needGrubInstall = currentDevice->needGrubInstall;

            if(currentSystem.needGrubInstall && !(currentDevice->systemClassEfi.isEmpty()))
            {
                currentSystem.grubInstallCmd += currentDevice->systemClassEfi;

//                currentSystem.grubInstallCmd += " --boot-directory=/boot";

//                currentSystem.grubInstallCmd += " --efi-directory=/boot/efi";

                currentSystem.grubInstallCmd += " --recheck";
//                currentSystem.grubInstallCmd += " --kylin-no-efi-register";
                qDebug() << "grubInstallCmd命令为：" << currentSystem.grubInstallCmd;
            }
            else
            {
                //uefi引导，但aarch架构，无需grub-install

                currentSystem.needGrubInstall = false;
                currentSystem.grubInstallCmd.clear();

            }

            readyToRepairList.append(currentSystem);              //将当前处理的根目录所属的系统信息添加至string list
        }
        else if(currentDevice->isBootPartion)
        {
            qDebug() << "主线程中： 当前分区为boot分区，无操作";
        }
        else if(currentDevice->isEfiParion)
        {
            qDebug() << "主线程中： 当前分区为efi分区，无操作";
        }

    }

    qDebug() << "主线程中： 所有分区遍历完毕共有" << systemNumOnDisk << "个系统安装在该硬盘";
    if(0 == systemNumOnDisk)
    {
        qDebug() << "硬盘中没有系统，无法修复！";
        emit failAndReturn();
        return;
    }
    //grub支持多系统直接修复，共有一个grub文件
    else if(1 == systemNumOnDisk)
    {
        qDebug() << "硬盘中只有一个系统！";
        currentBootRepair = new BootRepair(hasPassWord,userPassWord,readyToRepairList.at(0));
        if(nullptr == currentBootRepair)
        {
            qDebug() << "BootRepair对象创建失败！";
            emit failAndReturn();
            return;
        }
        connect(currentBootRepair,&BootRepair::repairResult,this,&PreRepair::getRepairResult);
        currentBootRepair->repairGrubFile();           //grub引导文件修复
    }
    else
    {
        qDebug() << "安装了多个系统，为防止有安装V10.1系统，需遍历修复，直至修复了V10.1系统";
        for(uint i = 0 ; i < systemNumOnDisk; i++)      //遍历string list中的系统，若多系统，则分别挂载修复
        {
            qDebug() << "修复表单中第" << i + 1 << "个系统中。";
            currentBootRepair = new BootRepair(hasPassWord,userPassWord,readyToRepairList.at(i));
            if(nullptr == currentBootRepair)
            {
                qDebug() << "BootRepair对象创建失败！";
                emit failAndReturn();
                return;
            }
            connect(currentBootRepair,&BootRepair::repairResult,this,&PreRepair::getRepairResult);
            currentBootRepair->repairGrubFile();           //grub引导文件修复

            if(currentBootRepair->isV101 && currentBootRepair->currentSystem.isUEFIBoot)
            {
                break;
            }
        }
    }


//    currentSystem = new BootRepair(hasPassWord,userPassWord,readyToRepairList.at(1));
//    connect(currentSystem,&BootRepair::repairResult,this,&PreRepair::getRepairResult);
//    currentSystem->repairGrubFile();           //grub引导文件修复

}

void PreRepair::getRepairResult(const bool& res,const bool& v101)
{

    repairSuccess &= res;
    repairTimes++;
    isV101 = v101;
    qDebug() << "修复完成表单中第" << repairTimes << "个系统。";
    if(res)
    {
        qDebug() << "修复成功";
    }
    else
    {
        qDebug() << "修复失败";
    }


    if(systemNumOnDisk == repairTimes || true == isV101)
    {
        if(repairSuccess)
        {
            qDebug() << "修复成功！！！";
            emit changeToFinishPage();                    //发送信号，使主线程翻页
        }
        else
        {
            qDebug() << "boot_repair过程中修复失败！！！";
            emit failAndReturn();
        }
    }

}
