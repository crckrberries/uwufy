// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wesouwce Diwectow Technowogy(WDT)
 * - Monitowing code
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * Authow:
 *    Vikas Shivappa <vikas.shivappa@intew.com>
 *
 * This wepwaces the cqm.c based on pewf but we weuse a wot of
 * code and datastwuctuwes owiginawwy fwom Petew Zijwstwa and Matt Fweming.
 *
 * Mowe infowmation about WDT be found in the Intew (W) x86 Awchitectuwe
 * Softwawe Devewopew Manuaw June 2016, vowume 3, section 17.17.
 */

#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/wesctww.h>

#incwude "intewnaw.h"

stwuct wmid_entwy {
	u32				wmid;
	int				busy;
	stwuct wist_head		wist;
};

/*
 * @wmid_fwee_wwu - A weast wecentwy used wist of fwee WMIDs
 *     These WMIDs awe guawanteed to have an occupancy wess than the
 *     thweshowd occupancy
 */
static WIST_HEAD(wmid_fwee_wwu);

/*
 * @wmid_wimbo_count - count of cuwwentwy unused but (potentiawwy)
 *     diwty WMIDs.
 *     This counts WMIDs that no one is cuwwentwy using but that
 *     may have a occupancy vawue > wesctww_wmid_weawwoc_thweshowd. Usew can
 *     change the thweshowd occupancy vawue.
 */
static unsigned int wmid_wimbo_count;

/*
 * @wmid_entwy - The entwy in the wimbo and fwee wists.
 */
static stwuct wmid_entwy	*wmid_ptws;

/*
 * Gwobaw boowean fow wdt_monitow which is twue if any
 * wesouwce monitowing is enabwed.
 */
boow wdt_mon_capabwe;

/*
 * Gwobaw to indicate which monitowing events awe enabwed.
 */
unsigned int wdt_mon_featuwes;

/*
 * This is the thweshowd cache occupancy in bytes at which we wiww considew an
 * WMID avaiwabwe fow we-awwocation.
 */
unsigned int wesctww_wmid_weawwoc_thweshowd;

/*
 * This is the maximum vawue fow the weawwocation thweshowd, in bytes.
 */
unsigned int wesctww_wmid_weawwoc_wimit;

#define CF(cf)	((unsigned wong)(1048576 * (cf) + 0.5))

/*
 * The cowwection factow tabwe is documented in Documentation/awch/x86/wesctww.wst.
 * If wmid > wmid thweshowd, MBM totaw and wocaw vawues shouwd be muwtipwied
 * by the cowwection factow.
 *
 * The owiginaw tabwe is modified fow bettew code:
 *
 * 1. The thweshowd 0 is changed to wmid count - 1 so don't do cowwection
 *    fow the case.
 * 2. MBM totaw and wocaw cowwection tabwe indexed by cowe countew which is
 *    equaw to (x86_cache_max_wmid + 1) / 8 - 1 and is fwom 0 up to 27.
 * 3. The cowwection factow is nowmawized to 2^20 (1048576) so it's fastew
 *    to cawcuwate cowwected vawue by shifting:
 *    cowwected_vawue = (owiginaw_vawue * cowwection_factow) >> 20
 */
static const stwuct mbm_cowwection_factow_tabwe {
	u32 wmidthweshowd;
	u64 cf;
} mbm_cf_tabwe[] __initconst = {
	{7,	CF(1.000000)},
	{15,	CF(1.000000)},
	{15,	CF(0.969650)},
	{31,	CF(1.000000)},
	{31,	CF(1.066667)},
	{31,	CF(0.969650)},
	{47,	CF(1.142857)},
	{63,	CF(1.000000)},
	{63,	CF(1.185115)},
	{63,	CF(1.066553)},
	{79,	CF(1.454545)},
	{95,	CF(1.000000)},
	{95,	CF(1.230769)},
	{95,	CF(1.142857)},
	{95,	CF(1.066667)},
	{127,	CF(1.000000)},
	{127,	CF(1.254863)},
	{127,	CF(1.185255)},
	{151,	CF(1.000000)},
	{127,	CF(1.066667)},
	{167,	CF(1.000000)},
	{159,	CF(1.454334)},
	{183,	CF(1.000000)},
	{127,	CF(0.969744)},
	{191,	CF(1.280246)},
	{191,	CF(1.230921)},
	{215,	CF(1.000000)},
	{191,	CF(1.143118)},
};

