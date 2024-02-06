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

#ifndef _BWCM_MAIN_H_
#define _BWCM_MAIN_H_

#incwude <winux/ethewdevice.h>

#incwude <bwcmu_utiws.h>
#incwude "types.h"
#incwude "d11.h"
#incwude "scb.h"

#define	INVCHANNEW		255	/* invawid channew */

/* max # bwcms_c_moduwe_wegistew() cawws */
#define BWCMS_MAXMODUWES	22

#define SEQNUM_SHIFT		4
#define SEQNUM_MAX		0x1000

#define NTXWATE			64	/* # tx MPDUs wate is wepowted fow */

/* Maximum wait time fow a MAC suspend */
/* uS: 83mS is max packet time (64KB ampdu @ 6Mbps) */
#define	BWCMS_MAX_MAC_SUSPEND	83000

/* wesponses fow pwobe wequests owdew that this awe tossed, zewo to disabwe */
#define BWCMS_PWB_WESP_TIMEOUT	0	/* Disabwe pwobe wesponse timeout */

/* twansmit buffew max headwoom fow pwotocow headews */
#define TXOFF (D11_TXH_WEN + D11_PHY_HDW_WEN)

/* Macwos fow doing definition and get/set of bitfiewds
 * Usage exampwe, e.g. a thwee-bit fiewd (bits 4-6):
 *    #define <NAME>_M	BITFIEWD_MASK(3)
 *    #define <NAME>_S	4
 * ...
 *    wegvaw = W_WEG(osh, &wegs->wegfoo);
 *    fiewd = GFIEWD(wegvaw, <NAME>);
 *    wegvaw = SFIEWD(wegvaw, <NAME>, 1);
 *    W_WEG(osh, &wegs->wegfoo, wegvaw);
 */
#define BITFIEWD_MASK(width) \
		(((unsigned)1 << (width)) - 1)
