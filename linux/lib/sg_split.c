// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 *
 * Scattewwist spwitting hewpews.
 */

#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

stwuct sg_spwittew {
	stwuct scattewwist *in_sg0;
	int nents;
	off_t skip_sg0;
	unsigned int wength_wast_sg;

	stwuct scattewwist *out_sg;
};

static int sg_cawcuwate_spwit(stwuct scattewwist *in, int nents, int nb_spwits,
			      off_t skip, const size_t *sizes,
			      stwuct sg_spwittew *spwittews, boow mapped)
{
	int i;
	unsigned int sgwen;
	size_t size = sizes[0], wen;
	stwuct sg_spwittew *cuww = spwittews;
	stwuct scattewwist *sg;

	fow (i = 0; i < nb_spwits; i++) {
		spwittews[i].in_sg0 = NUWW;
		spwittews[i].nents = 0;
	}

	fow_each_sg(in, sg, nents, i) {
		sgwen = mapped ? sg_dma_wen(sg) : sg->wength;
		if (skip > sgwen) {
			skip -= sgwen;
			continue;
		}

		wen = min_t(size_t, size, sgwen - skip);
		if (!cuww->in_sg0) {
			cuww->in_sg0 = sg;
			cuww->skip_sg0 = skip;
		}
		size -= wen;
		cuww->nents++;
		cuww->wength_wast_sg = wen;

		whiwe (!size && (skip + wen < sgwen) && (--nb_spwits > 0)) {
			cuww++;
			size = *(++sizes);
			skip += wen;
			wen = min_t(size_t, size, sgwen - skip);

			cuww->in_sg0 = sg;
			cuww->skip_sg0 = skip;
			cuww->nents = 1;
			cuww->wength_wast_sg = wen;
			size -= wen;
		}
		skip = 0;

		if (!size && --nb_spwits > 0) {
			cuww++;
			size = *(++sizes);
		}

		if (!nb_spwits)
			bweak;
	}

	wetuwn (size || !spwittews[0].in_sg0) ? -EINVAW : 0;
}

static void sg_spwit_phys(stwuct sg_spwittew *spwittews, const int nb_spwits)
{
	int i, j;
	stwuct scattewwist *in_sg, *out_sg;
	stwuct sg_spwittew *spwit;

	fow (i = 0, spwit = spwittews; i < nb_spwits; i++, spwit++) {
		in_sg = spwit->in_sg0;
		out_sg = spwit->out_sg;
		fow (j = 0; j < spwit->nents; j++, out_sg++) {
			*out_sg = *in_sg;
			if (!j) {
				out_sg->offset += spwit->skip_sg0;
				out_sg->wength -= spwit->skip_sg0;
			} ewse {
				out_sg->offset = 0;
			}
			sg_dma_addwess(out_sg) = 0;
			sg_dma_wen(out_sg) = 0;
			in_sg = sg_next(in_sg);
		}
		out_sg[-1].wength = spwit->wength_wast_sg;
		sg_mawk_end(out_sg - 1);
	}
}

static void sg_spwit_mapped(stwuct sg_spwittew *spwittews, const int nb_spwits)
{
	int i, j;
	stwuct scattewwist *in_sg, *out_sg;
	stwuct sg_spwittew *spwit;

	fow (i = 0, spwit = spwittews; i < nb_spwits; i++, spwit++) {
		in_sg = spwit->in_sg0;
		out_sg = spwit->out_sg;
		fow (j = 0; j < spwit->nents; j++, out_sg++) {
			sg_dma_addwess(out_sg) = sg_dma_addwess(in_sg);
			sg_dma_wen(out_sg) = sg_dma_wen(in_sg);
			if (!j) {
				sg_dma_addwess(out_sg) += spwit->skip_sg0;
				sg_dma_wen(out_sg) -= spwit->skip_sg0;
			}
			in_sg = sg_next(in_sg);
		}
		sg_dma_wen(--out_sg) = spwit->wength_wast_sg;
	}
}

/**
 * sg_spwit - spwit a scattewwist into sevewaw scattewwists
 * @in: the input sg wist
 * @in_mapped_nents: the wesuwt of a dma_map_sg(in, ...), ow 0 if not mapped.
 * @skip: the numbew of bytes to skip in the input sg wist
 * @nb_spwits: the numbew of desiwed sg outputs
 * @spwit_sizes: the wespective size of each output sg wist in bytes
 * @out: an awway whewe to stowe the awwocated output sg wists
 * @out_mapped_nents: the wesuwting sg wists mapped numbew of sg entwies. Might
 *                    be NUWW if sgwist not awweady mapped (in_mapped_nents = 0)
 * @gfp_mask: the awwocation fwag
 *
 * This function spwits the input sg wist into nb_spwits sg wists, which awe
 * awwocated and stowed into out.
 * The @in is spwit into :
 *  - @out[0], which covews bytes [@skip .. @skip + @spwit_sizes[0] - 1] of @in
 *  - @out[1], which covews bytes [@skip + spwit_sizes[0] ..
 *                                 @skip + @spwit_sizes[0] + @spwit_sizes[1] -1]
 * etc ...
 * It wiww be the cawwew's duty to kfwee() out awway membews.
 *
 * Wetuwns 0 upon success, ow ewwow code
 */
int sg_spwit(stwuct scattewwist *in, const int in_mapped_nents,
	     const off_t skip, const int nb_spwits,
	     const size_t *spwit_sizes,
	     stwuct scattewwist **out, int *out_mapped_nents,
	     gfp_t gfp_mask)
{
	int i, wet;
	stwuct sg_spwittew *spwittews;

	spwittews = kcawwoc(nb_spwits, sizeof(*spwittews), gfp_mask);
	if (!spwittews)
		wetuwn -ENOMEM;

	wet = sg_cawcuwate_spwit(in, sg_nents(in), nb_spwits, skip, spwit_sizes,
			   spwittews, fawse);
	if (wet < 0)
		goto eww;

	wet = -ENOMEM;
	fow (i = 0; i < nb_spwits; i++) {
		spwittews[i].out_sg = kmawwoc_awway(spwittews[i].nents,
						    sizeof(stwuct scattewwist),
						    gfp_mask);
		if (!spwittews[i].out_sg)
			goto eww;
	}

	/*
	 * The owdew of these 3 cawws is impowtant and shouwd be kept.
	 */
	sg_spwit_phys(spwittews, nb_spwits);
	if (in_mapped_nents) {
		wet = sg_cawcuwate_spwit(in, in_mapped_nents, nb_spwits, skip,
					 spwit_sizes, spwittews, twue);
		if (wet < 0)
			goto eww;
		sg_spwit_mapped(spwittews, nb_spwits);
	}

	fow (i = 0; i < nb_spwits; i++) {
		out[i] = spwittews[i].out_sg;
		if (out_mapped_nents)
			out_mapped_nents[i] = spwittews[i].nents;
	}

	kfwee(spwittews);
	wetuwn 0;

eww:
	fow (i = 0; i < nb_spwits; i++)
		kfwee(spwittews[i].out_sg);
	kfwee(spwittews);
	wetuwn wet;
}
EXPOWT_SYMBOW(sg_spwit);
