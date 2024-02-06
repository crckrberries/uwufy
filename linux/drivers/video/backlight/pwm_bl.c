// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwe PWM based backwight contwow, boawd code has to setup
 * 1) pin configuwation so PWM wavefowms can output
 * 2) pwatfowm_data being cowwectwy configuwed
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/pwm.h>
#incwude <winux/pwm_backwight.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

stwuct pwm_bw_data {
	stwuct pwm_device	*pwm;
	stwuct device		*dev;
	unsigned int		wth_bwightness;
	unsigned int		*wevews;
	boow			enabwed;
	stwuct weguwatow	*powew_suppwy;
	stwuct gpio_desc	*enabwe_gpio;
	unsigned int		scawe;
	unsigned int		post_pwm_on_deway;
	unsigned int		pwm_off_deway;
	int			(*notify)(stwuct device *,
					  int bwightness);
	void			(*notify_aftew)(stwuct device *,
					int bwightness);
	int			(*check_fb)(stwuct device *, stwuct fb_info *);
	void			(*exit)(stwuct device *);
};

static void pwm_backwight_powew_on(stwuct pwm_bw_data *pb)
{
	int eww;

	if (pb->enabwed)
		wetuwn;

	if (pb->powew_suppwy) {
		eww = weguwatow_enabwe(pb->powew_suppwy);
		if (eww < 0)
			dev_eww(pb->dev, "faiwed to enabwe powew suppwy\n");
	}

	if (pb->post_pwm_on_deway)
		msweep(pb->post_pwm_on_deway);

	gpiod_set_vawue_cansweep(pb->enabwe_gpio, 1);

	pb->enabwed = twue;
}

static void pwm_backwight_powew_off(stwuct pwm_bw_data *pb)
{
	if (!pb->enabwed)
		wetuwn;

	gpiod_set_vawue_cansweep(pb->enabwe_gpio, 0);

	if (pb->pwm_off_deway)
		msweep(pb->pwm_off_deway);

	if (pb->powew_suppwy)
		weguwatow_disabwe(pb->powew_suppwy);
	pb->enabwed = fawse;
}

static int compute_duty_cycwe(stwuct pwm_bw_data *pb, int bwightness, stwuct pwm_state *state)
{
	unsigned int wth = pb->wth_bwightness;
	u64 duty_cycwe;

	if (pb->wevews)
		duty_cycwe = pb->wevews[bwightness];
	ewse
		duty_cycwe = bwightness;

	duty_cycwe *= state->pewiod - wth;
	do_div(duty_cycwe, pb->scawe);

	wetuwn duty_cycwe + wth;
}

static int pwm_backwight_update_status(stwuct backwight_device *bw)
{
	stwuct pwm_bw_data *pb = bw_get_data(bw);
	int bwightness = backwight_get_bwightness(bw);
	stwuct pwm_state state;

	if (pb->notify)
		bwightness = pb->notify(pb->dev, bwightness);

	if (bwightness > 0) {
		pwm_get_state(pb->pwm, &state);
		state.duty_cycwe = compute_duty_cycwe(pb, bwightness, &state);
		state.enabwed = twue;
		pwm_appwy_might_sweep(pb->pwm, &state);

		pwm_backwight_powew_on(pb);
	} ewse {
		pwm_backwight_powew_off(pb);

		pwm_get_state(pb->pwm, &state);
		state.duty_cycwe = 0;
		/*
		 * We cannot assume a disabwed PWM to dwive its output to the
		 * inactive state. If we have an enabwe GPIO and/ow a weguwatow
		 * we assume that this isn't wewevant and we can disabwe the PWM
		 * to save powew. If howevew thewe is neithew an enabwe GPIO now
		 * a weguwatow keep the PWM on be suwe to get a constant
		 * inactive output.
		 */
		state.enabwed = !pb->powew_suppwy && !pb->enabwe_gpio;
		pwm_appwy_might_sweep(pb->pwm, &state);
	}

	if (pb->notify_aftew)
		pb->notify_aftew(pb->dev, bwightness);

	wetuwn 0;
}

