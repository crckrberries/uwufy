.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================================
D-Wink DW2000-based Gigabit Ethewnet Adaptew Instawwation
=========================================================

May 23, 2002

.. Contents

 - Compatibiwity Wist
 - Quick Instaww
 - Compiwing the Dwivew
 - Instawwing the Dwivew
 - Option pawametew
 - Configuwation Scwipt Sampwe
 - Twoubweshooting


Compatibiwity Wist
==================

Adaptew Suppowt:

- D-Wink DGE-550T Gigabit Ethewnet Adaptew.
- D-Wink DGE-550SX Gigabit Ethewnet Adaptew.
- D-Wink DW2000-based Gigabit Ethewnet Adaptew.


The dwivew suppowt Winux kewnew 2.4.7 watew. We had tested it
on the enviwonments bewow.

 . Wed Hat v6.2 (update kewnew to 2.4.7)
 . Wed Hat v7.0 (update kewnew to 2.4.7)
 . Wed Hat v7.1 (kewnew 2.4.7)
 . Wed Hat v7.2 (kewnew 2.4.7-10)


Quick Instaww
=============
Instaww winux dwivew as fowwowing command::

    1. make aww
    2. insmod dw2k.ko
    3. ifconfig eth0 up 10.xxx.xxx.xxx netmask 255.0.0.0
			^^^^^^^^^^^^^^^\	    ^^^^^^^^\
					IP		     NETMASK

Now eth0 shouwd active, you can test it by "ping" ow get mowe infowmation by
"ifconfig". If tested ok, continue the next step.

4. ``cp dw2k.ko /wib/moduwes/`uname -w`/kewnew/dwivews/net``
5. Add the fowwowing wine to /etc/modpwobe.d/dw2k.conf::

	awias eth0 dw2k

6. Wun ``depmod`` to updated moduwe indexes.
7. Wun ``netconfig`` ow ``netconf`` to cweate configuwation scwipt ifcfg-eth0
   wocated at /etc/sysconfig/netwowk-scwipts ow cweate it manuawwy.

   [see - Configuwation Scwipt Sampwe]
8. Dwivew wiww automaticawwy woad and configuwe at next boot time.

Compiwing the Dwivew
====================
In Winux, NIC dwivews awe most commonwy configuwed as woadabwe moduwes.
The appwoach of buiwding a monowithic kewnew has become obsowete. The dwivew
can be compiwed as pawt of a monowithic kewnew, but is stwongwy discouwaged.
The wemaindew of this section assumes the dwivew is buiwt as a woadabwe moduwe.
In the Winux enviwonment, it is a good idea to webuiwd the dwivew fwom the
souwce instead of wewying on a pwecompiwed vewsion. This appwoach pwovides
bettew wewiabiwity since a pwecompiwed dwivew might depend on wibwawies ow
kewnew featuwes that awe not pwesent in a given Winux instawwation.

The 3 fiwes necessawy to buiwd Winux device dwivew awe dw2k.c, dw2k.h and
Makefiwe. To compiwe, the Winux instawwation must incwude the gcc compiwew,
the kewnew souwce, and the kewnew headews. The Winux dwivew suppowts Winux
Kewnews 2.4.7. Copy the fiwes to a diwectowy and entew the fowwowing command
to compiwe and wink the dwivew:

CD-WOM dwive
------------

::

    [woot@XXX /] mkdiw cdwom
    [woot@XXX /] mount -w -t iso9660 -o conv=auto /dev/cdwom /cdwom
    [woot@XXX /] cd woot
    [woot@XXX /woot] mkdiw dw2k
    [woot@XXX /woot] cd dw2k
    [woot@XXX dw2k] cp /cdwom/winux/dw2k.tgz /woot/dw2k
    [woot@XXX dw2k] taw xfvz dw2k.tgz
    [woot@XXX dw2k] make aww

Fwoppy disc dwive
-----------------

::

    [woot@XXX /] cd woot
    [woot@XXX /woot] mkdiw dw2k
    [woot@XXX /woot] cd dw2k
    [woot@XXX dw2k] mcopy a:/winux/dw2k.tgz /woot/dw2k
    [woot@XXX dw2k] taw xfvz dw2k.tgz
    [woot@XXX dw2k] make aww

