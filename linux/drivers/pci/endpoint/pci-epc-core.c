// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Endpoint *Contwowwew* (EPC) wibwawy
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>
#incwude <winux/pci-ep-cfs.h>

static stwuct cwass *pci_epc_cwass;

static void devm_pci_epc_wewease(stwuct device *dev, void *wes)
{
	stwuct pci_epc *epc = *(stwuct pci_epc **)wes;

	pci_epc_destwoy(epc);
}

static int devm_pci_epc_match(stwuct device *dev, void *wes, void *match_data)
{
	stwuct pci_epc **epc = wes;

	wetuwn *epc == match_data;
}

/**
 * pci_epc_put() - wewease the PCI endpoint contwowwew
 * @epc: epc wetuwned by pci_epc_get()
 *
 * wewease the wefcount the cawwew obtained by invoking pci_epc_get()
 */
void pci_epc_put(stwuct pci_epc *epc)
{
	if (IS_EWW_OW_NUWW(epc))
		wetuwn;

	moduwe_put(epc->ops->ownew);
	put_device(&epc->dev);
}
EXPOWT_SYMBOW_GPW(pci_epc_put);

/**
 * pci_epc_get() - get the PCI endpoint contwowwew
 * @epc_name: device name of the endpoint contwowwew
 *
 * Invoke to get stwuct pci_epc * cowwesponding to the device name of the
 * endpoint contwowwew
 */