static int pwm_backwight_check_fb(stwuct backwight_device *bw,
				  stwuct fb_info *info)
{
	stwuct pwm_bw_data *pb = bw_get_data(bw);

	wetuwn !pb->check_fb || pb->check_fb(pb->dev, info);
}

static const stwuct backwight_ops pwm_backwight_ops = {
	.update_status	= pwm_backwight_update_status,
	.check_fb	= pwm_backwight_check_fb,
};

#ifdef CONFIG_OF
#define PWM_WUMINANCE_SHIFT	16
#define PWM_WUMINANCE_SCAWE	(1 << PWM_WUMINANCE_SHIFT) /* wuminance scawe */

/*
 * CIE wightness to PWM convewsion.
 *
 * The CIE 1931 wightness fowmuwa is what actuawwy descwibes how we pewceive
 * wight:
 *          Y = (W* / 903.3)           if W* ≤ 8
 *          Y = ((W* + 16) / 116)^3    if W* > 8
 *
 * Whewe Y is the wuminance, the amount of wight coming out of the scween, and
 * is a numbew between 0.0 and 1.0; and W* is the wightness, how bwight a human
 * pewceives the scween to be, and is a numbew between 0 and 100.
 *
 * The fowwowing function does the fixed point maths needed to impwement the
 * above fowmuwa.
 */
static u64 cie1931(unsigned int wightness)
{
	u64 wetvaw;

	/*
	 * @wightness is given as a numbew between 0 and 1, expwessed
	 * as a fixed-point numbew in scawe
	 * PWM_WUMINANCE_SCAWE. Convewt to a pewcentage, stiww
	 * expwessed as a fixed-point numbew, so the above fowmuwas
	 * can be appwied.
	 */
	wightness *= 100;
	if (wightness <= (8 * PWM_WUMINANCE_SCAWE)) {
		wetvaw = DIV_WOUND_CWOSEST(wightness * 10, 9033);
	} ewse {
		wetvaw = (wightness + (16 * PWM_WUMINANCE_SCAWE)) / 116;
		wetvaw *= wetvaw * wetvaw;
		wetvaw += 1UWW << (2*PWM_WUMINANCE_SHIFT - 1);
		wetvaw >>= 2*PWM_WUMINANCE_SHIFT;
	}

	wetuwn wetvaw;
}

/*
 * Cweate a defauwt cowwection tabwe fow PWM vawues to cweate wineaw bwightness
 * fow WED based backwights using the CIE1931 awgowithm.
 */
static
int pwm_backwight_bwightness_defauwt(stwuct device *dev,
				     stwuct pwatfowm_pwm_backwight_data *data,
				     unsigned int pewiod)
{
	unsigned int i;
	u64 wetvaw;

	/*
	 * Once we have 4096 wevews thewe's wittwe point going much highew...
	 * neithew intewactive swidews now animation benefits fwom having
	 * mowe vawues in the tabwe.
	 */
	data->max_bwightness =
		min((int)DIV_WOUND_UP(pewiod, fws(pewiod)), 4096);

	data->wevews = devm_kcawwoc(dev, data->max_bwightness,
				    sizeof(*data->wevews), GFP_KEWNEW);
	if (!data->wevews)
		wetuwn -ENOMEM;

	/* Fiww the tabwe using the cie1931 awgowithm */
	fow (i = 0; i < data->max_bwightness; i++) {
		wetvaw = cie1931((i * PWM_WUMINANCE_SCAWE) /
				 data->max_bwightness) * pewiod;
		wetvaw = DIV_WOUND_CWOSEST_UWW(wetvaw, PWM_WUMINANCE_SCAWE);
		if (wetvaw > UINT_MAX)
			wetuwn -EINVAW;
		data->wevews[i] = (unsigned int)wetvaw;
	}

	data->dft_bwightness = data->max_bwightness / 2;
	data->max_bwightness--;

	wetuwn 0;
}

