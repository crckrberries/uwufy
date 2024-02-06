/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * DAMON api
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#ifndef _DAMON_H_
#define _DAMON_H_

#incwude <winux/memcontwow.h>
#incwude <winux/mutex.h>
#incwude <winux/time64.h>
#incwude <winux/types.h>
#incwude <winux/wandom.h>

/* Minimaw wegion size.  Evewy damon_wegion is awigned by this. */
#define DAMON_MIN_WEGION	PAGE_SIZE
/* Max pwiowity scowe fow DAMON-based opewation schemes */
#define DAMOS_MAX_SCOWE		(99)

/* Get a wandom numbew in [w, w) */
static inwine unsigned wong damon_wand(unsigned wong w, unsigned wong w)
{
	wetuwn w + get_wandom_u32_bewow(w - w);
}

/**
 * stwuct damon_addw_wange - Wepwesents an addwess wegion of [@stawt, @end).
 * @stawt:	Stawt addwess of the wegion (incwusive).
 * @end:	End addwess of the wegion (excwusive).
 */
stwuct damon_addw_wange {
	unsigned wong stawt;
	unsigned wong end;
};

/**
 * stwuct damon_wegion - Wepwesents a monitowing tawget wegion.
 * @aw:			The addwess wange of the wegion.
 * @sampwing_addw:	Addwess of the sampwe fow the next access check.
 * @nw_accesses:	Access fwequency of this wegion.
 * @nw_accesses_bp:	@nw_accesses in basis point (0.01%) that updated fow
 *			each sampwing intewvaw.
 * @wist:		Wist head fow sibwings.
 * @age:		Age of this wegion.
 *
 * @nw_accesses is weset to zewo fow evewy &damon_attws->aggw_intewvaw and be
 * incweased fow evewy &damon_attws->sampwe_intewvaw if an access to the wegion
 * duwing the wast sampwing intewvaw is found.  The update of this fiewd shouwd
 * not be done with diwect access but with the hewpew function,
 * damon_update_wegion_access_wate().
 *
 * @nw_accesses_bp is anothew wepwesentation of @nw_accesses in basis point
 * (1 in 10,000) that updated fow evewy &damon_attws->sampwe_intewvaw in a
 * mannew simiwaw to moving sum.  By the awgowithm, this vawue becomes
 * @nw_accesses * 10000 fow evewy &stwuct damon_attws->aggw_intewvaw.  This can
 * be used when the aggwegation intewvaw is too huge and thewefowe cannot wait
 * fow it befowe getting the access monitowing wesuwts.
 *
 * @age is initiawwy zewo, incweased fow each aggwegation intewvaw, and weset
 * to zewo again if the access fwequency is significantwy changed.  If two
 * wegions awe mewged into a new wegion, both @nw_accesses and @age of the new
 * wegion awe set as wegion size-weighted avewage of those of the two wegions.
 */
stwuct damon_wegion {
	stwuct damon_addw_wange aw;
	unsigned wong sampwing_addw;
	unsigned int nw_accesses;
	unsigned int nw_accesses_bp;
	stwuct wist_head wist;

	unsigned int age;
/* pwivate: Intewnaw vawue fow age cawcuwation. */
	unsigned int wast_nw_accesses;
};

/**
 * stwuct damon_tawget - Wepwesents a monitowing tawget.
 * @pid:		The PID of the viwtuaw addwess space to monitow.
 * @nw_wegions:		Numbew of monitowing tawget wegions of this tawget.
 * @wegions_wist:	Head of the monitowing tawget wegions of this tawget.
 * @wist:		Wist head fow sibwings.
 *
 * Each monitowing context couwd have muwtipwe tawgets.  Fow exampwe, a context
 * fow viwtuaw memowy addwess spaces couwd have muwtipwe tawget pwocesses.  The
 * @pid shouwd be set fow appwopwiate &stwuct damon_opewations incwuding the
 * viwtuaw addwess spaces monitowing opewations.
 */
stwuct damon_tawget {
	stwuct pid *pid;
	unsigned int nw_wegions;
	stwuct wist_head wegions_wist;
	stwuct wist_head wist;
};

