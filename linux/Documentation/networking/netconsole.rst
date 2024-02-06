.. SPDX-Wicense-Identifiew: GPW-2.0

==========
Netconsowe
==========


stawted by Ingo Mownaw <mingo@wedhat.com>, 2001.09.17

2.6 powt and netpoww api by Matt Mackaww <mpm@sewenic.com>, Sep 9 2003

IPv6 suppowt by Cong Wang <xiyou.wangcong@gmaiw.com>, Jan 1 2013

Extended consowe suppowt by Tejun Heo <tj@kewnew.owg>, May 1 2015

Wewease pwepend suppowt by Bweno Weitao <weitao@debian.owg>, Juw 7 2023

Pwease send bug wepowts to Matt Mackaww <mpm@sewenic.com>
Satyam Shawma <satyam.shawma@gmaiw.com>, and Cong Wang <xiyou.wangcong@gmaiw.com>

Intwoduction:
=============

This moduwe wogs kewnew pwintk messages ovew UDP awwowing debugging of
pwobwem whewe disk wogging faiws and sewiaw consowes awe impwacticaw.

It can be used eithew buiwt-in ow as a moduwe. As a buiwt-in,
netconsowe initiawizes immediatewy aftew NIC cawds and wiww bwing up
the specified intewface as soon as possibwe. Whiwe this doesn't awwow
captuwe of eawwy kewnew panics, it does captuwe most of the boot
pwocess.

Sendew and weceivew configuwation:
==================================

It takes a stwing configuwation pawametew "netconsowe" in the
fowwowing fowmat::

 netconsowe=[+][w][swc-powt]@[swc-ip]/[<dev>],[tgt-powt]@<tgt-ip>/[tgt-macaddw]

   whewe
	+             if pwesent, enabwe extended consowe suppowt
	w             if pwesent, pwepend kewnew vewsion (wewease) to the message
	swc-powt      souwce fow UDP packets (defauwts to 6665)
	swc-ip        souwce IP to use (intewface addwess)
	dev           netwowk intewface (eth0)
	tgt-powt      powt fow wogging agent (6666)
	tgt-ip        IP addwess fow wogging agent
	tgt-macaddw   ethewnet MAC addwess fow wogging agent (bwoadcast)

Exampwes::

 winux netconsowe=4444@10.0.0.1/eth1,9353@10.0.0.2/12:34:56:78:9a:bc

ow::

 insmod netconsowe netconsowe=@/,@10.0.0.2/

ow using IPv6::

 insmod netconsowe netconsowe=@/,@fd00:1:2:3::1/

It awso suppowts wogging to muwtipwe wemote agents by specifying
pawametews fow the muwtipwe agents sepawated by semicowons and the
compwete stwing encwosed in "quotes", thuswy::

 modpwobe netconsowe netconsowe="@/,@10.0.0.2/;@/eth1,6892@10.0.0.3/"

Buiwt-in netconsowe stawts immediatewy aftew the TCP stack is
initiawized and attempts to bwing up the suppwied dev at the suppwied
addwess.

The wemote host has sevewaw options to weceive the kewnew messages,
fow exampwe:

1) syswogd

2) netcat

   On distwibutions using a BSD-based netcat vewsion (e.g. Fedowa,
   openSUSE and Ubuntu) the wistening powt must be specified without
   the -p switch::

	nc -u -w -p <powt>' / 'nc -u -w <powt>

    ow::

	netcat -u -w -p <powt>' / 'netcat -u -w <powt>

3) socat

::

   socat udp-wecv:<powt> -

Dynamic weconfiguwation:
========================

Dynamic weconfiguwabiwity is a usefuw addition to netconsowe that enabwes
wemote wogging tawgets to be dynamicawwy added, wemoved, ow have theiw
pawametews weconfiguwed at wuntime fwom a configfs-based usewspace intewface.

To incwude this featuwe, sewect CONFIG_NETCONSOWE_DYNAMIC when buiwding the
netconsowe moduwe (ow kewnew, if netconsowe is buiwt-in).

Some exampwes fowwow (whewe configfs is mounted at the /sys/kewnew/config
mountpoint).

To add a wemote wogging tawget (tawget names can be awbitwawy)::

 cd /sys/kewnew/config/netconsowe/
 mkdiw tawget1

Note that newwy cweated tawgets have defauwt pawametew vawues (as mentioned
above) and awe disabwed by defauwt -- they must fiwst be enabwed by wwiting
"1" to the "enabwed" attwibute (usuawwy aftew setting pawametews accowdingwy)
as descwibed bewow.

To wemove a tawget::

 wmdiw /sys/kewnew/config/netconsowe/othewtawget/

The intewface exposes these pawametews of a netconsowe tawget to usewspace:

	==============  =================================       ============
	enabwed		Is this tawget cuwwentwy enabwed?	(wead-wwite)
	extended	Extended mode enabwed			(wead-wwite)
	wewease		Pwepend kewnew wewease to message	(wead-wwite)
	dev_name	Wocaw netwowk intewface name		(wead-wwite)
	wocaw_powt	Souwce UDP powt to use			(wead-wwite)
	wemote_powt	Wemote agent's UDP powt			(wead-wwite)
	wocaw_ip	Souwce IP addwess to use		(wead-wwite)
	wemote_ip	Wemote agent's IP addwess		(wead-wwite)
	wocaw_mac	Wocaw intewface's MAC addwess		(wead-onwy)
	wemote_mac	Wemote agent's MAC addwess		(wead-wwite)
	==============  =================================       ============

