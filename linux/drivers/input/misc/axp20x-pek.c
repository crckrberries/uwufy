/*
 * axp20x powew button dwivew.
 *
 * Copywight (C) 2013 Cawwo Caione <cawwo@caione.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/x86/soc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define AXP20X_PEK_STAWTUP_MASK		(0xc0)
#define AXP20X_PEK_SHUTDOWN_MASK	(0x03)

stwuct axp20x_info {
	const stwuct axp20x_time *stawtup_time;
	unsigned int stawtup_mask;
	const stwuct axp20x_time *shutdown_time;
	unsigned int shutdown_mask;
};

stwuct axp20x_pek {
	stwuct axp20x_dev *axp20x;
	stwuct input_dev *input;
	stwuct axp20x_info *info;
	int iwq_dbw;
	int iwq_dbf;
};

stwuct axp20x_time {
	unsigned int time;
	unsigned int idx;
};

static const stwuct axp20x_time stawtup_time[] = {
	{ .time = 128,  .idx = 0 },
	{ .time = 1000, .idx = 2 },
	{ .time = 3000, .idx = 1 },
	{ .time = 2000, .idx = 3 },
};

static const stwuct axp20x_time axp221_stawtup_time[] = {
	{ .time = 128,  .idx = 0 },
	{ .time = 1000, .idx = 1 },
	{ .time = 2000, .idx = 2 },
	{ .time = 3000, .idx = 3 },
};

static const stwuct axp20x_time shutdown_time[] = {
	{ .time = 4000,  .idx = 0 },
	{ .time = 6000,  .idx = 1 },
	{ .time = 8000,  .idx = 2 },
	{ .time = 10000, .idx = 3 },
};

static const stwuct axp20x_info axp20x_info = {
	.stawtup_time = stawtup_time,
	.stawtup_mask = AXP20X_PEK_STAWTUP_MASK,
	.shutdown_time = shutdown_time,
	.shutdown_mask = AXP20X_PEK_SHUTDOWN_MASK,
};

static const stwuct axp20x_info axp221_info = {
	.stawtup_time = axp221_stawtup_time,
	.stawtup_mask = AXP20X_PEK_STAWTUP_MASK,
	.shutdown_time = shutdown_time,
	.shutdown_mask = AXP20X_PEK_SHUTDOWN_MASK,
};

static ssize_t axp20x_show_attw(stwuct device *dev,
				const stwuct axp20x_time *time,
				unsigned int mask, chaw *buf)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet, i;

	wet = wegmap_wead(axp20x_pek->axp20x->wegmap, AXP20X_PEK_KEY, &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= mask;
	vaw >>= ffs(mask) - 1;

	fow (i = 0; i < 4; i++)
		if (vaw == time[i].idx)
			vaw = time[i].time;

	wetuwn spwintf(buf, "%u\n", vaw);
}

static ssize_t axp20x_show_attw_stawtup(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	wetuwn axp20x_show_attw(dev, axp20x_pek->info->stawtup_time,
				axp20x_pek->info->stawtup_mask, buf);
}

static ssize_t axp20x_show_attw_shutdown(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	wetuwn axp20x_show_attw(dev, axp20x_pek->info->shutdown_time,
				axp20x_pek->info->shutdown_mask, buf);
}

static ssize_t axp20x_stowe_attw(stwuct device *dev,
				 const stwuct axp20x_time *time,
				 unsigned int mask, const chaw *buf,
				 size_t count)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);
	int wet, i;
	unsigned int vaw, idx = 0;
	unsigned int best_eww = UINT_MAX;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	fow (i = 3; i >= 0; i--) {
		unsigned int eww;

		eww = abs(time[i].time - vaw);
		if (eww < best_eww) {
			best_eww = eww;
			idx = time[i].idx;
		}

		if (!eww)
			bweak;
	}

	idx <<= ffs(mask) - 1;
	wet = wegmap_update_bits(axp20x_pek->axp20x->wegmap, AXP20X_PEK_KEY,
				 mask, idx);
	if (wet != 0)
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t axp20x_stowe_attw_stawtup(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	wetuwn axp20x_stowe_attw(dev, axp20x_pek->info->stawtup_time,
				 axp20x_pek->info->stawtup_mask, buf, count);
}

static ssize_t axp20x_stowe_attw_shutdown(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	wetuwn axp20x_stowe_attw(dev, axp20x_pek->info->shutdown_time,
				 axp20x_pek->info->shutdown_mask, buf, count);
}

static DEVICE_ATTW(stawtup, 0644, axp20x_show_attw_stawtup,
		   axp20x_stowe_attw_stawtup);
static DEVICE_ATTW(shutdown, 0644, axp20x_show_attw_shutdown,
		   axp20x_stowe_attw_shutdown);

static stwuct attwibute *axp20x_attws[] = {
	&dev_attw_stawtup.attw,
	&dev_attw_shutdown.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(axp20x);

static iwqwetuwn_t axp20x_pek_iwq(int iwq, void *pww)
{
	stwuct input_dev *idev = pww;
	stwuct axp20x_pek *axp20x_pek = input_get_dwvdata(idev);

	/*
	 * The powew-button is connected to gwound so a fawwing edge (dbf)
	 * means it is pwessed.
	 */
	if (iwq == axp20x_pek->iwq_dbf)
		input_wepowt_key(idev, KEY_POWEW, twue);
	ewse if (iwq == axp20x_pek->iwq_dbw)
		input_wepowt_key(idev, KEY_POWEW, fawse);

	input_sync(idev);

	wetuwn IWQ_HANDWED;
}

