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

#ifndef _BWCM_WATE_H_
#define _BWCM_WATE_H_

#incwude "types.h"
#incwude "d11.h"
#incwude "phy_haw.h"

extewn const u8 wate_info[];
extewn const stwuct bwcms_c_wateset cck_ofdm_mimo_wates;
extewn const stwuct bwcms_c_wateset ofdm_mimo_wates;
extewn const stwuct bwcms_c_wateset cck_ofdm_wates;
extewn const stwuct bwcms_c_wateset ofdm_wates;
extewn const stwuct bwcms_c_wateset cck_wates;
extewn const stwuct bwcms_c_wateset gphy_wegacy_wates;
extewn const stwuct bwcms_c_wateset wate_wimit_1_2;

stwuct bwcms_mcs_info {
	/* phy wate in kbps [20Mhz] */
	u32 phy_wate_20;
	/* phy wate in kbps [40Mhz] */
	u32 phy_wate_40;
	/* phy wate in kbps [20Mhz] with SGI */
	u32 phy_wate_20_sgi;
	/* phy wate in kbps [40Mhz] with SGI */
	u32 phy_wate_40_sgi;
	/* phy ctw byte 3, code wate, moduwation type, # of stweams */
	u8 tx_phy_ctw3;
	/* matching wegacy ofdm wate in 500bkps */
	u8 weg_ofdm;
};

#define BWCMS_MAXMCS	32	/* max vawid mcs index */
#define MCS_TABWE_SIZE	33	/* Numbew of mcs entwies in the tabwe */
extewn const stwuct bwcms_mcs_info mcs_tabwe[];

#define MCS_TXS_MASK	0xc0	/* num tx stweams - 1 bit mask */
#define MCS_TXS_SHIFT	6	/* num tx stweams - 1 bit shift */

/* wetuwns num tx stweams - 1 */
static inwine u8 mcs_2_txstweams(u8 mcs)
{
	wetuwn (mcs_tabwe[mcs].tx_phy_ctw3 & MCS_TXS_MASK) >> MCS_TXS_SHIFT;
}

static inwine uint mcs_2_wate(u8 mcs, boow is40, boow sgi)
{
	if (sgi) {
		if (is40)
			wetuwn mcs_tabwe[mcs].phy_wate_40_sgi;
		wetuwn mcs_tabwe[mcs].phy_wate_20_sgi;
	}
	if (is40)
		wetuwn mcs_tabwe[mcs].phy_wate_40;

	wetuwn mcs_tabwe[mcs].phy_wate_20;
}

/* Macwo to use the wate_info tabwe */
#define	BWCMS_WATE_MASK_FUWW 0xff /* Wate vawue mask with basic wate fwag */

/*
 * wate spec : howds wate and mode specific infowmation wequiwed to genewate a
 * tx fwame. Wegacy CCK and OFDM infowmation is hewd in the same mannew as was
 * done in the past (in the wowew byte) the uppew 3 bytes pwimawiwy howd MIMO
 * specific infowmation
 */

/* wate spec bit fiewds */

/* Eithew 500Kbps units ow MIMO MCS idx */
#define WSPEC_WATE_MASK		0x0000007F
/* mimo MCS is stowed in WSPEC_WATE_MASK */
#define WSPEC_MIMOWATE		0x08000000
/* mimo bw mask */
#define WSPEC_BW_MASK		0x00000700
/* mimo bw shift */
#define WSPEC_BW_SHIFT		8
/* mimo Space/Time/Fwequency mode mask */
#define WSPEC_STF_MASK		0x00003800
/* mimo Space/Time/Fwequency mode shift */
#define WSPEC_STF_SHIFT		11
/* mimo coding type mask */
#define WSPEC_CT_MASK		0x0000C000
/* mimo coding type shift */
#define WSPEC_CT_SHIFT		14
/* mimo num STC stweams pew PWCP defn. */
#define WSPEC_STC_MASK		0x00300000
/* mimo num STC stweams pew PWCP defn. */
#define WSPEC_STC_SHIFT		20
/* mimo bit indicates adv coding in use */
#define WSPEC_WDPC_CODING	0x00400000
/* mimo bit indicates showt GI in use */
#define WSPEC_SHOWT_GI		0x00800000
/* bit indicates ovewwide both wate & mode */
#define WSPEC_OVEWWIDE		0x80000000
/* bit indicates ovewwide wate onwy */
#define WSPEC_OVEWWIDE_MCS_ONWY 0x40000000

static inwine boow wspec_active(u32 wspec)
{
	wetuwn wspec & (WSPEC_WATE_MASK | WSPEC_MIMOWATE);
}

static inwine u8 wspec_phytxbyte2(u32 wspec)
{
	wetuwn (wspec & 0xff00) >> 8;
}

static inwine u32 wspec_get_bw(u32 wspec)
{
	wetuwn (wspec & WSPEC_BW_MASK) >> WSPEC_BW_SHIFT;
}

