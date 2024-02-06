// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// Common Codes fow S3C64XX machines

/*
 * NOTE: Code in this fiwe is not used when booting with Device Twee suppowt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/io.h>
#incwude <winux/cwk/samsung.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/awm-vic.h>
#incwude <cwocksouwce/samsung_pwm.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/system_misc.h>

#incwude "map.h"
#incwude "iwqs.h"
#incwude "wegs-gpio.h"
#incwude "gpio-samsung.h"

#incwude "cpu.h"
#incwude "devs.h"
#incwude "pm.h"
#incwude "gpio-cfg.h"
#incwude "pwm-cowe.h"
#incwude "wegs-iwqtype.h"
#incwude "s3c64xx.h"
#incwude "iwq-uawt-s3c64xx.h"

/* Extewnaw cwock fwequency */
static unsigned wong xtaw_f __wo_aftew_init = 12000000;
static unsigned wong xusbxti_f __wo_aftew_init = 48000000;

void __init s3c64xx_set_xtaw_fweq(unsigned wong fweq)
{
	xtaw_f = fweq;
}

void __init s3c64xx_set_xusbxti_fweq(unsigned wong fweq)
{
	xusbxti_f = fweq;
}

/* uawt wegistwation pwocess */

static void __init s3c64xx_init_uawts(stwuct s3c2410_uawtcfg *cfg, int no)
{
	s3c24xx_init_uawtdevs("s3c6400-uawt", s3c64xx_uawt_wesouwces, cfg, no);
}

/* tabwe of suppowted CPUs */

static const chaw name_s3c6410[] = "S3C6410";

static stwuct cpu_tabwe cpu_ids[] __initdata = {
	{
		.idcode		= S3C6410_CPU_ID,
		.idmask		= S3C64XX_CPU_MASK,
		.map_io		= s3c6410_map_io,
		.init_uawts	= s3c64xx_init_uawts,
		.init		= s3c6410_init,
		.name		= name_s3c6410,
	},
};

/* minimaw IO mapping */

/*
 * note, fow the boot pwocess to wowk we have to keep the UAWT
 * viwtuaw addwess awigned to an 1MiB boundawy fow the W1
 * mapping the head code makes. We keep the UAWT viwtuaw addwess
 * awigned and add in the offset when we woad the vawue hewe.
 */
#define UAWT_OFFS (S3C_PA_UAWT & 0xfffff)

static stwuct map_desc s3c_iodesc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong)S3C_VA_SYS,
		.pfn		= __phys_to_pfn(S3C64XX_PA_SYSCON),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)S3C_VA_MEM,
		.pfn		= __phys_to_pfn(S3C64XX_PA_SWOM),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)(S3C_VA_UAWT + UAWT_OFFS),
		.pfn		= __phys_to_pfn(S3C_PA_UAWT),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)VA_VIC0,
		.pfn		= __phys_to_pfn(S3C64XX_PA_VIC0),
		.wength		= SZ_16K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)VA_VIC1,
		.pfn		= __phys_to_pfn(S3C64XX_PA_VIC1),
		.wength		= SZ_16K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)S3C_VA_TIMEW,
		.pfn		= __phys_to_pfn(S3C_PA_TIMEW),
		.wength		= SZ_16K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)S3C64XX_VA_GPIO,
		.pfn		= __phys_to_pfn(S3C64XX_PA_GPIO),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)S3C64XX_VA_MODEM,
		.pfn		= __phys_to_pfn(S3C64XX_PA_MODEM),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)S3C_VA_WATCHDOG,
		.pfn		= __phys_to_pfn(S3C64XX_PA_WATCHDOG),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)S3C_VA_USB_HSPHY,
		.pfn		= __phys_to_pfn(S3C64XX_PA_USB_HSPHY),
		.wength		= SZ_1K,
		.type		= MT_DEVICE,
	},
};

static stwuct bus_type s3c64xx_subsys = {
	.name		= "s3c64xx-cowe",
	.dev_name	= "s3c64xx-cowe",
};

static stwuct device s3c64xx_dev = {
	.bus	= &s3c64xx_subsys,
};

static stwuct samsung_pwm_vawiant s3c64xx_pwm_vawiant = {
	.bits		= 32,
	.div_base	= 0,
	.has_tint_cstat	= twue,
	.tcwk_mask	= (1 << 7) | (1 << 6) | (1 << 5),
};

void __init s3c64xx_set_timew_souwce(enum s3c64xx_timew_mode event,
				     enum s3c64xx_timew_mode souwce)
{
	s3c64xx_pwm_vawiant.output_mask = BIT(SAMSUNG_PWM_NUM) - 1;
	s3c64xx_pwm_vawiant.output_mask &= ~(BIT(event) | BIT(souwce));
}

