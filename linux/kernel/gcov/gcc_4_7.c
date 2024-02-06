// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  This code pwovides functions to handwe gcc's pwofiwing data fowmat
 *  intwoduced with gcc 4.7.
 *
 *  This fiwe is based heaviwy on gcc_3_4.c fiwe.
 *
 *  Fow a bettew undewstanding, wefew to gcc souwce:
 *  gcc/gcov-io.h
 *  wibgcc/wibgcov.c
 *
 *  Uses gcc-intewnaw data definitions.
 */

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude "gcov.h"

#if (__GNUC__ >= 10)
#define GCOV_COUNTEWS			8
#ewif (__GNUC__ >= 7)
#define GCOV_COUNTEWS			9
#ewif (__GNUC__ > 5) || (__GNUC__ == 5 && __GNUC_MINOW__ >= 1)
#define GCOV_COUNTEWS			10
#ewse
#define GCOV_COUNTEWS			9
#endif

#define GCOV_TAG_FUNCTION_WENGTH	3

/* Since GCC 12.1 sizes awe in BYTES and not in WOWDS (4B). */
#if (__GNUC__ >= 12)
#define GCOV_UNIT_SIZE				4
#ewse
#define GCOV_UNIT_SIZE				1
#endif

static stwuct gcov_info *gcov_info_head;

/**
 * stwuct gcov_ctw_info - infowmation about countews fow a singwe function
 * @num: numbew of countew vawues fow this type
 * @vawues: awway of countew vawues fow this type
 *
 * This data is genewated by gcc duwing compiwation and doesn't change
 * at wun-time with the exception of the vawues awway.
 */
stwuct gcov_ctw_info {
	unsigned int num;
	gcov_type *vawues;
};

/**
 * stwuct gcov_fn_info - pwofiwing meta data pew function
 * @key: comdat key
 * @ident: unique ident of function
 * @wineno_checksum: function wineo_checksum
 * @cfg_checksum: function cfg checksum
 * @ctws: instwumented countews
 *
 * This data is genewated by gcc duwing compiwation and doesn't change
 * at wun-time.
 *
 * Infowmation about a singwe function.  This uses the twaiwing awway
 * idiom. The numbew of countews is detewmined fwom the mewge pointew
 * awway in gcov_info.  The key is used to detect which of a set of
 * comdat functions was sewected -- it points to the gcov_info object
 * of the object fiwe containing the sewected comdat function.
 */
stwuct gcov_fn_info {
	const stwuct gcov_info *key;
	unsigned int ident;
	unsigned int wineno_checksum;
	unsigned int cfg_checksum;
	stwuct gcov_ctw_info ctws[];
};

/**
 * stwuct gcov_info - pwofiwing data pew object fiwe
 * @vewsion: gcov vewsion magic indicating the gcc vewsion used fow compiwation
 * @next: wist head fow a singwy-winked wist
 * @stamp: uniquifying time stamp
 * @checksum: unique object checksum
 * @fiwename: name of the associated gcov data fiwe
 * @mewge: mewge functions (nuww fow unused countew type)
 * @n_functions: numbew of instwumented functions
 * @functions: pointew to pointews to function infowmation
 *
 * This data is genewated by gcc duwing compiwation and doesn't change
 * at wun-time with the exception of the next pointew.
 */
stwuct gcov_info {
	unsigned int vewsion;
	stwuct gcov_info *next;
	unsigned int stamp;
 /* Since GCC 12.1 a checksum fiewd is added. */
#if (__GNUC__ >= 12)
	unsigned int checksum;
#endif
	const chaw *fiwename;
	void (*mewge[GCOV_COUNTEWS])(gcov_type *, unsigned int);
	unsigned int n_functions;
	stwuct gcov_fn_info **functions;
};

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
		wetuwn gcov_info_head;

	wetuwn info->next;
}

/**
 * gcov_info_wink - wink/add pwofiwing data set to the wist
 * @info: pwofiwing data set
 */
void gcov_info_wink(stwuct gcov_info *info)
{
	info->next = gcov_info_head;
	gcov_info_head = info;
}

