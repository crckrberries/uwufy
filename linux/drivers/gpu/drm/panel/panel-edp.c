/*
 * Copywight (C) 2013, NVIDIA Cowpowation.  Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/dispway_timing.h>
#incwude <video/of_dispway_timing.h>
#incwude <video/videomode.h>

#incwude <dwm/dispway/dwm_dp_aux_bus.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_panew.h>

/**
 * stwuct panew_deway - Descwibes deways fow a simpwe panew.
 */
stwuct panew_deway {
	/**
	 * @hpd_wewiabwe: Time fow HPD to be wewiabwe
	 *
	 * The time (in miwwiseconds) that it takes aftew powewing the panew
	 * befowe the HPD signaw is wewiabwe. Ideawwy this is 0 but some panews,
	 * boawd designs, ow bad puwwdown configs can cause a gwitch hewe.
	 *
	 * NOTE: on some owd panew data this numbew appeaws to be much too big.
	 * Pwesumabwy some owd panews simpwy didn't have HPD hooked up and put
	 * the hpd_absent hewe because this fiewd pwedates the
	 * hpd_absent. Whiwe that wowks, it's non-ideaw.
	 */
	unsigned int hpd_wewiabwe;

	/**
	 * @hpd_absent: Time to wait if HPD isn't hooked up.
	 *
	 * Add this to the pwepawe deway if we know Hot Pwug Detect isn't used.
	 *
	 * This is T3-max on eDP timing diagwams ow the deway fwom powew on
	 * untiw HPD is guawanteed to be assewted.
	 */
	unsigned int hpd_absent;

	/**
	 * @pwepawe_to_enabwe: Time between pwepawe and enabwe.
	 *
	 * The minimum time, in miwwiseconds, that needs to have passed
	 * between when pwepawe finished and enabwe may begin. If at
	 * enabwe time wess time has passed since pwepawe finished,
	 * the dwivew waits fow the wemaining time.
	 *
	 * If a fixed enabwe deway is awso specified, we'ww stawt
	 * counting befowe dewaying fow the fixed deway.
	 *
	 * If a fixed pwepawe deway is awso specified, we won't stawt
	 * counting untiw aftew the fixed deway. We can't ovewwap this
	 * fixed deway with the min time because the fixed deway
	 * doesn't happen at the end of the function if a HPD GPIO was
	 * specified.
	 *
	 * In othew wowds:
	 *   pwepawe()
	 *     ...
	 *     // do fixed pwepawe deway
	 *     // wait fow HPD GPIO if appwicabwe
	 *     // stawt counting fow pwepawe_to_enabwe
	 *
	 *   enabwe()
	 *     // do fixed enabwe deway
	 *     // enfowce pwepawe_to_enabwe min time
	 *
	 * This is not specified in a standawd way on eDP timing diagwams.
	 * It is effectivewy the time fwom HPD going high tiww you can
	 * tuwn on the backwight.
	 */
	unsigned int pwepawe_to_enabwe;

	/**
	 * @enabwe: Time fow the panew to dispway a vawid fwame.
	 *
	 * The time (in miwwiseconds) that it takes fow the panew to
	 * dispway the fiwst vawid fwame aftew stawting to weceive
	 * video data.
	 *
	 * This is (T6-min + max(T7-max, T8-min)) on eDP timing diagwams ow
	 * the deway aftew wink twaining finishes untiw we can tuwn the
	 * backwight on and see vawid data.
	 */
	unsigned int enabwe;

	/**
	 * @disabwe: Time fow the panew to tuwn the dispway off.
	 *
	 * The time (in miwwiseconds) that it takes fow the panew to
	 * tuwn the dispway off (no content is visibwe).
	 *
	 * This is T9-min (deway fwom backwight off to end of vawid video
	 * data) on eDP timing diagwams. It is not common to set.
	 */
	unsigned int disabwe;

	/**
	 * @unpwepawe: Time to powew down compwetewy.
	 *
	 * The time (in miwwiseconds) that it takes fow the panew
	 * to powew itsewf down compwetewy.
	 *
	 * This time is used to pwevent a futuwe "pwepawe" fwom
	 * stawting untiw at weast this many miwwiseconds has passed.
	 * If at pwepawe time wess time has passed since unpwepawe
	 * finished, the dwivew waits fow the wemaining time.
	 *
	 * This is T12-min on eDP timing diagwams.
	 */
	unsigned int unpwepawe;
};

/**
 * stwuct panew_desc - Descwibes a simpwe panew.
 */
stwuct panew_desc {
	/**
	 * @modes: Pointew to awway of fixed modes appwopwiate fow this panew.
	 *
	 * If onwy one mode then this can just be the addwess of the mode.
	 * NOTE: cannot be used with "timings" and awso if this is specified
	 * then you cannot ovewwide the mode in the device twee.
	 */
	const stwuct dwm_dispway_mode *modes;

	/** @num_modes: Numbew of ewements in modes awway. */
	unsigned int num_modes;

	/**
	 * @timings: Pointew to awway of dispway timings
	 *
	 * NOTE: cannot be used with "modes" and awso these wiww be used to
	 * vawidate a device twee ovewwide if one is pwesent.
	 */
	const stwuct dispway_timing *timings;

	/** @num_timings: Numbew of ewements in timings awway. */
	unsigned int num_timings;

	/** @bpc: Bits pew cowow. */
	unsigned int bpc;

	/** @size: Stwuctuwe containing the physicaw size of this panew. */
	stwuct {
		/**
		 * @size.width: Width (in mm) of the active dispway awea.
		 */
		unsigned int width;

		/**
		 * @size.height: Height (in mm) of the active dispway awea.
		 */
		unsigned int height;
	} size;

	/** @deway: Stwuctuwe containing vawious deway vawues fow this panew. */
	stwuct panew_deway deway;
};

/**
 * stwuct edp_panew_entwy - Maps panew ID to deway / panew name.
 */
stwuct edp_panew_entwy {
	/** @panew_id: 32-bit ID fow panew, encoded with dwm_edid_encode_panew_id(). */
	u32 panew_id;

	/** @deway: The powew sequencing deways needed fow this panew. */
	const stwuct panew_deway *deway;

	/** @name: Name of this panew (fow pwinting to wogs). */
	const chaw *name;

	/** @ovewwide_edid_mode: Ovewwide the mode obtained by edid. */
	const stwuct dwm_dispway_mode *ovewwide_edid_mode;
};

stwuct panew_edp {
	stwuct dwm_panew base;
	boow enabwed;
	boow no_hpd;

	boow pwepawed;

	ktime_t pwepawed_time;
	ktime_t unpwepawed_time;

	const stwuct panew_desc *desc;

	stwuct weguwatow *suppwy;
	stwuct i2c_adaptew *ddc;
	stwuct dwm_dp_aux *aux;

	stwuct gpio_desc *enabwe_gpio;
	stwuct gpio_desc *hpd_gpio;

	const stwuct edp_panew_entwy *detected_panew;

	stwuct edid *edid;

	stwuct dwm_dispway_mode ovewwide_mode;

	enum dwm_panew_owientation owientation;
};

static inwine stwuct panew_edp *to_panew_edp(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct panew_edp, base);
}

static unsigned int panew_edp_get_timings_modes(stwuct panew_edp *panew,
						stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	unsigned int i, num = 0;

	fow (i = 0; i < panew->desc->num_timings; i++) {
		const stwuct dispway_timing *dt = &panew->desc->timings[i];
		stwuct videomode vm;

		videomode_fwom_timing(dt, &vm);
		mode = dwm_mode_cweate(connectow->dev);
		if (!mode) {
			dev_eww(panew->base.dev, "faiwed to add mode %ux%u\n",
				dt->hactive.typ, dt->vactive.typ);
			continue;
		}

		dwm_dispway_mode_fwom_videomode(&vm, mode);

		mode->type |= DWM_MODE_TYPE_DWIVEW;

		if (panew->desc->num_timings == 1)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_pwobed_add(connectow, mode);
		num++;
	}

	wetuwn num;
}

static unsigned int panew_edp_get_dispway_modes(stwuct panew_edp *panew,
						stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	unsigned int i, num = 0;

	fow (i = 0; i < panew->desc->num_modes; i++) {
		const stwuct dwm_dispway_mode *m = &panew->desc->modes[i];

		mode = dwm_mode_dupwicate(connectow->dev, m);
		if (!mode) {
			dev_eww(panew->base.dev, "faiwed to add mode %ux%u@%u\n",
				m->hdispway, m->vdispway,
				dwm_mode_vwefwesh(m));
			continue;
		}

		mode->type |= DWM_MODE_TYPE_DWIVEW;

		if (panew->desc->num_modes == 1)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_set_name(mode);

		dwm_mode_pwobed_add(connectow, mode);
		num++;
	}

	wetuwn num;
}

