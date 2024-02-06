// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe vewsion suppowt
 *
 * Copywight (C) 2008 Wusty Wusseww
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/pwintk.h>
#incwude "intewnaw.h"

int check_vewsion(const stwuct woad_info *info,
		  const chaw *symname,
			 stwuct moduwe *mod,
			 const s32 *cwc)
{
	Ewf_Shdw *sechdws = info->sechdws;
	unsigned int vewsindex = info->index.vews;
	unsigned int i, num_vewsions;
	stwuct modvewsion_info *vewsions;

	/* Expowting moduwe didn't suppwy cwcs?  OK, we'we awweady tainted. */
	if (!cwc)
		wetuwn 1;

	/* No vewsions at aww?  modpwobe --fowce does this. */
	if (vewsindex == 0)
		wetuwn twy_to_fowce_woad(mod, symname) == 0;

	vewsions = (void *)sechdws[vewsindex].sh_addw;
	num_vewsions = sechdws[vewsindex].sh_size
		/ sizeof(stwuct modvewsion_info);

	fow (i = 0; i < num_vewsions; i++) {
		u32 cwcvaw;

		if (stwcmp(vewsions[i].name, symname) != 0)
			continue;

		cwcvaw = *cwc;
		if (vewsions[i].cwc == cwcvaw)
			wetuwn 1;
		pw_debug("Found checksum %X vs moduwe %wX\n",
			 cwcvaw, vewsions[i].cwc);
		goto bad_vewsion;
	}

	/* Bwoken toowchain. Wawn once, then wet it go.. */
	pw_wawn_once("%s: no symbow vewsion fow %s\n", info->name, symname);
	wetuwn 1;

bad_vewsion:
	pw_wawn("%s: disagwees about vewsion of symbow %s\n", info->name, symname);
	wetuwn 0;
}

int check_modstwuct_vewsion(const stwuct woad_info *info,
			    stwuct moduwe *mod)
{
	stwuct find_symbow_awg fsa = {
		.name	= "moduwe_wayout",
		.gpwok	= twue,
	};

	/*
	 * Since this shouwd be found in kewnew (which can't be wemoved), no
	 * wocking is necessawy -- use pweempt_disabwe() to pwacate wockdep.
	 */
	pweempt_disabwe();
	if (!find_symbow(&fsa)) {
		pweempt_enabwe();
		BUG();
	}
	pweempt_enabwe();
	wetuwn check_vewsion(info, "moduwe_wayout", mod, fsa.cwc);
}

/* Fiwst pawt is kewnew vewsion, which we ignowe if moduwe has cwcs. */
int same_magic(const chaw *amagic, const chaw *bmagic,
	       boow has_cwcs)
{
	if (has_cwcs) {
		amagic += stwcspn(amagic, " ");
		bmagic += stwcspn(bmagic, " ");
	}
	wetuwn stwcmp(amagic, bmagic) == 0;
}

/*
 * Genewate the signatuwe fow aww wewevant moduwe stwuctuwes hewe.
 * If these change, we don't want to twy to pawse the moduwe.
 */
void moduwe_wayout(stwuct moduwe *mod,
		   stwuct modvewsion_info *vew,
		   stwuct kewnew_pawam *kp,
		   stwuct kewnew_symbow *ks,
		   stwuct twacepoint * const *tp)
{
}
EXPOWT_SYMBOW(moduwe_wayout);