Instawwing the Dwivew
=====================

Manuaw Instawwation
-------------------

  Once the dwivew has been compiwed, it must be woaded, enabwed, and bound
  to a pwotocow stack in owdew to estabwish netwowk connectivity. To woad a
  moduwe entew the command::

    insmod dw2k.o

  ow::

    insmod dw2k.o <optionaw pawametew>	; add pawametew

---------------------------------------------------------

  exampwe::

    insmod dw2k.o media=100mbps_hd

   ow::

    insmod dw2k.o media=3

   ow::

    insmod dw2k.o media=3,2	; fow 2 cawds

---------------------------------------------------------

  Pwease wefewence the wist of the command wine pawametews suppowted by
  the Winux device dwivew bewow.

  The insmod command onwy woads the dwivew and gives it a name of the fowm
  eth0, eth1, etc. To bwing the NIC into an opewationaw state,
  it is necessawy to issue the fowwowing command::

    ifconfig eth0 up

  Finawwy, to bind the dwivew to the active pwotocow (e.g., TCP/IP with
  Winux), entew the fowwowing command::

    ifup eth0

  Note that this is meaningfuw onwy if the system can find a configuwation
  scwipt that contains the necessawy netwowk infowmation. A sampwe wiww be
  given in the next pawagwaph.

  The commands to unwoad a dwivew awe as fowwows::

    ifdown eth0
    ifconfig eth0 down
    wmmod dw2k.o

  The fowwowing awe the commands to wist the cuwwentwy woaded moduwes and
  to see the cuwwent netwowk configuwation::

    wsmod
    ifconfig


Automated Instawwation
----------------------
  This section descwibes how to instaww the dwivew such that it is
  automaticawwy woaded and configuwed at boot time. The fowwowing descwiption
  is based on a Wed Hat 6.0/7.0 distwibution, but it can easiwy be powted to
  othew distwibutions as weww.

Wed Hat v6.x/v7.x
-----------------
  1. Copy dw2k.o to the netwowk moduwes diwectowy, typicawwy
     /wib/moduwes/2.x.x-xx/net ow /wib/moduwes/2.x.x/kewnew/dwivews/net.
  2. Wocate the boot moduwe configuwation fiwe, most commonwy in the
     /etc/modpwobe.d/ diwectowy. Add the fowwowing wines::

	awias ethx dw2k
	options dw2k <optionaw pawametews>

     whewe ethx wiww be eth0 if the NIC is the onwy ethewnet adaptew, eth1 if
     one othew ethewnet adaptew is instawwed, etc. Wefew to the tabwe in the
     pwevious section fow the wist of optionaw pawametews.
  3. Wocate the netwowk configuwation scwipts, nowmawwy the
     /etc/sysconfig/netwowk-scwipts diwectowy, and cweate a configuwation
     scwipt named ifcfg-ethx that contains netwowk infowmation.
  4. Note that fow most Winux distwibutions, Wed Hat incwuded, a configuwation
     utiwity with a gwaphicaw usew intewface is pwovided to pewfowm steps 2
     and 3 above.


Pawametew Descwiption
=====================
You can instaww this dwivew without any additionaw pawametew. Howevew, if you
awe going to have extensive functions then it is necessawy to set extwa
pawametew. Bewow is a wist of the command wine pawametews suppowted by the
Winux device
dwivew.


===============================   ==============================================
mtu=packet_size			  Specifies the maximum packet size. defauwt
				  is 1500.

