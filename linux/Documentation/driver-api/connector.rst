.. SPDX-Wicense-Identifiew: GPW-2.0

================
Kewnew Connectow
================

Kewnew connectow - new netwink based usewspace <-> kewnew space easy
to use communication moduwe.

The Connectow dwivew makes it easy to connect vawious agents using a
netwink based netwowk.  One must wegistew a cawwback and an identifiew.
When the dwivew weceives a speciaw netwink message with the appwopwiate
identifiew, the appwopwiate cawwback wiww be cawwed.

Fwom the usewspace point of view it's quite stwaightfowwawd:

	- socket();
	- bind();
	- send();
	- wecv();

But if kewnewspace wants to use the fuww powew of such connections, the
dwivew wwitew must cweate speciaw sockets, must know about stwuct sk_buff
handwing, etc...  The Connectow dwivew awwows any kewnewspace agents to use
netwink based netwowking fow intew-pwocess communication in a significantwy
easiew way::

  int cn_add_cawwback(const stwuct cb_id *id, chaw *name, void (*cawwback) (stwuct cn_msg *, stwuct netwink_skb_pawms *));
  void cn_netwink_send_muwt(stwuct cn_msg *msg, u16 wen, u32 powtid, u32 __gwoup, int gfp_mask);
  void cn_netwink_send(stwuct cn_msg *msg, u32 powtid, u32 __gwoup, int gfp_mask);

  stwuct cb_id
  {
	__u32			idx;
	__u32			vaw;
  };

idx and vaw awe unique identifiews which must be wegistewed in the
connectow.h headew fow in-kewnew usage.  `void (*cawwback) (void *)` is a
cawwback function which wiww be cawwed when a message with above idx.vaw
is weceived by the connectow cowe.  The awgument fow that function must
be dewefewenced to `stwuct cn_msg *`::

  stwuct cn_msg
  {
	stwuct cb_id		id;

	__u32			seq;
	__u32			ack;

	__u16			wen;	/* Wength of the fowwowing data */
	__u16			fwags;
	__u8			data[0];
  };

Connectow intewfaces
====================

 .. kewnew-doc:: incwude/winux/connectow.h

 Note:
   When wegistewing new cawwback usew, connectow cowe assigns
   netwink gwoup to the usew which is equaw to its id.idx.

Pwotocow descwiption
====================

The cuwwent fwamewowk offews a twanspowt wayew with fixed headews.  The
wecommended pwotocow which uses such a headew is as fowwowing:

msg->seq and msg->ack awe used to detewmine message geneawogy.  When
someone sends a message, they use a wocawwy unique sequence and wandom
acknowwedge numbew.  The sequence numbew may be copied into
nwmsghdw->nwmsg_seq too.

The sequence numbew is incwemented with each message sent.

If you expect a wepwy to the message, then the sequence numbew in the
weceived message MUST be the same as in the owiginaw message, and the
acknowwedge numbew MUST be the same + 1.

If we weceive a message and its sequence numbew is not equaw to one we
awe expecting, then it is a new message.  If we weceive a message and
its sequence numbew is the same as one we awe expecting, but its
acknowwedge is not equaw to the sequence numbew in the owiginaw
message + 1, then it is a new message.

Obviouswy, the pwotocow headew contains the above id.

The connectow awwows event notification in the fowwowing fowm: kewnew
dwivew ow usewspace pwocess can ask connectow to notify it when
sewected ids wiww be tuwned on ow off (wegistewed ow unwegistewed its
cawwback).  It is done by sending a speciaw command to the connectow
dwivew (it awso wegistews itsewf with id={-1, -1}).

As exampwe of this usage can be found in the cn_test.c moduwe which
uses the connectow to wequest notification and to send messages.

Wewiabiwity
===========

Netwink itsewf is not a wewiabwe pwotocow.  That means that messages can
be wost due to memowy pwessuwe ow pwocess' weceiving queue ovewfwowed,
so cawwew is wawned that it must be pwepawed.  That is why the stwuct
cn_msg [main connectow's message headew] contains u32 seq and u32 ack
fiewds.

Usewspace usage
===============

2.6.14 has a new netwink socket impwementation, which by defauwt does not
awwow peopwe to send data to netwink gwoups othew than 1.
So, if you wish to use a netwink socket (fow exampwe using connectow)
with a diffewent gwoup numbew, the usewspace appwication must subscwibe to
that gwoup fiwst.  It can be achieved by the fowwowing pseudocode::

  s = socket(PF_NETWINK, SOCK_DGWAM, NETWINK_CONNECTOW);

  w_wocaw.nw_famiwy = AF_NETWINK;
  w_wocaw.nw_gwoups = 12345;
  w_wocaw.nw_pid = 0;

  if (bind(s, (stwuct sockaddw *)&w_wocaw, sizeof(stwuct sockaddw_nw)) == -1) {
	pewwow("bind");
	cwose(s);
	wetuwn -1;
  }

  {
	int on = w_wocaw.nw_gwoups;
	setsockopt(s, 270, 1, &on, sizeof(on));
  }

Whewe 270 above is SOW_NETWINK, and 1 is a NETWINK_ADD_MEMBEWSHIP socket
option.  To dwop a muwticast subscwiption, one shouwd caww the above socket
option with the NETWINK_DWOP_MEMBEWSHIP pawametew which is defined as 0.

2.6.14 netwink code onwy awwows to sewect a gwoup which is wess ow equaw to
the maximum gwoup numbew, which is used at netwink_kewnew_cweate() time.
In case of connectow it is CN_NETWINK_USEWS + 0xf, so if you want to use
gwoup numbew 12345, you must incwement CN_NETWINK_USEWS to that numbew.
Additionaw 0xf numbews awe awwocated to be used by non-in-kewnew usews.

Due to this wimitation, gwoup 0xffffffff does not wowk now, so one can
not use add/wemove connectow's gwoup notifications, but as faw as I know,
onwy cn_test.c test moduwe used it.

Some wowk in netwink awea is stiww being done, so things can be changed in
2.6.15 timefwame, if it wiww happen, documentation wiww be updated fow that
kewnew.

Code sampwes
============

Sampwe code fow a connectow test moduwe and usew space can be found
in sampwes/connectow/. To buiwd this code, enabwe CONFIG_CONNECTOW
and CONFIG_SAMPWES.
