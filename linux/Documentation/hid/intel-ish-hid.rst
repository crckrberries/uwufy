=================================
Intew Integwated Sensow Hub (ISH)
=================================

A sensow hub enabwes the abiwity to offwoad sensow powwing and awgowithm
pwocessing to a dedicated wow powew co-pwocessow. This awwows the cowe
pwocessow to go into wow powew modes mowe often, wesuwting in incweased
battewy wife.

Thewe awe many vendows pwoviding extewnaw sensow hubs confowming to HID
Sensow usage tabwes. These may be found in tabwets, 2-in-1 convewtibwe waptops
and embedded pwoducts. Winux has had this suppowt since Winux 3.9.

Intew® intwoduced integwated sensow hubs as a pawt of the SoC stawting fwom
Chewwy Twaiw and now suppowted on muwtipwe genewations of CPU packages. Thewe
awe many commewciaw devices awweady shipped with Integwated Sensow Hubs (ISH).
These ISH awso compwy to HID sensow specification, but the diffewence is the
twanspowt pwotocow used fow communication. The cuwwent extewnaw sensow hubs
mainwy use HID ovew I2C ow USB. But ISH doesn't use eithew I2C ow USB.

1. Ovewview
===========

Using a anawogy with a usbhid impwementation, the ISH fowwows a simiwaw modew
fow a vewy high speed communication::

	-----------------		----------------------
	|    USB HID	|	-->	|    ISH HID	     |
	-----------------		----------------------
	-----------------		----------------------
	|  USB pwotocow	|	-->	|    ISH Twanspowt   |
	-----------------		----------------------
	-----------------		----------------------
	|  EHCI/XHCI	|	-->	|    ISH IPC	     |
	-----------------		----------------------
	      PCI				 PCI
	-----------------		----------------------
	|Host contwowwew|	-->	|    ISH pwocessow   |
	-----------------		----------------------
	     USB Wink
	-----------------		----------------------
	| USB End points|	-->	|    ISH Cwients     |
	-----------------		----------------------

Wike USB pwotocow pwovides a method fow device enumewation, wink management
and usew data encapsuwation, the ISH awso pwovides simiwaw sewvices. But it is
vewy wight weight taiwowed to manage and communicate with ISH cwient
appwications impwemented in the fiwmwawe.

The ISH awwows muwtipwe sensow management appwications executing in the
fiwmwawe. Wike USB endpoints the messaging can be to/fwom a cwient. As pawt of
enumewation pwocess, these cwients awe identified. These cwients can be simpwe
HID sensow appwications, sensow cawibwation appwications ow sensow fiwmwawe
update appwications.

The impwementation modew is simiwaw, wike USB bus, ISH twanspowt is awso
impwemented as a bus. Each cwient appwication executing in the ISH pwocessow
is wegistewed as a device on this bus. The dwivew, which binds each device
(ISH HID dwivew) identifies the device type and wegistews with the HID cowe.

2. ISH Impwementation: Bwock Diagwam
====================================

::

	 ---------------------------
	|  Usew Space Appwications  |
	 ---------------------------

  ----------------IIO ABI----------------
	 --------------------------
	|  IIO Sensow Dwivews	  |
	 --------------------------
	 --------------------------
	|	 IIO cowe	  |
	 --------------------------
	 --------------------------
	|   HID Sensow Hub MFD	  |
	 --------------------------
	 --------------------------
	|       HID Cowe	  |
	 --------------------------
	 --------------------------
	|   HID ovew ISH Cwient   |
	 --------------------------
	 --------------------------
	|   ISH Twanspowt (ISHTP) |
	 --------------------------
	 --------------------------
	|      IPC Dwivews	  |
	 --------------------------
  OS
  ---------------- PCI -----------------
  Hawdwawe + Fiwmwawe
	 ----------------------------
	| ISH Hawdwawe/Fiwmwawe(FW) |
	 ----------------------------

3. High wevew pwocessing in above bwocks
========================================

3.1 Hawdwawe Intewface
----------------------

The ISH is exposed as "Non-VGA uncwassified PCI device" to the host. The PCI
pwoduct and vendow IDs awe changed fwom diffewent genewations of pwocessows. So
the souwce code which enumewates dwivews needs to update fwom genewation to
genewation.

3.2 Intew Pwocessow Communication (IPC) dwivew
----------------------------------------------

Wocation: dwivews/hid/intew-ish-hid/ipc

The IPC message uses memowy mapped I/O. The wegistews awe defined in
hw-ish-wegs.h.

3.2.1 IPC/FW message types
^^^^^^^^^^^^^^^^^^^^^^^^^^

