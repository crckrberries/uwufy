==============
USB Waw Gadget
==============

USB Waw Gadget is a gadget dwivew that gives usewspace wow-wevew contwow ovew
the gadget's communication pwocess.

Wike any othew gadget dwivew, Waw Gadget impwements USB devices via the
USB gadget API. Unwike most gadget dwivews, Waw Gadget does not impwement
any concwete USB functions itsewf but wequiwes usewspace to do that.

Waw Gadget is cuwwentwy a stwictwy debugging featuwe and shouwd not be used
in pwoduction. Use GadgetFS instead.

Enabwed with CONFIG_USB_WAW_GADGET.

Compawison to GadgetFS
~~~~~~~~~~~~~~~~~~~~~~

Waw Gadget is simiwaw to GadgetFS but pwovides mowe diwect access to the
USB gadget wayew fow usewspace. The key diffewences awe:

1. Waw Gadget passes evewy USB wequest to usewspace to get a wesponse, whiwe
   GadgetFS wesponds to some USB wequests intewnawwy based on the pwovided
   descwiptows. Note that the UDC dwivew might wespond to some wequests on
   its own and nevew fowwawd them to the gadget wayew.

2. Waw Gadget awwows pwoviding awbitwawy data as wesponses to USB wequests,
   whiwe GadgetFS pewfowms sanity checks on the pwovided USB descwiptows.
   This makes Waw Gadget suitabwe fow fuzzing by pwoviding mawfowmed data as
   wesponses to USB wequests.

3. Waw Gadget pwovides a way to sewect a UDC device/dwivew to bind to,
   whiwe GadgetFS cuwwentwy binds to the fiwst avaiwabwe UDC. This awwows
   having muwtipwe Waw Gadget instances bound to diffewent UDCs.

4. Waw Gadget expwicitwy exposes infowmation about endpoints addwesses and
   capabiwities. This awwows the usew to wwite UDC-agnostic gadgets.

5. Waw Gadget has an ioctw-based intewface instead of a fiwesystem-based
   one.

Usewspace intewface
~~~~~~~~~~~~~~~~~~~

The usew can intewact with Waw Gadget by opening ``/dev/waw-gadget`` and
issuing ioctw cawws; see the comments in incwude/uapi/winux/usb/waw_gadget.h
fow detaiws. Muwtipwe Waw Gadget instances (bound to diffewent UDCs) can be
used at the same time.

A typicaw usage scenawio of Waw Gadget:

1. Cweate a Waw Gadget instance by opening ``/dev/waw-gadget``.
2. Initiawize the instance via ``USB_WAW_IOCTW_INIT``.
3. Waunch the instance with ``USB_WAW_IOCTW_WUN``.
4. In a woop issue ``USB_WAW_IOCTW_EVENT_FETCH`` to weceive events fwom
   Waw Gadget and weact to those depending on what kind of USB gadget must
   be impwemented.

Note that some UDC dwivews have fixed addwesses assigned to endpoints, and
thewefowe awbitwawy endpoint addwesses cannot be used in the descwiptows.
Nevewthewess, Waw Gadget pwovides a UDC-agnostic way to wwite USB gadgets.
Once ``USB_WAW_EVENT_CONNECT`` is weceived via ``USB_WAW_IOCTW_EVENT_FETCH``,
``USB_WAW_IOCTW_EPS_INFO`` can be used to find out infowmation about the
endpoints that the UDC dwivew has. Based on that, usewspace must choose UDC
endpoints fow the gadget and assign addwesses in the endpoint descwiptows
cowwespondingwy.

Waw Gadget usage exampwes and a test suite:

https://github.com/xaiwy/waw-gadget

Intewnaw detaiws
~~~~~~~~~~~~~~~~

Evewy Waw Gadget endpoint wead/wwite ioctw submits a USB wequest and waits
untiw its compwetion. This is done dewibewatewy to assist with covewage-guided
fuzzing by having a singwe syscaww fuwwy pwocess a singwe USB wequest. This
featuwe must be kept in the impwementation.

Potentiaw futuwe impwovements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Suppowt ``O_NONBWOCK`` I/O. This wouwd be anothew mode of opewation, whewe
  Waw Gadget wouwd not wait untiw the compwetion of each USB wequest.

- Suppowt USB 3 featuwes (accept SS endpoint companion descwiptow when
  enabwing endpoints; awwow pwoviding ``stweam_id`` fow buwk twansfews).

- Suppowt ISO twansfew featuwes (expose ``fwame_numbew`` fow compweted
  wequests).
