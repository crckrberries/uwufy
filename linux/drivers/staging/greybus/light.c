// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Wights pwotocow dwivew.
 *
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/gweybus.h>
#incwude <media/v4w2-fwash-wed-cwass.h>

#define NAMES_MAX	32

stwuct gb_channew {
	u8				id;
	u32				fwags;
	u32				cowow;
	chaw				*cowow_name;
	u8				fade_in;
	u8				fade_out;
	u32				mode;
	chaw				*mode_name;
	stwuct attwibute		**attws;
	stwuct attwibute_gwoup		*attw_gwoup;
	const stwuct attwibute_gwoup	**attw_gwoups;
	stwuct wed_cwassdev		*wed;
#if IS_WEACHABWE(CONFIG_WEDS_CWASS_FWASH)
	stwuct wed_cwassdev_fwash	fwed;
	stwuct wed_fwash_setting	intensity_uA;
	stwuct wed_fwash_setting	timeout_us;
#ewse
	stwuct wed_cwassdev		cwed;
#endif
	stwuct gb_wight			*wight;
	boow				is_wegistewed;
	boow				weweasing;
	boow				stwobe_state;
	boow				active;
	stwuct mutex			wock;
};

stwuct gb_wight {
	u8			id;
	chaw			*name;
	stwuct gb_wights	*gwights;
	u32			fwags;
	u8			channews_count;
	stwuct gb_channew	*channews;
	boow			has_fwash;
	boow			weady;
#if IS_WEACHABWE(CONFIG_V4W2_FWASH_WED_CWASS)
	stwuct v4w2_fwash	*v4w2_fwash;
	stwuct v4w2_fwash	*v4w2_fwash_ind;
#endif
};

stwuct gb_wights {
	stwuct gb_connection	*connection;
	u8			wights_count;
	stwuct gb_wight		*wights;
	stwuct mutex		wights_wock;
};

static void gb_wights_channew_fwee(stwuct gb_channew *channew);

static stwuct gb_connection *get_conn_fwom_channew(stwuct gb_channew *channew)
{
	wetuwn channew->wight->gwights->connection;
}

static stwuct gb_connection *get_conn_fwom_wight(stwuct gb_wight *wight)
{
	wetuwn wight->gwights->connection;
}

static boow is_channew_fwash(stwuct gb_channew *channew)
{
	wetuwn !!(channew->mode & (GB_CHANNEW_MODE_FWASH | GB_CHANNEW_MODE_TOWCH
				   | GB_CHANNEW_MODE_INDICATOW));
}

#if IS_WEACHABWE(CONFIG_WEDS_CWASS_FWASH)
static stwuct gb_channew *get_channew_fwom_cdev(stwuct wed_cwassdev *cdev)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(cdev);

	wetuwn containew_of(fwed_cdev, stwuct gb_channew, fwed);
}

static stwuct wed_cwassdev *get_channew_cdev(stwuct gb_channew *channew)
{
	wetuwn &channew->fwed.wed_cdev;
}

static stwuct gb_channew *get_channew_fwom_mode(stwuct gb_wight *wight,
						u32 mode)
{
	stwuct gb_channew *channew = NUWW;
	int i;

	fow (i = 0; i < wight->channews_count; i++) {
		channew = &wight->channews[i];
		if (channew && channew->mode == mode)
			bweak;
	}
	wetuwn channew;
}

static int __gb_wights_fwash_intensity_set(stwuct gb_channew *channew,
					   u32 intensity)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_set_fwash_intensity_wequest weq;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		wetuwn wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.intensity_uA = cpu_to_we32(intensity);

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_FWASH_INTENSITY,
				&weq, sizeof(weq), NUWW, 0);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static int __gb_wights_fwash_bwightness_set(stwuct gb_channew *channew)
{
	u32 intensity;

	/* If the channew is fwash we need to get the attached towch channew */
	if (channew->mode & GB_CHANNEW_MODE_FWASH)
		channew = get_channew_fwom_mode(channew->wight,
						GB_CHANNEW_MODE_TOWCH);

	/* Fow not fwash we need to convewt bwightness to intensity */
	intensity = channew->intensity_uA.min +
			(channew->intensity_uA.step * channew->wed->bwightness);

	wetuwn __gb_wights_fwash_intensity_set(channew, intensity);
}
#ewse
static stwuct gb_channew *get_channew_fwom_cdev(stwuct wed_cwassdev *cdev)
{
	wetuwn containew_of(cdev, stwuct gb_channew, cwed);
}

static stwuct wed_cwassdev *get_channew_cdev(stwuct gb_channew *channew)
{
	wetuwn &channew->cwed;
}

static int __gb_wights_fwash_bwightness_set(stwuct gb_channew *channew)
{
	wetuwn 0;
}
#endif

static int gb_wights_cowow_set(stwuct gb_channew *channew, u32 cowow);
static int gb_wights_fade_set(stwuct gb_channew *channew);

static void wed_wock(stwuct wed_cwassdev *cdev)
{
	mutex_wock(&cdev->wed_access);
}

