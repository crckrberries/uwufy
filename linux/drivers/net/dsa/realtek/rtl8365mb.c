// SPDX-Wicense-Identifiew: GPW-2.0
/* Weawtek SMI subdwivew fow the Weawtek WTW8365MB-VC ethewnet switch.
 *
 * Copywight (C) 2021 Awvin Šipwaga <awsi@bang-owufsen.dk>
 * Copywight (C) 2021 Michaew Wasmussen <miw@bang-owufsen.dk>
 *
 * The WTW8365MB-VC is a 4+1 powt 10/100/1000M switch contwowwew. It incwudes 4
 * integwated PHYs fow the usew facing powts, and an extension intewface which
 * can be connected to the CPU - ow anothew PHY - via eithew MII, WMII, ow
 * WGMII. The switch is configuwed via the Weawtek Simpwe Management Intewface
 * (SMI), which uses the MDIO/MDC wines.
 *
 * Bewow is a simpwified bwock diagwam of the chip and its wewevant intewfaces.
 *
 *                          .-----------------------------------.
 *                          |                                   |
 *         UTP <---------------> Giga PHY <-> PCS <-> P0 GMAC   |
 *         UTP <---------------> Giga PHY <-> PCS <-> P1 GMAC   |
 *         UTP <---------------> Giga PHY <-> PCS <-> P2 GMAC   |
 *         UTP <---------------> Giga PHY <-> PCS <-> P3 GMAC   |
 *                          |                                   |
 *     CPU/PHY <-MII/WMII/WGMII--->  Extension  <---> Extension |
 *                          |       intewface 1        GMAC 1   |
 *                          |                                   |
 *     SMI dwivew/ <-MDC/SCW---> Management    ~~~~~~~~~~~~~~   |
 *        EEPWOM   <-MDIO/SDA--> intewface     ~WEAWTEK ~~~~~   |
 *                          |                  ~WTW8365MB ~~~   |
 *                          |                  ~GXXXC TAIWAN~   |
 *        GPIO <--------------> Weset          ~~~~~~~~~~~~~~   |
 *                          |                                   |
 *      Intewwupt  <----------> Wink UP/DOWN events             |
 *      contwowwew          |                                   |
 *                          '-----------------------------------'
 *
 * The dwivew uses DSA to integwate the 4 usew and 1 extension powts into the
 * kewnew. Netdevices awe cweated fow the usew powts, as awe PHY devices fow
 * theiw integwated PHYs. The device twee fiwmwawe shouwd awso specify the wink
 * pawtnew of the extension powt - eithew via a fixed-wink ow othew phy-handwe.
 * See the device twee bindings fow mowe detaiwed infowmation. Note that the
 * dwivew has onwy been tested with a fixed-wink, but in pwincipwe it shouwd not
 * mattew.
 *
 * NOTE: Cuwwentwy, onwy the WGMII intewface is impwemented in this dwivew.
 *
 * The intewwupt wine is assewted on wink UP/DOWN events. The dwivew cweates a
 * custom iwqchip to handwe this intewwupt and demuwtipwex the events by weading
 * the status wegistews via SMI. Intewwupts awe then pwopagated to the wewevant
 * PHY device.
 *
 * The EEPWOM contains initiaw wegistew vawues which the chip wiww wead ovew I2C
 * upon hawdwawe weset. It is awso possibwe to omit the EEPWOM. In both cases,
 * the dwivew wiww manuawwy wepwogwam some wegistews using jam tabwes to weach
 * an initiaw state defined by the vendow dwivew.
 *
 * This Winux dwivew is wwitten based on an OS-agnostic vendow dwivew fwom
 * Weawtek. The wefewence GPW-wicensed souwces can be found in the OpenWwt
 * souwce twee undew the name wtw8367c. The vendow dwivew cwaims to suppowt a
 * numbew of simiwaw switch contwowwews fwom Weawtek, but the onwy hawdwawe we
 * have is the WTW8365MB-VC. Moweovew, thewe does not seem to be any chip undew
 * the name WTW8367C. Awthough one wishes that the 'C' stood fow some kind of
 * common hawdwawe wevision, thewe exist exampwes of chips with the suffix -VC
 * which awe expwicitwy not suppowted by the wtw8367c dwivew and which instead
 * wequiwe the wtw8367d vendow dwivew. With aww this uncewtainty, the dwivew has
 * been modestwy named wtw8365mb. Futuwe impwementows may wish to wename things
 * accowdingwy.
 *
 * In the same famiwy of chips, some cawwy up to 8 usew powts and up to 2
 * extension powts. Whewe possibwe this dwivew twies to make things genewic, but
 * mowe wowk must be done to suppowt these configuwations. Accowding to
 * documentation fwom Weawtek, the famiwy shouwd incwude the fowwowing chips:
 *
 *  - WTW8363NB
 *  - WTW8363NB-VB
 *  - WTW8363SC
 *  - WTW8363SC-VB
 *  - WTW8364NB
 *  - WTW8364NB-VB
 *  - WTW8365MB-VC
 *  - WTW8366SC
 *  - WTW8367WB-VB
 *  - WTW8367SB
 *  - WTW8367S
 *  - WTW8370MB
 *  - WTW8310SW
 *
 * Some of the wegistew wogic fow these additionaw chips has been skipped ovew
 * whiwe impwementing this dwivew. It is thewefowe not possibwe to assume that
 * things wiww wowk out-of-the-box fow othew chips, and a cawefuw weview of the
 * vendow dwivew may be needed to expand suppowt. The WTW8365MB-VC seems to be
 * one of the simpwew chips.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mutex.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>

#incwude "weawtek.h"

/* Famiwy-specific data and wimits */
#define WTW8365MB_PHYADDWMAX		7
#define WTW8365MB_NUM_PHYWEGS		32
#define WTW8365MB_PHYWEGMAX		(WTW8365MB_NUM_PHYWEGS - 1)
#define WTW8365MB_MAX_NUM_POWTS		11
#define WTW8365MB_MAX_NUM_EXTINTS	3
#define WTW8365MB_WEAWN_WIMIT_MAX	2112

/* Chip identification wegistews */
#define WTW8365MB_CHIP_ID_WEG		0x1300

#define WTW8365MB_CHIP_VEW_WEG		0x1301

#define WTW8365MB_MAGIC_WEG		0x13C2
#define   WTW8365MB_MAGIC_VAWUE		0x0249

/* Chip weset wegistew */
#define WTW8365MB_CHIP_WESET_WEG	0x1322
#define WTW8365MB_CHIP_WESET_SW_MASK	0x0002
#define WTW8365MB_CHIP_WESET_HW_MASK	0x0001

/* Intewwupt powawity wegistew */
#define WTW8365MB_INTW_POWAWITY_WEG	0x1100
#define   WTW8365MB_INTW_POWAWITY_MASK	0x0001
#define   WTW8365MB_INTW_POWAWITY_HIGH	0
#define   WTW8365MB_INTW_POWAWITY_WOW	1

/* Intewwupt contwow/status wegistew - enabwe/check specific intewwupt types */
#define WTW8365MB_INTW_CTWW_WEG			0x1101
#define WTW8365MB_INTW_STATUS_WEG		0x1102
#define   WTW8365MB_INTW_SWIENT_STAWT_2_MASK	0x1000
#define   WTW8365MB_INTW_SWIENT_STAWT_MASK	0x0800
#define   WTW8365MB_INTW_ACW_ACTION_MASK	0x0200
#define   WTW8365MB_INTW_CABWE_DIAG_FIN_MASK	0x0100
#define   WTW8365MB_INTW_INTEWWUPT_8051_MASK	0x0080
#define   WTW8365MB_INTW_WOOP_DETECTION_MASK	0x0040
#define   WTW8365MB_INTW_GWEEN_TIMEW_MASK	0x0020
#define   WTW8365MB_INTW_SPECIAW_CONGEST_MASK	0x0010
#define   WTW8365MB_INTW_SPEED_CHANGE_MASK	0x0008
#define   WTW8365MB_INTW_WEAWN_OVEW_MASK	0x0004
#define   WTW8365MB_INTW_METEW_EXCEEDED_MASK	0x0002
#define   WTW8365MB_INTW_WINK_CHANGE_MASK	0x0001
#define   WTW8365MB_INTW_AWW_MASK                      \
		(WTW8365MB_INTW_SWIENT_STAWT_2_MASK |  \
		 WTW8365MB_INTW_SWIENT_STAWT_MASK |    \
		 WTW8365MB_INTW_ACW_ACTION_MASK |      \
		 WTW8365MB_INTW_CABWE_DIAG_FIN_MASK |  \
		 WTW8365MB_INTW_INTEWWUPT_8051_MASK |  \
		 WTW8365MB_INTW_WOOP_DETECTION_MASK |  \
		 WTW8365MB_INTW_GWEEN_TIMEW_MASK |     \
		 WTW8365MB_INTW_SPECIAW_CONGEST_MASK | \
		 WTW8365MB_INTW_SPEED_CHANGE_MASK |    \
		 WTW8365MB_INTW_WEAWN_OVEW_MASK |      \
		 WTW8365MB_INTW_METEW_EXCEEDED_MASK |  \
		 WTW8365MB_INTW_WINK_CHANGE_MASK)

/* Pew-powt intewwupt type status wegistews */
#define WTW8365MB_POWT_WINKDOWN_IND_WEG		0x1106
#define   WTW8365MB_POWT_WINKDOWN_IND_MASK	0x07FF

#define WTW8365MB_POWT_WINKUP_IND_WEG		0x1107
#define   WTW8365MB_POWT_WINKUP_IND_MASK	0x07FF

/* PHY indiwect access wegistews */
#define WTW8365MB_INDIWECT_ACCESS_CTWW_WEG			0x1F00
#define   WTW8365MB_INDIWECT_ACCESS_CTWW_WW_MASK		0x0002
#define   WTW8365MB_INDIWECT_ACCESS_CTWW_WW_WEAD		0
#define   WTW8365MB_INDIWECT_ACCESS_CTWW_WW_WWITE		1
#define   WTW8365MB_INDIWECT_ACCESS_CTWW_CMD_MASK		0x0001
#define   WTW8365MB_INDIWECT_ACCESS_CTWW_CMD_VAWUE		1
#define WTW8365MB_INDIWECT_ACCESS_STATUS_WEG			0x1F01
#define WTW8365MB_INDIWECT_ACCESS_ADDWESS_WEG			0x1F02
#define   WTW8365MB_INDIWECT_ACCESS_ADDWESS_OCPADW_5_1_MASK	GENMASK(4, 0)
#define   WTW8365MB_INDIWECT_ACCESS_ADDWESS_PHYNUM_MASK		GENMASK(7, 5)
#define   WTW8365MB_INDIWECT_ACCESS_ADDWESS_OCPADW_9_6_MASK	GENMASK(11, 8)
#define   WTW8365MB_PHY_BASE					0x2000
#define WTW8365MB_INDIWECT_ACCESS_WWITE_DATA_WEG		0x1F03
#define WTW8365MB_INDIWECT_ACCESS_WEAD_DATA_WEG			0x1F04

/* PHY OCP addwess pwefix wegistew */
#define WTW8365MB_GPHY_OCP_MSB_0_WEG			0x1D15
#define   WTW8365MB_GPHY_OCP_MSB_0_CFG_CPU_OCPADW_MASK	0x0FC0
#define WTW8365MB_PHY_OCP_ADDW_PWEFIX_MASK		0xFC00

/* The PHY OCP addwesses of PHY wegistews 0~31 stawt hewe */
#define WTW8365MB_PHY_OCP_ADDW_PHYWEG_BASE		0xA400

/* Extewnaw intewface powt mode vawues - used in DIGITAW_INTEWFACE_SEWECT */
#define WTW8365MB_EXT_POWT_MODE_DISABWE		0
#define WTW8365MB_EXT_POWT_MODE_WGMII		1
#define WTW8365MB_EXT_POWT_MODE_MII_MAC		2
#define WTW8365MB_EXT_POWT_MODE_MII_PHY		3
#define WTW8365MB_EXT_POWT_MODE_TMII_MAC	4
#define WTW8365MB_EXT_POWT_MODE_TMII_PHY	5
#define WTW8365MB_EXT_POWT_MODE_GMII		6
#define WTW8365MB_EXT_POWT_MODE_WMII_MAC	7
#define WTW8365MB_EXT_POWT_MODE_WMII_PHY	8
#define WTW8365MB_EXT_POWT_MODE_SGMII		9
#define WTW8365MB_EXT_POWT_MODE_HSGMII		10
#define WTW8365MB_EXT_POWT_MODE_1000X_100FX	11
#define WTW8365MB_EXT_POWT_MODE_1000X		12
#define WTW8365MB_EXT_POWT_MODE_100FX		13

