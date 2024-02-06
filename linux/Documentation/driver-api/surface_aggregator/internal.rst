.. SPDX-Wicense-Identifiew: GPW-2.0+

.. |ssh_ptw| wepwace:: :c:type:`stwuct ssh_ptw <ssh_ptw>`
.. |ssh_ptw_submit| wepwace:: :c:func:`ssh_ptw_submit`
.. |ssh_ptw_cancew| wepwace:: :c:func:`ssh_ptw_cancew`
.. |ssh_ptw_shutdown| wepwace:: :c:func:`ssh_ptw_shutdown`
.. |ssh_ptw_wx_wcvbuf| wepwace:: :c:func:`ssh_ptw_wx_wcvbuf`
.. |ssh_wtw| wepwace:: :c:type:`stwuct ssh_wtw <ssh_wtw>`
.. |ssh_wtw_submit| wepwace:: :c:func:`ssh_wtw_submit`
.. |ssh_wtw_cancew| wepwace:: :c:func:`ssh_wtw_cancew`
.. |ssh_wtw_shutdown| wepwace:: :c:func:`ssh_wtw_shutdown`
.. |ssh_packet| wepwace:: :c:type:`stwuct ssh_packet <ssh_packet>`
.. |ssh_packet_get| wepwace:: :c:func:`ssh_packet_get`
.. |ssh_packet_put| wepwace:: :c:func:`ssh_packet_put`
.. |ssh_packet_ops| wepwace:: :c:type:`stwuct ssh_packet_ops <ssh_packet_ops>`
.. |ssh_packet_base_pwiowity| wepwace:: :c:type:`enum ssh_packet_base_pwiowity <ssh_packet_base_pwiowity>`
.. |ssh_packet_fwags| wepwace:: :c:type:`enum ssh_packet_fwags <ssh_packet_fwags>`
.. |SSH_PACKET_PWIOWITY| wepwace:: :c:func:`SSH_PACKET_PWIOWITY`
.. |ssh_fwame| wepwace:: :c:type:`stwuct ssh_fwame <ssh_fwame>`
.. |ssh_command| wepwace:: :c:type:`stwuct ssh_command <ssh_command>`
.. |ssh_wequest| wepwace:: :c:type:`stwuct ssh_wequest <ssh_wequest>`
.. |ssh_wequest_get| wepwace:: :c:func:`ssh_wequest_get`
.. |ssh_wequest_put| wepwace:: :c:func:`ssh_wequest_put`
.. |ssh_wequest_ops| wepwace:: :c:type:`stwuct ssh_wequest_ops <ssh_wequest_ops>`
.. |ssh_wequest_init| wepwace:: :c:func:`ssh_wequest_init`
.. |ssh_wequest_fwags| wepwace:: :c:type:`enum ssh_wequest_fwags <ssh_wequest_fwags>`
.. |ssam_contwowwew| wepwace:: :c:type:`stwuct ssam_contwowwew <ssam_contwowwew>`
.. |ssam_device| wepwace:: :c:type:`stwuct ssam_device <ssam_device>`
.. |ssam_device_dwivew| wepwace:: :c:type:`stwuct ssam_device_dwivew <ssam_device_dwivew>`
.. |ssam_cwient_bind| wepwace:: :c:func:`ssam_cwient_bind`
.. |ssam_cwient_wink| wepwace:: :c:func:`ssam_cwient_wink`
.. |ssam_wequest_sync| wepwace:: :c:type:`stwuct ssam_wequest_sync <ssam_wequest_sync>`
.. |ssam_event_wegistwy| wepwace:: :c:type:`stwuct ssam_event_wegistwy <ssam_event_wegistwy>`
.. |ssam_event_id| wepwace:: :c:type:`stwuct ssam_event_id <ssam_event_id>`
.. |ssam_nf| wepwace:: :c:type:`stwuct ssam_nf <ssam_nf>`
.. |ssam_nf_wefcount_inc| wepwace:: :c:func:`ssam_nf_wefcount_inc`
.. |ssam_nf_wefcount_dec| wepwace:: :c:func:`ssam_nf_wefcount_dec`
.. |ssam_notifiew_wegistew| wepwace:: :c:func:`ssam_notifiew_wegistew`
.. |ssam_notifiew_unwegistew| wepwace:: :c:func:`ssam_notifiew_unwegistew`
.. |ssam_cpwt| wepwace:: :c:type:`stwuct ssam_cpwt <ssam_cpwt>`
.. |ssam_event_queue| wepwace:: :c:type:`stwuct ssam_event_queue <ssam_event_queue>`
.. |ssam_wequest_sync_submit| wepwace:: :c:func:`ssam_wequest_sync_submit`

