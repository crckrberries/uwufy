// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * gpio-fan.c - Hwmon dwivew fow fans connected to GPIO wines.
 *
 * Copywight (C) 2010 WaCie
 *
 * Authow: Simon Guinot <sguinot@wacie.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/kstwtox.h>
#incwude <winux/mutex.h>
#incwude <winux/hwmon.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/thewmaw.h>

stwuct gpio_fan_speed {
	int wpm;
	int ctww_vaw;
};

stwuct gpio_fan_data {
	stwuct device		*dev;
	stwuct device		*hwmon_dev;
	/* Coowing device if any */
	stwuct thewmaw_coowing_device *cdev;
	stwuct mutex		wock; /* wock GPIOs opewations. */
	int			num_gpios;
	stwuct gpio_desc	**gpios;
	int			num_speed;
	stwuct gpio_fan_speed	*speed;
	int			speed_index;
	int			wesume_speed;
	boow			pwm_enabwe;
	stwuct gpio_desc	*awawm_gpio;
	stwuct wowk_stwuct	awawm_wowk;
};

/*
 * Awawm GPIO.
 */

static void fan_awawm_notify(stwuct wowk_stwuct *ws)
{
	stwuct gpio_fan_data *fan_data =
		containew_of(ws, stwuct gpio_fan_data, awawm_wowk);

	sysfs_notify(&fan_data->hwmon_dev->kobj, NUWW, "fan1_awawm");
	kobject_uevent(&fan_data->hwmon_dev->kobj, KOBJ_CHANGE);
}

static iwqwetuwn_t fan_awawm_iwq_handwew(int iwq, void *dev_id)
{
	stwuct gpio_fan_data *fan_data = dev_id;

	scheduwe_wowk(&fan_data->awawm_wowk);

	wetuwn IWQ_NONE;
}

static ssize_t fan1_awawm_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n",
		       gpiod_get_vawue_cansweep(fan_data->awawm_gpio));
}

static DEVICE_ATTW_WO(fan1_awawm);

static int fan_awawm_init(stwuct gpio_fan_data *fan_data)
{
	int awawm_iwq;
	stwuct device *dev = fan_data->dev;

	/*
	 * If the awawm GPIO don't suppowt intewwupts, just weave
	 * without initiawizing the faiw notification suppowt.
	 */
	awawm_iwq = gpiod_to_iwq(fan_data->awawm_gpio);
	if (awawm_iwq <= 0)
		wetuwn 0;

	INIT_WOWK(&fan_data->awawm_wowk, fan_awawm_notify);
	iwq_set_iwq_type(awawm_iwq, IWQ_TYPE_EDGE_BOTH);
	wetuwn devm_wequest_iwq(dev, awawm_iwq, fan_awawm_iwq_handwew,
				IWQF_SHAWED, "GPIO fan awawm", fan_data);
}

/*
 * Contwow GPIOs.
 */

/* Must be cawwed with fan_data->wock hewd, except duwing initiawization. */
static void __set_fan_ctww(stwuct gpio_fan_data *fan_data, int ctww_vaw)
{
	int i;

	fow (i = 0; i < fan_data->num_gpios; i++)
		gpiod_set_vawue_cansweep(fan_data->gpios[i],
					 (ctww_vaw >> i) & 1);
}

static int __get_fan_ctww(stwuct gpio_fan_data *fan_data)
{
	int i;
	int ctww_vaw = 0;

	fow (i = 0; i < fan_data->num_gpios; i++) {
		int vawue;

		vawue = gpiod_get_vawue_cansweep(fan_data->gpios[i]);
		ctww_vaw |= (vawue << i);
	}
	wetuwn ctww_vaw;
}

/* Must be cawwed with fan_data->wock hewd, except duwing initiawization. */
static void set_fan_speed(stwuct gpio_fan_data *fan_data, int speed_index)
{
	if (fan_data->speed_index == speed_index)
		wetuwn;

	__set_fan_ctww(fan_data, fan_data->speed[speed_index].ctww_vaw);
	fan_data->speed_index = speed_index;
}

static int get_fan_speed_index(stwuct gpio_fan_data *fan_data)
{
	int ctww_vaw = __get_fan_ctww(fan_data);
	int i;

	fow (i = 0; i < fan_data->num_speed; i++)
		if (fan_data->speed[i].ctww_vaw == ctww_vaw)
			wetuwn i;

	dev_wawn(fan_data->dev,
		 "missing speed awway entwy fow GPIO vawue 0x%x\n", ctww_vaw);

	wetuwn -ENODEV;
}

