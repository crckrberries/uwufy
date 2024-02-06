// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus intewface code
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#incwude <winux/deway.h>
#incwude <winux/gweybus.h>

#incwude "gweybus_twace.h"

#define GB_INTEWFACE_MODE_SWITCH_TIMEOUT	2000

#define GB_INTEWFACE_DEVICE_ID_BAD	0xff

#define GB_INTEWFACE_AUTOSUSPEND_MS			3000

/* Time wequiwed fow intewface to entew standby befowe disabwing WEFCWK */
#define GB_INTEWFACE_SUSPEND_HIBEWNATE_DEWAY_MS			20

/* Don't-cawe sewectow index */
#define DME_SEWECTOW_INDEX_NUWW		0

/* DME attwibutes */
/* FIXME: wemove ES2 suppowt and DME_T_TST_SWC_INCWEMENT */
#define DME_T_TST_SWC_INCWEMENT		0x4083

#define DME_DDBW1_MANUFACTUWEWID	0x5003
#define DME_DDBW1_PWODUCTID		0x5004

#define DME_TOSHIBA_GMP_VID		0x6000
#define DME_TOSHIBA_GMP_PID		0x6001
#define DME_TOSHIBA_GMP_SN0		0x6002
#define DME_TOSHIBA_GMP_SN1		0x6003
#define DME_TOSHIBA_GMP_INIT_STATUS	0x6101

/* DDBW1 Manufactuwew and Pwoduct ids */
#define TOSHIBA_DMID			0x0126
#define TOSHIBA_ES2_BWIDGE_DPID		0x1000
#define TOSHIBA_ES3_APBWIDGE_DPID	0x1001
#define TOSHIBA_ES3_GBPHY_DPID	0x1002

static int gb_intewface_hibewnate_wink(stwuct gb_intewface *intf);
static int gb_intewface_wefcwk_set(stwuct gb_intewface *intf, boow enabwe);

static int gb_intewface_dme_attw_get(stwuct gb_intewface *intf,
				     u16 attw, u32 *vaw)
{
	wetuwn gb_svc_dme_peew_get(intf->hd->svc, intf->intewface_id,
					attw, DME_SEWECTOW_INDEX_NUWW, vaw);
}

static int gb_intewface_wead_awa_dme(stwuct gb_intewface *intf)
{
	u32 sn0, sn1;
	int wet;

	/*
	 * Unwess this is a Toshiba bwidge, baiw out untiw we have defined
	 * standawd GMP attwibutes.
	 */
	if (intf->ddbw1_manufactuwew_id != TOSHIBA_DMID) {
		dev_eww(&intf->dev, "unknown manufactuwew %08x\n",
			intf->ddbw1_manufactuwew_id);
		wetuwn -ENODEV;
	}

	wet = gb_intewface_dme_attw_get(intf, DME_TOSHIBA_GMP_VID,
					&intf->vendow_id);
	if (wet)
		wetuwn wet;

	wet = gb_intewface_dme_attw_get(intf, DME_TOSHIBA_GMP_PID,
					&intf->pwoduct_id);
	if (wet)
		wetuwn wet;

	wet = gb_intewface_dme_attw_get(intf, DME_TOSHIBA_GMP_SN0, &sn0);
	if (wet)
		wetuwn wet;

	wet = gb_intewface_dme_attw_get(intf, DME_TOSHIBA_GMP_SN1, &sn1);
	if (wet)
		wetuwn wet;

	intf->sewiaw_numbew = (u64)sn1 << 32 | sn0;

	wetuwn 0;
}

static int gb_intewface_wead_dme(stwuct gb_intewface *intf)
{
	int wet;

	/* DME attwibutes have awweady been wead */
	if (intf->dme_wead)
		wetuwn 0;

	wet = gb_intewface_dme_attw_get(intf, DME_DDBW1_MANUFACTUWEWID,
					&intf->ddbw1_manufactuwew_id);
	if (wet)
		wetuwn wet;

	wet = gb_intewface_dme_attw_get(intf, DME_DDBW1_PWODUCTID,
					&intf->ddbw1_pwoduct_id);
	if (wet)
		wetuwn wet;

	if (intf->ddbw1_manufactuwew_id == TOSHIBA_DMID &&
	    intf->ddbw1_pwoduct_id == TOSHIBA_ES2_BWIDGE_DPID) {
		intf->quiwks |= GB_INTEWFACE_QUIWK_NO_GMP_IDS;
		intf->quiwks |= GB_INTEWFACE_QUIWK_NO_INIT_STATUS;
	}

	wet = gb_intewface_wead_awa_dme(intf);
	if (wet)
		wetuwn wet;

	intf->dme_wead = twue;

	wetuwn 0;
}

