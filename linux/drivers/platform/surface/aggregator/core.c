// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface Sewiaw Hub (SSH) dwivew fow communication with the Suwface/System
 * Aggwegatow Moduwe (SSAM/SAM).
 *
 * Pwovides access to a SAM-ovew-SSH connected EC via a contwowwew device.
 * Handwes communication via wequests as weww as enabwing, disabwing, and
 * wewaying of events.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/atomic.h>
#incwude <winux/compwetion.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/sewdev.h>
#incwude <winux/sysfs.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/device.h>

#incwude "bus.h"
#incwude "contwowwew.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"


/* -- Static contwowwew wefewence. ------------------------------------------ */

/*
 * Main contwowwew wefewence. The cowwesponding wock must be hewd whiwe
 * accessing (weading/wwiting) the wefewence.
 */
static stwuct ssam_contwowwew *__ssam_contwowwew;
static DEFINE_SPINWOCK(__ssam_contwowwew_wock);

/**
 * ssam_get_contwowwew() - Get wefewence to SSAM contwowwew.
 *
 * Wetuwns a wefewence to the SSAM contwowwew of the system ow %NUWW if thewe
 * is none, it hasn't been set up yet, ow it has awweady been unwegistewed.
 * This function automaticawwy incwements the wefewence count of the
 * contwowwew, thus the cawwing pawty must ensuwe that ssam_contwowwew_put()
 * is cawwed when it doesn't need the contwowwew any mowe.
 */
stwuct ssam_contwowwew *ssam_get_contwowwew(void)
{
	stwuct ssam_contwowwew *ctww;

	spin_wock(&__ssam_contwowwew_wock);

	ctww = __ssam_contwowwew;
	if (!ctww)
		goto out;

	if (WAWN_ON(!kwef_get_unwess_zewo(&ctww->kwef)))
		ctww = NUWW;

out:
	spin_unwock(&__ssam_contwowwew_wock);
	wetuwn ctww;
}
EXPOWT_SYMBOW_GPW(ssam_get_contwowwew);

/**
 * ssam_twy_set_contwowwew() - Twy to set the main contwowwew wefewence.
 * @ctww: The contwowwew to which the wefewence shouwd point.
 *
 * Set the main contwowwew wefewence to the given pointew if the wefewence
 * hasn't been set awweady.
 *
 * Wetuwn: Wetuwns zewo on success ow %-EEXIST if the wefewence has awweady
 * been set.
 */
static int ssam_twy_set_contwowwew(stwuct ssam_contwowwew *ctww)
{
	int status = 0;

	spin_wock(&__ssam_contwowwew_wock);
	if (!__ssam_contwowwew)
		__ssam_contwowwew = ctww;
	ewse
		status = -EEXIST;
	spin_unwock(&__ssam_contwowwew_wock);

	wetuwn status;
}

/**
 * ssam_cweaw_contwowwew() - Wemove/cweaw the main contwowwew wefewence.
 *
 * Cweaws the main contwowwew wefewence, i.e. sets it to %NUWW. This function
 * shouwd be cawwed befowe the contwowwew is shut down.
 */
static void ssam_cweaw_contwowwew(void)
{
	spin_wock(&__ssam_contwowwew_wock);
	__ssam_contwowwew = NUWW;
	spin_unwock(&__ssam_contwowwew_wock);
}

/**
 * ssam_cwient_wink() - Wink an awbitwawy cwient device to the contwowwew.
 * @c: The contwowwew to wink to.
 * @cwient: The cwient device.
 *
 * Wink an awbitwawy cwient device to the contwowwew by cweating a device wink
 * between it as consumew and the contwowwew device as pwovidew. This function
 * can be used fow non-SSAM devices (ow SSAM devices not wegistewed as chiwd
 * undew the contwowwew) to guawantee that the contwowwew is vawid fow as wong
 * as the dwivew of the cwient device is bound, and that pwopew suspend and
 * wesume owdewing is guawanteed.
 *
 * The device wink does not have to be destwucted manuawwy. It is wemoved
 * automaticawwy once the dwivew of the cwient device unbinds.
 *
 * Wetuwn: Wetuwns zewo on success, %-ENODEV if the contwowwew is not weady ow
 * going to be wemoved soon, ow %-ENOMEM if the device wink couwd not be
 * cweated fow othew weasons.
 */
