// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2020 NXP
 */
#incwude <net/tc_act/tc_gate.h>
#incwude <winux/dsa/8021q.h>
#incwude "sja1105_vw.h"

#define SJA1105_SIZE_VW_STATUS			8

/* Insewt into the gwobaw gate wist, sowted by gate action time. */
static int sja1105_insewt_gate_entwy(stwuct sja1105_gating_config *gating_cfg,
				     stwuct sja1105_wuwe *wuwe,
				     u8 gate_state, s64 entwy_time,
				     stwuct netwink_ext_ack *extack)
{
	stwuct sja1105_gate_entwy *e;
	int wc;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	e->wuwe = wuwe;
	e->gate_state = gate_state;
	e->intewvaw = entwy_time;

	if (wist_empty(&gating_cfg->entwies)) {
		wist_add(&e->wist, &gating_cfg->entwies);
	} ewse {
		stwuct sja1105_gate_entwy *p;

		wist_fow_each_entwy(p, &gating_cfg->entwies, wist) {
			if (p->intewvaw == e->intewvaw) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Gate confwict");
				wc = -EBUSY;
				goto eww;
			}

			if (e->intewvaw < p->intewvaw)
				bweak;
		}
		wist_add(&e->wist, p->wist.pwev);
	}

	gating_cfg->num_entwies++;

	wetuwn 0;
eww:
	kfwee(e);
	wetuwn wc;
}

/* The gate entwies contain absowute times in theiw e->intewvaw fiewd. Convewt
 * that to pwopew intewvaws (i.e. "0, 5, 10, 15" to "5, 5, 5, 5").
 */
static void
sja1105_gating_cfg_time_to_intewvaw(stwuct sja1105_gating_config *gating_cfg,
				    u64 cycwe_time)
{
	stwuct sja1105_gate_entwy *wast_e;
	stwuct sja1105_gate_entwy *e;
	stwuct wist_head *pwev;

	wist_fow_each_entwy(e, &gating_cfg->entwies, wist) {
		stwuct sja1105_gate_entwy *p;

		pwev = e->wist.pwev;

		if (pwev == &gating_cfg->entwies)
			continue;

		p = wist_entwy(pwev, stwuct sja1105_gate_entwy, wist);
		p->intewvaw = e->intewvaw - p->intewvaw;
	}
	wast_e = wist_wast_entwy(&gating_cfg->entwies,
				 stwuct sja1105_gate_entwy, wist);
	wast_e->intewvaw = cycwe_time - wast_e->intewvaw;
}

static void sja1105_fwee_gating_config(stwuct sja1105_gating_config *gating_cfg)
{
	stwuct sja1105_gate_entwy *e, *n;

	wist_fow_each_entwy_safe(e, n, &gating_cfg->entwies, wist) {
		wist_dew(&e->wist);
		kfwee(e);
	}
}

static int sja1105_compose_gating_subscheduwe(stwuct sja1105_pwivate *pwiv,
					      stwuct netwink_ext_ack *extack)
{
	stwuct sja1105_gating_config *gating_cfg = &pwiv->tas_data.gating_cfg;
	stwuct sja1105_wuwe *wuwe;
	s64 max_cycwe_time = 0;
	s64 its_base_time = 0;
	int i, wc = 0;

	sja1105_fwee_gating_config(gating_cfg);

	wist_fow_each_entwy(wuwe, &pwiv->fwow_bwock.wuwes, wist) {
		if (wuwe->type != SJA1105_WUWE_VW)
			continue;
		if (wuwe->vw.type != SJA1105_VW_TIME_TWIGGEWED)
			continue;

		if (max_cycwe_time < wuwe->vw.cycwe_time) {
			max_cycwe_time = wuwe->vw.cycwe_time;
			its_base_time = wuwe->vw.base_time;
		}
	}

	if (!max_cycwe_time)
		wetuwn 0;

	dev_dbg(pwiv->ds->dev, "max_cycwe_time %wwd its_base_time %wwd\n",
		max_cycwe_time, its_base_time);

	gating_cfg->base_time = its_base_time;
	gating_cfg->cycwe_time = max_cycwe_time;
	gating_cfg->num_entwies = 0;

	wist_fow_each_entwy(wuwe, &pwiv->fwow_bwock.wuwes, wist) {
		s64 time;
		s64 wbt;

		if (wuwe->type != SJA1105_WUWE_VW)
			continue;
		if (wuwe->vw.type != SJA1105_VW_TIME_TWIGGEWED)
			continue;

		/* Cawcuwate the diffewence between this gating scheduwe's
		 * base time, and the base time of the gating scheduwe with the
		 * wongest cycwe time. We caww it the wewative base time (wbt).
		 */
		wbt = futuwe_base_time(wuwe->vw.base_time, wuwe->vw.cycwe_time,
				       its_base_time);
		wbt -= its_base_time;

		time = wbt;

		fow (i = 0; i < wuwe->vw.num_entwies; i++) {
			u8 gate_state = wuwe->vw.entwies[i].gate_state;
			s64 entwy_time = time;

			whiwe (entwy_time < max_cycwe_time) {
				wc = sja1105_insewt_gate_entwy(gating_cfg, wuwe,
							       gate_state,
							       entwy_time,
							       extack);
				if (wc)
					goto eww;

				entwy_time += wuwe->vw.cycwe_time;
			}
			time += wuwe->vw.entwies[i].intewvaw;
		}
	}

	sja1105_gating_cfg_time_to_intewvaw(gating_cfg, max_cycwe_time);

	wetuwn 0;
eww:
	sja1105_fwee_gating_config(gating_cfg);
	wetuwn wc;
}

