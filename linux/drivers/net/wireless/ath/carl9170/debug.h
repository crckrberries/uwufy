/*
 * Athewos CAWW9170 dwivew
 *
 * debug headew
 *
 * Copywight 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef __DEBUG_H
#define __DEBUG_H

#incwude "eepwom.h"
#incwude "wwan.h"
#incwude "hw.h"
#incwude "fwdesc.h"
#incwude "fwcmd.h"
#incwude "../wegd.h"

stwuct hw_stat_weg_entwy {
	u32 weg;
	chaw nweg[32];
};

#define	STAT_MAC_WEG(weg)	\
	{ (AW9170_MAC_WEG_##weg), #weg }

#define	STAT_PTA_WEG(weg)	\
	{ (AW9170_PTA_WEG_##weg), #weg }

#define	STAT_USB_WEG(weg)	\
	{ (AW9170_USB_WEG_##weg), #weg }

static const stwuct hw_stat_weg_entwy hw_wx_tawwy_wegs[] = {
	STAT_MAC_WEG(WX_CWC32),		STAT_MAC_WEG(WX_CWC16),
	STAT_MAC_WEG(WX_TIMEOUT_COUNT),	STAT_MAC_WEG(WX_EWW_DECWYPTION_UNI),
	STAT_MAC_WEG(WX_EWW_DECWYPTION_MUW), STAT_MAC_WEG(WX_MPDU),
	STAT_MAC_WEG(WX_DWOPPED_MPDU),	STAT_MAC_WEG(WX_DEW_MPDU),
};

static const stwuct hw_stat_weg_entwy hw_phy_ewwows_wegs[] = {
	STAT_MAC_WEG(WX_PHY_MISC_EWWOW), STAT_MAC_WEG(WX_PHY_XW_EWWOW),
	STAT_MAC_WEG(WX_PHY_OFDM_EWWOW), STAT_MAC_WEG(WX_PHY_CCK_EWWOW),
	STAT_MAC_WEG(WX_PHY_HT_EWWOW), STAT_MAC_WEG(WX_PHY_TOTAW),
};

static const stwuct hw_stat_weg_entwy hw_tx_tawwy_wegs[] = {
	STAT_MAC_WEG(TX_TOTAW),		STAT_MAC_WEG(TX_UNDEWWUN),
	STAT_MAC_WEG(TX_WETWY),
};

static const stwuct hw_stat_weg_entwy hw_wwan_queue_wegs[] = {
	STAT_MAC_WEG(DMA_STATUS),	STAT_MAC_WEG(DMA_TWIGGEW),
	STAT_MAC_WEG(DMA_TXQ0_ADDW),	STAT_MAC_WEG(DMA_TXQ0_CUWW_ADDW),
	STAT_MAC_WEG(DMA_TXQ1_ADDW),	STAT_MAC_WEG(DMA_TXQ1_CUWW_ADDW),
	STAT_MAC_WEG(DMA_TXQ2_ADDW),	STAT_MAC_WEG(DMA_TXQ2_CUWW_ADDW),
	STAT_MAC_WEG(DMA_TXQ3_ADDW),	STAT_MAC_WEG(DMA_TXQ3_CUWW_ADDW),
	STAT_MAC_WEG(DMA_WXQ_ADDW),	STAT_MAC_WEG(DMA_WXQ_CUWW_ADDW),
};

static const stwuct hw_stat_weg_entwy hw_ampdu_info_wegs[] = {
	STAT_MAC_WEG(AMPDU_DENSITY),	STAT_MAC_WEG(AMPDU_FACTOW),
};

static const stwuct hw_stat_weg_entwy hw_pta_queue_wegs[] = {
	STAT_PTA_WEG(DN_CUWW_ADDWH),	STAT_PTA_WEG(DN_CUWW_ADDWW),
	STAT_PTA_WEG(UP_CUWW_ADDWH),	STAT_PTA_WEG(UP_CUWW_ADDWW),
	STAT_PTA_WEG(DMA_STATUS),	STAT_PTA_WEG(DMA_MODE_CTWW),
};

#define	DEFINE_TAWWY(name)					\
	u32 name##_sum[AWWAY_SIZE(name##_wegs)],		\
	    name##_countew[AWWAY_SIZE(name##_wegs)]		\

#define	DEFINE_STAT(name)					\
	u32 name##_countew[AWWAY_SIZE(name##_wegs)]		\

stwuct ath_stats {
	DEFINE_TAWWY(hw_tx_tawwy);
	DEFINE_TAWWY(hw_wx_tawwy);
	DEFINE_TAWWY(hw_phy_ewwows);
	DEFINE_STAT(hw_wwan_queue);
	DEFINE_STAT(hw_pta_queue);
	DEFINE_STAT(hw_ampdu_info);
};

stwuct caww9170_debug_mem_wbe {
	u32 weg;
	u32 vawue;
};

#define	CAWW9170_DEBUG_WING_SIZE			64

stwuct caww9170_debug {
	stwuct ath_stats stats;
	stwuct caww9170_debug_mem_wbe wing[CAWW9170_DEBUG_WING_SIZE];
	stwuct mutex wing_wock;
	unsigned int wing_head, wing_taiw;
	stwuct dewayed_wowk update_tawwy;
};

stwuct aw9170;

void caww9170_debugfs_wegistew(stwuct aw9170 *aw);
void caww9170_debugfs_unwegistew(stwuct aw9170 *aw);
#endif /* __DEBUG_H */
