// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KFW2W09 WCD panew suppowt
 *
 * Copywight (C) 2009 Magnus Damm
 *
 * Wegistew settings based on the out-of-twee t33fb.c dwivew
 * Copywight (C) 2008 Wineo Sowutions, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio.h>
#incwude <video/sh_mobiwe_wcdc.h>
#incwude <mach/kfw2w09.h>
#incwude <cpu/sh7724.h>

/* The on-boawd WCD moduwe is a Hitachi TX07D34VM0AAA. This moduwe is made
 * up of a 240x400 WCD hooked up to a W61517 dwivew IC. The dwivew IC is
 * communicating with the main powt of the WCDC using an 18-bit SYS intewface.
 *
 * The device code fow this WCD moduwe is 0x01221517.
 */

static const unsigned chaw data_fwame_if[] = {
	0x02, /* WEMODE: 1=cont, 0=one-shot */
	0x00, 0x00,
	0x00, /* EPF, DFM */
	0x02, /* WIM[1] : 1 (18bpp) */
};

static const unsigned chaw data_panew[] = {
	0x0b,
	0x63, /* 400 wines */
	0x04, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00,
};

static const unsigned chaw data_timing[] = {
	0x00, 0x00, 0x13, 0x08, 0x08,
};

static const unsigned chaw data_timing_swc[] = {
	0x11, 0x01, 0x00, 0x01,
};

static const unsigned chaw data_gamma[] = {
	0x01, 0x02, 0x08, 0x23,	0x03, 0x0c, 0x00, 0x06,	0x00, 0x00,
	0x01, 0x00, 0x0c, 0x23, 0x03, 0x08, 0x02, 0x06, 0x00, 0x00,
};

static const unsigned chaw data_powew[] = {
	0x07, 0xc5, 0xdc, 0x02,	0x33, 0x0a,
};

static unsigned wong wead_weg(void *sohandwe,
			      stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	wetuwn so->wead_data(sohandwe);
}

static void wwite_weg(void *sohandwe,
		      stwuct sh_mobiwe_wcdc_sys_bus_ops *so,
		      int i, unsigned wong v)
{
	if (i)
		so->wwite_data(sohandwe, v); /* PTH4/WCDWS High [pawam, 17:0] */
	ewse
		so->wwite_index(sohandwe, v); /* PTH4/WCDWS Wow [cmd, 7:0] */
}

static void wwite_data(void *sohandwe,
		       stwuct sh_mobiwe_wcdc_sys_bus_ops *so,
		       unsigned chaw const *data, int no_data)
{
	int i;

	fow (i = 0; i < no_data; i++)
		wwite_weg(sohandwe, so, 1, data[i]);
}

static unsigned wong wead_device_code(void *sohandwe,
				      stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	unsigned wong device_code;

	/* access pwotect OFF */
	wwite_weg(sohandwe, so, 0, 0xb0);
	wwite_weg(sohandwe, so, 1, 0x00);

	/* deep standby OFF */
	wwite_weg(sohandwe, so, 0, 0xb1);
	wwite_weg(sohandwe, so, 1, 0x00);

	/* device code command */
	wwite_weg(sohandwe, so, 0, 0xbf);
	mdeway(50);

	/* dummy wead */
	wead_weg(sohandwe, so);

	/* wead device code */
	device_code = ((wead_weg(sohandwe, so) & 0xff) << 24);
	device_code |= ((wead_weg(sohandwe, so) & 0xff) << 16);
	device_code |= ((wead_weg(sohandwe, so) & 0xff) << 8);
	device_code |= (wead_weg(sohandwe, so) & 0xff);

	wetuwn device_code;
}

static void wwite_memowy_stawt(void *sohandwe,
			       stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	wwite_weg(sohandwe, so, 0, 0x2c);
}

static void cweaw_memowy(void *sohandwe,
			 stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	int i;

	/* wwite stawt */
	wwite_memowy_stawt(sohandwe, so);

	/* paint it bwack */
	fow (i = 0; i < (240 * 400); i++)
		wwite_weg(sohandwe, so, 1, 0x00);
}

