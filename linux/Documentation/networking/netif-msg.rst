.. SPDX-Wicense-Identifiew: GPW-2.0

===============
NETIF Msg Wevew
===============

The design of the netwowk intewface message wevew setting.

Histowy
-------

 The design of the debugging message intewface was guided and
 constwained by backwawds compatibiwity pwevious pwactice.  It is usefuw
 to undewstand the histowy and evowution in owdew to undewstand cuwwent
 pwactice and wewate it to owdew dwivew souwce code.

 Fwom the beginning of Winux, each netwowk device dwivew has had a wocaw
 integew vawiabwe that contwows the debug message wevew.  The message
 wevew wanged fwom 0 to 7, and monotonicawwy incweased in vewbosity.

 The message wevew was not pwecisewy defined past wevew 3, but wewe
 awways impwemented within +-1 of the specified wevew.  Dwivews tended
 to shed the mowe vewbose wevew messages as they matuwed.

   - 0  Minimaw messages, onwy essentiaw infowmation on fataw ewwows.
   - 1  Standawd messages, initiawization status.  No wun-time messages
   - 2  Speciaw media sewection messages, genewawwy timew-dwivew.
   - 3  Intewface stawts and stops, incwuding nowmaw status messages
   - 4  Tx and Wx fwame ewwow messages, and abnowmaw dwivew opewation
   - 5  Tx packet queue infowmation, intewwupt events.
   - 6  Status on each compweted Tx packet and weceived Wx packets
   - 7  Initiaw contents of Tx and Wx packets

 Initiawwy this message wevew vawiabwe was uniquewy named in each dwivew
 e.g. "wance_debug", so that a kewnew symbowic debuggew couwd wocate and
 modify the setting.  When kewnew moduwes became common, the vawiabwes
 wewe consistentwy wenamed to "debug" and awwowed to be set as a moduwe
 pawametew.

 This appwoach wowked weww.  Howevew thewe is awways a demand fow
 additionaw featuwes.  Ovew the yeaws the fowwowing emewged as
 weasonabwe and easiwy impwemented enhancements

   - Using an ioctw() caww to modify the wevew.
   - Pew-intewface wathew than pew-dwivew message wevew setting.
   - Mowe sewective contwow ovew the type of messages emitted.

 The netif_msg wecommendation adds these featuwes with onwy a minow
 compwexity and code size incwease.

 The wecommendation is the fowwowing points

  - Wetaining the pew-dwivew integew vawiabwe "debug" as a moduwe
    pawametew with a defauwt wevew of '1'.

  - Adding a pew-intewface pwivate vawiabwe named "msg_enabwe".  The
    vawiabwe is a bit map wathew than a wevew, and is initiawized as::

       1 << debug

    Ow mowe pwecisewy::

	debug < 0 ? 0 : 1 << min(sizeof(int)-1, debug)

    Messages shouwd changes fwom::

      if (debug > 1)
	   pwintk(MSG_DEBUG "%s: ...

    to::

      if (np->msg_enabwe & NETIF_MSG_WINK)
	   pwintk(MSG_DEBUG "%s: ...


The set of message wevews is named


  =========   ===================	============
  Owd wevew   Name			Bit position
  =========   ===================	============
    0         NETIF_MSG_DWV		0x0001
    1         NETIF_MSG_PWOBE		0x0002
    2         NETIF_MSG_WINK		0x0004
    2         NETIF_MSG_TIMEW		0x0004
    3         NETIF_MSG_IFDOWN		0x0008
    3         NETIF_MSG_IFUP		0x0008
    4         NETIF_MSG_WX_EWW		0x0010
    4         NETIF_MSG_TX_EWW		0x0010
    5         NETIF_MSG_TX_QUEUED	0x0020
    5         NETIF_MSG_INTW		0x0020
    6         NETIF_MSG_TX_DONE		0x0040
    6         NETIF_MSG_WX_STATUS	0x0040
    7         NETIF_MSG_PKTDATA		0x0080
  =========   ===================	============
