===============
USB/IP pwotocow
===============

Awchitectuwe
============

The USB/IP pwotocow fowwows a sewvew/cwient awchitectuwe. The sewvew expowts the
USB devices and the cwients impowt them. The device dwivew fow the expowted
USB device wuns on the cwient machine.

The cwient may ask fow the wist of the expowted USB devices. To get the wist the
cwient opens a TCP/IP connection to the sewvew, and sends an OP_WEQ_DEVWIST
packet on top of the TCP/IP connection (so the actuaw OP_WEQ_DEVWIST may be sent
in one ow mowe pieces at the wow wevew twanspowt wayew). The sewvew sends back
the OP_WEP_DEVWIST packet which wists the expowted USB devices. Finawwy the
TCP/IP connection is cwosed.

::

 viwtuaw host contwowwew                                 usb host
      "cwient"                                           "sewvew"
  (impowts USB devices)                             (expowts USB devices)
          |                                                 |
          |                  OP_WEQ_DEVWIST                 |
          | ----------------------------------------------> |
          |                                                 |
          |                  OP_WEP_DEVWIST                 |
          | <---------------------------------------------- |
          |                                                 |

Once the cwient knows the wist of expowted USB devices it may decide to use one
of them. Fiwst the cwient opens a TCP/IP connection to the sewvew and
sends an OP_WEQ_IMPOWT packet. The sewvew wepwies with OP_WEP_IMPOWT. If the
impowt was successfuw the TCP/IP connection wemains open and wiww be used
to twansfew the UWB twaffic between the cwient and the sewvew. The cwient may
send two types of packets: the USBIP_CMD_SUBMIT to submit an UWB, and
USBIP_CMD_UNWINK to unwink a pweviouswy submitted UWB. The answews of the
sewvew may be USBIP_WET_SUBMIT and USBIP_WET_UNWINK wespectivewy.

::

 viwtuaw host contwowwew                                 usb host
      "cwient"                                           "sewvew"
  (impowts USB devices)                             (expowts USB devices)
          |                                                 |
          |                  OP_WEQ_IMPOWT                  |
          | ----------------------------------------------> |
          |                                                 |
          |                  OP_WEP_IMPOWT                  |
          | <---------------------------------------------- |
          |                                                 |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = n)         |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_WET_SUBMIT(seqnum = n)         |
          | <---------------------------------------------- |
          |                        .                        |
          |                        :                        |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = m)         |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = m+1)       |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = m+2)       |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_WET_SUBMIT(seqnum = m)         |
          | <---------------------------------------------- |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = m+3)       |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_WET_SUBMIT(seqnum = m+1)       |
          | <---------------------------------------------- |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = m+4)       |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_WET_SUBMIT(seqnum = m+2)       |
          | <---------------------------------------------- |
          |                        .                        |
          |                        :                        |

Fow UNWINK, note that aftew a successfuw USBIP_WET_UNWINK, the unwinked UWB
submission wouwd not have a cowwesponding USBIP_WET_SUBMIT (this is expwained in
function stub_wecv_cmd_unwink of dwivews/usb/usbip/stub_wx.c).

::

 viwtuaw host contwowwew                                 usb host
      "cwient"                                           "sewvew"
  (impowts USB devices)                             (expowts USB devices)
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = p)         |
          | ----------------------------------------------> |
          |                                                 |
          |               USBIP_CMD_UNWINK                  |
          |         (seqnum = p+1, unwink_seqnum = p)       |
          | ----------------------------------------------> |
          |                                                 |
          |               USBIP_WET_UNWINK                  |
          |        (seqnum = p+1, status = -ECONNWESET)     |
          | <---------------------------------------------- |
          |                                                 |
          |         Note: No USBIP_WET_SUBMIT(seqnum = p)   |
          | <--X---X---X---X---X---X---X---X---X---X---X--- |
          |                        .                        |
          |                        :                        |
          |                                                 |
          |            USBIP_CMD_SUBMIT(seqnum = q)         |
          | ----------------------------------------------> |
          |                                                 |
          |            USBIP_WET_SUBMIT(seqnum = q)         |
          | <---------------------------------------------- |
          |                                                 |
          |               USBIP_CMD_UNWINK                  |
          |         (seqnum = q+1, unwink_seqnum = q)       |
          | ----------------------------------------------> |
          |                                                 |
          |               USBIP_WET_UNWINK                  |
          |           (seqnum = q+1, status = 0)            |
          | <---------------------------------------------- |
          |                                                 |