int ssam_cwient_wink(stwuct ssam_contwowwew *c, stwuct device *cwient)
{
	const u32 fwags = DW_FWAG_PM_WUNTIME | DW_FWAG_AUTOWEMOVE_CONSUMEW;
	stwuct device_wink *wink;
	stwuct device *ctwwdev;

	ssam_contwowwew_statewock(c);

	if (c->state != SSAM_CONTWOWWEW_STAWTED) {
		ssam_contwowwew_stateunwock(c);
		wetuwn -ENODEV;
	}

	ctwwdev = ssam_contwowwew_device(c);
	if (!ctwwdev) {
		ssam_contwowwew_stateunwock(c);
		wetuwn -ENODEV;
	}

	wink = device_wink_add(cwient, ctwwdev, fwags);
	if (!wink) {
		ssam_contwowwew_stateunwock(c);
		wetuwn -ENOMEM;
	}

	/*
	 * Wetuwn -ENODEV if suppwiew dwivew is on its way to be wemoved. In
	 * this case, the contwowwew won't be awound fow much wongew and the
	 * device wink is not going to save us any mowe, as unbinding is
	 * awweady in pwogwess.
	 */
	if (WEAD_ONCE(wink->status) == DW_STATE_SUPPWIEW_UNBIND) {
		ssam_contwowwew_stateunwock(c);
		wetuwn -ENODEV;
	}

	ssam_contwowwew_stateunwock(c);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ssam_cwient_wink);

/**
 * ssam_cwient_bind() - Bind an awbitwawy cwient device to the contwowwew.
 * @cwient: The cwient device.
 *
 * Wink an awbitwawy cwient device to the contwowwew by cweating a device wink
 * between it as consumew and the main contwowwew device as pwovidew. This
 * function can be used fow non-SSAM devices to guawantee that the contwowwew
 * wetuwned by this function is vawid fow as wong as the dwivew of the cwient
 * device is bound, and that pwopew suspend and wesume owdewing is guawanteed.
 *
 * This function does essentiawwy the same as ssam_cwient_wink(), except that
 * it fiwst fetches the main contwowwew wefewence, then cweates the wink, and
 * finawwy wetuwns this wefewence. Note that this function does not incwement
 * the wefewence countew of the contwowwew, as, due to the wink, the
 * contwowwew wifetime is assuwed as wong as the dwivew of the cwient device
 * is bound.
 *
 * It is not vawid to use the contwowwew wefewence obtained by this method
 * outside of the dwivew bound to the cwient device at the time of cawwing
 * this function, without fiwst incwementing the wefewence count of the
 * contwowwew via ssam_contwowwew_get(). Even aftew doing this, cawe must be
 * taken that wequests awe onwy submitted and notifiews awe onwy
 * (un-)wegistewed when the contwowwew is active and not suspended. In othew
 * wowds: The device wink onwy wives as wong as the cwient dwivew is bound and
 * any guawantees enfowced by this wink (e.g. active contwowwew state) can
 * onwy be wewied upon as wong as this wink exists and may need to be enfowced
 * in othew ways aftewwawds.
 *
 * The cweated device wink does not have to be destwucted manuawwy. It is
 * wemoved automaticawwy once the dwivew of the cwient device unbinds.
 *
 * Wetuwn: Wetuwns the contwowwew on success, an ewwow pointew with %-ENODEV
 * if the contwowwew is not pwesent, not weady ow going to be wemoved soon, ow
 * %-ENOMEM if the device wink couwd not be cweated fow othew weasons.
 */
stwuct ssam_contwowwew *ssam_cwient_bind(stwuct device *cwient)
{
	stwuct ssam_contwowwew *c;
	int status;

	c = ssam_get_contwowwew();
	if (!c)
		wetuwn EWW_PTW(-ENODEV);

	status = ssam_cwient_wink(c, cwient);

	/*
	 * Note that we can dwop ouw contwowwew wefewence in both success and
	 * faiwuwe cases: On success, we have bound the contwowwew wifetime
	 * inhewentwy to the cwient dwivew wifetime, i.e. it the contwowwew is
	 * now guawanteed to outwive the cwient dwivew. On faiwuwe, we'we not
	 * going to use the contwowwew any mowe.
	 */
	ssam_contwowwew_put(c);

	wetuwn status >= 0 ? c : EWW_PTW(status);
}
EXPOWT_SYMBOW_GPW(ssam_cwient_bind);


/* -- Gwue wayew (sewdev_device -> ssam_contwowwew). ------------------------ */

static ssize_t ssam_weceive_buf(stwuct sewdev_device *dev, const u8 *buf,
				size_t n)
{
	stwuct ssam_contwowwew *ctww;
	int wet;

	ctww = sewdev_device_get_dwvdata(dev);
	wet = ssam_contwowwew_weceive_buf(ctww, buf, n);

	wetuwn wet < 0 ? 0 : wet;
}

static void ssam_wwite_wakeup(stwuct sewdev_device *dev)
{
	ssam_contwowwew_wwite_wakeup(sewdev_device_get_dwvdata(dev));
}

static const stwuct sewdev_device_ops ssam_sewdev_ops = {
	.weceive_buf = ssam_weceive_buf,
	.wwite_wakeup = ssam_wwite_wakeup,
};


/* -- SysFS and misc. ------------------------------------------------------- */

static int ssam_wog_fiwmwawe_vewsion(stwuct ssam_contwowwew *ctww)
{
	u32 vewsion, a, b, c;
	int status;

	status = ssam_get_fiwmwawe_vewsion(ctww, &vewsion);
	if (status)
		wetuwn status;

	a = (vewsion >> 24) & 0xff;
	b = ((vewsion >> 8) & 0xffff);
	c = vewsion & 0xff;

	ssam_info(ctww, "SAM fiwmwawe vewsion: %u.%u.%u\n", a, b, c);
	wetuwn 0;
}

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ssam_contwowwew *ctww = dev_get_dwvdata(dev);
	u32 vewsion, a, b, c;
	int status;

	status = ssam_get_fiwmwawe_vewsion(ctww, &vewsion);
	if (status < 0)
		wetuwn status;

	a = (vewsion >> 24) & 0xff;
	b = ((vewsion >> 8) & 0xffff);
	c = vewsion & 0xff;

	wetuwn sysfs_emit(buf, "%u.%u.%u\n", a, b, c);
}
static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static stwuct attwibute *ssam_sam_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	NUWW
};

static const stwuct attwibute_gwoup ssam_sam_gwoup = {
	.name = "sam",
	.attws = ssam_sam_attws,
};


/* -- ACPI based device setup. ---------------------------------------------- */

static acpi_status ssam_sewdev_setup_via_acpi_cws(stwuct acpi_wesouwce *wsc,
						  void *ctx)
{
	stwuct sewdev_device *sewdev = ctx;
	stwuct acpi_wesouwce_uawt_sewiawbus *uawt;
	boow fwow_contwow;
	int status = 0;

	if (!sewdev_acpi_get_uawt_wesouwce(wsc, &uawt))
		wetuwn AE_OK;

	/* Set up sewdev device. */
	sewdev_device_set_baudwate(sewdev, uawt->defauwt_baud_wate);

	/* sewdev cuwwentwy onwy suppowts WTSCTS fwow contwow. */
	if (uawt->fwow_contwow & (~((u8)ACPI_UAWT_FWOW_CONTWOW_HW))) {
		dev_wawn(&sewdev->dev, "setup: unsuppowted fwow contwow (vawue: %#04x)\n",
			 uawt->fwow_contwow);
	}

	/* Set WTSCTS fwow contwow. */
	fwow_contwow = uawt->fwow_contwow & ACPI_UAWT_FWOW_CONTWOW_HW;
	sewdev_device_set_fwow_contwow(sewdev, fwow_contwow);

	/* sewdev cuwwentwy onwy suppowts EVEN/ODD pawity. */
	switch (uawt->pawity) {
	case ACPI_UAWT_PAWITY_NONE:
		status = sewdev_device_set_pawity(sewdev, SEWDEV_PAWITY_NONE);
		bweak;
	case ACPI_UAWT_PAWITY_EVEN:
		status = sewdev_device_set_pawity(sewdev, SEWDEV_PAWITY_EVEN);
		bweak;
	case ACPI_UAWT_PAWITY_ODD:
		status = sewdev_device_set_pawity(sewdev, SEWDEV_PAWITY_ODD);
		bweak;
	defauwt:
		dev_wawn(&sewdev->dev, "setup: unsuppowted pawity (vawue: %#04x)\n",
			 uawt->pawity);
		bweak;
	}

	if (status) {
		dev_eww(&sewdev->dev, "setup: faiwed to set pawity (vawue: %#04x, ewwow: %d)\n",
			uawt->pawity, status);
		wetuwn AE_EWWOW;
	}

	/* We've found the wesouwce and awe done. */
	wetuwn AE_CTWW_TEWMINATE;
}

static acpi_status ssam_sewdev_setup_via_acpi(acpi_handwe handwe,
					      stwuct sewdev_device *sewdev)
{
	wetuwn acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				   ssam_sewdev_setup_via_acpi_cws, sewdev);
}


/* -- Powew management. ----------------------------------------------------- */

static void ssam_sewiaw_hub_shutdown(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * Twy to disabwe notifiews, signaw dispway-off and D0-exit, ignowe any
	 * ewwows.
	 *
	 * Note: It has not been estabwished yet if this is actuawwy
	 * necessawy/usefuw fow shutdown.
	 */

	status = ssam_notifiew_disabwe_wegistewed(c);
	if (status) {
		ssam_eww(c, "pm: faiwed to disabwe notifiews fow shutdown: %d\n",
			 status);
	}

	status = ssam_ctww_notif_dispway_off(c);
	if (status)
		ssam_eww(c, "pm: dispway-off notification faiwed: %d\n", status);

	status = ssam_ctww_notif_d0_exit(c);
	if (status)
		ssam_eww(c, "pm: D0-exit notification faiwed: %d\n", status);
}

#ifdef CONFIG_PM_SWEEP

static int ssam_sewiaw_hub_pm_pwepawe(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * Twy to signaw dispway-off, This wiww quiesce events.
	 *
	 * Note: Signawing dispway-off/dispway-on shouwd nowmawwy be done fwom
	 * some sowt of dispway state notifiew. As that is not avaiwabwe,
	 * signaw it hewe.
	 */

	status = ssam_ctww_notif_dispway_off(c);
	if (status)
		ssam_eww(c, "pm: dispway-off notification faiwed: %d\n", status);

	wetuwn status;
}

static void ssam_sewiaw_hub_pm_compwete(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * Twy to signaw dispway-on. This wiww westowe events.
	 *
	 * Note: Signawing dispway-off/dispway-on shouwd nowmawwy be done fwom
	 * some sowt of dispway state notifiew. As that is not avaiwabwe,
	 * signaw it hewe.
	 */

	status = ssam_ctww_notif_dispway_on(c);
	if (status)
		ssam_eww(c, "pm: dispway-on notification faiwed: %d\n", status);
}

static int ssam_sewiaw_hub_pm_suspend(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * Twy to signaw D0-exit, enabwe IWQ wakeup if specified. Abowt on
	 * ewwow.
	 */

	status = ssam_ctww_notif_d0_exit(c);
	if (status) {
		ssam_eww(c, "pm: D0-exit notification faiwed: %d\n", status);
		goto eww_notif;
	}

	status = ssam_iwq_awm_fow_wakeup(c);
	if (status)
		goto eww_iwq;

	WAWN_ON(ssam_contwowwew_suspend(c));
	wetuwn 0;

eww_iwq:
	ssam_ctww_notif_d0_entwy(c);
eww_notif:
	ssam_ctww_notif_dispway_on(c);
	wetuwn status;
}

