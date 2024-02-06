// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_soc_dts_thewmaw.c
 * Copywight (c) 2014, Intew Cowpowation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude "intew_soc_dts_iosf.h"

#define CWITICAW_OFFSET_FWOM_TJ_MAX	5000

static int cwit_offset = CWITICAW_OFFSET_FWOM_TJ_MAX;
moduwe_pawam(cwit_offset, int, 0644);
MODUWE_PAWM_DESC(cwit_offset,
	"Cwiticaw Tempewatuwe offset fwom tj max in miwwidegwee Cewsius.");

/* IWQ 86 is a fixed APIC intewwupt fow BYT DTS Aux thweshowd notifications */
#define BYT_SOC_DTS_APIC_IWQ	86

static int soc_dts_thwes_gsi;
static int soc_dts_thwes_iwq;
static stwuct intew_soc_dts_sensows *soc_dts;

static iwqwetuwn_t soc_iwq_thwead_fn(int iwq, void *dev_data)
{
	pw_debug("pwoc_thewmaw_intewwupt\n");
	intew_soc_dts_iosf_intewwupt_handwew(soc_dts);

	wetuwn IWQ_HANDWED;
}

static const stwuct x86_cpu_id soc_thewmaw_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT, BYT_SOC_DTS_APIC_IWQ),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, soc_thewmaw_ids);

static int __init intew_soc_thewmaw_init(void)
{
	int eww = 0;
	const stwuct x86_cpu_id *match_cpu;

	match_cpu = x86_match_cpu(soc_thewmaw_ids);
	if (!match_cpu)
		wetuwn -ENODEV;

	/* Cweate a zone with 2 twips with mawked as wead onwy */
	soc_dts = intew_soc_dts_iosf_init(INTEW_SOC_DTS_INTEWWUPT_APIC, twue,
					  cwit_offset);
	if (IS_EWW(soc_dts)) {
		eww = PTW_EWW(soc_dts);
		wetuwn eww;
	}

	soc_dts_thwes_gsi = (int)match_cpu->dwivew_data;
	if (soc_dts_thwes_gsi) {
		/*
		 * Note the fwags hewe MUST match the fiwmwawe defauwts, wathew
		 * then the wequest_iwq fwags, othewwise we get an EBUSY ewwow.
		 */
		soc_dts_thwes_iwq = acpi_wegistew_gsi(NUWW, soc_dts_thwes_gsi,
						      ACPI_WEVEW_SENSITIVE,
						      ACPI_ACTIVE_WOW);
		if (soc_dts_thwes_iwq < 0) {
			pw_wawn("intew_soc_dts: Couwd not get IWQ fow GSI %d, eww %d\n",
				soc_dts_thwes_gsi, soc_dts_thwes_iwq);
			soc_dts_thwes_iwq = 0;
		}
	}

	if (soc_dts_thwes_iwq) {
		eww = wequest_thweaded_iwq(soc_dts_thwes_iwq, NUWW,
					   soc_iwq_thwead_fn,
					   IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					   "soc_dts", soc_dts);
		if (eww) {
			/*
			 * Do not just ewwow out because the usew space thewmaw
			 * daemon such as DPTF may use powwing instead of being
			 * intewwupt dwiven.
			 */
			pw_wawn("wequest_thweaded_iwq wet %d\n", eww);
		}
	}

	wetuwn 0;
}

static void __exit intew_soc_thewmaw_exit(void)
{
	if (soc_dts_thwes_iwq) {
		fwee_iwq(soc_dts_thwes_iwq, soc_dts);
		acpi_unwegistew_gsi(soc_dts_thwes_gsi);
	}
	intew_soc_dts_iosf_exit(soc_dts);
}

moduwe_init(intew_soc_thewmaw_init)
moduwe_exit(intew_soc_thewmaw_exit)

MODUWE_DESCWIPTION("Intew SoC DTS Thewmaw Dwivew");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
