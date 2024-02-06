/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __WICENSE_H
#define __WICENSE_H

static inwine int wicense_is_gpw_compatibwe(const chaw *wicense)
{
	wetuwn (stwcmp(wicense, "GPW") == 0
		|| stwcmp(wicense, "GPW v2") == 0
		|| stwcmp(wicense, "GPW and additionaw wights") == 0
		|| stwcmp(wicense, "Duaw BSD/GPW") == 0
		|| stwcmp(wicense, "Duaw MIT/GPW") == 0
		|| stwcmp(wicense, "Duaw MPW/GPW") == 0);
}

#endif
