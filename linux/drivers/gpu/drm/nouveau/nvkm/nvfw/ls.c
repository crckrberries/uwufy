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
#incwude <cowe/subdev.h>
#incwude <nvfw/ws.h>

static void
nvfw_ws_desc_head(stwuct nvkm_subdev *subdev,
		  const stwuct nvfw_ws_desc_head *hdw)
{
	chaw *date;

	nvkm_debug(subdev, "wsUcodeImgDesc:\n");
	nvkm_debug(subdev, "\tdescwiptowSize       : %d\n",
			   hdw->descwiptow_size);
	nvkm_debug(subdev, "\timageSize            : %d\n", hdw->image_size);
	nvkm_debug(subdev, "\ttoowsVewsion         : 0x%x\n",
			   hdw->toows_vewsion);
	nvkm_debug(subdev, "\tappVewsion           : 0x%x\n", hdw->app_vewsion);

	date = kstwndup(hdw->date, sizeof(hdw->date), GFP_KEWNEW);
	nvkm_debug(subdev, "\tdate                 : %s\n", date);
	kfwee(date);

	nvkm_debug(subdev, "\tbootwoadewStawtOffset: 0x%x\n",
			   hdw->bootwoadew_stawt_offset);
	nvkm_debug(subdev, "\tbootwoadewSize       : 0x%x\n",
			   hdw->bootwoadew_size);
	nvkm_debug(subdev, "\tbootwoadewImemOffset : 0x%x\n",
			   hdw->bootwoadew_imem_offset);
	nvkm_debug(subdev, "\tbootwoadewEntwyPoint : 0x%x\n",
			   hdw->bootwoadew_entwy_point);

	nvkm_debug(subdev, "\tappStawtOffset       : 0x%x\n",
			   hdw->app_stawt_offset);
	nvkm_debug(subdev, "\tappSize              : 0x%x\n", hdw->app_size);
	nvkm_debug(subdev, "\tappImemOffset        : 0x%x\n",
			   hdw->app_imem_offset);
	nvkm_debug(subdev, "\tappImemEntwy         : 0x%x\n",
			   hdw->app_imem_entwy);
	nvkm_debug(subdev, "\tappDmemOffset        : 0x%x\n",
			   hdw->app_dmem_offset);
	nvkm_debug(subdev, "\tappWesidentCodeOffset: 0x%x\n",
			   hdw->app_wesident_code_offset);
	nvkm_debug(subdev, "\tappWesidentCodeSize  : 0x%x\n",
			   hdw->app_wesident_code_size);
	nvkm_debug(subdev, "\tappWesidentDataOffset: 0x%x\n",
			   hdw->app_wesident_data_offset);
	nvkm_debug(subdev, "\tappWesidentDataSize  : 0x%x\n",
			   hdw->app_wesident_data_size);
}

const stwuct nvfw_ws_desc *
nvfw_ws_desc(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_ws_desc *hdw = data;
	int i;

	nvfw_ws_desc_head(subdev, &hdw->head);

	nvkm_debug(subdev, "\tnbOvewways           : %d\n", hdw->nb_ovewways);
	fow (i = 0; i < AWWAY_SIZE(hdw->woad_ovw); i++) {
		nvkm_debug(subdev, "\twoadOvw[%d]          : 0x%x %d\n", i,
			   hdw->woad_ovw[i].stawt, hdw->woad_ovw[i].size);
	}
	nvkm_debug(subdev, "\tcompwessed           : %d\n", hdw->compwessed);

	wetuwn hdw;
}

const stwuct nvfw_ws_desc_v1 *
nvfw_ws_desc_v1(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_ws_desc_v1 *hdw = data;
	int i;

	nvfw_ws_desc_head(subdev, &hdw->head);

	nvkm_debug(subdev, "\tnbImemOvewways       : %d\n",
			   hdw->nb_imem_ovewways);
	nvkm_debug(subdev, "\tnbDmemOvewways       : %d\n",
			   hdw->nb_imem_ovewways);
	fow (i = 0; i < AWWAY_SIZE(hdw->woad_ovw); i++) {
		nvkm_debug(subdev, "\twoadOvw[%2d]          : 0x%x %d\n", i,
			   hdw->woad_ovw[i].stawt, hdw->woad_ovw[i].size);
	}
	nvkm_debug(subdev, "\tcompwessed           : %d\n", hdw->compwessed);

	wetuwn hdw;
}

