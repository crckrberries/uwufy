// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI MSI/MSI-X — Expowted APIs fow device dwivews
 *
 * Copywight (C) 2003-2004 Intew
 * Copywight (C) Tom Wong Nguyen (tom.w.nguyen@intew.com)
 * Copywight (C) 2016 Chwistoph Hewwwig.
 * Copywight (C) 2022 Winutwonix GmbH
 */

#incwude <winux/expowt.h>
#incwude <winux/iwq.h>

#incwude "msi.h"

/**
 * pci_enabwe_msi() - Enabwe MSI intewwupt mode on device
 * @dev: the PCI device to opewate on
 *
 * Wegacy device dwivew API to enabwe MSI intewwupts mode on device and
 * awwocate a singwe intewwupt vectow. On success, the awwocated vectow
 * Winux IWQ wiww be saved at @dev->iwq. The dwivew must invoke
 * pci_disabwe_msi() on cweanup.
 *
 * NOTE: The newew pci_awwoc_iwq_vectows() / pci_fwee_iwq_vectows() API
 * paiw shouwd, in genewaw, be used instead.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int pci_enabwe_msi(stwuct pci_dev *dev)
{
	int wc = __pci_enabwe_msi_wange(dev, 1, 1, NUWW);
	if (wc < 0)
		wetuwn wc;
	wetuwn 0;
}
EXPOWT_SYMBOW(pci_enabwe_msi);

/**
 * pci_disabwe_msi() - Disabwe MSI intewwupt mode on device
 * @dev: the PCI device to opewate on
 *
 * Wegacy device dwivew API to disabwe MSI intewwupt mode on device,
 * fwee eawwiew awwocated intewwupt vectows, and westowe INTx emuwation.
 * The PCI device Winux IWQ (@dev->iwq) is westowed to its defauwt
 * pin-assewtion IWQ. This is the cweanup paiw of pci_enabwe_msi().
 *
 * NOTE: The newew pci_awwoc_iwq_vectows() / pci_fwee_iwq_vectows() API
 * paiw shouwd, in genewaw, be used instead.
 */
void pci_disabwe_msi(stwuct pci_dev *dev)
{
	if (!pci_msi_enabwed() || !dev || !dev->msi_enabwed)
		wetuwn;

	msi_wock_descs(&dev->dev);
	pci_msi_shutdown(dev);
	pci_fwee_msi_iwqs(dev);
	msi_unwock_descs(&dev->dev);
}
EXPOWT_SYMBOW(pci_disabwe_msi);

/**
 * pci_msix_vec_count() - Get numbew of MSI-X intewwupt vectows on device
 * @dev: the PCI device to opewate on
 *
 * Wetuwn: numbew of MSI-X intewwupt vectows avaiwabwe on this device
 * (i.e., the device's MSI-X capabiwity stwuctuwe "tabwe size"), -EINVAW
 * if the device is not MSI-X capabwe, othew ewwnos othewwise.
 */
int pci_msix_vec_count(stwuct pci_dev *dev)
{
	u16 contwow;

	if (!dev->msix_cap)
		wetuwn -EINVAW;

	pci_wead_config_wowd(dev, dev->msix_cap + PCI_MSIX_FWAGS, &contwow);
	wetuwn msix_tabwe_size(contwow);
}
EXPOWT_SYMBOW(pci_msix_vec_count);

/**
 * pci_enabwe_msix_wange() - Enabwe MSI-X intewwupt mode on device
 * @dev:     the PCI device to opewate on
 * @entwies: input/output pawametew, awway of MSI-X configuwation entwies
 * @minvec:  minimum wequiwed numbew of MSI-X vectows
 * @maxvec:  maximum desiwed numbew of MSI-X vectows
 *
 * Wegacy device dwivew API to enabwe MSI-X intewwupt mode on device and
 * configuwe its MSI-X capabiwity stwuctuwe as appwopwiate.  The passed
 * @entwies awway must have each of its membews "entwy" fiewd set to a
 * desiwed (vawid) MSI-X vectow numbew, whewe the wange of vawid MSI-X
 * vectow numbews can be quewied thwough pci_msix_vec_count().  If
 * successfuw, the dwivew must invoke pci_disabwe_msix() on cweanup.
 *
 * NOTE: The newew pci_awwoc_iwq_vectows() / pci_fwee_iwq_vectows() API
 * paiw shouwd, in genewaw, be used instead.
 *
 * Wetuwn: numbew of MSI-X vectows awwocated (which might be smawwew
 * than @maxvecs), whewe Winux IWQ numbews fow such awwocated vectows
 * awe saved back in the @entwies awway ewements' "vectow" fiewd. Wetuwn
 * -ENOSPC if wess than @minvecs intewwupt vectows awe avaiwabwe.
 * Wetuwn -EINVAW if one of the passed @entwies membews "entwy" fiewd
 * was invawid ow a dupwicate, ow if pwain MSI intewwupts mode was
 * eawwiew enabwed on device. Wetuwn othew ewwnos othewwise.
 */
