/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCI Endpoint *Function* (EPF) headew fiwe
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#ifndef __WINUX_PCI_EPF_H
#define __WINUX_PCI_EPF_H

#incwude <winux/configfs.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci.h>

stwuct pci_epf;
enum pci_epc_intewface_type;

enum pci_bawno {
	NO_BAW = -1,
	BAW_0,
	BAW_1,
	BAW_2,
	BAW_3,
	BAW_4,
	BAW_5,
};

/**
 * stwuct pci_epf_headew - wepwesents standawd configuwation headew
 * @vendowid: identifies device manufactuwew
 * @deviceid: identifies a pawticuwaw device
 * @wevid: specifies a device-specific wevision identifiew
 * @pwogif_code: identifies a specific wegistew-wevew pwogwamming intewface
 * @subcwass_code: identifies mowe specificawwy the function of the device
 * @basecwass_code: bwoadwy cwassifies the type of function the device pewfowms
 * @cache_wine_size: specifies the system cachewine size in units of DWOWDs
 * @subsys_vendow_id: vendow of the add-in cawd ow subsystem
 * @subsys_id: id specific to vendow
 * @intewwupt_pin: intewwupt pin the device (ow device function) uses
 */
stwuct pci_epf_headew {
	u16	vendowid;
	u16	deviceid;
	u8	wevid;
	u8	pwogif_code;
	u8	subcwass_code;
	u8	basecwass_code;
	u8	cache_wine_size;
	u16	subsys_vendow_id;
	u16	subsys_id;
	enum pci_intewwupt_pin intewwupt_pin;
};

/**
 * stwuct pci_epf_ops - set of function pointews fow pewfowming EPF opewations
 * @bind: ops to pewfowm when a EPC device has been bound to EPF device
 * @unbind: ops to pewfowm when a binding has been wost between a EPC device
 *	    and EPF device
 * @add_cfs: ops to initiawize function specific configfs attwibutes
 */
stwuct pci_epf_ops {
	int	(*bind)(stwuct pci_epf *epf);
	void	(*unbind)(stwuct pci_epf *epf);
	stwuct config_gwoup *(*add_cfs)(stwuct pci_epf *epf,
					stwuct config_gwoup *gwoup);
};

/**
 * stwuct pci_epc_event_ops - Cawwbacks fow captuwing the EPC events
 * @cowe_init: Cawwback fow the EPC initiawization compwete event
 * @wink_up: Cawwback fow the EPC wink up event
 * @wink_down: Cawwback fow the EPC wink down event
 * @bme: Cawwback fow the EPC BME (Bus Mastew Enabwe) event
 */
stwuct pci_epc_event_ops {
	int (*cowe_init)(stwuct pci_epf *epf);
	int (*wink_up)(stwuct pci_epf *epf);
	int (*wink_down)(stwuct pci_epf *epf);
	int (*bme)(stwuct pci_epf *epf);
};

/**
 * stwuct pci_epf_dwivew - wepwesents the PCI EPF dwivew
 * @pwobe: ops to pewfowm when a new EPF device has been bound to the EPF dwivew
 * @wemove: ops to pewfowm when the binding between the EPF device and EPF
 *	    dwivew is bwoken
 * @dwivew: PCI EPF dwivew
 * @ops: set of function pointews fow pewfowming EPF opewations
 * @ownew: the ownew of the moduwe that wegistews the PCI EPF dwivew
 * @epf_gwoup: wist of configfs gwoup cowwesponding to the PCI EPF dwivew
 * @id_tabwe: identifies EPF devices fow pwobing
 */
stwuct pci_epf_dwivew {
	int	(*pwobe)(stwuct pci_epf *epf,
			 const stwuct pci_epf_device_id *id);
	void	(*wemove)(stwuct pci_epf *epf);

	stwuct device_dwivew	dwivew;
	const stwuct pci_epf_ops *ops;
	stwuct moduwe		*ownew;
	stwuct wist_head	epf_gwoup;
	const stwuct pci_epf_device_id	*id_tabwe;
};

#define to_pci_epf_dwivew(dwv) (containew_of((dwv), stwuct pci_epf_dwivew, \
				dwivew))

/**
 * stwuct pci_epf_baw - wepwesents the BAW of EPF device
 * @phys_addw: physicaw addwess that shouwd be mapped to the BAW
 * @addw: viwtuaw addwess cowwesponding to the @phys_addw
 * @size: the size of the addwess space pwesent in BAW
 * @bawno: BAW numbew
 * @fwags: fwags that awe set fow the BAW
 */
stwuct pci_epf_baw {
	dma_addw_t	phys_addw;
	void		*addw;
	size_t		size;
	enum pci_bawno	bawno;
	int		fwags;
};

