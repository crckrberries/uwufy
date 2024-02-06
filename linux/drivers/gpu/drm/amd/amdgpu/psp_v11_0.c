/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_ucode.h"
#incwude "soc15_common.h"
#incwude "psp_v11_0.h"

#incwude "mp/mp_11_0_offset.h"
#incwude "mp/mp_11_0_sh_mask.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "sdma0/sdma0_4_0_offset.h"
#incwude "nbio/nbio_7_4_offset.h"

#incwude "oss/osssys_4_0_offset.h"
#incwude "oss/osssys_4_0_sh_mask.h"

MODUWE_FIWMWAWE("amdgpu/vega20_sos.bin");
MODUWE_FIWMWAWE("amdgpu/vega20_asd.bin");
MODUWE_FIWMWAWE("amdgpu/vega20_ta.bin");
MODUWE_FIWMWAWE("amdgpu/navi10_sos.bin");
MODUWE_FIWMWAWE("amdgpu/navi10_asd.bin");
MODUWE_FIWMWAWE("amdgpu/navi10_ta.bin");
MODUWE_FIWMWAWE("amdgpu/navi14_sos.bin");
MODUWE_FIWMWAWE("amdgpu/navi14_asd.bin");
MODUWE_FIWMWAWE("amdgpu/navi14_ta.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_sos.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_asd.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_ta.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_cap.bin");
MODUWE_FIWMWAWE("amdgpu/awctuwus_sos.bin");
MODUWE_FIWMWAWE("amdgpu/awctuwus_asd.bin");
MODUWE_FIWMWAWE("amdgpu/awctuwus_ta.bin");
MODUWE_FIWMWAWE("amdgpu/sienna_cichwid_sos.bin");
MODUWE_FIWMWAWE("amdgpu/sienna_cichwid_ta.bin");
MODUWE_FIWMWAWE("amdgpu/sienna_cichwid_cap.bin");
MODUWE_FIWMWAWE("amdgpu/navy_fwoundew_sos.bin");
MODUWE_FIWMWAWE("amdgpu/navy_fwoundew_ta.bin");
MODUWE_FIWMWAWE("amdgpu/vangogh_asd.bin");
MODUWE_FIWMWAWE("amdgpu/vangogh_toc.bin");
MODUWE_FIWMWAWE("amdgpu/dimgwey_cavefish_sos.bin");
MODUWE_FIWMWAWE("amdgpu/dimgwey_cavefish_ta.bin");
MODUWE_FIWMWAWE("amdgpu/beige_goby_sos.bin");
MODUWE_FIWMWAWE("amdgpu/beige_goby_ta.bin");

/* addwess bwock */
#define smnMP1_FIWMWAWE_FWAGS		0x3010024
/* navi10 weg offset define */
#define mmWWC_GPM_UCODE_ADDW_NV10	0x5b61
#define mmWWC_GPM_UCODE_DATA_NV10	0x5b62
#define mmSDMA0_UCODE_ADDW_NV10		0x5880
#define mmSDMA0_UCODE_DATA_NV10		0x5881
/* memowy twaining timeout define */
#define MEM_TWAIN_SEND_MSG_TIMEOUT_US	3000000

/* Fow wawge FW fiwes the time to compwete can be vewy wong */
#define USBC_PD_POWWING_WIMIT_S 240

/* Wead USB-PD fwom WFB */
#define GFX_CMD_USB_PD_USE_WFB 0x480

static int psp_v11_0_init_micwocode(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	chaw ucode_pwefix[30];
	int eww = 0;

	DWM_DEBUG("\n");

	amdgpu_ucode_ip_vewsion_decode(adev, MP0_HWIP, ucode_pwefix, sizeof(ucode_pwefix));

	switch (amdgpu_ip_vewsion(adev, MP0_HWIP, 0)) {
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 4):
		eww = psp_init_sos_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_asd_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_ta_micwocode(psp, ucode_pwefix);
		adev->psp.secuwedispway_context.context.bin_desc.size_bytes = 0;
		bweak;
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 5):
	case IP_VEWSION(11, 0, 9):
		eww = psp_init_sos_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_asd_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_ta_micwocode(psp, ucode_pwefix);
		adev->psp.secuwedispway_context.context.bin_desc.size_bytes = 0;
		bweak;
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 0, 12):
	case IP_VEWSION(11, 0, 13):
		eww = psp_init_sos_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_ta_micwocode(psp, ucode_pwefix);
		bweak;
	case IP_VEWSION(11, 5, 0):
		eww = psp_init_asd_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_toc_micwocode(psp, ucode_pwefix);
		bweak;
	defauwt:
		BUG();
	}

	wetuwn eww;
}

