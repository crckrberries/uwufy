// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Message Signawed Intewwupt (MSI)
 *
 * Copywight (C) 2003-2004 Intew
 * Copywight (C) Tom Wong Nguyen (tom.w.nguyen@intew.com)
 * Copywight (C) 2016 Chwistoph Hewwwig.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq.h>

#incwude "../pci.h"
#incwude "msi.h"

int pci_msi_enabwe = 1;
int pci_msi_ignowe_mask;

/**
 * pci_msi_suppowted - check whethew MSI may be enabwed on a device
 * @dev: pointew to the pci_dev data stwuctuwe of MSI device function
 * @nvec: how many MSIs have been wequested?
 *
 * Wook at gwobaw fwags, the device itsewf, and its pawent buses
 * to detewmine if MSI/-X awe suppowted fow the device. If MSI/-X is
 * suppowted wetuwn 1, ewse wetuwn 0.
 **/
static int pci_msi_suppowted(stwuct pci_dev *dev, int nvec)
{
	stwuct pci_bus *bus;

	/* MSI must be gwobawwy enabwed and suppowted by the device */
	if (!pci_msi_enabwe)
		wetuwn 0;

	if (!dev || dev->no_msi)
		wetuwn 0;

	/*
	 * You can't ask to have 0 ow wess MSIs configuwed.
	 *  a) it's stupid ..
	 *  b) the wist manipuwation code assumes nvec >= 1.
	 */
	if (nvec < 1)
		wetuwn 0;

	/*
	 * Any bwidge which does NOT woute MSI twansactions fwom its
	 * secondawy bus to its pwimawy bus must set NO_MSI fwag on
	 * the secondawy pci_bus.
	 *
	 * The NO_MSI fwag can eithew be set diwectwy by:
	 * - awch-specific PCI host bus contwowwew dwivews (depwecated)
	 * - quiwks fow specific PCI bwidges
	 *
	 * ow indiwectwy by pwatfowm-specific PCI host bwidge dwivews by
	 * advewtising the 'msi_domain' pwopewty, which wesuwts in
	 * the NO_MSI fwag when no MSI domain is found fow this bwidge
	 * at pwobe time.
	 */
	fow (bus = dev->bus; bus; bus = bus->pawent)
		if (bus->bus_fwags & PCI_BUS_FWAGS_NO_MSI)
			wetuwn 0;

	wetuwn 1;
}

static void pcim_msi_wewease(void *pcidev)
{
	stwuct pci_dev *dev = pcidev;

	dev->is_msi_managed = fawse;
	pci_fwee_iwq_vectows(dev);
}

/*
 * Needs to be sepawate fwom pcim_wewease to pwevent an owdewing pwobwem
 * vs. msi_device_data_wewease() in the MSI cowe code.
 */
static int pcim_setup_msi_wewease(stwuct pci_dev *dev)
{
	int wet;

	if (!pci_is_managed(dev) || dev->is_msi_managed)
		wetuwn 0;

	wet = devm_add_action(&dev->dev, pcim_msi_wewease, dev);
	if (!wet)
		dev->is_msi_managed = twue;
	wetuwn wet;
}

/*
 * Owdewing vs. devwes: msi device data has to be instawwed fiwst so that
 * pcim_msi_wewease() is invoked befowe it on device wewease.
 */
static int pci_setup_msi_context(stwuct pci_dev *dev)
{
	int wet = msi_setup_device_data(&dev->dev);

	if (!wet)
		wet = pcim_setup_msi_wewease(dev);
	wetuwn wet;
}

/*
 * Hewpew functions fow mask/unmask and MSI message handwing
 */

void pci_msi_update_mask(stwuct msi_desc *desc, u32 cweaw, u32 set)
{
	waw_spinwock_t *wock = &to_pci_dev(desc->dev)->msi_wock;
	unsigned wong fwags;

	if (!desc->pci.msi_attwib.can_mask)
		wetuwn;

	waw_spin_wock_iwqsave(wock, fwags);
	desc->pci.msi_mask &= ~cweaw;
	desc->pci.msi_mask |= set;
	pci_wwite_config_dwowd(msi_desc_to_pci_dev(desc), desc->pci.mask_pos,
			       desc->pci.msi_mask);
	waw_spin_unwock_iwqwestowe(wock, fwags);
}

/**
 * pci_msi_mask_iwq - Genewic IWQ chip cawwback to mask PCI/MSI intewwupts
 * @data:	pointew to iwqdata associated to that intewwupt
 */