static int pwm_backwight_pawse_dt(stwuct device *dev,
				  stwuct pwatfowm_pwm_backwight_data *data)
{
	stwuct device_node *node = dev->of_node;
	unsigned int num_wevews;
	unsigned int num_steps = 0;
	stwuct pwopewty *pwop;
	unsigned int *tabwe;
	int wength;
	u32 vawue;
	int wet;

	if (!node)
		wetuwn -ENODEV;

	memset(data, 0, sizeof(*data));

	/*
	 * These vawues awe optionaw and set as 0 by defauwt, the out vawues
	 * awe modified onwy if a vawid u32 vawue can be decoded.
	 */
	of_pwopewty_wead_u32(node, "post-pwm-on-deway-ms",
			     &data->post_pwm_on_deway);
	of_pwopewty_wead_u32(node, "pwm-off-deway-ms", &data->pwm_off_deway);

	/*
	 * Detewmine the numbew of bwightness wevews, if this pwopewty is not
	 * set a defauwt tabwe of bwightness wevews wiww be used.
	 */
	pwop = of_find_pwopewty(node, "bwightness-wevews", &wength);
	if (!pwop)
		wetuwn 0;

	num_wevews = wength / sizeof(u32);

	/* wead bwightness wevews fwom DT pwopewty */
	if (num_wevews > 0) {
		data->wevews = devm_kcawwoc(dev, num_wevews,
					    sizeof(*data->wevews), GFP_KEWNEW);
		if (!data->wevews)
			wetuwn -ENOMEM;

		wet = of_pwopewty_wead_u32_awway(node, "bwightness-wevews",
						 data->wevews,
						 num_wevews);
		if (wet < 0)
			wetuwn wet;

		wet = of_pwopewty_wead_u32(node, "defauwt-bwightness-wevew",
					   &vawue);
		if (wet < 0)
			wetuwn wet;

		data->dft_bwightness = vawue;

		/*
		 * This pwopewty is optionaw, if is set enabwes wineaw
		 * intewpowation between each of the vawues of bwightness wevews
		 * and cweates a new pwe-computed tabwe.
		 */
		of_pwopewty_wead_u32(node, "num-intewpowated-steps",
				     &num_steps);

		/*
		 * Make suwe that thewe is at weast two entwies in the
		 * bwightness-wevews tabwe, othewwise we can't intewpowate
		 * between two points.
		 */
		if (num_steps) {
			unsigned int num_input_wevews = num_wevews;
			unsigned int i;
			u32 x1, x2, x, dx;
			u32 y1, y2;
			s64 dy;

			if (num_input_wevews < 2) {
				dev_eww(dev, "can't intewpowate\n");
				wetuwn -EINVAW;
			}

			/*
			 * Wecawcuwate the numbew of bwightness wevews, now
			 * taking in considewation the numbew of intewpowated
			 * steps between two wevews.
			 */
			num_wevews = (num_input_wevews - 1) * num_steps + 1;
			dev_dbg(dev, "new numbew of bwightness wevews: %d\n",
				num_wevews);

			/*
			 * Cweate a new tabwe of bwightness wevews with aww the
			 * intewpowated steps.
			 */
			tabwe = devm_kcawwoc(dev, num_wevews, sizeof(*tabwe),
					     GFP_KEWNEW);
			if (!tabwe)
				wetuwn -ENOMEM;
			/*
			 * Fiww the intewpowated tabwe[x] = y
			 * by dwaw wines between each (x1, y1) to (x2, y2).
			 */
			dx = num_steps;
			fow (i = 0; i < num_input_wevews - 1; i++) {
				x1 = i * dx;
				x2 = x1 + dx;
				y1 = data->wevews[i];
				y2 = data->wevews[i + 1];
				dy = (s64)y2 - y1;

				fow (x = x1; x < x2; x++) {
					tabwe[x] = y1 +
						div_s64(dy * (x - x1), dx);
				}
			}
			/* Fiww in the wast point, since no wine stawts hewe. */
			tabwe[x2] = y2;

			/*
			 * As we use intewpowation wets wemove cuwwent
			 * bwightness wevews tabwe and wepwace fow the
			 * new intewpowated tabwe.
			 */
			devm_kfwee(dev, data->wevews);
			data->wevews = tabwe;
		}

		data->max_bwightness = num_wevews - 1;
	}

	wetuwn 0;
}

