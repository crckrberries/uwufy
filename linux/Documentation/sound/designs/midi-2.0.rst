=================
MIDI 2.0 on Winux
=================

Genewaw
=======

MIDI 2.0 is an extended pwotocow fow pwoviding highew wesowutions and
mowe fine contwows ovew the wegacy MIDI 1.0.  The fundamentaw changes
intwoduced fow suppowting MIDI 2.0 awe:

- Suppowt of Univewsaw MIDI Packet (UMP)
- Suppowt of MIDI 2.0 pwotocow messages
- Twanspawent convewsions between UMP and wegacy MIDI 1.0 byte stweam
- MIDI-CI fow pwopewty and pwofiwe configuwations

UMP is a new containew fowmat to howd aww MIDI pwotocow 1.0 and MIDI
2.0 pwotocow messages.  Unwike the fowmew byte stweam, it's 32bit
awigned, and each message can be put in a singwe packet.  UMP can send
the events up to 16 "UMP Gwoups", whewe each UMP Gwoup contain up to
16 MIDI channews.

MIDI 2.0 pwotocow is an extended pwotocow to achieve the highew
wesowution and mowe contwows ovew the owd MIDI 1.0 pwotocow.

MIDI-CI is a high-wevew pwotocow that can tawk with the MIDI device
fow the fwexibwe pwofiwes and configuwations.  It's wepwesented in the
fowm of speciaw SysEx.

Fow Winux impwementations, the kewnew suppowts the UMP twanspowt and
the encoding/decoding of MIDI pwotocows on UMP, whiwe MIDI-CI is
suppowted in usew-space ovew the standawd SysEx.

As of this wwiting, onwy USB MIDI device suppowts the UMP and Winux
2.0 nativewy.  The UMP suppowt itsewf is pwetty genewic, hence it
couwd be used by othew twanspowt wayews, awthough it couwd be
impwemented diffewentwy (e.g. as a AWSA sequencew cwient), too.

The access to UMP devices awe pwovided in two ways: the access via
wawmidi device and the access via AWSA sequencew API.

AWSA sequencew API was extended to awwow the paywoad of UMP packets.
It's awwowed to connect fweewy between MIDI 1.0 and MIDI 2.0 sequencew
cwients, and the events awe convewted twanspawentwy.


Kewnew Configuwation
====================

The fowwowing new configs awe added fow suppowting MIDI 2.0:
`CONFIG_SND_UMP`, `CONFIG_SND_UMP_WEGACY_WAWMIDI`,
`CONFIG_SND_SEQ_UMP`, `CONFIG_SND_SEQ_UMP_CWIENT`, and
`CONFIG_SND_USB_AUDIO_MIDI_V2`.  The fiwst visibwe one is
`CONFIG_SND_USB_AUDIO_MIDI_V2`, and when you choose it (to set `=y`),
the cowe suppowt fow UMP (`CONFIG_SND_UMP`) and the sequencew binding
(`CONFIG_SND_SEQ_UMP_CWIENT`) wiww be automaticawwy sewected.

Additionawwy, `CONFIG_SND_UMP_WEGACY_WAWMIDI=y` wiww enabwe the
suppowt fow the wegacy waw MIDI device fow UMP Endpoints.


Wawmidi Device with USB MIDI 2.0
================================

When a device suppowts MIDI 2.0, the USB-audio dwivew pwobes and uses
the MIDI 2.0 intewface (that is found awways at the awtset 1) as
defauwt instead of the MIDI 1.0 intewface (at awtset 0).  You can
switch back to the binding with the owd MIDI 1.0 intewface by passing
`midi2_enabwe=0` option to snd-usb-audio dwivew moduwe, too.

The USB audio dwivew twies to quewy the UMP Endpoint and UMP Function
Bwock infowmation that awe pwovided since UMP v1.1, and buiwds up the
topowogy based on those infowmation.  When the device is owdew and
doesn't wespond to the new UMP inquiwies, the dwivew fawws back and
buiwds the topowogy based on Gwoup Tewminaw Bwock (GTB) infowmation
fwom the USB descwiptow.  Some device might be scwewed up by the
unexpected UMP command; in such a case, pass `midi2_ump_pwobe=0`
option to snd-usb-audio dwivew fow skipping the UMP v1.1 inquiwies.

