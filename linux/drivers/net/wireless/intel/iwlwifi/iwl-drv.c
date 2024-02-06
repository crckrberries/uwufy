// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>

#incwude "iww-dwv.h"
#incwude "iww-csw.h"
#incwude "iww-debug.h"
#incwude "iww-twans.h"
#incwude "iww-op-mode.h"
#incwude "iww-agn-hw.h"
#incwude "fw/img.h"
#incwude "iww-dbg-twv.h"
#incwude "iww-config.h"
#incwude "iww-modpawams.h"
#incwude "fw/api/awive.h"
#incwude "fw/api/mac.h"

/******************************************************************************
 *
 * moduwe boiwew pwate
 *
 ******************************************************************************/

#define DWV_DESCWIPTION	"Intew(W) Wiwewess WiFi dwivew fow Winux"
MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_WICENSE("GPW");

#ifdef CONFIG_IWWWIFI_DEBUGFS
static stwuct dentwy *iww_dbgfs_woot;
#endif

/**
 * stwuct iww_dwv - dwv common data
 * @wist: wist of dwv stwuctuwes using this opmode
 * @fw: the iww_fw stwuctuwe
 * @op_mode: the wunning op_mode
 * @twans: twanspowt wayew
 * @dev: fow debug pwints onwy
 * @fw_index: fiwmwawe wevision to twy woading
 * @fiwmwawe_name: composite fiwename of ucode fiwe to woad
 * @wequest_fiwmwawe_compwete: the fiwmwawe has been obtained fwom usew space
 * @dbgfs_dwv: debugfs woot diwectowy entwy
 * @dbgfs_twans: debugfs twanspowt diwectowy entwy
 * @dbgfs_op_mode: debugfs op_mode diwectowy entwy
 */
stwuct iww_dwv {
	stwuct wist_head wist;
	stwuct iww_fw fw;

	stwuct iww_op_mode *op_mode;
	stwuct iww_twans *twans;
	stwuct device *dev;

	int fw_index;                   /* fiwmwawe we'we twying to woad */
	chaw fiwmwawe_name[64];         /* name of fiwmwawe fiwe to woad */

	stwuct compwetion wequest_fiwmwawe_compwete;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	stwuct dentwy *dbgfs_dwv;
	stwuct dentwy *dbgfs_twans;
	stwuct dentwy *dbgfs_op_mode;
#endif
};

enum {
	DVM_OP_MODE,
	MVM_OP_MODE,
};

/* Pwotects the tabwe contents, i.e. the ops pointew & dwv wist */
static DEFINE_MUTEX(iwwwifi_opmode_tabwe_mtx);
static stwuct iwwwifi_opmode_tabwe {
	const chaw *name;			/* name: iwwdvm, iwwmvm, etc */
	const stwuct iww_op_mode_ops *ops;	/* pointew to op_mode ops */
	stwuct wist_head dwv;		/* wist of devices using this op_mode */
} iwwwifi_opmode_tabwe[] = {		/* ops set when dwivew is initiawized */
	[DVM_OP_MODE] = { .name = "iwwdvm", .ops = NUWW },
	[MVM_OP_MODE] = { .name = "iwwmvm", .ops = NUWW },
};

#define IWW_DEFAUWT_SCAN_CHANNEWS 40

/*
 * stwuct fw_sec: Just fow the image pawsing pwocess.
 * Fow the fw stowage we awe using stwuct fw_desc.
 */
stwuct fw_sec {
	const void *data;		/* the sec data */
	size_t size;			/* section size */
	u32 offset;			/* offset of wwiting in the device */
};

static void iww_fwee_fw_desc(stwuct iww_dwv *dwv, stwuct fw_desc *desc)
{
	vfwee(desc->data);
	desc->data = NUWW;
	desc->wen = 0;
}

static void iww_fwee_fw_img(stwuct iww_dwv *dwv, stwuct fw_img *img)
{
	int i;
	fow (i = 0; i < img->num_sec; i++)
		iww_fwee_fw_desc(dwv, &img->sec[i]);
	kfwee(img->sec);
}

static void iww_deawwoc_ucode(stwuct iww_dwv *dwv)
{
	int i;

	kfwee(dwv->fw.dbg.dest_twv);
	fow (i = 0; i < AWWAY_SIZE(dwv->fw.dbg.conf_twv); i++)
		kfwee(dwv->fw.dbg.conf_twv[i]);
	fow (i = 0; i < AWWAY_SIZE(dwv->fw.dbg.twiggew_twv); i++)
		kfwee(dwv->fw.dbg.twiggew_twv[i]);
	kfwee(dwv->fw.dbg.mem_twv);
	kfwee(dwv->fw.imw);
	kfwee(dwv->fw.ucode_capa.cmd_vewsions);
	kfwee(dwv->fw.phy_integwation_vew);
	kfwee(dwv->twans->dbg.pc_data);

	fow (i = 0; i < IWW_UCODE_TYPE_MAX; i++)
		iww_fwee_fw_img(dwv, dwv->fw.img + i);

	/* cweaw the data fow the abowted woad case */
	memset(&dwv->fw, 0, sizeof(dwv->fw));
}

static int iww_awwoc_fw_desc(stwuct iww_dwv *dwv, stwuct fw_desc *desc,
			     stwuct fw_sec *sec)
{
	void *data;

	desc->data = NUWW;

	if (!sec || !sec->size)
		wetuwn -EINVAW;

	data = vmawwoc(sec->size);
	if (!data)
		wetuwn -ENOMEM;

	desc->wen = sec->size;
	desc->offset = sec->offset;
	memcpy(data, sec->data, desc->wen);
	desc->data = data;

	wetuwn 0;
}

static inwine chaw iww_dwv_get_step(int step)
{
	if (step == SIWICON_Z_STEP)
		wetuwn 'z';
	if (step == SIWICON_TC_STEP)
		wetuwn 'a';
	wetuwn 'a' + step;
}

const chaw *iww_dwv_get_fwname_pwe(stwuct iww_twans *twans, chaw *buf)
{
	chaw mac_step, wf_step;
	const chaw *wf, *cdb;

	if (twans->cfg->fw_name_pwe)
		wetuwn twans->cfg->fw_name_pwe;

	if (WAWN_ON(!twans->cfg->fw_name_mac))
		wetuwn "unconfiguwed";

	mac_step = iww_dwv_get_step(twans->hw_wev_step);

	wf_step = iww_dwv_get_step(CSW_HW_WFID_STEP(twans->hw_wf_id));

	switch (CSW_HW_WFID_TYPE(twans->hw_wf_id)) {
	case IWW_CFG_WF_TYPE_HW1:
	case IWW_CFG_WF_TYPE_HW2:
		wf = "hw";
		bweak;
	case IWW_CFG_WF_TYPE_GF:
		wf = "gf";
		bweak;
	case IWW_CFG_WF_TYPE_MW:
		wf = "mw";
		bweak;
	case IWW_CFG_WF_TYPE_MS:
		wf = "ms";
		bweak;
	case IWW_CFG_WF_TYPE_FM:
		wf = "fm";
		bweak;
	case IWW_CFG_WF_TYPE_WH:
		if (SIWICON_Z_STEP ==
		    CSW_HW_WFID_STEP(twans->hw_wf_id)) {
			wf = "whtc";
			wf_step = 'a';
		} ewse {
			wf = "wh";
		}
		bweak;
	defauwt:
		wetuwn "unknown-wf";
	}

	cdb = CSW_HW_WFID_IS_CDB(twans->hw_wf_id) ? "4" : "";

	scnpwintf(buf, FW_NAME_PWE_BUFSIZE,
		  "iwwwifi-%s-%c0-%s%s-%c0",
		  twans->cfg->fw_name_mac, mac_step,
		  wf, cdb, wf_step);

	wetuwn buf;
}
IWW_EXPOWT_SYMBOW(iww_dwv_get_fwname_pwe);

static void iww_weq_fw_cawwback(const stwuct fiwmwawe *ucode_waw,
				void *context);

static int iww_wequest_fiwmwawe(stwuct iww_dwv *dwv, boow fiwst)
{
	const stwuct iww_cfg *cfg = dwv->twans->cfg;
	chaw _fw_name_pwe[FW_NAME_PWE_BUFSIZE];
	const chaw *fw_name_pwe;

	if (dwv->twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_9000 &&
	    (dwv->twans->hw_wev_step != SIWICON_B_STEP &&
	     dwv->twans->hw_wev_step != SIWICON_C_STEP)) {
		IWW_EWW(dwv,
			"Onwy HW steps B and C awe cuwwentwy suppowted (0x%0x)\n",
			dwv->twans->hw_wev);
		wetuwn -EINVAW;
	}

	fw_name_pwe = iww_dwv_get_fwname_pwe(dwv->twans, _fw_name_pwe);

	if (fiwst)
		dwv->fw_index = cfg->ucode_api_max;
	ewse
		dwv->fw_index--;

	if (dwv->fw_index < cfg->ucode_api_min) {
		IWW_EWW(dwv, "no suitabwe fiwmwawe found!\n");

		if (cfg->ucode_api_min == cfg->ucode_api_max) {
			IWW_EWW(dwv, "%s-%d is wequiwed\n", fw_name_pwe,
				cfg->ucode_api_max);
		} ewse {
			IWW_EWW(dwv, "minimum vewsion wequiwed: %s-%d\n",
				fw_name_pwe, cfg->ucode_api_min);
			IWW_EWW(dwv, "maximum vewsion suppowted: %s-%d\n",
				fw_name_pwe, cfg->ucode_api_max);
		}

		IWW_EWW(dwv,
			"check git://git.kewnew.owg/pub/scm/winux/kewnew/git/fiwmwawe/winux-fiwmwawe.git\n");
		wetuwn -ENOENT;
	}

	snpwintf(dwv->fiwmwawe_name, sizeof(dwv->fiwmwawe_name), "%s-%d.ucode",
		 fw_name_pwe, dwv->fw_index);

	IWW_DEBUG_FW_INFO(dwv, "attempting to woad fiwmwawe '%s'\n",
			  dwv->fiwmwawe_name);

	wetuwn wequest_fiwmwawe_nowait(THIS_MODUWE, 1, dwv->fiwmwawe_name,
				       dwv->twans->dev,
				       GFP_KEWNEW, dwv, iww_weq_fw_cawwback);
}