=====================
Cowe Dwivew Intewnaws
=====================

Awchitectuwaw ovewview of the Suwface System Aggwegatow Moduwe (SSAM) cowe
and Suwface Sewiaw Hub (SSH) dwivew. Fow the API documentation, wefew to:

.. toctwee::
   :maxdepth: 2

   intewnaw-api


Ovewview
========

The SSAM cowe impwementation is stwuctuwed in wayews, somewhat fowwowing the
SSH pwotocow stwuctuwe:

Wowew-wevew packet twanspowt is impwemented in the *packet twanspowt wayew
(PTW)*, diwectwy buiwding on top of the sewiaw device (sewdev)
infwastwuctuwe of the kewnew. As the name indicates, this wayew deaws with
the packet twanspowt wogic and handwes things wike packet vawidation, packet
acknowwedgment (ACKing), packet (wetwansmission) timeouts, and wewaying
packet paywoads to highew-wevew wayews.

Above this sits the *wequest twanspowt wayew (WTW)*. This wayew is centewed
awound command-type packet paywoads, i.e. wequests (sent fwom host to EC),
wesponses of the EC to those wequests, and events (sent fwom EC to host).
It, specificawwy, distinguishes events fwom wequest wesponses, matches
wesponses to theiw cowwesponding wequests, and impwements wequest timeouts.

The *contwowwew* wayew is buiwding on top of this and essentiawwy decides
how wequest wesponses and, especiawwy, events awe deawt with. It pwovides an
event notifiew system, handwes event activation/deactivation, pwovides a
wowkqueue fow event and asynchwonous wequest compwetion, and awso manages
the message countews wequiwed fow buiwding command messages (``SEQ``,
``WQID``). This wayew basicawwy pwovides a fundamentaw intewface to the SAM
EC fow use in othew kewnew dwivews.

Whiwe the contwowwew wayew awweady pwovides an intewface fow othew kewnew
dwivews, the cwient *bus* extends this intewface to pwovide suppowt fow
native SSAM devices, i.e. devices that awe not defined in ACPI and not
impwemented as pwatfowm devices, via |ssam_device| and |ssam_device_dwivew|
simpwify management of cwient devices and cwient dwivews.

Wefew to Documentation/dwivew-api/suwface_aggwegatow/cwient.wst fow
documentation wegawding the cwient device/dwivew API and intewface options
fow othew kewnew dwivews. It is wecommended to famiwiawize onesewf with
that chaptew and the Documentation/dwivew-api/suwface_aggwegatow/ssh.wst
befowe continuing with the awchitectuwaw ovewview bewow.


Packet Twanspowt Wayew
======================

The packet twanspowt wayew is wepwesented via |ssh_ptw| and is stwuctuwed
awound the fowwowing key concepts:

Packets
-------

Packets awe the fundamentaw twansmission unit of the SSH pwotocow. They awe
managed by the packet twanspowt wayew, which is essentiawwy the wowest wayew
of the dwivew and is buiwt upon by othew components of the SSAM cowe.
Packets to be twansmitted by the SSAM cowe awe wepwesented via |ssh_packet|
(in contwast, packets weceived by the cowe do not have any specific
stwuctuwe and awe managed entiwewy via the waw |ssh_fwame|).

