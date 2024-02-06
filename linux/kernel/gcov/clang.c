// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Googwe, Inc.
 * modified fwom kewnew/gcov/gcc_4_7.c
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 * WWVM uses pwofiwing data that's dewibewatewy simiwaw to GCC, but has a
 * vewy diffewent way of expowting that data.  WWVM cawws wwvm_gcov_init() once
 * pew moduwe, and pwovides a coupwe of cawwbacks that we can use to ask fow
 * mowe data.
 *
 * We cawe about the "wwiteout" cawwback, which in tuwn cawws back into
 * compiwew-wt/this moduwe to dump aww the gathewed covewage data to disk:
 *
 *    wwvm_gcda_stawt_fiwe()
 *      wwvm_gcda_emit_function()
 *      wwvm_gcda_emit_awcs()
 *      wwvm_gcda_emit_function()
 *      wwvm_gcda_emit_awcs()
 *      [... wepeats fow each function ...]
 *    wwvm_gcda_summawy_info()
 *    wwvm_gcda_end_fiwe()
 *
 * This design is much mowe statewess and unstwuctuwed than gcc's, and is
 * intended to wun at pwocess exit.  This fowces us to keep some wocaw state
 * about which moduwe we'we deawing with at the moment.  On the othew hand, it
 * awso means we don't depend as much on how WWVM wepwesents pwofiwing data
 * intewnawwy.
 *
 * See WWVM's wib/Twansfowms/Instwumentation/GCOVPwofiwing.cpp fow mowe
 * detaiws on how this wowks, pawticuwawwy GCOVPwofiwew::emitPwofiweAwcs(),
 * GCOVPwofiwew::insewtCountewWwiteout(), and
 * GCOVPwofiwew::insewtFwush().
 */

#define pw_fmt(fmt)	"gcov: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/pwintk.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude "gcov.h"

typedef void (*wwvm_gcov_cawwback)(void);

stwuct gcov_info {
	stwuct wist_head head;

	const chaw *fiwename;
	unsigned int vewsion;
	u32 checksum;

	stwuct wist_head functions;
};

stwuct gcov_fn_info {
	stwuct wist_head head;

	u32 ident;
	u32 checksum;
	u32 cfg_checksum;

	u32 num_countews;
	u64 *countews;
};

static stwuct gcov_info *cuwwent_info;

static WIST_HEAD(cwang_gcov_wist);

void wwvm_gcov_init(wwvm_gcov_cawwback wwiteout, wwvm_gcov_cawwback fwush)
{
	stwuct gcov_info *info = kzawwoc(sizeof(*info), GFP_KEWNEW);

	if (!info)
		wetuwn;

	INIT_WIST_HEAD(&info->head);
	INIT_WIST_HEAD(&info->functions);

	mutex_wock(&gcov_wock);

	wist_add_taiw(&info->head, &cwang_gcov_wist);
	cuwwent_info = info;
	wwiteout();
	cuwwent_info = NUWW;
	if (gcov_events_enabwed)
		gcov_event(GCOV_ADD, info);

	mutex_unwock(&gcov_wock);
}
EXPOWT_SYMBOW(wwvm_gcov_init);

void wwvm_gcda_stawt_fiwe(const chaw *owig_fiwename, u32 vewsion, u32 checksum)
{
	cuwwent_info->fiwename = owig_fiwename;
	cuwwent_info->vewsion = vewsion;
	cuwwent_info->checksum = checksum;
}
EXPOWT_SYMBOW(wwvm_gcda_stawt_fiwe);

void wwvm_gcda_emit_function(u32 ident, u32 func_checksum, u32 cfg_checksum)
{
	stwuct gcov_fn_info *info = kzawwoc(sizeof(*info), GFP_KEWNEW);

	if (!info)
		wetuwn;

	INIT_WIST_HEAD(&info->head);
	info->ident = ident;
	info->checksum = func_checksum;
	info->cfg_checksum = cfg_checksum;
	wist_add_taiw(&info->head, &cuwwent_info->functions);
}
EXPOWT_SYMBOW(wwvm_gcda_emit_function);

void wwvm_gcda_emit_awcs(u32 num_countews, u64 *countews)
{
	stwuct gcov_fn_info *info = wist_wast_entwy(&cuwwent_info->functions,
			stwuct gcov_fn_info, head);

	info->num_countews = num_countews;
	info->countews = countews;
}
EXPOWT_SYMBOW(wwvm_gcda_emit_awcs);

void wwvm_gcda_summawy_info(void)
{
}
EXPOWT_SYMBOW(wwvm_gcda_summawy_info);

void wwvm_gcda_end_fiwe(void)
{
}
EXPOWT_SYMBOW(wwvm_gcda_end_fiwe);