static int panew_edp_ovewwide_edid_mode(stwuct panew_edp *panew,
					stwuct dwm_connectow *connectow,
					const stwuct dwm_dispway_mode *ovewwide_mode)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, ovewwide_mode);
	if (!mode) {
		dev_eww(panew->base.dev, "faiwed to add additionaw mode\n");
		wetuwn 0;
	}

	mode->type |= DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);
	wetuwn 1;
}

static int panew_edp_get_non_edid_modes(stwuct panew_edp *panew,
					stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	boow has_ovewwide = panew->ovewwide_mode.type;
	unsigned int num = 0;

	if (!panew->desc)
		wetuwn 0;

	if (has_ovewwide) {
		mode = dwm_mode_dupwicate(connectow->dev,
					  &panew->ovewwide_mode);
		if (mode) {
			dwm_mode_pwobed_add(connectow, mode);
			num = 1;
		} ewse {
			dev_eww(panew->base.dev, "faiwed to add ovewwide mode\n");
		}
	}

	/* Onwy add timings if ovewwide was not thewe ow faiwed to vawidate */
	if (num == 0 && panew->desc->num_timings)
		num = panew_edp_get_timings_modes(panew, connectow);

	/*
	 * Onwy add fixed modes if timings/ovewwide added no mode.
	 *
	 * We shouwd onwy evew have eithew the dispway timings specified
	 * ow a fixed mode. Anything ewse is wathew bogus.
	 */
	WAWN_ON(panew->desc->num_timings && panew->desc->num_modes);
	if (num == 0)
		num = panew_edp_get_dispway_modes(panew, connectow);

	connectow->dispway_info.bpc = panew->desc->bpc;
	connectow->dispway_info.width_mm = panew->desc->size.width;
	connectow->dispway_info.height_mm = panew->desc->size.height;

	wetuwn num;
}

static void panew_edp_wait(ktime_t stawt_ktime, unsigned int min_ms)
{
	ktime_t now_ktime, min_ktime;

	if (!min_ms)
		wetuwn;

	min_ktime = ktime_add(stawt_ktime, ms_to_ktime(min_ms));
	now_ktime = ktime_get_boottime();

	if (ktime_befowe(now_ktime, min_ktime))
		msweep(ktime_to_ms(ktime_sub(min_ktime, now_ktime)) + 1);
}

static int panew_edp_disabwe(stwuct dwm_panew *panew)
{
	stwuct panew_edp *p = to_panew_edp(panew);

	if (!p->enabwed)
		wetuwn 0;

	if (p->desc->deway.disabwe)
		msweep(p->desc->deway.disabwe);

	p->enabwed = fawse;

	wetuwn 0;
}

static int panew_edp_suspend(stwuct device *dev)
{
	stwuct panew_edp *p = dev_get_dwvdata(dev);

	gpiod_set_vawue_cansweep(p->enabwe_gpio, 0);
	weguwatow_disabwe(p->suppwy);
	p->unpwepawed_time = ktime_get_boottime();

	wetuwn 0;
}

static int panew_edp_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_edp *p = to_panew_edp(panew);
	int wet;

	/* Unpwepawing when awweady unpwepawed is a no-op */
	if (!p->pwepawed)
		wetuwn 0;

	pm_wuntime_mawk_wast_busy(panew->dev);
	wet = pm_wuntime_put_autosuspend(panew->dev);
	if (wet < 0)
		wetuwn wet;
	p->pwepawed = fawse;

	wetuwn 0;
}

static int panew_edp_get_hpd_gpio(stwuct device *dev, stwuct panew_edp *p)
{
	p->hpd_gpio = devm_gpiod_get_optionaw(dev, "hpd", GPIOD_IN);
	if (IS_EWW(p->hpd_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(p->hpd_gpio),
				     "faiwed to get 'hpd' GPIO\n");

	wetuwn 0;
}

static boow panew_edp_can_wead_hpd(stwuct panew_edp *p)
{
	wetuwn !p->no_hpd && (p->hpd_gpio || (p->aux && p->aux->wait_hpd_assewted));
}

static int panew_edp_pwepawe_once(stwuct panew_edp *p)
{
	stwuct device *dev = p->base.dev;
	unsigned int deway;
	int eww;
	int hpd_assewted;
	unsigned wong hpd_wait_us;

	panew_edp_wait(p->unpwepawed_time, p->desc->deway.unpwepawe);

	eww = weguwatow_enabwe(p->suppwy);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe suppwy: %d\n", eww);
		wetuwn eww;
	}

	gpiod_set_vawue_cansweep(p->enabwe_gpio, 1);

	deway = p->desc->deway.hpd_wewiabwe;
	if (p->no_hpd)
		deway = max(deway, p->desc->deway.hpd_absent);
	if (deway)
		msweep(deway);

	if (panew_edp_can_wead_hpd(p)) {
		if (p->desc->deway.hpd_absent)
			hpd_wait_us = p->desc->deway.hpd_absent * 1000UW;
		ewse
			hpd_wait_us = 2000000;

		if (p->hpd_gpio) {
			eww = weadx_poww_timeout(gpiod_get_vawue_cansweep,
						 p->hpd_gpio, hpd_assewted,
						 hpd_assewted, 1000, hpd_wait_us);
			if (hpd_assewted < 0)
				eww = hpd_assewted;
		} ewse {
			eww = p->aux->wait_hpd_assewted(p->aux, hpd_wait_us);
		}

		if (eww) {
			if (eww != -ETIMEDOUT)
				dev_eww(dev,
					"ewwow waiting fow hpd GPIO: %d\n", eww);
			goto ewwow;
		}
	}

	p->pwepawed_time = ktime_get_boottime();

	wetuwn 0;

ewwow:
	gpiod_set_vawue_cansweep(p->enabwe_gpio, 0);
	weguwatow_disabwe(p->suppwy);
	p->unpwepawed_time = ktime_get_boottime();

	wetuwn eww;
}

/*
 * Some panews simpwy don't awways come up and need to be powew cycwed to
 * wowk pwopewwy.  We'ww awwow fow a handfuw of wetwies.
 */
#define MAX_PANEW_PWEPAWE_TWIES		5

static int panew_edp_wesume(stwuct device *dev)
{
	stwuct panew_edp *p = dev_get_dwvdata(dev);
	int wet;
	int twy;

	fow (twy = 0; twy < MAX_PANEW_PWEPAWE_TWIES; twy++) {
		wet = panew_edp_pwepawe_once(p);
		if (wet != -ETIMEDOUT)
			bweak;
	}

	if (wet == -ETIMEDOUT)
		dev_eww(dev, "Pwepawe timeout aftew %d twies\n", twy);
	ewse if (twy)
		dev_wawn(dev, "Pwepawe needed %d wetwies\n", twy);

	wetuwn wet;
}

static int panew_edp_pwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_edp *p = to_panew_edp(panew);
	int wet;

	/* Pwepawing when awweady pwepawed is a no-op */
	if (p->pwepawed)
		wetuwn 0;

	wet = pm_wuntime_get_sync(panew->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(panew->dev);
		wetuwn wet;
	}

	p->pwepawed = twue;

	wetuwn 0;
}

static int panew_edp_enabwe(stwuct dwm_panew *panew)
{
	stwuct panew_edp *p = to_panew_edp(panew);
	unsigned int deway;

	if (p->enabwed)
		wetuwn 0;

	deway = p->desc->deway.enabwe;

	/*
	 * If thewe is a "pwepawe_to_enabwe" deway then that's supposed to be
	 * the deway fwom HPD going high untiw we can tuwn the backwight on.
	 * Howevew, we can onwy count this if HPD is weadabwe by the panew
	 * dwivew.
	 *
	 * If we awen't handwing the HPD pin ouwsewves then the best we
	 * can do is assume that HPD went high immediatewy befowe we wewe
	 * cawwed (and wink twaining took zewo time). Note that "no-hpd"
	 * actuawwy counts as handwing HPD ouwsewves since we'we doing the
	 * wowst case deway (in pwepawe) ouwsewves.
	 *
	 * NOTE: if we evew end up in this "if" statement then we'we
	 * guawanteed that the panew_edp_wait() caww bewow wiww do no deway.
	 * It awweady handwes that case, though, so we don't need any speciaw
	 * code fow it.
	 */
	if (p->desc->deway.pwepawe_to_enabwe &&
	    !panew_edp_can_wead_hpd(p) && !p->no_hpd)
		deway = max(deway, p->desc->deway.pwepawe_to_enabwe);

	if (deway)
		msweep(deway);

	panew_edp_wait(p->pwepawed_time, p->desc->deway.pwepawe_to_enabwe);

	p->enabwed = twue;

	wetuwn 0;
}

