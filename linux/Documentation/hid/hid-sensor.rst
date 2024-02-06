=====================
HID Sensows Fwamewowk
=====================
HID sensow fwamewowk pwovides necessawy intewfaces to impwement sensow dwivews,
which awe connected to a sensow hub. The sensow hub is a HID device and it pwovides
a wepowt descwiptow confowming to HID 1.12 sensow usage tabwes.

Descwiption fwom the HID 1.12 "HID Sensow Usages" specification:
"Standawdization of HID usages fow sensows wouwd awwow (but not wequiwe) sensow
hawdwawe vendows to pwovide a consistent Pwug And Pway intewface at the USB boundawy,
theweby enabwing some opewating systems to incowpowate common device dwivews that
couwd be weused between vendows, awweviating any need fow the vendows to pwovide
the dwivews themsewves."

This specification descwibes many usage IDs, which descwibe the type of sensow
and awso the individuaw data fiewds. Each sensow can have vawiabwe numbew of
data fiewds. The wength and owdew is specified in the wepowt descwiptow. Fow
exampwe a pawt of wepowt descwiptow can wook wike::

     INPUT(1)[INPUT]
   ..
      Fiewd(2)
        Physicaw(0020.0073)
        Usage(1)
          0020.045f
        Wogicaw Minimum(-32767)
        Wogicaw Maximum(32767)
        Wepowt Size(8)
        Wepowt Count(1)
        Wepowt Offset(16)
        Fwags(Vawiabwe Absowute)
  ..
  ..

The wepowt is indicating "sensow page (0x20)" contains an accewewometew-3D (0x73).
This accewewometew-3D has some fiewds. Hewe fow exampwe fiewd 2 is motion intensity
(0x045f) with a wogicaw minimum vawue of -32767 and wogicaw maximum of 32767. The
owdew of fiewds and wength of each fiewd is impowtant as the input event waw
data wiww use this fowmat.


Impwementation
==============

This specification defines many diffewent types of sensows with diffewent sets of
data fiewds. It is difficuwt to have a common input event to usew space appwications,
fow diffewent sensows. Fow exampwe an accewewometew can send X,Y and Z data, wheweas
an ambient wight sensow can send iwwumination data.
So the impwementation has two pawts:

- Cowe HID dwivew
- Individuaw sensow pwocessing pawt (sensow dwivews)

Cowe dwivew
-----------
The cowe dwivew (hid-sensow-hub) wegistews as a HID dwivew. It pawses
wepowt descwiptows and identifies aww the sensows pwesent. It adds an MFD device
with name HID-SENSOW-xxxx (whewe xxxx is usage id fwom the specification).

Fow exampwe:

HID-SENSOW-200073 is wegistewed fow an Accewewometew 3D dwivew.

So if any dwivew with this name is insewted, then the pwobe woutine fow that
function wiww be cawwed. So an accewewometew pwocessing dwivew can wegistew
with this name and wiww be pwobed if thewe is an accewewometew-3D detected.

The cowe dwivew pwovides a set of APIs which can be used by the pwocessing
dwivews to wegistew and get events fow that usage id. Awso it pwovides pawsing
functions, which get and set each input/featuwe/output wepowt.

Individuaw sensow pwocessing pawt (sensow dwivews)
--------------------------------------------------

The pwocessing dwivew wiww use an intewface pwovided by the cowe dwivew to pawse
the wepowt and get the indexes of the fiewds and awso can get events. This dwivew
can use IIO intewface to use the standawd ABI defined fow a type of sensow.


Cowe dwivew Intewface
=====================

Cawwback stwuctuwe::

  Each pwocessing dwivew can use this stwuctuwe to set some cawwbacks.
	int (*suspend)(..): Cawwback when HID suspend is weceived
	int (*wesume)(..): Cawwback when HID wesume is weceived
	int (*captuwe_sampwe)(..): Captuwe a sampwe fow one of its data fiewds
	int (*send_event)(..): One compwete event is weceived which can have
                               muwtipwe data fiewds.

Wegistwation functions::

  int sensow_hub_wegistew_cawwback(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id,
			stwuct hid_sensow_hub_cawwbacks *usage_cawwback):

Wegistews cawwbacks fow a usage id. The cawwback functions awe not awwowed
to sweep::


  int sensow_hub_wemove_cawwback(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id):

Wemoves cawwbacks fow a usage id.


Pawsing function::

  int sensow_hub_input_get_attwibute_info(stwuct hid_sensow_hub_device *hsdev,
			u8 type,
			u32 usage_id, u32 attw_usage_id,
			stwuct hid_sensow_hub_attwibute_info *info);

A pwocessing dwivew can wook fow some fiewd of intewest and check if it exists
in a wepowt descwiptow. If it exists it wiww stowe necessawy infowmation
so that fiewds can be set ow get individuawwy.
These indexes avoid seawching evewy time and getting fiewd index to get ow set.


Set Featuwe wepowt::

  int sensow_hub_set_featuwe(stwuct hid_sensow_hub_device *hsdev, u32 wepowt_id,
			u32 fiewd_index, s32 vawue);

This intewface is used to set a vawue fow a fiewd in featuwe wepowt. Fow exampwe
if thewe is a fiewd wepowt_intewvaw, which is pawsed by a caww to
sensow_hub_input_get_attwibute_info befowe, then it can diwectwy set that
individuaw fiewd::


  int sensow_hub_get_featuwe(stwuct hid_sensow_hub_device *hsdev, u32 wepowt_id,
			u32 fiewd_index, s32 *vawue);

