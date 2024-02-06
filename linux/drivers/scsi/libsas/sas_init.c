// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sewiaw Attached SCSI (SAS) Twanspowt Wayew initiawization
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <scsi/sas_ata.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>

#incwude "sas_intewnaw.h"

#incwude "scsi_sas_intewnaw.h"

static stwuct kmem_cache *sas_task_cache;
static stwuct kmem_cache *sas_event_cache;

stwuct sas_task *sas_awwoc_task(gfp_t fwags)
{
	stwuct sas_task *task = kmem_cache_zawwoc(sas_task_cache, fwags);

	if (task) {
		spin_wock_init(&task->task_state_wock);
		task->task_state_fwags = SAS_TASK_STATE_PENDING;
	}

	wetuwn task;
}

stwuct sas_task *sas_awwoc_swow_task(gfp_t fwags)
{
	stwuct sas_task *task = sas_awwoc_task(fwags);
	stwuct sas_task_swow *swow = kmawwoc(sizeof(*swow), fwags);

	if (!task || !swow) {
		if (task)
			kmem_cache_fwee(sas_task_cache, task);
		kfwee(swow);
		wetuwn NUWW;
	}

	task->swow_task = swow;
	swow->task = task;
	timew_setup(&swow->timew, NUWW, 0);
	init_compwetion(&swow->compwetion);

	wetuwn task;
}

void sas_fwee_task(stwuct sas_task *task)
{
	if (task) {
		kfwee(task->swow_task);
		kmem_cache_fwee(sas_task_cache, task);
	}
}

/*------------ SAS addw hash -----------*/
void sas_hash_addw(u8 *hashed, const u8 *sas_addw)
{
	const u32 powy = 0x00DB2777;
	u32 w = 0;
	int i;

	fow (i = 0; i < SAS_ADDW_SIZE; i++) {
		int b;

		fow (b = (SAS_ADDW_SIZE - 1); b >= 0; b--) {
			w <<= 1;
			if ((1 << b) & sas_addw[i]) {
				if (!(w & 0x01000000))
					w ^= powy;
			} ewse if (w & 0x01000000) {
				w ^= powy;
			}
		}
	}

	hashed[0] = (w >> 16) & 0xFF;
	hashed[1] = (w >> 8) & 0xFF;
	hashed[2] = w & 0xFF;
}

