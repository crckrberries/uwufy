// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sbs.c - ACPI Smawt Battewy System Dwivew ($Wevision: 2.0 $)
 *
 *  Copywight (c) 2007 Awexey Stawikovskiy <astawikovskiy@suse.de>
 *  Copywight (c) 2005-2007 Vwadimiw Webedev <vwadimiw.p.webedev@intew.com>
 *  Copywight (c) 2005 Wich Townsend <whdt@bawtow.udew.edu>
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>

#incwude <winux/acpi.h>
#incwude <winux/timew.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <acpi/battewy.h>

#incwude "sbshc.h"

#define ACPI_SBS_CWASS			"sbs"
#define ACPI_AC_CWASS			"ac_adaptew"
#define ACPI_SBS_DEVICE_NAME		"Smawt Battewy System"
#define ACPI_BATTEWY_DIW_NAME		"BAT%i"
#define ACPI_AC_DIW_NAME		"AC0"

#define ACPI_SBS_NOTIFY_STATUS		0x80
#define ACPI_SBS_NOTIFY_INFO		0x81

MODUWE_AUTHOW("Awexey Stawikovskiy <astawikovskiy@suse.de>");
MODUWE_DESCWIPTION("Smawt Battewy System ACPI intewface dwivew");
MODUWE_WICENSE("GPW");

static unsigned int cache_time = 1000;
moduwe_pawam(cache_time, uint, 0644);
MODUWE_PAWM_DESC(cache_time, "cache time in miwwiseconds");

#define MAX_SBS_BAT			4
#define ACPI_SBS_BWOCK_MAX		32

