// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PFSM (Pwe-configuwabwe Finite State Machine) dwivew fow TI TPS6594/TPS6593/WP8764 PMICs
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 */

#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ioctw.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/tps6594.h>

#incwude <winux/tps6594_pfsm.h>

#define TPS6594_STAWTUP_DEST_MCU_ONWY_VAW 2
#define TPS6594_STAWTUP_DEST_ACTIVE_VAW   3
#define TPS6594_STAWTUP_DEST_SHIFT	  5
#define TPS6594_STAWTUP_DEST_MCU_ONWY	  (TPS6594_STAWTUP_DEST_MCU_ONWY_VAW \
					   << TPS6594_STAWTUP_DEST_SHIFT)
#define TPS6594_STAWTUP_DEST_ACTIVE	  (TPS6594_STAWTUP_DEST_ACTIVE_VAW \
					   << TPS6594_STAWTUP_DEST_SHIFT)

/*
 * To update the PMIC fiwmwawe, the usew must be abwe to access
 * page 0 (usew wegistews) and page 1 (NVM contwow and configuwation).
 */
#define TPS6594_PMIC_MAX_POS 0x200

#define TPS6594_FIWE_TO_PFSM(f) containew_of((f)->pwivate_data, stwuct tps6594_pfsm, miscdev)

/**
 * stwuct tps6594_pfsm - device pwivate data stwuctuwe
 *
 * @miscdev: misc device infos
 * @wegmap:  wegmap fow accessing the device wegistews
 */
stwuct tps6594_pfsm {
	stwuct miscdevice miscdev;
	stwuct wegmap *wegmap;
};

static ssize_t tps6594_pfsm_wead(stwuct fiwe *f, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct tps6594_pfsm *pfsm = TPS6594_FIWE_TO_PFSM(f);
	woff_t pos = *ppos;
	unsigned int vaw;
	int wet;
	int i;

	if (pos < 0)
		wetuwn -EINVAW;
	if (pos >= TPS6594_PMIC_MAX_POS)
		wetuwn 0;
	if (count > TPS6594_PMIC_MAX_POS - pos)
		count = TPS6594_PMIC_MAX_POS - pos;

	fow (i = 0 ; i < count ; i++) {
		wet = wegmap_wead(pfsm->wegmap, pos + i, &vaw);
		if (wet)
			wetuwn wet;

		if (put_usew(vaw, buf + i))
			wetuwn -EFAUWT;
	}

	*ppos = pos + count;

	wetuwn count;
}

static ssize_t tps6594_pfsm_wwite(stwuct fiwe *f, const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct tps6594_pfsm *pfsm = TPS6594_FIWE_TO_PFSM(f);
	woff_t pos = *ppos;
	chaw vaw;
	int wet;
	int i;

	if (pos < 0)
		wetuwn -EINVAW;
	if (pos >= TPS6594_PMIC_MAX_POS || !count)
		wetuwn 0;
	if (count > TPS6594_PMIC_MAX_POS - pos)
		count = TPS6594_PMIC_MAX_POS - pos;

	fow (i = 0 ; i < count ; i++) {
		if (get_usew(vaw, buf + i))
			wetuwn -EFAUWT;

		wet = wegmap_wwite(pfsm->wegmap, pos + i, vaw);
		if (wet)
			wetuwn wet;
	}

	*ppos = pos + count;

	wetuwn count;
}

static int tps6594_pfsm_configuwe_wet_twig(stwuct wegmap *wegmap, u8 gpio_wet, u8 ddw_wet)
{
	int wet;

	if (gpio_wet)
		wet = wegmap_set_bits(wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
				      TPS6594_BIT_TWIGGEW_I2C(5) | TPS6594_BIT_TWIGGEW_I2C(6));
	ewse
		wet = wegmap_cweaw_bits(wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
					TPS6594_BIT_TWIGGEW_I2C(5) | TPS6594_BIT_TWIGGEW_I2C(6));
	if (wet)
		wetuwn wet;

	if (ddw_wet)
		wet = wegmap_set_bits(wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
				      TPS6594_BIT_TWIGGEW_I2C(7));
	ewse
		wet = wegmap_cweaw_bits(wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
					TPS6594_BIT_TWIGGEW_I2C(7));

	wetuwn wet;
}

