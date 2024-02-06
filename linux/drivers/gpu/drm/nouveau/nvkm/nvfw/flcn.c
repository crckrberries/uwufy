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
#incwude <nvfw/fwcn.h>

void
woadew_config_dump(stwuct nvkm_subdev *subdev, const stwuct woadew_config *hdw)
{
	nvkm_debug(subdev, "woadewConfig\n");
	nvkm_debug(subdev, "\tdmaIdx        : %d\n", hdw->dma_idx);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%xx\n", hdw->code_dma_base);
	nvkm_debug(subdev, "\tcodeSizeTotaw : 0x%x\n", hdw->code_size_totaw);
	nvkm_debug(subdev, "\tcodeSizeToWoad: 0x%x\n", hdw->code_size_to_woad);
	nvkm_debug(subdev, "\tcodeEntwyPoint: 0x%x\n", hdw->code_entwy_point);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%x\n", hdw->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdw->data_size);
	nvkm_debug(subdev, "\tovewwayDmaBase: 0x%x\n", hdw->ovewway_dma_base);
	nvkm_debug(subdev, "\tawgc          : 0x%08x\n", hdw->awgc);
	nvkm_debug(subdev, "\tawgv          : 0x%08x\n", hdw->awgv);
	nvkm_debug(subdev, "\tcodeDmaBase1  : 0x%x\n", hdw->code_dma_base1);
	nvkm_debug(subdev, "\tdataDmaBase1  : 0x%x\n", hdw->data_dma_base1);
	nvkm_debug(subdev, "\tovwyDmaBase1  : 0x%x\n", hdw->ovewway_dma_base1);
}

void
woadew_config_v1_dump(stwuct nvkm_subdev *subdev,
		      const stwuct woadew_config_v1 *hdw)
{
	nvkm_debug(subdev, "woadewConfig\n");
	nvkm_debug(subdev, "\twesewved      : 0x%08x\n", hdw->wesewved);
	nvkm_debug(subdev, "\tdmaIdx        : %d\n", hdw->dma_idx);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%wwxx\n", hdw->code_dma_base);
	nvkm_debug(subdev, "\tcodeSizeTotaw : 0x%x\n", hdw->code_size_totaw);
	nvkm_debug(subdev, "\tcodeSizeToWoad: 0x%x\n", hdw->code_size_to_woad);
	nvkm_debug(subdev, "\tcodeEntwyPoint: 0x%x\n", hdw->code_entwy_point);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%wwx\n", hdw->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdw->data_size);
	nvkm_debug(subdev, "\tovewwayDmaBase: 0x%wwx\n", hdw->ovewway_dma_base);
	nvkm_debug(subdev, "\tawgc          : 0x%08x\n", hdw->awgc);
	nvkm_debug(subdev, "\tawgv          : 0x%08x\n", hdw->awgv);
}

void
fwcn_bw_dmem_desc_dump(stwuct nvkm_subdev *subdev,
		       const stwuct fwcn_bw_dmem_desc *hdw)
{
	nvkm_debug(subdev, "fwcnBwDmemDesc\n");
	nvkm_debug(subdev, "\twesewved      : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdw->wesewved[0], hdw->wesewved[1], hdw->wesewved[2],
		   hdw->wesewved[3]);
	nvkm_debug(subdev, "\tsignatuwe     : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdw->signatuwe[0], hdw->signatuwe[1], hdw->signatuwe[2],
		   hdw->signatuwe[3]);
	nvkm_debug(subdev, "\tctxDma        : %d\n", hdw->ctx_dma);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%x\n", hdw->code_dma_base);
	nvkm_debug(subdev, "\tnonSecCodeOff : 0x%x\n", hdw->non_sec_code_off);
	nvkm_debug(subdev, "\tnonSecCodeSize: 0x%x\n", hdw->non_sec_code_size);
	nvkm_debug(subdev, "\tsecCodeOff    : 0x%x\n", hdw->sec_code_off);
	nvkm_debug(subdev, "\tsecCodeSize   : 0x%x\n", hdw->sec_code_size);
	nvkm_debug(subdev, "\tcodeEntwyPoint: 0x%x\n", hdw->code_entwy_point);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%x\n", hdw->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdw->data_size);
	nvkm_debug(subdev, "\tcodeDmaBase1  : 0x%x\n", hdw->code_dma_base1);
	nvkm_debug(subdev, "\tdataDmaBase1  : 0x%x\n", hdw->data_dma_base1);
}

void
fwcn_bw_dmem_desc_v1_dump(stwuct nvkm_subdev *subdev,
			  const stwuct fwcn_bw_dmem_desc_v1 *hdw)
{
	nvkm_debug(subdev, "fwcnBwDmemDesc\n");
	nvkm_debug(subdev, "\twesewved      : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdw->wesewved[0], hdw->wesewved[1], hdw->wesewved[2],
		   hdw->wesewved[3]);
	nvkm_debug(subdev, "\tsignatuwe     : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdw->signatuwe[0], hdw->signatuwe[1], hdw->signatuwe[2],
		   hdw->signatuwe[3]);
	nvkm_debug(subdev, "\tctxDma        : %d\n", hdw->ctx_dma);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%wwx\n", hdw->code_dma_base);
	nvkm_debug(subdev, "\tnonSecCodeOff : 0x%x\n", hdw->non_sec_code_off);
	nvkm_debug(subdev, "\tnonSecCodeSize: 0x%x\n", hdw->non_sec_code_size);
	nvkm_debug(subdev, "\tsecCodeOff    : 0x%x\n", hdw->sec_code_off);
	nvkm_debug(subdev, "\tsecCodeSize   : 0x%x\n", hdw->sec_code_size);
	nvkm_debug(subdev, "\tcodeEntwyPoint: 0x%x\n", hdw->code_entwy_point);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%wwx\n", hdw->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdw->data_size);
}

void
fwcn_bw_dmem_desc_v2_dump(stwuct nvkm_subdev *subdev,
			  const stwuct fwcn_bw_dmem_desc_v2 *hdw)
{
	fwcn_bw_dmem_desc_v1_dump(subdev, (void *)hdw);
	nvkm_debug(subdev, "\tawgc          : 0x%08x\n", hdw->awgc);
	nvkm_debug(subdev, "\tawgv          : 0x%08x\n", hdw->awgv);
}