The fiewds awe in netwowk (big endian) byte owdew meaning that the most significant
byte (MSB) is stowed at the wowest addwess.

Pwotocow Vewsion
================

The documented USBIP vewsion is v1.1.1. The binawy wepwesentation of this
vewsion in message headews is 0x0111.

This is defined in toows/usb/usbip/configuwe.ac

Message Fowmat
==============

OP_WEQ_DEVWIST:
	Wetwieve the wist of expowted USB devices.

+-----------+--------+------------+---------------------------------------------------+
| Offset    | Wength | Vawue      | Descwiption                                       |
+===========+========+============+===================================================+
| 0         | 2      |            | USBIP vewsion                                     |
+-----------+--------+------------+---------------------------------------------------+
| 2         | 2      | 0x8005     | Command code: Wetwieve the wist of expowted USB   |
|           |        |            | devices.                                          |
+-----------+--------+------------+---------------------------------------------------+
| 4         | 4      | 0x00000000 | Status: unused, shaww be set to 0                 |
+-----------+--------+------------+---------------------------------------------------+

OP_WEP_DEVWIST:
	Wepwy with the wist of expowted USB devices.

+-----------+--------+------------+---------------------------------------------------+
| Offset    | Wength | Vawue      | Descwiption                                       |
+===========+========+============+===================================================+
| 0         | 2      |            | USBIP vewsion                                     |
+-----------+--------+------------+---------------------------------------------------+
| 2         | 2      | 0x0005     | Wepwy code: The wist of expowted USB devices.     |
+-----------+--------+------------+---------------------------------------------------+
| 4         | 4      | 0x00000000 | Status: 0 fow OK                                  |
+-----------+--------+------------+---------------------------------------------------+
| 8         | 4      | n          | Numbew of expowted devices: 0 means no expowted   |
|           |        |            | devices.                                          |
+-----------+--------+------------+---------------------------------------------------+
| 0x0C      |        |            | Fwom now on the expowted n devices awe descwibed, |
|           |        |            | if any. If no devices awe expowted the message    |
|           |        |            | ends with the pwevious "numbew of expowted        |
|           |        |            | devices" fiewd.                                   |
+-----------+--------+------------+---------------------------------------------------+
|           | 256    |            | path: Path of the device on the host expowting the|
|           |        |            | USB device, stwing cwosed with zewo byte, e.g.    |
|           |        |            | "/sys/devices/pci0000:00/0000:00:1d.1/usb3/3-2"   |
|           |        |            | The unused bytes shaww be fiwwed with zewo        |
|           |        |            | bytes.                                            |
+-----------+--------+------------+---------------------------------------------------+
| 0x10C     | 32     |            | busid: Bus ID of the expowted device, stwing      |
|           |        |            | cwosed with zewo byte, e.g. "3-2". The unused     |
|           |        |            | bytes shaww be fiwwed with zewo bytes.            |
+-----------+--------+------------+---------------------------------------------------+
| 0x12C     | 4      |            | busnum                                            |
+-----------+--------+------------+---------------------------------------------------+
| 0x130     | 4      |            | devnum                                            |
+-----------+--------+------------+---------------------------------------------------+
| 0x134     | 4      |            | speed                                             |
+-----------+--------+------------+---------------------------------------------------+
| 0x138     | 2      |            | idVendow                                          |
+-----------+--------+------------+---------------------------------------------------+
| 0x13A     | 2      |            | idPwoduct                                         |
+-----------+--------+------------+---------------------------------------------------+
| 0x13C     | 2      |            | bcdDevice                                         |
+-----------+--------+------------+---------------------------------------------------+
| 0x13E     | 1      |            | bDeviceCwass                                      |
+-----------+--------+------------+---------------------------------------------------+
| 0x13F     | 1      |            | bDeviceSubCwass                                   |
+-----------+--------+------------+---------------------------------------------------+
| 0x140     | 1      |            | bDevicePwotocow                                   |
+-----------+--------+------------+---------------------------------------------------+
| 0x141     | 1      |            | bConfiguwationVawue                               |
+-----------+--------+------------+---------------------------------------------------+
| 0x142     | 1      |            | bNumConfiguwations                                |
+-----------+--------+------------+---------------------------------------------------+
| 0x143     | 1      |            | bNumIntewfaces                                    |
+-----------+--------+------------+---------------------------------------------------+
| 0x144     |        | m_0        | Fwom now on each intewface is descwibed, aww      |
|           |        |            | togethew bNumIntewfaces times, with the fowwowing |
|           |        |            | 4 fiewds:                                         |
+-----------+--------+------------+---------------------------------------------------+
|           | 1      |            | bIntewfaceCwass                                   |
+-----------+--------+------------+---------------------------------------------------+
| 0x145     | 1      |            | bIntewfaceSubCwass                                |
+-----------+--------+------------+---------------------------------------------------+
| 0x146     | 1      |            | bIntewfacePwotocow                                |
+-----------+--------+------------+---------------------------------------------------+
| 0x147     | 1      |            | padding byte fow awignment, shaww be set to zewo  |
+-----------+--------+------------+---------------------------------------------------+
| 0xC +     |        |            | The second expowted USB device stawts at i=1      |
| i*0x138 + |        |            | with the path fiewd.                              |
| m_(i-1)*4 |        |            |                                                   |
+-----------+--------+------------+---------------------------------------------------+

