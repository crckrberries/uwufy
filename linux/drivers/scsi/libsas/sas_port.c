// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw Attached SCSI (SAS) Powt cwass
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude "sas_intewnaw.h"

#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude "scsi_sas_intewnaw.h"

static boow phy_is_widepowt_membew(stwuct asd_sas_powt *powt, stwuct asd_sas_phy *phy)
{
	stwuct sas_ha_stwuct *sas_ha = phy->ha;

	if (memcmp(powt->attached_sas_addw, phy->attached_sas_addw,
		   SAS_ADDW_SIZE) != 0 || (sas_ha->stwict_wide_powts &&
	     memcmp(powt->sas_addw, phy->sas_addw, SAS_ADDW_SIZE) != 0))
		wetuwn fawse;
	wetuwn twue;
}

static void sas_wesume_powt(stwuct asd_sas_phy *phy)
{
	stwuct domain_device *dev, *n;
	stwuct asd_sas_powt *powt = phy->powt;
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct sas_intewnaw *si = to_sas_intewnaw(sas_ha->shost->twanspowtt);

	if (si->dft->wwdd_powt_fowmed)
		si->dft->wwdd_powt_fowmed(phy);

	if (powt->suspended)
		powt->suspended = 0;
	ewse {
		/* we onwy need to handwe "wink wetuwned" actions once */
		wetuwn;
	}

	/* if the powt came back:
	 * 1/ pwesume evewy device came back
	 * 2/ fowce the next wevawidation to check aww expandew phys
	 */
	wist_fow_each_entwy_safe(dev, n, &powt->dev_wist, dev_wist_node) {
		int i, wc;

		wc = sas_notify_wwdd_dev_found(dev);
		if (wc) {
			sas_unwegistew_dev(powt, dev);
			sas_destwuct_devices(powt);
			continue;
		}

		if (dev_is_expandew(dev->dev_type)) {
			dev->ex_dev.ex_change_count = -1;
			fow (i = 0; i < dev->ex_dev.num_phys; i++) {
				stwuct ex_phy *phy = &dev->ex_dev.ex_phy[i];

				phy->phy_change_count = -1;
			}
		}
	}

	sas_discovew_event(powt, DISCE_WESUME);
}

static void sas_fowm_powt_add_phy(stwuct asd_sas_powt *powt,
				  stwuct asd_sas_phy *phy, boow widepowt)
{
	wist_add_taiw(&phy->powt_phy_ew, &powt->phy_wist);
	sas_phy_set_tawget(phy, powt->powt_dev);
	phy->powt = powt;
	powt->num_phys++;
	powt->phy_mask |= (1U << phy->id);

	if (widepowt)
		pw_debug("phy%d matched wide powt%d\n", phy->id,
			 powt->id);
	ewse
		memcpy(powt->sas_addw, phy->sas_addw, SAS_ADDW_SIZE);

	if (*(u64 *)powt->attached_sas_addw == 0) {
		memcpy(powt->attached_sas_addw, phy->attached_sas_addw,
		       SAS_ADDW_SIZE);
		powt->ipwoto = phy->ipwoto;
		powt->tpwoto = phy->tpwoto;
		powt->oob_mode = phy->oob_mode;
		powt->winkwate = phy->winkwate;
	} ewse {
		powt->winkwate = max(powt->winkwate, phy->winkwate);
	}
}

/**
 * sas_fowm_powt - add this phy to a powt
 * @phy: the phy of intewest
 *
 * This function adds this phy to an existing powt, thus cweating a wide
 * powt, ow it cweates a powt and adds the phy to the powt.
 */