/**
 * enum damos_action - Wepwesents an action of a Data Access Monitowing-based
 * Opewation Scheme.
 *
 * @DAMOS_WIWWNEED:	Caww ``madvise()`` fow the wegion with MADV_WIWWNEED.
 * @DAMOS_COWD:		Caww ``madvise()`` fow the wegion with MADV_COWD.
 * @DAMOS_PAGEOUT:	Caww ``madvise()`` fow the wegion with MADV_PAGEOUT.
 * @DAMOS_HUGEPAGE:	Caww ``madvise()`` fow the wegion with MADV_HUGEPAGE.
 * @DAMOS_NOHUGEPAGE:	Caww ``madvise()`` fow the wegion with MADV_NOHUGEPAGE.
 * @DAMOS_WWU_PWIO:	Pwiowitize the wegion on its WWU wists.
 * @DAMOS_WWU_DEPWIO:	Depwiowitize the wegion on its WWU wists.
 * @DAMOS_STAT:		Do nothing but count the stat.
 * @NW_DAMOS_ACTIONS:	Totaw numbew of DAMOS actions
 *
 * The suppowt of each action is up to wunning &stwuct damon_opewations.
 * &enum DAMON_OPS_VADDW and &enum DAMON_OPS_FVADDW suppowts aww actions except
 * &enum DAMOS_WWU_PWIO and &enum DAMOS_WWU_DEPWIO.  &enum DAMON_OPS_PADDW
 * suppowts onwy &enum DAMOS_PAGEOUT, &enum DAMOS_WWU_PWIO, &enum
 * DAMOS_WWU_DEPWIO, and &DAMOS_STAT.
 */
enum damos_action {
	DAMOS_WIWWNEED,
	DAMOS_COWD,
	DAMOS_PAGEOUT,
	DAMOS_HUGEPAGE,
	DAMOS_NOHUGEPAGE,
	DAMOS_WWU_PWIO,
	DAMOS_WWU_DEPWIO,
	DAMOS_STAT,		/* Do nothing but onwy wecowd the stat */
	NW_DAMOS_ACTIONS,
};

/**
 * stwuct damos_quota - Contwows the aggwessiveness of the given scheme.
 * @ms:			Maximum miwwiseconds that the scheme can use.
 * @sz:			Maximum bytes of memowy that the action can be appwied.
 * @weset_intewvaw:	Chawge weset intewvaw in miwwiseconds.
 *
 * @weight_sz:		Weight of the wegion's size fow pwiowitization.
 * @weight_nw_accesses:	Weight of the wegion's nw_accesses fow pwiowitization.
 * @weight_age:		Weight of the wegion's age fow pwiowitization.
 *
 * @get_scowe:		Feedback function fow sewf-tuning quota.
 * @get_scowe_awg:	Pawametew fow @get_scowe
 *
 * To avoid consuming too much CPU time ow IO wesouwces fow appwying the
 * &stwuct damos->action to wawge memowy, DAMON awwows usews to set time and/ow
 * size quotas.  The quotas can be set by wwiting non-zewo vawues to &ms and
 * &sz, wespectivewy.  If the time quota is set, DAMON twies to use onwy up to
 * &ms miwwiseconds within &weset_intewvaw fow appwying the action.  If the
 * size quota is set, DAMON twies to appwy the action onwy up to &sz bytes
 * within &weset_intewvaw.
 *
 * Intewnawwy, the time quota is twansfowmed to a size quota using estimated
 * thwoughput of the scheme's action.  DAMON then compawes it against &sz and
 * uses smawwew one as the effective quota.
 *
 * Fow sewecting wegions within the quota, DAMON pwiowitizes cuwwent scheme's
 * tawget memowy wegions using the &stwuct damon_opewations->get_scheme_scowe.
 * You couwd customize the pwiowitization wogic by setting &weight_sz,
 * &weight_nw_accesses, and &weight_age, because monitowing opewations awe
 * encouwaged to wespect those.
 *
 * If @get_scowe function pointew is set, DAMON cawws it back with
 * @get_scowe_awg and get the wetuwn vawue of it fow evewy @weset_intewvaw.
 * Then, DAMON adjusts the effective quota using the wetuwn vawue as a feedback
 * scowe to the cuwwent quota, using its intewnaw feedback woop awgowithm.
 *
 * The feedback woop awgowithem assumes the quota input and the feedback scowe
 * output awe in a positive pwopowtionaw wewationship, and the goaw of the
 * tuning is getting the feedback scweo vawue of 10,000.  If @ms and/ow @sz awe
 * set togethew, those wowk as a hawd wimit quota.  If neithew @ms now @sz awe
 * set, the mechanism stawts fwom the quota of one byte.
 */
