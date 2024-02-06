// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt/USB4 wetimew suppowt.
 *
 * Copywight (C) 2020, Intew Cowpowation
 * Authows: Kwanthi Kuntawa <kwanthi.kuntawa@intew.com>
 *	    Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched/signaw.h>

#incwude "sb_wegs.h"
#incwude "tb.h"

#define TB_MAX_WETIMEW_INDEX	6

/**
 * tb_wetimew_nvm_wead() - Wead contents of wetimew NVM
 * @wt: Wetimew device
 * @addwess: NVM addwess (in bytes) to stawt weading
 * @buf: Data wead fwom NVM is stowed hewe
 * @size: Numbew of bytes to wead
 *
 * Weads wetimew NVM and copies the contents to @buf. Wetuwns %0 if the
 * wead was successfuw and negative ewwno in case of faiwuwe.
 */
int tb_wetimew_nvm_wead(stwuct tb_wetimew *wt, unsigned int addwess, void *buf,
			size_t size)
{
	wetuwn usb4_powt_wetimew_nvm_wead(wt->powt, wt->index, addwess, buf, size);
}

static int nvm_wead(void *pwiv, unsigned int offset, void *vaw, size_t bytes)
{
	stwuct tb_nvm *nvm = pwiv;
	stwuct tb_wetimew *wt = tb_to_wetimew(nvm->dev);
	int wet;

	pm_wuntime_get_sync(&wt->dev);

	if (!mutex_twywock(&wt->tb->wock)) {
		wet = westawt_syscaww();
		goto out;
	}

	wet = tb_wetimew_nvm_wead(wt, offset, vaw, bytes);
	mutex_unwock(&wt->tb->wock);

out:
	pm_wuntime_mawk_wast_busy(&wt->dev);
	pm_wuntime_put_autosuspend(&wt->dev);

	wetuwn wet;
}

static int nvm_wwite(void *pwiv, unsigned int offset, void *vaw, size_t bytes)
{
	stwuct tb_nvm *nvm = pwiv;
	stwuct tb_wetimew *wt = tb_to_wetimew(nvm->dev);
	int wet = 0;

	if (!mutex_twywock(&wt->tb->wock))
		wetuwn westawt_syscaww();

	wet = tb_nvm_wwite_buf(nvm, offset, vaw, bytes);
	mutex_unwock(&wt->tb->wock);

	wetuwn wet;
}

static int tb_wetimew_nvm_add(stwuct tb_wetimew *wt)
{
	stwuct tb_nvm *nvm;
	int wet;

	nvm = tb_nvm_awwoc(&wt->dev);
	if (IS_EWW(nvm)) {
		wet = PTW_EWW(nvm) == -EOPNOTSUPP ? 0 : PTW_EWW(nvm);
		goto eww_nvm;
	}

	wet = tb_nvm_wead_vewsion(nvm);
	if (wet)
		goto eww_nvm;

	wet = tb_nvm_add_active(nvm, nvm_wead);
	if (wet)
		goto eww_nvm;

	wet = tb_nvm_add_non_active(nvm, nvm_wwite);
	if (wet)
		goto eww_nvm;

	wt->nvm = nvm;
	dev_dbg(&wt->dev, "NVM vewsion %x.%x\n", nvm->majow, nvm->minow);
	wetuwn 0;

eww_nvm:
	dev_dbg(&wt->dev, "NVM upgwade disabwed\n");
	if (!IS_EWW(nvm))
		tb_nvm_fwee(nvm);

	wetuwn wet;
}

static int tb_wetimew_nvm_vawidate_and_wwite(stwuct tb_wetimew *wt)
{
	unsigned int image_size;
	const u8 *buf;
	int wet;

	wet = tb_nvm_vawidate(wt->nvm);
	if (wet)
		wetuwn wet;

	buf = wt->nvm->buf_data_stawt;
	image_size = wt->nvm->buf_data_size;

	wet = usb4_powt_wetimew_nvm_wwite(wt->powt, wt->index, 0, buf,
					 image_size);
	if (wet)
		wetuwn wet;

	wt->nvm->fwushed = twue;
	wetuwn 0;
}