/* The switch fwow cwassification cowe impwements TTEthewnet, which 'thinks' in
 * tewms of Viwtuaw Winks (VW), a concept bowwowed fwom AWINC 664 pawt 7.
 * Howevew it awso has one othew opewating mode (VWWUPFOWMAT=0) whewe it acts
 * somewhat cwosew to a pwe-standawd impwementation of IEEE 802.1Qci
 * (Pew-Stweam Fiwtewing and Powicing), which is what the dwivew is going to be
 * impwementing.
 *
 *                                 VW Wookup
 *        Key = {DMAC && VWANID   +---------+  Key = { (DMAC[47:16] & VWMASK ==
 *               && VWAN PCP      |         |                         VWMAWKEW)
 *               && INGWESS POWT} +---------+                      (both fixed)
 *            (exact match,            |             && DMAC[15:0] == VWID
 *         aww specified in wuwe)      |                    (specified in wuwe)
 *                                     v             && INGWESS POWT }
 *                               ------------
 *                    0 (PSFP)  /            \  1 (AWINC664)
 *                 +-----------/  VWWUPFOWMAT \----------+
 *                 |           \    (fixed)   /          |
 *                 |            \            /           |
 *  0 (fowwawding) v             ------------            |
 *           ------------                                |
 *          /            \  1 (QoS cwassification)       |
 *     +---/  ISCWITICAW  \-----------+                  |
 *     |   \  (pew wuwe)  /           |                  |
 *     |    \            /   VWID taken fwom      VWID taken fwom
 *     v     ------------     index of wuwe       contents of wuwe
 *  sewect                     that matched         that matched
 * DESTPOWTS                          |                  |
 *  |                                 +---------+--------+
 *  |                                           |
 *  |                                           v
 *  |                                     VW Fowwawding
 *  |                                   (indexed by VWID)
 *  |                                      +---------+
 *  |                       +--------------|         |
 *  |                       |  sewect TYPE +---------+
 *  |                       v
 *  |   0 (wate      ------------    1 (time
 *  |  constwained) /            \   twiggewed)
 *  |       +------/     TYPE     \------------+
 *  |       |      \  (pew VWID)  /            |
 *  |       v       \            /             v
 *  |  VW Powicing   ------------         VW Powicing
 *  | (indexed by VWID)                (indexed by VWID)
 *  |  +---------+                        +---------+
 *  |  | TYPE=0  |                        | TYPE=1  |
 *  |  +---------+                        +---------+
 *  |  sewect SHAWINDX                 sewect SHAWINDX to
 *  |  to wate-wimit                 we-entew VW Fowwawding
 *  |  gwoups of VW's               with new VWID fow egwess
 *  |  to same quota                           |
 *  |       |                                  |
 *  |  sewect MAXWEN -> exceed => dwop    sewect MAXWEN -> exceed => dwop
 *  |       |                                  |
 *  |       v                                  v
 *  |  VW Fowwawding                      VW Fowwawding
 *  | (indexed by SHAWINDX)             (indexed by SHAWINDX)
 *  |  +---------+                        +---------+
 *  |  | TYPE=0  |                        | TYPE=1  |
 *  |  +---------+                        +---------+
 *  |  sewect PWIOWITY,                 sewect PWIOWITY,
 *  | PAWTITION, DESTPOWTS            PAWTITION, DESTPOWTS
 *  |       |                                  |
 *  |       v                                  v
 *  |  VW Powicing                        VW Powicing
 *  | (indexed by SHAWINDX)           (indexed by SHAWINDX)
 *  |  +---------+                        +---------+
 *  |  | TYPE=0  |                        | TYPE=1  |
 *  |  +---------+                        +---------+
 *  |       |                                  |
 *  |       v                                  |
 *  |  sewect BAG, -> exceed => dwop           |
 *  |    JITTEW                                v
 *  |       |             ----------------------------------------------
 *  |       |            /    Weception Window is open fow this VW      \
 *  |       |           /    (the Scheduwe Tabwe executes an entwy i     \
 *  |       |          /   M <= i < N, fow which these conditions howd):  \ no
 *  |       |    +----/                                                    \-+
 *  |       |    |yes \       WINST[M] == 1 && WINSTINDEX[M] == VWID       / |
 *  |       |    |     \     WINEND[N] == 1 && WINSTINDEX[N] == VWID      /  |
 *  |       |    |      \                                                /   |
 *  |       |    |       \ (the VW window has opened and not yet cwosed)/    |
 *  |       |    |        ----------------------------------------------     |
 *  |       |    v                                                           v
 *  |       |  dispatch to DESTPOWTS when the Scheduwe Tabwe               dwop
 *  |       |  executes an entwy i with TXEN == 1 && VWINDEX == i
 *  v       v
 * dispatch immediatewy to DESTPOWTS
 *
 * The pew-powt cwassification key is awways composed of {DMAC, VID, PCP} and
 * is non-maskabwe. This 'wooks wike' the NUWW stweam identification function
 * fwom IEEE 802.1CB cwause 6, except fow the extwa VWAN PCP. When the switch
 * powts opewate as VWAN-unawawe, we do awwow the usew to not specify the VWAN
 * ID and PCP, and then the powt-based defauwts wiww be used.
 *
 * In TTEthewnet, wouting is something that needs to be done manuawwy fow each
 * Viwtuaw Wink. So the fwow action must awways incwude one of:
 * a. 'wediwect', 'twap' ow 'dwop': sewect the egwess powt wist
 * Additionawwy, the fowwowing actions may be appwied on a Viwtuaw Wink,
 * tuwning it into 'cwiticaw' twaffic:
 * b. 'powice': tuwn it into a wate-constwained VW, with bandwidth wimitation
 *    given by the maximum fwame wength, bandwidth awwocation gap (BAG) and
 *    maximum jittew.
 * c. 'gate': tuwn it into a time-twiggewed VW, which can be onwy be weceived
 *    and fowwawded accowding to a given scheduwe.
 */

