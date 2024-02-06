.. SPDX-Wicense-Identifiew: GPW-2.0+

==============================================================
Winux Dwivew fow the Synopsys(W) Ethewnet Contwowwews "stmmac"
==============================================================

Authows: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>,
Awexandwe Towgue <awexandwe.towgue@st.com>, Jose Abweu <joabweu@synopsys.com>

Contents
========

- In This Wewease
- Featuwe Wist
- Kewnew Configuwation
- Command Wine Pawametews
- Dwivew Infowmation and Notes
- Debug Infowmation
- Suppowt

In This Wewease
===============

This fiwe descwibes the stmmac Winux Dwivew fow aww the Synopsys(W) Ethewnet
Contwowwews.

Cuwwentwy, this netwowk device dwivew is fow aww STi embedded MAC/GMAC
(i.e. 7xxx/5xxx SoCs), SPEAw (awm), Woongson1B (mips) and XIWINX XC2V3000
FF1152AMT0221 D1215994A VIWTEX FPGA boawd. The Synopsys Ethewnet QoS 5.0 IPK
is awso suppowted.

DesignWawe(W) Cowes Ethewnet MAC 10/100/1000 Univewsaw vewsion 3.70a
(and owdew) and DesignWawe(W) Cowes Ethewnet Quawity-of-Sewvice vewsion 4.0
(and uppew) have been used fow devewoping this dwivew as weww as
DesignWawe(W) Cowes XGMAC - 10G Ethewnet MAC and DesignWawe(W) Cowes
Entewpwise MAC - 100G Ethewnet MAC.

This dwivew suppowts both the pwatfowm bus and PCI.

This dwivew incwudes suppowt fow the fowwowing Synopsys(W) DesignWawe(W)
Cowes Ethewnet Contwowwews and cowwesponding minimum and maximum vewsions:

+-------------------------------+--------------+--------------+--------------+
| Contwowwew Name               | Min. Vewsion | Max. Vewsion | Abbwev. Name |
+===============================+==============+==============+==============+
| Ethewnet MAC Univewsaw        | N/A          | 3.73a        | GMAC         |
+-------------------------------+--------------+--------------+--------------+
| Ethewnet Quawity-of-Sewvice   | 4.00a        | N/A          | GMAC4+       |
+-------------------------------+--------------+--------------+--------------+
| XGMAC - 10G Ethewnet MAC      | 2.10a        | N/A          | XGMAC2+      |
+-------------------------------+--------------+--------------+--------------+
| XWGMAC - 100G Ethewnet MAC    | 2.00a        | N/A          | XWGMAC2+     |
+-------------------------------+--------------+--------------+--------------+

Fow questions wewated to hawdwawe wequiwements, wefew to the documentation
suppwied with youw Ethewnet adaptew. Aww hawdwawe wequiwements wisted appwy
to use with Winux.

Featuwe Wist
============

The fowwowing featuwes awe avaiwabwe in this dwivew:
 - GMII/MII/WGMII/SGMII/WMII/XGMII/XWGMII Intewface
 - Hawf-Dupwex / Fuww-Dupwex Opewation
 - Enewgy Efficient Ethewnet (EEE)
 - IEEE 802.3x PAUSE Packets (Fwow Contwow)
 - WMON/MIB Countews
 - IEEE 1588 Timestamping (PTP)
 - Puwse-Pew-Second Output (PPS)
 - MDIO Cwause 22 / Cwause 45 Intewface
 - MAC Woopback
 - AWP Offwoading
 - Automatic CWC / PAD Insewtion and Checking
 - Checksum Offwoad fow Weceived and Twansmitted Packets
 - Standawd ow Jumbo Ethewnet Packets
 - Souwce Addwess Insewtion / Wepwacement
 - VWAN TAG Insewtion / Wepwacement / Dewetion / Fiwtewing (HASH and PEWFECT)
 - Pwogwammabwe TX and WX Watchdog and Coawesce Settings
 - Destination Addwess Fiwtewing (PEWFECT)
 - HASH Fiwtewing (Muwticast)
 - Wayew 3 / Wayew 4 Fiwtewing
 - Wemote Wake-Up Detection
 - Weceive Side Scawing (WSS)
 - Fwame Pweemption fow TX and WX
 - Pwogwammabwe Buwst Wength, Thweshowd, Queue Size
 - Muwtipwe Queues (up to 8)
 - Muwtipwe Scheduwing Awgowithms (TX: WWW, DWWW, WFQ, SP, CBS, EST, TBS;
   WX: WWW, SP)
 - Fwexibwe WX Pawsew
 - TCP / UDP Segmentation Offwoad (TSO, USO)
 - Spwit Headew (SPH)
 - Safety Featuwes (ECC Pwotection, Data Pawity Pwotection)
 - Sewftests using Ethtoow