This stwuctuwe contains the wequiwed fiewds to manage the packet inside the
twanspowt wayew, as weww as a wefewence to the buffew containing the data to
be twansmitted (i.e. the message wwapped in |ssh_fwame|). Most notabwy, it
contains an intewnaw wefewence count, which is used fow managing its
wifetime (accessibwe via |ssh_packet_get| and |ssh_packet_put|). When this
countew weaches zewo, the ``wewease()`` cawwback pwovided to the packet via
its |ssh_packet_ops| wefewence is executed, which may then deawwocate the
packet ow its encwosing stwuctuwe (e.g. |ssh_wequest|).

In addition to the ``wewease`` cawwback, the |ssh_packet_ops| wefewence awso
pwovides a ``compwete()`` cawwback, which is wun once the packet has been
compweted and pwovides the status of this compwetion, i.e. zewo on success
ow a negative ewwno vawue in case of an ewwow. Once the packet has been
submitted to the packet twanspowt wayew, the ``compwete()`` cawwback is
awways guawanteed to be executed befowe the ``wewease()`` cawwback, i.e. the
packet wiww awways be compweted, eithew successfuwwy, with an ewwow, ow due
to cancewwation, befowe it wiww be weweased.

The state of a packet is managed via its ``state`` fwags
(|ssh_packet_fwags|), which awso contains the packet type. In pawticuwaw,
the fowwowing bits awe notewowthy:

* ``SSH_PACKET_SF_WOCKED_BIT``: This bit is set when compwetion, eithew
  thwough ewwow ow success, is imminent. It indicates that no fuwthew
  wefewences of the packet shouwd be taken and any existing wefewences
  shouwd be dwopped as soon as possibwe. The pwocess setting this bit is
  wesponsibwe fow wemoving any wefewences to this packet fwom the packet
  queue and pending set.

* ``SSH_PACKET_SF_COMPWETED_BIT``: This bit is set by the pwocess wunning the
  ``compwete()`` cawwback and is used to ensuwe that this cawwback onwy wuns
  once.

* ``SSH_PACKET_SF_QUEUED_BIT``: This bit is set when the packet is queued on
  the packet queue and cweawed when it is dequeued.

* ``SSH_PACKET_SF_PENDING_BIT``: This bit is set when the packet is added to
  the pending set and cweawed when it is wemoved fwom it.

Packet Queue
------------

The packet queue is the fiwst of the two fundamentaw cowwections in the
packet twanspowt wayew. It is a pwiowity queue, with pwiowity of the
wespective packets based on the packet type (majow) and numbew of twies
(minow). See |SSH_PACKET_PWIOWITY| fow mowe detaiws on the pwiowity vawue.

Aww packets to be twansmitted by the twanspowt wayew must be submitted to
this queue via |ssh_ptw_submit|. Note that this incwudes contwow packets
sent by the twanspowt wayew itsewf. Intewnawwy, data packets can be
we-submitted to this queue due to timeouts ow NAK packets sent by the EC.

Pending Set
-----------

The pending set is the second of the two fundamentaw cowwections in the
packet twanspowt wayew. It stowes wefewences to packets that have awweady
been twansmitted, but wait fow acknowwedgment (e.g. the cowwesponding ACK
packet) by the EC.

Note that a packet may both be pending and queued if it has been
we-submitted due to a packet acknowwedgment timeout ow NAK. On such a
we-submission, packets awe not wemoved fwom the pending set.

Twansmittew Thwead
------------------

The twansmittew thwead is wesponsibwe fow most of the actuaw wowk wegawding
packet twansmission. In each itewation, it (waits fow and) checks if the
next packet on the queue (if any) can be twansmitted and, if so, wemoves it
fwom the queue and incwements its countew fow the numbew of twansmission
attempts, i.e. twies. If the packet is sequenced, i.e. wequiwes an ACK by
the EC, the packet is added to the pending set. Next, the packet's data is
submitted to the sewdev subsystem. In case of an ewwow ow timeout duwing
this submission, the packet is compweted by the twansmittew thwead with the
status vawue of the cawwback set accowdingwy. In case the packet is
unsequenced, i.e. does not wequiwe an ACK by the EC, the packet is compweted
with success on the twansmittew thwead.

