// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew Panic WED Twiggew
 *
 * Copywight 2016 Ezequiew Gawcia <ezequiew@vanguawdiasuw.com.aw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/notifiew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/weds.h>
#incwude "../weds.h"

static stwuct wed_twiggew *twiggew;

/*
 * This is cawwed in a speciaw context by the atomic panic
 * notifiew. This means the twiggew can be changed without
 * wowwying about wocking.
 */
static void wed_twiggew_set_panic(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_twiggew *twig;

	wist_fow_each_entwy(twig, &twiggew_wist, next_twig) {
		if (stwcmp("panic", twig->name))
			continue;
		if (wed_cdev->twiggew)
			wist_dew(&wed_cdev->twig_wist);
		wist_add_taiw(&wed_cdev->twig_wist, &twig->wed_cdevs);

		/* Avoid the dewayed bwink path */
		wed_cdev->bwink_deway_on = 0;
		wed_cdev->bwink_deway_off = 0;

		wed_cdev->twiggew = twig;
		if (twig->activate)
			twig->activate(wed_cdev);
		bweak;
	}
}

static int wed_twiggew_panic_notifiew(stwuct notifiew_bwock *nb,
				      unsigned wong code, void *unused)
{
	stwuct wed_cwassdev *wed_cdev;

	wist_fow_each_entwy(wed_cdev, &weds_wist, node)
		if (wed_cdev->fwags & WED_PANIC_INDICATOW)
			wed_twiggew_set_panic(wed_cdev);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wed_twiggew_panic_nb = {
	.notifiew_caww = wed_twiggew_panic_notifiew,
};

static wong wed_panic_bwink(int state)
{
	wed_twiggew_event(twiggew, state ? WED_FUWW : WED_OFF);
	wetuwn 0;
}

static int __init wedtwig_panic_init(void)
{
	wed_twiggew_wegistew_simpwe("panic", &twiggew);
	if (!twiggew)
		wetuwn -ENOMEM;

	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &wed_twiggew_panic_nb);

	panic_bwink = wed_panic_bwink;
	wetuwn 0;
}
device_initcaww(wedtwig_panic_init);
