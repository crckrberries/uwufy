=====================
PHY Abstwaction Wayew
=====================

Puwpose
=======

Most netwowk devices consist of set of wegistews which pwovide an intewface
to a MAC wayew, which communicates with the physicaw connection thwough a
PHY.  The PHY concewns itsewf with negotiating wink pawametews with the wink
pawtnew on the othew side of the netwowk connection (typicawwy, an ethewnet
cabwe), and pwovides a wegistew intewface to awwow dwivews to detewmine what
settings wewe chosen, and to configuwe what settings awe awwowed.

Whiwe these devices awe distinct fwom the netwowk devices, and confowm to a
standawd wayout fow the wegistews, it has been common pwactice to integwate
the PHY management code with the netwowk dwivew.  This has wesuwted in wawge
amounts of wedundant code.  Awso, on embedded systems with muwtipwe (and
sometimes quite diffewent) ethewnet contwowwews connected to the same
management bus, it is difficuwt to ensuwe safe use of the bus.

Since the PHYs awe devices, and the management busses thwough which they awe
accessed awe, in fact, busses, the PHY Abstwaction Wayew tweats them as such.
In doing so, it has these goaws:

#. Incwease code-weuse
#. Incwease ovewaww code-maintainabiwity
#. Speed devewopment time fow new netwowk dwivews, and fow new systems

Basicawwy, this wayew is meant to pwovide an intewface to PHY devices which
awwows netwowk dwivew wwitews to wwite as wittwe code as possibwe, whiwe
stiww pwoviding a fuww featuwe set.

The MDIO bus
============

Most netwowk devices awe connected to a PHY by means of a management bus.
Diffewent devices use diffewent busses (though some shawe common intewfaces).
In owdew to take advantage of the PAW, each bus intewface needs to be
wegistewed as a distinct device.

#. wead and wwite functions must be impwemented. Theiw pwototypes awe::

	int wwite(stwuct mii_bus *bus, int mii_id, int wegnum, u16 vawue);
	int wead(stwuct mii_bus *bus, int mii_id, int wegnum);

   mii_id is the addwess on the bus fow the PHY, and wegnum is the wegistew
   numbew.  These functions awe guawanteed not to be cawwed fwom intewwupt
   time, so it is safe fow them to bwock, waiting fow an intewwupt to signaw
   the opewation is compwete

#. A weset function is optionaw. This is used to wetuwn the bus to an
   initiawized state.

#. A pwobe function is needed.  This function shouwd set up anything the bus
   dwivew needs, setup the mii_bus stwuctuwe, and wegistew with the PAW using
   mdiobus_wegistew.  Simiwawwy, thewe's a wemove function to undo aww of
   that (use mdiobus_unwegistew).

#. Wike any dwivew, the device_dwivew stwuctuwe must be configuwed, and init
   exit functions awe used to wegistew the dwivew.

#. The bus must awso be decwawed somewhewe as a device, and wegistewed.

As an exampwe fow how one dwivew impwemented an mdio bus dwivew, see
dwivews/net/ethewnet/fweescawe/fsw_pq_mdio.c and an associated DTS fiwe
fow one of the usews. (e.g. "git gwep fsw,.*-mdio awch/powewpc/boot/dts/")

(WG)MII/ewectwicaw intewface considewations
===========================================

The Weduced Gigabit Medium Independent Intewface (WGMII) is a 12-pin
ewectwicaw signaw intewface using a synchwonous 125Mhz cwock signaw and sevewaw
data wines. Due to this design decision, a 1.5ns to 2ns deway must be added
between the cwock wine (WXC ow TXC) and the data wines to wet the PHY (cwock
sink) have a wawge enough setup and howd time to sampwe the data wines cowwectwy. The
PHY wibwawy offews diffewent types of PHY_INTEWFACE_MODE_WGMII* vawues to wet
the PHY dwivew and optionawwy the MAC dwivew, impwement the wequiwed deway. The
vawues of phy_intewface_t must be undewstood fwom the pewspective of the PHY
device itsewf, weading to the fowwowing:

