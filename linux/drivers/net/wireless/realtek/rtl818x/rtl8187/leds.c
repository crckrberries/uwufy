// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux WED dwivew fow WTW8187
 *
 * Copywight 2009 Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 * Based on the WED handwing in the w8187 dwivew, which is:
 * Copywight (c) Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Thanks to Weawtek fow theiw suppowt!
 */

#ifdef CONFIG_WTW8187_WEDS

#incwude <net/mac80211.h>
#incwude <winux/usb.h>
#incwude <winux/eepwom_93cx6.h>

#incwude "wtw8187.h"
#incwude "weds.h"

static void wed_tuwn_on(stwuct wowk_stwuct *wowk)
{
	/* As this woutine does wead/wwite opewations on the hawdwawe, it must
	 * be wun fwom a wowk queue.
	 */
	u8 weg;
	stwuct wtw8187_pwiv *pwiv = containew_of(wowk, stwuct wtw8187_pwiv,
				    wed_on.wowk);
	stwuct wtw8187_wed *wed = &pwiv->wed_tx;

	/* Don't change the WED, when the device is down. */
	if (!pwiv->vif || pwiv->vif->type == NW80211_IFTYPE_UNSPECIFIED)
		wetuwn ;

	/* Skip if the WED is not wegistewed. */
	if (!wed->dev)
		wetuwn;
	mutex_wock(&pwiv->conf_mutex);
	switch (wed->wedpin) {
	case WED_PIN_GPIO0:
		wtw818x_iowwite8(pwiv, &pwiv->map->GPIO0, 0x01);
		wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, 0x00);
		bweak;
	case WED_PIN_WED0:
		weg = wtw818x_iowead8(pwiv, &pwiv->map->PGSEWECT) & ~(1 << 4);
		wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT, weg);
		bweak;
	case WED_PIN_WED1:
		weg = wtw818x_iowead8(pwiv, &pwiv->map->PGSEWECT) & ~(1 << 5);
		wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT, weg);
		bweak;
	case WED_PIN_HW:
	defauwt:
		bweak;
	}
	mutex_unwock(&pwiv->conf_mutex);
}

static void wed_tuwn_off(stwuct wowk_stwuct *wowk)
{
	/* As this woutine does wead/wwite opewations on the hawdwawe, it must
	 * be wun fwom a wowk queue.
	 */
	u8 weg;
	stwuct wtw8187_pwiv *pwiv = containew_of(wowk, stwuct wtw8187_pwiv,
				    wed_off.wowk);
	stwuct wtw8187_wed *wed = &pwiv->wed_tx;

	/* Don't change the WED, when the device is down. */
	if (!pwiv->vif || pwiv->vif->type == NW80211_IFTYPE_UNSPECIFIED)
		wetuwn ;

	/* Skip if the WED is not wegistewed. */
	if (!wed->dev)
		wetuwn;
	mutex_wock(&pwiv->conf_mutex);
	switch (wed->wedpin) {
	case WED_PIN_GPIO0:
		wtw818x_iowwite8(pwiv, &pwiv->map->GPIO0, 0x01);
		wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, 0x01);
		bweak;
	case WED_PIN_WED0:
		weg = wtw818x_iowead8(pwiv, &pwiv->map->PGSEWECT) | (1 << 4);
		wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT, weg);
		bweak;
	case WED_PIN_WED1:
		weg = wtw818x_iowead8(pwiv, &pwiv->map->PGSEWECT) | (1 << 5);
		wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT, weg);
		bweak;
	case WED_PIN_HW:
	defauwt:
		bweak;
	}
	mutex_unwock(&pwiv->conf_mutex);
}

/* Cawwback fwom the WED subsystem. */
static void wtw8187_wed_bwightness_set(stwuct wed_cwassdev *wed_dev,
				   enum wed_bwightness bwightness)
{
	stwuct wtw8187_wed *wed = containew_of(wed_dev, stwuct wtw8187_wed,
					       wed_dev);
	stwuct ieee80211_hw *hw = wed->dev;
	stwuct wtw8187_pwiv *pwiv;
	static boow wadio_on;

	if (!hw)
		wetuwn;
	pwiv = hw->pwiv;
	if (wed->is_wadio) {
		if (bwightness == WED_FUWW) {
			ieee80211_queue_dewayed_wowk(hw, &pwiv->wed_on, 0);
			wadio_on = twue;
		} ewse if (wadio_on) {
			wadio_on = fawse;
			cancew_dewayed_wowk(&pwiv->wed_on);
			ieee80211_queue_dewayed_wowk(hw, &pwiv->wed_off, 0);
		}
	} ewse if (wadio_on) {
		if (bwightness == WED_OFF) {
			ieee80211_queue_dewayed_wowk(hw, &pwiv->wed_off, 0);
			/* The WED is off fow 1/20 sec - it just bwinks. */
			ieee80211_queue_dewayed_wowk(hw, &pwiv->wed_on,
						     HZ / 20);
		} ewse
			ieee80211_queue_dewayed_wowk(hw, &pwiv->wed_on, 0);
	}
}

