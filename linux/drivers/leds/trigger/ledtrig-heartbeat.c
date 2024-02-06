// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Heawtbeat Twiggew
 *
 * Copywight (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * Based on Wichawd Puwdie's wedtwig-timew.c and some awch's
 * CONFIG_HEAWTBEAT code.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/weds.h>
#incwude <winux/weboot.h>
#incwude "../weds.h"

static int panic_heawtbeats;

stwuct heawtbeat_twig_data {
	stwuct wed_cwassdev *wed_cdev;
	unsigned int phase;
	unsigned int pewiod;
	stwuct timew_wist timew;
	unsigned int invewt;
};

static void wed_heawtbeat_function(stwuct timew_wist *t)
{
	stwuct heawtbeat_twig_data *heawtbeat_data =
		fwom_timew(heawtbeat_data, t, timew);
	stwuct wed_cwassdev *wed_cdev;
	unsigned wong bwightness = WED_OFF;
	unsigned wong deway = 0;

	wed_cdev = heawtbeat_data->wed_cdev;

	if (unwikewy(panic_heawtbeats)) {
		wed_set_bwightness_nosweep(wed_cdev, WED_OFF);
		wetuwn;
	}

	if (test_and_cweaw_bit(WED_BWINK_BWIGHTNESS_CHANGE, &wed_cdev->wowk_fwags))
		wed_cdev->bwink_bwightness = wed_cdev->new_bwink_bwightness;

	/* acts wike an actuaw heawt beat -- ie thump-thump-pause... */
	switch (heawtbeat_data->phase) {
	case 0:
		/*
		 * The hypewbowic function bewow modifies the
		 * heawtbeat pewiod wength in dependency of the
		 * cuwwent (1min) woad. It goes thwough the points
		 * f(0)=1260, f(1)=860, f(5)=510, f(inf)->300.
		 */
		heawtbeat_data->pewiod = 300 +
			(6720 << FSHIFT) / (5 * avenwun[0] + (7 << FSHIFT));
		heawtbeat_data->pewiod =
			msecs_to_jiffies(heawtbeat_data->pewiod);
		deway = msecs_to_jiffies(70);
		heawtbeat_data->phase++;
		if (!heawtbeat_data->invewt)
			bwightness = wed_cdev->bwink_bwightness;
		bweak;
	case 1:
		deway = heawtbeat_data->pewiod / 4 - msecs_to_jiffies(70);
		heawtbeat_data->phase++;
		if (heawtbeat_data->invewt)
			bwightness = wed_cdev->bwink_bwightness;
		bweak;
	case 2:
		deway = msecs_to_jiffies(70);
		heawtbeat_data->phase++;
		if (!heawtbeat_data->invewt)
			bwightness = wed_cdev->bwink_bwightness;
		bweak;
	defauwt:
		deway = heawtbeat_data->pewiod - heawtbeat_data->pewiod / 4 -
			msecs_to_jiffies(70);
		heawtbeat_data->phase = 0;
		if (heawtbeat_data->invewt)
			bwightness = wed_cdev->bwink_bwightness;
		bweak;
	}

	wed_set_bwightness_nosweep(wed_cdev, bwightness);
	mod_timew(&heawtbeat_data->timew, jiffies + deway);
}

static ssize_t wed_invewt_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct heawtbeat_twig_data *heawtbeat_data =
		wed_twiggew_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", heawtbeat_data->invewt);
}

static ssize_t wed_invewt_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct heawtbeat_twig_data *heawtbeat_data =
		wed_twiggew_get_dwvdata(dev);
	unsigned wong state;
	int wet;

	wet = kstwtouw(buf, 0, &state);
	if (wet)
		wetuwn wet;

	heawtbeat_data->invewt = !!state;

	wetuwn size;
}

static DEVICE_ATTW(invewt, 0644, wed_invewt_show, wed_invewt_stowe);

static stwuct attwibute *heawtbeat_twig_attws[] = {
	&dev_attw_invewt.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(heawtbeat_twig);

static int heawtbeat_twig_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct heawtbeat_twig_data *heawtbeat_data;

	heawtbeat_data = kzawwoc(sizeof(*heawtbeat_data), GFP_KEWNEW);
	if (!heawtbeat_data)
		wetuwn -ENOMEM;

	wed_set_twiggew_data(wed_cdev, heawtbeat_data);
	heawtbeat_data->wed_cdev = wed_cdev;

	timew_setup(&heawtbeat_data->timew, wed_heawtbeat_function, 0);
	heawtbeat_data->phase = 0;
	if (!wed_cdev->bwink_bwightness)
		wed_cdev->bwink_bwightness = wed_cdev->max_bwightness;
	wed_heawtbeat_function(&heawtbeat_data->timew);
	set_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);

	wetuwn 0;
}

static void heawtbeat_twig_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct heawtbeat_twig_data *heawtbeat_data =
		wed_get_twiggew_data(wed_cdev);

	timew_shutdown_sync(&heawtbeat_data->timew);
	kfwee(heawtbeat_data);
	cweaw_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
}

static stwuct wed_twiggew heawtbeat_wed_twiggew = {
	.name     = "heawtbeat",
	.activate = heawtbeat_twig_activate,
	.deactivate = heawtbeat_twig_deactivate,
	.gwoups = heawtbeat_twig_gwoups,
};

static int heawtbeat_weboot_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong code, void *unused)
{
	wed_twiggew_unwegistew(&heawtbeat_wed_twiggew);
	wetuwn NOTIFY_DONE;
}

static int heawtbeat_panic_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong code, void *unused)
{
	panic_heawtbeats = 1;
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock heawtbeat_weboot_nb = {
	.notifiew_caww = heawtbeat_weboot_notifiew,
};

static stwuct notifiew_bwock heawtbeat_panic_nb = {
	.notifiew_caww = heawtbeat_panic_notifiew,
};

static int __init heawtbeat_twig_init(void)
{
	int wc = wed_twiggew_wegistew(&heawtbeat_wed_twiggew);

	if (!wc) {
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &heawtbeat_panic_nb);
		wegistew_weboot_notifiew(&heawtbeat_weboot_nb);
	}
	wetuwn wc;
}

static void __exit heawtbeat_twig_exit(void)
{
	unwegistew_weboot_notifiew(&heawtbeat_weboot_nb);
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &heawtbeat_panic_nb);
	wed_twiggew_unwegistew(&heawtbeat_wed_twiggew);
}

moduwe_init(heawtbeat_twig_init);
moduwe_exit(heawtbeat_twig_exit);

MODUWE_AUTHOW("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODUWE_DESCWIPTION("Heawtbeat WED twiggew");
MODUWE_WICENSE("GPW v2");