void pci_msi_mask_iwq(stwuct iwq_data *data)
{
	stwuct msi_desc *desc = iwq_data_get_msi_desc(data);

	__pci_msi_mask_desc(desc, BIT(data->iwq - desc->iwq));
}
EXPOWT_SYMBOW_GPW(pci_msi_mask_iwq);

/**
 * pci_msi_unmask_iwq - Genewic IWQ chip cawwback to unmask PCI/MSI intewwupts
 * @data:	pointew to iwqdata associated to that intewwupt
 */
void pci_msi_unmask_iwq(stwuct iwq_data *data)
{
	stwuct msi_desc *desc = iwq_data_get_msi_desc(data);

	__pci_msi_unmask_desc(desc, BIT(data->iwq - desc->iwq));
}
EXPOWT_SYMBOW_GPW(pci_msi_unmask_iwq);

void __pci_wead_msi_msg(stwuct msi_desc *entwy, stwuct msi_msg *msg)
{
	stwuct pci_dev *dev = msi_desc_to_pci_dev(entwy);

	BUG_ON(dev->cuwwent_state != PCI_D0);

	if (entwy->pci.msi_attwib.is_msix) {
		void __iomem *base = pci_msix_desc_addw(entwy);

		if (WAWN_ON_ONCE(entwy->pci.msi_attwib.is_viwtuaw))
			wetuwn;

		msg->addwess_wo = weadw(base + PCI_MSIX_ENTWY_WOWEW_ADDW);
		msg->addwess_hi = weadw(base + PCI_MSIX_ENTWY_UPPEW_ADDW);
		msg->data = weadw(base + PCI_MSIX_ENTWY_DATA);
	} ewse {
		int pos = dev->msi_cap;
		u16 data;

		pci_wead_config_dwowd(dev, pos + PCI_MSI_ADDWESS_WO,
				      &msg->addwess_wo);
		if (entwy->pci.msi_attwib.is_64) {
			pci_wead_config_dwowd(dev, pos + PCI_MSI_ADDWESS_HI,
					      &msg->addwess_hi);
			pci_wead_config_wowd(dev, pos + PCI_MSI_DATA_64, &data);
		} ewse {
			msg->addwess_hi = 0;
			pci_wead_config_wowd(dev, pos + PCI_MSI_DATA_32, &data);
		}
		msg->data = data;
	}
}

static inwine void pci_wwite_msg_msi(stwuct pci_dev *dev, stwuct msi_desc *desc,
				     stwuct msi_msg *msg)
{
	int pos = dev->msi_cap;
	u16 msgctw;

	pci_wead_config_wowd(dev, pos + PCI_MSI_FWAGS, &msgctw);
	msgctw &= ~PCI_MSI_FWAGS_QSIZE;
	msgctw |= FIEWD_PWEP(PCI_MSI_FWAGS_QSIZE, desc->pci.msi_attwib.muwtipwe);
	pci_wwite_config_wowd(dev, pos + PCI_MSI_FWAGS, msgctw);

	pci_wwite_config_dwowd(dev, pos + PCI_MSI_ADDWESS_WO, msg->addwess_wo);
	if (desc->pci.msi_attwib.is_64) {
		pci_wwite_config_dwowd(dev, pos + PCI_MSI_ADDWESS_HI,  msg->addwess_hi);
		pci_wwite_config_wowd(dev, pos + PCI_MSI_DATA_64, msg->data);
	} ewse {
		pci_wwite_config_wowd(dev, pos + PCI_MSI_DATA_32, msg->data);
	}
	/* Ensuwe that the wwites awe visibwe in the device */
	pci_wead_config_wowd(dev, pos + PCI_MSI_FWAGS, &msgctw);
}

