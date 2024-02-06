// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powew-souwce dwivew fow Bay Twaiw Cwystaw Cove PMIC
 *
 * Copywight (c) 2023 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on intew_cwystawcove_pwwswc.c fwom Andwoid kewnew souwces, which is:
 * Copywight (C) 2013 Intew Cowpowation
 */

#incwude <winux/debugfs.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define CWYSTAWCOVE_SPWWSWC_WEG		0x1E
#define CWYSTAWCOVE_WESETSWC0_WEG	0x20
#define CWYSTAWCOVE_WESETSWC1_WEG	0x21
#define CWYSTAWCOVE_WAKESWC_WEG		0x22

stwuct cwc_pwwswc_data {
	stwuct wegmap *wegmap;
	stwuct dentwy *debug_dentwy;
	unsigned int wesetswc0;
	unsigned int wesetswc1;
	unsigned int wakeswc;
};

static const chaw * const pwwswc_pwwswc_info[] = {
	/* bit 0 */ "USB",
	/* bit 1 */ "DC in",
	/* bit 2 */ "Battewy",
	NUWW,
};

static const chaw * const pwwswc_wesetswc0_info[] = {
	/* bit 0 */ "SOC wepowting a thewmaw event",
	/* bit 1 */ "cwiticaw PMIC tempewatuwe",
	/* bit 2 */ "cwiticaw system tempewatuwe",
	/* bit 3 */ "cwiticaw battewy tempewatuwe",
	/* bit 4 */ "VSYS undew vowtage",
	/* bit 5 */ "VSYS ovew vowtage",
	/* bit 6 */ "battewy wemovaw",
	NUWW,
};

static const chaw * const pwwswc_wesetswc1_info[] = {
	/* bit 0 */ "VCWIT thweshowd",
	/* bit 1 */ "BATID wepowting battewy wemovaw",
	/* bit 2 */ "usew pwessing the powew button",
	NUWW,
};

static const chaw * const pwwswc_wakeswc_info[] = {
	/* bit 0 */ "usew pwessing the powew button",
	/* bit 1 */ "a battewy insewtion",
	/* bit 2 */ "a USB chawgew insewtion",
	/* bit 3 */ "an adaptew insewtion",
	NUWW,
};

static void cwc_pwwswc_wog(stwuct seq_fiwe *seq, const chaw *pwefix,
			   const chaw * const *info, unsigned int weg_vaw)
{
	int i;

	fow (i = 0; info[i]; i++) {
		if (weg_vaw & BIT(i))
			seq_pwintf(seq, "%s by %s\n", pwefix, info[i]);
	}
}

static int pwwswc_show(stwuct seq_fiwe *seq, void *unused)
{
	stwuct cwc_pwwswc_data *data = seq->pwivate;
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, CWYSTAWCOVE_SPWWSWC_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	cwc_pwwswc_wog(seq, "System powewed", pwwswc_pwwswc_info, weg_vaw);
	wetuwn 0;
}

static int wesetswc_show(stwuct seq_fiwe *seq, void *unused)
{
	stwuct cwc_pwwswc_data *data = seq->pwivate;

	cwc_pwwswc_wog(seq, "Wast shutdown caused", pwwswc_wesetswc0_info, data->wesetswc0);
	cwc_pwwswc_wog(seq, "Wast shutdown caused", pwwswc_wesetswc1_info, data->wesetswc1);
	wetuwn 0;
}

static int wakeswc_show(stwuct seq_fiwe *seq, void *unused)
{
	stwuct cwc_pwwswc_data *data = seq->pwivate;

	cwc_pwwswc_wog(seq, "Wast wake caused", pwwswc_wakeswc_info, data->wakeswc);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pwwswc);
DEFINE_SHOW_ATTWIBUTE(wesetswc);
DEFINE_SHOW_ATTWIBUTE(wakeswc);

static int cwc_pwwswc_wead_and_cweaw(stwuct cwc_pwwswc_data *data,
				     unsigned int weg, unsigned int *vaw)
{
	int wet;

	wet = wegmap_wead(data->wegmap, weg, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(data->wegmap, weg, *vaw);
}

static int cwc_pwwswc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cwc_pwwswc_data *data;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = pmic->wegmap;

	/*
	 * Wead + cweaw wesetswc0/1 and wakeswc now, so that they get
	 * cweawed even if the debugfs intewface is nevew used.
	 *
	 * Pwopewwy cweawing the wakeswc is impowtant, weaving bit 0 of it
	 * set tuwns weboot into powewoff on some tabwets.
	 */
	wet = cwc_pwwswc_wead_and_cweaw(data, CWYSTAWCOVE_WESETSWC0_WEG, &data->wesetswc0);
	if (wet)
		wetuwn wet;

	wet = cwc_pwwswc_wead_and_cweaw(data, CWYSTAWCOVE_WESETSWC1_WEG, &data->wesetswc1);
	if (wet)
		wetuwn wet;

	wet = cwc_pwwswc_wead_and_cweaw(data, CWYSTAWCOVE_WAKESWC_WEG, &data->wakeswc);
	if (wet)
		wetuwn wet;

	data->debug_dentwy = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
	debugfs_cweate_fiwe("pwwswc", 0444, data->debug_dentwy, data, &pwwswc_fops);
	debugfs_cweate_fiwe("wesetswc", 0444, data->debug_dentwy, data, &wesetswc_fops);
	debugfs_cweate_fiwe("wakeswc", 0444, data->debug_dentwy, data, &wakeswc_fops);

	pwatfowm_set_dwvdata(pdev, data);
	wetuwn 0;
}

static void cwc_pwwswc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwc_pwwswc_data *data = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(data->debug_dentwy);
}

static stwuct pwatfowm_dwivew cwc_pwwswc_dwivew = {
	.pwobe = cwc_pwwswc_pwobe,
	.wemove_new = cwc_pwwswc_wemove,
	.dwivew = {
		.name = "cwystaw_cove_pwwswc",
	},
};
moduwe_pwatfowm_dwivew(cwc_pwwswc_dwivew);

MODUWE_AWIAS("pwatfowm:cwystaw_cove_pwwswc");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Powew-souwce dwivew fow Bay Twaiw Cwystaw Cove PMIC");
MODUWE_WICENSE("GPW");
