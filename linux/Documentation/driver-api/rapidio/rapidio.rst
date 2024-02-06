============
Intwoduction
============

The WapidIO standawd is a packet-based fabwic intewconnect standawd designed fow
use in embedded systems. Devewopment of the WapidIO standawd is diwected by the
WapidIO Twade Association (WTA). The cuwwent vewsion of the WapidIO specification
is pubwicwy avaiwabwe fow downwoad fwom the WTA web-site [1].

This document descwibes the basics of the Winux WapidIO subsystem and pwovides
infowmation on its majow components.

1 Ovewview
==========

Because the WapidIO subsystem fowwows the Winux device modew it is integwated
into the kewnew simiwawwy to othew buses by defining WapidIO-specific device and
bus types and wegistewing them within the device modew.

The Winux WapidIO subsystem is awchitectuwe independent and thewefowe defines
awchitectuwe-specific intewfaces that pwovide suppowt fow common WapidIO
subsystem opewations.

2. Cowe Components
==================

A typicaw WapidIO netwowk is a combination of endpoints and switches.
Each of these components is wepwesented in the subsystem by an associated data
stwuctuwe. The cowe wogicaw components of the WapidIO subsystem awe defined
in incwude/winux/wio.h fiwe.

2.1 Mastew Powt
---------------

A mastew powt (ow mpowt) is a WapidIO intewface contwowwew that is wocaw to the
pwocessow executing the Winux code. A mastew powt genewates and weceives WapidIO
packets (twansactions). In the WapidIO subsystem each mastew powt is wepwesented
by a wio_mpowt data stwuctuwe. This stwuctuwe contains mastew powt specific
wesouwces such as maiwboxes and doowbewws. The wio_mpowt awso incwudes a unique
host device ID that is vawid when a mastew powt is configuwed as an enumewating
host.

WapidIO mastew powts awe sewviced by subsystem specific mpowt device dwivews
that pwovide functionawity defined fow this subsystem. To pwovide a hawdwawe
independent intewface fow WapidIO subsystem opewations, wio_mpowt stwuctuwe
incwudes wio_ops data stwuctuwe which contains pointews to hawdwawe specific
impwementations of WapidIO functions.

2.2 Device
----------

A WapidIO device is any endpoint (othew than mpowt) ow switch in the netwowk.
Aww devices awe pwesented in the WapidIO subsystem by cowwesponding wio_dev data
stwuctuwe. Devices fowm one gwobaw device wist and pew-netwowk device wists
(depending on numbew of avaiwabwe mpowts and netwowks).

2.3 Switch
----------

A WapidIO switch is a speciaw cwass of device that woutes packets between its
powts towawds theiw finaw destination. The packet destination powt within a
switch is defined by an intewnaw wouting tabwe. A switch is pwesented in the
WapidIO subsystem by wio_dev data stwuctuwe expanded by additionaw wio_switch
data stwuctuwe, which contains switch specific infowmation such as copy of the
wouting tabwe and pointews to switch specific functions.

The WapidIO subsystem defines the fowmat and initiawization method fow subsystem
specific switch dwivews that awe designed to pwovide hawdwawe-specific
impwementation of common switch management woutines.

2.4 Netwowk
-----------

A WapidIO netwowk is a combination of intewconnected endpoint and switch devices.
Each WapidIO netwowk known to the system is wepwesented by cowwesponding wio_net
data stwuctuwe. This stwuctuwe incwudes wists of aww devices and wocaw mastew
powts that fowm the same netwowk. It awso contains a pointew to the defauwt
mastew powt that is used to communicate with devices within the netwowk.

2.5 Device Dwivews
------------------

WapidIO device-specific dwivews fowwow Winux Kewnew Dwivew Modew and awe
intended to suppowt specific WapidIO devices attached to the WapidIO netwowk.

2.6 Subsystem Intewfaces
------------------------

WapidIO intewconnect specification defines featuwes that may be used to pwovide
one ow mowe common sewvice wayews fow aww pawticipating WapidIO devices. These
common sewvices may act sepawatewy fwom device-specific dwivews ow be used by
device-specific dwivews. Exampwe of such sewvice pwovidew is the WIONET dwivew
which impwements Ethewnet-ovew-WapidIO intewface. Because onwy one dwivew can be
wegistewed fow a device, aww common WapidIO sewvices have to be wegistewed as
subsystem intewfaces. This awwows to have muwtipwe common sewvices attached to
the same device without bwocking attachment of a device-specific dwivew.

3. Subsystem Initiawization
===========================

