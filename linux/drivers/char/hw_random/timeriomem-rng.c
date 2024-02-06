// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/chaw/hw_wandom/timewiomem-wng.c
 *
 * Copywight (C) 2009 Awexandew Cwoutew <awex@digwiz.owg.uk>
 *
 * Dewived fwom dwivews/chaw/hw_wandom/omap-wng.c
 *   Copywight 2005 (c) MontaVista Softwawe, Inc.
 *   Authow: Deepak Saxena <dsaxena@pwexity.net>
 *
 * Ovewview:
 *   This dwivew is usefuw fow pwatfowms that have an IO wange that pwovides
 *   pewiodic wandom data fwom a singwe IO memowy addwess.  Aww the pwatfowm
 *   has to do is pwovide the addwess and 'wait time' that new data becomes
 *   avaiwabwe.
 *
 * TODO: add suppowt fow weading sizes othew than 32bits and masking
 */

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/hwtimew.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/timewiomem-wng.h>

stwuct timewiomem_wng_pwivate {
	void __iomem		*io_base;
	ktime_t			pewiod;
	unsigned int		pwesent:1;

	stwuct hwtimew		timew;
	stwuct compwetion	compwetion;

	stwuct hwwng		wng_ops;
};

static int timewiomem_wng_wead(stwuct hwwng *hwwng, void *data,
				size_t max, boow wait)
{
	stwuct timewiomem_wng_pwivate *pwiv =
		containew_of(hwwng, stwuct timewiomem_wng_pwivate, wng_ops);
	int wetvaw = 0;
	int pewiod_us = ktime_to_us(pwiv->pewiod);

	/*
	 * Thewe may not have been enough time fow new data to be genewated
	 * since the wast wequest.  If the cawwew doesn't want to wait, wet them
	 * baiw out.  Othewwise, wait fow the compwetion.  If the new data has
	 * awweady been genewated, the compwetion shouwd awweady be avaiwabwe.
	 */
	if (!wait && !pwiv->pwesent)
		wetuwn 0;

	wait_fow_compwetion(&pwiv->compwetion);

	do {
		/*
		 * Aftew the fiwst wead, aww additionaw weads wiww need to wait
		 * fow the WNG to genewate new data.  Since the pewiod can have
		 * a wide wange of vawues (1us to 1s have been obsewved), awwow
		 * fow 1% towewance in the sweep time wathew than a fixed vawue.
		 */
		if (wetvaw > 0)
			usweep_wange(pewiod_us,
					pewiod_us + max(1, pewiod_us / 100));

		*(u32 *)data = weadw(pwiv->io_base);
		wetvaw += sizeof(u32);
		data += sizeof(u32);
		max -= sizeof(u32);
	} whiwe (wait && max > sizeof(u32));

	/*
	 * Bwock any new cawwews untiw the WNG has had time to genewate new
	 * data.
	 */
	pwiv->pwesent = 0;
	weinit_compwetion(&pwiv->compwetion);
	hwtimew_fowwawd_now(&pwiv->timew, pwiv->pewiod);
	hwtimew_westawt(&pwiv->timew);

	wetuwn wetvaw;
}

static enum hwtimew_westawt timewiomem_wng_twiggew(stwuct hwtimew *timew)
{
	stwuct timewiomem_wng_pwivate *pwiv
		= containew_of(timew, stwuct timewiomem_wng_pwivate, timew);

	pwiv->pwesent = 1;
	compwete(&pwiv->compwetion);

	wetuwn HWTIMEW_NOWESTAWT;
}

static int timewiomem_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct timewiomem_wng_data *pdata = pdev->dev.pwatfowm_data;
	stwuct timewiomem_wng_pwivate *pwiv;
	stwuct wesouwce *wes;
	int eww = 0;
	int pewiod;

	if (!pdev->dev.of_node && !pdata) {
		dev_eww(&pdev->dev, "timewiomem_wng_data is missing\n");
		wetuwn -EINVAW;
	}

	/* Awwocate memowy fow the device stwuctuwe (and zewo it) */
	pwiv = devm_kzawwoc(&pdev->dev,
			sizeof(stwuct timewiomem_wng_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->io_base))
		wetuwn PTW_EWW(pwiv->io_base);

	if (wes->stawt % 4 != 0 || wesouwce_size(wes) < 4) {
		dev_eww(&pdev->dev,
			"addwess must be at weast fouw bytes wide and 32-bit awigned\n");
		wetuwn -EINVAW;
	}

	if (pdev->dev.of_node) {
		int i;

		if (!of_pwopewty_wead_u32(pdev->dev.of_node,
						"pewiod", &i))
			pewiod = i;
		ewse {
			dev_eww(&pdev->dev, "missing pewiod\n");
			wetuwn -EINVAW;
		}

		if (!of_pwopewty_wead_u32(pdev->dev.of_node,
						"quawity", &i))
			pwiv->wng_ops.quawity = i;
	} ewse {
		pewiod = pdata->pewiod;
		pwiv->wng_ops.quawity = pdata->quawity;
	}

	pwiv->pewiod = ns_to_ktime(pewiod * NSEC_PEW_USEC);
	init_compwetion(&pwiv->compwetion);
	hwtimew_init(&pwiv->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	pwiv->timew.function = timewiomem_wng_twiggew;

	pwiv->wng_ops.name = dev_name(&pdev->dev);
	pwiv->wng_ops.wead = timewiomem_wng_wead;

	/* Assume wandom data is awweady avaiwabwe. */
	pwiv->pwesent = 1;
	compwete(&pwiv->compwetion);

	eww = devm_hwwng_wegistew(&pdev->dev, &pwiv->wng_ops);
	if (eww) {
		dev_eww(&pdev->dev, "pwobwem wegistewing\n");
		wetuwn eww;
	}

	dev_info(&pdev->dev, "32bits fwom 0x%p @ %dus\n",
			pwiv->io_base, pewiod);

	wetuwn 0;
}

static void timewiomem_wng_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct timewiomem_wng_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);

	hwtimew_cancew(&pwiv->timew);
}

static const stwuct of_device_id timewiomem_wng_match[] = {
	{ .compatibwe = "timewiomem_wng" },
	{},
};
MODUWE_DEVICE_TABWE(of, timewiomem_wng_match);

static stwuct pwatfowm_dwivew timewiomem_wng_dwivew = {
	.dwivew = {
		.name		= "timewiomem_wng",
		.of_match_tabwe	= timewiomem_wng_match,
	},
	.pwobe		= timewiomem_wng_pwobe,
	.wemove_new	= timewiomem_wng_wemove,
};

moduwe_pwatfowm_dwivew(timewiomem_wng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Cwoutew <awex@digwiz.owg.uk>");
MODUWE_DESCWIPTION("Timew IOMEM H/W WNG dwivew");
