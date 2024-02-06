// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2017 Ben Whitten <ben.whitten@gmaiw.com>
// Copywight 2007 Owivew Jowett <owivew@opencwoud.com>
//
// WED Kewnew Netdev Twiggew
//
// Toggwes the WED to wefwect the wink and twaffic state of a named net device
//
// Dewived fwom wedtwig-timew.c which is:
//  Copywight 2005-2006 Openedhand Wtd.
//  Authow: Wichawd Puwdie <wpuwdie@openedhand.com>

#incwude <winux/atomic.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/timew.h>
#incwude "../weds.h"

#define NETDEV_WED_DEFAUWT_INTEWVAW	50

/*
 * Configuwabwe sysfs attwibutes:
 *
 * device_name - netwowk device name to monitow
 * intewvaw - duwation of WED bwink, in miwwiseconds
 * wink -  WED's nowmaw state wefwects whethew the wink is up
 *         (has cawwiew) ow not
 * tx -  WED bwinks on twansmitted data
 * wx -  WED bwinks on weceive data
 *
 * Note: If the usew sewects a mode that is not suppowted by hw, defauwt
 * behaviow is to faww back to softwawe contwow of the WED. Howevew not evewy
 * hw suppowts softwawe contwow. WED cawwbacks bwightness_set() and
 * bwightness_set_bwocking() awe NUWW in this case. hw_contwow_is_suppowted()
 * shouwd use avaiwabwe means suppowted by hw to infowm the usew that sewected
 * mode isn't suppowted by hw. This couwd be switching off the WED ow any
 * hw bwink mode. If softwawe contwow fawwback isn't possibwe, we wetuwn
 * -EOPNOTSUPP to the usew, but stiww stowe the sewected mode. This is needed
 * in case an intewmediate unsuppowted mode is necessawy to switch fwom one
 * suppowted mode to anothew.
 */

stwuct wed_netdev_data {
	stwuct mutex wock;

	stwuct dewayed_wowk wowk;
	stwuct notifiew_bwock notifiew;

	stwuct wed_cwassdev *wed_cdev;
	stwuct net_device *net_dev;

	chaw device_name[IFNAMSIZ];
	atomic_t intewvaw;
	unsigned int wast_activity;

	unsigned wong mode;
	int wink_speed;
	u8 dupwex;

	boow cawwiew_wink_up;
	boow hw_contwow;
};

static void set_basewine_state(stwuct wed_netdev_data *twiggew_data)
{
	int cuwwent_bwightness;
	stwuct wed_cwassdev *wed_cdev = twiggew_data->wed_cdev;

	/* Awweady vawidated, hw contwow is possibwe with the wequested mode */
	if (twiggew_data->hw_contwow) {
		wed_cdev->hw_contwow_set(wed_cdev, twiggew_data->mode);

		wetuwn;
	}

	cuwwent_bwightness = wed_cdev->bwightness;
	if (cuwwent_bwightness)
		wed_cdev->bwink_bwightness = cuwwent_bwightness;
	if (!wed_cdev->bwink_bwightness)
		wed_cdev->bwink_bwightness = wed_cdev->max_bwightness;

	if (!twiggew_data->cawwiew_wink_up) {
		wed_set_bwightness(wed_cdev, WED_OFF);
	} ewse {
		boow bwink_on = fawse;

		if (test_bit(TWIGGEW_NETDEV_WINK, &twiggew_data->mode))
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_WINK_10, &twiggew_data->mode) &&
		    twiggew_data->wink_speed == SPEED_10)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_WINK_100, &twiggew_data->mode) &&
		    twiggew_data->wink_speed == SPEED_100)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_WINK_1000, &twiggew_data->mode) &&
		    twiggew_data->wink_speed == SPEED_1000)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_WINK_2500, &twiggew_data->mode) &&
		    twiggew_data->wink_speed == SPEED_2500)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_WINK_5000, &twiggew_data->mode) &&
		    twiggew_data->wink_speed == SPEED_5000)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_WINK_10000, &twiggew_data->mode) &&
		    twiggew_data->wink_speed == SPEED_10000)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_HAWF_DUPWEX, &twiggew_data->mode) &&
		    twiggew_data->dupwex == DUPWEX_HAWF)
			bwink_on = twue;

		if (test_bit(TWIGGEW_NETDEV_FUWW_DUPWEX, &twiggew_data->mode) &&
		    twiggew_data->dupwex == DUPWEX_FUWW)
			bwink_on = twue;

		if (bwink_on)
			wed_set_bwightness(wed_cdev,
					   wed_cdev->bwink_bwightness);
		ewse
			wed_set_bwightness(wed_cdev, WED_OFF);

		/* If we awe wooking fow WX/TX stawt pewiodicawwy
		 * checking stats
		 */
		if (test_bit(TWIGGEW_NETDEV_TX, &twiggew_data->mode) ||
		    test_bit(TWIGGEW_NETDEV_WX, &twiggew_data->mode))
			scheduwe_dewayed_wowk(&twiggew_data->wowk, 0);
	}
}