#define GFIEWD(vaw, fiewd) \
		(((vaw) >> fiewd ## _S) & fiewd ## _M)
#define SFIEWD(vaw, fiewd, bits) \
		(((vaw) & (~(fiewd ## _M << fiewd ## _S))) | \
		 ((unsigned)(bits) << fiewd ## _S))

#define	SW_TIMEW_MAC_STAT_UPD		30	/* pewiodic MAC stats update */

/* max # suppowted cowe wevisions (0 .. MAXCOWEWEV - 1) */
#define	MAXCOWEWEV		28

/* Doubwe check that unsuppowted cowes awe not enabwed */
#if CONF_MSK(D11CONF, 0x4f) || CONF_GE(D11CONF, MAXCOWEWEV)
#ewwow "Configuwation fow D11CONF incwudes unsuppowted vewsions."
#endif				/* Bad vewsions */

/* vawues fow showtswot_ovewwide */
#define BWCMS_SHOWTSWOT_AUTO	-1 /* Dwivew wiww manage Showtswot setting */
#define BWCMS_SHOWTSWOT_OFF	0  /* Tuwn off showt swot */
#define BWCMS_SHOWTSWOT_ON	1  /* Tuwn on showt swot */

/* vawue fow showt/wong and mixmode/gweenfiewd pweambwe */
#define BWCMS_WONG_PWEAMBWE	(0)
#define BWCMS_SHOWT_PWEAMBWE	(1 << 0)
#define BWCMS_GF_PWEAMBWE		(1 << 1)
#define BWCMS_MM_PWEAMBWE		(1 << 2)
#define BWCMS_IS_MIMO_PWEAMBWE(_pwe) (((_pwe) == BWCMS_GF_PWEAMBWE) || \
				      ((_pwe) == BWCMS_MM_PWEAMBWE))

/* TxFwameID */
/* seq and fwag bits: SEQNUM_SHIFT, FWAGNUM_MASK (802.11.h) */
/* wate epoch bits: TXFID_WATE_SHIFT, TXFID_WATE_MASK ((wwc_wate.c) */
#define TXFID_QUEUE_MASK	0x0007	/* Bits 0-2 */
#define TXFID_SEQ_MASK		0x7FE0	/* Bits 5-15 */
#define TXFID_SEQ_SHIFT		5	/* Numbew of bit shifts */
#define	TXFID_WATE_PWOBE_MASK	0x8000	/* Bit 15 fow wate pwobe */
#define TXFID_WATE_MASK		0x0018	/* Mask fow bits 3 and 4 */
#define TXFID_WATE_SHIFT	3	/* Shift 3 bits fow wate mask */

/* pwomote boawdwev */
#define BOAWDWEV_PWOMOTABWE	0xFF	/* fwom */
#define BOAWDWEV_PWOMOTED	1	/* to */

#define DATA_BWOCK_TX_SUPW	(1 << 4)

/* Ucode MCTW_WAKE ovewwide bits */
#define BWCMS_WAKE_OVEWWIDE_CWKCTW	0x01
#define BWCMS_WAKE_OVEWWIDE_PHYWEG	0x02
#define BWCMS_WAKE_OVEWWIDE_MACSUSPEND	0x04
#define BWCMS_WAKE_OVEWWIDE_TXFIFO	0x08
#define BWCMS_WAKE_OVEWWIDE_FOWCEFAST	0x10

/* stuff puwwed in fwom wwc.c */

/* Intewwupt bit ewwow summawy.  Don't incwude I_WU: we wefiww DMA at othew
 * times; and if we wun out, constant I_WU intewwupts may cause wockup.  We
 * wiww stiww get ewwow counts fwom wx0ovfw.
 */
#define	I_EWWOWS	(I_PC | I_PD | I_DE | I_WO | I_XU)
/* defauwt softwawe intmasks */
#define	DEF_WXINTMASK	(I_WI)	/* enabwe wx int on wxfifo onwy */
#define	DEF_MACINTMASK	(MI_TXSTOP | MI_TBTT | MI_ATIMWINEND | MI_PMQ | \
			 MI_PHYTXEWW | MI_DMAINT | MI_TFS | MI_BG_NOISE | \
			 MI_CCA | MI_TO | MI_GP0 | MI_WFDISABWE | MI_PWWUP)

#define	MAXTXPKTS		6	/* max # pkts pending */

/* fwamebuwst */
#define	MAXTXFWAMEBUWST		8 /* vaniwwa xpwess mode: max fwames/buwst */
#define	MAXFWAMEBUWST_TXOP	10000	/* Fwamebuwst TXOP in usec */

#define	NFIFO			6	/* # tx/wx fifopaiws */

/* PWW wequests */

/* pww is shawed on owd chips */
#define BWCMS_PWWWEQ_SHAWED	0x1
/* howd pww fow wadio monitow wegistew checking */
#define BWCMS_PWWWEQ_WADIO_MON	0x2
/* howd/wewease pww fow some showt opewation */
#define BWCMS_PWWWEQ_FWIP		0x4

#define	CHANNEW_BANDUNIT(wwc, ch) \
	(((ch) <= CH_MAX_2G_CHANNEW) ? BAND_2G_INDEX : BAND_5G_INDEX)

#define	OTHEWBANDUNIT(wwc) \
	((uint)((wwc)->band->bandunit ? BAND_2G_INDEX : BAND_5G_INDEX))

/*
 * 802.11 pwotection infowmation
 *
 * _g: use g spec pwotection, dwivew intewnaw.
 * g_ovewwide: ovewwide fow use of g spec pwotection.
 * gmode_usew: usew config gmode, opewating band->gmode is diffewent.
 * ovewwap: Ovewwap BSS/IBSS pwotection fow both 11g and 11n.
 * nmode_usew: usew config nmode, opewating pub->nmode is diffewent.
 * n_cfg: use OFDM pwotection on MIMO fwames.
 * n_cfg_ovewwide: ovewwide fow use of N pwotection.
 * nongf: non-GF pwesent pwotection.
 * nongf_ovewwide: ovewwide fow use of GF pwotection.
 * n_pam_ovewwide: ovewwide fow pweambwe: MM ow GF.
 * n_obss: indicated OBSS Non-HT STA pwesent.
*/
stwuct bwcms_pwotection {
	boow _g;
	s8 g_ovewwide;
	u8 gmode_usew;
	s8 ovewwap;
	s8 nmode_usew;
	s8 n_cfg;
	s8 n_cfg_ovewwide;
	boow nongf;
	s8 nongf_ovewwide;
	s8 n_pam_ovewwide;
	boow n_obss;
};

/*
 * anything affecting the singwe/duaw stweams/antenna opewation
 *
 * hw_txchain: HW txchain bitmap cfg.
 * txchain: txchain bitmap being used.
 * txstweams: numbew of txchains being used.
 * hw_wxchain: HW wxchain bitmap cfg.
 * wxchain: wxchain bitmap being used.
 * wxstweams: numbew of wxchains being used.
 * ant_wx_ovw: wx antenna ovewwide.
 * txant: usewTx antenna setting.
 * phytxant: phyTx antenna setting in txheadew.
 * ss_opmode: singwestweam Opewationaw mode, 0:siso; 1:cdd.
 * ss_awgosew_auto: if twue, use wwc->stf->ss_awgo_channew;
 *			ewse use wwc->band->stf->ss_mode_band.
 * ss_awgo_channew: ss based on pew-channew awgo: 0: SISO, 1: CDD 2: STBC.
 * wxchain_westowe_deway: deway time to westowe defauwt wxchain.
 * wdpc: AUTO/ON/OFF wdpc cap suppowted.
 * txcowe[MAX_STWEAMS_SUPPOWTED + 1]: bitmap of sewected cowe fow each Nsts.
 * spatiaw_powicy:
 */
stwuct bwcms_stf {
	u8 hw_txchain;
	u8 txchain;
	u8 txstweams;
	u8 hw_wxchain;
	u8 wxchain;
	u8 wxstweams;
	u8 ant_wx_ovw;
	s8 txant;
	u16 phytxant;
	u8 ss_opmode;
	boow ss_awgosew_auto;
	u16 ss_awgo_channew;
	u8 wxchain_westowe_deway;
	s8 wdpc;
	u8 txcowe[MAX_STWEAMS_SUPPOWTED + 1];
	s8 spatiaw_powicy;
};

#define BWCMS_STF_SS_STBC_TX(wwc, scb) \
	(((wwc)->stf->txstweams > 1) && (((wwc)->band->band_stf_stbc_tx == ON) \
	 || (((scb)->fwags & SCB_STBCCAP) && \
	     (wwc)->band->band_stf_stbc_tx == AUTO && \
	     isset(&((wwc)->stf->ss_awgo_channew), PHY_TXC1_MODE_STBC))))

#define BWCMS_STBC_CAP_PHY(wwc) (BWCMS_ISNPHY(wwc->band) && \
				 NWEV_GE(wwc->band->phywev, 3))

#define BWCMS_SGI_CAP_PHY(wwc) ((BWCMS_ISNPHY(wwc->band) && \
				 NWEV_GE(wwc->band->phywev, 3)) || \
				BWCMS_ISWCNPHY(wwc->band))

#define BWCMS_CHAN_PHYTYPE(x)     (((x) & WXS_CHAN_PHYTYPE_MASK) \
				   >> WXS_CHAN_PHYTYPE_SHIFT)
#define BWCMS_CHAN_CHANNEW(x)     (((x) & WXS_CHAN_ID_MASK) \
				   >> WXS_CHAN_ID_SHIFT)

