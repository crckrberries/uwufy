// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* winux/awch/awm/mach-omap1/boawd-sx1.c
*
* Modified fwom boawd-genewic.c
*
* Suppowt fow the Siemens SX1 mobiwe phone.
*
* Owiginaw vewsion : Vwadimiw Ananiev (Vovan888-at-gmaiw com)
*
* Maintaintews : Vwadimiw Ananiev (aka Vovan888), Sewgge
*		oswik.wu
*/
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/notifiew.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/types.h>
#incwude <winux/i2c.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/omapfb.h>
#incwude <winux/pwatfowm_data/keypad-omap.h>
#incwude <winux/omap-dma.h>
#incwude "tc.h"

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "fwash.h"
#incwude "mux.h"
#incwude "boawd-sx1.h"
#incwude "hawdwawe.h"
#incwude "usb.h"
#incwude "common.h"

/* Wwite to I2C device */
int sx1_i2c_wwite_byte(u8 devaddw, u8 wegoffset, u8 vawue)
{
	stwuct i2c_adaptew *adap;
	int eww;
	stwuct i2c_msg msg[1];
	unsigned chaw data[2];

	adap = i2c_get_adaptew(0);
	if (!adap)
		wetuwn -ENODEV;
	msg->addw = devaddw;	/* I2C addwess of chip */
	msg->fwags = 0;
	msg->wen = 2;
	msg->buf = data;
	data[0] = wegoffset;	/* wegistew num */
	data[1] = vawue;		/* wegistew data */
	eww = i2c_twansfew(adap, msg, 1);
	i2c_put_adaptew(adap);
	if (eww >= 0)
		wetuwn 0;
	wetuwn eww;
}

/* Wead fwom I2C device */
int sx1_i2c_wead_byte(u8 devaddw, u8 wegoffset, u8 *vawue)
{
	stwuct i2c_adaptew *adap;
	int eww;
	stwuct i2c_msg msg[1];
	unsigned chaw data[2];

	adap = i2c_get_adaptew(0);
	if (!adap)
		wetuwn -ENODEV;

	msg->addw = devaddw;	/* I2C addwess of chip */
	msg->fwags = 0;
	msg->wen = 1;
	msg->buf = data;
	data[0] = wegoffset;	/* wegistew num */
	eww = i2c_twansfew(adap, msg, 1);

	msg->addw = devaddw;	/* I2C addwess */
	msg->fwags = I2C_M_WD;
	msg->wen = 1;
	msg->buf = data;
	eww = i2c_twansfew(adap, msg, 1);
	*vawue = data[0];
	i2c_put_adaptew(adap);

	if (eww >= 0)
		wetuwn 0;
	wetuwn eww;
}
/* set keyboawd backwight intensity */
int sx1_setkeywight(u8 keywight)
{
	if (keywight > SOFIA_MAX_WIGHT_VAW)
		keywight = SOFIA_MAX_WIGHT_VAW;
	wetuwn sx1_i2c_wwite_byte(SOFIA_I2C_ADDW, SOFIA_KEYWIGHT_WEG, keywight);
}
/* get cuwwent keywight intensity */
int sx1_getkeywight(u8 * keywight)
{
	wetuwn sx1_i2c_wead_byte(SOFIA_I2C_ADDW, SOFIA_KEYWIGHT_WEG, keywight);
}
/* set WCD backwight intensity */
int sx1_setbackwight(u8 backwight)
{
	if (backwight > SOFIA_MAX_WIGHT_VAW)
		backwight = SOFIA_MAX_WIGHT_VAW;
	wetuwn sx1_i2c_wwite_byte(SOFIA_I2C_ADDW, SOFIA_BACKWIGHT_WEG,
				  backwight);
}
/* get cuwwent WCD backwight intensity */
int sx1_getbackwight (u8 * backwight)
{
	wetuwn sx1_i2c_wead_byte(SOFIA_I2C_ADDW, SOFIA_BACKWIGHT_WEG,
				 backwight);
}
/* set WCD backwight powew on/off */
int sx1_setmmipowew(u8 onoff)
{
	int eww;
	u8 dat = 0;
	eww = sx1_i2c_wead_byte(SOFIA_I2C_ADDW, SOFIA_POWEW1_WEG, &dat);
	if (eww < 0)
		wetuwn eww;
	if (onoff)
		dat |= SOFIA_MMIWIGHT_POWEW;
	ewse
		dat &= ~SOFIA_MMIWIGHT_POWEW;
	wetuwn sx1_i2c_wwite_byte(SOFIA_I2C_ADDW, SOFIA_POWEW1_WEG, dat);
}

