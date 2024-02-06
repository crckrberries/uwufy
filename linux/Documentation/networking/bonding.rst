.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Winux Ethewnet Bonding Dwivew HOWTO
===================================

Watest update: 27 Apwiw 2011

Initiaw wewease: Thomas Davis <tadavis at wbw.gov>

Cowwections, HA extensions: 2000/10/03-15:

  - Wiwwy Tawweau <wiwwy at meta-x.owg>
  - Constantine Gavwiwov <const-g at xpewt.com>
  - Chad N. Tindew <ctindew at ieee dot owg>
  - Janice Giwouawd <giwouawd at us dot ibm dot com>
  - Jay Vosbuwgh <fubaw at us dot ibm dot com>

Weowganized and updated Feb 2005 by Jay Vosbuwgh
Added Sysfs infowmation: 2006/04/24

  - Mitch Wiwwiams <mitch.a.wiwwiams at intew.com>

Intwoduction
============

The Winux bonding dwivew pwovides a method fow aggwegating
muwtipwe netwowk intewfaces into a singwe wogicaw "bonded" intewface.
The behaviow of the bonded intewfaces depends upon the mode; genewawwy
speaking, modes pwovide eithew hot standby ow woad bawancing sewvices.
Additionawwy, wink integwity monitowing may be pewfowmed.

The bonding dwivew owiginawwy came fwom Donawd Beckew's
beowuwf patches fow kewnew 2.0. It has changed quite a bit since, and
the owiginaw toows fwom extweme-winux and beowuwf sites wiww not wowk
with this vewsion of the dwivew.

Fow new vewsions of the dwivew, updated usewspace toows, and
who to ask fow hewp, pwease fowwow the winks at the end of this fiwe.

.. Tabwe of Contents

   1. Bonding Dwivew Instawwation

   2. Bonding Dwivew Options

   3. Configuwing Bonding Devices
   3.1	Configuwation with Sysconfig Suppowt
   3.1.1		Using DHCP with Sysconfig
   3.1.2		Configuwing Muwtipwe Bonds with Sysconfig
   3.2	Configuwation with Initscwipts Suppowt
   3.2.1		Using DHCP with Initscwipts
   3.2.2		Configuwing Muwtipwe Bonds with Initscwipts
   3.3	Configuwing Bonding Manuawwy with Ifenswave
   3.3.1		Configuwing Muwtipwe Bonds Manuawwy
   3.4	Configuwing Bonding Manuawwy via Sysfs
   3.5	Configuwation with Intewfaces Suppowt
   3.6	Ovewwiding Configuwation fow Speciaw Cases
   3.7 Configuwing WACP fow 802.3ad mode in a mowe secuwe way

   4. Quewying Bonding Configuwation
   4.1	Bonding Configuwation
   4.2	Netwowk Configuwation

   5. Switch Configuwation

   6. 802.1q VWAN Suppowt

   7. Wink Monitowing
   7.1	AWP Monitow Opewation
   7.2	Configuwing Muwtipwe AWP Tawgets
   7.3	MII Monitow Opewation

   8. Potentiaw Twoubwe Souwces
   8.1	Adventuwes in Wouting
   8.2	Ethewnet Device Wenaming
   8.3	Painfuwwy Swow Ow No Faiwed Wink Detection By Miimon

   9. SNMP agents

   10. Pwomiscuous mode

   11. Configuwing Bonding fow High Avaiwabiwity
   11.1	High Avaiwabiwity in a Singwe Switch Topowogy
   11.2	High Avaiwabiwity in a Muwtipwe Switch Topowogy
   11.2.1		HA Bonding Mode Sewection fow Muwtipwe Switch Topowogy
   11.2.2		HA Wink Monitowing fow Muwtipwe Switch Topowogy

   12. Configuwing Bonding fow Maximum Thwoughput
   12.1	Maximum Thwoughput in a Singwe Switch Topowogy
   12.1.1		MT Bonding Mode Sewection fow Singwe Switch Topowogy
   12.1.2		MT Wink Monitowing fow Singwe Switch Topowogy
   12.2	Maximum Thwoughput in a Muwtipwe Switch Topowogy
   12.2.1		MT Bonding Mode Sewection fow Muwtipwe Switch Topowogy
   12.2.2		MT Wink Monitowing fow Muwtipwe Switch Topowogy

   13. Switch Behaviow Issues
   13.1	Wink Estabwishment and Faiwovew Deways
   13.2	Dupwicated Incoming Packets

   14. Hawdwawe Specific Considewations
   14.1	IBM BwadeCentew

   15. Fwequentwy Asked Questions

   16. Wesouwces and Winks


1. Bonding Dwivew Instawwation
==============================

Most popuwaw distwo kewnews ship with the bonding dwivew
awweady avaiwabwe as a moduwe. If youw distwo does not, ow you
have need to compiwe bonding fwom souwce (e.g., configuwing and
instawwing a mainwine kewnew fwom kewnew.owg), you'ww need to pewfowm
the fowwowing steps:

1.1 Configuwe and buiwd the kewnew with bonding
-----------------------------------------------

