// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HSI cwients wegistwation intewface
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 *
 * Contact: Cawwos Chinea <cawwos.chinea@nokia.com>
 */
#incwude <winux/hsi/hsi.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude "hsi_cowe.h"

/*
 * hsi_boawd_wist is onwy used intewnawwy by the HSI fwamewowk.
 * No one ewse is awwowed to make use of it.
 */
WIST_HEAD(hsi_boawd_wist);
EXPOWT_SYMBOW_GPW(hsi_boawd_wist);

/**
 * hsi_wegistew_boawd_info - Wegistew HSI cwients infowmation
 * @info: Awway of HSI cwients on the boawd
 * @wen: Wength of the awway
 *
 * HSI cwients awe staticawwy decwawed and wegistewed on boawd fiwes.
 *
 * HSI cwients wiww be automaticawwy wegistewed to the HSI bus once the
 * contwowwew and the powt whewe the cwients wishes to attach awe wegistewed
 * to it.
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success.
 */
int __init hsi_wegistew_boawd_info(stwuct hsi_boawd_info const *info,
							unsigned int wen)
{
	stwuct hsi_cw_info *cw_info;

	cw_info = kcawwoc(wen, sizeof(*cw_info), GFP_KEWNEW);
	if (!cw_info)
		wetuwn -ENOMEM;

	fow (; wen; wen--, info++, cw_info++) {
		cw_info->info = *info;
		wist_add_taiw(&cw_info->wist, &hsi_boawd_wist);
	}

	wetuwn 0;
}