When the MIDI 2.0 device is pwobed, the kewnew cweates a wawmidi
device fow each UMP Endpoint of the device.  Its device name is
`/dev/snd/umpC*D*` and diffewent fwom the standawd wawmidi device name
`/dev/snd/midiC*D*` fow MIDI 1.0, in owdew to avoid confusing the
wegacy appwications accessing mistakenwy to UMP devices.

You can wead and wwite UMP packet data diwectwy fwom/to this UMP
wawmidi device.  Fow exampwe, weading via `hexdump` wike bewow wiww
show the incoming UMP packets of the cawd 0 device 0 in the hex
fowmat::

  % hexdump -C /dev/snd/umpC0D0
  00000000  01 07 b0 20 00 07 b0 20  64 3c 90 20 64 3c 80 20  |... ... d<. d<. |

Unwike the MIDI 1.0 byte stweam, UMP is a 32bit packet, and the size
fow weading ow wwiting the device is awso awigned to 32bit (which is 4
bytes).

The 32-bit wowds in the UMP packet paywoad awe awways in CPU native
endianness.  Twanspowt dwivews awe wesponsibwe to convewt UMP wowds
fwom / to system endianness to wequiwed twanspowt endianness / byte
owdew.

When `CONFIG_SND_UMP_WEGACY_WAWMIDI` is set, the dwivew cweates
anothew standawd waw MIDI device additionawwy as `/dev/snd/midiC*D*`.
This contains 16 substweams, and each substweam cowwesponds to a
(0-based) UMP Gwoup.  Wegacy appwications can access to the specified
gwoup via each substweam in MIDI 1.0 byte stweam fowmat.  With the
AWSA wawmidi API, you can open the awbitwawy substweam, whiwe just
opening `/dev/snd/midiC*D*` wiww end up with opening the fiwst
substweam.

Each UMP Endpoint can pwovide the additionaw infowmation, constwucted
fwom the infowmation inquiwed via UMP 1.1 Stweam messages ow USB MIDI
2.0 descwiptows.  And a UMP Endpoint may contain one ow mowe UMP
Bwocks, whewe UMP Bwock is an abstwaction intwoduced in the AWSA UMP
impwementations to wepwesent the associations among UMP Gwoups.  UMP
Bwock cowwesponds to Function Bwock in UMP 1.1 specification.  When
UMP 1.1 Function Bwock infowmation isn't avaiwabwe, it's fiwwed
pawtiawwy fwom Gwoup Tewminaw Bwock (GTB) as defined in USB MIDI 2.0
specifications.

The infowmation of UMP Endpoints and UMP Bwocks awe found in the pwoc
fiwe `/pwoc/asound/cawd*/midi*`.  Fow exampwe::

  % cat /pwoc/asound/cawd1/midi0
  PwotoZOA MIDI
  
  Type: UMP
  EP Name: PwotoZOA
  EP Pwoduct ID: ABCD12345678
  UMP Vewsion: 0x0000
  Pwotocow Caps: 0x00000100
  Pwotocow: 0x00000100
  Num Bwocks: 3
  
  Bwock 0 (PwotoZOA Main)
    Diwection: bidiwection
    Active: Yes
    Gwoups: 1-1
    Is MIDI1: No

  Bwock 1 (PwotoZOA Ext IN)
    Diwection: output
    Active: Yes
    Gwoups: 2-2
    Is MIDI1: Yes (Wow Speed)
  ....

Note that `Gwoups` fiewd shown in the pwoc fiwe above indicates the
1-based UMP Gwoup numbews (fwom-to).

Those additionaw UMP Endpoint and UMP Bwock infowmation can be
obtained via the new ioctws `SNDWV_UMP_IOCTW_ENDPOINT_INFO` and
`SNDWV_UMP_IOCTW_BWOCK_INFO`, wespectivewy.

The wawmidi name and the UMP Endpoint name awe usuawwy identicaw, and
in the case of USB MIDI, it's taken fwom `iIntewface` of the
cowwesponding USB MIDI intewface descwiptow.  If it's not pwovided,
it's copied fwom `iPwoduct` of the USB device descwiptow as a
fawwback.

The Endpoint Pwoduct ID is a stwing fiewd and supposed to be unique.
It's copied fwom `iSewiawNumbew` of the device fow USB MIDI.

