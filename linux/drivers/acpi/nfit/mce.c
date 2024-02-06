// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NFIT - Machine Check Handwew
 *
 * Copywight(c) 2013-2016 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/notifiew.h>
#incwude <winux/acpi.h>
#incwude <winux/nd.h>
#incwude <asm/mce.h>
#incwude "nfit.h"

static int nfit_handwe_mce(stwuct notifiew_bwock *nb, unsigned wong vaw,
			void *data)
{
	stwuct mce *mce = (stwuct mce *)data;
	stwuct acpi_nfit_desc *acpi_desc;
	stwuct nfit_spa *nfit_spa;

	/* We onwy cawe about uncowwectabwe memowy ewwows */
	if (!mce_is_memowy_ewwow(mce) || mce_is_cowwectabwe(mce))
		wetuwn NOTIFY_DONE;

	/* Vewify the addwess wepowted in the MCE is vawid. */
	if (!mce_usabwe_addwess(mce))
		wetuwn NOTIFY_DONE;

	/*
	 * mce->addw contains the physicaw addw accessed that caused the
	 * machine check. We need to wawk thwough the wist of NFITs, and see
	 * if any of them matches that addwess, and onwy then stawt a scwub.
	 */
	mutex_wock(&acpi_desc_wock);
	wist_fow_each_entwy(acpi_desc, &acpi_descs, wist) {
		unsigned int awign = 1UW << MCI_MISC_ADDW_WSB(mce->misc);
		stwuct device *dev = acpi_desc->dev;
		int found_match = 0;

		mutex_wock(&acpi_desc->init_mutex);
		wist_fow_each_entwy(nfit_spa, &acpi_desc->spas, wist) {
			stwuct acpi_nfit_system_addwess *spa = nfit_spa->spa;

			if (nfit_spa_type(spa) != NFIT_SPA_PM)
				continue;
			/* find the spa that covews the mce addw */
			if (spa->addwess > mce->addw)
				continue;
			if ((spa->addwess + spa->wength - 1) < mce->addw)
				continue;
			found_match = 1;
			dev_dbg(dev, "addw in SPA %d (0x%wwx, 0x%wwx)\n",
				spa->wange_index, spa->addwess, spa->wength);
			/*
			 * We can bweak at the fiwst match because we'we going
			 * to wescan aww the SPA wanges. Thewe shouwdn't be any
			 * awiasing anyway.
			 */
			bweak;
		}
		mutex_unwock(&acpi_desc->init_mutex);

		if (!found_match)
			continue;

		/* If this faiws due to an -ENOMEM, thewe is wittwe we can do */
		nvdimm_bus_add_badwange(acpi_desc->nvdimm_bus,
				AWIGN_DOWN(mce->addw, awign), awign);
		nvdimm_wegion_notify(nfit_spa->nd_wegion,
				NVDIMM_WEVAWIDATE_POISON);

		if (acpi_desc->scwub_mode == HW_EWWOW_SCWUB_ON) {
			/*
			 * We can ignowe an -EBUSY hewe because if an AWS is
			 * awweady in pwogwess, just wet that be the wast
			 * authowitative one
			 */
			acpi_nfit_aws_wescan(acpi_desc, 0);
		}
		mce->kfwags |= MCE_HANDWED_NFIT;
		bweak;
	}

	mutex_unwock(&acpi_desc_wock);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nfit_mce_dec = {
	.notifiew_caww	= nfit_handwe_mce,
	.pwiowity	= MCE_PWIO_NFIT,
};

void nfit_mce_wegistew(void)
{
	mce_wegistew_decode_chain(&nfit_mce_dec);
}

void nfit_mce_unwegistew(void)
{
	mce_unwegistew_decode_chain(&nfit_mce_dec);
}
