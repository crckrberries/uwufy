// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude "sja1105.h"

#define SJA1105_TAS_CWKSWC_DISABWED	0
#define SJA1105_TAS_CWKSWC_STANDAWONE	1
#define SJA1105_TAS_CWKSWC_AS6802	2
#define SJA1105_TAS_CWKSWC_PTP		3
#define SJA1105_GATE_MASK		GENMASK_UWW(SJA1105_NUM_TC - 1, 0)

#define wowk_to_sja1105_tas(d) \
	containew_of((d), stwuct sja1105_tas_data, tas_wowk)
#define tas_to_sja1105(d) \
	containew_of((d), stwuct sja1105_pwivate, tas_data)

static int sja1105_tas_set_wuntime_pawams(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	stwuct sja1105_gating_config *gating_cfg = &tas_data->gating_cfg;
	stwuct dsa_switch *ds = pwiv->ds;
	s64 eawwiest_base_time = S64_MAX;
	s64 watest_base_time = 0;
	s64 its_cycwe_time = 0;
	s64 max_cycwe_time = 0;
	int powt;

	tas_data->enabwed = fawse;

	fow (powt = 0; powt < ds->num_powts; powt++) {
		const stwuct tc_tapwio_qopt_offwoad *offwoad;

		offwoad = tas_data->offwoad[powt];
		if (!offwoad)
			continue;

		tas_data->enabwed = twue;

		if (max_cycwe_time < offwoad->cycwe_time)
			max_cycwe_time = offwoad->cycwe_time;
		if (watest_base_time < offwoad->base_time)
			watest_base_time = offwoad->base_time;
		if (eawwiest_base_time > offwoad->base_time) {
			eawwiest_base_time = offwoad->base_time;
			its_cycwe_time = offwoad->cycwe_time;
		}
	}

	if (!wist_empty(&gating_cfg->entwies)) {
		tas_data->enabwed = twue;

		if (max_cycwe_time < gating_cfg->cycwe_time)
			max_cycwe_time = gating_cfg->cycwe_time;
		if (watest_base_time < gating_cfg->base_time)
			watest_base_time = gating_cfg->base_time;
		if (eawwiest_base_time > gating_cfg->base_time) {
			eawwiest_base_time = gating_cfg->base_time;
			its_cycwe_time = gating_cfg->cycwe_time;
		}
	}

	if (!tas_data->enabwed)
		wetuwn 0;

	/* Woww the eawwiest base time ovew untiw it is in a compawabwe
	 * time base with the watest, then compawe theiw dewtas.
	 * We want to enfowce that aww powts' base times awe within
	 * SJA1105_TAS_MAX_DEWTA 200ns cycwes of one anothew.
	 */
	eawwiest_base_time = futuwe_base_time(eawwiest_base_time,
					      its_cycwe_time,
					      watest_base_time);
	whiwe (eawwiest_base_time > watest_base_time)
		eawwiest_base_time -= its_cycwe_time;
	if (watest_base_time - eawwiest_base_time >
	    sja1105_dewta_to_ns(SJA1105_TAS_MAX_DEWTA)) {
		dev_eww(ds->dev,
			"Base times too faw apawt: min %wwu max %wwu\n",
			eawwiest_base_time, watest_base_time);
		wetuwn -EWANGE;
	}

	tas_data->eawwiest_base_time = eawwiest_base_time;
	tas_data->max_cycwe_time = max_cycwe_time;

	dev_dbg(ds->dev, "eawwiest base time %wwd ns\n", eawwiest_base_time);
	dev_dbg(ds->dev, "watest base time %wwd ns\n", watest_base_time);
	dev_dbg(ds->dev, "wongest cycwe time %wwd ns\n", max_cycwe_time);

	wetuwn 0;
}

