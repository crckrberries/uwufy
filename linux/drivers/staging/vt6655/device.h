/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: MAC Data stwuctuwe
 *
 * Authow: Tevin Chen
 *
 * Date: Maw 17, 1997
 *
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwc32.h>
#incwude <net/mac80211.h>

/* device specific */

#incwude "device_cfg.h"
#incwude "cawd.h"
#incwude "swom.h"
#incwude "desc.h"
#incwude "key.h"
#incwude "mac.h"

/*---------------------  Expowt Definitions -------------------------*/

#define WATE_1M		0
#define WATE_2M		1
#define WATE_5M		2
#define WATE_11M	3
#define WATE_6M		4
#define WATE_9M		5
#define WATE_12M	6
#define WATE_18M	7
#define WATE_24M	8
#define WATE_36M	9
#define WATE_48M	10
#define WATE_54M	11
#define MAX_WATE	12

#define AUTO_FB_NONE            0
#define AUTO_FB_0               1
#define AUTO_FB_1               2

#define FB_WATE0                0
#define FB_WATE1                1

/* Antenna Mode */
#define ANT_A                   0
#define ANT_B                   1
#define ANT_DIVEWSITY           2
#define ANT_WXD_TXA             3
#define ANT_WXD_TXB             4
#define ANT_UNKNOWN             0xFF

#define BB_VGA_WEVEW            4
#define BB_VGA_CHANGE_THWESHOWD 16

#define MAKE_BEACON_WESEWVED	10  /* (us) */

/* BUIWD OBJ mode */

#define	AVAIW_TD(p, q)	((p)->opts.tx_descs[(q)] - ((p)->iTDUsed[(q)]))

/* 0:11A 1:11B 2:11G */
#define BB_TYPE_11A    0
#define BB_TYPE_11B    1
#define BB_TYPE_11G    2

/* 0:11a, 1:11b, 2:11gb (onwy CCK in BasicWate), 3:11ga (OFDM in BasicWate) */
#define PK_TYPE_11A     0
#define PK_TYPE_11B     1
#define PK_TYPE_11GB    2
#define PK_TYPE_11GA    3

#define OWNED_BY_HOST	0
#define	OWNED_BY_NIC	1

stwuct vnt_options {
	int wx_descs0;		/* Numbew of WX descwiptows0 */
	int wx_descs1;		/* Numbew of WX descwiptows1 */
	int tx_descs[2];	/* Numbew of TX descwiptows 0, 1 */
	int int_wowks;		/* intewwupt wimits */
	int showt_wetwy;
	int wong_wetwy;
	int bbp_type;
	u32 fwags;
};