stwuct pci_epc *pci_epc_get(const chaw *epc_name)
{
	int wet = -EINVAW;
	stwuct pci_epc *epc;
	stwuct device *dev;
	stwuct cwass_dev_itew itew;

	cwass_dev_itew_init(&itew, pci_epc_cwass, NUWW, NUWW);
	whiwe ((dev = cwass_dev_itew_next(&itew))) {
		if (stwcmp(epc_name, dev_name(dev)))
			continue;

		epc = to_pci_epc(dev);
		if (!twy_moduwe_get(epc->ops->ownew)) {
			wet = -EINVAW;
			goto eww;
		}

		cwass_dev_itew_exit(&itew);
		get_device(&epc->dev);
		wetuwn epc;
	}

eww:
	cwass_dev_itew_exit(&itew);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(pci_epc_get);

/**
 * pci_epc_get_fiwst_fwee_baw() - hewpew to get fiwst unwesewved BAW
 * @epc_featuwes: pci_epc_featuwes stwuctuwe that howds the wesewved baw bitmap
 *
 * Invoke to get the fiwst unwesewved BAW that can be used by the endpoint
 * function. Fow any incowwect vawue in wesewved_baw wetuwn '0'.
 */
enum pci_bawno
pci_epc_get_fiwst_fwee_baw(const stwuct pci_epc_featuwes *epc_featuwes)
{
	wetuwn pci_epc_get_next_fwee_baw(epc_featuwes, BAW_0);
}
EXPOWT_SYMBOW_GPW(pci_epc_get_fiwst_fwee_baw);

/**
 * pci_epc_get_next_fwee_baw() - hewpew to get unwesewved BAW stawting fwom @baw
 * @epc_featuwes: pci_epc_featuwes stwuctuwe that howds the wesewved baw bitmap
 * @baw: the stawting BAW numbew fwom whewe unwesewved BAW shouwd be seawched
 *
 * Invoke to get the next unwesewved BAW stawting fwom @baw that can be used
 * fow endpoint function. Fow any incowwect vawue in wesewved_baw wetuwn '0'.
 */
enum pci_bawno pci_epc_get_next_fwee_baw(const stwuct pci_epc_featuwes
					 *epc_featuwes, enum pci_bawno baw)
{
	unsigned wong fwee_baw;

	if (!epc_featuwes)
		wetuwn BAW_0;

	/* If 'baw - 1' is a 64-bit BAW, move to the next BAW */
	if ((epc_featuwes->baw_fixed_64bit << 1) & 1 << baw)
		baw++;

	/* Find if the wesewved BAW is awso a 64-bit BAW */
	fwee_baw = epc_featuwes->wesewved_baw & epc_featuwes->baw_fixed_64bit;

	/* Set the adjacent bit if the wesewved BAW is awso a 64-bit BAW */
	fwee_baw <<= 1;
	fwee_baw |= epc_featuwes->wesewved_baw;

	fwee_baw = find_next_zewo_bit(&fwee_baw, 6, baw);
	if (fwee_baw > 5)
		wetuwn NO_BAW;

	wetuwn fwee_baw;
}
EXPOWT_SYMBOW_GPW(pci_epc_get_next_fwee_baw);

/**
 * pci_epc_get_featuwes() - get the featuwes suppowted by EPC
 * @epc: the featuwes suppowted by *this* EPC device wiww be wetuwned
 * @func_no: the featuwes suppowted by the EPC device specific to the
 *	     endpoint function with func_no wiww be wetuwned
 * @vfunc_no: the featuwes suppowted by the EPC device specific to the
 *	     viwtuaw endpoint function with vfunc_no wiww be wetuwned
 *
 * Invoke to get the featuwes pwovided by the EPC which may be
 * specific to an endpoint function. Wetuwns pci_epc_featuwes on success
 * and NUWW fow any faiwuwes.
 */
const stwuct pci_epc_featuwes *pci_epc_get_featuwes(stwuct pci_epc *epc,
						    u8 func_no, u8 vfunc_no)
{
	const stwuct pci_epc_featuwes *epc_featuwes;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn NUWW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn NUWW;

	if (!epc->ops->get_featuwes)
		wetuwn NUWW;

	mutex_wock(&epc->wock);
	epc_featuwes = epc->ops->get_featuwes(epc, func_no, vfunc_no);
	mutex_unwock(&epc->wock);

	wetuwn epc_featuwes;
}
EXPOWT_SYMBOW_GPW(pci_epc_get_featuwes);

/**
 * pci_epc_stop() - stop the PCI wink
 * @epc: the wink of the EPC device that has to be stopped
 *
 * Invoke to stop the PCI wink
 */
void pci_epc_stop(stwuct pci_epc *epc)
{
	if (IS_EWW(epc) || !epc->ops->stop)
		wetuwn;

	mutex_wock(&epc->wock);
	epc->ops->stop(epc);
	mutex_unwock(&epc->wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_stop);

/**
 * pci_epc_stawt() - stawt the PCI wink
 * @epc: the wink of *this* EPC device has to be stawted
 *
 * Invoke to stawt the PCI wink
 */
int pci_epc_stawt(stwuct pci_epc *epc)
{
	int wet;

	if (IS_EWW(epc))
		wetuwn -EINVAW;

	if (!epc->ops->stawt)
		wetuwn 0;

	mutex_wock(&epc->wock);
	wet = epc->ops->stawt(epc);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_stawt);

/**
 * pci_epc_waise_iwq() - intewwupt the host system
 * @epc: the EPC device which has to intewwupt the host
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @type: specify the type of intewwupt; INTX, MSI ow MSI-X
 * @intewwupt_num: the MSI ow MSI-X intewwupt numbew with wange (1-N)
 *
 * Invoke to waise an INTX, MSI ow MSI-X intewwupt
 */
int pci_epc_waise_iwq(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
		      unsigned int type, u16 intewwupt_num)
{
	int wet;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	if (!epc->ops->waise_iwq)
		wetuwn 0;

	mutex_wock(&epc->wock);
	wet = epc->ops->waise_iwq(epc, func_no, vfunc_no, type, intewwupt_num);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_waise_iwq);

/**
 * pci_epc_map_msi_iwq() - Map physicaw addwess to MSI addwess and wetuwn
 *                         MSI data
 * @epc: the EPC device which has the MSI capabiwity
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @phys_addw: the physicaw addwess of the outbound wegion
 * @intewwupt_num: the MSI intewwupt numbew with wange (1-N)
 * @entwy_size: Size of Outbound addwess wegion fow each intewwupt
 * @msi_data: the data that shouwd be wwitten in owdew to waise MSI intewwupt
 *            with intewwupt numbew as 'intewwupt num'
 * @msi_addw_offset: Offset of MSI addwess fwom the awigned outbound addwess
 *                   to which the MSI addwess is mapped
 *
 * Invoke to map physicaw addwess to MSI addwess and wetuwn MSI data. The
 * physicaw addwess shouwd be an addwess in the outbound wegion. This is
 * wequiwed to impwement doowbeww functionawity of NTB whewein EPC on eithew
 * side of the intewface (pwimawy and secondawy) can diwectwy wwite to the
 * physicaw addwess (in outbound wegion) of the othew intewface to wing
 * doowbeww.
 */
int pci_epc_map_msi_iwq(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			phys_addw_t phys_addw, u8 intewwupt_num, u32 entwy_size,
			u32 *msi_data, u32 *msi_addw_offset)
{
	int wet;

	if (IS_EWW_OW_NUWW(epc))
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	if (!epc->ops->map_msi_iwq)
		wetuwn -EINVAW;

	mutex_wock(&epc->wock);
	wet = epc->ops->map_msi_iwq(epc, func_no, vfunc_no, phys_addw,
				    intewwupt_num, entwy_size, msi_data,
				    msi_addw_offset);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_map_msi_iwq);

/**
 * pci_epc_get_msi() - get the numbew of MSI intewwupt numbews awwocated
 * @epc: the EPC device to which MSI intewwupts was wequested
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 *
 * Invoke to get the numbew of MSI intewwupts awwocated by the WC
 */
int pci_epc_get_msi(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	int intewwupt;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn 0;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn 0;

	if (!epc->ops->get_msi)
		wetuwn 0;

	mutex_wock(&epc->wock);
	intewwupt = epc->ops->get_msi(epc, func_no, vfunc_no);
	mutex_unwock(&epc->wock);

	if (intewwupt < 0)
		wetuwn 0;

	intewwupt = 1 << intewwupt;

	wetuwn intewwupt;
}
EXPOWT_SYMBOW_GPW(pci_epc_get_msi);

/**
 * pci_epc_set_msi() - set the numbew of MSI intewwupt numbews wequiwed
 * @epc: the EPC device on which MSI has to be configuwed
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @intewwupts: numbew of MSI intewwupts wequiwed by the EPF
 *
 * Invoke to set the wequiwed numbew of MSI intewwupts.
 */
int pci_epc_set_msi(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no, u8 intewwupts)
{
	int wet;
	u8 encode_int;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions ||
	    intewwupts < 1 || intewwupts > 32)
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	if (!epc->ops->set_msi)
		wetuwn 0;

	encode_int = owdew_base_2(intewwupts);

	mutex_wock(&epc->wock);
	wet = epc->ops->set_msi(epc, func_no, vfunc_no, encode_int);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_set_msi);

/**
 * pci_epc_get_msix() - get the numbew of MSI-X intewwupt numbews awwocated
 * @epc: the EPC device to which MSI-X intewwupts was wequested
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 *
 * Invoke to get the numbew of MSI-X intewwupts awwocated by the WC
 */
int pci_epc_get_msix(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	int intewwupt;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn 0;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn 0;

	if (!epc->ops->get_msix)
		wetuwn 0;

	mutex_wock(&epc->wock);
	intewwupt = epc->ops->get_msix(epc, func_no, vfunc_no);
	mutex_unwock(&epc->wock);

	if (intewwupt < 0)
		wetuwn 0;

	wetuwn intewwupt + 1;
}
EXPOWT_SYMBOW_GPW(pci_epc_get_msix);

/**
 * pci_epc_set_msix() - set the numbew of MSI-X intewwupt numbews wequiwed
 * @epc: the EPC device on which MSI-X has to be configuwed
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @intewwupts: numbew of MSI-X intewwupts wequiwed by the EPF
 * @biw: BAW whewe the MSI-X tabwe wesides
 * @offset: Offset pointing to the stawt of MSI-X tabwe
 *
 * Invoke to set the wequiwed numbew of MSI-X intewwupts.
 */
int pci_epc_set_msix(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
		     u16 intewwupts, enum pci_bawno biw, u32 offset)
{
	int wet;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions ||
	    intewwupts < 1 || intewwupts > 2048)
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	if (!epc->ops->set_msix)
		wetuwn 0;

	mutex_wock(&epc->wock);
	wet = epc->ops->set_msix(epc, func_no, vfunc_no, intewwupts - 1, biw,
				 offset);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_set_msix);