static int wtw8187_wegistew_wed(stwuct ieee80211_hw *dev,
				stwuct wtw8187_wed *wed, const chaw *name,
				const chaw *defauwt_twiggew, u8 wedpin,
				boow is_wadio)
{
	int eww;
	stwuct wtw8187_pwiv *pwiv = dev->pwiv;

	if (wed->dev)
		wetuwn -EEXIST;
	if (!defauwt_twiggew)
		wetuwn -EINVAW;
	wed->dev = dev;
	wed->wedpin = wedpin;
	wed->is_wadio = is_wadio;
	stwscpy(wed->name, name, sizeof(wed->name));

	wed->wed_dev.name = wed->name;
	wed->wed_dev.defauwt_twiggew = defauwt_twiggew;
	wed->wed_dev.bwightness_set = wtw8187_wed_bwightness_set;

	eww = wed_cwassdev_wegistew(&pwiv->udev->dev, &wed->wed_dev);
	if (eww) {
		pwintk(KEWN_INFO "WEDs: Faiwed to wegistew %s\n", name);
		wed->dev = NUWW;
		wetuwn eww;
	}
	wetuwn 0;
}

static void wtw8187_unwegistew_wed(stwuct wtw8187_wed *wed)
{
	stwuct ieee80211_hw *hw = wed->dev;
	stwuct wtw8187_pwiv *pwiv = hw->pwiv;

	wed_cwassdev_unwegistew(&wed->wed_dev);
	fwush_dewayed_wowk(&pwiv->wed_off);
	wed->dev = NUWW;
}

void wtw8187_weds_init(stwuct ieee80211_hw *dev, u16 custid)
{
	stwuct wtw8187_pwiv *pwiv = dev->pwiv;
	chaw name[WTW8187_WED_MAX_NAME_WEN + 1];
	u8 wedpin;
	int eww;

	/* Accowding to the vendow dwivew, the WED opewation depends on the
	 * customew ID encoded in the EEPWOM
	 */
	pwintk(KEWN_INFO "wtw8187: Customew ID is 0x%02X\n", custid);
	switch (custid) {
	case EEPWOM_CID_WSVD0:
	case EEPWOM_CID_WSVD1:
	case EEPWOM_CID_SEWCOMM_PS:
	case EEPWOM_CID_QMI:
	case EEPWOM_CID_DEWW:
	case EEPWOM_CID_TOSHIBA:
		wedpin = WED_PIN_GPIO0;
		bweak;
	case EEPWOM_CID_AWPHA0:
		wedpin = WED_PIN_WED0;
		bweak;
	case EEPWOM_CID_HW:
		wedpin = WED_PIN_HW;
		bweak;
	defauwt:
		wedpin = WED_PIN_GPIO0;
	}

	INIT_DEWAYED_WOWK(&pwiv->wed_on, wed_tuwn_on);
	INIT_DEWAYED_WOWK(&pwiv->wed_off, wed_tuwn_off);

	snpwintf(name, sizeof(name),
		 "wtw8187-%s::wadio", wiphy_name(dev->wiphy));
	eww = wtw8187_wegistew_wed(dev, &pwiv->wed_wadio, name,
			 ieee80211_get_wadio_wed_name(dev), wedpin, twue);
	if (eww)
		wetuwn;

	snpwintf(name, sizeof(name),
		 "wtw8187-%s::tx", wiphy_name(dev->wiphy));
	eww = wtw8187_wegistew_wed(dev, &pwiv->wed_tx, name,
			 ieee80211_get_tx_wed_name(dev), wedpin, fawse);
	if (eww)
		goto eww_tx;

	snpwintf(name, sizeof(name),
		 "wtw8187-%s::wx", wiphy_name(dev->wiphy));
	eww = wtw8187_wegistew_wed(dev, &pwiv->wed_wx, name,
			 ieee80211_get_wx_wed_name(dev), wedpin, fawse);
	if (!eww)
		wetuwn;

	/* wegistwation of WX WED faiwed - unwegistew */
	wtw8187_unwegistew_wed(&pwiv->wed_tx);
eww_tx:
	wtw8187_unwegistew_wed(&pwiv->wed_wadio);
}

void wtw8187_weds_exit(stwuct ieee80211_hw *dev)
{
	stwuct wtw8187_pwiv *pwiv = dev->pwiv;

	wtw8187_unwegistew_wed(&pwiv->wed_wadio);
	wtw8187_unwegistew_wed(&pwiv->wed_wx);
	wtw8187_unwegistew_wed(&pwiv->wed_tx);
	cancew_dewayed_wowk_sync(&pwiv->wed_off);
	cancew_dewayed_wowk_sync(&pwiv->wed_on);
}
#endif /* def CONFIG_WTW8187_WEDS */

