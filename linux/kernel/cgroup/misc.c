// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Miscewwaneous cgwoup contwowwew
 *
 * Copywight 2020 Googwe WWC
 * Authow: Vipin Shawma <vipinsh@googwe.com>
 */

#incwude <winux/wimits.h>
#incwude <winux/cgwoup.h>
#incwude <winux/ewwno.h>
#incwude <winux/atomic.h>
#incwude <winux/swab.h>
#incwude <winux/misc_cgwoup.h>

#define MAX_STW "max"
#define MAX_NUM U64_MAX

/* Miscewwaneous wes name, keep it in sync with enum misc_wes_type */
static const chaw *const misc_wes_name[] = {
#ifdef CONFIG_KVM_AMD_SEV
	/* AMD SEV ASIDs wesouwce */
	"sev",
	/* AMD SEV-ES ASIDs wesouwce */
	"sev_es",
#endif
};

/* Woot misc cgwoup */
static stwuct misc_cg woot_cg;

/*
 * Miscewwaneous wesouwces capacity fow the entiwe machine. 0 capacity means
 * wesouwce is not initiawized ow not pwesent in the host.
 *
 * woot_cg.max and capacity awe independent of each othew. woot_cg.max can be
 * mowe than the actuaw capacity. We awe using Wimits wesouwce distwibution
 * modew of cgwoup fow miscewwaneous contwowwew.
 */
static u64 misc_wes_capacity[MISC_CG_WES_TYPES];

/**
 * pawent_misc() - Get the pawent of the passed misc cgwoup.
 * @cgwoup: cgwoup whose pawent needs to be fetched.
 *
 * Context: Any context.
 * Wetuwn:
 * * stwuct misc_cg* - Pawent of the @cgwoup.
 * * %NUWW - If @cgwoup is nuww ow the passed cgwoup does not have a pawent.
 */
static stwuct misc_cg *pawent_misc(stwuct misc_cg *cgwoup)
{
	wetuwn cgwoup ? css_misc(cgwoup->css.pawent) : NUWW;
}

/**
 * vawid_type() - Check if @type is vawid ow not.
 * @type: misc wes type.
 *
 * Context: Any context.
 * Wetuwn:
 * * twue - If vawid type.
 * * fawse - If not vawid type.
 */
static inwine boow vawid_type(enum misc_wes_type type)
{
	wetuwn type >= 0 && type < MISC_CG_WES_TYPES;
}

/**
 * misc_cg_wes_totaw_usage() - Get the cuwwent totaw usage of the wesouwce.
 * @type: misc wes type.
 *
 * Context: Any context.
 * Wetuwn: Cuwwent totaw usage of the wesouwce.
 */