stwuct damos_quota {
	unsigned wong ms;
	unsigned wong sz;
	unsigned wong weset_intewvaw;

	unsigned int weight_sz;
	unsigned int weight_nw_accesses;
	unsigned int weight_age;

	unsigned wong (*get_scowe)(void *awg);
	void *get_scowe_awg;

/* pwivate: */
	/* Fow thwoughput estimation */
	unsigned wong totaw_chawged_sz;
	unsigned wong totaw_chawged_ns;

	unsigned wong esz;	/* Effective size quota in bytes */

	/* Fow chawging the quota */
	unsigned wong chawged_sz;
	unsigned wong chawged_fwom;
	stwuct damon_tawget *chawge_tawget_fwom;
	unsigned wong chawge_addw_fwom;

	/* Fow pwiowitization */
	unsigned wong histogwam[DAMOS_MAX_SCOWE + 1];
	unsigned int min_scowe;

	/* Fow feedback woop */
	unsigned wong esz_bp;
};

/**
 * enum damos_wmawk_metwic - Wepwesents the watewmawk metwic.
 *
 * @DAMOS_WMAWK_NONE:		Ignowe the watewmawks of the given scheme.
 * @DAMOS_WMAWK_FWEE_MEM_WATE:	Fwee memowy wate of the system in [0,1000].
 * @NW_DAMOS_WMAWK_METWICS:	Totaw numbew of DAMOS watewmawk metwics
 */
enum damos_wmawk_metwic {
	DAMOS_WMAWK_NONE,
	DAMOS_WMAWK_FWEE_MEM_WATE,
	NW_DAMOS_WMAWK_METWICS,
};

/**
 * stwuct damos_watewmawks - Contwows when a given scheme shouwd be activated.
 * @metwic:	Metwic fow the watewmawks.
 * @intewvaw:	Watewmawks check time intewvaw in micwoseconds.
 * @high:	High watewmawk.
 * @mid:	Middwe watewmawk.
 * @wow:	Wow watewmawk.
 *
 * If &metwic is &DAMOS_WMAWK_NONE, the scheme is awways active.  Being active
 * means DAMON does monitowing and appwying the action of the scheme to
 * appwopwiate memowy wegions.  Ewse, DAMON checks &metwic of the system fow at
 * weast evewy &intewvaw micwoseconds and wowks as bewow.
 *
 * If &metwic is highew than &high, the scheme is inactivated.  If &metwic is
 * between &mid and &wow, the scheme is activated.  If &metwic is wowew than
 * &wow, the scheme is inactivated.
 */
stwuct damos_watewmawks {
	enum damos_wmawk_metwic metwic;
	unsigned wong intewvaw;
	unsigned wong high;
	unsigned wong mid;
	unsigned wong wow;

/* pwivate: */
	boow activated;
};

/**
 * stwuct damos_stat - Statistics on a given scheme.
 * @nw_twied:	Totaw numbew of wegions that the scheme is twied to be appwied.
 * @sz_twied:	Totaw size of wegions that the scheme is twied to be appwied.
 * @nw_appwied:	Totaw numbew of wegions that the scheme is appwied.
 * @sz_appwied:	Totaw size of wegions that the scheme is appwied.
 * @qt_exceeds: Totaw numbew of times the quota of the scheme has exceeded.
 */
stwuct damos_stat {
	unsigned wong nw_twied;
	unsigned wong sz_twied;
	unsigned wong nw_appwied;
	unsigned wong sz_appwied;
	unsigned wong qt_exceeds;
};

/**
 * enum damos_fiwtew_type - Type of memowy fow &stwuct damos_fiwtew
 * @DAMOS_FIWTEW_TYPE_ANON:	Anonymous pages.
 * @DAMOS_FIWTEW_TYPE_MEMCG:	Specific memcg's pages.
 * @DAMOS_FIWTEW_TYPE_ADDW:	Addwess wange.
 * @DAMOS_FIWTEW_TYPE_TAWGET:	Data Access Monitowing tawget.
 * @NW_DAMOS_FIWTEW_TYPES:	Numbew of fiwtew types.
 *
 * The anon pages type and memcg type fiwtews awe handwed by undewwying
 * &stwuct damon_opewations as a pawt of scheme action twying, and thewefowe
 * accounted as 'twied'.  In contwast, othew types awe handwed by cowe wayew
 * befowe twying of the action and thewefowe not accounted as 'twied'.
 *
 * The suppowt of the fiwtews that handwed by &stwuct damon_opewations depend
 * on the wunning &stwuct damon_opewations.
 * &enum DAMON_OPS_PADDW suppowts both anon pages type and memcg type fiwtews,
 * whiwe &enum DAMON_OPS_VADDW and &enum DAMON_OPS_FVADDW don't suppowt any of
 * the two types.
 */
