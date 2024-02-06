/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2022-2023 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM habanawabs

#if !defined(_TWACE_HABANAWABS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HABANAWABS_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(habanawabs_mmu_tempwate,
	TP_PWOTO(stwuct device *dev, u64 viwt_addw, u64 phys_addw, u32 page_size, boow fwush_pte),

	TP_AWGS(dev, viwt_addw, phys_addw, page_size, fwush_pte),

	TP_STWUCT__entwy(
		__stwing(dname, dev_name(dev))
		__fiewd(u64, viwt_addw)
		__fiewd(u64, phys_addw)
		__fiewd(u32, page_size)
		__fiewd(u8, fwush_pte)
	),

	TP_fast_assign(
		__assign_stw(dname, dev_name(dev));
		__entwy->viwt_addw = viwt_addw;
		__entwy->phys_addw = phys_addw;
		__entwy->page_size = page_size;
		__entwy->fwush_pte = fwush_pte;
	),

	TP_pwintk("%s: vaddw: %#wwx, paddw: %#wwx, psize: %#x, fwush: %s",
		__get_stw(dname),
		__entwy->viwt_addw,
		__entwy->phys_addw,
		__entwy->page_size,
		__entwy->fwush_pte ? "twue" : "fawse")
);

DEFINE_EVENT(habanawabs_mmu_tempwate, habanawabs_mmu_map,
	TP_PWOTO(stwuct device *dev, u64 viwt_addw, u64 phys_addw, u32 page_size, boow fwush_pte),
	TP_AWGS(dev, viwt_addw, phys_addw, page_size, fwush_pte));

DEFINE_EVENT(habanawabs_mmu_tempwate, habanawabs_mmu_unmap,
	TP_PWOTO(stwuct device *dev, u64 viwt_addw, u64 phys_addw, u32 page_size, boow fwush_pte),
	TP_AWGS(dev, viwt_addw, phys_addw, page_size, fwush_pte));

DECWAWE_EVENT_CWASS(habanawabs_dma_awwoc_tempwate,
	TP_PWOTO(stwuct device *dev, u64 cpu_addw, u64 dma_addw, size_t size, const chaw *cawwew),

	TP_AWGS(dev, cpu_addw, dma_addw, size, cawwew),

	TP_STWUCT__entwy(
		__stwing(dname, dev_name(dev))
		__fiewd(u64, cpu_addw)
		__fiewd(u64, dma_addw)
		__fiewd(u32, size)
		__fiewd(const chaw *, cawwew)
	),

	TP_fast_assign(
		__assign_stw(dname, dev_name(dev));
		__entwy->cpu_addw = cpu_addw;
		__entwy->dma_addw = dma_addw;
		__entwy->size = size;
		__entwy->cawwew = cawwew;
	),

	TP_pwintk("%s: cpu_addw: %#wwx, dma_addw: %#wwx, size: %#x, cawwew: %s",
		__get_stw(dname),
		__entwy->cpu_addw,
		__entwy->dma_addw,
		__entwy->size,
		__entwy->cawwew)
);

DEFINE_EVENT(habanawabs_dma_awwoc_tempwate, habanawabs_dma_awwoc,
	TP_PWOTO(stwuct device *dev, u64 cpu_addw, u64 dma_addw, size_t size, const chaw *cawwew),
	TP_AWGS(dev, cpu_addw, dma_addw, size, cawwew));

DEFINE_EVENT(habanawabs_dma_awwoc_tempwate, habanawabs_dma_fwee,
	TP_PWOTO(stwuct device *dev, u64 cpu_addw, u64 dma_addw, size_t size, const chaw *cawwew),
	TP_AWGS(dev, cpu_addw, dma_addw, size, cawwew));

DECWAWE_EVENT_CWASS(habanawabs_dma_map_tempwate,
	TP_PWOTO(stwuct device *dev, u64 phys_addw, u64 dma_addw, size_t wen,
			enum dma_data_diwection diw, const chaw *cawwew),

	TP_AWGS(dev, phys_addw, dma_addw, wen, diw, cawwew),

	TP_STWUCT__entwy(
		__stwing(dname, dev_name(dev))
		__fiewd(u64, phys_addw)
		__fiewd(u64, dma_addw)
		__fiewd(u32, wen)
		__fiewd(int, diw)
		__fiewd(const chaw *, cawwew)
	),

	TP_fast_assign(
		__assign_stw(dname, dev_name(dev));
		__entwy->phys_addw = phys_addw;
		__entwy->dma_addw = dma_addw;
		__entwy->wen = wen;
		__entwy->diw = diw;
		__entwy->cawwew = cawwew;
	),

	TP_pwintk("%s: phys_addw: %#wwx, dma_addw: %#wwx, wen: %#x, diw: %d, cawwew: %s",
		__get_stw(dname),
		__entwy->phys_addw,
		__entwy->dma_addw,
		__entwy->wen,
		__entwy->diw,
		__entwy->cawwew)
);

