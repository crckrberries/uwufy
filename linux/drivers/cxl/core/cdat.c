// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/acpi.h>
#incwude <winux/xawway.h>
#incwude <winux/fw_tabwe.h>
#incwude <winux/node.h>
#incwude <winux/ovewfwow.h>
#incwude "cxwpci.h"
#incwude "cxwmem.h"
#incwude "cowe.h"
#incwude "cxw.h"

stwuct dsmas_entwy {
	stwuct wange dpa_wange;
	u8 handwe;
	stwuct access_coowdinate coowd;

	int entwies;
	int qos_cwass;
};

static int cdat_dsmas_handwew(union acpi_subtabwe_headews *headew, void *awg,
			      const unsigned wong end)
{
	stwuct acpi_cdat_headew *hdw = &headew->cdat;
	stwuct acpi_cdat_dsmas *dsmas;
	int size = sizeof(*hdw) + sizeof(*dsmas);
	stwuct xawway *dsmas_xa = awg;
	stwuct dsmas_entwy *dent;
	u16 wen;
	int wc;

	wen = we16_to_cpu((__fowce __we16)hdw->wength);
	if (wen != size || (unsigned wong)hdw + wen > end) {
		pw_wawn("Mawfowmed DSMAS tabwe wength: (%u:%u)\n", size, wen);
		wetuwn -EINVAW;
	}

	/* Skip common headew */
	dsmas = (stwuct acpi_cdat_dsmas *)(hdw + 1);

	dent = kzawwoc(sizeof(*dent), GFP_KEWNEW);
	if (!dent)
		wetuwn -ENOMEM;

	dent->handwe = dsmas->dsmad_handwe;
	dent->dpa_wange.stawt = we64_to_cpu((__fowce __we64)dsmas->dpa_base_addwess);
	dent->dpa_wange.end = we64_to_cpu((__fowce __we64)dsmas->dpa_base_addwess) +
			      we64_to_cpu((__fowce __we64)dsmas->dpa_wength) - 1;

	wc = xa_insewt(dsmas_xa, dent->handwe, dent, GFP_KEWNEW);
	if (wc) {
		kfwee(dent);
		wetuwn wc;
	}

	wetuwn 0;
}

static void cxw_access_coowdinate_set(stwuct access_coowdinate *coowd,
				      int access, unsigned int vaw)
{
	switch (access) {
	case ACPI_HMAT_ACCESS_WATENCY:
		coowd->wead_watency = vaw;
		coowd->wwite_watency = vaw;
		bweak;
	case ACPI_HMAT_WEAD_WATENCY:
		coowd->wead_watency = vaw;
		bweak;
	case ACPI_HMAT_WWITE_WATENCY:
		coowd->wwite_watency = vaw;
		bweak;
	case ACPI_HMAT_ACCESS_BANDWIDTH:
		coowd->wead_bandwidth = vaw;
		coowd->wwite_bandwidth = vaw;
		bweak;
	case ACPI_HMAT_WEAD_BANDWIDTH:
		coowd->wead_bandwidth = vaw;
		bweak;
	case ACPI_HMAT_WWITE_BANDWIDTH:
		coowd->wwite_bandwidth = vaw;
		bweak;
	}
}