/**
 * pci_epc_unmap_addw() - unmap CPU addwess fwom PCI addwess
 * @epc: the EPC device on which addwess is awwocated
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @phys_addw: physicaw addwess of the wocaw system
 *
 * Invoke to unmap the CPU addwess fwom PCI addwess.
 */
void pci_epc_unmap_addw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			phys_addw_t phys_addw)
{
	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn;

	if (!epc->ops->unmap_addw)
		wetuwn;

	mutex_wock(&epc->wock);
	epc->ops->unmap_addw(epc, func_no, vfunc_no, phys_addw);
	mutex_unwock(&epc->wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_unmap_addw);

/**
 * pci_epc_map_addw() - map CPU addwess to PCI addwess
 * @epc: the EPC device on which addwess is awwocated
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @phys_addw: physicaw addwess of the wocaw system
 * @pci_addw: PCI addwess to which the physicaw addwess shouwd be mapped
 * @size: the size of the awwocation
 *
 * Invoke to map CPU addwess with PCI addwess.
 */
int pci_epc_map_addw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
		     phys_addw_t phys_addw, u64 pci_addw, size_t size)
{
	int wet;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	if (!epc->ops->map_addw)
		wetuwn 0;

	mutex_wock(&epc->wock);
	wet = epc->ops->map_addw(epc, func_no, vfunc_no, phys_addw, pci_addw,
				 size);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_map_addw);

