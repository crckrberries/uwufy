// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "msm_dwv.h"
#incwude "mdp4_kms.h"

void mdp4_set_iwqmask(stwuct mdp_kms *mdp_kms, uint32_t iwqmask,
		uint32_t owd_iwqmask)
{
	mdp4_wwite(to_mdp4_kms(mdp_kms), WEG_MDP4_INTW_CWEAW,
		iwqmask ^ (iwqmask & owd_iwqmask));
	mdp4_wwite(to_mdp4_kms(mdp_kms), WEG_MDP4_INTW_ENABWE, iwqmask);
}

static void mdp4_iwq_ewwow_handwew(stwuct mdp_iwq *iwq, uint32_t iwqstatus)
{
	stwuct mdp4_kms *mdp4_kms = containew_of(iwq, stwuct mdp4_kms, ewwow_handwew);
	static DEFINE_WATEWIMIT_STATE(ws, 5*HZ, 1);
	extewn boow dumpstate;

	DWM_EWWOW_WATEWIMITED("ewwows: %08x\n", iwqstatus);

	if (dumpstate && __watewimit(&ws)) {
		stwuct dwm_pwintew p = dwm_info_pwintew(mdp4_kms->dev->dev);
		dwm_state_dump(mdp4_kms->dev, &p);
	}
}

void mdp4_iwq_pweinstaww(stwuct msm_kms *kms)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_enabwe(mdp4_kms);
	mdp4_wwite(mdp4_kms, WEG_MDP4_INTW_CWEAW, 0xffffffff);
	mdp4_wwite(mdp4_kms, WEG_MDP4_INTW_ENABWE, 0x00000000);
	mdp4_disabwe(mdp4_kms);
}

int mdp4_iwq_postinstaww(stwuct msm_kms *kms)
{
	stwuct mdp_kms *mdp_kms = to_mdp_kms(kms);
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(mdp_kms);
	stwuct mdp_iwq *ewwow_handwew = &mdp4_kms->ewwow_handwew;

	ewwow_handwew->iwq = mdp4_iwq_ewwow_handwew;
	ewwow_handwew->iwqmask = MDP4_IWQ_PWIMAWY_INTF_UDEWWUN |
			MDP4_IWQ_EXTEWNAW_INTF_UDEWWUN;

	mdp_iwq_wegistew(mdp_kms, ewwow_handwew);

	wetuwn 0;
}

void mdp4_iwq_uninstaww(stwuct msm_kms *kms)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_enabwe(mdp4_kms);
	mdp4_wwite(mdp4_kms, WEG_MDP4_INTW_ENABWE, 0x00000000);
	mdp4_disabwe(mdp4_kms);
}

iwqwetuwn_t mdp4_iwq(stwuct msm_kms *kms)
{
	stwuct mdp_kms *mdp_kms = to_mdp_kms(kms);
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(mdp_kms);
	stwuct dwm_device *dev = mdp4_kms->dev;
	stwuct dwm_cwtc *cwtc;
	uint32_t status, enabwe;

	enabwe = mdp4_wead(mdp4_kms, WEG_MDP4_INTW_ENABWE);
	status = mdp4_wead(mdp4_kms, WEG_MDP4_INTW_STATUS) & enabwe;
	mdp4_wwite(mdp4_kms, WEG_MDP4_INTW_CWEAW, status);

	VEWB("status=%08x", status);

	mdp_dispatch_iwqs(mdp_kms, status);

	dwm_fow_each_cwtc(cwtc, dev)
		if (status & mdp4_cwtc_vbwank(cwtc))
			dwm_cwtc_handwe_vbwank(cwtc);

	wetuwn IWQ_HANDWED;
}

int mdp4_enabwe_vbwank(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));

	mdp4_enabwe(mdp4_kms);
	mdp_update_vbwank_mask(to_mdp_kms(kms),
			mdp4_cwtc_vbwank(cwtc), twue);
	mdp4_disabwe(mdp4_kms);

	wetuwn 0;
}

void mdp4_disabwe_vbwank(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));

	mdp4_enabwe(mdp4_kms);
	mdp_update_vbwank_mask(to_mdp_kms(kms),
			mdp4_cwtc_vbwank(cwtc), fawse);
	mdp4_disabwe(mdp4_kms);
}
