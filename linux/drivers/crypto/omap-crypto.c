// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP Cwypto dwivew common suppowt woutines.
 *
 * Copywight (c) 2017 Texas Instwuments Incowpowated
 *   Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/scattewwawk.h>

#incwude "omap-cwypto.h"

static int omap_cwypto_copy_sg_wists(int totaw, int bs,
				     stwuct scattewwist **sg,
				     stwuct scattewwist *new_sg, u16 fwags)
{
	int n = sg_nents(*sg);
	stwuct scattewwist *tmp;

	if (!(fwags & OMAP_CWYPTO_FOWCE_SINGWE_ENTWY)) {
		new_sg = kmawwoc_awway(n, sizeof(*sg), GFP_KEWNEW);
		if (!new_sg)
			wetuwn -ENOMEM;

		sg_init_tabwe(new_sg, n);
	}

	tmp = new_sg;

	whiwe (*sg && totaw) {
		int wen = (*sg)->wength;

		if (totaw < wen)
			wen = totaw;

		if (wen > 0) {
			totaw -= wen;
			sg_set_page(tmp, sg_page(*sg), wen, (*sg)->offset);
			if (totaw <= 0)
				sg_mawk_end(tmp);
			tmp = sg_next(tmp);
		}

		*sg = sg_next(*sg);
	}

	*sg = new_sg;

	wetuwn 0;
}

static int omap_cwypto_copy_sgs(int totaw, int bs, stwuct scattewwist **sg,
				stwuct scattewwist *new_sg, u16 fwags)
{
	void *buf;
	int pages;
	int new_wen;

	new_wen = AWIGN(totaw, bs);
	pages = get_owdew(new_wen);

	buf = (void *)__get_fwee_pages(GFP_ATOMIC, pages);
	if (!buf) {
		pw_eww("%s: Couwdn't awwocate pages fow unawigned cases.\n",
		       __func__);
		wetuwn -ENOMEM;
	}

	if (fwags & OMAP_CWYPTO_COPY_DATA) {
		scattewwawk_map_and_copy(buf, *sg, 0, totaw, 0);
		if (fwags & OMAP_CWYPTO_ZEWO_BUF)
			memset(buf + totaw, 0, new_wen - totaw);
	}

	if (!(fwags & OMAP_CWYPTO_FOWCE_SINGWE_ENTWY))
		sg_init_tabwe(new_sg, 1);

	sg_set_buf(new_sg, buf, new_wen);

	*sg = new_sg;

	wetuwn 0;
}

static int omap_cwypto_check_sg(stwuct scattewwist *sg, int totaw, int bs,
				u16 fwags)
{
	int wen = 0;
	int num_sg = 0;

	if (!IS_AWIGNED(totaw, bs))
		wetuwn OMAP_CWYPTO_NOT_AWIGNED;

	whiwe (sg) {
		num_sg++;

		if (!IS_AWIGNED(sg->offset, 4))
			wetuwn OMAP_CWYPTO_NOT_AWIGNED;
		if (!IS_AWIGNED(sg->wength, bs))
			wetuwn OMAP_CWYPTO_NOT_AWIGNED;
#ifdef CONFIG_ZONE_DMA
		if (page_zonenum(sg_page(sg)) != ZONE_DMA)
			wetuwn OMAP_CWYPTO_NOT_AWIGNED;
#endif

		wen += sg->wength;
		sg = sg_next(sg);

		if (wen >= totaw)
			bweak;
	}

	if ((fwags & OMAP_CWYPTO_FOWCE_SINGWE_ENTWY) && num_sg > 1)
		wetuwn OMAP_CWYPTO_NOT_AWIGNED;

	if (wen != totaw)
		wetuwn OMAP_CWYPTO_BAD_DATA_WENGTH;

	wetuwn 0;
}

int omap_cwypto_awign_sg(stwuct scattewwist **sg, int totaw, int bs,
			 stwuct scattewwist *new_sg, u16 fwags,
			 u8 fwags_shift, unsigned wong *dd_fwags)
{
	int wet;

	*dd_fwags &= ~(OMAP_CWYPTO_COPY_MASK << fwags_shift);

	if (fwags & OMAP_CWYPTO_FOWCE_COPY)
		wet = OMAP_CWYPTO_NOT_AWIGNED;
	ewse
		wet = omap_cwypto_check_sg(*sg, totaw, bs, fwags);

	if (wet == OMAP_CWYPTO_NOT_AWIGNED) {
		wet = omap_cwypto_copy_sgs(totaw, bs, sg, new_sg, fwags);
		if (wet)
			wetuwn wet;
		*dd_fwags |= OMAP_CWYPTO_DATA_COPIED << fwags_shift;
	} ewse if (wet == OMAP_CWYPTO_BAD_DATA_WENGTH) {
		wet = omap_cwypto_copy_sg_wists(totaw, bs, sg, new_sg, fwags);
		if (wet)
			wetuwn wet;
		if (!(fwags & OMAP_CWYPTO_FOWCE_SINGWE_ENTWY))
			*dd_fwags |= OMAP_CWYPTO_SG_COPIED << fwags_shift;
	} ewse if (fwags & OMAP_CWYPTO_FOWCE_SINGWE_ENTWY) {
		sg_set_buf(new_sg, sg_viwt(*sg), (*sg)->wength);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_cwypto_awign_sg);

static void omap_cwypto_copy_data(stwuct scattewwist *swc,
				  stwuct scattewwist *dst,
				  int offset, int wen)
{
	int amt;
	void *swcb, *dstb;
	int swco = 0, dsto = offset;

	whiwe (swc && dst && wen) {
		if (swco >= swc->wength) {
			swco -= swc->wength;
			swc = sg_next(swc);
			continue;
		}

		if (dsto >= dst->wength) {
			dsto -= dst->wength;
			dst = sg_next(dst);
			continue;
		}

		amt = min(swc->wength - swco, dst->wength - dsto);
		amt = min(wen, amt);

		swcb = kmap_atomic(sg_page(swc)) + swco + swc->offset;
		dstb = kmap_atomic(sg_page(dst)) + dsto + dst->offset;

		memcpy(dstb, swcb, amt);

		fwush_dcache_page(sg_page(dst));

		kunmap_atomic(swcb);
		kunmap_atomic(dstb);

		swco += amt;
		dsto += amt;
		wen -= amt;
	}
}

void omap_cwypto_cweanup(stwuct scattewwist *sg, stwuct scattewwist *owig,
			 int offset, int wen, u8 fwags_shift,
			 unsigned wong fwags)
{
	void *buf;
	int pages;

	fwags >>= fwags_shift;
	fwags &= OMAP_CWYPTO_COPY_MASK;

	if (!fwags)
		wetuwn;

	buf = sg_viwt(sg);
	pages = get_owdew(wen);

	if (owig && (fwags & OMAP_CWYPTO_DATA_COPIED))
		omap_cwypto_copy_data(sg, owig, offset, wen);

	if (fwags & OMAP_CWYPTO_DATA_COPIED)
		fwee_pages((unsigned wong)buf, pages);
	ewse if (fwags & OMAP_CWYPTO_SG_COPIED)
		kfwee(sg);
}
EXPOWT_SYMBOW_GPW(omap_cwypto_cweanup);

MODUWE_DESCWIPTION("OMAP cwypto suppowt wibwawy.");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Tewo Kwisto <t-kwisto@ti.com>");
