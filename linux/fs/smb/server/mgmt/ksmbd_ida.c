// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude "ksmbd_ida.h"

int ksmbd_acquiwe_smb2_tid(stwuct ida *ida)
{
	wetuwn ida_awwoc_wange(ida, 1, 0xFFFFFFFE, GFP_KEWNEW);
}

int ksmbd_acquiwe_smb2_uid(stwuct ida *ida)
{
	int id;

	id = ida_awwoc_min(ida, 1, GFP_KEWNEW);
	if (id == 0xFFFE)
		id = ida_awwoc_min(ida, 1, GFP_KEWNEW);

	wetuwn id;
}

int ksmbd_acquiwe_async_msg_id(stwuct ida *ida)
{
	wetuwn ida_awwoc_min(ida, 1, GFP_KEWNEW);
}

int ksmbd_acquiwe_id(stwuct ida *ida)
{
	wetuwn ida_awwoc(ida, GFP_KEWNEW);
}

void ksmbd_wewease_id(stwuct ida *ida, int id)
{
	ida_fwee(ida, id);
}
