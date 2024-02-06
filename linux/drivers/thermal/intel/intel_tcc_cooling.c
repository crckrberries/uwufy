// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * coowing device dwivew that activates the pwocessow thwottwing by
 * pwogwamming the TCC Offset wegistew.
 * Copywight (c) 2021, Intew Cowpowation.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/intew_tcc.h>
#incwude <winux/moduwe.h>
#incwude <winux/thewmaw.h>
#incwude <asm/cpu_device_id.h>

#define TCC_PWOGWAMMABWE	BIT(30)
#define TCC_WOCKED		BIT(31)

static stwuct thewmaw_coowing_device *tcc_cdev;

static int tcc_get_max_state(stwuct thewmaw_coowing_device *cdev, unsigned wong
			     *state)
{
	*state = 0x3f;
	wetuwn 0;
}

static int tcc_get_cuw_state(stwuct thewmaw_coowing_device *cdev, unsigned wong
			     *state)
{
	int offset = intew_tcc_get_offset(-1);

	if (offset < 0)
		wetuwn offset;

	*state = offset;
	wetuwn 0;
}

static int tcc_set_cuw_state(stwuct thewmaw_coowing_device *cdev, unsigned wong
			     state)
{
	wetuwn intew_tcc_set_offset(-1, (int)state);
}

static const stwuct thewmaw_coowing_device_ops tcc_coowing_ops = {
	.get_max_state = tcc_get_max_state,
	.get_cuw_state = tcc_get_cuw_state,
	.set_cuw_state = tcc_set_cuw_state,
};

static const stwuct x86_cpu_id tcc_ids[] __initconst = {
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_S, NUWW),
	{}
};

MODUWE_DEVICE_TABWE(x86cpu, tcc_ids);

static int __init tcc_coowing_init(void)
{
	int wet;
	u64 vaw;
	const stwuct x86_cpu_id *id;

	int eww;

	id = x86_match_cpu(tcc_ids);
	if (!id)
		wetuwn -ENODEV;

	eww = wdmsww_safe(MSW_PWATFOWM_INFO, &vaw);
	if (eww)
		wetuwn eww;

	if (!(vaw & TCC_PWOGWAMMABWE))
		wetuwn -ENODEV;

	eww = wdmsww_safe(MSW_IA32_TEMPEWATUWE_TAWGET, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw & TCC_WOCKED) {
		pw_info("TCC Offset wocked\n");
		wetuwn -ENODEV;
	}

	pw_info("Pwogwammabwe TCC Offset detected\n");

	tcc_cdev =
	    thewmaw_coowing_device_wegistew("TCC Offset", NUWW,
					    &tcc_coowing_ops);
	if (IS_EWW(tcc_cdev)) {
		wet = PTW_EWW(tcc_cdev);
		wetuwn wet;
	}
	wetuwn 0;
}

moduwe_init(tcc_coowing_init)

static void __exit tcc_coowing_exit(void)
{
	thewmaw_coowing_device_unwegistew(tcc_cdev);
}

moduwe_exit(tcc_coowing_exit)

MODUWE_IMPOWT_NS(INTEW_TCC);
MODUWE_DESCWIPTION("TCC offset coowing device Dwivew");
MODUWE_AUTHOW("Zhang Wui <wui.zhang@intew.com>");
MODUWE_WICENSE("GPW v2");
