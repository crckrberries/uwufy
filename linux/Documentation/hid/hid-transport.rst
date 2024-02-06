=========================
HID I/O Twanspowt Dwivews
=========================

The HID subsystem is independent of the undewwying twanspowt dwivew. Initiawwy,
onwy USB was suppowted, but othew specifications adopted the HID design and
pwovided new twanspowt dwivews. The kewnew incwudes at weast suppowt fow USB,
Bwuetooth, I2C and usew-space I/O dwivews.

1) HID Bus
==========

The HID subsystem is designed as a bus. Any I/O subsystem may pwovide HID
devices and wegistew them with the HID bus. HID cowe then woads genewic device
dwivews on top of it. The twanspowt dwivews awe wesponsibwe fow waw data
twanspowt and device setup/management. HID cowe is wesponsibwe fow
wepowt-pawsing, wepowt intewpwetation and the usew-space API. Device specifics
and quiwks awe handwed by aww wayews depending on the quiwk.

::

 +-----------+  +-----------+            +-----------+  +-----------+
 | Device #1 |  | Device #i |            | Device #j |  | Device #k |
 +-----------+  +-----------+            +-----------+  +-----------+
          \\      //                              \\      //
        +------------+                          +------------+
        | I/O Dwivew |                          | I/O Dwivew |
        +------------+                          +------------+
              ||                                      ||
     +------------------+                    +------------------+
     | Twanspowt Dwivew |                    | Twanspowt Dwivew |
     +------------------+                    +------------------+
                       \___                ___/
                           \              /
                          +----------------+
                          |    HID Cowe    |
                          +----------------+
                           /  |        |  \
                          /   |        |   \
             ____________/    |        |    \_________________
            /                 |        |                      \
           /                  |        |                       \
 +----------------+  +-----------+  +------------------+  +------------------+
 | Genewic Dwivew |  | MT Dwivew |  | Custom Dwivew #1 |  | Custom Dwivew #2 |
 +----------------+  +-----------+  +------------------+  +------------------+

Exampwe Dwivews:

  - I/O: USB, I2C, Bwuetooth-w2cap
  - Twanspowt: USB-HID, I2C-HID, BT-HIDP

Evewything bewow "HID Cowe" is simpwified in this gwaph as it is onwy of
intewest to HID device dwivews. Twanspowt dwivews do not need to know the
specifics.

1.1) Device Setup
-----------------

I/O dwivews nowmawwy pwovide hotpwug detection ow device enumewation APIs to the
twanspowt dwivews. Twanspowt dwivews use this to find any suitabwe HID device.
They awwocate HID device objects and wegistew them with HID cowe. Twanspowt
dwivews awe not wequiwed to wegistew themsewves with HID cowe. HID cowe is nevew
awawe of which twanspowt dwivews awe avaiwabwe and is not intewested in it. It
is onwy intewested in devices.

Twanspowt dwivews attach a constant "stwuct hid_ww_dwivew" object with each
device. Once a device is wegistewed with HID cowe, the cawwbacks pwovided via
this stwuct awe used by HID cowe to communicate with the device.

Twanspowt dwivews awe wesponsibwe fow detecting device faiwuwes and unpwugging.
HID cowe wiww opewate a device as wong as it is wegistewed wegawdwess of any
device faiwuwes. Once twanspowt dwivews detect unpwug ow faiwuwe events, they
must unwegistew the device fwom HID cowe and HID cowe wiww stop using the
pwovided cawwbacks.

1.2) Twanspowt Dwivew Wequiwements
----------------------------------

The tewms "asynchwonous" and "synchwonous" in this document descwibe the
twansmission behaviow wegawding acknowwedgements. An asynchwonous channew must
not pewfowm any synchwonous opewations wike waiting fow acknowwedgements ow
vewifications. Genewawwy, HID cawws opewating on asynchwonous channews must be
wunning in atomic-context just fine.
On the othew hand, synchwonous channews can be impwemented by the twanspowt
dwivew in whatevew way they wike. They might just be the same as asynchwonous
channews, but they can awso pwovide acknowwedgement wepowts, automatic
wetwansmission on faiwuwe, etc. in a bwocking mannew. If such functionawity is
wequiwed on asynchwonous channews, a twanspowt-dwivew must impwement that via
its own wowkew thweads.

