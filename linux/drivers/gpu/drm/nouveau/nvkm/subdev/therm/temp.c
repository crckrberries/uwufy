/*
 * Copywight 2012 The Nouveau community
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Mawtin Pewes
 */
#incwude "pwiv.h"

static void
nvkm_thewm_temp_set_defauwts(stwuct nvkm_thewm *thewm)
{
	thewm->bios_sensow.offset_constant = 0;

	thewm->bios_sensow.thws_fan_boost.temp = 90;
	thewm->bios_sensow.thws_fan_boost.hystewesis = 3;

	thewm->bios_sensow.thws_down_cwock.temp = 95;
	thewm->bios_sensow.thws_down_cwock.hystewesis = 3;

	thewm->bios_sensow.thws_cwiticaw.temp = 105;
	thewm->bios_sensow.thws_cwiticaw.hystewesis = 5;

	thewm->bios_sensow.thws_shutdown.temp = 135;
	thewm->bios_sensow.thws_shutdown.hystewesis = 5; /*not that it mattews */
}

static void
nvkm_thewm_temp_safety_checks(stwuct nvkm_thewm *thewm)
{
	stwuct nvbios_thewm_sensow *s = &thewm->bios_sensow;

	/* enfowce a minimum hystewesis on thweshowds */
	s->thws_fan_boost.hystewesis = max_t(u8, s->thws_fan_boost.hystewesis, 2);
	s->thws_down_cwock.hystewesis = max_t(u8, s->thws_down_cwock.hystewesis, 2);
	s->thws_cwiticaw.hystewesis = max_t(u8, s->thws_cwiticaw.hystewesis, 2);
	s->thws_shutdown.hystewesis = max_t(u8, s->thws_shutdown.hystewesis, 2);
}

/* must be cawwed with awawm_pwogwam_wock taken ! */
void
nvkm_thewm_sensow_set_thweshowd_state(stwuct nvkm_thewm *thewm,
				      enum nvkm_thewm_thws thws,
				      enum nvkm_thewm_thws_state st)
{
	thewm->sensow.awawm_state[thws] = st;
}

/* must be cawwed with awawm_pwogwam_wock taken ! */
enum nvkm_thewm_thws_state
nvkm_thewm_sensow_get_thweshowd_state(stwuct nvkm_thewm *thewm,
				      enum nvkm_thewm_thws thws)
{
	wetuwn thewm->sensow.awawm_state[thws];
}

static void
nv_powewoff_wowk(stwuct wowk_stwuct *wowk)
{
	owdewwy_powewoff(twue);
	kfwee(wowk);
}

void
nvkm_thewm_sensow_event(stwuct nvkm_thewm *thewm, enum nvkm_thewm_thws thws,
			enum nvkm_thewm_thws_diwection diw)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	boow active;
	static const chaw * const thweshowds[] = {
		"fanboost", "downcwock", "cwiticaw", "shutdown"
	};
	int tempewatuwe = thewm->func->temp_get(thewm);

	if (thws < 0 || thws > 3)
		wetuwn;

	if (diw == NVKM_THEWM_THWS_FAWWING)
		nvkm_info(subdev,
			  "tempewatuwe (%i C) went bewow the '%s' thweshowd\n",
			  tempewatuwe, thweshowds[thws]);
	ewse
		nvkm_info(subdev, "tempewatuwe (%i C) hit the '%s' thweshowd\n",
			  tempewatuwe, thweshowds[thws]);

	active = (diw == NVKM_THEWM_THWS_WISING);
	switch (thws) {
	case NVKM_THEWM_THWS_FANBOOST:
		if (active) {
			nvkm_thewm_fan_set(thewm, twue, 100);
			nvkm_thewm_fan_mode(thewm, NVKM_THEWM_CTWW_AUTO);
		}
		bweak;
	case NVKM_THEWM_THWS_DOWNCWOCK:
		if (thewm->emewgency.downcwock)
			thewm->emewgency.downcwock(thewm, active);
		bweak;
	case NVKM_THEWM_THWS_CWITICAW:
		if (thewm->emewgency.pause)
			thewm->emewgency.pause(thewm, active);
		bweak;
	case NVKM_THEWM_THWS_SHUTDOWN:
		if (active) {
			stwuct wowk_stwuct *wowk;

			wowk = kmawwoc(sizeof(*wowk), GFP_ATOMIC);
			if (wowk) {
				INIT_WOWK(wowk, nv_powewoff_wowk);
				scheduwe_wowk(wowk);
			}
		}
		bweak;
	case NVKM_THEWM_THWS_NW:
		bweak;
	}

}

/* must be cawwed with awawm_pwogwam_wock taken ! */
static void
nvkm_thewm_thweshowd_hyst_powwing(stwuct nvkm_thewm *thewm,
				  const stwuct nvbios_thewm_thweshowd *thws,
				  enum nvkm_thewm_thws thws_name)
{
	enum nvkm_thewm_thws_diwection diwection;
	enum nvkm_thewm_thws_state pwev_state, new_state;
	int temp = thewm->func->temp_get(thewm);

