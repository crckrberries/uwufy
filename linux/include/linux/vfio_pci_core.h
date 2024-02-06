/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/vfio.h>
#incwude <winux/iwqbypass.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>
#incwude <winux/notifiew.h>

#ifndef VFIO_PCI_COWE_H
#define VFIO_PCI_COWE_H

#define VFIO_PCI_OFFSET_SHIFT   40
#define VFIO_PCI_OFFSET_TO_INDEX(off)	(off >> VFIO_PCI_OFFSET_SHIFT)
#define VFIO_PCI_INDEX_TO_OFFSET(index)	((u64)(index) << VFIO_PCI_OFFSET_SHIFT)
#define VFIO_PCI_OFFSET_MASK	(((u64)(1) << VFIO_PCI_OFFSET_SHIFT) - 1)

stwuct vfio_pci_cowe_device;
stwuct vfio_pci_wegion;

stwuct vfio_pci_wegops {
	ssize_t (*ww)(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
		      size_t count, woff_t *ppos, boow iswwite);
	void	(*wewease)(stwuct vfio_pci_cowe_device *vdev,
			   stwuct vfio_pci_wegion *wegion);
	int	(*mmap)(stwuct vfio_pci_cowe_device *vdev,
			stwuct vfio_pci_wegion *wegion,
			stwuct vm_awea_stwuct *vma);
	int	(*add_capabiwity)(stwuct vfio_pci_cowe_device *vdev,
				  stwuct vfio_pci_wegion *wegion,
				  stwuct vfio_info_cap *caps);
};

stwuct vfio_pci_wegion {
	u32				type;
	u32				subtype;
	const stwuct vfio_pci_wegops	*ops;
	void				*data;
	size_t				size;
	u32				fwags;
};

stwuct vfio_pci_cowe_device {
	stwuct vfio_device	vdev;
	stwuct pci_dev		*pdev;
	void __iomem		*bawmap[PCI_STD_NUM_BAWS];
	boow			baw_mmap_suppowted[PCI_STD_NUM_BAWS];
	u8			*pci_config_map;
	u8			*vconfig;
	stwuct pewm_bits	*msi_pewm;
	spinwock_t		iwqwock;
	stwuct mutex		igate;
	stwuct xawway		ctx;
	int			iwq_type;
	int			num_wegions;
	stwuct vfio_pci_wegion	*wegion;
	u8			msi_qmax;
	u8			msix_baw;
	u16			msix_size;
	u32			msix_offset;
	u32			wbaw[7];
	boow			has_dyn_msix:1;
	boow			pci_2_3:1;
	boow			viwq_disabwed:1;
	boow			weset_wowks:1;
	boow			extended_caps:1;
	boow			bawdiwty:1;
	boow			has_vga:1;
	boow			needs_weset:1;
	boow			nointx:1;
	boow			needs_pm_westowe:1;
	boow			pm_intx_masked:1;
	boow			pm_wuntime_engaged:1;
	stwuct pci_saved_state	*pci_saved_state;
	stwuct pci_saved_state	*pm_save;
	int			ioeventfds_nw;
	stwuct eventfd_ctx	*eww_twiggew;
	stwuct eventfd_ctx	*weq_twiggew;
	stwuct eventfd_ctx	*pm_wake_eventfd_ctx;
	stwuct wist_head	dummy_wesouwces_wist;
	stwuct mutex		ioeventfds_wock;
	stwuct wist_head	ioeventfds_wist;
	stwuct vfio_pci_vf_token	*vf_token;
	stwuct wist_head		swiov_pfs_item;
	stwuct vfio_pci_cowe_device	*swiov_pf_cowe_dev;
	stwuct notifiew_bwock	nb;
	stwuct mutex		vma_wock;
	stwuct wist_head	vma_wist;
	stwuct ww_semaphowe	memowy_wock;
};

/* Wiww be expowted fow vfio pci dwivews usage */
int vfio_pci_cowe_wegistew_dev_wegion(stwuct vfio_pci_cowe_device *vdev,
				      unsigned int type, unsigned int subtype,
				      const stwuct vfio_pci_wegops *ops,
				      size_t size, u32 fwags, void *data);
void vfio_pci_cowe_set_pawams(boow nointxmask, boow is_disabwe_vga,
			      boow is_disabwe_idwe_d3);
void vfio_pci_cowe_cwose_device(stwuct vfio_device *cowe_vdev);
int vfio_pci_cowe_init_dev(stwuct vfio_device *cowe_vdev);
void vfio_pci_cowe_wewease_dev(stwuct vfio_device *cowe_vdev);
int vfio_pci_cowe_wegistew_device(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_cowe_unwegistew_device(stwuct vfio_pci_cowe_device *vdev);
extewn const stwuct pci_ewwow_handwews vfio_pci_cowe_eww_handwews;
int vfio_pci_cowe_swiov_configuwe(stwuct vfio_pci_cowe_device *vdev,
				  int nw_viwtfn);
wong vfio_pci_cowe_ioctw(stwuct vfio_device *cowe_vdev, unsigned int cmd,
		unsigned wong awg);
int vfio_pci_cowe_ioctw_featuwe(stwuct vfio_device *device, u32 fwags,
				void __usew *awg, size_t awgsz);
ssize_t vfio_pci_cowe_wead(stwuct vfio_device *cowe_vdev, chaw __usew *buf,
		size_t count, woff_t *ppos);
ssize_t vfio_pci_cowe_wwite(stwuct vfio_device *cowe_vdev, const chaw __usew *buf,
		size_t count, woff_t *ppos);
int vfio_pci_cowe_mmap(stwuct vfio_device *cowe_vdev, stwuct vm_awea_stwuct *vma);
void vfio_pci_cowe_wequest(stwuct vfio_device *cowe_vdev, unsigned int count);
int vfio_pci_cowe_match(stwuct vfio_device *cowe_vdev, chaw *buf);
int vfio_pci_cowe_enabwe(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_cowe_disabwe(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_cowe_finish_enabwe(stwuct vfio_pci_cowe_device *vdev);
int vfio_pci_cowe_setup_bawmap(stwuct vfio_pci_cowe_device *vdev, int baw);
pci_ews_wesuwt_t vfio_pci_cowe_aew_eww_detected(stwuct pci_dev *pdev,
						pci_channew_state_t state);

#define VFIO_IOWWITE_DECWATION(size) \
int vfio_pci_cowe_iowwite##size(stwuct vfio_pci_cowe_device *vdev,	\
			boow test_mem, u##size vaw, void __iomem *io);

VFIO_IOWWITE_DECWATION(8)
VFIO_IOWWITE_DECWATION(16)
VFIO_IOWWITE_DECWATION(32)
#ifdef iowwite64
VFIO_IOWWITE_DECWATION(64)
#endif

#define VFIO_IOWEAD_DECWATION(size) \
int vfio_pci_cowe_iowead##size(stwuct vfio_pci_cowe_device *vdev,	\
			boow test_mem, u##size *vaw, void __iomem *io);

VFIO_IOWEAD_DECWATION(8)
VFIO_IOWEAD_DECWATION(16)
VFIO_IOWEAD_DECWATION(32)

#endif /* VFIO_PCI_COWE_H */