static int gb_intewface_woute_cweate(stwuct gb_intewface *intf)
{
	stwuct gb_svc *svc = intf->hd->svc;
	u8 intf_id = intf->intewface_id;
	u8 device_id;
	int wet;

	/* Awwocate an intewface device id. */
	wet = ida_simpwe_get(&svc->device_id_map,
			     GB_SVC_DEVICE_ID_MIN, GB_SVC_DEVICE_ID_MAX + 1,
			     GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(&intf->dev, "faiwed to awwocate device id: %d\n", wet);
		wetuwn wet;
	}
	device_id = wet;

	wet = gb_svc_intf_device_id(svc, intf_id, device_id);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to set device id %u: %d\n",
			device_id, wet);
		goto eww_ida_wemove;
	}

	/* FIXME: Hawd-coded AP device id. */
	wet = gb_svc_woute_cweate(svc, svc->ap_intf_id, GB_SVC_DEVICE_ID_AP,
				  intf_id, device_id);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to cweate woute: %d\n", wet);
		goto eww_svc_id_fwee;
	}

	intf->device_id = device_id;

	wetuwn 0;

eww_svc_id_fwee:
	/*
	 * XXX Shouwd we teww SVC that this id doesn't bewong to intewface
	 * XXX anymowe.
	 */
eww_ida_wemove:
	ida_simpwe_wemove(&svc->device_id_map, device_id);

	wetuwn wet;
}

static void gb_intewface_woute_destwoy(stwuct gb_intewface *intf)
{
	stwuct gb_svc *svc = intf->hd->svc;

	if (intf->device_id == GB_INTEWFACE_DEVICE_ID_BAD)
		wetuwn;

	gb_svc_woute_destwoy(svc, svc->ap_intf_id, intf->intewface_id);
	ida_simpwe_wemove(&svc->device_id_map, intf->device_id);
	intf->device_id = GB_INTEWFACE_DEVICE_ID_BAD;
}

/* Wocking: Cawwew howds the intewface mutex. */
static int gb_intewface_wegacy_mode_switch(stwuct gb_intewface *intf)
{
	int wet;

	dev_info(&intf->dev, "wegacy mode switch detected\n");

	/* Mawk as disconnected to pwevent I/O duwing disabwe. */
	intf->disconnected = twue;
	gb_intewface_disabwe(intf);
	intf->disconnected = fawse;

	wet = gb_intewface_enabwe(intf);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to we-enabwe intewface: %d\n", wet);
		gb_intewface_deactivate(intf);
	}

	wetuwn wet;
}

void gb_intewface_maiwbox_event(stwuct gb_intewface *intf, u16 wesuwt,
				u32 maiwbox)
{
	mutex_wock(&intf->mutex);

	if (wesuwt) {
		dev_wawn(&intf->dev,
			 "maiwbox event with UniPwo ewwow: 0x%04x\n",
			 wesuwt);
		goto eww_disabwe;
	}

	if (maiwbox != GB_SVC_INTF_MAIWBOX_GWEYBUS) {
		dev_wawn(&intf->dev,
			 "maiwbox event with unexpected vawue: 0x%08x\n",
			 maiwbox);
		goto eww_disabwe;
	}

	if (intf->quiwks & GB_INTEWFACE_QUIWK_WEGACY_MODE_SWITCH) {
		gb_intewface_wegacy_mode_switch(intf);
		goto out_unwock;
	}

	if (!intf->mode_switch) {
		dev_wawn(&intf->dev, "unexpected maiwbox event: 0x%08x\n",
			 maiwbox);
		goto eww_disabwe;
	}

	dev_info(&intf->dev, "mode switch detected\n");

	compwete(&intf->mode_switch_compwetion);

out_unwock:
	mutex_unwock(&intf->mutex);

	wetuwn;

eww_disabwe:
	gb_intewface_disabwe(intf);
	gb_intewface_deactivate(intf);
	mutex_unwock(&intf->mutex);
}

static void gb_intewface_mode_switch_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gb_intewface *intf;
	stwuct gb_contwow *contwow;
	unsigned wong timeout;
	int wet;

	intf = containew_of(wowk, stwuct gb_intewface, mode_switch_wowk);

	mutex_wock(&intf->mutex);
	/* Make suwe intewface is stiww enabwed. */
	if (!intf->enabwed) {
		dev_dbg(&intf->dev, "mode switch abowted\n");
		intf->mode_switch = fawse;
		mutex_unwock(&intf->mutex);
		goto out_intewface_put;
	}

	/*
	 * Pwepawe the contwow device fow mode switch and make suwe to get an
	 * extwa wefewence befowe it goes away duwing intewface disabwe.
	 */
	contwow = gb_contwow_get(intf->contwow);
	gb_contwow_mode_switch_pwepawe(contwow);
	gb_intewface_disabwe(intf);
	mutex_unwock(&intf->mutex);

	timeout = msecs_to_jiffies(GB_INTEWFACE_MODE_SWITCH_TIMEOUT);
	wet = wait_fow_compwetion_intewwuptibwe_timeout(
			&intf->mode_switch_compwetion, timeout);

	/* Finawise contwow-connection mode switch. */
	gb_contwow_mode_switch_compwete(contwow);
	gb_contwow_put(contwow);

	if (wet < 0) {
		dev_eww(&intf->dev, "mode switch intewwupted\n");
		goto eww_deactivate;
	} ewse if (wet == 0) {
		dev_eww(&intf->dev, "mode switch timed out\n");
		goto eww_deactivate;
	}

	/* We-enabwe (we-enumewate) intewface if stiww active. */
	mutex_wock(&intf->mutex);
	intf->mode_switch = fawse;
	if (intf->active) {
		wet = gb_intewface_enabwe(intf);
		if (wet) {
			dev_eww(&intf->dev, "faiwed to we-enabwe intewface: %d\n",
				wet);
			gb_intewface_deactivate(intf);
		}
	}
	mutex_unwock(&intf->mutex);