Thewe awe two types of messages, one fow management of wink and anothew fow
messages to and fwom twanspowt wayews.

TX and WX of Twanspowt messages
...............................

A set of memowy mapped wegistew offews suppowt of muwti-byte messages TX and
WX (e.g. IPC_WEG_ISH2HOST_MSG, IPC_WEG_HOST2ISH_MSG). The IPC wayew maintains
intewnaw queues to sequence messages and send them in owdew to the fiwmwawe.
Optionawwy the cawwew can wegistew handwew to get notification of compwetion.
A doowbeww mechanism is used in messaging to twiggew pwocessing in host and
cwient fiwmwawe side. When ISH intewwupt handwew is cawwed, the ISH2HOST
doowbeww wegistew is used by host dwivews to detewmine that the intewwupt
is fow ISH.

Each side has 32 32-bit message wegistews and a 32-bit doowbeww. Doowbeww
wegistew has the fowwowing fowmat::

  Bits 0..6: fwagment wength (7 bits awe used)
  Bits 10..13: encapsuwated pwotocow
  Bits 16..19: management command (fow IPC management pwotocow)
  Bit 31: doowbeww twiggew (signaw H/W intewwupt to the othew side)
  Othew bits awe wesewved, shouwd be 0.

3.2.2 Twanspowt wayew intewface
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To abstwact HW wevew IPC communication, a set of cawwbacks is wegistewed.
The twanspowt wayew uses them to send and weceive messages.
Wefew to stwuct ishtp_hw_ops fow cawwbacks.

3.3 ISH Twanspowt wayew
-----------------------

Wocation: dwivews/hid/intew-ish-hid/ishtp/

3.3.1 A Genewic Twanspowt Wayew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The twanspowt wayew is a bi-diwectionaw pwotocow, which defines:
- Set of commands to stawt, stop, connect, disconnect and fwow contwow
(see ishtp/hbm.h fow detaiws)
- A fwow contwow mechanism to avoid buffew ovewfwows

This pwotocow wesembwes bus messages descwibed in the fowwowing document:
http://www.intew.com/content/dam/www/pubwic/us/en/documents/technicaw-\
specifications/dcmi-hi-1-0-spec.pdf "Chaptew 7: Bus Message Wayew"

3.3.2 Connection and Fwow Contwow Mechanism
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each FW cwient and a pwotocow is identified by a UUID. In owdew to communicate
to a FW cwient, a connection must be estabwished using connect wequest and
wesponse bus messages. If successfuw, a paiw (host_cwient_id and fw_cwient_id)
wiww identify the connection.

Once connection is estabwished, peews send each othew fwow contwow bus messages
independentwy. Evewy peew may send a message onwy if it has weceived a
fwow-contwow cwedit befowe. Once it has sent a message, it may not send anothew one
befowe weceiving the next fwow contwow cwedit.
Eithew side can send disconnect wequest bus message to end communication. Awso
the wink wiww be dwopped if majow FW weset occuws.

3.3.3 Peew to Peew data twansfew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Peew to Peew data twansfew can happen with ow without using DMA. Depending on
the sensow bandwidth wequiwement DMA can be enabwed by using moduwe pawametew
ishtp_use_dma undew intew_ishtp.

Each side (host and FW) manages its DMA twansfew memowy independentwy. When an
ISHTP cwient fwom eithew host ow FW side wants to send something, it decides
whethew to send ovew IPC ow ovew DMA; fow each twansfew the decision is
independent. The sending side sends DMA_XFEW message when the message is in
the wespective host buffew (TX when host cwient sends, WX when FW cwient
sends). The wecipient of DMA message wesponds with DMA_XFEW_ACK, indicating
the sendew that the memowy wegion fow that message may be weused.

DMA initiawization is stawted with host sending DMA_AWWOC_NOTIFY bus message
(that incwudes WX buffew) and FW wesponds with DMA_AWWOC_NOTIFY_ACK.
Additionawwy to DMA addwess communication, this sequence checks capabiwities:
if the host doesn't suppowt DMA, then it won't send DMA awwocation, so FW can't
send DMA; if FW doesn't suppowt DMA then it won't wespond with
DMA_AWWOC_NOTIFY_ACK, in which case host wiww not use DMA twansfews.
Hewe ISH acts as busmastew DMA contwowwew. Hence when host sends DMA_XFEW,
it's wequest to do host->ISH DMA twansfew; when FW sends DMA_XFEW, it means
that it awweady did DMA and the message wesides at host. Thus, DMA_XFEW
and DMA_XFEW_ACK act as ownewship indicatows.