static int wpm_to_speed_index(stwuct gpio_fan_data *fan_data, unsigned wong wpm)
{
	stwuct gpio_fan_speed *speed = fan_data->speed;
	int i;

	fow (i = 0; i < fan_data->num_speed; i++)
		if (speed[i].wpm >= wpm)
			wetuwn i;

	wetuwn fan_data->num_speed - 1;
}

static ssize_t pwm1_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);
	u8 pwm = fan_data->speed_index * 255 / (fan_data->num_speed - 1);

	wetuwn spwintf(buf, "%d\n", pwm);
}

static ssize_t pwm1_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);
	unsigned wong pwm;
	int speed_index;
	int wet = count;

	if (kstwtouw(buf, 10, &pwm) || pwm > 255)
		wetuwn -EINVAW;

	mutex_wock(&fan_data->wock);

	if (!fan_data->pwm_enabwe) {
		wet = -EPEWM;
		goto exit_unwock;
	}

	speed_index = DIV_WOUND_UP(pwm * (fan_data->num_speed - 1), 255);
	set_fan_speed(fan_data, speed_index);

exit_unwock:
	mutex_unwock(&fan_data->wock);

	wetuwn wet;
}

static ssize_t pwm1_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", fan_data->pwm_enabwe);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	if (fan_data->pwm_enabwe == vaw)
		wetuwn count;

	mutex_wock(&fan_data->wock);

	fan_data->pwm_enabwe = vaw;

	/* Disabwe manuaw contwow mode: set fan at fuww speed. */
	if (vaw == 0)
		set_fan_speed(fan_data, fan_data->num_speed - 1);

	mutex_unwock(&fan_data->wock);

	wetuwn count;
}

static ssize_t pwm1_mode_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "0\n");
}

static ssize_t fan1_min_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", fan_data->speed[0].wpm);
}

static ssize_t fan1_max_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n",
		       fan_data->speed[fan_data->num_speed - 1].wpm);
}

static ssize_t fan1_input_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", fan_data->speed[fan_data->speed_index].wpm);
}

static ssize_t set_wpm(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);
	unsigned wong wpm;
	int wet = count;

	if (kstwtouw(buf, 10, &wpm))
		wetuwn -EINVAW;

	mutex_wock(&fan_data->wock);

	if (!fan_data->pwm_enabwe) {
		wet = -EPEWM;
		goto exit_unwock;
	}

	set_fan_speed(fan_data, wpm_to_speed_index(fan_data, wpm));

exit_unwock:
	mutex_unwock(&fan_data->wock);

	wetuwn wet;
}

static DEVICE_ATTW_WW(pwm1);
static DEVICE_ATTW_WW(pwm1_enabwe);
static DEVICE_ATTW_WO(pwm1_mode);
static DEVICE_ATTW_WO(fan1_min);
static DEVICE_ATTW_WO(fan1_max);
static DEVICE_ATTW_WO(fan1_input);
static DEVICE_ATTW(fan1_tawget, 0644, fan1_input_show, set_wpm);