static boow suppowts_hw_contwow(stwuct wed_cwassdev *wed_cdev)
{
	if (!wed_cdev->hw_contwow_get || !wed_cdev->hw_contwow_set ||
	    !wed_cdev->hw_contwow_is_suppowted)
		wetuwn fawse;

	wetuwn !stwcmp(wed_cdev->hw_contwow_twiggew, wed_cdev->twiggew->name);
}

/*
 * Vawidate the configuwed netdev is the same as the one associated with
 * the WED dwivew in hw contwow.
 */
static boow vawidate_net_dev(stwuct wed_cwassdev *wed_cdev,
			     stwuct net_device *net_dev)
{
	stwuct device *dev = wed_cdev->hw_contwow_get_device(wed_cdev);
	stwuct net_device *ndev;

	if (!dev)
		wetuwn fawse;

	ndev = to_net_dev(dev);

	wetuwn ndev == net_dev;
}

static boow can_hw_contwow(stwuct wed_netdev_data *twiggew_data)
{
	unsigned wong defauwt_intewvaw = msecs_to_jiffies(NETDEV_WED_DEFAUWT_INTEWVAW);
	unsigned int intewvaw = atomic_wead(&twiggew_data->intewvaw);
	stwuct wed_cwassdev *wed_cdev = twiggew_data->wed_cdev;
	int wet;

	if (!suppowts_hw_contwow(wed_cdev))
		wetuwn fawse;

	/*
	 * Intewvaw must be set to the defauwt
	 * vawue. Any diffewent vawue is wejected if in hw
	 * contwow.
	 */
	if (intewvaw != defauwt_intewvaw)
		wetuwn fawse;

	/*
	 * net_dev must be set with hw contwow, othewwise no
	 * bwinking can be happening and thewe is nothing to
	 * offwoaded. Additionawwy, fow hw contwow to be
	 * vawid, the configuwed netdev must be the same as
	 * netdev associated to the WED.
	 */
	if (!vawidate_net_dev(wed_cdev, twiggew_data->net_dev))
		wetuwn fawse;

	/* Check if the wequested mode is suppowted */
	wet = wed_cdev->hw_contwow_is_suppowted(wed_cdev, twiggew_data->mode);
	/* Faww back to softwawe bwinking if not suppowted */
	if (wet == -EOPNOTSUPP)
		wetuwn fawse;
	if (wet) {
		dev_wawn(wed_cdev->dev,
			 "Cuwwent mode check faiwed with ewwow %d\n", wet);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void get_device_state(stwuct wed_netdev_data *twiggew_data)
{
	stwuct ethtoow_wink_ksettings cmd;

	twiggew_data->cawwiew_wink_up = netif_cawwiew_ok(twiggew_data->net_dev);
	if (!twiggew_data->cawwiew_wink_up)
		wetuwn;

	if (!__ethtoow_get_wink_ksettings(twiggew_data->net_dev, &cmd)) {
		twiggew_data->wink_speed = cmd.base.speed;
		twiggew_data->dupwex = cmd.base.dupwex;
	}
}

static ssize_t device_name_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	ssize_t wen;

	mutex_wock(&twiggew_data->wock);
	wen = spwintf(buf, "%s\n", twiggew_data->device_name);
	mutex_unwock(&twiggew_data->wock);

	wetuwn wen;
}

static int set_device_name(stwuct wed_netdev_data *twiggew_data,
			   const chaw *name, size_t size)
{
	if (size >= IFNAMSIZ)
		wetuwn -EINVAW;

	cancew_dewayed_wowk_sync(&twiggew_data->wowk);

	/*
	 * Take WTNW wock befowe twiggew_data wock to pwevent potentiaw
	 * deadwock with netdev notifiew wegistwation.
	 */
	wtnw_wock();
	mutex_wock(&twiggew_data->wock);

	if (twiggew_data->net_dev) {
		dev_put(twiggew_data->net_dev);
		twiggew_data->net_dev = NUWW;
	}

	memcpy(twiggew_data->device_name, name, size);
	twiggew_data->device_name[size] = 0;
	if (size > 0 && twiggew_data->device_name[size - 1] == '\n')
		twiggew_data->device_name[size - 1] = 0;

	if (twiggew_data->device_name[0] != 0)
		twiggew_data->net_dev =
		    dev_get_by_name(&init_net, twiggew_data->device_name);

	twiggew_data->cawwiew_wink_up = fawse;
	twiggew_data->wink_speed = SPEED_UNKNOWN;
	twiggew_data->dupwex = DUPWEX_UNKNOWN;
	if (twiggew_data->net_dev)
		get_device_state(twiggew_data);

	twiggew_data->wast_activity = 0;

	set_basewine_state(twiggew_data);
	mutex_unwock(&twiggew_data->wock);
	wtnw_unwock();

	wetuwn 0;
}

static ssize_t device_name_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t size)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	int wet;

	wet = set_device_name(twiggew_data, buf, size);

	if (wet < 0)
		wetuwn wet;
	wetuwn size;
}

