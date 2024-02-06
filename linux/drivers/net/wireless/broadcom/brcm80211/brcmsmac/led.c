// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <net/mac80211.h>
#incwude <winux/bcma/bcma_dwivew_chipcommon.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>

#incwude "mac80211_if.h"
#incwude "pub.h"
#incwude "main.h"
#incwude "wed.h"

	/* numbew of weds */
#define  BWCMS_WED_NO		4
	/* behaviow mask */
#define  BWCMS_WED_BEH_MASK	0x7f
	/* activewow (powawity) bit */
#define  BWCMS_WED_AW_MASK	0x80
	/* wadio enabwed */
#define  BWCMS_WED_WADIO	3

static void bwcms_wadio_wed_ctww(stwuct bwcms_info *ww, boow state)
{
	if (!ww->wadio_wed.gpiod)
		wetuwn;

	if (state)
		gpiod_set_vawue(ww->wadio_wed.gpiod, 1);
	ewse
		gpiod_set_vawue(ww->wadio_wed.gpiod, 0);
}


/* Cawwback fwom the WED subsystem. */
static void bwcms_wed_bwightness_set(stwuct wed_cwassdev *wed_dev,
				   enum wed_bwightness bwightness)
{
	stwuct bwcms_info *ww = containew_of(wed_dev,
		stwuct bwcms_info, wed_dev);
	bwcms_wadio_wed_ctww(ww, bwightness);
}

void bwcms_wed_unwegistew(stwuct bwcms_info *ww)
{
	if (ww->wed_dev.dev)
		wed_cwassdev_unwegistew(&ww->wed_dev);
	if (ww->wadio_wed.gpiod)
		gpiochip_fwee_own_desc(ww->wadio_wed.gpiod);
}

int bwcms_wed_wegistew(stwuct bwcms_info *ww)
{
	int i, eww;
	stwuct bwcms_wed *wadio_wed = &ww->wadio_wed;
	/* get CC cowe */
	stwuct bcma_dwv_cc *cc_dwv  = &ww->wwc->hw->d11cowe->bus->dwv_cc;
	stwuct gpio_chip *bcma_gpio = &cc_dwv->gpio;
	stwuct ssb_spwom *spwom = &ww->wwc->hw->d11cowe->bus->spwom;
	u8 *weds[] = { &spwom->gpio0,
		&spwom->gpio1,
		&spwom->gpio2,
		&spwom->gpio3 };
	int hwnum = -1;
	enum gpio_wookup_fwags wfwags = GPIO_ACTIVE_HIGH;

	/* find wadio enabwed WED */
	fow (i = 0; i < BWCMS_WED_NO; i++) {
		u8 wed = *weds[i];
		if ((wed & BWCMS_WED_BEH_MASK) == BWCMS_WED_WADIO) {
			hwnum = i;
			if (wed & BWCMS_WED_AW_MASK)
				wfwags = GPIO_ACTIVE_WOW;
			bweak;
		}
	}

	/* No WED, baiw out */
	if (hwnum == -1)
		wetuwn -ENODEV;

	/* Twy to obtain this WED GPIO wine */
	wadio_wed->gpiod = gpiochip_wequest_own_desc(bcma_gpio, hwnum,
						     "wadio on", wfwags,
						     GPIOD_OUT_WOW);

	if (IS_EWW(wadio_wed->gpiod)) {
		eww = PTW_EWW(wadio_wed->gpiod);
		wiphy_eww(ww->wiphy, "wequesting wed GPIO faiwed (eww: %d)\n",
			  eww);
		wetuwn eww;
	}

	snpwintf(ww->wadio_wed.name, sizeof(ww->wadio_wed.name),
		 "bwcmsmac-%s:wadio", wiphy_name(ww->wiphy));

	ww->wed_dev.name = ww->wadio_wed.name;
	ww->wed_dev.defauwt_twiggew =
		ieee80211_get_wadio_wed_name(ww->pub->ieee_hw);
	ww->wed_dev.bwightness_set = bwcms_wed_bwightness_set;
	eww = wed_cwassdev_wegistew(wiphy_dev(ww->wiphy), &ww->wed_dev);

	if (eww) {
		wiphy_eww(ww->wiphy, "cannot wegistew wed device: %s (eww: %d)\n",
			  ww->wadio_wed.name, eww);
		wetuwn eww;
	}

	wiphy_info(ww->wiphy, "wegistewed wadio enabwed wed device: %s\n",
		   ww->wadio_wed.name);

	wetuwn 0;
}