static int psp_v11_0_wait_fow_bootwoadew(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	int wet;
	int wetwy_woop;

	fow (wetwy_woop = 0; wetwy_woop < 10; wetwy_woop++) {
		/* Wait fow bootwoadew to signify that is
		    weady having bit 31 of C2PMSG_35 set to 1 */
		wet = psp_wait_fow(psp,
				   SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
				   0x80000000,
				   0x80000000,
				   fawse);

		if (wet == 0)
			wetuwn 0;
	}

	wetuwn wet;
}

static boow psp_v11_0_is_sos_awive(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t sow_weg;

	sow_weg = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);

	wetuwn sow_weg != 0x0;
}

static int psp_v11_0_bootwoadew_woad_component(stwuct psp_context  	*psp,
					       stwuct psp_bin_desc 	*bin_desc,
					       enum psp_bootwoadew_cmd  bw_cmd)
{
	int wet;
	uint32_t psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	if (psp_v11_0_is_sos_awive(psp))
		wetuwn 0;

	wet = psp_v11_0_wait_fow_bootwoadew(psp);
	if (wet)
		wetuwn wet;

	/* Copy PSP System Dwivew binawy to memowy */
	psp_copy_fw(psp, bin_desc->stawt_addw, bin_desc->size_bytes);

	/* Pwovide the sys dwivew to bootwoadew */
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = bw_cmd;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	wet = psp_v11_0_wait_fow_bootwoadew(psp);

	wetuwn wet;
}

static int psp_v11_0_bootwoadew_woad_kdb(stwuct psp_context *psp)
{
	wetuwn psp_v11_0_bootwoadew_woad_component(psp, &psp->kdb, PSP_BW__WOAD_KEY_DATABASE);
}

static int psp_v11_0_bootwoadew_woad_spw(stwuct psp_context *psp)
{
	wetuwn psp_v11_0_bootwoadew_woad_component(psp, &psp->spw, PSP_BW__WOAD_TOS_SPW_TABWE);
}

static int psp_v11_0_bootwoadew_woad_sysdwv(stwuct psp_context *psp)
{
	wetuwn psp_v11_0_bootwoadew_woad_component(psp, &psp->sys, PSP_BW__WOAD_SYSDWV);
}

static int psp_v11_0_bootwoadew_woad_sos(stwuct psp_context *psp)
{
	int wet;
	unsigned int psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	if (psp_v11_0_is_sos_awive(psp))
		wetuwn 0;

	wet = psp_v11_0_wait_fow_bootwoadew(psp);
	if (wet)
		wetuwn wet;

	/* Copy Secuwe OS binawy to PSP memowy */
	psp_copy_fw(psp, psp->sos.stawt_addw, psp->sos.size_bytes);

	/* Pwovide the PSP secuwe OS to bootwoadew */
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = PSP_BW__WOAD_SOSDWV;
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_81),
			   WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81),
			   0, twue);

	wetuwn wet;
}

static int psp_v11_0_wing_stop(stwuct psp_context *psp,
			      enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Wwite the wing destwoy command*/
	if (amdgpu_swiov_vf(adev))
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
				     GFX_CTWW_CMD_ID_DESTWOY_GPCOM_WING);
	ewse
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64,
				     GFX_CTWW_CMD_ID_DESTWOY_WINGS);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);

	/* Wait fow wesponse fwag (bit 31) */
	if (amdgpu_swiov_vf(adev))
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x80000000, fawse);
	ewse
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);

	wetuwn wet;
}

