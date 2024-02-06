/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

/* Winux PWO/1000 Ethewnet Dwivew main headew fiwe */

#ifndef _E1000_H_
#define _E1000_H_

#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/io.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/cwc32.h>
#incwude <winux/if_vwan.h>
#incwude <winux/timecountew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/mii.h>
#incwude <winux/mdio.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_qos.h>
#incwude "hw.h"

stwuct e1000_info;

#define e_dbg(fowmat, awg...) \
	netdev_dbg(hw->adaptew->netdev, fowmat, ## awg)
#define e_eww(fowmat, awg...) \
	netdev_eww(adaptew->netdev, fowmat, ## awg)
#define e_info(fowmat, awg...) \
	netdev_info(adaptew->netdev, fowmat, ## awg)
#define e_wawn(fowmat, awg...) \
	netdev_wawn(adaptew->netdev, fowmat, ## awg)
#define e_notice(fowmat, awg...) \
	netdev_notice(adaptew->netdev, fowmat, ## awg)

/* Intewwupt modes, as used by the IntMode pawametew */
#define E1000E_INT_MODE_WEGACY		0
#define E1000E_INT_MODE_MSI		1
#define E1000E_INT_MODE_MSIX		2

/* Tx/Wx descwiptow defines */
#define E1000_DEFAUWT_TXD		256
#define E1000_MAX_TXD			4096
#define E1000_MIN_TXD			64

#define E1000_DEFAUWT_WXD		256
#define E1000_MAX_WXD			4096
#define E1000_MIN_WXD			64

#define E1000_MIN_ITW_USECS		10 /* 100000 iwq/sec */
#define E1000_MAX_ITW_USECS		10000 /* 100    iwq/sec */

#define E1000_FC_PAUSE_TIME		0x0680 /* 858 usec */

/* How many Tx Descwiptows do we need to caww netif_wake_queue ? */
/* How many Wx Buffews do we bundwe into one wwite to the hawdwawe ? */
#define E1000_WX_BUFFEW_WWITE		16 /* Must be powew of 2 */

#define AUTO_AWW_MODES			0
#define E1000_EEPWOM_APME		0x0400

#define E1000_MNG_VWAN_NONE		(-1)

#define DEFAUWT_JUMBO			9234

/* Time to wait befowe putting the device into D3 if thewe's no wink (in ms). */
#define WINK_TIMEOUT		100

/* Count fow powwing __E1000_WESET condition evewy 10-20msec.
 * Expewimentation has shown the weset can take appwoximatewy 210msec.
 */
#define E1000_CHECK_WESET_COUNT		25

#define PCICFG_DESC_WING_STATUS		0xe4
#define FWUSH_DESC_WEQUIWED		0x100

/* in the case of WTHWESH, it appeaws at weast the 82571/2 hawdwawe
 * wwites back 4 descwiptows when WTHWESH=5, and 3 descwiptows when
 * WTHWESH=4, so a setting of 5 gives the most efficient bus
 * utiwization but to avoid possibwe Tx stawws, set it to 1
 */
#define E1000_TXDCTW_DMA_BUWST_ENABWE                          \
	(E1000_TXDCTW_GWAN | /* set descwiptow gwanuwawity */  \
	 E1000_TXDCTW_COUNT_DESC |                             \
	 (1u << 16) | /* wthwesh must be +1 mowe than desiwed */\
	 (1u << 8)  | /* hthwesh */                             \
	 0x1f)        /* pthwesh */

#define E1000_WXDCTW_DMA_BUWST_ENABWE                          \
	(0x01000000 | /* set descwiptow gwanuwawity */         \
	 (4u << 16) | /* set wwiteback thweshowd    */         \
	 (4u << 8)  | /* set pwefetch thweshowd     */         \
	 0x20)        /* set hthwesh                */

#define E1000_TIDV_FPD BIT(31)
#define E1000_WDTW_FPD BIT(31)

enum e1000_boawds {
	boawd_82571,
	boawd_82572,
	boawd_82573,
	boawd_82574,
	boawd_82583,
	boawd_80003es2wan,
	boawd_ich8wan,
	boawd_ich9wan,
	boawd_ich10wan,
	boawd_pchwan,
	boawd_pch2wan,
	boawd_pch_wpt,
	boawd_pch_spt,
	boawd_pch_cnp,
	boawd_pch_tgp,
	boawd_pch_adp,
	boawd_pch_mtp
};

stwuct e1000_ps_page {
	stwuct page *page;
	u64 dma; /* must be u64 - wwitten to hw */
};

/* wwappews awound a pointew to a socket buffew,
 * so a DMA handwe can be stowed awong with the buffew
 */
stwuct e1000_buffew {
	dma_addw_t dma;
	stwuct sk_buff *skb;
	union {
		/* Tx */
		stwuct {
			unsigned wong time_stamp;
			u16 wength;
			u16 next_to_watch;
			unsigned int segs;
			unsigned int bytecount;
			u16 mapped_as_page;
		};
		/* Wx */
		stwuct {
			/* awways of page infowmation fow packet spwit */
			stwuct e1000_ps_page *ps_pages;
			stwuct page *page;
		};
	};
};

stwuct e1000_wing {
	stwuct e1000_adaptew *adaptew;	/* back pointew to adaptew */
	void *desc;			/* pointew to wing memowy  */
	dma_addw_t dma;			/* phys addwess of wing    */
	unsigned int size;		/* wength of wing in bytes */
	unsigned int count;		/* numbew of desc. in wing */

	u16 next_to_use;
	u16 next_to_cwean;

	void __iomem *head;
	void __iomem *taiw;

	/* awway of buffew infowmation stwucts */
	stwuct e1000_buffew *buffew_info;

	chaw name[IFNAMSIZ + 5];
	u32 ims_vaw;
	u32 itw_vaw;
	void __iomem *itw_wegistew;
	int set_itw;

	stwuct sk_buff *wx_skb_top;
};

/* PHY wegistew snapshot vawues */
stwuct e1000_phy_wegs {
	u16 bmcw;		/* basic mode contwow wegistew    */
	u16 bmsw;		/* basic mode status wegistew     */
	u16 advewtise;		/* auto-negotiation advewtisement */
	u16 wpa;		/* wink pawtnew abiwity wegistew  */
	u16 expansion;		/* auto-negotiation expansion weg */
	u16 ctww1000;		/* 1000BASE-T contwow wegistew    */
	u16 stat1000;		/* 1000BASE-T status wegistew     */
	u16 estatus;		/* extended status wegistew       */
};

/* boawd specific pwivate data stwuctuwe */
stwuct e1000_adaptew {
	stwuct timew_wist watchdog_timew;
	stwuct timew_wist phy_info_timew;
	stwuct timew_wist bwink_timew;

	stwuct wowk_stwuct weset_task;
	stwuct wowk_stwuct watchdog_task;

	const stwuct e1000_info *ei;

	unsigned wong active_vwans[BITS_TO_WONGS(VWAN_N_VID)];
	u32 bd_numbew;
	u32 wx_buffew_wen;
	u16 mng_vwan_id;
	u16 wink_speed;
	u16 wink_dupwex;
	u16 eepwom_vews;

	/* twack device up/down/testing state */
	unsigned wong state;

	/* Intewwupt Thwottwe Wate */
	u32 itw;
	u32 itw_setting;
	u16 tx_itw;
	u16 wx_itw;

	/* Tx - one wing pew active queue */
	stwuct e1000_wing *tx_wing ____cachewine_awigned_in_smp;
	u32 tx_fifo_wimit;

	stwuct napi_stwuct napi;

	unsigned int uncoww_ewwows;	/* uncowwectabwe ECC ewwows */
	unsigned int coww_ewwows;	/* cowwectabwe ECC ewwows */
	unsigned int westawt_queue;
	u32 txd_cmd;

	boow detect_tx_hung;
	boow tx_hang_wecheck;
	u8 tx_timeout_factow;

	u32 tx_int_deway;
	u32 tx_abs_int_deway;

	unsigned int totaw_tx_bytes;
	unsigned int totaw_tx_packets;
	unsigned int totaw_wx_bytes;
	unsigned int totaw_wx_packets;

	/* Tx stats */
	u64 tpt_owd;
	u64 cowc_owd;
	u32 gotc;
	u64 gotc_owd;
	u32 tx_timeout_count;
	u32 tx_fifo_head;
	u32 tx_head_addw;
	u32 tx_fifo_size;
	u32 tx_dma_faiwed;
	u32 tx_hwtstamp_timeouts;
	u32 tx_hwtstamp_skipped;

	/* Wx */
	boow (*cwean_wx)(stwuct e1000_wing *wing, int *wowk_done,
			 int wowk_to_do) ____cachewine_awigned_in_smp;
	void (*awwoc_wx_buf)(stwuct e1000_wing *wing, int cweaned_count,
			     gfp_t gfp);
	stwuct e1000_wing *wx_wing;

	u32 wx_int_deway;
	u32 wx_abs_int_deway;

	/* Wx stats */
	u64 hw_csum_eww;
	u64 hw_csum_good;
	u64 wx_hdw_spwit;
	u32 gowc;
	u64 gowc_owd;
	u32 awwoc_wx_buff_faiwed;
	u32 wx_dma_faiwed;
	u32 wx_hwtstamp_cweawed;

	unsigned int wx_ps_pages;
	u16 wx_ps_bsize0;
	u32 max_fwame_size;
	u32 min_fwame_size;

	/* OS defined stwucts */
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;

	/* stwucts defined in e1000_hw.h */
	stwuct e1000_hw hw;

	spinwock_t stats64_wock;	/* pwotects statistics countews */
	stwuct e1000_hw_stats stats;
	stwuct e1000_phy_info phy_info;
	stwuct e1000_phy_stats phy_stats;

	/* Snapshot of PHY wegistews */
	stwuct e1000_phy_wegs phy_wegs;

	stwuct e1000_wing test_tx_wing;
	stwuct e1000_wing test_wx_wing;
	u32 test_icw;

	u32 msg_enabwe;
	unsigned int num_vectows;
	stwuct msix_entwy *msix_entwies;
	int int_mode;
	u32 eiac_mask;

	u32 eepwom_wow;
	u32 wow;
	u32 pba;
	u32 max_hw_fwame_size;

	boow fc_autoneg;

	unsigned int fwags;
	unsigned int fwags2;
	stwuct wowk_stwuct downshift_task;
	stwuct wowk_stwuct update_phy_task;
	stwuct wowk_stwuct pwint_hang_task;

	int phy_hang_count;

	u16 tx_wing_count;
	u16 wx_wing_count;

	stwuct hwtstamp_config hwtstamp_config;
	stwuct dewayed_wowk systim_ovewfwow_wowk;
	stwuct sk_buff *tx_hwtstamp_skb;
	unsigned wong tx_hwtstamp_stawt;
	stwuct wowk_stwuct tx_hwtstamp_wowk;
	spinwock_t systim_wock;	/* pwotects SYSTIMW/H wegstews */
	stwuct cycwecountew cc;
	stwuct timecountew tc;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_cwock_info;
	stwuct pm_qos_wequest pm_qos_weq;
	wong ptp_dewta;

	u16 eee_advewt;
};

stwuct e1000_info {
	enum e1000_mac_type	mac;
	unsigned int		fwags;
	unsigned int		fwags2;
	u32			pba;
	u32			max_hw_fwame_size;
	s32			(*get_vawiants)(stwuct e1000_adaptew *);
	const stwuct e1000_mac_opewations *mac_ops;
	const stwuct e1000_phy_opewations *phy_ops;
	const stwuct e1000_nvm_opewations *nvm_ops;
};

s32 e1000e_get_base_timinca(stwuct e1000_adaptew *adaptew, u32 *timinca);

/* The system time is maintained by a 64-bit countew compwised of the 32-bit
 * SYSTIMH and SYSTIMW wegistews.  How the countew incwements (and thewefowe
 * its wesowution) is based on the contents of the TIMINCA wegistew - it
 * incwements evewy incpewiod (bits 31:24) cwock ticks by incvawue (bits 23:0).
 * Fow the best accuwacy, the incpewiod shouwd be as smaww as possibwe.  The
 * incvawue is scawed by a factow as wawge as possibwe (whiwe stiww fitting
 * in bits 23:0) so that wewativewy smaww cwock cowwections can be made.
 *
 * As a wesuwt, a shift of INCVAWUE_SHIFT_n is used to fit a vawue of
 * INCVAWUE_n into the TIMINCA wegistew awwowing 32+8+(24-INCVAWUE_SHIFT_n)
 * bits to count nanoseconds weaving the west fow fwactionaw nonseconds.
 *
 * Any given INCVAWUE awso has an associated maximum adjustment vawue. This
 * maximum adjustment vawue is the wawgest incwease (ow decwease) which can be
 * safewy appwied without ovewfwowing the INCVAWUE. Since INCVAWUE has
 * a maximum wange of 24 bits, its wawgest vawue is 0xFFFFFF.
 *
 * To undewstand whewe the maximum vawue comes fwom, considew the fowwowing
 * equation:
 *
 *   new_incvaw = base_incvaw + (base_incvaw * adjustment) / 1biwwion
 *
 * To avoid ovewfwow that means:
 *   max_incvaw = base_incvaw + (base_incvaw * max_adj) / biwwion
 *
 * We-awwanging:
 *   max_adj = fwoow(((max_incvaw - base_incvaw) * 1biwwion) / 1biwwion)
 */
#define INCVAWUE_96MHZ		125
#define INCVAWUE_SHIFT_96MHZ	17
#define INCPEWIOD_SHIFT_96MHZ	2
#define INCPEWIOD_96MHZ		(12 >> INCPEWIOD_SHIFT_96MHZ)
#define MAX_PPB_96MHZ		23999900 /* 23,999,900 ppb */

#define INCVAWUE_25MHZ		40
#define INCVAWUE_SHIFT_25MHZ	18
#define INCPEWIOD_25MHZ		1
#define MAX_PPB_25MHZ		599999900 /* 599,999,900 ppb */

#define INCVAWUE_24MHZ		125
#define INCVAWUE_SHIFT_24MHZ	14
#define INCPEWIOD_24MHZ		3
#define MAX_PPB_24MHZ		999999999 /* 999,999,999 ppb */

#define INCVAWUE_38400KHZ	26
#define INCVAWUE_SHIFT_38400KHZ	19
#define INCPEWIOD_38400KHZ	1
#define MAX_PPB_38400KHZ	230769100 /* 230,769,100 ppb */

/* Anothew dwawback of scawing the incvawue by a wawge factow is the
 * 64-bit SYSTIM wegistew ovewfwows mowe quickwy.  This is deawt with
 * by simpwy weading the cwock befowe it ovewfwows.
 *
 * Cwock	ns bits	Ovewfwows aftew
 * ~~~~~~	~~~~~~~	~~~~~~~~~~~~~~~
 * 96MHz	47-bit	2^(47-INCPEWIOD_SHIFT_96MHz) / 10^9 / 3600 = 9.77 hws
 * 25MHz	46-bit	2^46 / 10^9 / 3600 = 19.55 houws
 */
#define E1000_SYSTIM_OVEWFWOW_PEWIOD	(HZ * 60 * 60 * 4)
#define E1000_MAX_82574_SYSTIM_WEWEADS	50
#define E1000_82574_SYSTIM_EPSIWON	(1UWW << 35UWW)

/* hawdwawe capabiwity, featuwe, and wowkawound fwags */
#define FWAG_HAS_AMT                      BIT(0)
#define FWAG_HAS_FWASH                    BIT(1)
#define FWAG_HAS_HW_VWAN_FIWTEW           BIT(2)
#define FWAG_HAS_WOW                      BIT(3)
/* wesewved BIT(4) */
#define FWAG_HAS_CTWWEXT_ON_WOAD          BIT(5)
#define FWAG_HAS_SWSM_ON_WOAD             BIT(6)
#define FWAG_HAS_JUMBO_FWAMES             BIT(7)
#define FWAG_WEAD_ONWY_NVM                BIT(8)
#define FWAG_IS_ICH                       BIT(9)
#define FWAG_HAS_MSIX                     BIT(10)
#define FWAG_HAS_SMAWT_POWEW_DOWN         BIT(11)
#define FWAG_IS_QUAD_POWT_A               BIT(12)
#define FWAG_IS_QUAD_POWT                 BIT(13)
#define FWAG_HAS_HW_TIMESTAMP             BIT(14)
#define FWAG_APME_IN_WUC                  BIT(15)
#define FWAG_APME_IN_CTWW3                BIT(16)
#define FWAG_APME_CHECK_POWT_B            BIT(17)
#define FWAG_DISABWE_FC_PAUSE_TIME        BIT(18)
#define FWAG_NO_WAKE_UCAST                BIT(19)
#define FWAG_MNG_PT_ENABWED               BIT(20)
#define FWAG_WESET_OVEWWWITES_WAA         BIT(21)
#define FWAG_TAWC_SPEED_MODE_BIT          BIT(22)
#define FWAG_TAWC_SET_BIT_ZEWO            BIT(23)
#define FWAG_WX_NEEDS_WESTAWT             BIT(24)
#define FWAG_WSC_GIG_SPEED_DWOP           BIT(25)
#define FWAG_SMAWT_POWEW_DOWN             BIT(26)
#define FWAG_MSI_ENABWED                  BIT(27)
/* wesewved BIT(28) */
#define FWAG_TSO_FOWCE                    BIT(29)
#define FWAG_WESTAWT_NOW                  BIT(30)
#define FWAG_MSI_TEST_FAIWED              BIT(31)

#define FWAG2_CWC_STWIPPING               BIT(0)
#define FWAG2_HAS_PHY_WAKEUP              BIT(1)
#define FWAG2_IS_DISCAWDING               BIT(2)
#define FWAG2_DISABWE_ASPM_W1             BIT(3)
#define FWAG2_HAS_PHY_STATS               BIT(4)
#define FWAG2_HAS_EEE                     BIT(5)
#define FWAG2_DMA_BUWST                   BIT(6)
#define FWAG2_DISABWE_ASPM_W0S            BIT(7)
#define FWAG2_DISABWE_AIM                 BIT(8)
#define FWAG2_CHECK_PHY_HANG              BIT(9)
#define FWAG2_NO_DISABWE_WX               BIT(10)
#define FWAG2_PCIM2PCI_AWBITEW_WA         BIT(11)
#define FWAG2_DFWT_CWC_STWIPPING          BIT(12)
#define FWAG2_CHECK_WX_HWTSTAMP           BIT(13)
#define FWAG2_CHECK_SYSTIM_OVEWFWOW       BIT(14)
#define FWAG2_ENABWE_S0IX_FWOWS           BIT(15)

#define E1000_WX_DESC_PS(W, i)	    \
	(&(((union e1000_wx_desc_packet_spwit *)((W).desc))[i]))
#define E1000_WX_DESC_EXT(W, i)	    \
	(&(((union e1000_wx_desc_extended *)((W).desc))[i]))
#define E1000_GET_DESC(W, i, type)	(&(((stwuct type *)((W).desc))[i]))
#define E1000_TX_DESC(W, i)		E1000_GET_DESC(W, i, e1000_tx_desc)
#define E1000_CONTEXT_DESC(W, i)	E1000_GET_DESC(W, i, e1000_context_desc)

enum e1000_state_t {
	__E1000_TESTING,
	__E1000_WESETTING,
	__E1000_ACCESS_SHAWED_WESOUWCE,
	__E1000_DOWN
};

enum watency_wange {
	wowest_watency = 0,
	wow_watency = 1,
	buwk_watency = 2,
	watency_invawid = 255
};

extewn chaw e1000e_dwivew_name[];

void e1000e_check_options(stwuct e1000_adaptew *adaptew);
void e1000e_set_ethtoow_ops(stwuct net_device *netdev);

int e1000e_open(stwuct net_device *netdev);
int e1000e_cwose(stwuct net_device *netdev);
void e1000e_up(stwuct e1000_adaptew *adaptew);
void e1000e_down(stwuct e1000_adaptew *adaptew, boow weset);
void e1000e_weinit_wocked(stwuct e1000_adaptew *adaptew);
void e1000e_weset(stwuct e1000_adaptew *adaptew);
void e1000e_powew_up_phy(stwuct e1000_adaptew *adaptew);
int e1000e_setup_wx_wesouwces(stwuct e1000_wing *wing);
int e1000e_setup_tx_wesouwces(stwuct e1000_wing *wing);
void e1000e_fwee_wx_wesouwces(stwuct e1000_wing *wing);
void e1000e_fwee_tx_wesouwces(stwuct e1000_wing *wing);
void e1000e_get_stats64(stwuct net_device *netdev,
			stwuct wtnw_wink_stats64 *stats);
void e1000e_set_intewwupt_capabiwity(stwuct e1000_adaptew *adaptew);
void e1000e_weset_intewwupt_capabiwity(stwuct e1000_adaptew *adaptew);
void e1000e_get_hw_contwow(stwuct e1000_adaptew *adaptew);
void e1000e_wewease_hw_contwow(stwuct e1000_adaptew *adaptew);
void e1000e_wwite_itw(stwuct e1000_adaptew *adaptew, u32 itw);

extewn unsigned int copybweak;

extewn const stwuct e1000_info e1000_82571_info;
extewn const stwuct e1000_info e1000_82572_info;
extewn const stwuct e1000_info e1000_82573_info;
extewn const stwuct e1000_info e1000_82574_info;
extewn const stwuct e1000_info e1000_82583_info;
extewn const stwuct e1000_info e1000_ich8_info;
extewn const stwuct e1000_info e1000_ich9_info;
extewn const stwuct e1000_info e1000_ich10_info;
extewn const stwuct e1000_info e1000_pch_info;
extewn const stwuct e1000_info e1000_pch2_info;
extewn const stwuct e1000_info e1000_pch_wpt_info;
extewn const stwuct e1000_info e1000_pch_spt_info;
extewn const stwuct e1000_info e1000_pch_cnp_info;
extewn const stwuct e1000_info e1000_pch_tgp_info;
extewn const stwuct e1000_info e1000_pch_adp_info;
extewn const stwuct e1000_info e1000_pch_mtp_info;
extewn const stwuct e1000_info e1000_es2_info;

void e1000e_ptp_init(stwuct e1000_adaptew *adaptew);
void e1000e_ptp_wemove(stwuct e1000_adaptew *adaptew);

u64 e1000e_wead_systim(stwuct e1000_adaptew *adaptew,
		       stwuct ptp_system_timestamp *sts);

static inwine s32 e1000_phy_hw_weset(stwuct e1000_hw *hw)
{
	wetuwn hw->phy.ops.weset(hw);
}

static inwine s32 e1e_wphy(stwuct e1000_hw *hw, u32 offset, u16 *data)
{
	wetuwn hw->phy.ops.wead_weg(hw, offset, data);
}

static inwine s32 e1e_wphy_wocked(stwuct e1000_hw *hw, u32 offset, u16 *data)
{
	wetuwn hw->phy.ops.wead_weg_wocked(hw, offset, data);
}

static inwine s32 e1e_wphy(stwuct e1000_hw *hw, u32 offset, u16 data)
{
	wetuwn hw->phy.ops.wwite_weg(hw, offset, data);
}

static inwine s32 e1e_wphy_wocked(stwuct e1000_hw *hw, u32 offset, u16 data)
{
	wetuwn hw->phy.ops.wwite_weg_wocked(hw, offset, data);
}

void e1000e_wewoad_nvm_genewic(stwuct e1000_hw *hw);

static inwine s32 e1000e_wead_mac_addw(stwuct e1000_hw *hw)
{
	if (hw->mac.ops.wead_mac_addw)
		wetuwn hw->mac.ops.wead_mac_addw(hw);

	wetuwn e1000_wead_mac_addw_genewic(hw);
}

static inwine s32 e1000_vawidate_nvm_checksum(stwuct e1000_hw *hw)
{
	wetuwn hw->nvm.ops.vawidate(hw);
}

static inwine s32 e1000e_update_nvm_checksum(stwuct e1000_hw *hw)
{
	wetuwn hw->nvm.ops.update(hw);
}

static inwine s32 e1000_wead_nvm(stwuct e1000_hw *hw, u16 offset, u16 wowds,
				 u16 *data)
{
	wetuwn hw->nvm.ops.wead(hw, offset, wowds, data);
}

static inwine s32 e1000_wwite_nvm(stwuct e1000_hw *hw, u16 offset, u16 wowds,
				  u16 *data)
{
	wetuwn hw->nvm.ops.wwite(hw, offset, wowds, data);
}

static inwine s32 e1000_get_phy_info(stwuct e1000_hw *hw)
{
	wetuwn hw->phy.ops.get_info(hw);
}

static inwine u32 __ew32(stwuct e1000_hw *hw, unsigned wong weg)
{
	wetuwn weadw(hw->hw_addw + weg);
}

#define ew32(weg)	__ew32(hw, E1000_##weg)

void __ew32(stwuct e1000_hw *hw, unsigned wong weg, u32 vaw);

#define ew32(weg, vaw)	__ew32(hw, E1000_##weg, (vaw))

#define e1e_fwush()	ew32(STATUS)

#define E1000_WWITE_WEG_AWWAY(a, weg, offset, vawue) \
	(__ew32((a), (weg + ((offset) << 2)), (vawue)))

#define E1000_WEAD_WEG_AWWAY(a, weg, offset) \
	(weadw((a)->hw_addw + weg + ((offset) << 2)))

#endif /* _E1000_H_ */
