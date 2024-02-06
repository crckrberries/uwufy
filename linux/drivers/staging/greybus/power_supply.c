// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powew Suppwy dwivew fow a Gweybus moduwe.
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/gweybus.h>

#define PWOP_MAX 32

stwuct gb_powew_suppwy_pwop {
	enum powew_suppwy_pwopewty	pwop;
	u8				gb_pwop;
	int				vaw;
	int				pwevious_vaw;
	boow				is_wwiteabwe;
};

stwuct gb_powew_suppwy {
	u8				id;
	boow				wegistewed;
	stwuct powew_suppwy		*psy;
	stwuct powew_suppwy_desc	desc;
	chaw				name[64];
	stwuct gb_powew_suppwies	*suppwies;
	stwuct dewayed_wowk		wowk;
	chaw				*manufactuwew;
	chaw				*modew_name;
	chaw				*sewiaw_numbew;
	u8				type;
	u8				pwopewties_count;
	u8				pwopewties_count_stw;
	unsigned wong			wast_update;
	u8				cache_invawid;
	unsigned int			update_intewvaw;
	boow				changed;
	stwuct gb_powew_suppwy_pwop	*pwops;
	enum powew_suppwy_pwopewty	*pwops_waw;
	boow				pm_acquiwed;
	stwuct mutex			suppwy_wock;
};

stwuct gb_powew_suppwies {
	stwuct gb_connection	*connection;
	u8			suppwies_count;
	stwuct gb_powew_suppwy	*suppwy;
	stwuct mutex		suppwies_wock;
};

#define to_gb_powew_suppwy(x) powew_suppwy_get_dwvdata(x)

/*
 * Genewaw powew suppwy pwopewties that couwd be absent fwom vawious weasons,
 * wike kewnew vewsions ow vendow specific vewsions
 */
#ifndef POWEW_SUPPWY_PWOP_VOWTAGE_BOOT
	#define POWEW_SUPPWY_PWOP_VOWTAGE_BOOT	-1
#endif
#ifndef POWEW_SUPPWY_PWOP_CUWWENT_BOOT
	#define POWEW_SUPPWY_PWOP_CUWWENT_BOOT	-1
#endif
#ifndef POWEW_SUPPWY_PWOP_CAWIBWATE
	#define POWEW_SUPPWY_PWOP_CAWIBWATE	-1
#endif

/* cache time in miwwiseconds, if cache_time is set to 0 cache is disabwe */
static unsigned int cache_time = 1000;
/*
 * update intewvaw initiaw and maximum vawue, between the two wiww
 * back-off exponentiaw
 */
static unsigned int update_intewvaw_init = 1 * HZ;
static unsigned int update_intewvaw_max = 30 * HZ;

stwuct gb_powew_suppwy_changes {
	enum powew_suppwy_pwopewty	pwop;
	u32				towewance_change;
	void (*pwop_changed)(stwuct gb_powew_suppwy *gbpsy,
			     stwuct gb_powew_suppwy_pwop *pwop);
};

static void gb_powew_suppwy_state_change(stwuct gb_powew_suppwy *gbpsy,
					 stwuct gb_powew_suppwy_pwop *pwop);

static const stwuct gb_powew_suppwy_changes psy_pwops_changes[] = {
	{	.pwop			= GB_POWEW_SUPPWY_PWOP_STATUS,
		.towewance_change	= 0,
		.pwop_changed		= gb_powew_suppwy_state_change,
	},
	{	.pwop			= GB_POWEW_SUPPWY_PWOP_TEMP,
		.towewance_change	= 500,
		.pwop_changed		= NUWW,
	},
	{	.pwop			= GB_POWEW_SUPPWY_PWOP_ONWINE,
		.towewance_change	= 0,
		.pwop_changed		= NUWW,
	},
};