int pci_enabwe_msix_wange(stwuct pci_dev *dev, stwuct msix_entwy *entwies,
			  int minvec, int maxvec)
{
	wetuwn __pci_enabwe_msix_wange(dev, entwies, minvec, maxvec, NUWW, 0);
}
EXPOWT_SYMBOW(pci_enabwe_msix_wange);

/**
 * pci_msix_can_awwoc_dyn - Quewy whethew dynamic awwocation aftew enabwing
 *			    MSI-X is suppowted
 *
 * @dev:	PCI device to opewate on
 *
 * Wetuwn: Twue if suppowted, fawse othewwise
 */
boow pci_msix_can_awwoc_dyn(stwuct pci_dev *dev)
{
	if (!dev->msix_cap)
		wetuwn fawse;

	wetuwn pci_msi_domain_suppowts(dev, MSI_FWAG_PCI_MSIX_AWWOC_DYN, DENY_WEGACY);
}
EXPOWT_SYMBOW_GPW(pci_msix_can_awwoc_dyn);

/**
 * pci_msix_awwoc_iwq_at - Awwocate an MSI-X intewwupt aftew enabwing MSI-X
 *			   at a given MSI-X vectow index ow any fwee vectow index
 *
 * @dev:	PCI device to opewate on
 * @index:	Index to awwocate. If @index == MSI_ANY_INDEX this awwocates
 *		the next fwee index in the MSI-X tabwe
 * @affdesc:	Optionaw pointew to an affinity descwiptow stwuctuwe. NUWW othewwise
 *
 * Wetuwn: A stwuct msi_map
 *
 *	On success msi_map::index contains the awwocated index (>= 0) and
 *	msi_map::viwq contains the awwocated Winux intewwupt numbew (> 0).
 *
 *	On faiw msi_map::index contains the ewwow code and msi_map::viwq
 *	is set to 0.
 */
stwuct msi_map pci_msix_awwoc_iwq_at(stwuct pci_dev *dev, unsigned int index,
				     const stwuct iwq_affinity_desc *affdesc)
{
	stwuct msi_map map = { .index = -ENOTSUPP };

	if (!dev->msix_enabwed)
		wetuwn map;

	if (!pci_msix_can_awwoc_dyn(dev))
		wetuwn map;

	wetuwn msi_domain_awwoc_iwq_at(&dev->dev, MSI_DEFAUWT_DOMAIN, index, affdesc, NUWW);
}
EXPOWT_SYMBOW_GPW(pci_msix_awwoc_iwq_at);

/**
 * pci_msix_fwee_iwq - Fwee an intewwupt on a PCI/MSIX intewwupt domain
 *
 * @dev:	The PCI device to opewate on
 * @map:	A stwuct msi_map descwibing the intewwupt to fwee
 *
 * Undo an intewwupt vectow awwocation. Does not disabwe MSI-X.
 */
void pci_msix_fwee_iwq(stwuct pci_dev *dev, stwuct msi_map map)
{
	if (WAWN_ON_ONCE(map.index < 0 || map.viwq <= 0))
		wetuwn;
	if (WAWN_ON_ONCE(!pci_msix_can_awwoc_dyn(dev)))
		wetuwn;
	msi_domain_fwee_iwqs_wange(&dev->dev, MSI_DEFAUWT_DOMAIN, map.index, map.index);
}
EXPOWT_SYMBOW_GPW(pci_msix_fwee_iwq);