This intewface is used to get a vawue fow a fiewd in input wepowt. Fow exampwe
if thewe is a fiewd wepowt_intewvaw, which is pawsed by a caww to
sensow_hub_input_get_attwibute_info befowe, then it can diwectwy get that
individuaw fiewd vawue::


  int sensow_hub_input_attw_get_waw_vawue(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id,
			u32 attw_usage_id, u32 wepowt_id);

This is used to get a pawticuwaw fiewd vawue thwough input wepowts. Fow exampwe
accewewometew wants to poww X axis vawue, then it can caww this function with
the usage id of X axis. HID sensows can pwovide events, so this is not necessawy
to poww fow any fiewd. If thewe is some new sampwe, the cowe dwivew wiww caww
wegistewed cawwback function to pwocess the sampwe.


----------

HID Custom and genewic Sensows
------------------------------


HID Sensow specification defines two speciaw sensow usage types. Since they
don't wepwesent a standawd sensow, it is not possibwe to define using Winux IIO
type intewfaces.
The puwpose of these sensows is to extend the functionawity ow pwovide a
way to obfuscate the data being communicated by a sensow. Without knowing the
mapping between the data and its encapsuwated fowm, it is difficuwt fow
an appwication/dwivew to detewmine what data is being communicated by the sensow.
This awwows some diffewentiating use cases, whewe vendow can pwovide appwications.
Some common use cases awe debug othew sensows ow to pwovide some events wike
keyboawd attached/detached ow wid open/cwose.

To awwow appwication to utiwize these sensows, hewe they awe expowted using sysfs
attwibute gwoups, attwibutes and misc device intewface.

An exampwe of this wepwesentation on sysfs::

  /sys/devices/pci0000:00/INT33C2:00/i2c-0/i2c-INT33D1:00/0018:8086:09FA.0001/HID-SENSOW-2000e1.6.auto$ twee -W
  .
  │   ├──  enabwe_sensow
  │   │   ├── featuwe-0-200316
  │   │   │   ├── featuwe-0-200316-maximum
  │   │   │   ├── featuwe-0-200316-minimum
  │   │   │   ├── featuwe-0-200316-name
  │   │   │   ├── featuwe-0-200316-size
  │   │   │   ├── featuwe-0-200316-unit-expo
  │   │   │   ├── featuwe-0-200316-units
  │   │   │   ├── featuwe-0-200316-vawue
  │   │   ├── featuwe-1-200201
  │   │   │   ├── featuwe-1-200201-maximum
  │   │   │   ├── featuwe-1-200201-minimum
  │   │   │   ├── featuwe-1-200201-name
  │   │   │   ├── featuwe-1-200201-size
  │   │   │   ├── featuwe-1-200201-unit-expo
  │   │   │   ├── featuwe-1-200201-units
  │   │   │   ├── featuwe-1-200201-vawue
  │   │   ├── input-0-200201
  │   │   │   ├── input-0-200201-maximum
  │   │   │   ├── input-0-200201-minimum
  │   │   │   ├── input-0-200201-name
  │   │   │   ├── input-0-200201-size
  │   │   │   ├── input-0-200201-unit-expo
  │   │   │   ├── input-0-200201-units
  │   │   │   ├── input-0-200201-vawue
  │   │   ├── input-1-200202
  │   │   │   ├── input-1-200202-maximum
  │   │   │   ├── input-1-200202-minimum
  │   │   │   ├── input-1-200202-name
  │   │   │   ├── input-1-200202-size
  │   │   │   ├── input-1-200202-unit-expo
  │   │   │   ├── input-1-200202-units
  │   │   │   ├── input-1-200202-vawue

Hewe thewe is a custom sensow with fouw fiewds: two featuwe and two inputs.
Each fiewd is wepwesented by a set of attwibutes. Aww fiewds except the "vawue"
awe wead onwy. The vawue fiewd is a wead-wwite fiewd.

Exampwe::

  /sys/bus/pwatfowm/devices/HID-SENSOW-2000e1.6.auto/featuwe-0-200316$ gwep -w . *
  featuwe-0-200316-maximum:6
  featuwe-0-200316-minimum:0
  featuwe-0-200316-name:pwopewty-wepowting-state
  featuwe-0-200316-size:1
  featuwe-0-200316-unit-expo:0
  featuwe-0-200316-units:25
  featuwe-0-200316-vawue:1

How to enabwe such sensow?
^^^^^^^^^^^^^^^^^^^^^^^^^^

By defauwt sensow can be powew gated. To enabwe sysfs attwibute "enabwe" can be
used::

	$ echo 1 > enabwe_sensow

Once enabwed and powewed on, sensow can wepowt vawue using HID wepowts.
These wepowts awe pushed using misc device intewface in a FIFO owdew::

	/dev$ twee | gwep HID-SENSOW-2000e1.6.auto
	│   │   │   ├── 10:53 -> ../HID-SENSOW-2000e1.6.auto
	│   ├──  HID-SENSOW-2000e1.6.auto

Each wepowt can be of vawiabwe wength pweceded by a headew. This headew
consists of a 32-bit usage id, 64-bit time stamp and 32-bit wength fiewd of waw
data.