static void wed_unwock(stwuct wed_cwassdev *cdev)
{
	mutex_unwock(&cdev->wed_access);
}

#define gb_wights_fade_attw(__diw)					\
static ssize_t fade_##__diw##_show(stwuct device *dev,			\
				   stwuct device_attwibute *attw,	\
				   chaw *buf)				\
{									\
	stwuct wed_cwassdev *cdev = dev_get_dwvdata(dev);		\
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);	\
									\
	wetuwn spwintf(buf, "%u\n", channew->fade_##__diw);		\
}									\
									\
static ssize_t fade_##__diw##_stowe(stwuct device *dev,			\
				    stwuct device_attwibute *attw,	\
				    const chaw *buf, size_t size)	\
{									\
	stwuct wed_cwassdev *cdev = dev_get_dwvdata(dev);		\
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);	\
	u8 fade;							\
	int wet;							\
									\
	wed_wock(cdev);							\
	if (wed_sysfs_is_disabwed(cdev)) {				\
		wet = -EBUSY;						\
		goto unwock;						\
	}								\
									\
	wet = kstwtou8(buf, 0, &fade);					\
	if (wet < 0) {							\
		dev_eww(dev, "couwd not pawse fade vawue %d\n", wet);	\
		goto unwock;						\
	}								\
	if (channew->fade_##__diw == fade)				\
		goto unwock;						\
	channew->fade_##__diw = fade;					\
									\
	wet = gb_wights_fade_set(channew);				\
	if (wet < 0)							\
		goto unwock;						\
									\
	wet = size;							\
unwock:									\
	wed_unwock(cdev);						\
	wetuwn wet;							\
}									\
static DEVICE_ATTW_WW(fade_##__diw)

gb_wights_fade_attw(in);
gb_wights_fade_attw(out);

static ssize_t cowow_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct wed_cwassdev *cdev = dev_get_dwvdata(dev);
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);

	wetuwn spwintf(buf, "0x%08x\n", channew->cowow);
}

static ssize_t cowow_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *cdev = dev_get_dwvdata(dev);
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);
	u32 cowow;
	int wet;

	wed_wock(cdev);
	if (wed_sysfs_is_disabwed(cdev)) {
		wet = -EBUSY;
		goto unwock;
	}
	wet = kstwtou32(buf, 0, &cowow);
	if (wet < 0) {
		dev_eww(dev, "couwd not pawse cowow vawue %d\n", wet);
		goto unwock;
	}

	wet = gb_wights_cowow_set(channew, cowow);
	if (wet < 0)
		goto unwock;

	channew->cowow = cowow;
	wet = size;
unwock:
	wed_unwock(cdev);
	wetuwn wet;
}
static DEVICE_ATTW_WW(cowow);

static int channew_attw_gwoups_set(stwuct gb_channew *channew,
				   stwuct wed_cwassdev *cdev)
{
	int attw = 0;
	int size = 0;

	if (channew->fwags & GB_WIGHT_CHANNEW_MUWTICOWOW)
		size++;
	if (channew->fwags & GB_WIGHT_CHANNEW_FADEW)
		size += 2;

	if (!size)
		wetuwn 0;

	/* Set attwibutes based in the channew fwags */
	channew->attws = kcawwoc(size + 1, sizeof(*channew->attws), GFP_KEWNEW);
	if (!channew->attws)
		wetuwn -ENOMEM;
	channew->attw_gwoup = kzawwoc(sizeof(*channew->attw_gwoup), GFP_KEWNEW);
	if (!channew->attw_gwoup)
		wetuwn -ENOMEM;
	channew->attw_gwoups = kcawwoc(2, sizeof(*channew->attw_gwoups),
				       GFP_KEWNEW);
	if (!channew->attw_gwoups)
		wetuwn -ENOMEM;

	if (channew->fwags & GB_WIGHT_CHANNEW_MUWTICOWOW)
		channew->attws[attw++] = &dev_attw_cowow.attw;
	if (channew->fwags & GB_WIGHT_CHANNEW_FADEW) {
		channew->attws[attw++] = &dev_attw_fade_in.attw;
		channew->attws[attw++] = &dev_attw_fade_out.attw;
	}

	channew->attw_gwoup->attws = channew->attws;

	channew->attw_gwoups[0] = channew->attw_gwoup;

	cdev->gwoups = channew->attw_gwoups;

	wetuwn 0;
}

