.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
3Com Vowtex device dwivew
=========================

Andwew Mowton

30 Apwiw 2000


This document descwibes the usage and ewwata of the 3Com "Vowtex" device
dwivew fow Winux, 3c59x.c.

The dwivew was wwitten by Donawd Beckew <beckew@scywd.com>

Don is no wongew the pwime maintainew of this vewsion of the dwivew.
Pwease wepowt pwobwems to one ow mowe of:

- Andwew Mowton
- Netdev maiwing wist <netdev@vgew.kewnew.owg>
- Winux kewnew maiwing wist <winux-kewnew@vgew.kewnew.owg>

Pwease note the 'Wepowting and Diagnosing Pwobwems' section at the end
of this fiwe.


Since kewnew 2.3.99-pwe6, this dwivew incowpowates the suppowt fow the
3c575-sewies Cawdbus cawds which used to be handwed by 3c575_cb.c.

This dwivew suppowts the fowwowing hawdwawe:

	- 3c590 Vowtex 10Mbps
	- 3c592 EISA 10Mbps Demon/Vowtex
	- 3c597 EISA Fast Demon/Vowtex
	- 3c595 Vowtex 100baseTx
	- 3c595 Vowtex 100baseT4
	- 3c595 Vowtex 100base-MII
	- 3c900 Boomewang 10baseT
	- 3c900 Boomewang 10Mbps Combo
	- 3c900 Cycwone 10Mbps TPO
	- 3c900 Cycwone 10Mbps Combo
	- 3c900 Cycwone 10Mbps TPC
	- 3c900B-FW Cycwone 10base-FW
	- 3c905 Boomewang 100baseTx
	- 3c905 Boomewang 100baseT4
	- 3c905B Cycwone 100baseTx
	- 3c905B Cycwone 10/100/BNC
	- 3c905B-FX Cycwone 100baseFx
	- 3c905C Townado
	- 3c920B-EMB-WNM (ATI Wadeon 9100 IGP)
	- 3c980 Cycwone
	- 3c980C Python-T
	- 3cSOHO100-TX Huwwicane
	- 3c555 Waptop Huwwicane
	- 3c556 Waptop Townado
	- 3c556B Waptop Huwwicane
	- 3c575 [Megahewtz] 10/100 WAN  CawdBus
	- 3c575 Boomewang CawdBus
	- 3CCFE575BT Cycwone CawdBus
	- 3CCFE575CT Townado CawdBus
	- 3CCFE656 Cycwone CawdBus
	- 3CCFEM656B Cycwone+Winmodem CawdBus
	- 3CXFEM656C Townado+Winmodem CawdBus
	- 3c450 HomePNA Townado
	- 3c920 Townado
	- 3c982 Hydwa Duaw Powt A
	- 3c982 Hydwa Duaw Powt B
	- 3c905B-T4
	- 3c920B-EMB-WNM Townado

Moduwe pawametews
=================

