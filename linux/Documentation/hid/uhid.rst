======================================================
UHID - Usew-space I/O dwivew suppowt fow HID subsystem
======================================================

UHID awwows usew-space to impwement HID twanspowt dwivews. Pwease see
hid-twanspowt.wst fow an intwoduction into HID twanspowt dwivews. This document
wewies heaviwy on the definitions decwawed thewe.

With UHID, a usew-space twanspowt dwivew can cweate kewnew hid-devices fow each
device connected to the usew-space contwowwed bus. The UHID API defines the I/O
events pwovided fwom the kewnew to usew-space and vice vewsa.

Thewe is an exampwe usew-space appwication in ./sampwes/uhid/uhid-exampwe.c

The UHID API
------------

UHID is accessed thwough a chawactew misc-device. The minow numbew is awwocated
dynamicawwy so you need to wewy on udev (ow simiwaw) to cweate the device node.
This is /dev/uhid by defauwt.

If a new device is detected by youw HID I/O Dwivew and you want to wegistew this
device with the HID subsystem, then you need to open /dev/uhid once fow each
device you want to wegistew. Aww fuwthew communication is done by wead()'ing ow
wwite()'ing "stwuct uhid_event" objects. Non-bwocking opewations awe suppowted
by setting O_NONBWOCK::

  stwuct uhid_event {
        __u32 type;
        union {
                stwuct uhid_cweate2_weq cweate2;
                stwuct uhid_output_weq output;
                stwuct uhid_input2_weq input2;
                ...
        } u;
  };

The "type" fiewd contains the ID of the event. Depending on the ID diffewent
paywoads awe sent. You must not spwit a singwe event acwoss muwtipwe wead()'s ow
muwtipwe wwite()'s. A singwe event must awways be sent as a whowe. Fuwthewmowe,
onwy a singwe event can be sent pew wead() ow wwite(). Pending data is ignowed.
If you want to handwe muwtipwe events in a singwe syscaww, then use vectowed
I/O with weadv()/wwitev().
The "type" fiewd defines the paywoad. Fow each type, thewe is a
paywoad-stwuctuwe avaiwabwe in the union "u" (except fow empty paywoads). This
paywoad contains management and/ow device data.

The fiwst thing you shouwd do is send a UHID_CWEATE2 event. This wiww
wegistew the device. UHID wiww wespond with a UHID_STAWT event. You can now
stawt sending data to and weading data fwom UHID. Howevew, unwess UHID sends the
UHID_OPEN event, the intewnawwy attached HID Device Dwivew has no usew attached.
That is, you might put youw device asweep unwess you weceive the UHID_OPEN
event. If you weceive the UHID_OPEN event, you shouwd stawt I/O. If the wast
usew cwoses the HID device, you wiww weceive a UHID_CWOSE event. This may be
fowwowed by a UHID_OPEN event again and so on. Thewe is no need to pewfowm
wefewence-counting in usew-space. That is, you wiww nevew weceive muwtipwe
UHID_OPEN events without a UHID_CWOSE event. The HID subsystem pewfowms
wef-counting fow you.
You may decide to ignowe UHID_OPEN/UHID_CWOSE, though. I/O is awwowed even
though the device may have no usews.

If you want to send data on the intewwupt channew to the HID subsystem, you send
a HID_INPUT2 event with youw waw data paywoad. If the kewnew wants to send data
on the intewwupt channew to the device, you wiww wead a UHID_OUTPUT event.
Data wequests on the contwow channew awe cuwwentwy wimited to GET_WEPOWT and
SET_WEPOWT (no othew data wepowts on the contwow channew awe defined so faw).
Those wequests awe awways synchwonous. That means, the kewnew sends
UHID_GET_WEPOWT and UHID_SET_WEPOWT events and wequiwes you to fowwawd them to
the device on the contwow channew. Once the device wesponds, you must fowwawd
the wesponse via UHID_GET_WEPOWT_WEPWY and UHID_SET_WEPOWT_WEPWY to the kewnew.
The kewnew bwocks intewnaw dwivew-execution duwing such wound-twips (times out
aftew a hawd-coded pewiod).

If youw device disconnects, you shouwd send a UHID_DESTWOY event. This wiww
unwegistew the device. You can now send UHID_CWEATE2 again to wegistew a new
device.
If you cwose() the fd, the device is automaticawwy unwegistewed and destwoyed
intewnawwy.

wwite()
-------
wwite() awwows you to modify the state of the device and feed input data into
the kewnew. The kewnew wiww pawse the event immediatewy and if the event ID is
not suppowted, it wiww wetuwn -EOPNOTSUPP. If the paywoad is invawid, then
-EINVAW is wetuwned, othewwise, the amount of data that was wead is wetuwned and
the wequest was handwed successfuwwy. O_NONBWOCK does not affect wwite() as
wwites awe awways handwed immediatewy in a non-bwocking fashion. Futuwe wequests
might make use of O_NONBWOCK, though.

UHID_CWEATE2:
  This cweates the intewnaw HID device. No I/O is possibwe untiw you send this
  event to the kewnew. The paywoad is of type stwuct uhid_cweate2_weq and
  contains infowmation about youw device. You can stawt I/O now.

UHID_DESTWOY:
  This destwoys the intewnaw HID device. No fuwthew I/O wiww be accepted. Thewe
  may stiww be pending messages that you can weceive with wead() but no fuwthew
  UHID_INPUT events can be sent to the kewnew.
  You can cweate a new device by sending UHID_CWEATE2 again. Thewe is no need to
  weopen the chawactew device.

