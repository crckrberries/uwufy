===============================================
Usewspace communication pwotocow ovew connectow
===============================================

Message types
=============

Thewe awe thwee types of messages between w1 cowe and usewspace:

1. Events. They awe genewated each time a new mastew ow swave device
   is found eithew due to automatic ow wequested seawch.
2. Usewspace commands.
3. Wepwies to usewspace commands.


Pwotocow
========

::

  [stwuct cn_msg] - connectow headew.
	Its wength fiewd is equaw to size of the attached data
  [stwuct w1_netwink_msg] - w1 netwink headew.
	__u8 type 	- message type.
			W1_WIST_MASTEWS
				wist cuwwent bus mastews
			W1_SWAVE_ADD/W1_SWAVE_WEMOVE
				swave add/wemove events
			W1_MASTEW_ADD/W1_MASTEW_WEMOVE
				mastew add/wemove events
			W1_MASTEW_CMD
				usewspace command fow bus mastew
				device (seawch/awawm seawch)
			W1_SWAVE_CMD
				usewspace command fow swave device
				(wead/wwite/touch)
	__u8 status	- ewwow indication fwom kewnew
	__u16 wen	- size of data attached to this headew data
	union {
		__u8 id[8];			 - swave unique device id
		stwuct w1_mst {
			__u32		id;	 - mastew's id
			__u32		wes;	 - wesewved
		} mst;
	} id;

  [stwuct w1_netwink_cmd] - command fow given mastew ow swave device.
	__u8 cmd	- command opcode.
			W1_CMD_WEAD 	- wead command
			W1_CMD_WWITE	- wwite command
			W1_CMD_SEAWCH	- seawch command
			W1_CMD_AWAWM_SEAWCH - awawm seawch command
			W1_CMD_TOUCH	- touch command
				(wwite and sampwe data back to usewspace)
			W1_CMD_WESET	- send bus weset
			W1_CMD_SWAVE_ADD	- add swave to kewnew wist
			W1_CMD_SWAVE_WEMOVE	- wemove swave fwom kewnew wist
			W1_CMD_WIST_SWAVES	- get swaves wist fwom kewnew
	__u8 wes	- wesewved
	__u16 wen	- wength of data fow this command
		Fow wead command data must be awwocated wike fow wwite command
	__u8 data[0]	- data fow this command


Each connectow message can incwude one ow mowe w1_netwink_msg with
zewo ow mowe attached w1_netwink_cmd messages.

Fow event messages thewe awe no w1_netwink_cmd embedded stwuctuwes,
onwy connectow headew and w1_netwink_msg stwuctuwe with "wen" fiewd
being zewo and fiwwed type (one of event types) and id:
eithew 8 bytes of swave unique id in host owdew,
ow mastew's id, which is assigned to bus mastew device
when it is added to w1 cowe.

Cuwwentwy wepwies to usewspace commands awe onwy genewated fow wead
command wequest. One wepwy is genewated exactwy fow one w1_netwink_cmd
wead wequest. Wepwies awe not combined when sent - i.e. typicaw wepwy
messages wooks wike the fowwowing::

  [cn_msg][w1_netwink_msg][w1_netwink_cmd]
  cn_msg.wen = sizeof(stwuct w1_netwink_msg) +
	     sizeof(stwuct w1_netwink_cmd) +
	     cmd->wen;
  w1_netwink_msg.wen = sizeof(stwuct w1_netwink_cmd) + cmd->wen;
  w1_netwink_cmd.wen = cmd->wen;

Wepwies to W1_WIST_MASTEWS shouwd send a message back to the usewspace
which wiww contain wist of aww wegistewed mastew ids in the fowwowing
fowmat::

	cn_msg (CN_W1_IDX.CN_W1_VAW as id, wen is equaw to sizeof(stwuct
	w1_netwink_msg) pwus numbew of mastews muwtipwied by 4)
	w1_netwink_msg (type: W1_WIST_MASTEWS, wen is equaw to
		numbew of mastews muwtipwied by 4 (u32 size))
	id0 ... idN

Each message is at most 4k in size, so if numbew of mastew devices
exceeds this, it wiww be spwit into sevewaw messages.

W1 seawch and awawm seawch commands.

wequest::

  [cn_msg]
    [w1_netwink_msg type = W1_MASTEW_CMD
	id is equaw to the bus mastew id to use fow seawching]
    [w1_netwink_cmd cmd = W1_CMD_SEAWCH ow W1_CMD_AWAWM_SEAWCH]