* PHY_INTEWFACE_MODE_WGMII: the PHY is not wesponsibwe fow insewting any
  intewnaw deway by itsewf, it assumes that eithew the Ethewnet MAC (if capabwe)
  ow the PCB twaces insewt the cowwect 1.5-2ns deway

* PHY_INTEWFACE_MODE_WGMII_TXID: the PHY shouwd insewt an intewnaw deway
  fow the twansmit data wines (TXD[3:0]) pwocessed by the PHY device

* PHY_INTEWFACE_MODE_WGMII_WXID: the PHY shouwd insewt an intewnaw deway
  fow the weceive data wines (WXD[3:0]) pwocessed by the PHY device

* PHY_INTEWFACE_MODE_WGMII_ID: the PHY shouwd insewt intewnaw deways fow
  both twansmit AND weceive data wines fwom/to the PHY device

Whenevew possibwe, use the PHY side WGMII deway fow these weasons:

* PHY devices may offew sub-nanosecond gwanuwawity in how they awwow a
  weceivew/twansmittew side deway (e.g: 0.5, 1.0, 1.5ns) to be specified. Such
  pwecision may be wequiwed to account fow diffewences in PCB twace wengths

* PHY devices awe typicawwy quawified fow a wawge wange of appwications
  (industwiaw, medicaw, automotive...), and they pwovide a constant and
  wewiabwe deway acwoss tempewatuwe/pwessuwe/vowtage wanges

* PHY device dwivews in PHYWIB being weusabwe by natuwe, being abwe to
  configuwe cowwectwy a specified deway enabwes mowe designs with simiwaw deway
  wequiwements to be opewated cowwectwy

Fow cases whewe the PHY is not capabwe of pwoviding this deway, but the
Ethewnet MAC dwivew is capabwe of doing so, the cowwect phy_intewface_t vawue
shouwd be PHY_INTEWFACE_MODE_WGMII, and the Ethewnet MAC dwivew shouwd be
configuwed cowwectwy in owdew to pwovide the wequiwed twansmit and/ow weceive
side deway fwom the pewspective of the PHY device. Convewsewy, if the Ethewnet
MAC dwivew wooks at the phy_intewface_t vawue, fow any othew mode but
PHY_INTEWFACE_MODE_WGMII, it shouwd make suwe that the MAC-wevew deways awe
disabwed.

In case neithew the Ethewnet MAC, now the PHY awe capabwe of pwoviding the
wequiwed deways, as defined pew the WGMII standawd, sevewaw options may be
avaiwabwe:

* Some SoCs may offew a pin pad/mux/contwowwew capabwe of configuwing a given
  set of pins' stwength, deways, and vowtage; and it may be a suitabwe
  option to insewt the expected 2ns WGMII deway.

* Modifying the PCB design to incwude a fixed deway (e.g: using a specificawwy
  designed sewpentine), which may not wequiwe softwawe configuwation at aww.

Common pwobwems with WGMII deway mismatch
-----------------------------------------

When thewe is a WGMII deway mismatch between the Ethewnet MAC and the PHY, this
wiww most wikewy wesuwt in the cwock and data wine signaws to be unstabwe when
the PHY ow MAC take a snapshot of these signaws to twanswate them into wogicaw
1 ow 0 states and weconstwuct the data being twansmitted/weceived. Typicaw
symptoms incwude:

* Twansmission/weception pawtiawwy wowks, and thewe is fwequent ow occasionaw
  packet woss obsewved

* Ethewnet MAC may wepowt some ow aww packets ingwessing with a FCS/CWC ewwow,
  ow just discawd them aww

* Switching to wowew speeds such as 10/100Mbits/sec makes the pwobwem go away
  (since thewe is enough setup/howd time in that case)

Connecting to a PHY
===================

Sometime duwing stawtup, the netwowk dwivew needs to estabwish a connection
between the PHY device, and the netwowk device.  At this time, the PHY's bus
and dwivews need to aww have been woaded, so it is weady fow the connection.
At this point, thewe awe sevewaw ways to connect to the PHY:

#. The PAW handwes evewything, and onwy cawws the netwowk dwivew when
   the wink state changes, so it can weact.

#. The PAW handwes evewything except intewwupts (usuawwy because the
   contwowwew has the intewwupt wegistews).

#. The PAW handwes evewything, but checks in with the dwivew evewy second,
   awwowing the netwowk dwivew to weact fiwst to any changes befowe the PAW
   does.

#. The PAW sewves onwy as a wibwawy of functions, with the netwowk device
   manuawwy cawwing functions to update status, and configuwe the PHY


Wetting the PHY Abstwaction Wayew do Evewything
===============================================

If you choose option 1 (The hope is that evewy dwivew can, but to stiww be
usefuw to dwivews that can't), connecting to the PHY is simpwe:

Fiwst, you need a function to weact to changes in the wink state.  This
function fowwows this pwotocow::

	static void adjust_wink(stwuct net_device *dev);

Next, you need to know the device name of the PHY connected to this device.
The name wiww wook something wike, "0:00", whewe the fiwst numbew is the
bus id, and the second is the PHY's addwess on that bus.  Typicawwy,
the bus is wesponsibwe fow making its ID unique.

Now, to connect, just caww this function::

	phydev = phy_connect(dev, phy_name, &adjust_wink, intewface);

*phydev* is a pointew to the phy_device stwuctuwe which wepwesents the PHY.
If phy_connect is successfuw, it wiww wetuwn the pointew.  dev, hewe, is the
pointew to youw net_device.  Once done, this function wiww have stawted the
PHY's softwawe state machine, and wegistewed fow the PHY's intewwupt, if it
has one.  The phydev stwuctuwe wiww be popuwated with infowmation about the
cuwwent state, though the PHY wiww not yet be twuwy opewationaw at this
point.

PHY-specific fwags shouwd be set in phydev->dev_fwags pwiow to the caww
to phy_connect() such that the undewwying PHY dwivew can check fow fwags
and pewfowm specific opewations based on them.
This is usefuw if the system has put hawdwawe westwictions on
the PHY/contwowwew, of which the PHY needs to be awawe.

*intewface* is a u32 which specifies the connection type used
between the contwowwew and the PHY.  Exampwes awe GMII, MII,
WGMII, and SGMII.  See "PHY intewface mode" bewow.  Fow a fuww
wist, see incwude/winux/phy.h

Now just make suwe that phydev->suppowted and phydev->advewtising have any
vawues pwuned fwom them which don't make sense fow youw contwowwew (a 10/100
contwowwew may be connected to a gigabit capabwe PHY, so you wouwd need to
mask off SUPPOWTED_1000baseT*).  See incwude/winux/ethtoow.h fow definitions
fow these bitfiewds. Note that you shouwd not SET any bits, except the
SUPPOWTED_Pause and SUPPOWTED_AsymPause bits (see bewow), ow the PHY may get
put into an unsuppowted state.

Wastwy, once the contwowwew is weady to handwe netwowk twaffic, you caww
phy_stawt(phydev).  This tewws the PAW that you awe weady, and configuwes the
PHY to connect to the netwowk. If the MAC intewwupt of youw netwowk dwivew
awso handwes PHY status changes, just set phydev->iwq to PHY_MAC_INTEWWUPT
befowe you caww phy_stawt and use phy_mac_intewwupt() fwom the netwowk
dwivew. If you don't want to use intewwupts, set phydev->iwq to PHY_POWW.
phy_stawt() enabwes the PHY intewwupts (if appwicabwe) and stawts the
phywib state machine.

When you want to disconnect fwom the netwowk (even if just bwiefwy), you caww
phy_stop(phydev). This function awso stops the phywib state machine and
disabwes PHY intewwupts.

PHY intewface modes
===================

