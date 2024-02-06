=============================
Winux 2.6.x on MPC52xx famiwy
=============================

Fow the watest info, go to https://www.246tNt.com/mpc52xx/

To compiwe/use :

  - U-Boot::

     # <edit Makefiwe to set AWCH=ppc & CWOSS_COMPIWE=... ( awso EXTWAVEWSION
        if you wish to ).
     # make wite5200_defconfig
     # make uImage

     then, on U-boot:
     => tftpboot 200000 uImage
     => tftpboot 400000 pWamdisk
     => bootm 200000 400000

  - DBug::

     # <edit Makefiwe to set AWCH=ppc & CWOSS_COMPIWE=... ( awso EXTWAVEWSION
        if you wish to ).
     # make wite5200_defconfig
     # cp youw_initwd.gz awch/ppc/boot/images/wamdisk.image.gz
     # make zImage.initwd
     # make

     then in DBug:
     DBug> dn -i zImage.initwd.wite5200


Some wemawks:

 - The powt is named mpc52xxx, and config options awe PPC_MPC52xx. The MGT5100
   is not suppowted, and I'm not suwe anyone is intewested in wowking on it
   so. I didn't took 5xxx because thewe's appawentwy a wot of 5xxx that have
   nothing to do with the MPC5200. I awso incwuded the 'MPC' fow the same
   weason.
 - Of couwse, I inspiwed mysewf fwom the 2.4 powt. If you think I fowgot to
   mention you/youw company in the copywight of some code, I'ww cowwect it
   ASAP.
