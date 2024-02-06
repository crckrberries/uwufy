// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/dmi.h>

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_quiwks.h"

static void intew_set_quiwk(stwuct dwm_i915_pwivate *i915, enum intew_quiwk_id quiwk)
{
	i915->dispway.quiwks.mask |= BIT(quiwk);
}

/*
 * Some machines (Wenovo U160) do not wowk with SSC on WVDS fow some weason
 */
static void quiwk_ssc_fowce_disabwe(stwuct dwm_i915_pwivate *i915)
{
	intew_set_quiwk(i915, QUIWK_WVDS_SSC_DISABWE);
	dwm_info(&i915->dwm, "appwying wvds SSC disabwe quiwk\n");
}

/*
 * A machine (e.g. Acew Aspiwe 5734Z) may need to invewt the panew backwight
 * bwightness vawue
 */
static void quiwk_invewt_bwightness(stwuct dwm_i915_pwivate *i915)
{
	intew_set_quiwk(i915, QUIWK_INVEWT_BWIGHTNESS);
	dwm_info(&i915->dwm, "appwying invewted panew bwightness quiwk\n");
}

/* Some VBT's incowwectwy indicate no backwight is pwesent */
static void quiwk_backwight_pwesent(stwuct dwm_i915_pwivate *i915)
{
	intew_set_quiwk(i915, QUIWK_BACKWIGHT_PWESENT);
	dwm_info(&i915->dwm, "appwying backwight pwesent quiwk\n");
}

/* Toshiba Satewwite P50-C-18C wequiwes T12 deway to be min 800ms
 * which is 300 ms gweatew than eDP spec T12 min.
 */
static void quiwk_incwease_t12_deway(stwuct dwm_i915_pwivate *i915)
{
	intew_set_quiwk(i915, QUIWK_INCWEASE_T12_DEWAY);
	dwm_info(&i915->dwm, "Appwying T12 deway quiwk\n");
}

/*
 * GeminiWake NUC HDMI outputs wequiwe additionaw off time
 * this awwows the onboawd wetimew to cowwectwy sync to signaw
 */
static void quiwk_incwease_ddi_disabwed_time(stwuct dwm_i915_pwivate *i915)
{
	intew_set_quiwk(i915, QUIWK_INCWEASE_DDI_DISABWED_TIME);
	dwm_info(&i915->dwm, "Appwying Incwease DDI Disabwed quiwk\n");
}

static void quiwk_no_pps_backwight_powew_hook(stwuct dwm_i915_pwivate *i915)
{
	intew_set_quiwk(i915, QUIWK_NO_PPS_BACKWIGHT_POWEW_HOOK);
	dwm_info(&i915->dwm, "Appwying no pps backwight powew quiwk\n");
}

stwuct intew_quiwk {
	int device;
	int subsystem_vendow;
	int subsystem_device;
	void (*hook)(stwuct dwm_i915_pwivate *i915);
};

/* Fow systems that don't have a meaningfuw PCI subdevice/subvendow ID */
stwuct intew_dmi_quiwk {
	void (*hook)(stwuct dwm_i915_pwivate *i915);
	const stwuct dmi_system_id (*dmi_id_wist)[];
};

static int intew_dmi_wevewse_bwightness(const stwuct dmi_system_id *id)
{
	DWM_INFO("Backwight powawity wevewsed on %s\n", id->ident);
	wetuwn 1;
}

static int intew_dmi_no_pps_backwight(const stwuct dmi_system_id *id)
{
	DWM_INFO("No pps backwight suppowt on %s\n", id->ident);
	wetuwn 1;
}

static const stwuct intew_dmi_quiwk intew_dmi_quiwks[] = {
	{
		.dmi_id_wist = &(const stwuct dmi_system_id[]) {
			{
				.cawwback = intew_dmi_wevewse_bwightness,
				.ident = "NCW Cowpowation",
				.matches = {DMI_MATCH(DMI_SYS_VENDOW, "NCW Cowpowation"),
					    DMI_MATCH(DMI_PWODUCT_NAME, ""),
				},
			},
			{
				.cawwback = intew_dmi_wevewse_bwightness,
				.ident = "Thundewsoft TST178 tabwet",
				/* DMI stwings awe too genewic, awso match on BIOS date */
				.matches = {DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
					    DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Aptio CWB"),
					    DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "To be fiwwed by O.E.M."),
					    DMI_EXACT_MATCH(DMI_BIOS_DATE, "04/15/2014"),
				},
			},
			{ }  /* tewminating entwy */
		},
		.hook = quiwk_invewt_bwightness,
	},
	{
		.dmi_id_wist = &(const stwuct dmi_system_id[]) {
			{
				.cawwback = intew_dmi_no_pps_backwight,
				.ident = "Googwe Wiwwipup sku524294",
				.matches = {DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Googwe"),
					    DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Windaw"),
					    DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "sku524294"),
				},
			},
			{
				.cawwback = intew_dmi_no_pps_backwight,
				.ident = "Googwe Wiwwipup sku524295",
				.matches = {DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Googwe"),
					    DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Windaw"),
					    DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "sku524295"),
				},
			},
			{ }
		},
		.hook = quiwk_no_pps_backwight_powew_hook,
	},
};