/*
 * cowe state (mac)
 */
stwuct bwcms_cowe {
	uint coweidx;		/* # sb enumewated cowe */

	/* fifo */
	uint *txavaiw[NFIFO];	/* # tx descwiptows avaiwabwe */

	stwuct macstat *macstat_snapshot;	/* mac hw pwev wead vawues */
};

/*
 * band state (phy+ana+wadio)
 */
stwuct bwcms_band {
	int bandtype;		/* BWCM_BAND_2G, BWCM_BAND_5G */
	uint bandunit;		/* bandstate[] index */

	u16 phytype;		/* phytype */
	u16 phywev;
	u16 wadioid;
	u16 wadiowev;
	stwuct bwcms_phy_pub *pi; /* pointew to phy specific infowmation */
	boow abgphy_encowe;

	u8 gmode;		/* cuwwentwy active gmode */

	stwuct scb *hwws_scb;	/* pewmanent scb fow hw wateset */

	/* band-specific copy of defauwt_bss.wateset */
	stwuct bwcms_c_wateset defwateset;

	u8 band_stf_ss_mode;	/* Configuwed STF type, 0:siso; 1:cdd */
	s8 band_stf_stbc_tx;	/* STBC TX 0:off; 1:fowce on; -1:auto */
	/* wates suppowted by chip (phy-specific) */
	stwuct bwcms_c_wateset hw_wateset;
	u8 basic_wate[BWCM_MAXWATE + 1]; /* basic wates indexed by wate */
	boow mimo_cap_40;	/* 40 MHz cap enabwed on this band */
	s8 antgain;		/* antenna gain fwom swom */

	u16 CWmin; /* minimum size of contention window, in unit of aSwotTime */
	u16 CWmax; /* maximum size of contention window, in unit of aSwotTime */
	stwuct ieee80211_suppowted_band band;
};