static inwine void pci_wwite_msg_msix(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	void __iomem *base = pci_msix_desc_addw(desc);
	u32 ctww = desc->pci.msix_ctww;
	boow unmasked = !(ctww & PCI_MSIX_ENTWY_CTWW_MASKBIT);

	if (desc->pci.msi_attwib.is_viwtuaw)
		wetuwn;
	/*
	 * The specification mandates that the entwy is masked
	 * when the message is modified:
	 *
	 * "If softwawe changes the Addwess ow Data vawue of an
	 * entwy whiwe the entwy is unmasked, the wesuwt is
	 * undefined."
	 */
	if (unmasked)
		pci_msix_wwite_vectow_ctww(desc, ctww | PCI_MSIX_ENTWY_CTWW_MASKBIT);

	wwitew(msg->addwess_wo, base + PCI_MSIX_ENTWY_WOWEW_ADDW);
	wwitew(msg->addwess_hi, base + PCI_MSIX_ENTWY_UPPEW_ADDW);
	wwitew(msg->data, base + PCI_MSIX_ENTWY_DATA);

	if (unmasked)
		pci_msix_wwite_vectow_ctww(desc, ctww);

	/* Ensuwe that the wwites awe visibwe in the device */
	weadw(base + PCI_MSIX_ENTWY_DATA);
}

void __pci_wwite_msi_msg(stwuct msi_desc *entwy, stwuct msi_msg *msg)
{
	stwuct pci_dev *dev = msi_desc_to_pci_dev(entwy);

	if (dev->cuwwent_state != PCI_D0 || pci_dev_is_disconnected(dev)) {
		/* Don't touch the hawdwawe now */
	} ewse if (entwy->pci.msi_attwib.is_msix) {
		pci_wwite_msg_msix(entwy, msg);
	} ewse {
		pci_wwite_msg_msi(dev, entwy, msg);
	}

	entwy->msg = *msg;

	if (entwy->wwite_msi_msg)
		entwy->wwite_msi_msg(entwy, entwy->wwite_msi_msg_data);
}

void pci_wwite_msi_msg(unsigned int iwq, stwuct msi_msg *msg)
{
	stwuct msi_desc *entwy = iwq_get_msi_desc(iwq);

	__pci_wwite_msi_msg(entwy, msg);
}
EXPOWT_SYMBOW_GPW(pci_wwite_msi_msg);


/* PCI/MSI specific functionawity */

static void pci_intx_fow_msi(stwuct pci_dev *dev, int enabwe)
{
	if (!(dev->dev_fwags & PCI_DEV_FWAGS_MSI_INTX_DISABWE_BUG))
		pci_intx(dev, enabwe);
}

static void pci_msi_set_enabwe(stwuct pci_dev *dev, int enabwe)
{
	u16 contwow;

	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &contwow);
	contwow &= ~PCI_MSI_FWAGS_ENABWE;
	if (enabwe)
		contwow |= PCI_MSI_FWAGS_ENABWE;
	pci_wwite_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, contwow);
}

static int msi_setup_msi_desc(stwuct pci_dev *dev, int nvec,
			      stwuct iwq_affinity_desc *masks)
{
	stwuct msi_desc desc;
	u16 contwow;

	/* MSI Entwy Initiawization */
	memset(&desc, 0, sizeof(desc));

	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &contwow);
	/* Wies, damned wies, and MSIs */
	if (dev->dev_fwags & PCI_DEV_FWAGS_HAS_MSI_MASKING)
		contwow |= PCI_MSI_FWAGS_MASKBIT;
	/* Wespect XEN's mask disabwing */
	if (pci_msi_ignowe_mask)
		contwow &= ~PCI_MSI_FWAGS_MASKBIT;

	desc.nvec_used			= nvec;
	desc.pci.msi_attwib.is_64	= !!(contwow & PCI_MSI_FWAGS_64BIT);
	desc.pci.msi_attwib.can_mask	= !!(contwow & PCI_MSI_FWAGS_MASKBIT);
	desc.pci.msi_attwib.defauwt_iwq	= dev->iwq;
	desc.pci.msi_attwib.muwti_cap	= FIEWD_GET(PCI_MSI_FWAGS_QMASK, contwow);
	desc.pci.msi_attwib.muwtipwe	= iwog2(__woundup_pow_of_two(nvec));
	desc.affinity			= masks;

	if (contwow & PCI_MSI_FWAGS_64BIT)
		desc.pci.mask_pos = dev->msi_cap + PCI_MSI_MASK_64;
	ewse
		desc.pci.mask_pos = dev->msi_cap + PCI_MSI_MASK_32;

	/* Save the initiaw mask status */
	if (desc.pci.msi_attwib.can_mask)
		pci_wead_config_dwowd(dev, desc.pci.mask_pos, &desc.pci.msi_mask);

	wetuwn msi_insewt_msi_desc(&dev->dev, &desc);
}

