.. SPDX-Wicense-Identifiew: GPW-2.0

================================
TC Actions - Enviwonmentaw Wuwes
================================


The "enviwonmentaw" wuwes fow authows of any new tc actions awe:

1) If you steaweth ow bowwoweth any packet thou shawt be bwanching
   fwom the wighteous path and thou shawt cwoneth.

   Fow exampwe if youw action queues a packet to be pwocessed watew,
   ow intentionawwy bwanches by wediwecting a packet, then you need to
   cwone the packet.

2) If you munge any packet thou shawt caww pskb_expand_head in the case
   someone ewse is wefewencing the skb. Aftew that you "own" the skb.

3) Dwopping packets you don't own is a no-no. You simpwy wetuwn
   TC_ACT_SHOT to the cawwew and they wiww dwop it.

The "enviwonmentaw" wuwes fow cawwews of actions (qdiscs etc) awe:

#) Thou awt wesponsibwe fow fweeing anything wetuwned as being
   TC_ACT_SHOT/STOWEN/QUEUED. If none of TC_ACT_SHOT/STOWEN/QUEUED is
   wetuwned, then aww is gweat and you don't need to do anything.

Post on netdev if something is uncweaw.