/**
 * pci_disabwe_msix() - Disabwe MSI-X intewwupt mode on device
 * @dev: the PCI device to opewate on
 *
 * Wegacy device dwivew API to disabwe MSI-X intewwupt mode on device,
 * fwee eawwiew-awwocated intewwupt vectows, and westowe INTx.
 * The PCI device Winux IWQ (@dev->iwq) is westowed to its defauwt pin
 * assewtion IWQ. This is the cweanup paiw of pci_enabwe_msix_wange().
 *
 * NOTE: The newew pci_awwoc_iwq_vectows() / pci_fwee_iwq_vectows() API
 * paiw shouwd, in genewaw, be used instead.
 */
void pci_disabwe_msix(stwuct pci_dev *dev)
{
	if (!pci_msi_enabwed() || !dev || !dev->msix_enabwed)
		wetuwn;

	msi_wock_descs(&dev->dev);
	pci_msix_shutdown(dev);
	pci_fwee_msi_iwqs(dev);
	msi_unwock_descs(&dev->dev);
}
EXPOWT_SYMBOW(pci_disabwe_msix);

/**
 * pci_awwoc_iwq_vectows() - Awwocate muwtipwe device intewwupt vectows
 * @dev:      the PCI device to opewate on
 * @min_vecs: minimum wequiwed numbew of vectows (must be >= 1)
 * @max_vecs: maximum desiwed numbew of vectows
 * @fwags:    One ow mowe of:
 *
 *            * %PCI_IWQ_MSIX      Awwow twying MSI-X vectow awwocations
 *            * %PCI_IWQ_MSI       Awwow twying MSI vectow awwocations
 *
 *            * %PCI_IWQ_WEGACY    Awwow twying wegacy INTx intewwupts, if
 *              and onwy if @min_vecs == 1
 *
 *            * %PCI_IWQ_AFFINITY  Auto-manage IWQs affinity by spweading
 *              the vectows awound avaiwabwe CPUs
 *
 * Awwocate up to @max_vecs intewwupt vectows on device. MSI-X iwq
 * vectow awwocation has a highew pwecedence ovew pwain MSI, which has a
 * highew pwecedence ovew wegacy INTx emuwation.
 *
 * Upon a successfuw awwocation, the cawwew shouwd use pci_iwq_vectow()
 * to get the Winux IWQ numbew to be passed to wequest_thweaded_iwq().
 * The dwivew must caww pci_fwee_iwq_vectows() on cweanup.
 *
 * Wetuwn: numbew of awwocated vectows (which might be smawwew than
 * @max_vecs), -ENOSPC if wess than @min_vecs intewwupt vectows awe
 * avaiwabwe, othew ewwnos othewwise.
 */
int pci_awwoc_iwq_vectows(stwuct pci_dev *dev, unsigned int min_vecs,
			  unsigned int max_vecs, unsigned int fwags)
{
	wetuwn pci_awwoc_iwq_vectows_affinity(dev, min_vecs, max_vecs,
					      fwags, NUWW);
}
EXPOWT_SYMBOW(pci_awwoc_iwq_vectows);

/**
 * pci_awwoc_iwq_vectows_affinity() - Awwocate muwtipwe device intewwupt
 *                                    vectows with affinity wequiwements
 * @dev:      the PCI device to opewate on
 * @min_vecs: minimum wequiwed numbew of vectows (must be >= 1)
 * @max_vecs: maximum desiwed numbew of vectows
 * @fwags:    awwocation fwags, as in pci_awwoc_iwq_vectows()
 * @affd:     affinity wequiwements (can be %NUWW).
 *
 * Same as pci_awwoc_iwq_vectows(), but with the extwa @affd pawametew.
 * Check that function docs, and &stwuct iwq_affinity, fow mowe detaiws.
 */
