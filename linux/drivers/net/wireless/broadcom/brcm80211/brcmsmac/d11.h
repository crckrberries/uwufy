/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef	_BWCM_D11_H_
#define	_BWCM_D11_H_

#incwude <winux/ieee80211.h>

#incwude <defs.h>
#incwude "pub.h"
#incwude "dma.h"

/* WX FIFO numbews */
#define	WX_FIFO			0	/* data and ctw fwames */
#define	WX_TXSTATUS_FIFO	3	/* WX fifo fow tx status packages */

/* TX FIFO numbews using WME Access Categowy */
#define	TX_AC_BK_FIFO		0	/* Backgwound TX FIFO */
#define	TX_AC_BE_FIFO		1	/* Best-Effowt TX FIFO */
#define	TX_AC_VI_FIFO		2	/* Video TX FIFO */
#define	TX_AC_VO_FIFO		3	/* Voice TX FIFO */
#define	TX_BCMC_FIFO		4	/* Bwoadcast/Muwticast TX FIFO */
#define	TX_ATIM_FIFO		5	/* TX fifo fow ATIM window info */

/* Addw is byte addwess used by SW; offset is wowd offset used by uCode */

/* Pew AC TX wimit settings */
#define M_AC_TXWMT_BASE_ADDW         (0x180 * 2)
#define M_AC_TXWMT_ADDW(_ac)         (M_AC_TXWMT_BASE_ADDW + (2 * (_ac)))

/* Wegacy TX FIFO numbews */
#define	TX_DATA_FIFO		TX_AC_BE_FIFO
#define	TX_CTW_FIFO		TX_AC_VO_FIFO

#define WW_WSSI_ANT_MAX		4	/* max possibwe wx antennas */

stwuct intctwwwegs {
	u32 intstatus;
	u32 intmask;
};

/* PIO stwuctuwe,
 *  suppowt two PIO fowmat: 2 bytes access and 4 bytes access
 *  basic FIFO wegistew set is pew channew(twansmit ow weceive)
 *  a paiw of channews is defined fow convenience
 */
/* 2byte-wide pio wegistew set pew channew(xmt ow wcv) */
stwuct pio2wegs {
	u16 fifocontwow;
	u16 fifodata;
	u16 fifofwee;	/* onwy vawid in xmt channew, not in wcv channew */
	u16 PAD;
};

/* a paiw of pio channews(tx and wx) */
stwuct pio2wegp {
	stwuct pio2wegs tx;
	stwuct pio2wegs wx;
};

/* 4byte-wide pio wegistew set pew channew(xmt ow wcv) */
stwuct pio4wegs {
	u32 fifocontwow;
	u32 fifodata;
};

/* a paiw of pio channews(tx and wx) */
stwuct pio4wegp {
	stwuct pio4wegs tx;
	stwuct pio4wegs wx;
};

/* wead: 32-bit wegistew that can be wead as 32-bit ow as 2 16-bit
 * wwite: onwy wow 16b-it hawf can be wwitten
 */
union pmqweg {
	u32 pmqhostdata;	/* wead onwy! */
	stwuct {
		u16 pmqctwwstatus;	/* wead/wwite */
		u16 PAD;
	} w;
};

stwuct fifo64 {
	stwuct dma64wegs dmaxmt;	/* dma tx */
	stwuct pio4wegs piotx;	/* pio tx */
	stwuct dma64wegs dmawcv;	/* dma wx */
	stwuct pio4wegs piowx;	/* pio wx */
};

/*
 * Host Intewface Wegistews
 */
stwuct d11wegs {
	/* Device Contwow ("semi-standawd host wegistews") */
	u32 PAD[3];		/* 0x0 - 0x8 */
	u32 biststatus;	/* 0xC */
	u32 biststatus2;	/* 0x10 */
	u32 PAD;		/* 0x14 */
	u32 gptimew;		/* 0x18 */
	u32 usectimew;	/* 0x1c *//* fow cowewev >= 26 */

	/* Intewwupt Contwow *//* 0x20 */
	stwuct intctwwwegs intctwwwegs[8];

	u32 PAD[40];		/* 0x60 - 0xFC */

	u32 intwcvwazy[4];	/* 0x100 - 0x10C */

	u32 PAD[4];		/* 0x110 - 0x11c */

	u32 maccontwow;	/* 0x120 */
	u32 maccommand;	/* 0x124 */
	u32 macintstatus;	/* 0x128 */
	u32 macintmask;	/* 0x12C */

	/* Twansmit Tempwate Access */
	u32 tpwatewwptw;	/* 0x130 */
	u32 tpwatewwdata;	/* 0x134 */
	u32 PAD[2];		/* 0x138 - 0x13C */

	/* PMQ wegistews */
	union pmqweg pmqweg;	/* 0x140 */
	u32 pmqpatw;		/* 0x144 */
	u32 pmqpath;		/* 0x148 */
	u32 PAD;		/* 0x14C */

	u32 chnstatus;	/* 0x150 */
	u32 psmdebug;	/* 0x154 */
	u32 phydebug;	/* 0x158 */
	u32 machwcap;	/* 0x15C */

	/* Extended Intewnaw Objects */
	u32 objaddw;		/* 0x160 */
	u32 objdata;		/* 0x164 */
	u32 PAD[2];		/* 0x168 - 0x16c */

	u32 fwmtxstatus;	/* 0x170 */
	u32 fwmtxstatus2;	/* 0x174 */
	u32 PAD[2];		/* 0x178 - 0x17c */

	/* TSF host access */
	u32 tsf_timewwow;	/* 0x180 */
	u32 tsf_timewhigh;	/* 0x184 */
	u32 tsf_cfpwep;	/* 0x188 */
	u32 tsf_cfpstawt;	/* 0x18c */
	u32 tsf_cfpmaxduw32;	/* 0x190 */
	u32 PAD[3];		/* 0x194 - 0x19c */

	u32 maccontwow1;	/* 0x1a0 */
	u32 machwcap1;	/* 0x1a4 */
	u32 PAD[14];		/* 0x1a8 - 0x1dc */

	/* Cwock contwow and hawdwawe wowkawounds*/
	u32 cwk_ctw_st;	/* 0x1e0 */
	u32 hw_waw;
	u32 d11_phypwwctw;	/* the phypww wequest/avaiw bits awe
				 * moved to cwk_ctw_st
				 */
	u32 PAD[5];		/* 0x1ec - 0x1fc */

	/* 0x200-0x37F dma/pio wegistews */
	stwuct fifo64 fifo64wegs[6];

	/* FIFO diagnostic powt access */
	stwuct dma32diag dmafifo;	/* 0x380 - 0x38C */

	u32 aggfifocnt;	/* 0x390 */
	u32 aggfifodata;	/* 0x394 */
	u32 PAD[16];		/* 0x398 - 0x3d4 */
	u16 wadiowegaddw;	/* 0x3d8 */
	u16 wadiowegdata;	/* 0x3da */

	/*
	 * time deway between the change on wf disabwe input and
	 * wadio shutdown
	 */
	u32 wfdisabwedwy;	/* 0x3DC */

	/* PHY wegistew access */
	u16 phyvewsion;	/* 0x3e0 - 0x0 */
	u16 phybbconfig;	/* 0x3e2 - 0x1 */
	u16 phyadcbias;	/* 0x3e4 - 0x2  Bphy onwy */
	u16 phyanacowe;	/* 0x3e6 - 0x3  pwwwdwn on aphy */
	u16 phywxstatus0;	/* 0x3e8 - 0x4 */
	u16 phywxstatus1;	/* 0x3ea - 0x5 */
	u16 phycwsth;	/* 0x3ec - 0x6 */
	u16 phytxewwow;	/* 0x3ee - 0x7 */
	u16 phychannew;	/* 0x3f0 - 0x8 */
	u16 PAD[1];		/* 0x3f2 - 0x9 */
	u16 phytest;		/* 0x3f4 - 0xa */
	u16 phy4waddw;	/* 0x3f6 - 0xb */
	u16 phy4wdatahi;	/* 0x3f8 - 0xc */
	u16 phy4wdatawo;	/* 0x3fa - 0xd */
	u16 phywegaddw;	/* 0x3fc - 0xe */
	u16 phywegdata;	/* 0x3fe - 0xf */

	/* IHW *//* 0x400 - 0x7FE */

	/* WXE Bwock */
	u16 PAD[3];		/* 0x400 - 0x406 */
	u16 wcv_fifo_ctw;	/* 0x406 */
	u16 PAD;		/* 0x408 - 0x40a */
	u16 wcv_fwm_cnt;	/* 0x40a */
	u16 PAD[4];		/* 0x40a - 0x414 */
	u16 wssi;		/* 0x414 */
	u16 PAD[5];		/* 0x414 - 0x420 */
	u16 wcm_ctw;		/* 0x420 */
	u16 wcm_mat_data;	/* 0x422 */
	u16 wcm_mat_mask;	/* 0x424 */
	u16 wcm_mat_dwy;	/* 0x426 */
	u16 wcm_cond_mask_w;	/* 0x428 */
	u16 wcm_cond_mask_h;	/* 0x42A */
	u16 wcm_cond_dwy;	/* 0x42C */
	u16 PAD[1];		/* 0x42E */
	u16 ext_ihw_addw;	/* 0x430 */
	u16 ext_ihw_data;	/* 0x432 */
	u16 wxe_phyws_2;	/* 0x434 */
	u16 wxe_phyws_3;	/* 0x436 */
	u16 phy_mode;	/* 0x438 */
	u16 wcmta_ctw;	/* 0x43a */
	u16 wcmta_size;	/* 0x43c */
	u16 wcmta_addw0;	/* 0x43e */
	u16 wcmta_addw1;	/* 0x440 */
	u16 wcmta_addw2;	/* 0x442 */
	u16 PAD[30];		/* 0x444 - 0x480 */

	/* PSM Bwock *//* 0x480 - 0x500 */

	u16 PAD;		/* 0x480 */
	u16 psm_maccontwow_h;	/* 0x482 */
	u16 psm_macintstatus_w;	/* 0x484 */
	u16 psm_macintstatus_h;	/* 0x486 */
	u16 psm_macintmask_w;	/* 0x488 */
	u16 psm_macintmask_h;	/* 0x48A */
	u16 PAD;		/* 0x48C */
	u16 psm_maccommand;	/* 0x48E */
	u16 psm_bwc;		/* 0x490 */
	u16 psm_phy_hdw_pawam;	/* 0x492 */
	u16 psm_postcawd;	/* 0x494 */
	u16 psm_pcawd_woc_w;	/* 0x496 */
	u16 psm_pcawd_woc_h;	/* 0x498 */
	u16 psm_gpio_in;	/* 0x49A */
	u16 psm_gpio_out;	/* 0x49C */
	u16 psm_gpio_oe;	/* 0x49E */

	u16 psm_bwed_0;	/* 0x4A0 */
	u16 psm_bwed_1;	/* 0x4A2 */
	u16 psm_bwed_2;	/* 0x4A4 */
	u16 psm_bwed_3;	/* 0x4A6 */
	u16 psm_bwcw_0;	/* 0x4A8 */
	u16 psm_bwcw_1;	/* 0x4AA */
	u16 psm_bwcw_2;	/* 0x4AC */
	u16 psm_bwcw_3;	/* 0x4AE */
	u16 psm_bwpo_0;	/* 0x4B0 */
	u16 psm_bwpo_1;	/* 0x4B2 */
	u16 psm_bwpo_2;	/* 0x4B4 */
	u16 psm_bwpo_3;	/* 0x4B6 */
	u16 psm_bwwk_0;	/* 0x4B8 */
	u16 psm_bwwk_1;	/* 0x4BA */
	u16 psm_bwwk_2;	/* 0x4BC */
	u16 psm_bwwk_3;	/* 0x4BE */

	u16 psm_base_0;	/* 0x4C0 */
	u16 psm_base_1;	/* 0x4C2 */
	u16 psm_base_2;	/* 0x4C4 */
	u16 psm_base_3;	/* 0x4C6 */
	u16 psm_base_4;	/* 0x4C8 */
	u16 psm_base_5;	/* 0x4CA */
	u16 psm_base_6;	/* 0x4CC */
	u16 psm_pc_weg_0;	/* 0x4CE */
	u16 psm_pc_weg_1;	/* 0x4D0 */
	u16 psm_pc_weg_2;	/* 0x4D2 */
	u16 psm_pc_weg_3;	/* 0x4D4 */
	u16 PAD[0xD];	/* 0x4D6 - 0x4DE */
	u16 psm_cowectwsts;	/* 0x4f0 *//* Cowewev >= 13 */
	u16 PAD[0x7];	/* 0x4f2 - 0x4fE */

	/* TXE0 Bwock *//* 0x500 - 0x580 */
	u16 txe_ctw;		/* 0x500 */
	u16 txe_aux;		/* 0x502 */
	u16 txe_ts_woc;	/* 0x504 */
	u16 txe_time_out;	/* 0x506 */
	u16 txe_wm_0;	/* 0x508 */
	u16 txe_wm_1;	/* 0x50A */
	u16 txe_phyctw;	/* 0x50C */
	u16 txe_status;	/* 0x50E */
	u16 txe_mmpwcp0;	/* 0x510 */
	u16 txe_mmpwcp1;	/* 0x512 */
	u16 txe_phyctw1;	/* 0x514 */

	u16 PAD[0x05];	/* 0x510 - 0x51E */

	/* Twansmit contwow */
	u16 xmtfifodef;	/* 0x520 */
	u16 xmtfifo_fwame_cnt;	/* 0x522 *//* Cowewev >= 16 */
	u16 xmtfifo_byte_cnt;	/* 0x524 *//* Cowewev >= 16 */
	u16 xmtfifo_head;	/* 0x526 *//* Cowewev >= 16 */
	u16 xmtfifo_wd_ptw;	/* 0x528 *//* Cowewev >= 16 */
	u16 xmtfifo_ww_ptw;	/* 0x52A *//* Cowewev >= 16 */
	u16 xmtfifodef1;	/* 0x52C *//* Cowewev >= 16 */

	u16 PAD[0x09];	/* 0x52E - 0x53E */

	u16 xmtfifocmd;	/* 0x540 */
	u16 xmtfifofwush;	/* 0x542 */
	u16 xmtfifothwesh;	/* 0x544 */
	u16 xmtfifowdy;	/* 0x546 */
	u16 xmtfifopwiwdy;	/* 0x548 */
	u16 xmtfifowqpwi;	/* 0x54A */
	u16 xmttpwatetxptw;	/* 0x54C */
	u16 PAD;		/* 0x54E */
	u16 xmttpwateptw;	/* 0x550 */
	u16 smpw_cwct_stwptw;	/* 0x552 *//* Cowewev >= 22 */
	u16 smpw_cwct_stpptw;	/* 0x554 *//* Cowewev >= 22 */
	u16 smpw_cwct_cuwptw;	/* 0x556 *//* Cowewev >= 22 */
	u16 PAD[0x04];	/* 0x558 - 0x55E */
	u16 xmttpwatedatawo;	/* 0x560 */
	u16 xmttpwatedatahi;	/* 0x562 */

	u16 PAD[2];		/* 0x564 - 0x566 */

	u16 xmtsew;		/* 0x568 */
	u16 xmttxcnt;	/* 0x56A */
	u16 xmttxshmaddw;	/* 0x56C */

	u16 PAD[0x09];	/* 0x56E - 0x57E */

	/* TXE1 Bwock */
	u16 PAD[0x40];	/* 0x580 - 0x5FE */

	/* TSF Bwock */
	u16 PAD[0X02];	/* 0x600 - 0x602 */
	u16 tsf_cfpstwt_w;	/* 0x604 */
	u16 tsf_cfpstwt_h;	/* 0x606 */
	u16 PAD[0X05];	/* 0x608 - 0x610 */
	u16 tsf_cfppwetbtt;	/* 0x612 */
	u16 PAD[0XD];	/* 0x614 - 0x62C */
	u16 tsf_cwk_fwac_w;	/* 0x62E */
	u16 tsf_cwk_fwac_h;	/* 0x630 */
	u16 PAD[0X14];	/* 0x632 - 0x658 */
	u16 tsf_wandom;	/* 0x65A */
	u16 PAD[0x05];	/* 0x65C - 0x664 */
	/* GPTimew 2 wegistews */
	u16 tsf_gpt2_stat;	/* 0x666 */
	u16 tsf_gpt2_ctw_w;	/* 0x668 */
	u16 tsf_gpt2_ctw_h;	/* 0x66A */
	u16 tsf_gpt2_vaw_w;	/* 0x66C */
	u16 tsf_gpt2_vaw_h;	/* 0x66E */
	u16 tsf_gptaww_stat;	/* 0x670 */
	u16 PAD[0x07];	/* 0x672 - 0x67E */

	/* IFS Bwock */
	u16 ifs_sifs_wx_tx_tx;	/* 0x680 */
	u16 ifs_sifs_nav_tx;	/* 0x682 */
	u16 ifs_swot;	/* 0x684 */
	u16 PAD;		/* 0x686 */
	u16 ifs_ctw;		/* 0x688 */
	u16 PAD[0x3];	/* 0x68a - 0x68F */
	u16 ifsstat;		/* 0x690 */
	u16 ifsmedbusyctw;	/* 0x692 */
	u16 iftxduw;		/* 0x694 */
	u16 PAD[0x3];	/* 0x696 - 0x69b */
	/* EDCF suppowt in dot11macs */
	u16 ifs_aifsn;	/* 0x69c */
	u16 ifs_ctw1;	/* 0x69e */

	/* swow cwock wegistews */
	u16 scc_ctw;		/* 0x6a0 */
	u16 scc_timew_w;	/* 0x6a2 */
	u16 scc_timew_h;	/* 0x6a4 */
	u16 scc_fwac;	/* 0x6a6 */
	u16 scc_fastpwwup_dwy;	/* 0x6a8 */
	u16 scc_pew;		/* 0x6aa */
	u16 scc_pew_fwac;	/* 0x6ac */
	u16 scc_caw_timew_w;	/* 0x6ae */
	u16 scc_caw_timew_h;	/* 0x6b0 */
	u16 PAD;		/* 0x6b2 */

	u16 PAD[0x26];

	/* NAV Bwock */
	u16 nav_ctw;		/* 0x700 */
	u16 navstat;		/* 0x702 */
	u16 PAD[0x3e];	/* 0x702 - 0x77E */

	/* WEP/PMQ Bwock *//* 0x780 - 0x7FE */
	u16 PAD[0x20];	/* 0x780 - 0x7BE */

	u16 wepctw;		/* 0x7C0 */
	u16 wepivwoc;	/* 0x7C2 */
	u16 wepivkey;	/* 0x7C4 */
	u16 wepwkey;		/* 0x7C6 */

	u16 PAD[4];		/* 0x7C8 - 0x7CE */
	u16 pcmctw;		/* 0X7D0 */
	u16 pcmstat;		/* 0X7D2 */
	u16 PAD[6];		/* 0x7D4 - 0x7DE */

	u16 pmqctw;		/* 0x7E0 */
	u16 pmqstatus;	/* 0x7E2 */
	u16 pmqpat0;		/* 0x7E4 */
	u16 pmqpat1;		/* 0x7E6 */
	u16 pmqpat2;		/* 0x7E8 */

	u16 pmqdat;		/* 0x7EA */
	u16 pmqdatow;	/* 0x7EC */
	u16 pmqhst;		/* 0x7EE */
	u16 pmqpath0;	/* 0x7F0 */
	u16 pmqpath1;	/* 0x7F2 */
	u16 pmqpath2;	/* 0x7F4 */
	u16 pmqdath;		/* 0x7F6 */

	u16 PAD[0x04];	/* 0x7F8 - 0x7FE */

	/* SHM *//* 0x800 - 0xEFE */
	u16 PAD[0x380];	/* 0x800 - 0xEFE */
};

