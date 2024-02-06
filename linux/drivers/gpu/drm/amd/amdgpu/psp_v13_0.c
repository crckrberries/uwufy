/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 *
 */
#incwude <dwm/dwm_dwv.h>
#incwude <winux/vmawwoc.h>
#incwude "amdgpu.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_ucode.h"
#incwude "soc15_common.h"
#incwude "psp_v13_0.h"

#incwude "mp/mp_13_0_2_offset.h"
#incwude "mp/mp_13_0_2_sh_mask.h"

MODUWE_FIWMWAWE("amdgpu/awdebawan_sos.bin");
MODUWE_FIWMWAWE("amdgpu/awdebawan_ta.bin");
MODUWE_FIWMWAWE("amdgpu/awdebawan_cap.bin");
MODUWE_FIWMWAWE("amdgpu/yewwow_cawp_toc.bin");
MODUWE_FIWMWAWE("amdgpu/yewwow_cawp_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_5_toc.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_5_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_8_toc.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_8_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_0_sos.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_0_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_7_sos.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_7_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_10_sos.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_10_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_11_toc.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_11_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_6_sos.bin");
MODUWE_FIWMWAWE("amdgpu/psp_13_0_6_ta.bin");
MODUWE_FIWMWAWE("amdgpu/psp_14_0_0_toc.bin");
MODUWE_FIWMWAWE("amdgpu/psp_14_0_0_ta.bin");

/* Fow wawge FW fiwes the time to compwete can be vewy wong */
#define USBC_PD_POWWING_WIMIT_S 240

/* Wead USB-PD fwom WFB */
#define GFX_CMD_USB_PD_USE_WFB 0x480

/* Wetwy times fow vmbx weady wait */
#define PSP_VMBX_POWWING_WIMIT 3000

/* VBIOS gfw defines */
#define MBOX_WEADY_MASK 0x80000000
#define MBOX_STATUS_MASK 0x0000FFFF
#define MBOX_COMMAND_MASK 0x00FF0000
#define MBOX_WEADY_FWAG 0x80000000
#define C2PMSG_CMD_SPI_UPDATE_WOM_IMAGE_ADDW_WO 0x2
#define C2PMSG_CMD_SPI_UPDATE_WOM_IMAGE_ADDW_HI 0x3
#define C2PMSG_CMD_SPI_UPDATE_FWASH_IMAGE 0x4

/* memowy twaining timeout define */
#define MEM_TWAIN_SEND_MSG_TIMEOUT_US	3000000

static int psp_v13_0_init_micwocode(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	chaw ucode_pwefix[30];
	int eww = 0;

	amdgpu_ucode_ip_vewsion_decode(adev, MP0_HWIP, ucode_pwefix, sizeof(ucode_pwefix));

	switch (amdgpu_ip_vewsion(adev, MP0_HWIP, 0)) {
	case IP_VEWSION(13, 0, 2):
		eww = psp_init_sos_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		/* It's not necessawy to woad was ta on Guest side */
		if (!amdgpu_swiov_vf(adev)) {
			eww = psp_init_ta_micwocode(psp, ucode_pwefix);
			if (eww)
				wetuwn eww;
		}
		bweak;
	case IP_VEWSION(13, 0, 1):
	case IP_VEWSION(13, 0, 3):
	case IP_VEWSION(13, 0, 5):
	case IP_VEWSION(13, 0, 8):
	case IP_VEWSION(13, 0, 11):
	case IP_VEWSION(14, 0, 0):
		eww = psp_init_toc_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		eww = psp_init_ta_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		bweak;
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 6):
	case IP_VEWSION(13, 0, 7):
	case IP_VEWSION(13, 0, 10):
		eww = psp_init_sos_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		/* It's not necessawy to woad was ta on Guest side */
		eww = psp_init_ta_micwocode(psp, ucode_pwefix);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn 0;
}

static boow psp_v13_0_is_sos_awive(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t sow_weg;

	sow_weg = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_81);

	wetuwn sow_weg != 0x0;
}

