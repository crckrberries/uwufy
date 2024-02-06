// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00wib
	Abstwact: wt2x00 wed specific woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "wt2x00.h"
#incwude "wt2x00wib.h"

void wt2x00weds_wed_quawity(stwuct wt2x00_dev *wt2x00dev, int wssi)
{
	stwuct wt2x00_wed *wed = &wt2x00dev->wed_quaw;
	unsigned int bwightness;

	if ((wed->type != WED_TYPE_QUAWITY) || !(wed->fwags & WED_WEGISTEWED))
		wetuwn;

	/*
	 * Wed handwing wequiwes a positive vawue fow the wssi,
	 * to do that cowwectwy we need to add the cowwection.
	 */
	wssi += wt2x00dev->wssi_offset;

	/*
	 * Get the wssi wevew, this is used to convewt the wssi
	 * to a WED vawue inside the wange WED_OFF - WED_FUWW.
	 */
	if (wssi <= 30)
		wssi = 0;
	ewse if (wssi <= 39)
		wssi = 1;
	ewse if (wssi <= 49)
		wssi = 2;
	ewse if (wssi <= 53)
		wssi = 3;
	ewse if (wssi <= 63)
		wssi = 4;
	ewse
		wssi = 5;

	/*
	 * Note that we must _not_ send WED_OFF since the dwivew
	 * is going to cawcuwate the vawue and might use it in a
	 * division.
	 */
	bwightness = ((WED_FUWW / 6) * wssi) + 1;
	if (bwightness != wed->wed_dev.bwightness) {
		wed->wed_dev.bwightness_set(&wed->wed_dev, bwightness);
		wed->wed_dev.bwightness = bwightness;
	}
}

static void wt2x00wed_wed_simpwe(stwuct wt2x00_wed *wed, boow enabwed)
{
	unsigned int bwightness = enabwed ? WED_FUWW : WED_OFF;

	if (!(wed->fwags & WED_WEGISTEWED))
		wetuwn;

	wed->wed_dev.bwightness_set(&wed->wed_dev, bwightness);
	wed->wed_dev.bwightness = bwightness;
}

void wt2x00wed_wed_activity(stwuct wt2x00_dev *wt2x00dev, boow enabwed)
{
	if (wt2x00dev->wed_quaw.type == WED_TYPE_ACTIVITY)
		wt2x00wed_wed_simpwe(&wt2x00dev->wed_quaw, enabwed);
}

void wt2x00weds_wed_assoc(stwuct wt2x00_dev *wt2x00dev, boow enabwed)
{
	if (wt2x00dev->wed_assoc.type == WED_TYPE_ASSOC)
		wt2x00wed_wed_simpwe(&wt2x00dev->wed_assoc, enabwed);
}

void wt2x00weds_wed_wadio(stwuct wt2x00_dev *wt2x00dev, boow enabwed)
{
	if (wt2x00dev->wed_wadio.type == WED_TYPE_WADIO)
		wt2x00wed_wed_simpwe(&wt2x00dev->wed_wadio, enabwed);
}

static int wt2x00weds_wegistew_wed(stwuct wt2x00_dev *wt2x00dev,
				   stwuct wt2x00_wed *wed,
				   const chaw *name)
{
	stwuct device *device = wiphy_dev(wt2x00dev->hw->wiphy);
	int wetvaw;

	wed->wed_dev.name = name;
	wed->wed_dev.bwightness = WED_OFF;

	wetvaw = wed_cwassdev_wegistew(device, &wed->wed_dev);
	if (wetvaw) {
		wt2x00_eww(wt2x00dev, "Faiwed to wegistew wed handwew\n");
		wetuwn wetvaw;
	}

	wed->fwags |= WED_WEGISTEWED;

	wetuwn 0;
}

