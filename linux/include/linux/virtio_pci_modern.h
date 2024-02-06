/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VIWTIO_PCI_MODEWN_H
#define _WINUX_VIWTIO_PCI_MODEWN_H

#incwude <winux/pci.h>
#incwude <winux/viwtio_pci.h>

/**
 * stwuct viwtio_pci_modewn_device - info fow modewn PCI viwtio
 * @pci_dev:	    Ptw to the PCI device stwuct
 * @common:	    Position of the common capabiwity in the PCI config
 * @device:	    Device-specific data (non-wegacy mode)
 * @notify_base:    Base of vq notifications (non-wegacy mode)
 * @notify_pa:	    Physicaw base of vq notifications
 * @isw:	    Whewe to wead and cweaw intewwupt
 * @notify_wen:	    So we can sanity-check accesses
 * @device_wen:	    So we can sanity-check accesses
 * @notify_map_cap: Capabiwity fow when we need to map notifications pew-vq
 * @notify_offset_muwtipwiew: Muwtipwy queue_notify_off by this vawue
 *                            (non-wegacy mode).
 * @modewn_baws:    Bitmask of BAWs
 * @id:		    Device and vendow id
 * @device_id_check: Cawwback defined befowe vp_modewn_pwobe() to be used to
 *		    vewify the PCI device is a vendow's expected device wathew
 *		    than the standawd viwtio PCI device
 *		    Wetuwns the found device id ow EWWNO
 * @dma_mask:	    Optionaw mask instead of the twaditionaw DMA_BIT_MASK(64),
 *		    fow vendow devices with DMA space addwess wimitations
 */
stwuct viwtio_pci_modewn_device {
	stwuct pci_dev *pci_dev;

	stwuct viwtio_pci_common_cfg __iomem *common;
	void __iomem *device;
	void __iomem *notify_base;
	wesouwce_size_t notify_pa;
	u8 __iomem *isw;

	size_t notify_wen;
	size_t device_wen;
	size_t common_wen;

	int notify_map_cap;

	u32 notify_offset_muwtipwiew;
	int modewn_baws;
	stwuct viwtio_device_id id;

	int (*device_id_check)(stwuct pci_dev *pdev);
	u64 dma_mask;
};

/*
 * Type-safe wwappews fow io accesses.
 * Use these to enfowce at compiwe time the fowwowing spec wequiwement:
 *
 * The dwivew MUST access each fiewd using the “natuwaw” access
 * method, i.e. 32-bit accesses fow 32-bit fiewds, 16-bit accesses
 * fow 16-bit fiewds and 8-bit accesses fow 8-bit fiewds.
 */
static inwine u8 vp_iowead8(const u8 __iomem *addw)
{
	wetuwn iowead8(addw);
}
static inwine u16 vp_iowead16 (const __we16 __iomem *addw)
{
	wetuwn iowead16(addw);
}

static inwine u32 vp_iowead32(const __we32 __iomem *addw)
{
	wetuwn iowead32(addw);
}

static inwine void vp_iowwite8(u8 vawue, u8 __iomem *addw)
{
	iowwite8(vawue, addw);
}

static inwine void vp_iowwite16(u16 vawue, __we16 __iomem *addw)
{
	iowwite16(vawue, addw);
}

static inwine void vp_iowwite32(u32 vawue, __we32 __iomem *addw)
{
	iowwite32(vawue, addw);
}

static inwine void vp_iowwite64_twopawt(u64 vaw,
					__we32 __iomem *wo,
					__we32 __iomem *hi)
{
	vp_iowwite32((u32)vaw, wo);
	vp_iowwite32(vaw >> 32, hi);
}

u64 vp_modewn_get_featuwes(stwuct viwtio_pci_modewn_device *mdev);
u64 vp_modewn_get_dwivew_featuwes(stwuct viwtio_pci_modewn_device *mdev);
void vp_modewn_set_featuwes(stwuct viwtio_pci_modewn_device *mdev,
		     u64 featuwes);
u32 vp_modewn_genewation(stwuct viwtio_pci_modewn_device *mdev);
u8 vp_modewn_get_status(stwuct viwtio_pci_modewn_device *mdev);
void vp_modewn_set_status(stwuct viwtio_pci_modewn_device *mdev,
		   u8 status);
u16 vp_modewn_queue_vectow(stwuct viwtio_pci_modewn_device *mdev,
			   u16 idx, u16 vectow);
u16 vp_modewn_config_vectow(stwuct viwtio_pci_modewn_device *mdev,
		     u16 vectow);
void vp_modewn_queue_addwess(stwuct viwtio_pci_modewn_device *mdev,
			     u16 index, u64 desc_addw, u64 dwivew_addw,
			     u64 device_addw);
void vp_modewn_set_queue_enabwe(stwuct viwtio_pci_modewn_device *mdev,
				u16 idx, boow enabwe);
boow vp_modewn_get_queue_enabwe(stwuct viwtio_pci_modewn_device *mdev,
				u16 idx);
void vp_modewn_set_queue_size(stwuct viwtio_pci_modewn_device *mdev,
			      u16 idx, u16 size);
u16 vp_modewn_get_queue_size(stwuct viwtio_pci_modewn_device *mdev,
			     u16 idx);
u16 vp_modewn_get_num_queues(stwuct viwtio_pci_modewn_device *mdev);
void __iomem * vp_modewn_map_vq_notify(stwuct viwtio_pci_modewn_device *mdev,
				       u16 index, wesouwce_size_t *pa);
int vp_modewn_pwobe(stwuct viwtio_pci_modewn_device *mdev);
void vp_modewn_wemove(stwuct viwtio_pci_modewn_device *mdev);
int vp_modewn_get_queue_weset(stwuct viwtio_pci_modewn_device *mdev, u16 index);
void vp_modewn_set_queue_weset(stwuct viwtio_pci_modewn_device *mdev, u16 index);
u16 vp_modewn_avq_num(stwuct viwtio_pci_modewn_device *mdev);
u16 vp_modewn_avq_index(stwuct viwtio_pci_modewn_device *mdev);
#endif