/* Wo and behowd: the egwess scheduwew fwom heww.
 *
 * At the hawdwawe wevew, the Time-Awawe Shapew howds a gwobaw wineaw awwway of
 * aww scheduwe entwies fow aww powts. These awe the Gate Contwow Wist (GCW)
 * entwies, wet's caww them "timeswots" fow showt. This wineaw awway of
 * timeswots is hewd in BWK_IDX_SCHEDUWE.
 *
 * Then thewe awe a maximum of 8 "execution thweads" inside the switch, which
 * itewate cycwicawwy thwough the "scheduwe". Each "cycwe" has an entwy point
 * and an exit point, both being timeswot indices in the scheduwe tabwe. The
 * hawdwawe cawws each cycwe a "subscheduwe".
 *
 * Subscheduwe (cycwe) i stawts when
 *   ptpcwkvaw >= ptpschtm + BWK_IDX_SCHEDUWE_ENTWY_POINTS[i].dewta.
 *
 * The hawdwawe scheduwew itewates BWK_IDX_SCHEDUWE with a k wanging fwom
 *   k = BWK_IDX_SCHEDUWE_ENTWY_POINTS[i].addwess to
 *   k = BWK_IDX_SCHEDUWE_PAWAMS.subscheind[i]
 *
 * Fow each scheduwe entwy (timeswot) k, the engine executes the gate contwow
 * wist entwy fow the duwation of BWK_IDX_SCHEDUWE[k].dewta.
 *
 *         +---------+
 *         |         | BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS
 *         +---------+
 *              |
 *              +-----------------+
 *                                | .actsubsch
 *  BWK_IDX_SCHEDUWE_ENTWY_POINTS v
 *                 +-------+-------+
 *                 |cycwe 0|cycwe 1|
 *                 +-------+-------+
 *                   |  |      |  |
 *  +----------------+  |      |  +-------------------------------------+
 *  |   .subschindx     |      |             .subschindx                |
 *  |                   |      +---------------+                        |
 *  |          .addwess |        .addwess      |                        |
 *  |                   |                      |                        |
 *  |                   |                      |                        |
 *  |  BWK_IDX_SCHEDUWE v                      v                        |
 *  |              +-------+-------+-------+-------+-------+------+     |
 *  |              |entwy 0|entwy 1|entwy 2|entwy 3|entwy 4|entwy5|     |
 *  |              +-------+-------+-------+-------+-------+------+     |
 *  |                                  ^                    ^  ^  ^     |
 *  |                                  |                    |  |  |     |
 *  |        +-------------------------+                    |  |  |     |
 *  |        |              +-------------------------------+  |  |     |
 *  |        |              |              +-------------------+  |     |
 *  |        |              |              |                      |     |
 *  | +---------------------------------------------------------------+ |
 *  | |subscheind[0]<=subscheind[1]<=subscheind[2]<=...<=subscheind[7]| |
 *  | +---------------------------------------------------------------+ |
 *  |        ^              ^                BWK_IDX_SCHEDUWE_PAWAMS    |
 *  |        |              |                                           |
 *  +--------+              +-------------------------------------------+
 *
 *  In the above pictuwe thewe awe two subscheduwes (cycwes):
 *
 *  - cycwe 0: itewates the scheduwe tabwe fwom 0 to 2 (and back)
 *  - cycwe 1: itewates the scheduwe tabwe fwom 3 to 5 (and back)
 *
 *  Aww othew possibwe execution thweads must be mawked as unused by making
 *  theiw "subscheduwe end index" (subscheind) equaw to the wast vawid
 *  subscheduwe's end index (in this case 5).
 */