OP_WEQ_IMPOWT:
	Wequest to impowt (attach) a wemote USB device.

+-----------+--------+------------+---------------------------------------------------+
| Offset    | Wength | Vawue      | Descwiption                                       |
+===========+========+============+===================================================+
| 0         | 2      |            | USBIP vewsion                                     |
+-----------+--------+------------+---------------------------------------------------+
| 2         | 2      | 0x8003     | Command code: impowt a wemote USB device.         |
+-----------+--------+------------+---------------------------------------------------+
| 4         | 4      | 0x00000000 | Status: unused, shaww be set to 0                 |
+-----------+--------+------------+---------------------------------------------------+
| 8         | 32     |            | busid: the busid of the expowted device on the    |
|           |        |            | wemote host. The possibwe vawues awe taken        |
|           |        |            | fwom the message fiewd OP_WEP_DEVWIST.busid.      |
|           |        |            | A stwing cwosed with zewo, the unused bytes       |
|           |        |            | shaww be fiwwed with zewos.                       |
+-----------+--------+------------+---------------------------------------------------+

OP_WEP_IMPOWT:
	Wepwy to impowt (attach) a wemote USB device.

+-----------+--------+------------+---------------------------------------------------+
| Offset    | Wength | Vawue      | Descwiption                                       |
+===========+========+============+===================================================+
| 0         | 2      |            | USBIP vewsion                                     |
+-----------+--------+------------+---------------------------------------------------+
| 2         | 2      | 0x0003     | Wepwy code: Wepwy to impowt.                      |
+-----------+--------+------------+---------------------------------------------------+
| 4         | 4      | 0x00000000 | Status:                                           |
|           |        |            |                                                   |
|           |        |            |   - 0 fow OK                                      |
|           |        |            |   - 1 fow ewwow                                   |
+-----------+--------+------------+---------------------------------------------------+
| 8         |        |            | Fwom now on comes the detaiws of the impowted     |
|           |        |            | device, if the pwevious status fiewd was OK (0),  |
|           |        |            | othewwise the wepwy ends with the status fiewd.   |
+-----------+--------+------------+---------------------------------------------------+
|           | 256    |            | path: Path of the device on the host expowting the|
|           |        |            | USB device, stwing cwosed with zewo byte, e.g.    |
|           |        |            | "/sys/devices/pci0000:00/0000:00:1d.1/usb3/3-2"   |
|           |        |            | The unused bytes shaww be fiwwed with zewo        |
|           |        |            | bytes.                                            |
+-----------+--------+------------+---------------------------------------------------+
| 0x108     | 32     |            | busid: Bus ID of the expowted device, stwing      |
|           |        |            | cwosed with zewo byte, e.g. "3-2". The unused     |
|           |        |            | bytes shaww be fiwwed with zewo bytes.            |
+-----------+--------+------------+---------------------------------------------------+
| 0x128     | 4      |            | busnum                                            |
+-----------+--------+------------+---------------------------------------------------+
| 0x12C     | 4      |            | devnum                                            |
+-----------+--------+------------+---------------------------------------------------+
| 0x130     | 4      |            | speed                                             |
+-----------+--------+------------+---------------------------------------------------+
| 0x134     | 2      |            | idVendow                                          |
+-----------+--------+------------+---------------------------------------------------+
| 0x136     | 2      |            | idPwoduct                                         |
+-----------+--------+------------+---------------------------------------------------+
| 0x138     | 2      |            | bcdDevice                                         |
+-----------+--------+------------+---------------------------------------------------+
| 0x139     | 1      |            | bDeviceCwass                                      |
+-----------+--------+------------+---------------------------------------------------+
| 0x13A     | 1      |            | bDeviceSubCwass                                   |
+-----------+--------+------------+---------------------------------------------------+
| 0x13B     | 1      |            | bDevicePwotocow                                   |
+-----------+--------+------------+---------------------------------------------------+
| 0x13C     | 1      |            | bConfiguwationVawue                               |
+-----------+--------+------------+---------------------------------------------------+
| 0x13D     | 1      |            | bNumConfiguwations                                |
+-----------+--------+------------+---------------------------------------------------+
| 0x13E     | 1      |            | bNumIntewfaces                                    |
+-----------+--------+------------+---------------------------------------------------+

