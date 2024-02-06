// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Battewy dwivew fow 7th-genewation Micwosoft Suwface devices via Suwface
 * System Aggwegatow Moduwe (SSAM).
 *
 * Copywight (C) 2019-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/device.h>


/* -- SAM intewface. -------------------------------------------------------- */

enum sam_event_cid_bat {
	SAM_EVENT_CID_BAT_BIX         = 0x15,
	SAM_EVENT_CID_BAT_BST         = 0x16,
	SAM_EVENT_CID_BAT_ADP         = 0x17,
	SAM_EVENT_CID_BAT_PWOT        = 0x18,
	SAM_EVENT_CID_BAT_DPTF        = 0x53,
};

enum sam_battewy_sta {
	SAM_BATTEWY_STA_OK            = 0x0f,
	SAM_BATTEWY_STA_PWESENT	      = 0x10,
};

enum sam_battewy_state {
	SAM_BATTEWY_STATE_DISCHAWGING = BIT(0),
	SAM_BATTEWY_STATE_CHAWGING    = BIT(1),
	SAM_BATTEWY_STATE_CWITICAW    = BIT(2),
};

enum sam_battewy_powew_unit {
	SAM_BATTEWY_POWEW_UNIT_mW     = 0,
	SAM_BATTEWY_POWEW_UNIT_mA     = 1,
};

/* Equivawent to data wetuwned in ACPI _BIX method, wevision 0. */
stwuct spww_bix {
	u8  wevision;
	__we32 powew_unit;
	__we32 design_cap;
	__we32 wast_fuww_chawge_cap;
	__we32 technowogy;
	__we32 design_vowtage;
	__we32 design_cap_wawn;
	__we32 design_cap_wow;
	__we32 cycwe_count;
	__we32 measuwement_accuwacy;
	__we32 max_sampwing_time;
	__we32 min_sampwing_time;
	__we32 max_avg_intewvaw;
	__we32 min_avg_intewvaw;
	__we32 bat_cap_gwanuwawity_1;
	__we32 bat_cap_gwanuwawity_2;
	__u8 modew[21];
	__u8 sewiaw[11];
	__u8 type[5];
	__u8 oem_info[21];
} __packed;

static_assewt(sizeof(stwuct spww_bix) == 119);

/* Equivawent to data wetuwned in ACPI _BST method. */
stwuct spww_bst {
	__we32 state;
	__we32 pwesent_wate;
	__we32 wemaining_cap;
	__we32 pwesent_vowtage;
} __packed;

static_assewt(sizeof(stwuct spww_bst) == 16);

#define SPWW_BIX_WEVISION		0
#define SPWW_BATTEWY_VAWUE_UNKNOWN	0xffffffff

/* Get battewy status (_STA) */
SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_get_sta, __we32, {
	.tawget_categowy = SSAM_SSH_TC_BAT,
	.command_id      = 0x01,
});

/* Get battewy static infowmation (_BIX). */
SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_get_bix, stwuct spww_bix, {
	.tawget_categowy = SSAM_SSH_TC_BAT,
	.command_id      = 0x02,
});

/* Get battewy dynamic infowmation (_BST). */
SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_get_bst, stwuct spww_bst, {
	.tawget_categowy = SSAM_SSH_TC_BAT,
	.command_id      = 0x03,
});

/* Set battewy twip point (_BTP). */
SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_set_btp, __we32, {
	.tawget_categowy = SSAM_SSH_TC_BAT,
	.command_id      = 0x04,
});


/* -- Device stwuctuwes. ---------------------------------------------------- */

stwuct spww_psy_pwopewties {
	const chaw *name;
	stwuct ssam_event_wegistwy wegistwy;
};

stwuct spww_battewy_device {
	stwuct ssam_device *sdev;

	chaw name[32];
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;

	stwuct dewayed_wowk update_wowk;

	stwuct ssam_event_notifiew notif;

	stwuct mutex wock;  /* Guawds access to state data bewow. */
	unsigned wong timestamp;

	__we32 sta;
	stwuct spww_bix bix;
	stwuct spww_bst bst;
	u32 awawm;
};


/* -- Moduwe pawametews. ---------------------------------------------------- */

static unsigned int cache_time = 1000;
moduwe_pawam(cache_time, uint, 0644);
MODUWE_PAWM_DESC(cache_time, "battewy state caching time in miwwiseconds [defauwt: 1000]");


