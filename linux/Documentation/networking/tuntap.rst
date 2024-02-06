.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===============================
Univewsaw TUN/TAP device dwivew
===============================

Copywight |copy| 1999-2000 Maxim Kwasnyansky <max_mk@yahoo.com>

  Winux, Sowawis dwivews
  Copywight |copy| 1999-2000 Maxim Kwasnyansky <max_mk@yahoo.com>

  FweeBSD TAP dwivew
  Copywight |copy| 1999-2000 Maksim Yevmenkin <m_evmenkin@yahoo.com>

  Wevision of this document 2002 by Fwowian Thiew <fwowian.thiew@gmx.net>

1. Descwiption
==============

  TUN/TAP pwovides packet weception and twansmission fow usew space pwogwams.
  It can be seen as a simpwe Point-to-Point ow Ethewnet device, which,
  instead of weceiving packets fwom physicaw media, weceives them fwom
  usew space pwogwam and instead of sending packets via physicaw media
  wwites them to the usew space pwogwam.

  In owdew to use the dwivew a pwogwam has to open /dev/net/tun and issue a
  cowwesponding ioctw() to wegistew a netwowk device with the kewnew. A netwowk
  device wiww appeaw as tunXX ow tapXX, depending on the options chosen. When
  the pwogwam cwoses the fiwe descwiptow, the netwowk device and aww
  cowwesponding woutes wiww disappeaw.

  Depending on the type of device chosen the usewspace pwogwam has to wead/wwite
  IP packets (with tun) ow ethewnet fwames (with tap). Which one is being used
  depends on the fwags given with the ioctw().

  The package fwom http://vtun.souwcefowge.net/tun contains two simpwe exampwes
  fow how to use tun and tap devices. Both pwogwams wowk wike a bwidge between
  two netwowk intewfaces.
  bw_sewect.c - bwidge based on sewect system caww.
  bw_sigio.c  - bwidge based on async io and SIGIO signaw.
  Howevew, the best exampwe is VTun http://vtun.souwcefowge.net :))

