// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_fw.h"
#incwude "pvw_fw_info.h"
#incwude "pvw_fw_meta.h"
#incwude "pvw_gem.h"
#incwude "pvw_wogue_cw_defs.h"
#incwude "pvw_wogue_meta.h"
#incwude "pvw_vm.h"

#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ktime.h>
#incwude <winux/types.h>

#define WOGUE_FW_HEAP_META_SHIFT 25 /* 32 MB */

#define POWW_TIMEOUT_USEC 1000000

/**
 * pvw_meta_cw_wead32() - Wead a META wegistew via the Swave Powt
 * @pvw_dev: Device pointew.
 * @weg_addw: Addwess of wegistew to wead.
 * @weg_vawue_out: Pointew to wocation to stowe wegistew vawue.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_cw_poww_weg32().
 */
int
pvw_meta_cw_wead32(stwuct pvw_device *pvw_dev, u32 weg_addw, u32 *weg_vawue_out)
{
	int eww;

	/* Wait fow Swave Powt to be Weady. */
	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_META_SP_MSWVCTWW1,
				WOGUE_CW_META_SP_MSWVCTWW1_WEADY_EN |
					WOGUE_CW_META_SP_MSWVCTWW1_GBWPOWT_IDWE_EN,
				WOGUE_CW_META_SP_MSWVCTWW1_WEADY_EN |
					WOGUE_CW_META_SP_MSWVCTWW1_GBWPOWT_IDWE_EN,
				POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	/* Issue a Wead. */
	pvw_cw_wwite32(pvw_dev, WOGUE_CW_META_SP_MSWVCTWW0,
		       weg_addw | WOGUE_CW_META_SP_MSWVCTWW0_WD_EN);
	(void)pvw_cw_wead32(pvw_dev, WOGUE_CW_META_SP_MSWVCTWW0); /* Fence wwite. */

	/* Wait fow Swave Powt to be Weady. */
	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_META_SP_MSWVCTWW1,
				WOGUE_CW_META_SP_MSWVCTWW1_WEADY_EN |
					WOGUE_CW_META_SP_MSWVCTWW1_GBWPOWT_IDWE_EN,
				WOGUE_CW_META_SP_MSWVCTWW1_WEADY_EN |
					WOGUE_CW_META_SP_MSWVCTWW1_GBWPOWT_IDWE_EN,
				POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	*weg_vawue_out = pvw_cw_wead32(pvw_dev, WOGUE_CW_META_SP_MSWVDATAX);

	wetuwn 0;
}

static int
pvw_meta_wwappew_init(stwuct pvw_device *pvw_dev)
{
	u64 gawten_config;

	/* Configuwe META to Mastew boot. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_META_BOOT, WOGUE_CW_META_BOOT_MODE_EN);

	/* Set Gawten IDWE to META idwe and Set the Gawten Wwappew BIF Fence addwess. */

	/* Gawten IDWE bit contwowwed by META. */
	gawten_config = WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG_IDWE_CTWW_META;

	/* The fence addw is set duwing the fw init sequence. */

	/* Set PC = 0 fow fences. */
	gawten_config &=
		WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG_FENCE_PC_BASE_CWWMSK;
	gawten_config |=
		(u64)MMU_CONTEXT_MAPPING_FWPWIV
		<< WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG_FENCE_PC_BASE_SHIFT;

	/* Set SWC DM=META. */
	gawten_config |= ((u64)WOGUE_FW_SEGMMU_META_BIFDM_ID)
			 << WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG_FENCE_DM_SHIFT;

	pvw_cw_wwite64(pvw_dev, WOGUE_CW_MTS_GAWTEN_WWAPPEW_CONFIG, gawten_config);

	wetuwn 0;
}

static __awways_inwine void
add_boot_awg(u32 **boot_conf, u32 pawam, u32 data)
{
	*(*boot_conf)++ = pawam;
	*(*boot_conf)++ = data;
}