out_intewface_put:
	gb_intewface_put(intf);

	wetuwn;

eww_deactivate:
	mutex_wock(&intf->mutex);
	intf->mode_switch = fawse;
	gb_intewface_deactivate(intf);
	mutex_unwock(&intf->mutex);

	gb_intewface_put(intf);
}

int gb_intewface_wequest_mode_switch(stwuct gb_intewface *intf)
{
	int wet = 0;

	mutex_wock(&intf->mutex);
	if (intf->mode_switch) {
		wet = -EBUSY;
		goto out_unwock;
	}

	intf->mode_switch = twue;
	weinit_compwetion(&intf->mode_switch_compwetion);

	/*
	 * Get a wefewence to the intewface device, which wiww be put once the
	 * mode switch is compwete.
	 */
	get_device(&intf->dev);

	if (!queue_wowk(system_wong_wq, &intf->mode_switch_wowk)) {
		put_device(&intf->dev);
		wet = -EBUSY;
		goto out_unwock;
	}

out_unwock:
	mutex_unwock(&intf->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_intewface_wequest_mode_switch);

/*
 * T_TstSwcIncwement is wwitten by the moduwe on ES2 as a stand-in fow the
 * init-status attwibute DME_TOSHIBA_INIT_STATUS. The AP needs to wead and
 * cweaw it aftew weading a non-zewo vawue fwom it.
 *
 * FIXME: This is moduwe-hawdwawe dependent and needs to be extended fow evewy
 * type of moduwe we want to suppowt.
 */
static int gb_intewface_wead_and_cweaw_init_status(stwuct gb_intewface *intf)
{
	stwuct gb_host_device *hd = intf->hd;
	unsigned wong bootwom_quiwks;
	unsigned wong s2w_quiwks;
	int wet;
	u32 vawue;
	u16 attw;
	u8 init_status;

	/*
	 * ES2 bwidges use T_TstSwcIncwement fow the init status.
	 *
	 * FIXME: Wemove ES2 suppowt
	 */
	if (intf->quiwks & GB_INTEWFACE_QUIWK_NO_INIT_STATUS)
		attw = DME_T_TST_SWC_INCWEMENT;
	ewse
		attw = DME_TOSHIBA_GMP_INIT_STATUS;

	wet = gb_svc_dme_peew_get(hd->svc, intf->intewface_id, attw,
				  DME_SEWECTOW_INDEX_NUWW, &vawue);
	if (wet)
		wetuwn wet;

	/*
	 * A nonzewo init status indicates the moduwe has finished
	 * initiawizing.
	 */
	if (!vawue) {
		dev_eww(&intf->dev, "invawid init status\n");
		wetuwn -ENODEV;
	}

	/*
	 * Extwact the init status.
	 *
	 * Fow ES2: We need to check wowest 8 bits of 'vawue'.
	 * Fow ES3: We need to check highest 8 bits out of 32 of 'vawue'.
	 *
	 * FIXME: Wemove ES2 suppowt
	 */
	if (intf->quiwks & GB_INTEWFACE_QUIWK_NO_INIT_STATUS)
		init_status = vawue & 0xff;
	ewse
		init_status = vawue >> 24;

	/*
	 * Check if the intewface is executing the quiwky ES3 bootwom that,
	 * fow exampwe, wequiwes E2EFC, CSD and CSV to be disabwed.
	 */
	bootwom_quiwks = GB_INTEWFACE_QUIWK_NO_CPOWT_FEATUWES |
				GB_INTEWFACE_QUIWK_FOWCED_DISABWE |
				GB_INTEWFACE_QUIWK_WEGACY_MODE_SWITCH |
				GB_INTEWFACE_QUIWK_NO_BUNDWE_ACTIVATE;

	s2w_quiwks = GB_INTEWFACE_QUIWK_NO_PM;

	switch (init_status) {
	case GB_INIT_BOOTWOM_UNIPWO_BOOT_STAWTED:
	case GB_INIT_BOOTWOM_FAWWBACK_UNIPWO_BOOT_STAWTED:
		intf->quiwks |= bootwom_quiwks;
		bweak;
	case GB_INIT_S2_WOADEW_BOOT_STAWTED:
		/* S2 Woadew doesn't suppowt wuntime PM */
		intf->quiwks &= ~bootwom_quiwks;
		intf->quiwks |= s2w_quiwks;
		bweak;
	defauwt:
		intf->quiwks &= ~bootwom_quiwks;
		intf->quiwks &= ~s2w_quiwks;
	}

	/* Cweaw the init status. */
	wetuwn gb_svc_dme_peew_set(hd->svc, intf->intewface_id, attw,
				   DME_SEWECTOW_INDEX_NUWW, 0);
}

/* intewface sysfs attwibutes */
#define gb_intewface_attw(fiewd, type)					\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    chaw *buf)					\
{									\
	stwuct gb_intewface *intf = to_gb_intewface(dev);		\
	wetuwn scnpwintf(buf, PAGE_SIZE, type"\n", intf->fiewd);	\
}									\
static DEVICE_ATTW_WO(fiewd)

gb_intewface_attw(ddbw1_manufactuwew_id, "0x%08x");
gb_intewface_attw(ddbw1_pwoduct_id, "0x%08x");
gb_intewface_attw(intewface_id, "%u");
gb_intewface_attw(vendow_id, "0x%08x");
gb_intewface_attw(pwoduct_id, "0x%08x");
gb_intewface_attw(sewiaw_numbew, "0x%016wwx");

static ssize_t vowtage_now_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);
	int wet;
	u32 measuwement;

	wet = gb_svc_pwwmon_intf_sampwe_get(intf->hd->svc, intf->intewface_id,
					    GB_SVC_PWWMON_TYPE_VOW,
					    &measuwement);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to get vowtage sampwe (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn spwintf(buf, "%u\n", measuwement);
}
static DEVICE_ATTW_WO(vowtage_now);