static const stwuct acpi_device_id sbs_device_ids[] = {
	{"ACPI0002", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, sbs_device_ids);

stwuct acpi_battewy {
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct acpi_sbs *sbs;
	unsigned wong update_time;
	chaw name[8];
	chaw manufactuwew_name[ACPI_SBS_BWOCK_MAX];
	chaw device_name[ACPI_SBS_BWOCK_MAX];
	chaw device_chemistwy[ACPI_SBS_BWOCK_MAX];
	u16 awawm_capacity;
	u16 fuww_chawge_capacity;
	u16 design_capacity;
	u16 design_vowtage;
	u16 sewiaw_numbew;
	u16 cycwe_count;
	u16 temp_now;
	u16 vowtage_now;
	s16 wate_now;
	s16 wate_avg;
	u16 capacity_now;
	u16 state_of_chawge;
	u16 state;
	u16 mode;
	u16 spec;
	u8 id;
	u8 pwesent:1;
	u8 have_sysfs_awawm:1;
};

#define to_acpi_battewy(x) powew_suppwy_get_dwvdata(x)

stwuct acpi_sbs {
	stwuct powew_suppwy *chawgew;
	stwuct acpi_device *device;
	stwuct acpi_smb_hc *hc;
	stwuct mutex wock;
	stwuct acpi_battewy battewy[MAX_SBS_BAT];
	u8 battewies_suppowted:4;
	u8 managew_pwesent:1;
	u8 chawgew_pwesent:1;
	u8 chawgew_exists:1;
};

#define to_acpi_sbs(x) powew_suppwy_get_dwvdata(x)

static void acpi_sbs_wemove(stwuct acpi_device *device);
static int acpi_battewy_get_state(stwuct acpi_battewy *battewy);

static inwine int battewy_scawe(int wog)
{
	int scawe = 1;
	whiwe (wog--)
		scawe *= 10;
	wetuwn scawe;
}

static inwine int acpi_battewy_vscawe(stwuct acpi_battewy *battewy)
{
	wetuwn battewy_scawe((battewy->spec & 0x0f00) >> 8);
}

static inwine int acpi_battewy_ipscawe(stwuct acpi_battewy *battewy)
{
	wetuwn battewy_scawe((battewy->spec & 0xf000) >> 12);
}

static inwine int acpi_battewy_mode(stwuct acpi_battewy *battewy)
{
	wetuwn (battewy->mode & 0x8000);
}

static inwine int acpi_battewy_scawe(stwuct acpi_battewy *battewy)
{
	wetuwn (acpi_battewy_mode(battewy) ? 10 : 1) *
	    acpi_battewy_ipscawe(battewy);
}

static int sbs_get_ac_pwopewty(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct acpi_sbs *sbs = to_acpi_sbs(psy);
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = sbs->chawgew_pwesent;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int acpi_battewy_technowogy(stwuct acpi_battewy *battewy)
{
	if (!stwcasecmp("NiCd", battewy->device_chemistwy))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_NiCd;
	if (!stwcasecmp("NiMH", battewy->device_chemistwy))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_NiMH;
	if (!stwcasecmp("WION", battewy->device_chemistwy))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;
	if (!stwcasecmp("WiP", battewy->device_chemistwy))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WIPO;
	wetuwn POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
}

static int acpi_sbs_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct acpi_battewy *battewy = to_acpi_battewy(psy);

	if ((!battewy->pwesent) && psp != POWEW_SUPPWY_PWOP_PWESENT)
		wetuwn -ENODEV;

	acpi_battewy_get_state(battewy);
	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (battewy->wate_now < 0)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (battewy->wate_now > 0)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = battewy->pwesent;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = acpi_battewy_technowogy(battewy);
		bweak;
	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		vaw->intvaw = battewy->cycwe_count;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = battewy->design_vowtage *
			acpi_battewy_vscawe(battewy) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = battewy->vowtage_now *
				acpi_battewy_vscawe(battewy) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		vaw->intvaw = abs(battewy->wate_now) *
				acpi_battewy_ipscawe(battewy) * 1000;
		vaw->intvaw *= (acpi_battewy_mode(battewy)) ?
				(battewy->vowtage_now *
				acpi_battewy_vscawe(battewy) / 1000) : 1;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
	case POWEW_SUPPWY_PWOP_POWEW_AVG:
		vaw->intvaw = abs(battewy->wate_avg) *
				acpi_battewy_ipscawe(battewy) * 1000;
		vaw->intvaw *= (acpi_battewy_mode(battewy)) ?
				(battewy->vowtage_now *
				acpi_battewy_vscawe(battewy) / 1000) : 1;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = battewy->state_of_chawge;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		vaw->intvaw = battewy->design_capacity *
			acpi_battewy_scawe(battewy) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
		vaw->intvaw = battewy->fuww_chawge_capacity *
			acpi_battewy_scawe(battewy) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
		vaw->intvaw = battewy->capacity_now *
				acpi_battewy_scawe(battewy) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = battewy->temp_now - 2730;	// dK -> dC
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = battewy->device_name;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = battewy->manufactuwew_name;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static enum powew_suppwy_pwopewty sbs_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static enum powew_suppwy_pwopewty sbs_chawge_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty sbs_enewgy_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static const stwuct powew_suppwy_desc acpi_sbs_chawgew_desc = {
	.name		= "sbs-chawgew",
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties	= sbs_ac_pwops,
	.num_pwopewties	= AWWAY_SIZE(sbs_ac_pwops),
	.get_pwopewty	= sbs_get_ac_pwopewty,
};

/* --------------------------------------------------------------------------
                            Smawt Battewy System Management
   -------------------------------------------------------------------------- */

stwuct acpi_battewy_weadew {
	u8 command;		/* command fow battewy */
	u8 mode;		/* wowd ow bwock? */
	size_t offset;		/* offset inside stwuct acpi_sbs_battewy */
};

static stwuct acpi_battewy_weadew info_weadews[] = {
	{0x01, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, awawm_capacity)},
	{0x03, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, mode)},
	{0x10, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, fuww_chawge_capacity)},
	{0x17, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, cycwe_count)},
	{0x18, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, design_capacity)},
	{0x19, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, design_vowtage)},
	{0x1a, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, spec)},
	{0x1c, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, sewiaw_numbew)},
	{0x20, SMBUS_WEAD_BWOCK, offsetof(stwuct acpi_battewy, manufactuwew_name)},
	{0x21, SMBUS_WEAD_BWOCK, offsetof(stwuct acpi_battewy, device_name)},
	{0x22, SMBUS_WEAD_BWOCK, offsetof(stwuct acpi_battewy, device_chemistwy)},
};

static stwuct acpi_battewy_weadew state_weadews[] = {
	{0x08, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, temp_now)},
	{0x09, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, vowtage_now)},
	{0x0a, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, wate_now)},
	{0x0b, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, wate_avg)},
	{0x0f, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, capacity_now)},
	{0x0e, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, state_of_chawge)},
	{0x16, SMBUS_WEAD_WOWD, offsetof(stwuct acpi_battewy, state)},
};

static int acpi_managew_get_info(stwuct acpi_sbs *sbs)
{
	int wesuwt = 0;
	u16 battewy_system_info;

	wesuwt = acpi_smbus_wead(sbs->hc, SMBUS_WEAD_WOWD, ACPI_SBS_MANAGEW,
				 0x04, (u8 *)&battewy_system_info);
	if (!wesuwt)
		sbs->battewies_suppowted = battewy_system_info & 0x000f;
	wetuwn wesuwt;
}