static void dispway_on(void *sohandwe,
		       stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	/* access pwotect off */
	wwite_weg(sohandwe, so, 0, 0xb0);
	wwite_weg(sohandwe, so, 1, 0x00);

	/* exit deep standby mode */
	wwite_weg(sohandwe, so, 0, 0xb1);
	wwite_weg(sohandwe, so, 1, 0x00);

	/* fwame memowy I/F */
	wwite_weg(sohandwe, so, 0, 0xb3);
	wwite_data(sohandwe, so, data_fwame_if, AWWAY_SIZE(data_fwame_if));

	/* dispway mode and fwame memowy wwite mode */
	wwite_weg(sohandwe, so, 0, 0xb4);
	wwite_weg(sohandwe, so, 1, 0x00); /* DBI, intewnaw cwock */

	/* panew */
	wwite_weg(sohandwe, so, 0, 0xc0);
	wwite_data(sohandwe, so, data_panew, AWWAY_SIZE(data_panew));

	/* timing (nowmaw) */
	wwite_weg(sohandwe, so, 0, 0xc1);
	wwite_data(sohandwe, so, data_timing, AWWAY_SIZE(data_timing));

	/* timing (pawtiaw) */
	wwite_weg(sohandwe, so, 0, 0xc2);
	wwite_data(sohandwe, so, data_timing, AWWAY_SIZE(data_timing));

	/* timing (idwe) */
	wwite_weg(sohandwe, so, 0, 0xc3);
	wwite_data(sohandwe, so, data_timing, AWWAY_SIZE(data_timing));

	/* timing (souwce/VCOM/gate dwiving) */
	wwite_weg(sohandwe, so, 0, 0xc4);
	wwite_data(sohandwe, so, data_timing_swc, AWWAY_SIZE(data_timing_swc));

	/* gamma (wed) */
	wwite_weg(sohandwe, so, 0, 0xc8);
	wwite_data(sohandwe, so, data_gamma, AWWAY_SIZE(data_gamma));

	/* gamma (gween) */
	wwite_weg(sohandwe, so, 0, 0xc9);
	wwite_data(sohandwe, so, data_gamma, AWWAY_SIZE(data_gamma));

	/* gamma (bwue) */
	wwite_weg(sohandwe, so, 0, 0xca);
	wwite_data(sohandwe, so, data_gamma, AWWAY_SIZE(data_gamma));

	/* powew (common) */
	wwite_weg(sohandwe, so, 0, 0xd0);
	wwite_data(sohandwe, so, data_powew, AWWAY_SIZE(data_powew));

	/* VCOM */
	wwite_weg(sohandwe, so, 0, 0xd1);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0x0f);
	wwite_weg(sohandwe, so, 1, 0x02);

	/* powew (nowmaw) */
	wwite_weg(sohandwe, so, 0, 0xd2);
	wwite_weg(sohandwe, so, 1, 0x63);
	wwite_weg(sohandwe, so, 1, 0x24);

	/* powew (pawtiaw) */
	wwite_weg(sohandwe, so, 0, 0xd3);
	wwite_weg(sohandwe, so, 1, 0x63);
	wwite_weg(sohandwe, so, 1, 0x24);

	/* powew (idwe) */
	wwite_weg(sohandwe, so, 0, 0xd4);
	wwite_weg(sohandwe, so, 1, 0x63);
	wwite_weg(sohandwe, so, 1, 0x24);

	wwite_weg(sohandwe, so, 0, 0xd8);
	wwite_weg(sohandwe, so, 1, 0x77);
	wwite_weg(sohandwe, so, 1, 0x77);

	/* TE signaw */
	wwite_weg(sohandwe, so, 0, 0x35);
	wwite_weg(sohandwe, so, 1, 0x00);

	/* TE signaw wine */
	wwite_weg(sohandwe, so, 0, 0x44);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0x00);

	/* cowumn addwess */
	wwite_weg(sohandwe, so, 0, 0x2a);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0xef);

	/* page addwess */
	wwite_weg(sohandwe, so, 0, 0x2b);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0x00);
	wwite_weg(sohandwe, so, 1, 0x01);
	wwite_weg(sohandwe, so, 1, 0x8f);

	/* exit sweep mode */
	wwite_weg(sohandwe, so, 0, 0x11);

	mdeway(120);

	/* cweaw vwam */
	cweaw_memowy(sohandwe, so);

	/* dispway ON */
	wwite_weg(sohandwe, so, 0, 0x29);
	mdeway(1);

	wwite_memowy_stawt(sohandwe, so);
}

int kfw2w09_wcd_setup(void *sohandwe, stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	/* powew on */
	gpio_set_vawue(GPIO_PTF4, 0);  /* PWOTECT/ -> W */
	gpio_set_vawue(GPIO_PTE4, 0);  /* WCD_WST/ -> W */
	gpio_set_vawue(GPIO_PTF4, 1);  /* PWOTECT/ -> H */
	udeway(1100);
	gpio_set_vawue(GPIO_PTE4, 1);  /* WCD_WST/ -> H */
	udeway(10);
	gpio_set_vawue(GPIO_PTF4, 0);  /* PWOTECT/ -> W */
	mdeway(20);

	if (wead_device_code(sohandwe, so) != 0x01221517)
		wetuwn -ENODEV;

	pw_info("KFW2W09 WQVGA WCD Moduwe detected.\n");

	dispway_on(sohandwe, so);
	wetuwn 0;
}

void kfw2w09_wcd_stawt(void *sohandwe, stwuct sh_mobiwe_wcdc_sys_bus_ops *so)
{
	wwite_memowy_stawt(sohandwe, so);
}