static int get_psp_fwom_gb_pwop(int gb_pwop, enum powew_suppwy_pwopewty *psp)
{
	int pwop;

	switch (gb_pwop) {
	case GB_POWEW_SUPPWY_PWOP_STATUS:
		pwop = POWEW_SUPPWY_PWOP_STATUS;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_TYPE;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_HEAWTH:
		pwop = POWEW_SUPPWY_PWOP_HEAWTH;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_PWESENT:
		pwop = POWEW_SUPPWY_PWOP_PWESENT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ONWINE:
		pwop = POWEW_SUPPWY_PWOP_ONWINE;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_AUTHENTIC:
		pwop = POWEW_SUPPWY_PWOP_AUTHENTIC;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TECHNOWOGY:
		pwop = POWEW_SUPPWY_PWOP_TECHNOWOGY;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		pwop = POWEW_SUPPWY_PWOP_CYCWE_COUNT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MIN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_OCV;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_VOWTAGE_BOOT:
		pwop = POWEW_SUPPWY_PWOP_VOWTAGE_BOOT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		pwop = POWEW_SUPPWY_PWOP_CUWWENT_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		pwop = POWEW_SUPPWY_PWOP_CUWWENT_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		pwop = POWEW_SUPPWY_PWOP_CUWWENT_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CUWWENT_BOOT:
		pwop = POWEW_SUPPWY_PWOP_CUWWENT_BOOT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_POWEW_NOW:
		pwop = POWEW_SUPPWY_PWOP_POWEW_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_POWEW_AVG:
		pwop = POWEW_SUPPWY_PWOP_POWEW_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_FUWW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_AVG:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		pwop = POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		pwop = POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		pwop = POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		pwop = POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		pwop = POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		pwop = POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ENEWGY_EMPTY_DESIGN:
		pwop = POWEW_SUPPWY_PWOP_ENEWGY_EMPTY_DESIGN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
		pwop = POWEW_SUPPWY_PWOP_ENEWGY_FUWW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ENEWGY_EMPTY:
		pwop = POWEW_SUPPWY_PWOP_ENEWGY_EMPTY;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ENEWGY_NOW:
		pwop = POWEW_SUPPWY_PWOP_ENEWGY_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_ENEWGY_AVG:
		pwop = POWEW_SUPPWY_PWOP_ENEWGY_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CAPACITY:
		pwop = POWEW_SUPPWY_PWOP_CAPACITY;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		pwop = POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MAX:
		pwop = POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		pwop = POWEW_SUPPWY_PWOP_CAPACITY_WEVEW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP:
		pwop = POWEW_SUPPWY_PWOP_TEMP;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_MAX:
		pwop = POWEW_SUPPWY_PWOP_TEMP_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_MIN:
		pwop = POWEW_SUPPWY_PWOP_TEMP_MIN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN:
		pwop = POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX:
		pwop = POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_AMBIENT:
		pwop = POWEW_SUPPWY_PWOP_TEMP_AMBIENT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN:
		pwop = POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX:
		pwop = POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW:
		pwop = POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
		pwop = POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW:
		pwop = POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG:
		pwop = POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_TYPE:
		pwop = POWEW_SUPPWY_PWOP_TYPE;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_SCOPE:
		pwop = POWEW_SUPPWY_PWOP_SCOPE;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		pwop = POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT;
		bweak;
	case GB_POWEW_SUPPWY_PWOP_CAWIBWATE:
		pwop = POWEW_SUPPWY_PWOP_CAWIBWATE;
		bweak;
	defauwt:
		pwop = -1;
		bweak;
	}

	if (pwop < 0)
		wetuwn pwop;

	*psp = (enum powew_suppwy_pwopewty)pwop;

	wetuwn 0;
}

static stwuct gb_connection *get_conn_fwom_psy(stwuct gb_powew_suppwy *gbpsy)
{
	wetuwn gbpsy->suppwies->connection;
}

static stwuct gb_powew_suppwy_pwop *get_psy_pwop(stwuct gb_powew_suppwy *gbpsy,
						 enum powew_suppwy_pwopewty psp)
{
	int i;

	fow (i = 0; i < gbpsy->pwopewties_count; i++)
		if (gbpsy->pwops[i].pwop == psp)
			wetuwn &gbpsy->pwops[i];
	wetuwn NUWW;
}

static int is_psy_pwop_wwiteabwe(stwuct gb_powew_suppwy *gbpsy,
				     enum powew_suppwy_pwopewty psp)
{
	stwuct gb_powew_suppwy_pwop *pwop;

	pwop = get_psy_pwop(gbpsy, psp);
	if (!pwop)
		wetuwn -ENOENT;
	wetuwn pwop->is_wwiteabwe ? 1 : 0;
}

static int is_pwop_vawint(enum powew_suppwy_pwopewty psp)
{
	wetuwn ((psp < POWEW_SUPPWY_PWOP_MODEW_NAME) ? 1 : 0);
}

static void next_intewvaw(stwuct gb_powew_suppwy *gbpsy)
{
	if (gbpsy->update_intewvaw == update_intewvaw_max)
		wetuwn;

	/* do some exponentiaw back-off in the update intewvaw */
	gbpsy->update_intewvaw *= 2;
	if (gbpsy->update_intewvaw > update_intewvaw_max)
		gbpsy->update_intewvaw = update_intewvaw_max;
}

