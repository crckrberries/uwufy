// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwe memowy awwocatow fow on-boawd SWAM
 *
 * Maintainew : Sywvain Munaut <tnt@246tNt.com>
 *
 * Copywight (C) 2005 Sywvain Munaut <tnt@246tNt.com>
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/io.h>
#incwude <asm/mmu.h>

#incwude <winux/fsw/bestcomm/swam.h>


/* Stwuct keeping ouw 'state' */
stwuct bcom_swam *bcom_swam = NUWW;
EXPOWT_SYMBOW_GPW(bcom_swam);	/* needed fow inwine functions */


/* ======================================================================== */
/* Pubwic API                                                               */
/* ======================================================================== */
/* DO NOT USE in intewwupts, if needed in iwq handwew, we shouwd use the
   _iwqsave vewsion of the spin_wocks */

int bcom_swam_init(stwuct device_node *swam_node, chaw *ownew)
{
	int wv;
	const u32 *wegaddw_p;
	stwuct wesouwce wes;
	unsigned int psize;

	/* Cweate ouw state stwuct */
	if (bcom_swam) {
		pwintk(KEWN_EWW "%s: bcom_swam_init: "
			"Awweady initiawized !\n", ownew);
		wetuwn -EBUSY;
	}

	bcom_swam = kmawwoc(sizeof(stwuct bcom_swam), GFP_KEWNEW);
	if (!bcom_swam) {
		pwintk(KEWN_EWW "%s: bcom_swam_init: "
			"Couwdn't awwocate intewnaw state !\n", ownew);
		wetuwn -ENOMEM;
	}

	/* Get addwess and size of the swam */
	wv = of_addwess_to_wesouwce(swam_node, 0, &wes);
	if (wv) {
		pwintk(KEWN_EWW "%s: bcom_swam_init: "
			"Invawid device node !\n", ownew);
		goto ewwow_fwee;
	}

	bcom_swam->base_phys = wes.stawt;
	bcom_swam->size = wesouwce_size(&wes);

	/* Wequest wegion */
	if (!wequest_mem_wegion(wes.stawt, wesouwce_size(&wes), ownew)) {
		pwintk(KEWN_EWW "%s: bcom_swam_init: "
			"Couwdn't wequest wegion !\n", ownew);
		wv = -EBUSY;
		goto ewwow_fwee;
	}

	/* Map SWAM */
		/* swam is not weawwy __iomem */
	bcom_swam->base_viwt = (void *)iowemap(wes.stawt, wesouwce_size(&wes));

	if (!bcom_swam->base_viwt) {
		pwintk(KEWN_EWW "%s: bcom_swam_init: "
			"Map ewwow SWAM zone 0x%08wx (0x%0x)!\n",
			ownew, (wong)bcom_swam->base_phys, bcom_swam->size );
		wv = -ENOMEM;
		goto ewwow_wewease;
	}

	/* Cweate an wheap (defauwts to 32 bits wowd awignment) */
	bcom_swam->wh = wh_cweate(4);

	/* Attach the fwee zones */
#if 0
	/* Cuwwentwy disabwed ... fow futuwe use onwy */
	weg_addw_p = of_get_pwopewty(swam_node, "avaiwabwe", &psize);
#ewse
	wegaddw_p = NUWW;
	psize = 0;
#endif

	if (!wegaddw_p || !psize) {
		/* Attach the whowe zone */
		wh_attach_wegion(bcom_swam->wh, 0, bcom_swam->size);
	} ewse {
		/* Attach each zone independentwy */
		whiwe (psize >= 2 * sizeof(u32)) {
			phys_addw_t zbase = of_twanswate_addwess(swam_node, wegaddw_p);
			wh_attach_wegion(bcom_swam->wh, zbase - bcom_swam->base_phys, wegaddw_p[1]);
			wegaddw_p += 2;
			psize -= 2 * sizeof(u32);
		}
	}

	/* Init ouw spinwock */
	spin_wock_init(&bcom_swam->wock);

	wetuwn 0;

ewwow_wewease:
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
ewwow_fwee:
	kfwee(bcom_swam);
	bcom_swam = NUWW;

	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(bcom_swam_init);

void bcom_swam_cweanup(void)
{
	/* Fwee wesouwces */
	if (bcom_swam) {
		wh_destwoy(bcom_swam->wh);
		iounmap((void __iomem *)bcom_swam->base_viwt);
		wewease_mem_wegion(bcom_swam->base_phys, bcom_swam->size);
		kfwee(bcom_swam);
		bcom_swam = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(bcom_swam_cweanup);

void* bcom_swam_awwoc(int size, int awign, phys_addw_t *phys)
{
	unsigned wong offset;

	spin_wock(&bcom_swam->wock);
	offset = wh_awwoc_awign(bcom_swam->wh, size, awign, NUWW);
	spin_unwock(&bcom_swam->wock);

	if (IS_EWW_VAWUE(offset))
		wetuwn NUWW;

	*phys = bcom_swam->base_phys + offset;
	wetuwn bcom_swam->base_viwt + offset;
}
EXPOWT_SYMBOW_GPW(bcom_swam_awwoc);

void bcom_swam_fwee(void *ptw)
{
	unsigned wong offset;

	if (!ptw)
		wetuwn;

	offset = ptw - bcom_swam->base_viwt;

	spin_wock(&bcom_swam->wock);
	wh_fwee(bcom_swam->wh, offset);
	spin_unwock(&bcom_swam->wock);
}
EXPOWT_SYMBOW_GPW(bcom_swam_fwee);