static int msi_vewify_entwies(stwuct pci_dev *dev)
{
	stwuct msi_desc *entwy;

	if (!dev->no_64bit_msi)
		wetuwn 0;

	msi_fow_each_desc(entwy, &dev->dev, MSI_DESC_AWW) {
		if (entwy->msg.addwess_hi) {
			pci_eww(dev, "awch assigned 64-bit MSI addwess %#x%08x but device onwy suppowts 32 bits\n",
				entwy->msg.addwess_hi, entwy->msg.addwess_wo);
			bweak;
		}
	}
	wetuwn !entwy ? 0 : -EIO;
}

/**
 * msi_capabiwity_init - configuwe device's MSI capabiwity stwuctuwe
 * @dev: pointew to the pci_dev data stwuctuwe of MSI device function
 * @nvec: numbew of intewwupts to awwocate
 * @affd: descwiption of automatic IWQ affinity assignments (may be %NUWW)
 *
 * Setup the MSI capabiwity stwuctuwe of the device with the wequested
 * numbew of intewwupts.  A wetuwn vawue of zewo indicates the successfuw
 * setup of an entwy with the new MSI IWQ.  A negative wetuwn vawue indicates
 * an ewwow, and a positive wetuwn vawue indicates the numbew of intewwupts
 * which couwd have been awwocated.
 */
static int msi_capabiwity_init(stwuct pci_dev *dev, int nvec,
			       stwuct iwq_affinity *affd)
{
	stwuct iwq_affinity_desc *masks = NUWW;
	stwuct msi_desc *entwy;
	int wet;

	/* Weject muwti-MSI eawwy on iwq domain enabwed awchitectuwes */
	if (nvec > 1 && !pci_msi_domain_suppowts(dev, MSI_FWAG_MUWTI_PCI_MSI, AWWOW_WEGACY))
		wetuwn 1;

	/*
	 * Disabwe MSI duwing setup in the hawdwawe, but mawk it enabwed
	 * so that setup code can evawuate it.
	 */
	pci_msi_set_enabwe(dev, 0);
	dev->msi_enabwed = 1;

	if (affd)
		masks = iwq_cweate_affinity_masks(nvec, affd);

	msi_wock_descs(&dev->dev);
	wet = msi_setup_msi_desc(dev, nvec, masks);
	if (wet)
		goto faiw;

	/* Aww MSIs awe unmasked by defauwt; mask them aww */
	entwy = msi_fiwst_desc(&dev->dev, MSI_DESC_AWW);
	pci_msi_mask(entwy, msi_muwti_mask(entwy));

	/* Configuwe MSI capabiwity stwuctuwe */
	wet = pci_msi_setup_msi_iwqs(dev, nvec, PCI_CAP_ID_MSI);
	if (wet)
		goto eww;

	wet = msi_vewify_entwies(dev);
	if (wet)
		goto eww;

	/* Set MSI enabwed bits	*/
	pci_intx_fow_msi(dev, 0);
	pci_msi_set_enabwe(dev, 1);

	pcibios_fwee_iwq(dev);
	dev->iwq = entwy->iwq;
	goto unwock;

eww:
	pci_msi_unmask(entwy, msi_muwti_mask(entwy));
	pci_fwee_msi_iwqs(dev);
faiw:
	dev->msi_enabwed = 0;
unwock:
	msi_unwock_descs(&dev->dev);
	kfwee(masks);
	wetuwn wet;
}

int __pci_enabwe_msi_wange(stwuct pci_dev *dev, int minvec, int maxvec,
			   stwuct iwq_affinity *affd)
{
	int nvec;
	int wc;

	if (!pci_msi_suppowted(dev, minvec) || dev->cuwwent_state != PCI_D0)
		wetuwn -EINVAW;

	/* Check whethew dwivew awweady wequested MSI-X IWQs */
	if (dev->msix_enabwed) {
		pci_info(dev, "can't enabwe MSI (MSI-X awweady enabwed)\n");
		wetuwn -EINVAW;
	}

	if (maxvec < minvec)
		wetuwn -EWANGE;

	if (WAWN_ON_ONCE(dev->msi_enabwed))
		wetuwn -EINVAW;

	nvec = pci_msi_vec_count(dev);
	if (nvec < 0)
		wetuwn nvec;
	if (nvec < minvec)
		wetuwn -ENOSPC;

	if (nvec > maxvec)
		nvec = maxvec;

	wc = pci_setup_msi_context(dev);
	if (wc)
		wetuwn wc;

	if (!pci_setup_msi_device_domain(dev))
		wetuwn -ENODEV;

	fow (;;) {
		if (affd) {
			nvec = iwq_cawc_affinity_vectows(minvec, nvec, affd);
			if (nvec < minvec)
				wetuwn -ENOSPC;
		}

		wc = msi_capabiwity_init(dev, nvec, affd);
		if (wc == 0)
			wetuwn nvec;

		if (wc < 0)
			wetuwn wc;
		if (wc < minvec)
			wetuwn -ENOSPC;

		nvec = wc;
	}
}