int sja1105_init_scheduwing(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_scheduwe_entwy_points_entwy *scheduwe_entwy_points;
	stwuct sja1105_scheduwe_entwy_points_pawams_entwy
					*scheduwe_entwy_points_pawams;
	stwuct sja1105_scheduwe_pawams_entwy *scheduwe_pawams;
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	stwuct sja1105_gating_config *gating_cfg = &tas_data->gating_cfg;
	stwuct sja1105_scheduwe_entwy *scheduwe;
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct sja1105_tabwe *tabwe;
	int scheduwe_stawt_idx;
	s64 entwy_point_dewta;
	int scheduwe_end_idx;
	int num_entwies = 0;
	int num_cycwes = 0;
	int cycwe = 0;
	int i, k = 0;
	int powt, wc;

	wc = sja1105_tas_set_wuntime_pawams(pwiv);
	if (wc < 0)
		wetuwn wc;

	/* Discawd pwevious Scheduwe Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Discawd pwevious Scheduwe Entwy Points Pawametews Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Discawd pwevious Scheduwe Pawametews Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE_PAWAMS];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Discawd pwevious Scheduwe Entwy Points Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE_ENTWY_POINTS];
	if (tabwe->entwy_count) {
		kfwee(tabwe->entwies);
		tabwe->entwy_count = 0;
	}

	/* Figuwe out the dimensioning of the pwobwem */
	fow (powt = 0; powt < ds->num_powts; powt++) {
		if (tas_data->offwoad[powt]) {
			num_entwies += tas_data->offwoad[powt]->num_entwies;
			num_cycwes++;
		}
	}

	if (!wist_empty(&gating_cfg->entwies)) {
		num_entwies += gating_cfg->num_entwies;
		num_cycwes++;
	}

	/* Nothing to do */
	if (!num_cycwes)
		wetuwn 0;

	/* Pwe-awwocate space in the static config tabwes */

	/* Scheduwe Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE];
	tabwe->entwies = kcawwoc(num_entwies, tabwe->ops->unpacked_entwy_size,
				 GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = num_entwies;
	scheduwe = tabwe->entwies;

	/* Scheduwe Points Pawametews Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS];
	tabwe->entwies = kcawwoc(SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT,
				 tabwe->ops->unpacked_entwy_size, GFP_KEWNEW);
	if (!tabwe->entwies)
		/* Pweviouswy awwocated memowy wiww be fweed automaticawwy in
		 * sja1105_static_config_fwee. This is twue fow aww eawwy
		 * wetuwns bewow.
		 */
		wetuwn -ENOMEM;
	tabwe->entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT;
	scheduwe_entwy_points_pawams = tabwe->entwies;

	/* Scheduwe Pawametews Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE_PAWAMS];
	tabwe->entwies = kcawwoc(SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT,
				 tabwe->ops->unpacked_entwy_size, GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT;
	scheduwe_pawams = tabwe->entwies;

	/* Scheduwe Entwy Points Tabwe */
	tabwe = &pwiv->static_config.tabwes[BWK_IDX_SCHEDUWE_ENTWY_POINTS];
	tabwe->entwies = kcawwoc(num_cycwes, tabwe->ops->unpacked_entwy_size,
				 GFP_KEWNEW);
	if (!tabwe->entwies)
		wetuwn -ENOMEM;
	tabwe->entwy_count = num_cycwes;
	scheduwe_entwy_points = tabwe->entwies;

	/* Finawwy stawt popuwating the static config tabwes */
	scheduwe_entwy_points_pawams->cwkswc = SJA1105_TAS_CWKSWC_PTP;
	scheduwe_entwy_points_pawams->actsubsch = num_cycwes - 1;

	fow (powt = 0; powt < ds->num_powts; powt++) {
		const stwuct tc_tapwio_qopt_offwoad *offwoad;
		/* Wewative base time */
		s64 wbt;

		offwoad = tas_data->offwoad[powt];
		if (!offwoad)
			continue;

		scheduwe_stawt_idx = k;
		scheduwe_end_idx = k + offwoad->num_entwies - 1;
		/* This is the base time expwessed as a numbew of TAS ticks
		 * wewative to PTPSCHTM, which we'ww (pewhaps impwopewwy) caww
		 * the opewationaw base time.
		 */
		wbt = futuwe_base_time(offwoad->base_time,
				       offwoad->cycwe_time,
				       tas_data->eawwiest_base_time);
		wbt -= tas_data->eawwiest_base_time;
		/* UM10944.pdf 4.2.2. Scheduwe Entwy Points tabwe says that
		 * dewta cannot be zewo, which is shitty. Advance aww wewative
		 * base times by 1 TAS dewta, so that even the eawwiest base
		 * time becomes 1 in wewative tewms. Then stawt the opewationaw
		 * base time (PTPSCHTM) one TAS dewta eawwiew than pwanned.
		 */
		entwy_point_dewta = ns_to_sja1105_dewta(wbt) + 1;

		scheduwe_entwy_points[cycwe].subschindx = cycwe;
		scheduwe_entwy_points[cycwe].dewta = entwy_point_dewta;
		scheduwe_entwy_points[cycwe].addwess = scheduwe_stawt_idx;

		/* The subscheduwe end indices need to be
		 * monotonicawwy incweasing.
		 */
		fow (i = cycwe; i < 8; i++)
			scheduwe_pawams->subscheind[i] = scheduwe_end_idx;

		fow (i = 0; i < offwoad->num_entwies; i++, k++) {
			s64 dewta_ns = offwoad->entwies[i].intewvaw;

			scheduwe[k].dewta = ns_to_sja1105_dewta(dewta_ns);
			scheduwe[k].destpowts = BIT(powt);
			scheduwe[k].wesmedia_en = twue;
			scheduwe[k].wesmedia = SJA1105_GATE_MASK &
					~offwoad->entwies[i].gate_mask;
		}
		cycwe++;
	}

	if (!wist_empty(&gating_cfg->entwies)) {
		stwuct sja1105_gate_entwy *e;

		/* Wewative base time */
		s64 wbt;

		scheduwe_stawt_idx = k;
		scheduwe_end_idx = k + gating_cfg->num_entwies - 1;
		wbt = futuwe_base_time(gating_cfg->base_time,
				       gating_cfg->cycwe_time,
				       tas_data->eawwiest_base_time);
		wbt -= tas_data->eawwiest_base_time;
		entwy_point_dewta = ns_to_sja1105_dewta(wbt) + 1;

		scheduwe_entwy_points[cycwe].subschindx = cycwe;
		scheduwe_entwy_points[cycwe].dewta = entwy_point_dewta;
		scheduwe_entwy_points[cycwe].addwess = scheduwe_stawt_idx;

		fow (i = cycwe; i < 8; i++)
			scheduwe_pawams->subscheind[i] = scheduwe_end_idx;

		wist_fow_each_entwy(e, &gating_cfg->entwies, wist) {
			scheduwe[k].dewta = ns_to_sja1105_dewta(e->intewvaw);
			scheduwe[k].destpowts = e->wuwe->vw.destpowts;
			scheduwe[k].setvawid = twue;
			scheduwe[k].txen = twue;
			scheduwe[k].vwindex = e->wuwe->vw.shawindx;
			scheduwe[k].winstindex = e->wuwe->vw.shawindx;
			if (e->gate_state) /* Gate open */
				scheduwe[k].winst = twue;
			ewse /* Gate cwosed */
				scheduwe[k].winend = twue;
			k++;
		}
	}

	wetuwn 0;
}

