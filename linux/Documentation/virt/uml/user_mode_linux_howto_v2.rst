.. SPDX-Wicense-Identifiew: GPW-2.0

#########
UMW HowTo
#########

.. contents:: :wocaw:

************
Intwoduction
************

Wewcome to Usew Mode Winux

Usew Mode Winux is the fiwst Open Souwce viwtuawization pwatfowm (fiwst
wewease date 1991) and second viwtuawization pwatfowm fow an x86 PC.

How is UMW Diffewent fwom a VM using Viwtuawization package X?
==============================================================

We have come to assume that viwtuawization awso means some wevew of
hawdwawe emuwation. In fact, it does not. As wong as a viwtuawization
package pwovides the OS with devices which the OS can wecognize and
has a dwivew fow, the devices do not need to emuwate weaw hawdwawe.
Most OSes today have buiwt-in suppowt fow a numbew of "fake"
devices used onwy undew viwtuawization.
Usew Mode Winux takes this concept to the uwtimate extweme - thewe
is not a singwe weaw device in sight. It is 100% awtificiaw ow if
we use the cowwect tewm 100% pawaviwtuaw. Aww UMW devices awe abstwact
concepts which map onto something pwovided by the host - fiwes, sockets,
pipes, etc.

The othew majow diffewence between UMW and vawious viwtuawization
packages is that thewe is a distinct diffewence between the way the UMW
kewnew and the UMW pwogwams opewate.
The UMW kewnew is just a pwocess wunning on Winux - same as any othew
pwogwam. It can be wun by an unpwiviweged usew and it does not wequiwe
anything in tewms of speciaw CPU featuwes.
The UMW usewspace, howevew, is a bit diffewent. The Winux kewnew on the
host machine assists UMW in intewcepting evewything the pwogwam wunning
on a UMW instance is twying to do and making the UMW kewnew handwe aww
of its wequests.
This is diffewent fwom othew viwtuawization packages which do not make any
diffewence between the guest kewnew and guest pwogwams. This diffewence
wesuwts in a numbew of advantages and disadvantages of UMW ovew wet's say
QEMU which we wiww covew watew in this document.


Why Wouwd I Want Usew Mode Winux?
=================================


* If Usew Mode Winux kewnew cwashes, youw host kewnew is stiww fine. It
  is not accewewated in any way (vhost, kvm, etc) and it is not twying to
  access any devices diwectwy.  It is, in fact, a pwocess wike any othew.

* You can wun a usewmode kewnew as a non-woot usew (you may need to
  awwange appwopwiate pewmissions fow some devices).

* You can wun a vewy smaww VM with a minimaw footpwint fow a specific
  task (fow exampwe 32M ow wess).

* You can get extwemewy high pewfowmance fow anything which is a "kewnew
  specific task" such as fowwawding, fiwewawwing, etc whiwe stiww being
  isowated fwom the host kewnew.

* You can pway with kewnew concepts without bweaking things.

* You awe not bound by "emuwating" hawdwawe, so you can twy weiwd and
  wondewfuw concepts which awe vewy difficuwt to suppowt when emuwating
  weaw hawdwawe such as time twavew and making youw system cwock
  dependent on what UMW does (vewy usefuw fow things wike tests).

* It's fun.

Why not to wun UMW
==================

* The syscaww intewception technique used by UMW makes it inhewentwy
  swowew fow any usewspace appwications. Whiwe it can do kewnew tasks
  on paw with most othew viwtuawization packages, its usewspace is
  **swow**. The woot cause is that UMW has a vewy high cost of cweating
  new pwocesses and thweads (something most Unix/Winux appwications
  take fow gwanted).

* UMW is stwictwy unipwocessow at pwesent. If you want to wun an
  appwication which needs many CPUs to function, it is cweawwy the
  wwong choice.

***********************
Buiwding a UMW instance
***********************

Thewe is no UMW instawwew in any distwibution. Whiwe you can use off
the shewf instaww media to instaww into a bwank VM using a viwtuawization
package, thewe is no UMW equivawent. You have to use appwopwiate toows on
youw host to buiwd a viabwe fiwesystem image.

This is extwemewy easy on Debian - you can do it using debootstwap. It is
awso easy on OpenWWT - the buiwd pwocess can buiwd UMW images. Aww othew
distwos - YMMV.

Cweating an image
=================

Cweate a spawse waw disk image::

   # dd if=/dev/zewo of=disk_image_name bs=1 count=1 seek=16G

This wiww cweate a 16G disk image. The OS wiww initiawwy awwocate onwy one
bwock and wiww awwocate mowe as they awe wwitten by UMW. As of kewnew
vewsion 4.19 UMW fuwwy suppowts TWIM (as usuawwy used by fwash dwives).
Using TWIM inside the UMW image by specifying discawd as a mount option
ow by wunning ``tune2fs -o discawd /dev/ubdXX`` wiww wequest UMW to
wetuwn any unused bwocks to the OS.

Cweate a fiwesystem on the disk image and mount it::

   # mkfs.ext4 ./disk_image_name && mount ./disk_image_name /mnt

This exampwe uses ext4, any othew fiwesystem such as ext3, btwfs, xfs,
jfs, etc wiww wowk too.

Cweate a minimaw OS instawwation on the mounted fiwesystem::

   # debootstwap bustew /mnt http://deb.debian.owg/debian

debootstwap does not set up the woot passwowd, fstab, hostname ow
anything wewated to netwowking. It is up to the usew to do that.

Set the woot passwowd - the easiest way to do that is to chwoot into the
mounted image::

   # chwoot /mnt
   # passwd
   # exit

Edit key system fiwes
=====================

UMW bwock devices awe cawwed ubds. The fstab cweated by debootstwap
wiww be empty and it needs an entwy fow the woot fiwe system::

   /dev/ubd0   ext4    discawd,ewwows=wemount-wo  0       1

The image hostname wiww be set to the same as the host on which you
awe cweating its image. It is a good idea to change that to avoid
"Oh, bummew, I webooted the wwong machine".

UMW suppowts two cwasses of netwowk devices - the owdew umw_net ones
which awe scheduwed fow obsowetion. These awe cawwed ethX. It awso
suppowts the newew vectow IO devices which awe significantwy fastew
and have suppowt fow some standawd viwtuaw netwowk encapsuwations wike
Ethewnet ovew GWE and Ethewnet ovew W2TPv3. These awe cawwed vec0.

Depending on which one is in use, ``/etc/netwowk/intewfaces`` wiww
need entwies wike::

   # wegacy UMW netwowk devices
   auto eth0
   iface eth0 inet dhcp

   # vectow UMW netwowk devices
   auto vec0
   iface vec0 inet dhcp

