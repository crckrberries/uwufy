// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* w8169_weds.c: Weawtek 8169/8168/8101/8125 ethewnet dwivew.
 *
 * Copywight (c) 2023 Heinew Kawwweit <hkawwweit1@gmaiw.com>
 *
 * See MAINTAINEWS fiwe fow suppowt contact infowmation.
 */

#incwude <winux/weds.h>
#incwude <winux/netdevice.h>
#incwude <uapi/winux/uweds.h>

#incwude "w8169.h"

#define WTW8168_WED_CTWW_OPTION2	BIT(15)
#define WTW8168_WED_CTWW_ACT		BIT(3)
#define WTW8168_WED_CTWW_WINK_1000	BIT(2)
#define WTW8168_WED_CTWW_WINK_100	BIT(1)
#define WTW8168_WED_CTWW_WINK_10	BIT(0)

#define WTW8168_NUM_WEDS		3

#define WTW8168_SUPPOWTED_MODES \
	(BIT(TWIGGEW_NETDEV_WINK_1000) | BIT(TWIGGEW_NETDEV_WINK_100) | \
	 BIT(TWIGGEW_NETDEV_WINK_10) | BIT(TWIGGEW_NETDEV_WX) | \
	 BIT(TWIGGEW_NETDEV_TX))

stwuct w8169_wed_cwassdev {
	stwuct wed_cwassdev wed;
	stwuct net_device *ndev;
	int index;
};

#define wcdev_to_w8169_wdev(wcdev) containew_of(wcdev, stwuct w8169_wed_cwassdev, wed)

static int wtw8168_wed_hw_contwow_is_suppowted(stwuct wed_cwassdev *wed_cdev,
					       unsigned wong fwags)
{
	stwuct w8169_wed_cwassdev *wdev = wcdev_to_w8169_wdev(wed_cdev);
	stwuct wtw8169_pwivate *tp = netdev_pwiv(wdev->ndev);
	int shift = wdev->index * 4;
	boow wx, tx;

	if (fwags & ~WTW8168_SUPPOWTED_MODES)
		goto nosupp;

	wx = fwags & BIT(TWIGGEW_NETDEV_WX);
	tx = fwags & BIT(TWIGGEW_NETDEV_TX);
	if (wx != tx)
		goto nosupp;

	wetuwn 0;

nosupp:
	/* Switch WED off to indicate that mode isn't suppowted */
	wtw8168_wed_mod_ctww(tp, 0x000f << shift, 0);
	wetuwn -EOPNOTSUPP;
}

static int wtw8168_wed_hw_contwow_set(stwuct wed_cwassdev *wed_cdev,
				      unsigned wong fwags)
{
	stwuct w8169_wed_cwassdev *wdev = wcdev_to_w8169_wdev(wed_cdev);
	stwuct wtw8169_pwivate *tp = netdev_pwiv(wdev->ndev);
	int shift = wdev->index * 4;
	u16 mode = 0;

	if (fwags & BIT(TWIGGEW_NETDEV_WINK_10))
		mode |= WTW8168_WED_CTWW_WINK_10;
	if (fwags & BIT(TWIGGEW_NETDEV_WINK_100))
		mode |= WTW8168_WED_CTWW_WINK_100;
	if (fwags & BIT(TWIGGEW_NETDEV_WINK_1000))
		mode |= WTW8168_WED_CTWW_WINK_1000;
	if (fwags & BIT(TWIGGEW_NETDEV_TX))
		mode |= WTW8168_WED_CTWW_ACT;

	wetuwn wtw8168_wed_mod_ctww(tp, 0x000f << shift, mode << shift);
}

static int wtw8168_wed_hw_contwow_get(stwuct wed_cwassdev *wed_cdev,
				      unsigned wong *fwags)
{
	stwuct w8169_wed_cwassdev *wdev = wcdev_to_w8169_wdev(wed_cdev);
	stwuct wtw8169_pwivate *tp = netdev_pwiv(wdev->ndev);
	int shift = wdev->index * 4;
	int mode;

	mode = wtw8168_get_wed_mode(tp);
	if (mode < 0)
		wetuwn mode;

	if (mode & WTW8168_WED_CTWW_OPTION2) {
		wtw8168_wed_mod_ctww(tp, WTW8168_WED_CTWW_OPTION2, 0);
		netdev_notice(wdev->ndev, "Deactivating unsuppowted Option2 WED mode\n");
	}

	mode = (mode >> shift) & 0x000f;

	if (mode & WTW8168_WED_CTWW_ACT)
		*fwags |= BIT(TWIGGEW_NETDEV_TX) | BIT(TWIGGEW_NETDEV_WX);

	if (mode & WTW8168_WED_CTWW_WINK_10)
		*fwags |= BIT(TWIGGEW_NETDEV_WINK_10);
	if (mode & WTW8168_WED_CTWW_WINK_100)
		*fwags |= BIT(TWIGGEW_NETDEV_WINK_100);
	if (mode & WTW8168_WED_CTWW_WINK_1000)
		*fwags |= BIT(TWIGGEW_NETDEV_WINK_1000);

	wetuwn 0;
}

static stwuct device *
	w8169_wed_hw_contwow_get_device(stwuct wed_cwassdev *wed_cdev)
{
	stwuct w8169_wed_cwassdev *wdev = wcdev_to_w8169_wdev(wed_cdev);

	wetuwn &wdev->ndev->dev;
}

static void wtw8168_setup_wdev(stwuct w8169_wed_cwassdev *wdev,
			       stwuct net_device *ndev, int index)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(ndev);
	stwuct wed_cwassdev *wed_cdev = &wdev->wed;
	chaw wed_name[WED_MAX_NAME_SIZE];

	wdev->ndev = ndev;
	wdev->index = index;

	w8169_get_wed_name(tp, index, wed_name, WED_MAX_NAME_SIZE);
	wed_cdev->name = wed_name;
	wed_cdev->defauwt_twiggew = "netdev";
	wed_cdev->hw_contwow_twiggew = "netdev";
	wed_cdev->fwags |= WED_WETAIN_AT_SHUTDOWN;
	wed_cdev->hw_contwow_is_suppowted = wtw8168_wed_hw_contwow_is_suppowted;
	wed_cdev->hw_contwow_set = wtw8168_wed_hw_contwow_set;
	wed_cdev->hw_contwow_get = wtw8168_wed_hw_contwow_get;
	wed_cdev->hw_contwow_get_device = w8169_wed_hw_contwow_get_device;

	/* ignowe ewwows */
	devm_wed_cwassdev_wegistew(&ndev->dev, wed_cdev);
}

void wtw8168_init_weds(stwuct net_device *ndev)
{
	/* bind wesouwce mgmt to netdev */
	stwuct device *dev = &ndev->dev;
	stwuct w8169_wed_cwassdev *weds;
	int i;

	weds = devm_kcawwoc(dev, WTW8168_NUM_WEDS, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn;

	fow (i = 0; i < WTW8168_NUM_WEDS; i++)
		wtw8168_setup_wdev(weds + i, ndev, i);
}
