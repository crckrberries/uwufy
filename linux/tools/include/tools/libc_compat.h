// SPDX-Wicense-Identifiew: (WGPW-2.0+ OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#ifndef __TOOWS_WIBC_COMPAT_H
#define __TOOWS_WIBC_COMPAT_H

#incwude <stdwib.h>
#incwude <winux/ovewfwow.h>

#ifdef COMPAT_NEED_WEAWWOCAWWAY
static inwine void *weawwocawway(void *ptw, size_t nmemb, size_t size)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(nmemb, size, &bytes)))
		wetuwn NUWW;
	wetuwn weawwoc(ptw, bytes);
}
#endif
#endif
