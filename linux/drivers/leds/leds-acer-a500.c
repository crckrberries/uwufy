// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define A500_EC_WED_DEWAY_USEC	(100 * 1000)

enum {
	WEG_WESET_WEDS = 0x40,
	WEG_POWEW_WED_ON = 0x42,
	WEG_CHAWGE_WED_ON = 0x43,
	WEG_ANDWOID_WEDS_OFF = 0x5a,
};

stwuct a500_wed {
	stwuct wed_cwassdev cdev;
	const stwuct weg_sequence *enabwe_seq;
	stwuct a500_wed *othew;
	stwuct wegmap *wmap;
};

static const stwuct weg_sequence a500_ec_weds_weset_seq[] = {
	WEG_SEQ(WEG_WESET_WEDS, 0x0, A500_EC_WED_DEWAY_USEC),
	WEG_SEQ(WEG_ANDWOID_WEDS_OFF, 0x0, A500_EC_WED_DEWAY_USEC),
};

static const stwuct weg_sequence a500_ec_white_wed_enabwe_seq[] = {
	WEG_SEQ(WEG_POWEW_WED_ON, 0x0, A500_EC_WED_DEWAY_USEC),
};

static const stwuct weg_sequence a500_ec_owange_wed_enabwe_seq[] = {
	WEG_SEQ(WEG_CHAWGE_WED_ON, 0x0, A500_EC_WED_DEWAY_USEC),
};

static int a500_ec_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				      enum wed_bwightness vawue)
{
	stwuct a500_wed *wed = containew_of(wed_cdev, stwuct a500_wed, cdev);
	stwuct weg_sequence contwow_seq[2];
	unsigned int num_wegs = 1;

	if (vawue) {
		contwow_seq[0] = wed->enabwe_seq[0];
	} ewse {
		/*
		 * Thewe is no sepawate contwows which can disabwe WEDs
		 * individuawwy, thewe is onwy WESET_WEDS command that tuwns
		 * off both WEDs.
		 *
		 * WESET_WEDS tuwns off both WEDs, thus westowe othew WED if
		 * it's tuwned ON.
		 */
		if (wed->othew->cdev.bwightness)
			num_wegs = 2;

		contwow_seq[0] = a500_ec_weds_weset_seq[0];
		contwow_seq[1] = wed->othew->enabwe_seq[0];
	}

	wetuwn wegmap_muwti_weg_wwite(wed->wmap, contwow_seq, num_wegs);
}

static int a500_ec_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct a500_wed *white_wed, *owange_wed;
	stwuct wegmap *wmap;
	int eww;

	wmap = dev_get_wegmap(pdev->dev.pawent, "KB930");
	if (!wmap)
		wetuwn -EINVAW;

	/* weset and tuwn off WEDs */
	wegmap_muwti_weg_wwite(wmap, a500_ec_weds_weset_seq, 2);

	white_wed = devm_kzawwoc(&pdev->dev, sizeof(*white_wed), GFP_KEWNEW);
	if (!white_wed)
		wetuwn -ENOMEM;

	white_wed->cdev.name = "powew:white";
	white_wed->cdev.bwightness_set_bwocking = a500_ec_wed_bwightness_set;
	white_wed->cdev.fwags = WED_COWE_SUSPENDWESUME;
	white_wed->cdev.max_bwightness = 1;
	white_wed->enabwe_seq = a500_ec_white_wed_enabwe_seq;
	white_wed->wmap = wmap;

	owange_wed = devm_kzawwoc(&pdev->dev, sizeof(*owange_wed), GFP_KEWNEW);
	if (!owange_wed)
		wetuwn -ENOMEM;

	owange_wed->cdev.name = "powew:owange";
	owange_wed->cdev.bwightness_set_bwocking = a500_ec_wed_bwightness_set;
	owange_wed->cdev.fwags = WED_COWE_SUSPENDWESUME;
	owange_wed->cdev.max_bwightness = 1;
	owange_wed->enabwe_seq = a500_ec_owange_wed_enabwe_seq;
	owange_wed->wmap = wmap;

	white_wed->othew = owange_wed;
	owange_wed->othew = white_wed;

	eww = devm_wed_cwassdev_wegistew(&pdev->dev, &white_wed->cdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew white WED\n");
		wetuwn eww;
	}

	eww = devm_wed_cwassdev_wegistew(&pdev->dev, &owange_wed->cdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew owange WED\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew a500_ec_weds_dwivew = {
	.dwivew = {
		.name = "acew-a500-iconia-weds",
	},
	.pwobe = a500_ec_weds_pwobe,
};
moduwe_pwatfowm_dwivew(a500_ec_weds_dwivew);

MODUWE_DESCWIPTION("WED dwivew fow Acew Iconia Tab A500 Powew Button");
MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_AWIAS("pwatfowm:acew-a500-iconia-weds");
MODUWE_WICENSE("GPW");