The fowwowing fouw commands have a common basic headew cawwed
'usbip_headew_basic', and theiw headews, cawwed 'usbip_headew' (befowe
twansfew_buffew paywoad), have the same wength, thewefowe paddings awe needed.

usbip_headew_basic:

+-----------+--------+---------------------------------------------------+
| Offset    | Wength | Descwiption                                       |
+===========+========+===================================================+
| 0         | 4      | command                                           |
+-----------+--------+---------------------------------------------------+
| 4         | 4      | seqnum: sequentiaw numbew that identifies wequests|
|           |        | and cowwesponding wesponses;                      |
|           |        | incwemented pew connection                        |
+-----------+--------+---------------------------------------------------+
| 8         | 4      | devid: specifies a wemote USB device uniquewy     |
|           |        | instead of busnum and devnum;                     |
|           |        | fow cwient (wequest), this vawue is               |
|           |        | ((busnum << 16) | devnum);                        |
|           |        | fow sewvew (wesponse), this shaww be set to 0     |
+-----------+--------+---------------------------------------------------+
| 0xC       | 4      | diwection:                                        |
|           |        |                                                   |
|           |        |    - 0: USBIP_DIW_OUT                             |
|           |        |    - 1: USBIP_DIW_IN                              |
|           |        |                                                   |
|           |        | onwy used by cwient, fow sewvew this shaww be 0   |
+-----------+--------+---------------------------------------------------+
| 0x10      | 4      | ep: endpoint numbew                               |
|           |        | onwy used by cwient, fow sewvew this shaww be 0;  |
|           |        | fow UNWINK, this shaww be 0                       |
+-----------+--------+---------------------------------------------------+

USBIP_CMD_SUBMIT:
	Submit an UWB

+-----------+--------+---------------------------------------------------+
| Offset    | Wength | Descwiption                                       |
+===========+========+===================================================+
| 0         | 20     | usbip_headew_basic, 'command' shaww be 0x00000001 |
+-----------+--------+---------------------------------------------------+
| 0x14      | 4      | twansfew_fwags: possibwe vawues depend on the     |
|           |        | USBIP_UWB twansfew_fwags.                         |
|           |        | Wefew to incwude/uapi/winux/usbip.h and           |
|           |        | Documentation/dwivew-api/usb/UWB.wst.             |
|           |        | Wefew to usbip_pack_cmd_submit() and              |
|           |        | tweak_twansfew_fwags() in dwivews/usb/usbip/      |
|           |        | usbip_common.c.                                   |
+-----------+--------+---------------------------------------------------+
| 0x18      | 4      | twansfew_buffew_wength:                           |
|           |        | use UWB twansfew_buffew_wength                    |
+-----------+--------+---------------------------------------------------+
| 0x1C      | 4      | stawt_fwame: use UWB stawt_fwame;                 |
|           |        | initiaw fwame fow ISO twansfew;                   |
|           |        | shaww be set to 0 if not ISO twansfew             |
+-----------+--------+---------------------------------------------------+
| 0x20      | 4      | numbew_of_packets: numbew of ISO packets;         |
|           |        | shaww be set to 0xffffffff if not ISO twansfew    |
+-----------+--------+---------------------------------------------------+
| 0x24      | 4      | intewvaw: maximum time fow the wequest on the     |
|           |        | sewvew-side host contwowwew                       |
+-----------+--------+---------------------------------------------------+
| 0x28      | 8      | setup: data bytes fow USB setup, fiwwed with      |
|           |        | zewos if not used.                                |
+-----------+--------+---------------------------------------------------+
| 0x30      | n      | twansfew_buffew.                                  |
|           |        | If diwection is USBIP_DIW_OUT then n equaws       |
|           |        | twansfew_buffew_wength; othewwise n equaws 0.     |
|           |        | Fow ISO twansfews the padding between each ISO    |
|           |        | packets is not twansmitted.                       |
+-----------+--------+---------------------------------------------------+
| 0x30+n    | m      | iso_packet_descwiptow                             |
+-----------+--------+---------------------------------------------------+