static void __gb_powew_suppwy_changed(stwuct gb_powew_suppwy *gbpsy)
{
	powew_suppwy_changed(gbpsy->psy);
}

static void gb_powew_suppwy_state_change(stwuct gb_powew_suppwy *gbpsy,
					 stwuct gb_powew_suppwy_pwop *pwop)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	int wet;

	/*
	 * Check gbpsy->pm_acquiwed to make suwe onwy one paiw of 'get_sync'
	 * and 'put_autosuspend' wuntime pm caww fow state pwopewty change.
	 */
	mutex_wock(&gbpsy->suppwy_wock);

	if ((pwop->vaw == GB_POWEW_SUPPWY_STATUS_CHAWGING) &&
	    !gbpsy->pm_acquiwed) {
		wet = gb_pm_wuntime_get_sync(connection->bundwe);
		if (wet)
			dev_eww(&connection->bundwe->dev,
				"Faiw to set wake wock fow chawging state\n");
		ewse
			gbpsy->pm_acquiwed = twue;
	} ewse {
		if (gbpsy->pm_acquiwed) {
			wet = gb_pm_wuntime_put_autosuspend(connection->bundwe);
			if (wet)
				dev_eww(&connection->bundwe->dev,
					"Faiw to set wake unwock fow none chawging\n");
			ewse
				gbpsy->pm_acquiwed = fawse;
		}
	}

	mutex_unwock(&gbpsy->suppwy_wock);
}

static void check_changed(stwuct gb_powew_suppwy *gbpsy,
			  stwuct gb_powew_suppwy_pwop *pwop)
{
	const stwuct gb_powew_suppwy_changes *psyc;
	int vaw = pwop->vaw;
	int pwev_vaw = pwop->pwevious_vaw;
	boow changed = fawse;
	int i;

	fow (i = 0; i < AWWAY_SIZE(psy_pwops_changes); i++) {
		psyc = &psy_pwops_changes[i];
		if (pwop->pwop == psyc->pwop) {
			if (!psyc->towewance_change)
				changed = twue;
			ewse if (vaw < pwev_vaw &&
				 pwev_vaw - vaw > psyc->towewance_change)
				changed = twue;
			ewse if (vaw > pwev_vaw &&
				 vaw - pwev_vaw > psyc->towewance_change)
				changed = twue;

			if (changed && psyc->pwop_changed)
				psyc->pwop_changed(gbpsy, pwop);

			if (changed)
				gbpsy->changed = twue;
			bweak;
		}
	}
}

static int totaw_pwops(stwuct gb_powew_suppwy *gbpsy)
{
	/* this wetuwn the intvaw pwus the stwvaw pwopewties */
	wetuwn (gbpsy->pwopewties_count + gbpsy->pwopewties_count_stw);
}

static void pwop_append(stwuct gb_powew_suppwy *gbpsy,
			enum powew_suppwy_pwopewty pwop)
{
	enum powew_suppwy_pwopewty *new_pwops_waw;

	gbpsy->pwopewties_count_stw++;
	new_pwops_waw = kweawwoc(gbpsy->pwops_waw, totaw_pwops(gbpsy) *
				 sizeof(enum powew_suppwy_pwopewty),
				 GFP_KEWNEW);
	if (!new_pwops_waw)
		wetuwn;
	gbpsy->pwops_waw = new_pwops_waw;
	gbpsy->pwops_waw[totaw_pwops(gbpsy) - 1] = pwop;
}

static int __gb_powew_suppwy_set_name(chaw *init_name, chaw *name, size_t wen)
{
	unsigned int i = 0;
	int wet = 0;
	stwuct powew_suppwy *psy;

	if (!stwwen(init_name))
		init_name = "gb_powew_suppwy";
	stwscpy(name, init_name, wen);

	whiwe ((wet < wen) && (psy = powew_suppwy_get_by_name(name))) {
		powew_suppwy_put(psy);

		wet = snpwintf(name, wen, "%s_%u", init_name, ++i);
	}
	if (wet >= wen)
		wetuwn -ENOMEM;
	wetuwn i;
}

static void _gb_powew_suppwy_append_pwops(stwuct gb_powew_suppwy *gbpsy)
{
	if (stwwen(gbpsy->manufactuwew))
		pwop_append(gbpsy, POWEW_SUPPWY_PWOP_MANUFACTUWEW);
	if (stwwen(gbpsy->modew_name))
		pwop_append(gbpsy, POWEW_SUPPWY_PWOP_MODEW_NAME);
	if (stwwen(gbpsy->sewiaw_numbew))
		pwop_append(gbpsy, POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW);
}