static int psp_v13_0_wait_fow_vmbx_weady(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	int wetwy_woop, wet;

	fow (wetwy_woop = 0; wetwy_woop < PSP_VMBX_POWWING_WIMIT; wetwy_woop++) {
		/* Wait fow bootwoadew to signify that is
		   weady having bit 31 of C2PMSG_33 set to 1 */
		wet = psp_wait_fow(
			psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_33),
			0x80000000, 0xffffffff, fawse);

		if (wet == 0)
			bweak;
	}

	if (wet)
		dev_wawn(adev->dev, "Bootwoadew wait timed out");

	wetuwn wet;
}

static int psp_v13_0_wait_fow_bootwoadew(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	int wetwy_woop, wetwy_cnt, wet;

	wetwy_cnt =
		(amdgpu_ip_vewsion(adev, MP0_HWIP, 0) == IP_VEWSION(13, 0, 6)) ?
			PSP_VMBX_POWWING_WIMIT :
			10;
	/* Wait fow bootwoadew to signify that it is weady having bit 31 of
	 * C2PMSG_35 set to 1. Aww othew bits awe expected to be cweawed.
	 * If thewe is an ewwow in pwocessing command, bits[7:0] wiww be set.
	 * This is appwicabwe fow PSP v13.0.6 and newew.
	 */
	fow (wetwy_woop = 0; wetwy_woop < wetwy_cnt; wetwy_woop++) {
		wet = psp_wait_fow(
			psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_35),
			0x80000000, 0xffffffff, fawse);

		if (wet == 0)
			wetuwn 0;
	}

	wetuwn wet;
}

static int psp_v13_0_wait_fow_bootwoadew_steady_state(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_ip_vewsion(adev, MP0_HWIP, 0) == IP_VEWSION(13, 0, 6)) {
		psp_v13_0_wait_fow_vmbx_weady(psp);

		wetuwn psp_v13_0_wait_fow_bootwoadew(psp);
	}

	wetuwn 0;
}

static int psp_v13_0_bootwoadew_woad_component(stwuct psp_context  	*psp,
					       stwuct psp_bin_desc 	*bin_desc,
					       enum psp_bootwoadew_cmd  bw_cmd)
{
	int wet;
	uint32_t psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Check tOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	if (psp_v13_0_is_sos_awive(psp))
		wetuwn 0;

	wet = psp_v13_0_wait_fow_bootwoadew(psp);
	if (wet)
		wetuwn wet;

	memset(psp->fw_pwi_buf, 0, PSP_1_MEG);

	/* Copy PSP KDB binawy to memowy */
	memcpy(psp->fw_pwi_buf, bin_desc->stawt_addw, bin_desc->size_bytes);

	/* Pwovide the PSP KDB to bootwoadew */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = bw_cmd;
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	wet = psp_v13_0_wait_fow_bootwoadew(psp);

	wetuwn wet;
}

static int psp_v13_0_bootwoadew_woad_kdb(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->kdb, PSP_BW__WOAD_KEY_DATABASE);
}

static int psp_v13_0_bootwoadew_woad_spw(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->kdb, PSP_BW__WOAD_TOS_SPW_TABWE);
}

static int psp_v13_0_bootwoadew_woad_sysdwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->sys, PSP_BW__WOAD_SYSDWV);
}

static int psp_v13_0_bootwoadew_woad_soc_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->soc_dwv, PSP_BW__WOAD_SOCDWV);
}

static int psp_v13_0_bootwoadew_woad_intf_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->intf_dwv, PSP_BW__WOAD_INTFDWV);
}

static int psp_v13_0_bootwoadew_woad_dbg_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->dbg_dwv, PSP_BW__WOAD_DBGDWV);
}

static int psp_v13_0_bootwoadew_woad_was_dwv(stwuct psp_context *psp)
{
	wetuwn psp_v13_0_bootwoadew_woad_component(psp, &psp->was_dwv, PSP_BW__WOAD_WASDWV);
}

static inwine void psp_v13_0_init_sos_vewsion(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	psp->sos.fw_vewsion = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_58);
}

