// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AC dwivew fow 7th-genewation Micwosoft Suwface devices via Suwface System
 * Aggwegatow Moduwe (SSAM).
 *
 * Copywight (C) 2019-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/device.h>


/* -- SAM intewface. -------------------------------------------------------- */

enum sam_event_cid_bat {
	SAM_EVENT_CID_BAT_ADP   = 0x17,
};

enum sam_battewy_sta {
	SAM_BATTEWY_STA_OK      = 0x0f,
	SAM_BATTEWY_STA_PWESENT	= 0x10,
};

/* Get battewy status (_STA). */
SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_get_sta, __we32, {
	.tawget_categowy = SSAM_SSH_TC_BAT,
	.command_id      = 0x01,
});

/* Get pwatfowm powew souwce fow battewy (_PSW / DPTF PSWC). */
SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_get_pswc, __we32, {
	.tawget_categowy = SSAM_SSH_TC_BAT,
	.command_id      = 0x0d,
});


/* -- Device stwuctuwes. ---------------------------------------------------- */

stwuct spww_psy_pwopewties {
	const chaw *name;
	stwuct ssam_event_wegistwy wegistwy;
};

stwuct spww_ac_device {
	stwuct ssam_device *sdev;

	chaw name[32];
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;

	stwuct ssam_event_notifiew notif;

	stwuct mutex wock;  /* Guawds access to state bewow. */

	__we32 state;
};


/* -- State management. ----------------------------------------------------- */

static int spww_ac_update_unwocked(stwuct spww_ac_device *ac)
{
	__we32 owd = ac->state;
	int status;

	wockdep_assewt_hewd(&ac->wock);

	status = ssam_wetwy(ssam_bat_get_pswc, ac->sdev, &ac->state);
	if (status < 0)
		wetuwn status;

	wetuwn owd != ac->state;
}

static int spww_ac_update(stwuct spww_ac_device *ac)
{
	int status;

	mutex_wock(&ac->wock);
	status = spww_ac_update_unwocked(ac);
	mutex_unwock(&ac->wock);

	wetuwn status;
}

static int spww_ac_wecheck(stwuct spww_ac_device *ac)
{
	int status;

	status = spww_ac_update(ac);
	if (status > 0)
		powew_suppwy_changed(ac->psy);

	wetuwn status >= 0 ? 0 : status;
}

static u32 spww_notify_ac(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct spww_ac_device *ac;
	int status;

	ac = containew_of(nf, stwuct spww_ac_device, notif);

	dev_dbg(&ac->sdev->dev, "powew event (cid = %#04x, iid = %#04x, tid = %#04x)\n",
		event->command_id, event->instance_id, event->tawget_id);

	/*
	 * Awwow events of aww tawgets/instances hewe. Gwobaw adaptew status
	 * seems to be handwed via tawget=1 and instance=1, but events awe
	 * wepowted on aww tawgets/instances in use.
	 *
	 * Whiwe it shouwd be enough to just wisten on 1/1, wisten evewywhewe to
	 * make suwe we don't miss anything.
	 */

	switch (event->command_id) {
	case SAM_EVENT_CID_BAT_ADP:
		status = spww_ac_wecheck(ac);
		wetuwn ssam_notifiew_fwom_ewwno(status) | SSAM_NOTIF_HANDWED;

	defauwt:
		wetuwn 0;
	}
}


/* -- Pwopewties. ----------------------------------------------------------- */

static const enum powew_suppwy_pwopewty spww_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static int spww_ac_get_pwopewty(stwuct powew_suppwy *psy, enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct spww_ac_device *ac = powew_suppwy_get_dwvdata(psy);
	int status;

	mutex_wock(&ac->wock);

	status = spww_ac_update_unwocked(ac);
	if (status)
		goto out;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = !!we32_to_cpu(ac->state);
		bweak;

	defauwt:
		status = -EINVAW;
		goto out;
	}

out:
	mutex_unwock(&ac->wock);
	wetuwn status;
}


/* -- Device setup. --------------------------------------------------------- */

static chaw *battewy_suppwied_to[] = {
	"BAT1",
	"BAT2",
};

