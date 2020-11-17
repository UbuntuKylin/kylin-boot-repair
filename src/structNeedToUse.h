/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef STRUCTNEEDTOUSE_H
#define STRUCTNEEDTOUSE_H

#include <QObject>

typedef struct linuxSystemInfo
{
    QString deviceName      = "";
    QString rootPath        = "";
    QString bootPath        = "";
    QString efiPath         = "";
    QString homePath        = "";

    bool    isUEFIBoot      = false;
    bool    isLegacyBoot    = false;
    bool    bootIsSeparate  = false;
    bool    homeIsSeparate  = false;

    QString treeMkdirCmd    = "sudo -S mkdir /media/kylin/ /media/kylin/dev";
    QString rootMkdirCmd    = "sudo -S mkdir /media/kylin";
    QString rootMountCmd    = "sudo -S mount ";
    QString bootMountCmd    = "sudo -S mount ";
    QString efiMountCmd     = "sudo -S mount ";
    QString homeMountCmd    = "sudo -S mount ";

    QString chrootCmd       = "sudo -S chroot /media/kylin";
    QString grubInstallCmd  = "sudo -S grub-install --target=";
    bool    needGrubInstall = false;
    QString grubMkconfigCmd = "sudo -S grub-mkconfig -o /boot/grub/grub.cfg";
    QString updateGrubCmd   = "sudo -S update-grub";

    QString devMountCmd     = "sudo -S mount --bind /dev /media/kylin";
    QString procMountCmd    = "sudo -S mount --bind /proc /media/kylin";
    QString sysMountCmd     = "sudo -S mount --bind /sys /media/kylin";

    QString umountAllCmd    = "sudo -S umount -l ";

    QString archDetectCmd   = "archdetect";
}linuxSystemInfo;

#endif // STRUCTNEEDTOUSE_H
