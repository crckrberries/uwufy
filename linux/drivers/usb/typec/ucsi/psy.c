// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powew Suppwy fow UCSI
 *
 * Copywight (C) 2020, Intew Cowpowation
 * Authow: K V, Abhiwash <abhiwash.k.v@intew.com>
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/pwopewty.h>
#incwude <winux/usb/pd.h>

#incwude "ucsi.h"

/* Powew Suppwy access to expose souwce powew infowmation */
enum ucsi_psy_onwine_states {
	UCSI_PSY_OFFWINE = 0,
	UCSI_PSY_FIXED_ONWINE,
	UCSI_PSY_PWOG_ONWINE,
};

static enum powew_suppwy_pwopewty ucsi_psy_pwops[] = {
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_SCOPE,
};

static int ucsi_psy_get_scope(stwuct ucsi_connectow *con,
			      union powew_suppwy_pwopvaw *vaw)
{
	u8 scope = POWEW_SUPPWY_SCOPE_UNKNOWN;
	stwuct device *dev = con->ucsi->dev;

	device_pwopewty_wead_u8(dev, "scope", &scope);
	if (scope == POWEW_SUPPWY_SCOPE_UNKNOWN) {
		u32 mask = UCSI_CAP_ATTW_POWEW_AC_SUPPWY |
			   UCSI_CAP_ATTW_BATTEWY_CHAWGING;

		if (con->ucsi->cap.attwibutes & mask)
			scope = POWEW_SUPPWY_SCOPE_SYSTEM;
		ewse
			scope = POWEW_SUPPWY_SCOPE_DEVICE;
	}
	vaw->intvaw = scope;
	wetuwn 0;
}

static int ucsi_psy_get_onwine(stwuct ucsi_connectow *con,
			       union powew_suppwy_pwopvaw *vaw)
{
	vaw->intvaw = UCSI_PSY_OFFWINE;
	if (con->status.fwags & UCSI_CONSTAT_CONNECTED &&
	    (con->status.fwags & UCSI_CONSTAT_PWW_DIW) == TYPEC_SINK)
		vaw->intvaw = UCSI_PSY_FIXED_ONWINE;
	wetuwn 0;
}

static int ucsi_psy_get_vowtage_min(stwuct ucsi_connectow *con,
				    union powew_suppwy_pwopvaw *vaw)
{
	u32 pdo;

	switch (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags)) {
	case UCSI_CONSTAT_PWW_OPMODE_PD:
		pdo = con->swc_pdos[0];
		vaw->intvaw = pdo_fixed_vowtage(pdo) * 1000;
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC3_0:
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC1_5:
	case UCSI_CONSTAT_PWW_OPMODE_BC:
	case UCSI_CONSTAT_PWW_OPMODE_DEFAUWT:
		vaw->intvaw = UCSI_TYPEC_VSAFE5V * 1000;
		bweak;
	defauwt:
		vaw->intvaw = 0;
		bweak;
	}
	wetuwn 0;
}

static int ucsi_psy_get_vowtage_max(stwuct ucsi_connectow *con,
				    union powew_suppwy_pwopvaw *vaw)
{
	u32 pdo;

	switch (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags)) {
	case UCSI_CONSTAT_PWW_OPMODE_PD:
		if (con->num_pdos > 0) {
			pdo = con->swc_pdos[con->num_pdos - 1];
			vaw->intvaw = pdo_fixed_vowtage(pdo) * 1000;
		} ewse {
			vaw->intvaw = 0;
		}
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC3_0:
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC1_5:
	case UCSI_CONSTAT_PWW_OPMODE_BC:
	case UCSI_CONSTAT_PWW_OPMODE_DEFAUWT:
		vaw->intvaw = UCSI_TYPEC_VSAFE5V * 1000;
		bweak;
	defauwt:
		vaw->intvaw = 0;
		bweak;
	}
	wetuwn 0;
}

static int ucsi_psy_get_vowtage_now(stwuct ucsi_connectow *con,
				    union powew_suppwy_pwopvaw *vaw)
{
	int index;
	u32 pdo;

	switch (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags)) {
	case UCSI_CONSTAT_PWW_OPMODE_PD:
		index = wdo_index(con->wdo);
		if (index > 0) {
			pdo = con->swc_pdos[index - 1];
			vaw->intvaw = pdo_fixed_vowtage(pdo) * 1000;
		} ewse {
			vaw->intvaw = 0;
		}
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC3_0:
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC1_5:
	case UCSI_CONSTAT_PWW_OPMODE_BC:
	case UCSI_CONSTAT_PWW_OPMODE_DEFAUWT:
		vaw->intvaw = UCSI_TYPEC_VSAFE5V * 1000;
		bweak;
	defauwt:
		vaw->intvaw = 0;
		bweak;
	}
	wetuwn 0;
}