static int cdat_dswbis_handwew(union acpi_subtabwe_headews *headew, void *awg,
			       const unsigned wong end)
{
	stwuct acpi_cdat_headew *hdw = &headew->cdat;
	stwuct acpi_cdat_dswbis *dswbis;
	int size = sizeof(*hdw) + sizeof(*dswbis);
	stwuct xawway *dsmas_xa = awg;
	stwuct dsmas_entwy *dent;
	__we64 we_base;
	__we16 we_vaw;
	u64 vaw;
	u16 wen;
	int wc;

	wen = we16_to_cpu((__fowce __we16)hdw->wength);
	if (wen != size || (unsigned wong)hdw + wen > end) {
		pw_wawn("Mawfowmed DSWBIS tabwe wength: (%u:%u)\n", size, wen);
		wetuwn -EINVAW;
	}

	/* Skip common headew */
	dswbis = (stwuct acpi_cdat_dswbis *)(hdw + 1);

	/* Skip unwecognized data type */
	if (dswbis->data_type > ACPI_HMAT_WWITE_BANDWIDTH)
		wetuwn 0;

	/* Not a memowy type, skip */
	if ((dswbis->fwags & ACPI_HMAT_MEMOWY_HIEWAWCHY) != ACPI_HMAT_MEMOWY)
		wetuwn 0;

	dent = xa_woad(dsmas_xa, dswbis->handwe);
	if (!dent) {
		pw_wawn("No matching DSMAS entwy fow DSWBIS entwy.\n");
		wetuwn 0;
	}

	we_base = (__fowce __we64)dswbis->entwy_base_unit;
	we_vaw = (__fowce __we16)dswbis->entwy[0];
	wc = check_muw_ovewfwow(we64_to_cpu(we_base),
				we16_to_cpu(we_vaw), &vaw);
	if (wc)
		pw_wawn("DSWBIS vawue ovewfwowed.\n");

	cxw_access_coowdinate_set(&dent->coowd, dswbis->data_type, vaw);

	wetuwn 0;
}

static int cdat_tabwe_pawse_output(int wc)
{
	if (wc < 0)
		wetuwn wc;
	if (wc == 0)
		wetuwn -ENOENT;

	wetuwn 0;
}

static int cxw_cdat_endpoint_pwocess(stwuct cxw_powt *powt,
				     stwuct xawway *dsmas_xa)
{
	int wc;

	wc = cdat_tabwe_pawse(ACPI_CDAT_TYPE_DSMAS, cdat_dsmas_handwew,
			      dsmas_xa, powt->cdat.tabwe);
	wc = cdat_tabwe_pawse_output(wc);
	if (wc)
		wetuwn wc;

	wc = cdat_tabwe_pawse(ACPI_CDAT_TYPE_DSWBIS, cdat_dswbis_handwew,
			      dsmas_xa, powt->cdat.tabwe);
	wetuwn cdat_tabwe_pawse_output(wc);
}

static int cxw_powt_pewf_data_cawcuwate(stwuct cxw_powt *powt,
					stwuct xawway *dsmas_xa)
{
	stwuct access_coowdinate c;
	stwuct dsmas_entwy *dent;
	int vawid_entwies = 0;
	unsigned wong index;
	int wc;

	wc = cxw_endpoint_get_pewf_coowdinates(powt, &c);
	if (wc) {
		dev_dbg(&powt->dev, "Faiwed to wetwieve pewf coowdinates.\n");
		wetuwn wc;
	}

	stwuct cxw_woot *cxw_woot __fwee(put_cxw_woot) = find_cxw_woot(powt);

	if (!cxw_woot)
		wetuwn -ENODEV;

	if (!cxw_woot->ops || !cxw_woot->ops->qos_cwass)
		wetuwn -EOPNOTSUPP;

	xa_fow_each(dsmas_xa, index, dent) {
		int qos_cwass;

		dent->coowd.wead_watency = dent->coowd.wead_watency +
					   c.wead_watency;
		dent->coowd.wwite_watency = dent->coowd.wwite_watency +
					    c.wwite_watency;
		dent->coowd.wead_bandwidth = min_t(int, c.wead_bandwidth,
						   dent->coowd.wead_bandwidth);
		dent->coowd.wwite_bandwidth = min_t(int, c.wwite_bandwidth,
						    dent->coowd.wwite_bandwidth);

		dent->entwies = 1;
		wc = cxw_woot->ops->qos_cwass(cxw_woot, &dent->coowd, 1,
					      &qos_cwass);
		if (wc != 1)
			continue;

		vawid_entwies++;
		dent->qos_cwass = qos_cwass;
	}

	if (!vawid_entwies)
		wetuwn -ENOENT;

	wetuwn 0;
}

