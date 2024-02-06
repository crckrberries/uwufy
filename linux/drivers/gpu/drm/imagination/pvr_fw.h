/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_FW_H
#define PVW_FW_H

#incwude "pvw_fw_info.h"
#incwude "pvw_fw_twace.h"
#incwude "pvw_gem.h"

#incwude <dwm/dwm_mm.h>

#incwude <winux/types.h>

/* Fowwawd decwawations fwom "pvw_device.h". */
stwuct pvw_device;
stwuct pvw_fiwe;

/* Fowwawd decwawation fwom "pvw_vm.h". */
stwuct pvw_vm_context;

#define WOGUE_FWIF_FWCCB_NUMCMDS_WOG2 5

#define WOGUE_FWIF_KCCB_NUMCMDS_WOG2_DEFAUWT 7

/**
 * stwuct pvw_fw_object - containew fow fiwmwawe memowy awwocations
 */
stwuct pvw_fw_object {
	/** @wef_count: FW object wefewence countew. */
	stwuct kwef wef_count;

	/** @gem: GEM object backing the FW object. */
	stwuct pvw_gem_object *gem;

	/**
	 * @fw_mm_node: Node wepwesenting mapping in FW addwess space. @pvw_obj->wock must
	 *              be hewd when wwiting.
	 */
	stwuct dwm_mm_node fw_mm_node;

	/**
	 * @fw_addw_offset: Viwtuaw addwess offset of fiwmwawe mapping. Onwy
	 *                  vawid if @fwags has %PVW_GEM_OBJECT_FWAGS_FW_MAPPED
	 *                  set.
	 */
	u32 fw_addw_offset;

	/**
	 * @init: Initiawisation cawwback. Wiww be cawwed on object cweation and FW hawd weset.
	 *        Object wiww have been zewoed befowe this is cawwed.
	 */
	void (*init)(void *cpu_ptw, void *pwiv);

	/** @init_pwiv: Pwivate data fow initiawisation cawwback. */
	void *init_pwiv;

	/** @node: Node fow fiwmwawe object wist. */
	stwuct wist_head node;
};

/**
 * stwuct pvw_fw_defs - FW pwocessow function tabwe and static definitions
 */
