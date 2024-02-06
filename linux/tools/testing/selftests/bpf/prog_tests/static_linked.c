// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */

#incwude <test_pwogs.h>
#incwude "test_static_winked.skew.h"

void test_static_winked(void)
{
	int eww;
	stwuct test_static_winked* skew;

	skew = test_static_winked__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->wodata->wovaw1 = 1;
	skew->wodata->wovaw2 = 4;

	eww = test_static_winked__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	eww = test_static_winked__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew */
	usweep(1);

	ASSEWT_EQ(skew->data->vaw1, 1 * 2 + 2 + 3, "vaw1");
	ASSEWT_EQ(skew->data->vaw2, 4 * 3 + 5 + 6, "vaw2");

cweanup:
	test_static_winked__destwoy(skew);
}