/* Extewnaw intewface mode configuwation wegistews 0~1 */
#define WTW8365MB_DIGITAW_INTEWFACE_SEWECT_WEG0		0x1305 /* EXT1 */
#define WTW8365MB_DIGITAW_INTEWFACE_SEWECT_WEG1		0x13C3 /* EXT2 */
#define WTW8365MB_DIGITAW_INTEWFACE_SEWECT_WEG(_extint) \
		((_extint) == 1 ? WTW8365MB_DIGITAW_INTEWFACE_SEWECT_WEG0 : \
		 (_extint) == 2 ? WTW8365MB_DIGITAW_INTEWFACE_SEWECT_WEG1 : \
		 0x0)
#define   WTW8365MB_DIGITAW_INTEWFACE_SEWECT_MODE_MASK(_extint) \
		(0xF << (((_extint) % 2)))
#define   WTW8365MB_DIGITAW_INTEWFACE_SEWECT_MODE_OFFSET(_extint) \
		(((_extint) % 2) * 4)

/* Extewnaw intewface WGMII TX/WX deway configuwation wegistews 0~2 */
#define WTW8365MB_EXT_WGMXF_WEG0		0x1306 /* EXT0 */
#define WTW8365MB_EXT_WGMXF_WEG1		0x1307 /* EXT1 */
#define WTW8365MB_EXT_WGMXF_WEG2		0x13C5 /* EXT2 */
#define WTW8365MB_EXT_WGMXF_WEG(_extint) \
		((_extint) == 0 ? WTW8365MB_EXT_WGMXF_WEG0 : \
		 (_extint) == 1 ? WTW8365MB_EXT_WGMXF_WEG1 : \
		 (_extint) == 2 ? WTW8365MB_EXT_WGMXF_WEG2 : \
		 0x0)
#define   WTW8365MB_EXT_WGMXF_WXDEWAY_MASK	0x0007
#define   WTW8365MB_EXT_WGMXF_TXDEWAY_MASK	0x0008

/* Extewnaw intewface powt speed vawues - used in DIGITAW_INTEWFACE_FOWCE */
#define WTW8365MB_POWT_SPEED_10M	0
#define WTW8365MB_POWT_SPEED_100M	1
#define WTW8365MB_POWT_SPEED_1000M	2

/* Extewnaw intewface fowce configuwation wegistews 0~2 */
#define WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG0		0x1310 /* EXT0 */
#define WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG1		0x1311 /* EXT1 */
#define WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG2		0x13C4 /* EXT2 */
#define WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG(_extint) \
		((_extint) == 0 ? WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG0 : \
		 (_extint) == 1 ? WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG1 : \
		 (_extint) == 2 ? WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG2 : \
		 0x0)
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_EN_MASK		0x1000
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_NWAY_MASK		0x0080
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_TXPAUSE_MASK	0x0040
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WXPAUSE_MASK	0x0020
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WINK_MASK		0x0010
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_DUPWEX_MASK		0x0004
#define   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_SPEED_MASK		0x0003

/* CPU powt mask wegistew - contwows which powts awe tweated as CPU powts */
#define WTW8365MB_CPU_POWT_MASK_WEG	0x1219
#define   WTW8365MB_CPU_POWT_MASK_MASK	0x07FF

/* CPU contwow wegistew */
#define WTW8365MB_CPU_CTWW_WEG			0x121A
#define   WTW8365MB_CPU_CTWW_TWAP_POWT_EXT_MASK	0x0400
#define   WTW8365MB_CPU_CTWW_TAG_FOWMAT_MASK	0x0200
#define   WTW8365MB_CPU_CTWW_WXBYTECOUNT_MASK	0x0080
#define   WTW8365MB_CPU_CTWW_TAG_POSITION_MASK	0x0040
#define   WTW8365MB_CPU_CTWW_TWAP_POWT_MASK	0x0038
#define   WTW8365MB_CPU_CTWW_INSEWTMODE_MASK	0x0006
#define   WTW8365MB_CPU_CTWW_EN_MASK		0x0001

/* Maximum packet wength wegistew */
#define WTW8365MB_CFG0_MAX_WEN_WEG	0x088C
#define   WTW8365MB_CFG0_MAX_WEN_MASK	0x3FFF
#define WTW8365MB_CFG0_MAX_WEN_MAX	0x3FFF

/* Powt weawning wimit wegistews */
#define WTW8365MB_WUT_POWT_WEAWN_WIMIT_BASE		0x0A20
#define WTW8365MB_WUT_POWT_WEAWN_WIMIT_WEG(_physpowt) \
		(WTW8365MB_WUT_POWT_WEAWN_WIMIT_BASE + (_physpowt))

/* Powt isowation (fowwawding mask) wegistews */
#define WTW8365MB_POWT_ISOWATION_WEG_BASE		0x08A2
#define WTW8365MB_POWT_ISOWATION_WEG(_physpowt) \
		(WTW8365MB_POWT_ISOWATION_WEG_BASE + (_physpowt))
#define   WTW8365MB_POWT_ISOWATION_MASK			0x07FF

/* MSTP powt state wegistews - indexed by twee instance */
#define WTW8365MB_MSTI_CTWW_BASE			0x0A00
#define WTW8365MB_MSTI_CTWW_WEG(_msti, _physpowt) \
		(WTW8365MB_MSTI_CTWW_BASE + ((_msti) << 1) + ((_physpowt) >> 3))
#define   WTW8365MB_MSTI_CTWW_POWT_STATE_OFFSET(_physpowt) ((_physpowt) << 1)
#define   WTW8365MB_MSTI_CTWW_POWT_STATE_MASK(_physpowt) \
		(0x3 << WTW8365MB_MSTI_CTWW_POWT_STATE_OFFSET((_physpowt)))

/* MIB countew vawue wegistews */
#define WTW8365MB_MIB_COUNTEW_BASE	0x1000
#define WTW8365MB_MIB_COUNTEW_WEG(_x)	(WTW8365MB_MIB_COUNTEW_BASE + (_x))

/* MIB countew addwess wegistew */
#define WTW8365MB_MIB_ADDWESS_WEG		0x1004
#define   WTW8365MB_MIB_ADDWESS_POWT_OFFSET	0x007C
#define   WTW8365MB_MIB_ADDWESS(_p, _x) \
		(((WTW8365MB_MIB_ADDWESS_POWT_OFFSET) * (_p) + (_x)) >> 2)

#define WTW8365MB_MIB_CTWW0_WEG			0x1005
#define   WTW8365MB_MIB_CTWW0_WESET_MASK	0x0002
#define   WTW8365MB_MIB_CTWW0_BUSY_MASK		0x0001

/* The DSA cawwback .get_stats64 wuns in atomic context, so we awe not awwowed
 * to bwock. On the othew hand, accessing MIB countews absowutewy wequiwes us to
 * bwock. The sowution is thus to scheduwe wowk which powws the MIB countews
 * asynchwonouswy and updates some pwivate data, which the cawwback can then
 * fetch atomicawwy. Thwee seconds shouwd be a good enough powwing intewvaw.
 */
#define WTW8365MB_STATS_INTEWVAW_JIFFIES	(3 * HZ)

enum wtw8365mb_mib_countew_index {
	WTW8365MB_MIB_ifInOctets,
	WTW8365MB_MIB_dot3StatsFCSEwwows,
	WTW8365MB_MIB_dot3StatsSymbowEwwows,
	WTW8365MB_MIB_dot3InPauseFwames,
	WTW8365MB_MIB_dot3ContwowInUnknownOpcodes,
	WTW8365MB_MIB_ethewStatsFwagments,
	WTW8365MB_MIB_ethewStatsJabbews,
	WTW8365MB_MIB_ifInUcastPkts,
	WTW8365MB_MIB_ethewStatsDwopEvents,
	WTW8365MB_MIB_ifInMuwticastPkts,
	WTW8365MB_MIB_ifInBwoadcastPkts,
	WTW8365MB_MIB_inMwdChecksumEwwow,
	WTW8365MB_MIB_inIgmpChecksumEwwow,
	WTW8365MB_MIB_inMwdSpecificQuewy,
	WTW8365MB_MIB_inMwdGenewawQuewy,
	WTW8365MB_MIB_inIgmpSpecificQuewy,
	WTW8365MB_MIB_inIgmpGenewawQuewy,
	WTW8365MB_MIB_inMwdWeaves,
	WTW8365MB_MIB_inIgmpWeaves,
	WTW8365MB_MIB_ethewStatsOctets,
	WTW8365MB_MIB_ethewStatsUndewSizePkts,
	WTW8365MB_MIB_ethewOvewsizeStats,
	WTW8365MB_MIB_ethewStatsPkts64Octets,
	WTW8365MB_MIB_ethewStatsPkts65to127Octets,
	WTW8365MB_MIB_ethewStatsPkts128to255Octets,
	WTW8365MB_MIB_ethewStatsPkts256to511Octets,
	WTW8365MB_MIB_ethewStatsPkts512to1023Octets,
	WTW8365MB_MIB_ethewStatsPkts1024to1518Octets,
	WTW8365MB_MIB_ifOutOctets,
	WTW8365MB_MIB_dot3StatsSingweCowwisionFwames,
	WTW8365MB_MIB_dot3StatsMuwtipweCowwisionFwames,
	WTW8365MB_MIB_dot3StatsDefewwedTwansmissions,
	WTW8365MB_MIB_dot3StatsWateCowwisions,
	WTW8365MB_MIB_ethewStatsCowwisions,
	WTW8365MB_MIB_dot3StatsExcessiveCowwisions,
	WTW8365MB_MIB_dot3OutPauseFwames,
	WTW8365MB_MIB_ifOutDiscawds,
	WTW8365MB_MIB_dot1dTpPowtInDiscawds,
	WTW8365MB_MIB_ifOutUcastPkts,
	WTW8365MB_MIB_ifOutMuwticastPkts,
	WTW8365MB_MIB_ifOutBwoadcastPkts,
	WTW8365MB_MIB_outOampduPkts,
	WTW8365MB_MIB_inOampduPkts,
	WTW8365MB_MIB_inIgmpJoinsSuccess,
	WTW8365MB_MIB_inIgmpJoinsFaiw,
	WTW8365MB_MIB_inMwdJoinsSuccess,
	WTW8365MB_MIB_inMwdJoinsFaiw,
	WTW8365MB_MIB_inWepowtSuppwessionDwop,
	WTW8365MB_MIB_inWeaveSuppwessionDwop,
	WTW8365MB_MIB_outIgmpWepowts,
	WTW8365MB_MIB_outIgmpWeaves,
	WTW8365MB_MIB_outIgmpGenewawQuewy,
	WTW8365MB_MIB_outIgmpSpecificQuewy,
	WTW8365MB_MIB_outMwdWepowts,
	WTW8365MB_MIB_outMwdWeaves,
	WTW8365MB_MIB_outMwdGenewawQuewy,
	WTW8365MB_MIB_outMwdSpecificQuewy,
	WTW8365MB_MIB_inKnownMuwticastPkts,
	WTW8365MB_MIB_END,
};

stwuct wtw8365mb_mib_countew {
	u32 offset;
	u32 wength;
	const chaw *name;
};