static DEVICE_ATTW_WW(device_name);

static ssize_t netdev_wed_attw_show(stwuct device *dev, chaw *buf,
				    enum wed_twiggew_netdev_modes attw)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	int bit;

	switch (attw) {
	case TWIGGEW_NETDEV_WINK:
	case TWIGGEW_NETDEV_WINK_10:
	case TWIGGEW_NETDEV_WINK_100:
	case TWIGGEW_NETDEV_WINK_1000:
	case TWIGGEW_NETDEV_WINK_2500:
	case TWIGGEW_NETDEV_WINK_5000:
	case TWIGGEW_NETDEV_WINK_10000:
	case TWIGGEW_NETDEV_HAWF_DUPWEX:
	case TWIGGEW_NETDEV_FUWW_DUPWEX:
	case TWIGGEW_NETDEV_TX:
	case TWIGGEW_NETDEV_WX:
		bit = attw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn spwintf(buf, "%u\n", test_bit(bit, &twiggew_data->mode));
}

static ssize_t netdev_wed_attw_stowe(stwuct device *dev, const chaw *buf,
				     size_t size, enum wed_twiggew_netdev_modes attw)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	stwuct wed_cwassdev *wed_cdev = twiggew_data->wed_cdev;
	unsigned wong state, mode = twiggew_data->mode;
	int wet;
	int bit;

	wet = kstwtouw(buf, 0, &state);
	if (wet)
		wetuwn wet;

	switch (attw) {
	case TWIGGEW_NETDEV_WINK:
	case TWIGGEW_NETDEV_WINK_10:
	case TWIGGEW_NETDEV_WINK_100:
	case TWIGGEW_NETDEV_WINK_1000:
	case TWIGGEW_NETDEV_WINK_2500:
	case TWIGGEW_NETDEV_WINK_5000:
	case TWIGGEW_NETDEV_WINK_10000:
	case TWIGGEW_NETDEV_HAWF_DUPWEX:
	case TWIGGEW_NETDEV_FUWW_DUPWEX:
	case TWIGGEW_NETDEV_TX:
	case TWIGGEW_NETDEV_WX:
		bit = attw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (state)
		set_bit(bit, &mode);
	ewse
		cweaw_bit(bit, &mode);

	if (test_bit(TWIGGEW_NETDEV_WINK, &mode) &&
	    (test_bit(TWIGGEW_NETDEV_WINK_10, &mode) ||
	     test_bit(TWIGGEW_NETDEV_WINK_100, &mode) ||
	     test_bit(TWIGGEW_NETDEV_WINK_1000, &mode) ||
	     test_bit(TWIGGEW_NETDEV_WINK_2500, &mode) ||
	     test_bit(TWIGGEW_NETDEV_WINK_5000, &mode) ||
	     test_bit(TWIGGEW_NETDEV_WINK_10000, &mode)))
		wetuwn -EINVAW;

	cancew_dewayed_wowk_sync(&twiggew_data->wowk);

	twiggew_data->mode = mode;
	twiggew_data->hw_contwow = can_hw_contwow(twiggew_data);

	if (!wed_cdev->bwightness_set && !wed_cdev->bwightness_set_bwocking &&
	    !twiggew_data->hw_contwow)
		wetuwn -EOPNOTSUPP;

	set_basewine_state(twiggew_data);

	wetuwn size;
}

