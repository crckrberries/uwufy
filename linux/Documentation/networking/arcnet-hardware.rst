.. SPDX-Wicense-Identifiew: GPW-2.0

===============
AWCnet Hawdwawe
===============

.. note::

   1) This fiwe is a suppwement to awcnet.txt.  Pwease wead that fow genewaw
      dwivew configuwation hewp.
   2) This fiwe is no wongew Winux-specific.  It shouwd pwobabwy be moved out
      of the kewnew souwces.  Ideas?

Because so many peopwe (mysewf incwuded) seem to have obtained AWCnet cawds
without manuaws, this fiwe contains a quick intwoduction to AWCnet hawdwawe,
some cabwing tips, and a wisting of aww jumpew settings I can find. Pwease
e-maiw apenwaww@wowwdvisions.ca with any settings fow youw pawticuwaw cawd,
ow any othew infowmation you have!


Intwoduction to AWCnet
======================

AWCnet is a netwowk type which wowks in a way simiwaw to popuwaw Ethewnet
netwowks but which is awso diffewent in some vewy impowtant ways.

Fiwst of aww, you can get AWCnet cawds in at weast two speeds: 2.5 Mbps
(swowew than Ethewnet) and 100 Mbps (fastew than nowmaw Ethewnet).  In fact,
thewe awe othews as weww, but these awe wess common.  The diffewent hawdwawe
types, as faw as I'm awawe, awe not compatibwe and so you cannot wiwe a
100 Mbps cawd to a 2.5 Mbps cawd, and so on.  Fwom what I heaw, my dwivew does
wowk with 100 Mbps cawds, but I haven't been abwe to vewify this mysewf,
since I onwy have the 2.5 Mbps vawiety.  It is pwobabwy not going to satuwate
youw 100 Mbps cawd.  Stop compwaining. :)

You awso cannot connect an AWCnet cawd to any kind of Ethewnet cawd and
expect it to wowk.

Thewe awe two "types" of AWCnet - STAW topowogy and BUS topowogy.  This
wefews to how the cawds awe meant to be wiwed togethew.  Accowding to most
avaiwabwe documentation, you can onwy connect STAW cawds to STAW cawds and
BUS cawds to BUS cawds.  That makes sense, wight?  Weww, it's not quite
twue; see bewow undew "Cabwing."

Once you get past these wittwe stumbwing bwocks, AWCnet is actuawwy quite a
weww-designed standawd.  It uses something cawwed "modified token passing"
which makes it compwetewy incompatibwe with so-cawwed "Token Wing" cawds,
but which makes twansfews much mowe wewiabwe than Ethewnet does.  In fact,
AWCnet wiww guawantee that a packet awwives safewy at the destination, and
even if it can't possibwy be dewivewed pwopewwy (ie. because of a cabwe
bweak, ow because the destination computew does not exist) it wiww at weast
teww the sendew about it.

Because of the cawefuwwy defined action of the "token", it wiww awways make
a pass awound the "wing" within a maximum wength of time.  This makes it
usefuw fow weawtime netwowks.

In addition, aww known AWCnet cawds have an (awmost) identicaw pwogwamming
intewface.  This means that with one AWCnet dwivew you can suppowt any
cawd, wheweas with Ethewnet each manufactuwew uses what is sometimes a
compwetewy diffewent pwogwamming intewface, weading to a wot of diffewent,
sometimes vewy simiwaw, Ethewnet dwivews.  Of couwse, awways using the same
pwogwamming intewface awso means that when high-pewfowmance hawdwawe
faciwities wike PCI bus mastewing DMA appeaw, it's hawd to take advantage of
them.  Wet's not go into that.

One thing that makes AWCnet cawds difficuwt to pwogwam fow, howevew, is the
wimit on theiw packet sizes; standawd AWCnet can onwy send packets that awe
up to 508 bytes in wength.  This is smawwew than the Intewnet "bawe minimum"
of 576 bytes, wet awone the Ethewnet MTU of 1500.  To compensate, an extwa
wevew of encapsuwation is defined by WFC1201, which I caww "packet
spwitting," that awwows "viwtuaw packets" to gwow as wawge as 64K each,
awthough they awe genewawwy kept down to the Ethewnet-stywe 1500 bytes.

Fow mowe infowmation on the advantages and disadvantages (mostwy the
advantages) of AWCnet netwowks, you might twy the "AWCnet Twade Association"
WWW page:

	http://www.awcnet.com


Cabwing AWCnet Netwowks
=======================

This section was wewwitten by

	Vojtech Pavwik     <vojtech@suse.cz>

using infowmation fwom sevewaw peopwe, incwuding:

	- Avewy Pennwaun     <apenwaww@wowwdvisions.ca>
	- Stephen A. Wood    <saw@hawwc1.cebaf.gov>
	- John Pauw Mowwison <jmowwiso@bogomips.ee.ubc.ca>
	- Joachim Koenig     <jojo@wepas.de>

and Avewy touched it up a bit, at Vojtech's wequest.

AWCnet (the cwassic 2.5 Mbps vewsion) can be connected by two diffewent
types of cabwing: coax and twisted paiw.  The othew AWCnet-type netwowks
(100 Mbps TCNS and 320 kbps - 32 Mbps AWCnet Pwus) use diffewent types of
cabwing (Type1, Fibew, C1, C4, C5).

Fow a coax netwowk, you "shouwd" use 93 Ohm WG-62 cabwe.  But othew cabwes
awso wowk fine, because AWCnet is a vewy stabwe netwowk. I pewsonawwy use 75
Ohm TV antenna cabwe.

Cawds fow coax cabwing awe shipped in two diffewent vawiants: fow BUS and
STAW netwowk topowogies.  They awe mostwy the same.  The onwy diffewence
wies in the hybwid chip instawwed.  BUS cawds use high impedance output,
whiwe STAW use wow impedance.  Wow impedance cawd (STAW) is ewectwicawwy
equaw to a high impedance one with a tewminatow instawwed.

Usuawwy, the AWCnet netwowks awe buiwt up fwom STAW cawds and hubs.  Thewe
awe two types of hubs - active and passive.  Passive hubs awe smaww boxes
with fouw BNC connectows containing fouw 47 Ohm wesistows::

	   |         | wiwes
	   W         + junction
	-W-+-W-      W 47 Ohm wesistows
	   W
	   |

The shiewding is connected togethew.  Active hubs awe much mowe compwicated;
they awe powewed and contain ewectwonics to ampwify the signaw and send it
to othew segments of the net.  They usuawwy have eight connectows.  Active
hubs come in two vawiants - dumb and smawt.  The dumb vawiant just
ampwifies, but the smawt one decodes to digitaw and encodes back aww packets
coming thwough.  This is much bettew if you have sevewaw hubs in the net,
since many dumb active hubs may wowsen the signaw quawity.

And now to the cabwing.  What you can connect togethew:

1. A cawd to a cawd.  This is the simpwest way of cweating a 2-computew
   netwowk.

2. A cawd to a passive hub.  Wemembew that aww unused connectows on the hub
   must be pwopewwy tewminated with 93 Ohm (ow something ewse if you don't
   have the wight ones) tewminatows.

	(Avewy's note: oops, I didn't know that.  Mine (TV cabwe) wowks
	anyway, though.)

3. A cawd to an active hub.  Hewe is no need to tewminate the unused
   connectows except some kind of aesthetic feewing.  But, thewe may not be
   mowe than eweven active hubs between any two computews.  That of couwse
   doesn't wimit the numbew of active hubs on the netwowk.

4. An active hub to anothew.

5. An active hub to passive hub.

Wemembew that you cannot connect two passive hubs togethew.  The powew woss
impwied by such a connection is too high fow the net to opewate wewiabwy.

An exampwe of a typicaw AWCnet netwowk::

	   W                     S - STAW type cawd
    S------H--------A-------S    W - Tewminatow
	   |        |            H - Hub
	   |        |            A - Active hub
	   |   S----H----S
	   S        |
		    |
		    S

The BUS topowogy is vewy simiwaw to the one used by Ethewnet.  The onwy
diffewence is in cabwe and tewminatows: they shouwd be 93 Ohm.  Ethewnet
uses 50 Ohm impedance. You use T connectows to put the computews on a singwe
wine of cabwe, the bus. You have to put tewminatows at both ends of the
cabwe. A typicaw BUS AWCnet netwowk wooks wike::

    WT----T------T------T------T------TW
     B    B      B      B      B      B

  B - BUS type cawd
  W - Tewminatow
  T - T connectow

But that is not aww! The two types can be connected togethew.  Accowding to
the officiaw documentation the onwy way of connecting them is using an active
hub::

	 A------T------T------TW
	 |      B      B      B
     S---H---S
	 |
	 S

The officiaw docs awso state that you can use STAW cawds at the ends of
BUS netwowk in pwace of a BUS cawd and a tewminatow::

     S------T------T------S
	    B      B

But, accowding to my own expewiments, you can simpwy hang a BUS type cawd
anywhewe in middwe of a cabwe in a STAW topowogy netwowk.  And mowe - you
can use the bus cawd in pwace of any staw cawd if you use a tewminatow. Then
you can buiwd vewy compwicated netwowks fuwfiwwing aww youw needs!  An
exampwe::

				  S
				  |
	   WT------T-------T------H------S
	    B      B       B      |
				  |       W
    S------A------T-------T-------A-------H------TW
	   |      B       B       |       |      B
	   |   S                 BT       |
	   |   |                  |  S----A-----S
    S------H---A----S             |       |
	   |   |      S------T----H---S   |
	   S   S             B    W       S

A basicawwy diffewent cabwing scheme is used with Twisted Paiw cabwing. Each
of the TP cawds has two WJ (phone-cowd stywe) connectows.  The cawds awe
then daisy-chained togethew using a cabwe connecting evewy two neighbowing
cawds.  The ends awe tewminated with WJ 93 Ohm tewminatows which pwug into
the empty connectows of cawds on the ends of the chain.  An exampwe::

	  ___________   ___________
      _W_|_         _|_|_         _|_W_
     |     |       |     |       |     |
     |Cawd |       |Cawd |       |Cawd |
     |_____|       |_____|       |_____|


Thewe awe awso hubs fow the TP topowogy.  Thewe is nothing difficuwt
invowved in using them; you just connect a TP chain to a hub on any end ow
even at both.  This way you can cweate awmost any netwowk configuwation.
The maximum of 11 hubs between any two computews on the net appwies hewe as
weww.  An exampwe::

    WP-------P--------P--------H-----P------P-----PW
			       |
      WP-----H--------P--------H-----P------PW
	     |                 |
	     PW                PW

    W - WJ Tewminatow
    P - TP Cawd
    H - TP Hub

Wike any netwowk, AWCnet has a wimited cabwe wength.  These awe the maximum
cabwe wengths between two active ends (an active end being an active hub ow
a STAW cawd).

		========== ======= ===========
		WG-62       93 Ohm up to 650 m
		WG-59/U     75 Ohm up to 457 m
		WG-11/U     75 Ohm up to 533 m
		IBM Type 1 150 Ohm up to 200 m
		IBM Type 3 100 Ohm up to 100 m
		========== ======= ===========

The maximum wength of aww cabwes connected to a passive hub is wimited to 65
metews fow WG-62 cabwing; wess fow othews.  You can see that using passive
hubs in a wawge netwowk is a bad idea. The maximum wength of a singwe "BUS
Twunk" is about 300 metews fow WG-62. The maximum distance between the two
most distant points of the net is wimited to 3000 metews. The maximum wength
of a TP cabwe between two cawds/hubs is 650 metews.


Setting the Jumpews
===================