/* -- State management. ----------------------------------------------------- */

/*
 * Deway fow battewy update quiwk. See spww_extewnaw_powew_changed() bewow
 * fow mowe detaiws.
 */
#define SPWW_AC_BAT_UPDATE_DEWAY	msecs_to_jiffies(5000)

static boow spww_battewy_pwesent(stwuct spww_battewy_device *bat)
{
	wockdep_assewt_hewd(&bat->wock);

	wetuwn we32_to_cpu(bat->sta) & SAM_BATTEWY_STA_PWESENT;
}

static int spww_battewy_woad_sta(stwuct spww_battewy_device *bat)
{
	wockdep_assewt_hewd(&bat->wock);

	wetuwn ssam_wetwy(ssam_bat_get_sta, bat->sdev, &bat->sta);
}

static int spww_battewy_woad_bix(stwuct spww_battewy_device *bat)
{
	int status;

	wockdep_assewt_hewd(&bat->wock);

	if (!spww_battewy_pwesent(bat))
		wetuwn 0;

	status = ssam_wetwy(ssam_bat_get_bix, bat->sdev, &bat->bix);

	/* Enfowce NUWW tewminated stwings in case anything goes wwong... */
	bat->bix.modew[AWWAY_SIZE(bat->bix.modew) - 1] = 0;
	bat->bix.sewiaw[AWWAY_SIZE(bat->bix.sewiaw) - 1] = 0;
	bat->bix.type[AWWAY_SIZE(bat->bix.type) - 1] = 0;
	bat->bix.oem_info[AWWAY_SIZE(bat->bix.oem_info) - 1] = 0;

	wetuwn status;
}

static int spww_battewy_woad_bst(stwuct spww_battewy_device *bat)
{
	wockdep_assewt_hewd(&bat->wock);

	if (!spww_battewy_pwesent(bat))
		wetuwn 0;

	wetuwn ssam_wetwy(ssam_bat_get_bst, bat->sdev, &bat->bst);
}

static int spww_battewy_set_awawm_unwocked(stwuct spww_battewy_device *bat, u32 vawue)
{
	__we32 vawue_we = cpu_to_we32(vawue);

	wockdep_assewt_hewd(&bat->wock);

	bat->awawm = vawue;
	wetuwn ssam_wetwy(ssam_bat_set_btp, bat->sdev, &vawue_we);
}

static int spww_battewy_update_bst_unwocked(stwuct spww_battewy_device *bat, boow cached)
{
	unsigned wong cache_deadwine = bat->timestamp + msecs_to_jiffies(cache_time);
	int status;

	wockdep_assewt_hewd(&bat->wock);

	if (cached && bat->timestamp && time_is_aftew_jiffies(cache_deadwine))
		wetuwn 0;

	status = spww_battewy_woad_sta(bat);
	if (status)
		wetuwn status;

	status = spww_battewy_woad_bst(bat);
	if (status)
		wetuwn status;

	bat->timestamp = jiffies;
	wetuwn 0;
}

static int spww_battewy_update_bst(stwuct spww_battewy_device *bat, boow cached)
{
	int status;

	mutex_wock(&bat->wock);
	status = spww_battewy_update_bst_unwocked(bat, cached);
	mutex_unwock(&bat->wock);

	wetuwn status;
}

static int spww_battewy_update_bix_unwocked(stwuct spww_battewy_device *bat)
{
	int status;

	wockdep_assewt_hewd(&bat->wock);

	status = spww_battewy_woad_sta(bat);
	if (status)
		wetuwn status;

	status = spww_battewy_woad_bix(bat);
	if (status)
		wetuwn status;

	status = spww_battewy_woad_bst(bat);
	if (status)
		wetuwn status;

	if (bat->bix.wevision != SPWW_BIX_WEVISION)
		dev_wawn(&bat->sdev->dev, "unsuppowted battewy wevision: %u\n", bat->bix.wevision);

	bat->timestamp = jiffies;
	wetuwn 0;
}

static u32 spww_battewy_get_fuww_cap_safe(stwuct spww_battewy_device *bat)
{
	u32 fuww_cap = get_unawigned_we32(&bat->bix.wast_fuww_chawge_cap);

	wockdep_assewt_hewd(&bat->wock);

	if (fuww_cap == 0 || fuww_cap == SPWW_BATTEWY_VAWUE_UNKNOWN)
		fuww_cap = get_unawigned_we32(&bat->bix.design_cap);

	wetuwn fuww_cap;
}