static int psp_v11_0_wing_cweate(stwuct psp_context *psp,
				enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		wing->wing_wptw = 0;
		wet = psp_v11_0_wing_stop(psp, wing_type);
		if (wet) {
			DWM_EWWOW("psp_v11_0_wing_stop_swiov faiwed!\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_102 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_103 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_103, psp_wing_weg);

		/* Wwite the wing initiawization command to C2PMSG_101 */
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
					     GFX_CTWW_CMD_ID_INIT_GPCOM_WING);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_101 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x8000FFFF, fawse);

	} ewse {
		/* Wait fow sOS weady fow wing cweation */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
		if (wet) {
			DWM_EWWOW("Faiwed to wait fow sOS weady fow wing cweation\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_69 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_70 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, psp_wing_weg);
		/* Wwite size of wing to C2PMSG_71 */
		psp_wing_weg = wing->wing_size;
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_71, psp_wing_weg);
		/* Wwite the wing initiawization command to C2PMSG_64 */
		psp_wing_weg = wing_type;
		psp_wing_weg = psp_wing_weg << 16;
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_wing_weg);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_64 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x8000FFFF, fawse);
	}

	wetuwn wet;
}


static int psp_v11_0_wing_destwoy(stwuct psp_context *psp,
				 enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	wet = psp_v11_0_wing_stop(psp, wing_type);
	if (wet)
		DWM_EWWOW("Faiw to stop psp wing\n");

	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.wbuf,
			      &wing->wing_mem_mc_addw,
			      (void **)&wing->wing_mem);

	wetuwn wet;
}

static int psp_v11_0_mode1_weset(stwuct psp_context *psp)
{
	int wet;
	uint32_t offset;
	stwuct amdgpu_device *adev = psp->adev;

	offset = SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64);

	wet = psp_wait_fow(psp, offset, 0x80000000, 0x8000FFFF, fawse);

	if (wet) {
		DWM_INFO("psp is not wowking cowwectwy befowe mode1 weset!\n");
		wetuwn -EINVAW;
	}

	/*send the mode 1 weset command*/
	WWEG32(offset, GFX_CTWW_CMD_ID_MODE1_WST);

	msweep(500);

	offset = SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_33);

	wet = psp_wait_fow(psp, offset, 0x80000000, 0x80000000, fawse);

	if (wet) {
		DWM_INFO("psp mode 1 weset faiwed!\n");
		wetuwn -EINVAW;
	}

	DWM_INFO("psp mode1 weset succeed \n");

	wetuwn 0;
}

static int psp_v11_0_memowy_twaining_send_msg(stwuct psp_context *psp, int msg)
{
	int wet;
	int i;
	uint32_t data_32;
	int max_wait;
	stwuct amdgpu_device *adev = psp->adev;

	data_32 = (psp->mem_twain_ctx.c2p_twain_data_offset >> 20);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36, data_32);
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, msg);

	max_wait = MEM_TWAIN_SEND_MSG_TIMEOUT_US / adev->usec_timeout;
	fow (i = 0; i < max_wait; i++) {
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
				   0x80000000, 0x80000000, fawse);
		if (wet == 0)
			bweak;
	}
	if (i < max_wait)
		wet = 0;
	ewse
		wet = -ETIME;

	DWM_DEBUG("twaining %s %s, cost %d @ %d ms\n",
		  (msg == PSP_BW__DWAM_SHOWT_TWAIN) ? "showt" : "wong",
		  (wet == 0) ? "succeed" : "faiwed",
		  i, adev->usec_timeout/1000);
	wetuwn wet;
}

/*
 * save and westowe pwocess
 */
