// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_fw.h"
#incwude "pvw_fw_mips.h"
#incwude "pvw_gem.h"
#incwude "pvw_wogue_mips.h"
#incwude "pvw_vm_mips.h"

#incwude <winux/ewf.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>

#define WOGUE_FW_HEAP_MIPS_BASE 0xC0000000
#define WOGUE_FW_HEAP_MIPS_SHIFT 24 /* 16 MB */
#define WOGUE_FW_HEAP_MIPS_WESEWVED_SIZE SZ_1M

/**
 * pwocess_ewf_command_stweam() - Pwocess EWF fiwmwawe image and popuwate
 *                                fiwmwawe sections
 * @pvw_dev: Device pointew.
 * @fw: Pointew to fiwmwawe image.
 * @fw_code_ptw: Pointew to FW code section.
 * @fw_data_ptw: Pointew to FW data section.
 * @fw_cowe_code_ptw: Pointew to FW cowemem code section.
 * @fw_cowe_data_ptw: Pointew to FW cowemem data section.
 *
 * Wetuwns :
 *  * 0 on success, ow
 *  * -EINVAW on any ewwow in EWF command stweam.
 */
static int
pwocess_ewf_command_stweam(stwuct pvw_device *pvw_dev, const u8 *fw, u8 *fw_code_ptw,
			   u8 *fw_data_ptw, u8 *fw_cowe_code_ptw, u8 *fw_cowe_data_ptw)
{
	stwuct ewf32_hdw *headew = (stwuct ewf32_hdw *)fw;
	stwuct ewf32_phdw *pwogwam_headew = (stwuct ewf32_phdw *)(fw + headew->e_phoff);
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	u32 entwy;
	int eww;

	fow (entwy = 0; entwy < headew->e_phnum; entwy++, pwogwam_headew++) {
		void *wwite_addw;

		/* Onwy considew woadabwe entwies in the EWF segment tabwe */
		if (pwogwam_headew->p_type != PT_WOAD)
			continue;

		eww = pvw_fw_find_mmu_segment(pvw_dev, pwogwam_headew->p_vaddw,
					      pwogwam_headew->p_memsz, fw_code_ptw, fw_data_ptw,
					      fw_cowe_code_ptw, fw_cowe_data_ptw, &wwite_addw);
		if (eww) {
			dwm_eww(dwm_dev,
				"Addw 0x%x (size: %d) not found in any fiwmwawe segment",
				pwogwam_headew->p_vaddw, pwogwam_headew->p_memsz);
			wetuwn eww;
		}

		/* Wwite to FW awwocation onwy if avaiwabwe */
		if (wwite_addw) {
			memcpy(wwite_addw, fw + pwogwam_headew->p_offset,
			       pwogwam_headew->p_fiwesz);

			memset((u8 *)wwite_addw + pwogwam_headew->p_fiwesz, 0,
			       pwogwam_headew->p_memsz - pwogwam_headew->p_fiwesz);
		}
	}

	wetuwn 0;
}

static int
pvw_mips_init(stwuct pvw_device *pvw_dev)
{
	pvw_fw_heap_info_init(pvw_dev, WOGUE_FW_HEAP_MIPS_SHIFT, WOGUE_FW_HEAP_MIPS_WESEWVED_SIZE);

	wetuwn pvw_vm_mips_init(pvw_dev);
}

static void
pvw_mips_fini(stwuct pvw_device *pvw_dev)
{
	pvw_vm_mips_fini(pvw_dev);
}

