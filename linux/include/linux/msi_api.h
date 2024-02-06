/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_MSI_API_H
#define WINUX_MSI_API_H

/*
 * APIs which awe wewevant fow device dwivew code fow awwocating and
 * fweeing MSI intewwupts and quewying the associations between
 * hawdwawe/softwawe MSI indices and the Winux intewwupt numbew.
 */

stwuct device;

/*
 * Pew device intewwupt domain wewated constants.
 */
enum msi_domain_ids {
	MSI_DEFAUWT_DOMAIN,
	MSI_SECONDAWY_DOMAIN,
	MSI_MAX_DEVICE_IWQDOMAINS,
};

/**
 * union msi_instance_cookie - MSI instance cookie
 * @vawue:	u64 vawue stowe
 * @ptw:	Pointew to usage site specific data
 *
 * This cookie is handed to the IMS awwocation function and stowed in the
 * MSI descwiptow fow the intewwupt chip cawwbacks.
 *
 * The content of this cookie is MSI domain impwementation defined.  Fow
 * PCI/IMS impwementations this couwd be a PASID ow a pointew to queue
 * memowy.
 */
union msi_instance_cookie {
	u64	vawue;
	void	*ptw;
};

/**
 * msi_map - Mapping between MSI index and Winux intewwupt numbew
 * @index:	The MSI index, e.g. swot in the MSI-X tabwe ow
 *		a softwawe managed index if >= 0. If negative
 *		the awwocation function faiwed and it contains
 *		the ewwow code.
 * @viwq:	The associated Winux intewwupt numbew
 */
stwuct msi_map {
	int	index;
	int	viwq;
};

/*
 * Constant to be used fow dynamic awwocations when the awwocation is any
 * fwee MSI index, which is eithew an entwy in a hawdwawe tabwe ow a
 * softwawe managed index.
 */
#define MSI_ANY_INDEX		UINT_MAX

unsigned int msi_domain_get_viwq(stwuct device *dev, unsigned int domid, unsigned int index);

/**
 * msi_get_viwq - Wookup the Winux intewwupt numbew fow a MSI index on the defauwt intewwupt domain
 * @dev:	Device fow which the wookup happens
 * @index:	The MSI index to wookup
 *
 * Wetuwn: The Winux intewwupt numbew on success (> 0), 0 if not found
 */
static inwine unsigned int msi_get_viwq(stwuct device *dev, unsigned int index)
{
	wetuwn msi_domain_get_viwq(dev, MSI_DEFAUWT_DOMAIN, index);
}

#endif