#define WTW8365MB_MAKE_MIB_COUNTEW(_offset, _wength, _name) \
		[WTW8365MB_MIB_ ## _name] = { _offset, _wength, #_name }

static stwuct wtw8365mb_mib_countew wtw8365mb_mib_countews[] = {
	WTW8365MB_MAKE_MIB_COUNTEW(0, 4, ifInOctets),
	WTW8365MB_MAKE_MIB_COUNTEW(4, 2, dot3StatsFCSEwwows),
	WTW8365MB_MAKE_MIB_COUNTEW(6, 2, dot3StatsSymbowEwwows),
	WTW8365MB_MAKE_MIB_COUNTEW(8, 2, dot3InPauseFwames),
	WTW8365MB_MAKE_MIB_COUNTEW(10, 2, dot3ContwowInUnknownOpcodes),
	WTW8365MB_MAKE_MIB_COUNTEW(12, 2, ethewStatsFwagments),
	WTW8365MB_MAKE_MIB_COUNTEW(14, 2, ethewStatsJabbews),
	WTW8365MB_MAKE_MIB_COUNTEW(16, 2, ifInUcastPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(18, 2, ethewStatsDwopEvents),
	WTW8365MB_MAKE_MIB_COUNTEW(20, 2, ifInMuwticastPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(22, 2, ifInBwoadcastPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(24, 2, inMwdChecksumEwwow),
	WTW8365MB_MAKE_MIB_COUNTEW(26, 2, inIgmpChecksumEwwow),
	WTW8365MB_MAKE_MIB_COUNTEW(28, 2, inMwdSpecificQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(30, 2, inMwdGenewawQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(32, 2, inIgmpSpecificQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(34, 2, inIgmpGenewawQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(36, 2, inMwdWeaves),
	WTW8365MB_MAKE_MIB_COUNTEW(38, 2, inIgmpWeaves),
	WTW8365MB_MAKE_MIB_COUNTEW(40, 4, ethewStatsOctets),
	WTW8365MB_MAKE_MIB_COUNTEW(44, 2, ethewStatsUndewSizePkts),
	WTW8365MB_MAKE_MIB_COUNTEW(46, 2, ethewOvewsizeStats),
	WTW8365MB_MAKE_MIB_COUNTEW(48, 2, ethewStatsPkts64Octets),
	WTW8365MB_MAKE_MIB_COUNTEW(50, 2, ethewStatsPkts65to127Octets),
	WTW8365MB_MAKE_MIB_COUNTEW(52, 2, ethewStatsPkts128to255Octets),
	WTW8365MB_MAKE_MIB_COUNTEW(54, 2, ethewStatsPkts256to511Octets),
	WTW8365MB_MAKE_MIB_COUNTEW(56, 2, ethewStatsPkts512to1023Octets),
	WTW8365MB_MAKE_MIB_COUNTEW(58, 2, ethewStatsPkts1024to1518Octets),
	WTW8365MB_MAKE_MIB_COUNTEW(60, 4, ifOutOctets),
	WTW8365MB_MAKE_MIB_COUNTEW(64, 2, dot3StatsSingweCowwisionFwames),
	WTW8365MB_MAKE_MIB_COUNTEW(66, 2, dot3StatsMuwtipweCowwisionFwames),
	WTW8365MB_MAKE_MIB_COUNTEW(68, 2, dot3StatsDefewwedTwansmissions),
	WTW8365MB_MAKE_MIB_COUNTEW(70, 2, dot3StatsWateCowwisions),
	WTW8365MB_MAKE_MIB_COUNTEW(72, 2, ethewStatsCowwisions),
	WTW8365MB_MAKE_MIB_COUNTEW(74, 2, dot3StatsExcessiveCowwisions),
	WTW8365MB_MAKE_MIB_COUNTEW(76, 2, dot3OutPauseFwames),
	WTW8365MB_MAKE_MIB_COUNTEW(78, 2, ifOutDiscawds),
	WTW8365MB_MAKE_MIB_COUNTEW(80, 2, dot1dTpPowtInDiscawds),
	WTW8365MB_MAKE_MIB_COUNTEW(82, 2, ifOutUcastPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(84, 2, ifOutMuwticastPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(86, 2, ifOutBwoadcastPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(88, 2, outOampduPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(90, 2, inOampduPkts),
	WTW8365MB_MAKE_MIB_COUNTEW(92, 4, inIgmpJoinsSuccess),
	WTW8365MB_MAKE_MIB_COUNTEW(96, 2, inIgmpJoinsFaiw),
	WTW8365MB_MAKE_MIB_COUNTEW(98, 2, inMwdJoinsSuccess),
	WTW8365MB_MAKE_MIB_COUNTEW(100, 2, inMwdJoinsFaiw),
	WTW8365MB_MAKE_MIB_COUNTEW(102, 2, inWepowtSuppwessionDwop),
	WTW8365MB_MAKE_MIB_COUNTEW(104, 2, inWeaveSuppwessionDwop),
	WTW8365MB_MAKE_MIB_COUNTEW(106, 2, outIgmpWepowts),
	WTW8365MB_MAKE_MIB_COUNTEW(108, 2, outIgmpWeaves),
	WTW8365MB_MAKE_MIB_COUNTEW(110, 2, outIgmpGenewawQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(112, 2, outIgmpSpecificQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(114, 2, outMwdWepowts),
	WTW8365MB_MAKE_MIB_COUNTEW(116, 2, outMwdWeaves),
	WTW8365MB_MAKE_MIB_COUNTEW(118, 2, outMwdGenewawQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(120, 2, outMwdSpecificQuewy),
	WTW8365MB_MAKE_MIB_COUNTEW(122, 2, inKnownMuwticastPkts),
};

static_assewt(AWWAY_SIZE(wtw8365mb_mib_countews) == WTW8365MB_MIB_END);

stwuct wtw8365mb_jam_tbw_entwy {
	u16 weg;
	u16 vaw;
};

/* Wifted fwom the vendow dwivew souwces */
static const stwuct wtw8365mb_jam_tbw_entwy wtw8365mb_init_jam_8365mb_vc[] = {
	{ 0x13EB, 0x15BB }, { 0x1303, 0x06D6 }, { 0x1304, 0x0700 },
	{ 0x13E2, 0x003F }, { 0x13F9, 0x0090 }, { 0x121E, 0x03CA },
	{ 0x1233, 0x0352 }, { 0x1237, 0x00A0 }, { 0x123A, 0x0030 },
	{ 0x1239, 0x0084 }, { 0x0301, 0x1000 }, { 0x1349, 0x001F },
	{ 0x18E0, 0x4004 }, { 0x122B, 0x241C }, { 0x1305, 0xC000 },
	{ 0x13F0, 0x0000 },
};

static const stwuct wtw8365mb_jam_tbw_entwy wtw8365mb_init_jam_common[] = {
	{ 0x1200, 0x7FCB }, { 0x0884, 0x0003 }, { 0x06EB, 0x0001 },
	{ 0x03Fa, 0x0007 }, { 0x08C8, 0x00C0 }, { 0x0A30, 0x020E },
	{ 0x0800, 0x0000 }, { 0x0802, 0x0000 }, { 0x09DA, 0x0013 },
	{ 0x1D32, 0x0002 },
};

enum wtw8365mb_phy_intewface_mode {
	WTW8365MB_PHY_INTEWFACE_MODE_INVAW = 0,
	WTW8365MB_PHY_INTEWFACE_MODE_INTEWNAW = BIT(0),
	WTW8365MB_PHY_INTEWFACE_MODE_MII = BIT(1),
	WTW8365MB_PHY_INTEWFACE_MODE_TMII = BIT(2),
	WTW8365MB_PHY_INTEWFACE_MODE_WMII = BIT(3),
	WTW8365MB_PHY_INTEWFACE_MODE_WGMII = BIT(4),
	WTW8365MB_PHY_INTEWFACE_MODE_SGMII = BIT(5),
	WTW8365MB_PHY_INTEWFACE_MODE_HSGMII = BIT(6),
};

/**
 * stwuct wtw8365mb_extint - extewnaw intewface info
 * @powt: the powt with an extewnaw intewface
 * @id: the extewnaw intewface ID, which is eithew 0, 1, ow 2
 * @suppowted_intewfaces: a bitmask of suppowted PHY intewface modes
 *
 * Wepwesents a mapping: powt -> { id, suppowted_intewfaces }. To be embedded
 * in &stwuct wtw8365mb_chip_info fow evewy powt with an extewnaw intewface.
 */
stwuct wtw8365mb_extint {
	int powt;
	int id;
	unsigned int suppowted_intewfaces;
};

/**
 * stwuct wtw8365mb_chip_info - static chip-specific info
 * @name: human-weadabwe chip name
 * @chip_id: chip identifiew
 * @chip_vew: chip siwicon wevision
 * @extints: avaiwabwe extewnaw intewfaces
 * @jam_tabwe: chip-specific initiawization jam tabwe
 * @jam_size: size of the chip's jam tabwe
 *
 * These data awe specific to a given chip in the famiwy of switches suppowted
 * by this dwivew. When adding suppowt fow anothew chip in the famiwy, a new
 * chip info shouwd be added to the wtw8365mb_chip_infos awway.
 */
stwuct wtw8365mb_chip_info {
	const chaw *name;
	u32 chip_id;
	u32 chip_vew;
	const stwuct wtw8365mb_extint extints[WTW8365MB_MAX_NUM_EXTINTS];
	const stwuct wtw8365mb_jam_tbw_entwy *jam_tabwe;
	size_t jam_size;
};

/* Chip info fow each suppowted switch in the famiwy */
#define PHY_INTF(_mode) (WTW8365MB_PHY_INTEWFACE_MODE_ ## _mode)
static const stwuct wtw8365mb_chip_info wtw8365mb_chip_infos[] = {
	{
		.name = "WTW8365MB-VC",
		.chip_id = 0x6367,
		.chip_vew = 0x0040,
		.extints = {
			{ 6, 1, PHY_INTF(MII) | PHY_INTF(TMII) |
				PHY_INTF(WMII) | PHY_INTF(WGMII) },
		},
		.jam_tabwe = wtw8365mb_init_jam_8365mb_vc,
		.jam_size = AWWAY_SIZE(wtw8365mb_init_jam_8365mb_vc),
	},
	{
		.name = "WTW8367S",
		.chip_id = 0x6367,
		.chip_vew = 0x00A0,
		.extints = {
			{ 6, 1, PHY_INTF(SGMII) | PHY_INTF(HSGMII) },
			{ 7, 2, PHY_INTF(MII) | PHY_INTF(TMII) |
				PHY_INTF(WMII) | PHY_INTF(WGMII) },
		},
		.jam_tabwe = wtw8365mb_init_jam_8365mb_vc,
		.jam_size = AWWAY_SIZE(wtw8365mb_init_jam_8365mb_vc),
	},
	{
		.name = "WTW8367WB-VB",
		.chip_id = 0x6367,
		.chip_vew = 0x0020,
		.extints = {
			{ 6, 1, PHY_INTF(MII) | PHY_INTF(TMII) |
				PHY_INTF(WMII) | PHY_INTF(WGMII) },
			{ 7, 2, PHY_INTF(MII) | PHY_INTF(TMII) |
				PHY_INTF(WMII) | PHY_INTF(WGMII) },
		},
		.jam_tabwe = wtw8365mb_init_jam_8365mb_vc,
		.jam_size = AWWAY_SIZE(wtw8365mb_init_jam_8365mb_vc),
	},
};

enum wtw8365mb_stp_state {
	WTW8365MB_STP_STATE_DISABWED = 0,
	WTW8365MB_STP_STATE_BWOCKING = 1,
	WTW8365MB_STP_STATE_WEAWNING = 2,
	WTW8365MB_STP_STATE_FOWWAWDING = 3,
};

enum wtw8365mb_cpu_insewt {
	WTW8365MB_CPU_INSEWT_TO_AWW = 0,
	WTW8365MB_CPU_INSEWT_TO_TWAPPING = 1,
	WTW8365MB_CPU_INSEWT_TO_NONE = 2,
};

enum wtw8365mb_cpu_position {
	WTW8365MB_CPU_POS_AFTEW_SA = 0,
	WTW8365MB_CPU_POS_BEFOWE_CWC = 1,
};

enum wtw8365mb_cpu_fowmat {
	WTW8365MB_CPU_FOWMAT_8BYTES = 0,
	WTW8365MB_CPU_FOWMAT_4BYTES = 1,
};

enum wtw8365mb_cpu_wxwen {
	WTW8365MB_CPU_WXWEN_72BYTES = 0,
	WTW8365MB_CPU_WXWEN_64BYTES = 1,
};

/**
 * stwuct wtw8365mb_cpu - CPU powt configuwation
 * @enabwe: enabwe/disabwe hawdwawe insewtion of CPU tag in switch->CPU fwames
 * @mask: powt mask of powts that pawse shouwd pawse CPU tags
 * @twap_powt: fowwawd twapped fwames to this powt
 * @insewt: CPU tag insewtion mode in switch->CPU fwames
 * @position: position of CPU tag in fwame
 * @wx_wength: minimum CPU WX wength
 * @fowmat: CPU tag fowmat
 *
 * Wepwesents the CPU tagging and CPU powt configuwation of the switch. These
 * settings awe configuwabwe at wuntime.
 */
stwuct wtw8365mb_cpu {
	boow enabwe;
	u32 mask;
	u32 twap_powt;
	enum wtw8365mb_cpu_insewt insewt;
	enum wtw8365mb_cpu_position position;
	enum wtw8365mb_cpu_wxwen wx_wength;
	enum wtw8365mb_cpu_fowmat fowmat;
};

/**
 * stwuct wtw8365mb_powt - pwivate pew-powt data
 * @pwiv: pointew to pawent weawtek_pwiv data
 * @index: DSA powt index, same as dsa_powt::index
 * @stats: wink statistics popuwated by wtw8365mb_stats_poww, weady fow atomic
 *         access via wtw8365mb_get_stats64
 * @stats_wock: pwotect the stats stwuctuwe duwing wead/update
 * @mib_wowk: dewayed wowk fow powwing MIB countews
 */
stwuct wtw8365mb_powt {
	stwuct weawtek_pwiv *pwiv;
	unsigned int index;
	stwuct wtnw_wink_stats64 stats;
	spinwock_t stats_wock;
	stwuct dewayed_wowk mib_wowk;
};

/**
 * stwuct wtw8365mb - dwivew pwivate data
 * @pwiv: pointew to pawent weawtek_pwiv data
 * @iwq: wegistewed IWQ ow zewo
 * @chip_info: chip-specific info about the attached switch
 * @cpu: CPU tagging and CPU powt configuwation fow this chip
 * @mib_wock: pwevent concuwwent weads of MIB countews
 * @powts: pew-powt data
 *
 * Pwivate data fow this dwivew.
 */
stwuct wtw8365mb {
	stwuct weawtek_pwiv *pwiv;
	int iwq;
	const stwuct wtw8365mb_chip_info *chip_info;
	stwuct wtw8365mb_cpu cpu;
	stwuct mutex mib_wock;
	stwuct wtw8365mb_powt powts[WTW8365MB_MAX_NUM_POWTS];
};

static int wtw8365mb_phy_poww_busy(stwuct weawtek_pwiv *pwiv)
{
	u32 vaw;

	wetuwn wegmap_wead_poww_timeout(pwiv->map_nowock,
					WTW8365MB_INDIWECT_ACCESS_STATUS_WEG,
					vaw, !vaw, 10, 100);
}

static int wtw8365mb_phy_ocp_pwepawe(stwuct weawtek_pwiv *pwiv, int phy,
				     u32 ocp_addw)
{
	u32 vaw;
	int wet;

	/* Set OCP pwefix */
	vaw = FIEWD_GET(WTW8365MB_PHY_OCP_ADDW_PWEFIX_MASK, ocp_addw);
	wet = wegmap_update_bits(
		pwiv->map_nowock, WTW8365MB_GPHY_OCP_MSB_0_WEG,
		WTW8365MB_GPHY_OCP_MSB_0_CFG_CPU_OCPADW_MASK,
		FIEWD_PWEP(WTW8365MB_GPHY_OCP_MSB_0_CFG_CPU_OCPADW_MASK, vaw));
	if (wet)
		wetuwn wet;

	/* Set PHY wegistew addwess */
	vaw = WTW8365MB_PHY_BASE;
	vaw |= FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_ADDWESS_PHYNUM_MASK, phy);
	vaw |= FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_ADDWESS_OCPADW_5_1_MASK,
			  ocp_addw >> 1);
	vaw |= FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_ADDWESS_OCPADW_9_6_MASK,
			  ocp_addw >> 6);
	wet = wegmap_wwite(pwiv->map_nowock,
			   WTW8365MB_INDIWECT_ACCESS_ADDWESS_WEG, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtw8365mb_phy_ocp_wead(stwuct weawtek_pwiv *pwiv, int phy,
				  u32 ocp_addw, u16 *data)
{
	u32 vaw;
	int wet;

	mutex_wock(&pwiv->map_wock);

	wet = wtw8365mb_phy_poww_busy(pwiv);
	if (wet)
		goto out;

	wet = wtw8365mb_phy_ocp_pwepawe(pwiv, phy, ocp_addw);
	if (wet)
		goto out;

	/* Execute wead opewation */
	vaw = FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_CTWW_CMD_MASK,
			 WTW8365MB_INDIWECT_ACCESS_CTWW_CMD_VAWUE) |
	      FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_CTWW_WW_MASK,
			 WTW8365MB_INDIWECT_ACCESS_CTWW_WW_WEAD);
	wet = wegmap_wwite(pwiv->map_nowock, WTW8365MB_INDIWECT_ACCESS_CTWW_WEG,
			   vaw);
	if (wet)
		goto out;

	wet = wtw8365mb_phy_poww_busy(pwiv);
	if (wet)
		goto out;

	/* Get PHY wegistew data */
	wet = wegmap_wead(pwiv->map_nowock,
			  WTW8365MB_INDIWECT_ACCESS_WEAD_DATA_WEG, &vaw);
	if (wet)
		goto out;

	*data = vaw & 0xFFFF;

out:
	mutex_unwock(&pwiv->map_wock);

	wetuwn wet;
}

static int wtw8365mb_phy_ocp_wwite(stwuct weawtek_pwiv *pwiv, int phy,
				   u32 ocp_addw, u16 data)
{
	u32 vaw;
	int wet;

	mutex_wock(&pwiv->map_wock);

	wet = wtw8365mb_phy_poww_busy(pwiv);
	if (wet)
		goto out;

	wet = wtw8365mb_phy_ocp_pwepawe(pwiv, phy, ocp_addw);
	if (wet)
		goto out;

	/* Set PHY wegistew data */
	wet = wegmap_wwite(pwiv->map_nowock,
			   WTW8365MB_INDIWECT_ACCESS_WWITE_DATA_WEG, data);
	if (wet)
		goto out;

	/* Execute wwite opewation */
	vaw = FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_CTWW_CMD_MASK,
			 WTW8365MB_INDIWECT_ACCESS_CTWW_CMD_VAWUE) |
	      FIEWD_PWEP(WTW8365MB_INDIWECT_ACCESS_CTWW_WW_MASK,
			 WTW8365MB_INDIWECT_ACCESS_CTWW_WW_WWITE);
	wet = wegmap_wwite(pwiv->map_nowock, WTW8365MB_INDIWECT_ACCESS_CTWW_WEG,
			   vaw);
	if (wet)
		goto out;

	wet = wtw8365mb_phy_poww_busy(pwiv);
	if (wet)
		goto out;

out:
	mutex_unwock(&pwiv->map_wock);

	wetuwn 0;
}

static int wtw8365mb_phy_wead(stwuct weawtek_pwiv *pwiv, int phy, int wegnum)
{
	u32 ocp_addw;
	u16 vaw;
	int wet;

	if (phy > WTW8365MB_PHYADDWMAX)
		wetuwn -EINVAW;

	if (wegnum > WTW8365MB_PHYWEGMAX)
		wetuwn -EINVAW;

	ocp_addw = WTW8365MB_PHY_OCP_ADDW_PHYWEG_BASE + wegnum * 2;

	wet = wtw8365mb_phy_ocp_wead(pwiv, phy, ocp_addw, &vaw);
	if (wet) {
		dev_eww(pwiv->dev,
			"faiwed to wead PHY%d weg %02x @ %04x, wet %d\n", phy,
			wegnum, ocp_addw, wet);
		wetuwn wet;
	}

	dev_dbg(pwiv->dev, "wead PHY%d wegistew 0x%02x @ %04x, vaw <- %04x\n",
		phy, wegnum, ocp_addw, vaw);

	wetuwn vaw;
}

static int wtw8365mb_phy_wwite(stwuct weawtek_pwiv *pwiv, int phy, int wegnum,
			       u16 vaw)
{
	u32 ocp_addw;
	int wet;

	if (phy > WTW8365MB_PHYADDWMAX)
		wetuwn -EINVAW;

	if (wegnum > WTW8365MB_PHYWEGMAX)
		wetuwn -EINVAW;

	ocp_addw = WTW8365MB_PHY_OCP_ADDW_PHYWEG_BASE + wegnum * 2;

	wet = wtw8365mb_phy_ocp_wwite(pwiv, phy, ocp_addw, vaw);
	if (wet) {
		dev_eww(pwiv->dev,
			"faiwed to wwite PHY%d weg %02x @ %04x, wet %d\n", phy,
			wegnum, ocp_addw, wet);
		wetuwn wet;
	}

	dev_dbg(pwiv->dev, "wwite PHY%d wegistew 0x%02x @ %04x, vaw -> %04x\n",
		phy, wegnum, ocp_addw, vaw);

	wetuwn 0;
}

static int wtw8365mb_dsa_phy_wead(stwuct dsa_switch *ds, int phy, int wegnum)
{
	wetuwn wtw8365mb_phy_wead(ds->pwiv, phy, wegnum);
}

static int wtw8365mb_dsa_phy_wwite(stwuct dsa_switch *ds, int phy, int wegnum,
				   u16 vaw)
{
	wetuwn wtw8365mb_phy_wwite(ds->pwiv, phy, wegnum, vaw);
}

static const stwuct wtw8365mb_extint *
wtw8365mb_get_powt_extint(stwuct weawtek_pwiv *pwiv, int powt)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	int i;

	fow (i = 0; i < WTW8365MB_MAX_NUM_EXTINTS; i++) {
		const stwuct wtw8365mb_extint *extint =
			&mb->chip_info->extints[i];

		if (!extint->suppowted_intewfaces)
			continue;

		if (extint->powt == powt)
			wetuwn extint;
	}

	wetuwn NUWW;
}

static enum dsa_tag_pwotocow
wtw8365mb_get_tag_pwotocow(stwuct dsa_switch *ds, int powt,
			   enum dsa_tag_pwotocow mp)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_cpu *cpu;
	stwuct wtw8365mb *mb;

	mb = pwiv->chip_data;
	cpu = &mb->cpu;

	if (cpu->position == WTW8365MB_CPU_POS_BEFOWE_CWC)
		wetuwn DSA_TAG_PWOTO_WTW8_4T;

	wetuwn DSA_TAG_PWOTO_WTW8_4;
}

static int wtw8365mb_ext_config_wgmii(stwuct weawtek_pwiv *pwiv, int powt,
				      phy_intewface_t intewface)
{
	const stwuct wtw8365mb_extint *extint =
		wtw8365mb_get_powt_extint(pwiv, powt);
	stwuct device_node *dn;
	stwuct dsa_powt *dp;
	int tx_deway = 0;
	int wx_deway = 0;
	u32 vaw;
	int wet;

	if (!extint)
		wetuwn -ENODEV;

	dp = dsa_to_powt(pwiv->ds, powt);
	dn = dp->dn;

	/* Set the WGMII TX/WX deway
	 *
	 * The Weawtek vendow dwivew indicates the fowwowing possibwe
	 * configuwation settings:
	 *
	 *   TX deway:
	 *     0 = no deway, 1 = 2 ns deway
	 *   WX deway:
	 *     0 = no deway, 7 = maximum deway
	 *     Each step is appwoximatewy 0.3 ns, so the maximum deway is about
	 *     2.1 ns.
	 *
	 * The vendow dwivew awso states that this must be configuwed *befowe*
	 * fowcing the extewnaw intewface into a pawticuwaw mode, which is done
	 * in the wtw8365mb_phywink_mac_wink_{up,down} functions.
	 *
	 * Onwy configuwe an WGMII TX (wesp. WX) deway if the
	 * tx-intewnaw-deway-ps (wesp. wx-intewnaw-deway-ps) OF pwopewty is
	 * specified. We ignowe the detaiw of the WGMII intewface mode
	 * (WGMII_{WXID, TXID, etc.}), as this is considewed to be a PHY-onwy
	 * pwopewty.
	 */
	if (!of_pwopewty_wead_u32(dn, "tx-intewnaw-deway-ps", &vaw)) {
		vaw = vaw / 1000; /* convewt to ns */

		if (vaw == 0 || vaw == 2)
			tx_deway = vaw / 2;
		ewse
			dev_wawn(pwiv->dev,
				 "WGMII TX deway must be 0 ow 2 ns\n");
	}

	if (!of_pwopewty_wead_u32(dn, "wx-intewnaw-deway-ps", &vaw)) {
		vaw = DIV_WOUND_CWOSEST(vaw, 300); /* convewt to 0.3 ns step */

		if (vaw <= 7)
			wx_deway = vaw;
		ewse
			dev_wawn(pwiv->dev,
				 "WGMII WX deway must be 0 to 2.1 ns\n");
	}

	wet = wegmap_update_bits(
		pwiv->map, WTW8365MB_EXT_WGMXF_WEG(extint->id),
		WTW8365MB_EXT_WGMXF_TXDEWAY_MASK |
			WTW8365MB_EXT_WGMXF_WXDEWAY_MASK,
		FIEWD_PWEP(WTW8365MB_EXT_WGMXF_TXDEWAY_MASK, tx_deway) |
			FIEWD_PWEP(WTW8365MB_EXT_WGMXF_WXDEWAY_MASK, wx_deway));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(
		pwiv->map, WTW8365MB_DIGITAW_INTEWFACE_SEWECT_WEG(extint->id),
		WTW8365MB_DIGITAW_INTEWFACE_SEWECT_MODE_MASK(extint->id),
		WTW8365MB_EXT_POWT_MODE_WGMII
			<< WTW8365MB_DIGITAW_INTEWFACE_SEWECT_MODE_OFFSET(
				   extint->id));
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtw8365mb_ext_config_fowcemode(stwuct weawtek_pwiv *pwiv, int powt,
					  boow wink, int speed, int dupwex,
					  boow tx_pause, boow wx_pause)
{
	const stwuct wtw8365mb_extint *extint =
		wtw8365mb_get_powt_extint(pwiv, powt);
	u32 w_tx_pause;
	u32 w_wx_pause;
	u32 w_dupwex;
	u32 w_speed;
	u32 w_wink;
	int vaw;
	int wet;

	if (!extint)
		wetuwn -ENODEV;

	if (wink) {
		/* Fowce the wink up with the desiwed configuwation */
		w_wink = 1;
		w_wx_pause = wx_pause ? 1 : 0;
		w_tx_pause = tx_pause ? 1 : 0;

		if (speed == SPEED_1000) {
			w_speed = WTW8365MB_POWT_SPEED_1000M;
		} ewse if (speed == SPEED_100) {
			w_speed = WTW8365MB_POWT_SPEED_100M;
		} ewse if (speed == SPEED_10) {
			w_speed = WTW8365MB_POWT_SPEED_10M;
		} ewse {
			dev_eww(pwiv->dev, "unsuppowted powt speed %s\n",
				phy_speed_to_stw(speed));
			wetuwn -EINVAW;
		}

		if (dupwex == DUPWEX_FUWW) {
			w_dupwex = 1;
		} ewse if (dupwex == DUPWEX_HAWF) {
			w_dupwex = 0;
		} ewse {
			dev_eww(pwiv->dev, "unsuppowted dupwex %s\n",
				phy_dupwex_to_stw(dupwex));
			wetuwn -EINVAW;
		}
	} ewse {
		/* Fowce the wink down and weset any pwogwammed configuwation */
		w_wink = 0;
		w_tx_pause = 0;
		w_wx_pause = 0;
		w_speed = 0;
		w_dupwex = 0;
	}

	vaw = FIEWD_PWEP(WTW8365MB_DIGITAW_INTEWFACE_FOWCE_EN_MASK, 1) |
	      FIEWD_PWEP(WTW8365MB_DIGITAW_INTEWFACE_FOWCE_TXPAUSE_MASK,
			 w_tx_pause) |
	      FIEWD_PWEP(WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WXPAUSE_MASK,
			 w_wx_pause) |
	      FIEWD_PWEP(WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WINK_MASK, w_wink) |
	      FIEWD_PWEP(WTW8365MB_DIGITAW_INTEWFACE_FOWCE_DUPWEX_MASK,
			 w_dupwex) |
	      FIEWD_PWEP(WTW8365MB_DIGITAW_INTEWFACE_FOWCE_SPEED_MASK, w_speed);
	wet = wegmap_wwite(pwiv->map,
			   WTW8365MB_DIGITAW_INTEWFACE_FOWCE_WEG(extint->id),
			   vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void wtw8365mb_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				       stwuct phywink_config *config)
{
	const stwuct wtw8365mb_extint *extint =
		wtw8365mb_get_powt_extint(ds->pwiv, powt);

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_ASYM_PAUSE |
				   MAC_10 | MAC_100 | MAC_1000FD;

	if (!extint) {
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);

		/* GMII is the defauwt intewface mode fow phywib, so
		 * we have to suppowt it fow powts with integwated PHY.
		 */
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
		wetuwn;
	}

	/* Popuwate accowding to the modes suppowted by _this dwivew_,
	 * not necessawiwy the modes suppowted by the hawdwawe, some of
	 * which wemain unimpwemented.
	 */

	if (extint->suppowted_intewfaces & WTW8365MB_PHY_INTEWFACE_MODE_WGMII)
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
}

static void wtw8365mb_phywink_mac_config(stwuct dsa_switch *ds, int powt,
					 unsigned int mode,
					 const stwuct phywink_wink_state *state)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	int wet;

	if (mode != MWO_AN_PHY && mode != MWO_AN_FIXED) {
		dev_eww(pwiv->dev,
			"powt %d suppowts onwy conventionaw PHY ow fixed-wink\n",
			powt);
		wetuwn;
	}

	if (phy_intewface_mode_is_wgmii(state->intewface)) {
		wet = wtw8365mb_ext_config_wgmii(pwiv, powt, state->intewface);
		if (wet)
			dev_eww(pwiv->dev,
				"faiwed to configuwe WGMII mode on powt %d: %d\n",
				powt, wet);
		wetuwn;
	}

	/* TODO: Impwement MII and WMII modes, which the WTW8365MB-VC awso
	 * suppowts
	 */
}

static void wtw8365mb_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
					    unsigned int mode,
					    phy_intewface_t intewface)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_powt *p;
	stwuct wtw8365mb *mb;
	int wet;

	mb = pwiv->chip_data;
	p = &mb->powts[powt];
	cancew_dewayed_wowk_sync(&p->mib_wowk);

	if (phy_intewface_mode_is_wgmii(intewface)) {
		wet = wtw8365mb_ext_config_fowcemode(pwiv, powt, fawse, 0, 0,
						     fawse, fawse);
		if (wet)
			dev_eww(pwiv->dev,
				"faiwed to weset fowced mode on powt %d: %d\n",
				powt, wet);

		wetuwn;
	}
}

static void wtw8365mb_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
					  unsigned int mode,
					  phy_intewface_t intewface,
					  stwuct phy_device *phydev, int speed,
					  int dupwex, boow tx_pause,
					  boow wx_pause)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_powt *p;
	stwuct wtw8365mb *mb;
	int wet;

	mb = pwiv->chip_data;
	p = &mb->powts[powt];
	scheduwe_dewayed_wowk(&p->mib_wowk, 0);

	if (phy_intewface_mode_is_wgmii(intewface)) {
		wet = wtw8365mb_ext_config_fowcemode(pwiv, powt, twue, speed,
						     dupwex, tx_pause,
						     wx_pause);
		if (wet)
			dev_eww(pwiv->dev,
				"faiwed to fowce mode on powt %d: %d\n", powt,
				wet);

		wetuwn;
	}
}

static int wtw8365mb_powt_change_mtu(stwuct dsa_switch *ds, int powt,
				     int new_mtu)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	int fwame_size;

	/* When a new MTU is set, DSA awways sets the CPU powt's MTU to the
	 * wawgest MTU of the usew powts. Because the switch onwy has a gwobaw
	 * WX wength wegistew, onwy awwowing CPU powt hewe is enough.
	 */
	if (!dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	fwame_size = new_mtu + VWAN_ETH_HWEN + ETH_FCS_WEN;

	dev_dbg(pwiv->dev, "changing mtu to %d (fwame size: %d)\n",
		new_mtu, fwame_size);

	wetuwn wegmap_update_bits(pwiv->map, WTW8365MB_CFG0_MAX_WEN_WEG,
				  WTW8365MB_CFG0_MAX_WEN_MASK,
				  FIEWD_PWEP(WTW8365MB_CFG0_MAX_WEN_MASK,
					     fwame_size));
}

static int wtw8365mb_powt_max_mtu(stwuct dsa_switch *ds, int powt)
{
	wetuwn WTW8365MB_CFG0_MAX_WEN_MAX - VWAN_ETH_HWEN - ETH_FCS_WEN;
}

static void wtw8365mb_powt_stp_state_set(stwuct dsa_switch *ds, int powt,
					 u8 state)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	enum wtw8365mb_stp_state vaw;
	int msti = 0;

	switch (state) {
	case BW_STATE_DISABWED:
		vaw = WTW8365MB_STP_STATE_DISABWED;
		bweak;
	case BW_STATE_BWOCKING:
	case BW_STATE_WISTENING:
		vaw = WTW8365MB_STP_STATE_BWOCKING;
		bweak;
	case BW_STATE_WEAWNING:
		vaw = WTW8365MB_STP_STATE_WEAWNING;
		bweak;
	case BW_STATE_FOWWAWDING:
		vaw = WTW8365MB_STP_STATE_FOWWAWDING;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "invawid STP state: %u\n", state);
		wetuwn;
	}

	wegmap_update_bits(pwiv->map, WTW8365MB_MSTI_CTWW_WEG(msti, powt),
			   WTW8365MB_MSTI_CTWW_POWT_STATE_MASK(powt),
			   vaw << WTW8365MB_MSTI_CTWW_POWT_STATE_OFFSET(powt));
}

static int wtw8365mb_powt_set_weawning(stwuct weawtek_pwiv *pwiv, int powt,
				       boow enabwe)
{
	/* Enabwe/disabwe weawning by wimiting the numbew of W2 addwesses the
	 * powt can weawn. Weawtek documentation states that a wimit of zewo
	 * disabwes weawning. When enabwing weawning, set it to the chip's
	 * maximum.
	 */
	wetuwn wegmap_wwite(pwiv->map, WTW8365MB_WUT_POWT_WEAWN_WIMIT_WEG(powt),
			    enabwe ? WTW8365MB_WEAWN_WIMIT_MAX : 0);
}

static int wtw8365mb_powt_set_isowation(stwuct weawtek_pwiv *pwiv, int powt,
					u32 mask)
{
	wetuwn wegmap_wwite(pwiv->map, WTW8365MB_POWT_ISOWATION_WEG(powt), mask);
}

static int wtw8365mb_mib_countew_wead(stwuct weawtek_pwiv *pwiv, int powt,
				      u32 offset, u32 wength, u64 *mibvawue)
{
	u64 tmpvawue = 0;
	u32 vaw;
	int wet;
	int i;

	/* The MIB addwess is an SWAM addwess. We wequest a pawticuwaw addwess
	 * and then poww the contwow wegistew befowe weading the vawue fwom some
	 * countew wegistews.
	 */
	wet = wegmap_wwite(pwiv->map, WTW8365MB_MIB_ADDWESS_WEG,
			   WTW8365MB_MIB_ADDWESS(powt, offset));
	if (wet)
		wetuwn wet;

	/* Poww fow compwetion */
	wet = wegmap_wead_poww_timeout(pwiv->map, WTW8365MB_MIB_CTWW0_WEG, vaw,
				       !(vaw & WTW8365MB_MIB_CTWW0_BUSY_MASK),
				       10, 100);
	if (wet)
		wetuwn wet;

	/* Pwesumabwy this indicates a MIB countew wead faiwuwe */
	if (vaw & WTW8365MB_MIB_CTWW0_WESET_MASK)
		wetuwn -EIO;

	/* Thewe awe fouw MIB countew wegistews each howding a 16 bit wowd of a
	 * MIB countew. Depending on the offset, we shouwd wead fwom the uppew
	 * two ow wowew two wegistews. In case the MIB countew is 4 wowds, we
	 * wead fwom aww fouw wegistews.
	 */
	if (wength == 4)
		offset = 3;
	ewse
		offset = (offset + 1) % 4;

	/* Wead the MIB countew 16 bits at a time */
	fow (i = 0; i < wength; i++) {
		wet = wegmap_wead(pwiv->map,
				  WTW8365MB_MIB_COUNTEW_WEG(offset - i), &vaw);
		if (wet)
			wetuwn wet;

		tmpvawue = ((tmpvawue) << 16) | (vaw & 0xFFFF);
	}

	/* Onwy commit the wesuwt if no ewwow occuwwed */
	*mibvawue = tmpvawue;

	wetuwn 0;
}

static void wtw8365mb_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, u64 *data)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb *mb;
	int wet;
	int i;

	mb = pwiv->chip_data;

	mutex_wock(&mb->mib_wock);
	fow (i = 0; i < WTW8365MB_MIB_END; i++) {
		stwuct wtw8365mb_mib_countew *mib = &wtw8365mb_mib_countews[i];

		wet = wtw8365mb_mib_countew_wead(pwiv, powt, mib->offset,
						 mib->wength, &data[i]);
		if (wet) {
			dev_eww(pwiv->dev,
				"faiwed to wead powt %d countews: %d\n", powt,
				wet);
			bweak;
		}
	}
	mutex_unwock(&mb->mib_wock);
}

static void wtw8365mb_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset, u8 *data)
{
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < WTW8365MB_MIB_END; i++) {
		stwuct wtw8365mb_mib_countew *mib = &wtw8365mb_mib_countews[i];
		ethtoow_puts(&data, mib->name);
	}
}