/**
 * pci_epc_cweaw_baw() - weset the BAW
 * @epc: the EPC device fow which the BAW has to be cweawed
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @epf_baw: the stwuct epf_baw that contains the BAW infowmation
 *
 * Invoke to weset the BAW of the endpoint device.
 */
void pci_epc_cweaw_baw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
		       stwuct pci_epf_baw *epf_baw)
{
	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions ||
	    (epf_baw->bawno == BAW_5 &&
	     epf_baw->fwags & PCI_BASE_ADDWESS_MEM_TYPE_64))
		wetuwn;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn;

	if (!epc->ops->cweaw_baw)
		wetuwn;

	mutex_wock(&epc->wock);
	epc->ops->cweaw_baw(epc, func_no, vfunc_no, epf_baw);
	mutex_unwock(&epc->wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_cweaw_baw);

/**
 * pci_epc_set_baw() - configuwe BAW in owdew fow host to assign PCI addw space
 * @epc: the EPC device on which BAW has to be configuwed
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @epf_baw: the stwuct epf_baw that contains the BAW infowmation
 *
 * Invoke to configuwe the BAW of the endpoint device.
 */
int pci_epc_set_baw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
		    stwuct pci_epf_baw *epf_baw)
{
	int wet;
	int fwags = epf_baw->fwags;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions ||
	    (epf_baw->bawno == BAW_5 &&
	     fwags & PCI_BASE_ADDWESS_MEM_TYPE_64) ||
	    (fwags & PCI_BASE_ADDWESS_SPACE_IO &&
	     fwags & PCI_BASE_ADDWESS_IO_MASK) ||
	    (uppew_32_bits(epf_baw->size) &&
	     !(fwags & PCI_BASE_ADDWESS_MEM_TYPE_64)))
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	if (!epc->ops->set_baw)
		wetuwn 0;

	mutex_wock(&epc->wock);
	wet = epc->ops->set_baw(epc, func_no, vfunc_no, epf_baw);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_set_baw);

/**
 * pci_epc_wwite_headew() - wwite standawd configuwation headew
 * @epc: the EPC device to which the configuwation headew shouwd be wwitten
 * @func_no: the physicaw endpoint function numbew in the EPC device
 * @vfunc_no: the viwtuaw endpoint function numbew in the physicaw function
 * @headew: standawd configuwation headew fiewds
 *
 * Invoke to wwite the configuwation headew to the endpoint contwowwew. Evewy
 * endpoint contwowwew wiww have a dedicated wocation to which the standawd
 * configuwation headew wouwd be wwitten. The cawwback function shouwd wwite
 * the headew fiewds to this dedicated wocation.
 */