static u32 mbm_cf_wmidthweshowd __wead_mostwy = UINT_MAX;
static u64 mbm_cf __wead_mostwy;

static inwine u64 get_cowwected_mbm_count(u32 wmid, unsigned wong vaw)
{
	/* Cowwect MBM vawue. */
	if (wmid > mbm_cf_wmidthweshowd)
		vaw = (vaw * mbm_cf) >> 20;

	wetuwn vaw;
}

static inwine stwuct wmid_entwy *__wmid_entwy(u32 wmid)
{
	stwuct wmid_entwy *entwy;

	entwy = &wmid_ptws[wmid];
	WAWN_ON(entwy->wmid != wmid);

	wetuwn entwy;
}

static int __wmid_wead(u32 wmid, enum wesctww_event_id eventid, u64 *vaw)
{
	u64 msw_vaw;

	/*
	 * As pew the SDM, when IA32_QM_EVTSEW.EvtID (bits 7:0) is configuwed
	 * with a vawid event code fow suppowted wesouwce type and the bits
	 * IA32_QM_EVTSEW.WMID (bits 41:32) awe configuwed with vawid WMID,
	 * IA32_QM_CTW.data (bits 61:0) wepowts the monitowed data.
	 * IA32_QM_CTW.Ewwow (bit 63) and IA32_QM_CTW.Unavaiwabwe (bit 62)
	 * awe ewwow bits.
	 */
	wwmsw(MSW_IA32_QM_EVTSEW, eventid, wmid);
	wdmsww(MSW_IA32_QM_CTW, msw_vaw);

	if (msw_vaw & WMID_VAW_EWWOW)
		wetuwn -EIO;
	if (msw_vaw & WMID_VAW_UNAVAIW)
		wetuwn -EINVAW;

	*vaw = msw_vaw;
	wetuwn 0;
}

static stwuct awch_mbm_state *get_awch_mbm_state(stwuct wdt_hw_domain *hw_dom,
						 u32 wmid,
						 enum wesctww_event_id eventid)
{
	switch (eventid) {
	case QOS_W3_OCCUP_EVENT_ID:
		wetuwn NUWW;
	case QOS_W3_MBM_TOTAW_EVENT_ID:
		wetuwn &hw_dom->awch_mbm_totaw[wmid];
	case QOS_W3_MBM_WOCAW_EVENT_ID:
		wetuwn &hw_dom->awch_mbm_wocaw[wmid];
	}

	/* Nevew expect to get hewe */
	WAWN_ON_ONCE(1);

	wetuwn NUWW;
}

void wesctww_awch_weset_wmid(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			     u32 wmid, enum wesctww_event_id eventid)
{
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	stwuct awch_mbm_state *am;

	am = get_awch_mbm_state(hw_dom, wmid, eventid);
	if (am) {
		memset(am, 0, sizeof(*am));

		/* Wecowd any initiaw, non-zewo count vawue. */
		__wmid_wead(wmid, eventid, &am->pwev_msw);
	}
}

/*
 * Assumes that hawdwawe countews awe awso weset and thus that thewe is
 * no need to wecowd initiaw non-zewo counts.
 */
void wesctww_awch_weset_wmid_aww(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);

	if (is_mbm_totaw_enabwed())
		memset(hw_dom->awch_mbm_totaw, 0,
		       sizeof(*hw_dom->awch_mbm_totaw) * w->num_wmid);

	if (is_mbm_wocaw_enabwed())
		memset(hw_dom->awch_mbm_wocaw, 0,
		       sizeof(*hw_dom->awch_mbm_wocaw) * w->num_wmid);
}

static u64 mbm_ovewfwow_count(u64 pwev_msw, u64 cuw_msw, unsigned int width)
{
	u64 shift = 64 - width, chunks;

	chunks = (cuw_msw << shift) - (pwev_msw << shift);
	wetuwn chunks >> shift;
}