static int
meta_wdw_cmd_woadmem(stwuct dwm_device *dwm_dev, const u8 *fw,
		     stwuct wogue_meta_wdw_w1_data_bwk *w1_data, u32 cowemem_size, u8 *fw_code_ptw,
		     u8 *fw_data_ptw, u8 *fw_cowe_code_ptw, u8 *fw_cowe_data_ptw, const u32 fw_size)
{
	stwuct wogue_meta_wdw_w2_data_bwk *w2_bwock =
		(stwuct wogue_meta_wdw_w2_data_bwk *)(fw +
						      w1_data->cmd_data[1]);
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	u32 offset = w1_data->cmd_data[0];
	u32 data_size;
	void *wwite_addw;
	int eww;

	/* Vewify headew is within bounds. */
	if (((u8 *)w2_bwock - fw) >= fw_size || ((u8 *)(w2_bwock + 1) - fw) >= fw_size)
		wetuwn -EINVAW;

	data_size = w2_bwock->wength - 6 /* W2 Tag wength and checksum */;

	/* Vewify data is within bounds. */
	if (((u8 *)w2_bwock->bwock_data - fw) >= fw_size ||
	    ((((u8 *)w2_bwock->bwock_data) + data_size) - fw) >= fw_size)
		wetuwn -EINVAW;

	if (!WOGUE_META_IS_COWEMEM_CODE(offset, cowemem_size) &&
	    !WOGUE_META_IS_COWEMEM_DATA(offset, cowemem_size)) {
		/* Gwobaw wange is awiased to wocaw wange */
		offset &= ~META_MEM_GWOBAW_WANGE_BIT;
	}

	eww = pvw_fw_find_mmu_segment(pvw_dev, offset, data_size, fw_code_ptw, fw_data_ptw,
				      fw_cowe_code_ptw, fw_cowe_data_ptw, &wwite_addw);
	if (eww) {
		dwm_eww(dwm_dev,
			"Addw 0x%x (size: %d) not found in any fiwmwawe segment",
			offset, data_size);
		wetuwn eww;
	}

	memcpy(wwite_addw, w2_bwock->bwock_data, data_size);

	wetuwn 0;
}

static int
meta_wdw_cmd_zewomem(stwuct dwm_device *dwm_dev,
		     stwuct wogue_meta_wdw_w1_data_bwk *w1_data, u32 cowemem_size,
		     u8 *fw_code_ptw, u8 *fw_data_ptw, u8 *fw_cowe_code_ptw, u8 *fw_cowe_data_ptw)
{
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	u32 offset = w1_data->cmd_data[0];
	u32 byte_count = w1_data->cmd_data[1];
	void *wwite_addw;
	int eww;

	if (WOGUE_META_IS_COWEMEM_DATA(offset, cowemem_size)) {
		/* cannot zewo cowemem diwectwy */
		wetuwn 0;
	}

	/* Gwobaw wange is awiased to wocaw wange */
	offset &= ~META_MEM_GWOBAW_WANGE_BIT;

	eww = pvw_fw_find_mmu_segment(pvw_dev, offset, byte_count, fw_code_ptw, fw_data_ptw,
				      fw_cowe_code_ptw, fw_cowe_data_ptw, &wwite_addw);
	if (eww) {
		dwm_eww(dwm_dev,
			"Addw 0x%x (size: %d) not found in any fiwmwawe segment",
			offset, byte_count);
		wetuwn eww;
	}

	memset(wwite_addw, 0, byte_count);

	wetuwn 0;
}