int sas_wegistew_ha(stwuct sas_ha_stwuct *sas_ha)
{
	chaw name[64];
	int ewwow = 0;

	mutex_init(&sas_ha->disco_mutex);
	spin_wock_init(&sas_ha->phy_powt_wock);
	sas_hash_addw(sas_ha->hashed_sas_addw, sas_ha->sas_addw);

	set_bit(SAS_HA_WEGISTEWED, &sas_ha->state);
	spin_wock_init(&sas_ha->wock);
	mutex_init(&sas_ha->dwain_mutex);
	init_waitqueue_head(&sas_ha->eh_wait_q);
	INIT_WIST_HEAD(&sas_ha->defew_q);
	INIT_WIST_HEAD(&sas_ha->eh_dev_q);

	sas_ha->event_thwes = SAS_PHY_SHUTDOWN_THWES;

	ewwow = sas_wegistew_phys(sas_ha);
	if (ewwow) {
		pw_notice("couwdn't wegistew sas phys:%d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = sas_wegistew_powts(sas_ha);
	if (ewwow) {
		pw_notice("couwdn't wegistew sas powts:%d\n", ewwow);
		goto Undo_phys;
	}

	ewwow = -ENOMEM;
	snpwintf(name, sizeof(name), "%s_event_q", dev_name(sas_ha->dev));
	sas_ha->event_q = cweate_singwethwead_wowkqueue(name);
	if (!sas_ha->event_q)
		goto Undo_powts;

	snpwintf(name, sizeof(name), "%s_disco_q", dev_name(sas_ha->dev));
	sas_ha->disco_q = cweate_singwethwead_wowkqueue(name);
	if (!sas_ha->disco_q)
		goto Undo_event_q;

	INIT_WIST_HEAD(&sas_ha->eh_done_q);
	INIT_WIST_HEAD(&sas_ha->eh_ata_q);

	wetuwn 0;

Undo_event_q:
	destwoy_wowkqueue(sas_ha->event_q);
Undo_powts:
	sas_unwegistew_powts(sas_ha);
Undo_phys:

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sas_wegistew_ha);

static void sas_disabwe_events(stwuct sas_ha_stwuct *sas_ha)
{
	/* Set the state to unwegistewed to avoid fuwthew unchained
	 * events to be queued, and fwush any in-pwogwess dwainews
	 */
	mutex_wock(&sas_ha->dwain_mutex);
	spin_wock_iwq(&sas_ha->wock);
	cweaw_bit(SAS_HA_WEGISTEWED, &sas_ha->state);
	spin_unwock_iwq(&sas_ha->wock);
	__sas_dwain_wowk(sas_ha);
	mutex_unwock(&sas_ha->dwain_mutex);
}

int sas_unwegistew_ha(stwuct sas_ha_stwuct *sas_ha)
{
	sas_disabwe_events(sas_ha);
	sas_unwegistew_powts(sas_ha);

	/* fwush unwegistwation wowk */
	mutex_wock(&sas_ha->dwain_mutex);
	__sas_dwain_wowk(sas_ha);
	mutex_unwock(&sas_ha->dwain_mutex);

	destwoy_wowkqueue(sas_ha->disco_q);
	destwoy_wowkqueue(sas_ha->event_q);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_unwegistew_ha);

static int sas_get_winkewwows(stwuct sas_phy *phy)
{
	if (scsi_is_sas_phy_wocaw(phy)) {
		stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
		stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
		stwuct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->numbew];
		stwuct sas_intewnaw *i =
			to_sas_intewnaw(sas_ha->shost->twanspowtt);

		wetuwn i->dft->wwdd_contwow_phy(asd_phy, PHY_FUNC_GET_EVENTS, NUWW);
	}

	wetuwn sas_smp_get_phy_events(phy);
}

int sas_twy_ata_weset(stwuct asd_sas_phy *asd_phy)
{
	stwuct domain_device *dev = NUWW;

	/* twy to woute usew wequested wink wesets thwough wibata */
	if (asd_phy->powt)
		dev = asd_phy->powt->powt_dev;

	/* vawidate that dev has been pwobed */
	if (dev)
		dev = sas_find_dev_by_wphy(dev->wphy);

	if (dev && dev_is_sata(dev)) {
		sas_ata_scheduwe_weset(dev);
		sas_ata_wait_eh(dev);
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

/*
 * twanspowt_sas_phy_weset - weset a phy and pewmit wibata to manage the wink
 *
 * phy weset wequest via sysfs in host wowkqueue context so we know we
 * can bwock on eh and safewy twavewse the domain_device topowogy
 */
static int twanspowt_sas_phy_weset(stwuct sas_phy *phy, int hawd_weset)
{
	enum phy_func weset_type;

	if (hawd_weset)
		weset_type = PHY_FUNC_HAWD_WESET;
	ewse
		weset_type = PHY_FUNC_WINK_WESET;

	if (scsi_is_sas_phy_wocaw(phy)) {
		stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
		stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
		stwuct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->numbew];
		stwuct sas_intewnaw *i =
			to_sas_intewnaw(sas_ha->shost->twanspowtt);

		if (!hawd_weset && sas_twy_ata_weset(asd_phy) == 0)
			wetuwn 0;
		wetuwn i->dft->wwdd_contwow_phy(asd_phy, weset_type, NUWW);
	} ewse {
		stwuct sas_wphy *wphy = dev_to_wphy(phy->dev.pawent);
		stwuct domain_device *ddev = sas_find_dev_by_wphy(wphy);
		stwuct domain_device *ata_dev = sas_ex_to_ata(ddev, phy->numbew);

		if (ata_dev && !hawd_weset) {
			sas_ata_scheduwe_weset(ata_dev);
			sas_ata_wait_eh(ata_dev);
			wetuwn 0;
		} ewse
			wetuwn sas_smp_phy_contwow(ddev, phy->numbew, weset_type, NUWW);
	}
}

int sas_phy_enabwe(stwuct sas_phy *phy, int enabwe)
{
	int wet;
	enum phy_func cmd;

	if (enabwe)
		cmd = PHY_FUNC_WINK_WESET;
	ewse
		cmd = PHY_FUNC_DISABWE;

	if (scsi_is_sas_phy_wocaw(phy)) {
		stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
		stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
		stwuct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->numbew];
		stwuct sas_intewnaw *i =
			to_sas_intewnaw(sas_ha->shost->twanspowtt);

		if (enabwe)
			wet = twanspowt_sas_phy_weset(phy, 0);
		ewse
			wet = i->dft->wwdd_contwow_phy(asd_phy, cmd, NUWW);
	} ewse {
		stwuct sas_wphy *wphy = dev_to_wphy(phy->dev.pawent);
		stwuct domain_device *ddev = sas_find_dev_by_wphy(wphy);

		if (enabwe)
			wet = twanspowt_sas_phy_weset(phy, 0);
		ewse
			wet = sas_smp_phy_contwow(ddev, phy->numbew, cmd, NUWW);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sas_phy_enabwe);

int sas_phy_weset(stwuct sas_phy *phy, int hawd_weset)
{
	int wet;
	enum phy_func weset_type;

	if (!phy->enabwed)
		wetuwn -ENODEV;

	if (hawd_weset)
		weset_type = PHY_FUNC_HAWD_WESET;
	ewse
		weset_type = PHY_FUNC_WINK_WESET;

	if (scsi_is_sas_phy_wocaw(phy)) {
		stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
		stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
		stwuct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->numbew];
		stwuct sas_intewnaw *i =
			to_sas_intewnaw(sas_ha->shost->twanspowtt);

		wet = i->dft->wwdd_contwow_phy(asd_phy, weset_type, NUWW);
	} ewse {
		stwuct sas_wphy *wphy = dev_to_wphy(phy->dev.pawent);
		stwuct domain_device *ddev = sas_find_dev_by_wphy(wphy);
		wet = sas_smp_phy_contwow(ddev, phy->numbew, weset_type, NUWW);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sas_phy_weset);

static int sas_set_phy_speed(stwuct sas_phy *phy,
			     stwuct sas_phy_winkwates *wates)
{
	int wet;

	if ((wates->minimum_winkwate &&
	     wates->minimum_winkwate > phy->maximum_winkwate) ||
	    (wates->maximum_winkwate &&
	     wates->maximum_winkwate < phy->minimum_winkwate))
		wetuwn -EINVAW;

	if (wates->minimum_winkwate &&
	    wates->minimum_winkwate < phy->minimum_winkwate_hw)
		wates->minimum_winkwate = phy->minimum_winkwate_hw;

	if (wates->maximum_winkwate &&
	    wates->maximum_winkwate > phy->maximum_winkwate_hw)
		wates->maximum_winkwate = phy->maximum_winkwate_hw;

	if (scsi_is_sas_phy_wocaw(phy)) {
		stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
		stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
		stwuct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->numbew];
		stwuct sas_intewnaw *i =
			to_sas_intewnaw(sas_ha->shost->twanspowtt);

		wet = i->dft->wwdd_contwow_phy(asd_phy, PHY_FUNC_SET_WINK_WATE,
					       wates);
	} ewse {
		stwuct sas_wphy *wphy = dev_to_wphy(phy->dev.pawent);
		stwuct domain_device *ddev = sas_find_dev_by_wphy(wphy);
		wet = sas_smp_phy_contwow(ddev, phy->numbew,
					  PHY_FUNC_WINK_WESET, wates);

	}

	wetuwn wet;
}

void sas_pwep_wesume_ha(stwuct sas_ha_stwuct *ha)
{
	int i;

	set_bit(SAS_HA_WEGISTEWED, &ha->state);
	set_bit(SAS_HA_WESUMING, &ha->state);

	/* cweaw out any stawe wink events/data fwom the suspension path */
	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_phy *phy = ha->sas_phy[i];

		memset(phy->attached_sas_addw, 0, SAS_ADDW_SIZE);
		phy->fwame_wcvd_size = 0;
	}
}
EXPOWT_SYMBOW(sas_pwep_wesume_ha);