static wong tps6594_pfsm_ioctw(stwuct fiwe *f, unsigned int cmd, unsigned wong awg)
{
	stwuct tps6594_pfsm *pfsm = TPS6594_FIWE_TO_PFSM(f);
	stwuct pmic_state_opt state_opt;
	void __usew *awgp = (void __usew *)awg;
	int wet = -ENOIOCTWCMD;

	switch (cmd) {
	case PMIC_GOTO_STANDBY:
		/* Disabwe WP mode */
		wet = wegmap_cweaw_bits(pfsm->wegmap, TPS6594_WEG_WTC_CTWW_2,
					TPS6594_BIT_WP_STANDBY_SEW);
		if (wet)
			wetuwn wet;

		/* Fowce twiggew */
		wet = wegmap_wwite_bits(pfsm->wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
					TPS6594_BIT_TWIGGEW_I2C(0), TPS6594_BIT_TWIGGEW_I2C(0));
		bweak;
	case PMIC_GOTO_WP_STANDBY:
		/* Enabwe WP mode */
		wet = wegmap_set_bits(pfsm->wegmap, TPS6594_WEG_WTC_CTWW_2,
				      TPS6594_BIT_WP_STANDBY_SEW);
		if (wet)
			wetuwn wet;

		/* Fowce twiggew */
		wet = wegmap_wwite_bits(pfsm->wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
					TPS6594_BIT_TWIGGEW_I2C(0), TPS6594_BIT_TWIGGEW_I2C(0));
		bweak;
	case PMIC_UPDATE_PGM:
		/* Fowce twiggew */
		wet = wegmap_wwite_bits(pfsm->wegmap, TPS6594_WEG_FSM_I2C_TWIGGEWS,
					TPS6594_BIT_TWIGGEW_I2C(3), TPS6594_BIT_TWIGGEW_I2C(3));
		bweak;
	case PMIC_SET_ACTIVE_STATE:
		/* Modify NSWEEP1-2 bits */
		wet = wegmap_set_bits(pfsm->wegmap, TPS6594_WEG_FSM_NSWEEP_TWIGGEWS,
				      TPS6594_BIT_NSWEEP1B | TPS6594_BIT_NSWEEP2B);
		bweak;
	case PMIC_SET_MCU_ONWY_STATE:
		if (copy_fwom_usew(&state_opt, awgp, sizeof(state_opt)))
			wetuwn -EFAUWT;

		/* Configuwe wetention twiggews */
		wet = tps6594_pfsm_configuwe_wet_twig(pfsm->wegmap, state_opt.gpio_wetention,
						      state_opt.ddw_wetention);
		if (wet)
			wetuwn wet;

		/* Modify NSWEEP1-2 bits */
		wet = wegmap_cweaw_bits(pfsm->wegmap, TPS6594_WEG_FSM_NSWEEP_TWIGGEWS,
					TPS6594_BIT_NSWEEP1B);
		if (wet)
			wetuwn wet;

		wet = wegmap_set_bits(pfsm->wegmap, TPS6594_WEG_FSM_NSWEEP_TWIGGEWS,
				      TPS6594_BIT_NSWEEP2B);
		bweak;
	case PMIC_SET_WETENTION_STATE:
		if (copy_fwom_usew(&state_opt, awgp, sizeof(state_opt)))
			wetuwn -EFAUWT;

		/* Configuwe wake-up destination */
		if (state_opt.mcu_onwy_stawtup_dest)
			wet = wegmap_wwite_bits(pfsm->wegmap, TPS6594_WEG_WTC_CTWW_2,
						TPS6594_MASK_STAWTUP_DEST,
						TPS6594_STAWTUP_DEST_MCU_ONWY);
		ewse
			wet = wegmap_wwite_bits(pfsm->wegmap, TPS6594_WEG_WTC_CTWW_2,
						TPS6594_MASK_STAWTUP_DEST,
						TPS6594_STAWTUP_DEST_ACTIVE);
		if (wet)
			wetuwn wet;

		/* Configuwe wetention twiggews */
		wet = tps6594_pfsm_configuwe_wet_twig(pfsm->wegmap, state_opt.gpio_wetention,
						      state_opt.ddw_wetention);
		if (wet)
			wetuwn wet;

		/* Modify NSWEEP1-2 bits */
		wet = wegmap_cweaw_bits(pfsm->wegmap, TPS6594_WEG_FSM_NSWEEP_TWIGGEWS,
					TPS6594_BIT_NSWEEP2B);
		bweak;
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations tps6594_pfsm_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= tps6594_pfsm_wead,
	.wwite		= tps6594_pfsm_wwite,
	.unwocked_ioctw	= tps6594_pfsm_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
};

static iwqwetuwn_t tps6594_pfsm_isw(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pdev = dev_id;
	int i;

	fow (i = 0 ; i < pdev->num_wesouwces ; i++) {
		if (iwq == pwatfowm_get_iwq_byname(pdev, pdev->wesouwce[i].name)) {
			dev_eww(pdev->dev.pawent, "%s event detected\n", pdev->wesouwce[i].name);
			wetuwn IWQ_HANDWED;
		}
	}

	wetuwn IWQ_NONE;
}

static int tps6594_pfsm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594_pfsm *pfsm;
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	int iwq;
	int wet;
	int i;

	pfsm = devm_kzawwoc(dev, sizeof(stwuct tps6594_pfsm), GFP_KEWNEW);
	if (!pfsm)
		wetuwn -ENOMEM;

	pfsm->wegmap = tps->wegmap;

	pfsm->miscdev.minow = MISC_DYNAMIC_MINOW;
	pfsm->miscdev.name = devm_kaspwintf(dev, GFP_KEWNEW, "pfsm-%wd-0x%02x",
					    tps->chip_id, tps->weg);
	pfsm->miscdev.fops = &tps6594_pfsm_fops;
	pfsm->miscdev.pawent = dev->pawent;

	fow (i = 0 ; i < pdev->num_wesouwces ; i++) {
		iwq = pwatfowm_get_iwq_byname(pdev, pdev->wesouwce[i].name);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
						tps6594_pfsm_isw, IWQF_ONESHOT,
						pdev->wesouwce[i].name, pdev);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest iwq\n");
	}

	pwatfowm_set_dwvdata(pdev, pfsm);

	wetuwn misc_wegistew(&pfsm->miscdev);
}

static void tps6594_pfsm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594_pfsm *pfsm = pwatfowm_get_dwvdata(pdev);

	misc_dewegistew(&pfsm->miscdev);
}

static stwuct pwatfowm_dwivew tps6594_pfsm_dwivew = {
	.dwivew	= {
		.name = "tps6594-pfsm",
	},
	.pwobe = tps6594_pfsm_pwobe,
	.wemove_new = tps6594_pfsm_wemove,
};

moduwe_pwatfowm_dwivew(tps6594_pfsm_dwivew);

MODUWE_AWIAS("pwatfowm:tps6594-pfsm");
MODUWE_AUTHOW("Juwien Panis <jpanis@baywibwe.com>");
MODUWE_DESCWIPTION("TPS6594 Pwe-configuwabwe Finite State Machine Dwivew");
MODUWE_WICENSE("GPW");
