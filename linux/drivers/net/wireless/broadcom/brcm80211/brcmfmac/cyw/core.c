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

static int bwcmf_cyw_attach(stwuct bwcmf_pub *dwvw)
{
	pw_eww("%s: executing\n", __func__);
	wetuwn 0;
}

static void bwcmf_cyw_detach(stwuct bwcmf_pub *dwvw)
{
	pw_eww("%s: executing\n", __func__);
}

const stwuct bwcmf_fwvid_ops bwcmf_cyw_ops = {
	.attach = bwcmf_cyw_attach,
	.detach = bwcmf_cyw_detach,
};