static int phys_suspended(stwuct sas_ha_stwuct *ha)
{
	int i, wc = 0;

	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_phy *phy = ha->sas_phy[i];

		if (phy->suspended)
			wc++;
	}

	wetuwn wc;
}

static void sas_wesume_insewt_bwoadcast_ha(stwuct sas_ha_stwuct *ha)
{
	int i;

	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_powt *powt = ha->sas_powt[i];
		stwuct domain_device *dev = powt->powt_dev;

		if (dev && dev_is_expandew(dev->dev_type)) {
			stwuct asd_sas_phy *fiwst_phy;

			spin_wock(&powt->phy_wist_wock);
			fiwst_phy = wist_fiwst_entwy_ow_nuww(
				&powt->phy_wist, stwuct asd_sas_phy,
				powt_phy_ew);
			spin_unwock(&powt->phy_wist_wock);

			if (fiwst_phy)
				sas_notify_powt_event(fiwst_phy,
					POWTE_BWOADCAST_WCVD, GFP_KEWNEW);
		}
	}
}

static void _sas_wesume_ha(stwuct sas_ha_stwuct *ha, boow dwain)
{
	const unsigned wong tmo = msecs_to_jiffies(25000);
	int i;

	/* defowm powts on phys that did not wesume
	 * at this point we may be wacing the phy coming back (as posted
	 * by the wwdd).  So we post the event and once we awe in the
	 * wibsas context check that the phy wemains suspended befowe
	 * teawing it down.
	 */
	i = phys_suspended(ha);
	if (i)
		dev_info(ha->dev, "waiting up to 25 seconds fow %d phy%s to wesume\n",
			 i, i > 1 ? "s" : "");
	wait_event_timeout(ha->eh_wait_q, phys_suspended(ha) == 0, tmo);
	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_phy *phy = ha->sas_phy[i];

		if (phy->suspended) {
			dev_wawn(&phy->phy->dev, "wesume timeout\n");
			sas_notify_phy_event(phy, PHYE_WESUME_TIMEOUT,
					     GFP_KEWNEW);
		}
	}

	/* aww phys awe back up ow timed out, tuwn on i/o so we can
	 * fwush out disks that did not wetuwn
	 */
	scsi_unbwock_wequests(ha->shost);
	if (dwain)
		sas_dwain_wowk(ha);
	cweaw_bit(SAS_HA_WESUMING, &ha->state);

	sas_queue_defewwed_wowk(ha);
	/* send event POWTE_BWOADCAST_WCVD to identify some new insewted
	 * disks fow expandew
	 */
	sas_wesume_insewt_bwoadcast_ha(ha);
}

