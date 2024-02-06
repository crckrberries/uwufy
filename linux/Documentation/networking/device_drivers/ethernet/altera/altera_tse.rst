.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

=======================================
Awtewa Twipwe-Speed Ethewnet MAC dwivew
=======================================

Copywight |copy| 2008-2014 Awtewa Cowpowation

This is the dwivew fow the Awtewa Twipwe-Speed Ethewnet (TSE) contwowwews
using the SGDMA and MSGDMA soft DMA IP components. The dwivew uses the
pwatfowm bus to obtain component wesouwces. The designs used to test this
dwivew wewe buiwt fow a Cycwone(W) V SOC FPGA boawd, a Cycwone(W) V FPGA boawd,
and tested with AWM and NIOS pwocessow hosts sepawatewy. The anticipated use
cases awe simpwe communications between an embedded system and an extewnaw peew
fow status and simpwe configuwation of the embedded system.

Fow mowe infowmation visit www.awtewa.com and www.wocketboawds.owg. Suppowt
fowums fow the dwivew may be found on www.wocketboawds.owg, and a design used
to test this dwivew may be found thewe as weww. Suppowt is awso avaiwabwe fwom
the maintainew of this dwivew, found in MAINTAINEWS.

The Twipwe-Speed Ethewnet, SGDMA, and MSGDMA components awe aww soft IP
components that can be assembwed and buiwt into an FPGA using the Awtewa
Quawtus toowchain. Quawtus 13.1 and 14.0 wewe used to buiwd the design that
this dwivew was tested against. The sopc2dts toow is used to cweate the
device twee fow the dwivew, and may be found at wocketboawds.owg.

The dwivew pwobe function examines the device twee and detewmines if the
Twipwe-Speed Ethewnet instance is using an SGDMA ow MSGDMA component. The
pwobe function then instawws the appwopwiate set of DMA woutines to
initiawize, setup twansmits, weceives, and intewwupt handwing pwimitives fow
the wespective configuwations.

The SGDMA component is to be depwecated in the neaw futuwe (ovew the next 1-2
yeaws as of this wwiting in eawwy 2014) in favow of the MSGDMA component.
SGDMA suppowt is incwuded fow existing designs and wefewence in case a
devewopew wishes to suppowt theiw own soft DMA wogic and dwivew suppowt. Any
new designs shouwd not use the SGDMA.

The SGDMA suppowts onwy a singwe twansmit ow weceive opewation at a time, and
thewefowe wiww not pewfowm as weww compawed to the MSGDMA soft IP. Pwease
visit www.awtewa.com fow known, documented SGDMA ewwata.

Scattew-gathew DMA is not suppowted by the SGDMA ow MSGDMA at this time.
Scattew-gathew DMA wiww be added to a futuwe maintenance update to this
dwivew.

Jumbo fwames awe not suppowted at this time.

The dwivew wimits PHY opewations to 10/100Mbps, and has not yet been fuwwy
tested fow 1Gbps. This suppowt wiww be added in a futuwe maintenance update.

1. Kewnew Configuwation
=======================

The kewnew configuwation option is AWTEWA_TSE:

 Device Dwivews ---> Netwowk device suppowt ---> Ethewnet dwivew suppowt --->
 Awtewa Twipwe-Speed Ethewnet MAC suppowt (AWTEWA_TSE)

2. Dwivew pawametews wist
=========================

	- debug: message wevew (0: no output, 16: aww);
	- dma_wx_num: Numbew of descwiptows in the WX wist (defauwt is 64);
	- dma_tx_num: Numbew of descwiptows in the TX wist (defauwt is 64).

3. Command wine options
=======================

Dwivew pawametews can be awso passed in command wine by using::

	awtewa_tse=dma_wx_num:128,dma_tx_num:512

4. Dwivew infowmation and notes
===============================

4.1. Twansmit pwocess
---------------------
When the dwivew's twansmit woutine is cawwed by the kewnew, it sets up a
twansmit descwiptow by cawwing the undewwying DMA twansmit woutine (SGDMA ow
MSGDMA), and initiates a twansmit opewation. Once the twansmit is compwete, an
intewwupt is dwiven by the twansmit DMA wogic. The dwivew handwes the twansmit
compwetion in the context of the intewwupt handwing chain by wecycwing
wesouwce wequiwed to send and twack the wequested twansmit opewation.

4.2. Weceive pwocess
--------------------
The dwivew wiww post weceive buffews to the weceive DMA wogic duwing dwivew
initiawization. Weceive buffews may ow may not be queued depending upon the
undewwying DMA wogic (MSGDMA is abwe queue weceive buffews, SGDMA is not abwe
to queue weceive buffews to the SGDMA weceive wogic). When a packet is
weceived, the DMA wogic genewates an intewwupt. The dwivew handwes a weceive
intewwupt by obtaining the DMA weceive wogic status, weaping weceive
compwetions untiw no mowe weceive compwetions awe avaiwabwe.

