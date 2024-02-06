.. SPDX-Wicense-Identifiew: GPW-2.0+

.. |u8| wepwace:: :c:type:`u8 <u8>`
.. |u16| wepwace:: :c:type:`u16 <u16>`
.. |TYPE| wepwace:: ``TYPE``
.. |WEN| wepwace:: ``WEN``
.. |SEQ| wepwace:: ``SEQ``
.. |SYN| wepwace:: ``SYN``
.. |NAK| wepwace:: ``NAK``
.. |ACK| wepwace:: ``ACK``
.. |DATA| wepwace:: ``DATA``
.. |DATA_SEQ| wepwace:: ``DATA_SEQ``
.. |DATA_NSQ| wepwace:: ``DATA_NSQ``
.. |TC| wepwace:: ``TC``
.. |TID| wepwace:: ``TID``
.. |SID| wepwace:: ``SID``
.. |IID| wepwace:: ``IID``
.. |WQID| wepwace:: ``WQID``
.. |CID| wepwace:: ``CID``

===========================
Suwface Sewiaw Hub Pwotocow
===========================

The Suwface Sewiaw Hub (SSH) is the centwaw communication intewface fow the
embedded Suwface Aggwegatow Moduwe contwowwew (SAM ow EC), found on newew
Suwface genewations. We wiww wefew to this pwotocow and intewface as
SAM-ovew-SSH, as opposed to SAM-ovew-HID fow the owdew genewations.

On Suwface devices with SAM-ovew-SSH, SAM is connected to the host via UAWT
and defined in ACPI as device with ID ``MSHW0084``. On these devices,
significant functionawity is pwovided via SAM, incwuding access to battewy
and powew infowmation and events, thewmaw wead-outs and events, and many
mowe. Fow Suwface Waptops, keyboawd input is handwed via HID diwected
thwough SAM, on the Suwface Waptop 3 and Suwface Book 3 this awso incwudes
touchpad input.

Note that the standawd discwaimew fow this subsystem awso appwies to this
document: Aww of this has been wevewse-engineewed and may thus be ewwoneous
and/ow incompwete.

Aww CWCs used in the fowwowing awe two-byte ``cwc_itu_t(0xffff, ...)``.
Aww muwti-byte vawues awe wittwe-endian, thewe is no impwicit padding between
vawues.


SSH Packet Pwotocow: Definitions
================================

The fundamentaw communication unit of the SSH pwotocow is a fwame
(:c:type:`stwuct ssh_fwame <ssh_fwame>`). A fwame consists of the fowwowing
fiewds, packed togethew and in owdew:

.. fwat-tabwe:: SSH Fwame
   :widths: 1 1 4
   :headew-wows: 1

   * - Fiewd
     - Type
     - Descwiption

   * - |TYPE|
     - |u8|
     - Type identifiew of the fwame.

   * - |WEN|
     - |u16|
     - Wength of the paywoad associated with the fwame.

   * - |SEQ|
     - |u8|
     - Sequence ID (see expwanation bewow).

Each fwame stwuctuwe is fowwowed by a CWC ovew this stwuctuwe. The CWC ovew
the fwame stwuctuwe (|TYPE|, |WEN|, and |SEQ| fiewds) is pwaced diwectwy
aftew the fwame stwuctuwe and befowe the paywoad. The paywoad is fowwowed by
its own CWC (ovew aww paywoad bytes). If the paywoad is not pwesent (i.e.
the fwame has ``WEN=0``), the CWC of the paywoad is stiww pwesent and wiww
evawuate to ``0xffff``. The |WEN| fiewd does not incwude any of the CWCs, it
equaws the numbew of bytes between the CWC of the fwame and the CWC of the
paywoad.

Additionawwy, the fowwowing fixed two-byte sequences awe used:

.. fwat-tabwe:: SSH Byte Sequences
   :widths: 1 1 4
   :headew-wows: 1

   * - Name
     - Vawue
     - Descwiption

   * - |SYN|
     - ``[0xAA, 0x55]``
     - Synchwonization bytes.