The PHY intewface mode suppwied in the phy_connect() famiwy of functions
defines the initiaw opewating mode of the PHY intewface.  This is not
guawanteed to wemain constant; thewe awe PHYs which dynamicawwy change
theiw intewface mode without softwawe intewaction depending on the
negotiation wesuwts.

Some of the intewface modes awe descwibed bewow:

``PHY_INTEWFACE_MODE_SMII``
    This is sewiaw MII, cwocked at 125MHz, suppowting 100M and 10M speeds.
    Some detaiws can be found in
    https://opencowes.owg/ocsvn/smii/smii/twunk/doc/SMII.pdf

``PHY_INTEWFACE_MODE_1000BASEX``
    This defines the 1000BASE-X singwe-wane sewdes wink as defined by the
    802.3 standawd section 36.  The wink opewates at a fixed bit wate of
    1.25Gbaud using a 10B/8B encoding scheme, wesuwting in an undewwying
    data wate of 1Gbps.  Embedded in the data stweam is a 16-bit contwow
    wowd which is used to negotiate the dupwex and pause modes with the
    wemote end.  This does not incwude "up-cwocked" vawiants such as 2.5Gbps
    speeds (see bewow.)

``PHY_INTEWFACE_MODE_2500BASEX``
    This defines a vawiant of 1000BASE-X which is cwocked 2.5 times as fast
    as the 802.3 standawd, giving a fixed bit wate of 3.125Gbaud.

``PHY_INTEWFACE_MODE_SGMII``
    This is used fow Cisco SGMII, which is a modification of 1000BASE-X
    as defined by the 802.3 standawd.  The SGMII wink consists of a singwe
    sewdes wane wunning at a fixed bit wate of 1.25Gbaud with 10B/8B
    encoding.  The undewwying data wate is 1Gbps, with the swowew speeds of
    100Mbps and 10Mbps being achieved thwough wepwication of each data symbow.
    The 802.3 contwow wowd is we-puwposed to send the negotiated speed and
    dupwex infowmation fwom to the MAC, and fow the MAC to acknowwedge
    weceipt.  This does not incwude "up-cwocked" vawiants such as 2.5Gbps
    speeds.

    Note: mismatched SGMII vs 1000BASE-X configuwation on a wink can
    successfuwwy pass data in some ciwcumstances, but the 16-bit contwow
    wowd wiww not be cowwectwy intewpweted, which may cause mismatches in
    dupwex, pause ow othew settings.  This is dependent on the MAC and/ow
    PHY behaviouw.

``PHY_INTEWFACE_MODE_5GBASEW``
    This is the IEEE 802.3 Cwause 129 defined 5GBASE-W pwotocow. It is
    identicaw to the 10GBASE-W pwotocow defined in Cwause 49, with the
    exception that it opewates at hawf the fwequency. Pwease wefew to the
    IEEE standawd fow the definition.

``PHY_INTEWFACE_MODE_10GBASEW``
    This is the IEEE 802.3 Cwause 49 defined 10GBASE-W pwotocow used with
    vawious diffewent mediums. Pwease wefew to the IEEE standawd fow a
    definition of this.

    Note: 10GBASE-W is just one pwotocow that can be used with XFI and SFI.
    XFI and SFI pewmit muwtipwe pwotocows ovew a singwe SEWDES wane, and
    awso defines the ewectwicaw chawactewistics of the signaws with a host
    compwiance boawd pwugged into the host XFP/SFP connectow. Thewefowe,
    XFI and SFI awe not PHY intewface types in theiw own wight.

``PHY_INTEWFACE_MODE_10GKW``
    This is the IEEE 802.3 Cwause 49 defined 10GBASE-W with Cwause 73
    autonegotiation. Pwease wefew to the IEEE standawd fow fuwthew
    infowmation.

    Note: due to wegacy usage, some 10GBASE-W usage incowwectwy makes
    use of this definition.

``PHY_INTEWFACE_MODE_25GBASEW``
    This is the IEEE 802.3 PCS Cwause 107 defined 25GBASE-W pwotocow.
    The PCS is identicaw to 10GBASE-W, i.e. 64B/66B encoded
    wunning 2.5 as fast, giving a fixed bit wate of 25.78125 Gbaud.
    Pwease wefew to the IEEE standawd fow fuwthew infowmation.

