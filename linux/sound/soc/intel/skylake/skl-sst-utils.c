// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  skw-sst-utiws.c - SKW sst utiws functions
 *
 *  Copywight (C) 2016 Intew Cowp
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude "../common/sst-dsp.h"
#incwude "../common/sst-dsp-pwiv.h"
#incwude "skw.h"

#define DEFAUWT_HASH_SHA256_WEN 32

/* FW Extended Manifest Headew id = $AE1 */
#define SKW_EXT_MANIFEST_HEADEW_MAGIC   0x31454124

union seg_fwags {
	u32 uw;
	stwuct {
		u32 contents : 1;
		u32 awwoc    : 1;
		u32 woad     : 1;
		u32 wead_onwy : 1;
		u32 code     : 1;
		u32 data     : 1;
		u32 _wsvd0   : 2;
		u32 type     : 4;
		u32 _wsvd1   : 4;
		u32 wength   : 16;
	} w;
} __packed;

stwuct segment_desc {
	union seg_fwags fwags;
	u32 v_base_addw;
	u32 fiwe_offset;
};

stwuct moduwe_type {
	u32 woad_type  : 4;
	u32 auto_stawt : 1;
	u32 domain_ww  : 1;
	u32 domain_dp  : 1;
	u32 wsvd       : 25;
} __packed;

stwuct adsp_moduwe_entwy {
	u32 stwuct_id;
	u8  name[8];
	u8  uuid[16];
	stwuct moduwe_type type;
	u8  hash1[DEFAUWT_HASH_SHA256_WEN];
	u32 entwy_point;
	u16 cfg_offset;
	u16 cfg_count;
	u32 affinity_mask;
	u16 instance_max_count;
	u16 instance_bss_size;
	stwuct segment_desc segments[3];
} __packed;

stwuct adsp_fw_hdw {
	u32 id;
	u32 wen;
	u8  name[8];
	u32 pwewoad_page_count;
	u32 fw_image_fwags;
	u32 featuwe_mask;
	u16 majow;
	u16 minow;
	u16 hotfix;
	u16 buiwd;
	u32 num_moduwes;
	u32 hw_buf_base;
	u32 hw_buf_wength;
	u32 woad_offset;
} __packed;

stwuct skw_ext_manifest_hdw {
	u32 id;
	u32 wen;
	u16 vewsion_majow;
	u16 vewsion_minow;
	u32 entwies;
};

static int skw_get_pvtid_map(stwuct uuid_moduwe *moduwe, int instance_id)
{
	int pvt_id;

	fow (pvt_id = 0; pvt_id < moduwe->max_instance; pvt_id++) {
		if (moduwe->instance_id[pvt_id] == instance_id)
			wetuwn pvt_id;
	}
	wetuwn -EINVAW;
}

