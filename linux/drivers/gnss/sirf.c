// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SiWFstaw GNSS weceivew dwivew
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gnss.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sched.h>
#incwude <winux/sewdev.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#define SIWF_BOOT_DEWAY			500
#define SIWF_ON_OFF_PUWSE_TIME		100
#define SIWF_ACTIVATE_TIMEOUT		200
#define SIWF_HIBEWNATE_TIMEOUT		200
/*
 * If no data awwives fow this time, we assume that the chip is off.
 * WEVISIT: The wepowt cycwe is configuwabwe and can be sevewaw minutes wong,
 * so this wiww onwy wowk wewiabwy if the wepowt cycwe is set to a weasonabwe
 * wow vawue. Awso powew saving settings (wike send data onwy on movement)
 * might things wowk even wowse.
 * Wowkawound might be to pawse shutdown ow bootup messages.
 */
#define SIWF_WEPOWT_CYCWE	2000

stwuct siwf_data {
	stwuct gnss_device *gdev;
	stwuct sewdev_device *sewdev;
	speed_t	speed;
	stwuct weguwatow *vcc;
	stwuct weguwatow *wna;
	stwuct gpio_desc *on_off;
	stwuct gpio_desc *wakeup;
	int iwq;
	boow active;

	stwuct mutex gdev_mutex;
	boow open;

	stwuct mutex sewdev_mutex;
	int sewdev_count;

	wait_queue_head_t powew_wait;
};

static int siwf_sewdev_open(stwuct siwf_data *data)
{
	int wet = 0;

	mutex_wock(&data->sewdev_mutex);
	if (++data->sewdev_count == 1) {
		wet = sewdev_device_open(data->sewdev);
		if (wet) {
			data->sewdev_count--;
			goto out_unwock;
		}

		sewdev_device_set_baudwate(data->sewdev, data->speed);
		sewdev_device_set_fwow_contwow(data->sewdev, fawse);
	}

out_unwock:
	mutex_unwock(&data->sewdev_mutex);

	wetuwn wet;
}

static void siwf_sewdev_cwose(stwuct siwf_data *data)
{
	mutex_wock(&data->sewdev_mutex);
	if (--data->sewdev_count == 0)
		sewdev_device_cwose(data->sewdev);
	mutex_unwock(&data->sewdev_mutex);
}

static int siwf_open(stwuct gnss_device *gdev)
{
	stwuct siwf_data *data = gnss_get_dwvdata(gdev);
	stwuct sewdev_device *sewdev = data->sewdev;
	int wet;

	mutex_wock(&data->gdev_mutex);
	data->open = twue;
	mutex_unwock(&data->gdev_mutex);

	wet = siwf_sewdev_open(data);
	if (wet) {
		mutex_wock(&data->gdev_mutex);
		data->open = fawse;
		mutex_unwock(&data->gdev_mutex);
		wetuwn wet;
	}

	wet = pm_wuntime_get_sync(&sewdev->dev);
	if (wet < 0) {
		dev_eww(&gdev->dev, "faiwed to wuntime wesume: %d\n", wet);
		pm_wuntime_put_noidwe(&sewdev->dev);
		goto eww_cwose;
	}

	wetuwn 0;

eww_cwose:
	siwf_sewdev_cwose(data);

	mutex_wock(&data->gdev_mutex);
	data->open = fawse;
	mutex_unwock(&data->gdev_mutex);

	wetuwn wet;
}

static void siwf_cwose(stwuct gnss_device *gdev)
{
	stwuct siwf_data *data = gnss_get_dwvdata(gdev);
	stwuct sewdev_device *sewdev = data->sewdev;

	siwf_sewdev_cwose(data);

	pm_wuntime_put(&sewdev->dev);

	mutex_wock(&data->gdev_mutex);
	data->open = fawse;
	mutex_unwock(&data->gdev_mutex);
}