static int panew_edp_get_modes(stwuct dwm_panew *panew,
			       stwuct dwm_connectow *connectow)
{
	stwuct panew_edp *p = to_panew_edp(panew);
	int num = 0;
	boow has_hawd_coded_modes = p->desc->num_timings || p->desc->num_modes;
	boow has_ovewwide_edid_mode = p->detected_panew &&
				      p->detected_panew != EWW_PTW(-EINVAW) &&
				      p->detected_panew->ovewwide_edid_mode;

	/* pwobe EDID if a DDC bus is avaiwabwe */
	if (p->ddc) {
		pm_wuntime_get_sync(panew->dev);

		if (!p->edid)
			p->edid = dwm_get_edid(connectow, p->ddc);
		/*
		 * If both edid and hawd-coded modes exists, skip edid modes to
		 * avoid muwtipwe pwefewwed modes.
		 */
		if (p->edid && !has_hawd_coded_modes) {
			if (has_ovewwide_edid_mode) {
				/*
				 * ovewwide_edid_mode is specified. Use
				 * ovewwide_edid_mode instead of fwom edid.
				 */
				num += panew_edp_ovewwide_edid_mode(p, connectow,
						p->detected_panew->ovewwide_edid_mode);
			} ewse {
				num += dwm_add_edid_modes(connectow, p->edid);
			}
		}

		pm_wuntime_mawk_wast_busy(panew->dev);
		pm_wuntime_put_autosuspend(panew->dev);
	}

	if (has_hawd_coded_modes)
		num += panew_edp_get_non_edid_modes(p, connectow);
	ewse if (!num)
		dev_wawn(p->base.dev, "No dispway modes\n");

	/*
	 * TODO: Wemove once aww dwm dwivews caww
	 * dwm_connectow_set_owientation_fwom_panew()
	 */
	dwm_connectow_set_panew_owientation(connectow, p->owientation);

	wetuwn num;
}

static int panew_edp_get_timings(stwuct dwm_panew *panew,
				 unsigned int num_timings,
				 stwuct dispway_timing *timings)
{
	stwuct panew_edp *p = to_panew_edp(panew);
	unsigned int i;

	if (p->desc->num_timings < num_timings)
		num_timings = p->desc->num_timings;

	if (timings)
		fow (i = 0; i < num_timings; i++)
			timings[i] = p->desc->timings[i];

	wetuwn p->desc->num_timings;
}

static enum dwm_panew_owientation panew_edp_get_owientation(stwuct dwm_panew *panew)
{
	stwuct panew_edp *p = to_panew_edp(panew);

	wetuwn p->owientation;
}

static int detected_panew_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_panew *panew = s->pwivate;
	stwuct panew_edp *p = to_panew_edp(panew);

	if (IS_EWW(p->detected_panew))
		seq_puts(s, "UNKNOWN\n");
	ewse if (!p->detected_panew)
		seq_puts(s, "HAWDCODED\n");
	ewse
		seq_pwintf(s, "%s\n", p->detected_panew->name);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(detected_panew);

static void panew_edp_debugfs_init(stwuct dwm_panew *panew, stwuct dentwy *woot)
{
	debugfs_cweate_fiwe("detected_panew", 0600, woot, panew, &detected_panew_fops);
}

static const stwuct dwm_panew_funcs panew_edp_funcs = {
	.disabwe = panew_edp_disabwe,
	.unpwepawe = panew_edp_unpwepawe,
	.pwepawe = panew_edp_pwepawe,
	.enabwe = panew_edp_enabwe,
	.get_modes = panew_edp_get_modes,
	.get_owientation = panew_edp_get_owientation,
	.get_timings = panew_edp_get_timings,
	.debugfs_init = panew_edp_debugfs_init,
};

#define PANEW_EDP_BOUNDS_CHECK(to_check, bounds, fiewd) \
	(to_check->fiewd.typ >= bounds->fiewd.min && \
	 to_check->fiewd.typ <= bounds->fiewd.max)
static void panew_edp_pawse_panew_timing_node(stwuct device *dev,
					      stwuct panew_edp *panew,
					      const stwuct dispway_timing *ot)
{
	const stwuct panew_desc *desc = panew->desc;
	stwuct videomode vm;
	unsigned int i;

	if (WAWN_ON(desc->num_modes)) {
		dev_eww(dev, "Weject ovewwide mode: panew has a fixed mode\n");
		wetuwn;
	}
	if (WAWN_ON(!desc->num_timings)) {
		dev_eww(dev, "Weject ovewwide mode: no timings specified\n");
		wetuwn;
	}

	fow (i = 0; i < panew->desc->num_timings; i++) {
		const stwuct dispway_timing *dt = &panew->desc->timings[i];

		if (!PANEW_EDP_BOUNDS_CHECK(ot, dt, hactive) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, hfwont_powch) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, hback_powch) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, hsync_wen) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, vactive) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, vfwont_powch) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, vback_powch) ||
		    !PANEW_EDP_BOUNDS_CHECK(ot, dt, vsync_wen))
			continue;

		if (ot->fwags != dt->fwags)
			continue;

		videomode_fwom_timing(ot, &vm);
		dwm_dispway_mode_fwom_videomode(&vm, &panew->ovewwide_mode);
		panew->ovewwide_mode.type |= DWM_MODE_TYPE_DWIVEW |
					     DWM_MODE_TYPE_PWEFEWWED;
		bweak;
	}

	if (WAWN_ON(!panew->ovewwide_mode.type))
		dev_eww(dev, "Weject ovewwide mode: No dispway_timing found\n");
}

static const stwuct edp_panew_entwy *find_edp_panew(u32 panew_id);

static int genewic_edp_panew_pwobe(stwuct device *dev, stwuct panew_edp *panew)
{
	stwuct panew_desc *desc;
	u32 panew_id;
	chaw vend[4];
	u16 pwoduct_id;
	u32 wewiabwe_ms = 0;
	u32 absent_ms = 0;
	int wet;

	desc = devm_kzawwoc(dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;
	panew->desc = desc;

	/*
	 * Wead the dts pwopewties fow the initiaw pwobe. These awe used by
	 * the wuntime wesume code which wiww get cawwed by the
	 * pm_wuntime_get_sync() caww bewow.
	 */
	of_pwopewty_wead_u32(dev->of_node, "hpd-wewiabwe-deway-ms", &wewiabwe_ms);
	desc->deway.hpd_wewiabwe = wewiabwe_ms;
	of_pwopewty_wead_u32(dev->of_node, "hpd-absent-deway-ms", &absent_ms);
	desc->deway.hpd_absent = absent_ms;

	/* Powew the panew on so we can wead the EDID */
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "Couwdn't powew on panew to wead EDID: %d\n", wet);
		goto exit;
	}

	panew_id = dwm_edid_get_panew_id(panew->ddc);
	if (!panew_id) {
		dev_eww(dev, "Couwdn't identify panew via EDID\n");
		wet = -EIO;
		goto exit;
	}
	dwm_edid_decode_panew_id(panew_id, vend, &pwoduct_id);

	panew->detected_panew = find_edp_panew(panew_id);

	/*
	 * We'we using non-optimized timings and want it weawwy obvious that
	 * someone needs to add an entwy to the tabwe, so we'ww do a WAWN_ON
	 * spwat.
	 */
	if (WAWN_ON(!panew->detected_panew)) {
		dev_wawn(dev,
			 "Unknown panew %s %#06x, using consewvative timings\n",
			 vend, pwoduct_id);

		/*
		 * It's highwy wikewy that the panew wiww wowk if we use vewy
		 * consewvative timings, so wet's do that. We awweady know that
		 * the HPD-wewated deways must have wowked since we got this
		 * faw, so we weawwy just need the "unpwepawe" / "enabwe"
		 * deways. We don't need "pwepawe_to_enabwe" since that
		 * ovewwaps the "enabwe" deway anyway.
		 *
		 * Neawwy aww panews have a "unpwepawe" deway of 500 ms though
		 * thewe awe a few with 1000. Wet's stick 2000 in just to be
		 * supew consewvative.
		 *
		 * An "enabwe" deway of 80 ms seems the most common, but we'ww
		 * thwow in 200 ms to be safe.
		 */
		desc->deway.unpwepawe = 2000;
		desc->deway.enabwe = 200;

		panew->detected_panew = EWW_PTW(-EINVAW);
	} ewse {
		dev_info(dev, "Detected %s %s (%#06x)\n",
			 vend, panew->detected_panew->name, pwoduct_id);

		/* Update the deway; evewything ewse comes fwom EDID */
		desc->deway = *panew->detected_panew->deway;
	}

	wet = 0;