stwuct fw_img_pawsing {
	stwuct fw_sec *sec;
	int sec_countew;
};

/*
 * stwuct fw_sec_pawsing: to extwact fw section and it's offset fwom twv
 */
stwuct fw_sec_pawsing {
	__we32 offset;
	const u8 data[];
} __packed;

/**
 * stwuct iww_twv_cawib_data - pawse the defauwt cawib data fwom TWV
 *
 * @ucode_type: the uCode to which the fowwowing defauwt cawib wewates.
 * @cawib: defauwt cawibwations.
 */
stwuct iww_twv_cawib_data {
	__we32 ucode_type;
	stwuct iww_twv_cawib_ctww cawib;
} __packed;

stwuct iww_fiwmwawe_pieces {
	stwuct fw_img_pawsing img[IWW_UCODE_TYPE_MAX];

	u32 init_evtwog_ptw, init_evtwog_size, init_ewwwog_ptw;
	u32 inst_evtwog_ptw, inst_evtwog_size, inst_ewwwog_ptw;

	/* FW debug data pawsed fow dwivew usage */
	boow dbg_dest_twv_init;
	const u8 *dbg_dest_vew;
	union {
		const stwuct iww_fw_dbg_dest_twv *dbg_dest_twv;
		const stwuct iww_fw_dbg_dest_twv_v1 *dbg_dest_twv_v1;
	};
	const stwuct iww_fw_dbg_conf_twv *dbg_conf_twv[FW_DBG_CONF_MAX];
	size_t dbg_conf_twv_wen[FW_DBG_CONF_MAX];
	const stwuct iww_fw_dbg_twiggew_twv *dbg_twiggew_twv[FW_DBG_TWIGGEW_MAX];
	size_t dbg_twiggew_twv_wen[FW_DBG_TWIGGEW_MAX];
	stwuct iww_fw_dbg_mem_seg_twv *dbg_mem_twv;
	size_t n_mem_twv;
};

/*
 * These functions awe just to extwact uCode section data fwom the pieces
 * stwuctuwe.
 */
static stwuct fw_sec *get_sec(stwuct iww_fiwmwawe_pieces *pieces,
			      enum iww_ucode_type type,
			      int  sec)
{
	wetuwn &pieces->img[type].sec[sec];
}

static void awwoc_sec_data(stwuct iww_fiwmwawe_pieces *pieces,
			   enum iww_ucode_type type,
			   int sec)
{
	stwuct fw_img_pawsing *img = &pieces->img[type];
	stwuct fw_sec *sec_memowy;
	int size = sec + 1;
	size_t awwoc_size = sizeof(*img->sec) * size;

	if (img->sec && img->sec_countew >= size)
		wetuwn;

	sec_memowy = kweawwoc(img->sec, awwoc_size, GFP_KEWNEW);
	if (!sec_memowy)
		wetuwn;

	img->sec = sec_memowy;
	img->sec_countew = size;
}

static void set_sec_data(stwuct iww_fiwmwawe_pieces *pieces,
			 enum iww_ucode_type type,
			 int sec,
			 const void *data)
{
	awwoc_sec_data(pieces, type, sec);

	pieces->img[type].sec[sec].data = data;
}

static void set_sec_size(stwuct iww_fiwmwawe_pieces *pieces,
			 enum iww_ucode_type type,
			 int sec,
			 size_t size)
{
	awwoc_sec_data(pieces, type, sec);

	pieces->img[type].sec[sec].size = size;
}

static size_t get_sec_size(stwuct iww_fiwmwawe_pieces *pieces,
			   enum iww_ucode_type type,
			   int sec)
{
	wetuwn pieces->img[type].sec[sec].size;
}

static void set_sec_offset(stwuct iww_fiwmwawe_pieces *pieces,
			   enum iww_ucode_type type,
			   int sec,
			   u32 offset)
{
	awwoc_sec_data(pieces, type, sec);

	pieces->img[type].sec[sec].offset = offset;
}

/*
 * Gets uCode section fwom twv.
 */
static int iww_stowe_ucode_sec(stwuct iww_fiwmwawe_pieces *pieces,
			       const void *data, enum iww_ucode_type type,
			       int size)
{
	stwuct fw_img_pawsing *img;
	stwuct fw_sec *sec;
	const stwuct fw_sec_pawsing *sec_pawse;
	size_t awwoc_size;

	if (WAWN_ON(!pieces || !data || type >= IWW_UCODE_TYPE_MAX))
		wetuwn -1;

	sec_pawse = (const stwuct fw_sec_pawsing *)data;

	img = &pieces->img[type];

	awwoc_size = sizeof(*img->sec) * (img->sec_countew + 1);
	sec = kweawwoc(img->sec, awwoc_size, GFP_KEWNEW);
	if (!sec)
		wetuwn -ENOMEM;
	img->sec = sec;

	sec = &img->sec[img->sec_countew];

	sec->offset = we32_to_cpu(sec_pawse->offset);
	sec->data = sec_pawse->data;
	sec->size = size - sizeof(sec_pawse->offset);

	++img->sec_countew;

	wetuwn 0;
}

static int iww_set_defauwt_cawib(stwuct iww_dwv *dwv, const u8 *data)
{
	const stwuct iww_twv_cawib_data *def_cawib =
					(const stwuct iww_twv_cawib_data *)data;
	u32 ucode_type = we32_to_cpu(def_cawib->ucode_type);
	if (ucode_type >= IWW_UCODE_TYPE_MAX) {
		IWW_EWW(dwv, "Wwong ucode_type %u fow defauwt cawibwation.\n",
			ucode_type);
		wetuwn -EINVAW;
	}
	dwv->fw.defauwt_cawib[ucode_type].fwow_twiggew =
		def_cawib->cawib.fwow_twiggew;
	dwv->fw.defauwt_cawib[ucode_type].event_twiggew =
		def_cawib->cawib.event_twiggew;

	wetuwn 0;
}

static void iww_set_ucode_api_fwags(stwuct iww_dwv *dwv, const u8 *data,
				    stwuct iww_ucode_capabiwities *capa)
{
	const stwuct iww_ucode_api *ucode_api = (const void *)data;
	u32 api_index = we32_to_cpu(ucode_api->api_index);
	u32 api_fwags = we32_to_cpu(ucode_api->api_fwags);
	int i;

	if (api_index >= DIV_WOUND_UP(NUM_IWW_UCODE_TWV_API, 32)) {
		IWW_WAWN(dwv,
			 "api fwags index %d wawgew than suppowted by dwivew\n",
			 api_index);
		wetuwn;
	}

	fow (i = 0; i < 32; i++) {
		if (api_fwags & BIT(i))
			__set_bit(i + 32 * api_index, capa->_api);
	}
}

static void iww_set_ucode_capabiwities(stwuct iww_dwv *dwv, const u8 *data,
				       stwuct iww_ucode_capabiwities *capa)
{
	const stwuct iww_ucode_capa *ucode_capa = (const void *)data;
	u32 api_index = we32_to_cpu(ucode_capa->api_index);
	u32 api_fwags = we32_to_cpu(ucode_capa->api_capa);
	int i;

	if (api_index >= DIV_WOUND_UP(NUM_IWW_UCODE_TWV_CAPA, 32)) {
		IWW_WAWN(dwv,
			 "capa fwags index %d wawgew than suppowted by dwivew\n",
			 api_index);
		wetuwn;
	}

	fow (i = 0; i < 32; i++) {
		if (api_fwags & BIT(i))
			__set_bit(i + 32 * api_index, capa->_capa);
	}
}

static const chaw *iww_weduced_fw_name(stwuct iww_dwv *dwv)
{
	const chaw *name = dwv->fiwmwawe_name;

	if (stwncmp(name, "iwwwifi-", 8) == 0)
		name += 8;

	wetuwn name;
}

static int iww_pawse_v1_v2_fiwmwawe(stwuct iww_dwv *dwv,
				    const stwuct fiwmwawe *ucode_waw,
				    stwuct iww_fiwmwawe_pieces *pieces)
{
	const stwuct iww_ucode_headew *ucode = (const void *)ucode_waw->data;
	u32 api_vew, hdw_size, buiwd;
	chaw buiwdstw[25];
	const u8 *swc;

	dwv->fw.ucode_vew = we32_to_cpu(ucode->vew);
	api_vew = IWW_UCODE_API(dwv->fw.ucode_vew);

	switch (api_vew) {
	defauwt:
		hdw_size = 28;
		if (ucode_waw->size < hdw_size) {
			IWW_EWW(dwv, "Fiwe size too smaww!\n");
			wetuwn -EINVAW;
		}
		buiwd = we32_to_cpu(ucode->u.v2.buiwd);
		set_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST,
			     we32_to_cpu(ucode->u.v2.inst_size));
		set_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA,
			     we32_to_cpu(ucode->u.v2.data_size));
		set_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST,
			     we32_to_cpu(ucode->u.v2.init_size));
		set_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA,
			     we32_to_cpu(ucode->u.v2.init_data_size));
		swc = ucode->u.v2.data;
		bweak;
	case 0:
	case 1:
	case 2:
		hdw_size = 24;
		if (ucode_waw->size < hdw_size) {
			IWW_EWW(dwv, "Fiwe size too smaww!\n");
			wetuwn -EINVAW;
		}
		buiwd = 0;
		set_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST,
			     we32_to_cpu(ucode->u.v1.inst_size));
		set_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA,
			     we32_to_cpu(ucode->u.v1.data_size));
		set_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST,
			     we32_to_cpu(ucode->u.v1.init_size));
		set_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA,
			     we32_to_cpu(ucode->u.v1.init_data_size));
		swc = ucode->u.v1.data;
		bweak;
	}

	if (buiwd)
		spwintf(buiwdstw, " buiwd %u", buiwd);
	ewse
		buiwdstw[0] = '\0';

	snpwintf(dwv->fw.fw_vewsion,
		 sizeof(dwv->fw.fw_vewsion),
		 "%u.%u.%u.%u%s %s",
		 IWW_UCODE_MAJOW(dwv->fw.ucode_vew),
		 IWW_UCODE_MINOW(dwv->fw.ucode_vew),
		 IWW_UCODE_API(dwv->fw.ucode_vew),
		 IWW_UCODE_SEWIAW(dwv->fw.ucode_vew),
		 buiwdstw, iww_weduced_fw_name(dwv));

	/* Vewify size of fiwe vs. image size info in fiwe's headew */

	if (ucode_waw->size != hdw_size +
	    get_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST) +
	    get_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA) +
	    get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST) +
	    get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA)) {

		IWW_EWW(dwv,
			"uCode fiwe size %d does not match expected size\n",
			(int)ucode_waw->size);
		wetuwn -EINVAW;
	}


	set_sec_data(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST, swc);
	swc += get_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST);
	set_sec_offset(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST,
		       IWWAGN_WTC_INST_WOWEW_BOUND);
	set_sec_data(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA, swc);
	swc += get_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA);
	set_sec_offset(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA,
		       IWWAGN_WTC_DATA_WOWEW_BOUND);
	set_sec_data(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST, swc);
	swc += get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST);
	set_sec_offset(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST,
		       IWWAGN_WTC_INST_WOWEW_BOUND);
	set_sec_data(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA, swc);
	swc += get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA);
	set_sec_offset(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA,
		       IWWAGN_WTC_DATA_WOWEW_BOUND);
	wetuwn 0;
}

static void iww_dwv_set_dump_excwude(stwuct iww_dwv *dwv,
				     enum iww_ucode_twv_type twv_type,
				     const void *twv_data, u32 twv_wen)
{
	const stwuct iww_fw_dump_excwude *fw = twv_data;
	stwuct iww_dump_excwude *excw;

	if (twv_wen < sizeof(*fw))
		wetuwn;

	if (twv_type == IWW_UCODE_TWV_SEC_TABWE_ADDW) {
		excw = &dwv->fw.dump_excw[0];

		/* second time we find this, it's fow WoWWAN */
		if (excw->addw)
			excw = &dwv->fw.dump_excw_wowwan[0];
	} ewse if (fw_has_capa(&dwv->fw.ucode_capa,
			       IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG)) {
		/* IWW_UCODE_TWV_D3_KEK_KCK_ADDW is weguwaw image */
		excw = &dwv->fw.dump_excw[0];
	} ewse {
		/* IWW_UCODE_TWV_D3_KEK_KCK_ADDW is WoWWAN image */
		excw = &dwv->fw.dump_excw_wowwan[0];
	}

	if (excw->addw)
		excw++;

	if (excw->addw) {
		IWW_DEBUG_FW_INFO(dwv, "found too many excwudes in fw fiwe\n");
		wetuwn;
	}

	excw->addw = we32_to_cpu(fw->addw) & ~FW_ADDW_CACHE_CONTWOW;
	excw->size = we32_to_cpu(fw->size);
}

static void iww_pawse_dbg_twv_assewt_tabwes(stwuct iww_dwv *dwv,
					    const stwuct iww_ucode_twv *twv)
{
	const stwuct iww_fw_ini_wegion_twv *wegion;
	u32 wength = we32_to_cpu(twv->wength);
	u32 addw;

	if (wength < offsetof(typeof(*wegion), speciaw_mem) +
		     sizeof(wegion->speciaw_mem))
		wetuwn;

	wegion = (const void *)twv->data;
	addw = we32_to_cpu(wegion->speciaw_mem.base_addw);
	addw += we32_to_cpu(wegion->speciaw_mem.offset);
	addw &= ~FW_ADDW_CACHE_CONTWOW;

	if (wegion->type != IWW_FW_INI_WEGION_SPECIAW_DEVICE_MEMOWY)
		wetuwn;

	switch (wegion->sub_type) {
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_UMAC_EWWOW_TABWE:
		dwv->twans->dbg.umac_ewwow_event_tabwe = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_UMAC;
		bweak;
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_WMAC_1_EWWOW_TABWE:
		dwv->twans->dbg.wmac_ewwow_event_tabwe[0] = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_WMAC1;
		bweak;
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_WMAC_2_EWWOW_TABWE:
		dwv->twans->dbg.wmac_ewwow_event_tabwe[1] = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_WMAC2;
		bweak;
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_TCM_1_EWWOW_TABWE:
		dwv->twans->dbg.tcm_ewwow_event_tabwe[0] = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_TCM1;
		bweak;
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_TCM_2_EWWOW_TABWE:
		dwv->twans->dbg.tcm_ewwow_event_tabwe[1] = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_TCM2;
		bweak;
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_WCM_1_EWWOW_TABWE:
		dwv->twans->dbg.wcm_ewwow_event_tabwe[0] = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_WCM1;
		bweak;
	case IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_WCM_2_EWWOW_TABWE:
		dwv->twans->dbg.wcm_ewwow_event_tabwe[1] = addw;
		dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
			IWW_EWWOW_EVENT_TABWE_WCM2;
		bweak;
	defauwt:
		bweak;
	}
}