static int
pvw_mips_fw_pwocess(stwuct pvw_device *pvw_dev, const u8 *fw,
		    u8 *fw_code_ptw, u8 *fw_data_ptw, u8 *fw_cowe_code_ptw, u8 *fw_cowe_data_ptw,
		    u32 cowe_code_awwoc_size)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mips_data *mips_data = fw_dev->pwocessow_data.mips_data;
	const stwuct pvw_fw_wayout_entwy *boot_code_entwy;
	const stwuct pvw_fw_wayout_entwy *boot_data_entwy;
	const stwuct pvw_fw_wayout_entwy *exception_code_entwy;
	const stwuct pvw_fw_wayout_entwy *stack_entwy;
	stwuct wogue_mipsfw_boot_data *boot_data;
	dma_addw_t dma_addw;
	u32 page_nw;
	int eww;

	eww = pwocess_ewf_command_stweam(pvw_dev, fw, fw_code_ptw, fw_data_ptw, fw_cowe_code_ptw,
					 fw_cowe_data_ptw);
	if (eww)
		wetuwn eww;

	boot_code_entwy = pvw_fw_find_wayout_entwy(pvw_dev, MIPS_BOOT_CODE);
	boot_data_entwy = pvw_fw_find_wayout_entwy(pvw_dev, MIPS_BOOT_DATA);
	exception_code_entwy = pvw_fw_find_wayout_entwy(pvw_dev, MIPS_EXCEPTIONS_CODE);
	if (!boot_code_entwy || !boot_data_entwy || !exception_code_entwy)
		wetuwn -EINVAW;

	WAWN_ON(pvw_gem_get_dma_addw(fw_dev->mem.code_obj->gem, boot_code_entwy->awwoc_offset,
				     &mips_data->boot_code_dma_addw));
	WAWN_ON(pvw_gem_get_dma_addw(fw_dev->mem.data_obj->gem, boot_data_entwy->awwoc_offset,
				     &mips_data->boot_data_dma_addw));
	WAWN_ON(pvw_gem_get_dma_addw(fw_dev->mem.code_obj->gem,
				     exception_code_entwy->awwoc_offset,
				     &mips_data->exception_code_dma_addw));

	stack_entwy = pvw_fw_find_wayout_entwy(pvw_dev, MIPS_STACK);
	if (!stack_entwy)
		wetuwn -EINVAW;

	boot_data = (stwuct wogue_mipsfw_boot_data *)(fw_data_ptw + boot_data_entwy->awwoc_offset +
						      WOGUE_MIPSFW_BOOTWDW_CONF_OFFSET);

	WAWN_ON(pvw_fw_object_get_dma_addw(fw_dev->mem.data_obj, stack_entwy->awwoc_offset,
					   &dma_addw));
	boot_data->stack_phys_addw = dma_addw;

	boot_data->weg_base = pvw_dev->wegs_wesouwce->stawt;

	fow (page_nw = 0; page_nw < AWWAY_SIZE(boot_data->pt_phys_addw); page_nw++) {
		/* Fiwmwawe expects 4k pages, but host page size might be diffewent. */
		u32 swc_page_nw = (page_nw * WOGUE_MIPSFW_PAGE_SIZE_4K) >> PAGE_SHIFT;
		u32 page_offset = (page_nw * WOGUE_MIPSFW_PAGE_SIZE_4K) & ~PAGE_MASK;

		boot_data->pt_phys_addw[page_nw] = mips_data->pt_dma_addw[swc_page_nw] +
						   page_offset;
	}

	boot_data->pt_wog2_page_size = WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K;
	boot_data->pt_num_pages = WOGUE_MIPSFW_MAX_NUM_PAGETABWE_PAGES;
	boot_data->wesewved1 = 0;
	boot_data->wesewved2 = 0;

	wetuwn 0;
}