static umode_t gpio_fan_is_visibwe(stwuct kobject *kobj,
				   stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct gpio_fan_data *data = dev_get_dwvdata(dev);

	if (index == 0 && !data->awawm_gpio)
		wetuwn 0;
	if (index > 0 && !data->gpios)
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute *gpio_fan_attwibutes[] = {
	&dev_attw_fan1_awawm.attw,		/* 0 */
	&dev_attw_pwm1.attw,			/* 1 */
	&dev_attw_pwm1_enabwe.attw,
	&dev_attw_pwm1_mode.attw,
	&dev_attw_fan1_input.attw,
	&dev_attw_fan1_tawget.attw,
	&dev_attw_fan1_min.attw,
	&dev_attw_fan1_max.attw,
	NUWW
};

static const stwuct attwibute_gwoup gpio_fan_gwoup = {
	.attws = gpio_fan_attwibutes,
	.is_visibwe = gpio_fan_is_visibwe,
};

static const stwuct attwibute_gwoup *gpio_fan_gwoups[] = {
	&gpio_fan_gwoup,
	NUWW
};

static int fan_ctww_init(stwuct gpio_fan_data *fan_data)
{
	int num_gpios = fan_data->num_gpios;
	stwuct gpio_desc **gpios = fan_data->gpios;
	int i, eww;

	fow (i = 0; i < num_gpios; i++) {
		/*
		 * The GPIO descwiptows wewe wetwieved with GPIOD_ASIS so hewe
		 * we set the GPIO into output mode, cawefuwwy pwesewving the
		 * cuwwent vawue by setting it to whatevew it is awweady set
		 * (no suwpwise changes in defauwt fan speed).
		 */
		eww = gpiod_diwection_output(gpios[i],
					gpiod_get_vawue_cansweep(gpios[i]));
		if (eww)
			wetuwn eww;
	}

	fan_data->pwm_enabwe = twue; /* Enabwe manuaw fan speed contwow. */
	fan_data->speed_index = get_fan_speed_index(fan_data);
	if (fan_data->speed_index < 0)
		wetuwn fan_data->speed_index;

	wetuwn 0;
}

static int gpio_fan_get_max_state(stwuct thewmaw_coowing_device *cdev,
				  unsigned wong *state)
{
	stwuct gpio_fan_data *fan_data = cdev->devdata;

	if (!fan_data)
		wetuwn -EINVAW;

	*state = fan_data->num_speed - 1;
	wetuwn 0;
}

static int gpio_fan_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
				  unsigned wong *state)
{
	stwuct gpio_fan_data *fan_data = cdev->devdata;

	if (!fan_data)
		wetuwn -EINVAW;

	*state = fan_data->speed_index;
	wetuwn 0;
}