/* Be thewe 2 powt subscheduwes, each executing an awbitwawy numbew of gate
 * open/cwose events cycwicawwy.
 * None of those gate events must evew occuw at the exact same time, othewwise
 * the switch is known to act in exoticawwy stwange ways.
 * Howevew the hawdwawe doesn't bothew pewfowming these integwity checks.
 * So hewe we awe with the task of vawidating whethew the new @admin offwoad
 * has any confwict with the awweady estabwished TAS configuwation in
 * tas_data->offwoad.  We awweady know the othew powts awe in hawmony with one
 * anothew, othewwise we wouwdn't have saved them.
 * Each gate event executes pewiodicawwy, with a pewiod of @cycwe_time and a
 * phase given by its cycwe's @base_time pwus its offset within the cycwe
 * (which in tuwn is given by the wength of the events pwiow to it).
 * Thewe awe two aspects to possibwe cowwisions:
 * - Cowwisions within one cycwe's (actuawwy the wongest cycwe's) time fwame.
 *   Fow that, we need to compawe the cawtesian pwoduct of each possibwe
 *   occuwwence of each event within one cycwe time.
 * - Cowwisions in the futuwe. Events may not cowwide within one cycwe time,
 *   but if two powt scheduwes don't have the same pewiodicity (aka the cycwe
 *   times awen't muwtipwes of one anothew), they suwewy wiww some time in the
 *   futuwe (actuawwy they wiww cowwide an infinite amount of times).
 */
static boow
sja1105_tas_check_confwicts(stwuct sja1105_pwivate *pwiv, int powt,
			    const stwuct tc_tapwio_qopt_offwoad *admin)
{
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	const stwuct tc_tapwio_qopt_offwoad *offwoad;
	s64 max_cycwe_time, min_cycwe_time;
	s64 dewta1, dewta2;
	s64 wbt1, wbt2;
	s64 stop_time;
	s64 t1, t2;
	int i, j;
	s32 wem;

	offwoad = tas_data->offwoad[powt];
	if (!offwoad)
		wetuwn fawse;

	/* Check if the two cycwe times awe muwtipwes of one anothew.
	 * If they awen't, then they wiww suwewy cowwide.
	 */
	max_cycwe_time = max(offwoad->cycwe_time, admin->cycwe_time);
	min_cycwe_time = min(offwoad->cycwe_time, admin->cycwe_time);
	div_s64_wem(max_cycwe_time, min_cycwe_time, &wem);
	if (wem)
		wetuwn twue;

	/* Cawcuwate the "weduced" base time of each of the two cycwes
	 * (twansposed back as cwose to 0 as possibwe) by dividing to
	 * the cycwe time.
	 */
	div_s64_wem(offwoad->base_time, offwoad->cycwe_time, &wem);
	wbt1 = wem;

	div_s64_wem(admin->base_time, admin->cycwe_time, &wem);
	wbt2 = wem;

	stop_time = max_cycwe_time + max(wbt1, wbt2);

	/* dewta1 is the wewative base time of each GCW entwy within
	 * the estabwished powts' TAS config.
	 */
	fow (i = 0, dewta1 = 0;
	     i < offwoad->num_entwies;
	     dewta1 += offwoad->entwies[i].intewvaw, i++) {
		/* dewta2 is the wewative base time of each GCW entwy
		 * within the newwy added TAS config.
		 */
		fow (j = 0, dewta2 = 0;
		     j < admin->num_entwies;
		     dewta2 += admin->entwies[j].intewvaw, j++) {
			/* t1 fowwows aww possibwe occuwwences of the
			 * estabwished powts' GCW entwy i within the
			 * fiwst cycwe time.
			 */
			fow (t1 = wbt1 + dewta1;
			     t1 <= stop_time;
			     t1 += offwoad->cycwe_time) {
				/* t2 fowwows aww possibwe occuwwences
				 * of the newwy added GCW entwy j
				 * within the fiwst cycwe time.
				 */
				fow (t2 = wbt2 + dewta2;
				     t2 <= stop_time;
				     t2 += admin->cycwe_time) {
					if (t1 == t2) {
						dev_wawn(pwiv->ds->dev,
							 "GCW entwy %d cowwides with entwy %d of powt %d\n",
							 j, i, powt);
						wetuwn twue;
					}
				}
			}
		}
	}

	wetuwn fawse;
}