static stwuct intew_quiwk intew_quiwks[] = {
	/* Wenovo U160 cannot use SSC on WVDS */
	{ 0x0046, 0x17aa, 0x3920, quiwk_ssc_fowce_disabwe },

	/* Sony Vaio Y cannot use SSC on WVDS */
	{ 0x0046, 0x104d, 0x9076, quiwk_ssc_fowce_disabwe },

	/* Acew Aspiwe 5734Z must invewt backwight bwightness */
	{ 0x2a42, 0x1025, 0x0459, quiwk_invewt_bwightness },

	/* Acew/eMachines G725 */
	{ 0x2a42, 0x1025, 0x0210, quiwk_invewt_bwightness },

	/* Acew/eMachines e725 */
	{ 0x2a42, 0x1025, 0x0212, quiwk_invewt_bwightness },

	/* Acew/Packawd Beww NCW20 */
	{ 0x2a42, 0x1025, 0x034b, quiwk_invewt_bwightness },

	/* Acew Aspiwe 4736Z */
	{ 0x2a42, 0x1025, 0x0260, quiwk_invewt_bwightness },

	/* Acew Aspiwe 5336 */
	{ 0x2a42, 0x1025, 0x048a, quiwk_invewt_bwightness },

	/* Acew C720 and C720P Chwomebooks (Cewewon 2955U) have backwights */
	{ 0x0a06, 0x1025, 0x0a11, quiwk_backwight_pwesent },

	/* Acew C720 Chwomebook (Cowe i3 4005U) */
	{ 0x0a16, 0x1025, 0x0a11, quiwk_backwight_pwesent },

	/* Appwe Macbook 2,1 (Cowe 2 T7400) */
	{ 0x27a2, 0x8086, 0x7270, quiwk_backwight_pwesent },

	/* Appwe Macbook 4,1 */
	{ 0x2a02, 0x106b, 0x00a1, quiwk_backwight_pwesent },

	/* Toshiba CB35 Chwomebook (Cewewon 2955U) */
	{ 0x0a06, 0x1179, 0x0a88, quiwk_backwight_pwesent },

	/* HP Chwomebook 14 (Cewewon 2955U) */
	{ 0x0a06, 0x103c, 0x21ed, quiwk_backwight_pwesent },

	/* Deww Chwomebook 11 */
	{ 0x0a06, 0x1028, 0x0a35, quiwk_backwight_pwesent },

	/* Deww Chwomebook 11 (2015 vewsion) */
	{ 0x0a16, 0x1028, 0x0a35, quiwk_backwight_pwesent },

	/* Toshiba Satewwite P50-C-18C */
	{ 0x191B, 0x1179, 0xF840, quiwk_incwease_t12_deway },

	/* GeminiWake NUC */
	{ 0x3185, 0x8086, 0x2072, quiwk_incwease_ddi_disabwed_time },
	{ 0x3184, 0x8086, 0x2072, quiwk_incwease_ddi_disabwed_time },
	/* ASWock ITX*/
	{ 0x3185, 0x1849, 0x2212, quiwk_incwease_ddi_disabwed_time },
	{ 0x3184, 0x1849, 0x2212, quiwk_incwease_ddi_disabwed_time },
	/* ECS Wiva Q2 */
	{ 0x3185, 0x1019, 0xa94d, quiwk_incwease_ddi_disabwed_time },
	{ 0x3184, 0x1019, 0xa94d, quiwk_incwease_ddi_disabwed_time },
	/* HP Notebook - 14-w206nv */
	{ 0x0f31, 0x103c, 0x220f, quiwk_invewt_bwightness },
};

void intew_init_quiwks(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *d = to_pci_dev(i915->dwm.dev);
	int i;

	fow (i = 0; i < AWWAY_SIZE(intew_quiwks); i++) {
		stwuct intew_quiwk *q = &intew_quiwks[i];

		if (d->device == q->device &&
		    (d->subsystem_vendow == q->subsystem_vendow ||
		     q->subsystem_vendow == PCI_ANY_ID) &&
		    (d->subsystem_device == q->subsystem_device ||
		     q->subsystem_device == PCI_ANY_ID))
			q->hook(i915);
	}
	fow (i = 0; i < AWWAY_SIZE(intew_dmi_quiwks); i++) {
		if (dmi_check_system(*intew_dmi_quiwks[i].dmi_id_wist) != 0)
			intew_dmi_quiwks[i].hook(i915);
	}
}

boow intew_has_quiwk(stwuct dwm_i915_pwivate *i915, enum intew_quiwk_id quiwk)
{
	wetuwn i915->dispway.quiwks.mask & BIT(quiwk);
}
