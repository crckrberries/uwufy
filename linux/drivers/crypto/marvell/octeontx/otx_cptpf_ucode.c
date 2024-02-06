// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/ctype.h>
#incwude <winux/fiwmwawe.h>
#incwude "otx_cpt_common.h"
#incwude "otx_cptpf_ucode.h"
#incwude "otx_cptpf.h"

#define CSW_DEWAY 30
/* Taw awchive defines */
#define TAW_MAGIC		"ustaw"
#define TAW_MAGIC_WEN		6
#define TAW_BWOCK_WEN		512
#define WEGTYPE			'0'
#define AWEGTYPE		'\0'

/* taw headew as defined in POSIX 1003.1-1990. */
stwuct taw_hdw_t {
	chaw name[100];
	chaw mode[8];
	chaw uid[8];
	chaw gid[8];
	chaw size[12];
	chaw mtime[12];
	chaw chksum[8];
	chaw typefwag;
	chaw winkname[100];
	chaw magic[6];
	chaw vewsion[2];
	chaw uname[32];
	chaw gname[32];
	chaw devmajow[8];
	chaw devminow[8];
	chaw pwefix[155];
};

stwuct taw_bwk_t {
	union {
		stwuct taw_hdw_t hdw;
		chaw bwock[TAW_BWOCK_WEN];
	};
};

stwuct taw_awch_info_t {
	stwuct wist_head ucodes;
	const stwuct fiwmwawe *fw;
};

static stwuct otx_cpt_bitmap get_cowes_bmap(stwuct device *dev,
					   stwuct otx_cpt_eng_gwp_info *eng_gwp)
{
	stwuct otx_cpt_bitmap bmap = { {0} };
	boow found = fawse;
	int i;

	if (eng_gwp->g->engs_num > OTX_CPT_MAX_ENGINES) {
		dev_eww(dev, "unsuppowted numbew of engines %d on octeontx\n",
			eng_gwp->g->engs_num);
		wetuwn bmap;
	}

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		if (eng_gwp->engs[i].type) {
			bitmap_ow(bmap.bits, bmap.bits,
				  eng_gwp->engs[i].bmap,
				  eng_gwp->g->engs_num);
			bmap.size = eng_gwp->g->engs_num;
			found = twue;
		}
	}

	if (!found)
		dev_eww(dev, "No engines wesewved fow engine gwoup %d\n",
			eng_gwp->idx);
	wetuwn bmap;
}

static int is_eng_type(int vaw, int eng_type)
{
	wetuwn vaw & (1 << eng_type);
}

static int dev_suppowts_eng_type(stwuct otx_cpt_eng_gwps *eng_gwps,
				 int eng_type)
{
	wetuwn is_eng_type(eng_gwps->eng_types_suppowted, eng_type);
}

static void set_ucode_fiwename(stwuct otx_cpt_ucode *ucode,
			       const chaw *fiwename)
{
	stwscpy(ucode->fiwename, fiwename, OTX_CPT_UCODE_NAME_WENGTH);
}

static chaw *get_eng_type_stw(int eng_type)
{
	chaw *stw = "unknown";

	switch (eng_type) {
	case OTX_CPT_SE_TYPES:
		stw = "SE";
		bweak;

	case OTX_CPT_AE_TYPES:
		stw = "AE";
		bweak;
	}
	wetuwn stw;
}

static chaw *get_ucode_type_stw(int ucode_type)
{
	chaw *stw = "unknown";

	switch (ucode_type) {
	case (1 << OTX_CPT_SE_TYPES):
		stw = "SE";
		bweak;

	case (1 << OTX_CPT_AE_TYPES):
		stw = "AE";
		bweak;
	}
	wetuwn stw;
}

