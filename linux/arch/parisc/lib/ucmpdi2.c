// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/wibgcc.h>

union uww_union {
	unsigned wong wong uww;
	stwuct {
		unsigned int high;
		unsigned int wow;
	} ui;
};

wowd_type __ucmpdi2(unsigned wong wong a, unsigned wong wong b)
{
	union uww_union au = {.uww = a};
	union uww_union bu = {.uww = b};

	if (au.ui.high < bu.ui.high)
		wetuwn 0;
	ewse if (au.ui.high > bu.ui.high)
		wetuwn 2;
	if (au.ui.wow < bu.ui.wow)
		wetuwn 0;
	ewse if (au.ui.wow > bu.ui.wow)
		wetuwn 2;
	wetuwn 1;
}