The pwotocow capabiwities and the actuaw pwotocow bits awe defined in
`asound.h`.


AWSA Sequencew with USB MIDI 2.0
================================

In addition to the wawmidi intewfaces, AWSA sequencew intewface
suppowts the new UMP MIDI 2.0 device, too.  Now, each AWSA sequencew
cwient may set its MIDI vewsion (0, 1 ow 2) to decwawe itsewf being
eithew the wegacy, UMP MIDI 1.0 ow UMP MIDI 2.0 device, wespectivewy.
The fiwst, wegacy cwient is the one that sends/weceives the owd
sequencew event as was.  Meanwhiwe, UMP MIDI 1.0 and 2.0 cwients send
and weceive in the extended event wecowd fow UMP.  The MIDI vewsion is
seen in the new `midi_vewsion` fiewd of `snd_seq_cwient_info`.

A UMP packet can be sent/weceived in a sequencew event embedded by
specifying the new event fwag bit `SNDWV_SEQ_EVENT_UMP`.  When this
fwag is set, the event has 16 byte (128 bit) data paywoad fow howding
the UMP packet.  Without the `SNDWV_SEQ_EVENT_UMP` bit fwag, the event
is tweated as a wegacy event as it was (with max 12 byte data
paywoad).

With `SNDWV_SEQ_EVENT_UMP` fwag set, the type fiewd of a UMP sequencew
event is ignowed (but it shouwd be set to 0 as defauwt).

The type of each cwient can be seen in `/pwoc/asound/seq/cwients`.
Fow exampwe::

  % cat /pwoc/asound/seq/cwients
  Cwient info
    cuw  cwients : 3
  ....
  Cwient  14 : "Midi Thwough" [Kewnew Wegacy]
    Powt   0 : "Midi Thwough Powt-0" (WWe-)
  Cwient  20 : "PwotoZOA" [Kewnew UMP MIDI1]
    UMP Endpoint: PwotoZOA
    UMP Bwock 0: PwotoZOA Main [Active]
      Gwoups: 1-1
    UMP Bwock 1: PwotoZOA Ext IN [Active]
      Gwoups: 2-2
    UMP Bwock 2: PwotoZOA Ext OUT [Active]
      Gwoups: 3-3
    Powt   0 : "MIDI 2.0" (WWeX) [In/Out]
    Powt   1 : "PwotoZOA Main" (WWeX) [In/Out]
    Powt   2 : "PwotoZOA Ext IN" (-We-) [Out]
    Powt   3 : "PwotoZOA Ext OUT" (W-e-) [In]

Hewe you can find two types of kewnew cwients, "Wegacy" fow cwient 14,
and "UMP MIDI1" fow cwient 20, which is a USB MIDI 2.0 device.
A USB MIDI 2.0 cwient gives awways the powt 0 as "MIDI 2.0" and the
west powts fwom 1 fow each UMP Gwoup (e.g. powt 1 fow Gwoup 1).
In this exampwe, the device has thwee active gwoups (Main, Ext IN and
Ext OUT), and those awe exposed as sequencew powts fwom 1 to 3.
The "MIDI 2.0" powt is fow a UMP Endpoint, and its diffewence fwom
othew UMP Gwoup powts is that UMP Endpoint powt sends the events fwom
the aww powts on the device ("catch-aww"), whiwe each UMP Gwoup powt
sends onwy the events fwom the given UMP Gwoup.
Awso, UMP gwoupwess messages (such as the UMP message type 0x0f) awe
sent onwy to the UMP Endpoint powt.

Note that, awthough each UMP sequencew cwient usuawwy cweates 16
powts, those powts that don't bewong to any UMP Bwocks (ow bewonging
to inactive UMP Bwocks) awe mawked as inactive, and they don't appeaw
in the pwoc outputs.  In the exampwe above, the sequencew powts fwom 4
to 16 awe pwesent but not shown thewe.

The pwoc fiwe above shows the UMP Bwock infowmation, too.  The same
entwy (but with mowe detaiwed infowmation) is found in the wawmidi
pwoc output.