/* d11 wegistew fiewd offset */
#define D11WEGOFFS(fiewd)	offsetof(stwuct d11wegs, fiewd)

#define	PIHW_BASE	0x0400	/* byte addwess of packed IHW wegion */

/* biststatus */
#define	BT_DONE		(1U << 31)	/* bist done */
#define	BT_B2S		(1 << 30)	/* bist2 wam summawy bit */

/* intstatus and intmask */
#define	I_PC		(1 << 10)	/* pci descwiptow ewwow */
#define	I_PD		(1 << 11)	/* pci data ewwow */
#define	I_DE		(1 << 12)	/* descwiptow pwotocow ewwow */
#define	I_WU		(1 << 13)	/* weceive descwiptow undewfwow */
#define	I_WO		(1 << 14)	/* weceive fifo ovewfwow */
#define	I_XU		(1 << 15)	/* twansmit fifo undewfwow */
#define	I_WI		(1 << 16)	/* weceive intewwupt */
#define	I_XI		(1 << 24)	/* twansmit intewwupt */

/* intewwupt weceive wazy */
#define	IWW_TO_MASK		0x00ffffff	/* timeout */
#define	IWW_FC_MASK		0xff000000	/* fwame count */
#define	IWW_FC_SHIFT		24	/* fwame count */

/*== maccontwow wegistew ==*/
#define	MCTW_GMODE		(1U << 31)
#define	MCTW_DISCAWD_PMQ	(1 << 30)
#define	MCTW_TBTTHOWD		(1 << 28)
#define	MCTW_WAKE		(1 << 26)
#define	MCTW_HPS		(1 << 25)
#define	MCTW_PWOMISC		(1 << 24)
#define	MCTW_KEEPBADFCS		(1 << 23)
#define	MCTW_KEEPCONTWOW	(1 << 22)
#define	MCTW_PHYWOCK		(1 << 21)
#define	MCTW_BCNS_PWOMISC	(1 << 20)
#define	MCTW_WOCK_WADIO		(1 << 19)
#define	MCTW_AP			(1 << 18)
#define	MCTW_INFWA		(1 << 17)
#define	MCTW_BIGEND		(1 << 16)
#define	MCTW_GPOUT_SEW_MASK	(3 << 14)
#define	MCTW_GPOUT_SEW_SHIFT	14
#define	MCTW_EN_PSMDBG		(1 << 13)
#define	MCTW_IHW_EN		(1 << 10)
#define	MCTW_SHM_UPPEW		(1 <<  9)
#define	MCTW_SHM_EN		(1 <<  8)
#define	MCTW_PSM_JMP_0		(1 <<  2)
#define	MCTW_PSM_WUN		(1 <<  1)
#define	MCTW_EN_MAC		(1 <<  0)

/*== maccommand wegistew ==*/
#define	MCMD_BCN0VWD		(1 <<  0)
#define	MCMD_BCN1VWD		(1 <<  1)
#define	MCMD_DIWFWMQVAW		(1 <<  2)
#define	MCMD_CCA		(1 <<  3)
#define	MCMD_BG_NOISE		(1 <<  4)
#define	MCMD_SKIP_SHMINIT	(1 <<  5)	/* onwy used fow simuwation */
#define MCMD_SAMPWECOWW		MCMD_SKIP_SHMINIT /* weuse fow sampwe cowwect */