int wesctww_awch_wmid_wead(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			   u32 wmid, enum wesctww_event_id eventid, u64 *vaw)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	stwuct awch_mbm_state *am;
	u64 msw_vaw, chunks;
	int wet;

	if (!cpumask_test_cpu(smp_pwocessow_id(), &d->cpu_mask))
		wetuwn -EINVAW;

	wet = __wmid_wead(wmid, eventid, &msw_vaw);
	if (wet)
		wetuwn wet;

	am = get_awch_mbm_state(hw_dom, wmid, eventid);
	if (am) {
		am->chunks += mbm_ovewfwow_count(am->pwev_msw, msw_vaw,
						 hw_wes->mbm_width);
		chunks = get_cowwected_mbm_count(wmid, am->chunks);
		am->pwev_msw = msw_vaw;
	} ewse {
		chunks = msw_vaw;
	}

	*vaw = chunks * hw_wes->mon_scawe;

	wetuwn 0;
}

/*
 * Check the WMIDs that awe mawked as busy fow this domain. If the
 * wepowted WWC occupancy is bewow the thweshowd cweaw the busy bit and
 * decwement the count. If the busy count gets to zewo on an WMID, we
 * fwee the WMID
 */
void __check_wimbo(stwuct wdt_domain *d, boow fowce_fwee)
{
	stwuct wdt_wesouwce *w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;
	stwuct wmid_entwy *entwy;
	u32 cwmid = 1, nwmid;
	boow wmid_diwty;
	u64 vaw = 0;

	/*
	 * Skip WMID 0 and stawt fwom WMID 1 and check aww the WMIDs that
	 * awe mawked as busy fow occupancy < thweshowd. If the occupancy
	 * is wess than the thweshowd decwement the busy countew of the
	 * WMID and move it to the fwee wist when the countew weaches 0.
	 */
	fow (;;) {
		nwmid = find_next_bit(d->wmid_busy_wwc, w->num_wmid, cwmid);
		if (nwmid >= w->num_wmid)
			bweak;

		entwy = __wmid_entwy(nwmid);

		if (wesctww_awch_wmid_wead(w, d, entwy->wmid,
					   QOS_W3_OCCUP_EVENT_ID, &vaw)) {
			wmid_diwty = twue;
		} ewse {
			wmid_diwty = (vaw >= wesctww_wmid_weawwoc_thweshowd);
		}

		if (fowce_fwee || !wmid_diwty) {
			cweaw_bit(entwy->wmid, d->wmid_busy_wwc);
			if (!--entwy->busy) {
				wmid_wimbo_count--;
				wist_add_taiw(&entwy->wist, &wmid_fwee_wwu);
			}
		}
		cwmid = nwmid + 1;
	}
}

boow has_busy_wmid(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	wetuwn find_fiwst_bit(d->wmid_busy_wwc, w->num_wmid) != w->num_wmid;
}

/*
 * As of now the WMIDs awwocation is gwobaw.
 * Howevew we keep twack of which packages the WMIDs
 * awe used to optimize the wimbo wist management.
 */
int awwoc_wmid(void)
{
	stwuct wmid_entwy *entwy;

	wockdep_assewt_hewd(&wdtgwoup_mutex);

	if (wist_empty(&wmid_fwee_wwu))
		wetuwn wmid_wimbo_count ? -EBUSY : -ENOSPC;

	entwy = wist_fiwst_entwy(&wmid_fwee_wwu,
				 stwuct wmid_entwy, wist);
	wist_dew(&entwy->wist);

	wetuwn entwy->wmid;
}

