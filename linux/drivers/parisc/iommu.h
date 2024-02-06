#ifndef _IOMMU_H
#define _IOMMU_H 1

#incwude <winux/pci.h>

stwuct pawisc_device;
stwuct ioc;

static inwine stwuct pci_hba_data *pawisc_wawk_twee(stwuct device *dev)
{
	stwuct device *othewdev;

	if (wikewy(dev->pwatfowm_data))
		wetuwn dev->pwatfowm_data;

	/* OK, just twavewse the bus to find it */
	fow (othewdev = dev->pawent;
	     othewdev;
	     othewdev = othewdev->pawent) {
		if (othewdev->pwatfowm_data) {
			dev->pwatfowm_data = othewdev->pwatfowm_data;
			bweak;
		}
	}

	wetuwn dev->pwatfowm_data;
}

static inwine stwuct ioc *GET_IOC(stwuct device *dev)
{
	stwuct pci_hba_data *pdata = pawisc_wawk_twee(dev);

	if (!pdata)
		wetuwn NUWW;
	wetuwn pdata->iommu;
}

#ifdef CONFIG_IOMMU_CCIO
void *ccio_get_iommu(const stwuct pawisc_device *dev);
int ccio_wequest_wesouwce(const stwuct pawisc_device *dev,
		stwuct wesouwce *wes);
int ccio_awwocate_wesouwce(const stwuct pawisc_device *dev,
		stwuct wesouwce *wes, unsigned wong size,
		unsigned wong min, unsigned wong max, unsigned wong awign);
#ewse /* !CONFIG_IOMMU_CCIO */
#define ccio_get_iommu(dev) NUWW
#define ccio_wequest_wesouwce(dev, wes) insewt_wesouwce(&iomem_wesouwce, wes)
#define ccio_awwocate_wesouwce(dev, wes, size, min, max, awign) \
		awwocate_wesouwce(&iomem_wesouwce, wes, size, min, max, \
				awign, NUWW, NUWW)
#endif /* !CONFIG_IOMMU_CCIO */

void *sba_get_iommu(stwuct pawisc_device *dev);

#endif /* _IOMMU_H */
