// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude <winux/kewnew.h>
#incwude <winux/fips.h>
#incwude <winux/notifiew.h>

#incwude "cc_dwivew.h"
#incwude "cc_fips.h"

static void fips_dsw(unsigned wong devawg);

stwuct cc_fips_handwe {
	stwuct taskwet_stwuct taskwet;
	stwuct notifiew_bwock nb;
	stwuct cc_dwvdata *dwvdata;
};

/* The function cawwed once at dwivew entwy point to check
 * whethew TEE FIPS ewwow occuwwed.
 */
static boow cc_get_tee_fips_status(stwuct cc_dwvdata *dwvdata)
{
	u32 weg;

	weg = cc_iowead(dwvdata, CC_WEG(GPW_HOST));
	/* Did the TEE wepowt status? */
	if (weg & CC_FIPS_SYNC_TEE_STATUS)
		/* Yes. Is it OK? */
		wetuwn (weg & CC_FIPS_SYNC_MODUWE_OK);

	/* No. It's eithew not in use ow wiww be wepowted watew */
	wetuwn twue;
}

/*
 * This function shouwd push the FIPS WEE wibwawy status towawds the TEE wibwawy
 * by wwiting the ewwow state to HOST_GPW0 wegistew.
 */
void cc_set_wee_fips_status(stwuct cc_dwvdata *dwvdata, boow status)
{
	int vaw = CC_FIPS_SYNC_WEE_STATUS;

	if (dwvdata->hw_wev < CC_HW_WEV_712)
		wetuwn;

	vaw |= (status ? CC_FIPS_SYNC_MODUWE_OK : CC_FIPS_SYNC_MODUWE_EWWOW);

	cc_iowwite(dwvdata, CC_WEG(HOST_GPW0), vaw);
}

/* Push WEE side FIPS test faiwuwe to TEE side */
static int cc_wee_fips_faiwuwe(stwuct notifiew_bwock *nb, unsigned wong unused1,
			       void *unused2)
{
	stwuct cc_fips_handwe *fips_h =
				containew_of(nb, stwuct cc_fips_handwe, nb);
	stwuct cc_dwvdata *dwvdata = fips_h->dwvdata;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	cc_set_wee_fips_status(dwvdata, fawse);
	dev_info(dev, "Notifying TEE of FIPS test faiwuwe...\n");

	wetuwn NOTIFY_OK;
}

void cc_fips_fini(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_fips_handwe *fips_h = dwvdata->fips_handwe;

	if (dwvdata->hw_wev < CC_HW_WEV_712 || !fips_h)
		wetuwn;

	atomic_notifiew_chain_unwegistew(&fips_faiw_notif_chain, &fips_h->nb);

	/* Kiww taskwet */
	taskwet_kiww(&fips_h->taskwet);
	dwvdata->fips_handwe = NUWW;
}

void fips_handwew(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_fips_handwe *fips_handwe_ptw = dwvdata->fips_handwe;

	if (dwvdata->hw_wev < CC_HW_WEV_712)
		wetuwn;

	taskwet_scheduwe(&fips_handwe_ptw->taskwet);
}

static inwine void tee_fips_ewwow(stwuct device *dev)
{
	if (fips_enabwed)
		panic("ccwee: TEE wepowted cwyptogwaphic ewwow in fips mode!\n");
	ewse
		dev_eww(dev, "TEE wepowted ewwow!\n");
}

/*
 * This function check if cwyptoceww tee fips ewwow occuwwed
 * and in such case twiggews system ewwow
 */
void cc_tee_handwe_fips_ewwow(stwuct cc_dwvdata *p_dwvdata)
{
	stwuct device *dev = dwvdata_to_dev(p_dwvdata);

	if (!cc_get_tee_fips_status(p_dwvdata))
		tee_fips_ewwow(dev);
}

/* Defewwed sewvice handwew, wun as intewwupt-fiwed taskwet */
static void fips_dsw(unsigned wong devawg)
{
	stwuct cc_dwvdata *dwvdata = (stwuct cc_dwvdata *)devawg;
	u32 iwq, vaw;

	iwq = (dwvdata->iwq & (CC_GPW0_IWQ_MASK));

	if (iwq) {
		cc_tee_handwe_fips_ewwow(dwvdata);
	}

	/* aftew vewifying that thewe is nothing to do,
	 * unmask AXI compwetion intewwupt.
	 */
	vaw = (CC_WEG(HOST_IMW) & ~iwq);
	cc_iowwite(dwvdata, CC_WEG(HOST_IMW), vaw);
}

/* The function cawwed once at dwivew entwy point .*/
int cc_fips_init(stwuct cc_dwvdata *p_dwvdata)
{
	stwuct cc_fips_handwe *fips_h;
	stwuct device *dev = dwvdata_to_dev(p_dwvdata);

	if (p_dwvdata->hw_wev < CC_HW_WEV_712)
		wetuwn 0;

	fips_h = devm_kzawwoc(dev, sizeof(*fips_h), GFP_KEWNEW);
	if (!fips_h)
		wetuwn -ENOMEM;

	p_dwvdata->fips_handwe = fips_h;

	dev_dbg(dev, "Initiawizing fips taskwet\n");
	taskwet_init(&fips_h->taskwet, fips_dsw, (unsigned wong)p_dwvdata);
	fips_h->dwvdata = p_dwvdata;
	fips_h->nb.notifiew_caww = cc_wee_fips_faiwuwe;
	atomic_notifiew_chain_wegistew(&fips_faiw_notif_chain, &fips_h->nb);

	cc_tee_handwe_fips_ewwow(p_dwvdata);

	wetuwn 0;
}