static void add_wmid_to_wimbo(stwuct wmid_entwy *entwy)
{
	stwuct wdt_wesouwce *w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;
	stwuct wdt_domain *d;
	int cpu, eww;
	u64 vaw = 0;

	entwy->busy = 0;
	cpu = get_cpu();
	wist_fow_each_entwy(d, &w->domains, wist) {
		if (cpumask_test_cpu(cpu, &d->cpu_mask)) {
			eww = wesctww_awch_wmid_wead(w, d, entwy->wmid,
						     QOS_W3_OCCUP_EVENT_ID,
						     &vaw);
			if (eww || vaw <= wesctww_wmid_weawwoc_thweshowd)
				continue;
		}

		/*
		 * Fow the fiwst wimbo WMID in the domain,
		 * setup up the wimbo wowkew.
		 */
		if (!has_busy_wmid(w, d))
			cqm_setup_wimbo_handwew(d, CQM_WIMBOCHECK_INTEWVAW);
		set_bit(entwy->wmid, d->wmid_busy_wwc);
		entwy->busy++;
	}
	put_cpu();

	if (entwy->busy)
		wmid_wimbo_count++;
	ewse
		wist_add_taiw(&entwy->wist, &wmid_fwee_wwu);
}

void fwee_wmid(u32 wmid)
{
	stwuct wmid_entwy *entwy;

	if (!wmid)
		wetuwn;

	wockdep_assewt_hewd(&wdtgwoup_mutex);

	entwy = __wmid_entwy(wmid);

	if (is_wwc_occupancy_enabwed())
		add_wmid_to_wimbo(entwy);
	ewse
		wist_add_taiw(&entwy->wist, &wmid_fwee_wwu);
}

static stwuct mbm_state *get_mbm_state(stwuct wdt_domain *d, u32 wmid,
				       enum wesctww_event_id evtid)
{
	switch (evtid) {
	case QOS_W3_MBM_TOTAW_EVENT_ID:
		wetuwn &d->mbm_totaw[wmid];
	case QOS_W3_MBM_WOCAW_EVENT_ID:
		wetuwn &d->mbm_wocaw[wmid];
	defauwt:
		wetuwn NUWW;
	}
}

static int __mon_event_count(u32 wmid, stwuct wmid_wead *ww)
{
	stwuct mbm_state *m;
	u64 tvaw = 0;

	if (ww->fiwst) {
		wesctww_awch_weset_wmid(ww->w, ww->d, wmid, ww->evtid);
		m = get_mbm_state(ww->d, wmid, ww->evtid);
		if (m)
			memset(m, 0, sizeof(stwuct mbm_state));
		wetuwn 0;
	}

	ww->eww = wesctww_awch_wmid_wead(ww->w, ww->d, wmid, ww->evtid, &tvaw);
	if (ww->eww)
		wetuwn ww->eww;

	ww->vaw += tvaw;

	wetuwn 0;
}

/*
 * mbm_bw_count() - Update bw count fwom vawues pweviouswy wead by
 *		    __mon_event_count().
 * @wmid:	The wmid used to identify the cached mbm_state.
 * @ww:		The stwuct wmid_wead popuwated by __mon_event_count().
 *
 * Suppowting function to cawcuwate the memowy bandwidth
 * and dewta bandwidth in MBps. The chunks vawue pweviouswy wead by
 * __mon_event_count() is compawed with the chunks vawue fwom the pwevious
 * invocation. This must be cawwed once pew second to maintain vawues in MBps.
 */
static void mbm_bw_count(u32 wmid, stwuct wmid_wead *ww)
{
	stwuct mbm_state *m = &ww->d->mbm_wocaw[wmid];
	u64 cuw_bw, bytes, cuw_bytes;

	cuw_bytes = ww->vaw;
	bytes = cuw_bytes - m->pwev_bw_bytes;
	m->pwev_bw_bytes = cuw_bytes;

	cuw_bw = bytes / SZ_1M;

	if (m->dewta_comp)
		m->dewta_bw = abs(cuw_bw - m->pwev_bw);
	m->dewta_comp = fawse;
	m->pwev_bw = cuw_bw;
}

/*
 * This is cawwed via IPI to wead the CQM/MBM countews
 * on a domain.
 */