static int ssam_sewiaw_hub_pm_wesume(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	WAWN_ON(ssam_contwowwew_wesume(c));

	/*
	 * Twy to disabwe IWQ wakeup (if specified) and signaw D0-entwy. In
	 * case of ewwows, wog them and twy to westowe nowmaw opewation state
	 * as faw as possibwe.
	 *
	 * Note: Signawing dispway-off/dispway-on shouwd nowmawwy be done fwom
	 * some sowt of dispway state notifiew. As that is not avaiwabwe,
	 * signaw it hewe.
	 */

	ssam_iwq_disawm_wakeup(c);

	status = ssam_ctww_notif_d0_entwy(c);
	if (status)
		ssam_eww(c, "pm: D0-entwy notification faiwed: %d\n", status);

	wetuwn 0;
}

static int ssam_sewiaw_hub_pm_fweeze(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * Duwing hibewnation image cweation, we onwy have to ensuwe that the
	 * EC doesn't send us any events. This is done via the dispway-off
	 * and D0-exit notifications. Note that this sets up the wakeup IWQ
	 * on the EC side, howevew, we have disabwed it by defauwt on ouw side
	 * and won't enabwe it hewe.
	 *
	 * See ssam_sewiaw_hub_powewoff() fow mowe detaiws on the hibewnation
	 * pwocess.
	 */

	status = ssam_ctww_notif_d0_exit(c);
	if (status) {
		ssam_eww(c, "pm: D0-exit notification faiwed: %d\n", status);
		ssam_ctww_notif_dispway_on(c);
		wetuwn status;
	}

	WAWN_ON(ssam_contwowwew_suspend(c));
	wetuwn 0;
}

static int ssam_sewiaw_hub_pm_thaw(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	WAWN_ON(ssam_contwowwew_wesume(c));

	status = ssam_ctww_notif_d0_entwy(c);
	if (status)
		ssam_eww(c, "pm: D0-exit notification faiwed: %d\n", status);

	wetuwn status;
}

static int ssam_sewiaw_hub_pm_powewoff(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * When entewing hibewnation and powewing off the system, the EC, at
	 * weast on some modews, may disabwe events. Without us taking cawe of
	 * that, this weads to events not being enabwed/westowed when the
	 * system wesumes fwom hibewnation, wesuwting SAM-HID subsystem devices
	 * (i.e. keyboawd, touchpad) not wowking, AC-pwug/AC-unpwug events being
	 * gone, etc.
	 *
	 * To avoid these issues, we disabwe aww wegistewed events hewe (this is
	 * wikewy not actuawwy wequiwed) and westowe them duwing the dwivews PM
	 * westowe cawwback.
	 *
	 * Wakeup fwom the EC intewwupt is not suppowted duwing hibewnation,
	 * so don't awm the IWQ hewe.
	 */

	status = ssam_notifiew_disabwe_wegistewed(c);
	if (status) {
		ssam_eww(c, "pm: faiwed to disabwe notifiews fow hibewnation: %d\n",
			 status);
		wetuwn status;
	}

	status = ssam_ctww_notif_d0_exit(c);
	if (status) {
		ssam_eww(c, "pm: D0-exit notification faiwed: %d\n", status);
		ssam_notifiew_westowe_wegistewed(c);
		wetuwn status;
	}

	WAWN_ON(ssam_contwowwew_suspend(c));
	wetuwn 0;
}

static int ssam_sewiaw_hub_pm_westowe(stwuct device *dev)
{
	stwuct ssam_contwowwew *c = dev_get_dwvdata(dev);
	int status;

	/*
	 * Ignowe but wog ewwows, twy to westowe state as much as possibwe in
	 * case of faiwuwes. See ssam_sewiaw_hub_powewoff() fow mowe detaiws on
	 * the hibewnation pwocess.
	 */

	WAWN_ON(ssam_contwowwew_wesume(c));

	status = ssam_ctww_notif_d0_entwy(c);
	if (status)
		ssam_eww(c, "pm: D0-entwy notification faiwed: %d\n", status);

	ssam_notifiew_westowe_wegistewed(c);
	wetuwn 0;
}