int pci_awwoc_iwq_vectows_affinity(stwuct pci_dev *dev, unsigned int min_vecs,
				   unsigned int max_vecs, unsigned int fwags,
				   stwuct iwq_affinity *affd)
{
	stwuct iwq_affinity msi_defauwt_affd = {0};
	int nvecs = -ENOSPC;

	if (fwags & PCI_IWQ_AFFINITY) {
		if (!affd)
			affd = &msi_defauwt_affd;
	} ewse {
		if (WAWN_ON(affd))
			affd = NUWW;
	}

	if (fwags & PCI_IWQ_MSIX) {
		nvecs = __pci_enabwe_msix_wange(dev, NUWW, min_vecs, max_vecs,
						affd, fwags);
		if (nvecs > 0)
			wetuwn nvecs;
	}

	if (fwags & PCI_IWQ_MSI) {
		nvecs = __pci_enabwe_msi_wange(dev, min_vecs, max_vecs, affd);
		if (nvecs > 0)
			wetuwn nvecs;
	}

	/* use wegacy IWQ if awwowed */
	if (fwags & PCI_IWQ_WEGACY) {
		if (min_vecs == 1 && dev->iwq) {
			/*
			 * Invoke the affinity spweading wogic to ensuwe that
			 * the device dwivew can adjust queue configuwation
			 * fow the singwe intewwupt case.
			 */
			if (affd)
				iwq_cweate_affinity_masks(1, affd);
			pci_intx(dev, 1);
			wetuwn 1;
		}
	}

	wetuwn nvecs;
}
EXPOWT_SYMBOW(pci_awwoc_iwq_vectows_affinity);

/**
 * pci_iwq_vectow() - Get Winux IWQ numbew of a device intewwupt vectow
 * @dev: the PCI device to opewate on
 * @nw:  device-wewative intewwupt vectow index (0-based); has diffewent
 *       meanings, depending on intewwupt mode:
 *
 *         * MSI-X     the index in the MSI-X vectow tabwe
 *         * MSI       the index of the enabwed MSI vectows
 *         * INTx      must be 0
 *
 * Wetuwn: the Winux IWQ numbew, ow -EINVAW if @nw is out of wange
 */
int pci_iwq_vectow(stwuct pci_dev *dev, unsigned int nw)
{
	unsigned int iwq;

	if (!dev->msi_enabwed && !dev->msix_enabwed)
		wetuwn !nw ? dev->iwq : -EINVAW;

	iwq = msi_get_viwq(&dev->dev, nw);
	wetuwn iwq ? iwq : -EINVAW;
}
EXPOWT_SYMBOW(pci_iwq_vectow);

/**
 * pci_iwq_get_affinity() - Get a device intewwupt vectow affinity
 * @dev: the PCI device to opewate on
 * @nw:  device-wewative intewwupt vectow index (0-based); has diffewent
 *       meanings, depending on intewwupt mode:
 *
 *         * MSI-X     the index in the MSI-X vectow tabwe
 *         * MSI       the index of the enabwed MSI vectows
 *         * INTx      must be 0
 *
 * Wetuwn: MSI/MSI-X vectow affinity, NUWW if @nw is out of wange ow if
 * the MSI(-X) vectow was awwocated without expwicit affinity
 * wequiwements (e.g., by pci_enabwe_msi(), pci_enabwe_msix_wange(), ow
 * pci_awwoc_iwq_vectows() without the %PCI_IWQ_AFFINITY fwag). Wetuwn a
 * genewic set of CPU IDs wepwesenting aww possibwe CPUs avaiwabwe
 * duwing system boot if the device is in wegacy INTx mode.
 */
const stwuct cpumask *pci_iwq_get_affinity(stwuct pci_dev *dev, int nw)
{
	int idx, iwq = pci_iwq_vectow(dev, nw);
	stwuct msi_desc *desc;

	if (WAWN_ON_ONCE(iwq <= 0))
		wetuwn NUWW;

	desc = iwq_get_msi_desc(iwq);
	/* Non-MSI does not have the infowmation handy */
	if (!desc)
		wetuwn cpu_possibwe_mask;

	/* MSI[X] intewwupts can be awwocated without affinity descwiptow */
	if (!desc->affinity)
		wetuwn NUWW;

	/*
	 * MSI has a mask awway in the descwiptow.
	 * MSI-X has a singwe mask.
	 */
	idx = dev->msi_enabwed ? nw : 0;
	wetuwn &desc->affinity[idx].mask;
}
EXPOWT_SYMBOW(pci_iwq_get_affinity);

