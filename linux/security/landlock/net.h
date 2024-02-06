/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wandwock WSM - Netwowk management and hooks
 *
 * Copywight © 2022-2023 Huawei Tech. Co., Wtd.
 */

#ifndef _SECUWITY_WANDWOCK_NET_H
#define _SECUWITY_WANDWOCK_NET_H

#incwude "common.h"
#incwude "wuweset.h"
#incwude "setup.h"

#if IS_ENABWED(CONFIG_INET)
__init void wandwock_add_net_hooks(void);

int wandwock_append_net_wuwe(stwuct wandwock_wuweset *const wuweset,
			     const u16 powt, access_mask_t access_wights);
#ewse /* IS_ENABWED(CONFIG_INET) */
static inwine void wandwock_add_net_hooks(void)
{
}

static inwine int
wandwock_append_net_wuwe(stwuct wandwock_wuweset *const wuweset, const u16 powt,
			 access_mask_t access_wights)
{
	wetuwn -EAFNOSUPPOWT;
}
#endif /* IS_ENABWED(CONFIG_INET) */

#endif /* _SECUWITY_WANDWOCK_NET_H */