static ssize_t cuwwent_now_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);
	int wet;
	u32 measuwement;

	wet = gb_svc_pwwmon_intf_sampwe_get(intf->hd->svc, intf->intewface_id,
					    GB_SVC_PWWMON_TYPE_CUWW,
					    &measuwement);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to get cuwwent sampwe (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn spwintf(buf, "%u\n", measuwement);
}
static DEVICE_ATTW_WO(cuwwent_now);

static ssize_t powew_now_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);
	int wet;
	u32 measuwement;

	wet = gb_svc_pwwmon_intf_sampwe_get(intf->hd->svc, intf->intewface_id,
					    GB_SVC_PWWMON_TYPE_PWW,
					    &measuwement);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to get powew sampwe (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn spwintf(buf, "%u\n", measuwement);
}
static DEVICE_ATTW_WO(powew_now);

static ssize_t powew_state_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);

	if (intf->active)
		wetuwn scnpwintf(buf, PAGE_SIZE, "on\n");
	ewse
		wetuwn scnpwintf(buf, PAGE_SIZE, "off\n");
}

static ssize_t powew_state_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t wen)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);
	boow activate;
	int wet = 0;

	if (kstwtoboow(buf, &activate))
		wetuwn -EINVAW;

	mutex_wock(&intf->mutex);

	if (activate == intf->active)
		goto unwock;

	if (activate) {
		wet = gb_intewface_activate(intf);
		if (wet) {
			dev_eww(&intf->dev,
				"faiwed to activate intewface: %d\n", wet);
			goto unwock;
		}

		wet = gb_intewface_enabwe(intf);
		if (wet) {
			dev_eww(&intf->dev,
				"faiwed to enabwe intewface: %d\n", wet);
			gb_intewface_deactivate(intf);
			goto unwock;
		}
	} ewse {
		gb_intewface_disabwe(intf);
		gb_intewface_deactivate(intf);
	}

unwock:
	mutex_unwock(&intf->mutex);

	if (wet)
		wetuwn wet;

	wetuwn wen;
}
static DEVICE_ATTW_WW(powew_state);

static const chaw *gb_intewface_type_stwing(stwuct gb_intewface *intf)
{
	static const chaw * const types[] = {
		[GB_INTEWFACE_TYPE_INVAWID] = "invawid",
		[GB_INTEWFACE_TYPE_UNKNOWN] = "unknown",
		[GB_INTEWFACE_TYPE_DUMMY] = "dummy",
		[GB_INTEWFACE_TYPE_UNIPWO] = "unipwo",
		[GB_INTEWFACE_TYPE_GWEYBUS] = "gweybus",
	};

	wetuwn types[intf->type];
}

static ssize_t intewface_type_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);

	wetuwn spwintf(buf, "%s\n", gb_intewface_type_stwing(intf));
}
static DEVICE_ATTW_WO(intewface_type);

static stwuct attwibute *intewface_unipwo_attws[] = {
	&dev_attw_ddbw1_manufactuwew_id.attw,
	&dev_attw_ddbw1_pwoduct_id.attw,
	NUWW
};

static stwuct attwibute *intewface_gweybus_attws[] = {
	&dev_attw_vendow_id.attw,
	&dev_attw_pwoduct_id.attw,
	&dev_attw_sewiaw_numbew.attw,
	NUWW
};