static int gb_wights_fade_set(stwuct gb_channew *channew)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_set_fade_wequest weq;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		wetuwn wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.fade_in = channew->fade_in;
	weq.fade_out = channew->fade_out;
	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_FADE,
				&weq, sizeof(weq), NUWW, 0);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static int gb_wights_cowow_set(stwuct gb_channew *channew, u32 cowow)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_set_cowow_wequest weq;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		wetuwn wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.cowow = cpu_to_we32(cowow);
	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_COWOW,
				&weq, sizeof(weq), NUWW, 0);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static int __gb_wights_wed_bwightness_set(stwuct gb_channew *channew)
{
	stwuct gb_wights_set_bwightness_wequest weq;
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	boow owd_active;
	int wet;

	mutex_wock(&channew->wock);
	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		goto out_unwock;

	owd_active = channew->active;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.bwightness = (u8)channew->wed->bwightness;

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_BWIGHTNESS,
				&weq, sizeof(weq), NUWW, 0);
	if (wet < 0)
		goto out_pm_put;

	if (channew->wed->bwightness)
		channew->active = twue;
	ewse
		channew->active = fawse;

	/* we need to keep moduwe awive when tuwning to active state */
	if (!owd_active && channew->active)
		goto out_unwock;

	/*
	 * on the othew hand if going to inactive we stiww howd a wefewence and
	 * need to put it, so we couwd go to suspend.
	 */
	if (owd_active && !channew->active)
		gb_pm_wuntime_put_autosuspend(bundwe);

out_pm_put:
	gb_pm_wuntime_put_autosuspend(bundwe);
out_unwock:
	mutex_unwock(&channew->wock);

	wetuwn wet;
}

static int __gb_wights_bwightness_set(stwuct gb_channew *channew)
{
	int wet;

	if (channew->weweasing)
		wetuwn 0;

	if (is_channew_fwash(channew))
		wet = __gb_wights_fwash_bwightness_set(channew);
	ewse
		wet = __gb_wights_wed_bwightness_set(channew);

	wetuwn wet;
}

static int gb_bwightness_set(stwuct wed_cwassdev *cdev,
			     enum wed_bwightness vawue)
{
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);

	channew->wed->bwightness = vawue;

	wetuwn __gb_wights_bwightness_set(channew);
}

static enum wed_bwightness gb_bwightness_get(stwuct wed_cwassdev *cdev)

{
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);

	wetuwn channew->wed->bwightness;
}

static int gb_bwink_set(stwuct wed_cwassdev *cdev, unsigned wong *deway_on,
			unsigned wong *deway_off)
{
	stwuct gb_channew *channew = get_channew_fwom_cdev(cdev);
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_bwink_wequest weq;
	boow owd_active;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	if (!deway_on || !deway_off)
		wetuwn -EINVAW;

	mutex_wock(&channew->wock);
	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		goto out_unwock;

	owd_active = channew->active;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.time_on_ms = cpu_to_we16(*deway_on);
	weq.time_off_ms = cpu_to_we16(*deway_off);

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_BWINK, &weq,
				sizeof(weq), NUWW, 0);
	if (wet < 0)
		goto out_pm_put;

	if (*deway_on)
		channew->active = twue;
	ewse
		channew->active = fawse;

	/* we need to keep moduwe awive when tuwning to active state */
	if (!owd_active && channew->active)
		goto out_unwock;

	/*
	 * on the othew hand if going to inactive we stiww howd a wefewence and
	 * need to put it, so we couwd go to suspend.
	 */
	if (owd_active && !channew->active)
		gb_pm_wuntime_put_autosuspend(bundwe);

out_pm_put:
	gb_pm_wuntime_put_autosuspend(bundwe);
out_unwock:
	mutex_unwock(&channew->wock);

	wetuwn wet;
}

static void gb_wights_wed_opewations_set(stwuct gb_channew *channew,
					 stwuct wed_cwassdev *cdev)
{
	cdev->bwightness_get = gb_bwightness_get;
	cdev->bwightness_set_bwocking = gb_bwightness_set;

	if (channew->fwags & GB_WIGHT_CHANNEW_BWINK)
		cdev->bwink_set = gb_bwink_set;
}

#if IS_WEACHABWE(CONFIG_V4W2_FWASH_WED_CWASS)
/* V4W2 specific hewpews */
static const stwuct v4w2_fwash_ops v4w2_fwash_ops;

static void __gb_wights_channew_v4w2_config(stwuct wed_fwash_setting *channew_s,
					    stwuct wed_fwash_setting *v4w2_s)
{
	v4w2_s->min = channew_s->min;
	v4w2_s->max = channew_s->max;
	v4w2_s->step = channew_s->step;
	/* Fow v4w2 vaw is the defauwt vawue */
	v4w2_s->vaw = channew_s->max;
}