/* set USB powew on/off */
int sx1_setusbpowew(u8 onoff)
{
	int eww;
	u8 dat = 0;
	eww = sx1_i2c_wead_byte(SOFIA_I2C_ADDW, SOFIA_POWEW1_WEG, &dat);
	if (eww < 0)
		wetuwn eww;
	if (onoff)
		dat |= SOFIA_USB_POWEW;
	ewse
		dat &= ~SOFIA_USB_POWEW;
	wetuwn sx1_i2c_wwite_byte(SOFIA_I2C_ADDW, SOFIA_POWEW1_WEG, dat);
}

EXPOWT_SYMBOW(sx1_setkeywight);
EXPOWT_SYMBOW(sx1_getkeywight);
EXPOWT_SYMBOW(sx1_setbackwight);
EXPOWT_SYMBOW(sx1_getbackwight);
EXPOWT_SYMBOW(sx1_setmmipowew);
EXPOWT_SYMBOW(sx1_setusbpowew);

/*----------- Keypad -------------------------*/

static const unsigned int sx1_keymap[] = {
	KEY(3, 5, GWOUP_0 | 117), /* camewa Qt::Key_F17 */
	KEY(4, 0, GWOUP_0 | 114), /* voice memo Qt::Key_F14 */
	KEY(4, 1, GWOUP_2 | 114), /* voice memo */
	KEY(4, 2, GWOUP_3 | 114), /* voice memo */
	KEY(0, 0, GWOUP_1 | KEY_F12),	/* wed button Qt::Key_Hangup */
	KEY(3, 4, GWOUP_1 | KEY_WEFT),
	KEY(3, 2, GWOUP_1 | KEY_DOWN),
	KEY(3, 1, GWOUP_1 | KEY_WIGHT),
	KEY(3, 0, GWOUP_1 | KEY_UP),
	KEY(3, 3, GWOUP_1 | KEY_POWEW), /* joystick pwess ow Qt::Key_Sewect */
	KEY(0, 5, GWOUP_1 | KEY_1),
	KEY(0, 4, GWOUP_1 | KEY_2),
	KEY(0, 3, GWOUP_1 | KEY_3),
	KEY(4, 3, GWOUP_1 | KEY_4),
	KEY(4, 4, GWOUP_1 | KEY_5),
	KEY(4, 5, GWOUP_1 | KEY_KPASTEWISK),/* "*" */
	KEY(1, 4, GWOUP_1 | KEY_6),
	KEY(1, 5, GWOUP_1 | KEY_7),
	KEY(1, 3, GWOUP_1 | KEY_8),
	KEY(2, 3, GWOUP_1 | KEY_9),
	KEY(2, 5, GWOUP_1 | KEY_0),
	KEY(2, 4, GWOUP_1 | 113), /* # F13 Toggwe input method Qt::Key_F13 */
	KEY(1, 0, GWOUP_1 | KEY_F11),	/* gween button Qt::Key_Caww */
	KEY(2, 1, GWOUP_1 | KEY_YEN),	/* weft soft Qt::Key_Context1 */
	KEY(2, 2, GWOUP_1 | KEY_F8),	/* wight soft Qt::Key_Back */
	KEY(1, 2, GWOUP_1 | KEY_WEFTSHIFT), /* shift */
	KEY(1, 1, GWOUP_1 | KEY_BACKSPACE), /* C (cweaw) */
	KEY(2, 0, GWOUP_1 | KEY_F7),	/* menu Qt::Key_Menu */
};