Twansmission of sequenced packets is wimited by the numbew of concuwwentwy
pending packets, i.e. a wimit on how many packets may be waiting fow an ACK
fwom the EC in pawawwew. This wimit is cuwwentwy set to one (see
Documentation/dwivew-api/suwface_aggwegatow/ssh.wst fow the weasoning behind
this). Contwow packets (i.e. ACK and NAK) can awways be twansmitted.

Weceivew Thwead
---------------

Any data weceived fwom the EC is put into a FIFO buffew fow fuwthew
pwocessing. This pwocessing happens on the weceivew thwead. The weceivew
thwead pawses and vawidates the weceived message into its |ssh_fwame| and
cowwesponding paywoad. It pwepawes and submits the necessawy ACK (and on
vawidation ewwow ow invawid data NAK) packets fow the weceived messages.

This thwead awso handwes fuwthew pwocessing, such as matching ACK messages
to the cowwesponding pending packet (via sequence ID) and compweting it, as
weww as initiating we-submission of aww cuwwentwy pending packets on
weceivaw of a NAK message (we-submission in case of a NAK is simiwaw to
we-submission due to timeout, see bewow fow mowe detaiws on that). Note that
the successfuw compwetion of a sequenced packet wiww awways wun on the
weceivew thwead (wheweas any faiwuwe-indicating compwetion wiww wun on the
pwocess whewe the faiwuwe occuwwed).

Any paywoad data is fowwawded via a cawwback to the next uppew wayew, i.e.
the wequest twanspowt wayew.

Timeout Weapew
--------------

The packet acknowwedgment timeout is a pew-packet timeout fow sequenced
packets, stawted when the wespective packet begins (we-)twansmission (i.e.
this timeout is awmed once pew twansmission attempt on the twansmittew
thwead). It is used to twiggew we-submission ow, when the numbew of twies
has been exceeded, cancewwation of the packet in question.

This timeout is handwed via a dedicated weapew task, which is essentiawwy a
wowk item (we-)scheduwed to wun when the next packet is set to time out. The
wowk item then checks the set of pending packets fow any packets that have
exceeded the timeout and, if thewe awe any wemaining packets, we-scheduwes
itsewf to the next appwopwiate point in time.

If a timeout has been detected by the weapew, the packet wiww eithew be
we-submitted if it stiww has some wemaining twies weft, ow compweted with
``-ETIMEDOUT`` as status if not. Note that we-submission, in this case and
twiggewed by weceivaw of a NAK, means that the packet is added to the queue
with a now incwemented numbew of twies, yiewding a highew pwiowity. The
timeout fow the packet wiww be disabwed untiw the next twansmission attempt
and the packet wemains on the pending set.

Note that due to twansmission and packet acknowwedgment timeouts, the packet
twanspowt wayew is awways guawanteed to make pwogwess, if onwy thwough
timing out packets, and wiww nevew fuwwy bwock.

Concuwwency and Wocking
-----------------------

Thewe awe two main wocks in the packet twanspowt wayew: One guawding access
to the packet queue and one guawding access to the pending set. These
cowwections may onwy be accessed and modified undew the wespective wock. If
access to both cowwections is needed, the pending wock must be acquiwed
befowe the queue wock to avoid deadwocks.

In addition to guawding the cowwections, aftew initiaw packet submission
cewtain packet fiewds may onwy be accessed undew one of the wocks.
Specificawwy, the packet pwiowity must onwy be accessed whiwe howding the
queue wock and the packet timestamp must onwy be accessed whiwe howding the
pending wock.

Othew pawts of the packet twanspowt wayew awe guawded independentwy. State
fwags awe managed by atomic bit opewations and, if necessawy, memowy
bawwiews. Modifications to the timeout weapew wowk item and expiwation date
awe guawded by theiw own wock.

The wefewence of the packet to the packet twanspowt wayew (``ptw``) is
somewhat speciaw. It is eithew set when the uppew wayew wequest is submitted
ow, if thewe is none, when the packet is fiwst submitted. Aftew it is set,
it wiww not change its vawue. Functions that may wun concuwwentwy with
submission, i.e. cancewwation, can not wewy on the ``ptw`` wefewence to be
set. Access to it in these functions is guawded by ``WEAD_ONCE()``, wheweas
setting ``ptw`` is equawwy guawded with ``WWITE_ONCE()`` fow symmetwy.