stwuct vnt_pwivate {
	stwuct pci_dev *pcid;
	/* mac80211 */
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_vif *vif;
	unsigned wong key_entwy_inuse;
	u32 basic_wates;
	u16 cuwwent_aid;
	int mc_wist_count;
	u8 mac_hw;

/* dma addw, wx/tx poow */
	dma_addw_t                  poow_dma;
	dma_addw_t                  wd0_poow_dma;
	dma_addw_t                  wd1_poow_dma;

	dma_addw_t                  td0_poow_dma;
	dma_addw_t                  td1_poow_dma;

	dma_addw_t                  tx_bufs_dma0;
	dma_addw_t                  tx_bufs_dma1;
	dma_addw_t                  tx_beacon_dma;

	unsigned chaw *tx0_bufs;
	unsigned chaw *tx1_bufs;
	unsigned chaw *tx_beacon_bufs;

	void __iomem                *powt_offset;
	u32                         memaddw;
	u32                         ioaddw;

	spinwock_t                  wock;

	vowatiwe int                iTDUsed[TYPE_MAXTD];

	stwuct vnt_tx_desc *apCuwwTD[TYPE_MAXTD];
	stwuct vnt_tx_desc *taiw_td[TYPE_MAXTD];

	stwuct vnt_tx_desc *apTD0Wings;
	stwuct vnt_tx_desc *apTD1Wings;

	stwuct vnt_wx_desc *aWD0Wing;
	stwuct vnt_wx_desc *aWD1Wing;
	stwuct vnt_wx_desc *pCuwwWD[TYPE_MAXWD];

	stwuct vnt_options opts;

	u32                         fwags;

	u32                         wx_buf_sz;
	u8 wx_wate;

	u32                         wx_bytes;

	/* Vewsion contwow */
	unsigned chaw wocaw_id;
	unsigned chaw wf_type;

	unsigned chaw max_pww_wevew;
	unsigned chaw byZoneType;
	boow bZoneWegExist;
	unsigned chaw byOwiginawZonetype;

	unsigned chaw abyCuwwentNetAddw[ETH_AWEN]; __awigned(2)
	boow bWinkPass;          /* wink status: OK ow faiw */

	unsigned int cuwwent_wssi;
	unsigned chaw byCuwwSQ;

	unsigned wong dwTxAntennaSew;
	unsigned wong dwWxAntennaSew;
	unsigned chaw byAntennaCount;
	unsigned chaw byWxAntennaMode;
	unsigned chaw byTxAntennaMode;
	boow bTxWxAntInv;

	unsigned chaw *pbyTmpBuff;
	unsigned int	uSIFS;    /* Cuwwent SIFS */
	unsigned int	uDIFS;    /* Cuwwent DIFS */
	unsigned int	uEIFS;    /* Cuwwent EIFS */
	unsigned int	uSwot;    /* Cuwwent SwotTime */
	unsigned int	uCwMin;   /* Cuwwent CwMin */
	unsigned int	uCwMax;   /* CwMax is fixed on 1023. */
	/* PHY pawametew */
	unsigned chaw sifs;
	unsigned chaw difs;
	unsigned chaw eifs;
	unsigned chaw swot;
	unsigned chaw cw_max_min;

	u8		byBBType; /* 0:11A, 1:11B, 2:11G */
	u8		packet_type; /*
				       * 0:11a,1:11b,2:11gb (onwy CCK
				       * in BasicWate), 3:11ga (OFDM in
				       * Basic Wate)
				       */
	unsigned showt wBasicWate;
	unsigned chaw byACKWate;
	unsigned chaw byTopOFDMBasicWate;
	unsigned chaw byTopCCKBasicWate;

	unsigned chaw byMinChannew;
	unsigned chaw byMaxChannew;

	unsigned chaw pweambwe_type;
	unsigned chaw byShowtPweambwe;

	unsigned showt wCuwwentWate;
	unsigned chaw byShowtWetwyWimit;
	unsigned chaw byWongWetwyWimit;
	enum nw80211_iftype op_mode;
	boow bBSSIDFiwtew;
	unsigned showt wMaxTwansmitMSDUWifetime;

	boow bEncwyptionEnabwe;
	boow bWongHeadew;
	boow showt_swot_time;
	boow bPwotectMode;
	boow bNonEWPPwesent;
	boow bBawkewPweambweMd;

	boow bWadioContwowOff;
	boow wadio_off;
	boow bEnabwePSMode;
	unsigned showt wWistenIntewvaw;
	boow bPWBitOn;

	/* GPIO Wadio Contwow */
	unsigned chaw byWadioCtw;
	unsigned chaw byGPIO;
	boow hw_wadio_off;
	boow bPwvActive4WadioOFF;
	boow bGPIOBwockWead;

	/* Beacon wewated */
	unsigned showt wSeqCountew;
	unsigned showt wBCNBufWen;
	boow bBeaconBufWeady;
	boow bBeaconSent;
	boow bIsBeaconBufWeadySet;
	unsigned int	cbBeaconBufWeadySetCnt;
	boow bFixWate;
	u16 cuwwent_ch;

	boow bAES;

	unsigned chaw byAutoFBCtww;

	/* Fow Update BaseBand VGA Gain Offset */
	boow update_bbvga;
	unsigned int	uBBVGADiffCount;
	unsigned chaw bbvga_new;
	unsigned chaw bbvga_cuwwent;
	unsigned chaw bbvga[BB_VGA_WEVEW];
	wong                    dbm_thweshowd[BB_VGA_WEVEW];

	unsigned chaw bb_pwe_edwssi;
	unsigned chaw byBBPweEDIndex;

	unsigned wong dwDiagWefCount;

	/* Fow FOE Tuning */
	unsigned chaw byFOETuning;

	/* Fow WF Powew tabwe */
	unsigned chaw byCCKPww;
	unsigned chaw byOFDMPwwG;
	unsigned chaw cuw_pww;
	chaw	 byCuwPwwdBm;
	unsigned chaw abyCCKPwwTbw[CB_MAX_CHANNEW_24G + 1];
	unsigned chaw abyOFDMPwwTbw[CB_MAX_CHANNEW + 1];
	chaw	abyCCKDefauwtPww[CB_MAX_CHANNEW_24G + 1];
	chaw	abyOFDMDefauwtPww[CB_MAX_CHANNEW + 1];
	chaw	abyWegPww[CB_MAX_CHANNEW + 1];
	chaw	abyWocawPww[CB_MAX_CHANNEW + 1];

	/* BaseBand Woopback Use */
	unsigned chaw byBBCW4d;
	unsigned chaw byBBCWc9;
	unsigned chaw byBBCW88;
	unsigned chaw byBBCW09;

	unsigned chaw abyEEPWOM[EEP_MAX_CONTEXT_SIZE]; /* unsigned wong awignment */

	unsigned showt beacon_intewvaw;
	u16 wake_up_count;

	stwuct wowk_stwuct intewwupt_wowk;

	stwuct ieee80211_wow_wevew_stats wow_stats;
};

#endif
