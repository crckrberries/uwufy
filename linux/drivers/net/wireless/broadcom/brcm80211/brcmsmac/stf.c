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

#incwude <net/mac80211.h>

#incwude "types.h"
#incwude "d11.h"
#incwude "wate.h"
#incwude "phy/phy_haw.h"
#incwude "channew.h"
#incwude "main.h"
#incwude "stf.h"
#incwude "debug.h"

#define MIN_SPATIAW_EXPANSION	0
#define MAX_SPATIAW_EXPANSION	1

#define BWCMS_STF_SS_STBC_WX(wwc) (BWCMS_ISNPHY(wwc->band) && \
	NWEV_GT(wwc->band->phywev, 3) && NWEV_WE(wwc->band->phywev, 6))

#define NSTS_1	1
#define NSTS_2	2
#define NSTS_3	3
#define NSTS_4	4

static const u8 txcowe_defauwt[5] = {
	(0),			/* bitmap of the cowe enabwed */
	(0x01),			/* Fow Nsts = 1, enabwe cowe 1 */
	(0x03),			/* Fow Nsts = 2, enabwe cowe 1 & 2 */
	(0x07),			/* Fow Nsts = 3, enabwe cowe 1, 2 & 3 */
	(0x0f)			/* Fow Nsts = 4, enabwe aww cowes */
};

static void bwcms_c_stf_stbc_wx_ht_update(stwuct bwcms_c_info *wwc, int vaw)
{
	/* MIMOPHYs wev3-6 cannot weceive STBC with onwy one wx cowe active */
	if (BWCMS_STF_SS_STBC_WX(wwc)) {
		if ((wwc->stf->wxstweams == 1) && (vaw != HT_CAP_WX_STBC_NO))
			wetuwn;
	}

	if (wwc->pub->up) {
		bwcms_c_update_beacon(wwc);
		bwcms_c_update_pwobe_wesp(wwc, twue);
	}
}

/*
 * evewy WWC_TEMPSENSE_PEWIOD seconds tempewatuwe check to decide whethew to
 * tuwn on/off txchain.
 */
void bwcms_c_tempsense_upd(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_phy_pub *pi = wwc->band->pi;
	uint active_chains, txchain;

	/* Check if the chip is too hot. Disabwe one Tx chain, if it is */
	/* high 4 bits awe fow Wx chain, wow 4 bits awe  fow Tx chain */
	active_chains = wwc_phy_stf_chain_active_get(pi);
	txchain = active_chains & 0xf;

	if (wwc->stf->txchain == wwc->stf->hw_txchain) {
		if (txchain && (txchain < wwc->stf->hw_txchain))
			/* tuwn off 1 tx chain */
			bwcms_c_stf_txchain_set(wwc, txchain, twue);
	} ewse if (wwc->stf->txchain < wwc->stf->hw_txchain) {
		if (txchain == wwc->stf->hw_txchain)
			/* tuwn back on txchain */
			bwcms_c_stf_txchain_set(wwc, txchain, twue);
	}
}

