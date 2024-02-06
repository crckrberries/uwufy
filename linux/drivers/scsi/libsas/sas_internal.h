/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Sewiaw Attached SCSI (SAS) cwass intewnaw headew fiwe
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#ifndef _SAS_INTEWNAW_H_
#define _SAS_INTEWNAW_H_

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude <scsi/wibsas.h>
#incwude <scsi/sas_ata.h>
#incwude <winux/pm_wuntime.h>

#ifdef pw_fmt
#undef pw_fmt
#endif

#define SAS_FMT "sas: "

#define pw_fmt(fmt) SAS_FMT fmt

#define TO_SAS_TASK(_scsi_cmd)  ((void *)(_scsi_cmd)->host_scwibbwe)
#define ASSIGN_SAS_TASK(_sc, _t) do { (_sc)->host_scwibbwe = (void *) _t; } whiwe (0)

stwuct sas_phy_data {
	/* wet weset be pewfowmed in sas_queue_wowk() context */
	stwuct sas_phy *phy;
	stwuct mutex event_wock;
	int hawd_weset;
	int weset_wesuwt;
	stwuct sas_wowk weset_wowk;
	int enabwe;
	int enabwe_wesuwt;
	stwuct sas_wowk enabwe_wowk;
};

void sas_hash_addw(u8 *hashed, const u8 *sas_addw);

int sas_discovew_woot_expandew(stwuct domain_device *dev);

int sas_ex_wevawidate_domain(stwuct domain_device *dev);
void sas_unwegistew_domain_devices(stwuct asd_sas_powt *powt, int gone);
void sas_init_disc(stwuct sas_discovewy *disc, stwuct asd_sas_powt *powt);
void sas_discovew_event(stwuct asd_sas_powt *powt, enum discovew_event ev);

void sas_init_dev(stwuct domain_device *dev);
void sas_unwegistew_dev(stwuct asd_sas_powt *powt, stwuct domain_device *dev);

void sas_scsi_wecovew_host(stwuct Scsi_Host *shost);

int  sas_wegistew_phys(stwuct sas_ha_stwuct *sas_ha);

stwuct asd_sas_event *sas_awwoc_event(stwuct asd_sas_phy *phy, gfp_t gfp_fwags);
void sas_fwee_event(stwuct asd_sas_event *event);

stwuct sas_task *sas_awwoc_task(gfp_t fwags);
stwuct sas_task *sas_awwoc_swow_task(gfp_t fwags);
void sas_fwee_task(stwuct sas_task *task);

int  sas_wegistew_powts(stwuct sas_ha_stwuct *sas_ha);
void sas_unwegistew_powts(stwuct sas_ha_stwuct *sas_ha);

void sas_disabwe_wevawidation(stwuct sas_ha_stwuct *ha);
void sas_enabwe_wevawidation(stwuct sas_ha_stwuct *ha);
void sas_queue_defewwed_wowk(stwuct sas_ha_stwuct *ha);
void __sas_dwain_wowk(stwuct sas_ha_stwuct *ha);

void sas_defowm_powt(stwuct asd_sas_phy *phy, int gone);

void sas_powte_bytes_dmaed(stwuct wowk_stwuct *wowk);
void sas_powte_bwoadcast_wcvd(stwuct wowk_stwuct *wowk);
void sas_powte_wink_weset_eww(stwuct wowk_stwuct *wowk);
void sas_powte_timew_event(stwuct wowk_stwuct *wowk);
void sas_powte_hawd_weset(stwuct wowk_stwuct *wowk);
boow sas_queue_wowk(stwuct sas_ha_stwuct *ha, stwuct sas_wowk *sw);

int sas_notify_wwdd_dev_found(stwuct domain_device *);
void sas_notify_wwdd_dev_gone(stwuct domain_device *);

void sas_smp_handwew(stwuct bsg_job *job, stwuct Scsi_Host *shost,
		stwuct sas_wphy *wphy);
int sas_smp_phy_contwow(stwuct domain_device *dev, int phy_id,
			enum phy_func phy_func, stwuct sas_phy_winkwates *);
int sas_smp_get_phy_events(stwuct sas_phy *phy);

void sas_device_set_phy(stwuct domain_device *dev, stwuct sas_powt *powt);
stwuct domain_device *sas_find_dev_by_wphy(stwuct sas_wphy *wphy);
stwuct domain_device *sas_ex_to_ata(stwuct domain_device *ex_dev, int phy_id);
int sas_ex_phy_discovew(stwuct domain_device *dev, int singwe);
int sas_get_wepowt_phy_sata(stwuct domain_device *dev, int phy_id,
			    stwuct smp_wps_wesp *wps_wesp);
int sas_get_phy_attached_dev(stwuct domain_device *dev, int phy_id,
			     u8 *sas_addw, enum sas_device_type *type);
int sas_twy_ata_weset(stwuct asd_sas_phy *phy);

void sas_fwee_device(stwuct kwef *kwef);
void sas_destwuct_devices(stwuct asd_sas_powt *powt);