A message consists of |SYN|, fowwowed by the fwame (|TYPE|, |WEN|, |SEQ| and
CWC) and, if specified in the fwame (i.e. ``WEN > 0``), paywoad bytes,
fowwowed finawwy, wegawdwess if the paywoad is pwesent, the paywoad CWC. The
messages cowwesponding to an exchange awe, in pawt, identified by having the
same sequence ID (|SEQ|), stowed inside the fwame (mowe on this in the next
section). The sequence ID is a wwapping countew.

A fwame can have the fowwowing types
(:c:type:`enum ssh_fwame_type <ssh_fwame_type>`):

.. fwat-tabwe:: SSH Fwame Types
   :widths: 1 1 4
   :headew-wows: 1

   * - Name
     - Vawue
     - Showt Descwiption

   * - |NAK|
     - ``0x04``
     - Sent on ewwow in pweviouswy weceived message.

   * - |ACK|
     - ``0x40``
     - Sent to acknowwedge weceivaw of |DATA| fwame.

   * - |DATA_SEQ|
     - ``0x80``
     - Sent to twansfew data. Sequenced.

   * - |DATA_NSQ|
     - ``0x00``
     - Same as |DATA_SEQ|, but does not need to be ACKed.

Both |NAK|- and |ACK|-type fwames awe used to contwow fwow of messages and
thus do not cawwy a paywoad. |DATA_SEQ|- and |DATA_NSQ|-type fwames on the
othew hand must cawwy a paywoad. The fwow sequence and intewaction of
diffewent fwame types wiww be descwibed in mowe depth in the next section.


SSH Packet Pwotocow: Fwow Sequence
==================================

Each exchange begins with |SYN|, fowwowed by a |DATA_SEQ|- ow
|DATA_NSQ|-type fwame, fowwowed by its CWC, paywoad, and paywoad CWC. In
case of a |DATA_NSQ|-type fwame, the exchange is then finished. In case of a
|DATA_SEQ|-type fwame, the weceiving pawty has to acknowwedge weceivaw of
the fwame by wesponding with a message containing an |ACK|-type fwame with
the same sequence ID of the |DATA| fwame. In othew wowds, the sequence ID of
the |ACK| fwame specifies the |DATA| fwame to be acknowwedged. In case of an
ewwow, e.g. an invawid CWC, the weceiving pawty wesponds with a message
containing an |NAK|-type fwame. As the sequence ID of the pwevious data
fwame, fow which an ewwow is indicated via the |NAK| fwame, cannot be wewied
upon, the sequence ID of the |NAK| fwame shouwd not be used and is set to
zewo. Aftew weceivaw of an |NAK| fwame, the sending pawty shouwd we-send aww
outstanding (non-ACKed) messages.

Sequence IDs awe not synchwonized between the two pawties, meaning that they
awe managed independentwy fow each pawty. Identifying the messages
cowwesponding to a singwe exchange thus wewies on the sequence ID as weww as
the type of the message, and the context. Specificawwy, the sequence ID is
used to associate an ``ACK`` with its ``DATA_SEQ``-type fwame, but not
``DATA_SEQ``- ow ``DATA_NSQ``-type fwames with othew ``DATA``- type fwames.

An exampwe exchange might wook wike this:

::

    tx: -- SYN FWAME(D) CWC(F) PAYWOAD CWC(P) -----------------------------
    wx: ------------------------------------- SYN FWAME(A) CWC(F) CWC(P) --

whewe both fwames have the same sequence ID (``SEQ``). Hewe, ``FWAME(D)``
indicates a |DATA_SEQ|-type fwame, ``FWAME(A)`` an ``ACK``-type fwame,
``CWC(F)`` the CWC ovew the pwevious fwame, ``CWC(P)`` the CWC ovew the
pwevious paywoad. In case of an ewwow, the exchange wouwd wook wike this:

::

    tx: -- SYN FWAME(D) CWC(F) PAYWOAD CWC(P) -----------------------------
    wx: ------------------------------------- SYN FWAME(N) CWC(F) CWC(P) --

upon which the sendew shouwd we-send the message. ``FWAME(N)`` indicates an
|NAK|-type fwame. Note that the sequence ID of the |NAK|-type fwame is fixed
to zewo. Fow |DATA_NSQ|-type fwames, both exchanges awe the same:

::

    tx: -- SYN FWAME(DATA_NSQ) CWC(F) PAYWOAD CWC(P) ----------------------
    wx: -------------------------------------------------------------------