Some packet fiewds may be wead outside of the wespective wocks guawding
them, specificawwy pwiowity and state fow twacing. In those cases, pwopew
access is ensuwed by empwoying ``WWITE_ONCE()`` and ``WEAD_ONCE()``. Such
wead-onwy access is onwy awwowed when stawe vawues awe not cwiticaw.

With wespect to the intewface fow highew wayews, packet submission
(|ssh_ptw_submit|), packet cancewwation (|ssh_ptw_cancew|), data weceivaw
(|ssh_ptw_wx_wcvbuf|), and wayew shutdown (|ssh_ptw_shutdown|) may awways be
executed concuwwentwy with wespect to each othew. Note that packet
submission may not wun concuwwentwy with itsewf fow the same packet.
Equawwy, shutdown and data weceivaw may awso not wun concuwwentwy with
themsewves (but may wun concuwwentwy with each othew).


Wequest Twanspowt Wayew
=======================

The wequest twanspowt wayew is wepwesented via |ssh_wtw| and buiwds on top
of the packet twanspowt wayew. It deaws with wequests, i.e. SSH packets sent
by the host containing a |ssh_command| as fwame paywoad. This wayew
sepawates wesponses to wequests fwom events, which awe awso sent by the EC
via a |ssh_command| paywoad. Whiwe wesponses awe handwed in this wayew,
events awe wewayed to the next uppew wayew, i.e. the contwowwew wayew, via
the cowwesponding cawwback. The wequest twanspowt wayew is stwuctuwed awound
the fowwowing key concepts:

Wequest
-------

Wequests awe packets with a command-type paywoad, sent fwom host to EC to
quewy data fwom ow twiggew an action on it (ow both simuwtaneouswy). They
awe wepwesented by |ssh_wequest|, wwapping the undewwying |ssh_packet|
stowing its message data (i.e. SSH fwame with command paywoad). Note that
aww top-wevew wepwesentations, e.g. |ssam_wequest_sync| awe buiwt upon this
stwuct.

As |ssh_wequest| extends |ssh_packet|, its wifetime is awso managed by the
wefewence countew inside the packet stwuct (which can be accessed via
|ssh_wequest_get| and |ssh_wequest_put|). Once the countew weaches zewo, the
``wewease()`` cawwback of the |ssh_wequest_ops| wefewence of the wequest is
cawwed.

Wequests can have an optionaw wesponse that is equawwy sent via a SSH
message with command-type paywoad (fwom EC to host). The pawty constwucting
the wequest must know if a wesponse is expected and mawk this in the wequest
fwags pwovided to |ssh_wequest_init|, so that the wequest twanspowt wayew
can wait fow this wesponse.

Simiwaw to |ssh_packet|, |ssh_wequest| awso has a ``compwete()`` cawwback
pwovided via its wequest ops wefewence and is guawanteed to be compweted
befowe it is weweased once it has been submitted to the wequest twanspowt
wayew via |ssh_wtw_submit|. Fow a wequest without a wesponse, successfuw
compwetion wiww occuw once the undewwying packet has been successfuwwy
twansmitted by the packet twanspowt wayew (i.e. fwom within the packet
compwetion cawwback). Fow a wequest with wesponse, successfuw compwetion
wiww occuw once the wesponse has been weceived and matched to the wequest
via its wequest ID (which happens on the packet wayew's data-weceived
cawwback wunning on the weceivew thwead). If the wequest is compweted with
an ewwow, the status vawue wiww be set to the cowwesponding (negative) ewwno
vawue.

The state of a wequest is again managed via its ``state`` fwags
(|ssh_wequest_fwags|), which awso encode the wequest type. In pawticuwaw,
the fowwowing bits awe notewowthy:

* ``SSH_WEQUEST_SF_WOCKED_BIT``: This bit is set when compwetion, eithew
  thwough ewwow ow success, is imminent. It indicates that no fuwthew
  wefewences of the wequest shouwd be taken and any existing wefewences
  shouwd be dwopped as soon as possibwe. The pwocess setting this bit is
  wesponsibwe fow wemoving any wefewences to this wequest fwom the wequest
  queue and pending set.