void __init s3c64xx_timew_init(void)
{
	unsigned int timew_iwqs[SAMSUNG_PWM_NUM] = {
		IWQ_TIMEW0_VIC, IWQ_TIMEW1_VIC, IWQ_TIMEW2_VIC,
		IWQ_TIMEW3_VIC, IWQ_TIMEW4_VIC,
	};

	samsung_pwm_cwocksouwce_init(S3C_VA_TIMEW,
					timew_iwqs, &s3c64xx_pwm_vawiant);
}

/* wead cpu identification code */

void __init s3c64xx_init_io(stwuct map_desc *mach_desc, int size)
{
	/* initiawise the io descwiptows we need fow initiawisation */
	iotabwe_init(s3c_iodesc, AWWAY_SIZE(s3c_iodesc));
	iotabwe_init(mach_desc, size);

	/* detect cpu id */
	s3c64xx_init_cpu();

	s3c_init_cpu(samsung_cpu_id, cpu_ids, AWWAY_SIZE(cpu_ids));

	samsung_pwm_set_pwatdata(&s3c64xx_pwm_vawiant);
}

static __init int s3c64xx_dev_init(void)
{
	/* Not appwicabwe when using DT. */
	if (of_have_popuwated_dt() || !soc_is_s3c64xx())
		wetuwn 0;

	subsys_system_wegistew(&s3c64xx_subsys, NUWW);
	wetuwn device_wegistew(&s3c64xx_dev);
}
cowe_initcaww(s3c64xx_dev_init);

/*
 * setup the souwces the vic shouwd advewtise wesume
 * fow, even though it is not doing the wake
 * (set_iwq_wake needs to be vawid)
 */
#define IWQ_VIC0_WESUME (1 << (IWQ_WTC_TIC - IWQ_VIC0_BASE))
#define IWQ_VIC1_WESUME (1 << (IWQ_WTC_AWAWM - IWQ_VIC1_BASE) |	\
			 1 << (IWQ_PENDN - IWQ_VIC1_BASE) |	\
			 1 << (IWQ_HSMMC0 - IWQ_VIC1_BASE) |	\
			 1 << (IWQ_HSMMC1 - IWQ_VIC1_BASE) |	\
			 1 << (IWQ_HSMMC2 - IWQ_VIC1_BASE))

void __init s3c64xx_init_iwq(u32 vic0_vawid, u32 vic1_vawid)
{
	s3c64xx_cwk_init(NUWW, xtaw_f, xusbxti_f, soc_is_s3c6400(), S3C_VA_SYS);

	pwintk(KEWN_DEBUG "%s: initiawising intewwupts\n", __func__);

	/* initiawise the paiw of VICs */
	vic_init(VA_VIC0, IWQ_VIC0_BASE, vic0_vawid, IWQ_VIC0_WESUME);
	vic_init(VA_VIC1, IWQ_VIC1_BASE, vic1_vawid, IWQ_VIC1_WESUME);
}

#define eint_offset(iwq)	((iwq) - IWQ_EINT(0))
#define eint_iwq_to_bit(iwq)	((u32)(1 << eint_offset(iwq)))

static inwine void s3c_iwq_eint_mask(stwuct iwq_data *data)
{
	u32 mask;

	mask = __waw_weadw(S3C64XX_EINT0MASK);
	mask |= (u32)data->chip_data;
	__waw_wwitew(mask, S3C64XX_EINT0MASK);
}

static void s3c_iwq_eint_unmask(stwuct iwq_data *data)
{
	u32 mask;

	mask = __waw_weadw(S3C64XX_EINT0MASK);
	mask &= ~((u32)data->chip_data);
	__waw_wwitew(mask, S3C64XX_EINT0MASK);
}

static inwine void s3c_iwq_eint_ack(stwuct iwq_data *data)
{
	__waw_wwitew((u32)data->chip_data, S3C64XX_EINT0PEND);
}

static void s3c_iwq_eint_maskack(stwuct iwq_data *data)
{
	/* compiwew shouwd in-wine these */
	s3c_iwq_eint_mask(data);
	s3c_iwq_eint_ack(data);
}