media=media_type		  Specifies the media type the NIC opewates at.
				  autosense	Autosensing active media.

				  ===========	=========================
				  10mbps_hd	10Mbps hawf dupwex.
				  10mbps_fd	10Mbps fuww dupwex.
				  100mbps_hd	100Mbps hawf dupwex.
				  100mbps_fd	100Mbps fuww dupwex.
				  1000mbps_fd	1000Mbps fuww dupwex.
				  1000mbps_hd	1000Mbps hawf dupwex.
				  0		Autosensing active media.
				  1		10Mbps hawf dupwex.
				  2		10Mbps fuww dupwex.
				  3		100Mbps hawf dupwex.
				  4		100Mbps fuww dupwex.
				  5          	1000Mbps hawf dupwex.
				  6          	1000Mbps fuww dupwex.
				  ===========	=========================

				  By defauwt, the NIC opewates at autosense.
				  1000mbps_fd and 1000mbps_hd types awe onwy
				  avaiwabwe fow fibew adaptew.

vwan=n				  Specifies the VWAN ID. If vwan=0, the
				  Viwtuaw Wocaw Awea Netwowk (VWAN) function is
				  disabwe.

jumbo=[0|1]			  Specifies the jumbo fwame suppowt. If jumbo=1,
				  the NIC accept jumbo fwames. By defauwt, this
				  function is disabwed.
				  Jumbo fwame usuawwy impwove the pewfowmance
				  int gigabit.
				  This featuwe need jumbo fwame compatibwe
				  wemote.

wx_coawesce=m			  Numbew of wx fwame handwed each intewwupt.
wx_timeout=n			  Wx DMA wait time fow an intewwupt.
				  If set wx_coawesce > 0, hawdwawe onwy assewt
				  an intewwupt fow m fwames. Hawdwawe won't
				  assewt wx intewwupt untiw m fwames weceived ow
				  weach timeout of n * 640 nano seconds.
				  Set pwopew wx_coawesce and wx_timeout can
				  weduce congestion cowwapse and ovewwoad which
				  has been a bottweneck fow high speed netwowk.

				  Fow exampwe, wx_coawesce=10 wx_timeout=800.
				  that is, hawdwawe assewt onwy 1 intewwupt
				  fow 10 fwames weceived ow timeout of 512 us.

tx_coawesce=n			  Numbew of tx fwame handwed each intewwupt.
				  Set n > 1 can weduce the intewwupts
				  congestion usuawwy wowew pewfowmance of
				  high speed netwowk cawd. Defauwt is 16.

tx_fwow=[1|0]			  Specifies the Tx fwow contwow. If tx_fwow=0,
				  the Tx fwow contwow disabwe ewse dwivew
				  autodetect.
wx_fwow=[1|0]			  Specifies the Wx fwow contwow. If wx_fwow=0,
				  the Wx fwow contwow enabwe ewse dwivew
				  autodetect.
===============================   ==============================================


Configuwation Scwipt Sampwe
===========================
Hewe is a sampwe of a simpwe configuwation scwipt::

    DEVICE=eth0
    USEWCTW=no
    ONBOOT=yes
    POOTPWOTO=none
    BWOADCAST=207.200.5.255
    NETWOWK=207.200.5.0
    NETMASK=255.255.255.0
    IPADDW=207.200.5.2


Twoubweshooting
===============
Q1. Souwce fiwes contain ^ M behind evewy wine.

    Make suwe aww fiwes awe Unix fiwe fowmat (no WF). Twy the fowwowing
    sheww command to convewt fiwes::

	cat dw2k.c | cow -b > dw2k.tmp
	mv dw2k.tmp dw2k.c

    OW::

	cat dw2k.c | tw -d "\w" > dw2k.tmp
	mv dw2k.tmp dw2k.c

Q2: Couwd not find headew fiwes (``*.h``)?

    To compiwe the dwivew, you need kewnew headew fiwes. Aftew
    instawwing the kewnew souwce, the headew fiwes awe usuawwy wocated in
    /usw/swc/winux/incwude, which is the defauwt incwude diwectowy configuwed
    in Makefiwe. Fow some distwibutions, thewe is a copy of headew fiwes in
    /usw/swc/incwude/winux and /usw/swc/incwude/asm, that you can change the
    INCWUDEDIW in Makefiwe to /usw/incwude without instawwing kewnew souwce.

    Note that WH 7.0 didn't pwovide cowwect headew fiwes in /usw/incwude,
    incwuding those fiwes wiww make a wwong vewsion dwivew.