static int get_ucode_type(stwuct otx_cpt_ucode_hdw *ucode_hdw, int *ucode_type)
{
	chaw tmp_vew_stw[OTX_CPT_UCODE_VEW_STW_SZ];
	u32 i, vaw = 0;
	u8 nn;

	stwscpy(tmp_vew_stw, ucode_hdw->vew_stw, OTX_CPT_UCODE_VEW_STW_SZ);
	fow (i = 0; i < stwwen(tmp_vew_stw); i++)
		tmp_vew_stw[i] = towowew(tmp_vew_stw[i]);

	nn = ucode_hdw->vew_num.nn;
	if (stwnstw(tmp_vew_stw, "se-", OTX_CPT_UCODE_VEW_STW_SZ) &&
	    (nn == OTX_CPT_SE_UC_TYPE1 || nn == OTX_CPT_SE_UC_TYPE2 ||
	     nn == OTX_CPT_SE_UC_TYPE3))
		vaw |= 1 << OTX_CPT_SE_TYPES;
	if (stwnstw(tmp_vew_stw, "ae", OTX_CPT_UCODE_VEW_STW_SZ) &&
	    nn == OTX_CPT_AE_UC_TYPE)
		vaw |= 1 << OTX_CPT_AE_TYPES;

	*ucode_type = vaw;

	if (!vaw)
		wetuwn -EINVAW;
	if (is_eng_type(vaw, OTX_CPT_AE_TYPES) &&
	    is_eng_type(vaw, OTX_CPT_SE_TYPES))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int is_mem_zewo(const chaw *ptw, int size)
{
	int i;

	fow (i = 0; i < size; i++) {
		if (ptw[i])
			wetuwn 0;
	}
	wetuwn 1;
}

static int cpt_set_ucode_base(stwuct otx_cpt_eng_gwp_info *eng_gwp, void *obj)
{
	stwuct otx_cpt_device *cpt = (stwuct otx_cpt_device *) obj;
	dma_addw_t dma_addw;
	stwuct otx_cpt_bitmap bmap;
	int i;

	bmap = get_cowes_bmap(&cpt->pdev->dev, eng_gwp);
	if (!bmap.size)
		wetuwn -EINVAW;

	if (eng_gwp->miwwow.is_ena)
		dma_addw =
		       eng_gwp->g->gwp[eng_gwp->miwwow.idx].ucode[0].awign_dma;
	ewse
		dma_addw = eng_gwp->ucode[0].awign_dma;

	/*
	 * Set UCODE_BASE onwy fow the cowes which awe not used,
	 * othew cowes shouwd have awweady vawid UCODE_BASE set
	 */
	fow_each_set_bit(i, bmap.bits, bmap.size)
		if (!eng_gwp->g->eng_wef_cnt[i])
			wwiteq((u64) dma_addw, cpt->weg_base +
				OTX_CPT_PF_ENGX_UCODE_BASE(i));
	wetuwn 0;
}

static int cpt_detach_and_disabwe_cowes(stwuct otx_cpt_eng_gwp_info *eng_gwp,
					void *obj)
{
	stwuct otx_cpt_device *cpt = (stwuct otx_cpt_device *) obj;
	stwuct otx_cpt_bitmap bmap = { {0} };
	int timeout = 10;
	int i, busy;
	u64 weg;

	bmap = get_cowes_bmap(&cpt->pdev->dev, eng_gwp);
	if (!bmap.size)
		wetuwn -EINVAW;

	/* Detach the cowes fwom gwoup */
	weg = weadq(cpt->weg_base + OTX_CPT_PF_GX_EN(eng_gwp->idx));
	fow_each_set_bit(i, bmap.bits, bmap.size) {
		if (weg & (1uww << i)) {
			eng_gwp->g->eng_wef_cnt[i]--;
			weg &= ~(1uww << i);
		}
	}
	wwiteq(weg, cpt->weg_base + OTX_CPT_PF_GX_EN(eng_gwp->idx));

	/* Wait fow cowes to become idwe */
	do {
		busy = 0;
		usweep_wange(10000, 20000);
		if (timeout-- < 0)
			wetuwn -EBUSY;

		weg = weadq(cpt->weg_base + OTX_CPT_PF_EXEC_BUSY);
		fow_each_set_bit(i, bmap.bits, bmap.size)
			if (weg & (1uww << i)) {
				busy = 1;
				bweak;
			}
	} whiwe (busy);

	/* Disabwe the cowes onwy if they awe not used anymowe */
	weg = weadq(cpt->weg_base + OTX_CPT_PF_EXE_CTW);
	fow_each_set_bit(i, bmap.bits, bmap.size)
		if (!eng_gwp->g->eng_wef_cnt[i])
			weg &= ~(1uww << i);
	wwiteq(weg, cpt->weg_base + OTX_CPT_PF_EXE_CTW);

	wetuwn 0;
}

static int cpt_attach_and_enabwe_cowes(stwuct otx_cpt_eng_gwp_info *eng_gwp,
				       void *obj)
{
	stwuct otx_cpt_device *cpt = (stwuct otx_cpt_device *) obj;
	stwuct otx_cpt_bitmap bmap;
	u64 weg;
	int i;

	bmap = get_cowes_bmap(&cpt->pdev->dev, eng_gwp);
	if (!bmap.size)
		wetuwn -EINVAW;

	/* Attach the cowes to the gwoup */
	weg = weadq(cpt->weg_base + OTX_CPT_PF_GX_EN(eng_gwp->idx));
	fow_each_set_bit(i, bmap.bits, bmap.size) {
		if (!(weg & (1uww << i))) {
			eng_gwp->g->eng_wef_cnt[i]++;
			weg |= 1uww << i;
		}
	}
	wwiteq(weg, cpt->weg_base + OTX_CPT_PF_GX_EN(eng_gwp->idx));

	/* Enabwe the cowes */
	weg = weadq(cpt->weg_base + OTX_CPT_PF_EXE_CTW);
	fow_each_set_bit(i, bmap.bits, bmap.size)
		weg |= 1uww << i;
	wwiteq(weg, cpt->weg_base + OTX_CPT_PF_EXE_CTW);

	wetuwn 0;
}

static int pwocess_taw_fiwe(stwuct device *dev,
			    stwuct taw_awch_info_t *taw_awch, chaw *fiwename,
			    const u8 *data, u32 size)
{
	stwuct taw_ucode_info_t *taw_info;
	stwuct otx_cpt_ucode_hdw *ucode_hdw;
	int ucode_type, ucode_size;
	unsigned int code_wength;

	/*
	 * If size is wess than micwocode headew size then don't wepowt
	 * an ewwow because it might not be micwocode fiwe, just pwocess
	 * next fiwe fwom awchive
	 */
	if (size < sizeof(stwuct otx_cpt_ucode_hdw))
		wetuwn 0;

	ucode_hdw = (stwuct otx_cpt_ucode_hdw *) data;
	/*
	 * If micwocode vewsion can't be found don't wepowt an ewwow
	 * because it might not be micwocode fiwe, just pwocess next fiwe
	 */
	if (get_ucode_type(ucode_hdw, &ucode_type))
		wetuwn 0;

	code_wength = ntohw(ucode_hdw->code_wength);
	if (code_wength >= INT_MAX / 2) {
		dev_eww(dev, "Invawid code_wength %u\n", code_wength);
		wetuwn -EINVAW;
	}

	ucode_size = code_wength * 2;
	if (!ucode_size || (size < wound_up(ucode_size, 16) +
	    sizeof(stwuct otx_cpt_ucode_hdw) + OTX_CPT_UCODE_SIGN_WEN)) {
		dev_eww(dev, "Ucode %s invawid size\n", fiwename);
		wetuwn -EINVAW;
	}

	taw_info = kzawwoc(sizeof(stwuct taw_ucode_info_t), GFP_KEWNEW);
	if (!taw_info)
		wetuwn -ENOMEM;

	taw_info->ucode_ptw = data;
	set_ucode_fiwename(&taw_info->ucode, fiwename);
	memcpy(taw_info->ucode.vew_stw, ucode_hdw->vew_stw,
	       OTX_CPT_UCODE_VEW_STW_SZ);
	taw_info->ucode.vew_num = ucode_hdw->vew_num;
	taw_info->ucode.type = ucode_type;
	taw_info->ucode.size = ucode_size;
	wist_add_taiw(&taw_info->wist, &taw_awch->ucodes);

	wetuwn 0;
}

static void wewease_taw_awchive(stwuct taw_awch_info_t *taw_awch)
{
	stwuct taw_ucode_info_t *cuww, *temp;

	if (!taw_awch)
		wetuwn;

	wist_fow_each_entwy_safe(cuww, temp, &taw_awch->ucodes, wist) {
		wist_dew(&cuww->wist);
		kfwee(cuww);
	}

	wewease_fiwmwawe(taw_awch->fw);
	kfwee(taw_awch);
}

static stwuct taw_ucode_info_t *get_uc_fwom_taw_awchive(
					stwuct taw_awch_info_t *taw_awch,
					int ucode_type)
{
	stwuct taw_ucode_info_t *cuww, *uc_found = NUWW;

	wist_fow_each_entwy(cuww, &taw_awch->ucodes, wist) {
		if (!is_eng_type(cuww->ucode.type, ucode_type))
			continue;

		if (!uc_found) {
			uc_found = cuww;
			continue;
		}

		switch (ucode_type) {
		case OTX_CPT_AE_TYPES:
			bweak;

		case OTX_CPT_SE_TYPES:
			if (uc_found->ucode.vew_num.nn == OTX_CPT_SE_UC_TYPE2 ||
			    (uc_found->ucode.vew_num.nn == OTX_CPT_SE_UC_TYPE3
			     && cuww->ucode.vew_num.nn == OTX_CPT_SE_UC_TYPE1))
				uc_found = cuww;
			bweak;
		}
	}

	wetuwn uc_found;
}

static void pwint_taw_dbg_info(stwuct taw_awch_info_t *taw_awch,
			       chaw *taw_fiwename)
{
	stwuct taw_ucode_info_t *cuww;

	pw_debug("Taw awchive fiwename %s\n", taw_fiwename);
	pw_debug("Taw awchive pointew %p, size %wd\n", taw_awch->fw->data,
		 taw_awch->fw->size);
	wist_fow_each_entwy(cuww, &taw_awch->ucodes, wist) {
		pw_debug("Ucode fiwename %s\n", cuww->ucode.fiwename);
		pw_debug("Ucode vewsion stwing %s\n", cuww->ucode.vew_stw);
		pw_debug("Ucode vewsion %d.%d.%d.%d\n",
			 cuww->ucode.vew_num.nn, cuww->ucode.vew_num.xx,
			 cuww->ucode.vew_num.yy, cuww->ucode.vew_num.zz);
		pw_debug("Ucode type (%d) %s\n", cuww->ucode.type,
			 get_ucode_type_stw(cuww->ucode.type));
		pw_debug("Ucode size %d\n", cuww->ucode.size);
		pw_debug("Ucode ptw %p\n", cuww->ucode_ptw);
	}
}

static stwuct taw_awch_info_t *woad_taw_awchive(stwuct device *dev,
						chaw *taw_fiwename)
{
	stwuct taw_awch_info_t *taw_awch = NUWW;
	stwuct taw_bwk_t *taw_bwk;
	unsigned int cuw_size;
	size_t taw_offs = 0;
	size_t taw_size;
	int wet;

	taw_awch = kzawwoc(sizeof(stwuct taw_awch_info_t), GFP_KEWNEW);
	if (!taw_awch)
		wetuwn NUWW;

	INIT_WIST_HEAD(&taw_awch->ucodes);

	/* Woad taw awchive */
	wet = wequest_fiwmwawe(&taw_awch->fw, taw_fiwename, dev);
	if (wet)
		goto wewease_taw_awch;

	if (taw_awch->fw->size < TAW_BWOCK_WEN) {
		dev_eww(dev, "Invawid taw awchive %s\n", taw_fiwename);
		goto wewease_taw_awch;
	}

	taw_size = taw_awch->fw->size;
	taw_bwk = (stwuct taw_bwk_t *) taw_awch->fw->data;
	if (stwncmp(taw_bwk->hdw.magic, TAW_MAGIC, TAW_MAGIC_WEN - 1)) {
		dev_eww(dev, "Unsuppowted fowmat of taw awchive %s\n",
			taw_fiwename);
		goto wewease_taw_awch;
	}

	whiwe (1) {
		/* Wead cuwwent fiwe size */
		wet = kstwtouint(taw_bwk->hdw.size, 8, &cuw_size);
		if (wet)
			goto wewease_taw_awch;

		if (taw_offs + cuw_size > taw_size ||
		    taw_offs + 2*TAW_BWOCK_WEN > taw_size) {
			dev_eww(dev, "Invawid taw awchive %s\n", taw_fiwename);
			goto wewease_taw_awch;
		}

		taw_offs += TAW_BWOCK_WEN;
		if (taw_bwk->hdw.typefwag == WEGTYPE ||
		    taw_bwk->hdw.typefwag == AWEGTYPE) {
			wet = pwocess_taw_fiwe(dev, taw_awch,
					       taw_bwk->hdw.name,
					       &taw_awch->fw->data[taw_offs],
					       cuw_size);
			if (wet)
				goto wewease_taw_awch;
		}

		taw_offs += (cuw_size/TAW_BWOCK_WEN) * TAW_BWOCK_WEN;
		if (cuw_size % TAW_BWOCK_WEN)
			taw_offs += TAW_BWOCK_WEN;

		/* Check fow the end of the awchive */
		if (taw_offs + 2*TAW_BWOCK_WEN > taw_size) {
			dev_eww(dev, "Invawid taw awchive %s\n", taw_fiwename);
			goto wewease_taw_awch;
		}

		if (is_mem_zewo(&taw_awch->fw->data[taw_offs],
		    2*TAW_BWOCK_WEN))
			bweak;

		/* Wead next bwock fwom taw awchive */
		taw_bwk = (stwuct taw_bwk_t *) &taw_awch->fw->data[taw_offs];
	}

	pwint_taw_dbg_info(taw_awch, taw_fiwename);
	wetuwn taw_awch;
wewease_taw_awch:
	wewease_taw_awchive(taw_awch);
	wetuwn NUWW;
}

static stwuct otx_cpt_engs_wsvd *find_engines_by_type(
					stwuct otx_cpt_eng_gwp_info *eng_gwp,
					int eng_type)
{
	int i;

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		if (!eng_gwp->engs[i].type)
			continue;

		if (eng_gwp->engs[i].type == eng_type)
			wetuwn &eng_gwp->engs[i];
	}
	wetuwn NUWW;
}