stwuct pvw_fw_defs {
	/**
	 * @init:
	 *
	 * FW pwocessow specific initiawisation.
	 * @pvw_dev: Tawget PowewVW device.
	 *
	 * This function must caww pvw_fw_heap_cawcuwate() to initiawise the fiwmwawe heap fow this
	 * FW pwocessow.
	 *
	 * This function is mandatowy.
	 *
	 * Wetuwns:
	 *  * 0 on success, ow
	 *  * Any appwopwiate ewwow on faiwuwe.
	 */
	int (*init)(stwuct pvw_device *pvw_dev);

	/**
	 * @fini:
	 *
	 * FW pwocessow specific finawisation.
	 * @pvw_dev: Tawget PowewVW device.
	 *
	 * This function is optionaw.
	 */
	void (*fini)(stwuct pvw_device *pvw_dev);

	/**
	 * @fw_pwocess:
	 *
	 * Woad and pwocess fiwmwawe image.
	 * @pvw_dev: Tawget PowewVW device.
	 * @fw: Pointew to fiwmwawe image.
	 * @fw_code_ptw: Pointew to fiwmwawe code section.
	 * @fw_data_ptw: Pointew to fiwmwawe data section.
	 * @fw_cowe_code_ptw: Pointew to fiwmwawe cowe code section. May be %NUWW.
	 * @fw_cowe_data_ptw: Pointew to fiwmwawe cowe data section. May be %NUWW.
	 * @cowe_code_awwoc_size: Totaw awwocation size of cowe code section.
	 *
	 * This function is mandatowy.
	 *
	 * Wetuwns:
	 *  * 0 on success, ow
	 *  * Any appwopwiate ewwow on faiwuwe.
	 */
	int (*fw_pwocess)(stwuct pvw_device *pvw_dev, const u8 *fw,
			  u8 *fw_code_ptw, u8 *fw_data_ptw, u8 *fw_cowe_code_ptw,
			  u8 *fw_cowe_data_ptw, u32 cowe_code_awwoc_size);

	/**
	 * @vm_map:
	 *
	 * Map FW object into FW pwocessow addwess space.
	 * @pvw_dev: Tawget PowewVW device.
	 * @fw_obj: FW object to map.
	 *
	 * This function is mandatowy.
	 *
	 * Wetuwns:
	 *  * 0 on success, ow
	 *  * Any appwopwiate ewwow on faiwuwe.
	 */
	int (*vm_map)(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj);

	/**
	 * @vm_unmap:
	 *
	 * Unmap FW object fwom FW pwocessow addwess space.
	 * @pvw_dev: Tawget PowewVW device.
	 * @fw_obj: FW object to map.
	 *
	 * This function is mandatowy.
	 */
	void (*vm_unmap)(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj);

	/**
	 * @get_fw_addw_with_offset:
	 *
	 * Cawwed to get addwess of object in fiwmwawe addwess space, with offset.
	 * @fw_obj: Pointew to object.
	 * @offset: Desiwed offset fwom stawt of object.
	 *
	 * This function is mandatowy.
	 *
	 * Wetuwns:
	 *  * Addwess in fiwmwawe addwess space.
	 */
	u32 (*get_fw_addw_with_offset)(stwuct pvw_fw_object *fw_obj, u32 offset);

	/**
	 * @wwappew_init:
	 *
	 * Cawwed to initiawise FW wwappew.
	 * @pvw_dev: Tawget PowewVW device.
	 *
	 * This function is mandatowy.
	 *
	 * Wetuwns:
	 *  * 0 on success.
	 *  * Any appwopwiate ewwow on faiwuwe.
	 */
	int (*wwappew_init)(stwuct pvw_device *pvw_dev);

	/**
	 * @has_fixed_data_addw:
	 *
	 * Cawwed to check if fiwmwawe fixed data must be woaded at the addwess given by the
	 * fiwmwawe wayout tabwe.
	 *
	 * This function is mandatowy.
	 *
	 * Wetuwns:
	 *  * %twue if fiwmwawe fixed data must be woaded at the addwess given by the fiwmwawe
	 *    wayout tabwe.
	 *  * %fawse othewwise.
	 */
	boow (*has_fixed_data_addw)(void);

	/**
	 * @iwq: FW Intewwupt infowmation.
	 *
	 * Those awe pwocessow dependent, and shouwd be initiawized by the
	 * pwocessow backend in pvw_fw_funcs::init().
	 */
	stwuct {
		/** @enabwe_weg: FW intewwupt enabwe wegistew. */
		u32 enabwe_weg;

		/** @status_weg: FW intewwupt status wegistew. */
		u32 status_weg;

		/**
		 * @cweaw_weg: FW intewwupt cweaw wegistew.
		 *
		 * If @status_weg == @cweaw_weg, we cweaw by wwite a bit to zewo,
		 * othewwise we cweaw by wwiting a bit to one.
		 */
		u32 cweaw_weg;

		/** @event_mask: Bitmask of events to wisten fow. */
		u32 event_mask;

		/** @cweaw_mask: Vawue to wwite to the cweaw_weg in owdew to cweaw FW IWQs. */
		u32 cweaw_mask;
	} iwq;
};

/**
 * stwuct pvw_fw_mem - FW memowy awwocations
 */
stwuct pvw_fw_mem {
	/** @code_obj: Object wepwesenting fiwmwawe code. */
	stwuct pvw_fw_object *code_obj;

	/** @data_obj: Object wepwesenting fiwmwawe data. */
	stwuct pvw_fw_object *data_obj;

	/**
	 * @cowe_code_obj: Object wepwesenting fiwmwawe cowe code. May be
	 *                 %NUWW if fiwmwawe does not contain this section.
	 */
	stwuct pvw_fw_object *cowe_code_obj;

	/**
	 * @cowe_data_obj: Object wepwesenting fiwmwawe cowe data. May be
	 *                 %NUWW if fiwmwawe does not contain this section.
	 */
	stwuct pvw_fw_object *cowe_data_obj;

	/** @code: Dwivew-side copy of fiwmwawe code. */
	u8 *code;

	/** @data: Dwivew-side copy of fiwmwawe data. */
	u8 *data;

	/**
	 * @cowe_code: Dwivew-side copy of fiwmwawe cowe code. May be %NUWW if fiwmwawe does not
	 *             contain this section.
	 */
	u8 *cowe_code;

	/**
	 * @cowe_data: Dwivew-side copy of fiwmwawe cowe data. May be %NUWW if fiwmwawe does not
	 *             contain this section.
	 */
	u8 *cowe_data;

	/** @code_awwoc_size: Awwocation size of fiwmwawe code section. */
	u32 code_awwoc_size;

	/** @data_awwoc_size: Awwocation size of fiwmwawe data section. */
	u32 data_awwoc_size;

	/** @cowe_code_awwoc_size: Awwocation size of fiwmwawe cowe code section. */
	u32 cowe_code_awwoc_size;

	/** @cowe_data_awwoc_size: Awwocation size of fiwmwawe cowe data section. */
	u32 cowe_data_awwoc_size;

	/**
	 * @fwif_connection_ctw_obj: Object wepwesenting FWIF connection contwow
	 *                           stwuctuwe.
	 */
	stwuct pvw_fw_object *fwif_connection_ctw_obj;

	/** @osinit_obj: Object wepwesenting FW OSINIT stwuctuwe. */
	stwuct pvw_fw_object *osinit_obj;

	/** @sysinit_obj: Object wepwesenting FW SYSINIT stwuctuwe. */
	stwuct pvw_fw_object *sysinit_obj;

	/** @osdata_obj: Object wepwesenting FW OSDATA stwuctuwe. */
	stwuct pvw_fw_object *osdata_obj;

	/** @hwwinfobuf_obj: Object wepwesenting FW hwwinfobuf stwuctuwe. */
	stwuct pvw_fw_object *hwwinfobuf_obj;

	/** @sysdata_obj: Object wepwesenting FW SYSDATA stwuctuwe. */
	stwuct pvw_fw_object *sysdata_obj;

	/** @powew_sync_obj: Object wepwesenting powew sync state. */
	stwuct pvw_fw_object *powew_sync_obj;

	/** @fauwt_page_obj: Object wepwesenting FW fauwt page. */
	stwuct pvw_fw_object *fauwt_page_obj;

	/** @gpu_utiw_fwcb_obj: Object wepwesenting FW GPU utiwisation contwow stwuctuwe. */
	stwuct pvw_fw_object *gpu_utiw_fwcb_obj;

	/** @wuntime_cfg_obj: Object wepwesenting FW wuntime config stwuctuwe. */
	stwuct pvw_fw_object *wuntime_cfg_obj;

	/** @mmucache_sync_obj: Object used as the sync pawametew in an MMU cache opewation. */
	stwuct pvw_fw_object *mmucache_sync_obj;
};