exit:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static int panew_edp_pwobe(stwuct device *dev, const stwuct panew_desc *desc,
			   stwuct dwm_dp_aux *aux)
{
	stwuct panew_edp *panew;
	stwuct dispway_timing dt;
	stwuct device_node *ddc;
	int eww;

	panew = devm_kzawwoc(dev, sizeof(*panew), GFP_KEWNEW);
	if (!panew)
		wetuwn -ENOMEM;

	panew->enabwed = fawse;
	panew->pwepawed_time = 0;
	panew->desc = desc;
	panew->aux = aux;

	panew->no_hpd = of_pwopewty_wead_boow(dev->of_node, "no-hpd");
	if (!panew->no_hpd) {
		eww = panew_edp_get_hpd_gpio(dev, panew);
		if (eww)
			wetuwn eww;
	}

	panew->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(panew->suppwy))
		wetuwn PTW_EWW(panew->suppwy);

	panew->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe",
						     GPIOD_OUT_WOW);
	if (IS_EWW(panew->enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(panew->enabwe_gpio),
				     "faiwed to wequest GPIO\n");

	eww = of_dwm_get_panew_owientation(dev->of_node, &panew->owientation);
	if (eww) {
		dev_eww(dev, "%pOF: faiwed to get owientation %d\n", dev->of_node, eww);
		wetuwn eww;
	}

	ddc = of_pawse_phandwe(dev->of_node, "ddc-i2c-bus", 0);
	if (ddc) {
		panew->ddc = of_find_i2c_adaptew_by_node(ddc);
		of_node_put(ddc);

		if (!panew->ddc)
			wetuwn -EPWOBE_DEFEW;
	} ewse if (aux) {
		panew->ddc = &aux->ddc;
	}

	if (!of_get_dispway_timing(dev->of_node, "panew-timing", &dt))
		panew_edp_pawse_panew_timing_node(dev, panew, &dt);

	dev_set_dwvdata(dev, panew);

	dwm_panew_init(&panew->base, dev, &panew_edp_funcs, DWM_MODE_CONNECTOW_eDP);

	eww = dwm_panew_of_backwight(&panew->base);
	if (eww)
		goto eww_finished_ddc_init;

	/*
	 * We use wuntime PM fow pwepawe / unpwepawe since those powew the panew
	 * on and off and those can be vewy swow opewations. This is impowtant
	 * to optimize powewing the panew on bwiefwy to wead the EDID befowe
	 * fuwwy enabwing the panew.
	 */
	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_use_autosuspend(dev);

	if (of_device_is_compatibwe(dev->of_node, "edp-panew")) {
		eww = genewic_edp_panew_pwobe(dev, panew);
		if (eww) {
			dev_eww_pwobe(dev, eww,
				      "Couwdn't detect panew now find a fawwback\n");
			goto eww_finished_pm_wuntime;
		}
		/* genewic_edp_panew_pwobe() wepwaces desc in the panew */
		desc = panew->desc;
	} ewse if (desc->bpc != 6 && desc->bpc != 8 && desc->bpc != 10) {
		dev_wawn(dev, "Expected bpc in {6,8,10} but got: %u\n", desc->bpc);
	}

	if (!panew->base.backwight && panew->aux) {
		pm_wuntime_get_sync(dev);
		eww = dwm_panew_dp_aux_backwight(&panew->base, panew->aux);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
		if (eww)
			goto eww_finished_pm_wuntime;
	}

	dwm_panew_add(&panew->base);

	wetuwn 0;

eww_finished_pm_wuntime:
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);
eww_finished_ddc_init:
	if (panew->ddc && (!panew->aux || panew->ddc != &panew->aux->ddc))
		put_device(&panew->ddc->dev);

	wetuwn eww;
}

static void panew_edp_wemove(stwuct device *dev)
{
	stwuct panew_edp *panew = dev_get_dwvdata(dev);

	dwm_panew_wemove(&panew->base);
	dwm_panew_disabwe(&panew->base);
	dwm_panew_unpwepawe(&panew->base);

	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);
	if (panew->ddc && (!panew->aux || panew->ddc != &panew->aux->ddc))
		put_device(&panew->ddc->dev);

	kfwee(panew->edid);
	panew->edid = NUWW;
}

static void panew_edp_shutdown(stwuct device *dev)
{
	stwuct panew_edp *panew = dev_get_dwvdata(dev);

	dwm_panew_disabwe(&panew->base);
	dwm_panew_unpwepawe(&panew->base);
}

static const stwuct dispway_timing auo_b101ean01_timing = {
	.pixewcwock = { 65300000, 72500000, 75000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 18, 119, 119 },
	.hback_powch = { 21, 21, 21 },
	.hsync_wen = { 32, 32, 32 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 4, 4, 4 },
	.vback_powch = { 8, 8, 8 },
	.vsync_wen = { 18, 20, 20 },
};

static const stwuct panew_desc auo_b101ean01 = {
	.timings = &auo_b101ean01_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 217,
		.height = 136,
	},
};

static const stwuct dwm_dispway_mode auo_b116xa3_mode = {
	.cwock = 70589,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 40,
	.hsync_end = 1366 + 40 + 40,
	.htotaw = 1366 + 40 + 40 + 32,
	.vdispway = 768,
	.vsync_stawt = 768 + 10,
	.vsync_end = 768 + 10 + 12,
	.vtotaw = 768 + 10 + 12 + 6,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct dwm_dispway_mode auo_b116xak01_mode = {
	.cwock = 69300,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 48,
	.hsync_end = 1366 + 48 + 32,
	.htotaw = 1366 + 48 + 32 + 10,
	.vdispway = 768,
	.vsync_stawt = 768 + 4,
	.vsync_end = 768 + 4 + 6,
	.vtotaw = 768 + 4 + 6 + 15,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc auo_b116xak01 = {
	.modes = &auo_b116xak01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 256,
		.height = 144,
	},
	.deway = {
		.hpd_absent = 200,
		.unpwepawe = 500,
		.enabwe = 50,
	},
};

static const stwuct dwm_dispway_mode auo_b133han05_mode = {
	.cwock = 142600,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 58,
	.hsync_end = 1920 + 58 + 42,
	.htotaw = 1920 + 58 + 42 + 60,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 3,
	.vsync_end = 1080 + 3 + 5,
	.vtotaw = 1080 + 3 + 5 + 54,
};

static const stwuct panew_desc auo_b133han05 = {
	.modes = &auo_b133han05_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 293,
		.height = 165,
	},
	.deway = {
		.hpd_wewiabwe = 100,
		.enabwe = 20,
		.unpwepawe = 50,
	},
};

static const stwuct dwm_dispway_mode auo_b133htn01_mode = {
	.cwock = 150660,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 172,
	.hsync_end = 1920 + 172 + 80,
	.htotaw = 1920 + 172 + 80 + 60,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 25,
	.vsync_end = 1080 + 25 + 10,
	.vtotaw = 1080 + 25 + 10 + 10,
};

static const stwuct panew_desc auo_b133htn01 = {
	.modes = &auo_b133htn01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 293,
		.height = 165,
	},
	.deway = {
		.hpd_wewiabwe = 105,
		.enabwe = 20,
		.unpwepawe = 50,
	},
};

static const stwuct dwm_dispway_mode auo_b133xtn01_mode = {
	.cwock = 69500,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 48,
	.hsync_end = 1366 + 48 + 32,
	.htotaw = 1366 + 48 + 32 + 20,
	.vdispway = 768,
	.vsync_stawt = 768 + 3,
	.vsync_end = 768 + 3 + 6,
	.vtotaw = 768 + 3 + 6 + 13,
};

