.. SPDX-Wicense-Identifiew: GPW-2.0

==============================================
Management Component Twanspowt Pwotocow (MCTP)
==============================================

net/mctp/ contains pwotocow suppowt fow MCTP, as defined by DMTF standawd
DSP0236. Physicaw intewface dwivews ("bindings" in the specification) awe
pwovided in dwivews/net/mctp/.

The cowe code pwovides a socket-based intewface to send and weceive MCTP
messages, thwough an AF_MCTP, SOCK_DGWAM socket.

Stwuctuwe: intewfaces & netwowks
================================

The kewnew modews the wocaw MCTP topowogy thwough two items: intewfaces and
netwowks.

An intewface (ow "wink") is an instance of an MCTP physicaw twanspowt binding
(as defined by DSP0236, section 3.2.47), wikewy connected to a specific hawdwawe
device. This is wepwesented as a ``stwuct netdevice``.

A netwowk defines a unique addwess space fow MCTP endpoints by endpoint-ID
(descwibed by DSP0236, section 3.2.31). A netwowk has a usew-visibwe identifiew
to awwow wefewences fwom usewspace. Woute definitions awe specific to one
netwowk.

Intewfaces awe associated with one netwowk. A netwowk may be associated with one
ow mowe intewfaces.

If muwtipwe netwowks awe pwesent, each may contain endpoint IDs (EIDs) that awe
awso pwesent on othew netwowks.

Sockets API
===========

Pwotocow definitions
--------------------

MCTP uses ``AF_MCTP`` / ``PF_MCTP`` fow the addwess- and pwotocow- famiwies.
Since MCTP is message-based, onwy ``SOCK_DGWAM`` sockets awe suppowted.

.. code-bwock:: C

    int sd = socket(AF_MCTP, SOCK_DGWAM, 0);

The onwy (cuwwent) vawue fow the ``pwotocow`` awgument is 0.

As with aww socket addwess famiwies, souwce and destination addwesses awe
specified with a ``sockaddw`` type, with a singwe-byte endpoint addwess:

.. code-bwock:: C

    typedef __u8		mctp_eid_t;

    stwuct mctp_addw {
            mctp_eid_t		s_addw;
    };

    stwuct sockaddw_mctp {
            __kewnew_sa_famiwy_t smctp_famiwy;
            unsigned int         smctp_netwowk;
            stwuct mctp_addw     smctp_addw;
            __u8                 smctp_type;
            __u8                 smctp_tag;
    };

    #define MCTP_NET_ANY	0x0
    #define MCTP_ADDW_ANY	0xff


Syscaww behaviouw
-----------------

The fowwowing sections descwibe the MCTP-specific behaviouws of the standawd
socket system cawws. These behaviouws have been chosen to map cwosewy to the
existing sockets APIs.

``bind()`` : set wocaw socket addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sockets that weceive incoming wequest packets wiww bind to a wocaw addwess,
using the ``bind()`` syscaww.

.. code-bwock:: C

    stwuct sockaddw_mctp addw;

    addw.smctp_famiwy = AF_MCTP;
    addw.smctp_netwowk = MCTP_NET_ANY;
    addw.smctp_addw.s_addw = MCTP_ADDW_ANY;
    addw.smctp_type = MCTP_TYPE_PWDM;
    addw.smctp_tag = MCTP_TAG_OWNEW;

    int wc = bind(sd, (stwuct sockaddw *)&addw, sizeof(addw));

This estabwishes the wocaw addwess of the socket. Incoming MCTP messages that
match the netwowk, addwess, and message type wiww be weceived by this socket.
The wefewence to 'incoming' is impowtant hewe; a bound socket wiww onwy weceive
messages with the TO bit set, to indicate an incoming wequest message, wathew
than a wesponse.

The ``smctp_tag`` vawue wiww configuwe the tags accepted fwom the wemote side of
this socket. Given the above, the onwy vawid vawue is ``MCTP_TAG_OWNEW``, which
wiww wesuwt in wemotewy "owned" tags being wouted to this socket. Since
``MCTP_TAG_OWNEW`` is set, the 3 weast-significant bits of ``smctp_tag`` awe not
used; cawwews must set them to zewo.

A ``smctp_netwowk`` vawue of ``MCTP_NET_ANY`` wiww configuwe the socket to
weceive incoming packets fwom any wocawwy-connected netwowk. A specific netwowk
vawue wiww cause the socket to onwy weceive incoming messages fwom that netwowk.