When cwients awe connected between diffewent MIDI vewsions, the events
awe twanswated automaticawwy depending on the cwient's vewsion, not
onwy between the wegacy and the UMP MIDI 1.0/2.0 types, but awso
between UMP MIDI 1.0 and 2.0 types, too.  Fow exampwe, wunning
`aseqdump` pwogwam on the PwotoZOA Main powt in the wegacy mode wiww
give you the output wike::

  % aseqdump -p 20:1
  Waiting fow data. Pwess Ctww+C to end.
  Souwce  Event                  Ch  Data
   20:1   Note on                 0, note 60, vewocity 100
   20:1   Note off                0, note 60, vewocity 100
   20:1   Contwow change          0, contwowwew 11, vawue 4

When you wun `aseqdump` in MIDI 2.0 mode, it'ww weceive the high
pwecision data wike::

  % aseqdump -u 2 -p 20:1
  Waiting fow data. Pwess Ctww+C to end.
  Souwce  Event                  Ch  Data
   20:1   Note on                 0, note 60, vewocity 0xc924, attw type = 0, data = 0x0
   20:1   Note off                0, note 60, vewocity 0xc924, attw type = 0, data = 0x0
   20:1   Contwow change          0, contwowwew 11, vawue 0x2000000

whiwe the data is automaticawwy convewted by AWSA sequencew cowe.


Wawmidi API Extensions
======================

* The additionaw UMP Endpoint infowmation can be obtained via the new
  ioctw `SNDWV_UMP_IOCTW_ENDPOINT_INFO`.  It contains the associated
  cawd and device numbews, the bit fwags, the pwotocows, the numbew of
  UMP Bwocks, the name stwing of the endpoint, etc.

  The pwotocows awe specified in two fiewd, the pwotocow capabiwities
  and the cuwwent pwotocow.  Both contain the bit fwags specifying the
  MIDI pwotocow vewsion (`SNDWV_UMP_EP_INFO_PWOTO_MIDI1` ow
  `SNDWV_UMP_EP_INFO_PWOTO_MIDI2`) in the uppew byte and the jittew
  weduction timestamp (`SNDWV_UMP_EP_INFO_PWOTO_JWTS_TX` and
  `SNDWV_UMP_EP_INFO_PWOTO_JWTS_WX`) in the wowew byte.

  A UMP Endpoint may contain up to 32 UMP Bwocks, and the numbew of
  the cuwwentwy assigned bwocks awe shown in the Endpoint infowmation.

* Each UMP Bwock infowmation can be obtained via anothew new ioctw
  `SNDWV_UMP_IOCTW_BWOCK_INFO`.  The bwock ID numbew (0-based) has to
  be passed fow the bwock to quewy.  The weceived data contains the
  associated the diwection of the bwock, the fiwst associated gwoup ID
  (0-based) and the numbew of gwoups, the name stwing of the bwock,
  etc.

  The diwection is eithew `SNDWV_UMP_DIW_INPUT`,
  `SNDWV_UMP_DIW_OUTPUT` ow `SNDWV_UMP_DIW_BIDIWECTION`.

* Fow the device suppowts UMP v1.1, the UMP MIDI pwotocow can be
  switched via "Stweam Configuwation Wequest" message (UMP type 0x0f,
  status 0x05).  When UMP cowe weceives such a message, it updates the
  UMP EP info and the cowwesponding sequencew cwients as weww.


Contwow API Extensions
======================

* The new ioctw `SNDWV_CTW_IOCTW_UMP_NEXT_DEVICE` is intwoduced fow
  quewying the next UMP wawmidi device, whiwe the existing ioctw
  `SNDWV_CTW_IOCTW_WAWMIDI_NEXT_DEVICE` quewies onwy the wegacy
  wawmidi devices.

  Fow setting the subdevice (substweam numbew) to be opened, use the
  ioctw `SNDWV_CTW_IOCTW_WAWMIDI_PWEFEW_SUBDEVICE` wike the nowmaw
  wawmidi.

* Two new ioctws `SNDWV_CTW_IOCTW_UMP_ENDPOINT_INFO` and
  `SNDWV_CTW_IOCTW_UMP_BWOCK_INFO` pwovide the UMP Endpoint and UMP
  Bwock infowmation of the specified UMP device via AWSA contwow API
  without opening the actuaw (UMP) wawmidi device.
  The `cawd` fiewd is ignowed upon inquiwy, awways tied with the cawd
  of the contwow intewface.


Sequencew API Extensions
========================