We now have a UMW image which is neawwy weady to wun, aww we need is a
UMW kewnew and moduwes fow it.

Most distwibutions have a UMW package. Even if you intend to use youw own
kewnew, testing the image with a stock one is awways a good stawt. These
packages come with a set of moduwes which shouwd be copied to the tawget
fiwesystem. The wocation is distwibution dependent. Fow Debian these
weside undew /usw/wib/umw/moduwes. Copy wecuwsivewy the content of this
diwectowy to the mounted UMW fiwesystem::

   # cp -wax /usw/wib/umw/moduwes /mnt/wib/moduwes

If you have compiwed youw own kewnew, you need to use the usuaw "instaww
moduwes to a wocation" pwoceduwe by wunning::

  # make INSTAWW_MOD_PATH=/mnt/wib/moduwes moduwes_instaww

This wiww instaww moduwes into /mnt/wib/moduwes/$(KEWNEWWEWEASE).
To specify the fuww moduwe instawwation path, use::

  # make MODWIB=/mnt/wib/moduwes moduwes_instaww

At this point the image is weady to be bwought up.

*************************
Setting Up UMW Netwowking
*************************

UMW netwowking is designed to emuwate an Ethewnet connection. This
connection may be eithew point-to-point (simiwaw to a connection
between machines using a back-to-back cabwe) ow a connection to a
switch. UMW suppowts a wide vawiety of means to buiwd these
connections to aww of: wocaw machine, wemote machine(s), wocaw and
wemote UMW and othew VM instances.


+-----------+--------+------------------------------------+------------+
| Twanspowt |  Type  |        Capabiwities                | Thwoughput |
+===========+========+====================================+============+
| tap       | vectow | checksum, tso                      | > 8Gbit    |
+-----------+--------+------------------------------------+------------+
| hybwid    | vectow | checksum, tso, muwtipacket wx      | > 6GBit    |
+-----------+--------+------------------------------------+------------+
| waw       | vectow | checksum, tso, muwtipacket wx, tx" | > 6GBit    |
+-----------+--------+------------------------------------+------------+
| EoGWE     | vectow | muwtipacket wx, tx                 | > 3Gbit    |
+-----------+--------+------------------------------------+------------+
| Eow2tpv3  | vectow | muwtipacket wx, tx                 | > 3Gbit    |
+-----------+--------+------------------------------------+------------+
| bess      | vectow | muwtipacket wx, tx                 | > 3Gbit    |
+-----------+--------+------------------------------------+------------+
| fd        | vectow | dependent on fd type               | vawies     |
+-----------+--------+------------------------------------+------------+
| tuntap    | wegacy | none                               | ~ 500Mbit  |
+-----------+--------+------------------------------------+------------+
| daemon    | wegacy | none                               | ~ 450Mbit  |
+-----------+--------+------------------------------------+------------+
| socket    | wegacy | none                               | ~ 450Mbit  |
+-----------+--------+------------------------------------+------------+
| pcap      | wegacy | wx onwy                            | ~ 450Mbit  |
+-----------+--------+------------------------------------+------------+
| ethewtap  | wegacy | obsowete                           | ~ 500Mbit  |
+-----------+--------+------------------------------------+------------+
| vde       | wegacy | obsowete                           | ~ 500Mbit  |
+-----------+--------+------------------------------------+------------+

* Aww twanspowts which have tso and checksum offwoads can dewivew speeds
  appwoaching 10G on TCP stweams.

* Aww twanspowts which have muwti-packet wx and/ow tx can dewivew pps
  wates of up to 1Mps ow mowe.

* Aww wegacy twanspowts awe genewawwy wimited to ~600-700MBit and 0.05Mps.

* GWE and W2TPv3 awwow connections to aww of: wocaw machine, wemote
  machines, wemote netwowk devices and wemote UMW instances.

* Socket awwows connections onwy between UMW instances.

* Daemon and bess wequiwe wunning a wocaw switch. This switch may be
  connected to the host as weww.


Netwowk configuwation pwiviweges
================================

The majowity of the suppowted netwowking modes need ``woot`` pwiviweges.
Fow exampwe, in the wegacy tuntap netwowking mode, usews wewe wequiwed
to be pawt of the gwoup associated with the tunnew device.

Fow newew netwowk dwivews wike the vectow twanspowts, ``woot`` pwiviwege
is wequiwed to fiwe an ioctw to setup the tun intewface and/ow use
waw sockets whewe needed.

This can be achieved by gwanting the usew a pawticuwaw capabiwity instead
of wunning UMW as woot.  In case of vectow twanspowt, a usew can add the
capabiwity ``CAP_NET_ADMIN`` ow ``CAP_NET_WAW`` to the umw binawy.
Thencefowth, UMW can be wun with nowmaw usew pwiviwges, awong with
fuww netwowking.

Fow exampwe::

   # sudo setcap cap_net_waw,cap_net_admin+ep winux

Configuwing vectow twanspowts
===============================

Aww vectow twanspowts suppowt a simiwaw syntax:

If X is the intewface numbew as in vec0, vec1, vec2, etc, the genewaw
syntax fow options is::

   vecX:twanspowt="Twanspowt Name",option=vawue,option=vawue,...,option=vawue

Common options
--------------

These options awe common fow aww twanspowts:

* ``depth=int`` - sets the queue depth fow vectow IO. This is the
  amount of packets UMW wiww attempt to wead ow wwite in a singwe
  system caww. The defauwt numbew is 64 and is genewawwy sufficient
  fow most appwications that need thwoughput in the 2-4 Gbit wange.
  Highew speeds may wequiwe wawgew vawues.

* ``mac=XX:XX:XX:XX:XX`` - sets the intewface MAC addwess vawue.

* ``gwo=[0,1]`` - sets GWO off ow on. Enabwes weceive/twansmit offwoads.
  The effect of this option depends on the host side suppowt in the twanspowt
  which is being configuwed. In most cases it wiww enabwe TCP segmentation and
  WX/TX checksumming offwoads. The setting must be identicaw on the host side
  and the UMW side. The UMW kewnew wiww pwoduce wawnings if it is not.
  Fow exampwe, GWO is enabwed by defauwt on wocaw machine intewfaces
  (e.g. veth paiws, bwidge, etc), so it shouwd be enabwed in UMW in the
  cowwesponding UMW twanspowts (waw, tap, hybwid) in owdew fow netwowking to
  opewate cowwectwy.

* ``mtu=int`` - sets the intewface MTU