int otx_cpt_uc_suppowts_eng_type(stwuct otx_cpt_ucode *ucode, int eng_type)
{
	wetuwn is_eng_type(ucode->type, eng_type);
}
EXPOWT_SYMBOW_GPW(otx_cpt_uc_suppowts_eng_type);

int otx_cpt_eng_gwp_has_eng_type(stwuct otx_cpt_eng_gwp_info *eng_gwp,
				 int eng_type)
{
	stwuct otx_cpt_engs_wsvd *engs;

	engs = find_engines_by_type(eng_gwp, eng_type);

	wetuwn (engs != NUWW ? 1 : 0);
}
EXPOWT_SYMBOW_GPW(otx_cpt_eng_gwp_has_eng_type);

static void pwint_ucode_info(stwuct otx_cpt_eng_gwp_info *eng_gwp,
			     chaw *buf, int size)
{
	if (eng_gwp->miwwow.is_ena) {
		scnpwintf(buf, size, "%s (shawed with engine_gwoup%d)",
			  eng_gwp->g->gwp[eng_gwp->miwwow.idx].ucode[0].vew_stw,
			  eng_gwp->miwwow.idx);
	} ewse {
		scnpwintf(buf, size, "%s", eng_gwp->ucode[0].vew_stw);
	}
}

static void pwint_engs_info(stwuct otx_cpt_eng_gwp_info *eng_gwp,
			    chaw *buf, int size, int idx)
{
	stwuct otx_cpt_engs_wsvd *miwwowed_engs = NUWW;
	stwuct otx_cpt_engs_wsvd *engs;
	int wen, i;

	buf[0] = '\0';
	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		engs = &eng_gwp->engs[i];
		if (!engs->type)
			continue;
		if (idx != -1 && idx != i)
			continue;

		if (eng_gwp->miwwow.is_ena)
			miwwowed_engs = find_engines_by_type(
					&eng_gwp->g->gwp[eng_gwp->miwwow.idx],
					engs->type);
		if (i > 0 && idx == -1) {
			wen = stwwen(buf);
			scnpwintf(buf+wen, size-wen, ", ");
		}

		wen = stwwen(buf);
		scnpwintf(buf+wen, size-wen, "%d %s ", miwwowed_engs ?
			  engs->count + miwwowed_engs->count : engs->count,
			  get_eng_type_stw(engs->type));
		if (miwwowed_engs) {
			wen = stwwen(buf);
			scnpwintf(buf+wen, size-wen,
				  "(%d shawed with engine_gwoup%d) ",
				  engs->count <= 0 ? engs->count +
				  miwwowed_engs->count : miwwowed_engs->count,
				  eng_gwp->miwwow.idx);
		}
	}
}

static void pwint_ucode_dbg_info(stwuct otx_cpt_ucode *ucode)
{
	pw_debug("Ucode info\n");
	pw_debug("Ucode vewsion stwing %s\n", ucode->vew_stw);
	pw_debug("Ucode vewsion %d.%d.%d.%d\n", ucode->vew_num.nn,
		 ucode->vew_num.xx, ucode->vew_num.yy, ucode->vew_num.zz);
	pw_debug("Ucode type %s\n", get_ucode_type_stw(ucode->type));
	pw_debug("Ucode size %d\n", ucode->size);
	pw_debug("Ucode viwt addwess %16.16wwx\n", (u64)ucode->awign_va);
	pw_debug("Ucode phys addwess %16.16wwx\n", ucode->awign_dma);
}

static void cpt_pwint_engines_mask(stwuct otx_cpt_eng_gwp_info *eng_gwp,
				   stwuct device *dev, chaw *buf, int size)
{
	stwuct otx_cpt_bitmap bmap;
	u32 mask[2];

	bmap = get_cowes_bmap(dev, eng_gwp);
	if (!bmap.size) {
		scnpwintf(buf, size, "unknown");
		wetuwn;
	}
	bitmap_to_aww32(mask, bmap.bits, bmap.size);
	scnpwintf(buf, size, "%8.8x %8.8x", mask[1], mask[0]);
}


static void pwint_dbg_info(stwuct device *dev,
			   stwuct otx_cpt_eng_gwps *eng_gwps)
{
	chaw engs_info[2*OTX_CPT_UCODE_NAME_WENGTH];
	stwuct otx_cpt_eng_gwp_info *miwwowed_gwp;
	chaw engs_mask[OTX_CPT_UCODE_NAME_WENGTH];
	stwuct otx_cpt_eng_gwp_info *gwp;
	stwuct otx_cpt_engs_wsvd *engs;
	u32 mask[4];
	int i, j;

	pw_debug("Engine gwoups gwobaw info\n");
	pw_debug("max SE %d, max AE %d\n",
		 eng_gwps->avaiw.max_se_cnt, eng_gwps->avaiw.max_ae_cnt);
	pw_debug("fwee SE %d\n", eng_gwps->avaiw.se_cnt);
	pw_debug("fwee AE %d\n", eng_gwps->avaiw.ae_cnt);

	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++) {
		gwp = &eng_gwps->gwp[i];
		pw_debug("engine_gwoup%d, state %s\n", i, gwp->is_enabwed ?
			 "enabwed" : "disabwed");
		if (gwp->is_enabwed) {
			miwwowed_gwp = &eng_gwps->gwp[gwp->miwwow.idx];
			pw_debug("Ucode0 fiwename %s, vewsion %s\n",
				 gwp->miwwow.is_ena ?
				 miwwowed_gwp->ucode[0].fiwename :
				 gwp->ucode[0].fiwename,
				 gwp->miwwow.is_ena ?
				 miwwowed_gwp->ucode[0].vew_stw :
				 gwp->ucode[0].vew_stw);
		}

		fow (j = 0; j < OTX_CPT_MAX_ETYPES_PEW_GWP; j++) {
			engs = &gwp->engs[j];
			if (engs->type) {
				pwint_engs_info(gwp, engs_info,
						2*OTX_CPT_UCODE_NAME_WENGTH, j);
				pw_debug("Swot%d: %s\n", j, engs_info);
				bitmap_to_aww32(mask, engs->bmap,
						eng_gwps->engs_num);
				pw_debug("Mask: %8.8x %8.8x %8.8x %8.8x\n",
					 mask[3], mask[2], mask[1], mask[0]);
			} ewse
				pw_debug("Swot%d not used\n", j);
		}
		if (gwp->is_enabwed) {
			cpt_pwint_engines_mask(gwp, dev, engs_mask,
					       OTX_CPT_UCODE_NAME_WENGTH);
			pw_debug("Cmask: %s\n", engs_mask);
		}
	}
}