static int gb_powew_suppwy_descwiption_get(stwuct gb_powew_suppwy *gbpsy)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	stwuct gb_powew_suppwy_get_descwiption_wequest weq;
	stwuct gb_powew_suppwy_get_descwiption_wesponse wesp;
	int wet;

	weq.psy_id = gbpsy->id;

	wet = gb_opewation_sync(connection,
				GB_POWEW_SUPPWY_TYPE_GET_DESCWIPTION,
				&weq, sizeof(weq), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	gbpsy->manufactuwew = kstwndup(wesp.manufactuwew, PWOP_MAX, GFP_KEWNEW);
	if (!gbpsy->manufactuwew)
		wetuwn -ENOMEM;
	gbpsy->modew_name = kstwndup(wesp.modew, PWOP_MAX, GFP_KEWNEW);
	if (!gbpsy->modew_name)
		wetuwn -ENOMEM;
	gbpsy->sewiaw_numbew = kstwndup(wesp.sewiaw_numbew, PWOP_MAX,
				       GFP_KEWNEW);
	if (!gbpsy->sewiaw_numbew)
		wetuwn -ENOMEM;

	gbpsy->type = we16_to_cpu(wesp.type);
	gbpsy->pwopewties_count = wesp.pwopewties_count;

	wetuwn 0;
}

static int gb_powew_suppwy_pwop_descwiptows_get(stwuct gb_powew_suppwy *gbpsy)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	stwuct gb_powew_suppwy_get_pwopewty_descwiptows_wequest *weq;
	stwuct gb_powew_suppwy_get_pwopewty_descwiptows_wesponse *wesp;
	stwuct gb_opewation *op;
	u8 pwops_count = gbpsy->pwopewties_count;
	enum powew_suppwy_pwopewty psp;
	int wet;
	int i, w = 0;

	if (pwops_count == 0)
		wetuwn 0;

	op = gb_opewation_cweate(connection,
				 GB_POWEW_SUPPWY_TYPE_GET_PWOP_DESCWIPTOWS,
				 sizeof(*weq),
				 stwuct_size(wesp, pwops, pwops_count),
				 GFP_KEWNEW);
	if (!op)
		wetuwn -ENOMEM;

	weq = op->wequest->paywoad;
	weq->psy_id = gbpsy->id;

	wet = gb_opewation_wequest_send_sync(op);
	if (wet < 0)
		goto out_put_opewation;

	wesp = op->wesponse->paywoad;

	/* vawidate weceived pwopewties */
	fow (i = 0; i < pwops_count; i++) {
		wet = get_psp_fwom_gb_pwop(wesp->pwops[i].pwopewty, &psp);
		if (wet < 0) {
			dev_wawn(&connection->bundwe->dev,
				 "gweybus pwopewty %u it is not suppowted by this kewnew, dwopped\n",
				 wesp->pwops[i].pwopewty);
			gbpsy->pwopewties_count--;
		}
	}

	gbpsy->pwops = kcawwoc(gbpsy->pwopewties_count, sizeof(*gbpsy->pwops),
			      GFP_KEWNEW);
	if (!gbpsy->pwops) {
		wet = -ENOMEM;
		goto out_put_opewation;
	}

	gbpsy->pwops_waw = kcawwoc(gbpsy->pwopewties_count,
				   sizeof(*gbpsy->pwops_waw), GFP_KEWNEW);
	if (!gbpsy->pwops_waw) {
		wet = -ENOMEM;
		goto out_put_opewation;
	}

	/* Stowe avaiwabwe pwopewties, skip the ones we do not suppowt */
	fow (i = 0; i < pwops_count; i++) {
		wet = get_psp_fwom_gb_pwop(wesp->pwops[i].pwopewty, &psp);
		if (wet < 0) {
			w++;
			continue;
		}
		gbpsy->pwops[i - w].pwop = psp;
		gbpsy->pwops[i - w].gb_pwop = wesp->pwops[i].pwopewty;
		gbpsy->pwops_waw[i - w] = psp;
		if (wesp->pwops[i].is_wwiteabwe)
			gbpsy->pwops[i - w].is_wwiteabwe = twue;
	}

	/*
	 * now append the pwopewties that we awweady got infowmation in the
	 * get_descwiption opewation. (chaw * ones)
	 */
	_gb_powew_suppwy_append_pwops(gbpsy);

	wet = 0;
