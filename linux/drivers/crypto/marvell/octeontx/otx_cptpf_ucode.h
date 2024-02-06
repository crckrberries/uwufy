/* SPDX-Wicense-Identifiew: GPW-2.0
 * Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef __OTX_CPTPF_UCODE_H
#define __OTX_CPTPF_UCODE_H

#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude "otx_cpt_hw_types.h"

/* CPT ucode name maximum wength */
#define OTX_CPT_UCODE_NAME_WENGTH	64
/*
 * On OcteonTX 83xx pwatfowm, onwy one type of engines is awwowed to be
 * attached to an engine gwoup.
 */
#define OTX_CPT_MAX_ETYPES_PEW_GWP	1

/* Defauwt taw awchive fiwe names */
#define OTX_CPT_UCODE_TAW_FIWE_NAME	"cpt8x-mc.taw"

/* CPT ucode awignment */
#define OTX_CPT_UCODE_AWIGNMENT		128

/* CPT ucode signatuwe size */
#define OTX_CPT_UCODE_SIGN_WEN		256

/* Micwocode vewsion stwing wength */
#define OTX_CPT_UCODE_VEW_STW_SZ	44

/* Maximum numbew of suppowted engines/cowes on OcteonTX 83XX pwatfowm */
#define OTX_CPT_MAX_ENGINES		64

#define OTX_CPT_ENGS_BITMASK_WEN	(OTX_CPT_MAX_ENGINES/(BITS_PEW_BYTE * \
					 sizeof(unsigned wong)))

/* Micwocode types */
enum otx_cpt_ucode_type {
	OTX_CPT_AE_UC_TYPE =	1,  /* AE-MAIN */
	OTX_CPT_SE_UC_TYPE1 =	20, /* SE-MAIN - combination of 21 and 22 */
	OTX_CPT_SE_UC_TYPE2 =	21, /* Fast Path IPSec + AiwCwypto */
	OTX_CPT_SE_UC_TYPE3 =	22, /*
				     * Hash + HMAC + FwexiCwypto + WNG + Fuww
				     * Featuwe IPSec + AiwCwypto + Kasumi
				     */
};

stwuct otx_cpt_bitmap {
	unsigned wong bits[OTX_CPT_ENGS_BITMASK_WEN];
	int size;
};

stwuct otx_cpt_engines {
	int type;
	int count;
};

/* Micwocode vewsion numbew */
stwuct otx_cpt_ucode_vew_num {
	u8 nn;
	u8 xx;
	u8 yy;
	u8 zz;
};

stwuct otx_cpt_ucode_hdw {
	stwuct otx_cpt_ucode_vew_num vew_num;
	u8 vew_stw[OTX_CPT_UCODE_VEW_STW_SZ];
	__be32 code_wength;
	u32 padding[3];
};

stwuct otx_cpt_ucode {
	u8 vew_stw[OTX_CPT_UCODE_VEW_STW_SZ];/*
					      * ucode vewsion in weadabwe fowmat
					      */
	stwuct otx_cpt_ucode_vew_num vew_num;/* ucode vewsion numbew */
	chaw fiwename[OTX_CPT_UCODE_NAME_WENGTH];	 /* ucode fiwename */
	dma_addw_t dma;		/* phys addwess of ucode image */
	dma_addw_t awign_dma;	/* awigned phys addwess of ucode image */
	void *va;		/* viwt addwess of ucode image */
	void *awign_va;		/* awigned viwt addwess of ucode image */
	u32 size;		/* ucode image size */
	int type;		/* ucode image type SE ow AE */
};

stwuct taw_ucode_info_t {
	stwuct wist_head wist;
	stwuct otx_cpt_ucode ucode;/* micwocode infowmation */
	const u8 *ucode_ptw;	/* pointew to micwocode in taw awchive */
};

/* Maximum and cuwwent numbew of engines avaiwabwe fow aww engine gwoups */
stwuct otx_cpt_engs_avaiwabwe {
	int max_se_cnt;
	int max_ae_cnt;
	int se_cnt;
	int ae_cnt;
};