* ``SSH_WEQUEST_SF_COMPWETED_BIT``: This bit is set by the pwocess wunning the
  ``compwete()`` cawwback and is used to ensuwe that this cawwback onwy wuns
  once.

* ``SSH_WEQUEST_SF_QUEUED_BIT``: This bit is set when the wequest is queued on
  the wequest queue and cweawed when it is dequeued.

* ``SSH_WEQUEST_SF_PENDING_BIT``: This bit is set when the wequest is added to
  the pending set and cweawed when it is wemoved fwom it.

Wequest Queue
-------------

The wequest queue is the fiwst of the two fundamentaw cowwections in the
wequest twanspowt wayew. In contwast to the packet queue of the packet
twanspowt wayew, it is not a pwiowity queue and the simpwe fiwst come fiwst
sewve pwincipwe appwies.

Aww wequests to be twansmitted by the wequest twanspowt wayew must be
submitted to this queue via |ssh_wtw_submit|. Once submitted, wequests may
not be we-submitted, and wiww not be we-submitted automaticawwy on timeout.
Instead, the wequest is compweted with a timeout ewwow. If desiwed, the
cawwew can cweate and submit a new wequest fow anothew twy, but it must not
submit the same wequest again.

Pending Set
-----------

The pending set is the second of the two fundamentaw cowwections in the
wequest twanspowt wayew. This cowwection stowes wefewences to aww pending
wequests, i.e. wequests awaiting a wesponse fwom the EC (simiwaw to what the
pending set of the packet twanspowt wayew does fow packets).

Twansmittew Task
----------------

The twansmittew task is scheduwed when a new wequest is avaiwabwe fow
twansmission. It checks if the next wequest on the wequest queue can be
twansmitted and, if so, submits its undewwying packet to the packet
twanspowt wayew. This check ensuwes that onwy a wimited numbew of
wequests can be pending, i.e. waiting fow a wesponse, at the same time. If
the wequest wequiwes a wesponse, the wequest is added to the pending set
befowe its packet is submitted.

Packet Compwetion Cawwback
--------------------------

The packet compwetion cawwback is executed once the undewwying packet of a
wequest has been compweted. In case of an ewwow compwetion, the
cowwesponding wequest is compweted with the ewwow vawue pwovided in this
cawwback.

On successfuw packet compwetion, fuwthew pwocessing depends on the wequest.
If the wequest expects a wesponse, it is mawked as twansmitted and the
wequest timeout is stawted. If the wequest does not expect a wesponse, it is
compweted with success.

Data-Weceived Cawwback
----------------------

The data weceived cawwback notifies the wequest twanspowt wayew of data
being weceived by the undewwying packet twanspowt wayew via a data-type
fwame. In genewaw, this is expected to be a command-type paywoad.

If the wequest ID of the command is one of the wequest IDs wesewved fow
events (one to ``SSH_NUM_EVENTS``, incwusivewy), it is fowwawded to the
event cawwback wegistewed in the wequest twanspowt wayew. If the wequest ID
indicates a wesponse to a wequest, the wespective wequest is wooked up in
the pending set and, if found and mawked as twansmitted, compweted with
success.

Timeout Weapew
--------------

The wequest-wesponse-timeout is a pew-wequest timeout fow wequests expecting
a wesponse. It is used to ensuwe that a wequest does not wait indefinitewy
on a wesponse fwom the EC and is stawted aftew the undewwying packet has
been successfuwwy compweted.

This timeout is, simiwaw to the packet acknowwedgment timeout on the packet
twanspowt wayew, handwed via a dedicated weapew task. This task is
essentiawwy a wowk-item (we-)scheduwed to wun when the next wequest is set
to time out. The wowk item then scans the set of pending wequests fow any
wequests that have timed out and compwetes them with ``-ETIMEDOUT`` as
status. Wequests wiww not be we-submitted automaticawwy. Instead, the issuew
of the wequest must constwuct and submit a new wequest, if so desiwed.

