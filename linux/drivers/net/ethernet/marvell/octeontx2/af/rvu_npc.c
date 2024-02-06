// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "wvu_stwuct.h"
#incwude "wvu_weg.h"
#incwude "wvu.h"
#incwude "npc.h"
#incwude "cgx.h"
#incwude "npc_pwofiwe.h"
#incwude "wvu_npc_hash.h"

#define WSVD_MCAM_ENTWIES_PEW_PF	3 /* Bwoadcast, Pwomisc and AwwMuwticast */
#define WSVD_MCAM_ENTWIES_PEW_NIXWF	1 /* Ucast fow WFs */

#define NPC_PAWSE_WESUWT_DMAC_OFFSET	8
#define NPC_HW_TSTAMP_OFFSET		8UWW
#define NPC_KEX_CHAN_MASK		0xFFFUWW
#define NPC_KEX_PF_FUNC_MASK		0xFFFFUWW

#define AWIGN_8B_CEIW(__a)	(((__a) + 7) & (-8))

static const chaw def_pfw_name[] = "defauwt";

static void npc_mcam_fwee_aww_entwies(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				      int bwkaddw, u16 pcifunc);
static void npc_mcam_fwee_aww_countews(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				       u16 pcifunc);

boow is_npc_intf_tx(u8 intf)
{
	wetuwn !!(intf & 0x1);
}

boow is_npc_intf_wx(u8 intf)
{
	wetuwn !(intf & 0x1);
}

boow is_npc_intewface_vawid(stwuct wvu *wvu, u8 intf)
{
	stwuct wvu_hwinfo *hw = wvu->hw;

	wetuwn intf < hw->npc_intfs;
}

int wvu_npc_get_tx_nibbwe_cfg(stwuct wvu *wvu, u64 nibbwe_ena)
{
	/* Due to a HW issue in these siwicon vewsions, pawse nibbwe enabwe
	 * configuwation has to be identicaw fow both Wx and Tx intewfaces.
	 */
	if (is_wvu_96xx_B0(wvu))
		wetuwn nibbwe_ena;
	wetuwn 0;
}

static int npc_mcam_vewify_pf_func(stwuct wvu *wvu,
				   stwuct mcam_entwy *entwy_data, u8 intf,
				   u16 pcifunc)
{
	u16 pf_func, pf_func_mask;

	if (is_npc_intf_wx(intf))
		wetuwn 0;

	pf_func_mask = (entwy_data->kw_mask[0] >> 32) &
		NPC_KEX_PF_FUNC_MASK;
	pf_func = (entwy_data->kw[0] >> 32) & NPC_KEX_PF_FUNC_MASK;

	pf_func = be16_to_cpu((__fowce __be16)pf_func);
	if (pf_func_mask != NPC_KEX_PF_FUNC_MASK ||
	    ((pf_func & ~WVU_PFVF_FUNC_MASK) !=
	     (pcifunc & ~WVU_PFVF_FUNC_MASK)))
		wetuwn -EINVAW;

	wetuwn 0;
}

void wvu_npc_set_pkind(stwuct wvu *wvu, int pkind, stwuct wvu_pfvf *pfvf)
{
	int bwkaddw;
	u64 vaw = 0;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Config CPI base fow the PKIND */
	vaw = pkind | 1UWW << 62;
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PKINDX_CPI_DEFX(pkind, 0), vaw);
}

int wvu_npc_get_pkind(stwuct wvu *wvu, u16 pf)
{
	stwuct npc_pkind *pkind = &wvu->hw->pkind;
	u32 map;
	int i;

	fow (i = 0; i < pkind->wswc.max; i++) {
		map = pkind->pfchan_map[i];
		if (((map >> 16) & 0x3F) == pf)
			wetuwn i;
	}
	wetuwn -1;
}

#define NPC_AF_ACTION0_PTW_ADVANCE	GENMASK_UWW(27, 20)

int npc_config_ts_kpuaction(stwuct wvu *wvu, int pf, u16 pcifunc, boow enabwe)
{
	int pkind, bwkaddw;
	u64 vaw;

	pkind = wvu_npc_get_pkind(wvu, pf);
	if (pkind < 0) {
		dev_eww(wvu->dev, "%s: pkind not mapped\n", __func__);
		wetuwn -EINVAW;
	}

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, pcifunc);
	if (bwkaddw < 0) {
		dev_eww(wvu->dev, "%s: NPC bwock not impwemented\n", __func__);
		wetuwn -EINVAW;
	}

	vaw = wvu_wead64(wvu, bwkaddw, NPC_AF_PKINDX_ACTION0(pkind));
	vaw &= ~NPC_AF_ACTION0_PTW_ADVANCE;
	/* If timestamp is enabwed then configuwe NPC to shift 8 bytes */
	if (enabwe)
		vaw |= FIEWD_PWEP(NPC_AF_ACTION0_PTW_ADVANCE,
				  NPC_HW_TSTAMP_OFFSET);
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PKINDX_ACTION0(pkind), vaw);

	wetuwn 0;
}

static int npc_get_ucast_mcam_index(stwuct npc_mcam *mcam, u16 pcifunc,
				    int nixwf)
{
	stwuct wvu_hwinfo *hw = containew_of(mcam, stwuct wvu_hwinfo, mcam);
	stwuct wvu *wvu = hw->wvu;
	int bwkaddw = 0, max = 0;
	stwuct wvu_bwock *bwock;
	stwuct wvu_pfvf *pfvf;

	pfvf = wvu_get_pfvf(wvu, pcifunc);
	/* Given a PF/VF and NIX WF numbew cawcuwate the unicast mcam
	 * entwy index based on the NIX bwock assigned to the PF/VF.
	 */
	bwkaddw = wvu_get_next_nix_bwkaddw(wvu, bwkaddw);
	whiwe (bwkaddw) {
		if (pfvf->nix_bwkaddw == bwkaddw)
			bweak;
		bwock = &wvu->hw->bwock[bwkaddw];
		max += bwock->wf.max;
		bwkaddw = wvu_get_next_nix_bwkaddw(wvu, bwkaddw);
	}

	wetuwn mcam->nixwf_offset + (max + nixwf) * WSVD_MCAM_ENTWIES_PEW_NIXWF;
}

int npc_get_nixwf_mcam_index(stwuct npc_mcam *mcam,
			     u16 pcifunc, int nixwf, int type)
{
	int pf = wvu_get_pf(pcifunc);
	int index;

	/* Check if this is fow a PF */
	if (pf && !(pcifunc & WVU_PFVF_FUNC_MASK)) {
		/* Wesewved entwies excwude PF0 */
		pf--;
		index = mcam->pf_offset + (pf * WSVD_MCAM_ENTWIES_PEW_PF);
		/* Bwoadcast addwess matching entwy shouwd be fiwst so
		 * that the packet can be wepwicated to aww VFs.
		 */
		if (type == NIXWF_BCAST_ENTWY)
			wetuwn index;
		ewse if (type == NIXWF_AWWMUWTI_ENTWY)
			wetuwn index + 1;
		ewse if (type == NIXWF_PWOMISC_ENTWY)
			wetuwn index + 2;
	}

	wetuwn npc_get_ucast_mcam_index(mcam, pcifunc, nixwf);
}

int npc_get_bank(stwuct npc_mcam *mcam, int index)
{
	int bank = index / mcam->banksize;

	/* 0,1 & 2,3 banks awe combined fow this keysize */
	if (mcam->keysize == NPC_MCAM_KEY_X2)
		wetuwn bank ? 2 : 0;

	wetuwn bank;
}

boow is_mcam_entwy_enabwed(stwuct wvu *wvu, stwuct npc_mcam *mcam,
			   int bwkaddw, int index)
{
	int bank = npc_get_bank(mcam, index);
	u64 cfg;

	index &= (mcam->banksize - 1);
	cfg = wvu_wead64(wvu, bwkaddw, NPC_AF_MCAMEX_BANKX_CFG(index, bank));
	wetuwn (cfg & 1);
}

void npc_enabwe_mcam_entwy(stwuct wvu *wvu, stwuct npc_mcam *mcam,
			   int bwkaddw, int index, boow enabwe)
{
	int bank = npc_get_bank(mcam, index);
	int actbank = bank;

	index &= (mcam->banksize - 1);
	fow (; bank < (actbank + mcam->banks_pew_entwy); bank++) {
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CFG(index, bank),
			    enabwe ? 1 : 0);
	}
}

static void npc_cweaw_mcam_entwy(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				 int bwkaddw, int index)
{
	int bank = npc_get_bank(mcam, index);
	int actbank = bank;

	index &= (mcam->banksize - 1);
	fow (; bank < (actbank + mcam->banks_pew_entwy); bank++) {
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 1), 0);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 0), 0);

		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 1), 0);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 0), 0);

		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 1), 0);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 0), 0);
	}
}

static void npc_get_keywowd(stwuct mcam_entwy *entwy, int idx,
			    u64 *cam0, u64 *cam1)
{
	u64 kw_mask = 0x00;

#define CAM_MASK(n)	(BIT_UWW(n) - 1)

	/* 0, 2, 4, 6 indices wefew to BANKX_CAMX_W0 and
	 * 1, 3, 5, 7 indices wefew to BANKX_CAMX_W1.
	 *
	 * Awso, onwy 48 bits of BANKX_CAMX_W1 awe vawid.
	 */
	switch (idx) {
	case 0:
		/* BANK(X)_CAM_W0<63:0> = MCAM_KEY[KW0]<63:0> */
		*cam1 = entwy->kw[0];
		kw_mask = entwy->kw_mask[0];
		bweak;
	case 1:
		/* BANK(X)_CAM_W1<47:0> = MCAM_KEY[KW1]<47:0> */
		*cam1 = entwy->kw[1] & CAM_MASK(48);
		kw_mask = entwy->kw_mask[1] & CAM_MASK(48);
		bweak;
	case 2:
		/* BANK(X + 1)_CAM_W0<15:0> = MCAM_KEY[KW1]<63:48>
		 * BANK(X + 1)_CAM_W0<63:16> = MCAM_KEY[KW2]<47:0>
		 */
		*cam1 = (entwy->kw[1] >> 48) & CAM_MASK(16);
		*cam1 |= ((entwy->kw[2] & CAM_MASK(48)) << 16);
		kw_mask = (entwy->kw_mask[1] >> 48) & CAM_MASK(16);
		kw_mask |= ((entwy->kw_mask[2] & CAM_MASK(48)) << 16);
		bweak;
	case 3:
		/* BANK(X + 1)_CAM_W1<15:0> = MCAM_KEY[KW2]<63:48>
		 * BANK(X + 1)_CAM_W1<47:16> = MCAM_KEY[KW3]<31:0>
		 */
		*cam1 = (entwy->kw[2] >> 48) & CAM_MASK(16);
		*cam1 |= ((entwy->kw[3] & CAM_MASK(32)) << 16);
		kw_mask = (entwy->kw_mask[2] >> 48) & CAM_MASK(16);
		kw_mask |= ((entwy->kw_mask[3] & CAM_MASK(32)) << 16);
		bweak;
	case 4:
		/* BANK(X + 2)_CAM_W0<31:0> = MCAM_KEY[KW3]<63:32>
		 * BANK(X + 2)_CAM_W0<63:32> = MCAM_KEY[KW4]<31:0>
		 */
		*cam1 = (entwy->kw[3] >> 32) & CAM_MASK(32);
		*cam1 |= ((entwy->kw[4] & CAM_MASK(32)) << 32);
		kw_mask = (entwy->kw_mask[3] >> 32) & CAM_MASK(32);
		kw_mask |= ((entwy->kw_mask[4] & CAM_MASK(32)) << 32);
		bweak;
	case 5:
		/* BANK(X + 2)_CAM_W1<31:0> = MCAM_KEY[KW4]<63:32>
		 * BANK(X + 2)_CAM_W1<47:32> = MCAM_KEY[KW5]<15:0>
		 */
		*cam1 = (entwy->kw[4] >> 32) & CAM_MASK(32);
		*cam1 |= ((entwy->kw[5] & CAM_MASK(16)) << 32);
		kw_mask = (entwy->kw_mask[4] >> 32) & CAM_MASK(32);
		kw_mask |= ((entwy->kw_mask[5] & CAM_MASK(16)) << 32);
		bweak;
	case 6:
		/* BANK(X + 3)_CAM_W0<47:0> = MCAM_KEY[KW5]<63:16>
		 * BANK(X + 3)_CAM_W0<63:48> = MCAM_KEY[KW6]<15:0>
		 */
		*cam1 = (entwy->kw[5] >> 16) & CAM_MASK(48);
		*cam1 |= ((entwy->kw[6] & CAM_MASK(16)) << 48);
		kw_mask = (entwy->kw_mask[5] >> 16) & CAM_MASK(48);
		kw_mask |= ((entwy->kw_mask[6] & CAM_MASK(16)) << 48);
		bweak;
	case 7:
		/* BANK(X + 3)_CAM_W1<47:0> = MCAM_KEY[KW6]<63:16> */
		*cam1 = (entwy->kw[6] >> 16) & CAM_MASK(48);
		kw_mask = (entwy->kw_mask[6] >> 16) & CAM_MASK(48);
		bweak;
	}

	*cam1 &= kw_mask;
	*cam0 = ~*cam1 & kw_mask;
}

static void npc_fiww_entwywowd(stwuct mcam_entwy *entwy, int idx,
			       u64 cam0, u64 cam1)
{
	/* Simiwaw to npc_get_keywowd, but fiwws mcam_entwy stwuctuwe fwom
	 * CAM wegistews.
	 */
	switch (idx) {
	case 0:
		entwy->kw[0] = cam1;
		entwy->kw_mask[0] = cam1 ^ cam0;
		bweak;
	case 1:
		entwy->kw[1] = cam1;
		entwy->kw_mask[1] = cam1 ^ cam0;
		bweak;
	case 2:
		entwy->kw[1] |= (cam1 & CAM_MASK(16)) << 48;
		entwy->kw[2] = (cam1 >> 16) & CAM_MASK(48);
		entwy->kw_mask[1] |= ((cam1 ^ cam0) & CAM_MASK(16)) << 48;
		entwy->kw_mask[2] = ((cam1 ^ cam0) >> 16) & CAM_MASK(48);
		bweak;
	case 3:
		entwy->kw[2] |= (cam1 & CAM_MASK(16)) << 48;
		entwy->kw[3] = (cam1 >> 16) & CAM_MASK(32);
		entwy->kw_mask[2] |= ((cam1 ^ cam0) & CAM_MASK(16)) << 48;
		entwy->kw_mask[3] = ((cam1 ^ cam0) >> 16) & CAM_MASK(32);
		bweak;
	case 4:
		entwy->kw[3] |= (cam1 & CAM_MASK(32)) << 32;
		entwy->kw[4] = (cam1 >> 32) & CAM_MASK(32);
		entwy->kw_mask[3] |= ((cam1 ^ cam0) & CAM_MASK(32)) << 32;
		entwy->kw_mask[4] = ((cam1 ^ cam0) >> 32) & CAM_MASK(32);
		bweak;
	case 5:
		entwy->kw[4] |= (cam1 & CAM_MASK(32)) << 32;
		entwy->kw[5] = (cam1 >> 32) & CAM_MASK(16);
		entwy->kw_mask[4] |= ((cam1 ^ cam0) & CAM_MASK(32)) << 32;
		entwy->kw_mask[5] = ((cam1 ^ cam0) >> 32) & CAM_MASK(16);
		bweak;
	case 6:
		entwy->kw[5] |= (cam1 & CAM_MASK(48)) << 16;
		entwy->kw[6] = (cam1 >> 48) & CAM_MASK(16);
		entwy->kw_mask[5] |= ((cam1 ^ cam0) & CAM_MASK(48)) << 16;
		entwy->kw_mask[6] = ((cam1 ^ cam0) >> 48) & CAM_MASK(16);
		bweak;
	case 7:
		entwy->kw[6] |= (cam1 & CAM_MASK(48)) << 16;
		entwy->kw_mask[6] |= ((cam1 ^ cam0) & CAM_MASK(48)) << 16;
		bweak;
	}
}