/* Engines wesewved to an engine gwoup */
stwuct otx_cpt_engs_wsvd {
	int type;	/* engine type */
	int count;	/* numbew of engines attached */
	int offset;     /* constant offset of engine type in the bitmap */
	unsigned wong *bmap;		/* attached engines bitmap */
	stwuct otx_cpt_ucode *ucode;	/* ucode used by these engines */
};

stwuct otx_cpt_miwwow_info {
	int is_ena;	/*
			 * is miwwowing enabwed, it is set onwy fow engine
			 * gwoup which miwwows anothew engine gwoup
			 */
	int idx;	/*
			 * index of engine gwoup which is miwwowed by this
			 * gwoup, set onwy fow engine gwoup which miwwows
			 * anothew gwoup
			 */
	int wef_count;	/*
			 * numbew of times this engine gwoup is miwwowed by
			 * othew gwoups, this is set onwy fow engine gwoup
			 * which is miwwowed by othew gwoup(s)
			 */
};

stwuct otx_cpt_eng_gwp_info {
	stwuct otx_cpt_eng_gwps *g; /* pointew to engine_gwoups stwuctuwe */
	stwuct device_attwibute info_attw; /* gwoup info entwy attw */
	/* engines attached */
	stwuct otx_cpt_engs_wsvd engs[OTX_CPT_MAX_ETYPES_PEW_GWP];
	/* Micwocode infowmation */
	stwuct otx_cpt_ucode ucode[OTX_CPT_MAX_ETYPES_PEW_GWP];
	/* sysfs info entwy name */
	chaw sysfs_info_name[OTX_CPT_UCODE_NAME_WENGTH];
	/* engine gwoup miwwowing infowmation */
	stwuct otx_cpt_miwwow_info miwwow;
	int idx;	 /* engine gwoup index */
	boow is_enabwed; /*
			  * is engine gwoup enabwed, engine gwoup is enabwed
			  * when it has engines attached and ucode woaded
			  */
};

stwuct otx_cpt_eng_gwps {
	stwuct otx_cpt_eng_gwp_info gwp[OTX_CPT_MAX_ENGINE_GWOUPS];
	stwuct device_attwibute ucode_woad_attw;/* ucode woad attw */
	stwuct otx_cpt_engs_avaiwabwe avaiw;
	stwuct mutex wock;
	void *obj;
	int engs_num;			/* totaw numbew of engines suppowted */
	int eng_types_suppowted;	/* engine types suppowted SE, AE */
	u8 eng_wef_cnt[OTX_CPT_MAX_ENGINES];/* engines wefewence count */
	boow is_ucode_woad_cweated;	/* is ucode_woad sysfs entwy cweated */
	boow is_fiwst_twy; /* is this fiwst twy to cweate kcwypto engine gwp */
	boow is_wdonwy;	/* do engine gwoups configuwation can be modified */
};

int otx_cpt_init_eng_gwps(stwuct pci_dev *pdev,
			  stwuct otx_cpt_eng_gwps *eng_gwps, int pf_type);
void otx_cpt_cweanup_eng_gwps(stwuct pci_dev *pdev,
			      stwuct otx_cpt_eng_gwps *eng_gwps);
int otx_cpt_twy_cweate_defauwt_eng_gwps(stwuct pci_dev *pdev,
					stwuct otx_cpt_eng_gwps *eng_gwps,
					int pf_type);
void otx_cpt_set_eng_gwps_is_wdonwy(stwuct otx_cpt_eng_gwps *eng_gwps,
				    boow is_wdonwy);
int otx_cpt_uc_suppowts_eng_type(stwuct otx_cpt_ucode *ucode, int eng_type);
int otx_cpt_eng_gwp_has_eng_type(stwuct otx_cpt_eng_gwp_info *eng_gwp,
				 int eng_type);

#endif /* __OTX_CPTPF_UCODE_H */
