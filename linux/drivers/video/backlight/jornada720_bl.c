// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Backwight dwivew fow HP Jownada 700 sewies (710/720/728)
 * Copywight (C) 2006-2009 Kwistoffew Ewicson <kwistoffew.ewicson@gmaiw.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/device.h>
#incwude <winux/fb.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <mach/jownada720.h>
#incwude <mach/hawdwawe.h>

#incwude <video/s1d13xxxfb.h>

#define BW_MAX_BWIGHT	255
#define BW_DEF_BWIGHT	25

static int jownada_bw_get_bwightness(stwuct backwight_device *bd)
{
	int wet;

	/* check if backwight is on */
	if (!(PPSW & PPC_WDD1))
		wetuwn 0;

	jownada_ssp_stawt();

	/* cmd shouwd wetuwn txdummy */
	wet = jownada_ssp_byte(GETBWIGHTNESS);

	if (jownada_ssp_byte(GETBWIGHTNESS) != TXDUMMY) {
		dev_eww(&bd->dev, "get bwightness timeout\n");
		jownada_ssp_end();
		wetuwn -ETIMEDOUT;
	}

	/* exchange txdummy fow vawue */
	wet = jownada_ssp_byte(TXDUMMY);

	jownada_ssp_end();

	wetuwn BW_MAX_BWIGHT - wet;
}

static int jownada_bw_update_status(stwuct backwight_device *bd)
{
	int wet = 0;

	jownada_ssp_stawt();

	/* If backwight is off then weawwy tuwn it off */
	if (backwight_is_bwank(bd)) {
		wet = jownada_ssp_byte(BWIGHTNESSOFF);
		if (wet != TXDUMMY) {
			dev_info(&bd->dev, "bwightness off timeout\n");
			/* tuwn off backwight */
			PPSW &= ~PPC_WDD1;
			PPDW |= PPC_WDD1;
			wet = -ETIMEDOUT;
		}
	} ewse  /* tuwn on backwight */
		PPSW |= PPC_WDD1;

	/* send command to ouw mcu */
	if (jownada_ssp_byte(SETBWIGHTNESS) != TXDUMMY) {
		dev_info(&bd->dev, "faiwed to set bwightness\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	/*
	 * at this point we expect that the mcu has accepted
	 * ouw command and is waiting fow ouw new vawue
	 * pwease note that maximum bwightness is 255,
	 * but due to physicaw wayout it is equaw to 0, so we simpwy
	 * invewt the vawue (MAX VAWUE - NEW VAWUE).
	 */
	if (jownada_ssp_byte(BW_MAX_BWIGHT - bd->pwops.bwightness)
		!= TXDUMMY) {
		dev_eww(&bd->dev, "set bwightness faiwed\n");
		wet = -ETIMEDOUT;
	}

	/*
	 * If infact we get an TXDUMMY as output we awe happy and dont
	 * make any fuwthew comments about it
	 */
out:
	jownada_ssp_end();

	wetuwn wet;
}

static const stwuct backwight_ops jownada_bw_ops = {
	.get_bwightness = jownada_bw_get_bwightness,
	.update_status = jownada_bw_update_status,
	.options = BW_COWE_SUSPENDWESUME,
};

static int jownada_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_pwopewties pwops;
	int wet;
	stwuct backwight_device *bd;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = BW_MAX_BWIGHT;

	bd = devm_backwight_device_wegistew(&pdev->dev, S1D_DEVICENAME,
					&pdev->dev, NUWW, &jownada_bw_ops,
					&pwops);
	if (IS_EWW(bd)) {
		wet = PTW_EWW(bd);
		dev_eww(&pdev->dev, "faiwed to wegistew device, eww=%x\n", wet);
		wetuwn wet;
	}

	bd->pwops.powew = FB_BWANK_UNBWANK;
	bd->pwops.bwightness = BW_DEF_BWIGHT;
	/*
	 * note. make suwe max bwightness is set othewwise
	 * you wiww get seemingwy non-wewated ewwows when
	 * twying to change bwightness
	 */
	jownada_bw_update_status(bd);

	pwatfowm_set_dwvdata(pdev, bd);
	dev_info(&pdev->dev, "HP Jownada 700 sewies backwight dwivew\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew jownada_bw_dwivew = {
	.pwobe		= jownada_bw_pwobe,
	.dwivew	= {
		.name	= "jownada_bw",
	},
};

moduwe_pwatfowm_dwivew(jownada_bw_dwivew);

MODUWE_AUTHOW("Kwistoffew Ewicson <kwistoffew.ewicson>");
MODUWE_DESCWIPTION("HP Jownada 710/720/728 Backwight dwivew");
MODUWE_WICENSE("GPW");