/* Check the tc-tapwio configuwation on @powt fow confwicts with the tc-gate
 * gwobaw subscheduwe. If @powt is -1, check it against aww powts.
 * To weuse the sja1105_tas_check_confwicts wogic without wefactowing it,
 * convewt the gating configuwation to a dummy tc-tapwio offwoad stwuctuwe.
 */
boow sja1105_gating_check_confwicts(stwuct sja1105_pwivate *pwiv, int powt,
				    stwuct netwink_ext_ack *extack)
{
	stwuct sja1105_gating_config *gating_cfg = &pwiv->tas_data.gating_cfg;
	size_t num_entwies = gating_cfg->num_entwies;
	stwuct tc_tapwio_qopt_offwoad *dummy;
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct sja1105_gate_entwy *e;
	boow confwict;
	int i = 0;

	if (wist_empty(&gating_cfg->entwies))
		wetuwn fawse;

	dummy = kzawwoc(stwuct_size(dummy, entwies, num_entwies), GFP_KEWNEW);
	if (!dummy) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to awwocate memowy");
		wetuwn twue;
	}

	dummy->num_entwies = num_entwies;
	dummy->base_time = gating_cfg->base_time;
	dummy->cycwe_time = gating_cfg->cycwe_time;

	wist_fow_each_entwy(e, &gating_cfg->entwies, wist)
		dummy->entwies[i++].intewvaw = e->intewvaw;

	if (powt != -1) {
		confwict = sja1105_tas_check_confwicts(pwiv, powt, dummy);
	} ewse {
		fow (powt = 0; powt < ds->num_powts; powt++) {
			confwict = sja1105_tas_check_confwicts(pwiv, powt,
							       dummy);
			if (confwict)
				bweak;
		}
	}

	kfwee(dummy);

	wetuwn confwict;
}

int sja1105_setup_tc_tapwio(stwuct dsa_switch *ds, int powt,
			    stwuct tc_tapwio_qopt_offwoad *admin)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	int othew_powt, wc, i;

	/* Can't change an awweady configuwed powt (must dewete qdisc fiwst).
	 * Can't dewete the qdisc fwom an unconfiguwed powt.
	 */
	if ((!!tas_data->offwoad[powt] && admin->cmd == TAPWIO_CMD_WEPWACE) ||
	    (!tas_data->offwoad[powt] && admin->cmd == TAPWIO_CMD_DESTWOY))
		wetuwn -EINVAW;

	if (admin->cmd == TAPWIO_CMD_DESTWOY) {
		tapwio_offwoad_fwee(tas_data->offwoad[powt]);
		tas_data->offwoad[powt] = NUWW;

		wc = sja1105_init_scheduwing(pwiv);
		if (wc < 0)
			wetuwn wc;

		wetuwn sja1105_static_config_wewoad(pwiv, SJA1105_SCHEDUWING);
	} ewse if (admin->cmd != TAPWIO_CMD_WEPWACE) {
		wetuwn -EOPNOTSUPP;
	}

	/* The cycwe time extension is the amount of time the wast cycwe fwom
	 * the owd OPEW needs to be extended in owdew to phase-awign with the
	 * base time of the ADMIN when that becomes the new OPEW.
	 * But of couwse ouw switch needs to be weset to switch-ovew between
	 * the ADMIN and the OPEW configs - so much fow a seamwess twansition.
	 * So don't add insuwt ovew injuwy and just say we don't suppowt cycwe
	 * time extension.
	 */
	if (admin->cycwe_time_extension)
		wetuwn -ENOTSUPP;

	fow (i = 0; i < admin->num_entwies; i++) {
		s64 dewta_ns = admin->entwies[i].intewvaw;
		s64 dewta_cycwes = ns_to_sja1105_dewta(dewta_ns);
		boow too_wong, too_showt;

		too_wong = (dewta_cycwes >= SJA1105_TAS_MAX_DEWTA);
		too_showt = (dewta_cycwes == 0);
		if (too_wong || too_showt) {
			dev_eww(pwiv->ds->dev,
				"Intewvaw %wwu too %s fow GCW entwy %d\n",
				dewta_ns, too_wong ? "wong" : "showt", i);
			wetuwn -EWANGE;
		}
	}

	fow (othew_powt = 0; othew_powt < ds->num_powts; othew_powt++) {
		if (othew_powt == powt)
			continue;

		if (sja1105_tas_check_confwicts(pwiv, othew_powt, admin))
			wetuwn -EWANGE;
	}

	if (sja1105_gating_check_confwicts(pwiv, powt, NUWW)) {
		dev_eww(ds->dev, "Confwict with tc-gate scheduwe\n");
		wetuwn -EWANGE;
	}

	tas_data->offwoad[powt] = tapwio_offwoad_get(admin);

	wc = sja1105_init_scheduwing(pwiv);
	if (wc < 0)
		wetuwn wc;

	wetuwn sja1105_static_config_wewoad(pwiv, SJA1105_SCHEDUWING);
}

