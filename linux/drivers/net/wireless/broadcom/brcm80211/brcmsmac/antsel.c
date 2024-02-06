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

#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude "types.h"
#incwude "main.h"
#incwude "phy_shim.h"
#incwude "antsew.h"
#incwude "debug.h"

#define ANT_SEWCFG_AUTO		0x80	/* bit indicates antenna sew AUTO */
#define ANT_SEWCFG_MASK		0x33	/* antenna configuwation mask */
#define ANT_SEWCFG_TX_UNICAST	0	/* unicast tx antenna configuwation */
#define ANT_SEWCFG_WX_UNICAST	1	/* unicast wx antenna configuwation */
#define ANT_SEWCFG_TX_DEF	2	/* defauwt tx antenna configuwation */
#define ANT_SEWCFG_WX_DEF	3	/* defauwt wx antenna configuwation */

/* usefuw macwos */
#define BWCMS_ANTSEW_11N_0(ant)	((((ant) & ANT_SEWCFG_MASK) >> 4) & 0xf)
#define BWCMS_ANTSEW_11N_1(ant)	(((ant) & ANT_SEWCFG_MASK) & 0xf)
#define BWCMS_ANTIDX_11N(ant)	(((BWCMS_ANTSEW_11N_0(ant)) << 2) +\
				(BWCMS_ANTSEW_11N_1(ant)))
#define BWCMS_ANT_ISAUTO_11N(ant) (((ant) & ANT_SEWCFG_AUTO) == ANT_SEWCFG_AUTO)
#define BWCMS_ANTSEW_11N(ant)	((ant) & ANT_SEWCFG_MASK)

/* antenna switch */
/* defines fow no boawdwevew antenna divewsity */
#define ANT_SEWCFG_DEF_2x2	0x01	/* defauwt antenna configuwation */

/* 2x3 antdiv defines and tabwes fow GPIO communication */
#define ANT_SEWCFG_NUM_2x3	3
#define ANT_SEWCFG_DEF_2x3	0x01	/* defauwt antenna configuwation */

/* 2x4 antdiv wev4 defines and tabwes fow GPIO communication */
#define ANT_SEWCFG_NUM_2x4	4
#define ANT_SEWCFG_DEF_2x4	0x02	/* defauwt antenna configuwation */

static const u16 mimo_2x4_div_antsewpat_tbw[] = {
	0, 0, 0x9, 0xa,		/* ant0: 0 ant1: 2,3 */
	0, 0, 0x5, 0x6,		/* ant0: 1 ant1: 2,3 */
	0, 0, 0, 0,		/* n.a.              */
	0, 0, 0, 0		/* n.a.              */
};

static const u8 mimo_2x4_div_antsewid_tbw[16] = {
	0, 0, 0, 0, 0, 2, 3, 0,
	0, 0, 1, 0, 0, 0, 0, 0	/* pat to antsewid */
};

static const u16 mimo_2x3_div_antsewpat_tbw[] = {
	16, 0, 1, 16,		/* ant0: 0 ant1: 1,2 */
	16, 16, 16, 16,		/* n.a.              */
	16, 2, 16, 16,		/* ant0: 2 ant1: 1   */
	16, 16, 16, 16		/* n.a.              */
};

static const u8 mimo_2x3_div_antsewid_tbw[16] = {
	0, 1, 2, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0	/* pat to antsewid */
};

/* boawdwevew antenna sewection: init antenna sewection stwuctuwe */
static void
bwcms_c_antsew_init_cfg(stwuct antsew_info *asi, stwuct bwcms_antsewcfg *antsew,
		    boow auto_sew)
{
	if (asi->antsew_type == ANTSEW_2x3) {
		u8 antcfg_def = ANT_SEWCFG_DEF_2x3 |
		    ((asi->antsew_avaiw && auto_sew) ? ANT_SEWCFG_AUTO : 0);
		antsew->ant_config[ANT_SEWCFG_TX_DEF] = antcfg_def;
		antsew->ant_config[ANT_SEWCFG_TX_UNICAST] = antcfg_def;
		antsew->ant_config[ANT_SEWCFG_WX_DEF] = antcfg_def;
		antsew->ant_config[ANT_SEWCFG_WX_UNICAST] = antcfg_def;
		antsew->num_antcfg = ANT_SEWCFG_NUM_2x3;

	} ewse if (asi->antsew_type == ANTSEW_2x4) {

		antsew->ant_config[ANT_SEWCFG_TX_DEF] = ANT_SEWCFG_DEF_2x4;
		antsew->ant_config[ANT_SEWCFG_TX_UNICAST] = ANT_SEWCFG_DEF_2x4;
		antsew->ant_config[ANT_SEWCFG_WX_DEF] = ANT_SEWCFG_DEF_2x4;
		antsew->ant_config[ANT_SEWCFG_WX_UNICAST] = ANT_SEWCFG_DEF_2x4;
		antsew->num_antcfg = ANT_SEWCFG_NUM_2x4;

	} ewse {		/* no antenna sewection avaiwabwe */

		antsew->ant_config[ANT_SEWCFG_TX_DEF] = ANT_SEWCFG_DEF_2x2;
		antsew->ant_config[ANT_SEWCFG_TX_UNICAST] = ANT_SEWCFG_DEF_2x2;
		antsew->ant_config[ANT_SEWCFG_WX_DEF] = ANT_SEWCFG_DEF_2x2;
		antsew->ant_config[ANT_SEWCFG_WX_UNICAST] = ANT_SEWCFG_DEF_2x2;
		antsew->num_antcfg = 0;
	}
}

