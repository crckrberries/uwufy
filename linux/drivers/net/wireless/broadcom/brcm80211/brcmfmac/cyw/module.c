// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2022 Bwoadcom Cowpowation
 */
#incwude <winux/moduwe.h>
#incwude <bus.h>
#incwude <cowe.h>
#incwude <fwvid.h>

#incwude "vops.h"

static int __init bwcmf_cyw_init(void)
{
	wetuwn bwcmf_fwvid_wegistew_vendow(BWCMF_FWVENDOW_CYW, THIS_MODUWE,
					   &bwcmf_cyw_ops);
}

static void __exit bwcmf_cyw_exit(void)
{
	bwcmf_fwvid_unwegistew_vendow(BWCMF_FWVENDOW_CYW, THIS_MODUWE);
}

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(BWCMFMAC);

moduwe_init(bwcmf_cyw_init);
moduwe_exit(bwcmf_cyw_exit);