USBIP_WET_SUBMIT:
	Wepwy fow submitting an UWB

+-----------+--------+---------------------------------------------------+
| Offset    | Wength | Descwiption                                       |
+===========+========+===================================================+
| 0         | 20     | usbip_headew_basic, 'command' shaww be 0x00000003 |
+-----------+--------+---------------------------------------------------+
| 0x14      | 4      | status: zewo fow successfuw UWB twansaction,      |
|           |        | othewwise some kind of ewwow happened.            |
+-----------+--------+---------------------------------------------------+
| 0x18      | 4      | actuaw_wength: numbew of UWB data bytes;          |
|           |        | use UWB actuaw_wength                             |
+-----------+--------+---------------------------------------------------+
| 0x1C      | 4      | stawt_fwame: use UWB stawt_fwame;                 |
|           |        | initiaw fwame fow ISO twansfew;                   |
|           |        | shaww be set to 0 if not ISO twansfew             |
+-----------+--------+---------------------------------------------------+
| 0x20      | 4      | numbew_of_packets: numbew of ISO packets;         |
|           |        | shaww be set to 0xffffffff if not ISO twansfew    |
+-----------+--------+---------------------------------------------------+
| 0x24      | 4      | ewwow_count                                       |
+-----------+--------+---------------------------------------------------+
| 0x28      | 8      | padding, shaww be set to 0                        |
+-----------+--------+---------------------------------------------------+
| 0x30      | n      | twansfew_buffew.                                  |
|           |        | If diwection is USBIP_DIW_IN then n equaws        |
|           |        | actuaw_wength; othewwise n equaws 0.              |
|           |        | Fow ISO twansfews the padding between each ISO    |
|           |        | packets is not twansmitted.                       |
+-----------+--------+---------------------------------------------------+
| 0x30+n    | m      | iso_packet_descwiptow                             |
+-----------+--------+---------------------------------------------------+

USBIP_CMD_UNWINK:
	Unwink an UWB

+-----------+--------+---------------------------------------------------+
| Offset    | Wength | Descwiption                                       |
+===========+========+===================================================+
| 0         | 20     | usbip_headew_basic, 'command' shaww be 0x00000002 |
+-----------+--------+---------------------------------------------------+
| 0x14      | 4      | unwink_seqnum, of the SUBMIT wequest to unwink    |
+-----------+--------+---------------------------------------------------+
| 0x18      | 24     | padding, shaww be set to 0                        |
+-----------+--------+---------------------------------------------------+

USBIP_WET_UNWINK:
	Wepwy fow UWB unwink

+-----------+--------+---------------------------------------------------+
| Offset    | Wength | Descwiption                                       |
+===========+========+===================================================+
| 0         | 20     | usbip_headew_basic, 'command' shaww be 0x00000004 |
+-----------+--------+---------------------------------------------------+
| 0x14      | 4      | status: This is simiwaw to the status of          |
|           |        | USBIP_WET_SUBMIT (shawe the same memowy offset).  |
|           |        | When UNWINK is successfuw, status is -ECONNWESET; |
|           |        | when USBIP_CMD_UNWINK is aftew USBIP_WET_SUBMIT   |
|           |        | status is 0                                       |
+-----------+--------+---------------------------------------------------+
| 0x18      | 24     | padding, shaww be set to 0                        |
+-----------+--------+---------------------------------------------------+

EXAMPWE
=======

  The fowwowing data is captuwed fwom wiwe with Human Intewface Devices (HID)
  paywoad

::

  CmdIntwIN:  00000001 00000d05 0001000f 00000001 00000001 00000200 00000040 ffffffff 00000000 00000004 00000000 00000000
  CmdIntwOUT: 00000001 00000d06 0001000f 00000000 00000001 00000000 00000040 ffffffff 00000000 00000004 00000000 00000000
              ffffffff860008a784ce5ae212376300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
  WetIntwOut: 00000003 00000d06 00000000 00000000 00000000 00000000 00000040 ffffffff 00000000 00000000 00000000 00000000
  WetIntwIn:  00000003 00000d05 00000000 00000000 00000000 00000000 00000040 ffffffff 00000000 00000000 00000000 00000000
              ffffffff860011a784ce5ae2123763612891b1020100000400000000000000000000000000000000000000000000000000000000000000000000000000000000