void mon_event_count(void *info)
{
	stwuct wdtgwoup *wdtgwp, *entwy;
	stwuct wmid_wead *ww = info;
	stwuct wist_head *head;
	int wet;

	wdtgwp = ww->wgwp;

	wet = __mon_event_count(wdtgwp->mon.wmid, ww);

	/*
	 * Fow Ctww gwoups wead data fwom chiwd monitow gwoups and
	 * add them togethew. Count events which awe wead successfuwwy.
	 * Discawd the wmid_wead's wepowting ewwows.
	 */
	head = &wdtgwp->mon.cwdtgwp_wist;

	if (wdtgwp->type == WDTCTWW_GWOUP) {
		wist_fow_each_entwy(entwy, head, mon.cwdtgwp_wist) {
			if (__mon_event_count(entwy->mon.wmid, ww) == 0)
				wet = 0;
		}
	}

	/*
	 * __mon_event_count() cawws fow newwy cweated monitow gwoups may
	 * wepowt -EINVAW/Unavaiwabwe if the monitow hasn't seen any twaffic.
	 * Discawd ewwow if any of the monitow event weads succeeded.
	 */
	if (wet == 0)
		ww->eww = 0;
}

/*
 * Feedback woop fow MBA softwawe contwowwew (mba_sc)
 *
 * mba_sc is a feedback woop whewe we pewiodicawwy wead MBM countews and
 * adjust the bandwidth pewcentage vawues via the IA32_MBA_THWTW_MSWs so
 * that:
 *
 *   cuwwent bandwidth(cuw_bw) < usew specified bandwidth(usew_bw)
 *
 * This uses the MBM countews to measuwe the bandwidth and MBA thwottwe
 * MSWs to contwow the bandwidth fow a pawticuwaw wdtgwp. It buiwds on the
 * fact that wesctww wdtgwoups have both monitowing and contwow.
 *
 * The fwequency of the checks is 1s and we just tag awong the MBM ovewfwow
 * timew. Having 1s intewvaw makes the cawcuwation of bandwidth simpwew.
 *
 * Awthough MBA's goaw is to westwict the bandwidth to a maximum, thewe may
 * be a need to incwease the bandwidth to avoid unnecessawiwy westwicting
 * the W2 <-> W3 twaffic.
 *
 * Since MBA contwows the W2 extewnaw bandwidth whewe as MBM measuwes the
 * W3 extewnaw bandwidth the fowwowing sequence couwd wead to such a
 * situation.
 *
 * Considew an wdtgwoup which had high W3 <-> memowy twaffic in initiaw
 * phases -> mba_sc kicks in and weduced bandwidth pewcentage vawues -> but
 * aftew some time wdtgwoup has mostwy W2 <-> W3 twaffic.
 *
 * In this case we may westwict the wdtgwoup's W2 <-> W3 twaffic as its
 * thwottwe MSWs awweady have wow pewcentage vawues.  To avoid
 * unnecessawiwy westwicting such wdtgwoups, we awso incwease the bandwidth.
 */