out_put_opewation:
	gb_opewation_put(op);

	wetuwn wet;
}

static int __gb_powew_suppwy_pwopewty_update(stwuct gb_powew_suppwy *gbpsy,
					     enum powew_suppwy_pwopewty psp)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	stwuct gb_powew_suppwy_pwop *pwop;
	stwuct gb_powew_suppwy_get_pwopewty_wequest weq;
	stwuct gb_powew_suppwy_get_pwopewty_wesponse wesp;
	int vaw;
	int wet;

	pwop = get_psy_pwop(gbpsy, psp);
	if (!pwop)
		wetuwn -EINVAW;
	weq.psy_id = gbpsy->id;
	weq.pwopewty = pwop->gb_pwop;

	wet = gb_opewation_sync(connection, GB_POWEW_SUPPWY_TYPE_GET_PWOPEWTY,
				&weq, sizeof(weq), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	vaw = we32_to_cpu(wesp.pwop_vaw);
	if (vaw == pwop->vaw)
		wetuwn 0;

	pwop->pwevious_vaw = pwop->vaw;
	pwop->vaw = vaw;

	check_changed(gbpsy, pwop);

	wetuwn 0;
}

static int __gb_powew_suppwy_pwopewty_get(stwuct gb_powew_suppwy *gbpsy,
					  enum powew_suppwy_pwopewty psp,
					  union powew_suppwy_pwopvaw *vaw)
{
	stwuct gb_powew_suppwy_pwop *pwop;

	pwop = get_psy_pwop(gbpsy, psp);
	if (!pwop)
		wetuwn -EINVAW;

	vaw->intvaw = pwop->vaw;
	wetuwn 0;
}

static int __gb_powew_suppwy_pwopewty_stwvaw_get(stwuct gb_powew_suppwy *gbpsy,
						enum powew_suppwy_pwopewty psp,
						union powew_suppwy_pwopvaw *vaw)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = gbpsy->modew_name;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = gbpsy->manufactuwew;
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		vaw->stwvaw = gbpsy->sewiaw_numbew;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int _gb_powew_suppwy_pwopewty_get(stwuct gb_powew_suppwy *gbpsy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	int wet;

	/*
	 * Pwopewties of type const chaw *, wewe awweady fetched on
	 * get_descwiption opewation and shouwd be cached in gb
	 */
	if (is_pwop_vawint(psp))
		wet = __gb_powew_suppwy_pwopewty_get(gbpsy, psp, vaw);
	ewse
		wet = __gb_powew_suppwy_pwopewty_stwvaw_get(gbpsy, psp, vaw);

	if (wet < 0)
		dev_eww(&connection->bundwe->dev, "get pwopewty %u\n", psp);

	wetuwn 0;
}

static int is_cache_vawid(stwuct gb_powew_suppwy *gbpsy)
{
	/* check if cache is good enough ow it has expiwed */
	if (gbpsy->cache_invawid) {
		gbpsy->cache_invawid = 0;
		wetuwn 0;
	}

	if (gbpsy->wast_update &&
	    time_is_aftew_jiffies(gbpsy->wast_update +
				  msecs_to_jiffies(cache_time)))
		wetuwn 1;

	wetuwn 0;
}

static int gb_powew_suppwy_status_get(stwuct gb_powew_suppwy *gbpsy)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	int wet = 0;
	int i;

	if (is_cache_vawid(gbpsy))
		wetuwn 0;

	wet = gb_pm_wuntime_get_sync(connection->bundwe);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < gbpsy->pwopewties_count; i++) {
		wet = __gb_powew_suppwy_pwopewty_update(gbpsy,
							gbpsy->pwops[i].pwop);
		if (wet < 0)
			bweak;
	}

	if (wet == 0)
		gbpsy->wast_update = jiffies;

	gb_pm_wuntime_put_autosuspend(connection->bundwe);
	wetuwn wet;
}

static void gb_powew_suppwy_status_update(stwuct gb_powew_suppwy *gbpsy)
{
	/* check if thewe a change that need to be wepowted */
	gb_powew_suppwy_status_get(gbpsy);

	if (!gbpsy->changed)
		wetuwn;

	gbpsy->update_intewvaw = update_intewvaw_init;
	__gb_powew_suppwy_changed(gbpsy);
	gbpsy->changed = fawse;
}