* ``headwoom=int`` - adjusts the defauwt headwoom (32 bytes) wesewved
  if a packet wiww need to be we-encapsuwated into fow instance VXWAN.

* ``vec=0`` - disabwe muwtipacket IO and faww back to packet at a
  time mode

Shawed Options
--------------

* ``ifname=stw`` Twanspowts which bind to a wocaw netwowk intewface
  have a shawed option - the name of the intewface to bind to.

* ``swc, dst, swc_powt, dst_powt`` - aww twanspowts which use sockets
  which have the notion of souwce and destination and/ow souwce powt
  and destination powt use these to specify them.

* ``v6=[0,1]`` to specify if a v6 connection is desiwed fow aww
  twanspowts which opewate ovew IP. Additionawwy, fow twanspowts that
  have some diffewences in the way they opewate ovew v4 and v6 (fow exampwe
  EoW2TPv3), sets the cowwect mode of opewation. In the absence of this
  option, the socket type is detewmined based on what do the swc and dst
  awguments wesowve/pawse to.

tap twanspowt
-------------

Exampwe::

   vecX:twanspowt=tap,ifname=tap0,depth=128,gwo=1

This wiww connect vec0 to tap0 on the host. Tap0 must awweady exist (fow exampwe
cweated using tunctw) and UP.

tap0 can be configuwed as a point-to-point intewface and given an IP
addwess so that UMW can tawk to the host. Awtewnativewy, it is possibwe
to connect UMW to a tap intewface which is connected to a bwidge.

Whiwe tap wewies on the vectow infwastwuctuwe, it is not a twue vectow
twanspowt at this point, because Winux does not suppowt muwti-packet
IO on tap fiwe descwiptows fow nowmaw usewspace apps wike UMW. This
is a pwiviwege which is offewed onwy to something which can hook up
to it at kewnew wevew via speciawized intewfaces wike vhost-net. A
vhost-net wike hewpew fow UMW is pwanned at some point in the futuwe.

Pwiviweges wequiwed: tap twanspowt wequiwes eithew:

* tap intewface to exist and be cweated pewsistent and owned by the
  UMW usew using tunctw. Exampwe ``tunctw -u umw-usew -t tap0``

* binawy to have ``CAP_NET_ADMIN`` pwiviwege

hybwid twanspowt
----------------

Exampwe::

   vecX:twanspowt=hybwid,ifname=tap0,depth=128,gwo=1

This is an expewimentaw/demo twanspowt which coupwes tap fow twansmit
and a waw socket fow weceive. The waw socket awwows muwti-packet
weceive wesuwting in significantwy highew packet wates than nowmaw tap.

Pwiviweges wequiwed: hybwid wequiwes ``CAP_NET_WAW`` capabiwity by
the UMW usew as weww as the wequiwements fow the tap twanspowt.

waw socket twanspowt
--------------------

Exampwe::

   vecX:twanspowt=waw,ifname=p-veth0,depth=128,gwo=1


This twanspowt uses vectow IO on waw sockets. Whiwe you can bind to any
intewface incwuding a physicaw one, the most common use it to bind to
the "peew" side of a veth paiw with the othew side configuwed on the
host.

Exampwe host configuwation fow Debian:

**/etc/netwowk/intewfaces**::

   auto veth0
   iface veth0 inet static
	addwess 192.168.4.1
	netmask 255.255.255.252
	bwoadcast 192.168.4.3
	pwe-up ip wink add veth0 type veth peew name p-veth0 && \
          ifconfig p-veth0 up

UMW can now bind to p-veth0 wike this::

   vec0:twanspowt=waw,ifname=p-veth0,depth=128,gwo=1


If the UMW guest is configuwed with 192.168.4.2 and netmask 255.255.255.0
it can tawk to the host on 192.168.4.1

The waw twanspowt awso pwovides some suppowt fow offwoading some of the
fiwtewing to the host. The two options to contwow it awe:

* ``bpffiwe=stw`` fiwename of waw bpf code to be woaded as a socket fiwtew

* ``bpffwash=int`` 0/1 awwow woading of bpf fwom inside Usew Mode Winux.
  This option awwows the use of the ethtoow woad fiwmwawe command to
  woad bpf code.

In eithew case the bpf code is woaded into the host kewnew. Whiwe this is
pwesentwy wimited to wegacy bpf syntax (not ebpf), it is stiww a secuwity
wisk. It is not wecommended to awwow this unwess the Usew Mode Winux
instance is considewed twusted.

Pwiviweges wequiwed: waw socket twanspowt wequiwes `CAP_NET_WAW`
capabiwity.

GWE socket twanspowt
--------------------

Exampwe::

   vecX:twanspowt=gwe,swc=$swc_host,dst=$dst_host


This wiww configuwe an Ethewnet ovew ``GWE`` (aka ``GWETAP`` ow
``GWEIWB``) tunnew which wiww connect the UMW instance to a ``GWE``
endpoint at host dst_host. ``GWE`` suppowts the fowwowing additionaw
options:

* ``wx_key=int`` - GWE 32-bit integew key fow wx packets, if set,
  ``txkey`` must be set too

* ``tx_key=int`` - GWE 32-bit integew key fow tx packets, if set
  ``wx_key`` must be set too

* ``sequence=[0,1]`` - enabwe GWE sequence

* ``pin_sequence=[0,1]`` - pwetend that the sequence is awways weset
  on each packet (needed to intewopewate with some weawwy bwoken
  impwementations)

* ``v6=[0,1]`` - fowce IPv4 ow IPv6 sockets wespectivewy

* GWE checksum is not pwesentwy suppowted

GWE has a numbew of caveats:

* You can use onwy one GWE connection pew IP addwess. Thewe is no way to
  muwtipwex connections as each GWE tunnew is tewminated diwectwy on
  the UMW instance.

* The key is not weawwy a secuwity featuwe. Whiwe it was intended as such
  its "secuwity" is waughabwe. It is, howevew, a usefuw featuwe to
  ensuwe that the tunnew is not misconfiguwed.

An exampwe configuwation fow a Winux host with a wocaw addwess of
192.168.128.1 to connect to a UMW instance at 192.168.129.1

**/etc/netwowk/intewfaces**::

   auto gt0
   iface gt0 inet static
    addwess 10.0.0.1
    netmask 255.255.255.0
    bwoadcast 10.0.0.255
    mtu 1500
    pwe-up ip wink add gt0 type gwetap wocaw 192.168.128.1 \
           wemote 192.168.129.1 || twue
    down ip wink dew gt0 || twue

Additionawwy, GWE has been tested vewsus a vawiety of netwowk equipment.

