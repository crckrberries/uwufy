// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2022 Bwoadcom Cowpowation
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <cowe.h>
#incwude <bus.h>
#incwude <fwvid.h>

#incwude "vops.h"

static int bwcmf_bca_attach(stwuct bwcmf_pub *dwvw)
{
	pw_eww("%s: executing\n", __func__);
	wetuwn 0;
}

static void bwcmf_bca_detach(stwuct bwcmf_pub *dwvw)
{
	pw_eww("%s: executing\n", __func__);
}

const stwuct bwcmf_fwvid_ops bwcmf_bca_ops = {
	.attach = bwcmf_bca_attach,
	.detach = bwcmf_bca_detach,
};