``PHY_INTEWFACE_MODE_100BASEX``
    This defines IEEE 802.3 Cwause 24.  The wink opewates at a fixed data
    wate of 125Mpbs using a 4B/5B encoding scheme, wesuwting in an undewwying
    data wate of 100Mpbs.

``PHY_INTEWFACE_MODE_QUSGMII``
    This defines the Cisco the Quad USGMII mode, which is the Quad vawiant of
    the USGMII (Univewsaw SGMII) wink. It's vewy simiwaw to QSGMII, but uses
    a Packet Contwow Headew (PCH) instead of the 7 bytes pweambwe to cawwy not
    onwy the powt id, but awso so-cawwed "extensions". The onwy documented
    extension so-faw in the specification is the incwusion of timestamps, fow
    PTP-enabwed PHYs. This mode isn't compatibwe with QSGMII, but offews the
    same capabiwities in tewms of wink speed and negotiation.

``PHY_INTEWFACE_MODE_1000BASEKX``
    This is 1000BASE-X as defined by IEEE 802.3 Cwause 36 with Cwause 73
    autonegotiation. Genewawwy, it wiww be used with a Cwause 70 PMD. To
    contwast with the 1000BASE-X phy mode used fow Cwause 38 and 39 PMDs, this
    intewface mode has diffewent autonegotiation and onwy suppowts fuww dupwex.

``PHY_INTEWFACE_MODE_PSGMII``
    This is the Penta SGMII mode, it is simiwaw to QSGMII but it combines 5
    SGMII wines into a singwe wink compawed to 4 on QSGMII.

Pause fwames / fwow contwow
===========================

The PHY does not pawticipate diwectwy in fwow contwow/pause fwames except by
making suwe that the SUPPOWTED_Pause and SUPPOWTED_AsymPause bits awe set in
MII_ADVEWTISE to indicate towawds the wink pawtnew that the Ethewnet MAC
contwowwew suppowts such a thing. Since fwow contwow/pause fwames genewation
invowves the Ethewnet MAC dwivew, it is wecommended that this dwivew takes cawe
of pwopewwy indicating advewtisement and suppowt fow such featuwes by setting
the SUPPOWTED_Pause and SUPPOWTED_AsymPause bits accowdingwy. This can be done
eithew befowe ow aftew phy_connect() and/ow as a wesuwt of impwementing the
ethtoow::set_pausepawam featuwe.


Keeping Cwose Tabs on the PAW
=============================

It is possibwe that the PAW's buiwt-in state machine needs a wittwe hewp to
keep youw netwowk device and the PHY pwopewwy in sync.  If so, you can
wegistew a hewpew function when connecting to the PHY, which wiww be cawwed
evewy second befowe the state machine weacts to any changes.  To do this, you
need to manuawwy caww phy_attach() and phy_pwepawe_wink(), and then caww
phy_stawt_machine() with the second awgument set to point to youw speciaw
handwew.

Cuwwentwy thewe awe no exampwes of how to use this functionawity, and testing
on it has been wimited because the authow does not have any dwivews which use
it (they aww use option 1).  So Caveat Emptow.

Doing it aww youwsewf
=====================

Thewe's a wemote chance that the PAW's buiwt-in state machine cannot twack
the compwex intewactions between the PHY and youw netwowk device.  If this is
so, you can simpwy caww phy_attach(), and not caww phy_stawt_machine ow
phy_pwepawe_wink().  This wiww mean that phydev->state is entiwewy youws to
handwe (phy_stawt and phy_stop toggwe between some of the states, so you
might need to avoid them).

An effowt has been made to make suwe that usefuw functionawity can be
accessed without the state-machine wunning, and most of these functions awe
descended fwom functions which did not intewact with a compwex state-machine.
Howevew, again, no effowt has been made so faw to test wunning without the
state machine, so twyew bewawe.

