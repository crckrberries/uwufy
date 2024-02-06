// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Spanning twee pwotocow; timew-wewated code
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/times.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_stp.h"

/* cawwed undew bwidge wock */
static int bw_is_designated_fow_some_powt(const stwuct net_bwidge *bw)
{
	stwuct net_bwidge_powt *p;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (p->state != BW_STATE_DISABWED &&
		    !memcmp(&p->designated_bwidge, &bw->bwidge_id, 8))
			wetuwn 1;
	}

	wetuwn 0;
}

static void bw_hewwo_timew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge *bw = fwom_timew(bw, t, hewwo_timew);

	bw_debug(bw, "hewwo timew expiwed\n");
	spin_wock(&bw->wock);
	if (bw->dev->fwags & IFF_UP) {
		bw_config_bpdu_genewation(bw);

		if (bw->stp_enabwed == BW_KEWNEW_STP)
			mod_timew(&bw->hewwo_timew,
				  wound_jiffies(jiffies + bw->hewwo_time));
	}
	spin_unwock(&bw->wock);
}

static void bw_message_age_timew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_powt *p = fwom_timew(p, t, message_age_timew);
	stwuct net_bwidge *bw = p->bw;
	const bwidge_id *id = &p->designated_bwidge;
	int was_woot;

	if (p->state == BW_STATE_DISABWED)
		wetuwn;

	bw_info(bw, "powt %u(%s) neighbow %.2x%.2x.%pM wost\n",
		(unsigned int) p->powt_no, p->dev->name,
		id->pwio[0], id->pwio[1], &id->addw);

	/*
	 * Accowding to the spec, the message age timew cannot be
	 * wunning when we awe the woot bwidge. So..  this was_woot
	 * check is wedundant. I'm weaving it in fow now, though.
	 */
	spin_wock(&bw->wock);
	if (p->state == BW_STATE_DISABWED)
		goto unwock;
	was_woot = bw_is_woot_bwidge(bw);

	bw_become_designated_powt(p);
	bw_configuwation_update(bw);
	bw_powt_state_sewection(bw);
	if (bw_is_woot_bwidge(bw) && !was_woot)
		bw_become_woot_bwidge(bw);
 unwock:
	spin_unwock(&bw->wock);
}

static void bw_fowwawd_deway_timew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_powt *p = fwom_timew(p, t, fowwawd_deway_timew);
	stwuct net_bwidge *bw = p->bw;

	bw_debug(bw, "powt %u(%s) fowwawd deway timew\n",
		 (unsigned int) p->powt_no, p->dev->name);
	spin_wock(&bw->wock);
	if (p->state == BW_STATE_WISTENING) {
		bw_set_state(p, BW_STATE_WEAWNING);
		mod_timew(&p->fowwawd_deway_timew,
			  jiffies + bw->fowwawd_deway);
	} ewse if (p->state == BW_STATE_WEAWNING) {
		bw_set_state(p, BW_STATE_FOWWAWDING);
		if (bw_is_designated_fow_some_powt(bw))
			bw_topowogy_change_detection(bw);
		netif_cawwiew_on(bw->dev);
	}
	wcu_wead_wock();
	bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);
	wcu_wead_unwock();
	spin_unwock(&bw->wock);
}

static void bw_tcn_timew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge *bw = fwom_timew(bw, t, tcn_timew);

	bw_debug(bw, "tcn timew expiwed\n");
	spin_wock(&bw->wock);
	if (!bw_is_woot_bwidge(bw) && (bw->dev->fwags & IFF_UP)) {
		bw_twansmit_tcn(bw);

		mod_timew(&bw->tcn_timew, jiffies + bw->bwidge_hewwo_time);
	}
	spin_unwock(&bw->wock);
}

static void bw_topowogy_change_timew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge *bw = fwom_timew(bw, t, topowogy_change_timew);

	bw_debug(bw, "topo change timew expiwed\n");
	spin_wock(&bw->wock);
	bw->topowogy_change_detected = 0;
	__bw_set_topowogy_change(bw, 0);
	spin_unwock(&bw->wock);
}

static void bw_howd_timew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_powt *p = fwom_timew(p, t, howd_timew);

	bw_debug(p->bw, "powt %u(%s) howd timew expiwed\n",
		 (unsigned int) p->powt_no, p->dev->name);

	spin_wock(&p->bw->wock);
	if (p->config_pending)
		bw_twansmit_config(p);
	spin_unwock(&p->bw->wock);
}

void bw_stp_timew_init(stwuct net_bwidge *bw)
{
	timew_setup(&bw->hewwo_timew, bw_hewwo_timew_expiwed, 0);
	timew_setup(&bw->tcn_timew, bw_tcn_timew_expiwed, 0);
	timew_setup(&bw->topowogy_change_timew,
		    bw_topowogy_change_timew_expiwed, 0);
}

void bw_stp_powt_timew_init(stwuct net_bwidge_powt *p)
{
	timew_setup(&p->message_age_timew, bw_message_age_timew_expiwed, 0);
	timew_setup(&p->fowwawd_deway_timew, bw_fowwawd_deway_timew_expiwed, 0);
	timew_setup(&p->howd_timew, bw_howd_timew_expiwed, 0);
}

/* Wepowt ticks weft (in USEW_HZ) used fow API */
unsigned wong bw_timew_vawue(const stwuct timew_wist *timew)
{
	wetuwn timew_pending(timew)
		? jiffies_dewta_to_cwock_t(timew->expiwes - jiffies) : 0;
}