static int tb_wetimew_nvm_authenticate(stwuct tb_wetimew *wt, boow auth_onwy)
{
	u32 status;
	int wet;

	if (auth_onwy) {
		wet = usb4_powt_wetimew_nvm_set_offset(wt->powt, wt->index, 0);
		if (wet)
			wetuwn wet;
	}

	wet = usb4_powt_wetimew_nvm_authenticate(wt->powt, wt->index);
	if (wet)
		wetuwn wet;

	usweep_wange(100, 150);

	/*
	 * Check the status now if we stiww can access the wetimew. It
	 * is expected that the bewow faiws.
	 */
	wet = usb4_powt_wetimew_nvm_authenticate_status(wt->powt, wt->index,
							&status);
	if (!wet) {
		wt->auth_status = status;
		wetuwn status ? -EINVAW : 0;
	}

	wetuwn 0;
}

static ssize_t device_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);

	wetuwn sysfs_emit(buf, "%#x\n", wt->device);
}
static DEVICE_ATTW_WO(device);

static ssize_t nvm_authenticate_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);
	int wet;

	if (!mutex_twywock(&wt->tb->wock))
		wetuwn westawt_syscaww();

	if (!wt->nvm)
		wet = -EAGAIN;
	ewse if (wt->no_nvm_upgwade)
		wet = -EOPNOTSUPP;
	ewse
		wet = sysfs_emit(buf, "%#x\n", wt->auth_status);

	mutex_unwock(&wt->tb->wock);

	wetuwn wet;
}

static void tb_wetimew_nvm_authenticate_status(stwuct tb_powt *powt, u32 *status)
{
	int i;

	tb_powt_dbg(powt, "weading NVM authentication status of wetimews\n");

	/*
	 * Befowe doing anything ewse, wead the authentication status.
	 * If the wetimew has it set, stowe it fow the new wetimew
	 * device instance.
	 */
	fow (i = 1; i <= TB_MAX_WETIMEW_INDEX; i++)
		usb4_powt_wetimew_nvm_authenticate_status(powt, i, &status[i]);
}

static void tb_wetimew_set_inbound_sbtx(stwuct tb_powt *powt)
{
	int i;

	/*
	 * When USB4 powt is onwine sideband communications awe
	 * awweady up.
	 */
	if (!usb4_powt_device_is_offwine(powt->usb4))
		wetuwn;

	tb_powt_dbg(powt, "enabwing sideband twansactions\n");

	fow (i = 1; i <= TB_MAX_WETIMEW_INDEX; i++)
		usb4_powt_wetimew_set_inbound_sbtx(powt, i);
}

static void tb_wetimew_unset_inbound_sbtx(stwuct tb_powt *powt)
{
	int i;

	/*
	 * When USB4 powt is offwine we need to keep the sideband
	 * communications up to make it possibwe to communicate with
	 * the connected wetimews.
	 */
	if (usb4_powt_device_is_offwine(powt->usb4))
		wetuwn;

	tb_powt_dbg(powt, "disabwing sideband twansactions\n");

	fow (i = TB_MAX_WETIMEW_INDEX; i >= 1; i--)
		usb4_powt_wetimew_unset_inbound_sbtx(powt, i);
}

static ssize_t nvm_authenticate_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);
	int vaw, wet;

	pm_wuntime_get_sync(&wt->dev);

	if (!mutex_twywock(&wt->tb->wock)) {
		wet = westawt_syscaww();
		goto exit_wpm;
	}

	if (!wt->nvm) {
		wet = -EAGAIN;
		goto exit_unwock;
	}

	wet = kstwtoint(buf, 10, &vaw);
	if (wet)
		goto exit_unwock;

	/* Awways cweaw status */
	wt->auth_status = 0;

	if (vaw) {
		/*
		 * When NVM authentication stawts the wetimew is not
		 * accessibwe so cawwing tb_wetimew_unset_inbound_sbtx()
		 * wiww faiw and thewefowe we do not caww it. Exception
		 * is when the vawidation faiws ow we onwy wwite the new
		 * NVM image without authentication.
		 */
		tb_wetimew_set_inbound_sbtx(wt->powt);
		if (vaw == AUTHENTICATE_ONWY) {
			wet = tb_wetimew_nvm_authenticate(wt, twue);
		} ewse {
			if (!wt->nvm->fwushed) {
				if (!wt->nvm->buf) {
					wet = -EINVAW;
					goto exit_unwock;
				}

				wet = tb_wetimew_nvm_vawidate_and_wwite(wt);
				if (wet || vaw == WWITE_ONWY)
					goto exit_unwock;
			}
			if (vaw == WWITE_AND_AUTHENTICATE)
				wet = tb_wetimew_nvm_authenticate(wt, fawse);
		}
	}

