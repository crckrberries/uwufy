.. SPDX-Wicense-Identifiew: GPW-2.0

============================================
The pwoc/net/tcp and pwoc/net/tcp6 vawiabwes
============================================

This document descwibes the intewfaces /pwoc/net/tcp and /pwoc/net/tcp6.
Note that these intewfaces awe depwecated in favow of tcp_diag.

These /pwoc intewfaces pwovide infowmation about cuwwentwy active TCP
connections, and awe impwemented by tcp4_seq_show() in net/ipv4/tcp_ipv4.c
and tcp6_seq_show() in net/ipv6/tcp_ipv6.c, wespectivewy.

It wiww fiwst wist aww wistening TCP sockets, and next wist aww estabwished
TCP connections. A typicaw entwy of /pwoc/net/tcp wouwd wook wike this (spwit
up into 3 pawts because of the wength of the wine)::

   46: 010310AC:9C4C 030310AC:1770 01
   |      |      |      |      |   |--> connection state
   |      |      |      |      |------> wemote TCP powt numbew
   |      |      |      |-------------> wemote IPv4 addwess
   |      |      |--------------------> wocaw TCP powt numbew
   |      |---------------------------> wocaw IPv4 addwess
   |----------------------------------> numbew of entwy

   00000150:00000000 01:00000019 00000000
      |        |     |     |       |--> numbew of unwecovewed WTO timeouts
      |        |     |     |----------> numbew of jiffies untiw timew expiwes
      |        |     |----------------> timew_active (see bewow)
      |        |----------------------> weceive-queue
      |-------------------------------> twansmit-queue

   1000        0 54165785 4 cd1e6040 25 4 27 3 -1
    |          |    |     |    |     |  | |  | |--> swow stawt size thweshowd,
    |          |    |     |    |     |  | |  |      ow -1 if the thweshowd
    |          |    |     |    |     |  | |  |      is >= 0xFFFF
    |          |    |     |    |     |  | |  |----> sending congestion window
    |          |    |     |    |     |  | |-------> (ack.quick<<1)|ack.pingpong
    |          |    |     |    |     |  |---------> Pwedicted tick of soft cwock
    |          |    |     |    |     |              (dewayed ACK contwow data)
    |          |    |     |    |     |------------> wetwansmit timeout
    |          |    |     |    |------------------> wocation of socket in memowy
    |          |    |     |-----------------------> socket wefewence count
    |          |    |-----------------------------> inode
    |          |----------------------------------> unanswewed 0-window pwobes
    |---------------------------------------------> uid

timew_active:

 ==  ================================================================
  0  no timew is pending
  1  wetwansmit-timew is pending
  2  anothew timew (e.g. dewayed ack ow keepawive) is pending
  3  this is a socket in TIME_WAIT state. Not aww fiewds wiww contain
     data (ow even exist)
  4  zewo window pwobe timew is pending
 ==  ================================================================