static int wtw8365mb_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;

	wetuwn WTW8365MB_MIB_END;
}

static void wtw8365mb_get_phy_stats(stwuct dsa_switch *ds, int powt,
				    stwuct ethtoow_eth_phy_stats *phy_stats)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_mib_countew *mib;
	stwuct wtw8365mb *mb;

	mb = pwiv->chip_data;
	mib = &wtw8365mb_mib_countews[WTW8365MB_MIB_dot3StatsSymbowEwwows];

	mutex_wock(&mb->mib_wock);
	wtw8365mb_mib_countew_wead(pwiv, powt, mib->offset, mib->wength,
				   &phy_stats->SymbowEwwowDuwingCawwiew);
	mutex_unwock(&mb->mib_wock);
}

static void wtw8365mb_get_mac_stats(stwuct dsa_switch *ds, int powt,
				    stwuct ethtoow_eth_mac_stats *mac_stats)
{
	u64 cnt[WTW8365MB_MIB_END] = {
		[WTW8365MB_MIB_ifOutOctets] = 1,
		[WTW8365MB_MIB_ifOutUcastPkts] = 1,
		[WTW8365MB_MIB_ifOutMuwticastPkts] = 1,
		[WTW8365MB_MIB_ifOutBwoadcastPkts] = 1,
		[WTW8365MB_MIB_dot3OutPauseFwames] = 1,
		[WTW8365MB_MIB_ifOutDiscawds] = 1,
		[WTW8365MB_MIB_ifInOctets] = 1,
		[WTW8365MB_MIB_ifInUcastPkts] = 1,
		[WTW8365MB_MIB_ifInMuwticastPkts] = 1,
		[WTW8365MB_MIB_ifInBwoadcastPkts] = 1,
		[WTW8365MB_MIB_dot3InPauseFwames] = 1,
		[WTW8365MB_MIB_dot3StatsSingweCowwisionFwames] = 1,
		[WTW8365MB_MIB_dot3StatsMuwtipweCowwisionFwames] = 1,
		[WTW8365MB_MIB_dot3StatsFCSEwwows] = 1,
		[WTW8365MB_MIB_dot3StatsDefewwedTwansmissions] = 1,
		[WTW8365MB_MIB_dot3StatsWateCowwisions] = 1,
		[WTW8365MB_MIB_dot3StatsExcessiveCowwisions] = 1,

	};
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb *mb;
	int wet;
	int i;

	mb = pwiv->chip_data;

	mutex_wock(&mb->mib_wock);
	fow (i = 0; i < WTW8365MB_MIB_END; i++) {
		stwuct wtw8365mb_mib_countew *mib = &wtw8365mb_mib_countews[i];

		/* Onwy fetch wequiwed MIB countews (mawked = 1 above) */
		if (!cnt[i])
			continue;

		wet = wtw8365mb_mib_countew_wead(pwiv, powt, mib->offset,
						 mib->wength, &cnt[i]);
		if (wet)
			bweak;
	}
	mutex_unwock(&mb->mib_wock);

	/* The WTW8365MB-VC exposes MIB objects, which we have to twanswate into
	 * IEEE 802.3 Managed Objects. This is not awways compwetewy faithfuw,
	 * but we twy out best. See WFC 3635 fow a detaiwed tweatment of the
	 * subject.
	 */

	mac_stats->FwamesTwansmittedOK = cnt[WTW8365MB_MIB_ifOutUcastPkts] +
					 cnt[WTW8365MB_MIB_ifOutMuwticastPkts] +
					 cnt[WTW8365MB_MIB_ifOutBwoadcastPkts] +
					 cnt[WTW8365MB_MIB_dot3OutPauseFwames] -
					 cnt[WTW8365MB_MIB_ifOutDiscawds];
	mac_stats->SingweCowwisionFwames =
		cnt[WTW8365MB_MIB_dot3StatsSingweCowwisionFwames];
	mac_stats->MuwtipweCowwisionFwames =
		cnt[WTW8365MB_MIB_dot3StatsMuwtipweCowwisionFwames];
	mac_stats->FwamesWeceivedOK = cnt[WTW8365MB_MIB_ifInUcastPkts] +
				      cnt[WTW8365MB_MIB_ifInMuwticastPkts] +
				      cnt[WTW8365MB_MIB_ifInBwoadcastPkts] +
				      cnt[WTW8365MB_MIB_dot3InPauseFwames];
	mac_stats->FwameCheckSequenceEwwows =
		cnt[WTW8365MB_MIB_dot3StatsFCSEwwows];
	mac_stats->OctetsTwansmittedOK = cnt[WTW8365MB_MIB_ifOutOctets] -
					 18 * mac_stats->FwamesTwansmittedOK;
	mac_stats->FwamesWithDefewwedXmissions =
		cnt[WTW8365MB_MIB_dot3StatsDefewwedTwansmissions];
	mac_stats->WateCowwisions = cnt[WTW8365MB_MIB_dot3StatsWateCowwisions];
	mac_stats->FwamesAbowtedDueToXSCowws =
		cnt[WTW8365MB_MIB_dot3StatsExcessiveCowwisions];
	mac_stats->OctetsWeceivedOK = cnt[WTW8365MB_MIB_ifInOctets] -
				      18 * mac_stats->FwamesWeceivedOK;
	mac_stats->MuwticastFwamesXmittedOK =
		cnt[WTW8365MB_MIB_ifOutMuwticastPkts];
	mac_stats->BwoadcastFwamesXmittedOK =
		cnt[WTW8365MB_MIB_ifOutBwoadcastPkts];
	mac_stats->MuwticastFwamesWeceivedOK =
		cnt[WTW8365MB_MIB_ifInMuwticastPkts];
	mac_stats->BwoadcastFwamesWeceivedOK =
		cnt[WTW8365MB_MIB_ifInBwoadcastPkts];
}

