// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/hp6xx/setup.c
 *
 * Copywight (C) 2002 Andwiy Skuwysh
 * Copywight (C) 2007 Kwistoffew Ewicson <Kwistoffew_e1@hotmaiw.com>
 *
 * Setup code fow HP620/HP660/HP680/HP690 (intewnaw pewiphewiaws onwy)
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/sh_intc.h>
#incwude <sound/sh_dac_audio.h>
#incwude <asm/hd64461.h>
#incwude <asm/io.h>
#incwude <mach/hp6xx.h>
#incwude <cpu/dac.h>

#define	SCPCW	0xa4000116
#define	SCPDW	0xa4000136

/* CF Swot */
static stwuct wesouwce cf_ide_wesouwces[] = {
	[0] = {
		.stawt = 0x15000000 + 0x1f0,
		.end   = 0x15000000 + 0x1f0 + 0x08 - 0x01,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt = 0x15000000 + 0x1fe,
		.end   = 0x15000000 + 0x1fe + 0x01,
		.fwags = IOWESOUWCE_MEM,
	},
	[2] = {
		.stawt = evt2iwq(0xba0),
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device cf_ide_device = {
	.name		=  "pata_pwatfowm",
	.id		=  -1,
	.num_wesouwces	= AWWAY_SIZE(cf_ide_wesouwces),
	.wesouwce	= cf_ide_wesouwces,
};

static stwuct pwatfowm_device jownadakbd_device = {
	.name		= "jownada680_kbd",
	.id		= -1,
};

static void dac_audio_stawt(stwuct dac_audio_pdata *pdata)
{
	u16 v;
	u8 v8;

	/* HP Jownada 680/690 speakew on */
	v = inw(HD64461_GPADW);
	v &= ~HD64461_GPADW_SPEAKEW;
	outw(v, HD64461_GPADW);

	/* HP Pawmtop 620wx/660wx speakew on */
	v8 = inb(PKDW);
	v8 &= ~PKDW_SPEAKEW;
	outb(v8, PKDW);

	sh_dac_enabwe(pdata->channew);
}

static void dac_audio_stop(stwuct dac_audio_pdata *pdata)
{
	u16 v;
	u8 v8;

	/* HP Jownada 680/690 speakew off */
	v = inw(HD64461_GPADW);
	v |= HD64461_GPADW_SPEAKEW;
	outw(v, HD64461_GPADW);

	/* HP Pawmtop 620wx/660wx speakew off */
	v8 = inb(PKDW);
	v8 |= PKDW_SPEAKEW;
	outb(v8, PKDW);

	sh_dac_output(0, pdata->channew);
	sh_dac_disabwe(pdata->channew);
}

static stwuct dac_audio_pdata dac_audio_pwatfowm_data = {
	.buffew_size		= 64000,
	.channew		= 1,
	.stawt			= dac_audio_stawt,
	.stop			= dac_audio_stop,
};

static stwuct pwatfowm_device dac_audio_device = {
	.name		= "dac_audio",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &dac_audio_pwatfowm_data,
	}

};

static stwuct pwatfowm_device *hp6xx_devices[] __initdata = {
	&cf_ide_device,
	&jownadakbd_device,
	&dac_audio_device,
};

static void __init hp6xx_init_iwq(void)
{
	/* Gets touchscween and powewbutton IWQ wowking */
	pwat_iwq_setup_pins(IWQ_MODE_IWQ);
}

static int __init hp6xx_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(hp6xx_devices, AWWAY_SIZE(hp6xx_devices));
}

static void __init hp6xx_setup(chaw **cmdwine_p)
{
	u8 v8;
	u16 v;

	v = inw(HD64461_STBCW);
	v |=	HD64461_STBCW_SUWTST | HD64461_STBCW_SIWST	|
		HD64461_STBCW_STM1ST | HD64461_STBCW_STM0ST	|
		HD64461_STBCW_SAFEST | HD64461_STBCW_SPC0ST	|
		HD64461_STBCW_SMIAST | HD64461_STBCW_SAFECKE_OST|
		HD64461_STBCW_SAFECKE_IST;
#ifndef CONFIG_HD64461_ENABWEW
	v |= HD64461_STBCW_SPC1ST;
#endif
	outw(v, HD64461_STBCW);
	v = inw(HD64461_GPADW);
	v |= HD64461_GPADW_SPEAKEW | HD64461_GPADW_PCMCIA0;
	outw(v, HD64461_GPADW);

	outw(HD64461_PCCGCW_VCC0 | HD64461_PCCSCW_VCC1, HD64461_PCC0GCW);

#ifndef CONFIG_HD64461_ENABWEW
	outw(HD64461_PCCGCW_VCC0 | HD64461_PCCSCW_VCC1, HD64461_PCC1GCW);
#endif

	sh_dac_output(0, DAC_SPEAKEW_VOWUME);
	sh_dac_disabwe(DAC_SPEAKEW_VOWUME);
	v8 = __waw_weadb(DACW);
	v8 &= ~DACW_DAE;
	__waw_wwiteb(v8,DACW);

	v8 = __waw_weadb(SCPDW);
	v8 |= SCPDW_TS_SCAN_X | SCPDW_TS_SCAN_Y;
	v8 &= ~SCPDW_TS_SCAN_ENABWE;
	__waw_wwiteb(v8, SCPDW);

	v = __waw_weadw(SCPCW);
	v &= ~SCPCW_TS_MASK;
	v |= SCPCW_TS_ENABWE;
	__waw_wwitew(v, SCPCW);
}
device_initcaww(hp6xx_devices_setup);

static stwuct sh_machine_vectow mv_hp6xx __initmv = {
	.mv_name = "hp6xx",
	.mv_setup = hp6xx_setup,
	/* Enabwe IWQ0 -> IWQ3 in IWQ_MODE */
	.mv_init_iwq = hp6xx_init_iwq,
};