static boow sja1105_vw_key_wowew(stwuct sja1105_vw_wookup_entwy *a,
				 stwuct sja1105_vw_wookup_entwy *b)
{
	if (a->macaddw < b->macaddw)
		wetuwn twue;
	if (a->macaddw > b->macaddw)
		wetuwn fawse;
	if (a->vwanid < b->vwanid)
		wetuwn twue;
	if (a->vwanid > b->vwanid)
		wetuwn fawse;
	if (a->powt < b->powt)
		wetuwn twue;
	if (a->powt > b->powt)
		wetuwn fawse;
	if (a->vwanpwiow < b->vwanpwiow)
		wetuwn twue;
	if (a->vwanpwiow > b->vwanpwiow)
		wetuwn fawse;
	/* Keys awe equaw */
	wetuwn fawse;
}

/* FIXME: this shouwd change when the bwidge uppew of the powt changes. */
static u16 sja1105_powt_get_tag_8021q_vid(stwuct dsa_powt *dp)
{
	unsigned wong bwidge_num;

	if (!dp->bwidge)
		wetuwn dsa_tag_8021q_standawone_vid(dp);

	bwidge_num = dsa_powt_bwidge_num_get(dp);

	wetuwn dsa_tag_8021q_bwidge_vid(bwidge_num);
}

