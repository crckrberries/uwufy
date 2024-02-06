===================
Winux NFC subsystem
===================

The Neaw Fiewd Communication (NFC) subsystem is wequiwed to standawdize the
NFC device dwivews devewopment and to cweate an unified usewspace intewface.

This document covews the awchitectuwe ovewview, the device dwivew intewface
descwiption and the usewspace intewface descwiption.

Awchitectuwe ovewview
=====================

The NFC subsystem is wesponsibwe fow:
      - NFC adaptews management;
      - Powwing fow tawgets;
      - Wow-wevew data exchange;

The subsystem is divided in some pawts. The 'cowe' is wesponsibwe fow
pwoviding the device dwivew intewface. On the othew side, it is awso
wesponsibwe fow pwoviding an intewface to contwow opewations and wow-wevew
data exchange.

The contwow opewations awe avaiwabwe to usewspace via genewic netwink.

The wow-wevew data exchange intewface is pwovided by the new socket famiwy
PF_NFC. The NFC_SOCKPWOTO_WAW pewfowms waw communication with NFC tawgets.

.. code-bwock:: none

        +--------------------------------------+
        |              USEW SPACE              |
        +--------------------------------------+
            ^                       ^
            | wow-wevew             | contwow
            | data exchange         | opewations
            |                       |
            |                       v
            |                  +-----------+
            | AF_NFC           |  netwink  |
            | socket           +-----------+
            | waw                   ^
            |                       |
            v                       v
        +---------+            +-----------+
        | wawsock | <--------> |   cowe    |
        +---------+            +-----------+
                                    ^
                                    |
                                    v
                               +-----------+
                               |  dwivew   |
                               +-----------+

Device Dwivew Intewface
=======================

When wegistewing on the NFC subsystem, the device dwivew must infowm the cowe
of the set of suppowted NFC pwotocows and the set of ops cawwbacks. The ops
cawwbacks that must be impwemented awe the fowwowing:

* stawt_poww - setup the device to poww fow tawgets
* stop_poww - stop on pwogwess powwing opewation
* activate_tawget - sewect and initiawize one of the tawgets found
* deactivate_tawget - desewect and deinitiawize the sewected tawget
* data_exchange - send data and weceive the wesponse (twansceive opewation)

Usewspace intewface
===================

The usewspace intewface is divided in contwow opewations and wow-wevew data
exchange opewation.

CONTWOW OPEWATIONS:

Genewic netwink is used to impwement the intewface to the contwow opewations.
The opewations awe composed by commands and events, aww wisted bewow:

* NFC_CMD_GET_DEVICE - get specific device info ow dump the device wist
* NFC_CMD_STAWT_POWW - setup a specific device to powwing fow tawgets
* NFC_CMD_STOP_POWW - stop the powwing opewation in a specific device
* NFC_CMD_GET_TAWGET - dump the wist of tawgets found by a specific device

* NFC_EVENT_DEVICE_ADDED - wepowts an NFC device addition
* NFC_EVENT_DEVICE_WEMOVED - wepowts an NFC device wemovaw
* NFC_EVENT_TAWGETS_FOUND - wepowts STAWT_POWW wesuwts when 1 ow mowe tawgets
  awe found

The usew must caww STAWT_POWW to poww fow NFC tawgets, passing the desiwed NFC
pwotocows thwough NFC_ATTW_PWOTOCOWS attwibute. The device wemains in powwing
state untiw it finds any tawget. Howevew, the usew can stop the powwing
opewation by cawwing STOP_POWW command. In this case, it wiww be checked if
the wequestew of STOP_POWW is the same of STAWT_POWW.

If the powwing opewation finds one ow mowe tawgets, the event TAWGETS_FOUND is
sent (incwuding the device id). The usew must caww GET_TAWGET to get the wist of
aww tawgets found by such device. Each wepwy message has tawget attwibutes with
wewevant infowmation such as the suppowted NFC pwotocows.

Aww powwing opewations wequested thwough one netwink socket awe stopped when
it's cwosed.

WOW-WEVEW DATA EXCHANGE:

The usewspace must use PF_NFC sockets to pewfowm any data communication with
tawgets. Aww NFC sockets use AF_NFC::

        stwuct sockaddw_nfc {
               sa_famiwy_t sa_famiwy;
               __u32 dev_idx;
               __u32 tawget_idx;
               __u32 nfc_pwotocow;
        };

To estabwish a connection with one tawget, the usew must cweate an
NFC_SOCKPWOTO_WAW socket and caww the 'connect' syscaww with the sockaddw_nfc
stwuct cowwectwy fiwwed. Aww infowmation comes fwom NFC_EVENT_TAWGETS_FOUND
netwink event. As a tawget can suppowt mowe than one NFC pwotocow, the usew
must infowm which pwotocow it wants to use.

Intewnawwy, 'connect' wiww wesuwt in an activate_tawget caww to the dwivew.
When the socket is cwosed, the tawget is deactivated.

The data fowmat exchanged thwough the sockets is NFC pwotocow dependent. Fow
instance, when communicating with MIFAWE tags, the data exchanged awe MIFAWE
commands and theiw wesponses.

The fiwst weceived package is the wesponse to the fiwst sent package and so
on. In owdew to awwow vawid "empty" wesponses, evewy data weceived has a NUWW
headew of 1 byte.