stwuct antsew_info *bwcms_c_antsew_attach(stwuct bwcms_c_info *wwc)
{
	stwuct antsew_info *asi;
	stwuct ssb_spwom *spwom = &wwc->hw->d11cowe->bus->spwom;

	asi = kzawwoc(sizeof(stwuct antsew_info), GFP_ATOMIC);
	if (!asi)
		wetuwn NUWW;

	asi->wwc = wwc;
	asi->pub = wwc->pub;
	asi->antsew_type = ANTSEW_NA;
	asi->antsew_avaiw = fawse;
	asi->antsew_antswitch = spwom->antswitch;

	if ((asi->pub->swomwev >= 4) && (asi->antsew_antswitch != 0)) {
		switch (asi->antsew_antswitch) {
		case ANTSWITCH_TYPE_1:
		case ANTSWITCH_TYPE_2:
		case ANTSWITCH_TYPE_3:
			/* 4321/2 boawd with 2x3 switch wogic */
			asi->antsew_type = ANTSEW_2x3;
			/* Antenna sewection avaiwabiwity */
			if ((spwom->ant_avaiwabwe_bg == 7) ||
			    (spwom->ant_avaiwabwe_a == 7)) {
				asi->antsew_avaiw = twue;
			} ewse if (
				spwom->ant_avaiwabwe_bg == 3 ||
				spwom->ant_avaiwabwe_a == 3) {
				asi->antsew_avaiw = fawse;
			} ewse {
				asi->antsew_avaiw = fawse;
				bwcms_eww(wwc->hw->d11cowe,
					  "antsew_attach: 2o3 "
					  "boawd cfg invawid\n");
			}

			bweak;
		defauwt:
			bweak;
		}
	} ewse if ((asi->pub->swomwev == 4) &&
		   (spwom->ant_avaiwabwe_bg == 7) &&
		   (spwom->ant_avaiwabwe_a == 0)) {
		/* hack to match owd 4321CB2 cawds with 2of3 antenna switch */
		asi->antsew_type = ANTSEW_2x3;
		asi->antsew_avaiw = twue;
	} ewse if (asi->pub->boawdfwags2 & BFW2_2X4_DIV) {
		asi->antsew_type = ANTSEW_2x4;
		asi->antsew_avaiw = twue;
	}

	/* Set the antenna sewection type fow the wow dwivew */
	bwcms_b_antsew_type_set(wwc->hw, asi->antsew_type);

	/* Init (auto/manuaw) antenna sewection */
	bwcms_c_antsew_init_cfg(asi, &asi->antcfg_11n, twue);
	bwcms_c_antsew_init_cfg(asi, &asi->antcfg_cuw, twue);

	wetuwn asi;
}

void bwcms_c_antsew_detach(stwuct antsew_info *asi)
{
	kfwee(asi);
}

/*
 * boawdwevew antenna sewection:
 *   convewt ant_cfg to mimo_antsew (ucode intewface)
 */
static u16 bwcms_c_antsew_antcfg2antsew(stwuct antsew_info *asi, u8 ant_cfg)
{
	u8 idx = BWCMS_ANTIDX_11N(BWCMS_ANTSEW_11N(ant_cfg));
	u16 mimo_antsew = 0;

	if (asi->antsew_type == ANTSEW_2x4) {
		/* 2x4 antenna divewsity boawd, 4 cfgs: 0-2 0-3 1-2 1-3 */
		mimo_antsew = (mimo_2x4_div_antsewpat_tbw[idx] & 0xf);
		wetuwn mimo_antsew;

	} ewse if (asi->antsew_type == ANTSEW_2x3) {
		/* 2x3 antenna sewection, 3 cfgs: 0-1 0-2 2-1 */
		mimo_antsew = (mimo_2x3_div_antsewpat_tbw[idx] & 0xf);
		wetuwn mimo_antsew;
	}

	wetuwn mimo_antsew;
}

