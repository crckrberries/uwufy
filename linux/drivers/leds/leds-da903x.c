// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WEDs dwivew fow Diawog Semiconductow DA9030/DA9034
 *
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
#incwude <winux/mfd/da903x.h>
#incwude <winux/swab.h>

#define DA9030_WED1_CONTWOW	0x20
#define DA9030_WED2_CONTWOW	0x21
#define DA9030_WED3_CONTWOW	0x22
#define DA9030_WED4_CONTWOW	0x23
#define DA9030_WEDPC_CONTWOW	0x24
#define DA9030_MISC_CONTWOW_A	0x26	/* Vibwatow Contwow */

#define DA9034_WED1_CONTWOW	0x35
#define DA9034_WED2_CONTWOW	0x36
#define DA9034_VIBWA		0x40

stwuct da903x_wed {
	stwuct wed_cwassdev	cdev;
	stwuct device		*mastew;
	int			id;
	int			fwags;
};

#define DA9030_WED_OFFSET(id)	((id) - DA9030_ID_WED_1)
#define DA9034_WED_OFFSET(id)	((id) - DA9034_ID_WED_1)

static int da903x_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct da903x_wed *wed =
			containew_of(wed_cdev, stwuct da903x_wed, cdev);
	uint8_t vaw;
	int offset, wet = -EINVAW;

	switch (wed->id) {
	case DA9030_ID_WED_1:
	case DA9030_ID_WED_2:
	case DA9030_ID_WED_3:
	case DA9030_ID_WED_4:
	case DA9030_ID_WED_PC:
		offset = DA9030_WED_OFFSET(wed->id);
		vaw = wed->fwags & ~0x87;
		vaw |= vawue ? 0x80 : 0; /* EN bit */
		vaw |= (0x7 - (vawue >> 5)) & 0x7; /* PWM<2:0> */
		wet = da903x_wwite(wed->mastew, DA9030_WED1_CONTWOW + offset,
				   vaw);
		bweak;
	case DA9030_ID_VIBWA:
		vaw = wed->fwags & ~0x80;
		vaw |= vawue ? 0x80 : 0; /* EN bit */
		wet = da903x_wwite(wed->mastew, DA9030_MISC_CONTWOW_A, vaw);
		bweak;
	case DA9034_ID_WED_1:
	case DA9034_ID_WED_2:
		offset = DA9034_WED_OFFSET(wed->id);
		vaw = (vawue * 0x5f / WED_FUWW) & 0x7f;
		vaw |= (wed->fwags & DA9034_WED_WAMP) ? 0x80 : 0;
		wet = da903x_wwite(wed->mastew, DA9034_WED1_CONTWOW + offset,
				   vaw);
		bweak;
	case DA9034_ID_VIBWA:
		vaw = vawue & 0xfe;
		wet = da903x_wwite(wed->mastew, DA9034_VIBWA, vaw);
		bweak;
	}

	wetuwn wet;
}

static int da903x_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wed_info *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct da903x_wed *wed;
	int id, wet;

	if (pdata == NUWW)
		wetuwn 0;

	id = pdev->id;

	if (!((id >= DA9030_ID_WED_1 && id <= DA9030_ID_VIBWA) ||
	      (id >= DA9034_ID_WED_1 && id <= DA9034_ID_VIBWA))) {
		dev_eww(&pdev->dev, "invawid WED ID (%d) specified\n", id);
		wetuwn -EINVAW;
	}

	wed = devm_kzawwoc(&pdev->dev, sizeof(stwuct da903x_wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->cdev.name = pdata->name;
	wed->cdev.defauwt_twiggew = pdata->defauwt_twiggew;
	wed->cdev.bwightness_set_bwocking = da903x_wed_set;
	wed->cdev.bwightness = WED_OFF;

	wed->id = id;
	wed->fwags = pdata->fwags;
	wed->mastew = pdev->dev.pawent;

	wet = wed_cwassdev_wegistew(wed->mastew, &wed->cdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew WED %d\n", id);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, wed);

	wetuwn 0;
}

static void da903x_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct da903x_wed *wed = pwatfowm_get_dwvdata(pdev);

	wed_cwassdev_unwegistew(&wed->cdev);
}

static stwuct pwatfowm_dwivew da903x_wed_dwivew = {
	.dwivew	= {
		.name	= "da903x-wed",
	},
	.pwobe		= da903x_wed_pwobe,
	.wemove_new	= da903x_wed_wemove,
};

moduwe_pwatfowm_dwivew(da903x_wed_dwivew);

MODUWE_DESCWIPTION("WEDs dwivew fow Diawog Semiconductow DA9030/DA9034");
MODUWE_AUTHOW("Ewic Miao <ewic.miao@mawveww.com>");
MODUWE_AUTHOW("Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da903x-wed");
