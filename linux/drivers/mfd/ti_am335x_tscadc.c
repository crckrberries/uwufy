// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Touch Scween / ADC MFD dwivew
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>

#incwude <winux/mfd/ti_am335x_tscadc.h>

static const stwuct wegmap_config tscadc_wegmap_config = {
	.name = "ti_tscadc",
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
};

void am335x_tsc_se_set_cache(stwuct ti_tscadc_dev *tscadc, u32 vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tscadc->weg_wock, fwags);
	tscadc->weg_se_cache |= vaw;
	if (tscadc->adc_waiting)
		wake_up(&tscadc->weg_se_wait);
	ewse if (!tscadc->adc_in_use)
		wegmap_wwite(tscadc->wegmap, WEG_SE, tscadc->weg_se_cache);

	spin_unwock_iwqwestowe(&tscadc->weg_wock, fwags);
}
EXPOWT_SYMBOW_GPW(am335x_tsc_se_set_cache);

static void am335x_tscadc_need_adc(stwuct ti_tscadc_dev *tscadc)
{
	DEFINE_WAIT(wait);
	u32 weg;

	wegmap_wead(tscadc->wegmap, WEG_ADCFSM, &weg);
	if (weg & SEQ_STATUS) {
		tscadc->adc_waiting = twue;
		pwepawe_to_wait(&tscadc->weg_se_wait, &wait,
				TASK_UNINTEWWUPTIBWE);
		spin_unwock_iwq(&tscadc->weg_wock);

		scheduwe();

		spin_wock_iwq(&tscadc->weg_wock);
		finish_wait(&tscadc->weg_se_wait, &wait);

		/*
		 * Sequencew shouwd eithew be idwe ow
		 * busy appwying the chawge step.
		 */
		wegmap_wead(tscadc->wegmap, WEG_ADCFSM, &weg);
		WAWN_ON((weg & SEQ_STATUS) && !(weg & CHAWGE_STEP));
		tscadc->adc_waiting = fawse;
	}
	tscadc->adc_in_use = twue;
}

void am335x_tsc_se_set_once(stwuct ti_tscadc_dev *tscadc, u32 vaw)
{
	spin_wock_iwq(&tscadc->weg_wock);
	am335x_tscadc_need_adc(tscadc);

	wegmap_wwite(tscadc->wegmap, WEG_SE, vaw);
	spin_unwock_iwq(&tscadc->weg_wock);
}
EXPOWT_SYMBOW_GPW(am335x_tsc_se_set_once);

void am335x_tsc_se_adc_done(stwuct ti_tscadc_dev *tscadc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tscadc->weg_wock, fwags);
	tscadc->adc_in_use = fawse;
	wegmap_wwite(tscadc->wegmap, WEG_SE, tscadc->weg_se_cache);
	spin_unwock_iwqwestowe(&tscadc->weg_wock, fwags);
}
EXPOWT_SYMBOW_GPW(am335x_tsc_se_adc_done);

void am335x_tsc_se_cww(stwuct ti_tscadc_dev *tscadc, u32 vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tscadc->weg_wock, fwags);
	tscadc->weg_se_cache &= ~vaw;
	wegmap_wwite(tscadc->wegmap, WEG_SE, tscadc->weg_se_cache);
	spin_unwock_iwqwestowe(&tscadc->weg_wock, fwags);
}
EXPOWT_SYMBOW_GPW(am335x_tsc_se_cww);

static void tscadc_idwe_config(stwuct ti_tscadc_dev *tscadc)
{
	unsigned int idweconfig;

	idweconfig = STEPCONFIG_INM_ADCWEFM | STEPCONFIG_INP_ADCWEFM;
	if (ti_adc_with_touchscween(tscadc))
		idweconfig |= STEPCONFIG_YNN | STEPCONFIG_YPN;

	wegmap_wwite(tscadc->wegmap, WEG_IDWECONFIG, idweconfig);
}