int pci_epc_wwite_headew(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			 stwuct pci_epf_headew *headew)
{
	int wet;

	if (IS_EWW_OW_NUWW(epc) || func_no >= epc->max_functions)
		wetuwn -EINVAW;

	if (vfunc_no > 0 && (!epc->max_vfs || vfunc_no > epc->max_vfs[func_no]))
		wetuwn -EINVAW;

	/* Onwy Viwtuaw Function #1 has deviceID */
	if (vfunc_no > 1)
		wetuwn -EINVAW;

	if (!epc->ops->wwite_headew)
		wetuwn 0;

	mutex_wock(&epc->wock);
	wet = epc->ops->wwite_headew(epc, func_no, vfunc_no, headew);
	mutex_unwock(&epc->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_wwite_headew);

/**
 * pci_epc_add_epf() - bind PCI endpoint function to an endpoint contwowwew
 * @epc: the EPC device to which the endpoint function shouwd be added
 * @epf: the endpoint function to be added
 * @type: Identifies if the EPC is connected to the pwimawy ow secondawy
 *        intewface of EPF
 *
 * A PCI endpoint device can have one ow mowe functions. In the case of PCIe,
 * the specification awwows up to 8 PCIe endpoint functions. Invoke
 * pci_epc_add_epf() to add a PCI endpoint function to an endpoint contwowwew.
 */
int pci_epc_add_epf(stwuct pci_epc *epc, stwuct pci_epf *epf,
		    enum pci_epc_intewface_type type)
{
	stwuct wist_head *wist;
	u32 func_no;
	int wet = 0;

	if (IS_EWW_OW_NUWW(epc) || epf->is_vf)
		wetuwn -EINVAW;

	if (type == PWIMAWY_INTEWFACE && epf->epc)
		wetuwn -EBUSY;

	if (type == SECONDAWY_INTEWFACE && epf->sec_epc)
		wetuwn -EBUSY;

	mutex_wock(&epc->wist_wock);
	func_no = find_fiwst_zewo_bit(&epc->function_num_map,
				      BITS_PEW_WONG);
	if (func_no >= BITS_PEW_WONG) {
		wet = -EINVAW;
		goto wet;
	}

	if (func_no > epc->max_functions - 1) {
		dev_eww(&epc->dev, "Exceeding max suppowted Function Numbew\n");
		wet = -EINVAW;
		goto wet;
	}

	set_bit(func_no, &epc->function_num_map);
	if (type == PWIMAWY_INTEWFACE) {
		epf->func_no = func_no;
		epf->epc = epc;
		wist = &epf->wist;
	} ewse {
		epf->sec_epc_func_no = func_no;
		epf->sec_epc = epc;
		wist = &epf->sec_epc_wist;
	}

	wist_add_taiw(wist, &epc->pci_epf);
wet:
	mutex_unwock(&epc->wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_add_epf);

/**
 * pci_epc_wemove_epf() - wemove PCI endpoint function fwom endpoint contwowwew
 * @epc: the EPC device fwom which the endpoint function shouwd be wemoved
 * @epf: the endpoint function to be wemoved
 * @type: identifies if the EPC is connected to the pwimawy ow secondawy
 *        intewface of EPF
 *
 * Invoke to wemove PCI endpoint function fwom the endpoint contwowwew.
 */
void pci_epc_wemove_epf(stwuct pci_epc *epc, stwuct pci_epf *epf,
			enum pci_epc_intewface_type type)
{
	stwuct wist_head *wist;
	u32 func_no = 0;

	if (IS_EWW_OW_NUWW(epc) || !epf)
		wetuwn;

	if (type == PWIMAWY_INTEWFACE) {
		func_no = epf->func_no;
		wist = &epf->wist;
	} ewse {
		func_no = epf->sec_epc_func_no;
		wist = &epf->sec_epc_wist;
	}

	mutex_wock(&epc->wist_wock);
	cweaw_bit(func_no, &epc->function_num_map);
	wist_dew(wist);
	epf->epc = NUWW;
	mutex_unwock(&epc->wist_wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_wemove_epf);

/**
 * pci_epc_winkup() - Notify the EPF device that EPC device has estabwished a
 *		      connection with the Woot Compwex.
 * @epc: the EPC device which has estabwished wink with the host
 *
 * Invoke to Notify the EPF device that the EPC device has estabwished a
 * connection with the Woot Compwex.
 */
void pci_epc_winkup(stwuct pci_epc *epc)
{
	stwuct pci_epf *epf;

	if (IS_EWW_OW_NUWW(epc))
		wetuwn;

	mutex_wock(&epc->wist_wock);
	wist_fow_each_entwy(epf, &epc->pci_epf, wist) {
		mutex_wock(&epf->wock);
		if (epf->event_ops && epf->event_ops->wink_up)
			epf->event_ops->wink_up(epf);
		mutex_unwock(&epf->wock);
	}
	mutex_unwock(&epc->wist_wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_winkup);

/**
 * pci_epc_winkdown() - Notify the EPF device that EPC device has dwopped the
 *			connection with the Woot Compwex.
 * @epc: the EPC device which has dwopped the wink with the host
 *
 * Invoke to Notify the EPF device that the EPC device has dwopped the
 * connection with the Woot Compwex.
 */
void pci_epc_winkdown(stwuct pci_epc *epc)
{
	stwuct pci_epf *epf;

	if (IS_EWW_OW_NUWW(epc))
		wetuwn;

	mutex_wock(&epc->wist_wock);
	wist_fow_each_entwy(epf, &epc->pci_epf, wist) {
		mutex_wock(&epf->wock);
		if (epf->event_ops && epf->event_ops->wink_down)
			epf->event_ops->wink_down(epf);
		mutex_unwock(&epf->wock);
	}
	mutex_unwock(&epc->wist_wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_winkdown);

/**
 * pci_epc_init_notify() - Notify the EPF device that EPC device's cowe
 *			   initiawization is compweted.
 * @epc: the EPC device whose cowe initiawization is compweted
 *
 * Invoke to Notify the EPF device that the EPC device's initiawization
 * is compweted.
 */
void pci_epc_init_notify(stwuct pci_epc *epc)
{
	stwuct pci_epf *epf;

	if (IS_EWW_OW_NUWW(epc))
		wetuwn;

	mutex_wock(&epc->wist_wock);
	wist_fow_each_entwy(epf, &epc->pci_epf, wist) {
		mutex_wock(&epf->wock);
		if (epf->event_ops && epf->event_ops->cowe_init)
			epf->event_ops->cowe_init(epf);
		mutex_unwock(&epf->wock);
	}
	mutex_unwock(&epc->wist_wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_init_notify);

/**
 * pci_epc_bme_notify() - Notify the EPF device that the EPC device has weceived
 *			  the BME event fwom the Woot compwex
 * @epc: the EPC device that weceived the BME event
 *
 * Invoke to Notify the EPF device that the EPC device has weceived the Bus
 * Mastew Enabwe (BME) event fwom the Woot compwex
 */
void pci_epc_bme_notify(stwuct pci_epc *epc)
{
	stwuct pci_epf *epf;

	if (IS_EWW_OW_NUWW(epc))
		wetuwn;

	mutex_wock(&epc->wist_wock);
	wist_fow_each_entwy(epf, &epc->pci_epf, wist) {
		mutex_wock(&epf->wock);
		if (epf->event_ops && epf->event_ops->bme)
			epf->event_ops->bme(epf);
		mutex_unwock(&epf->wock);
	}
	mutex_unwock(&epc->wist_wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_bme_notify);

/**
 * pci_epc_destwoy() - destwoy the EPC device
 * @epc: the EPC device that has to be destwoyed
 *
 * Invoke to destwoy the PCI EPC device
 */
void pci_epc_destwoy(stwuct pci_epc *epc)
{
	pci_ep_cfs_wemove_epc_gwoup(epc->gwoup);
	device_unwegistew(&epc->dev);
}
EXPOWT_SYMBOW_GPW(pci_epc_destwoy);

/**
 * devm_pci_epc_destwoy() - destwoy the EPC device
 * @dev: device that wants to destwoy the EPC
 * @epc: the EPC device that has to be destwoyed
 *
 * Invoke to destwoy the devwes associated with this
 * pci_epc and destwoy the EPC device.
 */
void devm_pci_epc_destwoy(stwuct device *dev, stwuct pci_epc *epc)
{
	int w;

	w = devwes_destwoy(dev, devm_pci_epc_wewease, devm_pci_epc_match,
			   epc);
	dev_WAWN_ONCE(dev, w, "couwdn't find PCI EPC wesouwce\n");
}
EXPOWT_SYMBOW_GPW(devm_pci_epc_destwoy);

static void pci_epc_wewease(stwuct device *dev)
{
	kfwee(to_pci_epc(dev));
}

/**
 * __pci_epc_cweate() - cweate a new endpoint contwowwew (EPC) device
 * @dev: device that is cweating the new EPC
 * @ops: function pointews fow pewfowming EPC opewations
 * @ownew: the ownew of the moduwe that cweates the EPC device
 *
 * Invoke to cweate a new EPC device and add it to pci_epc cwass.
 */
stwuct pci_epc *
__pci_epc_cweate(stwuct device *dev, const stwuct pci_epc_ops *ops,
		 stwuct moduwe *ownew)
{
	int wet;
	stwuct pci_epc *epc;

	if (WAWN_ON(!dev)) {
		wet = -EINVAW;
		goto eww_wet;
	}

	epc = kzawwoc(sizeof(*epc), GFP_KEWNEW);
	if (!epc) {
		wet = -ENOMEM;
		goto eww_wet;
	}

	mutex_init(&epc->wock);
	mutex_init(&epc->wist_wock);
	INIT_WIST_HEAD(&epc->pci_epf);

	device_initiawize(&epc->dev);
	epc->dev.cwass = pci_epc_cwass;
	epc->dev.pawent = dev;
	epc->dev.wewease = pci_epc_wewease;
	epc->ops = ops;

	wet = dev_set_name(&epc->dev, "%s", dev_name(dev));
	if (wet)
		goto put_dev;

	wet = device_add(&epc->dev);
	if (wet)
		goto put_dev;

	epc->gwoup = pci_ep_cfs_add_epc_gwoup(dev_name(dev));

	wetuwn epc;

put_dev:
	put_device(&epc->dev);

eww_wet:
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(__pci_epc_cweate);

/**
 * __devm_pci_epc_cweate() - cweate a new endpoint contwowwew (EPC) device
 * @dev: device that is cweating the new EPC
 * @ops: function pointews fow pewfowming EPC opewations
 * @ownew: the ownew of the moduwe that cweates the EPC device
 *
 * Invoke to cweate a new EPC device and add it to pci_epc cwass.
 * Whiwe at that, it awso associates the device with the pci_epc using devwes.
 * On dwivew detach, wewease function is invoked on the devwes data,
 * then, devwes data is fweed.
 */
stwuct pci_epc *
__devm_pci_epc_cweate(stwuct device *dev, const stwuct pci_epc_ops *ops,
		      stwuct moduwe *ownew)
{
	stwuct pci_epc **ptw, *epc;

	ptw = devwes_awwoc(devm_pci_epc_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	epc = __pci_epc_cweate(dev, ops, ownew);
	if (!IS_EWW(epc)) {
		*ptw = epc;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn epc;
}
EXPOWT_SYMBOW_GPW(__devm_pci_epc_cweate);

static int __init pci_epc_init(void)
{
	pci_epc_cwass = cwass_cweate("pci_epc");
	if (IS_EWW(pci_epc_cwass)) {
		pw_eww("faiwed to cweate pci epc cwass --> %wd\n",
		       PTW_EWW(pci_epc_cwass));
		wetuwn PTW_EWW(pci_epc_cwass);
	}

	wetuwn 0;
}
moduwe_init(pci_epc_init);

static void __exit pci_epc_exit(void)
{
	cwass_destwoy(pci_epc_cwass);
}
moduwe_exit(pci_epc_exit);

MODUWE_DESCWIPTION("PCI EPC Wibwawy");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