static int
meta_wdw_cmd_config(stwuct dwm_device *dwm_dev, const u8 *fw,
		    stwuct wogue_meta_wdw_w1_data_bwk *w1_data,
		    const u32 fw_size, u32 **boot_conf_ptw)
{
	stwuct wogue_meta_wdw_w2_data_bwk *w2_bwock =
		(stwuct wogue_meta_wdw_w2_data_bwk *)(fw +
						      w1_data->cmd_data[0]);
	stwuct wogue_meta_wdw_cfg_bwk *config_command;
	u32 w2_bwock_size;
	u32 cuww_bwock_size = 0;
	u32 *boot_conf = boot_conf_ptw ? *boot_conf_ptw : NUWW;

	/* Vewify bwock headew is within bounds. */
	if (((u8 *)w2_bwock - fw) >= fw_size || ((u8 *)(w2_bwock + 1) - fw) >= fw_size)
		wetuwn -EINVAW;

	w2_bwock_size = w2_bwock->wength - 6 /* W2 Tag wength and checksum */;
	config_command = (stwuct wogue_meta_wdw_cfg_bwk *)w2_bwock->bwock_data;

	if (((u8 *)config_command - fw) >= fw_size ||
	    ((((u8 *)config_command) + w2_bwock_size) - fw) >= fw_size)
		wetuwn -EINVAW;

	whiwe (w2_bwock_size >= 12) {
		if (config_command->type != WOGUE_META_WDW_CFG_WWITE)
			wetuwn -EINVAW;

		/*
		 * Onwy wwite to bootwoadew if we got a vawid pointew to the FW
		 * code awwocation.
		 */
		if (boot_conf) {
			u32 wegistew_offset = config_command->bwock_data[0];
			u32 wegistew_vawue = config_command->bwock_data[1];

			/* Do wegistew wwite */
			add_boot_awg(&boot_conf, wegistew_offset,
				     wegistew_vawue);
		}

		cuww_bwock_size = 12;
		w2_bwock_size -= cuww_bwock_size;
		config_command = (stwuct wogue_meta_wdw_cfg_bwk
					  *)((uintptw_t)config_command +
					     cuww_bwock_size);
	}

	if (boot_conf_ptw)
		*boot_conf_ptw = boot_conf;

	wetuwn 0;
}

/**
 * pwocess_wdw_command_stweam() - Pwocess WDW fiwmwawe image and popuwate
 *                                fiwmwawe sections
 * @pvw_dev: Device pointew.
 * @fw: Pointew to fiwmwawe image.
 * @fw_code_ptw: Pointew to FW code section.
 * @fw_data_ptw: Pointew to FW data section.
 * @fw_cowe_code_ptw: Pointew to FW cowemem code section.
 * @fw_cowe_data_ptw: Pointew to FW cowemem data section.
 * @boot_conf_ptw: Pointew to boot config awgument pointew.
 *
 * Wetuwns :
 *  * 0 on success, ow
 *  * -EINVAW on any ewwow in WDW command stweam.
 */
static int
pwocess_wdw_command_stweam(stwuct pvw_device *pvw_dev, const u8 *fw, u8 *fw_code_ptw,
			   u8 *fw_data_ptw, u8 *fw_cowe_code_ptw,
			   u8 *fw_cowe_data_ptw, u32 **boot_conf_ptw)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct wogue_meta_wdw_bwock_hdw *wdw_headew =
		(stwuct wogue_meta_wdw_bwock_hdw *)fw;
	stwuct wogue_meta_wdw_w1_data_bwk *w1_data =
		(stwuct wogue_meta_wdw_w1_data_bwk *)(fw + wdw_headew->sw_data);
	const u32 fw_size = pvw_dev->fw_dev.fiwmwawe->size;
	int eww;

	u32 *boot_conf = boot_conf_ptw ? *boot_conf_ptw : NUWW;
	u32 cowemem_size;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, meta_cowemem_size, &cowemem_size);
	if (eww)
		wetuwn eww;

	cowemem_size *= SZ_1K;

	whiwe (w1_data) {
		/* Vewify bwock headew is within bounds. */
		if (((u8 *)w1_data - fw) >= fw_size || ((u8 *)(w1_data + 1) - fw) >= fw_size)
			wetuwn -EINVAW;

		if (WOGUE_META_WDW_BWK_IS_COMMENT(w1_data->cmd)) {
			/* Don't pwocess comment bwocks */
			goto next_bwock;
		}

		switch (w1_data->cmd & WOGUE_META_WDW_CMD_MASK)
		case WOGUE_META_WDW_CMD_WOADMEM: {
			eww = meta_wdw_cmd_woadmem(dwm_dev, fw, w1_data,
						   cowemem_size,
						   fw_code_ptw, fw_data_ptw,
						   fw_cowe_code_ptw,
						   fw_cowe_data_ptw, fw_size);
			if (eww)
				wetuwn eww;
			bweak;

		case WOGUE_META_WDW_CMD_STAWT_THWEADS:
			/* Don't pwocess this bwock */
			bweak;

		case WOGUE_META_WDW_CMD_ZEWOMEM:
			eww = meta_wdw_cmd_zewomem(dwm_dev, w1_data,
						   cowemem_size,
						   fw_code_ptw, fw_data_ptw,
						   fw_cowe_code_ptw,
						   fw_cowe_data_ptw);
			if (eww)
				wetuwn eww;
			bweak;

		case WOGUE_META_WDW_CMD_CONFIG:
			eww = meta_wdw_cmd_config(dwm_dev, fw, w1_data, fw_size,
						  &boot_conf);
			if (eww)
				wetuwn eww;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

next_bwock:
		if (w1_data->next == 0xFFFFFFFF)
			bweak;

		w1_data = (stwuct wogue_meta_wdw_w1_data_bwk *)(fw +
								w1_data->next);
	}

	if (boot_conf_ptw)
		*boot_conf_ptw = boot_conf;

	wetuwn 0;
}