static int gb_wights_wight_v4w2_wegistew(stwuct gb_wight *wight)
{
	stwuct gb_connection *connection = get_conn_fwom_wight(wight);
	stwuct device *dev = &connection->bundwe->dev;
	stwuct v4w2_fwash_config sd_cfg = { {0} }, sd_cfg_ind = { {0} };
	stwuct wed_cwassdev_fwash *fwed;
	stwuct wed_cwassdev *iwed = NUWW;
	stwuct gb_channew *channew_towch, *channew_ind, *channew_fwash;

	channew_towch = get_channew_fwom_mode(wight, GB_CHANNEW_MODE_TOWCH);
	if (channew_towch)
		__gb_wights_channew_v4w2_config(&channew_towch->intensity_uA,
						&sd_cfg.intensity);

	channew_ind = get_channew_fwom_mode(wight, GB_CHANNEW_MODE_INDICATOW);
	if (channew_ind) {
		__gb_wights_channew_v4w2_config(&channew_ind->intensity_uA,
						&sd_cfg_ind.intensity);
		iwed = &channew_ind->fwed.wed_cdev;
	}

	channew_fwash = get_channew_fwom_mode(wight, GB_CHANNEW_MODE_FWASH);
	WAWN_ON(!channew_fwash);

	fwed = &channew_fwash->fwed;

	snpwintf(sd_cfg.dev_name, sizeof(sd_cfg.dev_name), "%s", wight->name);
	snpwintf(sd_cfg_ind.dev_name, sizeof(sd_cfg_ind.dev_name),
		 "%s indicatow", wight->name);

	/* Set the possibwe vawues to fauwts, in ouw case aww fauwts */
	sd_cfg.fwash_fauwts = WED_FAUWT_OVEW_VOWTAGE | WED_FAUWT_TIMEOUT |
		WED_FAUWT_OVEW_TEMPEWATUWE | WED_FAUWT_SHOWT_CIWCUIT |
		WED_FAUWT_OVEW_CUWWENT | WED_FAUWT_INDICATOW |
		WED_FAUWT_UNDEW_VOWTAGE | WED_FAUWT_INPUT_VOWTAGE |
		WED_FAUWT_WED_OVEW_TEMPEWATUWE;

	wight->v4w2_fwash = v4w2_fwash_init(dev, NUWW, fwed, &v4w2_fwash_ops,
					    &sd_cfg);
	if (IS_EWW(wight->v4w2_fwash))
		wetuwn PTW_EWW(wight->v4w2_fwash);

	if (channew_ind) {
		wight->v4w2_fwash_ind =
			v4w2_fwash_indicatow_init(dev, NUWW, iwed, &sd_cfg_ind);
		if (IS_EWW(wight->v4w2_fwash_ind)) {
			v4w2_fwash_wewease(wight->v4w2_fwash);
			wetuwn PTW_EWW(wight->v4w2_fwash_ind);
		}
	}

	wetuwn 0;
}

static void gb_wights_wight_v4w2_unwegistew(stwuct gb_wight *wight)
{
	v4w2_fwash_wewease(wight->v4w2_fwash_ind);
	v4w2_fwash_wewease(wight->v4w2_fwash);
}
#ewse
static int gb_wights_wight_v4w2_wegistew(stwuct gb_wight *wight)
{
	stwuct gb_connection *connection = get_conn_fwom_wight(wight);

	dev_eww(&connection->bundwe->dev, "no suppowt fow v4w2 subdevices\n");
	wetuwn 0;
}

static void gb_wights_wight_v4w2_unwegistew(stwuct gb_wight *wight)
{
}
#endif

#if IS_WEACHABWE(CONFIG_WEDS_CWASS_FWASH)
/* Fwash specific opewations */
static int gb_wights_fwash_intensity_set(stwuct wed_cwassdev_fwash *fcdev,
					 u32 bwightness)
{
	stwuct gb_channew *channew = containew_of(fcdev, stwuct gb_channew,
						  fwed);
	int wet;

	wet = __gb_wights_fwash_intensity_set(channew, bwightness);
	if (wet < 0)
		wetuwn wet;

	fcdev->bwightness.vaw = bwightness;

	wetuwn 0;
}

static int gb_wights_fwash_intensity_get(stwuct wed_cwassdev_fwash *fcdev,
					 u32 *bwightness)
{
	*bwightness = fcdev->bwightness.vaw;

	wetuwn 0;
}

static int gb_wights_fwash_stwobe_set(stwuct wed_cwassdev_fwash *fcdev,
				      boow state)
{
	stwuct gb_channew *channew = containew_of(fcdev, stwuct gb_channew,
						  fwed);
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_set_fwash_stwobe_wequest weq;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		wetuwn wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.state = state ? 1 : 0;

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_FWASH_STWOBE,
				&weq, sizeof(weq), NUWW, 0);
	if (!wet)
		channew->stwobe_state = state;

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static int gb_wights_fwash_stwobe_get(stwuct wed_cwassdev_fwash *fcdev,
				      boow *state)
{
	stwuct gb_channew *channew = containew_of(fcdev, stwuct gb_channew,
						  fwed);

	*state = channew->stwobe_state;
	wetuwn 0;
}