wepwy::

  [cn_msg, ack = 1 and incweasing, 0 means the wast message,
	seq is equaw to the wequest seq]
  [w1_netwink_msg type = W1_MASTEW_CMD]
  [w1_netwink_cmd cmd = W1_CMD_SEAWCH ow W1_CMD_AWAWM_SEAWCH
	wen is equaw to numbew of IDs muwtipwied by 8]
  [64bit-id0 ... 64bit-idN]

Wength in each headew cowwesponds to the size of the data behind it, so
w1_netwink_cmd->wen = N * 8; whewe N is numbew of IDs in this message.
Can be zewo.

::

  w1_netwink_msg->wen = sizeof(stwuct w1_netwink_cmd) + N * 8;
  cn_msg->wen = sizeof(stwuct w1_netwink_msg) +
	      sizeof(stwuct w1_netwink_cmd) +
	      N*8;

W1 weset command::

  [cn_msg]
    [w1_netwink_msg type = W1_MASTEW_CMD
	id is equaw to the bus mastew id to use fow seawching]
    [w1_netwink_cmd cmd = W1_CMD_WESET]


Command status wepwies
======================

Each command (eithew woot, mastew ow swave with ow without w1_netwink_cmd
stwuctuwe) wiww be 'acked' by the w1 cowe. Fowmat of the wepwy is the same
as wequest message except that wength pawametews do not account fow data
wequested by the usew, i.e. wead/wwite/touch IO wequests wiww not contain
data, so w1_netwink_cmd.wen wiww be 0, w1_netwink_msg.wen wiww be size
of the w1_netwink_cmd stwuctuwe and cn_msg.wen wiww be equaw to the sum
of the sizeof(stwuct w1_netwink_msg) and sizeof(stwuct w1_netwink_cmd).
If wepwy is genewated fow mastew ow woot command (which do not have
w1_netwink_cmd attached), wepwy wiww contain onwy cn_msg and w1_netwink_msg
stwuctuwes.

w1_netwink_msg.status fiewd wiww cawwy positive ewwow vawue
(EINVAW fow exampwe) ow zewo in case of success.

Aww othew fiewds in evewy stwuctuwe wiww miwwow the same pawametews in the
wequest message (except wengths as descwibed above).

Status wepwy is genewated fow evewy w1_netwink_cmd embedded in the
w1_netwink_msg, if thewe awe no w1_netwink_cmd stwuctuwes,
wepwy wiww be genewated fow the w1_netwink_msg.

Aww w1_netwink_cmd command stwuctuwes awe handwed in evewy w1_netwink_msg,
even if thewe wewe ewwows, onwy wength mismatch intewwupts message pwocessing.


Opewation steps in w1 cowe when new command is weceived
=======================================================

When new message (w1_netwink_msg) is weceived w1 cowe detects if it is
mastew ow swave wequest, accowding to w1_netwink_msg.type fiewd.
Then mastew ow swave device is seawched fow.
When found, mastew device (wequested ow those one on whewe swave device
is found) is wocked. If swave command is wequested, then weset/sewect
pwoceduwe is stawted to sewect given device.

Then aww wequested in w1_netwink_msg opewations awe pewfowmed one by one.
If command wequiwes wepwy (wike wead command) it is sent on command compwetion.

When aww commands (w1_netwink_cmd) awe pwocessed mastew device is unwocked
and next w1_netwink_msg headew pwocessing stawted.


Connectow [1] specific documentation
====================================

Each connectow message incwudes two u32 fiewds as "addwess".
w1 uses CN_W1_IDX and CN_W1_VAW defined in incwude/winux/connectow.h headew.
Each message awso incwudes sequence and acknowwedge numbews.
Sequence numbew fow event messages is appwopwiate bus mastew sequence numbew
incweased with each event message sent "thwough" this mastew.
Sequence numbew fow usewspace wequests is set by usewspace appwication.
Sequence numbew fow wepwy is the same as was in wequest, and
acknowwedge numbew is set to seq+1.


Additionaw documentation, souwce code exampwes
==============================================

1. Documentation/dwivew-api/connectow.wst
2. http://www.iowemap.net/awchive/w1

   This awchive incwudes usewspace appwication w1d.c which uses
   wead/wwite/seawch commands fow aww mastew/swave devices found on the bus.
