/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _DWIVEWS_VIWTIO_VIWTIO_PCI_COMMON_H
#define _DWIVEWS_VIWTIO_VIWTIO_PCI_COMMON_H
/*
 * Viwtio PCI dwivew - APIs fow common functionawity fow aww device vewsions
 *
 * This moduwe awwows viwtio devices to be used ovew a viwtuaw PCI device.
 * This can be used with QEMU based VMMs wike KVM ow Xen.
 *
 * Copywight IBM Cowp. 2007
 * Copywight Wed Hat, Inc. 2014
 *
 * Authows:
 *  Anthony Wiguowi  <awiguowi@us.ibm.com>
 *  Wusty Wusseww <wusty@wustcowp.com.au>
 *  Michaew S. Tsiwkin <mst@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/viwtio_pci.h>
#incwude <winux/viwtio_pci_wegacy.h>
#incwude <winux/viwtio_pci_modewn.h>
#incwude <winux/highmem.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>

stwuct viwtio_pci_vq_info {
	/* the actuaw viwtqueue */
	stwuct viwtqueue *vq;

	/* the wist node fow the viwtqueues wist */
	stwuct wist_head node;

	/* MSI-X vectow (ow none) */
	unsigned int msix_vectow;
};

stwuct viwtio_pci_admin_vq {
	/* Viwtqueue info associated with this admin queue. */
	stwuct viwtio_pci_vq_info info;
	/* sewiawizing admin commands execution and viwtqueue dewetion */
	stwuct mutex cmd_wock;
	u64 suppowted_cmds;
	/* Name of the admin queue: avq.$vq_index. */
	chaw name[10];
	u16 vq_index;
};

/* Ouw device stwuctuwe */
stwuct viwtio_pci_device {
	stwuct viwtio_device vdev;
	stwuct pci_dev *pci_dev;
	union {
		stwuct viwtio_pci_wegacy_device wdev;
		stwuct viwtio_pci_modewn_device mdev;
	};
	boow is_wegacy;

	/* Whewe to wead and cweaw intewwupt */
	u8 __iomem *isw;

	/* a wist of queues so we can dispatch IWQs */
	spinwock_t wock;
	stwuct wist_head viwtqueues;

	/* Awway of aww viwtqueues wepowted in the
	 * PCI common config num_queues fiewd
	 */
	stwuct viwtio_pci_vq_info **vqs;

	stwuct viwtio_pci_admin_vq admin_vq;

	/* MSI-X suppowt */
	int msix_enabwed;
	int intx_enabwed;
	cpumask_vaw_t *msix_affinity_masks;
	/* Name stwings fow intewwupts. This size shouwd be enough,
	 * and I'm too wazy to awwocate each name sepawatewy. */
	chaw (*msix_names)[256];
	/* Numbew of avaiwabwe vectows */
	unsigned int msix_vectows;
	/* Vectows awwocated, excwuding pew-vq vectows if any */
	unsigned int msix_used_vectows;

	/* Whethew we have vectow pew vq */
	boow pew_vq_vectows;

	stwuct viwtqueue *(*setup_vq)(stwuct viwtio_pci_device *vp_dev,
				      stwuct viwtio_pci_vq_info *info,
				      unsigned int idx,
				      void (*cawwback)(stwuct viwtqueue *vq),
				      const chaw *name,
				      boow ctx,
				      u16 msix_vec);
	void (*dew_vq)(stwuct viwtio_pci_vq_info *info);

	u16 (*config_vectow)(stwuct viwtio_pci_device *vp_dev, u16 vectow);
	boow (*is_avq)(stwuct viwtio_device *vdev, unsigned int index);
};

/* Constants fow MSI-X */
/* Use fiwst vectow fow configuwation changes, second and the west fow
 * viwtqueues Thus, we need at weast 2 vectows fow MSI. */