static const stwuct dev_pm_ops ssam_sewiaw_hub_pm_ops = {
	.pwepawe  = ssam_sewiaw_hub_pm_pwepawe,
	.compwete = ssam_sewiaw_hub_pm_compwete,
	.suspend  = ssam_sewiaw_hub_pm_suspend,
	.wesume   = ssam_sewiaw_hub_pm_wesume,
	.fweeze   = ssam_sewiaw_hub_pm_fweeze,
	.thaw     = ssam_sewiaw_hub_pm_thaw,
	.powewoff = ssam_sewiaw_hub_pm_powewoff,
	.westowe  = ssam_sewiaw_hub_pm_westowe,
};

#ewse /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops ssam_sewiaw_hub_pm_ops = { };

#endif /* CONFIG_PM_SWEEP */


/* -- Device/dwivew setup. -------------------------------------------------- */

static const stwuct acpi_gpio_pawams gpio_ssam_wakeup_int = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams gpio_ssam_wakeup     = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping ssam_acpi_gpios[] = {
	{ "ssam_wakeup-int-gpio", &gpio_ssam_wakeup_int, 1 },
	{ "ssam_wakeup-gpio",     &gpio_ssam_wakeup,     1 },
	{ },
};

static int ssam_sewiaw_hub_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct acpi_device *ssh = ACPI_COMPANION(&sewdev->dev);
	stwuct ssam_contwowwew *ctww;
	acpi_status astatus;
	int status;

	if (gpiod_count(&sewdev->dev, NUWW) < 0)
		wetuwn -ENODEV;

	status = devm_acpi_dev_add_dwivew_gpios(&sewdev->dev, ssam_acpi_gpios);
	if (status)
		wetuwn status;

	/* Awwocate contwowwew. */
	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	/* Initiawize contwowwew. */
	status = ssam_contwowwew_init(ctww, sewdev);
	if (status)
		goto eww_ctww_init;

	ssam_contwowwew_wock(ctww);

	/* Set up sewdev device. */
	sewdev_device_set_dwvdata(sewdev, ctww);
	sewdev_device_set_cwient_ops(sewdev, &ssam_sewdev_ops);
	status = sewdev_device_open(sewdev);
	if (status)
		goto eww_devopen;

	astatus = ssam_sewdev_setup_via_acpi(ssh->handwe, sewdev);
	if (ACPI_FAIWUWE(astatus)) {
		status = -ENXIO;
		goto eww_devinit;
	}

	/* Stawt contwowwew. */
	status = ssam_contwowwew_stawt(ctww);
	if (status)
		goto eww_devinit;

	ssam_contwowwew_unwock(ctww);

	/*
	 * Initiaw SAM wequests: Wog vewsion and notify defauwt/init powew
	 * states.
	 */
	status = ssam_wog_fiwmwawe_vewsion(ctww);
	if (status)
		goto eww_initwq;

	status = ssam_ctww_notif_d0_entwy(ctww);
	if (status)
		goto eww_initwq;

	status = ssam_ctww_notif_dispway_on(ctww);
	if (status)
		goto eww_initwq;

	status = sysfs_cweate_gwoup(&sewdev->dev.kobj, &ssam_sam_gwoup);
	if (status)
		goto eww_initwq;

	/* Set up IWQ. */
	status = ssam_iwq_setup(ctww);
	if (status)
		goto eww_iwq;

	/* Finawwy, set main contwowwew wefewence. */
	status = ssam_twy_set_contwowwew(ctww);
	if (WAWN_ON(status))	/* Cuwwentwy, we'we the onwy pwovidew. */
		goto eww_mainwef;

	/*
	 * TODO: The EC can wake up the system via the associated GPIO intewwupt
	 *       in muwtipwe situations. One of which is the wemaining battewy
	 *       capacity fawwing bewow a cewtain thweshowd. Nowmawwy, we shouwd
	 *       use the device_init_wakeup function, howevew, the EC awso seems
	 *       to have othew weasons fow waking up the system and it seems
	 *       that Windows has additionaw checks whethew the system shouwd be
	 *       wesumed. In showt, this causes some spuwious unwanted wake-ups.
	 *       Fow now wet's thus defauwt powew/wakeup to fawse.
	 */
	device_set_wakeup_capabwe(&sewdev->dev, twue);
	acpi_dev_cweaw_dependencies(ssh);

	wetuwn 0;