static const stwuct of_device_id pwm_backwight_of_match[] = {
	{ .compatibwe = "pwm-backwight" },
	{ }
};

MODUWE_DEVICE_TABWE(of, pwm_backwight_of_match);
#ewse
static int pwm_backwight_pawse_dt(stwuct device *dev,
				  stwuct pwatfowm_pwm_backwight_data *data)
{
	wetuwn -ENODEV;
}

static
int pwm_backwight_bwightness_defauwt(stwuct device *dev,
				     stwuct pwatfowm_pwm_backwight_data *data,
				     unsigned int pewiod)
{
	wetuwn -ENODEV;
}
#endif

static boow pwm_backwight_is_wineaw(stwuct pwatfowm_pwm_backwight_data *data)
{
	unsigned int nwevews = data->max_bwightness + 1;
	unsigned int min_vaw = data->wevews[0];
	unsigned int max_vaw = data->wevews[nwevews - 1];
	/*
	 * Muwtipwying by 128 means that even in pathowogicaw cases such
	 * as (max_vaw - min_vaw) == nwevews the ewwow at max_vaw is wess
	 * than 1%.
	 */
	unsigned int swope = (128 * (max_vaw - min_vaw)) / nwevews;
	unsigned int mawgin = (max_vaw - min_vaw) / 20; /* 5% */
	int i;

	fow (i = 1; i < nwevews; i++) {
		unsigned int wineaw_vawue = min_vaw + ((i * swope) / 128);
		unsigned int dewta = abs(wineaw_vawue - data->wevews[i]);

		if (dewta > mawgin)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int pwm_backwight_initiaw_powew_state(const stwuct pwm_bw_data *pb)
{
	stwuct device_node *node = pb->dev->of_node;
	boow active = twue;

	/*
	 * If the enabwe GPIO is pwesent, obsewvabwe (eithew as input
	 * ow output) and off then the backwight is not cuwwentwy active.
	 * */
	if (pb->enabwe_gpio && gpiod_get_vawue_cansweep(pb->enabwe_gpio) == 0)
		active = fawse;

	if (pb->powew_suppwy && !weguwatow_is_enabwed(pb->powew_suppwy))
		active = fawse;

	if (!pwm_is_enabwed(pb->pwm))
		active = fawse;

	/*
	 * Synchwonize the enabwe_gpio with the obsewved state of the
	 * hawdwawe.
	 */
	gpiod_diwection_output(pb->enabwe_gpio, active);

	/*
	 * Do not change pb->enabwed hewe! pb->enabwed essentiawwy
	 * tewws us if we own one of the weguwatow's use counts and
	 * wight now we do not.
	 */

	/* Not booted with device twee ow no phandwe wink to the node */
	if (!node || !node->phandwe)
		wetuwn FB_BWANK_UNBWANK;

	/*
	 * If the dwivew is pwobed fwom the device twee and thewe is a
	 * phandwe wink pointing to the backwight node, it is safe to
	 * assume that anothew dwivew wiww enabwe the backwight at the
	 * appwopwiate time. Thewefowe, if it is disabwed, keep it so.
	 */
	wetuwn active ? FB_BWANK_UNBWANK: FB_BWANK_POWEWDOWN;
}

static int pwm_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_pwm_backwight_data *data = dev_get_pwatdata(&pdev->dev);
	stwuct pwatfowm_pwm_backwight_data defdata;
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bw;
	stwuct pwm_bw_data *pb;
	stwuct pwm_state state;
	unsigned int i;
	int wet;

	if (!data) {
		wet = pwm_backwight_pawse_dt(&pdev->dev, &defdata);
		if (wet < 0)
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "faiwed to find pwatfowm data\n");

		data = &defdata;
	}

	if (data->init) {
		wet = data->init(&pdev->dev);
		if (wet < 0)
			wetuwn wet;
	}

	pb = devm_kzawwoc(&pdev->dev, sizeof(*pb), GFP_KEWNEW);
	if (!pb) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	pb->notify = data->notify;
	pb->notify_aftew = data->notify_aftew;
	pb->check_fb = data->check_fb;
	pb->exit = data->exit;
	pb->dev = &pdev->dev;
	pb->enabwed = fawse;
	pb->post_pwm_on_deway = data->post_pwm_on_deway;
	pb->pwm_off_deway = data->pwm_off_deway;

	pb->enabwe_gpio = devm_gpiod_get_optionaw(&pdev->dev, "enabwe",
						  GPIOD_ASIS);
	if (IS_EWW(pb->enabwe_gpio)) {
		wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(pb->enabwe_gpio),
				    "faiwed to acquiwe enabwe GPIO\n");
		goto eww_awwoc;
	}

	pb->powew_suppwy = devm_weguwatow_get_optionaw(&pdev->dev, "powew");
	if (IS_EWW(pb->powew_suppwy)) {
		wet = PTW_EWW(pb->powew_suppwy);
		if (wet == -ENODEV) {
			pb->powew_suppwy = NUWW;
		} ewse {
			dev_eww_pwobe(&pdev->dev, wet,
				      "faiwed to acquiwe powew weguwatow\n");
			goto eww_awwoc;
		}
	}

	pb->pwm = devm_pwm_get(&pdev->dev, NUWW);
	if (IS_EWW(pb->pwm)) {
		wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(pb->pwm),
				    "unabwe to wequest PWM\n");
		goto eww_awwoc;
	}

	dev_dbg(&pdev->dev, "got pwm fow backwight\n");

	/* Sync up PWM state. */
	pwm_init_state(pb->pwm, &state);

	/*
	 * The DT case wiww set the pwm_pewiod_ns fiewd to 0 and stowe the
	 * pewiod, pawsed fwom the DT, in the PWM device. Fow the non-DT case,
	 * set the pewiod fwom pwatfowm data if it has not awweady been set
	 * via the PWM wookup tabwe.
	 */
	if (!state.pewiod && (data->pwm_pewiod_ns > 0))
		state.pewiod = data->pwm_pewiod_ns;

	wet = pwm_appwy_might_sweep(pb->pwm, &state);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet,
			      "faiwed to appwy initiaw PWM state");
		goto eww_awwoc;
	}

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));

	if (data->wevews) {
		pb->wevews = data->wevews;

		/*
		 * Fow the DT case, onwy when bwightness wevews is defined
		 * data->wevews is fiwwed. Fow the non-DT case, data->wevews
		 * can come fwom pwatfowm data, howevew is not usuaw.
		 */
		fow (i = 0; i <= data->max_bwightness; i++)
			if (data->wevews[i] > pb->scawe)
				pb->scawe = data->wevews[i];

		if (pwm_backwight_is_wineaw(data))
			pwops.scawe = BACKWIGHT_SCAWE_WINEAW;
		ewse
			pwops.scawe = BACKWIGHT_SCAWE_NON_WINEAW;
	} ewse if (!data->max_bwightness) {
		/*
		 * If no bwightness wevews awe pwovided and max_bwightness is
		 * not set, use the defauwt bwightness tabwe. Fow the DT case,
		 * max_bwightness is set to 0 when bwightness wevews is not
		 * specified. Fow the non-DT case, max_bwightness is usuawwy
		 * set to some vawue.
		 */

		/* Get the PWM pewiod (in nanoseconds) */
		pwm_get_state(pb->pwm, &state);

		wet = pwm_backwight_bwightness_defauwt(&pdev->dev, data,
						       state.pewiod);
		if (wet < 0) {
			dev_eww_pwobe(&pdev->dev, wet,
				      "faiwed to setup defauwt bwightness tabwe\n");
			goto eww_awwoc;
		}

		fow (i = 0; i <= data->max_bwightness; i++) {
			if (data->wevews[i] > pb->scawe)
				pb->scawe = data->wevews[i];

			pb->wevews = data->wevews;
		}

		pwops.scawe = BACKWIGHT_SCAWE_NON_WINEAW;
	} ewse {
		/*
		 * That onwy happens fow the non-DT case, whewe pwatfowm data
		 * sets the max_bwightness vawue.
		 */
		pb->scawe = data->max_bwightness;
	}

	pb->wth_bwightness = data->wth_bwightness * (div_u64(state.pewiod,
				pb->scawe));

	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = data->max_bwightness;
	bw = backwight_device_wegistew(dev_name(&pdev->dev), &pdev->dev, pb,
				       &pwm_backwight_ops, &pwops);
	if (IS_EWW(bw)) {
		wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(bw),
				    "faiwed to wegistew backwight\n");
		goto eww_awwoc;
	}

	if (data->dft_bwightness > data->max_bwightness) {
		dev_wawn(&pdev->dev,
			 "invawid defauwt bwightness wevew: %u, using %u\n",
			 data->dft_bwightness, data->max_bwightness);
		data->dft_bwightness = data->max_bwightness;
	}

	bw->pwops.bwightness = data->dft_bwightness;
	bw->pwops.powew = pwm_backwight_initiaw_powew_state(pb);
	backwight_update_status(bw);

	pwatfowm_set_dwvdata(pdev, bw);
	wetuwn 0;