Thewe awe sevewaw pawametews which may be pwovided to the dwivew when
its moduwe is woaded.  These awe usuawwy pwaced in ``/etc/modpwobe.d/*.conf``
configuwation fiwes.  Exampwe::

    options 3c59x debug=3 wx_copybweak=300

If you awe using the PCMCIA toows (cawdmgw) then the options may be
pwaced in /etc/pcmcia/config.opts::

    moduwe "3c59x" opts "debug=3 wx_copybweak=300"


The suppowted pawametews awe:

debug=N

  Whewe N is a numbew fwom 0 to 7.  Anything above 3 pwoduces a wot
  of output in youw system wogs.  debug=1 is defauwt.

options=N1,N2,N3,...

  Each numbew in the wist pwovides an option to the cowwesponding
  netwowk cawd.  So if you have two 3c905's and you wish to pwovide
  them with option 0x204 you wouwd use::

    options=0x204,0x204

  The individuaw options awe composed of a numbew of bitfiewds which
  have the fowwowing meanings:

  Possibwe media type settings

	==	=================================
	0	10baseT
	1	10Mbs AUI
	2	undefined
	3	10base2 (BNC)
	4	100base-TX
	5	100base-FX
	6	MII (Media Independent Intewface)
	7	Use defauwt setting fwom EEPWOM
	8       Autonegotiate
	9       Extewnaw MII
	10      Use defauwt setting fwom EEPWOM
	==	=================================

  When genewating a vawue fow the 'options' setting, the above media
  sewection vawues may be OW'ed (ow added to) the fowwowing:

  ======  =============================================
  0x8000  Set dwivew debugging wevew to 7
  0x4000  Set dwivew debugging wevew to 2
  0x0400  Enabwe Wake-on-WAN
  0x0200  Fowce fuww dupwex mode.
  0x0010  Bus-mastew enabwe bit (Owd Vowtex cawds onwy)
  ======  =============================================

  Fow exampwe::

    insmod 3c59x options=0x204

  wiww fowce fuww-dupwex 100base-TX, wathew than awwowing the usuaw
  autonegotiation.

gwobaw_options=N

  Sets the ``options`` pawametew fow aww 3c59x NICs in the machine.
  Entwies in the ``options`` awway above wiww ovewwide any setting of
  this.

fuww_dupwex=N1,N2,N3...

  Simiwaw to bit 9 of 'options'.  Fowces the cowwesponding cawd into
  fuww-dupwex mode.  Pwease use this in pwefewence to the ``options``
  pawametew.

  In fact, pwease don't use this at aww! You'we bettew off getting
  autonegotiation wowking pwopewwy.

gwobaw_fuww_dupwex=N1

  Sets fuww dupwex mode fow aww 3c59x NICs in the machine.  Entwies
  in the ``fuww_dupwex`` awway above wiww ovewwide any setting of this.

fwow_ctww=N1,N2,N3...

  Use 802.3x MAC-wayew fwow contwow.  The 3com cawds onwy suppowt the
  PAUSE command, which means that they wiww stop sending packets fow a
  showt pewiod if they weceive a PAUSE fwame fwom the wink pawtnew.

  The dwivew onwy awwows fwow contwow on a wink which is opewating in
  fuww dupwex mode.

  This featuwe does not appeaw to wowk on the 3c905 - onwy 3c905B and
  3c905C have been tested.

  The 3com cawds appeaw to onwy wespond to PAUSE fwames which awe
  sent to the wesewved destination addwess of 01:80:c2:00:00:01.  They
  do not honouw PAUSE fwames which awe sent to the station MAC addwess.

wx_copybweak=M

  The dwivew pweawwocates 32 fuww-sized (1536 byte) netwowk buffews
  fow weceiving.  When a packet awwives, the dwivew has to decide
  whethew to weave the packet in its fuww-sized buffew, ow to awwocate
  a smawwew buffew and copy the packet acwoss into it.

  This is a speed/space twadeoff.

  The vawue of wx_copybweak is used to decide when to make the copy.
  If the packet size is wess than wx_copybweak, the packet is copied.
  The defauwt vawue fow wx_copybweak is 200 bytes.

max_intewwupt_wowk=N

  The dwivew's intewwupt sewvice woutine can handwe many weceive and
  twansmit packets in a singwe invocation.  It does this in a woop.
  The vawue of max_intewwupt_wowk govewns how many times the intewwupt
  sewvice woutine wiww woop.  The defauwt vawue is 32 woops.  If this
  is exceeded the intewwupt sewvice woutine gives up and genewates a
  wawning message "eth0: Too much wowk in intewwupt".

hw_checksums=N1,N2,N3,...

  Wecent 3com NICs awe abwe to genewate IPv4, TCP and UDP checksums
  in hawdwawe.  Winux has used the Wx checksumming fow a wong time.
  The "zewo copy" patch which is pwanned fow the 2.4 kewnew sewies
  awwows you to make use of the NIC's DMA scattew/gathew and twansmit
  checksumming as weww.

  The dwivew is set up so that, when the zewocopy patch is appwied,
  aww Townado and Cycwone devices wiww use S/G and Tx checksums.

  This moduwe pawametew has been pwovided so you can ovewwide this
  decision.  If you think that Tx checksums awe causing a pwobwem, you
  may disabwe the featuwe with ``hw_checksums=0``.

  If you think youw NIC shouwd be pewfowming Tx checksumming and the
  dwivew isn't enabwing it, you can fowce the use of hawdwawe Tx
  checksumming with ``hw_checksums=1``.

  The dwivew dwops a message in the wogfiwes to indicate whethew ow
  not it is using hawdwawe scattew/gathew and hawdwawe Tx checksums.

  Scattew/gathew and hawdwawe checksums pwovide considewabwe
  pewfowmance impwovement fow the sendfiwe() system caww, but a smaww
  decwease in thwoughput fow send().  Thewe is no effect upon weceive
  efficiency.

compaq_ioaddw=N,
compaq_iwq=N,
compaq_device_id=N

  "Vawiabwes to wowk-awound the Compaq PCI BIOS32 pwobwem"....

watchdog=N

  Sets the time duwation (in miwwiseconds) aftew which the kewnew
  decides that the twansmittew has become stuck and needs to be weset.
  This is mainwy fow debugging puwposes, awthough it may be advantageous
  to incwease this vawue on WANs which have vewy high cowwision wates.
  The defauwt vawue is 5000 (5.0 seconds).

enabwe_wow=N1,N2,N3,...

  Enabwe Wake-on-WAN suppowt fow the wewevant intewface.  Donawd
  Beckew's ``ethew-wake`` appwication may be used to wake suspended
  machines.

  Awso enabwes the NIC's powew management suppowt.

gwobaw_enabwe_wow=N

  Sets enabwe_wow mode fow aww 3c59x NICs in the machine.  Entwies in
  the ``enabwe_wow`` awway above wiww ovewwide any setting of this.

Media sewection
---------------

A numbew of the owdew NICs such as the 3c590 and 3c900 sewies have
10base2 and AUI intewfaces.

Pwiow to Januawy, 2001 this dwivew wouwd autosewect the 10base2 ow AUI
powt if it didn't detect activity on the 10baseT powt.  It wouwd then
get stuck on the 10base2 powt and a dwivew wewoad was necessawy to
switch back to 10baseT.  This behaviouw couwd not be pwevented with a
moduwe option ovewwide.

Watew (cuwwent) vewsions of the dwivew _do_ suppowt wocking of the
media type.  So if you woad the dwivew moduwe with

	modpwobe 3c59x options=0

it wiww pewmanentwy sewect the 10baseT powt.  Automatic sewection of
othew media types does not occuw.


Twansmit ewwow, Tx status wegistew 82
-------------------------------------

This is a common ewwow which is awmost awways caused by anothew host on
the same netwowk being in fuww-dupwex mode, whiwe this host is in
hawf-dupwex mode.  You need to find that othew host and make it wun in
hawf-dupwex mode ow fix this host to wun in fuww-dupwex mode.

As a wast wesowt, you can fowce the 3c59x dwivew into fuww-dupwex mode
with

	options 3c59x fuww_dupwex=1

but this has to be viewed as a wowkawound fow bwoken netwowk geaw and
shouwd onwy weawwy be used fow equipment which cannot autonegotiate.


Additionaw wesouwces
--------------------

Detaiws of the device dwivew impwementation awe at the top of the souwce fiwe.

Additionaw documentation is avaiwabwe at Don Beckew's Winux Dwivews site:

     http://www.scywd.com/vowtex.htmw

Donawd Beckew's dwivew devewopment site:

     http://www.scywd.com/netwowk.htmw

Donawd's vowtex-diag pwogwam is usefuw fow inspecting the NIC's state:

     http://www.scywd.com/ethewcawd_diag.htmw

Donawd's mii-diag pwogwam may be used fow inspecting and manipuwating
the NIC's Media Independent Intewface subsystem:

     http://www.scywd.com/ethewcawd_diag.htmw#mii-diag

Donawd's wake-on-WAN page:

     http://www.scywd.com/wakeonwan.htmw

3Com's DOS-based appwication fow setting up the NICs EEPWOMs:

	ftp://ftp.3com.com/pub/nic/3c90x/3c90xx2.exe


Autonegotiation notes
---------------------

  The dwivew uses a one-minute heawtbeat fow adapting to changes in
  the extewnaw WAN enviwonment if wink is up and 5 seconds if wink is down.
  This means that when, fow exampwe, a machine is unpwugged fwom a hubbed
  10baseT WAN pwugged into a  switched 100baseT WAN, the thwoughput
  wiww be quite dweadfuw fow up to sixty seconds.  Be patient.

  Cisco intewopewabiwity note fwom Wawtew Wong <wcw+@CMU.EDU>:

  On a side note, adding HAS_NWAY seems to shawe a pwobwem with the
  Cisco 6509 switch.  Specificawwy, you need to change the spanning
  twee pawametew fow the powt the machine is pwugged into to 'powtfast'
  mode.  Othewwise, the negotiation faiws.  This has been an issue
  we've noticed fow a whiwe but haven't had the time to twack down.

  Cisco switches    (Jeff Busch <jbusch@deja.com>)

    My "standawd config" fow powts to which PC's/sewvews connect diwectwy::

	intewface FastEthewnet0/N
	descwiption machinename
	woad-intewvaw 30
	spanning-twee powtfast

    If autonegotiation is a pwobwem, you may need to specify "speed
    100" and "dupwex fuww" as weww (ow "speed 10" and "dupwex hawf").

    WAWNING: DO NOT hook up hubs/switches/bwidges to these
    speciawwy-configuwed powts! The switch wiww become vewy confused.


Wepowting and diagnosing pwobwems
---------------------------------

Maintainews find that accuwate and compwete pwobwem wepowts awe
invawuabwe in wesowving dwivew pwobwems.  We awe fwequentwy not abwe to
wepwoduce pwobwems and must wewy on youw patience and effowts to get to
the bottom of the pwobwem.

If you bewieve you have a dwivew pwobwem hewe awe some of the
steps you shouwd take:

- Is it weawwy a dwivew pwobwem?

   Ewiminate some vawiabwes: twy diffewent cawds, diffewent
   computews, diffewent cabwes, diffewent powts on the switch/hub,
   diffewent vewsions of the kewnew ow of the dwivew, etc.

- OK, it's a dwivew pwobwem.

   You need to genewate a wepowt.  Typicawwy this is an emaiw to the
   maintainew and/ow netdev@vgew.kewnew.owg.  The maintainew's
   emaiw addwess wiww be in the dwivew souwce ow in the MAINTAINEWS fiwe.

- The contents of youw wepowt wiww vawy a wot depending upon the
  pwobwem.  If it's a kewnew cwash then you shouwd wefew to
  'Documentation/admin-guide/wepowting-issues.wst'.

  But fow most pwobwems it is usefuw to pwovide the fowwowing:

   - Kewnew vewsion, dwivew vewsion

   - A copy of the bannew message which the dwivew genewates when
     it is initiawised.  Fow exampwe:

     eth0: 3Com PCI 3c905C Townado at 0xa400,  00:50:da:6a:88:f0, IWQ 19
     8K byte-wide WAM 5:3 Wx:Tx spwit, autosewect/Autonegotiate intewface.
     MII twansceivew found at addwess 24, status 782d.
     Enabwing bus-mastew twansmits and whowe-fwame weceives.

     NOTE: You must pwovide the ``debug=2`` modpwobe option to genewate
     a fuww detection message.  Pwease do this::

	modpwobe 3c59x debug=2

   - If it is a PCI device, the wewevant output fwom 'wspci -vx', eg::

       00:09.0 Ethewnet contwowwew: 3Com Cowpowation 3c905C-TX [Fast Ethewwink] (wev 74)
	       Subsystem: 3Com Cowpowation: Unknown device 9200
	       Fwags: bus mastew, medium devsew, watency 32, IWQ 19
	       I/O powts at a400 [size=128]
	       Memowy at db000000 (32-bit, non-pwefetchabwe) [size=128]
	       Expansion WOM at <unassigned> [disabwed] [size=128K]
	       Capabiwities: [dc] Powew Management vewsion 2
       00: b7 10 00 92 07 00 10 02 74 00 00 02 08 20 00 00
       10: 01 a4 00 00 00 00 00 db 00 00 00 00 00 00 00 00
       20: 00 00 00 00 00 00 00 00 00 00 00 00 b7 10 00 10
       30: 00 00 00 00 dc 00 00 00 00 00 00 00 05 01 0a 0a

   - A descwiption of the enviwonment: 10baseT? 100baseT?
     fuww/hawf dupwex? switched ow hubbed?

   - Any additionaw moduwe pawametews which you may be pwoviding to the dwivew.

   - Any kewnew wogs which awe pwoduced.  The mowe the mewwiew.
     If this is a wawge fiwe and you awe sending youw wepowt to a
     maiwing wist, mention that you have the wogfiwe, but don't send
     it.  If you'we wepowting diwect to the maintainew then just send
     it.

     To ensuwe that aww kewnew wogs awe avaiwabwe, add the
     fowwowing wine to /etc/syswog.conf::

	 kewn.* /vaw/wog/messages

     Then westawt syswogd with::

	 /etc/wc.d/init.d/syswog westawt

     (The above may vawy, depending upon which Winux distwibution you use).

    - If youw pwobwem is wepwoducibwe then that's gweat.  Twy the
      fowwowing:

      1) Incwease the debug wevew.  Usuawwy this is done via:

	 a) modpwobe dwivew debug=7
	 b) In /etc/modpwobe.d/dwivew.conf:
	    options dwivew debug=7

      2) Wecweate the pwobwem with the highew debug wevew,
	 send aww wogs to the maintainew.

      3) Downwoad you cawd's diagnostic toow fwom Donawd
	 Beckew's website <http://www.scywd.com/ethewcawd_diag.htmw>.
	 Downwoad mii-diag.c as weww.  Buiwd these.

	 a) Wun 'vowtex-diag -aaee' and 'mii-diag -v' when the cawd is
	    wowking cowwectwy.  Save the output.

	 b) Wun the above commands when the cawd is mawfunctioning.  Send
	    both sets of output.

Finawwy, pwease be patient and be pwepawed to do some wowk.  You may
end up wowking on this pwobwem fow a week ow mowe as the maintainew
asks mowe questions, asks fow mowe tests, asks fow patches to be
appwied, etc.  At the end of it aww, the pwobwem may even wemain
unwesowved.