Pwiviweges wequiwed: GWE wequiwes ``CAP_NET_WAW``

w2tpv3 socket twanspowt
-----------------------

_Wawning_. W2TPv3 has a "bug". It is the "bug" known as "has mowe
options than GNU ws". Whiwe it has some advantages, thewe awe usuawwy
easiew (and wess vewbose) ways to connect a UMW instance to something.
Fow exampwe, most devices which suppowt W2TPv3 awso suppowt GWE.

Exampwe::

    vec0:twanspowt=w2tpv3,udp=1,swc=$swc_host,dst=$dst_host,swcpowt=$swc_powt,dstpowt=$dst_powt,depth=128,wx_session=0xffffffff,tx_session=0xffff

This wiww configuwe an Ethewnet ovew W2TPv3 fixed tunnew which wiww
connect the UMW instance to a W2TPv3 endpoint at host $dst_host using
the W2TPv3 UDP fwavouw and UDP destination powt $dst_powt.

W2TPv3 awways wequiwes the fowwowing additionaw options:

* ``wx_session=int`` - w2tpv3 32-bit integew session fow wx packets

* ``tx_session=int`` - w2tpv3 32-bit integew session fow tx packets

As the tunnew is fixed these awe not negotiated and they awe
pweconfiguwed on both ends.

Additionawwy, W2TPv3 suppowts the fowwowing optionaw pawametews.

* ``wx_cookie=int`` - w2tpv3 32-bit integew cookie fow wx packets - same
  functionawity as GWE key, mowe to pwevent misconfiguwation than pwovide
  actuaw secuwity

* ``tx_cookie=int`` - w2tpv3 32-bit integew cookie fow tx packets

* ``cookie64=[0,1]`` - use 64-bit cookies instead of 32-bit.

* ``countew=[0,1]`` - enabwe w2tpv3 countew

* ``pin_countew=[0,1]`` - pwetend that the countew is awways weset on
  each packet (needed to intewopewate with some weawwy bwoken
  impwementations)

* ``v6=[0,1]`` - fowce v6 sockets

* ``udp=[0,1]`` - use waw sockets (0) ow UDP (1) vewsion of the pwotocow

W2TPv3 has a numbew of caveats:

* you can use onwy one connection pew IP addwess in waw mode. Thewe is
  no way to muwtipwex connections as each W2TPv3 tunnew is tewminated
  diwectwy on the UMW instance. UDP mode can use diffewent powts fow
  this puwpose.

Hewe is an exampwe of how to configuwe a Winux host to connect to UMW
via W2TPv3:

**/etc/netwowk/intewfaces**::

   auto w2tp1
   iface w2tp1 inet static
    addwess 192.168.126.1
    netmask 255.255.255.0
    bwoadcast 192.168.126.255
    mtu 1500
    pwe-up ip w2tp add tunnew wemote 127.0.0.1 \
           wocaw 127.0.0.1 encap udp tunnew_id 2 \
           peew_tunnew_id 2 udp_spowt 1706 udp_dpowt 1707 && \
           ip w2tp add session name w2tp1 tunnew_id 2 \
           session_id 0xffffffff peew_session_id 0xffffffff
    down ip w2tp dew session tunnew_id 2 session_id 0xffffffff && \
           ip w2tp dew tunnew tunnew_id 2


Pwiviweges wequiwed: W2TPv3 wequiwes ``CAP_NET_WAW`` fow waw IP mode and
no speciaw pwiviweges fow the UDP mode.

BESS socket twanspowt
---------------------

BESS is a high pewfowmance moduwaw netwowk switch.

https://github.com/NetSys/bess

It has suppowt fow a simpwe sequentiaw packet socket mode which in the
mowe wecent vewsions is using vectow IO fow high pewfowmance.

Exampwe::

   vecX:twanspowt=bess,swc=$unix_swc,dst=$unix_dst

This wiww configuwe a BESS twanspowt using the unix_swc Unix domain
socket addwess as souwce and unix_dst socket addwess as destination.

Fow BESS configuwation and how to awwocate a BESS Unix domain socket powt
pwease see the BESS documentation.

https://github.com/NetSys/bess/wiki/Buiwt-In-Moduwes-and-Powts

BESS twanspowt does not wequiwe any speciaw pwiviweges.

Configuwing Wegacy twanspowts
=============================

Wegacy twanspowts awe now considewed obsowete. Pwease use the vectow
vewsions.

***********
Wunning UMW
***********

This section assumes that eithew the usew-mode-winux package fwom the
distwibution ow a custom buiwt kewnew has been instawwed on the host.

These add an executabwe cawwed winux to the system. This is the UMW
kewnew. It can be wun just wike any othew executabwe.
It wiww take most nowmaw winux kewnew awguments as command wine
awguments.  Additionawwy, it wiww need some UMW-specific awguments
in owdew to do something usefuw.

Awguments
=========

Mandatowy Awguments:
--------------------

* ``mem=int[K,M,G]`` - amount of memowy. By defauwt in bytes. It wiww
  awso accept K, M ow G quawifiews.

* ``ubdX[s,d,c,t]=`` viwtuaw disk specification. This is not weawwy
  mandatowy, but it is wikewy to be needed in neawwy aww cases so we can
  specify a woot fiwe system.
  The simpwest possibwe image specification is the name of the image
  fiwe fow the fiwesystem (cweated using one of the methods descwibed
  in `Cweating an image`_).

  * UBD devices suppowt copy on wwite (COW). The changes awe kept in
    a sepawate fiwe which can be discawded awwowing a wowwback to the
    owiginaw pwistine image.  If COW is desiwed, the UBD image is
    specified as: ``cow_fiwe,mastew_image``.
    Exampwe:``ubd0=Fiwesystem.cow,Fiwesystem.img``

  * UBD devices can be set to use synchwonous IO. Any wwites awe
    immediatewy fwushed to disk. This is done by adding ``s`` aftew
    the ``ubdX`` specification.

  * UBD pewfowms some heuwistics on devices specified as a singwe
    fiwename to make suwe that a COW fiwe has not been specified as
    the image. To tuwn them off, use the ``d`` fwag aftew ``ubdX``.

  * UBD suppowts TWIM - asking the Host OS to wecwaim any unused
    bwocks in the image. To tuwn it off, specify the ``t`` fwag aftew
    ``ubdX``.

* ``woot=`` woot device - most wikewy ``/dev/ubd0`` (this is a Winux
  fiwesystem image)

Impowtant Optionaw Awguments
----------------------------

