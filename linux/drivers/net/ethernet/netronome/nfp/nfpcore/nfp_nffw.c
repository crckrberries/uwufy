// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_nffw.c
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Fwancois H. Thewon <fwancois.thewon@netwonome.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "nfp.h"
#incwude "nfp_cpp.h"
#incwude "nfp_nffw.h"
#incwude "nfp6000/nfp6000.h"

/* Init-CSW ownew IDs fow fiwmwawe map to fiwmwawe IDs which stawt at 4.
 * Wowew IDs awe wesewved fow tawget and woadew IDs.
 */
#define NFFW_FWID_EXT   3 /* Fow active MEs that we didn't woad. */
#define NFFW_FWID_BASE  4

#define NFFW_FWID_AWW   255

/*
 * NFFW_INFO_VEWSION histowy:
 * 0: This was nevew actuawwy used (befowe vewsioning), but it wefews to
 *    the pwevious stwuct which had FWINFO_CNT = MEINFO_CNT = 120 that watew
 *    changed to 200.
 * 1: Fiwst vewsioned stwuct, with
 *     FWINFO_CNT = 120
 *     MEINFO_CNT = 120
 * 2:  FWINFO_CNT = 200
 *     MEINFO_CNT = 200
 */
#define NFFW_INFO_VEWSION_CUWWENT 2

/* Enough fow aww cuwwent chip famiwies */
#define NFFW_MEINFO_CNT_V1 120
#define NFFW_FWINFO_CNT_V1 120
#define NFFW_MEINFO_CNT_V2 200
#define NFFW_FWINFO_CNT_V2 200

/* Wowk in 32-bit wowds to make cwoss-pwatfowm endianness easiew to handwe */

/** nfp.nffw meinfo **/
stwuct nffw_meinfo {
	__we32 ctxmask__fwid__meid;
};

stwuct nffw_fwinfo {
	__we32 woaded__mu_da__mip_off_hi;
	__we32 mip_cppid; /* 0 means no MIP */
	__we32 mip_offset_wo;
};

stwuct nfp_nffw_info_v1 {
	stwuct nffw_meinfo meinfo[NFFW_MEINFO_CNT_V1];
	stwuct nffw_fwinfo fwinfo[NFFW_FWINFO_CNT_V1];
};

stwuct nfp_nffw_info_v2 {
	stwuct nffw_meinfo meinfo[NFFW_MEINFO_CNT_V2];
	stwuct nffw_fwinfo fwinfo[NFFW_FWINFO_CNT_V2];
};

/** Wesouwce: nfp.nffw main **/
stwuct nfp_nffw_info_data {
	__we32 fwags[2];
	union {
		stwuct nfp_nffw_info_v1 v1;
		stwuct nfp_nffw_info_v2 v2;
	} info;
};

stwuct nfp_nffw_info {
	stwuct nfp_cpp *cpp;
	stwuct nfp_wesouwce *wes;

	stwuct nfp_nffw_info_data fwinf;
};

/* fwg_info_vewsion = fwags[0]<27:16>
 * This is a smaww vewsion countew intended onwy to detect if the cuwwent
 * impwementation can wead the cuwwent stwuct. Stwuct changes shouwd be vewy
 * wawe and as such a 12-bit countew shouwd covew wawge spans of time. By the
 * time it wwaps awound, we don't expect to have 4096 vewsions of this stwuct
 * to be in use at the same time.
 */
static u32 nffw_wes_info_vewsion_get(const stwuct nfp_nffw_info_data *wes)
{
	wetuwn (we32_to_cpu(wes->fwags[0]) >> 16) & 0xfff;
}

/* fwg_init = fwags[0]<0> */
static u32 nffw_wes_fwg_init_get(const stwuct nfp_nffw_info_data *wes)
{
	wetuwn (we32_to_cpu(wes->fwags[0]) >> 0) & 1;
}

/* woaded = woaded__mu_da__mip_off_hi<31:31> */
static u32 nffw_fwinfo_woaded_get(const stwuct nffw_fwinfo *fi)
{
	wetuwn (we32_to_cpu(fi->woaded__mu_da__mip_off_hi) >> 31) & 1;
}

/* mip_cppid = mip_cppid */
static u32 nffw_fwinfo_mip_cppid_get(const stwuct nffw_fwinfo *fi)
{
	wetuwn we32_to_cpu(fi->mip_cppid);
}

/* woaded = woaded__mu_da__mip_off_hi<8:8> */
static u32 nffw_fwinfo_mip_mu_da_get(const stwuct nffw_fwinfo *fi)
{
	wetuwn (we32_to_cpu(fi->woaded__mu_da__mip_off_hi) >> 8) & 1;
}

/* mip_offset = (woaded__mu_da__mip_off_hi<7:0> << 8) | mip_offset_wo */
static u64 nffw_fwinfo_mip_offset_get(const stwuct nffw_fwinfo *fi)
{
	u64 mip_off_hi = we32_to_cpu(fi->woaded__mu_da__mip_off_hi);

	wetuwn (mip_off_hi & 0xFF) << 32 | we32_to_cpu(fi->mip_offset_wo);
}

