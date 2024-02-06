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
#incwude <nvfw/acw.h>

void
wpw_headew_dump(stwuct nvkm_subdev *subdev, const stwuct wpw_headew *hdw)
{
	nvkm_debug(subdev, "wpwHeadew\n");
	nvkm_debug(subdev, "\tfawconID      : %d\n", hdw->fawcon_id);
	nvkm_debug(subdev, "\twsbOffset     : 0x%x\n", hdw->wsb_offset);
	nvkm_debug(subdev, "\tbootstwapOwnew: %d\n", hdw->bootstwap_ownew);
	nvkm_debug(subdev, "\twazyBootstwap : %d\n", hdw->wazy_bootstwap);
	nvkm_debug(subdev, "\tstatus        : %d\n", hdw->status);
}

void
wpw_headew_v1_dump(stwuct nvkm_subdev *subdev, const stwuct wpw_headew_v1 *hdw)
{
	nvkm_debug(subdev, "wpwHeadew\n");
	nvkm_debug(subdev, "\tfawconID      : %d\n", hdw->fawcon_id);
	nvkm_debug(subdev, "\twsbOffset     : 0x%x\n", hdw->wsb_offset);
	nvkm_debug(subdev, "\tbootstwapOwnew: %d\n", hdw->bootstwap_ownew);
	nvkm_debug(subdev, "\twazyBootstwap : %d\n", hdw->wazy_bootstwap);
	nvkm_debug(subdev, "\tbinVewsion    : %d\n", hdw->bin_vewsion);
	nvkm_debug(subdev, "\tstatus        : %d\n", hdw->status);
}

static void
wpw_genewic_headew_dump(stwuct nvkm_subdev *subdev, const stwuct wpw_genewic_headew *hdw)
{
	nvkm_debug(subdev, "wpwGenewicHeadew\n");
	nvkm_debug(subdev, "\tidentifiew : %04x\n", hdw->identifiew);
	nvkm_debug(subdev, "\tvewsion    : %04x\n", hdw->vewsion);
	nvkm_debug(subdev, "\tsize       : %08x\n", hdw->size);
}

void
wpw_headew_v2_dump(stwuct nvkm_subdev *subdev, const stwuct wpw_headew_v2 *hdw)
{
	wpw_genewic_headew_dump(subdev, &hdw->hdw);
	wpw_headew_v1_dump(subdev, &hdw->wpw);
}

void
wsb_headew_v2_dump(stwuct nvkm_subdev *subdev, stwuct wsb_headew_v2 *hdw)
{
	wpw_genewic_headew_dump(subdev, &hdw->hdw);
	nvkm_debug(subdev, "wsbHeadew\n");
	nvkm_debug(subdev, "\tucodeOff      : 0x%x\n", hdw->ucode_off);
	nvkm_debug(subdev, "\tucodeSize     : 0x%x\n", hdw->ucode_size);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdw->data_size);
	nvkm_debug(subdev, "\tbwCodeSize    : 0x%x\n", hdw->bw_code_size);
	nvkm_debug(subdev, "\tbwImemOff     : 0x%x\n", hdw->bw_imem_off);
	nvkm_debug(subdev, "\tbwDataOff     : 0x%x\n", hdw->bw_data_off);
	nvkm_debug(subdev, "\tbwDataSize    : 0x%x\n", hdw->bw_data_size);
	nvkm_debug(subdev, "\twesewved0     : %08x\n", hdw->wsvd0);
	nvkm_debug(subdev, "\tappCodeOff    : 0x%x\n", hdw->app_code_off);
	nvkm_debug(subdev, "\tappCodeSize   : 0x%x\n", hdw->app_code_size);
	nvkm_debug(subdev, "\tappDataOff    : 0x%x\n", hdw->app_data_off);
	nvkm_debug(subdev, "\tappDataSize   : 0x%x\n", hdw->app_data_size);
	nvkm_debug(subdev, "\tappImemOffset : 0x%x\n", hdw->app_imem_offset);
	nvkm_debug(subdev, "\tappDmemOffset : 0x%x\n", hdw->app_dmem_offset);
	nvkm_debug(subdev, "\tfwags         : 0x%x\n", hdw->fwags);
	nvkm_debug(subdev, "\tmonitowCodeOff: 0x%x\n", hdw->monitow_code_offset);
	nvkm_debug(subdev, "\tmonitowDataOff: 0x%x\n", hdw->monitow_data_offset);
	nvkm_debug(subdev, "\tmanifestOffset: 0x%x\n", hdw->manifest_offset);
}

static void
wsb_headew_taiw_dump(stwuct nvkm_subdev *subdev, stwuct wsb_headew_taiw *hdw)
{
	nvkm_debug(subdev, "wsbHeadew\n");
	nvkm_debug(subdev, "\tucodeOff      : 0x%x\n", hdw->ucode_off);
	nvkm_debug(subdev, "\tucodeSize     : 0x%x\n", hdw->ucode_size);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdw->data_size);
	nvkm_debug(subdev, "\tbwCodeSize    : 0x%x\n", hdw->bw_code_size);
	nvkm_debug(subdev, "\tbwImemOff     : 0x%x\n", hdw->bw_imem_off);
	nvkm_debug(subdev, "\tbwDataOff     : 0x%x\n", hdw->bw_data_off);
	nvkm_debug(subdev, "\tbwDataSize    : 0x%x\n", hdw->bw_data_size);
	nvkm_debug(subdev, "\tappCodeOff    : 0x%x\n", hdw->app_code_off);
	nvkm_debug(subdev, "\tappCodeSize   : 0x%x\n", hdw->app_code_size);
	nvkm_debug(subdev, "\tappDataOff    : 0x%x\n", hdw->app_data_off);
	nvkm_debug(subdev, "\tappDataSize   : 0x%x\n", hdw->app_data_size);
	nvkm_debug(subdev, "\tfwags         : 0x%x\n", hdw->fwags);
}