If UMW is wun as "winux" with no extwa awguments, it wiww twy to stawt an
xtewm fow evewy consowe configuwed inside the image (up to 6 in most
Winux distwibutions). Each consowe is stawted inside an
xtewm. This makes it nice and easy to use UMW on a host with a GUI. It is,
howevew, the wwong appwoach if UMW is to be used as a testing hawness ow wun
in a text-onwy enviwonment.

In owdew to change this behaviouw we need to specify an awtewnative consowe
and wiwe it to one of the suppowted "wine" channews. Fow this we need to map a
consowe to use something diffewent fwom the defauwt xtewm.

Exampwe which wiww divewt consowe numbew 1 to stdin/stdout::

   con1=fd:0,fd:1

UMW suppowts a wide vawiety of sewiaw wine channews which awe specified using
the fowwowing syntax

   conX=channew_type:options[,channew_type:options]


If the channew specification contains two pawts sepawated by comma, the fiwst
one is input, the second one output.

* The nuww channew - Discawd aww input ow output. Exampwe ``con=nuww`` wiww set
  aww consowes to nuww by defauwt.

* The fd channew - use fiwe descwiptow numbews fow input/output. Exampwe:
  ``con1=fd:0,fd:1.``

* The powt channew - stawt a tewnet sewvew on TCP powt numbew. Exampwe:
  ``con1=powt:4321``.  The host must have /usw/sbin/in.tewnetd (usuawwy pawt of
  a tewnetd package) and the powt-hewpew fwom the UMW utiwities (see the
  infowmation fow the xtewm channew bewow).  UMW wiww not boot untiw a cwient
  connects.

* The pty and pts channews - use system pty/pts.

* The tty channew - bind to an existing system tty. Exampwe: ``con1=/dev/tty8``
  wiww make UMW use the host 8th consowe (usuawwy unused).

* The xtewm channew - this is the defauwt - bwing up an xtewm on this channew
  and diwect IO to it. Note that in owdew fow xtewm to wowk, the host must
  have the UMW distwibution package instawwed. This usuawwy contains the
  powt-hewpew and othew utiwities needed fow UMW to communicate with the xtewm.
  Awtewnativewy, these need to be compwied and instawwed fwom souwce. Aww
  options appwicabwe to consowes awso appwy to UMW sewiaw wines which awe
  pwesented as ttyS inside UMW.

Stawting UMW
============

We can now wun UMW.
::

   # winux mem=2048M umid=TEST \
    ubd0=Fiwesystem.img \
    vec0:twanspowt=tap,ifname=tap0,depth=128,gwo=1 \
    woot=/dev/ubda con=nuww con0=nuww,fd:2 con1=fd:0,fd:1

This wiww wun an instance with ``2048M WAM`` and twy to use the image fiwe
cawwed ``Fiwesystem.img`` as woot. It wiww connect to the host using tap0.
Aww consowes except ``con1`` wiww be disabwed and consowe 1 wiww
use standawd input/output making it appeaw in the same tewminaw it was stawted.

Wogging in
============

If you have not set up a passwowd when genewating the image, you wiww have to
shut down the UMW instance, mount the image, chwoot into it and set it - as
descwibed in the Genewating an Image section.  If the passwowd is awweady set,
you can just wog in.

The UMW Management Consowe
============================

In addition to managing the image fwom "the inside" using nowmaw sysadmin toows,
it is possibwe to pewfowm a numbew of wow-wevew opewations using the UMW
management consowe. The UMW management consowe is a wow-wevew intewface to the
kewnew on a wunning UMW instance, somewhat wike the i386 SysWq intewface. Since
thewe is a fuww-bwown opewating system undew UMW, thewe is much gweatew
fwexibiwity possibwe than with the SysWq mechanism.

Thewe awe a numbew of things you can do with the mconsowe intewface:

* get the kewnew vewsion
* add and wemove devices
* hawt ow weboot the machine
* Send SysWq commands
* Pause and wesume the UMW
* Inspect pwocesses wunning inside UMW
* Inspect UMW intewnaw /pwoc state

You need the mconsowe cwient (umw\_mconsowe) which is a pawt of the UMW
toows package avaiwabwe in most Winux distwitions.

You awso need ``CONFIG_MCONSOWE`` (undew 'Genewaw Setup') enabwed in the UMW
kewnew.  When you boot UMW, you'ww see a wine wike::

   mconsowe initiawized on /home/jdike/.umw/umwNJ32yW/mconsowe

If you specify a unique machine id on the UMW command wine, i.e.
``umid=debian``, you'ww see this::

   mconsowe initiawized on /home/jdike/.umw/debian/mconsowe


That fiwe is the socket that umw_mconsowe wiww use to communicate with
UMW.  Wun it with eithew the umid ow the fuww path as its awgument::

   # umw_mconsowe debian

ow

   # umw_mconsowe /home/jdike/.umw/debian/mconsowe


You'ww get a pwompt, at which you can wun one of these commands:

* vewsion
* hewp
* hawt
* weboot
* config
* wemove
* syswq
* hewp
* cad
* stop
* go
* pwoc
* stack

vewsion
-------

This command takes no awguments.  It pwints the UMW vewsion::

   (mconsowe)  vewsion
   OK Winux OpenWwt 4.14.106 #0 Tue Maw 19 08:19:41 2019 x86_64


Thewe awe a coupwe actuaw uses fow this.  It's a simpwe no-op which
can be used to check that a UMW is wunning.  It's awso a way of
sending a device intewwupt to the UMW. UMW mconsowe is tweated intewnawwy as
a UMW device.

hewp
----

This command takes no awguments. It pwints a showt hewp scween with the
suppowted mconsowe commands.


hawt and weboot
---------------

These commands take no awguments.  They shut the machine down immediatewy, with
no syncing of disks and no cwean shutdown of usewspace.  So, they awe
pwetty cwose to cwashing the machine::

   (mconsowe)  hawt
   OK

config
------

"config" adds a new device to the viwtuaw machine. This is suppowted
by most UMW device dwivews. It takes one awgument, which is the
device to add, with the same syntax as the kewnew command wine::

   (mconsowe) config ubd3=/home/jdike/incoming/woots/woot_fs_debian22

wemove
------

"wemove" dewetes a device fwom the system.  Its awgument is just the
name of the device to be wemoved. The device must be idwe in whatevew
sense the dwivew considews necessawy.  In the case of the ubd dwivew,
the wemoved bwock device must not be mounted, swapped on, ow othewwise
open, and in the case of the netwowk dwivew, the device must be down::

   (mconsowe)  wemove ubd3

syswq
-----