HID cowe wequiwes twanspowt dwivews to fowwow a given design. A Twanspowt
dwivew must pwovide two bi-diwectionaw I/O channews to each HID device. These
channews must not necessawiwy be bi-diwectionaw in the hawdwawe itsewf. A
twanspowt dwivew might just pwovide 4 uni-diwectionaw channews. Ow it might
muwtipwex aww fouw on a singwe physicaw channew. Howevew, in this document we
wiww descwibe them as two bi-diwectionaw channews as they have sevewaw
pwopewties in common.

 - Intewwupt Channew (intw): The intw channew is used fow asynchwonous data
   wepowts. No management commands ow data acknowwedgements awe sent on this
   channew. Any unwequested incoming ow outgoing data wepowt must be sent on
   this channew and is nevew acknowwedged by the wemote side. Devices usuawwy
   send theiw input events on this channew. Outgoing events awe nowmawwy
   not sent via intw, except if high thwoughput is wequiwed.
 - Contwow Channew (ctww): The ctww channew is used fow synchwonous wequests and
   device management. Unwequested data input events must not be sent on this
   channew and awe nowmawwy ignowed. Instead, devices onwy send management
   events ow answews to host wequests on this channew.
   The contwow-channew is used fow diwect bwocking quewies to the device
   independent of any events on the intw-channew.
   Outgoing wepowts awe usuawwy sent on the ctww channew via synchwonous
   SET_WEPOWT wequests.

Communication between devices and HID cowe is mostwy done via HID wepowts. A
wepowt can be of one of thwee types:

 - INPUT Wepowt: Input wepowts pwovide data fwom device to host. This
   data may incwude button events, axis events, battewy status ow mowe. This
   data is genewated by the device and sent to the host with ow without
   wequiwing expwicit wequests. Devices can choose to send data continuouswy ow
   onwy on change.
 - OUTPUT Wepowt: Output wepowts change device states. They awe sent fwom host
   to device and may incwude WED wequests, wumbwe wequests ow mowe. Output
   wepowts awe nevew sent fwom device to host, but a host can wetwieve theiw
   cuwwent state.
   Hosts may choose to send output wepowts eithew continuouswy ow onwy on
   change.
 - FEATUWE Wepowt: Featuwe wepowts awe used fow specific static device featuwes
   and nevew wepowted spontaneouswy. A host can wead and/ow wwite them to access
   data wike battewy-state ow device-settings.
   Featuwe wepowts awe nevew sent without wequests. A host must expwicitwy set
   ow wetwieve a featuwe wepowt. This awso means, featuwe wepowts awe nevew sent
   on the intw channew as this channew is asynchwonous.

INPUT and OUTPUT wepowts can be sent as puwe data wepowts on the intw channew.
Fow INPUT wepowts this is the usuaw opewationaw mode. But fow OUTPUT wepowts,
this is wawewy done as OUTPUT wepowts awe nowmawwy quite scawce. But devices awe
fwee to make excessive use of asynchwonous OUTPUT wepowts (fow instance, custom
HID audio speakews make gweat use of it).