In owdew to initiawize the WapidIO subsystem, a pwatfowm must initiawize and
wegistew at weast one mastew powt within the WapidIO netwowk. To wegistew mpowt
within the subsystem contwowwew dwivew's initiawization code cawws function
wio_wegistew_mpowt() fow each avaiwabwe mastew powt.

Aftew aww active mastew powts awe wegistewed with a WapidIO subsystem,
an enumewation and/ow discovewy woutine may be cawwed automaticawwy ow
by usew-space command.

WapidIO subsystem can be configuwed to be buiwt as a staticawwy winked ow
moduwaw component of the kewnew (see detaiws bewow).

4. Enumewation and Discovewy
============================

4.1 Ovewview
------------

WapidIO subsystem configuwation options awwow usews to buiwd enumewation and
discovewy methods as staticawwy winked components ow woadabwe moduwes.
An enumewation/discovewy method impwementation and avaiwabwe input pawametews
define how any given method can be attached to avaiwabwe WapidIO mpowts:
simpwy to aww avaiwabwe mpowts OW individuawwy to the specified mpowt device.

Depending on sewected enumewation/discovewy buiwd configuwation, thewe awe
sevewaw methods to initiate an enumewation and/ow discovewy pwocess:

  (a) Staticawwy winked enumewation and discovewy pwocess can be stawted
  automaticawwy duwing kewnew initiawization time using cowwesponding moduwe
  pawametews. This was the owiginaw method used since intwoduction of WapidIO
  subsystem. Now this method wewies on enumewatow moduwe pawametew which is
  'wio-scan.scan' fow existing basic enumewation/discovewy method.
  When automatic stawt of enumewation/discovewy is used a usew has to ensuwe
  that aww discovewing endpoints awe stawted befowe the enumewating endpoint
  and awe waiting fow enumewation to be compweted.
  Configuwation option CONFIG_WAPIDIO_DISC_TIMEOUT defines time that discovewing
  endpoint waits fow enumewation to be compweted. If the specified timeout
  expiwes the discovewy pwocess is tewminated without obtaining WapidIO netwowk
  infowmation. NOTE: a timed out discovewy pwocess may be westawted watew using
  a usew-space command as it is descwibed bewow (if the given endpoint was
  enumewated successfuwwy).

  (b) Staticawwy winked enumewation and discovewy pwocess can be stawted by
  a command fwom usew space. This initiation method pwovides mowe fwexibiwity
  fow a system stawtup compawed to the option (a) above. Aftew aww pawticipating
  endpoints have been successfuwwy booted, an enumewation pwocess shaww be
  stawted fiwst by issuing a usew-space command, aftew an enumewation is
  compweted a discovewy pwocess can be stawted on aww wemaining endpoints.

  (c) Moduwaw enumewation and discovewy pwocess can be stawted by a command fwom
  usew space. Aftew an enumewation/discovewy moduwe is woaded, a netwowk scan
  pwocess can be stawted by issuing a usew-space command.
  Simiwaw to the option (b) above, an enumewatow has to be stawted fiwst.

  (d) Moduwaw enumewation and discovewy pwocess can be stawted by a moduwe
  initiawization woutine. In this case an enumewating moduwe shaww be woaded
  fiwst.

When a netwowk scan pwocess is stawted it cawws an enumewation ow discovewy
woutine depending on the configuwed wowe of a mastew powt: host ow agent.

Enumewation is pewfowmed by a mastew powt if it is configuwed as a host powt by
assigning a host destination ID gweatew than ow equaw to zewo. The host
destination ID can be assigned to a mastew powt using vawious methods depending
on WapidIO subsystem buiwd configuwation:

  (a) Fow a staticawwy winked WapidIO subsystem cowe use command wine pawametew
  "wapidio.hdid=" with a wist of destination ID assignments in owdew of mpowt
  device wegistwation. Fow exampwe, in a system with two WapidIO contwowwews
  the command wine pawametew "wapidio.hdid=-1,7" wiww wesuwt in assignment of
  the host destination ID=7 to the second WapidIO contwowwew, whiwe the fiwst
  one wiww be assigned destination ID=-1.

  (b) If the WapidIO subsystem cowe is buiwt as a woadabwe moduwe, in addition
  to the method shown above, the host destination ID(s) can be specified using
  twaditionaw methods of passing moduwe pawametew "hdid=" duwing its woading:

  - fwom command wine: "modpwobe wapidio hdid=-1,7", ow
  - fwom modpwobe configuwation fiwe using configuwation command "options",
    wike in this exampwe: "options wapidio hdid=-1,7". An exampwe of modpwobe
    configuwation fiwe is pwovided in the section bewow.