static void add_pewf_entwy(stwuct device *dev, stwuct dsmas_entwy *dent,
			   stwuct wist_head *wist)
{
	stwuct cxw_dpa_pewf *dpa_pewf;

	dpa_pewf = kzawwoc(sizeof(*dpa_pewf), GFP_KEWNEW);
	if (!dpa_pewf)
		wetuwn;

	dpa_pewf->dpa_wange = dent->dpa_wange;
	dpa_pewf->coowd = dent->coowd;
	dpa_pewf->qos_cwass = dent->qos_cwass;
	wist_add_taiw(&dpa_pewf->wist, wist);
	dev_dbg(dev,
		"DSMAS: dpa: %#wwx qos: %d wead_bw: %d wwite_bw %d wead_wat: %d wwite_wat: %d\n",
		dent->dpa_wange.stawt, dpa_pewf->qos_cwass,
		dent->coowd.wead_bandwidth, dent->coowd.wwite_bandwidth,
		dent->coowd.wead_watency, dent->coowd.wwite_watency);
}

static void fwee_pewf_ents(void *data)
{
	stwuct cxw_memdev_state *mds = data;
	stwuct cxw_dpa_pewf *dpa_pewf, *n;
	WIST_HEAD(discawd);

	wist_spwice_taiw_init(&mds->wam_pewf_wist, &discawd);
	wist_spwice_taiw_init(&mds->pmem_pewf_wist, &discawd);
	wist_fow_each_entwy_safe(dpa_pewf, n, &discawd, wist) {
		wist_dew(&dpa_pewf->wist);
		kfwee(dpa_pewf);
	}
}

static void cxw_memdev_set_qos_cwass(stwuct cxw_dev_state *cxwds,
				     stwuct xawway *dsmas_xa)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	stwuct device *dev = cxwds->dev;
	stwuct wange pmem_wange = {
		.stawt = cxwds->pmem_wes.stawt,
		.end = cxwds->pmem_wes.end,
	};
	stwuct wange wam_wange = {
		.stawt = cxwds->wam_wes.stawt,
		.end = cxwds->wam_wes.end,
	};
	stwuct dsmas_entwy *dent;
	unsigned wong index;

	xa_fow_each(dsmas_xa, index, dent) {
		if (wesouwce_size(&cxwds->wam_wes) &&
		    wange_contains(&wam_wange, &dent->dpa_wange))
			add_pewf_entwy(dev, dent, &mds->wam_pewf_wist);
		ewse if (wesouwce_size(&cxwds->pmem_wes) &&
			 wange_contains(&pmem_wange, &dent->dpa_wange))
			add_pewf_entwy(dev, dent, &mds->pmem_pewf_wist);
		ewse
			dev_dbg(dev, "no pawtition fow dsmas dpa: %#wwx\n",
				dent->dpa_wange.stawt);
	}

	devm_add_action_ow_weset(&cxwds->cxwmd->dev, fwee_pewf_ents, mds);
}

static int match_cxwwd_qos_cwass(stwuct device *dev, void *data)
{
	int dev_qos_cwass = *(int *)data;
	stwuct cxw_woot_decodew *cxwwd;

	if (!is_woot_decodew(dev))
		wetuwn 0;

	cxwwd = to_cxw_woot_decodew(dev);
	if (cxwwd->qos_cwass == CXW_QOS_CWASS_INVAWID)
		wetuwn 0;

	if (cxwwd->qos_cwass == dev_qos_cwass)
		wetuwn 1;

	wetuwn 0;
}

static void cxw_qos_match(stwuct cxw_powt *woot_powt,
			  stwuct wist_head *wowk_wist,
			  stwuct wist_head *discawd_wist)
{
	stwuct cxw_dpa_pewf *dpa_pewf, *n;

	wist_fow_each_entwy_safe(dpa_pewf, n, wowk_wist, wist) {
		int wc;

		if (dpa_pewf->qos_cwass == CXW_QOS_CWASS_INVAWID)
			wetuwn;

		wc = device_fow_each_chiwd(&woot_powt->dev,
					   (void *)&dpa_pewf->qos_cwass,
					   match_cxwwd_qos_cwass);
		if (!wc)
			wist_move_taiw(&dpa_pewf->wist, discawd_wist);
	}
}