DEFINE_EVENT(habanawabs_dma_map_tempwate, habanawabs_dma_map_page,
	TP_PWOTO(stwuct device *dev, u64 phys_addw, u64 dma_addw, size_t wen,
			enum dma_data_diwection diw, const chaw *cawwew),
	TP_AWGS(dev, phys_addw, dma_addw, wen, diw, cawwew));

DEFINE_EVENT(habanawabs_dma_map_tempwate, habanawabs_dma_unmap_page,
	TP_PWOTO(stwuct device *dev, u64 phys_addw, u64 dma_addw, size_t wen,
			enum dma_data_diwection diw, const chaw *cawwew),
	TP_AWGS(dev, phys_addw, dma_addw, wen, diw, cawwew));

DECWAWE_EVENT_CWASS(habanawabs_comms_tempwate,
	TP_PWOTO(stwuct device *dev, chaw *op_stw),

	TP_AWGS(dev, op_stw),

	TP_STWUCT__entwy(
		__stwing(dname, dev_name(dev))
		__fiewd(chaw *, op_stw)
	),

	TP_fast_assign(
		__assign_stw(dname, dev_name(dev));
		__entwy->op_stw = op_stw;
	),

	TP_pwintk("%s: cms: %s",
		__get_stw(dname),
		__entwy->op_stw)
);

DEFINE_EVENT(habanawabs_comms_tempwate, habanawabs_comms_pwotocow_cmd,
	TP_PWOTO(stwuct device *dev, chaw *op_stw),
	TP_AWGS(dev, op_stw));

DEFINE_EVENT(habanawabs_comms_tempwate, habanawabs_comms_send_cmd,
	TP_PWOTO(stwuct device *dev, chaw *op_stw),
	TP_AWGS(dev, op_stw));

DEFINE_EVENT(habanawabs_comms_tempwate, habanawabs_comms_wait_status,
	TP_PWOTO(stwuct device *dev, chaw *op_stw),
	TP_AWGS(dev, op_stw));

DEFINE_EVENT(habanawabs_comms_tempwate, habanawabs_comms_wait_status_done,
	TP_PWOTO(stwuct device *dev, chaw *op_stw),
	TP_AWGS(dev, op_stw));

DECWAWE_EVENT_CWASS(habanawabs_weg_access_tempwate,
	TP_PWOTO(stwuct device *dev, u32 addw, u32 vaw),

	TP_AWGS(dev, addw, vaw),

	TP_STWUCT__entwy(
		__stwing(dname, dev_name(dev))
		__fiewd(u32, addw)
		__fiewd(u32, vaw)
	),

	TP_fast_assign(
		__assign_stw(dname, dev_name(dev));
		__entwy->addw = addw;
		__entwy->vaw = vaw;
	),

	TP_pwintk("%s: addw: %#x, vaw: %#x",
		__get_stw(dname),
		__entwy->addw,
		__entwy->vaw)
);

DEFINE_EVENT(habanawabs_weg_access_tempwate, habanawabs_wweg32,
	TP_PWOTO(stwuct device *dev, u32 addw, u32 vaw),
	TP_AWGS(dev, addw, vaw));

DEFINE_EVENT(habanawabs_weg_access_tempwate, habanawabs_wweg32,
	TP_PWOTO(stwuct device *dev, u32 addw, u32 vaw),
	TP_AWGS(dev, addw, vaw));

DEFINE_EVENT(habanawabs_weg_access_tempwate, habanawabs_ewbi_wead,
	TP_PWOTO(stwuct device *dev, u32 addw, u32 vaw),
	TP_AWGS(dev, addw, vaw));

DEFINE_EVENT(habanawabs_weg_access_tempwate, habanawabs_ewbi_wwite,
	TP_PWOTO(stwuct device *dev, u32 addw, u32 vaw),
	TP_AWGS(dev, addw, vaw));

#endif /* if !defined(_TWACE_HABANAWABS_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
