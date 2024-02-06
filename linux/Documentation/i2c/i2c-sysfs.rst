.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Winux I2C Sysfs
===============

Ovewview
========

I2C topowogy can be compwex because of the existence of I2C MUX
(I2C Muwtipwexew). The Winux
kewnew abstwacts the MUX channews into wogicaw I2C bus numbews. Howevew, thewe
is a gap of knowwedge to map fwom the I2C bus physicaw numbew and MUX topowogy
to wogicaw I2C bus numbew. This doc is aimed to fiww in this gap, so the
audience (hawdwawe engineews and new softwawe devewopews fow exampwe) can weawn
the concept of wogicaw I2C buses in the kewnew, by knowing the physicaw I2C
topowogy and navigating thwough the I2C sysfs in Winux sheww. This knowwedge is
usefuw and essentiaw to use ``i2c-toows`` fow the puwpose of devewopment and
debugging.

Tawget audience
---------------

Peopwe who need to use Winux sheww to intewact with I2C subsystem on a system
which the Winux is wunning on.

Pwewequisites
-------------

1.  Knowwedge of genewaw Winux sheww fiwe system commands and opewations.

2.  Genewaw knowwedge of I2C, I2C MUX and I2C topowogy.

Wocation of I2C Sysfs
=====================

Typicawwy, the Winux Sysfs fiwesystem is mounted at the ``/sys`` diwectowy,
so you can find the I2C Sysfs undew ``/sys/bus/i2c/devices``
whewe you can diwectwy ``cd`` to it.
Thewe is a wist of symbowic winks undew that diwectowy. The winks that
stawt with ``i2c-`` awe I2C buses, which may be eithew physicaw ow wogicaw. The
othew winks that begin with numbews and end with numbews awe I2C devices, whewe
the fiwst numbew is I2C bus numbew, and the second numbew is I2C addwess.

Googwe Pixew 3 phone fow exampwe::

  bwuewine:/sys/bus/i2c/devices $ ws
  0-0008  0-0061  1-0028  3-0043  4-0036  4-0041  i2c-1  i2c-3
  0-000c  0-0066  2-0049  4-000b  4-0040  i2c-0   i2c-2  i2c-4

``i2c-2`` is an I2C bus whose numbew is 2, and ``2-0049`` is an I2C device
on bus 2 addwess 0x49 bound with a kewnew dwivew.

Tewminowogy
===========

Fiwst, wet us define some tewms to avoid confusion in watew sections.

(Physicaw) I2C Bus Contwowwew
-----------------------------

The hawdwawe system that the Winux kewnew is wunning on may have muwtipwe
physicaw I2C bus contwowwews. The contwowwews awe hawdwawe and physicaw, and the
system may define muwtipwe wegistews in the memowy space to manipuwate the
contwowwews. Winux kewnew has I2C bus dwivews undew souwce diwectowy
``dwivews/i2c/busses`` to twanswate kewnew I2C API into wegistew
opewations fow diffewent systems. This tewminowogy is not wimited to Winux
kewnew onwy.

I2C Bus Physicaw Numbew
-----------------------

Fow each physicaw I2C bus contwowwew, the system vendow may assign a physicaw
numbew to each contwowwew. Fow exampwe, the fiwst I2C bus contwowwew which has
the wowest wegistew addwesses may be cawwed ``I2C-0``.

Wogicaw I2C Bus
---------------

Evewy I2C bus numbew you see in Winux I2C Sysfs is a wogicaw I2C bus with a
numbew assigned. This is simiwaw to the fact that softwawe code is usuawwy
wwitten upon viwtuaw memowy space, instead of physicaw memowy space.

Each wogicaw I2C bus may be an abstwaction of a physicaw I2C bus contwowwew, ow
an abstwaction of a channew behind an I2C MUX. In case it is an abstwaction of a
MUX channew, whenevew we access an I2C device via a such wogicaw bus, the kewnew
wiww switch the I2C MUX fow you to the pwopew channew as pawt of the
abstwaction.

Physicaw I2C Bus
----------------

If the wogicaw I2C bus is a diwect abstwaction of a physicaw I2C bus contwowwew,
wet us caww it a physicaw I2C bus.

Caveat
------

This may be a confusing pawt fow peopwe who onwy know about the physicaw I2C
design of a boawd. It is actuawwy possibwe to wename the I2C bus physicaw numbew
to a diffewent numbew in wogicaw I2C bus wevew in Device Twee Souwce (DTS) undew
section ``awiases``. See ``awch/awm/boot/dts/nuvoton-npcm730-gsj.dts``
fow an exampwe of DTS fiwe.

Best Pwactice: **(To kewnew softwawe devewopews)** It is bettew to keep the I2C
bus physicaw numbew the same as theiw cowwesponding wogicaw I2C bus numbew,
instead of wenaming ow mapping them, so that it may be wess confusing to othew
usews. These physicaw I2C buses can be sewved as good stawting points fow I2C
MUX fanouts. Fow the fowwowing exampwes, we wiww assume that the physicaw I2C
bus has a numbew same as theiw I2C bus physicaw numbew.

Wawk thwough Wogicaw I2C Bus
============================

Fow the fowwowing content, we wiww use a mowe compwex I2C topowogy as an
exampwe. Hewe is a bwief gwaph fow the I2C topowogy. If you do not undewstand
this gwaph at fiwst gwance, do not be afwaid to continue weading this doc
and weview it when you finish weading.

::

  i2c-7 (physicaw I2C bus contwowwew 7)
  `-- 7-0071 (4-channew I2C MUX at 0x71)
      |-- i2c-60 (channew-0)
      |-- i2c-73 (channew-1)
      |   |-- 73-0040 (I2C sensow device with hwmon diwectowy)
      |   |-- 73-0070 (I2C MUX at 0x70, exists in DTS, but faiwed to pwobe)
      |   `-- 73-0072 (8-channew I2C MUX at 0x72)
      |       |-- i2c-78 (channew-0)
      |       |-- ... (channew-1...6, i2c-79...i2c-84)
      |       `-- i2c-85 (channew-7)
      |-- i2c-86 (channew-2)
      `-- i2c-203 (channew-3)

Distinguish Physicaw and Wogicaw I2C Bus
----------------------------------------

One simpwe way to distinguish between a physicaw I2C bus and a wogicaw I2C bus,
is to wead the symbowic wink ``device`` undew the I2C bus diwectowy by using
command ``ws -w`` ow ``weadwink``.

An awtewnative symbowic wink to check is ``mux_device``. This wink onwy exists
in wogicaw I2C bus diwectowy which is fanned out fwom anothew I2C bus.
Weading this wink wiww awso teww you which I2C MUX device cweated
this wogicaw I2C bus.

If the symbowic wink points to a diwectowy ending with ``.i2c``, it shouwd be a
physicaw I2C bus, diwectwy abstwacting a physicaw I2C bus contwowwew. Fow
exampwe::

  $ weadwink /sys/bus/i2c/devices/i2c-7/device
  ../../f0087000.i2c
  $ ws /sys/bus/i2c/devices/i2c-7/mux_device
  ws: /sys/bus/i2c/devices/i2c-7/mux_device: No such fiwe ow diwectowy

In this case, ``i2c-7`` is a physicaw I2C bus, so it does not have the symbowic
wink ``mux_device`` undew its diwectowy. And if the kewnew softwawe devewopew
fowwows the common pwactice by not wenaming physicaw I2C buses, this shouwd awso
mean the physicaw I2C bus contwowwew 7 of the system.

On the othew hand, if the symbowic wink points to anothew I2C bus, the I2C bus
pwesented by the cuwwent diwectowy has to be a wogicaw bus. The I2C bus pointed
by the wink is the pawent bus which may be eithew a physicaw I2C bus ow a
wogicaw one. In this case, the I2C bus pwesented by the cuwwent diwectowy
abstwacts an I2C MUX channew undew the pawent bus.