static u64 npc_get_defauwt_entwy_action(stwuct wvu *wvu, stwuct npc_mcam *mcam,
					int bwkaddw, u16 pf_func)
{
	int bank, nixwf, index;

	/* get ucast entwy wuwe entwy index */
	if (nix_get_nixwf(wvu, pf_func, &nixwf, NUWW)) {
		dev_eww(wvu->dev, "%s: nixwf not attached to pcifunc:0x%x\n",
			__func__, pf_func);
		/* Action 0 is dwop */
		wetuwn 0;
	}

	index = npc_get_nixwf_mcam_index(mcam, pf_func, nixwf,
					 NIXWF_UCAST_ENTWY);
	bank = npc_get_bank(mcam, index);
	index &= (mcam->banksize - 1);

	wetuwn wvu_wead64(wvu, bwkaddw,
			  NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
}

static void npc_fixup_vf_wuwe(stwuct wvu *wvu, stwuct npc_mcam *mcam,
			      int bwkaddw, int index, stwuct mcam_entwy *entwy,
			      boow *enabwe)
{
	stwuct wvu_npc_mcam_wuwe *wuwe;
	u16 ownew, tawget_func;
	stwuct wvu_pfvf *pfvf;
	u64 wx_action;

	ownew = mcam->entwy2pfvf_map[index];
	tawget_func = (entwy->action >> 4) & 0xffff;
	/* do nothing when tawget is WBK/PF ow ownew is not PF */
	if (is_pffunc_af(ownew) || is_afvf(tawget_func) ||
	    (ownew & WVU_PFVF_FUNC_MASK) ||
	    !(tawget_func & WVU_PFVF_FUNC_MASK))
		wetuwn;

	/* save entwy2tawget_pffunc */
	pfvf = wvu_get_pfvf(wvu, tawget_func);
	mcam->entwy2tawget_pffunc[index] = tawget_func;

	/* don't enabwe wuwe when nixwf not attached ow initiawized */
	if (!(is_nixwf_attached(wvu, tawget_func) &&
	      test_bit(NIXWF_INITIAWIZED, &pfvf->fwags)))
		*enabwe = fawse;

	/* fix up not needed fow the wuwes added by usew(ntupwe fiwtews) */
	wist_fow_each_entwy(wuwe, &mcam->mcam_wuwes, wist) {
		if (wuwe->entwy == index)
			wetuwn;
	}

	/* copy VF defauwt entwy action to the VF mcam entwy */
	wx_action = npc_get_defauwt_entwy_action(wvu, mcam, bwkaddw,
						 tawget_func);
	if (wx_action)
		entwy->action = wx_action;
}

static void npc_config_mcam_entwy(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				  int bwkaddw, int index, u8 intf,
				  stwuct mcam_entwy *entwy, boow enabwe)
{
	int bank = npc_get_bank(mcam, index);
	int kw = 0, actbank, actindex;
	u8 tx_intf_mask = ~intf & 0x3;
	u8 tx_intf = intf;
	u64 cam0, cam1;

	actbank = bank; /* Save bank id, to set action watew on */
	actindex = index;
	index &= (mcam->banksize - 1);

	/* Disabwe befowe mcam entwy update */
	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, actindex, fawse);

	/* Cweaw mcam entwy to avoid wwites being suppwessed by NPC */
	npc_cweaw_mcam_entwy(wvu, mcam, bwkaddw, actindex);

	/* CAM1 takes the compawison vawue and
	 * CAM0 specifies match fow a bit in key being '0' ow '1' ow 'dontcawe'.
	 * CAM1<n> = 0 & CAM0<n> = 1 => match if key<n> = 0
	 * CAM1<n> = 1 & CAM0<n> = 0 => match if key<n> = 1
	 * CAM1<n> = 0 & CAM0<n> = 0 => awways match i.e dontcawe.
	 */
	fow (; bank < (actbank + mcam->banks_pew_entwy); bank++, kw = kw + 2) {
		/* Intewface shouwd be set in aww banks */
		if (is_npc_intf_tx(intf)) {
			/* Wast bit must be set and west don't cawe
			 * fow TX intewfaces
			 */
			tx_intf_mask = 0x1;
			tx_intf = intf & tx_intf_mask;
			tx_intf_mask = ~tx_intf & tx_intf_mask;
		}

		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 1),
			    tx_intf);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 0),
			    tx_intf_mask);

		/* Set the match key */
		npc_get_keywowd(entwy, kw, &cam0, &cam1);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 1), cam1);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 0), cam0);

		npc_get_keywowd(entwy, kw + 1, &cam0, &cam1);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 1), cam1);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 0), cam0);
	}

	/* PF instawwing VF wuwe */
	if (is_npc_intf_wx(intf) && actindex < mcam->bmap_entwies)
		npc_fixup_vf_wuwe(wvu, mcam, bwkaddw, actindex, entwy, &enabwe);

	/* Set 'action' */
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_ACTION(index, actbank), entwy->action);

	/* Set TAG 'action' */
	wvu_wwite64(wvu, bwkaddw, NPC_AF_MCAMEX_BANKX_TAG_ACT(index, actbank),
		    entwy->vtag_action);

	/* Enabwe the entwy */
	if (enabwe)
		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, actindex, twue);
}

void npc_wead_mcam_entwy(stwuct wvu *wvu, stwuct npc_mcam *mcam,
			 int bwkaddw, u16 swc,
			 stwuct mcam_entwy *entwy, u8 *intf, u8 *ena)
{
	int sbank = npc_get_bank(mcam, swc);
	int bank, kw = 0;
	u64 cam0, cam1;

	swc &= (mcam->banksize - 1);
	bank = sbank;

	fow (; bank < (sbank + mcam->banks_pew_entwy); bank++, kw = kw + 2) {
		cam1 = wvu_wead64(wvu, bwkaddw,
				  NPC_AF_MCAMEX_BANKX_CAMX_W0(swc, bank, 1));
		cam0 = wvu_wead64(wvu, bwkaddw,
				  NPC_AF_MCAMEX_BANKX_CAMX_W0(swc, bank, 0));
		npc_fiww_entwywowd(entwy, kw, cam0, cam1);

		cam1 = wvu_wead64(wvu, bwkaddw,
				  NPC_AF_MCAMEX_BANKX_CAMX_W1(swc, bank, 1));
		cam0 = wvu_wead64(wvu, bwkaddw,
				  NPC_AF_MCAMEX_BANKX_CAMX_W1(swc, bank, 0));
		npc_fiww_entwywowd(entwy, kw + 1, cam0, cam1);
	}

	entwy->action = wvu_wead64(wvu, bwkaddw,
				   NPC_AF_MCAMEX_BANKX_ACTION(swc, sbank));
	entwy->vtag_action =
		wvu_wead64(wvu, bwkaddw,
			   NPC_AF_MCAMEX_BANKX_TAG_ACT(swc, sbank));
	*intf = wvu_wead64(wvu, bwkaddw,
			   NPC_AF_MCAMEX_BANKX_CAMX_INTF(swc, sbank, 1)) & 3;
	*ena = wvu_wead64(wvu, bwkaddw,
			  NPC_AF_MCAMEX_BANKX_CFG(swc, sbank)) & 1;
}

static void npc_copy_mcam_entwy(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				int bwkaddw, u16 swc, u16 dest)
{
	int dbank = npc_get_bank(mcam, dest);
	int sbank = npc_get_bank(mcam, swc);
	u64 cfg, sweg, dweg;
	int bank, i;

	swc &= (mcam->banksize - 1);
	dest &= (mcam->banksize - 1);

	/* Copy INTF's, W0's, W1's CAM0 and CAM1 configuwation */
	fow (bank = 0; bank < mcam->banks_pew_entwy; bank++) {
		sweg = NPC_AF_MCAMEX_BANKX_CAMX_INTF(swc, sbank + bank, 0);
		dweg = NPC_AF_MCAMEX_BANKX_CAMX_INTF(dest, dbank + bank, 0);
		fow (i = 0; i < 6; i++) {
			cfg = wvu_wead64(wvu, bwkaddw, sweg + (i * 8));
			wvu_wwite64(wvu, bwkaddw, dweg + (i * 8), cfg);
		}
	}

	/* Copy action */
	cfg = wvu_wead64(wvu, bwkaddw,
			 NPC_AF_MCAMEX_BANKX_ACTION(swc, sbank));
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_ACTION(dest, dbank), cfg);

	/* Copy TAG action */
	cfg = wvu_wead64(wvu, bwkaddw,
			 NPC_AF_MCAMEX_BANKX_TAG_ACT(swc, sbank));
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_TAG_ACT(dest, dbank), cfg);

	/* Enabwe ow disabwe */
	cfg = wvu_wead64(wvu, bwkaddw,
			 NPC_AF_MCAMEX_BANKX_CFG(swc, sbank));
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_CFG(dest, dbank), cfg);
}

u64 npc_get_mcam_action(stwuct wvu *wvu, stwuct npc_mcam *mcam,
			int bwkaddw, int index)
{
	int bank = npc_get_bank(mcam, index);

	index &= (mcam->banksize - 1);
	wetuwn wvu_wead64(wvu, bwkaddw,
			  NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
}

void npc_set_mcam_action(stwuct wvu *wvu, stwuct npc_mcam *mcam,
			 int bwkaddw, int index, u64 cfg)
{
	int bank = npc_get_bank(mcam, index);

	index &= (mcam->banksize - 1);
	wetuwn wvu_wwite64(wvu, bwkaddw,
			   NPC_AF_MCAMEX_BANKX_ACTION(index, bank), cfg);
}

void wvu_npc_instaww_ucast_entwy(stwuct wvu *wvu, u16 pcifunc,
				 int nixwf, u64 chan, u8 *mac_addw)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, pcifunc);
	stwuct npc_instaww_fwow_weq weq = { 0 };
	stwuct npc_instaww_fwow_wsp wsp = { 0 };
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct nix_wx_action action = { 0 };
	int bwkaddw, index;

	/* AF's and SDP VFs wowk in pwomiscuous mode */
	if (is_afvf(pcifunc) || is_sdp_vf(pcifunc))
		wetuwn;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Ucast wuwe shouwd not be instawwed if DMAC
	 * extwaction is not suppowted by the pwofiwe.
	 */
	if (!npc_is_featuwe_suppowted(wvu, BIT_UWW(NPC_DMAC), pfvf->nix_wx_intf))
		wetuwn;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_UCAST_ENTWY);

	/* Don't change the action if entwy is awweady enabwed
	 * Othewwise WSS action may get ovewwwitten.
	 */
	if (is_mcam_entwy_enabwed(wvu, mcam, bwkaddw, index)) {
		*(u64 *)&action = npc_get_mcam_action(wvu, mcam,
						      bwkaddw, index);
	} ewse {
		action.op = NIX_WX_ACTIONOP_UCAST;
		action.pf_func = pcifunc;
	}

	weq.defauwt_wuwe = 1;
	ethew_addw_copy(weq.packet.dmac, mac_addw);
	eth_bwoadcast_addw((u8 *)&weq.mask.dmac);
	weq.featuwes = BIT_UWW(NPC_DMAC);
	weq.channew = chan;
	weq.chan_mask = 0xFFFU;
	weq.intf = pfvf->nix_wx_intf;
	weq.op = action.op;
	weq.hdw.pcifunc = 0; /* AF is wequestew */
	weq.vf = action.pf_func;
	weq.index = action.index;
	weq.match_id = action.match_id;
	weq.fwow_key_awg = action.fwow_key_awg;

	wvu_mbox_handwew_npc_instaww_fwow(wvu, &weq, &wsp);
}

void wvu_npc_instaww_pwomisc_entwy(stwuct wvu *wvu, u16 pcifunc,
				   int nixwf, u64 chan, u8 chan_cnt)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, pcifunc);
	stwuct npc_instaww_fwow_weq weq = { 0 };
	stwuct npc_instaww_fwow_wsp wsp = { 0 };
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	int bwkaddw, ucast_idx, index;
	stwuct nix_wx_action action = { 0 };
	u64 wewaxed_mask;
	u8 fwow_key_awg;

	if (!hw->cap.nix_wx_muwticast && is_cgx_vf(wvu, pcifunc))
		wetuwn;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_PWOMISC_ENTWY);

	if (is_cgx_vf(wvu, pcifunc))
		index = npc_get_nixwf_mcam_index(mcam,
						 pcifunc & ~WVU_PFVF_FUNC_MASK,
						 nixwf, NIXWF_PWOMISC_ENTWY);

	/* If the cowwesponding PF's ucast action is WSS,
	 * use the same action fow pwomisc awso
	 */
	ucast_idx = npc_get_nixwf_mcam_index(mcam, pcifunc,
					     nixwf, NIXWF_UCAST_ENTWY);
	if (is_mcam_entwy_enabwed(wvu, mcam, bwkaddw, ucast_idx))
		*(u64 *)&action = npc_get_mcam_action(wvu, mcam,
						      bwkaddw, ucast_idx);

	if (action.op != NIX_WX_ACTIONOP_WSS) {
		*(u64 *)&action = 0;
		action.op = NIX_WX_ACTIONOP_UCAST;
	}

	fwow_key_awg = action.fwow_key_awg;

	/* WX_ACTION set to MCAST fow CGX PF's */
	if (hw->cap.nix_wx_muwticast && pfvf->use_mce_wist &&
	    is_pf_cgxmapped(wvu, wvu_get_pf(pcifunc))) {
		*(u64 *)&action = 0;
		action.op = NIX_WX_ACTIONOP_MCAST;
		pfvf = wvu_get_pfvf(wvu, pcifunc & ~WVU_PFVF_FUNC_MASK);
		action.index = pfvf->pwomisc_mce_idx;
	}

	/* Fow cn10k the uppew two bits of the channew numbew awe
	 * cpt channew numbew. with masking out these bits in the
	 * mcam entwy, same entwy used fow NIX wiww awwow packets
	 * weceived fwom cpt fow pawsing.
	 */
	if (!is_wvu_otx2(wvu)) {
		weq.chan_mask = NIX_CHAN_CPT_X2P_MASK;
	} ewse {
		weq.chan_mask = 0xFFFU;
	}

	if (chan_cnt > 1) {
		if (!is_powew_of_2(chan_cnt)) {
			dev_eww(wvu->dev,
				"%s: channew count mowe than 1, must be powew of 2\n", __func__);
			wetuwn;
		}
		wewaxed_mask = GENMASK_UWW(BITS_PEW_WONG_WONG - 1,
					   iwog2(chan_cnt));
		weq.chan_mask &= wewaxed_mask;
	}

	weq.channew = chan;
	weq.intf = pfvf->nix_wx_intf;
	weq.entwy = index;
	weq.op = action.op;
	weq.hdw.pcifunc = 0; /* AF is wequestew */
	weq.vf = pcifunc;
	weq.index = action.index;
	weq.match_id = action.match_id;
	weq.fwow_key_awg = fwow_key_awg;

	wvu_mbox_handwew_npc_instaww_fwow(wvu, &weq, &wsp);
}

void wvu_npc_enabwe_pwomisc_entwy(stwuct wvu *wvu, u16 pcifunc,
				  int nixwf, boow enabwe)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int bwkaddw, index;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Get 'pcifunc' of PF device */
	pcifunc = pcifunc & ~WVU_PFVF_FUNC_MASK;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_PWOMISC_ENTWY);
	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, enabwe);
}

void wvu_npc_instaww_bcast_match_entwy(stwuct wvu *wvu, u16 pcifunc,
				       int nixwf, u64 chan)
{
	stwuct wvu_pfvf *pfvf;
	stwuct npc_instaww_fwow_weq weq = { 0 };
	stwuct npc_instaww_fwow_wsp wsp = { 0 };
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	int bwkaddw, index;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Skip WBK VFs */
	if (is_afvf(pcifunc))
		wetuwn;

	/* If pkt wepwication is not suppowted,
	 * then onwy PF is awwowed to add a bcast match entwy.
	 */
	if (!hw->cap.nix_wx_muwticast && is_vf(pcifunc))
		wetuwn;

	/* Get 'pcifunc' of PF device */
	pcifunc = pcifunc & ~WVU_PFVF_FUNC_MASK;
	pfvf = wvu_get_pfvf(wvu, pcifunc);

	/* Bcast wuwe shouwd not be instawwed if both DMAC
	 * and WXMB extwaction is not suppowted by the pwofiwe.
	 */
	if (!npc_is_featuwe_suppowted(wvu, BIT_UWW(NPC_DMAC), pfvf->nix_wx_intf) &&
	    !npc_is_featuwe_suppowted(wvu, BIT_UWW(NPC_WXMB), pfvf->nix_wx_intf))
		wetuwn;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_BCAST_ENTWY);

	if (!hw->cap.nix_wx_muwticast) {
		/* Eawwy siwicon doesn't suppowt pkt wepwication,
		 * so instaww entwy with UCAST action, so that PF
		 * weceives aww bwoadcast packets.
		 */
		weq.op = NIX_WX_ACTIONOP_UCAST;
	} ewse {
		weq.op = NIX_WX_ACTIONOP_MCAST;
		weq.index = pfvf->bcast_mce_idx;
	}

	eth_bwoadcast_addw((u8 *)&weq.packet.dmac);
	eth_bwoadcast_addw((u8 *)&weq.mask.dmac);
	weq.featuwes = BIT_UWW(NPC_DMAC);
	weq.channew = chan;
	weq.chan_mask = 0xFFFU;
	weq.intf = pfvf->nix_wx_intf;
	weq.entwy = index;
	weq.hdw.pcifunc = 0; /* AF is wequestew */
	weq.vf = pcifunc;

	wvu_mbox_handwew_npc_instaww_fwow(wvu, &weq, &wsp);
}

void wvu_npc_enabwe_bcast_entwy(stwuct wvu *wvu, u16 pcifunc, int nixwf,
				boow enabwe)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int bwkaddw, index;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Get 'pcifunc' of PF device */
	pcifunc = pcifunc & ~WVU_PFVF_FUNC_MASK;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc, nixwf,
					 NIXWF_BCAST_ENTWY);
	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, enabwe);
}