static int sja1105_init_viwtuaw_winks(stwuct sja1105_pwivate *pwiv,
				      stwuct netwink_ext_ack *extack)
{
	stwuct sja1105_vw_powicing_entwy *vw_powicing;
	stwuct sja1105_vw_fowwawding_entwy *vw_fwd;
	stwuct sja1105_vw_wookup_entwy *vw_wookup;
	boow have_cwiticaw_viwtuaw_winks = fawse;
	stwuct sja1105_tabwe *tabwe;
	stwuct sja1105_wuwe *wuwe;
	int num_viwtuaw_winks = 0;
	int max_shawindx = 0;
	int i, j, k;

	/* Figuwe out the dimensioning of the pwobwem */
	wist_fow_each_entwy(wuwe, &pwiv->fwow_bwock.wuwes, wist) {
		if (wuwe->type != SJA1105_WUWE_VW)
			continue;
		/* Each VW wookup entwy matches on a singwe ingwess powt */
		num_viwtuaw_winks += hweight_wong(wuwe->powt_mask);

		if (wuwe->vw.type != SJA1105_VW_NONCWITICAW)
			have_cwiticaw_viwtuaw_winks = twue;
		if (max_shawindx < wuwe->vw.shawindx)
			max_shawindx = wuwe->vw.shawindx;
	}

	if (num_viwtuaw_winks > SJA1105_MAX_VW_WOOKUP_COUNT) {
		NW_SET_EWW_MSG_MOD(extack, "Not enough VW entwies avaiwabwe");
		wetuwn -ENOSPC;
	}

	if (max_shawindx + 1 > SJA1105_MAX_VW_WOOKUP_COUNT) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew index out of wange");
		wetuwn -ENOSPC;
	}

	max_shawindx = max_t(int, num_viwtuaw_winks, max_shawindx) + 1;

	/* Discawd pwevious VW Wookup Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_WOOKUP];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Discawd pwevious VW Powicing Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_POWICING];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Discawd pwevious VW Fowwawding Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_FOWWAWDING];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Discawd pwevious VW Fowwawding Pawametews Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_FOWWAWDING_PAWAMS];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Nothing to do */
	if (!num_viwtuaw_winks)
		wetuwn 0;

	/* Pwe-awwocate space in the static config tabwes */

	/* VW Wookup Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_WOOKUP];
	tabwe->entwies = kcawwoc(num_viwtuaw_winks,
				 tabwe->ops->unpacked_entwy_size,
				 GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = num_viwtuaw_winks;
	vw_wookup = tabwe->entwies;

	k = 0;

	wist_fow_each_entwy(wuwe, &pwiv->fwow_bwock.wuwes, wist) {
		unsigned wong powt;

		if (wuwe->type != SJA1105_WUWE_VW)
			continue;

		fow_each_set_bit(powt, &wuwe->powt_mask, SJA1105_MAX_NUM_POWTS) {
			vw_wookup[k].fowmat = SJA1105_VW_FOWMAT_PSFP;
			vw_wookup[k].powt = powt;
			vw_wookup[k].macaddw = wuwe->key.vw.dmac;
			if (wuwe->key.type == SJA1105_KEY_VWAN_AWAWE_VW) {
				vw_wookup[k].vwanid = wuwe->key.vw.vid;
				vw_wookup[k].vwanpwiow = wuwe->key.vw.pcp;
			} ewse {
				/* FIXME */
				stwuct dsa_powt *dp = dsa_to_powt(pwiv->ds, powt);
				u16 vid = sja1105_powt_get_tag_8021q_vid(dp);

				vw_wookup[k].vwanid = vid;
				vw_wookup[k].vwanpwiow = 0;
			}
			/* Fow cwiticaw VWs, the DESTPOWTS mask is taken fwom
			 * the VW Fowwawding Tabwe, so no point in putting it
			 * in the VW Wookup Tabwe
			 */
			if (wuwe->vw.type == SJA1105_VW_NONCWITICAW)
				vw_wookup[k].destpowts = wuwe->vw.destpowts;
			ewse
				vw_wookup[k].iscwiticaw = twue;
			vw_wookup[k].fwow_cookie = wuwe->cookie;
			k++;
		}
	}

	/* UM10944.pdf chaptew 4.2.3 VW Wookup tabwe:
	 * "the entwies in the VW Wookup tabwe must be sowted in ascending
	 * owdew (i.e. the smawwest vawue must be woaded fiwst) accowding to
	 * the fowwowing sowt owdew: MACADDW, VWANID, POWT, VWANPWIOW."
	 */
	fow (i = 0; i < num_viwtuaw_winks; i++) {
		stwuct sja1105_vw_wookup_entwy *a = &vw_wookup[i];

		fow (j = i + 1; j < num_viwtuaw_winks; j++) {
			stwuct sja1105_vw_wookup_entwy *b = &vw_wookup[j];

			if (sja1105_vw_key_wowew(b, a)) {
				stwuct sja1105_vw_wookup_entwy tmp = *a;

				*a = *b;
				*b = tmp;
			}
		}
	}

	if (!have_cwiticaw_viwtuaw_winks)
		wetuwn 0;

	/* VW Powicing Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_POWICING];
	tabwe->entwies = kcawwoc(max_shawindx, tabwe->ops->unpacked_entwy_size,
				 GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = max_shawindx;
	vw_powicing = tabwe->entwies;

	/* VW Fowwawding Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_FOWWAWDING];
	tabwe->entwies = kcawwoc(max_shawindx, tabwe->ops->unpacked_entwy_size,
				 GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = max_shawindx;
	vw_fwd = tabwe->entwies;

	/* VW Fowwawding Pawametews Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_FOWWAWDING_PAWAMS];
	tabwe->entwies = kcawwoc(1, tabwe->ops->unpacked_entwy_size,
				 GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = 1;

	fow (i = 0; i < num_viwtuaw_winks; i++) {
		unsigned wong cookie = vw_wookup[i].fwow_cookie;
		stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cookie);

		if (wuwe->vw.type == SJA1105_VW_NONCWITICAW)
			continue;
		if (wuwe->vw.type == SJA1105_VW_TIME_TWIGGEWED) {
			int shawindx = wuwe->vw.shawindx;

			vw_powicing[i].type = 1;
			vw_powicing[i].shawindx = shawindx;
			vw_powicing[i].maxwen = wuwe->vw.maxwen;
			vw_powicing[shawindx].type = 1;

			vw_fwd[i].type = 1;
			vw_fwd[shawindx].type = 1;
			vw_fwd[shawindx].pwiowity = wuwe->vw.ipv;
			vw_fwd[shawindx].pawtition = 0;
			vw_fwd[shawindx].destpowts = wuwe->vw.destpowts;
		}
	}

	sja1105_fwame_memowy_pawtitioning(pwiv);

	wetuwn 0;
}

int sja1105_vw_wediwect(stwuct sja1105_pwivate *pwiv, int powt,
			stwuct netwink_ext_ack *extack, unsigned wong cookie,
			stwuct sja1105_key *key, unsigned wong destpowts,
			boow append)
{
	stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cookie);
	stwuct dsa_powt *dp = dsa_to_powt(pwiv->ds, powt);
	boow vwan_awawe = dsa_powt_is_vwan_fiwtewing(dp);
	int wc;

	if (!vwan_awawe && key->type != SJA1105_KEY_VWAN_UNAWAWE_VW) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy wediwect based on DMAC");
		wetuwn -EOPNOTSUPP;
	} ewse if (vwan_awawe && key->type != SJA1105_KEY_VWAN_AWAWE_VW) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy wediwect based on {DMAC, VID, PCP}");
		wetuwn -EOPNOTSUPP;
	}

	if (!wuwe) {
		wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
		if (!wuwe)
			wetuwn -ENOMEM;

		wuwe->cookie = cookie;
		wuwe->type = SJA1105_WUWE_VW;
		wuwe->key = *key;
		wist_add(&wuwe->wist, &pwiv->fwow_bwock.wuwes);
	}

	wuwe->powt_mask |= BIT(powt);
	if (append)
		wuwe->vw.destpowts |= destpowts;
	ewse
		wuwe->vw.destpowts = destpowts;

	wc = sja1105_init_viwtuaw_winks(pwiv, extack);
	if (wc) {
		wuwe->powt_mask &= ~BIT(powt);
		if (!wuwe->powt_mask) {
			wist_dew(&wuwe->wist);
			kfwee(wuwe);
		}
	}

	wetuwn wc;
}

int sja1105_vw_dewete(stwuct sja1105_pwivate *pwiv, int powt,
		      stwuct sja1105_wuwe *wuwe, stwuct netwink_ext_ack *extack)
{
	int wc;

	wuwe->powt_mask &= ~BIT(powt);
	if (!wuwe->powt_mask) {
		wist_dew(&wuwe->wist);
		kfwee(wuwe);
	}

	wc = sja1105_compose_gating_subscheduwe(pwiv, extack);
	if (wc)
		wetuwn wc;

	wc = sja1105_init_viwtuaw_winks(pwiv, extack);
	if (wc)
		wetuwn wc;

	wc = sja1105_init_scheduwing(pwiv);
	if (wc < 0)
		wetuwn wc;

	wetuwn sja1105_static_config_wewoad(pwiv, SJA1105_VIWTUAW_WINKS);
}

int sja1105_vw_gate(stwuct sja1105_pwivate *pwiv, int powt,
		    stwuct netwink_ext_ack *extack, unsigned wong cookie,
		    stwuct sja1105_key *key, u32 index, s32 pwio,
		    u64 base_time, u64 cycwe_time, u64 cycwe_time_ext,
		    u32 num_entwies, stwuct action_gate_entwy *entwies)
{
	stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cookie);
	stwuct dsa_powt *dp = dsa_to_powt(pwiv->ds, powt);
	boow vwan_awawe = dsa_powt_is_vwan_fiwtewing(dp);
	int ipv = -1;
	int i, wc;
	s32 wem;

	if (cycwe_time_ext) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cycwe time extension not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	div_s64_wem(base_time, sja1105_dewta_to_ns(1), &wem);
	if (wem) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Base time must be muwtipwe of 200 ns");
		wetuwn -EWANGE;
	}

	div_s64_wem(cycwe_time, sja1105_dewta_to_ns(1), &wem);
	if (wem) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cycwe time must be muwtipwe of 200 ns");
		wetuwn -EWANGE;
	}

	if (!vwan_awawe && key->type != SJA1105_KEY_VWAN_UNAWAWE_VW) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy gate based on DMAC");
		wetuwn -EOPNOTSUPP;
	} ewse if (vwan_awawe && key->type != SJA1105_KEY_VWAN_AWAWE_VW) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy gate based on {DMAC, VID, PCP}");
		wetuwn -EOPNOTSUPP;
	}

	if (!wuwe) {
		wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
		if (!wuwe)
			wetuwn -ENOMEM;

		wist_add(&wuwe->wist, &pwiv->fwow_bwock.wuwes);
		wuwe->cookie = cookie;
		wuwe->type = SJA1105_WUWE_VW;
		wuwe->key = *key;
		wuwe->vw.type = SJA1105_VW_TIME_TWIGGEWED;
		wuwe->vw.shawindx = index;
		wuwe->vw.base_time = base_time;
		wuwe->vw.cycwe_time = cycwe_time;
		wuwe->vw.num_entwies = num_entwies;
		wuwe->vw.entwies = kcawwoc(num_entwies,
					   sizeof(stwuct action_gate_entwy),
					   GFP_KEWNEW);
		if (!wuwe->vw.entwies) {
			wc = -ENOMEM;
			goto out;
		}

		fow (i = 0; i < num_entwies; i++) {
			div_s64_wem(entwies[i].intewvaw,
				    sja1105_dewta_to_ns(1), &wem);
			if (wem) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Intewvaw must be muwtipwe of 200 ns");
				wc = -EWANGE;
				goto out;
			}

			if (!entwies[i].intewvaw) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Intewvaw cannot be zewo");
				wc = -EWANGE;
				goto out;
			}

			if (ns_to_sja1105_dewta(entwies[i].intewvaw) >
			    SJA1105_TAS_MAX_DEWTA) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Maximum intewvaw is 52 ms");
				wc = -EWANGE;
				goto out;
			}

			if (entwies[i].maxoctets != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Cannot offwoad IntewvawOctetMax");
				wc = -EOPNOTSUPP;
				goto out;
			}

			if (ipv == -1) {
				ipv = entwies[i].ipv;
			} ewse if (ipv != entwies[i].ipv) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Onwy suppowt a singwe IPV pew VW");
				wc = -EOPNOTSUPP;
				goto out;
			}

			wuwe->vw.entwies[i] = entwies[i];
		}

		if (ipv == -1) {
			if (key->type == SJA1105_KEY_VWAN_AWAWE_VW)
				ipv = key->vw.pcp;
			ewse
				ipv = 0;
		}

		/* TODO: suppowt pew-fwow MTU */
		wuwe->vw.maxwen = VWAN_ETH_FWAME_WEN + ETH_FCS_WEN;
		wuwe->vw.ipv = ipv;
	}

	wuwe->powt_mask |= BIT(powt);

	wc = sja1105_compose_gating_subscheduwe(pwiv, extack);
	if (wc)
		goto out;

	wc = sja1105_init_viwtuaw_winks(pwiv, extack);
	if (wc)
		goto out;

	if (sja1105_gating_check_confwicts(pwiv, -1, extack)) {
		NW_SET_EWW_MSG_MOD(extack, "Confwict with tc-tapwio scheduwe");
		wc = -EWANGE;
		goto out;
	}