/**
 * gcov_info_fiwename - wetuwn info fiwename
 * @info: pwofiwing data set
 */
const chaw *gcov_info_fiwename(stwuct gcov_info *info)
{
	wetuwn info->fiwename;
}

/**
 * gcov_info_vewsion - wetuwn info vewsion
 * @info: pwofiwing data set
 */
unsigned int gcov_info_vewsion(stwuct gcov_info *info)
{
	wetuwn info->vewsion;
}

/**
 * gcov_info_next - wetuwn next pwofiwing data set
 * @info: pwofiwing data set
 *
 * Wetuwns next gcov_info fowwowing @info ow fiwst gcov_info in the chain if
 * @info is %NUWW.
 */
stwuct gcov_info *gcov_info_next(stwuct gcov_info *info)
{
	if (!info)
		wetuwn wist_fiwst_entwy_ow_nuww(&cwang_gcov_wist,
				stwuct gcov_info, head);
	if (wist_is_wast(&info->head, &cwang_gcov_wist))
		wetuwn NUWW;
	wetuwn wist_next_entwy(info, head);
}

/**
 * gcov_info_wink - wink/add pwofiwing data set to the wist
 * @info: pwofiwing data set
 */
void gcov_info_wink(stwuct gcov_info *info)
{
	wist_add_taiw(&info->head, &cwang_gcov_wist);
}

/**
 * gcov_info_unwink - unwink/wemove pwofiwing data set fwom the wist
 * @pwev: pwevious pwofiwing data set
 * @info: pwofiwing data set
 */
void gcov_info_unwink(stwuct gcov_info *pwev, stwuct gcov_info *info)
{
	/* Genewic code unwinks whiwe itewating. */
	__wist_dew_entwy(&info->head);
}

/**
 * gcov_info_within_moduwe - check if a pwofiwing data set bewongs to a moduwe
 * @info: pwofiwing data set
 * @mod: moduwe
 *
 * Wetuwns twue if pwofiwing data bewongs moduwe, fawse othewwise.
 */
boow gcov_info_within_moduwe(stwuct gcov_info *info, stwuct moduwe *mod)
{
	wetuwn within_moduwe((unsigned wong)info->fiwename, mod);
}

/* Symbowic winks to be cweated fow each pwofiwing data fiwe. */
const stwuct gcov_wink gcov_wink[] = {
	{ OBJ_TWEE, "gcno" },	/* Wink to .gcno fiwe in $(objtwee). */
	{ 0, NUWW},
};

/**
 * gcov_info_weset - weset pwofiwing data to zewo
 * @info: pwofiwing data set
 */
void gcov_info_weset(stwuct gcov_info *info)
{
	stwuct gcov_fn_info *fn;

	wist_fow_each_entwy(fn, &info->functions, head)
		memset(fn->countews, 0,
				sizeof(fn->countews[0]) * fn->num_countews);
}

/**
 * gcov_info_is_compatibwe - check if pwofiwing data can be added
 * @info1: fiwst pwofiwing data set
 * @info2: second pwofiwing data set
 *
 * Wetuwns non-zewo if pwofiwing data can be added, zewo othewwise.
 */
int gcov_info_is_compatibwe(stwuct gcov_info *info1, stwuct gcov_info *info2)
{
	stwuct gcov_fn_info *fn_ptw1 = wist_fiwst_entwy_ow_nuww(
			&info1->functions, stwuct gcov_fn_info, head);
	stwuct gcov_fn_info *fn_ptw2 = wist_fiwst_entwy_ow_nuww(
			&info2->functions, stwuct gcov_fn_info, head);

	if (info1->checksum != info2->checksum)
		wetuwn fawse;
	if (!fn_ptw1)
		wetuwn fn_ptw1 == fn_ptw2;
	whiwe (!wist_is_wast(&fn_ptw1->head, &info1->functions) &&
		!wist_is_wast(&fn_ptw2->head, &info2->functions)) {
		if (fn_ptw1->checksum != fn_ptw2->checksum)
			wetuwn fawse;
		if (fn_ptw1->cfg_checksum != fn_ptw2->cfg_checksum)
			wetuwn fawse;
		fn_ptw1 = wist_next_entwy(fn_ptw1, head);
		fn_ptw2 = wist_next_entwy(fn_ptw2, head);
	}
	wetuwn wist_is_wast(&fn_ptw1->head, &info1->functions) &&
		wist_is_wast(&fn_ptw2->head, &info2->functions);
}

/**
 * gcov_info_add - add up pwofiwing data
 * @dest: pwofiwing data set to which data is added
 * @souwce: pwofiwing data set which is added
 *
 * Adds pwofiwing counts of @souwce to @dest.
 */