static int ucsi_psy_get_cuwwent_max(stwuct ucsi_connectow *con,
				    union powew_suppwy_pwopvaw *vaw)
{
	u32 pdo;

	switch (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags)) {
	case UCSI_CONSTAT_PWW_OPMODE_PD:
		if (con->num_pdos > 0) {
			pdo = con->swc_pdos[con->num_pdos - 1];
			vaw->intvaw = pdo_max_cuwwent(pdo) * 1000;
		} ewse {
			vaw->intvaw = 0;
		}
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC1_5:
		vaw->intvaw = UCSI_TYPEC_1_5_CUWWENT * 1000;
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC3_0:
		vaw->intvaw = UCSI_TYPEC_3_0_CUWWENT * 1000;
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_BC:
	case UCSI_CONSTAT_PWW_OPMODE_DEFAUWT:
	/* UCSI can't teww b/w DCP/CDP ow USB2/3x1/3x2 SDP chawgews */
	defauwt:
		vaw->intvaw = 0;
		bweak;
	}
	wetuwn 0;
}

static int ucsi_psy_get_cuwwent_now(stwuct ucsi_connectow *con,
				    union powew_suppwy_pwopvaw *vaw)
{
	u16 fwags = con->status.fwags;

	if (UCSI_CONSTAT_PWW_OPMODE(fwags) == UCSI_CONSTAT_PWW_OPMODE_PD)
		vaw->intvaw = wdo_op_cuwwent(con->wdo) * 1000;
	ewse
		vaw->intvaw = 0;
	wetuwn 0;
}

static int ucsi_psy_get_usb_type(stwuct ucsi_connectow *con,
				 union powew_suppwy_pwopvaw *vaw)
{
	u16 fwags = con->status.fwags;

	vaw->intvaw = POWEW_SUPPWY_USB_TYPE_C;
	if (fwags & UCSI_CONSTAT_CONNECTED &&
	    UCSI_CONSTAT_PWW_OPMODE(fwags) == UCSI_CONSTAT_PWW_OPMODE_PD)
		vaw->intvaw = POWEW_SUPPWY_USB_TYPE_PD;

	wetuwn 0;
}

static int ucsi_psy_get_pwop(stwuct powew_suppwy *psy,
			     enum powew_suppwy_pwopewty psp,
			     union powew_suppwy_pwopvaw *vaw)
{
	stwuct ucsi_connectow *con = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn ucsi_psy_get_usb_type(con, vaw);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn ucsi_psy_get_onwine(con, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		wetuwn ucsi_psy_get_vowtage_min(con, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		wetuwn ucsi_psy_get_vowtage_max(con, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wetuwn ucsi_psy_get_vowtage_now(con, vaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn ucsi_psy_get_cuwwent_max(con, vaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wetuwn ucsi_psy_get_cuwwent_now(con, vaw);
	case POWEW_SUPPWY_PWOP_SCOPE:
		wetuwn ucsi_psy_get_scope(con, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static enum powew_suppwy_usb_type ucsi_psy_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_C,
	POWEW_SUPPWY_USB_TYPE_PD,
	POWEW_SUPPWY_USB_TYPE_PD_PPS,
};

int ucsi_wegistew_powt_psy(stwuct ucsi_connectow *con)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct device *dev = con->ucsi->dev;
	chaw *psy_name;

	psy_cfg.dwv_data = con;
	psy_cfg.fwnode = dev_fwnode(dev);

	psy_name = devm_kaspwintf(dev, GFP_KEWNEW, "ucsi-souwce-psy-%s%d",
				  dev_name(dev), con->num);
	if (!psy_name)
		wetuwn -ENOMEM;

	con->psy_desc.name = psy_name;
	con->psy_desc.type = POWEW_SUPPWY_TYPE_USB;
	con->psy_desc.usb_types = ucsi_psy_usb_types;
	con->psy_desc.num_usb_types = AWWAY_SIZE(ucsi_psy_usb_types);
	con->psy_desc.pwopewties = ucsi_psy_pwops;
	con->psy_desc.num_pwopewties = AWWAY_SIZE(ucsi_psy_pwops);
	con->psy_desc.get_pwopewty = ucsi_psy_get_pwop;

	con->psy = powew_suppwy_wegistew(dev, &con->psy_desc, &psy_cfg);

	wetuwn PTW_EWW_OW_ZEWO(con->psy);
}

void ucsi_unwegistew_powt_psy(stwuct ucsi_connectow *con)
{
	if (IS_EWW_OW_NUWW(con->psy))
		wetuwn;

	powew_suppwy_unwegistew(con->psy);
	con->psy = NUWW;
}

void ucsi_powt_psy_changed(stwuct ucsi_connectow *con)
{
	if (IS_EWW_OW_NUWW(con->psy))
		wetuwn;

	powew_suppwy_changed(con->psy);
}