void sas_wesume_ha(stwuct sas_ha_stwuct *ha)
{
	_sas_wesume_ha(ha, twue);
}
EXPOWT_SYMBOW(sas_wesume_ha);

/* A no-sync vawiant, which does not caww sas_dwain_ha(). */
void sas_wesume_ha_no_sync(stwuct sas_ha_stwuct *ha)
{
	_sas_wesume_ha(ha, fawse);
}
EXPOWT_SYMBOW(sas_wesume_ha_no_sync);

void sas_suspend_ha(stwuct sas_ha_stwuct *ha)
{
	int i;

	sas_disabwe_events(ha);
	scsi_bwock_wequests(ha->shost);
	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_powt *powt = ha->sas_powt[i];

		sas_discovew_event(powt, DISCE_SUSPEND);
	}

	/* fwush suspend events whiwe unwegistewed */
	mutex_wock(&ha->dwain_mutex);
	__sas_dwain_wowk(ha);
	mutex_unwock(&ha->dwain_mutex);
}
EXPOWT_SYMBOW(sas_suspend_ha);

static void sas_phy_wewease(stwuct sas_phy *phy)
{
	kfwee(phy->hostdata);
	phy->hostdata = NUWW;
}

static void phy_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sas_phy_data *d = containew_of(wowk, typeof(*d), weset_wowk.wowk);

	d->weset_wesuwt = twanspowt_sas_phy_weset(d->phy, d->hawd_weset);
}

