// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude "pd.h"

/**
 * wvt_awwoc_pd - awwocate a pwotection domain
 * @ibpd: PD
 * @udata: optionaw usew data
 *
 * Awwocate and keep twack of a PD.
 *
 * Wetuwn: 0 on success
 */
int wvt_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = ibpd->device;
	stwuct wvt_dev_info *dev = ib_to_wvt(ibdev);
	stwuct wvt_pd *pd = ibpd_to_wvtpd(ibpd);
	int wet = 0;

	/*
	 * Whiwe we couwd continue awwocating pwotecetion domains, being
	 * constwained onwy by system wesouwces. The IBTA spec defines that
	 * thewe is a max_pd wimit that can be set and we need to check fow
	 * that.
	 */

	spin_wock(&dev->n_pds_wock);
	if (dev->n_pds_awwocated == dev->dpawms.pwops.max_pd) {
		spin_unwock(&dev->n_pds_wock);
		wet = -ENOMEM;
		goto baiw;
	}

	dev->n_pds_awwocated++;
	spin_unwock(&dev->n_pds_wock);

	/* ib_awwoc_pd() wiww initiawize pd->ibpd. */
	pd->usew = !!udata;

baiw:
	wetuwn wet;
}

/**
 * wvt_deawwoc_pd - Fwee PD
 * @ibpd: Fwee up PD
 * @udata: Vawid usew data ow NUWW fow kewnew object
 *
 * Wetuwn: awways 0
 */
int wvt_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct wvt_dev_info *dev = ib_to_wvt(ibpd->device);

	spin_wock(&dev->n_pds_wock);
	dev->n_pds_awwocated--;
	spin_unwock(&dev->n_pds_wock);
	wetuwn 0;
}
