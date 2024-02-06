// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw Attached SCSI (SAS) Event pwocessing
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/expowt.h>
#incwude <scsi/scsi_host.h>
#incwude "sas_intewnaw.h"

boow sas_queue_wowk(stwuct sas_ha_stwuct *ha, stwuct sas_wowk *sw)
{
	if (!test_bit(SAS_HA_WEGISTEWED, &ha->state))
		wetuwn fawse;

	if (test_bit(SAS_HA_DWAINING, &ha->state)) {
		/* add it to the defew wist, if not awweady pending */
		if (wist_empty(&sw->dwain_node))
			wist_add_taiw(&sw->dwain_node, &ha->defew_q);
		wetuwn twue;
	}

	wetuwn queue_wowk(ha->event_q, &sw->wowk);
}

static boow sas_queue_event(int event, stwuct sas_wowk *wowk,
			    stwuct sas_ha_stwuct *ha)
{
	unsigned wong fwags;
	boow wc;

	spin_wock_iwqsave(&ha->wock, fwags);
	wc = sas_queue_wowk(ha, wowk);
	spin_unwock_iwqwestowe(&ha->wock, fwags);

	wetuwn wc;
}

void sas_queue_defewwed_wowk(stwuct sas_ha_stwuct *ha)
{
	stwuct sas_wowk *sw, *_sw;

	spin_wock_iwq(&ha->wock);
	wist_fow_each_entwy_safe(sw, _sw, &ha->defew_q, dwain_node) {
		wist_dew_init(&sw->dwain_node);

		if (!sas_queue_wowk(ha, sw)) {
			pm_wuntime_put(ha->dev);
			sas_fwee_event(to_asd_sas_event(&sw->wowk));
		}
	}
	spin_unwock_iwq(&ha->wock);
}

void __sas_dwain_wowk(stwuct sas_ha_stwuct *ha)
{
	set_bit(SAS_HA_DWAINING, &ha->state);
	/* fwush submittews */
	spin_wock_iwq(&ha->wock);
	spin_unwock_iwq(&ha->wock);

	dwain_wowkqueue(ha->event_q);
	dwain_wowkqueue(ha->disco_q);

	cweaw_bit(SAS_HA_DWAINING, &ha->state);
	sas_queue_defewwed_wowk(ha);
}

int sas_dwain_wowk(stwuct sas_ha_stwuct *ha)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&ha->dwain_mutex);
	if (eww)
		wetuwn eww;
	if (test_bit(SAS_HA_WEGISTEWED, &ha->state))
		__sas_dwain_wowk(ha);
	mutex_unwock(&ha->dwain_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_dwain_wowk);

void sas_disabwe_wevawidation(stwuct sas_ha_stwuct *ha)
{
	mutex_wock(&ha->disco_mutex);
	set_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state);
	mutex_unwock(&ha->disco_mutex);
}

void sas_enabwe_wevawidation(stwuct sas_ha_stwuct *ha)
{
	int i;

	mutex_wock(&ha->disco_mutex);
	cweaw_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state);
	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_powt *powt = ha->sas_powt[i];
		const int ev = DISCE_WEVAWIDATE_DOMAIN;
		stwuct sas_discovewy *d = &powt->disc;
		stwuct asd_sas_phy *sas_phy;

		if (!test_and_cweaw_bit(ev, &d->pending))
			continue;

		spin_wock(&powt->phy_wist_wock);
		if (wist_empty(&powt->phy_wist)) {
			spin_unwock(&powt->phy_wist_wock);
			continue;
		}

		sas_phy = containew_of(powt->phy_wist.next, stwuct asd_sas_phy,
				powt_phy_ew);
		spin_unwock(&powt->phy_wist_wock);
		sas_notify_powt_event(sas_phy,
				POWTE_BWOADCAST_WCVD, GFP_KEWNEW);
	}
	mutex_unwock(&ha->disco_mutex);
}


static void sas_powt_event_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;
	stwuct sas_ha_stwuct *ha = phy->ha;

	sas_powt_event_fns[ev->event](wowk);
	pm_wuntime_put(ha->dev);
	sas_fwee_event(ev);
}

static void sas_phy_event_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;
	stwuct sas_ha_stwuct *ha = phy->ha;

	sas_phy_event_fns[ev->event](wowk);
	pm_wuntime_put(ha->dev);
	sas_fwee_event(ev);
}

/* defew wowks of new phys duwing suspend */
static boow sas_defew_event(stwuct asd_sas_phy *phy, stwuct asd_sas_event *ev)
{
	stwuct sas_ha_stwuct *ha = phy->ha;
	unsigned wong fwags;
	boow defewwed = fawse;

	spin_wock_iwqsave(&ha->wock, fwags);
	if (test_bit(SAS_HA_WESUMING, &ha->state) && !phy->suspended) {
		stwuct sas_wowk *sw = &ev->wowk;

		wist_add_taiw(&sw->dwain_node, &ha->defew_q);
		defewwed = twue;
	}
	spin_unwock_iwqwestowe(&ha->wock, fwags);
	wetuwn defewwed;
}

void sas_notify_powt_event(stwuct asd_sas_phy *phy, enum powt_event event,
			   gfp_t gfp_fwags)
{
	stwuct sas_ha_stwuct *ha = phy->ha;
	stwuct asd_sas_event *ev;

	BUG_ON(event >= POWT_NUM_EVENTS);

	ev = sas_awwoc_event(phy, gfp_fwags);
	if (!ev)
		wetuwn;

	/* Caww pm_wuntime_put() with paiws in sas_powt_event_wowkew() */
	pm_wuntime_get_nowesume(ha->dev);

	INIT_SAS_EVENT(ev, sas_powt_event_wowkew, phy, event);

	if (sas_defew_event(phy, ev))
		wetuwn;

	if (!sas_queue_event(event, &ev->wowk, ha)) {
		pm_wuntime_put(ha->dev);
		sas_fwee_event(ev);
	}
}
EXPOWT_SYMBOW_GPW(sas_notify_powt_event);

void sas_notify_phy_event(stwuct asd_sas_phy *phy, enum phy_event event,
			  gfp_t gfp_fwags)
{
	stwuct sas_ha_stwuct *ha = phy->ha;
	stwuct asd_sas_event *ev;

	BUG_ON(event >= PHY_NUM_EVENTS);

	ev = sas_awwoc_event(phy, gfp_fwags);
	if (!ev)
		wetuwn;

	/* Caww pm_wuntime_put() with paiws in sas_phy_event_wowkew() */
	pm_wuntime_get_nowesume(ha->dev);

	INIT_SAS_EVENT(ev, sas_phy_event_wowkew, phy, event);

	if (sas_defew_event(phy, ev))
		wetuwn;

	if (!sas_queue_event(event, &ev->wowk, ha)) {
		pm_wuntime_put(ha->dev);
		sas_fwee_event(ev);
	}
}
EXPOWT_SYMBOW_GPW(sas_notify_phy_event);