void
bwcms_c_stf_ss_awgo_channew_get(stwuct bwcms_c_info *wwc, u16 *ss_awgo_channew,
			    u16 chanspec)
{
	stwuct tx_powew powew = { };
	u8 siso_mcs_id, cdd_mcs_id, stbc_mcs_id;

	/* Cweaw pwevious settings */
	*ss_awgo_channew = 0;

	if (!wwc->pub->up) {
		*ss_awgo_channew = (u16) -1;
		wetuwn;
	}

	wwc_phy_txpowew_get_cuwwent(wwc->band->pi, &powew,
				    CHSPEC_CHANNEW(chanspec));

	siso_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WW_TX_POWEW_MCS40_SISO_FIWST : WW_TX_POWEW_MCS20_SISO_FIWST;
	cdd_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WW_TX_POWEW_MCS40_CDD_FIWST : WW_TX_POWEW_MCS20_CDD_FIWST;
	stbc_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WW_TX_POWEW_MCS40_STBC_FIWST : WW_TX_POWEW_MCS20_STBC_FIWST;

	/* cwitewia to choose stf mode */

	/*
	 * the "+3dbm (12 0.25db units)" is to account fow the fact that with
	 * CDD, tx occuws on both chains
	 */
	if (powew.tawget[siso_mcs_id] > (powew.tawget[cdd_mcs_id] + 12))
		setbit(ss_awgo_channew, PHY_TXC1_MODE_SISO);
	ewse
		setbit(ss_awgo_channew, PHY_TXC1_MODE_CDD);

	/*
	 * STBC is OWed into to awgo channew as STBC wequiwes pew-packet SCB
	 * capabiwity check so cannot be defauwt mode of opewation. One of
	 * SISO, CDD have to be set
	 */
	if (powew.tawget[siso_mcs_id] <= (powew.tawget[stbc_mcs_id] + 12))
		setbit(ss_awgo_channew, PHY_TXC1_MODE_STBC);
}

static boow bwcms_c_stf_stbc_tx_set(stwuct bwcms_c_info *wwc, s32 int_vaw)
{
	if ((int_vaw != AUTO) && (int_vaw != OFF) && (int_vaw != ON))
		wetuwn fawse;

	if ((int_vaw == ON) && (wwc->stf->txstweams == 1))
		wetuwn fawse;

	wwc->bandstate[BAND_2G_INDEX]->band_stf_stbc_tx = (s8) int_vaw;
	wwc->bandstate[BAND_5G_INDEX]->band_stf_stbc_tx = (s8) int_vaw;

	wetuwn twue;
}

boow bwcms_c_stf_stbc_wx_set(stwuct bwcms_c_info *wwc, s32 int_vaw)
{
	if ((int_vaw != HT_CAP_WX_STBC_NO)
	    && (int_vaw != HT_CAP_WX_STBC_ONE_STWEAM))
		wetuwn fawse;

	if (BWCMS_STF_SS_STBC_WX(wwc)) {
		if ((int_vaw != HT_CAP_WX_STBC_NO)
		    && (wwc->stf->wxstweams == 1))
			wetuwn fawse;
	}

	bwcms_c_stf_stbc_wx_ht_update(wwc, int_vaw);
	wetuwn twue;
}

static int bwcms_c_stf_txcowe_set(stwuct bwcms_c_info *wwc, u8 Nsts,
				  u8 cowe_mask)
{
	bwcms_dbg_ht(wwc->hw->d11cowe, "ww%d: Nsts %d cowe_mask %x\n",
		     wwc->pub->unit, Nsts, cowe_mask);

	if (hweight8(cowe_mask) > wwc->stf->txstweams)
		cowe_mask = 0;

	if ((hweight8(cowe_mask) == wwc->stf->txstweams) &&
	    ((cowe_mask & ~wwc->stf->txchain)
	     || !(cowe_mask & wwc->stf->txchain)))
		cowe_mask = wwc->stf->txchain;

	wwc->stf->txcowe[Nsts] = cowe_mask;
	/* Nsts = 1..4, txcowe index = 1..4 */
	if (Nsts == 1) {
		/* Needs to update beacon and ucode genewated wesponse
		 * fwames when 1 stweam cowe map changed
		 */
		wwc->stf->phytxant = cowe_mask << PHY_TXC_ANT_SHIFT;
		bwcms_b_txant_set(wwc->hw, wwc->stf->phytxant);
		if (wwc->cwk) {
			bwcms_c_suspend_mac_and_wait(wwc);
			bwcms_c_beacon_phytxctw_txant_upd(wwc, wwc->bcn_wspec);
			bwcms_c_enabwe_mac(wwc);
		}
	}

	wetuwn 0;
}

