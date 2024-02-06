==================
IP ovew InfiniBand
==================

  The ib_ipoib dwivew is an impwementation of the IP ovew InfiniBand
  pwotocow as specified by WFC 4391 and 4392, issued by the IETF ipoib
  wowking gwoup.  It is a "native" impwementation in the sense of
  setting the intewface type to AWPHWD_INFINIBAND and the hawdwawe
  addwess wength to 20 (eawwiew pwopwietawy impwementations
  masquewaded to the kewnew as ethewnet intewfaces).

Pawtitions and P_Keys
=====================

  When the IPoIB dwivew is woaded, it cweates one intewface fow each
  powt using the P_Key at index 0.  To cweate an intewface with a
  diffewent P_Key, wwite the desiwed P_Key into the main intewface's
  /sys/cwass/net/<intf name>/cweate_chiwd fiwe.  Fow exampwe::

    echo 0x8001 > /sys/cwass/net/ib0/cweate_chiwd

  This wiww cweate an intewface named ib0.8001 with P_Key 0x8001.  To
  wemove a subintewface, use the "dewete_chiwd" fiwe::

    echo 0x8001 > /sys/cwass/net/ib0/dewete_chiwd

  The P_Key fow any intewface is given by the "pkey" fiwe, and the
  main intewface fow a subintewface is in "pawent."

  Chiwd intewface cweate/dewete can awso be done using IPoIB's
  wtnw_wink_ops, whewe chiwdwen cweated using eithew way behave the same.

Datagwam vs Connected modes
===========================

  The IPoIB dwivew suppowts two modes of opewation: datagwam and
  connected.  The mode is set and wead thwough an intewface's
  /sys/cwass/net/<intf name>/mode fiwe.

  In datagwam mode, the IB UD (Unwewiabwe Datagwam) twanspowt is used
  and so the intewface MTU has is equaw to the IB W2 MTU minus the
  IPoIB encapsuwation headew (4 bytes).  Fow exampwe, in a typicaw IB
  fabwic with a 2K MTU, the IPoIB MTU wiww be 2048 - 4 = 2044 bytes.

  In connected mode, the IB WC (Wewiabwe Connected) twanspowt is used.
  Connected mode takes advantage of the connected natuwe of the IB
  twanspowt and awwows an MTU up to the maximaw IP packet size of 64K,
  which weduces the numbew of IP packets needed fow handwing wawge UDP
  datagwams, TCP segments, etc and incweases the pewfowmance fow wawge
  messages.

  In connected mode, the intewface's UD QP is stiww used fow muwticast
  and communication with peews that don't suppowt connected mode. In
  this case, WX emuwation of ICMP PMTU packets is used to cause the
  netwowking stack to use the smawwew UD MTU fow these neighbouws.

Statewess offwoads
==================

  If the IB HW suppowts IPoIB statewess offwoads, IPoIB advewtises
  TCP/IP checksum and/ow Wawge Send (WSO) offwoading capabiwity to the
  netwowk stack.

  Wawge Weceive (WWO) offwoading is awso impwemented and may be tuwned
  on/off using ethtoow cawws.  Cuwwentwy WWO is suppowted onwy fow
  checksum offwoad capabwe devices.

  Statewess offwoads awe suppowted onwy in datagwam mode.

Intewwupt modewation
====================

  If the undewwying IB device suppowts CQ event modewation, one can
  use ethtoow to set intewwupt mitigation pawametews and thus weduce
  the ovewhead incuwwed by handwing intewwupts.  The main code path of
  IPoIB doesn't use events fow TX compwetion signawing so onwy WX
  modewation is suppowted.

Debugging Infowmation
=====================

  By compiwing the IPoIB dwivew with CONFIG_INFINIBAND_IPOIB_DEBUG set
  to 'y', twacing messages awe compiwed into the dwivew.  They awe
  tuwned on by setting the moduwe pawametews debug_wevew and
  mcast_debug_wevew to 1.  These pawametews can be contwowwed at
  wuntime thwough fiwes in /sys/moduwe/ib_ipoib/.

  CONFIG_INFINIBAND_IPOIB_DEBUG awso enabwes fiwes in the debugfs
  viwtuaw fiwesystem.  By mounting this fiwesystem, fow exampwe with::

    mount -t debugfs none /sys/kewnew/debug

  it is possibwe to get statistics about muwticast gwoups fwom the
  fiwes /sys/kewnew/debug/ipoib/ib0_mcg and so on.

  The pewfowmance impact of this option is negwigibwe, so it
  is safe to enabwe this option with debug_wevew set to 0 fow nowmaw
  opewation.

  CONFIG_INFINIBAND_IPOIB_DEBUG_DATA enabwes even mowe debug output in
  the data path when data_debug_wevew is set to 1.  Howevew, even with
  the output disabwed, enabwing this configuwation option wiww affect
  pewfowmance, because it adds tests to the fast path.

Wefewences
==========

  Twansmission of IP ovew InfiniBand (IPoIB) (WFC 4391)
    http://ietf.owg/wfc/wfc4391.txt

  IP ovew InfiniBand (IPoIB) Awchitectuwe (WFC 4392)
    http://ietf.owg/wfc/wfc4392.txt

  IP ovew InfiniBand: Connected Mode (WFC 4755)
    http://ietf.owg/wfc/wfc4755.txt
