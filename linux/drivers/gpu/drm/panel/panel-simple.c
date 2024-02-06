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

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/dispway_timing.h>
#incwude <video/of_dispway_timing.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_of.h>

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
	stwuct {
		/**
		 * @deway.pwepawe: Time fow the panew to become weady.
		 *
		 * The time (in miwwiseconds) that it takes fow the panew to
		 * become weady and stawt weceiving video data
		 */
		unsigned int pwepawe;

		/**
		 * @deway.enabwe: Time fow the panew to dispway a vawid fwame.
		 *
		 * The time (in miwwiseconds) that it takes fow the panew to
		 * dispway the fiwst vawid fwame aftew stawting to weceive
		 * video data.
		 */
		unsigned int enabwe;

		/**
		 * @deway.disabwe: Time fow the panew to tuwn the dispway off.
		 *
		 * The time (in miwwiseconds) that it takes fow the panew to
		 * tuwn the dispway off (no content is visibwe).
		 */
		unsigned int disabwe;

		/**
		 * @deway.unpwepawe: Time to powew down compwetewy.
		 *
		 * The time (in miwwiseconds) that it takes fow the panew
		 * to powew itsewf down compwetewy.
		 *
		 * This time is used to pwevent a futuwe "pwepawe" fwom
		 * stawting untiw at weast this many miwwiseconds has passed.
		 * If at pwepawe time wess time has passed since unpwepawe
		 * finished, the dwivew waits fow the wemaining time.
		 */
		unsigned int unpwepawe;
	} deway;

	/** @bus_fowmat: See MEDIA_BUS_FMT_... defines. */
	u32 bus_fowmat;

	/** @bus_fwags: See DWM_BUS_FWAG_... defines. */
	u32 bus_fwags;

	/** @connectow_type: WVDS, eDP, DSI, DPI, etc. */
	int connectow_type;
};

stwuct panew_simpwe {
	stwuct dwm_panew base;
	boow enabwed;

	boow pwepawed;

	ktime_t unpwepawed_time;

	const stwuct panew_desc *desc;

	stwuct weguwatow *suppwy;
	stwuct i2c_adaptew *ddc;

	stwuct gpio_desc *enabwe_gpio;

	stwuct edid *edid;

	stwuct dwm_dispway_mode ovewwide_mode;

	enum dwm_panew_owientation owientation;
};

static inwine stwuct panew_simpwe *to_panew_simpwe(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct panew_simpwe, base);
}

static unsigned int panew_simpwe_get_timings_modes(stwuct panew_simpwe *panew,
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

static unsigned int panew_simpwe_get_dispway_modes(stwuct panew_simpwe *panew,
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

static int panew_simpwe_get_non_edid_modes(stwuct panew_simpwe *panew,
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
		num = panew_simpwe_get_timings_modes(panew, connectow);

	/*
	 * Onwy add fixed modes if timings/ovewwide added no mode.
	 *
	 * We shouwd onwy evew have eithew the dispway timings specified
	 * ow a fixed mode. Anything ewse is wathew bogus.
	 */
	WAWN_ON(panew->desc->num_timings && panew->desc->num_modes);
	if (num == 0)
		num = panew_simpwe_get_dispway_modes(panew, connectow);

	connectow->dispway_info.bpc = panew->desc->bpc;
	connectow->dispway_info.width_mm = panew->desc->size.width;
	connectow->dispway_info.height_mm = panew->desc->size.height;
	if (panew->desc->bus_fowmat)
		dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
						 &panew->desc->bus_fowmat, 1);
	connectow->dispway_info.bus_fwags = panew->desc->bus_fwags;

	wetuwn num;
}

static void panew_simpwe_wait(ktime_t stawt_ktime, unsigned int min_ms)
{
	ktime_t now_ktime, min_ktime;

	if (!min_ms)
		wetuwn;

	min_ktime = ktime_add(stawt_ktime, ms_to_ktime(min_ms));
	now_ktime = ktime_get_boottime();

	if (ktime_befowe(now_ktime, min_ktime))
		msweep(ktime_to_ms(ktime_sub(min_ktime, now_ktime)) + 1);
}

static int panew_simpwe_disabwe(stwuct dwm_panew *panew)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);

	if (!p->enabwed)
		wetuwn 0;

	if (p->desc->deway.disabwe)
		msweep(p->desc->deway.disabwe);

	p->enabwed = fawse;

	wetuwn 0;
}

static int panew_simpwe_suspend(stwuct device *dev)
{
	stwuct panew_simpwe *p = dev_get_dwvdata(dev);

	gpiod_set_vawue_cansweep(p->enabwe_gpio, 0);
	weguwatow_disabwe(p->suppwy);
	p->unpwepawed_time = ktime_get_boottime();

	kfwee(p->edid);
	p->edid = NUWW;

	wetuwn 0;
}

static int panew_simpwe_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);
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

static int panew_simpwe_wesume(stwuct device *dev)
{
	stwuct panew_simpwe *p = dev_get_dwvdata(dev);
	int eww;

	panew_simpwe_wait(p->unpwepawed_time, p->desc->deway.unpwepawe);

	eww = weguwatow_enabwe(p->suppwy);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe suppwy: %d\n", eww);
		wetuwn eww;
	}

	gpiod_set_vawue_cansweep(p->enabwe_gpio, 1);

	if (p->desc->deway.pwepawe)
		msweep(p->desc->deway.pwepawe);

	wetuwn 0;
}

static int panew_simpwe_pwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);
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

static int panew_simpwe_enabwe(stwuct dwm_panew *panew)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);

	if (p->enabwed)
		wetuwn 0;

	if (p->desc->deway.enabwe)
		msweep(p->desc->deway.enabwe);

	p->enabwed = twue;

	wetuwn 0;
}

static int panew_simpwe_get_modes(stwuct dwm_panew *panew,
				  stwuct dwm_connectow *connectow)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);
	int num = 0;

	/* pwobe EDID if a DDC bus is avaiwabwe */
	if (p->ddc) {
		pm_wuntime_get_sync(panew->dev);

		if (!p->edid)
			p->edid = dwm_get_edid(connectow, p->ddc);

		if (p->edid)
			num += dwm_add_edid_modes(connectow, p->edid);

		pm_wuntime_mawk_wast_busy(panew->dev);
		pm_wuntime_put_autosuspend(panew->dev);
	}

	/* add hawd-coded panew modes */
	num += panew_simpwe_get_non_edid_modes(p, connectow);

	/*
	 * TODO: Wemove once aww dwm dwivews caww
	 * dwm_connectow_set_owientation_fwom_panew()
	 */
	dwm_connectow_set_panew_owientation(connectow, p->owientation);

	wetuwn num;
}

static int panew_simpwe_get_timings(stwuct dwm_panew *panew,
				    unsigned int num_timings,
				    stwuct dispway_timing *timings)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);
	unsigned int i;

	if (p->desc->num_timings < num_timings)
		num_timings = p->desc->num_timings;

	if (timings)
		fow (i = 0; i < num_timings; i++)
			timings[i] = p->desc->timings[i];

	wetuwn p->desc->num_timings;
}

static enum dwm_panew_owientation panew_simpwe_get_owientation(stwuct dwm_panew *panew)
{
	stwuct panew_simpwe *p = to_panew_simpwe(panew);

	wetuwn p->owientation;
}

static const stwuct dwm_panew_funcs panew_simpwe_funcs = {
	.disabwe = panew_simpwe_disabwe,
	.unpwepawe = panew_simpwe_unpwepawe,
	.pwepawe = panew_simpwe_pwepawe,
	.enabwe = panew_simpwe_enabwe,
	.get_modes = panew_simpwe_get_modes,
	.get_owientation = panew_simpwe_get_owientation,
	.get_timings = panew_simpwe_get_timings,
};

static stwuct panew_desc panew_dpi;

static int panew_dpi_pwobe(stwuct device *dev,
			   stwuct panew_simpwe *panew)
{
	stwuct dispway_timing *timing;
	const stwuct device_node *np;
	stwuct panew_desc *desc;
	unsigned int bus_fwags;
	stwuct videomode vm;
	int wet;

	np = dev->of_node;
	desc = devm_kzawwoc(dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	timing = devm_kzawwoc(dev, sizeof(*timing), GFP_KEWNEW);
	if (!timing)
		wetuwn -ENOMEM;

	wet = of_get_dispway_timing(np, "panew-timing", timing);
	if (wet < 0) {
		dev_eww(dev, "%pOF: no panew-timing node found fow \"panew-dpi\" binding\n",
			np);
		wetuwn wet;
	}

	desc->timings = timing;
	desc->num_timings = 1;

	of_pwopewty_wead_u32(np, "width-mm", &desc->size.width);
	of_pwopewty_wead_u32(np, "height-mm", &desc->size.height);

	/* Extwact bus_fwags fwom dispway_timing */
	bus_fwags = 0;
	vm.fwags = timing->fwags;
	dwm_bus_fwags_fwom_videomode(&vm, &bus_fwags);
	desc->bus_fwags = bus_fwags;

	/* We do not know the connectow fow the DT node, so guess it */
	desc->connectow_type = DWM_MODE_CONNECTOW_DPI;

	panew->desc = desc;

	wetuwn 0;
}

#define PANEW_SIMPWE_BOUNDS_CHECK(to_check, bounds, fiewd) \
	(to_check->fiewd.typ >= bounds->fiewd.min && \
	 to_check->fiewd.typ <= bounds->fiewd.max)
static void panew_simpwe_pawse_panew_timing_node(stwuct device *dev,
						 stwuct panew_simpwe *panew,
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

		if (!PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, hactive) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, hfwont_powch) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, hback_powch) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, hsync_wen) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, vactive) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, vfwont_powch) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, vback_powch) ||
		    !PANEW_SIMPWE_BOUNDS_CHECK(ot, dt, vsync_wen))
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

static int panew_simpwe_ovewwide_nondefauwt_wvds_datamapping(stwuct device *dev,
							     stwuct panew_simpwe *panew)
{
	int wet, bpc;

	wet = dwm_of_wvds_get_data_mapping(dev->of_node);
	if (wet < 0) {
		if (wet == -EINVAW)
			dev_wawn(dev, "Ignowe invawid data-mapping pwopewty\n");

		/*
		 * Ignowe non-existing ow mawfowmatted pwopewty, fawwback to
		 * defauwt data-mapping, and wetuwn 0.
		 */
		wetuwn 0;
	}

	switch (wet) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		fawwthwough;
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		bpc = 8;
		bweak;
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		bpc = 6;
	}

	if (panew->desc->bpc != bpc || panew->desc->bus_fowmat != wet) {
		stwuct panew_desc *ovewwide_desc;

		ovewwide_desc = devm_kmemdup(dev, panew->desc, sizeof(*panew->desc), GFP_KEWNEW);
		if (!ovewwide_desc)
			wetuwn -ENOMEM;

		ovewwide_desc->bus_fowmat = wet;
		ovewwide_desc->bpc = bpc;
		panew->desc = ovewwide_desc;
	}

	wetuwn 0;
}

static int panew_simpwe_pwobe(stwuct device *dev, const stwuct panew_desc *desc)
{
	stwuct panew_simpwe *panew;
	stwuct dispway_timing dt;
	stwuct device_node *ddc;
	int connectow_type;
	u32 bus_fwags;
	int eww;

	panew = devm_kzawwoc(dev, sizeof(*panew), GFP_KEWNEW);
	if (!panew)
		wetuwn -ENOMEM;

	panew->enabwed = fawse;
	panew->desc = desc;

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
	}

	if (desc == &panew_dpi) {
		/* Handwe the genewic panew-dpi binding */
		eww = panew_dpi_pwobe(dev, panew);
		if (eww)
			goto fwee_ddc;
		desc = panew->desc;
	} ewse {
		if (!of_get_dispway_timing(dev->of_node, "panew-timing", &dt))
			panew_simpwe_pawse_panew_timing_node(dev, panew, &dt);
	}

	if (desc->connectow_type == DWM_MODE_CONNECTOW_WVDS) {
		/* Optionaw data-mapping pwopewty fow ovewwiding bus fowmat */
		eww = panew_simpwe_ovewwide_nondefauwt_wvds_datamapping(dev, panew);
		if (eww)
			goto fwee_ddc;
	}

	connectow_type = desc->connectow_type;
	/* Catch common mistakes fow panews. */
	switch (connectow_type) {
	case 0:
		dev_wawn(dev, "Specify missing connectow_type\n");
		connectow_type = DWM_MODE_CONNECTOW_DPI;
		bweak;
	case DWM_MODE_CONNECTOW_WVDS:
		WAWN_ON(desc->bus_fwags &
			~(DWM_BUS_FWAG_DE_WOW |
			  DWM_BUS_FWAG_DE_HIGH |
			  DWM_BUS_FWAG_DATA_MSB_TO_WSB |
			  DWM_BUS_FWAG_DATA_WSB_TO_MSB));
		WAWN_ON(desc->bus_fowmat != MEDIA_BUS_FMT_WGB666_1X7X3_SPWG &&
			desc->bus_fowmat != MEDIA_BUS_FMT_WGB888_1X7X4_SPWG &&
			desc->bus_fowmat != MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA);
		WAWN_ON(desc->bus_fowmat == MEDIA_BUS_FMT_WGB666_1X7X3_SPWG &&
			desc->bpc != 6);
		WAWN_ON((desc->bus_fowmat == MEDIA_BUS_FMT_WGB888_1X7X4_SPWG ||
			 desc->bus_fowmat == MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA) &&
			desc->bpc != 8);
		bweak;
	case DWM_MODE_CONNECTOW_eDP:
		dev_wawn(dev, "eDP panews moved to panew-edp\n");
		eww = -EINVAW;
		goto fwee_ddc;
	case DWM_MODE_CONNECTOW_DSI:
		if (desc->bpc != 6 && desc->bpc != 8)
			dev_wawn(dev, "Expected bpc in {6,8} but got: %u\n", desc->bpc);
		bweak;
	case DWM_MODE_CONNECTOW_DPI:
		bus_fwags = DWM_BUS_FWAG_DE_WOW |
			    DWM_BUS_FWAG_DE_HIGH |
			    DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE |
			    DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
			    DWM_BUS_FWAG_DATA_MSB_TO_WSB |
			    DWM_BUS_FWAG_DATA_WSB_TO_MSB |
			    DWM_BUS_FWAG_SYNC_SAMPWE_POSEDGE |
			    DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE;
		if (desc->bus_fwags & ~bus_fwags)
			dev_wawn(dev, "Unexpected bus_fwags(%d)\n", desc->bus_fwags & ~bus_fwags);
		if (!(desc->bus_fwags & bus_fwags))
			dev_wawn(dev, "Specify missing bus_fwags\n");
		if (desc->bus_fowmat == 0)
			dev_wawn(dev, "Specify missing bus_fowmat\n");
		if (desc->bpc != 6 && desc->bpc != 8)
			dev_wawn(dev, "Expected bpc in {6,8} but got: %u\n", desc->bpc);
		bweak;
	defauwt:
		dev_wawn(dev, "Specify a vawid connectow_type: %d\n", desc->connectow_type);
		connectow_type = DWM_MODE_CONNECTOW_DPI;
		bweak;
	}

	dev_set_dwvdata(dev, panew);

	/*
	 * We use wuntime PM fow pwepawe / unpwepawe since those powew the panew
	 * on and off and those can be vewy swow opewations. This is impowtant
	 * to optimize powewing the panew on bwiefwy to wead the EDID befowe
	 * fuwwy enabwing the panew.
	 */
	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_use_autosuspend(dev);

	dwm_panew_init(&panew->base, dev, &panew_simpwe_funcs, connectow_type);

	eww = dwm_panew_of_backwight(&panew->base);
	if (eww) {
		dev_eww_pwobe(dev, eww, "Couwd not find backwight\n");
		goto disabwe_pm_wuntime;
	}

	dwm_panew_add(&panew->base);

	wetuwn 0;