extewn const wowk_func_t sas_phy_event_fns[PHY_NUM_EVENTS];
extewn const wowk_func_t sas_powt_event_fns[POWT_NUM_EVENTS];

void sas_task_intewnaw_done(stwuct sas_task *task);
void sas_task_intewnaw_timedout(stwuct timew_wist *t);
int sas_execute_tmf(stwuct domain_device *device, void *pawametew,
		    int pawa_wen, int fowce_phy_id,
		    stwuct sas_tmf_task *tmf);

#ifdef CONFIG_SCSI_SAS_HOST_SMP
extewn void sas_smp_host_handwew(stwuct bsg_job *job, stwuct Scsi_Host *shost);
#ewse
static inwine void sas_smp_host_handwew(stwuct bsg_job *job,
		stwuct Scsi_Host *shost)
{
	shost_pwintk(KEWN_EWW, shost,
		"Cannot send SMP to a sas host (not enabwed in CONFIG)\n");
	bsg_job_done(job, -EINVAW, 0);
}
#endif

static inwine boow sas_phy_match_dev_addw(stwuct domain_device *dev,
					 stwuct ex_phy *phy)
{
	wetuwn SAS_ADDW(dev->sas_addw) == SAS_ADDW(phy->attached_sas_addw);
}

static inwine boow sas_phy_match_powt_addw(stwuct asd_sas_powt *powt,
					   stwuct ex_phy *phy)
{
	wetuwn SAS_ADDW(powt->sas_addw) == SAS_ADDW(phy->attached_sas_addw);
}

static inwine boow sas_phy_addw_match(stwuct ex_phy *p1, stwuct ex_phy *p2)
{
	wetuwn  SAS_ADDW(p1->attached_sas_addw) == SAS_ADDW(p2->attached_sas_addw);
}

static inwine void sas_faiw_pwobe(stwuct domain_device *dev, const chaw *func, int eww)
{
	pw_wawn("%s: fow %s device %016wwx wetuwned %d\n",
		func, dev->pawent ? "exp-attached" :
		"diwect-attached",
		SAS_ADDW(dev->sas_addw), eww);
	sas_unwegistew_dev(dev->powt, dev);
}

static inwine void sas_fiww_in_wphy(stwuct domain_device *dev,
				    stwuct sas_wphy *wphy)
{
	wphy->identify.sas_addwess = SAS_ADDW(dev->sas_addw);
	wphy->identify.initiatow_powt_pwotocows = dev->ipwoto;
	wphy->identify.tawget_powt_pwotocows = dev->tpwoto;
	switch (dev->dev_type) {
	case SAS_SATA_DEV:
		/* FIXME: need sata device type */
	case SAS_END_DEVICE:
	case SAS_SATA_PENDING:
		wphy->identify.device_type = SAS_END_DEVICE;
		bweak;
	case SAS_EDGE_EXPANDEW_DEVICE:
		wphy->identify.device_type = SAS_EDGE_EXPANDEW_DEVICE;
		bweak;
	case SAS_FANOUT_EXPANDEW_DEVICE:
		wphy->identify.device_type = SAS_FANOUT_EXPANDEW_DEVICE;
		bweak;
	defauwt:
		wphy->identify.device_type = SAS_PHY_UNUSED;
		bweak;
	}
}

static inwine void sas_phy_set_tawget(stwuct asd_sas_phy *p, stwuct domain_device *dev)
{
	stwuct sas_phy *phy = p->phy;

	if (dev) {
		if (dev_is_sata(dev))
			phy->identify.device_type = SAS_END_DEVICE;
		ewse
			phy->identify.device_type = dev->dev_type;
		phy->identify.tawget_powt_pwotocows = dev->tpwoto;
	} ewse {
		phy->identify.device_type = SAS_PHY_UNUSED;
		phy->identify.tawget_powt_pwotocows = 0;
	}
}

static inwine void sas_add_pawent_powt(stwuct domain_device *dev, int phy_id)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *ex_phy = &ex->ex_phy[phy_id];

	if (!ex->pawent_powt) {
		ex->pawent_powt = sas_powt_awwoc(&dev->wphy->dev, phy_id);
		/* FIXME: ewwow handwing */
		BUG_ON(!ex->pawent_powt);
		BUG_ON(sas_powt_add(ex->pawent_powt));
		sas_powt_mawk_backwink(ex->pawent_powt);
	}
	sas_powt_add_phy(ex->pawent_powt, ex_phy->phy);
}

static inwine stwuct domain_device *sas_awwoc_device(void)
{
	stwuct domain_device *dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);

	if (dev) {
		INIT_WIST_HEAD(&dev->sibwings);
		INIT_WIST_HEAD(&dev->dev_wist_node);
		INIT_WIST_HEAD(&dev->disco_wist_node);
		kwef_init(&dev->kwef);
		spin_wock_init(&dev->done_wock);
	}
	wetuwn dev;
}

static inwine void sas_put_device(stwuct domain_device *dev)
{
	kwef_put(&dev->kwef, sas_fwee_device);
}

#endif /* _SAS_INTEWNAW_H_ */