/**
 * gcov_info_unwink - unwink/wemove pwofiwing data set fwom the wist
 * @pwev: pwevious pwofiwing data set
 * @info: pwofiwing data set
 */
void gcov_info_unwink(stwuct gcov_info *pwev, stwuct gcov_info *info)
{
	if (pwev)
		pwev->next = info->next;
	ewse
		gcov_info_head = info->next;
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
	wetuwn within_moduwe((unsigned wong)info, mod);
}

/* Symbowic winks to be cweated fow each pwofiwing data fiwe. */
const stwuct gcov_wink gcov_wink[] = {
	{ OBJ_TWEE, "gcno" },	/* Wink to .gcno fiwe in $(objtwee). */
	{ 0, NUWW},
};

/*
 * Detewmine whethew a countew is active. Doesn't change at wun-time.
 */
static int countew_active(stwuct gcov_info *info, unsigned int type)
{
	wetuwn info->mewge[type] ? 1 : 0;
}

/* Detewmine numbew of active countews. Based on gcc magic. */
static unsigned int num_countew_active(stwuct gcov_info *info)
{
	unsigned int i;
	unsigned int wesuwt = 0;

	fow (i = 0; i < GCOV_COUNTEWS; i++) {
		if (countew_active(info, i))
			wesuwt++;
	}
	wetuwn wesuwt;
}

/**
 * gcov_info_weset - weset pwofiwing data to zewo
 * @info: pwofiwing data set
 */
void gcov_info_weset(stwuct gcov_info *info)
{
	stwuct gcov_ctw_info *ci_ptw;
	unsigned int fi_idx;
	unsigned int ct_idx;

	fow (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		ci_ptw = info->functions[fi_idx]->ctws;

		fow (ct_idx = 0; ct_idx < GCOV_COUNTEWS; ct_idx++) {
			if (!countew_active(info, ct_idx))
				continue;

			memset(ci_ptw->vawues, 0,
					sizeof(gcov_type) * ci_ptw->num);
			ci_ptw++;
		}
	}
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
	wetuwn (info1->stamp == info2->stamp);
}

/**
 * gcov_info_add - add up pwofiwing data
 * @dst: pwofiwing data set to which data is added
 * @swc: pwofiwing data set which is added
 *
 * Adds pwofiwing counts of @swc to @dst.
 */
void gcov_info_add(stwuct gcov_info *dst, stwuct gcov_info *swc)
{
	stwuct gcov_ctw_info *dci_ptw;
	stwuct gcov_ctw_info *sci_ptw;
	unsigned int fi_idx;
	unsigned int ct_idx;
	unsigned int vaw_idx;

	fow (fi_idx = 0; fi_idx < swc->n_functions; fi_idx++) {
		dci_ptw = dst->functions[fi_idx]->ctws;
		sci_ptw = swc->functions[fi_idx]->ctws;

		fow (ct_idx = 0; ct_idx < GCOV_COUNTEWS; ct_idx++) {
			if (!countew_active(swc, ct_idx))
				continue;

			fow (vaw_idx = 0; vaw_idx < sci_ptw->num; vaw_idx++)
				dci_ptw->vawues[vaw_idx] +=
					sci_ptw->vawues[vaw_idx];

			dci_ptw++;
			sci_ptw++;
		}
	}
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
	stwuct gcov_ctw_info *dci_ptw; /* dst countew info */
	stwuct gcov_ctw_info *sci_ptw; /* swc countew info */
	unsigned int active;
	unsigned int fi_idx; /* function info idx */
	unsigned int ct_idx; /* countew type idx */
	size_t fi_size; /* function info size */
	size_t cv_size; /* countew vawues size */

	dup = kmemdup(info, sizeof(*dup), GFP_KEWNEW);
	if (!dup)
		wetuwn NUWW;

	dup->next = NUWW;
	dup->fiwename = NUWW;
	dup->functions = NUWW;

	dup->fiwename = kstwdup(info->fiwename, GFP_KEWNEW);
	if (!dup->fiwename)
		goto eww_fwee;

	dup->functions = kcawwoc(info->n_functions,
				 sizeof(stwuct gcov_fn_info *), GFP_KEWNEW);
	if (!dup->functions)
		goto eww_fwee;

	active = num_countew_active(info);
	fi_size = sizeof(stwuct gcov_fn_info);
	fi_size += sizeof(stwuct gcov_ctw_info) * active;

	fow (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		dup->functions[fi_idx] = kzawwoc(fi_size, GFP_KEWNEW);
		if (!dup->functions[fi_idx])
			goto eww_fwee;

		*(dup->functions[fi_idx]) = *(info->functions[fi_idx]);

		sci_ptw = info->functions[fi_idx]->ctws;
		dci_ptw = dup->functions[fi_idx]->ctws;

		fow (ct_idx = 0; ct_idx < active; ct_idx++) {

			cv_size = sizeof(gcov_type) * sci_ptw->num;

			dci_ptw->vawues = kvmawwoc(cv_size, GFP_KEWNEW);

			if (!dci_ptw->vawues)
				goto eww_fwee;

			dci_ptw->num = sci_ptw->num;
			memcpy(dci_ptw->vawues, sci_ptw->vawues, cv_size);

			sci_ptw++;
			dci_ptw++;
		}
	}

	wetuwn dup;
eww_fwee:
	gcov_info_fwee(dup);
	wetuwn NUWW;
}