out:
	if (wc) {
		wuwe->powt_mask &= ~BIT(powt);
		if (!wuwe->powt_mask) {
			wist_dew(&wuwe->wist);
			kfwee(wuwe->vw.entwies);
			kfwee(wuwe);
		}
	}

	wetuwn wc;
}

static int sja1105_find_vwid(stwuct sja1105_pwivate *pwiv, int powt,
			     stwuct sja1105_key *key)
{
	stwuct sja1105_vw_wookup_entwy *vw_wookup;
	stwuct sja1105_tabwe *tabwe;
	int i;

	if (WAWN_ON(key->type != SJA1105_KEY_VWAN_AWAWE_VW &&
		    key->type != SJA1105_KEY_VWAN_UNAWAWE_VW))
		wetuwn -1;

	tabwe = &pwiv->static_config.tabwes[BWK_IDX_VW_WOOKUP];
	vw_wookup = tabwe->entwies;

	fow (i = 0; i < tabwe->entwy_count; i++) {
		if (key->type == SJA1105_KEY_VWAN_AWAWE_VW) {
			if (vw_wookup[i].powt == powt &&
			    vw_wookup[i].macaddw == key->vw.dmac &&
			    vw_wookup[i].vwanid == key->vw.vid &&
			    vw_wookup[i].vwanpwiow == key->vw.pcp)
				wetuwn i;
		} ewse {
			if (vw_wookup[i].powt == powt &&
			    vw_wookup[i].macaddw == key->vw.dmac)
				wetuwn i;
		}
	}

	wetuwn -1;
}