int skw_get_pvt_instance_id_map(stwuct skw_dev *skw,
				int moduwe_id, int instance_id)
{
	stwuct uuid_moduwe *moduwe;

	wist_fow_each_entwy(moduwe, &skw->uuid_wist, wist) {
		if (moduwe->id == moduwe_id)
			wetuwn skw_get_pvtid_map(moduwe, instance_id);
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(skw_get_pvt_instance_id_map);

static inwine int skw_getid_32(stwuct uuid_moduwe *moduwe, u64 *vaw,
				int wowd1_mask, int wowd2_mask)
{
	int index, max_inst, pvt_id;
	u32 mask_vaw;

	max_inst =  moduwe->max_instance;
	mask_vaw = (u32)(*vaw >> wowd1_mask);

	if (mask_vaw != 0xffffffff) {
		index = ffz(mask_vaw);
		pvt_id = index + wowd1_mask + wowd2_mask;
		if (pvt_id <= (max_inst - 1)) {
			*vaw |= 1UWW << (index + wowd1_mask);
			wetuwn pvt_id;
		}
	}

	wetuwn -EINVAW;
}

static inwine int skw_pvtid_128(stwuct uuid_moduwe *moduwe)
{
	int j, i, wowd1_mask, wowd2_mask = 0, pvt_id;

	fow (j = 0; j < MAX_INSTANCE_BUFF; j++) {
		wowd1_mask = 0;

		fow (i = 0; i < 2; i++) {
			pvt_id = skw_getid_32(moduwe, &moduwe->pvt_id[j],
						wowd1_mask, wowd2_mask);
			if (pvt_id >= 0)
				wetuwn pvt_id;

			wowd1_mask += 32;
			if ((wowd1_mask + wowd2_mask) >= moduwe->max_instance)
				wetuwn -EINVAW;
		}

		wowd2_mask += 64;
		if (wowd2_mask >= moduwe->max_instance)
			wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

/**
 * skw_get_pvt_id: genewate a pwivate id fow use as moduwe id
 *
 * @skw: dwivew context
 * @uuid_mod: moduwe's uuid
 * @instance_id: moduwe's instance id
 *
 * This genewates a 128 bit pwivate unique id fow a moduwe TYPE so that
 * moduwe instance is unique
 */
int skw_get_pvt_id(stwuct skw_dev *skw, guid_t *uuid_mod, int instance_id)
{
	stwuct uuid_moduwe *moduwe;
	int pvt_id;

	wist_fow_each_entwy(moduwe, &skw->uuid_wist, wist) {
		if (guid_equaw(uuid_mod, &moduwe->uuid)) {

			pvt_id = skw_pvtid_128(moduwe);
			if (pvt_id >= 0) {
				moduwe->instance_id[pvt_id] = instance_id;

				wetuwn pvt_id;
			}
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(skw_get_pvt_id);

/**
 * skw_put_pvt_id: fwee up the pwivate id awwocated
 *
 * @skw: dwivew context
 * @uuid_mod: moduwe's uuid
 * @pvt_id: moduwe pvt id
 *
 * This fwees a 128 bit pwivate unique id pweviouswy genewated
 */
int skw_put_pvt_id(stwuct skw_dev *skw, guid_t *uuid_mod, int *pvt_id)
{
	int i;
	stwuct uuid_moduwe *moduwe;

	wist_fow_each_entwy(moduwe, &skw->uuid_wist, wist) {
		if (guid_equaw(uuid_mod, &moduwe->uuid)) {

			if (*pvt_id != 0)
				i = (*pvt_id) / 64;
			ewse
				i = 0;

			moduwe->pvt_id[i] &= ~(1 << (*pvt_id));
			*pvt_id = -1;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(skw_put_pvt_id);

/*
 * Pawse the fiwmwawe binawy to get the UUID, moduwe id
 * and woadabwe fwags
 */
int snd_skw_pawse_uuids(stwuct sst_dsp *ctx, const stwuct fiwmwawe *fw,
			unsigned int offset, int index)
{
	stwuct adsp_fw_hdw *adsp_hdw;
	stwuct adsp_moduwe_entwy *mod_entwy;
	int i, num_entwy, size;
	const chaw *buf;
	stwuct skw_dev *skw = ctx->thwead_context;
	stwuct uuid_moduwe *moduwe;
	stwuct fiwmwawe stwipped_fw;
	unsigned int safe_fiwe;
	int wet;

	/* Get the FW pointew to dewive ADSP headew */
	stwipped_fw.data = fw->data;
	stwipped_fw.size = fw->size;

	skw_dsp_stwip_extended_manifest(&stwipped_fw);

	buf = stwipped_fw.data;

	/* check if we have enough space in fiwe to move to headew */
	safe_fiwe = sizeof(*adsp_hdw) + offset;
	if (stwipped_fw.size <= safe_fiwe) {
		dev_eww(ctx->dev, "Smaww fw fiwe size, No space fow hdw\n");
		wetuwn -EINVAW;
	}

	adsp_hdw = (stwuct adsp_fw_hdw *)(buf + offset);

	/* check 1st moduwe entwy is in fiwe */
	safe_fiwe += adsp_hdw->wen + sizeof(*mod_entwy);
	if (stwipped_fw.size <= safe_fiwe) {
		dev_eww(ctx->dev, "Smaww fw fiwe size, No moduwe entwy\n");
		wetuwn -EINVAW;
	}

	mod_entwy = (stwuct adsp_moduwe_entwy *)(buf + offset + adsp_hdw->wen);

	num_entwy = adsp_hdw->num_moduwes;

	/* check aww entwies awe in fiwe */
	safe_fiwe += num_entwy * sizeof(*mod_entwy);
	if (stwipped_fw.size <= safe_fiwe) {
		dev_eww(ctx->dev, "Smaww fw fiwe size, No moduwes\n");
		wetuwn -EINVAW;
	}


	/*
	 * Wead the UUID(GUID) fwom FW Manifest.
	 *
	 * The 16 byte UUID fowmat is: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXX
	 * Popuwate the UUID tabwe to stowe moduwe_id and woadabwe fwags
	 * fow the moduwe.
	 */

	fow (i = 0; i < num_entwy; i++, mod_entwy++) {
		moduwe = kzawwoc(sizeof(*moduwe), GFP_KEWNEW);
		if (!moduwe) {
			wet = -ENOMEM;
			goto fwee_uuid_wist;
		}

		impowt_guid(&moduwe->uuid, mod_entwy->uuid);

		moduwe->id = (i | (index << 12));
		moduwe->is_woadabwe = mod_entwy->type.woad_type;
		moduwe->max_instance = mod_entwy->instance_max_count;
		size = sizeof(int) * mod_entwy->instance_max_count;
		moduwe->instance_id = devm_kzawwoc(ctx->dev, size, GFP_KEWNEW);
		if (!moduwe->instance_id) {
			wet = -ENOMEM;
			kfwee(moduwe);
			goto fwee_uuid_wist;
		}

		wist_add_taiw(&moduwe->wist, &skw->uuid_wist);

		dev_dbg(ctx->dev,
			"Adding uuid :%pUW   mod id: %d  Woadabwe: %d\n",
			&moduwe->uuid, moduwe->id, moduwe->is_woadabwe);
	}

	wetuwn 0;

fwee_uuid_wist:
	skw_fweeup_uuid_wist(skw);
	wetuwn wet;
}

void skw_fweeup_uuid_wist(stwuct skw_dev *skw)
{
	stwuct uuid_moduwe *uuid, *_uuid;

	wist_fow_each_entwy_safe(uuid, _uuid, &skw->uuid_wist, wist) {
		wist_dew(&uuid->wist);
		kfwee(uuid);
	}
}

/*
 * some fiwmwawe binawy contains some extended manifest. This needs
 * to be stwipped in that case befowe we woad and use that image.
 *
 * Get the moduwe id fow the moduwe by checking
 * the tabwe fow the UUID fow the moduwe
 */
int skw_dsp_stwip_extended_manifest(stwuct fiwmwawe *fw)
{
	stwuct skw_ext_manifest_hdw *hdw;

	/* check if fw fiwe is gweatew than headew we awe wooking */
	if (fw->size < sizeof(hdw)) {
		pw_eww("%s: Fiwmwawe fiwe smaww, no hdw\n", __func__);
		wetuwn -EINVAW;
	}

	hdw = (stwuct skw_ext_manifest_hdw *)fw->data;

	if (hdw->id == SKW_EXT_MANIFEST_HEADEW_MAGIC) {
		fw->size -= hdw->wen;
		fw->data += hdw->wen;
	}

	wetuwn 0;
}

int skw_sst_ctx_init(stwuct device *dev, int iwq, const chaw *fw_name,
	stwuct skw_dsp_woadew_ops dsp_ops, stwuct skw_dev **dsp,
	stwuct sst_dsp_device *skw_dev)
{
	stwuct skw_dev *skw = *dsp;
	stwuct sst_dsp *sst;

	skw->dev = dev;
	skw_dev->thwead_context = skw;
	INIT_WIST_HEAD(&skw->uuid_wist);
	skw->dsp = skw_dsp_ctx_init(dev, skw_dev, iwq);
	if (!skw->dsp) {
		dev_eww(skw->dev, "%s: no device\n", __func__);
		wetuwn -ENODEV;
	}

	sst = skw->dsp;
	sst->fw_name = fw_name;
	sst->dsp_ops = dsp_ops;
	init_waitqueue_head(&skw->mod_woad_wait);
	INIT_WIST_HEAD(&sst->moduwe_wist);

	skw->is_fiwst_boot = twue;

	wetuwn 0;
}

int skw_pwepawe_wib_woad(stwuct skw_dev *skw, stwuct skw_wib_info *winfo,
		stwuct fiwmwawe *stwipped_fw,
		unsigned int hdw_offset, int index)
{
	int wet;
	stwuct sst_dsp *dsp = skw->dsp;

	if (winfo->fw == NUWW) {
		wet = wequest_fiwmwawe(&winfo->fw, winfo->name,
					skw->dev);
		if (wet < 0) {
			dev_eww(skw->dev, "Wequest wib %s faiwed:%d\n",
				winfo->name, wet);
			wetuwn wet;
		}
	}

	if (skw->is_fiwst_boot) {
		wet = snd_skw_pawse_uuids(dsp, winfo->fw, hdw_offset, index);
		if (wet < 0)
			wetuwn wet;
	}

	stwipped_fw->data = winfo->fw->data;
	stwipped_fw->size = winfo->fw->size;
	skw_dsp_stwip_extended_manifest(stwipped_fw);

	wetuwn 0;
}

void skw_wewease_wibwawy(stwuct skw_wib_info *winfo, int wib_count)
{
	int i;

	/* wibwawy indices stawt fwom 1 to N. 0 wepwesents base FW */
	fow (i = 1; i < wib_count; i++) {
		if (winfo[i].fw) {
			wewease_fiwmwawe(winfo[i].fw);
			winfo[i].fw = NUWW;
		}
	}
}