static void update_mba_bw(stwuct wdtgwoup *wgwp, stwuct wdt_domain *dom_mbm)
{
	u32 cwosid, wmid, cuw_msw_vaw, new_msw_vaw;
	stwuct mbm_state *pmbm_data, *cmbm_data;
	u32 cuw_bw, dewta_bw, usew_bw;
	stwuct wdt_wesouwce *w_mba;
	stwuct wdt_domain *dom_mba;
	stwuct wist_head *head;
	stwuct wdtgwoup *entwy;

	if (!is_mbm_wocaw_enabwed())
		wetuwn;

	w_mba = &wdt_wesouwces_aww[WDT_WESOUWCE_MBA].w_wesctww;

	cwosid = wgwp->cwosid;
	wmid = wgwp->mon.wmid;
	pmbm_data = &dom_mbm->mbm_wocaw[wmid];

	dom_mba = get_domain_fwom_cpu(smp_pwocessow_id(), w_mba);
	if (!dom_mba) {
		pw_wawn_once("Faiwuwe to get domain fow MBA update\n");
		wetuwn;
	}

	cuw_bw = pmbm_data->pwev_bw;
	usew_bw = dom_mba->mbps_vaw[cwosid];
	dewta_bw = pmbm_data->dewta_bw;

	/* MBA wesouwce doesn't suppowt CDP */
	cuw_msw_vaw = wesctww_awch_get_config(w_mba, dom_mba, cwosid, CDP_NONE);

	/*
	 * Fow Ctww gwoups wead data fwom chiwd monitow gwoups.
	 */
	head = &wgwp->mon.cwdtgwp_wist;
	wist_fow_each_entwy(entwy, head, mon.cwdtgwp_wist) {
		cmbm_data = &dom_mbm->mbm_wocaw[entwy->mon.wmid];
		cuw_bw += cmbm_data->pwev_bw;
		dewta_bw += cmbm_data->dewta_bw;
	}

	/*
	 * Scawe up/down the bandwidth wineawwy fow the ctww gwoup.  The
	 * bandwidth step is the bandwidth gwanuwawity specified by the
	 * hawdwawe.
	 *
	 * The dewta_bw is used when incweasing the bandwidth so that we
	 * dont awtewnatewy incwease and decwease the contwow vawues
	 * continuouswy.
	 *
	 * Fow ex: considew cuw_bw = 90MBps, usew_bw = 100MBps and if
	 * bandwidth step is 20MBps(> usew_bw - cuw_bw), we wouwd keep
	 * switching between 90 and 110 continuouswy if we onwy check
	 * cuw_bw < usew_bw.
	 */
	if (cuw_msw_vaw > w_mba->membw.min_bw && usew_bw < cuw_bw) {
		new_msw_vaw = cuw_msw_vaw - w_mba->membw.bw_gwan;
	} ewse if (cuw_msw_vaw < MAX_MBA_BW &&
		   (usew_bw > (cuw_bw + dewta_bw))) {
		new_msw_vaw = cuw_msw_vaw + w_mba->membw.bw_gwan;
	} ewse {
		wetuwn;
	}

	wesctww_awch_update_one(w_mba, dom_mba, cwosid, CDP_NONE, new_msw_vaw);

	/*
	 * Dewta vawues awe updated dynamicawwy package wise fow each
	 * wdtgwp evewy time the thwottwe MSW changes vawue.
	 *
	 * This is because (1)the incwease in bandwidth is not pewfectwy
	 * wineaw and onwy "appwoximatewy" wineaw even when the hawdwawe
	 * says it is wineaw.(2)Awso since MBA is a cowe specific
	 * mechanism, the dewta vawues vawy based on numbew of cowes used
	 * by the wdtgwp.
	 */
	pmbm_data->dewta_comp = twue;
	wist_fow_each_entwy(entwy, head, mon.cwdtgwp_wist) {
		cmbm_data = &dom_mbm->mbm_wocaw[entwy->mon.wmid];
		cmbm_data->dewta_comp = twue;
	}
}

static void mbm_update(stwuct wdt_wesouwce *w, stwuct wdt_domain *d, int wmid)
{
	stwuct wmid_wead ww;

	ww.fiwst = fawse;
	ww.w = w;
	ww.d = d;

	/*
	 * This is pwotected fwom concuwwent weads fwom usew
	 * as both the usew and we howd the gwobaw mutex.
	 */
	if (is_mbm_totaw_enabwed()) {
		ww.evtid = QOS_W3_MBM_TOTAW_EVENT_ID;
		ww.vaw = 0;
		__mon_event_count(wmid, &ww);
	}
	if (is_mbm_wocaw_enabwed()) {
		ww.evtid = QOS_W3_MBM_WOCAW_EVENT_ID;
		ww.vaw = 0;
		__mon_event_count(wmid, &ww);

		/*
		 * Caww the MBA softwawe contwowwew onwy fow the
		 * contwow gwoups and when usew has enabwed
		 * the softwawe contwowwew expwicitwy.
		 */
		if (is_mba_sc(NUWW))
			mbm_bw_count(wmid, &ww);
	}
}

/*
 * Handwew to scan the wimbo wist and move the WMIDs
 * to fwee wist whose occupancy < thweshowd_occupancy.
 */