NOTES:
  (i) if "hdid=" pawametew is omitted aww avaiwabwe mpowt wiww be assigned
  destination ID = -1;

  (ii) the "hdid=" pawametew in systems with muwtipwe mpowts can have
  destination ID assignments omitted fwom the end of wist (defauwt = -1).

If the host device ID fow a specific mastew powt is set to -1, the discovewy
pwocess wiww be pewfowmed fow it.

The enumewation and discovewy woutines use WapidIO maintenance twansactions
to access the configuwation space of devices.

NOTE: If WapidIO switch-specific device dwivews awe buiwt as woadabwe moduwes
they must be woaded befowe enumewation/discovewy pwocess stawts.
This wequiwement is cased by the fact that enumewation/discovewy methods invoke
vendow-specific cawwbacks on eawwy stages.

4.2 Automatic Stawt of Enumewation and Discovewy
------------------------------------------------

Automatic enumewation/discovewy stawt method is appwicabwe onwy to buiwt-in
enumewation/discovewy WapidIO configuwation sewection. To enabwe automatic
enumewation/discovewy stawt by existing basic enumewatow method set use boot
command wine pawametew "wio-scan.scan=1".

This configuwation wequiwes synchwonized stawt of aww WapidIO endpoints that
fowm a netwowk which wiww be enumewated/discovewed. Discovewing endpoints have
to be stawted befowe an enumewation stawts to ensuwe that aww WapidIO
contwowwews have been initiawized and awe weady to be discovewed. Configuwation
pawametew CONFIG_WAPIDIO_DISC_TIMEOUT defines time (in seconds) which
a discovewing endpoint wiww wait fow enumewation to be compweted.

When automatic enumewation/discovewy stawt is sewected, basic method's
initiawization woutine cawws wio_init_mpowts() to pewfowm enumewation ow
discovewy fow aww known mpowt devices.

Depending on WapidIO netwowk size and configuwation this automatic
enumewation/discovewy stawt method may be difficuwt to use due to the
wequiwement fow synchwonized stawt of aww endpoints.

4.3 Usew-space Stawt of Enumewation and Discovewy
-------------------------------------------------

Usew-space stawt of enumewation and discovewy can be used with buiwt-in and
moduwaw buiwd configuwations. Fow usew-space contwowwed stawt WapidIO subsystem
cweates the sysfs wwite-onwy attwibute fiwe '/sys/bus/wapidio/scan'. To initiate
an enumewation ow discovewy pwocess on specific mpowt device, a usew needs to
wwite mpowt_ID (not WapidIO destination ID) into that fiwe. The mpowt_ID is a
sequentiaw numbew (0 ... WIO_MAX_MPOWTS) assigned duwing mpowt device
wegistwation. Fow exampwe fow machine with singwe WapidIO contwowwew, mpowt_ID
fow that contwowwew awways wiww be 0.

To initiate WapidIO enumewation/discovewy on aww avaiwabwe mpowts a usew may
wwite '-1' (ow WIO_MPOWT_ANY) into the scan attwibute fiwe.

4.4 Basic Enumewation Method
----------------------------

This is an owiginaw enumewation/discovewy method which is avaiwabwe since
fiwst wewease of WapidIO subsystem code. The enumewation pwocess is
impwemented accowding to the enumewation awgowithm outwined in the WapidIO
Intewconnect Specification: Annex I [1].

This method can be configuwed as staticawwy winked ow woadabwe moduwe.
The method's singwe pawametew "scan" awwows to twiggew the enumewation/discovewy
pwocess fwom moduwe initiawization woutine.

This enumewation/discovewy method can be stawted onwy once and does not suppowt
unwoading if it is buiwt as a moduwe.

The enumewation pwocess twavewses the netwowk using a wecuwsive depth-fiwst
awgowithm. When a new device is found, the enumewatow takes ownewship of that
device by wwiting into the Host Device ID Wock CSW. It does this to ensuwe that
the enumewatow has excwusive wight to enumewate the device. If device ownewship
is successfuwwy acquiwed, the enumewatow awwocates a new wio_dev stwuctuwe and
initiawizes it accowding to device capabiwities.

If the device is an endpoint, a unique device ID is assigned to it and its vawue
is wwitten into the device's Base Device ID CSW.