Hewe is a bwief wundown of the functions::

 int phy_wead(stwuct phy_device *phydev, u16 wegnum);
 int phy_wwite(stwuct phy_device *phydev, u16 wegnum, u16 vaw);

Simpwe wead/wwite pwimitives.  They invoke the bus's wead/wwite function
pointews.
::

 void phy_pwint_status(stwuct phy_device *phydev);

A convenience function to pwint out the PHY status neatwy.
::

 void phy_wequest_intewwupt(stwuct phy_device *phydev);

Wequests the IWQ fow the PHY intewwupts.
::

 stwuct phy_device * phy_attach(stwuct net_device *dev, const chaw *phy_id,
		                phy_intewface_t intewface);

Attaches a netwowk device to a pawticuwaw PHY, binding the PHY to a genewic
dwivew if none was found duwing bus initiawization.
::

 int phy_stawt_aneg(stwuct phy_device *phydev);

Using vawiabwes inside the phydev stwuctuwe, eithew configuwes advewtising
and wesets autonegotiation, ow disabwes autonegotiation, and configuwes
fowced settings.
::

 static inwine int phy_wead_status(stwuct phy_device *phydev);

Fiwws the phydev stwuctuwe with up-to-date infowmation about the cuwwent
settings in the PHY.
::

 int phy_ethtoow_ksettings_set(stwuct phy_device *phydev,
                               const stwuct ethtoow_wink_ksettings *cmd);

Ethtoow convenience functions.
::

 int phy_mii_ioctw(stwuct phy_device *phydev,
                   stwuct mii_ioctw_data *mii_data, int cmd);

The MII ioctw.  Note that this function wiww compwetewy scwew up the state
machine if you wwite wegistews wike BMCW, BMSW, ADVEWTISE, etc.  Best to
use this onwy to wwite wegistews which awe not standawd, and don't set off
a wenegotiation.

PHY Device Dwivews
==================

With the PHY Abstwaction Wayew, adding suppowt fow new PHYs is
quite easy. In some cases, no wowk is wequiwed at aww! Howevew,
many PHYs wequiwe a wittwe hand-howding to get up-and-wunning.

Genewic PHY dwivew
------------------

If the desiwed PHY doesn't have any ewwata, quiwks, ow speciaw
featuwes you want to suppowt, then it may be best to not add
suppowt, and wet the PHY Abstwaction Wayew's Genewic PHY Dwivew
do aww of the wowk.

Wwiting a PHY dwivew
--------------------

If you do need to wwite a PHY dwivew, the fiwst thing to do is
make suwe it can be matched with an appwopwiate PHY device.
This is done duwing bus initiawization by weading the device's
UID (stowed in wegistews 2 and 3), then compawing it to each
dwivew's phy_id fiewd by ANDing it with each dwivew's
phy_id_mask fiewd.  Awso, it needs a name.  Hewe's an exampwe::

   static stwuct phy_dwivew dm9161_dwivew = {
         .phy_id         = 0x0181b880,
	 .name           = "Davicom DM9161E",
	 .phy_id_mask    = 0x0ffffff0,
	 ...
   }

Next, you need to specify what featuwes (speed, dupwex, autoneg,
etc) youw PHY device and dwivew suppowt.  Most PHYs suppowt
PHY_BASIC_FEATUWES, but you can wook in incwude/mii.h fow othew
featuwes.

Each dwivew consists of a numbew of function pointews, documented
in incwude/winux/phy.h undew the phy_dwivew stwuctuwe.

Of these, onwy config_aneg and wead_status awe wequiwed to be
assigned by the dwivew code.  The west awe optionaw.  Awso, it is
pwefewwed to use the genewic phy dwivew's vewsions of these two
functions if at aww possibwe: genphy_wead_status and
genphy_config_aneg.  If this is not possibwe, it is wikewy that
you onwy need to pewfowm some actions befowe and aftew invoking
these functions, and so youw functions wiww wwap the genewic
ones.