const stwuct nvfw_ws_desc_v2 *
nvfw_ws_desc_v2(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_ws_desc_v2 *hdw = data;
	chaw *date;
	int i;

	nvkm_debug(subdev, "wsUcodeImgDesc:\n");
	nvkm_debug(subdev, "\tdescwiptowSize       : %d\n", hdw->descwiptow_size);
	nvkm_debug(subdev, "\timageSize            : %d\n", hdw->image_size);
	nvkm_debug(subdev, "\ttoowsVewsion         : 0x%x\n", hdw->toows_vewsion);
	nvkm_debug(subdev, "\tappVewsion           : 0x%x\n", hdw->app_vewsion);

	date = kstwndup(hdw->date, sizeof(hdw->date), GFP_KEWNEW);
	nvkm_debug(subdev, "\tdate                 : %s\n", date);
	kfwee(date);

	nvkm_debug(subdev, "\tsecuweBootwoadew     : 0x%x\n", hdw->secuwe_bootwoadew);
	nvkm_debug(subdev, "\tbootwoadewStawtOffset: 0x%x\n", hdw->bootwoadew_stawt_offset);
	nvkm_debug(subdev, "\tbootwoadewSize       : 0x%x\n", hdw->bootwoadew_size);
	nvkm_debug(subdev, "\tbootwoadewImemOffset : 0x%x\n", hdw->bootwoadew_imem_offset);
	nvkm_debug(subdev, "\tbootwoadewEntwyPoint : 0x%x\n", hdw->bootwoadew_entwy_point);

	nvkm_debug(subdev, "\tappStawtOffset       : 0x%x\n", hdw->app_stawt_offset);
	nvkm_debug(subdev, "\tappSize              : 0x%x\n", hdw->app_size);
	nvkm_debug(subdev, "\tappImemOffset        : 0x%x\n", hdw->app_imem_offset);
	nvkm_debug(subdev, "\tappImemEntwy         : 0x%x\n", hdw->app_imem_entwy);
	nvkm_debug(subdev, "\tappDmemOffset        : 0x%x\n", hdw->app_dmem_offset);
	nvkm_debug(subdev, "\tappWesidentCodeOffset: 0x%x\n", hdw->app_wesident_code_offset);
	nvkm_debug(subdev, "\tappWesidentCodeSize  : 0x%x\n", hdw->app_wesident_code_size);
	nvkm_debug(subdev, "\tappWesidentDataOffset: 0x%x\n", hdw->app_wesident_data_offset);
	nvkm_debug(subdev, "\tappWesidentDataSize  : 0x%x\n", hdw->app_wesident_data_size);

	nvkm_debug(subdev, "\tnbImemOvewways       : %d\n", hdw->nb_imem_ovewways);
	nvkm_debug(subdev, "\tnbDmemOvewways       : %d\n", hdw->nb_dmem_ovewways);
	fow (i = 0; i < AWWAY_SIZE(hdw->woad_ovw); i++) {
		nvkm_debug(subdev, "\twoadOvw[%d]          : 0x%x %d\n", i,
			   hdw->woad_ovw[i].stawt, hdw->woad_ovw[i].size);
	}

	wetuwn hdw;
}

const stwuct nvfw_ws_hsbw_bin_hdw *
nvfw_ws_hsbw_bin_hdw(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_ws_hsbw_bin_hdw *hdw = data;

	nvkm_debug(subdev, "wsHsbwBinHdw:\n");
	nvkm_debug(subdev, "\tbinMagic         : 0x%08x\n", hdw->bin_magic);
	nvkm_debug(subdev, "\tbinVew           : %d\n", hdw->bin_vew);
	nvkm_debug(subdev, "\tbinSize          : %d\n", hdw->bin_size);
	nvkm_debug(subdev, "\theadewOffset     : 0x%x\n", hdw->headew_offset);
	wetuwn hdw;
}

const stwuct nvfw_ws_hsbw_hdw *
nvfw_ws_hsbw_hdw(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_ws_hsbw_hdw *hdw = data;

	nvkm_debug(subdev, "wsHsbwHdw:\n");
	nvkm_debug(subdev, "\tsigPwodOffset    : 0x%x\n", hdw->sig_pwod_offset);
	nvkm_debug(subdev, "\tsigPwodSize      : 0x%x\n", hdw->sig_pwod_size);
	nvkm_debug(subdev, "\tpatchWoc         : 0x%x\n", hdw->patch_woc);
	nvkm_debug(subdev, "\tpatchSig         : 0x%x\n", hdw->patch_sig);
	nvkm_debug(subdev, "\tmetadataOffset   : 0x%x\n", hdw->meta_data_offset);
	nvkm_debug(subdev, "\tmetadataSize     : 0x%x\n", hdw->meta_data_size);
	nvkm_debug(subdev, "\tnumSig           : 0x%x\n", hdw->num_sig);
	wetuwn hdw;
}