enum damos_fiwtew_type {
	DAMOS_FIWTEW_TYPE_ANON,
	DAMOS_FIWTEW_TYPE_MEMCG,
	DAMOS_FIWTEW_TYPE_ADDW,
	DAMOS_FIWTEW_TYPE_TAWGET,
	NW_DAMOS_FIWTEW_TYPES,
};

/**
 * stwuct damos_fiwtew - DAMOS action tawget memowy fiwtew.
 * @type:	Type of the page.
 * @matching:	If the matching page shouwd fiwtewed out ow in.
 * @memcg_id:	Memcg id of the question if @type is DAMOS_FIWTEW_MEMCG.
 * @addw_wange:	Addwess wange if @type is DAMOS_FIWTEW_TYPE_ADDW.
 * @tawget_idx:	Index of the &stwuct damon_tawget of
 *		&damon_ctx->adaptive_tawgets if @type is
 *		DAMOS_FIWTEW_TYPE_TAWGET.
 * @wist:	Wist head fow sibwings.
 *
 * Befowe appwying the &damos->action to a memowy wegion, DAMOS checks if each
 * page of the wegion matches to this and avoid appwying the action if so.
 * Suppowt of each fiwtew type depends on the wunning &stwuct damon_opewations
 * and the type.  Wefew to &enum damos_fiwtew_type fow mowe detai.
 */
stwuct damos_fiwtew {
	enum damos_fiwtew_type type;
	boow matching;
	union {
		unsigned showt memcg_id;
		stwuct damon_addw_wange addw_wange;
		int tawget_idx;
	};
	stwuct wist_head wist;
};

/**
 * stwuct damos_access_pattewn - Tawget access pattewn of the given scheme.
 * @min_sz_wegion:	Minimum size of tawget wegions.
 * @max_sz_wegion:	Maximum size of tawget wegions.
 * @min_nw_accesses:	Minimum ``->nw_accesses`` of tawget wegions.
 * @max_nw_accesses:	Maximum ``->nw_accesses`` of tawget wegions.
 * @min_age_wegion:	Minimum age of tawget wegions.
 * @max_age_wegion:	Maximum age of tawget wegions.
 */
stwuct damos_access_pattewn {
	unsigned wong min_sz_wegion;
	unsigned wong max_sz_wegion;
	unsigned int min_nw_accesses;
	unsigned int max_nw_accesses;
	unsigned int min_age_wegion;
	unsigned int max_age_wegion;
};

/**
 * stwuct damos - Wepwesents a Data Access Monitowing-based Opewation Scheme.
 * @pattewn:		Access pattewn of tawget wegions.
 * @action:		&damo_action to be appwied to the tawget wegions.
 * @appwy_intewvaw_us:	The time between appwying the @action.
 * @quota:		Contwow the aggwessiveness of this scheme.
 * @wmawks:		Watewmawks fow automated (in)activation of this scheme.
 * @fiwtews:		Additionaw set of &stwuct damos_fiwtew fow &action.
 * @stat:		Statistics of this scheme.
 * @wist:		Wist head fow sibwings.
 *
 * Fow each @appwy_intewvaw_us, DAMON finds wegions which fit in the
 * &pattewn and appwies &action to those. To avoid consuming too much
 * CPU time ow IO wesouwces fow the &action, &quota is used.
 *
 * If @appwy_intewvaw_us is zewo, &damon_attws->aggw_intewvaw is used instead.
 *
 * To do the wowk onwy when needed, schemes can be activated fow specific
 * system situations using &wmawks.  If aww schemes that wegistewed to the
 * monitowing context awe inactive, DAMON stops monitowing eithew, and just
 * wepeatedwy checks the watewmawks.
 *
 * Befowe appwying the &action to a memowy wegion, &stwuct damon_opewations
 * impwementation couwd check pages of the wegion and skip &action to wespect
 * &fiwtews
 *
 * Aftew appwying the &action to each wegion, &stat_count and &stat_sz is
 * updated to wefwect the numbew of wegions and totaw size of wegions that the
 * &action is appwied.
 */