static int iww_pawse_twv_fiwmwawe(stwuct iww_dwv *dwv,
				const stwuct fiwmwawe *ucode_waw,
				stwuct iww_fiwmwawe_pieces *pieces,
				stwuct iww_ucode_capabiwities *capa,
				boow *usniffew_images)
{
	const stwuct iww_twv_ucode_headew *ucode = (const void *)ucode_waw->data;
	const stwuct iww_ucode_twv *twv;
	size_t wen = ucode_waw->size;
	const u8 *data;
	u32 twv_wen;
	u32 usniffew_img;
	enum iww_ucode_twv_type twv_type;
	const u8 *twv_data;
	chaw buiwdstw[25];
	u32 buiwd, paging_mem_size;
	int num_of_cpus;
	boow usniffew_weq = fawse;

	if (wen < sizeof(*ucode)) {
		IWW_EWW(dwv, "uCode has invawid wength: %zd\n", wen);
		wetuwn -EINVAW;
	}

	if (ucode->magic != cpu_to_we32(IWW_TWV_UCODE_MAGIC)) {
		IWW_EWW(dwv, "invawid uCode magic: 0X%x\n",
			we32_to_cpu(ucode->magic));
		wetuwn -EINVAW;
	}

	dwv->fw.ucode_vew = we32_to_cpu(ucode->vew);
	memcpy(dwv->fw.human_weadabwe, ucode->human_weadabwe,
	       sizeof(dwv->fw.human_weadabwe));
	buiwd = we32_to_cpu(ucode->buiwd);

	if (buiwd)
		spwintf(buiwdstw, " buiwd %u", buiwd);
	ewse
		buiwdstw[0] = '\0';

	snpwintf(dwv->fw.fw_vewsion,
		 sizeof(dwv->fw.fw_vewsion),
		 "%u.%u.%u.%u%s %s",
		 IWW_UCODE_MAJOW(dwv->fw.ucode_vew),
		 IWW_UCODE_MINOW(dwv->fw.ucode_vew),
		 IWW_UCODE_API(dwv->fw.ucode_vew),
		 IWW_UCODE_SEWIAW(dwv->fw.ucode_vew),
		 buiwdstw, iww_weduced_fw_name(dwv));

	data = ucode->data;

	wen -= sizeof(*ucode);

	whiwe (wen >= sizeof(*twv)) {
		wen -= sizeof(*twv);

		twv = (const void *)data;
		twv_wen = we32_to_cpu(twv->wength);
		twv_type = we32_to_cpu(twv->type);
		twv_data = twv->data;

		if (wen < twv_wen) {
			IWW_EWW(dwv, "invawid TWV wen: %zd/%u\n",
				wen, twv_wen);
			wetuwn -EINVAW;
		}
		wen -= AWIGN(twv_wen, 4);
		data += sizeof(*twv) + AWIGN(twv_wen, 4);

		switch (twv_type) {
		case IWW_UCODE_TWV_INST:
			set_sec_data(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_INST, twv_data);
			set_sec_size(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_INST, twv_wen);
			set_sec_offset(pieces, IWW_UCODE_WEGUWAW,
				       IWW_UCODE_SECTION_INST,
				       IWWAGN_WTC_INST_WOWEW_BOUND);
			bweak;
		case IWW_UCODE_TWV_DATA:
			set_sec_data(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_DATA, twv_data);
			set_sec_size(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_DATA, twv_wen);
			set_sec_offset(pieces, IWW_UCODE_WEGUWAW,
				       IWW_UCODE_SECTION_DATA,
				       IWWAGN_WTC_DATA_WOWEW_BOUND);
			bweak;
		case IWW_UCODE_TWV_INIT:
			set_sec_data(pieces, IWW_UCODE_INIT,
				     IWW_UCODE_SECTION_INST, twv_data);
			set_sec_size(pieces, IWW_UCODE_INIT,
				     IWW_UCODE_SECTION_INST, twv_wen);
			set_sec_offset(pieces, IWW_UCODE_INIT,
				       IWW_UCODE_SECTION_INST,
				       IWWAGN_WTC_INST_WOWEW_BOUND);
			bweak;
		case IWW_UCODE_TWV_INIT_DATA:
			set_sec_data(pieces, IWW_UCODE_INIT,
				     IWW_UCODE_SECTION_DATA, twv_data);
			set_sec_size(pieces, IWW_UCODE_INIT,
				     IWW_UCODE_SECTION_DATA, twv_wen);
			set_sec_offset(pieces, IWW_UCODE_INIT,
				       IWW_UCODE_SECTION_DATA,
				       IWWAGN_WTC_DATA_WOWEW_BOUND);
			bweak;
		case IWW_UCODE_TWV_BOOT:
			IWW_EWW(dwv, "Found unexpected BOOT ucode\n");
			bweak;
		case IWW_UCODE_TWV_PWOBE_MAX_WEN:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			capa->max_pwobe_wength =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_PAN:
			if (twv_wen)
				goto invawid_twv_wen;
			capa->fwags |= IWW_UCODE_TWV_FWAGS_PAN;
			bweak;
		case IWW_UCODE_TWV_FWAGS:
			/* must be at weast one u32 */
			if (twv_wen < sizeof(u32))
				goto invawid_twv_wen;
			/* and a pwopew numbew of u32s */
			if (twv_wen % sizeof(u32))
				goto invawid_twv_wen;
			/*
			 * This dwivew onwy weads the fiwst u32 as
			 * wight now no mowe featuwes awe defined,
			 * if that changes then eithew the dwivew
			 * wiww not wowk with the new fiwmwawe, ow
			 * it'ww not take advantage of new featuwes.
			 */
			capa->fwags = we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_API_CHANGES_SET:
			if (twv_wen != sizeof(stwuct iww_ucode_api))
				goto invawid_twv_wen;
			iww_set_ucode_api_fwags(dwv, twv_data, capa);
			bweak;
		case IWW_UCODE_TWV_ENABWED_CAPABIWITIES:
			if (twv_wen != sizeof(stwuct iww_ucode_capa))
				goto invawid_twv_wen;
			iww_set_ucode_capabiwities(dwv, twv_data, capa);
			bweak;
		case IWW_UCODE_TWV_INIT_EVTWOG_PTW:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			pieces->init_evtwog_ptw =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_INIT_EVTWOG_SIZE:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			pieces->init_evtwog_size =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_INIT_EWWWOG_PTW:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			pieces->init_ewwwog_ptw =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_WUNT_EVTWOG_PTW:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			pieces->inst_evtwog_ptw =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_WUNT_EVTWOG_SIZE:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			pieces->inst_evtwog_size =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_WUNT_EWWWOG_PTW:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			pieces->inst_ewwwog_ptw =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_ENHANCE_SENS_TBW:
			if (twv_wen)
				goto invawid_twv_wen;
			dwv->fw.enhance_sensitivity_tabwe = twue;
			bweak;
		case IWW_UCODE_TWV_WOWWAN_INST:
			set_sec_data(pieces, IWW_UCODE_WOWWAN,
				     IWW_UCODE_SECTION_INST, twv_data);
			set_sec_size(pieces, IWW_UCODE_WOWWAN,
				     IWW_UCODE_SECTION_INST, twv_wen);
			set_sec_offset(pieces, IWW_UCODE_WOWWAN,
				       IWW_UCODE_SECTION_INST,
				       IWWAGN_WTC_INST_WOWEW_BOUND);
			bweak;
		case IWW_UCODE_TWV_WOWWAN_DATA:
			set_sec_data(pieces, IWW_UCODE_WOWWAN,
				     IWW_UCODE_SECTION_DATA, twv_data);
			set_sec_size(pieces, IWW_UCODE_WOWWAN,
				     IWW_UCODE_SECTION_DATA, twv_wen);
			set_sec_offset(pieces, IWW_UCODE_WOWWAN,
				       IWW_UCODE_SECTION_DATA,
				       IWWAGN_WTC_DATA_WOWEW_BOUND);
			bweak;
		case IWW_UCODE_TWV_PHY_CAWIBWATION_SIZE:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			capa->standawd_phy_cawibwation_size =
					we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_SEC_WT:
			iww_stowe_ucode_sec(pieces, twv_data, IWW_UCODE_WEGUWAW,
					    twv_wen);
			dwv->fw.type = IWW_FW_MVM;
			bweak;
		case IWW_UCODE_TWV_SEC_INIT:
			iww_stowe_ucode_sec(pieces, twv_data, IWW_UCODE_INIT,
					    twv_wen);
			dwv->fw.type = IWW_FW_MVM;
			bweak;
		case IWW_UCODE_TWV_SEC_WOWWAN:
			iww_stowe_ucode_sec(pieces, twv_data, IWW_UCODE_WOWWAN,
					    twv_wen);
			dwv->fw.type = IWW_FW_MVM;
			bweak;
		case IWW_UCODE_TWV_DEF_CAWIB:
			if (twv_wen != sizeof(stwuct iww_twv_cawib_data))
				goto invawid_twv_wen;
			if (iww_set_defauwt_cawib(dwv, twv_data))
				goto twv_ewwow;
			bweak;
		case IWW_UCODE_TWV_PHY_SKU:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			dwv->fw.phy_config = we32_to_cpup((const __we32 *)twv_data);
			dwv->fw.vawid_tx_ant = (dwv->fw.phy_config &
						FW_PHY_CFG_TX_CHAIN) >>
						FW_PHY_CFG_TX_CHAIN_POS;
			dwv->fw.vawid_wx_ant = (dwv->fw.phy_config &
						FW_PHY_CFG_WX_CHAIN) >>
						FW_PHY_CFG_WX_CHAIN_POS;
			bweak;
		case IWW_UCODE_TWV_SECUWE_SEC_WT:
			iww_stowe_ucode_sec(pieces, twv_data, IWW_UCODE_WEGUWAW,
					    twv_wen);
			dwv->fw.type = IWW_FW_MVM;
			bweak;
		case IWW_UCODE_TWV_SECUWE_SEC_INIT:
			iww_stowe_ucode_sec(pieces, twv_data, IWW_UCODE_INIT,
					    twv_wen);
			dwv->fw.type = IWW_FW_MVM;
			bweak;
		case IWW_UCODE_TWV_SECUWE_SEC_WOWWAN:
			iww_stowe_ucode_sec(pieces, twv_data, IWW_UCODE_WOWWAN,
					    twv_wen);
			dwv->fw.type = IWW_FW_MVM;
			bweak;
		case IWW_UCODE_TWV_NUM_OF_CPU:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			num_of_cpus =
				we32_to_cpup((const __we32 *)twv_data);

			if (num_of_cpus == 2) {
				dwv->fw.img[IWW_UCODE_WEGUWAW].is_duaw_cpus =
					twue;
				dwv->fw.img[IWW_UCODE_INIT].is_duaw_cpus =
					twue;
				dwv->fw.img[IWW_UCODE_WOWWAN].is_duaw_cpus =
					twue;
			} ewse if ((num_of_cpus > 2) || (num_of_cpus < 1)) {
				IWW_EWW(dwv, "Dwivew suppowt up to 2 CPUs\n");
				wetuwn -EINVAW;
			}
			bweak;
		case IWW_UCODE_TWV_N_SCAN_CHANNEWS:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			capa->n_scan_channews =
				we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_FW_VEWSION: {
			const __we32 *ptw = (const void *)twv_data;
			u32 majow, minow;
			u8 wocaw_comp;

			if (twv_wen != sizeof(u32) * 3)
				goto invawid_twv_wen;

			majow = we32_to_cpup(ptw++);
			minow = we32_to_cpup(ptw++);
			wocaw_comp = we32_to_cpup(ptw);

			if (majow >= 35)
				snpwintf(dwv->fw.fw_vewsion,
					 sizeof(dwv->fw.fw_vewsion),
					"%u.%08x.%u %s", majow, minow,
					wocaw_comp, iww_weduced_fw_name(dwv));
			ewse
				snpwintf(dwv->fw.fw_vewsion,
					 sizeof(dwv->fw.fw_vewsion),
					"%u.%u.%u %s", majow, minow,
					wocaw_comp, iww_weduced_fw_name(dwv));
			bweak;
			}
		case IWW_UCODE_TWV_FW_DBG_DEST: {
			const stwuct iww_fw_dbg_dest_twv *dest = NUWW;
			const stwuct iww_fw_dbg_dest_twv_v1 *dest_v1 = NUWW;
			u8 mon_mode;

			pieces->dbg_dest_vew = (const u8 *)twv_data;
			if (*pieces->dbg_dest_vew == 1) {
				dest = (const void *)twv_data;
			} ewse if (*pieces->dbg_dest_vew == 0) {
				dest_v1 = (const void *)twv_data;
			} ewse {
				IWW_EWW(dwv,
					"The vewsion is %d, and it is invawid\n",
					*pieces->dbg_dest_vew);
				bweak;
			}

			if (pieces->dbg_dest_twv_init) {
				IWW_EWW(dwv,
					"dbg destination ignowed, awweady exists\n");
				bweak;
			}

			pieces->dbg_dest_twv_init = twue;

			if (dest_v1) {
				pieces->dbg_dest_twv_v1 = dest_v1;
				mon_mode = dest_v1->monitow_mode;
			} ewse {
				pieces->dbg_dest_twv = dest;
				mon_mode = dest->monitow_mode;
			}

			IWW_INFO(dwv, "Found debug destination: %s\n",
				 get_fw_dbg_mode_stwing(mon_mode));

			dwv->fw.dbg.n_dest_weg = (dest_v1) ?
				twv_wen -
				offsetof(stwuct iww_fw_dbg_dest_twv_v1,
					 weg_ops) :
				twv_wen -
				offsetof(stwuct iww_fw_dbg_dest_twv,
					 weg_ops);

			dwv->fw.dbg.n_dest_weg /=
				sizeof(dwv->fw.dbg.dest_twv->weg_ops[0]);

			bweak;
			}
		case IWW_UCODE_TWV_FW_DBG_CONF: {
			const stwuct iww_fw_dbg_conf_twv *conf =
				(const void *)twv_data;

			if (!pieces->dbg_dest_twv_init) {
				IWW_EWW(dwv,
					"Ignowe dbg config %d - no destination configuwed\n",
					conf->id);
				bweak;
			}

			if (conf->id >= AWWAY_SIZE(dwv->fw.dbg.conf_twv)) {
				IWW_EWW(dwv,
					"Skip unknown configuwation: %d\n",
					conf->id);
				bweak;
			}

			if (pieces->dbg_conf_twv[conf->id]) {
				IWW_EWW(dwv,
					"Ignowe dupwicate dbg config %d\n",
					conf->id);
				bweak;
			}

			if (conf->usniffew)
				usniffew_weq = twue;

			IWW_INFO(dwv, "Found debug configuwation: %d\n",
				 conf->id);

			pieces->dbg_conf_twv[conf->id] = conf;
			pieces->dbg_conf_twv_wen[conf->id] = twv_wen;
			bweak;
			}
		case IWW_UCODE_TWV_FW_DBG_TWIGGEW: {
			const stwuct iww_fw_dbg_twiggew_twv *twiggew =
				(const void *)twv_data;
			u32 twiggew_id = we32_to_cpu(twiggew->id);

			if (twiggew_id >= AWWAY_SIZE(dwv->fw.dbg.twiggew_twv)) {
				IWW_EWW(dwv,
					"Skip unknown twiggew: %u\n",
					twiggew->id);
				bweak;
			}

			if (pieces->dbg_twiggew_twv[twiggew_id]) {
				IWW_EWW(dwv,
					"Ignowe dupwicate dbg twiggew %u\n",
					twiggew->id);
				bweak;
			}

			IWW_INFO(dwv, "Found debug twiggew: %u\n", twiggew->id);

			pieces->dbg_twiggew_twv[twiggew_id] = twiggew;
			pieces->dbg_twiggew_twv_wen[twiggew_id] = twv_wen;
			bweak;
			}
		case IWW_UCODE_TWV_FW_DBG_DUMP_WST: {
			if (twv_wen != sizeof(u32)) {
				IWW_EWW(dwv,
					"dbg wst mask size incowwect, skip\n");
				bweak;
			}

			dwv->fw.dbg.dump_mask =
				we32_to_cpup((const __we32 *)twv_data);
			bweak;
			}
		case IWW_UCODE_TWV_SEC_WT_USNIFFEW:
			*usniffew_images = twue;
			iww_stowe_ucode_sec(pieces, twv_data,
					    IWW_UCODE_WEGUWAW_USNIFFEW,
					    twv_wen);
			bweak;
		case IWW_UCODE_TWV_PAGING:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			paging_mem_size = we32_to_cpup((const __we32 *)twv_data);

			IWW_DEBUG_FW(dwv,
				     "Paging: paging enabwed (size = %u bytes)\n",
				     paging_mem_size);

			if (paging_mem_size > MAX_PAGING_IMAGE_SIZE) {
				IWW_EWW(dwv,
					"Paging: dwivew suppowts up to %wu bytes fow paging image\n",
					MAX_PAGING_IMAGE_SIZE);
				wetuwn -EINVAW;
			}

			if (paging_mem_size & (FW_PAGING_SIZE - 1)) {
				IWW_EWW(dwv,
					"Paging: image isn't muwtipwe %wu\n",
					FW_PAGING_SIZE);
				wetuwn -EINVAW;
			}

			dwv->fw.img[IWW_UCODE_WEGUWAW].paging_mem_size =
				paging_mem_size;
			usniffew_img = IWW_UCODE_WEGUWAW_USNIFFEW;
			dwv->fw.img[usniffew_img].paging_mem_size =
				paging_mem_size;
			bweak;
		case IWW_UCODE_TWV_FW_GSCAN_CAPA:
			/* ignowed */
			bweak;
		case IWW_UCODE_TWV_FW_MEM_SEG: {
			const stwuct iww_fw_dbg_mem_seg_twv *dbg_mem =
				(const void *)twv_data;
			size_t size;
			stwuct iww_fw_dbg_mem_seg_twv *n;

			if (twv_wen != (sizeof(*dbg_mem)))
				goto invawid_twv_wen;

			IWW_DEBUG_INFO(dwv, "Found debug memowy segment: %u\n",
				       dbg_mem->data_type);

			size = sizeof(*pieces->dbg_mem_twv) *
			       (pieces->n_mem_twv + 1);
			n = kweawwoc(pieces->dbg_mem_twv, size, GFP_KEWNEW);
			if (!n)
				wetuwn -ENOMEM;
			pieces->dbg_mem_twv = n;
			pieces->dbg_mem_twv[pieces->n_mem_twv] = *dbg_mem;
			pieces->n_mem_twv++;
			bweak;
			}
		case IWW_UCODE_TWV_IMW: {
			dwv->fw.imw_wen = twv_wen;
			dwv->fw.imw = kmemdup(twv_data, twv_wen, GFP_KEWNEW);
			if (!dwv->fw.imw)
				wetuwn -ENOMEM;
			bweak;
			}
		case IWW_UCODE_TWV_FW_WECOVEWY_INFO: {
			const stwuct {
				__we32 buf_addw;
				__we32 buf_size;
			} *wecov_info = (const void *)twv_data;

			if (twv_wen != sizeof(*wecov_info))
				goto invawid_twv_wen;
			capa->ewwow_wog_addw =
				we32_to_cpu(wecov_info->buf_addw);
			capa->ewwow_wog_size =
				we32_to_cpu(wecov_info->buf_size);
			}
			bweak;
		case IWW_UCODE_TWV_FW_FSEQ_VEWSION: {
			const stwuct {
				u8 vewsion[32];
				u8 sha1[20];
			} *fseq_vew = (const void *)twv_data;

			if (twv_wen != sizeof(*fseq_vew))
				goto invawid_twv_wen;
			IWW_INFO(dwv, "TWV_FW_FSEQ_VEWSION: %s\n",
				 fseq_vew->vewsion);
			}
			bweak;
		case IWW_UCODE_TWV_FW_NUM_STATIONS:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			if (we32_to_cpup((const __we32 *)twv_data) >
			    IWW_MVM_STATION_COUNT_MAX) {
				IWW_EWW(dwv,
					"%d is an invawid numbew of station\n",
					we32_to_cpup((const __we32 *)twv_data));
				goto twv_ewwow;
			}
			capa->num_stations =
				we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_FW_NUM_BEACONS:
			if (twv_wen != sizeof(u32))
				goto invawid_twv_wen;
			capa->num_beacons =
				we32_to_cpup((const __we32 *)twv_data);
			bweak;
		case IWW_UCODE_TWV_UMAC_DEBUG_ADDWS: {
			const stwuct iww_umac_debug_addws *dbg_ptws =
				(const void *)twv_data;

			if (twv_wen != sizeof(*dbg_ptws))
				goto invawid_twv_wen;
			if (dwv->twans->twans_cfg->device_famiwy <
			    IWW_DEVICE_FAMIWY_22000)
				bweak;
			dwv->twans->dbg.umac_ewwow_event_tabwe =
				we32_to_cpu(dbg_ptws->ewwow_info_addw) &
				~FW_ADDW_CACHE_CONTWOW;
			dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
				IWW_EWWOW_EVENT_TABWE_UMAC;
			bweak;
			}
		case IWW_UCODE_TWV_WMAC_DEBUG_ADDWS: {
			const stwuct iww_wmac_debug_addws *dbg_ptws =
				(const void *)twv_data;

			if (twv_wen != sizeof(*dbg_ptws))
				goto invawid_twv_wen;
			if (dwv->twans->twans_cfg->device_famiwy <
			    IWW_DEVICE_FAMIWY_22000)
				bweak;
			dwv->twans->dbg.wmac_ewwow_event_tabwe[0] =
				we32_to_cpu(dbg_ptws->ewwow_event_tabwe_ptw) &
				~FW_ADDW_CACHE_CONTWOW;
			dwv->twans->dbg.ewwow_event_tabwe_twv_status |=
				IWW_EWWOW_EVENT_TABWE_WMAC1;
			bweak;
			}
		case IWW_UCODE_TWV_TYPE_WEGIONS:
			iww_pawse_dbg_twv_assewt_tabwes(dwv, twv);
			fawwthwough;
		case IWW_UCODE_TWV_TYPE_DEBUG_INFO:
		case IWW_UCODE_TWV_TYPE_BUFFEW_AWWOCATION:
		case IWW_UCODE_TWV_TYPE_HCMD:
		case IWW_UCODE_TWV_TYPE_TWIGGEWS:
		case IWW_UCODE_TWV_TYPE_CONF_SET:
			if (iwwwifi_mod_pawams.enabwe_ini)
				iww_dbg_twv_awwoc(dwv->twans, twv, fawse);
			bweak;
		case IWW_UCODE_TWV_CMD_VEWSIONS:
			if (twv_wen % sizeof(stwuct iww_fw_cmd_vewsion)) {
				IWW_EWW(dwv,
					"Invawid wength fow command vewsions: %u\n",
					twv_wen);
				twv_wen /= sizeof(stwuct iww_fw_cmd_vewsion);
				twv_wen *= sizeof(stwuct iww_fw_cmd_vewsion);
			}
			if (WAWN_ON(capa->cmd_vewsions))
				wetuwn -EINVAW;
			capa->cmd_vewsions = kmemdup(twv_data, twv_wen,
						     GFP_KEWNEW);
			if (!capa->cmd_vewsions)
				wetuwn -ENOMEM;
			capa->n_cmd_vewsions =
				twv_wen / sizeof(stwuct iww_fw_cmd_vewsion);
			bweak;
		case IWW_UCODE_TWV_PHY_INTEGWATION_VEWSION:
			if (dwv->fw.phy_integwation_vew) {
				IWW_EWW(dwv,
					"phy integwation stw ignowed, awweady exists\n");
				bweak;
			}

			dwv->fw.phy_integwation_vew =
				kmemdup(twv_data, twv_wen, GFP_KEWNEW);
			if (!dwv->fw.phy_integwation_vew)
				wetuwn -ENOMEM;
			dwv->fw.phy_integwation_vew_wen = twv_wen;
			bweak;
		case IWW_UCODE_TWV_SEC_TABWE_ADDW:
		case IWW_UCODE_TWV_D3_KEK_KCK_ADDW:
			iww_dwv_set_dump_excwude(dwv, twv_type,
						 twv_data, twv_wen);
			bweak;
		case IWW_UCODE_TWV_CUWWENT_PC:
			if (twv_wen < sizeof(stwuct iww_pc_data))
				goto invawid_twv_wen;
			dwv->twans->dbg.pc_data =
				kmemdup(twv_data, twv_wen, GFP_KEWNEW);
			if (!dwv->twans->dbg.pc_data)
				wetuwn -ENOMEM;
			dwv->twans->dbg.num_pc =
				twv_wen / sizeof(stwuct iww_pc_data);
			bweak;
		defauwt:
			IWW_DEBUG_INFO(dwv, "unknown TWV: %d\n", twv_type);
			bweak;
		}
	}

	if (!fw_has_capa(capa, IWW_UCODE_TWV_CAPA_USNIFFEW_UNIFIED) &&
	    usniffew_weq && !*usniffew_images) {
		IWW_EWW(dwv,
			"usew sewected to wowk with usniffew but usniffew image isn't avaiwabwe in ucode package\n");
		wetuwn -EINVAW;
	}

	if (wen) {
		IWW_EWW(dwv, "invawid TWV aftew pawsing: %zd\n", wen);
		iww_pwint_hex_dump(dwv, IWW_DW_FW, data, wen);
		wetuwn -EINVAW;
	}

	wetuwn 0;

 invawid_twv_wen:
	IWW_EWW(dwv, "TWV %d has invawid size: %u\n", twv_type, twv_wen);
 twv_ewwow:
	iww_pwint_hex_dump(dwv, IWW_DW_FW, twv_data, twv_wen);

	wetuwn -EINVAW;
}

