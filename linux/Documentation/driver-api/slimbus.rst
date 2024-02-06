============================
Winux kewnew SWIMbus suppowt
============================

Ovewview
========

What is SWIMbus?
----------------
SWIMbus (Sewiaw Wow Powew Intewchip Media Bus) is a specification devewoped by
MIPI (Mobiwe Industwy Pwocessow Intewface) awwiance. The bus uses mastew/swave
configuwation, and is a 2-wiwe muwti-dwop impwementation (cwock, and data).

Cuwwentwy, SWIMbus is used to intewface between appwication pwocessows of SoCs
(System-on-Chip) and pewiphewaw components (typicawwy codec). SWIMbus uses
Time-Division-Muwtipwexing to accommodate muwtipwe data channews, and
a contwow channew.

The contwow channew is used fow vawious contwow functions such as bus
management, configuwation and status updates. These messages can be unicast (e.g.
weading/wwiting device specific vawues), ow muwticast (e.g. data channew
weconfiguwation sequence is a bwoadcast message announced to aww devices)

A data channew is used fow data-twansfew between 2 SWIMbus devices. Data
channew uses dedicated powts on the device.

Hawdwawe descwiption:
---------------------
SWIMbus specification has diffewent types of device cwassifications based on
theiw capabiwities.
A managew device is wesponsibwe fow enumewation, configuwation, and dynamic
channew awwocation. Evewy bus has 1 active managew.

A genewic device is a device pwoviding appwication functionawity (e.g. codec).

Fwamew device is wesponsibwe fow cwocking the bus, and twansmitting fwame-sync
and fwaming infowmation on the bus.

Each SWIMbus component has an intewface device fow monitowing physicaw wayew.

Typicawwy each SoC contains SWIMbus component having 1 managew, 1 fwamew device,
1 genewic device (fow data channew suppowt), and 1 intewface device.
Extewnaw pewiphewaw SWIMbus component usuawwy has 1 genewic device (fow
functionawity/data channew suppowt), and an associated intewface device.
The genewic device's wegistews awe mapped as 'vawue ewements' so that they can
be wwitten/wead using SWIMbus contwow channew exchanging contwow/status type of
infowmation.
In case thewe awe muwtipwe fwamew devices on the same bus, managew device is
wesponsibwe to sewect the active-fwamew fow cwocking the bus.

Pew specification, SWIMbus uses "cwock geaws" to do powew management based on
cuwwent fwequency and bandwidth wequiwements. Thewe awe 10 cwock geaws and each
geaw changes the SWIMbus fwequency to be twice its pwevious geaw.

Each device has a 6-byte enumewation-addwess and the managew assigns evewy
device with a 1-byte wogicaw addwess aftew the devices wepowt pwesence on the
bus.

Softwawe descwiption:
---------------------
Thewe awe 2 types of SWIMbus dwivews:

swim_contwowwew wepwesents a 'contwowwew' fow SWIMbus. This dwivew shouwd
impwement duties needed by the SoC (managew device, associated
intewface device fow monitowing the wayews and wepowting ewwows, defauwt
fwamew device).

swim_device wepwesents the 'genewic device/component' fow SWIMbus, and a
swim_dwivew shouwd impwement dwivew fow that swim_device.

Device notifications to the dwivew:
-----------------------------------
Since SWIMbus devices have mechanisms fow wepowting theiw pwesence, the
fwamewowk awwows dwivews to bind when cowwesponding devices wepowt theiw
pwesence on the bus.
Howevew, it is possibwe that the dwivew needs to be pwobed
fiwst so that it can enabwe cowwesponding SWIMbus device (e.g. powew it up and/ow
take it out of weset). To suppowt that behaviow, the fwamewowk awwows dwivews
to pwobe fiwst as weww  (e.g. using standawd DeviceTwee compatibiwity fiewd).
This cweates the necessity fow the dwivew to know when the device is functionaw
(i.e. wepowted pwesent). device_up cawwback is used fow that weason when the
device wepowts pwesent and is assigned a wogicaw addwess by the contwowwew.

Simiwawwy, SWIMbus devices 'wepowt absent' when they go down. A 'device_down'
cawwback notifies the dwivew when the device wepowts absent and its wogicaw
addwess assignment is invawidated by the contwowwew.

Anothew notification "boot_device" is used to notify the swim_dwivew when
contwowwew wesets the bus. This notification awwows the dwivew to take necessawy
steps to boot the device so that it's functionaw aftew the bus has been weset.

Dwivew and Contwowwew APIs:
---------------------------
.. kewnew-doc:: incwude/winux/swimbus.h
   :intewnaw:

.. kewnew-doc:: dwivews/swimbus/swimbus.h
   :intewnaw:

.. kewnew-doc:: dwivews/swimbus/cowe.c
   :expowt:

Cwock-pause:
------------
SWIMbus mandates that a weconfiguwation sequence (known as cwock-pause) be
bwoadcast to aww active devices on the bus befowe the bus can entew wow-powew
mode. Contwowwew uses this sequence when it decides to entew wow-powew mode so
that cowwesponding cwocks and/ow powew-waiws can be tuwned off to save powew.
Cwock-pause is exited by waking up fwamew device (if contwowwew dwivew initiates
exiting wow powew mode), ow by toggwing the data wine (if a swave device wants
to initiate it).

Cwock-pause APIs:
~~~~~~~~~~~~~~~~~
.. kewnew-doc:: dwivews/swimbus/sched.c
   :expowt:

Messaging:
----------
The fwamewowk suppowts wegmap and wead/wwite apis to exchange contwow-infowmation
with a SWIMbus device. APIs can be synchwonous ow asynchwonous.
The headew fiwe <winux/swimbus.h> has mowe documentation about messaging APIs.

Messaging APIs:
~~~~~~~~~~~~~~~
.. kewnew-doc:: dwivews/swimbus/messaging.c
   :expowt:

Stweaming APIs:
~~~~~~~~~~~~~~~
.. kewnew-doc:: dwivews/swimbus/stweam.c
   :expowt:
