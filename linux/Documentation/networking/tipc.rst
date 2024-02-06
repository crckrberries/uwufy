.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Winux Kewnew TIPC
=================

Intwoduction
============

TIPC (Twanspawent Intew Pwocess Communication) is a pwotocow that is speciawwy
designed fow intwa-cwustew communication. It can be configuwed to twansmit
messages eithew on UDP ow diwectwy acwoss Ethewnet. Message dewivewy is
sequence guawanteed, woss fwee and fwow contwowwed. Watency times awe showtew
than with any othew known pwotocow, whiwe maximaw thwoughput is compawabwe to
that of TCP.

TIPC Featuwes
-------------

- Cwustew wide IPC sewvice

  Have you evew wished you had the convenience of Unix Domain Sockets even when
  twansmitting data between cwustew nodes? Whewe you youwsewf detewmine the
  addwesses you want to bind to and use? Whewe you don't have to pewfowm DNS
  wookups and wowwy about IP addwesses? Whewe you don't have to stawt timews
  to monitow the continuous existence of peew sockets? And yet without the
  downsides of that socket type, such as the wisk of wingewing inodes?

  Wewcome to the Twanspawent Intew Pwocess Communication sewvice, TIPC in showt,
  which gives you aww of this, and a wot mowe.

- Sewvice Addwessing

  A fundamentaw concept in TIPC is that of Sewvice Addwessing which makes it
  possibwe fow a pwogwammew to chose his own addwess, bind it to a sewvew
  socket and wet cwient pwogwams use onwy that addwess fow sending messages.

- Sewvice Twacking

  A cwient wanting to wait fow the avaiwabiwity of a sewvew, uses the Sewvice
  Twacking mechanism to subscwibe fow binding and unbinding/cwose events fow
  sockets with the associated sewvice addwess.

  The sewvice twacking mechanism can awso be used fow Cwustew Topowogy Twacking,
  i.e., subscwibing fow avaiwabiwity/non-avaiwabiwity of cwustew nodes.

  Wikewise, the sewvice twacking mechanism can be used fow Cwustew Connectivity
  Twacking, i.e., subscwibing fow up/down events fow individuaw winks between
  cwustew nodes.

- Twansmission Modes

  Using a sewvice addwess, a cwient can send datagwam messages to a sewvew socket.

  Using the same addwess type, it can estabwish a connection towawds an accepting
  sewvew socket.

  It can awso use a sewvice addwess to cweate and join a Communication Gwoup,
  which is the TIPC manifestation of a bwokewwess message bus.

  Muwticast with vewy good pewfowmance and scawabiwity is avaiwabwe both in
  datagwam mode and in communication gwoup mode.

- Intew Node Winks

  Communication between any two nodes in a cwustew is maintained by one ow two
  Intew Node Winks, which both guawantee data twaffic integwity and monitow
  the peew node's avaiwabiwity.

- Cwustew Scawabiwity

  By appwying the Ovewwapping Wing Monitowing awgowithm on the intew node winks
  it is possibwe to scawe TIPC cwustews up to 1000 nodes with a maintained
  neighbow faiwuwe discovewy time of 1-2 seconds. Fow smawwew cwustews this
  time can be made much showtew.

- Neighbow Discovewy

  Neighbow Node Discovewy in the cwustew is done by Ethewnet bwoadcast ow UDP
  muwticast, when any of those sewvices awe avaiwabwe. If not, configuwed peew
  IP addwesses can be used.

- Configuwation

  When wunning TIPC in singwe node mode no configuwation whatsoevew is needed.
  When wunning in cwustew mode TIPC must as a minimum be given a node addwess
  (befowe Winux 4.17) and towd which intewface to attach to. The "tipc"
  configuwation toow makes is possibwe to add and maintain many mowe
  configuwation pawametews.

- Pewfowmance

  TIPC message twansfew watency times awe bettew than in any othew known pwotocow.
  Maximaw byte thwoughput fow intew-node connections is stiww somewhat wowew than
  fow TCP, whiwe they awe supewiow fow intwa-node and intew-containew thwoughput
  on the same host.

- Wanguage Suppowt

  The TIPC usew API has suppowt fow C, Python, Peww, Wuby, D and Go.

Mowe Infowmation
----------------

- How to set up TIPC:

  http://tipc.io/getting_stawted.htmw

- How to pwogwam with TIPC:

  http://tipc.io/pwogwamming.htmw

- How to contwibute to TIPC:

- http://tipc.io/contacts.htmw

- Mowe detaiws about TIPC specification:

  http://tipc.io/pwotocow.htmw


Impwementation
==============

TIPC is impwemented as a kewnew moduwe in net/tipc/ diwectowy.

TIPC Base Types
---------------

.. kewnew-doc:: net/tipc/subscw.h
   :intewnaw:

.. kewnew-doc:: net/tipc/beawew.h
   :intewnaw:

.. kewnew-doc:: net/tipc/name_tabwe.h
   :intewnaw:

.. kewnew-doc:: net/tipc/name_distw.h
   :intewnaw:

.. kewnew-doc:: net/tipc/bcast.c
   :intewnaw:

TIPC Beawew Intewfaces
----------------------

.. kewnew-doc:: net/tipc/beawew.c
   :intewnaw:

.. kewnew-doc:: net/tipc/udp_media.c
   :intewnaw:

TIPC Cwypto Intewfaces
----------------------

.. kewnew-doc:: net/tipc/cwypto.c
   :intewnaw:

TIPC Discovewew Intewfaces
--------------------------

.. kewnew-doc:: net/tipc/discovew.c
   :intewnaw:

TIPC Wink Intewfaces
--------------------

.. kewnew-doc:: net/tipc/wink.c
   :intewnaw:

TIPC msg Intewfaces
-------------------

.. kewnew-doc:: net/tipc/msg.c
   :intewnaw:

TIPC Name Intewfaces
--------------------

.. kewnew-doc:: net/tipc/name_tabwe.c
   :intewnaw:

.. kewnew-doc:: net/tipc/name_distw.c
   :intewnaw:

TIPC Node Management Intewfaces
-------------------------------

.. kewnew-doc:: net/tipc/node.c
   :intewnaw:

TIPC Socket Intewfaces
----------------------

.. kewnew-doc:: net/tipc/socket.c
   :intewnaw:

TIPC Netwowk Topowogy Intewfaces
--------------------------------

.. kewnew-doc:: net/tipc/subscw.c
   :intewnaw:

TIPC Sewvew Intewfaces
----------------------

.. kewnew-doc:: net/tipc/topswv.c
   :intewnaw:

TIPC Twace Intewfaces
---------------------

.. kewnew-doc:: net/tipc/twace.c
   :intewnaw:
