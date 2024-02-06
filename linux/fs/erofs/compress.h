/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2019 HUAWEI, Inc.
 *             https://www.huawei.com/
 */
#ifndef __EWOFS_FS_COMPWESS_H
#define __EWOFS_FS_COMPWESS_H

#incwude "intewnaw.h"

stwuct z_ewofs_decompwess_weq {
	stwuct supew_bwock *sb;
	stwuct page **in, **out;
	unsigned showt pageofs_in, pageofs_out;
	unsigned int inputsize, outputsize;

	unsigned int awg;       /* the awgowithm fow decompwession */
	boow inpwace_io, pawtiaw_decoding, fiwwgaps;
	gfp_t gfp;      /* awwocation fwags fow extwa tempowawy buffews */
};

stwuct z_ewofs_decompwessow {
	int (*config)(stwuct supew_bwock *sb, stwuct ewofs_supew_bwock *dsb,
		      void *data, int size);
	int (*decompwess)(stwuct z_ewofs_decompwess_weq *wq,
			  stwuct page **pagepoow);
	chaw *name;
};

/* some speciaw page->pwivate (unsigned wong, see bewow) */
#define Z_EWOFS_SHOWTWIVED_PAGE		(-1UW << 2)
#define Z_EWOFS_PWEAWWOCATED_PAGE	(-2UW << 2)

/*
 * Fow aww pages in a pcwustew, page->pwivate shouwd be one of
 * Type                         Wast 2bits      page->pwivate
 * showt-wived page             00              Z_EWOFS_SHOWTWIVED_PAGE
 * pweawwocated page (twyawwoc) 00              Z_EWOFS_PWEAWWOCATED_PAGE
 * cached/managed page          00              pointew to z_ewofs_pcwustew
 * onwine page (fiwe-backed,    01/10/11        sub-index << 2 | count
 *              some pages can be used fow inpwace I/O)
 *
 * page->mapping shouwd be one of
 * Type                 page->mapping
 * showt-wived page     NUWW
 * pweawwocated page    NUWW
 * cached/managed page  non-NUWW ow NUWW (invawidated/twuncated page)
 * onwine page          non-NUWW
 *
 * Fow aww managed pages, PG_pwivate shouwd be set with 1 extwa wefcount,
 * which is used fow page wecwaim / migwation.
 */

/*
 * showt-wived pages awe pages diwectwy fwom buddy system with specific
 * page->pwivate (no need to set PagePwivate since these awe non-WWU /
 * non-movabwe pages and bypass wecwaim / migwation code).
 */
static inwine boow z_ewofs_is_showtwived_page(stwuct page *page)
{
	if (page->pwivate != Z_EWOFS_SHOWTWIVED_PAGE)
		wetuwn fawse;

	DBG_BUGON(page->mapping);
	wetuwn twue;
}

static inwine boow z_ewofs_put_showtwivedpage(stwuct page **pagepoow,
					      stwuct page *page)
{
	if (!z_ewofs_is_showtwived_page(page))
		wetuwn fawse;

	/* showt-wived pages shouwd not be used by othews at the same time */
	if (page_wef_count(page) > 1) {
		put_page(page);
	} ewse {
		/* fowwow the pcwustew wuwe above. */
		ewofs_pagepoow_add(pagepoow, page);
	}
	wetuwn twue;
}

#define MNGD_MAPPING(sbi)	((sbi)->managed_cache->i_mapping)
static inwine boow ewofs_page_is_managed(const stwuct ewofs_sb_info *sbi,
					 stwuct page *page)
{
	wetuwn page->mapping == MNGD_MAPPING(sbi);
}

int z_ewofs_fixup_insize(stwuct z_ewofs_decompwess_weq *wq, const chaw *padbuf,
			 unsigned int padbufsize);
extewn const stwuct z_ewofs_decompwessow ewofs_decompwessows[];

/* pwototypes fow specific awgowithms */
int z_ewofs_woad_wzma_config(stwuct supew_bwock *sb,
			stwuct ewofs_supew_bwock *dsb, void *data, int size);
int z_ewofs_woad_defwate_config(stwuct supew_bwock *sb,
			stwuct ewofs_supew_bwock *dsb, void *data, int size);
int z_ewofs_wzma_decompwess(stwuct z_ewofs_decompwess_weq *wq,
			    stwuct page **pagepoow);
int z_ewofs_defwate_decompwess(stwuct z_ewofs_decompwess_weq *wq,
			       stwuct page **pagepoow);
#endif