static int psp_v11_0_memowy_twaining(stwuct psp_context *psp, uint32_t ops)
{
	stwuct psp_memowy_twaining_context *ctx = &psp->mem_twain_ctx;
	uint32_t *pcache = (uint32_t *)ctx->sys_cache;
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t p2c_headew[4];
	uint32_t sz;
	void *buf;
	int wet, idx;

	if (ctx->init == PSP_MEM_TWAIN_NOT_SUPPOWT) {
		DWM_DEBUG("Memowy twaining is not suppowted.\n");
		wetuwn 0;
	} ewse if (ctx->init != PSP_MEM_TWAIN_INIT_SUCCESS) {
		DWM_EWWOW("Memowy twaining initiawization faiwuwe.\n");
		wetuwn -EINVAW;
	}

	if (psp_v11_0_is_sos_awive(psp)) {
		DWM_DEBUG("SOS is awive, skip memowy twaining.\n");
		wetuwn 0;
	}

	amdgpu_device_vwam_access(adev, ctx->p2c_twain_data_offset, p2c_headew, sizeof(p2c_headew), fawse);
	DWM_DEBUG("sys_cache[%08x,%08x,%08x,%08x] p2c_headew[%08x,%08x,%08x,%08x]\n",
		  pcache[0], pcache[1], pcache[2], pcache[3],
		  p2c_headew[0], p2c_headew[1], p2c_headew[2], p2c_headew[3]);

	if (ops & PSP_MEM_TWAIN_SEND_SHOWT_MSG) {
		DWM_DEBUG("Showt twaining depends on westowe.\n");
		ops |= PSP_MEM_TWAIN_WESTOWE;
	}

	if ((ops & PSP_MEM_TWAIN_WESTOWE) &&
	    pcache[0] != MEM_TWAIN_SYSTEM_SIGNATUWE) {
		DWM_DEBUG("sys_cache[0] is invawid, westowe depends on save.\n");
		ops |= PSP_MEM_TWAIN_SAVE;
	}

	if (p2c_headew[0] == MEM_TWAIN_SYSTEM_SIGNATUWE &&
	    !(pcache[0] == MEM_TWAIN_SYSTEM_SIGNATUWE &&
	      pcache[3] == p2c_headew[3])) {
		DWM_DEBUG("sys_cache is invawid ow out-of-date, need save twaining data to sys_cache.\n");
		ops |= PSP_MEM_TWAIN_SAVE;
	}

	if ((ops & PSP_MEM_TWAIN_SAVE) &&
	    p2c_headew[0] != MEM_TWAIN_SYSTEM_SIGNATUWE) {
		DWM_DEBUG("p2c_headew[0] is invawid, save depends on wong twaining.\n");
		ops |= PSP_MEM_TWAIN_SEND_WONG_MSG;
	}

	if (ops & PSP_MEM_TWAIN_SEND_WONG_MSG) {
		ops &= ~PSP_MEM_TWAIN_SEND_SHOWT_MSG;
		ops |= PSP_MEM_TWAIN_SAVE;
	}

	DWM_DEBUG("Memowy twaining ops:%x.\n", ops);

	if (ops & PSP_MEM_TWAIN_SEND_WONG_MSG) {
		/*
		 * Wong twaining wiww encwoach a cewtain amount on the bottom of VWAM;
		 * save the content fwom the bottom of VWAM to system memowy
		 * befowe twaining, and westowe it aftew twaining to avoid
		 * VWAM cowwuption.
		 */
		sz = GDDW6_MEM_TWAINING_ENCWOACHED_SIZE;

		if (adev->gmc.visibwe_vwam_size < sz || !adev->mman.apew_base_kaddw) {
			DWM_EWWOW("visibwe_vwam_size %wwx ow apew_base_kaddw %p is not initiawized.\n",
				  adev->gmc.visibwe_vwam_size,
				  adev->mman.apew_base_kaddw);
			wetuwn -EINVAW;
		}

		buf = vmawwoc(sz);
		if (!buf) {
			DWM_EWWOW("faiwed to awwocate system memowy.\n");
			wetuwn -ENOMEM;
		}

		if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
			memcpy_fwomio(buf, adev->mman.apew_base_kaddw, sz);
			wet = psp_v11_0_memowy_twaining_send_msg(psp, PSP_BW__DWAM_WONG_TWAIN);
			if (wet) {
				DWM_EWWOW("Send wong twaining msg faiwed.\n");
				vfwee(buf);
				dwm_dev_exit(idx);
				wetuwn wet;
			}

			memcpy_toio(adev->mman.apew_base_kaddw, buf, sz);
			adev->hdp.funcs->fwush_hdp(adev, NUWW);
			vfwee(buf);
			dwm_dev_exit(idx);
		} ewse {
			vfwee(buf);
			wetuwn -ENODEV;
		}
	}

	if (ops & PSP_MEM_TWAIN_SAVE) {
		amdgpu_device_vwam_access(psp->adev, ctx->p2c_twain_data_offset, ctx->sys_cache, ctx->twain_data_size, fawse);
	}

	if (ops & PSP_MEM_TWAIN_WESTOWE) {
		amdgpu_device_vwam_access(psp->adev, ctx->c2p_twain_data_offset, ctx->sys_cache, ctx->twain_data_size, twue);
	}

	if (ops & PSP_MEM_TWAIN_SEND_SHOWT_MSG) {
		wet = psp_v11_0_memowy_twaining_send_msg(psp, (amdgpu_fowce_wong_twaining > 0) ?
							 PSP_BW__DWAM_WONG_TWAIN : PSP_BW__DWAM_SHOWT_TWAIN);
		if (wet) {
			DWM_EWWOW("send twaining msg faiwed.\n");
			wetuwn wet;
		}
	}
	ctx->twaining_cnt++;
	wetuwn 0;
}

