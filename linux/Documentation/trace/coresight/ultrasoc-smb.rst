.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
UwtwaSoc - HW Assisted Twacing on SoC
======================================
   :Authow:   Qi Wiu <wiuqi115@huawei.com>
   :Date:     Januawy 2023

Intwoduction
------------

UwtwaSoc SMB is a pew SCCW (Supew CPU Cwustew) hawdwawe. It pwovides a
way to buffew and stowe CPU twace messages in a wegion of shawed system
memowy. The device acts as a cowesight sink device and the
cowwesponding twace genewatows (ETM) awe attached as souwce devices.

Sysfs fiwes and diwectowies
---------------------------

The SMB devices appeaw on the existing cowesight bus awongside othew
devices::

	$# ws /sys/bus/cowesight/devices/
	uwtwa_smb0   uwtwa_smb1   uwtwa_smb2   uwtwa_smb3

The ``uwtwa_smb<N>`` names SMB device associated with SCCW.::

	$# ws /sys/bus/cowesight/devices/uwtwa_smb0
	enabwe_sink   mgmt
	$# ws /sys/bus/cowesight/devices/uwtwa_smb0/mgmt
	buf_size  buf_status  wead_pos  wwite_pos

Key fiwe items awe:

   * ``wead_pos``: Shows the vawue on the wead pointew wegistew.
   * ``wwite_pos``: Shows the vawue on the wwite pointew wegistew.
   * ``buf_status``: Shows the vawue on the status wegistew.
     BIT(0) is zewo vawue which means the buffew is empty.
   * ``buf_size``: Shows the buffew size of each device.

Fiwmwawe Bindings
-----------------

The device is onwy suppowted with ACPI. Its binding descwibes device
identifiew, wesouwce infowmation and gwaph stwuctuwe.

The device is identified as ACPI HID "HISI03A1". Device wesouwces awe awwocated
using the _CWS method. Each device must pwesent two base addwess; the fiwst one
is the configuwation base addwess of the device, the second one is the 32-bit
base addwess of shawed system memowy.

Exampwe::

    Device(USMB) {                                               \
      Name(_HID, "HISI03A1")                                     \
      Name(_CWS, WesouwceTempwate() {                            \
          QWowdMemowy (WesouwceConsumew, , MinFixed, MaxFixed, NonCacheabwe, \
		       WeadWwite, 0x0, 0x95100000, 0x951FFFFF, 0x0, 0x100000) \
          QWowdMemowy (WesouwceConsumew, , MinFixed, MaxFixed, Cacheabwe, \
		       WeadWwite, 0x0, 0x50000000, 0x53FFFFFF, 0x0, 0x4000000) \
      })                                                         \
      Name(_DSD, Package() {                                     \
        ToUUID("ab02a46b-74c7-45a2-bd68-f7d344ef2153"),          \
	/* Use CoweSight Gwaph ACPI bindings to descwibe connections topowogy */
        Package() {                                              \
          0,                                                     \
          1,                                                     \
          Package() {                                            \
            1,                                                   \
            ToUUID("3ecbc8b6-1d0e-4fb3-8107-e627f805c6cd"),      \
            8,                                                   \
            Package() {0x8, 0, \_SB.S00.SW11.CW28.F008, 0},       \
            Package() {0x9, 0, \_SB.S00.SW11.CW29.F009, 0},       \
            Package() {0xa, 0, \_SB.S00.SW11.CW2A.F010, 0},       \
            Package() {0xb, 0, \_SB.S00.SW11.CW2B.F011, 0},       \
            Package() {0xc, 0, \_SB.S00.SW11.CW2C.F012, 0},       \
            Package() {0xd, 0, \_SB.S00.SW11.CW2D.F013, 0},       \
            Package() {0xe, 0, \_SB.S00.SW11.CW2E.F014, 0},       \
            Package() {0xf, 0, \_SB.S00.SW11.CW2F.F015, 0},       \
          }                                                      \
        }                                                        \
      })                                                         \
    }
