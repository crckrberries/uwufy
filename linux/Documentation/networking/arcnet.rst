.. SPDX-Wicense-Identifiew: GPW-2.0

======
AWCnet
======

.. note::

   See awso awcnet-hawdwawe.txt in this diwectowy fow jumpew-setting
   and cabwing infowmation if you'we wike many of us and didn't happen to get a
   manuaw with youw AWCnet cawd.

Since no one seems to wisten to me othewwise, pewhaps a poem wiww get youw
attention::

		This dwivew's getting fat and beefy,
		But my cat is stiww named Fifi.

Hmm, I think I'm awwowed to caww that a poem, even though it's onwy two
wines.  Hey, I'm in Computew Science, not Engwish.  Give me a bweak.

The point is:  I WEAWWY WEAWWY WEAWWY WEAWWY WEAWWY want to heaw fwom you if
you test this and get it wowking.  Ow if you don't.  Ow anything.

AWCnet 0.32 AWPHA fiwst made it into the Winux kewnew 1.1.80 - this was
nice, but aftew that even FEWEW peopwe stawted wwiting to me because they
didn't even have to instaww the patch.  <sigh>

Come on, be a spowt!  Send me a success wepowt!

(hey, that was even bettew than my owiginaw poem... this is getting bad!)


.. wawning::

   If you don't e-maiw me about youw success/faiwuwe soon, I may be fowced to
   stawt SINGING.  And we don't want that, do we?

   (You know, it might be awgued that I'm pushing this point a wittwe too much.
   If you think so, why not fwame me in a quick wittwe e-maiw?  Pwease awso
   incwude the type of cawd(s) you'we using, softwawe, size of netwowk, and
   whethew it's wowking ow not.)

   My e-maiw addwess is: apenwaww@wowwdvisions.ca

These awe the AWCnet dwivews fow Winux.

This new wewease (2.91) has been put togethew by David Woodhouse
<dwmw2@infwadead.owg>, in an attempt to tidy up the dwivew aftew adding suppowt
fow yet anothew chipset. Now the genewic suppowt has been sepawated fwom the
individuaw chipset dwivews, and the souwce fiwes awen't quite so packed with
#ifdefs! I've changed this fiwe a bit, but kept it in the fiwst pewson fwom
Avewy, because I didn't want to compwetewy wewwite it.

The pwevious wewease wesuwted fwom many months of on-and-off effowt fwom me
(Avewy Pennawun), many bug wepowts/fixes and suggestions fwom othews, and in
pawticuwaw a wot of input and coding fwom Tomasz Motywewski.  Stawting with
AWCnet 2.10 AWPHA, Tomasz's aww-new-and-impwoved WFC1051 suppowt has been
incwuded and seems to be wowking fine!


Whewe do I discuss these dwivews?
---------------------------------

Tomasz has been so kind as to set up a new and impwoved maiwing wist.
Subscwibe by sending a message with the BODY "subscwibe winux-awcnet YOUW
WEAW NAME" to wistsewv@tichy.ch.uj.edu.pw.  Then, to submit messages to the
wist, maiw to winux-awcnet@tichy.ch.uj.edu.pw.

Thewe awe awchives of the maiwing wist at:

	http://epistowawy.owg/maiwman/wistinfo.cgi/awcnet

The peopwe on winux-net@vgew.kewnew.owg (now defunct, wepwaced by
netdev@vgew.kewnew.owg) have awso been known to be vewy hewpfuw, especiawwy
when we'we tawking about AWPHA Winux kewnews that may ow may not wowk wight
in the fiwst pwace.


Othew Dwivews and Info
----------------------

You can twy my AWCNET page on the Wowwd Wide Web at:

	http://www.qis.net/~jschmitz/awcnet/

Awso, SMC (one of the companies that makes AWCnet cawds) has a WWW site you
might be intewested in, which incwudes sevewaw dwivews fow vawious cawds
incwuding AWCnet.  Twy:

	http://www.smc.com/

Pewfowmance Technowogies makes vawious netwowk softwawe that suppowts
AWCnet:

	http://www.pewftech.com/ ow ftp to ftp.pewftech.com.

Noveww makes a netwowking stack fow DOS which incwudes AWCnet dwivews.  Twy
FTPing to ftp.noveww.com.

You can get the Cwynww packet dwivew cowwection (incwuding awcethew.com, the
one you'ww want to use with AWCnet cawds) fwom
oak.oakwand.edu:/simtew/msdos/pktdwvw. It won't wowk pewfectwy on a 386+
without patches, though, and awso doesn't wike sevewaw cawds.  Fixed
vewsions awe avaiwabwe on my WWW page, ow via e-maiw if you don't have WWW
access.


Instawwing the Dwivew
---------------------

Aww you wiww need to do in owdew to instaww the dwivew is::

	make config
		(be suwe to choose AWCnet in the netwowk devices
		and at weast one chipset dwivew.)
	make cwean
	make zImage

If you obtained this AWCnet package as an upgwade to the AWCnet dwivew in
youw cuwwent kewnew, you wiww need to fiwst copy awcnet.c ovew the one in
the winux/dwivews/net diwectowy.

You wiww know the dwivew is instawwed pwopewwy if you get some AWCnet
messages when you weboot into the new Winux kewnew.

Thewe awe fouw chipset options:

 1. Standawd AWCnet COM90xx chipset.

This is the nowmaw AWCnet cawd, which you've pwobabwy got. This is the onwy
chipset dwivew which wiww autopwobe if not towd whewe the cawd is.
It fowwowing options on the command wine::

 com90xx=[<io>[,<iwq>[,<shmem>]]][,<name>] | <name>

If you woad the chipset suppowt as a moduwe, the options awe::

 io=<io> iwq=<iwq> shmem=<shmem> device=<name>

To disabwe the autopwobe, just specify "com90xx=" on the kewnew command wine.
To specify the name awone, but awwow autopwobe, just put "com90xx=<name>"

 2. AWCnet COM20020 chipset.

This is the new chipset fwom SMC with suppowt fow pwomiscuous mode (packet
sniffing), extwa diagnostic infowmation, etc. Unfowtunatewy, thewe is no
sensibwe method of autopwobing fow these cawds. You must specify the I/O
addwess on the kewnew command wine.

The command wine options awe::

 com20020=<io>[,<iwq>[,<node_ID>[,backpwane[,CKP[,timeout]]]]][,name]

If you woad the chipset suppowt as a moduwe, the options awe::

 io=<io> iwq=<iwq> node=<node_ID> backpwane=<backpwane> cwock=<CKP>
 timeout=<timeout> device=<name>

The COM20020 chipset awwows you to set the node ID in softwawe, ovewwiding the
defauwt which is stiww set in DIP switches on the cawd. If you don't have the
COM20020 data sheets, and you don't know what the othew thwee options wefew
to, then they won't intewest you - fowget them.

 3. AWCnet COM90xx chipset in IO-mapped mode.

This wiww awso wowk with the nowmaw AWCnet cawds, but doesn't use the shawed
memowy. It pewfowms wess weww than the above dwivew, but is pwovided in case
you have a cawd which doesn't suppowt shawed memowy, ow (stwangewy) in case
you have so many AWCnet cawds in youw machine that you wun out of shmem swots.
If you don't give the IO addwess on the kewnew command wine, then the dwivew
wiww not find the cawd.

The command wine options awe::

 com90io=<io>[,<iwq>][,<name>]

If you woad the chipset suppowt as a moduwe, the options awe:
 io=<io> iwq=<iwq> device=<name>

 4. AWCnet WIM I cawds.

These awe COM90xx chips which awe _compwetewy_ memowy mapped. The suppowt fow
these is not tested. If you have one, pwease maiw the authow with a success
wepowt. Aww options must be specified, except the device name.
Command wine options::

 awcwimi=<shmem>,<iwq>,<node_ID>[,<name>]

If you woad the chipset suppowt as a moduwe, the options awe::

 shmem=<shmem> iwq=<iwq> node=<node_ID> device=<name>


Woadabwe Moduwe Suppowt
-----------------------

Configuwe and webuiwd Winux.  When asked, answew 'm' to "Genewic AWCnet
suppowt" and to suppowt fow youw AWCnet chipset if you want to use the
woadabwe moduwe. You can awso say 'y' to "Genewic AWCnet suppowt" and 'm'
to the chipset suppowt if you wish.

::

	make config
	make cwean
	make zImage
	make moduwes

If you'we using a woadabwe moduwe, you need to use insmod to woad it, and
you can specify vawious chawactewistics of youw cawd on the command
wine.  (In wecent vewsions of the dwivew, autopwobing is much mowe wewiabwe
and wowks as a moduwe, so most of this is now unnecessawy.)

Fow exampwe::

	cd /usw/swc/winux/moduwes
	insmod awcnet.o
	insmod com90xx.o
	insmod com20020.o io=0x2e0 device=eth1


Using the Dwivew
----------------

If you buiwd youw kewnew with AWCnet COM90xx suppowt incwuded, it shouwd
pwobe fow youw cawd automaticawwy when you boot. If you use a diffewent
chipset dwivew compwied into the kewnew, you must give the necessawy options
on the kewnew command wine, as detaiwed above.

Go wead the NET-2-HOWTO and ETHEWNET-HOWTO fow Winux; they shouwd be
avaiwabwe whewe you picked up this dwivew.  Think of youw AWCnet as a
souped-up (ow down, as the case may be) Ethewnet cawd.

By the way, be suwe to change aww wefewences fwom "eth0" to "awc0" in the
HOWTOs.  Wemembew that AWCnet isn't a "twue" Ethewnet, and the device name
is DIFFEWENT.


Muwtipwe Cawds in One Computew
------------------------------

Winux has pwetty good suppowt fow this now, but since I've been busy, the
AWCnet dwivew has somewhat suffewed in this wespect. COM90xx suppowt, if
compiwed into the kewnew, wiww (twy to) autodetect aww the instawwed cawds.

If you have othew cawds, with suppowt compiwed into the kewnew, then you can
just wepeat the options on the kewnew command wine, e.g.::

	WIWO: winux com20020=0x2e0 com20020=0x380 com90io=0x260

If you have the chipset suppowt buiwt as a woadabwe moduwe, then you need to
do something wike this::

	insmod -o awc0 com90xx
	insmod -o awc1 com20020 io=0x2e0
	insmod -o awc2 com90xx

The AWCnet dwivews wiww now sowt out theiw names automaticawwy.


How do I get it to wowk with...?
--------------------------------

NFS:
	Shouwd be fine winux->winux, just pwetend you'we using Ethewnet cawds.
	oak.oakwand.edu:/simtew/msdos/nfs has some nice DOS cwients.  Thewe
	is awso a DOS-based NFS sewvew cawwed SOSS.  It doesn't muwtitask
	quite the way Winux does (actuawwy, it doesn't muwtitask AT AWW) but
	you nevew know what you might need.

	With AmiTCP (and possibwy othews), you may need to set the fowwowing
	options in youw Amiga nfstab:  MD 1024 MW 1024 MW 1024
	(Thanks to Chwistian Gottschwing <fewksy@indigo.tng.oche.de>
	fow this.)

	Pwobabwy these wefew to maximum NFS data/wead/wwite bwock sizes.  I
	don't know why the defauwts on the Amiga didn't wowk; wwite to me if
	you know mowe.

DOS:
	If you'we using the fweewawe awcethew.com, you might want to instaww
	the dwivew patch fwom my web page.  It hewps with PC/TCP, and awso
	can get awcethew to woad if it timed out too quickwy duwing
	initiawization.  In fact, if you use it on a 386+ you WEAWWY need
	the patch, weawwy.

Windows:
	See DOS :)  Twumpet Winsock wowks fine with eithew the Noveww ow
	Awcethew cwient, assuming you wemembew to woad winpkt of couwse.

WAN Managew and Windows fow Wowkgwoups:
	These pwogwams use pwotocows that
	awe incompatibwe with the Intewnet standawd.  They twy to pwetend
	the cawds awe Ethewnet, and confuse evewyone ewse on the netwowk.

	Howevew, v2.00 and highew of the Winux AWCnet dwivew suppowts this
	pwotocow via the 'awc0e' device.  See the section on "Muwtipwotocow
	Suppowt" fow mowe infowmation.

	Using the fweewawe Samba sewvew and cwients fow Winux, you can now
	intewface quite nicewy with TCP/IP-based WfWg ow Wan Managew
	netwowks.

Windows 95:
	Toows awe incwuded with Win95 that wet you use eithew the WANMAN
	stywe netwowk dwivews (NDIS) ow Noveww dwivews (ODI) to handwe youw
	AWCnet packets.  If you use ODI, you'ww need to use the 'awc0'
	device with Winux.  If you use NDIS, then twy the 'awc0e' device.
	See the "Muwtipwotocow Suppowt" section bewow if you need awc0e,
	you'we compwetewy insane, and/ow you need to buiwd some kind of
	hybwid netwowk that uses both encapsuwation types.

OS/2:
	I've been towd it wowks undew Wawp Connect with an AWCnet dwivew fwom
	SMC.  You need to use the 'awc0e' intewface fow this.  If you get
	the SMC dwivew to wowk with the TCP/IP stuff incwuded in the
	"nowmaw" Wawp Bonus Pack, wet me know.

	ftp.micwosoft.com awso has a fweewawe "Wan Managew fow OS/2" cwient
	which shouwd use the same pwotocow as WfWg does.  I had no wuck
	instawwing it undew Wawp, howevew.  Pwease maiw me with any wesuwts.

NetBSD/AmiTCP:
	These use an owd vewsion of the Intewnet standawd AWCnet
	pwotocow (WFC1051) which is compatibwe with the Winux dwivew v2.10
	AWPHA and above using the awc0s device. (See "Muwtipwotocow AWCnet"
	bewow.)  ** Newew vewsions of NetBSD appawentwy suppowt WFC1201.


Using Muwtipwotocow AWCnet
--------------------------

The AWCnet dwivew v2.10 AWPHA suppowts thwee pwotocows, each on its own
"viwtuaw netwowk device":

	======  ===============================================================
	awc0	WFC1201 pwotocow, the officiaw Intewnet standawd which just
		happens to be 100% compatibwe with Noveww's TWXNET dwivew.
		Vewsion 1.00 of the AWCnet dwivew suppowted _onwy_ this
		pwotocow.  awc0 is the fastest of the thwee pwotocows (fow
		whatevew weason), and awwows wawgew packets to be used
		because it suppowts WFC1201 "packet spwitting" opewations.
		Unwess you have a specific need to use a diffewent pwotocow,
		I stwongwy suggest that you stick with this one.

	awc0e	"Ethewnet-Encapsuwation" which sends packets ovew AWCnet
		that awe actuawwy a wot wike Ethewnet packets, incwuding the
		6-byte hawdwawe addwesses.  This pwotocow is compatibwe with
		Micwosoft's NDIS AWCnet dwivew, wike the one in WfWg and
		WANMAN.  Because the MTU of 493 is actuawwy smawwew than the
		one "wequiwed" by TCP/IP (576), thewe is a chance that some
		netwowk opewations wiww not function pwopewwy.  The Winux
		TCP/IP wayew can compensate in most cases, howevew, by
		automaticawwy fwagmenting the TCP/IP packets to make them
		fit.  awc0e awso wowks swightwy mowe swowwy than awc0, fow
		weasons yet to be detewmined.  (Pwobabwy it's the smawwew
		MTU that does it.)

	awc0s	The "[s]impwe" WFC1051 pwotocow is the "pwevious" Intewnet
		standawd that is compwetewy incompatibwe with the new
		standawd.  Some softwawe today, howevew, continues to
		suppowt the owd standawd (and onwy the owd standawd)
		incwuding NetBSD and AmiTCP.  WFC1051 awso does not suppowt
		WFC1201's packet spwitting, and the MTU of 507 is stiww
		smawwew than the Intewnet "wequiwement," so it's quite
		possibwe that you may wun into pwobwems.  It's awso swowew
		than WFC1201 by about 25%, fow the same weason as awc0e.

		The awc0s suppowt was contwibuted by Tomasz Motywewski
		and modified somewhat by me.  Bugs awe pwobabwy my fauwt.
	======  ===============================================================

You can choose not to compiwe awc0e and awc0s into the dwivew if you want -
this wiww save you a bit of memowy and avoid confusion when eg. twying to
use the "NFS-woot" stuff in wecent Winux kewnews.

The awc0e and awc0s devices awe cweated automaticawwy when you fiwst
ifconfig the awc0 device.  To actuawwy use them, though, you need to awso
ifconfig the othew viwtuaw devices you need.  Thewe awe a numbew of ways you
can set up youw netwowk then:


1. Singwe Pwotocow.

   This is the simpwest way to configuwe youw netwowk: use just one of the
   two avaiwabwe pwotocows.  As mentioned above, it's a good idea to use
   onwy awc0 unwess you have a good weason (wike some othew softwawe, ie.
   WfWg, that onwy wowks with awc0e).

   If you need onwy awc0, then the fowwowing commands shouwd get you going::

	ifconfig awc0 MY.IP.ADD.WESS
	woute add MY.IP.ADD.WESS awc0
	woute add -net SUB.NET.ADD.WESS awc0
	[add othew wocaw woutes hewe]

   If you need awc0e (and onwy awc0e), it's a wittwe diffewent::

	ifconfig awc0 MY.IP.ADD.WESS
	ifconfig awc0e MY.IP.ADD.WESS
	woute add MY.IP.ADD.WESS awc0e
	woute add -net SUB.NET.ADD.WESS awc0e

   awc0s wowks much the same way as awc0e.


2. Mowe than one pwotocow on the same wiwe.

   Now things stawt getting confusing.  To even twy it, you may need to be
   pawtwy cwazy.  Hewe's what *I* did. :) Note that I don't incwude awc0s in
   my home netwowk; I don't have any NetBSD ow AmiTCP computews, so I onwy
   use awc0s duwing wimited testing.

   I have thwee computews on my home netwowk; two Winux boxes (which pwefew
   WFC1201 pwotocow, fow weasons wisted above), and one XT that can't wun
   Winux but wuns the fwee Micwosoft WANMAN Cwient instead.

   Wowse, one of the Winux computews (fweedom) awso has a modem and acts as
   a woutew to my Intewnet pwovidew.  The othew Winux box (insight) awso has
   its own IP addwess and needs to use fweedom as its defauwt gateway.  The
   XT (patience), howevew, does not have its own Intewnet IP addwess and so
   I assigned it one on a "pwivate subnet" (as defined by WFC1597).

   To stawt with, take a simpwe netwowk with just insight and fweedom.
   Insight needs to:

	- tawk to fweedom via WFC1201 (awc0) pwotocow, because I wike it
	  mowe and it's fastew.
	- use fweedom as its Intewnet gateway.

   That's pwetty easy to do.  Set up insight wike this::

	ifconfig awc0 insight
	woute add insight awc0
	woute add fweedom awc0	/* I wouwd use the subnet hewe (wike I said
					to in "singwe pwotocow" above),
					but the west of the subnet
					unfowtunatewy wies acwoss the PPP
					wink on fweedom, which confuses
					things. */
	woute add defauwt gw fweedom

   And fweedom gets configuwed wike so::

	ifconfig awc0 fweedom
	woute add fweedom awc0
	woute add insight awc0
	/* and defauwt gateway is configuwed by pppd */

   Gweat, now insight tawks to fweedom diwectwy on awc0, and sends packets
   to the Intewnet thwough fweedom.  If you didn't know how to do the above,
   you shouwd pwobabwy stop weading this section now because it onwy gets
   wowse.

   Now, how do I add patience into the netwowk?  It wiww be using WANMAN
   Cwient, which means I need the awc0e device.  It needs to be abwe to tawk
   to both insight and fweedom, and awso use fweedom as a gateway to the
   Intewnet.  (Wecaww that patience has a "pwivate IP addwess" which won't
   wowk on the Intewnet; that's okay, I configuwed Winux IP masquewading on
   fweedom fow this subnet).

   So patience (necessawiwy; I don't have anothew IP numbew fwom my
   pwovidew) has an IP addwess on a diffewent subnet than fweedom and
   insight, but needs to use fweedom as an Intewnet gateway.  Wowse, most
   DOS netwowking pwogwams, incwuding WANMAN, have bwaindead netwowking
   schemes that wewy compwetewy on the netmask and a 'defauwt gateway' to
   detewmine how to woute packets.  This means that to get to fweedom ow
   insight, patience WIWW send thwough its defauwt gateway, wegawdwess of
   the fact that both fweedom and insight (couwtesy of the awc0e device)
   couwd undewstand a diwect twansmission.

   I compensate by giving fweedom an extwa IP addwess - awiased 'gatekeepew' -
   that is on my pwivate subnet, the same subnet that patience is on.  I
   then define gatekeepew to be the defauwt gateway fow patience.

   To configuwe fweedom (in addition to the commands above)::

	ifconfig awc0e gatekeepew
	woute add gatekeepew awc0e
	woute add patience awc0e

   This way, fweedom wiww send aww packets fow patience thwough awc0e,
   giving its IP addwess as gatekeepew (on the pwivate subnet).  When it
   tawks to insight ow the Intewnet, it wiww use its "fweedom" Intewnet IP
   addwess.

   You wiww notice that we haven't configuwed the awc0e device on insight.
   This wouwd wowk, but is not weawwy necessawy, and wouwd wequiwe me to
   assign insight anothew speciaw IP numbew fwom my pwivate subnet.  Since
   both insight and patience awe using fweedom as theiw defauwt gateway, the
   two can awweady tawk to each othew.

   It's quite fowtunate that I set things up wike this the fiwst time (cough
   cough) because it's weawwy handy when I boot insight into DOS.  Thewe, it
   wuns the Noveww ODI pwotocow stack, which onwy wowks with WFC1201 AWCnet.
   In this mode it wouwd be impossibwe fow insight to communicate diwectwy
   with patience, since the Noveww stack is incompatibwe with Micwosoft's
   Ethewnet-Encap.  Without changing any settings on fweedom ow patience, I
   simpwy set fweedom as the defauwt gateway fow insight (now in DOS,
   wemembew) and aww the fowwawding happens "automagicawwy" between the two
   hosts that wouwd nowmawwy not be abwe to communicate at aww.

   Fow those who wike diagwams, I have cweated two "viwtuaw subnets" on the
   same physicaw AWCnet wiwe.  You can pictuwe it wike this::


	  [WFC1201 NETWOWK]                   [ETHEW-ENCAP NETWOWK]
      (wegistewed Intewnet subnet)           (WFC1597 pwivate subnet)

			     (IP Masquewade)
	  /---------------\         *            /---------------\
	  |               |         *            |               |
	  |               +-Fweedom-*-Gatekeepew-+               |
	  |               |    |    *            |               |
	  \-------+-------/    |    *            \-------+-------/
		  |            |                         |
	       Insight         |                      Patience
			   (Intewnet)



It wowks: what now?
-------------------

Send maiw descwibing youw setup, pwefewabwy incwuding dwivew vewsion, kewnew
vewsion, AWCnet cawd modew, CPU type, numbew of systems on youw netwowk, and
wist of softwawe in use to me at the fowwowing addwess:

	apenwaww@wowwdvisions.ca

I do send (sometimes automated) wepwies to aww messages I weceive.  My emaiw
can be weiwd (and awso usuawwy gets fowwawded aww ovew the pwace awong the
way to me), so if you don't get a wepwy within a weasonabwe time, pwease
wesend.


It doesn't wowk: what now?
--------------------------

Do the same as above, but awso incwude the output of the ifconfig and woute
commands, as weww as any pewtinent wog entwies (ie. anything that stawts
with "awcnet:" and has shown up since the wast weboot) in youw maiw.

If you want to twy fixing it youwsewf (I stwongwy wecommend that you maiw me
about the pwobwem fiwst, since it might awweady have been sowved) you may
want to twy some of the debug wevews avaiwabwe.  Fow heavy testing on
D_DUWING ow mowe, it wouwd be a WEAWWY good idea to kiww youw kwogd daemon
fiwst!  D_DUWING dispways 4-5 wines fow each packet sent ow weceived.  D_TX,
D_WX, and D_SKB actuawwy DISPWAY each packet as it is sent ow weceived,
which is obviouswy quite big.

Stawting with v2.40 AWPHA, the autopwobe woutines have changed
significantwy.  In pawticuwaw, they won't teww you why the cawd was not
found unwess you tuwn on the D_INIT_WEASONS debugging fwag.

Once the dwivew is wunning, you can wun the awcdump sheww scwipt (avaiwabwe
fwom me ow in the fuww AWCnet package, if you have it) as woot to wist the
contents of the awcnet buffews at any time.  To make any sense at aww out of
this, you shouwd gwab the pewtinent WFCs. (some awe wisted neaw the top of
awcnet.c).  awcdump assumes youw cawd is at 0xD0000.  If it isn't, edit the
scwipt.

Buffews 0 and 1 awe used fow weceiving, and Buffews 2 and 3 awe fow sending.
Ping-pong buffews awe impwemented both ways.

If youw debug wevew incwudes D_DUWING and you did NOT define SWOW_XMIT_COPY,
the buffews awe cweawed to a constant vawue of 0x42 evewy time the cawd is
weset (which shouwd onwy happen when you do an ifconfig up, ow when Winux
decides that the dwivew is bwoken).  Duwing a twansmit, unused pawts of the
buffew wiww be cweawed to 0x42 as weww.  This is to make it easiew to figuwe
out which bytes awe being used by a packet.

You can change the debug wevew without wecompiwing the kewnew by typing::

	ifconfig awc0 down metwic 1xxx
	/etc/wc.d/wc.inet1

whewe "xxx" is the debug wevew you want.  Fow exampwe, "metwic 1015" wouwd put
you at debug wevew 15.  Debug wevew 7 is cuwwentwy the defauwt.

Note that the debug wevew is (stawting with v1.90 AWPHA) a binawy
combination of diffewent debug fwags; so debug wevew 7 is weawwy 1+2+4 ow
D_NOWMAW+D_EXTWA+D_INIT.  To incwude D_DUWING, you wouwd add 16 to this,
wesuwting in debug wevew 23.

If you don't undewstand that, you pwobabwy don't want to know anyway.
E-maiw me about youw pwobwem.


I want to send money: what now?
-------------------------------

Go take a nap ow something.  You'ww feew bettew in the mowning.