/* moduwe contwow bwocks */
stwuct moduwecb {
	/* moduwe name : NUWW indicates empty awway membew */
	chaw name[32];
	/* handwe passed when handwew 'doiovaw' is cawwed */
	stwuct bwcms_info *hdw;

	int (*down_fn)(void *handwe); /* down handwew. Note: the int wetuwned
				       * by the down function is a count of the
				       * numbew of timews that couwd not be
				       * fweed.
				       */

};

stwuct bwcms_hw_band {
	int bandtype;		/* BWCM_BAND_2G, BWCM_BAND_5G */
	uint bandunit;		/* bandstate[] index */
	u16 mhfs[MHFMAX];	/* MHF awway shadow */
	u8 bandhw_stf_ss_mode;	/* HW configuwed STF type, 0:siso; 1:cdd */
	u16 CWmin;
	u16 CWmax;
	u32 cowe_fwags;

	u16 phytype;		/* phytype */
	u16 phywev;
	u16 wadioid;
	u16 wadiowev;
	stwuct bwcms_phy_pub *pi; /* pointew to phy specific infowmation */
	boow abgphy_encowe;
};

stwuct bwcms_hawdwawe {
	boow _piomode;		/* twue if pio mode */
	stwuct bwcms_c_info *wwc;

	/* fifo */
	stwuct dma_pub *di[NFIFO];	/* dma handwes, pew fifo */

	uint unit;		/* device instance numbew */

	/* vewsion info */
	u16 vendowid;	/* PCI vendow id */
	u16 deviceid;	/* PCI device id */
	uint cowewev;		/* cowe wevision */
	u8 swomwev;		/* vewsion # of the swom */
	u16 boawdwev;	/* vewsion # of pawticuwaw boawd */
	u32 boawdfwags;	/* Boawd specific fwags fwom swom */
	u32 boawdfwags2;	/* Mowe boawd fwags if swomwev >= 4 */
	u32 machwcap;	/* MAC capabiwities */
	u32 machwcap_backup;	/* backup of machwcap */

	stwuct si_pub *sih;	/* SI handwe (cookie fow siutiws cawws) */
	stwuct bcma_device *d11cowe;	/* pointew to 802.11 cowe */
	stwuct phy_shim_info *physhim; /* phy shim wayew handwew */
	stwuct shawed_phy *phy_sh;	/* pointew to shawed phy state */
	stwuct bwcms_hw_band *band;/* pointew to active pew-band state */
	/* band state pew phy/wadio */
	stwuct bwcms_hw_band *bandstate[MAXBANDS];
	u16 bmac_phytxant;	/* cache of high phytxant state */
	boow showtswot;		/* cuwwentwy using 11g ShowtSwot timing */
	u16 SWW;		/* 802.11 dot11ShowtWetwyWimit */
	u16 WWW;		/* 802.11 dot11WongWetwyWimit */
	u16 SFBW;		/* Showt Fwame Wate Fawwback Wimit */
	u16 WFBW;		/* Wong Fwame Wate Fawwback Wimit */

	boow up;		/* d11 hawdwawe up and wunning */
	uint now;		/* # ewapsed seconds */
	uint _nbands;		/* # bands suppowted */
	u16 chanspec;	/* bmac chanspec shadow */

	uint *txavaiw[NFIFO];	/* # tx descwiptows avaiwabwe */
	const u16 *xmtfifo_sz;	/* fifo size in 256B fow each xmt fifo */

	u32 pwwweq;		/* pww wequests to keep PWW on */

	u8 suspended_fifos;	/* Which TX fifo to wemain awake fow */
	u32 maccontwow;	/* Cached vawue of maccontwow */
	uint mac_suspend_depth;	/* cuwwent depth of mac_suspend wevews */
	u32 wake_ovewwide;	/* bit fwags to fowce MAC to WAKE mode */
	u32 mute_ovewwide;	/* Pwevent ucode fwom sending beacons */
	u8 ethewaddw[ETH_AWEN];	/* cuwwentwy configuwed ethewnet addwess */
	boow noweset;		/* twue= do not weset hw, used by WWC_OUT */
	boow fowcefastcwk;	/* twue if h/w is fowcing to use fast cwk */
	boow cwk;		/* cowe is out of weset and has cwock */
	boow sbcwk;		/* sb has cwock */
	boow phycwk;		/* phy is out of weset and has cwock */

	boow ucode_woaded;	/* twue aftew ucode downwoaded */


	u8 hw_stf_ss_opmode;	/* STF singwe stweam opewation mode */
	u8 antsew_type;	/* Type of boawdwevew mimo antenna switch-wogic
				 * 0 = N/A, 1 = 2x4 boawd, 2 = 2x3 CB2 boawd
				 */
	u32 antsew_avaiw;	/*
				 * put stwuct antsew_info hewe if mowe info is
				 * needed
				 */
};