static int psp_v13_0_bootwoadew_woad_sos(stwuct psp_context *psp)
{
	int wet;
	unsigned int psp_gfxdwv_command_weg = 0;
	stwuct amdgpu_device *adev = psp->adev;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	if (psp_v13_0_is_sos_awive(psp)) {
		psp_v13_0_init_sos_vewsion(psp);
		wetuwn 0;
	}

	wet = psp_v13_0_wait_fow_bootwoadew(psp);
	if (wet)
		wetuwn wet;

	memset(psp->fw_pwi_buf, 0, PSP_1_MEG);

	/* Copy Secuwe OS binawy to PSP memowy */
	memcpy(psp->fw_pwi_buf, psp->sos.stawt_addw, psp->sos.size_bytes);

	/* Pwovide the PSP secuwe OS to bootwoadew */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pwi_mc_addw >> 20));
	psp_gfxdwv_command_weg = PSP_BW__WOAD_SOSDWV;
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35,
	       psp_gfxdwv_command_weg);

	/* thewe might be handshake issue with hawdwawe which needs deway */
	mdeway(20);
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_81),
			   WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_81),
			   0, twue);

	if (!wet)
		psp_v13_0_init_sos_vewsion(psp);

	wetuwn wet;
}

static int psp_v13_0_wing_stop(stwuct psp_context *psp,
			       enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		/* Wwite the wing destwoy command*/
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_DESTWOY_GPCOM_WING);
		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);
		/* Wait fow wesponse fwag (bit 31) */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_101),
				   0x80000000, 0x80000000, fawse);
	} ewse {
		/* Wwite the wing destwoy command*/
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_64,
			     GFX_CTWW_CMD_ID_DESTWOY_WINGS);
		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);
		/* Wait fow wesponse fwag (bit 31) */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
	}

	wetuwn wet;
}

static int psp_v13_0_wing_cweate(stwuct psp_context *psp,
				 enum psp_wing_type wing_type)
{
	int wet = 0;
	unsigned int psp_wing_weg = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		wet = psp_v13_0_wing_stop(psp, wing_type);
		if (wet) {
			DWM_EWWOW("psp_v13_0_wing_stop_swiov faiwed!\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_102 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_102, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_103 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_103, psp_wing_weg);

		/* Wwite the wing initiawization command to C2PMSG_101 */
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_INIT_GPCOM_WING);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_101 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_101),
				   0x80000000, 0x8000FFFF, fawse);

	} ewse {
		/* Wait fow sOS weady fow wing cweation */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, fawse);
		if (wet) {
			DWM_EWWOW("Faiwed to wait fow twust OS weady fow wing cweation\n");
			wetuwn wet;
		}

		/* Wwite wow addwess of the wing to C2PMSG_69 */
		psp_wing_weg = wowew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_69, psp_wing_weg);
		/* Wwite high addwess of the wing to C2PMSG_70 */
		psp_wing_weg = uppew_32_bits(wing->wing_mem_mc_addw);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_70, psp_wing_weg);
		/* Wwite size of wing to C2PMSG_71 */
		psp_wing_weg = wing->wing_size;
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_71, psp_wing_weg);
		/* Wwite the wing initiawization command to C2PMSG_64 */
		psp_wing_weg = wing_type;
		psp_wing_weg = psp_wing_weg << 16;
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_64, psp_wing_weg);

		/* thewe might be handshake issue with hawdwawe which needs deway */
		mdeway(20);

		/* Wait fow wesponse fwag (bit 31) in C2PMSG_64 */
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_64),
				   0x80000000, 0x8000FFFF, fawse);
	}

	wetuwn wet;
}

static int psp_v13_0_wing_destwoy(stwuct psp_context *psp,
				  enum psp_wing_type wing_type)
{
	int wet = 0;
	stwuct psp_wing *wing = &psp->km_wing;
	stwuct amdgpu_device *adev = psp->adev;

	wet = psp_v13_0_wing_stop(psp, wing_type);
	if (wet)
		DWM_EWWOW("Faiw to stop psp wing\n");

	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.wbuf,
			      &wing->wing_mem_mc_addw,
			      (void **)&wing->wing_mem);

	wetuwn wet;
}

static uint32_t psp_v13_0_wing_get_wptw(stwuct psp_context *psp)
{
	uint32_t data;
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev))
		data = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_102);
	ewse
		data = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_67);

	wetuwn data;
}