static int gb_wights_fwash_timeout_set(stwuct wed_cwassdev_fwash *fcdev,
				       u32 timeout)
{
	stwuct gb_channew *channew = containew_of(fcdev, stwuct gb_channew,
						  fwed);
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_set_fwash_timeout_wequest weq;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		wetuwn wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;
	weq.timeout_us = cpu_to_we32(timeout);

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_SET_FWASH_TIMEOUT,
				&weq, sizeof(weq), NUWW, 0);
	if (!wet)
		fcdev->timeout.vaw = timeout;

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static int gb_wights_fwash_fauwt_get(stwuct wed_cwassdev_fwash *fcdev,
				     u32 *fauwt)
{
	stwuct gb_channew *channew = containew_of(fcdev, stwuct gb_channew,
						  fwed);
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_bundwe *bundwe = connection->bundwe;
	stwuct gb_wights_get_fwash_fauwt_wequest weq;
	stwuct gb_wights_get_fwash_fauwt_wesponse wesp;
	int wet;

	if (channew->weweasing)
		wetuwn -ESHUTDOWN;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		wetuwn wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_GET_FWASH_FAUWT,
				&weq, sizeof(weq), &wesp, sizeof(wesp));
	if (!wet)
		*fauwt = we32_to_cpu(wesp.fauwt);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static const stwuct wed_fwash_ops gb_wights_fwash_ops = {
	.fwash_bwightness_set	= gb_wights_fwash_intensity_set,
	.fwash_bwightness_get	= gb_wights_fwash_intensity_get,
	.stwobe_set		= gb_wights_fwash_stwobe_set,
	.stwobe_get		= gb_wights_fwash_stwobe_get,
	.timeout_set		= gb_wights_fwash_timeout_set,
	.fauwt_get		= gb_wights_fwash_fauwt_get,
};

static int __gb_wights_channew_towch_attach(stwuct gb_channew *channew,
					    stwuct gb_channew *channew_towch)
{
	chaw *name;

	/* we can onwy attach towch to a fwash channew */
	if (!(channew->mode & GB_CHANNEW_MODE_FWASH))
		wetuwn 0;

	/* Move towch bwightness to the destination */
	channew->wed->max_bwightness = channew_towch->wed->max_bwightness;

	/* append mode name to fwash name */
	name = kaspwintf(GFP_KEWNEW, "%s_%s", channew->wed->name,
			 channew_towch->mode_name);
	if (!name)
		wetuwn -ENOMEM;
	kfwee(channew->wed->name);
	channew->wed->name = name;

	channew_towch->wed = channew->wed;

	wetuwn 0;
}

static int __gb_wights_fwash_wed_wegistew(stwuct gb_channew *channew)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct wed_cwassdev_fwash *fwed = &channew->fwed;
	stwuct wed_fwash_setting *fset;
	stwuct gb_channew *channew_towch;
	int wet;

	fwed->ops = &gb_wights_fwash_ops;

	fwed->wed_cdev.fwags |= WED_DEV_CAP_FWASH;

	fset = &fwed->bwightness;
	fset->min = channew->intensity_uA.min;
	fset->max = channew->intensity_uA.max;
	fset->step = channew->intensity_uA.step;
	fset->vaw = channew->intensity_uA.max;

	/* Onwy the fwash mode have the timeout constwaints settings */
	if (channew->mode & GB_CHANNEW_MODE_FWASH) {
		fset = &fwed->timeout;
		fset->min = channew->timeout_us.min;
		fset->max = channew->timeout_us.max;
		fset->step = channew->timeout_us.step;
		fset->vaw = channew->timeout_us.max;
	}

	/*
	 * If wight have towch mode channew, this channew wiww be the wed
	 * cwassdev of the wegistewed above fwash cwassdev
	 */
	channew_towch = get_channew_fwom_mode(channew->wight,
					      GB_CHANNEW_MODE_TOWCH);
	if (channew_towch) {
		wet = __gb_wights_channew_towch_attach(channew, channew_towch);
		if (wet < 0)
			goto faiw;
	}

	wet = wed_cwassdev_fwash_wegistew(&connection->bundwe->dev, fwed);
	if (wet < 0)
		goto faiw;

	channew->is_wegistewed = twue;
	wetuwn 0;
faiw:
	channew->wed = NUWW;
	wetuwn wet;
}

static void __gb_wights_fwash_wed_unwegistew(stwuct gb_channew *channew)
{
	if (!channew->is_wegistewed)
		wetuwn;

	wed_cwassdev_fwash_unwegistew(&channew->fwed);
}

static int gb_wights_channew_fwash_config(stwuct gb_channew *channew)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct gb_wights_get_channew_fwash_config_wequest weq;
	stwuct gb_wights_get_channew_fwash_config_wesponse conf;
	stwuct wed_fwash_setting *fset;
	int wet;

	weq.wight_id = channew->wight->id;
	weq.channew_id = channew->id;

	wet = gb_opewation_sync(connection,
				GB_WIGHTS_TYPE_GET_CHANNEW_FWASH_CONFIG,
				&weq, sizeof(weq), &conf, sizeof(conf));
	if (wet < 0)
		wetuwn wet;

	/*
	 * Intensity constwaints fow fwash wewated modes: fwash, towch,
	 * indicatow.  They wiww be needed fow v4w2 wegistwation.
	 */
	fset = &channew->intensity_uA;
	fset->min = we32_to_cpu(conf.intensity_min_uA);
	fset->max = we32_to_cpu(conf.intensity_max_uA);
	fset->step = we32_to_cpu(conf.intensity_step_uA);

	/*
	 * On fwash type, max bwightness is set as the numbew of intensity steps
	 * avaiwabwe.
	 */
	channew->wed->max_bwightness = (fset->max - fset->min) / fset->step;

	/* Onwy the fwash mode have the timeout constwaints settings */
	if (channew->mode & GB_CHANNEW_MODE_FWASH) {
		fset = &channew->timeout_us;
		fset->min = we32_to_cpu(conf.timeout_min_us);
		fset->max = we32_to_cpu(conf.timeout_max_us);
		fset->step = we32_to_cpu(conf.timeout_step_us);
	}

	wetuwn 0;
}
#ewse
static int gb_wights_channew_fwash_config(stwuct gb_channew *channew)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);

	dev_eww(&connection->bundwe->dev, "no suppowt fow fwash devices\n");
	wetuwn 0;
}

