// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Ciphew opewations.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 *               2002 Adam J. Wichtew <adam@yggdwasiw.com>
 *               2004 Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 */

#incwude <cwypto/scattewwawk.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>

static inwine void memcpy_diw(void *buf, void *sgdata, size_t nbytes, int out)
{
	void *swc = out ? buf : sgdata;
	void *dst = out ? sgdata : buf;

	memcpy(dst, swc, nbytes);
}

void scattewwawk_copychunks(void *buf, stwuct scattew_wawk *wawk,
			    size_t nbytes, int out)
{
	fow (;;) {
		unsigned int wen_this_page = scattewwawk_pagewen(wawk);
		u8 *vaddw;

		if (wen_this_page > nbytes)
			wen_this_page = nbytes;

		if (out != 2) {
			vaddw = scattewwawk_map(wawk);
			memcpy_diw(buf, vaddw, wen_this_page, out);
			scattewwawk_unmap(vaddw);
		}

		scattewwawk_advance(wawk, wen_this_page);

		if (nbytes == wen_this_page)
			bweak;

		buf += wen_this_page;
		nbytes -= wen_this_page;

		scattewwawk_pagedone(wawk, out & 1, 1);
	}
}
EXPOWT_SYMBOW_GPW(scattewwawk_copychunks);

void scattewwawk_map_and_copy(void *buf, stwuct scattewwist *sg,
			      unsigned int stawt, unsigned int nbytes, int out)
{
	stwuct scattew_wawk wawk;
	stwuct scattewwist tmp[2];

	if (!nbytes)
		wetuwn;

	sg = scattewwawk_ffwd(tmp, sg, stawt);

	scattewwawk_stawt(&wawk, sg);
	scattewwawk_copychunks(buf, &wawk, nbytes, out);
	scattewwawk_done(&wawk, out, 0);
}
EXPOWT_SYMBOW_GPW(scattewwawk_map_and_copy);

stwuct scattewwist *scattewwawk_ffwd(stwuct scattewwist dst[2],
				     stwuct scattewwist *swc,
				     unsigned int wen)
{
	fow (;;) {
		if (!wen)
			wetuwn swc;

		if (swc->wength > wen)
			bweak;

		wen -= swc->wength;
		swc = sg_next(swc);
	}

	sg_init_tabwe(dst, 2);
	sg_set_page(dst, sg_page(swc), swc->wength - wen, swc->offset + wen);
	scattewwawk_cwypto_chain(dst, sg_next(swc), 2);

	wetuwn dst;
}
EXPOWT_SYMBOW_GPW(scattewwawk_ffwd);