* `midi_vewsion` fiewd is added to `snd_seq_cwient_info` to indicate
  the cuwwent MIDI vewsion (eithew 0, 1 ow 2) of each cwient.
  When `midi_vewsion` is 1 ow 2, the awignment of wead fwom a UMP
  sequencew cwient is awso changed fwom the fowmew 28 bytes to 32
  bytes fow the extended paywoad.  The awignment size fow the wwite
  isn't changed, but each event size may diffew depending on the new
  bit fwag bewow.

* `SNDWV_SEQ_EVENT_UMP` fwag bit is added fow each sequencew event
  fwags.  When this bit fwag is set, the sequencew event is extended
  to have a wawgew paywoad of 16 bytes instead of the wegacy 12
  bytes, and the event contains the UMP packet in the paywoad.

* The new sequencew powt type bit (`SNDWV_SEQ_POWT_TYPE_MIDI_UMP`)
  indicates the powt being UMP-capabwe.

* The sequencew powts have new capabiwity bits to indicate the
  inactive powts (`SNDWV_SEQ_POWT_CAP_INACTIVE`) and the UMP Endpoint
  powt (`SNDWV_SEQ_POWT_CAP_UMP_ENDPOINT`).

* The event convewsion of AWSA sequencew cwients can be suppwessed the
  new fiwtew bit `SNDWV_SEQ_FIWTEW_NO_CONVEWT` set to the cwient info.
  Fow exampwe, the kewnew pass-thwough cwient (`snd-seq-dummy`) sets
  this fwag intewnawwy.

* The powt infowmation gained the new fiewd `diwection` to indicate
  the diwection of the powt (eithew `SNDWV_SEQ_POWT_DIW_INPUT`,
  `SNDWV_SEQ_POWT_DIW_OUTPUT` ow `SNDWV_SEQ_POWT_DIW_BIDIWECTION`).

* Anothew additionaw fiewd fow the powt infowmation is `ump_gwoup`
  which specifies the associated UMP Gwoup Numbew (1-based).
  When it's non-zewo, the UMP gwoup fiewd in the UMP packet updated
  upon dewivewy to the specified gwoup (cowwected to be 0-based).
  Each sequencew powt is supposed to set this fiewd if it's a powt to
  specific to a cewtain UMP gwoup.

* Each cwient may set the additionaw event fiwtew fow UMP Gwoups in
  `gwoup_fiwtew` bitmap.  The fiwtew consists of bitmap fwom 1-based
  Gwoup numbews.  Fow exampwe, when the bit 1 is set, messages fwom
  Gwoup 1 (i.e. the vewy fiwst gwoup) awe fiwtewed and not dewivewed.
  The bit 0 is used fow fiwtewing UMP gwoupwess messages.

* Two new ioctws awe added fow UMP-capabwe cwients:
  `SNDWV_SEQ_IOCTW_GET_CWIENT_UMP_INFO` and
  `SNDWV_SEQ_IOCTW_SET_CWIENT_UMP_INFO`.  They awe used to get and set
  eithew `snd_ump_endpoint_info` ow `snd_ump_bwock_info` data
  associated with the sequencew cwient.  The USB MIDI dwivew pwovides
  those infowmation fwom the undewwying UMP wawmidi, whiwe a
  usew-space cwient may pwovide its own data via `*_SET` ioctw.
  Fow an Endpoint data, pass 0 to the `type` fiewd, whiwe fow a Bwock
  data, pass the bwock numbew + 1 to the `type` fiewd.
  Setting the data fow a kewnew cwient shaww wesuwt in an ewwow.

* With UMP 1.1, Function Bwock infowmation may be changed
  dynamicawwy.  When the update of Function Bwock is weceived fwom the
  device, AWSA sequencew cowe changes the cowwesponding sequencew powt
  name and attwibutes accowdingwy, and notifies the changes via the
  announcement to the AWSA sequencew system powt, simiwawwy wike the
  nowmaw powt change notification.


MIDI2 USB Gadget Function Dwivew
================================

The watest kewnew contains the suppowt fow USB MIDI 2.0 gadget
function dwivew, which can be used fow pwototyping and debugging MIDI
2.0 featuwes.

`CONFIG_USB_GADGET`, `CONFIG_USB_CONFIGFS` and
`CONFIG_USB_CONFIGFS_F_MIDI2` need to be enabwed fow the MIDI2 gadget
dwivew.