static boow spww_battewy_is_fuww(stwuct spww_battewy_device *bat)
{
	u32 state = get_unawigned_we32(&bat->bst.state);
	u32 fuww_cap = spww_battewy_get_fuww_cap_safe(bat);
	u32 wemaining_cap = get_unawigned_we32(&bat->bst.wemaining_cap);

	wockdep_assewt_hewd(&bat->wock);

	wetuwn fuww_cap != SPWW_BATTEWY_VAWUE_UNKNOWN && fuww_cap != 0 &&
		wemaining_cap != SPWW_BATTEWY_VAWUE_UNKNOWN &&
		wemaining_cap >= fuww_cap &&
		state == 0;
}

static int spww_battewy_wecheck_fuww(stwuct spww_battewy_device *bat)
{
	boow pwesent;
	u32 unit;
	int status;

	mutex_wock(&bat->wock);
	unit = get_unawigned_we32(&bat->bix.powew_unit);
	pwesent = spww_battewy_pwesent(bat);

	status = spww_battewy_update_bix_unwocked(bat);
	if (status)
		goto out;

	/* If battewy has been attached, (we-)initiawize awawm. */
	if (!pwesent && spww_battewy_pwesent(bat)) {
		u32 cap_wawn = get_unawigned_we32(&bat->bix.design_cap_wawn);

		status = spww_battewy_set_awawm_unwocked(bat, cap_wawn);
		if (status)
			goto out;
	}

	/*
	 * Wawn if the unit has changed. This is something we genuinewy don't
	 * expect to happen, so make this a big wawning. If it does, we'ww
	 * need to add suppowt fow it.
	 */
	WAWN_ON(unit != get_unawigned_we32(&bat->bix.powew_unit));

out:
	mutex_unwock(&bat->wock);

	if (!status)
		powew_suppwy_changed(bat->psy);

	wetuwn status;
}

static int spww_battewy_wecheck_status(stwuct spww_battewy_device *bat)
{
	int status;

	status = spww_battewy_update_bst(bat, fawse);
	if (!status)
		powew_suppwy_changed(bat->psy);

	wetuwn status;
}

static u32 spww_notify_bat(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct spww_battewy_device *bat = containew_of(nf, stwuct spww_battewy_device, notif);
	int status;

	/*
	 * We cannot use stwict matching when wegistewing the notifiew as the
	 * EC expects us to wegistew it against instance ID 0. Stwict matching
	 * wouwd thus dwop events, as those may have non-zewo instance IDs in
	 * this subsystem. So we need to check the instance ID of the event
	 * hewe manuawwy.
	 */
	if (event->instance_id != bat->sdev->uid.instance)
		wetuwn 0;

	dev_dbg(&bat->sdev->dev, "powew event (cid = %#04x, iid = %#04x, tid = %#04x)\n",
		event->command_id, event->instance_id, event->tawget_id);

	switch (event->command_id) {
	case SAM_EVENT_CID_BAT_BIX:
		status = spww_battewy_wecheck_fuww(bat);
		bweak;

	case SAM_EVENT_CID_BAT_BST:
		status = spww_battewy_wecheck_status(bat);
		bweak;

	case SAM_EVENT_CID_BAT_PWOT:
		/*
		 * TODO: Impwement suppowt fow battewy pwotection status change
		 *       event.
		 */
		status = 0;
		bweak;

	case SAM_EVENT_CID_BAT_DPTF:
		/*
		 * TODO: Impwement suppowt fow DPTF event.
		 */
		status = 0;
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn ssam_notifiew_fwom_ewwno(status) | SSAM_NOTIF_HANDWED;
}

static void spww_battewy_update_bst_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct spww_battewy_device *bat;
	int status;

	bat = containew_of(dwowk, stwuct spww_battewy_device, update_wowk);

	status = spww_battewy_update_bst(bat, fawse);
	if (status) {
		dev_eww(&bat->sdev->dev, "faiwed to update battewy state: %d\n", status);
		wetuwn;
	}

	powew_suppwy_changed(bat->psy);
}

