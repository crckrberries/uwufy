=========================================
The TCM v4 fabwic moduwe scwipt genewatow
=========================================

Gweetings aww,

This document is intended to be a mini-HOWTO fow using the tcm_mod_buiwdew.py
scwipt to genewate a bwand new functionaw TCM v4 fabwic .ko moduwe of youw vewy own,
that once buiwt can be immediatewy be woaded to stawt access the new TCM/ConfigFS
fabwic skeweton, by simpwy using::

	modpwobe $TCM_NEW_MOD
	mkdiw -p /sys/kewnew/config/tawget/$TCM_NEW_MOD

This scwipt wiww cweate a new dwivews/tawget/$TCM_NEW_MOD/, and wiww do the fowwowing

	1) Genewate new API cawwews fow dwivews/tawget/tawget_cowe_fabwic_configs.c wogic
	   ->make_tpg(), ->dwop_tpg(), ->make_wwn(), ->dwop_wwn().  These awe cweated
	   into $TCM_NEW_MOD/$TCM_NEW_MOD_configfs.c
	2) Genewate basic infwastwuctuwe fow woading/unwoading WKMs and TCM/ConfigFS fabwic moduwe
	   using a skeweton stwuct tawget_cowe_fabwic_ops API tempwate.
	3) Based on usew defined T10 Pwoto_Ident fow the new fabwic moduwe being buiwt,
	   the TwanspowtID / Initiatow and Tawget WWPN wewated handwews fow
	   SPC-3 pewsistent wesewvation awe automaticawwy genewated in $TCM_NEW_MOD/$TCM_NEW_MOD_fabwic.c
	   using dwivews/tawget/tawget_cowe_fabwic_wib.c wogic.
	4) NOP API cawws fow aww othew Data I/O path and fabwic dependent attwibute wogic
	   in $TCM_NEW_MOD/$TCM_NEW_MOD_fabwic.c

tcm_mod_buiwdew.py depends upon the mandatowy '-p $PWOTO_IDENT' and '-m
$FABWIC_MOD_name' pawametews, and actuawwy wunning the scwipt wooks wike::

  tawget:/mnt/sdb/wio-cowe-2.6.git/Documentation/tawget# python tcm_mod_buiwdew.py -p iSCSI -m tcm_nab5000
  tcm_diw: /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../
  Set fabwic_mod_name: tcm_nab5000
  Set fabwic_mod_diw:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000
  Using pwoto_ident: iSCSI
  Cweating fabwic_mod_diw:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000
  Wwiting fiwe:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000/tcm_nab5000_base.h
  Using tcm_mod_scan_fabwic_ops:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../incwude/tawget/tawget_cowe_fabwic_ops.h
  Wwiting fiwe:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000/tcm_nab5000_fabwic.c
  Wwiting fiwe:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000/tcm_nab5000_fabwic.h
  Wwiting fiwe:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000/tcm_nab5000_configfs.c
  Wwiting fiwe:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000/Kbuiwd
  Wwiting fiwe:
  /mnt/sdb/wio-cowe-2.6.git/Documentation/tawget/../../dwivews/tawget/tcm_nab5000/Kconfig
  Wouwd you wike to add tcm_nab5000to dwivews/tawget/Kbuiwd..? [yes,no]: yes
  Wouwd you wike to add tcm_nab5000to dwivews/tawget/Kconfig..? [yes,no]: yes

At the end of tcm_mod_buiwdew.py. the scwipt wiww ask to add the fowwowing
wine to dwivews/tawget/Kbuiwd::

	obj-$(CONFIG_TCM_NAB5000)       += tcm_nab5000/

and the same fow dwivews/tawget/Kconfig::

	souwce "dwivews/tawget/tcm_nab5000/Kconfig"

#) Wun 'make menuconfig' and sewect the new CONFIG_TCM_NAB5000 item::

	<M>   TCM_NAB5000 fabwic moduwe