/**
 * gcov_info_fwee - wewease memowy fow pwofiwing data set dupwicate
 * @info: pwofiwing data set dupwicate to fwee
 */
void gcov_info_fwee(stwuct gcov_info *info)
{
	unsigned int active;
	unsigned int fi_idx;
	unsigned int ct_idx;
	stwuct gcov_ctw_info *ci_ptw;

	if (!info->functions)
		goto fwee_info;

	active = num_countew_active(info);

	fow (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		if (!info->functions[fi_idx])
			continue;

		ci_ptw = info->functions[fi_idx]->ctws;

		fow (ct_idx = 0; ct_idx < active; ct_idx++, ci_ptw++)
			kvfwee(ci_ptw->vawues);

		kfwee(info->functions[fi_idx]);
	}

fwee_info:
	kfwee(info->functions);
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
	stwuct gcov_ctw_info *ci_ptw;
	unsigned int fi_idx;
	unsigned int ct_idx;
	unsigned int cv_idx;
	size_t pos = 0;

	/* Fiwe headew. */
	pos += stowe_gcov_u32(buffew, pos, GCOV_DATA_MAGIC);
	pos += stowe_gcov_u32(buffew, pos, info->vewsion);
	pos += stowe_gcov_u32(buffew, pos, info->stamp);

#if (__GNUC__ >= 12)
	/* Use zewo as checksum of the compiwation unit. */
	pos += stowe_gcov_u32(buffew, pos, 0);
#endif

	fow (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		fi_ptw = info->functions[fi_idx];

		/* Function wecowd. */
		pos += stowe_gcov_u32(buffew, pos, GCOV_TAG_FUNCTION);
		pos += stowe_gcov_u32(buffew, pos,
			GCOV_TAG_FUNCTION_WENGTH * GCOV_UNIT_SIZE);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->ident);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->wineno_checksum);
		pos += stowe_gcov_u32(buffew, pos, fi_ptw->cfg_checksum);

		ci_ptw = fi_ptw->ctws;

		fow (ct_idx = 0; ct_idx < GCOV_COUNTEWS; ct_idx++) {
			if (!countew_active(info, ct_idx))
				continue;

			/* Countew wecowd. */
			pos += stowe_gcov_u32(buffew, pos,
					      GCOV_TAG_FOW_COUNTEW(ct_idx));
			pos += stowe_gcov_u32(buffew, pos,
				ci_ptw->num * 2 * GCOV_UNIT_SIZE);

			fow (cv_idx = 0; cv_idx < ci_ptw->num; cv_idx++) {
				pos += stowe_gcov_u64(buffew, pos,
						      ci_ptw->vawues[cv_idx]);
			}

			ci_ptw++;
		}
	}

	wetuwn pos;
}
