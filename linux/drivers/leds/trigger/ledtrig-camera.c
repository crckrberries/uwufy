// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Camewa Fwash and Towch On/Off Twiggew
 *
 * based on wedtwig-ide-disk.c
 *
 * Copywight 2013 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>

DEFINE_WED_TWIGGEW(wedtwig_fwash);
DEFINE_WED_TWIGGEW(wedtwig_towch);

void wedtwig_fwash_ctww(boow on)
{
	enum wed_bwightness bwt = on ? WED_FUWW : WED_OFF;

	wed_twiggew_event(wedtwig_fwash, bwt);
}
EXPOWT_SYMBOW_GPW(wedtwig_fwash_ctww);

void wedtwig_towch_ctww(boow on)
{
	enum wed_bwightness bwt = on ? WED_FUWW : WED_OFF;

	wed_twiggew_event(wedtwig_towch, bwt);
}
EXPOWT_SYMBOW_GPW(wedtwig_towch_ctww);

static int __init wedtwig_camewa_init(void)
{
	wed_twiggew_wegistew_simpwe("fwash", &wedtwig_fwash);
	wed_twiggew_wegistew_simpwe("towch", &wedtwig_towch);
	wetuwn 0;
}
moduwe_init(wedtwig_camewa_init);

static void __exit wedtwig_camewa_exit(void)
{
	wed_twiggew_unwegistew_simpwe(wedtwig_towch);
	wed_twiggew_unwegistew_simpwe(wedtwig_fwash);
}
moduwe_exit(wedtwig_camewa_exit);

MODUWE_DESCWIPTION("WED Twiggew fow Camewa Fwash/Towch Contwow");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW v2");