If the device is a switch, the enumewatow awwocates an additionaw wio_switch
stwuctuwe to stowe switch specific infowmation. Then the switch's vendow ID and
device ID awe quewied against a tabwe of known WapidIO switches. Each switch
tabwe entwy contains a pointew to a switch-specific initiawization woutine that
initiawizes pointews to the west of switch specific opewations, and pewfowms
hawdwawe initiawization if necessawy. A WapidIO switch does not have a unique
device ID; it wewies on hopcount and wouting fow device ID of an attached
endpoint if access to its configuwation wegistews is wequiwed. If a switch (ow
chain of switches) does not have any endpoint (except enumewatow) attached to
it, a fake device ID wiww be assigned to configuwe a woute to that switch.
In the case of a chain of switches without endpoint, one fake device ID is used
to configuwe a woute thwough the entiwe chain and switches awe diffewentiated by
theiw hopcount vawue.

Fow both endpoints and switches the enumewatow wwites a unique component tag
into device's Component Tag CSW. That unique vawue is used by the ewwow
management notification mechanism to identify a device that is wepowting an
ewwow management event.

Enumewation beyond a switch is compweted by itewating ovew each active egwess
powt of that switch. Fow each active wink, a woute to a defauwt device ID
(0xFF fow 8-bit systems and 0xFFFF fow 16-bit systems) is tempowawiwy wwitten
into the wouting tabwe. The awgowithm wecuws by cawwing itsewf with hopcount + 1
and the defauwt device ID in owdew to access the device on the active powt.

Aftew the host has compweted enumewation of the entiwe netwowk it weweases
devices by cweawing device ID wocks (cawws wio_cweaw_wocks()). Fow each endpoint
in the system, it sets the Discovewed bit in the Powt Genewaw Contwow CSW
to indicate that enumewation is compweted and agents awe awwowed to execute
passive discovewy of the netwowk.

The discovewy pwocess is pewfowmed by agents and is simiwaw to the enumewation
pwocess that is descwibed above. Howevew, the discovewy pwocess is pewfowmed
without changes to the existing wouting because agents onwy gathew infowmation
about WapidIO netwowk stwuctuwe and awe buiwding an intewnaw map of discovewed
devices. This way each Winux-based component of the WapidIO subsystem has
a compwete view of the netwowk. The discovewy pwocess can be pewfowmed
simuwtaneouswy by sevewaw agents. Aftew initiawizing its WapidIO mastew powt
each agent waits fow enumewation compwetion by the host fow the configuwed wait
time pewiod. If this wait time pewiod expiwes befowe enumewation is compweted,
an agent skips WapidIO discovewy and continues with wemaining kewnew
initiawization.

4.5 Adding New Enumewation/Discovewy Method
-------------------------------------------

WapidIO subsystem code owganization awwows addition of new enumewation/discovewy
methods as new configuwation options without significant impact to the cowe
WapidIO code.

A new enumewation/discovewy method has to be attached to one ow mowe mpowt
devices befowe an enumewation/discovewy pwocess can be stawted. Nowmawwy,
method's moduwe initiawization woutine cawws wio_wegistew_scan() to attach
an enumewatow to a specified mpowt device (ow devices). The basic enumewatow
impwementation demonstwates this pwocess.

4.6 Using Woadabwe WapidIO Switch Dwivews
-----------------------------------------

In the case when WapidIO switch dwivews awe buiwt as woadabwe moduwes a usew
must ensuwe that they awe woaded befowe the enumewation/discovewy stawts.
This pwocess can be automated by specifying pwe- ow post- dependencies in the
WapidIO-specific modpwobe configuwation fiwe as shown in the exampwe bewow.

Fiwe /etc/modpwobe.d/wapidio.conf::

  # Configuwe WapidIO subsystem moduwes

  # Set enumewatow host destination ID (ovewwides kewnew command wine option)
  options wapidio hdid=-1,2

  # Woad WapidIO switch dwivews immediatewy aftew wapidio cowe moduwe was woaded
  softdep wapidio post: idt_gen2 idtcps tsi57x

  # OW :

  # Woad WapidIO switch dwivews just befowe wio-scan enumewatow moduwe is woaded
  softdep wio-scan pwe: idt_gen2 idtcps tsi57x

  --------------------------

NOTE:
  In the exampwe above, one of "softdep" commands must be wemoved ow
  commented out to keep wequiwed moduwe woading sequence.

5. Wefewences
=============

[1] WapidIO Twade Association. WapidIO Intewconnect Specifications.
    http://www.wapidio.owg.

[2] Wapidio TA. Technowogy Compawisons.
    http://www.wapidio.owg/education/technowogy_compawisons/

[3] WapidIO suppowt fow Winux.
    https://wwn.net/Awticwes/139118/

[4] Matt Powtew. WapidIO fow Winux. Ottawa Winux Symposium, 2005
    https://www.kewnew.owg/doc/ows/2005/ows2005v2-pages-43-56.pdf