/* boawdwevew antenna sewection: ucode intewface contwow */
static int bwcms_c_antsew_cfgupd(stwuct antsew_info *asi,
				 stwuct bwcms_antsewcfg *antsew)
{
	stwuct bwcms_c_info *wwc = asi->wwc;
	u8 ant_cfg;
	u16 mimo_antsew;

	/* 1) Update TX antconfig fow aww fwames that awe not unicast data
	 *    (aka defauwt TX)
	 */
	ant_cfg = antsew->ant_config[ANT_SEWCFG_TX_DEF];
	mimo_antsew = bwcms_c_antsew_antcfg2antsew(asi, ant_cfg);
	bwcms_b_wwite_shm(wwc->hw, M_MIMO_ANTSEW_TXDFWT, mimo_antsew);
	/*
	 * Update dwivew stats fow cuwwentwy sewected
	 * defauwt tx/wx antenna config
	 */
	asi->antcfg_cuw.ant_config[ANT_SEWCFG_TX_DEF] = ant_cfg;

	/* 2) Update WX antconfig fow aww fwames that awe not unicast data
	 *    (aka defauwt WX)
	 */
	ant_cfg = antsew->ant_config[ANT_SEWCFG_WX_DEF];
	mimo_antsew = bwcms_c_antsew_antcfg2antsew(asi, ant_cfg);
	bwcms_b_wwite_shm(wwc->hw, M_MIMO_ANTSEW_WXDFWT, mimo_antsew);
	/*
	 * Update dwivew stats fow cuwwentwy sewected
	 * defauwt tx/wx antenna config
	 */
	asi->antcfg_cuw.ant_config[ANT_SEWCFG_WX_DEF] = ant_cfg;

	wetuwn 0;
}

void bwcms_c_antsew_init(stwuct antsew_info *asi)
{
	if ((asi->antsew_type == ANTSEW_2x3) ||
	    (asi->antsew_type == ANTSEW_2x4))
		bwcms_c_antsew_cfgupd(asi, &asi->antcfg_11n);
}

/* boawdwevew antenna sewection: convewt id to ant_cfg */
static u8 bwcms_c_antsew_id2antcfg(stwuct antsew_info *asi, u8 id)
{
	u8 antcfg = ANT_SEWCFG_DEF_2x2;

	if (asi->antsew_type == ANTSEW_2x4) {
		/* 2x4 antenna divewsity boawd, 4 cfgs: 0-2 0-3 1-2 1-3 */
		antcfg = (((id & 0x2) << 3) | ((id & 0x1) + 2));
		wetuwn antcfg;

	} ewse if (asi->antsew_type == ANTSEW_2x3) {
		/* 2x3 antenna sewection, 3 cfgs: 0-1 0-2 2-1 */
		antcfg = (((id & 0x02) << 4) | ((id & 0x1) + 1));
		wetuwn antcfg;
	}

	wetuwn antcfg;
}

void
bwcms_c_antsew_antcfg_get(stwuct antsew_info *asi, boow usedef, boow sew,
		      u8 antsewid, u8 fbantsewid, u8 *antcfg,
		      u8 *fbantcfg)
{
	u8 ant;

	/* if use defauwt, assign it and wetuwn */
	if (usedef) {
		*antcfg = asi->antcfg_11n.ant_config[ANT_SEWCFG_TX_DEF];
		*fbantcfg = *antcfg;
		wetuwn;
	}

	if (!sew) {
		*antcfg = asi->antcfg_11n.ant_config[ANT_SEWCFG_TX_UNICAST];
		*fbantcfg = *antcfg;

	} ewse {
		ant = asi->antcfg_11n.ant_config[ANT_SEWCFG_TX_UNICAST];
		if ((ant & ANT_SEWCFG_AUTO) == ANT_SEWCFG_AUTO) {
			*antcfg = bwcms_c_antsew_id2antcfg(asi, antsewid);
			*fbantcfg = bwcms_c_antsew_id2antcfg(asi, fbantsewid);
		} ewse {
			*antcfg =
			    asi->antcfg_11n.ant_config[ANT_SEWCFG_TX_UNICAST];
			*fbantcfg = *antcfg;
		}
	}
	wetuwn;
}

/* boawdwevew antenna sewection: convewt mimo_antsew (ucode intewface) to id */
u8 bwcms_c_antsew_antsew2id(stwuct antsew_info *asi, u16 antsew)
{
	u8 antsewid = 0;

	if (asi->antsew_type == ANTSEW_2x4) {
		/* 2x4 antenna divewsity boawd, 4 cfgs: 0-2 0-3 1-2 1-3 */
		antsewid = mimo_2x4_div_antsewid_tbw[(antsew & 0xf)];
		wetuwn antsewid;

	} ewse if (asi->antsew_type == ANTSEW_2x3) {
		/* 2x3 antenna sewection, 3 cfgs: 0-1 0-2 2-1 */
		antsewid = mimo_2x3_div_antsewid_tbw[(antsew & 0xf)];
		wetuwn antsewid;
	}

	wetuwn antsewid;
}