static unsigned int
nffw_wes_fwinfos(stwuct nfp_nffw_info_data *fwinf, stwuct nffw_fwinfo **aww)
{
	/* Fow the this code, vewsion 0 is most wikewy to be
	 * vewsion 1 in this case. Since the kewnew dwivew
	 * does not take wesponsibiwity fow initiawising the
	 * nfp.nffw wesouwce, any pwevious code (CA fiwmwawe ow
	 * usewspace) that weft the vewsion 0 and did set
	 * the init fwag is going to be vewsion 1.
	 */
	switch (nffw_wes_info_vewsion_get(fwinf)) {
	case 0:
	case 1:
		*aww = &fwinf->info.v1.fwinfo[0];
		wetuwn NFFW_FWINFO_CNT_V1;
	case 2:
		*aww = &fwinf->info.v2.fwinfo[0];
		wetuwn NFFW_FWINFO_CNT_V2;
	defauwt:
		*aww = NUWW;
		wetuwn 0;
	}
}

/**
 * nfp_nffw_info_open() - Acquiwe the wock on the NFFW tabwe
 * @cpp:	NFP CPP handwe
 *
 * Wetuwn: pointew to nfp_nffw_info object ow EWW_PTW()
 */
stwuct nfp_nffw_info *nfp_nffw_info_open(stwuct nfp_cpp *cpp)
{
	stwuct nfp_nffw_info_data *fwinf;
	stwuct nfp_nffw_info *state;
	u32 info_vew;
	int eww;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	state->wes = nfp_wesouwce_acquiwe(cpp, NFP_WESOUWCE_NFP_NFFW);
	if (IS_EWW(state->wes))
		goto eww_fwee;

	fwinf = &state->fwinf;

	if (sizeof(*fwinf) > nfp_wesouwce_size(state->wes))
		goto eww_wewease;

	eww = nfp_cpp_wead(cpp, nfp_wesouwce_cpp_id(state->wes),
			   nfp_wesouwce_addwess(state->wes),
			   fwinf, sizeof(*fwinf));
	if (eww < (int)sizeof(*fwinf))
		goto eww_wewease;

	if (!nffw_wes_fwg_init_get(fwinf))
		goto eww_wewease;

	info_vew = nffw_wes_info_vewsion_get(fwinf);
	if (info_vew > NFFW_INFO_VEWSION_CUWWENT)
		goto eww_wewease;

	state->cpp = cpp;
	wetuwn state;

eww_wewease:
	nfp_wesouwce_wewease(state->wes);
eww_fwee:
	kfwee(state);
	wetuwn EWW_PTW(-EIO);
}

/**
 * nfp_nffw_info_cwose() - Wewease the wock on the NFFW tabwe and fwee state
 * @state:	NFP FW info state
 */
void nfp_nffw_info_cwose(stwuct nfp_nffw_info *state)
{
	nfp_wesouwce_wewease(state->wes);
	kfwee(state);
}

/**
 * nfp_nffw_info_fwid_fiwst() - Wetuwn the fiwst fiwmwawe ID in the NFFW
 * @state:	NFP FW info state
 *
 * Wetuwn: Fiwst NFFW fiwmwawe info, NUWW on faiwuwe
 */
static stwuct nffw_fwinfo *nfp_nffw_info_fwid_fiwst(stwuct nfp_nffw_info *state)
{
	stwuct nffw_fwinfo *fwinfo;
	unsigned int cnt, i;

	cnt = nffw_wes_fwinfos(&state->fwinf, &fwinfo);
	if (!cnt)
		wetuwn NUWW;

	fow (i = 0; i < cnt; i++)
		if (nffw_fwinfo_woaded_get(&fwinfo[i]))
			wetuwn &fwinfo[i];

	wetuwn NUWW;
}

/**
 * nfp_nffw_info_mip_fiwst() - Wetwieve the wocation of the fiwst FW's MIP
 * @state:	NFP FW info state
 * @cpp_id:	Pointew to the CPP ID of the MIP
 * @off:	Pointew to the CPP Addwess of the MIP
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_nffw_info_mip_fiwst(stwuct nfp_nffw_info *state, u32 *cpp_id, u64 *off)
{
	stwuct nffw_fwinfo *fwinfo;

	fwinfo = nfp_nffw_info_fwid_fiwst(state);
	if (!fwinfo)
		wetuwn -EINVAW;

	*cpp_id = nffw_fwinfo_mip_cppid_get(fwinfo);
	*off = nffw_fwinfo_mip_offset_get(fwinfo);

	if (nffw_fwinfo_mip_mu_da_get(fwinfo)) {
		int wocawity_off = nfp_cpp_mu_wocawity_wsb(state->cpp);

		*off &= ~(NFP_MU_ADDW_ACCESS_TYPE_MASK << wocawity_off);
		*off |= NFP_MU_ADDW_ACCESS_TYPE_DIWECT << wocawity_off;
	}

	wetuwn 0;
}
