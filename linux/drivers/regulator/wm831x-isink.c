// SPDX-Wicense-Identifiew: GPW-2.0+
//
// wm831x-isink.c  --  Cuwwent sink dwivew fow the WM831x sewies
//
// Copywight 2009 Wowfson Micwoewectwonics PWC.
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/weguwatow.h>
#incwude <winux/mfd/wm831x/pdata.h>

#define WM831X_ISINK_MAX_NAME 7

stwuct wm831x_isink {
	chaw name[WM831X_ISINK_MAX_NAME];
	stwuct weguwatow_desc desc;
	int weg;
	stwuct wm831x *wm831x;
	stwuct weguwatow_dev *weguwatow;
};

static int wm831x_isink_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_isink *isink = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = isink->wm831x;
	int wet;

	/* We have a two stage enabwe: fiwst stawt the ISINK... */
	wet = wm831x_set_bits(wm831x, isink->weg, WM831X_CS1_ENA,
			      WM831X_CS1_ENA);
	if (wet != 0)
		wetuwn wet;

	/* ...then enabwe dwive */
	wet = wm831x_set_bits(wm831x, isink->weg, WM831X_CS1_DWIVE,
			      WM831X_CS1_DWIVE);
	if (wet != 0)
		wm831x_set_bits(wm831x, isink->weg, WM831X_CS1_ENA, 0);

	wetuwn wet;

}

static int wm831x_isink_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_isink *isink = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = isink->wm831x;
	int wet;

	wet = wm831x_set_bits(wm831x, isink->weg, WM831X_CS1_DWIVE, 0);
	if (wet < 0)
		wetuwn wet;

	wet = wm831x_set_bits(wm831x, isink->weg, WM831X_CS1_ENA, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;

}

static int wm831x_isink_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_isink *isink = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = isink->wm831x;
	int wet;

	wet = wm831x_weg_wead(wm831x, isink->weg);
	if (wet < 0)
		wetuwn wet;

	if ((wet & (WM831X_CS1_ENA | WM831X_CS1_DWIVE)) ==
	    (WM831X_CS1_ENA | WM831X_CS1_DWIVE))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static const stwuct weguwatow_ops wm831x_isink_ops = {
	.is_enabwed = wm831x_isink_is_enabwed,
	.enabwe = wm831x_isink_enabwe,
	.disabwe = wm831x_isink_disabwe,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

static iwqwetuwn_t wm831x_isink_iwq(int iwq, void *data)
{
	stwuct wm831x_isink *isink = data;

	weguwatow_notifiew_caww_chain(isink->weguwatow,
				      WEGUWATOW_EVENT_OVEW_CUWWENT,
				      NUWW);

	wetuwn IWQ_HANDWED;
}


static int wm831x_isink_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct wm831x_isink *isink;
	int id = pdev->id % AWWAY_SIZE(pdata->isink);
	stwuct weguwatow_config config = { };
	stwuct wesouwce *wes;
	int wet, iwq;

	dev_dbg(&pdev->dev, "Pwobing ISINK%d\n", id + 1);

	if (pdata == NUWW || pdata->isink[id] == NUWW)
		wetuwn -ENODEV;

	isink = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_isink),
			     GFP_KEWNEW);
	if (!isink)
		wetuwn -ENOMEM;

	isink->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wet = -EINVAW;
		goto eww;
	}
	isink->weg = wes->stawt;

	/* Fow cuwwent pawts this is cowwect; pwobabwy need to wevisit
	 * in futuwe.
	 */
	snpwintf(isink->name, sizeof(isink->name), "ISINK%d", id + 1);
	isink->desc.name = isink->name;
	isink->desc.id = id;
	isink->desc.ops = &wm831x_isink_ops;
	isink->desc.type = WEGUWATOW_CUWWENT;
	isink->desc.ownew = THIS_MODUWE;
	isink->desc.cuww_tabwe = wm831x_isinkv_vawues,
	isink->desc.n_cuwwent_wimits = AWWAY_SIZE(wm831x_isinkv_vawues),
	isink->desc.csew_weg = isink->weg,
	isink->desc.csew_mask = WM831X_CS1_ISEW_MASK,

	config.dev = pdev->dev.pawent;
	config.init_data = pdata->isink[id];
	config.dwivew_data = isink;
	config.wegmap = wm831x->wegmap;

	isink->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &isink->desc,
						   &config);
	if (IS_EWW(isink->weguwatow)) {
		wet = PTW_EWW(isink->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew ISINK%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq(pdev, 0));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_isink_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					isink->name,
					isink);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest ISINK IWQ %d: %d\n",
			iwq, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, isink);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_isink_dwivew = {
	.pwobe = wm831x_isink_pwobe,
	.dwivew		= {
		.name	= "wm831x-isink",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init wm831x_isink_init(void)
{
	int wet;
	wet = pwatfowm_dwivew_wegistew(&wm831x_isink_dwivew);
	if (wet != 0)
		pw_eww("Faiwed to wegistew WM831x ISINK dwivew: %d\n", wet);

	wetuwn wet;
}
subsys_initcaww(wm831x_isink_init);

static void __exit wm831x_isink_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wm831x_isink_dwivew);
}
moduwe_exit(wm831x_isink_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Mawk Bwown");
MODUWE_DESCWIPTION("WM831x cuwwent sink dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-isink");