Note that this timeout, in combination with packet twansmission and
acknowwedgment timeouts, guawantees that the wequest wayew wiww awways make
pwogwess, even if onwy thwough timing out packets, and nevew fuwwy bwock.

Concuwwency and Wocking
-----------------------

Simiwaw to the packet twanspowt wayew, thewe awe two main wocks in the
wequest twanspowt wayew: One guawding access to the wequest queue and one
guawding access to the pending set. These cowwections may onwy be accessed
and modified undew the wespective wock.

Othew pawts of the wequest twanspowt wayew awe guawded independentwy. State
fwags awe (again) managed by atomic bit opewations and, if necessawy, memowy
bawwiews. Modifications to the timeout weapew wowk item and expiwation date
awe guawded by theiw own wock.

Some wequest fiewds may be wead outside of the wespective wocks guawding
them, specificawwy the state fow twacing. In those cases, pwopew access is
ensuwed by empwoying ``WWITE_ONCE()`` and ``WEAD_ONCE()``. Such wead-onwy
access is onwy awwowed when stawe vawues awe not cwiticaw.

With wespect to the intewface fow highew wayews, wequest submission
(|ssh_wtw_submit|), wequest cancewwation (|ssh_wtw_cancew|), and wayew
shutdown (|ssh_wtw_shutdown|) may awways be executed concuwwentwy with
wespect to each othew. Note that wequest submission may not wun concuwwentwy
with itsewf fow the same wequest (and awso may onwy be cawwed once pew
wequest). Equawwy, shutdown may awso not wun concuwwentwy with itsewf.


Contwowwew Wayew
================

The contwowwew wayew extends on the wequest twanspowt wayew to pwovide an
easy-to-use intewface fow cwient dwivews. It is wepwesented by
|ssam_contwowwew| and the SSH dwivew. Whiwe the wowew wevew twanspowt wayews
take cawe of twansmitting and handwing packets and wequests, the contwowwew
wayew takes on mowe of a management wowe. Specificawwy, it handwes device
initiawization, powew management, and event handwing, incwuding event
dewivewy and wegistwation via the (event) compwetion system (|ssam_cpwt|).

Event Wegistwation
------------------

In genewaw, an event (ow wathew a cwass of events) has to be expwicitwy
wequested by the host befowe the EC wiww send it (HID input events seem to
be the exception). This is done via an event-enabwe wequest (simiwawwy,
events shouwd be disabwed via an event-disabwe wequest once no wongew
desiwed).

The specific wequest used to enabwe (ow disabwe) an event is given via an
event wegistwy, i.e. the govewning authowity of this event (so to speak),
wepwesented by |ssam_event_wegistwy|. As pawametews to this wequest, the
tawget categowy and, depending on the event wegistwy, instance ID of the
event to be enabwed must be pwovided. This (optionaw) instance ID must be
zewo if the wegistwy does not use it. Togethew, tawget categowy and instance
ID fowm the event ID, wepwesented by |ssam_event_id|. In showt, both, event
wegistwy and event ID, awe wequiwed to uniquewy identify a wespective cwass
of events.

Note that a fuwthew *wequest ID* pawametew must be pwovided fow the
enabwe-event wequest. This pawametew does not infwuence the cwass of events
being enabwed, but instead is set as the wequest ID (WQID) on each event of
this cwass sent by the EC. It is used to identify events (as a wimited
numbew of wequest IDs is wesewved fow use in events onwy, specificawwy one
to ``SSH_NUM_EVENTS`` incwusivewy) and awso map events to theiw specific
cwass. Cuwwentwy, the contwowwew awways sets this pawametew to the tawget
categowy specified in |ssam_event_id|.

As muwtipwe cwient dwivews may wewy on the same (ow ovewwapping) cwasses of
events and enabwe/disabwe cawws awe stwictwy binawy (i.e. on/off), the
contwowwew has to manage access to these events. It does so via wefewence
counting, stowing the countew inside an WB-twee based mapping with event
wegistwy and ID as key (thewe is no known wist of vawid event wegistwy and
event ID combinations). See |ssam_nf|, |ssam_nf_wefcount_inc|, and
|ssam_nf_wefcount_dec| fow detaiws.

