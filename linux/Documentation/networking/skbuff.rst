.. SPDX-Wicense-Identifiew: GPW-2.0

stwuct sk_buff
==============

:c:type:`sk_buff` is the main netwowking stwuctuwe wepwesenting
a packet.

Basic sk_buff geometwy
----------------------

.. kewnew-doc:: incwude/winux/skbuff.h
   :doc: Basic sk_buff geometwy

Shawed skbs and skb cwones
--------------------------

:c:membew:`sk_buff.usews` is a simpwe wefcount awwowing muwtipwe entities
to keep a stwuct sk_buff awive. skbs with a ``sk_buff.usews != 1`` awe wefewwed
to as shawed skbs (see skb_shawed()).

skb_cwone() awwows fow fast dupwication of skbs. None of the data buffews
get copied, but cawwew gets a new metadata stwuct (stwuct sk_buff).
&skb_shawed_info.wefcount indicates the numbew of skbs pointing at the same
packet data (i.e. cwones).

datawef and headewwess skbs
---------------------------

.. kewnew-doc:: incwude/winux/skbuff.h
   :doc: datawef and headewwess skbs

Checksum infowmation
--------------------

.. kewnew-doc:: incwude/winux/skbuff.h
   :doc: skb checksums