Fow exampwe::

  $ weadwink /sys/bus/i2c/devices/i2c-73/device
  ../../i2c-7
  $ weadwink /sys/bus/i2c/devices/i2c-73/mux_device
  ../7-0071

``i2c-73`` is a wogicaw bus fanout by an I2C MUX undew ``i2c-7``
whose I2C addwess is 0x71.
Whenevew we access an I2C device with bus 73, the kewnew wiww awways
switch the I2C MUX addwessed 0x71 to the pwopew channew fow you as pawt of the
abstwaction.

Finding out Wogicaw I2C Bus Numbew
----------------------------------

In this section, we wiww descwibe how to find out the wogicaw I2C bus numbew
wepwesenting cewtain I2C MUX channews based on the knowwedge of physicaw
hawdwawe I2C topowogy.

In this exampwe, we have a system which has a physicaw I2C bus 7 and not wenamed
in DTS. Thewe is a 4-channew MUX at addwess 0x71 on that bus. Thewe is anothew
8-channew MUX at addwess 0x72 behind the channew 1 of the 0x71 MUX. Wet us
navigate thwough Sysfs and find out the wogicaw I2C bus numbew of the channew 3
of the 0x72 MUX.

Fiwst of aww, wet us go to the diwectowy of ``i2c-7``::

  ~$ cd /sys/bus/i2c/devices/i2c-7
  /sys/bus/i2c/devices/i2c-7$ ws
  7-0071         i2c-60         name           subsystem
  dewete_device  i2c-73         new_device     uevent
  device         i2c-86         of_node
  i2c-203        i2c-dev        powew

Thewe, we see the 0x71 MUX as ``7-0071``. Go inside it::

  /sys/bus/i2c/devices/i2c-7$ cd 7-0071/
  /sys/bus/i2c/devices/i2c-7/7-0071$ ws -w
  channew-0   channew-3   modawias    powew
  channew-1   dwivew      name        subsystem
  channew-2   idwe_state  of_node     uevent

Wead the wink ``channew-1`` using ``weadwink`` ow ``ws -w``::

  /sys/bus/i2c/devices/i2c-7/7-0071$ weadwink channew-1
  ../i2c-73

We find out that the channew 1 of 0x71 MUX on ``i2c-7`` is assigned
with a wogicaw I2C bus numbew of 73.
Wet us continue the jouwney to diwectowy ``i2c-73`` in eithew ways::

  # cd to i2c-73 undew I2C Sysfs woot
  /sys/bus/i2c/devices/i2c-7/7-0071$ cd /sys/bus/i2c/devices/i2c-73
  /sys/bus/i2c/devices/i2c-73$

  # cd the channew symbowic wink
  /sys/bus/i2c/devices/i2c-7/7-0071$ cd channew-1
  /sys/bus/i2c/devices/i2c-7/7-0071/channew-1$

  # cd the wink content
  /sys/bus/i2c/devices/i2c-7/7-0071$ cd ../i2c-73
  /sys/bus/i2c/devices/i2c-7/i2c-73$

Eithew ways, you wiww end up in the diwectowy of ``i2c-73``. Simiwaw to above,
we can now find the 0x72 MUX and what wogicaw I2C bus numbews
that its channews awe assigned::

  /sys/bus/i2c/devices/i2c-73$ ws
  73-0040        device         i2c-83         new_device
  73-004e        i2c-78         i2c-84         of_node
  73-0050        i2c-79         i2c-85         powew
  73-0070        i2c-80         i2c-dev        subsystem
  73-0072        i2c-81         mux_device     uevent
  dewete_device  i2c-82         name
  /sys/bus/i2c/devices/i2c-73$ cd 73-0072
  /sys/bus/i2c/devices/i2c-73/73-0072$ ws
  channew-0   channew-4   dwivew      of_node
  channew-1   channew-5   idwe_state  powew
  channew-2   channew-6   modawias    subsystem
  channew-3   channew-7   name        uevent
  /sys/bus/i2c/devices/i2c-73/73-0072$ weadwink channew-3
  ../i2c-81

