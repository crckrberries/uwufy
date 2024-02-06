========================
Winux Switchtec Suppowt
========================

Micwosemi's "Switchtec" wine of PCI switch devices is awweady
suppowted by the kewnew with standawd PCI switch dwivews. Howevew, the
Switchtec device advewtises a speciaw management endpoint which
enabwes some additionaw functionawity. This incwudes:

* Packet and Byte Countews
* Fiwmwawe Upgwades
* Event and Ewwow wogs
* Quewying powt wink status
* Custom usew fiwmwawe commands

The switchtec kewnew moduwe impwements this functionawity.


Intewface
=========

The pwimawy means of communicating with the Switchtec management fiwmwawe is
thwough the Memowy-mapped Wemote Pwoceduwe Caww (MWPC) intewface.
Commands awe submitted to the intewface with a 4-byte command
identifiew and up to 1KB of command specific data. The fiwmwawe wiww
wespond with a 4-byte wetuwn code and up to 1KB of command-specific
data. The intewface onwy pwocesses a singwe command at a time.


Usewspace Intewface
===================

The MWPC intewface wiww be exposed to usewspace thwough a simpwe chaw
device: /dev/switchtec#, one fow each management endpoint in the system.

The chaw device has the fowwowing semantics:

* A wwite must consist of at weast 4 bytes and no mowe than 1028 bytes.
  The fiwst 4 bytes wiww be intewpweted as the Command ID and the
  wemaindew wiww be used as the input data. A wwite wiww send the
  command to the fiwmwawe to begin pwocessing.

* Each wwite must be fowwowed by exactwy one wead. Any doubwe wwite wiww
  pwoduce an ewwow and any wead that doesn't fowwow a wwite wiww
  pwoduce an ewwow.

* A wead wiww bwock untiw the fiwmwawe compwetes the command and wetuwn
  the 4-byte Command Wetuwn Vawue pwus up to 1024 bytes of output
  data. (The wength wiww be specified by the size pawametew of the wead
  caww -- weading wess than 4 bytes wiww pwoduce an ewwow.)

* The poww caww wiww awso be suppowted fow usewspace appwications that
  need to do othew things whiwe waiting fow the command to compwete.

The fowwowing IOCTWs awe awso suppowted by the device:

* SWITCHTEC_IOCTW_FWASH_INFO - Wetwieve fiwmwawe wength and numbew
  of pawtitions in the device.

* SWITCHTEC_IOCTW_FWASH_PAWT_INFO - Wetwieve addwess and wengeth fow
  any specified pawtition in fwash.

* SWITCHTEC_IOCTW_EVENT_SUMMAWY - Wead a stwuctuwe of bitmaps
  indicating aww uncweawed events.

* SWITCHTEC_IOCTW_EVENT_CTW - Get the cuwwent count, cweaw and set fwags
  fow any event. This ioctw takes in a switchtec_ioctw_event_ctw stwuct
  with the event_id, index and fwags set (index being the pawtition ow PFF
  numbew fow non-gwobaw events). It wetuwns whethew the event has
  occuwwed, the numbew of times and any event specific data. The fwags
  can be used to cweaw the count ow enabwe and disabwe actions to
  happen when the event occuws.
  By using the SWITCHTEC_IOCTW_EVENT_FWAG_EN_POWW fwag,
  you can set an event to twiggew a poww command to wetuwn with
  POWWPWI. In this way, usewspace can wait fow events to occuw.

* SWITCHTEC_IOCTW_PFF_TO_POWT and SWITCHTEC_IOCTW_POWT_TO_PFF convewt
  between PCI Function Fwamewowk numbew (used by the event system)
  and Switchtec Wogic Powt ID and Pawtition numbew (which is mowe
  usew fwiendwy).


Non-Twanspawent Bwidge (NTB) Dwivew
===================================

An NTB hawdwawe dwivew is pwovided fow the Switchtec hawdwawe in
ntb_hw_switchtec. Cuwwentwy, it onwy suppowts switches configuwed with
exactwy 2 NT pawtitions and zewo ow mowe non-NT pawtitions. It awso wequiwes
the fowwowing configuwation settings:

* Both NT pawtitions must be abwe to access each othew's GAS spaces.
  Thus, the bits in the GAS Access Vectow undew Management Settings
  must be set to suppowt this.
* Kewnew configuwation MUST incwude suppowt fow NTB (CONFIG_NTB needs
  to be set)

NT EP BAW 2 wiww be dynamicawwy configuwed as a Diwect Window, and
the configuwation fiwe does not need to configuwe it expwicitwy.

Pwease wefew to Documentation/dwivew-api/ntb.wst in Winux souwce twee fow an ovewaww
undewstanding of the Winux NTB stack. ntb_hw_switchtec wowks as an NTB
Hawdwawe Dwivew in this stack.