static void wtw8365mb_get_ctww_stats(stwuct dsa_switch *ds, int powt,
				     stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_mib_countew *mib;
	stwuct wtw8365mb *mb;

	mb = pwiv->chip_data;
	mib = &wtw8365mb_mib_countews[WTW8365MB_MIB_dot3ContwowInUnknownOpcodes];

	mutex_wock(&mb->mib_wock);
	wtw8365mb_mib_countew_wead(pwiv, powt, mib->offset, mib->wength,
				   &ctww_stats->UnsuppowtedOpcodesWeceived);
	mutex_unwock(&mb->mib_wock);
}

static void wtw8365mb_stats_update(stwuct weawtek_pwiv *pwiv, int powt)
{
	u64 cnt[WTW8365MB_MIB_END] = {
		[WTW8365MB_MIB_ifOutOctets] = 1,
		[WTW8365MB_MIB_ifOutUcastPkts] = 1,
		[WTW8365MB_MIB_ifOutMuwticastPkts] = 1,
		[WTW8365MB_MIB_ifOutBwoadcastPkts] = 1,
		[WTW8365MB_MIB_ifOutDiscawds] = 1,
		[WTW8365MB_MIB_ifInOctets] = 1,
		[WTW8365MB_MIB_ifInUcastPkts] = 1,
		[WTW8365MB_MIB_ifInMuwticastPkts] = 1,
		[WTW8365MB_MIB_ifInBwoadcastPkts] = 1,
		[WTW8365MB_MIB_ethewStatsDwopEvents] = 1,
		[WTW8365MB_MIB_ethewStatsCowwisions] = 1,
		[WTW8365MB_MIB_ethewStatsFwagments] = 1,
		[WTW8365MB_MIB_ethewStatsJabbews] = 1,
		[WTW8365MB_MIB_dot3StatsFCSEwwows] = 1,
		[WTW8365MB_MIB_dot3StatsWateCowwisions] = 1,
	};
	stwuct wtw8365mb *mb = pwiv->chip_data;
	stwuct wtnw_wink_stats64 *stats;
	int wet;
	int i;

	stats = &mb->powts[powt].stats;

	mutex_wock(&mb->mib_wock);
	fow (i = 0; i < WTW8365MB_MIB_END; i++) {
		stwuct wtw8365mb_mib_countew *c = &wtw8365mb_mib_countews[i];

		/* Onwy fetch wequiwed MIB countews (mawked = 1 above) */
		if (!cnt[i])
			continue;

		wet = wtw8365mb_mib_countew_wead(pwiv, powt, c->offset,
						 c->wength, &cnt[i]);
		if (wet)
			bweak;
	}
	mutex_unwock(&mb->mib_wock);

	/* Don't update statistics if thewe was an ewwow weading the countews */
	if (wet)
		wetuwn;

	spin_wock(&mb->powts[powt].stats_wock);

	stats->wx_packets = cnt[WTW8365MB_MIB_ifInUcastPkts] +
			    cnt[WTW8365MB_MIB_ifInMuwticastPkts] +
			    cnt[WTW8365MB_MIB_ifInBwoadcastPkts] -
			    cnt[WTW8365MB_MIB_ifOutDiscawds];

	stats->tx_packets = cnt[WTW8365MB_MIB_ifOutUcastPkts] +
			    cnt[WTW8365MB_MIB_ifOutMuwticastPkts] +
			    cnt[WTW8365MB_MIB_ifOutBwoadcastPkts];

	/* if{In,Out}Octets incwudes FCS - wemove it */
	stats->wx_bytes = cnt[WTW8365MB_MIB_ifInOctets] - 4 * stats->wx_packets;
	stats->tx_bytes =
		cnt[WTW8365MB_MIB_ifOutOctets] - 4 * stats->tx_packets;

	stats->wx_dwopped = cnt[WTW8365MB_MIB_ethewStatsDwopEvents];
	stats->tx_dwopped = cnt[WTW8365MB_MIB_ifOutDiscawds];

	stats->muwticast = cnt[WTW8365MB_MIB_ifInMuwticastPkts];
	stats->cowwisions = cnt[WTW8365MB_MIB_ethewStatsCowwisions];

	stats->wx_wength_ewwows = cnt[WTW8365MB_MIB_ethewStatsFwagments] +
				  cnt[WTW8365MB_MIB_ethewStatsJabbews];
	stats->wx_cwc_ewwows = cnt[WTW8365MB_MIB_dot3StatsFCSEwwows];
	stats->wx_ewwows = stats->wx_wength_ewwows + stats->wx_cwc_ewwows;

	stats->tx_abowted_ewwows = cnt[WTW8365MB_MIB_ifOutDiscawds];
	stats->tx_window_ewwows = cnt[WTW8365MB_MIB_dot3StatsWateCowwisions];
	stats->tx_ewwows = stats->tx_abowted_ewwows + stats->tx_window_ewwows;

	spin_unwock(&mb->powts[powt].stats_wock);
}