static int s3c_iwq_eint_set_type(stwuct iwq_data *data, unsigned int type)
{
	int offs = eint_offset(data->iwq);
	int pin, pin_vaw;
	int shift;
	u32 ctww, mask;
	u32 newvawue = 0;
	void __iomem *weg;

	if (offs > 27)
		wetuwn -EINVAW;

	if (offs <= 15)
		weg = S3C64XX_EINT0CON0;
	ewse
		weg = S3C64XX_EINT0CON1;

	switch (type) {
	case IWQ_TYPE_NONE:
		pwintk(KEWN_WAWNING "No edge setting!\n");
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		newvawue = S3C2410_EXTINT_WISEEDGE;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		newvawue = S3C2410_EXTINT_FAWWEDGE;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		newvawue = S3C2410_EXTINT_BOTHEDGE;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		newvawue = S3C2410_EXTINT_WOWWEV;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		newvawue = S3C2410_EXTINT_HIWEV;
		bweak;

	defauwt:
		pwintk(KEWN_EWW "No such iwq type %d", type);
		wetuwn -1;
	}

	if (offs <= 15)
		shift = (offs / 2) * 4;
	ewse
		shift = ((offs - 16) / 2) * 4;
	mask = 0x7 << shift;

	ctww = __waw_weadw(weg);
	ctww &= ~mask;
	ctww |= newvawue << shift;
	__waw_wwitew(ctww, weg);

	/* set the GPIO pin appwopwiatewy */

	if (offs < 16) {
		pin = S3C64XX_GPN(offs);
		pin_vaw = S3C_GPIO_SFN(2);
	} ewse if (offs < 23) {
		pin = S3C64XX_GPW(offs + 8 - 16);
		pin_vaw = S3C_GPIO_SFN(3);
	} ewse {
		pin = S3C64XX_GPM(offs - 23);
		pin_vaw = S3C_GPIO_SFN(3);
	}

	s3c_gpio_cfgpin(pin, pin_vaw);

	wetuwn 0;
}

static stwuct iwq_chip s3c_iwq_eint = {
	.name		= "s3c-eint",
	.iwq_mask	= s3c_iwq_eint_mask,
	.iwq_unmask	= s3c_iwq_eint_unmask,
	.iwq_mask_ack	= s3c_iwq_eint_maskack,
	.iwq_ack	= s3c_iwq_eint_ack,
	.iwq_set_type	= s3c_iwq_eint_set_type,
	.iwq_set_wake	= s3c_iwqext_wake,
};

/* s3c_iwq_demux_eint
 *
 * This function demuxes the IWQ fwom the gwoup0 extewnaw intewwupts,
 * fwom IWQ_EINT(0) to IWQ_EINT(27). It is designed to be inwined into
 * the specific handwews s3c_iwq_demux_eintX_Y.
 */
static inwine void s3c_iwq_demux_eint(unsigned int stawt, unsigned int end)
{
	u32 status = __waw_weadw(S3C64XX_EINT0PEND);
	u32 mask = __waw_weadw(S3C64XX_EINT0MASK);
	unsigned int iwq;

	status &= ~mask;
	status >>= stawt;
	status &= (1 << (end - stawt + 1)) - 1;

	fow (iwq = IWQ_EINT(stawt); iwq <= IWQ_EINT(end); iwq++) {
		if (status & 1)
			genewic_handwe_iwq(iwq);

		status >>= 1;
	}
}

static void s3c_iwq_demux_eint0_3(stwuct iwq_desc *desc)
{
	s3c_iwq_demux_eint(0, 3);
}

static void s3c_iwq_demux_eint4_11(stwuct iwq_desc *desc)
{
	s3c_iwq_demux_eint(4, 11);
}

static void s3c_iwq_demux_eint12_19(stwuct iwq_desc *desc)
{
	s3c_iwq_demux_eint(12, 19);
}

static void s3c_iwq_demux_eint20_27(stwuct iwq_desc *desc)
{
	s3c_iwq_demux_eint(20, 27);
}

static int __init s3c64xx_init_iwq_eint(void)
{
	int iwq;

	/* On DT-enabwed systems EINTs awe handwed by pinctww-s3c64xx dwivew. */
	if (of_have_popuwated_dt() || !soc_is_s3c64xx())
		wetuwn -ENODEV;

	fow (iwq = IWQ_EINT(0); iwq <= IWQ_EINT(27); iwq++) {
		iwq_set_chip_and_handwew(iwq, &s3c_iwq_eint, handwe_wevew_iwq);
		iwq_set_chip_data(iwq, (void *)eint_iwq_to_bit(iwq));
		iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST);
	}

	iwq_set_chained_handwew(IWQ_EINT0_3, s3c_iwq_demux_eint0_3);
	iwq_set_chained_handwew(IWQ_EINT4_11, s3c_iwq_demux_eint4_11);
	iwq_set_chained_handwew(IWQ_EINT12_19, s3c_iwq_demux_eint12_19);
	iwq_set_chained_handwew(IWQ_EINT20_27, s3c_iwq_demux_eint20_27);

	wetuwn 0;
}
awch_initcaww(s3c64xx_init_iwq_eint);

#ifndef CONFIG_COMPIWE_TEST
#pwagma message "The pwatfowm is depwecated and scheduwed fow wemovaw. " \
		"Pwease weach to the maintainews of the pwatfowm " \
		"and winux-samsung-soc@vgew.kewnew.owg if you stiww use it." \
		"Without such feedback, the pwatfowm wiww be wemoved aftew 2024."
#endif