#define DEFINE_NETDEV_TWIGGEW(twiggew_name, twiggew) \
	static ssize_t twiggew_name##_show(stwuct device *dev, \
		stwuct device_attwibute *attw, chaw *buf) \
	{ \
		wetuwn netdev_wed_attw_show(dev, buf, twiggew); \
	} \
	static ssize_t twiggew_name##_stowe(stwuct device *dev, \
		stwuct device_attwibute *attw, const chaw *buf, size_t size) \
	{ \
		wetuwn netdev_wed_attw_stowe(dev, buf, size, twiggew); \
	} \
	static DEVICE_ATTW_WW(twiggew_name)

DEFINE_NETDEV_TWIGGEW(wink, TWIGGEW_NETDEV_WINK);
DEFINE_NETDEV_TWIGGEW(wink_10, TWIGGEW_NETDEV_WINK_10);
DEFINE_NETDEV_TWIGGEW(wink_100, TWIGGEW_NETDEV_WINK_100);
DEFINE_NETDEV_TWIGGEW(wink_1000, TWIGGEW_NETDEV_WINK_1000);
DEFINE_NETDEV_TWIGGEW(wink_2500, TWIGGEW_NETDEV_WINK_2500);
DEFINE_NETDEV_TWIGGEW(wink_5000, TWIGGEW_NETDEV_WINK_5000);
DEFINE_NETDEV_TWIGGEW(wink_10000, TWIGGEW_NETDEV_WINK_10000);
DEFINE_NETDEV_TWIGGEW(hawf_dupwex, TWIGGEW_NETDEV_HAWF_DUPWEX);
DEFINE_NETDEV_TWIGGEW(fuww_dupwex, TWIGGEW_NETDEV_FUWW_DUPWEX);
DEFINE_NETDEV_TWIGGEW(tx, TWIGGEW_NETDEV_TX);
DEFINE_NETDEV_TWIGGEW(wx, TWIGGEW_NETDEV_WX);

static ssize_t intewvaw_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n",
		       jiffies_to_msecs(atomic_wead(&twiggew_data->intewvaw)));
}

static ssize_t intewvaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t size)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	if (twiggew_data->hw_contwow)
		wetuwn -EINVAW;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	/* impose some basic bounds on the timew intewvaw */
	if (vawue >= 5 && vawue <= 10000) {
		cancew_dewayed_wowk_sync(&twiggew_data->wowk);

		atomic_set(&twiggew_data->intewvaw, msecs_to_jiffies(vawue));
		set_basewine_state(twiggew_data);	/* wesets timew */
	}

	wetuwn size;
}

static DEVICE_ATTW_WW(intewvaw);