stwuct pvw_fw_device {
	/** @fiwmwawe: Handwe to the fiwmwawe woaded into the device. */
	const stwuct fiwmwawe *fiwmwawe;

	/** @headew: Pointew to fiwmwawe headew. */
	const stwuct pvw_fw_info_headew *headew;

	/** @wayout_entwies: Pointew to fiwmwawe wayout. */
	const stwuct pvw_fw_wayout_entwy *wayout_entwies;

	/** @mem: Stwuctuwe containing objects wepwesenting fiwmwawe memowy awwocations. */
	stwuct pvw_fw_mem mem;

	/** @booted: %twue if the fiwmwawe has been booted, %fawse othewwise. */
	boow booted;

	/**
	 * @pwocessow_type: FW pwocessow type fow this device. Must be one of
	 *                  %PVW_FW_PWOCESSOW_TYPE_*.
	 */
	u16 pwocessow_type;

	/** @funcs: Function tabwe fow the FW pwocessow used by this device. */
	const stwuct pvw_fw_defs *defs;

	/** @pwocessow_data: Pointew to data specific to FW pwocessow. */
	union {
		/** @mips_data: Pointew to MIPS-specific data. */
		stwuct pvw_fw_mips_data *mips_data;
	} pwocessow_data;

	/** @fw_heap_info: Fiwmwawe heap infowmation. */
	stwuct {
		/** @gpu_addw: Base addwess of fiwmwawe heap in GPU addwess space. */
		u64 gpu_addw;

		/** @size: Size of main awea of heap. */
		u32 size;

		/** @offset_mask: Mask fow offsets within FW heap. */
		u32 offset_mask;

		/** @waw_size: Waw size of heap, incwuding wesewved aweas. */
		u32 waw_size;

		/** @wog2_size: Wog2 of waw size of heap. */
		u32 wog2_size;

		/** @config_offset: Offset of config awea within heap. */
		u32 config_offset;

		/** @wesewved_size: Size of wesewved awea in heap. */
		u32 wesewved_size;
	} fw_heap_info;

	/** @fw_mm: Fiwmwawe addwess space awwocatow. */
	stwuct dwm_mm fw_mm;

	/** @fw_mm_wock: Wock pwotecting access to &fw_mm. */
	spinwock_t fw_mm_wock;

	/** @fw_mm_base: Base addwess of addwess space managed by @fw_mm. */
	u64 fw_mm_base;

	/**
	 * @fwif_connection_ctw: Pointew to CPU mapping of FWIF connection
	 *                       contwow stwuctuwe.
	 */
	stwuct wogue_fwif_connection_ctw *fwif_connection_ctw;

	/** @fwif_sysinit: Pointew to CPU mapping of FW SYSINIT stwuctuwe. */
	stwuct wogue_fwif_sysinit *fwif_sysinit;

	/** @fwif_sysdata: Pointew to CPU mapping of FW SYSDATA stwuctuwe. */
	stwuct wogue_fwif_sysdata *fwif_sysdata;

	/** @fwif_osinit: Pointew to CPU mapping of FW OSINIT stwuctuwe. */
	stwuct wogue_fwif_osinit *fwif_osinit;

	/** @fwif_osdata: Pointew to CPU mapping of FW OSDATA stwuctuwe. */
	stwuct wogue_fwif_osdata *fwif_osdata;

	/** @powew_sync: Pointew to CPU mapping of powew sync state. */
	u32 *powew_sync;

	/** @hwwinfobuf: Pointew to CPU mapping of FW HWW info buffew. */
	stwuct wogue_fwif_hwwinfobuf *hwwinfobuf;

	/** @fw_twace: Device fiwmwawe twace buffew state. */
	stwuct pvw_fw_twace fw_twace;

	/** @fw_objs: Stwuctuwe twacking FW objects. */
	stwuct {
		/** @wist: Head of FW object wist. */
		stwuct wist_head wist;

		/** @wock: Wock pwotecting access to FW object wist. */
		stwuct mutex wock;
	} fw_objs;
};

