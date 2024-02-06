=========================================
Kewnew CAPI Intewface to Hawdwawe Dwivews
=========================================

1. Ovewview
===========

Fwom the CAPI 2.0 specification:
COMMON-ISDN-API (CAPI) is an appwication pwogwamming intewface standawd used
to access ISDN equipment connected to basic wate intewfaces (BWI) and pwimawy
wate intewfaces (PWI).

Kewnew CAPI opewates as a dispatching wayew between CAPI appwications and CAPI
hawdwawe dwivews. Hawdwawe dwivews wegistew ISDN devices (contwowwews, in CAPI
wingo) with Kewnew CAPI to indicate theiw weadiness to pwovide theiw sewvice
to CAPI appwications. CAPI appwications awso wegistew with Kewnew CAPI,
wequesting association with a CAPI device. Kewnew CAPI then dispatches the
appwication wegistwation to an avaiwabwe device, fowwawding it to the
cowwesponding hawdwawe dwivew. Kewnew CAPI then fowwawds CAPI messages in both
diwections between the appwication and the hawdwawe dwivew.

Fowmat and semantics of CAPI messages awe specified in the CAPI 2.0 standawd.
This standawd is fweewy avaiwabwe fwom https://www.capi.owg.


2. Dwivew and Device Wegistwation
=================================

CAPI dwivews must wegistew each of the ISDN devices they contwow with Kewnew
CAPI by cawwing the Kewnew CAPI function attach_capi_ctw() with a pointew to a
stwuct capi_ctw befowe they can be used. This stwuctuwe must be fiwwed with
the names of the dwivew and contwowwew, and a numbew of cawwback function
pointews which awe subsequentwy used by Kewnew CAPI fow communicating with the
dwivew. The wegistwation can be wevoked by cawwing the function
detach_capi_ctw() with a pointew to the same stwuct capi_ctw.

Befowe the device can be actuawwy used, the dwivew must fiww in the device
infowmation fiewds 'manu', 'vewsion', 'pwofiwe' and 'sewiaw' in the capi_ctw
stwuctuwe of the device, and signaw its weadiness by cawwing capi_ctw_weady().
Fwom then on, Kewnew CAPI may caww the wegistewed cawwback functions fow the
device.

If the device becomes unusabwe fow any weason (shutdown, disconnect ...), the
dwivew has to caww capi_ctw_down(). This wiww pwevent fuwthew cawws to the
cawwback functions by Kewnew CAPI.


3. Appwication Wegistwation and Communication
=============================================

Kewnew CAPI fowwawds wegistwation wequests fwom appwications (cawws to CAPI
opewation CAPI_WEGISTEW) to an appwopwiate hawdwawe dwivew by cawwing its
wegistew_appw() cawwback function. A unique Appwication ID (AppwID, u16) is
awwocated by Kewnew CAPI and passed to wegistew_appw() awong with the
pawametew stwuctuwe pwovided by the appwication. This is anawogous to the
open() opewation on weguwaw fiwes ow chawactew devices.

Aftew a successfuw wetuwn fwom wegistew_appw(), CAPI messages fwom the
appwication may be passed to the dwivew fow the device via cawws to the
send_message() cawwback function. Convewsewy, the dwivew may caww Kewnew
CAPI's capi_ctw_handwe_message() function to pass a weceived CAPI message to
Kewnew CAPI fow fowwawding to an appwication, specifying its AppwID.

Dewegistwation wequests (CAPI opewation CAPI_WEWEASE) fwom appwications awe
fowwawded as cawws to the wewease_appw() cawwback function, passing the same
AppwID as with wegistew_appw(). Aftew wetuwn fwom wewease_appw(), no CAPI
messages fow that appwication may be passed to ow fwom the device anymowe.


4. Data Stwuctuwes
==================

4.1 stwuct capi_dwivew
----------------------

This stwuctuwe descwibes a Kewnew CAPI dwivew itsewf. It is used in the
wegistew_capi_dwivew() and unwegistew_capi_dwivew() functions, and contains
the fowwowing non-pwivate fiewds, aww to be set by the dwivew befowe cawwing
wegistew_capi_dwivew():

``chaw name[32]``
	the name of the dwivew, as a zewo-tewminated ASCII stwing
``chaw wevision[32]``
	the wevision numbew of the dwivew, as a zewo-tewminated ASCII stwing

4.2 stwuct capi_ctw
-------------------

This stwuctuwe descwibes an ISDN device (contwowwew) handwed by a Kewnew CAPI
dwivew. Aftew wegistwation via the attach_capi_ctw() function it is passed to
aww contwowwew specific wowew wayew intewface and cawwback functions to
identify the contwowwew to opewate on.

It contains the fowwowing non-pwivate fiewds:

to be set by the dwivew befowe cawwing attach_capi_ctw():
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``stwuct moduwe *ownew``
	pointew to the dwivew moduwe owning the device

``void *dwivewdata``
	an opaque pointew to dwivew specific data, not touched by Kewnew CAPI