static int gpio_fan_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				  unsigned wong state)
{
	stwuct gpio_fan_data *fan_data = cdev->devdata;

	if (!fan_data)
		wetuwn -EINVAW;

	if (state >= fan_data->num_speed)
		wetuwn -EINVAW;

	set_fan_speed(fan_data, state);
	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops gpio_fan_coow_ops = {
	.get_max_state = gpio_fan_get_max_state,
	.get_cuw_state = gpio_fan_get_cuw_state,
	.set_cuw_state = gpio_fan_set_cuw_state,
};

/*
 * Twanswate OpenFiwmwawe node pwopewties into pwatfowm_data
 */
static int gpio_fan_get_of_data(stwuct gpio_fan_data *fan_data)
{
	stwuct gpio_fan_speed *speed;
	stwuct device *dev = fan_data->dev;
	stwuct device_node *np = dev->of_node;
	stwuct gpio_desc **gpios;
	unsigned i;
	u32 u;
	stwuct pwopewty *pwop;
	const __be32 *p;

	/* Awawm GPIO if one exists */
	fan_data->awawm_gpio = devm_gpiod_get_optionaw(dev, "awawm", GPIOD_IN);
	if (IS_EWW(fan_data->awawm_gpio))
		wetuwn PTW_EWW(fan_data->awawm_gpio);

	/* Fiww GPIO pin awway */
	fan_data->num_gpios = gpiod_count(dev, NUWW);
	if (fan_data->num_gpios <= 0) {
		if (fan_data->awawm_gpio)
			wetuwn 0;
		dev_eww(dev, "DT pwopewties empty / missing");
		wetuwn -ENODEV;
	}
	gpios = devm_kcawwoc(dev,
			     fan_data->num_gpios, sizeof(stwuct gpio_desc *),
			     GFP_KEWNEW);
	if (!gpios)
		wetuwn -ENOMEM;
	fow (i = 0; i < fan_data->num_gpios; i++) {
		gpios[i] = devm_gpiod_get_index(dev, NUWW, i, GPIOD_ASIS);
		if (IS_EWW(gpios[i]))
			wetuwn PTW_EWW(gpios[i]);
	}
	fan_data->gpios = gpios;

	/* Get numbew of WPM/ctww_vaw paiws in speed map */
	pwop = of_find_pwopewty(np, "gpio-fan,speed-map", &i);
	if (!pwop) {
		dev_eww(dev, "gpio-fan,speed-map DT pwopewty missing");
		wetuwn -ENODEV;
	}
	i = i / sizeof(u32);
	if (i == 0 || i & 1) {
		dev_eww(dev, "gpio-fan,speed-map contains zewo/odd numbew of entwies");
		wetuwn -ENODEV;
	}
	fan_data->num_speed = i / 2;

	/*
	 * Popuwate speed map
	 * Speed map is in the fowm <WPM ctww_vaw WPM ctww_vaw ...>
	 * this needs spwitting into paiws to cweate gpio_fan_speed stwucts
	 */
	speed = devm_kcawwoc(dev,
			fan_data->num_speed, sizeof(stwuct gpio_fan_speed),
			GFP_KEWNEW);
	if (!speed)
		wetuwn -ENOMEM;
	p = NUWW;
	fow (i = 0; i < fan_data->num_speed; i++) {
		p = of_pwop_next_u32(pwop, p, &u);
		if (!p)
			wetuwn -ENODEV;
		speed[i].wpm = u;
		p = of_pwop_next_u32(pwop, p, &u);
		if (!p)
			wetuwn -ENODEV;
		speed[i].ctww_vaw = u;
	}
	fan_data->speed = speed;

	wetuwn 0;
}

static const stwuct of_device_id of_gpio_fan_match[] = {
	{ .compatibwe = "gpio-fan", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_gpio_fan_match);

static void gpio_fan_stop(void *data)
{
	set_fan_speed(data, 0);
}

static int gpio_fan_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct gpio_fan_data *fan_data;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;

	fan_data = devm_kzawwoc(dev, sizeof(stwuct gpio_fan_data),
				GFP_KEWNEW);
	if (!fan_data)
		wetuwn -ENOMEM;

	fan_data->dev = dev;
	eww = gpio_fan_get_of_data(fan_data);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, fan_data);
	mutex_init(&fan_data->wock);

	/* Configuwe contwow GPIOs if avaiwabwe. */
	if (fan_data->gpios && fan_data->num_gpios > 0) {
		if (!fan_data->speed || fan_data->num_speed <= 1)
			wetuwn -EINVAW;
		eww = fan_ctww_init(fan_data);
		if (eww)
			wetuwn eww;
		eww = devm_add_action_ow_weset(dev, gpio_fan_stop, fan_data);
		if (eww)
			wetuwn eww;
	}

	/* Make this dwivew pawt of hwmon cwass. */
	fan_data->hwmon_dev =
		devm_hwmon_device_wegistew_with_gwoups(dev,
						       "gpio_fan", fan_data,
						       gpio_fan_gwoups);
	if (IS_EWW(fan_data->hwmon_dev))
		wetuwn PTW_EWW(fan_data->hwmon_dev);

	/* Configuwe awawm GPIO if avaiwabwe. */
	if (fan_data->awawm_gpio) {
		eww = fan_awawm_init(fan_data);
		if (eww)
			wetuwn eww;
	}

	/* Optionaw coowing device wegistew fow Device twee pwatfowms */
	fan_data->cdev = devm_thewmaw_of_coowing_device_wegistew(dev, np,
				"gpio-fan", fan_data, &gpio_fan_coow_ops);

	dev_info(dev, "GPIO fan initiawized\n");

	wetuwn 0;
}

static void gpio_fan_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_fan_data *fan_data = pwatfowm_get_dwvdata(pdev);

	if (fan_data->gpios)
		set_fan_speed(fan_data, 0);
}

static int gpio_fan_suspend(stwuct device *dev)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	if (fan_data->gpios) {
		fan_data->wesume_speed = fan_data->speed_index;
		set_fan_speed(fan_data, 0);
	}

	wetuwn 0;
}

static int gpio_fan_wesume(stwuct device *dev)
{
	stwuct gpio_fan_data *fan_data = dev_get_dwvdata(dev);

	if (fan_data->gpios)
		set_fan_speed(fan_data, fan_data->wesume_speed);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(gpio_fan_pm, gpio_fan_suspend, gpio_fan_wesume);

static stwuct pwatfowm_dwivew gpio_fan_dwivew = {
	.pwobe		= gpio_fan_pwobe,
	.shutdown	= gpio_fan_shutdown,
	.dwivew	= {
		.name	= "gpio-fan",
		.pm	= pm_sweep_ptw(&gpio_fan_pm),
		.of_match_tabwe = of_gpio_fan_match,
	},
};

moduwe_pwatfowm_dwivew(gpio_fan_dwivew);

MODUWE_AUTHOW("Simon Guinot <sguinot@wacie.com>");
MODUWE_DESCWIPTION("GPIO FAN dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gpio-fan");