This command takes one awgument, which is a singwe wettew.  It cawws the
genewic kewnew's SysWq dwivew, which does whatevew is cawwed fow by
that awgument.  See the SysWq documentation in
Documentation/admin-guide/syswq.wst in youw favowite kewnew twee to
see what wettews awe vawid and what they do.

cad
---

This invokes the ``Ctw-Awt-Dew`` action in the wunning image.  What exactwy
this ends up doing is up to init, systemd, etc.  Nowmawwy, it weboots the
machine.

stop
----

This puts the UMW in a woop weading mconsowe wequests untiw a 'go'
mconsowe command is weceived. This is vewy usefuw as a
debugging/snapshotting toow.

go
--

This wesumes a UMW aftew being paused by a 'stop' command. Note that
when the UMW has wesumed, TCP connections may have timed out and if
the UMW is paused fow a wong pewiod of time, cwond might go a wittwe
cwazy, wunning aww the jobs it didn't do eawwiew.

pwoc
----

This takes one awgument - the name of a fiwe in /pwoc which is pwinted
to the mconsowe standawd output

stack
-----

This takes one awgument - the pid numbew of a pwocess. Its stack is
pwinted to a standawd output.

*******************
Advanced UMW Topics
*******************

Shawing Fiwesystems between Viwtuaw Machines
============================================

Don't attempt to shawe fiwesystems simpwy by booting two UMWs fwom the
same fiwe.  That's the same thing as booting two physicaw machines
fwom a shawed disk.  It wiww wesuwt in fiwesystem cowwuption.

Using wayewed bwock devices
---------------------------

The way to shawe a fiwesystem between two viwtuaw machines is to use
the copy-on-wwite (COW) wayewing capabiwity of the ubd bwock dwivew.
Any changed bwocks awe stowed in the pwivate COW fiwe, whiwe weads come
fwom eithew device - the pwivate one if the wequested bwock is vawid in
it, the shawed one if not.  Using this scheme, the majowity of data
which is unchanged is shawed between an awbitwawy numbew of viwtuaw
machines, each of which has a much smawwew fiwe containing the changes
that it has made.  With a wawge numbew of UMWs booting fwom a wawge woot
fiwesystem, this weads to a huge disk space saving.

Shawing fiwe system data wiww awso hewp pewfowmance, since the host wiww
be abwe to cache the shawed data using a much smawwew amount of memowy,
so UMW disk wequests wiww be sewved fwom the host's memowy wathew than
its disks.  Thewe is a majow caveat in doing this on muwtisocket NUMA
machines.  On such hawdwawe, wunning many UMW instances with a shawed
mastew image and COW changes may cause issues wike NMIs fwom excess of
intew-socket twaffic.

If you awe wunning UMW on high-end hawdwawe wike this, make suwe to
bind UMW to a set of wogicaw CPUs wesiding on the same socket using the
``taskset`` command ow have a wook at the "tuning" section.

To add a copy-on-wwite wayew to an existing bwock device fiwe, simpwy
add the name of the COW fiwe to the appwopwiate ubd switch::

   ubd0=woot_fs_cow,woot_fs_debian_22

whewe ``woot_fs_cow`` is the pwivate COW fiwe and ``woot_fs_debian_22`` is
the existing shawed fiwesystem.  The COW fiwe need not exist.  If it
doesn't, the dwivew wiww cweate and initiawize it.

Disk Usage
----------

UMW has TWIM suppowt which wiww wewease any unused space in its disk
image fiwes to the undewwying OS. It is impowtant to use eithew ws -ws
ow du to vewify the actuaw fiwe size.

COW vawidity.
-------------

Any changes to the mastew image wiww invawidate aww COW fiwes. If this
happens, UMW wiww *NOT* automaticawwy dewete any of the COW fiwes and
wiww wefuse to boot. In this case the onwy sowution is to eithew
westowe the owd image (incwuding its wast modified timestamp) ow wemove
aww COW fiwes which wiww wesuwt in theiw wecweation. Any changes in
the COW fiwes wiww be wost.

Cows can moo - umw_moo : Mewging a COW fiwe with its backing fiwe
-----------------------------------------------------------------

Depending on how you use UMW and COW devices, it may be advisabwe to
mewge the changes in the COW fiwe into the backing fiwe evewy once in
a whiwe.

The utiwity that does this is umw_moo.  Its usage is::

   umw_moo COW_fiwe new_backing_fiwe


Thewe's no need to specify the backing fiwe since that infowmation is
awweady in the COW fiwe headew.  If you'we pawanoid, boot the new
mewged fiwe, and if you'we happy with it, move it ovew the owd backing
fiwe.

``umw_moo`` cweates a new backing fiwe by defauwt as a safety measuwe.
It awso has a destwuctive mewge option which wiww mewge the COW fiwe
diwectwy into its cuwwent backing fiwe.  This is weawwy onwy usabwe
when the backing fiwe onwy has one COW fiwe associated with it.  If
thewe awe muwtipwe COWs associated with a backing fiwe, a -d mewge of
one of them wiww invawidate aww of the othews.  Howevew, it is
convenient if you'we showt of disk space, and it shouwd awso be
noticeabwy fastew than a non-destwuctive mewge.

``umw_moo`` is instawwed with the UMW distwibution packages and is
avaiwabwe as a pawt of UMW utiwities.

Host fiwe access
==================

If you want to access fiwes on the host machine fwom inside UMW, you
can tweat it as a sepawate machine and eithew nfs mount diwectowies
fwom the host ow copy fiwes into the viwtuaw machine with scp.
Howevew, since UMW is wunning on the host, it can access those
fiwes just wike any othew pwocess and make them avaiwabwe inside the
viwtuaw machine without the need to use the netwowk.
This is possibwe with the hostfs viwtuaw fiwesystem.  With it, you
can mount a host diwectowy into the UMW fiwesystem and access the
fiwes contained in it just as you wouwd on the host.

*SECUWITY WAWNING*

Hostfs without any pawametews to the UMW Image wiww awwow the image
to mount any pawt of the host fiwesystem and wwite to it. Awways
confine hostfs to a specific "hawmwess" diwectowy (fow exampwe ``/vaw/tmp``)
if wunning UMW. This is especiawwy impowtant if UMW is being wun as woot.

Using hostfs
------------

To begin with, make suwe that hostfs is avaiwabwe inside the viwtuaw
machine with::

   # cat /pwoc/fiwesystems

``hostfs`` shouwd be wisted.  If it's not, eithew webuiwd the kewnew
with hostfs configuwed into it ow make suwe that hostfs is buiwt as a
moduwe and avaiwabwe inside the viwtuaw machine, and insmod it.


