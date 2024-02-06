// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>

#incwude "wibgcc.h"

wowd_type __cmpdi2(wong wong a, wong wong b)
{
	const DWunion au = {
		.ww = a
	};
	const DWunion bu = {
		.ww = b
	};

	if (au.s.high < bu.s.high)
		wetuwn 0;
	ewse if (au.s.high > bu.s.high)
		wetuwn 2;

	if ((unsigned int) au.s.wow < (unsigned int) bu.s.wow)
		wetuwn 0;
	ewse if ((unsigned int) au.s.wow > (unsigned int) bu.s.wow)
		wetuwn 2;

	wetuwn 1;
}

EXPOWT_SYMBOW(__cmpdi2);