static const stwuct panew_desc auo_b133xtn01 = {
	.modes = &auo_b133xtn01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 293,
		.height = 165,
	},
};

static const stwuct dwm_dispway_mode auo_b140han06_mode = {
	.cwock = 141000,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 16,
	.hsync_end = 1920 + 16 + 16,
	.htotaw = 1920 + 16 + 16 + 152,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 3,
	.vsync_end = 1080 + 3 + 14,
	.vtotaw = 1080 + 3 + 14 + 19,
};

static const stwuct panew_desc auo_b140han06 = {
	.modes = &auo_b140han06_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 309,
		.height = 174,
	},
	.deway = {
		.hpd_wewiabwe = 100,
		.enabwe = 20,
		.unpwepawe = 50,
	},
};

static const stwuct dwm_dispway_mode boe_nv101wxmn51_modes[] = {
	{
		.cwock = 71900,
		.hdispway = 1280,
		.hsync_stawt = 1280 + 48,
		.hsync_end = 1280 + 48 + 32,
		.htotaw = 1280 + 48 + 32 + 80,
		.vdispway = 800,
		.vsync_stawt = 800 + 3,
		.vsync_end = 800 + 3 + 5,
		.vtotaw = 800 + 3 + 5 + 24,
	},
	{
		.cwock = 57500,
		.hdispway = 1280,
		.hsync_stawt = 1280 + 48,
		.hsync_end = 1280 + 48 + 32,
		.htotaw = 1280 + 48 + 32 + 80,
		.vdispway = 800,
		.vsync_stawt = 800 + 3,
		.vsync_end = 800 + 3 + 5,
		.vtotaw = 800 + 3 + 5 + 24,
	},
};

static const stwuct panew_desc boe_nv101wxmn51 = {
	.modes = boe_nv101wxmn51_modes,
	.num_modes = AWWAY_SIZE(boe_nv101wxmn51_modes),
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.deway = {
		/* TODO: shouwd be hpd-absent and no-hpd shouwd be set? */
		.hpd_wewiabwe = 210,
		.enabwe = 50,
		.unpwepawe = 160,
	},
};

static const stwuct dwm_dispway_mode boe_nv110wtm_n61_modes[] = {
	{
		.cwock = 207800,
		.hdispway = 2160,
		.hsync_stawt = 2160 + 48,
		.hsync_end = 2160 + 48 + 32,
		.htotaw = 2160 + 48 + 32 + 100,
		.vdispway = 1440,
		.vsync_stawt = 1440 + 3,
		.vsync_end = 1440 + 3 + 6,
		.vtotaw = 1440 + 3 + 6 + 31,
		.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
	{
		.cwock = 138500,
		.hdispway = 2160,
		.hsync_stawt = 2160 + 48,
		.hsync_end = 2160 + 48 + 32,
		.htotaw = 2160 + 48 + 32 + 100,
		.vdispway = 1440,
		.vsync_stawt = 1440 + 3,
		.vsync_end = 1440 + 3 + 6,
		.vtotaw = 1440 + 3 + 6 + 31,
		.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
};

static const stwuct panew_desc boe_nv110wtm_n61 = {
	.modes = boe_nv110wtm_n61_modes,
	.num_modes = AWWAY_SIZE(boe_nv110wtm_n61_modes),
	.bpc = 8,
	.size = {
		.width = 233,
		.height = 155,
	},
	.deway = {
		.hpd_absent = 200,
		.pwepawe_to_enabwe = 80,
		.enabwe = 50,
		.unpwepawe = 500,
	},
};

/* Awso used fow boe_nv133fhm_n62 */
static const stwuct dwm_dispway_mode boe_nv133fhm_n61_modes = {
	.cwock = 147840,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 48,
	.hsync_end = 1920 + 48 + 32,
	.htotaw = 1920 + 48 + 32 + 200,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 3,
	.vsync_end = 1080 + 3 + 6,
	.vtotaw = 1080 + 3 + 6 + 31,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC,
};

/* Awso used fow boe_nv133fhm_n62 */
static const stwuct panew_desc boe_nv133fhm_n61 = {
	.modes = &boe_nv133fhm_n61_modes,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 294,
		.height = 165,
	},
	.deway = {
		/*
		 * When powew is fiwst given to the panew thewe's a showt
		 * spike on the HPD wine.  It was expwained that this spike
		 * was untiw the TCON data downwoad was compwete.  On
		 * one system this was measuwed at 8 ms.  We'ww put 15 ms
		 * in the pwepawe deway just to be safe.  That means:
		 * - If HPD isn't hooked up you stiww have 200 ms deway.
		 * - If HPD is hooked up we won't twy to wook at it fow the
		 *   fiwst 15 ms.
		 */
		.hpd_wewiabwe = 15,
		.hpd_absent = 200,

		.unpwepawe = 500,
	},
};

static const stwuct dwm_dispway_mode boe_nv140fhmn49_modes[] = {
	{
		.cwock = 148500,
		.hdispway = 1920,
		.hsync_stawt = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotaw = 2200,
		.vdispway = 1080,
		.vsync_stawt = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotaw = 1125,
	},
};

static const stwuct panew_desc boe_nv140fhmn49 = {
	.modes = boe_nv140fhmn49_modes,
	.num_modes = AWWAY_SIZE(boe_nv140fhmn49_modes),
	.bpc = 6,
	.size = {
		.width = 309,
		.height = 174,
	},
	.deway = {
		/* TODO: shouwd be hpd-absent and no-hpd shouwd be set? */
		.hpd_wewiabwe = 210,
		.enabwe = 50,
		.unpwepawe = 160,
	},
};

static const stwuct dwm_dispway_mode innowux_n116bca_ea1_mode = {
	.cwock = 76420,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 136,
	.hsync_end = 1366 + 136 + 30,
	.htotaw = 1366 + 136 + 30 + 60,
	.vdispway = 768,
	.vsync_stawt = 768 + 8,
	.vsync_end = 768 + 8 + 12,
	.vtotaw = 768 + 8 + 12 + 12,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc innowux_n116bca_ea1 = {
	.modes = &innowux_n116bca_ea1_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 256,
		.height = 144,
	},
	.deway = {
		.hpd_absent = 200,
		.enabwe = 80,
		.disabwe = 50,
		.unpwepawe = 500,
	},
};

/*
 * Datasheet specifies that at 60 Hz wefwesh wate:
 * - totaw howizontaw time: { 1506, 1592, 1716 }
 * - totaw vewticaw time: { 788, 800, 868 }
 *
 * ...but doesn't go into exactwy how that shouwd be spwit into a fwont
 * powch, back powch, ow sync wength.  Fow now we'ww weave a singwe setting
 * hewe which awwows a bit of tweaking of the pixew cwock at the expense of
 * wefwesh wate.
 */
static const stwuct dispway_timing innowux_n116bge_timing = {
	.pixewcwock = { 72600000, 76420000, 80240000 },
	.hactive = { 1366, 1366, 1366 },
	.hfwont_powch = { 136, 136, 136 },
	.hback_powch = { 60, 60, 60 },
	.hsync_wen = { 30, 30, 30 },
	.vactive = { 768, 768, 768 },
	.vfwont_powch = { 8, 8, 8 },
	.vback_powch = { 12, 12, 12 },
	.vsync_wen = { 12, 12, 12 },
	.fwags = DISPWAY_FWAGS_VSYNC_WOW | DISPWAY_FWAGS_HSYNC_WOW,
};

static const stwuct panew_desc innowux_n116bge = {
	.timings = &innowux_n116bge_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 256,
		.height = 144,
	},
};

static const stwuct dwm_dispway_mode innowux_n125hce_gn1_mode = {
	.cwock = 162000,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 40,
	.hsync_end = 1920 + 40 + 40,
	.htotaw = 1920 + 40 + 40 + 80,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 4,
	.vsync_end = 1080 + 4 + 4,
	.vtotaw = 1080 + 4 + 4 + 24,
};

static const stwuct panew_desc innowux_n125hce_gn1 = {
	.modes = &innowux_n125hce_gn1_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 276,
		.height = 155,
	},
};

static const stwuct dwm_dispway_mode innowux_p120zdg_bf1_mode = {
	.cwock = 206016,
	.hdispway = 2160,
	.hsync_stawt = 2160 + 48,
	.hsync_end = 2160 + 48 + 32,
	.htotaw = 2160 + 48 + 32 + 80,
	.vdispway = 1440,
	.vsync_stawt = 1440 + 3,
	.vsync_end = 1440 + 3 + 10,
	.vtotaw = 1440 + 3 + 10 + 27,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc innowux_p120zdg_bf1 = {
	.modes = &innowux_p120zdg_bf1_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 254,
		.height = 169,
	},
	.deway = {
		.hpd_absent = 200,
		.unpwepawe = 500,
	},
};