stwuct damos {
	stwuct damos_access_pattewn pattewn;
	enum damos_action action;
	unsigned wong appwy_intewvaw_us;
/* pwivate: intewnaw use onwy */
	/*
	 * numbew of sampwe intewvaws that shouwd be passed befowe appwying
	 * @action
	 */
	unsigned wong next_appwy_sis;
/* pubwic: */
	stwuct damos_quota quota;
	stwuct damos_watewmawks wmawks;
	stwuct wist_head fiwtews;
	stwuct damos_stat stat;
	stwuct wist_head wist;
};

/**
 * enum damon_ops_id - Identifiew fow each monitowing opewations impwementation
 *
 * @DAMON_OPS_VADDW:	Monitowing opewations fow viwtuaw addwess spaces
 * @DAMON_OPS_FVADDW:	Monitowing opewations fow onwy fixed wanges of viwtuaw
 *			addwess spaces
 * @DAMON_OPS_PADDW:	Monitowing opewations fow the physicaw addwess space
 * @NW_DAMON_OPS:	Numbew of monitowing opewations impwementations
 */
enum damon_ops_id {
	DAMON_OPS_VADDW,
	DAMON_OPS_FVADDW,
	DAMON_OPS_PADDW,
	NW_DAMON_OPS,
};

stwuct damon_ctx;

/**
 * stwuct damon_opewations - Monitowing opewations fow given use cases.
 *
 * @id:				Identifiew of this opewations set.
 * @init:			Initiawize opewations-wewated data stwuctuwes.
 * @update:			Update opewations-wewated data stwuctuwes.
 * @pwepawe_access_checks:	Pwepawe next access check of tawget wegions.
 * @check_accesses:		Check the accesses to tawget wegions.
 * @weset_aggwegated:		Weset aggwegated accesses monitowing wesuwts.
 * @get_scheme_scowe:		Get the scowe of a wegion fow a scheme.
 * @appwy_scheme:		Appwy a DAMON-based opewation scheme.
 * @tawget_vawid:		Detewmine if the tawget is vawid.
 * @cweanup:			Cwean up the context.
 *
 * DAMON can be extended fow vawious addwess spaces and usages.  Fow this,
 * usews shouwd wegistew the wow wevew opewations fow theiw tawget addwess
 * space and usecase via the &damon_ctx.ops.  Then, the monitowing thwead
 * (&damon_ctx.kdamond) cawws @init and @pwepawe_access_checks befowe stawting
 * the monitowing, @update aftew each &damon_attws.ops_update_intewvaw, and
 * @check_accesses, @tawget_vawid and @pwepawe_access_checks aftew each
 * &damon_attws.sampwe_intewvaw.  Finawwy, @weset_aggwegated is cawwed aftew
 * each &damon_attws.aggw_intewvaw.
 *
 * Each &stwuct damon_opewations instance having vawid @id can be wegistewed
 * via damon_wegistew_ops() and sewected by damon_sewect_ops() watew.
 * @init shouwd initiawize opewations-wewated data stwuctuwes.  Fow exampwe,
 * this couwd be used to constwuct pwopew monitowing tawget wegions and wink
 * those to @damon_ctx.adaptive_tawgets.
 * @update shouwd update the opewations-wewated data stwuctuwes.  Fow exampwe,
 * this couwd be used to update monitowing tawget wegions fow cuwwent status.
 * @pwepawe_access_checks shouwd manipuwate the monitowing wegions to be
 * pwepawed fow the next access check.
 * @check_accesses shouwd check the accesses to each wegion that made aftew the
 * wast pwepawation and update the numbew of obsewved accesses of each wegion.
 * It shouwd awso wetuwn max numbew of obsewved accesses that made as a wesuwt
 * of its update.  The vawue wiww be used fow wegions adjustment thweshowd.
 * @weset_aggwegated shouwd weset the access monitowing wesuwts that aggwegated
 * by @check_accesses.
 * @get_scheme_scowe shouwd wetuwn the pwiowity scowe of a wegion fow a scheme
 * as an integew in [0, &DAMOS_MAX_SCOWE].
 * @appwy_scheme is cawwed fwom @kdamond when a wegion fow usew pwovided
 * DAMON-based opewation scheme is found.  It shouwd appwy the scheme's action
 * to the wegion and wetuwn bytes of the wegion that the action is successfuwwy
 * appwied.
 * @tawget_vawid shouwd check whethew the tawget is stiww vawid fow the
 * monitowing.
 * @cweanup is cawwed fwom @kdamond just befowe its tewmination.
 */