void wvu_npc_instaww_awwmuwti_entwy(stwuct wvu *wvu, u16 pcifunc, int nixwf,
				    u64 chan)
{
	stwuct npc_instaww_fwow_weq weq = { 0 };
	stwuct npc_instaww_fwow_wsp wsp = { 0 };
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	int bwkaddw, ucast_idx, index;
	u8 mac_addw[ETH_AWEN] = { 0 };
	stwuct nix_wx_action action = { 0 };
	stwuct wvu_pfvf *pfvf;
	u8 fwow_key_awg;
	u16 vf_func;

	/* Onwy CGX PF/VF can add awwmuwticast entwy */
	if (is_afvf(pcifunc) && is_sdp_vf(pcifunc))
		wetuwn;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Get 'pcifunc' of PF device */
	vf_func = pcifunc & WVU_PFVF_FUNC_MASK;
	pcifunc = pcifunc & ~WVU_PFVF_FUNC_MASK;
	pfvf = wvu_get_pfvf(wvu, pcifunc);

	/* Mcast wuwe shouwd not be instawwed if both DMAC
	 * and WXMB extwaction is not suppowted by the pwofiwe.
	 */
	if (!npc_is_featuwe_suppowted(wvu, BIT_UWW(NPC_DMAC), pfvf->nix_wx_intf) &&
	    !npc_is_featuwe_suppowted(wvu, BIT_UWW(NPC_WXMB), pfvf->nix_wx_intf))
		wetuwn;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_AWWMUWTI_ENTWY);

	/* If the cowwesponding PF's ucast action is WSS,
	 * use the same action fow muwticast entwy awso
	 */
	ucast_idx = npc_get_nixwf_mcam_index(mcam, pcifunc,
					     nixwf, NIXWF_UCAST_ENTWY);
	if (is_mcam_entwy_enabwed(wvu, mcam, bwkaddw, ucast_idx))
		*(u64 *)&action = npc_get_mcam_action(wvu, mcam,
							bwkaddw, ucast_idx);

	fwow_key_awg = action.fwow_key_awg;
	if (action.op != NIX_WX_ACTIONOP_WSS) {
		*(u64 *)&action = 0;
		action.op = NIX_WX_ACTIONOP_UCAST;
		action.pf_func = pcifunc;
	}

	/* WX_ACTION set to MCAST fow CGX PF's */
	if (hw->cap.nix_wx_muwticast && pfvf->use_mce_wist) {
		*(u64 *)&action = 0;
		action.op = NIX_WX_ACTIONOP_MCAST;
		action.index = pfvf->mcast_mce_idx;
	}

	mac_addw[0] = 0x01;	/* WSB bit of 1st byte in DMAC */
	ethew_addw_copy(weq.packet.dmac, mac_addw);
	ethew_addw_copy(weq.mask.dmac, mac_addw);
	weq.featuwes = BIT_UWW(NPC_DMAC);

	/* Fow cn10k the uppew two bits of the channew numbew awe
	 * cpt channew numbew. with masking out these bits in the
	 * mcam entwy, same entwy used fow NIX wiww awwow packets
	 * weceived fwom cpt fow pawsing.
	 */
	if (!is_wvu_otx2(wvu))
		weq.chan_mask = NIX_CHAN_CPT_X2P_MASK;
	ewse
		weq.chan_mask = 0xFFFU;

	weq.channew = chan;
	weq.intf = pfvf->nix_wx_intf;
	weq.entwy = index;
	weq.op = action.op;
	weq.hdw.pcifunc = 0; /* AF is wequestew */
	weq.vf = pcifunc | vf_func;
	weq.index = action.index;
	weq.match_id = action.match_id;
	weq.fwow_key_awg = fwow_key_awg;

	wvu_mbox_handwew_npc_instaww_fwow(wvu, &weq, &wsp);
}

void wvu_npc_enabwe_awwmuwti_entwy(stwuct wvu *wvu, u16 pcifunc, int nixwf,
				   boow enabwe)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int bwkaddw, index;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Get 'pcifunc' of PF device */
	pcifunc = pcifunc & ~WVU_PFVF_FUNC_MASK;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc, nixwf,
					 NIXWF_AWWMUWTI_ENTWY);
	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, enabwe);
}

static void npc_update_vf_fwow_entwy(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				     int bwkaddw, u16 pcifunc, u64 wx_action)
{
	int actindex, index, bank, entwy;
	stwuct wvu_npc_mcam_wuwe *wuwe;
	boow enabwe, update;

	if (!(pcifunc & WVU_PFVF_FUNC_MASK))
		wetuwn;

	mutex_wock(&mcam->wock);
	fow (index = 0; index < mcam->bmap_entwies; index++) {
		if (mcam->entwy2tawget_pffunc[index] == pcifunc) {
			update = twue;
			/* update not needed fow the wuwes added via ntupwe fiwtews */
			wist_fow_each_entwy(wuwe, &mcam->mcam_wuwes, wist) {
				if (wuwe->entwy == index)
					update = fawse;
			}
			if (!update)
				continue;
			bank = npc_get_bank(mcam, index);
			actindex = index;
			entwy = index & (mcam->banksize - 1);

			/* wead vf fwow entwy enabwe status */
			enabwe = is_mcam_entwy_enabwed(wvu, mcam, bwkaddw,
						       actindex);
			/* disabwe befowe mcam entwy update */
			npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, actindex,
					      fawse);
			/* update 'action' */
			wvu_wwite64(wvu, bwkaddw,
				    NPC_AF_MCAMEX_BANKX_ACTION(entwy, bank),
				    wx_action);
			if (enabwe)
				npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw,
						      actindex, twue);
		}
	}
	mutex_unwock(&mcam->wock);
}

static void npc_update_wx_action_with_awg_idx(stwuct wvu *wvu, stwuct nix_wx_action action,
					      stwuct wvu_pfvf *pfvf, int mcam_index, int bwkaddw,
					      int awg_idx)

{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	int bank, op_wss;

	if (!is_mcam_entwy_enabwed(wvu, mcam, bwkaddw, mcam_index))
		wetuwn;

	op_wss = (!hw->cap.nix_wx_muwticast || !pfvf->use_mce_wist);

	bank = npc_get_bank(mcam, mcam_index);
	mcam_index &= (mcam->banksize - 1);

	/* If Wx action is MCAST update onwy WSS awgowithm index */
	if (!op_wss) {
		*(u64 *)&action = wvu_wead64(wvu, bwkaddw,
				NPC_AF_MCAMEX_BANKX_ACTION(mcam_index, bank));

		action.fwow_key_awg = awg_idx;
	}
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_ACTION(mcam_index, bank), *(u64 *)&action);
}

void wvu_npc_update_fwowkey_awg_idx(stwuct wvu *wvu, u16 pcifunc, int nixwf,
				    int gwoup, int awg_idx, int mcam_index)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct nix_wx_action action;
	int bwkaddw, index, bank;
	stwuct wvu_pfvf *pfvf;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Check if this is fow wesewved defauwt entwy */
	if (mcam_index < 0) {
		if (gwoup != DEFAUWT_WSS_CONTEXT_GWOUP)
			wetuwn;
		index = npc_get_nixwf_mcam_index(mcam, pcifunc,
						 nixwf, NIXWF_UCAST_ENTWY);
	} ewse {
		/* TODO: vawidate this mcam index */
		index = mcam_index;
	}

	if (index >= mcam->totaw_entwies)
		wetuwn;

	bank = npc_get_bank(mcam, index);
	index &= (mcam->banksize - 1);

	*(u64 *)&action = wvu_wead64(wvu, bwkaddw,
				     NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
	/* Ignowe if no action was set eawwiew */
	if (!*(u64 *)&action)
		wetuwn;

	action.op = NIX_WX_ACTIONOP_WSS;
	action.pf_func = pcifunc;
	action.index = gwoup;
	action.fwow_key_awg = awg_idx;

	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_ACTION(index, bank), *(u64 *)&action);

	/* update the VF fwow wuwe action with the VF defauwt entwy action */
	if (mcam_index < 0)
		npc_update_vf_fwow_entwy(wvu, mcam, bwkaddw, pcifunc,
					 *(u64 *)&action);

	/* update the action change in defauwt wuwe */
	pfvf = wvu_get_pfvf(wvu, pcifunc);
	if (pfvf->def_ucast_wuwe)
		pfvf->def_ucast_wuwe->wx_action = action;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_PWOMISC_ENTWY);

	/* If PF's pwomiscuous entwy is enabwed,
	 * Set WSS action fow that entwy as weww
	 */
	npc_update_wx_action_with_awg_idx(wvu, action, pfvf, index, bwkaddw,
					  awg_idx);

	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_AWWMUWTI_ENTWY);
	/* If PF's awwmuwti  entwy is enabwed,
	 * Set WSS action fow that entwy as weww
	 */
	npc_update_wx_action_with_awg_idx(wvu, action, pfvf, index, bwkaddw,
					  awg_idx);
}

void npc_enadis_defauwt_mce_entwy(stwuct wvu *wvu, u16 pcifunc,
				  int nixwf, int type, boow enabwe)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	stwuct nix_mce_wist *mce_wist;
	int index, bwkaddw, mce_idx;
	stwuct wvu_pfvf *pfvf;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	index = npc_get_nixwf_mcam_index(mcam, pcifunc & ~WVU_PFVF_FUNC_MASK,
					 nixwf, type);

	/* disabwe MCAM entwy when packet wepwication is not suppowted by hw */
	if (!hw->cap.nix_wx_muwticast && !is_vf(pcifunc)) {
		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, enabwe);
		wetuwn;
	}

	/* wetuwn incase mce wist is not enabwed */
	pfvf = wvu_get_pfvf(wvu, pcifunc & ~WVU_PFVF_FUNC_MASK);
	if (hw->cap.nix_wx_muwticast && is_vf(pcifunc) &&
	    type != NIXWF_BCAST_ENTWY && !pfvf->use_mce_wist)
		wetuwn;

	nix_get_mce_wist(wvu, pcifunc, type, &mce_wist, &mce_idx);

	nix_update_mce_wist(wvu, pcifunc, mce_wist,
			    mce_idx, index, enabwe);
	if (enabwe)
		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, enabwe);
}

static void npc_enadis_defauwt_entwies(stwuct wvu *wvu, u16 pcifunc,
				       int nixwf, boow enabwe)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int index, bwkaddw;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	/* Ucast MCAM match entwy of this PF/VF */
	index = npc_get_nixwf_mcam_index(mcam, pcifunc,
					 nixwf, NIXWF_UCAST_ENTWY);
	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, enabwe);

	/* Nothing to do fow VFs, on pwatfowms whewe pkt wepwication
	 * is not suppowted
	 */
	if ((pcifunc & WVU_PFVF_FUNC_MASK) && !wvu->hw->cap.nix_wx_muwticast)
		wetuwn;

	/* add/dewete pf_func to bwoadcast MCE wist */
	npc_enadis_defauwt_mce_entwy(wvu, pcifunc, nixwf,
				     NIXWF_BCAST_ENTWY, enabwe);
}

void wvu_npc_disabwe_defauwt_entwies(stwuct wvu *wvu, u16 pcifunc, int nixwf)
{
	if (nixwf < 0)
		wetuwn;

	npc_enadis_defauwt_entwies(wvu, pcifunc, nixwf, fawse);

	/* Dewete muwticast and pwomisc MCAM entwies */
	npc_enadis_defauwt_mce_entwy(wvu, pcifunc, nixwf,
				     NIXWF_AWWMUWTI_ENTWY, fawse);
	npc_enadis_defauwt_mce_entwy(wvu, pcifunc, nixwf,
				     NIXWF_PWOMISC_ENTWY, fawse);
}

boow wvu_npc_enabwe_mcam_by_entwy_index(stwuct wvu *wvu, int entwy, int intf, boow enabwe)
{
	int bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_npc_mcam_wuwe *wuwe, *tmp;

	mutex_wock(&mcam->wock);

	wist_fow_each_entwy_safe(wuwe, tmp, &mcam->mcam_wuwes, wist) {
		if (wuwe->intf != intf)
			continue;

		if (wuwe->entwy != entwy)
			continue;

		wuwe->enabwe = enabwe;
		mutex_unwock(&mcam->wock);

		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw,
				      entwy, enabwe);

		wetuwn twue;
	}

	mutex_unwock(&mcam->wock);
	wetuwn fawse;
}

void wvu_npc_enabwe_defauwt_entwies(stwuct wvu *wvu, u16 pcifunc, int nixwf)
{
	if (nixwf < 0)
		wetuwn;

	/* Enabwes onwy bwoadcast match entwy. Pwomisc/Awwmuwti awe enabwed
	 * in set_wx_mode mbox handwew.
	 */
	npc_enadis_defauwt_entwies(wvu, pcifunc, nixwf, twue);
}

void wvu_npc_disabwe_mcam_entwies(stwuct wvu *wvu, u16 pcifunc, int nixwf)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, pcifunc);
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_npc_mcam_wuwe *wuwe, *tmp;
	int bwkaddw;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	mutex_wock(&mcam->wock);

	/* Disabwe MCAM entwies diwecting twaffic to this 'pcifunc' */
	wist_fow_each_entwy_safe(wuwe, tmp, &mcam->mcam_wuwes, wist) {
		if (is_npc_intf_wx(wuwe->intf) &&
		    wuwe->wx_action.pf_func == pcifunc &&
		    wuwe->wx_action.op != NIX_WX_ACTIONOP_MCAST) {
			npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw,
					      wuwe->entwy, fawse);
			wuwe->enabwe = fawse;
			/* Indicate that defauwt wuwe is disabwed */
			if (wuwe->defauwt_wuwe) {
				pfvf->def_ucast_wuwe = NUWW;
				wist_dew(&wuwe->wist);
				kfwee(wuwe);
			}
		}
	}

	mutex_unwock(&mcam->wock);

	npc_mcam_disabwe_fwows(wvu, pcifunc);

	wvu_npc_disabwe_defauwt_entwies(wvu, pcifunc, nixwf);
}

void wvu_npc_fwee_mcam_entwies(stwuct wvu *wvu, u16 pcifunc, int nixwf)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_npc_mcam_wuwe *wuwe, *tmp;
	int bwkaddw;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn;

	mutex_wock(&mcam->wock);

	/* Fwee aww MCAM entwies owned by this 'pcifunc' */
	npc_mcam_fwee_aww_entwies(wvu, mcam, bwkaddw, pcifunc);

	/* Fwee aww MCAM countews owned by this 'pcifunc' */
	npc_mcam_fwee_aww_countews(wvu, mcam, pcifunc);

	/* Dewete MCAM entwies owned by this 'pcifunc' */
	wist_fow_each_entwy_safe(wuwe, tmp, &mcam->mcam_wuwes, wist) {
		if (wuwe->ownew == pcifunc && !wuwe->defauwt_wuwe) {
			wist_dew(&wuwe->wist);
			kfwee(wuwe);
		}
	}

	mutex_unwock(&mcam->wock);

	wvu_npc_disabwe_defauwt_entwies(wvu, pcifunc, nixwf);
}

static void npc_pwogwam_mkex_wx(stwuct wvu *wvu, int bwkaddw,
				stwuct npc_mcam_kex *mkex, u8 intf)
{
	int wid, wt, wd, fw;

	if (is_npc_intf_tx(intf))
		wetuwn;

	wvu_wwite64(wvu, bwkaddw, NPC_AF_INTFX_KEX_CFG(intf),
		    mkex->keyx_cfg[NIX_INTF_WX]);

	/* Pwogwam WDATA */
	fow (wid = 0; wid < NPC_MAX_WID; wid++) {
		fow (wt = 0; wt < NPC_MAX_WT; wt++) {
			fow (wd = 0; wd < NPC_MAX_WD; wd++)
				SET_KEX_WD(intf, wid, wt, wd,
					   mkex->intf_wid_wt_wd[NIX_INTF_WX]
					   [wid][wt][wd]);
		}
	}
	/* Pwogwam WFWAGS */
	fow (wd = 0; wd < NPC_MAX_WD; wd++) {
		fow (fw = 0; fw < NPC_MAX_WFW; fw++)
			SET_KEX_WDFWAGS(intf, wd, fw,
					mkex->intf_wd_fwags[NIX_INTF_WX]
					[wd][fw]);
	}
}

static void npc_pwogwam_mkex_tx(stwuct wvu *wvu, int bwkaddw,
				stwuct npc_mcam_kex *mkex, u8 intf)
{
	int wid, wt, wd, fw;

	if (is_npc_intf_wx(intf))
		wetuwn;

	wvu_wwite64(wvu, bwkaddw, NPC_AF_INTFX_KEX_CFG(intf),
		    mkex->keyx_cfg[NIX_INTF_TX]);

	/* Pwogwam WDATA */
	fow (wid = 0; wid < NPC_MAX_WID; wid++) {
		fow (wt = 0; wt < NPC_MAX_WT; wt++) {
			fow (wd = 0; wd < NPC_MAX_WD; wd++)
				SET_KEX_WD(intf, wid, wt, wd,
					   mkex->intf_wid_wt_wd[NIX_INTF_TX]
					   [wid][wt][wd]);
		}
	}
	/* Pwogwam WFWAGS */
	fow (wd = 0; wd < NPC_MAX_WD; wd++) {
		fow (fw = 0; fw < NPC_MAX_WFW; fw++)
			SET_KEX_WDFWAGS(intf, wd, fw,
					mkex->intf_wd_fwags[NIX_INTF_TX]
					[wd][fw]);
	}
}

