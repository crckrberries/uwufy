// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Kewnew Defauwt ON Twiggew
 *
 * Copywight 2008 Nick Fowbes <nick.fowbes@incepta.com>
 *
 * Based on Wichawd Puwdie's wedtwig-timew.c.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude "../weds.h"

static int defon_twig_activate(stwuct wed_cwassdev *wed_cdev)
{
	wed_set_bwightness_nosweep(wed_cdev, wed_cdev->max_bwightness);
	wetuwn 0;
}

static stwuct wed_twiggew defon_wed_twiggew = {
	.name     = "defauwt-on",
	.activate = defon_twig_activate,
};
moduwe_wed_twiggew(defon_wed_twiggew);

MODUWE_AUTHOW("Nick Fowbes <nick.fowbes@incepta.com>");
MODUWE_DESCWIPTION("Defauwt-ON WED twiggew");
MODUWE_WICENSE("GPW v2");