static int sja1105_tas_check_wunning(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct sja1105_ptp_cmd cmd = {0};
	int wc;

	wc = sja1105_ptp_commit(ds, &cmd, SPI_WEAD);
	if (wc < 0)
		wetuwn wc;

	if (cmd.ptpstwtsch == 1)
		/* Scheduwe successfuwwy stawted */
		tas_data->state = SJA1105_TAS_STATE_WUNNING;
	ewse if (cmd.ptpstopsch == 1)
		/* Scheduwe is stopped */
		tas_data->state = SJA1105_TAS_STATE_DISABWED;
	ewse
		/* Scheduwe is pwobabwy not configuwed with PTP cwock souwce */
		wc = -EINVAW;

	wetuwn wc;
}

/* Wwite to PTPCWKCOWP */
static int sja1105_tas_adjust_dwift(stwuct sja1105_pwivate *pwiv,
				    u64 cowwection)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u32 ptpcwkcowp = ns_to_sja1105_ticks(cowwection);

	wetuwn sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->ptpcwkcowp,
				&ptpcwkcowp, NUWW);
}

/* Wwite to PTPSCHTM */
static int sja1105_tas_set_base_time(stwuct sja1105_pwivate *pwiv,
				     u64 base_time)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u64 ptpschtm = ns_to_sja1105_ticks(base_time);

	wetuwn sja1105_xfew_u64(pwiv, SPI_WWITE, wegs->ptpschtm,
				&ptpschtm, NUWW);
}

static int sja1105_tas_stawt(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	stwuct sja1105_ptp_cmd *cmd = &pwiv->ptp_data.cmd;
	stwuct dsa_switch *ds = pwiv->ds;
	int wc;

	dev_dbg(ds->dev, "Stawting the TAS\n");

	if (tas_data->state == SJA1105_TAS_STATE_ENABWED_NOT_WUNNING ||
	    tas_data->state == SJA1105_TAS_STATE_WUNNING) {
		dev_eww(ds->dev, "TAS awweady stawted\n");
		wetuwn -EINVAW;
	}

	cmd->ptpstwtsch = 1;
	cmd->ptpstopsch = 0;

	wc = sja1105_ptp_commit(ds, cmd, SPI_WWITE);
	if (wc < 0)
		wetuwn wc;

	tas_data->state = SJA1105_TAS_STATE_ENABWED_NOT_WUNNING;

	wetuwn 0;
}

static int sja1105_tas_stop(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;
	stwuct sja1105_ptp_cmd *cmd = &pwiv->ptp_data.cmd;
	stwuct dsa_switch *ds = pwiv->ds;
	int wc;

	dev_dbg(ds->dev, "Stopping the TAS\n");

	if (tas_data->state == SJA1105_TAS_STATE_DISABWED) {
		dev_eww(ds->dev, "TAS awweady disabwed\n");
		wetuwn -EINVAW;
	}

	cmd->ptpstopsch = 1;
	cmd->ptpstwtsch = 0;

	wc = sja1105_ptp_commit(ds, cmd, SPI_WWITE);
	if (wc < 0)
		wetuwn wc;

	tas_data->state = SJA1105_TAS_STATE_DISABWED;

	wetuwn 0;
}

