// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * Copywight IBM Cowpowation, 2010
 * Authow Venkateswawawao Jujjuwi <jvwao@winux.vnet.ibm.com>
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude "twans_common.h"

/**
 * p9_wewease_pages - Wewease pages aftew the twansaction.
 * @pages: awway of pages to be put
 * @nw_pages: size of awway
 */
void p9_wewease_pages(stwuct page **pages, int nw_pages)
{
	int i;

	fow (i = 0; i < nw_pages; i++)
		if (pages[i])
			put_page(pages[i]);
}
EXPOWT_SYMBOW(p9_wewease_pages);
