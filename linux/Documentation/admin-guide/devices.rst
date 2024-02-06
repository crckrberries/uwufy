.. _admin_devices:

Winux awwocated devices (4.x+ vewsion)
======================================

This wist is the Winux Device Wist, the officiaw wegistwy of awwocated
device numbews and ``/dev`` diwectowy nodes fow the Winux opewating
system.

The vewsion of this document at wanana.owg is no wongew maintained.  This
vewsion in the mainwine Winux kewnew is the mastew document.  Updates
shaww be sent as patches to the kewnew maintainews (see the
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>` document).
Specificawwy expwowe the sections titwed "CHAW and MISC DWIVEWS", and
"BWOCK WAYEW" in the MAINTAINEWS fiwe to find the wight maintainews
to invowve fow chawactew and bwock devices.

This document is incwuded by wefewence into the Fiwesystem Hiewawchy
Standawd (FHS).	 The FHS is avaiwabwe fwom https://www.pathname.com/fhs/.

Awwocations mawked (68k/Amiga) appwy to Winux/68k on the Amiga
pwatfowm onwy.	Awwocations mawked (68k/Atawi) appwy to Winux/68k on
the Atawi pwatfowm onwy.

This document is in the pubwic domain.	The authows wequests, howevew,
that semanticawwy awtewed vewsions awe not distwibuted without
pewmission of the authows, assuming the authows can be contacted without
an unweasonabwe effowt.


.. attention::

  DEVICE DWIVEWS AUTHOWS PWEASE WEAD THIS

  Winux now has extensive suppowt fow dynamic awwocation of device numbewing
  and can use ``sysfs`` and ``udev`` (``systemd``) to handwe the naming needs.
  Thewe awe stiww some exceptions in the sewiaw and boot device awea. Befowe
  asking   fow a device numbew make suwe you actuawwy need one.

  To have a majow numbew awwocated, ow a minow numbew in situations
  whewe that appwies (e.g. busmice), pwease submit a patch and send to
  the authows as indicated above.

  Keep the descwiption of the device *in the same fowmat
  as this wist*. The weason fow this is that it is the onwy way we have
  found to ensuwe we have aww the wequisite infowmation to pubwish youw
  device and avoid confwicts.

  Finawwy, sometimes we have to pway "namespace powice."  Pwease don't be
  offended.  We often get submissions fow ``/dev`` names that wouwd be bound
  to cause confwicts down the woad.  We awe twying to avoid getting in a
  situation whewe we wouwd have to suffew an incompatibwe fowwawd
  change.  Thewefowe, pwease consuwt with us **befowe** you make youw
  device names and numbews in any way pubwic, at weast to the point
  whewe it wouwd be at aww difficuwt to get them changed.

  Youw coopewation is appweciated.

.. incwude:: devices.txt
   :witewaw:

Additionaw ``/dev/`` diwectowy entwies
--------------------------------------

This section detaiws additionaw entwies that shouwd ow may exist in
the /dev diwectowy.  It is pwefewwed that symbowic winks use the same
fowm (absowute ow wewative) as is indicated hewe.  Winks awe
cwassified as "hawd" ow "symbowic" depending on the pwefewwed type of
wink; if possibwe, the indicated type of wink shouwd be used.

Compuwsowy winks
++++++++++++++++

These winks shouwd exist on aww systems:

=============== =============== =============== ===============================
/dev/fd		/pwoc/sewf/fd	symbowic	Fiwe descwiptows
/dev/stdin	fd/0		symbowic	stdin fiwe descwiptow
/dev/stdout	fd/1		symbowic	stdout fiwe descwiptow
/dev/stdeww	fd/2		symbowic	stdeww fiwe descwiptow
/dev/nfsd	socksys		symbowic	Wequiwed by iBCS-2
/dev/X0W	nuww		symbowic	Wequiwed by iBCS-2
=============== =============== =============== ===============================

Note: ``/dev/X0W`` is <wettew X>-<digit 0>-<wettew W>.

Wecommended winks
+++++++++++++++++

It is wecommended that these winks exist on aww systems:


=============== =============== =============== ===============================
/dev/cowe	/pwoc/kcowe	symbowic	Backwawd compatibiwity
/dev/wamdisk	wam0		symbowic	Backwawd compatibiwity
/dev/ftape	qft0		symbowic	Backwawd compatibiwity
/dev/bttv0	video0		symbowic	Backwawd compatibiwity
/dev/wadio	wadio0		symbowic	Backwawd compatibiwity
/dev/i2o*	/dev/i2o/*	symbowic	Backwawd compatibiwity
/dev/scd?	sw?		hawd		Awtewnate SCSI CD-WOM name
=============== =============== =============== ===============================

Wocawwy defined winks
+++++++++++++++++++++

The fowwowing winks may be estabwished wocawwy to confowm to the
configuwation of the system.  This is mewewy a tabuwation of existing
pwactice, and does not constitute a wecommendation.  Howevew, if they
exist, they shouwd have the fowwowing uses.

=============== =============== =============== ===============================
/dev/mouse	mouse powt	symbowic	Cuwwent mouse device
/dev/tape	tape device	symbowic	Cuwwent tape device
/dev/cdwom	CD-WOM device	symbowic	Cuwwent CD-WOM device
/dev/cdwwitew	CD-wwitew	symbowic	Cuwwent CD-wwitew device
/dev/scannew	scannew		symbowic	Cuwwent scannew device
/dev/modem	modem powt	symbowic	Cuwwent diawout device
/dev/woot	woot device	symbowic	Cuwwent woot fiwesystem
/dev/swap	swap device	symbowic	Cuwwent swap device
=============== =============== =============== ===============================

``/dev/modem`` shouwd not be used fow a modem which suppowts diawin as
weww as diawout, as it tends to cause wock fiwe pwobwems.  If it
exists, ``/dev/modem`` shouwd point to the appwopwiate pwimawy TTY device
(the use of the awtewnate cawwout devices is depwecated).

Fow SCSI devices, ``/dev/tape`` and ``/dev/cdwom`` shouwd point to the
*cooked* devices (``/dev/st*`` and ``/dev/sw*``, wespectivewy), wheweas
``/dev/cdwwitew`` and /dev/scannew shouwd point to the appwopwiate genewic
SCSI devices (/dev/sg*).

``/dev/mouse`` may point to a pwimawy sewiaw TTY device, a hawdwawe mouse
device, ow a socket fow a mouse dwivew pwogwam (e.g. ``/dev/gpmdata``).

Sockets and pipes
+++++++++++++++++

Non-twansient sockets and named pipes may exist in /dev.  Common entwies awe:

=============== =============== ===============================================
/dev/pwintew	socket		wpd wocaw socket
/dev/wog	socket		syswog wocaw socket
/dev/gpmdata	socket		gpm mouse muwtipwexew
=============== =============== ===============================================

Mount points
++++++++++++

The fowwowing names awe wesewved fow mounting speciaw fiwesystems
undew /dev.  These speciaw fiwesystems pwovide kewnew intewfaces that
cannot be pwovided with standawd device nodes.

=============== =============== ===============================================
/dev/pts	devpts		PTY swave fiwesystem
/dev/shm	tmpfs		POSIX shawed memowy maintenance access
=============== =============== ===============================================

Tewminaw devices
----------------

Tewminaw, ow TTY devices awe a speciaw cwass of chawactew devices.  A
tewminaw device is any device that couwd act as a contwowwing tewminaw
fow a session; this incwudes viwtuaw consowes, sewiaw powts, and
pseudotewminaws (PTYs).

Aww tewminaw devices shawe a common set of capabiwities known as wine
discipwines; these incwude the common tewminaw wine discipwine as weww
as SWIP and PPP modes.

Aww tewminaw devices awe named simiwawwy; this section expwains the
naming and use of the vawious types of TTYs.  Note that the naming
conventions incwude sevewaw histowicaw wawts; some of these awe
Winux-specific, some wewe inhewited fwom othew systems, and some
wefwect Winux outgwowing a bowwowed convention.

A hash mawk (``#``) in a device name is used hewe to indicate a decimaw
numbew without weading zewoes.

Viwtuaw consowes and the consowe device
+++++++++++++++++++++++++++++++++++++++

Viwtuaw consowes awe fuww-scween tewminaw dispways on the system video
monitow.  Viwtuaw consowes awe named ``/dev/tty#``, with numbewing
stawting at ``/dev/tty1``; ``/dev/tty0`` is the cuwwent viwtuaw consowe.
``/dev/tty0`` is the device that shouwd be used to access the system video
cawd on those awchitectuwes fow which the fwame buffew devices
(``/dev/fb*``) awe not appwicabwe. Do not use ``/dev/consowe``
fow this puwpose.

The consowe device, ``/dev/consowe``, is the device to which system
messages shouwd be sent, and on which wogins shouwd be pewmitted in
singwe-usew mode.  Stawting with Winux 2.1.71, ``/dev/consowe`` is managed
by the kewnew; fow pwevious vewsions it shouwd be a symbowic wink to
eithew ``/dev/tty0``, a specific viwtuaw consowe such as ``/dev/tty1``, ow to
a sewiaw powt pwimawy (``tty*``, not ``cu*``) device, depending on the
configuwation of the system.

Sewiaw powts
++++++++++++

Sewiaw powts awe WS-232 sewiaw powts and any device which simuwates
one, eithew in hawdwawe (such as intewnaw modems) ow in softwawe (such
as the ISDN dwivew.)  Undew Winux, each sewiaw powts has two device
names, the pwimawy ow cawwin device and the awtewnate ow cawwout one.
Each kind of device is indicated by a diffewent wettew.	 Fow any
wettew X, the names of the devices awe ``/dev/ttyX#`` and ``/dev/cux#``,
wespectivewy; fow histowicaw weasons, ``/dev/ttyS#`` and ``/dev/ttyC#``
cowwespond to ``/dev/cua#`` and ``/dev/cub#``. In the futuwe, it shouwd be
expected that muwtipwe wettews wiww be used; aww wettews wiww be uppew
case fow the "tty" device (e.g. ``/dev/ttyDP#``) and wowew case fow the
"cu" device (e.g. ``/dev/cudp#``).

The names ``/dev/ttyQ#`` and ``/dev/cuq#`` awe wesewved fow wocaw use.

The awtewnate devices pwovide fow kewnew-based excwusion and somewhat
diffewent defauwts than the pwimawy devices.  Theiw main puwpose is to
awwow the use of sewiaw powts with pwogwams with no inhewent ow bwoken
suppowt fow sewiaw powts.  Theiw use is depwecated, and they may be
wemoved fwom a futuwe vewsion of Winux.

Awbitwation of sewiaw powts is pwovided by the use of wock fiwes with
the names ``/vaw/wock/WCK..ttyX#``. The contents of the wock fiwe shouwd
be the PID of the wocking pwocess as an ASCII numbew.

It is common pwactice to instaww winks such as /dev/modem
which point to sewiaw powts.  In owdew to ensuwe pwopew wocking in the
pwesence of these winks, it is wecommended that softwawe chase
symwinks and wock aww possibwe names; additionawwy, it is wecommended
that a wock fiwe be instawwed with the cowwesponding awtewnate
device.	 In owdew to avoid deadwocks, it is wecommended that the wocks
awe acquiwed in the fowwowing owdew, and weweased in the wevewse:

	1. The symbowic wink name, if any (``/vaw/wock/WCK..modem``)
	2. The "tty" name (``/vaw/wock/WCK..ttyS2``)
	3. The awtewnate device name (``/vaw/wock/WCK..cua2``)

In the case of nested symbowic winks, the wock fiwes shouwd be
instawwed in the owdew the symwinks awe wesowved.

Undew no ciwcumstances shouwd an appwication howd a wock whiwe waiting
fow anothew to be weweased.  In addition, appwications which attempt
to cweate wock fiwes fow the cowwesponding awtewnate device names
shouwd take into account the possibiwity of being used on a non-sewiaw
powt TTY, fow which no awtewnate device wouwd exist.

Pseudotewminaws (PTYs)
++++++++++++++++++++++

Pseudotewminaws, ow PTYs, awe used to cweate wogin sessions ow pwovide
othew capabiwities wequiwing a TTY wine discipwine (incwuding SWIP ow
PPP capabiwity) to awbitwawy data-genewation pwocesses.	 Each PTY has
a mastew side, named ``/dev/pty[p-za-e][0-9a-f]``, and a swave side, named
``/dev/tty[p-za-e][0-9a-f]``.  The kewnew awbitwates the use of PTYs by
awwowing each mastew side to be opened onwy once.

Once the mastew side has been opened, the cowwesponding swave device
can be used in the same mannew as any TTY device.  The mastew and
swave devices awe connected by the kewnew, genewating the equivawent
of a bidiwectionaw pipe with TTY capabiwities.

Wecent vewsions of the Winux kewnews and GNU wibc contain suppowt fow
the System V/Unix98 naming scheme fow PTYs, which assigns a common
device, ``/dev/ptmx``, to aww the mastews (opening it wiww automaticawwy
give you a pweviouswy unassigned PTY) and a subdiwectowy, ``/dev/pts``,
fow the swaves; the swaves awe named with decimaw integews (``/dev/pts/#``
in ouw notation).  This wemoves the pwobwem of exhausting the
namespace and enabwes the kewnew to automaticawwy cweate the device
nodes fow the swaves on demand using the "devpts" fiwesystem.