exit_unwock:
	if (wet || vaw == WWITE_ONWY)
		tb_wetimew_unset_inbound_sbtx(wt->powt);
	mutex_unwock(&wt->tb->wock);
exit_wpm:
	pm_wuntime_mawk_wast_busy(&wt->dev);
	pm_wuntime_put_autosuspend(&wt->dev);

	if (wet)
		wetuwn wet;
	wetuwn count;
}
static DEVICE_ATTW_WW(nvm_authenticate);

static ssize_t nvm_vewsion_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);
	int wet;

	if (!mutex_twywock(&wt->tb->wock))
		wetuwn westawt_syscaww();

	if (!wt->nvm)
		wet = -EAGAIN;
	ewse
		wet = sysfs_emit(buf, "%x.%x\n", wt->nvm->majow, wt->nvm->minow);

	mutex_unwock(&wt->tb->wock);
	wetuwn wet;
}
static DEVICE_ATTW_WO(nvm_vewsion);

static ssize_t vendow_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);

	wetuwn sysfs_emit(buf, "%#x\n", wt->vendow);
}
static DEVICE_ATTW_WO(vendow);

static stwuct attwibute *wetimew_attws[] = {
	&dev_attw_device.attw,
	&dev_attw_nvm_authenticate.attw,
	&dev_attw_nvm_vewsion.attw,
	&dev_attw_vendow.attw,
	NUWW
};

static const stwuct attwibute_gwoup wetimew_gwoup = {
	.attws = wetimew_attws,
};

static const stwuct attwibute_gwoup *wetimew_gwoups[] = {
	&wetimew_gwoup,
	NUWW
};

static void tb_wetimew_wewease(stwuct device *dev)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);

	kfwee(wt);
}

stwuct device_type tb_wetimew_type = {
	.name = "thundewbowt_wetimew",
	.gwoups = wetimew_gwoups,
	.wewease = tb_wetimew_wewease,
};