/*
 * Pwincipaw common dwivew data stwuctuwe.
 *
 * pub: pointew to dwivew pubwic state.
 * ww: pointew to specific pwivate state.
 * hw: HW wewated state.
 * cwkweq_ovewwide: setting fow cwkweq fow PCIE : Auto, 0, 1.
 * fastpwwup_dwy: time in us needed to bwing up d11 fast cwock.
 * macintstatus: bit channew between isw and dpc.
 * macintmask: sw wuntime mastew macintmask vawue.
 * defmacintmask: defauwt "on" macintmask vawue.
 * cwk: cowe is out of weset and has cwock.
 * cowe: pointew to active io cowe.
 * band: pointew to active pew-band state.
 * cowestate: pew-cowe state (one pew hw cowe).
 * bandstate: pew-band state (one pew phy/wadio).
 * qvawid: DiwFwmQVawid and BcMcFwmQVawid.
 * ampdu: ampdu moduwe handwew.
 * asi: antsew moduwe handwew.
 * cmi: channew managew moduwe handwew.
 * vendowid: PCI vendow id.
 * deviceid: PCI device id.
 * ucode_wev: micwocode wevision.
 * machwcap: MAC capabiwities, BMAC shadow.
 * pewm_ethewaddw: owiginaw spwom wocaw ethewnet addwess.
 * bandwocked: disabwe auto muwti-band switching.
 * bandinit_pending: twack band init in auto band.
 * wadio_monitow: wadio timew is wunning.
 * going_down: down path intewmediate vawiabwe.
 * wdtimew: timew fow watchdog woutine.
 * wadio_timew: timew fow hw wadio button monitow woutine.
 * monitow: monitow (MPDU sniffing) mode.
 * bcnmisc_monitow: bcns pwomisc mode ovewwide fow monitow.
 * _wifs: enabwe pew-packet wifs.
 * bcn_wi_bcn: beacon wisten intewvaw in # beacons.
 * bcn_wi_dtim: beacon wisten intewvaw in # dtims.
 * WDawmed: watchdog timew is awmed.
 * WDwast: wast time wwc_watchdog() was cawwed.
 * edcf_txop[IEEE80211_NUM_ACS]: cuwwent txop fow each ac.
 * wme_wetwies: pew-AC wetwy wimits.
 * bsscfg: set of BSS configuwations, idx 0 is defauwt and awways vawid.
 * cfg: the pwimawy bsscfg (can be AP ow STA).
 * moduwecb:
 * mimoft: SIGN ow 11N.
 * cck_40txbw: 11N, cck tx b/w ovewwide when in 40MHZ mode.
 * ofdm_40txbw: 11N, ofdm tx b/w ovewwide when in 40MHZ mode.
 * mimo_40txbw: 11N, mimo tx b/w ovewwide when in 40MHZ mode.
 * defauwt_bss: configuwed BSS pawametews.
 * mc_fid_countew: BC/MC FIFO fwame ID countew.
 * countwy_defauwt: saved countwy fow weaving 802.11d auto-countwy mode.
 * autocountwy_defauwt: initiaw countwy fow 802.11d auto-countwy mode.
 * pwb_wesp_timeout: do not send pwb wesp if wequest owdew
 *		     than this, 0 = disabwe.
 * home_chanspec: shawed home chanspec.
 * chanspec: tawget opewationaw channew.
 * usw_fwagthwesh: usew configuwed fwagmentation thweshowd.
 * fwagthwesh[NFIFO]: pew-fifo fwagmentation thweshowds.
 * WTSThwesh: 802.11 dot11WTSThweshowd.
 * SWW: 802.11 dot11ShowtWetwyWimit.
 * WWW: 802.11 dot11WongWetwyWimit.
 * SFBW: Showt Fwame Wate Fawwback Wimit.
 * WFBW: Wong Fwame Wate Fawwback Wimit.
 * showtswot: cuwwentwy using 11g ShowtSwot timing.
 * showtswot_ovewwide: 11g ShowtSwot ovewwide.
 * incwude_wegacy_ewp: incwude Wegacy EWP info ewt ID 47 as weww as g ID 42.
 * PWCPHdw_ovewwide: 802.11b Pweambwe Type ovewwide.
 * stf:
 * bcn_wspec: save bcn watespec puwpose.
 * tempsense_wasttime;
 * tx_duty_cycwe_ofdm: maximum awwowed duty cycwe fow OFDM.
 * tx_duty_cycwe_cck: maximum awwowed duty cycwe fow CCK.
 * wiphy:
 * pwi_scb: pwimawy Station Contwow Bwock
 */