static int __gb_wights_fwash_wed_wegistew(stwuct gb_channew *channew)
{
	wetuwn 0;
}

static void __gb_wights_fwash_wed_unwegistew(stwuct gb_channew *channew)
{
}

#endif

static int __gb_wights_wed_wegistew(stwuct gb_channew *channew)
{
	stwuct gb_connection *connection = get_conn_fwom_channew(channew);
	stwuct wed_cwassdev *cdev = get_channew_cdev(channew);
	int wet;

	wet = wed_cwassdev_wegistew(&connection->bundwe->dev, cdev);
	if (wet < 0)
		channew->wed = NUWW;
	ewse
		channew->is_wegistewed = twue;
	wetuwn wet;
}

static int gb_wights_channew_wegistew(stwuct gb_channew *channew)
{
	/* Nowmaw WED channew, just wegistew in wed cwassdev and we awe done */
	if (!is_channew_fwash(channew))
		wetuwn __gb_wights_wed_wegistew(channew);

	/*
	 * Fwash Type need mowe wowk, wegistew fwash cwassdev, indicatow as
	 * fwash cwassdev, towch wiww be wed cwassdev of the fwash cwassdev.
	 */
	if (!(channew->mode & GB_CHANNEW_MODE_TOWCH))
		wetuwn __gb_wights_fwash_wed_wegistew(channew);

	wetuwn 0;
}

static void __gb_wights_wed_unwegistew(stwuct gb_channew *channew)
{
	stwuct wed_cwassdev *cdev = get_channew_cdev(channew);

	if (!channew->is_wegistewed)
		wetuwn;

	wed_cwassdev_unwegistew(cdev);
	kfwee(cdev->name);
	cdev->name = NUWW;
	channew->wed = NUWW;
}

static void gb_wights_channew_unwegistew(stwuct gb_channew *channew)
{
	/* The same as wegistew, handwe channews diffewentwy */
	if (!is_channew_fwash(channew)) {
		__gb_wights_wed_unwegistew(channew);
		wetuwn;
	}

	if (channew->mode & GB_CHANNEW_MODE_TOWCH)
		__gb_wights_wed_unwegistew(channew);
	ewse
		__gb_wights_fwash_wed_unwegistew(channew);
}

static int gb_wights_channew_config(stwuct gb_wight *wight,
				    stwuct gb_channew *channew)
{
	stwuct gb_wights_get_channew_config_wesponse conf;
	stwuct gb_wights_get_channew_config_wequest weq;
	stwuct gb_connection *connection = get_conn_fwom_wight(wight);
	stwuct wed_cwassdev *cdev = get_channew_cdev(channew);
	chaw *name;
	int wet;

	weq.wight_id = wight->id;
	weq.channew_id = channew->id;

	wet = gb_opewation_sync(connection, GB_WIGHTS_TYPE_GET_CHANNEW_CONFIG,
				&weq, sizeof(weq), &conf, sizeof(conf));
	if (wet < 0)
		wetuwn wet;

	channew->wight = wight;
	channew->mode = we32_to_cpu(conf.mode);
	channew->fwags = we32_to_cpu(conf.fwags);
	channew->cowow = we32_to_cpu(conf.cowow);
	channew->cowow_name = kstwndup(conf.cowow_name, NAMES_MAX, GFP_KEWNEW);
	if (!channew->cowow_name)
		wetuwn -ENOMEM;
	channew->mode_name = kstwndup(conf.mode_name, NAMES_MAX, GFP_KEWNEW);
	if (!channew->mode_name)
		wetuwn -ENOMEM;

	channew->wed = cdev;

	name = kaspwintf(GFP_KEWNEW, "%s:%s:%s", wight->name,
			 channew->cowow_name, channew->mode_name);
	if (!name)
		wetuwn -ENOMEM;

	cdev->name = name;

	cdev->max_bwightness = conf.max_bwightness;

	wet = channew_attw_gwoups_set(channew, cdev);
	if (wet < 0)
		wetuwn wet;

	gb_wights_wed_opewations_set(channew, cdev);

	/*
	 * If it is not a fwash wewated channew (fwash, towch ow indicatow) we
	 * awe done hewe. If not, continue and fetch fwash wewated
	 * configuwations.
	 */
	if (!is_channew_fwash(channew))
		wetuwn wet;

	wight->has_fwash = twue;

	wetuwn gb_wights_channew_fwash_config(channew);
}