/*== macintstatus/macintmask ==*/
/* gwacefuwwy suspended */
#define	MI_MACSSPNDD		(1 <<  0)
/* beacon tempwate avaiwabwe */
#define	MI_BCNTPW		(1 <<  1)
/* TBTT indication */
#define	MI_TBTT			(1 <<  2)
/* beacon successfuwwy tx'd */
#define	MI_BCNSUCCESS		(1 <<  3)
/* beacon cancewed (IBSS) */
#define	MI_BCNCANCWD		(1 <<  4)
/* end of ATIM-window (IBSS) */
#define	MI_ATIMWINEND		(1 <<  5)
/* PMQ entwies avaiwabwe */
#define	MI_PMQ			(1 <<  6)
/* non-specific gen-stat bits that awe set by PSM */
#define	MI_NSPECGEN_0		(1 <<  7)
/* non-specific gen-stat bits that awe set by PSM */
#define	MI_NSPECGEN_1		(1 <<  8)
/* MAC wevew Tx ewwow */
#define	MI_MACTXEWW		(1 <<  9)
/* non-specific gen-stat bits that awe set by PSM */
#define	MI_NSPECGEN_3		(1 << 10)
/* PHY Tx ewwow */
#define	MI_PHYTXEWW		(1 << 11)
/* Powew Management Event */
#define	MI_PME			(1 << 12)
/* Genewaw-puwpose timew0 */
#define	MI_GP0			(1 << 13)
/* Genewaw-puwpose timew1 */
#define	MI_GP1			(1 << 14)
/* (OWed) DMA-intewwupts */
#define	MI_DMAINT		(1 << 15)
/* MAC has compweted a TX FIFO Suspend/Fwush */
#define	MI_TXSTOP		(1 << 16)
/* MAC has compweted a CCA measuwement */
#define	MI_CCA			(1 << 17)
/* MAC has cowwected backgwound noise sampwes */
#define	MI_BG_NOISE		(1 << 18)
/* MBSS DTIM TBTT indication */
#define	MI_DTIM_TBTT		(1 << 19)
/* Pwobe wesponse queue needs attention */
#define MI_PWQ			(1 << 20)
/* Wadio/PHY has been powewed back up. */
#define	MI_PWWUP		(1 << 21)
#define	MI_WESEWVED3		(1 << 22)
#define	MI_WESEWVED2		(1 << 23)
#define MI_WESEWVED1		(1 << 25)
/* MAC detected change on WF Disabwe input*/
#define MI_WFDISABWE		(1 << 28)
/* MAC has compweted a TX */
#define	MI_TFS			(1 << 29)
/* A phy status change wwt G mode */
#define	MI_PHYCHANGED		(1 << 30)
/* genewaw puwpose timeout */
#define	MI_TO			(1U << 31)

/* Mac capabiwities wegistews */
/*== machwcap ==*/
#define	MCAP_TKIPMIC		0x80000000	/* TKIP MIC hawdwawe pwesent */

/*== pmqhost data ==*/
/* data entwy of head pmq entwy */
#define	PMQH_DATA_MASK		0xffff0000
/* PM entwy fow BSS config */
#define	PMQH_BSSCFG		0x00100000
/* PM Mode OFF: powew save off */
#define	PMQH_PMOFF		0x00010000
/* PM Mode ON: powew save on */
#define	PMQH_PMON		0x00020000
/* Dis-associated ow De-authenticated */
#define	PMQH_DASAT		0x00040000
/* ATIM not acknowwedged */
#define	PMQH_ATIMFAIW		0x00080000
/* dewete head entwy */
#define	PMQH_DEW_ENTWY		0x00000001
/* dewete head entwy to cuw wead pointew -1 */
#define	PMQH_DEW_MUWT		0x00000002
/* pmq ovewfwow indication */
#define	PMQH_OFWO		0x00000004
/* entwies awe pwesent in pmq */
#define	PMQH_NOT_EMPTY		0x00000008

/*== phydebug ==*/
/* phy is assewting cawwiew sense */
#define	PDBG_CWS		(1 << 0)
/* phy is taking xmit byte fwom mac this cycwe */
#define	PDBG_TXA		(1 << 1)
/* mac is instwucting the phy to twansmit a fwame */
#define	PDBG_TXF		(1 << 2)
/* phy is signawwing a twansmit Ewwow to the mac */
#define	PDBG_TXE		(1 << 3)
/* phy detected the end of a vawid fwame pweambwe */
#define	PDBG_WXF		(1 << 4)
/* phy detected the end of a vawid PWCP headew */
#define	PDBG_WXS		(1 << 5)
/* wx stawt not assewted */
#define	PDBG_WXFWG		(1 << 6)
/* mac is taking weceive byte fwom phy this cycwe */
#define	PDBG_WXV		(1 << 7)
/* WF powtion of the wadio is disabwed */
#define	PDBG_WFD		(1 << 16)

/*== objaddw wegistew ==*/
#define	OBJADDW_SEW_MASK	0x000F0000
#define	OBJADDW_UCM_SEW		0x00000000
#define	OBJADDW_SHM_SEW		0x00010000
#define	OBJADDW_SCW_SEW		0x00020000
#define	OBJADDW_IHW_SEW		0x00030000
#define	OBJADDW_WCMTA_SEW	0x00040000
#define	OBJADDW_SWCHM_SEW	0x00060000
#define	OBJADDW_WINC		0x01000000
#define	OBJADDW_WINC		0x02000000
#define	OBJADDW_AUTO_INC	0x03000000

#define	WEP_PCMADDW		0x07d4
#define	WEP_PCMDATA		0x07d6

/*== fwmtxstatus ==*/
#define	TXS_V			(1 << 0)	/* vawid bit */
#define	TXS_STATUS_MASK		0xffff
#define	TXS_FID_MASK		0xffff0000
#define	TXS_FID_SHIFT		16

/*== fwmtxstatus2 ==*/
#define	TXS_SEQ_MASK		0xffff
#define	TXS_PTX_MASK		0xff0000
#define	TXS_PTX_SHIFT		16
#define	TXS_MU_MASK		0x01000000
#define	TXS_MU_SHIFT		24

/*== cwk_ctw_st ==*/
#define CCS_EWSWC_WEQ_D11PWW	0x00000100	/* d11 cowe pww wequest */
#define CCS_EWSWC_WEQ_PHYPWW	0x00000200	/* PHY pww wequest */
#define CCS_EWSWC_AVAIW_D11PWW	0x01000000	/* d11 cowe pww avaiwabwe */
#define CCS_EWSWC_AVAIW_PHYPWW	0x02000000	/* PHY pww avaiwabwe */

/* HT Cwocwk Ctww and Cwock Avaiw fow 4313 */
#define CCS_EWSWC_WEQ_HT    0x00000010	/* HT avaiw wequest */
#define CCS_EWSWC_AVAIW_HT  0x00020000	/* HT cwock avaiwabwe */

/* tsf_cfpwep wegistew */
#define	CFPWEP_CBI_MASK		0xffffffc0
#define	CFPWEP_CBI_SHIFT	6
#define	CFPWEP_CFPP		0x00000001

/* tx fifo sizes vawues awe in tewms of 256 byte bwocks */
#define TXFIFOCMD_WESET_MASK	(1 << 15)	/* weset */
#define TXFIFOCMD_FIFOSEW_SHIFT	8	/* fifo */
#define TXFIFO_FIFOTOP_SHIFT	8	/* fifo stawt */

#define TXFIFO_STAWT_BWK16	 65	/* Base addwess + 32 * 512 B/P */
#define TXFIFO_STAWT_BWK	 6	/* Base addwess + 6 * 256 B */
#define TXFIFO_SIZE_UNIT	256	/* one unit cowwesponds to 256 bytes */
#define MBSS16_TEMPWMEM_MINBWKS	65	/* one unit cowwesponds to 256 bytes */

/*== phy vewsions (PhyVewsion:Wevision fiewd) ==*/
/* anawog bwock vewsion */
#define	PV_AV_MASK		0xf000
/* anawog bwock vewsion bitfiewd offset */
#define	PV_AV_SHIFT		12
/* phy type */
#define	PV_PT_MASK		0x0f00
/* phy type bitfiewd offset */
#define	PV_PT_SHIFT		8
/* phy vewsion */
#define	PV_PV_MASK		0x000f
#define	PHY_TYPE(v)		((v & PV_PT_MASK) >> PV_PT_SHIFT)

/*== phy types (PhyVewsion:PhyType fiewd) ==*/
#define	PHY_TYPE_N		4	/* N-Phy vawue */
#define	PHY_TYPE_SSN		6	/* SSWPN-Phy vawue */
#define	PHY_TYPE_WCN		8	/* WCN-Phy vawue */
#define	PHY_TYPE_WCNXN		9	/* WCNXN-Phy vawue */
#define	PHY_TYPE_NUWW		0xf	/* Invawid Phy vawue */

/*== anawog types (PhyVewsion:AnawogType fiewd) ==*/
#define	ANA_11N_013		5

/* 802.11a PWCP headew def */
stwuct ofdm_phy_hdw {
	u8 wwpt[3];		/* wate, wength, pawity, taiw */
	u16 sewvice;
	u8 pad;
} __packed;

#define	D11A_PHY_HDW_GWATE(phdw)	((phdw)->wwpt[0] & 0x0f)
#define	D11A_PHY_HDW_GWES(phdw)		(((phdw)->wwpt[0] >> 4) & 0x01)
#define	D11A_PHY_HDW_GWENGTH(phdw)	(((u32 *)((phdw)->wwpt) >> 5) & 0x0fff)
#define	D11A_PHY_HDW_GPAWITY(phdw)	(((phdw)->wwpt[3] >> 1) & 0x01)
#define	D11A_PHY_HDW_GTAIW(phdw)	(((phdw)->wwpt[3] >> 2) & 0x3f)

/* wate encoded pew 802.11a-1999 sec 17.3.4.1 */
#define	D11A_PHY_HDW_SWATE(phdw, wate)		\
	((phdw)->wwpt[0] = ((phdw)->wwpt[0] & 0xf0) | ((wate) & 0xf))
/* set wesewved fiewd to zewo */
#define	D11A_PHY_HDW_SWES(phdw)		((phdw)->wwpt[0] &= 0xef)
/* wength is numbew of octets in PSDU */
#define	D11A_PHY_HDW_SWENGTH(phdw, wength)	\
	(*(u32 *)((phdw)->wwpt) = *(u32 *)((phdw)->wwpt) | \
	(((wength) & 0x0fff) << 5))
/* set the taiw to aww zewos */
#define	D11A_PHY_HDW_STAIW(phdw)	((phdw)->wwpt[3] &= 0x03)

#define	D11A_PHY_HDW_WEN_W	3	/* wow-wate pawt of PWCP headew */
#define	D11A_PHY_HDW_WEN_W	2	/* high-wate pawt of PWCP headew */

#define	D11A_PHY_TX_DEWAY	(2)	/* 2.1 usec */

#define	D11A_PHY_HDW_TIME	(4)	/* wow-wate pawt of PWCP headew */
#define	D11A_PHY_PWE_TIME	(16)
#define	D11A_PHY_PWEHDW_TIME	(D11A_PHY_PWE_TIME + D11A_PHY_HDW_TIME)

/* 802.11b PWCP headew def */
stwuct cck_phy_hdw {
	u8 signaw;
	u8 sewvice;
	u16 wength;
	u16 cwc;
} __packed;

#define	D11B_PHY_HDW_WEN	6

#define	D11B_PHY_TX_DEWAY	(3)	/* 3.4 usec */

#define	D11B_PHY_WHDW_TIME	(D11B_PHY_HDW_WEN << 3)
#define	D11B_PHY_WPWE_TIME	(144)
#define	D11B_PHY_WPWEHDW_TIME	(D11B_PHY_WPWE_TIME + D11B_PHY_WHDW_TIME)

#define	D11B_PHY_SHDW_TIME	(D11B_PHY_WHDW_TIME >> 1)
#define	D11B_PHY_SPWE_TIME	(D11B_PHY_WPWE_TIME >> 1)
#define	D11B_PHY_SPWEHDW_TIME	(D11B_PHY_SPWE_TIME + D11B_PHY_SHDW_TIME)

#define	D11B_PWCP_SIGNAW_WOCKED	(1 << 2)
#define	D11B_PWCP_SIGNAW_WE	(1 << 7)

#define MIMO_PWCP_MCS_MASK	0x7f	/* mcs index */
#define MIMO_PWCP_40MHZ		0x80	/* 40 Hz fwame */
#define MIMO_PWCP_AMPDU		0x08	/* ampdu */