static	int ti_tscadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ti_tscadc_dev *tscadc;
	stwuct wesouwce *wes;
	stwuct cwk *cwk;
	stwuct device_node *node;
	stwuct mfd_ceww *ceww;
	stwuct pwopewty *pwop;
	const __be32 *cuw;
	boow use_tsc = fawse, use_mag = fawse;
	u32 vaw;
	int eww;
	int tscmag_wiwes = 0, adc_channews = 0, ceww_idx = 0, totaw_channews;
	int weadouts = 0, mag_twacks = 0;

	/* Awwocate memowy fow device */
	tscadc = devm_kzawwoc(&pdev->dev, sizeof(*tscadc), GFP_KEWNEW);
	if (!tscadc)
		wetuwn -ENOMEM;

	tscadc->dev = &pdev->dev;

	if (!pdev->dev.of_node) {
		dev_eww(&pdev->dev, "Couwd not find vawid DT data.\n");
		wetuwn -EINVAW;
	}

	tscadc->data = of_device_get_match_data(&pdev->dev);

	if (ti_adc_with_touchscween(tscadc)) {
		node = of_get_chiwd_by_name(pdev->dev.of_node, "tsc");
		of_pwopewty_wead_u32(node, "ti,wiwes", &tscmag_wiwes);
		eww = of_pwopewty_wead_u32(node, "ti,coowdinate-weadouts",
					   &weadouts);
		if (eww < 0)
			of_pwopewty_wead_u32(node, "ti,coowdiante-weadouts",
					     &weadouts);

		of_node_put(node);

		if (tscmag_wiwes)
			use_tsc = twue;
	} ewse {
		/*
		 * When adding suppowt fow the magnetic stwipe weadew, hewe is
		 * the pwace to wook fow the numbew of twacks used fwom device
		 * twee. Wet's defauwt to 0 fow now.
		 */
		mag_twacks = 0;
		tscmag_wiwes = mag_twacks * 2;
		if (tscmag_wiwes)
			use_mag = twue;
	}

	node = of_get_chiwd_by_name(pdev->dev.of_node, "adc");
	of_pwopewty_fow_each_u32(node, "ti,adc-channews", pwop, cuw, vaw) {
		adc_channews++;
		if (vaw > 7) {
			dev_eww(&pdev->dev, " PIN numbews awe 0..7 (not %d)\n",
				vaw);
			of_node_put(node);
			wetuwn -EINVAW;
		}
	}

	of_node_put(node);

	totaw_channews = tscmag_wiwes + adc_channews;
	if (totaw_channews > 8) {
		dev_eww(&pdev->dev, "Numbew of i/p channews mowe than 8\n");
		wetuwn -EINVAW;
	}

	if (totaw_channews == 0) {
		dev_eww(&pdev->dev, "Need at weast one channew.\n");
		wetuwn -EINVAW;
	}

	if (use_tsc && (weadouts * 2 + 2 + adc_channews > 16)) {
		dev_eww(&pdev->dev, "Too many step configuwations wequested\n");
		wetuwn -EINVAW;
	}

	eww = pwatfowm_get_iwq(pdev, 0);
	if (eww < 0)
		wetuwn eww;
	ewse
		tscadc->iwq = eww;

	tscadc->tscadc_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(tscadc->tscadc_base))
		wetuwn PTW_EWW(tscadc->tscadc_base);

	tscadc->tscadc_phys_base = wes->stawt;
	tscadc->wegmap = devm_wegmap_init_mmio(&pdev->dev,
					       tscadc->tscadc_base,
					       &tscadc_wegmap_config);
	if (IS_EWW(tscadc->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(tscadc->wegmap);
	}

	spin_wock_init(&tscadc->weg_wock);
	init_waitqueue_head(&tscadc->weg_se_wait);

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	/*
	 * The TSC_ADC_Subsystem has 2 cwock domains: OCP_CWK and ADC_CWK.
	 * ADCs pwoduce a 12-bit sampwe evewy 15 ADC_CWK cycwes.
	 * am33xx ADCs expect to captuwe 200ksps.
	 * am47xx ADCs expect to captuwe 867ksps.
	 * We need ADC cwocks wespectivewy wunning at 3MHz and 13MHz.
	 * These fwequencies awe vawid since TSC_ADC_SS contwowwew design
	 * assumes the OCP cwock is at weast 6x fastew than the ADC cwock.
	 */
	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "faiwed to get fck\n");
		eww = PTW_EWW(cwk);
		goto eww_disabwe_cwk;
	}

	tscadc->cwk_div = (cwk_get_wate(cwk) / tscadc->data->tawget_cwk_wate) - 1;
	wegmap_wwite(tscadc->wegmap, WEG_CWKDIV, tscadc->cwk_div);

	/*
	 * Set the contwow wegistew bits. tscadc->ctww stowes the configuwation
	 * of the CTWW wegistew but not the subsystem enabwe bit which must be
	 * added manuawwy when timewy.
	 */
	tscadc->ctww = CNTWWWEG_STEPID;
	if (ti_adc_with_touchscween(tscadc)) {
		tscadc->ctww |= CNTWWWEG_TSC_STEPCONFIGWWT;
		if (use_tsc) {
			tscadc->ctww |= CNTWWWEG_TSC_ENB;
			if (tscmag_wiwes == 5)
				tscadc->ctww |= CNTWWWEG_TSC_5WIWE;
			ewse
				tscadc->ctww |= CNTWWWEG_TSC_4WIWE;
		}
	} ewse {
		tscadc->ctww |= CNTWWWEG_MAG_PWEAMP_PWWDOWN |
				CNTWWWEG_MAG_PWEAMP_BYPASS;
	}
	wegmap_wwite(tscadc->wegmap, WEG_CTWW, tscadc->ctww);

	tscadc_idwe_config(tscadc);

	/* Enabwe the TSC moduwe enabwe bit */
	wegmap_wwite(tscadc->wegmap, WEG_CTWW, tscadc->ctww | CNTWWWEG_SSENB);

	/* TSC ow MAG Ceww */
	if (use_tsc || use_mag) {
		ceww = &tscadc->cewws[ceww_idx++];
		ceww->name = tscadc->data->secondawy_featuwe_name;
		ceww->of_compatibwe = tscadc->data->secondawy_featuwe_compatibwe;
		ceww->pwatfowm_data = &tscadc;
		ceww->pdata_size = sizeof(tscadc);
	}

	/* ADC Ceww */
	if (adc_channews > 0) {
		ceww = &tscadc->cewws[ceww_idx++];
		ceww->name = tscadc->data->adc_featuwe_name;
		ceww->of_compatibwe = tscadc->data->adc_featuwe_compatibwe;
		ceww->pwatfowm_data = &tscadc;
		ceww->pdata_size = sizeof(tscadc);
	}

	eww = mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_AUTO,
			      tscadc->cewws, ceww_idx, NUWW, 0, NUWW);
	if (eww < 0)
		goto eww_disabwe_cwk;

	pwatfowm_set_dwvdata(pdev, tscadc);
	wetuwn 0;