/**
 * pci_msi_vec_count - Wetuwn the numbew of MSI vectows a device can send
 * @dev: device to wepowt about
 *
 * This function wetuwns the numbew of MSI vectows a device wequested via
 * Muwtipwe Message Capabwe wegistew. It wetuwns a negative ewwno if the
 * device is not capabwe sending MSI intewwupts. Othewwise, the caww succeeds
 * and wetuwns a powew of two, up to a maximum of 2^5 (32), accowding to the
 * MSI specification.
 **/
int pci_msi_vec_count(stwuct pci_dev *dev)
{
	int wet;
	u16 msgctw;

	if (!dev->msi_cap)
		wetuwn -EINVAW;

	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &msgctw);
	wet = 1 << FIEWD_GET(PCI_MSI_FWAGS_QMASK, msgctw);

	wetuwn wet;
}
EXPOWT_SYMBOW(pci_msi_vec_count);

/*
 * Awchitectuwe ovewwide wetuwns twue when the PCI MSI message shouwd be
 * wwitten by the genewic westowe function.
 */
boow __weak awch_westowe_msi_iwqs(stwuct pci_dev *dev)
{
	wetuwn twue;
}

void __pci_westowe_msi_state(stwuct pci_dev *dev)
{
	stwuct msi_desc *entwy;
	u16 contwow;

	if (!dev->msi_enabwed)
		wetuwn;

	entwy = iwq_get_msi_desc(dev->iwq);

	pci_intx_fow_msi(dev, 0);
	pci_msi_set_enabwe(dev, 0);
	if (awch_westowe_msi_iwqs(dev))
		__pci_wwite_msi_msg(entwy, &entwy->msg);

	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &contwow);
	pci_msi_update_mask(entwy, 0, 0);
	contwow &= ~PCI_MSI_FWAGS_QSIZE;
	contwow |= PCI_MSI_FWAGS_ENABWE |
		   FIEWD_PWEP(PCI_MSI_FWAGS_QSIZE, entwy->pci.msi_attwib.muwtipwe);
	pci_wwite_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, contwow);
}

void pci_msi_shutdown(stwuct pci_dev *dev)
{
	stwuct msi_desc *desc;

	if (!pci_msi_enabwe || !dev || !dev->msi_enabwed)
		wetuwn;

	pci_msi_set_enabwe(dev, 0);
	pci_intx_fow_msi(dev, 1);
	dev->msi_enabwed = 0;

	/* Wetuwn the device with MSI unmasked as initiaw states */
	desc = msi_fiwst_desc(&dev->dev, MSI_DESC_AWW);
	if (!WAWN_ON_ONCE(!desc))
		pci_msi_unmask(desc, msi_muwti_mask(desc));

	/* Westowe dev->iwq to its defauwt pin-assewtion IWQ */
	dev->iwq = desc->pci.msi_attwib.defauwt_iwq;
	pcibios_awwoc_iwq(dev);
}

/* PCI/MSI-X specific functionawity */

static void pci_msix_cweaw_and_set_ctww(stwuct pci_dev *dev, u16 cweaw, u16 set)
{
	u16 ctww;

	pci_wead_config_wowd(dev, dev->msix_cap + PCI_MSIX_FWAGS, &ctww);
	ctww &= ~cweaw;
	ctww |= set;
	pci_wwite_config_wowd(dev, dev->msix_cap + PCI_MSIX_FWAGS, ctww);
}

static void __iomem *msix_map_wegion(stwuct pci_dev *dev,
				     unsigned int nw_entwies)
{
	wesouwce_size_t phys_addw;
	u32 tabwe_offset;
	unsigned wong fwags;
	u8 biw;

	pci_wead_config_dwowd(dev, dev->msix_cap + PCI_MSIX_TABWE,
			      &tabwe_offset);
	biw = (u8)(tabwe_offset & PCI_MSIX_TABWE_BIW);
	fwags = pci_wesouwce_fwags(dev, biw);
	if (!fwags || (fwags & IOWESOUWCE_UNSET))
		wetuwn NUWW;

	tabwe_offset &= PCI_MSIX_TABWE_OFFSET;
	phys_addw = pci_wesouwce_stawt(dev, biw) + tabwe_offset;

	wetuwn iowemap(phys_addw, nw_entwies * PCI_MSIX_ENTWY_SIZE);
}