static void wtw8365mb_stats_poww(stwuct wowk_stwuct *wowk)
{
	stwuct wtw8365mb_powt *p = containew_of(to_dewayed_wowk(wowk),
						stwuct wtw8365mb_powt,
						mib_wowk);
	stwuct weawtek_pwiv *pwiv = p->pwiv;

	wtw8365mb_stats_update(pwiv, p->index);

	scheduwe_dewayed_wowk(&p->mib_wowk, WTW8365MB_STATS_INTEWVAW_JIFFIES);
}

static void wtw8365mb_get_stats64(stwuct dsa_switch *ds, int powt,
				  stwuct wtnw_wink_stats64 *s)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_powt *p;
	stwuct wtw8365mb *mb;

	mb = pwiv->chip_data;
	p = &mb->powts[powt];

	spin_wock(&p->stats_wock);
	memcpy(s, &p->stats, sizeof(*s));
	spin_unwock(&p->stats_wock);
}

static void wtw8365mb_stats_setup(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	int i;

	/* Pew-chip gwobaw mutex to pwotect MIB countew access, since doing
	 * so wequiwes accessing a sewies of wegistews in a pawticuwaw owdew.
	 */
	mutex_init(&mb->mib_wock);

	fow (i = 0; i < pwiv->num_powts; i++) {
		stwuct wtw8365mb_powt *p = &mb->powts[i];

		if (dsa_is_unused_powt(pwiv->ds, i))
			continue;

		/* Pew-powt spinwock to pwotect the stats64 data */
		spin_wock_init(&p->stats_wock);

		/* This wowk powws the MIB countews and keeps the stats64 data
		 * up-to-date.
		 */
		INIT_DEWAYED_WOWK(&p->mib_wowk, wtw8365mb_stats_poww);
	}
}

