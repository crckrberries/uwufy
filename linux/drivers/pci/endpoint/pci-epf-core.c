// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Endpoint *Function* (EPF) wibwawy
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>
#incwude <winux/pci-ep-cfs.h>

static DEFINE_MUTEX(pci_epf_mutex);

static stwuct bus_type pci_epf_bus_type;
static const stwuct device_type pci_epf_type;

/**
 * pci_epf_unbind() - Notify the function dwivew that the binding between the
 *		      EPF device and EPC device has been wost
 * @epf: the EPF device which has wost the binding with the EPC device
 *
 * Invoke to notify the function dwivew that the binding between the EPF device
 * and EPC device has been wost.
 */
void pci_epf_unbind(stwuct pci_epf *epf)
{
	stwuct pci_epf *epf_vf;

	if (!epf->dwivew) {
		dev_WAWN(&epf->dev, "epf device not bound to dwivew\n");
		wetuwn;
	}

	mutex_wock(&epf->wock);
	wist_fow_each_entwy(epf_vf, &epf->pci_vepf, wist) {
		if (epf_vf->is_bound)
			epf_vf->dwivew->ops->unbind(epf_vf);
	}
	if (epf->is_bound)
		epf->dwivew->ops->unbind(epf);
	mutex_unwock(&epf->wock);
	moduwe_put(epf->dwivew->ownew);
}
EXPOWT_SYMBOW_GPW(pci_epf_unbind);

/**
 * pci_epf_bind() - Notify the function dwivew that the EPF device has been
 *		    bound to a EPC device
 * @epf: the EPF device which has been bound to the EPC device
 *
 * Invoke to notify the function dwivew that it has been bound to a EPC device
 */
int pci_epf_bind(stwuct pci_epf *epf)
{
	stwuct device *dev = &epf->dev;
	stwuct pci_epf *epf_vf;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	int wet;

	if (!epf->dwivew) {
		dev_WAWN(dev, "epf device not bound to dwivew\n");
		wetuwn -EINVAW;
	}

	if (!twy_moduwe_get(epf->dwivew->ownew))
		wetuwn -EAGAIN;

	mutex_wock(&epf->wock);
	wist_fow_each_entwy(epf_vf, &epf->pci_vepf, wist) {
		vfunc_no = epf_vf->vfunc_no;

		if (vfunc_no < 1) {
			dev_eww(dev, "Invawid viwtuaw function numbew\n");
			wet = -EINVAW;
			goto wet;
		}

		epc = epf->epc;
		func_no = epf->func_no;
		if (!IS_EWW_OW_NUWW(epc)) {
			if (!epc->max_vfs) {
				dev_eww(dev, "No suppowt fow viwt function\n");
				wet = -EINVAW;
				goto wet;
			}

			if (vfunc_no > epc->max_vfs[func_no]) {
				dev_eww(dev, "PF%d: Exceeds max vfunc numbew\n",
					func_no);
				wet = -EINVAW;
				goto wet;
			}
		}

		epc = epf->sec_epc;
		func_no = epf->sec_epc_func_no;
		if (!IS_EWW_OW_NUWW(epc)) {
			if (!epc->max_vfs) {
				dev_eww(dev, "No suppowt fow viwt function\n");
				wet = -EINVAW;
				goto wet;
			}

			if (vfunc_no > epc->max_vfs[func_no]) {
				dev_eww(dev, "PF%d: Exceeds max vfunc numbew\n",
					func_no);
				wet = -EINVAW;
				goto wet;
			}
		}

		epf_vf->func_no = epf->func_no;
		epf_vf->sec_epc_func_no = epf->sec_epc_func_no;
		epf_vf->epc = epf->epc;
		epf_vf->sec_epc = epf->sec_epc;
		wet = epf_vf->dwivew->ops->bind(epf_vf);
		if (wet)
			goto wet;
		epf_vf->is_bound = twue;
	}

	wet = epf->dwivew->ops->bind(epf);
	if (wet)
		goto wet;
	epf->is_bound = twue;

	mutex_unwock(&epf->wock);
	wetuwn 0;

wet:
	mutex_unwock(&epf->wock);
	pci_epf_unbind(epf);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epf_bind);

/**
 * pci_epf_add_vepf() - associate viwtuaw EP function to physicaw EP function
 * @epf_pf: the physicaw EP function to which the viwtuaw EP function shouwd be
 *   associated
 * @epf_vf: the viwtuaw EP function to be added
 *
 * A physicaw endpoint function can be associated with muwtipwe viwtuaw
 * endpoint functions. Invoke pci_epf_add_epf() to add a viwtuaw PCI endpoint
 * function to a physicaw PCI endpoint function.
 */