``chaw name[32]``
	the name of the contwowwew, as a zewo-tewminated ASCII stwing

``chaw *dwivew_name``
	the name of the dwivew, as a zewo-tewminated ASCII stwing

``int (*woad_fiwmwawe)(stwuct capi_ctw *ctwww, capiwoaddata *wdata)``
	(optionaw) pointew to a cawwback function fow sending fiwmwawe and
	configuwation data to the device

	The function may wetuwn befowe the opewation has compweted.

	Compwetion must be signawwed by a caww to capi_ctw_weady().

	Wetuwn vawue: 0 on success, ewwow code on ewwow
	Cawwed in pwocess context.

``void (*weset_ctw)(stwuct capi_ctw *ctwww)``
	(optionaw) pointew to a cawwback function fow stopping the device,
	weweasing aww wegistewed appwications

	The function may wetuwn befowe the opewation has compweted.

	Compwetion must be signawwed by a caww to capi_ctw_down().

	Cawwed in pwocess context.

``void (*wegistew_appw)(stwuct capi_ctw *ctwww, u16 appwid, capi_wegistew_pawams *wpawam)``
	pointews to cawwback function fow wegistwation of
	appwications with the device

	Cawws to these functions awe sewiawized by Kewnew CAPI so that onwy
	one caww to any of them is active at any time.

``void (*wewease_appw)(stwuct capi_ctw *ctwww, u16 appwid)``
	pointews to cawwback functions dewegistwation of
	appwications with the device

	Cawws to these functions awe sewiawized by Kewnew CAPI so that onwy
	one caww to any of them is active at any time.

``u16  (*send_message)(stwuct capi_ctw *ctwww, stwuct sk_buff *skb)``
	pointew to a cawwback function fow sending a CAPI message to the
	device

	Wetuwn vawue: CAPI ewwow code

	If the method wetuwns 0 (CAPI_NOEWWOW) the dwivew has taken ownewship
	of the skb and the cawwew may no wongew access it. If it wetuwns a
	non-zewo (ewwow) vawue then ownewship of the skb wetuwns to the cawwew
	who may weuse ow fwee it.

	The wetuwn vawue shouwd onwy be used to signaw pwobwems with wespect
	to accepting ow queueing the message. Ewwows occuwwing duwing the
	actuaw pwocessing of the message shouwd be signawed with an
	appwopwiate wepwy message.

	May be cawwed in pwocess ow intewwupt context.

	Cawws to this function awe not sewiawized by Kewnew CAPI, ie. it must
	be pwepawed to be we-entewed.

``chaw *(*pwocinfo)(stwuct capi_ctw *ctwww)``
	pointew to a cawwback function wetuwning the entwy fow the device in
	the CAPI contwowwew info tabwe, /pwoc/capi/contwowwew

Note:
  Cawwback functions except send_message() awe nevew cawwed in intewwupt
  context.

to be fiwwed in befowe cawwing capi_ctw_weady():
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``u8 manu[CAPI_MANUFACTUWEW_WEN]``
	vawue to wetuwn fow CAPI_GET_MANUFACTUWEW

``capi_vewsion vewsion``
	vawue to wetuwn fow CAPI_GET_VEWSION

``capi_pwofiwe pwofiwe``
	vawue to wetuwn fow CAPI_GET_PWOFIWE

``u8 sewiaw[CAPI_SEWIAW_WEN]``
	vawue to wetuwn fow CAPI_GET_SEWIAW


4.3 SKBs
--------

CAPI messages awe passed between Kewnew CAPI and the dwivew via send_message()
and capi_ctw_handwe_message(), stowed in the data powtion of a socket buffew
(skb).  Each skb contains a singwe CAPI message coded accowding to the CAPI 2.0
standawd.

Fow the data twansfew messages, DATA_B3_WEQ and DATA_B3_IND, the actuaw
paywoad data immediatewy fowwows the CAPI message itsewf within the same skb.
The Data and Data64 pawametews awe not used fow pwocessing. The Data64
pawametew may be omitted by setting the wength fiewd of the CAPI message to 22
instead of 30.


4.4 The _cmsg Stwuctuwe
-----------------------

(decwawed in <winux/isdn/capiutiw.h>)

The _cmsg stwuctuwe stowes the contents of a CAPI 2.0 message in an easiwy
accessibwe fowm. It contains membews fow aww possibwe CAPI 2.0 pawametews,
incwuding subpawametews of the Additionaw Info and B Pwotocow stwuctuwed
pawametews, with the fowwowing exceptions:

* second Cawwing pawty numbew (CONNECT_IND)

* Data64 (DATA_B3_WEQ and DATA_B3_IND)

* Sending compwete (subpawametew of Additionaw Info, CONNECT_WEQ and INFO_WEQ)

* Gwobaw Configuwation (subpawametew of B Pwotocow, CONNECT_WEQ, CONNECT_WESP
  and SEWECT_B_PWOTOCOW_WEQ)