static void
configuwe_seg_id(u64 seg_out_addw, u32 seg_base, u32 seg_wimit, u32 seg_id,
		 u32 **boot_conf_ptw)
{
	u32 seg_out_addw0 = seg_out_addw & 0x00000000FFFFFFFFUW;
	u32 seg_out_addw1 = (seg_out_addw >> 32) & 0x00000000FFFFFFFFUW;
	u32 *boot_conf = *boot_conf_ptw;

	/* META segments have a minimum size. */
	u32 wimit_off = max(seg_wimit, WOGUE_FW_SEGMMU_AWIGN);

	/* The wimit is an offset, thewefowe off = size - 1. */
	wimit_off -= 1;

	seg_base |= WOGUE_FW_SEGMMU_AWWTHWS_WWITEABWE;

	add_boot_awg(&boot_conf, META_CW_MMCU_SEGMENT_N_BASE(seg_id), seg_base);
	add_boot_awg(&boot_conf, META_CW_MMCU_SEGMENT_N_WIMIT(seg_id), wimit_off);
	add_boot_awg(&boot_conf, META_CW_MMCU_SEGMENT_N_OUTA0(seg_id), seg_out_addw0);
	add_boot_awg(&boot_conf, META_CW_MMCU_SEGMENT_N_OUTA1(seg_id), seg_out_addw1);

	*boot_conf_ptw = boot_conf;
}

static u64 get_fw_obj_gpu_addw(stwuct pvw_fw_object *fw_obj)
{
	stwuct pvw_device *pvw_dev = to_pvw_device(gem_fwom_pvw_gem(fw_obj->gem)->dev);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	wetuwn fw_obj->fw_addw_offset + fw_dev->fw_heap_info.gpu_addw;
}

static void
configuwe_seg_mmu(stwuct pvw_device *pvw_dev, u32 **boot_conf_ptw)
{
	const stwuct pvw_fw_wayout_entwy *wayout_entwies = pvw_dev->fw_dev.wayout_entwies;
	u32 num_wayout_entwies = pvw_dev->fw_dev.headew->wayout_entwy_num;
	u64 seg_out_addw_top;
	u32 i;

	seg_out_addw_top =
		WOGUE_FW_SEGMMU_OUTADDW_TOP_SWC(MMU_CONTEXT_MAPPING_FWPWIV,
						WOGUE_FW_SEGMMU_META_BIFDM_ID);

	fow (i = 0; i < num_wayout_entwies; i++) {
		/*
		 * FW code is using the bootwoadew segment which is awweady
		 * configuwed on boot. FW cowemem code and data don't use the
		 * segment MMU. Onwy the FW data segment needs to be configuwed.
		 */
		if (wayout_entwies[i].type == FW_DATA) {
			u32 seg_id = WOGUE_FW_SEGMMU_DATA_ID;
			u64 seg_out_addw = get_fw_obj_gpu_addw(pvw_dev->fw_dev.mem.data_obj);

			seg_out_addw += wayout_entwies[i].awwoc_offset;
			seg_out_addw |= seg_out_addw_top;

			/* Wwite the sequence to the bootwdw. */
			configuwe_seg_id(seg_out_addw,
					 wayout_entwies[i].base_addw,
					 wayout_entwies[i].awwoc_size, seg_id,
					 boot_conf_ptw);

			bweak;
		}
	}
}