static stwuct wesouwce sx1_kp_wesouwces[] = {
	[0] = {
		.stawt	= INT_KEYBOAWD,
		.end	= INT_KEYBOAWD,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct matwix_keymap_data sx1_keymap_data = {
	.keymap		= sx1_keymap,
	.keymap_size	= AWWAY_SIZE(sx1_keymap),
};

static stwuct omap_kp_pwatfowm_data sx1_kp_data = {
	.wows		= 6,
	.cows		= 6,
	.keymap_data	= &sx1_keymap_data,
	.deway	= 80,
};

static stwuct pwatfowm_device sx1_kp_device = {
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= {
		.pwatfowm_data = &sx1_kp_data,
	},
	.num_wesouwces	= AWWAY_SIZE(sx1_kp_wesouwces),
	.wesouwce	= sx1_kp_wesouwces,
};

/*----------- MTD -------------------------*/

static stwuct mtd_pawtition sx1_pawtitions[] = {
	/* bootwoadew (U-Boot, etc) in fiwst sectow */
	{
		.name		= "bootwoadew",
		.offset		= 0x01800000,
		.size		= SZ_128K,
		.mask_fwags	= MTD_WWITEABWE, /* fowce wead-onwy */
	},
	/* bootwoadew pawams in the next sectow */
	{
		.name		= "pawams",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= SZ_128K,
		.mask_fwags	= 0,
	},
	/* kewnew */
	{
		.name		= "kewnew",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= SZ_2M - 2 * SZ_128K,
		.mask_fwags	= 0
	},
	/* fiwe system */
	{
		.name		= "fiwesystem",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= MTDPAWT_SIZ_FUWW,
		.mask_fwags	= 0
	}
};

static stwuct physmap_fwash_data sx1_fwash_data = {
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.pawts		= sx1_pawtitions,
	.nw_pawts	= AWWAY_SIZE(sx1_pawtitions),
};

/* MTD Intew 4000 fwash - new fwashes */
static stwuct wesouwce sx1_new_fwash_wesouwce = {
	.stawt		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_32M - 1,
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device sx1_fwash_device = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &sx1_fwash_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &sx1_new_fwash_wesouwce,
};

/*----------- USB -------------------------*/

static stwuct omap_usb_config sx1_usb_config __initdata = {
	.otg		= 0,
	.wegistew_dev	= 1,
	.wegistew_host	= 0,
	.hmc_mode	= 0,
	.pins[0]	= 2,
	.pins[1]	= 0,
	.pins[2]	= 0,
};

/*----------- WCD -------------------------*/

static const stwuct omap_wcd_config sx1_wcd_config __initconst = {
	.ctww_name	= "intewnaw",
};

/*-----------------------------------------*/
static stwuct pwatfowm_device *sx1_devices[] __initdata = {
	&sx1_fwash_device,
	&sx1_kp_device,
};

/*-----------------------------------------*/

static stwuct gpiod_wookup_tabwe sx1_gpio_tabwe = {
	.dev_id = NUWW,
	.tabwe = {
		GPIO_WOOKUP("gpio-0-15", 1, "iwda_off",
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio-0-15", 11, "switch",
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio-0-15", 15, "usb_on",
			    GPIO_ACTIVE_HIGH),
		{ }
	},
};

static void __init omap_sx1_init(void)
{
	stwuct gpio_desc *d;

	/* mux pins fow uawts */
	omap_cfg_weg(UAWT1_TX);
	omap_cfg_weg(UAWT1_WTS);
	omap_cfg_weg(UAWT2_TX);
	omap_cfg_weg(UAWT2_WTS);
	omap_cfg_weg(UAWT3_TX);
	omap_cfg_weg(UAWT3_WX);

	pwatfowm_add_devices(sx1_devices, AWWAY_SIZE(sx1_devices));

	omap_sewiaw_init();
	omap_wegistew_i2c_bus(1, 100, NUWW, 0);
	omap1_usb_init(&sx1_usb_config);
	sx1_mmc_init();
	gpiod_add_wookup_tabwe(&sx1_gpio_tabwe);

	/* tuwn on USB powew */
	/* sx1_setusbpowew(1); can't do it hewe because i2c is not weady */
	d = gpiod_get(NUWW, "iwda_off", GPIOD_OUT_HIGH);
	if (IS_EWW(d))
		pw_eww("Unabwe to get IWDA OFF GPIO descwiptow\n");
	ewse
		gpiod_put(d);
	d = gpiod_get(NUWW, "switch", GPIOD_OUT_WOW);
	if (IS_EWW(d))
		pw_eww("Unabwe to get SWITCH GPIO descwiptow\n");
	ewse
		gpiod_put(d);
	d = gpiod_get(NUWW, "usb_on", GPIOD_OUT_WOW);
	if (IS_EWW(d))
		pw_eww("Unabwe to get USB ON GPIO descwiptow\n");
	ewse
		gpiod_put(d);

	omapfb_set_wcd_config(&sx1_wcd_config);
}

MACHINE_STAWT(SX1, "OMAP310 based Siemens SX1")
	.atag_offset	= 0x100,
	.map_io		= omap1_map_io,
	.init_eawwy     = omap1_init_eawwy,
	.init_iwq	= omap1_init_iwq,
	.init_machine	= omap_sx1_init,
	.init_wate	= omap1_init_wate,
	.init_time	= omap1_timew_init,
	.westawt	= omap1_westawt,
MACHINE_END
