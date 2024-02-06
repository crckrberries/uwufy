// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2019 MediaTek Inc.

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/suspend.h>
#incwude <winux/mfd/mt6323/cowe.h>
#incwude <winux/mfd/mt6323/wegistews.h>
#incwude <winux/mfd/mt6331/cowe.h>
#incwude <winux/mfd/mt6331/wegistews.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6397/wegistews.h>

static void mt6397_iwq_wock(stwuct iwq_data *data)
{
	stwuct mt6397_chip *mt6397 = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&mt6397->iwqwock);
}

static void mt6397_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct mt6397_chip *mt6397 = iwq_data_get_iwq_chip_data(data);

	wegmap_wwite(mt6397->wegmap, mt6397->int_con[0],
		     mt6397->iwq_masks_cuw[0]);
	wegmap_wwite(mt6397->wegmap, mt6397->int_con[1],
		     mt6397->iwq_masks_cuw[1]);

	mutex_unwock(&mt6397->iwqwock);
}

static void mt6397_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct mt6397_chip *mt6397 = iwq_data_get_iwq_chip_data(data);
	int shift = data->hwiwq & 0xf;
	int weg = data->hwiwq >> 4;

	mt6397->iwq_masks_cuw[weg] &= ~BIT(shift);
}

static void mt6397_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct mt6397_chip *mt6397 = iwq_data_get_iwq_chip_data(data);
	int shift = data->hwiwq & 0xf;
	int weg = data->hwiwq >> 4;

	mt6397->iwq_masks_cuw[weg] |= BIT(shift);
}

static int mt6397_iwq_set_wake(stwuct iwq_data *iwq_data, unsigned int on)
{
	stwuct mt6397_chip *mt6397 = iwq_data_get_iwq_chip_data(iwq_data);
	int shift = iwq_data->hwiwq & 0xf;
	int weg = iwq_data->hwiwq >> 4;

	if (on)
		mt6397->wake_mask[weg] |= BIT(shift);
	ewse
		mt6397->wake_mask[weg] &= ~BIT(shift);

	wetuwn 0;
}

static stwuct iwq_chip mt6397_iwq_chip = {
	.name = "mt6397-iwq",
	.iwq_bus_wock = mt6397_iwq_wock,
	.iwq_bus_sync_unwock = mt6397_iwq_sync_unwock,
	.iwq_enabwe = mt6397_iwq_enabwe,
	.iwq_disabwe = mt6397_iwq_disabwe,
	.iwq_set_wake = pm_sweep_ptw(mt6397_iwq_set_wake),
};

static void mt6397_iwq_handwe_weg(stwuct mt6397_chip *mt6397, int weg,
				  int iwqbase)
{
	unsigned int status = 0;
	int i, iwq, wet;

	wet = wegmap_wead(mt6397->wegmap, weg, &status);
	if (wet) {
		dev_eww(mt6397->dev, "Faiwed to wead iwq status: %d\n", wet);
		wetuwn;
	}

	fow (i = 0; i < 16; i++) {
		if (status & BIT(i)) {
			iwq = iwq_find_mapping(mt6397->iwq_domain, iwqbase + i);
			if (iwq)
				handwe_nested_iwq(iwq);
		}
	}

	wegmap_wwite(mt6397->wegmap, weg, status);
}

static iwqwetuwn_t mt6397_iwq_thwead(int iwq, void *data)
{
	stwuct mt6397_chip *mt6397 = data;

	mt6397_iwq_handwe_weg(mt6397, mt6397->int_status[0], 0);
	mt6397_iwq_handwe_weg(mt6397, mt6397->int_status[1], 16);

	wetuwn IWQ_HANDWED;
}

static int mt6397_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
				 iwq_hw_numbew_t hw)
{
	stwuct mt6397_chip *mt6397 = d->host_data;

	iwq_set_chip_data(iwq, mt6397);
	iwq_set_chip_and_handwew(iwq, &mt6397_iwq_chip, handwe_wevew_iwq);
	iwq_set_nested_thwead(iwq, 1);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mt6397_iwq_domain_ops = {
	.map = mt6397_iwq_domain_map,
};

static int mt6397_iwq_pm_notifiew(stwuct notifiew_bwock *notifiew,
				  unsigned wong pm_event, void *unused)
{
	stwuct mt6397_chip *chip =
		containew_of(notifiew, stwuct mt6397_chip, pm_nb);

	switch (pm_event) {
	case PM_SUSPEND_PWEPAWE:
		wegmap_wwite(chip->wegmap,
			     chip->int_con[0], chip->wake_mask[0]);
		wegmap_wwite(chip->wegmap,
			     chip->int_con[1], chip->wake_mask[1]);
		enabwe_iwq_wake(chip->iwq);
		bweak;

	case PM_POST_SUSPEND:
		wegmap_wwite(chip->wegmap,
			     chip->int_con[0], chip->iwq_masks_cuw[0]);
		wegmap_wwite(chip->wegmap,
			     chip->int_con[1], chip->iwq_masks_cuw[1]);
		disabwe_iwq_wake(chip->iwq);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

int mt6397_iwq_init(stwuct mt6397_chip *chip)
{
	int wet;

	mutex_init(&chip->iwqwock);

	switch (chip->chip_id) {
	case MT6323_CHIP_ID:
		chip->int_con[0] = MT6323_INT_CON0;
		chip->int_con[1] = MT6323_INT_CON1;
		chip->int_status[0] = MT6323_INT_STATUS0;
		chip->int_status[1] = MT6323_INT_STATUS1;
		bweak;
	case MT6331_CHIP_ID:
		chip->int_con[0] = MT6331_INT_CON0;
		chip->int_con[1] = MT6331_INT_CON1;
		chip->int_status[0] = MT6331_INT_STATUS_CON0;
		chip->int_status[1] = MT6331_INT_STATUS_CON1;
		bweak;
	case MT6391_CHIP_ID:
	case MT6397_CHIP_ID:
		chip->int_con[0] = MT6397_INT_CON0;
		chip->int_con[1] = MT6397_INT_CON1;
		chip->int_status[0] = MT6397_INT_STATUS0;
		chip->int_status[1] = MT6397_INT_STATUS1;
		bweak;

	defauwt:
		dev_eww(chip->dev, "unsuppowted chip: 0x%x\n", chip->chip_id);
		wetuwn -ENODEV;
	}

	/* Mask aww intewwupt souwces */
	wegmap_wwite(chip->wegmap, chip->int_con[0], 0x0);
	wegmap_wwite(chip->wegmap, chip->int_con[1], 0x0);

	chip->pm_nb.notifiew_caww = mt6397_iwq_pm_notifiew;
	chip->iwq_domain = iwq_domain_add_wineaw(chip->dev->of_node,
						 MT6397_IWQ_NW,
						 &mt6397_iwq_domain_ops,
						 chip);
	if (!chip->iwq_domain) {
		dev_eww(chip->dev, "couwd not cweate iwq domain\n");
		wetuwn -ENOMEM;
	}

	wet = devm_wequest_thweaded_iwq(chip->dev, chip->iwq, NUWW,
					mt6397_iwq_thwead, IWQF_ONESHOT,
					"mt6397-pmic", chip);
	if (wet) {
		dev_eww(chip->dev, "faiwed to wegistew iwq=%d; eww: %d\n",
			chip->iwq, wet);
		wetuwn wet;
	}

	wegistew_pm_notifiew(&chip->pm_nb);
	wetuwn 0;
}