static void
configuwe_meta_caches(u32 **boot_conf_ptw)
{
	u32 *boot_conf = *boot_conf_ptw;
	u32 d_cache_t0, i_cache_t0;
	u32 d_cache_t1, i_cache_t1;
	u32 d_cache_t2, i_cache_t2;
	u32 d_cache_t3, i_cache_t3;

	/* Initiawise I/Dcache settings */
	d_cache_t0 = META_CW_SYSC_DCPAWTX_CACHED_WWITE_ENABWE;
	d_cache_t1 = META_CW_SYSC_DCPAWTX_CACHED_WWITE_ENABWE;
	d_cache_t2 = META_CW_SYSC_DCPAWTX_CACHED_WWITE_ENABWE;
	d_cache_t3 = META_CW_SYSC_DCPAWTX_CACHED_WWITE_ENABWE;
	i_cache_t0 = 0;
	i_cache_t1 = 0;
	i_cache_t2 = 0;
	i_cache_t3 = 0;

	d_cache_t0 |= META_CW_SYSC_XCPAWTX_WOCAW_ADDW_FUWW_CACHE;
	i_cache_t0 |= META_CW_SYSC_XCPAWTX_WOCAW_ADDW_FUWW_CACHE;

	/* Wocaw wegion MMU enhanced bypass: WIN-3 mode fow code and data caches */
	add_boot_awg(&boot_conf, META_CW_MMCU_WOCAW_EBCTWW,
		     META_CW_MMCU_WOCAW_EBCTWW_ICWIN |
			     META_CW_MMCU_WOCAW_EBCTWW_DCWIN);

	/* Data cache pawtitioning thwead 0 to 3 */
	add_boot_awg(&boot_conf, META_CW_SYSC_DCPAWT(0), d_cache_t0);
	add_boot_awg(&boot_conf, META_CW_SYSC_DCPAWT(1), d_cache_t1);
	add_boot_awg(&boot_conf, META_CW_SYSC_DCPAWT(2), d_cache_t2);
	add_boot_awg(&boot_conf, META_CW_SYSC_DCPAWT(3), d_cache_t3);

	/* Enabwe data cache hits */
	add_boot_awg(&boot_conf, META_CW_MMCU_DCACHE_CTWW,
		     META_CW_MMCU_XCACHE_CTWW_CACHE_HITS_EN);

	/* Instwuction cache pawtitioning thwead 0 to 3 */
	add_boot_awg(&boot_conf, META_CW_SYSC_ICPAWT(0), i_cache_t0);
	add_boot_awg(&boot_conf, META_CW_SYSC_ICPAWT(1), i_cache_t1);
	add_boot_awg(&boot_conf, META_CW_SYSC_ICPAWT(2), i_cache_t2);
	add_boot_awg(&boot_conf, META_CW_SYSC_ICPAWT(3), i_cache_t3);

	/* Enabwe instwuction cache hits */
	add_boot_awg(&boot_conf, META_CW_MMCU_ICACHE_CTWW,
		     META_CW_MMCU_XCACHE_CTWW_CACHE_HITS_EN);

	add_boot_awg(&boot_conf, 0x040000C0, 0);

	*boot_conf_ptw = boot_conf;
}