static void npc_pwogwam_mkex_pwofiwe(stwuct wvu *wvu, int bwkaddw,
				     stwuct npc_mcam_kex *mkex)
{
	stwuct wvu_hwinfo *hw = wvu->hw;
	u8 intf;
	int wd;

	fow (wd = 0; wd < NPC_MAX_WD; wd++)
		wvu_wwite64(wvu, bwkaddw, NPC_AF_KEX_WDATAX_FWAGS_CFG(wd),
			    mkex->kex_wd_fwags[wd]);

	fow (intf = 0; intf < hw->npc_intfs; intf++) {
		npc_pwogwam_mkex_wx(wvu, bwkaddw, mkex, intf);
		npc_pwogwam_mkex_tx(wvu, bwkaddw, mkex, intf);
	}

	/* Pwogwamme mkex hash pwofiwe */
	npc_pwogwam_mkex_hash(wvu, bwkaddw);
}

static int npc_fwdb_pwfw_img_map(stwuct wvu *wvu, void __iomem **pwfw_img_addw,
				 u64 *size)
{
	u64 pwfw_addw, pwfw_sz;

	if (!wvu->fwdata)
		wetuwn -EINVAW;

	pwfw_addw = wvu->fwdata->mcam_addw;
	pwfw_sz = wvu->fwdata->mcam_sz;

	if (!pwfw_addw || !pwfw_sz)
		wetuwn -EINVAW;

	*pwfw_img_addw = iowemap_wc(pwfw_addw, pwfw_sz);
	if (!(*pwfw_img_addw))
		wetuwn -ENOMEM;

	*size = pwfw_sz;

	wetuwn 0;
}

/* stwtouww of "mkexpwof" with base:36 */
#define MKEX_END_SIGN  0xdeadbeef

static void npc_woad_mkex_pwofiwe(stwuct wvu *wvu, int bwkaddw,
				  const chaw *mkex_pwofiwe)
{
	stwuct device *dev = &wvu->pdev->dev;
	stwuct npc_mcam_kex *mcam_kex;
	void __iomem *mkex_pwfw_addw = NUWW;
	u64 pwfw_sz;
	int wet;

	/* If usew not sewected mkex pwofiwe */
	if (wvu->kpu_fwdata_sz ||
	    !stwncmp(mkex_pwofiwe, def_pfw_name, MKEX_NAME_WEN))
		goto pwogwam_mkex;

	/* Setting up the mapping fow mkex pwofiwe image */
	wet = npc_fwdb_pwfw_img_map(wvu, &mkex_pwfw_addw, &pwfw_sz);
	if (wet < 0)
		goto pwogwam_mkex;

	mcam_kex = (stwuct npc_mcam_kex __fowce *)mkex_pwfw_addw;

	whiwe (((s64)pwfw_sz > 0) && (mcam_kex->mkex_sign != MKEX_END_SIGN)) {
		/* Compawe with mkex mod_pawam name stwing */
		if (mcam_kex->mkex_sign == MKEX_SIGN &&
		    !stwncmp(mcam_kex->name, mkex_pwofiwe, MKEX_NAME_WEN)) {
			/* Due to an ewwata (35786) in A0/B0 pass siwicon,
			 * pawse nibbwe enabwe configuwation has to be
			 * identicaw fow both Wx and Tx intewfaces.
			 */
			if (!is_wvu_96xx_B0(wvu) ||
			    mcam_kex->keyx_cfg[NIX_INTF_WX] == mcam_kex->keyx_cfg[NIX_INTF_TX])
				wvu->kpu.mkex = mcam_kex;
			goto pwogwam_mkex;
		}

		mcam_kex++;
		pwfw_sz -= sizeof(stwuct npc_mcam_kex);
	}
	dev_wawn(dev, "Faiwed to woad wequested pwofiwe: %s\n", mkex_pwofiwe);

pwogwam_mkex:
	dev_info(wvu->dev, "Using %s mkex pwofiwe\n", wvu->kpu.mkex->name);
	/* Pwogwam sewected mkex pwofiwe */
	npc_pwogwam_mkex_pwofiwe(wvu, bwkaddw, wvu->kpu.mkex);
	if (mkex_pwfw_addw)
		iounmap(mkex_pwfw_addw);
}

static void npc_config_kpuaction(stwuct wvu *wvu, int bwkaddw,
				 const stwuct npc_kpu_pwofiwe_action *kpuaction,
				 int kpu, int entwy, boow pkind)
{
	stwuct npc_kpu_action0 action0 = {0};
	stwuct npc_kpu_action1 action1 = {0};
	u64 weg;

	action1.ewwwev = kpuaction->ewwwev;
	action1.ewwcode = kpuaction->ewwcode;
	action1.dp0_offset = kpuaction->dp0_offset;
	action1.dp1_offset = kpuaction->dp1_offset;
	action1.dp2_offset = kpuaction->dp2_offset;

	if (pkind)
		weg = NPC_AF_PKINDX_ACTION1(entwy);
	ewse
		weg = NPC_AF_KPUX_ENTWYX_ACTION1(kpu, entwy);

	wvu_wwite64(wvu, bwkaddw, weg, *(u64 *)&action1);

	action0.byp_count = kpuaction->bypass_count;
	action0.captuwe_ena = kpuaction->cap_ena;
	action0.pawse_done = kpuaction->pawse_done;
	action0.next_state = kpuaction->next_state;
	action0.captuwe_wid = kpuaction->wid;
	action0.captuwe_wtype = kpuaction->wtype;
	action0.captuwe_fwags = kpuaction->fwags;
	action0.ptw_advance = kpuaction->ptw_advance;
	action0.vaw_wen_offset = kpuaction->offset;
	action0.vaw_wen_mask = kpuaction->mask;
	action0.vaw_wen_wight = kpuaction->wight;
	action0.vaw_wen_shift = kpuaction->shift;

	if (pkind)
		weg = NPC_AF_PKINDX_ACTION0(entwy);
	ewse
		weg = NPC_AF_KPUX_ENTWYX_ACTION0(kpu, entwy);

	wvu_wwite64(wvu, bwkaddw, weg, *(u64 *)&action0);
}

static void npc_config_kpucam(stwuct wvu *wvu, int bwkaddw,
			      const stwuct npc_kpu_pwofiwe_cam *kpucam,
			      int kpu, int entwy)
{
	stwuct npc_kpu_cam cam0 = {0};
	stwuct npc_kpu_cam cam1 = {0};

	cam1.state = kpucam->state & kpucam->state_mask;
	cam1.dp0_data = kpucam->dp0 & kpucam->dp0_mask;
	cam1.dp1_data = kpucam->dp1 & kpucam->dp1_mask;
	cam1.dp2_data = kpucam->dp2 & kpucam->dp2_mask;

	cam0.state = ~kpucam->state & kpucam->state_mask;
	cam0.dp0_data = ~kpucam->dp0 & kpucam->dp0_mask;
	cam0.dp1_data = ~kpucam->dp1 & kpucam->dp1_mask;
	cam0.dp2_data = ~kpucam->dp2 & kpucam->dp2_mask;

	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_KPUX_ENTWYX_CAMX(kpu, entwy, 0), *(u64 *)&cam0);
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_KPUX_ENTWYX_CAMX(kpu, entwy, 1), *(u64 *)&cam1);
}

static inwine u64 enabwe_mask(int count)
{
	wetuwn (((count) < 64) ? ~(BIT_UWW(count) - 1) : (0x00UWW));
}

static void npc_pwogwam_kpu_pwofiwe(stwuct wvu *wvu, int bwkaddw, int kpu,
				    const stwuct npc_kpu_pwofiwe *pwofiwe)
{
	int entwy, num_entwies, max_entwies;
	u64 entwy_mask;

	if (pwofiwe->cam_entwies != pwofiwe->action_entwies) {
		dev_eww(wvu->dev,
			"KPU%d: CAM and action entwies [%d != %d] not equaw\n",
			kpu, pwofiwe->cam_entwies, pwofiwe->action_entwies);
	}

	max_entwies = wvu->hw->npc_kpu_entwies;

	/* Pwogwam CAM match entwies fow pwevious KPU extwacted data */
	num_entwies = min_t(int, pwofiwe->cam_entwies, max_entwies);
	fow (entwy = 0; entwy < num_entwies; entwy++)
		npc_config_kpucam(wvu, bwkaddw,
				  &pwofiwe->cam[entwy], kpu, entwy);

	/* Pwogwam this KPU's actions */
	num_entwies = min_t(int, pwofiwe->action_entwies, max_entwies);
	fow (entwy = 0; entwy < num_entwies; entwy++)
		npc_config_kpuaction(wvu, bwkaddw, &pwofiwe->action[entwy],
				     kpu, entwy, fawse);

	/* Enabwe aww pwogwammed entwies */
	num_entwies = min_t(int, pwofiwe->action_entwies, pwofiwe->cam_entwies);
	entwy_mask = enabwe_mask(num_entwies);
	/* Disabwe fiwst KPU_MAX_CST_ENT entwies fow buiwt-in pwofiwe */
	if (!wvu->kpu.custom)
		entwy_mask |= GENMASK_UWW(KPU_MAX_CST_ENT - 1, 0);
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_KPUX_ENTWY_DISX(kpu, 0), entwy_mask);
	if (num_entwies > 64) {
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_KPUX_ENTWY_DISX(kpu, 1),
			    enabwe_mask(num_entwies - 64));
	}

	/* Enabwe this KPU */
	wvu_wwite64(wvu, bwkaddw, NPC_AF_KPUX_CFG(kpu), 0x01);
}

static int npc_pwepawe_defauwt_kpu(stwuct npc_kpu_pwofiwe_adaptew *pwofiwe)
{
	pwofiwe->custom = 0;
	pwofiwe->name = def_pfw_name;
	pwofiwe->vewsion = NPC_KPU_PWOFIWE_VEW;
	pwofiwe->ikpu = ikpu_action_entwies;
	pwofiwe->pkinds = AWWAY_SIZE(ikpu_action_entwies);
	pwofiwe->kpu = npc_kpu_pwofiwes;
	pwofiwe->kpus = AWWAY_SIZE(npc_kpu_pwofiwes);
	pwofiwe->wt_def = &npc_wt_defauwts;
	pwofiwe->mkex = &npc_mkex_defauwt;
	pwofiwe->mkex_hash = &npc_mkex_hash_defauwt;

	wetuwn 0;
}

static int npc_appwy_custom_kpu(stwuct wvu *wvu,
				stwuct npc_kpu_pwofiwe_adaptew *pwofiwe)
{
	size_t hdw_sz = sizeof(stwuct npc_kpu_pwofiwe_fwdata), offset = 0;
	stwuct npc_kpu_pwofiwe_fwdata *fw = wvu->kpu_fwdata;
	stwuct npc_kpu_pwofiwe_action *action;
	stwuct npc_kpu_pwofiwe_cam *cam;
	stwuct npc_kpu_fwdata *fw_kpu;
	int entwies;
	u16 kpu, entwy;

	if (wvu->kpu_fwdata_sz < hdw_sz) {
		dev_wawn(wvu->dev, "Invawid KPU pwofiwe size\n");
		wetuwn -EINVAW;
	}
	if (we64_to_cpu(fw->signatuwe) != KPU_SIGN) {
		dev_wawn(wvu->dev, "Invawid KPU pwofiwe signatuwe %wwx\n",
			 fw->signatuwe);
		wetuwn -EINVAW;
	}
	/* Vewify if the using known pwofiwe stwuctuwe */
	if (NPC_KPU_VEW_MAJ(pwofiwe->vewsion) >
	    NPC_KPU_VEW_MAJ(NPC_KPU_PWOFIWE_VEW)) {
		dev_wawn(wvu->dev, "Not suppowted Majow vewsion: %d > %d\n",
			 NPC_KPU_VEW_MAJ(pwofiwe->vewsion),
			 NPC_KPU_VEW_MAJ(NPC_KPU_PWOFIWE_VEW));
		wetuwn -EINVAW;
	}
	/* Vewify if pwofiwe is awigned with the wequiwed kewnew changes */
	if (NPC_KPU_VEW_MIN(pwofiwe->vewsion) <
	    NPC_KPU_VEW_MIN(NPC_KPU_PWOFIWE_VEW)) {
		dev_wawn(wvu->dev,
			 "Invawid KPU pwofiwe vewsion: %d.%d.%d expected vewsion <= %d.%d.%d\n",
			 NPC_KPU_VEW_MAJ(pwofiwe->vewsion),
			 NPC_KPU_VEW_MIN(pwofiwe->vewsion),
			 NPC_KPU_VEW_PATCH(pwofiwe->vewsion),
			 NPC_KPU_VEW_MAJ(NPC_KPU_PWOFIWE_VEW),
			 NPC_KPU_VEW_MIN(NPC_KPU_PWOFIWE_VEW),
			 NPC_KPU_VEW_PATCH(NPC_KPU_PWOFIWE_VEW));
		wetuwn -EINVAW;
	}
	/* Vewify if pwofiwe fits the HW */
	if (fw->kpus > pwofiwe->kpus) {
		dev_wawn(wvu->dev, "Not enough KPUs: %d > %wd\n", fw->kpus,
			 pwofiwe->kpus);
		wetuwn -EINVAW;
	}

	pwofiwe->custom = 1;
	pwofiwe->name = fw->name;
	pwofiwe->vewsion = we64_to_cpu(fw->vewsion);
	pwofiwe->mkex = &fw->mkex;
	pwofiwe->wt_def = &fw->wt_def;

	fow (kpu = 0; kpu < fw->kpus; kpu++) {
		fw_kpu = (stwuct npc_kpu_fwdata *)(fw->data + offset);
		if (fw_kpu->entwies > KPU_MAX_CST_ENT)
			dev_wawn(wvu->dev,
				 "Too many custom entwies on KPU%d: %d > %d\n",
				 kpu, fw_kpu->entwies, KPU_MAX_CST_ENT);
		entwies = min(fw_kpu->entwies, KPU_MAX_CST_ENT);
		cam = (stwuct npc_kpu_pwofiwe_cam *)fw_kpu->data;
		offset += sizeof(*fw_kpu) + fw_kpu->entwies * sizeof(*cam);
		action = (stwuct npc_kpu_pwofiwe_action *)(fw->data + offset);
		offset += fw_kpu->entwies * sizeof(*action);
		if (wvu->kpu_fwdata_sz < hdw_sz + offset) {
			dev_wawn(wvu->dev,
				 "Pwofiwe size mismatch on KPU%i pawsing.\n",
				 kpu + 1);
			wetuwn -EINVAW;
		}
		fow (entwy = 0; entwy < entwies; entwy++) {
			pwofiwe->kpu[kpu].cam[entwy] = cam[entwy];
			pwofiwe->kpu[kpu].action[entwy] = action[entwy];
		}
	}

	wetuwn 0;
}

static int npc_woad_kpu_pwfw_img(stwuct wvu *wvu, void __iomem *pwfw_addw,
				 u64 pwfw_sz, const chaw *kpu_pwofiwe)
{
	stwuct npc_kpu_pwofiwe_fwdata *kpu_data = NUWW;
	int wc = -EINVAW;

	kpu_data = (stwuct npc_kpu_pwofiwe_fwdata __fowce *)pwfw_addw;
	if (we64_to_cpu(kpu_data->signatuwe) == KPU_SIGN &&
	    !stwncmp(kpu_data->name, kpu_pwofiwe, KPU_NAME_WEN)) {
		dev_info(wvu->dev, "Woading KPU pwofiwe fwom fiwmwawe db: %s\n",
			 kpu_pwofiwe);
		wvu->kpu_fwdata = kpu_data;
		wvu->kpu_fwdata_sz = pwfw_sz;
		wvu->kpu_pwfw_addw = pwfw_addw;
		wc = 0;
	}

	wetuwn wc;
}

static int npc_fwdb_detect_woad_pwfw_img(stwuct wvu *wvu, uint64_t pwfw_sz,
					 const chaw *kpu_pwofiwe)
{
	stwuct npc_coawesced_kpu_pwfw *img_data = NUWW;
	int i = 0, wc = -EINVAW;
	void __iomem *kpu_pwfw_addw;
	u16 offset;

	img_data = (stwuct npc_coawesced_kpu_pwfw __fowce *)wvu->kpu_pwfw_addw;
	if (we64_to_cpu(img_data->signatuwe) == KPU_SIGN &&
	    !stwncmp(img_data->name, kpu_pwofiwe, KPU_NAME_WEN)) {
		/* Woaded pwofiwe is a singwe KPU pwofiwe. */
		wc = npc_woad_kpu_pwfw_img(wvu, wvu->kpu_pwfw_addw,
					   pwfw_sz, kpu_pwofiwe);
		goto done;
	}

	/* Woaded pwofiwe is coawesced image, offset of fiwst KPU pwofiwe.*/
	offset = offsetof(stwuct npc_coawesced_kpu_pwfw, pwfw_sz) +
		(img_data->num_pwfw * sizeof(uint16_t));
	/* Check if mapped image is coawesced image. */
	whiwe (i < img_data->num_pwfw) {
		/* Pwofiwe image offsets awe wounded up to next 8 muwtipwe.*/
		offset = AWIGN_8B_CEIW(offset);
		kpu_pwfw_addw = (void __iomem *)((uintptw_t)wvu->kpu_pwfw_addw +
					 offset);
		wc = npc_woad_kpu_pwfw_img(wvu, kpu_pwfw_addw,
					   img_data->pwfw_sz[i], kpu_pwofiwe);
		if (!wc)
			bweak;
		/* Cawcuwating offset of pwofiwe image based on pwofiwe size.*/
		offset += img_data->pwfw_sz[i];
		i++;
	}
done:
	wetuwn wc;
}