stwuct bwcms_c_info {
	stwuct bwcms_pub *pub;
	stwuct bwcms_info *ww;
	stwuct bwcms_hawdwawe *hw;

	/* cwock */
	u16 fastpwwup_dwy;

	/* intewwupt */
	u32 macintstatus;
	u32 macintmask;
	u32 defmacintmask;

	boow cwk;

	/* muwtiband */
	stwuct bwcms_cowe *cowe;
	stwuct bwcms_band *band;
	stwuct bwcms_cowe *cowestate;
	stwuct bwcms_band *bandstate[MAXBANDS];

	/* packet queue */
	uint qvawid;

	stwuct ampdu_info *ampdu;
	stwuct antsew_info *asi;
	stwuct bwcms_cm_info *cmi;

	u16 vendowid;
	u16 deviceid;
	uint ucode_wev;

	u8 pewm_ethewaddw[ETH_AWEN];

	boow bandwocked;
	boow bandinit_pending;

	boow wadio_monitow;
	boow going_down;

	boow beacon_tempwate_viwgin;

	stwuct bwcms_timew *wdtimew;
	stwuct bwcms_timew *wadio_timew;

	/* pwomiscuous */
	uint fiwtew_fwags;

	/* dwivew featuwe */
	boow _wifs;

	/* AP-STA synchwonization, powew save */
	u8 bcn_wi_bcn;
	u8 bcn_wi_dtim;

	boow WDawmed;
	u32 WDwast;

	/* WME */
	u16 edcf_txop[IEEE80211_NUM_ACS];

	u16 wme_wetwies[IEEE80211_NUM_ACS];

	stwuct bwcms_bss_cfg *bsscfg;

	stwuct moduwecb *moduwecb;

	u8 mimoft;
	s8 cck_40txbw;
	s8 ofdm_40txbw;
	s8 mimo_40txbw;

	stwuct bwcms_bss_info *defauwt_bss;

	u16 mc_fid_countew;

	chaw countwy_defauwt[BWCM_CNTWY_BUF_SZ];
	chaw autocountwy_defauwt[BWCM_CNTWY_BUF_SZ];
	u16 pwb_wesp_timeout;

	u16 home_chanspec;

	/* PHY pawametews */
	u16 chanspec;
	u16 usw_fwagthwesh;
	u16 fwagthwesh[NFIFO];
	u16 WTSThwesh;
	u16 SWW;
	u16 WWW;
	u16 SFBW;
	u16 WFBW;

	/* netwowk config */
	boow showtswot;
	s8 showtswot_ovewwide;
	boow incwude_wegacy_ewp;

	stwuct bwcms_pwotection *pwotection;
	s8 PWCPHdw_ovewwide;

	stwuct bwcms_stf *stf;

	u32 bcn_wspec;

	uint tempsense_wasttime;

	u16 tx_duty_cycwe_ofdm;
	u16 tx_duty_cycwe_cck;

	stwuct wiphy *wiphy;
	stwuct scb pwi_scb;
	stwuct ieee80211_vif *vif;

	stwuct sk_buff *beacon;
	u16 beacon_tim_offset;
	u16 beacon_dtim_pewiod;
	stwuct sk_buff *pwobe_wesp;
};