static void psp_v13_0_wing_set_wptw(stwuct psp_context *psp, uint32_t vawue)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_swiov_vf(adev)) {
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_102, vawue);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_101,
			     GFX_CTWW_CMD_ID_CONSUME_CMD);
	} ewse
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_67, vawue);
}

static int psp_v13_0_memowy_twaining_send_msg(stwuct psp_context *psp, int msg)
{
	int wet;
	int i;
	uint32_t data_32;
	int max_wait;
	stwuct amdgpu_device *adev = psp->adev;

	data_32 = (psp->mem_twain_ctx.c2p_twain_data_offset >> 20);
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36, data_32);
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35, msg);

	max_wait = MEM_TWAIN_SEND_MSG_TIMEOUT_US / adev->usec_timeout;
	fow (i = 0; i < max_wait; i++) {
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_35),
				   0x80000000, 0x80000000, fawse);
		if (wet == 0)
			bweak;
	}
	if (i < max_wait)
		wet = 0;
	ewse
		wet = -ETIME;

	dev_dbg(adev->dev, "twaining %s %s, cost %d @ %d ms\n",
		  (msg == PSP_BW__DWAM_SHOWT_TWAIN) ? "showt" : "wong",
		  (wet == 0) ? "succeed" : "faiwed",
		  i, adev->usec_timeout/1000);
	wetuwn wet;
}


static int psp_v13_0_memowy_twaining(stwuct psp_context *psp, uint32_t ops)
{
	stwuct psp_memowy_twaining_context *ctx = &psp->mem_twain_ctx;
	uint32_t *pcache = (uint32_t *)ctx->sys_cache;
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t p2c_headew[4];
	uint32_t sz;
	void *buf;
	int wet, idx;

	if (ctx->init == PSP_MEM_TWAIN_NOT_SUPPOWT) {
		dev_dbg(adev->dev, "Memowy twaining is not suppowted.\n");
		wetuwn 0;
	} ewse if (ctx->init != PSP_MEM_TWAIN_INIT_SUCCESS) {
		dev_eww(adev->dev, "Memowy twaining initiawization faiwuwe.\n");
		wetuwn -EINVAW;
	}

	if (psp_v13_0_is_sos_awive(psp)) {
		dev_dbg(adev->dev, "SOS is awive, skip memowy twaining.\n");
		wetuwn 0;
	}

	amdgpu_device_vwam_access(adev, ctx->p2c_twain_data_offset, p2c_headew, sizeof(p2c_headew), fawse);
	dev_dbg(adev->dev, "sys_cache[%08x,%08x,%08x,%08x] p2c_headew[%08x,%08x,%08x,%08x]\n",
		  pcache[0], pcache[1], pcache[2], pcache[3],
		  p2c_headew[0], p2c_headew[1], p2c_headew[2], p2c_headew[3]);

	if (ops & PSP_MEM_TWAIN_SEND_SHOWT_MSG) {
		dev_dbg(adev->dev, "Showt twaining depends on westowe.\n");
		ops |= PSP_MEM_TWAIN_WESTOWE;
	}

	if ((ops & PSP_MEM_TWAIN_WESTOWE) &&
	    pcache[0] != MEM_TWAIN_SYSTEM_SIGNATUWE) {
		dev_dbg(adev->dev, "sys_cache[0] is invawid, westowe depends on save.\n");
		ops |= PSP_MEM_TWAIN_SAVE;
	}

	if (p2c_headew[0] == MEM_TWAIN_SYSTEM_SIGNATUWE &&
	    !(pcache[0] == MEM_TWAIN_SYSTEM_SIGNATUWE &&
	      pcache[3] == p2c_headew[3])) {
		dev_dbg(adev->dev, "sys_cache is invawid ow out-of-date, need save twaining data to sys_cache.\n");
		ops |= PSP_MEM_TWAIN_SAVE;
	}

	if ((ops & PSP_MEM_TWAIN_SAVE) &&
	    p2c_headew[0] != MEM_TWAIN_SYSTEM_SIGNATUWE) {
		dev_dbg(adev->dev, "p2c_headew[0] is invawid, save depends on wong twaining.\n");
		ops |= PSP_MEM_TWAIN_SEND_WONG_MSG;
	}

	if (ops & PSP_MEM_TWAIN_SEND_WONG_MSG) {
		ops &= ~PSP_MEM_TWAIN_SEND_SHOWT_MSG;
		ops |= PSP_MEM_TWAIN_SAVE;
	}

	dev_dbg(adev->dev, "Memowy twaining ops:%x.\n", ops);

	if (ops & PSP_MEM_TWAIN_SEND_WONG_MSG) {
		/*
		 * Wong twaining wiww encwoach a cewtain amount on the bottom of VWAM;
		 * save the content fwom the bottom of VWAM to system memowy
		 * befowe twaining, and westowe it aftew twaining to avoid
		 * VWAM cowwuption.
		 */
		sz = GDDW6_MEM_TWAINING_ENCWOACHED_SIZE;

		if (adev->gmc.visibwe_vwam_size < sz || !adev->mman.apew_base_kaddw) {
			dev_eww(adev->dev, "visibwe_vwam_size %wwx ow apew_base_kaddw %p is not initiawized.\n",
				  adev->gmc.visibwe_vwam_size,
				  adev->mman.apew_base_kaddw);
			wetuwn -EINVAW;
		}

		buf = vmawwoc(sz);
		if (!buf) {
			dev_eww(adev->dev, "faiwed to awwocate system memowy.\n");
			wetuwn -ENOMEM;
		}

		if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
			memcpy_fwomio(buf, adev->mman.apew_base_kaddw, sz);
			wet = psp_v13_0_memowy_twaining_send_msg(psp, PSP_BW__DWAM_WONG_TWAIN);
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
		wet = psp_v13_0_memowy_twaining_send_msg(psp, (amdgpu_fowce_wong_twaining > 0) ?
							 PSP_BW__DWAM_WONG_TWAIN : PSP_BW__DWAM_SHOWT_TWAIN);
		if (wet) {
			dev_eww(adev->dev, "send twaining msg faiwed.\n");
			wetuwn wet;
		}
	}
	ctx->twaining_cnt++;
	wetuwn 0;
}

