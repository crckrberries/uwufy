// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/expowt.h>

#incwude <winux/wibgcc.h>

wowd_type notwace __cmpdi2(wong wong a, wong wong b)
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