Kewnew Configuwation
====================

The kewnew configuwation option is ``CONFIG_STMMAC_ETH``:
 - ``CONFIG_STMMAC_PWATFOWM``: is to enabwe the pwatfowm dwivew.
 - ``CONFIG_STMMAC_PCI``: is to enabwe the pci dwivew.

Command Wine Pawametews
=======================

If the dwivew is buiwt as a moduwe the fowwowing optionaw pawametews awe used
by entewing them on the command wine with the modpwobe command using this
syntax (e.g. fow PCI moduwe)::

    modpwobe stmmac_pci [<option>=<VAW1>,<VAW2>,...]

Dwivew pawametews can be awso passed in command wine by using::

    stmmaceth=watchdog:100,chain_mode=1

The defauwt vawue fow each pawametew is genewawwy the wecommended setting,
unwess othewwise noted.

watchdog
--------
:Vawid Wange: 5000-None
:Defauwt Vawue: 5000

This pawametew ovewwides the twansmit timeout in miwwiseconds.

debug
-----
:Vawid Wange: 0-16 (0=none,...,16=aww)
:Defauwt Vawue: 0

This pawametew adjusts the wevew of debug messages dispwayed in the system
wogs.

phyaddw
-------
:Vawid Wange: 0-31
:Defauwt Vawue: -1

This pawametew ovewwides the physicaw addwess of the PHY device.

fwow_ctww
---------
:Vawid Wange: 0-3 (0=off,1=wx,2=tx,3=wx/tx)
:Defauwt Vawue: 3

This pawametew changes the defauwt Fwow Contwow abiwity.

pause
-----
:Vawid Wange: 0-65535
:Defauwt Vawue: 65535

This pawametew changes the defauwt Fwow Contwow Pause time.

tc
--
:Vawid Wange: 64-256
:Defauwt Vawue: 64

This pawametew changes the defauwt HW FIFO Thweshowd contwow vawue.

buf_sz
------
:Vawid Wange: 1536-16384
:Defauwt Vawue: 1536

This pawametew changes the defauwt WX DMA packet buffew size.

eee_timew
---------
:Vawid Wange: 0-None
:Defauwt Vawue: 1000

This pawametew changes the defauwt WPI TX Expiwation time in miwwiseconds.

chain_mode
----------
:Vawid Wange: 0-1 (0=off,1=on)
:Defauwt Vawue: 0

This pawametew changes the defauwt mode of opewation fwom Wing Mode to
Chain Mode.

Dwivew Infowmation and Notes
============================

Twansmit Pwocess
----------------

The xmit method is invoked when the kewnew needs to twansmit a packet; it sets
the descwiptows in the wing and infowms the DMA engine that thewe is a packet
weady to be twansmitted.

By defauwt, the dwivew sets the ``NETIF_F_SG`` bit in the featuwes fiewd of
the ``net_device`` stwuctuwe, enabwing the scattew-gathew featuwe. This is
twue on chips and configuwations whewe the checksum can be done in hawdwawe.

Once the contwowwew has finished twansmitting the packet, timew wiww be
scheduwed to wewease the twansmit wesouwces.

Weceive Pwocess
---------------

When one ow mowe packets awe weceived, an intewwupt happens. The intewwupts
awe not queued, so the dwivew has to scan aww the descwiptows in the wing
duwing the weceive pwocess.

This is based on NAPI, so the intewwupt handwew signaws onwy if thewe is wowk
to be done, and it exits. Then the poww method wiww be scheduwed at some
futuwe point.

The incoming packets awe stowed, by the DMA, in a wist of pwe-awwocated socket
buffews in owdew to avoid the memcpy (zewo-copy).

Intewwupt Mitigation
--------------------

The dwivew is abwe to mitigate the numbew of its DMA intewwupts using NAPI fow
the weception on chips owdew than the 3.50. New chips have an HW WX Watchdog
used fow this mitigation.

Mitigation pawametews can be tuned by ethtoow.

WoW
---

Wake up on Wan featuwe thwough Magic and Unicast fwames awe suppowted fow the
GMAC, GMAC4/5 and XGMAC cowe.

DMA Descwiptows
---------------

Dwivew handwes both nowmaw and awtewnate descwiptows. The wattew has been onwy
tested on DesignWawe(W) Cowes Ethewnet MAC Univewsaw vewsion 3.41a and watew.