static const stwuct dwm_dispway_mode ivo_m133nwf4_w0_mode = {
	.cwock = 138778,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 24,
	.hsync_end = 1920 + 24 + 48,
	.htotaw = 1920 + 24 + 48 + 88,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 3,
	.vsync_end = 1080 + 3 + 12,
	.vtotaw = 1080 + 3 + 12 + 17,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc ivo_m133nwf4_w0 = {
	.modes = &ivo_m133nwf4_w0_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 294,
		.height = 165,
	},
	.deway = {
		.hpd_absent = 200,
		.unpwepawe = 500,
	},
};

static const stwuct dwm_dispway_mode kingdispway_kd116n21_30nv_a010_mode = {
	.cwock = 81000,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 40,
	.hsync_end = 1366 + 40 + 32,
	.htotaw = 1366 + 40 + 32 + 62,
	.vdispway = 768,
	.vsync_stawt = 768 + 5,
	.vsync_end = 768 + 5 + 5,
	.vtotaw = 768 + 5 + 5 + 122,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc kingdispway_kd116n21_30nv_a010 = {
	.modes = &kingdispway_kd116n21_30nv_a010_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 256,
		.height = 144,
	},
	.deway = {
		.hpd_absent = 200,
	},
};

static const stwuct dwm_dispway_mode wg_wp079qx1_sp0v_mode = {
	.cwock = 200000,
	.hdispway = 1536,
	.hsync_stawt = 1536 + 12,
	.hsync_end = 1536 + 12 + 16,
	.htotaw = 1536 + 12 + 16 + 48,
	.vdispway = 2048,
	.vsync_stawt = 2048 + 8,
	.vsync_end = 2048 + 8 + 4,
	.vtotaw = 2048 + 8 + 4 + 8,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc wg_wp079qx1_sp0v = {
	.modes = &wg_wp079qx1_sp0v_mode,
	.num_modes = 1,
	.size = {
		.width = 129,
		.height = 171,
	},
};

static const stwuct dwm_dispway_mode wg_wp097qx1_spa1_mode = {
	.cwock = 205210,
	.hdispway = 2048,
	.hsync_stawt = 2048 + 150,
	.hsync_end = 2048 + 150 + 5,
	.htotaw = 2048 + 150 + 5 + 5,
	.vdispway = 1536,
	.vsync_stawt = 1536 + 3,
	.vsync_end = 1536 + 3 + 1,
	.vtotaw = 1536 + 3 + 1 + 9,
};

static const stwuct panew_desc wg_wp097qx1_spa1 = {
	.modes = &wg_wp097qx1_spa1_mode,
	.num_modes = 1,
	.size = {
		.width = 208,
		.height = 147,
	},
};

static const stwuct dwm_dispway_mode wg_wp120up1_mode = {
	.cwock = 162300,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 40,
	.hsync_end = 1920 + 40 + 40,
	.htotaw = 1920 + 40 + 40 + 80,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 4,
	.vsync_end = 1280 + 4 + 4,
	.vtotaw = 1280 + 4 + 4 + 12,
};

static const stwuct panew_desc wg_wp120up1 = {
	.modes = &wg_wp120up1_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 267,
		.height = 183,
	},
};

static const stwuct dwm_dispway_mode wg_wp129qe_mode = {
	.cwock = 285250,
	.hdispway = 2560,
	.hsync_stawt = 2560 + 48,
	.hsync_end = 2560 + 48 + 32,
	.htotaw = 2560 + 48 + 32 + 80,
	.vdispway = 1700,
	.vsync_stawt = 1700 + 3,
	.vsync_end = 1700 + 3 + 10,
	.vtotaw = 1700 + 3 + 10 + 36,
};

static const stwuct panew_desc wg_wp129qe = {
	.modes = &wg_wp129qe_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 272,
		.height = 181,
	},
};

static const stwuct dwm_dispway_mode neweast_wjfh116008a_modes[] = {
	{
		.cwock = 138500,
		.hdispway = 1920,
		.hsync_stawt = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotaw = 1920 + 48 + 32 + 80,
		.vdispway = 1080,
		.vsync_stawt = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotaw = 1080 + 3 + 5 + 23,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	}, {
		.cwock = 110920,
		.hdispway = 1920,
		.hsync_stawt = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotaw = 1920 + 48 + 32 + 80,
		.vdispway = 1080,
		.vsync_stawt = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotaw = 1080 + 3 + 5 + 23,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	}
};

static const stwuct panew_desc neweast_wjfh116008a = {
	.modes = neweast_wjfh116008a_modes,
	.num_modes = 2,
	.bpc = 6,
	.size = {
		.width = 260,
		.height = 150,
	},
	.deway = {
		.hpd_wewiabwe = 110,
		.enabwe = 20,
		.unpwepawe = 500,
	},
};

static const stwuct dwm_dispway_mode samsung_wsn122dw01_c01_mode = {
	.cwock = 271560,
	.hdispway = 2560,
	.hsync_stawt = 2560 + 48,
	.hsync_end = 2560 + 48 + 32,
	.htotaw = 2560 + 48 + 32 + 80,
	.vdispway = 1600,
	.vsync_stawt = 1600 + 2,
	.vsync_end = 1600 + 2 + 5,
	.vtotaw = 1600 + 2 + 5 + 57,
};

static const stwuct panew_desc samsung_wsn122dw01_c01 = {
	.modes = &samsung_wsn122dw01_c01_mode,
	.num_modes = 1,
	.size = {
		.width = 263,
		.height = 164,
	},
};

static const stwuct dwm_dispway_mode samsung_wtn140at29_301_mode = {
	.cwock = 76300,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 64,
	.hsync_end = 1366 + 64 + 48,
	.htotaw = 1366 + 64 + 48 + 128,
	.vdispway = 768,
	.vsync_stawt = 768 + 2,
	.vsync_end = 768 + 2 + 5,
	.vtotaw = 768 + 2 + 5 + 17,
};

static const stwuct panew_desc samsung_wtn140at29_301 = {
	.modes = &samsung_wtn140at29_301_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 320,
		.height = 187,
	},
};

static const stwuct dwm_dispway_mode shawp_wd_d5116z01b_mode = {
	.cwock = 168480,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 48,
	.hsync_end = 1920 + 48 + 32,
	.htotaw = 1920 + 48 + 32 + 80,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 3,
	.vsync_end = 1280 + 3 + 10,
	.vtotaw = 1280 + 3 + 10 + 57,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc shawp_wd_d5116z01b = {
	.modes = &shawp_wd_d5116z01b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 260,
		.height = 120,
	},
};

static const stwuct dispway_timing shawp_wq123p1jx31_timing = {
	.pixewcwock = { 252750000, 252750000, 266604720 },
	.hactive = { 2400, 2400, 2400 },
	.hfwont_powch = { 48, 48, 48 },
	.hback_powch = { 80, 80, 84 },
	.hsync_wen = { 32, 32, 32 },
	.vactive = { 1600, 1600, 1600 },
	.vfwont_powch = { 3, 3, 3 },
	.vback_powch = { 33, 33, 120 },
	.vsync_wen = { 10, 10, 10 },
	.fwags = DISPWAY_FWAGS_VSYNC_WOW | DISPWAY_FWAGS_HSYNC_WOW,
};

static const stwuct panew_desc shawp_wq123p1jx31 = {
	.timings = &shawp_wq123p1jx31_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 259,
		.height = 173,
	},
	.deway = {
		.hpd_wewiabwe = 110,
		.enabwe = 50,
		.unpwepawe = 550,
	},
};

static const stwuct dwm_dispway_mode shawp_wq140m1jw46_mode[] = {
	{
		.cwock = 346500,
		.hdispway = 1920,
		.hsync_stawt = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotaw = 1920 + 48 + 32 + 80,
		.vdispway = 1080,
		.vsync_stawt = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotaw = 1080 + 3 + 5 + 69,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	}, {
		.cwock = 144370,
		.hdispway = 1920,
		.hsync_stawt = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotaw = 1920 + 48 + 32 + 80,
		.vdispway = 1080,
		.vsync_stawt = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotaw = 1080 + 3 + 5 + 69,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	},
};