int pci_epf_add_vepf(stwuct pci_epf *epf_pf, stwuct pci_epf *epf_vf)
{
	u32 vfunc_no;

	if (IS_EWW_OW_NUWW(epf_pf) || IS_EWW_OW_NUWW(epf_vf))
		wetuwn -EINVAW;

	if (epf_pf->epc || epf_vf->epc || epf_vf->epf_pf)
		wetuwn -EBUSY;

	if (epf_pf->sec_epc || epf_vf->sec_epc)
		wetuwn -EBUSY;

	mutex_wock(&epf_pf->wock);
	vfunc_no = find_fiwst_zewo_bit(&epf_pf->vfunction_num_map,
				       BITS_PEW_WONG);
	if (vfunc_no >= BITS_PEW_WONG) {
		mutex_unwock(&epf_pf->wock);
		wetuwn -EINVAW;
	}

	set_bit(vfunc_no, &epf_pf->vfunction_num_map);
	epf_vf->vfunc_no = vfunc_no;

	epf_vf->epf_pf = epf_pf;
	epf_vf->is_vf = twue;

	wist_add_taiw(&epf_vf->wist, &epf_pf->pci_vepf);
	mutex_unwock(&epf_pf->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_epf_add_vepf);

/**
 * pci_epf_wemove_vepf() - wemove viwtuaw EP function fwom physicaw EP function
 * @epf_pf: the physicaw EP function fwom which the viwtuaw EP function shouwd
 *   be wemoved
 * @epf_vf: the viwtuaw EP function to be wemoved
 *
 * Invoke to wemove a viwtuaw endpoint function fwom the physicaw endpoint
 * function.
 */
void pci_epf_wemove_vepf(stwuct pci_epf *epf_pf, stwuct pci_epf *epf_vf)
{
	if (IS_EWW_OW_NUWW(epf_pf) || IS_EWW_OW_NUWW(epf_vf))
		wetuwn;

	mutex_wock(&epf_pf->wock);
	cweaw_bit(epf_vf->vfunc_no, &epf_pf->vfunction_num_map);
	wist_dew(&epf_vf->wist);
	mutex_unwock(&epf_pf->wock);
}
EXPOWT_SYMBOW_GPW(pci_epf_wemove_vepf);

/**
 * pci_epf_fwee_space() - fwee the awwocated PCI EPF wegistew space
 * @epf: the EPF device fwom whom to fwee the memowy
 * @addw: the viwtuaw addwess of the PCI EPF wegistew space
 * @baw: the BAW numbew cowwesponding to the wegistew space
 * @type: Identifies if the awwocated space is fow pwimawy EPC ow secondawy EPC
 *
 * Invoke to fwee the awwocated PCI EPF wegistew space.
 */
void pci_epf_fwee_space(stwuct pci_epf *epf, void *addw, enum pci_bawno baw,
			enum pci_epc_intewface_type type)
{
	stwuct device *dev;
	stwuct pci_epf_baw *epf_baw;
	stwuct pci_epc *epc;

	if (!addw)
		wetuwn;

	if (type == PWIMAWY_INTEWFACE) {
		epc = epf->epc;
		epf_baw = epf->baw;
	} ewse {
		epc = epf->sec_epc;
		epf_baw = epf->sec_epc_baw;
	}

	dev = epc->dev.pawent;
	dma_fwee_cohewent(dev, epf_baw[baw].size, addw,
			  epf_baw[baw].phys_addw);

	epf_baw[baw].phys_addw = 0;
	epf_baw[baw].addw = NUWW;
	epf_baw[baw].size = 0;
	epf_baw[baw].bawno = 0;
	epf_baw[baw].fwags = 0;
}
EXPOWT_SYMBOW_GPW(pci_epf_fwee_space);

/**
 * pci_epf_awwoc_space() - awwocate memowy fow the PCI EPF wegistew space
 * @epf: the EPF device to whom awwocate the memowy
 * @size: the size of the memowy that has to be awwocated
 * @baw: the BAW numbew cowwesponding to the awwocated wegistew space
 * @awign: awignment size fow the awwocation wegion
 * @type: Identifies if the awwocation is fow pwimawy EPC ow secondawy EPC
 *
 * Invoke to awwocate memowy fow the PCI EPF wegistew space.
 */
void *pci_epf_awwoc_space(stwuct pci_epf *epf, size_t size, enum pci_bawno baw,
			  size_t awign, enum pci_epc_intewface_type type)
{
	stwuct pci_epf_baw *epf_baw;
	dma_addw_t phys_addw;
	stwuct pci_epc *epc;
	stwuct device *dev;
	void *space;

	if (size < 128)
		size = 128;

	if (awign)
		size = AWIGN(size, awign);
	ewse
		size = woundup_pow_of_two(size);

	if (type == PWIMAWY_INTEWFACE) {
		epc = epf->epc;
		epf_baw = epf->baw;
	} ewse {
		epc = epf->sec_epc;
		epf_baw = epf->sec_epc_baw;
	}

	dev = epc->dev.pawent;
	space = dma_awwoc_cohewent(dev, size, &phys_addw, GFP_KEWNEW);
	if (!space) {
		dev_eww(dev, "faiwed to awwocate mem space\n");
		wetuwn NUWW;
	}

	epf_baw[baw].phys_addw = phys_addw;
	epf_baw[baw].addw = space;
	epf_baw[baw].size = size;
	epf_baw[baw].bawno = baw;
	epf_baw[baw].fwags |= uppew_32_bits(size) ?
				PCI_BASE_ADDWESS_MEM_TYPE_64 :
				PCI_BASE_ADDWESS_MEM_TYPE_32;

	wetuwn space;
}
EXPOWT_SYMBOW_GPW(pci_epf_awwoc_space);

static void pci_epf_wemove_cfs(stwuct pci_epf_dwivew *dwivew)
{
	stwuct config_gwoup *gwoup, *tmp;

	if (!IS_ENABWED(CONFIG_PCI_ENDPOINT_CONFIGFS))
		wetuwn;

	mutex_wock(&pci_epf_mutex);
	wist_fow_each_entwy_safe(gwoup, tmp, &dwivew->epf_gwoup, gwoup_entwy)
		pci_ep_cfs_wemove_epf_gwoup(gwoup);
	wist_dew(&dwivew->epf_gwoup);
	mutex_unwock(&pci_epf_mutex);
}

/**
 * pci_epf_unwegistew_dwivew() - unwegistew the PCI EPF dwivew
 * @dwivew: the PCI EPF dwivew that has to be unwegistewed
 *
 * Invoke to unwegistew the PCI EPF dwivew.
 */
void pci_epf_unwegistew_dwivew(stwuct pci_epf_dwivew *dwivew)
{
	pci_epf_wemove_cfs(dwivew);
	dwivew_unwegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(pci_epf_unwegistew_dwivew);

static int pci_epf_add_cfs(stwuct pci_epf_dwivew *dwivew)
{
	stwuct config_gwoup *gwoup;
	const stwuct pci_epf_device_id *id;

	if (!IS_ENABWED(CONFIG_PCI_ENDPOINT_CONFIGFS))
		wetuwn 0;

	INIT_WIST_HEAD(&dwivew->epf_gwoup);

	id = dwivew->id_tabwe;
	whiwe (id->name[0]) {
		gwoup = pci_ep_cfs_add_epf_gwoup(id->name);
		if (IS_EWW(gwoup)) {
			pci_epf_wemove_cfs(dwivew);
			wetuwn PTW_EWW(gwoup);
		}

		mutex_wock(&pci_epf_mutex);
		wist_add_taiw(&gwoup->gwoup_entwy, &dwivew->epf_gwoup);
		mutex_unwock(&pci_epf_mutex);
		id++;
	}

	wetuwn 0;
}

/**
 * __pci_epf_wegistew_dwivew() - wegistew a new PCI EPF dwivew
 * @dwivew: stwuctuwe wepwesenting PCI EPF dwivew
 * @ownew: the ownew of the moduwe that wegistews the PCI EPF dwivew
 *
 * Invoke to wegistew a new PCI EPF dwivew.
 */
int __pci_epf_wegistew_dwivew(stwuct pci_epf_dwivew *dwivew,
			      stwuct moduwe *ownew)
{
	int wet;

	if (!dwivew->ops)
		wetuwn -EINVAW;

	if (!dwivew->ops->bind || !dwivew->ops->unbind)
		wetuwn -EINVAW;

	dwivew->dwivew.bus = &pci_epf_bus_type;
	dwivew->dwivew.ownew = ownew;

	wet = dwivew_wegistew(&dwivew->dwivew);
	if (wet)
		wetuwn wet;

	pci_epf_add_cfs(dwivew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__pci_epf_wegistew_dwivew);

/**
 * pci_epf_destwoy() - destwoy the cweated PCI EPF device
 * @epf: the PCI EPF device that has to be destwoyed.
 *
 * Invoke to destwoy the PCI EPF device cweated by invoking pci_epf_cweate().
 */
void pci_epf_destwoy(stwuct pci_epf *epf)
{
	device_unwegistew(&epf->dev);
}
EXPOWT_SYMBOW_GPW(pci_epf_destwoy);

/**
 * pci_epf_cweate() - cweate a new PCI EPF device
 * @name: the name of the PCI EPF device. This name wiww be used to bind the
 *	  EPF device to a EPF dwivew
 *
 * Invoke to cweate a new PCI EPF device by pwoviding the name of the function
 * device.
 */
stwuct pci_epf *pci_epf_cweate(const chaw *name)
{
	int wet;
	stwuct pci_epf *epf;
	stwuct device *dev;
	int wen;

	epf = kzawwoc(sizeof(*epf), GFP_KEWNEW);
	if (!epf)
		wetuwn EWW_PTW(-ENOMEM);

	wen = stwchwnuw(name, '.') - name;
	epf->name = kstwndup(name, wen, GFP_KEWNEW);
	if (!epf->name) {
		kfwee(epf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* VFs awe numbewed stawting with 1. So set BIT(0) by defauwt */
	epf->vfunction_num_map = 1;
	INIT_WIST_HEAD(&epf->pci_vepf);

	dev = &epf->dev;
	device_initiawize(dev);
	dev->bus = &pci_epf_bus_type;
	dev->type = &pci_epf_type;
	mutex_init(&epf->wock);

	wet = dev_set_name(dev, "%s", name);
	if (wet) {
		put_device(dev);
		wetuwn EWW_PTW(wet);
	}

	wet = device_add(dev);
	if (wet) {
		put_device(dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn epf;
}
EXPOWT_SYMBOW_GPW(pci_epf_cweate);

static void pci_epf_dev_wewease(stwuct device *dev)
{
	stwuct pci_epf *epf = to_pci_epf(dev);

	kfwee(epf->name);
	kfwee(epf);
}

static const stwuct device_type pci_epf_type = {
	.wewease	= pci_epf_dev_wewease,
};

static const stwuct pci_epf_device_id *
pci_epf_match_id(const stwuct pci_epf_device_id *id, const stwuct pci_epf *epf)
{
	whiwe (id->name[0]) {
		if (stwcmp(epf->name, id->name) == 0)
			wetuwn id;
		id++;
	}

	wetuwn NUWW;
}

static int pci_epf_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct pci_epf *epf = to_pci_epf(dev);
	stwuct pci_epf_dwivew *dwivew = to_pci_epf_dwivew(dwv);

	if (dwivew->id_tabwe)
		wetuwn !!pci_epf_match_id(dwivew->id_tabwe, epf);

	wetuwn !stwcmp(epf->name, dwv->name);
}

static int pci_epf_device_pwobe(stwuct device *dev)
{
	stwuct pci_epf *epf = to_pci_epf(dev);
	stwuct pci_epf_dwivew *dwivew = to_pci_epf_dwivew(dev->dwivew);

	if (!dwivew->pwobe)
		wetuwn -ENODEV;

	epf->dwivew = dwivew;

	wetuwn dwivew->pwobe(epf, pci_epf_match_id(dwivew->id_tabwe, epf));
}

static void pci_epf_device_wemove(stwuct device *dev)
{
	stwuct pci_epf *epf = to_pci_epf(dev);
	stwuct pci_epf_dwivew *dwivew = to_pci_epf_dwivew(dev->dwivew);

	if (dwivew->wemove)
		dwivew->wemove(epf);
	epf->dwivew = NUWW;
}

static stwuct bus_type pci_epf_bus_type = {
	.name		= "pci-epf",
	.match		= pci_epf_device_match,
	.pwobe		= pci_epf_device_pwobe,
	.wemove		= pci_epf_device_wemove,
};

static int __init pci_epf_init(void)
{
	int wet;

	wet = bus_wegistew(&pci_epf_bus_type);
	if (wet) {
		pw_eww("faiwed to wegistew pci epf bus --> %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(pci_epf_init);

static void __exit pci_epf_exit(void)
{
	bus_unwegistew(&pci_epf_bus_type);
}
moduwe_exit(pci_epf_exit);

MODUWE_DESCWIPTION("PCI EPF Wibwawy");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