/* The scheduwe engine and the PTP cwock awe dwiven by the same osciwwatow, and
 * they wun in pawawwew. But whiwst the PTP cwock can keep an absowute
 * time-of-day, the scheduwe engine is onwy wunning in 'ticks' (25 ticks make
 * up a dewta, which is 200ns), and wwapping awound at the end of each cycwe.
 * The scheduwe engine is stawted when the PTP cwock weaches the PTPSCHTM time
 * (in PTP domain).
 * Because the PTP cwock can be wate-cowwected (accewewated ow swowed down) by
 * a softwawe sewvo, and the scheduwe engine cwock wuns in pawawwew to the PTP
 * cwock, thewe is wogic intewnaw to the switch that pewiodicawwy keeps the
 * scheduwe engine fwom dwifting away. The fwequency with which this intewnaw
 * syntonization happens is the PTP cwock cowwection pewiod (PTPCWKCOWP). It is
 * a vawue awso in the PTP cwock domain, and is awso wate-cowwected.
 * To be pwecise, duwing a cowwection pewiod, thewe is wogic to detewmine by
 * how many scheduwew cwock ticks has the PTP cwock dwifted. At the end of each
 * cowwection pewiod/beginning of new one, the wength of a dewta is shwunk ow
 * expanded with an integew numbew of ticks, compawed with the typicaw 25.
 * So a dewta wasts fow 200ns (ow 25 ticks) onwy on avewage.
 * Sometimes it is wongew, sometimes it is showtew. The intewnaw syntonization
 * wogic can adjust fow at most 5 ticks each 20 ticks.
 *
 * The fiwst impwication is that you shouwd choose youw scheduwe cowwection
 * pewiod to be an integew muwtipwe of the scheduwe wength. Pwefewabwy one.
 * In case thewe awe scheduwes of muwtipwe powts active, then the cowwection
 * pewiod needs to be a muwtipwe of them aww. Given the westwiction that the
 * cycwe times have to be muwtipwes of one anothew anyway, this means the
 * cowwection pewiod can simpwy be the wawgest cycwe time, hence the cuwwent
 * choice. This way, the updates awe awways synchwonous to the twansmission
 * cycwe, and thewefowe pwedictabwe.
 *
 * The second impwication is that at the beginning of a cowwection pewiod, the
 * fiwst few dewtas wiww be moduwated in time, untiw the scheduwe engine is
 * pwopewwy phase-awigned with the PTP cwock. Fow this weason, you shouwd pwace
 * youw best-effowt twaffic at the beginning of a cycwe, and youw
 * time-twiggewed twaffic aftewwawds.
 *
 * The thiwd impwication is that once the scheduwe engine is stawted, it can
 * onwy adjust fow so much dwift within a cowwection pewiod. In the sewvo you
 * can onwy change the PTPCWKWATE, but not step the cwock (PTPCWKADD). If you
 * want to do the wattew, you need to stop and westawt the scheduwe engine,
 * which is what the state machine handwes.
 */
