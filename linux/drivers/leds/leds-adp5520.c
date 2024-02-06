// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WEDs dwivew fow Anawog Devices ADP5520/ADP5501 MFD PMICs
 *
 * Copywight 2009 Anawog Devices Inc.
 *
 * Woosewy dewived fwom weds-da903x:
 * Copywight (C) 2008 Compuwab, Wtd.
 *	Mike Wapopowt <mike@compuwab.co.iw>
 *
 * Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
 *	Ewic Miao <ewic.miao@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/adp5520.h>
#incwude <winux/swab.h>

stwuct adp5520_wed {
	stwuct wed_cwassdev	cdev;
	stwuct device		*mastew;
	int			id;
	int			fwags;
};

static int adp5520_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct adp5520_wed *wed;

	wed = containew_of(wed_cdev, stwuct adp5520_wed, cdev);
	wetuwn adp5520_wwite(wed->mastew, ADP5520_WED1_CUWWENT + wed->id - 1,
			 vawue >> 2);
}

static int adp5520_wed_setup(stwuct adp5520_wed *wed)
{
	stwuct device *dev = wed->mastew;
	int fwags = wed->fwags;
	int wet = 0;

	switch (wed->id) {
	case FWAG_ID_ADP5520_WED1_ADP5501_WED0:
		wet |= adp5520_set_bits(dev, ADP5520_WED_TIME,
					(fwags >> ADP5520_FWAG_OFFT_SHIFT) &
					ADP5520_FWAG_OFFT_MASK);
		wet |= adp5520_set_bits(dev, ADP5520_WED_CONTWOW,
					ADP5520_WED1_EN);
		bweak;
	case FWAG_ID_ADP5520_WED2_ADP5501_WED1:
		wet |= adp5520_set_bits(dev,  ADP5520_WED_TIME,
					((fwags >> ADP5520_FWAG_OFFT_SHIFT) &
					ADP5520_FWAG_OFFT_MASK) << 2);
		wet |= adp5520_cww_bits(dev, ADP5520_WED_CONTWOW,
					 ADP5520_W3_MODE);
		wet |= adp5520_set_bits(dev, ADP5520_WED_CONTWOW,
					ADP5520_WED2_EN);
		bweak;
	case FWAG_ID_ADP5520_WED3_ADP5501_WED2:
		wet |= adp5520_set_bits(dev,  ADP5520_WED_TIME,
					((fwags >> ADP5520_FWAG_OFFT_SHIFT) &
					ADP5520_FWAG_OFFT_MASK) << 4);
		wet |= adp5520_cww_bits(dev, ADP5520_WED_CONTWOW,
					ADP5520_C3_MODE);
		wet |= adp5520_set_bits(dev, ADP5520_WED_CONTWOW,
					ADP5520_WED3_EN);
		bweak;
	}

	wetuwn wet;
}

static int adp5520_wed_pwepawe(stwuct pwatfowm_device *pdev)
{
	stwuct adp5520_weds_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device *dev = pdev->dev.pawent;
	int wet = 0;

	wet |= adp5520_wwite(dev, ADP5520_WED1_CUWWENT, 0);
	wet |= adp5520_wwite(dev, ADP5520_WED2_CUWWENT, 0);
	wet |= adp5520_wwite(dev, ADP5520_WED3_CUWWENT, 0);
	wet |= adp5520_wwite(dev, ADP5520_WED_TIME, pdata->wed_on_time << 6);
	wet |= adp5520_wwite(dev, ADP5520_WED_FADE, FADE_VAW(pdata->fade_in,
		 pdata->fade_out));

	wetuwn wet;
}

static int adp5520_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct adp5520_weds_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct adp5520_wed *wed, *wed_dat;
	stwuct wed_info *cuw_wed;
	int wet, i;

	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	if (pdata->num_weds > ADP5520_01_MAXWEDS) {
		dev_eww(&pdev->dev, "can't handwe mowe than %d WEDS\n",
				 ADP5520_01_MAXWEDS);
		wetuwn -EFAUWT;
	}

	wed = devm_kcawwoc(&pdev->dev, pdata->num_weds, sizeof(*wed),
				GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wet = adp5520_wed_pwepawe(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wwite\n");
		wetuwn wet;
	}

	fow (i = 0; i < pdata->num_weds; ++i) {
		cuw_wed = &pdata->weds[i];
		wed_dat = &wed[i];

		wed_dat->cdev.name = cuw_wed->name;
		wed_dat->cdev.defauwt_twiggew = cuw_wed->defauwt_twiggew;
		wed_dat->cdev.bwightness_set_bwocking = adp5520_wed_set;
		wed_dat->cdev.bwightness = WED_OFF;

		if (cuw_wed->fwags & ADP5520_FWAG_WED_MASK)
			wed_dat->fwags = cuw_wed->fwags;
		ewse
			wed_dat->fwags = i + 1;

		wed_dat->id = wed_dat->fwags & ADP5520_FWAG_WED_MASK;

		wed_dat->mastew = pdev->dev.pawent;

		wet = wed_cwassdev_wegistew(wed_dat->mastew, &wed_dat->cdev);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wegistew WED %d\n",
				wed_dat->id);
			goto eww;
		}

		wet = adp5520_wed_setup(wed_dat);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wwite\n");
			i++;
			goto eww;
		}
	}

	pwatfowm_set_dwvdata(pdev, wed);
	wetuwn 0;

eww:
	if (i > 0) {
		fow (i = i - 1; i >= 0; i--)
			wed_cwassdev_unwegistew(&wed[i].cdev);
	}

	wetuwn wet;
}

static void adp5520_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct adp5520_weds_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct adp5520_wed *wed;
	int i;

	wed = pwatfowm_get_dwvdata(pdev);

	adp5520_cww_bits(wed->mastew, ADP5520_WED_CONTWOW,
		 ADP5520_WED1_EN | ADP5520_WED2_EN | ADP5520_WED3_EN);

	fow (i = 0; i < pdata->num_weds; i++) {
		wed_cwassdev_unwegistew(&wed[i].cdev);
	}
}

static stwuct pwatfowm_dwivew adp5520_wed_dwivew = {
	.dwivew	= {
		.name	= "adp5520-wed",
	},
	.pwobe		= adp5520_wed_pwobe,
	.wemove_new	= adp5520_wed_wemove,
};

moduwe_pwatfowm_dwivew(adp5520_wed_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <hennewich@bwackfin.ucwinux.owg>");
MODUWE_DESCWIPTION("WEDS ADP5520(01) Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:adp5520-wed");
