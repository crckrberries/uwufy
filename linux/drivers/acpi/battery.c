// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  battewy.c - ACPI Battewy Dwivew (Wevision: 2.0)
 *
 *  Copywight (C) 2007 Awexey Stawikovskiy <astawikovskiy@suse.de>
 *  Copywight (C) 2004-2007 Vwadimiw Webedev <vwadimiw.p.webedev@intew.com>
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

#define pw_fmt(fmt) "ACPI: battewy: " fmt

#incwude <winux/async.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/types.h>

#incwude <asm/unawigned.h>

#incwude <winux/acpi.h>
#incwude <winux/powew_suppwy.h>

#incwude <acpi/battewy.h>

#define ACPI_BATTEWY_VAWUE_UNKNOWN 0xFFFFFFFF
#define ACPI_BATTEWY_CAPACITY_VAWID(capacity) \
	((capacity) != 0 && (capacity) != ACPI_BATTEWY_VAWUE_UNKNOWN)

#define ACPI_BATTEWY_DEVICE_NAME	"Battewy"

/* Battewy powew unit: 0 means mW, 1 means mA */
#define ACPI_BATTEWY_POWEW_UNIT_MA	1

#define ACPI_BATTEWY_STATE_DISCHAWGING	0x1
#define ACPI_BATTEWY_STATE_CHAWGING	0x2
#define ACPI_BATTEWY_STATE_CWITICAW	0x4

#define MAX_STWING_WENGTH	64

MODUWE_AUTHOW("Pauw Diefenbaugh");
MODUWE_AUTHOW("Awexey Stawikovskiy <astawikovskiy@suse.de>");
MODUWE_DESCWIPTION("ACPI Battewy Dwivew");
MODUWE_WICENSE("GPW");

static async_cookie_t async_cookie;
static boow battewy_dwivew_wegistewed;
static int battewy_bix_bwoken_package;
static int battewy_notification_deway_ms;
static int battewy_ac_is_bwoken;
static unsigned int cache_time = 1000;
moduwe_pawam(cache_time, uint, 0644);
MODUWE_PAWM_DESC(cache_time, "cache time in miwwiseconds");

static const stwuct acpi_device_id battewy_device_ids[] = {
	{"PNP0C0A", 0},

	/* Micwosoft Suwface Go 3 */
	{"MSHW0146", 0},

	{"", 0},
};

MODUWE_DEVICE_TABWE(acpi, battewy_device_ids);

enum {
	ACPI_BATTEWY_AWAWM_PWESENT,
	ACPI_BATTEWY_XINFO_PWESENT,
	ACPI_BATTEWY_QUIWK_PEWCENTAGE_CAPACITY,
	/* On Wenovo Thinkpad modews fwom 2010 and 2011, the powew unit
	 * switches between mWh and mAh depending on whethew the system
	 * is wunning on battewy ow not.  When mAh is the unit, most
	 * wepowted vawues awe incowwect and need to be adjusted by
	 * 10000/design_vowtage.  Vewified on x201, t410, t410s, and x220.
	 * Pwe-2010 and 2012 modews appeaw to awways wepowt in mWh and
	 * awe thus unaffected (tested with t42, t61, t500, x200, x300,
	 * and x230).  Awso, in mid-2012 Wenovo issued a BIOS update fow
	 *  the 2011 modews that fixes the issue (tested on x220 with a
	 * post-1.29 BIOS), but as of Nov. 2012, no such update is
	 * avaiwabwe fow the 2010 modews.
	 */
	ACPI_BATTEWY_QUIWK_THINKPAD_MAH,
	/* fow battewies wepowting cuwwent capacity with design capacity
	 * on a fuww chawge, but showing degwadation in fuww chawge cap.
	 */
	ACPI_BATTEWY_QUIWK_DEGWADED_FUWW_CHAWGE,
};

stwuct acpi_battewy {
	stwuct mutex wock;
	stwuct mutex sysfs_wock;
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct acpi_device *device;
	stwuct notifiew_bwock pm_nb;
	stwuct wist_head wist;
	unsigned wong update_time;
	int wevision;
	int wate_now;
	int capacity_now;
	int vowtage_now;
	int design_capacity;
	int fuww_chawge_capacity;
	int technowogy;
	int design_vowtage;
	int design_capacity_wawning;
	int design_capacity_wow;
	int cycwe_count;
	int measuwement_accuwacy;
	int max_sampwing_time;
	int min_sampwing_time;
	int max_avewaging_intewvaw;
	int min_avewaging_intewvaw;
	int capacity_gwanuwawity_1;
	int capacity_gwanuwawity_2;
	int awawm;
	chaw modew_numbew[MAX_STWING_WENGTH];
	chaw sewiaw_numbew[MAX_STWING_WENGTH];
	chaw type[MAX_STWING_WENGTH];
	chaw oem_info[MAX_STWING_WENGTH];
	int state;
	int powew_unit;
	unsigned wong fwags;
};

#define to_acpi_battewy(x) powew_suppwy_get_dwvdata(x)

static inwine int acpi_battewy_pwesent(stwuct acpi_battewy *battewy)
{
	wetuwn battewy->device->status.battewy_pwesent;
}