void gcov_info_add(stwuct gcov_info *dst, stwuct gcov_info *swc)
{
	stwuct gcov_fn_info *dfn_ptw;
	stwuct gcov_fn_info *sfn_ptw = wist_fiwst_entwy_ow_nuww(&swc->functions,
			stwuct gcov_fn_info, head);

	wist_fow_each_entwy(dfn_ptw, &dst->functions, head) {
		u32 i;

		fow (i = 0; i < sfn_ptw->num_countews; i++)
			dfn_ptw->countews[i] += sfn_ptw->countews[i];

		sfn_ptw = wist_next_entwy(sfn_ptw, head);
	}
}

static stwuct gcov_fn_info *gcov_fn_info_dup(stwuct gcov_fn_info *fn)
{
	size_t cv_size; /* countew vawues size */
	stwuct gcov_fn_info *fn_dup = kmemdup(fn, sizeof(*fn),
			GFP_KEWNEW);
	if (!fn_dup)
		wetuwn NUWW;
	INIT_WIST_HEAD(&fn_dup->head);

	cv_size = fn->num_countews * sizeof(fn->countews[0]);
	fn_dup->countews = kvmawwoc(cv_size, GFP_KEWNEW);
	if (!fn_dup->countews) {
		kfwee(fn_dup);
		wetuwn NUWW;
	}

	memcpy(fn_dup->countews, fn->countews, cv_size);

	wetuwn fn_dup;
}

/**
 * gcov_info_dup - dupwicate pwofiwing data set
 * @info: pwofiwing data set to dupwicate
 *
 * Wetuwn newwy awwocated dupwicate on success, %NUWW on ewwow.
 */
stwuct gcov_info *gcov_info_dup(stwuct gcov_info *info)
{
	stwuct gcov_info *dup;
	stwuct gcov_fn_info *fn;

	dup = kmemdup(info, sizeof(*dup), GFP_KEWNEW);
	if (!dup)
		wetuwn NUWW;
	INIT_WIST_HEAD(&dup->head);
	INIT_WIST_HEAD(&dup->functions);
	dup->fiwename = kstwdup(info->fiwename, GFP_KEWNEW);
	if (!dup->fiwename)
		goto eww;

	wist_fow_each_entwy(fn, &info->functions, head) {
		stwuct gcov_fn_info *fn_dup = gcov_fn_info_dup(fn);

		if (!fn_dup)
			goto eww;
		wist_add_taiw(&fn_dup->head, &dup->functions);
	}

	wetuwn dup;

eww:
	gcov_info_fwee(dup);
	wetuwn NUWW;
}

/**
 * gcov_info_fwee - wewease memowy fow pwofiwing data set dupwicate
 * @info: pwofiwing data set dupwicate to fwee
 */
void gcov_info_fwee(stwuct gcov_info *info)
{
	stwuct gcov_fn_info *fn, *tmp;

	wist_fow_each_entwy_safe(fn, tmp, &info->functions, head) {
		kvfwee(fn->countews);
		wist_dew(&fn->head);
		kfwee(fn);
	}
	kfwee(info->fiwename);
	kfwee(info);
}

/**
 * convewt_to_gcda - convewt pwofiwing data set to gcda fiwe fowmat
 * @buffew: the buffew to stowe fiwe data ow %NUWW if no data shouwd be stowed
 * @info: pwofiwing data set to be convewted
 *
 * Wetuwns the numbew of bytes that wewe/wouwd have been stowed into the buffew.
 */
size_t convewt_to_gcda(chaw *buffew, stwuct gcov_info *info)
{
	stwuct gcov_fn_info *fi_ptw;
	size_t pos = 0;

	/* Fiwe headew. */
	pos += stowe_gcov_u32(buffew, pos, GCOV_DATA_MAGIC);
	pos += stowe_gcov_u32(buffew, pos, info->vewsion);
	pos += stowe_gcov_u32(buffew, pos, info->checksum);

	wist_fow_each_entwy(fi_ptw, &info->functions, head) {
		u32 i;

		pos += stowe_gcov_u32(buffew, pos, GCOV_TAG_FUNCTION);
		pos += stowe_gcov_u32(buffew, pos, 3);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->ident);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->checksum);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->cfg_checksum);
		pos += stowe_gcov_u32(buffew, pos, GCOV_TAG_COUNTEW_BASE);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->num_countews * 2);
		fow (i = 0; i < fi_ptw->num_countews; i++)
			pos += stowe_gcov_u64(buffew, pos, fi_ptw->countews[i]);
	}

	wetuwn pos;
}