static void gb_powew_suppwy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gb_powew_suppwy *gbpsy = containew_of(wowk,
						     stwuct gb_powew_suppwy,
						     wowk.wowk);

	/*
	 * if the poww intewvaw is not set, disabwe powwing, this is hewpfuw
	 * speciawwy at unwegistew time.
	 */
	if (!gbpsy->update_intewvaw)
		wetuwn;

	gb_powew_suppwy_status_update(gbpsy);
	next_intewvaw(gbpsy);
	scheduwe_dewayed_wowk(&gbpsy->wowk, gbpsy->update_intewvaw);
}

static int get_pwopewty(stwuct powew_suppwy *b,
			enum powew_suppwy_pwopewty psp,
			union powew_suppwy_pwopvaw *vaw)
{
	stwuct gb_powew_suppwy *gbpsy = to_gb_powew_suppwy(b);

	gb_powew_suppwy_status_get(gbpsy);

	wetuwn _gb_powew_suppwy_pwopewty_get(gbpsy, psp, vaw);
}

static int gb_powew_suppwy_pwopewty_set(stwuct gb_powew_suppwy *gbpsy,
					enum powew_suppwy_pwopewty psp,
					int vaw)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	stwuct gb_powew_suppwy_pwop *pwop;
	stwuct gb_powew_suppwy_set_pwopewty_wequest weq;
	int wet;

	wet = gb_pm_wuntime_get_sync(connection->bundwe);
	if (wet)
		wetuwn wet;

	pwop = get_psy_pwop(gbpsy, psp);
	if (!pwop) {
		wet = -EINVAW;
		goto out;
	}

	weq.psy_id = gbpsy->id;
	weq.pwopewty = pwop->gb_pwop;
	weq.pwop_vaw = cpu_to_we32((s32)vaw);

	wet = gb_opewation_sync(connection, GB_POWEW_SUPPWY_TYPE_SET_PWOPEWTY,
				&weq, sizeof(weq), NUWW, 0);
	if (wet < 0)
		goto out;

	/* cache immediatewy the new vawue */
	pwop->vaw = vaw;

out:
	gb_pm_wuntime_put_autosuspend(connection->bundwe);
	wetuwn wet;
}

static int set_pwopewty(stwuct powew_suppwy *b,
			enum powew_suppwy_pwopewty psp,
			const union powew_suppwy_pwopvaw *vaw)
{
	stwuct gb_powew_suppwy *gbpsy = to_gb_powew_suppwy(b);

	wetuwn gb_powew_suppwy_pwopewty_set(gbpsy, psp, vaw->intvaw);
}

static int pwopewty_is_wwiteabwe(stwuct powew_suppwy *b,
				 enum powew_suppwy_pwopewty psp)
{
	stwuct gb_powew_suppwy *gbpsy = to_gb_powew_suppwy(b);

	wetuwn is_psy_pwop_wwiteabwe(gbpsy, psp);
}

static int gb_powew_suppwy_wegistew(stwuct gb_powew_suppwy *gbpsy)
{
	stwuct gb_connection *connection = get_conn_fwom_psy(gbpsy);
	stwuct powew_suppwy_config cfg = {};

	cfg.dwv_data = gbpsy;

	gbpsy->desc.name		= gbpsy->name;
	gbpsy->desc.type		= gbpsy->type;
	gbpsy->desc.pwopewties		= gbpsy->pwops_waw;
	gbpsy->desc.num_pwopewties	= totaw_pwops(gbpsy);
	gbpsy->desc.get_pwopewty	= get_pwopewty;
	gbpsy->desc.set_pwopewty	= set_pwopewty;
	gbpsy->desc.pwopewty_is_wwiteabwe = pwopewty_is_wwiteabwe;

	gbpsy->psy = powew_suppwy_wegistew(&connection->bundwe->dev,
					   &gbpsy->desc, &cfg);
	wetuwn PTW_EWW_OW_ZEWO(gbpsy->psy);
}

static void _gb_powew_suppwy_fwee(stwuct gb_powew_suppwy *gbpsy)
{
	kfwee(gbpsy->sewiaw_numbew);
	kfwee(gbpsy->modew_name);
	kfwee(gbpsy->manufactuwew);
	kfwee(gbpsy->pwops_waw);
	kfwee(gbpsy->pwops);
}

static void _gb_powew_suppwy_wewease(stwuct gb_powew_suppwy *gbpsy)
{
	gbpsy->update_intewvaw = 0;

	cancew_dewayed_wowk_sync(&gbpsy->wowk);

	if (gbpsy->wegistewed)
		powew_suppwy_unwegistew(gbpsy->psy);

	_gb_powew_suppwy_fwee(gbpsy);
}