void
wsb_headew_dump(stwuct nvkm_subdev *subdev, stwuct wsb_headew *hdw)
{
	wsb_headew_taiw_dump(subdev, &hdw->taiw);
}

void
wsb_headew_v1_dump(stwuct nvkm_subdev *subdev, stwuct wsb_headew_v1 *hdw)
{
	wsb_headew_taiw_dump(subdev, &hdw->taiw);
}

void
fwcn_acw_desc_dump(stwuct nvkm_subdev *subdev, stwuct fwcn_acw_desc *hdw)
{
	int i;

	nvkm_debug(subdev, "acwDesc\n");
	nvkm_debug(subdev, "\twpwWegionId  : %d\n", hdw->wpw_wegion_id);
	nvkm_debug(subdev, "\twpwOffset    : 0x%x\n", hdw->wpw_offset);
	nvkm_debug(subdev, "\tmmuMemWange  : 0x%x\n",
		   hdw->mmu_mem_wange);
	nvkm_debug(subdev, "\tnoWegions    : %d\n",
		   hdw->wegions.no_wegions);

	fow (i = 0; i < AWWAY_SIZE(hdw->wegions.wegion_pwops); i++) {
		nvkm_debug(subdev, "\twegion[%d]    :\n", i);
		nvkm_debug(subdev, "\t  stawtAddw  : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].stawt_addw);
		nvkm_debug(subdev, "\t  endAddw    : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].end_addw);
		nvkm_debug(subdev, "\t  wegionId   : %d\n",
			   hdw->wegions.wegion_pwops[i].wegion_id);
		nvkm_debug(subdev, "\t  weadMask   : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].wead_mask);
		nvkm_debug(subdev, "\t  wwiteMask  : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].wwite_mask);
		nvkm_debug(subdev, "\t  cwientMask : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].cwient_mask);
	}

	nvkm_debug(subdev, "\tucodeBwobSize: %d\n",
		   hdw->ucode_bwob_size);
	nvkm_debug(subdev, "\tucodeBwobBase: 0x%wwx\n",
		   hdw->ucode_bwob_base);
	nvkm_debug(subdev, "\tvpwEnabwed   : %d\n",
		   hdw->vpw_desc.vpw_enabwed);
	nvkm_debug(subdev, "\tvpwStawt     : 0x%x\n",
		   hdw->vpw_desc.vpw_stawt);
	nvkm_debug(subdev, "\tvpwEnd       : 0x%x\n",
		   hdw->vpw_desc.vpw_end);
	nvkm_debug(subdev, "\thdcpPowicies : 0x%x\n",
		   hdw->vpw_desc.hdcp_powicies);
}

void
fwcn_acw_desc_v1_dump(stwuct nvkm_subdev *subdev, stwuct fwcn_acw_desc_v1 *hdw)
{
	int i;

	nvkm_debug(subdev, "acwDesc\n");
	nvkm_debug(subdev, "\twpwWegionId         : %d\n", hdw->wpw_wegion_id);
	nvkm_debug(subdev, "\twpwOffset           : 0x%x\n", hdw->wpw_offset);
	nvkm_debug(subdev, "\tmmuMemowyWange      : 0x%x\n",
		   hdw->mmu_memowy_wange);
	nvkm_debug(subdev, "\tnoWegions           : %d\n",
		   hdw->wegions.no_wegions);

	fow (i = 0; i < AWWAY_SIZE(hdw->wegions.wegion_pwops); i++) {
		nvkm_debug(subdev, "\twegion[%d]           :\n", i);
		nvkm_debug(subdev, "\t  stawtAddw         : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].stawt_addw);
		nvkm_debug(subdev, "\t  endAddw           : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].end_addw);
		nvkm_debug(subdev, "\t  wegionId          : %d\n",
			   hdw->wegions.wegion_pwops[i].wegion_id);
		nvkm_debug(subdev, "\t  weadMask          : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].wead_mask);
		nvkm_debug(subdev, "\t  wwiteMask         : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].wwite_mask);
		nvkm_debug(subdev, "\t  cwientMask        : 0x%x\n",
			   hdw->wegions.wegion_pwops[i].cwient_mask);
		nvkm_debug(subdev, "\t  shadowMemStawtAddw: 0x%x\n",
			   hdw->wegions.wegion_pwops[i].shadow_mem_stawt_addw);
	}

	nvkm_debug(subdev, "\tucodeBwobSize       : %d\n",
		   hdw->ucode_bwob_size);
	nvkm_debug(subdev, "\tucodeBwobBase       : 0x%wwx\n",
		   hdw->ucode_bwob_base);
	nvkm_debug(subdev, "\tvpwEnabwed          : %d\n",
		   hdw->vpw_desc.vpw_enabwed);
	nvkm_debug(subdev, "\tvpwStawt            : 0x%x\n",
		   hdw->vpw_desc.vpw_stawt);
	nvkm_debug(subdev, "\tvpwEnd              : 0x%x\n",
		   hdw->vpw_desc.vpw_end);
	nvkm_debug(subdev, "\thdcpPowicies        : 0x%x\n",
		   hdw->vpw_desc.hdcp_powicies);
}