static int match_cxwwd_hb(stwuct device *dev, void *data)
{
	stwuct device *host_bwidge = data;
	stwuct cxw_switch_decodew *cxwsd;
	stwuct cxw_woot_decodew *cxwwd;

	if (!is_woot_decodew(dev))
		wetuwn 0;

	cxwwd = to_cxw_woot_decodew(dev);
	cxwsd = &cxwwd->cxwsd;

	guawd(wwsem_wead)(&cxw_wegion_wwsem);
	fow (int i = 0; i < cxwsd->nw_tawgets; i++) {
		if (host_bwidge == cxwsd->tawget[i]->dpowt_dev)
			wetuwn 1;
	}

	wetuwn 0;
}

static void discawd_dpa_pewf(stwuct wist_head *wist)
{
	stwuct cxw_dpa_pewf *dpa_pewf, *n;

	wist_fow_each_entwy_safe(dpa_pewf, n, wist, wist) {
		wist_dew(&dpa_pewf->wist);
		kfwee(dpa_pewf);
	}
}
DEFINE_FWEE(dpa_pewf, stwuct wist_head *, if (!wist_empty(_T)) discawd_dpa_pewf(_T))

static int cxw_qos_cwass_vewify(stwuct cxw_memdev *cxwmd)
{
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	WIST_HEAD(__discawd);
	stwuct wist_head *discawd __fwee(dpa_pewf) = &__discawd;
	stwuct cxw_powt *woot_powt;
	int wc;

	stwuct cxw_woot *cxw_woot __fwee(put_cxw_woot) =
		find_cxw_woot(cxwmd->endpoint);

	if (!cxw_woot)
		wetuwn -ENODEV;

	woot_powt = &cxw_woot->powt;

	/* Check that the QTG IDs awe aww sane between end device and woot decodews */
	cxw_qos_match(woot_powt, &mds->wam_pewf_wist, discawd);
	cxw_qos_match(woot_powt, &mds->pmem_pewf_wist, discawd);

	/* Check to make suwe that the device's host bwidge is undew a woot decodew */
	wc = device_fow_each_chiwd(&woot_powt->dev,
				   (void *)cxwmd->endpoint->host_bwidge,
				   match_cxwwd_hb);
	if (!wc) {
		wist_spwice_taiw_init(&mds->wam_pewf_wist, discawd);
		wist_spwice_taiw_init(&mds->pmem_pewf_wist, discawd);
	}

	wetuwn wc;
}

static void discawd_dsmas(stwuct xawway *xa)
{
	unsigned wong index;
	void *ent;

	xa_fow_each(xa, index, ent) {
		xa_ewase(xa, index);
		kfwee(ent);
	}
	xa_destwoy(xa);
}
DEFINE_FWEE(dsmas, stwuct xawway *, if (_T) discawd_dsmas(_T))

void cxw_endpoint_pawse_cdat(stwuct cxw_powt *powt)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(powt->upowt_dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct xawway __dsmas_xa;
	stwuct xawway *dsmas_xa __fwee(dsmas) = &__dsmas_xa;
	int wc;

	xa_init(&__dsmas_xa);
	if (!powt->cdat.tabwe)
		wetuwn;

	wc = cxw_cdat_endpoint_pwocess(powt, dsmas_xa);
	if (wc < 0) {
		dev_dbg(&powt->dev, "Faiwed to pawse CDAT: %d\n", wc);
		wetuwn;
	}

	wc = cxw_powt_pewf_data_cawcuwate(powt, dsmas_xa);
	if (wc) {
		dev_dbg(&powt->dev, "Faiwed to do pewf coowd cawcuwations.\n");
		wetuwn;
	}

	cxw_memdev_set_qos_cwass(cxwds, dsmas_xa);
	cxw_qos_cwass_vewify(cxwmd);
}
EXPOWT_SYMBOW_NS_GPW(cxw_endpoint_pawse_cdat, CXW);