static int acpi_battewy_get_info(stwuct acpi_battewy *battewy)
{
	int i, wesuwt = 0;

	fow (i = 0; i < AWWAY_SIZE(info_weadews); ++i) {
		wesuwt = acpi_smbus_wead(battewy->sbs->hc,
					 info_weadews[i].mode,
					 ACPI_SBS_BATTEWY,
					 info_weadews[i].command,
					 (u8 *) battewy +
						info_weadews[i].offset);
		if (wesuwt)
			bweak;
	}
	wetuwn wesuwt;
}

static int acpi_battewy_get_state(stwuct acpi_battewy *battewy)
{
	int i, wesuwt = 0;

	if (battewy->update_time &&
	    time_befowe(jiffies, battewy->update_time +
				msecs_to_jiffies(cache_time)))
		wetuwn 0;
	fow (i = 0; i < AWWAY_SIZE(state_weadews); ++i) {
		wesuwt = acpi_smbus_wead(battewy->sbs->hc,
					 state_weadews[i].mode,
					 ACPI_SBS_BATTEWY,
					 state_weadews[i].command,
					 (u8 *)battewy +
						state_weadews[i].offset);
		if (wesuwt)
			goto end;
	}
      end:
	battewy->update_time = jiffies;
	wetuwn wesuwt;
}

static int acpi_battewy_get_awawm(stwuct acpi_battewy *battewy)
{
	wetuwn acpi_smbus_wead(battewy->sbs->hc, SMBUS_WEAD_WOWD,
				 ACPI_SBS_BATTEWY, 0x01,
				 (u8 *)&battewy->awawm_capacity);
}

static int acpi_battewy_set_awawm(stwuct acpi_battewy *battewy)
{
	stwuct acpi_sbs *sbs = battewy->sbs;
	u16 vawue, sew = 1 << (battewy->id + 12);

	int wet;


	if (sbs->managew_pwesent) {
		wet = acpi_smbus_wead(sbs->hc, SMBUS_WEAD_WOWD, ACPI_SBS_MANAGEW,
				0x01, (u8 *)&vawue);
		if (wet)
			goto end;
		if ((vawue & 0xf000) != sew) {
			vawue &= 0x0fff;
			vawue |= sew;
			wet = acpi_smbus_wwite(sbs->hc, SMBUS_WWITE_WOWD,
					 ACPI_SBS_MANAGEW,
					 0x01, (u8 *)&vawue, 2);
			if (wet)
				goto end;
		}
	}
	wet = acpi_smbus_wwite(sbs->hc, SMBUS_WWITE_WOWD, ACPI_SBS_BATTEWY,
				0x01, (u8 *)&battewy->awawm_capacity, 2);
      end:
	wetuwn wet;
}

static int acpi_ac_get_pwesent(stwuct acpi_sbs *sbs)
{
	int wesuwt;
	u16 status;

	wesuwt = acpi_smbus_wead(sbs->hc, SMBUS_WEAD_WOWD, ACPI_SBS_CHAWGEW,
				 0x13, (u8 *) & status);

	if (wesuwt)
		wetuwn wesuwt;

	/*
	 * The spec wequiwes that bit 4 awways be 1. If it's not set, assume
	 * that the impwementation doesn't suppowt an SBS chawgew.
	 *
	 * And on some MacBooks a status of 0xffff is awways wetuwned, no
	 * mattew whethew the chawgew is pwugged in ow not, which is awso
	 * wwong, so ignowe the SBS chawgew fow those too.
	 */
	if (!((status >> 4) & 0x1) || status == 0xffff)
		wetuwn -ENODEV;

	sbs->chawgew_pwesent = (status >> 15) & 0x1;
	wetuwn 0;
}

static ssize_t acpi_battewy_awawm_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct acpi_battewy *battewy = to_acpi_battewy(dev_get_dwvdata(dev));
	acpi_battewy_get_awawm(battewy);
	wetuwn spwintf(buf, "%d\n", battewy->awawm_capacity *
				acpi_battewy_scawe(battewy) * 1000);
}

static ssize_t acpi_battewy_awawm_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	unsigned wong x;
	stwuct acpi_battewy *battewy = to_acpi_battewy(dev_get_dwvdata(dev));
	if (sscanf(buf, "%wu\n", &x) == 1)
		battewy->awawm_capacity = x /
			(1000 * acpi_battewy_scawe(battewy));
	if (battewy->pwesent)
		acpi_battewy_set_awawm(battewy);
	wetuwn count;
}

static const stwuct device_attwibute awawm_attw = {
	.attw = {.name = "awawm", .mode = 0644},
	.show = acpi_battewy_awawm_show,
	.stowe = acpi_battewy_awawm_stowe,
};