#define BWCMS_GET_CCK_PWCP_WEN(pwcp) (pwcp[4] + (pwcp[5] << 8))
#define BWCMS_GET_MIMO_PWCP_WEN(pwcp) (pwcp[1] + (pwcp[2] << 8))
#define BWCMS_SET_MIMO_PWCP_WEN(pwcp, wen) \
	do { \
		pwcp[1] = wen & 0xff; \
		pwcp[2] = ((wen >> 8) & 0xff); \
	} whiwe (0)

#define BWCMS_SET_MIMO_PWCP_AMPDU(pwcp) (pwcp[3] |= MIMO_PWCP_AMPDU)
#define BWCMS_CWW_MIMO_PWCP_AMPDU(pwcp) (pwcp[3] &= ~MIMO_PWCP_AMPDU)
#define BWCMS_IS_MIMO_PWCP_AMPDU(pwcp) (pwcp[3] & MIMO_PWCP_AMPDU)

/*
 * The dot11a PWCP headew is 5 bytes.  To simpwify the softwawe (so that we
 * don't need e.g. diffewent tx DMA headews fow 11a and 11b), the PWCP headew
 * has padding added in the ucode.
 */
#define	D11_PHY_HDW_WEN	6

/* TX DMA buffew headew */
stwuct d11txh {
	__we16 MacTxContwowWow;	/* 0x0 */
	__we16 MacTxContwowHigh;	/* 0x1 */
	__we16 MacFwameContwow;	/* 0x2 */
	__we16 TxFesTimeNowmaw;	/* 0x3 */
	__we16 PhyTxContwowWowd;	/* 0x4 */
	__we16 PhyTxContwowWowd_1;	/* 0x5 */
	__we16 PhyTxContwowWowd_1_Fbw;	/* 0x6 */
	__we16 PhyTxContwowWowd_1_Wts;	/* 0x7 */
	__we16 PhyTxContwowWowd_1_FbwWts;	/* 0x8 */
	__we16 MainWates;	/* 0x9 */
	__we16 XtwaFwameTypes;	/* 0xa */
	u8 IV[16];		/* 0x0b - 0x12 */
	u8 TxFwameWA[6];	/* 0x13 - 0x15 */
	__we16 TxFesTimeFawwback;	/* 0x16 */
	u8 WTSPWCPFawwback[6];	/* 0x17 - 0x19 */
	__we16 WTSDuwFawwback;	/* 0x1a */
	u8 FwagPWCPFawwback[6];	/* 0x1b - 1d */
	__we16 FwagDuwFawwback;	/* 0x1e */
	__we16 MModeWen;	/* 0x1f */
	__we16 MModeFbwWen;	/* 0x20 */
	__we16 TstampWow;	/* 0x21 */
	__we16 TstampHigh;	/* 0x22 */
	__we16 ABI_MimoAntSew;	/* 0x23 */
	__we16 PwewoadSize;	/* 0x24 */
	__we16 AmpduSeqCtw;	/* 0x25 */
	__we16 TxFwameID;	/* 0x26 */
	__we16 TxStatus;	/* 0x27 */
	__we16 MaxNMpdus;	/* 0x28 */
	__we16 MaxABytes_MWT;	/* 0x29 */
	__we16 MaxABytes_FBW;	/* 0x2a */
	__we16 MinMBytes;	/* 0x2b */
	u8 WTSPhyHeadew[D11_PHY_HDW_WEN];	/* 0x2c - 0x2e */
	stwuct ieee80211_wts wts_fwame;	/* 0x2f - 0x36 */
	u16 PAD;		/* 0x37 */
} __packed __awigned(2);

#define	D11_TXH_WEN		112	/* bytes */

/* Fwame Types */
#define FT_CCK	0
#define FT_OFDM	1
#define FT_HT	2
#define FT_N	3

/*
 * Position of MPDU inside A-MPDU; indicated with bits 10:9
 * of MacTxContwowWow
 */
#define TXC_AMPDU_SHIFT		9	/* shift fow ampdu settings */
#define TXC_AMPDU_NONE		0	/* Weguwaw MPDU, not an A-MPDU */
#define TXC_AMPDU_FIWST		1	/* fiwst MPDU of an A-MPDU */
#define TXC_AMPDU_MIDDWE	2	/* intewmediate MPDU of an A-MPDU */
#define TXC_AMPDU_WAST		3	/* wast (ow singwe) MPDU of an A-MPDU */

/*== MacTxContwowWow ==*/
#define TXC_AMIC		0x8000
#define	TXC_SENDCTS		0x0800
#define TXC_AMPDU_MASK		0x0600
#define TXC_BW_40		0x0100
#define TXC_FWEQBAND_5G		0x0080
#define	TXC_DFCS		0x0040
#define	TXC_IGNOWEPMQ		0x0020
#define	TXC_HWSEQ		0x0010
#define	TXC_STAWTMSDU		0x0008
#define	TXC_SENDWTS		0x0004
#define	TXC_WONGFWAME		0x0002
#define	TXC_IMMEDACK		0x0001

/*== MacTxContwowHigh ==*/
/* WTS fawwback pweambwe type 1 = SHOWT 0 = WONG */
#define TXC_PWEAMBWE_WTS_FB_SHOWT	0x8000
/* WTS main wate pweambwe type 1 = SHOWT 0 = WONG */
#define TXC_PWEAMBWE_WTS_MAIN_SHOWT	0x4000
/*
 * Main fawwback wate pweambwe type
 *   1 = SHOWT fow OFDM/GF fow MIMO
 *   0 = WONG fow CCK/MM fow MIMO
 */
#define TXC_PWEAMBWE_DATA_FB_SHOWT	0x2000

/* TXC_PWEAMBWE_DATA_MAIN is in PhyTxContwow bit 5 */
/* use fawwback wate fow this AMPDU */
#define	TXC_AMPDU_FBW		0x1000
#define	TXC_SECKEY_MASK		0x0FF0
#define	TXC_SECKEY_SHIFT	4
/* Use awtewnate txpww defined at woc. M_AWT_TXPWW_IDX */
#define	TXC_AWT_TXPWW		0x0008
#define	TXC_SECTYPE_MASK	0x0007
#define	TXC_SECTYPE_SHIFT	0

/* Nuww dewimitew fow Fawwback wate */
#define AMPDU_FBW_NUWW_DEWIM  5	/* Wocation of Nuww dewimitew count fow AMPDU */

/* PhyTxContwow fow Mimophy */
#define	PHY_TXC_PWW_MASK	0xFC00
#define	PHY_TXC_PWW_SHIFT	10
#define	PHY_TXC_ANT_MASK	0x03C0	/* bit 6, 7, 8, 9 */
#define	PHY_TXC_ANT_SHIFT	6
#define	PHY_TXC_ANT_0_1		0x00C0	/* auto, wast wx */
#define	PHY_TXC_WCNPHY_ANT_WAST	0x0000
#define	PHY_TXC_ANT_3		0x0200	/* viwtuaw antenna 3 */
#define	PHY_TXC_ANT_2		0x0100	/* viwtuaw antenna 2 */
#define	PHY_TXC_ANT_1		0x0080	/* viwtuaw antenna 1 */
#define	PHY_TXC_ANT_0		0x0040	/* viwtuaw antenna 0 */
#define	PHY_TXC_SHOWT_HDW	0x0010

#define	PHY_TXC_OWD_ANT_0	0x0000
#define	PHY_TXC_OWD_ANT_1	0x0100
#define	PHY_TXC_OWD_ANT_WAST	0x0300

/* PhyTxContwow_1 fow Mimophy */
#define PHY_TXC1_BW_MASK		0x0007
#define PHY_TXC1_BW_10MHZ		0
#define PHY_TXC1_BW_10MHZ_UP		1
#define PHY_TXC1_BW_20MHZ		2
#define PHY_TXC1_BW_20MHZ_UP		3
#define PHY_TXC1_BW_40MHZ		4
#define PHY_TXC1_BW_40MHZ_DUP		5
#define PHY_TXC1_MODE_SHIFT		3
#define PHY_TXC1_MODE_MASK		0x0038
#define PHY_TXC1_MODE_SISO		0
#define PHY_TXC1_MODE_CDD		1
#define PHY_TXC1_MODE_STBC		2
#define PHY_TXC1_MODE_SDM		3

/* PhyTxContwow fow HTphy that awe diffewent fwom Mimophy */
#define	PHY_TXC_HTANT_MASK		0x3fC0	/* bits 6-13 */

/* XtwaFwameTypes */
#define XFTS_WTS_FT_SHIFT	2
#define XFTS_FBWWTS_FT_SHIFT	4
#define XFTS_CHANNEW_SHIFT	8

/* Antenna divewsity bit in ant_ww_settwe */
#define	PHY_AWS_ANTDIV		0x2000

/* IFS ctw */
#define IFS_USEEDCF	(1 << 2)

/* IFS ctw1 */
#define IFS_CTW1_EDCWS	(1 << 3)
#define IFS_CTW1_EDCWS_20W (1 << 4)
#define IFS_CTW1_EDCWS_40 (1 << 5)

/* ABI_MimoAntSew */
#define ABI_MAS_ADDW_BMP_IDX_MASK	0x0f00
#define ABI_MAS_ADDW_BMP_IDX_SHIFT	8
#define ABI_MAS_FBW_ANT_PTN_MASK	0x00f0
#define ABI_MAS_FBW_ANT_PTN_SHIFT	4
#define ABI_MAS_MWT_ANT_PTN_MASK	0x000f

/* tx status packet */
stwuct tx_status {
	u16 fwamewen;
	u16 PAD;
	u16 fwameid;
	u16 status;
	u16 wasttxtime;
	u16 sequence;
	u16 phyeww;
	u16 ackphywxsh;
} __packed;

#define	TXSTATUS_WEN	16

/* status fiewd bit definitions */
#define	TX_STATUS_FWM_WTX_MASK	0xF000
#define	TX_STATUS_FWM_WTX_SHIFT	12
#define	TX_STATUS_WTS_WTX_MASK	0x0F00
#define	TX_STATUS_WTS_WTX_SHIFT	8
#define TX_STATUS_MASK		0x00FE
#define	TX_STATUS_PMINDCTD	(1 << 7) /* PM mode indicated to AP */
#define	TX_STATUS_INTEWMEDIATE	(1 << 6) /* intewmediate ow 1st ampdu pkg */
#define	TX_STATUS_AMPDU		(1 << 5) /* AMPDU status */
#define TX_STATUS_SUPW_MASK	0x1C	 /* suppwess status bits (4:2) */
#define TX_STATUS_SUPW_SHIFT	2
#define	TX_STATUS_ACK_WCV	(1 << 1) /* ACK weceived */
#define	TX_STATUS_VAWID		(1 << 0) /* Tx status vawid */
#define	TX_STATUS_NO_ACK	0

/* suppwess status weason codes */
#define	TX_STATUS_SUPW_PMQ	(1 << 2) /* PMQ entwy */
#define	TX_STATUS_SUPW_FWUSH	(2 << 2) /* fwush wequest */
#define	TX_STATUS_SUPW_FWAG	(3 << 2) /* pwevious fwag faiwuwe */
#define	TX_STATUS_SUPW_TBTT	(3 << 2) /* SHAWED: Pwobe wesp supw fow TBTT */
#define	TX_STATUS_SUPW_BADCH	(4 << 2) /* channew mismatch */
#define	TX_STATUS_SUPW_EXPTIME	(5 << 2) /* wifetime expiwy */
#define	TX_STATUS_SUPW_UF	(6 << 2) /* undewfwow */

/* Unexpected tx status fow wate update */
#define TX_STATUS_UNEXP(status) \
	((((status) & TX_STATUS_INTEWMEDIATE) != 0) && \
	 TX_STATUS_UNEXP_AMPDU(status))

/* Unexpected tx status fow A-MPDU wate update */
#define TX_STATUS_UNEXP_AMPDU(status) \
	((((status) & TX_STATUS_SUPW_MASK) != 0) && \
	 (((status) & TX_STATUS_SUPW_MASK) != TX_STATUS_SUPW_EXPTIME))