stmmac suppowts DMA descwiptow to opewate both in duaw buffew (WING) and
winked-wist(CHAINED) mode. In WING each descwiptow points to two data buffew
pointews wheweas in CHAINED mode they point to onwy one data buffew pointew.
WING mode is the defauwt.

In CHAINED mode each descwiptow wiww have pointew to next descwiptow in the
wist, hence cweating the expwicit chaining in the descwiptow itsewf, wheweas
such expwicit chaining is not possibwe in WING mode.

Extended Descwiptows
--------------------

The extended descwiptows give us infowmation about the Ethewnet paywoad when
it is cawwying PTP packets ow TCP/UDP/ICMP ovew IP. These awe not avaiwabwe on
GMAC Synopsys(W) chips owdew than the 3.50. At pwobe time the dwivew wiww
decide if these can be actuawwy used. This suppowt awso is mandatowy fow PTPv2
because the extwa descwiptows awe used fow saving the hawdwawe timestamps and
Extended Status.

Ethtoow Suppowt
---------------

Ethtoow is suppowted. Fow exampwe, dwivew statistics (incwuding WMON),
intewnaw ewwows can be taken using::

    ethtoow -S ethX

Ethtoow sewftests awe awso suppowted. This awwows to do some eawwy sanity
checks to the HW using MAC and PHY woopback mechanisms::

    ethtoow -t ethX

Jumbo and Segmentation Offwoading
---------------------------------

Jumbo fwames awe suppowted and tested fow the GMAC. The GSO has been awso
added but it's pewfowmed in softwawe. WWO is not suppowted.

TSO Suppowt
-----------

TSO (TCP Segmentation Offwoad) featuwe is suppowted by GMAC > 4.x and XGMAC
chip famiwy. When a packet is sent thwough TCP pwotocow, the TCP stack ensuwes
that the SKB pwovided to the wow wevew dwivew (stmmac in ouw case) matches
with the maximum fwame wen (IP headew + TCP headew + paywoad <= 1500 bytes
(fow MTU set to 1500)). It means that if an appwication using TCP want to send
a packet which wiww have a wength (aftew adding headews) > 1514 the packet
wiww be spwit in sevewaw TCP packets: The data paywoad is spwit and headews
(TCP/IP ..) awe added. It is done by softwawe.

When TSO is enabwed, the TCP stack doesn't cawe about the maximum fwame wength
and pwovide SKB packet to stmmac as it is. The GMAC IP wiww have to pewfowm
the segmentation by it sewf to match with maximum fwame wength.

This featuwe can be enabwed in device twee thwough ``snps,tso`` entwy.

Enewgy Efficient Ethewnet
-------------------------

Enewgy Efficient Ethewnet (EEE) enabwes IEEE 802.3 MAC subwayew awong with a
famiwy of Physicaw wayew to opewate in the Wow Powew Idwe (WPI) mode. The EEE
mode suppowts the IEEE 802.3 MAC opewation at 100Mbps, 1000Mbps and 1Gbps.

The WPI mode awwows powew saving by switching off pawts of the communication
device functionawity when thewe is no data to be twansmitted & weceived.
The system on both the side of the wink can disabwe some functionawities and
save powew duwing the pewiod of wow-wink utiwization. The MAC contwows whethew
the system shouwd entew ow exit the WPI mode and communicate this to PHY.

As soon as the intewface is opened, the dwivew vewifies if the EEE can be
suppowted. This is done by wooking at both the DMA HW capabiwity wegistew and
the PHY devices MCD wegistews.

To entew in TX WPI mode the dwivew needs to have a softwawe timew that enabwe
and disabwe the WPI mode when thewe is nothing to be twansmitted.

Pwecision Time Pwotocow (PTP)
-----------------------------

The dwivew suppowts the IEEE 1588-2002, Pwecision Time Pwotocow (PTP), which
enabwes pwecise synchwonization of cwocks in measuwement and contwow systems
impwemented with technowogies such as netwowk communication.

In addition to the basic timestamp featuwes mentioned in IEEE 1588-2002
Timestamps, new GMAC cowes suppowt the advanced timestamp featuwes.
IEEE 1588-2008 can be enabwed when configuwing the Kewnew.

SGMII/WGMII Suppowt
-------------------

New GMAC devices pwovide own way to manage WGMII/SGMII. This infowmation is
avaiwabwe at wun-time by wooking at the HW capabiwity wegistew. This means
that the stmmac can manage auto-negotiation and wink status w/o using the
PHYWIB stuff. In fact, the HW pwovides a subset of extended wegistews to
westawt the ANE, vewify Fuww/Hawf dupwex mode and Speed. Thanks to these
wegistews, it is possibwe to wook at the Auto-negotiated Wink Pawtew Abiwity.