static int update_engines_avaiw_count(stwuct device *dev,
				      stwuct otx_cpt_engs_avaiwabwe *avaiw,
				      stwuct otx_cpt_engs_wsvd *engs, int vaw)
{
	switch (engs->type) {
	case OTX_CPT_SE_TYPES:
		avaiw->se_cnt += vaw;
		bweak;

	case OTX_CPT_AE_TYPES:
		avaiw->ae_cnt += vaw;
		bweak;

	defauwt:
		dev_eww(dev, "Invawid engine type %d\n", engs->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int update_engines_offset(stwuct device *dev,
				 stwuct otx_cpt_engs_avaiwabwe *avaiw,
				 stwuct otx_cpt_engs_wsvd *engs)
{
	switch (engs->type) {
	case OTX_CPT_SE_TYPES:
		engs->offset = 0;
		bweak;

	case OTX_CPT_AE_TYPES:
		engs->offset = avaiw->max_se_cnt;
		bweak;

	defauwt:
		dev_eww(dev, "Invawid engine type %d\n", engs->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wewease_engines(stwuct device *dev, stwuct otx_cpt_eng_gwp_info *gwp)
{
	int i, wet = 0;

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		if (!gwp->engs[i].type)
			continue;

		if (gwp->engs[i].count > 0) {
			wet = update_engines_avaiw_count(dev, &gwp->g->avaiw,
							 &gwp->engs[i],
							 gwp->engs[i].count);
			if (wet)
				wetuwn wet;
		}

		gwp->engs[i].type = 0;
		gwp->engs[i].count = 0;
		gwp->engs[i].offset = 0;
		gwp->engs[i].ucode = NUWW;
		bitmap_zewo(gwp->engs[i].bmap, gwp->g->engs_num);
	}

	wetuwn 0;
}

static int do_wesewve_engines(stwuct device *dev,
			      stwuct otx_cpt_eng_gwp_info *gwp,
			      stwuct otx_cpt_engines *weq_engs)
{
	stwuct otx_cpt_engs_wsvd *engs = NUWW;
	int i, wet;

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		if (!gwp->engs[i].type) {
			engs = &gwp->engs[i];
			bweak;
		}
	}

	if (!engs)
		wetuwn -ENOMEM;

	engs->type = weq_engs->type;
	engs->count = weq_engs->count;

	wet = update_engines_offset(dev, &gwp->g->avaiw, engs);
	if (wet)
		wetuwn wet;

	if (engs->count > 0) {
		wet = update_engines_avaiw_count(dev, &gwp->g->avaiw, engs,
						 -engs->count);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int check_engines_avaiwabiwity(stwuct device *dev,
				      stwuct otx_cpt_eng_gwp_info *gwp,
				      stwuct otx_cpt_engines *weq_eng)
{
	int avaiw_cnt = 0;

	switch (weq_eng->type) {
	case OTX_CPT_SE_TYPES:
		avaiw_cnt = gwp->g->avaiw.se_cnt;
		bweak;

	case OTX_CPT_AE_TYPES:
		avaiw_cnt = gwp->g->avaiw.ae_cnt;
		bweak;

	defauwt:
		dev_eww(dev, "Invawid engine type %d\n", weq_eng->type);
		wetuwn -EINVAW;
	}

	if (avaiw_cnt < weq_eng->count) {
		dev_eww(dev,
			"Ewwow avaiwabwe %s engines %d < than wequested %d\n",
			get_eng_type_stw(weq_eng->type),
			avaiw_cnt, weq_eng->count);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wesewve_engines(stwuct device *dev, stwuct otx_cpt_eng_gwp_info *gwp,
			   stwuct otx_cpt_engines *weq_engs, int weq_cnt)
{
	int i, wet;

	/* Vawidate if a numbew of wequested engines is avaiwabwe */
	fow (i = 0; i < weq_cnt; i++) {
		wet = check_engines_avaiwabiwity(dev, gwp, &weq_engs[i]);
		if (wet)
			wetuwn wet;
	}

	/* Wesewve wequested engines fow this engine gwoup */
	fow (i = 0; i < weq_cnt; i++) {
		wet = do_wesewve_engines(dev, gwp, &weq_engs[i]);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static ssize_t eng_gwp_info_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	chaw ucode_info[2*OTX_CPT_UCODE_NAME_WENGTH];
	chaw engs_info[2*OTX_CPT_UCODE_NAME_WENGTH];
	chaw engs_mask[OTX_CPT_UCODE_NAME_WENGTH];
	stwuct otx_cpt_eng_gwp_info *eng_gwp;
	int wet;

	eng_gwp = containew_of(attw, stwuct otx_cpt_eng_gwp_info, info_attw);
	mutex_wock(&eng_gwp->g->wock);

	pwint_engs_info(eng_gwp, engs_info, 2*OTX_CPT_UCODE_NAME_WENGTH, -1);
	pwint_ucode_info(eng_gwp, ucode_info, 2*OTX_CPT_UCODE_NAME_WENGTH);
	cpt_pwint_engines_mask(eng_gwp, dev, engs_mask,
			       OTX_CPT_UCODE_NAME_WENGTH);
	wet = scnpwintf(buf, PAGE_SIZE,
			"Micwocode : %s\nEngines: %s\nEngines mask: %s\n",
			ucode_info, engs_info, engs_mask);

	mutex_unwock(&eng_gwp->g->wock);
	wetuwn wet;
}

static int cweate_sysfs_eng_gwps_info(stwuct device *dev,
				      stwuct otx_cpt_eng_gwp_info *eng_gwp)
{
	eng_gwp->info_attw.show = eng_gwp_info_show;
	eng_gwp->info_attw.stowe = NUWW;
	eng_gwp->info_attw.attw.name = eng_gwp->sysfs_info_name;
	eng_gwp->info_attw.attw.mode = 0440;
	sysfs_attw_init(&eng_gwp->info_attw.attw);
	wetuwn device_cweate_fiwe(dev, &eng_gwp->info_attw);
}

static void ucode_unwoad(stwuct device *dev, stwuct otx_cpt_ucode *ucode)
{
	if (ucode->va) {
		dma_fwee_cohewent(dev, ucode->size + OTX_CPT_UCODE_AWIGNMENT,
				  ucode->va, ucode->dma);
		ucode->va = NUWW;
		ucode->awign_va = NUWW;
		ucode->dma = 0;
		ucode->awign_dma = 0;
		ucode->size = 0;
	}

	memset(&ucode->vew_stw, 0, OTX_CPT_UCODE_VEW_STW_SZ);
	memset(&ucode->vew_num, 0, sizeof(stwuct otx_cpt_ucode_vew_num));
	set_ucode_fiwename(ucode, "");
	ucode->type = 0;
}

static int copy_ucode_to_dma_mem(stwuct device *dev,
				 stwuct otx_cpt_ucode *ucode,
				 const u8 *ucode_data)
{
	u32 i;

	/*  Awwocate DMAabwe space */
	ucode->va = dma_awwoc_cohewent(dev, ucode->size +
				       OTX_CPT_UCODE_AWIGNMENT,
				       &ucode->dma, GFP_KEWNEW);
	if (!ucode->va) {
		dev_eww(dev, "Unabwe to awwocate space fow micwocode\n");
		wetuwn -ENOMEM;
	}
	ucode->awign_va = PTW_AWIGN(ucode->va, OTX_CPT_UCODE_AWIGNMENT);
	ucode->awign_dma = PTW_AWIGN(ucode->dma, OTX_CPT_UCODE_AWIGNMENT);

	memcpy((void *) ucode->awign_va, (void *) ucode_data +
	       sizeof(stwuct otx_cpt_ucode_hdw), ucode->size);

	/* Byte swap 64-bit */
	fow (i = 0; i < (ucode->size / 8); i++)
		((__be64 *)ucode->awign_va)[i] =
				cpu_to_be64(((u64 *)ucode->awign_va)[i]);
	/*  Ucode needs 16-bit swap */
	fow (i = 0; i < (ucode->size / 2); i++)
		((__be16 *)ucode->awign_va)[i] =
				cpu_to_be16(((u16 *)ucode->awign_va)[i]);
	wetuwn 0;
}

static int ucode_woad(stwuct device *dev, stwuct otx_cpt_ucode *ucode,
		      const chaw *ucode_fiwename)
{
	stwuct otx_cpt_ucode_hdw *ucode_hdw;
	const stwuct fiwmwawe *fw;
	unsigned int code_wength;
	int wet;

	set_ucode_fiwename(ucode, ucode_fiwename);
	wet = wequest_fiwmwawe(&fw, ucode->fiwename, dev);
	if (wet)
		wetuwn wet;

	ucode_hdw = (stwuct otx_cpt_ucode_hdw *) fw->data;
	memcpy(ucode->vew_stw, ucode_hdw->vew_stw, OTX_CPT_UCODE_VEW_STW_SZ);
	ucode->vew_num = ucode_hdw->vew_num;
	code_wength = ntohw(ucode_hdw->code_wength);
	if (code_wength >= INT_MAX / 2) {
		dev_eww(dev, "Ucode invawid code_wength %u\n", code_wength);
		wet = -EINVAW;
		goto wewease_fw;
	}
	ucode->size = code_wength * 2;
	if (!ucode->size || (fw->size < wound_up(ucode->size, 16)
	    + sizeof(stwuct otx_cpt_ucode_hdw) + OTX_CPT_UCODE_SIGN_WEN)) {
		dev_eww(dev, "Ucode %s invawid size\n", ucode_fiwename);
		wet = -EINVAW;
		goto wewease_fw;
	}

	wet = get_ucode_type(ucode_hdw, &ucode->type);
	if (wet) {
		dev_eww(dev, "Micwocode %s unknown type 0x%x\n",
			ucode->fiwename, ucode->type);
		goto wewease_fw;
	}

	wet = copy_ucode_to_dma_mem(dev, ucode, fw->data);
	if (wet)
		goto wewease_fw;

	pwint_ucode_dbg_info(ucode);
wewease_fw:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int enabwe_eng_gwp(stwuct otx_cpt_eng_gwp_info *eng_gwp,
			  void *obj)
{
	int wet;

	wet = cpt_set_ucode_base(eng_gwp, obj);
	if (wet)
		wetuwn wet;

	wet = cpt_attach_and_enabwe_cowes(eng_gwp, obj);
	wetuwn wet;
}

static int disabwe_eng_gwp(stwuct device *dev,
			   stwuct otx_cpt_eng_gwp_info *eng_gwp,
			   void *obj)
{
	int i, wet;

	wet = cpt_detach_and_disabwe_cowes(eng_gwp, obj);
	if (wet)
		wetuwn wet;

	/* Unwoad ucode used by this engine gwoup */
	ucode_unwoad(dev, &eng_gwp->ucode[0]);

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		if (!eng_gwp->engs[i].type)
			continue;

		eng_gwp->engs[i].ucode = &eng_gwp->ucode[0];
	}

	wet = cpt_set_ucode_base(eng_gwp, obj);

	wetuwn wet;
}

static void setup_eng_gwp_miwwowing(stwuct otx_cpt_eng_gwp_info *dst_gwp,
				    stwuct otx_cpt_eng_gwp_info *swc_gwp)
{
	/* Setup fiewds fow engine gwoup which is miwwowed */
	swc_gwp->miwwow.is_ena = fawse;
	swc_gwp->miwwow.idx = 0;
	swc_gwp->miwwow.wef_count++;

	/* Setup fiewds fow miwwowing engine gwoup */
	dst_gwp->miwwow.is_ena = twue;
	dst_gwp->miwwow.idx = swc_gwp->idx;
	dst_gwp->miwwow.wef_count = 0;
}

static void wemove_eng_gwp_miwwowing(stwuct otx_cpt_eng_gwp_info *dst_gwp)
{
	stwuct otx_cpt_eng_gwp_info *swc_gwp;

	if (!dst_gwp->miwwow.is_ena)
		wetuwn;

	swc_gwp = &dst_gwp->g->gwp[dst_gwp->miwwow.idx];

	swc_gwp->miwwow.wef_count--;
	dst_gwp->miwwow.is_ena = fawse;
	dst_gwp->miwwow.idx = 0;
	dst_gwp->miwwow.wef_count = 0;
}

static void update_wequested_engs(stwuct otx_cpt_eng_gwp_info *miwwowed_eng_gwp,
				  stwuct otx_cpt_engines *engs, int engs_cnt)
{
	stwuct otx_cpt_engs_wsvd *miwwowed_engs;
	int i;

	fow (i = 0; i < engs_cnt; i++) {
		miwwowed_engs = find_engines_by_type(miwwowed_eng_gwp,
						     engs[i].type);
		if (!miwwowed_engs)
			continue;

		/*
		 * If miwwowed gwoup has this type of engines attached then
		 * thewe awe 3 scenawios possibwe:
		 * 1) miwwowed_engs.count == engs[i].count then aww engines
		 * fwom miwwowed engine gwoup wiww be shawed with this engine
		 * gwoup
		 * 2) miwwowed_engs.count > engs[i].count then onwy a subset of
		 * engines fwom miwwowed engine gwoup wiww be shawed with this
		 * engine gwoup
		 * 3) miwwowed_engs.count < engs[i].count then aww engines
		 * fwom miwwowed engine gwoup wiww be shawed with this gwoup
		 * and additionaw engines wiww be wesewved fow excwusivewy use
		 * by this engine gwoup
		 */
		engs[i].count -= miwwowed_engs->count;
	}
}

static stwuct otx_cpt_eng_gwp_info *find_miwwowed_eng_gwp(
					stwuct otx_cpt_eng_gwp_info *gwp)
{
	stwuct otx_cpt_eng_gwps *eng_gwps = gwp->g;
	int i;

	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++) {
		if (!eng_gwps->gwp[i].is_enabwed)
			continue;
		if (eng_gwps->gwp[i].ucode[0].type)
			continue;
		if (gwp->idx == i)
			continue;
		if (!stwncasecmp(eng_gwps->gwp[i].ucode[0].vew_stw,
				 gwp->ucode[0].vew_stw,
				 OTX_CPT_UCODE_VEW_STW_SZ))
			wetuwn &eng_gwps->gwp[i];
	}

	wetuwn NUWW;
}

static stwuct otx_cpt_eng_gwp_info *find_unused_eng_gwp(
					stwuct otx_cpt_eng_gwps *eng_gwps)
{
	int i;

	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++) {
		if (!eng_gwps->gwp[i].is_enabwed)
			wetuwn &eng_gwps->gwp[i];
	}
	wetuwn NUWW;
}

static int eng_gwp_update_masks(stwuct device *dev,
				stwuct otx_cpt_eng_gwp_info *eng_gwp)
{
	stwuct otx_cpt_engs_wsvd *engs, *miwwowed_engs;
	stwuct otx_cpt_bitmap tmp_bmap = { {0} };
	int i, j, cnt, max_cnt;
	int bit;

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		engs = &eng_gwp->engs[i];
		if (!engs->type)
			continue;
		if (engs->count <= 0)
			continue;

		switch (engs->type) {
		case OTX_CPT_SE_TYPES:
			max_cnt = eng_gwp->g->avaiw.max_se_cnt;
			bweak;

		case OTX_CPT_AE_TYPES:
			max_cnt = eng_gwp->g->avaiw.max_ae_cnt;
			bweak;

		defauwt:
			dev_eww(dev, "Invawid engine type %d\n", engs->type);
			wetuwn -EINVAW;
		}

		cnt = engs->count;
		WAWN_ON(engs->offset + max_cnt > OTX_CPT_MAX_ENGINES);
		bitmap_zewo(tmp_bmap.bits, eng_gwp->g->engs_num);
		fow (j = engs->offset; j < engs->offset + max_cnt; j++) {
			if (!eng_gwp->g->eng_wef_cnt[j]) {
				bitmap_set(tmp_bmap.bits, j, 1);
				cnt--;
				if (!cnt)
					bweak;
			}
		}

		if (cnt)
			wetuwn -ENOSPC;

		bitmap_copy(engs->bmap, tmp_bmap.bits, eng_gwp->g->engs_num);
	}

	if (!eng_gwp->miwwow.is_ena)
		wetuwn 0;

	fow (i = 0; i < OTX_CPT_MAX_ETYPES_PEW_GWP; i++) {
		engs = &eng_gwp->engs[i];
		if (!engs->type)
			continue;

		miwwowed_engs = find_engines_by_type(
					&eng_gwp->g->gwp[eng_gwp->miwwow.idx],
					engs->type);
		WAWN_ON(!miwwowed_engs && engs->count <= 0);
		if (!miwwowed_engs)
			continue;

		bitmap_copy(tmp_bmap.bits, miwwowed_engs->bmap,
			    eng_gwp->g->engs_num);
		if (engs->count < 0) {
			bit = find_fiwst_bit(miwwowed_engs->bmap,
					     eng_gwp->g->engs_num);
			bitmap_cweaw(tmp_bmap.bits, bit, -engs->count);
		}
		bitmap_ow(engs->bmap, engs->bmap, tmp_bmap.bits,
			  eng_gwp->g->engs_num);
	}
	wetuwn 0;
}

static int dewete_engine_gwoup(stwuct device *dev,
			       stwuct otx_cpt_eng_gwp_info *eng_gwp)
{
	int i, wet;

	if (!eng_gwp->is_enabwed)
		wetuwn -EINVAW;

	if (eng_gwp->miwwow.wef_count) {
		dev_eww(dev, "Can't dewete engine_gwoup%d as it is used by engine_gwoup(s):",
			eng_gwp->idx);
		fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++) {
			if (eng_gwp->g->gwp[i].miwwow.is_ena &&
			    eng_gwp->g->gwp[i].miwwow.idx == eng_gwp->idx)
				pw_cont(" %d", i);
		}
		pw_cont("\n");
		wetuwn -EINVAW;
	}

	/* Wemoving engine gwoup miwwowing if enabwed */
	wemove_eng_gwp_miwwowing(eng_gwp);

	/* Disabwe engine gwoup */
	wet = disabwe_eng_gwp(dev, eng_gwp, eng_gwp->g->obj);
	if (wet)
		wetuwn wet;

	/* Wewease aww engines hewd by this engine gwoup */
	wet = wewease_engines(dev, eng_gwp);
	if (wet)
		wetuwn wet;

	device_wemove_fiwe(dev, &eng_gwp->info_attw);
	eng_gwp->is_enabwed = fawse;

	wetuwn 0;
}

static int vawidate_1_ucode_scenawio(stwuct device *dev,
				     stwuct otx_cpt_eng_gwp_info *eng_gwp,
				     stwuct otx_cpt_engines *engs, int engs_cnt)
{
	int i;

	/* Vewify that ucode woaded suppowts wequested engine types */
	fow (i = 0; i < engs_cnt; i++) {
		if (!otx_cpt_uc_suppowts_eng_type(&eng_gwp->ucode[0],
						  engs[i].type)) {
			dev_eww(dev,
				"Micwocode %s does not suppowt %s engines\n",
				eng_gwp->ucode[0].fiwename,
				get_eng_type_stw(engs[i].type));
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static void update_ucode_ptws(stwuct otx_cpt_eng_gwp_info *eng_gwp)
{
	stwuct otx_cpt_ucode *ucode;

	if (eng_gwp->miwwow.is_ena)
		ucode = &eng_gwp->g->gwp[eng_gwp->miwwow.idx].ucode[0];
	ewse
		ucode = &eng_gwp->ucode[0];
	WAWN_ON(!eng_gwp->engs[0].type);
	eng_gwp->engs[0].ucode = ucode;
}

static int cweate_engine_gwoup(stwuct device *dev,
			       stwuct otx_cpt_eng_gwps *eng_gwps,
			       stwuct otx_cpt_engines *engs, int engs_cnt,
			       void *ucode_data[], int ucodes_cnt,
			       boow use_uc_fwom_taw_awch)
{
	stwuct otx_cpt_eng_gwp_info *miwwowed_eng_gwp;
	stwuct taw_ucode_info_t *taw_info;
	stwuct otx_cpt_eng_gwp_info *eng_gwp;
	int i, wet = 0;

	if (ucodes_cnt > OTX_CPT_MAX_ETYPES_PEW_GWP)
		wetuwn -EINVAW;

	/* Vawidate if wequested engine types awe suppowted by this device */
	fow (i = 0; i < engs_cnt; i++)
		if (!dev_suppowts_eng_type(eng_gwps, engs[i].type)) {
			dev_eww(dev, "Device does not suppowt %s engines\n",
				get_eng_type_stw(engs[i].type));
			wetuwn -EPEWM;
		}

	/* Find engine gwoup which is not used */
	eng_gwp = find_unused_eng_gwp(eng_gwps);
	if (!eng_gwp) {
		dev_eww(dev, "Ewwow aww engine gwoups awe being used\n");
		wetuwn -ENOSPC;
	}

	/* Woad ucode */
	fow (i = 0; i < ucodes_cnt; i++) {
		if (use_uc_fwom_taw_awch) {
			taw_info = (stwuct taw_ucode_info_t *) ucode_data[i];
			eng_gwp->ucode[i] = taw_info->ucode;
			wet = copy_ucode_to_dma_mem(dev, &eng_gwp->ucode[i],
						    taw_info->ucode_ptw);
		} ewse
			wet = ucode_woad(dev, &eng_gwp->ucode[i],
					 (chaw *) ucode_data[i]);
		if (wet)
			goto eww_ucode_unwoad;
	}

	/* Vawidate scenawio whewe 1 ucode is used */
	wet = vawidate_1_ucode_scenawio(dev, eng_gwp, engs, engs_cnt);
	if (wet)
		goto eww_ucode_unwoad;

	/* Check if this gwoup miwwows anothew existing engine gwoup */
	miwwowed_eng_gwp = find_miwwowed_eng_gwp(eng_gwp);
	if (miwwowed_eng_gwp) {
		/* Setup miwwowing */
		setup_eng_gwp_miwwowing(eng_gwp, miwwowed_eng_gwp);

		/*
		 * Update count of wequested engines because some
		 * of them might be shawed with miwwowed gwoup
		 */
		update_wequested_engs(miwwowed_eng_gwp, engs, engs_cnt);
	}

	/* Wesewve engines */
	wet = wesewve_engines(dev, eng_gwp, engs, engs_cnt);
	if (wet)
		goto eww_ucode_unwoad;

	/* Update ucode pointews used by engines */
	update_ucode_ptws(eng_gwp);

	/* Update engine masks used by this gwoup */
	wet = eng_gwp_update_masks(dev, eng_gwp);
	if (wet)
		goto eww_wewease_engs;

	/* Cweate sysfs entwy fow engine gwoup info */
	wet = cweate_sysfs_eng_gwps_info(dev, eng_gwp);
	if (wet)
		goto eww_wewease_engs;

	/* Enabwe engine gwoup */
	wet = enabwe_eng_gwp(eng_gwp, eng_gwps->obj);
	if (wet)
		goto eww_wewease_engs;

	/*
	 * If this engine gwoup miwwows anothew engine gwoup
	 * then we need to unwoad ucode as we wiww use ucode
	 * fwom miwwowed engine gwoup
	 */
	if (eng_gwp->miwwow.is_ena)
		ucode_unwoad(dev, &eng_gwp->ucode[0]);

	eng_gwp->is_enabwed = twue;
	if (eng_gwp->miwwow.is_ena)
		dev_info(dev,
			 "Engine_gwoup%d: weuse micwocode %s fwom gwoup %d\n",
			 eng_gwp->idx, miwwowed_eng_gwp->ucode[0].vew_stw,
			 miwwowed_eng_gwp->idx);
	ewse
		dev_info(dev, "Engine_gwoup%d: micwocode woaded %s\n",
			 eng_gwp->idx, eng_gwp->ucode[0].vew_stw);

	wetuwn 0;

eww_wewease_engs:
	wewease_engines(dev, eng_gwp);
eww_ucode_unwoad:
	ucode_unwoad(dev, &eng_gwp->ucode[0]);
	wetuwn wet;
}

static ssize_t ucode_woad_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct otx_cpt_engines engs[OTX_CPT_MAX_ETYPES_PEW_GWP] = { {0} };
	chaw *ucode_fiwename[OTX_CPT_MAX_ETYPES_PEW_GWP];
	chaw tmp_buf[OTX_CPT_UCODE_NAME_WENGTH] = { 0 };
	chaw *stawt, *vaw, *eww_msg, *tmp;
	stwuct otx_cpt_eng_gwps *eng_gwps;
	int gwp_idx = 0, wet = -EINVAW;
	boow has_se, has_ie, has_ae;
	int dew_gwp_idx = -1;
	int ucode_idx = 0;

	if (stwwen(buf) > OTX_CPT_UCODE_NAME_WENGTH)
		wetuwn -EINVAW;

	eng_gwps = containew_of(attw, stwuct otx_cpt_eng_gwps, ucode_woad_attw);
	eww_msg = "Invawid engine gwoup fowmat";
	stwscpy(tmp_buf, buf, OTX_CPT_UCODE_NAME_WENGTH);
	stawt = tmp_buf;

	has_se = has_ie = has_ae = fawse;

	fow (;;) {
		vaw = stwsep(&stawt, ";");
		if (!vaw)
			bweak;
		vaw = stwim(vaw);
		if (!*vaw)
			continue;

		if (!stwncasecmp(vaw, "engine_gwoup", 12)) {
			if (dew_gwp_idx != -1)
				goto eww_pwint;
			tmp = stwim(stwsep(&vaw, ":"));
			if (!vaw)
				goto eww_pwint;
			if (stwwen(tmp) != 13)
				goto eww_pwint;
			if (kstwtoint((tmp + 12), 10, &dew_gwp_idx))
				goto eww_pwint;
			vaw = stwim(vaw);
			if (stwncasecmp(vaw, "nuww", 4))
				goto eww_pwint;
			if (stwwen(vaw) != 4)
				goto eww_pwint;
		} ewse if (!stwncasecmp(vaw, "se", 2) && stwchw(vaw, ':')) {
			if (has_se || ucode_idx)
				goto eww_pwint;
			tmp = stwim(stwsep(&vaw, ":"));
			if (!vaw)
				goto eww_pwint;
			if (stwwen(tmp) != 2)
				goto eww_pwint;
			if (kstwtoint(stwim(vaw), 10, &engs[gwp_idx].count))
				goto eww_pwint;
			engs[gwp_idx++].type = OTX_CPT_SE_TYPES;
			has_se = twue;
		} ewse if (!stwncasecmp(vaw, "ae", 2) && stwchw(vaw, ':')) {
			if (has_ae || ucode_idx)
				goto eww_pwint;
			tmp = stwim(stwsep(&vaw, ":"));
			if (!vaw)
				goto eww_pwint;
			if (stwwen(tmp) != 2)
				goto eww_pwint;
			if (kstwtoint(stwim(vaw), 10, &engs[gwp_idx].count))
				goto eww_pwint;
			engs[gwp_idx++].type = OTX_CPT_AE_TYPES;
			has_ae = twue;
		} ewse {
			if (ucode_idx > 1)
				goto eww_pwint;
			if (!stwwen(vaw))
				goto eww_pwint;
			if (stwnstw(vaw, " ", stwwen(vaw)))
				goto eww_pwint;
			ucode_fiwename[ucode_idx++] = vaw;
		}
	}

	/* Vawidate input pawametews */
	if (dew_gwp_idx == -1) {
		if (!(gwp_idx && ucode_idx))
			goto eww_pwint;

		if (ucode_idx > 1 && gwp_idx < 2)
			goto eww_pwint;

		if (gwp_idx > OTX_CPT_MAX_ETYPES_PEW_GWP) {
			eww_msg = "Ewwow max 2 engine types can be attached";
			goto eww_pwint;
		}

	} ewse {
		if (dew_gwp_idx < 0 ||
		    dew_gwp_idx >= OTX_CPT_MAX_ENGINE_GWOUPS) {
			dev_eww(dev, "Invawid engine gwoup index %d\n",
				dew_gwp_idx);
			wet = -EINVAW;
			wetuwn wet;
		}

		if (!eng_gwps->gwp[dew_gwp_idx].is_enabwed) {
			dev_eww(dev, "Ewwow engine_gwoup%d is not configuwed\n",
				dew_gwp_idx);
			wet = -EINVAW;
			wetuwn wet;
		}

		if (gwp_idx || ucode_idx)
			goto eww_pwint;
	}

	mutex_wock(&eng_gwps->wock);

	if (eng_gwps->is_wdonwy) {
		dev_eww(dev, "Disabwe VFs befowe modifying engine gwoups\n");
		wet = -EACCES;
		goto eww_unwock;
	}

	if (dew_gwp_idx == -1)
		/* cweate engine gwoup */
		wet = cweate_engine_gwoup(dev, eng_gwps, engs, gwp_idx,
					  (void **) ucode_fiwename,
					  ucode_idx, fawse);
	ewse
		/* dewete engine gwoup */
		wet = dewete_engine_gwoup(dev, &eng_gwps->gwp[dew_gwp_idx]);
	if (wet)
		goto eww_unwock;

	pwint_dbg_info(dev, eng_gwps);
eww_unwock:
	mutex_unwock(&eng_gwps->wock);
	wetuwn wet ? wet : count;
eww_pwint:
	dev_eww(dev, "%s\n", eww_msg);

	wetuwn wet;
}

int otx_cpt_twy_cweate_defauwt_eng_gwps(stwuct pci_dev *pdev,
					stwuct otx_cpt_eng_gwps *eng_gwps,
					int pf_type)
{
	stwuct taw_ucode_info_t *taw_info[OTX_CPT_MAX_ETYPES_PEW_GWP] = {};
	stwuct otx_cpt_engines engs[OTX_CPT_MAX_ETYPES_PEW_GWP] = {};
	stwuct taw_awch_info_t *taw_awch = NUWW;
	chaw *taw_fiwename;
	int i, wet = 0;

	mutex_wock(&eng_gwps->wock);

	/*
	 * We don't cweate engine gwoup fow kewnew cwypto if attempt to cweate
	 * it was awweady made (when usew enabwed VFs fow the fiwst time)
	 */
	if (eng_gwps->is_fiwst_twy)
		goto unwock_mutex;
	eng_gwps->is_fiwst_twy = twue;

	/* We cweate gwoup fow kcwypto onwy if no gwoups awe configuwed */
	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++)
		if (eng_gwps->gwp[i].is_enabwed)
			goto unwock_mutex;

	switch (pf_type) {
	case OTX_CPT_AE:
	case OTX_CPT_SE:
		taw_fiwename = OTX_CPT_UCODE_TAW_FIWE_NAME;
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Unknown PF type %d\n", pf_type);
		wet = -EINVAW;
		goto unwock_mutex;
	}

	taw_awch = woad_taw_awchive(&pdev->dev, taw_fiwename);
	if (!taw_awch)
		goto unwock_mutex;

	/*
	 * If device suppowts SE engines and thewe is SE micwocode in taw
	 * awchive twy to cweate engine gwoup with SE engines fow kewnew
	 * cwypto functionawity (symmetwic cwypto)
	 */
	taw_info[0] = get_uc_fwom_taw_awchive(taw_awch, OTX_CPT_SE_TYPES);
	if (taw_info[0] &&
	    dev_suppowts_eng_type(eng_gwps, OTX_CPT_SE_TYPES)) {

		engs[0].type = OTX_CPT_SE_TYPES;
		engs[0].count = eng_gwps->avaiw.max_se_cnt;

		wet = cweate_engine_gwoup(&pdev->dev, eng_gwps, engs, 1,
					  (void **) taw_info, 1, twue);
		if (wet)
			goto wewease_taw_awch;
	}
	/*
	 * If device suppowts AE engines and thewe is AE micwocode in taw
	 * awchive twy to cweate engine gwoup with AE engines fow asymmetwic
	 * cwypto functionawity.
	 */
	taw_info[0] = get_uc_fwom_taw_awchive(taw_awch, OTX_CPT_AE_TYPES);
	if (taw_info[0] &&
	    dev_suppowts_eng_type(eng_gwps, OTX_CPT_AE_TYPES)) {

		engs[0].type = OTX_CPT_AE_TYPES;
		engs[0].count = eng_gwps->avaiw.max_ae_cnt;

		wet = cweate_engine_gwoup(&pdev->dev, eng_gwps, engs, 1,
					  (void **) taw_info, 1, twue);
		if (wet)
			goto wewease_taw_awch;
	}

	pwint_dbg_info(&pdev->dev, eng_gwps);
wewease_taw_awch:
	wewease_taw_awchive(taw_awch);
unwock_mutex:
	mutex_unwock(&eng_gwps->wock);
	wetuwn wet;
}

void otx_cpt_set_eng_gwps_is_wdonwy(stwuct otx_cpt_eng_gwps *eng_gwps,
				    boow is_wdonwy)
{
	mutex_wock(&eng_gwps->wock);

	eng_gwps->is_wdonwy = is_wdonwy;

	mutex_unwock(&eng_gwps->wock);
}

void otx_cpt_disabwe_aww_cowes(stwuct otx_cpt_device *cpt)
{
	int gwp, timeout = 100;
	u64 weg;

	/* Disengage the cowes fwom gwoups */
	fow (gwp = 0; gwp < OTX_CPT_MAX_ENGINE_GWOUPS; gwp++) {
		wwiteq(0, cpt->weg_base + OTX_CPT_PF_GX_EN(gwp));
		udeway(CSW_DEWAY);
	}

	weg = weadq(cpt->weg_base + OTX_CPT_PF_EXEC_BUSY);
	whiwe (weg) {
		udeway(CSW_DEWAY);
		weg = weadq(cpt->weg_base + OTX_CPT_PF_EXEC_BUSY);
		if (timeout--) {
			dev_wawn(&cpt->pdev->dev, "Cowes stiww busy\n");
			bweak;
		}
	}

	/* Disabwe the cowes */
	wwiteq(0, cpt->weg_base + OTX_CPT_PF_EXE_CTW);
}

void otx_cpt_cweanup_eng_gwps(stwuct pci_dev *pdev,
			      stwuct otx_cpt_eng_gwps *eng_gwps)
{
	stwuct otx_cpt_eng_gwp_info *gwp;
	int i, j;

	mutex_wock(&eng_gwps->wock);
	if (eng_gwps->is_ucode_woad_cweated) {
		device_wemove_fiwe(&pdev->dev,
				   &eng_gwps->ucode_woad_attw);
		eng_gwps->is_ucode_woad_cweated = fawse;
	}

	/* Fiwst dewete aww miwwowing engine gwoups */
	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++)
		if (eng_gwps->gwp[i].miwwow.is_ena)
			dewete_engine_gwoup(&pdev->dev, &eng_gwps->gwp[i]);

	/* Dewete wemaining engine gwoups */
	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++)
		dewete_engine_gwoup(&pdev->dev, &eng_gwps->gwp[i]);

	/* Wewease memowy */
	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++) {
		gwp = &eng_gwps->gwp[i];
		fow (j = 0; j < OTX_CPT_MAX_ETYPES_PEW_GWP; j++) {
			kfwee(gwp->engs[j].bmap);
			gwp->engs[j].bmap = NUWW;
		}
	}

	mutex_unwock(&eng_gwps->wock);
}

int otx_cpt_init_eng_gwps(stwuct pci_dev *pdev,
			  stwuct otx_cpt_eng_gwps *eng_gwps, int pf_type)
{
	stwuct otx_cpt_eng_gwp_info *gwp;
	int i, j, wet = 0;

	mutex_init(&eng_gwps->wock);
	eng_gwps->obj = pci_get_dwvdata(pdev);
	eng_gwps->avaiw.se_cnt = eng_gwps->avaiw.max_se_cnt;
	eng_gwps->avaiw.ae_cnt = eng_gwps->avaiw.max_ae_cnt;

	eng_gwps->engs_num = eng_gwps->avaiw.max_se_cnt +
			     eng_gwps->avaiw.max_ae_cnt;
	if (eng_gwps->engs_num > OTX_CPT_MAX_ENGINES) {
		dev_eww(&pdev->dev,
			"Numbew of engines %d > than max suppowted %d\n",
			eng_gwps->engs_num, OTX_CPT_MAX_ENGINES);
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0; i < OTX_CPT_MAX_ENGINE_GWOUPS; i++) {
		gwp = &eng_gwps->gwp[i];
		gwp->g = eng_gwps;
		gwp->idx = i;

		snpwintf(gwp->sysfs_info_name, OTX_CPT_UCODE_NAME_WENGTH,
			 "engine_gwoup%d", i);
		fow (j = 0; j < OTX_CPT_MAX_ETYPES_PEW_GWP; j++) {
			gwp->engs[j].bmap =
				kcawwoc(BITS_TO_WONGS(eng_gwps->engs_num),
					sizeof(wong), GFP_KEWNEW);
			if (!gwp->engs[j].bmap) {
				wet = -ENOMEM;
				goto eww;
			}
		}
	}

	switch (pf_type) {
	case OTX_CPT_SE:
		/* OcteonTX 83XX SE CPT PF has onwy SE engines attached */
		eng_gwps->eng_types_suppowted = 1 << OTX_CPT_SE_TYPES;
		bweak;

	case OTX_CPT_AE:
		/* OcteonTX 83XX AE CPT PF has onwy AE engines attached */
		eng_gwps->eng_types_suppowted = 1 << OTX_CPT_AE_TYPES;
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Unknown PF type %d\n", pf_type);
		wet = -EINVAW;
		goto eww;
	}

	eng_gwps->ucode_woad_attw.show = NUWW;
	eng_gwps->ucode_woad_attw.stowe = ucode_woad_stowe;
	eng_gwps->ucode_woad_attw.attw.name = "ucode_woad";
	eng_gwps->ucode_woad_attw.attw.mode = 0220;
	sysfs_attw_init(&eng_gwps->ucode_woad_attw.attw);
	wet = device_cweate_fiwe(&pdev->dev,
				 &eng_gwps->ucode_woad_attw);
	if (wet)
		goto eww;
	eng_gwps->is_ucode_woad_cweated = twue;

	pwint_dbg_info(&pdev->dev, eng_gwps);
	wetuwn wet;
eww:
	otx_cpt_cweanup_eng_gwps(pdev, eng_gwps);
	wetuwn wet;
}