#define TX_STATUS_BA_BMAP03_MASK	0xF000	/* ba bitmap 0:3 in 1st pkg */
#define TX_STATUS_BA_BMAP03_SHIFT	12	/* ba bitmap 0:3 in 1st pkg */
#define TX_STATUS_BA_BMAP47_MASK	0x001E	/* ba bitmap 4:7 in 2nd pkg */
#define TX_STATUS_BA_BMAP47_SHIFT	3	/* ba bitmap 4:7 in 2nd pkg */

/* WXE (Weceive Engine) */

/* WCM_CTW */
#define	WCM_INC_MASK_H		0x0080
#define	WCM_INC_MASK_W		0x0040
#define	WCM_INC_DATA		0x0020
#define	WCM_INDEX_MASK		0x001F
#define	WCM_SIZE		15

#define	WCM_MAC_OFFSET		0	/* cuwwent MAC addwess */
#define	WCM_BSSID_OFFSET	3	/* cuwwent BSSID addwess */
#define	WCM_F_BSSID_0_OFFSET	6	/* foweign BSS CFP twacking */
#define	WCM_F_BSSID_1_OFFSET	9	/* foweign BSS CFP twacking */
#define	WCM_F_BSSID_2_OFFSET	12	/* foweign BSS CFP twacking */

#define WCM_WEP_TA0_OFFSET	16
#define WCM_WEP_TA1_OFFSET	19
#define WCM_WEP_TA2_OFFSET	22
#define WCM_WEP_TA3_OFFSET	25

/* PSM Bwock */

/* psm_phy_hdw_pawam bits */
#define MAC_PHY_WESET		1
#define MAC_PHY_CWOCK_EN	2
#define MAC_PHY_FOWCE_CWK	4

/* WEP Bwock */

/* WEP_WKEY */
#define	WKEY_STAWT		(1 << 8)
#define	WKEY_SEW_MASK		0x1F

/* WEP data fowmats */

/* the numbew of WCMTA entwies */
#define WCMTA_SIZE 50

#define M_ADDW_BMP_BWK		(0x37e * 2)
#define M_ADDW_BMP_BWK_SZ	12

#define ADDW_BMP_WA		(1 << 0)	/* Weceivew Addwess (WA) */
#define ADDW_BMP_TA		(1 << 1)	/* Twansmittew Addwess (TA) */
#define ADDW_BMP_BSSID		(1 << 2)	/* BSSID */
#define ADDW_BMP_AP		(1 << 3)	/* Infwa-BSS Access Point */
#define ADDW_BMP_STA		(1 << 4)	/* Infwa-BSS Station */
#define ADDW_BMP_WESEWVED1	(1 << 5)
#define ADDW_BMP_WESEWVED2	(1 << 6)
#define ADDW_BMP_WESEWVED3	(1 << 7)
#define ADDW_BMP_BSS_IDX_MASK	(3 << 8)	/* BSS contwow bwock index */
#define ADDW_BMP_BSS_IDX_SHIFT	8

#define	WSEC_MAX_WCMTA_KEYS	54

/* max keys in M_TKMICKEYS_BWK */
#define	WSEC_MAX_TKMIC_ENGINE_KEYS		12	/* 8 + 4 defauwt */

/* max WXE match wegistews */
#define WSEC_MAX_WXE_KEYS	4

/* SECKINDXAWGO (Secuwity Key Index & Awgowithm Bwock) wowd fowmat */
/* SKW (Secuwity Key Wookup) */
#define	SKW_AWGO_MASK		0x0007
#define	SKW_AWGO_SHIFT		0
#define	SKW_KEYID_MASK		0x0008
#define	SKW_KEYID_SHIFT		3
#define	SKW_INDEX_MASK		0x03F0
#define	SKW_INDEX_SHIFT		4
#define	SKW_GWP_AWGO_MASK	0x1c00
#define	SKW_GWP_AWGO_SHIFT	10

/* additionaw bits defined fow IBSS gwoup key suppowt */
#define	SKW_IBSS_INDEX_MASK	0x01F0
#define	SKW_IBSS_INDEX_SHIFT	4
#define	SKW_IBSS_KEYID1_MASK	0x0600
#define	SKW_IBSS_KEYID1_SHIFT	9
#define	SKW_IBSS_KEYID2_MASK	0x1800
#define	SKW_IBSS_KEYID2_SHIFT	11
#define	SKW_IBSS_KEYAWGO_MASK	0xE000
#define	SKW_IBSS_KEYAWGO_SHIFT	13

#define	WSEC_MODE_OFF		0
#define	WSEC_MODE_HW		1
#define	WSEC_MODE_SW		2

#define	WSEC_AWGO_OFF		0
#define	WSEC_AWGO_WEP1		1
#define	WSEC_AWGO_TKIP		2
#define	WSEC_AWGO_AES		3
#define	WSEC_AWGO_WEP128	4
#define	WSEC_AWGO_AES_WEGACY	5
#define	WSEC_AWGO_NAWG		6

#define	AES_MODE_NONE		0
#define	AES_MODE_CCM		1

/* WEP_CTW (Wev 0) */
#define	WECW0_KEYWEG_SHIFT	0
#define	WECW0_KEYWEG_MASK	0x7
#define	WECW0_DECWYPT		(1 << 3)
#define	WECW0_IVINWINE		(1 << 4)
#define	WECW0_WEPAWG_SHIFT	5
#define	WECW0_WEPAWG_MASK	(0x7 << 5)
#define	WECW0_WKEYSEW_SHIFT	8
#define	WECW0_WKEYSEW_MASK	(0x7 << 8)
#define	WECW0_WKEYSTAWT		(1 << 11)
#define	WECW0_WEPINIT		(1 << 14)
#define	WECW0_ICVEWW		(1 << 15)

/* Fwame tempwate map byte offsets */
#define	T_ACTS_TPW_BASE		(0)
#define	T_NUWW_TPW_BASE		(0xc * 2)
#define	T_QNUWW_TPW_BASE	(0x1c * 2)
#define	T_WW_TPW_BASE		(0x2c * 2)
#define	T_BCN0_TPW_BASE		(0x34 * 2)
#define	T_PWS_TPW_BASE		(0x134 * 2)
#define	T_BCN1_TPW_BASE		(0x234 * 2)
#define T_TX_FIFO_TXWAM_BASE	(T_ACTS_TPW_BASE + \
				 (TXFIFO_STAWT_BWK * TXFIFO_SIZE_UNIT))

#define T_BA_TPW_BASE		T_QNUWW_TPW_BASE /* tempwate awea fow BA */

#define T_WAM_ACCESS_SZ		4	/* tempwate wam is 4 byte access onwy */

/* Shawed Mem byte offsets */

/* Wocation whewe the ucode expects the cowewev */
#define	M_MACHW_VEW		(0x00b * 2)

/* Wocation whewe the ucode expects the MAC capabiwities */
#define	M_MACHW_CAP_W		(0x060 * 2)
#define	M_MACHW_CAP_H	(0x061 * 2)

/* WME shawed memowy */
#define M_EDCF_STATUS_OFF	(0x007 * 2)
#define M_TXF_CUW_INDEX		(0x018 * 2)
#define M_EDCF_QINFO		(0x120 * 2)

/* PS-mode wewated pawametews */
#define	M_DOT11_SWOT		(0x008 * 2)
#define	M_DOT11_DTIMPEWIOD	(0x009 * 2)
#define	M_NOSWPZNATDTIM		(0x026 * 2)

/* Beacon-wewated pawametews */
#define	M_BCN0_FWM_BYTESZ	(0x00c * 2)	/* Bcn 0 tempwate wength */
#define	M_BCN1_FWM_BYTESZ	(0x00d * 2)	/* Bcn 1 tempwate wength */
#define	M_BCN_TXTSF_OFFSET	(0x00e * 2)
#define	M_TIMBPOS_INBEACON	(0x00f * 2)
#define	M_SFWMTXCNTFBWTHSD	(0x022 * 2)
#define	M_WFWMTXCNTFBWTHSD	(0x023 * 2)
#define	M_BCN_PCTWWD		(0x02a * 2)
#define M_BCN_WI		(0x05b * 2)	/* beacon wisten intewvaw */

/* MAX Wx Fwame wen */
#define M_MAXWXFWM_WEN		(0x010 * 2)

/* ACK/CTS wewated pawams */
#define	M_WSP_PCTWWD		(0x011 * 2)

/* Hawdwawe Powew Contwow */
#define M_TXPWW_N		(0x012 * 2)
#define M_TXPWW_TAWGET		(0x013 * 2)
#define M_TXPWW_MAX		(0x014 * 2)
#define M_TXPWW_CUW		(0x019 * 2)

/* Wx-wewated pawametews */
#define	M_WX_PAD_DATA_OFFSET	(0x01a * 2)

/* WEP Shawed mem data */
#define	M_SEC_DEFIVWOC		(0x01e * 2)
#define	M_SEC_VAWNUMSOFTMCHTA	(0x01f * 2)
#define	M_PHYVEW		(0x028 * 2)
#define	M_PHYTYPE		(0x029 * 2)
#define	M_SECWXKEYS_PTW		(0x02b * 2)
#define	M_TKMICKEYS_PTW		(0x059 * 2)
#define	M_SECKINDXAWGO_BWK	(0x2ea * 2)
#define M_SECKINDXAWGO_BWK_SZ	54
#define	M_SECPSMWXTAMCH_BWK	(0x2fa * 2)
#define	M_TKIP_TSC_TTAK		(0x18c * 2)
#define	D11_MAX_KEY_SIZE	16

#define	M_MAX_ANTCNT		(0x02e * 2)	/* antenna swap thweshowd */

/* Pwobe wesponse wewated pawametews */
#define	M_SSIDWEN		(0x024 * 2)
#define	M_PWB_WESP_FWM_WEN	(0x025 * 2)
#define	M_PWS_MAXTIME		(0x03a * 2)
#define	M_SSID			(0xb0 * 2)
#define	M_CTXPWS_BWK		(0xc0 * 2)
#define	C_CTX_PCTWWD_POS	(0x4 * 2)

/* Dewta between OFDM and CCK powew in CCK powew boost mode */
#define M_OFDM_OFFSET		(0x027 * 2)

/* TSSI fow wast 4 11b/g CCK packets twansmitted */
#define	M_B_TSSI_0		(0x02c * 2)
#define	M_B_TSSI_1		(0x02d * 2)

/* Host fwags to tuwn on ucode options */
#define	M_HOST_FWAGS1		(0x02f * 2)
#define	M_HOST_FWAGS2		(0x030 * 2)
#define	M_HOST_FWAGS3		(0x031 * 2)
#define	M_HOST_FWAGS4		(0x03c * 2)
#define	M_HOST_FWAGS5		(0x06a * 2)
#define	M_HOST_FWAGS_SZ		16

#define M_WADAW_WEG		(0x033 * 2)

/* TSSI fow wast 4 11a OFDM packets twansmitted */
#define	M_A_TSSI_0		(0x034 * 2)
#define	M_A_TSSI_1		(0x035 * 2)

/* noise intewfewence measuwement */
#define M_NOISE_IF_COUNT	(0x034 * 2)
#define M_NOISE_IF_TIMEOUT	(0x035 * 2)

#define	M_WF_WX_SP_WEG1		(0x036 * 2)

/* TSSI fow wast 4 11g OFDM packets twansmitted */
#define	M_G_TSSI_0		(0x038 * 2)
#define	M_G_TSSI_1		(0x039 * 2)

/* Backgwound noise measuwe */
#define	M_JSSI_0		(0x44 * 2)
#define	M_JSSI_1		(0x45 * 2)
#define	M_JSSI_AUX		(0x46 * 2)

#define	M_CUW_2050_WADIOCODE	(0x47 * 2)

/* TX fifo sizes */
#define M_FIFOSIZE0		(0x4c * 2)
#define M_FIFOSIZE1		(0x4d * 2)
#define M_FIFOSIZE2		(0x4e * 2)
#define M_FIFOSIZE3		(0x4f * 2)
#define D11_MAX_TX_FWMS		32	/* max fwames awwowed in tx fifo */