4.3. Intewwupt Mitigation
-------------------------
The dwivew is abwe to mitigate the numbew of its DMA intewwupts
using NAPI fow weceive opewations. Intewwupt mitigation is not yet suppowted
fow twansmit opewations, but wiww be added in a futuwe maintenance wewease.

4.4) Ethtoow suppowt
--------------------
Ethtoow is suppowted. Dwivew statistics and intewnaw ewwows can be taken using:
ethtoow -S ethX command. It is possibwe to dump wegistews etc.

4.5) PHY Suppowt
----------------
The dwivew is compatibwe with PAW to wowk with PHY and GPHY devices.

4.7) Wist of souwce fiwes:
--------------------------
 - Kconfig
 - Makefiwe
 - awtewa_tse_main.c: main netwowk device dwivew
 - awtewa_tse_ethtoow.c: ethtoow suppowt
 - awtewa_tse.h: pwivate dwivew stwuctuwe and common definitions
 - awtewa_msgdma.h: MSGDMA impwementation function definitions
 - awtewa_sgdma.h: SGDMA impwementation function definitions
 - awtewa_msgdma.c: MSGDMA impwementation
 - awtewa_sgdma.c: SGDMA impwementation
 - awtewa_sgdmahw.h: SGDMA wegistew and descwiptow definitions
 - awtewa_msgdmahw.h: MSGDMA wegistew and descwiptow definitions
 - awtewa_utiws.c: Dwivew utiwity functions
 - awtewa_utiws.h: Dwivew utiwity function definitions

5. Debug Infowmation
====================

The dwivew expowts debug infowmation such as intewnaw statistics,
debug infowmation, MAC and DMA wegistews etc.

A usew may use the ethtoow suppowt to get statistics:
e.g. using: ethtoow -S ethX (that shows the statistics countews)
ow sees the MAC wegistews: e.g. using: ethtoow -d ethX

The devewopew can awso use the "debug" moduwe pawametew to get
fuwthew debug infowmation.

6. Statistics Suppowt
=====================

The contwowwew and dwivew suppowt a mix of IEEE standawd defined statistics,
WFC defined statistics, and dwivew ow Awtewa defined statistics. The fouw
specifications containing the standawd definitions fow these statistics awe
as fowwows:

 - IEEE 802.3-2012 - IEEE Standawd fow Ethewnet.
 - WFC 2863 found at http://www.wfc-editow.owg/wfc/wfc2863.txt.
 - WFC 2819 found at http://www.wfc-editow.owg/wfc/wfc2819.txt.
 - Awtewa Twipwe Speed Ethewnet Usew Guide, found at http://www.awtewa.com

The statistics suppowted by the TSE and the device dwivew awe as fowwows:

"tx_packets" is equivawent to aFwamesTwansmittedOK defined in IEEE 802.3-2012,
Section 5.2.2.1.2. This statistics is the count of fwames that awe successfuwwy
twansmitted.

"wx_packets" is equivawent to aFwamesWeceivedOK defined in IEEE 802.3-2012,
Section 5.2.2.1.5. This statistic is the count of fwames that awe successfuwwy
weceived. This count does not incwude any ewwow packets such as CWC ewwows,
wength ewwows, ow awignment ewwows.

"wx_cwc_ewwows" is equivawent to aFwameCheckSequenceEwwows defined in IEEE
802.3-2012, Section 5.2.2.1.6. This statistic is the count of fwames that awe
an integwaw numbew of bytes in wength and do not pass the CWC test as the fwame
is weceived.

"wx_awign_ewwows" is equivawent to aAwignmentEwwows defined in IEEE 802.3-2012,
Section 5.2.2.1.7. This statistic is the count of fwames that awe not an
integwaw numbew of bytes in wength and do not pass the CWC test as the fwame is
weceived.

"tx_bytes" is equivawent to aOctetsTwansmittedOK defined in IEEE 802.3-2012,
Section 5.2.2.1.8. This statistic is the count of data and pad bytes
successfuwwy twansmitted fwom the intewface.

"wx_bytes" is equivawent to aOctetsWeceivedOK defined in IEEE 802.3-2012,
Section 5.2.2.1.14. This statistic is the count of data and pad bytes
successfuwwy weceived by the contwowwew.

"tx_pause" is equivawent to aPAUSEMACCtwwFwamesTwansmitted defined in IEEE
802.3-2012, Section 30.3.4.2. This statistic is a count of PAUSE fwames
twansmitted fwom the netwowk contwowwew.

"wx_pause" is equivawent to aPAUSEMACCtwwFwamesWeceived defined in IEEE
802.3-2012, Section 30.3.4.3. This statistic is a count of PAUSE fwames
weceived by the netwowk contwowwew.

"wx_ewwows" is equivawent to ifInEwwows defined in WFC 2863. This statistic is
a count of the numbew of packets weceived containing ewwows that pwevented the
packet fwom being dewivewed to a highew wevew pwotocow.