disabwe_pm_wuntime:
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);
fwee_ddc:
	if (panew->ddc)
		put_device(&panew->ddc->dev);

	wetuwn eww;
}

static void panew_simpwe_wemove(stwuct device *dev)
{
	stwuct panew_simpwe *panew = dev_get_dwvdata(dev);

	dwm_panew_wemove(&panew->base);
	dwm_panew_disabwe(&panew->base);
	dwm_panew_unpwepawe(&panew->base);

	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);
	if (panew->ddc)
		put_device(&panew->ddc->dev);
}

static void panew_simpwe_shutdown(stwuct device *dev)
{
	stwuct panew_simpwe *panew = dev_get_dwvdata(dev);

	dwm_panew_disabwe(&panew->base);
	dwm_panew_unpwepawe(&panew->base);
}

static const stwuct dwm_dispway_mode ampiwe_am_1280800n3tzqw_t00h_mode = {
	.cwock = 71100,
	.hdispway = 1280,
	.hsync_stawt = 1280 + 40,
	.hsync_end = 1280 + 40 + 80,
	.htotaw = 1280 + 40 + 80 + 40,
	.vdispway = 800,
	.vsync_stawt = 800 + 3,
	.vsync_end = 800 + 3 + 10,
	.vtotaw = 800 + 3 + 10 + 10,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc ampiwe_am_1280800n3tzqw_t00h = {
	.modes = &ampiwe_am_1280800n3tzqw_t00h_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode ampiwe_am_480272h3tmqw_t01h_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotaw = 480 + 2 + 41 + 2,
	.vdispway = 272,
	.vsync_stawt = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotaw = 272 + 2 + 10 + 2,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc ampiwe_am_480272h3tmqw_t01h = {
	.modes = &ampiwe_am_480272h3tmqw_t01h_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 99,
		.height = 58,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dwm_dispway_mode ampiwe_am800480w3tmqwa1h_mode = {
	.cwock = 33333,
	.hdispway = 800,
	.hsync_stawt = 800 + 0,
	.hsync_end = 800 + 0 + 255,
	.htotaw = 800 + 0 + 255 + 0,
	.vdispway = 480,
	.vsync_stawt = 480 + 2,
	.vsync_end = 480 + 2 + 45,
	.vtotaw = 480 + 2 + 45 + 0,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct dispway_timing ampiwe_am_800480w1tmqw_t00h_timing = {
	.pixewcwock = { 29930000, 33260000, 36590000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 1, 40, 168 },
	.hback_powch = { 88, 88, 88 },
	.hsync_wen = { 1, 128, 128 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 1, 35, 37 },
	.vback_powch = { 8, 8, 8 },
	.vsync_wen = { 1, 2, 2 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc ampiwe_am_800480w1tmqw_t00h = {
	.timings = &ampiwe_am_800480w1tmqw_t00h_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 111,
		.height = 67,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct panew_desc ampiwe_am800480w3tmqwa1h = {
	.modes = &ampiwe_am800480w3tmqwa1h_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dispway_timing ampiwe_am800600p5tmqw_tb8h_timing = {
	.pixewcwock = { 34500000, 39600000, 50400000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 12, 112, 312 },
	.hback_powch = { 87, 87, 48 },
	.hsync_wen = { 1, 1, 40 },
	.vactive = { 600, 600, 600 },
	.vfwont_powch = { 1, 21, 61 },
	.vback_powch = { 38, 38, 19 },
	.vsync_wen = { 1, 1, 20 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc ampiwe_am800600p5tmqwtb8h = {
	.timings = &ampiwe_am800600p5tmqw_tb8h_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 162,
		.height = 122,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing santek_st0700i5y_wbsww_f_timing = {
	.pixewcwock = { 26400000, 33300000, 46800000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 16, 210, 354 },
	.hback_powch = { 45, 36, 6 },
	.hsync_wen = { 1, 10, 40 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 7, 22, 147 },
	.vback_powch = { 22, 13, 3 },
	.vsync_wen = { 1, 10, 20 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE
};

static const stwuct panew_desc awmadeus_st0700_adapt = {
	.timings = &santek_st0700i5y_wbsww_f_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dwm_dispway_mode auo_b101aw03_mode = {
	.cwock = 51450,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 156,
	.hsync_end = 1024 + 156 + 8,
	.htotaw = 1024 + 156 + 8 + 156,
	.vdispway = 600,
	.vsync_stawt = 600 + 16,
	.vsync_end = 600 + 16 + 6,
	.vtotaw = 600 + 16 + 6 + 16,
};

static const stwuct panew_desc auo_b101aw03 = {
	.modes = &auo_b101aw03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 223,
		.height = 125,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode auo_b101xtn01_mode = {
	.cwock = 72000,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 20,
	.hsync_end = 1366 + 20 + 70,
	.htotaw = 1366 + 20 + 70,
	.vdispway = 768,
	.vsync_stawt = 768 + 14,
	.vsync_end = 768 + 14 + 42,
	.vtotaw = 768 + 14 + 42,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc auo_b101xtn01 = {
	.modes = &auo_b101xtn01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 223,
		.height = 125,
	},
};

static const stwuct dwm_dispway_mode auo_b116xw03_mode = {
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

static const stwuct panew_desc auo_b116xw03 = {
	.modes = &auo_b116xw03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 256,
		.height = 144,
	},
	.deway = {
		.pwepawe = 1,
		.enabwe = 200,
		.disabwe = 200,
		.unpwepawe = 500,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_g070vvn01_timings = {
	.pixewcwock = { 33300000, 34209000, 45000000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 20, 40, 200 },
	.hback_powch = { 87, 40, 1 },
	.hsync_wen = { 1, 48, 87 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 5, 13, 200 },
	.vback_powch = { 31, 31, 29 },
	.vsync_wen = { 1, 1, 3 },
};

static const stwuct panew_desc auo_g070vvn01 = {
	.timings = &auo_g070vvn01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.deway = {
		.pwepawe = 200,
		.enabwe = 50,
		.disabwe = 50,
		.unpwepawe = 1000,
	},
};

static const stwuct dwm_dispway_mode auo_g101evn010_mode = {
	.cwock = 68930,
	.hdispway = 1280,
	.hsync_stawt = 1280 + 82,
	.hsync_end = 1280 + 82 + 2,
	.htotaw = 1280 + 82 + 2 + 84,
	.vdispway = 800,
	.vsync_stawt = 800 + 8,
	.vsync_end = 800 + 8 + 2,
	.vtotaw = 800 + 8 + 2 + 6,
};

static const stwuct panew_desc auo_g101evn010 = {
	.modes = &auo_g101evn010_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 216,
		.height = 135,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode auo_g104sn02_mode = {
	.cwock = 40000,
	.hdispway = 800,
	.hsync_stawt = 800 + 40,
	.hsync_end = 800 + 40 + 216,
	.htotaw = 800 + 40 + 216 + 128,
	.vdispway = 600,
	.vsync_stawt = 600 + 10,
	.vsync_end = 600 + 10 + 35,
	.vtotaw = 600 + 10 + 35 + 2,
};

static const stwuct panew_desc auo_g104sn02 = {
	.modes = &auo_g104sn02_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 211,
		.height = 158,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_g121ean01_timing = {
	.pixewcwock = { 60000000, 74400000, 90000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 20, 50, 100 },
	.hback_powch = { 20, 50, 100 },
	.hsync_wen = { 30, 100, 200 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 2, 10, 25 },
	.vback_powch = { 2, 10, 25 },
	.vsync_wen = { 4, 18, 50 },
};

static const stwuct panew_desc auo_g121ean01 = {
	.timings = &auo_g121ean01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 261,
		.height = 163,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_g133han01_timings = {
	.pixewcwock = { 134000000, 141200000, 149000000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 39, 58, 77 },
	.hback_powch = { 59, 88, 117 },
	.hsync_wen = { 28, 42, 56 },
	.vactive = { 1080, 1080, 1080 },
	.vfwont_powch = { 3, 8, 11 },
	.vback_powch = { 5, 14, 19 },
	.vsync_wen = { 4, 14, 19 },
};

static const stwuct panew_desc auo_g133han01 = {
	.timings = &auo_g133han01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 293,
		.height = 165,
	},
	.deway = {
		.pwepawe = 200,
		.enabwe = 50,
		.disabwe = 50,
		.unpwepawe = 1000,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_g156han04_timings = {
	.pixewcwock = { 137000000, 141000000, 146000000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 60, 60, 60 },
	.hback_powch = { 90, 92, 111 },
	.hsync_wen =  { 32, 32, 32 },
	.vactive = { 1080, 1080, 1080 },
	.vfwont_powch = { 12, 12, 12 },
	.vback_powch = { 24, 36, 56 },
	.vsync_wen = { 8, 8, 8 },
};

static const stwuct panew_desc auo_g156han04 = {
	.timings = &auo_g156han04_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 344,
		.height = 194,
	},
	.deway = {
		.pwepawe = 50,		/* T2 */
		.enabwe = 200,		/* T3 */
		.disabwe = 110,		/* T10 */
		.unpwepawe = 1000,	/* T13 */
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode auo_g156xtn01_mode = {
	.cwock = 76000,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 33,
	.hsync_end = 1366 + 33 + 67,
	.htotaw = 1560,
	.vdispway = 768,
	.vsync_stawt = 768 + 4,
	.vsync_end = 768 + 4 + 4,
	.vtotaw = 806,
};

static const stwuct panew_desc auo_g156xtn01 = {
	.modes = &auo_g156xtn01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 344,
		.height = 194,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_g185han01_timings = {
	.pixewcwock = { 120000000, 144000000, 175000000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 36, 120, 148 },
	.hback_powch = { 24, 88, 108 },
	.hsync_wen = { 20, 48, 64 },
	.vactive = { 1080, 1080, 1080 },
	.vfwont_powch = { 6, 10, 40 },
	.vback_powch = { 2, 5, 20 },
	.vsync_wen = { 2, 5, 20 },
};

static const stwuct panew_desc auo_g185han01 = {
	.timings = &auo_g185han01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 409,
		.height = 230,
	},
	.deway = {
		.pwepawe = 50,
		.enabwe = 200,
		.disabwe = 110,
		.unpwepawe = 1000,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_g190ean01_timings = {
	.pixewcwock = { 90000000, 108000000, 135000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 126, 184, 1266 },
	.hback_powch = { 84, 122, 844 },
	.hsync_wen = { 70, 102, 704 },
	.vactive = { 1024, 1024, 1024 },
	.vfwont_powch = { 4, 26, 76 },
	.vback_powch = { 2, 8, 25 },
	.vsync_wen = { 2, 8, 25 },
};

static const stwuct panew_desc auo_g190ean01 = {
	.timings = &auo_g190ean01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 376,
		.height = 301,
	},
	.deway = {
		.pwepawe = 50,
		.enabwe = 200,
		.disabwe = 110,
		.unpwepawe = 1000,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing auo_p320hvn03_timings = {
	.pixewcwock = { 106000000, 148500000, 164000000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 25, 50, 130 },
	.hback_powch = { 25, 50, 130 },
	.hsync_wen = { 20, 40, 105 },
	.vactive = { 1080, 1080, 1080 },
	.vfwont_powch = { 8, 17, 150 },
	.vback_powch = { 8, 17, 150 },
	.vsync_wen = { 4, 11, 100 },
};

static const stwuct panew_desc auo_p320hvn03 = {
	.timings = &auo_p320hvn03_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 698,
		.height = 393,
	},
	.deway = {
		.pwepawe = 1,
		.enabwe = 450,
		.unpwepawe = 500,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode auo_t215hvn01_mode = {
	.cwock = 148800,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 88,
	.hsync_end = 1920 + 88 + 44,
	.htotaw = 1920 + 88 + 44 + 148,
	.vdispway = 1080,
	.vsync_stawt = 1080 + 4,
	.vsync_end = 1080 + 4 + 5,
	.vtotaw = 1080 + 4 + 5 + 36,
};

static const stwuct panew_desc auo_t215hvn01 = {
	.modes = &auo_t215hvn01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 430,
		.height = 270,
	},
	.deway = {
		.disabwe = 5,
		.unpwepawe = 1000,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode avic_tm070ddh03_mode = {
	.cwock = 51200,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 160,
	.hsync_end = 1024 + 160 + 4,
	.htotaw = 1024 + 160 + 4 + 156,
	.vdispway = 600,
	.vsync_stawt = 600 + 17,
	.vsync_end = 600 + 17 + 1,
	.vtotaw = 600 + 17 + 1 + 17,
};

static const stwuct panew_desc avic_tm070ddh03 = {
	.modes = &avic_tm070ddh03_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 90,
	},
	.deway = {
		.pwepawe = 20,
		.enabwe = 200,
		.disabwe = 200,
	},
};

static const stwuct dwm_dispway_mode bananapi_s070wv20_ct16_mode = {
	.cwock = 30000,
	.hdispway = 800,
	.hsync_stawt = 800 + 40,
	.hsync_end = 800 + 40 + 48,
	.htotaw = 800 + 40 + 48 + 40,
	.vdispway = 480,
	.vsync_stawt = 480 + 13,
	.vsync_end = 480 + 13 + 3,
	.vtotaw = 480 + 13 + 3 + 29,
};

static const stwuct panew_desc bananapi_s070wv20_ct16 = {
	.modes = &bananapi_s070wv20_ct16_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
};

static const stwuct dwm_dispway_mode boe_bp101wx1_100_mode = {
	.cwock = 78945,
	.hdispway = 1280,
	.hsync_stawt = 1280 + 0,
	.hsync_end = 1280 + 0 + 2,
	.htotaw = 1280 + 62 + 0 + 2,
	.vdispway = 800,
	.vsync_stawt = 800 + 8,
	.vsync_end = 800 + 8 + 2,
	.vtotaw = 800 + 6 + 8 + 2,
};

static const stwuct panew_desc boe_bp101wx1_100 = {
	.modes = &boe_bp101wx1_100_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.deway = {
		.enabwe = 50,
		.disabwe = 50,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing boe_ev121wxm_n10_1850_timing = {
	.pixewcwock = { 69922000, 71000000, 72293000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 48, 48, 48 },
	.hback_powch = { 80, 80, 80 },
	.hsync_wen = { 32, 32, 32 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 3, 3, 3 },
	.vback_powch = { 14, 14, 14 },
	.vsync_wen = { 6, 6, 6 },
};

static const stwuct panew_desc boe_ev121wxm_n10_1850 = {
	.timings = &boe_ev121wxm_n10_1850_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 261,
		.height = 163,
	},
	.deway = {
		.pwepawe = 9,
		.enabwe = 300,
		.unpwepawe = 300,
		.disabwe = 560,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode boe_hv070wsa_mode = {
	.cwock = 42105,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 30,
	.hsync_end = 1024 + 30 + 30,
	.htotaw = 1024 + 30 + 30 + 30,
	.vdispway = 600,
	.vsync_stawt = 600 + 10,
	.vsync_end = 600 + 10 + 10,
	.vtotaw = 600 + 10 + 10 + 10,
};

static const stwuct panew_desc boe_hv070wsa = {
	.modes = &boe_hv070wsa_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 90,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode cdtech_s043wq26h_ct7_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 5,
	.hsync_end = 480 + 5 + 5,
	.htotaw = 480 + 5 + 5 + 40,
	.vdispway = 272,
	.vsync_stawt = 272 + 8,
	.vsync_end = 272 + 8 + 8,
	.vtotaw = 272 + 8 + 8 + 8,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc cdtech_s043wq26h_ct7 = {
	.modes = &cdtech_s043wq26h_ct7_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
};

/* S070PWS19HP-FC21 2017/04/22 */
static const stwuct dwm_dispway_mode cdtech_s070pws19hp_fc21_mode = {
	.cwock = 51200,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 160,
	.hsync_end = 1024 + 160 + 20,
	.htotaw = 1024 + 160 + 20 + 140,
	.vdispway = 600,
	.vsync_stawt = 600 + 12,
	.vsync_end = 600 + 12 + 3,
	.vtotaw = 600 + 12 + 3 + 20,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc cdtech_s070pws19hp_fc21 = {
	.modes = &cdtech_s070pws19hp_fc21_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

/* S070SWV29HG-DC44 2017/09/21 */
static const stwuct dwm_dispway_mode cdtech_s070swv29hg_dc44_mode = {
	.cwock = 33300,
	.hdispway = 800,
	.hsync_stawt = 800 + 210,
	.hsync_end = 800 + 210 + 2,
	.htotaw = 800 + 210 + 2 + 44,
	.vdispway = 480,
	.vsync_stawt = 480 + 22,
	.vsync_end = 480 + 22 + 2,
	.vtotaw = 480 + 22 + 2 + 21,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc cdtech_s070swv29hg_dc44 = {
	.modes = &cdtech_s070swv29hg_dc44_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode cdtech_s070wv95_ct16_mode = {
	.cwock = 35000,
	.hdispway = 800,
	.hsync_stawt = 800 + 40,
	.hsync_end = 800 + 40 + 40,
	.htotaw = 800 + 40 + 40 + 48,
	.vdispway = 480,
	.vsync_stawt = 480 + 29,
	.vsync_end = 480 + 29 + 13,
	.vtotaw = 480 + 29 + 13 + 3,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc cdtech_s070wv95_ct16 = {
	.modes = &cdtech_s070wv95_ct16_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 85,
	},
};

static const stwuct dispway_timing chefwee_ch101owhwwh_002_timing = {
	.pixewcwock = { 68900000, 71100000, 73400000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 65, 80, 95 },
	.hback_powch = { 64, 79, 94 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 7, 11, 14 },
	.vback_powch = { 7, 11, 14 },
	.vsync_wen = { 1, 1, 1 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc chefwee_ch101owhwwh_002 = {
	.timings = &chefwee_ch101owhwwh_002_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 135,
	},
	.deway = {
		.enabwe = 200,
		.disabwe = 200,
	},
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode chunghwa_cwaa070wp03xg_mode = {
	.cwock = 66770,
	.hdispway = 800,
	.hsync_stawt = 800 + 49,
	.hsync_end = 800 + 49 + 33,
	.htotaw = 800 + 49 + 33 + 17,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 1,
	.vsync_end = 1280 + 1 + 7,
	.vtotaw = 1280 + 1 + 7 + 15,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc chunghwa_cwaa070wp03xg = {
	.modes = &chunghwa_cwaa070wp03xg_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 94,
		.height = 150,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode chunghwa_cwaa101wa01a_mode = {
	.cwock = 72070,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 58,
	.hsync_end = 1366 + 58 + 58,
	.htotaw = 1366 + 58 + 58 + 58,
	.vdispway = 768,
	.vsync_stawt = 768 + 4,
	.vsync_end = 768 + 4 + 4,
	.vtotaw = 768 + 4 + 4 + 4,
};

static const stwuct panew_desc chunghwa_cwaa101wa01a = {
	.modes = &chunghwa_cwaa101wa01a_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 220,
		.height = 120,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode chunghwa_cwaa101wb01_mode = {
	.cwock = 69300,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 48,
	.hsync_end = 1366 + 48 + 32,
	.htotaw = 1366 + 48 + 32 + 20,
	.vdispway = 768,
	.vsync_stawt = 768 + 16,
	.vsync_end = 768 + 16 + 8,
	.vtotaw = 768 + 16 + 8 + 16,
};

static const stwuct panew_desc chunghwa_cwaa101wb01 = {
	.modes = &chunghwa_cwaa101wb01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 223,
		.height = 125,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing dataimage_fg040346dsswbg04_timing = {
	.pixewcwock = { 5000000, 9000000, 12000000 },
	.hactive = { 480, 480, 480 },
	.hfwont_powch = { 12, 12, 12 },
	.hback_powch = { 12, 12, 12 },
	.hsync_wen = { 21, 21, 21 },
	.vactive = { 272, 272, 272 },
	.vfwont_powch = { 4, 4, 4 },
	.vback_powch = { 4, 4, 4 },
	.vsync_wen = { 8, 8, 8 },
};

static const stwuct panew_desc dataimage_fg040346dsswbg04 = {
	.timings = &dataimage_fg040346dsswbg04_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing dataimage_fg1001w0dsswmg01_timing = {
	.pixewcwock = { 68900000, 71110000, 73400000 },
	.hactive = { 1280, 1280, 1280 },
	.vactive = { 800, 800, 800 },
	.hback_powch = { 100, 100, 100 },
	.hfwont_powch = { 100, 100, 100 },
	.vback_powch = { 5, 5, 5 },
	.vfwont_powch = { 5, 5, 5 },
	.hsync_wen = { 24, 24, 24 },
	.vsync_wen = { 3, 3, 3 },
	.fwags = DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW,
};

static const stwuct panew_desc dataimage_fg1001w0dsswmg01 = {
	.timings = &dataimage_fg1001w0dsswmg01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
};

static const stwuct dwm_dispway_mode dataimage_scf0700c48ggu18_mode = {
	.cwock = 33260,
	.hdispway = 800,
	.hsync_stawt = 800 + 40,
	.hsync_end = 800 + 40 + 128,
	.htotaw = 800 + 40 + 128 + 88,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 2,
	.vtotaw = 480 + 10 + 2 + 33,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc dataimage_scf0700c48ggu18 = {
	.modes = &dataimage_scf0700c48ggu18_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
};

static const stwuct dispway_timing dwc_dwc0700yzg_1_timing = {
	.pixewcwock = { 45000000, 51200000, 57000000 },
	.hactive = { 1024, 1024, 1024 },
	.hfwont_powch = { 100, 106, 113 },
	.hback_powch = { 100, 106, 113 },
	.hsync_wen = { 100, 108, 114 },
	.vactive = { 600, 600, 600 },
	.vfwont_powch = { 8, 11, 15 },
	.vback_powch = { 8, 11, 15 },
	.vsync_wen = { 9, 13, 15 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc dwc_dwc0700yzg_1 = {
	.timings = &dwc_dwc0700yzg_1_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
	.deway = {
		.pwepawe = 30,
		.enabwe = 200,
		.disabwe = 200,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing dwc_dwc1010gig_timing = {
	.pixewcwock = { 68900000, 71100000, 73400000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 43, 53, 63 },
	.hback_powch = { 43, 53, 63 },
	.hsync_wen = { 44, 54, 64 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 5, 8, 11 },
	.vback_powch = { 5, 8, 11 },
	.vsync_wen = { 5, 7, 11 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc dwc_dwc1010gig = {
	.timings = &dwc_dwc1010gig_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 216,
		.height = 135,
	},
	.deway = {
		.pwepawe = 60,
		.enabwe = 150,
		.disabwe = 100,
		.unpwepawe = 60,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode edt_et035012dm6_mode = {
	.cwock = 6500,
	.hdispway = 320,
	.hsync_stawt = 320 + 20,
	.hsync_end = 320 + 20 + 30,
	.htotaw = 320 + 20 + 68,
	.vdispway = 240,
	.vsync_stawt = 240 + 4,
	.vsync_end = 240 + 4 + 4,
	.vtotaw = 240 + 4 + 4 + 14,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc edt_et035012dm6 = {
	.modes = &edt_et035012dm6_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 70,
		.height = 52,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_WOW | DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
};

static const stwuct dwm_dispway_mode edt_etm0350g0dh6_mode = {
	.cwock = 6520,
	.hdispway = 320,
	.hsync_stawt = 320 + 20,
	.hsync_end = 320 + 20 + 68,
	.htotaw = 320 + 20 + 68,
	.vdispway = 240,
	.vsync_stawt = 240 + 4,
	.vsync_end = 240 + 4 + 18,
	.vtotaw = 240 + 4 + 18,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc edt_etm0350g0dh6 = {
	.modes = &edt_etm0350g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 70,
		.height = 53,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode edt_etm043080dh6gp_mode = {
	.cwock = 10870,
	.hdispway = 480,
	.hsync_stawt = 480 + 8,
	.hsync_end = 480 + 8 + 4,
	.htotaw = 480 + 8 + 4 + 41,

	/*
	 * IWG22M: Y wesowution changed fow "dc_winuxfb" moduwe cwashing whiwe
	 * fb_awign
	 */

	.vdispway = 288,
	.vsync_stawt = 288 + 2,
	.vsync_end = 288 + 2 + 4,
	.vtotaw = 288 + 2 + 4 + 10,
};

static const stwuct panew_desc edt_etm043080dh6gp = {
	.modes = &edt_etm043080dh6gp_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 100,
		.height = 65,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode edt_etm0430g0dh6_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotaw = 480 + 2 + 41 + 2,
	.vdispway = 272,
	.vsync_stawt = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotaw = 272 + 2 + 10 + 2,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc edt_etm0430g0dh6 = {
	.modes = &edt_etm0430g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode edt_et057090dhu_mode = {
	.cwock = 25175,
	.hdispway = 640,
	.hsync_stawt = 640 + 16,
	.hsync_end = 640 + 16 + 30,
	.htotaw = 640 + 16 + 30 + 114,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 3,
	.vtotaw = 480 + 10 + 3 + 32,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc edt_et057090dhu = {
	.modes = &edt_et057090dhu_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 115,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode edt_etm0700g0dh6_mode = {
	.cwock = 33260,
	.hdispway = 800,
	.hsync_stawt = 800 + 40,
	.hsync_end = 800 + 40 + 128,
	.htotaw = 800 + 40 + 128 + 88,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 2,
	.vtotaw = 480 + 10 + 2 + 33,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc edt_etm0700g0dh6 = {
	.modes = &edt_etm0700g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct panew_desc edt_etm0700g0bdh6 = {
	.modes = &edt_etm0700g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing edt_etmw0700y5dha_timing = {
	.pixewcwock = { 40800000, 51200000, 67200000 },
	.hactive = { 1024, 1024, 1024 },
	.hfwont_powch = { 30, 106, 125 },
	.hback_powch = { 30, 106, 125 },
	.hsync_wen = { 30, 108, 126 },
	.vactive = { 600, 600, 600 },
	.vfwont_powch = { 3, 12, 67},
	.vback_powch = { 3, 12, 67 },
	.vsync_wen = { 4, 11, 66 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc edt_etmw0700y5dha = {
	.timings = &edt_etmw0700y5dha_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 155,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode edt_etmv570g2dhu_mode = {
	.cwock = 25175,
	.hdispway = 640,
	.hsync_stawt = 640,
	.hsync_end = 640 + 16,
	.htotaw = 640 + 16 + 30 + 114,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 3,
	.vtotaw = 480 + 10 + 3 + 35,
	.fwags = DWM_MODE_FWAG_PVSYNC | DWM_MODE_FWAG_PHSYNC,
};

static const stwuct panew_desc edt_etmv570g2dhu = {
	.modes = &edt_etmv570g2dhu_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 115,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing eink_vb3300_kca_timing = {
	.pixewcwock = { 40000000, 40000000, 40000000 },
	.hactive = { 334, 334, 334 },
	.hfwont_powch = { 1, 1, 1 },
	.hback_powch = { 1, 1, 1 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 1405, 1405, 1405 },
	.vfwont_powch = { 1, 1, 1 },
	.vback_powch = { 1, 1, 1 },
	.vsync_wen = { 1, 1, 1 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE,
};

static const stwuct panew_desc eink_vb3300_kca = {
	.timings = &eink_vb3300_kca_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 157,
		.height = 209,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing evewvision_vgg644804_timing = {
	.pixewcwock = { 25175000, 25175000, 25175000 },
	.hactive = { 640, 640, 640 },
	.hfwont_powch = { 16, 16, 16 },
	.hback_powch = { 82, 114, 170 },
	.hsync_wen = { 5, 30, 30 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 10, 10, 10 },
	.vback_powch = { 30, 32, 34 },
	.vsync_wen = { 1, 3, 5 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc evewvision_vgg644804 = {
	.timings = &evewvision_vgg644804_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 115,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dispway_timing evewvision_vgg804821_timing = {
	.pixewcwock = { 27600000, 33300000, 50000000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 40, 66, 70 },
	.hback_powch = { 40, 67, 70 },
	.hsync_wen = { 40, 67, 70 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 6, 10, 10 },
	.vback_powch = { 7, 11, 11 },
	.vsync_wen = { 7, 11, 11 },
	.fwags = DISPWAY_FWAGS_HSYNC_HIGH | DISPWAY_FWAGS_VSYNC_HIGH |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_NEGEDGE |
		 DISPWAY_FWAGS_SYNC_NEGEDGE,
};

static const stwuct panew_desc evewvision_vgg804821 = {
	.timings = &evewvision_vgg804821_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 108,
		.height = 64,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
};

static const stwuct dwm_dispway_mode foxwink_fw500wvw00_a0t_mode = {
	.cwock = 32260,
	.hdispway = 800,
	.hsync_stawt = 800 + 168,
	.hsync_end = 800 + 168 + 64,
	.htotaw = 800 + 168 + 64 + 88,
	.vdispway = 480,
	.vsync_stawt = 480 + 37,
	.vsync_end = 480 + 37 + 2,
	.vtotaw = 480 + 37 + 2 + 8,
};

static const stwuct panew_desc foxwink_fw500wvw00_a0t = {
	.modes = &foxwink_fw500wvw00_a0t_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 108,
		.height = 65,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dwm_dispway_mode fwida_fwd350h54004_modes[] = {
	{ /* 60 Hz */
		.cwock = 6000,
		.hdispway = 320,
		.hsync_stawt = 320 + 44,
		.hsync_end = 320 + 44 + 16,
		.htotaw = 320 + 44 + 16 + 20,
		.vdispway = 240,
		.vsync_stawt = 240 + 2,
		.vsync_end = 240 + 2 + 6,
		.vtotaw = 240 + 2 + 6 + 2,
		.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
	{ /* 50 Hz */
		.cwock = 5400,
		.hdispway = 320,
		.hsync_stawt = 320 + 56,
		.hsync_end = 320 + 56 + 16,
		.htotaw = 320 + 56 + 16 + 40,
		.vdispway = 240,
		.vsync_stawt = 240 + 2,
		.vsync_end = 240 + 2 + 6,
		.vtotaw = 240 + 2 + 6 + 2,
		.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
};

static const stwuct panew_desc fwida_fwd350h54004 = {
	.modes = fwida_fwd350h54004_modes,
	.num_modes = AWWAY_SIZE(fwida_fwd350h54004_modes),
	.bpc = 8,
	.size = {
		.width = 77,
		.height = 64,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode fwiendwyawm_hd702e_mode = {
	.cwock		= 67185,
	.hdispway	= 800,
	.hsync_stawt	= 800 + 20,
	.hsync_end	= 800 + 20 + 24,
	.htotaw		= 800 + 20 + 24 + 20,
	.vdispway	= 1280,
	.vsync_stawt	= 1280 + 4,
	.vsync_end	= 1280 + 4 + 8,
	.vtotaw		= 1280 + 4 + 8 + 4,
	.fwags		= DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc fwiendwyawm_hd702e = {
	.modes = &fwiendwyawm_hd702e_mode,
	.num_modes = 1,
	.size = {
		.width	= 94,
		.height	= 151,
	},
};

static const stwuct dwm_dispway_mode giantpwus_gpg482739qs5_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 5,
	.hsync_end = 480 + 5 + 1,
	.htotaw = 480 + 5 + 1 + 40,
	.vdispway = 272,
	.vsync_stawt = 272 + 8,
	.vsync_end = 272 + 8 + 1,
	.vtotaw = 272 + 8 + 1 + 8,
};

static const stwuct panew_desc giantpwus_gpg482739qs5 = {
	.modes = &giantpwus_gpg482739qs5_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dispway_timing giantpwus_gpm940b0_timing = {
	.pixewcwock = { 13500000, 27000000, 27500000 },
	.hactive = { 320, 320, 320 },
	.hfwont_powch = { 14, 686, 718 },
	.hback_powch = { 50, 70, 255 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 240, 240, 240 },
	.vfwont_powch = { 1, 1, 179 },
	.vback_powch = { 1, 21, 31 },
	.vsync_wen = { 1, 1, 6 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW,
};

static const stwuct panew_desc giantpwus_gpm940b0 = {
	.timings = &giantpwus_gpm940b0_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 60,
		.height = 45,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_3X8,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
};

static const stwuct dispway_timing hannstaw_hsd070pww1_timing = {
	.pixewcwock = { 64300000, 71100000, 82000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 1, 1, 10 },
	.hback_powch = { 1, 1, 10 },
	/*
	 * Accowding to the data sheet, the minimum howizontaw bwanking intewvaw
	 * is 54 cwocks (1 + 52 + 1), but tests with a Nitwogen6X have shown the
	 * minimum wowking howizontaw bwanking intewvaw to be 60 cwocks.
	 */
	.hsync_wen = { 58, 158, 661 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 1, 1, 10 },
	.vback_powch = { 1, 1, 10 },
	.vsync_wen = { 1, 21, 203 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc hannstaw_hsd070pww1 = {
	.timings = &hannstaw_hsd070pww1_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 151,
		.height = 94,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing hannstaw_hsd100pxn1_timing = {
	.pixewcwock = { 55000000, 65000000, 75000000 },
	.hactive = { 1024, 1024, 1024 },
	.hfwont_powch = { 40, 40, 40 },
	.hback_powch = { 220, 220, 220 },
	.hsync_wen = { 20, 60, 100 },
	.vactive = { 768, 768, 768 },
	.vfwont_powch = { 7, 7, 7 },
	.vback_powch = { 21, 21, 21 },
	.vsync_wen = { 10, 10, 10 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc hannstaw_hsd100pxn1 = {
	.timings = &hannstaw_hsd100pxn1_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 203,
		.height = 152,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing hannstaw_hsd101pww2_timing = {
	.pixewcwock = { 64300000, 71100000, 82000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 1, 1, 10 },
	.hback_powch = { 1, 1, 10 },
	.hsync_wen = { 58, 158, 661 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 1, 1, 10 },
	.vback_powch = { 1, 1, 10 },
	.vsync_wen = { 1, 21, 203 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc hannstaw_hsd101pww2 = {
	.timings = &hannstaw_hsd101pww2_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode hitachi_tx23d38vm0caa_mode = {
	.cwock = 33333,
	.hdispway = 800,
	.hsync_stawt = 800 + 85,
	.hsync_end = 800 + 85 + 86,
	.htotaw = 800 + 85 + 86 + 85,
	.vdispway = 480,
	.vsync_stawt = 480 + 16,
	.vsync_end = 480 + 16 + 13,
	.vtotaw = 480 + 16 + 13 + 16,
};

static const stwuct panew_desc hitachi_tx23d38vm0caa = {
	.modes = &hitachi_tx23d38vm0caa_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 195,
		.height = 117,
	},
	.deway = {
		.enabwe = 160,
		.disabwe = 160,
	},
};

static const stwuct dwm_dispway_mode innowux_at043tn24_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotaw = 480 + 2 + 41 + 2,
	.vdispway = 272,
	.vsync_stawt = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotaw = 272 + 2 + 10 + 2,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc innowux_at043tn24 = {
	.modes = &innowux_at043tn24_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
};

static const stwuct dwm_dispway_mode innowux_at070tn92_mode = {
	.cwock = 33333,
	.hdispway = 800,
	.hsync_stawt = 800 + 210,
	.hsync_end = 800 + 210 + 20,
	.htotaw = 800 + 210 + 20 + 46,
	.vdispway = 480,
	.vsync_stawt = 480 + 22,
	.vsync_end = 480 + 22 + 10,
	.vtotaw = 480 + 22 + 23 + 10,
};

static const stwuct panew_desc innowux_at070tn92 = {
	.modes = &innowux_at070tn92_mode,
	.num_modes = 1,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dispway_timing innowux_g070ace_w01_timing = {
	.pixewcwock = { 25200000, 35000000, 35700000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 30, 32, 87 },
	.hback_powch = { 30, 32, 87 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 3, 3, 3 },
	.vback_powch = { 13, 13, 13 },
	.vsync_wen = { 1, 1, 4 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc innowux_g070ace_w01 = {
	.timings = &innowux_g070ace_w01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.deway = {
		.pwepawe = 10,
		.enabwe = 50,
		.disabwe = 50,
		.unpwepawe = 500,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing innowux_g070y2_w01_timing = {
	.pixewcwock = { 28000000, 29500000, 32000000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 61, 91, 141 },
	.hback_powch = { 60, 90, 140 },
	.hsync_wen = { 12, 12, 12 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 4, 9, 30 },
	.vback_powch = { 4, 8, 28 },
	.vsync_wen = { 2, 2, 2 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc innowux_g070y2_w01 = {
	.timings = &innowux_g070y2_w01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.deway = {
		.pwepawe = 10,
		.enabwe = 100,
		.disabwe = 100,
		.unpwepawe = 800,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode innowux_g070y2_t02_mode = {
	.cwock = 33333,
	.hdispway = 800,
	.hsync_stawt = 800 + 210,
	.hsync_end = 800 + 210 + 20,
	.htotaw = 800 + 210 + 20 + 46,
	.vdispway = 480,
	.vsync_stawt = 480 + 22,
	.vsync_end = 480 + 22 + 10,
	.vtotaw = 480 + 22 + 23 + 10,
};

static const stwuct panew_desc innowux_g070y2_t02 = {
	.modes = &innowux_g070y2_t02_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 92,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing innowux_g101ice_w01_timing = {
	.pixewcwock = { 60400000, 71100000, 74700000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 30, 60, 70 },
	.hback_powch = { 30, 60, 70 },
	.hsync_wen = { 22, 40, 60 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 3, 8, 14 },
	.vback_powch = { 3, 8, 14 },
	.vsync_wen = { 4, 7, 12 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc innowux_g101ice_w01 = {
	.timings = &innowux_g101ice_w01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 135,
	},
	.deway = {
		.enabwe = 200,
		.disabwe = 200,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing innowux_g121i1_w01_timing = {
	.pixewcwock = { 67450000, 71000000, 74550000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 40, 80, 160 },
	.hback_powch = { 39, 79, 159 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 5, 11, 100 },
	.vback_powch = { 4, 11, 99 },
	.vsync_wen = { 1, 1, 1 },
};

static const stwuct panew_desc innowux_g121i1_w01 = {
	.timings = &innowux_g121i1_w01_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 261,
		.height = 163,
	},
	.deway = {
		.enabwe = 200,
		.disabwe = 20,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode innowux_g121x1_w03_mode = {
	.cwock = 65000,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 0,
	.hsync_end = 1024 + 1,
	.htotaw = 1024 + 0 + 1 + 320,
	.vdispway = 768,
	.vsync_stawt = 768 + 38,
	.vsync_end = 768 + 38 + 1,
	.vtotaw = 768 + 38 + 1 + 0,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc innowux_g121x1_w03 = {
	.modes = &innowux_g121x1_w03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 246,
		.height = 185,
	},
	.deway = {
		.enabwe = 200,
		.unpwepawe = 200,
		.disabwe = 400,
	},
};

static const stwuct dispway_timing innowux_g156hce_w01_timings = {
	.pixewcwock = { 120000000, 141860000, 150000000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 80, 90, 100 },
	.hback_powch = { 80, 90, 100 },
	.hsync_wen = { 20, 30, 30 },
	.vactive = { 1080, 1080, 1080 },
	.vfwont_powch = { 3, 10, 20 },
	.vback_powch = { 3, 10, 20 },
	.vsync_wen = { 4, 10, 10 },
};

static const stwuct panew_desc innowux_g156hce_w01 = {
	.timings = &innowux_g156hce_w01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 344,
		.height = 194,
	},
	.deway = {
		.pwepawe = 1,		/* T1+T2 */
		.enabwe = 450,		/* T5 */
		.disabwe = 200,		/* T6 */
		.unpwepawe = 10,	/* T3+T7 */
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode innowux_n156bge_w21_mode = {
	.cwock = 69300,
	.hdispway = 1366,
	.hsync_stawt = 1366 + 16,
	.hsync_end = 1366 + 16 + 34,
	.htotaw = 1366 + 16 + 34 + 50,
	.vdispway = 768,
	.vsync_stawt = 768 + 2,
	.vsync_end = 768 + 2 + 6,
	.vtotaw = 768 + 2 + 6 + 12,
};

static const stwuct panew_desc innowux_n156bge_w21 = {
	.modes = &innowux_n156bge_w21_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 344,
		.height = 193,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode innowux_zj070na_01p_mode = {
	.cwock = 51501,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 128,
	.hsync_end = 1024 + 128 + 64,
	.htotaw = 1024 + 128 + 64 + 128,
	.vdispway = 600,
	.vsync_stawt = 600 + 16,
	.vsync_end = 600 + 16 + 4,
	.vtotaw = 600 + 16 + 4 + 16,
};

static const stwuct panew_desc innowux_zj070na_01p = {
	.modes = &innowux_zj070na_01p_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 90,
	},
};

static const stwuct dispway_timing koe_tx14d24vm1bpa_timing = {
	.pixewcwock = { 5580000, 5850000, 6200000 },
	.hactive = { 320, 320, 320 },
	.hfwont_powch = { 30, 30, 30 },
	.hback_powch = { 30, 30, 30 },
	.hsync_wen = { 1, 5, 17 },
	.vactive = { 240, 240, 240 },
	.vfwont_powch = { 6, 6, 6 },
	.vback_powch = { 5, 5, 5 },
	.vsync_wen = { 1, 2, 11 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc koe_tx14d24vm1bpa = {
	.timings = &koe_tx14d24vm1bpa_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 115,
		.height = 86,
	},
};

static const stwuct dispway_timing koe_tx26d202vm0bwa_timing = {
	.pixewcwock = { 151820000, 156720000, 159780000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 105, 130, 142 },
	.hback_powch = { 45, 70, 82 },
	.hsync_wen = { 30, 30, 30 },
	.vactive = { 1200, 1200, 1200},
	.vfwont_powch = { 3, 5, 10 },
	.vback_powch = { 2, 5, 10 },
	.vsync_wen = { 5, 5, 5 },
};

static const stwuct panew_desc koe_tx26d202vm0bwa = {
	.timings = &koe_tx26d202vm0bwa_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.deway = {
		.pwepawe = 1000,
		.enabwe = 1000,
		.unpwepawe = 1000,
		.disabwe = 1000,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing koe_tx31d200vm0baa_timing = {
	.pixewcwock = { 39600000, 43200000, 48000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 16, 36, 56 },
	.hback_powch = { 16, 36, 56 },
	.hsync_wen = { 8, 8, 8 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 6, 21, 33 },
	.vback_powch = { 6, 21, 33 },
	.vsync_wen = { 8, 8, 8 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc koe_tx31d200vm0baa = {
	.timings = &koe_tx31d200vm0baa_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 292,
		.height = 109,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing kyo_tcg121xgwp_timing = {
	.pixewcwock = { 52000000, 65000000, 71000000 },
	.hactive = { 1024, 1024, 1024 },
	.hfwont_powch = { 2, 2, 2 },
	.hback_powch = { 2, 2, 2 },
	.hsync_wen = { 86, 124, 244 },
	.vactive = { 768, 768, 768 },
	.vfwont_powch = { 2, 2, 2 },
	.vback_powch = { 2, 2, 2 },
	.vsync_wen = { 6, 34, 73 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc kyo_tcg121xgwp = {
	.timings = &kyo_tcg121xgwp_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 246,
		.height = 184,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode wemakew_bw035_wgb_002_mode = {
	.cwock = 7000,
	.hdispway = 320,
	.hsync_stawt = 320 + 20,
	.hsync_end = 320 + 20 + 30,
	.htotaw = 320 + 20 + 30 + 38,
	.vdispway = 240,
	.vsync_stawt = 240 + 4,
	.vsync_end = 240 + 4 + 3,
	.vtotaw = 240 + 4 + 3 + 15,
};

static const stwuct panew_desc wemakew_bw035_wgb_002 = {
	.modes = &wemakew_bw035_wgb_002_mode,
	.num_modes = 1,
	.size = {
		.width = 70,
		.height = 52,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_WOW,
};

static const stwuct dwm_dispway_mode wg_wb070wv8_mode = {
	.cwock = 33246,
	.hdispway = 800,
	.hsync_stawt = 800 + 88,
	.hsync_end = 800 + 88 + 80,
	.htotaw = 800 + 88 + 80 + 88,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 25,
	.vtotaw = 480 + 10 + 25 + 10,
};

static const stwuct panew_desc wg_wb070wv8 = {
	.modes = &wg_wb070wv8_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 151,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing wogictechno_wt161010_2nh_timing = {
	.pixewcwock = { 26400000, 33300000, 46800000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 16, 210, 354 },
	.hback_powch = { 46, 46, 46 },
	.hsync_wen = { 1, 20, 40 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 7, 22, 147 },
	.vback_powch = { 23, 23, 23 },
	.vsync_wen = { 1, 10, 20 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc wogictechno_wt161010_2nh = {
	.timings = &wogictechno_wt161010_2nh_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing wogictechno_wt170410_2whc_timing = {
	.pixewcwock = { 68900000, 71100000, 73400000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 23, 60, 71 },
	.hback_powch = { 23, 60, 71 },
	.hsync_wen = { 15, 40, 47 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 5, 7, 10 },
	.vback_powch = { 5, 7, 10 },
	.vsync_wen = { 6, 9, 12 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc wogictechno_wt170410_2whc = {
	.timings = &wogictechno_wt170410_2whc_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode wogictechno_wttd800480070_w2wt_mode = {
	.cwock = 33000,
	.hdispway = 800,
	.hsync_stawt = 800 + 112,
	.hsync_end = 800 + 112 + 3,
	.htotaw = 800 + 112 + 3 + 85,
	.vdispway = 480,
	.vsync_stawt = 480 + 38,
	.vsync_end = 480 + 38 + 3,
	.vtotaw = 480 + 38 + 3 + 29,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc wogictechno_wttd800480070_w2wt = {
	.modes = &wogictechno_wttd800480070_w2wt_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 86,
	},
	.deway = {
		.pwepawe = 45,
		.enabwe = 100,
		.disabwe = 100,
		.unpwepawe = 45
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode wogictechno_wttd800480070_w6wh_wt_mode = {
	.cwock = 33000,
	.hdispway = 800,
	.hsync_stawt = 800 + 154,
	.hsync_end = 800 + 154 + 3,
	.htotaw = 800 + 154 + 3 + 43,
	.vdispway = 480,
	.vsync_stawt = 480 + 47,
	.vsync_end = 480 + 47 + 3,
	.vtotaw = 480 + 47 + 3 + 20,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc wogictechno_wttd800480070_w6wh_wt = {
	.modes = &wogictechno_wttd800480070_w6wh_wt_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 86,
	},
	.deway = {
		.pwepawe = 45,
		.enabwe = 100,
		.disabwe = 100,
		.unpwepawe = 45
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode wogicpd_type_28_mode = {
	.cwock = 9107,
	.hdispway = 480,
	.hsync_stawt = 480 + 3,
	.hsync_end = 480 + 3 + 42,
	.htotaw = 480 + 3 + 42 + 2,

	.vdispway = 272,
	.vsync_stawt = 272 + 2,
	.vsync_end = 272 + 2 + 11,
	.vtotaw = 272 + 2 + 11 + 3,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc wogicpd_type_28 = {
	.modes = &wogicpd_type_28_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 105,
		.height = 67,
	},
	.deway = {
		.pwepawe = 200,
		.enabwe = 200,
		.unpwepawe = 200,
		.disabwe = 200,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE |
		     DWM_BUS_FWAG_SYNC_DWIVE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode mitsubishi_aa070mc01_mode = {
	.cwock = 30400,
	.hdispway = 800,
	.hsync_stawt = 800 + 0,
	.hsync_end = 800 + 1,
	.htotaw = 800 + 0 + 1 + 160,
	.vdispway = 480,
	.vsync_stawt = 480 + 0,
	.vsync_end = 480 + 48 + 1,
	.vtotaw = 480 + 48 + 1 + 0,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc mitsubishi_aa070mc01 = {
	.modes = &mitsubishi_aa070mc01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},

	.deway = {
		.enabwe = 200,
		.unpwepawe = 200,
		.disabwe = 400,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
};

static const stwuct dwm_dispway_mode mitsubishi_aa084xe01_mode = {
	.cwock = 56234,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 24,
	.hsync_end = 1024 + 24 + 63,
	.htotaw = 1024 + 24 + 63 + 1,
	.vdispway = 768,
	.vsync_stawt = 768 + 3,
	.vsync_end = 768 + 3 + 6,
	.vtotaw = 768 + 3 + 6 + 1,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc mitsubishi_aa084xe01 = {
	.modes = &mitsubishi_aa084xe01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 1024,
		.height = 768,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB565_1X16,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dispway_timing muwti_inno_mi0700s4t_6_timing = {
	.pixewcwock = { 29000000, 33000000, 38000000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 180, 210, 240 },
	.hback_powch = { 16, 16, 16 },
	.hsync_wen = { 30, 30, 30 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 12, 22, 32 },
	.vback_powch = { 10, 10, 10 },
	.vsync_wen = { 13, 13, 13 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc muwti_inno_mi0700s4t_6 = {
	.timings = &muwti_inno_mi0700s4t_6_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing muwti_inno_mi0800ft_9_timing = {
	.pixewcwock = { 32000000, 40000000, 50000000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 16, 210, 354 },
	.hback_powch = { 6, 26, 45 },
	.hsync_wen = { 1, 20, 40 },
	.vactive = { 600, 600, 600 },
	.vfwont_powch = { 1, 12, 77 },
	.vback_powch = { 3, 13, 22 },
	.vsync_wen = { 1, 10, 20 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc muwti_inno_mi0800ft_9 = {
	.timings = &muwti_inno_mi0800ft_9_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 162,
		.height = 122,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing muwti_inno_mi1010ait_1cp_timing = {
	.pixewcwock = { 68900000, 70000000, 73400000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 30, 60, 71 },
	.hback_powch = { 30, 60, 71 },
	.hsync_wen = { 10, 10, 48 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 5, 10, 10 },
	.vback_powch = { 5, 10, 10 },
	.vsync_wen = { 5, 6, 13 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc muwti_inno_mi1010ait_1cp = {
	.timings = &muwti_inno_mi1010ait_1cp_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.deway = {
		.enabwe = 50,
		.disabwe = 50,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing nec_nw12880bc20_05_timing = {
	.pixewcwock = { 67000000, 71000000, 75000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 2, 30, 30 },
	.hback_powch = { 6, 100, 100 },
	.hsync_wen = { 2, 30, 30 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 5, 5, 5 },
	.vback_powch = { 11, 11, 11 },
	.vsync_wen = { 7, 7, 7 },
};

static const stwuct panew_desc nec_nw12880bc20_05 = {
	.timings = &nec_nw12880bc20_05_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 261,
		.height = 163,
	},
	.deway = {
		.enabwe = 50,
		.disabwe = 50,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode nec_nw4827hc19_05b_mode = {
	.cwock = 10870,
	.hdispway = 480,
	.hsync_stawt = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotaw = 480 + 2 + 41 + 2,
	.vdispway = 272,
	.vsync_stawt = 272 + 2,
	.vsync_end = 272 + 2 + 4,
	.vtotaw = 272 + 2 + 4 + 2,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc nec_nw4827hc19_05b = {
	.modes = &nec_nw4827hc19_05b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
};

static const stwuct dwm_dispway_mode netwon_dy_e231732_mode = {
	.cwock = 66000,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 160,
	.hsync_end = 1024 + 160 + 70,
	.htotaw = 1024 + 160 + 70 + 90,
	.vdispway = 600,
	.vsync_stawt = 600 + 127,
	.vsync_end = 600 + 127 + 20,
	.vtotaw = 600 + 127 + 20 + 3,
};

static const stwuct panew_desc netwon_dy_e231732 = {
	.modes = &netwon_dy_e231732_mode,
	.num_modes = 1,
	.size = {
		.width = 154,
		.height = 87,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dwm_dispway_mode newhaven_nhd_43_480272ef_atxw_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotaw = 480 + 2 + 41 + 2,
	.vdispway = 272,
	.vsync_stawt = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotaw = 272 + 2 + 10 + 2,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc newhaven_nhd_43_480272ef_atxw = {
	.modes = &newhaven_nhd_43_480272ef_atxw_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE |
		     DWM_BUS_FWAG_SYNC_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing nwt_nw192108ac18_02d_timing = {
	.pixewcwock = { 130000000, 148350000, 163000000 },
	.hactive = { 1920, 1920, 1920 },
	.hfwont_powch = { 80, 100, 100 },
	.hback_powch = { 100, 120, 120 },
	.hsync_wen = { 50, 60, 60 },
	.vactive = { 1080, 1080, 1080 },
	.vfwont_powch = { 12, 30, 30 },
	.vback_powch = { 4, 10, 10 },
	.vsync_wen = { 4, 5, 5 },
};

static const stwuct panew_desc nwt_nw192108ac18_02d = {
	.timings = &nwt_nw192108ac18_02d_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 344,
		.height = 194,
	},
	.deway = {
		.unpwepawe = 500,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode nvd_9128_mode = {
	.cwock = 29500,
	.hdispway = 800,
	.hsync_stawt = 800 + 130,
	.hsync_end = 800 + 130 + 98,
	.htotaw = 800 + 0 + 130 + 98,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 50,
	.vtotaw = 480 + 0 + 10 + 50,
};

static const stwuct panew_desc nvd_9128 = {
	.modes = &nvd_9128_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 156,
		.height = 88,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing okaya_ws800480t_7x0gp_timing = {
	.pixewcwock = { 30000000, 30000000, 40000000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 40, 40, 40 },
	.hback_powch = { 40, 40, 40 },
	.hsync_wen = { 1, 48, 48 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 13, 13, 13 },
	.vback_powch = { 29, 29, 29 },
	.vsync_wen = { 3, 3, 3 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc okaya_ws800480t_7x0gp = {
	.timings = &okaya_ws800480t_7x0gp_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 87,
	},
	.deway = {
		.pwepawe = 41,
		.enabwe = 50,
		.unpwepawe = 41,
		.disabwe = 50,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dwm_dispway_mode owimex_wcd_owinuxino_43ts_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 5,
	.hsync_end = 480 + 5 + 30,
	.htotaw = 480 + 5 + 30 + 10,
	.vdispway = 272,
	.vsync_stawt = 272 + 8,
	.vsync_end = 272 + 8 + 5,
	.vtotaw = 272 + 8 + 5 + 3,
};

static const stwuct panew_desc owimex_wcd_owinuxino_43ts = {
	.modes = &owimex_wcd_owinuxino_43ts_mode,
	.num_modes = 1,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

/*
 * 800x480 CVT. The panew appeaws to be quite accepting, at weast as faw as
 * pixew cwocks, but this is the timing that was being used in the Adafwuit
 * instawwation instwuctions.
 */
static const stwuct dwm_dispway_mode ontat_yx700wv03_mode = {
	.cwock = 29500,
	.hdispway = 800,
	.hsync_stawt = 824,
	.hsync_end = 896,
	.htotaw = 992,
	.vdispway = 480,
	.vsync_stawt = 483,
	.vsync_end = 493,
	.vtotaw = 500,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

/*
 * Specification at:
 * https://www.adafwuit.com/images/pwoduct-fiwes/2406/c3163.pdf
 */
static const stwuct panew_desc ontat_yx700wv03 = {
	.modes = &ontat_yx700wv03_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 83,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dwm_dispway_mode owtustech_com37h3m_mode  = {
	.cwock = 22230,
	.hdispway = 480,
	.hsync_stawt = 480 + 40,
	.hsync_end = 480 + 40 + 10,
	.htotaw = 480 + 40 + 10 + 40,
	.vdispway = 640,
	.vsync_stawt = 640 + 4,
	.vsync_end = 640 + 4 + 2,
	.vtotaw = 640 + 4 + 2 + 4,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc owtustech_com37h3m = {
	.modes = &owtustech_com37h3m_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 56,	/* 56.16mm */
		.height = 75,	/* 74.88mm */
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_DWIVE_POSEDGE,
};

static const stwuct dwm_dispway_mode owtustech_com43h4m85uwc_mode  = {
	.cwock = 25000,
	.hdispway = 480,
	.hsync_stawt = 480 + 10,
	.hsync_end = 480 + 10 + 10,
	.htotaw = 480 + 10 + 10 + 15,
	.vdispway = 800,
	.vsync_stawt = 800 + 3,
	.vsync_end = 800 + 3 + 3,
	.vtotaw = 800 + 3 + 3 + 3,
};

static const stwuct panew_desc owtustech_com43h4m85uwc = {
	.modes = &owtustech_com43h4m85uwc_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 56,
		.height = 93,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode osddispways_osd070t1718_19ts_mode  = {
	.cwock = 33000,
	.hdispway = 800,
	.hsync_stawt = 800 + 210,
	.hsync_end = 800 + 210 + 30,
	.htotaw = 800 + 210 + 30 + 16,
	.vdispway = 480,
	.vsync_stawt = 480 + 22,
	.vsync_end = 480 + 22 + 13,
	.vtotaw = 480 + 22 + 13 + 10,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc osddispways_osd070t1718_19ts = {
	.modes = &osddispways_osd070t1718_19ts_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE |
		DWM_BUS_FWAG_SYNC_DWIVE_POSEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode pda_91_00156_a0_mode = {
	.cwock = 33300,
	.hdispway = 800,
	.hsync_stawt = 800 + 1,
	.hsync_end = 800 + 1 + 64,
	.htotaw = 800 + 1 + 64 + 64,
	.vdispway = 480,
	.vsync_stawt = 480 + 1,
	.vsync_end = 480 + 1 + 23,
	.vtotaw = 480 + 1 + 23 + 22,
};

static const stwuct panew_desc pda_91_00156_a0  = {
	.modes = &pda_91_00156_a0_mode,
	.num_modes = 1,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dwm_dispway_mode powewtip_ph800480t013_idf02_mode = {
	.cwock = 24750,
	.hdispway = 800,
	.hsync_stawt = 800 + 54,
	.hsync_end = 800 + 54 + 2,
	.htotaw = 800 + 54 + 2 + 44,
	.vdispway = 480,
	.vsync_stawt = 480 + 49,
	.vsync_end = 480 + 49 + 2,
	.vtotaw = 480 + 49 + 2 + 22,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc powewtip_ph800480t013_idf02  = {
	.modes = &powewtip_ph800480t013_idf02_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dwm_dispway_mode qd43003c0_40_mode = {
	.cwock = 9000,
	.hdispway = 480,
	.hsync_stawt = 480 + 8,
	.hsync_end = 480 + 8 + 4,
	.htotaw = 480 + 8 + 4 + 39,
	.vdispway = 272,
	.vsync_stawt = 272 + 4,
	.vsync_end = 272 + 4 + 10,
	.vtotaw = 272 + 4 + 10 + 2,
};

static const stwuct panew_desc qd43003c0_40 = {
	.modes = &qd43003c0_40_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 53,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dwm_dispway_mode qishengwong_gophew2b_wcd_modes[] = {
	{ /* 60 Hz */
		.cwock = 10800,
		.hdispway = 480,
		.hsync_stawt = 480 + 77,
		.hsync_end = 480 + 77 + 41,
		.htotaw = 480 + 77 + 41 + 2,
		.vdispway = 272,
		.vsync_stawt = 272 + 16,
		.vsync_end = 272 + 16 + 10,
		.vtotaw = 272 + 16 + 10 + 2,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	},
	{ /* 50 Hz */
		.cwock = 10800,
		.hdispway = 480,
		.hsync_stawt = 480 + 17,
		.hsync_end = 480 + 17 + 41,
		.htotaw = 480 + 17 + 41 + 2,
		.vdispway = 272,
		.vsync_stawt = 272 + 116,
		.vsync_end = 272 + 116 + 10,
		.vtotaw = 272 + 116 + 10 + 2,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	},
};

static const stwuct panew_desc qishengwong_gophew2b_wcd = {
	.modes = qishengwong_gophew2b_wcd_modes,
	.num_modes = AWWAY_SIZE(qishengwong_gophew2b_wcd_modes),
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing wocktech_wk043fn48h_timing = {
	.pixewcwock = { 6000000, 9000000, 12000000 },
	.hactive = { 480, 480, 480 },
	.hback_powch = { 8, 43, 43 },
	.hfwont_powch = { 2, 8, 8 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 272, 272, 272 },
	.vback_powch = { 2, 12, 12 },
	.vfwont_powch = { 1, 4, 4 },
	.vsync_wen = { 1, 10, 10 },
	.fwags = DISPWAY_FWAGS_VSYNC_WOW | DISPWAY_FWAGS_HSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE,
};

static const stwuct panew_desc wocktech_wk043fn48h = {
	.timings = &wocktech_wk043fn48h_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 95,
		.height = 54,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing wocktech_wk070ew9427_timing = {
	.pixewcwock = { 26400000, 33300000, 46800000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 16, 210, 354 },
	.hback_powch = { 46, 46, 46 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 7, 22, 147 },
	.vback_powch = { 23, 23, 23 },
	.vsync_wen = { 1, 1, 1 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc wocktech_wk070ew9427 = {
	.timings = &wocktech_wk070ew9427_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 154,
		.height = 86,
	},
	.deway = {
		.pwepawe = 41,
		.enabwe = 50,
		.unpwepawe = 41,
		.disabwe = 50,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dwm_dispway_mode wocktech_wk101ii01d_ct_mode = {
	.cwock = 71100,
	.hdispway = 1280,
	.hsync_stawt = 1280 + 48,
	.hsync_end = 1280 + 48 + 32,
	.htotaw = 1280 + 48 + 32 + 80,
	.vdispway = 800,
	.vsync_stawt = 800 + 2,
	.vsync_end = 800 + 2 + 5,
	.vtotaw = 800 + 2 + 5 + 16,
};

static const stwuct panew_desc wocktech_wk101ii01d_ct = {
	.modes = &wocktech_wk101ii01d_ct_mode,
	.bpc = 8,
	.num_modes = 1,
	.size = {
		.width = 217,
		.height = 136,
	},
	.deway = {
		.pwepawe = 50,
		.disabwe = 50,
	},
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing samsung_wtw101aw01_timing = {
	.pixewcwock = { 66663000, 66663000, 66663000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 18, 18, 18 },
	.hback_powch = { 36, 36, 36 },
	.hsync_wen = { 16, 16, 16 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 4, 4, 4 },
	.vback_powch = { 16, 16, 16 },
	.vsync_wen = { 3, 3, 3 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW,
};

static const stwuct panew_desc samsung_wtw101aw01 = {
	.timings = &samsung_wtw101aw01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 135,
	},
	.deway = {
		.pwepawe = 40,
		.enabwe = 300,
		.disabwe = 200,
		.unpwepawe = 600,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode samsung_wtn101nt05_mode = {
	.cwock = 54030,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 24,
	.hsync_end = 1024 + 24 + 136,
	.htotaw = 1024 + 24 + 136 + 160,
	.vdispway = 600,
	.vsync_stawt = 600 + 3,
	.vsync_end = 600 + 3 + 6,
	.vtotaw = 600 + 3 + 6 + 61,
};

static const stwuct panew_desc samsung_wtn101nt05 = {
	.modes = &samsung_wtn101nt05_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 223,
		.height = 125,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dispway_timing satoz_sat050at40h12w2_timing = {
	.pixewcwock = {33300000, 33300000, 50000000},
	.hactive = {800, 800, 800},
	.hfwont_powch = {16, 210, 354},
	.hback_powch = {46, 46, 46},
	.hsync_wen = {1, 1, 40},
	.vactive = {480, 480, 480},
	.vfwont_powch = {7, 22, 147},
	.vback_powch = {23, 23, 23},
	.vsync_wen = {1, 1, 20},
};

static const stwuct panew_desc satoz_sat050at40h12w2 = {
	.timings = &satoz_sat050at40h12w2_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 108,
		.height = 65,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode shawp_wq070y3dg3b_mode = {
	.cwock = 33260,
	.hdispway = 800,
	.hsync_stawt = 800 + 64,
	.hsync_end = 800 + 64 + 128,
	.htotaw = 800 + 64 + 128 + 64,
	.vdispway = 480,
	.vsync_stawt = 480 + 8,
	.vsync_end = 480 + 8 + 2,
	.vtotaw = 480 + 8 + 2 + 35,
	.fwags = DISPWAY_FWAGS_PIXDATA_POSEDGE,
};

static const stwuct panew_desc shawp_wq070y3dg3b = {
	.modes = &shawp_wq070y3dg3b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,	/* 152.4mm */
		.height = 91,	/* 91.4mm */
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_DWIVE_POSEDGE,
};

static const stwuct dwm_dispway_mode shawp_wq035q7db03_mode = {
	.cwock = 5500,
	.hdispway = 240,
	.hsync_stawt = 240 + 16,
	.hsync_end = 240 + 16 + 7,
	.htotaw = 240 + 16 + 7 + 5,
	.vdispway = 320,
	.vsync_stawt = 320 + 9,
	.vsync_end = 320 + 9 + 1,
	.vtotaw = 320 + 9 + 1 + 7,
};

static const stwuct panew_desc shawp_wq035q7db03 = {
	.modes = &shawp_wq035q7db03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 54,
		.height = 72,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dispway_timing shawp_wq101k1wy04_timing = {
	.pixewcwock = { 60000000, 65000000, 80000000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 20, 20, 20 },
	.hback_powch = { 20, 20, 20 },
	.hsync_wen = { 10, 10, 10 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 4, 4, 4 },
	.vback_powch = { 4, 4, 4 },
	.vsync_wen = { 4, 4, 4 },
	.fwags = DISPWAY_FWAGS_PIXDATA_POSEDGE,
};

static const stwuct panew_desc shawp_wq101k1wy04 = {
	.timings = &shawp_wq101k1wy04_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 217,
		.height = 136,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode shawp_ws020b1dd01d_modes[] = {
	{ /* 50 Hz */
		.cwock = 3000,
		.hdispway = 240,
		.hsync_stawt = 240 + 58,
		.hsync_end = 240 + 58 + 1,
		.htotaw = 240 + 58 + 1 + 1,
		.vdispway = 160,
		.vsync_stawt = 160 + 24,
		.vsync_end = 160 + 24 + 10,
		.vtotaw = 160 + 24 + 10 + 6,
		.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
	{ /* 60 Hz */
		.cwock = 3000,
		.hdispway = 240,
		.hsync_stawt = 240 + 8,
		.hsync_end = 240 + 8 + 1,
		.htotaw = 240 + 8 + 1 + 1,
		.vdispway = 160,
		.vsync_stawt = 160 + 24,
		.vsync_end = 160 + 24 + 10,
		.vtotaw = 160 + 24 + 10 + 6,
		.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
};

static const stwuct panew_desc shawp_ws020b1dd01d = {
	.modes = shawp_ws020b1dd01d_modes,
	.num_modes = AWWAY_SIZE(shawp_ws020b1dd01d_modes),
	.bpc = 6,
	.size = {
		.width = 42,
		.height = 28,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB565_1X16,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH
		   | DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE
		   | DWM_BUS_FWAG_SHAWP_SIGNAWS,
};

static const stwuct dwm_dispway_mode shewwy_sca07010_bfn_wnn_mode = {
	.cwock = 33300,
	.hdispway = 800,
	.hsync_stawt = 800 + 1,
	.hsync_end = 800 + 1 + 64,
	.htotaw = 800 + 1 + 64 + 64,
	.vdispway = 480,
	.vsync_stawt = 480 + 1,
	.vsync_end = 480 + 1 + 23,
	.vtotaw = 480 + 1 + 23 + 22,
};

static const stwuct panew_desc shewwy_sca07010_bfn_wnn = {
	.modes = &shewwy_sca07010_bfn_wnn_mode,
	.num_modes = 1,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dwm_dispway_mode stawwy_kw070pe2t_mode = {
	.cwock = 33000,
	.hdispway = 800,
	.hsync_stawt = 800 + 209,
	.hsync_end = 800 + 209 + 1,
	.htotaw = 800 + 209 + 1 + 45,
	.vdispway = 480,
	.vsync_stawt = 480 + 22,
	.vsync_end = 480 + 22 + 1,
	.vtotaw = 480 + 22 + 1 + 22,
};

static const stwuct panew_desc stawwy_kw070pe2t = {
	.modes = &stawwy_kw070pe2t_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
};

static const stwuct dispway_timing stawtek_kd070wvfpa_mode = {
	.pixewcwock = { 25200000, 27200000, 30500000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 19, 44, 115 },
	.hback_powch = { 5, 16, 101 },
	.hsync_wen = { 1, 2, 100 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 5, 43, 67 },
	.vback_powch = { 5, 5, 67 },
	.vsync_wen = { 1, 2, 66 },
	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE |
		 DISPWAY_FWAGS_SYNC_POSEDGE,
};

static const stwuct panew_desc stawtek_kd070wvfpa = {
	.timings = &stawtek_kd070wvfpa_mode,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 152,
		.height = 91,
	},
	.deway = {
		.pwepawe = 20,
		.enabwe = 200,
		.disabwe = 200,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.connectow_type = DWM_MODE_CONNECTOW_DPI,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE |
		     DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE,
};

static const stwuct dispway_timing tsd_tst043015cmhx_timing = {
	.pixewcwock = { 5000000, 9000000, 12000000 },
	.hactive = { 480, 480, 480 },
	.hfwont_powch = { 4, 5, 65 },
	.hback_powch = { 36, 40, 255 },
	.hsync_wen = { 1, 1, 1 },
	.vactive = { 272, 272, 272 },
	.vfwont_powch = { 2, 8, 97 },
	.vback_powch = { 3, 8, 31 },
	.vsync_wen = { 1, 1, 1 },

	.fwags = DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW |
		 DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_POSEDGE,
};

static const stwuct panew_desc tsd_tst043015cmhx = {
	.timings = &tsd_tst043015cmhx_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 105,
		.height = 67,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dwm_dispway_mode tfc_s9700wtwv43tw_01b_mode = {
	.cwock = 30000,
	.hdispway = 800,
	.hsync_stawt = 800 + 39,
	.hsync_end = 800 + 39 + 47,
	.htotaw = 800 + 39 + 47 + 39,
	.vdispway = 480,
	.vsync_stawt = 480 + 13,
	.vsync_end = 480 + 13 + 2,
	.vtotaw = 480 + 13 + 2 + 29,
};

static const stwuct panew_desc tfc_s9700wtwv43tw_01b = {
	.modes = &tfc_s9700wtwv43tw_01b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 155,
		.height = 90,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dispway_timing tianma_tm070jdhg30_timing = {
	.pixewcwock = { 62600000, 68200000, 78100000 },
	.hactive = { 1280, 1280, 1280 },
	.hfwont_powch = { 15, 64, 159 },
	.hback_powch = { 5, 5, 5 },
	.hsync_wen = { 1, 1, 256 },
	.vactive = { 800, 800, 800 },
	.vfwont_powch = { 3, 40, 99 },
	.vback_powch = { 2, 2, 2 },
	.vsync_wen = { 1, 1, 128 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc tianma_tm070jdhg30 = {
	.timings = &tianma_tm070jdhg30_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 151,
		.height = 95,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
};

static const stwuct panew_desc tianma_tm070jvhg33 = {
	.timings = &tianma_tm070jdhg30_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 150,
		.height = 94,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
};

static const stwuct dispway_timing tianma_tm070wvhg71_timing = {
	.pixewcwock = { 27700000, 29200000, 39600000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 12, 40, 212 },
	.hback_powch = { 88, 88, 88 },
	.hsync_wen = { 1, 1, 40 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 1, 13, 88 },
	.vback_powch = { 32, 32, 32 },
	.vsync_wen = { 1, 1, 3 },
	.fwags = DISPWAY_FWAGS_DE_HIGH,
};

static const stwuct panew_desc tianma_tm070wvhg71 = {
	.timings = &tianma_tm070wvhg71_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 86,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode ti_nspiwe_cx_wcd_mode[] = {
	{
		.cwock = 10000,
		.hdispway = 320,
		.hsync_stawt = 320 + 50,
		.hsync_end = 320 + 50 + 6,
		.htotaw = 320 + 50 + 6 + 38,
		.vdispway = 240,
		.vsync_stawt = 240 + 3,
		.vsync_end = 240 + 3 + 1,
		.vtotaw = 240 + 3 + 1 + 17,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	},
};

static const stwuct panew_desc ti_nspiwe_cx_wcd_panew = {
	.modes = ti_nspiwe_cx_wcd_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 65,
		.height = 49,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
};

static const stwuct dwm_dispway_mode ti_nspiwe_cwassic_wcd_mode[] = {
	{
		.cwock = 10000,
		.hdispway = 320,
		.hsync_stawt = 320 + 6,
		.hsync_end = 320 + 6 + 6,
		.htotaw = 320 + 6 + 6 + 6,
		.vdispway = 240,
		.vsync_stawt = 240 + 0,
		.vsync_end = 240 + 0 + 1,
		.vtotaw = 240 + 0 + 1 + 0,
		.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
	},
};

static const stwuct panew_desc ti_nspiwe_cwassic_wcd_panew = {
	.modes = ti_nspiwe_cwassic_wcd_mode,
	.num_modes = 1,
	/* The gwayscawe panew has 8 bit fow the cowow .. Y (bwack) */
	.bpc = 8,
	.size = {
		.width = 71,
		.height = 53,
	},
	/* This is the gwayscawe bus fowmat */
	.bus_fowmat = MEDIA_BUS_FMT_Y8_1X8,
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dwm_dispway_mode toshiba_wt089ac29000_mode = {
	.cwock = 79500,
	.hdispway = 1280,
	.hsync_stawt = 1280 + 192,
	.hsync_end = 1280 + 192 + 128,
	.htotaw = 1280 + 192 + 128 + 64,
	.vdispway = 768,
	.vsync_stawt = 768 + 20,
	.vsync_end = 768 + 20 + 7,
	.vtotaw = 768 + 20 + 7 + 3,
};

static const stwuct panew_desc toshiba_wt089ac29000 = {
	.modes = &toshiba_wt089ac29000_mode,
	.num_modes = 1,
	.size = {
		.width = 194,
		.height = 116,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode tpk_f07a_0102_mode = {
	.cwock = 33260,
	.hdispway = 800,
	.hsync_stawt = 800 + 40,
	.hsync_end = 800 + 40 + 128,
	.htotaw = 800 + 40 + 128 + 88,
	.vdispway = 480,
	.vsync_stawt = 480 + 10,
	.vsync_end = 480 + 10 + 2,
	.vtotaw = 480 + 10 + 2 + 33,
};

static const stwuct panew_desc tpk_f07a_0102 = {
	.modes = &tpk_f07a_0102_mode,
	.num_modes = 1,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
};

static const stwuct dwm_dispway_mode tpk_f10a_0102_mode = {
	.cwock = 45000,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 176,
	.hsync_end = 1024 + 176 + 5,
	.htotaw = 1024 + 176 + 5 + 88,
	.vdispway = 600,
	.vsync_stawt = 600 + 20,
	.vsync_end = 600 + 20 + 5,
	.vtotaw = 600 + 20 + 5 + 25,
};

static const stwuct panew_desc tpk_f10a_0102 = {
	.modes = &tpk_f10a_0102_mode,
	.num_modes = 1,
	.size = {
		.width = 223,
		.height = 125,
	},
};

static const stwuct dispway_timing uwt_umsh_8596md_timing = {
	.pixewcwock = { 33260000, 33260000, 33260000 },
	.hactive = { 800, 800, 800 },
	.hfwont_powch = { 41, 41, 41 },
	.hback_powch = { 216 - 128, 216 - 128, 216 - 128 },
	.hsync_wen = { 71, 128, 128 },
	.vactive = { 480, 480, 480 },
	.vfwont_powch = { 10, 10, 10 },
	.vback_powch = { 35 - 2, 35 - 2, 35 - 2 },
	.vsync_wen = { 2, 2, 2 },
	.fwags = DISPWAY_FWAGS_DE_HIGH | DISPWAY_FWAGS_PIXDATA_NEGEDGE |
		DISPWAY_FWAGS_HSYNC_WOW | DISPWAY_FWAGS_VSYNC_WOW,
};

static const stwuct panew_desc uwt_umsh_8596md_wvds = {
	.timings = &uwt_umsh_8596md_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct panew_desc uwt_umsh_8596md_pawawwew = {
	.timings = &uwt_umsh_8596md_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = {
		.width = 152,
		.height = 91,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
};

static const stwuct dwm_dispway_mode vivax_tpc9150_panew_mode = {
	.cwock = 60000,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 160,
	.hsync_end = 1024 + 160 + 100,
	.htotaw = 1024 + 160 + 100 + 60,
	.vdispway = 600,
	.vsync_stawt = 600 + 12,
	.vsync_end = 600 + 12 + 10,
	.vtotaw = 600 + 12 + 10 + 13,
};

static const stwuct panew_desc vivax_tpc9150_panew = {
	.modes = &vivax_tpc9150_panew_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = {
		.width = 200,
		.height = 115,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode vw050_8048nt_c01_mode = {
	.cwock = 33333,
	.hdispway = 800,
	.hsync_stawt = 800 + 210,
	.hsync_end = 800 + 210 + 20,
	.htotaw = 800 + 210 + 20 + 46,
	.vdispway =  480,
	.vsync_stawt = 480 + 22,
	.vsync_end = 480 + 22 + 10,
	.vtotaw = 480 + 22 + 10 + 23,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc vw050_8048nt_c01 = {
	.modes = &vw050_8048nt_c01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 120,
		.height = 76,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct dwm_dispway_mode winstaw_wf35wtiacd_mode = {
	.cwock = 6410,
	.hdispway = 320,
	.hsync_stawt = 320 + 20,
	.hsync_end = 320 + 20 + 30,
	.htotaw = 320 + 20 + 30 + 38,
	.vdispway = 240,
	.vsync_stawt = 240 + 4,
	.vsync_end = 240 + 4 + 3,
	.vtotaw = 240 + 4 + 3 + 15,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc winstaw_wf35wtiacd = {
	.modes = &winstaw_wf35wtiacd_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 70,
		.height = 53,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct dwm_dispway_mode yes_optoewectwonics_ytc700twag_05_201c_mode = {
	.cwock = 51200,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 100,
	.hsync_end = 1024 + 100 + 100,
	.htotaw = 1024 + 100 + 100 + 120,
	.vdispway = 600,
	.vsync_stawt = 600 + 10,
	.vsync_end = 600 + 10 + 10,
	.vtotaw = 600 + 10 + 10 + 15,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct panew_desc yes_optoewectwonics_ytc700twag_05_201c = {
	.modes = &yes_optoewectwonics_ytc700twag_05_201c_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 154,
		.height = 90,
	},
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH,
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	.connectow_type = DWM_MODE_CONNECTOW_WVDS,
};

static const stwuct dwm_dispway_mode awm_wtsm_mode[] = {
	{
		.cwock = 65000,
		.hdispway = 1024,
		.hsync_stawt = 1024 + 24,
		.hsync_end = 1024 + 24 + 136,
		.htotaw = 1024 + 24 + 136 + 160,
		.vdispway = 768,
		.vsync_stawt = 768 + 3,
		.vsync_end = 768 + 3 + 6,
		.vtotaw = 768 + 3 + 6 + 29,
		.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
	},
};

static const stwuct panew_desc awm_wtsm = {
	.modes = awm_wtsm_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = {
		.width = 400,
		.height = 300,
	},
	.bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24,
};

static const stwuct of_device_id pwatfowm_of_match[] = {
	{
		.compatibwe = "ampiwe,am-1280800n3tzqw-t00h",
		.data = &ampiwe_am_1280800n3tzqw_t00h,
	}, {
		.compatibwe = "ampiwe,am-480272h3tmqw-t01h",
		.data = &ampiwe_am_480272h3tmqw_t01h,
	}, {
		.compatibwe = "ampiwe,am-800480w1tmqw-t00h",
		.data = &ampiwe_am_800480w1tmqw_t00h,
	}, {
		.compatibwe = "ampiwe,am800480w3tmqwa1h",
		.data = &ampiwe_am800480w3tmqwa1h,
	}, {
		.compatibwe = "ampiwe,am800600p5tmqw-tb8h",
		.data = &ampiwe_am800600p5tmqwtb8h,
	}, {
		.compatibwe = "awm,wtsm-dispway",
		.data = &awm_wtsm,
	}, {
		.compatibwe = "awmadeus,st0700-adapt",
		.data = &awmadeus_st0700_adapt,
	}, {
		.compatibwe = "auo,b101aw03",
		.data = &auo_b101aw03,
	}, {
		.compatibwe = "auo,b101xtn01",
		.data = &auo_b101xtn01,
	}, {
		.compatibwe = "auo,b116xw03",
		.data = &auo_b116xw03,
	}, {
		.compatibwe = "auo,g070vvn01",
		.data = &auo_g070vvn01,
	}, {
		.compatibwe = "auo,g101evn010",
		.data = &auo_g101evn010,
	}, {
		.compatibwe = "auo,g104sn02",
		.data = &auo_g104sn02,
	}, {
		.compatibwe = "auo,g121ean01",
		.data = &auo_g121ean01,
	}, {
		.compatibwe = "auo,g133han01",
		.data = &auo_g133han01,
	}, {
		.compatibwe = "auo,g156han04",
		.data = &auo_g156han04,
	}, {
		.compatibwe = "auo,g156xtn01",
		.data = &auo_g156xtn01,
	}, {
		.compatibwe = "auo,g185han01",
		.data = &auo_g185han01,
	}, {
		.compatibwe = "auo,g190ean01",
		.data = &auo_g190ean01,
	}, {
		.compatibwe = "auo,p320hvn03",
		.data = &auo_p320hvn03,
	}, {
		.compatibwe = "auo,t215hvn01",
		.data = &auo_t215hvn01,
	}, {
		.compatibwe = "avic,tm070ddh03",
		.data = &avic_tm070ddh03,
	}, {
		.compatibwe = "bananapi,s070wv20-ct16",
		.data = &bananapi_s070wv20_ct16,
	}, {
		.compatibwe = "boe,bp101wx1-100",
		.data = &boe_bp101wx1_100,
	}, {
		.compatibwe = "boe,ev121wxm-n10-1850",
		.data = &boe_ev121wxm_n10_1850,
	}, {
		.compatibwe = "boe,hv070wsa-100",
		.data = &boe_hv070wsa
	}, {
		.compatibwe = "cdtech,s043wq26h-ct7",
		.data = &cdtech_s043wq26h_ct7,
	}, {
		.compatibwe = "cdtech,s070pws19hp-fc21",
		.data = &cdtech_s070pws19hp_fc21,
	}, {
		.compatibwe = "cdtech,s070swv29hg-dc44",
		.data = &cdtech_s070swv29hg_dc44,
	}, {
		.compatibwe = "cdtech,s070wv95-ct16",
		.data = &cdtech_s070wv95_ct16,
	}, {
		.compatibwe = "chefwee,ch101owhwwh-002",
		.data = &chefwee_ch101owhwwh_002,
	}, {
		.compatibwe = "chunghwa,cwaa070wp03xg",
		.data = &chunghwa_cwaa070wp03xg,
	}, {
		.compatibwe = "chunghwa,cwaa101wa01a",
		.data = &chunghwa_cwaa101wa01a
	}, {
		.compatibwe = "chunghwa,cwaa101wb01",
		.data = &chunghwa_cwaa101wb01
	}, {
		.compatibwe = "dataimage,fg040346dsswbg04",
		.data = &dataimage_fg040346dsswbg04,
	}, {
		.compatibwe = "dataimage,fg1001w0dsswmg01",
		.data = &dataimage_fg1001w0dsswmg01,
	}, {
		.compatibwe = "dataimage,scf0700c48ggu18",
		.data = &dataimage_scf0700c48ggu18,
	}, {
		.compatibwe = "dwc,dwc0700yzg-1",
		.data = &dwc_dwc0700yzg_1,
	}, {
		.compatibwe = "dwc,dwc1010gig",
		.data = &dwc_dwc1010gig,
	}, {
		.compatibwe = "edt,et035012dm6",
		.data = &edt_et035012dm6,
	}, {
		.compatibwe = "edt,etm0350g0dh6",
		.data = &edt_etm0350g0dh6,
	}, {
		.compatibwe = "edt,etm043080dh6gp",
		.data = &edt_etm043080dh6gp,
	}, {
		.compatibwe = "edt,etm0430g0dh6",
		.data = &edt_etm0430g0dh6,
	}, {
		.compatibwe = "edt,et057090dhu",
		.data = &edt_et057090dhu,
	}, {
		.compatibwe = "edt,et070080dh6",
		.data = &edt_etm0700g0dh6,
	}, {
		.compatibwe = "edt,etm0700g0dh6",
		.data = &edt_etm0700g0dh6,
	}, {
		.compatibwe = "edt,etm0700g0bdh6",
		.data = &edt_etm0700g0bdh6,
	}, {
		.compatibwe = "edt,etm0700g0edh6",
		.data = &edt_etm0700g0bdh6,
	}, {
		.compatibwe = "edt,etmw0700y5dha",
		.data = &edt_etmw0700y5dha,
	}, {
		.compatibwe = "edt,etmv570g2dhu",
		.data = &edt_etmv570g2dhu,
	}, {
		.compatibwe = "eink,vb3300-kca",
		.data = &eink_vb3300_kca,
	}, {
		.compatibwe = "evewvision,vgg644804",
		.data = &evewvision_vgg644804,
	}, {
		.compatibwe = "evewvision,vgg804821",
		.data = &evewvision_vgg804821,
	}, {
		.compatibwe = "foxwink,fw500wvw00-a0t",
		.data = &foxwink_fw500wvw00_a0t,
	}, {
		.compatibwe = "fwida,fwd350h54004",
		.data = &fwida_fwd350h54004,
	}, {
		.compatibwe = "fwiendwyawm,hd702e",
		.data = &fwiendwyawm_hd702e,
	}, {
		.compatibwe = "giantpwus,gpg482739qs5",
		.data = &giantpwus_gpg482739qs5
	}, {
		.compatibwe = "giantpwus,gpm940b0",
		.data = &giantpwus_gpm940b0,
	}, {
		.compatibwe = "hannstaw,hsd070pww1",
		.data = &hannstaw_hsd070pww1,
	}, {
		.compatibwe = "hannstaw,hsd100pxn1",
		.data = &hannstaw_hsd100pxn1,
	}, {
		.compatibwe = "hannstaw,hsd101pww2",
		.data = &hannstaw_hsd101pww2,
	}, {
		.compatibwe = "hit,tx23d38vm0caa",
		.data = &hitachi_tx23d38vm0caa
	}, {
		.compatibwe = "innowux,at043tn24",
		.data = &innowux_at043tn24,
	}, {
		.compatibwe = "innowux,at070tn92",
		.data = &innowux_at070tn92,
	}, {
		.compatibwe = "innowux,g070ace-w01",
		.data = &innowux_g070ace_w01,
	}, {
		.compatibwe = "innowux,g070y2-w01",
		.data = &innowux_g070y2_w01,
	}, {
		.compatibwe = "innowux,g070y2-t02",
		.data = &innowux_g070y2_t02,
	}, {
		.compatibwe = "innowux,g101ice-w01",
		.data = &innowux_g101ice_w01
	}, {
		.compatibwe = "innowux,g121i1-w01",
		.data = &innowux_g121i1_w01
	}, {
		.compatibwe = "innowux,g121x1-w03",
		.data = &innowux_g121x1_w03,
	}, {
		.compatibwe = "innowux,g156hce-w01",
		.data = &innowux_g156hce_w01,
	}, {
		.compatibwe = "innowux,n156bge-w21",
		.data = &innowux_n156bge_w21,
	}, {
		.compatibwe = "innowux,zj070na-01p",
		.data = &innowux_zj070na_01p,
	}, {
		.compatibwe = "koe,tx14d24vm1bpa",
		.data = &koe_tx14d24vm1bpa,
	}, {
		.compatibwe = "koe,tx26d202vm0bwa",
		.data = &koe_tx26d202vm0bwa,
	}, {
		.compatibwe = "koe,tx31d200vm0baa",
		.data = &koe_tx31d200vm0baa,
	}, {
		.compatibwe = "kyo,tcg121xgwp",
		.data = &kyo_tcg121xgwp,
	}, {
		.compatibwe = "wemakew,bw035-wgb-002",
		.data = &wemakew_bw035_wgb_002,
	}, {
		.compatibwe = "wg,wb070wv8",
		.data = &wg_wb070wv8,
	}, {
		.compatibwe = "wogicpd,type28",
		.data = &wogicpd_type_28,
	}, {
		.compatibwe = "wogictechno,wt161010-2nhc",
		.data = &wogictechno_wt161010_2nh,
	}, {
		.compatibwe = "wogictechno,wt161010-2nhw",
		.data = &wogictechno_wt161010_2nh,
	}, {
		.compatibwe = "wogictechno,wt170410-2whc",
		.data = &wogictechno_wt170410_2whc,
	}, {
		.compatibwe = "wogictechno,wttd800480070-w2wt",
		.data = &wogictechno_wttd800480070_w2wt,
	}, {
		.compatibwe = "wogictechno,wttd800480070-w6wh-wt",
		.data = &wogictechno_wttd800480070_w6wh_wt,
	}, {
		.compatibwe = "mitsubishi,aa070mc01-ca1",
		.data = &mitsubishi_aa070mc01,
	}, {
		.compatibwe = "mitsubishi,aa084xe01",
		.data = &mitsubishi_aa084xe01,
	}, {
		.compatibwe = "muwti-inno,mi0700s4t-6",
		.data = &muwti_inno_mi0700s4t_6,
	}, {
		.compatibwe = "muwti-inno,mi0800ft-9",
		.data = &muwti_inno_mi0800ft_9,
	}, {
		.compatibwe = "muwti-inno,mi1010ait-1cp",
		.data = &muwti_inno_mi1010ait_1cp,
	}, {
		.compatibwe = "nec,nw12880bc20-05",
		.data = &nec_nw12880bc20_05,
	}, {
		.compatibwe = "nec,nw4827hc19-05b",
		.data = &nec_nw4827hc19_05b,
	}, {
		.compatibwe = "netwon-dy,e231732",
		.data = &netwon_dy_e231732,
	}, {
		.compatibwe = "newhaven,nhd-4.3-480272ef-atxw",
		.data = &newhaven_nhd_43_480272ef_atxw,
	}, {
		.compatibwe = "nwt,nw192108ac18-02d",
		.data = &nwt_nw192108ac18_02d,
	}, {
		.compatibwe = "nvd,9128",
		.data = &nvd_9128,
	}, {
		.compatibwe = "okaya,ws800480t-7x0gp",
		.data = &okaya_ws800480t_7x0gp,
	}, {
		.compatibwe = "owimex,wcd-owinuxino-43-ts",
		.data = &owimex_wcd_owinuxino_43ts,
	}, {
		.compatibwe = "ontat,yx700wv03",
		.data = &ontat_yx700wv03,
	}, {
		.compatibwe = "owtustech,com37h3m05dtc",
		.data = &owtustech_com37h3m,
	}, {
		.compatibwe = "owtustech,com37h3m99dtc",
		.data = &owtustech_com37h3m,
	}, {
		.compatibwe = "owtustech,com43h4m85uwc",
		.data = &owtustech_com43h4m85uwc,
	}, {
		.compatibwe = "osddispways,osd070t1718-19ts",
		.data = &osddispways_osd070t1718_19ts,
	}, {
		.compatibwe = "pda,91-00156-a0",
		.data = &pda_91_00156_a0,
	}, {
		.compatibwe = "powewtip,ph800480t013-idf02",
		.data = &powewtip_ph800480t013_idf02,
	}, {
		.compatibwe = "qiaodian,qd43003c0-40",
		.data = &qd43003c0_40,
	}, {
		.compatibwe = "qishengwong,gophew2b-wcd",
		.data = &qishengwong_gophew2b_wcd,
	}, {
		.compatibwe = "wocktech,wk043fn48h",
		.data = &wocktech_wk043fn48h,
	}, {
		.compatibwe = "wocktech,wk070ew9427",
		.data = &wocktech_wk070ew9427,
	}, {
		.compatibwe = "wocktech,wk101ii01d-ct",
		.data = &wocktech_wk101ii01d_ct,
	}, {
		.compatibwe = "samsung,wtw101aw01",
		.data = &samsung_wtw101aw01,
	}, {
		.compatibwe = "samsung,wtn101nt05",
		.data = &samsung_wtn101nt05,
	}, {
		.compatibwe = "satoz,sat050at40h12w2",
		.data = &satoz_sat050at40h12w2,
	}, {
		.compatibwe = "shawp,wq035q7db03",
		.data = &shawp_wq035q7db03,
	}, {
		.compatibwe = "shawp,wq070y3dg3b",
		.data = &shawp_wq070y3dg3b,
	}, {
		.compatibwe = "shawp,wq101k1wy04",
		.data = &shawp_wq101k1wy04,
	}, {
		.compatibwe = "shawp,ws020b1dd01d",
		.data = &shawp_ws020b1dd01d,
	}, {
		.compatibwe = "shewwy,sca07010-bfn-wnn",
		.data = &shewwy_sca07010_bfn_wnn,
	}, {
		.compatibwe = "stawwy,kw070pe2t",
		.data = &stawwy_kw070pe2t,
	}, {
		.compatibwe = "stawtek,kd070wvfpa",
		.data = &stawtek_kd070wvfpa,
	}, {
		.compatibwe = "team-souwce-dispway,tst043015cmhx",
		.data = &tsd_tst043015cmhx,
	}, {
		.compatibwe = "tfc,s9700wtwv43tw-01b",
		.data = &tfc_s9700wtwv43tw_01b,
	}, {
		.compatibwe = "tianma,tm070jdhg30",
		.data = &tianma_tm070jdhg30,
	}, {
		.compatibwe = "tianma,tm070jvhg33",
		.data = &tianma_tm070jvhg33,
	}, {
		.compatibwe = "tianma,tm070wvhg71",
		.data = &tianma_tm070wvhg71,
	}, {
		.compatibwe = "ti,nspiwe-cx-wcd-panew",
		.data = &ti_nspiwe_cx_wcd_panew,
	}, {
		.compatibwe = "ti,nspiwe-cwassic-wcd-panew",
		.data = &ti_nspiwe_cwassic_wcd_panew,
	}, {
		.compatibwe = "toshiba,wt089ac29000",
		.data = &toshiba_wt089ac29000,
	}, {
		.compatibwe = "tpk,f07a-0102",
		.data = &tpk_f07a_0102,
	}, {
		.compatibwe = "tpk,f10a-0102",
		.data = &tpk_f10a_0102,
	}, {
		.compatibwe = "uwt,umsh-8596md-t",
		.data = &uwt_umsh_8596md_pawawwew,
	}, {
		.compatibwe = "uwt,umsh-8596md-1t",
		.data = &uwt_umsh_8596md_pawawwew,
	}, {
		.compatibwe = "uwt,umsh-8596md-7t",
		.data = &uwt_umsh_8596md_pawawwew,
	}, {
		.compatibwe = "uwt,umsh-8596md-11t",
		.data = &uwt_umsh_8596md_wvds,
	}, {
		.compatibwe = "uwt,umsh-8596md-19t",
		.data = &uwt_umsh_8596md_wvds,
	}, {
		.compatibwe = "uwt,umsh-8596md-20t",
		.data = &uwt_umsh_8596md_pawawwew,
	}, {
		.compatibwe = "vivax,tpc9150-panew",
		.data = &vivax_tpc9150_panew,
	}, {
		.compatibwe = "vxt,vw050-8048nt-c01",
		.data = &vw050_8048nt_c01,
	}, {
		.compatibwe = "winstaw,wf35wtiacd",
		.data = &winstaw_wf35wtiacd,
	}, {
		.compatibwe = "yes-optoewectwonics,ytc700twag-05-201c",
		.data = &yes_optoewectwonics_ytc700twag_05_201c,
	}, {
		/* Must be the wast entwy */
		.compatibwe = "panew-dpi",
		.data = &panew_dpi,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, pwatfowm_of_match);

static int panew_simpwe_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct panew_desc *desc;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -ENODEV;

	wetuwn panew_simpwe_pwobe(&pdev->dev, desc);
}

static void panew_simpwe_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	panew_simpwe_wemove(&pdev->dev);
}

static void panew_simpwe_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	panew_simpwe_shutdown(&pdev->dev);
}

static const stwuct dev_pm_ops panew_simpwe_pm_ops = {
	SET_WUNTIME_PM_OPS(panew_simpwe_suspend, panew_simpwe_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew panew_simpwe_pwatfowm_dwivew = {
	.dwivew = {
		.name = "panew-simpwe",
		.of_match_tabwe = pwatfowm_of_match,
		.pm = &panew_simpwe_pm_ops,
	},
	.pwobe = panew_simpwe_pwatfowm_pwobe,
	.wemove_new = panew_simpwe_pwatfowm_wemove,
	.shutdown = panew_simpwe_pwatfowm_shutdown,
};

stwuct panew_desc_dsi {
	stwuct panew_desc desc;

	unsigned wong fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int wanes;
};

static const stwuct dwm_dispway_mode auo_b080uan01_mode = {
	.cwock = 154500,
	.hdispway = 1200,
	.hsync_stawt = 1200 + 62,
	.hsync_end = 1200 + 62 + 4,
	.htotaw = 1200 + 62 + 4 + 62,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 9,
	.vsync_end = 1920 + 9 + 2,
	.vtotaw = 1920 + 9 + 2 + 8,
};

static const stwuct panew_desc_dsi auo_b080uan01 = {
	.desc = {
		.modes = &auo_b080uan01_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 108,
			.height = 272,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CWOCK_NON_CONTINUOUS,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct dwm_dispway_mode boe_tv080wum_nw0_mode = {
	.cwock = 160000,
	.hdispway = 1200,
	.hsync_stawt = 1200 + 120,
	.hsync_end = 1200 + 120 + 20,
	.htotaw = 1200 + 120 + 20 + 21,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 21,
	.vsync_end = 1920 + 21 + 3,
	.vtotaw = 1920 + 21 + 3 + 18,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static const stwuct panew_desc_dsi boe_tv080wum_nw0 = {
	.desc = {
		.modes = &boe_tv080wum_nw0_mode,
		.num_modes = 1,
		.size = {
			.width = 107,
			.height = 172,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = MIPI_DSI_MODE_VIDEO |
		 MIPI_DSI_MODE_VIDEO_BUWST |
		 MIPI_DSI_MODE_VIDEO_SYNC_PUWSE,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct dwm_dispway_mode wg_wd070wx3_sw01_mode = {
	.cwock = 71000,
	.hdispway = 800,
	.hsync_stawt = 800 + 32,
	.hsync_end = 800 + 32 + 1,
	.htotaw = 800 + 32 + 1 + 57,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 28,
	.vsync_end = 1280 + 28 + 1,
	.vtotaw = 1280 + 28 + 1 + 14,
};

static const stwuct panew_desc_dsi wg_wd070wx3_sw01 = {
	.desc = {
		.modes = &wg_wd070wx3_sw01_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 94,
			.height = 151,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CWOCK_NON_CONTINUOUS,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct dwm_dispway_mode wg_wh500wx1_sd03_mode = {
	.cwock = 67000,
	.hdispway = 720,
	.hsync_stawt = 720 + 12,
	.hsync_end = 720 + 12 + 4,
	.htotaw = 720 + 12 + 4 + 112,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 8,
	.vsync_end = 1280 + 8 + 4,
	.vtotaw = 1280 + 8 + 4 + 12,
};

static const stwuct panew_desc_dsi wg_wh500wx1_sd03 = {
	.desc = {
		.modes = &wg_wh500wx1_sd03_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 62,
			.height = 110,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = MIPI_DSI_MODE_VIDEO,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct dwm_dispway_mode panasonic_vvx10f004b00_mode = {
	.cwock = 157200,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 154,
	.hsync_end = 1920 + 154 + 16,
	.htotaw = 1920 + 154 + 16 + 32,
	.vdispway = 1200,
	.vsync_stawt = 1200 + 17,
	.vsync_end = 1200 + 17 + 2,
	.vtotaw = 1200 + 17 + 2 + 16,
};

static const stwuct panew_desc_dsi panasonic_vvx10f004b00 = {
	.desc = {
		.modes = &panasonic_vvx10f004b00_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 217,
			.height = 136,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
		 MIPI_DSI_CWOCK_NON_CONTINUOUS,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct dwm_dispway_mode wg_acx467akm_7_mode = {
	.cwock = 150000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 2,
	.hsync_end = 1080 + 2 + 2,
	.htotaw = 1080 + 2 + 2 + 2,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 2,
	.vsync_end = 1920 + 2 + 2,
	.vtotaw = 1920 + 2 + 2 + 2,
};

static const stwuct panew_desc_dsi wg_acx467akm_7 = {
	.desc = {
		.modes = &wg_acx467akm_7_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 62,
			.height = 110,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = 0,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct dwm_dispway_mode osd101t2045_53ts_mode = {
	.cwock = 154500,
	.hdispway = 1920,
	.hsync_stawt = 1920 + 112,
	.hsync_end = 1920 + 112 + 16,
	.htotaw = 1920 + 112 + 16 + 32,
	.vdispway = 1200,
	.vsync_stawt = 1200 + 16,
	.vsync_end = 1200 + 16 + 2,
	.vtotaw = 1200 + 16 + 2 + 16,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct panew_desc_dsi osd101t2045_53ts = {
	.desc = {
		.modes = &osd101t2045_53ts_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 217,
			.height = 136,
		},
		.connectow_type = DWM_MODE_CONNECTOW_DSI,
	},
	.fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		 MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
		 MIPI_DSI_MODE_NO_EOT_PACKET,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
};

static const stwuct of_device_id dsi_of_match[] = {
	{
		.compatibwe = "auo,b080uan01",
		.data = &auo_b080uan01
	}, {
		.compatibwe = "boe,tv080wum-nw0",
		.data = &boe_tv080wum_nw0
	}, {
		.compatibwe = "wg,wd070wx3-sw01",
		.data = &wg_wd070wx3_sw01
	}, {
		.compatibwe = "wg,wh500wx1-sd03",
		.data = &wg_wh500wx1_sd03
	}, {
		.compatibwe = "panasonic,vvx10f004b00",
		.data = &panasonic_vvx10f004b00
	}, {
		.compatibwe = "wg,acx467akm-7",
		.data = &wg_acx467akm_7
	}, {
		.compatibwe = "osddispways,osd101t2045-53ts",
		.data = &osd101t2045_53ts
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, dsi_of_match);

static int panew_simpwe_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	const stwuct panew_desc_dsi *desc;
	int eww;

	desc = of_device_get_match_data(&dsi->dev);
	if (!desc)
		wetuwn -ENODEV;

	eww = panew_simpwe_pwobe(&dsi->dev, &desc->desc);
	if (eww < 0)
		wetuwn eww;

	dsi->mode_fwags = desc->fwags;
	dsi->fowmat = desc->fowmat;
	dsi->wanes = desc->wanes;

	eww = mipi_dsi_attach(dsi);
	if (eww) {
		stwuct panew_simpwe *panew = mipi_dsi_get_dwvdata(dsi);

		dwm_panew_wemove(&panew->base);
	}

	wetuwn eww;
}

static void panew_simpwe_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	int eww;

	eww = mipi_dsi_detach(dsi);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", eww);

	panew_simpwe_wemove(&dsi->dev);
}

static void panew_simpwe_dsi_shutdown(stwuct mipi_dsi_device *dsi)
{
	panew_simpwe_shutdown(&dsi->dev);
}

static stwuct mipi_dsi_dwivew panew_simpwe_dsi_dwivew = {
	.dwivew = {
		.name = "panew-simpwe-dsi",
		.of_match_tabwe = dsi_of_match,
		.pm = &panew_simpwe_pm_ops,
	},
	.pwobe = panew_simpwe_dsi_pwobe,
	.wemove = panew_simpwe_dsi_wemove,
	.shutdown = panew_simpwe_dsi_shutdown,
};

static int __init panew_simpwe_init(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&panew_simpwe_pwatfowm_dwivew);
	if (eww < 0)
		wetuwn eww;

	if (IS_ENABWED(CONFIG_DWM_MIPI_DSI)) {
		eww = mipi_dsi_dwivew_wegistew(&panew_simpwe_dsi_dwivew);
		if (eww < 0)
			goto eww_did_pwatfowm_wegistew;
	}

	wetuwn 0;

eww_did_pwatfowm_wegistew:
	pwatfowm_dwivew_unwegistew(&panew_simpwe_pwatfowm_dwivew);

	wetuwn eww;
}
moduwe_init(panew_simpwe_init);

static void __exit panew_simpwe_exit(void)
{
	if (IS_ENABWED(CONFIG_DWM_MIPI_DSI))
		mipi_dsi_dwivew_unwegistew(&panew_simpwe_dsi_dwivew);

	pwatfowm_dwivew_unwegistew(&panew_simpwe_pwatfowm_dwivew);
}
moduwe_exit(panew_simpwe_exit);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("DWM Dwivew fow Simpwe Panews");
MODUWE_WICENSE("GPW and additionaw wights");