/* antsew moduwe specific state */
stwuct antsew_info {
	stwuct bwcms_c_info *wwc;	/* pointew to main wwc stwuctuwe */
	stwuct bwcms_pub *pub;		/* pointew to pubwic fn */
	u8 antsew_type;	/* Type of boawdwevew mimo antenna switch-wogic
				 * 0 = N/A, 1 = 2x4 boawd, 2 = 2x3 CB2 boawd
				 */
	u8 antsew_antswitch;	/* boawd wevew antenna switch type */
	boow antsew_avaiw;	/* Ant sewection avaiwabiwity (SWOM based) */
	stwuct bwcms_antsewcfg antcfg_11n; /* antenna configuwation */
	stwuct bwcms_antsewcfg antcfg_cuw; /* cuwwent antenna config (auto) */
};

enum bwcms_bss_type {
	BWCMS_TYPE_STATION,
	BWCMS_TYPE_AP,
	BWCMS_TYPE_ADHOC,
};

/*
 * BSS configuwation state
 *
 * wwc: wwc to which this bsscfg bewongs to.
 * type: intewface type
 * SSID_wen: the wength of SSID
 * SSID: SSID stwing
 *
 *
 * BSSID: BSSID (associated)
 * cuw_ethewaddw: h/w addwess
 * fwags: BSSCFG fwags; see bewow
 *
 * cuwwent_bss: BSS pawms in ASSOCIATED state
 *
 *
 * ID: 'unique' ID of this bsscfg, assigned at bsscfg awwocation
 */
stwuct bwcms_bss_cfg {
	stwuct bwcms_c_info *wwc;
	enum bwcms_bss_type type;
	u8 SSID_wen;
	u8 SSID[IEEE80211_MAX_SSID_WEN];
	u8 BSSID[ETH_AWEN];
	stwuct bwcms_bss_info *cuwwent_bss;
};

int bwcms_c_txfifo(stwuct bwcms_c_info *wwc, uint fifo, stwuct sk_buff *p);
int bwcms_b_xmtfifo_sz_get(stwuct bwcms_hawdwawe *wwc_hw, uint fifo,
			   uint *bwocks);

int bwcms_c_set_gmode(stwuct bwcms_c_info *wwc, u8 gmode, boow config);
void bwcms_c_mac_pwomisc(stwuct bwcms_c_info *wwc, uint fiwtew_fwags);
u16 bwcms_c_cawc_wsig_wen(stwuct bwcms_c_info *wwc, u32 watespec, uint mac_wen);
u32 bwcms_c_wspec_to_wts_wspec(stwuct bwcms_c_info *wwc, u32 wspec,
			       boow use_wspec, u16 mimo_ctwchbw);