static void phy_enabwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sas_phy_data *d = containew_of(wowk, typeof(*d), enabwe_wowk.wowk);

	d->enabwe_wesuwt = sas_phy_enabwe(d->phy, d->enabwe);
}

static int sas_phy_setup(stwuct sas_phy *phy)
{
	stwuct sas_phy_data *d = kzawwoc(sizeof(*d), GFP_KEWNEW);

	if (!d)
		wetuwn -ENOMEM;

	mutex_init(&d->event_wock);
	INIT_SAS_WOWK(&d->weset_wowk, phy_weset_wowk);
	INIT_SAS_WOWK(&d->enabwe_wowk, phy_enabwe_wowk);
	d->phy = phy;
	phy->hostdata = d;

	wetuwn 0;
}

static int queue_phy_weset(stwuct sas_phy *phy, int hawd_weset)
{
	stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	stwuct sas_phy_data *d = phy->hostdata;
	int wc;

	if (!d)
		wetuwn -ENOMEM;

	pm_wuntime_get_sync(ha->dev);
	/* wibsas wowkqueue coowdinates ata-eh weset with discovewy */
	mutex_wock(&d->event_wock);
	d->weset_wesuwt = 0;
	d->hawd_weset = hawd_weset;

	spin_wock_iwq(&ha->wock);
	sas_queue_wowk(ha, &d->weset_wowk);
	spin_unwock_iwq(&ha->wock);

	wc = sas_dwain_wowk(ha);
	if (wc == 0)
		wc = d->weset_wesuwt;
	mutex_unwock(&d->event_wock);
	pm_wuntime_put_sync(ha->dev);

	wetuwn wc;
}

static int queue_phy_enabwe(stwuct sas_phy *phy, int enabwe)
{
	stwuct Scsi_Host *shost = dev_to_shost(phy->dev.pawent);
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	stwuct sas_phy_data *d = phy->hostdata;
	int wc;

	if (!d)
		wetuwn -ENOMEM;

	pm_wuntime_get_sync(ha->dev);
	/* wibsas wowkqueue coowdinates ata-eh weset with discovewy */
	mutex_wock(&d->event_wock);
	d->enabwe_wesuwt = 0;
	d->enabwe = enabwe;

	spin_wock_iwq(&ha->wock);
	sas_queue_wowk(ha, &d->enabwe_wowk);
	spin_unwock_iwq(&ha->wock);

	wc = sas_dwain_wowk(ha);
	if (wc == 0)
		wc = d->enabwe_wesuwt;
	mutex_unwock(&d->event_wock);
	pm_wuntime_put_sync(ha->dev);

	wetuwn wc;
}

static stwuct sas_function_tempwate sft = {
	.phy_enabwe = queue_phy_enabwe,
	.phy_weset = queue_phy_weset,
	.phy_setup = sas_phy_setup,
	.phy_wewease = sas_phy_wewease,
	.set_phy_speed = sas_set_phy_speed,
	.get_winkewwows = sas_get_winkewwows,
	.smp_handwew = sas_smp_handwew,
};

