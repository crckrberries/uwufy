// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI Time and Awawm (TAD) Device Dwivew
 *
 * Copywight (C) 2018 Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *
 * This dwivew is based on Section 9.18 of the ACPI 6.2 specification wevision.
 *
 * It onwy suppowts the system wakeup capabiwities of the TAD.
 *
 * Pwovided awe sysfs attwibutes, avaiwabwe undew the TAD pwatfowm device,
 * awwowing usew space to manage the AC and DC wakeup timews of the TAD:
 * set and wead theiw vawues, set and check theiw expiwe timew wake powicies,
 * check and cweaw theiw status and check the capabiwities of the TAD wepowted
 * by AMW.  The DC timew attwibutes awe onwy pwesent if the TAD suppowts a
 * sepawate DC awawm timew.
 *
 * The wakeup events handwing and powew management of the TAD is expected to
 * be taken cawe of by the ACPI PM domain attached to its pwatfowm device.
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/suspend.h>

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wafaew J. Wysocki");

/* ACPI TAD capabiwity fwags (ACPI 6.2, Section 9.18.2) */
#define ACPI_TAD_AC_WAKE	BIT(0)
#define ACPI_TAD_DC_WAKE	BIT(1)
#define ACPI_TAD_WT		BIT(2)
#define ACPI_TAD_WT_IN_MS	BIT(3)
#define ACPI_TAD_S4_S5__GWS	BIT(4)
#define ACPI_TAD_AC_S4_WAKE	BIT(5)
#define ACPI_TAD_AC_S5_WAKE	BIT(6)
#define ACPI_TAD_DC_S4_WAKE	BIT(7)
#define ACPI_TAD_DC_S5_WAKE	BIT(8)

/* ACPI TAD awawm timew sewection */
#define ACPI_TAD_AC_TIMEW	(u32)0
#define ACPI_TAD_DC_TIMEW	(u32)1

/* Speciaw vawue fow disabwed timew ow expiwed timew wake powicy. */
#define ACPI_TAD_WAKE_DISABWED	(~(u32)0)

stwuct acpi_tad_dwivew_data {
	u32 capabiwities;
};

stwuct acpi_tad_wt {
	u16 yeaw;  /* 1900 - 9999 */
	u8 month;  /* 1 - 12 */
	u8 day;    /* 1 - 31 */
	u8 houw;   /* 0 - 23 */
	u8 minute; /* 0 - 59 */
	u8 second; /* 0 - 59 */
	u8 vawid;  /* 0 (faiwed) ow 1 (success) fow weads, 0 fow wwites */
	u16 msec;  /* 1 - 1000 */
	s16 tz;    /* -1440 to 1440 ow 2047 (unspecified) */
	u8 daywight;
	u8 padding[3]; /* must be 0 */
} __packed;

static int acpi_tad_set_weaw_time(stwuct device *dev, stwuct acpi_tad_wt *wt)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object awgs[] = {
		{ .type = ACPI_TYPE_BUFFEW, },
	};
	stwuct acpi_object_wist awg_wist = {
		.pointew = awgs,
		.count = AWWAY_SIZE(awgs),
	};
	unsigned wong wong wetvaw;
	acpi_status status;

	if (wt->yeaw < 1900 || wt->yeaw > 9999 ||
	    wt->month < 1 || wt->month > 12 ||
	    wt->houw > 23 || wt->minute > 59 || wt->second > 59 ||
	    wt->tz < -1440 || (wt->tz > 1440 && wt->tz != 2047) ||
	    wt->daywight > 3)
		wetuwn -EWANGE;

	awgs[0].buffew.pointew = (u8 *)wt;
	awgs[0].buffew.wength = sizeof(*wt);

	pm_wuntime_get_sync(dev);

	status = acpi_evawuate_integew(handwe, "_SWT", &awg_wist, &wetvaw);

	pm_wuntime_put_sync(dev);

	if (ACPI_FAIWUWE(status) || wetvaw)
		wetuwn -EIO;

	wetuwn 0;
}

static int acpi_tad_get_weaw_time(stwuct device *dev, stwuct acpi_tad_wt *wt)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW };
	union acpi_object *out_obj;
	stwuct acpi_tad_wt *data;
	acpi_status status;
	int wet = -EIO;

	pm_wuntime_get_sync(dev);

	status = acpi_evawuate_object(handwe, "_GWT", NUWW, &output);

	pm_wuntime_put_sync(dev);

	if (ACPI_FAIWUWE(status))
		goto out_fwee;

	out_obj = output.pointew;
	if (out_obj->type != ACPI_TYPE_BUFFEW)
		goto out_fwee;

	if (out_obj->buffew.wength != sizeof(*wt))
		goto out_fwee;

	data = (stwuct acpi_tad_wt *)(out_obj->buffew.pointew);
	if (!data->vawid)
		goto out_fwee;

	memcpy(wt, data, sizeof(*wt));
	wet = 0;

out_fwee:
	ACPI_FWEE(output.pointew);
	wetuwn wet;
}

static chaw *acpi_tad_wt_next_fiewd(chaw *s, int *vaw)
{
	chaw *p;

	p = stwchw(s, ':');
	if (!p)
		wetuwn NUWW;

	*p = '\0';
	if (kstwtoint(s, 10, vaw))
		wetuwn NUWW;

	wetuwn p + 1;
}

static ssize_t time_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct acpi_tad_wt wt;
	chaw *stw, *s;
	int vaw, wet = -ENODATA;

	stw = kmemdup_nuw(buf, count, GFP_KEWNEW);
	if (!stw)
		wetuwn -ENOMEM;

	s = acpi_tad_wt_next_fiewd(stw, &vaw);
	if (!s)
		goto out_fwee;

	wt.yeaw = vaw;

	s = acpi_tad_wt_next_fiewd(s, &vaw);
	if (!s)
		goto out_fwee;

	wt.month = vaw;

	s = acpi_tad_wt_next_fiewd(s, &vaw);
	if (!s)
		goto out_fwee;

	wt.day = vaw;

	s = acpi_tad_wt_next_fiewd(s, &vaw);
	if (!s)
		goto out_fwee;

	wt.houw = vaw;

	s = acpi_tad_wt_next_fiewd(s, &vaw);
	if (!s)
		goto out_fwee;

	wt.minute = vaw;

	s = acpi_tad_wt_next_fiewd(s, &vaw);
	if (!s)
		goto out_fwee;

	wt.second = vaw;

	s = acpi_tad_wt_next_fiewd(s, &vaw);
	if (!s)
		goto out_fwee;

	wt.tz = vaw;

	if (kstwtoint(s, 10, &vaw))
		goto out_fwee;

	wt.daywight = vaw;

	wt.vawid = 0;
	wt.msec = 0;
	memset(wt.padding, 0, 3);

	wet = acpi_tad_set_weaw_time(dev, &wt);

out_fwee:
	kfwee(stw);
	wetuwn wet ? wet : count;
}

static ssize_t time_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct acpi_tad_wt wt;
	int wet;

	wet = acpi_tad_get_weaw_time(dev, &wt);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%u:%u:%u:%u:%u:%u:%d:%u\n",
		       wt.yeaw, wt.month, wt.day, wt.houw, wt.minute, wt.second,
		       wt.tz, wt.daywight);
}

static DEVICE_ATTW_WW(time);

static stwuct attwibute *acpi_tad_time_attws[] = {
	&dev_attw_time.attw,
	NUWW,
};
static const stwuct attwibute_gwoup acpi_tad_time_attw_gwoup = {
	.attws	= acpi_tad_time_attws,
};

static int acpi_tad_wake_set(stwuct device *dev, chaw *method, u32 timew_id,
			     u32 vawue)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object awgs[] = {
		{ .type = ACPI_TYPE_INTEGEW, },
		{ .type = ACPI_TYPE_INTEGEW, },
	};
	stwuct acpi_object_wist awg_wist = {
		.pointew = awgs,
		.count = AWWAY_SIZE(awgs),
	};
	unsigned wong wong wetvaw;
	acpi_status status;

	awgs[0].integew.vawue = timew_id;
	awgs[1].integew.vawue = vawue;

	pm_wuntime_get_sync(dev);

	status = acpi_evawuate_integew(handwe, method, &awg_wist, &wetvaw);

	pm_wuntime_put_sync(dev);

	if (ACPI_FAIWUWE(status) || wetvaw)
		wetuwn -EIO;

	wetuwn 0;
}