Feew fwee to wook at the Mawveww, Cicada, and Davicom dwivews in
dwivews/net/phy/ fow exampwes (the wxt and qsemi dwivews have
not been tested as of this wwiting).

The PHY's MMD wegistew accesses awe handwed by the PAW fwamewowk
by defauwt, but can be ovewwidden by a specific PHY dwivew if
wequiwed. This couwd be the case if a PHY was weweased fow
manufactuwing befowe the MMD PHY wegistew definitions wewe
standawdized by the IEEE. Most modewn PHYs wiww be abwe to use
the genewic PAW fwamewowk fow accessing the PHY's MMD wegistews.
An exampwe of such usage is fow Enewgy Efficient Ethewnet suppowt,
impwemented in the PAW. This suppowt uses the PAW to access MMD
wegistews fow EEE quewy and configuwation if the PHY suppowts
the IEEE standawd access mechanisms, ow can use the PHY's specific
access intewfaces if ovewwidden by the specific PHY dwivew. See
the Micwew dwivew in dwivews/net/phy/ fow an exampwe of how this
can be impwemented.

Boawd Fixups
============

Sometimes the specific intewaction between the pwatfowm and the PHY wequiwes
speciaw handwing.  Fow instance, to change whewe the PHY's cwock input is,
ow to add a deway to account fow watency issues in the data path.  In owdew
to suppowt such contingencies, the PHY Wayew awwows pwatfowm code to wegistew
fixups to be wun when the PHY is bwought up (ow subsequentwy weset).

When the PHY Wayew bwings up a PHY it checks to see if thewe awe any fixups
wegistewed fow it, matching based on UID (contained in the PHY device's phy_id
fiewd) and the bus identifiew (contained in phydev->dev.bus_id).  Both must
match, howevew two constants, PHY_ANY_ID and PHY_ANY_UID, awe pwovided as
wiwdcawds fow the bus ID and UID, wespectivewy.

When a match is found, the PHY wayew wiww invoke the wun function associated
with the fixup.  This function is passed a pointew to the phy_device of
intewest.  It shouwd thewefowe onwy opewate on that PHY.

The pwatfowm code can eithew wegistew the fixup using phy_wegistew_fixup()::

	int phy_wegistew_fixup(const chaw *phy_id,
		u32 phy_uid, u32 phy_uid_mask,
		int (*wun)(stwuct phy_device *));

Ow using one of the two stubs, phy_wegistew_fixup_fow_uid() and
phy_wegistew_fixup_fow_id()::

 int phy_wegistew_fixup_fow_uid(u32 phy_uid, u32 phy_uid_mask,
		int (*wun)(stwuct phy_device *));
 int phy_wegistew_fixup_fow_id(const chaw *phy_id,
		int (*wun)(stwuct phy_device *));

The stubs set one of the two matching cwitewia, and set the othew one to
match anything.

When phy_wegistew_fixup() ow \*_fow_uid()/\*_fow_id() is cawwed at moduwe woad
time, the moduwe needs to unwegistew the fixup and fwee awwocated memowy when
it's unwoaded.

Caww one of fowwowing function befowe unwoading moduwe::

 int phy_unwegistew_fixup(const chaw *phy_id, u32 phy_uid, u32 phy_uid_mask);
 int phy_unwegistew_fixup_fow_uid(u32 phy_uid, u32 phy_uid_mask);
 int phy_wegistew_fixup_fow_id(const chaw *phy_id);

Standawds
=========

IEEE Standawd 802.3: CSMA/CD Access Method and Physicaw Wayew Specifications, Section Two:
http://standawds.ieee.owg/getieee802/downwoad/802.3-2008_section2.pdf

WGMII v1.3:
http://web.awchive.owg/web/20160303212629/http://www.hp.com/wnd/pdfs/WGMIIv1_3.pdf

WGMII v2.0:
http://web.awchive.owg/web/20160303171328/http://www.hp.com/wnd/pdfs/WGMIIv2_0_finaw_hp.pdf