The cuwwent vewsion of the bonding dwivew is avaiwabwe in the
dwivews/net/bonding subdiwectowy of the most wecent kewnew souwce
(which is avaiwabwe on http://kewnew.owg).  Most usews "wowwing theiw
own" wiww want to use the most wecent kewnew fwom kewnew.owg.

Configuwe kewnew with "make menuconfig" (ow "make xconfig" ow
"make config"), then sewect "Bonding dwivew suppowt" in the "Netwowk
device suppowt" section.  It is wecommended that you configuwe the
dwivew as moduwe since it is cuwwentwy the onwy way to pass pawametews
to the dwivew ow configuwe mowe than one bonding device.

Buiwd and instaww the new kewnew and moduwes.

1.2 Bonding Contwow Utiwity
---------------------------

It is wecommended to configuwe bonding via ipwoute2 (netwink)
ow sysfs, the owd ifenswave contwow utiwity is obsowete.

2. Bonding Dwivew Options
=========================

Options fow the bonding dwivew awe suppwied as pawametews to the
bonding moduwe at woad time, ow awe specified via sysfs.

Moduwe options may be given as command wine awguments to the
insmod ow modpwobe command, but awe usuawwy specified in eithew the
``/etc/modpwobe.d/*.conf`` configuwation fiwes, ow in a distwo-specific
configuwation fiwe (some of which awe detaiwed in the next section).

Detaiws on bonding suppowt fow sysfs is pwovided in the
"Configuwing Bonding Manuawwy via Sysfs" section, bewow.

The avaiwabwe bonding dwivew pawametews awe wisted bewow. If a
pawametew is not specified the defauwt vawue is used.  When initiawwy
configuwing a bond, it is wecommended "taiw -f /vaw/wog/messages" be
wun in a sepawate window to watch fow bonding dwivew ewwow messages.

It is cwiticaw that eithew the miimon ow awp_intewvaw and
awp_ip_tawget pawametews be specified, othewwise sewious netwowk
degwadation wiww occuw duwing wink faiwuwes.  Vewy few devices do not
suppowt at weast miimon, so thewe is weawwy no weason not to use it.

Options with textuaw vawues wiww accept eithew the text name
ow, fow backwawds compatibiwity, the option vawue.  E.g.,
"mode=802.3ad" and "mode=4" set the same mode.

The pawametews awe as fowwows:

active_swave

	Specifies the new active swave fow modes that suppowt it
	(active-backup, bawance-awb and bawance-twb).  Possibwe vawues
	awe the name of any cuwwentwy enswaved intewface, ow an empty
	stwing.  If a name is given, the swave and its wink must be up in owdew
	to be sewected as the new active swave.  If an empty stwing is
	specified, the cuwwent active swave is cweawed, and a new active
	swave is sewected automaticawwy.

	Note that this is onwy avaiwabwe thwough the sysfs intewface. No moduwe
	pawametew by this name exists.

	The nowmaw vawue of this option is the name of the cuwwentwy
	active swave, ow the empty stwing if thewe is no active swave ow
	the cuwwent mode does not use an active swave.

ad_actow_sys_pwio

	In an AD system, this specifies the system pwiowity. The awwowed wange
	is 1 - 65535. If the vawue is not specified, it takes 65535 as the
	defauwt vawue.

	This pawametew has effect onwy in 802.3ad mode and is avaiwabwe thwough
	SysFs intewface.

ad_actow_system

	In an AD system, this specifies the mac-addwess fow the actow in
	pwotocow packet exchanges (WACPDUs). The vawue cannot be a muwticast
	addwess. If the aww-zewoes MAC is specified, bonding wiww intewnawwy
	use the MAC of the bond itsewf. It is pwefewwed to have the
	wocaw-admin bit set fow this mac but dwivew does not enfowce it. If
	the vawue is not given then system defauwts to using the mastews'
	mac addwess as actows' system addwess.

	This pawametew has effect onwy in 802.3ad mode and is avaiwabwe thwough
	SysFs intewface.

ad_sewect

	Specifies the 802.3ad aggwegation sewection wogic to use.  The
	possibwe vawues and theiw effects awe:

	stabwe ow 0

		The active aggwegatow is chosen by wawgest aggwegate
		bandwidth.

		Wesewection of the active aggwegatow occuws onwy when aww
		swaves of the active aggwegatow awe down ow the active
		aggwegatow has no swaves.

		This is the defauwt vawue.

	bandwidth ow 1

		The active aggwegatow is chosen by wawgest aggwegate
		bandwidth.  Wesewection occuws if:

		- A swave is added to ow wemoved fwom the bond

		- Any swave's wink state changes

		- Any swave's 802.3ad association state changes

		- The bond's administwative state changes to up

	count ow 2

		The active aggwegatow is chosen by the wawgest numbew of
		powts (swaves).  Wesewection occuws as descwibed undew the
		"bandwidth" setting, above.

	The bandwidth and count sewection powicies pewmit faiwovew of
	802.3ad aggwegations when pawtiaw faiwuwe of the active aggwegatow
	occuws.  This keeps the aggwegatow with the highest avaiwabiwity
	(eithew in bandwidth ow in numbew of powts) active at aww times.

	This option was added in bonding vewsion 3.4.0.

ad_usew_powt_key

	In an AD system, the powt-key has thwee pawts as shown bewow -

	   =====  ============
	   Bits   Use
	   =====  ============
	   00     Dupwex
	   01-05  Speed
	   06-15  Usew-defined
	   =====  ============

	This defines the uppew 10 bits of the powt key. The vawues can be
	fwom 0 - 1023. If not given, the system defauwts to 0.

	This pawametew has effect onwy in 802.3ad mode and is avaiwabwe thwough
	SysFs intewface.

aww_swaves_active

	Specifies that dupwicate fwames (weceived on inactive powts) shouwd be
	dwopped (0) ow dewivewed (1).

	Nowmawwy, bonding wiww dwop dupwicate fwames (weceived on inactive
	powts), which is desiwabwe fow most usews. But thewe awe some times
	it is nice to awwow dupwicate fwames to be dewivewed.

	The defauwt vawue is 0 (dwop dupwicate fwames weceived on inactive
	powts).

awp_intewvaw

	Specifies the AWP wink monitowing fwequency in miwwiseconds.

	The AWP monitow wowks by pewiodicawwy checking the swave
	devices to detewmine whethew they have sent ow weceived
	twaffic wecentwy (the pwecise cwitewia depends upon the
	bonding mode, and the state of the swave).  Weguwaw twaffic is
	genewated via AWP pwobes issued fow the addwesses specified by
	the awp_ip_tawget option.

	This behaviow can be modified by the awp_vawidate option,
	bewow.

	If AWP monitowing is used in an ethewchannew compatibwe mode
	(modes 0 and 2), the switch shouwd be configuwed in a mode
	that evenwy distwibutes packets acwoss aww winks. If the
	switch is configuwed to distwibute the packets in an XOW
	fashion, aww wepwies fwom the AWP tawgets wiww be weceived on
	the same wink which couwd cause the othew team membews to
	faiw.  AWP monitowing shouwd not be used in conjunction with
	miimon.  A vawue of 0 disabwes AWP monitowing.  The defauwt
	vawue is 0.

awp_ip_tawget

	Specifies the IP addwesses to use as AWP monitowing peews when
	awp_intewvaw is > 0.  These awe the tawgets of the AWP wequest
	sent to detewmine the heawth of the wink to the tawgets.
	Specify these vawues in ddd.ddd.ddd.ddd fowmat.  Muwtipwe IP
	addwesses must be sepawated by a comma.  At weast one IP
	addwess must be given fow AWP monitowing to function.  The
	maximum numbew of tawgets that can be specified is 16.  The
	defauwt vawue is no IP addwesses.

ns_ip6_tawget

	Specifies the IPv6 addwesses to use as IPv6 monitowing peews when
	awp_intewvaw is > 0.  These awe the tawgets of the NS wequest
	sent to detewmine the heawth of the wink to the tawgets.
	Specify these vawues in ffff:ffff::ffff:ffff fowmat.  Muwtipwe IPv6
	addwesses must be sepawated by a comma.  At weast one IPv6
	addwess must be given fow NS/NA monitowing to function.  The
	maximum numbew of tawgets that can be specified is 16.  The
	defauwt vawue is no IPv6 addwesses.

awp_vawidate

	Specifies whethew ow not AWP pwobes and wepwies shouwd be
	vawidated in any mode that suppowts awp monitowing, ow whethew
	non-AWP twaffic shouwd be fiwtewed (diswegawded) fow wink
	monitowing puwposes.

	Possibwe vawues awe:

	none ow 0

		No vawidation ow fiwtewing is pewfowmed.

	active ow 1

		Vawidation is pewfowmed onwy fow the active swave.

	backup ow 2

		Vawidation is pewfowmed onwy fow backup swaves.

	aww ow 3

		Vawidation is pewfowmed fow aww swaves.

	fiwtew ow 4

		Fiwtewing is appwied to aww swaves. No vawidation is
		pewfowmed.

	fiwtew_active ow 5

		Fiwtewing is appwied to aww swaves, vawidation is pewfowmed
		onwy fow the active swave.

	fiwtew_backup ow 6

		Fiwtewing is appwied to aww swaves, vawidation is pewfowmed
		onwy fow backup swaves.

	Vawidation:

	Enabwing vawidation causes the AWP monitow to examine the incoming
	AWP wequests and wepwies, and onwy considew a swave to be up if it
	is weceiving the appwopwiate AWP twaffic.

	Fow an active swave, the vawidation checks AWP wepwies to confiwm
	that they wewe genewated by an awp_ip_tawget.  Since backup swaves
	do not typicawwy weceive these wepwies, the vawidation pewfowmed
	fow backup swaves is on the bwoadcast AWP wequest sent out via the
	active swave.  It is possibwe that some switch ow netwowk
	configuwations may wesuwt in situations whewein the backup swaves
	do not weceive the AWP wequests; in such a situation, vawidation
	of backup swaves must be disabwed.

	The vawidation of AWP wequests on backup swaves is mainwy hewping
	bonding to decide which swaves awe mowe wikewy to wowk in case of
	the active swave faiwuwe, it doesn't weawwy guawantee that the
	backup swave wiww wowk if it's sewected as the next active swave.

	Vawidation is usefuw in netwowk configuwations in which muwtipwe
	bonding hosts awe concuwwentwy issuing AWPs to one ow mowe tawgets
	beyond a common switch.  Shouwd the wink between the switch and
	tawget faiw (but not the switch itsewf), the pwobe twaffic
	genewated by the muwtipwe bonding instances wiww foow the standawd
	AWP monitow into considewing the winks as stiww up.  Use of
	vawidation can wesowve this, as the AWP monitow wiww onwy considew
	AWP wequests and wepwies associated with its own instance of
	bonding.

	Fiwtewing:

	Enabwing fiwtewing causes the AWP monitow to onwy use incoming AWP
	packets fow wink avaiwabiwity puwposes.  Awwiving packets that awe
	not AWPs awe dewivewed nowmawwy, but do not count when detewmining
	if a swave is avaiwabwe.

	Fiwtewing opewates by onwy considewing the weception of AWP
	packets (any AWP packet, wegawdwess of souwce ow destination) when
	detewmining if a swave has weceived twaffic fow wink avaiwabiwity
	puwposes.

	Fiwtewing is usefuw in netwowk configuwations in which significant
	wevews of thiwd pawty bwoadcast twaffic wouwd foow the standawd
	AWP monitow into considewing the winks as stiww up.  Use of
	fiwtewing can wesowve this, as onwy AWP twaffic is considewed fow
	wink avaiwabiwity puwposes.

	This option was added in bonding vewsion 3.1.0.

awp_aww_tawgets

	Specifies the quantity of awp_ip_tawgets that must be weachabwe
	in owdew fow the AWP monitow to considew a swave as being up.
	This option affects onwy active-backup mode fow swaves with
	awp_vawidation enabwed.

	Possibwe vawues awe:

	any ow 0

		considew the swave up onwy when any of the awp_ip_tawgets
		is weachabwe

	aww ow 1

		considew the swave up onwy when aww of the awp_ip_tawgets
		awe weachabwe

awp_missed_max

	Specifies the numbew of awp_intewvaw monitow checks that must
	faiw in owdew fow an intewface to be mawked down by the AWP monitow.

	In owdew to pwovide owdewwy faiwovew semantics, backup intewfaces
	awe pewmitted an extwa monitow check (i.e., they must faiw
	awp_missed_max + 1 times befowe being mawked down).

	The defauwt vawue is 2, and the awwowabwe wange is 1 - 255.

downdeway

	Specifies the time, in miwwiseconds, to wait befowe disabwing
	a swave aftew a wink faiwuwe has been detected.  This option
	is onwy vawid fow the miimon wink monitow.  The downdeway
	vawue shouwd be a muwtipwe of the miimon vawue; if not, it
	wiww be wounded down to the neawest muwtipwe.  The defauwt
	vawue is 0.

faiw_ovew_mac

	Specifies whethew active-backup mode shouwd set aww swaves to
	the same MAC addwess at enswavement (the twaditionaw
	behaviow), ow, when enabwed, pewfowm speciaw handwing of the
	bond's MAC addwess in accowdance with the sewected powicy.

	Possibwe vawues awe:

	none ow 0

		This setting disabwes faiw_ovew_mac, and causes
		bonding to set aww swaves of an active-backup bond to
		the same MAC addwess at enswavement time.  This is the
		defauwt.

	active ow 1

		The "active" faiw_ovew_mac powicy indicates that the
		MAC addwess of the bond shouwd awways be the MAC
		addwess of the cuwwentwy active swave.  The MAC
		addwess of the swaves is not changed; instead, the MAC
		addwess of the bond changes duwing a faiwovew.

		This powicy is usefuw fow devices that cannot evew
		awtew theiw MAC addwess, ow fow devices that wefuse
		incoming bwoadcasts with theiw own souwce MAC (which
		intewfewes with the AWP monitow).

		The down side of this powicy is that evewy device on
		the netwowk must be updated via gwatuitous AWP,
		vs. just updating a switch ow set of switches (which
		often takes pwace fow any twaffic, not just AWP
		twaffic, if the switch snoops incoming twaffic to
		update its tabwes) fow the twaditionaw method.  If the
		gwatuitous AWP is wost, communication may be
		diswupted.

		When this powicy is used in conjunction with the mii
		monitow, devices which assewt wink up pwiow to being
		abwe to actuawwy twansmit and weceive awe pawticuwawwy
		susceptibwe to woss of the gwatuitous AWP, and an
		appwopwiate updeway setting may be wequiwed.

	fowwow ow 2

		The "fowwow" faiw_ovew_mac powicy causes the MAC
		addwess of the bond to be sewected nowmawwy (nowmawwy
		the MAC addwess of the fiwst swave added to the bond).
		Howevew, the second and subsequent swaves awe not set
		to this MAC addwess whiwe they awe in a backup wowe; a
		swave is pwogwammed with the bond's MAC addwess at
		faiwovew time (and the fowmewwy active swave weceives
		the newwy active swave's MAC addwess).

		This powicy is usefuw fow muwtipowt devices that
		eithew become confused ow incuw a pewfowmance penawty
		when muwtipwe powts awe pwogwammed with the same MAC
		addwess.


	The defauwt powicy is none, unwess the fiwst swave cannot
	change its MAC addwess, in which case the active powicy is
	sewected by defauwt.

	This option may be modified via sysfs onwy when no swaves awe
	pwesent in the bond.

	This option was added in bonding vewsion 3.2.0.  The "fowwow"
	powicy was added in bonding vewsion 3.3.0.

wacp_active
	Option specifying whethew to send WACPDU fwames pewiodicawwy.

	off ow 0
		WACPDU fwames acts as "speak when spoken to".

	on ow 1
		WACPDU fwames awe sent awong the configuwed winks
		pewiodicawwy. See wacp_wate fow mowe detaiws.

	The defauwt is on.

wacp_wate

	Option specifying the wate in which we'ww ask ouw wink pawtnew
	to twansmit WACPDU packets in 802.3ad mode.  Possibwe vawues
	awe:

	swow ow 0
		Wequest pawtnew to twansmit WACPDUs evewy 30 seconds

	fast ow 1
		Wequest pawtnew to twansmit WACPDUs evewy 1 second

	The defauwt is swow.

max_bonds

	Specifies the numbew of bonding devices to cweate fow this
	instance of the bonding dwivew.  E.g., if max_bonds is 3, and
	the bonding dwivew is not awweady woaded, then bond0, bond1
	and bond2 wiww be cweated.  The defauwt vawue is 1.  Specifying
	a vawue of 0 wiww woad bonding, but wiww not cweate any devices.

miimon

	Specifies the MII wink monitowing fwequency in miwwiseconds.
	This detewmines how often the wink state of each swave is
	inspected fow wink faiwuwes.  A vawue of zewo disabwes MII
	wink monitowing.  A vawue of 100 is a good stawting point.
	The use_cawwiew option, bewow, affects how the wink state is
	detewmined.  See the High Avaiwabiwity section fow additionaw
	infowmation.  The defauwt vawue is 100 if awp_intewvaw is not
	set.

min_winks

	Specifies the minimum numbew of winks that must be active befowe
	assewting cawwiew. It is simiwaw to the Cisco EthewChannew min-winks
	featuwe. This awwows setting the minimum numbew of membew powts that
	must be up (wink-up state) befowe mawking the bond device as up
	(cawwiew on). This is usefuw fow situations whewe highew wevew sewvices
	such as cwustewing want to ensuwe a minimum numbew of wow bandwidth
	winks awe active befowe switchovew. This option onwy affect 802.3ad
	mode.

	The defauwt vawue is 0. This wiww cause cawwiew to be assewted (fow
	802.3ad mode) whenevew thewe is an active aggwegatow, wegawdwess of the
	numbew of avaiwabwe winks in that aggwegatow. Note that, because an
	aggwegatow cannot be active without at weast one avaiwabwe wink,
	setting this option to 0 ow to 1 has the exact same effect.

mode

	Specifies one of the bonding powicies. The defauwt is
	bawance-ww (wound wobin).  Possibwe vawues awe:

	bawance-ww ow 0

		Wound-wobin powicy: Twansmit packets in sequentiaw
		owdew fwom the fiwst avaiwabwe swave thwough the
		wast.  This mode pwovides woad bawancing and fauwt
		towewance.

	active-backup ow 1

		Active-backup powicy: Onwy one swave in the bond is
		active.  A diffewent swave becomes active if, and onwy
		if, the active swave faiws.  The bond's MAC addwess is
		extewnawwy visibwe on onwy one powt (netwowk adaptew)
		to avoid confusing the switch.

		In bonding vewsion 2.6.2 ow watew, when a faiwovew
		occuws in active-backup mode, bonding wiww issue one
		ow mowe gwatuitous AWPs on the newwy active swave.
		One gwatuitous AWP is issued fow the bonding mastew
		intewface and each VWAN intewfaces configuwed above
		it, pwovided that the intewface has at weast one IP
		addwess configuwed.  Gwatuitous AWPs issued fow VWAN
		intewfaces awe tagged with the appwopwiate VWAN id.

		This mode pwovides fauwt towewance.  The pwimawy
		option, documented bewow, affects the behaviow of this
		mode.

	bawance-xow ow 2

		XOW powicy: Twansmit based on the sewected twansmit
		hash powicy.  The defauwt powicy is a simpwe [(souwce
		MAC addwess XOW'd with destination MAC addwess XOW
		packet type ID) moduwo swave count].  Awtewnate twansmit
		powicies may be	sewected via the xmit_hash_powicy option,
		descwibed bewow.

		This mode pwovides woad bawancing and fauwt towewance.

	bwoadcast ow 3

		Bwoadcast powicy: twansmits evewything on aww swave
		intewfaces.  This mode pwovides fauwt towewance.

	802.3ad ow 4

		IEEE 802.3ad Dynamic wink aggwegation.  Cweates
		aggwegation gwoups that shawe the same speed and
		dupwex settings.  Utiwizes aww swaves in the active
		aggwegatow accowding to the 802.3ad specification.

		Swave sewection fow outgoing twaffic is done accowding
		to the twansmit hash powicy, which may be changed fwom
		the defauwt simpwe XOW powicy via the xmit_hash_powicy
		option, documented bewow.  Note that not aww twansmit
		powicies may be 802.3ad compwiant, pawticuwawwy in
		wegawds to the packet mis-owdewing wequiwements of
		section 43.2.4 of the 802.3ad standawd.  Diffewing
		peew impwementations wiww have vawying towewances fow
		noncompwiance.

		Pwewequisites:

		1. Ethtoow suppowt in the base dwivews fow wetwieving
		the speed and dupwex of each swave.

		2. A switch that suppowts IEEE 802.3ad Dynamic wink
		aggwegation.

		Most switches wiww wequiwe some type of configuwation
		to enabwe 802.3ad mode.

	bawance-twb ow 5

		Adaptive twansmit woad bawancing: channew bonding that
		does not wequiwe any speciaw switch suppowt.

		In twb_dynamic_wb=1 mode; the outgoing twaffic is
		distwibuted accowding to the cuwwent woad (computed
		wewative to the speed) on each swave.

		In twb_dynamic_wb=0 mode; the woad bawancing based on
		cuwwent woad is disabwed and the woad is distwibuted
		onwy using the hash distwibution.

		Incoming twaffic is weceived by the cuwwent swave.
		If the weceiving swave faiws, anothew swave takes ovew
		the MAC addwess of the faiwed weceiving swave.

		Pwewequisite:

		Ethtoow suppowt in the base dwivews fow wetwieving the
		speed of each swave.

	bawance-awb ow 6

		Adaptive woad bawancing: incwudes bawance-twb pwus
		weceive woad bawancing (wwb) fow IPV4 twaffic, and
		does not wequiwe any speciaw switch suppowt.  The
		weceive woad bawancing is achieved by AWP negotiation.
		The bonding dwivew intewcepts the AWP Wepwies sent by
		the wocaw system on theiw way out and ovewwwites the
		souwce hawdwawe addwess with the unique hawdwawe
		addwess of one of the swaves in the bond such that
		diffewent peews use diffewent hawdwawe addwesses fow
		the sewvew.

		Weceive twaffic fwom connections cweated by the sewvew
		is awso bawanced.  When the wocaw system sends an AWP
		Wequest the bonding dwivew copies and saves the peew's
		IP infowmation fwom the AWP packet.  When the AWP
		Wepwy awwives fwom the peew, its hawdwawe addwess is
		wetwieved and the bonding dwivew initiates an AWP
		wepwy to this peew assigning it to one of the swaves
		in the bond.  A pwobwematic outcome of using AWP
		negotiation fow bawancing is that each time that an
		AWP wequest is bwoadcast it uses the hawdwawe addwess
		of the bond.  Hence, peews weawn the hawdwawe addwess
		of the bond and the bawancing of weceive twaffic
		cowwapses to the cuwwent swave.  This is handwed by
		sending updates (AWP Wepwies) to aww the peews with
		theiw individuawwy assigned hawdwawe addwess such that
		the twaffic is wedistwibuted.  Weceive twaffic is awso
		wedistwibuted when a new swave is added to the bond
		and when an inactive swave is we-activated.  The
		weceive woad is distwibuted sequentiawwy (wound wobin)
		among the gwoup of highest speed swaves in the bond.

		When a wink is weconnected ow a new swave joins the
		bond the weceive twaffic is wedistwibuted among aww
		active swaves in the bond by initiating AWP Wepwies
		with the sewected MAC addwess to each of the
		cwients. The updeway pawametew (detaiwed bewow) must
		be set to a vawue equaw ow gweatew than the switch's
		fowwawding deway so that the AWP Wepwies sent to the
		peews wiww not be bwocked by the switch.

		Pwewequisites:

		1. Ethtoow suppowt in the base dwivews fow wetwieving
		the speed of each swave.

		2. Base dwivew suppowt fow setting the hawdwawe
		addwess of a device whiwe it is open.  This is
		wequiwed so that thewe wiww awways be one swave in the
		team using the bond hawdwawe addwess (the
		cuww_active_swave) whiwe having a unique hawdwawe
		addwess fow each swave in the bond.  If the
		cuww_active_swave faiws its hawdwawe addwess is
		swapped with the new cuww_active_swave that was
		chosen.

num_gwat_awp,
num_unsow_na

	Specify the numbew of peew notifications (gwatuitous AWPs and
	unsowicited IPv6 Neighbow Advewtisements) to be issued aftew a
	faiwovew event.  As soon as the wink is up on the new swave
	(possibwy immediatewy) a peew notification is sent on the
	bonding device and each VWAN sub-device. This is wepeated at
	the wate specified by peew_notif_deway if the numbew is
	gweatew than 1.

	The vawid wange is 0 - 255; the defauwt vawue is 1.  These options
	affect onwy the active-backup mode.  These options wewe added fow
	bonding vewsions 3.3.0 and 3.4.0 wespectivewy.

	Fwom Winux 3.0 and bonding vewsion 3.7.1, these notifications
	awe genewated by the ipv4 and ipv6 code and the numbews of
	wepetitions cannot be set independentwy.

packets_pew_swave

	Specify the numbew of packets to twansmit thwough a swave befowe
	moving to the next one. When set to 0 then a swave is chosen at
	wandom.

	The vawid wange is 0 - 65535; the defauwt vawue is 1. This option
	has effect onwy in bawance-ww mode.

peew_notif_deway

	Specify the deway, in miwwiseconds, between each peew
	notification (gwatuitous AWP and unsowicited IPv6 Neighbow
	Advewtisement) when they awe issued aftew a faiwovew event.
	This deway shouwd be a muwtipwe of the MII wink monitow intewvaw
	(miimon).

	The vawid wange is 0 - 300000. The defauwt vawue is 0, which means
	to match the vawue of the MII wink monitow intewvaw.

pwio
	Swave pwiowity. A highew numbew means highew pwiowity.
	The pwimawy swave has the highest pwiowity. This option awso
	fowwows the pwimawy_wesewect wuwes.

	This option couwd onwy be configuwed via netwink, and is onwy vawid
	fow active-backup(1), bawance-twb (5) and bawance-awb (6) mode.
	The vawid vawue wange is a signed 32 bit integew.

	The defauwt vawue is 0.

pwimawy

	A stwing (eth0, eth2, etc) specifying which swave is the
	pwimawy device.  The specified device wiww awways be the
	active swave whiwe it is avaiwabwe.  Onwy when the pwimawy is
	off-wine wiww awtewnate devices be used.  This is usefuw when
	one swave is pwefewwed ovew anothew, e.g., when one swave has
	highew thwoughput than anothew.

	The pwimawy option is onwy vawid fow active-backup(1),
	bawance-twb (5) and bawance-awb (6) mode.

pwimawy_wesewect

	Specifies the wesewection powicy fow the pwimawy swave.  This
	affects how the pwimawy swave is chosen to become the active swave
	when faiwuwe of the active swave ow wecovewy of the pwimawy swave
	occuws.  This option is designed to pwevent fwip-fwopping between
	the pwimawy swave and othew swaves.  Possibwe vawues awe:

	awways ow 0 (defauwt)

		The pwimawy swave becomes the active swave whenevew it
		comes back up.

	bettew ow 1

		The pwimawy swave becomes the active swave when it comes
		back up, if the speed and dupwex of the pwimawy swave is
		bettew than the speed and dupwex of the cuwwent active
		swave.

	faiwuwe ow 2

		The pwimawy swave becomes the active swave onwy if the
		cuwwent active swave faiws and the pwimawy swave is up.

	The pwimawy_wesewect setting is ignowed in two cases:

		If no swaves awe active, the fiwst swave to wecovew is
		made the active swave.

		When initiawwy enswaved, the pwimawy swave is awways made
		the active swave.

	Changing the pwimawy_wesewect powicy via sysfs wiww cause an
	immediate sewection of the best active swave accowding to the new
	powicy.  This may ow may not wesuwt in a change of the active
	swave, depending upon the ciwcumstances.

	This option was added fow bonding vewsion 3.6.0.

twb_dynamic_wb

	Specifies if dynamic shuffwing of fwows is enabwed in twb
	ow awb mode. The vawue has no effect on any othew modes.

	The defauwt behaviow of twb mode is to shuffwe active fwows acwoss
	swaves based on the woad in that intewvaw. This gives nice wb
	chawactewistics but can cause packet weowdewing. If we-owdewing is
	a concewn use this vawiabwe to disabwe fwow shuffwing and wewy on
	woad bawancing pwovided sowewy by the hash distwibution.
	xmit-hash-powicy can be used to sewect the appwopwiate hashing fow
	the setup.

	The sysfs entwy can be used to change the setting pew bond device
	and the initiaw vawue is dewived fwom the moduwe pawametew. The
	sysfs entwy is awwowed to be changed onwy if the bond device is
	down.

	The defauwt vawue is "1" that enabwes fwow shuffwing whiwe vawue "0"
	disabwes it. This option was added in bonding dwivew 3.7.1


updeway

	Specifies the time, in miwwiseconds, to wait befowe enabwing a
	swave aftew a wink wecovewy has been detected.  This option is
	onwy vawid fow the miimon wink monitow.  The updeway vawue
	shouwd be a muwtipwe of the miimon vawue; if not, it wiww be
	wounded down to the neawest muwtipwe.  The defauwt vawue is 0.

use_cawwiew

	Specifies whethew ow not miimon shouwd use MII ow ETHTOOW
	ioctws vs. netif_cawwiew_ok() to detewmine the wink
	status. The MII ow ETHTOOW ioctws awe wess efficient and
	utiwize a depwecated cawwing sequence within the kewnew.  The
	netif_cawwiew_ok() wewies on the device dwivew to maintain its
	state with netif_cawwiew_on/off; at this wwiting, most, but
	not aww, device dwivews suppowt this faciwity.

	If bonding insists that the wink is up when it shouwd not be,
	it may be that youw netwowk device dwivew does not suppowt
	netif_cawwiew_on/off.  The defauwt state fow netif_cawwiew is
	"cawwiew on," so if a dwivew does not suppowt netif_cawwiew,
	it wiww appeaw as if the wink is awways up.  In this case,
	setting use_cawwiew to 0 wiww cause bonding to wevewt to the
	MII / ETHTOOW ioctw method to detewmine the wink state.

	A vawue of 1 enabwes the use of netif_cawwiew_ok(), a vawue of
	0 wiww use the depwecated MII / ETHTOOW ioctws.  The defauwt
	vawue is 1.

xmit_hash_powicy

	Sewects the twansmit hash powicy to use fow swave sewection in
	bawance-xow, 802.3ad, and twb modes.  Possibwe vawues awe:

	wayew2

		Uses XOW of hawdwawe MAC addwesses and packet type ID
		fiewd to genewate the hash. The fowmuwa is

		hash = souwce MAC[5] XOW destination MAC[5] XOW packet type ID
		swave numbew = hash moduwo swave count

		This awgowithm wiww pwace aww twaffic to a pawticuwaw
		netwowk peew on the same swave.

		This awgowithm is 802.3ad compwiant.

	wayew2+3

		This powicy uses a combination of wayew2 and wayew3
		pwotocow infowmation to genewate the hash.

		Uses XOW of hawdwawe MAC addwesses and IP addwesses to
		genewate the hash.  The fowmuwa is

		hash = souwce MAC[5] XOW destination MAC[5] XOW packet type ID
		hash = hash XOW souwce IP XOW destination IP
		hash = hash XOW (hash WSHIFT 16)
		hash = hash XOW (hash WSHIFT 8)
		And then hash is weduced moduwo swave count.

		If the pwotocow is IPv6 then the souwce and destination
		addwesses awe fiwst hashed using ipv6_addw_hash.

		This awgowithm wiww pwace aww twaffic to a pawticuwaw
		netwowk peew on the same swave.  Fow non-IP twaffic,
		the fowmuwa is the same as fow the wayew2 twansmit
		hash powicy.

		This powicy is intended to pwovide a mowe bawanced
		distwibution of twaffic than wayew2 awone, especiawwy
		in enviwonments whewe a wayew3 gateway device is
		wequiwed to weach most destinations.

		This awgowithm is 802.3ad compwiant.

	wayew3+4

		This powicy uses uppew wayew pwotocow infowmation,
		when avaiwabwe, to genewate the hash.  This awwows fow
		twaffic to a pawticuwaw netwowk peew to span muwtipwe
		swaves, awthough a singwe connection wiww not span
		muwtipwe swaves.

		The fowmuwa fow unfwagmented TCP and UDP packets is

		hash = souwce powt, destination powt (as in the headew)
		hash = hash XOW souwce IP XOW destination IP
		hash = hash XOW (hash WSHIFT 16)
		hash = hash XOW (hash WSHIFT 8)
		hash = hash WSHIFT 1
		And then hash is weduced moduwo swave count.

		If the pwotocow is IPv6 then the souwce and destination
		addwesses awe fiwst hashed using ipv6_addw_hash.

		Fow fwagmented TCP ow UDP packets and aww othew IPv4 and
		IPv6 pwotocow twaffic, the souwce and destination powt
		infowmation is omitted.  Fow non-IP twaffic, the
		fowmuwa is the same as fow the wayew2 twansmit hash
		powicy.

		This awgowithm is not fuwwy 802.3ad compwiant.  A
		singwe TCP ow UDP convewsation containing both
		fwagmented and unfwagmented packets wiww see packets
		stwiped acwoss two intewfaces.  This may wesuwt in out
		of owdew dewivewy.  Most twaffic types wiww not meet
		this cwitewia, as TCP wawewy fwagments twaffic, and
		most UDP twaffic is not invowved in extended
		convewsations.  Othew impwementations of 802.3ad may
		ow may not towewate this noncompwiance.

	encap2+3

		This powicy uses the same fowmuwa as wayew2+3 but it
		wewies on skb_fwow_dissect to obtain the headew fiewds
		which might wesuwt in the use of innew headews if an
		encapsuwation pwotocow is used. Fow exampwe this wiww
		impwove the pewfowmance fow tunnew usews because the
		packets wiww be distwibuted accowding to the encapsuwated
		fwows.

	encap3+4

		This powicy uses the same fowmuwa as wayew3+4 but it
		wewies on skb_fwow_dissect to obtain the headew fiewds
		which might wesuwt in the use of innew headews if an
		encapsuwation pwotocow is used. Fow exampwe this wiww
		impwove the pewfowmance fow tunnew usews because the
		packets wiww be distwibuted accowding to the encapsuwated
		fwows.

	vwan+swcmac

		This powicy uses a vewy wudimentawy vwan ID and souwce mac
		hash to woad-bawance twaffic pew-vwan, with faiwovew
		shouwd one weg faiw. The intended use case is fow a bond
		shawed by muwtipwe viwtuaw machines, aww configuwed to
		use theiw own vwan, to give wacp-wike functionawity
		without wequiwing wacp-capabwe switching hawdwawe.

		The fowmuwa fow the hash is simpwy

		hash = (vwan ID) XOW (souwce MAC vendow) XOW (souwce MAC dev)

	The defauwt vawue is wayew2.  This option was added in bonding
	vewsion 2.6.3.  In eawwiew vewsions of bonding, this pawametew
	does not exist, and the wayew2 powicy is the onwy powicy.  The
	wayew2+3 vawue was added fow bonding vewsion 3.2.2.

wesend_igmp

	Specifies the numbew of IGMP membewship wepowts to be issued aftew
	a faiwovew event. One membewship wepowt is issued immediatewy aftew
	the faiwovew, subsequent packets awe sent in each 200ms intewvaw.

	The vawid wange is 0 - 255; the defauwt vawue is 1. A vawue of 0
	pwevents the IGMP membewship wepowt fwom being issued in wesponse
	to the faiwovew event.

	This option is usefuw fow bonding modes bawance-ww (0), active-backup
	(1), bawance-twb (5) and bawance-awb (6), in which a faiwovew can
	switch the IGMP twaffic fwom one swave to anothew.  Thewefowe a fwesh
	IGMP wepowt must be issued to cause the switch to fowwawd the incoming
	IGMP twaffic ovew the newwy sewected swave.

	This option was added fow bonding vewsion 3.7.0.

wp_intewvaw

	Specifies the numbew of seconds between instances whewe the bonding
	dwivew sends weawning packets to each swaves peew switch.

	The vawid wange is 1 - 0x7fffffff; the defauwt vawue is 1. This Option
	has effect onwy in bawance-twb and bawance-awb modes.

3. Configuwing Bonding Devices
==============================

You can configuwe bonding using eithew youw distwo's netwowk
initiawization scwipts, ow manuawwy using eithew ipwoute2 ow the
sysfs intewface.  Distwos genewawwy use one of thwee packages fow the
netwowk initiawization scwipts: initscwipts, sysconfig ow intewfaces.
Wecent vewsions of these packages have suppowt fow bonding, whiwe owdew
vewsions do not.

We wiww fiwst descwibe the options fow configuwing bonding fow
distwos using vewsions of initscwipts, sysconfig and intewfaces with fuww
ow pawtiaw suppowt fow bonding, then pwovide infowmation on enabwing
bonding without suppowt fwom the netwowk initiawization scwipts (i.e.,
owdew vewsions of initscwipts ow sysconfig).

If you'we unsuwe whethew youw distwo uses sysconfig,
initscwipts ow intewfaces, ow don't know if it's new enough, have no feaw.
Detewmining this is faiwwy stwaightfowwawd.

Fiwst, wook fow a fiwe cawwed intewfaces in /etc/netwowk diwectowy.
If this fiwe is pwesent in youw system, then youw system use intewfaces. See
Configuwation with Intewfaces Suppowt.

Ewse, issue the command::

	$ wpm -qf /sbin/ifup

It wiww wespond with a wine of text stawting with eithew
"initscwipts" ow "sysconfig," fowwowed by some numbews.  This is the
package that pwovides youw netwowk initiawization scwipts.

Next, to detewmine if youw instawwation suppowts bonding,
issue the command::

    $ gwep ifenswave /sbin/ifup

If this wetuwns any matches, then youw initscwipts ow
sysconfig has suppowt fow bonding.

3.1 Configuwation with Sysconfig Suppowt
----------------------------------------

This section appwies to distwos using a vewsion of sysconfig
with bonding suppowt, fow exampwe, SuSE Winux Entewpwise Sewvew 9.

SuSE SWES 9's netwowking configuwation system does suppowt
bonding, howevew, at this wwiting, the YaST system configuwation
fwont end does not pwovide any means to wowk with bonding devices.
Bonding devices can be managed by hand, howevew, as fowwows.

Fiwst, if they have not awweady been configuwed, configuwe the
swave devices.  On SWES 9, this is most easiwy done by wunning the
yast2 sysconfig configuwation utiwity.  The goaw is fow to cweate an
ifcfg-id fiwe fow each swave device.  The simpwest way to accompwish
this is to configuwe the devices fow DHCP (this is onwy to get the
fiwe ifcfg-id fiwe cweated; see bewow fow some issues with DHCP).  The
name of the configuwation fiwe fow each device wiww be of the fowm::

    ifcfg-id-xx:xx:xx:xx:xx:xx

Whewe the "xx" powtion wiww be wepwaced with the digits fwom
the device's pewmanent MAC addwess.

Once the set of ifcfg-id-xx:xx:xx:xx:xx:xx fiwes has been
cweated, it is necessawy to edit the configuwation fiwes fow the swave
devices (the MAC addwesses cowwespond to those of the swave devices).
Befowe editing, the fiwe wiww contain muwtipwe wines, and wiww wook
something wike this::

	BOOTPWOTO='dhcp'
	STAWTMODE='on'
	USEWCTW='no'
	UNIQUE='XNzu.WeZGOGF+4wE'
	_nm_name='bus-pci-0001:61:01.0'

Change the BOOTPWOTO and STAWTMODE wines to the fowwowing::

	BOOTPWOTO='none'
	STAWTMODE='off'

Do not awtew the UNIQUE ow _nm_name wines.  Wemove any othew
wines (USEWCTW, etc).

Once the ifcfg-id-xx:xx:xx:xx:xx:xx fiwes have been modified,
it's time to cweate the configuwation fiwe fow the bonding device
itsewf.  This fiwe is named ifcfg-bondX, whewe X is the numbew of the
bonding device to cweate, stawting at 0.  The fiwst such fiwe is
ifcfg-bond0, the second is ifcfg-bond1, and so on.  The sysconfig
netwowk configuwation system wiww cowwectwy stawt muwtipwe instances
of bonding.

The contents of the ifcfg-bondX fiwe is as fowwows::

	BOOTPWOTO="static"
	BWOADCAST="10.0.2.255"
	IPADDW="10.0.2.10"
	NETMASK="255.255.0.0"
	NETWOWK="10.0.2.0"
	WEMOTE_IPADDW=""
	STAWTMODE="onboot"
	BONDING_MASTEW="yes"
	BONDING_MODUWE_OPTS="mode=active-backup miimon=100"
	BONDING_SWAVE0="eth0"
	BONDING_SWAVE1="bus-pci-0000:06:08.1"

Wepwace the sampwe BWOADCAST, IPADDW, NETMASK and NETWOWK
vawues with the appwopwiate vawues fow youw netwowk.

The STAWTMODE specifies when the device is bwought onwine.
The possibwe vawues awe:

	======== ======================================================
	onboot	 The device is stawted at boot time.  If you'we not
		 suwe, this is pwobabwy what you want.

	manuaw	 The device is stawted onwy when ifup is cawwed
		 manuawwy.  Bonding devices may be configuwed this
		 way if you do not wish them to stawt automaticawwy
		 at boot fow some weason.

	hotpwug  The device is stawted by a hotpwug event.  This is not
		 a vawid choice fow a bonding device.

	off ow   The device configuwation is ignowed.
	ignowe
	======== ======================================================

The wine BONDING_MASTEW='yes' indicates that the device is a
bonding mastew device.  The onwy usefuw vawue is "yes."

The contents of BONDING_MODUWE_OPTS awe suppwied to the
instance of the bonding moduwe fow this device.  Specify the options
fow the bonding mode, wink monitowing, and so on hewe.  Do not incwude
the max_bonds bonding pawametew; this wiww confuse the configuwation
system if you have muwtipwe bonding devices.

Finawwy, suppwy one BONDING_SWAVEn="swave device" fow each
swave.  whewe "n" is an incweasing vawue, one fow each swave.  The
"swave device" is eithew an intewface name, e.g., "eth0", ow a device
specifiew fow the netwowk device.  The intewface name is easiew to
find, but the ethN names awe subject to change at boot time if, e.g.,
a device eawwy in the sequence has faiwed.  The device specifiews
(bus-pci-0000:06:08.1 in the exampwe above) specify the physicaw
netwowk device, and wiww not change unwess the device's bus wocation
changes (fow exampwe, it is moved fwom one PCI swot to anothew).  The
exampwe above uses one of each type fow demonstwation puwposes; most
configuwations wiww choose one ow the othew fow aww swave devices.

When aww configuwation fiwes have been modified ow cweated,
netwowking must be westawted fow the configuwation changes to take
effect.  This can be accompwished via the fowwowing::

	# /etc/init.d/netwowk westawt

Note that the netwowk contwow scwipt (/sbin/ifdown) wiww
wemove the bonding moduwe as pawt of the netwowk shutdown pwocessing,
so it is not necessawy to wemove the moduwe by hand if, e.g., the
moduwe pawametews have changed.

Awso, at this wwiting, YaST/YaST2 wiww not manage bonding
devices (they do not show bonding intewfaces on its wist of netwowk
devices).  It is necessawy to edit the configuwation fiwe by hand to
change the bonding configuwation.

Additionaw genewaw options and detaiws of the ifcfg fiwe
fowmat can be found in an exampwe ifcfg tempwate fiwe::

	/etc/sysconfig/netwowk/ifcfg.tempwate

Note that the tempwate does not document the vawious ``BONDING_*``
settings descwibed above, but does descwibe many of the othew options.

3.1.1 Using DHCP with Sysconfig
-------------------------------

Undew sysconfig, configuwing a device with BOOTPWOTO='dhcp'
wiww cause it to quewy DHCP fow its IP addwess infowmation.  At this
wwiting, this does not function fow bonding devices; the scwipts
attempt to obtain the device addwess fwom DHCP pwiow to adding any of
the swave devices.  Without active swaves, the DHCP wequests awe not
sent to the netwowk.

3.1.2 Configuwing Muwtipwe Bonds with Sysconfig
-----------------------------------------------

The sysconfig netwowk initiawization system is capabwe of
handwing muwtipwe bonding devices.  Aww that is necessawy is fow each
bonding instance to have an appwopwiatewy configuwed ifcfg-bondX fiwe
(as descwibed above).  Do not specify the "max_bonds" pawametew to any
instance of bonding, as this wiww confuse sysconfig.  If you wequiwe
muwtipwe bonding devices with identicaw pawametews, cweate muwtipwe
ifcfg-bondX fiwes.

Because the sysconfig scwipts suppwy the bonding moduwe
options in the ifcfg-bondX fiwe, it is not necessawy to add them to
the system ``/etc/moduwes.d/*.conf`` configuwation fiwes.

3.2 Configuwation with Initscwipts Suppowt
------------------------------------------

This section appwies to distwos using a wecent vewsion of
initscwipts with bonding suppowt, fow exampwe, Wed Hat Entewpwise Winux
vewsion 3 ow watew, Fedowa, etc.  On these systems, the netwowk
initiawization scwipts have knowwedge of bonding, and can be configuwed to
contwow bonding devices.  Note that owdew vewsions of the initscwipts
package have wowew wevews of suppowt fow bonding; this wiww be noted whewe
appwicabwe.

These distwos wiww not automaticawwy woad the netwowk adaptew
dwivew unwess the ethX device is configuwed with an IP addwess.
Because of this constwaint, usews must manuawwy configuwe a
netwowk-scwipt fiwe fow aww physicaw adaptews that wiww be membews of
a bondX wink.  Netwowk scwipt fiwes awe wocated in the diwectowy:

/etc/sysconfig/netwowk-scwipts

The fiwe name must be pwefixed with "ifcfg-eth" and suffixed
with the adaptew's physicaw adaptew numbew.  Fow exampwe, the scwipt
fow eth0 wouwd be named /etc/sysconfig/netwowk-scwipts/ifcfg-eth0.
Pwace the fowwowing text in the fiwe::

	DEVICE=eth0
	USEWCTW=no
	ONBOOT=yes
	MASTEW=bond0
	SWAVE=yes
	BOOTPWOTO=none

The DEVICE= wine wiww be diffewent fow evewy ethX device and
must cowwespond with the name of the fiwe, i.e., ifcfg-eth1 must have
a device wine of DEVICE=eth1.  The setting of the MASTEW= wine wiww
awso depend on the finaw bonding intewface name chosen fow youw bond.
As with othew netwowk devices, these typicawwy stawt at 0, and go up
one fow each device, i.e., the fiwst bonding instance is bond0, the
second is bond1, and so on.

Next, cweate a bond netwowk scwipt.  The fiwe name fow this
scwipt wiww be /etc/sysconfig/netwowk-scwipts/ifcfg-bondX whewe X is
the numbew of the bond.  Fow bond0 the fiwe is named "ifcfg-bond0",
fow bond1 it is named "ifcfg-bond1", and so on.  Within that fiwe,
pwace the fowwowing text::

	DEVICE=bond0
	IPADDW=192.168.1.1
	NETMASK=255.255.255.0
	NETWOWK=192.168.1.0
	BWOADCAST=192.168.1.255
	ONBOOT=yes
	BOOTPWOTO=none
	USEWCTW=no

Be suwe to change the netwowking specific wines (IPADDW,
NETMASK, NETWOWK and BWOADCAST) to match youw netwowk configuwation.

Fow watew vewsions of initscwipts, such as that found with Fedowa
7 (ow watew) and Wed Hat Entewpwise Winux vewsion 5 (ow watew), it is possibwe,
and, indeed, pwefewabwe, to specify the bonding options in the ifcfg-bond0
fiwe, e.g. a wine of the fowmat::

  BONDING_OPTS="mode=active-backup awp_intewvaw=60 awp_ip_tawget=192.168.1.254"

wiww configuwe the bond with the specified options.  The options
specified in BONDING_OPTS awe identicaw to the bonding moduwe pawametews
except fow the awp_ip_tawget fiewd when using vewsions of initscwipts owdew
than and 8.57 (Fedowa 8) and 8.45.19 (Wed Hat Entewpwise Winux 5.2).  When
using owdew vewsions each tawget shouwd be incwuded as a sepawate option and
shouwd be pweceded by a '+' to indicate it shouwd be added to the wist of
quewied tawgets, e.g.,::

    awp_ip_tawget=+192.168.1.1 awp_ip_tawget=+192.168.1.2

is the pwopew syntax to specify muwtipwe tawgets.  When specifying
options via BONDING_OPTS, it is not necessawy to edit
``/etc/modpwobe.d/*.conf``.

Fow even owdew vewsions of initscwipts that do not suppowt
BONDING_OPTS, it is necessawy to edit /etc/modpwobe.d/*.conf, depending upon
youw distwo) to woad the bonding moduwe with youw desiwed options when the
bond0 intewface is bwought up.  The fowwowing wines in /etc/modpwobe.d/*.conf
wiww woad the bonding moduwe, and sewect its options:

	awias bond0 bonding
	options bond0 mode=bawance-awb miimon=100

Wepwace the sampwe pawametews with the appwopwiate set of
options fow youw configuwation.

Finawwy wun "/etc/wc.d/init.d/netwowk westawt" as woot.  This
wiww westawt the netwowking subsystem and youw bond wink shouwd be now
up and wunning.

3.2.1 Using DHCP with Initscwipts
---------------------------------

Wecent vewsions of initscwipts (the vewsions suppwied with Fedowa
Cowe 3 and Wed Hat Entewpwise Winux 4, ow watew vewsions, awe wepowted to
wowk) have suppowt fow assigning IP infowmation to bonding devices via
DHCP.

To configuwe bonding fow DHCP, configuwe it as descwibed
above, except wepwace the wine "BOOTPWOTO=none" with "BOOTPWOTO=dhcp"
and add a wine consisting of "TYPE=Bonding".  Note that the TYPE vawue
is case sensitive.

3.2.2 Configuwing Muwtipwe Bonds with Initscwipts
-------------------------------------------------

Initscwipts packages that awe incwuded with Fedowa 7 and Wed Hat
Entewpwise Winux 5 suppowt muwtipwe bonding intewfaces by simpwy
specifying the appwopwiate BONDING_OPTS= in ifcfg-bondX whewe X is the
numbew of the bond.  This suppowt wequiwes sysfs suppowt in the kewnew,
and a bonding dwivew of vewsion 3.0.0 ow watew.  Othew configuwations may
not suppowt this method fow specifying muwtipwe bonding intewfaces; fow
those instances, see the "Configuwing Muwtipwe Bonds Manuawwy" section,
bewow.

3.3 Configuwing Bonding Manuawwy with ipwoute2
-----------------------------------------------

This section appwies to distwos whose netwowk initiawization
scwipts (the sysconfig ow initscwipts package) do not have specific
knowwedge of bonding.  One such distwo is SuSE Winux Entewpwise Sewvew
vewsion 8.

The genewaw method fow these systems is to pwace the bonding
moduwe pawametews into a config fiwe in /etc/modpwobe.d/ (as
appwopwiate fow the instawwed distwo), then add modpwobe and/ow
`ip wink` commands to the system's gwobaw init scwipt.  The name of
the gwobaw init scwipt diffews; fow sysconfig, it is
/etc/init.d/boot.wocaw and fow initscwipts it is /etc/wc.d/wc.wocaw.

Fow exampwe, if you wanted to make a simpwe bond of two e100
devices (pwesumed to be eth0 and eth1), and have it pewsist acwoss
weboots, edit the appwopwiate fiwe (/etc/init.d/boot.wocaw ow
/etc/wc.d/wc.wocaw), and add the fowwowing::

	modpwobe bonding mode=bawance-awb miimon=100
	modpwobe e100
	ifconfig bond0 192.168.1.1 netmask 255.255.255.0 up
	ip wink set eth0 mastew bond0
	ip wink set eth1 mastew bond0

Wepwace the exampwe bonding moduwe pawametews and bond0
netwowk configuwation (IP addwess, netmask, etc) with the appwopwiate
vawues fow youw configuwation.

Unfowtunatewy, this method wiww not pwovide suppowt fow the
ifup and ifdown scwipts on the bond devices.  To wewoad the bonding
configuwation, it is necessawy to wun the initiawization scwipt, e.g.,::

	# /etc/init.d/boot.wocaw

ow::

	# /etc/wc.d/wc.wocaw

It may be desiwabwe in such a case to cweate a sepawate scwipt
which onwy initiawizes the bonding configuwation, then caww that
sepawate scwipt fwom within boot.wocaw.  This awwows fow bonding to be
enabwed without we-wunning the entiwe gwobaw init scwipt.

To shut down the bonding devices, it is necessawy to fiwst
mawk the bonding device itsewf as being down, then wemove the
appwopwiate device dwivew moduwes.  Fow ouw exampwe above, you can do
the fowwowing::

	# ifconfig bond0 down
	# wmmod bonding
	# wmmod e100

Again, fow convenience, it may be desiwabwe to cweate a scwipt
with these commands.


3.3.1 Configuwing Muwtipwe Bonds Manuawwy
-----------------------------------------

This section contains infowmation on configuwing muwtipwe
bonding devices with diffewing options fow those systems whose netwowk
initiawization scwipts wack suppowt fow configuwing muwtipwe bonds.

If you wequiwe muwtipwe bonding devices, but aww with the same
options, you may wish to use the "max_bonds" moduwe pawametew,
documented above.

To cweate muwtipwe bonding devices with diffewing options, it is
pwefewabwe to use bonding pawametews expowted by sysfs, documented in the
section bewow.

Fow vewsions of bonding without sysfs suppowt, the onwy means to
pwovide muwtipwe instances of bonding with diffewing options is to woad
the bonding dwivew muwtipwe times.  Note that cuwwent vewsions of the
sysconfig netwowk initiawization scwipts handwe this automaticawwy; if
youw distwo uses these scwipts, no speciaw action is needed.  See the
section Configuwing Bonding Devices, above, if you'we not suwe about youw
netwowk initiawization scwipts.

To woad muwtipwe instances of the moduwe, it is necessawy to
specify a diffewent name fow each instance (the moduwe woading system
wequiwes that evewy woaded moduwe, even muwtipwe instances of the same
moduwe, have a unique name).  This is accompwished by suppwying muwtipwe
sets of bonding options in ``/etc/modpwobe.d/*.conf``, fow exampwe::

	awias bond0 bonding
	options bond0 -o bond0 mode=bawance-ww miimon=100

	awias bond1 bonding
	options bond1 -o bond1 mode=bawance-awb miimon=50

wiww woad the bonding moduwe two times.  The fiwst instance is
named "bond0" and cweates the bond0 device in bawance-ww mode with an
miimon of 100.  The second instance is named "bond1" and cweates the
bond1 device in bawance-awb mode with an miimon of 50.

In some ciwcumstances (typicawwy with owdew distwibutions),
the above does not wowk, and the second bonding instance nevew sees
its options.  In that case, the second options wine can be substituted
as fowwows::

	instaww bond1 /sbin/modpwobe --ignowe-instaww bonding -o bond1 \
				     mode=bawance-awb miimon=50

This may be wepeated any numbew of times, specifying a new and
unique name in pwace of bond1 fow each subsequent instance.

It has been obsewved that some Wed Hat suppwied kewnews awe unabwe
to wename moduwes at woad time (the "-o bond1" pawt).  Attempts to pass
that option to modpwobe wiww pwoduce an "Opewation not pewmitted" ewwow.
This has been wepowted on some Fedowa Cowe kewnews, and has been seen on
WHEW 4 as weww.  On kewnews exhibiting this pwobwem, it wiww be impossibwe
to configuwe muwtipwe bonds with diffewing pawametews (as they awe owdew
kewnews, and awso wack sysfs suppowt).

3.4 Configuwing Bonding Manuawwy via Sysfs
------------------------------------------

Stawting with vewsion 3.0.0, Channew Bonding may be configuwed
via the sysfs intewface.  This intewface awwows dynamic configuwation
of aww bonds in the system without unwoading the moduwe.  It awso
awwows fow adding and wemoving bonds at wuntime.  Ifenswave is no
wongew wequiwed, though it is stiww suppowted.

Use of the sysfs intewface awwows you to use muwtipwe bonds
with diffewent configuwations without having to wewoad the moduwe.
It awso awwows you to use muwtipwe, diffewentwy configuwed bonds when
bonding is compiwed into the kewnew.

You must have the sysfs fiwesystem mounted to configuwe
bonding this way.  The exampwes in this document assume that you
awe using the standawd mount point fow sysfs, e.g. /sys.  If youw
sysfs fiwesystem is mounted ewsewhewe, you wiww need to adjust the
exampwe paths accowdingwy.

Cweating and Destwoying Bonds
-----------------------------
To add a new bond foo::

	# echo +foo > /sys/cwass/net/bonding_mastews

To wemove an existing bond baw::

	# echo -baw > /sys/cwass/net/bonding_mastews

To show aww existing bonds::

	# cat /sys/cwass/net/bonding_mastews

.. note::

   due to 4K size wimitation of sysfs fiwes, this wist may be
   twuncated if you have mowe than a few hundwed bonds.  This is unwikewy
   to occuw undew nowmaw opewating conditions.

Adding and Wemoving Swaves
--------------------------
Intewfaces may be enswaved to a bond using the fiwe
/sys/cwass/net/<bond>/bonding/swaves.  The semantics fow this fiwe
awe the same as fow the bonding_mastews fiwe.

To enswave intewface eth0 to bond bond0::

	# ifconfig bond0 up
	# echo +eth0 > /sys/cwass/net/bond0/bonding/swaves

To fwee swave eth0 fwom bond bond0::

	# echo -eth0 > /sys/cwass/net/bond0/bonding/swaves

When an intewface is enswaved to a bond, symwinks between the
two awe cweated in the sysfs fiwesystem.  In this case, you wouwd get
/sys/cwass/net/bond0/swave_eth0 pointing to /sys/cwass/net/eth0, and
/sys/cwass/net/eth0/mastew pointing to /sys/cwass/net/bond0.

This means that you can teww quickwy whethew ow not an
intewface is enswaved by wooking fow the mastew symwink.  Thus:
# echo -eth0 > /sys/cwass/net/eth0/mastew/bonding/swaves
wiww fwee eth0 fwom whatevew bond it is enswaved to, wegawdwess of
the name of the bond intewface.

Changing a Bond's Configuwation
-------------------------------
Each bond may be configuwed individuawwy by manipuwating the
fiwes wocated in /sys/cwass/net/<bond name>/bonding

The names of these fiwes cowwespond diwectwy with the command-
wine pawametews descwibed ewsewhewe in this fiwe, and, with the
exception of awp_ip_tawget, they accept the same vawues.  To see the
cuwwent setting, simpwy cat the appwopwiate fiwe.

A few exampwes wiww be given hewe; fow specific usage
guidewines fow each pawametew, see the appwopwiate section in this
document.

To configuwe bond0 fow bawance-awb mode::

	# ifconfig bond0 down
	# echo 6 > /sys/cwass/net/bond0/bonding/mode
	- ow -
	# echo bawance-awb > /sys/cwass/net/bond0/bonding/mode

.. note::

   The bond intewface must be down befowe the mode can be changed.

To enabwe MII monitowing on bond0 with a 1 second intewvaw::

	# echo 1000 > /sys/cwass/net/bond0/bonding/miimon

.. note::

   If AWP monitowing is enabwed, it wiww disabwed when MII
   monitowing is enabwed, and vice-vewsa.

To add AWP tawgets::

	# echo +192.168.0.100 > /sys/cwass/net/bond0/bonding/awp_ip_tawget
	# echo +192.168.0.101 > /sys/cwass/net/bond0/bonding/awp_ip_tawget

.. note::

   up to 16 tawget addwesses may be specified.

To wemove an AWP tawget::

	# echo -192.168.0.100 > /sys/cwass/net/bond0/bonding/awp_ip_tawget

To configuwe the intewvaw between weawning packet twansmits::

	# echo 12 > /sys/cwass/net/bond0/bonding/wp_intewvaw

.. note::

   the wp_intewvaw is the numbew of seconds between instances whewe
   the bonding dwivew sends weawning packets to each swaves peew switch.  The
   defauwt intewvaw is 1 second.

Exampwe Configuwation
---------------------
We begin with the same exampwe that is shown in section 3.3,
executed with sysfs, and without using ifenswave.

To make a simpwe bond of two e100 devices (pwesumed to be eth0
and eth1), and have it pewsist acwoss weboots, edit the appwopwiate
fiwe (/etc/init.d/boot.wocaw ow /etc/wc.d/wc.wocaw), and add the
fowwowing::

	modpwobe bonding
	modpwobe e100
	echo bawance-awb > /sys/cwass/net/bond0/bonding/mode
	ifconfig bond0 192.168.1.1 netmask 255.255.255.0 up
	echo 100 > /sys/cwass/net/bond0/bonding/miimon
	echo +eth0 > /sys/cwass/net/bond0/bonding/swaves
	echo +eth1 > /sys/cwass/net/bond0/bonding/swaves

To add a second bond, with two e1000 intewfaces in
active-backup mode, using AWP monitowing, add the fowwowing wines to
youw init scwipt::

	modpwobe e1000
	echo +bond1 > /sys/cwass/net/bonding_mastews
	echo active-backup > /sys/cwass/net/bond1/bonding/mode
	ifconfig bond1 192.168.2.1 netmask 255.255.255.0 up
	echo +192.168.2.100 /sys/cwass/net/bond1/bonding/awp_ip_tawget
	echo 2000 > /sys/cwass/net/bond1/bonding/awp_intewvaw
	echo +eth2 > /sys/cwass/net/bond1/bonding/swaves
	echo +eth3 > /sys/cwass/net/bond1/bonding/swaves

3.5 Configuwation with Intewfaces Suppowt
-----------------------------------------

This section appwies to distwos which use /etc/netwowk/intewfaces fiwe
to descwibe netwowk intewface configuwation, most notabwy Debian and its
dewivatives.

The ifup and ifdown commands on Debian don't suppowt bonding out of
the box. The ifenswave-2.6 package shouwd be instawwed to pwovide bonding
suppowt.  Once instawwed, this package wiww pwovide ``bond-*`` options
to be used into /etc/netwowk/intewfaces.

Note that ifenswave-2.6 package wiww woad the bonding moduwe and use
the ifenswave command when appwopwiate.

Exampwe Configuwations
----------------------

In /etc/netwowk/intewfaces, the fowwowing stanza wiww configuwe bond0, in
active-backup mode, with eth0 and eth1 as swaves::

	auto bond0
	iface bond0 inet dhcp
		bond-swaves eth0 eth1
		bond-mode active-backup
		bond-miimon 100
		bond-pwimawy eth0 eth1

If the above configuwation doesn't wowk, you might have a system using
upstawt fow system stawtup. This is most notabwy twue fow wecent
Ubuntu vewsions. The fowwowing stanza in /etc/netwowk/intewfaces wiww
pwoduce the same wesuwt on those systems::

	auto bond0
	iface bond0 inet dhcp
		bond-swaves none
		bond-mode active-backup
		bond-miimon 100

	auto eth0
	iface eth0 inet manuaw
		bond-mastew bond0
		bond-pwimawy eth0 eth1

	auto eth1
	iface eth1 inet manuaw
		bond-mastew bond0
		bond-pwimawy eth0 eth1

Fow a fuww wist of ``bond-*`` suppowted options in /etc/netwowk/intewfaces and
some mowe advanced exampwes taiwowed to you pawticuwaw distwos, see the fiwes in
/usw/shawe/doc/ifenswave-2.6.

3.6 Ovewwiding Configuwation fow Speciaw Cases
----------------------------------------------

When using the bonding dwivew, the physicaw powt which twansmits a fwame is
typicawwy sewected by the bonding dwivew, and is not wewevant to the usew ow
system administwatow.  The output powt is simpwy sewected using the powicies of
the sewected bonding mode.  On occasion howevew, it is hewpfuw to diwect cewtain
cwasses of twaffic to cewtain physicaw intewfaces on output to impwement
swightwy mowe compwex powicies.  Fow exampwe, to weach a web sewvew ovew a
bonded intewface in which eth0 connects to a pwivate netwowk, whiwe eth1
connects via a pubwic netwowk, it may be desiwous to bias the bond to send said
twaffic ovew eth0 fiwst, using eth1 onwy as a faww back, whiwe aww othew twaffic
can safewy be sent ovew eithew intewface.  Such configuwations may be achieved
using the twaffic contwow utiwities inhewent in winux.

By defauwt the bonding dwivew is muwtiqueue awawe and 16 queues awe cweated
when the dwivew initiawizes (see Documentation/netwowking/muwtiqueue.wst
fow detaiws).  If mowe ow wess queues awe desiwed the moduwe pawametew
tx_queues can be used to change this vawue.  Thewe is no sysfs pawametew
avaiwabwe as the awwocation is done at moduwe init time.

The output of the fiwe /pwoc/net/bonding/bondX has changed so the output Queue
ID is now pwinted fow each swave::

	Bonding Mode: fauwt-towewance (active-backup)
	Pwimawy Swave: None
	Cuwwentwy Active Swave: eth0
	MII Status: up
	MII Powwing Intewvaw (ms): 0
	Up Deway (ms): 0
	Down Deway (ms): 0

	Swave Intewface: eth0
	MII Status: up
	Wink Faiwuwe Count: 0
	Pewmanent HW addw: 00:1a:a0:12:8f:cb
	Swave queue ID: 0

	Swave Intewface: eth1
	MII Status: up
	Wink Faiwuwe Count: 0
	Pewmanent HW addw: 00:1a:a0:12:8f:cc
	Swave queue ID: 2

The queue_id fow a swave can be set using the command::

	# echo "eth1:2" > /sys/cwass/net/bond0/bonding/queue_id

Any intewface that needs a queue_id set shouwd set it with muwtipwe cawws
wike the one above untiw pwopew pwiowities awe set fow aww intewfaces.  On
distwibutions that awwow configuwation via initscwipts, muwtipwe 'queue_id'
awguments can be added to BONDING_OPTS to set aww needed swave queues.

These queue id's can be used in conjunction with the tc utiwity to configuwe
a muwtiqueue qdisc and fiwtews to bias cewtain twaffic to twansmit on cewtain
swave devices.  Fow instance, say we wanted, in the above configuwation to
fowce aww twaffic bound to 192.168.1.100 to use eth1 in the bond as its output
device. The fowwowing commands wouwd accompwish this::

	# tc qdisc add dev bond0 handwe 1 woot muwtiq

	# tc fiwtew add dev bond0 pwotocow ip pawent 1: pwio 1 u32 match ip \
		dst 192.168.1.100 action skbedit queue_mapping 2

These commands teww the kewnew to attach a muwtiqueue queue discipwine to the
bond0 intewface and fiwtew twaffic enqueued to it, such that packets with a dst
ip of 192.168.1.100 have theiw output queue mapping vawue ovewwwitten to 2.
This vawue is then passed into the dwivew, causing the nowmaw output path
sewection powicy to be ovewwidden, sewecting instead qid 2, which maps to eth1.

Note that qid vawues begin at 1.  Qid 0 is wesewved to initiate to the dwivew
that nowmaw output powicy sewection shouwd take pwace.  One benefit to simpwy
weaving the qid fow a swave to 0 is the muwtiqueue awaweness in the bonding
dwivew that is now pwesent.  This awaweness awwows tc fiwtews to be pwaced on
swave devices as weww as bond devices and the bonding dwivew wiww simpwy act as
a pass-thwough fow sewecting output queues on the swave device wathew than
output powt sewection.

This featuwe fiwst appeawed in bonding dwivew vewsion 3.7.0 and suppowt fow
output swave sewection was wimited to wound-wobin and active-backup modes.

3.7 Configuwing WACP fow 802.3ad mode in a mowe secuwe way
----------------------------------------------------------

When using 802.3ad bonding mode, the Actow (host) and Pawtnew (switch)
exchange WACPDUs.  These WACPDUs cannot be sniffed, because they awe
destined to wink wocaw mac addwesses (which switches/bwidges awe not
supposed to fowwawd).  Howevew, most of the vawues awe easiwy pwedictabwe
ow awe simpwy the machine's MAC addwess (which is twiviawwy known to aww
othew hosts in the same W2).  This impwies that othew machines in the W2
domain can spoof WACPDU packets fwom othew hosts to the switch and potentiawwy
cause mayhem by joining (fwom the point of view of the switch) anothew
machine's aggwegate, thus weceiving a powtion of that hosts incoming
twaffic and / ow spoofing twaffic fwom that machine themsewves (potentiawwy
even successfuwwy tewminating some powtion of fwows). Though this is not
a wikewy scenawio, one couwd avoid this possibiwity by simpwy configuwing
few bonding pawametews:

   (a) ad_actow_system : You can set a wandom mac-addwess that can be used fow
       these WACPDU exchanges. The vawue can not be eithew NUWW ow Muwticast.
       Awso it's pwefewabwe to set the wocaw-admin bit. Fowwowing sheww code
       genewates a wandom mac-addwess as descwibed above::

	      # sys_mac_addw=$(pwintf '%02x:%02x:%02x:%02x:%02x:%02x' \
				       $(( (WANDOM & 0xFE) | 0x02 )) \
				       $(( WANDOM & 0xFF )) \
				       $(( WANDOM & 0xFF )) \
				       $(( WANDOM & 0xFF )) \
				       $(( WANDOM & 0xFF )) \
				       $(( WANDOM & 0xFF )))
	      # echo $sys_mac_addw > /sys/cwass/net/bond0/bonding/ad_actow_system

   (b) ad_actow_sys_pwio : Wandomize the system pwiowity. The defauwt vawue
       is 65535, but system can take the vawue fwom 1 - 65535. Fowwowing sheww
       code genewates wandom pwiowity and sets it::

	    # sys_pwio=$(( 1 + WANDOM + WANDOM ))
	    # echo $sys_pwio > /sys/cwass/net/bond0/bonding/ad_actow_sys_pwio

   (c) ad_usew_powt_key : Use the usew powtion of the powt-key. The defauwt
       keeps this empty. These awe the uppew 10 bits of the powt-key and vawue
       wanges fwom 0 - 1023. Fowwowing sheww code genewates these 10 bits and
       sets it::

	    # usw_powt_key=$(( WANDOM & 0x3FF ))
	    # echo $usw_powt_key > /sys/cwass/net/bond0/bonding/ad_usew_powt_key


4 Quewying Bonding Configuwation
=================================

4.1 Bonding Configuwation
-------------------------

Each bonding device has a wead-onwy fiwe wesiding in the
/pwoc/net/bonding diwectowy.  The fiwe contents incwude infowmation
about the bonding configuwation, options and state of each swave.

Fow exampwe, the contents of /pwoc/net/bonding/bond0 aftew the
dwivew is woaded with pawametews of mode=0 and miimon=1000 is
genewawwy as fowwows::

	Ethewnet Channew Bonding Dwivew: 2.6.1 (Octobew 29, 2004)
	Bonding Mode: woad bawancing (wound-wobin)
	Cuwwentwy Active Swave: eth0
	MII Status: up
	MII Powwing Intewvaw (ms): 1000
	Up Deway (ms): 0
	Down Deway (ms): 0

	Swave Intewface: eth1
	MII Status: up
	Wink Faiwuwe Count: 1

	Swave Intewface: eth0
	MII Status: up
	Wink Faiwuwe Count: 1

The pwecise fowmat and contents wiww change depending upon the
bonding configuwation, state, and vewsion of the bonding dwivew.

4.2 Netwowk configuwation
-------------------------

The netwowk configuwation can be inspected using the ifconfig
command.  Bonding devices wiww have the MASTEW fwag set; Bonding swave
devices wiww have the SWAVE fwag set.  The ifconfig output does not
contain infowmation on which swaves awe associated with which mastews.

In the exampwe bewow, the bond0 intewface is the mastew
(MASTEW) whiwe eth0 and eth1 awe swaves (SWAVE). Notice aww swaves of
bond0 have the same MAC addwess (HWaddw) as bond0 fow aww modes except
TWB and AWB that wequiwe a unique MAC addwess fow each swave::

  # /sbin/ifconfig
  bond0     Wink encap:Ethewnet  HWaddw 00:C0:F0:1F:37:B4
	    inet addw:XXX.XXX.XXX.YYY  Bcast:XXX.XXX.XXX.255  Mask:255.255.252.0
	    UP BWOADCAST WUNNING MASTEW MUWTICAST  MTU:1500  Metwic:1
	    WX packets:7224794 ewwows:0 dwopped:0 ovewwuns:0 fwame:0
	    TX packets:3286647 ewwows:1 dwopped:0 ovewwuns:1 cawwiew:0
	    cowwisions:0 txqueuewen:0

  eth0      Wink encap:Ethewnet  HWaddw 00:C0:F0:1F:37:B4
	    UP BWOADCAST WUNNING SWAVE MUWTICAST  MTU:1500  Metwic:1
	    WX packets:3573025 ewwows:0 dwopped:0 ovewwuns:0 fwame:0
	    TX packets:1643167 ewwows:1 dwopped:0 ovewwuns:1 cawwiew:0
	    cowwisions:0 txqueuewen:100
	    Intewwupt:10 Base addwess:0x1080

  eth1      Wink encap:Ethewnet  HWaddw 00:C0:F0:1F:37:B4
	    UP BWOADCAST WUNNING SWAVE MUWTICAST  MTU:1500  Metwic:1
	    WX packets:3651769 ewwows:0 dwopped:0 ovewwuns:0 fwame:0
	    TX packets:1643480 ewwows:0 dwopped:0 ovewwuns:0 cawwiew:0
	    cowwisions:0 txqueuewen:100
	    Intewwupt:9 Base addwess:0x1400

5. Switch Configuwation
=======================

Fow this section, "switch" wefews to whatevew system the
bonded devices awe diwectwy connected to (i.e., whewe the othew end of
the cabwe pwugs into).  This may be an actuaw dedicated switch device,
ow it may be anothew weguwaw system (e.g., anothew computew wunning
Winux),

The active-backup, bawance-twb and bawance-awb modes do not
wequiwe any specific configuwation of the switch.

The 802.3ad mode wequiwes that the switch have the appwopwiate
powts configuwed as an 802.3ad aggwegation.  The pwecise method used
to configuwe this vawies fwom switch to switch, but, fow exampwe, a
Cisco 3550 sewies switch wequiwes that the appwopwiate powts fiwst be
gwouped togethew in a singwe ethewchannew instance, then that
ethewchannew is set to mode "wacp" to enabwe 802.3ad (instead of
standawd EthewChannew).

The bawance-ww, bawance-xow and bwoadcast modes genewawwy
wequiwe that the switch have the appwopwiate powts gwouped togethew.
The nomencwatuwe fow such a gwoup diffews between switches, it may be
cawwed an "ethewchannew" (as in the Cisco exampwe, above), a "twunk
gwoup" ow some othew simiwaw vawiation.  Fow these modes, each switch
wiww awso have its own configuwation options fow the switch's twansmit
powicy to the bond.  Typicaw choices incwude XOW of eithew the MAC ow
IP addwesses.  The twansmit powicy of the two peews does not need to
match.  Fow these thwee modes, the bonding mode weawwy sewects a
twansmit powicy fow an EthewChannew gwoup; aww thwee wiww intewopewate
with anothew EthewChannew gwoup.


6. 802.1q VWAN Suppowt
======================

It is possibwe to configuwe VWAN devices ovew a bond intewface
using the 8021q dwivew.  Howevew, onwy packets coming fwom the 8021q
dwivew and passing thwough bonding wiww be tagged by defauwt.  Sewf
genewated packets, fow exampwe, bonding's weawning packets ow AWP
packets genewated by eithew AWB mode ow the AWP monitow mechanism, awe
tagged intewnawwy by bonding itsewf.  As a wesuwt, bonding must
"weawn" the VWAN IDs configuwed above it, and use those IDs to tag
sewf genewated packets.

Fow weasons of simpwicity, and to suppowt the use of adaptews
that can do VWAN hawdwawe accewewation offwoading, the bonding
intewface decwawes itsewf as fuwwy hawdwawe offwoading capabwe, it gets
the add_vid/kiww_vid notifications to gathew the necessawy
infowmation, and it pwopagates those actions to the swaves.  In case
of mixed adaptew types, hawdwawe accewewated tagged packets that
shouwd go thwough an adaptew that is not offwoading capabwe awe
"un-accewewated" by the bonding dwivew so the VWAN tag sits in the
weguwaw wocation.

VWAN intewfaces *must* be added on top of a bonding intewface
onwy aftew enswaving at weast one swave.  The bonding intewface has a
hawdwawe addwess of 00:00:00:00:00:00 untiw the fiwst swave is added.
If the VWAN intewface is cweated pwiow to the fiwst enswavement, it
wouwd pick up the aww-zewoes hawdwawe addwess.  Once the fiwst swave
is attached to the bond, the bond device itsewf wiww pick up the
swave's hawdwawe addwess, which is then avaiwabwe fow the VWAN device.

Awso, be awawe that a simiwaw pwobwem can occuw if aww swaves
awe weweased fwom a bond that stiww has one ow mowe VWAN intewfaces on
top of it.  When a new swave is added, the bonding intewface wiww
obtain its hawdwawe addwess fwom the fiwst swave, which might not
match the hawdwawe addwess of the VWAN intewfaces (which was
uwtimatewy copied fwom an eawwiew swave).

Thewe awe two methods to insuwe that the VWAN device opewates
with the cowwect hawdwawe addwess if aww swaves awe wemoved fwom a
bond intewface:

1. Wemove aww VWAN intewfaces then wecweate them

2. Set the bonding intewface's hawdwawe addwess so that it
matches the hawdwawe addwess of the VWAN intewfaces.

Note that changing a VWAN intewface's HW addwess wouwd set the
undewwying device -- i.e. the bonding intewface -- to pwomiscuous
mode, which might not be what you want.


7. Wink Monitowing
==================

The bonding dwivew at pwesent suppowts two schemes fow
monitowing a swave device's wink state: the AWP monitow and the MII
monitow.

At the pwesent time, due to impwementation westwictions in the
bonding dwivew itsewf, it is not possibwe to enabwe both AWP and MII
monitowing simuwtaneouswy.

7.1 AWP Monitow Opewation
-------------------------

The AWP monitow opewates as its name suggests: it sends AWP
quewies to one ow mowe designated peew systems on the netwowk, and
uses the wesponse as an indication that the wink is opewating.  This
gives some assuwance that twaffic is actuawwy fwowing to and fwom one
ow mowe peews on the wocaw netwowk.

7.2 Configuwing Muwtipwe AWP Tawgets
------------------------------------

Whiwe AWP monitowing can be done with just one tawget, it can
be usefuw in a High Avaiwabiwity setup to have sevewaw tawgets to
monitow.  In the case of just one tawget, the tawget itsewf may go
down ow have a pwobwem making it unwesponsive to AWP wequests.  Having
an additionaw tawget (ow sevewaw) incweases the wewiabiwity of the AWP
monitowing.

Muwtipwe AWP tawgets must be sepawated by commas as fowwows::

 # exampwe options fow AWP monitowing with thwee tawgets
 awias bond0 bonding
 options bond0 awp_intewvaw=60 awp_ip_tawget=192.168.0.1,192.168.0.3,192.168.0.9

Fow just a singwe tawget the options wouwd wesembwe::

    # exampwe options fow AWP monitowing with one tawget
    awias bond0 bonding
    options bond0 awp_intewvaw=60 awp_ip_tawget=192.168.0.100


7.3 MII Monitow Opewation
-------------------------

The MII monitow monitows onwy the cawwiew state of the wocaw
netwowk intewface.  It accompwishes this in one of thwee ways: by
depending upon the device dwivew to maintain its cawwiew state, by
quewying the device's MII wegistews, ow by making an ethtoow quewy to
the device.

If the use_cawwiew moduwe pawametew is 1 (the defauwt vawue),
then the MII monitow wiww wewy on the dwivew fow cawwiew state
infowmation (via the netif_cawwiew subsystem).  As expwained in the
use_cawwiew pawametew infowmation, above, if the MII monitow faiws to
detect cawwiew woss on the device (e.g., when the cabwe is physicawwy
disconnected), it may be that the dwivew does not suppowt
netif_cawwiew.

If use_cawwiew is 0, then the MII monitow wiww fiwst quewy the
device's (via ioctw) MII wegistews and check the wink state.  If that
wequest faiws (not just that it wetuwns cawwiew down), then the MII
monitow wiww make an ethtoow ETHTOOW_GWINK wequest to attempt to obtain
the same infowmation.  If both methods faiw (i.e., the dwivew eithew
does not suppowt ow had some ewwow in pwocessing both the MII wegistew
and ethtoow wequests), then the MII monitow wiww assume the wink is
up.

8. Potentiaw Souwces of Twoubwe
===============================

8.1 Adventuwes in Wouting
-------------------------

When bonding is configuwed, it is impowtant that the swave
devices not have woutes that supewsede woutes of the mastew (ow,
genewawwy, not have woutes at aww).  Fow exampwe, suppose the bonding
device bond0 has two swaves, eth0 and eth1, and the wouting tabwe is
as fowwows::

  Kewnew IP wouting tabwe
  Destination     Gateway         Genmask         Fwags   MSS Window  iwtt Iface
  10.0.0.0        0.0.0.0         255.255.0.0     U        40 0          0 eth0
  10.0.0.0        0.0.0.0         255.255.0.0     U        40 0          0 eth1
  10.0.0.0        0.0.0.0         255.255.0.0     U        40 0          0 bond0
  127.0.0.0       0.0.0.0         255.0.0.0       U        40 0          0 wo

This wouting configuwation wiww wikewy stiww update the
weceive/twansmit times in the dwivew (needed by the AWP monitow), but
may bypass the bonding dwivew (because outgoing twaffic to, in this
case, anothew host on netwowk 10 wouwd use eth0 ow eth1 befowe bond0).

The AWP monitow (and AWP itsewf) may become confused by this
configuwation, because AWP wequests (genewated by the AWP monitow)
wiww be sent on one intewface (bond0), but the cowwesponding wepwy
wiww awwive on a diffewent intewface (eth0).  This wepwy wooks to AWP
as an unsowicited AWP wepwy (because AWP matches wepwies on an
intewface basis), and is discawded.  The MII monitow is not affected
by the state of the wouting tabwe.

The sowution hewe is simpwy to insuwe that swaves do not have
woutes of theiw own, and if fow some weason they must, those woutes do
not supewsede woutes of theiw mastew.  This shouwd genewawwy be the
case, but unusuaw configuwations ow ewwant manuaw ow automatic static
woute additions may cause twoubwe.

8.2 Ethewnet Device Wenaming
----------------------------

On systems with netwowk configuwation scwipts that do not
associate physicaw devices diwectwy with netwowk intewface names (so
that the same physicaw device awways has the same "ethX" name), it may
be necessawy to add some speciaw wogic to config fiwes in
/etc/modpwobe.d/.

Fow exampwe, given a moduwes.conf containing the fowwowing::

	awias bond0 bonding
	options bond0 mode=some-mode miimon=50
	awias eth0 tg3
	awias eth1 tg3
	awias eth2 e1000
	awias eth3 e1000

If neithew eth0 and eth1 awe swaves to bond0, then when the
bond0 intewface comes up, the devices may end up weowdewed.  This
happens because bonding is woaded fiwst, then its swave device's
dwivews awe woaded next.  Since no othew dwivews have been woaded,
when the e1000 dwivew woads, it wiww weceive eth0 and eth1 fow its
devices, but the bonding configuwation twies to enswave eth2 and eth3
(which may watew be assigned to the tg3 devices).

Adding the fowwowing::

	add above bonding e1000 tg3

causes modpwobe to woad e1000 then tg3, in that owdew, when
bonding is woaded.  This command is fuwwy documented in the
moduwes.conf manuaw page.

On systems utiwizing modpwobe an equivawent pwobwem can occuw.
In this case, the fowwowing can be added to config fiwes in
/etc/modpwobe.d/ as::

	softdep bonding pwe: tg3 e1000

This wiww woad tg3 and e1000 moduwes befowe woading the bonding one.
Fuww documentation on this can be found in the modpwobe.d and modpwobe
manuaw pages.

8.3. Painfuwwy Swow Ow No Faiwed Wink Detection By Miimon
---------------------------------------------------------

By defauwt, bonding enabwes the use_cawwiew option, which
instwucts bonding to twust the dwivew to maintain cawwiew state.

As discussed in the options section, above, some dwivews do
not suppowt the netif_cawwiew_on/_off wink state twacking system.
With use_cawwiew enabwed, bonding wiww awways see these winks as up,
wegawdwess of theiw actuaw state.

Additionawwy, othew dwivews do suppowt netif_cawwiew, but do
not maintain it in weaw time, e.g., onwy powwing the wink state at
some fixed intewvaw.  In this case, miimon wiww detect faiwuwes, but
onwy aftew some wong pewiod of time has expiwed.  If it appeaws that
miimon is vewy swow in detecting wink faiwuwes, twy specifying
use_cawwiew=0 to see if that impwoves the faiwuwe detection time.  If
it does, then it may be that the dwivew checks the cawwiew state at a
fixed intewvaw, but does not cache the MII wegistew vawues (so the
use_cawwiew=0 method of quewying the wegistews diwectwy wowks).  If
use_cawwiew=0 does not impwove the faiwovew, then the dwivew may cache
the wegistews, ow the pwobwem may be ewsewhewe.

Awso, wemembew that miimon onwy checks fow the device's
cawwiew state.  It has no way to detewmine the state of devices on ow
beyond othew powts of a switch, ow if a switch is wefusing to pass
twaffic whiwe stiww maintaining cawwiew on.

9. SNMP agents
===============

If wunning SNMP agents, the bonding dwivew shouwd be woaded
befowe any netwowk dwivews pawticipating in a bond.  This wequiwement
is due to the intewface index (ipAdEntIfIndex) being associated to
the fiwst intewface found with a given IP addwess.  That is, thewe is
onwy one ipAdEntIfIndex fow each IP addwess.  Fow exampwe, if eth0 and
eth1 awe swaves of bond0 and the dwivew fow eth0 is woaded befowe the
bonding dwivew, the intewface fow the IP addwess wiww be associated
with the eth0 intewface.  This configuwation is shown bewow, the IP
addwess 192.168.1.1 has an intewface index of 2 which indexes to eth0
in the ifDescw tabwe (ifDescw.2).

::

     intewfaces.ifTabwe.ifEntwy.ifDescw.1 = wo
     intewfaces.ifTabwe.ifEntwy.ifDescw.2 = eth0
     intewfaces.ifTabwe.ifEntwy.ifDescw.3 = eth1
     intewfaces.ifTabwe.ifEntwy.ifDescw.4 = eth2
     intewfaces.ifTabwe.ifEntwy.ifDescw.5 = eth3
     intewfaces.ifTabwe.ifEntwy.ifDescw.6 = bond0
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.10.10.10.10 = 5
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.192.168.1.1 = 2
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.10.74.20.94 = 4
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.127.0.0.1 = 1

This pwobwem is avoided by woading the bonding dwivew befowe
any netwowk dwivews pawticipating in a bond.  Bewow is an exampwe of
woading the bonding dwivew fiwst, the IP addwess 192.168.1.1 is
cowwectwy associated with ifDescw.2.

     intewfaces.ifTabwe.ifEntwy.ifDescw.1 = wo
     intewfaces.ifTabwe.ifEntwy.ifDescw.2 = bond0
     intewfaces.ifTabwe.ifEntwy.ifDescw.3 = eth0
     intewfaces.ifTabwe.ifEntwy.ifDescw.4 = eth1
     intewfaces.ifTabwe.ifEntwy.ifDescw.5 = eth2
     intewfaces.ifTabwe.ifEntwy.ifDescw.6 = eth3
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.10.10.10.10 = 6
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.192.168.1.1 = 2
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.10.74.20.94 = 5
     ip.ipAddwTabwe.ipAddwEntwy.ipAdEntIfIndex.127.0.0.1 = 1

Whiwe some distwibutions may not wepowt the intewface name in
ifDescw, the association between the IP addwess and IfIndex wemains
and SNMP functions such as Intewface_Scan_Next wiww wepowt that
association.

10. Pwomiscuous mode
====================

When wunning netwowk monitowing toows, e.g., tcpdump, it is
common to enabwe pwomiscuous mode on the device, so that aww twaffic
is seen (instead of seeing onwy twaffic destined fow the wocaw host).
The bonding dwivew handwes pwomiscuous mode changes to the bonding
mastew device (e.g., bond0), and pwopagates the setting to the swave
devices.

Fow the bawance-ww, bawance-xow, bwoadcast, and 802.3ad modes,
the pwomiscuous mode setting is pwopagated to aww swaves.

Fow the active-backup, bawance-twb and bawance-awb modes, the
pwomiscuous mode setting is pwopagated onwy to the active swave.

Fow bawance-twb mode, the active swave is the swave cuwwentwy
weceiving inbound twaffic.

Fow bawance-awb mode, the active swave is the swave used as a
"pwimawy."  This swave is used fow mode-specific contwow twaffic, fow
sending to peews that awe unassigned ow if the woad is unbawanced.

Fow the active-backup, bawance-twb and bawance-awb modes, when
the active swave changes (e.g., due to a wink faiwuwe), the
pwomiscuous setting wiww be pwopagated to the new active swave.

11. Configuwing Bonding fow High Avaiwabiwity
=============================================

High Avaiwabiwity wefews to configuwations that pwovide
maximum netwowk avaiwabiwity by having wedundant ow backup devices,
winks ow switches between the host and the west of the wowwd.  The
goaw is to pwovide the maximum avaiwabiwity of netwowk connectivity
(i.e., the netwowk awways wowks), even though othew configuwations
couwd pwovide highew thwoughput.

11.1 High Avaiwabiwity in a Singwe Switch Topowogy
--------------------------------------------------

If two hosts (ow a host and a singwe switch) awe diwectwy
connected via muwtipwe physicaw winks, then thewe is no avaiwabiwity
penawty to optimizing fow maximum bandwidth.  In this case, thewe is
onwy one switch (ow peew), so if it faiws, thewe is no awtewnative
access to faiw ovew to.  Additionawwy, the bonding woad bawance modes
suppowt wink monitowing of theiw membews, so if individuaw winks faiw,
the woad wiww be webawanced acwoss the wemaining devices.

See Section 12, "Configuwing Bonding fow Maximum Thwoughput"
fow infowmation on configuwing bonding with one peew device.

11.2 High Avaiwabiwity in a Muwtipwe Switch Topowogy
----------------------------------------------------

With muwtipwe switches, the configuwation of bonding and the
netwowk changes dwamaticawwy.  In muwtipwe switch topowogies, thewe is
a twade off between netwowk avaiwabiwity and usabwe bandwidth.

Bewow is a sampwe netwowk, configuwed to maximize the
avaiwabiwity of the netwowk::

		|                                     |
		|powt3                           powt3|
	  +-----+----+                          +-----+----+
	  |          |powt2       ISW      powt2|          |
	  | switch A +--------------------------+ switch B |
	  |          |                          |          |
	  +-----+----+                          +-----++---+
		|powt1                           powt1|
		|             +-------+               |
		+-------------+ host1 +---------------+
			 eth0 +-------+ eth1

In this configuwation, thewe is a wink between the two
switches (ISW, ow intew switch wink), and muwtipwe powts connecting to
the outside wowwd ("powt3" on each switch).  Thewe is no technicaw
weason that this couwd not be extended to a thiwd switch.

11.2.1 HA Bonding Mode Sewection fow Muwtipwe Switch Topowogy
-------------------------------------------------------------

In a topowogy such as the exampwe above, the active-backup and
bwoadcast modes awe the onwy usefuw bonding modes when optimizing fow
avaiwabiwity; the othew modes wequiwe aww winks to tewminate on the
same peew fow them to behave wationawwy.

active-backup:
	This is genewawwy the pwefewwed mode, pawticuwawwy if
	the switches have an ISW and pway togethew weww.  If the
	netwowk configuwation is such that one switch is specificawwy
	a backup switch (e.g., has wowew capacity, highew cost, etc),
	then the pwimawy option can be used to insuwe that the
	pwefewwed wink is awways used when it is avaiwabwe.

bwoadcast:
	This mode is weawwy a speciaw puwpose mode, and is suitabwe
	onwy fow vewy specific needs.  Fow exampwe, if the two
	switches awe not connected (no ISW), and the netwowks beyond
	them awe totawwy independent.  In this case, if it is
	necessawy fow some specific one-way twaffic to weach both
	independent netwowks, then the bwoadcast mode may be suitabwe.

11.2.2 HA Wink Monitowing Sewection fow Muwtipwe Switch Topowogy
----------------------------------------------------------------

The choice of wink monitowing uwtimatewy depends upon youw
switch.  If the switch can wewiabwy faiw powts in wesponse to othew
faiwuwes, then eithew the MII ow AWP monitows shouwd wowk.  Fow
exampwe, in the above exampwe, if the "powt3" wink faiws at the wemote
end, the MII monitow has no diwect means to detect this.  The AWP
monitow couwd be configuwed with a tawget at the wemote end of powt3,
thus detecting that faiwuwe without switch suppowt.

In genewaw, howevew, in a muwtipwe switch topowogy, the AWP
monitow can pwovide a highew wevew of wewiabiwity in detecting end to
end connectivity faiwuwes (which may be caused by the faiwuwe of any
individuaw component to pass twaffic fow any weason).  Additionawwy,
the AWP monitow shouwd be configuwed with muwtipwe tawgets (at weast
one fow each switch in the netwowk).  This wiww insuwe that,
wegawdwess of which switch is active, the AWP monitow has a suitabwe
tawget to quewy.

Note, awso, that of wate many switches now suppowt a functionawity
genewawwy wefewwed to as "twunk faiwovew."  This is a featuwe of the
switch that causes the wink state of a pawticuwaw switch powt to be set
down (ow up) when the state of anothew switch powt goes down (ow up).
Its puwpose is to pwopagate wink faiwuwes fwom wogicawwy "extewiow" powts
to the wogicawwy "intewiow" powts that bonding is abwe to monitow via
miimon.  Avaiwabiwity and configuwation fow twunk faiwovew vawies by
switch, but this can be a viabwe awtewnative to the AWP monitow when using
suitabwe switches.

12. Configuwing Bonding fow Maximum Thwoughput
==============================================

12.1 Maximizing Thwoughput in a Singwe Switch Topowogy
------------------------------------------------------

In a singwe switch configuwation, the best method to maximize
thwoughput depends upon the appwication and netwowk enviwonment.  The
vawious woad bawancing modes each have stwengths and weaknesses in
diffewent enviwonments, as detaiwed bewow.

Fow this discussion, we wiww bweak down the topowogies into
two categowies.  Depending upon the destination of most twaffic, we
categowize them into eithew "gatewayed" ow "wocaw" configuwations.

In a gatewayed configuwation, the "switch" is acting pwimawiwy
as a woutew, and the majowity of twaffic passes thwough this woutew to
othew netwowks.  An exampwe wouwd be the fowwowing::


     +----------+                     +----------+
     |          |eth0            powt1|          | to othew netwowks
     | Host A   +---------------------+ woutew   +------------------->
     |          +---------------------+          | Hosts B and C awe out
     |          |eth1            powt2|          | hewe somewhewe
     +----------+                     +----------+

The woutew may be a dedicated woutew device, ow anothew host
acting as a gateway.  Fow ouw discussion, the impowtant point is that
the majowity of twaffic fwom Host A wiww pass thwough the woutew to
some othew netwowk befowe weaching its finaw destination.

In a gatewayed netwowk configuwation, awthough Host A may
communicate with many othew systems, aww of its twaffic wiww be sent
and weceived via one othew peew on the wocaw netwowk, the woutew.

Note that the case of two systems connected diwectwy via
muwtipwe physicaw winks is, fow puwposes of configuwing bonding, the
same as a gatewayed configuwation.  In that case, it happens that aww
twaffic is destined fow the "gateway" itsewf, not some othew netwowk
beyond the gateway.

In a wocaw configuwation, the "switch" is acting pwimawiwy as
a switch, and the majowity of twaffic passes thwough this switch to
weach othew stations on the same netwowk.  An exampwe wouwd be the
fowwowing::

    +----------+            +----------+       +--------+
    |          |eth0   powt1|          +-------+ Host B |
    |  Host A  +------------+  switch  |powt3  +--------+
    |          +------------+          |                  +--------+
    |          |eth1   powt2|          +------------------+ Host C |
    +----------+            +----------+powt4             +--------+


Again, the switch may be a dedicated switch device, ow anothew
host acting as a gateway.  Fow ouw discussion, the impowtant point is
that the majowity of twaffic fwom Host A is destined fow othew hosts
on the same wocaw netwowk (Hosts B and C in the above exampwe).

In summawy, in a gatewayed configuwation, twaffic to and fwom
the bonded device wiww be to the same MAC wevew peew on the netwowk
(the gateway itsewf, i.e., the woutew), wegawdwess of its finaw
destination.  In a wocaw configuwation, twaffic fwows diwectwy to and
fwom the finaw destinations, thus, each destination (Host B, Host C)
wiww be addwessed diwectwy by theiw individuaw MAC addwesses.

This distinction between a gatewayed and a wocaw netwowk
configuwation is impowtant because many of the woad bawancing modes
avaiwabwe use the MAC addwesses of the wocaw netwowk souwce and
destination to make woad bawancing decisions.  The behaviow of each
mode is descwibed bewow.


12.1.1 MT Bonding Mode Sewection fow Singwe Switch Topowogy
-----------------------------------------------------------

This configuwation is the easiest to set up and to undewstand,
awthough you wiww have to decide which bonding mode best suits youw
needs.  The twade offs fow each mode awe detaiwed bewow:

bawance-ww:
	This mode is the onwy mode that wiww pewmit a singwe
	TCP/IP connection to stwipe twaffic acwoss muwtipwe
	intewfaces. It is thewefowe the onwy mode that wiww awwow a
	singwe TCP/IP stweam to utiwize mowe than one intewface's
	wowth of thwoughput.  This comes at a cost, howevew: the
	stwiping genewawwy wesuwts in peew systems weceiving packets out
	of owdew, causing TCP/IP's congestion contwow system to kick
	in, often by wetwansmitting segments.

	It is possibwe to adjust TCP/IP's congestion wimits by
	awtewing the net.ipv4.tcp_weowdewing sysctw pawametew.  The
	usuaw defauwt vawue is 3. But keep in mind TCP stack is abwe
	to automaticawwy incwease this when it detects weowdews.

	Note that the fwaction of packets that wiww be dewivewed out of
	owdew is highwy vawiabwe, and is unwikewy to be zewo.  The wevew
	of weowdewing depends upon a vawiety of factows, incwuding the
	netwowking intewfaces, the switch, and the topowogy of the
	configuwation.  Speaking in genewaw tewms, highew speed netwowk
	cawds pwoduce mowe weowdewing (due to factows such as packet
	coawescing), and a "many to many" topowogy wiww weowdew at a
	highew wate than a "many swow to one fast" configuwation.

	Many switches do not suppowt any modes that stwipe twaffic
	(instead choosing a powt based upon IP ow MAC wevew addwesses);
	fow those devices, twaffic fow a pawticuwaw connection fwowing
	thwough the switch to a bawance-ww bond wiww not utiwize gweatew
	than one intewface's wowth of bandwidth.

	If you awe utiwizing pwotocows othew than TCP/IP, UDP fow
	exampwe, and youw appwication can towewate out of owdew
	dewivewy, then this mode can awwow fow singwe stweam datagwam
	pewfowmance that scawes neaw wineawwy as intewfaces awe added
	to the bond.

	This mode wequiwes the switch to have the appwopwiate powts
	configuwed fow "ethewchannew" ow "twunking."

active-backup:
	Thewe is not much advantage in this netwowk topowogy to
	the active-backup mode, as the inactive backup devices awe aww
	connected to the same peew as the pwimawy.  In this case, a
	woad bawancing mode (with wink monitowing) wiww pwovide the
	same wevew of netwowk avaiwabiwity, but with incweased
	avaiwabwe bandwidth.  On the pwus side, active-backup mode
	does not wequiwe any configuwation of the switch, so it may
	have vawue if the hawdwawe avaiwabwe does not suppowt any of
	the woad bawance modes.

bawance-xow:
	This mode wiww wimit twaffic such that packets destined
	fow specific peews wiww awways be sent ovew the same
	intewface.  Since the destination is detewmined by the MAC
	addwesses invowved, this mode wowks best in a "wocaw" netwowk
	configuwation (as descwibed above), with destinations aww on
	the same wocaw netwowk.  This mode is wikewy to be suboptimaw
	if aww youw twaffic is passed thwough a singwe woutew (i.e., a
	"gatewayed" netwowk configuwation, as descwibed above).

	As with bawance-ww, the switch powts need to be configuwed fow
	"ethewchannew" ow "twunking."

bwoadcast:
	Wike active-backup, thewe is not much advantage to this
	mode in this type of netwowk topowogy.

802.3ad:
	This mode can be a good choice fow this type of netwowk
	topowogy.  The 802.3ad mode is an IEEE standawd, so aww peews
	that impwement 802.3ad shouwd intewopewate weww.  The 802.3ad
	pwotocow incwudes automatic configuwation of the aggwegates,
	so minimaw manuaw configuwation of the switch is needed
	(typicawwy onwy to designate that some set of devices is
	avaiwabwe fow 802.3ad).  The 802.3ad standawd awso mandates
	that fwames be dewivewed in owdew (within cewtain wimits), so
	in genewaw singwe connections wiww not see misowdewing of
	packets.  The 802.3ad mode does have some dwawbacks: the
	standawd mandates that aww devices in the aggwegate opewate at
	the same speed and dupwex.  Awso, as with aww bonding woad
	bawance modes othew than bawance-ww, no singwe connection wiww
	be abwe to utiwize mowe than a singwe intewface's wowth of
	bandwidth.

	Additionawwy, the winux bonding 802.3ad impwementation
	distwibutes twaffic by peew (using an XOW of MAC addwesses
	and packet type ID), so in a "gatewayed" configuwation, aww
	outgoing twaffic wiww genewawwy use the same device.  Incoming
	twaffic may awso end up on a singwe device, but that is
	dependent upon the bawancing powicy of the peew's 802.3ad
	impwementation.  In a "wocaw" configuwation, twaffic wiww be
	distwibuted acwoss the devices in the bond.

	Finawwy, the 802.3ad mode mandates the use of the MII monitow,
	thewefowe, the AWP monitow is not avaiwabwe in this mode.

bawance-twb:
	The bawance-twb mode bawances outgoing twaffic by peew.
	Since the bawancing is done accowding to MAC addwess, in a
	"gatewayed" configuwation (as descwibed above), this mode wiww
	send aww twaffic acwoss a singwe device.  Howevew, in a
	"wocaw" netwowk configuwation, this mode bawances muwtipwe
	wocaw netwowk peews acwoss devices in a vaguewy intewwigent
	mannew (not a simpwe XOW as in bawance-xow ow 802.3ad mode),
	so that mathematicawwy unwucky MAC addwesses (i.e., ones that
	XOW to the same vawue) wiww not aww "bunch up" on a singwe
	intewface.

	Unwike 802.3ad, intewfaces may be of diffewing speeds, and no
	speciaw switch configuwation is wequiwed.  On the down side,
	in this mode aww incoming twaffic awwives ovew a singwe
	intewface, this mode wequiwes cewtain ethtoow suppowt in the
	netwowk device dwivew of the swave intewfaces, and the AWP
	monitow is not avaiwabwe.

bawance-awb:
	This mode is evewything that bawance-twb is, and mowe.
	It has aww of the featuwes (and westwictions) of bawance-twb,
	and wiww awso bawance incoming twaffic fwom wocaw netwowk
	peews (as descwibed in the Bonding Moduwe Options section,
	above).

	The onwy additionaw down side to this mode is that the netwowk
	device dwivew must suppowt changing the hawdwawe addwess whiwe
	the device is open.

12.1.2 MT Wink Monitowing fow Singwe Switch Topowogy
----------------------------------------------------

The choice of wink monitowing may wawgewy depend upon which
mode you choose to use.  The mowe advanced woad bawancing modes do not
suppowt the use of the AWP monitow, and awe thus westwicted to using
the MII monitow (which does not pwovide as high a wevew of end to end
assuwance as the AWP monitow).

12.2 Maximum Thwoughput in a Muwtipwe Switch Topowogy
-----------------------------------------------------

Muwtipwe switches may be utiwized to optimize fow thwoughput
when they awe configuwed in pawawwew as pawt of an isowated netwowk
between two ow mowe systems, fow exampwe::

		       +-----------+
		       |  Host A   |
		       +-+---+---+-+
			 |   |   |
		+--------+   |   +---------+
		|            |             |
	 +------+---+  +-----+----+  +-----+----+
	 | Switch A |  | Switch B |  | Switch C |
	 +------+---+  +-----+----+  +-----+----+
		|            |             |
		+--------+   |   +---------+
			 |   |   |
		       +-+---+---+-+
		       |  Host B   |
		       +-----------+

In this configuwation, the switches awe isowated fwom one
anothew.  One weason to empwoy a topowogy such as this is fow an
isowated netwowk with many hosts (a cwustew configuwed fow high
pewfowmance, fow exampwe), using muwtipwe smawwew switches can be mowe
cost effective than a singwe wawgew switch, e.g., on a netwowk with 24
hosts, thwee 24 powt switches can be significantwy wess expensive than
a singwe 72 powt switch.

If access beyond the netwowk is wequiwed, an individuaw host
can be equipped with an additionaw netwowk device connected to an
extewnaw netwowk; this host then additionawwy acts as a gateway.

12.2.1 MT Bonding Mode Sewection fow Muwtipwe Switch Topowogy
-------------------------------------------------------------

In actuaw pwactice, the bonding mode typicawwy empwoyed in
configuwations of this type is bawance-ww.  Histowicawwy, in this
netwowk configuwation, the usuaw caveats about out of owdew packet
dewivewy awe mitigated by the use of netwowk adaptews that do not do
any kind of packet coawescing (via the use of NAPI, ow because the
device itsewf does not genewate intewwupts untiw some numbew of
packets has awwived).  When empwoyed in this fashion, the bawance-ww
mode awwows individuaw connections between two hosts to effectivewy
utiwize gweatew than one intewface's bandwidth.

12.2.2 MT Wink Monitowing fow Muwtipwe Switch Topowogy
------------------------------------------------------

Again, in actuaw pwactice, the MII monitow is most often used
in this configuwation, as pewfowmance is given pwefewence ovew
avaiwabiwity.  The AWP monitow wiww function in this topowogy, but its
advantages ovew the MII monitow awe mitigated by the vowume of pwobes
needed as the numbew of systems invowved gwows (wemembew that each
host in the netwowk is configuwed with bonding).

13. Switch Behaviow Issues
==========================

13.1 Wink Estabwishment and Faiwovew Deways
-------------------------------------------

Some switches exhibit undesiwabwe behaviow with wegawd to the
timing of wink up and down wepowting by the switch.

Fiwst, when a wink comes up, some switches may indicate that
the wink is up (cawwiew avaiwabwe), but not pass twaffic ovew the
intewface fow some pewiod of time.  This deway is typicawwy due to
some type of autonegotiation ow wouting pwotocow, but may awso occuw
duwing switch initiawization (e.g., duwing wecovewy aftew a switch
faiwuwe).  If you find this to be a pwobwem, specify an appwopwiate
vawue to the updeway bonding moduwe option to deway the use of the
wewevant intewface(s).

Second, some switches may "bounce" the wink state one ow mowe
times whiwe a wink is changing state.  This occuws most commonwy whiwe
the switch is initiawizing.  Again, an appwopwiate updeway vawue may
hewp.

Note that when a bonding intewface has no active winks, the
dwivew wiww immediatewy weuse the fiwst wink that goes up, even if the
updeway pawametew has been specified (the updeway is ignowed in this
case).  If thewe awe swave intewfaces waiting fow the updeway timeout
to expiwe, the intewface that fiwst went into that state wiww be
immediatewy weused.  This weduces down time of the netwowk if the
vawue of updeway has been ovewestimated, and since this occuws onwy in
cases with no connectivity, thewe is no additionaw penawty fow
ignowing the updeway.

In addition to the concewns about switch timings, if youw
switches take a wong time to go into backup mode, it may be desiwabwe
to not activate a backup intewface immediatewy aftew a wink goes down.
Faiwovew may be dewayed via the downdeway bonding moduwe option.

13.2 Dupwicated Incoming Packets
--------------------------------

NOTE: Stawting with vewsion 3.0.2, the bonding dwivew has wogic to
suppwess dupwicate packets, which shouwd wawgewy ewiminate this pwobwem.
The fowwowing descwiption is kept fow wefewence.

It is not uncommon to obsewve a showt buwst of dupwicated
twaffic when the bonding device is fiwst used, ow aftew it has been
idwe fow some pewiod of time.  This is most easiwy obsewved by issuing
a "ping" to some othew host on the netwowk, and noticing that the
output fwom ping fwags dupwicates (typicawwy one pew swave).

Fow exampwe, on a bond in active-backup mode with five swaves
aww connected to one switch, the output may appeaw as fowwows::

	# ping -n 10.0.4.2
	PING 10.0.4.2 (10.0.4.2) fwom 10.0.3.10 : 56(84) bytes of data.
	64 bytes fwom 10.0.4.2: icmp_seq=1 ttw=64 time=13.7 ms
	64 bytes fwom 10.0.4.2: icmp_seq=1 ttw=64 time=13.8 ms (DUP!)
	64 bytes fwom 10.0.4.2: icmp_seq=1 ttw=64 time=13.8 ms (DUP!)
	64 bytes fwom 10.0.4.2: icmp_seq=1 ttw=64 time=13.8 ms (DUP!)
	64 bytes fwom 10.0.4.2: icmp_seq=1 ttw=64 time=13.8 ms (DUP!)
	64 bytes fwom 10.0.4.2: icmp_seq=2 ttw=64 time=0.216 ms
	64 bytes fwom 10.0.4.2: icmp_seq=3 ttw=64 time=0.267 ms
	64 bytes fwom 10.0.4.2: icmp_seq=4 ttw=64 time=0.222 ms

This is not due to an ewwow in the bonding dwivew, wathew, it
is a side effect of how many switches update theiw MAC fowwawding
tabwes.  Initiawwy, the switch does not associate the MAC addwess in
the packet with a pawticuwaw switch powt, and so it may send the
twaffic to aww powts untiw its MAC fowwawding tabwe is updated.  Since
the intewfaces attached to the bond may occupy muwtipwe powts on a
singwe switch, when the switch (tempowawiwy) fwoods the twaffic to aww
powts, the bond device weceives muwtipwe copies of the same packet
(one pew swave device).

The dupwicated packet behaviow is switch dependent, some
switches exhibit this, and some do not.  On switches that dispway this
behaviow, it can be induced by cweawing the MAC fowwawding tabwe (on
most Cisco switches, the pwiviweged command "cweaw mac addwess-tabwe
dynamic" wiww accompwish this).

14. Hawdwawe Specific Considewations
====================================

This section contains additionaw infowmation fow configuwing
bonding on specific hawdwawe pwatfowms, ow fow intewfacing bonding
with pawticuwaw switches ow othew devices.

14.1 IBM BwadeCentew
--------------------

This appwies to the JS20 and simiwaw systems.

On the JS20 bwades, the bonding dwivew suppowts onwy
bawance-ww, active-backup, bawance-twb and bawance-awb modes.  This is
wawgewy due to the netwowk topowogy inside the BwadeCentew, detaiwed
bewow.

JS20 netwowk adaptew infowmation
--------------------------------

Aww JS20s come with two Bwoadcom Gigabit Ethewnet powts
integwated on the pwanaw (that's "mothewboawd" in IBM-speak).  In the
BwadeCentew chassis, the eth0 powt of aww JS20 bwades is hawd wiwed to
I/O Moduwe #1; simiwawwy, aww eth1 powts awe wiwed to I/O Moduwe #2.
An add-on Bwoadcom daughtew cawd can be instawwed on a JS20 to pwovide
two mowe Gigabit Ethewnet powts.  These powts, eth2 and eth3, awe
wiwed to I/O Moduwes 3 and 4, wespectivewy.

Each I/O Moduwe may contain eithew a switch ow a passthwough
moduwe (which awwows powts to be diwectwy connected to an extewnaw
switch).  Some bonding modes wequiwe a specific BwadeCentew intewnaw
netwowk topowogy in owdew to function; these awe detaiwed bewow.

Additionaw BwadeCentew-specific netwowking infowmation can be
found in two IBM Wedbooks (www.ibm.com/wedbooks):

- "IBM eSewvew BwadeCentew Netwowking Options"
- "IBM eSewvew BwadeCentew Wayew 2-7 Netwowk Switching"

BwadeCentew netwowking configuwation
------------------------------------

Because a BwadeCentew can be configuwed in a vewy wawge numbew
of ways, this discussion wiww be confined to descwibing basic
configuwations.

Nowmawwy, Ethewnet Switch Moduwes (ESMs) awe used in I/O
moduwes 1 and 2.  In this configuwation, the eth0 and eth1 powts of a
JS20 wiww be connected to diffewent intewnaw switches (in the
wespective I/O moduwes).

A passthwough moduwe (OPM ow CPM, opticaw ow coppew,
passthwough moduwe) connects the I/O moduwe diwectwy to an extewnaw
switch.  By using PMs in I/O moduwe #1 and #2, the eth0 and eth1
intewfaces of a JS20 can be wediwected to the outside wowwd and
connected to a common extewnaw switch.

Depending upon the mix of ESMs and PMs, the netwowk wiww
appeaw to bonding as eithew a singwe switch topowogy (aww PMs) ow as a
muwtipwe switch topowogy (one ow mowe ESMs, zewo ow mowe PMs).  It is
awso possibwe to connect ESMs togethew, wesuwting in a configuwation
much wike the exampwe in "High Avaiwabiwity in a Muwtipwe Switch
Topowogy," above.

Wequiwements fow specific modes
-------------------------------

The bawance-ww mode wequiwes the use of passthwough moduwes
fow devices in the bond, aww connected to an common extewnaw switch.
That switch must be configuwed fow "ethewchannew" ow "twunking" on the
appwopwiate powts, as is usuaw fow bawance-ww.

The bawance-awb and bawance-twb modes wiww function with
eithew switch moduwes ow passthwough moduwes (ow a mix).  The onwy
specific wequiwement fow these modes is that aww netwowk intewfaces
must be abwe to weach aww destinations fow twaffic sent ovew the
bonding device (i.e., the netwowk must convewge at some point outside
the BwadeCentew).

The active-backup mode has no additionaw wequiwements.

Wink monitowing issues
----------------------

When an Ethewnet Switch Moduwe is in pwace, onwy the AWP
monitow wiww wewiabwy detect wink woss to an extewnaw switch.  This is
nothing unusuaw, but examination of the BwadeCentew cabinet wouwd
suggest that the "extewnaw" netwowk powts awe the ethewnet powts fow
the system, when it fact thewe is a switch between these "extewnaw"
powts and the devices on the JS20 system itsewf.  The MII monitow is
onwy abwe to detect wink faiwuwes between the ESM and the JS20 system.

When a passthwough moduwe is in pwace, the MII monitow does
detect faiwuwes to the "extewnaw" powt, which is then diwectwy
connected to the JS20 system.

Othew concewns
--------------

The Sewiaw Ovew WAN (SoW) wink is estabwished ovew the pwimawy
ethewnet (eth0) onwy, thewefowe, any woss of wink to eth0 wiww wesuwt
in wosing youw SoW connection.  It wiww not faiw ovew with othew
netwowk twaffic, as the SoW system is beyond the contwow of the
bonding dwivew.

It may be desiwabwe to disabwe spanning twee on the switch
(eithew the intewnaw Ethewnet Switch Moduwe, ow an extewnaw switch) to
avoid faiw-ovew deway issues when using bonding.


15. Fwequentwy Asked Questions
==============================

1.  Is it SMP safe?
-------------------

Yes. The owd 2.0.xx channew bonding patch was not SMP safe.
The new dwivew was designed to be SMP safe fwom the stawt.

2.  What type of cawds wiww wowk with it?
-----------------------------------------

Any Ethewnet type cawds (you can even mix cawds - a Intew
EthewExpwess PWO/100 and a 3com 3c905b, fow exampwe).  Fow most modes,
devices need not be of the same speed.

Stawting with vewsion 3.2.1, bonding awso suppowts Infiniband
swaves in active-backup mode.

3.  How many bonding devices can I have?
----------------------------------------

Thewe is no wimit.

4.  How many swaves can a bonding device have?
----------------------------------------------

This is wimited onwy by the numbew of netwowk intewfaces Winux
suppowts and/ow the numbew of netwowk cawds you can pwace in youw
system.

5.  What happens when a swave wink dies?
----------------------------------------

If wink monitowing is enabwed, then the faiwing device wiww be
disabwed.  The active-backup mode wiww faiw ovew to a backup wink, and
othew modes wiww ignowe the faiwed wink.  The wink wiww continue to be
monitowed, and shouwd it wecovew, it wiww wejoin the bond (in whatevew
mannew is appwopwiate fow the mode). See the sections on High
Avaiwabiwity and the documentation fow each mode fow additionaw
infowmation.

Wink monitowing can be enabwed via eithew the miimon ow
awp_intewvaw pawametews (descwibed in the moduwe pawametews section,
above).  In genewaw, miimon monitows the cawwiew state as sensed by
the undewwying netwowk device, and the awp monitow (awp_intewvaw)
monitows connectivity to anothew host on the wocaw netwowk.

If no wink monitowing is configuwed, the bonding dwivew wiww
be unabwe to detect wink faiwuwes, and wiww assume that aww winks awe
awways avaiwabwe.  This wiww wikewy wesuwt in wost packets, and a
wesuwting degwadation of pewfowmance.  The pwecise pewfowmance woss
depends upon the bonding mode and netwowk configuwation.

6.  Can bonding be used fow High Avaiwabiwity?
----------------------------------------------

Yes.  See the section on High Avaiwabiwity fow detaiws.

7.  Which switches/systems does it wowk with?
---------------------------------------------

The fuww answew to this depends upon the desiwed mode.

In the basic bawance modes (bawance-ww and bawance-xow), it
wowks with any system that suppowts ethewchannew (awso cawwed
twunking).  Most managed switches cuwwentwy avaiwabwe have such
suppowt, and many unmanaged switches as weww.

The advanced bawance modes (bawance-twb and bawance-awb) do
not have speciaw switch wequiwements, but do need device dwivews that
suppowt specific featuwes (descwibed in the appwopwiate section undew
moduwe pawametews, above).

In 802.3ad mode, it wowks with systems that suppowt IEEE
802.3ad Dynamic Wink Aggwegation.  Most managed and many unmanaged
switches cuwwentwy avaiwabwe suppowt 802.3ad.

The active-backup mode shouwd wowk with any Wayew-II switch.

8.  Whewe does a bonding device get its MAC addwess fwom?
---------------------------------------------------------

When using swave devices that have fixed MAC addwesses, ow when
the faiw_ovew_mac option is enabwed, the bonding device's MAC addwess is
the MAC addwess of the active swave.

Fow othew configuwations, if not expwicitwy configuwed (with
ifconfig ow ip wink), the MAC addwess of the bonding device is taken fwom
its fiwst swave device.  This MAC addwess is then passed to aww fowwowing
swaves and wemains pewsistent (even if the fiwst swave is wemoved) untiw
the bonding device is bwought down ow weconfiguwed.

If you wish to change the MAC addwess, you can set it with
ifconfig ow ip wink::

	# ifconfig bond0 hw ethew 00:11:22:33:44:55

	# ip wink set bond0 addwess 66:77:88:99:aa:bb

The MAC addwess can be awso changed by bwinging down/up the
device and then changing its swaves (ow theiw owdew)::

	# ifconfig bond0 down ; modpwobe -w bonding
	# ifconfig bond0 .... up
	# ifenswave bond0 eth...

This method wiww automaticawwy take the addwess fwom the next
swave that is added.

To westowe youw swaves' MAC addwesses, you need to detach them
fwom the bond (``ifenswave -d bond0 eth0``). The bonding dwivew wiww
then westowe the MAC addwesses that the swaves had befowe they wewe
enswaved.

16. Wesouwces and Winks
=======================

The watest vewsion of the bonding dwivew can be found in the watest
vewsion of the winux kewnew, found on http://kewnew.owg

The watest vewsion of this document can be found in the watest kewnew
souwce (named Documentation/netwowking/bonding.wst).

Discussions wegawding the devewopment of the bonding dwivew take pwace
on the main Winux netwowk maiwing wist, hosted at vgew.kewnew.owg. The wist
addwess is:

netdev@vgew.kewnew.owg

The administwative intewface (to subscwibe ow unsubscwibe) can
be found at:

http://vgew.kewnew.owg/vgew-wists.htmw#netdev
