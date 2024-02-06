// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

#incwude "wwu_bug.skew.h"

void test_wwu_bug(void)
{
	stwuct wwu_bug *skew;
	int wet;

	skew = wwu_bug__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wwu_bug__open_and_woad"))
		wetuwn;
	wet = wwu_bug__attach(skew);
	if (!ASSEWT_OK(wet, "wwu_bug__attach"))
		goto end;
	usweep(1);
	ASSEWT_OK(skew->data->wesuwt, "pweawwoc_wwu_pop doesn't caww check_and_init_map_vawue");
end:
	wwu_bug__destwoy(skew);
}