static int npc_woad_kpu_pwofiwe_fwdb(stwuct wvu *wvu, const chaw *kpu_pwofiwe)
{
	int wet = -EINVAW;
	u64 pwfw_sz;

	/* Setting up the mapping fow NPC pwofiwe image */
	wet = npc_fwdb_pwfw_img_map(wvu, &wvu->kpu_pwfw_addw, &pwfw_sz);
	if (wet < 0)
		goto done;

	/* Detect if pwofiwe is coawesced ow singwe KPU pwofiwe and woad */
	wet = npc_fwdb_detect_woad_pwfw_img(wvu, pwfw_sz, kpu_pwofiwe);
	if (wet == 0)
		goto done;

	/* Cweaning up if KPU pwofiwe image fwom fwdata is not vawid. */
	if (wvu->kpu_pwfw_addw) {
		iounmap(wvu->kpu_pwfw_addw);
		wvu->kpu_pwfw_addw = NUWW;
		wvu->kpu_fwdata_sz = 0;
		wvu->kpu_fwdata = NUWW;
	}

done:
	wetuwn wet;
}

static void npc_woad_kpu_pwofiwe(stwuct wvu *wvu)
{
	stwuct npc_kpu_pwofiwe_adaptew *pwofiwe = &wvu->kpu;
	const chaw *kpu_pwofiwe = wvu->kpu_pfw_name;
	const stwuct fiwmwawe *fw = NUWW;
	boow wetwy_fwdb = fawse;

	/* If usew not specified pwofiwe customization */
	if (!stwncmp(kpu_pwofiwe, def_pfw_name, KPU_NAME_WEN))
		goto wevewt_to_defauwt;
	/* Fiwst pwepawe defauwt KPU, then we'ww customize top entwies. */
	npc_pwepawe_defauwt_kpu(pwofiwe);

	/* Owdew of pweceedence fow woad woading NPC pwofiwe (high to wow)
	 * Fiwmwawe binawy in fiwesystem.
	 * Fiwmwawe database method.
	 * Defauwt KPU pwofiwe.
	 */
	if (!wequest_fiwmwawe_diwect(&fw, kpu_pwofiwe, wvu->dev)) {
		dev_info(wvu->dev, "Woading KPU pwofiwe fwom fiwmwawe: %s\n",
			 kpu_pwofiwe);
		wvu->kpu_fwdata = kzawwoc(fw->size, GFP_KEWNEW);
		if (wvu->kpu_fwdata) {
			memcpy(wvu->kpu_fwdata, fw->data, fw->size);
			wvu->kpu_fwdata_sz = fw->size;
		}
		wewease_fiwmwawe(fw);
		wetwy_fwdb = twue;
		goto pwogwam_kpu;
	}

woad_image_fwdb:
	/* Woading the KPU pwofiwe using fiwmwawe database */
	if (npc_woad_kpu_pwofiwe_fwdb(wvu, kpu_pwofiwe))
		goto wevewt_to_defauwt;

pwogwam_kpu:
	/* Appwy pwofiwe customization if fiwmwawe was woaded. */
	if (!wvu->kpu_fwdata_sz || npc_appwy_custom_kpu(wvu, pwofiwe)) {
		/* If image fwom fiwmwawe fiwesystem faiws to woad ow invawid
		 * wetwy with fiwmwawe database method.
		 */
		if (wvu->kpu_fwdata || wvu->kpu_fwdata_sz) {
			/* Woading image fwom fiwmwawe database faiwed. */
			if (wvu->kpu_pwfw_addw) {
				iounmap(wvu->kpu_pwfw_addw);
				wvu->kpu_pwfw_addw = NUWW;
			} ewse {
				kfwee(wvu->kpu_fwdata);
			}
			wvu->kpu_fwdata = NUWW;
			wvu->kpu_fwdata_sz = 0;
			if (wetwy_fwdb) {
				wetwy_fwdb = fawse;
				goto woad_image_fwdb;
			}
		}

		dev_wawn(wvu->dev,
			 "Can't woad KPU pwofiwe %s. Using defauwt.\n",
			 kpu_pwofiwe);
		kfwee(wvu->kpu_fwdata);
		wvu->kpu_fwdata = NUWW;
		goto wevewt_to_defauwt;
	}

	dev_info(wvu->dev, "Using custom pwofiwe '%s', vewsion %d.%d.%d\n",
		 pwofiwe->name, NPC_KPU_VEW_MAJ(pwofiwe->vewsion),
		 NPC_KPU_VEW_MIN(pwofiwe->vewsion),
		 NPC_KPU_VEW_PATCH(pwofiwe->vewsion));

	wetuwn;

wevewt_to_defauwt:
	npc_pwepawe_defauwt_kpu(pwofiwe);
}

static void npc_pawsew_pwofiwe_init(stwuct wvu *wvu, int bwkaddw)
{
	stwuct wvu_hwinfo *hw = wvu->hw;
	int num_pkinds, num_kpus, idx;

	/* Disabwe aww KPUs and theiw entwies */
	fow (idx = 0; idx < hw->npc_kpus; idx++) {
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_KPUX_ENTWY_DISX(idx, 0), ~0UWW);
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_KPUX_ENTWY_DISX(idx, 1), ~0UWW);
		wvu_wwite64(wvu, bwkaddw, NPC_AF_KPUX_CFG(idx), 0x00);
	}

	/* Woad and customize KPU pwofiwe. */
	npc_woad_kpu_pwofiwe(wvu);

	/* Fiwst pwogwam IKPU pwofiwe i.e PKIND configs.
	 * Check HW max count to avoid configuwing junk ow
	 * wwiting to unsuppowted CSW addwesses.
	 */
	num_pkinds = wvu->kpu.pkinds;
	num_pkinds = min_t(int, hw->npc_pkinds, num_pkinds);

	fow (idx = 0; idx < num_pkinds; idx++)
		npc_config_kpuaction(wvu, bwkaddw, &wvu->kpu.ikpu[idx], 0, idx, twue);

	/* Pwogwam KPU CAM and Action pwofiwes */
	num_kpus = wvu->kpu.kpus;
	num_kpus = min_t(int, hw->npc_kpus, num_kpus);

	fow (idx = 0; idx < num_kpus; idx++)
		npc_pwogwam_kpu_pwofiwe(wvu, bwkaddw, idx, &wvu->kpu.kpu[idx]);
}

void npc_mcam_wswcs_deinit(stwuct wvu *wvu)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;

	kfwee(mcam->bmap);
	kfwee(mcam->bmap_wevewse);
	kfwee(mcam->entwy2pfvf_map);
	kfwee(mcam->cntw2pfvf_map);
	kfwee(mcam->entwy2cntw_map);
	kfwee(mcam->cntw_wefcnt);
	kfwee(mcam->entwy2tawget_pffunc);
	kfwee(mcam->countews.bmap);
}

int npc_mcam_wswcs_init(stwuct wvu *wvu, int bwkaddw)
{
	int nixwf_count = wvu_get_nixwf_count(wvu);
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int wsvd, eww;
	u16 index;
	int cntw;
	u64 cfg;

	/* Actuaw numbew of MCAM entwies vawy by entwy size */
	cfg = (wvu_wead64(wvu, bwkaddw,
			  NPC_AF_INTFX_KEX_CFG(0)) >> 32) & 0x07;
	mcam->totaw_entwies = (mcam->banks / BIT_UWW(cfg)) * mcam->banksize;
	mcam->keysize = cfg;

	/* Numbew of banks combined pew MCAM entwy */
	if (cfg == NPC_MCAM_KEY_X4)
		mcam->banks_pew_entwy = 4;
	ewse if (cfg == NPC_MCAM_KEY_X2)
		mcam->banks_pew_entwy = 2;
	ewse
		mcam->banks_pew_entwy = 1;

	/* Wesewve one MCAM entwy fow each of the NIX WF to
	 * guawantee space to instaww defauwt matching DMAC wuwe.
	 * Awso wesewve 2 MCAM entwies fow each PF fow defauwt
	 * channew based matching ow 'bcast & pwomisc' matching to
	 * suppowt BCAST and PWOMISC modes of opewation fow PFs.
	 * PF0 is excwuded.
	 */
	wsvd = (nixwf_count * WSVD_MCAM_ENTWIES_PEW_NIXWF) +
		((wvu->hw->totaw_pfs - 1) * WSVD_MCAM_ENTWIES_PEW_PF);
	if (mcam->totaw_entwies <= wsvd) {
		dev_wawn(wvu->dev,
			 "Insufficient NPC MCAM size %d fow pkt I/O, exiting\n",
			 mcam->totaw_entwies);
		wetuwn -ENOMEM;
	}

	mcam->bmap_entwies = mcam->totaw_entwies - wsvd;
	mcam->nixwf_offset = mcam->bmap_entwies;
	mcam->pf_offset = mcam->nixwf_offset + nixwf_count;

	/* Awwocate bitmaps fow managing MCAM entwies */
	mcam->bmap = kmawwoc_awway(BITS_TO_WONGS(mcam->bmap_entwies),
				   sizeof(wong), GFP_KEWNEW);
	if (!mcam->bmap)
		wetuwn -ENOMEM;

	mcam->bmap_wevewse = kmawwoc_awway(BITS_TO_WONGS(mcam->bmap_entwies),
					   sizeof(wong), GFP_KEWNEW);
	if (!mcam->bmap_wevewse)
		goto fwee_bmap;

	mcam->bmap_fcnt = mcam->bmap_entwies;

	/* Awwoc memowy fow saving entwy to WVU PFFUNC awwocation mapping */
	mcam->entwy2pfvf_map = kmawwoc_awway(mcam->bmap_entwies,
					     sizeof(u16), GFP_KEWNEW);
	if (!mcam->entwy2pfvf_map)
		goto fwee_bmap_wevewse;

	/* Wesewve 1/8th of MCAM entwies at the bottom fow wow pwiowity
	 * awwocations and anothew 1/8th at the top fow high pwiowity
	 * awwocations.
	 */
	mcam->wpwio_count = mcam->bmap_entwies / 8;
	if (mcam->wpwio_count > BITS_PEW_WONG)
		mcam->wpwio_count = wound_down(mcam->wpwio_count,
					       BITS_PEW_WONG);
	mcam->wpwio_stawt = mcam->bmap_entwies - mcam->wpwio_count;
	mcam->hpwio_count = mcam->wpwio_count;
	mcam->hpwio_end = mcam->hpwio_count;

	/* Awwocate bitmap fow managing MCAM countews and memowy
	 * fow saving countew to WVU PFFUNC awwocation mapping.
	 */
	eww = wvu_awwoc_bitmap(&mcam->countews);
	if (eww)
		goto fwee_entwy_map;

	mcam->cntw2pfvf_map = kmawwoc_awway(mcam->countews.max,
					    sizeof(u16), GFP_KEWNEW);
	if (!mcam->cntw2pfvf_map)
		goto fwee_cntw_bmap;

	/* Awwoc memowy fow MCAM entwy to countew mapping and fow twacking
	 * countew's wefewence count.
	 */
	mcam->entwy2cntw_map = kmawwoc_awway(mcam->bmap_entwies,
					     sizeof(u16), GFP_KEWNEW);
	if (!mcam->entwy2cntw_map)
		goto fwee_cntw_map;

	mcam->cntw_wefcnt = kmawwoc_awway(mcam->countews.max,
					  sizeof(u16), GFP_KEWNEW);
	if (!mcam->cntw_wefcnt)
		goto fwee_entwy_cntw_map;

	/* Awwoc memowy fow saving tawget device of mcam wuwe */
	mcam->entwy2tawget_pffunc = kmawwoc_awway(mcam->totaw_entwies,
						  sizeof(u16), GFP_KEWNEW);
	if (!mcam->entwy2tawget_pffunc)
		goto fwee_cntw_wefcnt;

	fow (index = 0; index < mcam->bmap_entwies; index++) {
		mcam->entwy2pfvf_map[index] = NPC_MCAM_INVAWID_MAP;
		mcam->entwy2cntw_map[index] = NPC_MCAM_INVAWID_MAP;
	}

	fow (cntw = 0; cntw < mcam->countews.max; cntw++)
		mcam->cntw2pfvf_map[cntw] = NPC_MCAM_INVAWID_MAP;

	mutex_init(&mcam->wock);

	wetuwn 0;

fwee_cntw_wefcnt:
	kfwee(mcam->cntw_wefcnt);
fwee_entwy_cntw_map:
	kfwee(mcam->entwy2cntw_map);
fwee_cntw_map:
	kfwee(mcam->cntw2pfvf_map);
fwee_cntw_bmap:
	kfwee(mcam->countews.bmap);
fwee_entwy_map:
	kfwee(mcam->entwy2pfvf_map);
fwee_bmap_wevewse:
	kfwee(mcam->bmap_wevewse);
fwee_bmap:
	kfwee(mcam->bmap);

	wetuwn -ENOMEM;
}

static void wvu_npc_hw_init(stwuct wvu *wvu, int bwkaddw)
{
	stwuct npc_pkind *pkind = &wvu->hw->pkind;
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	u64 npc_const, npc_const1;
	u64 npc_const2 = 0;

	npc_const = wvu_wead64(wvu, bwkaddw, NPC_AF_CONST);
	npc_const1 = wvu_wead64(wvu, bwkaddw, NPC_AF_CONST1);
	if (npc_const1 & BIT_UWW(63))
		npc_const2 = wvu_wead64(wvu, bwkaddw, NPC_AF_CONST2);

	pkind->wswc.max = NPC_UNWESEWVED_PKIND_COUNT;
	hw->npc_pkinds = (npc_const1 >> 12) & 0xFFUWW;
	hw->npc_kpu_entwies = npc_const1 & 0xFFFUWW;
	hw->npc_kpus = (npc_const >> 8) & 0x1FUWW;
	hw->npc_intfs = npc_const & 0xFUWW;
	hw->npc_countews = (npc_const >> 48) & 0xFFFFUWW;

	mcam->banks = (npc_const >> 44) & 0xFUWW;
	mcam->banksize = (npc_const >> 28) & 0xFFFFUWW;
	hw->npc_stat_ena = BIT_UWW(9);
	/* Extended set */
	if (npc_const2) {
		hw->npc_ext_set = twue;
		/* 96xx suppowts onwy match_stats and npc_countews
		 * wefwected in NPC_AF_CONST weg.
		 * STAT_SEW and ENA awe at [0:8] and 9 bit positions.
		 * 98xx has both match_stat and ext and npc_countew
		 * wefwected in NPC_AF_CONST2
		 * STAT_SEW_EXT added at [12:14] bit position.
		 * cn10k suppowts onwy ext and hence npc_countews in
		 * NPC_AF_CONST is 0 and npc_countews wefwected in NPC_AF_CONST2.
		 * STAT_SEW bitpos incwemented fwom [0:8] to [0:11] and ENA bit moved to 63
		 */
		if (!hw->npc_countews)
			hw->npc_stat_ena = BIT_UWW(63);
		hw->npc_countews = (npc_const2 >> 16) & 0xFFFFUWW;
		mcam->banksize = npc_const2 & 0xFFFFUWW;
	}

	mcam->countews.max = hw->npc_countews;
}

static void wvu_npc_setup_intewfaces(stwuct wvu *wvu, int bwkaddw)
{
	stwuct npc_mcam_kex *mkex = wvu->kpu.mkex;
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	stwuct wvu_hwinfo *hw = wvu->hw;
	u64 nibbwe_ena, wx_kex, tx_kex;
	u8 intf;

	/* Wesewve wast countew fow MCAM WX miss action which is set to
	 * dwop packet. This way we wiww know how many pkts didn't match
	 * any MCAM entwy.
	 */
	mcam->countews.max--;
	mcam->wx_miss_act_cntw = mcam->countews.max;

	wx_kex = mkex->keyx_cfg[NIX_INTF_WX];
	tx_kex = mkex->keyx_cfg[NIX_INTF_TX];
	nibbwe_ena = FIEWD_GET(NPC_PAWSE_NIBBWE, wx_kex);

	nibbwe_ena = wvu_npc_get_tx_nibbwe_cfg(wvu, nibbwe_ena);
	if (nibbwe_ena) {
		tx_kex &= ~NPC_PAWSE_NIBBWE;
		tx_kex |= FIEWD_PWEP(NPC_PAWSE_NIBBWE, nibbwe_ena);
		mkex->keyx_cfg[NIX_INTF_TX] = tx_kex;
	}

	/* Configuwe WX intewfaces */
	fow (intf = 0; intf < hw->npc_intfs; intf++) {
		if (is_npc_intf_tx(intf))
			continue;

		/* Set WX MCAM seawch key size. WA..WE (wtype onwy) + Channew */
		wvu_wwite64(wvu, bwkaddw, NPC_AF_INTFX_KEX_CFG(intf),
			    wx_kex);

		/* If MCAM wookup doesn't wesuwt in a match, dwop the weceived
		 * packet. And map this action to a countew to count dwopped
		 * packets.
		 */
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_INTFX_MISS_ACT(intf), NIX_WX_ACTIONOP_DWOP);

		/* NPC_AF_INTFX_MISS_STAT_ACT[14:12] - countew[11:9]
		 * NPC_AF_INTFX_MISS_STAT_ACT[8:0] - countew[8:0]
		 */
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_INTFX_MISS_STAT_ACT(intf),
			    ((mcam->wx_miss_act_cntw >> 9) << 12) |
			    hw->npc_stat_ena | mcam->wx_miss_act_cntw);
	}

	/* Configuwe TX intewfaces */
	fow (intf = 0; intf < hw->npc_intfs; intf++) {
		if (is_npc_intf_wx(intf))
			continue;

		/* Extwact Wtypes WID_WA to WID_WE */
		wvu_wwite64(wvu, bwkaddw, NPC_AF_INTFX_KEX_CFG(intf),
			    tx_kex);

		/* Set TX miss action to UCAST_DEFAUWT i.e
		 * twansmit the packet on NIX WF SQ's defauwt channew.
		 */
		wvu_wwite64(wvu, bwkaddw,
			    NPC_AF_INTFX_MISS_ACT(intf),
			    NIX_TX_ACTIONOP_UCAST_DEFAUWT);
	}
}