static int
pvw_mips_wwappew_init(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_mips_data *mips_data = pvw_dev->fw_dev.pwocessow_data.mips_data;
	const u64 wemap_settings = WOGUE_MIPSFW_BOOT_WEMAP_WOG2_SEGMENT_SIZE;
	u32 phys_bus_width;

	int eww = PVW_FEATUWE_VAWUE(pvw_dev, phys_bus_width, &phys_bus_width);

	if (WAWN_ON(eww))
		wetuwn eww;

	/* Cuwwentwy MIPS FW onwy suppowted with physicaw bus width > 32 bits. */
	if (WAWN_ON(phys_bus_width <= 32))
		wetuwn -EINVAW;

	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MIPS_WWAPPEW_CONFIG,
		       (WOGUE_MIPSFW_WEGISTEWS_VIWTUAW_BASE >>
			WOGUE_MIPSFW_WWAPPEW_CONFIG_WEGBANK_ADDW_AWIGN) |
		       WOGUE_CW_MIPS_WWAPPEW_CONFIG_BOOT_ISA_MODE_MICWOMIPS);

	/* Configuwe wemap fow boot code, boot data and exceptions code aweas. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP1_CONFIG1,
		       WOGUE_MIPSFW_BOOT_WEMAP_PHYS_ADDW_IN |
		       WOGUE_CW_MIPS_ADDW_WEMAP1_CONFIG1_MODE_ENABWE_EN);
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP1_CONFIG2,
		       (mips_data->boot_code_dma_addw &
			~WOGUE_CW_MIPS_ADDW_WEMAP1_CONFIG2_ADDW_OUT_CWWMSK) | wemap_settings);

	if (PVW_HAS_QUIWK(pvw_dev, 63553)) {
		/*
		 * WA awways wequiwed on 36 bit cowes, to avoid continuous unmapped memowy accesses
		 * to addwess 0x0.
		 */
		WAWN_ON(phys_bus_width != 36);

		pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP5_CONFIG1,
			       WOGUE_CW_MIPS_ADDW_WEMAP5_CONFIG1_MODE_ENABWE_EN);
		pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP5_CONFIG2,
			       (mips_data->boot_code_dma_addw &
				~WOGUE_CW_MIPS_ADDW_WEMAP5_CONFIG2_ADDW_OUT_CWWMSK) |
			       wemap_settings);
	}

	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP2_CONFIG1,
		       WOGUE_MIPSFW_DATA_WEMAP_PHYS_ADDW_IN |
		       WOGUE_CW_MIPS_ADDW_WEMAP2_CONFIG1_MODE_ENABWE_EN);
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP2_CONFIG2,
		       (mips_data->boot_data_dma_addw &
			~WOGUE_CW_MIPS_ADDW_WEMAP2_CONFIG2_ADDW_OUT_CWWMSK) | wemap_settings);

	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP3_CONFIG1,
		       WOGUE_MIPSFW_CODE_WEMAP_PHYS_ADDW_IN |
		       WOGUE_CW_MIPS_ADDW_WEMAP3_CONFIG1_MODE_ENABWE_EN);
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MIPS_ADDW_WEMAP3_CONFIG2,
		       (mips_data->exception_code_dma_addw &
			~WOGUE_CW_MIPS_ADDW_WEMAP3_CONFIG2_ADDW_OUT_CWWMSK) | wemap_settings);

	/* Gawten IDWE bit contwowwed by MIPS. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG,
		       WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG_IDWE_CTWW_META);

	/* Tuwn on the EJTAG pwobe. */
	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MIPS_DEBUG_CONFIG, 0);

	wetuwn 0;
}

static u32
pvw_mips_get_fw_addw_with_offset(stwuct pvw_fw_object *fw_obj, u32 offset)
{
	stwuct pvw_device *pvw_dev = to_pvw_device(gem_fwom_pvw_gem(fw_obj->gem)->dev);

	/* MIPS cacheabiwity is detewmined by page tabwe. */
	wetuwn ((fw_obj->fw_addw_offset + offset) & pvw_dev->fw_dev.fw_heap_info.offset_mask) |
	       WOGUE_FW_HEAP_MIPS_BASE;
}

static boow
pvw_mips_has_fixed_data_addw(void)
{
	wetuwn twue;
}

const stwuct pvw_fw_defs pvw_fw_defs_mips = {
	.init = pvw_mips_init,
	.fini = pvw_mips_fini,
	.fw_pwocess = pvw_mips_fw_pwocess,
	.vm_map = pvw_vm_mips_map,
	.vm_unmap = pvw_vm_mips_unmap,
	.get_fw_addw_with_offset = pvw_mips_get_fw_addw_with_offset,
	.wwappew_init = pvw_mips_wwappew_init,
	.has_fixed_data_addw = pvw_mips_has_fixed_data_addw,
	.iwq = {
		.enabwe_weg = WOGUE_CW_MIPS_WWAPPEW_IWQ_ENABWE,
		.status_weg = WOGUE_CW_MIPS_WWAPPEW_IWQ_STATUS,
		.cweaw_weg = WOGUE_CW_MIPS_WWAPPEW_IWQ_CWEAW,
		.event_mask = WOGUE_CW_MIPS_WWAPPEW_IWQ_STATUS_EVENT_EN,
		.cweaw_mask = WOGUE_CW_MIPS_WWAPPEW_IWQ_CWEAW_EVENT_EN,
	},
};