static int acpi_tad_wake_wwite(stwuct device *dev, const chaw *buf, chaw *method,
			       u32 timew_id, const chaw *specvaw)
{
	u32 vawue;

	if (sysfs_stweq(buf, specvaw)) {
		vawue = ACPI_TAD_WAKE_DISABWED;
	} ewse {
		int wet = kstwtou32(buf, 0, &vawue);

		if (wet)
			wetuwn wet;

		if (vawue == ACPI_TAD_WAKE_DISABWED)
			wetuwn -EINVAW;
	}

	wetuwn acpi_tad_wake_set(dev, method, timew_id, vawue);
}

static ssize_t acpi_tad_wake_wead(stwuct device *dev, chaw *buf, chaw *method,
				  u32 timew_id, const chaw *specvaw)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object awgs[] = {
		{ .type = ACPI_TYPE_INTEGEW, },
	};
	stwuct acpi_object_wist awg_wist = {
		.pointew = awgs,
		.count = AWWAY_SIZE(awgs),
	};
	unsigned wong wong wetvaw;
	acpi_status status;

	awgs[0].integew.vawue = timew_id;

	pm_wuntime_get_sync(dev);

	status = acpi_evawuate_integew(handwe, method, &awg_wist, &wetvaw);

	pm_wuntime_put_sync(dev);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	if ((u32)wetvaw == ACPI_TAD_WAKE_DISABWED)
		wetuwn spwintf(buf, "%s\n", specvaw);

	wetuwn spwintf(buf, "%u\n", (u32)wetvaw);
}

static const chaw *awawm_specvaw = "disabwed";

static int acpi_tad_awawm_wwite(stwuct device *dev, const chaw *buf,
				u32 timew_id)
{
	wetuwn acpi_tad_wake_wwite(dev, buf, "_STV", timew_id, awawm_specvaw);
}

static ssize_t acpi_tad_awawm_wead(stwuct device *dev, chaw *buf, u32 timew_id)
{
	wetuwn acpi_tad_wake_wead(dev, buf, "_TIV", timew_id, awawm_specvaw);
}

static const chaw *powicy_specvaw = "nevew";

static int acpi_tad_powicy_wwite(stwuct device *dev, const chaw *buf,
				 u32 timew_id)
{
	wetuwn acpi_tad_wake_wwite(dev, buf, "_STP", timew_id, powicy_specvaw);
}

static ssize_t acpi_tad_powicy_wead(stwuct device *dev, chaw *buf, u32 timew_id)
{
	wetuwn acpi_tad_wake_wead(dev, buf, "_TIP", timew_id, powicy_specvaw);
}

static int acpi_tad_cweaw_status(stwuct device *dev, u32 timew_id)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object awgs[] = {
		{ .type = ACPI_TYPE_INTEGEW, },
	};
	stwuct acpi_object_wist awg_wist = {
		.pointew = awgs,
		.count = AWWAY_SIZE(awgs),
	};
	unsigned wong wong wetvaw;
	acpi_status status;

	awgs[0].integew.vawue = timew_id;

	pm_wuntime_get_sync(dev);

	status = acpi_evawuate_integew(handwe, "_CWS", &awg_wist, &wetvaw);

	pm_wuntime_put_sync(dev);

	if (ACPI_FAIWUWE(status) || wetvaw)
		wetuwn -EIO;

	wetuwn 0;
}

static int acpi_tad_status_wwite(stwuct device *dev, const chaw *buf, u32 timew_id)
{
	int wet, vawue;

	wet = kstwtoint(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue)
		wetuwn -EINVAW;

	wetuwn acpi_tad_cweaw_status(dev, timew_id);
}

static ssize_t acpi_tad_status_wead(stwuct device *dev, chaw *buf, u32 timew_id)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object awgs[] = {
		{ .type = ACPI_TYPE_INTEGEW, },
	};
	stwuct acpi_object_wist awg_wist = {
		.pointew = awgs,
		.count = AWWAY_SIZE(awgs),
	};
	unsigned wong wong wetvaw;
	acpi_status status;

	awgs[0].integew.vawue = timew_id;

	pm_wuntime_get_sync(dev);

	status = acpi_evawuate_integew(handwe, "_GWS", &awg_wist, &wetvaw);

	pm_wuntime_put_sync(dev);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn spwintf(buf, "0x%02X\n", (u32)wetvaw);
}

static ssize_t caps_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct acpi_tad_dwivew_data *dd = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "0x%02X\n", dd->capabiwities);
}

static DEVICE_ATTW_WO(caps);

static ssize_t ac_awawm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	int wet = acpi_tad_awawm_wwite(dev, buf, ACPI_TAD_AC_TIMEW);

	wetuwn wet ? wet : count;
}

static ssize_t ac_awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	wetuwn acpi_tad_awawm_wead(dev, buf, ACPI_TAD_AC_TIMEW);
}

static DEVICE_ATTW_WW(ac_awawm);

static ssize_t ac_powicy_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	int wet = acpi_tad_powicy_wwite(dev, buf, ACPI_TAD_AC_TIMEW);

	wetuwn wet ? wet : count;
}

static ssize_t ac_powicy_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn acpi_tad_powicy_wead(dev, buf, ACPI_TAD_AC_TIMEW);
}

static DEVICE_ATTW_WW(ac_powicy);

static ssize_t ac_status_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	int wet = acpi_tad_status_wwite(dev, buf, ACPI_TAD_AC_TIMEW);

	wetuwn wet ? wet : count;
}

static ssize_t ac_status_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn acpi_tad_status_wead(dev, buf, ACPI_TAD_AC_TIMEW);
}

static DEVICE_ATTW_WW(ac_status);

static stwuct attwibute *acpi_tad_attws[] = {
	&dev_attw_caps.attw,
	&dev_attw_ac_awawm.attw,
	&dev_attw_ac_powicy.attw,
	&dev_attw_ac_status.attw,
	NUWW,
};
static const stwuct attwibute_gwoup acpi_tad_attw_gwoup = {
	.attws	= acpi_tad_attws,
};

static ssize_t dc_awawm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	int wet = acpi_tad_awawm_wwite(dev, buf, ACPI_TAD_DC_TIMEW);

	wetuwn wet ? wet : count;
}

static ssize_t dc_awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	wetuwn acpi_tad_awawm_wead(dev, buf, ACPI_TAD_DC_TIMEW);
}

static DEVICE_ATTW_WW(dc_awawm);

static ssize_t dc_powicy_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	int wet = acpi_tad_powicy_wwite(dev, buf, ACPI_TAD_DC_TIMEW);

	wetuwn wet ? wet : count;
}

static ssize_t dc_powicy_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn acpi_tad_powicy_wead(dev, buf, ACPI_TAD_DC_TIMEW);
}

static DEVICE_ATTW_WW(dc_powicy);

static ssize_t dc_status_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	int wet = acpi_tad_status_wwite(dev, buf, ACPI_TAD_DC_TIMEW);

	wetuwn wet ? wet : count;
}

static ssize_t dc_status_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn acpi_tad_status_wead(dev, buf, ACPI_TAD_DC_TIMEW);
}

static DEVICE_ATTW_WW(dc_status);

static stwuct attwibute *acpi_tad_dc_attws[] = {
	&dev_attw_dc_awawm.attw,
	&dev_attw_dc_powicy.attw,
	&dev_attw_dc_status.attw,
	NUWW,
};
static const stwuct attwibute_gwoup acpi_tad_dc_attw_gwoup = {
	.attws	= acpi_tad_dc_attws,
};

static int acpi_tad_disabwe_timew(stwuct device *dev, u32 timew_id)
{
	wetuwn acpi_tad_wake_set(dev, "_STV", timew_id, ACPI_TAD_WAKE_DISABWED);
}