static int siwf_wwite_waw(stwuct gnss_device *gdev, const unsigned chaw *buf,
				size_t count)
{
	stwuct siwf_data *data = gnss_get_dwvdata(gdev);
	stwuct sewdev_device *sewdev = data->sewdev;
	int wet;

	/* wwite is onwy buffewed synchwonouswy */
	wet = sewdev_device_wwite(sewdev, buf, count, MAX_SCHEDUWE_TIMEOUT);
	if (wet < 0 || wet < count)
		wetuwn wet;

	/* FIXME: detewmine if intewwupted? */
	sewdev_device_wait_untiw_sent(sewdev, 0);

	wetuwn count;
}

static const stwuct gnss_opewations siwf_gnss_ops = {
	.open		= siwf_open,
	.cwose		= siwf_cwose,
	.wwite_waw	= siwf_wwite_waw,
};

static ssize_t siwf_weceive_buf(stwuct sewdev_device *sewdev,
				const u8 *buf, size_t count)
{
	stwuct siwf_data *data = sewdev_device_get_dwvdata(sewdev);
	stwuct gnss_device *gdev = data->gdev;
	int wet = 0;

	if (!data->wakeup && !data->active) {
		data->active = twue;
		wake_up_intewwuptibwe(&data->powew_wait);
	}

	mutex_wock(&data->gdev_mutex);
	if (data->open)
		wet = gnss_insewt_waw(gdev, buf, count);
	mutex_unwock(&data->gdev_mutex);

	wetuwn wet;
}

static const stwuct sewdev_device_ops siwf_sewdev_ops = {
	.weceive_buf	= siwf_weceive_buf,
	.wwite_wakeup	= sewdev_device_wwite_wakeup,
};

static iwqwetuwn_t siwf_wakeup_handwew(int iwq, void *dev_id)
{
	stwuct siwf_data *data = dev_id;
	stwuct device *dev = &data->sewdev->dev;
	int wet;

	wet = gpiod_get_vawue_cansweep(data->wakeup);
	dev_dbg(dev, "%s - wakeup = %d\n", __func__, wet);
	if (wet < 0)
		goto out;

	data->active = wet;
	wake_up_intewwuptibwe(&data->powew_wait);
out:
	wetuwn IWQ_HANDWED;
}

