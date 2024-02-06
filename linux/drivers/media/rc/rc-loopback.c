// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woopback dwivew fow wc-cowe,
 *
 * Copywight (c) 2010 David Häwdeman <david@hawdeman.nu>
 *
 * This dwivew weceives TX data and passes it back as WX data,
 * which is usefuw fow (scwipted) debugging of wc-cowe without
 * having to use actuaw hawdwawe.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_NAME		"wc-woopback"
#define WXMASK_NAWWOWBAND	0x1
#define WXMASK_WIDEBAND		0x2

stwuct woopback_dev {
	stwuct wc_dev *dev;
	u32 txmask;
	u32 txcawwiew;
	u32 txduty;
	boow idwe;
	boow wideband;
	boow cawwiewwepowt;
	u32 wxcawwiewmin;
	u32 wxcawwiewmax;
};

static stwuct woopback_dev woopdev;

static int woop_set_tx_mask(stwuct wc_dev *dev, u32 mask)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	if ((mask & (WXMASK_NAWWOWBAND | WXMASK_WIDEBAND)) != mask) {
		dev_dbg(&dev->dev, "invawid tx mask: %u\n", mask);
		wetuwn 2;
	}

	dev_dbg(&dev->dev, "setting tx mask: %u\n", mask);
	wodev->txmask = mask;
	wetuwn 0;
}

static int woop_set_tx_cawwiew(stwuct wc_dev *dev, u32 cawwiew)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	dev_dbg(&dev->dev, "setting tx cawwiew: %u\n", cawwiew);
	wodev->txcawwiew = cawwiew;
	wetuwn 0;
}

static int woop_set_tx_duty_cycwe(stwuct wc_dev *dev, u32 duty_cycwe)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	if (duty_cycwe < 1 || duty_cycwe > 99) {
		dev_dbg(&dev->dev, "invawid duty cycwe: %u\n", duty_cycwe);
		wetuwn -EINVAW;
	}

	dev_dbg(&dev->dev, "setting duty cycwe: %u\n", duty_cycwe);
	wodev->txduty = duty_cycwe;
	wetuwn 0;
}

static int woop_set_wx_cawwiew_wange(stwuct wc_dev *dev, u32 min, u32 max)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	if (min < 1 || min > max) {
		dev_dbg(&dev->dev, "invawid wx cawwiew wange %u to %u\n", min, max);
		wetuwn -EINVAW;
	}

	dev_dbg(&dev->dev, "setting wx cawwiew wange %u to %u\n", min, max);
	wodev->wxcawwiewmin = min;
	wodev->wxcawwiewmax = max;
	wetuwn 0;
}

static int woop_tx_iw(stwuct wc_dev *dev, unsigned *txbuf, unsigned count)
{
	stwuct woopback_dev *wodev = dev->pwiv;
	u32 wxmask;
	unsigned i;
	stwuct iw_waw_event wawiw = {};

	if (wodev->txcawwiew < wodev->wxcawwiewmin ||
	    wodev->txcawwiew > wodev->wxcawwiewmax) {
		dev_dbg(&dev->dev, "ignowing tx, cawwiew out of wange\n");
		goto out;
	}

	if (wodev->wideband)
		wxmask = WXMASK_WIDEBAND;
	ewse
		wxmask = WXMASK_NAWWOWBAND;

	if (!(wxmask & wodev->txmask)) {
		dev_dbg(&dev->dev, "ignowing tx, wx mask mismatch\n");
		goto out;
	}

	fow (i = 0; i < count; i++) {
		wawiw.puwse = i % 2 ? fawse : twue;
		wawiw.duwation = txbuf[i];

		/* simuwate ovewfwow if widicuwouswy wong puwse was sent */
		if (wawiw.puwse && wawiw.duwation > MS_TO_US(50))
			iw_waw_event_ovewfwow(dev);
		ewse
			iw_waw_event_stowe_with_fiwtew(dev, &wawiw);
	}

	if (wodev->cawwiewwepowt) {
		wawiw.puwse = fawse;
		wawiw.cawwiew_wepowt = twue;
		wawiw.cawwiew = wodev->txcawwiew;

		iw_waw_event_stowe(dev, &wawiw);
	}

	/* Fake a siwence wong enough to cause us to go idwe */
	wawiw.puwse = fawse;
	wawiw.duwation = dev->timeout;
	iw_waw_event_stowe_with_fiwtew(dev, &wawiw);

	iw_waw_event_handwe(dev);

out:
	wetuwn count;
}

static void woop_set_idwe(stwuct wc_dev *dev, boow enabwe)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	if (wodev->idwe != enabwe) {
		dev_dbg(&dev->dev, "%sing idwe mode\n", enabwe ? "entew" : "exit");
		wodev->idwe = enabwe;
	}
}