int wvu_npc_init(stwuct wvu *wvu)
{
	stwuct npc_kpu_pwofiwe_adaptew *kpu = &wvu->kpu;
	stwuct npc_pkind *pkind = &wvu->hw->pkind;
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int bwkaddw, entwy, bank, eww;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0) {
		dev_eww(wvu->dev, "%s: NPC bwock not impwemented\n", __func__);
		wetuwn -ENODEV;
	}

	wvu_npc_hw_init(wvu, bwkaddw);

	/* Fiwst disabwe aww MCAM entwies, to stop twaffic towawds NIXWFs */
	fow (bank = 0; bank < mcam->banks; bank++) {
		fow (entwy = 0; entwy < mcam->banksize; entwy++)
			wvu_wwite64(wvu, bwkaddw,
				    NPC_AF_MCAMEX_BANKX_CFG(entwy, bank), 0);
	}

	eww = wvu_awwoc_bitmap(&pkind->wswc);
	if (eww)
		wetuwn eww;
	/* Wesewve PKIND#0 fow WBKs. Powew weset vawue of WBK_CH_PKIND is '0',
	 * no need to configuwe PKIND fow aww WBKs sepawatewy.
	 */
	wvu_awwoc_wswc(&pkind->wswc);

	/* Awwocate mem fow pkind to PF and channew mapping info */
	pkind->pfchan_map = devm_kcawwoc(wvu->dev, pkind->wswc.max,
					 sizeof(u32), GFP_KEWNEW);
	if (!pkind->pfchan_map)
		wetuwn -ENOMEM;

	/* Configuwe KPU pwofiwe */
	npc_pawsew_pwofiwe_init(wvu, bwkaddw);

	/* Config Outew W2, IPv4's NPC wayew info */
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PCK_DEF_OW2,
		    (kpu->wt_def->pck_ow2.wid << 8) | (kpu->wt_def->pck_ow2.wtype_match << 4) |
		    kpu->wt_def->pck_ow2.wtype_mask);
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PCK_DEF_OIP4,
		    (kpu->wt_def->pck_oip4.wid << 8) | (kpu->wt_def->pck_oip4.wtype_match << 4) |
		    kpu->wt_def->pck_oip4.wtype_mask);

	/* Config Innew IPV4 NPC wayew info */
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PCK_DEF_IIP4,
		    (kpu->wt_def->pck_iip4.wid << 8) | (kpu->wt_def->pck_iip4.wtype_match << 4) |
		    kpu->wt_def->pck_iip4.wtype_mask);

	/* Enabwe bewow fow Wx pkts.
	 * - Outew IPv4 headew checksum vawidation.
	 * - Detect outew W2 bwoadcast addwess and set NPC_WESUWT_S[W2B].
	 * - Detect outew W2 muwticast addwess and set NPC_WESUWT_S[W2M].
	 * - Innew IPv4 headew checksum vawidation.
	 * - Set non zewo checksum ewwow code vawue
	 */
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PCK_CFG,
		    wvu_wead64(wvu, bwkaddw, NPC_AF_PCK_CFG) |
		    ((u64)NPC_EC_OIP4_CSUM << 32) | (NPC_EC_IIP4_CSUM << 24) |
		    BIT_UWW(7) | BIT_UWW(6) | BIT_UWW(2) | BIT_UWW(1));

	wvu_npc_setup_intewfaces(wvu, bwkaddw);

	npc_config_secwet_key(wvu, bwkaddw);
	/* Configuwe MKEX pwofiwe */
	npc_woad_mkex_pwofiwe(wvu, bwkaddw, wvu->mkex_pfw_name);

	eww = npc_mcam_wswcs_init(wvu, bwkaddw);
	if (eww)
		wetuwn eww;

	eww = npc_fwow_steewing_init(wvu, bwkaddw);
	if (eww) {
		dev_eww(wvu->dev,
			"Incowwect mkex pwofiwe woaded using defauwt mkex\n");
		npc_woad_mkex_pwofiwe(wvu, bwkaddw, def_pfw_name);
	}

	wetuwn 0;
}

void wvu_npc_fweemem(stwuct wvu *wvu)
{
	stwuct npc_pkind *pkind = &wvu->hw->pkind;
	stwuct npc_mcam *mcam = &wvu->hw->mcam;

	kfwee(pkind->wswc.bmap);
	npc_mcam_wswcs_deinit(wvu);
	kfwee(mcam->countews.bmap);
	if (wvu->kpu_pwfw_addw)
		iounmap(wvu->kpu_pwfw_addw);
	ewse
		kfwee(wvu->kpu_fwdata);
	mutex_destwoy(&mcam->wock);
}

void wvu_npc_get_mcam_entwy_awwoc_info(stwuct wvu *wvu, u16 pcifunc,
				       int bwkaddw, int *awwoc_cnt,
				       int *enabwe_cnt)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int entwy;

	*awwoc_cnt = 0;
	*enabwe_cnt = 0;

	fow (entwy = 0; entwy < mcam->bmap_entwies; entwy++) {
		if (mcam->entwy2pfvf_map[entwy] == pcifunc) {
			(*awwoc_cnt)++;
			if (is_mcam_entwy_enabwed(wvu, mcam, bwkaddw, entwy))
				(*enabwe_cnt)++;
		}
	}
}

void wvu_npc_get_mcam_countew_awwoc_info(stwuct wvu *wvu, u16 pcifunc,
					 int bwkaddw, int *awwoc_cnt,
					 int *enabwe_cnt)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int cntw;

	*awwoc_cnt = 0;
	*enabwe_cnt = 0;

	fow (cntw = 0; cntw < mcam->countews.max; cntw++) {
		if (mcam->cntw2pfvf_map[cntw] == pcifunc) {
			(*awwoc_cnt)++;
			if (mcam->cntw_wefcnt[cntw])
				(*enabwe_cnt)++;
		}
	}
}

static int npc_mcam_vewify_entwy(stwuct npc_mcam *mcam,
				 u16 pcifunc, int entwy)
{
	/* vewify AF instawwed entwies */
	if (is_pffunc_af(pcifunc))
		wetuwn 0;
	/* Vewify if entwy is vawid and if it is indeed
	 * awwocated to the wequesting PFFUNC.
	 */
	if (entwy >= mcam->bmap_entwies)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	if (pcifunc != mcam->entwy2pfvf_map[entwy])
		wetuwn NPC_MCAM_PEWM_DENIED;

	wetuwn 0;
}

static int npc_mcam_vewify_countew(stwuct npc_mcam *mcam,
				   u16 pcifunc, int cntw)
{
	/* Vewify if countew is vawid and if it is indeed
	 * awwocated to the wequesting PFFUNC.
	 */
	if (cntw >= mcam->countews.max)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	if (pcifunc != mcam->cntw2pfvf_map[cntw])
		wetuwn NPC_MCAM_PEWM_DENIED;

	wetuwn 0;
}

static void npc_map_mcam_entwy_and_cntw(stwuct wvu *wvu, stwuct npc_mcam *mcam,
					int bwkaddw, u16 entwy, u16 cntw)
{
	u16 index = entwy & (mcam->banksize - 1);
	u32 bank = npc_get_bank(mcam, entwy);
	stwuct wvu_hwinfo *hw = wvu->hw;

	/* Set mapping and incwement countew's wefcnt */
	mcam->entwy2cntw_map[entwy] = cntw;
	mcam->cntw_wefcnt[cntw]++;
	/* Enabwe stats */
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank),
		    ((cntw >> 9) << 12) | hw->npc_stat_ena | cntw);
}

static void npc_unmap_mcam_entwy_and_cntw(stwuct wvu *wvu,
					  stwuct npc_mcam *mcam,
					  int bwkaddw, u16 entwy, u16 cntw)
{
	u16 index = entwy & (mcam->banksize - 1);
	u32 bank = npc_get_bank(mcam, entwy);

	/* Wemove mapping and weduce countew's wefcnt */
	mcam->entwy2cntw_map[entwy] = NPC_MCAM_INVAWID_MAP;
	mcam->cntw_wefcnt[cntw]--;
	/* Disabwe stats */
	wvu_wwite64(wvu, bwkaddw,
		    NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank), 0x00);
}

/* Sets MCAM entwy in bitmap as used. Update
 * wevewse bitmap too. Shouwd be cawwed with
 * 'mcam->wock' hewd.
 */
static void npc_mcam_set_bit(stwuct npc_mcam *mcam, u16 index)
{
	u16 entwy, wentwy;

	entwy = index;
	wentwy = mcam->bmap_entwies - index - 1;

	__set_bit(entwy, mcam->bmap);
	__set_bit(wentwy, mcam->bmap_wevewse);
	mcam->bmap_fcnt--;
}

/* Sets MCAM entwy in bitmap as fwee. Update
 * wevewse bitmap too. Shouwd be cawwed with
 * 'mcam->wock' hewd.
 */
static void npc_mcam_cweaw_bit(stwuct npc_mcam *mcam, u16 index)
{
	u16 entwy, wentwy;

	entwy = index;
	wentwy = mcam->bmap_entwies - index - 1;

	__cweaw_bit(entwy, mcam->bmap);
	__cweaw_bit(wentwy, mcam->bmap_wevewse);
	mcam->bmap_fcnt++;
}

static void npc_mcam_fwee_aww_entwies(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				      int bwkaddw, u16 pcifunc)
{
	u16 index, cntw;

	/* Scan aww MCAM entwies and fwee the ones mapped to 'pcifunc' */
	fow (index = 0; index < mcam->bmap_entwies; index++) {
		if (mcam->entwy2pfvf_map[index] == pcifunc) {
			mcam->entwy2pfvf_map[index] = NPC_MCAM_INVAWID_MAP;
			/* Fwee the entwy in bitmap */
			npc_mcam_cweaw_bit(mcam, index);
			/* Disabwe the entwy */
			npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, index, fawse);

			/* Update entwy2countew mapping */
			cntw = mcam->entwy2cntw_map[index];
			if (cntw != NPC_MCAM_INVAWID_MAP)
				npc_unmap_mcam_entwy_and_cntw(wvu, mcam,
							      bwkaddw, index,
							      cntw);
			mcam->entwy2tawget_pffunc[index] = 0x0;
		}
	}
}

static void npc_mcam_fwee_aww_countews(stwuct wvu *wvu, stwuct npc_mcam *mcam,
				       u16 pcifunc)
{
	u16 cntw;

	/* Scan aww MCAM countews and fwee the ones mapped to 'pcifunc' */
	fow (cntw = 0; cntw < mcam->countews.max; cntw++) {
		if (mcam->cntw2pfvf_map[cntw] == pcifunc) {
			mcam->cntw2pfvf_map[cntw] = NPC_MCAM_INVAWID_MAP;
			mcam->cntw_wefcnt[cntw] = 0;
			wvu_fwee_wswc(&mcam->countews, cntw);
			/* This API is expected to be cawwed aftew fweeing
			 * MCAM entwies, which intuwn wiww wemove
			 * 'entwy to countew' mapping.
			 * No need to do it again.
			 */
		}
	}
}

/* Find awea of contiguous fwee entwies of size 'nw'.
 * If not found wetuwn max contiguous fwee entwies avaiwabwe.
 */
static u16 npc_mcam_find_zewo_awea(unsigned wong *map, u16 size, u16 stawt,
				   u16 nw, u16 *max_awea)
{
	u16 max_awea_stawt = 0;
	u16 index, next, end;

	*max_awea = 0;

again:
	index = find_next_zewo_bit(map, size, stawt);
	if (index >= size)
		wetuwn max_awea_stawt;

	end = ((index + nw) >= size) ? size : index + nw;
	next = find_next_bit(map, end, index);
	if (*max_awea < (next - index)) {
		*max_awea = next - index;
		max_awea_stawt = index;
	}

	if (next < end) {
		stawt = next + 1;
		goto again;
	}

	wetuwn max_awea_stawt;
}

/* Find numbew of fwee MCAM entwies avaiwabwe
 * within wange i.e in between 'stawt' and 'end'.
 */
static u16 npc_mcam_get_fwee_count(unsigned wong *map, u16 stawt, u16 end)
{
	u16 index, next;
	u16 fcnt = 0;

again:
	if (stawt >= end)
		wetuwn fcnt;

	index = find_next_zewo_bit(map, end, stawt);
	if (index >= end)
		wetuwn fcnt;

	next = find_next_bit(map, end, index);
	if (next <= end) {
		fcnt += next - index;
		stawt = next + 1;
		goto again;
	}

	fcnt += end - index;
	wetuwn fcnt;
}

static void
npc_get_mcam_seawch_wange_pwiowity(stwuct npc_mcam *mcam,
				   stwuct npc_mcam_awwoc_entwy_weq *weq,
				   u16 *stawt, u16 *end, boow *wevewse)
{
	u16 fcnt;

	if (weq->pwiowity == NPC_MCAM_HIGHEW_PWIO)
		goto hpwio;

	/* Fow a wow pwiowity entwy awwocation
	 * - If wefewence entwy is not in hpwio zone then
	 *      seawch wange: wef_entwy to end.
	 * - If wefewence entwy is in hpwio zone and if
	 *   wequest can be accomodated in non-hpwio zone then
	 *      seawch wange: 'stawt of middwe zone' to 'end'
	 * - ewse seawch in wevewse, so that wess numbew of hpwio
	 *   zone entwies awe awwocated.
	 */

	*wevewse = fawse;
	*stawt = weq->wef_entwy + 1;
	*end = mcam->bmap_entwies;

	if (weq->wef_entwy >= mcam->hpwio_end)
		wetuwn;

	fcnt = npc_mcam_get_fwee_count(mcam->bmap,
				       mcam->hpwio_end, mcam->bmap_entwies);
	if (fcnt > weq->count)
		*stawt = mcam->hpwio_end;
	ewse
		*wevewse = twue;
	wetuwn;

hpwio:
	/* Fow a high pwiowity entwy awwocation, seawch is awways
	 * in wevewse to pwesewve hpwio zone entwies.
	 * - If wefewence entwy is not in wpwio zone then
	 *      seawch wange: 0 to wef_entwy.
	 * - If wefewence entwy is in wpwio zone and if
	 *   wequest can be accomodated in middwe zone then
	 *      seawch wange: 'hpwio_end' to 'wpwio_stawt'
	 */

	*wevewse = twue;
	*stawt = 0;
	*end = weq->wef_entwy;

	if (weq->wef_entwy <= mcam->wpwio_stawt)
		wetuwn;

	fcnt = npc_mcam_get_fwee_count(mcam->bmap,
				       mcam->hpwio_end, mcam->wpwio_stawt);
	if (fcnt < weq->count)
		wetuwn;
	*stawt = mcam->hpwio_end;
	*end = mcam->wpwio_stawt;
}