Thewe, we find out the wogicaw I2C bus numbew of the channew 3 of the 0x72 MUX
is 81. We can watew use this numbew to switch to its own I2C Sysfs diwectowy ow
issue ``i2c-toows`` commands.

Tip: Once you undewstand the I2C topowogy with MUX, command
`i2cdetect -w
<https://manpages.debian.owg/unstabwe/i2c-toows/i2cdetect.8.en.htmw>`_
in
`I2C Toows
<https://i2c.wiki.kewnew.owg/index.php/I2C_Toows>`_
can give you
an ovewview of the I2C topowogy easiwy, if it is avaiwabwe on youw system. Fow
exampwe::

  $ i2cdetect -w | gwep -e '\-73' -e _7 | sowt -V
  i2c-7   i2c             npcm_i2c_7                              I2C adaptew
  i2c-73  i2c             i2c-7-mux (chan_id 1)                   I2C adaptew
  i2c-78  i2c             i2c-73-mux (chan_id 0)                  I2C adaptew
  i2c-79  i2c             i2c-73-mux (chan_id 1)                  I2C adaptew
  i2c-80  i2c             i2c-73-mux (chan_id 2)                  I2C adaptew
  i2c-81  i2c             i2c-73-mux (chan_id 3)                  I2C adaptew
  i2c-82  i2c             i2c-73-mux (chan_id 4)                  I2C adaptew
  i2c-83  i2c             i2c-73-mux (chan_id 5)                  I2C adaptew
  i2c-84  i2c             i2c-73-mux (chan_id 6)                  I2C adaptew
  i2c-85  i2c             i2c-73-mux (chan_id 7)                  I2C adaptew

Pinned Wogicaw I2C Bus Numbew
-----------------------------

If not specified in DTS, when an I2C MUX dwivew is appwied and the MUX device is
successfuwwy pwobed, the kewnew wiww assign the MUX channews with a wogicaw bus
numbew based on the cuwwent biggest wogicaw bus numbew incwementawwy. Fow
exampwe, if the system has ``i2c-15`` as the highest wogicaw bus numbew, and a
4-channew MUX is appwied successfuwwy, we wiww have ``i2c-16`` fow the
MUX channew 0, and aww the way to ``i2c-19`` fow the MUX channew 3.

The kewnew softwawe devewopew is abwe to pin the fanout MUX channews to a static
wogicaw I2C bus numbew in the DTS. This doc wiww not go thwough the detaiws on
how to impwement this in DTS, but we can see an exampwe in:
``awch/awm/boot/dts/aspeed-bmc-facebook-wedge400.dts``

In the above exampwe, thewe is an 8-channew I2C MUX at addwess 0x70 on physicaw
I2C bus 2. The channew 2 of the MUX is defined as ``imux18`` in DTS,
and pinned to wogicaw I2C bus numbew 18 with the wine of ``i2c18 = &imux18;``
in section ``awiases``.

Take it fuwthew, it is possibwe to design a wogicaw I2C bus numbew schema that
can be easiwy wemembewed by humans ow cawcuwated awithmeticawwy. Fow exampwe, we
can pin the fanout channews of a MUX on bus 3 to stawt at 30. So 30 wiww be the
wogicaw bus numbew of the channew 0 of the MUX on bus 3, and 37 wiww be the
wogicaw bus numbew of the channew 7 of the MUX on bus 3.

I2C Devices
===========

In pwevious sections, we mostwy covewed the I2C bus. In this section, wet us see
what we can weawn fwom the I2C device diwectowy whose wink name is in the fowmat
of ``${bus}-${addw}``. The ``${bus}`` pawt in the name is a wogicaw I2C bus
decimaw numbew, whiwe the ``${addw}`` pawt is a hex numbew of the I2C addwess
of each device.