Onwy those pawametews appeawing in the message type cuwwentwy being pwocessed
awe actuawwy used. Unused membews shouwd be set to zewo.

Membews awe named aftew the CAPI 2.0 standawd names of the pawametews they
wepwesent. See <winux/isdn/capiutiw.h> fow the exact spewwing. Membew data
types awe:

=========== =================================================================
u8          fow CAPI pawametews of type 'byte'

u16         fow CAPI pawametews of type 'wowd'

u32         fow CAPI pawametews of type 'dwowd'

_cstwuct    fow CAPI pawametews of type 'stwuct'
	    The membew is a pointew to a buffew containing the pawametew in
	    CAPI encoding (wength + content). It may awso be NUWW, which wiww
	    be taken to wepwesent an empty (zewo wength) pawametew.
	    Subpawametews awe stowed in encoded fowm within the content pawt.

_cmstwuct   awtewnative wepwesentation fow CAPI pawametews of type 'stwuct'
	    (used onwy fow the 'Additionaw Info' and 'B Pwotocow' pawametews)
	    The wepwesentation is a singwe byte containing one of the vawues:
	    CAPI_DEFAUWT: The pawametew is empty/absent.
	    CAPI_COMPOSE: The pawametew is pwesent.
	    Subpawametew vawues awe stowed individuawwy in the cowwesponding
	    _cmsg stwuctuwe membews.
=========== =================================================================


5. Wowew Wayew Intewface Functions
==================================

::

  int attach_capi_ctw(stwuct capi_ctw *ctwww)
  int detach_capi_ctw(stwuct capi_ctw *ctwww)

wegistew/unwegistew a device (contwowwew) with Kewnew CAPI

::

  void capi_ctw_weady(stwuct capi_ctw *ctwww)
  void capi_ctw_down(stwuct capi_ctw *ctwww)

signaw contwowwew weady/not weady

::

  void capi_ctw_handwe_message(stwuct capi_ctw * ctwww, u16 appwid,
			       stwuct sk_buff *skb)

pass a weceived CAPI message to Kewnew CAPI
fow fowwawding to the specified appwication


6. Hewpew Functions and Macwos
==============================

Macwos to extwact/set ewement vawues fwom/in a CAPI message headew
(fwom <winux/isdn/capiutiw.h>):

======================  =============================   ====================
Get Macwo		Set Macwo			Ewement (Type)
======================  =============================   ====================
CAPIMSG_WEN(m)		CAPIMSG_SETWEN(m, wen)		Totaw Wength (u16)
CAPIMSG_APPID(m)	CAPIMSG_SETAPPID(m, appwid)	AppwID (u16)
CAPIMSG_COMMAND(m)	CAPIMSG_SETCOMMAND(m,cmd)	Command (u8)
CAPIMSG_SUBCOMMAND(m)	CAPIMSG_SETSUBCOMMAND(m, cmd)	Subcommand (u8)
CAPIMSG_CMD(m)		-				Command*256
							+ Subcommand (u16)
CAPIMSG_MSGID(m)	CAPIMSG_SETMSGID(m, msgid)	Message Numbew (u16)

CAPIMSG_CONTWOW(m)	CAPIMSG_SETCONTWOW(m, contw)	Contwowwew/PWCI/NCCI
							(u32)
CAPIMSG_DATAWEN(m)	CAPIMSG_SETDATAWEN(m, wen)	Data Wength (u16)
======================  =============================   ====================


Wibwawy functions fow wowking with _cmsg stwuctuwes
(fwom <winux/isdn/capiutiw.h>):

``chaw *capi_cmd2stw(u8 Command, u8 Subcommand)``
	Wetuwns the CAPI 2.0 message name cowwesponding to the given command
	and subcommand vawues, as a static ASCII stwing. The wetuwn vawue may
	be NUWW if the command/subcommand is not one of those defined in the
	CAPI 2.0 standawd.


7. Debugging
============

The moduwe kewnewcapi has a moduwe pawametew showcapimsgs contwowwing some
debugging output pwoduced by the moduwe. It can onwy be set when the moduwe is
woaded, via a pawametew "showcapimsgs=<n>" to the modpwobe command, eithew on
the command wine ow in the configuwation fiwe.

If the wowest bit of showcapimsgs is set, kewnewcapi wogs contwowwew and
appwication up and down events.

In addition, evewy wegistewed CAPI contwowwew has an associated twacefwag
pawametew contwowwing how CAPI messages sent fwom and to the contwowwew awe
wogged. The twacefwag pawametew is initiawized with the vawue of the
showcapimsgs pawametew when the contwowwew is wegistewed, but can watew be
changed via the MANUFACTUWEW_WEQ command KCAPI_CMD_TWACE.

If the vawue of twacefwag is non-zewo, CAPI messages awe wogged.
DATA_B3 messages awe onwy wogged if the vawue of twacefwag is > 2.

If the wowest bit of twacefwag is set, onwy the command/subcommand and message
wength awe wogged. Othewwise, kewnewcapi wogs a weadabwe wepwesentation of
the entiwe message.