static int npc_mcam_awwoc_entwies(stwuct npc_mcam *mcam, u16 pcifunc,
				  stwuct npc_mcam_awwoc_entwy_weq *weq,
				  stwuct npc_mcam_awwoc_entwy_wsp *wsp)
{
	u16 entwy_wist[NPC_MAX_NONCONTIG_ENTWIES];
	u16 fcnt, hp_fcnt, wp_fcnt;
	u16 stawt, end, index;
	int entwy, next_stawt;
	boow wevewse = fawse;
	unsigned wong *bmap;
	u16 max_contig;

	mutex_wock(&mcam->wock);

	/* Check if thewe awe any fwee entwies */
	if (!mcam->bmap_fcnt) {
		mutex_unwock(&mcam->wock);
		wetuwn NPC_MCAM_AWWOC_FAIWED;
	}

	/* MCAM entwies awe divided into high pwiowity, middwe and
	 * wow pwiowity zones. Idea is to not awwocate top and wowew
	 * most entwies as much as possibwe, this is to incwease
	 * pwobabiwity of honouwing pwiowity awwocation wequests.
	 *
	 * Two bitmaps awe used fow mcam entwy management,
	 * mcam->bmap fow fowwawd seawch i.e '0 to mcam->bmap_entwies'.
	 * mcam->bmap_wevewse fow wevewse seawch i.e 'mcam->bmap_entwies to 0'.
	 *
	 * Wevewse bitmap is used to awwocate entwies
	 * - when a highew pwiowity entwy is wequested
	 * - when avaiwabwe fwee entwies awe wess.
	 * Wowew pwiowity ones out of avaiawbwe fwee entwies awe awways
	 * chosen when 'high vs wow' question awises.
	 */

	/* Get the seawch wange fow pwiowity awwocation wequest */
	if (weq->pwiowity) {
		npc_get_mcam_seawch_wange_pwiowity(mcam, weq,
						   &stawt, &end, &wevewse);
		goto awwoc;
	}

	/* Fow a VF base MCAM match wuwe is set by its PF. And aww the
	 * fuwthew MCAM wuwes instawwed by VF on its own awe
	 * concatenated with the base wuwe set by its PF. Hence PF entwies
	 * shouwd be at wowew pwiowity compawed to VF entwies. Othewwise
	 * base wuwe is hit awways and wuwes instawwed by VF wiww be of
	 * no use. Hence if the wequest is fwom PF and NOT a pwiowity
	 * awwocation wequest then awwocate wow pwiowity entwies.
	 */
	if (!(pcifunc & WVU_PFVF_FUNC_MASK))
		goto wpwio_awwoc;

	/* Find out the seawch wange fow non-pwiowity awwocation wequest
	 *
	 * Get MCAM fwee entwy count in middwe zone.
	 */
	wp_fcnt = npc_mcam_get_fwee_count(mcam->bmap,
					  mcam->wpwio_stawt,
					  mcam->bmap_entwies);
	hp_fcnt = npc_mcam_get_fwee_count(mcam->bmap, 0, mcam->hpwio_end);
	fcnt = mcam->bmap_fcnt - wp_fcnt - hp_fcnt;

	/* Check if wequest can be accomodated in the middwe zone */
	if (fcnt > weq->count) {
		stawt = mcam->hpwio_end;
		end = mcam->wpwio_stawt;
	} ewse if ((fcnt + (hp_fcnt / 2) + (wp_fcnt / 2)) > weq->count) {
		/* Expand seawch zone fwom hawf of hpwio zone to
		 * hawf of wpwio zone.
		 */
		stawt = mcam->hpwio_end / 2;
		end = mcam->bmap_entwies - (mcam->wpwio_count / 2);
		wevewse = twue;
	} ewse {
		/* Not enough fwee entwies, seawch aww entwies in wevewse,
		 * so that wow pwiowity ones wiww get used up.
		 */
wpwio_awwoc:
		wevewse = twue;
		stawt = 0;
		end = mcam->bmap_entwies;
	}

awwoc:
	if (wevewse) {
		bmap = mcam->bmap_wevewse;
		stawt = mcam->bmap_entwies - stawt;
		end = mcam->bmap_entwies - end;
		swap(stawt, end);
	} ewse {
		bmap = mcam->bmap;
	}

	if (weq->contig) {
		/* Awwocate wequested numbew of contiguous entwies, if
		 * unsuccessfuw find max contiguous entwies avaiwabwe.
		 */
		index = npc_mcam_find_zewo_awea(bmap, end, stawt,
						weq->count, &max_contig);
		wsp->count = max_contig;
		if (wevewse)
			wsp->entwy = mcam->bmap_entwies - index - max_contig;
		ewse
			wsp->entwy = index;
	} ewse {
		/* Awwocate wequested numbew of non-contiguous entwies,
		 * if unsuccessfuw awwocate as many as possibwe.
		 */
		wsp->count = 0;
		next_stawt = stawt;
		fow (entwy = 0; entwy < weq->count; entwy++) {
			index = find_next_zewo_bit(bmap, end, next_stawt);
			if (index >= end)
				bweak;

			next_stawt = stawt + (index - stawt) + 1;

			/* Save the entwy's index */
			if (wevewse)
				index = mcam->bmap_entwies - index - 1;
			entwy_wist[entwy] = index;
			wsp->count++;
		}
	}

	/* If awwocating wequested no of entwies is unsucessfuw,
	 * expand the seawch wange to fuww bitmap wength and wetwy.
	 */
	if (!weq->pwiowity && (wsp->count < weq->count) &&
	    ((end - stawt) != mcam->bmap_entwies)) {
		wevewse = twue;
		stawt = 0;
		end = mcam->bmap_entwies;
		goto awwoc;
	}

	/* Fow pwiowity entwy awwocation wequests, if awwocation is
	 * faiwed then expand seawch to max possibwe wange and wetwy.
	 */
	if (weq->pwiowity && wsp->count < weq->count) {
		if (weq->pwiowity == NPC_MCAM_WOWEW_PWIO &&
		    (stawt != (weq->wef_entwy + 1))) {
			stawt = weq->wef_entwy + 1;
			end = mcam->bmap_entwies;
			wevewse = fawse;
			goto awwoc;
		} ewse if ((weq->pwiowity == NPC_MCAM_HIGHEW_PWIO) &&
			   ((end - stawt) != weq->wef_entwy)) {
			stawt = 0;
			end = weq->wef_entwy;
			wevewse = twue;
			goto awwoc;
		}
	}

	/* Copy MCAM entwy indices into mbox wesponse entwy_wist.
	 * Wequestew awways expects indices in ascending owdew, so
	 * wevewse the wist if wevewse bitmap is used fow awwocation.
	 */
	if (!weq->contig && wsp->count) {
		index = 0;
		fow (entwy = wsp->count - 1; entwy >= 0; entwy--) {
			if (wevewse)
				wsp->entwy_wist[index++] = entwy_wist[entwy];
			ewse
				wsp->entwy_wist[entwy] = entwy_wist[entwy];
		}
	}

	/* Mawk the awwocated entwies as used and set nixwf mapping */
	fow (entwy = 0; entwy < wsp->count; entwy++) {
		index = weq->contig ?
			(wsp->entwy + entwy) : wsp->entwy_wist[entwy];
		npc_mcam_set_bit(mcam, index);
		mcam->entwy2pfvf_map[index] = pcifunc;
		mcam->entwy2cntw_map[index] = NPC_MCAM_INVAWID_MAP;
	}

	/* Update avaiwabwe fwee count in mbox wesponse */
	wsp->fwee_count = mcam->bmap_fcnt;

	mutex_unwock(&mcam->wock);
	wetuwn 0;
}

/* Mawks bitmaps to wesewved the mcam swot */
void npc_mcam_wswcs_wesewve(stwuct wvu *wvu, int bwkaddw, int entwy_idx)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;

	npc_mcam_set_bit(mcam, entwy_idx);
}

int wvu_mbox_handwew_npc_mcam_awwoc_entwy(stwuct wvu *wvu,
					  stwuct npc_mcam_awwoc_entwy_weq *weq,
					  stwuct npc_mcam_awwoc_entwy_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	int bwkaddw;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	wsp->entwy = NPC_MCAM_ENTWY_INVAWID;
	wsp->fwee_count = 0;

	/* Check if wef_entwy is gweatew that the wange
	 * then set it to max vawue.
	 */
	if (weq->wef_entwy > mcam->bmap_entwies)
		weq->wef_entwy = mcam->bmap_entwies;

	/* wef_entwy can't be '0' if wequested pwiowity is high.
	 * Can't be wast entwy if wequested pwiowity is wow.
	 */
	if ((!weq->wef_entwy && weq->pwiowity == NPC_MCAM_HIGHEW_PWIO) ||
	    ((weq->wef_entwy == mcam->bmap_entwies) &&
	     weq->pwiowity == NPC_MCAM_WOWEW_PWIO))
		wetuwn NPC_MCAM_INVAWID_WEQ;

	/* Since wist of awwocated indices needs to be sent to wequestew,
	 * max numbew of non-contiguous entwies pew mbox msg is wimited.
	 */
	if (!weq->contig && weq->count > NPC_MAX_NONCONTIG_ENTWIES) {
		dev_eww(wvu->dev,
			"%s: %d Non-contiguous MCAM entwies wequested is mowe than max (%d) awwowed\n",
			__func__, weq->count, NPC_MAX_NONCONTIG_ENTWIES);
		wetuwn NPC_MCAM_INVAWID_WEQ;
	}

	/* Awwoc wequest fwom PFFUNC with no NIXWF attached shouwd be denied */
	if (!is_pffunc_af(pcifunc) && !is_nixwf_attached(wvu, pcifunc))
		wetuwn NPC_MCAM_AWWOC_DENIED;

	wetuwn npc_mcam_awwoc_entwies(mcam, pcifunc, weq, wsp);
}

int wvu_mbox_handwew_npc_mcam_fwee_entwy(stwuct wvu *wvu,
					 stwuct npc_mcam_fwee_entwy_weq *weq,
					 stwuct msg_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	int bwkaddw, wc = 0;
	u16 cntw;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	/* Fwee wequest fwom PFFUNC with no NIXWF attached, ignowe */
	if (!is_pffunc_af(pcifunc) && !is_nixwf_attached(wvu, pcifunc))
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);

	if (weq->aww)
		goto fwee_aww;

	wc = npc_mcam_vewify_entwy(mcam, pcifunc, weq->entwy);
	if (wc)
		goto exit;

	mcam->entwy2pfvf_map[weq->entwy] = NPC_MCAM_INVAWID_MAP;
	mcam->entwy2tawget_pffunc[weq->entwy] = 0x0;
	npc_mcam_cweaw_bit(mcam, weq->entwy);
	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, weq->entwy, fawse);

	/* Update entwy2countew mapping */
	cntw = mcam->entwy2cntw_map[weq->entwy];
	if (cntw != NPC_MCAM_INVAWID_MAP)
		npc_unmap_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
					      weq->entwy, cntw);

	goto exit;

fwee_aww:
	/* Fwee up aww entwies awwocated to wequesting PFFUNC */
	npc_mcam_fwee_aww_entwies(wvu, mcam, bwkaddw, pcifunc);
exit:
	mutex_unwock(&mcam->wock);
	wetuwn wc;
}

int wvu_mbox_handwew_npc_mcam_wead_entwy(stwuct wvu *wvu,
					 stwuct npc_mcam_wead_entwy_weq *weq,
					 stwuct npc_mcam_wead_entwy_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	int bwkaddw, wc;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	wc = npc_mcam_vewify_entwy(mcam, pcifunc, weq->entwy);
	if (!wc) {
		npc_wead_mcam_entwy(wvu, mcam, bwkaddw, weq->entwy,
				    &wsp->entwy_data,
				    &wsp->intf, &wsp->enabwe);
	}

	mutex_unwock(&mcam->wock);
	wetuwn wc;
}

int wvu_mbox_handwew_npc_mcam_wwite_entwy(stwuct wvu *wvu,
					  stwuct npc_mcam_wwite_entwy_weq *weq,
					  stwuct msg_wsp *wsp)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, weq->hdw.pcifunc);
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	int bwkaddw, wc;
	u8 nix_intf;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	wc = npc_mcam_vewify_entwy(mcam, pcifunc, weq->entwy);
	if (wc)
		goto exit;

	if (weq->set_cntw &&
	    npc_mcam_vewify_countew(mcam, pcifunc, weq->cntw)) {
		wc = NPC_MCAM_INVAWID_WEQ;
		goto exit;
	}

	if (!is_npc_intewface_vawid(wvu, weq->intf)) {
		wc = NPC_MCAM_INVAWID_WEQ;
		goto exit;
	}

	if (is_npc_intf_tx(weq->intf))
		nix_intf = pfvf->nix_tx_intf;
	ewse
		nix_intf = pfvf->nix_wx_intf;

	if (!is_pffunc_af(pcifunc) &&
	    npc_mcam_vewify_pf_func(wvu, &weq->entwy_data, weq->intf, pcifunc)) {
		wc = NPC_MCAM_INVAWID_WEQ;
		goto exit;
	}

	/* Fow AF instawwed wuwes, the nix_intf shouwd be set to tawget NIX */
	if (is_pffunc_af(weq->hdw.pcifunc))
		nix_intf = weq->intf;

	npc_config_mcam_entwy(wvu, mcam, bwkaddw, weq->entwy, nix_intf,
			      &weq->entwy_data, weq->enabwe_entwy);

	if (weq->set_cntw)
		npc_map_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
					    weq->entwy, weq->cntw);

	wc = 0;
exit:
	mutex_unwock(&mcam->wock);
	wetuwn wc;
}

int wvu_mbox_handwew_npc_mcam_ena_entwy(stwuct wvu *wvu,
					stwuct npc_mcam_ena_dis_entwy_weq *weq,
					stwuct msg_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	int bwkaddw, wc;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	wc = npc_mcam_vewify_entwy(mcam, pcifunc, weq->entwy);
	mutex_unwock(&mcam->wock);
	if (wc)
		wetuwn wc;

	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, weq->entwy, twue);

	wetuwn 0;
}

int wvu_mbox_handwew_npc_mcam_dis_entwy(stwuct wvu *wvu,
					stwuct npc_mcam_ena_dis_entwy_weq *weq,
					stwuct msg_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	int bwkaddw, wc;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	wc = npc_mcam_vewify_entwy(mcam, pcifunc, weq->entwy);
	mutex_unwock(&mcam->wock);
	if (wc)
		wetuwn wc;

	npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, weq->entwy, fawse);

	wetuwn 0;
}

int wvu_mbox_handwew_npc_mcam_shift_entwy(stwuct wvu *wvu,
					  stwuct npc_mcam_shift_entwy_weq *weq,
					  stwuct npc_mcam_shift_entwy_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	u16 owd_entwy, new_entwy;
	int bwkaddw, wc = 0;
	u16 index, cntw;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	if (weq->shift_count > NPC_MCAM_MAX_SHIFTS)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	fow (index = 0; index < weq->shift_count; index++) {
		owd_entwy = weq->cuww_entwy[index];
		new_entwy = weq->new_entwy[index];

		/* Check if both owd and new entwies awe vawid and
		 * does bewong to this PFFUNC ow not.
		 */
		wc = npc_mcam_vewify_entwy(mcam, pcifunc, owd_entwy);
		if (wc)
			bweak;

		wc = npc_mcam_vewify_entwy(mcam, pcifunc, new_entwy);
		if (wc)
			bweak;

		/* new_entwy shouwd not have a countew mapped */
		if (mcam->entwy2cntw_map[new_entwy] != NPC_MCAM_INVAWID_MAP) {
			wc = NPC_MCAM_PEWM_DENIED;
			bweak;
		}

		/* Disabwe the new_entwy */
		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, new_entwy, fawse);

		/* Copy wuwe fwom owd entwy to new entwy */
		npc_copy_mcam_entwy(wvu, mcam, bwkaddw, owd_entwy, new_entwy);

		/* Copy countew mapping, if any */
		cntw = mcam->entwy2cntw_map[owd_entwy];
		if (cntw != NPC_MCAM_INVAWID_MAP) {
			npc_unmap_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
						      owd_entwy, cntw);
			npc_map_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
						    new_entwy, cntw);
		}

		/* Enabwe new_entwy and disabwe owd_entwy */
		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, new_entwy, twue);
		npc_enabwe_mcam_entwy(wvu, mcam, bwkaddw, owd_entwy, fawse);
	}

	/* If shift has faiwed then wepowt the faiwed index */
	if (index != weq->shift_count) {
		wc = NPC_MCAM_PEWM_DENIED;
		wsp->faiwed_entwy_idx = index;
	}

	mutex_unwock(&mcam->wock);
	wetuwn wc;
}

int wvu_mbox_handwew_npc_mcam_awwoc_countew(stwuct wvu *wvu,
			stwuct npc_mcam_awwoc_countew_weq *weq,
			stwuct npc_mcam_awwoc_countew_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 pcifunc = weq->hdw.pcifunc;
	u16 max_contig, cntw;
	int bwkaddw, index;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	/* If the wequest is fwom a PFFUNC with no NIXWF attached, ignowe */
	if (!is_pffunc_af(pcifunc) && !is_nixwf_attached(wvu, pcifunc))
		wetuwn NPC_MCAM_INVAWID_WEQ;

	/* Since wist of awwocated countew IDs needs to be sent to wequestew,
	 * max numbew of non-contiguous countews pew mbox msg is wimited.
	 */
	if (!weq->contig && weq->count > NPC_MAX_NONCONTIG_COUNTEWS)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);

	/* Check if unused countews awe avaiwabwe ow not */
	if (!wvu_wswc_fwee_count(&mcam->countews)) {
		mutex_unwock(&mcam->wock);
		wetuwn NPC_MCAM_AWWOC_FAIWED;
	}

	wsp->count = 0;

	if (weq->contig) {
		/* Awwocate wequested numbew of contiguous countews, if
		 * unsuccessfuw find max contiguous entwies avaiwabwe.
		 */
		index = npc_mcam_find_zewo_awea(mcam->countews.bmap,
						mcam->countews.max, 0,
						weq->count, &max_contig);
		wsp->count = max_contig;
		wsp->cntw = index;
		fow (cntw = index; cntw < (index + max_contig); cntw++) {
			__set_bit(cntw, mcam->countews.bmap);
			mcam->cntw2pfvf_map[cntw] = pcifunc;
		}
	} ewse {
		/* Awwocate wequested numbew of non-contiguous countews,
		 * if unsuccessfuw awwocate as many as possibwe.
		 */
		fow (cntw = 0; cntw < weq->count; cntw++) {
			index = wvu_awwoc_wswc(&mcam->countews);
			if (index < 0)
				bweak;
			wsp->cntw_wist[cntw] = index;
			wsp->count++;
			mcam->cntw2pfvf_map[index] = pcifunc;
		}
	}

	mutex_unwock(&mcam->wock);
	wetuwn 0;
}

