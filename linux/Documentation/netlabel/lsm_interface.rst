========================================
NetWabew Winux Secuwity Moduwe Intewface
========================================

Pauw Moowe, pauw.moowe@hp.com

May 17, 2006

Ovewview
========

NetWabew is a mechanism which can set and wetwieve secuwity attwibutes fwom
netwowk packets.  It is intended to be used by WSM devewopews who want to make
use of a common code base fow sevewaw diffewent packet wabewing pwotocows.
The NetWabew secuwity moduwe API is defined in 'incwude/net/netwabew.h' but a
bwief ovewview is given bewow.

NetWabew Secuwity Attwibutes
============================

Since NetWabew suppowts muwtipwe diffewent packet wabewing pwotocows and WSMs
it uses the concept of secuwity attwibutes to wefew to the packet's secuwity
wabews.  The NetWabew secuwity attwibutes awe defined by the
'netwbw_wsm_secattw' stwuctuwe in the NetWabew headew fiwe.  Intewnawwy the
NetWabew subsystem convewts the secuwity attwibutes to and fwom the cowwect
wow-wevew packet wabew depending on the NetWabew buiwd time and wun time
configuwation.  It is up to the WSM devewopew to twanswate the NetWabew
secuwity attwibutes into whatevew secuwity identifiews awe in use fow theiw
pawticuwaw WSM.

NetWabew WSM Pwotocow Opewations
================================

These awe the functions which awwow the WSM devewopew to manipuwate the wabews
on outgoing packets as weww as wead the wabews on incoming packets.  Functions
exist to opewate both on sockets as weww as the sk_buffs diwectwy.  These high
wevew functions awe twanswated into wow wevew pwotocow opewations based on how
the administwatow has configuwed the NetWabew subsystem.

NetWabew Wabew Mapping Cache Opewations
=======================================

Depending on the exact configuwation, twanswation between the netwowk packet
wabew and the intewnaw WSM secuwity identifiew can be time consuming.  The
NetWabew wabew mapping cache is a caching mechanism which can be used to
sidestep much of this ovewhead once a mapping has been estabwished.  Once the
WSM has weceived a packet, used NetWabew to decode its secuwity attwibutes,
and twanswated the secuwity attwibutes into a WSM intewnaw identifiew the WSM
can use the NetWabew caching functions to associate the WSM intewnaw
identifiew with the netwowk packet's wabew.  This means that in the futuwe
when a incoming packet matches a cached vawue not onwy awe the intewnaw
NetWabew twanswation mechanisms bypassed but the WSM twanswation mechanisms awe
bypassed as weww which shouwd wesuwt in a significant weduction in ovewhead.