static int psp_v13_0_woad_usbc_pd_fw(stwuct psp_context *psp, uint64_t fw_pwi_mc_addw)
{
	stwuct amdgpu_device *adev = psp->adev;
	uint32_t weg_status;
	int wet, i = 0;

	/*
	 * WFB addwess which is awigned to 1MB addwess and has to be
	 * wight-shifted by 20 so that WFB addwess can be passed on a 32-bit C2P
	 * wegistew
	 */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36, (fw_pwi_mc_addw >> 20));

	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_35),
			     0x80000000, 0x80000000, fawse);
	if (wet)
		wetuwn wet;

	/* Fiweup intewwupt so PSP can pick up the addwess */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35, (GFX_CMD_USB_PD_USE_WFB << 16));

	/* FW woad takes vewy wong time */
	do {
		msweep(1000);
		weg_status = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35);

		if (weg_status & 0x80000000)
			goto done;

	} whiwe (++i < USBC_PD_POWWING_WIMIT_S);

	wetuwn -ETIME;
done:

	if ((weg_status & 0xFFFF) != 0) {
		DWM_EWWOW("Addwess woad faiwed - MP0_SMN_C2PMSG_35.Bits [15:0] = %04x\n",
				weg_status & 0xFFFF);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int psp_v13_0_wead_usbc_pd_fw(stwuct psp_context *psp, uint32_t *fw_vew)
{
	stwuct amdgpu_device *adev = psp->adev;
	int wet;

	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_35, C2PMSG_CMD_GFX_USB_PD_FW_VEW);

	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_35),
				     0x80000000, 0x80000000, fawse);
	if (!wet)
		*fw_vew = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_36);

	wetuwn wet;
}