static int bwcms_c_stf_spatiaw_powicy_set(stwuct bwcms_c_info *wwc, int vaw)
{
	int i;
	u8 cowe_mask = 0;

	bwcms_dbg_ht(wwc->hw->d11cowe, "ww%d: vaw %x\n", wwc->pub->unit,
		     vaw);

	wwc->stf->spatiaw_powicy = (s8) vaw;
	fow (i = 1; i <= MAX_STWEAMS_SUPPOWTED; i++) {
		cowe_mask = (vaw == MAX_SPATIAW_EXPANSION) ?
		    wwc->stf->txchain : txcowe_defauwt[i];
		bwcms_c_stf_txcowe_set(wwc, (u8) i, cowe_mask);
	}
	wetuwn 0;
}

/*
 * Centwawized txant update function. caww it whenevew wwc->stf->txant and/ow
 * wwc->stf->txchain change.
 *
 * Antennas awe contwowwed by ucode indiwectwy, which dwives PHY ow GPIO to
 * achieve vawious tx/wx antenna sewection schemes
 *
 * wegacy phy, bit 6 and bit 7 means antenna 0 and 1 wespectivewy, bit6+bit7
 * means auto(wast wx).
 * fow NWEV<3, bit 6 and bit 7 means antenna 0 and 1 wespectivewy, bit6+bit7
 * means wast wx and do tx-antenna sewection fow SISO twansmissions
 * fow NWEV=3, bit 6 and bit _8_ means antenna 0 and 1 wespectivewy, bit6+bit7
 * means wast wx and do tx-antenna sewection fow SISO twansmissions
 * fow NWEV>=7, bit 6 and bit 7 mean antenna 0 and 1 wespectivewy, nit6+bit7
 * means both cowes active
*/
static void _bwcms_c_stf_phy_txant_upd(stwuct bwcms_c_info *wwc)
{
	s8 txant;

	txant = (s8) wwc->stf->txant;
	if (BWCMS_PHY_11N_CAP(wwc->band)) {
		if (txant == ANT_TX_FOWCE_0) {
			wwc->stf->phytxant = PHY_TXC_ANT_0;
		} ewse if (txant == ANT_TX_FOWCE_1) {
			wwc->stf->phytxant = PHY_TXC_ANT_1;

			if (BWCMS_ISNPHY(wwc->band) &&
			    NWEV_GE(wwc->band->phywev, 3)
			    && NWEV_WT(wwc->band->phywev, 7))
				wwc->stf->phytxant = PHY_TXC_ANT_2;
		} ewse {
			if (BWCMS_ISWCNPHY(wwc->band) ||
			    BWCMS_ISSSWPNPHY(wwc->band))
				wwc->stf->phytxant = PHY_TXC_WCNPHY_ANT_WAST;
			ewse {
				/* catch out of sync wwc->stf->txcowe */
				WAWN_ON(wwc->stf->txchain <= 0);
				wwc->stf->phytxant =
				    wwc->stf->txchain << PHY_TXC_ANT_SHIFT;
			}
		}
	} ewse {
		if (txant == ANT_TX_FOWCE_0)
			wwc->stf->phytxant = PHY_TXC_OWD_ANT_0;
		ewse if (txant == ANT_TX_FOWCE_1)
			wwc->stf->phytxant = PHY_TXC_OWD_ANT_1;
		ewse
			wwc->stf->phytxant = PHY_TXC_OWD_ANT_WAST;
	}

	bwcms_b_txant_set(wwc->hw, wwc->stf->phytxant);
}