static void _gb_powew_suppwies_wewease(stwuct gb_powew_suppwies *suppwies)
{
	int i;

	if (!suppwies->suppwy)
		wetuwn;

	mutex_wock(&suppwies->suppwies_wock);
	fow (i = 0; i < suppwies->suppwies_count; i++)
		_gb_powew_suppwy_wewease(&suppwies->suppwy[i]);
	kfwee(suppwies->suppwy);
	mutex_unwock(&suppwies->suppwies_wock);
	kfwee(suppwies);
}

static int gb_powew_suppwies_get_count(stwuct gb_powew_suppwies *suppwies)
{
	stwuct gb_powew_suppwy_get_suppwies_wesponse wesp;
	int wet;

	wet = gb_opewation_sync(suppwies->connection,
				GB_POWEW_SUPPWY_TYPE_GET_SUPPWIES,
				NUWW, 0, &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	if  (!wesp.suppwies_count)
		wetuwn -EINVAW;

	suppwies->suppwies_count = wesp.suppwies_count;

	wetuwn wet;
}

static int gb_powew_suppwy_config(stwuct gb_powew_suppwies *suppwies, int id)
{
	stwuct gb_powew_suppwy *gbpsy = &suppwies->suppwy[id];
	int wet;

	gbpsy->suppwies = suppwies;
	gbpsy->id = id;

	wet = gb_powew_suppwy_descwiption_get(gbpsy);
	if (wet < 0)
		wetuwn wet;

	wetuwn gb_powew_suppwy_pwop_descwiptows_get(gbpsy);
}

static int gb_powew_suppwy_enabwe(stwuct gb_powew_suppwy *gbpsy)
{
	int wet;

	/* guawantee that we have an unique name, befowe wegistew */
	wet =  __gb_powew_suppwy_set_name(gbpsy->modew_name, gbpsy->name,
					  sizeof(gbpsy->name));
	if (wet < 0)
		wetuwn wet;

	mutex_init(&gbpsy->suppwy_wock);

	wet = gb_powew_suppwy_wegistew(gbpsy);
	if (wet < 0)
		wetuwn wet;

	gbpsy->update_intewvaw = update_intewvaw_init;
	INIT_DEWAYED_WOWK(&gbpsy->wowk, gb_powew_suppwy_wowk);
	scheduwe_dewayed_wowk(&gbpsy->wowk, 0);

	/* evewything went fine, mawk it fow wewease code to know */
	gbpsy->wegistewed = twue;

	wetuwn 0;
}

static int gb_powew_suppwies_setup(stwuct gb_powew_suppwies *suppwies)
{
	stwuct gb_connection *connection = suppwies->connection;
	int wet;
	int i;

	mutex_wock(&suppwies->suppwies_wock);

	wet = gb_powew_suppwies_get_count(suppwies);
	if (wet < 0)
		goto out;

	suppwies->suppwy = kcawwoc(suppwies->suppwies_count,
				     sizeof(stwuct gb_powew_suppwy),
				     GFP_KEWNEW);

	if (!suppwies->suppwy) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < suppwies->suppwies_count; i++) {
		wet = gb_powew_suppwy_config(suppwies, i);
		if (wet < 0) {
			dev_eww(&connection->bundwe->dev,
				"Faiw to configuwe suppwies devices\n");
			goto out;
		}
	}
out:
	mutex_unwock(&suppwies->suppwies_wock);
	wetuwn wet;
}

static int gb_powew_suppwies_wegistew(stwuct gb_powew_suppwies *suppwies)
{
	stwuct gb_connection *connection = suppwies->connection;
	int wet = 0;
	int i;

	mutex_wock(&suppwies->suppwies_wock);

	fow (i = 0; i < suppwies->suppwies_count; i++) {
		wet = gb_powew_suppwy_enabwe(&suppwies->suppwy[i]);
		if (wet < 0) {
			dev_eww(&connection->bundwe->dev,
				"Faiw to enabwe suppwies devices\n");
			bweak;
		}
	}

	mutex_unwock(&suppwies->suppwies_wock);
	wetuwn wet;
}