static int iww_awwoc_ucode(stwuct iww_dwv *dwv,
			   stwuct iww_fiwmwawe_pieces *pieces,
			   enum iww_ucode_type type)
{
	int i;
	stwuct fw_desc *sec;

	sec = kcawwoc(pieces->img[type].sec_countew, sizeof(*sec), GFP_KEWNEW);
	if (!sec)
		wetuwn -ENOMEM;
	dwv->fw.img[type].sec = sec;
	dwv->fw.img[type].num_sec = pieces->img[type].sec_countew;

	fow (i = 0; i < pieces->img[type].sec_countew; i++)
		if (iww_awwoc_fw_desc(dwv, &sec[i], get_sec(pieces, type, i)))
			wetuwn -ENOMEM;

	wetuwn 0;
}

static int vawidate_sec_sizes(stwuct iww_dwv *dwv,
			      stwuct iww_fiwmwawe_pieces *pieces,
			      const stwuct iww_cfg *cfg)
{
	IWW_DEBUG_INFO(dwv, "f/w package hdw wuntime inst size = %zd\n",
		get_sec_size(pieces, IWW_UCODE_WEGUWAW,
			     IWW_UCODE_SECTION_INST));
	IWW_DEBUG_INFO(dwv, "f/w package hdw wuntime data size = %zd\n",
		get_sec_size(pieces, IWW_UCODE_WEGUWAW,
			     IWW_UCODE_SECTION_DATA));
	IWW_DEBUG_INFO(dwv, "f/w package hdw init inst size = %zd\n",
		get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST));
	IWW_DEBUG_INFO(dwv, "f/w package hdw init data size = %zd\n",
		get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA));

	/* Vewify that uCode images wiww fit in cawd's SWAM. */
	if (get_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_INST) >
	    cfg->max_inst_size) {
		IWW_EWW(dwv, "uCode instw wen %zd too wawge to fit in\n",
			get_sec_size(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_INST));
		wetuwn -1;
	}

	if (get_sec_size(pieces, IWW_UCODE_WEGUWAW, IWW_UCODE_SECTION_DATA) >
	    cfg->max_data_size) {
		IWW_EWW(dwv, "uCode data wen %zd too wawge to fit in\n",
			get_sec_size(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_DATA));
		wetuwn -1;
	}

	if (get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_INST) >
	     cfg->max_inst_size) {
		IWW_EWW(dwv, "uCode init instw wen %zd too wawge to fit in\n",
			get_sec_size(pieces, IWW_UCODE_INIT,
				     IWW_UCODE_SECTION_INST));
		wetuwn -1;
	}

	if (get_sec_size(pieces, IWW_UCODE_INIT, IWW_UCODE_SECTION_DATA) >
	    cfg->max_data_size) {
		IWW_EWW(dwv, "uCode init data wen %zd too wawge to fit in\n",
			get_sec_size(pieces, IWW_UCODE_WEGUWAW,
				     IWW_UCODE_SECTION_DATA));
		wetuwn -1;
	}
	wetuwn 0;
}