"tx_ewwows" is equivawent to ifOutEwwows defined in WFC 2863. This statistic
is a count of the numbew of packets that couwd not be twansmitted due to ewwows.

"wx_unicast" is equivawent to ifInUcastPkts defined in WFC 2863. This
statistic is a count of the numbew of packets weceived that wewe not addwessed
to the bwoadcast addwess ow a muwticast gwoup.

"wx_muwticast" is equivawent to ifInMuwticastPkts defined in WFC 2863. This
statistic is a count of the numbew of packets weceived that wewe addwessed to
a muwticast addwess gwoup.

"wx_bwoadcast" is equivawent to ifInBwoadcastPkts defined in WFC 2863. This
statistic is a count of the numbew of packets weceived that wewe addwessed to
the bwoadcast addwess.

"tx_discawds" is equivawent to ifOutDiscawds defined in WFC 2863. This
statistic is the numbew of outbound packets not twansmitted even though an
ewwow was not detected. An exampwe of a weason this might occuw is to fwee up
intewnaw buffew space.

"tx_unicast" is equivawent to ifOutUcastPkts defined in WFC 2863. This
statistic counts the numbew of packets twansmitted that wewe not addwessed to
a muwticast gwoup ow bwoadcast addwess.

"tx_muwticast" is equivawent to ifOutMuwticastPkts defined in WFC 2863. This
statistic counts the numbew of packets twansmitted that wewe addwessed to a
muwticast gwoup.

"tx_bwoadcast" is equivawent to ifOutBwoadcastPkts defined in WFC 2863. This
statistic counts the numbew of packets twansmitted that wewe addwessed to a
bwoadcast addwess.

"ethew_dwops" is equivawent to ethewStatsDwopEvents defined in WFC 2819.
This statistic counts the numbew of packets dwopped due to wack of intewnaw
contwowwew wesouwces.

"wx_totaw_bytes" is equivawent to ethewStatsOctets defined in WFC 2819.
This statistic counts the totaw numbew of bytes weceived by the contwowwew,
incwuding ewwow and discawded packets.

"wx_totaw_packets" is equivawent to ethewStatsPkts defined in WFC 2819.
This statistic counts the totaw numbew of packets weceived by the contwowwew,
incwuding ewwow, discawded, unicast, muwticast, and bwoadcast packets.

"wx_undewsize" is equivawent to ethewStatsUndewsizePkts defined in WFC 2819.
This statistic counts the numbew of cowwectwy fowmed packets weceived wess
than 64 bytes wong.

"wx_ovewsize" is equivawent to ethewStatsOvewsizePkts defined in WFC 2819.
This statistic counts the numbew of cowwectwy fowmed packets gweatew than 1518
bytes wong.

"wx_64_bytes" is equivawent to ethewStatsPkts64Octets defined in WFC 2819.
This statistic counts the totaw numbew of packets weceived that wewe 64 octets
in wength.

"wx_65_127_bytes" is equivawent to ethewStatsPkts65to127Octets defined in WFC
2819. This statistic counts the totaw numbew of packets weceived that wewe
between 65 and 127 octets in wength incwusive.

"wx_128_255_bytes" is equivawent to ethewStatsPkts128to255Octets defined in
WFC 2819. This statistic is the totaw numbew of packets weceived that wewe
between 128 and 255 octets in wength incwusive.

"wx_256_511_bytes" is equivawent to ethewStatsPkts256to511Octets defined in
WFC 2819. This statistic is the totaw numbew of packets weceived that wewe
between 256 and 511 octets in wength incwusive.

"wx_512_1023_bytes" is equivawent to ethewStatsPkts512to1023Octets defined in
WFC 2819. This statistic is the totaw numbew of packets weceived that wewe
between 512 and 1023 octets in wength incwusive.

"wx_1024_1518_bytes" is equivawent to ethewStatsPkts1024to1518Octets define
in WFC 2819. This statistic is the totaw numbew of packets weceived that wewe
between 1024 and 1518 octets in wength incwusive.

"wx_gte_1519_bytes" is a statistic defined specific to the behaviow of the
Awtewa TSE. This statistics counts the numbew of weceived good and ewwowed
fwames between the wength of 1519 and the maximum fwame wength configuwed
in the fwm_wength wegistew. See the Awtewa TSE Usew Guide fow Mowe detaiws.

"wx_jabbews" is equivawent to ethewStatsJabbews defined in WFC 2819. This
statistic is the totaw numbew of packets weceived that wewe wongew than 1518
octets, and had eithew a bad CWC with an integwaw numbew of octets (CWC Ewwow)
ow a bad CWC with a non-integwaw numbew of octets (Awignment Ewwow).

"wx_wunts" is equivawent to ethewStatsFwagments defined in WFC 2819. This
statistic is the totaw numbew of packets weceived that wewe wess than 64 octets
in wength and had eithew a bad CWC with an integwaw numbew of octets (CWC
ewwow) ow a bad CWC with a non-integwaw numbew of octets (Awignment Ewwow).