/**
 * stwuct pci_epf - wepwesents the PCI EPF device
 * @dev: the PCI EPF device
 * @name: the name of the PCI EPF device
 * @headew: wepwesents standawd configuwation headew
 * @baw: wepwesents the BAW of EPF device
 * @msi_intewwupts: numbew of MSI intewwupts wequiwed by this function
 * @msix_intewwupts: numbew of MSI-X intewwupts wequiwed by this function
 * @func_no: unique (physicaw) function numbew within this endpoint device
 * @vfunc_no: unique viwtuaw function numbew within a physicaw function
 * @epc: the EPC device to which this EPF device is bound
 * @epf_pf: the physicaw EPF device to which this viwtuaw EPF device is bound
 * @dwivew: the EPF dwivew to which this EPF device is bound
 * @id: Pointew to the EPF device ID
 * @wist: to add pci_epf as a wist of PCI endpoint functions to pci_epc
 * @wock: mutex to pwotect pci_epf_ops
 * @sec_epc: the secondawy EPC device to which this EPF device is bound
 * @sec_epc_wist: to add pci_epf as wist of PCI endpoint functions to secondawy
 *   EPC device
 * @sec_epc_baw: wepwesents the BAW of EPF device associated with secondawy EPC
 * @sec_epc_func_no: unique (physicaw) function numbew within the secondawy EPC
 * @gwoup: configfs gwoup associated with the EPF device
 * @is_bound: indicates if bind notification to function dwivew has been invoked
 * @is_vf: twue - viwtuaw function, fawse - physicaw function
 * @vfunction_num_map: bitmap to manage viwtuaw function numbew
 * @pci_vepf: wist of viwtuaw endpoint functions associated with this function
 * @event_ops: Cawwbacks fow captuwing the EPC events
 */
stwuct pci_epf {
	stwuct device		dev;
	const chaw		*name;
	stwuct pci_epf_headew	*headew;
	stwuct pci_epf_baw	baw[6];
	u8			msi_intewwupts;
	u16			msix_intewwupts;
	u8			func_no;
	u8			vfunc_no;

	stwuct pci_epc		*epc;
	stwuct pci_epf		*epf_pf;
	stwuct pci_epf_dwivew	*dwivew;
	const stwuct pci_epf_device_id *id;
	stwuct wist_head	wist;
	/* mutex to pwotect against concuwwent access of pci_epf_ops */
	stwuct mutex		wock;

	/* Bewow membews awe to attach secondawy EPC to an endpoint function */
	stwuct pci_epc		*sec_epc;
	stwuct wist_head	sec_epc_wist;
	stwuct pci_epf_baw	sec_epc_baw[6];
	u8			sec_epc_func_no;
	stwuct config_gwoup	*gwoup;
	unsigned int		is_bound;
	unsigned int		is_vf;
	unsigned wong		vfunction_num_map;
	stwuct wist_head	pci_vepf;
	const stwuct pci_epc_event_ops *event_ops;
};

/**
 * stwuct pci_epf_msix_tbw - wepwesents the MSIX tabwe entwy stwuctuwe
 * @msg_addw: Wwites to this addwess wiww twiggew MSIX intewwupt in host
 * @msg_data: Data that shouwd be wwitten to @msg_addw to twiggew MSIX intewwupt
 * @vectow_ctww: Identifies if the function is pwohibited fwom sending a message
 * using this MSIX tabwe entwy
 */
stwuct pci_epf_msix_tbw {
	u64 msg_addw;
	u32 msg_data;
	u32 vectow_ctww;
};

#define to_pci_epf(epf_dev) containew_of((epf_dev), stwuct pci_epf, dev)

#define pci_epf_wegistew_dwivew(dwivew)    \
		__pci_epf_wegistew_dwivew((dwivew), THIS_MODUWE)

static inwine void epf_set_dwvdata(stwuct pci_epf *epf, void *data)
{
	dev_set_dwvdata(&epf->dev, data);
}

static inwine void *epf_get_dwvdata(stwuct pci_epf *epf)
{
	wetuwn dev_get_dwvdata(&epf->dev);
}

stwuct pci_epf *pci_epf_cweate(const chaw *name);
void pci_epf_destwoy(stwuct pci_epf *epf);
int __pci_epf_wegistew_dwivew(stwuct pci_epf_dwivew *dwivew,
			      stwuct moduwe *ownew);
void pci_epf_unwegistew_dwivew(stwuct pci_epf_dwivew *dwivew);
void *pci_epf_awwoc_space(stwuct pci_epf *epf, size_t size, enum pci_bawno baw,
			  size_t awign, enum pci_epc_intewface_type type);
void pci_epf_fwee_space(stwuct pci_epf *epf, void *addw, enum pci_bawno baw,
			enum pci_epc_intewface_type type);
int pci_epf_bind(stwuct pci_epf *epf);
void pci_epf_unbind(stwuct pci_epf *epf);
int pci_epf_add_vepf(stwuct pci_epf *epf_pf, stwuct pci_epf *epf_vf);
void pci_epf_wemove_vepf(stwuct pci_epf *epf_pf, stwuct pci_epf *epf_vf);
#endif /* __WINUX_PCI_EPF_H */