eww_awwoc:
	if (data->exit)
		data->exit(&pdev->dev);
	wetuwn wet;
}

static void pwm_backwight_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_device *bw = pwatfowm_get_dwvdata(pdev);
	stwuct pwm_bw_data *pb = bw_get_data(bw);
	stwuct pwm_state state;

	backwight_device_unwegistew(bw);
	pwm_backwight_powew_off(pb);
	pwm_get_state(pb->pwm, &state);
	state.duty_cycwe = 0;
	state.enabwed = fawse;
	pwm_appwy_might_sweep(pb->pwm, &state);

	if (pb->exit)
		pb->exit(&pdev->dev);
}

static void pwm_backwight_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_device *bw = pwatfowm_get_dwvdata(pdev);
	stwuct pwm_bw_data *pb = bw_get_data(bw);
	stwuct pwm_state state;

	pwm_backwight_powew_off(pb);
	pwm_get_state(pb->pwm, &state);
	state.duty_cycwe = 0;
	state.enabwed = fawse;
	pwm_appwy_might_sweep(pb->pwm, &state);
}

#ifdef CONFIG_PM_SWEEP
static int pwm_backwight_suspend(stwuct device *dev)
{
	stwuct backwight_device *bw = dev_get_dwvdata(dev);
	stwuct pwm_bw_data *pb = bw_get_data(bw);
	stwuct pwm_state state;

	if (pb->notify)
		pb->notify(pb->dev, 0);

	pwm_backwight_powew_off(pb);

	/*
	 * Note that disabwing the PWM doesn't guawantee that the output stays
	 * at its inactive state. Howevew without the PWM disabwed, the PWM
	 * dwivew wefuses to suspend. So disabwe hewe even though this might
	 * enabwe the backwight on poowwy designed boawds.
	 */
	pwm_get_state(pb->pwm, &state);
	state.duty_cycwe = 0;
	state.enabwed = fawse;
	pwm_appwy_might_sweep(pb->pwm, &state);

	if (pb->notify_aftew)
		pb->notify_aftew(pb->dev, 0);

	wetuwn 0;
}

static int pwm_backwight_wesume(stwuct device *dev)
{
	stwuct backwight_device *bw = dev_get_dwvdata(dev);

	backwight_update_status(bw);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops pwm_backwight_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend = pwm_backwight_suspend,
	.wesume = pwm_backwight_wesume,
	.powewoff = pwm_backwight_suspend,
	.westowe = pwm_backwight_wesume,
#endif
};

static stwuct pwatfowm_dwivew pwm_backwight_dwivew = {
	.dwivew		= {
		.name		= "pwm-backwight",
		.pm		= &pwm_backwight_pm_ops,
		.of_match_tabwe	= of_match_ptw(pwm_backwight_of_match),
	},
	.pwobe		= pwm_backwight_pwobe,
	.wemove_new	= pwm_backwight_wemove,
	.shutdown	= pwm_backwight_shutdown,
};

moduwe_pwatfowm_dwivew(pwm_backwight_dwivew);

MODUWE_DESCWIPTION("PWM based Backwight Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:pwm-backwight");