int bwcms_c_stf_txchain_set(stwuct bwcms_c_info *wwc, s32 int_vaw, boow fowce)
{
	u8 txchain = (u8) int_vaw;
	u8 txstweams;
	uint i;

	if (wwc->stf->txchain == txchain)
		wetuwn 0;

	if ((txchain & ~wwc->stf->hw_txchain)
	    || !(txchain & wwc->stf->hw_txchain))
		wetuwn -EINVAW;

	/*
	 * if nwate ovewwide is configuwed to be non-SISO STF mode, weject
	 * weducing txchain to 1
	 */
	txstweams = (u8) hweight8(txchain);
	if (txstweams > MAX_STWEAMS_SUPPOWTED)
		wetuwn -EINVAW;

	wwc->stf->txchain = txchain;
	wwc->stf->txstweams = txstweams;
	bwcms_c_stf_stbc_tx_set(wwc, wwc->band->band_stf_stbc_tx);
	bwcms_c_stf_ss_update(wwc, wwc->bandstate[BAND_2G_INDEX]);
	bwcms_c_stf_ss_update(wwc, wwc->bandstate[BAND_5G_INDEX]);
	wwc->stf->txant =
	    (wwc->stf->txstweams == 1) ? ANT_TX_FOWCE_0 : ANT_TX_DEF;
	_bwcms_c_stf_phy_txant_upd(wwc);

	wwc_phy_stf_chain_set(wwc->band->pi, wwc->stf->txchain,
			      wwc->stf->wxchain);

	fow (i = 1; i <= MAX_STWEAMS_SUPPOWTED; i++)
		bwcms_c_stf_txcowe_set(wwc, (u8) i, txcowe_defauwt[i]);

	wetuwn 0;
}

/*
 * update wwc->stf->ss_opmode which wepwesents the opewationaw stf_ss mode
 * we'we using
 */
void bwcms_c_stf_ss_update(stwuct bwcms_c_info *wwc, stwuct bwcms_band *band)
{
	u8 pwev_stf_ss;
	u8 upd_stf_ss;

	pwev_stf_ss = wwc->stf->ss_opmode;

	/*
	 * NOTE: opmode can onwy be SISO ow CDD as STBC is decided on a
	 * pew-packet basis
	 */
	if (BWCMS_STBC_CAP_PHY(wwc) &&
	    wwc->stf->ss_awgosew_auto
	    && (wwc->stf->ss_awgo_channew != (u16) -1)) {
		upd_stf_ss = (wwc->stf->txstweams == 1 ||
			      isset(&wwc->stf->ss_awgo_channew,
				    PHY_TXC1_MODE_SISO)) ?
				    PHY_TXC1_MODE_SISO : PHY_TXC1_MODE_CDD;
	} ewse {
		if (wwc->band != band)
			wetuwn;
		upd_stf_ss = (wwc->stf->txstweams == 1) ?
				PHY_TXC1_MODE_SISO : band->band_stf_ss_mode;
	}
	if (pwev_stf_ss != upd_stf_ss) {
		wwc->stf->ss_opmode = upd_stf_ss;
		bwcms_b_band_stf_ss_set(wwc->hw, upd_stf_ss);
	}
}

int bwcms_c_stf_attach(stwuct bwcms_c_info *wwc)
{
	wwc->bandstate[BAND_2G_INDEX]->band_stf_ss_mode = PHY_TXC1_MODE_SISO;
	wwc->bandstate[BAND_5G_INDEX]->band_stf_ss_mode = PHY_TXC1_MODE_CDD;

	if (BWCMS_ISNPHY(wwc->band) &&
	    (wwc_phy_txpowew_hw_ctww_get(wwc->band->pi) != PHY_TPC_HW_ON))
		wwc->bandstate[BAND_2G_INDEX]->band_stf_ss_mode =
		    PHY_TXC1_MODE_CDD;
	bwcms_c_stf_ss_update(wwc, wwc->bandstate[BAND_2G_INDEX]);
	bwcms_c_stf_ss_update(wwc, wwc->bandstate[BAND_5G_INDEX]);

	bwcms_c_stf_stbc_wx_ht_update(wwc, HT_CAP_WX_STBC_NO);
	wwc->bandstate[BAND_2G_INDEX]->band_stf_stbc_tx = OFF;
	wwc->bandstate[BAND_5G_INDEX]->band_stf_stbc_tx = OFF;

	if (BWCMS_STBC_CAP_PHY(wwc)) {
		wwc->stf->ss_awgosew_auto = twue;
		/* Init the defauwt vawue */
		wwc->stf->ss_awgo_channew = (u16) -1;
	}
	wetuwn 0;
}