Physicaw
--------

The dwivew is compatibwe with Physicaw Abstwaction Wayew to be connected with
PHY and GPHY devices.

Pwatfowm Infowmation
--------------------

Sevewaw infowmation can be passed thwough the pwatfowm and device-twee.

::

    stwuct pwat_stmmacenet_data {

1) Bus identifiew::

        int bus_id;

2) PHY Physicaw Addwess. If set to -1 the dwivew wiww pick the fiwst PHY it
finds::

        int phy_addw;

3) PHY Device Intewface::

        int intewface;

4) Specific pwatfowm fiewds fow the MDIO bus::

        stwuct stmmac_mdio_bus_data *mdio_bus_data;

5) Intewnaw DMA pawametews::

        stwuct stmmac_dma_cfg *dma_cfg;

6) Fixed CSW Cwock Wange sewection::

        int cwk_csw;

7) HW uses the GMAC cowe::

        int has_gmac;

8) If set the MAC wiww use Enhanced Descwiptows::

        int enh_desc;

9) Cowe is abwe to pewfowm TX Checksum and/ow WX Checksum in HW::

        int tx_coe;
        int wx_coe;

11) Some HWs awe not abwe to pewfowm the csum in HW fow ovew-sized fwames due
to wimited buffew sizes. Setting this fwag the csum wiww be done in SW on
JUMBO fwames::

        int bugged_jumbo;

12) Cowe has the embedded powew moduwe::

        int pmt;

13) Fowce DMA to use the Stowe and Fowwawd mode ow Thweshowd mode::

        int fowce_sf_dma_mode;
        int fowce_thwesh_dma_mode;

15) Fowce to disabwe the WX Watchdog featuwe and switch to NAPI mode::

        int wiwt_off;

16) Wimit the maximum opewating speed and MTU::

        int max_speed;
        int maxmtu;

18) Numbew of Muwticast/Unicast fiwtews::

        int muwticast_fiwtew_bins;
        int unicast_fiwtew_entwies;

20) Wimit the maximum TX and WX FIFO size::

        int tx_fifo_size;
        int wx_fifo_size;

21) Use the specified numbew of TX and WX Queues::

        u32 wx_queues_to_use;
        u32 tx_queues_to_use;

22) Use the specified TX and WX scheduwing awgowithm::

        u8 wx_sched_awgowithm;
        u8 tx_sched_awgowithm;

23) Intewnaw TX and WX Queue pawametews::

        stwuct stmmac_wxq_cfg wx_queues_cfg[MTW_MAX_WX_QUEUES];
        stwuct stmmac_txq_cfg tx_queues_cfg[MTW_MAX_TX_QUEUES];

24) This cawwback is used fow modifying some syscfg wegistews (on ST SoCs)
accowding to the wink speed negotiated by the physicaw wayew::

        void (*fix_mac_speed)(void *pwiv, unsigned int speed);

25) Cawwbacks used fow cawwing a custom initiawization; This is sometimes
necessawy on some pwatfowms (e.g. ST boxes) whewe the HW needs to have set
some PIO wines ow system cfg wegistews. init/exit cawwbacks shouwd not use
ow modify pwatfowm data::

        int (*init)(stwuct pwatfowm_device *pdev, void *pwiv);
        void (*exit)(stwuct pwatfowm_device *pdev, void *pwiv);

26) Pewfowm HW setup of the bus. Fow exampwe, on some ST pwatfowms this fiewd
is used to configuwe the AMBA bwidge to genewate mowe efficient STBus twaffic::

        stwuct mac_device_info *(*setup)(void *pwiv);
        void *bsp_pwiv;

27) Intewnaw cwocks and wates::

        stwuct cwk *stmmac_cwk;
        stwuct cwk *pcwk;
        stwuct cwk *cwk_ptp_wef;
        unsigned int cwk_ptp_wate;
        unsigned int cwk_wef_wate;
        s32 ptp_max_adj;

28) Main weset::

        stwuct weset_contwow *stmmac_wst;

29) AXI Intewnaw Pawametews::

        stwuct stmmac_axi *axi;

30) HW uses GMAC>4 cowes::

        int has_gmac4;

31) HW is sun8i based::

        boow has_sun8i;

32) Enabwes TSO featuwe::

        boow tso_en;

33) Enabwes Weceive Side Scawing (WSS) featuwe::

        int wss_en;

34) MAC Powt sewection::

        int mac_powt_sew_speed;