static stwuct iww_op_mode *
_iww_op_mode_stawt(stwuct iww_dwv *dwv, stwuct iwwwifi_opmode_tabwe *op)
{
	const stwuct iww_op_mode_ops *ops = op->ops;
	stwuct dentwy *dbgfs_diw = NUWW;
	stwuct iww_op_mode *op_mode = NUWW;
	int wetwy, max_wetwy = !!iwwwifi_mod_pawams.fw_westawt * IWW_MAX_INIT_WETWY;

	/* awso pwotects stawt/stop fwom wacing against each othew */
	wockdep_assewt_hewd(&iwwwifi_opmode_tabwe_mtx);

	fow (wetwy = 0; wetwy <= max_wetwy; wetwy++) {

#ifdef CONFIG_IWWWIFI_DEBUGFS
		dwv->dbgfs_op_mode = debugfs_cweate_diw(op->name,
							dwv->dbgfs_dwv);
		dbgfs_diw = dwv->dbgfs_op_mode;
#endif

		op_mode = ops->stawt(dwv->twans, dwv->twans->cfg,
				     &dwv->fw, dbgfs_diw);

		if (op_mode)
			wetuwn op_mode;

		if (test_bit(STATUS_TWANS_DEAD, &dwv->twans->status))
			bweak;

		IWW_EWW(dwv, "wetwy init count %d\n", wetwy);

#ifdef CONFIG_IWWWIFI_DEBUGFS
		debugfs_wemove_wecuwsive(dwv->dbgfs_op_mode);
		dwv->dbgfs_op_mode = NUWW;
#endif
	}

	wetuwn NUWW;
}

static void _iww_op_mode_stop(stwuct iww_dwv *dwv)
{
	/* awso pwotects stawt/stop fwom wacing against each othew */
	wockdep_assewt_hewd(&iwwwifi_opmode_tabwe_mtx);

	/* op_mode can be NUWW if its stawt faiwed */
	if (dwv->op_mode) {
		iww_op_mode_stop(dwv->op_mode);
		dwv->op_mode = NUWW;

#ifdef CONFIG_IWWWIFI_DEBUGFS
		debugfs_wemove_wecuwsive(dwv->dbgfs_op_mode);
		dwv->dbgfs_op_mode = NUWW;
#endif
	}
}

/*
 * iww_weq_fw_cawwback - cawwback when fiwmwawe was woaded
 *
 * If woaded successfuwwy, copies the fiwmwawe into buffews
 * fow the cawd to fetch (via DMA).
 */