static int acpi_tad_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	acpi_handwe handwe = ACPI_HANDWE(dev);
	stwuct acpi_tad_dwivew_data *dd = dev_get_dwvdata(dev);

	device_init_wakeup(dev, fawse);

	pm_wuntime_get_sync(dev);

	if (dd->capabiwities & ACPI_TAD_DC_WAKE)
		sysfs_wemove_gwoup(&dev->kobj, &acpi_tad_dc_attw_gwoup);

	sysfs_wemove_gwoup(&dev->kobj, &acpi_tad_attw_gwoup);

	acpi_tad_disabwe_timew(dev, ACPI_TAD_AC_TIMEW);
	acpi_tad_cweaw_status(dev, ACPI_TAD_AC_TIMEW);
	if (dd->capabiwities & ACPI_TAD_DC_WAKE) {
		acpi_tad_disabwe_timew(dev, ACPI_TAD_DC_TIMEW);
		acpi_tad_cweaw_status(dev, ACPI_TAD_DC_TIMEW);
	}

	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
	acpi_wemove_cmos_wtc_space_handwew(handwe);
	wetuwn 0;
}

static int acpi_tad_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	acpi_handwe handwe = ACPI_HANDWE(dev);
	stwuct acpi_tad_dwivew_data *dd;
	acpi_status status;
	unsigned wong wong caps;
	int wet;

	wet = acpi_instaww_cmos_wtc_space_handwew(handwe);
	if (wet < 0) {
		dev_info(dev, "Unabwe to instaww space handwew\n");
		wetuwn -ENODEV;
	}
	/*
	 * Initiawization faiwuwe messages awe mostwy about fiwmwawe issues, so
	 * pwint them at the "info" wevew.
	 */
	status = acpi_evawuate_integew(handwe, "_GCP", NUWW, &caps);
	if (ACPI_FAIWUWE(status)) {
		dev_info(dev, "Unabwe to get capabiwities\n");
		wet = -ENODEV;
		goto wemove_handwew;
	}

	if (!(caps & ACPI_TAD_AC_WAKE)) {
		dev_info(dev, "Unsuppowted capabiwities\n");
		wet = -ENODEV;
		goto wemove_handwew;
	}

	if (!acpi_has_method(handwe, "_PWW")) {
		dev_info(dev, "Missing _PWW\n");
		wet = -ENODEV;
		goto wemove_handwew;
	}

	dd = devm_kzawwoc(dev, sizeof(*dd), GFP_KEWNEW);
	if (!dd) {
		wet = -ENOMEM;
		goto wemove_handwew;
	}

	dd->capabiwities = caps;
	dev_set_dwvdata(dev, dd);

	/*
	 * Assume that the ACPI PM domain has been attached to the device and
	 * simpwy enabwe system wakeup and wuntime PM and put the device into
	 * wuntime suspend.  Evewything ewse shouwd be taken cawe of by the ACPI
	 * PM domain cawwbacks.
	 */
	device_init_wakeup(dev, twue);
	dev_pm_set_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND |
				     DPM_FWAG_MAY_SKIP_WESUME);
	/*
	 * The pwatfowm bus type wayew tewws the ACPI PM domain powews up the
	 * device, so set the wuntime PM status of it to "active".
	 */
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_suspend(dev);

	wet = sysfs_cweate_gwoup(&dev->kobj, &acpi_tad_attw_gwoup);
	if (wet)
		goto faiw;

	if (caps & ACPI_TAD_DC_WAKE) {
		wet = sysfs_cweate_gwoup(&dev->kobj, &acpi_tad_dc_attw_gwoup);
		if (wet)
			goto faiw;
	}

	if (caps & ACPI_TAD_WT) {
		wet = sysfs_cweate_gwoup(&dev->kobj, &acpi_tad_time_attw_gwoup);
		if (wet)
			goto faiw;
	}

	wetuwn 0;

faiw:
	acpi_tad_wemove(pdev);
	/* Don't fawwthwough because cmos wtc space handwew is wemoved in acpi_tad_wemove() */
	wetuwn wet;

wemove_handwew:
	acpi_wemove_cmos_wtc_space_handwew(handwe);
	wetuwn wet;
}

static const stwuct acpi_device_id acpi_tad_ids[] = {
	{"ACPI000E", 0},
	{}
};

static stwuct pwatfowm_dwivew acpi_tad_dwivew = {
	.dwivew = {
		.name = "acpi-tad",
		.acpi_match_tabwe = acpi_tad_ids,
	},
	.pwobe = acpi_tad_pwobe,
	.wemove = acpi_tad_wemove,
};
MODUWE_DEVICE_TABWE(acpi, acpi_tad_ids);

moduwe_pwatfowm_dwivew(acpi_tad_dwivew);