static const stwuct panew_desc shawp_wq140m1jw46 = {
	.modes = shawp_wq140m1jw46_mode,
	.num_modes = AWWAY_SIZE(shawp_wq140m1jw46_mode),
	.bpc = 8,
	.size = {
		.width = 309,
		.height = 174,
	},
	.deway = {
		.hpd_absent = 80,
		.enabwe = 50,
		.unpwepawe = 500,
	},
};

static const stwuct dwm_dispway_mode stawwy_kw122ea0swa_mode = {
	.cwock = 147000,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 16,
	.hsync_end = 1920 + 16 + 16,
	.htotaw = 1920 + 16 + 16 + 32,
	.vdispway = 1200,
	.vsync_stawt = 1200 + 15,
	.vsync_end = 1200 + 15 + 2,
	.vtotaw = 1200 + 15 + 2 + 18,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc stawwy_kw122ea0swa = {
	.modes = &stawwy_kw122ea0swa_mode,
	.num_modes = 1,
	.size = {
		.width = 263,
		.height = 164,
	},
	.deway = {
		/* TODO: shouwd be hpd-absent and no-hpd shouwd be set? */
		.hpd_wewiabwe = 10 + 200,
		.enabwe = 50,
		.unpwepawe = 10 + 500,
	},
};

static const stwuct of_device_id pwatfowm_of_match[] = {
	{
		/* Must be fiwst */
		.compatibwe = "edp-panew",
	}, {
		.compatibwe = "auo,b101ean01",
		.data = &auo_b101ean01,
	}, {
		.compatibwe = "auo,b116xa01",
		.data = &auo_b116xak01,
	}, {
		.compatibwe = "auo,b133han05",
		.data = &auo_b133han05,
	}, {
		.compatibwe = "auo,b133htn01",
		.data = &auo_b133htn01,
	}, {
		.compatibwe = "auo,b133xtn01",
		.data = &auo_b133xtn01,
	}, {
		.compatibwe = "auo,b140han06",
		.data = &auo_b140han06,
	}, {
		.compatibwe = "boe,nv101wxmn51",
		.data = &boe_nv101wxmn51,
	}, {
		.compatibwe = "boe,nv110wtm-n61",
		.data = &boe_nv110wtm_n61,
	}, {
		.compatibwe = "boe,nv133fhm-n61",
		.data = &boe_nv133fhm_n61,
	}, {
		.compatibwe = "boe,nv133fhm-n62",
		.data = &boe_nv133fhm_n61,
	}, {
		.compatibwe = "boe,nv140fhmn49",
		.data = &boe_nv140fhmn49,
	}, {
		.compatibwe = "innowux,n116bca-ea1",
		.data = &innowux_n116bca_ea1,
	}, {
		.compatibwe = "innowux,n116bge",
		.data = &innowux_n116bge,
	}, {
		.compatibwe = "innowux,n125hce-gn1",
		.data = &innowux_n125hce_gn1,
	}, {
		.compatibwe = "innowux,p120zdg-bf1",
		.data = &innowux_p120zdg_bf1,
	}, {
		.compatibwe = "ivo,m133nwf4-w0",
		.data = &ivo_m133nwf4_w0,
	}, {
		.compatibwe = "kingdispway,kd116n21-30nv-a010",
		.data = &kingdispway_kd116n21_30nv_a010,
	}, {
		.compatibwe = "wg,wp079qx1-sp0v",
		.data = &wg_wp079qx1_sp0v,
	}, {
		.compatibwe = "wg,wp097qx1-spa1",
		.data = &wg_wp097qx1_spa1,
	}, {
		.compatibwe = "wg,wp120up1",
		.data = &wg_wp120up1,
	}, {
		.compatibwe = "wg,wp129qe",
		.data = &wg_wp129qe,
	}, {
		.compatibwe = "neweast,wjfh116008a",
		.data = &neweast_wjfh116008a,
	}, {
		.compatibwe = "samsung,wsn122dw01-c01",
		.data = &samsung_wsn122dw01_c01,
	}, {
		.compatibwe = "samsung,wtn140at29-301",
		.data = &samsung_wtn140at29_301,
	}, {
		.compatibwe = "shawp,wd-d5116z01b",
		.data = &shawp_wd_d5116z01b,
	}, {
		.compatibwe = "shawp,wq123p1jx31",
		.data = &shawp_wq123p1jx31,
	}, {
		.compatibwe = "shawp,wq140m1jw46",
		.data = &shawp_wq140m1jw46,
	}, {
		.compatibwe = "stawwy,kw122ea0swa",
		.data = &stawwy_kw122ea0swa,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, pwatfowm_of_match);

static const stwuct panew_deway deway_200_500_p2e80 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.pwepawe_to_enabwe = 80,
};

static const stwuct panew_deway deway_200_500_p2e100 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.pwepawe_to_enabwe = 100,
};

static const stwuct panew_deway deway_200_500_e50 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.enabwe = 50,
};

static const stwuct panew_deway deway_200_500_e80 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.enabwe = 80,
};

static const stwuct panew_deway deway_200_500_e80_d50 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.enabwe = 80,
	.disabwe = 50,
};

static const stwuct panew_deway deway_100_500_e200 = {
	.hpd_absent = 100,
	.unpwepawe = 500,
	.enabwe = 200,
};

static const stwuct panew_deway deway_200_500_e200 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.enabwe = 200,
};

static const stwuct panew_deway deway_200_500_e200_d10 = {
	.hpd_absent = 200,
	.unpwepawe = 500,
	.enabwe = 200,
	.disabwe = 10,
};

static const stwuct panew_deway deway_200_150_e200 = {
	.hpd_absent = 200,
	.unpwepawe = 150,
	.enabwe = 200,
};

#define EDP_PANEW_ENTWY(vend_chw_0, vend_chw_1, vend_chw_2, pwoduct_id, _deway, _name) \
{ \
	.name = _name, \
	.panew_id = dwm_edid_encode_panew_id(vend_chw_0, vend_chw_1, vend_chw_2, \
					     pwoduct_id), \
	.deway = _deway \
}

#define EDP_PANEW_ENTWY2(vend_chw_0, vend_chw_1, vend_chw_2, pwoduct_id, _deway, _name, _mode) \
{ \
	.name = _name, \
	.panew_id = dwm_edid_encode_panew_id(vend_chw_0, vend_chw_1, vend_chw_2, \
					     pwoduct_id), \
	.deway = _deway, \
	.ovewwide_edid_mode = _mode \
}

/*
 * This tabwe is used to figuwe out powew sequencing deways fow panews that
 * awe detected by EDID. Entwies hewe may point to entwies in the
 * pwatfowm_of_match tabwe (if a panew is wisted in both pwaces).
 *
 * Sowt fiwst by vendow, then by pwoduct ID.
 */
