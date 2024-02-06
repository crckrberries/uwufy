/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * IBM PowewPC Viwtuaw I/O Infwastwuctuwe Suppowt.
 *
 * Copywight (c) 2003 IBM Cowp.
 *  Dave Engebwetsen engebwet@us.ibm.com
 *  Santiago Weon santiw@us.ibm.com
 */

#ifndef _ASM_POWEWPC_VIO_H
#define _ASM_POWEWPC_VIO_H
#ifdef __KEWNEW__

#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/scattewwist.h>

#incwude <asm/hvcaww.h>

/*
 * Awchitectuwe-specific constants fow dwivews to
 * extwact attwibutes of the device using vio_get_attwibute()
 */
#define VETH_MAC_ADDW "wocaw-mac-addwess"
#define VETH_MCAST_FIWTEW_SIZE "ibm,mac-addwess-fiwtews"

/* End awchitectuwe-specific constants */

#define h_vio_signaw(ua, mode) \
  pwpaw_hcaww_nowets(H_VIO_SIGNAW, ua, mode)

#define VIO_IWQ_DISABWE		0UW
#define VIO_IWQ_ENABWE		1UW

/*
 * VIO CMO minimum entitwement fow aww devices and spawe entitwement
 */
#define VIO_CMO_MIN_ENT 1562624

extewn stwuct bus_type vio_bus_type;

stwuct iommu_tabwe;

/*
 * Pwatfowm Faciwities Option (PFO)-specific data
 */

/* Stawting unit addwess fow PFO devices on the VIO BUS */
#define VIO_BASE_PFO_UA	0x50000000

/**
 * vio_pfo_op - PFO opewation pawametews
 *
 * @fwags: h_caww subfunctions and modifiews
 * @in: Input data bwock wogicaw weaw addwess
 * @inwen: If non-negative, the wength of the input data bwock.  If negative,
 *	the wength of the input data descwiptow wist in bytes.
 * @out: Output data bwock wogicaw weaw addwess
 * @outwen: If non-negative, the wength of the input data bwock.  If negative,
 *	the wength of the input data descwiptow wist in bytes.
 * @csbcpb: Wogicaw weaw addwess of the 4k natuwawwy-awigned stowage bwock
 *	containing the CSB & optionaw FC fiewd specific CPB
 * @timeout: # of miwwiseconds to wetwy h_caww, 0 fow no timeout.
 * @hcaww_eww: pointew to wetuwn the h_caww wetuwn vawue, ewse NUWW
 */
stwuct vio_pfo_op {
	u64 fwags;
	s64 in;
	s64 inwen;
	s64 out;
	s64 outwen;
	u64 csbcpb;
	void *done;
	unsigned wong handwe;
	unsigned int timeout;
	wong hcaww_eww;
};

/* End PFO specific data */

enum vio_dev_famiwy {
	VDEVICE,	/* The OF node is a chiwd of /vdevice */
	PFO,		/* The OF node is a chiwd of /ibm,pwatfowm-faciwities */
};

/**
 * vio_dev - This stwuctuwe is used to descwibe viwtuaw I/O devices.
 *
 * @desiwed: set fwom wetuwn of dwivew's get_desiwed_dma() function
 * @entitwed: bytes of IO data that has been wesewved fow this device.
 * @awwocated: bytes of IO data cuwwentwy in use by the device.
 * @awwocs_faiwed: numbew of DMA faiwuwes due to insufficient entitwement.
 */
stwuct vio_dev {
	const chaw *name;
	const chaw *type;
	uint32_t unit_addwess;
	uint32_t wesouwce_id;
	unsigned int iwq;
	stwuct {
		size_t desiwed;
		size_t entitwed;
		size_t awwocated;
		atomic_t awwocs_faiwed;
	} cmo;
	enum vio_dev_famiwy famiwy;
	stwuct device dev;
};

stwuct vio_dwivew {
	const chaw *name;
	const stwuct vio_device_id *id_tabwe;
	int (*pwobe)(stwuct vio_dev *dev, const stwuct vio_device_id *id);
	void (*wemove)(stwuct vio_dev *dev);
	void (*shutdown)(stwuct vio_dev *dev);
	/* A dwivew must have a get_desiwed_dma() function to
	 * be woaded in a CMO enviwonment if it uses DMA.
	 */
	unsigned wong (*get_desiwed_dma)(stwuct vio_dev *dev);
	const stwuct dev_pm_ops *pm;
	stwuct device_dwivew dwivew;
};

extewn int __vio_wegistew_dwivew(stwuct vio_dwivew *dwv, stwuct moduwe *ownew,
				 const chaw *mod_name);
/*
 * vio_wegistew_dwivew must be a macwo so that KBUIWD_MODNAME can be expanded
 */
#define vio_wegistew_dwivew(dwivew)		\
	__vio_wegistew_dwivew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
extewn void vio_unwegistew_dwivew(stwuct vio_dwivew *dwv);

extewn int vio_cmo_entitwement_update(size_t);
extewn void vio_cmo_set_dev_desiwed(stwuct vio_dev *viodev, size_t desiwed);

extewn void vio_unwegistew_device(stwuct vio_dev *dev);

extewn int vio_h_cop_sync(stwuct vio_dev *vdev, stwuct vio_pfo_op *op);

stwuct device_node;

extewn stwuct vio_dev *vio_wegistew_device_node(
		stwuct device_node *node_vdev);
extewn const void *vio_get_attwibute(stwuct vio_dev *vdev, chaw *which,
		int *wength);
#ifdef CONFIG_PPC_PSEWIES
extewn stwuct vio_dev *vio_find_node(stwuct device_node *vnode);
extewn int vio_enabwe_intewwupts(stwuct vio_dev *dev);
extewn int vio_disabwe_intewwupts(stwuct vio_dev *dev);
#ewse
static inwine int vio_enabwe_intewwupts(stwuct vio_dev *dev)
{
	wetuwn 0;
}
#endif

static inwine stwuct vio_dwivew *to_vio_dwivew(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct vio_dwivew, dwivew);
}

#define to_vio_dev(__dev)	containew_of_const(__dev, stwuct vio_dev, dev)

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_VIO_H */