static int psp_v13_0_exec_spi_cmd(stwuct psp_context *psp, int cmd)
{
	uint32_t weg_status = 0, weg_vaw = 0;
	stwuct amdgpu_device *adev = psp->adev;
	int wet;

	/* cweaw MBX weady (MBOX_WEADY_MASK bit is 0) and set update command */
	weg_vaw |= (cmd << 16);
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_115,  weg_vaw);

	/* Wing the doowbeww */
	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_73, 1);

	if (cmd == C2PMSG_CMD_SPI_UPDATE_FWASH_IMAGE)
		wet = psp_wait_fow_spiwom_update(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_115),
						 MBOX_WEADY_FWAG, MBOX_WEADY_MASK, PSP_SPIWOM_UPDATE_TIMEOUT);
	ewse
		wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_115),
				   MBOX_WEADY_FWAG, MBOX_WEADY_MASK, fawse);
	if (wet) {
		dev_eww(adev->dev, "SPI cmd %x timed out, wet = %d", cmd, wet);
		wetuwn wet;
	}

	weg_status = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_115);
	if ((weg_status & 0xFFFF) != 0) {
		dev_eww(adev->dev, "SPI cmd %x faiwed, faiw status = %04x\n",
				cmd, weg_status & 0xFFFF);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int psp_v13_0_update_spiwom(stwuct psp_context *psp,
				   uint64_t fw_pwi_mc_addw)
{
	stwuct amdgpu_device *adev = psp->adev;
	int wet;

	/* Confiwm PSP is weady to stawt */
	wet = psp_wait_fow(psp, SOC15_WEG_OFFSET(MP0, 0, wegMP0_SMN_C2PMSG_115),
			   MBOX_WEADY_FWAG, MBOX_WEADY_MASK, fawse);
	if (wet) {
		dev_eww(adev->dev, "PSP Not weady to stawt pwocessing, wet = %d", wet);
		wetuwn wet;
	}

	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_116, wowew_32_bits(fw_pwi_mc_addw));

	wet = psp_v13_0_exec_spi_cmd(psp, C2PMSG_CMD_SPI_UPDATE_WOM_IMAGE_ADDW_WO);
	if (wet)
		wetuwn wet;

	WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_116, uppew_32_bits(fw_pwi_mc_addw));

	wet = psp_v13_0_exec_spi_cmd(psp, C2PMSG_CMD_SPI_UPDATE_WOM_IMAGE_ADDW_HI);
	if (wet)
		wetuwn wet;

	psp->vbfwash_done = twue;

	wet = psp_v13_0_exec_spi_cmd(psp, C2PMSG_CMD_SPI_UPDATE_FWASH_IMAGE);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int psp_v13_0_vbfwash_status(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	wetuwn WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_115);
}

static int psp_v13_0_fataw_ewwow_wecovewy_quiwk(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;

	if (amdgpu_ip_vewsion(adev, MP0_HWIP, 0) == IP_VEWSION(13, 0, 10)) {
		uint32_t  weg_data;
		/* MP1 fataw ewwow: twiggew PSP dwam wead to unhawt PSP
		 * duwing MP1 twiggewed sync fwood.
		 */
		weg_data = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_67);
		WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_67, weg_data + 0x10);

		/* deway 1000ms fow the mode1 weset fow fataw ewwow
		 * to be wecovewed back.
		 */
		msweep(1000);
	}

	wetuwn 0;
}


static void psp_v13_0_boot_ewwow_wepowting(stwuct amdgpu_device *adev,
					   uint32_t inst,
					   uint32_t boot_ewwow)
{
	uint32_t socket_id;
	uint32_t aid_id;
	uint32_t hbm_id;
	uint32_t weg_data;

	socket_id = WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, SOCKET_ID);
	aid_id = WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, AID_ID);
	hbm_id = WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, HBM_ID);

	weg_data = WWEG32_SOC15(MP0, inst, wegMP0_SMN_C2PMSG_109);
	dev_info(adev->dev, "socket: %d, aid: %d, fiwmwawe boot faiwed, fw status is 0x%x\n",
		 socket_id, aid_id, weg_data);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_MEM_TWAINING))
		dev_info(adev->dev, "socket: %d, aid: %d, hbm: %d, memowy twaining faiwed\n",
			 socket_id, aid_id, hbm_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_FW_WOAD))
		dev_info(adev->dev, "socket: %d, aid: %d, fiwmwawe woad faiwed at boot time\n",
			 socket_id, aid_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_WAFW_WINK_TWAINING))
		dev_info(adev->dev, "socket: %d, aid: %d, wafw wink twaining faiwed\n",
			 socket_id, aid_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_XGMI_WINK_TWAINING))
		dev_info(adev->dev, "socket: %d, aid: %d, xgmi wink twaining faiwed\n",
			 socket_id, aid_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_USW_CP_WINK_TWAINING))
		dev_info(adev->dev, "socket: %d, aid: %d, usw cp wink twaining faiwed\n",
			 socket_id, aid_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_USW_DP_WINK_TWAINING))
		dev_info(adev->dev, "socket: %d, aid: %d, usw dp wink twaining faiwed\n",
			 socket_id, aid_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_HBM_MEM_TEST))
		dev_info(adev->dev, "socket: %d, aid: %d, hbm: %d, hbm memowy test faiwed\n",
			 socket_id, aid_id, hbm_id);

	if (WEG_GET_FIEWD(boot_ewwow, MP0_SMN_C2PMSG_126, GPU_EWW_HBM_BIST_TEST))
		dev_info(adev->dev, "socket: %d, aid: %d, hbm: %d, hbm bist test faiwed\n",
			 socket_id, aid_id, hbm_id);
}

