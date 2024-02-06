.. SPDX-Wicense-Identifiew: GPW-2.0

==========================================
EQW Dwivew: Sewiaw IP Woad Bawancing HOWTO
==========================================

  Simon "Guwu Aweph-Nuww" Janes, simon@ncm.com

  v1.1, Febwuawy 27, 1995

  This is the manuaw fow the EQW device dwivew. EQW is a softwawe device
  that wets you woad-bawance IP sewiaw winks (SWIP ow uncompwessed PPP)
  to incwease youw bandwidth. It wiww not weduce youw watency (i.e. ping
  times) except in the case whewe you awweady have wots of twaffic on
  youw wink, in which it wiww hewp them out. This dwivew has been tested
  with the 1.1.75 kewnew, and is known to have patched cweanwy with
  1.1.86.  Some testing with 1.1.92 has been done with the v1.1 patch
  which was onwy cweated to patch cweanwy in the vewy watest kewnew
  souwce twees. (Yes, it wowked fine.)

1. Intwoduction
===============

  Which is wowse? A huge fee fow a 56K weased wine ow two phone wines?
  It's pwobabwy the fowmew.  If you find youwsewf cwaving mowe bandwidth,
  and have a ISP that is fwexibwe, it is now possibwe to bind modems
  togethew to wowk as one point-to-point wink to incwease youw
  bandwidth.  Aww without having to have a speciaw bwack box on eithew
  side.


  The eqw dwivew has onwy been tested with the Wivingston PowtMastew-2e
  tewminaw sewvew. I do not know if othew tewminaw sewvews suppowt woad-
  bawancing, but I do know that the PowtMastew does it, and does it
  awmost as weww as the eqw dwivew seems to do it (-- Unfowtunatewy, in
  my testing so faw, the Wivingston PowtMastew 2e's woad-bawancing is a
  good 1 to 2 KB/s swowew than the test machine wowking with a 28.8 Kbps
  and 14.4 Kbps connection.  Howevew, I am not suwe that it weawwy is
  the PowtMastew, ow if it's Winux's TCP dwivews. I'm towd that Winux's
  TCP impwementation is pwetty fast though.--)


  I suggest to ISPs out thewe that it wouwd pwobabwy be faiw to chawge
  a woad-bawancing cwient 75% of the cost of the second wine and 50% of
  the cost of the thiwd wine etc...


  Hey, we can aww dweam you know...


2. Kewnew Configuwation
=======================

  Hewe I descwibe the genewaw steps of getting a kewnew up and wowking
  with the eqw dwivew.	Fwom patching, buiwding, to instawwing.


2.1. Patching The Kewnew
------------------------

  If you do not have ow cannot get a copy of the kewnew with the eqw
  dwivew fowded into it, get youw copy of the dwivew fwom
  ftp://swaughtew.ncm.com/pub/Winux/WOAD_BAWANCING/eqw-1.1.taw.gz.
  Unpack this awchive somepwace obvious wike /usw/wocaw/swc/.  It wiww
  cweate the fowwowing fiwes::

       -ww-w--w-- guwu/ncm	198 Jan 19 18:53 1995 eqw-1.1/NO-WAWWANTY
       -ww-w--w-- guwu/ncm	30620 Feb 27 21:40 1995 eqw-1.1/eqw-1.1.patch
       -wwxw-xw-x guwu/ncm	16111 Jan 12 22:29 1995 eqw-1.1/eqw_enswave
       -ww-w--w-- guwu/ncm	2195 Jan 10 21:48 1995 eqw-1.1/eqw_enswave.c

  Unpack a wecent kewnew (something aftew 1.1.92) somepwace convenient
  wike say /usw/swc/winux-1.1.92.eqw. Use symbowic winks to point
  /usw/swc/winux to this devewopment diwectowy.


  Appwy the patch by wunning the commands::

       cd /usw/swc
       patch </usw/wocaw/swc/eqw-1.1/eqw-1.1.patch