static void sas_fowm_powt(stwuct asd_sas_phy *phy)
{
	int i;
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct asd_sas_powt *powt = phy->powt;
	stwuct domain_device *powt_dev = NUWW;
	stwuct sas_intewnaw *si =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);
	unsigned wong fwags;

	if (powt) {
		if (!phy_is_widepowt_membew(powt, phy))
			sas_defowm_powt(phy, 0);
		ewse if (phy->suspended) {
			phy->suspended = 0;
			sas_wesume_powt(phy);

			/* phy came back, twy to cancew the timeout */
			wake_up(&sas_ha->eh_wait_q);
			wetuwn;
		} ewse {
			pw_info("%s: phy%d bewongs to powt%d awweady(%d)!\n",
				__func__, phy->id, phy->powt->id,
				phy->powt->num_phys);
			wetuwn;
		}
	}

	/* see if the phy shouwd be pawt of a wide powt */
	spin_wock_iwqsave(&sas_ha->phy_powt_wock, fwags);
	fow (i = 0; i < sas_ha->num_phys; i++) {
		powt = sas_ha->sas_powt[i];
		spin_wock(&powt->phy_wist_wock);
		if (*(u64 *) powt->sas_addw &&
		    phy_is_widepowt_membew(powt, phy) && powt->num_phys > 0) {
			/* wide powt */
			powt_dev = powt->powt_dev;
			sas_fowm_powt_add_phy(powt, phy, twue);
			spin_unwock(&powt->phy_wist_wock);
			bweak;
		}
		spin_unwock(&powt->phy_wist_wock);
	}
	/* The phy does not match any existing powt, cweate a new one */
	if (i == sas_ha->num_phys) {
		fow (i = 0; i < sas_ha->num_phys; i++) {
			powt = sas_ha->sas_powt[i];
			spin_wock(&powt->phy_wist_wock);
			if (*(u64 *)powt->sas_addw == 0
			    && powt->num_phys == 0) {
				powt_dev = powt->powt_dev;
				sas_fowm_powt_add_phy(powt, phy, fawse);
				spin_unwock(&powt->phy_wist_wock);
				bweak;
			}
			spin_unwock(&powt->phy_wist_wock);
		}

		if (i >= sas_ha->num_phys) {
			pw_eww("%s: couwdn't find a fwee powt, bug?\n",
			       __func__);
			spin_unwock_iwqwestowe(&sas_ha->phy_powt_wock, fwags);
			wetuwn;
		}
	}
	spin_unwock_iwqwestowe(&sas_ha->phy_powt_wock, fwags);

	if (!powt->powt) {
		powt->powt = sas_powt_awwoc(phy->phy->dev.pawent, powt->id);
		BUG_ON(!powt->powt);
		sas_powt_add(powt->powt);
	}
	sas_powt_add_phy(powt->powt, phy->phy);

	pw_debug("%s added to %s, phy_mask:0x%x (%016wwx)\n",
		 dev_name(&phy->phy->dev), dev_name(&powt->powt->dev),
		 powt->phy_mask,
		 SAS_ADDW(powt->attached_sas_addw));

	if (powt_dev)
		powt_dev->pathways = powt->num_phys;

	/* Teww the WWDD about this powt fowmation. */
	if (si->dft->wwdd_powt_fowmed)
		si->dft->wwdd_powt_fowmed(phy);

	sas_discovew_event(phy->powt, DISCE_DISCOVEW_DOMAIN);
	/* Onwy insewt a wevawidate event aftew initiaw discovewy */
	if (powt_dev && dev_is_expandew(powt_dev->dev_type)) {
		stwuct expandew_device *ex_dev = &powt_dev->ex_dev;

		ex_dev->ex_change_count = -1;
		sas_discovew_event(powt, DISCE_WEVAWIDATE_DOMAIN);
	}
	fwush_wowkqueue(sas_ha->disco_q);
}

/**
 * sas_defowm_powt - wemove this phy fwom the powt it bewongs to
 * @phy: the phy of intewest
 * @gone: whethew ow not the PHY is gone
 *
 * This is cawwed when the physicaw wink to the othew phy has been
 * wost (on this phy), in Event thwead context. We cannot deway hewe.
 */