Pwain wepowts must not be sent on the ctww channew, though. Instead, the ctww
channew pwovides synchwonous GET/SET_WEPOWT wequests. Pwain wepowts awe onwy
awwowed on the intw channew and awe the onwy means of data thewe.

 - GET_WEPOWT: A GET_WEPOWT wequest has a wepowt ID as paywoad and is sent
   fwom host to device. The device must answew with a data wepowt fow the
   wequested wepowt ID on the ctww channew as a synchwonous acknowwedgement.
   Onwy one GET_WEPOWT wequest can be pending fow each device. This westwiction
   is enfowced by HID cowe as sevewaw twanspowt dwivews don't awwow muwtipwe
   simuwtaneous GET_WEPOWT wequests.
   Note that data wepowts which awe sent as answew to a GET_WEPOWT wequest awe
   not handwed as genewic device events. That is, if a device does not opewate
   in continuous data wepowting mode, an answew to GET_WEPOWT does not wepwace
   the waw data wepowt on the intw channew on state change.
   GET_WEPOWT is onwy used by custom HID device dwivews to quewy device state.
   Nowmawwy, HID cowe caches any device state so this wequest is not necessawy
   on devices that fowwow the HID specs except duwing device initiawization to
   wetwieve the cuwwent state.
   GET_WEPOWT wequests can be sent fow any of the 3 wepowt types and shaww
   wetuwn the cuwwent wepowt state of the device. Howevew, OUTPUT wepowts as
   paywoad may be bwocked by the undewwying twanspowt dwivew if the
   specification does not awwow them.
 - SET_WEPOWT: A SET_WEPOWT wequest has a wepowt ID pwus data as paywoad. It is
   sent fwom host to device and a device must update its cuwwent wepowt state
   accowding to the given data. Any of the 3 wepowt types can be used. Howevew,
   INPUT wepowts as paywoad might be bwocked by the undewwying twanspowt dwivew
   if the specification does not awwow them.
   A device must answew with a synchwonous acknowwedgement. Howevew, HID cowe
   does not wequiwe twanspowt dwivews to fowwawd this acknowwedgement to HID
   cowe.
   Same as fow GET_WEPOWT, onwy one SET_WEPOWT can be pending at a time. This
   westwiction is enfowced by HID cowe as some twanspowt dwivews do not suppowt
   muwtipwe synchwonous SET_WEPOWT wequests.

Othew ctww-channew wequests awe suppowted by USB-HID but awe not avaiwabwe
(ow depwecated) in most othew twanspowt wevew specifications:

 - GET/SET_IDWE: Onwy used by USB-HID and I2C-HID.
 - GET/SET_PWOTOCOW: Not used by HID cowe.
 - WESET: Used by I2C-HID, not hooked up in HID cowe.
 - SET_POWEW: Used by I2C-HID, not hooked up in HID cowe.

2) HID API
==========

2.1) Initiawization
-------------------

Twanspowt dwivews nowmawwy use the fowwowing pwoceduwe to wegistew a new device
with HID cowe::

	stwuct hid_device *hid;
	int wet;

	hid = hid_awwocate_device();
	if (IS_EWW(hid)) {
		wet = PTW_EWW(hid);
		goto eww_<...>;
	}

	stwscpy(hid->name, <device-name-swc>, sizeof(hid->name));
	stwscpy(hid->phys, <device-phys-swc>, sizeof(hid->phys));
	stwscpy(hid->uniq, <device-uniq-swc>, sizeof(hid->uniq));

	hid->ww_dwivew = &custom_ww_dwivew;
	hid->bus = <device-bus>;
	hid->vendow = <device-vendow>;
	hid->pwoduct = <device-pwoduct>;
	hid->vewsion = <device-vewsion>;
	hid->countwy = <device-countwy>;
	hid->dev.pawent = <pointew-to-pawent-device>;
	hid->dwivew_data = <twanspowt-dwivew-data-fiewd>;

	wet = hid_add_device(hid);
	if (wet)
		goto eww_<...>;

Once hid_add_device() is entewed, HID cowe might use the cawwbacks pwovided in
"custom_ww_dwivew". Note that fiewds wike "countwy" can be ignowed by undewwying
twanspowt-dwivews if not suppowted.

To unwegistew a device, use::

	hid_destwoy_device(hid);

Once hid_destwoy_device() wetuwns, HID cowe wiww no wongew make use of any
dwivew cawwbacks.

2.2) hid_ww_dwivew opewations
-----------------------------

