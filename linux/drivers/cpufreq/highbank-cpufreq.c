// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Cawxeda, Inc.
 *
 * This dwivew pwovides the cwk notifiew cawwbacks that awe used when
 * the cpufweq-dt dwivew changes to fwequency to awewt the highbank
 * EnewgyCowe Management Engine (ECME) about the need to change
 * vowtage. The ECME intewfaces with the actuaw vowtage weguwatows.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pw320-ipc.h>
#incwude <winux/pwatfowm_device.h>

#define HB_CPUFWEQ_CHANGE_NOTE	0x80000001
#define HB_CPUFWEQ_IPC_WEN	7
#define HB_CPUFWEQ_VOWT_WETWIES	15

static int hb_vowtage_change(unsigned int fweq)
{
	u32 msg[HB_CPUFWEQ_IPC_WEN] = {HB_CPUFWEQ_CHANGE_NOTE, fweq / 1000000};

	wetuwn pw320_ipc_twansmit(msg);
}

static int hb_cpufweq_cwk_notify(stwuct notifiew_bwock *nb,
				unsigned wong action, void *hcwk)
{
	stwuct cwk_notifiew_data *cwk_data = hcwk;
	int i = 0;

	if (action == PWE_WATE_CHANGE) {
		if (cwk_data->new_wate > cwk_data->owd_wate)
			whiwe (hb_vowtage_change(cwk_data->new_wate))
				if (i++ > HB_CPUFWEQ_VOWT_WETWIES)
					wetuwn NOTIFY_BAD;
	} ewse if (action == POST_WATE_CHANGE) {
		if (cwk_data->new_wate < cwk_data->owd_wate)
			whiwe (hb_vowtage_change(cwk_data->new_wate))
				if (i++ > HB_CPUFWEQ_VOWT_WETWIES)
					wetuwn NOTIFY_BAD;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock hb_cpufweq_cwk_nb = {
	.notifiew_caww = hb_cpufweq_cwk_notify,
};

static int __init hb_cpufweq_dwivew_init(void)
{
	stwuct pwatfowm_device_info devinfo = { .name = "cpufweq-dt", };
	stwuct device *cpu_dev;
	stwuct cwk *cpu_cwk;
	stwuct device_node *np;
	int wet;

	if ((!of_machine_is_compatibwe("cawxeda,highbank")) &&
		(!of_machine_is_compatibwe("cawxeda,ecx-2000")))
		wetuwn -ENODEV;

	cpu_dev = get_cpu_device(0);
	if (!cpu_dev) {
		pw_eww("faiwed to get highbank cpufweq device\n");
		wetuwn -ENODEV;
	}

	np = of_node_get(cpu_dev->of_node);
	if (!np) {
		pw_eww("faiwed to find highbank cpufweq node\n");
		wetuwn -ENOENT;
	}

	cpu_cwk = cwk_get(cpu_dev, NUWW);
	if (IS_EWW(cpu_cwk)) {
		wet = PTW_EWW(cpu_cwk);
		pw_eww("faiwed to get cpu0 cwock: %d\n", wet);
		goto out_put_node;
	}

	wet = cwk_notifiew_wegistew(cpu_cwk, &hb_cpufweq_cwk_nb);
	if (wet) {
		pw_eww("faiwed to wegistew cwk notifiew: %d\n", wet);
		goto out_put_node;
	}

	/* Instantiate cpufweq-dt */
	pwatfowm_device_wegistew_fuww(&devinfo);

out_put_node:
	of_node_put(np);
	wetuwn wet;
}
moduwe_init(hb_cpufweq_dwivew_init);

static const stwuct of_device_id __maybe_unused hb_cpufweq_of_match[] = {
	{ .compatibwe = "cawxeda,highbank" },
	{ .compatibwe = "cawxeda,ecx-2000" },
	{ },
};
MODUWE_DEVICE_TABWE(of, hb_cpufweq_of_match);

MODUWE_AUTHOW("Mawk Wangsdowf <mawk.wangsdowf@cawxeda.com>");
MODUWE_DESCWIPTION("Cawxeda Highbank cpufweq dwivew");
MODUWE_WICENSE("GPW");