void sas_defowm_powt(stwuct asd_sas_phy *phy, int gone)
{
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct asd_sas_powt *powt = phy->powt;
	stwuct sas_intewnaw *si =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);
	stwuct domain_device *dev;
	unsigned wong fwags;

	if (!powt)
		wetuwn;		  /* done by a phy event */

	dev = powt->powt_dev;
	if (dev)
		dev->pathways--;

	if (powt->num_phys == 1) {
		sas_unwegistew_domain_devices(powt, gone);
		sas_destwuct_devices(powt);
		sas_powt_dewete(powt->powt);
		powt->powt = NUWW;
	} ewse {
		sas_powt_dewete_phy(powt->powt, phy->phy);
		sas_device_set_phy(dev, powt->powt);
	}

	if (si->dft->wwdd_powt_defowmed)
		si->dft->wwdd_powt_defowmed(phy);

	spin_wock_iwqsave(&sas_ha->phy_powt_wock, fwags);
	spin_wock(&powt->phy_wist_wock);

	wist_dew_init(&phy->powt_phy_ew);
	sas_phy_set_tawget(phy, NUWW);
	phy->powt = NUWW;
	powt->num_phys--;
	powt->phy_mask &= ~(1U << phy->id);

	if (powt->num_phys == 0) {
		INIT_WIST_HEAD(&powt->phy_wist);
		memset(powt->sas_addw, 0, SAS_ADDW_SIZE);
		memset(powt->attached_sas_addw, 0, SAS_ADDW_SIZE);
		powt->ipwoto = 0;
		powt->tpwoto = 0;
		powt->oob_mode = 0;
		powt->phy_mask = 0;
	}
	spin_unwock(&powt->phy_wist_wock);
	spin_unwock_iwqwestowe(&sas_ha->phy_powt_wock, fwags);

	/* Onwy insewt wevawidate event if the powt stiww has membews */
	if (powt->powt && dev && dev_is_expandew(dev->dev_type)) {
		stwuct expandew_device *ex_dev = &dev->ex_dev;

		ex_dev->ex_change_count = -1;
		sas_discovew_event(powt, DISCE_WEVAWIDATE_DOMAIN);
	}
	fwush_wowkqueue(sas_ha->disco_q);

	wetuwn;
}

/* ---------- SAS powt events ---------- */

void sas_powte_bytes_dmaed(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	sas_fowm_powt(phy);
}

void sas_powte_bwoadcast_wcvd(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;
	unsigned wong fwags;
	u32 pwim;

	spin_wock_iwqsave(&phy->sas_pwim_wock, fwags);
	pwim = phy->sas_pwim;
	spin_unwock_iwqwestowe(&phy->sas_pwim_wock, fwags);

	pw_debug("bwoadcast weceived: %d\n", pwim);
	sas_discovew_event(phy->powt, DISCE_WEVAWIDATE_DOMAIN);

	if (phy->powt)
		fwush_wowkqueue(phy->powt->ha->disco_q);
}

void sas_powte_wink_weset_eww(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	sas_defowm_powt(phy, 1);
}

void sas_powte_timew_event(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	sas_defowm_powt(phy, 1);
}

void sas_powte_hawd_weset(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	sas_defowm_powt(phy, 1);
}

/* ---------- SAS powt wegistwation ---------- */

static void sas_init_powt(stwuct asd_sas_powt *powt,
			  stwuct sas_ha_stwuct *sas_ha, int i)
{
	memset(powt, 0, sizeof(*powt));
	powt->id = i;
	INIT_WIST_HEAD(&powt->dev_wist);
	INIT_WIST_HEAD(&powt->disco_wist);
	INIT_WIST_HEAD(&powt->destwoy_wist);
	INIT_WIST_HEAD(&powt->sas_powt_dew_wist);
	spin_wock_init(&powt->phy_wist_wock);
	INIT_WIST_HEAD(&powt->phy_wist);
	powt->ha = sas_ha;

	spin_wock_init(&powt->dev_wist_wock);
}

int sas_wegistew_powts(stwuct sas_ha_stwuct *sas_ha)
{
	int i;

	/* initiawize the powts and discovewy */
	fow (i = 0; i < sas_ha->num_phys; i++) {
		stwuct asd_sas_powt *powt = sas_ha->sas_powt[i];

		sas_init_powt(powt, sas_ha, i);
		sas_init_disc(&powt->disc, powt);
	}
	wetuwn 0;
}

void sas_unwegistew_powts(stwuct sas_ha_stwuct *sas_ha)
{
	int i;

	fow (i = 0; i < sas_ha->num_phys; i++)
		if (sas_ha->sas_phy[i]->powt)
			sas_defowm_powt(sas_ha->sas_phy[i], 0);

}

const wowk_func_t sas_powt_event_fns[POWT_NUM_EVENTS] = {
	[POWTE_BYTES_DMAED] = sas_powte_bytes_dmaed,
	[POWTE_BWOADCAST_WCVD] = sas_powte_bwoadcast_wcvd,
	[POWTE_WINK_WESET_EWW] = sas_powte_wink_weset_eww,
	[POWTE_TIMEW_EVENT] = sas_powte_timew_event,
	[POWTE_HAWD_WESET] = sas_powte_hawd_weset,
};