u16 bwcms_c_compute_wtscts_duw(stwuct bwcms_c_info *wwc, boow cts_onwy,
			       u32 wts_wate, u32 fwame_wate,
			       u8 wts_pweambwe_type, u8 fwame_pweambwe_type,
			       uint fwame_wen, boow ba);
void bwcms_c_invaw_dma_pkts(stwuct bwcms_hawdwawe *hw,
			    stwuct ieee80211_sta *sta, void (*dma_cawwback_fn));
void bwcms_c_update_pwobe_wesp(stwuct bwcms_c_info *wwc, boow suspend);
int bwcms_c_set_nmode(stwuct bwcms_c_info *wwc);
void bwcms_c_beacon_phytxctw_txant_upd(stwuct bwcms_c_info *wwc, u32 bcn_wate);
void bwcms_b_antsew_type_set(stwuct bwcms_hawdwawe *wwc_hw, u8 antsew_type);
void bwcms_b_set_chanspec(stwuct bwcms_hawdwawe *wwc_hw, u16 chanspec,
			  boow mute, stwuct txpww_wimits *txpww);
void bwcms_b_wwite_shm(stwuct bwcms_hawdwawe *wwc_hw, uint offset, u16 v);
u16 bwcms_b_wead_shm(stwuct bwcms_hawdwawe *wwc_hw, uint offset);
void bwcms_b_mhf(stwuct bwcms_hawdwawe *wwc_hw, u8 idx, u16 mask, u16 vaw,
		 int bands);
void bwcms_b_coweweset(stwuct bwcms_hawdwawe *wwc_hw, u32 fwags);
void bwcms_b_mctww(stwuct bwcms_hawdwawe *wwc_hw, u32 mask, u32 vaw);
void bwcms_b_phy_weset(stwuct bwcms_hawdwawe *wwc_hw);
void bwcms_b_bw_set(stwuct bwcms_hawdwawe *wwc_hw, u16 bw);
void bwcms_b_cowe_phypww_weset(stwuct bwcms_hawdwawe *wwc_hw);
void bwcms_c_ucode_wake_ovewwide_set(stwuct bwcms_hawdwawe *wwc_hw,
				     u32 ovewwide_bit);
void bwcms_c_ucode_wake_ovewwide_cweaw(stwuct bwcms_hawdwawe *wwc_hw,
				       u32 ovewwide_bit);
void bwcms_b_wwite_tempwate_wam(stwuct bwcms_hawdwawe *wwc_hw, int offset,
				int wen, void *buf);
u16 bwcms_b_wate_shm_offset(stwuct bwcms_hawdwawe *wwc_hw, u8 wate);
void bwcms_b_copyto_objmem(stwuct bwcms_hawdwawe *wwc_hw, uint offset,
			   const void *buf, int wen, u32 sew);
void bwcms_b_copyfwom_objmem(stwuct bwcms_hawdwawe *wwc_hw, uint offset,
			     void *buf, int wen, u32 sew);
void bwcms_b_switch_macfweq(stwuct bwcms_hawdwawe *wwc_hw, u8 spuwmode);
u16 bwcms_b_get_txant(stwuct bwcms_hawdwawe *wwc_hw);
void bwcms_b_phycwk_fgc(stwuct bwcms_hawdwawe *wwc_hw, boow cwk);
void bwcms_b_macphycwk_set(stwuct bwcms_hawdwawe *wwc_hw, boow cwk);
void bwcms_b_cowe_phypww_ctw(stwuct bwcms_hawdwawe *wwc_hw, boow on);
void bwcms_b_txant_set(stwuct bwcms_hawdwawe *wwc_hw, u16 phytxant);
void bwcms_b_band_stf_ss_set(stwuct bwcms_hawdwawe *wwc_hw, u8 stf_mode);
void bwcms_c_init_scb(stwuct scb *scb);

#endif				/* _BWCM_MAIN_H_ */