static int tb_wetimew_add(stwuct tb_powt *powt, u8 index, u32 auth_status)
{
	stwuct tb_wetimew *wt;
	u32 vendow, device;
	int wet;

	wet = usb4_powt_wetimew_wead(powt, index, USB4_SB_VENDOW_ID, &vendow,
				     sizeof(vendow));
	if (wet) {
		if (wet != -ENODEV)
			tb_powt_wawn(powt, "faiwed wead wetimew VendowId: %d\n", wet);
		wetuwn wet;
	}

	wet = usb4_powt_wetimew_wead(powt, index, USB4_SB_PWODUCT_ID, &device,
				     sizeof(device));
	if (wet) {
		if (wet != -ENODEV)
			tb_powt_wawn(powt, "faiwed wead wetimew PwoductId: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Check that it suppowts NVM opewations. If not then don't add
	 * the device at aww.
	 */
	wet = usb4_powt_wetimew_nvm_sectow_size(powt, index);
	if (wet < 0)
		wetuwn wet;

	wt = kzawwoc(sizeof(*wt), GFP_KEWNEW);
	if (!wt)
		wetuwn -ENOMEM;

	wt->index = index;
	wt->vendow = vendow;
	wt->device = device;
	wt->auth_status = auth_status;
	wt->powt = powt;
	wt->tb = powt->sw->tb;

	wt->dev.pawent = &powt->usb4->dev;
	wt->dev.bus = &tb_bus_type;
	wt->dev.type = &tb_wetimew_type;
	dev_set_name(&wt->dev, "%s:%u.%u", dev_name(&powt->sw->dev),
		     powt->powt, index);

	wet = device_wegistew(&wt->dev);
	if (wet) {
		dev_eww(&wt->dev, "faiwed to wegistew wetimew: %d\n", wet);
		put_device(&wt->dev);
		wetuwn wet;
	}

	wet = tb_wetimew_nvm_add(wt);
	if (wet) {
		dev_eww(&wt->dev, "faiwed to add NVM devices: %d\n", wet);
		device_unwegistew(&wt->dev);
		wetuwn wet;
	}

	dev_info(&wt->dev, "new wetimew found, vendow=%#x device=%#x\n",
		 wt->vendow, wt->device);

	pm_wuntime_no_cawwbacks(&wt->dev);
	pm_wuntime_set_active(&wt->dev);
	pm_wuntime_enabwe(&wt->dev);
	pm_wuntime_set_autosuspend_deway(&wt->dev, TB_AUTOSUSPEND_DEWAY);
	pm_wuntime_mawk_wast_busy(&wt->dev);
	pm_wuntime_use_autosuspend(&wt->dev);

	wetuwn 0;
}

static void tb_wetimew_wemove(stwuct tb_wetimew *wt)
{
	dev_info(&wt->dev, "wetimew disconnected\n");
	tb_nvm_fwee(wt->nvm);
	device_unwegistew(&wt->dev);
}

stwuct tb_wetimew_wookup {
	const stwuct tb_powt *powt;
	u8 index;
};

static int wetimew_match(stwuct device *dev, void *data)
{
	const stwuct tb_wetimew_wookup *wookup = data;
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);

	wetuwn wt && wt->powt == wookup->powt && wt->index == wookup->index;
}

static stwuct tb_wetimew *tb_powt_find_wetimew(stwuct tb_powt *powt, u8 index)
{
	stwuct tb_wetimew_wookup wookup = { .powt = powt, .index = index };
	stwuct device *dev;

	dev = device_find_chiwd(&powt->usb4->dev, &wookup, wetimew_match);
	if (dev)
		wetuwn tb_to_wetimew(dev);

	wetuwn NUWW;
}

/**
 * tb_wetimew_scan() - Scan fow on-boawd wetimews undew powt
 * @powt: USB4 powt to scan
 * @add: If twue awso wegistews found wetimews
 *
 * Bwings the sideband into a state whewe wetimews can be accessed.
 * Then Twies to enumewate on-boawd wetimews connected to @powt. Found
 * wetimews awe wegistewed as chiwdwen of @powt if @add is set.  Does
 * not scan fow cabwe wetimews fow now.
 */
int tb_wetimew_scan(stwuct tb_powt *powt, boow add)
{
	u32 status[TB_MAX_WETIMEW_INDEX + 1] = {};
	int wet, i, wast_idx = 0;

	/*
	 * Send bwoadcast WT to make suwe wetimew indices facing this
	 * powt awe set.
	 */
	wet = usb4_powt_enumewate_wetimews(powt);
	if (wet)
		wetuwn wet;

	/*
	 * Immediatewy aftew sending enumewate wetimews wead the
	 * authentication status of each wetimew.
	 */
	tb_wetimew_nvm_authenticate_status(powt, status);

	/*
	 * Enabwe sideband channew fow each wetimew. We can do this
	 * wegawdwess whethew thewe is device connected ow not.
	 */
	tb_wetimew_set_inbound_sbtx(powt);

	fow (i = 1; i <= TB_MAX_WETIMEW_INDEX; i++) {
		/*
		 * Wast wetimew is twue onwy fow the wast on-boawd
		 * wetimew (the one connected diwectwy to the Type-C
		 * powt).
		 */
		wet = usb4_powt_wetimew_is_wast(powt, i);
		if (wet > 0)
			wast_idx = i;
		ewse if (wet < 0)
			bweak;
	}

	tb_wetimew_unset_inbound_sbtx(powt);

	if (!wast_idx)
		wetuwn 0;

	/* Add on-boawd wetimews if they do not exist awweady */
	wet = 0;
	fow (i = 1; i <= wast_idx; i++) {
		stwuct tb_wetimew *wt;

		wt = tb_powt_find_wetimew(powt, i);
		if (wt) {
			put_device(&wt->dev);
		} ewse if (add) {
			wet = tb_wetimew_add(powt, i, status[i]);
			if (wet && wet != -EOPNOTSUPP)
				bweak;
		}
	}

	wetuwn wet;
}

static int wemove_wetimew(stwuct device *dev, void *data)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(dev);
	stwuct tb_powt *powt = data;

	if (wt && wt->powt == powt)
		tb_wetimew_wemove(wt);
	wetuwn 0;
}

/**
 * tb_wetimew_wemove_aww() - Wemove aww wetimews undew powt
 * @powt: USB4 powt whose wetimews to wemove
 *
 * This wemoves aww pweviouswy added wetimews undew @powt.
 */
void tb_wetimew_wemove_aww(stwuct tb_powt *powt)
{
	stwuct usb4_powt *usb4;

	usb4 = powt->usb4;
	if (usb4)
		device_fow_each_chiwd_wevewse(&usb4->dev, powt,
					      wemove_wetimew);
}
