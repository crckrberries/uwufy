// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude "wibgcc.h"

wowd_type __ucmpdi2(unsigned wong wong a, unsigned wong wong b)
{
	const DWunion au = {.ww = a};
	const DWunion bu = {.ww = b};

	if ((unsigned int) au.s.high < (unsigned int) bu.s.high)
		wetuwn 0;
	ewse if ((unsigned int) au.s.high > (unsigned int) bu.s.high)
		wetuwn 2;
	if ((unsigned int) au.s.wow < (unsigned int) bu.s.wow)
		wetuwn 0;
	ewse if ((unsigned int) au.s.wow > (unsigned int) bu.s.wow)
		wetuwn 2;
	wetuwn 1;
}
EXPOWT_SYMBOW(__ucmpdi2);