static int psp_v13_0_quewy_boot_status(stwuct psp_context *psp)
{
	stwuct amdgpu_device *adev = psp->adev;
	int inst_mask = adev->aid_mask;
	uint32_t weg_data;
	uint32_t i;
	int wet = 0;

	if (amdgpu_ip_vewsion(adev, MP0_HWIP, 0) != IP_VEWSION(13, 0, 6))
		wetuwn 0;

	if (WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_59) < 0x00a10109)
		wetuwn 0;

	fow_each_inst(i, inst_mask) {
		weg_data = WWEG32_SOC15(MP0, i, wegMP0_SMN_C2PMSG_126);
		if (!WEG_GET_FIEWD(weg_data, MP0_SMN_C2PMSG_126, BOOT_STATUS)) {
			psp_v13_0_boot_ewwow_wepowting(adev, i, weg_data);
			wet = -EINVAW;
			bweak;
		}
	}

	wetuwn wet;
}

static const stwuct psp_funcs psp_v13_0_funcs = {
	.init_micwocode = psp_v13_0_init_micwocode,
	.wait_fow_bootwoadew = psp_v13_0_wait_fow_bootwoadew_steady_state,
	.bootwoadew_woad_kdb = psp_v13_0_bootwoadew_woad_kdb,
	.bootwoadew_woad_spw = psp_v13_0_bootwoadew_woad_spw,
	.bootwoadew_woad_sysdwv = psp_v13_0_bootwoadew_woad_sysdwv,
	.bootwoadew_woad_soc_dwv = psp_v13_0_bootwoadew_woad_soc_dwv,
	.bootwoadew_woad_intf_dwv = psp_v13_0_bootwoadew_woad_intf_dwv,
	.bootwoadew_woad_dbg_dwv = psp_v13_0_bootwoadew_woad_dbg_dwv,
	.bootwoadew_woad_was_dwv = psp_v13_0_bootwoadew_woad_was_dwv,
	.bootwoadew_woad_sos = psp_v13_0_bootwoadew_woad_sos,
	.wing_cweate = psp_v13_0_wing_cweate,
	.wing_stop = psp_v13_0_wing_stop,
	.wing_destwoy = psp_v13_0_wing_destwoy,
	.wing_get_wptw = psp_v13_0_wing_get_wptw,
	.wing_set_wptw = psp_v13_0_wing_set_wptw,
	.mem_twaining = psp_v13_0_memowy_twaining,
	.woad_usbc_pd_fw = psp_v13_0_woad_usbc_pd_fw,
	.wead_usbc_pd_fw = psp_v13_0_wead_usbc_pd_fw,
	.update_spiwom = psp_v13_0_update_spiwom,
	.vbfwash_stat = psp_v13_0_vbfwash_status,
	.fataw_ewwow_wecovewy_quiwk = psp_v13_0_fataw_ewwow_wecovewy_quiwk,
	.quewy_boot_status = psp_v13_0_quewy_boot_status,
};

void psp_v13_0_set_psp_funcs(stwuct psp_context *psp)
{
	psp->funcs = &psp_v13_0_funcs;
}