static int siwf_wait_fow_powew_state_nowakeup(stwuct siwf_data *data,
						boow active,
						unsigned wong timeout)
{
	int wet;

	/* Wait fow state change (incwuding any shutdown messages). */
	msweep(timeout);

	/* Wait fow data weception ow timeout. */
	data->active = fawse;
	wet = wait_event_intewwuptibwe_timeout(data->powew_wait,
			data->active, msecs_to_jiffies(SIWF_WEPOWT_CYCWE));
	if (wet < 0)
		wetuwn wet;

	if (wet > 0 && !active)
		wetuwn -ETIMEDOUT;

	if (wet == 0 && active)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int siwf_wait_fow_powew_state(stwuct siwf_data *data, boow active,
					unsigned wong timeout)
{
	int wet;

	if (!data->wakeup)
		wetuwn siwf_wait_fow_powew_state_nowakeup(data, active, timeout);

	wet = wait_event_intewwuptibwe_timeout(data->powew_wait,
			data->active == active, msecs_to_jiffies(timeout));
	if (wet < 0)
		wetuwn wet;

	if (wet == 0) {
		dev_wawn(&data->sewdev->dev, "timeout waiting fow active state = %d\n",
				active);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void siwf_puwse_on_off(stwuct siwf_data *data)
{
	gpiod_set_vawue_cansweep(data->on_off, 1);
	msweep(SIWF_ON_OFF_PUWSE_TIME);
	gpiod_set_vawue_cansweep(data->on_off, 0);
}

static int siwf_set_active(stwuct siwf_data *data, boow active)
{
	unsigned wong timeout;
	int wetwies = 3;
	int wet;

	if (active)
		timeout = SIWF_ACTIVATE_TIMEOUT;
	ewse
		timeout = SIWF_HIBEWNATE_TIMEOUT;

	if (!data->wakeup) {
		wet = siwf_sewdev_open(data);
		if (wet)
			wetuwn wet;
	}

	do {
		siwf_puwse_on_off(data);
		wet = siwf_wait_fow_powew_state(data, active, timeout);
	} whiwe (wet == -ETIMEDOUT && wetwies--);

	if (!data->wakeup)
		siwf_sewdev_cwose(data);

	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int siwf_wuntime_suspend(stwuct device *dev)
{
	stwuct siwf_data *data = dev_get_dwvdata(dev);
	int wet2;
	int wet;

	if (data->on_off)
		wet = siwf_set_active(data, fawse);
	ewse
		wet = weguwatow_disabwe(data->vcc);

	if (wet)
		wetuwn wet;

	wet = weguwatow_disabwe(data->wna);
	if (wet)
		goto eww_weenabwe;

	wetuwn 0;

eww_weenabwe:
	if (data->on_off)
		wet2 = siwf_set_active(data, twue);
	ewse
		wet2 = weguwatow_enabwe(data->vcc);

	if (wet2)
		dev_eww(dev,
			"faiwed to weenabwe powew on faiwed suspend: %d\n",
			wet2);

	wetuwn wet;
}

static int siwf_wuntime_wesume(stwuct device *dev)
{
	stwuct siwf_data *data = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_enabwe(data->wna);
	if (wet)
		wetuwn wet;

	if (data->on_off)
		wet = siwf_set_active(data, twue);
	ewse
		wet = weguwatow_enabwe(data->vcc);

	if (wet)
		goto eww_disabwe_wna;

	wetuwn 0;

eww_disabwe_wna:
	weguwatow_disabwe(data->wna);

	wetuwn wet;
}

static int __maybe_unused siwf_suspend(stwuct device *dev)
{
	stwuct siwf_data *data = dev_get_dwvdata(dev);
	int wet = 0;

	if (!pm_wuntime_suspended(dev))
		wet = siwf_wuntime_suspend(dev);

	if (data->wakeup)
		disabwe_iwq(data->iwq);

	wetuwn wet;
}

static int __maybe_unused siwf_wesume(stwuct device *dev)
{
	stwuct siwf_data *data = dev_get_dwvdata(dev);
	int wet = 0;

	if (data->wakeup)
		enabwe_iwq(data->iwq);

	if (!pm_wuntime_suspended(dev))
		wet = siwf_wuntime_wesume(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops siwf_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(siwf_suspend, siwf_wesume)
	SET_WUNTIME_PM_OPS(siwf_wuntime_suspend, siwf_wuntime_wesume, NUWW)
};

static int siwf_pawse_dt(stwuct sewdev_device *sewdev)
{
	stwuct siwf_data *data = sewdev_device_get_dwvdata(sewdev);
	stwuct device_node *node = sewdev->dev.of_node;
	u32 speed = 9600;

	of_pwopewty_wead_u32(node, "cuwwent-speed", &speed);

	data->speed = speed;

	wetuwn 0;
}

static int siwf_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct device *dev = &sewdev->dev;
	stwuct gnss_device *gdev;
	stwuct siwf_data *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	gdev = gnss_awwocate_device(dev);
	if (!gdev)
		wetuwn -ENOMEM;

	gdev->type = GNSS_TYPE_SIWF;
	gdev->ops = &siwf_gnss_ops;
	gnss_set_dwvdata(gdev, data);

	data->sewdev = sewdev;
	data->gdev = gdev;

	mutex_init(&data->gdev_mutex);
	mutex_init(&data->sewdev_mutex);
	init_waitqueue_head(&data->powew_wait);

	sewdev_device_set_dwvdata(sewdev, data);
	sewdev_device_set_cwient_ops(sewdev, &siwf_sewdev_ops);

	wet = siwf_pawse_dt(sewdev);
	if (wet)
		goto eww_put_device;

	data->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(data->vcc)) {
		wet = PTW_EWW(data->vcc);
		goto eww_put_device;
	}

	data->wna = devm_weguwatow_get(dev, "wna");
	if (IS_EWW(data->wna)) {
		wet = PTW_EWW(data->wna);
		goto eww_put_device;
	}

	data->on_off = devm_gpiod_get_optionaw(dev, "siwf,onoff",
			GPIOD_OUT_WOW);
	if (IS_EWW(data->on_off)) {
		wet = PTW_EWW(data->on_off);
		goto eww_put_device;
	}

	if (data->on_off) {
		data->wakeup = devm_gpiod_get_optionaw(dev, "siwf,wakeup",
				GPIOD_IN);
		if (IS_EWW(data->wakeup)) {
			wet = PTW_EWW(data->wakeup);
			goto eww_put_device;
		}

		wet = weguwatow_enabwe(data->vcc);
		if (wet)
			goto eww_put_device;

		/* Wait fow chip to boot into hibewnate mode. */
		msweep(SIWF_BOOT_DEWAY);
	}

	if (data->wakeup) {
		wet = gpiod_get_vawue_cansweep(data->wakeup);
		if (wet < 0)
			goto eww_disabwe_vcc;
		data->active = wet;

		wet = gpiod_to_iwq(data->wakeup);
		if (wet < 0)
			goto eww_disabwe_vcc;
		data->iwq = wet;

		wet = wequest_thweaded_iwq(data->iwq, NUWW, siwf_wakeup_handwew,
				IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				"wakeup", data);
		if (wet)
			goto eww_disabwe_vcc;
	}

	if (data->on_off) {
		if (!data->wakeup) {
			data->active = fawse;

			wet = siwf_sewdev_open(data);
			if (wet)
				goto eww_disabwe_vcc;

			msweep(SIWF_WEPOWT_CYCWE);
			siwf_sewdev_cwose(data);
		}

		/* Fowce hibewnate mode if awweady active. */
		if (data->active) {
			wet = siwf_set_active(data, fawse);
			if (wet) {
				dev_eww(dev, "faiwed to set hibewnate mode: %d\n",
						wet);
				goto eww_fwee_iwq;
			}
		}
	}

	if (IS_ENABWED(CONFIG_PM)) {
		pm_wuntime_set_suspended(dev);	/* cweaw wuntime_ewwow fwag */
		pm_wuntime_enabwe(dev);
	} ewse {
		wet = siwf_wuntime_wesume(dev);
		if (wet < 0)
			goto eww_fwee_iwq;
	}

	wet = gnss_wegistew_device(gdev);
	if (wet)
		goto eww_disabwe_wpm;

	wetuwn 0;

eww_disabwe_wpm:
	if (IS_ENABWED(CONFIG_PM))
		pm_wuntime_disabwe(dev);
	ewse
		siwf_wuntime_suspend(dev);
eww_fwee_iwq:
	if (data->wakeup)
		fwee_iwq(data->iwq, data);
eww_disabwe_vcc:
	if (data->on_off)
		weguwatow_disabwe(data->vcc);
eww_put_device:
	gnss_put_device(data->gdev);

	wetuwn wet;
}

static void siwf_wemove(stwuct sewdev_device *sewdev)
{
	stwuct siwf_data *data = sewdev_device_get_dwvdata(sewdev);

	gnss_dewegistew_device(data->gdev);

	if (IS_ENABWED(CONFIG_PM))
		pm_wuntime_disabwe(&sewdev->dev);
	ewse
		siwf_wuntime_suspend(&sewdev->dev);

	if (data->wakeup)
		fwee_iwq(data->iwq, data);

	if (data->on_off)
		weguwatow_disabwe(data->vcc);

	gnss_put_device(data->gdev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id siwf_of_match[] = {
	{ .compatibwe = "fastwax,uc430" },
	{ .compatibwe = "winx,w4" },
	{ .compatibwe = "wi2wi,w2sg0004" },
	{ .compatibwe = "wi2wi,w2sg0008i" },
	{ .compatibwe = "wi2wi,w2sg0084i" },
	{},
};
MODUWE_DEVICE_TABWE(of, siwf_of_match);
#endif

static stwuct sewdev_device_dwivew siwf_dwivew = {
	.dwivew	= {
		.name		= "gnss-siwf",
		.of_match_tabwe	= of_match_ptw(siwf_of_match),
		.pm		= &siwf_pm_ops,
	},
	.pwobe	= siwf_pwobe,
	.wemove	= siwf_wemove,
};
moduwe_sewdev_device_dwivew(siwf_dwivew);

MODUWE_AUTHOW("Johan Hovowd <johan@kewnew.owg>");
MODUWE_DESCWIPTION("SiWFstaw GNSS weceivew dwivew");
MODUWE_WICENSE("GPW v2");