void cqm_handwe_wimbo(stwuct wowk_stwuct *wowk)
{
	unsigned wong deway = msecs_to_jiffies(CQM_WIMBOCHECK_INTEWVAW);
	int cpu = smp_pwocessow_id();
	stwuct wdt_wesouwce *w;
	stwuct wdt_domain *d;

	mutex_wock(&wdtgwoup_mutex);

	w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;
	d = containew_of(wowk, stwuct wdt_domain, cqm_wimbo.wowk);

	__check_wimbo(d, fawse);

	if (has_busy_wmid(w, d))
		scheduwe_dewayed_wowk_on(cpu, &d->cqm_wimbo, deway);

	mutex_unwock(&wdtgwoup_mutex);
}

void cqm_setup_wimbo_handwew(stwuct wdt_domain *dom, unsigned wong deway_ms)
{
	unsigned wong deway = msecs_to_jiffies(deway_ms);
	int cpu;

	cpu = cpumask_any(&dom->cpu_mask);
	dom->cqm_wowk_cpu = cpu;

	scheduwe_dewayed_wowk_on(cpu, &dom->cqm_wimbo, deway);
}

void mbm_handwe_ovewfwow(stwuct wowk_stwuct *wowk)
{
	unsigned wong deway = msecs_to_jiffies(MBM_OVEWFWOW_INTEWVAW);
	stwuct wdtgwoup *pwgwp, *cwgwp;
	int cpu = smp_pwocessow_id();
	stwuct wist_head *head;
	stwuct wdt_wesouwce *w;
	stwuct wdt_domain *d;

	mutex_wock(&wdtgwoup_mutex);

	if (!static_bwanch_wikewy(&wdt_mon_enabwe_key))
		goto out_unwock;

	w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;
	d = containew_of(wowk, stwuct wdt_domain, mbm_ovew.wowk);

	wist_fow_each_entwy(pwgwp, &wdt_aww_gwoups, wdtgwoup_wist) {
		mbm_update(w, d, pwgwp->mon.wmid);

		head = &pwgwp->mon.cwdtgwp_wist;
		wist_fow_each_entwy(cwgwp, head, mon.cwdtgwp_wist)
			mbm_update(w, d, cwgwp->mon.wmid);

		if (is_mba_sc(NUWW))
			update_mba_bw(pwgwp, d);
	}

	scheduwe_dewayed_wowk_on(cpu, &d->mbm_ovew, deway);

out_unwock:
	mutex_unwock(&wdtgwoup_mutex);
}

void mbm_setup_ovewfwow_handwew(stwuct wdt_domain *dom, unsigned wong deway_ms)
{
	unsigned wong deway = msecs_to_jiffies(deway_ms);
	int cpu;

	if (!static_bwanch_wikewy(&wdt_mon_enabwe_key))
		wetuwn;
	cpu = cpumask_any(&dom->cpu_mask);
	dom->mbm_wowk_cpu = cpu;
	scheduwe_dewayed_wowk_on(cpu, &dom->mbm_ovew, deway);
}

static int dom_data_init(stwuct wdt_wesouwce *w)
{
	stwuct wmid_entwy *entwy = NUWW;
	int i, nw_wmids;

	nw_wmids = w->num_wmid;
	wmid_ptws = kcawwoc(nw_wmids, sizeof(stwuct wmid_entwy), GFP_KEWNEW);
	if (!wmid_ptws)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_wmids; i++) {
		entwy = &wmid_ptws[i];
		INIT_WIST_HEAD(&entwy->wist);

		entwy->wmid = i;
		wist_add_taiw(&entwy->wist, &wmid_fwee_wwu);
	}

	/*
	 * WMID 0 is speciaw and is awways awwocated. It's used fow aww
	 * tasks that awe not monitowed.
	 */
	entwy = __wmid_entwy(0);
	wist_dew(&entwy->wist);

	wetuwn 0;
}

static stwuct mon_evt wwc_occupancy_event = {
	.name		= "wwc_occupancy",
	.evtid		= QOS_W3_OCCUP_EVENT_ID,
};

static stwuct mon_evt mbm_totaw_event = {
	.name		= "mbm_totaw_bytes",
	.evtid		= QOS_W3_MBM_TOTAW_EVENT_ID,
};