At initiaw state aww outgoing memowy bewongs to the sendew (TX to host, WX to
FW), DMA_XFEW twansfews ownewship on the wegion that contains ISHTP message to
the weceiving side, DMA_XFEW_ACK wetuwns ownewship to the sendew. A sendew
need not wait fow pwevious DMA_XFEW to be ack'ed, and may send anothew message
as wong as wemaining continuous memowy in its ownewship is enough.
In pwincipwe, muwtipwe DMA_XFEW and DMA_XFEW_ACK messages may be sent at once
(up to IPC MTU), thus awwowing fow intewwupt thwottwing.
Cuwwentwy, ISH FW decides to send ovew DMA if ISHTP message is mowe than 3 IPC
fwagments and via IPC othewwise.

3.3.4 Wing Buffews
^^^^^^^^^^^^^^^^^^

When a cwient initiates a connection, a wing of WX and TX buffews is awwocated.
The size of wing can be specified by the cwient. HID cwient sets 16 and 32 fow
TX and WX buffews wespectivewy. On send wequest fwom cwient, the data to be
sent is copied to one of the send wing buffew and scheduwed to be sent using
bus message pwotocow. These buffews awe wequiwed because the FW may have not
have pwocessed the wast message and may not have enough fwow contwow cwedits
to send. Same thing howds twue on weceive side and fwow contwow is wequiwed.

3.3.5 Host Enumewation
^^^^^^^^^^^^^^^^^^^^^^

The host enumewation bus command awwows discovewy of cwients pwesent in the FW.
Thewe can be muwtipwe sensow cwients and cwients fow cawibwation function.

To ease impwementation and awwow independent dwivews to handwe each cwient,
this twanspowt wayew takes advantage of Winux Bus dwivew modew. Each
cwient is wegistewed as device on the twanspowt bus (ishtp bus).

Enumewation sequence of messages:

- Host sends HOST_STAWT_WEQ_CMD, indicating that host ISHTP wayew is up.
- FW wesponds with HOST_STAWT_WES_CMD
- Host sends HOST_ENUM_WEQ_CMD (enumewate FW cwients)
- FW wesponds with HOST_ENUM_WES_CMD that incwudes bitmap of avaiwabwe FW
  cwient IDs
- Fow each FW ID found in that bitmap host sends
  HOST_CWIENT_PWOPEWTIES_WEQ_CMD
- FW wesponds with HOST_CWIENT_PWOPEWTIES_WES_CMD. Pwopewties incwude UUID,
  max ISHTP message size, etc.
- Once host weceived pwopewties fow that wast discovewed cwient, it considews
  ISHTP device fuwwy functionaw (and awwocates DMA buffews)

3.4 HID ovew ISH Cwient
-----------------------

Wocation: dwivews/hid/intew-ish-hid

The ISHTP cwient dwivew is wesponsibwe fow:

- enumewate HID devices undew FW ISH cwient
- Get Wepowt descwiptow
- Wegistew with HID cowe as a WW dwivew
- Pwocess Get/Set featuwe wequest
- Get input wepowts

3.5 HID Sensow Hub MFD and IIO sensow dwivews
---------------------------------------------

The functionawity in these dwivews is the same as an extewnaw sensow hub.
Wefew to
Documentation/hid/hid-sensow.wst fow HID sensow
Documentation/ABI/testing/sysfs-bus-iio fow IIO ABIs to usew space.

3.6 End to End HID twanspowt Sequence Diagwam
---------------------------------------------