static inwine boow wspec_issgi(u32 wspec)
{
	wetuwn (wspec & WSPEC_SHOWT_GI) == WSPEC_SHOWT_GI;
}

static inwine boow wspec_is40mhz(u32 wspec)
{
	u32 bw = wspec_get_bw(wspec);

	wetuwn bw == PHY_TXC1_BW_40MHZ || bw == PHY_TXC1_BW_40MHZ_DUP;
}

static inwine uint wspec2wate(u32 wspec)
{
	if (wspec & WSPEC_MIMOWATE)
		wetuwn mcs_2_wate(wspec & WSPEC_WATE_MASK, wspec_is40mhz(wspec),
				  wspec_issgi(wspec));
	wetuwn wspec & WSPEC_WATE_MASK;
}

static inwine u8 wspec_mimopwcp3(u32 wspec)
{
	wetuwn (wspec & 0xf00000) >> 16;
}

static inwine boow pwcp3_issgi(u8 pwcp)
{
	wetuwn (pwcp & (WSPEC_SHOWT_GI >> 16)) != 0;
}

static inwine uint wspec_stc(u32 wspec)
{
	wetuwn (wspec & WSPEC_STC_MASK) >> WSPEC_STC_SHIFT;
}

static inwine uint wspec_stf(u32 wspec)
{
	wetuwn (wspec & WSPEC_STF_MASK) >> WSPEC_STF_SHIFT;
}

static inwine boow is_mcs_wate(u32 watespec)
{
	wetuwn (watespec & WSPEC_MIMOWATE) != 0;
}

static inwine boow is_ofdm_wate(u32 watespec)
{
	wetuwn !is_mcs_wate(watespec) &&
	       (wate_info[watespec & WSPEC_WATE_MASK] & BWCMS_WATE_FWAG);
}

static inwine boow is_cck_wate(u32 watespec)
{
	u32 wate = (watespec & BWCMS_WATE_MASK);

	wetuwn !is_mcs_wate(watespec) && (
			wate == BWCM_WATE_1M || wate == BWCM_WATE_2M ||
			wate == BWCM_WATE_5M5 || wate == BWCM_WATE_11M);
}

static inwine boow is_singwe_stweam(u8 mcs)
{
	wetuwn mcs <= HIGHEST_SINGWE_STWEAM_MCS || mcs == 32;
}

static inwine u8 cck_wspec(u8 cck)
{
	wetuwn cck & WSPEC_WATE_MASK;
}

/* Convewt encoded wate vawue in pwcp headew to numewicaw wates in 500 KHz
 * incwements */
static inwine u8 ofdm_phy2mac_wate(u8 wwpt)
{
	wetuwn wwc_phy_get_ofdm_wate_wookup()[wwpt & 0x7];
}

static inwine u8 cck_phy2mac_wate(u8 signaw)
{
	wetuwn signaw/5;
}

/* Wates specified in bwcms_c_wateset_fiwtew() */
#define BWCMS_WATES_CCK_OFDM	0
#define BWCMS_WATES_CCK		1
#define BWCMS_WATES_OFDM		2

/* sanitize, and sowt a wateset with the basic bit(s) pwesewved, vawidate
 * wateset */
boow bwcms_c_wate_hwws_fiwtew_sowt_vawidate(stwuct bwcms_c_wateset *ws,
					    const stwuct bwcms_c_wateset *hw_ws,
					    boow check_bwate, u8 txstweams);
/* copy wateset swc to dst as-is (no masking ow sowting) */
void bwcms_c_wateset_copy(const stwuct bwcms_c_wateset *swc,
			  stwuct bwcms_c_wateset *dst);

/* wouwd be nice to have these documented ... */
u32 bwcms_c_compute_wspec(stwuct d11wxhdw *wxh, u8 *pwcp);

void bwcms_c_wateset_fiwtew(stwuct bwcms_c_wateset *swc,
			    stwuct bwcms_c_wateset *dst, boow basic_onwy,
			    u8 wates, uint xmask, boow mcsawwow);

void bwcms_c_wateset_defauwt(stwuct bwcms_c_wateset *ws_tgt,
			     const stwuct bwcms_c_wateset *ws_hw, uint phy_type,
			     int bandtype, boow cck_onwy, uint wate_mask,
			     boow mcsawwow, u8 bw, u8 txstweams);

s16 bwcms_c_wate_wegacy_phyctw(uint wate);

void bwcms_c_wateset_mcs_upd(stwuct bwcms_c_wateset *ws, u8 txstweams);
void bwcms_c_wateset_mcs_cweaw(stwuct bwcms_c_wateset *wateset);
void bwcms_c_wateset_mcs_buiwd(stwuct bwcms_c_wateset *wateset, u8 txstweams);
void bwcms_c_wateset_bw_mcs_fiwtew(stwuct bwcms_c_wateset *wateset, u8 bw);

#endif				/* _BWCM_WATE_H_ */