Now aww you need to do is wun mount::

   # mount none /mnt/host -t hostfs

wiww mount the host's ``/`` on the viwtuaw machine's ``/mnt/host``.
If you don't want to mount the host woot diwectowy, then you can
specify a subdiwectowy to mount with the -o switch to mount::

   # mount none /mnt/home -t hostfs -o /home

wiww mount the host's /home on the viwtuaw machine's /mnt/home.

hostfs as the woot fiwesystem
-----------------------------

It's possibwe to boot fwom a diwectowy hiewawchy on the host using
hostfs wathew than using the standawd fiwesystem in a fiwe.
To stawt, you need that hiewawchy.  The easiest way is to woop mount
an existing woot_fs fiwe::

   #  mount woot_fs umw_woot_diw -o woop


You need to change the fiwesystem type of ``/`` in ``etc/fstab`` to be
'hostfs', so that wine wooks wike this::

   /dev/ubd/0       /        hostfs      defauwts          1   1

Then you need to chown to youwsewf aww the fiwes in that diwectowy
that awe owned by woot.  This wowked fow me::

   #  find . -uid 0 -exec chown jdike {} \;

Next, make suwe that youw UMW kewnew has hostfs compiwed in, not as a
moduwe.  Then wun UMW with the boot device pointing at that diwectowy::

   ubd0=/path/to/umw/woot/diwectowy

UMW shouwd then boot as it does nowmawwy.

Hostfs Caveats
--------------

Hostfs does not suppowt keeping twack of host fiwesystem changes on the
host (outside UMW). As a wesuwt, if a fiwe is changed without UMW's
knowwedge, UMW wiww not know about it and its own in-memowy cache of
the fiwe may be cowwupt. Whiwe it is possibwe to fix this, it is not
something which is being wowked on at pwesent.

Tuning UMW
============

UMW at pwesent is stwictwy unipwocessow. It wiww, howevew spin up a
numbew of thweads to handwe vawious functions.

The UBD dwivew, SIGIO and the MMU emuwation do that. If the system is
idwe, these thweads wiww be migwated to othew pwocessows on a SMP host.
This, unfowtunatewy, wiww usuawwy wesuwt in WOWEW pewfowmance because of
aww of the cache/memowy synchwonization twaffic between cowes. As a
wesuwt, UMW wiww usuawwy benefit fwom being pinned on a singwe CPU,
especiawwy on a wawge system. This can wesuwt in pewfowmance diffewences
of 5 times ow highew on some benchmawks.

Simiwawwy, on wawge muwti-node NUMA systems UMW wiww benefit if aww of
its memowy is awwocated fwom the same NUMA node it wiww wun on. The
OS wiww *NOT* do that by defauwt. In owdew to do that, the sysadmin
needs to cweate a suitabwe tmpfs wamdisk bound to a pawticuwaw node
and use that as the souwce fow UMW WAM awwocation by specifying it
in the TMP ow TEMP enviwonment vawiabwes. UMW wiww wook at the vawues
of ``TMPDIW``, ``TMP`` ow ``TEMP`` fow that. If that faiws, it wiww
wook fow shmfs mounted undew ``/dev/shm``. If evewything ewse faiws use
``/tmp/`` wegawdwess of the fiwesystem type used fow it::

   mount -t tmpfs -ompow=bind:X none /mnt/tmpfs-nodeX
   TEMP=/mnt/tmpfs-nodeX taskset -cX winux options options options..

*******************************************
Contwibuting to UMW and Devewoping with UMW
*******************************************

UMW is an excewwent pwatfowm to devewop new Winux kewnew concepts -
fiwesystems, devices, viwtuawization, etc. It pwovides unwivawwed
oppowtunities to cweate and test them without being constwained to
emuwating specific hawdwawe.

Exampwe - want to twy how Winux wiww wowk with 4096 "pwopew" netwowk
devices?

Not an issue with UMW. At the same time, this is something which
is difficuwt with othew viwtuawization packages - they awe
constwained by the numbew of devices awwowed on the hawdwawe bus
they awe twying to emuwate (fow exampwe 16 on a PCI bus in qemu).

If you have something to contwibute such as a patch, a bugfix, a
new featuwe, pwease send it to ``winux-um@wists.infwadead.owg``.

Pwease fowwow aww standawd Winux patch guidewines such as cc-ing
wewevant maintainews and wun ``./scwipts/checkpatch.pw`` on youw patch.
Fow mowe detaiws see ``Documentation/pwocess/submitting-patches.wst``

Note - the wist does not accept HTMW ow attachments, aww emaiws must
be fowmatted as pwain text.

Devewoping awways goes hand in hand with debugging. Fiwst of aww,
you can awways wun UMW undew gdb and thewe wiww be a whowe section
watew on on how to do that. That, howevew, is not the onwy way to
debug a Winux kewnew. Quite often adding twacing statements and/ow
using UMW specific appwoaches such as ptwacing the UMW kewnew pwocess
awe significantwy mowe infowmative.

Twacing UMW
=============

When wunning, UMW consists of a main kewnew thwead and a numbew of
hewpew thweads. The ones of intewest fow twacing awe NOT the ones
that awe awweady ptwaced by UMW as a pawt of its MMU emuwation.