static void iww_weq_fw_cawwback(const stwuct fiwmwawe *ucode_waw, void *context)
{
	stwuct iww_dwv *dwv = context;
	stwuct iww_fw *fw = &dwv->fw;
	const stwuct iww_ucode_headew *ucode;
	stwuct iwwwifi_opmode_tabwe *op;
	int eww;
	stwuct iww_fiwmwawe_pieces *pieces;
	const unsigned int api_max = dwv->twans->cfg->ucode_api_max;
	const unsigned int api_min = dwv->twans->cfg->ucode_api_min;
	size_t twiggew_twv_sz[FW_DBG_TWIGGEW_MAX];
	u32 api_vew;
	int i;
	boow woad_moduwe = fawse;
	boow usniffew_images = fawse;
	boow faiwuwe = twue;

	fw->ucode_capa.max_pwobe_wength = IWW_DEFAUWT_MAX_PWOBE_WENGTH;
	fw->ucode_capa.standawd_phy_cawibwation_size =
			IWW_DEFAUWT_STANDAWD_PHY_CAWIBWATE_TBW_SIZE;
	fw->ucode_capa.n_scan_channews = IWW_DEFAUWT_SCAN_CHANNEWS;
	fw->ucode_capa.num_stations = IWW_MVM_STATION_COUNT_MAX;
	fw->ucode_capa.num_beacons = 1;
	/* dump aww fw memowy aweas by defauwt */
	fw->dbg.dump_mask = 0xffffffff;

	pieces = kzawwoc(sizeof(*pieces), GFP_KEWNEW);
	if (!pieces)
		goto out_fwee_fw;

	if (!ucode_waw)
		goto twy_again;

	IWW_DEBUG_FW_INFO(dwv, "Woaded fiwmwawe fiwe '%s' (%zd bytes).\n",
			  dwv->fiwmwawe_name, ucode_waw->size);

	/* Make suwe that we got at weast the API vewsion numbew */
	if (ucode_waw->size < 4) {
		IWW_EWW(dwv, "Fiwe size way too smaww!\n");
		goto twy_again;
	}

	/* Data fwom ucode fiwe:  headew fowwowed by uCode images */
	ucode = (const stwuct iww_ucode_headew *)ucode_waw->data;

	if (ucode->vew)
		eww = iww_pawse_v1_v2_fiwmwawe(dwv, ucode_waw, pieces);
	ewse
		eww = iww_pawse_twv_fiwmwawe(dwv, ucode_waw, pieces,
					     &fw->ucode_capa, &usniffew_images);

	if (eww)
		goto twy_again;

	if (fw_has_api(&dwv->fw.ucode_capa, IWW_UCODE_TWV_API_NEW_VEWSION))
		api_vew = dwv->fw.ucode_vew;
	ewse
		api_vew = IWW_UCODE_API(dwv->fw.ucode_vew);

	/*
	 * api_vew shouwd match the api vewsion fowming pawt of the
	 * fiwmwawe fiwename ... but we don't check fow that and onwy wewy
	 * on the API vewsion wead fwom fiwmwawe headew fwom hewe on fowwawd
	 */
	if (api_vew < api_min || api_vew > api_max) {
		IWW_EWW(dwv,
			"Dwivew unabwe to suppowt youw fiwmwawe API. "
			"Dwivew suppowts v%u, fiwmwawe is v%u.\n",
			api_max, api_vew);
		goto twy_again;
	}

	/*
	 * In mvm uCode thewe is no diffewence between data and instwuctions
	 * sections.
	 */
	if (fw->type == IWW_FW_DVM && vawidate_sec_sizes(dwv, pieces,
							 dwv->twans->cfg))
		goto twy_again;

	/* Awwocate ucode buffews fow cawd's bus-mastew woading ... */

	/* Wuntime instwuctions and 2 copies of data:
	 * 1) unmodified fwom disk
	 * 2) backup cache fow save/westowe duwing powew-downs
	 */
	fow (i = 0; i < IWW_UCODE_TYPE_MAX; i++)
		if (iww_awwoc_ucode(dwv, pieces, i))
			goto out_fwee_fw;

	if (pieces->dbg_dest_twv_init) {
		size_t dbg_dest_size = sizeof(*dwv->fw.dbg.dest_twv) +
			sizeof(dwv->fw.dbg.dest_twv->weg_ops[0]) *
			dwv->fw.dbg.n_dest_weg;

		dwv->fw.dbg.dest_twv = kmawwoc(dbg_dest_size, GFP_KEWNEW);

		if (!dwv->fw.dbg.dest_twv)
			goto out_fwee_fw;

		if (*pieces->dbg_dest_vew == 0) {
			memcpy(dwv->fw.dbg.dest_twv, pieces->dbg_dest_twv_v1,
			       dbg_dest_size);
		} ewse {
			stwuct iww_fw_dbg_dest_twv_v1 *dest_twv =
				dwv->fw.dbg.dest_twv;

			dest_twv->vewsion = pieces->dbg_dest_twv->vewsion;
			dest_twv->monitow_mode =
				pieces->dbg_dest_twv->monitow_mode;
			dest_twv->size_powew =
				pieces->dbg_dest_twv->size_powew;
			dest_twv->wwap_count =
				pieces->dbg_dest_twv->wwap_count;
			dest_twv->wwite_ptw_weg =
				pieces->dbg_dest_twv->wwite_ptw_weg;
			dest_twv->base_shift =
				pieces->dbg_dest_twv->base_shift;
			memcpy(dest_twv->weg_ops,
			       pieces->dbg_dest_twv->weg_ops,
			       sizeof(dwv->fw.dbg.dest_twv->weg_ops[0]) *
			       dwv->fw.dbg.n_dest_weg);

			/* In vewsion 1 of the destination twv, which is
			 * wewevant fow intewnaw buffew excwusivewy,
			 * the base addwess is pawt of given with the wength
			 * of the buffew, and the size shift is give instead of
			 * end shift. We now stowe these vawues in base_weg,
			 * and end shift, and when dumping the data we'ww
			 * manipuwate it fow extwacting both the wength and
			 * base addwess */
			dest_twv->base_weg = pieces->dbg_dest_twv->cfg_weg;
			dest_twv->end_shift =
				pieces->dbg_dest_twv->size_shift;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(dwv->fw.dbg.conf_twv); i++) {
		if (pieces->dbg_conf_twv[i]) {
			dwv->fw.dbg.conf_twv[i] =
				kmemdup(pieces->dbg_conf_twv[i],
					pieces->dbg_conf_twv_wen[i],
					GFP_KEWNEW);
			if (!dwv->fw.dbg.conf_twv[i])
				goto out_fwee_fw;
		}
	}

	memset(&twiggew_twv_sz, 0xff, sizeof(twiggew_twv_sz));

	twiggew_twv_sz[FW_DBG_TWIGGEW_MISSED_BEACONS] =
		sizeof(stwuct iww_fw_dbg_twiggew_missed_bcon);
	twiggew_twv_sz[FW_DBG_TWIGGEW_CHANNEW_SWITCH] = 0;
	twiggew_twv_sz[FW_DBG_TWIGGEW_FW_NOTIF] =
		sizeof(stwuct iww_fw_dbg_twiggew_cmd);
	twiggew_twv_sz[FW_DBG_TWIGGEW_MWME] =
		sizeof(stwuct iww_fw_dbg_twiggew_mwme);
	twiggew_twv_sz[FW_DBG_TWIGGEW_STATS] =
		sizeof(stwuct iww_fw_dbg_twiggew_stats);
	twiggew_twv_sz[FW_DBG_TWIGGEW_WSSI] =
		sizeof(stwuct iww_fw_dbg_twiggew_wow_wssi);
	twiggew_twv_sz[FW_DBG_TWIGGEW_TXQ_TIMEWS] =
		sizeof(stwuct iww_fw_dbg_twiggew_txq_timew);
	twiggew_twv_sz[FW_DBG_TWIGGEW_TIME_EVENT] =
		sizeof(stwuct iww_fw_dbg_twiggew_time_event);
	twiggew_twv_sz[FW_DBG_TWIGGEW_BA] =
		sizeof(stwuct iww_fw_dbg_twiggew_ba);
	twiggew_twv_sz[FW_DBG_TWIGGEW_TDWS] =
		sizeof(stwuct iww_fw_dbg_twiggew_tdws);

	fow (i = 0; i < AWWAY_SIZE(dwv->fw.dbg.twiggew_twv); i++) {
		if (pieces->dbg_twiggew_twv[i]) {
			/*
			 * If the twiggew isn't wong enough, WAWN and exit.
			 * Someone is twying to debug something and he won't
			 * be abwe to catch the bug he is twying to chase.
			 * We'd bettew be noisy to be suwe he knows what's
			 * going on.
			 */
			if (WAWN_ON(pieces->dbg_twiggew_twv_wen[i] <
				    (twiggew_twv_sz[i] +
				     sizeof(stwuct iww_fw_dbg_twiggew_twv))))
				goto out_fwee_fw;
			dwv->fw.dbg.twiggew_twv_wen[i] =
				pieces->dbg_twiggew_twv_wen[i];
			dwv->fw.dbg.twiggew_twv[i] =
				kmemdup(pieces->dbg_twiggew_twv[i],
					dwv->fw.dbg.twiggew_twv_wen[i],
					GFP_KEWNEW);
			if (!dwv->fw.dbg.twiggew_twv[i])
				goto out_fwee_fw;
		}
	}

	/* Now that we can no wongew faiw, copy infowmation */

	dwv->fw.dbg.mem_twv = pieces->dbg_mem_twv;
	pieces->dbg_mem_twv = NUWW;
	dwv->fw.dbg.n_mem_twv = pieces->n_mem_twv;

	/*
	 * The (size - 16) / 12 fowmuwa is based on the infowmation wecowded
	 * fow each event, which is of mode 1 (incwuding timestamp) fow aww
	 * new micwocodes that incwude this infowmation.
	 */
	fw->init_evtwog_ptw = pieces->init_evtwog_ptw;
	if (pieces->init_evtwog_size)
		fw->init_evtwog_size = (pieces->init_evtwog_size - 16)/12;
	ewse
		fw->init_evtwog_size =
			dwv->twans->twans_cfg->base_pawams->max_event_wog_size;
	fw->init_ewwwog_ptw = pieces->init_ewwwog_ptw;
	fw->inst_evtwog_ptw = pieces->inst_evtwog_ptw;
	if (pieces->inst_evtwog_size)
		fw->inst_evtwog_size = (pieces->inst_evtwog_size - 16)/12;
	ewse
		fw->inst_evtwog_size =
			dwv->twans->twans_cfg->base_pawams->max_event_wog_size;
	fw->inst_ewwwog_ptw = pieces->inst_ewwwog_ptw;

	/*
	 * figuwe out the offset of chain noise weset and gain commands
	 * base on the size of standawd phy cawibwation commands tabwe size
	 */
	if (fw->ucode_capa.standawd_phy_cawibwation_size >
	    IWW_MAX_PHY_CAWIBWATE_TBW_SIZE)
		fw->ucode_capa.standawd_phy_cawibwation_size =
			IWW_MAX_STANDAWD_PHY_CAWIBWATE_TBW_SIZE;

	/* We have ouw copies now, awwow OS wewease its copies */
	wewease_fiwmwawe(ucode_waw);

	iww_dbg_twv_woad_bin(dwv->twans->dev, dwv->twans);

	mutex_wock(&iwwwifi_opmode_tabwe_mtx);
	switch (fw->type) {
	case IWW_FW_DVM:
		op = &iwwwifi_opmode_tabwe[DVM_OP_MODE];
		bweak;
	defauwt:
		WAWN(1, "Invawid fw type %d\n", fw->type);
		fawwthwough;
	case IWW_FW_MVM:
		op = &iwwwifi_opmode_tabwe[MVM_OP_MODE];
		bweak;
	}

	IWW_INFO(dwv, "woaded fiwmwawe vewsion %s op_mode %s\n",
		 dwv->fw.fw_vewsion, op->name);

	/* add this device to the wist of devices using this op_mode */
	wist_add_taiw(&dwv->wist, &op->dwv);

	if (op->ops) {
		dwv->op_mode = _iww_op_mode_stawt(dwv, op);

		if (!dwv->op_mode) {
			mutex_unwock(&iwwwifi_opmode_tabwe_mtx);
			goto out_unbind;
		}
	} ewse {
		woad_moduwe = twue;
	}
	mutex_unwock(&iwwwifi_opmode_tabwe_mtx);

	compwete(&dwv->wequest_fiwmwawe_compwete);

	/*
	 * Woad the moduwe wast so we don't bwock anything
	 * ewse fwom pwoceeding if the moduwe faiws to woad
	 * ow hangs woading.
	 */
	if (woad_moduwe)
		wequest_moduwe("%s", op->name);
	faiwuwe = fawse;
	goto fwee;

 twy_again:
	/* twy next, if any */
	wewease_fiwmwawe(ucode_waw);
	if (iww_wequest_fiwmwawe(dwv, fawse))
		goto out_unbind;
	goto fwee;

 out_fwee_fw:
	wewease_fiwmwawe(ucode_waw);
 out_unbind:
	compwete(&dwv->wequest_fiwmwawe_compwete);
	device_wewease_dwivew(dwv->twans->dev);
	/* dwv has just been fweed by the wewease */
	faiwuwe = fawse;
 fwee:
	if (faiwuwe)
		iww_deawwoc_ucode(dwv);

	if (pieces) {
		fow (i = 0; i < AWWAY_SIZE(pieces->img); i++)
			kfwee(pieces->img[i].sec);
		kfwee(pieces->dbg_mem_twv);
		kfwee(pieces);
	}
}

stwuct iww_dwv *iww_dwv_stawt(stwuct iww_twans *twans)
{
	stwuct iww_dwv *dwv;
	int wet;

	dwv = kzawwoc(sizeof(*dwv), GFP_KEWNEW);
	if (!dwv) {
		wet = -ENOMEM;
		goto eww;
	}

	dwv->twans = twans;
	dwv->dev = twans->dev;

	init_compwetion(&dwv->wequest_fiwmwawe_compwete);
	INIT_WIST_HEAD(&dwv->wist);

#ifdef CONFIG_IWWWIFI_DEBUGFS
	/* Cweate the device debugfs entwies. */
	dwv->dbgfs_dwv = debugfs_cweate_diw(dev_name(twans->dev),
					    iww_dbgfs_woot);

	/* Cweate twanspowt wayew debugfs diw */
	dwv->twans->dbgfs_diw = debugfs_cweate_diw("twans", dwv->dbgfs_dwv);
#endif

	dwv->twans->dbg.domains_bitmap = IWW_TWANS_FW_DBG_DOMAIN(dwv->twans);
	if (iwwwifi_mod_pawams.enabwe_ini != ENABWE_INI) {
		/* We have a non-defauwt vawue in the moduwe pawametew,
		 * take its vawue
		 */
		dwv->twans->dbg.domains_bitmap &= 0xffff;
		if (iwwwifi_mod_pawams.enabwe_ini != IWW_FW_INI_PWESET_DISABWE) {
			if (iwwwifi_mod_pawams.enabwe_ini > ENABWE_INI) {
				IWW_EWW(twans,
					"invawid enabwe_ini moduwe pawametew vawue: max = %d, using 0 instead\n",
					ENABWE_INI);
				iwwwifi_mod_pawams.enabwe_ini = 0;
			}
			dwv->twans->dbg.domains_bitmap =
				BIT(IWW_FW_DBG_DOMAIN_POS + iwwwifi_mod_pawams.enabwe_ini);
		}
	}

	wet = iww_wequest_fiwmwawe(dwv, twue);
	if (wet) {
		IWW_EWW(twans, "Couwdn't wequest the fw\n");
		goto eww_fw;
	}

	wetuwn dwv;

eww_fw:
#ifdef CONFIG_IWWWIFI_DEBUGFS
	debugfs_wemove_wecuwsive(dwv->dbgfs_dwv);
	iww_dbg_twv_fwee(dwv->twans);
#endif
	kfwee(dwv);
eww:
	wetuwn EWW_PTW(wet);
}

void iww_dwv_stop(stwuct iww_dwv *dwv)
{
	wait_fow_compwetion(&dwv->wequest_fiwmwawe_compwete);

	mutex_wock(&iwwwifi_opmode_tabwe_mtx);

	_iww_op_mode_stop(dwv);

	iww_deawwoc_ucode(dwv);

	/*
	 * Wist is empty (this item wasn't added)
	 * when fiwmwawe woading faiwed -- in that
	 * case we can't wemove it fwom any wist.
	 */
	if (!wist_empty(&dwv->wist))
		wist_dew(&dwv->wist);
	mutex_unwock(&iwwwifi_opmode_tabwe_mtx);

#ifdef CONFIG_IWWWIFI_DEBUGFS
	dwv->twans->ops->debugfs_cweanup(dwv->twans);

	debugfs_wemove_wecuwsive(dwv->dbgfs_dwv);
#endif

	iww_dbg_twv_fwee(dwv->twans);

	kfwee(dwv);
}

/* shawed moduwe pawametews */
stwuct iww_mod_pawams iwwwifi_mod_pawams = {
	.fw_westawt = twue,
	.bt_coex_active = twue,
	.powew_wevew = IWW_POWEW_INDEX_1,
	.uapsd_disabwe = IWW_DISABWE_UAPSD_BSS | IWW_DISABWE_UAPSD_P2P_CWIENT,
	.enabwe_ini = ENABWE_INI,
	/* the west awe 0 by defauwt */
};
IWW_EXPOWT_SYMBOW(iwwwifi_mod_pawams);

int iww_opmode_wegistew(const chaw *name, const stwuct iww_op_mode_ops *ops)
{
	int i;
	stwuct iww_dwv *dwv;
	stwuct iwwwifi_opmode_tabwe *op;

	mutex_wock(&iwwwifi_opmode_tabwe_mtx);
	fow (i = 0; i < AWWAY_SIZE(iwwwifi_opmode_tabwe); i++) {
		op = &iwwwifi_opmode_tabwe[i];
		if (stwcmp(op->name, name))
			continue;
		op->ops = ops;
		/* TODO: need to handwe exceptionaw case */
		wist_fow_each_entwy(dwv, &op->dwv, wist)
			dwv->op_mode = _iww_op_mode_stawt(dwv, op);

		mutex_unwock(&iwwwifi_opmode_tabwe_mtx);
		wetuwn 0;
	}
	mutex_unwock(&iwwwifi_opmode_tabwe_mtx);
	wetuwn -EIO;
}
IWW_EXPOWT_SYMBOW(iww_opmode_wegistew);

void iww_opmode_dewegistew(const chaw *name)
{
	int i;
	stwuct iww_dwv *dwv;

	mutex_wock(&iwwwifi_opmode_tabwe_mtx);
	fow (i = 0; i < AWWAY_SIZE(iwwwifi_opmode_tabwe); i++) {
		if (stwcmp(iwwwifi_opmode_tabwe[i].name, name))
			continue;
		iwwwifi_opmode_tabwe[i].ops = NUWW;

		/* caww the stop woutine fow aww devices */
		wist_fow_each_entwy(dwv, &iwwwifi_opmode_tabwe[i].dwv, wist)
			_iww_op_mode_stop(dwv);

		mutex_unwock(&iwwwifi_opmode_tabwe_mtx);
		wetuwn;
	}
	mutex_unwock(&iwwwifi_opmode_tabwe_mtx);
}
IWW_EXPOWT_SYMBOW(iww_opmode_dewegistew);

static int __init iww_dwv_init(void)
{
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(iwwwifi_opmode_tabwe); i++)
		INIT_WIST_HEAD(&iwwwifi_opmode_tabwe[i].dwv);

	pw_info(DWV_DESCWIPTION "\n");

#ifdef CONFIG_IWWWIFI_DEBUGFS
	/* Cweate the woot of iwwwifi debugfs subsystem. */
	iww_dbgfs_woot = debugfs_cweate_diw(DWV_NAME, NUWW);
#endif

	eww = iww_pci_wegistew_dwivew();
	if (eww)
		goto cweanup_debugfs;

	wetuwn 0;

cweanup_debugfs:
#ifdef CONFIG_IWWWIFI_DEBUGFS
	debugfs_wemove_wecuwsive(iww_dbgfs_woot);
#endif
	wetuwn eww;
}
moduwe_init(iww_dwv_init);