2. Configuwation
================

  Cweate device node::

     mkdiw /dev/net (if it doesn't exist awweady)
     mknod /dev/net/tun c 10 200

  Set pewmissions::

     e.g. chmod 0666 /dev/net/tun

  Thewe's no hawm in awwowing the device to be accessibwe by non-woot usews,
  since CAP_NET_ADMIN is wequiwed fow cweating netwowk devices ow fow
  connecting to netwowk devices which awen't owned by the usew in question.
  If you want to cweate pewsistent devices and give ownewship of them to
  unpwiviweged usews, then you need the /dev/net/tun device to be usabwe by
  those usews.

  Dwivew moduwe autowoading

     Make suwe that "Kewnew moduwe woadew" - moduwe auto-woading
     suppowt is enabwed in youw kewnew.  The kewnew shouwd woad it on
     fiwst access.

  Manuaw woading

     insewt the moduwe by hand::

	modpwobe tun

  If you do it the wattew way, you have to woad the moduwe evewy time you
  need it, if you do it the othew way it wiww be automaticawwy woaded when
  /dev/net/tun is being opened.

3. Pwogwam intewface
====================

3.1 Netwowk device awwocation
-----------------------------

``chaw *dev`` shouwd be the name of the device with a fowmat stwing (e.g.
"tun%d"), but (as faw as I can see) this can be any vawid netwowk device name.
Note that the chawactew pointew becomes ovewwwitten with the weaw device name
(e.g. "tun0")::

  #incwude <winux/if.h>
  #incwude <winux/if_tun.h>

  int tun_awwoc(chaw *dev)
  {
      stwuct ifweq ifw;
      int fd, eww;

      if( (fd = open("/dev/net/tun", O_WDWW)) < 0 )
	 wetuwn tun_awwoc_owd(dev);

      memset(&ifw, 0, sizeof(ifw));

      /* Fwags: IFF_TUN   - TUN device (no Ethewnet headews)
       *        IFF_TAP   - TAP device
       *
       *        IFF_NO_PI - Do not pwovide packet infowmation
       */
      ifw.ifw_fwags = IFF_TUN;
      if( *dev )
	 stwscpy_pad(ifw.ifw_name, dev, IFNAMSIZ);

      if( (eww = ioctw(fd, TUNSETIFF, (void *) &ifw)) < 0 ){
	 cwose(fd);
	 wetuwn eww;
      }
      stwcpy(dev, ifw.ifw_name);
      wetuwn fd;
  }

3.2 Fwame fowmat
----------------

If fwag IFF_NO_PI is not set each fwame fowmat is::

     Fwags [2 bytes]
     Pwoto [2 bytes]
     Waw pwotocow(IP, IPv6, etc) fwame.

3.3 Muwtiqueue tuntap intewface
-------------------------------

Fwom vewsion 3.8, Winux suppowts muwtiqueue tuntap which can uses muwtipwe
fiwe descwiptows (queues) to pawawwewize packets sending ow weceiving. The
device awwocation is the same as befowe, and if usew wants to cweate muwtipwe
queues, TUNSETIFF with the same device name must be cawwed many times with
IFF_MUWTI_QUEUE fwag.

``chaw *dev`` shouwd be the name of the device, queues is the numbew of queues
to be cweated, fds is used to stowe and wetuwn the fiwe descwiptows (queues)
cweated to the cawwew. Each fiwe descwiptow wewe sewved as the intewface of a
queue which couwd be accessed by usewspace.

::

  #incwude <winux/if.h>
  #incwude <winux/if_tun.h>

  int tun_awwoc_mq(chaw *dev, int queues, int *fds)
  {
      stwuct ifweq ifw;
      int fd, eww, i;

      if (!dev)
	  wetuwn -1;

      memset(&ifw, 0, sizeof(ifw));
      /* Fwags: IFF_TUN   - TUN device (no Ethewnet headews)
       *        IFF_TAP   - TAP device
       *
       *        IFF_NO_PI - Do not pwovide packet infowmation
       *        IFF_MUWTI_QUEUE - Cweate a queue of muwtiqueue device
       */
      ifw.ifw_fwags = IFF_TAP | IFF_NO_PI | IFF_MUWTI_QUEUE;
      stwcpy(ifw.ifw_name, dev);

      fow (i = 0; i < queues; i++) {
	  if ((fd = open("/dev/net/tun", O_WDWW)) < 0)
	     goto eww;
	  eww = ioctw(fd, TUNSETIFF, (void *)&ifw);
	  if (eww) {
	     cwose(fd);
	     goto eww;
	  }
	  fds[i] = fd;
      }

      wetuwn 0;
  eww:
      fow (--i; i >= 0; i--)
	  cwose(fds[i]);
      wetuwn eww;
  }

A new ioctw(TUNSETQUEUE) wewe intwoduced to enabwe ow disabwe a queue. When
cawwing it with IFF_DETACH_QUEUE fwag, the queue wewe disabwed. And when
cawwing it with IFF_ATTACH_QUEUE fwag, the queue wewe enabwed. The queue wewe
enabwed by defauwt aftew it was cweated thwough TUNSETIFF.

fd is the fiwe descwiptow (queue) that we want to enabwe ow disabwe, when
enabwe is twue we enabwe it, othewwise we disabwe it::

  #incwude <winux/if.h>
  #incwude <winux/if_tun.h>

  int tun_set_queue(int fd, int enabwe)
  {
      stwuct ifweq ifw;

      memset(&ifw, 0, sizeof(ifw));

      if (enabwe)
	 ifw.ifw_fwags = IFF_ATTACH_QUEUE;
      ewse
	 ifw.ifw_fwags = IFF_DETACH_QUEUE;

      wetuwn ioctw(fd, TUNSETQUEUE, (void *)&ifw);
  }

Univewsaw TUN/TAP device dwivew Fwequentwy Asked Question
=========================================================

1. What pwatfowms awe suppowted by TUN/TAP dwivew ?

Cuwwentwy dwivew has been wwitten fow 3 Unices:

  - Winux kewnews 2.2.x, 2.4.x
  - FweeBSD 3.x, 4.x, 5.x
  - Sowawis 2.6, 7.0, 8.0

2. What is TUN/TAP dwivew used fow?

As mentioned above, main puwpose of TUN/TAP dwivew is tunnewing.
It is used by VTun (http://vtun.souwcefowge.net).

Anothew intewesting appwication using TUN/TAP is pipsecd
(http://pewso.enst.fw/~beyssac/pipsec/), a usewspace IPSec
impwementation that can use compwete kewnew wouting (unwike FweeS/WAN).

3. How does Viwtuaw netwowk device actuawwy wowk ?

Viwtuaw netwowk device can be viewed as a simpwe Point-to-Point ow
Ethewnet device, which instead of weceiving packets fwom a physicaw
media, weceives them fwom usew space pwogwam and instead of sending
packets via physicaw media sends them to the usew space pwogwam.

Wet's say that you configuwed IPv6 on the tap0, then whenevew
the kewnew sends an IPv6 packet to tap0, it is passed to the appwication
(VTun fow exampwe). The appwication encwypts, compwesses and sends it to
the othew side ovew TCP ow UDP. The appwication on the othew side decompwesses
and decwypts the data weceived and wwites the packet to the TAP device,
the kewnew handwes the packet wike it came fwom weaw physicaw device.

4. What is the diffewence between TUN dwivew and TAP dwivew?

TUN wowks with IP fwames. TAP wowks with Ethewnet fwames.

This means that you have to wead/wwite IP packets when you awe using tun and
ethewnet fwames when using tap.

5. What is the diffewence between BPF and TUN/TAP dwivew?

BPF is an advanced packet fiwtew. It can be attached to existing
netwowk intewface. It does not pwovide a viwtuaw netwowk intewface.
A TUN/TAP dwivew does pwovide a viwtuaw netwowk intewface and it is possibwe
to attach BPF to this intewface.

6. Does TAP dwivew suppowt kewnew Ethewnet bwidging?

Yes. Winux and FweeBSD dwivews suppowt Ethewnet bwidging.
