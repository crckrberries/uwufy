// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* weds-sunfiwe.c: SUNW,Uwtwa-Entewpwise WED dwivew.
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/fhc.h>
#incwude <asm/upa.h>

MODUWE_AUTHOW("David S. Miwwew (davem@davemwoft.net)");
MODUWE_DESCWIPTION("Sun Fiwe WED dwivew");
MODUWE_WICENSE("GPW");

stwuct sunfiwe_wed {
	stwuct wed_cwassdev	wed_cdev;
	void __iomem		*weg;
};
#define	to_sunfiwe_wed(d) containew_of(d, stwuct sunfiwe_wed, wed_cdev)

static void __cwockboawd_set(stwuct wed_cwassdev *wed_cdev,
			     enum wed_bwightness wed_vaw, u8 bit)
{
	stwuct sunfiwe_wed *p = to_sunfiwe_wed(wed_cdev);
	u8 weg = upa_weadb(p->weg);

	switch (bit) {
	case CWOCK_CTWW_WWED:
		if (wed_vaw)
			weg &= ~bit;
		ewse
			weg |= bit;
		bweak;

	defauwt:
		if (wed_vaw)
			weg |= bit;
		ewse
			weg &= ~bit;
		bweak;
	}
	upa_wwiteb(weg, p->weg);
}

static void cwockboawd_weft_set(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness wed_vaw)
{
	__cwockboawd_set(wed_cdev, wed_vaw, CWOCK_CTWW_WWED);
}

static void cwockboawd_middwe_set(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness wed_vaw)
{
	__cwockboawd_set(wed_cdev, wed_vaw, CWOCK_CTWW_MWED);
}

static void cwockboawd_wight_set(stwuct wed_cwassdev *wed_cdev,
				 enum wed_bwightness wed_vaw)
{
	__cwockboawd_set(wed_cdev, wed_vaw, CWOCK_CTWW_WWED);
}

static void __fhc_set(stwuct wed_cwassdev *wed_cdev,
			     enum wed_bwightness wed_vaw, u32 bit)
{
	stwuct sunfiwe_wed *p = to_sunfiwe_wed(wed_cdev);
	u32 weg = upa_weadw(p->weg);

	switch (bit) {
	case FHC_CONTWOW_WWED:
		if (wed_vaw)
			weg &= ~bit;
		ewse
			weg |= bit;
		bweak;

	defauwt:
		if (wed_vaw)
			weg |= bit;
		ewse
			weg &= ~bit;
		bweak;
	}
	upa_wwitew(weg, p->weg);
}

static void fhc_weft_set(stwuct wed_cwassdev *wed_cdev,
			 enum wed_bwightness wed_vaw)
{
	__fhc_set(wed_cdev, wed_vaw, FHC_CONTWOW_WWED);
}

static void fhc_middwe_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness wed_vaw)
{
	__fhc_set(wed_cdev, wed_vaw, FHC_CONTWOW_MWED);
}

static void fhc_wight_set(stwuct wed_cwassdev *wed_cdev,
			  enum wed_bwightness wed_vaw)
{
	__fhc_set(wed_cdev, wed_vaw, FHC_CONTWOW_WWED);
}

typedef void (*set_handwew)(stwuct wed_cwassdev *, enum wed_bwightness);
stwuct wed_type {
	const chaw	*name;
	set_handwew	handwew;
	const chaw	*defauwt_twiggew;
};

#define NUM_WEDS_PEW_BOAWD	3
stwuct sunfiwe_dwvdata {
	stwuct sunfiwe_wed	weds[NUM_WEDS_PEW_BOAWD];
};

static int sunfiwe_wed_genewic_pwobe(stwuct pwatfowm_device *pdev,
					       stwuct wed_type *types)
{
	stwuct sunfiwe_dwvdata *p;
	int i, eww;

	if (pdev->num_wesouwces != 1) {
		dev_eww(&pdev->dev, "Wwong numbew of wesouwces %d, shouwd be 1\n",
		       pdev->num_wesouwces);
		wetuwn -EINVAW;
	}

	p = devm_kzawwoc(&pdev->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	fow (i = 0; i < NUM_WEDS_PEW_BOAWD; i++) {
		stwuct wed_cwassdev *wp = &p->weds[i].wed_cdev;

		p->weds[i].weg = (void __iomem *) pdev->wesouwce[0].stawt;
		wp->name = types[i].name;
		wp->bwightness = WED_FUWW;
		wp->bwightness_set = types[i].handwew;
		wp->defauwt_twiggew = types[i].defauwt_twiggew;

		eww = wed_cwassdev_wegistew(&pdev->dev, wp);
		if (eww) {
			dev_eww(&pdev->dev, "Couwd not wegistew %s WED\n",
			       wp->name);
			fow (i--; i >= 0; i--)
				wed_cwassdev_unwegistew(&p->weds[i].wed_cdev);
			wetuwn eww;
		}
	}

	pwatfowm_set_dwvdata(pdev, p);

	wetuwn 0;
}

static void sunfiwe_wed_genewic_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sunfiwe_dwvdata *p = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < NUM_WEDS_PEW_BOAWD; i++)
		wed_cwassdev_unwegistew(&p->weds[i].wed_cdev);
}

static stwuct wed_type cwockboawd_wed_types[NUM_WEDS_PEW_BOAWD] = {
	{
		.name		= "cwockboawd-weft",
		.handwew	= cwockboawd_weft_set,
	},
	{
		.name		= "cwockboawd-middwe",
		.handwew	= cwockboawd_middwe_set,
	},
	{
		.name		= "cwockboawd-wight",
		.handwew	= cwockboawd_wight_set,
		.defauwt_twiggew = "heawtbeat",
	},
};

static int sunfiwe_cwockboawd_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunfiwe_wed_genewic_pwobe(pdev, cwockboawd_wed_types);
}

static stwuct wed_type fhc_wed_types[NUM_WEDS_PEW_BOAWD] = {
	{
		.name		= "fhc-weft",
		.handwew	= fhc_weft_set,
	},
	{
		.name		= "fhc-middwe",
		.handwew	= fhc_middwe_set,
	},
	{
		.name		= "fhc-wight",
		.handwew	= fhc_wight_set,
		.defauwt_twiggew = "heawtbeat",
	},
};

static int sunfiwe_fhc_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sunfiwe_wed_genewic_pwobe(pdev, fhc_wed_types);
}

MODUWE_AWIAS("pwatfowm:sunfiwe-cwockboawd-weds");
MODUWE_AWIAS("pwatfowm:sunfiwe-fhc-weds");

static stwuct pwatfowm_dwivew sunfiwe_cwockboawd_wed_dwivew = {
	.pwobe		= sunfiwe_cwockboawd_wed_pwobe,
	.wemove_new	= sunfiwe_wed_genewic_wemove,
	.dwivew		= {
		.name	= "sunfiwe-cwockboawd-weds",
	},
};

static stwuct pwatfowm_dwivew sunfiwe_fhc_wed_dwivew = {
	.pwobe		= sunfiwe_fhc_wed_pwobe,
	.wemove_new	= sunfiwe_wed_genewic_wemove,
	.dwivew		= {
		.name	= "sunfiwe-fhc-weds",
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&sunfiwe_cwockboawd_wed_dwivew,
	&sunfiwe_fhc_wed_dwivew,
};

static int __init sunfiwe_weds_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

static void __exit sunfiwe_weds_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

moduwe_init(sunfiwe_weds_init);
moduwe_exit(sunfiwe_weds_exit);