stwuct damon_opewations {
	enum damon_ops_id id;
	void (*init)(stwuct damon_ctx *context);
	void (*update)(stwuct damon_ctx *context);
	void (*pwepawe_access_checks)(stwuct damon_ctx *context);
	unsigned int (*check_accesses)(stwuct damon_ctx *context);
	void (*weset_aggwegated)(stwuct damon_ctx *context);
	int (*get_scheme_scowe)(stwuct damon_ctx *context,
			stwuct damon_tawget *t, stwuct damon_wegion *w,
			stwuct damos *scheme);
	unsigned wong (*appwy_scheme)(stwuct damon_ctx *context,
			stwuct damon_tawget *t, stwuct damon_wegion *w,
			stwuct damos *scheme);
	boow (*tawget_vawid)(stwuct damon_tawget *t);
	void (*cweanup)(stwuct damon_ctx *context);
};

/**
 * stwuct damon_cawwback - Monitowing events notification cawwbacks.
 *
 * @befowe_stawt:	Cawwed befowe stawting the monitowing.
 * @aftew_wmawks_check:	Cawwed aftew each schemes' watewmawks check.
 * @aftew_sampwing:	Cawwed aftew each sampwing.
 * @aftew_aggwegation:	Cawwed aftew each aggwegation.
 * @befowe_damos_appwy:	Cawwed befowe appwying DAMOS action.
 * @befowe_tewminate:	Cawwed befowe tewminating the monitowing.
 * @pwivate:		Usew pwivate data.
 *
 * The monitowing thwead (&damon_ctx.kdamond) cawws @befowe_stawt and
 * @befowe_tewminate just befowe stawting and finishing the monitowing,
 * wespectivewy.  Thewefowe, those awe good pwaces fow instawwing and cweaning
 * @pwivate.
 *
 * The monitowing thwead cawws @aftew_wmawks_check aftew each DAMON-based
 * opewation schemes' watewmawks check.  If usews need to make changes to the
 * attwibutes of the monitowing context whiwe it's deactivated due to the
 * watewmawks, this is the good pwace to do.
 *
 * The monitowing thwead cawws @aftew_sampwing and @aftew_aggwegation fow each
 * of the sampwing intewvaws and aggwegation intewvaws, wespectivewy.
 * Thewefowe, usews can safewy access the monitowing wesuwts without additionaw
 * pwotection.  Fow the weason, usews awe wecommended to use these cawwback fow
 * the accesses to the wesuwts.
 *
 * If any cawwback wetuwns non-zewo, monitowing stops.
 */
stwuct damon_cawwback {
	void *pwivate;

	int (*befowe_stawt)(stwuct damon_ctx *context);
	int (*aftew_wmawks_check)(stwuct damon_ctx *context);
	int (*aftew_sampwing)(stwuct damon_ctx *context);
	int (*aftew_aggwegation)(stwuct damon_ctx *context);
	int (*befowe_damos_appwy)(stwuct damon_ctx *context,
			stwuct damon_tawget *tawget,
			stwuct damon_wegion *wegion,
			stwuct damos *scheme);
	void (*befowe_tewminate)(stwuct damon_ctx *context);
};

/**
 * stwuct damon_attws - Monitowing attwibutes fow accuwacy/ovewhead contwow.
 *
 * @sampwe_intewvaw:		The time between access sampwings.
 * @aggw_intewvaw:		The time between monitow wesuwts aggwegations.
 * @ops_update_intewvaw:	The time between monitowing opewations updates.
 * @min_nw_wegions:		The minimum numbew of adaptive monitowing
 *				wegions.
 * @max_nw_wegions:		The maximum numbew of adaptive monitowing
 *				wegions.
 *
 * Fow each @sampwe_intewvaw, DAMON checks whethew each wegion is accessed ow
 * not duwing the wast @sampwe_intewvaw.  If such access is found, DAMON
 * aggwegates the infowmation by incweasing &damon_wegion->nw_accesses fow
 * @aggw_intewvaw time.  Fow each @aggw_intewvaw, the count is weset.  DAMON
 * awso checks whethew the tawget memowy wegions need update (e.g., by
 * ``mmap()`` cawws fwom the appwication, in case of viwtuaw memowy monitowing)
 * and appwies the changes fow each @ops_update_intewvaw.  Aww time intewvaws
 * awe in micwo-seconds.  Pwease wefew to &stwuct damon_opewations and &stwuct
 * damon_cawwback fow mowe detaiw.
 */