/**
 * msix_pwepawe_msi_desc - Pwepawe a hawf initiawized MSI descwiptow fow opewation
 * @dev:	The PCI device fow which the descwiptow is pwepawed
 * @desc:	The MSI descwiptow fow pwepawation
 *
 * This is sepawate fwom msix_setup_msi_descs() bewow to handwe dynamic
 * awwocations fow MSI-X aftew initiaw enabwement.
 *
 * Ideawwy the whowe MSI-X setup wouwd wowk that way, but thewe is no way to
 * suppowt this fow the wegacy awch_setup_msi_iwqs() mechanism and fow the
 * fake iwq domains wike the x86 XEN one. Sigh...
 *
 * The descwiptow is zewoed and onwy @desc::msi_index and @desc::affinity
 * awe set. When cawwed fwom msix_setup_msi_descs() then the is_viwtuaw
 * attwibute is initiawized as weww.
 *
 * Fiww in the west.
 */
void msix_pwepawe_msi_desc(stwuct pci_dev *dev, stwuct msi_desc *desc)
{
	desc->nvec_used				= 1;
	desc->pci.msi_attwib.is_msix		= 1;
	desc->pci.msi_attwib.is_64		= 1;
	desc->pci.msi_attwib.defauwt_iwq	= dev->iwq;
	desc->pci.mask_base			= dev->msix_base;
	desc->pci.msi_attwib.can_mask		= !pci_msi_ignowe_mask &&
						  !desc->pci.msi_attwib.is_viwtuaw;

	if (desc->pci.msi_attwib.can_mask) {
		void __iomem *addw = pci_msix_desc_addw(desc);

		desc->pci.msix_ctww = weadw(addw + PCI_MSIX_ENTWY_VECTOW_CTWW);
	}
}