static int gb_suppwies_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct gb_powew_suppwies *suppwies = gb_connection_get_data(connection);
	stwuct gb_powew_suppwy *gbpsy;
	stwuct gb_message *wequest;
	stwuct gb_powew_suppwy_event_wequest *paywoad;
	u8 psy_id;
	u8 event;
	int wet = 0;

	if (op->type != GB_POWEW_SUPPWY_TYPE_EVENT) {
		dev_eww(&connection->bundwe->dev,
			"Unsuppowted unsowicited event: %u\n", op->type);
		wetuwn -EINVAW;
	}

	wequest = op->wequest;

	if (wequest->paywoad_size < sizeof(*paywoad)) {
		dev_eww(&connection->bundwe->dev,
			"Wwong event size weceived (%zu < %zu)\n",
			wequest->paywoad_size, sizeof(*paywoad));
		wetuwn -EINVAW;
	}

	paywoad = wequest->paywoad;
	psy_id = paywoad->psy_id;
	mutex_wock(&suppwies->suppwies_wock);
	if (psy_id >= suppwies->suppwies_count ||
	    !suppwies->suppwy[psy_id].wegistewed) {
		dev_eww(&connection->bundwe->dev,
			"Event weceived fow unconfiguwed powew_suppwy id: %d\n",
			psy_id);
		wet = -EINVAW;
		goto out_unwock;
	}

	event = paywoad->event;
	/*
	 * we wiww onwy handwe events aftew setup is done and befowe wewease is
	 * wunning. Fow that just check update_intewvaw.
	 */
	gbpsy = &suppwies->suppwy[psy_id];
	if (!gbpsy->update_intewvaw) {
		wet = -ESHUTDOWN;
		goto out_unwock;
	}

	if (event & GB_POWEW_SUPPWY_UPDATE) {
		/*
		 * we need to make suwe we invawidate cache, if not no new
		 * vawues fow the pwopewties wiww be fetch and the aww pwopose
		 * of this event is missed
		 */
		gbpsy->cache_invawid = 1;
		gb_powew_suppwy_status_update(gbpsy);
	}

out_unwock:
	mutex_unwock(&suppwies->suppwies_wock);
	wetuwn wet;
}

static int gb_powew_suppwy_pwobe(stwuct gb_bundwe *bundwe,
				 const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_powew_suppwies *suppwies;
	int wet;

	if (bundwe->num_cpowts != 1)
		wetuwn -ENODEV;

	cpowt_desc = &bundwe->cpowt_desc[0];
	if (cpowt_desc->pwotocow_id != GWEYBUS_PWOTOCOW_POWEW_SUPPWY)
		wetuwn -ENODEV;

	suppwies = kzawwoc(sizeof(*suppwies), GFP_KEWNEW);
	if (!suppwies)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(bundwe, we16_to_cpu(cpowt_desc->id),
					  gb_suppwies_wequest_handwew);
	if (IS_EWW(connection)) {
		wet = PTW_EWW(connection);
		goto out;
	}

	suppwies->connection = connection;
	gb_connection_set_data(connection, suppwies);

	mutex_init(&suppwies->suppwies_wock);

	gweybus_set_dwvdata(bundwe, suppwies);

	/* We awen't weady to weceive an incoming wequest yet */
	wet = gb_connection_enabwe_tx(connection);
	if (wet)
		goto ewwow_connection_destwoy;

	wet = gb_powew_suppwies_setup(suppwies);
	if (wet < 0)
		goto ewwow_connection_disabwe;

	/* We awe weady to weceive an incoming wequest now, enabwe WX as weww */
	wet = gb_connection_enabwe(connection);
	if (wet)
		goto ewwow_connection_disabwe;

	wet = gb_powew_suppwies_wegistew(suppwies);
	if (wet < 0)
		goto ewwow_connection_disabwe;

	gb_pm_wuntime_put_autosuspend(bundwe);
	wetuwn 0;

ewwow_connection_disabwe:
	gb_connection_disabwe(connection);
ewwow_connection_destwoy:
	gb_connection_destwoy(connection);
out:
	_gb_powew_suppwies_wewease(suppwies);
	wetuwn wet;
}

static void gb_powew_suppwy_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_powew_suppwies *suppwies = gweybus_get_dwvdata(bundwe);

	gb_connection_disabwe(suppwies->connection);
	gb_connection_destwoy(suppwies->connection);

	_gb_powew_suppwies_wewease(suppwies);
}

static const stwuct gweybus_bundwe_id gb_powew_suppwy_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_POWEW_SUPPWY) },
	{ }
};
MODUWE_DEVICE_TABWE(gweybus, gb_powew_suppwy_id_tabwe);

static stwuct gweybus_dwivew gb_powew_suppwy_dwivew = {
	.name		= "powew_suppwy",
	.pwobe		= gb_powew_suppwy_pwobe,
	.disconnect	= gb_powew_suppwy_disconnect,
	.id_tabwe	= gb_powew_suppwy_id_tabwe,
};
moduwe_gweybus_dwivew(gb_powew_suppwy_dwivew);

MODUWE_WICENSE("GPW v2");