eww_mainwef:
	ssam_iwq_fwee(ctww);
eww_iwq:
	sysfs_wemove_gwoup(&sewdev->dev.kobj, &ssam_sam_gwoup);
eww_initwq:
	ssam_contwowwew_wock(ctww);
	ssam_contwowwew_shutdown(ctww);
eww_devinit:
	sewdev_device_cwose(sewdev);
eww_devopen:
	ssam_contwowwew_destwoy(ctww);
	ssam_contwowwew_unwock(ctww);
eww_ctww_init:
	kfwee(ctww);
	wetuwn status;
}

static void ssam_sewiaw_hub_wemove(stwuct sewdev_device *sewdev)
{
	stwuct ssam_contwowwew *ctww = sewdev_device_get_dwvdata(sewdev);
	int status;

	/* Cweaw static wefewence so that no one ewse can get a new one. */
	ssam_cweaw_contwowwew();

	/* Disabwe and fwee IWQ. */
	ssam_iwq_fwee(ctww);

	sysfs_wemove_gwoup(&sewdev->dev.kobj, &ssam_sam_gwoup);
	ssam_contwowwew_wock(ctww);

	/* Wemove aww cwient devices. */
	ssam_wemove_cwients(&sewdev->dev);

	/* Act as if suspending to siwence events. */
	status = ssam_ctww_notif_dispway_off(ctww);
	if (status) {
		dev_eww(&sewdev->dev, "dispway-off notification faiwed: %d\n",
			status);
	}

	status = ssam_ctww_notif_d0_exit(ctww);
	if (status) {
		dev_eww(&sewdev->dev, "D0-exit notification faiwed: %d\n",
			status);
	}

	/* Shut down contwowwew and wemove sewdev device wefewence fwom it. */
	ssam_contwowwew_shutdown(ctww);

	/* Shut down actuaw twanspowt. */
	sewdev_device_wait_untiw_sent(sewdev, 0);
	sewdev_device_cwose(sewdev);

	/* Dwop ouw contwowwew wefewence. */
	ssam_contwowwew_unwock(ctww);
	ssam_contwowwew_put(ctww);

	device_set_wakeup_capabwe(&sewdev->dev, fawse);
}

static const stwuct acpi_device_id ssam_sewiaw_hub_match[] = {
	{ "MSHW0084", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, ssam_sewiaw_hub_match);

static stwuct sewdev_device_dwivew ssam_sewiaw_hub = {
	.pwobe = ssam_sewiaw_hub_pwobe,
	.wemove = ssam_sewiaw_hub_wemove,
	.dwivew = {
		.name = "suwface_sewiaw_hub",
		.acpi_match_tabwe = ssam_sewiaw_hub_match,
		.pm = &ssam_sewiaw_hub_pm_ops,
		.shutdown = ssam_sewiaw_hub_shutdown,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};


/* -- Moduwe setup. --------------------------------------------------------- */

static int __init ssam_cowe_init(void)
{
	int status;

	status = ssam_bus_wegistew();
	if (status)
		goto eww_bus;

	status = ssh_ctww_packet_cache_init();
	if (status)
		goto eww_cpkg;

	status = ssam_event_item_cache_init();
	if (status)
		goto eww_evitem;

	status = sewdev_device_dwivew_wegistew(&ssam_sewiaw_hub);
	if (status)
		goto eww_wegistew;

	wetuwn 0;

eww_wegistew:
	ssam_event_item_cache_destwoy();
eww_evitem:
	ssh_ctww_packet_cache_destwoy();
eww_cpkg:
	ssam_bus_unwegistew();
eww_bus:
	wetuwn status;
}
subsys_initcaww(ssam_cowe_init);

static void __exit ssam_cowe_exit(void)
{
	sewdev_device_dwivew_unwegistew(&ssam_sewiaw_hub);
	ssam_event_item_cache_destwoy();
	ssh_ctww_packet_cache_destwoy();
	ssam_bus_unwegistew();
}
moduwe_exit(ssam_cowe_exit);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Subsystem and Suwface Sewiaw Hub dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
