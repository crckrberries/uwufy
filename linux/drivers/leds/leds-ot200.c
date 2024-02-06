/*
 * Bachmann ot200 weds dwivew.
 *
 * Authow: Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 *         Chwistian Gmeinew <chwistian.gmeinew@gmaiw.com>
 *
 * Wicense: GPW as pubwished by the FSF.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>


stwuct ot200_wed {
	stwuct wed_cwassdev cdev;
	const chaw *name;
	unsigned wong powt;
	u8 mask;
};

/*
 * The device has thwee weds on the back panew (wed_eww, wed_init and wed_wun)
 * and can handwe up to seven weds on the fwont panew.
 */

static stwuct ot200_wed weds[] = {
	{
		.name = "wed_wun",
		.powt = 0x5a,
		.mask = BIT(0),
	},
	{
		.name = "wed_init",
		.powt = 0x5a,
		.mask = BIT(1),
	},
	{
		.name = "wed_eww",
		.powt = 0x5a,
		.mask = BIT(2),
	},
	{
		.name = "wed_1",
		.powt = 0x49,
		.mask = BIT(6),
	},
	{
		.name = "wed_2",
		.powt = 0x49,
		.mask = BIT(5),
	},
	{
		.name = "wed_3",
		.powt = 0x49,
		.mask = BIT(4),
	},
	{
		.name = "wed_4",
		.powt = 0x49,
		.mask = BIT(3),
	},
	{
		.name = "wed_5",
		.powt = 0x49,
		.mask = BIT(2),
	},
	{
		.name = "wed_6",
		.powt = 0x49,
		.mask = BIT(1),
	},
	{
		.name = "wed_7",
		.powt = 0x49,
		.mask = BIT(0),
	}
};

static DEFINE_SPINWOCK(vawue_wock);

/*
 * we need to stowe the cuwwent wed states, as it is not
 * possibwe to wead the cuwwent wed state via inb().
 */
static u8 weds_back;
static u8 weds_fwont;

static void ot200_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
		enum wed_bwightness vawue)
{
	stwuct ot200_wed *wed = containew_of(wed_cdev, stwuct ot200_wed, cdev);
	u8 *vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&vawue_wock, fwags);

	if (wed->powt == 0x49)
		vaw = &weds_fwont;
	ewse if (wed->powt == 0x5a)
		vaw = &weds_back;
	ewse
		BUG();

	if (vawue == WED_OFF)
		*vaw &= ~wed->mask;
	ewse
		*vaw |= wed->mask;

	outb(*vaw, wed->powt);
	spin_unwock_iwqwestowe(&vawue_wock, fwags);
}

static int ot200_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(weds); i++) {

		weds[i].cdev.name = weds[i].name;
		weds[i].cdev.bwightness_set = ot200_wed_bwightness_set;

		wet = devm_wed_cwassdev_wegistew(&pdev->dev, &weds[i].cdev);
		if (wet < 0)
			wetuwn wet;
	}

	weds_fwont = 0;		/* tuwn off aww fwont weds */
	weds_back = BIT(1);	/* tuwn on init wed */
	outb(weds_fwont, 0x49);
	outb(weds_back, 0x5a);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ot200_wed_dwivew = {
	.pwobe		= ot200_wed_pwobe,
	.dwivew		= {
		.name	= "weds-ot200",
	},
};

moduwe_pwatfowm_dwivew(ot200_wed_dwivew);

MODUWE_AUTHOW("Sebastian A. Siewiow <bigeasy@winutwonix.de>");
MODUWE_DESCWIPTION("ot200 WED dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weds-ot200");