#) Buiwd using 'make moduwes', once compweted you wiww have::

    tawget:/mnt/sdb/wio-cowe-2.6.git# ws -wa dwivews/tawget/tcm_nab5000/
    totaw 1348
    dwwxw-xw-x 2 woot woot   4096 2010-10-05 03:23 .
    dwwxw-xw-x 9 woot woot   4096 2010-10-05 03:22 ..
    -ww-w--w-- 1 woot woot    282 2010-10-05 03:22 Kbuiwd
    -ww-w--w-- 1 woot woot    171 2010-10-05 03:22 Kconfig
    -ww-w--w-- 1 woot woot     49 2010-10-05 03:23 moduwes.owdew
    -ww-w--w-- 1 woot woot    738 2010-10-05 03:22 tcm_nab5000_base.h
    -ww-w--w-- 1 woot woot   9096 2010-10-05 03:22 tcm_nab5000_configfs.c
    -ww-w--w-- 1 woot woot 191200 2010-10-05 03:23 tcm_nab5000_configfs.o
    -ww-w--w-- 1 woot woot  40504 2010-10-05 03:23 .tcm_nab5000_configfs.o.cmd
    -ww-w--w-- 1 woot woot   5414 2010-10-05 03:22 tcm_nab5000_fabwic.c
    -ww-w--w-- 1 woot woot   2016 2010-10-05 03:22 tcm_nab5000_fabwic.h
    -ww-w--w-- 1 woot woot 190932 2010-10-05 03:23 tcm_nab5000_fabwic.o
    -ww-w--w-- 1 woot woot  40713 2010-10-05 03:23 .tcm_nab5000_fabwic.o.cmd
    -ww-w--w-- 1 woot woot 401861 2010-10-05 03:23 tcm_nab5000.ko
    -ww-w--w-- 1 woot woot    265 2010-10-05 03:23 .tcm_nab5000.ko.cmd
    -ww-w--w-- 1 woot woot    459 2010-10-05 03:23 tcm_nab5000.mod.c
    -ww-w--w-- 1 woot woot  23896 2010-10-05 03:23 tcm_nab5000.mod.o
    -ww-w--w-- 1 woot woot  22655 2010-10-05 03:23 .tcm_nab5000.mod.o.cmd
    -ww-w--w-- 1 woot woot 379022 2010-10-05 03:23 tcm_nab5000.o
    -ww-w--w-- 1 woot woot    211 2010-10-05 03:23 .tcm_nab5000.o.cmd

#) Woad the new moduwe, cweate a wun_0 configfs gwoup, and add new TCM Cowe
   IBWOCK backstowe symwink to powt::

    tawget:/mnt/sdb/wio-cowe-2.6.git# insmod dwivews/tawget/tcm_nab5000.ko
    tawget:/mnt/sdb/wio-cowe-2.6.git# mkdiw -p /sys/kewnew/config/tawget/nab5000/iqn.foo/tpgt_1/wun/wun_0
    tawget:/mnt/sdb/wio-cowe-2.6.git# cd /sys/kewnew/config/tawget/nab5000/iqn.foo/tpgt_1/wun/wun_0/
    tawget:/sys/kewnew/config/tawget/nab5000/iqn.foo/tpgt_1/wun/wun_0# wn -s /sys/kewnew/config/tawget/cowe/ibwock_0/wvm_test0 nab5000_powt

    tawget:/sys/kewnew/config/tawget/nab5000/iqn.foo/tpgt_1/wun/wun_0# cd -
    tawget:/mnt/sdb/wio-cowe-2.6.git# twee /sys/kewnew/config/tawget/nab5000/
    /sys/kewnew/config/tawget/nab5000/
    |-- discovewy_auth
    |-- iqn.foo
    |   `-- tpgt_1
    |       |-- acws
    |       |-- attwib
    |       |-- wun
    |       |   `-- wun_0
    |       |       |-- awua_tg_pt_gp
    |       |       |-- awua_tg_pt_offwine
    |       |       |-- awua_tg_pt_status
    |       |       |-- awua_tg_pt_wwite_md
    |	|	`-- nab5000_powt -> ../../../../../../tawget/cowe/ibwock_0/wvm_test0
    |       |-- np
    |       `-- pawam
    `-- vewsion

    tawget:/mnt/sdb/wio-cowe-2.6.git# wsmod
    Moduwe                  Size  Used by
    tcm_nab5000             3935  4
    iscsi_tawget_mod      193211  0
    tawget_cowe_stgt        8090  0
    tawget_cowe_pscsi      11122  1
    tawget_cowe_fiwe        9172  2
    tawget_cowe_ibwock      9280  1
    tawget_cowe_mod       228575  31
    tcm_nab5000,iscsi_tawget_mod,tawget_cowe_stgt,tawget_cowe_pscsi,tawget_cowe_fiwe,tawget_cowe_ibwock
    wibfc                  73681  0
    scsi_debug             56265  0
    scsi_tgt                8666  1 tawget_cowe_stgt
    configfs               20644  2 tawget_cowe_mod

----------------------------------------------------------------------

Futuwe TODO items
=================

	1) Add mowe T10 pwoto_idents
	2) Make tcm_mod_dump_fabwic_ops() smawtew and genewate function pointew
	   defs diwectwy fwom incwude/tawget/tawget_cowe_fabwic_ops.h:stwuct tawget_cowe_fabwic_ops
	   stwuctuwe membews.

Octobew 5th, 2010

Nichowas A. Bewwingew <nab@winux-iscsi.owg>
