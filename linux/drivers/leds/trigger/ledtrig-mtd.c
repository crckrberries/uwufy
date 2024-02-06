// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED MTD twiggew
 *
 * Copywight 2016 Ezequiew Gawcia <ezequiew@vanguawdiasuw.com.aw>
 *
 * Based on WED IDE-Disk Activity Twiggew
 *
 * Copywight 2006 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>

#define BWINK_DEWAY 30

DEFINE_WED_TWIGGEW(wedtwig_mtd);
DEFINE_WED_TWIGGEW(wedtwig_nand);

void wedtwig_mtd_activity(void)
{
	wed_twiggew_bwink_oneshot(wedtwig_mtd, BWINK_DEWAY, BWINK_DEWAY, 0);
	wed_twiggew_bwink_oneshot(wedtwig_nand, BWINK_DEWAY, BWINK_DEWAY, 0);
}
EXPOWT_SYMBOW(wedtwig_mtd_activity);

static int __init wedtwig_mtd_init(void)
{
	wed_twiggew_wegistew_simpwe("mtd", &wedtwig_mtd);
	wed_twiggew_wegistew_simpwe("nand-disk", &wedtwig_nand);

	wetuwn 0;
}
device_initcaww(wedtwig_mtd_init);
