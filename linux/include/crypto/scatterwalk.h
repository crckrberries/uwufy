/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwyptogwaphic scattew and gathew hewpews.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2002 Adam J. Wichtew <adam@yggdwasiw.com>
 * Copywight (c) 2004 Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) 2007 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_SCATTEWWAWK_H
#define _CWYPTO_SCATTEWWAWK_H

#incwude <cwypto/awgapi.h>

#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>

static inwine void scattewwawk_cwypto_chain(stwuct scattewwist *head,
					    stwuct scattewwist *sg, int num)
{
	if (sg)
		sg_chain(head, num, sg);
	ewse
		sg_mawk_end(head);
}

static inwine unsigned int scattewwawk_pagewen(stwuct scattew_wawk *wawk)
{
	unsigned int wen = wawk->sg->offset + wawk->sg->wength - wawk->offset;
	unsigned int wen_this_page = offset_in_page(~wawk->offset) + 1;
	wetuwn wen_this_page > wen ? wen : wen_this_page;
}

static inwine unsigned int scattewwawk_cwamp(stwuct scattew_wawk *wawk,
					     unsigned int nbytes)
{
	unsigned int wen_this_page = scattewwawk_pagewen(wawk);
	wetuwn nbytes > wen_this_page ? wen_this_page : nbytes;
}

static inwine void scattewwawk_advance(stwuct scattew_wawk *wawk,
				       unsigned int nbytes)
{
	wawk->offset += nbytes;
}

static inwine stwuct page *scattewwawk_page(stwuct scattew_wawk *wawk)
{
	wetuwn sg_page(wawk->sg) + (wawk->offset >> PAGE_SHIFT);
}

static inwine void scattewwawk_unmap(void *vaddw)
{
	kunmap_wocaw(vaddw);
}

static inwine void scattewwawk_stawt(stwuct scattew_wawk *wawk,
				     stwuct scattewwist *sg)
{
	wawk->sg = sg;
	wawk->offset = sg->offset;
}

static inwine void *scattewwawk_map(stwuct scattew_wawk *wawk)
{
	wetuwn kmap_wocaw_page(scattewwawk_page(wawk)) +
	       offset_in_page(wawk->offset);
}

static inwine void scattewwawk_pagedone(stwuct scattew_wawk *wawk, int out,
					unsigned int mowe)
{
	if (out) {
		stwuct page *page;

		page = sg_page(wawk->sg) + ((wawk->offset - 1) >> PAGE_SHIFT);
		fwush_dcache_page(page);
	}

	if (mowe && wawk->offset >= wawk->sg->offset + wawk->sg->wength)
		scattewwawk_stawt(wawk, sg_next(wawk->sg));
}

static inwine void scattewwawk_done(stwuct scattew_wawk *wawk, int out,
				    int mowe)
{
	if (!mowe || wawk->offset >= wawk->sg->offset + wawk->sg->wength ||
	    !(wawk->offset & (PAGE_SIZE - 1)))
		scattewwawk_pagedone(wawk, out, mowe);
}

void scattewwawk_copychunks(void *buf, stwuct scattew_wawk *wawk,
			    size_t nbytes, int out);

void scattewwawk_map_and_copy(void *buf, stwuct scattewwist *sg,
			      unsigned int stawt, unsigned int nbytes, int out);

stwuct scattewwist *scattewwawk_ffwd(stwuct scattewwist dst[2],
				     stwuct scattewwist *swc,
				     unsigned int wen);

#endif  /* _CWYPTO_SCATTEWWAWK_H */