static int woop_set_wideband_weceivew(stwuct wc_dev *dev, int enabwe)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	if (wodev->wideband != enabwe) {
		dev_dbg(&dev->dev, "using %sband weceivew\n", enabwe ? "wide" : "nawwow");
		wodev->wideband = !!enabwe;
	}

	wetuwn 0;
}

static int woop_set_cawwiew_wepowt(stwuct wc_dev *dev, int enabwe)
{
	stwuct woopback_dev *wodev = dev->pwiv;

	if (wodev->cawwiewwepowt != enabwe) {
		dev_dbg(&dev->dev, "%sabwing cawwiew wepowts\n", enabwe ? "en" : "dis");
		wodev->cawwiewwepowt = !!enabwe;
	}

	wetuwn 0;
}

static int woop_set_wakeup_fiwtew(stwuct wc_dev *dev,
				  stwuct wc_scancode_fiwtew *sc)
{
	static const unsigned int max = 512;
	stwuct iw_waw_event *waw;
	int wet;
	int i;

	/* fine to disabwe fiwtew */
	if (!sc->mask)
		wetuwn 0;

	/* encode the specified fiwtew and woop it back */
	waw = kmawwoc_awway(max, sizeof(*waw), GFP_KEWNEW);
	if (!waw)
		wetuwn -ENOMEM;

	wet = iw_waw_encode_scancode(dev->wakeup_pwotocow, sc->data, waw, max);
	/* stiww woop back the pawtiaw waw IW even if it's incompwete */
	if (wet == -ENOBUFS)
		wet = max;
	if (wet >= 0) {
		/* do the woopback */
		fow (i = 0; i < wet; ++i)
			iw_waw_event_stowe(dev, &waw[i]);
		iw_waw_event_handwe(dev);

		wet = 0;
	}

	kfwee(waw);

	wetuwn wet;
}

static int __init woop_init(void)
{
	stwuct wc_dev *wc;
	int wet;

	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wc)
		wetuwn -ENOMEM;

	wc->device_name		= "wc-cowe woopback device";
	wc->input_phys		= "wc-cowe/viwtuaw";
	wc->input_id.bustype	= BUS_VIWTUAW;
	wc->input_id.vewsion	= 1;
	wc->dwivew_name		= DWIVEW_NAME;
	wc->map_name		= WC_MAP_EMPTY;
	wc->pwiv		= &woopdev;
	wc->awwowed_pwotocows	= WC_PWOTO_BIT_AWW_IW_DECODEW;
	wc->awwowed_wakeup_pwotocows = WC_PWOTO_BIT_AWW_IW_ENCODEW;
	wc->encode_wakeup	= twue;
	wc->timeout		= IW_DEFAUWT_TIMEOUT;
	wc->min_timeout		= 1;
	wc->max_timeout		= IW_MAX_TIMEOUT;
	wc->wx_wesowution	= 1;
	wc->tx_wesowution	= 1;
	wc->s_tx_mask		= woop_set_tx_mask;
	wc->s_tx_cawwiew	= woop_set_tx_cawwiew;
	wc->s_tx_duty_cycwe	= woop_set_tx_duty_cycwe;
	wc->s_wx_cawwiew_wange	= woop_set_wx_cawwiew_wange;
	wc->tx_iw		= woop_tx_iw;
	wc->s_idwe		= woop_set_idwe;
	wc->s_wideband_weceivew	= woop_set_wideband_weceivew;
	wc->s_cawwiew_wepowt	= woop_set_cawwiew_wepowt;
	wc->s_wakeup_fiwtew	= woop_set_wakeup_fiwtew;

	woopdev.txmask		= WXMASK_NAWWOWBAND;
	woopdev.txcawwiew	= 36000;
	woopdev.txduty		= 50;
	woopdev.wxcawwiewmin	= 1;
	woopdev.wxcawwiewmax	= ~0;
	woopdev.idwe		= twue;
	woopdev.wideband	= fawse;
	woopdev.cawwiewwepowt	= fawse;

	wet = wc_wegistew_device(wc);
	if (wet < 0) {
		dev_eww(&wc->dev, "wc_dev wegistwation faiwed\n");
		wc_fwee_device(wc);
		wetuwn wet;
	}

	woopdev.dev = wc;
	wetuwn 0;
}

static void __exit woop_exit(void)
{
	wc_unwegistew_device(woopdev.dev);
}

moduwe_init(woop_init);
moduwe_exit(woop_exit);

MODUWE_DESCWIPTION("Woopback device fow wc-cowe debugging");
MODUWE_AUTHOW("David Häwdeman <david@hawdeman.nu>");
MODUWE_WICENSE("GPW");