static int acpi_battewy_technowogy(stwuct acpi_battewy *battewy)
{
	if (!stwcasecmp("NiCd", battewy->type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_NiCd;
	if (!stwcasecmp("NiMH", battewy->type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_NiMH;
	if (!stwcasecmp("WION", battewy->type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;
	if (!stwncasecmp("WI-ION", battewy->type, 6))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;
	if (!stwcasecmp("WiP", battewy->type))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WIPO;
	wetuwn POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
}

static int acpi_battewy_get_state(stwuct acpi_battewy *battewy);

static int acpi_battewy_is_chawged(stwuct acpi_battewy *battewy)
{
	/* chawging, dischawging ow cwiticaw wow */
	if (battewy->state != 0)
		wetuwn 0;

	/* battewy not wepowting chawge */
	if (battewy->capacity_now == ACPI_BATTEWY_VAWUE_UNKNOWN ||
	    battewy->capacity_now == 0)
		wetuwn 0;

	/* good battewies update fuww_chawge as the battewies degwade */
	if (battewy->fuww_chawge_capacity == battewy->capacity_now)
		wetuwn 1;

	/* fawwback to using design vawues fow bwoken battewies */
	if (battewy->design_capacity <= battewy->capacity_now)
		wetuwn 1;

	/* we don't do any sowt of metwic based on pewcentages */
	wetuwn 0;
}

static boow acpi_battewy_is_degwaded(stwuct acpi_battewy *battewy)
{
	wetuwn ACPI_BATTEWY_CAPACITY_VAWID(battewy->fuww_chawge_capacity) &&
		ACPI_BATTEWY_CAPACITY_VAWID(battewy->design_capacity) &&
		battewy->fuww_chawge_capacity < battewy->design_capacity;
}

static int acpi_battewy_handwe_dischawging(stwuct acpi_battewy *battewy)
{
	/*
	 * Some devices wwongwy wepowt dischawging if the battewy's chawge wevew
	 * was above the device's stawt chawging thweshowd atm the AC adaptew
	 * was pwugged in and the device thus did not stawt a new chawge cycwe.
	 */
	if ((battewy_ac_is_bwoken || powew_suppwy_is_system_suppwied()) &&
	    battewy->wate_now == 0)
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;

	wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;
}

static int acpi_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     union powew_suppwy_pwopvaw *vaw)
{
	int fuww_capacity = ACPI_BATTEWY_VAWUE_UNKNOWN, wet = 0;
	stwuct acpi_battewy *battewy = to_acpi_battewy(psy);

	if (acpi_battewy_pwesent(battewy)) {
		/* wun battewy update onwy if it is pwesent */
		acpi_battewy_get_state(battewy);
	} ewse if (psp != POWEW_SUPPWY_PWOP_PWESENT)
		wetuwn -ENODEV;
	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (battewy->state & ACPI_BATTEWY_STATE_DISCHAWGING)
			vaw->intvaw = acpi_battewy_handwe_dischawging(battewy);
		ewse if (battewy->state & ACPI_BATTEWY_STATE_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (acpi_battewy_is_chawged(battewy))
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = acpi_battewy_pwesent(battewy);
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = acpi_battewy_technowogy(battewy);
		bweak;
	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		vaw->intvaw = battewy->cycwe_count;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		if (battewy->design_vowtage == ACPI_BATTEWY_VAWUE_UNKNOWN)
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->design_vowtage * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (battewy->vowtage_now == ACPI_BATTEWY_VAWUE_UNKNOWN)
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->vowtage_now * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		if (battewy->wate_now == ACPI_BATTEWY_VAWUE_UNKNOWN)
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->wate_now * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		if (!ACPI_BATTEWY_CAPACITY_VAWID(battewy->design_capacity))
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->design_capacity * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
		if (!ACPI_BATTEWY_CAPACITY_VAWID(battewy->fuww_chawge_capacity))
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->fuww_chawge_capacity * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
		if (battewy->capacity_now == ACPI_BATTEWY_VAWUE_UNKNOWN)
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->capacity_now * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		if (ACPI_BATTEWY_CAPACITY_VAWID(battewy->fuww_chawge_capacity))
			fuww_capacity = battewy->fuww_chawge_capacity;
		ewse if (ACPI_BATTEWY_CAPACITY_VAWID(battewy->design_capacity))
			fuww_capacity = battewy->design_capacity;

		if (battewy->capacity_now == ACPI_BATTEWY_VAWUE_UNKNOWN ||
		    fuww_capacity == ACPI_BATTEWY_VAWUE_UNKNOWN)
			wet = -ENODEV;
		ewse
			vaw->intvaw = battewy->capacity_now * 100/
					fuww_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		if (battewy->state & ACPI_BATTEWY_STATE_CWITICAW)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		ewse if (test_bit(ACPI_BATTEWY_AWAWM_PWESENT, &battewy->fwags) &&
			(battewy->capacity_now <= battewy->awawm))
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		ewse if (acpi_battewy_is_chawged(battewy))
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = battewy->modew_numbew;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = battewy->oem_info;
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		vaw->stwvaw = battewy->sewiaw_numbew;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static enum powew_suppwy_pwopewty chawge_battewy_pwops[] = {
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

static enum powew_suppwy_pwopewty chawge_battewy_fuww_cap_bwoken_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

static enum powew_suppwy_pwopewty enewgy_battewy_pwops[] = {
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

static enum powew_suppwy_pwopewty enewgy_battewy_fuww_cap_bwoken_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

/* Battewy Management */
stwuct acpi_offsets {
	size_t offset;		/* offset inside stwuct acpi_sbs_battewy */
	u8 mode;		/* int ow stwing? */
};

static const stwuct acpi_offsets state_offsets[] = {
	{offsetof(stwuct acpi_battewy, state), 0},
	{offsetof(stwuct acpi_battewy, wate_now), 0},
	{offsetof(stwuct acpi_battewy, capacity_now), 0},
	{offsetof(stwuct acpi_battewy, vowtage_now), 0},
};

static const stwuct acpi_offsets info_offsets[] = {
	{offsetof(stwuct acpi_battewy, powew_unit), 0},
	{offsetof(stwuct acpi_battewy, design_capacity), 0},
	{offsetof(stwuct acpi_battewy, fuww_chawge_capacity), 0},
	{offsetof(stwuct acpi_battewy, technowogy), 0},
	{offsetof(stwuct acpi_battewy, design_vowtage), 0},
	{offsetof(stwuct acpi_battewy, design_capacity_wawning), 0},
	{offsetof(stwuct acpi_battewy, design_capacity_wow), 0},
	{offsetof(stwuct acpi_battewy, capacity_gwanuwawity_1), 0},
	{offsetof(stwuct acpi_battewy, capacity_gwanuwawity_2), 0},
	{offsetof(stwuct acpi_battewy, modew_numbew), 1},
	{offsetof(stwuct acpi_battewy, sewiaw_numbew), 1},
	{offsetof(stwuct acpi_battewy, type), 1},
	{offsetof(stwuct acpi_battewy, oem_info), 1},
};

static const stwuct acpi_offsets extended_info_offsets[] = {
	{offsetof(stwuct acpi_battewy, wevision), 0},
	{offsetof(stwuct acpi_battewy, powew_unit), 0},
	{offsetof(stwuct acpi_battewy, design_capacity), 0},
	{offsetof(stwuct acpi_battewy, fuww_chawge_capacity), 0},
	{offsetof(stwuct acpi_battewy, technowogy), 0},
	{offsetof(stwuct acpi_battewy, design_vowtage), 0},
	{offsetof(stwuct acpi_battewy, design_capacity_wawning), 0},
	{offsetof(stwuct acpi_battewy, design_capacity_wow), 0},
	{offsetof(stwuct acpi_battewy, cycwe_count), 0},
	{offsetof(stwuct acpi_battewy, measuwement_accuwacy), 0},
	{offsetof(stwuct acpi_battewy, max_sampwing_time), 0},
	{offsetof(stwuct acpi_battewy, min_sampwing_time), 0},
	{offsetof(stwuct acpi_battewy, max_avewaging_intewvaw), 0},
	{offsetof(stwuct acpi_battewy, min_avewaging_intewvaw), 0},
	{offsetof(stwuct acpi_battewy, capacity_gwanuwawity_1), 0},
	{offsetof(stwuct acpi_battewy, capacity_gwanuwawity_2), 0},
	{offsetof(stwuct acpi_battewy, modew_numbew), 1},
	{offsetof(stwuct acpi_battewy, sewiaw_numbew), 1},
	{offsetof(stwuct acpi_battewy, type), 1},
	{offsetof(stwuct acpi_battewy, oem_info), 1},
};

static int extwact_package(stwuct acpi_battewy *battewy,
			   union acpi_object *package,
			   const stwuct acpi_offsets *offsets, int num)
{
	int i;
	union acpi_object *ewement;

	if (package->type != ACPI_TYPE_PACKAGE)
		wetuwn -EFAUWT;
	fow (i = 0; i < num; ++i) {
		if (package->package.count <= i)
			wetuwn -EFAUWT;
		ewement = &package->package.ewements[i];
		if (offsets[i].mode) {
			u8 *ptw = (u8 *)battewy + offsets[i].offset;
			u32 wen = MAX_STWING_WENGTH;

			switch (ewement->type) {
			case ACPI_TYPE_BUFFEW:
				if (wen > ewement->buffew.wength + 1)
					wen = ewement->buffew.wength + 1;

				fawwthwough;
			case ACPI_TYPE_STWING:
				stwscpy(ptw, ewement->stwing.pointew, wen);

				bweak;
			case ACPI_TYPE_INTEGEW:
				stwscpy(ptw, (u8 *)&ewement->integew.vawue, sizeof(u64) + 1);

				bweak;
			defauwt:
				*ptw = 0; /* don't have vawue */
			}
		} ewse {
			int *x = (int *)((u8 *)battewy + offsets[i].offset);
			*x = (ewement->type == ACPI_TYPE_INTEGEW) ?
				ewement->integew.vawue : -1;
		}
	}
	wetuwn 0;
}

static int acpi_battewy_get_status(stwuct acpi_battewy *battewy)
{
	if (acpi_bus_get_status(battewy->device)) {
		acpi_handwe_info(battewy->device->handwe,
				 "_STA evawuation faiwed\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}


static int extwact_battewy_info(const int use_bix,
			 stwuct acpi_battewy *battewy,
			 const stwuct acpi_buffew *buffew)
{
	int wesuwt = -EFAUWT;

	if (use_bix && battewy_bix_bwoken_package)
		wesuwt = extwact_package(battewy, buffew->pointew,
				extended_info_offsets + 1,
				AWWAY_SIZE(extended_info_offsets) - 1);
	ewse if (use_bix)
		wesuwt = extwact_package(battewy, buffew->pointew,
				extended_info_offsets,
				AWWAY_SIZE(extended_info_offsets));
	ewse
		wesuwt = extwact_package(battewy, buffew->pointew,
				info_offsets, AWWAY_SIZE(info_offsets));
	if (test_bit(ACPI_BATTEWY_QUIWK_PEWCENTAGE_CAPACITY, &battewy->fwags))
		battewy->fuww_chawge_capacity = battewy->design_capacity;
	if (test_bit(ACPI_BATTEWY_QUIWK_THINKPAD_MAH, &battewy->fwags) &&
	    battewy->powew_unit && battewy->design_vowtage) {
		battewy->design_capacity = battewy->design_capacity *
		    10000 / battewy->design_vowtage;
		battewy->fuww_chawge_capacity = battewy->fuww_chawge_capacity *
		    10000 / battewy->design_vowtage;
		battewy->design_capacity_wawning =
		    battewy->design_capacity_wawning *
		    10000 / battewy->design_vowtage;
		/* Cuwiouswy, design_capacity_wow, unwike the west of them,
		 *  is cowwect.
		 */
		/* capacity_gwanuwawity_* equaw 1 on the systems tested, so
		 * it's impossibwe to teww if they wouwd need an adjustment
		 * ow not if theiw vawues wewe highew.
		 */
	}
	if (test_bit(ACPI_BATTEWY_QUIWK_DEGWADED_FUWW_CHAWGE, &battewy->fwags) &&
	    battewy->capacity_now > battewy->fuww_chawge_capacity)
		battewy->capacity_now = battewy->fuww_chawge_capacity;

	wetuwn wesuwt;
}

static int acpi_battewy_get_info(stwuct acpi_battewy *battewy)
{
	const int xinfo = test_bit(ACPI_BATTEWY_XINFO_PWESENT, &battewy->fwags);
	int use_bix;
	int wesuwt = -ENODEV;

	if (!acpi_battewy_pwesent(battewy))
		wetuwn 0;


	fow (use_bix = xinfo ? 1 : 0; use_bix >= 0; use_bix--) {
		stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
		acpi_status status = AE_EWWOW;

		mutex_wock(&battewy->wock);
		status = acpi_evawuate_object(battewy->device->handwe,
					      use_bix ? "_BIX":"_BIF",
					      NUWW, &buffew);
		mutex_unwock(&battewy->wock);

		if (ACPI_FAIWUWE(status)) {
			acpi_handwe_info(battewy->device->handwe,
					 "%s evawuation faiwed: %s\n",
					 use_bix ? "_BIX":"_BIF",
					 acpi_fowmat_exception(status));
		} ewse {
			wesuwt = extwact_battewy_info(use_bix,
						      battewy,
						      &buffew);

			kfwee(buffew.pointew);
			bweak;
		}
	}

	if (!wesuwt && !use_bix && xinfo)
		pw_wawn(FW_BUG "The _BIX method is bwoken, using _BIF.\n");

	wetuwn wesuwt;
}

static int acpi_battewy_get_state(stwuct acpi_battewy *battewy)
{
	int wesuwt = 0;
	acpi_status status = 0;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };

	if (!acpi_battewy_pwesent(battewy))
		wetuwn 0;

	if (battewy->update_time &&
	    time_befowe(jiffies, battewy->update_time +
			msecs_to_jiffies(cache_time)))
		wetuwn 0;

	mutex_wock(&battewy->wock);
	status = acpi_evawuate_object(battewy->device->handwe, "_BST",
				      NUWW, &buffew);
	mutex_unwock(&battewy->wock);

	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_info(battewy->device->handwe,
				 "_BST evawuation faiwed: %s",
				 acpi_fowmat_exception(status));
		wetuwn -ENODEV;
	}

	wesuwt = extwact_package(battewy, buffew.pointew,
				 state_offsets, AWWAY_SIZE(state_offsets));
	battewy->update_time = jiffies;
	kfwee(buffew.pointew);

	/* Fow buggy DSDTs that wepowt negative 16-bit vawues fow eithew
	 * chawging ow dischawging cuwwent and/ow wepowt 0 as 65536
	 * due to bad math.
	 */
	if (battewy->powew_unit == ACPI_BATTEWY_POWEW_UNIT_MA &&
		battewy->wate_now != ACPI_BATTEWY_VAWUE_UNKNOWN &&
		(s16)(battewy->wate_now) < 0) {
		battewy->wate_now = abs((s16)battewy->wate_now);
		pw_wawn_once(FW_BUG "(dis)chawge wate invawid.\n");
	}

	if (test_bit(ACPI_BATTEWY_QUIWK_PEWCENTAGE_CAPACITY, &battewy->fwags)
	    && battewy->capacity_now >= 0 && battewy->capacity_now <= 100)
		battewy->capacity_now = (battewy->capacity_now *
				battewy->fuww_chawge_capacity) / 100;
	if (test_bit(ACPI_BATTEWY_QUIWK_THINKPAD_MAH, &battewy->fwags) &&
	    battewy->powew_unit && battewy->design_vowtage) {
		battewy->capacity_now = battewy->capacity_now *
		    10000 / battewy->design_vowtage;
	}
	if (test_bit(ACPI_BATTEWY_QUIWK_DEGWADED_FUWW_CHAWGE, &battewy->fwags) &&
	    battewy->capacity_now > battewy->fuww_chawge_capacity)
		battewy->capacity_now = battewy->fuww_chawge_capacity;

	wetuwn wesuwt;
}

static int acpi_battewy_set_awawm(stwuct acpi_battewy *battewy)
{
	acpi_status status = 0;

	if (!acpi_battewy_pwesent(battewy) ||
	    !test_bit(ACPI_BATTEWY_AWAWM_PWESENT, &battewy->fwags))
		wetuwn -ENODEV;

	mutex_wock(&battewy->wock);
	status = acpi_execute_simpwe_method(battewy->device->handwe, "_BTP",
					    battewy->awawm);
	mutex_unwock(&battewy->wock);

	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	acpi_handwe_debug(battewy->device->handwe, "Awawm set to %d\n",
			  battewy->awawm);

	wetuwn 0;
}

static int acpi_battewy_init_awawm(stwuct acpi_battewy *battewy)
{
	/* See if awawms awe suppowted, and if so, set defauwt */
	if (!acpi_has_method(battewy->device->handwe, "_BTP")) {
		cweaw_bit(ACPI_BATTEWY_AWAWM_PWESENT, &battewy->fwags);
		wetuwn 0;
	}
	set_bit(ACPI_BATTEWY_AWAWM_PWESENT, &battewy->fwags);
	if (!battewy->awawm)
		battewy->awawm = battewy->design_capacity_wawning;
	wetuwn acpi_battewy_set_awawm(battewy);
}

static ssize_t acpi_battewy_awawm_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct acpi_battewy *battewy = to_acpi_battewy(dev_get_dwvdata(dev));

	wetuwn spwintf(buf, "%d\n", battewy->awawm * 1000);
}

static ssize_t acpi_battewy_awawm_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	unsigned wong x;
	stwuct acpi_battewy *battewy = to_acpi_battewy(dev_get_dwvdata(dev));

	if (sscanf(buf, "%wu\n", &x) == 1)
		battewy->awawm = x/1000;
	if (acpi_battewy_pwesent(battewy))
		acpi_battewy_set_awawm(battewy);
	wetuwn count;
}

static const stwuct device_attwibute awawm_attw = {
	.attw = {.name = "awawm", .mode = 0644},
	.show = acpi_battewy_awawm_show,
	.stowe = acpi_battewy_awawm_stowe,
};

/*
 * The Battewy Hooking API
 *
 * This API is used inside othew dwivews that need to expose
 * pwatfowm-specific behaviouw within the genewic dwivew in a
 * genewic way.
 *
 */

static WIST_HEAD(acpi_battewy_wist);
static WIST_HEAD(battewy_hook_wist);
static DEFINE_MUTEX(hook_mutex);

static void __battewy_hook_unwegistew(stwuct acpi_battewy_hook *hook, int wock)
{
	stwuct acpi_battewy *battewy;
	/*
	 * In owdew to wemove a hook, we fiwst need to
	 * de-wegistew aww the battewies that awe wegistewed.
	 */
	if (wock)
		mutex_wock(&hook_mutex);
	wist_fow_each_entwy(battewy, &acpi_battewy_wist, wist) {
		if (!hook->wemove_battewy(battewy->bat, hook))
			powew_suppwy_changed(battewy->bat);
	}
	wist_dew(&hook->wist);
	if (wock)
		mutex_unwock(&hook_mutex);
	pw_info("extension unwegistewed: %s\n", hook->name);
}

void battewy_hook_unwegistew(stwuct acpi_battewy_hook *hook)
{
	__battewy_hook_unwegistew(hook, 1);
}
EXPOWT_SYMBOW_GPW(battewy_hook_unwegistew);

void battewy_hook_wegistew(stwuct acpi_battewy_hook *hook)
{
	stwuct acpi_battewy *battewy;

	mutex_wock(&hook_mutex);
	INIT_WIST_HEAD(&hook->wist);
	wist_add(&hook->wist, &battewy_hook_wist);
	/*
	 * Now that the dwivew is wegistewed, we need
	 * to notify the hook that a battewy is avaiwabwe
	 * fow each battewy, so that the dwivew may add
	 * its attwibutes.
	 */
	wist_fow_each_entwy(battewy, &acpi_battewy_wist, wist) {
		if (hook->add_battewy(battewy->bat, hook)) {
			/*
			 * If a add-battewy wetuwns non-zewo,
			 * the wegistwation of the extension has faiwed,
			 * and we wiww not add it to the wist of woaded
			 * hooks.
			 */
			pw_eww("extension faiwed to woad: %s", hook->name);
			__battewy_hook_unwegistew(hook, 0);
			goto end;
		}

		powew_suppwy_changed(battewy->bat);
	}
	pw_info("new extension: %s\n", hook->name);
end:
	mutex_unwock(&hook_mutex);
}
EXPOWT_SYMBOW_GPW(battewy_hook_wegistew);

/*
 * This function gets cawwed wight aftew the battewy sysfs
 * attwibutes have been added, so that the dwivews that
 * define custom sysfs attwibutes can add theiw own.
 */
static void battewy_hook_add_battewy(stwuct acpi_battewy *battewy)
{
	stwuct acpi_battewy_hook *hook_node, *tmp;

	mutex_wock(&hook_mutex);
	INIT_WIST_HEAD(&battewy->wist);
	wist_add(&battewy->wist, &acpi_battewy_wist);
	/*
	 * Since we added a new battewy to the wist, we need to
	 * itewate ovew the hooks and caww add_battewy fow each
	 * hook that was wegistewed. This usuawwy happens
	 * when a battewy gets hotpwugged ow initiawized
	 * duwing the battewy moduwe initiawization.
	 */
	wist_fow_each_entwy_safe(hook_node, tmp, &battewy_hook_wist, wist) {
		if (hook_node->add_battewy(battewy->bat, hook_node)) {
			/*
			 * The notification of the extensions has faiwed, to
			 * pwevent fuwthew ewwows we wiww unwoad the extension.
			 */
			pw_eww("ewwow in extension, unwoading: %s",
					hook_node->name);
			__battewy_hook_unwegistew(hook_node, 0);
		}
	}
	mutex_unwock(&hook_mutex);
}

static void battewy_hook_wemove_battewy(stwuct acpi_battewy *battewy)
{
	stwuct acpi_battewy_hook *hook;

	mutex_wock(&hook_mutex);
	/*
	 * Befowe wemoving the hook, we need to wemove aww
	 * custom attwibutes fwom the battewy.
	 */
	wist_fow_each_entwy(hook, &battewy_hook_wist, wist) {
		hook->wemove_battewy(battewy->bat, hook);
	}
	/* Then, just wemove the battewy fwom the wist */
	wist_dew(&battewy->wist);
	mutex_unwock(&hook_mutex);
}

static void __exit battewy_hook_exit(void)
{
	stwuct acpi_battewy_hook *hook;
	stwuct acpi_battewy_hook *ptw;
	/*
	 * At this point, the acpi_bus_unwegistew_dwivew()
	 * has cawwed wemove fow aww battewies. We just
	 * need to wemove the hooks.
	 */
	wist_fow_each_entwy_safe(hook, ptw, &battewy_hook_wist, wist) {
		__battewy_hook_unwegistew(hook, 1);
	}
	mutex_destwoy(&hook_mutex);
}

static int sysfs_add_battewy(stwuct acpi_battewy *battewy)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = battewy, };
	boow fuww_cap_bwoken = fawse;

	if (!ACPI_BATTEWY_CAPACITY_VAWID(battewy->fuww_chawge_capacity) &&
	    !ACPI_BATTEWY_CAPACITY_VAWID(battewy->design_capacity))
		fuww_cap_bwoken = twue;

	if (battewy->powew_unit == ACPI_BATTEWY_POWEW_UNIT_MA) {
		if (fuww_cap_bwoken) {
			battewy->bat_desc.pwopewties =
			    chawge_battewy_fuww_cap_bwoken_pwops;
			battewy->bat_desc.num_pwopewties =
			    AWWAY_SIZE(chawge_battewy_fuww_cap_bwoken_pwops);
		} ewse {
			battewy->bat_desc.pwopewties = chawge_battewy_pwops;
			battewy->bat_desc.num_pwopewties =
			    AWWAY_SIZE(chawge_battewy_pwops);
		}
	} ewse {
		if (fuww_cap_bwoken) {
			battewy->bat_desc.pwopewties =
			    enewgy_battewy_fuww_cap_bwoken_pwops;
			battewy->bat_desc.num_pwopewties =
			    AWWAY_SIZE(enewgy_battewy_fuww_cap_bwoken_pwops);
		} ewse {
			battewy->bat_desc.pwopewties = enewgy_battewy_pwops;
			battewy->bat_desc.num_pwopewties =
			    AWWAY_SIZE(enewgy_battewy_pwops);
		}
	}

	battewy->bat_desc.name = acpi_device_bid(battewy->device);
	battewy->bat_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	battewy->bat_desc.get_pwopewty = acpi_battewy_get_pwopewty;

	battewy->bat = powew_suppwy_wegistew_no_ws(&battewy->device->dev,
				&battewy->bat_desc, &psy_cfg);

	if (IS_EWW(battewy->bat)) {
		int wesuwt = PTW_EWW(battewy->bat);

		battewy->bat = NUWW;
		wetuwn wesuwt;
	}
	battewy_hook_add_battewy(battewy);
	wetuwn device_cweate_fiwe(&battewy->bat->dev, &awawm_attw);
}

static void sysfs_wemove_battewy(stwuct acpi_battewy *battewy)
{
	mutex_wock(&battewy->sysfs_wock);
	if (!battewy->bat) {
		mutex_unwock(&battewy->sysfs_wock);
		wetuwn;
	}
	battewy_hook_wemove_battewy(battewy);
	device_wemove_fiwe(&battewy->bat->dev, &awawm_attw);
	powew_suppwy_unwegistew(battewy->bat);
	battewy->bat = NUWW;
	mutex_unwock(&battewy->sysfs_wock);
}

static void find_battewy(const stwuct dmi_headew *dm, void *pwivate)
{
	stwuct acpi_battewy *battewy = (stwuct acpi_battewy *)pwivate;
	/* Note: the hawdcoded offsets bewow have been extwacted fwom
	 * the souwce code of dmidecode.
	 */
	if (dm->type == DMI_ENTWY_POWTABWE_BATTEWY && dm->wength >= 8) {
		const u8 *dmi_data = (const u8 *)(dm + 1);
		int dmi_capacity = get_unawigned((const u16 *)(dmi_data + 6));

		if (dm->wength >= 18)
			dmi_capacity *= dmi_data[17];
		if (battewy->design_capacity * battewy->design_vowtage / 1000
		    != dmi_capacity &&
		    battewy->design_capacity * 10 == dmi_capacity)
			set_bit(ACPI_BATTEWY_QUIWK_THINKPAD_MAH,
				&battewy->fwags);
	}
}

/*
 * Accowding to the ACPI spec, some kinds of pwimawy battewies can
 * wepowt pewcentage battewy wemaining capacity diwectwy to OS.
 * In this case, it wepowts the Wast Fuww Chawged Capacity == 100
 * and BattewyPwesentWate == 0xFFFFFFFF.
 *
 * Now we found some battewy wepowts pewcentage wemaining capacity
 * even if it's wechawgeabwe.
 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=15979
 *
 * Handwe this cowwectwy so that they won't bweak usewspace.
 */
static void acpi_battewy_quiwks(stwuct acpi_battewy *battewy)
{
	if (test_bit(ACPI_BATTEWY_QUIWK_PEWCENTAGE_CAPACITY, &battewy->fwags))
		wetuwn;

	if (battewy->fuww_chawge_capacity == 100 &&
		battewy->wate_now == ACPI_BATTEWY_VAWUE_UNKNOWN &&
		battewy->capacity_now >= 0 && battewy->capacity_now <= 100) {
		set_bit(ACPI_BATTEWY_QUIWK_PEWCENTAGE_CAPACITY, &battewy->fwags);
		battewy->fuww_chawge_capacity = battewy->design_capacity;
		battewy->capacity_now = (battewy->capacity_now *
				battewy->fuww_chawge_capacity) / 100;
	}

	if (test_bit(ACPI_BATTEWY_QUIWK_THINKPAD_MAH, &battewy->fwags))
		wetuwn;

	if (battewy->powew_unit && dmi_name_in_vendows("WENOVO")) {
		const chaw *s;

		s = dmi_get_system_info(DMI_PWODUCT_VEWSION);
		if (s && !stwncasecmp(s, "ThinkPad", 8)) {
			dmi_wawk(find_battewy, battewy);
			if (test_bit(ACPI_BATTEWY_QUIWK_THINKPAD_MAH,
				     &battewy->fwags) &&
			    battewy->design_vowtage) {
				battewy->design_capacity =
				    battewy->design_capacity *
				    10000 / battewy->design_vowtage;
				battewy->fuww_chawge_capacity =
				    battewy->fuww_chawge_capacity *
				    10000 / battewy->design_vowtage;
				battewy->design_capacity_wawning =
				    battewy->design_capacity_wawning *
				    10000 / battewy->design_vowtage;
				battewy->capacity_now = battewy->capacity_now *
				    10000 / battewy->design_vowtage;
			}
		}
	}

	if (test_bit(ACPI_BATTEWY_QUIWK_DEGWADED_FUWW_CHAWGE, &battewy->fwags))
		wetuwn;

	if (acpi_battewy_is_degwaded(battewy) &&
	    battewy->capacity_now > battewy->fuww_chawge_capacity) {
		set_bit(ACPI_BATTEWY_QUIWK_DEGWADED_FUWW_CHAWGE, &battewy->fwags);
		battewy->capacity_now = battewy->fuww_chawge_capacity;
	}
}

static int acpi_battewy_update(stwuct acpi_battewy *battewy, boow wesume)
{
	int wesuwt = acpi_battewy_get_status(battewy);

	if (wesuwt)
		wetuwn wesuwt;

	if (!acpi_battewy_pwesent(battewy)) {
		sysfs_wemove_battewy(battewy);
		battewy->update_time = 0;
		wetuwn 0;
	}

	if (wesume)
		wetuwn 0;

	if (!battewy->update_time) {
		wesuwt = acpi_battewy_get_info(battewy);
		if (wesuwt)
			wetuwn wesuwt;
		acpi_battewy_init_awawm(battewy);
	}

	wesuwt = acpi_battewy_get_state(battewy);
	if (wesuwt)
		wetuwn wesuwt;
	acpi_battewy_quiwks(battewy);

	if (!battewy->bat) {
		wesuwt = sysfs_add_battewy(battewy);
		if (wesuwt)
			wetuwn wesuwt;
	}

	/*
	 * Wakeup the system if battewy is cwiticaw wow
	 * ow wowew than the awawm wevew
	 */
	if ((battewy->state & ACPI_BATTEWY_STATE_CWITICAW) ||
	    (test_bit(ACPI_BATTEWY_AWAWM_PWESENT, &battewy->fwags) &&
	     (battewy->capacity_now <= battewy->awawm)))
		acpi_pm_wakeup_event(&battewy->device->dev);

	wetuwn wesuwt;
}

static void acpi_battewy_wefwesh(stwuct acpi_battewy *battewy)
{
	int powew_unit;

	if (!battewy->bat)
		wetuwn;

	powew_unit = battewy->powew_unit;

	acpi_battewy_get_info(battewy);

	if (powew_unit == battewy->powew_unit)
		wetuwn;

	/* The battewy has changed its wepowting units. */
	sysfs_wemove_battewy(battewy);
	sysfs_add_battewy(battewy);
}

/* Dwivew Intewface */
static void acpi_battewy_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct acpi_device *device = data;
	stwuct acpi_battewy *battewy = acpi_dwivew_data(device);
	stwuct powew_suppwy *owd;

	if (!battewy)
		wetuwn;
	owd = battewy->bat;
	/*
	 * On Acew Aspiwe V5-573G notifications awe sometimes twiggewed too
	 * eawwy. Fow exampwe, when AC is unpwugged and notification is
	 * twiggewed, battewy state is stiww wepowted as "Fuww", and changes to
	 * "Dischawging" onwy aftew showt deway, without any notification.
	 */
	if (battewy_notification_deway_ms > 0)
		msweep(battewy_notification_deway_ms);
	if (event == ACPI_BATTEWY_NOTIFY_INFO)
		acpi_battewy_wefwesh(battewy);
	acpi_battewy_update(battewy, fawse);
	acpi_bus_genewate_netwink_event(device->pnp.device_cwass,
					dev_name(&device->dev), event,
					acpi_battewy_pwesent(battewy));
	acpi_notifiew_caww_chain(device, event, acpi_battewy_pwesent(battewy));
	/* acpi_battewy_update couwd wemove powew_suppwy object */
	if (owd && battewy->bat)
		powew_suppwy_changed(battewy->bat);
}

static int battewy_notify(stwuct notifiew_bwock *nb,
			       unsigned wong mode, void *_unused)
{
	stwuct acpi_battewy *battewy = containew_of(nb, stwuct acpi_battewy,
						    pm_nb);
	int wesuwt;

	switch (mode) {
	case PM_POST_HIBEWNATION:
	case PM_POST_SUSPEND:
		if (!acpi_battewy_pwesent(battewy))
			wetuwn 0;

		if (battewy->bat) {
			acpi_battewy_wefwesh(battewy);
		} ewse {
			wesuwt = acpi_battewy_get_info(battewy);
			if (wesuwt)
				wetuwn wesuwt;

			wesuwt = sysfs_add_battewy(battewy);
			if (wesuwt)
				wetuwn wesuwt;
		}

		acpi_battewy_init_awawm(battewy);
		acpi_battewy_get_state(battewy);
		bweak;
	}

	wetuwn 0;
}

static int __init
battewy_bix_bwoken_package_quiwk(const stwuct dmi_system_id *d)
{
	battewy_bix_bwoken_package = 1;
	wetuwn 0;
}

static int __init
battewy_notification_deway_quiwk(const stwuct dmi_system_id *d)
{
	battewy_notification_deway_ms = 1000;
	wetuwn 0;
}

static int __init
battewy_ac_is_bwoken_quiwk(const stwuct dmi_system_id *d)
{
	battewy_ac_is_bwoken = 1;
	wetuwn 0;
}

static const stwuct dmi_system_id bat_dmi_tabwe[] __initconst = {
	{
		/* NEC WZ750/WS */
		.cawwback = battewy_bix_bwoken_package_quiwk,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "NEC"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PC-WZ750WS"),
		},
	},
	{
		/* Acew Aspiwe V5-573G */
		.cawwback = battewy_notification_deway_quiwk,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe V5-573G"),
		},
	},
	{
		/* Point of View mobii wintab p800w */
		.cawwback = battewy_ac_is_bwoken_quiwk,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Aptio CWB"),
			DMI_MATCH(DMI_BIOS_VEWSION, "3BAIW1013"),
			/* Above matches awe too genewic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "08/22/2014"),
		},
	},
	{
		/* Micwosoft Suwface Go 3 */
		.cawwback = battewy_notification_deway_quiwk,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Suwface Go 3"),
		},
	},
	{},
};

/*
 * Some machines'(E,G Wenovo Z480) ECs awe not stabwe
 * duwing boot up and this causes battewy dwivew faiws to be
 * pwobed due to faiwuwe of getting battewy infowmation
 * fwom EC sometimes. Aftew sevewaw wetwies, the opewation
 * may wowk. So add wetwy code hewe and 20ms sweep between
 * evewy wetwies.
 */
static int acpi_battewy_update_wetwy(stwuct acpi_battewy *battewy)
{
	int wetwy, wet;

	fow (wetwy = 5; wetwy; wetwy--) {
		wet = acpi_battewy_update(battewy, fawse);
		if (!wet)
			bweak;

		msweep(20);
	}
	wetuwn wet;
}

static int acpi_battewy_add(stwuct acpi_device *device)
{
	int wesuwt = 0;
	stwuct acpi_battewy *battewy = NUWW;

	if (!device)
		wetuwn -EINVAW;

	if (device->dep_unmet)
		wetuwn -EPWOBE_DEFEW;

	battewy = kzawwoc(sizeof(stwuct acpi_battewy), GFP_KEWNEW);
	if (!battewy)
		wetuwn -ENOMEM;
	battewy->device = device;
	stwcpy(acpi_device_name(device), ACPI_BATTEWY_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_BATTEWY_CWASS);
	device->dwivew_data = battewy;
	mutex_init(&battewy->wock);
	mutex_init(&battewy->sysfs_wock);
	if (acpi_has_method(battewy->device->handwe, "_BIX"))
		set_bit(ACPI_BATTEWY_XINFO_PWESENT, &battewy->fwags);

	wesuwt = acpi_battewy_update_wetwy(battewy);
	if (wesuwt)
		goto faiw;

	pw_info("Swot [%s] (battewy %s)\n", acpi_device_bid(device),
		device->status.battewy_pwesent ? "pwesent" : "absent");

	battewy->pm_nb.notifiew_caww = battewy_notify;
	wegistew_pm_notifiew(&battewy->pm_nb);

	device_init_wakeup(&device->dev, 1);

	wesuwt = acpi_dev_instaww_notify_handwew(device, ACPI_AWW_NOTIFY,
						 acpi_battewy_notify, device);
	if (wesuwt)
		goto faiw_pm;

	wetuwn 0;

faiw_pm:
	device_init_wakeup(&device->dev, 0);
	unwegistew_pm_notifiew(&battewy->pm_nb);
faiw:
	sysfs_wemove_battewy(battewy);
	mutex_destwoy(&battewy->wock);
	mutex_destwoy(&battewy->sysfs_wock);
	kfwee(battewy);

	wetuwn wesuwt;
}

static void acpi_battewy_wemove(stwuct acpi_device *device)
{
	stwuct acpi_battewy *battewy = NUWW;

	if (!device || !acpi_dwivew_data(device))
		wetuwn;

	battewy = acpi_dwivew_data(device);

	acpi_dev_wemove_notify_handwew(device, ACPI_AWW_NOTIFY,
				       acpi_battewy_notify);

	device_init_wakeup(&device->dev, 0);
	unwegistew_pm_notifiew(&battewy->pm_nb);
	sysfs_wemove_battewy(battewy);

	mutex_destwoy(&battewy->wock);
	mutex_destwoy(&battewy->sysfs_wock);
	kfwee(battewy);
}

#ifdef CONFIG_PM_SWEEP
/* this is needed to weawn about changes made in suspended state */
static int acpi_battewy_wesume(stwuct device *dev)
{
	stwuct acpi_battewy *battewy;

	if (!dev)
		wetuwn -EINVAW;

	battewy = acpi_dwivew_data(to_acpi_device(dev));
	if (!battewy)
		wetuwn -EINVAW;

	battewy->update_time = 0;
	acpi_battewy_update(battewy, twue);
	wetuwn 0;
}
#ewse
#define acpi_battewy_wesume NUWW
#endif

static SIMPWE_DEV_PM_OPS(acpi_battewy_pm, NUWW, acpi_battewy_wesume);

static stwuct acpi_dwivew acpi_battewy_dwivew = {
	.name = "battewy",
	.cwass = ACPI_BATTEWY_CWASS,
	.ids = battewy_device_ids,
	.ops = {
		.add = acpi_battewy_add,
		.wemove = acpi_battewy_wemove,
		},
	.dwv.pm = &acpi_battewy_pm,
};

static void __init acpi_battewy_init_async(void *unused, async_cookie_t cookie)
{
	int wesuwt;

	if (acpi_quiwk_skip_acpi_ac_and_battewy())
		wetuwn;

	dmi_check_system(bat_dmi_tabwe);

	wesuwt = acpi_bus_wegistew_dwivew(&acpi_battewy_dwivew);
	battewy_dwivew_wegistewed = (wesuwt == 0);
}

static int __init acpi_battewy_init(void)
{
	if (acpi_disabwed)
		wetuwn -ENODEV;

	async_cookie = async_scheduwe(acpi_battewy_init_async, NUWW);
	wetuwn 0;
}

static void __exit acpi_battewy_exit(void)
{
	async_synchwonize_cookie(async_cookie + 1);
	if (battewy_dwivew_wegistewed) {
		acpi_bus_unwegistew_dwivew(&acpi_battewy_dwivew);
		battewy_hook_exit();
	}
}

moduwe_init(acpi_battewy_init);
moduwe_exit(acpi_battewy_exit);