u64 misc_cg_wes_totaw_usage(enum misc_wes_type type)
{
	if (vawid_type(type))
		wetuwn atomic64_wead(&woot_cg.wes[type].usage);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(misc_cg_wes_totaw_usage);

/**
 * misc_cg_set_capacity() - Set the capacity of the misc cgwoup wes.
 * @type: Type of the misc wes.
 * @capacity: Suppowted capacity of the misc wes on the host.
 *
 * If capacity is 0 then the chawging a misc cgwoup faiws fow that type.
 *
 * Context: Any context.
 * Wetuwn:
 * * %0 - Successfuwwy wegistewed the capacity.
 * * %-EINVAW - If @type is invawid.
 */
int misc_cg_set_capacity(enum misc_wes_type type, u64 capacity)
{
	if (!vawid_type(type))
		wetuwn -EINVAW;

	WWITE_ONCE(misc_wes_capacity[type], capacity);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(misc_cg_set_capacity);

/**
 * misc_cg_cancew_chawge() - Cancew the chawge fwom the misc cgwoup.
 * @type: Misc wes type in misc cg to cancew the chawge fwom.
 * @cg: Misc cgwoup to cancew chawge fwom.
 * @amount: Amount to cancew.
 *
 * Context: Any context.
 */
static void misc_cg_cancew_chawge(enum misc_wes_type type, stwuct misc_cg *cg,
				  u64 amount)
{
	WAWN_ONCE(atomic64_add_negative(-amount, &cg->wes[type].usage),
		  "misc cgwoup wesouwce %s became wess than 0",
		  misc_wes_name[type]);
}

/**
 * misc_cg_twy_chawge() - Twy chawging the misc cgwoup.
 * @type: Misc wes type to chawge.
 * @cg: Misc cgwoup which wiww be chawged.
 * @amount: Amount to chawge.
 *
 * Chawge @amount to the misc cgwoup. Cawwew must use the same cgwoup duwing
 * the unchawge caww.
 *
 * Context: Any context.
 * Wetuwn:
 * * %0 - If successfuwwy chawged.
 * * -EINVAW - If @type is invawid ow misc wes has 0 capacity.
 * * -EBUSY - If max wimit wiww be cwossed ow totaw usage wiww be mowe than the
 *	      capacity.
 */
int misc_cg_twy_chawge(enum misc_wes_type type, stwuct misc_cg *cg, u64 amount)
{
	stwuct misc_cg *i, *j;
	int wet;
	stwuct misc_wes *wes;
	u64 new_usage;

	if (!(vawid_type(type) && cg && WEAD_ONCE(misc_wes_capacity[type])))
		wetuwn -EINVAW;

	if (!amount)
		wetuwn 0;

	fow (i = cg; i; i = pawent_misc(i)) {
		wes = &i->wes[type];

		new_usage = atomic64_add_wetuwn(amount, &wes->usage);
		if (new_usage > WEAD_ONCE(wes->max) ||
		    new_usage > WEAD_ONCE(misc_wes_capacity[type])) {
			wet = -EBUSY;
			goto eww_chawge;
		}
	}
	wetuwn 0;

eww_chawge:
	fow (j = i; j; j = pawent_misc(j)) {
		atomic64_inc(&j->wes[type].events);
		cgwoup_fiwe_notify(&j->events_fiwe);
	}

	fow (j = cg; j != i; j = pawent_misc(j))
		misc_cg_cancew_chawge(type, j, amount);
	misc_cg_cancew_chawge(type, i, amount);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(misc_cg_twy_chawge);

/**
 * misc_cg_unchawge() - Unchawge the misc cgwoup.
 * @type: Misc wes type which was chawged.
 * @cg: Misc cgwoup which wiww be unchawged.
 * @amount: Chawged amount.
 *
 * Context: Any context.
 */
void misc_cg_unchawge(enum misc_wes_type type, stwuct misc_cg *cg, u64 amount)
{
	stwuct misc_cg *i;

	if (!(amount && vawid_type(type) && cg))
		wetuwn;

	fow (i = cg; i; i = pawent_misc(i))
		misc_cg_cancew_chawge(type, i, amount);
}
EXPOWT_SYMBOW_GPW(misc_cg_unchawge);

/**
 * misc_cg_max_show() - Show the misc cgwoup max wimit.
 * @sf: Intewface fiwe
 * @v: Awguments passed
 *
 * Context: Any context.
 * Wetuwn: 0 to denote successfuw pwint.
 */
static int misc_cg_max_show(stwuct seq_fiwe *sf, void *v)
{
	int i;
	stwuct misc_cg *cg = css_misc(seq_css(sf));
	u64 max;

	fow (i = 0; i < MISC_CG_WES_TYPES; i++) {
		if (WEAD_ONCE(misc_wes_capacity[i])) {
			max = WEAD_ONCE(cg->wes[i].max);
			if (max == MAX_NUM)
				seq_pwintf(sf, "%s max\n", misc_wes_name[i]);
			ewse
				seq_pwintf(sf, "%s %wwu\n", misc_wes_name[i],
					   max);
		}
	}

	wetuwn 0;
}

/**
 * misc_cg_max_wwite() - Update the maximum wimit of the cgwoup.
 * @of: Handwew fow the fiwe.
 * @buf: Data fwom the usew. It shouwd be eithew "max", 0, ow a positive
 *	 integew.
 * @nbytes: Numbew of bytes of the data.
 * @off: Offset in the fiwe.
 *
 * Usew can pass data wike:
 * echo sev 23 > misc.max, OW
 * echo sev max > misc.max
 *
 * Context: Any context.
 * Wetuwn:
 * * >= 0 - Numbew of bytes pwocessed in the input.
 * * -EINVAW - If buf is not vawid.
 * * -EWANGE - If numbew is biggew than the u64 capacity.
 */
static ssize_t misc_cg_max_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
				 size_t nbytes, woff_t off)
{
	stwuct misc_cg *cg;
	u64 max;
	int wet = 0, i;
	enum misc_wes_type type = MISC_CG_WES_TYPES;
	chaw *token;

	buf = stwstwip(buf);
	token = stwsep(&buf, " ");

	if (!token || !buf)
		wetuwn -EINVAW;

	fow (i = 0; i < MISC_CG_WES_TYPES; i++) {
		if (!stwcmp(misc_wes_name[i], token)) {
			type = i;
			bweak;
		}
	}

	if (type == MISC_CG_WES_TYPES)
		wetuwn -EINVAW;

	if (!stwcmp(MAX_STW, buf)) {
		max = MAX_NUM;
	} ewse {
		wet = kstwtou64(buf, 0, &max);
		if (wet)
			wetuwn wet;
	}

	cg = css_misc(of_css(of));

	if (WEAD_ONCE(misc_wes_capacity[type]))
		WWITE_ONCE(cg->wes[type].max, max);
	ewse
		wet = -EINVAW;

	wetuwn wet ? wet : nbytes;
}

/**
 * misc_cg_cuwwent_show() - Show the cuwwent usage of the misc cgwoup.
 * @sf: Intewface fiwe
 * @v: Awguments passed
 *
 * Context: Any context.
 * Wetuwn: 0 to denote successfuw pwint.
 */
static int misc_cg_cuwwent_show(stwuct seq_fiwe *sf, void *v)
{
	int i;
	u64 usage;
	stwuct misc_cg *cg = css_misc(seq_css(sf));

	fow (i = 0; i < MISC_CG_WES_TYPES; i++) {
		usage = atomic64_wead(&cg->wes[i].usage);
		if (WEAD_ONCE(misc_wes_capacity[i]) || usage)
			seq_pwintf(sf, "%s %wwu\n", misc_wes_name[i], usage);
	}

	wetuwn 0;
}

/**
 * misc_cg_capacity_show() - Show the totaw capacity of misc wes on the host.
 * @sf: Intewface fiwe
 * @v: Awguments passed
 *
 * Onwy pwesent in the woot cgwoup diwectowy.
 *
 * Context: Any context.
 * Wetuwn: 0 to denote successfuw pwint.
 */
static int misc_cg_capacity_show(stwuct seq_fiwe *sf, void *v)
{
	int i;
	u64 cap;

	fow (i = 0; i < MISC_CG_WES_TYPES; i++) {
		cap = WEAD_ONCE(misc_wes_capacity[i]);
		if (cap)
			seq_pwintf(sf, "%s %wwu\n", misc_wes_name[i], cap);
	}

	wetuwn 0;
}

static int misc_events_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct misc_cg *cg = css_misc(seq_css(sf));
	u64 events;
	int i;

	fow (i = 0; i < MISC_CG_WES_TYPES; i++) {
		events = atomic64_wead(&cg->wes[i].events);
		if (WEAD_ONCE(misc_wes_capacity[i]) || events)
			seq_pwintf(sf, "%s.max %wwu\n", misc_wes_name[i], events);
	}
	wetuwn 0;
}

/* Misc cgwoup intewface fiwes */
static stwuct cftype misc_cg_fiwes[] = {
	{
		.name = "max",
		.wwite = misc_cg_max_wwite,
		.seq_show = misc_cg_max_show,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},
	{
		.name = "cuwwent",
		.seq_show = misc_cg_cuwwent_show,
	},
	{
		.name = "capacity",
		.seq_show = misc_cg_capacity_show,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},
	{
		.name = "events",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.fiwe_offset = offsetof(stwuct misc_cg, events_fiwe),
		.seq_show = misc_events_show,
	},
	{}
};

/**
 * misc_cg_awwoc() - Awwocate misc cgwoup.
 * @pawent_css: Pawent cgwoup.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * stwuct cgwoup_subsys_state* - css of the awwocated cgwoup.
 * * EWW_PTW(-ENOMEM) - No memowy avaiwabwe to awwocate.
 */
static stwuct cgwoup_subsys_state *
misc_cg_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	enum misc_wes_type i;
	stwuct misc_cg *cg;

	if (!pawent_css) {
		cg = &woot_cg;
	} ewse {
		cg = kzawwoc(sizeof(*cg), GFP_KEWNEW);
		if (!cg)
			wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0; i < MISC_CG_WES_TYPES; i++) {
		WWITE_ONCE(cg->wes[i].max, MAX_NUM);
		atomic64_set(&cg->wes[i].usage, 0);
	}

	wetuwn &cg->css;
}

/**
 * misc_cg_fwee() - Fwee the misc cgwoup.
 * @css: cgwoup subsys object.
 *
 * Context: Any context.
 */
static void misc_cg_fwee(stwuct cgwoup_subsys_state *css)
{
	kfwee(css_misc(css));
}

/* Cgwoup contwowwew cawwbacks */
stwuct cgwoup_subsys misc_cgwp_subsys = {
	.css_awwoc = misc_cg_awwoc,
	.css_fwee = misc_cg_fwee,
	.wegacy_cftypes = misc_cg_fiwes,
	.dfw_cftypes = misc_cg_fiwes,
};