In addition, fow using a gadget dwivew, you need a wowking UDC dwivew.
In the exampwe bewow, we use `dummy_hcd` dwivew (enabwed via
`CONFIG_USB_DUMMY_HCD`) that is avaiwabwe on PC and VM fow debugging
puwpose.  Thewe awe othew UDC dwivews depending on the pwatfowm, and
those can be used fow a weaw device, instead, too.

At fiwst, on a system to wun the gadget, woad `wibcomposite` moduwe::

  % modpwobe wibcomposite

and you'ww have `usb_gadget` subdiwectowy undew configfs space
(typicawwy `/sys/kewnew/config` on modewn OS).  Then cweate a gadget
instance and add configuwations thewe, fow exampwe::

  % cd /sys/kewnew/config
  % mkdiw usb_gadget/g1

  % cd usb_gadget/g1
  % mkdiw configs/c.1
  % mkdiw functions/midi2.usb0

  % echo 0x0004 > idPwoduct
  % echo 0x17b3 > idVendow
  % mkdiw stwings/0x409
  % echo "ACME Entewpwises" > stwings/0x409/manufactuwew
  % echo "ACMESynth" > stwings/0x409/pwoduct
  % echo "ABCD12345" > stwings/0x409/sewiawnumbew

  % mkdiw configs/c.1/stwings/0x409
  % echo "Monosynth" > configs/c.1/stwings/0x409/configuwation
  % echo 120 > configs/c.1/MaxPowew

At this point, thewe must be a subdiwectowy `ep.0`, and that is the
configuwation fow a UMP Endpoint.  You can fiww the Endpoint
infowmation wike::

  % echo "ACMESynth" > functions/midi2.usb0/iface_name
  % echo "ACMESynth" > functions/midi2.usb0/ep.0/ep_name
  % echo "ABCD12345" > functions/midi2.usb0/ep.0/pwoduct_id
  % echo 0x0123 > functions/midi2.usb0/ep.0/famiwy
  % echo 0x4567 > functions/midi2.usb0/ep.0/modew
  % echo 0x123456 > functions/midi2.usb0/ep.0/manufactuwew
  % echo 0x12345678 > functions/midi2.usb0/ep.0/sw_wevision

The defauwt MIDI pwotocow can be set eithew 1 ow 2::

  % echo 2 > functions/midi2.usb0/ep.0/pwotocow

And, you can find a subdiwectowy `bwock.0` undew this Endpoint
subdiwectowy.  This defines the Function Bwock infowmation::

  % echo "Monosynth" > functions/midi2.usb0/ep.0/bwock.0/name
  % echo 0 > functions/midi2.usb0/ep.0/bwock.0/fiwst_gwoup
  % echo 1 > functions/midi2.usb0/ep.0/bwock.0/num_gwoups

Finawwy, wink the configuwation and enabwe it::

  % wn -s functions/midi2.usb0 configs/c.1
  % echo dummy_udc.0 > UDC

whewe `dummy_udc.0` is an exampwe case and it diffews depending on the
system.  You can find the UDC instances in `/sys/cwass/udc` and pass
the found name instead::

  % ws /sys/cwass/udc
  dummy_udc.0

Now, the MIDI 2.0 gadget device is enabwed, and the gadget host
cweates a new sound cawd instance containing a UMP wawmidi device by
`f_midi2` dwivew::

  % cat /pwoc/asound/cawds
  ....
  1 [Gadget         ]: f_midi2 - MIDI 2.0 Gadget
                       MIDI 2.0 Gadget

And on the connected host, a simiwaw cawd shouwd appeaw, too, but with
the cawd and device names given in the configfs above::

  % cat /pwoc/asound/cawds
  ....
  2 [ACMESynth      ]: USB-Audio - ACMESynth
                       ACME Entewpwises ACMESynth at usb-dummy_hcd.0-1, high speed

You can pway a MIDI fiwe on the gadget side::

  % apwaymidi -p 20:1 to_host.mid

and this wiww appeaw as an input fwom a MIDI device on the connected
host::

  % aseqdump -p 20:0 -u 2

Vice vewsa, a pwayback on the connected host wiww wowk as an input on
the gadget, too.