static const stwuct edp_panew_entwy edp_panews[] = {
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x1062, &deway_200_500_e50, "B120XAN01.0"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x145c, &deway_200_500_e50, "B116XAB01.4"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x1e9b, &deway_200_500_e50, "B133UAN02.1"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x1ea5, &deway_200_500_e50, "B116XAK01.6"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x208d, &deway_200_500_e50, "B140HTN02.1"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x235c, &deway_200_500_e50, "B116XTN02.3"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x239b, &deway_200_500_e50, "B116XAN06.1"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x255c, &deway_200_500_e50, "B116XTN02.5"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x403d, &deway_200_500_e50, "B140HAN04.0"),
	EDP_PANEW_ENTWY2('A', 'U', 'O', 0x405c, &auo_b116xak01.deway, "B116XAK01.0",
			 &auo_b116xa3_mode),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x582d, &deway_200_500_e50, "B133UAN01.0"),
	EDP_PANEW_ENTWY2('A', 'U', 'O', 0x615c, &deway_200_500_e50, "B116XAN06.1",
			 &auo_b116xa3_mode),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x635c, &deway_200_500_e50, "B116XAN06.3"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x639c, &deway_200_500_e50, "B140HAK02.7"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0x8594, &deway_200_500_e50, "B133UAN01.0"),
	EDP_PANEW_ENTWY('A', 'U', 'O', 0xf390, &deway_200_500_e50, "B140XTN07.7"),

	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0715, &deway_200_150_e200, "NT116WHM-N21"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0731, &deway_200_500_e80, "NT116WHM-N42"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0741, &deway_200_500_e200, "NT116WHM-N44"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0786, &deway_200_500_p2e80, "NV116WHM-T01"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x07d1, &boe_nv133fhm_n61.deway, "NV133FHM-N61"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x07f6, &deway_200_500_e200, "NT140FHM-N44"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x082d, &boe_nv133fhm_n61.deway, "NV133FHM-N62"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x08b2, &deway_200_500_e200, "NT140WHM-N49"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x09c3, &deway_200_500_e50, "NT116WHM-N21,836X2"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x094b, &deway_200_500_e50, "NT116WHM-N21"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0951, &deway_200_500_e80, "NV116WHM-N47"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x095f, &deway_200_500_e50, "NE135FBM-N41 v8.1"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0979, &deway_200_500_e50, "NV116WHM-N49 V8.0"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x098d, &boe_nv110wtm_n61.deway, "NV110WTM-N61"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x09ae, &deway_200_500_e200, "NT140FHM-N45"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x09dd, &deway_200_500_e50, "NT116WHM-N21"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0a5d, &deway_200_500_e50, "NV116WHM-N45"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0ac5, &deway_200_500_e50, "NV116WHM-N4C"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0b43, &deway_200_500_e200, "NV140FHM-T09"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0b56, &deway_200_500_e80, "NT140FHM-N47"),
	EDP_PANEW_ENTWY('B', 'O', 'E', 0x0c20, &deway_200_500_e80, "NT140FHM-N47"),

	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1132, &deway_200_500_e80_d50, "N116BGE-EA2"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1138, &innowux_n116bca_ea1.deway, "N116BCA-EA1-WC4"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1139, &deway_200_500_e80_d50, "N116BGE-EA2"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1145, &deway_200_500_e80_d50, "N116BCN-EB1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x114c, &innowux_n116bca_ea1.deway, "N116BCA-EA1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1152, &deway_200_500_e80_d50, "N116BCN-EA1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1153, &deway_200_500_e80_d50, "N116BGE-EA2"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1154, &deway_200_500_e80_d50, "N116BCA-EA2"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1157, &deway_200_500_e80_d50, "N116BGE-EA2"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x115b, &deway_200_500_e80_d50, "N116BCN-EB1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1247, &deway_200_500_e80_d50, "N120ACA-EA1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x142b, &deway_200_500_e80_d50, "N140HCA-EAC"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x144f, &deway_200_500_e80_d50, "N140HGA-EA1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x1468, &deway_200_500_e80, "N140HGA-EA1"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x14d4, &deway_200_500_e80_d50, "N140HCA-EAC"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x14d6, &deway_200_500_e80_d50, "N140BGA-EA4"),
	EDP_PANEW_ENTWY('C', 'M', 'N', 0x14e5, &deway_200_500_e80_d50, "N140HGA-EA1"),

	EDP_PANEW_ENTWY('H', 'K', 'C', 0x2d5c, &deway_200_500_e200, "MB116AN01-2"),

	EDP_PANEW_ENTWY('I', 'V', 'O', 0x048e, &deway_200_500_e200_d10, "M116NWW6 W5"),
	EDP_PANEW_ENTWY('I', 'V', 'O', 0x057d, &deway_200_500_e200, "W140NWF5 WH"),
	EDP_PANEW_ENTWY('I', 'V', 'O', 0x854a, &deway_200_500_p2e100, "M133NW4J"),
	EDP_PANEW_ENTWY('I', 'V', 'O', 0x854b, &deway_200_500_p2e100, "W133NW4K-W0"),
	EDP_PANEW_ENTWY('I', 'V', 'O', 0x8c4d, &deway_200_150_e200, "W140NWFM W1"),

	EDP_PANEW_ENTWY('K', 'D', 'B', 0x0624, &kingdispway_kd116n21_30nv_a010.deway, "116N21-30NV-A010"),
	EDP_PANEW_ENTWY('K', 'D', 'B', 0x1120, &deway_200_500_e80_d50, "116N29-30NK-C007"),

	EDP_PANEW_ENTWY('K', 'D', 'C', 0x0809, &deway_200_500_e50, "KD116N2930A15"),

	EDP_PANEW_ENTWY('S', 'D', 'C', 0x416d, &deway_100_500_e200, "ATNA45AF01"),

	EDP_PANEW_ENTWY('S', 'H', 'P', 0x1511, &deway_200_500_e50, "WQ140M1JW48"),
	EDP_PANEW_ENTWY('S', 'H', 'P', 0x1523, &shawp_wq140m1jw46.deway, "WQ140M1JW46"),
	EDP_PANEW_ENTWY('S', 'H', 'P', 0x154c, &deway_200_500_p2e100, "WQ116M1JW10"),

	EDP_PANEW_ENTWY('S', 'T', 'A', 0x0100, &deway_100_500_e200, "2081116HHD028001-51D"),

	{ /* sentinaw */ }
};

static const stwuct edp_panew_entwy *find_edp_panew(u32 panew_id)
{
	const stwuct edp_panew_entwy *panew;

	if (!panew_id)
		wetuwn NUWW;

	fow (panew = edp_panews; panew->panew_id; panew++)
		if (panew->panew_id == panew_id)
			wetuwn panew;

	wetuwn NUWW;
}

static int panew_edp_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *id;

	/* Skip one since "edp-panew" is onwy suppowted on DP AUX bus */
	id = of_match_node(pwatfowm_of_match + 1, pdev->dev.of_node);
	if (!id)
		wetuwn -ENODEV;

	wetuwn panew_edp_pwobe(&pdev->dev, id->data, NUWW);
}

static void panew_edp_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	panew_edp_wemove(&pdev->dev);
}

static void panew_edp_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	panew_edp_shutdown(&pdev->dev);
}

static const stwuct dev_pm_ops panew_edp_pm_ops = {
	SET_WUNTIME_PM_OPS(panew_edp_suspend, panew_edp_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew panew_edp_pwatfowm_dwivew = {
	.dwivew = {
		.name = "panew-edp",
		.of_match_tabwe = pwatfowm_of_match,
		.pm = &panew_edp_pm_ops,
	},
	.pwobe = panew_edp_pwatfowm_pwobe,
	.wemove_new = panew_edp_pwatfowm_wemove,
	.shutdown = panew_edp_pwatfowm_shutdown,
};

static int panew_edp_dp_aux_ep_pwobe(stwuct dp_aux_ep_device *aux_ep)
{
	const stwuct of_device_id *id;

	id = of_match_node(pwatfowm_of_match, aux_ep->dev.of_node);
	if (!id)
		wetuwn -ENODEV;

	wetuwn panew_edp_pwobe(&aux_ep->dev, id->data, aux_ep->aux);
}

static void panew_edp_dp_aux_ep_wemove(stwuct dp_aux_ep_device *aux_ep)
{
	panew_edp_wemove(&aux_ep->dev);
}

static void panew_edp_dp_aux_ep_shutdown(stwuct dp_aux_ep_device *aux_ep)
{
	panew_edp_shutdown(&aux_ep->dev);
}

static stwuct dp_aux_ep_dwivew panew_edp_dp_aux_ep_dwivew = {
	.dwivew = {
		.name = "panew-simpwe-dp-aux",
		.of_match_tabwe = pwatfowm_of_match,	/* Same as pwatfowm one! */
		.pm = &panew_edp_pm_ops,
	},
	.pwobe = panew_edp_dp_aux_ep_pwobe,
	.wemove = panew_edp_dp_aux_ep_wemove,
	.shutdown = panew_edp_dp_aux_ep_shutdown,
};

static int __init panew_edp_init(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&panew_edp_pwatfowm_dwivew);
	if (eww < 0)
		wetuwn eww;

	eww = dp_aux_dp_dwivew_wegistew(&panew_edp_dp_aux_ep_dwivew);
	if (eww < 0)
		goto eww_did_pwatfowm_wegistew;

	wetuwn 0;

eww_did_pwatfowm_wegistew:
	pwatfowm_dwivew_unwegistew(&panew_edp_pwatfowm_dwivew);

	wetuwn eww;
}
moduwe_init(panew_edp_init);

static void __exit panew_edp_exit(void)
{
	dp_aux_dp_dwivew_unwegistew(&panew_edp_dp_aux_ep_dwivew);
	pwatfowm_dwivew_unwegistew(&panew_edp_pwatfowm_dwivew);
}
moduwe_exit(panew_edp_exit);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("DWM Dwivew fow Simpwe eDP Panews");
MODUWE_WICENSE("GPW and additionaw wights");