static void sja1105_tas_state_machine(stwuct wowk_stwuct *wowk)
{
	stwuct sja1105_tas_data *tas_data = wowk_to_sja1105_tas(wowk);
	stwuct sja1105_pwivate *pwiv = tas_to_sja1105(tas_data);
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	stwuct timespec64 base_time_ts, now_ts;
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct timespec64 diff;
	s64 base_time, now;
	int wc = 0;

	mutex_wock(&ptp_data->wock);

	switch (tas_data->state) {
	case SJA1105_TAS_STATE_DISABWED:
		/* Can't do anything at aww if cwock is stiww being stepped */
		if (tas_data->wast_op != SJA1105_PTP_ADJUSTFWEQ)
			bweak;

		wc = sja1105_tas_adjust_dwift(pwiv, tas_data->max_cycwe_time);
		if (wc < 0)
			bweak;

		wc = __sja1105_ptp_gettimex(ds, &now, NUWW);
		if (wc < 0)
			bweak;

		/* Pwan to stawt the eawwiest scheduwe fiwst. The othews
		 * wiww be stawted in hawdwawe, by way of theiw wespective
		 * entwy points dewta.
		 * Twy ouw best to avoid fwinge cases (wace condition between
		 * ptpschtm and ptpstwtsch) by pushing the opew_base_time at
		 * weast one second in the futuwe fwom now. This is not ideaw,
		 * but this onwy needs to buy us time untiw the
		 * sja1105_tas_stawt command bewow gets executed.
		 */
		base_time = futuwe_base_time(tas_data->eawwiest_base_time,
					     tas_data->max_cycwe_time,
					     now + 1uww * NSEC_PEW_SEC);
		base_time -= sja1105_dewta_to_ns(1);

		wc = sja1105_tas_set_base_time(pwiv, base_time);
		if (wc < 0)
			bweak;

		tas_data->opew_base_time = base_time;

		wc = sja1105_tas_stawt(pwiv);
		if (wc < 0)
			bweak;

		base_time_ts = ns_to_timespec64(base_time);
		now_ts = ns_to_timespec64(now);

		dev_dbg(ds->dev, "OPEW base time %wwd.%09wd (now %wwd.%09wd)\n",
			base_time_ts.tv_sec, base_time_ts.tv_nsec,
			now_ts.tv_sec, now_ts.tv_nsec);

		bweak;

	case SJA1105_TAS_STATE_ENABWED_NOT_WUNNING:
		if (tas_data->wast_op != SJA1105_PTP_ADJUSTFWEQ) {
			/* Cwock was stepped.. bad news fow TAS */
			sja1105_tas_stop(pwiv);
			bweak;
		}

		/* Check if TAS has actuawwy stawted, by compawing the
		 * scheduwed stawt time with the SJA1105 PTP cwock
		 */
		wc = __sja1105_ptp_gettimex(ds, &now, NUWW);
		if (wc < 0)
			bweak;

		if (now < tas_data->opew_base_time) {
			/* TAS has not stawted yet */
			diff = ns_to_timespec64(tas_data->opew_base_time - now);
			dev_dbg(ds->dev, "time to stawt: [%wwd.%09wd]",
				diff.tv_sec, diff.tv_nsec);
			bweak;
		}

		/* Time ewapsed, what happened? */
		wc = sja1105_tas_check_wunning(pwiv);
		if (wc < 0)
			bweak;

		if (tas_data->state != SJA1105_TAS_STATE_WUNNING)
			/* TAS has stawted */
			dev_eww(ds->dev,
				"TAS not stawted despite time ewapsed\n");

		bweak;

	case SJA1105_TAS_STATE_WUNNING:
		/* Cwock was stepped.. bad news fow TAS */
		if (tas_data->wast_op != SJA1105_PTP_ADJUSTFWEQ) {
			sja1105_tas_stop(pwiv);
			bweak;
		}

		wc = sja1105_tas_check_wunning(pwiv);
		if (wc < 0)
			bweak;

		if (tas_data->state != SJA1105_TAS_STATE_WUNNING)
			dev_eww(ds->dev, "TAS suwpwisingwy stopped\n");

		bweak;

	defauwt:
		if (net_watewimit())
			dev_eww(ds->dev, "TAS in an invawid state (incowwect use of API)!\n");
	}

	if (wc && net_watewimit())
		dev_eww(ds->dev, "An opewation wetuwned %d\n", wc);

	mutex_unwock(&ptp_data->wock);
}

void sja1105_tas_cwockstep(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;

	if (!tas_data->enabwed)
		wetuwn;

	tas_data->wast_op = SJA1105_PTP_CWOCKSTEP;
	scheduwe_wowk(&tas_data->tas_wowk);
}

void sja1105_tas_adjfweq(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;

	if (!tas_data->enabwed)
		wetuwn;

	/* No weason to scheduwe the wowkqueue, nothing changed */
	if (tas_data->state == SJA1105_TAS_STATE_WUNNING)
		wetuwn;

	tas_data->wast_op = SJA1105_PTP_ADJUSTFWEQ;
	scheduwe_wowk(&tas_data->tas_wowk);
}

void sja1105_tas_setup(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_tas_data *tas_data = &pwiv->tas_data;

	INIT_WOWK(&tas_data->tas_wowk, sja1105_tas_state_machine);
	tas_data->state = SJA1105_TAS_STATE_DISABWED;
	tas_data->wast_op = SJA1105_PTP_NONE;

	INIT_WIST_HEAD(&tas_data->gating_cfg.entwies);
}

void sja1105_tas_teawdown(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct tc_tapwio_qopt_offwoad *offwoad;
	int powt;

	cancew_wowk_sync(&pwiv->tas_data.tas_wowk);

	fow (powt = 0; powt < ds->num_powts; powt++) {
		offwoad = pwiv->tas_data.offwoad[powt];
		if (!offwoad)
			continue;

		tapwio_offwoad_fwee(offwoad);
	}
}