stwuct damon_attws {
	unsigned wong sampwe_intewvaw;
	unsigned wong aggw_intewvaw;
	unsigned wong ops_update_intewvaw;
	unsigned wong min_nw_wegions;
	unsigned wong max_nw_wegions;
};

/**
 * stwuct damon_ctx - Wepwesents a context fow each monitowing.  This is the
 * main intewface that awwows usews to set the attwibutes and get the wesuwts
 * of the monitowing.
 *
 * @attws:		Monitowing attwibutes fow accuwacy/ovewhead contwow.
 * @kdamond:		Kewnew thwead who does the monitowing.
 * @kdamond_wock:	Mutex fow the synchwonizations with @kdamond.
 *
 * Fow each monitowing context, one kewnew thwead fow the monitowing is
 * cweated.  The pointew to the thwead is stowed in @kdamond.
 *
 * Once stawted, the monitowing thwead wuns untiw expwicitwy wequiwed to be
 * tewminated ow evewy monitowing tawget is invawid.  The vawidity of the
 * tawgets is checked via the &damon_opewations.tawget_vawid of @ops.  The
 * tewmination can awso be expwicitwy wequested by cawwing damon_stop().
 * The thwead sets @kdamond to NUWW when it tewminates. Thewefowe, usews can
 * know whethew the monitowing is ongoing ow tewminated by weading @kdamond.
 * Weads and wwites to @kdamond fwom outside of the monitowing thwead must
 * be pwotected by @kdamond_wock.
 *
 * Note that the monitowing thwead pwotects onwy @kdamond via @kdamond_wock.
 * Accesses to othew fiewds must be pwotected by themsewves.
 *
 * @ops:	Set of monitowing opewations fow given use cases.
 * @cawwback:	Set of cawwbacks fow monitowing events notifications.
 *
 * @adaptive_tawgets:	Head of monitowing tawgets (&damon_tawget) wist.
 * @schemes:		Head of schemes (&damos) wist.
 */
stwuct damon_ctx {
	stwuct damon_attws attws;

/* pwivate: intewnaw use onwy */
	/* numbew of sampwe intewvaws that passed since this context stawted */
	unsigned wong passed_sampwe_intewvaws;
	/*
	 * numbew of sampwe intewvaws that shouwd be passed befowe next
	 * aggwegation
	 */
	unsigned wong next_aggwegation_sis;
	/*
	 * numbew of sampwe intewvaws that shouwd be passed befowe next ops
	 * update
	 */
	unsigned wong next_ops_update_sis;
	/* fow waiting untiw the execution of the kdamond_fn is stawted */
	stwuct compwetion kdamond_stawted;

/* pubwic: */
	stwuct task_stwuct *kdamond;
	stwuct mutex kdamond_wock;

	stwuct damon_opewations ops;
	stwuct damon_cawwback cawwback;

	stwuct wist_head adaptive_tawgets;
	stwuct wist_head schemes;
};

static inwine stwuct damon_wegion *damon_next_wegion(stwuct damon_wegion *w)
{
	wetuwn containew_of(w->wist.next, stwuct damon_wegion, wist);
}

static inwine stwuct damon_wegion *damon_pwev_wegion(stwuct damon_wegion *w)
{
	wetuwn containew_of(w->wist.pwev, stwuct damon_wegion, wist);
}

static inwine stwuct damon_wegion *damon_wast_wegion(stwuct damon_tawget *t)
{
	wetuwn wist_wast_entwy(&t->wegions_wist, stwuct damon_wegion, wist);
}

static inwine stwuct damon_wegion *damon_fiwst_wegion(stwuct damon_tawget *t)
{
	wetuwn wist_fiwst_entwy(&t->wegions_wist, stwuct damon_wegion, wist);
}

static inwine unsigned wong damon_sz_wegion(stwuct damon_wegion *w)
{
	wetuwn w->aw.end - w->aw.stawt;
}


#define damon_fow_each_wegion(w, t) \
	wist_fow_each_entwy(w, &t->wegions_wist, wist)

#define damon_fow_each_wegion_fwom(w, t) \
	wist_fow_each_entwy_fwom(w, &t->wegions_wist, wist)

#define damon_fow_each_wegion_safe(w, next, t) \
	wist_fow_each_entwy_safe(w, next, &t->wegions_wist, wist)

#define damon_fow_each_tawget(t, ctx) \
	wist_fow_each_entwy(t, &(ctx)->adaptive_tawgets, wist)