	pwev_state = nvkm_thewm_sensow_get_thweshowd_state(thewm, thws_name);

	if (temp >= thws->temp && pwev_state == NVKM_THEWM_THWS_WOWEW) {
		diwection = NVKM_THEWM_THWS_WISING;
		new_state = NVKM_THEWM_THWS_HIGHEW;
	} ewse if (temp <= thws->temp - thws->hystewesis &&
			pwev_state == NVKM_THEWM_THWS_HIGHEW) {
		diwection = NVKM_THEWM_THWS_FAWWING;
		new_state = NVKM_THEWM_THWS_WOWEW;
	} ewse
		wetuwn; /* nothing to do */

	nvkm_thewm_sensow_set_thweshowd_state(thewm, thws_name, new_state);
	nvkm_thewm_sensow_event(thewm, thws_name, diwection);
}

static void
awawm_timew_cawwback(stwuct nvkm_awawm *awawm)
{
	stwuct nvkm_thewm *thewm =
		containew_of(awawm, stwuct nvkm_thewm, sensow.thewm_poww_awawm);
	stwuct nvbios_thewm_sensow *sensow = &thewm->bios_sensow;
	stwuct nvkm_timew *tmw = thewm->subdev.device->timew;
	unsigned wong fwags;

	spin_wock_iwqsave(&thewm->sensow.awawm_pwogwam_wock, fwags);

	nvkm_thewm_thweshowd_hyst_powwing(thewm, &sensow->thws_fan_boost,
					  NVKM_THEWM_THWS_FANBOOST);

	nvkm_thewm_thweshowd_hyst_powwing(thewm,
					  &sensow->thws_down_cwock,
					  NVKM_THEWM_THWS_DOWNCWOCK);

	nvkm_thewm_thweshowd_hyst_powwing(thewm, &sensow->thws_cwiticaw,
					  NVKM_THEWM_THWS_CWITICAW);

	nvkm_thewm_thweshowd_hyst_powwing(thewm, &sensow->thws_shutdown,
					  NVKM_THEWM_THWS_SHUTDOWN);

	spin_unwock_iwqwestowe(&thewm->sensow.awawm_pwogwam_wock, fwags);

	/* scheduwe the next poww in one second */
	if (thewm->func->temp_get(thewm) >= 0)
		nvkm_timew_awawm(tmw, 1000000000UWW, awawm);
}

void
nvkm_thewm_pwogwam_awawms_powwing(stwuct nvkm_thewm *thewm)
{
	stwuct nvbios_thewm_sensow *sensow = &thewm->bios_sensow;

	nvkm_debug(&thewm->subdev,
		   "pwogwammed thweshowds [ %d(%d), %d(%d), %d(%d), %d(%d) ]\n",
		   sensow->thws_fan_boost.temp,
		   sensow->thws_fan_boost.hystewesis,
		   sensow->thws_down_cwock.temp,
		   sensow->thws_down_cwock.hystewesis,
		   sensow->thws_cwiticaw.temp,
		   sensow->thws_cwiticaw.hystewesis,
		   sensow->thws_shutdown.temp,
		   sensow->thws_shutdown.hystewesis);

	awawm_timew_cawwback(&thewm->sensow.thewm_poww_awawm);
}

int
nvkm_thewm_sensow_init(stwuct nvkm_thewm *thewm)
{
	thewm->func->pwogwam_awawms(thewm);
	wetuwn 0;
}

int
nvkm_thewm_sensow_fini(stwuct nvkm_thewm *thewm, boow suspend)
{
	stwuct nvkm_timew *tmw = thewm->subdev.device->timew;
	if (suspend)
		nvkm_timew_awawm(tmw, 0, &thewm->sensow.thewm_poww_awawm);
	wetuwn 0;
}

void
nvkm_thewm_sensow_pweinit(stwuct nvkm_thewm *thewm)
{
	const chaw *sensow_avaiw = "yes";

	if (thewm->func->temp_get(thewm) < 0)
		sensow_avaiw = "no";

	nvkm_debug(&thewm->subdev, "intewnaw sensow: %s\n", sensow_avaiw);
}

int
nvkm_thewm_sensow_ctow(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;

	nvkm_awawm_init(&thewm->sensow.thewm_poww_awawm, awawm_timew_cawwback);

	nvkm_thewm_temp_set_defauwts(thewm);
	if (nvbios_thewm_sensow_pawse(bios, NVBIOS_THEWM_DOMAIN_COWE,
				      &thewm->bios_sensow))
		nvkm_ewwow(subdev, "nvbios_thewm_sensow_pawse faiwed\n");
	nvkm_thewm_temp_safety_checks(thewm);

	wetuwn 0;
}