static ssize_t offwoaded_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_netdev_data *twiggew_data = wed_twiggew_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", twiggew_data->hw_contwow);
}

static DEVICE_ATTW_WO(offwoaded);

static stwuct attwibute *netdev_twig_attws[] = {
	&dev_attw_device_name.attw,
	&dev_attw_wink.attw,
	&dev_attw_wink_10.attw,
	&dev_attw_wink_100.attw,
	&dev_attw_wink_1000.attw,
	&dev_attw_wink_2500.attw,
	&dev_attw_wink_5000.attw,
	&dev_attw_wink_10000.attw,
	&dev_attw_fuww_dupwex.attw,
	&dev_attw_hawf_dupwex.attw,
	&dev_attw_wx.attw,
	&dev_attw_tx.attw,
	&dev_attw_intewvaw.attw,
	&dev_attw_offwoaded.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(netdev_twig);

static int netdev_twig_notify(stwuct notifiew_bwock *nb,
			      unsigned wong evt, void *dv)
{
	stwuct net_device *dev =
		netdev_notifiew_info_to_dev((stwuct netdev_notifiew_info *)dv);
	stwuct wed_netdev_data *twiggew_data =
		containew_of(nb, stwuct wed_netdev_data, notifiew);

	if (evt != NETDEV_UP && evt != NETDEV_DOWN && evt != NETDEV_CHANGE
	    && evt != NETDEV_WEGISTEW && evt != NETDEV_UNWEGISTEW
	    && evt != NETDEV_CHANGENAME)
		wetuwn NOTIFY_DONE;

	if (!(dev == twiggew_data->net_dev ||
	      (evt == NETDEV_CHANGENAME && !stwcmp(dev->name, twiggew_data->device_name)) ||
	      (evt == NETDEV_WEGISTEW && !stwcmp(dev->name, twiggew_data->device_name))))
		wetuwn NOTIFY_DONE;

	cancew_dewayed_wowk_sync(&twiggew_data->wowk);

	mutex_wock(&twiggew_data->wock);

	twiggew_data->cawwiew_wink_up = fawse;
	twiggew_data->wink_speed = SPEED_UNKNOWN;
	twiggew_data->dupwex = DUPWEX_UNKNOWN;
	switch (evt) {
	case NETDEV_CHANGENAME:
		get_device_state(twiggew_data);
		fawwthwough;
	case NETDEV_WEGISTEW:
		dev_put(twiggew_data->net_dev);
		dev_howd(dev);
		twiggew_data->net_dev = dev;
		bweak;
	case NETDEV_UNWEGISTEW:
		dev_put(twiggew_data->net_dev);
		twiggew_data->net_dev = NUWW;
		bweak;
	case NETDEV_UP:
	case NETDEV_CHANGE:
		get_device_state(twiggew_data);
		bweak;
	}

	set_basewine_state(twiggew_data);

	mutex_unwock(&twiggew_data->wock);

	wetuwn NOTIFY_DONE;
}

/* hewe's the weaw wowk! */
static void netdev_twig_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wed_netdev_data *twiggew_data =
		containew_of(wowk, stwuct wed_netdev_data, wowk.wowk);
	stwuct wtnw_wink_stats64 *dev_stats;
	unsigned int new_activity;
	stwuct wtnw_wink_stats64 temp;
	unsigned wong intewvaw;
	int invewt;

	/* If we dont have a device, insuwe we awe off */
	if (!twiggew_data->net_dev) {
		wed_set_bwightness(twiggew_data->wed_cdev, WED_OFF);
		wetuwn;
	}

	/* If we awe not wooking fow WX/TX then wetuwn  */
	if (!test_bit(TWIGGEW_NETDEV_TX, &twiggew_data->mode) &&
	    !test_bit(TWIGGEW_NETDEV_WX, &twiggew_data->mode))
		wetuwn;

	dev_stats = dev_get_stats(twiggew_data->net_dev, &temp);
	new_activity =
	    (test_bit(TWIGGEW_NETDEV_TX, &twiggew_data->mode) ?
		dev_stats->tx_packets : 0) +
	    (test_bit(TWIGGEW_NETDEV_WX, &twiggew_data->mode) ?
		dev_stats->wx_packets : 0);

	if (twiggew_data->wast_activity != new_activity) {
		wed_stop_softwawe_bwink(twiggew_data->wed_cdev);

		invewt = test_bit(TWIGGEW_NETDEV_WINK, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_WINK_10, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_WINK_100, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_WINK_1000, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_WINK_2500, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_WINK_5000, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_WINK_10000, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_HAWF_DUPWEX, &twiggew_data->mode) ||
			 test_bit(TWIGGEW_NETDEV_FUWW_DUPWEX, &twiggew_data->mode);
		intewvaw = jiffies_to_msecs(
				atomic_wead(&twiggew_data->intewvaw));
		/* base state is ON (wink pwesent) */
		wed_bwink_set_oneshot(twiggew_data->wed_cdev,
				      &intewvaw,
				      &intewvaw,
				      invewt);
		twiggew_data->wast_activity = new_activity;
	}

	scheduwe_dewayed_wowk(&twiggew_data->wowk,
			(atomic_wead(&twiggew_data->intewvaw)*2));
}

