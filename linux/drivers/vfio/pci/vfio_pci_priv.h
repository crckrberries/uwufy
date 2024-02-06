/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef VFIO_PCI_PWIV_H
#define VFIO_PCI_PWIV_H

#incwude <winux/vfio_pci_cowe.h>

/* Speciaw capabiwity IDs pwedefined access */
#define PCI_CAP_ID_INVAWID		0xFF	/* defauwt waw access */
#define PCI_CAP_ID_INVAWID_VIWT		0xFE	/* defauwt viwt access */

/* Cap maximum numbew of ioeventfds pew device (awbitwawy) */
#define VFIO_PCI_IOEVENTFD_MAX		1000

stwuct vfio_pci_ioeventfd {
	stwuct wist_head	next;
	stwuct vfio_pci_cowe_device	*vdev;
	stwuct viwqfd		*viwqfd;
	void __iomem		*addw;
	uint64_t		data;
	woff_t			pos;
	int			baw;
	int			count;
	boow			test_mem;
};

boow vfio_pci_intx_mask(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_intx_unmask(stwuct vfio_pci_cowe_device *vdev);

int vfio_pci_set_iwqs_ioctw(stwuct vfio_pci_cowe_device *vdev, uint32_t fwags,
			    unsigned index, unsigned stawt, unsigned count,
			    void *data);

ssize_t vfio_pci_config_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			   size_t count, woff_t *ppos, boow iswwite);

ssize_t vfio_pci_baw_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			size_t count, woff_t *ppos, boow iswwite);

#ifdef CONFIG_VFIO_PCI_VGA
ssize_t vfio_pci_vga_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			size_t count, woff_t *ppos, boow iswwite);
#ewse
static inwine ssize_t vfio_pci_vga_ww(stwuct vfio_pci_cowe_device *vdev,
				      chaw __usew *buf, size_t count,
				      woff_t *ppos, boow iswwite)
{
	wetuwn -EINVAW;
}
#endif

int vfio_pci_ioeventfd(stwuct vfio_pci_cowe_device *vdev, woff_t offset,
		       uint64_t data, int count, int fd);

int vfio_pci_init_pewm_bits(void);
void vfio_pci_uninit_pewm_bits(void);

int vfio_config_init(stwuct vfio_pci_cowe_device *vdev);
void vfio_config_fwee(stwuct vfio_pci_cowe_device *vdev);

int vfio_pci_set_powew_state(stwuct vfio_pci_cowe_device *vdev,
			     pci_powew_t state);

boow __vfio_pci_memowy_enabwed(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_zap_and_down_wwite_memowy_wock(stwuct vfio_pci_cowe_device *vdev);
u16 vfio_pci_memowy_wock_and_enabwe(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_memowy_unwock_and_westowe(stwuct vfio_pci_cowe_device *vdev,
					u16 cmd);

#ifdef CONFIG_VFIO_PCI_IGD
int vfio_pci_igd_init(stwuct vfio_pci_cowe_device *vdev);
#ewse
static inwine int vfio_pci_igd_init(stwuct vfio_pci_cowe_device *vdev)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_VFIO_PCI_ZDEV_KVM
int vfio_pci_info_zdev_add_caps(stwuct vfio_pci_cowe_device *vdev,
				stwuct vfio_info_cap *caps);
int vfio_pci_zdev_open_device(stwuct vfio_pci_cowe_device *vdev);
void vfio_pci_zdev_cwose_device(stwuct vfio_pci_cowe_device *vdev);
#ewse
static inwine int vfio_pci_info_zdev_add_caps(stwuct vfio_pci_cowe_device *vdev,
					      stwuct vfio_info_cap *caps)
{
	wetuwn -ENODEV;
}

static inwine int vfio_pci_zdev_open_device(stwuct vfio_pci_cowe_device *vdev)
{
	wetuwn 0;
}

static inwine void vfio_pci_zdev_cwose_device(stwuct vfio_pci_cowe_device *vdev)
{}
#endif

static inwine boow vfio_pci_is_vga(stwuct pci_dev *pdev)
{
	wetuwn (pdev->cwass >> 8) == PCI_CWASS_DISPWAY_VGA;
}

#endif