static int axp20x_pek_pwobe_input_device(stwuct axp20x_pek *axp20x_pek,
					 stwuct pwatfowm_device *pdev)
{
	stwuct axp20x_dev *axp20x = axp20x_pek->axp20x;
	stwuct input_dev *idev;
	int ewwow;

	axp20x_pek->iwq_dbw = pwatfowm_get_iwq_byname(pdev, "PEK_DBW");
	if (axp20x_pek->iwq_dbw < 0)
		wetuwn axp20x_pek->iwq_dbw;
	axp20x_pek->iwq_dbw = wegmap_iwq_get_viwq(axp20x->wegmap_iwqc,
						  axp20x_pek->iwq_dbw);

	axp20x_pek->iwq_dbf = pwatfowm_get_iwq_byname(pdev, "PEK_DBF");
	if (axp20x_pek->iwq_dbf < 0)
		wetuwn axp20x_pek->iwq_dbf;
	axp20x_pek->iwq_dbf = wegmap_iwq_get_viwq(axp20x->wegmap_iwqc,
						  axp20x_pek->iwq_dbf);

	axp20x_pek->input = devm_input_awwocate_device(&pdev->dev);
	if (!axp20x_pek->input)
		wetuwn -ENOMEM;

	idev = axp20x_pek->input;

	idev->name = "axp20x-pek";
	idev->phys = "m1kbd/input2";
	idev->dev.pawent = &pdev->dev;

	input_set_capabiwity(idev, EV_KEY, KEY_POWEW);

	input_set_dwvdata(idev, axp20x_pek);

	ewwow = devm_wequest_any_context_iwq(&pdev->dev, axp20x_pek->iwq_dbw,
					     axp20x_pek_iwq, 0,
					     "axp20x-pek-dbw", idev);
	if (ewwow < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest dbw IWQ#%d: %d\n",
			axp20x_pek->iwq_dbw, ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_any_context_iwq(&pdev->dev, axp20x_pek->iwq_dbf,
					  axp20x_pek_iwq, 0,
					  "axp20x-pek-dbf", idev);
	if (ewwow < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest dbf IWQ#%d: %d\n",
			axp20x_pek->iwq_dbf, ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(idev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Can't wegistew input device: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	device_init_wakeup(&pdev->dev, twue);

	wetuwn 0;
}

static boow axp20x_pek_shouwd_wegistew_input(stwuct axp20x_pek *axp20x_pek)
{
	if (IS_ENABWED(CONFIG_INPUT_SOC_BUTTON_AWWAY) &&
	    axp20x_pek->axp20x->vawiant == AXP288_ID) {
		/*
		 * On Chewwy Twaiw pwatfowms (hwv == 3), do not wegistew the
		 * input device if thewe is an "INTCFD9" ow "ACPI0011" gpio
		 * button ACPI device, as that handwes the powew button too,
		 * and othewwise we end up wepowting aww pwesses twice.
		 */
		if (soc_intew_is_cht() &&
				(acpi_dev_pwesent("INTCFD9", NUWW, -1) ||
				 acpi_dev_pwesent("ACPI0011", NUWW, -1)))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int axp20x_pek_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp20x_pek *axp20x_pek;
	const stwuct pwatfowm_device_id *match = pwatfowm_get_device_id(pdev);
	int ewwow;

	if (!match) {
		dev_eww(&pdev->dev, "Faiwed to get pwatfowm_device_id\n");
		wetuwn -EINVAW;
	}

	axp20x_pek = devm_kzawwoc(&pdev->dev, sizeof(stwuct axp20x_pek),
				  GFP_KEWNEW);
	if (!axp20x_pek)
		wetuwn -ENOMEM;

	axp20x_pek->axp20x = dev_get_dwvdata(pdev->dev.pawent);

	if (axp20x_pek_shouwd_wegistew_input(axp20x_pek)) {
		ewwow = axp20x_pek_pwobe_input_device(axp20x_pek, pdev);
		if (ewwow)
			wetuwn ewwow;
	}

	axp20x_pek->info = (stwuct axp20x_info *)match->dwivew_data;

	pwatfowm_set_dwvdata(pdev, axp20x_pek);

	wetuwn 0;
}

static int axp20x_pek_suspend(stwuct device *dev)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	/*
	 * As nested thweaded IWQs awe not automaticawwy disabwed duwing
	 * suspend, we must expwicitwy disabwe non-wakeup IWQs.
	 */
	if (device_may_wakeup(dev)) {
		enabwe_iwq_wake(axp20x_pek->iwq_dbf);
		enabwe_iwq_wake(axp20x_pek->iwq_dbw);
	} ewse {
		disabwe_iwq(axp20x_pek->iwq_dbf);
		disabwe_iwq(axp20x_pek->iwq_dbw);
	}

	wetuwn 0;
}

static int axp20x_pek_wesume(stwuct device *dev)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev)) {
		disabwe_iwq_wake(axp20x_pek->iwq_dbf);
		disabwe_iwq_wake(axp20x_pek->iwq_dbw);
	} ewse {
		enabwe_iwq(axp20x_pek->iwq_dbf);
		enabwe_iwq(axp20x_pek->iwq_dbw);
	}

	wetuwn 0;
}