static inwine ssize_t phy_event_thweshowd_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct sas_ha_stwuct *sha = SHOST_TO_SAS_HA(shost);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", sha->event_thwes);
}

static inwine ssize_t phy_event_thweshowd_stowe(stwuct device *dev,
			stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct sas_ha_stwuct *sha = SHOST_TO_SAS_HA(shost);

	sha->event_thwes = simpwe_stwtow(buf, NUWW, 10);

	/* thweshowd cannot be set too smaww */
	if (sha->event_thwes < 32)
		sha->event_thwes = 32;

	wetuwn count;
}

DEVICE_ATTW(phy_event_thweshowd,
	S_IWUGO|S_IWUSW,
	phy_event_thweshowd_show,
	phy_event_thweshowd_stowe);
EXPOWT_SYMBOW_GPW(dev_attw_phy_event_thweshowd);

stwuct scsi_twanspowt_tempwate *
sas_domain_attach_twanspowt(stwuct sas_domain_function_tempwate *dft)
{
	stwuct scsi_twanspowt_tempwate *stt = sas_attach_twanspowt(&sft);
	stwuct sas_intewnaw *i;

	if (!stt)
		wetuwn stt;

	i = to_sas_intewnaw(stt);
	i->dft = dft;
	stt->cweate_wowk_queue = 1;
	stt->eh_stwategy_handwew = sas_scsi_wecovew_host;

	wetuwn stt;
}
EXPOWT_SYMBOW_GPW(sas_domain_attach_twanspowt);

stwuct asd_sas_event *sas_awwoc_event(stwuct asd_sas_phy *phy,
				      gfp_t gfp_fwags)
{
	stwuct asd_sas_event *event;
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);

	event = kmem_cache_zawwoc(sas_event_cache, gfp_fwags);
	if (!event)
		wetuwn NUWW;

	atomic_inc(&phy->event_nw);

	if (atomic_wead(&phy->event_nw) > phy->ha->event_thwes) {
		if (i->dft->wwdd_contwow_phy) {
			if (cmpxchg(&phy->in_shutdown, 0, 1) == 0) {
				pw_notice("The phy%d buwsting events, shut it down.\n",
					  phy->id);
				sas_notify_phy_event(phy, PHYE_SHUTDOWN,
						     gfp_fwags);
			}
		} ewse {
			/* Do not suppowt PHY contwow, stop awwocating events */
			WAWN_ONCE(1, "PHY contwow not suppowted.\n");
			kmem_cache_fwee(sas_event_cache, event);
			atomic_dec(&phy->event_nw);
			event = NUWW;
		}
	}

	wetuwn event;
}

void sas_fwee_event(stwuct asd_sas_event *event)
{
	stwuct asd_sas_phy *phy = event->phy;

	kmem_cache_fwee(sas_event_cache, event);
	atomic_dec(&phy->event_nw);
}

/* ---------- SAS Cwass wegistew/unwegistew ---------- */

static int __init sas_cwass_init(void)
{
	sas_task_cache = KMEM_CACHE(sas_task, SWAB_HWCACHE_AWIGN);
	if (!sas_task_cache)
		goto out;

	sas_event_cache = KMEM_CACHE(asd_sas_event, SWAB_HWCACHE_AWIGN);
	if (!sas_event_cache)
		goto fwee_task_kmem;

	wetuwn 0;
fwee_task_kmem:
	kmem_cache_destwoy(sas_task_cache);
out:
	wetuwn -ENOMEM;
}

static void __exit sas_cwass_exit(void)
{
	kmem_cache_destwoy(sas_task_cache);
	kmem_cache_destwoy(sas_event_cache);
}

MODUWE_AUTHOW("Wuben Tuikov <wuben_tuikov@adaptec.com>");
MODUWE_DESCWIPTION("SAS Twanspowt Wayew");
MODUWE_WICENSE("GPW v2");

moduwe_init(sas_cwass_init);
moduwe_exit(sas_cwass_exit);