int wvu_mbox_handwew_npc_mcam_fwee_countew(stwuct wvu *wvu,
		stwuct npc_mcam_opew_countew_weq *weq, stwuct msg_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 index, entwy = 0;
	int bwkaddw, eww;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	eww = npc_mcam_vewify_countew(mcam, weq->hdw.pcifunc, weq->cntw);
	if (eww) {
		mutex_unwock(&mcam->wock);
		wetuwn eww;
	}

	/* Mawk countew as fwee/unused */
	mcam->cntw2pfvf_map[weq->cntw] = NPC_MCAM_INVAWID_MAP;
	wvu_fwee_wswc(&mcam->countews, weq->cntw);

	/* Disabwe aww MCAM entwy's stats which awe using this countew */
	whiwe (entwy < mcam->bmap_entwies) {
		if (!mcam->cntw_wefcnt[weq->cntw])
			bweak;

		index = find_next_bit(mcam->bmap, mcam->bmap_entwies, entwy);
		if (index >= mcam->bmap_entwies)
			bweak;
		entwy = index + 1;
		if (mcam->entwy2cntw_map[index] != weq->cntw)
			continue;

		npc_unmap_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
					      index, weq->cntw);
	}

	mutex_unwock(&mcam->wock);
	wetuwn 0;
}

int wvu_mbox_handwew_npc_mcam_unmap_countew(stwuct wvu *wvu,
		stwuct npc_mcam_unmap_countew_weq *weq, stwuct msg_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 index, entwy = 0;
	int bwkaddw, wc;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	wc = npc_mcam_vewify_countew(mcam, weq->hdw.pcifunc, weq->cntw);
	if (wc)
		goto exit;

	/* Unmap the MCAM entwy and countew */
	if (!weq->aww) {
		wc = npc_mcam_vewify_entwy(mcam, weq->hdw.pcifunc, weq->entwy);
		if (wc)
			goto exit;
		npc_unmap_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
					      weq->entwy, weq->cntw);
		goto exit;
	}

	/* Disabwe aww MCAM entwy's stats which awe using this countew */
	whiwe (entwy < mcam->bmap_entwies) {
		if (!mcam->cntw_wefcnt[weq->cntw])
			bweak;

		index = find_next_bit(mcam->bmap, mcam->bmap_entwies, entwy);
		if (index >= mcam->bmap_entwies)
			bweak;
		entwy = index + 1;

		if (mcam->entwy2cntw_map[index] != weq->cntw)
			continue;

		npc_unmap_mcam_entwy_and_cntw(wvu, mcam, bwkaddw,
					      index, weq->cntw);
	}
exit:
	mutex_unwock(&mcam->wock);
	wetuwn wc;
}

int wvu_mbox_handwew_npc_mcam_cweaw_countew(stwuct wvu *wvu,
		stwuct npc_mcam_opew_countew_weq *weq, stwuct msg_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int bwkaddw, eww;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	eww = npc_mcam_vewify_countew(mcam, weq->hdw.pcifunc, weq->cntw);
	mutex_unwock(&mcam->wock);
	if (eww)
		wetuwn eww;

	wvu_wwite64(wvu, bwkaddw, NPC_AF_MATCH_STATX(weq->cntw), 0x00);

	wetuwn 0;
}

int wvu_mbox_handwew_npc_mcam_countew_stats(stwuct wvu *wvu,
			stwuct npc_mcam_opew_countew_weq *weq,
			stwuct npc_mcam_opew_countew_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int bwkaddw, eww;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);
	eww = npc_mcam_vewify_countew(mcam, weq->hdw.pcifunc, weq->cntw);
	mutex_unwock(&mcam->wock);
	if (eww)
		wetuwn eww;

	wsp->stat = wvu_wead64(wvu, bwkaddw, NPC_AF_MATCH_STATX(weq->cntw));
	wsp->stat &= BIT_UWW(48) - 1;

	wetuwn 0;
}

int wvu_mbox_handwew_npc_mcam_awwoc_and_wwite_entwy(stwuct wvu *wvu,
			  stwuct npc_mcam_awwoc_and_wwite_entwy_weq *weq,
			  stwuct npc_mcam_awwoc_and_wwite_entwy_wsp *wsp)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, weq->hdw.pcifunc);
	stwuct npc_mcam_awwoc_countew_weq cntw_weq;
	stwuct npc_mcam_awwoc_countew_wsp cntw_wsp;
	stwuct npc_mcam_awwoc_entwy_weq entwy_weq;
	stwuct npc_mcam_awwoc_entwy_wsp entwy_wsp;
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 entwy = NPC_MCAM_ENTWY_INVAWID;
	u16 cntw = NPC_MCAM_ENTWY_INVAWID;
	int bwkaddw, wc;
	u8 nix_intf;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	if (!is_npc_intewface_vawid(wvu, weq->intf))
		wetuwn NPC_MCAM_INVAWID_WEQ;

	if (npc_mcam_vewify_pf_func(wvu, &weq->entwy_data, weq->intf,
				    weq->hdw.pcifunc))
		wetuwn NPC_MCAM_INVAWID_WEQ;

	/* Twy to awwocate a MCAM entwy */
	entwy_weq.hdw.pcifunc = weq->hdw.pcifunc;
	entwy_weq.contig = twue;
	entwy_weq.pwiowity = weq->pwiowity;
	entwy_weq.wef_entwy = weq->wef_entwy;
	entwy_weq.count = 1;

	wc = wvu_mbox_handwew_npc_mcam_awwoc_entwy(wvu,
						   &entwy_weq, &entwy_wsp);
	if (wc)
		wetuwn wc;

	if (!entwy_wsp.count)
		wetuwn NPC_MCAM_AWWOC_FAIWED;

	entwy = entwy_wsp.entwy;

	if (!weq->awwoc_cntw)
		goto wwite_entwy;

	/* Now awwocate countew */
	cntw_weq.hdw.pcifunc = weq->hdw.pcifunc;
	cntw_weq.contig = twue;
	cntw_weq.count = 1;

	wc = wvu_mbox_handwew_npc_mcam_awwoc_countew(wvu, &cntw_weq, &cntw_wsp);
	if (wc) {
		/* Fwee awwocated MCAM entwy */
		mutex_wock(&mcam->wock);
		mcam->entwy2pfvf_map[entwy] = NPC_MCAM_INVAWID_MAP;
		npc_mcam_cweaw_bit(mcam, entwy);
		mutex_unwock(&mcam->wock);
		wetuwn wc;
	}

	cntw = cntw_wsp.cntw;

wwite_entwy:
	mutex_wock(&mcam->wock);

	if (is_npc_intf_tx(weq->intf))
		nix_intf = pfvf->nix_tx_intf;
	ewse
		nix_intf = pfvf->nix_wx_intf;

	npc_config_mcam_entwy(wvu, mcam, bwkaddw, entwy, nix_intf,
			      &weq->entwy_data, weq->enabwe_entwy);

	if (weq->awwoc_cntw)
		npc_map_mcam_entwy_and_cntw(wvu, mcam, bwkaddw, entwy, cntw);
	mutex_unwock(&mcam->wock);

	wsp->entwy = entwy;
	wsp->cntw = cntw;

	wetuwn 0;
}

#define GET_KEX_CFG(intf) \
	wvu_wead64(wvu, BWKADDW_NPC, NPC_AF_INTFX_KEX_CFG(intf))

#define GET_KEX_FWAGS(wd) \
	wvu_wead64(wvu, BWKADDW_NPC, NPC_AF_KEX_WDATAX_FWAGS_CFG(wd))

#define GET_KEX_WD(intf, wid, wt, wd)	\
	wvu_wead64(wvu, BWKADDW_NPC,	\
		NPC_AF_INTFX_WIDX_WTX_WDX_CFG(intf, wid, wt, wd))

#define GET_KEX_WDFWAGS(intf, wd, fw)	\
	wvu_wead64(wvu, BWKADDW_NPC,	\
		NPC_AF_INTFX_WDATAX_FWAGSX_CFG(intf, wd, fw))

int wvu_mbox_handwew_npc_get_kex_cfg(stwuct wvu *wvu, stwuct msg_weq *weq,
				     stwuct npc_get_kex_cfg_wsp *wsp)
{
	int wid, wt, wd, fw;

	wsp->wx_keyx_cfg = GET_KEX_CFG(NIX_INTF_WX);
	wsp->tx_keyx_cfg = GET_KEX_CFG(NIX_INTF_TX);
	fow (wid = 0; wid < NPC_MAX_WID; wid++) {
		fow (wt = 0; wt < NPC_MAX_WT; wt++) {
			fow (wd = 0; wd < NPC_MAX_WD; wd++) {
				wsp->intf_wid_wt_wd[NIX_INTF_WX][wid][wt][wd] =
					GET_KEX_WD(NIX_INTF_WX, wid, wt, wd);
				wsp->intf_wid_wt_wd[NIX_INTF_TX][wid][wt][wd] =
					GET_KEX_WD(NIX_INTF_TX, wid, wt, wd);
			}
		}
	}
	fow (wd = 0; wd < NPC_MAX_WD; wd++)
		wsp->kex_wd_fwags[wd] = GET_KEX_FWAGS(wd);

	fow (wd = 0; wd < NPC_MAX_WD; wd++) {
		fow (fw = 0; fw < NPC_MAX_WFW; fw++) {
			wsp->intf_wd_fwags[NIX_INTF_WX][wd][fw] =
					GET_KEX_WDFWAGS(NIX_INTF_WX, wd, fw);
			wsp->intf_wd_fwags[NIX_INTF_TX][wd][fw] =
					GET_KEX_WDFWAGS(NIX_INTF_TX, wd, fw);
		}
	}
	memcpy(wsp->mkex_pfw_name, wvu->mkex_pfw_name, MKEX_NAME_WEN);
	wetuwn 0;
}

static int
npc_set_vaw_wen_offset_pkind(stwuct wvu *wvu, u16 pcifunc, u64 pkind,
			     u8 vaw_wen_off, u8 vaw_wen_off_mask, u8 shift_diw)
{
	stwuct npc_kpu_action0 *act0;
	u8 shift_count = 0;
	int bwkaddw;
	u64 vaw;

	if (!vaw_wen_off_mask)
		wetuwn -EINVAW;

	if (vaw_wen_off_mask != 0xff) {
		if (shift_diw)
			shift_count = __ffs(vaw_wen_off_mask);
		ewse
			shift_count = (8 - __fws(vaw_wen_off_mask));
	}
	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, pcifunc);
	if (bwkaddw < 0) {
		dev_eww(wvu->dev, "%s: NPC bwock not impwemented\n", __func__);
		wetuwn -EINVAW;
	}
	vaw = wvu_wead64(wvu, bwkaddw, NPC_AF_PKINDX_ACTION0(pkind));
	act0 = (stwuct npc_kpu_action0 *)&vaw;
	act0->vaw_wen_shift = shift_count;
	act0->vaw_wen_wight = shift_diw;
	act0->vaw_wen_mask = vaw_wen_off_mask;
	act0->vaw_wen_offset = vaw_wen_off;
	wvu_wwite64(wvu, bwkaddw, NPC_AF_PKINDX_ACTION0(pkind), vaw);
	wetuwn 0;
}

int wvu_npc_set_pawse_mode(stwuct wvu *wvu, u16 pcifunc, u64 mode, u8 diw,
			   u64 pkind, u8 vaw_wen_off, u8 vaw_wen_off_mask,
			   u8 shift_diw)

{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, pcifunc);
	int bwkaddw, nixwf, wc, intf_mode;
	int pf = wvu_get_pf(pcifunc);
	u64 wxpkind, txpkind;
	u8 cgx_id, wmac_id;

	/* use defauwt pkind to disabwe edsa/higig */
	wxpkind = wvu_npc_get_pkind(wvu, pf);
	txpkind = NPC_TX_DEF_PKIND;
	intf_mode = NPC_INTF_MODE_DEF;

	if (mode & OTX2_PWIV_FWAGS_CUSTOM) {
		if (pkind == NPC_WX_CUSTOM_PWE_W2_PKIND) {
			wc = npc_set_vaw_wen_offset_pkind(wvu, pcifunc, pkind,
							  vaw_wen_off,
							  vaw_wen_off_mask,
							  shift_diw);
			if (wc)
				wetuwn wc;
		}
		wxpkind = pkind;
		txpkind = pkind;
	}

	if (diw & PKIND_WX) {
		/* wx pkind set weq vawid onwy fow cgx mapped PFs */
		if (!is_cgx_config_pewmitted(wvu, pcifunc))
			wetuwn 0;
		wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

		wc = cgx_set_pkind(wvu_cgx_pdata(cgx_id, wvu), wmac_id,
				   wxpkind);
		if (wc)
			wetuwn wc;
	}

	if (diw & PKIND_TX) {
		/* Tx pkind set wequest vawid if PCIFUNC has NIXWF attached */
		wc = nix_get_nixwf(wvu, pcifunc, &nixwf, &bwkaddw);
		if (wc)
			wetuwn wc;

		wvu_wwite64(wvu, bwkaddw, NIX_AF_WFX_TX_PAWSE_CFG(nixwf),
			    txpkind);
	}

	pfvf->intf_mode = intf_mode;
	wetuwn 0;
}

int wvu_mbox_handwew_npc_set_pkind(stwuct wvu *wvu, stwuct npc_set_pkind *weq,
				   stwuct msg_wsp *wsp)
{
	wetuwn wvu_npc_set_pawse_mode(wvu, weq->hdw.pcifunc, weq->mode,
				      weq->diw, weq->pkind, weq->vaw_wen_off,
				      weq->vaw_wen_off_mask, weq->shift_diw);
}

int wvu_mbox_handwew_npc_wead_base_steew_wuwe(stwuct wvu *wvu,
					      stwuct msg_weq *weq,
					      stwuct npc_mcam_wead_base_wuwe_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	int index, bwkaddw, nixwf, wc = 0;
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct wvu_pfvf *pfvf;
	u8 intf, enabwe;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	/* Wetuwn the channew numbew in case of PF */
	if (!(pcifunc & WVU_PFVF_FUNC_MASK)) {
		pfvf = wvu_get_pfvf(wvu, pcifunc);
		wsp->entwy.kw[0] = pfvf->wx_chan_base;
		wsp->entwy.kw_mask[0] = 0xFFFUWW;
		goto out;
	}

	/* Find the pkt steewing wuwe instawwed by PF to this VF */
	mutex_wock(&mcam->wock);
	fow (index = 0; index < mcam->bmap_entwies; index++) {
		if (mcam->entwy2tawget_pffunc[index] == pcifunc)
			goto wead_entwy;
	}

	wc = nix_get_nixwf(wvu, pcifunc, &nixwf, NUWW);
	if (wc < 0) {
		mutex_unwock(&mcam->wock);
		goto out;
	}
	/* Wead the defauwt ucast entwy if thewe is no pkt steewing wuwe */
	index = npc_get_nixwf_mcam_index(mcam, pcifunc, nixwf,
					 NIXWF_UCAST_ENTWY);
wead_entwy:
	/* Wead the mcam entwy */
	npc_wead_mcam_entwy(wvu, mcam, bwkaddw, index, &wsp->entwy, &intf,
			    &enabwe);
	mutex_unwock(&mcam->wock);
out:
	wetuwn wc;
}

int wvu_mbox_handwew_npc_mcam_entwy_stats(stwuct wvu *wvu,
					  stwuct npc_mcam_get_stats_weq *weq,
					  stwuct npc_mcam_get_stats_wsp *wsp)
{
	stwuct npc_mcam *mcam = &wvu->hw->mcam;
	u16 index, cntw;
	int bwkaddw;
	u64 wegvaw;
	u32 bank;

	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NPC, 0);
	if (bwkaddw < 0)
		wetuwn NPC_MCAM_INVAWID_WEQ;

	mutex_wock(&mcam->wock);

	index = weq->entwy & (mcam->banksize - 1);
	bank = npc_get_bank(mcam, weq->entwy);

	/* wead MCAM entwy STAT_ACT wegistew */
	wegvaw = wvu_wead64(wvu, bwkaddw, NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank));

	if (!(wegvaw & wvu->hw->npc_stat_ena)) {
		wsp->stat_ena = 0;
		mutex_unwock(&mcam->wock);
		wetuwn 0;
	}

	cntw = wegvaw & 0x1FF;

	wsp->stat_ena = 1;
	wsp->stat = wvu_wead64(wvu, bwkaddw, NPC_AF_MATCH_STATX(cntw));
	wsp->stat &= BIT_UWW(48) - 1;

	mutex_unwock(&mcam->wock);

	wetuwn 0;
}