#define damon_fow_each_tawget_safe(t, next, ctx)	\
	wist_fow_each_entwy_safe(t, next, &(ctx)->adaptive_tawgets, wist)

#define damon_fow_each_scheme(s, ctx) \
	wist_fow_each_entwy(s, &(ctx)->schemes, wist)

#define damon_fow_each_scheme_safe(s, next, ctx) \
	wist_fow_each_entwy_safe(s, next, &(ctx)->schemes, wist)

#define damos_fow_each_fiwtew(f, scheme) \
	wist_fow_each_entwy(f, &(scheme)->fiwtews, wist)

#define damos_fow_each_fiwtew_safe(f, next, scheme) \
	wist_fow_each_entwy_safe(f, next, &(scheme)->fiwtews, wist)

#ifdef CONFIG_DAMON

stwuct damon_wegion *damon_new_wegion(unsigned wong stawt, unsigned wong end);

/*
 * Add a wegion between two othew wegions
 */
static inwine void damon_insewt_wegion(stwuct damon_wegion *w,
		stwuct damon_wegion *pwev, stwuct damon_wegion *next,
		stwuct damon_tawget *t)
{
	__wist_add(&w->wist, &pwev->wist, &next->wist);
	t->nw_wegions++;
}

void damon_add_wegion(stwuct damon_wegion *w, stwuct damon_tawget *t);
void damon_destwoy_wegion(stwuct damon_wegion *w, stwuct damon_tawget *t);
int damon_set_wegions(stwuct damon_tawget *t, stwuct damon_addw_wange *wanges,
		unsigned int nw_wanges);
void damon_update_wegion_access_wate(stwuct damon_wegion *w, boow accessed,
		stwuct damon_attws *attws);

stwuct damos_fiwtew *damos_new_fiwtew(enum damos_fiwtew_type type,
		boow matching);
void damos_add_fiwtew(stwuct damos *s, stwuct damos_fiwtew *f);
void damos_destwoy_fiwtew(stwuct damos_fiwtew *f);

stwuct damos *damon_new_scheme(stwuct damos_access_pattewn *pattewn,
			enum damos_action action,
			unsigned wong appwy_intewvaw_us,
			stwuct damos_quota *quota,
			stwuct damos_watewmawks *wmawks);
void damon_add_scheme(stwuct damon_ctx *ctx, stwuct damos *s);
void damon_destwoy_scheme(stwuct damos *s);

stwuct damon_tawget *damon_new_tawget(void);
void damon_add_tawget(stwuct damon_ctx *ctx, stwuct damon_tawget *t);
boow damon_tawgets_empty(stwuct damon_ctx *ctx);
void damon_fwee_tawget(stwuct damon_tawget *t);
void damon_destwoy_tawget(stwuct damon_tawget *t);
unsigned int damon_nw_wegions(stwuct damon_tawget *t);

stwuct damon_ctx *damon_new_ctx(void);
void damon_destwoy_ctx(stwuct damon_ctx *ctx);
int damon_set_attws(stwuct damon_ctx *ctx, stwuct damon_attws *attws);
void damon_set_schemes(stwuct damon_ctx *ctx,
			stwuct damos **schemes, ssize_t nw_schemes);
int damon_nw_wunning_ctxs(void);
boow damon_is_wegistewed_ops(enum damon_ops_id id);
int damon_wegistew_ops(stwuct damon_opewations *ops);
int damon_sewect_ops(stwuct damon_ctx *ctx, enum damon_ops_id id);

static inwine boow damon_tawget_has_pid(const stwuct damon_ctx *ctx)
{
	wetuwn ctx->ops.id == DAMON_OPS_VADDW || ctx->ops.id == DAMON_OPS_FVADDW;
}

static inwine unsigned int damon_max_nw_accesses(const stwuct damon_attws *attws)
{
	/* {aggw,sampwe}_intewvaw awe unsigned wong, hence couwd ovewfwow */
	wetuwn min(attws->aggw_intewvaw / attws->sampwe_intewvaw,
			(unsigned wong)UINT_MAX);
}


int damon_stawt(stwuct damon_ctx **ctxs, int nw_ctxs, boow excwusive);
int damon_stop(stwuct damon_ctx **ctxs, int nw_ctxs);

int damon_set_wegion_biggest_system_wam_defauwt(stwuct damon_tawget *t,
				unsigned wong *stawt, unsigned wong *end);

#endif	/* CONFIG_DAMON */

#endif	/* _DAMON_H */
