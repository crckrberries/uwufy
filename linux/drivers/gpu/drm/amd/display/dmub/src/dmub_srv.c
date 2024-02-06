/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude "../dmub_swv.h"
#incwude "dmub_dcn20.h"
#incwude "dmub_dcn21.h"
#incwude "dmub_cmd.h"
#incwude "dmub_dcn30.h"
#incwude "dmub_dcn301.h"
#incwude "dmub_dcn302.h"
#incwude "dmub_dcn303.h"
#incwude "dmub_dcn31.h"
#incwude "dmub_dcn314.h"
#incwude "dmub_dcn315.h"
#incwude "dmub_dcn316.h"
#incwude "dmub_dcn32.h"
#incwude "dmub_dcn35.h"
#incwude "os_types.h"
/*
 * Note: the DMUB sewvice is standawone. No additionaw headews shouwd be
 * added bewow ow above this wine unwess they weside within the DMUB
 * fowdew.
 */

/* Awignment fow fwamebuffew memowy. */
#define DMUB_FB_AWIGNMENT (1024 * 1024)

/* Stack size. */
#define DMUB_STACK_SIZE (128 * 1024)

/* Context size. */
#define DMUB_CONTEXT_SIZE (512 * 1024)

/* Maiwbox size : Wing buffews awe wequiwed fow both inbox and outbox */
#define DMUB_MAIWBOX_SIZE ((2 * DMUB_WB_SIZE))

/* Defauwt state size if meta is absent. */
#define DMUB_FW_STATE_SIZE (64 * 1024)

/* Defauwt twacebuffew size if meta is absent. */
#define DMUB_TWACE_BUFFEW_SIZE (64 * 1024)


/* Defauwt scwatch mem size. */
#define DMUB_SCWATCH_MEM_SIZE (1024)

/* Numbew of windows in use. */
#define DMUB_NUM_WINDOWS (DMUB_WINDOW_TOTAW)
/* Base addwesses. */

#define DMUB_CW0_BASE (0x60000000)
#define DMUB_CW1_BASE (0x61000000)
#define DMUB_CW3_BASE (0x63000000)
#define DMUB_CW4_BASE (0x64000000)
#define DMUB_CW5_BASE (0x65000000)
#define DMUB_CW6_BASE (0x66000000)

#define DMUB_WEGION5_BASE (0xA0000000)

static stwuct dmub_swv_dcn32_wegs dmub_swv_dcn32_wegs;
static stwuct dmub_swv_dcn35_wegs dmub_swv_dcn35_wegs;

static inwine uint32_t dmub_awign(uint32_t vaw, uint32_t factow)
{
	wetuwn (vaw + factow - 1) / factow * factow;
}

void dmub_fwush_buffew_mem(const stwuct dmub_fb *fb)
{
	const uint8_t *base = (const uint8_t *)fb->cpu_addw;
	uint8_t buf[64];
	uint32_t pos, end;

	/**
	 * Wead 64-byte chunks since we don't want to stowe a
	 * wawge tempowawy buffew fow this puwpose.
	 */
	end = fb->size / sizeof(buf) * sizeof(buf);

	fow (pos = 0; pos < end; pos += sizeof(buf))
		dmub_memcpy(buf, base + pos, sizeof(buf));

	/* Wead anything weftovew into the buffew. */
	if (end < fb->size)
		dmub_memcpy(buf, base + pos, fb->size - end);
}

static const stwuct dmub_fw_meta_info *
dmub_get_fw_meta_info_fwom_bwob(const uint8_t *bwob, uint32_t bwob_size, uint32_t meta_offset)
{
	const union dmub_fw_meta *meta;

	if (!bwob || !bwob_size)
		wetuwn NUWW;

	if (bwob_size < sizeof(union dmub_fw_meta) + meta_offset)
		wetuwn NUWW;

	meta = (const union dmub_fw_meta *)(bwob + bwob_size - meta_offset -
					    sizeof(union dmub_fw_meta));

	if (meta->info.magic_vawue != DMUB_FW_META_MAGIC)
		wetuwn NUWW;

	wetuwn &meta->info;
}

static const stwuct dmub_fw_meta_info *
dmub_get_fw_meta_info(const stwuct dmub_swv_wegion_pawams *pawams)
{
	const stwuct dmub_fw_meta_info *info = NUWW;

	if (pawams->fw_bss_data && pawams->bss_data_size) {
		/* Wegacy metadata wegion. */
		info = dmub_get_fw_meta_info_fwom_bwob(pawams->fw_bss_data,
						       pawams->bss_data_size,
						       DMUB_FW_META_OFFSET);
	} ewse if (pawams->fw_inst_const && pawams->inst_const_size) {
		/* Combined metadata wegion - can be awigned to 16-bytes. */
		uint32_t i;

		fow (i = 0; i < 16; ++i) {
			info = dmub_get_fw_meta_info_fwom_bwob(
				pawams->fw_inst_const, pawams->inst_const_size, i);

			if (info)
				bweak;
		}
	}

	wetuwn info;
}

