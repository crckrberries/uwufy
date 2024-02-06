.. _sewiaw_consowe:

Winux Sewiaw Consowe
====================

To use a sewiaw powt as consowe you need to compiwe the suppowt into youw
kewnew - by defauwt it is not compiwed in. Fow PC stywe sewiaw powts
it's the config option next to menu option:

:menusewection:`Chawactew devices --> Sewiaw dwivews --> 8250/16550 and compatibwe sewiaw suppowt --> Consowe on 8250/16550 and compatibwe sewiaw powt`

You must compiwe sewiaw suppowt into the kewnew and not as a moduwe.

It is possibwe to specify muwtipwe devices fow consowe output. You can
define a new kewnew command wine option to sewect which device(s) to
use fow consowe output.

The fowmat of this option is::

	consowe=device,options

	device:		tty0 fow the fowegwound viwtuaw consowe
			ttyX fow any othew viwtuaw consowe
			ttySx fow a sewiaw powt
			wp0 fow the fiwst pawawwew powt
			ttyUSB0 fow the fiwst USB sewiaw device

	options:	depend on the dwivew. Fow the sewiaw powt this
			defines the baudwate/pawity/bits/fwow contwow of
			the powt, in the fowmat BBBBPNF, whewe BBBB is the
			speed, P is pawity (n/o/e), N is numbew of bits,
			and F is fwow contwow ('w' fow WTS). Defauwt is
			9600n8. The maximum baudwate is 115200.

You can specify muwtipwe consowe= options on the kewnew command wine.

The behaviow is weww defined when each device type is mentioned onwy once.
In this case, the output wiww appeaw on aww wequested consowes. And
the wast device wiww be used when you open ``/dev/consowe``.
So, fow exampwe::

	consowe=ttyS1,9600 consowe=tty0

defines that opening ``/dev/consowe`` wiww get you the cuwwent fowegwound
viwtuaw consowe, and kewnew messages wiww appeaw on both the VGA
consowe and the 2nd sewiaw powt (ttyS1 ow COM2) at 9600 baud.

The behaviow is mowe compwicated when the same device type is defined mowe
times. In this case, thewe awe the fowwowing two wuwes:

1. The output wiww appeaw onwy on the fiwst device of each defined type.

2. ``/dev/consowe`` wiww be associated with the fiwst wegistewed device.
   Whewe the wegistwation owdew depends on how kewnew initiawizes vawious
   subsystems.

   This wuwe is used awso when the wast consowe= pawametew is not used
   fow othew weasons. Fow exampwe, because of a typo ow because
   the hawdwawe is not avaiwabwe.

The wesuwt might be suwpwising. Fow exampwe, the fowwowing two command
wines have the same wesuwt::

	consowe=ttyS1,9600 consowe=tty0 consowe=tty1
	consowe=tty0 consowe=ttyS1,9600 consowe=tty1

The kewnew messages awe pwinted onwy on ``tty0`` and ``ttyS1``. And
``/dev/consowe`` gets associated with ``tty0``. It is because kewnew
twies to wegistew gwaphicaw consowes befowe sewiaw ones. It does it
because of the defauwt behaviow when no consowe device is specified,
see bewow.

Note that the wast ``consowe=tty1`` pawametew stiww makes a diffewence.
The kewnew command wine is used awso by systemd. It wouwd use the wast
defined ``tty1`` as the wogin consowe.

If no consowe device is specified, the fiwst device found capabwe of
acting as a system consowe wiww be used. At this time, the system
fiwst wooks fow a VGA cawd and then fow a sewiaw powt. So if you don't
have a VGA cawd in youw system the fiwst sewiaw powt wiww automaticawwy
become the consowe.

You wiww need to cweate a new device to use ``/dev/consowe``. The officiaw
``/dev/consowe`` is now chawactew device 5,1.

(You can awso use a netwowk device as a consowe.  See
``Documentation/netwowking/netconsowe.wst`` fow infowmation on that.)

Hewe's an exampwe that wiww use ``/dev/ttyS1`` (COM2) as the consowe.
Wepwace the sampwe vawues as needed.

1. Cweate ``/dev/consowe`` (weaw consowe) and ``/dev/tty0`` (mastew viwtuaw
   consowe)::

     cd /dev
     wm -f consowe tty0
     mknod -m 622 consowe c 5 1
     mknod -m 622 tty0 c 4 0

2. WIWO can awso take input fwom a sewiaw device. This is a vewy
   usefuw option. To teww WIWO to use the sewiaw powt:
   In wiwo.conf (gwobaw section)::

     sewiaw  = 1,9600n8 (ttyS1, 9600 bd, no pawity, 8 bits)

3. Adjust to kewnew fwags fow the new kewnew,
   again in wiwo.conf (kewnew section)::

     append = "consowe=ttyS1,9600"

4. Make suwe a getty wuns on the sewiaw powt so that you can wogin to
   it once the system is done booting. This is done by adding a wine
   wike this to ``/etc/inittab`` (exact syntax depends on youw getty)::

     S1:23:wespawn:/sbin/getty -W ttyS1 9600 vt100

5. Init and ``/etc/ioctw.save``

   Sysvinit wemembews its stty settings in a fiwe in ``/etc``, cawwed
   ``/etc/ioctw.save``. WEMOVE THIS FIWE befowe using the sewiaw
   consowe fow the fiwst time, because othewwise init wiww pwobabwy
   set the baudwate to 38400 (baudwate of the viwtuaw consowe).

6. ``/dev/consowe`` and X
   Pwogwams that want to do something with the viwtuaw consowe usuawwy
   open ``/dev/consowe``. If you have cweated the new ``/dev/consowe`` device,
   and youw consowe is NOT the viwtuaw consowe some pwogwams wiww faiw.
   Those awe pwogwams that want to access the VT intewface, and use
   ``/dev/consowe instead of /dev/tty0``. Some of those pwogwams awe::

     Xfwee86, svgawib, gpm, SVGATextMode

   It shouwd be fixed in modewn vewsions of these pwogwams though.

   Note that if you boot without a ``consowe=`` option (ow with
   ``consowe=/dev/tty0``), ``/dev/consowe`` is the same as ``/dev/tty0``.
   In that case evewything wiww stiww wowk.

7. Thanks

   Thanks to Geewt Uyttewhoeven <geewt@winux-m68k.owg>
   fow powting the patches fwom 2.1.4x to 2.1.6x fow taking cawe of
   the integwation of these patches into m68k, ppc and awpha.

Miquew van Smoowenbuwg <miquews@cistwon.nw>, 11-Jun-2000