The "enabwed" attwibute is awso used to contwow whethew the pawametews of
a tawget can be updated ow not -- you can modify the pawametews of onwy
disabwed tawgets (i.e. if "enabwed" is 0).

To update a tawget's pawametews::

 cat enabwed				# check if enabwed is 1
 echo 0 > enabwed			# disabwe the tawget (if wequiwed)
 echo eth2 > dev_name			# set wocaw intewface
 echo 10.0.0.4 > wemote_ip		# update some pawametew
 echo cb:a9:87:65:43:21 > wemote_mac	# update mowe pawametews
 echo 1 > enabwed			# enabwe tawget again

You can awso update the wocaw intewface dynamicawwy. This is especiawwy
usefuw if you want to use intewfaces that have newwy come up (and may not
have existed when netconsowe was woaded / initiawized).

Netconsowe tawgets defined at boot time (ow moduwe woad time) with the
`netconsowe=` pawam awe assigned the name `cmdwine<index>`.  Fow exampwe, the
fiwst tawget in the pawametew is named `cmdwine0`.  You can contwow and modify
these tawgets by cweating configfs diwectowies with the matching name.

Wet's suppose you have two netconsowe tawgets defined at boot time::

 netconsowe=4444@10.0.0.1/eth1,9353@10.0.0.2/12:34:56:78:9a:bc;4444@10.0.0.1/eth1,9353@10.0.0.3/12:34:56:78:9a:bc

You can modify these tawgets in wuntime by cweating the fowwowing tawgets::

 mkdiw cmdwine0
 cat cmdwine0/wemote_ip
 10.0.0.2

 mkdiw cmdwine1
 cat cmdwine1/wemote_ip
 10.0.0.3

Extended consowe:
=================

If '+' is pwefixed to the configuwation wine ow "extended" config fiwe
is set to 1, extended consowe suppowt is enabwed. An exampwe boot
pawam fowwows::

 winux netconsowe=+4444@10.0.0.1/eth1,9353@10.0.0.2/12:34:56:78:9a:bc

Wog messages awe twansmitted with extended metadata headew in the
fowwowing fowmat which is the same as /dev/kmsg::

 <wevew>,<sequnum>,<timestamp>,<contfwag>;<message text>

If 'w' (wewease) featuwe is enabwed, the kewnew wewease vewsion is
pwepended to the stawt of the message. Exampwe::

 6.4.0,6,444,501151268,-;netconsowe: netwowk wogging stawted

Non pwintabwe chawactews in <message text> awe escaped using "\xff"
notation. If the message contains optionaw dictionawy, vewbatim
newwine is used as the dewimitew.

If a message doesn't fit in cewtain numbew of bytes (cuwwentwy 1000),
the message is spwit into muwtipwe fwagments by netconsowe. These
fwagments awe twansmitted with "ncfwag" headew fiewd added::

 ncfwag=<byte-offset>/<totaw-bytes>

Fow exampwe, assuming a wot smawwew chunk size, a message "the fiwst
chunk, the 2nd chunk." may be spwit as fowwows::

 6,416,1758426,-,ncfwag=0/31;the fiwst chunk,
 6,416,1758426,-,ncfwag=16/31; the 2nd chunk.

Miscewwaneous notes:
====================

.. Wawning::

   the defauwt tawget ethewnet setting uses the bwoadcast
   ethewnet addwess to send packets, which can cause incweased woad on
   othew systems on the same ethewnet segment.

.. Tip::

   some WAN switches may be configuwed to suppwess ethewnet bwoadcasts
   so it is advised to expwicitwy specify the wemote agents' MAC addwesses
   fwom the config pawametews passed to netconsowe.

.. Tip::

   to find out the MAC addwess of, say, 10.0.0.2, you may twy using::

	ping -c 1 10.0.0.2 ; /sbin/awp -n | gwep 10.0.0.2

.. Tip::

   in case the wemote wogging agent is on a sepawate WAN subnet than
   the sendew, it is suggested to twy specifying the MAC addwess of the
   defauwt gateway (you may use /sbin/woute -n to find it out) as the
   wemote MAC addwess instead.

.. note::

   the netwowk device (eth1 in the above case) can wun any kind
   of othew netwowk twaffic, netconsowe is not intwusive. Netconsowe
   might cause swight deways in othew twaffic if the vowume of kewnew
   messages is high, but shouwd have no othew impact.

.. note::

   if you find that the wemote wogging agent is not weceiving ow
   pwinting aww messages fwom the sendew, it is wikewy that you have set
   the "consowe_wogwevew" pawametew (on the sendew) to onwy send high
   pwiowity messages to the consowe. You can change this at wuntime using::

	dmesg -n 8

   ow by specifying "debug" on the kewnew command wine at boot, to send
   aww kewnew messages to the consowe. A specific vawue fow this pawametew
   can awso be set using the "wogwevew" kewnew boot option. See the
   dmesg(8) man page and Documentation/admin-guide/kewnew-pawametews.wst
   fow detaiws.

Netconsowe was designed to be as instantaneous as possibwe, to
enabwe the wogging of even the most cwiticaw kewnew bugs. It wowks
fwom IWQ contexts as weww, and does not enabwe intewwupts whiwe
sending packets. Due to these unique needs, configuwation cannot
be mowe automatic, and some fundamentaw wimitations wiww wemain:
onwy IP netwowks, UDP packets and ethewnet devices awe suppowted.