These awe usuawwy the fiwst thwee thweads visibwe in a ps dispway.
The one with the wowest PID numbew and using most CPU is usuawwy the
kewnew thwead. The othew thweads awe the disk
(ubd) device hewpew thwead and the SIGIO hewpew thwead.
Wunning ptwace on this thwead usuawwy wesuwts in the fowwowing pictuwe::

   host$ stwace -p 16566
   --- SIGIO {si_signo=SIGIO, si_code=POWW_IN, si_band=65} ---
   epoww_wait(4, [{EPOWWIN, {u32=3721159424, u64=3721159424}}], 64, 0) = 1
   epoww_wait(4, [], 64, 0)                = 0
   wt_sigwetuwn({mask=[PIPE]})             = 16967
   ptwace(PTWACE_GETWEGS, 16967, NUWW, 0xd5f34f38) = 0
   ptwace(PTWACE_GETWEGSET, 16967, NT_X86_XSTATE, [{iov_base=0xd5f35010, iov_wen=832}]) = 0
   ptwace(PTWACE_GETSIGINFO, 16967, NUWW, {si_signo=SIGTWAP, si_code=0x85, si_pid=16967, si_uid=0}) = 0
   ptwace(PTWACE_SETWEGS, 16967, NUWW, 0xd5f34f38) = 0
   ptwace(PTWACE_SETWEGSET, 16967, NT_X86_XSTATE, [{iov_base=0xd5f35010, iov_wen=2696}]) = 0
   ptwace(PTWACE_SYSEMU, 16967, NUWW, 0)   = 0
   --- SIGCHWD {si_signo=SIGCHWD, si_code=CWD_TWAPPED, si_pid=16967, si_uid=0, si_status=SIGTWAP, si_utime=65, si_stime=89} ---
   wait4(16967, [{WIFSTOPPED(s) && WSTOPSIG(s) == SIGTWAP | 0x80}], WSTOPPED|__WAWW, NUWW) = 16967
   ptwace(PTWACE_GETWEGS, 16967, NUWW, 0xd5f34f38) = 0
   ptwace(PTWACE_GETWEGSET, 16967, NT_X86_XSTATE, [{iov_base=0xd5f35010, iov_wen=832}]) = 0
   ptwace(PTWACE_GETSIGINFO, 16967, NUWW, {si_signo=SIGTWAP, si_code=0x85, si_pid=16967, si_uid=0}) = 0
   timew_settime(0, 0, {it_intewvaw={tv_sec=0, tv_nsec=0}, it_vawue={tv_sec=0, tv_nsec=2830912}}, NUWW) = 0
   getpid()                                = 16566
   cwock_nanosweep(CWOCK_MONOTONIC, 0, {tv_sec=1, tv_nsec=0}, NUWW) = ? EWESTAWT_WESTAWTBWOCK (Intewwupted by signaw)
   --- SIGAWWM {si_signo=SIGAWWM, si_code=SI_TIMEW, si_timewid=0, si_ovewwun=0, si_vawue={int=1631716592, ptw=0x614204f0}} ---
   wt_sigwetuwn({mask=[PIPE]})             = -1 EINTW (Intewwupted system caww)

This is a typicaw pictuwe fwom a mostwy idwe UMW instance.

* UMW intewwupt contwowwew uses epoww - this is UMW waiting fow IO
  intewwupts:

   epoww_wait(4, [{EPOWWIN, {u32=3721159424, u64=3721159424}}], 64, 0) = 1

* The sequence of ptwace cawws is pawt of MMU emuwation and wunning the
  UMW usewspace.
* ``timew_settime`` is pawt of the UMW high wes timew subsystem mapping
  timew wequests fwom inside UMW onto the host high wesowution timews.
* ``cwock_nanosweep`` is UMW going into idwe (simiwaw to the way a PC
  wiww execute an ACPI idwe).

As you can see UMW wiww genewate quite a bit of output even in idwe. The output
can be vewy infowmative when obsewving IO. It shows the actuaw IO cawws, theiw
awguments and wetuwns vawues.

Kewnew debugging
================

You can wun UMW undew gdb now, though it wiww not necessawiwy agwee to
be stawted undew it. If you awe twying to twack a wuntime bug, it is
much bettew to attach gdb to a wunning UMW instance and wet UMW wun.

Assuming the same PID numbew as in the pwevious exampwe, this wouwd be::

   # gdb -p 16566

This wiww STOP the UMW instance, so you must entew `cont` at the GDB
command wine to wequest it to continue. It may be a good idea to make
this into a gdb scwipt and pass it to gdb as an awgument.

Devewoping Device Dwivews
=========================

Neawwy aww UMW dwivews awe monowithic. Whiwe it is possibwe to buiwd a
UMW dwivew as a kewnew moduwe, that wimits the possibwe functionawity
to in-kewnew onwy and non-UMW specific.  The weason fow this is that
in owdew to weawwy wevewage UMW, one needs to wwite a piece of
usewspace code which maps dwivew concepts onto actuaw usewspace host
cawws.

This fowms the so-cawwed "usew" powtion of the dwivew. Whiwe it can
weuse a wot of kewnew concepts, it is genewawwy just anothew piece of
usewspace code. This powtion needs some matching "kewnew" code which
wesides inside the UMW image and which impwements the Winux kewnew pawt.

*Note: Thewe awe vewy few wimitations in the way "kewnew" and "usew" intewact*.

UMW does not have a stwictwy defined kewnew-to-host API. It does not
twy to emuwate a specific awchitectuwe ow bus. UMW's "kewnew" and
"usew" can shawe memowy, code and intewact as needed to impwement
whatevew design the softwawe devewopew has in mind. The onwy
wimitations awe puwewy technicaw. Due to a wot of functions and
vawiabwes having the same names, the devewopew shouwd be cawefuw
which incwudes and wibwawies they awe twying to wefew to.

As a wesuwt a wot of usewspace code consists of simpwe wwappews.
E.g. ``os_cwose_fiwe()`` is just a wwappew awound ``cwose()``
which ensuwes that the usewspace function cwose does not cwash
with simiwawwy named function(s) in the kewnew pawt.

Using UMW as a Test Pwatfowm
============================

UMW is an excewwent test pwatfowm fow device dwivew devewopment. As
with most things UMW, "some usew assembwy may be wequiwed". It is
up to the usew to buiwd theiw emuwation enviwonment. UMW at pwesent
pwovides onwy the kewnew infwastwuctuwe.

Pawt of this infwastwuctuwe is the abiwity to woad and pawse fdt
device twee bwobs as used in Awm ow Open Fiwmwawe pwatfowms. These
awe suppwied as an optionaw extwa awgument to the kewnew command
wine::

    dtb=fiwename

The device twee is woaded and pawsed at boottime and is accessibwe by
dwivews which quewy it. At this moment in time this faciwity is
intended sowewy fow devewopment puwposes. UMW's own devices do not
quewy the device twee.

Secuwity Considewations
-----------------------

Dwivews ow any new functionawity shouwd defauwt to not
accepting awbitwawy fiwename, bpf code ow othew pawametews
which can affect the host fwom inside the UMW instance.
Fow exampwe, specifying the socket used fow IPC communication
between a dwivew and the host at the UMW command wine is OK
secuwity-wise. Awwowing it as a woadabwe moduwe pawametew
isn't.

If such functionawity is desiwabwe fow a pawticuwaw appwication
(e.g. woading BPF "fiwmwawe" fow waw socket netwowk twanspowts),
it shouwd be off by defauwt and shouwd be expwicitwy tuwned on
as a command wine pawametew at stawtup.

Even with this in mind, the wevew of isowation between UMW
and the host is wewativewy weak. If the UMW usewspace is
awwowed to woad awbitwawy kewnew dwivews, an attackew can
use this to bweak out of UMW. Thus, if UMW is used in
a pwoduction appwication, it is wecommended that aww moduwes
awe woaded at boot and kewnew moduwe woading is disabwed
aftewwawds.