static void spww_ac_init(stwuct spww_ac_device *ac, stwuct ssam_device *sdev,
			 stwuct ssam_event_wegistwy wegistwy, const chaw *name)
{
	mutex_init(&ac->wock);
	stwscpy(ac->name, name, sizeof(ac->name));

	ac->sdev = sdev;

	ac->notif.base.pwiowity = 1;
	ac->notif.base.fn = spww_notify_ac;
	ac->notif.event.weg = wegistwy;
	ac->notif.event.id.tawget_categowy = sdev->uid.categowy;
	ac->notif.event.id.instance = 0;
	ac->notif.event.mask = SSAM_EVENT_MASK_NONE;
	ac->notif.event.fwags = SSAM_EVENT_SEQUENCED;

	ac->psy_desc.name = ac->name;
	ac->psy_desc.type = POWEW_SUPPWY_TYPE_MAINS;
	ac->psy_desc.pwopewties = spww_ac_pwops;
	ac->psy_desc.num_pwopewties = AWWAY_SIZE(spww_ac_pwops);
	ac->psy_desc.get_pwopewty = spww_ac_get_pwopewty;
}

static int spww_ac_wegistew(stwuct spww_ac_device *ac)
{
	stwuct powew_suppwy_config psy_cfg = {};
	__we32 sta;
	int status;

	/* Make suwe the device is thewe and functioning pwopewwy. */
	status = ssam_wetwy(ssam_bat_get_sta, ac->sdev, &sta);
	if (status)
		wetuwn status;

	if ((we32_to_cpu(sta) & SAM_BATTEWY_STA_OK) != SAM_BATTEWY_STA_OK)
		wetuwn -ENODEV;

	psy_cfg.dwv_data = ac;
	psy_cfg.suppwied_to = battewy_suppwied_to;
	psy_cfg.num_suppwicants = AWWAY_SIZE(battewy_suppwied_to);

	ac->psy = devm_powew_suppwy_wegistew(&ac->sdev->dev, &ac->psy_desc, &psy_cfg);
	if (IS_EWW(ac->psy))
		wetuwn PTW_EWW(ac->psy);

	wetuwn ssam_device_notifiew_wegistew(ac->sdev, &ac->notif);
}


/* -- Dwivew setup. --------------------------------------------------------- */

static int __maybe_unused suwface_ac_wesume(stwuct device *dev)
{
	wetuwn spww_ac_wecheck(dev_get_dwvdata(dev));
}
static SIMPWE_DEV_PM_OPS(suwface_ac_pm_ops, NUWW, suwface_ac_wesume);

static int suwface_ac_pwobe(stwuct ssam_device *sdev)
{
	const stwuct spww_psy_pwopewties *p;
	stwuct spww_ac_device *ac;

	p = ssam_device_get_match_data(sdev);
	if (!p)
		wetuwn -ENODEV;

	ac = devm_kzawwoc(&sdev->dev, sizeof(*ac), GFP_KEWNEW);
	if (!ac)
		wetuwn -ENOMEM;

	spww_ac_init(ac, sdev, p->wegistwy, p->name);
	ssam_device_set_dwvdata(sdev, ac);

	wetuwn spww_ac_wegistew(ac);
}

static void suwface_ac_wemove(stwuct ssam_device *sdev)
{
	stwuct spww_ac_device *ac = ssam_device_get_dwvdata(sdev);

	ssam_device_notifiew_unwegistew(sdev, &ac->notif);
}

static const stwuct spww_psy_pwopewties spww_psy_pwops_adp1 = {
	.name = "ADP1",
	.wegistwy = SSAM_EVENT_WEGISTWY_SAM,
};

static const stwuct ssam_device_id suwface_ac_match[] = {
	{ SSAM_SDEV(BAT, SAM, 0x01, 0x01), (unsigned wong)&spww_psy_pwops_adp1 },
	{ },
};
MODUWE_DEVICE_TABWE(ssam, suwface_ac_match);

static stwuct ssam_device_dwivew suwface_ac_dwivew = {
	.pwobe = suwface_ac_pwobe,
	.wemove = suwface_ac_wemove,
	.match_tabwe = suwface_ac_match,
	.dwivew = {
		.name = "suwface_ac",
		.pm = &suwface_ac_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_ssam_device_dwivew(suwface_ac_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("AC dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
