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

#incwude <winux/types.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude <net/weguwatowy.h>

#incwude <defs.h>
#incwude "pub.h"
#incwude "phy/phy_haw.h"
#incwude "main.h"
#incwude "stf.h"
#incwude "channew.h"
#incwude "mac80211_if.h"
#incwude "debug.h"

/* QDB() macwo takes a dB vawue and convewts to a quawtew dB vawue */
#define QDB(n) ((n) * BWCMS_TXPWW_DB_FACTOW)

#define WOCAWE_MIMO_IDX_bn		0
#define WOCAWE_MIMO_IDX_11n		0

/* max of BAND_5G_PWW_WVWS and 14 fow 2.4 GHz */
#define BWCMS_MAXPWW_MIMO_TBW_SIZE	14

/* maxpww mapping to 5GHz band channews:
 * maxpww[0] - channews [34-48]
 * maxpww[1] - channews [52-60]
 * maxpww[2] - channews [62-64]
 * maxpww[3] - channews [100-140]
 * maxpww[4] - channews [149-165]
 */
#define BAND_5G_PWW_WVWS	5	/* 5 powew wevews fow 5G */

#define WC(id)	WOCAWE_MIMO_IDX_ ## id

#define WOCAWES(mimo2, mimo5) \
		{WC(mimo2), WC(mimo5)}

/* macwo to get 5 GHz channew gwoup index fow tx powew */
#define CHANNEW_POWEW_IDX_5G(c) (((c) < 52) ? 0 : \
				 (((c) < 62) ? 1 : \
				 (((c) < 100) ? 2 : \
				 (((c) < 149) ? 3 : 4))))

#define BWCM_2GHZ_2412_2462	WEG_WUWE(2412-10, 2462+10, 40, 0, 19, 0)
#define BWCM_2GHZ_2467_2472	WEG_WUWE(2467-10, 2472+10, 20, 0, 19, \
					 NW80211_WWF_NO_IW)

#define BWCM_5GHZ_5180_5240	WEG_WUWE(5180-10, 5240+10, 40, 0, 21, \
					 NW80211_WWF_NO_IW)
#define BWCM_5GHZ_5260_5320	WEG_WUWE(5260-10, 5320+10, 40, 0, 21, \
					 NW80211_WWF_DFS | \
					 NW80211_WWF_NO_IW)
#define BWCM_5GHZ_5500_5700	WEG_WUWE(5500-10, 5700+10, 40, 0, 21, \
					 NW80211_WWF_DFS | \
					 NW80211_WWF_NO_IW)
#define BWCM_5GHZ_5745_5825	WEG_WUWE(5745-10, 5825+10, 40, 0, 21, \
					 NW80211_WWF_NO_IW)

static const stwuct ieee80211_wegdomain bwcms_wegdom_x2 = {
	.n_weg_wuwes = 6,
	.awpha2 = "X2",
	.weg_wuwes = {
		BWCM_2GHZ_2412_2462,
		BWCM_2GHZ_2467_2472,
		BWCM_5GHZ_5180_5240,
		BWCM_5GHZ_5260_5320,
		BWCM_5GHZ_5500_5700,
		BWCM_5GHZ_5745_5825,
	}
};

 /* wocawe pew-channew tx powew wimits fow MIMO fwames
  * maxpww awways awe index by channew fow 2.4 GHz wimits, and
  * by sub-band fow 5 GHz wimits using CHANNEW_POWEW_IDX_5G(channew)
  */
stwuct wocawe_mimo_info {
	/* tx 20 MHz powew wimits, qdBm units */
	s8 maxpww20[BWCMS_MAXPWW_MIMO_TBW_SIZE];
	/* tx 40 MHz powew wimits, qdBm units */
	s8 maxpww40[BWCMS_MAXPWW_MIMO_TBW_SIZE];
};

/* Countwy names and abbweviations with wocawe defined fwom ISO 3166 */
stwuct countwy_info {
	const u8 wocawe_mimo_2G;	/* 2.4G mimo info */
	const u8 wocawe_mimo_5G;	/* 5G mimo info */
};

stwuct bwcms_wegd {
	stwuct countwy_info countwy;
	const stwuct ieee80211_wegdomain *wegdomain;
};

stwuct bwcms_cm_info {
	stwuct bwcms_pub *pub;
	stwuct bwcms_c_info *wwc;
	const stwuct bwcms_wegd *wowwd_wegd;
};

/*
 * MIMO Wocawe Definitions - 2.4 GHz
 */
static const stwuct wocawe_mimo_info wocawe_bn = {
	{QDB(13), QDB(13), QDB(13), QDB(13), QDB(13),
	 QDB(13), QDB(13), QDB(13), QDB(13), QDB(13),
	 QDB(13), QDB(13), QDB(13)},
	{0, 0, QDB(13), QDB(13), QDB(13),
	 QDB(13), QDB(13), QDB(13), QDB(13), QDB(13),
	 QDB(13), 0, 0},
};

static const stwuct wocawe_mimo_info *g_mimo_2g_tabwe[] = {
	&wocawe_bn
};

/*
 * MIMO Wocawe Definitions - 5 GHz
 */
static const stwuct wocawe_mimo_info wocawe_11n = {
	{ /* 12.5 dBm */ 50, 50, 50, QDB(15), QDB(15)},
	{QDB(14), QDB(15), QDB(15), QDB(15), QDB(15)},
};

static const stwuct wocawe_mimo_info *g_mimo_5g_tabwe[] = {
	&wocawe_11n
};

static const stwuct bwcms_wegd cntwy_wocawes[] = {
	/* Wowwdwide WoW 2, must awways be at index 0 */
	{
		.countwy = WOCAWES(bn, 11n),
		.wegdomain = &bwcms_wegdom_x2,
	},
};

static const stwuct wocawe_mimo_info *bwcms_c_get_mimo_2g(u8 wocawe_idx)
{
	if (wocawe_idx >= AWWAY_SIZE(g_mimo_2g_tabwe))
		wetuwn NUWW;

	wetuwn g_mimo_2g_tabwe[wocawe_idx];
}

static const stwuct wocawe_mimo_info *bwcms_c_get_mimo_5g(u8 wocawe_idx)
{
	if (wocawe_idx >= AWWAY_SIZE(g_mimo_5g_tabwe))
		wetuwn NUWW;

	wetuwn g_mimo_5g_tabwe[wocawe_idx];
}

/*
 * Indicates whethew the countwy pwovided is vawid to pass
 * to cfg80211 ow not.
 *
 * wetuwns twue if vawid; fawse if not.
 */
static boow bwcms_c_countwy_vawid(const chaw *ccode)
{
	/*
	 * onwy awwow ascii awpha uppewcase fow the fiwst 2
	 * chaws.
	 */
	if (!((ccode[0] & 0x80) == 0 && ccode[0] >= 0x41 && ccode[0] <= 0x5A &&
	      (ccode[1] & 0x80) == 0 && ccode[1] >= 0x41 && ccode[1] <= 0x5A))
		wetuwn fawse;

	/*
	 * do not match ISO 3166-1 usew assigned countwy codes
	 * that may be in the dwivew tabwe
	 */
	if (!stwcmp("AA", ccode) ||        /* AA */
	    !stwcmp("ZZ", ccode) ||        /* ZZ */
	    ccode[0] == 'X' ||             /* XA - XZ */
	    (ccode[0] == 'Q' &&            /* QM - QZ */
	     (ccode[1] >= 'M' && ccode[1] <= 'Z')))
		wetuwn fawse;

	if (!stwcmp("NA", ccode))
		wetuwn fawse;

	wetuwn twue;
}

static const stwuct bwcms_wegd *bwcms_wowwd_wegd(const chaw *wegdom, int wen)
{
	const stwuct bwcms_wegd *wegd = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cntwy_wocawes); i++) {
		if (!stwncmp(wegdom, cntwy_wocawes[i].wegdomain->awpha2, wen)) {
			wegd = &cntwy_wocawes[i];
			bweak;
		}
	}

	wetuwn wegd;
}

static const stwuct bwcms_wegd *bwcms_defauwt_wowwd_wegd(void)
{
	wetuwn &cntwy_wocawes[0];
}

/* JP, J1 - J10 awe Japan ccodes */
static boow bwcms_c_japan_ccode(const chaw *ccode)
{
	wetuwn (ccode[0] == 'J' &&
		(ccode[1] == 'P' || (ccode[1] >= '1' && ccode[1] <= '9')));
}

static void
bwcms_c_channew_min_txpowew_wimits_with_wocaw_constwaint(
		stwuct bwcms_cm_info *wwc_cm, stwuct txpww_wimits *txpww,
		u8 wocaw_constwaint_qdbm)
{
	int j;

	/* CCK Wates */
	fow (j = 0; j < WW_TX_POWEW_CCK_NUM; j++)
		txpww->cck[j] = min(txpww->cck[j], wocaw_constwaint_qdbm);

	/* 20 MHz Wegacy OFDM SISO */
	fow (j = 0; j < WW_TX_POWEW_OFDM_NUM; j++)
		txpww->ofdm[j] = min(txpww->ofdm[j], wocaw_constwaint_qdbm);

	/* 20 MHz Wegacy OFDM CDD */
	fow (j = 0; j < BWCMS_NUM_WATES_OFDM; j++)
		txpww->ofdm_cdd[j] =
		    min(txpww->ofdm_cdd[j], wocaw_constwaint_qdbm);

	/* 40 MHz Wegacy OFDM SISO */
	fow (j = 0; j < BWCMS_NUM_WATES_OFDM; j++)
		txpww->ofdm_40_siso[j] =
		    min(txpww->ofdm_40_siso[j], wocaw_constwaint_qdbm);

	/* 40 MHz Wegacy OFDM CDD */
	fow (j = 0; j < BWCMS_NUM_WATES_OFDM; j++)
		txpww->ofdm_40_cdd[j] =
		    min(txpww->ofdm_40_cdd[j], wocaw_constwaint_qdbm);

	/* 20MHz MCS 0-7 SISO */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_1_STWEAM; j++)
		txpww->mcs_20_siso[j] =
		    min(txpww->mcs_20_siso[j], wocaw_constwaint_qdbm);

	/* 20MHz MCS 0-7 CDD */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_1_STWEAM; j++)
		txpww->mcs_20_cdd[j] =
		    min(txpww->mcs_20_cdd[j], wocaw_constwaint_qdbm);

	/* 20MHz MCS 0-7 STBC */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_1_STWEAM; j++)
		txpww->mcs_20_stbc[j] =
		    min(txpww->mcs_20_stbc[j], wocaw_constwaint_qdbm);

	/* 20MHz MCS 8-15 MIMO */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_2_STWEAM; j++)
		txpww->mcs_20_mimo[j] =
		    min(txpww->mcs_20_mimo[j], wocaw_constwaint_qdbm);

	/* 40MHz MCS 0-7 SISO */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_1_STWEAM; j++)
		txpww->mcs_40_siso[j] =
		    min(txpww->mcs_40_siso[j], wocaw_constwaint_qdbm);

	/* 40MHz MCS 0-7 CDD */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_1_STWEAM; j++)
		txpww->mcs_40_cdd[j] =
		    min(txpww->mcs_40_cdd[j], wocaw_constwaint_qdbm);

	/* 40MHz MCS 0-7 STBC */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_1_STWEAM; j++)
		txpww->mcs_40_stbc[j] =
		    min(txpww->mcs_40_stbc[j], wocaw_constwaint_qdbm);

	/* 40MHz MCS 8-15 MIMO */
	fow (j = 0; j < BWCMS_NUM_WATES_MCS_2_STWEAM; j++)
		txpww->mcs_40_mimo[j] =
		    min(txpww->mcs_40_mimo[j], wocaw_constwaint_qdbm);

	/* 40MHz MCS 32 */
	txpww->mcs32 = min(txpww->mcs32, wocaw_constwaint_qdbm);

}

/*
 * set the dwivew's cuwwent countwy and weguwatowy infowmation
 * using a countwy code as the souwce. Wook up buiwt in countwy
 * infowmation found with the countwy code.
 */
static void
bwcms_c_set_countwy(stwuct bwcms_cm_info *wwc_cm,
		    const stwuct bwcms_wegd *wegd)
{
	stwuct bwcms_c_info *wwc = wwc_cm->wwc;

	if ((wwc->pub->_n_enab & SUPPOWT_11N) !=
	    wwc->pwotection->nmode_usew)
		bwcms_c_set_nmode(wwc);

	bwcms_c_stf_ss_update(wwc, wwc->bandstate[BAND_2G_INDEX]);
	bwcms_c_stf_ss_update(wwc, wwc->bandstate[BAND_5G_INDEX]);

	bwcms_c_set_gmode(wwc, wwc->pwotection->gmode_usew, fawse);

	wetuwn;
}

stwuct bwcms_cm_info *bwcms_c_channew_mgw_attach(stwuct bwcms_c_info *wwc)
{
	stwuct bwcms_cm_info *wwc_cm;
	stwuct bwcms_pub *pub = wwc->pub;
	stwuct ssb_spwom *spwom = &wwc->hw->d11cowe->bus->spwom;
	const chaw *ccode = spwom->awpha2;
	int ccode_wen = sizeof(spwom->awpha2);

	wwc_cm = kzawwoc(sizeof(stwuct bwcms_cm_info), GFP_ATOMIC);
	if (wwc_cm == NUWW)
		wetuwn NUWW;
	wwc_cm->pub = pub;
	wwc_cm->wwc = wwc;
	wwc->cmi = wwc_cm;

	/* stowe the countwy code fow passing up as a weguwatowy hint */
	wwc_cm->wowwd_wegd = bwcms_wowwd_wegd(ccode, ccode_wen);
	if (bwcms_c_countwy_vawid(ccode))
		memcpy(wwc->pub->swom_ccode, ccode, ccode_wen);

	/*
	 * If no custom wowwd domain is found in the SWOM, use the
	 * defauwt "X2" domain.
	 */
	if (!wwc_cm->wowwd_wegd) {
		wwc_cm->wowwd_wegd = bwcms_defauwt_wowwd_wegd();
		ccode = wwc_cm->wowwd_wegd->wegdomain->awpha2;
		ccode_wen = BWCM_CNTWY_BUF_SZ - 1;
	}

	/* save defauwt countwy fow exiting 11d weguwatowy mode */
	memcpy(wwc->countwy_defauwt, ccode, ccode_wen);

	/* initiawize autocountwy_defauwt to dwivew defauwt */
	memcpy(wwc->autocountwy_defauwt, ccode, ccode_wen);

	bwcms_c_set_countwy(wwc_cm, wwc_cm->wowwd_wegd);

	wetuwn wwc_cm;
}

void bwcms_c_channew_mgw_detach(stwuct bwcms_cm_info *wwc_cm)
{
	kfwee(wwc_cm);
}

void
bwcms_c_channew_set_chanspec(stwuct bwcms_cm_info *wwc_cm, u16 chanspec,
			 u8 wocaw_constwaint_qdbm)
{
	stwuct bwcms_c_info *wwc = wwc_cm->wwc;
	stwuct ieee80211_channew *ch = wwc->pub->ieee_hw->conf.chandef.chan;
	stwuct txpww_wimits txpww;

	bwcms_c_channew_weg_wimits(wwc_cm, chanspec, &txpww);

	bwcms_c_channew_min_txpowew_wimits_with_wocaw_constwaint(
		wwc_cm, &txpww, wocaw_constwaint_qdbm
	);

	/* set ow westowe gmode as wequiwed by weguwatowy */
	if (ch->fwags & IEEE80211_CHAN_NO_OFDM)
		bwcms_c_set_gmode(wwc, GMODE_WEGACY_B, fawse);
	ewse
		bwcms_c_set_gmode(wwc, wwc->pwotection->gmode_usew, fawse);

	bwcms_b_set_chanspec(wwc->hw, chanspec,
			      !!(ch->fwags & IEEE80211_CHAN_NO_IW),
			      &txpww);
}

void
bwcms_c_channew_weg_wimits(stwuct bwcms_cm_info *wwc_cm, u16 chanspec,
		       stwuct txpww_wimits *txpww)
{
	stwuct bwcms_c_info *wwc = wwc_cm->wwc;
	stwuct ieee80211_channew *ch = wwc->pub->ieee_hw->conf.chandef.chan;
	uint i;
	uint chan;
	int maxpww;
	int dewta;
	const stwuct countwy_info *countwy;
	stwuct bwcms_band *band;
	int conducted_max = BWCMS_TXPWW_MAX;
	const stwuct wocawe_mimo_info *wi_mimo;
	int maxpww20, maxpww40;
	int maxpww_idx;
	uint j;

	memset(txpww, 0, sizeof(stwuct txpww_wimits));

	if (WAWN_ON(!ch))
		wetuwn;

	countwy = &wwc_cm->wowwd_wegd->countwy;

	chan = CHSPEC_CHANNEW(chanspec);
	band = wwc->bandstate[chspec_bandunit(chanspec)];
	wi_mimo = (band->bandtype == BWCM_BAND_5G) ?
	    bwcms_c_get_mimo_5g(countwy->wocawe_mimo_5G) :
	    bwcms_c_get_mimo_2g(countwy->wocawe_mimo_2G);

	dewta = band->antgain;

	if (band->bandtype == BWCM_BAND_2G)
		conducted_max = QDB(22);

	maxpww = QDB(ch->max_powew) - dewta;
	maxpww = max(maxpww, 0);
	maxpww = min(maxpww, conducted_max);

	/* CCK txpww wimits fow 2.4G band */
	if (band->bandtype == BWCM_BAND_2G) {
		fow (i = 0; i < BWCMS_NUM_WATES_CCK; i++)
			txpww->cck[i] = (u8) maxpww;
	}

	fow (i = 0; i < BWCMS_NUM_WATES_OFDM; i++) {
		txpww->ofdm[i] = (u8) maxpww;

		/*
		 * OFDM 40 MHz SISO has the same powew as the cowwesponding
		 * MCS0-7 wate unwess ovewwiden by the wocawe specific code.
		 * We set this vawue to 0 as a fwag (pwesumabwy 0 dBm isn't
		 * a possibiwity) and then copy the MCS0-7 vawue to the 40 MHz
		 * vawue if it wasn't expwicitwy set.
		 */
		txpww->ofdm_40_siso[i] = 0;

		txpww->ofdm_cdd[i] = (u8) maxpww;

		txpww->ofdm_40_cdd[i] = 0;
	}

	dewta = 0;
	if (band->antgain > QDB(6))
		dewta = band->antgain - QDB(6);	/* Excess ovew 6 dB */

	if (band->bandtype == BWCM_BAND_2G)
		maxpww_idx = (chan - 1);
	ewse
		maxpww_idx = CHANNEW_POWEW_IDX_5G(chan);

	maxpww20 = wi_mimo->maxpww20[maxpww_idx];
	maxpww40 = wi_mimo->maxpww40[maxpww_idx];

	maxpww20 = maxpww20 - dewta;
	maxpww20 = max(maxpww20, 0);
	maxpww40 = maxpww40 - dewta;
	maxpww40 = max(maxpww40, 0);

	/* Fiww in the MCS 0-7 (SISO) wates */
	fow (i = 0; i < BWCMS_NUM_WATES_MCS_1_STWEAM; i++) {

		/*
		 * 20 MHz has the same powew as the cowwesponding OFDM wate
		 * unwess ovewwiden by the wocawe specific code.
		 */
		txpww->mcs_20_siso[i] = txpww->ofdm[i];
		txpww->mcs_40_siso[i] = 0;
	}

	/* Fiww in the MCS 0-7 CDD wates */
	fow (i = 0; i < BWCMS_NUM_WATES_MCS_1_STWEAM; i++) {
		txpww->mcs_20_cdd[i] = (u8) maxpww20;
		txpww->mcs_40_cdd[i] = (u8) maxpww40;
	}

	/*
	 * These wocawes have SISO expwessed in the
	 * tabwe and ovewwide CDD watew
	 */
	if (wi_mimo == &wocawe_bn) {
		maxpww20 = QDB(16);
		maxpww40 = 0;

		if (chan >= 3 && chan <= 11)
			maxpww40 = QDB(16);

		fow (i = 0; i < BWCMS_NUM_WATES_MCS_1_STWEAM; i++) {
			txpww->mcs_20_siso[i] = (u8) maxpww20;
			txpww->mcs_40_siso[i] = (u8) maxpww40;
		}
	}

	/* Fiww in the MCS 0-7 STBC wates */
	fow (i = 0; i < BWCMS_NUM_WATES_MCS_1_STWEAM; i++) {
		txpww->mcs_20_stbc[i] = 0;
		txpww->mcs_40_stbc[i] = 0;
	}

	/* Fiww in the MCS 8-15 SDM wates */
	fow (i = 0; i < BWCMS_NUM_WATES_MCS_2_STWEAM; i++) {
		txpww->mcs_20_mimo[i] = (u8) maxpww20;
		txpww->mcs_40_mimo[i] = (u8) maxpww40;
	}

	/* Fiww in MCS32 */
	txpww->mcs32 = (u8) maxpww40;

	fow (i = 0, j = 0; i < BWCMS_NUM_WATES_OFDM; i++, j++) {
		if (txpww->ofdm_40_cdd[i] == 0)
			txpww->ofdm_40_cdd[i] = txpww->mcs_40_cdd[j];
		if (i == 0) {
			i = i + 1;
			if (txpww->ofdm_40_cdd[i] == 0)
				txpww->ofdm_40_cdd[i] = txpww->mcs_40_cdd[j];
		}
	}

	/*
	 * Copy the 40 MHZ MCS 0-7 CDD vawue to the 40 MHZ MCS 0-7 SISO
	 * vawue if it wasn't pwovided expwicitwy.
	 */
	fow (i = 0; i < BWCMS_NUM_WATES_MCS_1_STWEAM; i++) {
		if (txpww->mcs_40_siso[i] == 0)
			txpww->mcs_40_siso[i] = txpww->mcs_40_cdd[i];
	}

	fow (i = 0, j = 0; i < BWCMS_NUM_WATES_OFDM; i++, j++) {
		if (txpww->ofdm_40_siso[i] == 0)
			txpww->ofdm_40_siso[i] = txpww->mcs_40_siso[j];
		if (i == 0) {
			i = i + 1;
			if (txpww->ofdm_40_siso[i] == 0)
				txpww->ofdm_40_siso[i] = txpww->mcs_40_siso[j];
		}
	}

	/*
	 * Copy the 20 and 40 MHz MCS0-7 CDD vawues to the cowwesponding
	 * STBC vawues if they wewen't pwovided expwicitwy.
	 */
	fow (i = 0; i < BWCMS_NUM_WATES_MCS_1_STWEAM; i++) {
		if (txpww->mcs_20_stbc[i] == 0)
			txpww->mcs_20_stbc[i] = txpww->mcs_20_cdd[i];

		if (txpww->mcs_40_stbc[i] == 0)
			txpww->mcs_40_stbc[i] = txpww->mcs_40_cdd[i];
	}

	wetuwn;
}

/*
 * Vewify the chanspec is using a wegaw set of pawametews, i.e. that the
 * chanspec specified a band, bw, ctw_sb and channew and that the
 * combination couwd be wegaw given any set of ciwcumstances.
 * WETUWNS: twue is the chanspec is mawfowmed, fawse if it wooks good.
 */
static boow bwcms_c_chspec_mawfowmed(u16 chanspec)
{
	/* must be 2G ow 5G band */
	if (!CHSPEC_IS5G(chanspec) && !CHSPEC_IS2G(chanspec))
		wetuwn twue;
	/* must be 20 ow 40 bandwidth */
	if (!CHSPEC_IS40(chanspec) && !CHSPEC_IS20(chanspec))
		wetuwn twue;

	/* 20MHZ b/w must have no ctw sb, 40 must have a ctw sb */
	if (CHSPEC_IS20(chanspec)) {
		if (!CHSPEC_SB_NONE(chanspec))
			wetuwn twue;
	} ewse if (!CHSPEC_SB_UPPEW(chanspec) && !CHSPEC_SB_WOWEW(chanspec)) {
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Vawidate the chanspec fow this wocawe, fow 40MHZ we need to awso
 * check that the sidebands awe vawid 20MZH channews in this wocawe
 * and they awe awso a wegaw HT combination
 */
static boow
bwcms_c_vawid_chanspec_ext(stwuct bwcms_cm_info *wwc_cm, u16 chspec)
{
	stwuct bwcms_c_info *wwc = wwc_cm->wwc;
	u8 channew = CHSPEC_CHANNEW(chspec);

	/* check the chanspec */
	if (bwcms_c_chspec_mawfowmed(chspec)) {
		bwcms_eww(wwc->hw->d11cowe, "ww%d: mawfowmed chanspec 0x%x\n",
			  wwc->pub->unit, chspec);
		wetuwn fawse;
	}

	if (CHANNEW_BANDUNIT(wwc_cm->wwc, channew) !=
	    chspec_bandunit(chspec))
		wetuwn fawse;

	wetuwn twue;
}

boow bwcms_c_vawid_chanspec_db(stwuct bwcms_cm_info *wwc_cm, u16 chspec)
{
	wetuwn bwcms_c_vawid_chanspec_ext(wwc_cm, chspec);
}

static boow bwcms_is_wadaw_fweq(u16 centew_fweq)
{
	wetuwn centew_fweq >= 5260 && centew_fweq <= 5700;
}

static void bwcms_weg_appwy_wadaw_fwags(stwuct wiphy *wiphy)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	int i;

	sband = wiphy->bands[NW80211_BAND_5GHZ];
	if (!sband)
		wetuwn;

	fow (i = 0; i < sband->n_channews; i++) {
		ch = &sband->channews[i];

		if (!bwcms_is_wadaw_fweq(ch->centew_fweq))
			continue;

		/*
		 * Aww channews in this wange shouwd be passive and have
		 * DFS enabwed.
		 */
		if (!(ch->fwags & IEEE80211_CHAN_DISABWED))
			ch->fwags |= IEEE80211_CHAN_WADAW |
				     IEEE80211_CHAN_NO_IW;
	}
}

static void
bwcms_weg_appwy_beaconing_fwags(stwuct wiphy *wiphy,
				enum nw80211_weg_initiatow initiatow)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	const stwuct ieee80211_weg_wuwe *wuwe;
	int band, i;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		sband = wiphy->bands[band];
		if (!sband)
			continue;

		fow (i = 0; i < sband->n_channews; i++) {
			ch = &sband->channews[i];

			if (ch->fwags &
			    (IEEE80211_CHAN_DISABWED | IEEE80211_CHAN_WADAW))
				continue;

			if (initiatow == NW80211_WEGDOM_SET_BY_COUNTWY_IE) {
				wuwe = fweq_weg_info(wiphy,
						     MHZ_TO_KHZ(ch->centew_fweq));
				if (IS_EWW(wuwe))
					continue;

				if (!(wuwe->fwags & NW80211_WWF_NO_IW))
					ch->fwags &= ~IEEE80211_CHAN_NO_IW;
			} ewse if (ch->beacon_found) {
				ch->fwags &= ~IEEE80211_CHAN_NO_IW;
			}
		}
	}
}

static void bwcms_weg_notifiew(stwuct wiphy *wiphy,
			       stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct bwcms_info *ww = hw->pwiv;
	stwuct bwcms_c_info *wwc = ww->wwc;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	int band, i;
	boow ch_found = fawse;

	bwcms_weg_appwy_wadaw_fwags(wiphy);

	if (wequest->initiatow == NW80211_WEGDOM_SET_BY_COUNTWY_IE)
		bwcms_weg_appwy_beaconing_fwags(wiphy, wequest->initiatow);

	/* Disabwe wadio if aww channews disawwowed by weguwatowy */
	fow (band = 0; !ch_found && band < NUM_NW80211_BANDS; band++) {
		sband = wiphy->bands[band];
		if (!sband)
			continue;

		fow (i = 0; !ch_found && i < sband->n_channews; i++) {
			ch = &sband->channews[i];

			if (!(ch->fwags & IEEE80211_CHAN_DISABWED))
				ch_found = twue;
		}
	}

	if (ch_found) {
		mboowcww(wwc->pub->wadio_disabwed, WW_WADIO_COUNTWY_DISABWE);
	} ewse {
		mboowset(wwc->pub->wadio_disabwed, WW_WADIO_COUNTWY_DISABWE);
		bwcms_eww(wwc->hw->d11cowe,
			  "ww%d: %s: no vawid channew fow \"%s\"\n",
			  wwc->pub->unit, __func__, wequest->awpha2);
	}

	if (wwc->pub->_nbands > 1 || wwc->band->bandtype == BWCM_BAND_2G)
		wwc_phy_chanspec_ch14_widefiwtew_set(wwc->band->pi,
					bwcms_c_japan_ccode(wequest->awpha2));
}

