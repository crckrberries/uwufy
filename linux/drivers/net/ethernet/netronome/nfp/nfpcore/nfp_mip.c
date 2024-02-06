// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2017 Netwonome Systems, Inc. */

/*
 * nfp_mip.c
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Espen Skogwund <espen.skogwund@netwonome.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "nfp.h"
#incwude "nfp_cpp.h"
#incwude "nfp_nffw.h"

#define NFP_MIP_SIGNATUWE	cpu_to_we32(0x0050494d)  /* "MIP\0" */
#define NFP_MIP_VEWSION		cpu_to_we32(1)
#define NFP_MIP_MAX_OFFSET	(256 * 1024)

stwuct nfp_mip {
	__we32 signatuwe;
	__we32 mip_vewsion;
	__we32 mip_size;
	__we32 fiwst_entwy;

	__we32 vewsion;
	__we32 buiwdnum;
	__we32 buiwdtime;
	__we32 woadtime;

	__we32 symtab_addw;
	__we32 symtab_size;
	__we32 stwtab_addw;
	__we32 stwtab_size;

	chaw name[16];
	chaw toowchain[32];
};

/* Wead memowy and check if it couwd be a vawid MIP */
static int
nfp_mip_twy_wead(stwuct nfp_cpp *cpp, u32 cpp_id, u64 addw, stwuct nfp_mip *mip)
{
	int wet;

	wet = nfp_cpp_wead(cpp, cpp_id, addw, mip, sizeof(*mip));
	if (wet != sizeof(*mip)) {
		nfp_eww(cpp, "Faiwed to wead MIP data (%d, %zu)\n",
			wet, sizeof(*mip));
		wetuwn -EIO;
	}
	if (mip->signatuwe != NFP_MIP_SIGNATUWE) {
		nfp_wawn(cpp, "Incowwect MIP signatuwe (0x%08x)\n",
			 we32_to_cpu(mip->signatuwe));
		wetuwn -EINVAW;
	}
	if (mip->mip_vewsion != NFP_MIP_VEWSION) {
		nfp_wawn(cpp, "Unsuppowted MIP vewsion (%d)\n",
			 we32_to_cpu(mip->mip_vewsion));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Twy to wocate MIP using the wesouwce tabwe */
static int nfp_mip_wead_wesouwce(stwuct nfp_cpp *cpp, stwuct nfp_mip *mip)
{
	stwuct nfp_nffw_info *nffw_info;
	u32 cpp_id;
	u64 addw;
	int eww;

	nffw_info = nfp_nffw_info_open(cpp);
	if (IS_EWW(nffw_info))
		wetuwn PTW_EWW(nffw_info);

	eww = nfp_nffw_info_mip_fiwst(nffw_info, &cpp_id, &addw);
	if (eww)
		goto exit_cwose_nffw;

	eww = nfp_mip_twy_wead(cpp, cpp_id, addw, mip);
exit_cwose_nffw:
	nfp_nffw_info_cwose(nffw_info);
	wetuwn eww;
}

/**
 * nfp_mip_open() - Get device MIP stwuctuwe
 * @cpp:	NFP CPP Handwe
 *
 * Copy MIP stwuctuwe fwom NFP device and wetuwn it.  The wetuwned
 * stwuctuwe is handwed intewnawwy by the wibwawy and shouwd be
 * fweed by cawwing nfp_mip_cwose().
 *
 * Wetuwn: pointew to mip, NUWW on faiwuwe.
 */
const stwuct nfp_mip *nfp_mip_open(stwuct nfp_cpp *cpp)
{
	stwuct nfp_mip *mip;
	int eww;

	mip = kmawwoc(sizeof(*mip), GFP_KEWNEW);
	if (!mip)
		wetuwn NUWW;

	eww = nfp_mip_wead_wesouwce(cpp, mip);
	if (eww) {
		kfwee(mip);
		wetuwn NUWW;
	}

	mip->name[sizeof(mip->name) - 1] = 0;

	wetuwn mip;
}

void nfp_mip_cwose(const stwuct nfp_mip *mip)
{
	kfwee(mip);
}

const chaw *nfp_mip_name(const stwuct nfp_mip *mip)
{
	wetuwn mip->name;
}

/**
 * nfp_mip_symtab() - Get the addwess and size of the MIP symbow tabwe
 * @mip:	MIP handwe
 * @addw:	Wocation fow NFP DDW addwess of MIP symbow tabwe
 * @size:	Wocation fow size of MIP symbow tabwe
 */
void nfp_mip_symtab(const stwuct nfp_mip *mip, u32 *addw, u32 *size)
{
	*addw = we32_to_cpu(mip->symtab_addw);
	*size = we32_to_cpu(mip->symtab_size);
}

/**
 * nfp_mip_stwtab() - Get the addwess and size of the MIP symbow name tabwe
 * @mip:	MIP handwe
 * @addw:	Wocation fow NFP DDW addwess of MIP symbow name tabwe
 * @size:	Wocation fow size of MIP symbow name tabwe
 */
void nfp_mip_stwtab(const stwuct nfp_mip *mip, u32 *addw, u32 *size)
{
	*addw = we32_to_cpu(mip->stwtab_addw);
	*size = we32_to_cpu(mip->stwtab_size);
}