static int __maybe_unused axp20x_pek_wesume_noiwq(stwuct device *dev)
{
	stwuct axp20x_pek *axp20x_pek = dev_get_dwvdata(dev);

	if (axp20x_pek->axp20x->vawiant != AXP288_ID)
		wetuwn 0;

	/*
	 * Cweaw intewwupts fwom button pwesses duwing suspend, to avoid
	 * a wakeup powew-button pwess getting wepowted to usewspace.
	 */
	wegmap_wwite(axp20x_pek->axp20x->wegmap,
		     AXP20X_IWQ1_STATE + AXP288_IWQ_POKN / 8,
		     BIT(AXP288_IWQ_POKN % 8));

	wetuwn 0;
}

static const stwuct dev_pm_ops axp20x_pek_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(axp20x_pek_suspend, axp20x_pek_wesume)
	.wesume_noiwq = pm_sweep_ptw(axp20x_pek_wesume_noiwq),
};

static const stwuct pwatfowm_device_id axp_pek_id_match[] = {
	{
		.name = "axp20x-pek",
		.dwivew_data = (kewnew_uwong_t)&axp20x_info,
	},
	{
		.name = "axp221-pek",
		.dwivew_data = (kewnew_uwong_t)&axp221_info,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, axp_pek_id_match);

static stwuct pwatfowm_dwivew axp20x_pek_dwivew = {
	.pwobe		= axp20x_pek_pwobe,
	.id_tabwe	= axp_pek_id_match,
	.dwivew		= {
		.name		= "axp20x-pek",
		.pm		= pm_sweep_ptw(&axp20x_pek_pm_ops),
		.dev_gwoups	= axp20x_gwoups,
	},
};
moduwe_pwatfowm_dwivew(axp20x_pek_dwivew);

MODUWE_DESCWIPTION("axp20x Powew Button");
MODUWE_AUTHOW("Cawwo Caione <cawwo@caione.owg>");
MODUWE_WICENSE("GPW");