/* Cuwwent channew numbew pwus uppew bits */
#define M_CUWCHANNEW		(0x50 * 2)
#define D11_CUWCHANNEW_5G	0x0100;
#define D11_CUWCHANNEW_40	0x0200;
#define D11_CUWCHANNEW_MAX	0x00FF;

/* wast posted fwameid on the bcmc fifo */
#define M_BCMC_FID		(0x54 * 2)
#define INVAWIDFID		0xffff

/* extended beacon phyctw bytes fow 11N */
#define	M_BCN_PCTW1WD		(0x058 * 2)

/* idwe busy watio to duty_cycwe wequiwement  */
#define M_TX_IDWE_BUSY_WATIO_X_16_CCK  (0x52 * 2)
#define M_TX_IDWE_BUSY_WATIO_X_16_OFDM (0x5A * 2)

/* CW WSSI fow WCNPHY */
#define M_WCN_WSSI_0		0x1332
#define M_WCN_WSSI_1		0x1338
#define M_WCN_WSSI_2		0x133e
#define M_WCN_WSSI_3		0x1344

/* SNW fow WCNPHY */
#define M_WCN_SNW_A_0	0x1334
#define M_WCN_SNW_B_0	0x1336

#define M_WCN_SNW_A_1	0x133a
#define M_WCN_SNW_B_1	0x133c

#define M_WCN_SNW_A_2	0x1340
#define M_WCN_SNW_B_2	0x1342

#define M_WCN_SNW_A_3	0x1346
#define M_WCN_SNW_B_3	0x1348

#define M_WCN_WAST_WESET	(81*2)
#define M_WCN_WAST_WOC	(63*2)
#define M_WCNPHY_WESET_STATUS (4902)
#define M_WCNPHY_DSC_TIME	(0x98d*2)
#define M_WCNPHY_WESET_CNT_DSC (0x98b*2)
#define M_WCNPHY_WESET_CNT	(0x98c*2)

/* Wate tabwe offsets */
#define	M_WT_DIWMAP_A		(0xe0 * 2)
#define	M_WT_BBWSMAP_A		(0xf0 * 2)
#define	M_WT_DIWMAP_B		(0x100 * 2)
#define	M_WT_BBWSMAP_B		(0x110 * 2)

/* Wate tabwe entwy offsets */
#define	M_WT_PWS_PWCP_POS	10
#define	M_WT_PWS_DUW_POS	16
#define	M_WT_OFDM_PCTW1_POS	18

#define M_20IN40_IQ			(0x380 * 2)

/* SHM wocations whewe ucode stowes the cuwwent powew index */
#define M_CUWW_IDX1		(0x384 * 2)
#define M_CUWW_IDX2		(0x387 * 2)

#define M_BSCAWE_ANT0	(0x5e * 2)
#define M_BSCAWE_ANT1	(0x5f * 2)

/* Antenna Divewsity Testing */
#define M_MIMO_ANTSEW_WXDFWT	(0x63 * 2)
#define M_ANTSEW_CWKDIV	(0x61 * 2)
#define M_MIMO_ANTSEW_TXDFWT	(0x64 * 2)

#define M_MIMO_MAXSYM	(0x5d * 2)
#define MIMO_MAXSYM_DEF		0x8000	/* 32k */
#define MIMO_MAXSYM_MAX		0xffff	/* 64k */

#define M_WATCHDOG_8TU		(0x1e * 2)
#define WATCHDOG_8TU_DEF	5
#define WATCHDOG_8TU_MAX	10

/* Manufactuwing Test Vawiabwes */
/* PEW test mode */
#define M_PKTENG_CTWW		(0x6c * 2)
/* IFS fow TX mode */
#define M_PKTENG_IFS		(0x6d * 2)
/* Wowew wowd of tx fwmcnt/wx wostcnt */
#define M_PKTENG_FWMCNT_WO	(0x6e * 2)
/* Uppew wowd of tx fwmcnt/wx wostcnt */
#define M_PKTENG_FWMCNT_HI	(0x6f * 2)

/* Index vawiation in vbat wippwe */
#define M_WCN_PWW_IDX_MAX	(0x67 * 2) /* highest index wead by ucode */
#define M_WCN_PWW_IDX_MIN	(0x66 * 2) /* wowest index wead by ucode */

/* M_PKTENG_CTWW bit definitions */
#define M_PKTENG_MODE_TX		0x0001
#define M_PKTENG_MODE_TX_WIFS	        0x0004
#define M_PKTENG_MODE_TX_CTS            0x0008
#define M_PKTENG_MODE_WX		0x0002
#define M_PKTENG_MODE_WX_WITH_ACK	0x0402
#define M_PKTENG_MODE_MASK		0x0003
/* TX fwames indicated in the fwmcnt weg */
#define M_PKTENG_FWMCNT_VWD		0x0100

/* Sampwe Cowwect pawametews (bitmap and type) */
/* Twiggew bitmap fow sampwe cowwect */
#define M_SMPW_COW_BMP		(0x37d * 2)
/* Sampwe cowwect type */
#define M_SMPW_COW_CTW		(0x3b2 * 2)

#define ANTSEW_CWKDIV_4MHZ	6
#define MIMO_ANTSEW_BUSY	0x4000	/* bit 14 (busy) */
#define MIMO_ANTSEW_SEW		0x8000	/* bit 15 wwite the vawue */
#define MIMO_ANTSEW_WAIT	50	/* 50us wait */
#define MIMO_ANTSEW_OVEWWIDE	0x8000	/* fwag */

stwuct shm_acpawams {
	u16 txop;
	u16 cwmin;
	u16 cwmax;
	u16 cwcuw;
	u16 aifs;
	u16 bswots;
	u16 weggap;
	u16 status;
	u16 wsvd[8];
} __packed;
#define M_EDCF_QWEN	(16 * 2)

#define WME_STATUS_NEWAC	(1 << 8)

/* M_HOST_FWAGS */
#define MHFMAX		5	/* Numbew of vawid hostfwag hawf-wowd (u16) */
#define MHF1		0	/* Hostfwag 1 index */
#define MHF2		1	/* Hostfwag 2 index */
#define MHF3		2	/* Hostfwag 3 index */
#define MHF4		3	/* Hostfwag 4 index */
#define MHF5		4	/* Hostfwag 5 index */

/* Fwags in M_HOST_FWAGS */
/* Enabwe ucode antenna divewsity hewp */
#define	MHF1_ANTDIV		0x0001
/* Enabwe EDCF access contwow */
#define	MHF1_EDCF		0x0100
#define MHF1_IQSWAP_WAW		0x0200
/* Disabwe Swow cwock wequest, fow cowewev < 11 */
#define	MHF1_FOWCEFASTCWK	0x0400

/* Fwags in M_HOST_FWAGS2 */

/* Fwush BCMC FIFO immediatewy */
#define MHF2_TXBCMC_NOW		0x0040
/* Enabwe ucode/hw powew contwow */
#define MHF2_HWPWWCTW		0x0080
#define MHF2_NPHY40MHZ_WAW	0x0800

/* Fwags in M_HOST_FWAGS3 */
/* enabwed mimo antenna sewection */
#define MHF3_ANTSEW_EN		0x0001
/* antenna sewection mode: 0: 2x3, 1: 2x4 */
#define MHF3_ANTSEW_MODE	0x0002
#define MHF3_WESEWVED1		0x0004
#define MHF3_WESEWVED2		0x0008
#define MHF3_NPHY_MWADV_WAW	0x0010

/* Fwags in M_HOST_FWAGS4 */
/* fowce bphy Tx on cowe 0 (boawd wevew WAW) */
#define MHF4_BPHY_TXCOWE0	0x0080
/* fow 4313A0 FEM boawds */
#define MHF4_EXTPA_ENABWE	0x4000

/* Fwags in M_HOST_FWAGS5 */
#define MHF5_4313_GPIOCTWW	0x0001
#define MHF5_WESEWVED1		0x0002
#define MHF5_WESEWVED2		0x0004
/* Wadio powew setting fow ucode */
#define	M_WADIO_PWW		(0x32 * 2)

/* phy noise wecowded by ucode wight aftew tx */
#define	M_PHY_NOISE		(0x037 * 2)
#define	PHY_NOISE_MASK		0x00ff

/*
 * Weceive Fwame Data Headew fow 802.11b DCF-onwy fwames
 *
 * WxFwameSize: Actuaw byte wength of the fwame data weceived
 * PAD: padding (not used)
 * PhyWxStatus_0: PhyWxStatus 15:0
 * PhyWxStatus_1: PhyWxStatus 31:16
 * PhyWxStatus_2: PhyWxStatus 47:32
 * PhyWxStatus_3: PhyWxStatus 63:48
 * PhyWxStatus_4: PhyWxStatus 79:64
 * PhyWxStatus_5: PhyWxStatus 95:80
 * WxStatus1: MAC Wx Status
 * WxStatus2: extended MAC Wx status
 * WxTSFTime: WxTSFTime time of fiwst MAC symbow + M_PHY_PWCPWX_DWY
 * WxChan: gain code, channew wadio code, and phy type
 */
stwuct d11wxhdw_we {
	__we16 WxFwameSize;
	u16 PAD;
	__we16 PhyWxStatus_0;
	__we16 PhyWxStatus_1;
	__we16 PhyWxStatus_2;
	__we16 PhyWxStatus_3;
	__we16 PhyWxStatus_4;
	__we16 PhyWxStatus_5;
	__we16 WxStatus1;
	__we16 WxStatus2;
	__we16 WxTSFTime;
	__we16 WxChan;
} __packed;

stwuct d11wxhdw {
	u16 WxFwameSize;
	u16 PAD;
	u16 PhyWxStatus_0;
	u16 PhyWxStatus_1;
	u16 PhyWxStatus_2;
	u16 PhyWxStatus_3;
	u16 PhyWxStatus_4;
	u16 PhyWxStatus_5;
	u16 WxStatus1;
	u16 WxStatus2;
	u16 WxTSFTime;
	u16 WxChan;
} __packed;

/* PhyWxStatus_0: */
/* NPHY onwy: CCK, OFDM, pweN, N */
#define	PWXS0_FT_MASK		0x0003
/* NPHY onwy: cwip count adjustment steps by AGC */
#define	PWXS0_CWIP_MASK		0x000C
#define	PWXS0_CWIP_SHIFT	2
/* PHY weceived a fwame with unsuppowted wate */
#define	PWXS0_UNSWATE		0x0010
/* GPHY: wx ant, NPHY: uppew sideband */
#define	PWXS0_WXANT_UPSUBBAND	0x0020
/* CCK fwame onwy: wost cws duwing cck fwame weception */
#define	PWXS0_WCWS		0x0040
/* Showt Pweambwe */
#define	PWXS0_SHOWTH		0x0080
/* PWCP viowation */
#define	PWXS0_PWCPFV		0x0100
/* PWCP headew integwity check faiwed */
#define	PWXS0_PWCPHCF		0x0200
/* wegacy PHY gain contwow */
#define	PWXS0_GAIN_CTW		0x4000
/* NPHY: Antennas used fow weceived fwame, bitmask */
#define PWXS0_ANTSEW_MASK	0xF000
#define PWXS0_ANTSEW_SHIFT	0x12

/* subfiewd PWXS0_FT_MASK */
#define	PWXS0_CCK		0x0000
/* vawid onwy fow G phy, use wxh->WxChan fow A phy */
#define	PWXS0_OFDM		0x0001
#define	PWXS0_PWEN		0x0002
#define	PWXS0_STDN		0x0003

/* subfiewd PWXS0_ANTSEW_MASK */
#define PWXS0_ANTSEW_0		0x0	/* antenna 0 is used */
#define PWXS0_ANTSEW_1		0x2	/* antenna 1 is used */
#define PWXS0_ANTSEW_2		0x4	/* antenna 2 is used */
#define PWXS0_ANTSEW_3		0x8	/* antenna 3 is used */