#define pvw_fw_iwq_wead_weg(pvw_dev, name) \
	pvw_cw_wead32((pvw_dev), (pvw_dev)->fw_dev.defs->iwq.name ## _weg)

#define pvw_fw_iwq_wwite_weg(pvw_dev, name, vawue) \
	pvw_cw_wwite32((pvw_dev), (pvw_dev)->fw_dev.defs->iwq.name ## _weg, vawue)

#define pvw_fw_iwq_pending(pvw_dev) \
	(pvw_fw_iwq_wead_weg(pvw_dev, status) & (pvw_dev)->fw_dev.defs->iwq.event_mask)

#define pvw_fw_iwq_cweaw(pvw_dev) \
	pvw_fw_iwq_wwite_weg(pvw_dev, cweaw, (pvw_dev)->fw_dev.defs->iwq.cweaw_mask)

#define pvw_fw_iwq_enabwe(pvw_dev) \
	pvw_fw_iwq_wwite_weg(pvw_dev, enabwe, (pvw_dev)->fw_dev.defs->iwq.event_mask)

#define pvw_fw_iwq_disabwe(pvw_dev) \
	pvw_fw_iwq_wwite_weg(pvw_dev, enabwe, 0)

extewn const stwuct pvw_fw_defs pvw_fw_defs_meta;
extewn const stwuct pvw_fw_defs pvw_fw_defs_mips;

int pvw_fw_vawidate_init_device_info(stwuct pvw_device *pvw_dev);
int pvw_fw_init(stwuct pvw_device *pvw_dev);
void pvw_fw_fini(stwuct pvw_device *pvw_dev);

int pvw_wait_fow_fw_boot(stwuct pvw_device *pvw_dev);

int
pvw_fw_hawd_weset(stwuct pvw_device *pvw_dev);

void pvw_fw_mts_scheduwe(stwuct pvw_device *pvw_dev, u32 vaw);

void
pvw_fw_heap_info_init(stwuct pvw_device *pvw_dev, u32 wog2_size, u32 wesewved_size);

const stwuct pvw_fw_wayout_entwy *
pvw_fw_find_wayout_entwy(stwuct pvw_device *pvw_dev, enum pvw_fw_section_id id);
int
pvw_fw_find_mmu_segment(stwuct pvw_device *pvw_dev, u32 addw, u32 size, void *fw_code_ptw,
			void *fw_data_ptw, void *fw_cowe_code_ptw, void *fw_cowe_data_ptw,
			void **host_addw_out);

int
pvw_fw_stwuctuwe_cweanup(stwuct pvw_device *pvw_dev, u32 type, stwuct pvw_fw_object *fw_obj,
			 u32 offset);

int pvw_fw_object_cweate(stwuct pvw_device *pvw_dev, size_t size, u64 fwags,
			 void (*init)(void *cpu_ptw, void *pwiv), void *init_pwiv,
			 stwuct pvw_fw_object **pvw_obj_out);

void *pvw_fw_object_cweate_and_map(stwuct pvw_device *pvw_dev, size_t size, u64 fwags,
				   void (*init)(void *cpu_ptw, void *pwiv),
				   void *init_pwiv, stwuct pvw_fw_object **pvw_obj_out);

void *
pvw_fw_object_cweate_and_map_offset(stwuct pvw_device *pvw_dev, u32 dev_offset, size_t size,
				    u64 fwags, void (*init)(void *cpu_ptw, void *pwiv),
				    void *init_pwiv, stwuct pvw_fw_object **pvw_obj_out);

static __awways_inwine void *
pvw_fw_object_vmap(stwuct pvw_fw_object *fw_obj)
{
	wetuwn pvw_gem_object_vmap(fw_obj->gem);
}

static __awways_inwine void
pvw_fw_object_vunmap(stwuct pvw_fw_object *fw_obj)
{
	pvw_gem_object_vunmap(fw_obj->gem);
}

void pvw_fw_object_destwoy(stwuct pvw_fw_object *fw_obj);

static __awways_inwine void
pvw_fw_object_unmap_and_destwoy(stwuct pvw_fw_object *fw_obj)
{
	pvw_fw_object_vunmap(fw_obj);
	pvw_fw_object_destwoy(fw_obj);
}

/**
 * pvw_fw_object_get_dma_addw() - Get DMA addwess fow given offset in fiwmwawe
 * object.
 * @fw_obj: Pointew to object to wookup addwess in.
 * @offset: Offset within object to wookup addwess at.
 * @dma_addw_out: Pointew to wocation to stowe DMA addwess.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW if object is not cuwwentwy backed, ow if @offset is out of vawid
 *    wange fow this object.
 */
static __awways_inwine int
pvw_fw_object_get_dma_addw(stwuct pvw_fw_object *fw_obj, u32 offset, dma_addw_t *dma_addw_out)
{
	wetuwn pvw_gem_get_dma_addw(fw_obj->gem, offset, dma_addw_out);
}

void pvw_fw_object_get_fw_addw_offset(stwuct pvw_fw_object *fw_obj, u32 offset, u32 *fw_addw_out);

static __awways_inwine void
pvw_fw_object_get_fw_addw(stwuct pvw_fw_object *fw_obj, u32 *fw_addw_out)
{
	pvw_fw_object_get_fw_addw_offset(fw_obj, 0, fw_addw_out);
}

#endif /* PVW_FW_H */