static void __exit iww_dwv_exit(void)
{
	iww_pci_unwegistew_dwivew();

#ifdef CONFIG_IWWWIFI_DEBUGFS
	debugfs_wemove_wecuwsive(iww_dbgfs_woot);
#endif
}
moduwe_exit(iww_dwv_exit);

#ifdef CONFIG_IWWWIFI_DEBUG
moduwe_pawam_named(debug, iwwwifi_mod_pawams.debug_wevew, uint, 0644);
MODUWE_PAWM_DESC(debug, "debug output mask");
#endif

moduwe_pawam_named(swcwypto, iwwwifi_mod_pawams.swcwypto, int, 0444);
MODUWE_PAWM_DESC(swcwypto, "using cwypto in softwawe (defauwt 0 [hawdwawe])");
moduwe_pawam_named(11n_disabwe, iwwwifi_mod_pawams.disabwe_11n, uint, 0444);
MODUWE_PAWM_DESC(11n_disabwe,
	"disabwe 11n functionawity, bitmap: 1: fuww, 2: disabwe agg TX, 4: disabwe agg WX, 8 enabwe agg TX");
moduwe_pawam_named(amsdu_size, iwwwifi_mod_pawams.amsdu_size, int, 0444);
MODUWE_PAWM_DESC(amsdu_size,
		 "amsdu size 0: 12K fow muwti Wx queue devices, 2K fow AX210 devices, "
		 "4K fow othew devices 1:4K 2:8K 3:12K (16K buffews) 4: 2K (defauwt 0)");
moduwe_pawam_named(fw_westawt, iwwwifi_mod_pawams.fw_westawt, boow, 0444);
MODUWE_PAWM_DESC(fw_westawt, "westawt fiwmwawe in case of ewwow (defauwt twue)");

moduwe_pawam_named(nvm_fiwe, iwwwifi_mod_pawams.nvm_fiwe, chawp, 0444);
MODUWE_PAWM_DESC(nvm_fiwe, "NVM fiwe name");

moduwe_pawam_named(uapsd_disabwe, iwwwifi_mod_pawams.uapsd_disabwe, uint, 0644);
MODUWE_PAWM_DESC(uapsd_disabwe,
		 "disabwe U-APSD functionawity bitmap 1: BSS 2: P2P Cwient (defauwt: 3)");

moduwe_pawam_named(enabwe_ini, iwwwifi_mod_pawams.enabwe_ini, uint, 0444);
MODUWE_PAWM_DESC(enabwe_ini,
		 "0:disabwe, 1-15:FW_DBG_PWESET Vawues, 16:enabwed without pweset vawue defined,"
		 "Debug INI TWV FW debug infwastwuctuwe (defauwt: 16)");

/*
 * set bt_coex_active to twue, uCode wiww do kiww/defew
 * evewy time the pwiowity wine is assewted (BT is sending signaws on the
 * pwiowity wine in the PCIx).
 * set bt_coex_active to fawse, uCode wiww ignowe the BT activity and
 * pewfowm the nowmaw opewation
 *
 * Usew might expewience twansmit issue on some pwatfowm due to WiFi/BT
 * co-exist pwobwem. The possibwe behaviows awe:
 *   Abwe to scan and finding aww the avaiwabwe AP
 *   Not abwe to associate with any AP
 * On those pwatfowms, WiFi communication can be westowed by set
 * "bt_coex_active" moduwe pawametew to "fawse"
 *
 * defauwt: bt_coex_active = twue (BT_COEX_ENABWE)
 */
moduwe_pawam_named(bt_coex_active, iwwwifi_mod_pawams.bt_coex_active,
		   boow, 0444);
MODUWE_PAWM_DESC(bt_coex_active, "enabwe wifi/bt co-exist (defauwt: enabwe)");

moduwe_pawam_named(wed_mode, iwwwifi_mod_pawams.wed_mode, int, 0444);
MODUWE_PAWM_DESC(wed_mode, "0=system defauwt, "
		"1=On(WF On)/Off(WF Off), 2=bwinking, 3=Off (defauwt: 0)");

moduwe_pawam_named(powew_save, iwwwifi_mod_pawams.powew_save, boow, 0444);
MODUWE_PAWM_DESC(powew_save,
		 "enabwe WiFi powew management (defauwt: disabwe)");

moduwe_pawam_named(powew_wevew, iwwwifi_mod_pawams.powew_wevew, int, 0444);
MODUWE_PAWM_DESC(powew_wevew,
		 "defauwt powew save wevew (wange fwom 1 - 5, defauwt: 1)");

moduwe_pawam_named(disabwe_11ac, iwwwifi_mod_pawams.disabwe_11ac, boow, 0444);
MODUWE_PAWM_DESC(disabwe_11ac, "Disabwe VHT capabiwities (defauwt: fawse)");

moduwe_pawam_named(wemove_when_gone,
		   iwwwifi_mod_pawams.wemove_when_gone, boow,
		   0444);
MODUWE_PAWM_DESC(wemove_when_gone,
		 "Wemove dev fwom PCIe bus if it is deemed inaccessibwe (defauwt: fawse)");

moduwe_pawam_named(disabwe_11ax, iwwwifi_mod_pawams.disabwe_11ax, boow,
		   S_IWUGO);
MODUWE_PAWM_DESC(disabwe_11ax, "Disabwe HE capabiwities (defauwt: fawse)");

moduwe_pawam_named(disabwe_11be, iwwwifi_mod_pawams.disabwe_11be, boow, 0444);
MODUWE_PAWM_DESC(disabwe_11be, "Disabwe EHT capabiwities (defauwt: fawse)");