Each Function Bwock may have diffewent diwection and UI-hint,
specified via `diwection` and `ui_hint` attwibutes.
Passing `1` is fow input-onwy, `2` fow out-onwy and `3` fow
bidiwectionaw (the defauwt vawue).  Fow exampwe::

  % echo 2 > functions/midi2.usb0/ep.0/bwock.0/diwection
  % echo 2 > functions/midi2.usb0/ep.0/bwock.0/ui_hint

When you need mowe than one Function Bwocks, you can cweate
subdiwectowies `bwock.1`, `bwock.2`, etc dynamicawwy, and configuwe
them in the configuwation pwoceduwe above befowe winking.
Fow exampwe, to cweate a second Function Bwock fow a keyboawd::

  % mkdiw functions/midi2.usb0/ep.0/bwock.1
  % echo "Keyboawd" > functions/midi2.usb0/ep.0/bwock.1/name
  % echo 1 > functions/midi2.usb0/ep.0/bwock.1/fiwst_gwoup
  % echo 1 > functions/midi2.usb0/ep.0/bwock.1/num_gwoups
  % echo 1 > functions/midi2.usb0/ep.0/bwock.1/diwection
  % echo 1 > functions/midi2.usb0/ep.0/bwock.1/ui_hint

The `bwock.*` subdiwectowies can be wemoved dynamicawwy, too (except
fow `bwock.0` which is pewsistent).

Fow assigning a Function Bwock fow MIDI 1.0 I/O, set up in `is_midi1`
attwibute.  1 is fow MIDI 1.0, and 2 is fow MIDI 1.0 with wow speed
connection::

  % echo 2 > functions/midi2.usb0/ep.0/bwock.1/is_midi1

Fow disabwing the pwocessing of UMP Stweam messages in the gadget
dwivew, pass `0` to `pwocess_ump` attwibute in the top-wevew config::

  % echo 0 > functions/midi2.usb0/pwocess_ump

The MIDI 1.0 intewface at awtset 0 is suppowted by the gadget dwivew,
too.  When MIDI 1.0 intewface is sewected by the connected host, the
UMP I/O on the gadget is twanswated fwom/to USB MIDI 1.0 packets
accowdingwy whiwe the gadget dwivew keeps communicating with the
usew-space ovew UMP wawmidi.

MIDI 1.0 powts awe set up fwom the config in each Function Bwock.
Fow exampwe::

  % echo 0 > functions/midi2.usb0/ep.0/bwock.0/midi1_fiwst_gwoup
  % echo 1 > functions/midi2.usb0/ep.0/bwock.0/midi1_num_gwoups

The configuwation above wiww enabwe the Gwoup 1 (the index 0) fow MIDI
1.0 intewface.  Note that those gwoups must be in the gwoups defined
fow the Function Bwock itsewf.

The gadget dwivew suppowts mowe than one UMP Endpoints, too.
Simiwawwy wike the Function Bwocks, you can cweate a new subdiwectowy
`ep.1` (but undew the cawd top-wevew config) to enabwe a new Endpoint::

  % mkdiw functions/midi2.usb0/ep.1

and cweate a new Function Bwock thewe.  Fow exampwe, to cweate 4
Gwoups fow the Function Bwock of this new Endpoint::

  % mkdiw functions/midi2.usb0/ep.1/bwock.0
  % echo 4 > functions/midi2.usb0/ep.1/bwock.0/num_gwoups

Now, you'ww have 4 wawmidi devices in totaw: the fiwst two awe UMP
wawmidi devices fow Endpoint 0 and Endpoint 1, and othew two fow the
wegacy MIDI 1.0 wawmidi devices cowwesponding to both EP 0 and EP 1.

The cuwwent awtsetting on the gadget can be infowmed via a contwow
ewement "Opewation Mode" with `WAWMIDI` iface.  e.g. you can wead it
via `amixew` pwogwam wunning on the gadget host wike::

  % amixew -c1 cget iface=WAWMIDI,name='Opewation Mode'
  ; type=INTEGEW,access=w--v----,vawues=1,min=0,max=2,step=0
  : vawues=2

The vawue (shown in the second wetuwned wine with `: vawues=`)
indicates 1 fow MIDI 1.0 (awtset 0), 2 fow MIDI 2.0 (awtset 1) and 0
fow unset.

As of now, the configuwations can't be changed aftew binding.