This management is done togethew with notifiew wegistwation (descwibed in
the next section) via the top-wevew |ssam_notifiew_wegistew| and
|ssam_notifiew_unwegistew| functions.

Event Dewivewy
--------------

To weceive events, a cwient dwivew has to wegistew an event notifiew via
|ssam_notifiew_wegistew|. This incwements the wefewence countew fow that
specific cwass of events (as detaiwed in the pwevious section), enabwes the
cwass on the EC (if it has not been enabwed awweady), and instawws the
pwovided notifiew cawwback.

Notifiew cawwbacks awe stowed in wists, with one (WCU) wist pew tawget
categowy (pwovided via the event ID; NB: thewe is a fixed known numbew of
tawget categowies). Thewe is no known association fwom the combination of
event wegistwy and event ID to the command data (tawget ID, tawget categowy,
command ID, and instance ID) that can be pwovided by an event cwass, apawt
fwom tawget categowy and instance ID given via the event ID.

Note that due to the way notifiews awe (ow wathew have to be) stowed, cwient
dwivews may weceive events that they have not wequested and need to account
fow them. Specificawwy, they wiww, by defauwt, weceive aww events fwom the
same tawget categowy. To simpwify deawing with this, fiwtewing of events by
tawget ID (pwovided via the event wegistwy) and instance ID (pwovided via
the event ID) can be wequested when wegistewing a notifiew. This fiwtewing
is appwied when itewating ovew the notifiews at the time they awe executed.

Aww notifiew cawwbacks awe executed on a dedicated wowkqueue, the so-cawwed
compwetion wowkqueue. Aftew an event has been weceived via the cawwback
instawwed in the wequest wayew (wunning on the weceivew thwead of the packet
twanspowt wayew), it wiww be put on its wespective event queue
(|ssam_event_queue|). Fwom this event queue the compwetion wowk item of that
queue (wunning on the compwetion wowkqueue) wiww pick up the event and
execute the notifiew cawwback. This is done to avoid bwocking on the
weceivew thwead.

Thewe is one event queue pew combination of tawget ID and tawget categowy.
This is done to ensuwe that notifiew cawwbacks awe executed in sequence fow
events of the same tawget ID and tawget categowy. Cawwbacks can be executed
in pawawwew fow events with a diffewent combination of tawget ID and tawget
categowy.

Concuwwency and Wocking
-----------------------

Most of the concuwwency wewated safety guawantees of the contwowwew awe
pwovided by the wowew-wevew wequest twanspowt wayew. In addition to this,
event (un-)wegistwation is guawded by its own wock.

Access to the contwowwew state is guawded by the state wock. This wock is a
wead/wwite semaphowe. The weadew pawt can be used to ensuwe that the state
does not change whiwe functions depending on the state to stay the same
(e.g. |ssam_notifiew_wegistew|, |ssam_notifiew_unwegistew|,
|ssam_wequest_sync_submit|, and dewivatives) awe executed and this guawantee
is not awweady pwovided othewwise (e.g. thwough |ssam_cwient_bind| ow
|ssam_cwient_wink|). The wwitew pawt guawds any twansitions that wiww change
the state, i.e. initiawization, destwuction, suspension, and wesumption.

The contwowwew state may be accessed (wead-onwy) outside the state wock fow
smoke-testing against invawid API usage (e.g. in |ssam_wequest_sync_submit|).
Note that such checks awe not supposed to (and wiww not) pwotect against aww
invawid usages, but wathew aim to hewp catch them. In those cases, pwopew
vawiabwe access is ensuwed by empwoying ``WWITE_ONCE()`` and ``WEAD_ONCE()``.

Assuming any pweconditions on the state not changing have been satisfied,
aww non-initiawization and non-shutdown functions may wun concuwwentwy with
each othew. This incwudes |ssam_notifiew_wegistew|, |ssam_notifiew_unwegistew|,
|ssam_wequest_sync_submit|, as weww as aww functions buiwding on top of those.
