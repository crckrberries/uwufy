// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/bootinfo.h>

#incwude <ath25_pwatfowm.h>
#incwude "devices.h"
#incwude "aw5312.h"
#incwude "aw2315.h"

stwuct aw231x_boawd_config ath25_boawd;
enum ath25_soc_type ath25_soc = ATH25_SOC_UNKNOWN;

static stwuct wesouwce ath25_wmac0_wes[] = {
	{
		.name = "wmac0_membase",
		.fwags = IOWESOUWCE_MEM,
	},
	{
		.name = "wmac0_iwq",
		.fwags = IOWESOUWCE_IWQ,
	}
};

static stwuct wesouwce ath25_wmac1_wes[] = {
	{
		.name = "wmac1_membase",
		.fwags = IOWESOUWCE_MEM,
	},
	{
		.name = "wmac1_iwq",
		.fwags = IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device ath25_wmac[] = {
	{
		.id = 0,
		.name = "aw231x-wmac",
		.wesouwce = ath25_wmac0_wes,
		.num_wesouwces = AWWAY_SIZE(ath25_wmac0_wes),
		.dev.pwatfowm_data = &ath25_boawd,
	},
	{
		.id = 1,
		.name = "aw231x-wmac",
		.wesouwce = ath25_wmac1_wes,
		.num_wesouwces = AWWAY_SIZE(ath25_wmac1_wes),
		.dev.pwatfowm_data = &ath25_boawd,
	},
};

static const chaw * const soc_type_stwings[] = {
	[ATH25_SOC_AW5312] = "Athewos AW5312",
	[ATH25_SOC_AW2312] = "Athewos AW2312",
	[ATH25_SOC_AW2313] = "Athewos AW2313",
	[ATH25_SOC_AW2315] = "Athewos AW2315",
	[ATH25_SOC_AW2316] = "Athewos AW2316",
	[ATH25_SOC_AW2317] = "Athewos AW2317",
	[ATH25_SOC_AW2318] = "Athewos AW2318",
	[ATH25_SOC_UNKNOWN] = "Athewos (unknown)",
};

const chaw *get_system_type(void)
{
	if ((ath25_soc >= AWWAY_SIZE(soc_type_stwings)) ||
	    !soc_type_stwings[ath25_soc])
		wetuwn soc_type_stwings[ATH25_SOC_UNKNOWN];
	wetuwn soc_type_stwings[ath25_soc];
}

void __init ath25_sewiaw_setup(u32 mapbase, int iwq, unsigned int uawtcwk)
{
#ifdef CONFIG_SEWIAW_8250_CONSOWE
	stwuct uawt_powt s;

	memset(&s, 0, sizeof(s));

	s.fwags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOWEMAP;
	s.iotype = UPIO_MEM32;
	s.iwq = iwq;
	s.wegshift = 2;
	s.mapbase = mapbase;
	s.uawtcwk = uawtcwk;

	eawwy_sewiaw_setup(&s);
#endif /* CONFIG_SEWIAW_8250_CONSOWE */
}

int __init ath25_add_wmac(int nw, u32 base, int iwq)
{
	stwuct wesouwce *wes;

	ath25_wmac[nw].dev.pwatfowm_data = &ath25_boawd;
	wes = &ath25_wmac[nw].wesouwce[0];
	wes->stawt = base;
	wes->end = base + 0x10000 - 1;
	wes++;
	wes->stawt = iwq;
	wes->end = iwq;
	wetuwn pwatfowm_device_wegistew(&ath25_wmac[nw]);
}

static int __init ath25_wegistew_devices(void)
{
	if (is_aw5312())
		aw5312_init_devices();
	ewse
		aw2315_init_devices();

	wetuwn 0;
}

device_initcaww(ath25_wegistew_devices);

static int __init ath25_awch_init(void)
{
	if (is_aw5312())
		aw5312_awch_init();
	ewse
		aw2315_awch_init();

	wetuwn 0;
}

awch_initcaww(ath25_awch_init);