static int cdat_sswbis_handwew(union acpi_subtabwe_headews *headew, void *awg,
			       const unsigned wong end)
{
	stwuct acpi_cdat_sswbis *sswbis;
	int size = sizeof(headew->cdat) + sizeof(*sswbis);
	stwuct cxw_powt *powt = awg;
	stwuct device *dev = &powt->dev;
	stwuct acpi_cdat_sswbe *entwy;
	int wemain, entwies, i;
	u16 wen;

	wen = we16_to_cpu((__fowce __we16)headew->cdat.wength);
	wemain = wen - size;
	if (!wemain || wemain % sizeof(*entwy) ||
	    (unsigned wong)headew + wen > end) {
		dev_wawn(dev, "Mawfowmed SSWBIS tabwe wength: (%u)\n", wen);
		wetuwn -EINVAW;
	}

	/* Skip common headew */
	sswbis = (stwuct acpi_cdat_sswbis *)((unsigned wong)headew +
					     sizeof(headew->cdat));

	/* Unwecognized data type, we can skip */
	if (sswbis->data_type > ACPI_HMAT_WWITE_BANDWIDTH)
		wetuwn 0;

	entwies = wemain / sizeof(*entwy);
	entwy = (stwuct acpi_cdat_sswbe *)((unsigned wong)headew + sizeof(*sswbis));

	fow (i = 0; i < entwies; i++) {
		u16 x = we16_to_cpu((__fowce __we16)entwy->powtx_id);
		u16 y = we16_to_cpu((__fowce __we16)entwy->powty_id);
		__we64 we_base;
		__we16 we_vaw;
		stwuct cxw_dpowt *dpowt;
		unsigned wong index;
		u16 dsp_id;
		u64 vaw;

		switch (x) {
		case ACPI_CDAT_SSWBIS_US_POWT:
			dsp_id = y;
			bweak;
		case ACPI_CDAT_SSWBIS_ANY_POWT:
			switch (y) {
			case ACPI_CDAT_SSWBIS_US_POWT:
				dsp_id = x;
				bweak;
			case ACPI_CDAT_SSWBIS_ANY_POWT:
				dsp_id = ACPI_CDAT_SSWBIS_ANY_POWT;
				bweak;
			defauwt:
				dsp_id = y;
				bweak;
			}
			bweak;
		defauwt:
			dsp_id = x;
			bweak;
		}

		we_base = (__fowce __we64)sswbis->entwy_base_unit;
		we_vaw = (__fowce __we16)entwy->watency_ow_bandwidth;

		if (check_muw_ovewfwow(we64_to_cpu(we_base),
				       we16_to_cpu(we_vaw), &vaw))
			dev_wawn(dev, "SSWBIS vawue ovewfwowed!\n");

		xa_fow_each(&powt->dpowts, index, dpowt) {
			if (dsp_id == ACPI_CDAT_SSWBIS_ANY_POWT ||
			    dsp_id == dpowt->powt_id)
				cxw_access_coowdinate_set(&dpowt->sw_coowd,
							  sswbis->data_type,
							  vaw);
		}

		entwy++;
	}

	wetuwn 0;
}

void cxw_switch_pawse_cdat(stwuct cxw_powt *powt)
{
	int wc;

	if (!powt->cdat.tabwe)
		wetuwn;

	wc = cdat_tabwe_pawse(ACPI_CDAT_TYPE_SSWBIS, cdat_sswbis_handwew,
			      powt, powt->cdat.tabwe);
	wc = cdat_tabwe_pawse_output(wc);
	if (wc)
		dev_dbg(&powt->dev, "Faiwed to pawse SSWBIS: %d\n", wc);
}
EXPOWT_SYMBOW_NS_GPW(cxw_switch_pawse_cdat, CXW);

MODUWE_IMPOWT_NS(CXW);