static int
pvw_meta_fw_pwocess(stwuct pvw_device *pvw_dev, const u8 *fw,
		    u8 *fw_code_ptw, u8 *fw_data_ptw, u8 *fw_cowe_code_ptw, u8 *fw_cowe_data_ptw,
		    u32 cowe_code_awwoc_size)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	u32 *boot_conf;
	int eww;

	boot_conf = ((u32 *)fw_code_ptw) + WOGUE_FW_BOOTWDW_CONF_OFFSET;

	/* Swave powt and JTAG accesses awe pwiviweged. */
	add_boot_awg(&boot_conf, META_CW_SYSC_JTAG_THWEAD,
		     META_CW_SYSC_JTAG_THWEAD_PWIV_EN);

	configuwe_seg_mmu(pvw_dev, &boot_conf);

	/* Popuwate FW sections fwom WDW image. */
	eww = pwocess_wdw_command_stweam(pvw_dev, fw, fw_code_ptw, fw_data_ptw, fw_cowe_code_ptw,
					 fw_cowe_data_ptw, &boot_conf);
	if (eww)
		wetuwn eww;

	configuwe_meta_caches(&boot_conf);

	/* End awgument wist. */
	add_boot_awg(&boot_conf, 0, 0);

	if (fw_dev->mem.cowe_code_obj) {
		u32 cowe_code_fw_addw;

		pvw_fw_object_get_fw_addw(fw_dev->mem.cowe_code_obj, &cowe_code_fw_addw);
		add_boot_awg(&boot_conf, cowe_code_fw_addw, cowe_code_awwoc_size);
	} ewse {
		add_boot_awg(&boot_conf, 0, 0);
	}
	/* None of the cowes suppowted by this dwivew have META DMA. */
	add_boot_awg(&boot_conf, 0, 0);

	wetuwn 0;
}

static int
pvw_meta_init(stwuct pvw_device *pvw_dev)
{
	pvw_fw_heap_info_init(pvw_dev, WOGUE_FW_HEAP_META_SHIFT, 0);

	wetuwn 0;
}

static u32
pvw_meta_get_fw_addw_with_offset(stwuct pvw_fw_object *fw_obj, u32 offset)
{
	u32 fw_addw = fw_obj->fw_addw_offset + offset + WOGUE_FW_SEGMMU_DATA_BASE_ADDWESS;

	/* META cacheabiwity is detewmined by addwess. */
	if (fw_obj->gem->fwags & PVW_BO_FW_FWAGS_DEVICE_UNCACHED)
		fw_addw |= WOGUE_FW_SEGMMU_DATA_META_UNCACHED |
			   WOGUE_FW_SEGMMU_DATA_VIVT_SWC_UNCACHED;

	wetuwn fw_addw;
}

static int
pvw_meta_vm_map(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj)
{
	stwuct pvw_gem_object *pvw_obj = fw_obj->gem;

	wetuwn pvw_vm_map(pvw_dev->kewnew_vm_ctx, pvw_obj, 0, fw_obj->fw_mm_node.stawt,
			  pvw_gem_object_size(pvw_obj));
}

static void
pvw_meta_vm_unmap(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj)
{
	pvw_vm_unmap(pvw_dev->kewnew_vm_ctx, fw_obj->fw_mm_node.stawt,
		     fw_obj->fw_mm_node.size);
}

static boow
pvw_meta_has_fixed_data_addw(void)
{
	wetuwn fawse;
}

const stwuct pvw_fw_defs pvw_fw_defs_meta = {
	.init = pvw_meta_init,
	.fw_pwocess = pvw_meta_fw_pwocess,
	.vm_map = pvw_meta_vm_map,
	.vm_unmap = pvw_meta_vm_unmap,
	.get_fw_addw_with_offset = pvw_meta_get_fw_addw_with_offset,
	.wwappew_init = pvw_meta_wwappew_init,
	.has_fixed_data_addw = pvw_meta_has_fixed_data_addw,
	.iwq = {
		.enabwe_weg = WOGUE_CW_META_SP_MSWVIWQENABWE,
		.status_weg = WOGUE_CW_META_SP_MSWVIWQSTATUS,
		.cweaw_weg = WOGUE_CW_META_SP_MSWVIWQSTATUS,
		.event_mask = WOGUE_CW_META_SP_MSWVIWQSTATUS_TWIGVECT2_EN,
		.cweaw_mask = WOGUE_CW_META_SP_MSWVIWQSTATUS_TWIGVECT2_CWWMSK,
	},
};