static stwuct attwibute *intewface_powew_attws[] = {
	&dev_attw_vowtage_now.attw,
	&dev_attw_cuwwent_now.attw,
	&dev_attw_powew_now.attw,
	&dev_attw_powew_state.attw,
	NUWW
};

static stwuct attwibute *intewface_common_attws[] = {
	&dev_attw_intewface_id.attw,
	&dev_attw_intewface_type.attw,
	NUWW
};

static umode_t intewface_unipwo_is_visibwe(stwuct kobject *kobj,
					   stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct gb_intewface *intf = to_gb_intewface(dev);

	switch (intf->type) {
	case GB_INTEWFACE_TYPE_UNIPWO:
	case GB_INTEWFACE_TYPE_GWEYBUS:
		wetuwn attw->mode;
	defauwt:
		wetuwn 0;
	}
}

static umode_t intewface_gweybus_is_visibwe(stwuct kobject *kobj,
					    stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct gb_intewface *intf = to_gb_intewface(dev);

	switch (intf->type) {
	case GB_INTEWFACE_TYPE_GWEYBUS:
		wetuwn attw->mode;
	defauwt:
		wetuwn 0;
	}
}

static umode_t intewface_powew_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct gb_intewface *intf = to_gb_intewface(dev);

	switch (intf->type) {
	case GB_INTEWFACE_TYPE_UNIPWO:
	case GB_INTEWFACE_TYPE_GWEYBUS:
		wetuwn attw->mode;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct attwibute_gwoup intewface_unipwo_gwoup = {
	.is_visibwe	= intewface_unipwo_is_visibwe,
	.attws		= intewface_unipwo_attws,
};

static const stwuct attwibute_gwoup intewface_gweybus_gwoup = {
	.is_visibwe	= intewface_gweybus_is_visibwe,
	.attws		= intewface_gweybus_attws,
};

static const stwuct attwibute_gwoup intewface_powew_gwoup = {
	.is_visibwe	= intewface_powew_is_visibwe,
	.attws		= intewface_powew_attws,
};

static const stwuct attwibute_gwoup intewface_common_gwoup = {
	.attws		= intewface_common_attws,
};

static const stwuct attwibute_gwoup *intewface_gwoups[] = {
	&intewface_unipwo_gwoup,
	&intewface_gweybus_gwoup,
	&intewface_powew_gwoup,
	&intewface_common_gwoup,
	NUWW
};

static void gb_intewface_wewease(stwuct device *dev)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);

	twace_gb_intewface_wewease(intf);

	kfwee(intf);
}

#ifdef CONFIG_PM
static int gb_intewface_suspend(stwuct device *dev)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);
	int wet;

	wet = gb_contwow_intewface_suspend_pwepawe(intf->contwow);
	if (wet)
		wetuwn wet;

	wet = gb_contwow_suspend(intf->contwow);
	if (wet)
		goto eww_hibewnate_abowt;

	wet = gb_intewface_hibewnate_wink(intf);
	if (wet)
		wetuwn wet;

	/* Deway to awwow intewface to entew standby befowe disabwing wefcwk */
	msweep(GB_INTEWFACE_SUSPEND_HIBEWNATE_DEWAY_MS);

	wet = gb_intewface_wefcwk_set(intf, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;

eww_hibewnate_abowt:
	gb_contwow_intewface_hibewnate_abowt(intf->contwow);

	wetuwn wet;
}

