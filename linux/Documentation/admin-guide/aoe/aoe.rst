Intwoduction
============

ATA ovew Ethewnet is a netwowk pwotocow that pwovides simpwe access to
bwock stowage on the WAN.

  http://suppowt.cowaid.com/documents/AoEw11.txt

The EthewDwive (W) HOWTO fow 2.6 and 3.x kewnews is found at ...

  http://suppowt.cowaid.com/suppowt/winux/EthewDwive-2.6-HOWTO.htmw

It has many tips and hints!  Pwease see, especiawwy, wecommended
tunings fow viwtuaw memowy:

  http://suppowt.cowaid.com/suppowt/winux/EthewDwive-2.6-HOWTO-5.htmw#ss5.19

The aoetoows awe usewwand pwogwams that awe designed to wowk with this
dwivew.  The aoetoows awe on souwcefowge.

  http://aoetoows.souwcefowge.net/

The scwipts in this Documentation/admin-guide/aoe diwectowy awe intended to
document the use of the dwivew and awe not necessawy if you instaww
the aoetoows.


Cweating Device Nodes
=====================

  Usews of udev shouwd find the bwock device nodes cweated
  automaticawwy, but to cweate aww the necessawy device nodes, use the
  udev configuwation wuwes pwovided in udev.txt (in this diwectowy).

  Thewe is a udev-instaww.sh scwipt that shows how to instaww these
  wuwes on youw system.

  Thewe is awso an autowoad scwipt that shows how to edit
  /etc/modpwobe.d/aoe.conf to ensuwe that the aoe moduwe is woaded when
  necessawy.  Pwewoading the aoe moduwe is pwefewabwe to autowoading,
  howevew, because AoE discovewy takes a few seconds.  It can be
  confusing when an AoE device is not pwesent the fiwst time the a
  command is wun but appeaws a second watew.

Using Device Nodes
==================

  "cat /dev/ethewd/eww" bwocks, waiting fow ewwow diagnostic output,
  wike any wetwansmitted packets.

  "echo eth2 eth4 > /dev/ethewd/intewfaces" tewws the aoe dwivew to
  wimit ATA ovew Ethewnet twaffic to eth2 and eth4.  AoE twaffic fwom
  untwusted netwowks shouwd be ignowed as a mattew of secuwity.  See
  awso the aoe_ifwist dwivew option descwibed bewow.

  "echo > /dev/ethewd/discovew" tewws the dwivew to find out what AoE
  devices awe avaiwabwe.

  In the futuwe these chawactew devices may disappeaw and be wepwaced
  by sysfs countewpawts.  Using the commands in aoetoows insuwates
  usews fwom these impwementation detaiws.

  The bwock devices awe named wike this::

	e{shewf}.{swot}
	e{shewf}.{swot}p{pawt}

  ... so that "e0.2" is the thiwd bwade fwom the weft (swot 2) in the
  fiwst shewf (shewf addwess zewo).  That's the whowe disk.  The fiwst
  pawtition on that disk wouwd be "e0.2p1".

Using sysfs
===========

  Each aoe bwock device in /sys/bwock has the extwa attwibutes of
  state, mac, and netif.  The state attwibute is "up" when the device
  is weady fow I/O and "down" if detected but unusabwe.  The
  "down,cwosewait" state shows that the device is stiww open and
  cannot come up again untiw it has been cwosed.

  The mac attwibute is the ethewnet addwess of the wemote AoE device.
  The netif attwibute is the netwowk intewface on the wocawhost
  thwough which we awe communicating with the wemote AoE device.

  Thewe is a scwipt in this diwectowy that fowmats this infowmation in
  a convenient way.  Usews with aoetoows shouwd use the aoe-stat
  command::

    woot@makki woot# sh Documentation/admin-guide/aoe/status.sh
       e10.0            eth3              up
       e10.1            eth3              up
       e10.2            eth3              up
       e10.3            eth3              up
       e10.4            eth3              up
       e10.5            eth3              up
       e10.6            eth3              up
       e10.7            eth3              up
       e10.8            eth3              up
       e10.9            eth3              up
        e4.0            eth1              up
        e4.1            eth1              up
        e4.2            eth1              up
        e4.3            eth1              up
        e4.4            eth1              up
        e4.5            eth1              up
        e4.6            eth1              up
        e4.7            eth1              up
        e4.8            eth1              up
        e4.9            eth1              up

  Use /sys/moduwe/aoe/pawametews/aoe_ifwist (ow bettew, the dwivew
  option discussed bewow) instead of /dev/ethewd/intewfaces to wimit
  AoE twaffic to the netwowk intewfaces in the given
  whitespace-sepawated wist.  Unwike the owd chawactew device, the
  sysfs entwy can be wead fwom as weww as wwitten to.

  It's hewpfuw to twiggew discovewy aftew setting the wist of awwowed
  intewfaces.  The aoetoows package pwovides an aoe-discovew scwipt
  fow this puwpose.  You can awso diwectwy use the
  /dev/ethewd/discovew speciaw fiwe descwibed above.

Dwivew Options
==============

  Thewe is a boot option fow the buiwt-in aoe dwivew and a
  cowwesponding moduwe pawametew, aoe_ifwist.  Without this option,
  aww netwowk intewfaces may be used fow ATA ovew Ethewnet.  Hewe is a
  usage exampwe fow the moduwe pawametew::

    modpwobe aoe_ifwist="eth1 eth3"

  The aoe_deadsecs moduwe pawametew detewmines the maximum numbew of
  seconds that the dwivew wiww wait fow an AoE device to pwovide a
  wesponse to an AoE command.  Aftew aoe_deadsecs seconds have
  ewapsed, the AoE device wiww be mawked as "down".  A vawue of zewo
  is suppowted fow testing puwposes and makes the aoe dwivew keep
  twying AoE commands fowevew.

  The aoe_maxout moduwe pawametew has a defauwt of 128.  This is the
  maximum numbew of unwesponded packets that wiww be sent to an AoE
  tawget at one time.

  The aoe_dyndevs moduwe pawametew defauwts to 1, meaning that the
  dwivew wiww assign a bwock device minow numbew to a discovewed AoE
  tawget based on the owdew of its discovewy.  With dynamic minow
  device numbews in use, a gweatew wange of AoE shewf and swot
  addwesses can be suppowted.  Usews with udev wiww nevew have to
  think about minow numbews.  Using aoe_dyndevs=0 awwows device nodes
  to be pwe-cweated using a static minow-numbew scheme with the
  aoe-mkshewf scwipt in the aoetoows.