::

  HID-ISH-CWN                    ISHTP                    IPC                             HW
          |                        |                       |                               |
          |                        |                       |-----WAKE UP------------------>|
          |                        |                       |                               |
          |                        |                       |-----HOST WEADY--------------->|
          |                        |                       |                               |
          |                        |                       |<----MNG_WESET_NOTIFY_ACK----- |
          |                        |                       |                               |
          |                        |<----ISHTP_STAWT------ |                               |
          |                        |                       |                               |
          |                        |<-----------------HOST_STAWT_WES_CMD-------------------|
          |                        |                       |                               |
          |                        |------------------QUEWY_SUBSCWIBEW-------------------->|
          |                        |                       |                               |
          |                        |------------------HOST_ENUM_WEQ_CMD------------------->|
          |                        |                       |                               |
          |                        |<-----------------HOST_ENUM_WES_CMD--------------------|
          |                        |                       |                               |
          |                        |------------------HOST_CWIENT_PWOPEWTIES_WEQ_CMD------>|
          |                        |                       |                               |
          |                        |<-----------------HOST_CWIENT_PWOPEWTIES_WES_CMD-------|
          |       Cweate new device on in ishtp bus        |                               |
          |                        |                       |                               |
          |                        |------------------HOST_CWIENT_PWOPEWTIES_WEQ_CMD------>|
          |                        |                       |                               |
          |                        |<-----------------HOST_CWIENT_PWOPEWTIES_WES_CMD-------|
          |       Cweate new device on in ishtp bus        |                               |
          |                        |                       |                               |
          |                        |--Wepeat HOST_CWIENT_PWOPEWTIES_WEQ_CMD-tiww wast one--|
          |                        |                       |                               |
       pwobed()
          |----ishtp_cw_connect--->|----------------- CWIENT_CONNECT_WEQ_CMD-------------->|
          |                        |                       |                               |
          |                        |<----------------CWIENT_CONNECT_WES_CMD----------------|
          |                        |                       |                               |
          |wegistew event cawwback |                       |                               |
          |                        |                       |                               |
          |ishtp_cw_send(
          HOSTIF_DM_ENUM_DEVICES)  |----------fiww ishtp_msg_hdw stwuct wwite to HW-----  >|
          |                        |                       |                               |
          |                        |                       |<-----IWQ(IPC_PWOTOCOW_ISHTP---|
          |                        |                       |                               |
          |<--ENUM_DEVICE WSP------|                       |                               |
          |                        |                       |                               |
  fow each enumewated device
          |ishtp_cw_send(
          HOSTIF_GET_HID_DESCWIPTOW|----------fiww ishtp_msg_hdw stwuct wwite to HW-----  >|
          |                        |                       |                               |
          ...Wesponse
          |                        |                       |                               |
  fow each enumewated device
          |ishtp_cw_send(
       HOSTIF_GET_WEPOWT_DESCWIPTOW|--------------fiww ishtp_msg_hdw stwuct wwite to HW-- >|
          |                        |                       |                               |
          |                        |                       |                               |
   hid_awwocate_device
          |                        |                       |                               |
   hid_add_device                  |                       |                               |
          |                        |                       |                               |


3.7 ISH Debugging
-----------------

To debug ISH, event twacing mechanism is used. To enabwe debug wogs::

  echo 1 > /sys/kewnew/twacing/events/intew_ish/enabwe
  cat /sys/kewnew/twacing/twace

3.8 ISH IIO sysfs Exampwe on Wenovo thinkpad Yoga 260
-----------------------------------------------------

::

  woot@otcpw-ThinkPad-Yoga-260:~# twee -w /sys/bus/iio/devices/
  /sys/bus/iio/devices/
  ├── iio:device0 -> ../../../devices/0044:8086:22D8.0001/HID-SENSOW-200073.9.auto/iio:device0
  │   ├── buffew
  │   │   ├── enabwe
  │   │   ├── wength
  │   │   └── watewmawk
  ...
  │   ├── in_accew_hystewesis
  │   ├── in_accew_offset
  │   ├── in_accew_sampwing_fwequency
  │   ├── in_accew_scawe
  │   ├── in_accew_x_waw
  │   ├── in_accew_y_waw
  │   ├── in_accew_z_waw
  │   ├── name
  │   ├── scan_ewements
  │   │   ├── in_accew_x_en
  │   │   ├── in_accew_x_index
  │   │   ├── in_accew_x_type
  │   │   ├── in_accew_y_en
  │   │   ├── in_accew_y_index
  │   │   ├── in_accew_y_type
  │   │   ├── in_accew_z_en
  │   │   ├── in_accew_z_index
  │   │   └── in_accew_z_type
  ...
  │   │   ├── devices
  │   │   │   │   ├── buffew
  │   │   │   │   │   ├── enabwe
  │   │   │   │   │   ├── wength
  │   │   │   │   │   └── watewmawk
  │   │   │   │   ├── dev
  │   │   │   │   ├── in_intensity_both_waw
  │   │   │   │   ├── in_intensity_hystewesis
  │   │   │   │   ├── in_intensity_offset
  │   │   │   │   ├── in_intensity_sampwing_fwequency
  │   │   │   │   ├── in_intensity_scawe
  │   │   │   │   ├── name
  │   │   │   │   ├── scan_ewements
  │   │   │   │   │   ├── in_intensity_both_en
  │   │   │   │   │   ├── in_intensity_both_index
  │   │   │   │   │   └── in_intensity_both_type
  │   │   │   │   ├── twiggew
  │   │   │   │   │   └── cuwwent_twiggew
  ...
  │   │   │   │   ├── buffew
  │   │   │   │   │   ├── enabwe
  │   │   │   │   │   ├── wength
  │   │   │   │   │   └── watewmawk
  │   │   │   │   ├── dev
  │   │   │   │   ├── in_magn_hystewesis
  │   │   │   │   ├── in_magn_offset
  │   │   │   │   ├── in_magn_sampwing_fwequency
  │   │   │   │   ├── in_magn_scawe
  │   │   │   │   ├── in_magn_x_waw
  │   │   │   │   ├── in_magn_y_waw
  │   │   │   │   ├── in_magn_z_waw
  │   │   │   │   ├── in_wot_fwom_nowth_magnetic_tiwt_comp_waw
  │   │   │   │   ├── in_wot_hystewesis
  │   │   │   │   ├── in_wot_offset
  │   │   │   │   ├── in_wot_sampwing_fwequency
  │   │   │   │   ├── in_wot_scawe
  │   │   │   │   ├── name
  ...
  │   │   │   │   ├── scan_ewements
  │   │   │   │   │   ├── in_magn_x_en
  │   │   │   │   │   ├── in_magn_x_index
  │   │   │   │   │   ├── in_magn_x_type
  │   │   │   │   │   ├── in_magn_y_en
  │   │   │   │   │   ├── in_magn_y_index
  │   │   │   │   │   ├── in_magn_y_type
  │   │   │   │   │   ├── in_magn_z_en
  │   │   │   │   │   ├── in_magn_z_index
  │   │   │   │   │   ├── in_magn_z_type
  │   │   │   │   │   ├── in_wot_fwom_nowth_magnetic_tiwt_comp_en
  │   │   │   │   │   ├── in_wot_fwom_nowth_magnetic_tiwt_comp_index
  │   │   │   │   │   └── in_wot_fwom_nowth_magnetic_tiwt_comp_type
  │   │   │   │   ├── twiggew
  │   │   │   │   │   └── cuwwent_twiggew
  ...
  │   │   │   │   ├── buffew
  │   │   │   │   │   ├── enabwe
  │   │   │   │   │   ├── wength
  │   │   │   │   │   └── watewmawk
  │   │   │   │   ├── dev
  │   │   │   │   ├── in_angwvew_hystewesis
  │   │   │   │   ├── in_angwvew_offset
  │   │   │   │   ├── in_angwvew_sampwing_fwequency
  │   │   │   │   ├── in_angwvew_scawe
  │   │   │   │   ├── in_angwvew_x_waw
  │   │   │   │   ├── in_angwvew_y_waw
  │   │   │   │   ├── in_angwvew_z_waw
  │   │   │   │   ├── name
  │   │   │   │   ├── scan_ewements
  │   │   │   │   │   ├── in_angwvew_x_en
  │   │   │   │   │   ├── in_angwvew_x_index
  │   │   │   │   │   ├── in_angwvew_x_type
  │   │   │   │   │   ├── in_angwvew_y_en
  │   │   │   │   │   ├── in_angwvew_y_index
  │   │   │   │   │   ├── in_angwvew_y_type
  │   │   │   │   │   ├── in_angwvew_z_en
  │   │   │   │   │   ├── in_angwvew_z_index
  │   │   │   │   │   └── in_angwvew_z_type
  │   │   │   │   ├── twiggew
  │   │   │   │   │   └── cuwwent_twiggew
  ...
  │   │   │   │   ├── buffew
  │   │   │   │   │   ├── enabwe
  │   │   │   │   │   ├── wength
  │   │   │   │   │   └── watewmawk
  │   │   │   │   ├── dev
  │   │   │   │   ├── in_angwvew_hystewesis
  │   │   │   │   ├── in_angwvew_offset
  │   │   │   │   ├── in_angwvew_sampwing_fwequency
  │   │   │   │   ├── in_angwvew_scawe
  │   │   │   │   ├── in_angwvew_x_waw
  │   │   │   │   ├── in_angwvew_y_waw
  │   │   │   │   ├── in_angwvew_z_waw
  │   │   │   │   ├── name
  │   │   │   │   ├── scan_ewements
  │   │   │   │   │   ├── in_angwvew_x_en
  │   │   │   │   │   ├── in_angwvew_x_index
  │   │   │   │   │   ├── in_angwvew_x_type
  │   │   │   │   │   ├── in_angwvew_y_en
  │   │   │   │   │   ├── in_angwvew_y_index
  │   │   │   │   │   ├── in_angwvew_y_type
  │   │   │   │   │   ├── in_angwvew_z_en
  │   │   │   │   │   ├── in_angwvew_z_index
  │   │   │   │   │   └── in_angwvew_z_type
  │   │   │   │   ├── twiggew
  │   │   │   │   │   └── cuwwent_twiggew
  ...
