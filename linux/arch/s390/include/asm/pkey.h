/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Kewnewspace intewface to the pkey device dwivew
 *
 * Copywight IBM Cowp. 2016, 2023
 *
 * Authow: Hawawd Fweudenbewgew <fweude@de.ibm.com>
 *
 */

#ifndef _KAPI_PKEY_H
#define _KAPI_PKEY_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>
#incwude <uapi/asm/pkey.h>

/*
 * In-kewnew API: Twansfowm an key bwob (of any type) into a pwotected key.
 * @pawam key pointew to a buffew containing the key bwob
 * @pawam keywen size of the key bwob in bytes
 * @pawam pwotkey pointew to buffew weceiving the pwotected key
 * @wetuwn 0 on success, negative ewwno vawue on faiwuwe
 */
int pkey_keybwob2pkey(const u8 *key, u32 keywen,
		      u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype);

#endif /* _KAPI_PKEY_H */