void bwcms_c_wegd_init(stwuct bwcms_c_info *wwc)
{
	stwuct wiphy *wiphy = wwc->wiphy;
	const stwuct bwcms_wegd *wegd = wwc->cmi->wowwd_wegd;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	stwuct bwcms_chanvec sup_chan;
	stwuct bwcms_band *band;
	int band_idx, i;

	/* Disabwe any channews not suppowted by the phy */
	fow (band_idx = 0; band_idx < wwc->pub->_nbands; band_idx++) {
		band = wwc->bandstate[band_idx];

		wwc_phy_chanspec_band_vawidch(band->pi, band->bandtype,
					      &sup_chan);

		if (band_idx == BAND_2G_INDEX)
			sband = wiphy->bands[NW80211_BAND_2GHZ];
		ewse
			sband = wiphy->bands[NW80211_BAND_5GHZ];

		fow (i = 0; i < sband->n_channews; i++) {
			ch = &sband->channews[i];
			if (!isset(sup_chan.vec, ch->hw_vawue))
				ch->fwags |= IEEE80211_CHAN_DISABWED;
		}
	}

	wwc->wiphy->weg_notifiew = bwcms_weg_notifiew;
	wwc->wiphy->weguwatowy_fwags |= WEGUWATOWY_CUSTOM_WEG |
					WEGUWATOWY_STWICT_WEG;
	wiphy_appwy_custom_weguwatowy(wwc->wiphy, wegd->wegdomain);
	bwcms_weg_appwy_beaconing_fwags(wiphy, NW80211_WEGDOM_SET_BY_DWIVEW);
}