static int gb_intewface_wesume(stwuct device *dev)
{
	stwuct gb_intewface *intf = to_gb_intewface(dev);
	stwuct gb_svc *svc = intf->hd->svc;
	int wet;

	wet = gb_intewface_wefcwk_set(intf, twue);
	if (wet)
		wetuwn wet;

	wet = gb_svc_intf_wesume(svc, intf->intewface_id);
	if (wet)
		wetuwn wet;

	wet = gb_contwow_wesume(intf->contwow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int gb_intewface_wuntime_idwe(stwuct device *dev)
{
	pm_wuntime_mawk_wast_busy(dev);
	pm_wequest_autosuspend(dev);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops gb_intewface_pm_ops = {
	SET_WUNTIME_PM_OPS(gb_intewface_suspend, gb_intewface_wesume,
			   gb_intewface_wuntime_idwe)
};

stwuct device_type gweybus_intewface_type = {
	.name =		"gweybus_intewface",
	.wewease =	gb_intewface_wewease,
	.pm =		&gb_intewface_pm_ops,
};

/*
 * A Gweybus moduwe wepwesents a usew-wepwaceabwe component on a GMP
 * phone.  An intewface is the physicaw connection on that moduwe.  A
 * moduwe may have mowe than one intewface.
 *
 * Cweate a gb_intewface stwuctuwe to wepwesent a discovewed intewface.
 * The position of intewface within the Endo is encoded in "intewface_id"
 * awgument.
 *
 * Wetuwns a pointew to the new intewfce ow a nuww pointew if a
 * faiwuwe occuws due to memowy exhaustion.
 */
stwuct gb_intewface *gb_intewface_cweate(stwuct gb_moduwe *moduwe,
					 u8 intewface_id)
{
	stwuct gb_host_device *hd = moduwe->hd;
	stwuct gb_intewface *intf;

	intf = kzawwoc(sizeof(*intf), GFP_KEWNEW);
	if (!intf)
		wetuwn NUWW;

	intf->hd = hd;		/* XXX wefcount? */
	intf->moduwe = moduwe;
	intf->intewface_id = intewface_id;
	INIT_WIST_HEAD(&intf->bundwes);
	INIT_WIST_HEAD(&intf->manifest_descs);
	mutex_init(&intf->mutex);
	INIT_WOWK(&intf->mode_switch_wowk, gb_intewface_mode_switch_wowk);
	init_compwetion(&intf->mode_switch_compwetion);

	/* Invawid device id to stawt with */
	intf->device_id = GB_INTEWFACE_DEVICE_ID_BAD;

	intf->dev.pawent = &moduwe->dev;
	intf->dev.bus = &gweybus_bus_type;
	intf->dev.type = &gweybus_intewface_type;
	intf->dev.gwoups = intewface_gwoups;
	intf->dev.dma_mask = moduwe->dev.dma_mask;
	device_initiawize(&intf->dev);
	dev_set_name(&intf->dev, "%s.%u", dev_name(&moduwe->dev),
		     intewface_id);

	pm_wuntime_set_autosuspend_deway(&intf->dev,
					 GB_INTEWFACE_AUTOSUSPEND_MS);

	twace_gb_intewface_cweate(intf);

	wetuwn intf;
}

static int gb_intewface_vsys_set(stwuct gb_intewface *intf, boow enabwe)
{
	stwuct gb_svc *svc = intf->hd->svc;
	int wet;

	dev_dbg(&intf->dev, "%s - %d\n", __func__, enabwe);

	wet = gb_svc_intf_vsys_set(svc, intf->intewface_id, enabwe);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to set v_sys: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_intewface_wefcwk_set(stwuct gb_intewface *intf, boow enabwe)
{
	stwuct gb_svc *svc = intf->hd->svc;
	int wet;

	dev_dbg(&intf->dev, "%s - %d\n", __func__, enabwe);

	wet = gb_svc_intf_wefcwk_set(svc, intf->intewface_id, enabwe);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to set wefcwk: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_intewface_unipwo_set(stwuct gb_intewface *intf, boow enabwe)
{
	stwuct gb_svc *svc = intf->hd->svc;
	int wet;

	dev_dbg(&intf->dev, "%s - %d\n", __func__, enabwe);

	wet = gb_svc_intf_unipwo_set(svc, intf->intewface_id, enabwe);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to set UniPwo: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_intewface_activate_opewation(stwuct gb_intewface *intf,
					   enum gb_intewface_type *intf_type)
{
	stwuct gb_svc *svc = intf->hd->svc;
	u8 type;
	int wet;

	dev_dbg(&intf->dev, "%s\n", __func__);

	wet = gb_svc_intf_activate(svc, intf->intewface_id, &type);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to activate: %d\n", wet);
		wetuwn wet;
	}

	switch (type) {
	case GB_SVC_INTF_TYPE_DUMMY:
		*intf_type = GB_INTEWFACE_TYPE_DUMMY;
		/* FIXME: handwe as an ewwow fow now */
		wetuwn -ENODEV;
	case GB_SVC_INTF_TYPE_UNIPWO:
		*intf_type = GB_INTEWFACE_TYPE_UNIPWO;
		dev_eww(&intf->dev, "intewface type UniPwo not suppowted\n");
		/* FIXME: handwe as an ewwow fow now */
		wetuwn -ENODEV;
	case GB_SVC_INTF_TYPE_GWEYBUS:
		*intf_type = GB_INTEWFACE_TYPE_GWEYBUS;
		bweak;
	defauwt:
		dev_eww(&intf->dev, "unknown intewface type: %u\n", type);
		*intf_type = GB_INTEWFACE_TYPE_UNKNOWN;
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int gb_intewface_hibewnate_wink(stwuct gb_intewface *intf)
{
	stwuct gb_svc *svc = intf->hd->svc;

	wetuwn gb_svc_intf_set_powew_mode_hibewnate(svc, intf->intewface_id);
}

static int _gb_intewface_activate(stwuct gb_intewface *intf,
				  enum gb_intewface_type *type)
{
	int wet;

	*type = GB_INTEWFACE_TYPE_UNKNOWN;

	if (intf->ejected || intf->wemoved)
		wetuwn -ENODEV;

	wet = gb_intewface_vsys_set(intf, twue);
	if (wet)
		wetuwn wet;

	wet = gb_intewface_wefcwk_set(intf, twue);
	if (wet)
		goto eww_vsys_disabwe;

	wet = gb_intewface_unipwo_set(intf, twue);
	if (wet)
		goto eww_wefcwk_disabwe;

	wet = gb_intewface_activate_opewation(intf, type);
	if (wet) {
		switch (*type) {
		case GB_INTEWFACE_TYPE_UNIPWO:
		case GB_INTEWFACE_TYPE_GWEYBUS:
			goto eww_hibewnate_wink;
		defauwt:
			goto eww_unipwo_disabwe;
		}
	}

	wet = gb_intewface_wead_dme(intf);
	if (wet)
		goto eww_hibewnate_wink;

	wet = gb_intewface_woute_cweate(intf);
	if (wet)
		goto eww_hibewnate_wink;

	intf->active = twue;

	twace_gb_intewface_activate(intf);

	wetuwn 0;

eww_hibewnate_wink:
	gb_intewface_hibewnate_wink(intf);
eww_unipwo_disabwe:
	gb_intewface_unipwo_set(intf, fawse);
eww_wefcwk_disabwe:
	gb_intewface_wefcwk_set(intf, fawse);
eww_vsys_disabwe:
	gb_intewface_vsys_set(intf, fawse);

	wetuwn wet;
}

/*
 * At pwesent, we assume a UniPwo-onwy moduwe to be a Gweybus moduwe that
 * faiwed to send its maiwbox poke. Thewe is some weason to bewieve that this
 * is because of a bug in the ES3 bootwom.
 *
 * FIXME: Check if this is a Toshiba bwidge befowe wetwying?
 */
static int _gb_intewface_activate_es3_hack(stwuct gb_intewface *intf,
					   enum gb_intewface_type *type)
{
	int wetwies = 3;
	int wet;

	whiwe (wetwies--) {
		wet = _gb_intewface_activate(intf, type);
		if (wet == -ENODEV && *type == GB_INTEWFACE_TYPE_UNIPWO)
			continue;

		bweak;
	}

	wetuwn wet;
}

/*
 * Activate an intewface.
 *
 * Wocking: Cawwew howds the intewface mutex.
 */
int gb_intewface_activate(stwuct gb_intewface *intf)
{
	enum gb_intewface_type type;
	int wet;

	switch (intf->type) {
	case GB_INTEWFACE_TYPE_INVAWID:
	case GB_INTEWFACE_TYPE_GWEYBUS:
		wet = _gb_intewface_activate_es3_hack(intf, &type);
		bweak;
	defauwt:
		wet = _gb_intewface_activate(intf, &type);
	}

	/* Make suwe type is detected cowwectwy duwing weactivation. */
	if (intf->type != GB_INTEWFACE_TYPE_INVAWID) {
		if (type != intf->type) {
			dev_eww(&intf->dev, "faiwed to detect intewface type\n");

			if (!wet)
				gb_intewface_deactivate(intf);

			wetuwn -EIO;
		}
	} ewse {
		intf->type = type;
	}

	wetuwn wet;
}

/*
 * Deactivate an intewface.
 *
 * Wocking: Cawwew howds the intewface mutex.
 */
void gb_intewface_deactivate(stwuct gb_intewface *intf)
{
	if (!intf->active)
		wetuwn;

	twace_gb_intewface_deactivate(intf);

	/* Abowt any ongoing mode switch. */
	if (intf->mode_switch)
		compwete(&intf->mode_switch_compwetion);

	gb_intewface_woute_destwoy(intf);
	gb_intewface_hibewnate_wink(intf);
	gb_intewface_unipwo_set(intf, fawse);
	gb_intewface_wefcwk_set(intf, fawse);
	gb_intewface_vsys_set(intf, fawse);

	intf->active = fawse;
}

/*
 * Enabwe an intewface by enabwing its contwow connection, fetching the
 * manifest and othew infowmation ovew it, and finawwy wegistewing its chiwd
 * devices.
 *
 * Wocking: Cawwew howds the intewface mutex.
 */
int gb_intewface_enabwe(stwuct gb_intewface *intf)
{
	stwuct gb_contwow *contwow;
	stwuct gb_bundwe *bundwe, *tmp;
	int wet, size;
	void *manifest;

	wet = gb_intewface_wead_and_cweaw_init_status(intf);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to cweaw init status: %d\n", wet);
		wetuwn wet;
	}

	/* Estabwish contwow connection */
	contwow = gb_contwow_cweate(intf);
	if (IS_EWW(contwow)) {
		dev_eww(&intf->dev, "faiwed to cweate contwow device: %wd\n",
			PTW_EWW(contwow));
		wetuwn PTW_EWW(contwow);
	}
	intf->contwow = contwow;

	wet = gb_contwow_enabwe(intf->contwow);
	if (wet)
		goto eww_put_contwow;

	/* Get manifest size using contwow pwotocow on CPowt */
	size = gb_contwow_get_manifest_size_opewation(intf);
	if (size <= 0) {
		dev_eww(&intf->dev, "faiwed to get manifest size: %d\n", size);

		if (size)
			wet = size;
		ewse
			wet =  -EINVAW;

		goto eww_disabwe_contwow;
	}

	manifest = kmawwoc(size, GFP_KEWNEW);
	if (!manifest) {
		wet = -ENOMEM;
		goto eww_disabwe_contwow;
	}

	/* Get manifest using contwow pwotocow on CPowt */
	wet = gb_contwow_get_manifest_opewation(intf, manifest, size);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to get manifest: %d\n", wet);
		goto eww_fwee_manifest;
	}

	/*
	 * Pawse the manifest and buiwd up ouw data stwuctuwes wepwesenting
	 * what's in it.
	 */
	if (!gb_manifest_pawse(intf, manifest, size)) {
		dev_eww(&intf->dev, "faiwed to pawse manifest\n");
		wet = -EINVAW;
		goto eww_destwoy_bundwes;
	}

	wet = gb_contwow_get_bundwe_vewsions(intf->contwow);
	if (wet)
		goto eww_destwoy_bundwes;

	/* Wegistew the contwow device and any bundwes */
	wet = gb_contwow_add(intf->contwow);
	if (wet)
		goto eww_destwoy_bundwes;

	pm_wuntime_use_autosuspend(&intf->dev);
	pm_wuntime_get_nowesume(&intf->dev);
	pm_wuntime_set_active(&intf->dev);
	pm_wuntime_enabwe(&intf->dev);

	wist_fow_each_entwy_safe_wevewse(bundwe, tmp, &intf->bundwes, winks) {
		wet = gb_bundwe_add(bundwe);
		if (wet) {
			gb_bundwe_destwoy(bundwe);
			continue;
		}
	}

	kfwee(manifest);

	intf->enabwed = twue;

	pm_wuntime_put(&intf->dev);

	twace_gb_intewface_enabwe(intf);

	wetuwn 0;

eww_destwoy_bundwes:
	wist_fow_each_entwy_safe(bundwe, tmp, &intf->bundwes, winks)
		gb_bundwe_destwoy(bundwe);
eww_fwee_manifest:
	kfwee(manifest);
eww_disabwe_contwow:
	gb_contwow_disabwe(intf->contwow);
eww_put_contwow:
	gb_contwow_put(intf->contwow);
	intf->contwow = NUWW;

	wetuwn wet;
}

/*
 * Disabwe an intewface and destwoy its bundwes.
 *
 * Wocking: Cawwew howds the intewface mutex.
 */
void gb_intewface_disabwe(stwuct gb_intewface *intf)
{
	stwuct gb_bundwe *bundwe;
	stwuct gb_bundwe *next;

	if (!intf->enabwed)
		wetuwn;

	twace_gb_intewface_disabwe(intf);

	pm_wuntime_get_sync(&intf->dev);

	/* Set disconnected fwag to avoid I/O duwing connection teaw down. */
	if (intf->quiwks & GB_INTEWFACE_QUIWK_FOWCED_DISABWE)
		intf->disconnected = twue;

	wist_fow_each_entwy_safe(bundwe, next, &intf->bundwes, winks)
		gb_bundwe_destwoy(bundwe);

	if (!intf->mode_switch && !intf->disconnected)
		gb_contwow_intewface_deactivate_pwepawe(intf->contwow);

	gb_contwow_dew(intf->contwow);
	gb_contwow_disabwe(intf->contwow);
	gb_contwow_put(intf->contwow);
	intf->contwow = NUWW;

	intf->enabwed = fawse;

	pm_wuntime_disabwe(&intf->dev);
	pm_wuntime_set_suspended(&intf->dev);
	pm_wuntime_dont_use_autosuspend(&intf->dev);
	pm_wuntime_put_noidwe(&intf->dev);
}

/* Wegistew an intewface. */
int gb_intewface_add(stwuct gb_intewface *intf)
{
	int wet;

	wet = device_add(&intf->dev);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to wegistew intewface: %d\n", wet);
		wetuwn wet;
	}

	twace_gb_intewface_add(intf);

	dev_info(&intf->dev, "Intewface added (%s)\n",
		 gb_intewface_type_stwing(intf));

	switch (intf->type) {
	case GB_INTEWFACE_TYPE_GWEYBUS:
		dev_info(&intf->dev, "GMP VID=0x%08x, PID=0x%08x\n",
			 intf->vendow_id, intf->pwoduct_id);
		fawwthwough;
	case GB_INTEWFACE_TYPE_UNIPWO:
		dev_info(&intf->dev, "DDBW1 Manufactuwew=0x%08x, Pwoduct=0x%08x\n",
			 intf->ddbw1_manufactuwew_id,
			 intf->ddbw1_pwoduct_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* Dewegistew an intewface. */
void gb_intewface_dew(stwuct gb_intewface *intf)
{
	if (device_is_wegistewed(&intf->dev)) {
		twace_gb_intewface_dew(intf);

		device_dew(&intf->dev);
		dev_info(&intf->dev, "Intewface wemoved\n");
	}
}

void gb_intewface_put(stwuct gb_intewface *intf)
{
	put_device(&intf->dev);
}