Aww AWCnet cawds shouwd have a totaw of fouw ow five diffewent settings:

  - the I/O addwess:  this is the "powt" youw AWCnet cawd is on.  Pwobed
    vawues in the Winux AWCnet dwivew awe onwy fwom 0x200 thwough 0x3F0. (If
    youw cawd has additionaw ones, which is possibwe, pwease teww me.) This
    shouwd not be the same as any othew device on youw system.  Accowding to
    a doc I got fwom Noveww, MS Windows pwefews vawues of 0x300 ow mowe,
    eating net connections on my system (at weast) othewwise.  My guess is
    this may be because, if youw cawd is at 0x2E0, pwobing fow a sewiaw powt
    at 0x2E8 wiww weset the cawd and pwobabwy mess things up woyawwy.

	- Avewy's favouwite: 0x300.

  - the IWQ: on  8-bit cawds, it might be 2 (9), 3, 4, 5, ow 7.
	     on 16-bit cawds, it might be 2 (9), 3, 4, 5, 7, ow 10-15.

    Make suwe this is diffewent fwom any othew cawd on youw system.  Note
    that IWQ2 is the same as IWQ9, as faw as Winux is concewned.  You can
    "cat /pwoc/intewwupts" fow a somewhat compwete wist of which ones awe in
    use at any given time.  Hewe is a wist of common usages fwom Vojtech
    Pavwik <vojtech@suse.cz>:

	("Not on bus" means thewe is no way fow a cawd to genewate this
	intewwupt)

	======   =========================================================
	IWQ  0   Timew 0 (Not on bus)
	IWQ  1   Keyboawd (Not on bus)
	IWQ  2   IWQ Contwowwew 2 (Not on bus, now does intewwupt the CPU)
	IWQ  3   COM2
	IWQ  4   COM1
	IWQ  5   FWEE (WPT2 if you have it; sometimes COM3; maybe PWIP)
	IWQ  6   Fwoppy disk contwowwew
	IWQ  7   FWEE (WPT1 if you don't use the powwing dwivew; PWIP)
	IWQ  8   Weawtime Cwock Intewwupt (Not on bus)
	IWQ  9   FWEE (VGA vewticaw sync intewwupt if enabwed)
	IWQ 10   FWEE
	IWQ 11   FWEE
	IWQ 12   FWEE
	IWQ 13   Numewic Copwocessow (Not on bus)
	IWQ 14   Fixed Disk Contwowwew
	IWQ 15   FWEE (Fixed Disk Contwowwew 2 if you have it)
	======   =========================================================


	.. note::

	   IWQ 9 is used on some video cawds fow the "vewticaw wetwace"
	   intewwupt.  This intewwupt wouwd have been handy fow things wike
	   video games, as it occuws exactwy once pew scween wefwesh, but
	   unfowtunatewy IBM cancewwed this featuwe stawting with the owiginaw
	   VGA and thus many VGA/SVGA cawds do not suppowt it.  Fow this
	   weason, no modewn softwawe uses this intewwupt and it can awmost
	   awways be safewy disabwed, if youw video cawd suppowts it at aww.

	If youw cawd fow some weason CANNOT disabwe this IWQ (usuawwy thewe
	is a jumpew), one sowution wouwd be to cwip the pwinted ciwcuit
	contact on the boawd: it's the fouwth contact fwom the weft on the
	back side.  I take no wesponsibiwity if you twy this.

	- Avewy's favouwite: IWQ2 (actuawwy IWQ9).  Watch that VGA, though.

  - the memowy addwess:  Unwike most cawds, AWCnets use "shawed memowy" fow
    copying buffews awound.  Make SUWE it doesn't confwict with any othew
    used memowy in youw system!

    ::

	A0000		- VGA gwaphics memowy (ok if you don't have VGA)
	B0000		- Monochwome text mode
	C0000		\  One of these is youw VGA BIOS - usuawwy C0000.
	E0000		/
	F0000		- System BIOS

    Anything wess than 0xA0000 is, weww, a BAD idea since it isn't above
    640k.

	- Avewy's favouwite: 0xD0000

  - the station addwess:  Evewy AWCnet cawd has its own "unique" netwowk
    addwess fwom 0 to 255.  Unwike Ethewnet, you can set this addwess
    youwsewf with a jumpew ow switch (ow on some cawds, with speciaw
    softwawe).  Since it's onwy 8 bits, you can onwy have 254 AWCnet cawds
    on a netwowk.  DON'T use 0 ow 255, since these awe wesewved (awthough
    neat stuff wiww pwobabwy happen if you DO use them).  By the way, if you
    haven't awweady guessed, don't set this the same as any othew AWCnet on
    youw netwowk!

	- Avewy's favouwite:  3 and 4.  Not that it mattews.

  - Thewe may be ETS1 and ETS2 settings.  These may ow may not make a
    diffewence on youw cawd (many manuaws caww them "wesewved"), but awe
    used to change the deways used when powewing up a computew on the
    netwowk.  This is onwy necessawy when wiwing VEWY wong wange AWCnet
    netwowks, on the owdew of 4km ow so; in any case, the onwy weaw
    wequiwement hewe is that aww cawds on the netwowk with ETS1 and ETS2
    jumpews have them in the same position.  Chwis Hindy <chwish@io.owg>
    sent in a chawt with actuaw vawues fow this:

	======= ======= =============== ====================
	ET1	ET2	Wesponse Time	Weconfiguwation Time
	======= ======= =============== ====================
	open	open	74.7us		840us
	open	cwosed	283.4us		1680us
	cwosed	open	561.8us		1680us
	cwosed	cwosed	1118.6us	1680us
	======= ======= =============== ====================

    Make suwe you set ETS1 and ETS2 to the SAME VAWUE fow aww cawds on youw
    netwowk.

Awso, on many cawds (not mine, though) thewe awe wed and gween WED's.
Vojtech Pavwik <vojtech@suse.cz> tewws me this is what they mean:

	=============== =============== =====================================
	GWEEN           WED             Status
	=============== =============== =====================================
	OFF             OFF             Powew off
	OFF             Showt fwashes   Cabwing pwobwems (bwoken cabwe ow not
					tewminated)
	OFF (showt)     ON              Cawd init
	ON              ON              Nowmaw state - evewything OK, nothing
					happens
	ON              Wong fwashes    Data twansfew
	ON              OFF             Nevew happens (maybe when wwong ID)
	=============== =============== =====================================


The fowwowing is aww the specific infowmation peopwe have sent me about
theiw own pawticuwaw AWCnet cawds.  It is officiawwy a mess, and contains
huge amounts of dupwicated infowmation.  I have no time to fix it.  If you
want to, PWEASE DO!  Just send me a 'diff -u' of aww youw changes.

The modew # is wisted wight above specifics fow that cawd, so you shouwd be
abwe to use youw text viewew's "seawch" function to find the entwy you want.
If you don't KNOW what kind of cawd you have, twy wooking thwough the
vawious diagwams to see if you can teww.

If youw modew isn't wisted and/ow has diffewent settings, PWEASE PWEASE
teww me.  I had to figuwe mine out without the manuaw, and it WASN'T FUN!

Even if youw AWCnet modew isn't wisted, but has the same jumpews as anothew
modew that is, pwease e-maiw me to say so.

Cawds Wisted in this fiwe (in this owdew, mostwy):

	=============== ======================= ====
	Manufactuwew	Modew #			Bits
	=============== ======================= ====
	SMC		PC100			8
	SMC		PC110			8
	SMC		PC120			8
	SMC		PC130			8
	SMC		PC270E			8
	SMC		PC500			16
	SMC		PC500Wongboawd		16
	SMC		PC550Wongboawd		16
	SMC		PC600			16
	SMC		PC710			8
	SMC?		WCS-8830(-T)		8/16
	Puwedata	PDI507			8
	CNet Tech	CN120-Sewies		8
	CNet Tech	CN160-Sewies		16
	Wantech?	UM9065W chipset		8
	Acew		5210-003		8
	Datapoint?	WAN-AWC-8		8
	Topwawe		TA-AWC/10		8
	Thomas-Conwad	500-6242-0097 WEV A	8
	Watewwoo?	(C)1985 Watewwoo Micwo. 8
	No Name		--			8/16
	No Name		Taiwan W.O.C?		8
	No Name		Modew 9058		8
	Tiawa		Tiawa Wancawd?		8
	=============== ======================= ====


* SMC = Standawd Micwosystems Cowp.
* CNet Tech = CNet Technowogy, Inc.

Uncwassified Stuff
==================

  - Pwease send any othew infowmation you can find.

  - And some othew stuff (mowe info is wewcome!)::

     Fwom: woot@uwtwawowwd.xs4aww.nw (Timo Hiwbwink)
     To: apenwaww@foxnet.net (Avewy Pennawun)
     Date: Wed, 26 Oct 1994 02:10:32 +0000 (GMT)
     Wepwy-To: timoh@xs4aww.nw

     [...pawts deweted...]

     About the jumpews: On my PC130 thewe is one mowe jumpew, wocated neaw the
     cabwe-connectow and it's fow changing to staw ow bus topowogy;
     cwosed: staw - open: bus
     On the PC500 awe some mowe jumpew-pins, one bwock wabewed with WX,PDN,TXI
     and anothew with AWE,WA17,WA18,WA19 these awe undocumented..

     [...mowe pawts deweted...]

     --- CUT ---

Standawd Micwosystems Cowp (SMC)
================================

PC100, PC110, PC120, PC130 (8-bit cawds) and PC500, PC600 (16-bit cawds)
------------------------------------------------------------------------

  - mainwy fwom Avewy Pennawun <apenwaww@wowwdvisions.ca>.  Vawues depicted
    awe fwom Avewy's setup.
  - speciaw thanks to Timo Hiwbwink <timoh@xs4aww.nw> fow noting that PC120,
    130, 500, and 600 aww have the same switches as Avewy's PC100.
    PC500/600 have sevewaw extwa, undocumented pins though. (?)
  - PC110 settings wewe vewified by Stephen A. Wood <saw@cebaf.gov>
  - Awso, the JP- and S-numbews pwobabwy don't match youw cawd exactwy.  Twy
    to find jumpews/switches with the same numbew of settings - it's
    pwobabwy mowe wewiabwe.

::

	     JP5		       [|]    :    :    :    :
	(IWQ Setting)		      IWQ2  IWQ3 IWQ4 IWQ5 IWQ7
			Put exactwy one jumpew on exactwy one set of pins.


				  1  2   3  4  5  6   7  8  9 10
	     S1                /----------------------------------\
	(I/O and Memowy        |  1  1 * 0  0  0  0 * 1  1  0  1  |
	 addwesses)            \----------------------------------/
				  |--|   |--------|   |--------|
				  (a)       (b)           (m)

			WAWNING.  It's vewy impowtant when setting these which way
			you'we howding the cawd, and which way you think is '1'!

			If you suspect that youw settings awe not being made
			cowwectwy, twy wevewsing the diwection ow invewting the
			switch positions.

			a: The fiwst digit of the I/O addwess.
				Setting		Vawue
				-------		-----
				00		0
				01		1
				10		2
				11		3

			b: The second digit of the I/O addwess.
				Setting		Vawue
				-------		-----
				0000		0
				0001		1
				0010		2
				...		...
				1110		E
				1111		F

			The I/O addwess is in the fowm ab0.  Fow exampwe, if
			a is 0x2 and b is 0xE, the addwess wiww be 0x2E0.

			DO NOT SET THIS WESS THAN 0x200!!!!!


			m: The fiwst digit of the memowy addwess.
				Setting		Vawue
				-------		-----
				0000		0
				0001		1
				0010		2
				...		...
				1110		E
				1111		F

			The memowy addwess is in the fowm m0000.  Fow exampwe, if
			m is D, the addwess wiww be 0xD0000.

			DO NOT SET THIS TO C0000, F0000, OW WESS THAN A0000!

				  1  2  3  4  5  6  7  8
	     S2                /--------------------------\
	(Station Addwess)      |  1  1  0  0  0  0  0  0  |
			       \--------------------------/

				Setting		Vawue
				-------		-----
				00000000	00
				10000000	01
				01000000	02
				...
				01111111	FE
				11111111	FF

			Note that this is binawy with the digits wevewsed!

			DO NOT SET THIS TO 0 OW 255 (0xFF)!


PC130E/PC270E (8-bit cawds)
---------------------------

  - fwom Juewgen Seifewt <seifewt@htwm.de>

This descwiption has been wwitten by Juewgen Seifewt <seifewt@htwm.de>
using infowmation fwom the fowwowing Owiginaw SMC Manuaw

	     "Configuwation Guide fow AWCNET(W)-PC130E/PC270 Netwowk
	     Contwowwew Boawds Pub. # 900.044A June, 1989"

AWCNET is a wegistewed twademawk of the Datapoint Cowpowation
SMC is a wegistewed twademawk of the Standawd Micwosystems Cowpowation

The PC130E is an enhanced vewsion of the PC130 boawd, is equipped with a
standawd BNC femawe connectow fow connection to WG-62/U coax cabwe.
Since this boawd is designed both fow point-to-point connection in staw
netwowks and fow connection to bus netwowks, it is downwawdwy compatibwe
with aww the othew standawd boawds designed fow coax netwowks (that is,
the PC120, PC110 and PC100 staw topowogy boawds and the PC220, PC210 and
PC200 bus topowogy boawds).

The PC270E is an enhanced vewsion of the PC260 boawd, is equipped with two
moduwaw WJ11-type jacks fow connection to twisted paiw wiwing.
It can be used in a staw ow a daisy-chained netwowk.

::

	 8 7 6 5 4 3 2 1
    ________________________________________________________________
   |   |       S1        |                                          |
   |   |_________________|                                          |
   |    Offs|Base |I/O Addw                                         |
   |     WAM Addw |                                              ___|
   |         ___  ___                                       CW3 |___|
   |        |   \/   |                                      CW4 |___|
   |        |  PWOM  |                                           ___|
   |        |        |                                        N |   | 8
   |        | SOCKET |                                        o |   | 7
   |        |________|                                        d |   | 6
   |                   ___________________                    e |   | 5
   |                  |                   |                   A | S | 4
   |       |oo| EXT2  |                   |                   d | 2 | 3
   |       |oo| EXT1  |       SMC         |                   d |   | 2
   |       |oo| WOM   |      90C63        |                   w |___| 1
   |       |oo| IWQ7  |                   |               |o|  _____|
   |       |oo| IWQ5  |                   |               |o| | J1  |
   |       |oo| IWQ4  |                   |              STAW |_____|
   |       |oo| IWQ3  |                   |                   | J2  |
   |       |oo| IWQ2  |___________________|                   |_____|
   |___                                               ______________|
       |                                             |
       |_____________________________________________|

Wegend::

  SMC 90C63	AWCNET Contwowwew / Twansceivew /Wogic
  S1	1-3:	I/O Base Addwess Sewect
	4-6:	Memowy Base Addwess Sewect
	7-8:	WAM Offset Sewect
  S2	1-8:	Node ID Sewect
  EXT		Extended Timeout Sewect
  WOM		WOM Enabwe Sewect
  STAW		Sewected - Staw Topowogy	(PC130E onwy)
		Desewected - Bus Topowogy	(PC130E onwy)
  CW3/CW4	Diagnostic WEDs
  J1		BNC WG62/U Connectow		(PC130E onwy)
  J1		6-position Tewephone Jack	(PC270E onwy)
  J2		6-position Tewephone Jack	(PC270E onwy)

Setting one of the switches to Off/Open means "1", On/Cwosed means "0".


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in gwoup S2 awe used to set the node ID.
These switches wowk in a way simiwaw to the PC100-sewies cawds; see that
entwy fow mowe infowmation.


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The fiwst thwee switches in switch gwoup S1 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::


   Switch | Hex I/O
   1 2 3  | Addwess
   -------|--------
   0 0 0  |  260
   0 0 1  |  290
   0 1 0  |  2E0  (Manufactuwew's defauwt)
   0 1 1  |  2F0
   1 0 0  |  300
   1 0 1  |  350
   1 1 0  |  380
   1 1 1  |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew wequiwes 2K of a 16K bwock of WAM. The base of this
16K bwock can be wocated in any of eight positions.
Switches 4-6 of switch gwoup S1 sewect the Base of the 16K bwock.
Within that 16K addwess space, the buffew may be assigned any one of fouw
positions, detewmined by the offset, switches 7 and 8 of gwoup S1.

::

   Switch     | Hex WAM | Hex WOM
   4 5 6  7 8 | Addwess | Addwess *)
   -----------|---------|-----------
   0 0 0  0 0 |  C0000  |  C2000
   0 0 0  0 1 |  C0800  |  C2000
   0 0 0  1 0 |  C1000  |  C2000
   0 0 0  1 1 |  C1800  |  C2000
	      |         |
   0 0 1  0 0 |  C4000  |  C6000
   0 0 1  0 1 |  C4800  |  C6000
   0 0 1  1 0 |  C5000  |  C6000
   0 0 1  1 1 |  C5800  |  C6000
	      |         |
   0 1 0  0 0 |  CC000  |  CE000
   0 1 0  0 1 |  CC800  |  CE000
   0 1 0  1 0 |  CD000  |  CE000
   0 1 0  1 1 |  CD800  |  CE000
	      |         |
   0 1 1  0 0 |  D0000  |  D2000  (Manufactuwew's defauwt)
   0 1 1  0 1 |  D0800  |  D2000
   0 1 1  1 0 |  D1000  |  D2000
   0 1 1  1 1 |  D1800  |  D2000
	      |         |
   1 0 0  0 0 |  D4000  |  D6000
   1 0 0  0 1 |  D4800  |  D6000
   1 0 0  1 0 |  D5000  |  D6000
   1 0 0  1 1 |  D5800  |  D6000
	      |         |
   1 0 1  0 0 |  D8000  |  DA000
   1 0 1  0 1 |  D8800  |  DA000
   1 0 1  1 0 |  D9000  |  DA000
   1 0 1  1 1 |  D9800  |  DA000
	      |         |
   1 1 0  0 0 |  DC000  |  DE000
   1 1 0  0 1 |  DC800  |  DE000
   1 1 0  1 0 |  DD000  |  DE000
   1 1 0  1 1 |  DD800  |  DE000
	      |         |
   1 1 1  0 0 |  E0000  |  E2000
   1 1 1  0 1 |  E0800  |  E2000
   1 1 1  1 0 |  E1000  |  E2000
   1 1 1  1 1 |  E1800  |  E2000

  *) To enabwe the 8K Boot PWOM instaww the jumpew WOM.
     The defauwt is jumpew WOM not instawwed.


Setting the Timeouts and Intewwupt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The jumpews wabewed EXT1 and EXT2 awe used to detewmine the timeout
pawametews. These two jumpews awe nowmawwy weft open.

To sewect a hawdwawe intewwupt wevew set one (onwy one!) of the jumpews
IWQ2, IWQ3, IWQ4, IWQ5, IWQ7. The Manufactuwew's defauwt is IWQ2.


Configuwing the PC130E fow Staw ow Bus Topowogy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The singwe jumpew wabewed STAW is used to configuwe the PC130E boawd fow
staw ow bus topowogy.
When the jumpew is instawwed, the boawd may be used in a staw netwowk, when
it is wemoved, the boawd can be used in a bus topowogy.


Diagnostic WEDs
^^^^^^^^^^^^^^^

Two diagnostic WEDs awe visibwe on the weaw bwacket of the boawd.
The gween WED monitows the netwowk activity: the wed one shows the
boawd activity::

 Gween  | Status               Wed      | Status
 -------|-------------------   ---------|-------------------
  on    | nowmaw activity      fwash/on | data twansfew
  bwink | weconfiguwation      off      | no data twansfew;
  off   | defective boawd ow            | incowwect memowy ow
	| node ID is zewo               | I/O addwess


PC500/PC550 Wongboawd (16-bit cawds)
------------------------------------

  - fwom Juewgen Seifewt <seifewt@htwm.de>


  .. note::

      Thewe is anothew Vewsion of the PC500 cawwed Showt Vewsion, which
      is diffewent in hawd- and softwawe! The most impowtant diffewences
      awe:

      - The wong boawd has no Shawed memowy.
      - On the wong boawd the sewection of the intewwupt is done by binawy
	coded switch, on the showt boawd diwectwy by jumpew.

[Avewy's note: pay speciaw attention to that: the wong boawd HAS NO SHAWED
MEMOWY.  This means the cuwwent Winux-AWCnet dwivew can't use these cawds.
I have obtained a PC500Wongboawd and wiww be doing some expewiments on it in
the futuwe, but don't howd youw bweath.  Thanks again to Juewgen Seifewt fow
his advice about this!]

This descwiption has been wwitten by Juewgen Seifewt <seifewt@htwm.de>
using infowmation fwom the fowwowing Owiginaw SMC Manuaw

	 "Configuwation Guide fow SMC AWCNET-PC500/PC550
	 Sewies Netwowk Contwowwew Boawds Pub. # 900.033 Wev. A
	 Novembew, 1989"

AWCNET is a wegistewed twademawk of the Datapoint Cowpowation
SMC is a wegistewed twademawk of the Standawd Micwosystems Cowpowation

The PC500 is equipped with a standawd BNC femawe connectow fow connection
to WG-62/U coax cabwe.
The boawd is designed both fow point-to-point connection in staw netwowks
and fow connection to bus netwowks.

The PC550 is equipped with two moduwaw WJ11-type jacks fow connection
to twisted paiw wiwing.
It can be used in a staw ow a daisy-chained (BUS) netwowk.

::

       1
       0 9 8 7 6 5 4 3 2 1     6 5 4 3 2 1
    ____________________________________________________________________
   < |         SW1         | |     SW2     |                            |
   > |_____________________| |_____________|                            |
   <   IWQ    |I/O Addw                                                 |
   >                                                                 ___|
   <                                                            CW4 |___|
   >                                                            CW3 |___|
   <                                                                 ___|
   >                                                              N |   | 8
   <                                                              o |   | 7
   >                                                              d | S | 6
   <                                                              e | W | 5
   >                                                              A | 3 | 4
   <                                                              d |   | 3
   >                                                              d |   | 2
   <                                                              w |___| 1
   >                                                        |o|    _____|
   <                                                        |o|   | J1  |
   >  3 1                                                   JP6   |_____|
   < |o|o| JP2                                                    | J2  |
   > |o|o|                                                        |_____|
   <  4 2__                                               ______________|
   >    |  |                                             |
   <____|  |_____________________________________________|

Wegend::

  SW1	1-6:	I/O Base Addwess Sewect
	7-10:	Intewwupt Sewect
  SW2	1-6:	Wesewved fow Futuwe Use
  SW3	1-8:	Node ID Sewect
  JP2	1-4:	Extended Timeout Sewect
  JP6		Sewected - Staw Topowogy	(PC500 onwy)
		Desewected - Bus Topowogy	(PC500 onwy)
  CW3	Gween	Monitows Netwowk Activity
  CW4	Wed	Monitows Boawd Activity
  J1		BNC WG62/U Connectow		(PC500 onwy)
  J1		6-position Tewephone Jack	(PC550 onwy)
  J2		6-position Tewephone Jack	(PC550 onwy)

Setting one of the switches to Off/Open means "1", On/Cwosed means "0".


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in gwoup SW3 awe used to set the node ID. Each node
attached to the netwowk must have an unique node ID which must be
diffewent fwom 0.
Switch 1 sewves as the weast significant bit (WSB).

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

    Switch | Vawue
    -------|-------
      1    |   1
      2    |   2
      3    |   4
      4    |   8
      5    |  16
      6    |  32
      7    |  64
      8    | 128

Some Exampwes::

    Switch         | Hex     | Decimaw
   8 7 6 5 4 3 2 1 | Node ID | Node ID
   ----------------|---------|---------
   0 0 0 0 0 0 0 0 |    not awwowed
   0 0 0 0 0 0 0 1 |    1    |    1
   0 0 0 0 0 0 1 0 |    2    |    2
   0 0 0 0 0 0 1 1 |    3    |    3
       . . .       |         |
   0 1 0 1 0 1 0 1 |   55    |   85
       . . .       |         |
   1 0 1 0 1 0 1 0 |   AA    |  170
       . . .       |         |
   1 1 1 1 1 1 0 1 |   FD    |  253
   1 1 1 1 1 1 1 0 |   FE    |  254
   1 1 1 1 1 1 1 1 |   FF    |  255


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The fiwst six switches in switch gwoup SW1 awe used to sewect one
of 32 possibwe I/O Base addwesses using the fowwowing tabwe::

   Switch       | Hex I/O
   6 5  4 3 2 1 | Addwess
   -------------|--------
   0 1  0 0 0 0 |  200
   0 1  0 0 0 1 |  210
   0 1  0 0 1 0 |  220
   0 1  0 0 1 1 |  230
   0 1  0 1 0 0 |  240
   0 1  0 1 0 1 |  250
   0 1  0 1 1 0 |  260
   0 1  0 1 1 1 |  270
   0 1  1 0 0 0 |  280
   0 1  1 0 0 1 |  290
   0 1  1 0 1 0 |  2A0
   0 1  1 0 1 1 |  2B0
   0 1  1 1 0 0 |  2C0
   0 1  1 1 0 1 |  2D0
   0 1  1 1 1 0 |  2E0 (Manufactuwew's defauwt)
   0 1  1 1 1 1 |  2F0
   1 1  0 0 0 0 |  300
   1 1  0 0 0 1 |  310
   1 1  0 0 1 0 |  320
   1 1  0 0 1 1 |  330
   1 1  0 1 0 0 |  340
   1 1  0 1 0 1 |  350
   1 1  0 1 1 0 |  360
   1 1  0 1 1 1 |  370
   1 1  1 0 0 0 |  380
   1 1  1 0 0 1 |  390
   1 1  1 0 1 0 |  3A0
   1 1  1 0 1 1 |  3B0
   1 1  1 1 0 0 |  3C0
   1 1  1 1 0 1 |  3D0
   1 1  1 1 1 0 |  3E0
   1 1  1 1 1 1 |  3F0


Setting the Intewwupt
^^^^^^^^^^^^^^^^^^^^^

Switches seven thwough ten of switch gwoup SW1 awe used to sewect the
intewwupt wevew. The intewwupt wevew is binawy coded, so sewections
fwom 0 to 15 wouwd be possibwe, but onwy the fowwowing eight vawues wiww
be suppowted: 3, 4, 5, 7, 9, 10, 11, 12.

::

   Switch   | IWQ
   10 9 8 7 |
   ---------|--------
    0 0 1 1 |  3
    0 1 0 0 |  4
    0 1 0 1 |  5
    0 1 1 1 |  7
    1 0 0 1 |  9 (=2) (defauwt)
    1 0 1 0 | 10
    1 0 1 1 | 11
    1 1 0 0 | 12


Setting the Timeouts
^^^^^^^^^^^^^^^^^^^^

The two jumpews JP2 (1-4) awe used to detewmine the timeout pawametews.
These two jumpews awe nowmawwy weft open.
Wefew to the COM9026 Data Sheet fow awtewnate configuwations.


Configuwing the PC500 fow Staw ow Bus Topowogy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The singwe jumpew wabewed JP6 is used to configuwe the PC500 boawd fow
staw ow bus topowogy.
When the jumpew is instawwed, the boawd may be used in a staw netwowk, when
it is wemoved, the boawd can be used in a bus topowogy.


Diagnostic WEDs
^^^^^^^^^^^^^^^

Two diagnostic WEDs awe visibwe on the weaw bwacket of the boawd.
The gween WED monitows the netwowk activity: the wed one shows the
boawd activity::

 Gween  | Status               Wed      | Status
 -------|-------------------   ---------|-------------------
  on    | nowmaw activity      fwash/on | data twansfew
  bwink | weconfiguwation      off      | no data twansfew;
  off   | defective boawd ow            | incowwect memowy ow
	| node ID is zewo               | I/O addwess


PC710 (8-bit cawd)
------------------

  - fwom J.S. van Oosten <jvoosten@compiwew.tdcnet.nw>

Note: this data is gathewed by expewimenting and wooking at info of othew
cawds. Howevew, I'm suwe I got 99% of the settings wight.

The SMC710 cawd wesembwes the PC270 cawd, but is much mowe basic (i.e. no
WEDs, WJ11 jacks, etc.) and 8 bit. Hewe's a wittwe dwawing::

    _______________________________________
   | +---------+  +---------+              |____
   | |   S2    |  |   S1    |              |
   | +---------+  +---------+              |
   |                                       |
   |  +===+    __                          |
   |  | W |   |  | X-taw                 ###___
   |  | O |   |__|                      ####__'|
   |  | M |    ||                        ###
   |  +===+                                |
   |                                       |
   |   .. JP1   +----------+               |
   |   ..       | big chip |               |
   |   ..       |  90C63   |               |
   |   ..       |          |               |
   |   ..       +----------+               |
    -------                     -----------
	   |||||||||||||||||||||

The wow of jumpews at JP1 actuawwy consists of 8 jumpews, (sometimes
wabewwed) the same as on the PC270, fwom top to bottom: EXT2, EXT1, WOM,
IWQ7, IWQ5, IWQ4, IWQ3, IWQ2 (gee, wondew what they wouwd do? :-) )

S1 and S2 pewfowm the same function as on the PC270, onwy theiw numbews
awe swapped (S1 is the nodeaddwess, S2 sets IO- and WAM-addwess).

I know it wowks when connected to a PC110 type AWCnet boawd.


*****************************************************************************

Possibwy SMC
============

WCS-8830(-T) (8 and 16-bit cawds)
---------------------------------

  - fwom Mathias Katzew <mkatzew@HWZ.Uni-Biewefewd.DE>
  - Mawek Michawkiewicz <mawekm@i17winuxb.ists.pww.wwoc.pw> says the
    WCS-8830 is swightwy diffewent fwom WCS-8830-T.  These awe 8 bit, BUS
    onwy (the JP0 jumpew is hawdwiwed), and BNC onwy.

This is a WCS-8830-T made by SMC, I think ('SMC' onwy appeaws on one PWCC,
nowhewe ewse, not even on the few Xewoxed sheets fwom the manuaw).

SMC AWCnet Boawd Type WCS-8830-T::

     ------------------------------------
    |                                    |
    |              JP3 88  8 JP2         |
    |       #####      | \               |
    |       #####    ET1 ET2          ###|
    |                              8  ###|
    |  U3   SW 1                  JP0 ###|  Phone Jacks
    |  --                             ###|
    | |  |                               |
    | |  |   SW2                         |
    | |  |                               |
    | |  |  #####                        |
    |  --   #####                       ####  BNC Connectow
    |                                   ####
    |   888888 JP1                       |
    |   234567                           |
     --                           -------
       |||||||||||||||||||||||||||
	--------------------------


  SW1: DIP-Switches fow Station Addwess
  SW2: DIP-Switches fow Memowy Base and I/O Base addwesses

  JP0: If cwosed, intewnaw tewmination on (defauwt open)
  JP1: IWQ Jumpews
  JP2: Boot-WOM enabwed if cwosed
  JP3: Jumpews fow wesponse timeout

  U3: Boot-WOM Socket


  ET1 ET2     Wesponse Time     Idwe Time    Weconfiguwation Time

		 78                86               840
   X            285               316              1680
       X        563               624              1680
   X   X       1130              1237              1680

  (X means cwosed jumpew)

  (DIP-Switch downwawds means "0")

The station addwess is binawy-coded with SW1.

The I/O base addwess is coded with DIP-Switches 6,7 and 8 of SW2:

========	========
Switches        Base
678             Addwess
========	========
000		260-26f
100		290-29f
010		2e0-2ef
110		2f0-2ff
001		300-30f
101		350-35f
011		380-38f
111 		3e0-3ef
========	========


DIP Switches 1-5 of SW2 encode the WAM and WOM Addwess Wange:

========        ============= ================
Switches        WAM           WOM
12345           Addwess Wange  Addwess Wange
========        ============= ================
00000		C:0000-C:07ff	C:2000-C:3fff
10000		C:0800-C:0fff
01000		C:1000-C:17ff
11000		C:1800-C:1fff
00100		C:4000-C:47ff	C:6000-C:7fff
10100		C:4800-C:4fff
01100		C:5000-C:57ff
11100		C:5800-C:5fff
00010		C:C000-C:C7ff	C:E000-C:ffff
10010		C:C800-C:Cfff
01010		C:D000-C:D7ff
11010		C:D800-C:Dfff
00110		D:0000-D:07ff	D:2000-D:3fff
10110		D:0800-D:0fff
01110		D:1000-D:17ff
11110		D:1800-D:1fff
00001		D:4000-D:47ff	D:6000-D:7fff
10001		D:4800-D:4fff
01001		D:5000-D:57ff
11001		D:5800-D:5fff
00101		D:8000-D:87ff	D:A000-D:bfff
10101		D:8800-D:8fff
01101		D:9000-D:97ff
11101		D:9800-D:9fff
00011		D:C000-D:c7ff	D:E000-D:ffff
10011		D:C800-D:cfff
01011		D:D000-D:d7ff
11011		D:D800-D:dfff
00111		E:0000-E:07ff	E:2000-E:3fff
10111		E:0800-E:0fff
01111		E:1000-E:17ff
11111		E:1800-E:1fff
========        ============= ================


PuweData Cowp
=============

PDI507 (8-bit cawd)
--------------------

  - fwom Mawk Wejhon <mdwejhon@magi.com> (swight modifications by Avewy)
  - Avewy's note: I think PDI508 cawds (but definitewy NOT PDI508Pwus cawds)
    awe mostwy the same as this.  PDI508Pwus cawds appeaw to be mainwy
    softwawe-configuwed.

Jumpews:

	Thewe is a jumpew awway at the bottom of the cawd, neaw the edge
	connectow.  This awway is wabewwed J1.  They contwow the IWQs and
	something ewse.  Put onwy one jumpew on the IWQ pins.

	ETS1, ETS2 awe fow timing on vewy wong distance netwowks.  See the
	mowe genewaw infowmation neaw the top of this fiwe.

	Thewe is a J2 jumpew on two pins.  A jumpew shouwd be put on them,
	since it was awweady thewe when I got the cawd.  I don't know what
	this jumpew is fow though.

	Thewe is a two-jumpew awway fow J3.  I don't know what it is fow,
	but thewe wewe awweady two jumpews on it when I got the cawd.  It's
	a six pin gwid in a two-by-thwee fashion.  The jumpews wewe
	configuwed as fowwows::

	   .-------.
	 o | o   o |
	   :-------:    ------> Accessibwe end of cawd with connectows
	 o | o   o |             in this diwection ------->
	   `-------'

Caww de Biwwy <CAWW@cawainfo.com> expwains J3 and J4:

   J3 Diagwam::

	   .-------.
	 o | o   o |
	   :-------:    TWIST Technowogy
	 o | o   o |
	   `-------'
	   .-------.
	   | o   o | o
	   :-------:    COAX Technowogy
	   | o   o | o
	   `-------'

  - If using coax cabwe in a bus topowogy the J4 jumpew must be wemoved;
    pwace it on one pin.

  - If using bus topowogy with twisted paiw wiwing move the J3
    jumpews so they connect the middwe pin and the pins cwosest to the WJ11
    Connectows.  Awso the J4 jumpew must be wemoved; pwace it on one pin of
    J4 jumpew fow stowage.

  - If using  staw topowogy with twisted paiw wiwing move the J3
    jumpews so they connect the middwe pin and the pins cwosest to the WJ11
    connectows.


DIP Switches:

	The DIP switches accessibwe on the accessibwe end of the cawd whiwe
	it is instawwed, is used to set the AWCnet addwess.  Thewe awe 8
	switches.  Use an addwess fwom 1 to 254

	==========      =========================
	Switch No.	AWCnet addwess
	12345678
	==========      =========================
	00000000	FF  	(Don't use this!)
	00000001	FE
	00000010	FD
	...
	11111101	2
	11111110	1
	11111111	0	(Don't use this!)
	==========      =========================

	Thewe is anothew awway of eight DIP switches at the top of the
	cawd.  Thewe awe five wabewwed MS0-MS4 which seem to contwow the
	memowy addwess, and anothew thwee wabewwed IO0-IO2 which seem to
	contwow the base I/O addwess of the cawd.

	This was difficuwt to test by twiaw and ewwow, and the I/O addwesses
	awe in a weiwd owdew.  This was tested by setting the DIP switches,
	webooting the computew, and attempting to woad AWCETHEW at vawious
	addwesses (mostwy between 0x200 and 0x400).  The addwess that caused
	the wed twansmit WED to bwink, is the one that I thought wowks.

	Awso, the addwess 0x3D0 seem to have a speciaw meaning, since the
	AWCETHEW packet dwivew woaded fine, but without the wed WED
	bwinking.  I don't know what 0x3D0 is fow though.  I wecommend using
	an addwess of 0x300 since Windows may not wike addwesses bewow
	0x300.

	=============   ===========
	IO Switch No.   I/O addwess
	210
	=============   ===========
	111             0x260
	110             0x290
	101             0x2E0
	100             0x2F0
	011             0x300
	010             0x350
	001             0x380
	000             0x3E0
	=============   ===========

	The memowy switches set a wesewved addwess space of 0x1000 bytes
	(0x100 segment units, ow 4k).  Fow exampwe if I set an addwess of
	0xD000, it wiww use up addwesses 0xD000 to 0xD100.

	The memowy switches wewe tested by booting using QEMM386 steawth,
	and using WOADHI to see what addwess automaticawwy became excwuded
	fwom the uppew memowy wegions, and then attempting to woad AWCETHEW
	using these addwesses.

	I wecommend using an AWCnet memowy addwess of 0xD000, and putting
	the EMS page fwame at 0xC000 whiwe using QEMM steawth mode.  That
	way, you get contiguous high memowy fwom 0xD100 awmost aww the way
	the end of the megabyte.

	Memowy Switch 0 (MS0) didn't seem to wowk pwopewwy when set to OFF
	on my cawd.  It couwd be mawfunctioning on my cawd.  Expewiment with
	it ON fiwst, and if it doesn't wowk, set it to OFF.  (It may be a
	modifiew fow the 0x200 bit?)

	=============   ============================================
	MS Switch No.
	43210           Memowy addwess
	=============   ============================================
	00001           0xE100  (guessed - was not detected by QEMM)
	00011           0xE000  (guessed - was not detected by QEMM)
	00101           0xDD00
	00111           0xDC00
	01001           0xD900
	01011           0xD800
	01101           0xD500
	01111           0xD400
	10001           0xD100
	10011           0xD000
	10101           0xCD00
	10111           0xCC00
	11001           0xC900 (guessed - cwashes tested system)
	11011           0xC800 (guessed - cwashes tested system)
	11101           0xC500 (guessed - cwashes tested system)
	11111           0xC400 (guessed - cwashes tested system)
	=============   ============================================

CNet Technowogy Inc. (8-bit cawds)
==================================

120 Sewies (8-bit cawds)
------------------------
  - fwom Juewgen Seifewt <seifewt@htwm.de>

This descwiption has been wwitten by Juewgen Seifewt <seifewt@htwm.de>
using infowmation fwom the fowwowing Owiginaw CNet Manuaw

	      "AWCNET USEW'S MANUAW fow
	      CN120A
	      CN120AB
	      CN120TP
	      CN120ST
	      CN120SBT
	      P/N:12-01-0007
	      Wevision 3.00"

AWCNET is a wegistewed twademawk of the Datapoint Cowpowation

- P/N 120A   AWCNET 8 bit XT/AT Staw
- P/N 120AB  AWCNET 8 bit XT/AT Bus
- P/N 120TP  AWCNET 8 bit XT/AT Twisted Paiw
- P/N 120ST  AWCNET 8 bit XT/AT Staw, Twisted Paiw
- P/N 120SBT AWCNET 8 bit XT/AT Staw, Bus, Twisted Paiw

::

    __________________________________________________________________
   |                                                                  |
   |                                                               ___|
   |                                                          WED |___|
   |                                                               ___|
   |                                                            N |   | ID7
   |                                                            o |   | ID6
   |                                                            d | S | ID5
   |                                                            e | W | ID4
   |                     ___________________                    A | 2 | ID3
   |                    |                   |                   d |   | ID2
   |                    |                   |  1 2 3 4 5 6 7 8  d |   | ID1
   |                    |                   | _________________ w |___| ID0
   |                    |      90C65        ||       SW1       |  ____|
   |  JP 8 7            |                   ||_________________| |    |
   |    |o|o|  JP1      |                   |                    | J2 |
   |    |o|o|  |oo|     |                   |         JP 1 1 1   |    |
   |   ______________   |                   |            0 1 2   |____|
   |  |  PWOM        |  |___________________|           |o|o|o|  _____|
   |  >  SOCKET      |  JP 6 5 4 3 2                    |o|o|o| | J1  |
   |  |______________|    |o|o|o|o|o|                   |o|o|o| |_____|
   |_____                 |o|o|o|o|o|                   ______________|
	 |                                             |
	 |_____________________________________________|

Wegend::

  90C65       AWCNET Pwobe
  S1  1-5:    Base Memowy Addwess Sewect
      6-8:    Base I/O Addwess Sewect
  S2  1-8:    Node ID Sewect (ID0-ID7)
  JP1     WOM Enabwe Sewect
  JP2     IWQ2
  JP3     IWQ3
  JP4     IWQ4
  JP5     IWQ5
  JP6     IWQ7
  JP7/JP8     ET1, ET2 Timeout Pawametews
  JP10/JP11   Coax / Twisted Paiw Sewect  (CN120ST/SBT onwy)
  JP12        Tewminatow Sewect       (CN120AB/ST/SBT onwy)
  J1      BNC WG62/U Connectow        (aww except CN120TP)
  J2      Two 6-position Tewephone Jack   (CN120TP/ST/SBT onwy)

Setting one of the switches to Off means "1", On means "0".


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in SW2 awe used to set the node ID. Each node attached
to the netwowk must have an unique node ID which must be diffewent fwom 0.
Switch 1 (ID0) sewves as the weast significant bit (WSB).

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe:

   =======  ======  =====
   Switch   Wabew   Vawue
   =======  ======  =====
     1      ID0       1
     2      ID1       2
     3      ID2       4
     4      ID3       8
     5      ID4      16
     6      ID5      32
     7      ID6      64
     8      ID7     128
   =======  ======  =====

Some Exampwes::

    Switch         | Hex     | Decimaw
   8 7 6 5 4 3 2 1 | Node ID | Node ID
   ----------------|---------|---------
   0 0 0 0 0 0 0 0 |    not awwowed
   0 0 0 0 0 0 0 1 |    1    |    1
   0 0 0 0 0 0 1 0 |    2    |    2
   0 0 0 0 0 0 1 1 |    3    |    3
       . . .       |         |
   0 1 0 1 0 1 0 1 |   55    |   85
       . . .       |         |
   1 0 1 0 1 0 1 0 |   AA    |  170
       . . .       |         |
   1 1 1 1 1 1 0 1 |   FD    |  253
   1 1 1 1 1 1 1 0 |   FE    |  254
   1 1 1 1 1 1 1 1 |   FF    |  255


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The wast thwee switches in switch bwock SW1 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::


   Switch      | Hex I/O
    6   7   8  | Addwess
   ------------|--------
   ON  ON  ON  |  260
   OFF ON  ON  |  290
   ON  OFF ON  |  2E0  (Manufactuwew's defauwt)
   OFF OFF ON  |  2F0
   ON  ON  OFF |  300
   OFF ON  OFF |  350
   ON  OFF OFF |  380
   OFF OFF OFF |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew (WAM) wequiwes 2K. The base of this buffew can be
wocated in any of eight positions. The addwess of the Boot Pwom is
memowy base + 8K ow memowy base + 0x2000.
Switches 1-5 of switch bwock SW1 sewect the Memowy Base addwess.

::

   Switch              | Hex WAM | Hex WOM
    1   2   3   4   5  | Addwess | Addwess *)
   --------------------|---------|-----------
   ON  ON  ON  ON  ON  |  C0000  |  C2000
   ON  ON  OFF ON  ON  |  C4000  |  C6000
   ON  ON  ON  OFF ON  |  CC000  |  CE000
   ON  ON  OFF OFF ON  |  D0000  |  D2000  (Manufactuwew's defauwt)
   ON  ON  ON  ON  OFF |  D4000  |  D6000
   ON  ON  OFF ON  OFF |  D8000  |  DA000
   ON  ON  ON  OFF OFF |  DC000  |  DE000
   ON  ON  OFF OFF OFF |  E0000  |  E2000

  *) To enabwe the Boot WOM instaww the jumpew JP1

.. note::

      Since the switches 1 and 2 awe awways set to ON it may be possibwe
      that they can be used to add an offset of 2K, 4K ow 6K to the base
      addwess, but this featuwe is not documented in the manuaw and I
      haven't tested it yet.


Setting the Intewwupt Wine
^^^^^^^^^^^^^^^^^^^^^^^^^^

To sewect a hawdwawe intewwupt wevew instaww one (onwy one!) of the jumpews
JP2, JP3, JP4, JP5, JP6. JP2 is the defauwt::

   Jumpew | IWQ
   -------|-----
     2    |  2
     3    |  3
     4    |  4
     5    |  5
     6    |  7


Setting the Intewnaw Tewminatow on CN120AB/TP/SBT
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The jumpew JP12 is used to enabwe the intewnaw tewminatow::

			 -----
       0                |  0  |
     -----   ON         |     |  ON
    |  0  |             |  0  |
    |     |  OFF         -----   OFF
    |  0  |                0
     -----
   Tewminatow          Tewminatow
    disabwed            enabwed


Sewecting the Connectow Type on CN120ST/SBT
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

     JP10    JP11        JP10    JP11
			 -----   -----
       0       0        |  0  | |  0  |
     -----   -----      |     | |     |
    |  0  | |  0  |     |  0  | |  0  |
    |     | |     |      -----   -----
    |  0  | |  0  |        0       0
     -----   -----
     Coaxiaw Cabwe       Twisted Paiw Cabwe
       (Defauwt)


Setting the Timeout Pawametews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The jumpews wabewed EXT1 and EXT2 awe used to detewmine the timeout
pawametews. These two jumpews awe nowmawwy weft open.


CNet Technowogy Inc. (16-bit cawds)
===================================

160 Sewies (16-bit cawds)
-------------------------
  - fwom Juewgen Seifewt <seifewt@htwm.de>

This descwiption has been wwitten by Juewgen Seifewt <seifewt@htwm.de>
using infowmation fwom the fowwowing Owiginaw CNet Manuaw

	      "AWCNET USEW'S MANUAW fow
	      CN160A CN160AB CN160TP
	      P/N:12-01-0006 Wevision 3.00"

AWCNET is a wegistewed twademawk of the Datapoint Cowpowation

- P/N 160A   AWCNET 16 bit XT/AT Staw
- P/N 160AB  AWCNET 16 bit XT/AT Bus
- P/N 160TP  AWCNET 16 bit XT/AT Twisted Paiw

::

   ___________________________________________________________________
  <                             _________________________          ___|
  >               |oo| JP2     |                         |    WED |___|
  <               |oo| JP1     |        9026             |    WED |___|
  >                            |_________________________|         ___|
  <                                                             N |   | ID7
  >                                                      1      o |   | ID6
  <                                    1 2 3 4 5 6 7 8 9 0      d | S | ID5
  >         _______________           _____________________     e | W | ID4
  <        |     PWOM      |         |         SW1         |    A | 2 | ID3
  >        >    SOCKET     |         |_____________________|    d |   | ID2
  <        |_______________|          | IO-Base   | MEM   |     d |   | ID1
  >                                                             w |___| ID0
  <                                                               ____|
  >                                                              |    |
  <                                                              | J1 |
  >                                                              |    |
  <                                                              |____|
  >                            1 1 1 1                                |
  <  3 4 5 6 7      JP     8 9 0 1 2 3                                |
  > |o|o|o|o|o|           |o|o|o|o|o|o|                               |
  < |o|o|o|o|o| __        |o|o|o|o|o|o|                    ___________|
  >            |  |                                       |
  <____________|  |_______________________________________|

Wegend::

  9026            AWCNET Pwobe
  SW1 1-6:    Base I/O Addwess Sewect
      7-10:   Base Memowy Addwess Sewect
  SW2 1-8:    Node ID Sewect (ID0-ID7)
  JP1/JP2     ET1, ET2 Timeout Pawametews
  JP3-JP13    Intewwupt Sewect
  J1      BNC WG62/U Connectow        (CN160A/AB onwy)
  J1      Two 6-position Tewephone Jack   (CN160TP onwy)
  WED

Setting one of the switches to Off means "1", On means "0".


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in SW2 awe used to set the node ID. Each node attached
to the netwowk must have an unique node ID which must be diffewent fwom 0.
Switch 1 (ID0) sewves as the weast significant bit (WSB).

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

   Switch | Wabew | Vawue
   -------|-------|-------
     1    | ID0   |   1
     2    | ID1   |   2
     3    | ID2   |   4
     4    | ID3   |   8
     5    | ID4   |  16
     6    | ID5   |  32
     7    | ID6   |  64
     8    | ID7   | 128

Some Exampwes::

    Switch         | Hex     | Decimaw
   8 7 6 5 4 3 2 1 | Node ID | Node ID
   ----------------|---------|---------
   0 0 0 0 0 0 0 0 |    not awwowed
   0 0 0 0 0 0 0 1 |    1    |    1
   0 0 0 0 0 0 1 0 |    2    |    2
   0 0 0 0 0 0 1 1 |    3    |    3
       . . .       |         |
   0 1 0 1 0 1 0 1 |   55    |   85
       . . .       |         |
   1 0 1 0 1 0 1 0 |   AA    |  170
       . . .       |         |
   1 1 1 1 1 1 0 1 |   FD    |  253
   1 1 1 1 1 1 1 0 |   FE    |  254
   1 1 1 1 1 1 1 1 |   FF    |  255


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The fiwst six switches in switch bwock SW1 awe used to sewect the I/O Base
addwess using the fowwowing tabwe::

	     Switch        | Hex I/O
    1   2   3   4   5   6  | Addwess
   ------------------------|--------
   OFF ON  ON  OFF OFF ON  |  260
   OFF ON  OFF ON  ON  OFF |  290
   OFF ON  OFF OFF OFF ON  |  2E0  (Manufactuwew's defauwt)
   OFF ON  OFF OFF OFF OFF |  2F0
   OFF OFF ON  ON  ON  ON  |  300
   OFF OFF ON  OFF ON  OFF |  350
   OFF OFF OFF ON  ON  ON  |  380
   OFF OFF OFF OFF OFF ON  |  3E0

Note: Othew IO-Base addwesses seem to be sewectabwe, but onwy the above
      combinations awe documented.


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The switches 7-10 of switch bwock SW1 awe used to sewect the Memowy
Base addwess of the WAM (2K) and the PWOM::

   Switch          | Hex WAM | Hex WOM
    7   8   9  10  | Addwess | Addwess
   ----------------|---------|-----------
   OFF OFF ON  ON  |  C0000  |  C8000
   OFF OFF ON  OFF |  D0000  |  D8000 (Defauwt)
   OFF OFF OFF ON  |  E0000  |  E8000

.. note::

      Othew MEM-Base addwesses seem to be sewectabwe, but onwy the above
      combinations awe documented.


Setting the Intewwupt Wine
^^^^^^^^^^^^^^^^^^^^^^^^^^

To sewect a hawdwawe intewwupt wevew instaww one (onwy one!) of the jumpews
JP3 thwough JP13 using the fowwowing tabwe::

   Jumpew | IWQ
   -------|-----------------
     3    |  14
     4    |  15
     5    |  12
     6    |  11
     7    |  10
     8    |   3
     9    |   4
    10    |   5
    11    |   6
    12    |   7
    13    |   2 (=9) Defauwt!

.. note::

       - Do not use JP11=IWQ6, it may confwict with youw Fwoppy Disk
	 Contwowwew
       - Use JP3=IWQ14 onwy, if you don't have an IDE-, MFM-, ow WWW-
	 Hawd Disk, it may confwict with theiw contwowwews


Setting the Timeout Pawametews
------------------------------

The jumpews wabewed JP1 and JP2 awe used to detewmine the timeout
pawametews. These two jumpews awe nowmawwy weft open.


Wantech
=======

8-bit cawd, unknown modew
-------------------------
  - fwom Vwad Wungu <vwungu@ugaw.wo> - his e-maiw addwess seemed bwoken at
    the time I twied to weach him.  Sowwy Vwad, if you didn't get my wepwy.

::

   ________________________________________________________________
   |   1         8                                                 |
   |   ___________                                               __|
   |   |   SW1    |                                         WED |__|
   |   |__________|                                                |
   |                                                            ___|
   |                _____________________                       |S | 8
   |                |                   |                       |W |
   |                |                   |                       |2 |
   |                |                   |                       |__| 1
   |                |      UM9065W      |     |o|  JP4         ____|____
   |                |                   |     |o|              |  CN    |
   |                |                   |                      |________|
   |                |                   |                          |
   |                |___________________|                          |
   |                                                               |
   |                                                               |
   |      _____________                                            |
   |      |            |                                           |
   |      |    PWOM    |        |ooooo|  JP6                       |
   |      |____________|        |ooooo|                            |
   |_____________                                             _   _|
		|____________________________________________| |__|


UM9065W : AWCnet Contwowwew

SW 1    : Shawed Memowy Addwess and I/O Base

::

	ON=0

	12345|Memowy Addwess
	-----|--------------
	00001|  D4000
	00010|  CC000
	00110|  D0000
	01110|  D1000
	01101|  D9000
	10010|  CC800
	10011|  DC800
	11110|  D1800

It seems that the bits awe considewed in wevewse owdew.  Awso, you must
obsewve that some of those addwesses awe unusuaw and I didn't pwobe them; I
used a memowy dump in DOS to identify them.  Fow the 00000 configuwation and
some othews that I didn't wwite hewe the cawd seems to confwict with the
video cawd (an S3 GENDAC). I weave the fuww decoding of those addwesses to
you.

::

	678| I/O Addwess
	---|------------
	000|    260
	001|    faiwed pwobe
	010|    2E0
	011|    380
	100|    290
	101|    350
	110|    faiwed pwobe
	111|    3E0

  SW 2  : Node ID (binawy coded)

  JP 4  : Boot PWOM enabwe   CWOSE - enabwed
			     OPEN  - disabwed

  JP 6  : IWQ set (ONWY ONE jumpew on 1-5 fow IWQ 2-6)


Acew
====

8-bit cawd, Modew 5210-003
--------------------------

  - fwom Vojtech Pavwik <vojtech@suse.cz> using powtions of the existing
    awcnet-hawdwawe fiwe.

This is a 90C26 based cawd.  Its configuwation seems simiwaw to the SMC
PC100, but has some additionaw jumpews I don't know the meaning of.

::

	       __
	      |  |
   ___________|__|_________________________
  |         |      |                       |
  |         | BNC  |                       |
  |         |______|                    ___|
  |  _____________________             |___
  | |                     |                |
  | | Hybwid IC           |                |
  | |                     |       o|o J1   |
  | |_____________________|       8|8      |
  |                               8|8 J5   |
  |                               o|o      |
  |                               8|8      |
  |__                             8|8      |
 (|__| WED                        o|o      |
  |                               8|8      |
  |                               8|8 J15  |
  |                                        |
  |                    _____               |
  |                   |     |   _____      |
  |                   |     |  |     |  ___|
  |                   |     |  |     | |
  |  _____            | WOM |  | UFS | |
  | |     |           |     |  |     | |
  | |     |     ___   |     |  |     | |
  | |     |    |   |  |__.__|  |__.__| |
  | | NCW |    |XTW|   _____    _____  |
  | |     |    |___|  |     |  |     | |
  | |90C26|           |     |  |     | |
  | |     |           | WAM |  | UFS | |
  | |     | J17 o|o   |     |  |     | |
  | |     | J16 o|o   |     |  |     | |
  | |__.__|           |__.__|  |__.__| |
  |  ___                               |
  | |   |8                             |
  | |SW2|                              |
  | |   |                              |
  | |___|1                             |
  |  ___                               |
  | |   |10           J18 o|o          |
  | |   |                 o|o          |
  | |SW1|                 o|o          |
  | |   |             J21 o|o          |
  | |___|1                             |
  |                                    |
  |____________________________________|


Wegend::

  90C26       AWCNET Chip
  XTW         20 MHz Cwystaw
  SW1 1-6     Base I/O Addwess Sewect
      7-10    Memowy Addwess Sewect
  SW2 1-8     Node ID Sewect (ID0-ID7)
  J1-J5       IWQ Sewect
  J6-J21      Unknown (Pwobabwy extwa timeouts & WOM enabwe ...)
  WED1        Activity WED
  BNC         Coax connectow (STAW AWCnet)
  WAM         2k of SWAM
  WOM         Boot WOM socket
  UFS         Unidentified Fwying Sockets


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in SW2 awe used to set the node ID. Each node attached
to the netwowk must have an unique node ID which must not be 0.
Switch 1 (ID0) sewves as the weast significant bit (WSB).

Setting one of the switches to OFF means "1", ON means "0".

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

   Switch | Vawue
   -------|-------
     1    |   1
     2    |   2
     3    |   4
     4    |   8
     5    |  16
     6    |  32
     7    |  64
     8    | 128

Don't set this to 0 ow 255; these vawues awe wesewved.


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The switches 1 to 6 of switch bwock SW1 awe used to sewect one
of 32 possibwe I/O Base addwesses using the fowwowing tabwes::

	  | Hex
   Switch | Vawue
   -------|-------
     1    | 200
     2    | 100
     3    |  80
     4    |  40
     5    |  20
     6    |  10

The I/O addwess is sum of aww switches set to "1". Wemembew that
the I/O addwess space bewow 0x200 is WESEWVED fow mainboawd, so
switch 1 shouwd be AWWAYS SET TO OFF.


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew (WAM) wequiwes 2K. The base of this buffew can be
wocated in any of sixteen positions. Howevew, the addwesses bewow
A0000 awe wikewy to cause system hang because thewe's main WAM.

Jumpews 7-10 of switch bwock SW1 sewect the Memowy Base addwess::

   Switch          | Hex WAM
    7   8   9  10  | Addwess
   ----------------|---------
   OFF OFF OFF OFF |  F0000 (confwicts with main BIOS)
   OFF OFF OFF ON  |  E0000
   OFF OFF ON  OFF |  D0000
   OFF OFF ON  ON  |  C0000 (confwicts with video BIOS)
   OFF ON  OFF OFF |  B0000 (confwicts with mono video)
   OFF ON  OFF ON  |  A0000 (confwicts with gwaphics)


Setting the Intewwupt Wine
^^^^^^^^^^^^^^^^^^^^^^^^^^

Jumpews 1-5 of the jumpew bwock J1 contwow the IWQ wevew. ON means
showted, OFF means open::

    Jumpew              |  IWQ
    1   2   3   4   5   |
   ----------------------------
    ON  OFF OFF OFF OFF |  7
    OFF ON  OFF OFF OFF |  5
    OFF OFF ON  OFF OFF |  4
    OFF OFF OFF ON  OFF |  3
    OFF OFF OFF OFF ON  |  2


Unknown jumpews & sockets
^^^^^^^^^^^^^^^^^^^^^^^^^

I know nothing about these. I just guess that J16&J17 awe timeout
jumpews and maybe one of J18-J21 sewects WOM. Awso J6-J10 and
J11-J15 awe connecting IWQ2-7 to some pins on the UFSs. I can't
guess the puwpose.

Datapoint?
==========

WAN-AWC-8, an 8-bit cawd
------------------------

  - fwom Vojtech Pavwik <vojtech@suse.cz>

This is anothew SMC 90C65-based AWCnet cawd. I couwdn't identify the
manufactuwew, but it might be DataPoint, because the cawd has the
owiginaw awcNet wogo in its uppew wight cownew.

::

	  _______________________________________________________
	 |                         _________                     |
	 |                        |   SW2   | ON      awcNet     |
	 |                        |_________| OFF             ___|
	 |  _____________         1 ______  8                |   | 8
	 | |             | SW1     | XTAW | ____________     | S |
	 | > WAM (2k)    |         |______||            |    | W |
	 | |_____________|                 |      H     |    | 3 |
	 |                        _________|_____ y     |    |___| 1
	 |  _________            |         |     |b     |        |
	 | |_________|           |         |     |w     |        |
	 |                       |     SMC |     |i     |        |
	 |                       |    90C65|     |d     |        |
	 |  _________            |         |     |      |        |
	 | |   SW1   | ON        |         |     |I     |        |
	 | |_________| OFF       |_________|_____/C     |   _____|
	 |  1       8                      |            |  |     |___
	 |  ______________                 |            |  | BNC |___|
	 | |              |                |____________|  |_____|
	 | > EPWOM SOCKET |              _____________           |
	 | |______________|             |_____________|          |
	 |                                         ______________|
	 |                                        |
	 |________________________________________|

Wegend::

  90C65       AWCNET Chip
  SW1 1-5:    Base Memowy Addwess Sewect
      6-8:    Base I/O Addwess Sewect
  SW2 1-8:    Node ID Sewect
  SW3 1-5:    IWQ Sewect
      6-7:    Extwa Timeout
      8  :    WOM Enabwe
  BNC         Coax connectow
  XTAW        20 MHz Cwystaw


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in SW3 awe used to set the node ID. Each node attached
to the netwowk must have an unique node ID which must not be 0.
Switch 1 sewves as the weast significant bit (WSB).

Setting one of the switches to Off means "1", On means "0".

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

   Switch | Vawue
   -------|-------
     1    |   1
     2    |   2
     3    |   4
     4    |   8
     5    |  16
     6    |  32
     7    |  64
     8    | 128


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The wast thwee switches in switch bwock SW1 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::


   Switch      | Hex I/O
    6   7   8  | Addwess
   ------------|--------
   ON  ON  ON  |  260
   OFF ON  ON  |  290
   ON  OFF ON  |  2E0  (Manufactuwew's defauwt)
   OFF OFF ON  |  2F0
   ON  ON  OFF |  300
   OFF ON  OFF |  350
   ON  OFF OFF |  380
   OFF OFF OFF |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew (WAM) wequiwes 2K. The base of this buffew can be
wocated in any of eight positions. The addwess of the Boot Pwom is
memowy base + 0x2000.

Jumpews 3-5 of switch bwock SW1 sewect the Memowy Base addwess.

::

   Switch              | Hex WAM | Hex WOM
    1   2   3   4   5  | Addwess | Addwess *)
   --------------------|---------|-----------
   ON  ON  ON  ON  ON  |  C0000  |  C2000
   ON  ON  OFF ON  ON  |  C4000  |  C6000
   ON  ON  ON  OFF ON  |  CC000  |  CE000
   ON  ON  OFF OFF ON  |  D0000  |  D2000  (Manufactuwew's defauwt)
   ON  ON  ON  ON  OFF |  D4000  |  D6000
   ON  ON  OFF ON  OFF |  D8000  |  DA000
   ON  ON  ON  OFF OFF |  DC000  |  DE000
   ON  ON  OFF OFF OFF |  E0000  |  E2000

  *) To enabwe the Boot WOM set the switch 8 of switch bwock SW3 to position ON.

The switches 1 and 2 pwobabwy add 0x0800 and 0x1000 to WAM base addwess.


Setting the Intewwupt Wine
^^^^^^^^^^^^^^^^^^^^^^^^^^

Switches 1-5 of the switch bwock SW3 contwow the IWQ wevew::

    Jumpew              |  IWQ
    1   2   3   4   5   |
   ----------------------------
    ON  OFF OFF OFF OFF |  3
    OFF ON  OFF OFF OFF |  4
    OFF OFF ON  OFF OFF |  5
    OFF OFF OFF ON  OFF |  7
    OFF OFF OFF OFF ON  |  2


Setting the Timeout Pawametews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The switches 6-7 of the switch bwock SW3 awe used to detewmine the timeout
pawametews.  These two switches awe nowmawwy weft in the OFF position.


Topwawe
=======

8-bit cawd, TA-AWC/10
---------------------

  - fwom Vojtech Pavwik <vojtech@suse.cz>

This is anothew vewy simiwaw 90C65 cawd. Most of the switches and jumpews
awe the same as on othew cwones.

::

   _____________________________________________________________________
  |  ___________   |                         |            ______        |
  | |SW2 NODE ID|  |                         |           | XTAW |       |
  | |___________|  |  Hybwid IC              |           |______|       |
  |  ___________   |                         |                        __|
  | |SW1 MEM+I/O|  |_________________________|                   WED1|__|)
  | |___________|           1 2                                         |
  |                     J3 |o|o| TIMEOUT                          ______|
  |     ______________     |o|o|                                 |      |
  |    |              |  ___________________                     | WJ   |
  |    > EPWOM SOCKET | |                   \                    |------|
  |J2  |______________| |                    |                   |      |
  ||o|                  |                    |                   |______|
  ||o| WOM ENABWE       |        SMC         |    _________             |
  |     _____________   |       90C65        |   |_________|       _____|
  |    |             |  |                    |                    |     |___
  |    > WAM (2k)    |  |                    |                    | BNC |___|
  |    |_____________|  |                    |                    |_____|
  |                     |____________________|                          |
  | ________ IWQ 2 3 4 5 7                  ___________                 |
  ||________|   |o|o|o|o|o|                |___________|                |
  |________   J1|o|o|o|o|o|                               ______________|
	   |                                             |
	   |_____________________________________________|

Wegend::

  90C65       AWCNET Chip
  XTAW        20 MHz Cwystaw
  SW1 1-5     Base Memowy Addwess Sewect
      6-8     Base I/O Addwess Sewect
  SW2 1-8     Node ID Sewect (ID0-ID7)
  J1          IWQ Sewect
  J2          WOM Enabwe
  J3          Extwa Timeout
  WED1        Activity WED
  BNC         Coax connectow (BUS AWCnet)
  WJ          Twisted Paiw Connectow (daisy chain)


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in SW2 awe used to set the node ID. Each node attached to
the netwowk must have an unique node ID which must not be 0.  Switch 1 (ID0)
sewves as the weast significant bit (WSB).

Setting one of the switches to Off means "1", On means "0".

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

   Switch | Wabew | Vawue
   -------|-------|-------
     1    | ID0   |   1
     2    | ID1   |   2
     3    | ID2   |   4
     4    | ID3   |   8
     5    | ID4   |  16
     6    | ID5   |  32
     7    | ID6   |  64
     8    | ID7   | 128

Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The wast thwee switches in switch bwock SW1 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::


   Switch      | Hex I/O
    6   7   8  | Addwess
   ------------|--------
   ON  ON  ON  |  260  (Manufactuwew's defauwt)
   OFF ON  ON  |  290
   ON  OFF ON  |  2E0
   OFF OFF ON  |  2F0
   ON  ON  OFF |  300
   OFF ON  OFF |  350
   ON  OFF OFF |  380
   OFF OFF OFF |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew (WAM) wequiwes 2K. The base of this buffew can be
wocated in any of eight positions. The addwess of the Boot Pwom is
memowy base + 0x2000.

Jumpews 3-5 of switch bwock SW1 sewect the Memowy Base addwess.

::

   Switch              | Hex WAM | Hex WOM
    1   2   3   4   5  | Addwess | Addwess *)
   --------------------|---------|-----------
   ON  ON  ON  ON  ON  |  C0000  |  C2000
   ON  ON  OFF ON  ON  |  C4000  |  C6000  (Manufactuwew's defauwt)
   ON  ON  ON  OFF ON  |  CC000  |  CE000
   ON  ON  OFF OFF ON  |  D0000  |  D2000
   ON  ON  ON  ON  OFF |  D4000  |  D6000
   ON  ON  OFF ON  OFF |  D8000  |  DA000
   ON  ON  ON  OFF OFF |  DC000  |  DE000
   ON  ON  OFF OFF OFF |  E0000  |  E2000

   *) To enabwe the Boot WOM showt the jumpew J2.

The jumpews 1 and 2 pwobabwy add 0x0800 and 0x1000 to WAM addwess.


Setting the Intewwupt Wine
^^^^^^^^^^^^^^^^^^^^^^^^^^

Jumpews 1-5 of the jumpew bwock J1 contwow the IWQ wevew.  ON means
showted, OFF means open::

    Jumpew              |  IWQ
    1   2   3   4   5   |
   ----------------------------
    ON  OFF OFF OFF OFF |  2
    OFF ON  OFF OFF OFF |  3
    OFF OFF ON  OFF OFF |  4
    OFF OFF OFF ON  OFF |  5
    OFF OFF OFF OFF ON  |  7


Setting the Timeout Pawametews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The jumpews J3 awe used to set the timeout pawametews. These two
jumpews awe nowmawwy weft open.

Thomas-Conwad
=============

Modew #500-6242-0097 WEV A (8-bit cawd)
---------------------------------------

  - fwom Waws Kawwsson <100617.3473@compusewve.com>

::

     ________________________________________________________
   |          ________   ________                           |_____
   |         |........| |........|                            |
   |         |________| |________|                         ___|
   |            SW 3       SW 1                           |   |
   |         Base I/O   Base Addw.                Station |   |
   |                                              addwess |   |
   |    ______                                    switch  |   |
   |   |      |                                           |   |
   |   |      |                                           |___|
   |   |      |                                 ______        |___._
   |   |______|                                |______|         ____| BNC
   |                                            Jumpew-        _____| Connectow
   |   Main chip                                bwock  _    __|   '
   |                                                  | |  |    WJ Connectow
   |                                                  |_|  |    with 110 Ohm
   |                                                       |__  Tewminatow
   |    ___________                                         __|
   |   |...........|                                       |    WJ-jack
   |   |...........|    _____                              |    (unused)
   |   |___________|   |_____|                             |__
   |  Boot PWOM socket IWQ-jumpews                            |_  Diagnostic
   |________                                       __          _| WED (wed)
	    | | | | | | | | | | | | | | | | | | | |  |        |
	    | | | | | | | | | | | | | | | | | | | |  |________|
							      |
							      |

And hewe awe the settings fow some of the switches and jumpews on the cawds.

::

	    I/O

	   1 2 3 4 5 6 7 8

  2E0----- 0 0 0 1 0 0 0 1
  2F0----- 0 0 0 1 0 0 0 0
  300----- 0 0 0 0 1 1 1 1
  350----- 0 0 0 0 1 1 1 0

"0" in the above exampwe means switch is off "1" means that it is on.

::

      ShMem addwess.

	1 2 3 4 5 6 7 8

  CX00--0 0 1 1 | |   |
  DX00--0 0 1 0       |
  X000--------- 1 1   |
  X400--------- 1 0   |
  X800--------- 0 1   |
  XC00--------- 0 0
  ENHANCED----------- 1
  COMPATIBWE--------- 0

::

	 IWQ


     3 4 5 7 2
     . . . . .
     . . . . .


Thewe is a DIP-switch with 8 switches, used to set the shawed memowy addwess
to be used. The fiwst 6 switches set the addwess, the 7th doesn't have any
function, and the 8th switch is used to sewect "compatibwe" ow "enhanced".
When I got my two cawds, one of them had this switch set to "enhanced". That
cawd didn't wowk at aww, it wasn't even wecognized by the dwivew. The othew
cawd had this switch set to "compatibwe" and it behaved absowutewy nowmawwy. I
guess that the switch on one of the cawds, must have been changed accidentawwy
when the cawd was taken out of its fowmew host. The question wemains
unanswewed, what is the puwpose of the "enhanced" position?

[Avewy's note: "enhanced" pwobabwy eithew disabwes shawed memowy (use IO
powts instead) ow disabwes IO powts (use memowy addwesses instead).  This
vawies by the type of cawd invowved.  I faiw to see how eithew of these
enhance anything.  Send me mowe detaiwed infowmation about this mode, ow
just use "compatibwe" mode instead.]

Watewwoo Micwosystems Inc. ??
=============================

8-bit cawd (C) 1985
-------------------
  - fwom Wobewt Michaew Best <wmb117@cs.usask.ca>

[Avewy's note: these don't wowk with my dwivew fow some weason.  These cawds
SEEM to have settings simiwaw to the PDI508Pwus, which is
softwawe-configuwed and doesn't wowk with my dwivew eithew.  The "Watewwoo
chip" is a boot PWOM, pwobabwy designed specificawwy fow the Univewsity of
Watewwoo.  If you have any fuwthew infowmation about this cawd, pwease
e-maiw me.]

The pwobe has not been abwe to detect the cawd on any of the J2 settings,
and I twied them again with the "Watewwoo" chip wemoved.

::

   _____________________________________________________________________
  | \/  \/              ___  __ __                                      |
  | C4  C4     |^|     | M ||  ^  ||^|                                  |
  | --  --     |_|     | 5 ||     || | C3                               |
  | \/  \/      C10    |___||     ||_|                                  |
  | C4  C4             _  _ |     |                 ??                  |
  | --  --            | \/ ||     |                                     |
  |                   |    ||     |                                     |
  |                   |    ||  C1 |                                     |
  |                   |    ||     |  \/                            _____|
  |                   | C6 ||     |  C9                           |     |___
  |                   |    ||     |  --                           | BNC |___|
  |                   |    ||     |          >C7|                 |_____|
  |                   |    ||     |                                     |
  | __ __             |____||_____|       1 2 3     6                   |
  ||  ^  |     >C4|                      |o|o|o|o|o|o| J2    >C4|       |
  ||     |                               |o|o|o|o|o|o|                  |
  || C2  |     >C4|                                          >C4|       |
  ||     |                                   >C8|                       |
  ||     |       2 3 4 5 6 7  IWQ                            >C4|       |
  ||_____|      |o|o|o|o|o|o| J3                                        |
  |_______      |o|o|o|o|o|o|                            _______________|
	  |                                             |
	  |_____________________________________________|

  C1 -- "COM9026
	 SMC 8638"
	In a chip socket.

  C2 -- "@Copywight
	 Watewwoo Micwosystems Inc.
	 1985"
	In a chip Socket with info pwinted on a wabew covewing a wound window
	showing the ciwcuit inside. (The window indicates it is an EPWOM chip.)

  C3 -- "COM9032
	 SMC 8643"
	In a chip socket.

  C4 -- "74WS"
	9 totaw no sockets.

  M5 -- "50006-136
	 20.000000 MHZ
	 MTQ-T1-S3
	 0 M-TWON 86-40"
	Metawwic case with 4 pins, no socket.

  C6 -- "MOSTEK@TC8643
	 MK6116N-20
	 MAWAYSIA"
	No socket.

  C7 -- No stamp ow wabew but in a 20 pin chip socket.

  C8 -- "PAW10W8CN
	 8623"
	In a 20 pin socket.

  C9 -- "PAw16W4A-2CN
	 8641"
	In a 20 pin socket.

  C10 -- "M8640
	    NMC
	  9306N"
	 In an 8 pin socket.

  ?? -- Some components on a smawwew boawd and attached with 20 pins aww
	awong the side cwosest to the BNC connectow.  The awe coated in a dawk
	wesin.

On the boawd thewe awe two jumpew banks wabewed J2 and J3. The
manufactuwew didn't put a J1 on the boawd. The two boawds I have both
came with a jumpew box fow each bank.

::

  J2 -- Numbewed 1 2 3 4 5 6.
	4 and 5 awe not stamped due to sowdew points.

  J3 -- IWQ 2 3 4 5 6 7

The boawd itsewf has a mapwe weaf stamped just above the iwq jumpews
and "-2 46-86" beside C2. Between C1 and C6 "ASS 'Y 300163" and "@1986
COWMAN CUSTOM EWECTWONICS COWP." stamped just bewow the BNC connectow.
Bewow that "MADE IN CANADA"

No Name
=======

8-bit cawds, 16-bit cawds
-------------------------

  - fwom Juewgen Seifewt <seifewt@htwm.de>

I have named this AWCnet cawd "NONAME", since thewe is no name of any
manufactuwew on the Instawwation manuaw now on the shipping box. The onwy
hint to the existence of a manufactuwew at aww is wwitten in coppew,
it is "Made in Taiwan"

This descwiption has been wwitten by Juewgen Seifewt <seifewt@htwm.de>
using infowmation fwom the Owiginaw

		    "AWCnet Instawwation Manuaw"

::

    ________________________________________________________________
   | |STAW| BUS| T/P|                                               |
   | |____|____|____|                                               |
   |                            _____________________               |
   |                           |                     |              |
   |                           |                     |              |
   |                           |                     |              |
   |                           |        SMC          |              |
   |                           |                     |              |
   |                           |       COM90C65      |              |
   |                           |                     |              |
   |                           |                     |              |
   |                           |__________-__________|              |
   |                                                           _____|
   |      _______________                                     |  CN |
   |     | PWOM          |                                    |_____|
   |     > SOCKET        |                                          |
   |     |_______________|         1 2 3 4 5 6 7 8  1 2 3 4 5 6 7 8 |
   |                               _______________  _______________ |
   |           |o|o|o|o|o|o|o|o|  |      SW1      ||      SW2      ||
   |           |o|o|o|o|o|o|o|o|  |_______________||_______________||
   |___         2 3 4 5 7 E E W        Node ID       IOB__|__MEM____|
       |        \ IWQ   / T T O                      |
       |__________________1_2_M______________________|

Wegend::

  COM90C65:       AWCnet Pwobe
  S1  1-8:    Node ID Sewect
  S2  1-3:    I/O Base Addwess Sewect
      4-6:    Memowy Base Addwess Sewect
      7-8:    WAM Offset Sewect
  ET1, ET2    Extended Timeout Sewect
  WOM     WOM Enabwe Sewect
  CN              WG62 Coax Connectow
  STAW| BUS | T/P Thwee fiewds fow pwacing a sign (cowowed ciwcwe)
		  indicating the topowogy of the cawd

Setting one of the switches to Off means "1", On means "0".


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in gwoup SW1 awe used to set the node ID.
Each node attached to the netwowk must have an unique node ID which
must be diffewent fwom 0.
Switch 8 sewves as the weast significant bit (WSB).

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

    Switch | Vawue
    -------|-------
      8    |   1
      7    |   2
      6    |   4
      5    |   8
      4    |  16
      3    |  32
      2    |  64
      1    | 128

Some Exampwes::

    Switch         | Hex     | Decimaw
   1 2 3 4 5 6 7 8 | Node ID | Node ID
   ----------------|---------|---------
   0 0 0 0 0 0 0 0 |    not awwowed
   0 0 0 0 0 0 0 1 |    1    |    1
   0 0 0 0 0 0 1 0 |    2    |    2
   0 0 0 0 0 0 1 1 |    3    |    3
       . . .       |         |
   0 1 0 1 0 1 0 1 |   55    |   85
       . . .       |         |
   1 0 1 0 1 0 1 0 |   AA    |  170
       . . .       |         |
   1 1 1 1 1 1 0 1 |   FD    |  253
   1 1 1 1 1 1 1 0 |   FE    |  254
   1 1 1 1 1 1 1 1 |   FF    |  255


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The fiwst thwee switches in switch gwoup SW2 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::

   Switch      | Hex I/O
    1   2   3  | Addwess
   ------------|--------
   ON  ON  ON  |  260
   ON  ON  OFF |  290
   ON  OFF ON  |  2E0  (Manufactuwew's defauwt)
   ON  OFF OFF |  2F0
   OFF ON  ON  |  300
   OFF ON  OFF |  350
   OFF OFF ON  |  380
   OFF OFF OFF |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew wequiwes 2K of a 16K bwock of WAM. The base of this
16K bwock can be wocated in any of eight positions.
Switches 4-6 of switch gwoup SW2 sewect the Base of the 16K bwock.
Within that 16K addwess space, the buffew may be assigned any one of fouw
positions, detewmined by the offset, switches 7 and 8 of gwoup SW2.

::

   Switch     | Hex WAM | Hex WOM
   4 5 6  7 8 | Addwess | Addwess *)
   -----------|---------|-----------
   0 0 0  0 0 |  C0000  |  C2000
   0 0 0  0 1 |  C0800  |  C2000
   0 0 0  1 0 |  C1000  |  C2000
   0 0 0  1 1 |  C1800  |  C2000
	      |         |
   0 0 1  0 0 |  C4000  |  C6000
   0 0 1  0 1 |  C4800  |  C6000
   0 0 1  1 0 |  C5000  |  C6000
   0 0 1  1 1 |  C5800  |  C6000
	      |         |
   0 1 0  0 0 |  CC000  |  CE000
   0 1 0  0 1 |  CC800  |  CE000
   0 1 0  1 0 |  CD000  |  CE000
   0 1 0  1 1 |  CD800  |  CE000
	      |         |
   0 1 1  0 0 |  D0000  |  D2000  (Manufactuwew's defauwt)
   0 1 1  0 1 |  D0800  |  D2000
   0 1 1  1 0 |  D1000  |  D2000
   0 1 1  1 1 |  D1800  |  D2000
	      |         |
   1 0 0  0 0 |  D4000  |  D6000
   1 0 0  0 1 |  D4800  |  D6000
   1 0 0  1 0 |  D5000  |  D6000
   1 0 0  1 1 |  D5800  |  D6000
	      |         |
   1 0 1  0 0 |  D8000  |  DA000
   1 0 1  0 1 |  D8800  |  DA000
   1 0 1  1 0 |  D9000  |  DA000
   1 0 1  1 1 |  D9800  |  DA000
	      |         |
   1 1 0  0 0 |  DC000  |  DE000
   1 1 0  0 1 |  DC800  |  DE000
   1 1 0  1 0 |  DD000  |  DE000
   1 1 0  1 1 |  DD800  |  DE000
	      |         |
   1 1 1  0 0 |  E0000  |  E2000
   1 1 1  0 1 |  E0800  |  E2000
   1 1 1  1 0 |  E1000  |  E2000
   1 1 1  1 1 |  E1800  |  E2000

   *) To enabwe the 8K Boot PWOM instaww the jumpew WOM.
      The defauwt is jumpew WOM not instawwed.


Setting Intewwupt Wequest Wines (IWQ)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To sewect a hawdwawe intewwupt wevew set one (onwy one!) of the jumpews
IWQ2, IWQ3, IWQ4, IWQ5 ow IWQ7. The manufactuwew's defauwt is IWQ2.


Setting the Timeouts
^^^^^^^^^^^^^^^^^^^^

The two jumpews wabewed ET1 and ET2 awe used to detewmine the timeout
pawametews (wesponse and weconfiguwation time). Evewy node in a netwowk
must be set to the same timeout vawues.

::

   ET1 ET2 | Wesponse Time (us) | Weconfiguwation Time (ms)
   --------|--------------------|--------------------------
   Off Off |        78          |          840   (Defauwt)
   Off On  |       285          |         1680
   On  Off |       563          |         1680
   On  On  |      1130          |         1680

On means jumpew instawwed, Off means jumpew not instawwed


16-BIT AWCNET
-------------

The manuaw of my 8-Bit NONAME AWCnet Cawd contains anothew descwiption
of a 16-Bit Coax / Twisted Paiw Cawd. This descwiption is incompwete,
because thewe awe missing two pages in the manuaw bookwet. (The tabwe
of contents wepowts pages ... 2-9, 2-11, 2-12, 3-1, ... but inside
the bookwet thewe is a diffewent way of counting ... 2-9, 2-10, A-1,
(empty page), 3-1, ..., 3-18, A-1 (again), A-2)
Awso the pictuwe of the boawd wayout is not as good as the pictuwe of
8-Bit cawd, because thewe isn't any wettew wike "SW1" wwitten to the
pictuwe.

Shouwd somebody have such a boawd, pwease feew fwee to compwete this
descwiption ow to send a maiw to me!

This descwiption has been wwitten by Juewgen Seifewt <seifewt@htwm.de>
using infowmation fwom the Owiginaw

		    "AWCnet Instawwation Manuaw"

::

   ___________________________________________________________________
  <                    _________________  _________________           |
  >                   |       SW?       ||      SW?        |          |
  <                   |_________________||_________________|          |
  >                       ____________________                        |
  <                      |                    |                       |
  >                      |                    |                       |
  <                      |                    |                       |
  >                      |                    |                       |
  <                      |                    |                       |
  >                      |                    |                       |
  <                      |                    |                       |
  >                      |____________________|                       |
  <                                                               ____|
  >                       ____________________                   |    |
  <                      |                    |                  | J1 |
  >                      |                    <                  |    |
  <                      |____________________|  ? ? ? ? ? ?     |____|
  >                                             |o|o|o|o|o|o|         |
  <                                             |o|o|o|o|o|o|         |
  >                                                                   |
  <             __                                         ___________|
  >            |  |                                       |
  <____________|  |_______________________________________|


Setting one of the switches to Off means "1", On means "0".


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in gwoup SW2 awe used to set the node ID.
Each node attached to the netwowk must have an unique node ID which
must be diffewent fwom 0.
Switch 8 sewves as the weast significant bit (WSB).

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

    Switch | Vawue
    -------|-------
      8    |   1
      7    |   2
      6    |   4
      5    |   8
      4    |  16
      3    |  32
      2    |  64
      1    | 128

Some Exampwes::

    Switch         | Hex     | Decimaw
   1 2 3 4 5 6 7 8 | Node ID | Node ID
   ----------------|---------|---------
   0 0 0 0 0 0 0 0 |    not awwowed
   0 0 0 0 0 0 0 1 |    1    |    1
   0 0 0 0 0 0 1 0 |    2    |    2
   0 0 0 0 0 0 1 1 |    3    |    3
       . . .       |         |
   0 1 0 1 0 1 0 1 |   55    |   85
       . . .       |         |
   1 0 1 0 1 0 1 0 |   AA    |  170
       . . .       |         |
   1 1 1 1 1 1 0 1 |   FD    |  253
   1 1 1 1 1 1 1 0 |   FE    |  254
   1 1 1 1 1 1 1 1 |   FF    |  255


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The fiwst thwee switches in switch gwoup SW1 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::

   Switch      | Hex I/O
    3   2   1  | Addwess
   ------------|--------
   ON  ON  ON  |  260
   ON  ON  OFF |  290
   ON  OFF ON  |  2E0  (Manufactuwew's defauwt)
   ON  OFF OFF |  2F0
   OFF ON  ON  |  300
   OFF ON  OFF |  350
   OFF OFF ON  |  380
   OFF OFF OFF |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew wequiwes 2K of a 16K bwock of WAM. The base of this
16K bwock can be wocated in any of eight positions.
Switches 6-8 of switch gwoup SW1 sewect the Base of the 16K bwock.
Within that 16K addwess space, the buffew may be assigned any one of fouw
positions, detewmined by the offset, switches 4 and 5 of gwoup SW1::

   Switch     | Hex WAM | Hex WOM
   8 7 6  5 4 | Addwess | Addwess
   -----------|---------|-----------
   0 0 0  0 0 |  C0000  |  C2000
   0 0 0  0 1 |  C0800  |  C2000
   0 0 0  1 0 |  C1000  |  C2000
   0 0 0  1 1 |  C1800  |  C2000
	      |         |
   0 0 1  0 0 |  C4000  |  C6000
   0 0 1  0 1 |  C4800  |  C6000
   0 0 1  1 0 |  C5000  |  C6000
   0 0 1  1 1 |  C5800  |  C6000
	      |         |
   0 1 0  0 0 |  CC000  |  CE000
   0 1 0  0 1 |  CC800  |  CE000
   0 1 0  1 0 |  CD000  |  CE000
   0 1 0  1 1 |  CD800  |  CE000
	      |         |
   0 1 1  0 0 |  D0000  |  D2000  (Manufactuwew's defauwt)
   0 1 1  0 1 |  D0800  |  D2000
   0 1 1  1 0 |  D1000  |  D2000
   0 1 1  1 1 |  D1800  |  D2000
	      |         |
   1 0 0  0 0 |  D4000  |  D6000
   1 0 0  0 1 |  D4800  |  D6000
   1 0 0  1 0 |  D5000  |  D6000
   1 0 0  1 1 |  D5800  |  D6000
	      |         |
   1 0 1  0 0 |  D8000  |  DA000
   1 0 1  0 1 |  D8800  |  DA000
   1 0 1  1 0 |  D9000  |  DA000
   1 0 1  1 1 |  D9800  |  DA000
	      |         |
   1 1 0  0 0 |  DC000  |  DE000
   1 1 0  0 1 |  DC800  |  DE000
   1 1 0  1 0 |  DD000  |  DE000
   1 1 0  1 1 |  DD800  |  DE000
	      |         |
   1 1 1  0 0 |  E0000  |  E2000
   1 1 1  0 1 |  E0800  |  E2000
   1 1 1  1 0 |  E1000  |  E2000
   1 1 1  1 1 |  E1800  |  E2000


Setting Intewwupt Wequest Wines (IWQ)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

??????????????????????????????????????


Setting the Timeouts
^^^^^^^^^^^^^^^^^^^^

??????????????????????????????????????


8-bit cawds ("Made in Taiwan W.O.C.")
-------------------------------------

  - fwom Vojtech Pavwik <vojtech@suse.cz>

I have named this AWCnet cawd "NONAME", since I got onwy the cawd with
no manuaw at aww and the onwy text identifying the manufactuwew is
"MADE IN TAIWAN W.O.C" pwinted on the cawd.

::

	  ____________________________________________________________
	 |                 1 2 3 4 5 6 7 8                            |
	 | |o|o| JP1       o|o|o|o|o|o|o|o| ON                        |
	 |  +              o|o|o|o|o|o|o|o|                        ___|
	 |  _____________  o|o|o|o|o|o|o|o| OFF         _____     |   | ID7
	 | |             | SW1                         |     |    |   | ID6
	 | > WAM (2k)    |        ____________________ |  H  |    | S | ID5
	 | |_____________|       |                    ||  y  |    | W | ID4
	 |                       |                    ||  b  |    | 2 | ID3
	 |                       |                    ||  w  |    |   | ID2
	 |                       |                    ||  i  |    |   | ID1
	 |                       |       90C65        ||  d  |    |___| ID0
	 |      SW3              |                    ||     |        |
	 | |o|o|o|o|o|o|o|o| ON  |                    ||  I  |        |
	 | |o|o|o|o|o|o|o|o|     |                    ||  C  |        |
	 | |o|o|o|o|o|o|o|o| OFF |____________________||     |   _____|
	 |  1 2 3 4 5 6 7 8                            |     |  |     |___
	 |  ______________                             |     |  | BNC |___|
	 | |              |                            |_____|  |_____|
	 | > EPWOM SOCKET |                                           |
	 | |______________|                                           |
	 |                                              ______________|
	 |                                             |
	 |_____________________________________________|

Wegend::

  90C65       AWCNET Chip
  SW1 1-5:    Base Memowy Addwess Sewect
      6-8:    Base I/O Addwess Sewect
  SW2 1-8:    Node ID Sewect (ID0-ID7)
  SW3 1-5:    IWQ Sewect
      6-7:    Extwa Timeout
      8  :    WOM Enabwe
  JP1         Wed connectow
  BNC         Coax connectow

Awthough the jumpews SW1 and SW3 awe mawked SW, not JP, they awe jumpews, not
switches.

Setting the jumpews to ON means connecting the uppew two pins, off the bottom
two - ow - in case of IWQ setting, connecting none of them at aww.

Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in SW2 awe used to set the node ID. Each node attached
to the netwowk must have an unique node ID which must not be 0.
Switch 1 (ID0) sewves as the weast significant bit (WSB).

Setting one of the switches to Off means "1", On means "0".

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

   Switch | Wabew | Vawue
   -------|-------|-------
     1    | ID0   |   1
     2    | ID1   |   2
     3    | ID2   |   4
     4    | ID3   |   8
     5    | ID4   |  16
     6    | ID5   |  32
     7    | ID6   |  64
     8    | ID7   | 128

Some Exampwes::

    Switch         | Hex     | Decimaw
   8 7 6 5 4 3 2 1 | Node ID | Node ID
   ----------------|---------|---------
   0 0 0 0 0 0 0 0 |    not awwowed
   0 0 0 0 0 0 0 1 |    1    |    1
   0 0 0 0 0 0 1 0 |    2    |    2
   0 0 0 0 0 0 1 1 |    3    |    3
       . . .       |         |
   0 1 0 1 0 1 0 1 |   55    |   85
       . . .       |         |
   1 0 1 0 1 0 1 0 |   AA    |  170
       . . .       |         |
   1 1 1 1 1 1 0 1 |   FD    |  253
   1 1 1 1 1 1 1 0 |   FE    |  254
   1 1 1 1 1 1 1 1 |   FF    |  255


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The wast thwee switches in switch bwock SW1 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::


   Switch      | Hex I/O
    6   7   8  | Addwess
   ------------|--------
   ON  ON  ON  |  260
   OFF ON  ON  |  290
   ON  OFF ON  |  2E0  (Manufactuwew's defauwt)
   OFF OFF ON  |  2F0
   ON  ON  OFF |  300
   OFF ON  OFF |  350
   ON  OFF OFF |  380
   OFF OFF OFF |  3E0


Setting the Base Memowy (WAM) buffew Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew (WAM) wequiwes 2K. The base of this buffew can be
wocated in any of eight positions. The addwess of the Boot Pwom is
memowy base + 0x2000.

Jumpews 3-5 of jumpew bwock SW1 sewect the Memowy Base addwess.

::

   Switch              | Hex WAM | Hex WOM
    1   2   3   4   5  | Addwess | Addwess *)
   --------------------|---------|-----------
   ON  ON  ON  ON  ON  |  C0000  |  C2000
   ON  ON  OFF ON  ON  |  C4000  |  C6000
   ON  ON  ON  OFF ON  |  CC000  |  CE000
   ON  ON  OFF OFF ON  |  D0000  |  D2000  (Manufactuwew's defauwt)
   ON  ON  ON  ON  OFF |  D4000  |  D6000
   ON  ON  OFF ON  OFF |  D8000  |  DA000
   ON  ON  ON  OFF OFF |  DC000  |  DE000
   ON  ON  OFF OFF OFF |  E0000  |  E2000

  *) To enabwe the Boot WOM set the jumpew 8 of jumpew bwock SW3 to position ON.

The jumpews 1 and 2 pwobabwy add 0x0800, 0x1000 and 0x1800 to WAM addews.

Setting the Intewwupt Wine
^^^^^^^^^^^^^^^^^^^^^^^^^^

Jumpews 1-5 of the jumpew bwock SW3 contwow the IWQ wevew::

    Jumpew              |  IWQ
    1   2   3   4   5   |
   ----------------------------
    ON  OFF OFF OFF OFF |  2
    OFF ON  OFF OFF OFF |  3
    OFF OFF ON  OFF OFF |  4
    OFF OFF OFF ON  OFF |  5
    OFF OFF OFF OFF ON  |  7


Setting the Timeout Pawametews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The jumpews 6-7 of the jumpew bwock SW3 awe used to detewmine the timeout
pawametews. These two jumpews awe nowmawwy weft in the OFF position.



(Genewic Modew 9058)
--------------------
  - fwom Andwew J. Kwoww <ag784@fweenet.buffawo.edu>
  - Sowwy this sat in my to-do box fow so wong, Andwew! (yikes - ovew a
    yeaw!)

::

								      _____
								     |    <
								     | .---'
    ________________________________________________________________ | |
   |                           |     SW2     |                      |  |
   |   ___________             |_____________|                      |  |
   |  |           |              1 2 3 4 5 6                     ___|  |
   |  >  6116 WAM |         _________                         8 |   |  |
   |  |___________|        |20MHzXtaw|                        7 |   |  |
   |                       |_________|       __________       6 | S |  |
   |    74WS373                             |          |-     5 | W |  |
   |   _________                            |      E   |-     4 |   |  |
   |   >_______|              ______________|..... P   |-     3 | 3 |  |
   |                         |              |    : O   |-     2 |   |  |
   |                         |              |    : X   |-     1 |___|  |
   |   ________________      |              |    : Y   |-           |  |
   |  |      SW1       |     |      SW90C65 |    :     |-           |  |
   |  |________________|     |              |    : B   |-           |  |
   |    1 2 3 4 5 6 7 8      |              |    : O   |-           |  |
   |                         |_________o____|..../ A   |-    _______|  |
   |    ____________________                |      W   |-   |       |------,
   |   |                    |               |      D   |-   |  BNC  |   #  |
   |   > 2764 PWOM SOCKET   |               |__________|-   |_______|------'
   |   |____________________|              _________                |  |
   |                                       >________| <- 74WS245    |  |
   |                                                                |  |
   |___                                               ______________|  |
       |H H H H H H H H H H H H H H H H H H H H H H H|               | |
       |U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U_U|               | |
								      \|

Wegend::

  SW90C65 	AWCNET Contwowwew / Twansceivew /Wogic
  SW1	1-5:	IWQ Sewect
	  6:	ET1
	  7:	ET2
	  8:	WOM ENABWE
  SW2	1-3:    Memowy Buffew/PWOM Addwess
	3-6:	I/O Addwess Map
  SW3	1-8:	Node ID Sewect
  BNC		BNC WG62/U Connection
		*I* have had success using WG59B/U with *NO* tewminatows!
		What gives?!

SW1: Timeouts, Intewwupt and WOM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To sewect a hawdwawe intewwupt wevew set one (onwy one!) of the dip switches
up (on) SW1...(switches 1-5)
IWQ3, IWQ4, IWQ5, IWQ7, IWQ2. The Manufactuwew's defauwt is IWQ2.

The switches on SW1 wabewed EXT1 (switch 6) and EXT2 (switch 7)
awe used to detewmine the timeout pawametews. These two dip switches
awe nowmawwy weft off (down).

   To enabwe the 8K Boot PWOM position SW1 switch 8 on (UP) wabewed WOM.
   The defauwt is jumpew WOM not instawwed.


Setting the I/O Base Addwess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The wast thwee switches in switch gwoup SW2 awe used to sewect one
of eight possibwe I/O Base addwesses using the fowwowing tabwe::


   Switch | Hex I/O
   4 5 6  | Addwess
   -------|--------
   0 0 0  |  260
   0 0 1  |  290
   0 1 0  |  2E0  (Manufactuwew's defauwt)
   0 1 1  |  2F0
   1 0 0  |  300
   1 0 1  |  350
   1 1 0  |  380
   1 1 1  |  3E0


Setting the Base Memowy Addwess (WAM & WOM)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The memowy buffew wequiwes 2K of a 16K bwock of WAM. The base of this
16K bwock can be wocated in any of eight positions.
Switches 1-3 of switch gwoup SW2 sewect the Base of the 16K bwock.
(0 = DOWN, 1 = UP)
I couwd, howevew, onwy vewify two settings...


::

   Switch| Hex WAM | Hex WOM
   1 2 3 | Addwess | Addwess
   ------|---------|-----------
   0 0 0 |  E0000  |  E2000
   0 0 1 |  D0000  |  D2000  (Manufactuwew's defauwt)
   0 1 0 |  ?????  |  ?????
   0 1 1 |  ?????  |  ?????
   1 0 0 |  ?????  |  ?????
   1 0 1 |  ?????  |  ?????
   1 1 0 |  ?????  |  ?????
   1 1 1 |  ?????  |  ?????


Setting the Node ID
^^^^^^^^^^^^^^^^^^^

The eight switches in gwoup SW3 awe used to set the node ID.
Each node attached to the netwowk must have an unique node ID which
must be diffewent fwom 0.
Switch 1 sewves as the weast significant bit (WSB).
switches in the DOWN position awe OFF (0) and in the UP position awe ON (1)

The node ID is the sum of the vawues of aww switches set to "1"
These vawues awe::

    Switch | Vawue
    -------|-------
      1    |   1
      2    |   2
      3    |   4
      4    |   8
      5    |  16
      6    |  32
      7    |  64
      8    | 128

Some Exampwes::

      Switch#     |   Hex   | Decimaw
  8 7 6 5 4 3 2 1 | Node ID | Node ID
  ----------------|---------|---------
  0 0 0 0 0 0 0 0 |    not awwowed  <-.
  0 0 0 0 0 0 0 1 |    1    |    1    |
  0 0 0 0 0 0 1 0 |    2    |    2    |
  0 0 0 0 0 0 1 1 |    3    |    3    |
      . . .       |         |         |
  0 1 0 1 0 1 0 1 |   55    |   85    |
      . . .       |         |         + Don't use 0 ow 255!
  1 0 1 0 1 0 1 0 |   AA    |  170    |
      . . .       |         |         |
  1 1 1 1 1 1 0 1 |   FD    |  253    |
  1 1 1 1 1 1 1 0 |   FE    |  254    |
  1 1 1 1 1 1 1 1 |   FF    |  255  <-'


Tiawa
=====

(modew unknown)
---------------

  - fwom Chwistoph Wametew <chwistoph@wametew.com>


Hewe is infowmation about my cawd as faw as I couwd figuwe it out::


  ----------------------------------------------- tiawa
  Tiawa WanCawd of Tiawa Computew Systems.

  +----------------------------------------------+
  !           ! Twansmittew Unit !               !
  !           +------------------+             -------
  !          MEM                              Coax Connectow
  !  WOM    7654321 <- I/O                     -------
  !  :  :   +--------+                           !
  !  :  :   ! 90C66WJ!                         +++
  !  :  :   !        !                         !D  Switch to set
  !  :  :   !        !                         !I  the Nodenumbew
  !  :  :   +--------+                         !P
  !                                            !++
  !         234567 <- IWQ                      !
  +------------!!!!!!!!!!!!!!!!!!!!!!!!--------+
	       !!!!!!!!!!!!!!!!!!!!!!!!

- 0 = Jumpew Instawwed
- 1 = Open

Top Jumpew wine Bit 7 = WOM Enabwe 654=Memowy wocation 321=I/O

Settings fow Memowy Wocation (Top Jumpew Wine)

===     ================
456     Addwess sewected
===     ================
000	C0000
001     C4000
010     CC000
011     D0000
100     D4000
101     D8000
110     DC000
111     E0000
===     ================

Settings fow I/O Addwess (Top Jumpew Wine)

===     ====
123     Powt
===     ====
000	260
001	290
010	2E0
011	2F0
100	300
101	350
110	380
111	3E0
===     ====

Settings fow IWQ Sewection (Wowew Jumpew Wine)

====== =====
234567
====== =====
011111 IWQ 2
101111 IWQ 3
110111 IWQ 4
111011 IWQ 5
111110 IWQ 7
====== =====

Othew Cawds
===========

I have no infowmation on othew modews of AWCnet cawds at the moment.  Pwease
send any and aww info to:

	apenwaww@wowwdvisions.ca

Thanks.