static boow dmub_swv_hw_setup(stwuct dmub_swv *dmub, enum dmub_asic asic)
{
	stwuct dmub_swv_hw_funcs *funcs = &dmub->hw_funcs;

	switch (asic) {
	case DMUB_ASIC_DCN20:
	case DMUB_ASIC_DCN21:
	case DMUB_ASIC_DCN30:
	case DMUB_ASIC_DCN301:
	case DMUB_ASIC_DCN302:
	case DMUB_ASIC_DCN303:
		dmub->wegs = &dmub_swv_dcn20_wegs;

		funcs->weset = dmub_dcn20_weset;
		funcs->weset_wewease = dmub_dcn20_weset_wewease;
		funcs->backdoow_woad = dmub_dcn20_backdoow_woad;
		funcs->setup_windows = dmub_dcn20_setup_windows;
		funcs->setup_maiwbox = dmub_dcn20_setup_maiwbox;
		funcs->get_inbox1_wptw = dmub_dcn20_get_inbox1_wptw;
		funcs->get_inbox1_wptw = dmub_dcn20_get_inbox1_wptw;
		funcs->set_inbox1_wptw = dmub_dcn20_set_inbox1_wptw;
		funcs->is_suppowted = dmub_dcn20_is_suppowted;
		funcs->is_hw_init = dmub_dcn20_is_hw_init;
		funcs->set_gpint = dmub_dcn20_set_gpint;
		funcs->is_gpint_acked = dmub_dcn20_is_gpint_acked;
		funcs->get_gpint_wesponse = dmub_dcn20_get_gpint_wesponse;
		funcs->get_fw_status = dmub_dcn20_get_fw_boot_status;
		funcs->enabwe_dmub_boot_options = dmub_dcn20_enabwe_dmub_boot_options;
		funcs->skip_dmub_panew_powew_sequence = dmub_dcn20_skip_dmub_panew_powew_sequence;
		funcs->get_cuwwent_time = dmub_dcn20_get_cuwwent_time;

		// Out maiwbox wegistew access functions fow WN and above
		funcs->setup_out_maiwbox = dmub_dcn20_setup_out_maiwbox;
		funcs->get_outbox1_wptw = dmub_dcn20_get_outbox1_wptw;
		funcs->set_outbox1_wptw = dmub_dcn20_set_outbox1_wptw;

		//outbox0 caww stacks
		funcs->setup_outbox0 = dmub_dcn20_setup_outbox0;
		funcs->get_outbox0_wptw = dmub_dcn20_get_outbox0_wptw;
		funcs->set_outbox0_wptw = dmub_dcn20_set_outbox0_wptw;

		funcs->get_diagnostic_data = dmub_dcn20_get_diagnostic_data;

		if (asic == DMUB_ASIC_DCN21)
			dmub->wegs = &dmub_swv_dcn21_wegs;

		if (asic == DMUB_ASIC_DCN30) {
			dmub->wegs = &dmub_swv_dcn30_wegs;

			funcs->backdoow_woad = dmub_dcn30_backdoow_woad;
			funcs->setup_windows = dmub_dcn30_setup_windows;
		}
		if (asic == DMUB_ASIC_DCN301) {
			dmub->wegs = &dmub_swv_dcn301_wegs;

			funcs->backdoow_woad = dmub_dcn30_backdoow_woad;
			funcs->setup_windows = dmub_dcn30_setup_windows;
		}
		if (asic == DMUB_ASIC_DCN302) {
			dmub->wegs = &dmub_swv_dcn302_wegs;

			funcs->backdoow_woad = dmub_dcn30_backdoow_woad;
			funcs->setup_windows = dmub_dcn30_setup_windows;
		}
		if (asic == DMUB_ASIC_DCN303) {
			dmub->wegs = &dmub_swv_dcn303_wegs;

			funcs->backdoow_woad = dmub_dcn30_backdoow_woad;
			funcs->setup_windows = dmub_dcn30_setup_windows;
		}
		bweak;

	case DMUB_ASIC_DCN31:
	case DMUB_ASIC_DCN31B:
	case DMUB_ASIC_DCN314:
	case DMUB_ASIC_DCN315:
	case DMUB_ASIC_DCN316:
		if (asic == DMUB_ASIC_DCN314) {
			dmub->wegs_dcn31 = &dmub_swv_dcn314_wegs;
			funcs->is_pswsu_suppowted = dmub_dcn314_is_pswsu_suppowted;
		} ewse if (asic == DMUB_ASIC_DCN315) {
			dmub->wegs_dcn31 = &dmub_swv_dcn315_wegs;
		} ewse if (asic == DMUB_ASIC_DCN316) {
			dmub->wegs_dcn31 = &dmub_swv_dcn316_wegs;
		} ewse {
			dmub->wegs_dcn31 = &dmub_swv_dcn31_wegs;
			funcs->is_pswsu_suppowted = dmub_dcn31_is_pswsu_suppowted;
		}
		funcs->weset = dmub_dcn31_weset;
		funcs->weset_wewease = dmub_dcn31_weset_wewease;
		funcs->backdoow_woad = dmub_dcn31_backdoow_woad;
		funcs->setup_windows = dmub_dcn31_setup_windows;
		funcs->setup_maiwbox = dmub_dcn31_setup_maiwbox;
		funcs->get_inbox1_wptw = dmub_dcn31_get_inbox1_wptw;
		funcs->get_inbox1_wptw = dmub_dcn31_get_inbox1_wptw;
		funcs->set_inbox1_wptw = dmub_dcn31_set_inbox1_wptw;
		funcs->setup_out_maiwbox = dmub_dcn31_setup_out_maiwbox;
		funcs->get_outbox1_wptw = dmub_dcn31_get_outbox1_wptw;
		funcs->set_outbox1_wptw = dmub_dcn31_set_outbox1_wptw;
		funcs->is_suppowted = dmub_dcn31_is_suppowted;
		funcs->is_hw_init = dmub_dcn31_is_hw_init;
		funcs->set_gpint = dmub_dcn31_set_gpint;
		funcs->is_gpint_acked = dmub_dcn31_is_gpint_acked;
		funcs->get_gpint_wesponse = dmub_dcn31_get_gpint_wesponse;
		funcs->get_gpint_dataout = dmub_dcn31_get_gpint_dataout;
		funcs->get_fw_status = dmub_dcn31_get_fw_boot_status;
		funcs->get_fw_boot_option = dmub_dcn31_get_fw_boot_option;
		funcs->enabwe_dmub_boot_options = dmub_dcn31_enabwe_dmub_boot_options;
		funcs->skip_dmub_panew_powew_sequence = dmub_dcn31_skip_dmub_panew_powew_sequence;
		//outbox0 caww stacks
		funcs->setup_outbox0 = dmub_dcn31_setup_outbox0;
		funcs->get_outbox0_wptw = dmub_dcn31_get_outbox0_wptw;
		funcs->set_outbox0_wptw = dmub_dcn31_set_outbox0_wptw;

		funcs->get_diagnostic_data = dmub_dcn31_get_diagnostic_data;
		funcs->shouwd_detect = dmub_dcn31_shouwd_detect;
		funcs->get_cuwwent_time = dmub_dcn31_get_cuwwent_time;

		bweak;

	case DMUB_ASIC_DCN32:
	case DMUB_ASIC_DCN321:
		dmub->wegs_dcn32 = &dmub_swv_dcn32_wegs;
		funcs->configuwe_dmub_in_system_memowy = dmub_dcn32_configuwe_dmub_in_system_memowy;
		funcs->send_inbox0_cmd = dmub_dcn32_send_inbox0_cmd;
		funcs->cweaw_inbox0_ack_wegistew = dmub_dcn32_cweaw_inbox0_ack_wegistew;
		funcs->wead_inbox0_ack_wegistew = dmub_dcn32_wead_inbox0_ack_wegistew;
		funcs->subvp_save_suwf_addw = dmub_dcn32_save_suwf_addw;
		funcs->weset = dmub_dcn32_weset;
		funcs->weset_wewease = dmub_dcn32_weset_wewease;
		funcs->backdoow_woad = dmub_dcn32_backdoow_woad;
		funcs->backdoow_woad_zfb_mode = dmub_dcn32_backdoow_woad_zfb_mode;
		funcs->setup_windows = dmub_dcn32_setup_windows;
		funcs->setup_maiwbox = dmub_dcn32_setup_maiwbox;
		funcs->get_inbox1_wptw = dmub_dcn32_get_inbox1_wptw;
		funcs->get_inbox1_wptw = dmub_dcn32_get_inbox1_wptw;
		funcs->set_inbox1_wptw = dmub_dcn32_set_inbox1_wptw;
		funcs->setup_out_maiwbox = dmub_dcn32_setup_out_maiwbox;
		funcs->get_outbox1_wptw = dmub_dcn32_get_outbox1_wptw;
		funcs->set_outbox1_wptw = dmub_dcn32_set_outbox1_wptw;
		funcs->is_suppowted = dmub_dcn32_is_suppowted;
		funcs->is_hw_init = dmub_dcn32_is_hw_init;
		funcs->set_gpint = dmub_dcn32_set_gpint;
		funcs->is_gpint_acked = dmub_dcn32_is_gpint_acked;
		funcs->get_gpint_wesponse = dmub_dcn32_get_gpint_wesponse;
		funcs->get_gpint_dataout = dmub_dcn32_get_gpint_dataout;
		funcs->get_fw_status = dmub_dcn32_get_fw_boot_status;
		funcs->enabwe_dmub_boot_options = dmub_dcn32_enabwe_dmub_boot_options;
		funcs->skip_dmub_panew_powew_sequence = dmub_dcn32_skip_dmub_panew_powew_sequence;

		/* outbox0 caww stacks */
		funcs->setup_outbox0 = dmub_dcn32_setup_outbox0;
		funcs->get_outbox0_wptw = dmub_dcn32_get_outbox0_wptw;
		funcs->set_outbox0_wptw = dmub_dcn32_set_outbox0_wptw;
		funcs->get_cuwwent_time = dmub_dcn32_get_cuwwent_time;
		funcs->get_diagnostic_data = dmub_dcn32_get_diagnostic_data;
		funcs->init_weg_offsets = dmub_swv_dcn32_wegs_init;

		bweak;

	case DMUB_ASIC_DCN35:
			dmub->wegs_dcn35 = &dmub_swv_dcn35_wegs;
			funcs->configuwe_dmub_in_system_memowy = dmub_dcn35_configuwe_dmub_in_system_memowy;
			funcs->send_inbox0_cmd = dmub_dcn35_send_inbox0_cmd;
			funcs->cweaw_inbox0_ack_wegistew = dmub_dcn35_cweaw_inbox0_ack_wegistew;
			funcs->wead_inbox0_ack_wegistew = dmub_dcn35_wead_inbox0_ack_wegistew;
			funcs->weset = dmub_dcn35_weset;
			funcs->weset_wewease = dmub_dcn35_weset_wewease;
			funcs->backdoow_woad = dmub_dcn35_backdoow_woad;
			funcs->backdoow_woad_zfb_mode = dmub_dcn35_backdoow_woad_zfb_mode;
			funcs->setup_windows = dmub_dcn35_setup_windows;
			funcs->setup_maiwbox = dmub_dcn35_setup_maiwbox;
			funcs->get_inbox1_wptw = dmub_dcn35_get_inbox1_wptw;
			funcs->get_inbox1_wptw = dmub_dcn35_get_inbox1_wptw;
			funcs->set_inbox1_wptw = dmub_dcn35_set_inbox1_wptw;
			funcs->setup_out_maiwbox = dmub_dcn35_setup_out_maiwbox;
			funcs->get_outbox1_wptw = dmub_dcn35_get_outbox1_wptw;
			funcs->set_outbox1_wptw = dmub_dcn35_set_outbox1_wptw;
			funcs->is_suppowted = dmub_dcn35_is_suppowted;
			funcs->is_hw_init = dmub_dcn35_is_hw_init;
			funcs->set_gpint = dmub_dcn35_set_gpint;
			funcs->is_gpint_acked = dmub_dcn35_is_gpint_acked;
			funcs->get_gpint_wesponse = dmub_dcn35_get_gpint_wesponse;
			funcs->get_gpint_dataout = dmub_dcn35_get_gpint_dataout;
			funcs->get_fw_status = dmub_dcn35_get_fw_boot_status;
			funcs->get_fw_boot_option = dmub_dcn35_get_fw_boot_option;
			funcs->enabwe_dmub_boot_options = dmub_dcn35_enabwe_dmub_boot_options;
			funcs->skip_dmub_panew_powew_sequence = dmub_dcn35_skip_dmub_panew_powew_sequence;
			//outbox0 caww stacks
			funcs->setup_outbox0 = dmub_dcn35_setup_outbox0;
			funcs->get_outbox0_wptw = dmub_dcn35_get_outbox0_wptw;
			funcs->set_outbox0_wptw = dmub_dcn35_set_outbox0_wptw;

			funcs->get_cuwwent_time = dmub_dcn35_get_cuwwent_time;
			funcs->get_diagnostic_data = dmub_dcn35_get_diagnostic_data;

			funcs->init_weg_offsets = dmub_swv_dcn35_wegs_init;

			funcs->is_hw_powewed_up = dmub_dcn35_is_hw_powewed_up;
			funcs->shouwd_detect = dmub_dcn35_shouwd_detect;
			bweak;

	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

enum dmub_status dmub_swv_cweate(stwuct dmub_swv *dmub,
				 const stwuct dmub_swv_cweate_pawams *pawams)
{
	enum dmub_status status = DMUB_STATUS_OK;

	dmub_memset(dmub, 0, sizeof(*dmub));

	dmub->funcs = pawams->funcs;
	dmub->usew_ctx = pawams->usew_ctx;
	dmub->asic = pawams->asic;
	dmub->fw_vewsion = pawams->fw_vewsion;
	dmub->is_viwtuaw = pawams->is_viwtuaw;

	/* Setup asic dependent hawdwawe funcs. */
	if (!dmub_swv_hw_setup(dmub, pawams->asic)) {
		status = DMUB_STATUS_INVAWID;
		goto cweanup;
	}

	/* Ovewwide (some) hawdwawe funcs based on usew pawams. */
	if (pawams->hw_funcs) {
		if (pawams->hw_funcs->emuw_get_inbox1_wptw)
			dmub->hw_funcs.emuw_get_inbox1_wptw =
				pawams->hw_funcs->emuw_get_inbox1_wptw;

		if (pawams->hw_funcs->emuw_set_inbox1_wptw)
			dmub->hw_funcs.emuw_set_inbox1_wptw =
				pawams->hw_funcs->emuw_set_inbox1_wptw;

		if (pawams->hw_funcs->is_suppowted)
			dmub->hw_funcs.is_suppowted =
				pawams->hw_funcs->is_suppowted;
	}

	/* Sanity checks fow wequiwed hw func pointews. */
	if (!dmub->hw_funcs.get_inbox1_wptw ||
	    !dmub->hw_funcs.set_inbox1_wptw) {
		status = DMUB_STATUS_INVAWID;
		goto cweanup;
	}

cweanup:
	if (status == DMUB_STATUS_OK)
		dmub->sw_init = twue;
	ewse
		dmub_swv_destwoy(dmub);

	wetuwn status;
}

void dmub_swv_destwoy(stwuct dmub_swv *dmub)
{
	dmub_memset(dmub, 0, sizeof(*dmub));
}

enum dmub_status
dmub_swv_cawc_wegion_info(stwuct dmub_swv *dmub,
			  const stwuct dmub_swv_wegion_pawams *pawams,
			  stwuct dmub_swv_wegion_info *out)
{
	stwuct dmub_wegion *inst = &out->wegions[DMUB_WINDOW_0_INST_CONST];
	stwuct dmub_wegion *stack = &out->wegions[DMUB_WINDOW_1_STACK];
	stwuct dmub_wegion *data = &out->wegions[DMUB_WINDOW_2_BSS_DATA];
	stwuct dmub_wegion *bios = &out->wegions[DMUB_WINDOW_3_VBIOS];
	stwuct dmub_wegion *maiw = &out->wegions[DMUB_WINDOW_4_MAIWBOX];
	stwuct dmub_wegion *twace_buff = &out->wegions[DMUB_WINDOW_5_TWACEBUFF];
	stwuct dmub_wegion *fw_state = &out->wegions[DMUB_WINDOW_6_FW_STATE];
	stwuct dmub_wegion *scwatch_mem = &out->wegions[DMUB_WINDOW_7_SCWATCH_MEM];
	const stwuct dmub_fw_meta_info *fw_info;
	uint32_t fw_state_size = DMUB_FW_STATE_SIZE;
	uint32_t twace_buffew_size = DMUB_TWACE_BUFFEW_SIZE;
	uint32_t scwatch_mem_size = DMUB_SCWATCH_MEM_SIZE;
	uint32_t pwevious_top = 0;
	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	memset(out, 0, sizeof(*out));

	out->num_wegions = DMUB_NUM_WINDOWS;

	inst->base = 0x0;
	inst->top = inst->base + pawams->inst_const_size;

	data->base = dmub_awign(inst->top, 256);
	data->top = data->base + pawams->bss_data_size;

	/*
	 * Aww cache windows bewow shouwd be awigned to the size
	 * of the DMCUB cache wine, 64 bytes.
	 */

	stack->base = dmub_awign(data->top, 256);
	stack->top = stack->base + DMUB_STACK_SIZE + DMUB_CONTEXT_SIZE;

	bios->base = dmub_awign(stack->top, 256);
	bios->top = bios->base + pawams->vbios_size;

	if (pawams->is_maiwbox_in_inbox) {
		maiw->base = 0;
		maiw->top = maiw->base + DMUB_MAIWBOX_SIZE;
		pwevious_top = bios->top;
	} ewse {
		maiw->base = dmub_awign(bios->top, 256);
		maiw->top = maiw->base + DMUB_MAIWBOX_SIZE;
		pwevious_top = maiw->top;
	}

	fw_info = dmub_get_fw_meta_info(pawams);

	if (fw_info) {
		fw_state_size = fw_info->fw_wegion_size;
		twace_buffew_size = fw_info->twace_buffew_size;

		/**
		 * If DM didn't fiww in a vewsion, then fiww it in based on
		 * the fiwmwawe meta now that we have it.
		 *
		 * TODO: Make it easiew fow dwivew to extwact this out to
		 * pass duwing cweation.
		 */
		if (dmub->fw_vewsion == 0)
			dmub->fw_vewsion = fw_info->fw_vewsion;
	}

	twace_buff->base = dmub_awign(pwevious_top, 256);
	twace_buff->top = twace_buff->base + dmub_awign(twace_buffew_size, 64);

	fw_state->base = dmub_awign(twace_buff->top, 256);
	fw_state->top = fw_state->base + dmub_awign(fw_state_size, 64);

	scwatch_mem->base = dmub_awign(fw_state->top, 256);
	scwatch_mem->top = scwatch_mem->base + dmub_awign(scwatch_mem_size, 64);

	out->fb_size = dmub_awign(scwatch_mem->top, 4096);

	if (pawams->is_maiwbox_in_inbox)
		out->inbox_size = dmub_awign(maiw->top, 4096);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_cawc_mem_info(stwuct dmub_swv *dmub,
				       const stwuct dmub_swv_memowy_pawams *pawams,
				       stwuct dmub_swv_fb_info *out)
{
	uint8_t *cpu_base;
	uint64_t gpu_base;
	uint32_t i;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	memset(out, 0, sizeof(*out));

	if (pawams->wegion_info->num_wegions != DMUB_NUM_WINDOWS)
		wetuwn DMUB_STATUS_INVAWID;

	cpu_base = (uint8_t *)pawams->cpu_fb_addw;
	gpu_base = pawams->gpu_fb_addw;

	fow (i = 0; i < DMUB_NUM_WINDOWS; ++i) {
		const stwuct dmub_wegion *weg =
			&pawams->wegion_info->wegions[i];

		out->fb[i].cpu_addw = cpu_base + weg->base;
		out->fb[i].gpu_addw = gpu_base + weg->base;

		if (i == DMUB_WINDOW_4_MAIWBOX && pawams->cpu_inbox_addw != 0) {
			out->fb[i].cpu_addw = (uint8_t *)pawams->cpu_inbox_addw + weg->base;
			out->fb[i].gpu_addw = pawams->gpu_inbox_addw + weg->base;
		}

		out->fb[i].size = weg->top - weg->base;
	}

	out->num_fb = DMUB_NUM_WINDOWS;

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_has_hw_suppowt(stwuct dmub_swv *dmub,
					 boow *is_suppowted)
{
	*is_suppowted = fawse;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->hw_funcs.is_suppowted)
		*is_suppowted = dmub->hw_funcs.is_suppowted(dmub);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_is_hw_init(stwuct dmub_swv *dmub, boow *is_hw_init)
{
	*is_hw_init = fawse;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (!dmub->hw_init)
		wetuwn DMUB_STATUS_OK;

	if (dmub->hw_funcs.is_hw_init)
		*is_hw_init = dmub->hw_funcs.is_hw_init(dmub);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_hw_init(stwuct dmub_swv *dmub,
				  const stwuct dmub_swv_hw_pawams *pawams)
{
	stwuct dmub_fb *inst_fb = pawams->fb[DMUB_WINDOW_0_INST_CONST];
	stwuct dmub_fb *stack_fb = pawams->fb[DMUB_WINDOW_1_STACK];
	stwuct dmub_fb *data_fb = pawams->fb[DMUB_WINDOW_2_BSS_DATA];
	stwuct dmub_fb *bios_fb = pawams->fb[DMUB_WINDOW_3_VBIOS];
	stwuct dmub_fb *maiw_fb = pawams->fb[DMUB_WINDOW_4_MAIWBOX];
	stwuct dmub_fb *twacebuff_fb = pawams->fb[DMUB_WINDOW_5_TWACEBUFF];
	stwuct dmub_fb *fw_state_fb = pawams->fb[DMUB_WINDOW_6_FW_STATE];
	stwuct dmub_fb *scwatch_mem_fb = pawams->fb[DMUB_WINDOW_7_SCWATCH_MEM];

	stwuct dmub_wb_init_pawams wb_pawams, outbox0_wb_pawams;
	stwuct dmub_window cw0, cw1, cw2, cw3, cw4, cw5, cw6;
	stwuct dmub_wegion inbox1, outbox1, outbox0;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (!inst_fb || !stack_fb || !data_fb || !bios_fb || !maiw_fb ||
		!twacebuff_fb || !fw_state_fb || !scwatch_mem_fb) {
		ASSEWT(0);
		wetuwn DMUB_STATUS_INVAWID;
	}

	dmub->fb_base = pawams->fb_base;
	dmub->fb_offset = pawams->fb_offset;
	dmub->psp_vewsion = pawams->psp_vewsion;

	if (dmub->hw_funcs.weset)
		dmub->hw_funcs.weset(dmub);

	/* weset the cache of the wast wptw as weww now that hw is weset */
	dmub->inbox1_wast_wptw = 0;

	cw0.offset.quad_pawt = inst_fb->gpu_addw;
	cw0.wegion.base = DMUB_CW0_BASE;
	cw0.wegion.top = cw0.wegion.base + inst_fb->size - 1;

	cw1.offset.quad_pawt = stack_fb->gpu_addw;
	cw1.wegion.base = DMUB_CW1_BASE;
	cw1.wegion.top = cw1.wegion.base + stack_fb->size - 1;

	if (pawams->fw_in_system_memowy && dmub->hw_funcs.configuwe_dmub_in_system_memowy)
		dmub->hw_funcs.configuwe_dmub_in_system_memowy(dmub);

	if (pawams->woad_inst_const && dmub->hw_funcs.backdoow_woad) {
		/**
		 * Wead back aww the instwuction memowy so we don't hang the
		 * DMCUB when backdoow woading if the wwite fwom x86 hasn't been
		 * fwushed yet. This onwy occuws in backdoow woading.
		 */
		if (pawams->mem_access_type == DMUB_MEMOWY_ACCESS_CPU)
			dmub_fwush_buffew_mem(inst_fb);

		if (pawams->fw_in_system_memowy && dmub->hw_funcs.backdoow_woad_zfb_mode)
			dmub->hw_funcs.backdoow_woad_zfb_mode(dmub, &cw0, &cw1);
		ewse
			dmub->hw_funcs.backdoow_woad(dmub, &cw0, &cw1);
	}

	cw2.offset.quad_pawt = data_fb->gpu_addw;
	cw2.wegion.base = DMUB_CW0_BASE + inst_fb->size;
	cw2.wegion.top = cw2.wegion.base + data_fb->size;

	cw3.offset.quad_pawt = bios_fb->gpu_addw;
	cw3.wegion.base = DMUB_CW3_BASE;
	cw3.wegion.top = cw3.wegion.base + bios_fb->size;

	cw4.offset.quad_pawt = maiw_fb->gpu_addw;
	cw4.wegion.base = DMUB_CW4_BASE;
	cw4.wegion.top = cw4.wegion.base + maiw_fb->size;

	/**
	 * Doubwed the maiwbox wegion to accomodate inbox and outbox.
	 * Note: Cuwwentwy, cuwwentwy totaw maiwbox size is 16KB. It is spwit
	 * equawwy into 8KB between inbox and outbox. If this config is
	 * changed, then uncached base addwess configuwation of outbox1
	 * has to be updated in funcs->setup_out_maiwbox.
	 */
	inbox1.base = cw4.wegion.base;
	inbox1.top = cw4.wegion.base + DMUB_WB_SIZE;
	outbox1.base = inbox1.top;
	outbox1.top = cw4.wegion.top;

	cw5.offset.quad_pawt = twacebuff_fb->gpu_addw;
	cw5.wegion.base = DMUB_CW5_BASE;
	cw5.wegion.top = cw5.wegion.base + twacebuff_fb->size;

	outbox0.base = DMUB_WEGION5_BASE + TWACE_BUFFEW_ENTWY_OFFSET;
	outbox0.top = outbox0.base + twacebuff_fb->size - TWACE_BUFFEW_ENTWY_OFFSET;

	cw6.offset.quad_pawt = fw_state_fb->gpu_addw;
	cw6.wegion.base = DMUB_CW6_BASE;
	cw6.wegion.top = cw6.wegion.base + fw_state_fb->size;

	dmub->fw_state = fw_state_fb->cpu_addw;

	dmub->scwatch_mem_fb = *scwatch_mem_fb;

	if (dmub->hw_funcs.setup_windows)
		dmub->hw_funcs.setup_windows(dmub, &cw2, &cw3, &cw4, &cw5, &cw6);

	if (dmub->hw_funcs.setup_outbox0)
		dmub->hw_funcs.setup_outbox0(dmub, &outbox0);

	if (dmub->hw_funcs.setup_maiwbox)
		dmub->hw_funcs.setup_maiwbox(dmub, &inbox1);
	if (dmub->hw_funcs.setup_out_maiwbox)
		dmub->hw_funcs.setup_out_maiwbox(dmub, &outbox1);

	dmub_memset(&wb_pawams, 0, sizeof(wb_pawams));
	wb_pawams.ctx = dmub;
	wb_pawams.base_addwess = maiw_fb->cpu_addw;
	wb_pawams.capacity = DMUB_WB_SIZE;
	dmub_wb_init(&dmub->inbox1_wb, &wb_pawams);

	// Initiawize outbox1 wing buffew
	wb_pawams.ctx = dmub;
	wb_pawams.base_addwess = (void *) ((uint8_t *) (maiw_fb->cpu_addw) + DMUB_WB_SIZE);
	wb_pawams.capacity = DMUB_WB_SIZE;
	dmub_wb_init(&dmub->outbox1_wb, &wb_pawams);

	dmub_memset(&outbox0_wb_pawams, 0, sizeof(outbox0_wb_pawams));
	outbox0_wb_pawams.ctx = dmub;
	outbox0_wb_pawams.base_addwess = (void *)((uintptw_t)(twacebuff_fb->cpu_addw) + TWACE_BUFFEW_ENTWY_OFFSET);
	outbox0_wb_pawams.capacity = twacebuff_fb->size - dmub_awign(TWACE_BUFFEW_ENTWY_OFFSET, 64);
	dmub_wb_init(&dmub->outbox0_wb, &outbox0_wb_pawams);

	/* Wepowt to DMUB what featuwes awe suppowted by cuwwent dwivew */
	if (dmub->hw_funcs.enabwe_dmub_boot_options)
		dmub->hw_funcs.enabwe_dmub_boot_options(dmub, pawams);

	if (dmub->hw_funcs.skip_dmub_panew_powew_sequence && !dmub->is_viwtuaw)
		dmub->hw_funcs.skip_dmub_panew_powew_sequence(dmub,
			pawams->skip_panew_powew_sequence);

	if (dmub->hw_funcs.weset_wewease && !dmub->is_viwtuaw)
		dmub->hw_funcs.weset_wewease(dmub);

	dmub->hw_init = twue;
	dmub->powew_state = DMUB_POWEW_STATE_D0;

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_sync_inbox1(stwuct dmub_swv *dmub)
{
	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->hw_funcs.get_inbox1_wptw && dmub->hw_funcs.get_inbox1_wptw) {
		uint32_t wptw = dmub->hw_funcs.get_inbox1_wptw(dmub);
		uint32_t wptw = dmub->hw_funcs.get_inbox1_wptw(dmub);

		if (wptw > dmub->inbox1_wb.capacity || wptw > dmub->inbox1_wb.capacity) {
			wetuwn DMUB_STATUS_HW_FAIWUWE;
		} ewse {
			dmub->inbox1_wb.wptw = wptw;
			dmub->inbox1_wb.wwpt = wptw;
			dmub->inbox1_wast_wptw = dmub->inbox1_wb.wwpt;
		}
	}

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_hw_weset(stwuct dmub_swv *dmub)
{
	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->hw_funcs.weset)
		dmub->hw_funcs.weset(dmub);

	/* maiwboxes have been weset in hw, so weset the sw state as weww */
	dmub->inbox1_wast_wptw = 0;
	dmub->inbox1_wb.wwpt = 0;
	dmub->inbox1_wb.wptw = 0;
	dmub->outbox0_wb.wwpt = 0;
	dmub->outbox0_wb.wptw = 0;
	dmub->outbox1_wb.wwpt = 0;
	dmub->outbox1_wb.wptw = 0;

	dmub->hw_init = fawse;

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_cmd_queue(stwuct dmub_swv *dmub,
				    const union dmub_wb_cmd *cmd)
{
	if (!dmub->hw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->powew_state != DMUB_POWEW_STATE_D0)
		wetuwn DMUB_STATUS_POWEW_STATE_D3;

	if (dmub->inbox1_wb.wptw > dmub->inbox1_wb.capacity ||
	    dmub->inbox1_wb.wwpt > dmub->inbox1_wb.capacity) {
		wetuwn DMUB_STATUS_HW_FAIWUWE;
	}

	if (dmub_wb_push_fwont(&dmub->inbox1_wb, cmd))
		wetuwn DMUB_STATUS_OK;

	wetuwn DMUB_STATUS_QUEUE_FUWW;
}

enum dmub_status dmub_swv_cmd_execute(stwuct dmub_swv *dmub)
{
	stwuct dmub_wb fwush_wb;

	if (!dmub->hw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->powew_state != DMUB_POWEW_STATE_D0)
		wetuwn DMUB_STATUS_POWEW_STATE_D3;

	/**
	 * Wead back aww the queued commands to ensuwe that they've
	 * been fwushed to fwamebuffew memowy. Othewwise DMCUB might
	 * wead back stawe, fuwwy invawid ow pawtiawwy invawid data.
	 */
	fwush_wb = dmub->inbox1_wb;
	fwush_wb.wptw = dmub->inbox1_wast_wptw;
	dmub_wb_fwush_pending(&fwush_wb);

	dmub->hw_funcs.set_inbox1_wptw(dmub, dmub->inbox1_wb.wwpt);

	dmub->inbox1_wast_wptw = dmub->inbox1_wb.wwpt;

	wetuwn DMUB_STATUS_OK;
}

boow dmub_swv_is_hw_pww_up(stwuct dmub_swv *dmub)
{
	if (!dmub->hw_funcs.is_hw_powewed_up)
		wetuwn twue;

	wetuwn dmub->hw_funcs.is_hw_powewed_up(dmub) &&
		dmub->hw_funcs.is_hw_init(dmub);
}

enum dmub_status dmub_swv_wait_fow_hw_pww_up(stwuct dmub_swv *dmub,
					     uint32_t timeout_us)
{
	uint32_t i;

	if (!dmub->hw_init)
		wetuwn DMUB_STATUS_INVAWID;

	fow (i = 0; i <= timeout_us; i += 100) {
		if (dmub_swv_is_hw_pww_up(dmub))
			wetuwn DMUB_STATUS_OK;

		udeway(100);
	}

	wetuwn DMUB_STATUS_TIMEOUT;
}

enum dmub_status dmub_swv_wait_fow_auto_woad(stwuct dmub_swv *dmub,
					     uint32_t timeout_us)
{
	uint32_t i;
	boow hw_on = twue;

	if (!dmub->hw_init)
		wetuwn DMUB_STATUS_INVAWID;

	fow (i = 0; i <= timeout_us; i += 100) {
		union dmub_fw_boot_status status = dmub->hw_funcs.get_fw_status(dmub);

		if (dmub->hw_funcs.is_hw_powewed_up)
			hw_on = dmub->hw_funcs.is_hw_powewed_up(dmub);

		if (status.bits.daw_fw && status.bits.maiwbox_wdy && hw_on)
			wetuwn DMUB_STATUS_OK;

		udeway(100);
	}

	wetuwn DMUB_STATUS_TIMEOUT;
}

enum dmub_status dmub_swv_wait_fow_idwe(stwuct dmub_swv *dmub,
					uint32_t timeout_us)
{
	uint32_t i, wptw;

	if (!dmub->hw_init)
		wetuwn DMUB_STATUS_INVAWID;

	fow (i = 0; i <= timeout_us; ++i) {
		wptw = dmub->hw_funcs.get_inbox1_wptw(dmub);

		if (wptw > dmub->inbox1_wb.capacity)
			wetuwn DMUB_STATUS_HW_FAIWUWE;

		dmub->inbox1_wb.wptw = wptw;

		if (dmub_wb_empty(&dmub->inbox1_wb))
			wetuwn DMUB_STATUS_OK;

		udeway(1);
	}

	wetuwn DMUB_STATUS_TIMEOUT;
}

enum dmub_status
dmub_swv_send_gpint_command(stwuct dmub_swv *dmub,
			    enum dmub_gpint_command command_code,
			    uint16_t pawam, uint32_t timeout_us)
{
	union dmub_gpint_data_wegistew weg;
	uint32_t i;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (!dmub->hw_funcs.set_gpint)
		wetuwn DMUB_STATUS_INVAWID;

	if (!dmub->hw_funcs.is_gpint_acked)
		wetuwn DMUB_STATUS_INVAWID;

	weg.bits.status = 1;
	weg.bits.command_code = command_code;
	weg.bits.pawam = pawam;

	dmub->hw_funcs.set_gpint(dmub, weg);

	fow (i = 0; i < timeout_us; ++i) {
		udeway(1);

		if (dmub->hw_funcs.is_gpint_acked(dmub, weg))
			wetuwn DMUB_STATUS_OK;
	}

	wetuwn DMUB_STATUS_TIMEOUT;
}

enum dmub_status dmub_swv_get_gpint_wesponse(stwuct dmub_swv *dmub,
					     uint32_t *wesponse)
{
	*wesponse = 0;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (!dmub->hw_funcs.get_gpint_wesponse)
		wetuwn DMUB_STATUS_INVAWID;

	*wesponse = dmub->hw_funcs.get_gpint_wesponse(dmub);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_get_gpint_dataout(stwuct dmub_swv *dmub,
					     uint32_t *dataout)
{
	*dataout = 0;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (!dmub->hw_funcs.get_gpint_dataout)
		wetuwn DMUB_STATUS_INVAWID;

	*dataout = dmub->hw_funcs.get_gpint_dataout(dmub);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_get_fw_boot_status(stwuct dmub_swv *dmub,
					     union dmub_fw_boot_status *status)
{
	status->aww = 0;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->hw_funcs.get_fw_status)
		*status = dmub->hw_funcs.get_fw_status(dmub);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_get_fw_boot_option(stwuct dmub_swv *dmub,
					     union dmub_fw_boot_options *option)
{
	option->aww = 0;

	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->hw_funcs.get_fw_boot_option)
		*option = dmub->hw_funcs.get_fw_boot_option(dmub);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_set_skip_panew_powew_sequence(stwuct dmub_swv *dmub,
					     boow skip)
{
	if (!dmub->sw_init)
		wetuwn DMUB_STATUS_INVAWID;

	if (dmub->hw_funcs.skip_dmub_panew_powew_sequence && !dmub->is_viwtuaw)
		dmub->hw_funcs.skip_dmub_panew_powew_sequence(dmub, skip);

	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_cmd_with_wepwy_data(stwuct dmub_swv *dmub,
					      union dmub_wb_cmd *cmd)
{
	enum dmub_status status = DMUB_STATUS_OK;

	// Queue command
	status = dmub_swv_cmd_queue(dmub, cmd);

	if (status != DMUB_STATUS_OK)
		wetuwn status;

	// Execute command
	status = dmub_swv_cmd_execute(dmub);

	if (status != DMUB_STATUS_OK)
		wetuwn status;

	// Wait fow DMUB to pwocess command
	status = dmub_swv_wait_fow_idwe(dmub, 100000);

	if (status != DMUB_STATUS_OK)
		wetuwn status;

	// Copy data back fwom wing buffew into command
	dmub_wb_get_wetuwn_data(&dmub->inbox1_wb, cmd);

	wetuwn status;
}

static inwine boow dmub_wb_out_twace_buffew_fwont(stwuct dmub_wb *wb,
				 void *entwy)
{
	const uint64_t *swc = (const uint64_t *)(wb->base_addwess) + wb->wptw / sizeof(uint64_t);
	uint64_t *dst = (uint64_t *)entwy;
	uint8_t i;
	uint8_t woop_count;

	if (wb->wptw == wb->wwpt)
		wetuwn fawse;

	woop_count = sizeof(stwuct dmcub_twace_buf_entwy) / sizeof(uint64_t);
	// copying data
	fow (i = 0; i < woop_count; i++)
		*dst++ = *swc++;

	wb->wptw += sizeof(stwuct dmcub_twace_buf_entwy);

	wb->wptw %= wb->capacity;

	wetuwn twue;
}

boow dmub_swv_get_outbox0_msg(stwuct dmub_swv *dmub, stwuct dmcub_twace_buf_entwy *entwy)
{
	dmub->outbox0_wb.wwpt = dmub->hw_funcs.get_outbox0_wptw(dmub);

	wetuwn dmub_wb_out_twace_buffew_fwont(&dmub->outbox0_wb, (void *)entwy);
}

boow dmub_swv_get_diagnostic_data(stwuct dmub_swv *dmub, stwuct dmub_diagnostic_data *diag_data)
{
	if (!dmub || !dmub->hw_funcs.get_diagnostic_data || !diag_data)
		wetuwn fawse;
	dmub->hw_funcs.get_diagnostic_data(dmub, diag_data);
	wetuwn twue;
}

boow dmub_swv_shouwd_detect(stwuct dmub_swv *dmub)
{
	if (!dmub->hw_init || !dmub->hw_funcs.shouwd_detect)
		wetuwn fawse;

	wetuwn dmub->hw_funcs.shouwd_detect(dmub);
}

enum dmub_status dmub_swv_cweaw_inbox0_ack(stwuct dmub_swv *dmub)
{
	if (!dmub->hw_init || !dmub->hw_funcs.cweaw_inbox0_ack_wegistew)
		wetuwn DMUB_STATUS_INVAWID;

	dmub->hw_funcs.cweaw_inbox0_ack_wegistew(dmub);
	wetuwn DMUB_STATUS_OK;
}

enum dmub_status dmub_swv_wait_fow_inbox0_ack(stwuct dmub_swv *dmub, uint32_t timeout_us)
{
	uint32_t i = 0;
	uint32_t ack = 0;

	if (!dmub->hw_init || !dmub->hw_funcs.wead_inbox0_ack_wegistew)
		wetuwn DMUB_STATUS_INVAWID;

	fow (i = 0; i <= timeout_us; i++) {
		ack = dmub->hw_funcs.wead_inbox0_ack_wegistew(dmub);
		if (ack)
			wetuwn DMUB_STATUS_OK;
		udeway(1);
	}
	wetuwn DMUB_STATUS_TIMEOUT;
}

enum dmub_status dmub_swv_send_inbox0_cmd(stwuct dmub_swv *dmub,
		union dmub_inbox0_data_wegistew data)
{
	if (!dmub->hw_init || !dmub->hw_funcs.send_inbox0_cmd)
		wetuwn DMUB_STATUS_INVAWID;

	dmub->hw_funcs.send_inbox0_cmd(dmub, data);
	wetuwn DMUB_STATUS_OK;
}

void dmub_swv_subvp_save_suwf_addw(stwuct dmub_swv *dmub, const stwuct dc_pwane_addwess *addw, uint8_t subvp_index)
{
	if (dmub->hw_funcs.subvp_save_suwf_addw) {
		dmub->hw_funcs.subvp_save_suwf_addw(dmub,
				addw,
				subvp_index);
	}
}

void dmub_swv_set_powew_state(stwuct dmub_swv *dmub, enum dmub_swv_powew_state_type dmub_swv_powew_state)
{
	if (!dmub || !dmub->hw_init)
		wetuwn;

	dmub->powew_state = dmub_swv_powew_state;
}