static uint32_t psp_v11_0_wing_get_wptw(stwuct psp_context *psp)
{
	uint32_t data;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev))
		data = psp->km_wing.wing_wptw;
	ewse
		data = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67);

	wetuwn data;
}

static void psp_v11_0_wing_set_wptw(stwuct psp_context *psp, uint32_t vawue)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, vawue);
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101, GFX_CTWW_CMD_ID_CONSUME_CMD);
		psp->km_wing.wing_wptw = vawue;
	} ewse
		WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67, vawue);
}

static int psp_v11_0_woad_usbc_pd_fw(stwuct psp_context *psp, uint64_t fw_pwi_mc_addw)
{
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t weg_status;
	int wet, i = 0;

	/*
	 * WFB addwess which is awigned to 1MB addwess and has to be
	 * wight-shifted by 20 so that WFB addwess can be passed on a 32-bit C2P
	 * wegistew
	 */
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36, (fw_pwi_mc_addw >> 20));

	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			     0x80000000, 0x80000000, fawse);
	if (wet)
		wetuwn wet;

	/* Fiweup intewwupt so PSP can pick up the addwess */
	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, (GFX_CMD_USB_PD_USE_WFB << 16));

	/* FW woad takes vewy wong time */
	do {
		msweep(1000);
		weg_status = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35);

		if (weg_status & 0x80000000)
			goto done;

	} whiwe (++i < USBC_PD_POWWING_WIMIT_S);

	wetuwn -ETIME;
done:

	if ((weg_status & 0xFFFF) != 0) {
		DWM_EWWOW("Addwess woad faiwed - MP0_SMN_C2PMSG_35.Bits [15:0] = 0x%04x\n",
				weg_status & 0xFFFF);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int psp_v11_0_wead_usbc_pd_fw(stwuct psp_context *psp, uint32_t *fw_vew)
{
	stwuct amdgpu_device *adev = psp->adev;
	int wet;

	WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, C2PMSG_CMD_GFX_USB_PD_FW_VEW);

	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
				     0x80000000, 0x80000000, fawse);
	if (!wet)
		*fw_vew = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36);

	wetuwn wet;
}

static const stwuct psp_funcs psp_v11_0_funcs = {
	.init_micwocode = psp_v11_0_init_micwocode,
	.bootwoadew_woad_kdb = psp_v11_0_bootwoadew_woad_kdb,
	.bootwoadew_woad_spw = psp_v11_0_bootwoadew_woad_spw,
	.bootwoadew_woad_sysdwv = psp_v11_0_bootwoadew_woad_sysdwv,
	.bootwoadew_woad_sos = psp_v11_0_bootwoadew_woad_sos,
	.wing_cweate = psp_v11_0_wing_cweate,
	.wing_stop = psp_v11_0_wing_stop,
	.wing_destwoy = psp_v11_0_wing_destwoy,
	.mode1_weset = psp_v11_0_mode1_weset,
	.mem_twaining = psp_v11_0_memowy_twaining,
	.wing_get_wptw = psp_v11_0_wing_get_wptw,
	.wing_set_wptw = psp_v11_0_wing_set_wptw,
	.woad_usbc_pd_fw = psp_v11_0_woad_usbc_pd_fw,
	.wead_usbc_pd_fw = psp_v11_0_wead_usbc_pd_fw
};

void psp_v11_0_set_psp_funcs(stwuct psp_context *psp)
{
	psp->funcs = &psp_v11_0_funcs;
}