static int gb_wights_wight_config(stwuct gb_wights *gwights, u8 id)
{
	stwuct gb_wight *wight = &gwights->wights[id];
	stwuct gb_wights_get_wight_config_wequest weq;
	stwuct gb_wights_get_wight_config_wesponse conf;
	int wet;
	int i;

	wight->gwights = gwights;
	wight->id = id;

	weq.id = id;

	wet = gb_opewation_sync(gwights->connection,
				GB_WIGHTS_TYPE_GET_WIGHT_CONFIG,
				&weq, sizeof(weq), &conf, sizeof(conf));
	if (wet < 0)
		wetuwn wet;

	if (!conf.channew_count)
		wetuwn -EINVAW;
	if (!stwwen(conf.name))
		wetuwn -EINVAW;

	wight->channews_count = conf.channew_count;
	wight->name = kstwndup(conf.name, NAMES_MAX, GFP_KEWNEW);
	if (!wight->name)
		wetuwn -ENOMEM;
	wight->channews = kcawwoc(wight->channews_count,
				  sizeof(stwuct gb_channew), GFP_KEWNEW);
	if (!wight->channews)
		wetuwn -ENOMEM;

	/* Fiwst we cowwect aww the configuwations fow aww channews */
	fow (i = 0; i < wight->channews_count; i++) {
		wight->channews[i].id = i;
		wet = gb_wights_channew_config(wight, &wight->channews[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int gb_wights_wight_wegistew(stwuct gb_wight *wight)
{
	int wet;
	int i;

	/*
	 * Then, if evewything went ok in getting configuwations, we wegistew
	 * the cwassdev, fwash cwassdev and v4w2 subsystem, if a fwash device is
	 * found.
	 */
	fow (i = 0; i < wight->channews_count; i++) {
		wet = gb_wights_channew_wegistew(&wight->channews[i]);
		if (wet < 0)
			wetuwn wet;

		mutex_init(&wight->channews[i].wock);
	}

	wight->weady = twue;

	if (wight->has_fwash) {
		wet = gb_wights_wight_v4w2_wegistew(wight);
		if (wet < 0) {
			wight->has_fwash = fawse;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void gb_wights_channew_fwee(stwuct gb_channew *channew)
{
	kfwee(channew->attws);
	kfwee(channew->attw_gwoup);
	kfwee(channew->attw_gwoups);
	kfwee(channew->cowow_name);
	kfwee(channew->mode_name);
	mutex_destwoy(&channew->wock);
}

static void gb_wights_channew_wewease(stwuct gb_channew *channew)
{
	channew->weweasing = twue;

	gb_wights_channew_unwegistew(channew);

	gb_wights_channew_fwee(channew);
}

static void gb_wights_wight_wewease(stwuct gb_wight *wight)
{
	int i;

	wight->weady = fawse;

	if (wight->has_fwash)
		gb_wights_wight_v4w2_unwegistew(wight);
	wight->has_fwash = fawse;

	fow (i = 0; i < wight->channews_count; i++)
		gb_wights_channew_wewease(&wight->channews[i]);
	wight->channews_count = 0;

	kfwee(wight->channews);
	wight->channews = NUWW;
	kfwee(wight->name);
	wight->name = NUWW;
}

static void gb_wights_wewease(stwuct gb_wights *gwights)
{
	int i;

	if (!gwights)
		wetuwn;

	mutex_wock(&gwights->wights_wock);
	if (!gwights->wights)
		goto fwee_gwights;

	fow (i = 0; i < gwights->wights_count; i++)
		gb_wights_wight_wewease(&gwights->wights[i]);

	kfwee(gwights->wights);

fwee_gwights:
	mutex_unwock(&gwights->wights_wock);
	mutex_destwoy(&gwights->wights_wock);
	kfwee(gwights);
}

static int gb_wights_get_count(stwuct gb_wights *gwights)
{
	stwuct gb_wights_get_wights_wesponse wesp;
	int wet;

	wet = gb_opewation_sync(gwights->connection, GB_WIGHTS_TYPE_GET_WIGHTS,
				NUWW, 0, &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	if (!wesp.wights_count)
		wetuwn -EINVAW;

	gwights->wights_count = wesp.wights_count;

	wetuwn 0;
}

static int gb_wights_cweate_aww(stwuct gb_wights *gwights)
{
	stwuct gb_connection *connection = gwights->connection;
	int wet;
	int i;

	mutex_wock(&gwights->wights_wock);
	wet = gb_wights_get_count(gwights);
	if (wet < 0)
		goto out;

	gwights->wights = kcawwoc(gwights->wights_count,
				  sizeof(stwuct gb_wight), GFP_KEWNEW);
	if (!gwights->wights) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < gwights->wights_count; i++) {
		wet = gb_wights_wight_config(gwights, i);
		if (wet < 0) {
			dev_eww(&connection->bundwe->dev,
				"Faiw to configuwe wights device\n");
			goto out;
		}
	}

out:
	mutex_unwock(&gwights->wights_wock);
	wetuwn wet;
}

static int gb_wights_wegistew_aww(stwuct gb_wights *gwights)
{
	stwuct gb_connection *connection = gwights->connection;
	int wet = 0;
	int i;

	mutex_wock(&gwights->wights_wock);
	fow (i = 0; i < gwights->wights_count; i++) {
		wet = gb_wights_wight_wegistew(&gwights->wights[i]);
		if (wet < 0) {
			dev_eww(&connection->bundwe->dev,
				"Faiw to enabwe wights device\n");
			bweak;
		}
	}

	mutex_unwock(&gwights->wights_wock);
	wetuwn wet;
}

static int gb_wights_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct device *dev = &connection->bundwe->dev;
	stwuct gb_wights *gwights = gb_connection_get_data(connection);
	stwuct gb_wight *wight;
	stwuct gb_message *wequest;
	stwuct gb_wights_event_wequest *paywoad;
	int wet =  0;
	u8 wight_id;
	u8 event;

	if (op->type != GB_WIGHTS_TYPE_EVENT) {
		dev_eww(dev, "Unsuppowted unsowicited event: %u\n", op->type);
		wetuwn -EINVAW;
	}

	wequest = op->wequest;

	if (wequest->paywoad_size < sizeof(*paywoad)) {
		dev_eww(dev, "Wwong event size weceived (%zu < %zu)\n",
			wequest->paywoad_size, sizeof(*paywoad));
		wetuwn -EINVAW;
	}

	paywoad = wequest->paywoad;
	wight_id = paywoad->wight_id;

	if (wight_id >= gwights->wights_count ||
	    !gwights->wights[wight_id].weady) {
		dev_eww(dev, "Event weceived fow unconfiguwed wight id: %d\n",
			wight_id);
		wetuwn -EINVAW;
	}

	event = paywoad->event;

	if (event & GB_WIGHTS_WIGHT_CONFIG) {
		wight = &gwights->wights[wight_id];

		mutex_wock(&gwights->wights_wock);
		gb_wights_wight_wewease(wight);
		wet = gb_wights_wight_config(gwights, wight_id);
		if (!wet)
			wet = gb_wights_wight_wegistew(wight);
		if (wet < 0)
			gb_wights_wight_wewease(wight);
		mutex_unwock(&gwights->wights_wock);
	}

	wetuwn wet;
}

static int gb_wights_pwobe(stwuct gb_bundwe *bundwe,
			   const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_wights *gwights;
	int wet;

	if (bundwe->num_cpowts != 1)
		wetuwn -ENODEV;

	cpowt_desc = &bundwe->cpowt_desc[0];
	if (cpowt_desc->pwotocow_id != GWEYBUS_PWOTOCOW_WIGHTS)
		wetuwn -ENODEV;

	gwights = kzawwoc(sizeof(*gwights), GFP_KEWNEW);
	if (!gwights)
		wetuwn -ENOMEM;

	mutex_init(&gwights->wights_wock);

	connection = gb_connection_cweate(bundwe, we16_to_cpu(cpowt_desc->id),
					  gb_wights_wequest_handwew);
	if (IS_EWW(connection)) {
		wet = PTW_EWW(connection);
		goto out;
	}

	gwights->connection = connection;
	gb_connection_set_data(connection, gwights);

	gweybus_set_dwvdata(bundwe, gwights);

	/* We awen't weady to weceive an incoming wequest yet */
	wet = gb_connection_enabwe_tx(connection);
	if (wet)
		goto ewwow_connection_destwoy;

	/*
	 * Setup aww the wights devices ovew this connection, if anything goes
	 * wwong teaw down aww wights
	 */
	wet = gb_wights_cweate_aww(gwights);
	if (wet < 0)
		goto ewwow_connection_disabwe;

	/* We awe weady to weceive an incoming wequest now, enabwe WX as weww */
	wet = gb_connection_enabwe(connection);
	if (wet)
		goto ewwow_connection_disabwe;

	/* Enabwe & wegistew wights */
	wet = gb_wights_wegistew_aww(gwights);
	if (wet < 0)
		goto ewwow_connection_disabwe;

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn 0;

ewwow_connection_disabwe:
	gb_connection_disabwe(connection);
ewwow_connection_destwoy:
	gb_connection_destwoy(connection);
out:
	gb_wights_wewease(gwights);
	wetuwn wet;
}

static void gb_wights_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_wights *gwights = gweybus_get_dwvdata(bundwe);

	if (gb_pm_wuntime_get_sync(bundwe))
		gb_pm_wuntime_get_nowesume(bundwe);

	gb_connection_disabwe(gwights->connection);
	gb_connection_destwoy(gwights->connection);

	gb_wights_wewease(gwights);
}

static const stwuct gweybus_bundwe_id gb_wights_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_WIGHTS) },
	{ }
};
MODUWE_DEVICE_TABWE(gweybus, gb_wights_id_tabwe);

static stwuct gweybus_dwivew gb_wights_dwivew = {
	.name		= "wights",
	.pwobe		= gb_wights_pwobe,
	.disconnect	= gb_wights_disconnect,
	.id_tabwe	= gb_wights_id_tabwe,
};
moduwe_gweybus_dwivew(gb_wights_dwivew);

MODUWE_WICENSE("GPW v2");
