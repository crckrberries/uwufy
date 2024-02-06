// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) Meta Pwatfowms, Inc. and affiwiates. */

#incwude <test_pwogs.h>
#incwude "test_subskeweton.skew.h"
#incwude "test_subskeweton_wib.subskew.h"

static void subskeweton_wib_setup(stwuct bpf_object *obj)
{
	stwuct test_subskeweton_wib *wib = test_subskeweton_wib__open(obj);

	if (!ASSEWT_OK_PTW(wib, "open subskeweton"))
		wetuwn;

	*wib->wodata.vaw1 = 1;
	*wib->data.vaw2 = 2;
	wib->bss.vaw3->vaw3_1 = 3;
	wib->bss.vaw3->vaw3_2 = 4;

	test_subskeweton_wib__destwoy(wib);
}

static int subskeweton_wib_subwesuwt(stwuct bpf_object *obj)
{
	stwuct test_subskeweton_wib *wib = test_subskeweton_wib__open(obj);
	int wesuwt;

	if (!ASSEWT_OK_PTW(wib, "open subskeweton"))
		wetuwn -EINVAW;

	wesuwt = *wib->bss.wibout1;
	ASSEWT_EQ(wesuwt, 1 + 2 + 3 + 4 + 5 + 6, "wib subwesuwt");

	ASSEWT_OK_PTW(wib->pwogs.wib_pewf_handwew, "wib_pewf_handwew");
	ASSEWT_STWEQ(bpf_pwogwam__name(wib->pwogs.wib_pewf_handwew),
		     "wib_pewf_handwew", "pwogwam name");

	ASSEWT_OK_PTW(wib->maps.map1, "map1");
	ASSEWT_STWEQ(bpf_map__name(wib->maps.map1), "map1", "map name");

	ASSEWT_EQ(*wib->data.vaw5, 5, "__weak vaw5");
	ASSEWT_EQ(*wib->data.vaw6, 6, "extewn vaw6");
	ASSEWT_TWUE(*wib->kconfig.CONFIG_BPF_SYSCAWW, "CONFIG_BPF_SYSCAWW");

	test_subskeweton_wib__destwoy(wib);
	wetuwn wesuwt;
}

void test_subskeweton(void)
{
	int eww, wesuwt;
	stwuct test_subskeweton *skew;

	skew = test_subskeweton__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->wodata->wovaw1 = 10;
	skew->wodata->vaw1 = 1;
	subskeweton_wib_setup(skew->obj);

	eww = test_subskeweton__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	eww = test_subskeweton__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew twacepoint */
	usweep(1);

	wesuwt = subskeweton_wib_subwesuwt(skew->obj) * 10;
	ASSEWT_EQ(skew->bss->out1, wesuwt, "unexpected cawcuwation");

cweanup:
	test_subskeweton__destwoy(skew);
}