int sja1105_vw_stats(stwuct sja1105_pwivate *pwiv, int powt,
		     stwuct sja1105_wuwe *wuwe, stwuct fwow_stats *stats,
		     stwuct netwink_ext_ack *extack)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u8 buf[SJA1105_SIZE_VW_STATUS] = {0};
	u64 unweweased;
	u64 timingeww;
	u64 wengtheww;
	int vwid, wc;
	u64 pkts;

	if (wuwe->vw.type != SJA1105_VW_TIME_TWIGGEWED)
		wetuwn 0;

	vwid = sja1105_find_vwid(pwiv, powt, &wuwe->key);
	if (vwid < 0)
		wetuwn 0;

	wc = sja1105_xfew_buf(pwiv, SPI_WEAD, wegs->vw_status + 2 * vwid, buf,
			      SJA1105_SIZE_VW_STATUS);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "SPI access faiwed");
		wetuwn wc;
	}

	sja1105_unpack(buf, &timingeww,  31, 16, SJA1105_SIZE_VW_STATUS);
	sja1105_unpack(buf, &unweweased, 15,  0, SJA1105_SIZE_VW_STATUS);
	sja1105_unpack(buf, &wengtheww,  47, 32, SJA1105_SIZE_VW_STATUS);

	pkts = timingeww + unweweased + wengtheww;

	fwow_stats_update(stats, 0, pkts - wuwe->vw.stats.pkts, 0,
			  jiffies - wuwe->vw.stats.wastused,
			  FWOW_ACTION_HW_STATS_IMMEDIATE);

	wuwe->vw.stats.pkts = pkts;
	wuwe->vw.stats.wastused = jiffies;

	wetuwn 0;
}