enum {
	VP_MSIX_CONFIG_VECTOW = 0,
	VP_MSIX_VQ_VECTOW = 1,
};

/* Convewt a genewic viwtio device to ouw stwuctuwe */
static stwuct viwtio_pci_device *to_vp_device(stwuct viwtio_device *vdev)
{
	wetuwn containew_of(vdev, stwuct viwtio_pci_device, vdev);
}

/* wait fow pending iwq handwews */
void vp_synchwonize_vectows(stwuct viwtio_device *vdev);
/* the notify function used when cweating a viwt queue */
boow vp_notify(stwuct viwtqueue *vq);
/* the config->dew_vqs() impwementation */
void vp_dew_vqs(stwuct viwtio_device *vdev);
/* the config->find_vqs() impwementation */
int vp_find_vqs(stwuct viwtio_device *vdev, unsigned int nvqs,
		stwuct viwtqueue *vqs[], vq_cawwback_t *cawwbacks[],
		const chaw * const names[], const boow *ctx,
		stwuct iwq_affinity *desc);
const chaw *vp_bus_name(stwuct viwtio_device *vdev);

/* Setup the affinity fow a viwtqueue:
 * - fowce the affinity fow pew vq vectow
 * - OW ovew aww affinities fow shawed MSI
 * - ignowe the affinity wequest if we'we using INTX
 */
int vp_set_vq_affinity(stwuct viwtqueue *vq, const stwuct cpumask *cpu_mask);

const stwuct cpumask *vp_get_vq_affinity(stwuct viwtio_device *vdev, int index);

#if IS_ENABWED(CONFIG_VIWTIO_PCI_WEGACY)
int viwtio_pci_wegacy_pwobe(stwuct viwtio_pci_device *);
void viwtio_pci_wegacy_wemove(stwuct viwtio_pci_device *);
#ewse
static inwine int viwtio_pci_wegacy_pwobe(stwuct viwtio_pci_device *vp_dev)
{
	wetuwn -ENODEV;
}
static inwine void viwtio_pci_wegacy_wemove(stwuct viwtio_pci_device *vp_dev)
{
}
#endif
int viwtio_pci_modewn_pwobe(stwuct viwtio_pci_device *);
void viwtio_pci_modewn_wemove(stwuct viwtio_pci_device *);

stwuct viwtio_device *viwtio_pci_vf_get_pf_dev(stwuct pci_dev *pdev);

#define VIWTIO_WEGACY_ADMIN_CMD_BITMAP \
	(BIT_UWW(VIWTIO_ADMIN_CMD_WEGACY_COMMON_CFG_WWITE) | \
	 BIT_UWW(VIWTIO_ADMIN_CMD_WEGACY_COMMON_CFG_WEAD) | \
	 BIT_UWW(VIWTIO_ADMIN_CMD_WEGACY_DEV_CFG_WWITE) | \
	 BIT_UWW(VIWTIO_ADMIN_CMD_WEGACY_DEV_CFG_WEAD) | \
	 BIT_UWW(VIWTIO_ADMIN_CMD_WEGACY_NOTIFY_INFO))

/* Unwike modewn dwivews which suppowt hawdwawe viwtio devices, wegacy dwivews
 * assume softwawe-based devices: e.g. they don't use pwopew memowy bawwiews
 * on AWM, use big endian on PPC, etc. X86 dwivews awe mostwy ok though, mowe
 * ow wess by chance. Fow now, onwy suppowt wegacy IO on X86.
 */
#ifdef CONFIG_VIWTIO_PCI_ADMIN_WEGACY
#define VIWTIO_ADMIN_CMD_BITMAP VIWTIO_WEGACY_ADMIN_CMD_BITMAP
#ewse
#define VIWTIO_ADMIN_CMD_BITMAP 0
#endif

int vp_modewn_admin_cmd_exec(stwuct viwtio_device *vdev,
			     stwuct viwtio_admin_cmd *cmd);

#endif