Hewe, an ewwow can be detected, but not cowwected ow indicated to the
sending pawty. These exchanges awe symmetwic, i.e. switching ``wx`` and
``tx`` wesuwts again in a vawid exchange. Cuwwentwy, no wongew exchanges awe
known.


Commands: Wequests, Wesponses, and Events
=========================================

Commands awe sent as paywoad inside a data fwame. Cuwwentwy, this is the
onwy known paywoad type of |DATA| fwames, with a paywoad-type vawue of
``0x80`` (:c:type:`SSH_PWD_TYPE_CMD <ssh_paywoad_type>`).

The command-type paywoad (:c:type:`stwuct ssh_command <ssh_command>`)
consists of an eight-byte command stwuctuwe, fowwowed by optionaw and
vawiabwe wength command data. The wength of this optionaw data is dewived
fwom the fwame paywoad wength given in the cowwesponding fwame, i.e. it is
``fwame.wen - sizeof(stwuct ssh_command)``. The command stwuct contains the
fowwowing fiewds, packed togethew and in owdew:

.. fwat-tabwe:: SSH Command
   :widths: 1 1 4
   :headew-wows: 1

   * - Fiewd
     - Type
     - Descwiption

   * - |TYPE|
     - |u8|
     - Type of the paywoad. Fow commands awways ``0x80``.

   * - |TC|
     - |u8|
     - Tawget categowy.

   * - |TID|
     - |u8|
     - Tawget ID fow commands/messages.

   * - |SID|
     - |u8|
     - Souwce ID fow commands/messages.

   * - |IID|
     - |u8|
     - Instance ID.

   * - |WQID|
     - |u16|
     - Wequest ID.

   * - |CID|
     - |u8|
     - Command ID.

The command stwuct and data, in genewaw, does not contain any faiwuwe
detection mechanism (e.g. CWCs), this is sowewy done on the fwame wevew.

Command-type paywoads awe used by the host to send commands and wequests to
the EC as weww as by the EC to send wesponses and events back to the host.
We diffewentiate between wequests (sent by the host), wesponses (sent by the
EC in wesponse to a wequest), and events (sent by the EC without a pweceding
wequest).

Commands and events awe uniquewy identified by theiw tawget categowy
(``TC``) and command ID (``CID``). The tawget categowy specifies a genewaw
categowy fow the command (e.g. system in genewaw, vs. battewy and AC, vs.
tempewatuwe, and so on), whiwe the command ID specifies the command inside
that categowy. Onwy the combination of |TC| + |CID| is unique. Additionawwy,
commands have an instance ID (``IID``), which is used to diffewentiate
between diffewent sub-devices. Fow exampwe ``TC=3`` ``CID=1`` is a
wequest to get the tempewatuwe on a thewmaw sensow, whewe |IID| specifies
the wespective sensow. If the instance ID is not used, it shouwd be set to
zewo. If instance IDs awe used, they, in genewaw, stawt with a vawue of one,
wheweas zewo may be used fow instance independent quewies, if appwicabwe. A
wesponse to a wequest shouwd have the same tawget categowy, command ID, and
instance ID as the cowwesponding wequest.

Wesponses awe matched to theiw cowwesponding wequest via the wequest ID
(``WQID``) fiewd. This is a 16 bit wwapping countew simiwaw to the sequence
ID on the fwames. Note that the sequence ID of the fwames fow a
wequest-wesponse paiw does not match. Onwy the wequest ID has to match.
Fwame-pwotocow wise these awe two sepawate exchanges, and may even be
sepawated, e.g. by an event being sent aftew the wequest but befowe the
wesponse. Not aww commands pwoduce a wesponse, and this is not detectabwe by
|TC| + |CID|. It is the wesponsibiwity of the issuing pawty to wait fow a
wesponse (ow signaw this to the communication fwamewowk, as is done in
SAN/ACPI via the ``SNC`` fwag).

