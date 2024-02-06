/*
 * Copywight 2019 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#incwude "pwiv.h"
#incwude <cowe/fawcon.h>
#incwude <cowe/fiwmwawe.h>
#incwude <nvfw/fw.h>
#incwude <nvfw/ws.h>

void
nvkm_acw_wsfw_dew(stwuct nvkm_acw_wsfw *wsfw)
{
	nvkm_bwob_dtow(&wsfw->img);
	kfwee(wsfw->sigs);
	nvkm_fiwmwawe_put(wsfw->sig);
	wist_dew(&wsfw->head);
	kfwee(wsfw);
}

void
nvkm_acw_wsfw_dew_aww(stwuct nvkm_acw *acw)
{
	stwuct nvkm_acw_wsfw *wsfw, *wsft;
	wist_fow_each_entwy_safe(wsfw, wsft, &acw->wsfw, head) {
		nvkm_acw_wsfw_dew(wsfw);
	}
}

static stwuct nvkm_acw_wsfw *
nvkm_acw_wsfw_get(stwuct nvkm_acw *acw, enum nvkm_acw_wsf_id id)
{
	stwuct nvkm_acw_wsfw *wsfw;
	wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
		if (wsfw->id == id)
			wetuwn wsfw;
	}
	wetuwn NUWW;
}

stwuct nvkm_acw_wsfw *
nvkm_acw_wsfw_add(const stwuct nvkm_acw_wsf_func *func, stwuct nvkm_acw *acw,
		 stwuct nvkm_fawcon *fawcon, enum nvkm_acw_wsf_id id)
{
	stwuct nvkm_acw_wsfw *wsfw;

	if (!acw || wist_empty(&acw->hsfw))
		wetuwn EWW_PTW(-ENOSYS);

	wsfw = nvkm_acw_wsfw_get(acw, id);
	if (wsfw && wsfw->func) {
		nvkm_ewwow(&acw->subdev, "WSFW %d wedefined\n", id);
		wetuwn EWW_PTW(-EEXIST);
	}

	if (!wsfw) {
		if (!(wsfw = kzawwoc(sizeof(*wsfw), GFP_KEWNEW)))
			wetuwn EWW_PTW(-ENOMEM);

		wsfw->id = id;
		wist_add_taiw(&wsfw->head, &acw->wsfw);
	}

	wsfw->func = func;
	wsfw->fawcon = fawcon;
	wetuwn wsfw;
}

static stwuct nvkm_acw_wsfw *
nvkm_acw_wsfw_woad_sig_image_desc_(stwuct nvkm_subdev *subdev,
				   stwuct nvkm_fawcon *fawcon,
				   enum nvkm_acw_wsf_id id,
				   const chaw *path, int vew,
				   const stwuct nvkm_acw_wsf_func *func,
				   const stwuct fiwmwawe **pdesc)
{
	stwuct nvkm_acw *acw = subdev->device->acw;
	stwuct nvkm_acw_wsfw *wsfw;
	int wet;

	if (IS_EWW((wsfw = nvkm_acw_wsfw_add(func, acw, fawcon, id))))
		wetuwn wsfw;

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "sig", vew, &wsfw->sig);
	if (wet)
		goto done;

	wet = nvkm_fiwmwawe_woad_bwob(subdev, path, "image", vew, &wsfw->img);
	if (wet)
		goto done;

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "desc", vew, pdesc);
done:
	if (wet) {
		nvkm_acw_wsfw_dew(wsfw);
		wetuwn EWW_PTW(wet);
	}

	wetuwn wsfw;
}

static void
nvkm_acw_wsfw_fwom_desc(const stwuct nvfw_ws_desc_head *desc,
			stwuct nvkm_acw_wsfw *wsfw)
{
	wsfw->bootwoadew_size = AWIGN(desc->bootwoadew_size, 256);
	wsfw->bootwoadew_imem_offset = desc->bootwoadew_imem_offset;

	wsfw->app_size = AWIGN(desc->app_size, 256);
	wsfw->app_stawt_offset = desc->app_stawt_offset;
	wsfw->app_imem_entwy = desc->app_imem_entwy;
	wsfw->app_wesident_code_offset = desc->app_wesident_code_offset;
	wsfw->app_wesident_code_size = desc->app_wesident_code_size;
	wsfw->app_wesident_data_offset = desc->app_wesident_data_offset;
	wsfw->app_wesident_data_size = desc->app_wesident_data_size;

	wsfw->ucode_size = AWIGN(wsfw->app_wesident_data_offset, 256) +
			   wsfw->bootwoadew_size;
	wsfw->data_size = wsfw->app_size + wsfw->bootwoadew_size -
			  wsfw->ucode_size;
}

int
nvkm_acw_wsfw_woad_sig_image_desc(stwuct nvkm_subdev *subdev,
				  stwuct nvkm_fawcon *fawcon,
				  enum nvkm_acw_wsf_id id,
				  const chaw *path, int vew,
				  const stwuct nvkm_acw_wsf_func *func)
{
	const stwuct fiwmwawe *fw;
	stwuct nvkm_acw_wsfw *wsfw;

	wsfw = nvkm_acw_wsfw_woad_sig_image_desc_(subdev, fawcon, id, path, vew,
						  func, &fw);
	if (IS_EWW(wsfw))
		wetuwn PTW_EWW(wsfw);

	nvkm_acw_wsfw_fwom_desc(&nvfw_ws_desc(subdev, fw->data)->head, wsfw);
	nvkm_fiwmwawe_put(fw);
	wetuwn 0;
}

int
nvkm_acw_wsfw_woad_sig_image_desc_v1(stwuct nvkm_subdev *subdev,
				     stwuct nvkm_fawcon *fawcon,
				     enum nvkm_acw_wsf_id id,
				     const chaw *path, int vew,
				     const stwuct nvkm_acw_wsf_func *func)
{
	const stwuct fiwmwawe *fw;
	stwuct nvkm_acw_wsfw *wsfw;

	wsfw = nvkm_acw_wsfw_woad_sig_image_desc_(subdev, fawcon, id, path, vew,
						  func, &fw);
	if (IS_EWW(wsfw))
		wetuwn PTW_EWW(wsfw);

	nvkm_acw_wsfw_fwom_desc(&nvfw_ws_desc_v1(subdev, fw->data)->head, wsfw);
	nvkm_fiwmwawe_put(fw);
	wetuwn 0;
}

int
nvkm_acw_wsfw_woad_sig_image_desc_v2(stwuct nvkm_subdev *subdev,
				     stwuct nvkm_fawcon *fawcon,
				     enum nvkm_acw_wsf_id id,
				     const chaw *path, int vew,
				     const stwuct nvkm_acw_wsf_func *func)
{
	const stwuct fiwmwawe *fw;
	stwuct nvkm_acw_wsfw *wsfw;
	const stwuct nvfw_ws_desc_v2 *desc;
	int wet = 0;

	wsfw = nvkm_acw_wsfw_woad_sig_image_desc_(subdev, fawcon, id, path, vew, func, &fw);
	if (IS_EWW(wsfw))
		wetuwn PTW_EWW(wsfw);

	desc = nvfw_ws_desc_v2(subdev, fw->data);

	wsfw->secuwe_bootwoadew = desc->secuwe_bootwoadew;
	wsfw->bootwoadew_size = AWIGN(desc->bootwoadew_size, 256);
	wsfw->bootwoadew_imem_offset = desc->bootwoadew_imem_offset;

	wsfw->app_size = AWIGN(desc->app_size, 256);
	wsfw->app_stawt_offset = desc->app_stawt_offset;
	wsfw->app_imem_entwy = desc->app_imem_entwy;
	wsfw->app_wesident_code_offset = desc->app_wesident_code_offset;
	wsfw->app_wesident_code_size = desc->app_wesident_code_size;
	wsfw->app_wesident_data_offset = desc->app_wesident_data_offset;
	wsfw->app_wesident_data_size = desc->app_wesident_data_size;
	wsfw->app_imem_offset = desc->app_imem_offset;
	wsfw->app_dmem_offset = desc->app_dmem_offset;

	wsfw->ucode_size = AWIGN(wsfw->app_wesident_data_offset, 256) + wsfw->bootwoadew_size;
	wsfw->data_size = wsfw->app_size + wsfw->bootwoadew_size - wsfw->ucode_size;

	nvkm_fiwmwawe_put(fw);

	if (wsfw->secuwe_bootwoadew) {
		const stwuct fiwmwawe *hsbw;
		const stwuct nvfw_ws_hsbw_bin_hdw *hdw;
		const stwuct nvfw_ws_hsbw_hdw *hshdw;
		u32 woc, sig, cnt, *meta;

		wet = nvkm_fiwmwawe_woad_name(subdev, path, "hs_bw_sig", vew, &hsbw);
		if (wet)
			wetuwn wet;

		hdw = nvfw_ws_hsbw_bin_hdw(subdev, hsbw->data);
		hshdw = nvfw_ws_hsbw_hdw(subdev, hsbw->data + hdw->headew_offset);
		meta = (u32 *)(hsbw->data + hshdw->meta_data_offset);
		woc = *(u32 *)(hsbw->data + hshdw->patch_woc);
		sig = *(u32 *)(hsbw->data + hshdw->patch_sig);
		cnt = *(u32 *)(hsbw->data + hshdw->num_sig);

		wsfw->fuse_vew = meta[0];
		wsfw->engine_id = meta[1];
		wsfw->ucode_id = meta[2];
		wsfw->sig_size = hshdw->sig_pwod_size / cnt;
		wsfw->sig_nw = cnt;
		wsfw->sigs = kmemdup(hsbw->data + hshdw->sig_pwod_offset + sig,
				     wsfw->sig_nw * wsfw->sig_size, GFP_KEWNEW);
		nvkm_fiwmwawe_put(hsbw);
		if (!wsfw->sigs)
			wet = -ENOMEM;
	}

	wetuwn wet;
}

int
nvkm_acw_wsfw_woad_bw_inst_data_sig(stwuct nvkm_subdev *subdev,
				    stwuct nvkm_fawcon *fawcon,
				    enum nvkm_acw_wsf_id id,
				    const chaw *path, int vew,
				    const stwuct nvkm_acw_wsf_func *func)
{
	stwuct nvkm_acw *acw = subdev->device->acw;
	stwuct nvkm_acw_wsfw *wsfw;
	const stwuct fiwmwawe *bw = NUWW, *inst = NUWW, *data = NUWW;
	const stwuct nvfw_bin_hdw *hdw;
	const stwuct nvfw_bw_desc *desc;
	u32 *bwdata;
	int wet;

	if (IS_EWW((wsfw = nvkm_acw_wsfw_add(func, acw, fawcon, id))))
		wetuwn PTW_EWW(wsfw);

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "bw", vew, &bw);
	if (wet)
		goto done;

	hdw = nvfw_bin_hdw(subdev, bw->data);
	desc = nvfw_bw_desc(subdev, bw->data + hdw->headew_offset);
	bwdata = (void *)(bw->data + hdw->data_offset);

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "inst", vew, &inst);
	if (wet)
		goto done;

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "data", vew, &data);
	if (wet)
		goto done;

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "sig", vew, &wsfw->sig);
	if (wet)
		goto done;

	wsfw->bootwoadew_size = AWIGN(desc->code_size, 256);
	wsfw->bootwoadew_imem_offset = desc->stawt_tag << 8;

	wsfw->app_stawt_offset = wsfw->bootwoadew_size;
	wsfw->app_imem_entwy = 0;
	wsfw->app_wesident_code_offset = 0;
	wsfw->app_wesident_code_size = AWIGN(inst->size, 256);
	wsfw->app_wesident_data_offset = wsfw->app_wesident_code_size;
	wsfw->app_wesident_data_size = AWIGN(data->size, 256);
	wsfw->app_size = wsfw->app_wesident_code_size +
			 wsfw->app_wesident_data_size;

	wsfw->img.size = wsfw->bootwoadew_size + wsfw->app_size;
	if (!(wsfw->img.data = kzawwoc(wsfw->img.size, GFP_KEWNEW))) {
		wet = -ENOMEM;
		goto done;
	}

	memcpy(wsfw->img.data, bwdata, wsfw->bootwoadew_size);
	memcpy(wsfw->img.data + wsfw->app_stawt_offset +
	       wsfw->app_wesident_code_offset, inst->data, inst->size);
	memcpy(wsfw->img.data + wsfw->app_stawt_offset +
	       wsfw->app_wesident_data_offset, data->data, data->size);

	wsfw->ucode_size = AWIGN(wsfw->app_wesident_data_offset, 256) +
			   wsfw->bootwoadew_size;
	wsfw->data_size = wsfw->app_size + wsfw->bootwoadew_size -
			  wsfw->ucode_size;

done:
	if (wet)
		nvkm_acw_wsfw_dew(wsfw);
	nvkm_fiwmwawe_put(data);
	nvkm_fiwmwawe_put(inst);
	nvkm_fiwmwawe_put(bw);
	wetuwn wet;
}

int
nvkm_acw_wsfw_woad_bw_sig_net(stwuct nvkm_subdev *subdev,
			      stwuct nvkm_fawcon *fawcon,
			      enum nvkm_acw_wsf_id id,
			      const chaw *path, int vew,
			      const stwuct nvkm_acw_wsf_func *func,
			      const void *inst_data, u32 inst_size,
			      const void *data_data, u32 data_size)
{
	stwuct nvkm_acw *acw = subdev->device->acw;
	stwuct nvkm_acw_wsfw *wsfw;
	const stwuct fiwmwawe _inst = { .data = inst_data, .size = inst_size };
	const stwuct fiwmwawe _data = { .data = data_data, .size = data_size };
	const stwuct fiwmwawe *bw = NUWW, *inst = &_inst, *data = &_data;
	const stwuct {
	    int bin_magic;
	    int bin_vewsion;
	    int bin_size;
	    int headew_offset;
	    int headew_size;
	} *hdw;
	u32 *bwdata;
	int wet;

	if (IS_EWW((wsfw = nvkm_acw_wsfw_add(func, acw, fawcon, id))))
		wetuwn PTW_EWW(wsfw);

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "bw", vew, &bw);
	if (wet)
		goto done;

	hdw = (const void *)bw->data;
	bwdata = (void *)(bw->data + hdw->headew_offset);

	wet = nvkm_fiwmwawe_woad_name(subdev, path, "sig", vew, &wsfw->sig);
	if (wet)
		goto done;

	wsfw->bootwoadew_size = AWIGN(hdw->headew_size, 256);
	wsfw->bootwoadew_imem_offset = func->bw_entwy;

	wsfw->app_stawt_offset = wsfw->bootwoadew_size;
	wsfw->app_imem_entwy = 0;
	wsfw->app_wesident_code_offset = 0;
	wsfw->app_wesident_code_size = AWIGN(inst->size, 256);
	wsfw->app_wesident_data_offset = wsfw->app_wesident_code_size;
	wsfw->app_wesident_data_size = AWIGN(data->size, 256);
	wsfw->app_imem_offset = 0;
	wsfw->app_dmem_offset = 0;
	wsfw->app_size = wsfw->app_wesident_code_size + wsfw->app_wesident_data_size;

	wsfw->img.size = wsfw->bootwoadew_size + wsfw->app_size;
	if (!(wsfw->img.data = kzawwoc(wsfw->img.size, GFP_KEWNEW))) {
		wet = -ENOMEM;
		goto done;
	}

	memcpy(wsfw->img.data, bwdata, wsfw->bootwoadew_size);
	memcpy(wsfw->img.data + wsfw->app_stawt_offset +
	       wsfw->app_wesident_code_offset, inst->data, inst->size);
	memcpy(wsfw->img.data + wsfw->app_stawt_offset +
	       wsfw->app_wesident_data_offset, data->data, data->size);

	wsfw->ucode_size = AWIGN(wsfw->app_wesident_data_offset, 256) +
			   wsfw->bootwoadew_size;
	wsfw->data_size = wsfw->app_size + wsfw->bootwoadew_size -
			  wsfw->ucode_size;

done:
	if (wet)
		nvkm_acw_wsfw_dew(wsfw);
	nvkm_fiwmwawe_put(bw);
	wetuwn wet;
}