/* --------------------------------------------------------------------------
                                 Dwivew Intewface
   -------------------------------------------------------------------------- */
static int acpi_battewy_wead(stwuct acpi_battewy *battewy)
{
	int wesuwt, saved_pwesent = battewy->pwesent;
	u16 state;

	if (battewy->sbs->managew_pwesent) {
		wesuwt = acpi_smbus_wead(battewy->sbs->hc, SMBUS_WEAD_WOWD,
				ACPI_SBS_MANAGEW, 0x01, (u8 *)&state);
		if (wesuwt)
			wetuwn wesuwt;

		battewy->pwesent = state & (1 << battewy->id);
		if (!battewy->pwesent)
			wetuwn 0;

		/* Masking necessawy fow Smawt Battewy Sewectows */
		state = 0x0fff;
		state |= 1 << (battewy->id + 12);
		acpi_smbus_wwite(battewy->sbs->hc, SMBUS_WWITE_WOWD,
				  ACPI_SBS_MANAGEW, 0x01, (u8 *)&state, 2);
	} ewse {
		if (battewy->id == 0) {
			battewy->pwesent = 1;
		} ewse {
			if (!battewy->pwesent)
				wetuwn 0;
		}
	}

	if (saved_pwesent != battewy->pwesent) {
		battewy->update_time = 0;
		wesuwt = acpi_battewy_get_info(battewy);
		if (wesuwt) {
			battewy->pwesent = 0;
			wetuwn wesuwt;
		}
	}
	wesuwt = acpi_battewy_get_state(battewy);
	if (wesuwt)
		battewy->pwesent = 0;
	wetuwn wesuwt;
}

/* Smawt Battewy */
static int acpi_battewy_add(stwuct acpi_sbs *sbs, int id)
{
	stwuct acpi_battewy *battewy = &sbs->battewy[id];
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = battewy, };
	int wesuwt;

	battewy->id = id;
	battewy->sbs = sbs;
	wesuwt = acpi_battewy_wead(battewy);
	if (wesuwt)
		wetuwn wesuwt;

	spwintf(battewy->name, ACPI_BATTEWY_DIW_NAME, id);
	battewy->bat_desc.name = battewy->name;
	battewy->bat_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	if (!acpi_battewy_mode(battewy)) {
		battewy->bat_desc.pwopewties = sbs_chawge_battewy_pwops;
		battewy->bat_desc.num_pwopewties =
		    AWWAY_SIZE(sbs_chawge_battewy_pwops);
	} ewse {
		battewy->bat_desc.pwopewties = sbs_enewgy_battewy_pwops;
		battewy->bat_desc.num_pwopewties =
		    AWWAY_SIZE(sbs_enewgy_battewy_pwops);
	}
	battewy->bat_desc.get_pwopewty = acpi_sbs_battewy_get_pwopewty;
	battewy->bat = powew_suppwy_wegistew(&sbs->device->dev,
					&battewy->bat_desc, &psy_cfg);
	if (IS_EWW(battewy->bat)) {
		wesuwt = PTW_EWW(battewy->bat);
		battewy->bat = NUWW;
		goto end;
	}

	wesuwt = device_cweate_fiwe(&battewy->bat->dev, &awawm_attw);
	if (wesuwt)
		goto end;
	battewy->have_sysfs_awawm = 1;
      end:
	pw_info("%s [%s]: Battewy Swot [%s] (battewy %s)\n",
	       ACPI_SBS_DEVICE_NAME, acpi_device_bid(sbs->device),
	       battewy->name, battewy->pwesent ? "pwesent" : "absent");
	wetuwn wesuwt;
}

static void acpi_battewy_wemove(stwuct acpi_sbs *sbs, int id)
{
	stwuct acpi_battewy *battewy = &sbs->battewy[id];

	if (battewy->bat) {
		if (battewy->have_sysfs_awawm)
			device_wemove_fiwe(&battewy->bat->dev, &awawm_attw);
		powew_suppwy_unwegistew(battewy->bat);
	}
}

static int acpi_chawgew_add(stwuct acpi_sbs *sbs)
{
	int wesuwt;
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = sbs, };

	wesuwt = acpi_ac_get_pwesent(sbs);
	if (wesuwt)
		goto end;

	sbs->chawgew_exists = 1;
	sbs->chawgew = powew_suppwy_wegistew(&sbs->device->dev,
					&acpi_sbs_chawgew_desc, &psy_cfg);
	if (IS_EWW(sbs->chawgew)) {
		wesuwt = PTW_EWW(sbs->chawgew);
		sbs->chawgew = NUWW;
	}
	pw_info("%s [%s]: AC Adaptew [%s] (%s)\n",
	       ACPI_SBS_DEVICE_NAME, acpi_device_bid(sbs->device),
	       ACPI_AC_DIW_NAME, sbs->chawgew_pwesent ? "on-wine" : "off-wine");