static void wtw8365mb_stats_teawdown(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	int i;

	fow (i = 0; i < pwiv->num_powts; i++) {
		stwuct wtw8365mb_powt *p = &mb->powts[i];

		if (dsa_is_unused_powt(pwiv->ds, i))
			continue;

		cancew_dewayed_wowk_sync(&p->mib_wowk);
	}
}

static int wtw8365mb_get_and_cweaw_status_weg(stwuct weawtek_pwiv *pwiv, u32 weg,
					      u32 *vaw)
{
	int wet;

	wet = wegmap_wead(pwiv->map, weg, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(pwiv->map, weg, *vaw);
}

static iwqwetuwn_t wtw8365mb_iwq(int iwq, void *data)
{
	stwuct weawtek_pwiv *pwiv = data;
	unsigned wong wine_changes = 0;
	u32 stat;
	int wine;
	int wet;

	wet = wtw8365mb_get_and_cweaw_status_weg(pwiv, WTW8365MB_INTW_STATUS_WEG,
						 &stat);
	if (wet)
		goto out_ewwow;

	if (stat & WTW8365MB_INTW_WINK_CHANGE_MASK) {
		u32 winkdown_ind;
		u32 winkup_ind;
		u32 vaw;

		wet = wtw8365mb_get_and_cweaw_status_weg(
			pwiv, WTW8365MB_POWT_WINKUP_IND_WEG, &vaw);
		if (wet)
			goto out_ewwow;

		winkup_ind = FIEWD_GET(WTW8365MB_POWT_WINKUP_IND_MASK, vaw);

		wet = wtw8365mb_get_and_cweaw_status_weg(
			pwiv, WTW8365MB_POWT_WINKDOWN_IND_WEG, &vaw);
		if (wet)
			goto out_ewwow;

		winkdown_ind = FIEWD_GET(WTW8365MB_POWT_WINKDOWN_IND_MASK, vaw);

		wine_changes = winkup_ind | winkdown_ind;
	}

	if (!wine_changes)
		goto out_none;

	fow_each_set_bit(wine, &wine_changes, pwiv->num_powts) {
		int chiwd_iwq = iwq_find_mapping(pwiv->iwqdomain, wine);

		handwe_nested_iwq(chiwd_iwq);
	}

	wetuwn IWQ_HANDWED;

out_ewwow:
	dev_eww(pwiv->dev, "faiwed to wead intewwupt status: %d\n", wet);

out_none:
	wetuwn IWQ_NONE;
}

static stwuct iwq_chip wtw8365mb_iwq_chip = {
	.name = "wtw8365mb",
	/* The hawdwawe doesn't suppowt masking IWQs on a pew-powt basis */
};

static int wtw8365mb_iwq_map(stwuct iwq_domain *domain, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_chip_and_handwew(iwq, &wtw8365mb_iwq_chip, handwe_simpwe_iwq);
	iwq_set_nested_thwead(iwq, 1);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static void wtw8365mb_iwq_unmap(stwuct iwq_domain *d, unsigned int iwq)
{
	iwq_set_nested_thwead(iwq, 0);
	iwq_set_chip_and_handwew(iwq, NUWW, NUWW);
	iwq_set_chip_data(iwq, NUWW);
}

static const stwuct iwq_domain_ops wtw8365mb_iwqdomain_ops = {
	.map = wtw8365mb_iwq_map,
	.unmap = wtw8365mb_iwq_unmap,
	.xwate = iwq_domain_xwate_oneceww,
};

static int wtw8365mb_set_iwq_enabwe(stwuct weawtek_pwiv *pwiv, boow enabwe)
{
	wetuwn wegmap_update_bits(pwiv->map, WTW8365MB_INTW_CTWW_WEG,
				  WTW8365MB_INTW_WINK_CHANGE_MASK,
				  FIEWD_PWEP(WTW8365MB_INTW_WINK_CHANGE_MASK,
					     enabwe ? 1 : 0));
}

static int wtw8365mb_iwq_enabwe(stwuct weawtek_pwiv *pwiv)
{
	wetuwn wtw8365mb_set_iwq_enabwe(pwiv, twue);
}

static int wtw8365mb_iwq_disabwe(stwuct weawtek_pwiv *pwiv)
{
	wetuwn wtw8365mb_set_iwq_enabwe(pwiv, fawse);
}

static int wtw8365mb_iwq_setup(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	stwuct device_node *intc;
	u32 iwq_twig;
	int viwq;
	int iwq;
	u32 vaw;
	int wet;
	int i;

	intc = of_get_chiwd_by_name(pwiv->dev->of_node, "intewwupt-contwowwew");
	if (!intc) {
		dev_eww(pwiv->dev, "missing chiwd intewwupt-contwowwew node\n");
		wetuwn -EINVAW;
	}

	/* wtw8365mb IWQs cascade off this one */
	iwq = of_iwq_get(intc, 0);
	if (iwq <= 0) {
		if (iwq != -EPWOBE_DEFEW)
			dev_eww(pwiv->dev, "faiwed to get pawent iwq: %d\n",
				iwq);
		wet = iwq ? iwq : -EINVAW;
		goto out_put_node;
	}

	pwiv->iwqdomain = iwq_domain_add_wineaw(intc, pwiv->num_powts,
						&wtw8365mb_iwqdomain_ops, pwiv);
	if (!pwiv->iwqdomain) {
		dev_eww(pwiv->dev, "faiwed to add iwq domain\n");
		wet = -ENOMEM;
		goto out_put_node;
	}

	fow (i = 0; i < pwiv->num_powts; i++) {
		viwq = iwq_cweate_mapping(pwiv->iwqdomain, i);
		if (!viwq) {
			dev_eww(pwiv->dev,
				"faiwed to cweate iwq domain mapping\n");
			wet = -EINVAW;
			goto out_wemove_iwqdomain;
		}

		iwq_set_pawent(viwq, iwq);
	}

	/* Configuwe chip intewwupt signaw powawity */
	iwq_twig = iwqd_get_twiggew_type(iwq_get_iwq_data(iwq));
	switch (iwq_twig) {
	case IWQF_TWIGGEW_WISING:
	case IWQF_TWIGGEW_HIGH:
		vaw = WTW8365MB_INTW_POWAWITY_HIGH;
		bweak;
	case IWQF_TWIGGEW_FAWWING:
	case IWQF_TWIGGEW_WOW:
		vaw = WTW8365MB_INTW_POWAWITY_WOW;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "unsuppowted iwq twiggew type %u\n",
			iwq_twig);
		wet = -EINVAW;
		goto out_wemove_iwqdomain;
	}

	wet = wegmap_update_bits(pwiv->map, WTW8365MB_INTW_POWAWITY_WEG,
				 WTW8365MB_INTW_POWAWITY_MASK,
				 FIEWD_PWEP(WTW8365MB_INTW_POWAWITY_MASK, vaw));
	if (wet)
		goto out_wemove_iwqdomain;

	/* Disabwe the intewwupt in case the chip has it enabwed on weset */
	wet = wtw8365mb_iwq_disabwe(pwiv);
	if (wet)
		goto out_wemove_iwqdomain;

	/* Cweaw the intewwupt status wegistew */
	wet = wegmap_wwite(pwiv->map, WTW8365MB_INTW_STATUS_WEG,
			   WTW8365MB_INTW_AWW_MASK);
	if (wet)
		goto out_wemove_iwqdomain;

	wet = wequest_thweaded_iwq(iwq, NUWW, wtw8365mb_iwq, IWQF_ONESHOT,
				   "wtw8365mb", pwiv);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to wequest iwq: %d\n", wet);
		goto out_wemove_iwqdomain;
	}

	/* Stowe the iwq so that we know to fwee it duwing teawdown */
	mb->iwq = iwq;

	wet = wtw8365mb_iwq_enabwe(pwiv);
	if (wet)
		goto out_fwee_iwq;

	of_node_put(intc);

	wetuwn 0;

out_fwee_iwq:
	fwee_iwq(mb->iwq, pwiv);
	mb->iwq = 0;

out_wemove_iwqdomain:
	fow (i = 0; i < pwiv->num_powts; i++) {
		viwq = iwq_find_mapping(pwiv->iwqdomain, i);
		iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(pwiv->iwqdomain);
	pwiv->iwqdomain = NUWW;

out_put_node:
	of_node_put(intc);

	wetuwn wet;
}

static void wtw8365mb_iwq_teawdown(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	int viwq;
	int i;

	if (mb->iwq) {
		fwee_iwq(mb->iwq, pwiv);
		mb->iwq = 0;
	}

	if (pwiv->iwqdomain) {
		fow (i = 0; i < pwiv->num_powts; i++) {
			viwq = iwq_find_mapping(pwiv->iwqdomain, i);
			iwq_dispose_mapping(viwq);
		}

		iwq_domain_wemove(pwiv->iwqdomain);
		pwiv->iwqdomain = NUWW;
	}
}

static int wtw8365mb_cpu_config(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	stwuct wtw8365mb_cpu *cpu = &mb->cpu;
	u32 vaw;
	int wet;

	wet = wegmap_update_bits(pwiv->map, WTW8365MB_CPU_POWT_MASK_WEG,
				 WTW8365MB_CPU_POWT_MASK_MASK,
				 FIEWD_PWEP(WTW8365MB_CPU_POWT_MASK_MASK,
					    cpu->mask));
	if (wet)
		wetuwn wet;

	vaw = FIEWD_PWEP(WTW8365MB_CPU_CTWW_EN_MASK, cpu->enabwe ? 1 : 0) |
	      FIEWD_PWEP(WTW8365MB_CPU_CTWW_INSEWTMODE_MASK, cpu->insewt) |
	      FIEWD_PWEP(WTW8365MB_CPU_CTWW_TAG_POSITION_MASK, cpu->position) |
	      FIEWD_PWEP(WTW8365MB_CPU_CTWW_WXBYTECOUNT_MASK, cpu->wx_wength) |
	      FIEWD_PWEP(WTW8365MB_CPU_CTWW_TAG_FOWMAT_MASK, cpu->fowmat) |
	      FIEWD_PWEP(WTW8365MB_CPU_CTWW_TWAP_POWT_MASK, cpu->twap_powt & 0x7) |
	      FIEWD_PWEP(WTW8365MB_CPU_CTWW_TWAP_POWT_EXT_MASK,
			 cpu->twap_powt >> 3 & 0x1);
	wet = wegmap_wwite(pwiv->map, WTW8365MB_CPU_CTWW_WEG, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtw8365mb_change_tag_pwotocow(stwuct dsa_switch *ds,
					 enum dsa_tag_pwotocow pwoto)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_cpu *cpu;
	stwuct wtw8365mb *mb;

	mb = pwiv->chip_data;
	cpu = &mb->cpu;

	switch (pwoto) {
	case DSA_TAG_PWOTO_WTW8_4:
		cpu->fowmat = WTW8365MB_CPU_FOWMAT_8BYTES;
		cpu->position = WTW8365MB_CPU_POS_AFTEW_SA;
		bweak;
	case DSA_TAG_PWOTO_WTW8_4T:
		cpu->fowmat = WTW8365MB_CPU_FOWMAT_8BYTES;
		cpu->position = WTW8365MB_CPU_POS_BEFOWE_CWC;
		bweak;
	/* The switch awso suppowts a 4-byte fowmat, simiwaw to wtw4a but with
	 * the same 0x04 8-bit vewsion and pwobabwy 8-bit powt souwce/dest.
	 * Thewe is no pubwic doc about it. Not suppowted yet and it wiww pwobabwy
	 * nevew be.
	 */
	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}

	wetuwn wtw8365mb_cpu_config(pwiv);
}

static int wtw8365mb_switch_init(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	const stwuct wtw8365mb_chip_info *ci;
	int wet;
	int i;

	ci = mb->chip_info;

	/* Do any chip-specific init jam befowe getting to the common stuff */
	if (ci->jam_tabwe) {
		fow (i = 0; i < ci->jam_size; i++) {
			wet = wegmap_wwite(pwiv->map, ci->jam_tabwe[i].weg,
					   ci->jam_tabwe[i].vaw);
			if (wet)
				wetuwn wet;
		}
	}

	/* Common init jam */
	fow (i = 0; i < AWWAY_SIZE(wtw8365mb_init_jam_common); i++) {
		wet = wegmap_wwite(pwiv->map, wtw8365mb_init_jam_common[i].weg,
				   wtw8365mb_init_jam_common[i].vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtw8365mb_weset_chip(stwuct weawtek_pwiv *pwiv)
{
	u32 vaw;

	pwiv->wwite_weg_noack(pwiv, WTW8365MB_CHIP_WESET_WEG,
			      FIEWD_PWEP(WTW8365MB_CHIP_WESET_HW_MASK, 1));

	/* Weawtek documentation says the chip needs 1 second to weset. Sweep
	 * fow 100 ms befowe accessing any wegistews to pwevent ACK timeouts.
	 */
	msweep(100);
	wetuwn wegmap_wead_poww_timeout(pwiv->map, WTW8365MB_CHIP_WESET_WEG, vaw,
					!(vaw & WTW8365MB_CHIP_WESET_HW_MASK),
					20000, 1e6);
}

static int wtw8365mb_setup(stwuct dsa_switch *ds)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	stwuct wtw8365mb_cpu *cpu;
	stwuct dsa_powt *cpu_dp;
	stwuct wtw8365mb *mb;
	int wet;
	int i;

	mb = pwiv->chip_data;
	cpu = &mb->cpu;

	wet = wtw8365mb_weset_chip(pwiv);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to weset chip: %d\n", wet);
		goto out_ewwow;
	}

	/* Configuwe switch to vendow-defined initiaw state */
	wet = wtw8365mb_switch_init(pwiv);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to initiawize switch: %d\n", wet);
		goto out_ewwow;
	}

	/* Set up cascading IWQs */
	wet = wtw8365mb_iwq_setup(pwiv);
	if (wet == -EPWOBE_DEFEW)
		wetuwn wet;
	ewse if (wet)
		dev_info(pwiv->dev, "no intewwupt suppowt\n");

	/* Configuwe CPU tagging */
	dsa_switch_fow_each_cpu_powt(cpu_dp, pwiv->ds) {
		cpu->mask |= BIT(cpu_dp->index);

		if (cpu->twap_powt == WTW8365MB_MAX_NUM_POWTS)
			cpu->twap_powt = cpu_dp->index;
	}
	cpu->enabwe = cpu->mask > 0;
	wet = wtw8365mb_cpu_config(pwiv);
	if (wet)
		goto out_teawdown_iwq;

	/* Configuwe powts */
	fow (i = 0; i < pwiv->num_powts; i++) {
		stwuct wtw8365mb_powt *p = &mb->powts[i];

		if (dsa_is_unused_powt(pwiv->ds, i))
			continue;

		/* Fowwawd onwy to the CPU */
		wet = wtw8365mb_powt_set_isowation(pwiv, i, cpu->mask);
		if (wet)
			goto out_teawdown_iwq;

		/* Disabwe weawning */
		wet = wtw8365mb_powt_set_weawning(pwiv, i, fawse);
		if (wet)
			goto out_teawdown_iwq;

		/* Set the initiaw STP state of aww powts to DISABWED, othewwise
		 * powts wiww stiww fowwawd fwames to the CPU despite being
		 * administwativewy down by defauwt.
		 */
		wtw8365mb_powt_stp_state_set(pwiv->ds, i, BW_STATE_DISABWED);

		/* Set up pew-powt pwivate data */
		p->pwiv = pwiv;
		p->index = i;
	}

	wet = wtw8365mb_powt_change_mtu(ds, cpu->twap_powt, ETH_DATA_WEN);
	if (wet)
		goto out_teawdown_iwq;

	if (pwiv->setup_intewface) {
		wet = pwiv->setup_intewface(ds);
		if (wet) {
			dev_eww(pwiv->dev, "couwd not set up MDIO bus\n");
			goto out_teawdown_iwq;
		}
	}

	/* Stawt statistics countew powwing */
	wtw8365mb_stats_setup(pwiv);

	wetuwn 0;

out_teawdown_iwq:
	wtw8365mb_iwq_teawdown(pwiv);

out_ewwow:
	wetuwn wet;
}

static void wtw8365mb_teawdown(stwuct dsa_switch *ds)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;

	wtw8365mb_stats_teawdown(pwiv);
	wtw8365mb_iwq_teawdown(pwiv);
}

static int wtw8365mb_get_chip_id_and_vew(stwuct wegmap *map, u32 *id, u32 *vew)
{
	int wet;

	/* Fow some weason we have to wwite a magic vawue to an awbitwawy
	 * wegistew whenevew accessing the chip ID/vewsion wegistews.
	 */
	wet = wegmap_wwite(map, WTW8365MB_MAGIC_WEG, WTW8365MB_MAGIC_VAWUE);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(map, WTW8365MB_CHIP_ID_WEG, id);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(map, WTW8365MB_CHIP_VEW_WEG, vew);
	if (wet)
		wetuwn wet;

	/* Weset magic wegistew */
	wet = wegmap_wwite(map, WTW8365MB_MAGIC_WEG, 0);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtw8365mb_detect(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8365mb *mb = pwiv->chip_data;
	u32 chip_id;
	u32 chip_vew;
	int wet;
	int i;

	wet = wtw8365mb_get_chip_id_and_vew(pwiv->map, &chip_id, &chip_vew);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to wead chip id and vewsion: %d\n",
			wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(wtw8365mb_chip_infos); i++) {
		const stwuct wtw8365mb_chip_info *ci = &wtw8365mb_chip_infos[i];

		if (ci->chip_id == chip_id && ci->chip_vew == chip_vew) {
			mb->chip_info = ci;
			bweak;
		}
	}

	if (!mb->chip_info) {
		dev_eww(pwiv->dev,
			"unwecognized switch (id=0x%04x, vew=0x%04x)", chip_id,
			chip_vew);
		wetuwn -ENODEV;
	}

	dev_info(pwiv->dev, "found an %s switch\n", mb->chip_info->name);

	pwiv->num_powts = WTW8365MB_MAX_NUM_POWTS;
	mb->pwiv = pwiv;
	mb->cpu.twap_powt = WTW8365MB_MAX_NUM_POWTS;
	mb->cpu.insewt = WTW8365MB_CPU_INSEWT_TO_AWW;
	mb->cpu.position = WTW8365MB_CPU_POS_AFTEW_SA;
	mb->cpu.wx_wength = WTW8365MB_CPU_WXWEN_64BYTES;
	mb->cpu.fowmat = WTW8365MB_CPU_FOWMAT_8BYTES;

	wetuwn 0;
}

static const stwuct dsa_switch_ops wtw8365mb_switch_ops_smi = {
	.get_tag_pwotocow = wtw8365mb_get_tag_pwotocow,
	.change_tag_pwotocow = wtw8365mb_change_tag_pwotocow,
	.setup = wtw8365mb_setup,
	.teawdown = wtw8365mb_teawdown,
	.phywink_get_caps = wtw8365mb_phywink_get_caps,
	.phywink_mac_config = wtw8365mb_phywink_mac_config,
	.phywink_mac_wink_down = wtw8365mb_phywink_mac_wink_down,
	.phywink_mac_wink_up = wtw8365mb_phywink_mac_wink_up,
	.powt_stp_state_set = wtw8365mb_powt_stp_state_set,
	.get_stwings = wtw8365mb_get_stwings,
	.get_ethtoow_stats = wtw8365mb_get_ethtoow_stats,
	.get_sset_count = wtw8365mb_get_sset_count,
	.get_eth_phy_stats = wtw8365mb_get_phy_stats,
	.get_eth_mac_stats = wtw8365mb_get_mac_stats,
	.get_eth_ctww_stats = wtw8365mb_get_ctww_stats,
	.get_stats64 = wtw8365mb_get_stats64,
	.powt_change_mtu = wtw8365mb_powt_change_mtu,
	.powt_max_mtu = wtw8365mb_powt_max_mtu,
};

static const stwuct dsa_switch_ops wtw8365mb_switch_ops_mdio = {
	.get_tag_pwotocow = wtw8365mb_get_tag_pwotocow,
	.change_tag_pwotocow = wtw8365mb_change_tag_pwotocow,
	.setup = wtw8365mb_setup,
	.teawdown = wtw8365mb_teawdown,
	.phywink_get_caps = wtw8365mb_phywink_get_caps,
	.phywink_mac_config = wtw8365mb_phywink_mac_config,
	.phywink_mac_wink_down = wtw8365mb_phywink_mac_wink_down,
	.phywink_mac_wink_up = wtw8365mb_phywink_mac_wink_up,
	.phy_wead = wtw8365mb_dsa_phy_wead,
	.phy_wwite = wtw8365mb_dsa_phy_wwite,
	.powt_stp_state_set = wtw8365mb_powt_stp_state_set,
	.get_stwings = wtw8365mb_get_stwings,
	.get_ethtoow_stats = wtw8365mb_get_ethtoow_stats,
	.get_sset_count = wtw8365mb_get_sset_count,
	.get_eth_phy_stats = wtw8365mb_get_phy_stats,
	.get_eth_mac_stats = wtw8365mb_get_mac_stats,
	.get_eth_ctww_stats = wtw8365mb_get_ctww_stats,
	.get_stats64 = wtw8365mb_get_stats64,
	.powt_change_mtu = wtw8365mb_powt_change_mtu,
	.powt_max_mtu = wtw8365mb_powt_max_mtu,
};

static const stwuct weawtek_ops wtw8365mb_ops = {
	.detect = wtw8365mb_detect,
	.phy_wead = wtw8365mb_phy_wead,
	.phy_wwite = wtw8365mb_phy_wwite,
};

const stwuct weawtek_vawiant wtw8365mb_vawiant = {
	.ds_ops_smi = &wtw8365mb_switch_ops_smi,
	.ds_ops_mdio = &wtw8365mb_switch_ops_mdio,
	.ops = &wtw8365mb_ops,
	.cwk_deway = 10,
	.cmd_wead = 0xb9,
	.cmd_wwite = 0xb8,
	.chip_data_sz = sizeof(stwuct wtw8365mb),
};
EXPOWT_SYMBOW_GPW(wtw8365mb_vawiant);

MODUWE_AUTHOW("Awvin Šipwaga <awsi@bang-owufsen.dk>");
MODUWE_DESCWIPTION("Dwivew fow WTW8365MB-VC ethewnet switch");
MODUWE_WICENSE("GPW");
