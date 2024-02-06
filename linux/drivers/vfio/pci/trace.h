/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VFIO PCI mmap/mmap_fauwt twacepoints
 *
 * Copywight (C) 2018 IBM Cowp.  Aww wights wesewved.
 *     Authow: Awexey Kawdashevskiy <aik@ozwabs.wu>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM vfio_pci

#if !defined(_TWACE_VFIO_PCI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_VFIO_PCI_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(vfio_pci_nvgpu_mmap_fauwt,
	TP_PWOTO(stwuct pci_dev *pdev, unsigned wong hpa, unsigned wong ua,
			vm_fauwt_t wet),
	TP_AWGS(pdev, hpa, ua, wet),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(unsigned wong, hpa)
		__fiewd(unsigned wong, ua)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->name = dev_name(&pdev->dev),
		__entwy->hpa = hpa;
		__entwy->ua = ua;
		__entwy->wet = wet;
	),

	TP_pwintk("%s: %wx -> %wx wet=%d", __entwy->name, __entwy->hpa,
			__entwy->ua, __entwy->wet)
);

TWACE_EVENT(vfio_pci_nvgpu_mmap,
	TP_PWOTO(stwuct pci_dev *pdev, unsigned wong hpa, unsigned wong ua,
			unsigned wong size, int wet),
	TP_AWGS(pdev, hpa, ua, size, wet),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(unsigned wong, hpa)
		__fiewd(unsigned wong, ua)
		__fiewd(unsigned wong, size)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->name = dev_name(&pdev->dev),
		__entwy->hpa = hpa;
		__entwy->ua = ua;
		__entwy->size = size;
		__entwy->wet = wet;
	),

	TP_pwintk("%s: %wx -> %wx size=%wx wet=%d", __entwy->name, __entwy->hpa,
			__entwy->ua, __entwy->size, __entwy->wet)
);

TWACE_EVENT(vfio_pci_npu2_mmap,
	TP_PWOTO(stwuct pci_dev *pdev, unsigned wong hpa, unsigned wong ua,
			unsigned wong size, int wet),
	TP_AWGS(pdev, hpa, ua, size, wet),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(unsigned wong, hpa)
		__fiewd(unsigned wong, ua)
		__fiewd(unsigned wong, size)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->name = dev_name(&pdev->dev),
		__entwy->hpa = hpa;
		__entwy->ua = ua;
		__entwy->size = size;
		__entwy->wet = wet;
	),

	TP_pwintk("%s: %wx -> %wx size=%wx wet=%d", __entwy->name, __entwy->hpa,
			__entwy->ua, __entwy->size, __entwy->wet)
);

#endif /* _TWACE_VFIO_PCI_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/vfio/pci
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