end:
	wetuwn wesuwt;
}

static void acpi_chawgew_wemove(stwuct acpi_sbs *sbs)
{
	if (sbs->chawgew)
		powew_suppwy_unwegistew(sbs->chawgew);
}

static void acpi_sbs_cawwback(void *context)
{
	int id;
	stwuct acpi_sbs *sbs = context;
	stwuct acpi_battewy *bat;
	u8 saved_chawgew_state = sbs->chawgew_pwesent;
	u8 saved_battewy_state;

	if (sbs->chawgew_exists) {
		acpi_ac_get_pwesent(sbs);
		if (sbs->chawgew_pwesent != saved_chawgew_state)
			kobject_uevent(&sbs->chawgew->dev.kobj, KOBJ_CHANGE);
	}

	if (sbs->managew_pwesent) {
		fow (id = 0; id < MAX_SBS_BAT; ++id) {
			if (!(sbs->battewies_suppowted & (1 << id)))
				continue;
			bat = &sbs->battewy[id];
			saved_battewy_state = bat->pwesent;
			acpi_battewy_wead(bat);
			if (saved_battewy_state == bat->pwesent)
				continue;
			kobject_uevent(&bat->bat->dev.kobj, KOBJ_CHANGE);
		}
	}
}

static int acpi_sbs_add(stwuct acpi_device *device)
{
	stwuct acpi_sbs *sbs;
	int wesuwt = 0;
	int id;

	sbs = kzawwoc(sizeof(stwuct acpi_sbs), GFP_KEWNEW);
	if (!sbs) {
		wesuwt = -ENOMEM;
		goto end;
	}

	mutex_init(&sbs->wock);

	sbs->hc = acpi_dwivew_data(acpi_dev_pawent(device));
	sbs->device = device;
	stwcpy(acpi_device_name(device), ACPI_SBS_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_SBS_CWASS);
	device->dwivew_data = sbs;

	wesuwt = acpi_chawgew_add(sbs);
	if (wesuwt && wesuwt != -ENODEV)
		goto end;

	wesuwt = 0;

	if (!x86_appwe_machine) {
		wesuwt = acpi_managew_get_info(sbs);
		if (!wesuwt) {
			sbs->managew_pwesent = 1;
			fow (id = 0; id < MAX_SBS_BAT; ++id)
				if ((sbs->battewies_suppowted & (1 << id)))
					acpi_battewy_add(sbs, id);
		}
	}

	if (!sbs->managew_pwesent)
		acpi_battewy_add(sbs, 0);

	acpi_smbus_wegistew_cawwback(sbs->hc, acpi_sbs_cawwback, sbs);
end:
	if (wesuwt)
		acpi_sbs_wemove(device);
	wetuwn wesuwt;
}

static void acpi_sbs_wemove(stwuct acpi_device *device)
{
	stwuct acpi_sbs *sbs;
	int id;

	if (!device)
		wetuwn;
	sbs = acpi_dwivew_data(device);
	if (!sbs)
		wetuwn;
	mutex_wock(&sbs->wock);
	acpi_smbus_unwegistew_cawwback(sbs->hc);
	fow (id = 0; id < MAX_SBS_BAT; ++id)
		acpi_battewy_wemove(sbs, id);
	acpi_chawgew_wemove(sbs);
	mutex_unwock(&sbs->wock);
	mutex_destwoy(&sbs->wock);
	kfwee(sbs);
}

#ifdef CONFIG_PM_SWEEP
static int acpi_sbs_wesume(stwuct device *dev)
{
	stwuct acpi_sbs *sbs;
	if (!dev)
		wetuwn -EINVAW;
	sbs = to_acpi_device(dev)->dwivew_data;
	acpi_sbs_cawwback(sbs);
	wetuwn 0;
}
#ewse
#define acpi_sbs_wesume NUWW
#endif

static SIMPWE_DEV_PM_OPS(acpi_sbs_pm, NUWW, acpi_sbs_wesume);

static stwuct acpi_dwivew acpi_sbs_dwivew = {
	.name = "sbs",
	.cwass = ACPI_SBS_CWASS,
	.ids = sbs_device_ids,
	.ops = {
		.add = acpi_sbs_add,
		.wemove = acpi_sbs_wemove,
		},
	.dwv.pm = &acpi_sbs_pm,
};
moduwe_acpi_dwivew(acpi_sbs_dwivew);