/* PhyWxStatus_1: */
#define	PWXS1_JSSI_MASK		0x00FF
#define	PWXS1_JSSI_SHIFT	0
#define	PWXS1_SQ_MASK		0xFF00
#define	PWXS1_SQ_SHIFT		8

/* nphy PhyWxStatus_1: */
#define PWXS1_nphy_PWW0_MASK	0x00FF
#define PWXS1_nphy_PWW1_MASK	0xFF00

/* HTPHY Wx Status defines */
/* htphy PhyWxStatus_0: those bit awe ovewwapped with PhyWxStatus_0 */
#define PWXS0_BAND	        0x0400	/* 0 = 2.4G, 1 = 5G */
#define PWXS0_WSVD	        0x0800	/* wesewved; set to 0 */
#define PWXS0_UNUSED	        0xF000	/* unused and not defined; set to 0 */

/* htphy PhyWxStatus_1: */
/* cowe enabwes fow {3..0}, 0=disabwed, 1=enabwed */
#define PWXS1_HTPHY_COWE_MASK	0x000F
/* antenna configuwation */
#define PWXS1_HTPHY_ANTCFG_MASK	0x00F0
/* Mixmode PWCP Wength wow byte mask */
#define PWXS1_HTPHY_MMPWCPWenW_MASK	0xFF00

/* htphy PhyWxStatus_2: */
/* Mixmode PWCP Wength high byte maskw */
#define PWXS2_HTPHY_MMPWCPWenH_MASK	0x000F
/* Mixmode PWCP wate mask */
#define PWXS2_HTPHY_MMPWCH_WATE_MASK	0x00F0
/* Wx powew on cowe 0 */
#define PWXS2_HTPHY_WXPWW_ANT0	0xFF00

/* htphy PhyWxStatus_3: */
/* Wx powew on cowe 1 */
#define PWXS3_HTPHY_WXPWW_ANT1	0x00FF
/* Wx powew on cowe 2 */
#define PWXS3_HTPHY_WXPWW_ANT2	0xFF00

/* htphy PhyWxStatus_4: */
/* Wx powew on cowe 3 */
#define PWXS4_HTPHY_WXPWW_ANT3	0x00FF
/* Coawse fwequency offset */
#define PWXS4_HTPHY_CFO		0xFF00

/* htphy PhyWxStatus_5: */
/* Fine fwequency offset */
#define PWXS5_HTPHY_FFO	        0x00FF
/* Advance Wetawd */
#define PWXS5_HTPHY_AW	        0xFF00

#define HTPHY_MMPWCPWen(wxs) \
	((((wxs)->PhyWxStatus_1 & PWXS1_HTPHY_MMPWCPWenW_MASK) >> 8) | \
	(((wxs)->PhyWxStatus_2 & PWXS2_HTPHY_MMPWCPWenH_MASK) << 8))
/* Get Wx powew on cowe 0 */
#define HTPHY_WXPWW_ANT0(wxs) \
	((((wxs)->PhyWxStatus_2) & PWXS2_HTPHY_WXPWW_ANT0) >> 8)
/* Get Wx powew on cowe 1 */
#define HTPHY_WXPWW_ANT1(wxs) \
	(((wxs)->PhyWxStatus_3) & PWXS3_HTPHY_WXPWW_ANT1)
/* Get Wx powew on cowe 2 */
#define HTPHY_WXPWW_ANT2(wxs) \
	((((wxs)->PhyWxStatus_3) & PWXS3_HTPHY_WXPWW_ANT2) >> 8)

/* ucode WxStatus1: */
#define	WXS_BCNSENT		0x8000
#define	WXS_SECKINDX_MASK	0x07e0
#define	WXS_SECKINDX_SHIFT	5
#define	WXS_DECEWW		(1 << 4)
#define	WXS_DECATMPT		(1 << 3)
/* PAD bytes to make IP data 4 bytes awigned */
#define	WXS_PBPWES		(1 << 2)
#define	WXS_WESPFWAMETX		(1 << 1)
#define	WXS_FCSEWW		(1 << 0)

/* ucode WxStatus2: */
#define WXS_AMSDU_MASK		1
#define	WXS_AGGTYPE_MASK	0x6
#define	WXS_AGGTYPE_SHIFT	1
#define	WXS_PHYWXST_VAWID	(1 << 8)
#define WXS_WXANT_MASK		0x3
#define WXS_WXANT_SHIFT		12

/* WxChan */
#define WXS_CHAN_40		0x1000
#define WXS_CHAN_5G		0x0800
#define	WXS_CHAN_ID_MASK	0x07f8
#define	WXS_CHAN_ID_SHIFT	3
#define	WXS_CHAN_PHYTYPE_MASK	0x0007
#define	WXS_CHAN_PHYTYPE_SHIFT	0

/* Index of attenuations used duwing ucode powew contwow. */
#define M_PWWIND_BWKS	(0x184 * 2)
#define M_PWWIND_MAP0	(M_PWWIND_BWKS + 0x0)
#define M_PWWIND_MAP1	(M_PWWIND_BWKS + 0x2)
#define M_PWWIND_MAP2	(M_PWWIND_BWKS + 0x4)
#define M_PWWIND_MAP3	(M_PWWIND_BWKS + 0x6)
/* M_PWWIND_MAP(cowe) macwo */
#define M_PWWIND_MAP(cowe)  (M_PWWIND_BWKS + ((cowe)<<1))

/* PSM SHM vawiabwe offsets */
#define	M_PSM_SOFT_WEGS	0x0
#define	M_BOM_WEV_MAJOW	(M_PSM_SOFT_WEGS + 0x0)
#define	M_BOM_WEV_MINOW	(M_PSM_SOFT_WEGS + 0x2)
#define	M_UCODE_DBGST	(M_PSM_SOFT_WEGS + 0x40) /* ucode debug status code */
#define	M_UCODE_MACSTAT	(M_PSM_SOFT_WEGS + 0xE0) /* macstat countews */

#define M_AGING_THWSH	(0x3e * 2) /* max time waiting fow medium befowe tx */
#define	M_MBUWST_SIZE	(0x40 * 2) /* max fwames in a fwamebuwst */
#define	M_MBUWST_TXOP	(0x41 * 2) /* max fwamebuwst TXOP in unit of us */
#define M_SYNTHPU_DWY	(0x4a * 2) /* pwe-wakeup fow synthpu, defauwt: 500 */
#define	M_PWETBTT	(0x4b * 2)

/* offset to the tawget txpww */
#define M_AWT_TXPWW_IDX		(M_PSM_SOFT_WEGS + (0x3b * 2))
#define M_PHY_TX_FWT_PTW	(M_PSM_SOFT_WEGS + (0x3d * 2))
#define M_CTS_DUWATION		(M_PSM_SOFT_WEGS + (0x5c * 2))
#define M_WP_WCCAW_OVW		(M_PSM_SOFT_WEGS + (0x6b * 2))

/* PKTENG Wx Stats Bwock */
#define M_WXSTATS_BWK_PTW	(M_PSM_SOFT_WEGS + (0x65 * 2))

/* ucode debug status codes */
/* not vawid weawwy */
#define	DBGST_INACTIVE		0
/* aftew zewoing SHM, befowe suspending at init */
#define	DBGST_INIT		1
/* "nowmaw" state */
#define	DBGST_ACTIVE		2
/* suspended */
#define	DBGST_SUSPENDED		3
/* asweep (PS mode) */
#define	DBGST_ASWEEP		4

/* Scwatch Weg defs */
enum _ePsmScwatchPadWegDefinitions {
	S_WSV0 = 0,
	S_WSV1,
	S_WSV2,

	/* offset 0x03: scwatch wegistews fow Dot11-contants */
	S_DOT11_CWMIN,		/* CW-minimum */
	S_DOT11_CWMAX,		/* CW-maximum */
	S_DOT11_CWCUW,		/* CW-cuwwent */
	S_DOT11_SWC_WMT,	/* showt wetwy count wimit */
	S_DOT11_WWC_WMT,	/* wong wetwy count wimit */
	S_DOT11_DTIMCOUNT,	/* DTIM-count */

	/* offset 0x09: Tx-side scwatch wegistews */
	S_SEQ_NUM,		/* hawdwawe sequence numbew weg */
	S_SEQ_NUM_FWAG,		/* seq num fow fwags (at the stawt of MSDU) */
	S_FWMWETX_CNT,		/* fwame wetx count */
	S_SSWC,			/* Station showt wetwy count */
	S_SWWC,			/* Station wong wetwy count */
	S_EXP_WSP,		/* Expected wesponse fwame */
	S_OWD_BWEM,		/* Wemaining backoff ctw */
	S_OWD_CWWIN,		/* saved-off CW-cuw */
	S_TXECTW,		/* TXE-Ctw wowd constwucted in scw-pad */
	S_CTXTST,		/* fwm type-subtype as wead fwom Tx-descw */

	/* offset 0x13: Wx-side scwatch wegistews */
	S_WXTST,		/* Type and subtype in Wxfwame */

	/* Gwobaw state wegistew */
	S_STWEG,		/* state stowage actuaw bit maps bewow */

	S_TXPWW_SUM,		/* Tx powew contwow: accumuwatow */
	S_TXPWW_ITEW,		/* Tx powew contwow: itewation */
	S_WX_FWMTYPE,		/* Wate and PHY type fow fwames */
	S_THIS_AGG,		/* Size of this AGG (A-MSDU) */

	S_KEYINDX,
	S_WXFWMWEN,		/* Weceive MPDU wength in bytes */

	/* offset 0x1B: Weceive TSF time stowed in SCW */
	S_WXTSFTMWVAW_WD3,	/* TSF vawue at the stawt of wx */
	S_WXTSFTMWVAW_WD2,	/* TSF vawue at the stawt of wx */
	S_WXTSFTMWVAW_WD1,	/* TSF vawue at the stawt of wx */
	S_WXTSFTMWVAW_WD0,	/* TSF vawue at the stawt of wx */
	S_WXSSN,		/* Weceived stawt seq numbew fow A-MPDU BA */
	S_WXQOSFWD,		/* Wx-QoS fiewd (if pwesent) */

	/* offset 0x21: Scwatch pad wegs used in micwocode as temp stowage */
	S_TMP0,			/* stmp0 */
	S_TMP1,			/* stmp1 */
	S_TMP2,			/* stmp2 */
	S_TMP3,			/* stmp3 */
	S_TMP4,			/* stmp4 */
	S_TMP5,			/* stmp5 */
	S_PWQPENAWTY_CTW,	/* Pwobe wesponse queue penawty countew */
	S_ANTCNT,		/* unsuccessfuw attempts on cuwwent ant. */
	S_SYMBOW,		/* fwag fow possibwe symbow ctw fwames */
	S_WXTP,			/* wx fwame type */
	S_STWEG2,		/* extwa state stowage */
	S_STWEG3,		/* even mowe extwa state stowage */
	S_STWEG4,		/* ... */
	S_STWEG5,		/* wemembew to initiawize it to zewo */

	S_ADJPWW_IDX,
	S_CUW_PTW,		/* Temp pointew fow A-MPDU we-Tx SHM tabwe */
	S_WEVID4,		/* 0x33 */
	S_INDX,			/* 0x34 */
	S_ADDW0,		/* 0x35 */
	S_ADDW1,		/* 0x36 */
	S_ADDW2,		/* 0x37 */
	S_ADDW3,		/* 0x38 */
	S_ADDW4,		/* 0x39 */
	S_ADDW5,		/* 0x3A */
	S_TMP6,			/* 0x3B */
	S_KEYINDX_BU,		/* Backup fow Key index */
	S_MFGTEST_TMP0,		/* Temp wegs used fow WX test cawcuwations */
	S_WXESN,		/* Weceived end sequence numbew fow A-MPDU BA */
	S_STWEG6,		/* 0x3F */
};

#define S_BEACON_INDX	S_OWD_BWEM
#define S_PWS_INDX	S_OWD_CWWIN
#define S_PHYTYPE	S_SSWC
#define S_PHYVEW	S_SWWC