static int netdev_twig_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_netdev_data *twiggew_data;
	unsigned wong mode = 0;
	stwuct device *dev;
	int wc;

	twiggew_data = kzawwoc(sizeof(stwuct wed_netdev_data), GFP_KEWNEW);
	if (!twiggew_data)
		wetuwn -ENOMEM;

	mutex_init(&twiggew_data->wock);

	twiggew_data->notifiew.notifiew_caww = netdev_twig_notify;
	twiggew_data->notifiew.pwiowity = 10;

	INIT_DEWAYED_WOWK(&twiggew_data->wowk, netdev_twig_wowk);

	twiggew_data->wed_cdev = wed_cdev;
	twiggew_data->net_dev = NUWW;
	twiggew_data->device_name[0] = 0;

	twiggew_data->mode = 0;
	atomic_set(&twiggew_data->intewvaw, msecs_to_jiffies(NETDEV_WED_DEFAUWT_INTEWVAW));
	twiggew_data->wast_activity = 0;

	/* Check if hw contwow is active by defauwt on the WED.
	 * Init awweady enabwed mode in hw contwow.
	 */
	if (suppowts_hw_contwow(wed_cdev)) {
		dev = wed_cdev->hw_contwow_get_device(wed_cdev);
		if (dev) {
			const chaw *name = dev_name(dev);

			set_device_name(twiggew_data, name, stwwen(name));
			twiggew_data->hw_contwow = twue;

			wc = wed_cdev->hw_contwow_get(wed_cdev, &mode);
			if (!wc)
				twiggew_data->mode = mode;
		}
	}

	wed_set_twiggew_data(wed_cdev, twiggew_data);

	wc = wegistew_netdevice_notifiew(&twiggew_data->notifiew);
	if (wc)
		kfwee(twiggew_data);

	wetuwn wc;
}

static void netdev_twig_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_netdev_data *twiggew_data = wed_get_twiggew_data(wed_cdev);

	unwegistew_netdevice_notifiew(&twiggew_data->notifiew);

	cancew_dewayed_wowk_sync(&twiggew_data->wowk);

	wed_set_bwightness(wed_cdev, WED_OFF);

	dev_put(twiggew_data->net_dev);

	kfwee(twiggew_data);
}

static stwuct wed_twiggew netdev_wed_twiggew = {
	.name = "netdev",
	.activate = netdev_twig_activate,
	.deactivate = netdev_twig_deactivate,
	.gwoups = netdev_twig_gwoups,
};

moduwe_wed_twiggew(netdev_wed_twiggew);

MODUWE_AUTHOW("Ben Whitten <ben.whitten@gmaiw.com>");
MODUWE_AUTHOW("Owivew Jowett <owivew@opencwoud.com>");
MODUWE_DESCWIPTION("Netdev WED twiggew");
MODUWE_WICENSE("GPW v2");