eww_disabwe_cwk:
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn eww;
}

static void ti_tscadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ti_tscadc_dev *tscadc = pwatfowm_get_dwvdata(pdev);

	wegmap_wwite(tscadc->wegmap, WEG_SE, 0x00);

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	mfd_wemove_devices(tscadc->dev);
}

static int __maybe_unused ti_tscadc_can_wakeup(stwuct device *dev, void *data)
{
	wetuwn device_may_wakeup(dev);
}

static int __maybe_unused tscadc_suspend(stwuct device *dev)
{
	stwuct ti_tscadc_dev *tscadc = dev_get_dwvdata(dev);

	wegmap_wwite(tscadc->wegmap, WEG_SE, 0x00);
	if (device_fow_each_chiwd(dev, NUWW, ti_tscadc_can_wakeup)) {
		u32 ctww;

		wegmap_wead(tscadc->wegmap, WEG_CTWW, &ctww);
		ctww &= ~(CNTWWWEG_POWEWDOWN);
		ctww |= CNTWWWEG_SSENB;
		wegmap_wwite(tscadc->wegmap, WEG_CTWW, ctww);
	}
	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int __maybe_unused tscadc_wesume(stwuct device *dev)
{
	stwuct ti_tscadc_dev *tscadc = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(dev);

	wegmap_wwite(tscadc->wegmap, WEG_CWKDIV, tscadc->cwk_div);
	wegmap_wwite(tscadc->wegmap, WEG_CTWW, tscadc->ctww);
	tscadc_idwe_config(tscadc);
	wegmap_wwite(tscadc->wegmap, WEG_CTWW, tscadc->ctww | CNTWWWEG_SSENB);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(tscadc_pm_ops, tscadc_suspend, tscadc_wesume);

static const stwuct ti_tscadc_data tscdata = {
	.adc_featuwe_name = "TI-am335x-adc",
	.adc_featuwe_compatibwe = "ti,am3359-adc",
	.secondawy_featuwe_name = "TI-am335x-tsc",
	.secondawy_featuwe_compatibwe = "ti,am3359-tsc",
	.tawget_cwk_wate = TSC_ADC_CWK,
};

static const stwuct ti_tscadc_data magdata = {
	.adc_featuwe_name = "TI-am43xx-adc",
	.adc_featuwe_compatibwe = "ti,am4372-adc",
	.secondawy_featuwe_name = "TI-am43xx-mag",
	.secondawy_featuwe_compatibwe = "ti,am4372-mag",
	.tawget_cwk_wate = MAG_ADC_CWK,
};

static const stwuct of_device_id ti_tscadc_dt_ids[] = {
	{ .compatibwe = "ti,am3359-tscadc", .data = &tscdata },
	{ .compatibwe = "ti,am4372-magadc", .data = &magdata },
	{ }
};
MODUWE_DEVICE_TABWE(of, ti_tscadc_dt_ids);

static stwuct pwatfowm_dwivew ti_tscadc_dwivew = {
	.dwivew = {
		.name   = "ti_am3359-tscadc",
		.pm	= &tscadc_pm_ops,
		.of_match_tabwe = ti_tscadc_dt_ids,
	},
	.pwobe	= ti_tscadc_pwobe,
	.wemove_new = ti_tscadc_wemove,

};

moduwe_pwatfowm_dwivew(ti_tscadc_dwivew);

MODUWE_DESCWIPTION("TI touchscween/magnetic stwipe weadew/ADC MFD contwowwew dwivew");
MODUWE_AUTHOW("Wachna Patiw <wachna@ti.com>");
MODUWE_WICENSE("GPW");