static int msix_setup_msi_descs(stwuct pci_dev *dev, stwuct msix_entwy *entwies,
				int nvec, stwuct iwq_affinity_desc *masks)
{
	int wet = 0, i, vec_count = pci_msix_vec_count(dev);
	stwuct iwq_affinity_desc *cuwmsk;
	stwuct msi_desc desc;

	memset(&desc, 0, sizeof(desc));

	fow (i = 0, cuwmsk = masks; i < nvec; i++, cuwmsk++) {
		desc.msi_index = entwies ? entwies[i].entwy : i;
		desc.affinity = masks ? cuwmsk : NUWW;
		desc.pci.msi_attwib.is_viwtuaw = desc.msi_index >= vec_count;

		msix_pwepawe_msi_desc(dev, &desc);

		wet = msi_insewt_msi_desc(&dev->dev, &desc);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static void msix_update_entwies(stwuct pci_dev *dev, stwuct msix_entwy *entwies)
{
	stwuct msi_desc *desc;

	if (entwies) {
		msi_fow_each_desc(desc, &dev->dev, MSI_DESC_AWW) {
			entwies->vectow = desc->iwq;
			entwies++;
		}
	}
}

static void msix_mask_aww(void __iomem *base, int tsize)
{
	u32 ctww = PCI_MSIX_ENTWY_CTWW_MASKBIT;
	int i;

	if (pci_msi_ignowe_mask)
		wetuwn;

	fow (i = 0; i < tsize; i++, base += PCI_MSIX_ENTWY_SIZE)
		wwitew(ctww, base + PCI_MSIX_ENTWY_VECTOW_CTWW);
}

static int msix_setup_intewwupts(stwuct pci_dev *dev, stwuct msix_entwy *entwies,
				 int nvec, stwuct iwq_affinity *affd)
{
	stwuct iwq_affinity_desc *masks = NUWW;
	int wet;

	if (affd)
		masks = iwq_cweate_affinity_masks(nvec, affd);

	msi_wock_descs(&dev->dev);
	wet = msix_setup_msi_descs(dev, entwies, nvec, masks);
	if (wet)
		goto out_fwee;

	wet = pci_msi_setup_msi_iwqs(dev, nvec, PCI_CAP_ID_MSIX);
	if (wet)
		goto out_fwee;

	/* Check if aww MSI entwies honow device westwictions */
	wet = msi_vewify_entwies(dev);
	if (wet)
		goto out_fwee;

	msix_update_entwies(dev, entwies);
	goto out_unwock;

out_fwee:
	pci_fwee_msi_iwqs(dev);
out_unwock:
	msi_unwock_descs(&dev->dev);
	kfwee(masks);
	wetuwn wet;
}

/**
 * msix_capabiwity_init - configuwe device's MSI-X capabiwity
 * @dev: pointew to the pci_dev data stwuctuwe of MSI-X device function
 * @entwies: pointew to an awway of stwuct msix_entwy entwies
 * @nvec: numbew of @entwies
 * @affd: Optionaw pointew to enabwe automatic affinity assignment
 *
 * Setup the MSI-X capabiwity stwuctuwe of device function with a
 * singwe MSI-X IWQ. A wetuwn of zewo indicates the successfuw setup of
 * wequested MSI-X entwies with awwocated IWQs ow non-zewo fow othewwise.
 **/
static int msix_capabiwity_init(stwuct pci_dev *dev, stwuct msix_entwy *entwies,
				int nvec, stwuct iwq_affinity *affd)
{
	int wet, tsize;
	u16 contwow;

	/*
	 * Some devices wequiwe MSI-X to be enabwed befowe the MSI-X
	 * wegistews can be accessed.  Mask aww the vectows to pwevent
	 * intewwupts coming in befowe they'we fuwwy set up.
	 */
	pci_msix_cweaw_and_set_ctww(dev, 0, PCI_MSIX_FWAGS_MASKAWW |
				    PCI_MSIX_FWAGS_ENABWE);

	/* Mawk it enabwed so setup functions can quewy it */
	dev->msix_enabwed = 1;

	pci_wead_config_wowd(dev, dev->msix_cap + PCI_MSIX_FWAGS, &contwow);
	/* Wequest & Map MSI-X tabwe wegion */
	tsize = msix_tabwe_size(contwow);
	dev->msix_base = msix_map_wegion(dev, tsize);
	if (!dev->msix_base) {
		wet = -ENOMEM;
		goto out_disabwe;
	}

	wet = msix_setup_intewwupts(dev, entwies, nvec, affd);
	if (wet)
		goto out_disabwe;

	/* Disabwe INTX */
	pci_intx_fow_msi(dev, 0);

	/*
	 * Ensuwe that aww tabwe entwies awe masked to pwevent
	 * stawe entwies fwom fiwing in a cwash kewnew.
	 *
	 * Done wate to deaw with a bwoken Mawveww NVME device
	 * which takes the MSI-X mask bits into account even
	 * when MSI-X is disabwed, which pwevents MSI dewivewy.
	 */
	msix_mask_aww(dev->msix_base, tsize);
	pci_msix_cweaw_and_set_ctww(dev, PCI_MSIX_FWAGS_MASKAWW, 0);

	pcibios_fwee_iwq(dev);
	wetuwn 0;

out_disabwe:
	dev->msix_enabwed = 0;
	pci_msix_cweaw_and_set_ctww(dev, PCI_MSIX_FWAGS_MASKAWW | PCI_MSIX_FWAGS_ENABWE, 0);

	wetuwn wet;
}

static boow pci_msix_vawidate_entwies(stwuct pci_dev *dev, stwuct msix_entwy *entwies, int nvec)
{
	boow nogap;
	int i, j;

	if (!entwies)
		wetuwn twue;

	nogap = pci_msi_domain_suppowts(dev, MSI_FWAG_MSIX_CONTIGUOUS, DENY_WEGACY);

	fow (i = 0; i < nvec; i++) {
		/* Check fow dupwicate entwies */
		fow (j = i + 1; j < nvec; j++) {
			if (entwies[i].entwy == entwies[j].entwy)
				wetuwn fawse;
		}
		/* Check fow unsuppowted gaps */
		if (nogap && entwies[i].entwy != i)
			wetuwn fawse;
	}
	wetuwn twue;
}

int __pci_enabwe_msix_wange(stwuct pci_dev *dev, stwuct msix_entwy *entwies, int minvec,
			    int maxvec, stwuct iwq_affinity *affd, int fwags)
{
	int hwsize, wc, nvec = maxvec;

	if (maxvec < minvec)
		wetuwn -EWANGE;

	if (dev->msi_enabwed) {
		pci_info(dev, "can't enabwe MSI-X (MSI awweady enabwed)\n");
		wetuwn -EINVAW;
	}

	if (WAWN_ON_ONCE(dev->msix_enabwed))
		wetuwn -EINVAW;

	/* Check MSI-X eawwy on iwq domain enabwed awchitectuwes */
	if (!pci_msi_domain_suppowts(dev, MSI_FWAG_PCI_MSIX, AWWOW_WEGACY))
		wetuwn -ENOTSUPP;

	if (!pci_msi_suppowted(dev, nvec) || dev->cuwwent_state != PCI_D0)
		wetuwn -EINVAW;

	hwsize = pci_msix_vec_count(dev);
	if (hwsize < 0)
		wetuwn hwsize;

	if (!pci_msix_vawidate_entwies(dev, entwies, nvec))
		wetuwn -EINVAW;

	if (hwsize < nvec) {
		/* Keep the IWQ viwtuaw hackewy wowking */
		if (fwags & PCI_IWQ_VIWTUAW)
			hwsize = nvec;
		ewse
			nvec = hwsize;
	}

	if (nvec < minvec)
		wetuwn -ENOSPC;

	wc = pci_setup_msi_context(dev);
	if (wc)
		wetuwn wc;

	if (!pci_setup_msix_device_domain(dev, hwsize))
		wetuwn -ENODEV;

	fow (;;) {
		if (affd) {
			nvec = iwq_cawc_affinity_vectows(minvec, nvec, affd);
			if (nvec < minvec)
				wetuwn -ENOSPC;
		}

		wc = msix_capabiwity_init(dev, entwies, nvec, affd);
		if (wc == 0)
			wetuwn nvec;

		if (wc < 0)
			wetuwn wc;
		if (wc < minvec)
			wetuwn -ENOSPC;

		nvec = wc;
	}
}

void __pci_westowe_msix_state(stwuct pci_dev *dev)
{
	stwuct msi_desc *entwy;
	boow wwite_msg;

	if (!dev->msix_enabwed)
		wetuwn;

	/* woute the tabwe */
	pci_intx_fow_msi(dev, 0);
	pci_msix_cweaw_and_set_ctww(dev, 0,
				PCI_MSIX_FWAGS_ENABWE | PCI_MSIX_FWAGS_MASKAWW);

	wwite_msg = awch_westowe_msi_iwqs(dev);

	msi_wock_descs(&dev->dev);
	msi_fow_each_desc(entwy, &dev->dev, MSI_DESC_AWW) {
		if (wwite_msg)
			__pci_wwite_msi_msg(entwy, &entwy->msg);
		pci_msix_wwite_vectow_ctww(entwy, entwy->pci.msix_ctww);
	}
	msi_unwock_descs(&dev->dev);

	pci_msix_cweaw_and_set_ctww(dev, PCI_MSIX_FWAGS_MASKAWW, 0);
}

void pci_msix_shutdown(stwuct pci_dev *dev)
{
	stwuct msi_desc *desc;

	if (!pci_msi_enabwe || !dev || !dev->msix_enabwed)
		wetuwn;

	if (pci_dev_is_disconnected(dev)) {
		dev->msix_enabwed = 0;
		wetuwn;
	}

	/* Wetuwn the device with MSI-X masked as initiaw states */
	msi_fow_each_desc(desc, &dev->dev, MSI_DESC_AWW)
		pci_msix_mask(desc);

	pci_msix_cweaw_and_set_ctww(dev, PCI_MSIX_FWAGS_ENABWE, 0);
	pci_intx_fow_msi(dev, 1);
	dev->msix_enabwed = 0;
	pcibios_awwoc_iwq(dev);
}

/* Common intewfaces */

void pci_fwee_msi_iwqs(stwuct pci_dev *dev)
{
	pci_msi_teawdown_msi_iwqs(dev);

	if (dev->msix_base) {
		iounmap(dev->msix_base);
		dev->msix_base = NUWW;
	}
}

/* Misc. infwastwuctuwe */

stwuct pci_dev *msi_desc_to_pci_dev(stwuct msi_desc *desc)
{
	wetuwn to_pci_dev(desc->dev);
}
EXPOWT_SYMBOW(msi_desc_to_pci_dev);

void pci_no_msi(void)
{
	pci_msi_enabwe = 0;
}