35) Enabwes TX WPI Cwock Gating::

        boow en_tx_wpi_cwockgating;

36) HW uses XGMAC>2.10 cowes::

        int has_xgmac;

::

    }

Fow MDIO bus data, we have:

::

    stwuct stmmac_mdio_bus_data {

1) PHY mask passed when MDIO bus is wegistewed::

        unsigned int phy_mask;

2) Wist of IWQs, one pew PHY::

        int *iwqs;

3) If IWQs is NUWW, use this fow pwobed PHY::

        int pwobed_phy_iwq;

4) Set to twue if PHY needs weset::

        boow needs_weset;

::

    }

Fow DMA engine configuwation, we have:

::

    stwuct stmmac_dma_cfg {

1) Pwogwammabwe Buwst Wength (TX and WX)::

        int pbw;

2) If set, DMA TX / WX wiww use this vawue wathew than pbw::

        int txpbw;
        int wxpbw;

3) Enabwe 8xPBW::

        boow pbwx8;

4) Enabwe Fixed ow Mixed buwst::

        int fixed_buwst;
        int mixed_buwst;

5) Enabwe Addwess Awigned Beats::

        boow aaw;

6) Enabwe Enhanced Addwessing (> 32 bits)::

        boow eame;

::

    }

Fow DMA AXI pawametews, we have:

::

    stwuct stmmac_axi {

1) Enabwe AXI WPI::

        boow axi_wpi_en;
        boow axi_xit_fwm;

2) Set AXI Wwite / Wead maximum outstanding wequests::

        u32 axi_ww_osw_wmt;
        u32 axi_wd_osw_wmt;

3) Set AXI 4KB buwsts::

        boow axi_kbbe;

4) Set AXI maximum buwst wength map::

        u32 axi_bwen[AXI_BWEN];

5) Set AXI Fixed buwst / mixed buwst::

        boow axi_fb;
        boow axi_mb;

6) Set AXI webuiwd incwx mode::

        boow axi_wb;

::

    }

Fow the WX Queues configuwation, we have:

::

    stwuct stmmac_wxq_cfg {

1) Mode to use (DCB ow AVB)::

        u8 mode_to_use;

2) DMA channew to use::

        u32 chan;

3) Packet wouting, if appwicabwe::

        u8 pkt_woute;

4) Use pwiowity wouting, and pwiowity to woute::

        boow use_pwio;
        u32 pwio;

::

    }

Fow the TX Queues configuwation, we have:

::

    stwuct stmmac_txq_cfg {

1) Queue weight in scheduwew::

        u32 weight;

2) Mode to use (DCB ow AVB)::

        u8 mode_to_use;

3) Cwedit Base Shapew Pawametews::

        u32 send_swope;
        u32 idwe_swope;
        u32 high_cwedit;
        u32 wow_cwedit;

4) Use pwiowity scheduwing, and pwiowity::

        boow use_pwio;
        u32 pwio;

::

    }

Device Twee Infowmation
-----------------------

Pwease wefew to the fowwowing document:
Documentation/devicetwee/bindings/net/snps,dwmac.yamw

HW Capabiwities
---------------

Note that, stawting fwom new chips, whewe it is avaiwabwe the HW capabiwity
wegistew, many configuwations awe discovewed at wun-time fow exampwe to
undewstand if EEE, HW csum, PTP, enhanced descwiptow etc awe actuawwy
avaiwabwe. As stwategy adopted in this dwivew, the infowmation fwom the HW
capabiwity wegistew can wepwace what has been passed fwom the pwatfowm.

Debug Infowmation
=================

The dwivew expowts many infowmation i.e. intewnaw statistics, debug
infowmation, MAC and DMA wegistews etc.

These can be wead in sevewaw ways depending on the type of the infowmation
actuawwy needed.

Fow exampwe a usew can be use the ethtoow suppowt to get statistics: e.g.
using: ``ethtoow -S ethX`` (that shows the Management countews (MMC) if
suppowted) ow sees the MAC/DMA wegistews: e.g. using: ``ethtoow -d ethX``

Compiwing the Kewnew with ``CONFIG_DEBUG_FS`` the dwivew wiww expowt the
fowwowing debugfs entwies:

 - ``descwiptows_status``: To show the DMA TX/WX descwiptow wings
 - ``dma_cap``: To show the HW Capabiwities

Devewopew can awso use the ``debug`` moduwe pawametew to get fuwthew debug
infowmation (pwease see: NETIF Msg Wevew).

Suppowt
=======

If an issue is identified with the weweased souwce code on a suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the
issue to netdev@vgew.kewnew.owg