/* IHW SWOW_CTWW vawues */
#define SWOW_CTWW_PDE		(1 << 0)
#define SWOW_CTWW_FD		(1 << 8)

/* ucode mac statistic countews in shawed memowy */
stwuct macstat {
	u16 txawwfwm;	/* 0x80 */
	u16 txwtsfwm;	/* 0x82 */
	u16 txctsfwm;	/* 0x84 */
	u16 txackfwm;	/* 0x86 */
	u16 txdnwfwm;	/* 0x88 */
	u16 txbcnfwm;	/* 0x8a */
	u16 txfunfw[8];	/* 0x8c - 0x9b */
	u16 txtpwunfw;	/* 0x9c */
	u16 txphyeww;	/* 0x9e */
	u16 pktengwxducast;	/* 0xa0 */
	u16 pktengwxdmcast;	/* 0xa2 */
	u16 wxfwmtoowong;	/* 0xa4 */
	u16 wxfwmtooshwt;	/* 0xa6 */
	u16 wxinvmachdw;	/* 0xa8 */
	u16 wxbadfcs;	/* 0xaa */
	u16 wxbadpwcp;	/* 0xac */
	u16 wxcwsgwitch;	/* 0xae */
	u16 wxstwt;		/* 0xb0 */
	u16 wxdfwmucastmbss;	/* 0xb2 */
	u16 wxmfwmucastmbss;	/* 0xb4 */
	u16 wxcfwmucast;	/* 0xb6 */
	u16 wxwtsucast;	/* 0xb8 */
	u16 wxctsucast;	/* 0xba */
	u16 wxackucast;	/* 0xbc */
	u16 wxdfwmocast;	/* 0xbe */
	u16 wxmfwmocast;	/* 0xc0 */
	u16 wxcfwmocast;	/* 0xc2 */
	u16 wxwtsocast;	/* 0xc4 */
	u16 wxctsocast;	/* 0xc6 */
	u16 wxdfwmmcast;	/* 0xc8 */
	u16 wxmfwmmcast;	/* 0xca */
	u16 wxcfwmmcast;	/* 0xcc */
	u16 wxbeaconmbss;	/* 0xce */
	u16 wxdfwmucastobss;	/* 0xd0 */
	u16 wxbeaconobss;	/* 0xd2 */
	u16 wxwsptmout;	/* 0xd4 */
	u16 bcntxcancw;	/* 0xd6 */
	u16 PAD;
	u16 wxf0ovfw;	/* 0xda */
	u16 wxf1ovfw;	/* 0xdc */
	u16 wxf2ovfw;	/* 0xde */
	u16 txsfovfw;	/* 0xe0 */
	u16 pmqovfw;		/* 0xe2 */
	u16 wxcgpwqfwm;	/* 0xe4 */
	u16 wxcgpwsqovfw;	/* 0xe6 */
	u16 txcgpwsfaiw;	/* 0xe8 */
	u16 txcgpwssuc;	/* 0xea */
	u16 pws_timeout;	/* 0xec */
	u16 wxnack;
	u16 fwmscons;
	u16 txnack;
	u16 txgwitch_nack;
	u16 txbuwst;		/* 0xf6 # tx buwsts */
	u16 bphy_wxcwsgwitch;	/* bphy wx cws gwitch */
	u16 phywatchdog;	/* 0xfa # of phy watchdog events */
	u16 PAD;
	u16 bphy_badpwcp;	/* bphy bad pwcp */
};

/* dot11 cowe-specific contwow fwags */
#define	SICF_PCWKE		0x0004	/* PHY cwock enabwe */
#define	SICF_PWST		0x0008	/* PHY weset */
#define	SICF_MPCWKE		0x0010	/* MAC PHY cwockcontwow enabwe */
#define	SICF_FWEF		0x0020	/* PWW FweqWefSewect */
/* NOTE: the fowwowing bw bits onwy appwy when the cowe is attached
 * to a NPHY
 */
#define	SICF_BWMASK		0x00c0	/* phy cwock mask (b6 & b7) */
#define	SICF_BW40		0x0080	/* 40MHz BW (160MHz phycwk) */
#define	SICF_BW20		0x0040	/* 20MHz BW (80MHz phycwk) */
#define	SICF_BW10		0x0000	/* 10MHz BW (40MHz phycwk) */
#define	SICF_GMODE		0x2000	/* gmode enabwe */

/* dot11 cowe-specific status fwags */
#define	SISF_2G_PHY		0x0001	/* 2.4G capabwe phy */
#define	SISF_5G_PHY		0x0002	/* 5G capabwe phy */
#define	SISF_FCWKA		0x0004	/* FastCwkAvaiwabwe */
#define	SISF_DB_PHY		0x0008	/* Duawband phy */

/* === End of MAC weg, Beginning of PHY(b/a/g/n) weg === */
/* wadio and WPPHY wegs awe sepawated */

#define	BPHY_WEG_OFT_BASE	0x0
/* offsets fow indiwect access to bphy wegistews */
#define	BPHY_BB_CONFIG		0x01
#define	BPHY_ADCBIAS		0x02
#define	BPHY_ANACOWE		0x03
#define	BPHY_PHYCWSTH		0x06
#define	BPHY_TEST		0x0a
#define	BPHY_PA_TX_TO		0x10
#define	BPHY_SYNTH_DC_TO	0x11
#define	BPHY_PA_TX_TIME_UP	0x12
#define	BPHY_WX_FWTW_TIME_UP	0x13
#define	BPHY_TX_POWEW_OVEWWIDE	0x14
#define	BPHY_WF_OVEWWIDE	0x15
#define	BPHY_WF_TW_WOOKUP1	0x16
#define	BPHY_WF_TW_WOOKUP2	0x17
#define	BPHY_COEFFS		0x18
#define	BPHY_PWW_OUT		0x19
#define	BPHY_WEFWESH_MAIN	0x1a
#define	BPHY_WEFWESH_TO0	0x1b
#define	BPHY_WEFWESH_TO1	0x1c
#define	BPHY_WSSI_TWESH		0x20
#define	BPHY_IQ_TWESH_HH	0x21
#define	BPHY_IQ_TWESH_H		0x22
#define	BPHY_IQ_TWESH_W		0x23
#define	BPHY_IQ_TWESH_WW	0x24
#define	BPHY_GAIN		0x25
#define	BPHY_WNA_GAIN_WANGE	0x26
#define	BPHY_JSSI		0x27
#define	BPHY_TSSI_CTW		0x28
#define	BPHY_TSSI		0x29
#define	BPHY_TW_WOSS_CTW	0x2a
#define	BPHY_WO_WEAKAGE		0x2b
#define	BPHY_WO_WSSI_ACC	0x2c
#define	BPHY_WO_IQMAG_ACC	0x2d
#define	BPHY_TX_DC_OFF1		0x2e
#define	BPHY_TX_DC_OFF2		0x2f
#define	BPHY_PEAK_CNT_THWESH	0x30
#define	BPHY_FWEQ_OFFSET	0x31
#define	BPHY_DIVEWSITY_CTW	0x32
#define	BPHY_PEAK_ENEWGY_WO	0x33
#define	BPHY_PEAK_ENEWGY_HI	0x34
#define	BPHY_SYNC_CTW		0x35
#define	BPHY_TX_PWW_CTWW	0x36
#define BPHY_TX_EST_PWW		0x37
#define	BPHY_STEP		0x38
#define	BPHY_WAWMUP		0x39
#define	BPHY_WMS_CFF_WEAD	0x3a
#define	BPHY_WMS_COEFF_I	0x3b
#define	BPHY_WMS_COEFF_Q	0x3c
#define	BPHY_SIG_POW		0x3d
#define	BPHY_WFDC_CANCEW_CTW	0x3e
#define	BPHY_HDW_TYPE		0x40
#define	BPHY_SFD_TO		0x41
#define	BPHY_SFD_CTW		0x42
#define	BPHY_DEBUG		0x43
#define	BPHY_WX_DEWAY_COMP	0x44
#define	BPHY_CWS_DWOP_TO	0x45
#define	BPHY_SHOWT_SFD_NZEWOS	0x46
#define	BPHY_DSSS_COEFF1	0x48
#define	BPHY_DSSS_COEFF2	0x49
#define	BPHY_CCK_COEFF1		0x4a
#define	BPHY_CCK_COEFF2		0x4b
#define	BPHY_TW_COWW		0x4c
#define	BPHY_ANGWE_SCAWE	0x4d
#define	BPHY_TX_PWW_BASE_IDX	0x4e
#define	BPHY_OPTIONAW_MODES2	0x4f
#define	BPHY_CCK_WMS_STEP	0x50
#define	BPHY_BYPASS		0x51
#define	BPHY_CCK_DEWAY_WONG	0x52
#define	BPHY_CCK_DEWAY_SHOWT	0x53
#define	BPHY_PPWOC_CHAN_DEWAY	0x54
#define	BPHY_DDFS_ENABWE	0x58
#define	BPHY_PHASE_SCAWE	0x59
#define	BPHY_FWEQ_CONTWOW	0x5a
#define	BPHY_WNA_GAIN_WANGE_10	0x5b
#define	BPHY_WNA_GAIN_WANGE_32	0x5c
#define	BPHY_OPTIONAW_MODES	0x5d
#define	BPHY_WX_STATUS2		0x5e
#define	BPHY_WX_STATUS3		0x5f
#define	BPHY_DAC_CONTWOW	0x60
#define	BPHY_ANA11G_FIWT_CTWW	0x62
#define	BPHY_WEFWESH_CTWW	0x64
#define	BPHY_WF_OVEWWIDE2	0x65
#define	BPHY_SPUW_CANCEW_CTWW	0x66
#define	BPHY_FINE_DIGIGAIN_CTWW	0x67
#define	BPHY_WSSI_WUT		0x88
#define	BPHY_WSSI_WUT_END	0xa7
#define	BPHY_TSSI_WUT		0xa8
#define	BPHY_TSSI_WUT_END	0xc7
#define	BPHY_TSSI2PWW_WUT	0x380
#define	BPHY_TSSI2PWW_WUT_END	0x39f
#define	BPHY_WOCOMP_WUT		0x3a0
#define	BPHY_WOCOMP_WUT_END	0x3bf
#define	BPHY_TXGAIN_WUT		0x3c0
#define	BPHY_TXGAIN_WUT_END	0x3ff

/* Bits in BB_CONFIG: */
#define	PHY_BBC_ANT_MASK	0x0180
#define	PHY_BBC_ANT_SHIFT	7
#define	BB_DAWWIN		0x1000
#define BBCFG_WESETCCA		0x4000
#define BBCFG_WESETWX		0x8000

/* Bits in phytest(0x0a): */
#define	TST_DDFS		0x2000
#define	TST_TXFIWT1		0x0800
#define	TST_UNSCWAM		0x0400
#define	TST_CAWW_SUPP		0x0200
#define	TST_DC_COMP_WOOP	0x0100
#define	TST_WOOPBACK		0x0080
#define	TST_TXFIWT0		0x0040
#define	TST_TXTEST_ENABWE	0x0020
#define	TST_TXTEST_WATE		0x0018
#define	TST_TXTEST_PHASE	0x0007

/* phytest txTestWate vawues */
#define	TST_TXTEST_WATE_1MBPS	0
#define	TST_TXTEST_WATE_2MBPS	1
#define	TST_TXTEST_WATE_5_5MBPS	2
#define	TST_TXTEST_WATE_11MBPS	3
#define	TST_TXTEST_WATE_SHIFT	3

#define SHM_BYT_CNT	0x2	/* IHW wocation */
#define MAX_BYT_CNT	0x600	/* Maximum fwame wen */

stwuct d11cnt {
	u32 txfwag;
	u32 txmuwti;
	u32 txfaiw;
	u32 txwetwy;
	u32 txwetwie;
	u32 wxdup;
	u32 txwts;
	u32 txnocts;
	u32 txnoack;
	u32 wxfwag;
	u32 wxmuwti;
	u32 wxcwc;
	u32 txfwmsnt;
	u32 wxundec;
};

#endif				/* _BWCM_D11_H_ */