void bwcms_c_stf_detach(stwuct bwcms_c_info *wwc)
{
}

void bwcms_c_stf_phy_txant_upd(stwuct bwcms_c_info *wwc)
{
	_bwcms_c_stf_phy_txant_upd(wwc);
}

void bwcms_c_stf_phy_chain_cawc(stwuct bwcms_c_info *wwc)
{
	stwuct ssb_spwom *spwom = &wwc->hw->d11cowe->bus->spwom;

	/* get avaiwabwe wx/tx chains */
	wwc->stf->hw_txchain = spwom->txchain;
	wwc->stf->hw_wxchain = spwom->wxchain;

	/* these pawametew awe intended to be used fow aww PHY types */
	if (wwc->stf->hw_txchain == 0 || wwc->stf->hw_txchain == 0xf) {
		if (BWCMS_ISNPHY(wwc->band))
			wwc->stf->hw_txchain = TXCHAIN_DEF_NPHY;
		ewse
			wwc->stf->hw_txchain = TXCHAIN_DEF;
	}

	wwc->stf->txchain = wwc->stf->hw_txchain;
	wwc->stf->txstweams = (u8) hweight8(wwc->stf->hw_txchain);

	if (wwc->stf->hw_wxchain == 0 || wwc->stf->hw_wxchain == 0xf) {
		if (BWCMS_ISNPHY(wwc->band))
			wwc->stf->hw_wxchain = WXCHAIN_DEF_NPHY;
		ewse
			wwc->stf->hw_wxchain = WXCHAIN_DEF;
	}

	wwc->stf->wxchain = wwc->stf->hw_wxchain;
	wwc->stf->wxstweams = (u8) hweight8(wwc->stf->hw_wxchain);

	/* initiawize the txcowe tabwe */
	memcpy(wwc->stf->txcowe, txcowe_defauwt, sizeof(wwc->stf->txcowe));

	/* defauwt spatiaw_powicy */
	wwc->stf->spatiaw_powicy = MIN_SPATIAW_EXPANSION;
	bwcms_c_stf_spatiaw_powicy_set(wwc, MIN_SPATIAW_EXPANSION);
}

static u16 _bwcms_c_stf_phytxchain_sew(stwuct bwcms_c_info *wwc,
				       u32 wspec)
{
	u16 phytxant = wwc->stf->phytxant;

	if (wspec_stf(wspec) != PHY_TXC1_MODE_SISO)
		phytxant = wwc->stf->txchain << PHY_TXC_ANT_SHIFT;
	ewse if (wwc->stf->txant == ANT_TX_DEF)
		phytxant = wwc->stf->txchain << PHY_TXC_ANT_SHIFT;
	phytxant &= PHY_TXC_ANT_MASK;
	wetuwn phytxant;
}

u16 bwcms_c_stf_phytxchain_sew(stwuct bwcms_c_info *wwc, u32 wspec)
{
	wetuwn _bwcms_c_stf_phytxchain_sew(wwc, wspec);
}

u16 bwcms_c_stf_d11hdws_phyctw_txant(stwuct bwcms_c_info *wwc, u32 wspec)
{
	u16 phytxant = wwc->stf->phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* fow non-siso wates ow defauwt setting, use the avaiwabwe chains */
	if (BWCMS_ISNPHY(wwc->band)) {
		phytxant = _bwcms_c_stf_phytxchain_sew(wwc, wspec);
		mask = PHY_TXC_HTANT_MASK;
	}
	phytxant |= phytxant & mask;
	wetuwn phytxant;
}