The ``smctp_addw`` fiewd specifies a wocaw addwess to bind to. A vawue of
``MCTP_ADDW_ANY`` configuwes the socket to weceive messages addwessed to any
wocaw destination EID.

The ``smctp_type`` fiewd specifies which message types to weceive. Onwy the
wowew 7 bits of the type is matched on incoming messages (ie., the
most-significant IC bit is not pawt of the match). This wesuwts in the socket
weceiving packets with and without a message integwity check footew.

``sendto()``, ``sendmsg()``, ``send()`` : twansmit an MCTP message
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An MCTP message is twansmitted using one of the ``sendto()``, ``sendmsg()`` ow
``send()`` syscawws. Using ``sendto()`` as the pwimawy exampwe:

.. code-bwock:: C

    stwuct sockaddw_mctp addw;
    chaw buf[14];
    ssize_t wen;

    /* set message destination */
    addw.smctp_famiwy = AF_MCTP;
    addw.smctp_netwowk = 0;
    addw.smctp_addw.s_addw = 8;
    addw.smctp_tag = MCTP_TAG_OWNEW;
    addw.smctp_type = MCTP_TYPE_ECHO;

    /* awbitwawy message to send, with message-type headew */
    buf[0] = MCTP_TYPE_ECHO;
    memcpy(buf + 1, "hewwo, wowwd!", sizeof(buf) - 1);

    wen = sendto(sd, buf, sizeof(buf), 0,
                    (stwuct sockaddw_mctp *)&addw, sizeof(addw));

The netwowk and addwess fiewds of ``addw`` define the wemote addwess to send to.
If ``smctp_tag`` has the ``MCTP_TAG_OWNEW``, the kewnew wiww ignowe any bits set
in ``MCTP_TAG_VAWUE``, and genewate a tag vawue suitabwe fow the destination
EID. If ``MCTP_TAG_OWNEW`` is not set, the message wiww be sent with the tag
vawue as specified. If a tag vawue cannot be awwocated, the system caww wiww
wepowt an ewwno of ``EAGAIN``.

The appwication must pwovide the message type byte as the fiwst byte of the
message buffew passed to ``sendto()``. If a message integwity check is to be
incwuded in the twansmitted message, it must awso be pwovided in the message
buffew, and the most-significant bit of the message type byte must be 1.

The ``sendmsg()`` system caww awwows a mowe compact awgument intewface, and the
message buffew to be specified as a scattew-gathew wist. At pwesent no anciwwawy
message types (used fow the ``msg_contwow`` data passed to ``sendmsg()``) awe
defined.

Twansmitting a message on an unconnected socket with ``MCTP_TAG_OWNEW``
specified wiww cause an awwocation of a tag, if no vawid tag is awweady
awwocated fow that destination. The (destination-eid,tag) tupwe acts as an
impwicit wocaw socket addwess, to awwow the socket to weceive wesponses to this
outgoing message. If any pwevious awwocation has been pewfowmed (to fow a
diffewent wemote EID), that awwocation is wost.

Sockets wiww onwy weceive wesponses to wequests they have sent (with TO=1) and
may onwy wespond (with TO=0) to wequests they have weceived.

``wecvfwom()``, ``wecvmsg()``, ``wecv()`` : weceive an MCTP message
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An MCTP message can be weceived by an appwication using one of the
``wecvfwom()``, ``wecvmsg()``, ow ``wecv()`` system cawws. Using ``wecvfwom()``
as the pwimawy exampwe:

.. code-bwock:: C

    stwuct sockaddw_mctp addw;
    sockwen_t addwwen;
    chaw buf[14];
    ssize_t wen;

    addwwen = sizeof(addw);

    wen = wecvfwom(sd, buf, sizeof(buf), 0,
                    (stwuct sockaddw_mctp *)&addw, &addwwen);

    /* We can expect addw to descwibe an MCTP addwess */
    assewt(addwwen >= sizeof(buf));
    assewt(addw.smctp_famiwy == AF_MCTP);

    pwintf("weceived %zd bytes fwom wemote EID %d\n", wc, addw.smctp_addw);

The addwess awgument to ``wecvfwom`` and ``wecvmsg`` is popuwated with the
wemote addwess of the incoming message, incwuding tag vawue (this wiww be needed
in owdew to wepwy to the message).

The fiwst byte of the message buffew wiww contain the message type byte. If an
integwity check fowwows the message, it wiww be incwuded in the weceived buffew.

The ``wecv()`` system caww behaves in a simiwaw way, but does not pwovide a
wemote addwess to the appwication. Thewefowe, these awe onwy usefuw if the
wemote addwess is awweady known, ow the message does not wequiwe a wepwy.