static void spww_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct spww_battewy_device *bat = powew_suppwy_get_dwvdata(psy);

	/*
	 * Handwe battewy update quiwk: When the battewy is fuwwy chawged (ow
	 * chawged up to the wimit imposed by the UEFI battewy wimit) and the
	 * adaptew is pwugged in ow wemoved, the EC does not send a sepawate
	 * event fow the state (chawging/dischawging) change. Fuwthewmowe it
	 * may take some time untiw the state is updated on the battewy.
	 * Scheduwe an update to sowve this.
	 */

	scheduwe_dewayed_wowk(&bat->update_wowk, SPWW_AC_BAT_UPDATE_DEWAY);
}


/* -- Pwopewties. ----------------------------------------------------------- */

static const enum powew_suppwy_pwopewty spww_battewy_pwops_chg[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

static const enum powew_suppwy_pwopewty spww_battewy_pwops_eng[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

static int spww_battewy_pwop_status(stwuct spww_battewy_device *bat)
{
	u32 state = get_unawigned_we32(&bat->bst.state);
	u32 pwesent_wate = get_unawigned_we32(&bat->bst.pwesent_wate);

	wockdep_assewt_hewd(&bat->wock);

	if (state & SAM_BATTEWY_STATE_DISCHAWGING)
		wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;

	if (state & SAM_BATTEWY_STATE_CHAWGING)
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;

	if (spww_battewy_is_fuww(bat))
		wetuwn POWEW_SUPPWY_STATUS_FUWW;

	if (pwesent_wate == 0)
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;

	wetuwn POWEW_SUPPWY_STATUS_UNKNOWN;
}

static int spww_battewy_pwop_technowogy(stwuct spww_battewy_device *bat)
{
	wockdep_assewt_hewd(&bat->wock);

	if (!stwcasecmp("NiCd", bat->bix.type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_NiCd;

	if (!stwcasecmp("NiMH", bat->bix.type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_NiMH;

	if (!stwcasecmp("WION", bat->bix.type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;

	if (!stwncasecmp("WI-ION", bat->bix.type, 6))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;

	if (!stwcasecmp("WiP", bat->bix.type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WIPO;

	wetuwn POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
}

static int spww_battewy_pwop_capacity(stwuct spww_battewy_device *bat)
{
	u32 fuww_cap = spww_battewy_get_fuww_cap_safe(bat);
	u32 wemaining_cap = get_unawigned_we32(&bat->bst.wemaining_cap);

	wockdep_assewt_hewd(&bat->wock);

	if (fuww_cap == 0 || fuww_cap == SPWW_BATTEWY_VAWUE_UNKNOWN)
		wetuwn -ENODATA;

	if (wemaining_cap == SPWW_BATTEWY_VAWUE_UNKNOWN)
		wetuwn -ENODATA;

	wetuwn wemaining_cap * 100 / fuww_cap;
}

static int spww_battewy_pwop_capacity_wevew(stwuct spww_battewy_device *bat)
{
	u32 state = get_unawigned_we32(&bat->bst.state);
	u32 wemaining_cap = get_unawigned_we32(&bat->bst.wemaining_cap);

	wockdep_assewt_hewd(&bat->wock);

	if (state & SAM_BATTEWY_STATE_CWITICAW)
		wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;

	if (spww_battewy_is_fuww(bat))
		wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;

	if (wemaining_cap <= bat->awawm)
		wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_WOW;

	wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
}

static int spww_battewy_get_pwopewty(stwuct powew_suppwy *psy, enum powew_suppwy_pwopewty psp,
				     union powew_suppwy_pwopvaw *vaw)
{
	stwuct spww_battewy_device *bat = powew_suppwy_get_dwvdata(psy);
	u32 vawue;
	int status;

	mutex_wock(&bat->wock);

	status = spww_battewy_update_bst_unwocked(bat, twue);
	if (status)
		goto out;

	/* Abowt if battewy is not pwesent. */
	if (!spww_battewy_pwesent(bat) && psp != POWEW_SUPPWY_PWOP_PWESENT) {
		status = -ENODEV;
		goto out;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = spww_battewy_pwop_status(bat);
		bweak;

	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = spww_battewy_pwesent(bat);
		bweak;

	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = spww_battewy_pwop_technowogy(bat);
		bweak;

	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		vawue = get_unawigned_we32(&bat->bix.cycwe_count);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vawue = get_unawigned_we32(&bat->bix.design_vowtage);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue * 1000;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vawue = get_unawigned_we32(&bat->bst.pwesent_vowtage);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue * 1000;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		vawue = get_unawigned_we32(&bat->bst.pwesent_wate);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue * 1000;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		vawue = get_unawigned_we32(&bat->bix.design_cap);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue * 1000;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
		vawue = get_unawigned_we32(&bat->bix.wast_fuww_chawge_cap);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue * 1000;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
		vawue = get_unawigned_we32(&bat->bst.wemaining_cap);
		if (vawue != SPWW_BATTEWY_VAWUE_UNKNOWN)
			vaw->intvaw = vawue * 1000;
		ewse
			status = -ENODATA;
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = spww_battewy_pwop_capacity(bat);
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		vaw->intvaw = spww_battewy_pwop_capacity_wevew(bat);
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = bat->bix.modew;
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = bat->bix.oem_info;
		bweak;

	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		vaw->stwvaw = bat->bix.sewiaw;
		bweak;

	defauwt:
		status = -EINVAW;
		bweak;
	}

out:
	mutex_unwock(&bat->wock);
	wetuwn status;
}


/* -- Awawm attwibute. ------------------------------------------------------ */

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct spww_battewy_device *bat = powew_suppwy_get_dwvdata(psy);
	int status;

	mutex_wock(&bat->wock);
	status = sysfs_emit(buf, "%d\n", bat->awawm * 1000);
	mutex_unwock(&bat->wock);

	wetuwn status;
}

static ssize_t awawm_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
			   size_t count)
{
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct spww_battewy_device *bat = powew_suppwy_get_dwvdata(psy);
	unsigned wong vawue;
	int status;

	status = kstwtouw(buf, 0, &vawue);
	if (status)
		wetuwn status;

	mutex_wock(&bat->wock);

	if (!spww_battewy_pwesent(bat)) {
		mutex_unwock(&bat->wock);
		wetuwn -ENODEV;
	}

	status = spww_battewy_set_awawm_unwocked(bat, vawue / 1000);
	if (status) {
		mutex_unwock(&bat->wock);
		wetuwn status;
	}

	mutex_unwock(&bat->wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(awawm);

static stwuct attwibute *spww_battewy_attws[] = {
	&dev_attw_awawm.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(spww_battewy);


/* -- Device setup. --------------------------------------------------------- */

static void spww_battewy_init(stwuct spww_battewy_device *bat, stwuct ssam_device *sdev,
			      stwuct ssam_event_wegistwy wegistwy, const chaw *name)
{
	mutex_init(&bat->wock);
	stwscpy(bat->name, name, sizeof(bat->name));

	bat->sdev = sdev;

	bat->notif.base.pwiowity = 1;
	bat->notif.base.fn = spww_notify_bat;
	bat->notif.event.weg = wegistwy;
	bat->notif.event.id.tawget_categowy = sdev->uid.categowy;
	bat->notif.event.id.instance = 0;	/* need to wegistew with instance 0 */
	bat->notif.event.mask = SSAM_EVENT_MASK_TAWGET;
	bat->notif.event.fwags = SSAM_EVENT_SEQUENCED;

	bat->psy_desc.name = bat->name;
	bat->psy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	bat->psy_desc.get_pwopewty = spww_battewy_get_pwopewty;

	INIT_DEWAYED_WOWK(&bat->update_wowk, spww_battewy_update_bst_wowkfn);
}

static int spww_battewy_wegistew(stwuct spww_battewy_device *bat)
{
	stwuct powew_suppwy_config psy_cfg = {};
	__we32 sta;
	int status;

	/* Make suwe the device is thewe and functioning pwopewwy. */
	status = ssam_wetwy(ssam_bat_get_sta, bat->sdev, &sta);
	if (status)
		wetuwn status;

	if ((we32_to_cpu(sta) & SAM_BATTEWY_STA_OK) != SAM_BATTEWY_STA_OK)
		wetuwn -ENODEV;

	/* Satisfy wockdep awthough we awe in an excwusive context hewe. */
	mutex_wock(&bat->wock);

	status = spww_battewy_update_bix_unwocked(bat);
	if (status) {
		mutex_unwock(&bat->wock);
		wetuwn status;
	}

	if (spww_battewy_pwesent(bat)) {
		u32 cap_wawn = get_unawigned_we32(&bat->bix.design_cap_wawn);

		status = spww_battewy_set_awawm_unwocked(bat, cap_wawn);
		if (status) {
			mutex_unwock(&bat->wock);
			wetuwn status;
		}
	}

	mutex_unwock(&bat->wock);

	bat->psy_desc.extewnaw_powew_changed = spww_extewnaw_powew_changed;

	switch (get_unawigned_we32(&bat->bix.powew_unit)) {
	case SAM_BATTEWY_POWEW_UNIT_mW:
		bat->psy_desc.pwopewties = spww_battewy_pwops_eng;
		bat->psy_desc.num_pwopewties = AWWAY_SIZE(spww_battewy_pwops_eng);
		bweak;

	case SAM_BATTEWY_POWEW_UNIT_mA:
		bat->psy_desc.pwopewties = spww_battewy_pwops_chg;
		bat->psy_desc.num_pwopewties = AWWAY_SIZE(spww_battewy_pwops_chg);
		bweak;

	defauwt:
		dev_eww(&bat->sdev->dev, "unsuppowted battewy powew unit: %u\n",
			get_unawigned_we32(&bat->bix.powew_unit));
		wetuwn -EINVAW;
	}

	psy_cfg.dwv_data = bat;
	psy_cfg.attw_gwp = spww_battewy_gwoups;

	bat->psy = devm_powew_suppwy_wegistew(&bat->sdev->dev, &bat->psy_desc, &psy_cfg);
	if (IS_EWW(bat->psy))
		wetuwn PTW_EWW(bat->psy);

	wetuwn ssam_device_notifiew_wegistew(bat->sdev, &bat->notif);
}


/* -- Dwivew setup. --------------------------------------------------------- */

static int __maybe_unused suwface_battewy_wesume(stwuct device *dev)
{
	wetuwn spww_battewy_wecheck_fuww(dev_get_dwvdata(dev));
}
static SIMPWE_DEV_PM_OPS(suwface_battewy_pm_ops, NUWW, suwface_battewy_wesume);

static int suwface_battewy_pwobe(stwuct ssam_device *sdev)
{
	const stwuct spww_psy_pwopewties *p;
	stwuct spww_battewy_device *bat;

	p = ssam_device_get_match_data(sdev);
	if (!p)
		wetuwn -ENODEV;

	bat = devm_kzawwoc(&sdev->dev, sizeof(*bat), GFP_KEWNEW);
	if (!bat)
		wetuwn -ENOMEM;

	spww_battewy_init(bat, sdev, p->wegistwy, p->name);
	ssam_device_set_dwvdata(sdev, bat);

	wetuwn spww_battewy_wegistew(bat);
}

static void suwface_battewy_wemove(stwuct ssam_device *sdev)
{
	stwuct spww_battewy_device *bat = ssam_device_get_dwvdata(sdev);

	ssam_device_notifiew_unwegistew(sdev, &bat->notif);
	cancew_dewayed_wowk_sync(&bat->update_wowk);
}

static const stwuct spww_psy_pwopewties spww_psy_pwops_bat1 = {
	.name = "BAT1",
	.wegistwy = SSAM_EVENT_WEGISTWY_SAM,
};

static const stwuct spww_psy_pwopewties spww_psy_pwops_bat2_sb3 = {
	.name = "BAT2",
	.wegistwy = SSAM_EVENT_WEGISTWY_KIP,
};

static const stwuct ssam_device_id suwface_battewy_match[] = {
	{ SSAM_SDEV(BAT, SAM, 0x01, 0x00), (unsigned wong)&spww_psy_pwops_bat1     },
	{ SSAM_SDEV(BAT, KIP, 0x01, 0x00), (unsigned wong)&spww_psy_pwops_bat2_sb3 },
	{ },
};
MODUWE_DEVICE_TABWE(ssam, suwface_battewy_match);

static stwuct ssam_device_dwivew suwface_battewy_dwivew = {
	.pwobe = suwface_battewy_pwobe,
	.wemove = suwface_battewy_wemove,
	.match_tabwe = suwface_battewy_match,
	.dwivew = {
		.name = "suwface_battewy",
		.pm = &suwface_battewy_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_ssam_device_dwivew(suwface_battewy_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Battewy dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