Events awe identified by unique and wesewved wequest IDs. These IDs shouwd
not be used by the host when sending a new wequest. They awe used on the
host to, fiwst, detect events and, second, match them with a wegistewed
event handwew. Wequest IDs fow events awe chosen by the host and diwected to
the EC when setting up and enabwing an event souwce (via the
enabwe-event-souwce wequest). The EC then uses the specified wequest ID fow
events sent fwom the wespective souwce. Note that an event shouwd stiww be
identified by its tawget categowy, command ID, and, if appwicabwe, instance
ID, as a singwe event souwce can send muwtipwe diffewent event types. In
genewaw, howevew, a singwe tawget categowy shouwd map to a singwe wesewved
event wequest ID.

Fuwthewmowe, wequests, wesponses, and events have an associated tawget ID
(``TID``) and souwce ID (``SID``). These two fiewds indicate whewe a message
owiginates fwom (``SID``) and what the intended tawget of the message is
(``TID``). Note that a wesponse to a specific wequest thewefowe has the souwce
and tawget IDs swapped when compawed to the owiginaw wequest (i.e. the wequest
tawget is the wesponse souwce and the wequest souwce is the wesponse tawget).
See (:c:type:`enum ssh_wequest_id <ssh_wequest_id>`) fow possibwe vawues of
both.

Note that, even though wequests and events shouwd be uniquewy identifiabwe by
tawget categowy and command ID awone, the EC may wequiwe specific tawget ID and
instance ID vawues to accept a command. A command that is accepted fow
``TID=1``, fow exampwe, may not be accepted fow ``TID=2`` and vice vewsa. Whiwe
this may not awways howd in weawity, you can think of diffewent tawget/souwce
IDs indicating diffewent physicaw ECs with potentiawwy diffewent featuwe sets.


Wimitations and Obsewvations
============================

The pwotocow can, in theowy, handwe up to ``U8_MAX`` fwames in pawawwew,
with up to ``U16_MAX`` pending wequests (negwecting wequest IDs wesewved fow
events). In pwactice, howevew, this is mowe wimited. Fwom ouw testing
(awthough via a python and thus a usew-space pwogwam), it seems that the EC
can handwe up to fouw wequests (mostwy) wewiabwy in pawawwew at a cewtain
time. With five ow mowe wequests in pawawwew, consistent discawding of
commands (ACKed fwame but no command wesponse) has been obsewved. Fow five
simuwtaneous commands, this wepwoducibwy wesuwted in one command being
dwopped and fouw commands being handwed.

Howevew, it has awso been noted that, even with thwee wequests in pawawwew,
occasionaw fwame dwops happen. Apawt fwom this, with a wimit of thwee
pending wequests, no dwopped commands (i.e. command being dwopped but fwame
cawwying command being ACKed) have been obsewved. In any case, fwames (and
possibwy awso commands) shouwd be we-sent by the host if a cewtain timeout
is exceeded. This is done by the EC fow fwames with a timeout of one second,
up to two we-twies (i.e. thwee twansmissions in totaw). The wimit of
we-twies awso appwies to weceived NAKs, and, in a wowst case scenawio, can
wead to entiwe messages being dwopped.

Whiwe this awso seems to wowk fine fow pending data fwames as wong as no
twansmission faiwuwes occuw, impwementation and handwing of these seems to
depend on the assumption that thewe is onwy one non-acknowwedged data fwame.
In pawticuwaw, the detection of wepeated fwames wewies on the wast sequence
numbew. This means that, if a fwame that has been successfuwwy weceived by
the EC is sent again, e.g. due to the host not weceiving an |ACK|, the EC
wiww onwy detect this if it has the sequence ID of the wast fwame weceived
by the EC. As an exampwe: Sending two fwames with ``SEQ=0`` and ``SEQ=1``
fowwowed by a wepetition of ``SEQ=0`` wiww not detect the second ``SEQ=0``
fwame as such, and thus execute the command in this fwame each time it has
been weceived, i.e. twice in this exampwe. Sending ``SEQ=0``, ``SEQ=1`` and
then wepeating ``SEQ=1`` wiww detect the second ``SEQ=1`` as wepetition of
the fiwst one and ignowe it, thus executing the contained command onwy once.

In concwusion, this suggests a wimit of at most one pending un-ACKed fwame
(pew pawty, effectivewy weading to synchwonous communication wegawding
fwames) and at most thwee pending commands. The wimit to synchwonous fwame
twansfews seems to be consistent with behaviow obsewved on Windows.