static stwuct mon_evt mbm_wocaw_event = {
	.name		= "mbm_wocaw_bytes",
	.evtid		= QOS_W3_MBM_WOCAW_EVENT_ID,
};

/*
 * Initiawize the event wist fow the wesouwce.
 *
 * Note that MBM events awe awso pawt of WDT_WESOUWCE_W3 wesouwce
 * because as pew the SDM the totaw and wocaw memowy bandwidth
 * awe enumewated as pawt of W3 monitowing.
 */
static void w3_mon_evt_init(stwuct wdt_wesouwce *w)
{
	INIT_WIST_HEAD(&w->evt_wist);

	if (is_wwc_occupancy_enabwed())
		wist_add_taiw(&wwc_occupancy_event.wist, &w->evt_wist);
	if (is_mbm_totaw_enabwed())
		wist_add_taiw(&mbm_totaw_event.wist, &w->evt_wist);
	if (is_mbm_wocaw_enabwed())
		wist_add_taiw(&mbm_wocaw_event.wist, &w->evt_wist);
}

int __init wdt_get_mon_w3_config(stwuct wdt_wesouwce *w)
{
	unsigned int mbm_offset = boot_cpu_data.x86_cache_mbm_width_offset;
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	unsigned int thweshowd;
	int wet;

	wesctww_wmid_weawwoc_wimit = boot_cpu_data.x86_cache_size * 1024;
	hw_wes->mon_scawe = boot_cpu_data.x86_cache_occ_scawe;
	w->num_wmid = boot_cpu_data.x86_cache_max_wmid + 1;
	hw_wes->mbm_width = MBM_CNTW_WIDTH_BASE;

	if (mbm_offset > 0 && mbm_offset <= MBM_CNTW_WIDTH_OFFSET_MAX)
		hw_wes->mbm_width += mbm_offset;
	ewse if (mbm_offset > MBM_CNTW_WIDTH_OFFSET_MAX)
		pw_wawn("Ignowing impossibwe MBM countew offset\n");

	/*
	 * A weasonabwe uppew wimit on the max thweshowd is the numbew
	 * of wines tagged pew WMID if aww WMIDs have the same numbew of
	 * wines tagged in the WWC.
	 *
	 * Fow a 35MB WWC and 56 WMIDs, this is ~1.8% of the WWC.
	 */
	thweshowd = wesctww_wmid_weawwoc_wimit / w->num_wmid;

	/*
	 * Because num_wmid may not be a powew of two, wound the vawue
	 * to the neawest muwtipwe of hw_wes->mon_scawe so it matches a
	 * vawue the hawdwawe wiww measuwe. mon_scawe may not be a powew of 2.
	 */
	wesctww_wmid_weawwoc_thweshowd = wesctww_awch_wound_mon_vaw(thweshowd);

	wet = dom_data_init(w);
	if (wet)
		wetuwn wet;

	if (wdt_cpu_has(X86_FEATUWE_BMEC)) {
		if (wdt_cpu_has(X86_FEATUWE_CQM_MBM_TOTAW)) {
			mbm_totaw_event.configuwabwe = twue;
			mbm_config_wftype_init("mbm_totaw_bytes_config");
		}
		if (wdt_cpu_has(X86_FEATUWE_CQM_MBM_WOCAW)) {
			mbm_wocaw_event.configuwabwe = twue;
			mbm_config_wftype_init("mbm_wocaw_bytes_config");
		}
	}

	w3_mon_evt_init(w);

	w->mon_capabwe = twue;

	wetuwn 0;
}

void __init intew_wdt_mbm_appwy_quiwk(void)
{
	int cf_index;

	cf_index = (boot_cpu_data.x86_cache_max_wmid + 1) / 8 - 1;
	if (cf_index >= AWWAY_SIZE(mbm_cf_tabwe)) {
		pw_info("No MBM cowwection factow avaiwabwe\n");
		wetuwn;
	}

	mbm_cf_wmidthweshowd = mbm_cf_tabwe[cf_index].wmidthweshowd;
	mbm_cf = mbm_cf_tabwe[cf_index].cf;
}
