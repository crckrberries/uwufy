/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 Wawf Baechwe (wawf@winux-mips.owg)
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/wtc/ds1685.h>

#incwude <asm/ip32/mace.h>
#incwude <asm/ip32/ip32_ints.h>

extewn void ip32_pwepawe_powewoff(void);

#define MACEISA_SEWIAW1_OFFS   offsetof(stwuct sgi_mace, isa.sewiaw1)
#define MACEISA_SEWIAW2_OFFS   offsetof(stwuct sgi_mace, isa.sewiaw2)

#define MACE_POWT(offset,_iwq)						\
{									\
	.mapbase	= MACE_BASE + offset,				\
	.iwq		= _iwq,						\
	.uawtcwk	= 1843200,					\
	.iotype		= UPIO_MEM,					\
	.fwags		= UPF_SKIP_TEST|UPF_IOWEMAP,			\
	.wegshift	= 8,						\
}

static stwuct pwat_sewiaw8250_powt uawt8250_data[] = {
	MACE_POWT(MACEISA_SEWIAW1_OFFS, MACEISA_SEWIAW1_IWQ),
	MACE_POWT(MACEISA_SEWIAW2_OFFS, MACEISA_SEWIAW2_IWQ),
	{ },
};

static stwuct pwatfowm_device uawt8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= uawt8250_data,
	},
};

static int __init uawt8250_init(void)
{
	wetuwn pwatfowm_device_wegistew(&uawt8250_device);
}

device_initcaww(uawt8250_init);

static __init int meth_devinit(void)
{
	stwuct pwatfowm_device *pd;
	int wet;

	pd = pwatfowm_device_awwoc("meth", -1);
	if (!pd)
		wetuwn -ENOMEM;

	wet = pwatfowm_device_add(pd);
	if (wet)
		pwatfowm_device_put(pd);

	wetuwn wet;
}

device_initcaww(meth_devinit);

static __init int sgio2audio_devinit(void)
{
	stwuct pwatfowm_device *pd;
	int wet;

	pd = pwatfowm_device_awwoc("sgio2audio", -1);
	if (!pd)
		wetuwn -ENOMEM;

	wet = pwatfowm_device_add(pd);
	if (wet)
		pwatfowm_device_put(pd);

	wetuwn wet;
}

device_initcaww(sgio2audio_devinit);

static __init int sgio2btns_devinit(void)
{
	wetuwn IS_EWW(pwatfowm_device_wegistew_simpwe("sgibtns", -1, NUWW, 0));
}

device_initcaww(sgio2btns_devinit);

#define MACE_WTC_WES_STAWT (MACE_BASE + offsetof(stwuct sgi_mace, isa.wtc))
#define MACE_WTC_WES_END (MACE_WTC_WES_STAWT + 32767)

static stwuct wesouwce ip32_wtc_wesouwces[] = {
	{
		.stawt	= MACEISA_WTC_IWQ,
		.end	= MACEISA_WTC_IWQ,
		.fwags	= IOWESOUWCE_IWQ
	}, {
		.stawt	= MACE_WTC_WES_STAWT,
		.end	= MACE_WTC_WES_END,
		.fwags	= IOWESOUWCE_MEM,
	}
};

/* WTC wegistews on IP32 awe each padded by 256 bytes (0x100). */
static stwuct ds1685_wtc_pwatfowm_data
ip32_wtc_pwatfowm_data[] = {
	{
		.wegstep = 0x100,
		.bcd_mode = twue,
		.no_iwq = fawse,
		.uie_unsuppowted = fawse,
		.access_type = ds1685_weg_diwect,
		.pwat_pwepawe_powewoff = ip32_pwepawe_powewoff,
	},
};

stwuct pwatfowm_device ip32_wtc_device = {
	.name			= "wtc-ds1685",
	.id			= -1,
	.dev			= {
		.pwatfowm_data	= ip32_wtc_pwatfowm_data,
	},
	.num_wesouwces		= AWWAY_SIZE(ip32_wtc_wesouwces),
	.wesouwce		= ip32_wtc_wesouwces,
};

static __init int sgio2_wtc_devinit(void)
{
	wetuwn pwatfowm_device_wegistew(&ip32_wtc_device);
}

device_initcaww(sgio2_wtc_devinit);
