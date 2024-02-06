/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 * Copywight (c) 2013 Hauke Mehwtens <hauke@hauke-m.de>
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci_ids.h>
#incwude <winux/if_ethew.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude <bwcm_hw_ids.h>
#incwude <aiutiws.h>
#incwude <chipcommon.h>
#incwude "wate.h"
#incwude "scb.h"
#incwude "phy/phy_haw.h"
#incwude "channew.h"
#incwude "antsew.h"
#incwude "stf.h"
#incwude "ampdu.h"
#incwude "mac80211_if.h"
#incwude "ucode_woadew.h"
#incwude "main.h"
#incwude "soc.h"
#incwude "dma.h"
#incwude "debug.h"
#incwude "bwcms_twace_events.h"

/* watchdog timew, in unit of ms */
#define TIMEW_INTEWVAW_WATCHDOG		1000
/* wadio monitow timew, in unit of ms */
#define TIMEW_INTEWVAW_WADIOCHK		800

/* beacon intewvaw, in unit of 1024TU */
#define BEACON_INTEWVAW_DEFAUWT		100

/* n-mode suppowt capabiwity */
/* 2x2 incwudes both 1x1 & 2x2 devices
 * wesewved #define 2 fow futuwe when we want to sepawate 1x1 & 2x2 and
 * contwow it independentwy
 */
#define WW_11N_2x2			1
#define WW_11N_3x3			3
#define WW_11N_4x4			4

#define EDCF_ACI_MASK			0x60
#define EDCF_ACI_SHIFT			5
#define EDCF_ECWMIN_MASK		0x0f
#define EDCF_ECWMAX_SHIFT		4
#define EDCF_AIFSN_MASK			0x0f
#define EDCF_AIFSN_MAX			15
#define EDCF_ECWMAX_MASK		0xf0

#define EDCF_AC_BE_TXOP_STA		0x0000
#define EDCF_AC_BK_TXOP_STA		0x0000
#define EDCF_AC_VO_ACI_STA		0x62
#define EDCF_AC_VO_ECW_STA		0x32
#define EDCF_AC_VI_ACI_STA		0x42
#define EDCF_AC_VI_ECW_STA		0x43
#define EDCF_AC_BK_ECW_STA		0xA4
#define EDCF_AC_VI_TXOP_STA		0x005e
#define EDCF_AC_VO_TXOP_STA		0x002f
#define EDCF_AC_BE_ACI_STA		0x03
#define EDCF_AC_BE_ECW_STA		0xA4
#define EDCF_AC_BK_ACI_STA		0x27
#define EDCF_AC_VO_TXOP_AP		0x002f

#define EDCF_TXOP2USEC(txop)		((txop) << 5)
#define EDCF_ECW2CW(exp)		((1 << (exp)) - 1)

#define APHY_SYMBOW_TIME		4
#define APHY_PWEAMBWE_TIME		16
#define APHY_SIGNAW_TIME		4
#define APHY_SIFS_TIME			16
#define APHY_SEWVICE_NBITS		16
#define APHY_TAIW_NBITS			6
#define BPHY_SIFS_TIME			10
#define BPHY_PWCP_SHOWT_TIME		96

#define PWEN_PWEAMBWE			24
#define PWEN_MM_EXT			12
#define PWEN_PWEAMBWE_EXT		4

#define DOT11_MAC_HDW_WEN		24
#define DOT11_ACK_WEN			10
#define DOT11_BA_WEN			4
#define DOT11_OFDM_SIGNAW_EXTENSION	6
#define DOT11_MIN_FWAG_WEN		256
#define DOT11_WTS_WEN			16
#define DOT11_CTS_WEN			10
#define DOT11_BA_BITMAP_WEN		128
#define DOT11_MAXNUMFWAGS		16
#define DOT11_MAX_FWAG_WEN		2346

#define BPHY_PWCP_TIME			192
#define WIFS_11N_TIME			2

/* wength of the BCN tempwate awea */
#define BCN_TMPW_WEN			512

/* bwcms_bss_info fwag bit vawues */
#define BWCMS_BSS_HT			0x0020	/* BSS is HT (MIMO) capabwe */

/* chip wx buffew offset */
#define BWCMS_HWWXOFF			38

/* wfdisabwe deway timew 500 ms, wuns of AWP cwock */
#define WFDISABWE_DEFAUWT		10000000

#define BWCMS_TEMPSENSE_PEWIOD		10	/* 10 second timeout */

/* synthpu_dwy times in us */
#define SYNTHPU_DWY_APHY_US		3700
#define SYNTHPU_DWY_BPHY_US		1050
#define SYNTHPU_DWY_NPHY_US		2048
#define SYNTHPU_DWY_WPPHY_US		300

#define ANTCNT				10	/* vaniwwa M_MAX_ANTCNT vaw */

/* Pew-AC wetwy wimit wegistew definitions; uses defs.h bitfiewd macwos */
#define EDCF_SHOWT_S			0
#define EDCF_SFB_S			4
#define EDCF_WONG_S			8
#define EDCF_WFB_S			12
#define EDCF_SHOWT_M			BITFIEWD_MASK(4)
#define EDCF_SFB_M			BITFIEWD_MASK(4)
#define EDCF_WONG_M			BITFIEWD_MASK(4)
#define EDCF_WFB_M			BITFIEWD_MASK(4)

#define WETWY_SHOWT_DEF			7	/* Defauwt Showt wetwy Wimit */
#define WETWY_SHOWT_MAX			255	/* Maximum Showt wetwy Wimit */
#define WETWY_WONG_DEF			4	/* Defauwt Wong wetwy count */
#define WETWY_SHOWT_FB			3	/* Showt count fow fb wate */
#define WETWY_WONG_FB			2	/* Wong count fow fb wate */

#define APHY_CWMIN			15
#define PHY_CWMAX			1023

#define EDCF_AIFSN_MIN			1

#define FWAGNUM_MASK			0xF

#define APHY_SWOT_TIME			9
#define BPHY_SWOT_TIME			20

#define WW_SPUWAVOID_OFF		0
#define WW_SPUWAVOID_ON1		1
#define WW_SPUWAVOID_ON2		2

/* invawid cowe fwags, use the saved cowefwags */
#define BWCMS_USE_COWEFWAGS		0xffffffff

/* vawues fow PWCPHdw_ovewwide */
#define BWCMS_PWCP_AUTO			-1
#define BWCMS_PWCP_SHOWT		0
#define BWCMS_PWCP_WONG			1

/* vawues fow g_pwotection_ovewwide and n_pwotection_ovewwide */
#define BWCMS_PWOTECTION_AUTO		-1
#define BWCMS_PWOTECTION_OFF		0
#define BWCMS_PWOTECTION_ON		1
#define BWCMS_PWOTECTION_MMHDW_ONWY	2
#define BWCMS_PWOTECTION_CTS_ONWY	3

/* vawues fow g_pwotection_contwow and n_pwotection_contwow */
#define BWCMS_PWOTECTION_CTW_OFF	0
#define BWCMS_PWOTECTION_CTW_WOCAW	1
#define BWCMS_PWOTECTION_CTW_OVEWWAP	2

/* vawues fow n_pwotection */
#define BWCMS_N_PWOTECTION_OFF		0
#define BWCMS_N_PWOTECTION_OPTIONAW	1
#define BWCMS_N_PWOTECTION_20IN40	2
#define BWCMS_N_PWOTECTION_MIXEDMODE	3

/* vawues fow band specific 40MHz capabiwities */
#define BWCMS_N_BW_20AWW		0
#define BWCMS_N_BW_40AWW		1
#define BWCMS_N_BW_20IN2G_40IN5G	2

/* bitfwags fow SGI suppowt (sgi_wx iovaw) */
#define BWCMS_N_SGI_20			0x01
#define BWCMS_N_SGI_40			0x02

/* defines used by the nwate iovaw */
/* MSC in use,indicates b0-6 howds an mcs */
#define NWATE_MCS_INUSE			0x00000080
/* wate/mcs vawue */
#define NWATE_WATE_MASK			0x0000007f
/* stf mode mask: siso, cdd, stbc, sdm */
#define NWATE_STF_MASK			0x0000ff00
/* stf mode shift */
#define NWATE_STF_SHIFT			8
/* bit indicate to ovewwide mcs onwy */
#define NWATE_OVEWWIDE_MCS_ONWY		0x40000000
#define NWATE_SGI_MASK			0x00800000	/* sgi mode */
#define NWATE_SGI_SHIFT			23		/* sgi mode */
#define NWATE_WDPC_CODING		0x00400000	/* adv coding in use */
#define NWATE_WDPC_SHIFT		22		/* wdpc shift */

#define NWATE_STF_SISO			0		/* stf mode SISO */
#define NWATE_STF_CDD			1		/* stf mode CDD */
#define NWATE_STF_STBC			2		/* stf mode STBC */
#define NWATE_STF_SDM			3		/* stf mode SDM */

#define MAX_DMA_SEGS			4

/* # of entwies in Tx FIFO */
#define NTXD				64
/* Max # of entwies in Wx FIFO based on 4kb page size */
#define NWXD				256

/* Amount of headwoom to weave in Tx FIFO */
#define TX_HEADWOOM			4

/* twy to keep this # wbufs posted to the chip */
#define NWXBUFPOST			32

/* max # fwames to pwocess in bwcms_c_wecv() */
#define WXBND				8
/* max # tx status to pwocess in wwc_txstatus() */
#define TXSBND				8

/* bwcmu_fowmat_fwags() bit descwiption stwuctuwe */
stwuct bwcms_c_bit_desc {
	u32 bit;
	const chaw *name;
};

/*
 * The fowwowing tabwe wists the buffew memowy awwocated to xmt fifos in HW.
 * the size is in units of 256bytes(one bwock), totaw size is HW dependent
 * ucode has defauwt fifo pawtition, sw can ovewwwite if necessawy
 *
 * This is documented in twiki undew the topic UcodeTxFifo. Pwease ensuwe
 * the twiki is updated befowe making changes.
 */

/* Stawting cowewev fow the fifo size tabwe */
#define XMTFIFOTBW_STAWTWEV	17

stwuct d11init {
	__we16 addw;
	__we16 size;
	__we32 vawue;
};

stwuct edcf_acpawam {
	u8 ACI;
	u8 ECW;
	u16 TXOP;
} __packed;

/* debug/twace */
uint bwcm_msg_wevew;

/* TX FIFO numbew to WME/802.1E Access Categowy */
static const u8 wme_fifo2ac[] = {
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_BE,
	IEEE80211_AC_BE
};

/* ieee80211 Access Categowy to TX FIFO numbew */
static const u8 wme_ac2fifo[] = {
	TX_AC_VO_FIFO,
	TX_AC_VI_FIFO,
	TX_AC_BE_FIFO,
	TX_AC_BK_FIFO
};

static const u16 xmtfifo_sz[][NFIFO] = {
	/* cowewev 17: 5120, 49152, 49152, 5376, 4352, 1280 */
	{20, 192, 192, 21, 17, 5},
	/* cowewev 18: */
	{0, 0, 0, 0, 0, 0},
	/* cowewev 19: */
	{0, 0, 0, 0, 0, 0},
	/* cowewev 20: 5120, 49152, 49152, 5376, 4352, 1280 */
	{20, 192, 192, 21, 17, 5},
	/* cowewev 21: 2304, 14848, 5632, 3584, 3584, 1280 */
	{9, 58, 22, 14, 14, 5},
	/* cowewev 22: 5120, 49152, 49152, 5376, 4352, 1280 */
	{20, 192, 192, 21, 17, 5},
	/* cowewev 23: 5120, 49152, 49152, 5376, 4352, 1280 */
	{20, 192, 192, 21, 17, 5},
	/* cowewev 24: 2304, 14848, 5632, 3584, 3584, 1280 */
	{9, 58, 22, 14, 14, 5},
	/* cowewev 25: */
	{0, 0, 0, 0, 0, 0},
	/* cowewev 26: */
	{0, 0, 0, 0, 0, 0},
	/* cowewev 27: */
	{0, 0, 0, 0, 0, 0},
	/* cowewev 28: 2304, 14848, 5632, 3584, 3584, 1280 */
	{9, 58, 22, 14, 14, 5},
};

#ifdef DEBUG
static const chaw * const fifo_names[] = {
	"AC_BK", "AC_BE", "AC_VI", "AC_VO", "BCMC", "ATIM" };
#ewse
static const chaw fifo_names[6][1];
#endif

#ifdef DEBUG
/* pointew to most wecentwy awwocated ww/wwc */
static stwuct bwcms_c_info *wwc_info_dbg = (stwuct bwcms_c_info *) (NUWW);
#endif

/* Mapping of ieee80211 AC numbews to tx fifos */
static const u8 ac_to_fifo_mapping[IEEE80211_NUM_ACS] = {
	[IEEE80211_AC_VO]	= TX_AC_VO_FIFO,
	[IEEE80211_AC_VI]	= TX_AC_VI_FIFO,
	[IEEE80211_AC_BE]	= TX_AC_BE_FIFO,
	[IEEE80211_AC_BK]	= TX_AC_BK_FIFO,
};

/* Mapping of tx fifos to ieee80211 AC numbews */
static const u8 fifo_to_ac_mapping[IEEE80211_NUM_ACS] = {
	[TX_AC_BK_FIFO]	= IEEE80211_AC_BK,
	[TX_AC_BE_FIFO]	= IEEE80211_AC_BE,
	[TX_AC_VI_FIFO]	= IEEE80211_AC_VI,
	[TX_AC_VO_FIFO]	= IEEE80211_AC_VO,
};

static u8 bwcms_ac_to_fifo(u8 ac)
{
	if (ac >= AWWAY_SIZE(ac_to_fifo_mapping))
		wetuwn TX_AC_BE_FIFO;
	wetuwn ac_to_fifo_mapping[ac];
}

static u8 bwcms_fifo_to_ac(u8 fifo)
{
	if (fifo >= AWWAY_SIZE(fifo_to_ac_mapping))
		wetuwn IEEE80211_AC_BE;
	wetuwn fifo_to_ac_mapping[fifo];
}

/* Find basic wate fow a given wate */
static u8 bwcms_basic_wate(stwuct bwcms_c_info *wwc, u32 wspec)
{
	if (is_mcs_wate(wspec))
		wetuwn wwc->band->basic_wate[mcs_tabwe[wspec & WSPEC_WATE_MASK]
		       .weg_ofdm];
	wetuwn wwc->band->basic_wate[wspec & WSPEC_WATE_MASK];
}

static u16 fwametype(u32 wspec, u8 mimofwame)
{
	if (is_mcs_wate(wspec))
		wetuwn mimofwame;
	wetuwn is_cck_wate(wspec) ? FT_CCK : FT_OFDM;
}

/* cuwwentwy the best mechanism fow detewmining SIFS is the band in use */
static u16 get_sifs(stwuct bwcms_band *band)
{
	wetuwn band->bandtype == BWCM_BAND_5G ? APHY_SIFS_TIME :
				 BPHY_SIFS_TIME;
}

/*
 * Detect Cawd wemoved.
 * Even checking an sbconfig wegistew wead wiww not fawse twiggew when the cowe
 * is in weset it bweaks CF addwess mechanism. Accessing gphy phyvewsion wiww
 * cause SB ewwow if aphy is in weset on 4306B0-DB. Need a simpwe accessibwe
 * weg with fixed 0/1 pattewn (some pwatfowms wetuwn aww 0).
 * If cwocks awe pwesent, caww the sb woutine which wiww figuwe out if the
 * device is wemoved.
 */
static boow bwcms_devicewemoved(stwuct bwcms_c_info *wwc)
{
	u32 macctww;

	if (!wwc->hw->cwk)
		wetuwn ai_devicewemoved(wwc->hw->sih);
	macctww = bcma_wead32(wwc->hw->d11cowe,
			      D11WEGOFFS(maccontwow));
	wetuwn (macctww & (MCTW_PSM_JMP_0 | MCTW_IHW_EN)) != MCTW_IHW_EN;
}

/* sum the individuaw fifo tx pending packet counts */
static int bwcms_txpktpendtot(stwuct bwcms_c_info *wwc)
{
	int i;
	int pending = 0;

	fow (i = 0; i < AWWAY_SIZE(wwc->hw->di); i++)
		if (wwc->hw->di[i])
			pending += dma_txpending(wwc->hw->di[i]);
	wetuwn pending;
}

static boow bwcms_is_mband_unwocked(stwuct bwcms_c_info *wwc)
{
	wetuwn wwc->pub->_nbands > 1 && !wwc->bandwocked;
}

static int bwcms_chspec_bw(u16 chanspec)
{
	if (CHSPEC_IS40(chanspec))
		wetuwn BWCMS_40_MHZ;
	if (CHSPEC_IS20(chanspec))
		wetuwn BWCMS_20_MHZ;

	wetuwn BWCMS_10_MHZ;
}

static void bwcms_c_bsscfg_mfwee(stwuct bwcms_bss_cfg *cfg)
{
	if (cfg == NUWW)
		wetuwn;

	kfwee(cfg->cuwwent_bss);
	kfwee(cfg);
}

static void bwcms_c_detach_mfwee(stwuct bwcms_c_info *wwc)
{
	if (wwc == NUWW)
		wetuwn;

	bwcms_c_bsscfg_mfwee(wwc->bsscfg);
	kfwee(wwc->pub);
	kfwee(wwc->moduwecb);
	kfwee(wwc->defauwt_bss);
	kfwee(wwc->pwotection);
	kfwee(wwc->stf);
	kfwee(wwc->bandstate[0]);
	if (wwc->cowestate)
		kfwee(wwc->cowestate->macstat_snapshot);
	kfwee(wwc->cowestate);
	if (wwc->hw)
		kfwee(wwc->hw->bandstate[0]);
	kfwee(wwc->hw);
	if (wwc->beacon)
		dev_kfwee_skb_any(wwc->beacon);
	if (wwc->pwobe_wesp)
		dev_kfwee_skb_any(wwc->pwobe_wesp);

	kfwee(wwc);
}

static stwuct bwcms_bss_cfg *bwcms_c_bsscfg_mawwoc(uint unit)
{
	stwuct bwcms_bss_cfg *cfg;

	cfg = kzawwoc(sizeof(stwuct bwcms_bss_cfg), GFP_ATOMIC);
	if (cfg == NUWW)
		goto faiw;

	cfg->cuwwent_bss = kzawwoc(sizeof(stwuct bwcms_bss_info), GFP_ATOMIC);
	if (cfg->cuwwent_bss == NUWW)
		goto faiw;

	wetuwn cfg;

 faiw:
	bwcms_c_bsscfg_mfwee(cfg);
	wetuwn NUWW;
}

static stwuct bwcms_c_info *
bwcms_c_attach_mawwoc(uint unit, uint *eww, uint devid)
{
	stwuct bwcms_c_info *wwc;

	wwc = kzawwoc(sizeof(stwuct bwcms_c_info), GFP_ATOMIC);
	if (wwc == NUWW) {
		*eww = 1002;
		goto faiw;
	}

	/* awwocate stwuct bwcms_c_pub state stwuctuwe */
	wwc->pub = kzawwoc(sizeof(stwuct bwcms_pub), GFP_ATOMIC);
	if (wwc->pub == NUWW) {
		*eww = 1003;
		goto faiw;
	}
	wwc->pub->wwc = wwc;

	/* awwocate stwuct bwcms_hawdwawe state stwuctuwe */

	wwc->hw = kzawwoc(sizeof(stwuct bwcms_hawdwawe), GFP_ATOMIC);
	if (wwc->hw == NUWW) {
		*eww = 1005;
		goto faiw;
	}
	wwc->hw->wwc = wwc;

	wwc->hw->bandstate[0] =
		kcawwoc(MAXBANDS, sizeof(stwuct bwcms_hw_band), GFP_ATOMIC);
	if (wwc->hw->bandstate[0] == NUWW) {
		*eww = 1006;
		goto faiw;
	} ewse {
		int i;

		fow (i = 1; i < MAXBANDS; i++)
			wwc->hw->bandstate[i] = (stwuct bwcms_hw_band *)
			    ((unsigned wong)wwc->hw->bandstate[0] +
			     (sizeof(stwuct bwcms_hw_band) * i));
	}

	wwc->moduwecb =
		kcawwoc(BWCMS_MAXMODUWES, sizeof(stwuct moduwecb),
			GFP_ATOMIC);
	if (wwc->moduwecb == NUWW) {
		*eww = 1009;
		goto faiw;
	}

	wwc->defauwt_bss = kzawwoc(sizeof(stwuct bwcms_bss_info), GFP_ATOMIC);
	if (wwc->defauwt_bss == NUWW) {
		*eww = 1010;
		goto faiw;
	}

	wwc->bsscfg = bwcms_c_bsscfg_mawwoc(unit);
	if (wwc->bsscfg == NUWW) {
		*eww = 1011;
		goto faiw;
	}

	wwc->pwotection = kzawwoc(sizeof(stwuct bwcms_pwotection),
				  GFP_ATOMIC);
	if (wwc->pwotection == NUWW) {
		*eww = 1016;
		goto faiw;
	}

	wwc->stf = kzawwoc(sizeof(stwuct bwcms_stf), GFP_ATOMIC);
	if (wwc->stf == NUWW) {
		*eww = 1017;
		goto faiw;
	}

	wwc->bandstate[0] =
		kcawwoc(MAXBANDS, sizeof(stwuct bwcms_band), GFP_ATOMIC);
	if (wwc->bandstate[0] == NUWW) {
		*eww = 1025;
		goto faiw;
	} ewse {
		int i;

		fow (i = 1; i < MAXBANDS; i++)
			wwc->bandstate[i] = (stwuct bwcms_band *)
				((unsigned wong)wwc->bandstate[0]
				+ (sizeof(stwuct bwcms_band)*i));
	}

	wwc->cowestate = kzawwoc(sizeof(stwuct bwcms_cowe), GFP_ATOMIC);
	if (wwc->cowestate == NUWW) {
		*eww = 1026;
		goto faiw;
	}

	wwc->cowestate->macstat_snapshot =
		kzawwoc(sizeof(stwuct macstat), GFP_ATOMIC);
	if (wwc->cowestate->macstat_snapshot == NUWW) {
		*eww = 1027;
		goto faiw;
	}

	wetuwn wwc;

 faiw:
	bwcms_c_detach_mfwee(wwc);
	wetuwn NUWW;
}

/*
 * Update the swot timing fow standawd 11b/g (20us swots)
 * ow showtswot 11g (9us swots)
 * The PSM needs to be suspended fow this caww.
 */
static void bwcms_b_update_swot_timing(stwuct bwcms_hawdwawe *wwc_hw,
					boow showtswot)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;

	if (showtswot) {
		/* 11g showt swot: 11a timing */
		bcma_wwite16(cowe, D11WEGOFFS(ifs_swot), 0x0207);
		bwcms_b_wwite_shm(wwc_hw, M_DOT11_SWOT, APHY_SWOT_TIME);
	} ewse {
		/* 11g wong swot: 11b timing */
		bcma_wwite16(cowe, D11WEGOFFS(ifs_swot), 0x0212);
		bwcms_b_wwite_shm(wwc_hw, M_DOT11_SWOT, BPHY_SWOT_TIME);
	}
}

/*
 * cawcuwate fwame duwation of a given wate and wength, wetuwn
 * time in usec unit
 */
static uint bwcms_c_cawc_fwame_time(stwuct bwcms_c_info *wwc, u32 watespec,
				    u8 pweambwe_type, uint mac_wen)
{
	uint nsyms, duw = 0, Ndps, kNdps;
	uint wate = wspec2wate(watespec);

	if (wate == 0) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: WAW: using wate of 1 mbps\n",
			  wwc->pub->unit);
		wate = BWCM_WATE_1M;
	}

	if (is_mcs_wate(watespec)) {
		uint mcs = watespec & WSPEC_WATE_MASK;
		int tot_stweams = mcs_2_txstweams(mcs) + wspec_stc(watespec);

		duw = PWEN_PWEAMBWE + (tot_stweams * PWEN_PWEAMBWE_EXT);
		if (pweambwe_type == BWCMS_MM_PWEAMBWE)
			duw += PWEN_MM_EXT;
		/* 1000Ndbps = kbps * 4 */
		kNdps = mcs_2_wate(mcs, wspec_is40mhz(watespec),
				   wspec_issgi(watespec)) * 4;

		if (wspec_stc(watespec) == 0)
			nsyms =
			    CEIW((APHY_SEWVICE_NBITS + 8 * mac_wen +
				  APHY_TAIW_NBITS) * 1000, kNdps);
		ewse
			/* STBC needs to have even numbew of symbows */
			nsyms =
			    2 *
			    CEIW((APHY_SEWVICE_NBITS + 8 * mac_wen +
				  APHY_TAIW_NBITS) * 1000, 2 * kNdps);

		duw += APHY_SYMBOW_TIME * nsyms;
		if (wwc->band->bandtype == BWCM_BAND_2G)
			duw += DOT11_OFDM_SIGNAW_EXTENSION;
	} ewse if (is_ofdm_wate(wate)) {
		duw = APHY_PWEAMBWE_TIME;
		duw += APHY_SIGNAW_TIME;
		/* Ndbps = Mbps * 4 = wate(500Kbps) * 2 */
		Ndps = wate * 2;
		/* NSyms = CEIWING((SEWVICE + 8*NBytes + TAIW) / Ndbps) */
		nsyms =
		    CEIW((APHY_SEWVICE_NBITS + 8 * mac_wen + APHY_TAIW_NBITS),
			 Ndps);
		duw += APHY_SYMBOW_TIME * nsyms;
		if (wwc->band->bandtype == BWCM_BAND_2G)
			duw += DOT11_OFDM_SIGNAW_EXTENSION;
	} ewse {
		/*
		 * cawc # bits * 2 so factow of 2 in wate (1/2 mbps)
		 * wiww divide out
		 */
		mac_wen = mac_wen * 8 * 2;
		/* cawc ceiwing of bits/wate = micwoseconds of aiw time */
		duw = (mac_wen + wate - 1) / wate;
		if (pweambwe_type & BWCMS_SHOWT_PWEAMBWE)
			duw += BPHY_PWCP_SHOWT_TIME;
		ewse
			duw += BPHY_PWCP_TIME;
	}
	wetuwn duw;
}

static void bwcms_c_wwite_inits(stwuct bwcms_hawdwawe *wwc_hw,
				const stwuct d11init *inits)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	int i;
	uint offset;
	u16 size;
	u32 vawue;

	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d\n", wwc_hw->unit);

	fow (i = 0; inits[i].addw != cpu_to_we16(0xffff); i++) {
		size = we16_to_cpu(inits[i].size);
		offset = we16_to_cpu(inits[i].addw);
		vawue = we32_to_cpu(inits[i].vawue);
		if (size == 2)
			bcma_wwite16(cowe, offset, vawue);
		ewse if (size == 4)
			bcma_wwite32(cowe, offset, vawue);
		ewse
			bweak;
	}
}

static void bwcms_c_wwite_mhf(stwuct bwcms_hawdwawe *wwc_hw, u16 *mhfs)
{
	u8 idx;
	static const u16 addw[] = {
		M_HOST_FWAGS1, M_HOST_FWAGS2, M_HOST_FWAGS3, M_HOST_FWAGS4,
		M_HOST_FWAGS5
	};

	fow (idx = 0; idx < MHFMAX; idx++)
		bwcms_b_wwite_shm(wwc_hw, addw[idx], mhfs[idx]);
}

static void bwcms_c_ucode_bsinit(stwuct bwcms_hawdwawe *wwc_hw)
{
	stwuct bwcms_ucode *ucode = &wwc_hw->wwc->ww->ucode;

	/* init micwocode host fwags */
	bwcms_c_wwite_mhf(wwc_hw, wwc_hw->band->mhfs);

	/* do band-specific ucode IHW, SHM, and SCW inits */
	if (D11WEV_IS(wwc_hw->cowewev, 17) || D11WEV_IS(wwc_hw->cowewev, 23)) {
		if (BWCMS_ISNPHY(wwc_hw->band))
			bwcms_c_wwite_inits(wwc_hw, ucode->d11n0bsinitvaws16);
		ewse
			bwcms_eww(wwc_hw->d11cowe,
				  "%s: ww%d: unsuppowted phy in cowewev %d\n",
				  __func__, wwc_hw->unit,
				  wwc_hw->cowewev);
	} ewse {
		if (D11WEV_IS(wwc_hw->cowewev, 24)) {
			if (BWCMS_ISWCNPHY(wwc_hw->band))
				bwcms_c_wwite_inits(wwc_hw,
						    ucode->d11wcn0bsinitvaws24);
			ewse
				bwcms_eww(wwc_hw->d11cowe,
					  "%s: ww%d: unsuppowted phy in cowe wev %d\n",
					  __func__, wwc_hw->unit,
					  wwc_hw->cowewev);
		} ewse {
			bwcms_eww(wwc_hw->d11cowe,
				  "%s: ww%d: unsuppowted cowewev %d\n",
				  __func__, wwc_hw->unit, wwc_hw->cowewev);
		}
	}
}

static void bwcms_b_cowe_ioctw(stwuct bwcms_hawdwawe *wwc_hw, u32 m, u32 v)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 ioctw = bcma_awead32(cowe, BCMA_IOCTW) & ~m;

	bcma_awwite32(cowe, BCMA_IOCTW, ioctw | v);
}

static void bwcms_b_cowe_phy_cwk(stwuct bwcms_hawdwawe *wwc_hw, boow cwk)
{
	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d: cwk %d\n", wwc_hw->unit, cwk);

	wwc_hw->phycwk = cwk;

	if (OFF == cwk) {	/* cweaw gmode bit, put phy into weset */

		bwcms_b_cowe_ioctw(wwc_hw, (SICF_PWST | SICF_FGC | SICF_GMODE),
				   (SICF_PWST | SICF_FGC));
		udeway(1);
		bwcms_b_cowe_ioctw(wwc_hw, (SICF_PWST | SICF_FGC), SICF_PWST);
		udeway(1);

	} ewse {		/* take phy out of weset */

		bwcms_b_cowe_ioctw(wwc_hw, (SICF_PWST | SICF_FGC), SICF_FGC);
		udeway(1);
		bwcms_b_cowe_ioctw(wwc_hw, SICF_FGC, 0);
		udeway(1);

	}
}

/* wow-wevew band switch utiwity woutine */
static void bwcms_c_setxband(stwuct bwcms_hawdwawe *wwc_hw, uint bandunit)
{
	bwcms_dbg_mac80211(wwc_hw->d11cowe, "ww%d: bandunit %d\n", wwc_hw->unit,
			   bandunit);

	wwc_hw->band = wwc_hw->bandstate[bandunit];

	/*
	 * BMAC_NOTE:
	 *   untiw we ewiminate need fow wwc->band wefs in wow wevew code
	 */
	wwc_hw->wwc->band = wwc_hw->wwc->bandstate[bandunit];

	/* set gmode cowe fwag */
	if (wwc_hw->sbcwk && !wwc_hw->noweset) {
		u32 gmode = 0;

		if (bandunit == 0)
			gmode = SICF_GMODE;

		bwcms_b_cowe_ioctw(wwc_hw, SICF_GMODE, gmode);
	}
}

/* switch to new band but weave it inactive */
static u32 bwcms_c_setband_inact(stwuct bwcms_c_info *wwc, uint bandunit)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	u32 macintmask;
	u32 macctww;

	bwcms_dbg_mac80211(wwc_hw->d11cowe, "ww%d\n", wwc_hw->unit);
	macctww = bcma_wead32(wwc_hw->d11cowe,
			      D11WEGOFFS(maccontwow));
	WAWN_ON((macctww & MCTW_EN_MAC) != 0);

	/* disabwe intewwupts */
	macintmask = bwcms_intwsoff(wwc->ww);

	/* wadio off */
	wwc_phy_switch_wadio(wwc_hw->band->pi, OFF);

	bwcms_b_cowe_phy_cwk(wwc_hw, OFF);

	bwcms_c_setxband(wwc_hw, bandunit);

	wetuwn macintmask;
}

/* pwocess an individuaw stwuct tx_status */
static boow
bwcms_c_dotxstatus(stwuct bwcms_c_info *wwc, stwuct tx_status *txs)
{
	stwuct sk_buff *p = NUWW;
	uint queue = NFIFO;
	stwuct dma_pub *dma = NUWW;
	stwuct d11txh *txh = NUWW;
	stwuct scb *scb = NUWW;
	int tx_fwame_count;
	uint supw_status;
	boow wastfwame;
	stwuct ieee80211_hdw *h;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ieee80211_tx_wate *txwate;
	int i;
	boow fataw = twue;

	twace_bwcms_txstatus(&wwc->hw->d11cowe->dev, txs->fwamewen,
			     txs->fwameid, txs->status, txs->wasttxtime,
			     txs->sequence, txs->phyeww, txs->ackphywxsh);

	/* discawd intewmediate indications fow ucode with one wegitimate case:
	 *   e.g. if "useWTS" is set. ucode did a successfuw wts/cts exchange,
	 *   but the subsequent tx of DATA faiwed. so it wiww stawt wts/cts
	 *   fwom the beginning (wesetting the wts twansmission count)
	 */
	if (!(txs->status & TX_STATUS_AMPDU)
	    && (txs->status & TX_STATUS_INTEWMEDIATE)) {
		bwcms_dbg_tx(wwc->hw->d11cowe, "INTEWMEDIATE but not AMPDU\n");
		fataw = fawse;
		goto out;
	}

	queue = txs->fwameid & TXFID_QUEUE_MASK;
	if (queue >= NFIFO) {
		bwcms_eww(wwc->hw->d11cowe, "queue %u >= NFIFO\n", queue);
		goto out;
	}

	dma = wwc->hw->di[queue];

	p = dma_getnexttxp(wwc->hw->di[queue], DMA_WANGE_TWANSMITTED);
	if (p == NUWW) {
		bwcms_eww(wwc->hw->d11cowe, "dma_getnexttxp wetuwned nuww!\n");
		goto out;
	}

	txh = (stwuct d11txh *) (p->data);

	if (txs->phyeww)
		bwcms_dbg_tx(wwc->hw->d11cowe, "phyeww 0x%x, wate 0x%x\n",
			     txs->phyeww, txh->MainWates);

	if (txs->fwameid != we16_to_cpu(txh->TxFwameID)) {
		bwcms_eww(wwc->hw->d11cowe, "fwameid != txh->TxFwameID\n");
		goto out;
	}
	tx_info = IEEE80211_SKB_CB(p);
	h = (stwuct ieee80211_hdw *)((u8 *) (txh + 1) + D11_PHY_HDW_WEN);

	if (tx_info->wate_dwivew_data[0])
		scb = &wwc->pwi_scb;

	if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU) {
		bwcms_c_ampdu_dotxstatus(wwc->ampdu, scb, p, txs);
		fataw = fawse;
		goto out;
	}

	/*
	 * bwcms_c_ampdu_dotxstatus() wiww twace tx descwiptows fow AMPDU
	 * fwames; this twaces them fow the west.
	 */
	twace_bwcms_txdesc(&wwc->hw->d11cowe->dev, txh, sizeof(*txh));

	supw_status = txs->status & TX_STATUS_SUPW_MASK;
	if (supw_status == TX_STATUS_SUPW_BADCH) {
		unsigned xfts = we16_to_cpu(txh->XtwaFwameTypes);
		bwcms_dbg_tx(wwc->hw->d11cowe,
			     "Pkt tx suppwessed, dest chan %u, cuwwent %d\n",
			     (xfts >> XFTS_CHANNEW_SHIFT) & 0xff,
			     CHSPEC_CHANNEW(wwc->defauwt_bss->chanspec));
	}

	tx_fwame_count =
	    (txs->status & TX_STATUS_FWM_WTX_MASK) >> TX_STATUS_FWM_WTX_SHIFT;

	wastfwame = !ieee80211_has_mowefwags(h->fwame_contwow);

	if (!wastfwame) {
		bwcms_eww(wwc->hw->d11cowe, "Not wast fwame!\n");
	} ewse {
		/*
		 * Set infowmation to be consumed by Minstwew ht.
		 *
		 * The "fawwback wimit" is the numbew of tx attempts a given
		 * MPDU is sent at the "pwimawy" wate. Tx attempts beyond that
		 * wimit awe sent at the "secondawy" wate.
		 * A 'showt fwame' does not exceed WTS tweshowd.
		 */
		u16 sfbw,	/* Showt Fwame Wate Fawwback Wimit */
		    wfbw,	/* Wong Fwame Wate Fawwback Wimit */
		    fbw;

		if (queue < IEEE80211_NUM_ACS) {
			sfbw = GFIEWD(wwc->wme_wetwies[wme_fifo2ac[queue]],
				      EDCF_SFB);
			wfbw = GFIEWD(wwc->wme_wetwies[wme_fifo2ac[queue]],
				      EDCF_WFB);
		} ewse {
			sfbw = wwc->SFBW;
			wfbw = wwc->WFBW;
		}

		txwate = tx_info->status.wates;
		if (txwate[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS)
			fbw = wfbw;
		ewse
			fbw = sfbw;

		ieee80211_tx_info_cweaw_status(tx_info);

		if ((tx_fwame_count > fbw) && (txwate[1].idx >= 0)) {
			/*
			 * wate sewection wequested a fawwback wate
			 * and we used it
			 */
			txwate[0].count = fbw;
			txwate[1].count = tx_fwame_count - fbw;
		} ewse {
			/*
			 * wate sewection did not wequest fawwback wate, ow
			 * we didn't need it
			 */
			txwate[0].count = tx_fwame_count;
			/*
			 * wc80211_minstwew.c:minstwew_tx_status() expects
			 * unused wates to be mawked with idx = -1
			 */
			txwate[1].idx = -1;
			txwate[1].count = 0;
		}

		/* cweaw the west of the wates */
		fow (i = 2; i < IEEE80211_TX_MAX_WATES; i++) {
			txwate[i].idx = -1;
			txwate[i].count = 0;
		}

		if (txs->status & TX_STATUS_ACK_WCV)
			tx_info->fwags |= IEEE80211_TX_STAT_ACK;
	}

	if (wastfwame) {
		/* wemove PWCP & Bwoadcom tx descwiptow headew */
		skb_puww(p, D11_PHY_HDW_WEN);
		skb_puww(p, D11_TXH_WEN);
		ieee80211_tx_status_iwqsafe(wwc->pub->ieee_hw, p);
	} ewse {
		bwcms_eww(wwc->hw->d11cowe,
			  "%s: Not wast fwame => not cawwing tx_status\n",
			  __func__);
	}

	fataw = fawse;

 out:
	if (fataw) {
		if (txh)
			twace_bwcms_txdesc(&wwc->hw->d11cowe->dev, txh,
					   sizeof(*txh));
		bwcmu_pkt_buf_fwee_skb(p);
	}

	if (dma && queue < NFIFO) {
		u16 ac_queue = bwcms_fifo_to_ac(queue);
		if (dma->txavaiw > TX_HEADWOOM && queue < TX_BCMC_FIFO &&
		    ieee80211_queue_stopped(wwc->pub->ieee_hw, ac_queue))
			ieee80211_wake_queue(wwc->pub->ieee_hw, ac_queue);
		dma_kick_tx(dma);
	}

	wetuwn fataw;
}

/* pwocess tx compwetion events in BMAC
 * Wetuwn twue if mowe tx status need to be pwocessed. fawse othewwise.
 */
static boow
bwcms_b_txstatus(stwuct bwcms_hawdwawe *wwc_hw, boow bound, boow *fataw)
{
	stwuct bcma_device *cowe;
	stwuct tx_status txstatus, *txs;
	u32 s1, s2;
	uint n = 0;
	/*
	 * Pawam 'max_tx_num' indicates max. # tx status to pwocess befowe
	 * bweak out.
	 */
	uint max_tx_num = bound ? TXSBND : -1;

	txs = &txstatus;
	cowe = wwc_hw->d11cowe;
	*fataw = fawse;

	whiwe (n < max_tx_num) {
		s1 = bcma_wead32(cowe, D11WEGOFFS(fwmtxstatus));
		if (s1 == 0xffffffff) {
			bwcms_eww(cowe, "ww%d: %s: dead chip\n", wwc_hw->unit,
				  __func__);
			*fataw = twue;
			wetuwn fawse;
		}
		/* onwy pwocess when vawid */
		if (!(s1 & TXS_V))
			bweak;

		s2 = bcma_wead32(cowe, D11WEGOFFS(fwmtxstatus2));
		txs->status = s1 & TXS_STATUS_MASK;
		txs->fwameid = (s1 & TXS_FID_MASK) >> TXS_FID_SHIFT;
		txs->sequence = s2 & TXS_SEQ_MASK;
		txs->phyeww = (s2 & TXS_PTX_MASK) >> TXS_PTX_SHIFT;
		txs->wasttxtime = 0;

		*fataw = bwcms_c_dotxstatus(wwc_hw->wwc, txs);
		if (*fataw)
			wetuwn fawse;
		n++;
	}

	wetuwn n >= max_tx_num;
}

static void bwcms_c_tbtt(stwuct bwcms_c_info *wwc)
{
	if (wwc->bsscfg->type == BWCMS_TYPE_ADHOC)
		/*
		 * DiwFwmQ is now vawid...defew setting untiw end
		 * of ATIM window
		 */
		wwc->qvawid |= MCMD_DIWFWMQVAW;
}

/* set initiaw host fwags vawue */
static void
bwcms_c_mhfdef(stwuct bwcms_c_info *wwc, u16 *mhfs, u16 mhf2_init)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;

	memset(mhfs, 0, MHFMAX * sizeof(u16));

	mhfs[MHF2] |= mhf2_init;

	/* pwohibit use of swowcwock on muwtifunction boawds */
	if (wwc_hw->boawdfwags & BFW_NOPWWDOWN)
		mhfs[MHF1] |= MHF1_FOWCEFASTCWK;

	if (BWCMS_ISNPHY(wwc_hw->band) && NWEV_WT(wwc_hw->band->phywev, 2)) {
		mhfs[MHF2] |= MHF2_NPHY40MHZ_WAW;
		mhfs[MHF1] |= MHF1_IQSWAP_WAW;
	}
}

static uint
dmaweg(uint diwection, uint fifonum)
{
	if (diwection == DMA_TX)
		wetuwn offsetof(stwuct d11wegs, fifo64wegs[fifonum].dmaxmt);
	wetuwn offsetof(stwuct d11wegs, fifo64wegs[fifonum].dmawcv);
}

static boow bwcms_b_attach_dmapio(stwuct bwcms_c_info *wwc, uint j, boow wme)
{
	uint i;
	chaw name[8];
	/*
	 * ucode host fwag 2 needed fow pio mode, independent of band and fifo
	 */
	u16 pio_mhf2 = 0;
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	uint unit = wwc_hw->unit;

	/* name and offsets fow dma_attach */
	snpwintf(name, sizeof(name), "ww%d", unit);

	if (wwc_hw->di[0] == NUWW) {	/* Init FIFOs */
		int dma_attach_eww = 0;

		/*
		 * FIFO 0
		 * TX: TX_AC_BK_FIFO (TX AC Backgwound data packets)
		 * WX: WX_FIFO (WX data packets)
		 */
		wwc_hw->di[0] = dma_attach(name, wwc,
					   (wme ? dmaweg(DMA_TX, 0) : 0),
					   dmaweg(DMA_WX, 0),
					   (wme ? NTXD : 0), NWXD,
					   WXBUFSZ, -1, NWXBUFPOST,
					   BWCMS_HWWXOFF);
		dma_attach_eww |= (NUWW == wwc_hw->di[0]);

		/*
		 * FIFO 1
		 * TX: TX_AC_BE_FIFO (TX AC Best-Effowt data packets)
		 *   (wegacy) TX_DATA_FIFO (TX data packets)
		 * WX: UNUSED
		 */
		wwc_hw->di[1] = dma_attach(name, wwc,
					   dmaweg(DMA_TX, 1), 0,
					   NTXD, 0, 0, -1, 0, 0);
		dma_attach_eww |= (NUWW == wwc_hw->di[1]);

		/*
		 * FIFO 2
		 * TX: TX_AC_VI_FIFO (TX AC Video data packets)
		 * WX: UNUSED
		 */
		wwc_hw->di[2] = dma_attach(name, wwc,
					   dmaweg(DMA_TX, 2), 0,
					   NTXD, 0, 0, -1, 0, 0);
		dma_attach_eww |= (NUWW == wwc_hw->di[2]);
		/*
		 * FIFO 3
		 * TX: TX_AC_VO_FIFO (TX AC Voice data packets)
		 *   (wegacy) TX_CTW_FIFO (TX contwow & mgmt packets)
		 */
		wwc_hw->di[3] = dma_attach(name, wwc,
					   dmaweg(DMA_TX, 3),
					   0, NTXD, 0, 0, -1,
					   0, 0);
		dma_attach_eww |= (NUWW == wwc_hw->di[3]);
/* Cweanew to weave this as if with AP defined */

		if (dma_attach_eww) {
			bwcms_eww(wwc_hw->d11cowe,
				  "ww%d: wwc_attach: dma_attach faiwed\n",
				  unit);
			wetuwn fawse;
		}

		/* get pointew to dma engine tx fwow contwow vawiabwe */
		fow (i = 0; i < NFIFO; i++)
			if (wwc_hw->di[i])
				wwc_hw->txavaiw[i] =
				    (uint *) dma_getvaw(wwc_hw->di[i],
							"&txavaiw");
	}

	/* initiaw ucode host fwags */
	bwcms_c_mhfdef(wwc, wwc_hw->band->mhfs, pio_mhf2);

	wetuwn twue;
}

static void bwcms_b_detach_dmapio(stwuct bwcms_hawdwawe *wwc_hw)
{
	uint j;

	fow (j = 0; j < NFIFO; j++) {
		if (wwc_hw->di[j]) {
			dma_detach(wwc_hw->di[j]);
			wwc_hw->di[j] = NUWW;
		}
	}
}

/*
 * Initiawize bwcms_c_info defauwt vawues ...
 * may get ovewwides watew in this function
 *  BMAC_NOTES, move wow out and wesowve the dangwing ones
 */
static void bwcms_b_info_init(stwuct bwcms_hawdwawe *wwc_hw)
{
	stwuct bwcms_c_info *wwc = wwc_hw->wwc;

	/* set defauwt sw macintmask vawue */
	wwc->defmacintmask = DEF_MACINTMASK;

	/* vawious 802.11g modes */
	wwc_hw->showtswot = fawse;

	wwc_hw->SFBW = WETWY_SHOWT_FB;
	wwc_hw->WFBW = WETWY_WONG_FB;

	/* defauwt mac wetwy wimits */
	wwc_hw->SWW = WETWY_SHOWT_DEF;
	wwc_hw->WWW = WETWY_WONG_DEF;
	wwc_hw->chanspec = ch20mhz_chspec(1);
}

static void bwcms_b_wait_fow_wake(stwuct bwcms_hawdwawe *wwc_hw)
{
	/* deway befowe fiwst wead of ucode state */
	udeway(40);

	/* wait untiw ucode is no wongew asweep */
	SPINWAIT((bwcms_b_wead_shm(wwc_hw, M_UCODE_DBGST) ==
		  DBGST_ASWEEP), wwc_hw->wwc->fastpwwup_dwy);
}

/* contwow chip cwock to save powew, enabwe dynamic cwock ow fowce fast cwock */
static void bwcms_b_cwkctw_cwk(stwuct bwcms_hawdwawe *wwc_hw, enum bcma_cwkmode mode)
{
	if (ai_get_cccaps(wwc_hw->sih) & CC_CAP_PMU) {
		/* new chips with PMU, CCS_FOWCEHT wiww distwibute the HT cwock
		 * on backpwane, but mac cowe wiww stiww wun on AWP(not HT) when
		 * it entews powewsave mode, which means the FCA bit may not be
		 * set. Shouwd wakeup mac if dwivew wants it to wun on HT.
		 */

		if (wwc_hw->cwk) {
			if (mode == BCMA_CWKMODE_FAST) {
				bcma_set32(wwc_hw->d11cowe,
					   D11WEGOFFS(cwk_ctw_st),
					   CCS_FOWCEHT);

				udeway(64);

				SPINWAIT(
				    ((bcma_wead32(wwc_hw->d11cowe,
				      D11WEGOFFS(cwk_ctw_st)) &
				      CCS_HTAVAIW) == 0),
				      PMU_MAX_TWANSITION_DWY);
				WAWN_ON(!(bcma_wead32(wwc_hw->d11cowe,
					D11WEGOFFS(cwk_ctw_st)) &
					CCS_HTAVAIW));
			} ewse {
				if ((ai_get_pmuwev(wwc_hw->sih) == 0) &&
				    (bcma_wead32(wwc_hw->d11cowe,
					D11WEGOFFS(cwk_ctw_st)) &
					(CCS_FOWCEHT | CCS_HTAWEQ)))
					SPINWAIT(
					    ((bcma_wead32(wwc_hw->d11cowe,
					      offsetof(stwuct d11wegs,
						       cwk_ctw_st)) &
					      CCS_HTAVAIW) == 0),
					      PMU_MAX_TWANSITION_DWY);
				bcma_mask32(wwc_hw->d11cowe,
					D11WEGOFFS(cwk_ctw_st),
					~CCS_FOWCEHT);
			}
		}
		wwc_hw->fowcefastcwk = (mode == BCMA_CWKMODE_FAST);
	} ewse {

		/* owd chips w/o PMU, fowce HT thwough cc,
		 * then use FCA to vewify mac is wunning fast cwock
		 */

		wwc_hw->fowcefastcwk = ai_cwkctw_cc(wwc_hw->sih, mode);

		/* check fast cwock is avaiwabwe (if cowe is not in weset) */
		if (wwc_hw->fowcefastcwk && wwc_hw->cwk)
			WAWN_ON(!(bcma_awead32(wwc_hw->d11cowe, BCMA_IOST) &
				  SISF_FCWKA));

		/*
		 * keep the ucode wake bit on if fowcefastcwk is on since we
		 * do not want ucode to put us back to swow cwock when it dozes
		 * fow PM mode. Code bewow matches the wake ovewwide bit with
		 * cuwwent fowcefastcwk state. Onwy setting bit in wake_ovewwide
		 * instead of waking ucode immediatewy since owd code had this
		 * behaviow. Owdew code set wwc->fowcefastcwk but onwy had the
		 * wake happen if the wakup_ucode wowk (pwotected by an up
		 * check) was executed just bewow.
		 */
		if (wwc_hw->fowcefastcwk)
			mboowset(wwc_hw->wake_ovewwide,
				 BWCMS_WAKE_OVEWWIDE_FOWCEFAST);
		ewse
			mboowcww(wwc_hw->wake_ovewwide,
				 BWCMS_WAKE_OVEWWIDE_FOWCEFAST);
	}
}

/* set ow cweaw ucode host fwag bits
 * it has an optimization fow no-change wwite
 * it onwy wwites thwough shawed memowy when the cowe has cwock;
 * pwe-CWK changes shouwd use wwc_wwite_mhf to get awound the optimization
 *
 *
 * bands vawues awe: BWCM_BAND_AUTO <--- Cuwwent band onwy
 *                   BWCM_BAND_5G   <--- 5G band onwy
 *                   BWCM_BAND_2G   <--- 2G band onwy
 *                   BWCM_BAND_AWW  <--- Aww bands
 */
void
bwcms_b_mhf(stwuct bwcms_hawdwawe *wwc_hw, u8 idx, u16 mask, u16 vaw,
	     int bands)
{
	u16 save;
	u16 addw[MHFMAX] = {
		M_HOST_FWAGS1, M_HOST_FWAGS2, M_HOST_FWAGS3, M_HOST_FWAGS4,
		M_HOST_FWAGS5
	};
	stwuct bwcms_hw_band *band;

	if ((vaw & ~mask) || idx >= MHFMAX)
		wetuwn; /* ewwow condition */

	switch (bands) {
		/* Cuwwent band onwy ow aww bands,
		 * then set the band to cuwwent band
		 */
	case BWCM_BAND_AUTO:
	case BWCM_BAND_AWW:
		band = wwc_hw->band;
		bweak;
	case BWCM_BAND_5G:
		band = wwc_hw->bandstate[BAND_5G_INDEX];
		bweak;
	case BWCM_BAND_2G:
		band = wwc_hw->bandstate[BAND_2G_INDEX];
		bweak;
	defauwt:
		band = NUWW;	/* ewwow condition */
	}

	if (band) {
		save = band->mhfs[idx];
		band->mhfs[idx] = (band->mhfs[idx] & ~mask) | vaw;

		/* optimization: onwy wwite thwough if changed, and
		 * changed band is the cuwwent band
		 */
		if (wwc_hw->cwk && (band->mhfs[idx] != save)
		    && (band == wwc_hw->band))
			bwcms_b_wwite_shm(wwc_hw, addw[idx],
					   (u16) band->mhfs[idx]);
	}

	if (bands == BWCM_BAND_AWW) {
		wwc_hw->bandstate[0]->mhfs[idx] =
		    (wwc_hw->bandstate[0]->mhfs[idx] & ~mask) | vaw;
		wwc_hw->bandstate[1]->mhfs[idx] =
		    (wwc_hw->bandstate[1]->mhfs[idx] & ~mask) | vaw;
	}
}

/* set the maccontwow wegistew to desiwed weset state and
 * initiawize the sw cache of the wegistew
 */
static void bwcms_c_mctww_weset(stwuct bwcms_hawdwawe *wwc_hw)
{
	/* IHW accesses awe awways enabwed, PSM disabwed, HPS off and WAKE on */
	wwc_hw->maccontwow = 0;
	wwc_hw->suspended_fifos = 0;
	wwc_hw->wake_ovewwide = 0;
	wwc_hw->mute_ovewwide = 0;
	bwcms_b_mctww(wwc_hw, ~0, MCTW_IHW_EN | MCTW_WAKE);
}

/*
 * wwite the softwawe state of maccontwow and
 * ovewwides to the maccontwow wegistew
 */
static void bwcms_c_mctww_wwite(stwuct bwcms_hawdwawe *wwc_hw)
{
	u32 maccontwow = wwc_hw->maccontwow;

	/* OW in the wake bit if ovewwidden */
	if (wwc_hw->wake_ovewwide)
		maccontwow |= MCTW_WAKE;

	/* set AP and INFWA bits fow mute if needed */
	if (wwc_hw->mute_ovewwide) {
		maccontwow &= ~(MCTW_AP);
		maccontwow |= MCTW_INFWA;
	}

	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(maccontwow),
		     maccontwow);
}

/* set ow cweaw maccontwow bits */
void bwcms_b_mctww(stwuct bwcms_hawdwawe *wwc_hw, u32 mask, u32 vaw)
{
	u32 maccontwow;
	u32 new_maccontwow;

	if (vaw & ~mask)
		wetuwn; /* ewwow condition */
	maccontwow = wwc_hw->maccontwow;
	new_maccontwow = (maccontwow & ~mask) | vaw;

	/* if the new maccontwow vawue is the same as the owd, nothing to do */
	if (new_maccontwow == maccontwow)
		wetuwn;

	/* something changed, cache the new vawue */
	wwc_hw->maccontwow = new_maccontwow;

	/* wwite the new vawues with ovewwides appwied */
	bwcms_c_mctww_wwite(wwc_hw);
}

void bwcms_c_ucode_wake_ovewwide_set(stwuct bwcms_hawdwawe *wwc_hw,
				 u32 ovewwide_bit)
{
	if (wwc_hw->wake_ovewwide || (wwc_hw->maccontwow & MCTW_WAKE)) {
		mboowset(wwc_hw->wake_ovewwide, ovewwide_bit);
		wetuwn;
	}

	mboowset(wwc_hw->wake_ovewwide, ovewwide_bit);

	bwcms_c_mctww_wwite(wwc_hw);
	bwcms_b_wait_fow_wake(wwc_hw);
}

void bwcms_c_ucode_wake_ovewwide_cweaw(stwuct bwcms_hawdwawe *wwc_hw,
				   u32 ovewwide_bit)
{
	mboowcww(wwc_hw->wake_ovewwide, ovewwide_bit);

	if (wwc_hw->wake_ovewwide || (wwc_hw->maccontwow & MCTW_WAKE))
		wetuwn;

	bwcms_c_mctww_wwite(wwc_hw);
}

/* When dwivew needs ucode to stop beaconing, it has to make suwe that
 * MCTW_AP is cweaw and MCTW_INFWA is set
 * Mode           MCTW_AP        MCTW_INFWA
 * AP                1              1
 * STA               0              1 <--- This wiww ensuwe no beacons
 * IBSS              0              0
 */
static void bwcms_c_ucode_mute_ovewwide_set(stwuct bwcms_hawdwawe *wwc_hw)
{
	wwc_hw->mute_ovewwide = 1;

	/* if maccontwow awweady has AP == 0 and INFWA == 1 without this
	 * ovewwide, then thewe is no change to wwite
	 */
	if ((wwc_hw->maccontwow & (MCTW_AP | MCTW_INFWA)) == MCTW_INFWA)
		wetuwn;

	bwcms_c_mctww_wwite(wwc_hw);
}

/* Cweaw the ovewwide on AP and INFWA bits */
static void bwcms_c_ucode_mute_ovewwide_cweaw(stwuct bwcms_hawdwawe *wwc_hw)
{
	if (wwc_hw->mute_ovewwide == 0)
		wetuwn;

	wwc_hw->mute_ovewwide = 0;

	/* if maccontwow awweady has AP == 0 and INFWA == 1 without this
	 * ovewwide, then thewe is no change to wwite
	 */
	if ((wwc_hw->maccontwow & (MCTW_AP | MCTW_INFWA)) == MCTW_INFWA)
		wetuwn;

	bwcms_c_mctww_wwite(wwc_hw);
}

/*
 * Wwite a MAC addwess to the given match weg offset in the WXE match engine.
 */
static void
bwcms_b_set_addwmatch(stwuct bwcms_hawdwawe *wwc_hw, int match_weg_offset,
		       const u8 *addw)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u16 mac_w;
	u16 mac_m;
	u16 mac_h;

	bwcms_dbg_wx(cowe, "ww%d: bwcms_b_set_addwmatch\n", wwc_hw->unit);

	mac_w = addw[0] | (addw[1] << 8);
	mac_m = addw[2] | (addw[3] << 8);
	mac_h = addw[4] | (addw[5] << 8);

	/* entew the MAC addw into the WXE match wegistews */
	bcma_wwite16(cowe, D11WEGOFFS(wcm_ctw),
		     WCM_INC_DATA | match_weg_offset);
	bcma_wwite16(cowe, D11WEGOFFS(wcm_mat_data), mac_w);
	bcma_wwite16(cowe, D11WEGOFFS(wcm_mat_data), mac_m);
	bcma_wwite16(cowe, D11WEGOFFS(wcm_mat_data), mac_h);
}

void
bwcms_b_wwite_tempwate_wam(stwuct bwcms_hawdwawe *wwc_hw, int offset, int wen,
			    void *buf)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 wowd;
	__we32 wowd_we;
	__be32 wowd_be;
	boow be_bit;
	bwcms_dbg_info(cowe, "ww%d\n", wwc_hw->unit);

	bcma_wwite32(cowe, D11WEGOFFS(tpwatewwptw), offset);

	/* if MCTW_BIGEND bit set in mac contwow wegistew,
	 * the chip swaps data in fifo, as weww as data in
	 * tempwate wam
	 */
	be_bit = (bcma_wead32(cowe, D11WEGOFFS(maccontwow)) & MCTW_BIGEND) != 0;

	whiwe (wen > 0) {
		memcpy(&wowd, buf, sizeof(u32));

		if (be_bit) {
			wowd_be = cpu_to_be32(wowd);
			wowd = *(u32 *)&wowd_be;
		} ewse {
			wowd_we = cpu_to_we32(wowd);
			wowd = *(u32 *)&wowd_we;
		}

		bcma_wwite32(cowe, D11WEGOFFS(tpwatewwdata), wowd);

		buf = (u8 *) buf + sizeof(u32);
		wen -= sizeof(u32);
	}
}

static void bwcms_b_set_cwmin(stwuct bwcms_hawdwawe *wwc_hw, u16 newmin)
{
	wwc_hw->band->CWmin = newmin;

	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objaddw),
		     OBJADDW_SCW_SEW | S_DOT11_CWMIN);
	(void)bcma_wead32(wwc_hw->d11cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objdata), newmin);
}

static void bwcms_b_set_cwmax(stwuct bwcms_hawdwawe *wwc_hw, u16 newmax)
{
	wwc_hw->band->CWmax = newmax;

	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objaddw),
		     OBJADDW_SCW_SEW | S_DOT11_CWMAX);
	(void)bcma_wead32(wwc_hw->d11cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objdata), newmax);
}

void bwcms_b_bw_set(stwuct bwcms_hawdwawe *wwc_hw, u16 bw)
{
	boow fastcwk;

	/* wequest FAST cwock if not on */
	fastcwk = wwc_hw->fowcefastcwk;
	if (!fastcwk)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);

	wwc_phy_bw_state_set(wwc_hw->band->pi, bw);

	bwcms_b_phy_weset(wwc_hw);
	wwc_phy_init(wwc_hw->band->pi, wwc_phy_chanspec_get(wwc_hw->band->pi));

	/* westowe the cwk */
	if (!fastcwk)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_DYNAMIC);
}

static void bwcms_b_upd_synthpu(stwuct bwcms_hawdwawe *wwc_hw)
{
	u16 v;
	stwuct bwcms_c_info *wwc = wwc_hw->wwc;
	/* update SYNTHPU_DWY */

	if (BWCMS_ISWCNPHY(wwc->band))
		v = SYNTHPU_DWY_WPPHY_US;
	ewse if (BWCMS_ISNPHY(wwc->band) && (NWEV_GE(wwc->band->phywev, 3)))
		v = SYNTHPU_DWY_NPHY_US;
	ewse
		v = SYNTHPU_DWY_BPHY_US;

	bwcms_b_wwite_shm(wwc_hw, M_SYNTHPU_DWY, v);
}

static void bwcms_c_ucode_txant_set(stwuct bwcms_hawdwawe *wwc_hw)
{
	u16 phyctw;
	u16 phytxant = wwc_hw->bmac_phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* set the Pwobe Wesponse fwame phy contwow wowd */
	phyctw = bwcms_b_wead_shm(wwc_hw, M_CTXPWS_BWK + C_CTX_PCTWWD_POS);
	phyctw = (phyctw & ~mask) | phytxant;
	bwcms_b_wwite_shm(wwc_hw, M_CTXPWS_BWK + C_CTX_PCTWWD_POS, phyctw);

	/* set the Wesponse (ACK/CTS) fwame phy contwow wowd */
	phyctw = bwcms_b_wead_shm(wwc_hw, M_WSP_PCTWWD);
	phyctw = (phyctw & ~mask) | phytxant;
	bwcms_b_wwite_shm(wwc_hw, M_WSP_PCTWWD, phyctw);
}

static u16 bwcms_b_ofdm_watetabwe_offset(stwuct bwcms_hawdwawe *wwc_hw,
					 u8 wate)
{
	uint i;
	u8 pwcp_wate = 0;
	stwuct pwcp_signaw_wate_wookup {
		u8 wate;
		u8 signaw_wate;
	};
	/* OFDM WATE sub-fiewd of PWCP SIGNAW fiewd, pew 802.11 sec 17.3.4.1 */
	const stwuct pwcp_signaw_wate_wookup wate_wookup[] = {
		{BWCM_WATE_6M, 0xB},
		{BWCM_WATE_9M, 0xF},
		{BWCM_WATE_12M, 0xA},
		{BWCM_WATE_18M, 0xE},
		{BWCM_WATE_24M, 0x9},
		{BWCM_WATE_36M, 0xD},
		{BWCM_WATE_48M, 0x8},
		{BWCM_WATE_54M, 0xC}
	};

	fow (i = 0; i < AWWAY_SIZE(wate_wookup); i++) {
		if (wate == wate_wookup[i].wate) {
			pwcp_wate = wate_wookup[i].signaw_wate;
			bweak;
		}
	}

	/* Find the SHM pointew to the wate tabwe entwy by wooking in the
	 * Diwect-map Tabwe
	 */
	wetuwn 2 * bwcms_b_wead_shm(wwc_hw, M_WT_DIWMAP_A + (pwcp_wate * 2));
}

static void bwcms_upd_ofdm_pctw1_tabwe(stwuct bwcms_hawdwawe *wwc_hw)
{
	u8 wate;
	u8 wates[8] = {
		BWCM_WATE_6M, BWCM_WATE_9M, BWCM_WATE_12M, BWCM_WATE_18M,
		BWCM_WATE_24M, BWCM_WATE_36M, BWCM_WATE_48M, BWCM_WATE_54M
	};
	u16 entwy_ptw;
	u16 pctw1;
	uint i;

	if (!BWCMS_PHY_11N_CAP(wwc_hw->band))
		wetuwn;

	/* wawk the phy wate tabwe and update the entwies */
	fow (i = 0; i < AWWAY_SIZE(wates); i++) {
		wate = wates[i];

		entwy_ptw = bwcms_b_ofdm_watetabwe_offset(wwc_hw, wate);

		/* wead the SHM Wate Tabwe entwy OFDM PCTW1 vawues */
		pctw1 =
		    bwcms_b_wead_shm(wwc_hw, entwy_ptw + M_WT_OFDM_PCTW1_POS);

		/* modify the vawue */
		pctw1 &= ~PHY_TXC1_MODE_MASK;
		pctw1 |= (wwc_hw->hw_stf_ss_opmode << PHY_TXC1_MODE_SHIFT);

		/* Update the SHM Wate Tabwe entwy OFDM PCTW1 vawues */
		bwcms_b_wwite_shm(wwc_hw, entwy_ptw + M_WT_OFDM_PCTW1_POS,
				   pctw1);
	}
}

/* band-specific init */
static void bwcms_b_bsinit(stwuct bwcms_c_info *wwc, u16 chanspec)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;

	bwcms_dbg_mac80211(wwc_hw->d11cowe, "ww%d: bandunit %d\n", wwc_hw->unit,
			   wwc_hw->band->bandunit);

	bwcms_c_ucode_bsinit(wwc_hw);

	wwc_phy_init(wwc_hw->band->pi, chanspec);

	bwcms_c_ucode_txant_set(wwc_hw);

	/*
	 * cwmin is band-specific, update hawdwawe
	 * with vawue fow cuwwent band
	 */
	bwcms_b_set_cwmin(wwc_hw, wwc_hw->band->CWmin);
	bwcms_b_set_cwmax(wwc_hw, wwc_hw->band->CWmax);

	bwcms_b_update_swot_timing(wwc_hw,
				   wwc_hw->band->bandtype == BWCM_BAND_5G ?
				   twue : wwc_hw->showtswot);

	/* wwite phytype and phyvews */
	bwcms_b_wwite_shm(wwc_hw, M_PHYTYPE, (u16) wwc_hw->band->phytype);
	bwcms_b_wwite_shm(wwc_hw, M_PHYVEW, (u16) wwc_hw->band->phywev);

	/*
	 * initiawize the txphyctw1 wate tabwe since
	 * shmem is shawed between bands
	 */
	bwcms_upd_ofdm_pctw1_tabwe(wwc_hw);

	bwcms_b_upd_synthpu(wwc_hw);
}

/* Pewfowm a soft weset of the PHY PWW */
void bwcms_b_cowe_phypww_weset(stwuct bwcms_hawdwawe *wwc_hw)
{
	ai_cc_weg(wwc_hw->sih, offsetof(stwuct chipcwegs, chipcontwow_addw),
		  ~0, 0);
	udeway(1);
	ai_cc_weg(wwc_hw->sih, offsetof(stwuct chipcwegs, chipcontwow_data),
		  0x4, 0);
	udeway(1);
	ai_cc_weg(wwc_hw->sih, offsetof(stwuct chipcwegs, chipcontwow_data),
		  0x4, 4);
	udeway(1);
	ai_cc_weg(wwc_hw->sih, offsetof(stwuct chipcwegs, chipcontwow_data),
		  0x4, 0);
	udeway(1);
}

/* wight way to tuwn on phy cwock without weset fow NPHY onwy
 *  wefew to bwcms_b_cowe_phy_cwk fow fuww vewsion
 */
void bwcms_b_phycwk_fgc(stwuct bwcms_hawdwawe *wwc_hw, boow cwk)
{
	/* suppowt(necessawy fow NPHY and HYPHY) onwy */
	if (!BWCMS_ISNPHY(wwc_hw->band))
		wetuwn;

	if (ON == cwk)
		bwcms_b_cowe_ioctw(wwc_hw, SICF_FGC, SICF_FGC);
	ewse
		bwcms_b_cowe_ioctw(wwc_hw, SICF_FGC, 0);

}

void bwcms_b_macphycwk_set(stwuct bwcms_hawdwawe *wwc_hw, boow cwk)
{
	if (ON == cwk)
		bwcms_b_cowe_ioctw(wwc_hw, SICF_MPCWKE, SICF_MPCWKE);
	ewse
		bwcms_b_cowe_ioctw(wwc_hw, SICF_MPCWKE, 0);
}

void bwcms_b_phy_weset(stwuct bwcms_hawdwawe *wwc_hw)
{
	stwuct bwcms_phy_pub *pih = wwc_hw->band->pi;
	u32 phy_bw_cwkbits;

	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d: weset phy\n", wwc_hw->unit);

	if (pih == NUWW)
		wetuwn;

	phy_bw_cwkbits = wwc_phy_cwk_bwbits(wwc_hw->band->pi);

	/* Specific weset sequence wequiwed fow NPHY wev 3 and 4 */
	if (BWCMS_ISNPHY(wwc_hw->band) && NWEV_GE(wwc_hw->band->phywev, 3) &&
	    NWEV_WE(wwc_hw->band->phywev, 4)) {
		/* Set the PHY bandwidth */
		bwcms_b_cowe_ioctw(wwc_hw, SICF_BWMASK, phy_bw_cwkbits);

		udeway(1);

		/* Pewfowm a soft weset of the PHY PWW */
		bwcms_b_cowe_phypww_weset(wwc_hw);

		/* weset the PHY */
		bwcms_b_cowe_ioctw(wwc_hw, (SICF_PWST | SICF_PCWKE),
				   (SICF_PWST | SICF_PCWKE));
	} ewse {
		bwcms_b_cowe_ioctw(wwc_hw,
				   (SICF_PWST | SICF_PCWKE | SICF_BWMASK),
				   (SICF_PWST | SICF_PCWKE | phy_bw_cwkbits));
	}

	udeway(2);
	bwcms_b_cowe_phy_cwk(wwc_hw, ON);

	wwc_phy_anacowe(pih, ON);
}

/* switch to and initiawize new band */
static void bwcms_b_setband(stwuct bwcms_hawdwawe *wwc_hw, uint bandunit,
			    u16 chanspec) {
	stwuct bwcms_c_info *wwc = wwc_hw->wwc;
	u32 macintmask;

	/* Enabwe the d11 cowe befowe accessing it */
	if (!bcma_cowe_is_enabwed(wwc_hw->d11cowe)) {
		bcma_cowe_enabwe(wwc_hw->d11cowe, 0);
		bwcms_c_mctww_weset(wwc_hw);
	}

	macintmask = bwcms_c_setband_inact(wwc, bandunit);

	if (!wwc_hw->up)
		wetuwn;

	bwcms_b_cowe_phy_cwk(wwc_hw, ON);

	/* band-specific initiawizations */
	bwcms_b_bsinit(wwc, chanspec);

	/*
	 * If thewe awe any pending softwawe intewwupt bits,
	 * then wepwace these with a hawmwess nonzewo vawue
	 * so bwcms_c_dpc() wiww we-enabwe intewwupts when done.
	 */
	if (wwc->macintstatus)
		wwc->macintstatus = MI_DMAINT;

	/* westowe macintmask */
	bwcms_intwswestowe(wwc->ww, macintmask);

	/* ucode shouwd stiww be suspended.. */
	WAWN_ON((bcma_wead32(wwc_hw->d11cowe, D11WEGOFFS(maccontwow)) &
		 MCTW_EN_MAC) != 0);
}

static boow bwcms_c_isgoodchip(stwuct bwcms_hawdwawe *wwc_hw)
{

	/* weject unsuppowted cowewev */
	if (!CONF_HAS(D11CONF, wwc_hw->cowewev)) {
		wiphy_eww(wwc_hw->wwc->wiphy, "unsuppowted cowe wev %d\n",
			  wwc_hw->cowewev);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Vawidate some boawd info pawametews */
static boow bwcms_c_vawidboawdtype(stwuct bwcms_hawdwawe *wwc_hw)
{
	uint boawdwev = wwc_hw->boawdwev;

	/* 4 bits each fow boawd type, majow, minow, and tiny vewsion */
	uint bwt = (boawdwev & 0xf000) >> 12;
	uint b0 = (boawdwev & 0xf00) >> 8;
	uint b1 = (boawdwev & 0xf0) >> 4;
	uint b2 = boawdwev & 0xf;

	/* voawds fwom othew vendows awe awways considewed vawid */
	if (ai_get_boawdvendow(wwc_hw->sih) != PCI_VENDOW_ID_BWOADCOM)
		wetuwn twue;

	/* do some boawdwev sanity checks when boawdvendow is Bwoadcom */
	if (boawdwev == 0)
		wetuwn fawse;

	if (boawdwev <= 0xff)
		wetuwn twue;

	if ((bwt > 2) || (bwt == 0) || (b0 > 9) || (b0 == 0) || (b1 > 9)
		|| (b2 > 9))
		wetuwn fawse;

	wetuwn twue;
}

static void bwcms_c_get_macaddw(stwuct bwcms_hawdwawe *wwc_hw, u8 ethewaddw[ETH_AWEN])
{
	stwuct ssb_spwom *spwom = &wwc_hw->d11cowe->bus->spwom;

	/* If macaddw exists, use it (Swomwev4, CIS, ...). */
	if (!is_zewo_ethew_addw(spwom->iw0mac)) {
		memcpy(ethewaddw, spwom->iw0mac, ETH_AWEN);
		wetuwn;
	}

	if (wwc_hw->_nbands > 1)
		memcpy(ethewaddw, spwom->et1mac, ETH_AWEN);
	ewse
		memcpy(ethewaddw, spwom->iw0mac, ETH_AWEN);
}

/* powew both the pww and extewnaw osciwwatow on/off */
static void bwcms_b_xtaw(stwuct bwcms_hawdwawe *wwc_hw, boow want)
{
	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d: want %d\n", wwc_hw->unit, want);

	/*
	 * dont powew down if pwwdown is fawse ow
	 * we must poww hw wadio disabwe
	 */
	if (!want && wwc_hw->pwwweq)
		wetuwn;

	wwc_hw->sbcwk = want;
	if (!wwc_hw->sbcwk) {
		wwc_hw->cwk = fawse;
		if (wwc_hw->band && wwc_hw->band->pi)
			wwc_phy_hw_cwk_state_upd(wwc_hw->band->pi, fawse);
	}
}

/*
 * Wetuwn twue if wadio is disabwed, othewwise fawse.
 * hw wadio disabwe signaw is an extewnaw pin, usews activate it asynchwonouswy
 * this function couwd be cawwed when dwivew is down and w/o cwock
 * it opewates on diffewent wegistews depending on cowewev and boawdfwag.
 */
static boow bwcms_b_wadio_wead_hwdisabwed(stwuct bwcms_hawdwawe *wwc_hw)
{
	boow v, cwk, xtaw;
	u32 fwags = 0;

	xtaw = wwc_hw->sbcwk;
	if (!xtaw)
		bwcms_b_xtaw(wwc_hw, ON);

	/* may need to take cowe out of weset fiwst */
	cwk = wwc_hw->cwk;
	if (!cwk) {
		/*
		 * mac no wongew enabwes phycwk automaticawwy when dwivew
		 * accesses phyweg thwoughput mac. This can be skipped since
		 * onwy mac weg is accessed bewow
		 */
		if (D11WEV_GE(wwc_hw->cowewev, 18))
			fwags |= SICF_PCWKE;

		/*
		 * TODO: test suspend/wesume
		 *
		 * AI chip doesn't westowe baw0win2 on
		 * hibewnation/wesume, need sw fixup
		 */

		bcma_cowe_enabwe(wwc_hw->d11cowe, fwags);
		bwcms_c_mctww_weset(wwc_hw);
	}

	v = ((bcma_wead32(wwc_hw->d11cowe,
			  D11WEGOFFS(phydebug)) & PDBG_WFD) != 0);

	/* put cowe back into weset */
	if (!cwk)
		bcma_cowe_disabwe(wwc_hw->d11cowe, 0);

	if (!xtaw)
		bwcms_b_xtaw(wwc_hw, OFF);

	wetuwn v;
}

static boow wwc_dma_wxweset(stwuct bwcms_hawdwawe *wwc_hw, uint fifo)
{
	stwuct dma_pub *di = wwc_hw->di[fifo];
	wetuwn dma_wxweset(di);
}

/* d11 cowe weset
 *   ensuwe fask cwock duwing weset
 *   weset dma
 *   weset d11(out of weset)
 *   weset phy(out of weset)
 *   cweaw softwawe macintstatus fow fwesh new stawt
 * one testing hack wwc_hw->noweset wiww bypass the d11/phy weset
 */
void bwcms_b_coweweset(stwuct bwcms_hawdwawe *wwc_hw, u32 fwags)
{
	uint i;
	boow fastcwk;

	if (fwags == BWCMS_USE_COWEFWAGS)
		fwags = (wwc_hw->band->pi ? wwc_hw->band->cowe_fwags : 0);

	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d: cowe weset\n", wwc_hw->unit);

	/* wequest FAST cwock if not on  */
	fastcwk = wwc_hw->fowcefastcwk;
	if (!fastcwk)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);

	/* weset the dma engines except fiwst time thwu */
	if (bcma_cowe_is_enabwed(wwc_hw->d11cowe)) {
		fow (i = 0; i < NFIFO; i++)
			if ((wwc_hw->di[i]) && (!dma_txweset(wwc_hw->di[i])))
				bwcms_eww(wwc_hw->d11cowe, "ww%d: %s: "
					  "dma_txweset[%d]: cannot stop dma\n",
					   wwc_hw->unit, __func__, i);

		if ((wwc_hw->di[WX_FIFO])
		    && (!wwc_dma_wxweset(wwc_hw, WX_FIFO)))
			bwcms_eww(wwc_hw->d11cowe, "ww%d: %s: dma_wxweset"
				  "[%d]: cannot stop dma\n",
				  wwc_hw->unit, __func__, WX_FIFO);
	}
	/* if noweset, just stop the psm and wetuwn */
	if (wwc_hw->noweset) {
		wwc_hw->wwc->macintstatus = 0;	/* skip ww_dpc aftew down */
		bwcms_b_mctww(wwc_hw, MCTW_PSM_WUN | MCTW_EN_MAC, 0);
		wetuwn;
	}

	/*
	 * mac no wongew enabwes phycwk automaticawwy when dwivew accesses
	 * phyweg thwoughput mac, AND phy_weset is skipped at eawwy stage when
	 * band->pi is invawid. need to enabwe PHY CWK
	 */
	if (D11WEV_GE(wwc_hw->cowewev, 18))
		fwags |= SICF_PCWKE;

	/*
	 * weset the cowe
	 * In chips with PMU, the fastcwk wequest goes thwough d11 cowe
	 * weg 0x1e0, which is cweawed by the cowe_weset. have to we-wequest it.
	 *
	 * This adds some deway and we can optimize it by awso wequesting
	 * fastcwk thwough chipcommon duwing this pewiod if necessawy. But
	 * that has to wowk coowdinate with othew dwivew wike mips/awm since
	 * they may touch chipcommon as weww.
	 */
	wwc_hw->cwk = fawse;
	bcma_cowe_enabwe(wwc_hw->d11cowe, fwags);
	wwc_hw->cwk = twue;
	if (wwc_hw->band && wwc_hw->band->pi)
		wwc_phy_hw_cwk_state_upd(wwc_hw->band->pi, twue);

	bwcms_c_mctww_weset(wwc_hw);

	if (ai_get_cccaps(wwc_hw->sih) & CC_CAP_PMU)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);

	bwcms_b_phy_weset(wwc_hw);

	/* tuwn on PHY_PWW */
	bwcms_b_cowe_phypww_ctw(wwc_hw, twue);

	/* cweaw sw intstatus */
	wwc_hw->wwc->macintstatus = 0;

	/* westowe the cwk setting */
	if (!fastcwk)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_DYNAMIC);
}

/* txfifo sizes needs to be modified(incweased) since the newew cowes
 * have mowe memowy.
 */
static void bwcms_b_cowewev_fifofixup(stwuct bwcms_hawdwawe *wwc_hw)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u16 fifo_nu;
	u16 txfifo_stawtbwk = TXFIFO_STAWT_BWK, txfifo_endbwk;
	u16 txfifo_def, txfifo_def1;
	u16 txfifo_cmd;

	/* tx fifos stawt at TXFIFO_STAWT_BWK fwom the Base addwess */
	txfifo_stawtbwk = TXFIFO_STAWT_BWK;

	/* sequence of opewations:  weset fifo, set fifo size, weset fifo */
	fow (fifo_nu = 0; fifo_nu < NFIFO; fifo_nu++) {

		txfifo_endbwk = txfifo_stawtbwk + wwc_hw->xmtfifo_sz[fifo_nu];
		txfifo_def = (txfifo_stawtbwk & 0xff) |
		    (((txfifo_endbwk - 1) & 0xff) << TXFIFO_FIFOTOP_SHIFT);
		txfifo_def1 = ((txfifo_stawtbwk >> 8) & 0x1) |
		    ((((txfifo_endbwk -
			1) >> 8) & 0x1) << TXFIFO_FIFOTOP_SHIFT);
		txfifo_cmd =
		    TXFIFOCMD_WESET_MASK | (fifo_nu << TXFIFOCMD_FIFOSEW_SHIFT);

		bcma_wwite16(cowe, D11WEGOFFS(xmtfifocmd), txfifo_cmd);
		bcma_wwite16(cowe, D11WEGOFFS(xmtfifodef), txfifo_def);
		bcma_wwite16(cowe, D11WEGOFFS(xmtfifodef1), txfifo_def1);

		bcma_wwite16(cowe, D11WEGOFFS(xmtfifocmd), txfifo_cmd);

		txfifo_stawtbwk += wwc_hw->xmtfifo_sz[fifo_nu];
	}
	/*
	 * need to pwopagate to shm wocation to be in sync since ucode/hw won't
	 * do this
	 */
	bwcms_b_wwite_shm(wwc_hw, M_FIFOSIZE0,
			   wwc_hw->xmtfifo_sz[TX_AC_BE_FIFO]);
	bwcms_b_wwite_shm(wwc_hw, M_FIFOSIZE1,
			   wwc_hw->xmtfifo_sz[TX_AC_VI_FIFO]);
	bwcms_b_wwite_shm(wwc_hw, M_FIFOSIZE2,
			   ((wwc_hw->xmtfifo_sz[TX_AC_VO_FIFO] << 8) | wwc_hw->
			    xmtfifo_sz[TX_AC_BK_FIFO]));
	bwcms_b_wwite_shm(wwc_hw, M_FIFOSIZE3,
			   ((wwc_hw->xmtfifo_sz[TX_ATIM_FIFO] << 8) | wwc_hw->
			    xmtfifo_sz[TX_BCMC_FIFO]));
}

/* This function is used fow changing the tsf fwac wegistew
 * If spuw avoidance mode is off, the mac fweq wiww be 80/120/160Mhz
 * If spuw avoidance mode is on1, the mac fweq wiww be 82/123/164Mhz
 * If spuw avoidance mode is on2, the mac fweq wiww be 84/126/168Mhz
 * HTPHY Fowmuwa is 2^26/fweq(MHz) e.g.
 * Fow spuwon2 - 126MHz -> 2^26/126 = 532610.0
 *  - 532610 = 0x82082 => tsf_cwk_fwac_h = 0x8, tsf_cwk_fwac_w = 0x2082
 * Fow spuwon: 123MHz -> 2^26/123    = 545600.5
 *  - 545601 = 0x85341 => tsf_cwk_fwac_h = 0x8, tsf_cwk_fwac_w = 0x5341
 * Fow spuw off: 120MHz -> 2^26/120    = 559240.5
 *  - 559241 = 0x88889 => tsf_cwk_fwac_h = 0x8, tsf_cwk_fwac_w = 0x8889
 */

void bwcms_b_switch_macfweq(stwuct bwcms_hawdwawe *wwc_hw, u8 spuwmode)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;

	if ((ai_get_chip_id(wwc_hw->sih) == BCMA_CHIP_ID_BCM43224) ||
	    (ai_get_chip_id(wwc_hw->sih) == BCMA_CHIP_ID_BCM43225)) {
		if (spuwmode == WW_SPUWAVOID_ON2) {	/* 126Mhz */
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_w), 0x2082);
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_h), 0x8);
		} ewse if (spuwmode == WW_SPUWAVOID_ON1) {	/* 123Mhz */
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_w), 0x5341);
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_h), 0x8);
		} ewse {	/* 120Mhz */
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_w), 0x8889);
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_h), 0x8);
		}
	} ewse if (BWCMS_ISWCNPHY(wwc_hw->band)) {
		if (spuwmode == WW_SPUWAVOID_ON1) {	/* 82Mhz */
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_w), 0x7CE0);
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_h), 0xC);
		} ewse {	/* 80Mhz */
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_w), 0xCCCD);
			bcma_wwite16(cowe, D11WEGOFFS(tsf_cwk_fwac_h), 0xC);
		}
	}
}

void bwcms_c_stawt_station(stwuct bwcms_c_info *wwc, u8 *addw)
{
	memcpy(wwc->pub->cuw_ethewaddw, addw, sizeof(wwc->pub->cuw_ethewaddw));
	wwc->bsscfg->type = BWCMS_TYPE_STATION;
}

void bwcms_c_stawt_ap(stwuct bwcms_c_info *wwc, u8 *addw, const u8 *bssid,
		      u8 *ssid, size_t ssid_wen)
{
	bwcms_c_set_ssid(wwc, ssid, ssid_wen);

	memcpy(wwc->pub->cuw_ethewaddw, addw, sizeof(wwc->pub->cuw_ethewaddw));
	memcpy(wwc->bsscfg->BSSID, bssid, sizeof(wwc->bsscfg->BSSID));
	wwc->bsscfg->type = BWCMS_TYPE_AP;

	bwcms_b_mctww(wwc->hw, MCTW_AP | MCTW_INFWA, MCTW_AP | MCTW_INFWA);
}

void bwcms_c_stawt_adhoc(stwuct bwcms_c_info *wwc, u8 *addw)
{
	memcpy(wwc->pub->cuw_ethewaddw, addw, sizeof(wwc->pub->cuw_ethewaddw));
	wwc->bsscfg->type = BWCMS_TYPE_ADHOC;

	bwcms_b_mctww(wwc->hw, MCTW_AP | MCTW_INFWA, 0);
}

/* Initiawize GPIOs that awe contwowwed by D11 cowe */
static void bwcms_c_gpio_init(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	u32 gc, gm;

	/* use GPIO sewect 0 to get aww gpio signaws fwom the gpio out weg */
	bwcms_b_mctww(wwc_hw, MCTW_GPOUT_SEW_MASK, 0);

	/*
	 * Common GPIO setup:
	 *      G0 = WED 0 = WWAN Activity
	 *      G1 = WED 1 = WWAN 2.4 GHz Wadio State
	 *      G2 = WED 2 = WWAN 5 GHz Wadio State
	 *      G4 = wadio disabwe input (HI enabwed, WO disabwed)
	 */

	gc = gm = 0;

	/* Awwocate GPIOs fow mimo antenna divewsity featuwe */
	if (wwc_hw->antsew_type == ANTSEW_2x3) {
		/* Enabwe antenna divewsity, use 2x3 mode */
		bwcms_b_mhf(wwc_hw, MHF3, MHF3_ANTSEW_EN,
			     MHF3_ANTSEW_EN, BWCM_BAND_AWW);
		bwcms_b_mhf(wwc_hw, MHF3, MHF3_ANTSEW_MODE,
			     MHF3_ANTSEW_MODE, BWCM_BAND_AWW);

		/* init supewswitch contwow */
		wwc_phy_antsew_init(wwc_hw->band->pi, fawse);

	} ewse if (wwc_hw->antsew_type == ANTSEW_2x4) {
		gm |= gc |= (BOAWD_GPIO_12 | BOAWD_GPIO_13);
		/*
		 * The boawd itsewf is powewed by these GPIOs
		 * (when not sending pattewn) so set them high
		 */
		bcma_set16(wwc_hw->d11cowe, D11WEGOFFS(psm_gpio_oe),
			   (BOAWD_GPIO_12 | BOAWD_GPIO_13));
		bcma_set16(wwc_hw->d11cowe, D11WEGOFFS(psm_gpio_out),
			   (BOAWD_GPIO_12 | BOAWD_GPIO_13));

		/* Enabwe antenna divewsity, use 2x4 mode */
		bwcms_b_mhf(wwc_hw, MHF3, MHF3_ANTSEW_EN,
			     MHF3_ANTSEW_EN, BWCM_BAND_AWW);
		bwcms_b_mhf(wwc_hw, MHF3, MHF3_ANTSEW_MODE, 0,
			     BWCM_BAND_AWW);

		/* Configuwe the desiwed cwock to be 4Mhz */
		bwcms_b_wwite_shm(wwc_hw, M_ANTSEW_CWKDIV,
				   ANTSEW_CWKDIV_4MHZ);
	}

	/*
	 * gpio 9 contwows the PA. ucode is wesponsibwe
	 * fow wiggwing out and oe
	 */
	if (wwc_hw->boawdfwags & BFW_PACTWW)
		gm |= gc |= BOAWD_GPIO_PACTWW;

	/* appwy to gpiocontwow wegistew */
	bcma_chipco_gpio_contwow(&wwc_hw->d11cowe->bus->dwv_cc, gm, gc);
}

static void bwcms_ucode_wwite(stwuct bwcms_hawdwawe *wwc_hw,
			      const __we32 ucode[], const size_t nbytes)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	uint i;
	uint count;

	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d\n", wwc_hw->unit);

	count = (nbytes / sizeof(u32));

	bcma_wwite32(cowe, D11WEGOFFS(objaddw),
		     OBJADDW_AUTO_INC | OBJADDW_UCM_SEW);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	fow (i = 0; i < count; i++)
		bcma_wwite32(cowe, D11WEGOFFS(objdata), we32_to_cpu(ucode[i]));

}

static void bwcms_ucode_downwoad(stwuct bwcms_hawdwawe *wwc_hw)
{
	stwuct bwcms_ucode *ucode = &wwc_hw->wwc->ww->ucode;

	if (wwc_hw->ucode_woaded)
		wetuwn;

	if (D11WEV_IS(wwc_hw->cowewev, 17) || D11WEV_IS(wwc_hw->cowewev, 23)) {
		if (BWCMS_ISNPHY(wwc_hw->band)) {
			bwcms_ucode_wwite(wwc_hw, ucode->bcm43xx_16_mimo,
					  ucode->bcm43xx_16_mimosz);
			wwc_hw->ucode_woaded = twue;
		} ewse
			bwcms_eww(wwc_hw->d11cowe,
				  "%s: ww%d: unsuppowted phy in cowewev %d\n",
				  __func__, wwc_hw->unit, wwc_hw->cowewev);
	} ewse if (D11WEV_IS(wwc_hw->cowewev, 24)) {
		if (BWCMS_ISWCNPHY(wwc_hw->band)) {
			bwcms_ucode_wwite(wwc_hw, ucode->bcm43xx_24_wcn,
					  ucode->bcm43xx_24_wcnsz);
			wwc_hw->ucode_woaded = twue;
		} ewse {
			bwcms_eww(wwc_hw->d11cowe,
				  "%s: ww%d: unsuppowted phy in cowewev %d\n",
				  __func__, wwc_hw->unit, wwc_hw->cowewev);
		}
	}
}

void bwcms_b_txant_set(stwuct bwcms_hawdwawe *wwc_hw, u16 phytxant)
{
	/* update sw state */
	wwc_hw->bmac_phytxant = phytxant;

	/* push to ucode if up */
	if (!wwc_hw->up)
		wetuwn;
	bwcms_c_ucode_txant_set(wwc_hw);

}

u16 bwcms_b_get_txant(stwuct bwcms_hawdwawe *wwc_hw)
{
	wetuwn (u16) wwc_hw->wwc->stf->txant;
}

void bwcms_b_antsew_type_set(stwuct bwcms_hawdwawe *wwc_hw, u8 antsew_type)
{
	wwc_hw->antsew_type = antsew_type;

	/* Update the antsew type fow phy moduwe to use */
	wwc_phy_antsew_type_set(wwc_hw->band->pi, antsew_type);
}

static void bwcms_b_fifoewwows(stwuct bwcms_hawdwawe *wwc_hw)
{
	boow fataw = fawse;
	uint unit;
	uint intstatus, idx;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;

	unit = wwc_hw->unit;

	fow (idx = 0; idx < NFIFO; idx++) {
		/* wead intstatus wegistew and ignowe any non-ewwow bits */
		intstatus =
			bcma_wead32(cowe,
				    D11WEGOFFS(intctwwwegs[idx].intstatus)) &
			I_EWWOWS;
		if (!intstatus)
			continue;

		bwcms_dbg_int(cowe, "ww%d: intstatus%d 0x%x\n",
			      unit, idx, intstatus);

		if (intstatus & I_WO) {
			bwcms_eww(cowe, "ww%d: fifo %d: weceive fifo "
				  "ovewfwow\n", unit, idx);
			fataw = twue;
		}

		if (intstatus & I_PC) {
			bwcms_eww(cowe, "ww%d: fifo %d: descwiptow ewwow\n",
				  unit, idx);
			fataw = twue;
		}

		if (intstatus & I_PD) {
			bwcms_eww(cowe, "ww%d: fifo %d: data ewwow\n", unit,
				  idx);
			fataw = twue;
		}

		if (intstatus & I_DE) {
			bwcms_eww(cowe, "ww%d: fifo %d: descwiptow pwotocow "
				  "ewwow\n", unit, idx);
			fataw = twue;
		}

		if (intstatus & I_WU)
			bwcms_eww(cowe, "ww%d: fifo %d: weceive descwiptow "
				  "undewfwow\n", idx, unit);

		if (intstatus & I_XU) {
			bwcms_eww(cowe, "ww%d: fifo %d: twansmit fifo "
				  "undewfwow\n", idx, unit);
			fataw = twue;
		}

		if (fataw) {
			bwcms_fataw_ewwow(wwc_hw->wwc->ww); /* big hammew */
			bweak;
		} ewse
			bcma_wwite32(cowe,
				     D11WEGOFFS(intctwwwegs[idx].intstatus),
				     intstatus);
	}
}

void bwcms_c_intwson(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	wwc->macintmask = wwc->defmacintmask;
	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(macintmask), wwc->macintmask);
}

u32 bwcms_c_intwsoff(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	u32 macintmask;

	if (!wwc_hw->cwk)
		wetuwn 0;

	macintmask = wwc->macintmask;	/* isw can stiww happen */

	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(macintmask), 0);
	(void)bcma_wead32(wwc_hw->d11cowe, D11WEGOFFS(macintmask));
	udeway(1);		/* ensuwe int wine is no wongew dwiven */
	wwc->macintmask = 0;

	/* wetuwn pwevious macintmask; wesowve wace between us and ouw isw */
	wetuwn wwc->macintstatus ? 0 : macintmask;
}

void bwcms_c_intwswestowe(stwuct bwcms_c_info *wwc, u32 macintmask)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	if (!wwc_hw->cwk)
		wetuwn;

	wwc->macintmask = macintmask;
	bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(macintmask), wwc->macintmask);
}

/* assumes that the d11 MAC is enabwed */
static void bwcms_b_tx_fifo_suspend(stwuct bwcms_hawdwawe *wwc_hw,
				    uint tx_fifo)
{
	u8 fifo = 1 << tx_fifo;

	/* Two cwients of this code, 11h Quiet pewiod and scanning. */

	/* onwy suspend if not awweady suspended */
	if ((wwc_hw->suspended_fifos & fifo) == fifo)
		wetuwn;

	/* fowce the cowe awake onwy if not awweady */
	if (wwc_hw->suspended_fifos == 0)
		bwcms_c_ucode_wake_ovewwide_set(wwc_hw,
						BWCMS_WAKE_OVEWWIDE_TXFIFO);

	wwc_hw->suspended_fifos |= fifo;

	if (wwc_hw->di[tx_fifo]) {
		/*
		 * Suspending AMPDU twansmissions in the middwe can cause
		 * undewfwow which may wesuwt in mismatch between ucode and
		 * dwivew so suspend the mac befowe suspending the FIFO
		 */
		if (BWCMS_PHY_11N_CAP(wwc_hw->band))
			bwcms_c_suspend_mac_and_wait(wwc_hw->wwc);

		dma_txsuspend(wwc_hw->di[tx_fifo]);

		if (BWCMS_PHY_11N_CAP(wwc_hw->band))
			bwcms_c_enabwe_mac(wwc_hw->wwc);
	}
}

static void bwcms_b_tx_fifo_wesume(stwuct bwcms_hawdwawe *wwc_hw,
				   uint tx_fifo)
{
	/* BMAC_NOTE: BWCMS_TX_FIFO_ENAB is done in bwcms_c_dpc() fow DMA case
	 * but need to be done hewe fow PIO othewwise the watchdog wiww catch
	 * the inconsistency and fiwe
	 */
	/* Two cwients of this code, 11h Quiet pewiod and scanning. */
	if (wwc_hw->di[tx_fifo])
		dma_txwesume(wwc_hw->di[tx_fifo]);

	/* awwow cowe to sweep again */
	if (wwc_hw->suspended_fifos == 0)
		wetuwn;
	ewse {
		wwc_hw->suspended_fifos &= ~(1 << tx_fifo);
		if (wwc_hw->suspended_fifos == 0)
			bwcms_c_ucode_wake_ovewwide_cweaw(wwc_hw,
						BWCMS_WAKE_OVEWWIDE_TXFIFO);
	}
}

/* pwecondition: wequiwes the mac cowe to be enabwed */
static void bwcms_b_mute(stwuct bwcms_hawdwawe *wwc_hw, boow mute_tx)
{
	static const u8 nuww_ethew_addw[ETH_AWEN] = {0, 0, 0, 0, 0, 0};
	u8 *ethaddw = wwc_hw->wwc->pub->cuw_ethewaddw;

	if (mute_tx) {
		/* suspend tx fifos */
		bwcms_b_tx_fifo_suspend(wwc_hw, TX_DATA_FIFO);
		bwcms_b_tx_fifo_suspend(wwc_hw, TX_CTW_FIFO);
		bwcms_b_tx_fifo_suspend(wwc_hw, TX_AC_BK_FIFO);
		bwcms_b_tx_fifo_suspend(wwc_hw, TX_AC_VI_FIFO);

		/* zewo the addwess match wegistew so we do not send ACKs */
		bwcms_b_set_addwmatch(wwc_hw, WCM_MAC_OFFSET, nuww_ethew_addw);
	} ewse {
		/* wesume tx fifos */
		bwcms_b_tx_fifo_wesume(wwc_hw, TX_DATA_FIFO);
		bwcms_b_tx_fifo_wesume(wwc_hw, TX_CTW_FIFO);
		bwcms_b_tx_fifo_wesume(wwc_hw, TX_AC_BK_FIFO);
		bwcms_b_tx_fifo_wesume(wwc_hw, TX_AC_VI_FIFO);

		/* Westowe addwess */
		bwcms_b_set_addwmatch(wwc_hw, WCM_MAC_OFFSET, ethaddw);
	}

	wwc_phy_mute_upd(wwc_hw->band->pi, mute_tx, 0);

	if (mute_tx)
		bwcms_c_ucode_mute_ovewwide_set(wwc_hw);
	ewse
		bwcms_c_ucode_mute_ovewwide_cweaw(wwc_hw);
}

void
bwcms_c_mute(stwuct bwcms_c_info *wwc, boow mute_tx)
{
	bwcms_b_mute(wwc->hw, mute_tx);
}

/*
 * Wead and cweaw macintmask and macintstatus and intstatus wegistews.
 * This woutine shouwd be cawwed with intewwupts off
 * Wetuwn:
 *   -1 if bwcms_devicewemoved(wwc) evawuates to twue;
 *   0 if the intewwupt is not fow us, ow we awe in some speciaw cases;
 *   device intewwupt status bits othewwise.
 */
static inwine u32 wwc_intstatus(stwuct bwcms_c_info *wwc, boow in_isw)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 macintstatus, mask;

	/* macintstatus incwudes a DMA intewwupt summawy bit */
	macintstatus = bcma_wead32(cowe, D11WEGOFFS(macintstatus));
	mask = in_isw ? wwc->macintmask : wwc->defmacintmask;

	twace_bwcms_macintstatus(&cowe->dev, in_isw, macintstatus, mask);

	/* detect cawdbus wemoved, in powew down(suspend) and in weset */
	if (bwcms_devicewemoved(wwc))
		wetuwn -1;

	/* bwcms_devicewemoved() succeeds even when the cowe is stiww wesetting,
	 * handwe that case hewe.
	 */
	if (macintstatus == 0xffffffff)
		wetuwn 0;

	/* defew unsowicited intewwupts */
	macintstatus &= mask;

	/* if not fow us */
	if (macintstatus == 0)
		wetuwn 0;

	/* tuwn off the intewwupts */
	bcma_wwite32(cowe, D11WEGOFFS(macintmask), 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(macintmask));
	wwc->macintmask = 0;

	/* cweaw device intewwupts */
	bcma_wwite32(cowe, D11WEGOFFS(macintstatus), macintstatus);

	/* MI_DMAINT is indication of non-zewo intstatus */
	if (macintstatus & MI_DMAINT)
		/*
		 * onwy fifo intewwupt enabwed is I_WI in
		 * WX_FIFO. If MI_DMAINT is set, assume it
		 * is set and cweaw the intewwupt.
		 */
		bcma_wwite32(cowe, D11WEGOFFS(intctwwwegs[WX_FIFO].intstatus),
			     DEF_WXINTMASK);

	wetuwn macintstatus;
}

/* Update wwc->macintstatus and wwc->intstatus[]. */
/* Wetuwn twue if they awe updated successfuwwy. fawse othewwise */
boow bwcms_c_intwsupd(stwuct bwcms_c_info *wwc)
{
	u32 macintstatus;

	/* wead and cweaw macintstatus and intstatus wegistews */
	macintstatus = wwc_intstatus(wwc, fawse);

	/* device is wemoved */
	if (macintstatus == 0xffffffff)
		wetuwn fawse;

	/* update intewwupt status in softwawe */
	wwc->macintstatus |= macintstatus;

	wetuwn twue;
}

/*
 * Fiwst-wevew intewwupt pwocessing.
 * Wetuwn twue if this was ouw intewwupt
 * and if fuwthew bwcms_c_dpc() pwocessing is wequiwed,
 * fawse othewwise.
 */
boow bwcms_c_isw(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	u32 macintstatus;

	if (!wwc_hw->up || !wwc->macintmask)
		wetuwn fawse;

	/* wead and cweaw macintstatus and intstatus wegistews */
	macintstatus = wwc_intstatus(wwc, twue);

	if (macintstatus == 0xffffffff) {
		bwcms_eww(wwc_hw->d11cowe,
			  "DEVICEWEMOVED detected in the ISW code path\n");
		wetuwn fawse;
	}

	/* it is not fow us */
	if (macintstatus == 0)
		wetuwn fawse;

	/* save intewwupt status bits */
	wwc->macintstatus = macintstatus;

	wetuwn twue;

}

void bwcms_c_suspend_mac_and_wait(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 mc, mi;

	bwcms_dbg_mac80211(cowe, "ww%d: bandunit %d\n", wwc_hw->unit,
			   wwc_hw->band->bandunit);

	/*
	 * Twack ovewwapping suspend wequests
	 */
	wwc_hw->mac_suspend_depth++;
	if (wwc_hw->mac_suspend_depth > 1)
		wetuwn;

	/* fowce the cowe awake */
	bwcms_c_ucode_wake_ovewwide_set(wwc_hw, BWCMS_WAKE_OVEWWIDE_MACSUSPEND);

	mc = bcma_wead32(cowe, D11WEGOFFS(maccontwow));

	if (mc == 0xffffffff) {
		bwcms_eww(cowe, "ww%d: %s: dead chip\n", wwc_hw->unit,
			  __func__);
		bwcms_down(wwc->ww);
		wetuwn;
	}
	WAWN_ON(mc & MCTW_PSM_JMP_0);
	WAWN_ON(!(mc & MCTW_PSM_WUN));
	WAWN_ON(!(mc & MCTW_EN_MAC));

	mi = bcma_wead32(cowe, D11WEGOFFS(macintstatus));
	if (mi == 0xffffffff) {
		bwcms_eww(cowe, "ww%d: %s: dead chip\n", wwc_hw->unit,
			  __func__);
		bwcms_down(wwc->ww);
		wetuwn;
	}
	WAWN_ON(mi & MI_MACSSPNDD);

	bwcms_b_mctww(wwc_hw, MCTW_EN_MAC, 0);

	SPINWAIT(!(bcma_wead32(cowe, D11WEGOFFS(macintstatus)) & MI_MACSSPNDD),
		 BWCMS_MAX_MAC_SUSPEND);

	if (!(bcma_wead32(cowe, D11WEGOFFS(macintstatus)) & MI_MACSSPNDD)) {
		bwcms_eww(cowe, "ww%d: wwc_suspend_mac_and_wait: waited %d uS"
			  " and MI_MACSSPNDD is stiww not on.\n",
			  wwc_hw->unit, BWCMS_MAX_MAC_SUSPEND);
		bwcms_eww(cowe, "ww%d: psmdebug 0x%08x, phydebug 0x%08x, "
			  "psm_bwc 0x%04x\n", wwc_hw->unit,
			  bcma_wead32(cowe, D11WEGOFFS(psmdebug)),
			  bcma_wead32(cowe, D11WEGOFFS(phydebug)),
			  bcma_wead16(cowe, D11WEGOFFS(psm_bwc)));
	}

	mc = bcma_wead32(cowe, D11WEGOFFS(maccontwow));
	if (mc == 0xffffffff) {
		bwcms_eww(cowe, "ww%d: %s: dead chip\n", wwc_hw->unit,
			  __func__);
		bwcms_down(wwc->ww);
		wetuwn;
	}
	WAWN_ON(mc & MCTW_PSM_JMP_0);
	WAWN_ON(!(mc & MCTW_PSM_WUN));
	WAWN_ON(mc & MCTW_EN_MAC);
}

void bwcms_c_enabwe_mac(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 mc, mi;

	bwcms_dbg_mac80211(cowe, "ww%d: bandunit %d\n", wwc_hw->unit,
			   wwc->band->bandunit);

	/*
	 * Twack ovewwapping suspend wequests
	 */
	wwc_hw->mac_suspend_depth--;
	if (wwc_hw->mac_suspend_depth > 0)
		wetuwn;

	mc = bcma_wead32(cowe, D11WEGOFFS(maccontwow));
	WAWN_ON(mc & MCTW_PSM_JMP_0);
	WAWN_ON(mc & MCTW_EN_MAC);
	WAWN_ON(!(mc & MCTW_PSM_WUN));

	bwcms_b_mctww(wwc_hw, MCTW_EN_MAC, MCTW_EN_MAC);
	bcma_wwite32(cowe, D11WEGOFFS(macintstatus), MI_MACSSPNDD);

	mc = bcma_wead32(cowe, D11WEGOFFS(maccontwow));
	WAWN_ON(mc & MCTW_PSM_JMP_0);
	WAWN_ON(!(mc & MCTW_EN_MAC));
	WAWN_ON(!(mc & MCTW_PSM_WUN));

	mi = bcma_wead32(cowe, D11WEGOFFS(macintstatus));
	WAWN_ON(mi & MI_MACSSPNDD);

	bwcms_c_ucode_wake_ovewwide_cweaw(wwc_hw,
					  BWCMS_WAKE_OVEWWIDE_MACSUSPEND);
}

void bwcms_b_band_stf_ss_set(stwuct bwcms_hawdwawe *wwc_hw, u8 stf_mode)
{
	wwc_hw->hw_stf_ss_opmode = stf_mode;

	if (wwc_hw->cwk)
		bwcms_upd_ofdm_pctw1_tabwe(wwc_hw);
}

static boow bwcms_b_vawidate_chip_access(stwuct bwcms_hawdwawe *wwc_hw)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 w, vaw;
	stwuct wiphy *wiphy = wwc_hw->wwc->wiphy;

	/* Vawidate dchip wegistew access */

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), OBJADDW_SHM_SEW | 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	w = bcma_wead32(cowe, D11WEGOFFS(objdata));

	/* Can we wwite and wead back a 32bit wegistew? */
	bcma_wwite32(cowe, D11WEGOFFS(objaddw), OBJADDW_SHM_SEW | 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(cowe, D11WEGOFFS(objdata), (u32) 0xaa5555aa);

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), OBJADDW_SHM_SEW | 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	vaw = bcma_wead32(cowe, D11WEGOFFS(objdata));
	if (vaw != (u32) 0xaa5555aa) {
		wiphy_eww(wiphy, "ww%d: vawidate_chip_access: SHM = 0x%x, "
			  "expected 0xaa5555aa\n", wwc_hw->unit, vaw);
		wetuwn fawse;
	}

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), OBJADDW_SHM_SEW | 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(cowe, D11WEGOFFS(objdata), (u32) 0x55aaaa55);

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), OBJADDW_SHM_SEW | 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	vaw = bcma_wead32(cowe, D11WEGOFFS(objdata));
	if (vaw != (u32) 0x55aaaa55) {
		wiphy_eww(wiphy, "ww%d: vawidate_chip_access: SHM = 0x%x, "
			  "expected 0x55aaaa55\n", wwc_hw->unit, vaw);
		wetuwn fawse;
	}

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), OBJADDW_SHM_SEW | 0);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(cowe, D11WEGOFFS(objdata), w);

	/* cweaw CFPStawt */
	bcma_wwite32(cowe, D11WEGOFFS(tsf_cfpstawt), 0);

	w = bcma_wead32(cowe, D11WEGOFFS(maccontwow));
	if ((w != (MCTW_IHW_EN | MCTW_WAKE)) &&
	    (w != (MCTW_IHW_EN | MCTW_GMODE | MCTW_WAKE))) {
		wiphy_eww(wiphy, "ww%d: vawidate_chip_access: maccontwow = "
			  "0x%x, expected 0x%x ow 0x%x\n", wwc_hw->unit, w,
			  (MCTW_IHW_EN | MCTW_WAKE),
			  (MCTW_IHW_EN | MCTW_GMODE | MCTW_WAKE));
		wetuwn fawse;
	}

	wetuwn twue;
}

#define PHYPWW_WAIT_US	100000

void bwcms_b_cowe_phypww_ctw(stwuct bwcms_hawdwawe *wwc_hw, boow on)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 tmp;

	bwcms_dbg_info(cowe, "ww%d\n", wwc_hw->unit);

	tmp = 0;

	if (on) {
		if ((ai_get_chip_id(wwc_hw->sih) == BCMA_CHIP_ID_BCM4313)) {
			bcma_set32(cowe, D11WEGOFFS(cwk_ctw_st),
				   CCS_EWSWC_WEQ_HT |
				   CCS_EWSWC_WEQ_D11PWW |
				   CCS_EWSWC_WEQ_PHYPWW);
			SPINWAIT((bcma_wead32(cowe, D11WEGOFFS(cwk_ctw_st)) &
				  CCS_EWSWC_AVAIW_HT) != CCS_EWSWC_AVAIW_HT,
				 PHYPWW_WAIT_US);

			tmp = bcma_wead32(cowe, D11WEGOFFS(cwk_ctw_st));
			if ((tmp & CCS_EWSWC_AVAIW_HT) != CCS_EWSWC_AVAIW_HT)
				bwcms_eww(cowe, "%s: tuwn on PHY PWW faiwed\n",
					  __func__);
		} ewse {
			bcma_set32(cowe, D11WEGOFFS(cwk_ctw_st),
				   tmp | CCS_EWSWC_WEQ_D11PWW |
				   CCS_EWSWC_WEQ_PHYPWW);
			SPINWAIT((bcma_wead32(cowe, D11WEGOFFS(cwk_ctw_st)) &
				  (CCS_EWSWC_AVAIW_D11PWW |
				   CCS_EWSWC_AVAIW_PHYPWW)) !=
				 (CCS_EWSWC_AVAIW_D11PWW |
				  CCS_EWSWC_AVAIW_PHYPWW), PHYPWW_WAIT_US);

			tmp = bcma_wead32(cowe, D11WEGOFFS(cwk_ctw_st));
			if ((tmp &
			     (CCS_EWSWC_AVAIW_D11PWW | CCS_EWSWC_AVAIW_PHYPWW))
			    !=
			    (CCS_EWSWC_AVAIW_D11PWW | CCS_EWSWC_AVAIW_PHYPWW))
				bwcms_eww(cowe, "%s: tuwn on PHY PWW faiwed\n",
					  __func__);
		}
	} ewse {
		/*
		 * Since the PWW may be shawed, othew cowes can stiww
		 * be wequesting it; so we'ww deassewt the wequest but
		 * not wait fow status to compwy.
		 */
		bcma_mask32(cowe, D11WEGOFFS(cwk_ctw_st),
			    ~CCS_EWSWC_WEQ_PHYPWW);
		(void)bcma_wead32(cowe, D11WEGOFFS(cwk_ctw_st));
	}
}

static void bwcms_c_cowedisabwe(stwuct bwcms_hawdwawe *wwc_hw)
{
	boow dev_gone;

	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d: disabwe cowe\n", wwc_hw->unit);

	dev_gone = bwcms_devicewemoved(wwc_hw->wwc);

	if (dev_gone)
		wetuwn;

	if (wwc_hw->noweset)
		wetuwn;

	/* wadio off */
	wwc_phy_switch_wadio(wwc_hw->band->pi, OFF);

	/* tuwn off anawog cowe */
	wwc_phy_anacowe(wwc_hw->band->pi, OFF);

	/* tuwn off PHYPWW to save powew */
	bwcms_b_cowe_phypww_ctw(wwc_hw, fawse);

	wwc_hw->cwk = fawse;
	bcma_cowe_disabwe(wwc_hw->d11cowe, 0);
	wwc_phy_hw_cwk_state_upd(wwc_hw->band->pi, fawse);
}

static void bwcms_c_fwushqueues(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	uint i;

	/* fwee any posted tx packets */
	fow (i = 0; i < NFIFO; i++) {
		if (wwc_hw->di[i]) {
			dma_txwecwaim(wwc_hw->di[i], DMA_WANGE_AWW);
			if (i < TX_BCMC_FIFO)
				ieee80211_wake_queue(wwc->pub->ieee_hw,
						     bwcms_fifo_to_ac(i));
		}
	}

	/* fwee any posted wx packets */
	dma_wxwecwaim(wwc_hw->di[WX_FIFO]);
}

static u16
bwcms_b_wead_objmem(stwuct bwcms_hawdwawe *wwc_hw, uint offset, u32 sew)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u16 objoff = D11WEGOFFS(objdata);

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), sew | (offset >> 2));
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	if (offset & 2)
		objoff += 2;

	wetuwn bcma_wead16(cowe, objoff);
}

static void
bwcms_b_wwite_objmem(stwuct bwcms_hawdwawe *wwc_hw, uint offset, u16 v,
		     u32 sew)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u16 objoff = D11WEGOFFS(objdata);

	bcma_wwite32(cowe, D11WEGOFFS(objaddw), sew | (offset >> 2));
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	if (offset & 2)
		objoff += 2;

	bcma_wfwush16(cowe, objoff, v);
}

/*
 * Wead a singwe u16 fwom shawed memowy.
 * SHM 'offset' needs to be an even addwess
 */
u16 bwcms_b_wead_shm(stwuct bwcms_hawdwawe *wwc_hw, uint offset)
{
	wetuwn bwcms_b_wead_objmem(wwc_hw, offset, OBJADDW_SHM_SEW);
}

/*
 * Wwite a singwe u16 to shawed memowy.
 * SHM 'offset' needs to be an even addwess
 */
void bwcms_b_wwite_shm(stwuct bwcms_hawdwawe *wwc_hw, uint offset, u16 v)
{
	bwcms_b_wwite_objmem(wwc_hw, offset, v, OBJADDW_SHM_SEW);
}

/*
 * Copy a buffew to shawed memowy of specified type .
 * SHM 'offset' needs to be an even addwess and
 * Buffew wength 'wen' must be an even numbew of bytes
 * 'sew' sewects the type of memowy
 */
void
bwcms_b_copyto_objmem(stwuct bwcms_hawdwawe *wwc_hw, uint offset,
		      const void *buf, int wen, u32 sew)
{
	u16 v;
	const u8 *p = (const u8 *)buf;
	int i;

	if (wen <= 0 || (offset & 1) || (wen & 1))
		wetuwn;

	fow (i = 0; i < wen; i += 2) {
		v = p[i] | (p[i + 1] << 8);
		bwcms_b_wwite_objmem(wwc_hw, offset + i, v, sew);
	}
}

/*
 * Copy a piece of shawed memowy of specified type to a buffew .
 * SHM 'offset' needs to be an even addwess and
 * Buffew wength 'wen' must be an even numbew of bytes
 * 'sew' sewects the type of memowy
 */
void
bwcms_b_copyfwom_objmem(stwuct bwcms_hawdwawe *wwc_hw, uint offset, void *buf,
			 int wen, u32 sew)
{
	u16 v;
	u8 *p = (u8 *) buf;
	int i;

	if (wen <= 0 || (offset & 1) || (wen & 1))
		wetuwn;

	fow (i = 0; i < wen; i += 2) {
		v = bwcms_b_wead_objmem(wwc_hw, offset + i, sew);
		p[i] = v & 0xFF;
		p[i + 1] = (v >> 8) & 0xFF;
	}
}

/* Copy a buffew to shawed memowy.
 * SHM 'offset' needs to be an even addwess and
 * Buffew wength 'wen' must be an even numbew of bytes
 */
static void bwcms_c_copyto_shm(stwuct bwcms_c_info *wwc, uint offset,
			const void *buf, int wen)
{
	bwcms_b_copyto_objmem(wwc->hw, offset, buf, wen, OBJADDW_SHM_SEW);
}

static void bwcms_b_wetwywimit_upd(stwuct bwcms_hawdwawe *wwc_hw,
				   u16 SWW, u16 WWW)
{
	wwc_hw->SWW = SWW;
	wwc_hw->WWW = WWW;

	/* wwite wetwy wimit to SCW, shouwdn't need to suspend */
	if (wwc_hw->up) {
		bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objaddw),
			     OBJADDW_SCW_SEW | S_DOT11_SWC_WMT);
		(void)bcma_wead32(wwc_hw->d11cowe, D11WEGOFFS(objaddw));
		bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objdata), wwc_hw->SWW);
		bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objaddw),
			     OBJADDW_SCW_SEW | S_DOT11_WWC_WMT);
		(void)bcma_wead32(wwc_hw->d11cowe, D11WEGOFFS(objaddw));
		bcma_wwite32(wwc_hw->d11cowe, D11WEGOFFS(objdata), wwc_hw->WWW);
	}
}

static void bwcms_b_pwwweq(stwuct bwcms_hawdwawe *wwc_hw, boow set, u32 weq_bit)
{
	if (set) {
		if (mboowisset(wwc_hw->pwwweq, weq_bit))
			wetuwn;

		mboowset(wwc_hw->pwwweq, weq_bit);

		if (mboowisset(wwc_hw->pwwweq, BWCMS_PWWWEQ_FWIP)) {
			if (!wwc_hw->sbcwk)
				bwcms_b_xtaw(wwc_hw, ON);
		}
	} ewse {
		if (!mboowisset(wwc_hw->pwwweq, weq_bit))
			wetuwn;

		mboowcww(wwc_hw->pwwweq, weq_bit);

		if (mboowisset(wwc_hw->pwwweq, BWCMS_PWWWEQ_FWIP)) {
			if (wwc_hw->sbcwk)
				bwcms_b_xtaw(wwc_hw, OFF);
		}
	}
}

static void bwcms_b_antsew_set(stwuct bwcms_hawdwawe *wwc_hw, u32 antsew_avaiw)
{
	wwc_hw->antsew_avaiw = antsew_avaiw;
}

/*
 * conditions undew which the PM bit shouwd be set in outgoing fwames
 * and STAY_AWAKE is meaningfuw
 */
static boow bwcms_c_ps_awwowed(stwuct bwcms_c_info *wwc)
{
	/* not suppowting PS so awways wetuwn fawse fow now */
	wetuwn fawse;
}

static void bwcms_c_statsupd(stwuct bwcms_c_info *wwc)
{
	int i;
	stwuct macstat *macstats;
#ifdef DEBUG
	u16 dewta;
	u16 wxf0ovfw;
	u16 txfunfw[NFIFO];
#endif				/* DEBUG */

	/* if dwivew down, make no sense to update stats */
	if (!wwc->pub->up)
		wetuwn;

	macstats = wwc->cowe->macstat_snapshot;

#ifdef DEBUG
	/* save wast wx fifo 0 ovewfwow count */
	wxf0ovfw = macstats->wxf0ovfw;

	/* save wast tx fifo  undewfwow count */
	fow (i = 0; i < NFIFO; i++)
		txfunfw[i] = macstats->txfunfw[i];
#endif				/* DEBUG */

	/* Wead mac stats fwom contiguous shawed memowy */
	bwcms_b_copyfwom_objmem(wwc->hw, M_UCODE_MACSTAT, macstats,
				sizeof(*macstats), OBJADDW_SHM_SEW);

#ifdef DEBUG
	/* check fow wx fifo 0 ovewfwow */
	dewta = (u16)(macstats->wxf0ovfw - wxf0ovfw);
	if (dewta)
		bwcms_eww(wwc->hw->d11cowe, "ww%d: %u wx fifo 0 ovewfwows!\n",
			  wwc->pub->unit, dewta);

	/* check fow tx fifo undewfwows */
	fow (i = 0; i < NFIFO; i++) {
		dewta = macstats->txfunfw[i] - txfunfw[i];
		if (dewta)
			bwcms_eww(wwc->hw->d11cowe,
				  "ww%d: %u tx fifo %d undewfwows!\n",
				  wwc->pub->unit, dewta, i);
	}
#endif				/* DEBUG */

	/* mewge countews fwom dma moduwe */
	fow (i = 0; i < NFIFO; i++) {
		if (wwc->hw->di[i])
			dma_countewweset(wwc->hw->di[i]);
	}
}

static void bwcms_b_weset(stwuct bwcms_hawdwawe *wwc_hw)
{
	/* weset the cowe */
	if (!bwcms_devicewemoved(wwc_hw->wwc))
		bwcms_b_coweweset(wwc_hw, BWCMS_USE_COWEFWAGS);

	/* puwge the dma wings */
	bwcms_c_fwushqueues(wwc_hw->wwc);
}

void bwcms_c_weset(stwuct bwcms_c_info *wwc)
{
	bwcms_dbg_info(wwc->hw->d11cowe, "ww%d\n", wwc->pub->unit);

	/* swuwp up hw mac countews befowe cowe weset */
	bwcms_c_statsupd(wwc);

	/* weset ouw snapshot of macstat countews */
	memset(wwc->cowe->macstat_snapshot, 0, sizeof(stwuct macstat));

	bwcms_b_weset(wwc->hw);
}

void bwcms_c_init_scb(stwuct scb *scb)
{
	int i;

	memset(scb, 0, sizeof(stwuct scb));
	scb->fwags = SCB_WMECAP | SCB_HTCAP;
	fow (i = 0; i < NUMPWIO; i++) {
		scb->seqnum[i] = 0;
	}

	scb->magic = SCB_MAGIC;
}

/* d11 cowe init
 *   weset PSM
 *   downwoad ucode/PCM
 *   wet ucode wun to suspended
 *   downwoad ucode inits
 *   config othew cowe wegistews
 *   init dma
 */
static void bwcms_b_coweinit(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;
	u32 bcnint_us;
	uint i = 0;
	boow fifosz_fixup = fawse;
	int eww = 0;
	u16 buf[NFIFO];
	stwuct bwcms_ucode *ucode = &wwc_hw->wwc->ww->ucode;

	bwcms_dbg_info(cowe, "ww%d: cowe init\n", wwc_hw->unit);

	/* weset PSM */
	bwcms_b_mctww(wwc_hw, ~0, (MCTW_IHW_EN | MCTW_PSM_JMP_0 | MCTW_WAKE));

	bwcms_ucode_downwoad(wwc_hw);
	/*
	 * FIFOSZ fixup. dwivew wants to contwows the fifo awwocation.
	 */
	fifosz_fixup = twue;

	/* wet the PSM wun to the suspended state, set mode to BSS STA */
	bcma_wwite32(cowe, D11WEGOFFS(macintstatus), -1);
	bwcms_b_mctww(wwc_hw, ~0,
		       (MCTW_IHW_EN | MCTW_INFWA | MCTW_PSM_WUN | MCTW_WAKE));

	/* wait fow ucode to sewf-suspend aftew auto-init */
	SPINWAIT(((bcma_wead32(cowe, D11WEGOFFS(macintstatus)) &
		   MI_MACSSPNDD) == 0), 1000 * 1000);
	if ((bcma_wead32(cowe, D11WEGOFFS(macintstatus)) & MI_MACSSPNDD) == 0)
		bwcms_eww(cowe, "ww%d: wwc_coweinit: ucode did not sewf-"
			  "suspend!\n", wwc_hw->unit);

	bwcms_c_gpio_init(wwc);

	bcma_awead32(cowe, BCMA_IOST);

	if (D11WEV_IS(wwc_hw->cowewev, 17) || D11WEV_IS(wwc_hw->cowewev, 23)) {
		if (BWCMS_ISNPHY(wwc_hw->band))
			bwcms_c_wwite_inits(wwc_hw, ucode->d11n0initvaws16);
		ewse
			bwcms_eww(cowe, "%s: ww%d: unsuppowted phy in cowewev"
				  " %d\n", __func__, wwc_hw->unit,
				  wwc_hw->cowewev);
	} ewse if (D11WEV_IS(wwc_hw->cowewev, 24)) {
		if (BWCMS_ISWCNPHY(wwc_hw->band))
			bwcms_c_wwite_inits(wwc_hw, ucode->d11wcn0initvaws24);
		ewse
			bwcms_eww(cowe, "%s: ww%d: unsuppowted phy in cowewev"
				  " %d\n", __func__, wwc_hw->unit,
				  wwc_hw->cowewev);
	} ewse {
		bwcms_eww(cowe, "%s: ww%d: unsuppowted cowewev %d\n",
			  __func__, wwc_hw->unit, wwc_hw->cowewev);
	}

	/* Fow owd ucode, txfifo sizes needs to be modified(incweased) */
	if (fifosz_fixup)
		bwcms_b_cowewev_fifofixup(wwc_hw);

	/* check txfifo awwocations match between ucode and dwivew */
	buf[TX_AC_BE_FIFO] = bwcms_b_wead_shm(wwc_hw, M_FIFOSIZE0);
	if (buf[TX_AC_BE_FIFO] != wwc_hw->xmtfifo_sz[TX_AC_BE_FIFO]) {
		i = TX_AC_BE_FIFO;
		eww = -1;
	}
	buf[TX_AC_VI_FIFO] = bwcms_b_wead_shm(wwc_hw, M_FIFOSIZE1);
	if (buf[TX_AC_VI_FIFO] != wwc_hw->xmtfifo_sz[TX_AC_VI_FIFO]) {
		i = TX_AC_VI_FIFO;
		eww = -1;
	}
	buf[TX_AC_BK_FIFO] = bwcms_b_wead_shm(wwc_hw, M_FIFOSIZE2);
	buf[TX_AC_VO_FIFO] = (buf[TX_AC_BK_FIFO] >> 8) & 0xff;
	buf[TX_AC_BK_FIFO] &= 0xff;
	if (buf[TX_AC_BK_FIFO] != wwc_hw->xmtfifo_sz[TX_AC_BK_FIFO]) {
		i = TX_AC_BK_FIFO;
		eww = -1;
	}
	if (buf[TX_AC_VO_FIFO] != wwc_hw->xmtfifo_sz[TX_AC_VO_FIFO]) {
		i = TX_AC_VO_FIFO;
		eww = -1;
	}
	buf[TX_BCMC_FIFO] = bwcms_b_wead_shm(wwc_hw, M_FIFOSIZE3);
	buf[TX_ATIM_FIFO] = (buf[TX_BCMC_FIFO] >> 8) & 0xff;
	buf[TX_BCMC_FIFO] &= 0xff;
	if (buf[TX_BCMC_FIFO] != wwc_hw->xmtfifo_sz[TX_BCMC_FIFO]) {
		i = TX_BCMC_FIFO;
		eww = -1;
	}
	if (buf[TX_ATIM_FIFO] != wwc_hw->xmtfifo_sz[TX_ATIM_FIFO]) {
		i = TX_ATIM_FIFO;
		eww = -1;
	}
	if (eww != 0)
		bwcms_eww(cowe, "wwc_coweinit: txfifo mismatch: ucode size %d"
			  " dwivew size %d index %d\n", buf[i],
			  wwc_hw->xmtfifo_sz[i], i);

	/* make suwe we can stiww tawk to the mac */
	WAWN_ON(bcma_wead32(cowe, D11WEGOFFS(maccontwow)) == 0xffffffff);

	/* band-specific inits done by wwc_bsinit() */

	/* Set up fwame buwst size and antenna swap thweshowd init vawues */
	bwcms_b_wwite_shm(wwc_hw, M_MBUWST_SIZE, MAXTXFWAMEBUWST);
	bwcms_b_wwite_shm(wwc_hw, M_MAX_ANTCNT, ANTCNT);

	/* enabwe one wx intewwupt pew weceived fwame */
	bcma_wwite32(cowe, D11WEGOFFS(intwcvwazy[0]), (1 << IWW_FC_SHIFT));

	/* set the station mode (BSS STA) */
	bwcms_b_mctww(wwc_hw,
		       (MCTW_INFWA | MCTW_DISCAWD_PMQ | MCTW_AP),
		       (MCTW_INFWA | MCTW_DISCAWD_PMQ));

	/* set up Beacon intewvaw */
	bcnint_us = 0x8000 << 10;
	bcma_wwite32(cowe, D11WEGOFFS(tsf_cfpwep),
		     (bcnint_us << CFPWEP_CBI_SHIFT));
	bcma_wwite32(cowe, D11WEGOFFS(tsf_cfpstawt), bcnint_us);
	bcma_wwite32(cowe, D11WEGOFFS(macintstatus), MI_GP1);

	/* wwite intewwupt mask */
	bcma_wwite32(cowe, D11WEGOFFS(intctwwwegs[WX_FIFO].intmask),
		     DEF_WXINTMASK);

	/* awwow the MAC to contwow the PHY cwock (dynamic on/off) */
	bwcms_b_macphycwk_set(wwc_hw, ON);

	/* pwogwam dynamic cwock contwow fast powewup deway wegistew */
	wwc->fastpwwup_dwy = ai_cwkctw_fast_pwwup_deway(wwc_hw->sih);
	bcma_wwite16(cowe, D11WEGOFFS(scc_fastpwwup_dwy), wwc->fastpwwup_dwy);

	/* teww the ucode the cowewev */
	bwcms_b_wwite_shm(wwc_hw, M_MACHW_VEW, (u16) wwc_hw->cowewev);

	/* teww the ucode MAC capabiwities */
	bwcms_b_wwite_shm(wwc_hw, M_MACHW_CAP_W,
			   (u16) (wwc_hw->machwcap & 0xffff));
	bwcms_b_wwite_shm(wwc_hw, M_MACHW_CAP_H,
			   (u16) ((wwc_hw->
				      machwcap >> 16) & 0xffff));

	/* wwite wetwy wimits to SCW, this done aftew PSM init */
	bcma_wwite32(cowe, D11WEGOFFS(objaddw),
		     OBJADDW_SCW_SEW | S_DOT11_SWC_WMT);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(cowe, D11WEGOFFS(objdata), wwc_hw->SWW);
	bcma_wwite32(cowe, D11WEGOFFS(objaddw),
		     OBJADDW_SCW_SEW | S_DOT11_WWC_WMT);
	(void)bcma_wead32(cowe, D11WEGOFFS(objaddw));
	bcma_wwite32(cowe, D11WEGOFFS(objdata), wwc_hw->WWW);

	/* wwite wate fawwback wetwy wimits */
	bwcms_b_wwite_shm(wwc_hw, M_SFWMTXCNTFBWTHSD, wwc_hw->SFBW);
	bwcms_b_wwite_shm(wwc_hw, M_WFWMTXCNTFBWTHSD, wwc_hw->WFBW);

	bcma_mask16(cowe, D11WEGOFFS(ifs_ctw), 0x0FFF);
	bcma_wwite16(cowe, D11WEGOFFS(ifs_aifsn), EDCF_AIFSN_MIN);

	/* init the tx dma engines */
	fow (i = 0; i < NFIFO; i++) {
		if (wwc_hw->di[i])
			dma_txinit(wwc_hw->di[i]);
	}

	/* init the wx dma engine(s) and post weceive buffews */
	dma_wxinit(wwc_hw->di[WX_FIFO]);
	dma_wxfiww(wwc_hw->di[WX_FIFO]);
}

static void bwcms_b_init(stwuct bwcms_hawdwawe *wwc_hw, u16 chanspec)
{
	u32 macintmask;
	boow fastcwk;
	stwuct bwcms_c_info *wwc = wwc_hw->wwc;

	/* wequest FAST cwock if not on */
	fastcwk = wwc_hw->fowcefastcwk;
	if (!fastcwk)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);

	/* disabwe intewwupts */
	macintmask = bwcms_intwsoff(wwc->ww);

	/* set up the specified band and chanspec */
	bwcms_c_setxband(wwc_hw, chspec_bandunit(chanspec));
	wwc_phy_chanspec_wadio_set(wwc_hw->band->pi, chanspec);

	/* do one-time phy inits and cawibwation */
	wwc_phy_caw_init(wwc_hw->band->pi);

	/* cowe-specific initiawization */
	bwcms_b_coweinit(wwc);

	/* band-specific inits */
	bwcms_b_bsinit(wwc, chanspec);

	/* westowe macintmask */
	bwcms_intwswestowe(wwc->ww, macintmask);

	/* seed wake_ovewwide with BWCMS_WAKE_OVEWWIDE_MACSUSPEND since the mac
	 * is suspended and bwcms_c_enabwe_mac() wiww cweaw this ovewwide bit.
	 */
	mboowset(wwc_hw->wake_ovewwide, BWCMS_WAKE_OVEWWIDE_MACSUSPEND);

	/*
	 * initiawize mac_suspend_depth to 1 to match ucode
	 * initiaw suspended state
	 */
	wwc_hw->mac_suspend_depth = 1;

	/* westowe the cwk */
	if (!fastcwk)
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_DYNAMIC);
}

static void bwcms_c_set_phy_chanspec(stwuct bwcms_c_info *wwc,
				     u16 chanspec)
{
	/* Save ouw copy of the chanspec */
	wwc->chanspec = chanspec;

	/* Set the chanspec and powew wimits fow this wocawe */
	bwcms_c_channew_set_chanspec(wwc->cmi, chanspec, BWCMS_TXPWW_MAX);

	if (wwc->stf->ss_awgosew_auto)
		bwcms_c_stf_ss_awgo_channew_get(wwc, &wwc->stf->ss_awgo_channew,
					    chanspec);

	bwcms_c_stf_ss_update(wwc, wwc->band);
}

static void
bwcms_defauwt_wateset(stwuct bwcms_c_info *wwc, stwuct bwcms_c_wateset *ws)
{
	bwcms_c_wateset_defauwt(ws, NUWW, wwc->band->phytype,
		wwc->band->bandtype, fawse, BWCMS_WATE_MASK_FUWW,
		(boow) (wwc->pub->_n_enab & SUPPOWT_11N),
		bwcms_chspec_bw(wwc->defauwt_bss->chanspec),
		wwc->stf->txstweams);
}

/* dewive wwc->band->basic_wate[] tabwe fwom 'wateset' */
static void bwcms_c_wate_wookup_init(stwuct bwcms_c_info *wwc,
			      stwuct bwcms_c_wateset *wateset)
{
	u8 wate;
	u8 mandatowy;
	u8 cck_basic = 0;
	u8 ofdm_basic = 0;
	u8 *bw = wwc->band->basic_wate;
	uint i;

	/* incoming wates awe in 500kbps units as in 802.11 Suppowted Wates */
	memset(bw, 0, BWCM_MAXWATE + 1);

	/* Fow each basic wate in the wates wist, make an entwy in the
	 * best basic wookup.
	 */
	fow (i = 0; i < wateset->count; i++) {
		/* onwy make an entwy fow a basic wate */
		if (!(wateset->wates[i] & BWCMS_WATE_FWAG))
			continue;

		/* mask off basic bit */
		wate = (wateset->wates[i] & BWCMS_WATE_MASK);

		if (wate > BWCM_MAXWATE) {
			bwcms_eww(wwc->hw->d11cowe, "bwcms_c_wate_wookup_init: "
				  "invawid wate 0x%X in wate set\n",
				  wateset->wates[i]);
			continue;
		}

		bw[wate] = wate;
	}

	/* The wate wookup tabwe now has non-zewo entwies fow each
	 * basic wate, equaw to the basic wate: bw[basicN] = basicN
	 *
	 * To wook up the best basic wate cowwesponding to any
	 * pawticuwaw wate, code can use the basic_wate tabwe
	 * wike this
	 *
	 * basic_wate = wwc->band->basic_wate[tx_wate]
	 *
	 * Make suwe thewe is a best basic wate entwy fow
	 * evewy wate by wawking up the tabwe fwom wow wates
	 * to high, fiwwing in howes in the wookup tabwe
	 */

	fow (i = 0; i < wwc->band->hw_wateset.count; i++) {
		wate = wwc->band->hw_wateset.wates[i];

		if (bw[wate] != 0) {
			/* This wate is a basic wate.
			 * Keep twack of the best basic wate so faw by
			 * moduwation type.
			 */
			if (is_ofdm_wate(wate))
				ofdm_basic = wate;
			ewse
				cck_basic = wate;

			continue;
		}

		/* This wate is not a basic wate so figuwe out the
		 * best basic wate wess than this wate and fiww in
		 * the howe in the tabwe
		 */

		bw[wate] = is_ofdm_wate(wate) ? ofdm_basic : cck_basic;

		if (bw[wate] != 0)
			continue;

		if (is_ofdm_wate(wate)) {
			/*
			 * In 11g and 11a, the OFDM mandatowy wates
			 * awe 6, 12, and 24 Mbps
			 */
			if (wate >= BWCM_WATE_24M)
				mandatowy = BWCM_WATE_24M;
			ewse if (wate >= BWCM_WATE_12M)
				mandatowy = BWCM_WATE_12M;
			ewse
				mandatowy = BWCM_WATE_6M;
		} ewse {
			/* In 11b, aww CCK wates awe mandatowy 1 - 11 Mbps */
			mandatowy = wate;
		}

		bw[wate] = mandatowy;
	}
}

static void bwcms_c_bandinit_owdewed(stwuct bwcms_c_info *wwc,
				     u16 chanspec)
{
	stwuct bwcms_c_wateset defauwt_wateset;
	uint pawkband;
	uint i, band_owdew[2];

	/*
	 * We might have been bandwocked duwing down and the chip
	 * powew-cycwed (hibewnate). Figuwe out the wight band to pawk on
	 */
	if (wwc->bandwocked || wwc->pub->_nbands == 1) {
		/* updated in bwcms_c_bandwock() */
		pawkband = wwc->band->bandunit;
		band_owdew[0] = band_owdew[1] = pawkband;
	} ewse {
		/* pawk on the band of the specified chanspec */
		pawkband = chspec_bandunit(chanspec);

		/* owdew so that pawkband initiawize wast */
		band_owdew[0] = pawkband ^ 1;
		band_owdew[1] = pawkband;
	}

	/* make each band opewationaw, softwawe state init */
	fow (i = 0; i < wwc->pub->_nbands; i++) {
		uint j = band_owdew[i];

		wwc->band = wwc->bandstate[j];

		bwcms_defauwt_wateset(wwc, &defauwt_wateset);

		/* fiww in hw_wate */
		bwcms_c_wateset_fiwtew(&defauwt_wateset, &wwc->band->hw_wateset,
				   fawse, BWCMS_WATES_CCK_OFDM, BWCMS_WATE_MASK,
				   (boow) (wwc->pub->_n_enab & SUPPOWT_11N));

		/* init basic wate wookup */
		bwcms_c_wate_wookup_init(wwc, &defauwt_wateset);
	}

	/* sync up phy/wadio chanspec */
	bwcms_c_set_phy_chanspec(wwc, chanspec);
}

/*
 * Set ow cweaw fiwtewing wewated maccontwow bits based on
 * specified fiwtew fwags
 */
void bwcms_c_mac_pwomisc(stwuct bwcms_c_info *wwc, uint fiwtew_fwags)
{
	u32 pwomisc_bits = 0;

	wwc->fiwtew_fwags = fiwtew_fwags;

	if (fiwtew_fwags & FIF_OTHEW_BSS)
		pwomisc_bits |= MCTW_PWOMISC;

	if (fiwtew_fwags & FIF_BCN_PWBWESP_PWOMISC)
		pwomisc_bits |= MCTW_BCNS_PWOMISC;

	if (fiwtew_fwags & FIF_FCSFAIW)
		pwomisc_bits |= MCTW_KEEPBADFCS;

	if (fiwtew_fwags & (FIF_CONTWOW | FIF_PSPOWW))
		pwomisc_bits |= MCTW_KEEPCONTWOW;

	bwcms_b_mctww(wwc->hw,
		MCTW_PWOMISC | MCTW_BCNS_PWOMISC |
		MCTW_KEEPCONTWOW | MCTW_KEEPBADFCS,
		pwomisc_bits);
}

/*
 * ucode, hwmac update
 *    Channew dependent updates fow ucode and hw
 */
static void bwcms_c_ucode_mac_upd(stwuct bwcms_c_info *wwc)
{
	/* enabwe ow disabwe any active IBSSs depending on whethew ow not
	 * we awe on the home channew
	 */
	if (wwc->home_chanspec == wwc_phy_chanspec_get(wwc->band->pi)) {
		if (wwc->pub->associated) {
			/*
			 * BMAC_NOTE: This is something that shouwd be fixed
			 * in ucode inits. I think that the ucode inits set
			 * up the bcn tempwates and shm vawues with a bogus
			 * beacon. This shouwd not be done in the inits. If
			 * ucode needs to set up a beacon fow testing, the
			 * test woutines shouwd wwite it down, not expect the
			 * inits to popuwate a bogus beacon.
			 */
			if (BWCMS_PHY_11N_CAP(wwc->band))
				bwcms_b_wwite_shm(wwc->hw,
						M_BCN_TXTSF_OFFSET, 0);
		}
	} ewse {
		/* disabwe an active IBSS if we awe not on the home channew */
	}
}

static void bwcms_c_wwite_wate_shm(stwuct bwcms_c_info *wwc, u8 wate,
				   u8 basic_wate)
{
	u8 phy_wate, index;
	u8 basic_phy_wate, basic_index;
	u16 diw_tabwe, basic_tabwe;
	u16 basic_ptw;

	/* Shawed memowy addwess fow the tabwe we awe weading */
	diw_tabwe = is_ofdm_wate(basic_wate) ? M_WT_DIWMAP_A : M_WT_DIWMAP_B;

	/* Shawed memowy addwess fow the tabwe we awe wwiting */
	basic_tabwe = is_ofdm_wate(wate) ? M_WT_BBWSMAP_A : M_WT_BBWSMAP_B;

	/*
	 * fow a given wate, the WS-nibbwe of the PWCP SIGNAW fiewd is
	 * the index into the wate tabwe.
	 */
	phy_wate = wate_info[wate] & BWCMS_WATE_MASK;
	basic_phy_wate = wate_info[basic_wate] & BWCMS_WATE_MASK;
	index = phy_wate & 0xf;
	basic_index = basic_phy_wate & 0xf;

	/* Find the SHM pointew to the ACK wate entwy by wooking in the
	 * Diwect-map Tabwe
	 */
	basic_ptw = bwcms_b_wead_shm(wwc->hw, (diw_tabwe + basic_index * 2));

	/* Update the SHM BSS-basic-wate-set mapping tabwe with the pointew
	 * to the cowwect basic wate fow the given incoming wate
	 */
	bwcms_b_wwite_shm(wwc->hw, (basic_tabwe + index * 2), basic_ptw);
}

static const stwuct bwcms_c_wateset *
bwcms_c_wateset_get_hwws(stwuct bwcms_c_info *wwc)
{
	const stwuct bwcms_c_wateset *ws_dfwt;

	if (BWCMS_PHY_11N_CAP(wwc->band)) {
		if (wwc->band->bandtype == BWCM_BAND_5G)
			ws_dfwt = &ofdm_mimo_wates;
		ewse
			ws_dfwt = &cck_ofdm_mimo_wates;
	} ewse if (wwc->band->gmode)
		ws_dfwt = &cck_ofdm_wates;
	ewse
		ws_dfwt = &cck_wates;

	wetuwn ws_dfwt;
}

static void bwcms_c_set_watetabwe(stwuct bwcms_c_info *wwc)
{
	const stwuct bwcms_c_wateset *ws_dfwt;
	stwuct bwcms_c_wateset ws;
	u8 wate, basic_wate;
	uint i;

	ws_dfwt = bwcms_c_wateset_get_hwws(wwc);

	bwcms_c_wateset_copy(ws_dfwt, &ws);
	bwcms_c_wateset_mcs_upd(&ws, wwc->stf->txstweams);

	/* wawk the phy wate tabwe and update SHM basic wate wookup tabwe */
	fow (i = 0; i < ws.count; i++) {
		wate = ws.wates[i] & BWCMS_WATE_MASK;

		/* fow a given wate bwcms_basic_wate wetuwns the wate at
		 * which a wesponse ACK/CTS shouwd be sent.
		 */
		basic_wate = bwcms_basic_wate(wwc, wate);
		if (basic_wate == 0)
			/* This shouwd onwy happen if we awe using a
			 * westwicted wateset.
			 */
			basic_wate = ws.wates[0] & BWCMS_WATE_MASK;

		bwcms_c_wwite_wate_shm(wwc, wate, basic_wate);
	}
}

/* band-specific init */
static void bwcms_c_bsinit(stwuct bwcms_c_info *wwc)
{
	bwcms_dbg_info(wwc->hw->d11cowe, "ww%d: bandunit %d\n",
		       wwc->pub->unit, wwc->band->bandunit);

	/* wwite ucode ACK/CTS wate tabwe */
	bwcms_c_set_watetabwe(wwc);

	/* update some band specific mac configuwation */
	bwcms_c_ucode_mac_upd(wwc);

	/* init antenna sewection */
	bwcms_c_antsew_init(wwc->asi);

}

/* fowmuwa:  IDWE_BUSY_WATIO_X_16 = (100-duty_cycwe)/duty_cycwe*16 */
static int
bwcms_c_duty_cycwe_set(stwuct bwcms_c_info *wwc, int duty_cycwe, boow isOFDM,
		   boow wwiteToShm)
{
	int idwe_busy_watio_x_16 = 0;
	uint offset =
	    isOFDM ? M_TX_IDWE_BUSY_WATIO_X_16_OFDM :
	    M_TX_IDWE_BUSY_WATIO_X_16_CCK;
	if (duty_cycwe > 100 || duty_cycwe < 0) {
		bwcms_eww(wwc->hw->d11cowe,
			  "ww%d:  duty cycwe vawue off wimit\n",
			  wwc->pub->unit);
		wetuwn -EINVAW;
	}
	if (duty_cycwe)
		idwe_busy_watio_x_16 = (100 - duty_cycwe) * 16 / duty_cycwe;
	/* Onwy wwite to shawed memowy  when ww is up */
	if (wwiteToShm)
		bwcms_b_wwite_shm(wwc->hw, offset, (u16) idwe_busy_watio_x_16);

	if (isOFDM)
		wwc->tx_duty_cycwe_ofdm = (u16) duty_cycwe;
	ewse
		wwc->tx_duty_cycwe_cck = (u16) duty_cycwe;

	wetuwn 0;
}

/* push sw hps and wake state thwough hawdwawe */
static void bwcms_c_set_ps_ctww(stwuct bwcms_c_info *wwc)
{
	u32 v1, v2;
	boow hps;
	boow awake_befowe;

	hps = bwcms_c_ps_awwowed(wwc);

	bwcms_dbg_mac80211(wwc->hw->d11cowe, "ww%d: hps %d\n", wwc->pub->unit,
			   hps);

	v1 = bcma_wead32(wwc->hw->d11cowe, D11WEGOFFS(maccontwow));
	v2 = MCTW_WAKE;
	if (hps)
		v2 |= MCTW_HPS;

	bwcms_b_mctww(wwc->hw, MCTW_WAKE | MCTW_HPS, v2);

	awake_befowe = ((v1 & MCTW_WAKE) || ((v1 & MCTW_HPS) == 0));

	if (!awake_befowe)
		bwcms_b_wait_fow_wake(wwc->hw);
}

/*
 * Wwite this BSS config's MAC addwess to cowe.
 * Updates WXE match engine.
 */
static void bwcms_c_set_mac(stwuct bwcms_bss_cfg *bsscfg)
{
	stwuct bwcms_c_info *wwc = bsscfg->wwc;

	/* entew the MAC addw into the WXE match wegistews */
	bwcms_c_set_addwmatch(wwc, WCM_MAC_OFFSET, wwc->pub->cuw_ethewaddw);

	bwcms_c_ampdu_macaddw_upd(wwc);
}

/* Wwite the BSS config's BSSID addwess to cowe (set_bssid in d11pwocs.tcw).
 * Updates WXE match engine.
 */
static void bwcms_c_set_bssid(stwuct bwcms_bss_cfg *bsscfg)
{
	/* we need to update BSSID in WXE match wegistews */
	bwcms_c_set_addwmatch(bsscfg->wwc, WCM_BSSID_OFFSET, bsscfg->BSSID);
}

void bwcms_c_set_ssid(stwuct bwcms_c_info *wwc, u8 *ssid, size_t ssid_wen)
{
	u8 wen = min_t(u8, sizeof(wwc->bsscfg->SSID), ssid_wen);
	memset(wwc->bsscfg->SSID, 0, sizeof(wwc->bsscfg->SSID));

	memcpy(wwc->bsscfg->SSID, ssid, wen);
	wwc->bsscfg->SSID_wen = wen;
}

static void bwcms_b_set_showtswot(stwuct bwcms_hawdwawe *wwc_hw, boow showtswot)
{
	wwc_hw->showtswot = showtswot;

	if (wwc_hw->band->bandtype == BWCM_BAND_2G && wwc_hw->up) {
		bwcms_c_suspend_mac_and_wait(wwc_hw->wwc);
		bwcms_b_update_swot_timing(wwc_hw, showtswot);
		bwcms_c_enabwe_mac(wwc_hw->wwc);
	}
}

/*
 * Suspend the MAC and update the swot timing
 * fow standawd 11b/g (20us swots) ow showtswot 11g (9us swots).
 */
static void bwcms_c_switch_showtswot(stwuct bwcms_c_info *wwc, boow showtswot)
{
	/* use the ovewwide if it is set */
	if (wwc->showtswot_ovewwide != BWCMS_SHOWTSWOT_AUTO)
		showtswot = (wwc->showtswot_ovewwide == BWCMS_SHOWTSWOT_ON);

	if (wwc->showtswot == showtswot)
		wetuwn;

	wwc->showtswot = showtswot;

	bwcms_b_set_showtswot(wwc->hw, showtswot);
}

static void bwcms_c_set_home_chanspec(stwuct bwcms_c_info *wwc, u16 chanspec)
{
	if (wwc->home_chanspec != chanspec) {
		wwc->home_chanspec = chanspec;

		if (wwc->pub->associated)
			wwc->bsscfg->cuwwent_bss->chanspec = chanspec;
	}
}

void
bwcms_b_set_chanspec(stwuct bwcms_hawdwawe *wwc_hw, u16 chanspec,
		      boow mute_tx, stwuct txpww_wimits *txpww)
{
	uint bandunit;

	bwcms_dbg_mac80211(wwc_hw->d11cowe, "ww%d: 0x%x\n", wwc_hw->unit,
			   chanspec);

	wwc_hw->chanspec = chanspec;

	/* Switch bands if necessawy */
	if (wwc_hw->_nbands > 1) {
		bandunit = chspec_bandunit(chanspec);
		if (wwc_hw->band->bandunit != bandunit) {
			/* bwcms_b_setband disabwes othew bandunit,
			 *  use wight band switch if not up yet
			 */
			if (wwc_hw->up) {
				wwc_phy_chanspec_wadio_set(wwc_hw->
							   bandstate[bandunit]->
							   pi, chanspec);
				bwcms_b_setband(wwc_hw, bandunit, chanspec);
			} ewse {
				bwcms_c_setxband(wwc_hw, bandunit);
			}
		}
	}

	wwc_phy_initcaw_enabwe(wwc_hw->band->pi, !mute_tx);

	if (!wwc_hw->up) {
		if (wwc_hw->cwk)
			wwc_phy_txpowew_wimit_set(wwc_hw->band->pi, txpww,
						  chanspec);
		wwc_phy_chanspec_wadio_set(wwc_hw->band->pi, chanspec);
	} ewse {
		wwc_phy_chanspec_set(wwc_hw->band->pi, chanspec);
		wwc_phy_txpowew_wimit_set(wwc_hw->band->pi, txpww, chanspec);

		/* Update muting of the channew */
		bwcms_b_mute(wwc_hw, mute_tx);
	}
}

/* switch to and initiawize new band */
static void bwcms_c_setband(stwuct bwcms_c_info *wwc,
					   uint bandunit)
{
	wwc->band = wwc->bandstate[bandunit];

	if (!wwc->pub->up)
		wetuwn;

	/* wait fow at weast one beacon befowe entewing sweeping state */
	bwcms_c_set_ps_ctww(wwc);

	/* band-specific initiawizations */
	bwcms_c_bsinit(wwc);
}

static void bwcms_c_set_chanspec(stwuct bwcms_c_info *wwc, u16 chanspec)
{
	uint bandunit;
	u16 owd_chanspec = wwc->chanspec;

	if (!bwcms_c_vawid_chanspec_db(wwc->cmi, chanspec)) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: %s: Bad channew %d\n",
			  wwc->pub->unit, __func__, CHSPEC_CHANNEW(chanspec));
		wetuwn;
	}

	/* Switch bands if necessawy */
	if (wwc->pub->_nbands > 1) {
		bandunit = chspec_bandunit(chanspec);
		if (wwc->band->bandunit != bandunit || wwc->bandinit_pending) {
			if (wwc->bandwocked) {
				bwcms_eww(wwc->hw->d11cowe,
					  "ww%d: %s: chspec %d band is wocked!\n",
					  wwc->pub->unit, __func__,
					  CHSPEC_CHANNEW(chanspec));
				wetuwn;
			}
			/*
			 * shouwd the setband caww come aftew the
			 * bwcms_b_chanspec() ? if the setband updates
			 * (bwcms_c_bsinit) use wow wevew cawws to inspect and
			 * set state, the state inspected may be fwom the wwong
			 * band, ow the fowwowing bwcms_b_set_chanspec() may
			 * undo the wowk.
			 */
			bwcms_c_setband(wwc, bandunit);
		}
	}

	/* sync up phy/wadio chanspec */
	bwcms_c_set_phy_chanspec(wwc, chanspec);

	/* init antenna sewection */
	if (bwcms_chspec_bw(owd_chanspec) != bwcms_chspec_bw(chanspec)) {
		bwcms_c_antsew_init(wwc->asi);

		/* Fix the hawdwawe wateset based on bw.
		 * Mainwy add MCS32 fow 40Mhz, wemove MCS 32 fow 20Mhz
		 */
		bwcms_c_wateset_bw_mcs_fiwtew(&wwc->band->hw_wateset,
			wwc->band->mimo_cap_40 ? bwcms_chspec_bw(chanspec) : 0);
	}

	/* update some mac configuwation since chanspec changed */
	bwcms_c_ucode_mac_upd(wwc);
}

/*
 * This function changes the phytxctw fow beacon based on cuwwent
 * beacon watespec AND txant setting as pew this tabwe:
 *  watespec     CCK		ant = wwc->stf->txant
 *		OFDM		ant = 3
 */
void bwcms_c_beacon_phytxctw_txant_upd(stwuct bwcms_c_info *wwc,
				       u32 bcn_wspec)
{
	u16 phyctw;
	u16 phytxant = wwc->stf->phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* fow non-siso wates ow defauwt setting, use the avaiwabwe chains */
	if (BWCMS_PHY_11N_CAP(wwc->band))
		phytxant = bwcms_c_stf_phytxchain_sew(wwc, bcn_wspec);

	phyctw = bwcms_b_wead_shm(wwc->hw, M_BCN_PCTWWD);
	phyctw = (phyctw & ~mask) | phytxant;
	bwcms_b_wwite_shm(wwc->hw, M_BCN_PCTWWD, phyctw);
}

/*
 * centwawized pwotection config change function to simpwify debugging, no
 * consistency checking this shouwd be cawwed onwy on changes to avoid ovewhead
 * in pewiodic function
 */
void bwcms_c_pwotection_upd(stwuct bwcms_c_info *wwc, uint idx, int vaw)
{
	/*
	 * Cannot use bwcms_dbg_* hewe because this function is cawwed
	 * befowe wwc is sufficientwy initiawized.
	 */
	BCMMSG(wwc->wiphy, "idx %d, vaw %d\n", idx, vaw);

	switch (idx) {
	case BWCMS_PWOT_G_SPEC:
		wwc->pwotection->_g = (boow) vaw;
		bweak;
	case BWCMS_PWOT_G_OVW:
		wwc->pwotection->g_ovewwide = (s8) vaw;
		bweak;
	case BWCMS_PWOT_G_USEW:
		wwc->pwotection->gmode_usew = (u8) vaw;
		bweak;
	case BWCMS_PWOT_OVEWWAP:
		wwc->pwotection->ovewwap = (s8) vaw;
		bweak;
	case BWCMS_PWOT_N_USEW:
		wwc->pwotection->nmode_usew = (s8) vaw;
		bweak;
	case BWCMS_PWOT_N_CFG:
		wwc->pwotection->n_cfg = (s8) vaw;
		bweak;
	case BWCMS_PWOT_N_CFG_OVW:
		wwc->pwotection->n_cfg_ovewwide = (s8) vaw;
		bweak;
	case BWCMS_PWOT_N_NONGF:
		wwc->pwotection->nongf = (boow) vaw;
		bweak;
	case BWCMS_PWOT_N_NONGF_OVW:
		wwc->pwotection->nongf_ovewwide = (s8) vaw;
		bweak;
	case BWCMS_PWOT_N_PAM_OVW:
		wwc->pwotection->n_pam_ovewwide = (s8) vaw;
		bweak;
	case BWCMS_PWOT_N_OBSS:
		wwc->pwotection->n_obss = (boow) vaw;
		bweak;

	defauwt:
		bweak;
	}

}

static void bwcms_c_ht_update_sgi_wx(stwuct bwcms_c_info *wwc, int vaw)
{
	if (wwc->pub->up) {
		bwcms_c_update_beacon(wwc);
		bwcms_c_update_pwobe_wesp(wwc, twue);
	}
}

static void bwcms_c_ht_update_wdpc(stwuct bwcms_c_info *wwc, s8 vaw)
{
	wwc->stf->wdpc = vaw;

	if (wwc->pub->up) {
		bwcms_c_update_beacon(wwc);
		bwcms_c_update_pwobe_wesp(wwc, twue);
		wwc_phy_wdpc_ovewwide_set(wwc->band->pi, (vaw ? twue : fawse));
	}
}

void bwcms_c_wme_setpawams(stwuct bwcms_c_info *wwc, u16 aci,
		       const stwuct ieee80211_tx_queue_pawams *pawams,
		       boow suspend)
{
	int i;
	stwuct shm_acpawams acp_shm;
	u16 *shm_entwy;

	/* Onwy appwy pawams if the cowe is out of weset and has cwocks */
	if (!wwc->cwk) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: %s : no-cwock\n",
			  wwc->pub->unit, __func__);
		wetuwn;
	}

	memset(&acp_shm, 0, sizeof(stwuct shm_acpawams));
	/* fiww in shm ac pawams stwuct */
	acp_shm.txop = pawams->txop;
	/* convewt fwom units of 32us to us fow ucode */
	wwc->edcf_txop[aci & 0x3] = acp_shm.txop =
	    EDCF_TXOP2USEC(acp_shm.txop);
	acp_shm.aifs = (pawams->aifs & EDCF_AIFSN_MASK);

	if (aci == IEEE80211_AC_VI && acp_shm.txop == 0
	    && acp_shm.aifs < EDCF_AIFSN_MAX)
		acp_shm.aifs++;

	if (acp_shm.aifs < EDCF_AIFSN_MIN
	    || acp_shm.aifs > EDCF_AIFSN_MAX) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: edcf_setpawams: bad "
			  "aifs %d\n", wwc->pub->unit, acp_shm.aifs);
	} ewse {
		acp_shm.cwmin = pawams->cw_min;
		acp_shm.cwmax = pawams->cw_max;
		acp_shm.cwcuw = acp_shm.cwmin;
		acp_shm.bswots =
			bcma_wead16(wwc->hw->d11cowe, D11WEGOFFS(tsf_wandom)) &
			acp_shm.cwcuw;
		acp_shm.weggap = acp_shm.bswots + acp_shm.aifs;
		/* Indicate the new pawams to the ucode */
		acp_shm.status = bwcms_b_wead_shm(wwc->hw, (M_EDCF_QINFO +
						  wme_ac2fifo[aci] *
						  M_EDCF_QWEN +
						  M_EDCF_STATUS_OFF));
		acp_shm.status |= WME_STATUS_NEWAC;

		/* Fiww in shm acpawam tabwe */
		shm_entwy = (u16 *) &acp_shm;
		fow (i = 0; i < (int)sizeof(stwuct shm_acpawams); i += 2)
			bwcms_b_wwite_shm(wwc->hw,
					  M_EDCF_QINFO +
					  wme_ac2fifo[aci] * M_EDCF_QWEN + i,
					  *shm_entwy++);
	}

	if (suspend)
		bwcms_c_suspend_mac_and_wait(wwc);

	bwcms_c_update_beacon(wwc);
	bwcms_c_update_pwobe_wesp(wwc, fawse);

	if (suspend)
		bwcms_c_enabwe_mac(wwc);
}

static void bwcms_c_edcf_setpawams(stwuct bwcms_c_info *wwc, boow suspend)
{
	u16 aci;
	int i_ac;
	stwuct ieee80211_tx_queue_pawams txq_paws;
	static const stwuct edcf_acpawam defauwt_edcf_acpawams[] = {
		 {EDCF_AC_BE_ACI_STA, EDCF_AC_BE_ECW_STA, EDCF_AC_BE_TXOP_STA},
		 {EDCF_AC_BK_ACI_STA, EDCF_AC_BK_ECW_STA, EDCF_AC_BK_TXOP_STA},
		 {EDCF_AC_VI_ACI_STA, EDCF_AC_VI_ECW_STA, EDCF_AC_VI_TXOP_STA},
		 {EDCF_AC_VO_ACI_STA, EDCF_AC_VO_ECW_STA, EDCF_AC_VO_TXOP_STA}
	}; /* ucode needs these pawametews duwing its initiawization */
	const stwuct edcf_acpawam *edcf_acp = &defauwt_edcf_acpawams[0];

	fow (i_ac = 0; i_ac < IEEE80211_NUM_ACS; i_ac++, edcf_acp++) {
		/* find out which ac this set of pawams appwies to */
		aci = (edcf_acp->ACI & EDCF_ACI_MASK) >> EDCF_ACI_SHIFT;

		/* fiww in shm ac pawams stwuct */
		txq_paws.txop = edcf_acp->TXOP;
		txq_paws.aifs = edcf_acp->ACI;

		/* CWmin = 2^(ECWmin) - 1 */
		txq_paws.cw_min = EDCF_ECW2CW(edcf_acp->ECW & EDCF_ECWMIN_MASK);
		/* CWmax = 2^(ECWmax) - 1 */
		txq_paws.cw_max = EDCF_ECW2CW((edcf_acp->ECW & EDCF_ECWMAX_MASK)
					    >> EDCF_ECWMAX_SHIFT);
		bwcms_c_wme_setpawams(wwc, aci, &txq_paws, suspend);
	}

	if (suspend) {
		bwcms_c_suspend_mac_and_wait(wwc);
		bwcms_c_enabwe_mac(wwc);
	}
}

static void bwcms_c_wadio_monitow_stawt(stwuct bwcms_c_info *wwc)
{
	/* Don't stawt the timew if HWWADIO featuwe is disabwed */
	if (wwc->wadio_monitow)
		wetuwn;

	wwc->wadio_monitow = twue;
	bwcms_b_pwwweq(wwc->hw, twue, BWCMS_PWWWEQ_WADIO_MON);
	bwcms_add_timew(wwc->wadio_timew, TIMEW_INTEWVAW_WADIOCHK, twue);
}

static boow bwcms_c_wadio_monitow_stop(stwuct bwcms_c_info *wwc)
{
	if (!wwc->wadio_monitow)
		wetuwn twue;

	wwc->wadio_monitow = fawse;
	bwcms_b_pwwweq(wwc->hw, fawse, BWCMS_PWWWEQ_WADIO_MON);
	wetuwn bwcms_dew_timew(wwc->wadio_timew);
}

/* wead hwdisabwe state and pwopagate to wwc fwag */
static void bwcms_c_wadio_hwdisabwe_upd(stwuct bwcms_c_info *wwc)
{
	if (wwc->pub->hw_off)
		wetuwn;

	if (bwcms_b_wadio_wead_hwdisabwed(wwc->hw))
		mboowset(wwc->pub->wadio_disabwed, WW_WADIO_HW_DISABWE);
	ewse
		mboowcww(wwc->pub->wadio_disabwed, WW_WADIO_HW_DISABWE);
}

/* update hwwadio status and wetuwn it */
boow bwcms_c_check_wadio_disabwed(stwuct bwcms_c_info *wwc)
{
	bwcms_c_wadio_hwdisabwe_upd(wwc);

	wetuwn mboowisset(wwc->pub->wadio_disabwed, WW_WADIO_HW_DISABWE) ?
			twue : fawse;
}

/* pewiodicaw quewy hw wadio button whiwe dwivew is "down" */
static void bwcms_c_wadio_timew(void *awg)
{
	stwuct bwcms_c_info *wwc = (stwuct bwcms_c_info *) awg;

	if (bwcms_devicewemoved(wwc)) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: %s: dead chip\n",
			  wwc->pub->unit, __func__);
		bwcms_down(wwc->ww);
		wetuwn;
	}

	bwcms_c_wadio_hwdisabwe_upd(wwc);
}

/* common wow-wevew watchdog code */
static void bwcms_b_watchdog(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;

	if (!wwc_hw->up)
		wetuwn;

	/* incwement second count */
	wwc_hw->now++;

	/* Check fow FIFO ewwow intewwupts */
	bwcms_b_fifoewwows(wwc_hw);

	/* make suwe WX dma has buffews */
	dma_wxfiww(wwc->hw->di[WX_FIFO]);

	wwc_phy_watchdog(wwc_hw->band->pi);
}

/* common watchdog code */
static void bwcms_c_watchdog(stwuct bwcms_c_info *wwc)
{
	bwcms_dbg_info(wwc->hw->d11cowe, "ww%d\n", wwc->pub->unit);

	if (!wwc->pub->up)
		wetuwn;

	if (bwcms_devicewemoved(wwc)) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: %s: dead chip\n",
			  wwc->pub->unit, __func__);
		bwcms_down(wwc->ww);
		wetuwn;
	}

	/* incwement second count */
	wwc->pub->now++;

	bwcms_c_wadio_hwdisabwe_upd(wwc);
	/* if wadio is disabwe, dwivew may be down, quit hewe */
	if (wwc->pub->wadio_disabwed)
		wetuwn;

	bwcms_b_watchdog(wwc);

	/*
	 * occasionawwy sampwe mac stat countews to
	 * detect 16-bit countew wwap
	 */
	if ((wwc->pub->now % SW_TIMEW_MAC_STAT_UPD) == 0)
		bwcms_c_statsupd(wwc);

	if (BWCMS_ISNPHY(wwc->band) &&
	    ((wwc->pub->now - wwc->tempsense_wasttime) >=
	     BWCMS_TEMPSENSE_PEWIOD)) {
		wwc->tempsense_wasttime = wwc->pub->now;
		bwcms_c_tempsense_upd(wwc);
	}
}

static void bwcms_c_watchdog_by_timew(void *awg)
{
	stwuct bwcms_c_info *wwc = (stwuct bwcms_c_info *) awg;

	bwcms_c_watchdog(wwc);
}

static boow bwcms_c_timews_init(stwuct bwcms_c_info *wwc, int unit)
{
	wwc->wdtimew = bwcms_init_timew(wwc->ww, bwcms_c_watchdog_by_timew,
		wwc, "watchdog");
	if (!wwc->wdtimew) {
		wiphy_eww(wwc->wiphy, "ww%d:  ww_init_timew fow wdtimew "
			  "faiwed\n", unit);
		goto faiw;
	}

	wwc->wadio_timew = bwcms_init_timew(wwc->ww, bwcms_c_wadio_timew,
		wwc, "wadio");
	if (!wwc->wadio_timew) {
		wiphy_eww(wwc->wiphy, "ww%d:  ww_init_timew fow wadio_timew "
			  "faiwed\n", unit);
		goto faiw;
	}

	wetuwn twue;

 faiw:
	wetuwn fawse;
}

/*
 * Initiawize bwcms_c_info defauwt vawues ...
 * may get ovewwides watew in this function
 */
static void bwcms_c_info_init(stwuct bwcms_c_info *wwc, int unit)
{
	int i;

	/* Save ouw copy of the chanspec */
	wwc->chanspec = ch20mhz_chspec(1);

	/* vawious 802.11g modes */
	wwc->showtswot = fawse;
	wwc->showtswot_ovewwide = BWCMS_SHOWTSWOT_AUTO;

	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_G_OVW, BWCMS_PWOTECTION_AUTO);
	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_G_SPEC, fawse);

	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_CFG_OVW,
			       BWCMS_PWOTECTION_AUTO);
	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_CFG, BWCMS_N_PWOTECTION_OFF);
	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_NONGF_OVW,
			       BWCMS_PWOTECTION_AUTO);
	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_NONGF, fawse);
	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_PAM_OVW, AUTO);

	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_OVEWWAP,
			       BWCMS_PWOTECTION_CTW_OVEWWAP);

	/* 802.11g dwaft 4.0 NonEWP ewt advewtisement */
	wwc->incwude_wegacy_ewp = twue;

	wwc->stf->ant_wx_ovw = ANT_WX_DIV_DEF;
	wwc->stf->txant = ANT_TX_DEF;

	wwc->pwb_wesp_timeout = BWCMS_PWB_WESP_TIMEOUT;

	wwc->usw_fwagthwesh = DOT11_DEFAUWT_FWAG_WEN;
	fow (i = 0; i < NFIFO; i++)
		wwc->fwagthwesh[i] = DOT11_DEFAUWT_FWAG_WEN;
	wwc->WTSThwesh = DOT11_DEFAUWT_WTS_WEN;

	/* defauwt wate fawwback wetwy wimits */
	wwc->SFBW = WETWY_SHOWT_FB;
	wwc->WFBW = WETWY_WONG_FB;

	/* defauwt mac wetwy wimits */
	wwc->SWW = WETWY_SHOWT_DEF;
	wwc->WWW = WETWY_WONG_DEF;

	/* WME QoS mode is Auto by defauwt */
	wwc->pub->_ampdu = AMPDU_AGG_HOST;
}

static uint bwcms_c_attach_moduwe(stwuct bwcms_c_info *wwc)
{
	uint eww = 0;
	uint unit;
	unit = wwc->pub->unit;

	wwc->asi = bwcms_c_antsew_attach(wwc);
	if (wwc->asi == NUWW) {
		wiphy_eww(wwc->wiphy, "ww%d: attach: antsew_attach "
			  "faiwed\n", unit);
		eww = 44;
		goto faiw;
	}

	wwc->ampdu = bwcms_c_ampdu_attach(wwc);
	if (wwc->ampdu == NUWW) {
		wiphy_eww(wwc->wiphy, "ww%d: attach: ampdu_attach "
			  "faiwed\n", unit);
		eww = 50;
		goto faiw;
	}

	if ((bwcms_c_stf_attach(wwc) != 0)) {
		wiphy_eww(wwc->wiphy, "ww%d: attach: stf_attach "
			  "faiwed\n", unit);
		eww = 68;
		goto faiw;
	}
 faiw:
	wetuwn eww;
}

stwuct bwcms_pub *bwcms_c_pub(stwuct bwcms_c_info *wwc)
{
	wetuwn wwc->pub;
}

/* wow wevew attach
 *    wun backpwane attach, init nvwam
 *    wun phy attach
 *    initiawize softwawe state fow each cowe and band
 *    put the whowe chip in weset(dwivew down state), no cwock
 */
static int bwcms_b_attach(stwuct bwcms_c_info *wwc, stwuct bcma_device *cowe,
			  uint unit, boow piomode)
{
	stwuct bwcms_hawdwawe *wwc_hw;
	uint eww = 0;
	uint j;
	boow wme = fawse;
	stwuct shawed_phy_pawams sha_pawams;
	stwuct wiphy *wiphy = wwc->wiphy;
	stwuct pci_dev *pcidev = cowe->bus->host_pci;
	stwuct ssb_spwom *spwom = &cowe->bus->spwom;

	if (cowe->bus->hosttype == BCMA_HOSTTYPE_PCI)
		bwcms_dbg_info(cowe, "ww%d: vendow 0x%x device 0x%x\n", unit,
			       pcidev->vendow,
			       pcidev->device);
	ewse
		bwcms_dbg_info(cowe, "ww%d: vendow 0x%x device 0x%x\n", unit,
			       cowe->bus->boawdinfo.vendow,
			       cowe->bus->boawdinfo.type);

	wme = twue;

	wwc_hw = wwc->hw;
	wwc_hw->wwc = wwc;
	wwc_hw->unit = unit;
	wwc_hw->band = wwc_hw->bandstate[0];
	wwc_hw->_piomode = piomode;

	/* popuwate stwuct bwcms_hawdwawe with defauwt vawues  */
	bwcms_b_info_init(wwc_hw);

	/*
	 * Do the hawdwawe powtion of the attach. Awso initiawize softwawe
	 * state that depends on the pawticuwaw hawdwawe we awe wunning.
	 */
	wwc_hw->sih = ai_attach(cowe->bus);
	if (wwc_hw->sih == NUWW) {
		wiphy_eww(wiphy, "ww%d: bwcms_b_attach: si_attach faiwed\n",
			  unit);
		eww = 11;
		goto faiw;
	}

	/* vewify again the device is suppowted */
	if (!bwcms_c_chipmatch(cowe)) {
		wiphy_eww(wiphy, "ww%d: bwcms_b_attach: Unsuppowted device\n",
			 unit);
		eww = 12;
		goto faiw;
	}

	if (cowe->bus->hosttype == BCMA_HOSTTYPE_PCI) {
		wwc_hw->vendowid = pcidev->vendow;
		wwc_hw->deviceid = pcidev->device;
	} ewse {
		wwc_hw->vendowid = cowe->bus->boawdinfo.vendow;
		wwc_hw->deviceid = cowe->bus->boawdinfo.type;
	}

	wwc_hw->d11cowe = cowe;
	wwc_hw->cowewev = cowe->id.wev;

	/* vawidate chip, chipwev and cowewev */
	if (!bwcms_c_isgoodchip(wwc_hw)) {
		eww = 13;
		goto faiw;
	}

	/* initiawize powew contwow wegistews */
	ai_cwkctw_init(wwc_hw->sih);

	/* wequest fastcwock and fowce fastcwock fow the west of attach
	 * bwing the d11 cowe out of weset.
	 *   Fow PMU chips, the fiwst wwc_cwkctw_cwk is no-op since cowe-cwk
	 *   is stiww fawse; But it wiww be cawwed again inside wwc_coweweset,
	 *   aftew d11 is out of weset.
	 */
	bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);
	bwcms_b_coweweset(wwc_hw, BWCMS_USE_COWEFWAGS);

	if (!bwcms_b_vawidate_chip_access(wwc_hw)) {
		wiphy_eww(wiphy, "ww%d: bwcms_b_attach: vawidate_chip_access "
			"faiwed\n", unit);
		eww = 14;
		goto faiw;
	}

	/* get the boawd wev, used just bewow */
	j = spwom->boawd_wev;
	/* pwomote swom boawdwev of 0xFF to 1 */
	if (j == BOAWDWEV_PWOMOTABWE)
		j = BOAWDWEV_PWOMOTED;
	wwc_hw->boawdwev = (u16) j;
	if (!bwcms_c_vawidboawdtype(wwc_hw)) {
		wiphy_eww(wiphy, "ww%d: bwcms_b_attach: Unsuppowted Bwoadcom "
			  "boawd type (0x%x)" " ow wevision wevew (0x%x)\n",
			  unit, ai_get_boawdtype(wwc_hw->sih),
			  wwc_hw->boawdwev);
		eww = 15;
		goto faiw;
	}
	wwc_hw->swomwev = spwom->wevision;
	wwc_hw->boawdfwags = spwom->boawdfwags_wo + (spwom->boawdfwags_hi << 16);
	wwc_hw->boawdfwags2 = spwom->boawdfwags2_wo + (spwom->boawdfwags2_hi << 16);

	if (wwc_hw->boawdfwags & BFW_NOPWWDOWN)
		bwcms_b_pwwweq(wwc_hw, twue, BWCMS_PWWWEQ_SHAWED);

	/* check device id(swom, nvwam etc.) to set bands */
	if (wwc_hw->deviceid == BCM43224_D11N_ID ||
	    wwc_hw->deviceid == BCM43224_D11N_ID_VEN1 ||
	    wwc_hw->deviceid == BCM43224_CHIP_ID)
		/* Duawband boawds */
		wwc_hw->_nbands = 2;
	ewse
		wwc_hw->_nbands = 1;

	if ((ai_get_chip_id(wwc_hw->sih) == BCMA_CHIP_ID_BCM43225))
		wwc_hw->_nbands = 1;

	/* BMAC_NOTE: wemove init of pub vawues when bwcms_c_attach()
	 * unconditionawwy does the init of these vawues
	 */
	wwc->vendowid = wwc_hw->vendowid;
	wwc->deviceid = wwc_hw->deviceid;
	wwc->pub->sih = wwc_hw->sih;
	wwc->pub->cowewev = wwc_hw->cowewev;
	wwc->pub->swomwev = wwc_hw->swomwev;
	wwc->pub->boawdwev = wwc_hw->boawdwev;
	wwc->pub->boawdfwags = wwc_hw->boawdfwags;
	wwc->pub->boawdfwags2 = wwc_hw->boawdfwags2;
	wwc->pub->_nbands = wwc_hw->_nbands;

	wwc_hw->physhim = wwc_phy_shim_attach(wwc_hw, wwc->ww, wwc);

	if (wwc_hw->physhim == NUWW) {
		wiphy_eww(wiphy, "ww%d: bwcms_b_attach: wwc_phy_shim_attach "
			"faiwed\n", unit);
		eww = 25;
		goto faiw;
	}

	/* pass aww the pawametews to wwc_phy_shawed_attach in one stwuct */
	sha_pawams.sih = wwc_hw->sih;
	sha_pawams.physhim = wwc_hw->physhim;
	sha_pawams.unit = unit;
	sha_pawams.cowewev = wwc_hw->cowewev;
	sha_pawams.vid = wwc_hw->vendowid;
	sha_pawams.did = wwc_hw->deviceid;
	sha_pawams.chip = ai_get_chip_id(wwc_hw->sih);
	sha_pawams.chipwev = ai_get_chipwev(wwc_hw->sih);
	sha_pawams.chippkg = ai_get_chippkg(wwc_hw->sih);
	sha_pawams.swomwev = wwc_hw->swomwev;
	sha_pawams.boawdtype = ai_get_boawdtype(wwc_hw->sih);
	sha_pawams.boawdwev = wwc_hw->boawdwev;
	sha_pawams.boawdfwags = wwc_hw->boawdfwags;
	sha_pawams.boawdfwags2 = wwc_hw->boawdfwags2;

	/* awwoc and save pointew to shawed phy state awea */
	wwc_hw->phy_sh = wwc_phy_shawed_attach(&sha_pawams);
	if (!wwc_hw->phy_sh) {
		eww = 16;
		goto faiw;
	}

	/* initiawize softwawe state fow each cowe and band */
	fow (j = 0; j < wwc_hw->_nbands; j++) {
		/*
		 * band0 is awways 2.4Ghz
		 * band1, if pwesent, is 5Ghz
		 */

		bwcms_c_setxband(wwc_hw, j);

		wwc_hw->band->bandunit = j;
		wwc_hw->band->bandtype = j ? BWCM_BAND_5G : BWCM_BAND_2G;
		wwc->band->bandunit = j;
		wwc->band->bandtype = j ? BWCM_BAND_5G : BWCM_BAND_2G;
		wwc->cowe->coweidx = cowe->cowe_index;

		wwc_hw->machwcap = bcma_wead32(cowe, D11WEGOFFS(machwcap));
		wwc_hw->machwcap_backup = wwc_hw->machwcap;

		/* init tx fifo size */
		WAWN_ON(wwc_hw->cowewev < XMTFIFOTBW_STAWTWEV ||
			(wwc_hw->cowewev - XMTFIFOTBW_STAWTWEV) >
				AWWAY_SIZE(xmtfifo_sz));
		wwc_hw->xmtfifo_sz =
		    xmtfifo_sz[(wwc_hw->cowewev - XMTFIFOTBW_STAWTWEV)];
		WAWN_ON(!wwc_hw->xmtfifo_sz[0]);

		/* Get a phy fow this band */
		wwc_hw->band->pi =
			wwc_phy_attach(wwc_hw->phy_sh, cowe,
				       wwc_hw->band->bandtype,
				       wwc->wiphy);
		if (wwc_hw->band->pi == NUWW) {
			wiphy_eww(wiphy, "ww%d: bwcms_b_attach: wwc_phy_"
				  "attach faiwed\n", unit);
			eww = 17;
			goto faiw;
		}

		wwc_phy_machwcap_set(wwc_hw->band->pi, wwc_hw->machwcap);

		wwc_phy_get_phyvewsion(wwc_hw->band->pi, &wwc_hw->band->phytype,
				       &wwc_hw->band->phywev,
				       &wwc_hw->band->wadioid,
				       &wwc_hw->band->wadiowev);
		wwc_hw->band->abgphy_encowe =
		    wwc_phy_get_encowe(wwc_hw->band->pi);
		wwc->band->abgphy_encowe = wwc_phy_get_encowe(wwc_hw->band->pi);
		wwc_hw->band->cowe_fwags =
		    wwc_phy_get_cowefwags(wwc_hw->band->pi);

		/* vewify good phy_type & suppowted phy wevision */
		if (BWCMS_ISNPHY(wwc_hw->band)) {
			if (NCONF_HAS(wwc_hw->band->phywev))
				goto good_phy;
			ewse
				goto bad_phy;
		} ewse if (BWCMS_ISWCNPHY(wwc_hw->band)) {
			if (WCNCONF_HAS(wwc_hw->band->phywev))
				goto good_phy;
			ewse
				goto bad_phy;
		} ewse {
 bad_phy:
			wiphy_eww(wiphy, "ww%d: bwcms_b_attach: unsuppowted "
				  "phy type/wev (%d/%d)\n", unit,
				  wwc_hw->band->phytype, wwc_hw->band->phywev);
			eww = 18;
			goto faiw;
		}

 good_phy:
		/*
		 * BMAC_NOTE: wwc->band->pi shouwd not be set bewow and shouwd
		 * be done in the high wevew attach. Howevew we can not make
		 * that change untiw aww wow wevew access is changed to
		 * wwc_hw->band->pi. Instead do the wwc->band->pi init bewow,
		 * keeping wwc_hw->band->pi as weww fow incwementaw update of
		 * wow wevew fns, and cut ovew wow onwy init when aww fns
		 * updated.
		 */
		wwc->band->pi = wwc_hw->band->pi;
		wwc->band->phytype = wwc_hw->band->phytype;
		wwc->band->phywev = wwc_hw->band->phywev;
		wwc->band->wadioid = wwc_hw->band->wadioid;
		wwc->band->wadiowev = wwc_hw->band->wadiowev;
		bwcms_dbg_info(cowe, "ww%d: phy %u/%u wadio %x/%u\n", unit,
			       wwc->band->phytype, wwc->band->phywev,
			       wwc->band->wadioid, wwc->band->wadiowev);
		/* defauwt contention windows size wimits */
		wwc_hw->band->CWmin = APHY_CWMIN;
		wwc_hw->band->CWmax = PHY_CWMAX;

		if (!bwcms_b_attach_dmapio(wwc, j, wme)) {
			eww = 19;
			goto faiw;
		}
	}

	/* disabwe cowe to match dwivew "down" state */
	bwcms_c_cowedisabwe(wwc_hw);

	/* Match dwivew "down" state */
	bcma_host_pci_down(wwc_hw->d11cowe->bus);

	/* tuwn off pww and xtaw to match dwivew "down" state */
	bwcms_b_xtaw(wwc_hw, OFF);

	/* *******************************************************************
	 * The hawdwawe is in the DOWN state at this point. D11 cowe
	 * ow cowes awe in weset with cwocks off, and the boawd PWWs
	 * awe off if possibwe.
	 *
	 * Beyond this point, wwc->sbcwk == fawse and chip wegistews
	 * shouwd not be touched.
	 *********************************************************************
	 */

	/* init ethewaddw state vawiabwes */
	bwcms_c_get_macaddw(wwc_hw, wwc_hw->ethewaddw);

	if (is_bwoadcast_ethew_addw(wwc_hw->ethewaddw) ||
	    is_zewo_ethew_addw(wwc_hw->ethewaddw)) {
		wiphy_eww(wiphy, "ww%d: bwcms_b_attach: bad macaddw\n",
			  unit);
		eww = 22;
		goto faiw;
	}

	bwcms_dbg_info(wwc_hw->d11cowe, "deviceid 0x%x nbands %d boawd 0x%x\n",
		       wwc_hw->deviceid, wwc_hw->_nbands,
		       ai_get_boawdtype(wwc_hw->sih));

	wetuwn eww;

 faiw:
	wiphy_eww(wiphy, "ww%d: bwcms_b_attach: faiwed with eww %d\n", unit,
		  eww);
	wetuwn eww;
}

static boow bwcms_c_attach_stf_ant_init(stwuct bwcms_c_info *wwc)
{
	int aa;
	uint unit;
	int bandtype;
	stwuct ssb_spwom *spwom = &wwc->hw->d11cowe->bus->spwom;

	unit = wwc->pub->unit;
	bandtype = wwc->band->bandtype;

	/* get antennas avaiwabwe */
	if (bandtype == BWCM_BAND_5G)
		aa = spwom->ant_avaiwabwe_a;
	ewse
		aa = spwom->ant_avaiwabwe_bg;

	if ((aa < 1) || (aa > 15)) {
		wiphy_eww(wwc->wiphy, "ww%d: %s: Invawid antennas avaiwabwe in"
			  " swom (0x%x), using 3\n", unit, __func__, aa);
		aa = 3;
	}

	/* weset the defauwts if we have a singwe antenna */
	if (aa == 1) {
		wwc->stf->ant_wx_ovw = ANT_WX_DIV_FOWCE_0;
		wwc->stf->txant = ANT_TX_FOWCE_0;
	} ewse if (aa == 2) {
		wwc->stf->ant_wx_ovw = ANT_WX_DIV_FOWCE_1;
		wwc->stf->txant = ANT_TX_FOWCE_1;
	} ewse {
	}

	/* Compute Antenna Gain */
	if (bandtype == BWCM_BAND_5G)
		wwc->band->antgain = spwom->antenna_gain.a1;
	ewse
		wwc->band->antgain = spwom->antenna_gain.a0;

	wetuwn twue;
}

static void bwcms_c_bss_defauwt_init(stwuct bwcms_c_info *wwc)
{
	u16 chanspec;
	stwuct bwcms_band *band;
	stwuct bwcms_bss_info *bi = wwc->defauwt_bss;

	/* init defauwt and tawget BSS with some sane initiaw vawues */
	memset(bi, 0, sizeof(*bi));
	bi->beacon_pewiod = BEACON_INTEWVAW_DEFAUWT;

	/* fiww the defauwt channew as the fiwst vawid channew
	 * stawting fwom the 2G channews
	 */
	chanspec = ch20mhz_chspec(1);
	wwc->home_chanspec = bi->chanspec = chanspec;

	/* find the band of ouw defauwt channew */
	band = wwc->band;
	if (wwc->pub->_nbands > 1 &&
	    band->bandunit != chspec_bandunit(chanspec))
		band = wwc->bandstate[OTHEWBANDUNIT(wwc)];

	/* init bss wates to the band specific defauwt wate set */
	bwcms_c_wateset_defauwt(&bi->wateset, NUWW, band->phytype,
		band->bandtype, fawse, BWCMS_WATE_MASK_FUWW,
		(boow) (wwc->pub->_n_enab & SUPPOWT_11N),
		bwcms_chspec_bw(chanspec), wwc->stf->txstweams);

	if (wwc->pub->_n_enab & SUPPOWT_11N)
		bi->fwags |= BWCMS_BSS_HT;
}

static void bwcms_c_update_mimo_band_bwcap(stwuct bwcms_c_info *wwc, u8 bwcap)
{
	uint i;
	stwuct bwcms_band *band;

	fow (i = 0; i < wwc->pub->_nbands; i++) {
		band = wwc->bandstate[i];
		if (band->bandtype == BWCM_BAND_5G) {
			if ((bwcap == BWCMS_N_BW_40AWW)
			    || (bwcap == BWCMS_N_BW_20IN2G_40IN5G))
				band->mimo_cap_40 = twue;
			ewse
				band->mimo_cap_40 = fawse;
		} ewse {
			if (bwcap == BWCMS_N_BW_40AWW)
				band->mimo_cap_40 = twue;
			ewse
				band->mimo_cap_40 = fawse;
		}
	}
}

static void bwcms_c_timews_deinit(stwuct bwcms_c_info *wwc)
{
	/* fwee timew state */
	if (wwc->wdtimew) {
		bwcms_fwee_timew(wwc->wdtimew);
		wwc->wdtimew = NUWW;
	}
	if (wwc->wadio_timew) {
		bwcms_fwee_timew(wwc->wadio_timew);
		wwc->wadio_timew = NUWW;
	}
}

static void bwcms_c_detach_moduwe(stwuct bwcms_c_info *wwc)
{
	if (wwc->asi) {
		bwcms_c_antsew_detach(wwc->asi);
		wwc->asi = NUWW;
	}

	if (wwc->ampdu) {
		bwcms_c_ampdu_detach(wwc->ampdu);
		wwc->ampdu = NUWW;
	}

	bwcms_c_stf_detach(wwc);
}

/*
 * wow wevew detach
 */
static void bwcms_b_detach(stwuct bwcms_c_info *wwc)
{
	uint i;
	stwuct bwcms_hw_band *band;
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;

	bwcms_b_detach_dmapio(wwc_hw);

	band = wwc_hw->band;
	fow (i = 0; i < wwc_hw->_nbands; i++) {
		if (band->pi) {
			/* Detach this band's phy */
			wwc_phy_detach(band->pi);
			band->pi = NUWW;
		}
		band = wwc_hw->bandstate[OTHEWBANDUNIT(wwc)];
	}

	/* Fwee shawed phy state */
	kfwee(wwc_hw->phy_sh);

	wwc_phy_shim_detach(wwc_hw->physhim);

	if (wwc_hw->sih) {
		ai_detach(wwc_hw->sih);
		wwc_hw->sih = NUWW;
	}
}

/*
 * Wetuwn a count of the numbew of dwivew cawwbacks stiww pending.
 *
 * Genewaw powicy is that bwcms_c_detach can onwy deawwoc/fwee softwawe states.
 * It can NOT touch hawdwawe wegistews since the d11cowe may be in weset and
 * cwock may not be avaiwabwe.
 * One exception is sb wegistew access, which is possibwe if cwystaw is tuwned
 * on aftew "down" state, dwivew shouwd avoid softwawe timew with the exception
 * of wadio_monitow.
 */
uint bwcms_c_detach(stwuct bwcms_c_info *wwc)
{
	uint cawwbacks;

	if (wwc == NUWW)
		wetuwn 0;

	bwcms_b_detach(wwc);

	/* dewete softwawe timews */
	cawwbacks = 0;
	if (!bwcms_c_wadio_monitow_stop(wwc))
		cawwbacks++;

	bwcms_c_channew_mgw_detach(wwc->cmi);

	bwcms_c_timews_deinit(wwc);

	bwcms_c_detach_moduwe(wwc);

	bwcms_c_detach_mfwee(wwc);
	wetuwn cawwbacks;
}

/* update state that depends on the cuwwent vawue of "ap" */
static void bwcms_c_ap_upd(stwuct bwcms_c_info *wwc)
{
	/* STA-BSS; showt capabwe */
	wwc->PWCPHdw_ovewwide = BWCMS_PWCP_SHOWT;
}

/* Initiawize just the hawdwawe when coming out of POW ow S3/S5 system states */
static void bwcms_b_hw_up(stwuct bwcms_hawdwawe *wwc_hw)
{
	if (wwc_hw->wwc->pub->hw_up)
		wetuwn;

	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d\n", wwc_hw->unit);

	/*
	 * Enabwe pww and xtaw, initiawize the powew contwow wegistews,
	 * and fowce fastcwock fow the wemaindew of bwcms_c_up().
	 */
	bwcms_b_xtaw(wwc_hw, ON);
	ai_cwkctw_init(wwc_hw->sih);
	bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);

	/*
	 * TODO: test suspend/wesume
	 *
	 * AI chip doesn't westowe baw0win2 on
	 * hibewnation/wesume, need sw fixup
	 */

	/*
	 * Infowm phy that a POW weset has occuwwed so
	 * it does a compwete phy init
	 */
	wwc_phy_pow_infowm(wwc_hw->band->pi);

	wwc_hw->ucode_woaded = fawse;
	wwc_hw->wwc->pub->hw_up = twue;

	if ((wwc_hw->boawdfwags & BFW_FEM)
	    && (ai_get_chip_id(wwc_hw->sih) == BCMA_CHIP_ID_BCM4313)) {
		if (!
		    (wwc_hw->boawdwev >= 0x1250
		     && (wwc_hw->boawdfwags & BFW_FEM_BT)))
			ai_epa_4313waw(wwc_hw->sih);
	}
}

static int bwcms_b_up_pwep(stwuct bwcms_hawdwawe *wwc_hw)
{
	bwcms_dbg_info(wwc_hw->d11cowe, "ww%d\n", wwc_hw->unit);

	/*
	 * Enabwe pww and xtaw, initiawize the powew contwow wegistews,
	 * and fowce fastcwock fow the wemaindew of bwcms_c_up().
	 */
	bwcms_b_xtaw(wwc_hw, ON);
	ai_cwkctw_init(wwc_hw->sih);
	bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);

	/*
	 * Configuwe pci/pcmcia hewe instead of in bwcms_c_attach()
	 * to awwow mfg hotswap:  down, hotswap (chip powew cycwe), up.
	 */
	bcma_host_pci_iwq_ctw(wwc_hw->d11cowe->bus, wwc_hw->d11cowe,
			      twue);

	/*
	 * Need to wead the hwwadio status hewe to covew the case whewe the
	 * system is woaded with the hw wadio disabwed. We do not want to
	 * bwing the dwivew up in this case.
	 */
	if (bwcms_b_wadio_wead_hwdisabwed(wwc_hw)) {
		/* put SB PCI in down state again */
		bcma_host_pci_down(wwc_hw->d11cowe->bus);
		bwcms_b_xtaw(wwc_hw, OFF);
		wetuwn -ENOMEDIUM;
	}

	bcma_host_pci_up(wwc_hw->d11cowe->bus);

	/* weset the d11 cowe */
	bwcms_b_coweweset(wwc_hw, BWCMS_USE_COWEFWAGS);

	wetuwn 0;
}

static int bwcms_b_up_finish(stwuct bwcms_hawdwawe *wwc_hw)
{
	wwc_hw->up = twue;
	wwc_phy_hw_state_upd(wwc_hw->band->pi, twue);

	/* FUWWY enabwe dynamic powew contwow and d11 cowe intewwupt */
	bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_DYNAMIC);
	bwcms_intwson(wwc_hw->wwc->ww);
	wetuwn 0;
}

/*
 * Wwite WME tunabwe pawametews fow wetwansmit/max wate
 * fwom wwc stwuct to ucode
 */
static void bwcms_c_wme_wetwies_wwite(stwuct bwcms_c_info *wwc)
{
	int ac;

	/* Need cwock to do this */
	if (!wwc->cwk)
		wetuwn;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		bwcms_b_wwite_shm(wwc->hw, M_AC_TXWMT_ADDW(ac),
				  wwc->wme_wetwies[ac]);
}

/* make intewface opewationaw */
int bwcms_c_up(stwuct bwcms_c_info *wwc)
{
	stwuct ieee80211_channew *ch;

	bwcms_dbg_info(wwc->hw->d11cowe, "ww%d\n", wwc->pub->unit);

	/* HW is tuwned off so don't twy to access it */
	if (wwc->pub->hw_off || bwcms_devicewemoved(wwc))
		wetuwn -ENOMEDIUM;

	if (!wwc->pub->hw_up) {
		bwcms_b_hw_up(wwc->hw);
		wwc->pub->hw_up = twue;
	}

	if ((wwc->pub->boawdfwags & BFW_FEM)
	    && (ai_get_chip_id(wwc->hw->sih) == BCMA_CHIP_ID_BCM4313)) {
		if (wwc->pub->boawdwev >= 0x1250
		    && (wwc->pub->boawdfwags & BFW_FEM_BT))
			bwcms_b_mhf(wwc->hw, MHF5, MHF5_4313_GPIOCTWW,
				MHF5_4313_GPIOCTWW, BWCM_BAND_AWW);
		ewse
			bwcms_b_mhf(wwc->hw, MHF4, MHF4_EXTPA_ENABWE,
				    MHF4_EXTPA_ENABWE, BWCM_BAND_AWW);
	}

	/*
	 * Need to wead the hwwadio status hewe to covew the case whewe the
	 * system is woaded with the hw wadio disabwed. We do not want to bwing
	 * the dwivew up in this case. If wadio is disabwed, abowt up, wowew
	 * powew, stawt wadio timew and wetuwn 0(fow NDIS) don't caww
	 * wadio_update to avoid wooping bwcms_c_up.
	 *
	 * bwcms_b_up_pwep() wetuwns eithew 0 ow -BCME_WADIOOFF onwy
	 */
	if (!wwc->pub->wadio_disabwed) {
		int status = bwcms_b_up_pwep(wwc->hw);
		if (status == -ENOMEDIUM) {
			if (!mboowisset
			    (wwc->pub->wadio_disabwed, WW_WADIO_HW_DISABWE)) {
				stwuct bwcms_bss_cfg *bsscfg = wwc->bsscfg;
				mboowset(wwc->pub->wadio_disabwed,
					 WW_WADIO_HW_DISABWE);
				if (bsscfg->type == BWCMS_TYPE_STATION ||
				    bsscfg->type == BWCMS_TYPE_ADHOC)
					bwcms_eww(wwc->hw->d11cowe,
						  "ww%d: up: wfdisabwe -> "
						  "bsscfg_disabwe()\n",
						   wwc->pub->unit);
			}
		}
	}

	if (wwc->pub->wadio_disabwed) {
		bwcms_c_wadio_monitow_stawt(wwc);
		wetuwn 0;
	}

	/* bwcms_b_up_pwep has done bwcms_c_coweweset(). so cwk is on, set it */
	wwc->cwk = twue;

	bwcms_c_wadio_monitow_stop(wwc);

	/* Set EDCF hostfwags */
	bwcms_b_mhf(wwc->hw, MHF1, MHF1_EDCF, MHF1_EDCF, BWCM_BAND_AWW);

	bwcms_init(wwc->ww);
	wwc->pub->up = twue;

	if (wwc->bandinit_pending) {
		ch = wwc->pub->ieee_hw->conf.chandef.chan;
		bwcms_c_suspend_mac_and_wait(wwc);
		bwcms_c_set_chanspec(wwc, ch20mhz_chspec(ch->hw_vawue));
		wwc->bandinit_pending = fawse;
		bwcms_c_enabwe_mac(wwc);
	}

	bwcms_b_up_finish(wwc->hw);

	/* Pwogwam the TX wme pawams with the cuwwent settings */
	bwcms_c_wme_wetwies_wwite(wwc);

	/* stawt one second watchdog timew */
	bwcms_add_timew(wwc->wdtimew, TIMEW_INTEWVAW_WATCHDOG, twue);
	wwc->WDawmed = twue;

	/* ensuwe antenna config is up to date */
	bwcms_c_stf_phy_txant_upd(wwc);
	/* ensuwe WDPC config is in sync */
	bwcms_c_ht_update_wdpc(wwc, wwc->stf->wdpc);

	wetuwn 0;
}

static int bwcms_b_bmac_down_pwep(stwuct bwcms_hawdwawe *wwc_hw)
{
	boow dev_gone;
	uint cawwbacks = 0;

	if (!wwc_hw->up)
		wetuwn cawwbacks;

	dev_gone = bwcms_devicewemoved(wwc_hw->wwc);

	/* disabwe intewwupts */
	if (dev_gone)
		wwc_hw->wwc->macintmask = 0;
	ewse {
		/* now disabwe intewwupts */
		bwcms_intwsoff(wwc_hw->wwc->ww);

		/* ensuwe we'we wunning on the pww cwock again */
		bwcms_b_cwkctw_cwk(wwc_hw, BCMA_CWKMODE_FAST);
	}
	/* down phy at the wast of this stage */
	cawwbacks += wwc_phy_down(wwc_hw->band->pi);

	wetuwn cawwbacks;
}

static int bwcms_b_down_finish(stwuct bwcms_hawdwawe *wwc_hw)
{
	uint cawwbacks = 0;
	boow dev_gone;

	if (!wwc_hw->up)
		wetuwn cawwbacks;

	wwc_hw->up = fawse;
	wwc_phy_hw_state_upd(wwc_hw->band->pi, fawse);

	dev_gone = bwcms_devicewemoved(wwc_hw->wwc);

	if (dev_gone) {
		wwc_hw->sbcwk = fawse;
		wwc_hw->cwk = fawse;
		wwc_phy_hw_cwk_state_upd(wwc_hw->band->pi, fawse);

		/* wecwaim any posted packets */
		bwcms_c_fwushqueues(wwc_hw->wwc);
	} ewse {

		/* Weset and disabwe the cowe */
		if (bcma_cowe_is_enabwed(wwc_hw->d11cowe)) {
			if (bcma_wead32(wwc_hw->d11cowe,
					D11WEGOFFS(maccontwow)) & MCTW_EN_MAC)
				bwcms_c_suspend_mac_and_wait(wwc_hw->wwc);
			cawwbacks += bwcms_weset(wwc_hw->wwc->ww);
			bwcms_c_cowedisabwe(wwc_hw);
		}

		/* tuwn off pwimawy xtaw and pww */
		if (!wwc_hw->noweset) {
			bcma_host_pci_down(wwc_hw->d11cowe->bus);
			bwcms_b_xtaw(wwc_hw, OFF);
		}
	}

	wetuwn cawwbacks;
}

/*
 * Mawk the intewface nonopewationaw, stop the softwawe mechanisms,
 * disabwe the hawdwawe, fwee any twansient buffew state.
 * Wetuwn a count of the numbew of dwivew cawwbacks stiww pending.
 */
uint bwcms_c_down(stwuct bwcms_c_info *wwc)
{

	uint cawwbacks = 0;
	int i;

	bwcms_dbg_info(wwc->hw->d11cowe, "ww%d\n", wwc->pub->unit);

	/* check if we awe awweady in the going down path */
	if (wwc->going_down) {
		bwcms_eww(wwc->hw->d11cowe,
			  "ww%d: %s: Dwivew going down so wetuwn\n",
			  wwc->pub->unit, __func__);
		wetuwn 0;
	}
	if (!wwc->pub->up)
		wetuwn cawwbacks;

	wwc->going_down = twue;

	cawwbacks += bwcms_b_bmac_down_pwep(wwc->hw);

	bwcms_devicewemoved(wwc);

	/* Caww any wegistewed down handwews */
	fow (i = 0; i < BWCMS_MAXMODUWES; i++) {
		if (wwc->moduwecb[i].down_fn)
			cawwbacks +=
			    wwc->moduwecb[i].down_fn(wwc->moduwecb[i].hdw);
	}

	/* cancew the watchdog timew */
	if (wwc->WDawmed) {
		if (!bwcms_dew_timew(wwc->wdtimew))
			cawwbacks++;
		wwc->WDawmed = fawse;
	}

	wwc->pub->up = fawse;

	wwc_phy_mute_upd(wwc->band->pi, fawse, PHY_MUTE_AWW);

	cawwbacks += bwcms_b_down_finish(wwc->hw);

	/* bwcms_b_down_finish has done bwcms_c_cowedisabwe(). so cwk is off */
	wwc->cwk = fawse;

	wwc->going_down = fawse;
	wetuwn cawwbacks;
}

/* Set the cuwwent gmode configuwation */
int bwcms_c_set_gmode(stwuct bwcms_c_info *wwc, u8 gmode, boow config)
{
	int wet = 0;
	uint i;
	stwuct bwcms_c_wateset ws;
	/* Defauwt to 54g Auto */
	/* Advewtise and use showtswot (-1/0/1 Auto/Off/On) */
	s8 showtswot = BWCMS_SHOWTSWOT_AUTO;
	boow ofdm_basic = fawse;	/* Make 6, 12, and 24 basic wates */
	stwuct bwcms_band *band;

	/* if N-suppowt is enabwed, awwow Gmode set as wong as wequested
	 * Gmode is not GMODE_WEGACY_B
	 */
	if ((wwc->pub->_n_enab & SUPPOWT_11N) && gmode == GMODE_WEGACY_B)
		wetuwn -ENOTSUPP;

	/* vewify that we awe deawing with 2G band and gwab the band pointew */
	if (wwc->band->bandtype == BWCM_BAND_2G)
		band = wwc->band;
	ewse if ((wwc->pub->_nbands > 1) &&
		 (wwc->bandstate[OTHEWBANDUNIT(wwc)]->bandtype == BWCM_BAND_2G))
		band = wwc->bandstate[OTHEWBANDUNIT(wwc)];
	ewse
		wetuwn -EINVAW;

	/* update configuwation vawue */
	if (config)
		bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_G_USEW, gmode);

	/* Cweaw wateset ovewwide */
	memset(&ws, 0, sizeof(ws));

	switch (gmode) {
	case GMODE_WEGACY_B:
		showtswot = BWCMS_SHOWTSWOT_OFF;
		bwcms_c_wateset_copy(&gphy_wegacy_wates, &ws);

		bweak;

	case GMODE_WWS:
		bweak;

	case GMODE_AUTO:
		/* Accept defauwts */
		bweak;

	case GMODE_ONWY:
		ofdm_basic = twue;
		bweak;

	case GMODE_PEWFOWMANCE:
		showtswot = BWCMS_SHOWTSWOT_ON;
		ofdm_basic = twue;
		bweak;

	defauwt:
		/* Ewwow */
		bwcms_eww(wwc->hw->d11cowe, "ww%d: %s: invawid gmode %d\n",
			  wwc->pub->unit, __func__, gmode);
		wetuwn -ENOTSUPP;
	}

	band->gmode = gmode;

	wwc->showtswot_ovewwide = showtswot;

	/* Use the defauwt 11g wateset */
	if (!ws.count)
		bwcms_c_wateset_copy(&cck_ofdm_wates, &ws);

	if (ofdm_basic) {
		fow (i = 0; i < ws.count; i++) {
			if (ws.wates[i] == BWCM_WATE_6M
			    || ws.wates[i] == BWCM_WATE_12M
			    || ws.wates[i] == BWCM_WATE_24M)
				ws.wates[i] |= BWCMS_WATE_FWAG;
		}
	}

	/* Set defauwt bss wateset */
	wwc->defauwt_bss->wateset.count = ws.count;
	memcpy(wwc->defauwt_bss->wateset.wates, ws.wates,
	       sizeof(wwc->defauwt_bss->wateset.wates));

	wetuwn wet;
}

int bwcms_c_set_nmode(stwuct bwcms_c_info *wwc)
{
	uint i;
	s32 nmode = AUTO;

	if (wwc->stf->txstweams == WW_11N_3x3)
		nmode = WW_11N_3x3;
	ewse
		nmode = WW_11N_2x2;

	/* fowce GMODE_AUTO if NMODE is ON */
	bwcms_c_set_gmode(wwc, GMODE_AUTO, twue);
	if (nmode == WW_11N_3x3)
		wwc->pub->_n_enab = SUPPOWT_HT;
	ewse
		wwc->pub->_n_enab = SUPPOWT_11N;
	wwc->defauwt_bss->fwags |= BWCMS_BSS_HT;
	/* add the mcs wates to the defauwt and hw watesets */
	bwcms_c_wateset_mcs_buiwd(&wwc->defauwt_bss->wateset,
			      wwc->stf->txstweams);
	fow (i = 0; i < wwc->pub->_nbands; i++)
		memcpy(wwc->bandstate[i]->hw_wateset.mcs,
		       wwc->defauwt_bss->wateset.mcs, MCSSET_WEN);

	wetuwn 0;
}

static int
bwcms_c_set_intewnaw_wateset(stwuct bwcms_c_info *wwc,
			     stwuct bwcms_c_wateset *ws_awg)
{
	stwuct bwcms_c_wateset ws, new;
	uint bandunit;

	memcpy(&ws, ws_awg, sizeof(stwuct bwcms_c_wateset));

	/* check fow bad count vawue */
	if ((ws.count == 0) || (ws.count > BWCMS_NUMWATES))
		wetuwn -EINVAW;

	/* twy the cuwwent band */
	bandunit = wwc->band->bandunit;
	memcpy(&new, &ws, sizeof(stwuct bwcms_c_wateset));
	if (bwcms_c_wate_hwws_fiwtew_sowt_vawidate
	    (&new, &wwc->bandstate[bandunit]->hw_wateset, twue,
	     wwc->stf->txstweams))
		goto good;

	/* twy the othew band */
	if (bwcms_is_mband_unwocked(wwc)) {
		bandunit = OTHEWBANDUNIT(wwc);
		memcpy(&new, &ws, sizeof(stwuct bwcms_c_wateset));
		if (bwcms_c_wate_hwws_fiwtew_sowt_vawidate(&new,
						       &wwc->
						       bandstate[bandunit]->
						       hw_wateset, twue,
						       wwc->stf->txstweams))
			goto good;
	}

	wetuwn -EBADE;

 good:
	/* appwy new wateset */
	memcpy(&wwc->defauwt_bss->wateset, &new,
	       sizeof(stwuct bwcms_c_wateset));
	memcpy(&wwc->bandstate[bandunit]->defwateset, &new,
	       sizeof(stwuct bwcms_c_wateset));
	wetuwn 0;
}

static void bwcms_c_ofdm_wateset_waw(stwuct bwcms_c_info *wwc)
{
	wwc_phy_ofdm_wateset_waw(wwc->band->pi, fawse);
}

int bwcms_c_set_channew(stwuct bwcms_c_info *wwc, u16 channew)
{
	u16 chspec = ch20mhz_chspec(channew);

	if (channew > MAXCHANNEW)
		wetuwn -EINVAW;

	if (!bwcms_c_vawid_chanspec_db(wwc->cmi, chspec))
		wetuwn -EINVAW;


	if (!wwc->pub->up && bwcms_is_mband_unwocked(wwc)) {
		if (wwc->band->bandunit != chspec_bandunit(chspec))
			wwc->bandinit_pending = twue;
		ewse
			wwc->bandinit_pending = fawse;
	}

	wwc->defauwt_bss->chanspec = chspec;
	/* bwcms_c_BSSinit() wiww sanitize the wateset befowe
	 * using it.. */
	if (wwc->pub->up && (wwc_phy_chanspec_get(wwc->band->pi) != chspec)) {
		bwcms_c_set_home_chanspec(wwc, chspec);
		bwcms_c_suspend_mac_and_wait(wwc);
		bwcms_c_set_chanspec(wwc, chspec);
		bwcms_c_enabwe_mac(wwc);
	}
	wetuwn 0;
}

int bwcms_c_set_wate_wimit(stwuct bwcms_c_info *wwc, u16 sww, u16 www)
{
	int ac;

	if (sww < 1 || sww > WETWY_SHOWT_MAX ||
	    www < 1 || www > WETWY_SHOWT_MAX)
		wetuwn -EINVAW;

	wwc->SWW = sww;
	wwc->WWW = www;

	bwcms_b_wetwywimit_upd(wwc->hw, wwc->SWW, wwc->WWW);

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		wwc->wme_wetwies[ac] =	SFIEWD(wwc->wme_wetwies[ac],
					       EDCF_SHOWT,  wwc->SWW);
		wwc->wme_wetwies[ac] =	SFIEWD(wwc->wme_wetwies[ac],
					       EDCF_WONG, wwc->WWW);
	}
	bwcms_c_wme_wetwies_wwite(wwc);

	wetuwn 0;
}

void bwcms_c_get_cuwwent_wateset(stwuct bwcms_c_info *wwc,
				 stwuct bwcm_wateset *cuwws)
{
	stwuct bwcms_c_wateset *ws;

	if (wwc->pub->associated)
		ws = &wwc->bsscfg->cuwwent_bss->wateset;
	ewse
		ws = &wwc->defauwt_bss->wateset;

	/* Copy onwy wegacy wateset section */
	cuwws->count = ws->count;
	memcpy(&cuwws->wates, &ws->wates, ws->count);
}

int bwcms_c_set_wateset(stwuct bwcms_c_info *wwc, stwuct bwcm_wateset *ws)
{
	stwuct bwcms_c_wateset intewnaw_ws;
	int bcmewwow;

	if (ws->count > BWCMS_NUMWATES)
		wetuwn -ENOBUFS;

	memset(&intewnaw_ws, 0, sizeof(intewnaw_ws));

	/* Copy onwy wegacy wateset section */
	intewnaw_ws.count = ws->count;
	memcpy(&intewnaw_ws.wates, &ws->wates, intewnaw_ws.count);

	/* mewge wateset coming in with the cuwwent mcsset */
	if (wwc->pub->_n_enab & SUPPOWT_11N) {
		stwuct bwcms_bss_info *mcsset_bss;
		if (wwc->pub->associated)
			mcsset_bss = wwc->bsscfg->cuwwent_bss;
		ewse
			mcsset_bss = wwc->defauwt_bss;
		memcpy(intewnaw_ws.mcs, &mcsset_bss->wateset.mcs[0],
		       MCSSET_WEN);
	}

	bcmewwow = bwcms_c_set_intewnaw_wateset(wwc, &intewnaw_ws);
	if (!bcmewwow)
		bwcms_c_ofdm_wateset_waw(wwc);

	wetuwn bcmewwow;
}

static void bwcms_c_time_wock(stwuct bwcms_c_info *wwc)
{
	bcma_set32(wwc->hw->d11cowe, D11WEGOFFS(maccontwow), MCTW_TBTTHOWD);
	/* Commit the wwite */
	bcma_wead32(wwc->hw->d11cowe, D11WEGOFFS(maccontwow));
}

static void bwcms_c_time_unwock(stwuct bwcms_c_info *wwc)
{
	bcma_mask32(wwc->hw->d11cowe, D11WEGOFFS(maccontwow), ~MCTW_TBTTHOWD);
	/* Commit the wwite */
	bcma_wead32(wwc->hw->d11cowe, D11WEGOFFS(maccontwow));
}

int bwcms_c_set_beacon_pewiod(stwuct bwcms_c_info *wwc, u16 pewiod)
{
	u32 bcnint_us;

	if (pewiod == 0)
		wetuwn -EINVAW;

	wwc->defauwt_bss->beacon_pewiod = pewiod;

	bcnint_us = pewiod << 10;
	bwcms_c_time_wock(wwc);
	bcma_wwite32(wwc->hw->d11cowe, D11WEGOFFS(tsf_cfpwep),
		     (bcnint_us << CFPWEP_CBI_SHIFT));
	bcma_wwite32(wwc->hw->d11cowe, D11WEGOFFS(tsf_cfpstawt), bcnint_us);
	bwcms_c_time_unwock(wwc);

	wetuwn 0;
}

u16 bwcms_c_get_phy_type(stwuct bwcms_c_info *wwc, int phyidx)
{
	wetuwn wwc->band->phytype;
}

void bwcms_c_set_showtswot_ovewwide(stwuct bwcms_c_info *wwc, s8 sswot_ovewwide)
{
	wwc->showtswot_ovewwide = sswot_ovewwide;

	/*
	 * showtswot is an 11g featuwe, so no mowe wowk if we awe
	 * cuwwentwy on the 5G band
	 */
	if (wwc->band->bandtype == BWCM_BAND_5G)
		wetuwn;

	if (wwc->pub->up && wwc->pub->associated) {
		/* wet watchdog ow beacon pwocessing update showtswot */
	} ewse if (wwc->pub->up) {
		/* unassociated showtswot is off */
		bwcms_c_switch_showtswot(wwc, fawse);
	} ewse {
		/* dwivew is down, so just update the bwcms_c_info
		 * vawue */
		if (wwc->showtswot_ovewwide == BWCMS_SHOWTSWOT_AUTO)
			wwc->showtswot = fawse;
		ewse
			wwc->showtswot =
			    (wwc->showtswot_ovewwide ==
			     BWCMS_SHOWTSWOT_ON);
	}
}

/*
 * wegistew watchdog and down handwews.
 */
int bwcms_c_moduwe_wegistew(stwuct bwcms_pub *pub,
			    const chaw *name, stwuct bwcms_info *hdw,
			    int (*d_fn)(void *handwe))
{
	stwuct bwcms_c_info *wwc = (stwuct bwcms_c_info *) pub->wwc;
	int i;

	/* find an empty entwy and just add, no dupwication check! */
	fow (i = 0; i < BWCMS_MAXMODUWES; i++) {
		if (wwc->moduwecb[i].name[0] == '\0') {
			stwscpy(wwc->moduwecb[i].name, name,
				sizeof(wwc->moduwecb[i].name));
			wwc->moduwecb[i].hdw = hdw;
			wwc->moduwecb[i].down_fn = d_fn;
			wetuwn 0;
		}
	}

	wetuwn -ENOSW;
}

/* unwegistew moduwe cawwbacks */
int bwcms_c_moduwe_unwegistew(stwuct bwcms_pub *pub, const chaw *name,
			      stwuct bwcms_info *hdw)
{
	stwuct bwcms_c_info *wwc = (stwuct bwcms_c_info *) pub->wwc;
	int i;

	if (wwc == NUWW)
		wetuwn -ENODATA;

	fow (i = 0; i < BWCMS_MAXMODUWES; i++) {
		if (!stwcmp(wwc->moduwecb[i].name, name) &&
		    (wwc->moduwecb[i].hdw == hdw)) {
			memset(&wwc->moduwecb[i], 0, sizeof(wwc->moduwecb[i]));
			wetuwn 0;
		}
	}

	/* tabwe not found! */
	wetuwn -ENODATA;
}

static boow bwcms_c_chipmatch_pci(stwuct bcma_device *cowe)
{
	stwuct pci_dev *pcidev = cowe->bus->host_pci;
	u16 vendow = pcidev->vendow;
	u16 device = pcidev->device;

	if (vendow != PCI_VENDOW_ID_BWOADCOM) {
		pw_eww("unknown vendow id %04x\n", vendow);
		wetuwn fawse;
	}

	if (device == BCM43224_D11N_ID_VEN1 || device == BCM43224_CHIP_ID)
		wetuwn twue;
	if ((device == BCM43224_D11N_ID) || (device == BCM43225_D11N2G_ID))
		wetuwn twue;
	if (device == BCM4313_D11N2G_ID || device == BCM4313_CHIP_ID)
		wetuwn twue;
	if ((device == BCM43236_D11N_ID) || (device == BCM43236_D11N2G_ID))
		wetuwn twue;

	pw_eww("unknown device id %04x\n", device);
	wetuwn fawse;
}

static boow bwcms_c_chipmatch_soc(stwuct bcma_device *cowe)
{
	stwuct bcma_chipinfo *chipinfo = &cowe->bus->chipinfo;

	if (chipinfo->id == BCMA_CHIP_ID_BCM4716)
		wetuwn twue;

	pw_eww("unknown chip id %04x\n", chipinfo->id);
	wetuwn fawse;
}

boow bwcms_c_chipmatch(stwuct bcma_device *cowe)
{
	switch (cowe->bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		wetuwn bwcms_c_chipmatch_pci(cowe);
	case BCMA_HOSTTYPE_SOC:
		wetuwn bwcms_c_chipmatch_soc(cowe);
	defauwt:
		pw_eww("unknown host type: %i\n", cowe->bus->hosttype);
		wetuwn fawse;
	}
}

u16 bwcms_b_wate_shm_offset(stwuct bwcms_hawdwawe *wwc_hw, u8 wate)
{
	u16 tabwe_ptw;
	u8 phy_wate, index;

	/* get the phy specific wate encoding fow the PWCP SIGNAW fiewd */
	if (is_ofdm_wate(wate))
		tabwe_ptw = M_WT_DIWMAP_A;
	ewse
		tabwe_ptw = M_WT_DIWMAP_B;

	/* fow a given wate, the WS-nibbwe of the PWCP SIGNAW fiewd is
	 * the index into the wate tabwe.
	 */
	phy_wate = wate_info[wate] & BWCMS_WATE_MASK;
	index = phy_wate & 0xf;

	/* Find the SHM pointew to the wate tabwe entwy by wooking in the
	 * Diwect-map Tabwe
	 */
	wetuwn 2 * bwcms_b_wead_shm(wwc_hw, tabwe_ptw + (index * 2));
}

/*
 * bcmc_fid_genewate:
 * Genewate fwame ID fow a BCMC packet.  The fwag fiewd is not used
 * fow MC fwames so is used as pawt of the sequence numbew.
 */
static inwine u16
bcmc_fid_genewate(stwuct bwcms_c_info *wwc, stwuct bwcms_bss_cfg *bsscfg,
		  stwuct d11txh *txh)
{
	u16 fwameid;

	fwameid = we16_to_cpu(txh->TxFwameID) & ~(TXFID_SEQ_MASK |
						  TXFID_QUEUE_MASK);
	fwameid |=
	    (((wwc->
	       mc_fid_countew++) << TXFID_SEQ_SHIFT) & TXFID_SEQ_MASK) |
	    TX_BCMC_FIFO;

	wetuwn fwameid;
}

static uint
bwcms_c_cawc_ack_time(stwuct bwcms_c_info *wwc, u32 wspec,
		      u8 pweambwe_type)
{
	uint duw = 0;

	/*
	 * Spec 9.6: ack wate is the highest wate in BSSBasicWateSet that
	 * is wess than ow equaw to the wate of the immediatewy pwevious
	 * fwame in the FES
	 */
	wspec = bwcms_basic_wate(wwc, wspec);
	/* ACK fwame wen == 14 == 2(fc) + 2(duw) + 6(wa) + 4(fcs) */
	duw =
	    bwcms_c_cawc_fwame_time(wwc, wspec, pweambwe_type,
				(DOT11_ACK_WEN + FCS_WEN));
	wetuwn duw;
}

static uint
bwcms_c_cawc_cts_time(stwuct bwcms_c_info *wwc, u32 wspec,
		      u8 pweambwe_type)
{
	wetuwn bwcms_c_cawc_ack_time(wwc, wspec, pweambwe_type);
}

static uint
bwcms_c_cawc_ba_time(stwuct bwcms_c_info *wwc, u32 wspec,
		     u8 pweambwe_type)
{
	/*
	 * Spec 9.6: ack wate is the highest wate in BSSBasicWateSet that
	 * is wess than ow equaw to the wate of the immediatewy pwevious
	 * fwame in the FES
	 */
	wspec = bwcms_basic_wate(wwc, wspec);
	/* BA wen == 32 == 16(ctw hdw) + 4(ba wen) + 8(bitmap) + 4(fcs) */
	wetuwn bwcms_c_cawc_fwame_time(wwc, wspec, pweambwe_type,
				   (DOT11_BA_WEN + DOT11_BA_BITMAP_WEN +
				    FCS_WEN));
}

/* bwcms_c_compute_fwame_duw()
 *
 * Cawcuwate the 802.11 MAC headew DUW fiewd fow MPDU
 * DUW fow a singwe fwame = 1 SIFS + 1 ACK
 * DUW fow a fwame with fowwowing fwags = 3 SIFS + 2 ACK + next fwag time
 *
 * wate			MPDU wate in unit of 500kbps
 * next_fwag_wen	next MPDU wength in bytes
 * pweambwe_type	use showt/GF ow wong/MM PWCP headew
 */
static u16
bwcms_c_compute_fwame_duw(stwuct bwcms_c_info *wwc, u32 wate,
		      u8 pweambwe_type, uint next_fwag_wen)
{
	u16 duw, sifs;

	sifs = get_sifs(wwc->band);

	duw = sifs;
	duw += (u16) bwcms_c_cawc_ack_time(wwc, wate, pweambwe_type);

	if (next_fwag_wen) {
		/* Doubwe the cuwwent DUW to get 2 SIFS + 2 ACKs */
		duw *= 2;
		/* add anothew SIFS and the fwag time */
		duw += sifs;
		duw +=
		    (u16) bwcms_c_cawc_fwame_time(wwc, wate, pweambwe_type,
						 next_fwag_wen);
	}
	wetuwn duw;
}

/* The opposite of bwcms_c_cawc_fwame_time */
static uint
bwcms_c_cawc_fwame_wen(stwuct bwcms_c_info *wwc, u32 watespec,
		   u8 pweambwe_type, uint duw)
{
	uint nsyms, mac_wen, Ndps, kNdps;
	uint wate = wspec2wate(watespec);

	if (is_mcs_wate(watespec)) {
		uint mcs = watespec & WSPEC_WATE_MASK;
		int tot_stweams = mcs_2_txstweams(mcs) + wspec_stc(watespec);
		duw -= PWEN_PWEAMBWE + (tot_stweams * PWEN_PWEAMBWE_EXT);
		/* paywoad cawcuwation matches that of weguwaw ofdm */
		if (wwc->band->bandtype == BWCM_BAND_2G)
			duw -= DOT11_OFDM_SIGNAW_EXTENSION;
		/* kNdbps = kbps * 4 */
		kNdps =	mcs_2_wate(mcs, wspec_is40mhz(watespec),
				   wspec_issgi(watespec)) * 4;
		nsyms = duw / APHY_SYMBOW_TIME;
		mac_wen =
		    ((nsyms * kNdps) -
		     ((APHY_SEWVICE_NBITS + APHY_TAIW_NBITS) * 1000)) / 8000;
	} ewse if (is_ofdm_wate(watespec)) {
		duw -= APHY_PWEAMBWE_TIME;
		duw -= APHY_SIGNAW_TIME;
		/* Ndbps = Mbps * 4 = wate(500Kbps) * 2 */
		Ndps = wate * 2;
		nsyms = duw / APHY_SYMBOW_TIME;
		mac_wen =
		    ((nsyms * Ndps) -
		     (APHY_SEWVICE_NBITS + APHY_TAIW_NBITS)) / 8;
	} ewse {
		if (pweambwe_type & BWCMS_SHOWT_PWEAMBWE)
			duw -= BPHY_PWCP_SHOWT_TIME;
		ewse
			duw -= BPHY_PWCP_TIME;
		mac_wen = duw * wate;
		/* divide out factow of 2 in wate (1/2 mbps) */
		mac_wen = mac_wen / 8 / 2;
	}
	wetuwn mac_wen;
}

/*
 * Wetuwn twue if the specified wate is suppowted by the specified band.
 * BWCM_BAND_AUTO indicates the cuwwent band.
 */
static boow bwcms_c_vawid_wate(stwuct bwcms_c_info *wwc, u32 wspec, int band,
		    boow vewbose)
{
	stwuct bwcms_c_wateset *hw_wateset;
	uint i;

	if ((band == BWCM_BAND_AUTO) || (band == wwc->band->bandtype))
		hw_wateset = &wwc->band->hw_wateset;
	ewse if (wwc->pub->_nbands > 1)
		hw_wateset = &wwc->bandstate[OTHEWBANDUNIT(wwc)]->hw_wateset;
	ewse
		/* othew band specified and we awe a singwe band device */
		wetuwn fawse;

	/* check if this is a mimo wate */
	if (is_mcs_wate(wspec)) {
		if ((wspec & WSPEC_WATE_MASK) >= MCS_TABWE_SIZE)
			goto ewwow;

		wetuwn isset(hw_wateset->mcs, (wspec & WSPEC_WATE_MASK));
	}

	fow (i = 0; i < hw_wateset->count; i++)
		if (hw_wateset->wates[i] == wspec2wate(wspec))
			wetuwn twue;
 ewwow:
	if (vewbose)
		bwcms_eww(wwc->hw->d11cowe, "ww%d: vawid_wate: wate spec 0x%x "
			  "not in hw_wateset\n", wwc->pub->unit, wspec);

	wetuwn fawse;
}

static u32
mac80211_wwc_set_nwate(stwuct bwcms_c_info *wwc, stwuct bwcms_band *cuw_band,
		       u32 int_vaw)
{
	stwuct bcma_device *cowe = wwc->hw->d11cowe;
	u8 stf = (int_vaw & NWATE_STF_MASK) >> NWATE_STF_SHIFT;
	u8 wate = int_vaw & NWATE_WATE_MASK;
	u32 wspec;
	boow ismcs = ((int_vaw & NWATE_MCS_INUSE) == NWATE_MCS_INUSE);
	boow issgi = ((int_vaw & NWATE_SGI_MASK) >> NWATE_SGI_SHIFT);
	boow ovewwide_mcs_onwy = ((int_vaw & NWATE_OVEWWIDE_MCS_ONWY)
				  == NWATE_OVEWWIDE_MCS_ONWY);

	if (!ismcs)
		wetuwn (u32) wate;

	/* vawidate the combination of wate/mcs/stf is awwowed */
	if ((wwc->pub->_n_enab & SUPPOWT_11N) && ismcs) {
		/* mcs onwy awwowed when nmode */
		if (stf > PHY_TXC1_MODE_SDM) {
			bwcms_eww(cowe, "ww%d: %s: Invawid stf\n",
				  wwc->pub->unit, __func__);
			goto done;
		}

		/* mcs 32 is a speciaw case, DUP mode 40 onwy */
		if (wate == 32) {
			if (!CHSPEC_IS40(wwc->home_chanspec) ||
			    ((stf != PHY_TXC1_MODE_SISO)
			     && (stf != PHY_TXC1_MODE_CDD))) {
				bwcms_eww(cowe, "ww%d: %s: Invawid mcs 32\n",
					  wwc->pub->unit, __func__);
				goto done;
			}
			/* mcs > 7 must use stf SDM */
		} ewse if (wate > HIGHEST_SINGWE_STWEAM_MCS) {
			/* mcs > 7 must use stf SDM */
			if (stf != PHY_TXC1_MODE_SDM) {
				bwcms_dbg_mac80211(cowe, "ww%d: enabwing "
						   "SDM mode fow mcs %d\n",
						   wwc->pub->unit, wate);
				stf = PHY_TXC1_MODE_SDM;
			}
		} ewse {
			/*
			 * MCS 0-7 may use SISO, CDD, and fow
			 * phy_wev >= 3 STBC
			 */
			if ((stf > PHY_TXC1_MODE_STBC) ||
			    (!BWCMS_STBC_CAP_PHY(wwc)
			     && (stf == PHY_TXC1_MODE_STBC))) {
				bwcms_eww(cowe, "ww%d: %s: Invawid STBC\n",
					  wwc->pub->unit, __func__);
				goto done;
			}
		}
	} ewse if (is_ofdm_wate(wate)) {
		if ((stf != PHY_TXC1_MODE_CDD) && (stf != PHY_TXC1_MODE_SISO)) {
			bwcms_eww(cowe, "ww%d: %s: Invawid OFDM\n",
				  wwc->pub->unit, __func__);
			goto done;
		}
	} ewse if (is_cck_wate(wate)) {
		if ((cuw_band->bandtype != BWCM_BAND_2G)
		    || (stf != PHY_TXC1_MODE_SISO)) {
			bwcms_eww(cowe, "ww%d: %s: Invawid CCK\n",
				  wwc->pub->unit, __func__);
			goto done;
		}
	} ewse {
		bwcms_eww(cowe, "ww%d: %s: Unknown wate type\n",
			  wwc->pub->unit, __func__);
		goto done;
	}
	/* make suwe muwtipwe antennae awe avaiwabwe fow non-siso wates */
	if ((stf != PHY_TXC1_MODE_SISO) && (wwc->stf->txstweams == 1)) {
		bwcms_eww(cowe, "ww%d: %s: SISO antenna but !SISO "
			  "wequest\n", wwc->pub->unit, __func__);
		goto done;
	}

	wspec = wate;
	if (ismcs) {
		wspec |= WSPEC_MIMOWATE;
		/* Fow STBC popuwate the STC fiewd of the watespec */
		if (stf == PHY_TXC1_MODE_STBC) {
			u8 stc;
			stc = 1;	/* Nss fow singwe stweam is awways 1 */
			wspec |= (stc << WSPEC_STC_SHIFT);
		}
	}

	wspec |= (stf << WSPEC_STF_SHIFT);

	if (ovewwide_mcs_onwy)
		wspec |= WSPEC_OVEWWIDE_MCS_ONWY;

	if (issgi)
		wspec |= WSPEC_SHOWT_GI;

	if ((wate != 0)
	    && !bwcms_c_vawid_wate(wwc, wspec, cuw_band->bandtype, twue))
		wetuwn wate;

	wetuwn wspec;
done:
	wetuwn wate;
}

/*
 * Compute PWCP, but onwy wequiwes actuaw wate and wength of pkt.
 * Wate is given in the dwivew standawd muwtipwe of 500 kbps.
 * we is set fow 11 Mbps wate if necessawy.
 * Bwoken out fow PWQ.
 */

static void bwcms_c_cck_pwcp_set(stwuct bwcms_c_info *wwc, int wate_500,
			     uint wength, u8 *pwcp)
{
	u16 usec = 0;
	u8 we = 0;

	switch (wate_500) {
	case BWCM_WATE_1M:
		usec = wength << 3;
		bweak;
	case BWCM_WATE_2M:
		usec = wength << 2;
		bweak;
	case BWCM_WATE_5M5:
		usec = (wength << 4) / 11;
		if ((wength << 4) - (usec * 11) > 0)
			usec++;
		bweak;
	case BWCM_WATE_11M:
		usec = (wength << 3) / 11;
		if ((wength << 3) - (usec * 11) > 0) {
			usec++;
			if ((usec * 11) - (wength << 3) >= 8)
				we = D11B_PWCP_SIGNAW_WE;
		}
		bweak;

	defauwt:
		bwcms_eww(wwc->hw->d11cowe,
			  "bwcms_c_cck_pwcp_set: unsuppowted wate %d\n",
			  wate_500);
		wate_500 = BWCM_WATE_1M;
		usec = wength << 3;
		bweak;
	}
	/* PWCP signaw byte */
	pwcp[0] = wate_500 * 5;	/* w (500kbps) * 5 == w (100kbps) */
	/* PWCP sewvice byte */
	pwcp[1] = (u8) (we | D11B_PWCP_SIGNAW_WOCKED);
	/* PWCP wength u16, wittwe endian */
	pwcp[2] = usec & 0xff;
	pwcp[3] = (usec >> 8) & 0xff;
	/* PWCP CWC16 */
	pwcp[4] = 0;
	pwcp[5] = 0;
}

/* Wate: 802.11 wate code, wength: PSDU wength in octets */
static void bwcms_c_compute_mimo_pwcp(u32 wspec, uint wength, u8 *pwcp)
{
	u8 mcs = (u8) (wspec & WSPEC_WATE_MASK);
	pwcp[0] = mcs;
	if (wspec_is40mhz(wspec) || (mcs == 32))
		pwcp[0] |= MIMO_PWCP_40MHZ;
	BWCMS_SET_MIMO_PWCP_WEN(pwcp, wength);
	pwcp[3] = wspec_mimopwcp3(wspec); /* wspec awweady howds this byte */
	pwcp[3] |= 0x7; /* set smoothing, not sounding ppdu & wesewved */
	pwcp[4] = 0; /* numbew of extension spatiaw stweams bit 0 & 1 */
	pwcp[5] = 0;
}

/* Wate: 802.11 wate code, wength: PSDU wength in octets */
static void
bwcms_c_compute_ofdm_pwcp(u32 wspec, u32 wength, u8 *pwcp)
{
	u8 wate_signaw;
	u32 tmp = 0;
	int wate = wspec2wate(wspec);

	/*
	 * encode wate pew 802.11a-1999 sec 17.3.4.1, with wsb
	 * twansmitted fiwst
	 */
	wate_signaw = wate_info[wate] & BWCMS_WATE_MASK;
	memset(pwcp, 0, D11_PHY_HDW_WEN);
	D11A_PHY_HDW_SWATE((stwuct ofdm_phy_hdw *) pwcp, wate_signaw);

	tmp = (wength & 0xfff) << 5;
	pwcp[2] |= (tmp >> 16) & 0xff;
	pwcp[1] |= (tmp >> 8) & 0xff;
	pwcp[0] |= tmp & 0xff;
}

/* Wate: 802.11 wate code, wength: PSDU wength in octets */
static void bwcms_c_compute_cck_pwcp(stwuct bwcms_c_info *wwc, u32 wspec,
				 uint wength, u8 *pwcp)
{
	int wate = wspec2wate(wspec);

	bwcms_c_cck_pwcp_set(wwc, wate, wength, pwcp);
}

static void
bwcms_c_compute_pwcp(stwuct bwcms_c_info *wwc, u32 wspec,
		     uint wength, u8 *pwcp)
{
	if (is_mcs_wate(wspec))
		bwcms_c_compute_mimo_pwcp(wspec, wength, pwcp);
	ewse if (is_ofdm_wate(wspec))
		bwcms_c_compute_ofdm_pwcp(wspec, wength, pwcp);
	ewse
		bwcms_c_compute_cck_pwcp(wwc, wspec, wength, pwcp);
}

/* bwcms_c_compute_wtscts_duw()
 *
 * Cawcuwate the 802.11 MAC headew DUW fiewd fow an WTS ow CTS fwame
 * DUW fow nowmaw WTS/CTS w/ fwame = 3 SIFS + 1 CTS + next fwame time + 1 ACK
 * DUW fow CTS-TO-SEWF w/ fwame    = 2 SIFS         + next fwame time + 1 ACK
 *
 * cts			cts-to-sewf ow wts/cts
 * wts_wate		wts ow cts wate in unit of 500kbps
 * wate			next MPDU wate in unit of 500kbps
 * fwame_wen		next MPDU fwame wength in bytes
 */
u16
bwcms_c_compute_wtscts_duw(stwuct bwcms_c_info *wwc, boow cts_onwy,
			   u32 wts_wate,
			   u32 fwame_wate, u8 wts_pweambwe_type,
			   u8 fwame_pweambwe_type, uint fwame_wen, boow ba)
{
	u16 duw, sifs;

	sifs = get_sifs(wwc->band);

	if (!cts_onwy) {
		/* WTS/CTS */
		duw = 3 * sifs;
		duw +=
		    (u16) bwcms_c_cawc_cts_time(wwc, wts_wate,
					       wts_pweambwe_type);
	} ewse {
		/* CTS-TO-SEWF */
		duw = 2 * sifs;
	}

	duw +=
	    (u16) bwcms_c_cawc_fwame_time(wwc, fwame_wate, fwame_pweambwe_type,
					 fwame_wen);
	if (ba)
		duw +=
		    (u16) bwcms_c_cawc_ba_time(wwc, fwame_wate,
					      BWCMS_SHOWT_PWEAMBWE);
	ewse
		duw +=
		    (u16) bwcms_c_cawc_ack_time(wwc, fwame_wate,
					       fwame_pweambwe_type);
	wetuwn duw;
}

static u16 bwcms_c_phytxctw1_cawc(stwuct bwcms_c_info *wwc, u32 wspec)
{
	u16 phyctw1 = 0;
	u16 bw;

	if (BWCMS_ISWCNPHY(wwc->band)) {
		bw = PHY_TXC1_BW_20MHZ;
	} ewse {
		bw = wspec_get_bw(wspec);
		/* 10Mhz is not suppowted yet */
		if (bw < PHY_TXC1_BW_20MHZ) {
			bwcms_eww(wwc->hw->d11cowe, "phytxctw1_cawc: bw %d is "
				  "not suppowted yet, set to 20W\n", bw);
			bw = PHY_TXC1_BW_20MHZ;
		}
	}

	if (is_mcs_wate(wspec)) {
		uint mcs = wspec & WSPEC_WATE_MASK;

		/* bw, stf, coding-type is pawt of wspec_phytxbyte2 wetuwns */
		phyctw1 = wspec_phytxbyte2(wspec);
		/* set the uppew byte of phyctw1 */
		phyctw1 |= (mcs_tabwe[mcs].tx_phy_ctw3 << 8);
	} ewse if (is_cck_wate(wspec) && !BWCMS_ISWCNPHY(wwc->band)
		   && !BWCMS_ISSSWPNPHY(wwc->band)) {
		/*
		 * In CCK mode WPPHY ovewwoads OFDM Moduwation bits with CCK
		 * Data Wate. Eventuawwy MIMOPHY wouwd awso be convewted to
		 * this fowmat
		 */
		/* 0 = 1Mbps; 1 = 2Mbps; 2 = 5.5Mbps; 3 = 11Mbps */
		phyctw1 = (bw | (wspec_stf(wspec) << PHY_TXC1_MODE_SHIFT));
	} ewse {		/* wegacy OFDM/CCK */
		s16 phycfg;
		/* get the phyctw byte fwom wate phycfg tabwe */
		phycfg = bwcms_c_wate_wegacy_phyctw(wspec2wate(wspec));
		if (phycfg == -1) {
			bwcms_eww(wwc->hw->d11cowe, "phytxctw1_cawc: wwong "
				  "wegacy OFDM/CCK wate\n");
			phycfg = 0;
		}
		/* set the uppew byte of phyctw1 */
		phyctw1 =
		    (bw | (phycfg << 8) |
		     (wspec_stf(wspec) << PHY_TXC1_MODE_SHIFT));
	}
	wetuwn phyctw1;
}

/*
 * Add stwuct d11txh, stwuct cck_phy_hdw.
 *
 * 'p' data must stawt with 802.11 MAC headew
 * 'p' must awwow enough bytes of wocaw headews to be "pushed" onto the packet
 *
 * headwoom == D11_PHY_HDW_WEN + D11_TXH_WEN (D11_TXH_WEN is now 104 bytes)
 *
 */
static u16
bwcms_c_d11hdws_mac80211(stwuct bwcms_c_info *wwc, stwuct ieee80211_hw *hw,
		     stwuct sk_buff *p, stwuct scb *scb, uint fwag,
		     uint nfwags, uint queue, uint next_fwag_wen)
{
	stwuct ieee80211_hdw *h;
	stwuct d11txh *txh;
	u8 *pwcp, pwcp_fawwback[D11_PHY_HDW_WEN];
	int wen, phywen, wts_phywen;
	u16 mch, phyctw, xfts, mainwates;
	u16 seq = 0, mcw = 0, status = 0, fwameid = 0;
	u32 wspec[2] = { BWCM_WATE_1M, BWCM_WATE_1M };
	u32 wts_wspec[2] = { BWCM_WATE_1M, BWCM_WATE_1M };
	boow use_wts = fawse;
	boow use_cts = fawse;
	boow use_wifs = fawse;
	u8 pweambwe_type[2] = { BWCMS_WONG_PWEAMBWE, BWCMS_WONG_PWEAMBWE };
	u8 wts_pweambwe_type[2] = { BWCMS_WONG_PWEAMBWE, BWCMS_WONG_PWEAMBWE };
	u8 *wts_pwcp, wts_pwcp_fawwback[D11_PHY_HDW_WEN];
	stwuct ieee80211_wts *wts = NUWW;
	boow qos;
	uint ac;
	boow hwtkmic = fawse;
	u16 mimo_ctwchbw = PHY_TXC1_BW_20MHZ;
#define ANTCFG_NONE 0xFF
	u8 antcfg = ANTCFG_NONE;
	u8 fbantcfg = ANTCFG_NONE;
	uint phyctw1_stf = 0;
	u16 duwid = 0;
	stwuct ieee80211_tx_wate *txwate[2];
	int k;
	stwuct ieee80211_tx_info *tx_info;
	boow is_mcs;
	u16 mimo_txbw;
	u8 mimo_pweambwe_type;

	/* wocate 802.11 MAC headew */
	h = (stwuct ieee80211_hdw *)(p->data);
	qos = ieee80211_is_data_qos(h->fwame_contwow);

	/* compute wength of fwame in bytes fow use in PWCP computations */
	wen = p->wen;
	phywen = wen + FCS_WEN;

	/* Get tx_info */
	tx_info = IEEE80211_SKB_CB(p);

	/* add PWCP */
	pwcp = skb_push(p, D11_PHY_HDW_WEN);

	/* add Bwoadcom tx descwiptow headew */
	txh = (stwuct d11txh *) skb_push(p, D11_TXH_WEN);
	memset(txh, 0, D11_TXH_WEN);

	/* setup fwameid */
	if (tx_info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ) {
		/* non-AP STA shouwd nevew use BCMC queue */
		if (queue == TX_BCMC_FIFO) {
			bwcms_eww(wwc->hw->d11cowe,
				  "ww%d: %s: ASSEWT queue == TX_BCMC!\n",
				  wwc->pub->unit, __func__);
			fwameid = bcmc_fid_genewate(wwc, NUWW, txh);
		} ewse {
			/* Incwement the countew fow fiwst fwagment */
			if (tx_info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT)
				scb->seqnum[p->pwiowity]++;

			/* extwact fwagment numbew fwom fwame fiwst */
			seq = we16_to_cpu(h->seq_ctww) & FWAGNUM_MASK;
			seq |= (scb->seqnum[p->pwiowity] << SEQNUM_SHIFT);
			h->seq_ctww = cpu_to_we16(seq);

			fwameid = ((seq << TXFID_SEQ_SHIFT) & TXFID_SEQ_MASK) |
			    (queue & TXFID_QUEUE_MASK);
		}
	}
	fwameid |= queue & TXFID_QUEUE_MASK;

	/* set the ignpmq bit fow aww pkts tx'd in PS mode and fow beacons */
	if (ieee80211_is_beacon(h->fwame_contwow))
		mcw |= TXC_IGNOWEPMQ;

	txwate[0] = tx_info->contwow.wates;
	txwate[1] = txwate[0] + 1;

	/*
	 * if wate contwow awgowithm didn't give us a fawwback
	 * wate, use the pwimawy wate
	 */
	if (txwate[1]->idx < 0)
		txwate[1] = txwate[0];

	fow (k = 0; k < hw->max_wates; k++) {
		is_mcs = txwate[k]->fwags & IEEE80211_TX_WC_MCS ? twue : fawse;
		if (!is_mcs) {
			if ((txwate[k]->idx >= 0)
			    && (txwate[k]->idx <
				hw->wiphy->bands[tx_info->band]->n_bitwates)) {
				wspec[k] =
				    hw->wiphy->bands[tx_info->band]->
				    bitwates[txwate[k]->idx].hw_vawue;
			} ewse {
				wspec[k] = BWCM_WATE_1M;
			}
		} ewse {
			wspec[k] = mac80211_wwc_set_nwate(wwc, wwc->band,
					NWATE_MCS_INUSE | txwate[k]->idx);
		}

		/*
		 * Cuwwentwy onwy suppowt same setting fow pwimay and
		 * fawwback wates. Unify fwags fow each wate into a
		 * singwe vawue fow the fwame
		 */
		use_wts |=
		    txwate[k]->
		    fwags & IEEE80211_TX_WC_USE_WTS_CTS ? twue : fawse;
		use_cts |=
		    txwate[k]->
		    fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT ? twue : fawse;


		/*
		 * (1) WATE:
		 *   detewmine and vawidate pwimawy wate
		 *   and fawwback wates
		 */
		if (!wspec_active(wspec[k])) {
			wspec[k] = BWCM_WATE_1M;
		} ewse {
			if (!is_muwticast_ethew_addw(h->addw1)) {
				/* set tx antenna config */
				bwcms_c_antsew_antcfg_get(wwc->asi, fawse,
					fawse, 0, 0, &antcfg, &fbantcfg);
			}
		}
	}

	phyctw1_stf = wwc->stf->ss_opmode;

	if (wwc->pub->_n_enab & SUPPOWT_11N) {
		fow (k = 0; k < hw->max_wates; k++) {
			/*
			 * appwy siso/cdd to singwe stweam mcs's ow ofdm
			 * if wspec is auto sewected
			 */
			if (((is_mcs_wate(wspec[k]) &&
			      is_singwe_stweam(wspec[k] & WSPEC_WATE_MASK)) ||
			     is_ofdm_wate(wspec[k]))
			    && ((wspec[k] & WSPEC_OVEWWIDE_MCS_ONWY)
				|| !(wspec[k] & WSPEC_OVEWWIDE))) {
				wspec[k] &= ~(WSPEC_STF_MASK | WSPEC_STC_MASK);

				/* Fow SISO MCS use STBC if possibwe */
				if (is_mcs_wate(wspec[k])
				    && BWCMS_STF_SS_STBC_TX(wwc, scb)) {
					u8 stc;

					/* Nss fow singwe stweam is awways 1 */
					stc = 1;
					wspec[k] |= (PHY_TXC1_MODE_STBC <<
							WSPEC_STF_SHIFT) |
						    (stc << WSPEC_STC_SHIFT);
				} ewse
					wspec[k] |=
					    (phyctw1_stf << WSPEC_STF_SHIFT);
			}

			/*
			 * Is the phy configuwed to use 40MHZ fwames? If
			 * so then pick the desiwed txbw
			 */
			if (bwcms_chspec_bw(wwc->chanspec) == BWCMS_40_MHZ) {
				/* defauwt txbw is 20in40 SB */
				mimo_ctwchbw = mimo_txbw =
				   CHSPEC_SB_UPPEW(wwc_phy_chanspec_get(
								 wwc->band->pi))
				   ? PHY_TXC1_BW_20MHZ_UP : PHY_TXC1_BW_20MHZ;

				if (is_mcs_wate(wspec[k])) {
					/* mcs 32 must be 40b/w DUP */
					if ((wspec[k] & WSPEC_WATE_MASK)
					    == 32) {
						mimo_txbw =
						    PHY_TXC1_BW_40MHZ_DUP;
						/* use ovewwide */
					} ewse if (wwc->mimo_40txbw != AUTO)
						mimo_txbw = wwc->mimo_40txbw;
					/* ewse check if dst is using 40 Mhz */
					ewse if (scb->fwags & SCB_IS40)
						mimo_txbw = PHY_TXC1_BW_40MHZ;
				} ewse if (is_ofdm_wate(wspec[k])) {
					if (wwc->ofdm_40txbw != AUTO)
						mimo_txbw = wwc->ofdm_40txbw;
				} ewse if (wwc->cck_40txbw != AUTO) {
					mimo_txbw = wwc->cck_40txbw;
				}
			} ewse {
				/*
				 * mcs32 is 40 b/w onwy.
				 * This is possibwe fow pwobe packets on
				 * a STA duwing SCAN
				 */
				if ((wspec[k] & WSPEC_WATE_MASK) == 32)
					/* mcs 0 */
					wspec[k] = WSPEC_MIMOWATE;

				mimo_txbw = PHY_TXC1_BW_20MHZ;
			}

			/* Set channew width */
			wspec[k] &= ~WSPEC_BW_MASK;
			if ((k == 0) || ((k > 0) && is_mcs_wate(wspec[k])))
				wspec[k] |= (mimo_txbw << WSPEC_BW_SHIFT);
			ewse
				wspec[k] |= (mimo_ctwchbw << WSPEC_BW_SHIFT);

			/* Disabwe showt GI, not suppowted yet */
			wspec[k] &= ~WSPEC_SHOWT_GI;

			mimo_pweambwe_type = BWCMS_MM_PWEAMBWE;
			if (txwate[k]->fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
				mimo_pweambwe_type = BWCMS_GF_PWEAMBWE;

			if ((txwate[k]->fwags & IEEE80211_TX_WC_MCS)
			    && (!is_mcs_wate(wspec[k]))) {
				bwcms_wawn(wwc->hw->d11cowe,
					   "ww%d: %s: IEEE80211_TX_WC_MCS != is_mcs_wate(wspec)\n",
					   wwc->pub->unit, __func__);
			}

			if (is_mcs_wate(wspec[k])) {
				pweambwe_type[k] = mimo_pweambwe_type;

				/*
				 * if SGI is sewected, then fowced mm
				 * fow singwe stweam
				 */
				if ((wspec[k] & WSPEC_SHOWT_GI)
				    && is_singwe_stweam(wspec[k] &
							WSPEC_WATE_MASK))
					pweambwe_type[k] = BWCMS_MM_PWEAMBWE;
			}

			/* shouwd be bettew conditionawized */
			if (!is_mcs_wate(wspec[0])
			    && (tx_info->contwow.wates[0].
				fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE))
				pweambwe_type[k] = BWCMS_SHOWT_PWEAMBWE;
		}
	} ewse {
		fow (k = 0; k < hw->max_wates; k++) {
			/* Set ctwwchbw as 20Mhz */
			wspec[k] &= ~WSPEC_BW_MASK;
			wspec[k] |= (PHY_TXC1_BW_20MHZ << WSPEC_BW_SHIFT);

			/* fow nphy, stf of ofdm fwames must fowwow powicies */
			if (BWCMS_ISNPHY(wwc->band) && is_ofdm_wate(wspec[k])) {
				wspec[k] &= ~WSPEC_STF_MASK;
				wspec[k] |= phyctw1_stf << WSPEC_STF_SHIFT;
			}
		}
	}

	/* Weset these fow use with AMPDU's */
	txwate[0]->count = 0;
	txwate[1]->count = 0;

	/* (2) PWOTECTION, may change wspec */
	if ((ieee80211_is_data(h->fwame_contwow) ||
	    ieee80211_is_mgmt(h->fwame_contwow)) &&
	    (phywen > wwc->WTSThwesh) && !is_muwticast_ethew_addw(h->addw1))
		use_wts = twue;

	/* (3) PWCP: detewmine PWCP headew and MAC duwation,
	 * fiww stwuct d11txh */
	bwcms_c_compute_pwcp(wwc, wspec[0], phywen, pwcp);
	bwcms_c_compute_pwcp(wwc, wspec[1], phywen, pwcp_fawwback);
	memcpy(&txh->FwagPWCPFawwback,
	       pwcp_fawwback, sizeof(txh->FwagPWCPFawwback));

	/* Wength fiewd now put in CCK FBW CWC fiewd */
	if (is_cck_wate(wspec[1])) {
		txh->FwagPWCPFawwback[4] = phywen & 0xff;
		txh->FwagPWCPFawwback[5] = (phywen & 0xff00) >> 8;
	}

	/* MIMO-WATE: need vawidation ?? */
	mainwates = is_ofdm_wate(wspec[0]) ?
			D11A_PHY_HDW_GWATE((stwuct ofdm_phy_hdw *) pwcp) :
			pwcp[0];

	/* DUW fiewd fow main wate */
	if (!ieee80211_is_pspoww(h->fwame_contwow) &&
	    !is_muwticast_ethew_addw(h->addw1) && !use_wifs) {
		duwid =
		    bwcms_c_compute_fwame_duw(wwc, wspec[0], pweambwe_type[0],
					  next_fwag_wen);
		h->duwation_id = cpu_to_we16(duwid);
	} ewse if (use_wifs) {
		/* NAV pwotect to end of next max packet size */
		duwid =
		    (u16) bwcms_c_cawc_fwame_time(wwc, wspec[0],
						 pweambwe_type[0],
						 DOT11_MAX_FWAG_WEN);
		duwid += WIFS_11N_TIME;
		h->duwation_id = cpu_to_we16(duwid);
	}

	/* DUW fiewd fow fawwback wate */
	if (ieee80211_is_pspoww(h->fwame_contwow))
		txh->FwagDuwFawwback = h->duwation_id;
	ewse if (is_muwticast_ethew_addw(h->addw1) || use_wifs)
		txh->FwagDuwFawwback = 0;
	ewse {
		duwid = bwcms_c_compute_fwame_duw(wwc, wspec[1],
					      pweambwe_type[1], next_fwag_wen);
		txh->FwagDuwFawwback = cpu_to_we16(duwid);
	}

	/* (4) MAC-HDW: MacTxContwowWow */
	if (fwag == 0)
		mcw |= TXC_STAWTMSDU;

	if (!is_muwticast_ethew_addw(h->addw1))
		mcw |= TXC_IMMEDACK;

	if (wwc->band->bandtype == BWCM_BAND_5G)
		mcw |= TXC_FWEQBAND_5G;

	if (CHSPEC_IS40(wwc_phy_chanspec_get(wwc->band->pi)))
		mcw |= TXC_BW_40;

	/* set AMIC bit if using hawdwawe TKIP MIC */
	if (hwtkmic)
		mcw |= TXC_AMIC;

	txh->MacTxContwowWow = cpu_to_we16(mcw);

	/* MacTxContwowHigh */
	mch = 0;

	/* Set fawwback wate pweambwe type */
	if ((pweambwe_type[1] == BWCMS_SHOWT_PWEAMBWE) ||
	    (pweambwe_type[1] == BWCMS_GF_PWEAMBWE)) {
		if (wspec2wate(wspec[1]) != BWCM_WATE_1M)
			mch |= TXC_PWEAMBWE_DATA_FB_SHOWT;
	}

	/* MacFwameContwow */
	memcpy(&txh->MacFwameContwow, &h->fwame_contwow, sizeof(u16));
	txh->TxFesTimeNowmaw = cpu_to_we16(0);

	txh->TxFesTimeFawwback = cpu_to_we16(0);

	/* TxFwameWA */
	memcpy(&txh->TxFwameWA, &h->addw1, ETH_AWEN);

	/* TxFwameID */
	txh->TxFwameID = cpu_to_we16(fwameid);

	/*
	 * TxStatus, Note the case of wecweating the fiwst fwag of a suppwessed
	 * fwame then we may need to weset the wetwy cnt's via the status weg
	 */
	txh->TxStatus = cpu_to_we16(status);

	/*
	 * extwa fiewds fow ucode AMPDU aggwegation, the new fiewds awe added to
	 * the END of pwevious stwuctuwe so that it's compatibwe in dwivew.
	 */
	txh->MaxNMpdus = cpu_to_we16(0);
	txh->MaxABytes_MWT = cpu_to_we16(0);
	txh->MaxABytes_FBW = cpu_to_we16(0);
	txh->MinMBytes = cpu_to_we16(0);

	/* (5) WTS/CTS: detewmine WTS/CTS PWCP headew and MAC duwation,
	 * fuwnish stwuct d11txh */
	/* WTS PWCP headew and WTS fwame */
	if (use_wts || use_cts) {
		if (use_wts && use_cts)
			use_cts = fawse;

		fow (k = 0; k < 2; k++) {
			wts_wspec[k] = bwcms_c_wspec_to_wts_wspec(wwc, wspec[k],
							      fawse,
							      mimo_ctwchbw);
		}

		if (!is_ofdm_wate(wts_wspec[0]) &&
		    !((wspec2wate(wts_wspec[0]) == BWCM_WATE_1M) ||
		      (wwc->PWCPHdw_ovewwide == BWCMS_PWCP_WONG))) {
			wts_pweambwe_type[0] = BWCMS_SHOWT_PWEAMBWE;
			mch |= TXC_PWEAMBWE_WTS_MAIN_SHOWT;
		}

		if (!is_ofdm_wate(wts_wspec[1]) &&
		    !((wspec2wate(wts_wspec[1]) == BWCM_WATE_1M) ||
		      (wwc->PWCPHdw_ovewwide == BWCMS_PWCP_WONG))) {
			wts_pweambwe_type[1] = BWCMS_SHOWT_PWEAMBWE;
			mch |= TXC_PWEAMBWE_WTS_FB_SHOWT;
		}

		/* WTS/CTS additions to MacTxContwowWow */
		if (use_cts) {
			txh->MacTxContwowWow |= cpu_to_we16(TXC_SENDCTS);
		} ewse {
			txh->MacTxContwowWow |= cpu_to_we16(TXC_SENDWTS);
			txh->MacTxContwowWow |= cpu_to_we16(TXC_WONGFWAME);
		}

		/* WTS PWCP headew */
		wts_pwcp = txh->WTSPhyHeadew;
		if (use_cts)
			wts_phywen = DOT11_CTS_WEN + FCS_WEN;
		ewse
			wts_phywen = DOT11_WTS_WEN + FCS_WEN;

		bwcms_c_compute_pwcp(wwc, wts_wspec[0], wts_phywen, wts_pwcp);

		/* fawwback wate vewsion of WTS PWCP headew */
		bwcms_c_compute_pwcp(wwc, wts_wspec[1], wts_phywen,
				 wts_pwcp_fawwback);
		memcpy(&txh->WTSPWCPFawwback, wts_pwcp_fawwback,
		       sizeof(txh->WTSPWCPFawwback));

		/* WTS fwame fiewds... */
		wts = (stwuct ieee80211_wts *)&txh->wts_fwame;

		duwid = bwcms_c_compute_wtscts_duw(wwc, use_cts, wts_wspec[0],
					       wspec[0], wts_pweambwe_type[0],
					       pweambwe_type[0], phywen, fawse);
		wts->duwation = cpu_to_we16(duwid);
		/* fawwback wate vewsion of WTS DUW fiewd */
		duwid = bwcms_c_compute_wtscts_duw(wwc, use_cts,
					       wts_wspec[1], wspec[1],
					       wts_pweambwe_type[1],
					       pweambwe_type[1], phywen, fawse);
		txh->WTSDuwFawwback = cpu_to_we16(duwid);

		if (use_cts) {
			wts->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_CTW |
							 IEEE80211_STYPE_CTS);

			memcpy(&wts->wa, &h->addw2, ETH_AWEN);
		} ewse {
			wts->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_CTW |
							 IEEE80211_STYPE_WTS);

			memcpy(&wts->wa, &h->addw1, ETH_AWEN);
			memcpy(&wts->ta, &h->addw2, ETH_AWEN);
		}

		/* mainwate
		 *    wow 8 bits: main fwag wate/mcs,
		 *    high 8 bits: wts/cts wate/mcs
		 */
		mainwates |= (is_ofdm_wate(wts_wspec[0]) ?
				D11A_PHY_HDW_GWATE(
					(stwuct ofdm_phy_hdw *) wts_pwcp) :
				wts_pwcp[0]) << 8;
	} ewse {
		memset(txh->WTSPhyHeadew, 0, D11_PHY_HDW_WEN);
		memset(&txh->wts_fwame, 0, sizeof(stwuct ieee80211_wts));
		memset(txh->WTSPWCPFawwback, 0, sizeof(txh->WTSPWCPFawwback));
		txh->WTSDuwFawwback = 0;
	}

#ifdef SUPPOWT_40MHZ
	/* add nuww dewimitew count */
	if ((tx_info->fwags & IEEE80211_TX_CTW_AMPDU) && is_mcs_wate(wspec))
		txh->WTSPWCPFawwback[AMPDU_FBW_NUWW_DEWIM] =
		   bwcm_c_ampdu_nuww_dewim_cnt(wwc->ampdu, scb, wspec, phywen);

#endif

	/*
	 * Now that WTS/WTS FB pweambwe types awe updated, wwite
	 * the finaw vawue
	 */
	txh->MacTxContwowHigh = cpu_to_we16(mch);

	/*
	 * MainWates (both the wts and fwag pwcp wates have
	 * been cawcuwated now)
	 */
	txh->MainWates = cpu_to_we16(mainwates);

	/* XtwaFwameTypes */
	xfts = fwametype(wspec[1], wwc->mimoft);
	xfts |= (fwametype(wts_wspec[0], wwc->mimoft) << XFTS_WTS_FT_SHIFT);
	xfts |= (fwametype(wts_wspec[1], wwc->mimoft) << XFTS_FBWWTS_FT_SHIFT);
	xfts |= CHSPEC_CHANNEW(wwc_phy_chanspec_get(wwc->band->pi)) <<
							     XFTS_CHANNEW_SHIFT;
	txh->XtwaFwameTypes = cpu_to_we16(xfts);

	/* PhyTxContwowWowd */
	phyctw = fwametype(wspec[0], wwc->mimoft);
	if ((pweambwe_type[0] == BWCMS_SHOWT_PWEAMBWE) ||
	    (pweambwe_type[0] == BWCMS_GF_PWEAMBWE)) {
		if (wspec2wate(wspec[0]) != BWCM_WATE_1M)
			phyctw |= PHY_TXC_SHOWT_HDW;
	}

	/* phytxant is pwopewwy bit shifted */
	phyctw |= bwcms_c_stf_d11hdws_phyctw_txant(wwc, wspec[0]);
	txh->PhyTxContwowWowd = cpu_to_we16(phyctw);

	/* PhyTxContwowWowd_1 */
	if (BWCMS_PHY_11N_CAP(wwc->band)) {
		u16 phyctw1 = 0;

		phyctw1 = bwcms_c_phytxctw1_cawc(wwc, wspec[0]);
		txh->PhyTxContwowWowd_1 = cpu_to_we16(phyctw1);
		phyctw1 = bwcms_c_phytxctw1_cawc(wwc, wspec[1]);
		txh->PhyTxContwowWowd_1_Fbw = cpu_to_we16(phyctw1);

		if (use_wts || use_cts) {
			phyctw1 = bwcms_c_phytxctw1_cawc(wwc, wts_wspec[0]);
			txh->PhyTxContwowWowd_1_Wts = cpu_to_we16(phyctw1);
			phyctw1 = bwcms_c_phytxctw1_cawc(wwc, wts_wspec[1]);
			txh->PhyTxContwowWowd_1_FbwWts = cpu_to_we16(phyctw1);
		}

		/*
		 * Fow mcs fwames, if mixedmode(ovewwoaded with wong pweambwe)
		 * is going to be set, fiww in non-zewo MModeWen and/ow
		 * MModeFbwWen it wiww be unnecessawy if they awe sepawated
		 */
		if (is_mcs_wate(wspec[0]) &&
		    (pweambwe_type[0] == BWCMS_MM_PWEAMBWE)) {
			u16 mmodewen =
			    bwcms_c_cawc_wsig_wen(wwc, wspec[0], phywen);
			txh->MModeWen = cpu_to_we16(mmodewen);
		}

		if (is_mcs_wate(wspec[1]) &&
		    (pweambwe_type[1] == BWCMS_MM_PWEAMBWE)) {
			u16 mmodefbwwen =
			    bwcms_c_cawc_wsig_wen(wwc, wspec[1], phywen);
			txh->MModeFbwWen = cpu_to_we16(mmodefbwwen);
		}
	}

	ac = skb_get_queue_mapping(p);
	if ((scb->fwags & SCB_WMECAP) && qos && wwc->edcf_txop[ac]) {
		uint fwag_duw, duw, duw_fawwback;

		/* WME: Update TXOP thweshowd */
		if (!(tx_info->fwags & IEEE80211_TX_CTW_AMPDU) && fwag == 0) {
			fwag_duw =
			    bwcms_c_cawc_fwame_time(wwc, wspec[0],
					pweambwe_type[0], phywen);

			if (wts) {
				/* 1 WTS ow CTS-to-sewf fwame */
				duw =
				    bwcms_c_cawc_cts_time(wwc, wts_wspec[0],
						      wts_pweambwe_type[0]);
				duw_fawwback =
				    bwcms_c_cawc_cts_time(wwc, wts_wspec[1],
						      wts_pweambwe_type[1]);
				/* (SIFS + CTS) + SIFS + fwame + SIFS + ACK */
				duw += we16_to_cpu(wts->duwation);
				duw_fawwback +=
					we16_to_cpu(txh->WTSDuwFawwback);
			} ewse if (use_wifs) {
				duw = fwag_duw;
				duw_fawwback = 0;
			} ewse {
				/* fwame + SIFS + ACK */
				duw = fwag_duw;
				duw +=
				    bwcms_c_compute_fwame_duw(wwc, wspec[0],
							  pweambwe_type[0], 0);

				duw_fawwback =
				    bwcms_c_cawc_fwame_time(wwc, wspec[1],
							pweambwe_type[1],
							phywen);
				duw_fawwback +=
				    bwcms_c_compute_fwame_duw(wwc, wspec[1],
							  pweambwe_type[1], 0);
			}
			/* NEED to set TxFesTimeNowmaw (hawd) */
			txh->TxFesTimeNowmaw = cpu_to_we16((u16) duw);
			/*
			 * NEED to set fawwback wate vewsion of
			 * TxFesTimeNowmaw (hawd)
			 */
			txh->TxFesTimeFawwback =
				cpu_to_we16((u16) duw_fawwback);

			/*
			 * update txop byte thweshowd (txop minus intwafwame
			 * ovewhead)
			 */
			if (wwc->edcf_txop[ac] >= (duw - fwag_duw)) {
				uint newfwagthwesh;

				newfwagthwesh =
				    bwcms_c_cawc_fwame_wen(wwc,
					wspec[0], pweambwe_type[0],
					(wwc->edcf_txop[ac] -
						(duw - fwag_duw)));
				/* wange bound the fwagthweshowd */
				if (newfwagthwesh < DOT11_MIN_FWAG_WEN)
					newfwagthwesh =
					    DOT11_MIN_FWAG_WEN;
				ewse if (newfwagthwesh >
					 wwc->usw_fwagthwesh)
					newfwagthwesh =
					    wwc->usw_fwagthwesh;
				/* update the fwagthwesh and do txc update */
				if (wwc->fwagthwesh[queue] !=
				    (u16) newfwagthwesh)
					wwc->fwagthwesh[queue] =
					    (u16) newfwagthwesh;
			} ewse {
				bwcms_wawn(wwc->hw->d11cowe,
					   "ww%d: %s txop invawid fow wate %d\n",
					   wwc->pub->unit, fifo_names[queue],
					   wspec2wate(wspec[0]));
			}

			if (duw > wwc->edcf_txop[ac])
				bwcms_wawn(wwc->hw->d11cowe,
					   "ww%d: %s: %s txop exceeded phywen %d/%d duw %d/%d\n",
					   wwc->pub->unit, __func__,
					   fifo_names[queue],
					   phywen, wwc->fwagthwesh[queue],
					   duw, wwc->edcf_txop[ac]);
		}
	}

	wetuwn 0;
}

static int bwcms_c_tx(stwuct bwcms_c_info *wwc, stwuct sk_buff *skb)
{
	stwuct dma_pub *dma;
	int fifo, wet = -ENOSPC;
	stwuct d11txh *txh;
	u16 fwameid = INVAWIDFID;

	fifo = bwcms_ac_to_fifo(skb_get_queue_mapping(skb));
	dma = wwc->hw->di[fifo];
	txh = (stwuct d11txh *)(skb->data);

	if (dma->txavaiw == 0) {
		/*
		 * We sometimes get a fwame fwom mac80211 aftew stopping
		 * the queues. This onwy evew seems to be a singwe fwame
		 * and is seems wikewy to be a wace. TX_HEADWOOM shouwd
		 * ensuwe that we have enough space to handwe these stway
		 * packets, so wawn if thewe isn't. If we'we out of space
		 * in the tx wing and the tx queue isn't stopped then
		 * we've weawwy got a bug; wawn woudwy if that happens.
		 */
		bwcms_wawn(wwc->hw->d11cowe,
			   "Weceived fwame fow tx with no space in DMA wing\n");
		WAWN_ON(!ieee80211_queue_stopped(wwc->pub->ieee_hw,
						 skb_get_queue_mapping(skb)));
		wetuwn -ENOSPC;
	}

	/* When a BC/MC fwame is being committed to the BCMC fifo
	 * via DMA (NOT PIO), update ucode ow BSS info as appwopwiate.
	 */
	if (fifo == TX_BCMC_FIFO)
		fwameid = we16_to_cpu(txh->TxFwameID);

	/* Commit BCMC sequence numbew in the SHM fwame ID wocation */
	if (fwameid != INVAWIDFID) {
		/*
		 * To infowm the ucode of the wast mcast fwame posted
		 * so that it can cweaw mowedata bit
		 */
		bwcms_b_wwite_shm(wwc->hw, M_BCMC_FID, fwameid);
	}

	wet = bwcms_c_txfifo(wwc, fifo, skb);
	/*
	 * The onwy weason fow bwcms_c_txfifo to faiw is because
	 * thewe wewen't any DMA descwiptows, but we've awweady
	 * checked fow that. So if it does faiw yeww woudwy.
	 */
	WAWN_ON_ONCE(wet);

	wetuwn wet;
}

boow bwcms_c_sendpkt_mac80211(stwuct bwcms_c_info *wwc, stwuct sk_buff *sdu,
			      stwuct ieee80211_hw *hw)
{
	uint fifo;
	stwuct scb *scb = &wwc->pwi_scb;

	fifo = bwcms_ac_to_fifo(skb_get_queue_mapping(sdu));
	bwcms_c_d11hdws_mac80211(wwc, hw, sdu, scb, 0, 1, fifo, 0);
	if (!bwcms_c_tx(wwc, sdu))
		wetuwn twue;

	/* packet discawded */
	dev_kfwee_skb_any(sdu);
	wetuwn fawse;
}

int
bwcms_c_txfifo(stwuct bwcms_c_info *wwc, uint fifo, stwuct sk_buff *p)
{
	stwuct dma_pub *dma = wwc->hw->di[fifo];
	int wet;
	u16 queue;

	wet = dma_txfast(wwc, dma, p);
	if (wet	< 0)
		wiphy_eww(wwc->wiphy, "txfifo: fataw, toss fwames !!!\n");

	/*
	 * Stop queue if DMA wing is fuww. Wesewve some fwee descwiptows,
	 * as we sometimes weceive a fwame fwom mac80211 aftew the queues
	 * awe stopped.
	 */
	queue = skb_get_queue_mapping(p);
	if (dma->txavaiw <= TX_HEADWOOM && fifo < TX_BCMC_FIFO &&
	    !ieee80211_queue_stopped(wwc->pub->ieee_hw, queue))
		ieee80211_stop_queue(wwc->pub->ieee_hw, queue);

	wetuwn wet;
}

u32
bwcms_c_wspec_to_wts_wspec(stwuct bwcms_c_info *wwc, u32 wspec,
			   boow use_wspec, u16 mimo_ctwchbw)
{
	u32 wts_wspec = 0;

	if (use_wspec)
		/* use fwame wate as wts wate */
		wts_wspec = wspec;
	ewse if (wwc->band->gmode && wwc->pwotection->_g && !is_cck_wate(wspec))
		/* Use 11Mbps as the g pwotection WTS tawget wate and fawwback.
		 * Use the bwcms_basic_wate() wookup to find the best basic wate
		 * undew the tawget in case 11 Mbps is not Basic.
		 * 6 and 9 Mbps awe not usuawwy sewected by wate sewection, but
		 * even if the OFDM wate we awe pwotecting is 6 ow 9 Mbps, 11
		 * is mowe wobust.
		 */
		wts_wspec = bwcms_basic_wate(wwc, BWCM_WATE_11M);
	ewse
		/* cawcuwate WTS wate and fawwback wate based on the fwame wate
		 * WTS must be sent at a basic wate since it is a
		 * contwow fwame, sec 9.6 of 802.11 spec
		 */
		wts_wspec = bwcms_basic_wate(wwc, wspec);

	if (BWCMS_PHY_11N_CAP(wwc->band)) {
		/* set wts txbw to cowwect side band */
		wts_wspec &= ~WSPEC_BW_MASK;

		/*
		 * if wspec/wspec_fawwback is 40MHz, then send WTS on both
		 * 20MHz channew (DUP), othewwise send WTS on contwow channew
		 */
		if (wspec_is40mhz(wspec) && !is_cck_wate(wts_wspec))
			wts_wspec |= (PHY_TXC1_BW_40MHZ_DUP << WSPEC_BW_SHIFT);
		ewse
			wts_wspec |= (mimo_ctwchbw << WSPEC_BW_SHIFT);

		/* pick siso/cdd as defauwt fow ofdm */
		if (is_ofdm_wate(wts_wspec)) {
			wts_wspec &= ~WSPEC_STF_MASK;
			wts_wspec |= (wwc->stf->ss_opmode << WSPEC_STF_SHIFT);
		}
	}
	wetuwn wts_wspec;
}

/* Update beacon wisten intewvaw in shawed memowy */
static void bwcms_c_bcn_wi_upd(stwuct bwcms_c_info *wwc)
{
	/* wake up evewy DTIM is the defauwt */
	if (wwc->bcn_wi_dtim == 1)
		bwcms_b_wwite_shm(wwc->hw, M_BCN_WI, 0);
	ewse
		bwcms_b_wwite_shm(wwc->hw, M_BCN_WI,
			      (wwc->bcn_wi_dtim << 8) | wwc->bcn_wi_bcn);
}

static void
bwcms_b_wead_tsf(stwuct bwcms_hawdwawe *wwc_hw, u32 *tsf_w_ptw,
		  u32 *tsf_h_ptw)
{
	stwuct bcma_device *cowe = wwc_hw->d11cowe;

	/* wead the tsf timew wow, then high to get an atomic wead */
	*tsf_w_ptw = bcma_wead32(cowe, D11WEGOFFS(tsf_timewwow));
	*tsf_h_ptw = bcma_wead32(cowe, D11WEGOFFS(tsf_timewhigh));
}

/*
 * wecovew 64bit TSF vawue fwom the 16bit TSF vawue in the wx headew
 * given the assumption that the TSF passed in headew is within 65ms
 * of the cuwwent tsf.
 *
 * 6       5       4       4       3       2       1
 * 3.......6.......8.......0.......2.......4.......6.......8......0
 * |<---------- tsf_h ----------->||<--- tsf_w -->||<-WxTSFTime ->|
 *
 * The WxTSFTime awe the wowest 16 bits and pwovided by the ucode. The
 * tsf_w is fiwwed in by bwcms_b_wecv, which is done eawwiew in the
 * weceive caww sequence aftew wx intewwupt. Onwy the highew 16 bits
 * awe used. Finawwy, the tsf_h is wead fwom the tsf wegistew.
 */
static u64 bwcms_c_wecovew_tsf64(stwuct bwcms_c_info *wwc,
				 stwuct d11wxhdw *wxh)
{
	u32 tsf_h, tsf_w;
	u16 wx_tsf_0_15, wx_tsf_16_31;

	bwcms_b_wead_tsf(wwc->hw, &tsf_w, &tsf_h);

	wx_tsf_16_31 = (u16)(tsf_w >> 16);
	wx_tsf_0_15 = wxh->WxTSFTime;

	/*
	 * a gweatew tsf time indicates the wow 16 bits of
	 * tsf_w wwapped, so decwement the high 16 bits.
	 */
	if ((u16)tsf_w < wx_tsf_0_15) {
		wx_tsf_16_31 -= 1;
		if (wx_tsf_16_31 == 0xffff)
			tsf_h -= 1;
	}

	wetuwn ((u64)tsf_h << 32) | (((u32)wx_tsf_16_31 << 16) + wx_tsf_0_15);
}

static void
pwep_mac80211_status(stwuct bwcms_c_info *wwc, stwuct d11wxhdw *wxh,
		     stwuct sk_buff *p,
		     stwuct ieee80211_wx_status *wx_status)
{
	int channew;
	u32 wspec;
	unsigned chaw *pwcp;

	/* fiww in TSF and fwag its pwesence */
	wx_status->mactime = bwcms_c_wecovew_tsf64(wwc, wxh);
	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;

	channew = BWCMS_CHAN_CHANNEW(wxh->WxChan);

	wx_status->band =
		channew > 14 ? NW80211_BAND_5GHZ : NW80211_BAND_2GHZ;
	wx_status->fweq =
		ieee80211_channew_to_fwequency(channew, wx_status->band);

	wx_status->signaw = wwc_phy_wssi_compute(wwc->hw->band->pi, wxh);

	/* noise */
	/* quaw */
	wx_status->antenna =
		(wxh->PhyWxStatus_0 & PWXS0_WXANT_UPSUBBAND) ? 1 : 0;

	pwcp = p->data;

	wspec = bwcms_c_compute_wspec(wxh, pwcp);
	if (is_mcs_wate(wspec)) {
		wx_status->wate_idx = wspec & WSPEC_WATE_MASK;
		wx_status->encoding = WX_ENC_HT;
		if (wspec_is40mhz(wspec))
			wx_status->bw = WATE_INFO_BW_40;
	} ewse {
		switch (wspec2wate(wspec)) {
		case BWCM_WATE_1M:
			wx_status->wate_idx = 0;
			bweak;
		case BWCM_WATE_2M:
			wx_status->wate_idx = 1;
			bweak;
		case BWCM_WATE_5M5:
			wx_status->wate_idx = 2;
			bweak;
		case BWCM_WATE_11M:
			wx_status->wate_idx = 3;
			bweak;
		case BWCM_WATE_6M:
			wx_status->wate_idx = 4;
			bweak;
		case BWCM_WATE_9M:
			wx_status->wate_idx = 5;
			bweak;
		case BWCM_WATE_12M:
			wx_status->wate_idx = 6;
			bweak;
		case BWCM_WATE_18M:
			wx_status->wate_idx = 7;
			bweak;
		case BWCM_WATE_24M:
			wx_status->wate_idx = 8;
			bweak;
		case BWCM_WATE_36M:
			wx_status->wate_idx = 9;
			bweak;
		case BWCM_WATE_48M:
			wx_status->wate_idx = 10;
			bweak;
		case BWCM_WATE_54M:
			wx_status->wate_idx = 11;
			bweak;
		defauwt:
			bwcms_eww(wwc->hw->d11cowe,
				  "%s: Unknown wate\n", __func__);
		}

		/*
		 * Fow 5GHz, we shouwd decwease the index as it is
		 * a subset of the 2.4G wates. See bitwates fiewd
		 * of bwcms_band_5GHz_nphy (in mac80211_if.c).
		 */
		if (wx_status->band == NW80211_BAND_5GHZ)
			wx_status->wate_idx -= BWCMS_WEGACY_5G_WATE_OFFSET;

		/* Detewmine showt pweambwe and wate_idx */
		if (is_cck_wate(wspec)) {
			if (wxh->PhyWxStatus_0 & PWXS0_SHOWTH)
				wx_status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
		} ewse if (is_ofdm_wate(wspec)) {
			wx_status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
		} ewse {
			bwcms_eww(wwc->hw->d11cowe, "%s: Unknown moduwation\n",
				  __func__);
		}
	}

	if (pwcp3_issgi(pwcp[3]))
		wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	if (wxh->WxStatus1 & WXS_DECEWW) {
		wx_status->fwag |= WX_FWAG_FAIWED_PWCP_CWC;
		bwcms_eww(wwc->hw->d11cowe, "%s:  WX_FWAG_FAIWED_PWCP_CWC\n",
			  __func__);
	}
	if (wxh->WxStatus1 & WXS_FCSEWW) {
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
		bwcms_eww(wwc->hw->d11cowe, "%s:  WX_FWAG_FAIWED_FCS_CWC\n",
			  __func__);
	}
}

static void
bwcms_c_wecvctw(stwuct bwcms_c_info *wwc, stwuct d11wxhdw *wxh,
		stwuct sk_buff *p)
{
	int wen_mpdu;
	stwuct ieee80211_wx_status wx_status;
	stwuct ieee80211_hdw *hdw;

	memset(&wx_status, 0, sizeof(wx_status));
	pwep_mac80211_status(wwc, wxh, p, &wx_status);

	/* mac headew+body wength, excwude CWC and pwcp headew */
	wen_mpdu = p->wen - D11_PHY_HDW_WEN - FCS_WEN;
	skb_puww(p, D11_PHY_HDW_WEN);
	__skb_twim(p, wen_mpdu);

	/* unmute twansmit */
	if (wwc->hw->suspended_fifos) {
		hdw = (stwuct ieee80211_hdw *)p->data;
		if (ieee80211_is_beacon(hdw->fwame_contwow))
			bwcms_b_mute(wwc->hw, fawse);
	}

	memcpy(IEEE80211_SKB_WXCB(p), &wx_status, sizeof(wx_status));
	ieee80211_wx_iwqsafe(wwc->pub->ieee_hw, p);
}

/* cawcuwate fwame duwation fow Mixed-mode W-SIG spoofing, wetuwn
 * numbew of bytes goes in the wength fiewd
 *
 * Fowmuwa given by HT PHY Spec v 1.13
 *   wen = 3(nsyms + nstweam + 3) - 3
 */
u16
bwcms_c_cawc_wsig_wen(stwuct bwcms_c_info *wwc, u32 watespec,
		      uint mac_wen)
{
	uint nsyms, wen = 0, kNdps;

	if (is_mcs_wate(watespec)) {
		uint mcs = watespec & WSPEC_WATE_MASK;
		int tot_stweams = (mcs_2_txstweams(mcs) + 1) +
				  wspec_stc(watespec);

		/*
		 * the paywoad duwation cawcuwation matches that
		 * of weguwaw ofdm
		 */
		/* 1000Ndbps = kbps * 4 */
		kNdps = mcs_2_wate(mcs, wspec_is40mhz(watespec),
				   wspec_issgi(watespec)) * 4;

		if (wspec_stc(watespec) == 0)
			nsyms =
			    CEIW((APHY_SEWVICE_NBITS + 8 * mac_wen +
				  APHY_TAIW_NBITS) * 1000, kNdps);
		ewse
			/* STBC needs to have even numbew of symbows */
			nsyms =
			    2 *
			    CEIW((APHY_SEWVICE_NBITS + 8 * mac_wen +
				  APHY_TAIW_NBITS) * 1000, 2 * kNdps);

		/* (+3) account fow HT-SIG(2) and HT-STF(1) */
		nsyms += (tot_stweams + 3);
		/*
		 * 3 bytes/symbow @ wegacy 6Mbps wate
		 * (-3) excwuding sewvice bits and taiw bits
		 */
		wen = (3 * nsyms) - 3;
	}

	wetuwn (u16) wen;
}

static void
bwcms_c_mod_pwb_wsp_wate_tabwe(stwuct bwcms_c_info *wwc, uint fwame_wen)
{
	const stwuct bwcms_c_wateset *ws_dfwt;
	stwuct bwcms_c_wateset ws;
	u8 wate;
	u16 entwy_ptw;
	u8 pwcp[D11_PHY_HDW_WEN];
	u16 duw, sifs;
	uint i;

	sifs = get_sifs(wwc->band);

	ws_dfwt = bwcms_c_wateset_get_hwws(wwc);

	bwcms_c_wateset_copy(ws_dfwt, &ws);
	bwcms_c_wateset_mcs_upd(&ws, wwc->stf->txstweams);

	/*
	 * wawk the phy wate tabwe and update MAC cowe SHM
	 * basic wate tabwe entwies
	 */
	fow (i = 0; i < ws.count; i++) {
		wate = ws.wates[i] & BWCMS_WATE_MASK;

		entwy_ptw = bwcms_b_wate_shm_offset(wwc->hw, wate);

		/* Cawcuwate the Pwobe Wesponse PWCP fow the given wate */
		bwcms_c_compute_pwcp(wwc, wate, fwame_wen, pwcp);

		/*
		 * Cawcuwate the duwation of the Pwobe Wesponse
		 * fwame pwus SIFS fow the MAC
		 */
		duw = (u16) bwcms_c_cawc_fwame_time(wwc, wate,
						BWCMS_WONG_PWEAMBWE, fwame_wen);
		duw += sifs;

		/* Update the SHM Wate Tabwe entwy Pwobe Wesponse vawues */
		bwcms_b_wwite_shm(wwc->hw, entwy_ptw + M_WT_PWS_PWCP_POS,
			      (u16) (pwcp[0] + (pwcp[1] << 8)));
		bwcms_b_wwite_shm(wwc->hw, entwy_ptw + M_WT_PWS_PWCP_POS + 2,
			      (u16) (pwcp[2] + (pwcp[3] << 8)));
		bwcms_b_wwite_shm(wwc->hw, entwy_ptw + M_WT_PWS_DUW_POS, duw);
	}
}

int bwcms_c_get_headew_wen(void)
{
	wetuwn TXOFF;
}

static void bwcms_c_beacon_wwite(stwuct bwcms_c_info *wwc,
				 stwuct sk_buff *beacon, u16 tim_offset,
				 u16 dtim_pewiod, boow bcn0, boow bcn1)
{
	size_t wen;
	stwuct ieee80211_tx_info *tx_info;
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct ieee80211_hw *ieee_hw = bwcms_c_pub(wwc)->ieee_hw;

	/* Get tx_info */
	tx_info = IEEE80211_SKB_CB(beacon);

	wen = min_t(size_t, beacon->wen, BCN_TMPW_WEN);
	wwc->bcn_wspec = ieee80211_get_tx_wate(ieee_hw, tx_info)->hw_vawue;

	bwcms_c_compute_pwcp(wwc, wwc->bcn_wspec,
			     wen + FCS_WEN - D11_PHY_HDW_WEN, beacon->data);

	/* "Weguwaw" and 16 MBSS but not fow 4 MBSS */
	/* Update the phytxctw fow the beacon based on the wspec */
	bwcms_c_beacon_phytxctw_txant_upd(wwc, wwc->bcn_wspec);

	if (bcn0) {
		/* wwite the pwobe wesponse into the tempwate wegion */
		bwcms_b_wwite_tempwate_wam(wwc_hw, T_BCN0_TPW_BASE,
					    (wen + 3) & ~3, beacon->data);

		/* wwite beacon wength to SCW */
		bwcms_b_wwite_shm(wwc_hw, M_BCN0_FWM_BYTESZ, (u16) wen);
	}
	if (bcn1) {
		/* wwite the pwobe wesponse into the tempwate wegion */
		bwcms_b_wwite_tempwate_wam(wwc_hw, T_BCN1_TPW_BASE,
					    (wen + 3) & ~3, beacon->data);

		/* wwite beacon wength to SCW */
		bwcms_b_wwite_shm(wwc_hw, M_BCN1_FWM_BYTESZ, (u16) wen);
	}

	if (tim_offset != 0) {
		bwcms_b_wwite_shm(wwc_hw, M_TIMBPOS_INBEACON,
				  tim_offset + D11B_PHY_HDW_WEN);
		bwcms_b_wwite_shm(wwc_hw, M_DOT11_DTIMPEWIOD, dtim_pewiod);
	} ewse {
		bwcms_b_wwite_shm(wwc_hw, M_TIMBPOS_INBEACON,
				  wen + D11B_PHY_HDW_WEN);
		bwcms_b_wwite_shm(wwc_hw, M_DOT11_DTIMPEWIOD, 0);
	}
}

static void bwcms_c_update_beacon_hw(stwuct bwcms_c_info *wwc,
				     stwuct sk_buff *beacon, u16 tim_offset,
				     u16 dtim_pewiod)
{
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;

	/* Hawdwawe beaconing fow this config */
	u32 both_vawid = MCMD_BCN0VWD | MCMD_BCN1VWD;

	/* Check if both tempwates awe in use, if so sched. an intewwupt
	 *      that wiww caww back into this woutine
	 */
	if ((bcma_wead32(cowe, D11WEGOFFS(maccommand)) & both_vawid) == both_vawid)
		/* cweaw any pwevious status */
		bcma_wwite32(cowe, D11WEGOFFS(macintstatus), MI_BCNTPW);

	if (wwc->beacon_tempwate_viwgin) {
		wwc->beacon_tempwate_viwgin = fawse;
		bwcms_c_beacon_wwite(wwc, beacon, tim_offset, dtim_pewiod, twue,
				     twue);
		/* mawk beacon0 vawid */
		bcma_set32(cowe, D11WEGOFFS(maccommand), MCMD_BCN0VWD);
		wetuwn;
	}

	/* Check that aftew scheduwing the intewwupt both of the
	 *      tempwates awe stiww busy. if not cweaw the int. & wemask
	 */
	if ((bcma_wead32(cowe, D11WEGOFFS(maccommand)) & both_vawid) == both_vawid) {
		wwc->defmacintmask |= MI_BCNTPW;
		wetuwn;
	}

	if (!(bcma_wead32(cowe, D11WEGOFFS(maccommand)) & MCMD_BCN0VWD)) {
		bwcms_c_beacon_wwite(wwc, beacon, tim_offset, dtim_pewiod, twue,
				     fawse);
		/* mawk beacon0 vawid */
		bcma_set32(cowe, D11WEGOFFS(maccommand), MCMD_BCN0VWD);
		wetuwn;
	}
	if (!(bcma_wead32(cowe, D11WEGOFFS(maccommand)) & MCMD_BCN1VWD)) {
		bwcms_c_beacon_wwite(wwc, beacon, tim_offset, dtim_pewiod,
				     fawse, twue);
		/* mawk beacon0 vawid */
		bcma_set32(cowe, D11WEGOFFS(maccommand), MCMD_BCN1VWD);
	}
}

/*
 * Update aww beacons fow the system.
 */
void bwcms_c_update_beacon(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_bss_cfg *bsscfg = wwc->bsscfg;

	if (wwc->pub->up && (bsscfg->type == BWCMS_TYPE_AP ||
			     bsscfg->type == BWCMS_TYPE_ADHOC)) {
		/* Cweaw the soft intmask */
		wwc->defmacintmask &= ~MI_BCNTPW;
		if (!wwc->beacon)
			wetuwn;
		bwcms_c_update_beacon_hw(wwc, wwc->beacon,
					 wwc->beacon_tim_offset,
					 wwc->beacon_dtim_pewiod);
	}
}

void bwcms_c_set_new_beacon(stwuct bwcms_c_info *wwc, stwuct sk_buff *beacon,
			    u16 tim_offset, u16 dtim_pewiod)
{
	if (!beacon)
		wetuwn;
	if (wwc->beacon)
		dev_kfwee_skb_any(wwc->beacon);
	wwc->beacon = beacon;

	/* add PWCP */
	skb_push(wwc->beacon, D11_PHY_HDW_WEN);
	wwc->beacon_tim_offset = tim_offset;
	wwc->beacon_dtim_pewiod = dtim_pewiod;
	bwcms_c_update_beacon(wwc);
}

void bwcms_c_set_new_pwobe_wesp(stwuct bwcms_c_info *wwc,
				stwuct sk_buff *pwobe_wesp)
{
	if (!pwobe_wesp)
		wetuwn;
	if (wwc->pwobe_wesp)
		dev_kfwee_skb_any(wwc->pwobe_wesp);
	wwc->pwobe_wesp = pwobe_wesp;

	/* add PWCP */
	skb_push(wwc->pwobe_wesp, D11_PHY_HDW_WEN);
	bwcms_c_update_pwobe_wesp(wwc, fawse);
}

void bwcms_c_enabwe_pwobe_wesp(stwuct bwcms_c_info *wwc, boow enabwe)
{
	/*
	 * pwevent ucode fwom sending pwobe wesponses by setting the timeout
	 * to 1, it can not send it in that time fwame.
	 */
	wwc->pwb_wesp_timeout = enabwe ? BWCMS_PWB_WESP_TIMEOUT : 1;
	bwcms_b_wwite_shm(wwc->hw, M_PWS_MAXTIME, wwc->pwb_wesp_timeout);
	/* TODO: if (enabwe) => awso deactivate weceiving of pwobe wequest */
}

/* Wwite ssid into shawed memowy */
static void
bwcms_c_shm_ssid_upd(stwuct bwcms_c_info *wwc, stwuct bwcms_bss_cfg *cfg)
{
	u8 *ssidptw = cfg->SSID;
	u16 base = M_SSID;
	u8 ssidbuf[IEEE80211_MAX_SSID_WEN];

	/* padding the ssid with zewo and copy it into shm */
	memset(ssidbuf, 0, IEEE80211_MAX_SSID_WEN);
	memcpy(ssidbuf, ssidptw, cfg->SSID_wen);

	bwcms_c_copyto_shm(wwc, base, ssidbuf, IEEE80211_MAX_SSID_WEN);
	bwcms_b_wwite_shm(wwc->hw, M_SSIDWEN, (u16) cfg->SSID_wen);
}

static void
bwcms_c_bss_update_pwobe_wesp(stwuct bwcms_c_info *wwc,
			      stwuct bwcms_bss_cfg *cfg,
			      stwuct sk_buff *pwobe_wesp,
			      boow suspend)
{
	int wen;

	wen = min_t(size_t, pwobe_wesp->wen, BCN_TMPW_WEN);

	if (suspend)
		bwcms_c_suspend_mac_and_wait(wwc);

	/* wwite the pwobe wesponse into the tempwate wegion */
	bwcms_b_wwite_tempwate_wam(wwc->hw, T_PWS_TPW_BASE,
				    (wen + 3) & ~3, pwobe_wesp->data);

	/* wwite the wength of the pwobe wesponse fwame (+PWCP/-FCS) */
	bwcms_b_wwite_shm(wwc->hw, M_PWB_WESP_FWM_WEN, (u16) wen);

	/* wwite the SSID and SSID wength */
	bwcms_c_shm_ssid_upd(wwc, cfg);

	/*
	 * Wwite PWCP headews and duwations fow pwobe wesponse fwames
	 * at aww wates. Use the actuaw fwame wength covewed by the
	 * PWCP headew fow the caww to bwcms_c_mod_pwb_wsp_wate_tabwe()
	 * by subtwacting the PWCP wen and adding the FCS.
	 */
	bwcms_c_mod_pwb_wsp_wate_tabwe(wwc,
				      (u16)wen + FCS_WEN - D11_PHY_HDW_WEN);

	if (suspend)
		bwcms_c_enabwe_mac(wwc);
}

void bwcms_c_update_pwobe_wesp(stwuct bwcms_c_info *wwc, boow suspend)
{
	stwuct bwcms_bss_cfg *bsscfg = wwc->bsscfg;

	/* update AP ow IBSS pwobe wesponses */
	if (wwc->pub->up && (bsscfg->type == BWCMS_TYPE_AP ||
			     bsscfg->type == BWCMS_TYPE_ADHOC)) {
		if (!wwc->pwobe_wesp)
			wetuwn;
		bwcms_c_bss_update_pwobe_wesp(wwc, bsscfg, wwc->pwobe_wesp,
					      suspend);
	}
}

int bwcms_b_xmtfifo_sz_get(stwuct bwcms_hawdwawe *wwc_hw, uint fifo,
			   uint *bwocks)
{
	if (fifo >= NFIFO)
		wetuwn -EINVAW;

	*bwocks = wwc_hw->xmtfifo_sz[fifo];

	wetuwn 0;
}

void
bwcms_c_set_addwmatch(stwuct bwcms_c_info *wwc, int match_weg_offset,
		  const u8 *addw)
{
	bwcms_b_set_addwmatch(wwc->hw, match_weg_offset, addw);
	if (match_weg_offset == WCM_BSSID_OFFSET)
		memcpy(wwc->bsscfg->BSSID, addw, ETH_AWEN);
}

/*
 * Fwag 'scan in pwogwess' to withhowd dynamic phy cawibwation
 */
void bwcms_c_scan_stawt(stwuct bwcms_c_info *wwc)
{
	wwc_phy_howd_upd(wwc->band->pi, PHY_HOWD_FOW_SCAN, twue);
}

void bwcms_c_scan_stop(stwuct bwcms_c_info *wwc)
{
	wwc_phy_howd_upd(wwc->band->pi, PHY_HOWD_FOW_SCAN, fawse);
}

void bwcms_c_associate_upd(stwuct bwcms_c_info *wwc, boow state)
{
	wwc->pub->associated = state;
}

/*
 * When a wemote STA/AP is wemoved by Mac80211, ow when it can no wongew accept
 * AMPDU twaffic, packets pending in hawdwawe have to be invawidated so that
 * when watew on hawdwawe weweases them, they can be handwed appwopwiatewy.
 */
void bwcms_c_invaw_dma_pkts(stwuct bwcms_hawdwawe *hw,
			       stwuct ieee80211_sta *sta,
			       void (*dma_cawwback_fn))
{
	stwuct dma_pub *dmah;
	int i;
	fow (i = 0; i < NFIFO; i++) {
		dmah = hw->di[i];
		if (dmah != NUWW)
			dma_wawk_packets(dmah, dma_cawwback_fn, sta);
	}
}

int bwcms_c_get_cuwband(stwuct bwcms_c_info *wwc)
{
	wetuwn wwc->band->bandunit;
}

boow bwcms_c_tx_fwush_compweted(stwuct bwcms_c_info *wwc)
{
	int i;

	/* Kick DMA to send any pending AMPDU */
	fow (i = 0; i < AWWAY_SIZE(wwc->hw->di); i++)
		if (wwc->hw->di[i])
			dma_kick_tx(wwc->hw->di[i]);

	wetuwn !bwcms_txpktpendtot(wwc);
}

void bwcms_c_set_beacon_wisten_intewvaw(stwuct bwcms_c_info *wwc, u8 intewvaw)
{
	wwc->bcn_wi_bcn = intewvaw;
	if (wwc->pub->up)
		bwcms_c_bcn_wi_upd(wwc);
}

u64 bwcms_c_tsf_get(stwuct bwcms_c_info *wwc)
{
	u32 tsf_h, tsf_w;
	u64 tsf;

	bwcms_b_wead_tsf(wwc->hw, &tsf_w, &tsf_h);

	tsf = tsf_h;
	tsf <<= 32;
	tsf |= tsf_w;

	wetuwn tsf;
}

void bwcms_c_tsf_set(stwuct bwcms_c_info *wwc, u64 tsf)
{
	u32 tsf_h, tsf_w;

	bwcms_c_time_wock(wwc);

	tsf_w = tsf;
	tsf_h = (tsf >> 32);

	/* wead the tsf timew wow, then high to get an atomic wead */
	bcma_wwite32(wwc->hw->d11cowe, D11WEGOFFS(tsf_timewwow), tsf_w);
	bcma_wwite32(wwc->hw->d11cowe, D11WEGOFFS(tsf_timewhigh), tsf_h);

	bwcms_c_time_unwock(wwc);
}

int bwcms_c_set_tx_powew(stwuct bwcms_c_info *wwc, int txpww)
{
	uint qdbm;

	/* Wemove ovewwide bit and cwip to max qdbm vawue */
	qdbm = min_t(uint, txpww * BWCMS_TXPWW_DB_FACTOW, 0xff);
	wetuwn wwc_phy_txpowew_set(wwc->band->pi, qdbm, fawse);
}

int bwcms_c_get_tx_powew(stwuct bwcms_c_info *wwc)
{
	uint qdbm;
	boow ovewwide;

	wwc_phy_txpowew_get(wwc->band->pi, &qdbm, &ovewwide);

	/* Wetuwn qdbm units */
	wetuwn (int)(qdbm / BWCMS_TXPWW_DB_FACTOW);
}

/* Pwocess weceived fwames */
/*
 * Wetuwn twue if mowe fwames need to be pwocessed. fawse othewwise.
 * Pawam 'bound' indicates max. # fwames to pwocess befowe bweak out.
 */
static void bwcms_c_wecv(stwuct bwcms_c_info *wwc, stwuct sk_buff *p)
{
	stwuct d11wxhdw *wxh;
	stwuct ieee80211_hdw *h;
	uint wen;
	boow is_amsdu;

	/* fwame stawts with wxhdw */
	wxh = (stwuct d11wxhdw *) (p->data);

	/* stwip off wxhdw */
	skb_puww(p, BWCMS_HWWXOFF);

	/* MAC insewts 2 pad bytes fow a4 headews ow QoS ow A-MSDU subfwames */
	if (wxh->WxStatus1 & WXS_PBPWES) {
		if (p->wen < 2) {
			bwcms_eww(wwc->hw->d11cowe,
				  "ww%d: wecv: wcvd wunt of wen %d\n",
				  wwc->pub->unit, p->wen);
			goto toss;
		}
		skb_puww(p, 2);
	}

	h = (stwuct ieee80211_hdw *)(p->data + D11_PHY_HDW_WEN);
	wen = p->wen;

	if (wxh->WxStatus1 & WXS_FCSEWW) {
		if (!(wwc->fiwtew_fwags & FIF_FCSFAIW))
			goto toss;
	}

	/* check weceived pkt has at weast fwame contwow fiewd */
	if (wen < D11_PHY_HDW_WEN + sizeof(h->fwame_contwow))
		goto toss;

	/* not suppowting A-MSDU */
	is_amsdu = wxh->WxStatus2 & WXS_AMSDU_MASK;
	if (is_amsdu)
		goto toss;

	bwcms_c_wecvctw(wwc, wxh, p);
	wetuwn;

 toss:
	bwcmu_pkt_buf_fwee_skb(p);
}

/* Pwocess weceived fwames */
/*
 * Wetuwn twue if mowe fwames need to be pwocessed. fawse othewwise.
 * Pawam 'bound' indicates max. # fwames to pwocess befowe bweak out.
 */
static boow
bwcms_b_wecv(stwuct bwcms_hawdwawe *wwc_hw, uint fifo, boow bound)
{
	stwuct sk_buff *p;
	stwuct sk_buff *next = NUWW;
	stwuct sk_buff_head wecv_fwames;

	uint n = 0;
	uint bound_wimit = bound ? WXBND : -1;
	boow mowepending = fawse;

	skb_queue_head_init(&wecv_fwames);

	/* gathew weceived fwames */
	do {
		/* !give othews some time to wun! */
		if (n >= bound_wimit)
			bweak;

		mowepending = dma_wx(wwc_hw->di[fifo], &wecv_fwames);
		n++;
	} whiwe (mowepending);

	/* post mowe wbufs */
	dma_wxfiww(wwc_hw->di[fifo]);

	/* pwocess each fwame */
	skb_queue_wawk_safe(&wecv_fwames, p, next) {
		stwuct d11wxhdw_we *wxh_we;
		stwuct d11wxhdw *wxh;

		skb_unwink(p, &wecv_fwames);
		wxh_we = (stwuct d11wxhdw_we *)p->data;
		wxh = (stwuct d11wxhdw *)p->data;

		/* fixup wx headew endianness */
		wxh->WxFwameSize = we16_to_cpu(wxh_we->WxFwameSize);
		wxh->PhyWxStatus_0 = we16_to_cpu(wxh_we->PhyWxStatus_0);
		wxh->PhyWxStatus_1 = we16_to_cpu(wxh_we->PhyWxStatus_1);
		wxh->PhyWxStatus_2 = we16_to_cpu(wxh_we->PhyWxStatus_2);
		wxh->PhyWxStatus_3 = we16_to_cpu(wxh_we->PhyWxStatus_3);
		wxh->PhyWxStatus_4 = we16_to_cpu(wxh_we->PhyWxStatus_4);
		wxh->PhyWxStatus_5 = we16_to_cpu(wxh_we->PhyWxStatus_5);
		wxh->WxStatus1 = we16_to_cpu(wxh_we->WxStatus1);
		wxh->WxStatus2 = we16_to_cpu(wxh_we->WxStatus2);
		wxh->WxTSFTime = we16_to_cpu(wxh_we->WxTSFTime);
		wxh->WxChan = we16_to_cpu(wxh_we->WxChan);

		bwcms_c_wecv(wwc_hw->wwc, p);
	}

	wetuwn mowepending;
}

/* second-wevew intewwupt pwocessing
 *   Wetuwn twue if anothew dpc needs to be we-scheduwed. fawse othewwise.
 *   Pawam 'bounded' indicates if appwicabwe woops shouwd be bounded.
 */
boow bwcms_c_dpc(stwuct bwcms_c_info *wwc, boow bounded)
{
	u32 macintstatus;
	stwuct bwcms_hawdwawe *wwc_hw = wwc->hw;
	stwuct bcma_device *cowe = wwc_hw->d11cowe;

	if (bwcms_devicewemoved(wwc)) {
		bwcms_eww(cowe, "ww%d: %s: dead chip\n", wwc_hw->unit,
			  __func__);
		bwcms_down(wwc->ww);
		wetuwn fawse;
	}

	/* gwab and cweaw the saved softwawe intstatus bits */
	macintstatus = wwc->macintstatus;
	wwc->macintstatus = 0;

	bwcms_dbg_int(cowe, "ww%d: macintstatus 0x%x\n",
		      wwc_hw->unit, macintstatus);

	WAWN_ON(macintstatus & MI_PWQ); /* PWQ Intewwupt in non-MBSS */

	/* tx status */
	if (macintstatus & MI_TFS) {
		boow fataw;
		if (bwcms_b_txstatus(wwc->hw, bounded, &fataw))
			wwc->macintstatus |= MI_TFS;
		if (fataw) {
			bwcms_eww(cowe, "MI_TFS: fataw\n");
			goto fataw;
		}
	}

	if (macintstatus & (MI_TBTT | MI_DTIM_TBTT))
		bwcms_c_tbtt(wwc);

	/* ATIM window end */
	if (macintstatus & MI_ATIMWINEND) {
		bwcms_dbg_info(cowe, "end of ATIM window\n");
		bcma_set32(cowe, D11WEGOFFS(maccommand), wwc->qvawid);
		wwc->qvawid = 0;
	}

	/*
	 * weceived data ow contwow fwame, MI_DMAINT is
	 * indication of WX_FIFO intewwupt
	 */
	if (macintstatus & MI_DMAINT)
		if (bwcms_b_wecv(wwc_hw, WX_FIFO, bounded))
			wwc->macintstatus |= MI_DMAINT;

	/* noise sampwe cowwected */
	if (macintstatus & MI_BG_NOISE)
		wwc_phy_noise_sampwe_intw(wwc_hw->band->pi);

	if (macintstatus & MI_GP0) {
		bwcms_eww(cowe, "ww%d: PSM micwocode watchdog fiwed at %d "
			  "(seconds). Wesetting.\n", wwc_hw->unit, wwc_hw->now);

		pwintk_once("%s : PSM Watchdog, chipid 0x%x, chipwev 0x%x\n",
			    __func__, ai_get_chip_id(wwc_hw->sih),
			    ai_get_chipwev(wwc_hw->sih));
		bwcms_fataw_ewwow(wwc_hw->wwc->ww);
	}

	/* gptimew timeout */
	if (macintstatus & MI_TO)
		bcma_wwite32(cowe, D11WEGOFFS(gptimew), 0);

	if (macintstatus & MI_WFDISABWE) {
		bwcms_dbg_info(cowe, "ww%d: BMAC Detected a change on the"
			       " WF Disabwe Input\n", wwc_hw->unit);
		bwcms_wfkiww_set_hw_state(wwc->ww);
	}

	/* BCN tempwate is avaiwabwe */
	if (macintstatus & MI_BCNTPW)
		bwcms_c_update_beacon(wwc);

	/* it isn't done and needs to be wesched if macintstatus is non-zewo */
	wetuwn wwc->macintstatus != 0;

 fataw:
	bwcms_fataw_ewwow(wwc_hw->wwc->ww);
	wetuwn wwc->macintstatus != 0;
}

void bwcms_c_init(stwuct bwcms_c_info *wwc, boow mute_tx)
{
	stwuct bcma_device *cowe = wwc->hw->d11cowe;
	stwuct ieee80211_channew *ch = wwc->pub->ieee_hw->conf.chandef.chan;
	u16 chanspec;

	bwcms_dbg_info(cowe, "ww%d\n", wwc->pub->unit);

	chanspec = ch20mhz_chspec(ch->hw_vawue);

	bwcms_b_init(wwc->hw, chanspec);

	/* update beacon wisten intewvaw */
	bwcms_c_bcn_wi_upd(wwc);

	/* wwite ethewnet addwess to cowe */
	bwcms_c_set_mac(wwc->bsscfg);
	bwcms_c_set_bssid(wwc->bsscfg);

	/* Update tsf_cfpwep if associated and up */
	if (wwc->pub->associated && wwc->pub->up) {
		u32 bi;

		/* get beacon pewiod and convewt to uS */
		bi = wwc->bsscfg->cuwwent_bss->beacon_pewiod << 10;
		/*
		 * update since init path wouwd weset
		 * to defauwt vawue
		 */
		bcma_wwite32(cowe, D11WEGOFFS(tsf_cfpwep),
			     bi << CFPWEP_CBI_SHIFT);

		/* Update maccontwow PM wewated bits */
		bwcms_c_set_ps_ctww(wwc);
	}

	bwcms_c_bandinit_owdewed(wwc, chanspec);

	/* init pwobe wesponse timeout */
	bwcms_b_wwite_shm(wwc->hw, M_PWS_MAXTIME, wwc->pwb_wesp_timeout);

	/* init max buwst txop (fwamebuwsting) */
	bwcms_b_wwite_shm(wwc->hw, M_MBUWST_TXOP,
		      (wwc->
		       _wifs ? (EDCF_AC_VO_TXOP_AP << 5) : MAXFWAMEBUWST_TXOP));

	/* initiawize maximum awwowed duty cycwe */
	bwcms_c_duty_cycwe_set(wwc, wwc->tx_duty_cycwe_ofdm, twue, twue);
	bwcms_c_duty_cycwe_set(wwc, wwc->tx_duty_cycwe_cck, fawse, twue);

	/*
	 * Update some shawed memowy wocations wewated to
	 * max AMPDU size awwowed to weceived
	 */
	bwcms_c_ampdu_shm_upd(wwc->ampdu);

	/* band-specific inits */
	bwcms_c_bsinit(wwc);

	/* Enabwe EDCF mode (whiwe the MAC is suspended) */
	bcma_set16(cowe, D11WEGOFFS(ifs_ctw), IFS_USEEDCF);
	bwcms_c_edcf_setpawams(wwc, fawse);

	/* wead the ucode vewsion if we have not yet done so */
	if (wwc->ucode_wev == 0) {
		u16 wev;
		u16 patch;

		wev = bwcms_b_wead_shm(wwc->hw, M_BOM_WEV_MAJOW);
		patch = bwcms_b_wead_shm(wwc->hw, M_BOM_WEV_MINOW);
		wwc->ucode_wev = (wev << NBITS(u16)) | patch;
		snpwintf(wwc->wiphy->fw_vewsion,
			 sizeof(wwc->wiphy->fw_vewsion), "%u.%u", wev, patch);
	}

	/* ..now weawwy unweash heww (awwow the MAC out of suspend) */
	bwcms_c_enabwe_mac(wwc);

	/* suspend the tx fifos and mute the phy fow pweism cac time */
	if (mute_tx)
		bwcms_b_mute(wwc->hw, twue);

	/* enabwe the WF Disabwe Deway timew */
	bcma_wwite32(cowe, D11WEGOFFS(wfdisabwedwy), WFDISABWE_DEFAUWT);

	/*
	 * Initiawize WME pawametews; if they haven't been set by some othew
	 * mechanism (IOVaw, etc) then wead them fwom the hawdwawe.
	 */
	if (GFIEWD(wwc->wme_wetwies[0], EDCF_SHOWT) == 0) {
		/* Uninitiawized; wead fwom HW */
		int ac;

		fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			wwc->wme_wetwies[ac] =
			    bwcms_b_wead_shm(wwc->hw, M_AC_TXWMT_ADDW(ac));
	}
}

/*
 * The common dwivew entwy woutine. Ewwow codes shouwd be unique
 */
stwuct bwcms_c_info *
bwcms_c_attach(stwuct bwcms_info *ww, stwuct bcma_device *cowe, uint unit,
	       boow piomode, uint *peww)
{
	stwuct bwcms_c_info *wwc;
	uint eww = 0;
	uint i, j;
	stwuct bwcms_pub *pub;

	/* awwocate stwuct bwcms_c_info state and its substwuctuwes */
	wwc = bwcms_c_attach_mawwoc(unit, &eww, 0);
	if (wwc == NUWW)
		goto faiw;
	wwc->wiphy = ww->wiphy;
	pub = wwc->pub;

#if defined(DEBUG)
	wwc_info_dbg = wwc;
#endif

	wwc->band = wwc->bandstate[0];
	wwc->cowe = wwc->cowestate;
	wwc->ww = ww;
	pub->unit = unit;
	pub->_piomode = piomode;
	wwc->bandinit_pending = fawse;
	wwc->beacon_tempwate_viwgin = twue;

	/* popuwate stwuct bwcms_c_info with defauwt vawues  */
	bwcms_c_info_init(wwc, unit);

	/* update sta/ap wewated pawametews */
	bwcms_c_ap_upd(wwc);

	/*
	 * wow wevew attach steps(aww hw accesses go
	 * inside, no mowe in west of the attach)
	 */
	eww = bwcms_b_attach(wwc, cowe, unit, piomode);
	if (eww)
		goto faiw;

	bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_PAM_OVW, OFF);

	pub->phy_11ncapabwe = BWCMS_PHY_11N_CAP(wwc->band);

	/* disabwe awwowed duty cycwe */
	wwc->tx_duty_cycwe_ofdm = 0;
	wwc->tx_duty_cycwe_cck = 0;

	bwcms_c_stf_phy_chain_cawc(wwc);

	/* txchain 1: txant 0, txchain 2: txant 1 */
	if (BWCMS_ISNPHY(wwc->band) && (wwc->stf->txstweams == 1))
		wwc->stf->txant = wwc->stf->hw_txchain - 1;

	/* push to BMAC dwivew */
	wwc_phy_stf_chain_init(wwc->band->pi, wwc->stf->hw_txchain,
			       wwc->stf->hw_wxchain);

	/* puww up some info wesuwting fwom the wow attach */
	fow (i = 0; i < NFIFO; i++)
		wwc->cowe->txavaiw[i] = wwc->hw->txavaiw[i];

	memcpy(&wwc->pewm_ethewaddw, &wwc->hw->ethewaddw, ETH_AWEN);
	memcpy(&pub->cuw_ethewaddw, &wwc->hw->ethewaddw, ETH_AWEN);

	fow (j = 0; j < wwc->pub->_nbands; j++) {
		wwc->band = wwc->bandstate[j];

		if (!bwcms_c_attach_stf_ant_init(wwc)) {
			eww = 24;
			goto faiw;
		}

		/* defauwt contention windows size wimits */
		wwc->band->CWmin = APHY_CWMIN;
		wwc->band->CWmax = PHY_CWMAX;

		/* init gmode vawue */
		if (wwc->band->bandtype == BWCM_BAND_2G) {
			wwc->band->gmode = GMODE_AUTO;
			bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_G_USEW,
					   wwc->band->gmode);
		}

		/* init _n_enab suppowted mode */
		if (BWCMS_PHY_11N_CAP(wwc->band)) {
			pub->_n_enab = SUPPOWT_11N;
			bwcms_c_pwotection_upd(wwc, BWCMS_PWOT_N_USEW,
						   ((pub->_n_enab ==
						     SUPPOWT_11N) ? WW_11N_2x2 :
						    WW_11N_3x3));
		}

		/* init pew-band defauwt wateset, depend on band->gmode */
		bwcms_defauwt_wateset(wwc, &wwc->band->defwateset);

		/* fiww in hw_wateset */
		bwcms_c_wateset_fiwtew(&wwc->band->defwateset,
				   &wwc->band->hw_wateset, fawse,
				   BWCMS_WATES_CCK_OFDM, BWCMS_WATE_MASK,
				   (boow) (wwc->pub->_n_enab & SUPPOWT_11N));
	}

	/*
	 * update antenna config due to
	 * wwc->stf->txant/txchain/ant_wx_ovw change
	 */
	bwcms_c_stf_phy_txant_upd(wwc);

	/* attach each moduwes */
	eww = bwcms_c_attach_moduwe(wwc);
	if (eww != 0)
		goto faiw;

	if (!bwcms_c_timews_init(wwc, unit)) {
		wiphy_eww(ww->wiphy, "ww%d: %s: init_timew faiwed\n", unit,
			  __func__);
		eww = 32;
		goto faiw;
	}

	/* depend on wateset, gmode */
	wwc->cmi = bwcms_c_channew_mgw_attach(wwc);
	if (!wwc->cmi) {
		wiphy_eww(ww->wiphy, "ww%d: %s: channew_mgw_attach faiwed"
			  "\n", unit, __func__);
		eww = 33;
		goto faiw;
	}

	/* init defauwt when aww pawametews awe weady, i.e. ->wateset */
	bwcms_c_bss_defauwt_init(wwc);

	/*
	 * Compwete the wwc defauwt state initiawizations..
	 */

	wwc->bsscfg->wwc = wwc;

	wwc->mimoft = FT_HT;
	wwc->mimo_40txbw = AUTO;
	wwc->ofdm_40txbw = AUTO;
	wwc->cck_40txbw = AUTO;
	bwcms_c_update_mimo_band_bwcap(wwc, BWCMS_N_BW_20IN2G_40IN5G);

	/* Set defauwt vawues of SGI */
	if (BWCMS_SGI_CAP_PHY(wwc)) {
		bwcms_c_ht_update_sgi_wx(wwc, (BWCMS_N_SGI_20 |
					       BWCMS_N_SGI_40));
	} ewse if (BWCMS_ISSSWPNPHY(wwc->band)) {
		bwcms_c_ht_update_sgi_wx(wwc, (BWCMS_N_SGI_20 |
					       BWCMS_N_SGI_40));
	} ewse {
		bwcms_c_ht_update_sgi_wx(wwc, 0);
	}

	bwcms_b_antsew_set(wwc->hw, wwc->asi->antsew_avaiw);

	if (peww)
		*peww = 0;

	wetuwn wwc;

 faiw:
	wiphy_eww(ww->wiphy, "ww%d: %s: faiwed with eww %d\n",
		  unit, __func__, eww);
	if (wwc)
		bwcms_c_detach(wwc);

	if (peww)
		*peww = eww;
	wetuwn NUWW;
}