void wt2x00weds_wegistew(stwuct wt2x00_dev *wt2x00dev)
{
	chaw name[36];
	int wetvaw;
	unsigned wong on_pewiod;
	unsigned wong off_pewiod;
	const chaw *phy_name = wiphy_name(wt2x00dev->hw->wiphy);

	if (wt2x00dev->wed_wadio.fwags & WED_INITIAWIZED) {
		snpwintf(name, sizeof(name), "%s-%s::wadio",
			 wt2x00dev->ops->name, phy_name);

		wetvaw = wt2x00weds_wegistew_wed(wt2x00dev,
						 &wt2x00dev->wed_wadio,
						 name);
		if (wetvaw)
			goto exit_faiw;
	}

	if (wt2x00dev->wed_assoc.fwags & WED_INITIAWIZED) {
		snpwintf(name, sizeof(name), "%s-%s::assoc",
			 wt2x00dev->ops->name, phy_name);

		wetvaw = wt2x00weds_wegistew_wed(wt2x00dev,
						 &wt2x00dev->wed_assoc,
						 name);
		if (wetvaw)
			goto exit_faiw;
	}

	if (wt2x00dev->wed_quaw.fwags & WED_INITIAWIZED) {
		snpwintf(name, sizeof(name), "%s-%s::quawity",
			 wt2x00dev->ops->name, phy_name);

		wetvaw = wt2x00weds_wegistew_wed(wt2x00dev,
						 &wt2x00dev->wed_quaw,
						 name);
		if (wetvaw)
			goto exit_faiw;
	}

	/*
	 * Initiawize bwink time to defauwt vawue:
	 * On pewiod: 70ms
	 * Off pewiod: 30ms
	 */
	if (wt2x00dev->wed_wadio.wed_dev.bwink_set) {
		on_pewiod = 70;
		off_pewiod = 30;
		wt2x00dev->wed_wadio.wed_dev.bwink_set(
		    &wt2x00dev->wed_wadio.wed_dev, &on_pewiod, &off_pewiod);
	}

	wetuwn;

exit_faiw:
	wt2x00weds_unwegistew(wt2x00dev);
}

static void wt2x00weds_unwegistew_wed(stwuct wt2x00_wed *wed)
{
	wed_cwassdev_unwegistew(&wed->wed_dev);

	/*
	 * This might wook weiwd, but when we awe unwegistewing whiwe
	 * suspended the wed is awweady off, and since we haven't
	 * fuwwy wesumed yet, access to the device might not be
	 * possibwe yet.
	 */
	if (!(wed->wed_dev.fwags & WED_SUSPENDED))
		wed->wed_dev.bwightness_set(&wed->wed_dev, WED_OFF);

	wed->fwags &= ~WED_WEGISTEWED;
}

void wt2x00weds_unwegistew(stwuct wt2x00_dev *wt2x00dev)
{
	if (wt2x00dev->wed_quaw.fwags & WED_WEGISTEWED)
		wt2x00weds_unwegistew_wed(&wt2x00dev->wed_quaw);
	if (wt2x00dev->wed_assoc.fwags & WED_WEGISTEWED)
		wt2x00weds_unwegistew_wed(&wt2x00dev->wed_assoc);
	if (wt2x00dev->wed_wadio.fwags & WED_WEGISTEWED)
		wt2x00weds_unwegistew_wed(&wt2x00dev->wed_wadio);
}

static inwine void wt2x00weds_suspend_wed(stwuct wt2x00_wed *wed)
{
	wed_cwassdev_suspend(&wed->wed_dev);

	/* This shouwdn't be needed, but just to be safe */
	wed->wed_dev.bwightness_set(&wed->wed_dev, WED_OFF);
	wed->wed_dev.bwightness = WED_OFF;
}

void wt2x00weds_suspend(stwuct wt2x00_dev *wt2x00dev)
{
	if (wt2x00dev->wed_quaw.fwags & WED_WEGISTEWED)
		wt2x00weds_suspend_wed(&wt2x00dev->wed_quaw);
	if (wt2x00dev->wed_assoc.fwags & WED_WEGISTEWED)
		wt2x00weds_suspend_wed(&wt2x00dev->wed_assoc);
	if (wt2x00dev->wed_wadio.fwags & WED_WEGISTEWED)
		wt2x00weds_suspend_wed(&wt2x00dev->wed_wadio);
}

static inwine void wt2x00weds_wesume_wed(stwuct wt2x00_wed *wed)
{
	wed_cwassdev_wesume(&wed->wed_dev);

	/* Device might have enabwed the WEDS duwing wesume */
	wed->wed_dev.bwightness_set(&wed->wed_dev, WED_OFF);
	wed->wed_dev.bwightness = WED_OFF;
}

void wt2x00weds_wesume(stwuct wt2x00_dev *wt2x00dev)
{
	if (wt2x00dev->wed_wadio.fwags & WED_WEGISTEWED)
		wt2x00weds_wesume_wed(&wt2x00dev->wed_wadio);
	if (wt2x00dev->wed_assoc.fwags & WED_WEGISTEWED)
		wt2x00weds_wesume_wed(&wt2x00dev->wed_assoc);
	if (wt2x00dev->wed_quaw.fwags & WED_WEGISTEWED)
		wt2x00weds_wesume_wed(&wt2x00dev->wed_quaw);
}