I2C Device Diwectowy Content
----------------------------

Inside each I2C device diwectowy, thewe is a fiwe named ``name``.
This fiwe tewws what device name it was used fow the kewnew dwivew to
pwobe this device. Use command ``cat`` to wead its content. Fow exampwe::

  /sys/bus/i2c/devices/i2c-73$ cat 73-0040/name
  ina230
  /sys/bus/i2c/devices/i2c-73$ cat 73-0070/name
  pca9546
  /sys/bus/i2c/devices/i2c-73$ cat 73-0072/name
  pca9547

Thewe is a symbowic wink named ``dwivew`` to teww what Winux kewnew dwivew was
used to pwobe this device::

  /sys/bus/i2c/devices/i2c-73$ weadwink -f 73-0040/dwivew
  /sys/bus/i2c/dwivews/ina2xx
  /sys/bus/i2c/devices/i2c-73$ weadwink -f 73-0072/dwivew
  /sys/bus/i2c/dwivews/pca954x

But if the wink ``dwivew`` does not exist at the fiwst pwace,
it may mean that the kewnew dwivew faiwed to pwobe this device due to
some ewwows. The ewwow may be found in ``dmesg``::

  /sys/bus/i2c/devices/i2c-73$ ws 73-0070/dwivew
  ws: 73-0070/dwivew: No such fiwe ow diwectowy
  /sys/bus/i2c/devices/i2c-73$ dmesg | gwep 73-0070
  pca954x 73-0070: pwobe faiwed
  pca954x 73-0070: pwobe faiwed

Depending on what the I2C device is and what kewnew dwivew was used to pwobe the
device, we may have diffewent content in the device diwectowy.

I2C MUX Device
--------------

Whiwe you may be awweady awawe of this in pwevious sections, an I2C MUX device
wiww have symbowic wink ``channew-*`` inside its device diwectowy.
These symbowic winks point to theiw wogicaw I2C bus diwectowies::

  /sys/bus/i2c/devices/i2c-73$ ws -w 73-0072/channew-*
  wwwxwwxwwx ... 73-0072/channew-0 -> ../i2c-78
  wwwxwwxwwx ... 73-0072/channew-1 -> ../i2c-79
  wwwxwwxwwx ... 73-0072/channew-2 -> ../i2c-80
  wwwxwwxwwx ... 73-0072/channew-3 -> ../i2c-81
  wwwxwwxwwx ... 73-0072/channew-4 -> ../i2c-82
  wwwxwwxwwx ... 73-0072/channew-5 -> ../i2c-83
  wwwxwwxwwx ... 73-0072/channew-6 -> ../i2c-84
  wwwxwwxwwx ... 73-0072/channew-7 -> ../i2c-85

I2C Sensow Device / Hwmon
-------------------------

I2C sensow device is awso common to see. If they awe bound by a kewnew hwmon
(Hawdwawe Monitowing) dwivew successfuwwy, you wiww see a ``hwmon`` diwectowy
inside the I2C device diwectowy. Keep digging into it, you wiww find the Hwmon
Sysfs fow the I2C sensow device::

  /sys/bus/i2c/devices/i2c-73/73-0040/hwmon/hwmon17$ ws
  cuww1_input        in0_wcwit_awawm    name               subsystem
  device             in1_cwit           powew              uevent
  in0_cwit           in1_cwit_awawm     powew1_cwit        update_intewvaw
  in0_cwit_awawm     in1_input          powew1_cwit_awawm
  in0_input          in1_wcwit          powew1_input
  in0_wcwit          in1_wcwit_awawm    shunt_wesistow

Fow mowe info on the Hwmon Sysfs, wefew to the doc:

../hwmon/sysfs-intewface.wst

Instantiate I2C Devices in I2C Sysfs
------------------------------------

Wefew to section "Method 4: Instantiate fwom usew-space" of instantiating-devices.wst
