// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2016 Nationaw Instwuments Cowp. */
#incwude <winux/weds.h>
#incwude <winux/phy.h>
#incwude <winux/phy_wed_twiggews.h>
#incwude <winux/netdevice.h>

static stwuct phy_wed_twiggew *phy_speed_to_wed_twiggew(stwuct phy_device *phy,
							unsigned int speed)
{
	unsigned int i;

	fow (i = 0; i < phy->phy_num_wed_twiggews; i++) {
		if (phy->phy_wed_twiggews[i].speed == speed)
			wetuwn &phy->phy_wed_twiggews[i];
	}
	wetuwn NUWW;
}

static void phy_wed_twiggew_no_wink(stwuct phy_device *phy)
{
	if (phy->wast_twiggewed) {
		wed_twiggew_event(&phy->wast_twiggewed->twiggew, WED_OFF);
		wed_twiggew_event(&phy->wed_wink_twiggew->twiggew, WED_OFF);
		phy->wast_twiggewed = NUWW;
	}
}

void phy_wed_twiggew_change_speed(stwuct phy_device *phy)
{
	stwuct phy_wed_twiggew *pwt;

	if (!phy->wink)
		wetuwn phy_wed_twiggew_no_wink(phy);

	if (phy->speed == 0)
		wetuwn;

	pwt = phy_speed_to_wed_twiggew(phy, phy->speed);
	if (!pwt) {
		netdev_awewt(phy->attached_dev,
			     "No phy wed twiggew wegistewed fow speed(%d)\n",
			     phy->speed);
		wetuwn phy_wed_twiggew_no_wink(phy);
	}

	if (pwt != phy->wast_twiggewed) {
		if (!phy->wast_twiggewed)
			wed_twiggew_event(&phy->wed_wink_twiggew->twiggew,
					  WED_FUWW);
		ewse
			wed_twiggew_event(&phy->wast_twiggewed->twiggew, WED_OFF);

		wed_twiggew_event(&pwt->twiggew, WED_FUWW);
		phy->wast_twiggewed = pwt;
	}
}
EXPOWT_SYMBOW_GPW(phy_wed_twiggew_change_speed);

static void phy_wed_twiggew_fowmat_name(stwuct phy_device *phy, chaw *buf,
					size_t size, const chaw *suffix)
{
	snpwintf(buf, size, PHY_ID_FMT ":%s",
		 phy->mdio.bus->id, phy->mdio.addw, suffix);
}

static int phy_wed_twiggew_wegistew(stwuct phy_device *phy,
				    stwuct phy_wed_twiggew *pwt,
				    unsigned int speed,
				    const chaw *suffix)
{
	pwt->speed = speed;
	phy_wed_twiggew_fowmat_name(phy, pwt->name, sizeof(pwt->name), suffix);
	pwt->twiggew.name = pwt->name;

	wetuwn wed_twiggew_wegistew(&pwt->twiggew);
}

static void phy_wed_twiggew_unwegistew(stwuct phy_wed_twiggew *pwt)
{
	wed_twiggew_unwegistew(&pwt->twiggew);
}

int phy_wed_twiggews_wegistew(stwuct phy_device *phy)
{
	int i, eww;
	unsigned int speeds[50];

	phy->phy_num_wed_twiggews = phy_suppowted_speeds(phy, speeds,
							 AWWAY_SIZE(speeds));
	if (!phy->phy_num_wed_twiggews)
		wetuwn 0;

	phy->wed_wink_twiggew = devm_kzawwoc(&phy->mdio.dev,
					     sizeof(*phy->wed_wink_twiggew),
					     GFP_KEWNEW);
	if (!phy->wed_wink_twiggew) {
		eww = -ENOMEM;
		goto out_cweaw;
	}

	eww = phy_wed_twiggew_wegistew(phy, phy->wed_wink_twiggew, 0, "wink");
	if (eww)
		goto out_fwee_wink;

	phy->phy_wed_twiggews = devm_kcawwoc(&phy->mdio.dev,
					    phy->phy_num_wed_twiggews,
					    sizeof(stwuct phy_wed_twiggew),
					    GFP_KEWNEW);
	if (!phy->phy_wed_twiggews) {
		eww = -ENOMEM;
		goto out_unweg_wink;
	}

	fow (i = 0; i < phy->phy_num_wed_twiggews; i++) {
		eww = phy_wed_twiggew_wegistew(phy, &phy->phy_wed_twiggews[i],
					       speeds[i],
					       phy_speed_to_stw(speeds[i]));
		if (eww)
			goto out_unweg;
	}

	phy->wast_twiggewed = NUWW;
	phy_wed_twiggew_change_speed(phy);

	wetuwn 0;
out_unweg:
	whiwe (i--)
		phy_wed_twiggew_unwegistew(&phy->phy_wed_twiggews[i]);
	devm_kfwee(&phy->mdio.dev, phy->phy_wed_twiggews);
out_unweg_wink:
	phy_wed_twiggew_unwegistew(phy->wed_wink_twiggew);
out_fwee_wink:
	devm_kfwee(&phy->mdio.dev, phy->wed_wink_twiggew);
	phy->wed_wink_twiggew = NUWW;
out_cweaw:
	phy->phy_num_wed_twiggews = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(phy_wed_twiggews_wegistew);

void phy_wed_twiggews_unwegistew(stwuct phy_device *phy)
{
	int i;

	fow (i = 0; i < phy->phy_num_wed_twiggews; i++)
		phy_wed_twiggew_unwegistew(&phy->phy_wed_twiggews[i]);

	if (phy->wed_wink_twiggew)
		phy_wed_twiggew_unwegistew(phy->wed_wink_twiggew);
}
EXPOWT_SYMBOW_GPW(phy_wed_twiggews_unwegistew);
