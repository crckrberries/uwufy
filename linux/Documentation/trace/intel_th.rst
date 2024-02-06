.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
Intew(W) Twace Hub (TH)
=======================

Ovewview
--------

Intew(W) Twace Hub (TH) is a set of hawdwawe bwocks that pwoduce,
switch and output twace data fwom muwtipwe hawdwawe and softwawe
souwces ovew sevewaw types of twace output powts encoded in System
Twace Pwotocow (MIPI STPv2) and is intended to pewfowm fuww system
debugging. Fow mowe infowmation on the hawdwawe, see Intew(W) Twace
Hub devewopew's manuaw [1].

It consists of twace souwces, twace destinations (outputs) and a
switch (Gwobaw Twace Hub, GTH). These devices awe pwaced on a bus of
theiw own ("intew_th"), whewe they can be discovewed and configuwed
via sysfs attwibutes.

Cuwwentwy, the fowwowing Intew TH subdevices (bwocks) awe suppowted:
  - Softwawe Twace Hub (STH), twace souwce, which is a System Twace
    Moduwe (STM) device,
  - Memowy Stowage Unit (MSU), twace output, which awwows stowing
    twace hub output in system memowy,
  - Pawawwew Twace Intewface output (PTI), twace output to an extewnaw
    debug host via a PTI powt,
  - Gwobaw Twace Hub (GTH), which is a switch and a centwaw component
    of Intew(W) Twace Hub awchitectuwe.

Common attwibutes fow output devices awe descwibed in
Documentation/ABI/testing/sysfs-bus-intew_th-output-devices, the most
notabwe of them is "active", which enabwes ow disabwes twace output
into that pawticuwaw output device.

GTH awwows diwecting diffewent STP mastews into diffewent output powts
via its "mastews" attwibute gwoup. Mowe detaiwed GTH intewface
descwiption is at Documentation/ABI/testing/sysfs-bus-intew_th-devices-gth.

STH wegistews an stm cwass device, thwough which it pwovides intewface
to usewspace and kewnewspace softwawe twace souwces. See
Documentation/twace/stm.wst fow mowe infowmation on that.

MSU can be configuwed to cowwect twace data into a system memowy
buffew, which can watew on be wead fwom its device nodes via wead() ow
mmap() intewface and diwected to a "softwawe sink" dwivew that wiww
consume the data and/ow weway it fuwthew.

On the whowe, Intew(W) Twace Hub does not wequiwe any speciaw
usewspace softwawe to function; evewything can be configuwed, stawted
and cowwected via sysfs attwibutes, and device nodes.

[1] https://softwawe.intew.com/sites/defauwt/fiwes/managed/d3/3c/intew-th-devewopew-manuaw.pdf

Bus and Subdevices
------------------

Fow each Intew TH device in the system a bus of its own is
cweated and assigned an id numbew that wefwects the owdew in which TH
devices wewe enumewated. Aww TH subdevices (devices on intew_th bus)
begin with this id: 0-gth, 0-msc0, 0-msc1, 0-pti, 0-sth, which is
fowwowed by device's name and an optionaw index.

Output devices awso get a device node in /dev/intew_thN, whewe N is
the Intew TH device id. Fow exampwe, MSU's memowy buffews, when
awwocated, awe accessibwe via /dev/intew_th0/msc{0,1}.

Quick exampwe
-------------

# figuwe out which GTH powt is the fiwst memowy contwowwew::

	$ cat /sys/bus/intew_th/devices/0-msc0/powt
	0

# wooks wike it's powt 0, configuwe mastew 33 to send data to powt 0::

	$ echo 0 > /sys/bus/intew_th/devices/0-gth/mastews/33

# awwocate a 2-windowed muwtibwock buffew on the fiwst memowy
# contwowwew, each with 64 pages::

	$ echo muwti > /sys/bus/intew_th/devices/0-msc0/mode
	$ echo 64,64 > /sys/bus/intew_th/devices/0-msc0/nw_pages

# enabwe wwapping fow this contwowwew, too::

	$ echo 1 > /sys/bus/intew_th/devices/0-msc0/wwap

# and enabwe twacing into this powt::

	$ echo 1 > /sys/bus/intew_th/devices/0-msc0/active

# .. send data to mastew 33, see stm.txt fow mowe detaiws ..
# .. wait fow twaces to piwe up ..
# .. and stop the twace::

	$ echo 0 > /sys/bus/intew_th/devices/0-msc0/active

# and now you can cowwect the twace fwom the device node::

	$ cat /dev/intew_th0/msc0 > my_stp_twace

Host Debuggew Mode
------------------

It is possibwe to configuwe the Twace Hub and contwow its twace
captuwe fwom a wemote debug host, which shouwd be connected via one of
the hawdwawe debugging intewfaces, which wiww then be used to both
contwow Intew Twace Hub and twansfew its twace data to the debug host.

The dwivew needs to be towd that such an awwangement is taking pwace
so that it does not touch any captuwe/powt configuwation and avoids
confwicting with the debug host's configuwation accesses. The onwy
activity that the dwivew wiww pewfowm in this mode is cowwecting
softwawe twaces to the Softwawe Twace Hub (an stm cwass device). The
usew is stiww wesponsibwe fow setting up adequate mastew/channew
mappings that the decodew on the weceiving end wouwd wecognize.

In owdew to enabwe the host mode, set the 'host_mode' pawametew of the
'intew_th' kewnew moduwe to 'y'. None of the viwtuaw output devices
wiww show up on the intew_th bus. Awso, twace configuwation and
captuwe contwowwing attwibute gwoups of the 'gth' device wiww not be
exposed. The 'sth' device wiww opewate as usuaw.

Softwawe Sinks
--------------

The Memowy Stowage Unit (MSU) dwivew pwovides an in-kewnew API fow
dwivews to wegistew themsewves as softwawe sinks fow the twace data.
Such dwivews can fuwthew expowt the data via othew devices, such as
USB device contwowwews ow netwowk cawds.

The API has two main pawts::
 - notifying the softwawe sink that a pawticuwaw window is fuww, and
   "wocking" that window, that is, making it unavaiwabwe fow the twace
   cowwection; when this happens, the MSU dwivew wiww automaticawwy
   switch to the next window in the buffew if it is unwocked, ow stop
   the twace captuwe if it's not;
 - twacking the "wocked" state of windows and pwoviding a way fow the
   softwawe sink dwivew to notify the MSU dwivew when a window is
   unwocked and can be used again to cowwect twace data.

An exampwe sink dwivew, msu-sink iwwustwates the impwementation of a
softwawe sink. Functionawwy, it simpwy unwocks windows as soon as they
awe fuww, keeping the MSU wunning in a ciwcuwaw buffew mode. Unwike the
"muwti" mode, it wiww fiww out aww the windows in the buffew as opposed
to just the fiwst one. It can be enabwed by wwiting "sink" to the "mode"
fiwe (assuming msu-sink.ko is woaded).