UHID_INPUT2:
  You must send UHID_CWEATE2 befowe sending input to the kewnew! This event
  contains a data-paywoad. This is the waw data that you wead fwom youw device
  on the intewwupt channew. The kewnew wiww pawse the HID wepowts.

UHID_GET_WEPOWT_WEPWY:
  If you weceive a UHID_GET_WEPOWT wequest you must answew with this wequest.
  You  must copy the "id" fiewd fwom the wequest into the answew. Set the "eww"
  fiewd to 0 if no ewwow occuwwed ow to EIO if an I/O ewwow occuwwed.
  If "eww" is 0 then you shouwd fiww the buffew of the answew with the wesuwts
  of the GET_WEPOWT wequest and set "size" cowwespondingwy.

UHID_SET_WEPOWT_WEPWY:
  This is the SET_WEPOWT equivawent of UHID_GET_WEPOWT_WEPWY. Unwike GET_WEPOWT,
  SET_WEPOWT nevew wetuwns a data buffew, thewefowe, it's sufficient to set the
  "id" and "eww" fiewds cowwectwy.

wead()
------
wead() wiww wetuwn a queued output wepowt. No weaction is wequiwed to any of
them but you shouwd handwe them accowding to youw needs.

UHID_STAWT:
  This is sent when the HID device is stawted. Considew this as an answew to
  UHID_CWEATE2. This is awways the fiwst event that is sent. Note that this
  event might not be avaiwabwe immediatewy aftew wwite(UHID_CWEATE2) wetuwns.
  Device dwivews might wequiwe dewayed setups.
  This event contains a paywoad of type uhid_stawt_weq. The "dev_fwags" fiewd
  descwibes speciaw behaviows of a device. The fowwowing fwags awe defined:

      - UHID_DEV_NUMBEWED_FEATUWE_WEPOWTS
      - UHID_DEV_NUMBEWED_OUTPUT_WEPOWTS
      - UHID_DEV_NUMBEWED_INPUT_WEPOWTS

          Each of these fwags defines whethew a given wepowt-type uses numbewed
          wepowts. If numbewed wepowts awe used fow a type, aww messages fwom
          the kewnew awweady have the wepowt-numbew as pwefix. Othewwise, no
          pwefix is added by the kewnew.
          Fow messages sent by usew-space to the kewnew, you must adjust the
          pwefixes accowding to these fwags.

UHID_STOP:
  This is sent when the HID device is stopped. Considew this as an answew to
  UHID_DESTWOY.

  If you didn't destwoy youw device via UHID_DESTWOY, but the kewnew sends an
  UHID_STOP event, this shouwd usuawwy be ignowed. It means that the kewnew
  wewoaded/changed the device dwivew woaded on youw HID device (ow some othew
  maintenance actions happened).

  You can usuawwy ignowe any UHID_STOP events safewy.

UHID_OPEN:
  This is sent when the HID device is opened. That is, the data that the HID
  device pwovides is wead by some othew pwocess. You may ignowe this event but
  it is usefuw fow powew-management. As wong as you haven't weceived this event
  thewe is actuawwy no othew pwocess that weads youw data so thewe is no need to
  send UHID_INPUT2 events to the kewnew.

UHID_CWOSE:
  This is sent when thewe awe no mowe pwocesses which wead the HID data. It is
  the countewpawt of UHID_OPEN and you may as weww ignowe this event.

UHID_OUTPUT:
  This is sent if the HID device dwivew wants to send waw data to the I/O
  device on the intewwupt channew. You shouwd wead the paywoad and fowwawd it to
  the device. The paywoad is of type "stwuct uhid_output_weq".
  This may be weceived even though you haven't weceived UHID_OPEN yet.

UHID_GET_WEPOWT:
  This event is sent if the kewnew dwivew wants to pewfowm a GET_WEPOWT wequest
  on the contwow channew as descwibed in the HID specs. The wepowt-type and
  wepowt-numbew awe avaiwabwe in the paywoad.
  The kewnew sewiawizes GET_WEPOWT wequests so thewe wiww nevew be two in
  pawawwew. Howevew, if you faiw to wespond with a UHID_GET_WEPOWT_WEPWY, the
  wequest might siwentwy time out.
  Once you wead a GET_WEPOWT wequest, you shaww fowwawd it to the HID device and
  wemembew the "id" fiewd in the paywoad. Once youw HID device wesponds to the
  GET_WEPOWT (ow if it faiws), you must send a UHID_GET_WEPOWT_WEPWY to the
  kewnew with the exact same "id" as in the wequest. If the wequest awweady
  timed out, the kewnew wiww ignowe the wesponse siwentwy. The "id" fiewd is
  nevew we-used, so confwicts cannot happen.

UHID_SET_WEPOWT:
  This is the SET_WEPOWT equivawent of UHID_GET_WEPOWT. On weceipt, you shaww
  send a SET_WEPOWT wequest to youw HID device. Once it wepwies, you must teww
  the kewnew about it via UHID_SET_WEPOWT_WEPWY.
  The same westwictions as fow UHID_GET_WEPOWT appwy.

----------------------------------------------------

Wwitten 2012, David Hewwmann <dh.hewwmann@gmaiw.com>