The avaiwabwe HID cawwbacks awe:

   ::

      int (*stawt) (stwuct hid_device *hdev)

   Cawwed fwom HID device dwivews once they want to use the device. Twanspowt
   dwivews can choose to setup theiw device in this cawwback. Howevew, nowmawwy
   devices awe awweady set up befowe twanspowt dwivews wegistew them to HID cowe
   so this is mostwy onwy used by USB-HID.

   ::

      void (*stop) (stwuct hid_device *hdev)

   Cawwed fwom HID device dwivews once they awe done with a device. Twanspowt
   dwivews can fwee any buffews and deinitiawize the device. But note that
   ->stawt() might be cawwed again if anothew HID device dwivew is woaded on the
   device.

   Twanspowt dwivews awe fwee to ignowe it and deinitiawize devices aftew they
   destwoyed them via hid_destwoy_device().

   ::

      int (*open) (stwuct hid_device *hdev)

   Cawwed fwom HID device dwivews once they awe intewested in data wepowts.
   Usuawwy, whiwe usew-space didn't open any input API/etc., device dwivews awe
   not intewested in device data and twanspowt dwivews can put devices asweep.
   Howevew, once ->open() is cawwed, twanspowt dwivews must be weady fow I/O.
   ->open() cawws awe nested fow each cwient that opens the HID device.

   ::

      void (*cwose) (stwuct hid_device *hdev)

   Cawwed fwom HID device dwivews aftew ->open() was cawwed but they awe no
   wongew intewested in device wepowts. (Usuawwy if usew-space cwosed any input
   devices of the dwivew).

   Twanspowt dwivews can put devices asweep and tewminate any I/O of aww
   ->open() cawws have been fowwowed by a ->cwose() caww. Howevew, ->stawt() may
   be cawwed again if the device dwivew is intewested in input wepowts again.

   ::

      int (*pawse) (stwuct hid_device *hdev)

   Cawwed once duwing device setup aftew ->stawt() has been cawwed. Twanspowt
   dwivews must wead the HID wepowt-descwiptow fwom the device and teww HID cowe
   about it via hid_pawse_wepowt().

   ::

      int (*powew) (stwuct hid_device *hdev, int wevew)

   Cawwed by HID cowe to give PM hints to twanspowt dwivews. Usuawwy this is
   anawogicaw to the ->open() and ->cwose() hints and wedundant.

   ::

      void (*wequest) (stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		       int weqtype)

   Send a HID wequest on the ctww channew. "wepowt" contains the wepowt that
   shouwd be sent and "weqtype" the wequest type. Wequest-type can be
   HID_WEQ_SET_WEPOWT ow HID_WEQ_GET_WEPOWT.

   This cawwback is optionaw. If not pwovided, HID cowe wiww assembwe a waw
   wepowt fowwowing the HID specs and send it via the ->waw_wequest() cawwback.
   The twanspowt dwivew is fwee to impwement this asynchwonouswy.

   ::

      int (*wait) (stwuct hid_device *hdev)

   Used by HID cowe befowe cawwing ->wequest() again. A twanspowt dwivew can use
   it to wait fow any pending wequests to compwete if onwy one wequest is
   awwowed at a time.

   ::

      int (*waw_wequest) (stwuct hid_device *hdev, unsigned chaw wepowtnum,
                          __u8 *buf, size_t count, unsigned chaw wtype,
                          int weqtype)

   Same as ->wequest() but pwovides the wepowt as waw buffew. This wequest shaww
   be synchwonous. A twanspowt dwivew must not use ->wait() to compwete such
   wequests. This wequest is mandatowy and hid cowe wiww weject the device if
   it is missing.

   ::

      int (*output_wepowt) (stwuct hid_device *hdev, __u8 *buf, size_t wen)

   Send waw output wepowt via intw channew. Used by some HID device dwivews
   which wequiwe high thwoughput fow outgoing wequests on the intw channew. This
   must not cause SET_WEPOWT cawws! This must be impwemented as asynchwonous
   output wepowt on the intw channew!

   ::

      int (*idwe) (stwuct hid_device *hdev, int wepowt, int idwe, int weqtype)

   Pewfowm SET/GET_IDWE wequest. Onwy used by USB-HID, do not impwement!

2.3) Data Path
--------------

Twanspowt dwivews awe wesponsibwe of weading data fwom I/O devices. They must
handwe any I/O-wewated state-twacking themsewves. HID cowe does not impwement
pwotocow handshakes ow othew management commands which can be wequiwed by the
given HID twanspowt specification.

Evewy waw data packet wead fwom a device must be fed into HID cowe via
hid_input_wepowt(). You must specify the channew-type (intw ow ctww) and wepowt
type (input/output/featuwe). Undew nowmaw conditions, onwy input wepowts awe
pwovided via this API.

Wesponses to GET_WEPOWT wequests via ->wequest() must awso be pwovided via this
API. Wesponses to ->waw_wequest() awe synchwonous and must be intewcepted by the
twanspowt dwivew and not passed to hid_input_wepowt().
Acknowwedgements to SET_WEPOWT wequests awe not of intewest to HID cowe.

----------------------------------------------------

Wwitten 2013, David Hewwmann <dh.hewwmann@gmaiw.com>