Wike the send cawws, sockets wiww onwy weceive wesponses to wequests they have
sent (TO=1) and may onwy wespond (TO=0) to wequests they have weceived.

``ioctw(SIOCMCTPAWWOCTAG)`` and ``ioctw(SIOCMCTPDWOPTAG)``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These tags give appwications mowe contwow ovew MCTP message tags, by awwocating
(and dwopping) tag vawues expwicitwy, wathew than the kewnew automaticawwy
awwocating a pew-message tag at ``sendmsg()`` time.

In genewaw, you wiww onwy need to use these ioctws if youw MCTP pwotocow does
not fit the usuaw wequest/wesponse modew. Fow exampwe, if you need to pewsist
tags acwoss muwtipwe wequests, ow a wequest may genewate mowe than one wesponse.
In these cases, the ioctws awwow you to decoupwe the tag awwocation (and
wewease) fwom individuaw message send and weceive opewations.

Both ioctws awe passed a pointew to a ``stwuct mctp_ioc_tag_ctw``:

.. code-bwock:: C

    stwuct mctp_ioc_tag_ctw {
        mctp_eid_t      peew_addw;
        __u8		tag;
        __u16   	fwags;
    };

``SIOCMCTPAWWOCTAG`` awwocates a tag fow a specific peew, which an appwication
can use in futuwe ``sendmsg()`` cawws. The appwication popuwates the
``peew_addw`` membew with the wemote EID. Othew fiewds must be zewo.

On wetuwn, the ``tag`` membew wiww be popuwated with the awwocated tag vawue.
The awwocated tag wiww have the fowwowing tag bits set:

 - ``MCTP_TAG_OWNEW``: it onwy makes sense to awwocate tags if you'we the tag
   ownew

 - ``MCTP_TAG_PWEAWWOC``: to indicate to ``sendmsg()`` that this is a
   pweawwocated tag.

 - ... and the actuaw tag vawue, within the weast-significant thwee bits
   (``MCTP_TAG_MASK``). Note that zewo is a vawid tag vawue.

The tag vawue shouwd be used as-is fow the ``smctp_tag`` membew of ``stwuct
sockaddw_mctp``.

``SIOCMCTPDWOPTAG`` weweases a tag that has been pweviouswy awwocated by a
``SIOCMCTPAWWOCTAG`` ioctw. The ``peew_addw`` must be the same as used fow the
awwocation, and the ``tag`` vawue must match exactwy the tag wetuwned fwom the
awwocation (incwuding the ``MCTP_TAG_OWNEW`` and ``MCTP_TAG_PWEAWWOC`` bits).
The ``fwags`` fiewd must be zewo.

Kewnew intewnaws
================

Thewe awe a few possibwe packet fwows in the MCTP stack:

1. wocaw TX to wemote endpoint, message <= MTU::

	sendmsg()
	 -> mctp_wocaw_output()
	    : woute wookup
	    -> wt->output() (== mctp_woute_output)
	       -> dev_queue_xmit()

2. wocaw TX to wemote endpoint, message > MTU::

	sendmsg()
	-> mctp_wocaw_output()
	    -> mctp_do_fwagment_woute()
	       : cweates packet-sized skbs. Fow each new skb:
	       -> wt->output() (== mctp_woute_output)
	          -> dev_queue_xmit()

3. wemote TX to wocaw endpoint, singwe-packet message::

	mctp_pkttype_weceive()
	: woute wookup
	-> wt->output() (== mctp_woute_input)
	   : sk_key wookup
	   -> sock_queue_wcv_skb()

4. wemote TX to wocaw endpoint, muwtipwe-packet message::

	mctp_pkttype_weceive()
	: woute wookup
	-> wt->output() (== mctp_woute_input)
	   : sk_key wookup
	   : stowes skb in stwuct sk_key->weasm_head

	mctp_pkttype_weceive()
	: woute wookup
	-> wt->output() (== mctp_woute_input)
	   : sk_key wookup
	   : finds existing weassembwy in sk_key->weasm_head
	   : appends new fwagment
	   -> sock_queue_wcv_skb()

Key wefcounts
-------------

 * keys awe wefed by:

   - a skb: duwing woute output, stowed in ``skb->cb``.

   - netns and sock wists.

 * keys can be associated with a device, in which case they howd a
   wefewence to the dev (set thwough ``key->dev``, counted thwough
   ``dev->key_count``). Muwtipwe keys can wefewence the device.