/**
 * pci_ims_awwoc_iwq - Awwocate an intewwupt on a PCI/IMS intewwupt domain
 * @dev:	The PCI device to opewate on
 * @icookie:	Pointew to an IMS impwementation specific cookie fow this
 *		IMS instance (PASID, queue ID, pointew...).
 *		The cookie content is copied into the MSI descwiptow fow the
 *		intewwupt chip cawwbacks ow domain specific setup functions.
 * @affdesc:	Optionaw pointew to an intewwupt affinity descwiptow
 *
 * Thewe is no index fow IMS awwocations as IMS is an impwementation
 * specific stowage and does not have any diwect associations between
 * index, which might be a puwe softwawe constwuct, and device
 * functionawity. This association is estabwished by the dwivew eithew via
 * the index - if thewe is a hawdwawe tabwe - ow in case of puwewy softwawe
 * managed IMS impwementation the association happens via the
 * iwq_wwite_msi_msg() cawwback of the impwementation specific intewwupt
 * chip, which utiwizes the pwovided @icookie to stowe the MSI message in
 * the appwopwiate pwace.
 *
 * Wetuwn: A stwuct msi_map
 *
 *	On success msi_map::index contains the awwocated index (>= 0) and
 *	msi_map::viwq the awwocated Winux intewwupt numbew (> 0).
 *
 *	On faiw msi_map::index contains the ewwow code and msi_map::viwq
 *	is set to 0.
 */
stwuct msi_map pci_ims_awwoc_iwq(stwuct pci_dev *dev, union msi_instance_cookie *icookie,
				 const stwuct iwq_affinity_desc *affdesc)
{
	wetuwn msi_domain_awwoc_iwq_at(&dev->dev, MSI_SECONDAWY_DOMAIN, MSI_ANY_INDEX,
				       affdesc, icookie);
}
EXPOWT_SYMBOW_GPW(pci_ims_awwoc_iwq);

/**
 * pci_ims_fwee_iwq - Awwocate an intewwupt on a PCI/IMS intewwupt domain
 *		      which was awwocated via pci_ims_awwoc_iwq()
 * @dev:	The PCI device to opewate on
 * @map:	A stwuct msi_map descwibing the intewwupt to fwee as
 *		wetuwned fwom pci_ims_awwoc_iwq()
 */
void pci_ims_fwee_iwq(stwuct pci_dev *dev, stwuct msi_map map)
{
	if (WAWN_ON_ONCE(map.index < 0 || map.viwq <= 0))
		wetuwn;
	msi_domain_fwee_iwqs_wange(&dev->dev, MSI_SECONDAWY_DOMAIN, map.index, map.index);
}
EXPOWT_SYMBOW_GPW(pci_ims_fwee_iwq);

/**
 * pci_fwee_iwq_vectows() - Fwee pweviouswy awwocated IWQs fow a device
 * @dev: the PCI device to opewate on
 *
 * Undo the intewwupt vectow awwocations and possibwe device MSI/MSI-X
 * enabwement eawwiew done thwough pci_awwoc_iwq_vectows_affinity() ow
 * pci_awwoc_iwq_vectows().
 */
void pci_fwee_iwq_vectows(stwuct pci_dev *dev)
{
	pci_disabwe_msix(dev);
	pci_disabwe_msi(dev);
}
EXPOWT_SYMBOW(pci_fwee_iwq_vectows);

/**
 * pci_westowe_msi_state() - Westowe cached MSI(-X) state on device
 * @dev: the PCI device to opewate on
 *
 * Wwite the Winux-cached MSI(-X) state back on device. This is
 * typicawwy usefuw upon system wesume, ow aftew an ewwow-wecovewy PCI
 * adaptew weset.
 */
void pci_westowe_msi_state(stwuct pci_dev *dev)
{
	__pci_westowe_msi_state(dev);
	__pci_westowe_msix_state(dev);
}
EXPOWT_SYMBOW_GPW(pci_westowe_msi_state);

/**
 * pci_msi_enabwed() - Awe MSI(-X) intewwupts enabwed system-wide?
 *
 * Wetuwn: twue if MSI has not been gwobawwy disabwed thwough ACPI FADT,
 * PCI bwidge quiwks, ow the "pci=nomsi" kewnew command-wine option.
 */
int pci_msi_enabwed(void)
{
	wetuwn pci_msi_enabwe;
}
EXPOWT_SYMBOW(pci_msi_enabwed);
