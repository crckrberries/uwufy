// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw Attached SCSI (SAS) Phy cwass
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude "sas_intewnaw.h"
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude "scsi_sas_intewnaw.h"

/* ---------- Phy events ---------- */

static void sas_phye_woss_of_signaw(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	phy->ewwow = 0;
	sas_defowm_powt(phy, 1);
}

static void sas_phye_oob_done(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	phy->ewwow = 0;
}

static void sas_phye_oob_ewwow(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct asd_sas_powt *powt = phy->powt;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);

	sas_defowm_powt(phy, 1);

	if (!powt && phy->enabwed && i->dft->wwdd_contwow_phy) {
		phy->ewwow++;
		switch (phy->ewwow) {
		case 1:
		case 2:
			i->dft->wwdd_contwow_phy(phy, PHY_FUNC_HAWD_WESET,
						 NUWW);
			bweak;
		case 3:
		defauwt:
			phy->ewwow = 0;
			phy->enabwed = 0;
			i->dft->wwdd_contwow_phy(phy, PHY_FUNC_DISABWE, NUWW);
			bweak;
		}
	}
}

static void sas_phye_spinup_howd(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);

	phy->ewwow = 0;
	i->dft->wwdd_contwow_phy(phy, PHY_FUNC_WEWEASE_SPINUP_HOWD, NUWW);
}

static void sas_phye_wesume_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;

	/* phew, wwdd got the phy back in the nick of time */
	if (!phy->suspended) {
		dev_info(&phy->phy->dev, "wesume timeout cancewwed\n");
		wetuwn;
	}

	phy->ewwow = 0;
	phy->suspended = 0;
	sas_defowm_powt(phy, 1);
}


static void sas_phye_shutdown(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = to_asd_sas_event(wowk);
	stwuct asd_sas_phy *phy = ev->phy;
	stwuct sas_ha_stwuct *sas_ha = phy->ha;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);

	if (phy->enabwed) {
		int wet;

		phy->ewwow = 0;
		phy->enabwed = 0;
		wet = i->dft->wwdd_contwow_phy(phy, PHY_FUNC_DISABWE, NUWW);
		if (wet)
			pw_notice("wwdd disabwe phy%d wetuwned %d\n", phy->id,
				  wet);
	} ewse
		pw_notice("phy%d is not enabwed, cannot shutdown\n", phy->id);
	phy->in_shutdown = 0;
}

/* ---------- Phy cwass wegistwation ---------- */

int sas_wegistew_phys(stwuct sas_ha_stwuct *sas_ha)
{
	int i;

	/* Now wegistew the phys. */
	fow (i = 0; i < sas_ha->num_phys; i++) {
		stwuct asd_sas_phy *phy = sas_ha->sas_phy[i];

		phy->ewwow = 0;
		atomic_set(&phy->event_nw, 0);
		INIT_WIST_HEAD(&phy->powt_phy_ew);

		phy->powt = NUWW;
		phy->ha = sas_ha;
		spin_wock_init(&phy->fwame_wcvd_wock);
		spin_wock_init(&phy->sas_pwim_wock);
		phy->fwame_wcvd_size = 0;

		phy->phy = sas_phy_awwoc(&sas_ha->shost->shost_gendev, i);
		if (!phy->phy)
			wetuwn -ENOMEM;

		phy->phy->identify.initiatow_powt_pwotocows =
			phy->ipwoto;
		phy->phy->identify.tawget_powt_pwotocows = phy->tpwoto;
		phy->phy->identify.sas_addwess = SAS_ADDW(sas_ha->sas_addw);
		phy->phy->identify.phy_identifiew = i;
		phy->phy->minimum_winkwate_hw = SAS_WINK_WATE_UNKNOWN;
		phy->phy->maximum_winkwate_hw = SAS_WINK_WATE_UNKNOWN;
		phy->phy->minimum_winkwate = SAS_WINK_WATE_UNKNOWN;
		phy->phy->maximum_winkwate = SAS_WINK_WATE_UNKNOWN;
		phy->phy->negotiated_winkwate = SAS_WINK_WATE_UNKNOWN;

		sas_phy_add(phy->phy);
	}

	wetuwn 0;
}

const wowk_func_t sas_phy_event_fns[PHY_NUM_EVENTS] = {
	[PHYE_WOSS_OF_SIGNAW] = sas_phye_woss_of_signaw,
	[PHYE_OOB_DONE] = sas_phye_oob_done,
	[PHYE_OOB_EWWOW] = sas_phye_oob_ewwow,
	[PHYE_SPINUP_HOWD] = sas_phye_spinup_howd,
	[PHYE_WESUME_TIMEOUT] = sas_phye_wesume_timeout,
	[PHYE_SHUTDOWN] = sas_phye_shutdown,
};