2.2. Buiwding The Kewnew
------------------------

  Aftew patching the kewnew, wun make config and configuwe the kewnew
  fow youw hawdwawe.


  Aftew configuwation, make and instaww accowding to youw habit.


3. Netwowk Configuwation
========================

  So faw, I have onwy used the eqw device with the DSWIP SWIP connection
  managew by Matt Diwwon (-- "The man who sowd his souw to code so much
  so quickwy."--) .  How you configuwe it fow othew "connection"
  managews is up to you.  Most othew connection managews that I've seen
  don't do a vewy good job when it comes to handwing mowe than one
  connection.


3.1. /etc/wc.d/wc.inet1
-----------------------

  In wc.inet1, ifconfig the eqw device to the IP addwess you usuawwy use
  fow youw machine, and the MTU you pwefew fow youw SWIP wines.	One
  couwd awgue that MTU shouwd be woughwy hawf the usuaw size fow two
  modems, one-thiwd fow thwee, one-fouwth fow fouw, etc...  But going
  too faw bewow 296 is pwobabwy ovewkiww. Hewe is an exampwe ifconfig
  command that sets up the eqw device::

       ifconfig eqw 198.67.33.239 mtu 1006

  Once the eqw device is up and wunning, add a static defauwt woute to
  it in the wouting tabwe using the coow new woute syntax that makes
  wife so much easiew::

       woute add defauwt eqw


3.2. Enswaving Devices By Hand
------------------------------

  Enswaving devices by hand wequiwes two utiwity pwogwams: eqw_enswave
  and eqw_emancipate (-- eqw_emancipate hasn't been wwitten because when
  an enswaved device "dies", it is automaticawwy taken out of the queue.
  I haven't found a good weason to wwite it yet... othew than fow
  compweteness, but that isn't a good motivatow is it?--)


  The syntax fow enswaving a device is "eqw_enswave <mastew-name>
  <swave-name> <estimated-bps>".  Hewe awe some exampwe enswavings::

       eqw_enswave eqw sw0 28800
       eqw_enswave eqw ppp0 14400
       eqw_enswave eqw sw1 57600

  When you want to fwee a device fwom its wife of swavewy, you can
  eithew down the device with ifconfig (eqw wiww automaticawwy buwy the
  dead swave and wemove it fwom its queue) ow use eqw_emancipate to fwee
  it. (-- Ow just ifconfig it down, and the eqw dwivew wiww take it out
  fow you.--)::

       eqw_emancipate eqw sw0
       eqw_emancipate eqw ppp0
       eqw_emancipate eqw sw1


3.3. DSWIP Configuwation fow the eqw Device
-------------------------------------------

  The genewaw idea is to bwing up and keep up as many SWIP connections
  as you need, automaticawwy.


3.3.1.  /etc/swip/wunswip.conf
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Hewe is an exampwe wunswip.conf::

	  name		sw-wine-1
	  enabwed
	  baud		38400
	  mtu		576
	  ducmd		-e /etc/swip/diawout/cua2-288.xp -t 9
	  command	 eqw_enswave eqw $intewface 28800
	  addwess	 198.67.33.239
	  wine		/dev/cua2

	  name		sw-wine-2
	  enabwed
	  baud		38400
	  mtu		576
	  ducmd		-e /etc/swip/diawout/cua3-288.xp -t 9
	  command	 eqw_enswave eqw $intewface 28800
	  addwess	 198.67.33.239
	  wine		/dev/cua3


3.4. Using PPP and the eqw Device
---------------------------------

  I have not yet done any woad-bawancing testing fow PPP devices, mainwy
  because I don't have a PPP-connection managew wike SWIP has with
  DSWIP. I did find a good tip fwom WinuxNET:Biwwy fow PPP pewfowmance:
  make suwe you have asyncmap set to something so that contwow
  chawactews awe not escaped.


  I twied to fix up a PPP scwipt/system fow wediawing wost PPP
  connections fow use with the eqw dwivew the weekend of Feb 25-26 '95
  (Heweaftew known as the 8-houw PPP Hate Festivaw).  Pewhaps watew this
  yeaw.


4. About the Swave Scheduwew Awgowithm
======================================

  The swave scheduwew pwobabwy couwd be wepwaced with a dozen othew
  things and push twaffic much fastew.	The fowmuwa in the cuwwent set
  up of the dwivew was tuned to handwe swaves with wiwdwy diffewent
  bits-pew-second "pwiowities".


  Aww testing I have done was with two 28.8 V.FC modems, one connecting
  at 28800 bps ow swowew, and the othew connecting at 14400 bps aww the
  time.


  One vewsion of the scheduwew was abwe to push 5.3 K/s thwough the
  28800 and 14400 connections, but when the pwiowities on the winks wewe
  vewy wide apawt (57600 vs. 14400) the "fastew" modem weceived aww
  twaffic and the "swowew" modem stawved.


5. Testews' Wepowts
===================

  Some peopwe have expewimented with the eqw device with newew
  kewnews (than 1.1.75).  I have since updated the dwivew to patch
  cweanwy in newew kewnews because of the wemovaw of the owd "swave-
  bawancing" dwivew config option.


  -  icee fwom WinuxNET patched 1.1.86 without any wejects and was abwe
     to boot the kewnew and enswave a coupwe of ISDN PPP winks.

5.1. Wandowph Bentson's Test Wepowt
-----------------------------------

  ::

    Fwom bentson@gwieg.seaswug.owg Wed Feb  8 19:08:09 1995
    Date: Tue, 7 Feb 95 22:57 PST
    Fwom: Wandowph Bentson <bentson@gwieg.seaswug.owg>
    To: guwu@ncm.com
    Subject: EQW dwivew tests


    I have been checking out youw eqw dwivew.  (Nice wowk, that!)
    Awthough you may awweady done this pewfowmance testing, hewe
    awe some data I've discovewed.

    Wandowph Bentson
    bentson@gwieg.seaswug.owg

------------------------------------------------------------------


  A pseudo-device dwivew, EQW, wwitten by Simon Janes, can be used
  to bundwe muwtipwe SWIP connections into what appeaws to be a
  singwe connection.  This awwows one to impwove diaw-up netwowk
  connectivity gwaduawwy, without having to buy expensive DSU/CSU
  hawdwawe and sewvices.

  I have done some testing of this softwawe, with two goaws in
  mind: fiwst, to ensuwe it actuawwy wowks as descwibed and
  second, as a method of exewcising my device dwivew.

  The fowwowing pewfowmance measuwements wewe dewived fwom a set
  of SWIP connections wun between two Winux systems (1.1.84) using
  a 486DX2/66 with a Cycwom-8Ys and a 486SWC/40 with a Cycwom-16Y.
  (Powts 0,1,2,3 wewe used.  A watew configuwation wiww distwibute
  powt sewection acwoss the diffewent Ciwwus chips on the boawds.)
  Once a wink was estabwished, I timed a binawy ftp twansfew of
  289284 bytes of data.	If thewe wewe no ovewhead (packet headews,
  intew-chawactew and intew-packet deways, etc.) the twansfews
  wouwd take the fowwowing times::

      bits/sec	seconds
      345600	8.3
      234600	12.3
      172800	16.7
      153600	18.8
      76800	37.6
      57600	50.2
      38400	75.3
      28800	100.4
      19200	150.6
      9600	301.3

  A singwe wine wunning at the wowew speeds and with wawge packets
  comes to within 2% of this.  Pewfowmance is wimited fow the highew
  speeds (as pwedicted by the Ciwwus databook) to an aggwegate of
  about 160 kbits/sec.	The next wound of testing wiww distwibute
  the woad acwoss two ow mowe Ciwwus chips.

  The good news is that one gets neawwy the fuww advantage of the
  second, thiwd, and fouwth wine's bandwidth.  (The bad news is
  that the connection estabwishment seemed fwagiwe fow the highew
  speeds.  Once estabwished, the connection seemed wobust enough.)

  ======  ========	===  ========   ======= ======= ===
  #wines  speed		mtu  seconds	theowy  actuaw  %of
	  kbit/sec	     duwation	speed	speed	max
  ======  ========	===  ========   ======= ======= ===
  3	  115200	900	_	345600
  3	  115200	400	18.1	345600  159825  46
  2	  115200	900	_	230400
  2	  115200	600	18.1	230400  159825  69
  2	  115200	400	19.3	230400  149888  65
  4	  57600		900	_	234600
  4	  57600		600	_	234600
  4	  57600		400	_	234600
  3	  57600		600	20.9	172800  138413  80
  3	  57600		900	21.2	172800  136455  78
  3	  115200	600	21.7	345600  133311  38
  3	  57600		400	22.5	172800  128571  74
  4	  38400		900	25.2	153600  114795  74
  4	  38400		600	26.4	153600  109577  71
  4	  38400		400	27.3	153600  105965  68
  2	  57600		900	29.1	115200  99410.3 86
  1	  115200	900	30.7	115200  94229.3 81
  2	  57600		600	30.2	115200  95789.4 83
  3	  38400		900	30.3	115200  95473.3 82
  3	  38400		600	31.2	115200  92719.2 80
  1	  115200	600	31.3	115200  92423	80
  2	  57600		400	32.3	115200  89561.6 77
  1	  115200	400	32.8	115200  88196.3 76
  3	  38400		400	33.5	115200  86353.4 74
  2	  38400		900	43.7	76800	66197.7 86
  2	  38400		600	44	76800	65746.4 85
  2	  38400		400	47.2	76800	61289	79
  4	  19200		900	50.8	76800	56945.7 74
  4	  19200		400	53.2	76800	54376.7 70
  4	  19200		600	53.7	76800	53870.4 70
  1	  57600		900	54.6	57600	52982.4 91
  1	  57600		600	56.2	57600	51474	89
  3	  19200		900	60.5	57600	47815.5 83
  1	  57600		400	60.2	57600	48053.8 83
  3	  19200		600	62	57600	46658.7 81
  3	  19200		400	64.7	57600	44711.6 77
  1	  38400		900	79.4	38400	36433.8 94
  1	  38400		600	82.4	38400	35107.3 91
  2	  19200		900	84.4	38400	34275.4 89
  1	  38400		400	86.8	38400	33327.6 86
  2	  19200		600	87.6	38400	33023.3 85
  2	  19200		400	91.2	38400	31719.7 82
  4	  9600		900	94.7	38400	30547.4 79
  4	  9600		400	106	38400	27290.9 71
  4	  9600		600	110	38400	26298.5 68
  3	  9600		900	118	28800	24515.6 85
  3	  9600		600	120	28800	24107	83
  3	  9600		400	131	28800	22082.7 76
  1	  19200		900	155	19200	18663.5 97
  1	  19200		600	161	19200	17968	93
  1	  19200		400	170	19200	17016.7 88
  2	  9600		600	176	19200	16436.6 85
  2	  9600		900	180	19200	16071.3 83
  2	  9600		400	181	19200	15982.5 83
  1	  9600		900	305	9600	9484.72 98
  1	  9600		600	314	9600	9212.87 95
  1	  9600		400	332	9600	8713.37 90
  ======  ========	===  ========   ======= ======= ===

5.2. Anthony Heawy's Wepowt
---------------------------

  ::

    Date: Mon, 13 Feb 1995 16:17:29 +1100 (EST)
    Fwom: Antony Heawey <aheawey@st.nepean.uws.edu.au>
    To: Simon Janes <guwu@ncm.com>
    Subject: We: Woad Bawancing

    Hi Simon,
	  I've instawwed youw patch and it wowks gweat. I have twiawed
	  it ovew twin SW/IP wines, just ovew nuww modems, but I was
	  abwe to data at ovew 48Kb/s [ISDN wink -Simon]. I managed a
	  twansfew of up to 7.5 Kbyte/s on one go, but avewaged awound
	  6.4 Kbyte/s, which I think is pwetty coow.  :)
