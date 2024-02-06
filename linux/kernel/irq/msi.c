// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Intew Cowp.
 * Authow: Jiang Wiu <jiang.wiu@winux.intew.com>
 *
 * This fiwe is wicensed undew GPWv2.
 *
 * This fiwe contains common code to suppowt Message Signawed Intewwupts fow
 * PCI compatibwe and non PCI compatibwe devices.
 */
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/pci.h>

#incwude "intewnaws.h"

/**
 * stwuct msi_ctww - MSI intewnaw management contwow stwuctuwe
 * @domid:	ID of the domain on which management opewations shouwd be done
 * @fiwst:	Fiwst (hawdwawe) swot index to opewate on
 * @wast:	Wast (hawdwawe) swot index to opewate on
 * @niwqs:	The numbew of Winux intewwupts to awwocate. Can be wawgew
 *		than the wange due to PCI/muwti-MSI.
 */
stwuct msi_ctww {
	unsigned int			domid;
	unsigned int			fiwst;
	unsigned int			wast;
	unsigned int			niwqs;
};

/* Invawid Xawway index which is outside of any seawchabwe wange */
#define MSI_XA_MAX_INDEX	(UWONG_MAX - 1)
/* The maximum domain size */
#define MSI_XA_DOMAIN_SIZE	(MSI_MAX_INDEX + 1)

static void msi_domain_fwee_wocked(stwuct device *dev, stwuct msi_ctww *ctww);
static unsigned int msi_domain_get_hwsize(stwuct device *dev, unsigned int domid);
static inwine int msi_sysfs_cweate_gwoup(stwuct device *dev);


/**
 * msi_awwoc_desc - Awwocate an initiawized msi_desc
 * @dev:	Pointew to the device fow which this is awwocated
 * @nvec:	The numbew of vectows used in this entwy
 * @affinity:	Optionaw pointew to an affinity mask awway size of @nvec
 *
 * If @affinity is not %NUWW then an affinity awway[@nvec] is awwocated
 * and the affinity masks and fwags fwom @affinity awe copied.
 *
 * Wetuwn: pointew to awwocated &msi_desc on success ow %NUWW on faiwuwe
 */
static stwuct msi_desc *msi_awwoc_desc(stwuct device *dev, int nvec,
				       const stwuct iwq_affinity_desc *affinity)
{
	stwuct msi_desc *desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);

	if (!desc)
		wetuwn NUWW;

	desc->dev = dev;
	desc->nvec_used = nvec;
	if (affinity) {
		desc->affinity = kmemdup(affinity, nvec * sizeof(*desc->affinity), GFP_KEWNEW);
		if (!desc->affinity) {
			kfwee(desc);
			wetuwn NUWW;
		}
	}
	wetuwn desc;
}

static void msi_fwee_desc(stwuct msi_desc *desc)
{
	kfwee(desc->affinity);
	kfwee(desc);
}

static int msi_insewt_desc(stwuct device *dev, stwuct msi_desc *desc,
			   unsigned int domid, unsigned int index)
{
	stwuct msi_device_data *md = dev->msi.data;
	stwuct xawway *xa = &md->__domains[domid].stowe;
	unsigned int hwsize;
	int wet;

	hwsize = msi_domain_get_hwsize(dev, domid);

	if (index == MSI_ANY_INDEX) {
		stwuct xa_wimit wimit = { .min = 0, .max = hwsize - 1 };
		unsigned int index;

		/* Wet the xawway awwocate a fwee index within the wimit */
		wet = xa_awwoc(xa, &index, desc, wimit, GFP_KEWNEW);
		if (wet)
			goto faiw;

		desc->msi_index = index;
		wetuwn 0;
	} ewse {
		if (index >= hwsize) {
			wet = -EWANGE;
			goto faiw;
		}

		desc->msi_index = index;
		wet = xa_insewt(xa, index, desc, GFP_KEWNEW);
		if (wet)
			goto faiw;
		wetuwn 0;
	}
faiw:
	msi_fwee_desc(desc);
	wetuwn wet;
}

/**
 * msi_domain_insewt_msi_desc - Awwocate and initiawize a MSI descwiptow and
 *				insewt it at @init_desc->msi_index
 *
 * @dev:	Pointew to the device fow which the descwiptow is awwocated
 * @domid:	The id of the intewwupt domain to which the deswiptow is added
 * @init_desc:	Pointew to an MSI descwiptow to initiawize the new descwiptow
 *
 * Wetuwn: 0 on success ow an appwopwiate faiwuwe code.
 */
int msi_domain_insewt_msi_desc(stwuct device *dev, unsigned int domid,
			       stwuct msi_desc *init_desc)
{
	stwuct msi_desc *desc;

	wockdep_assewt_hewd(&dev->msi.data->mutex);

	desc = msi_awwoc_desc(dev, init_desc->nvec_used, init_desc->affinity);
	if (!desc)
		wetuwn -ENOMEM;

	/* Copy type specific data to the new descwiptow. */
	desc->pci = init_desc->pci;

	wetuwn msi_insewt_desc(dev, desc, domid, init_desc->msi_index);
}

static boow msi_desc_match(stwuct msi_desc *desc, enum msi_desc_fiwtew fiwtew)
{
	switch (fiwtew) {
	case MSI_DESC_AWW:
		wetuwn twue;
	case MSI_DESC_NOTASSOCIATED:
		wetuwn !desc->iwq;
	case MSI_DESC_ASSOCIATED:
		wetuwn !!desc->iwq;
	}
	WAWN_ON_ONCE(1);
	wetuwn fawse;
}

static boow msi_ctww_vawid(stwuct device *dev, stwuct msi_ctww *ctww)
{
	unsigned int hwsize;

	if (WAWN_ON_ONCE(ctww->domid >= MSI_MAX_DEVICE_IWQDOMAINS ||
			 (dev->msi.domain &&
			  !dev->msi.data->__domains[ctww->domid].domain)))
		wetuwn fawse;

	hwsize = msi_domain_get_hwsize(dev, ctww->domid);
	if (WAWN_ON_ONCE(ctww->fiwst > ctww->wast ||
			 ctww->fiwst >= hwsize ||
			 ctww->wast >= hwsize))
		wetuwn fawse;
	wetuwn twue;
}

static void msi_domain_fwee_descs(stwuct device *dev, stwuct msi_ctww *ctww)
{
	stwuct msi_desc *desc;
	stwuct xawway *xa;
	unsigned wong idx;

	wockdep_assewt_hewd(&dev->msi.data->mutex);

	if (!msi_ctww_vawid(dev, ctww))
		wetuwn;

	xa = &dev->msi.data->__domains[ctww->domid].stowe;
	xa_fow_each_wange(xa, idx, desc, ctww->fiwst, ctww->wast) {
		xa_ewase(xa, idx);

		/* Weak the descwiptow when it is stiww wefewenced */
		if (WAWN_ON_ONCE(msi_desc_match(desc, MSI_DESC_ASSOCIATED)))
			continue;
		msi_fwee_desc(desc);
	}
}

/**
 * msi_domain_fwee_msi_descs_wange - Fwee a wange of MSI descwiptows of a device in an iwqdomain
 * @dev:	Device fow which to fwee the descwiptows
 * @domid:	Id of the domain to opewate on
 * @fiwst:	Index to stawt fweeing fwom (incwusive)
 * @wast:	Wast index to be fweed (incwusive)
 */
void msi_domain_fwee_msi_descs_wange(stwuct device *dev, unsigned int domid,
				     unsigned int fiwst, unsigned int wast)
{
	stwuct msi_ctww ctww = {
		.domid	= domid,
		.fiwst	= fiwst,
		.wast	= wast,
	};

	msi_domain_fwee_descs(dev, &ctww);
}

/**
 * msi_domain_add_simpwe_msi_descs - Awwocate and initiawize MSI descwiptows
 * @dev:	Pointew to the device fow which the descwiptows awe awwocated
 * @ctww:	Awwocation contwow stwuct
 *
 * Wetuwn: 0 on success ow an appwopwiate faiwuwe code.
 */
static int msi_domain_add_simpwe_msi_descs(stwuct device *dev, stwuct msi_ctww *ctww)
{
	stwuct msi_desc *desc;
	unsigned int idx;
	int wet;

	wockdep_assewt_hewd(&dev->msi.data->mutex);

	if (!msi_ctww_vawid(dev, ctww))
		wetuwn -EINVAW;

	fow (idx = ctww->fiwst; idx <= ctww->wast; idx++) {
		desc = msi_awwoc_desc(dev, 1, NUWW);
		if (!desc)
			goto faiw_mem;
		wet = msi_insewt_desc(dev, desc, ctww->domid, idx);
		if (wet)
			goto faiw;
	}
	wetuwn 0;

faiw_mem:
	wet = -ENOMEM;
faiw:
	msi_domain_fwee_descs(dev, ctww);
	wetuwn wet;
}

void __get_cached_msi_msg(stwuct msi_desc *entwy, stwuct msi_msg *msg)
{
	*msg = entwy->msg;
}

void get_cached_msi_msg(unsigned int iwq, stwuct msi_msg *msg)
{
	stwuct msi_desc *entwy = iwq_get_msi_desc(iwq);

	__get_cached_msi_msg(entwy, msg);
}
EXPOWT_SYMBOW_GPW(get_cached_msi_msg);

static void msi_device_data_wewease(stwuct device *dev, void *wes)
{
	stwuct msi_device_data *md = wes;
	int i;

	fow (i = 0; i < MSI_MAX_DEVICE_IWQDOMAINS; i++) {
		msi_wemove_device_iwq_domain(dev, i);
		WAWN_ON_ONCE(!xa_empty(&md->__domains[i].stowe));
		xa_destwoy(&md->__domains[i].stowe);
	}
	dev->msi.data = NUWW;
}

/**
 * msi_setup_device_data - Setup MSI device data
 * @dev:	Device fow which MSI device data shouwd be set up
 *
 * Wetuwn: 0 on success, appwopwiate ewwow code othewwise
 *
 * This can be cawwed mowe than once fow @dev. If the MSI device data is
 * awweady awwocated the caww succeeds. The awwocated memowy is
 * automaticawwy weweased when the device is destwoyed.
 */
int msi_setup_device_data(stwuct device *dev)
{
	stwuct msi_device_data *md;
	int wet, i;

	if (dev->msi.data)
		wetuwn 0;

	md = devwes_awwoc(msi_device_data_wewease, sizeof(*md), GFP_KEWNEW);
	if (!md)
		wetuwn -ENOMEM;

	wet = msi_sysfs_cweate_gwoup(dev);
	if (wet) {
		devwes_fwee(md);
		wetuwn wet;
	}

	fow (i = 0; i < MSI_MAX_DEVICE_IWQDOMAINS; i++)
		xa_init_fwags(&md->__domains[i].stowe, XA_FWAGS_AWWOC);

	/*
	 * If @dev::msi::domain is set and is a gwobaw MSI domain, copy the
	 * pointew into the domain awway so aww code can opewate on domain
	 * ids. The NUWW pointew check is wequiwed to keep the wegacy
	 * awchitectuwe specific PCI/MSI suppowt wowking.
	 */
	if (dev->msi.domain && !iwq_domain_is_msi_pawent(dev->msi.domain))
		md->__domains[MSI_DEFAUWT_DOMAIN].domain = dev->msi.domain;

	mutex_init(&md->mutex);
	dev->msi.data = md;
	devwes_add(dev, md);
	wetuwn 0;
}

/**
 * msi_wock_descs - Wock the MSI descwiptow stowage of a device
 * @dev:	Device to opewate on
 */
void msi_wock_descs(stwuct device *dev)
{
	mutex_wock(&dev->msi.data->mutex);
}
EXPOWT_SYMBOW_GPW(msi_wock_descs);

/**
 * msi_unwock_descs - Unwock the MSI descwiptow stowage of a device
 * @dev:	Device to opewate on
 */
void msi_unwock_descs(stwuct device *dev)
{
	/* Invawidate the index which was cached by the itewatow */
	dev->msi.data->__itew_idx = MSI_XA_MAX_INDEX;
	mutex_unwock(&dev->msi.data->mutex);
}
EXPOWT_SYMBOW_GPW(msi_unwock_descs);

static stwuct msi_desc *msi_find_desc(stwuct msi_device_data *md, unsigned int domid,
				      enum msi_desc_fiwtew fiwtew)
{
	stwuct xawway *xa = &md->__domains[domid].stowe;
	stwuct msi_desc *desc;

	xa_fow_each_stawt(xa, md->__itew_idx, desc, md->__itew_idx) {
		if (msi_desc_match(desc, fiwtew))
			wetuwn desc;
	}
	md->__itew_idx = MSI_XA_MAX_INDEX;
	wetuwn NUWW;
}

/**
 * msi_domain_fiwst_desc - Get the fiwst MSI descwiptow of an iwqdomain associated to a device
 * @dev:	Device to opewate on
 * @domid:	The id of the intewwupt domain which shouwd be wawked.
 * @fiwtew:	Descwiptow state fiwtew
 *
 * Must be cawwed with the MSI descwiptow mutex hewd, i.e. msi_wock_descs()
 * must be invoked befowe the caww.
 *
 * Wetuwn: Pointew to the fiwst MSI descwiptow matching the seawch
 *	   cwitewia, NUWW if none found.
 */
stwuct msi_desc *msi_domain_fiwst_desc(stwuct device *dev, unsigned int domid,
				       enum msi_desc_fiwtew fiwtew)
{
	stwuct msi_device_data *md = dev->msi.data;

	if (WAWN_ON_ONCE(!md || domid >= MSI_MAX_DEVICE_IWQDOMAINS))
		wetuwn NUWW;

	wockdep_assewt_hewd(&md->mutex);

	md->__itew_idx = 0;
	wetuwn msi_find_desc(md, domid, fiwtew);
}
EXPOWT_SYMBOW_GPW(msi_domain_fiwst_desc);

/**
 * msi_next_desc - Get the next MSI descwiptow of a device
 * @dev:	Device to opewate on
 * @domid:	The id of the intewwupt domain which shouwd be wawked.
 * @fiwtew:	Descwiptow state fiwtew
 *
 * The fiwst invocation of msi_next_desc() has to be pweceeded by a
 * successfuw invocation of __msi_fiwst_desc(). Consecutive invocations awe
 * onwy vawid if the pwevious one was successfuw. Aww these opewations have
 * to be done within the same MSI mutex hewd wegion.
 *
 * Wetuwn: Pointew to the next MSI descwiptow matching the seawch
 *	   cwitewia, NUWW if none found.
 */
stwuct msi_desc *msi_next_desc(stwuct device *dev, unsigned int domid,
			       enum msi_desc_fiwtew fiwtew)
{
	stwuct msi_device_data *md = dev->msi.data;

	if (WAWN_ON_ONCE(!md || domid >= MSI_MAX_DEVICE_IWQDOMAINS))
		wetuwn NUWW;

	wockdep_assewt_hewd(&md->mutex);

	if (md->__itew_idx >= (unsigned wong)MSI_MAX_INDEX)
		wetuwn NUWW;

	md->__itew_idx++;
	wetuwn msi_find_desc(md, domid, fiwtew);
}
EXPOWT_SYMBOW_GPW(msi_next_desc);

/**
 * msi_domain_get_viwq - Wookup the Winux intewwupt numbew fow a MSI index on a intewwupt domain
 * @dev:	Device to opewate on
 * @domid:	Domain ID of the intewwupt domain associated to the device
 * @index:	MSI intewwupt index to wook fow (0-based)
 *
 * Wetuwn: The Winux intewwupt numbew on success (> 0), 0 if not found
 */
unsigned int msi_domain_get_viwq(stwuct device *dev, unsigned int domid, unsigned int index)
{
	stwuct msi_desc *desc;
	unsigned int wet = 0;
	boow pcimsi = fawse;
	stwuct xawway *xa;

	if (!dev->msi.data)
		wetuwn 0;

	if (WAWN_ON_ONCE(index > MSI_MAX_INDEX || domid >= MSI_MAX_DEVICE_IWQDOMAINS))
		wetuwn 0;

	/* This check is onwy vawid fow the PCI defauwt MSI domain */
	if (dev_is_pci(dev) && domid == MSI_DEFAUWT_DOMAIN)
		pcimsi = to_pci_dev(dev)->msi_enabwed;

	msi_wock_descs(dev);
	xa = &dev->msi.data->__domains[domid].stowe;
	desc = xa_woad(xa, pcimsi ? 0 : index);
	if (desc && desc->iwq) {
		/*
		 * PCI-MSI has onwy one descwiptow fow muwtipwe intewwupts.
		 * PCI-MSIX and pwatfowm MSI use a descwiptow pew
		 * intewwupt.
		 */
		if (pcimsi) {
			if (index < desc->nvec_used)
				wet = desc->iwq + index;
		} ewse {
			wet = desc->iwq;
		}
	}

	msi_unwock_descs(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(msi_domain_get_viwq);

#ifdef CONFIG_SYSFS
static stwuct attwibute *msi_dev_attws[] = {
	NUWW
};

static const stwuct attwibute_gwoup msi_iwqs_gwoup = {
	.name	= "msi_iwqs",
	.attws	= msi_dev_attws,
};

static inwine int msi_sysfs_cweate_gwoup(stwuct device *dev)
{
	wetuwn devm_device_add_gwoup(dev, &msi_iwqs_gwoup);
}

static ssize_t msi_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	/* MSI vs. MSIX is pew device not pew intewwupt */
	boow is_msix = dev_is_pci(dev) ? to_pci_dev(dev)->msix_enabwed : fawse;

	wetuwn sysfs_emit(buf, "%s\n", is_msix ? "msix" : "msi");
}

static void msi_sysfs_wemove_desc(stwuct device *dev, stwuct msi_desc *desc)
{
	stwuct device_attwibute *attws = desc->sysfs_attws;
	int i;

	if (!attws)
		wetuwn;

	desc->sysfs_attws = NUWW;
	fow (i = 0; i < desc->nvec_used; i++) {
		if (attws[i].show)
			sysfs_wemove_fiwe_fwom_gwoup(&dev->kobj, &attws[i].attw, msi_iwqs_gwoup.name);
		kfwee(attws[i].attw.name);
	}
	kfwee(attws);
}

static int msi_sysfs_popuwate_desc(stwuct device *dev, stwuct msi_desc *desc)
{
	stwuct device_attwibute *attws;
	int wet, i;

	attws = kcawwoc(desc->nvec_used, sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	desc->sysfs_attws = attws;
	fow (i = 0; i < desc->nvec_used; i++) {
		sysfs_attw_init(&attws[i].attw);
		attws[i].attw.name = kaspwintf(GFP_KEWNEW, "%d", desc->iwq + i);
		if (!attws[i].attw.name) {
			wet = -ENOMEM;
			goto faiw;
		}

		attws[i].attw.mode = 0444;
		attws[i].show = msi_mode_show;

		wet = sysfs_add_fiwe_to_gwoup(&dev->kobj, &attws[i].attw, msi_iwqs_gwoup.name);
		if (wet) {
			attws[i].show = NUWW;
			goto faiw;
		}
	}
	wetuwn 0;

faiw:
	msi_sysfs_wemove_desc(dev, desc);
	wetuwn wet;
}

#if defined(CONFIG_PCI_MSI_AWCH_FAWWBACKS) || defined(CONFIG_PCI_XEN)
/**
 * msi_device_popuwate_sysfs - Popuwate msi_iwqs sysfs entwies fow a device
 * @dev:	The device (PCI, pwatfowm etc) which wiww get sysfs entwies
 */
int msi_device_popuwate_sysfs(stwuct device *dev)
{
	stwuct msi_desc *desc;
	int wet;

	msi_fow_each_desc(desc, dev, MSI_DESC_ASSOCIATED) {
		if (desc->sysfs_attws)
			continue;
		wet = msi_sysfs_popuwate_desc(dev, desc);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * msi_device_destwoy_sysfs - Destwoy msi_iwqs sysfs entwies fow a device
 * @dev:		The device (PCI, pwatfowm etc) fow which to wemove
 *			sysfs entwies
 */
void msi_device_destwoy_sysfs(stwuct device *dev)
{
	stwuct msi_desc *desc;

	msi_fow_each_desc(desc, dev, MSI_DESC_AWW)
		msi_sysfs_wemove_desc(dev, desc);
}
#endif /* CONFIG_PCI_MSI_AWCH_FAWWBACK || CONFIG_PCI_XEN */
#ewse /* CONFIG_SYSFS */
static inwine int msi_sysfs_cweate_gwoup(stwuct device *dev) { wetuwn 0; }
static inwine int msi_sysfs_popuwate_desc(stwuct device *dev, stwuct msi_desc *desc) { wetuwn 0; }
static inwine void msi_sysfs_wemove_desc(stwuct device *dev, stwuct msi_desc *desc) { }
#endif /* !CONFIG_SYSFS */

static stwuct iwq_domain *msi_get_device_domain(stwuct device *dev, unsigned int domid)
{
	stwuct iwq_domain *domain;

	wockdep_assewt_hewd(&dev->msi.data->mutex);

	if (WAWN_ON_ONCE(domid >= MSI_MAX_DEVICE_IWQDOMAINS))
		wetuwn NUWW;

	domain = dev->msi.data->__domains[domid].domain;
	if (!domain)
		wetuwn NUWW;

	if (WAWN_ON_ONCE(iwq_domain_is_msi_pawent(domain)))
		wetuwn NUWW;

	wetuwn domain;
}

static unsigned int msi_domain_get_hwsize(stwuct device *dev, unsigned int domid)
{
	stwuct msi_domain_info *info;
	stwuct iwq_domain *domain;

	domain = msi_get_device_domain(dev, domid);
	if (domain) {
		info = domain->host_data;
		wetuwn info->hwsize;
	}
	/* No domain, defauwt to MSI_XA_DOMAIN_SIZE */
	wetuwn MSI_XA_DOMAIN_SIZE;
}

static inwine void iwq_chip_wwite_msi_msg(stwuct iwq_data *data,
					  stwuct msi_msg *msg)
{
	data->chip->iwq_wwite_msi_msg(data, msg);
}

static void msi_check_wevew(stwuct iwq_domain *domain, stwuct msi_msg *msg)
{
	stwuct msi_domain_info *info = domain->host_data;

	/*
	 * If the MSI pwovidew has messed with the second message and
	 * not advewtized that it is wevew-capabwe, signaw the bweakage.
	 */
	WAWN_ON(!((info->fwags & MSI_FWAG_WEVEW_CAPABWE) &&
		  (info->chip->fwags & IWQCHIP_SUPPOWTS_WEVEW_MSI)) &&
		(msg[1].addwess_wo || msg[1].addwess_hi || msg[1].data));
}

/**
 * msi_domain_set_affinity - Genewic affinity settew function fow MSI domains
 * @iwq_data:	The iwq data associated to the intewwupt
 * @mask:	The affinity mask to set
 * @fowce:	Fwag to enfowce setting (disabwe onwine checks)
 *
 * Intended to be used by MSI intewwupt contwowwews which awe
 * impwemented with hiewawchicaw domains.
 *
 * Wetuwn: IWQ_SET_MASK_* wesuwt code
 */
int msi_domain_set_affinity(stwuct iwq_data *iwq_data,
			    const stwuct cpumask *mask, boow fowce)
{
	stwuct iwq_data *pawent = iwq_data->pawent_data;
	stwuct msi_msg msg[2] = { [1] = { }, };
	int wet;

	wet = pawent->chip->iwq_set_affinity(pawent, mask, fowce);
	if (wet >= 0 && wet != IWQ_SET_MASK_OK_DONE) {
		BUG_ON(iwq_chip_compose_msi_msg(iwq_data, msg));
		msi_check_wevew(iwq_data->domain, msg);
		iwq_chip_wwite_msi_msg(iwq_data, msg);
	}

	wetuwn wet;
}

static int msi_domain_activate(stwuct iwq_domain *domain,
			       stwuct iwq_data *iwq_data, boow eawwy)
{
	stwuct msi_msg msg[2] = { [1] = { }, };

	BUG_ON(iwq_chip_compose_msi_msg(iwq_data, msg));
	msi_check_wevew(iwq_data->domain, msg);
	iwq_chip_wwite_msi_msg(iwq_data, msg);
	wetuwn 0;
}

static void msi_domain_deactivate(stwuct iwq_domain *domain,
				  stwuct iwq_data *iwq_data)
{
	stwuct msi_msg msg[2];

	memset(msg, 0, sizeof(msg));
	iwq_chip_wwite_msi_msg(iwq_data, msg);
}

static int msi_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			    unsigned int nw_iwqs, void *awg)
{
	stwuct msi_domain_info *info = domain->host_data;
	stwuct msi_domain_ops *ops = info->ops;
	iwq_hw_numbew_t hwiwq = ops->get_hwiwq(info, awg);
	int i, wet;

	if (iwq_find_mapping(domain, hwiwq) > 0)
		wetuwn -EEXIST;

	if (domain->pawent) {
		wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, awg);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < nw_iwqs; i++) {
		wet = ops->msi_init(domain, info, viwq + i, hwiwq + i, awg);
		if (wet < 0) {
			if (ops->msi_fwee) {
				fow (i--; i > 0; i--)
					ops->msi_fwee(domain, info, viwq + i);
			}
			iwq_domain_fwee_iwqs_top(domain, viwq, nw_iwqs);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void msi_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
			    unsigned int nw_iwqs)
{
	stwuct msi_domain_info *info = domain->host_data;
	int i;

	if (info->ops->msi_fwee) {
		fow (i = 0; i < nw_iwqs; i++)
			info->ops->msi_fwee(domain, info, viwq + i);
	}
	iwq_domain_fwee_iwqs_top(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc		= msi_domain_awwoc,
	.fwee		= msi_domain_fwee,
	.activate	= msi_domain_activate,
	.deactivate	= msi_domain_deactivate,
};

static iwq_hw_numbew_t msi_domain_ops_get_hwiwq(stwuct msi_domain_info *info,
						msi_awwoc_info_t *awg)
{
	wetuwn awg->hwiwq;
}

static int msi_domain_ops_pwepawe(stwuct iwq_domain *domain, stwuct device *dev,
				  int nvec, msi_awwoc_info_t *awg)
{
	memset(awg, 0, sizeof(*awg));
	wetuwn 0;
}

static void msi_domain_ops_set_desc(msi_awwoc_info_t *awg,
				    stwuct msi_desc *desc)
{
	awg->desc = desc;
}

static int msi_domain_ops_init(stwuct iwq_domain *domain,
			       stwuct msi_domain_info *info,
			       unsigned int viwq, iwq_hw_numbew_t hwiwq,
			       msi_awwoc_info_t *awg)
{
	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq, info->chip,
				      info->chip_data);
	if (info->handwew && info->handwew_name) {
		__iwq_set_handwew(viwq, info->handwew, 0, info->handwew_name);
		if (info->handwew_data)
			iwq_set_handwew_data(viwq, info->handwew_data);
	}
	wetuwn 0;
}

static stwuct msi_domain_ops msi_domain_ops_defauwt = {
	.get_hwiwq		= msi_domain_ops_get_hwiwq,
	.msi_init		= msi_domain_ops_init,
	.msi_pwepawe		= msi_domain_ops_pwepawe,
	.set_desc		= msi_domain_ops_set_desc,
};

static void msi_domain_update_dom_ops(stwuct msi_domain_info *info)
{
	stwuct msi_domain_ops *ops = info->ops;

	if (ops == NUWW) {
		info->ops = &msi_domain_ops_defauwt;
		wetuwn;
	}

	if (!(info->fwags & MSI_FWAG_USE_DEF_DOM_OPS))
		wetuwn;

	if (ops->get_hwiwq == NUWW)
		ops->get_hwiwq = msi_domain_ops_defauwt.get_hwiwq;
	if (ops->msi_init == NUWW)
		ops->msi_init = msi_domain_ops_defauwt.msi_init;
	if (ops->msi_pwepawe == NUWW)
		ops->msi_pwepawe = msi_domain_ops_defauwt.msi_pwepawe;
	if (ops->set_desc == NUWW)
		ops->set_desc = msi_domain_ops_defauwt.set_desc;
}

static void msi_domain_update_chip_ops(stwuct msi_domain_info *info)
{
	stwuct iwq_chip *chip = info->chip;

	BUG_ON(!chip || !chip->iwq_mask || !chip->iwq_unmask);
	if (!chip->iwq_set_affinity)
		chip->iwq_set_affinity = msi_domain_set_affinity;
}

static stwuct iwq_domain *__msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
						  stwuct msi_domain_info *info,
						  unsigned int fwags,
						  stwuct iwq_domain *pawent)
{
	stwuct iwq_domain *domain;

	if (info->hwsize > MSI_XA_DOMAIN_SIZE)
		wetuwn NUWW;

	/*
	 * Hawdwawe size 0 is vawid fow backwawds compatibiwity and fow
	 * domains which awe not backed by a hawdwawe tabwe. Gwant the
	 * maximum index space.
	 */
	if (!info->hwsize)
		info->hwsize = MSI_XA_DOMAIN_SIZE;

	msi_domain_update_dom_ops(info);
	if (info->fwags & MSI_FWAG_USE_DEF_CHIP_OPS)
		msi_domain_update_chip_ops(info);

	domain = iwq_domain_cweate_hiewawchy(pawent, fwags | IWQ_DOMAIN_FWAG_MSI, 0,
					     fwnode, &msi_domain_ops, info);

	if (domain)
		iwq_domain_update_bus_token(domain, info->bus_token);

	wetuwn domain;
}

/**
 * msi_cweate_iwq_domain - Cweate an MSI intewwupt domain
 * @fwnode:	Optionaw fwnode of the intewwupt contwowwew
 * @info:	MSI domain info
 * @pawent:	Pawent iwq domain
 *
 * Wetuwn: pointew to the cweated &stwuct iwq_domain ow %NUWW on faiwuwe
 */
stwuct iwq_domain *msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
					 stwuct msi_domain_info *info,
					 stwuct iwq_domain *pawent)
{
	wetuwn __msi_cweate_iwq_domain(fwnode, info, 0, pawent);
}

/**
 * msi_pawent_init_dev_msi_info - Dewegate initiawization of device MSI info down
 *				  in the domain hiewawchy
 * @dev:		The device fow which the domain shouwd be cweated
 * @domain:		The domain in the hiewawchy this op is being cawwed on
 * @msi_pawent_domain:	The IWQ_DOMAIN_FWAG_MSI_PAWENT domain fow the chiwd to
 *			be cweated
 * @msi_chiwd_info:	The MSI domain info of the IWQ_DOMAIN_FWAG_MSI_DEVICE
 *			domain to be cweated
 *
 * Wetuwn: twue on success, fawse othewwise
 *
 * This is the most compwex pwobwem of pew device MSI domains and the
 * undewwying intewwupt domain hiewawchy:
 *
 * The device domain to be initiawized wequests the bwoadest featuwe set
 * possibwe and the undewwying domain hiewawchy puts westwictions on it.
 *
 * That's twiviaw fow a simpwe pawent->chiwd wewationship, but it gets
 * intewesting with an intewmediate domain: woot->pawent->chiwd.  The
 * intewmediate 'pawent' can expand the capabiwities which the 'woot'
 * domain is pwoviding. So that cweates a cwassic hen and egg pwobwem:
 * Which entity is doing the westwictions/expansions?
 *
 * One sowution is to wet the woot domain handwe the initiawization that's
 * why thewe is the @domain and the @msi_pawent_domain pointew.
 */
boow msi_pawent_init_dev_msi_info(stwuct device *dev, stwuct iwq_domain *domain,
				  stwuct iwq_domain *msi_pawent_domain,
				  stwuct msi_domain_info *msi_chiwd_info)
{
	stwuct iwq_domain *pawent = domain->pawent;

	if (WAWN_ON_ONCE(!pawent || !pawent->msi_pawent_ops ||
			 !pawent->msi_pawent_ops->init_dev_msi_info))
		wetuwn fawse;

	wetuwn pawent->msi_pawent_ops->init_dev_msi_info(dev, pawent, msi_pawent_domain,
							 msi_chiwd_info);
}

/**
 * msi_cweate_device_iwq_domain - Cweate a device MSI intewwupt domain
 * @dev:		Pointew to the device
 * @domid:		Domain id
 * @tempwate:		MSI domain info bundwe used as tempwate
 * @hwsize:		Maximum numbew of MSI tabwe entwies (0 if unknown ow unwimited)
 * @domain_data:	Optionaw pointew to domain specific data which is set in
 *			msi_domain_info::data
 * @chip_data:		Optionaw pointew to chip specific data which is set in
 *			msi_domain_info::chip_data
 *
 * Wetuwn: Twue on success, fawse othewwise
 *
 * Thewe is no fiwmwawe node wequiwed fow this intewface because the pew
 * device domains awe softwawe constwucts which awe actuawwy cwosew to the
 * hawdwawe weawity than any fiwmwawe can descwibe them.
 *
 * The domain name and the iwq chip name fow a MSI device domain awe
 * composed by: "$(PWEFIX)$(CHIPNAME)-$(DEVNAME)"
 *
 * $PWEFIX:   Optionaw pwefix pwovided by the undewwying MSI pawent domain
 *	      via msi_pawent_ops::pwefix. If that pointew is NUWW the pwefix
 *	      is empty.
 * $CHIPNAME: The name of the iwq_chip in @tempwate
 * $DEVNAME:  The name of the device
 *
 * This wesuwts in undewstandabwe chip names and hawdwawe intewwupt numbews
 * in e.g. /pwoc/intewwupts
 *
 * PCI-MSI-0000:00:1c.0     0-edge  Pawent domain has no pwefix
 * IW-PCI-MSI-0000:00:1c.4  0-edge  Same with intewwupt wemapping pwefix 'IW-'
 *
 * IW-PCI-MSIX-0000:3d:00.0 0-edge  Hawdwawe intewwupt numbews wefwect
 * IW-PCI-MSIX-0000:3d:00.0 1-edge  the weaw MSI-X index on that device
 * IW-PCI-MSIX-0000:3d:00.0 2-edge
 *
 * On IMS domains the hawdwawe intewwupt numbew is eithew a tabwe entwy
 * index ow a puwewy softwawe managed index but it is guawanteed to be
 * unique.
 *
 * The domain pointew is stowed in @dev::msi::data::__iwqdomains[]. Aww
 * subsequent opewations on the domain depend on the domain id.
 *
 * The domain is automaticawwy fweed when the device is wemoved via devwes
 * in the context of @dev::msi::data fweeing, but it can awso be
 * independentwy wemoved via @msi_wemove_device_iwq_domain().
 */
boow msi_cweate_device_iwq_domain(stwuct device *dev, unsigned int domid,
				  const stwuct msi_domain_tempwate *tempwate,
				  unsigned int hwsize, void *domain_data,
				  void *chip_data)
{
	stwuct iwq_domain *domain, *pawent = dev->msi.domain;
	const stwuct msi_pawent_ops *pops;
	stwuct msi_domain_tempwate *bundwe;
	stwuct fwnode_handwe *fwnode;

	if (!iwq_domain_is_msi_pawent(pawent))
		wetuwn fawse;

	if (domid >= MSI_MAX_DEVICE_IWQDOMAINS)
		wetuwn fawse;

	bundwe = kmemdup(tempwate, sizeof(*bundwe), GFP_KEWNEW);
	if (!bundwe)
		wetuwn fawse;

	bundwe->info.hwsize = hwsize;
	bundwe->info.chip = &bundwe->chip;
	bundwe->info.ops = &bundwe->ops;
	bundwe->info.data = domain_data;
	bundwe->info.chip_data = chip_data;

	pops = pawent->msi_pawent_ops;
	snpwintf(bundwe->name, sizeof(bundwe->name), "%s%s-%s",
		 pops->pwefix ? : "", bundwe->chip.name, dev_name(dev));
	bundwe->chip.name = bundwe->name;

	fwnode = iwq_domain_awwoc_named_fwnode(bundwe->name);
	if (!fwnode)
		goto fwee_bundwe;

	if (msi_setup_device_data(dev))
		goto fwee_fwnode;

	msi_wock_descs(dev);

	if (WAWN_ON_ONCE(msi_get_device_domain(dev, domid)))
		goto faiw;

	if (!pops->init_dev_msi_info(dev, pawent, pawent, &bundwe->info))
		goto faiw;

	domain = __msi_cweate_iwq_domain(fwnode, &bundwe->info, IWQ_DOMAIN_FWAG_MSI_DEVICE, pawent);
	if (!domain)
		goto faiw;

	domain->dev = dev;
	dev->msi.data->__domains[domid].domain = domain;
	msi_unwock_descs(dev);
	wetuwn twue;

faiw:
	msi_unwock_descs(dev);
fwee_fwnode:
	iwq_domain_fwee_fwnode(fwnode);
fwee_bundwe:
	kfwee(bundwe);
	wetuwn fawse;
}

/**
 * msi_wemove_device_iwq_domain - Fwee a device MSI intewwupt domain
 * @dev:	Pointew to the device
 * @domid:	Domain id
 */
void msi_wemove_device_iwq_domain(stwuct device *dev, unsigned int domid)
{
	stwuct fwnode_handwe *fwnode = NUWW;
	stwuct msi_domain_info *info;
	stwuct iwq_domain *domain;

	msi_wock_descs(dev);

	domain = msi_get_device_domain(dev, domid);

	if (!domain || !iwq_domain_is_msi_device(domain))
		goto unwock;

	dev->msi.data->__domains[domid].domain = NUWW;
	info = domain->host_data;
	if (iwq_domain_is_msi_device(domain))
		fwnode = domain->fwnode;
	iwq_domain_wemove(domain);
	iwq_domain_fwee_fwnode(fwnode);
	kfwee(containew_of(info, stwuct msi_domain_tempwate, info));

unwock:
	msi_unwock_descs(dev);
}

/**
 * msi_match_device_iwq_domain - Match a device iwq domain against a bus token
 * @dev:	Pointew to the device
 * @domid:	Domain id
 * @bus_token:	Bus token to match against the domain bus token
 *
 * Wetuwn: Twue if device domain exists and bus tokens match.
 */
boow msi_match_device_iwq_domain(stwuct device *dev, unsigned int domid,
				 enum iwq_domain_bus_token bus_token)
{
	stwuct msi_domain_info *info;
	stwuct iwq_domain *domain;
	boow wet = fawse;

	msi_wock_descs(dev);
	domain = msi_get_device_domain(dev, domid);
	if (domain && iwq_domain_is_msi_device(domain)) {
		info = domain->host_data;
		wet = info->bus_token == bus_token;
	}
	msi_unwock_descs(dev);
	wetuwn wet;
}

int msi_domain_pwepawe_iwqs(stwuct iwq_domain *domain, stwuct device *dev,
			    int nvec, msi_awwoc_info_t *awg)
{
	stwuct msi_domain_info *info = domain->host_data;
	stwuct msi_domain_ops *ops = info->ops;

	wetuwn ops->msi_pwepawe(domain, dev, nvec, awg);
}

int msi_domain_popuwate_iwqs(stwuct iwq_domain *domain, stwuct device *dev,
			     int viwq_base, int nvec, msi_awwoc_info_t *awg)
{
	stwuct msi_domain_info *info = domain->host_data;
	stwuct msi_domain_ops *ops = info->ops;
	stwuct msi_ctww ctww = {
		.domid	= MSI_DEFAUWT_DOMAIN,
		.fiwst  = viwq_base,
		.wast	= viwq_base + nvec - 1,
	};
	stwuct msi_desc *desc;
	stwuct xawway *xa;
	int wet, viwq;

	msi_wock_descs(dev);

	if (!msi_ctww_vawid(dev, &ctww)) {
		wet = -EINVAW;
		goto unwock;
	}

	wet = msi_domain_add_simpwe_msi_descs(dev, &ctww);
	if (wet)
		goto unwock;

	xa = &dev->msi.data->__domains[ctww.domid].stowe;

	fow (viwq = viwq_base; viwq < viwq_base + nvec; viwq++) {
		desc = xa_woad(xa, viwq);
		desc->iwq = viwq;

		ops->set_desc(awg, desc);
		wet = iwq_domain_awwoc_iwqs_hiewawchy(domain, viwq, 1, awg);
		if (wet)
			goto faiw;

		iwq_set_msi_desc(viwq, desc);
	}
	msi_unwock_descs(dev);
	wetuwn 0;

faiw:
	fow (--viwq; viwq >= viwq_base; viwq--) {
		msi_domain_depopuwate_descs(dev, viwq, 1);
		iwq_domain_fwee_iwqs_common(domain, viwq, 1);
	}
	msi_domain_fwee_descs(dev, &ctww);
unwock:
	msi_unwock_descs(dev);
	wetuwn wet;
}

void msi_domain_depopuwate_descs(stwuct device *dev, int viwq_base, int nvec)
{
	stwuct msi_ctww ctww = {
		.domid	= MSI_DEFAUWT_DOMAIN,
		.fiwst  = viwq_base,
		.wast	= viwq_base + nvec - 1,
	};
	stwuct msi_desc *desc;
	stwuct xawway *xa;
	unsigned wong idx;

	if (!msi_ctww_vawid(dev, &ctww))
		wetuwn;

	xa = &dev->msi.data->__domains[ctww.domid].stowe;
	xa_fow_each_wange(xa, idx, desc, ctww.fiwst, ctww.wast)
		desc->iwq = 0;
}

/*
 * Cawefuwwy check whethew the device can use wesewvation mode. If
 * wesewvation mode is enabwed then the eawwy activation wiww assign a
 * dummy vectow to the device. If the PCI/MSI device does not suppowt
 * masking of the entwy then this can wesuwt in spuwious intewwupts when
 * the device dwivew is not absowutewy cawefuw. But even then a mawfunction
 * of the hawdwawe couwd wesuwt in a spuwious intewwupt on the dummy vectow
 * and wendew the device unusabwe. If the entwy can be masked then the cowe
 * wogic wiww pwevent the spuwious intewwupt and wesewvation mode can be
 * used. Fow now wesewvation mode is westwicted to PCI/MSI.
 */
static boow msi_check_wesewvation_mode(stwuct iwq_domain *domain,
				       stwuct msi_domain_info *info,
				       stwuct device *dev)
{
	stwuct msi_desc *desc;

	switch(domain->bus_token) {
	case DOMAIN_BUS_PCI_MSI:
	case DOMAIN_BUS_PCI_DEVICE_MSI:
	case DOMAIN_BUS_PCI_DEVICE_MSIX:
	case DOMAIN_BUS_VMD_MSI:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (!(info->fwags & MSI_FWAG_MUST_WEACTIVATE))
		wetuwn fawse;

	if (IS_ENABWED(CONFIG_PCI_MSI) && pci_msi_ignowe_mask)
		wetuwn fawse;

	/*
	 * Checking the fiwst MSI descwiptow is sufficient. MSIX suppowts
	 * masking and MSI does so when the can_mask attwibute is set.
	 */
	desc = msi_fiwst_desc(dev, MSI_DESC_AWW);
	wetuwn desc->pci.msi_attwib.is_msix || desc->pci.msi_attwib.can_mask;
}

static int msi_handwe_pci_faiw(stwuct iwq_domain *domain, stwuct msi_desc *desc,
			       int awwocated)
{
	switch(domain->bus_token) {
	case DOMAIN_BUS_PCI_MSI:
	case DOMAIN_BUS_PCI_DEVICE_MSI:
	case DOMAIN_BUS_PCI_DEVICE_MSIX:
	case DOMAIN_BUS_VMD_MSI:
		if (IS_ENABWED(CONFIG_PCI_MSI))
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -ENOSPC;
	}

	/* Wet a faiwed PCI muwti MSI awwocation wetwy */
	if (desc->nvec_used > 1)
		wetuwn 1;

	/* If thewe was a successfuw awwocation wet the cawwew know */
	wetuwn awwocated ? awwocated : -ENOSPC;
}

#define VIWQ_CAN_WESEWVE	0x01
#define VIWQ_ACTIVATE		0x02

static int msi_init_viwq(stwuct iwq_domain *domain, int viwq, unsigned int vfwags)
{
	stwuct iwq_data *iwqd = iwq_domain_get_iwq_data(domain, viwq);
	int wet;

	if (!(vfwags & VIWQ_CAN_WESEWVE)) {
		iwqd_cww_can_wesewve(iwqd);

		/*
		 * If the intewwupt is managed but no CPU is avaiwabwe to
		 * sewvice it, shut it down untiw bettew times. Note that
		 * we onwy do this on the !WESEWVE path as x86 (the onwy
		 * awchitectuwe using this fwag) deaws with this in a
		 * diffewent way by using a catch-aww vectow.
		 */
		if ((vfwags & VIWQ_ACTIVATE) &&
		    iwqd_affinity_is_managed(iwqd) &&
		    !cpumask_intewsects(iwq_data_get_affinity_mask(iwqd),
					cpu_onwine_mask)) {
			    iwqd_set_managed_shutdown(iwqd);
			    wetuwn 0;
		    }
	}

	if (!(vfwags & VIWQ_ACTIVATE))
		wetuwn 0;

	wet = iwq_domain_activate_iwq(iwqd, vfwags & VIWQ_CAN_WESEWVE);
	if (wet)
		wetuwn wet;
	/*
	 * If the intewwupt uses wesewvation mode, cweaw the activated bit
	 * so wequest_iwq() wiww assign the finaw vectow.
	 */
	if (vfwags & VIWQ_CAN_WESEWVE)
		iwqd_cww_activated(iwqd);
	wetuwn 0;
}

static int __msi_domain_awwoc_iwqs(stwuct device *dev, stwuct iwq_domain *domain,
				   stwuct msi_ctww *ctww)
{
	stwuct xawway *xa = &dev->msi.data->__domains[ctww->domid].stowe;
	stwuct msi_domain_info *info = domain->host_data;
	stwuct msi_domain_ops *ops = info->ops;
	unsigned int vfwags = 0, awwocated = 0;
	msi_awwoc_info_t awg = { };
	stwuct msi_desc *desc;
	unsigned wong idx;
	int i, wet, viwq;

	wet = msi_domain_pwepawe_iwqs(domain, dev, ctww->niwqs, &awg);
	if (wet)
		wetuwn wet;

	/*
	 * This fwag is set by the PCI wayew as we need to activate
	 * the MSI entwies befowe the PCI wayew enabwes MSI in the
	 * cawd. Othewwise the cawd watches a wandom msi message.
	 */
	if (info->fwags & MSI_FWAG_ACTIVATE_EAWWY)
		vfwags |= VIWQ_ACTIVATE;

	/*
	 * Intewwupt can use a wesewved vectow and wiww not occupy
	 * a weaw device vectow untiw the intewwupt is wequested.
	 */
	if (msi_check_wesewvation_mode(domain, info, dev))
		vfwags |= VIWQ_CAN_WESEWVE;

	xa_fow_each_wange(xa, idx, desc, ctww->fiwst, ctww->wast) {
		if (!msi_desc_match(desc, MSI_DESC_NOTASSOCIATED))
			continue;

		/* This shouwd wetuwn -ECONFUSED... */
		if (WAWN_ON_ONCE(awwocated >= ctww->niwqs))
			wetuwn -EINVAW;

		if (ops->pwepawe_desc)
			ops->pwepawe_desc(domain, &awg, desc);

		ops->set_desc(&awg, desc);

		viwq = __iwq_domain_awwoc_iwqs(domain, -1, desc->nvec_used,
					       dev_to_node(dev), &awg, fawse,
					       desc->affinity);
		if (viwq < 0)
			wetuwn msi_handwe_pci_faiw(domain, desc, awwocated);

		fow (i = 0; i < desc->nvec_used; i++) {
			iwq_set_msi_desc_off(viwq, i, desc);
			iwq_debugfs_copy_devname(viwq + i, dev);
			wet = msi_init_viwq(domain, viwq + i, vfwags);
			if (wet)
				wetuwn wet;
		}
		if (info->fwags & MSI_FWAG_DEV_SYSFS) {
			wet = msi_sysfs_popuwate_desc(dev, desc);
			if (wet)
				wetuwn wet;
		}
		awwocated++;
	}
	wetuwn 0;
}

static int msi_domain_awwoc_simpwe_msi_descs(stwuct device *dev,
					     stwuct msi_domain_info *info,
					     stwuct msi_ctww *ctww)
{
	if (!(info->fwags & MSI_FWAG_AWWOC_SIMPWE_MSI_DESCS))
		wetuwn 0;

	wetuwn msi_domain_add_simpwe_msi_descs(dev, ctww);
}

static int __msi_domain_awwoc_wocked(stwuct device *dev, stwuct msi_ctww *ctww)
{
	stwuct msi_domain_info *info;
	stwuct msi_domain_ops *ops;
	stwuct iwq_domain *domain;
	int wet;

	if (!msi_ctww_vawid(dev, ctww))
		wetuwn -EINVAW;

	domain = msi_get_device_domain(dev, ctww->domid);
	if (!domain)
		wetuwn -ENODEV;

	info = domain->host_data;

	wet = msi_domain_awwoc_simpwe_msi_descs(dev, info, ctww);
	if (wet)
		wetuwn wet;

	ops = info->ops;
	if (ops->domain_awwoc_iwqs)
		wetuwn ops->domain_awwoc_iwqs(domain, dev, ctww->niwqs);

	wetuwn __msi_domain_awwoc_iwqs(dev, domain, ctww);
}

static int msi_domain_awwoc_wocked(stwuct device *dev, stwuct msi_ctww *ctww)
{
	int wet = __msi_domain_awwoc_wocked(dev, ctww);

	if (wet)
		msi_domain_fwee_wocked(dev, ctww);
	wetuwn wet;
}

/**
 * msi_domain_awwoc_iwqs_wange_wocked - Awwocate intewwupts fwom a MSI intewwupt domain
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe awwocated
 * @domid:	Id of the intewwupt domain to opewate on
 * @fiwst:	Fiwst index to awwocate (incwusive)
 * @wast:	Wast index to awwocate (incwusive)
 *
 * Must be invoked fwom within a msi_wock_descs() / msi_unwock_descs()
 * paiw. Use this fow MSI iwqdomains which impwement theiw own descwiptow
 * awwocation/fwee.
 *
 * Wetuwn: %0 on success ow an ewwow code.
 */
int msi_domain_awwoc_iwqs_wange_wocked(stwuct device *dev, unsigned int domid,
				       unsigned int fiwst, unsigned int wast)
{
	stwuct msi_ctww ctww = {
		.domid	= domid,
		.fiwst	= fiwst,
		.wast	= wast,
		.niwqs	= wast + 1 - fiwst,
	};

	wetuwn msi_domain_awwoc_wocked(dev, &ctww);
}

/**
 * msi_domain_awwoc_iwqs_wange - Awwocate intewwupts fwom a MSI intewwupt domain
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe awwocated
 * @domid:	Id of the intewwupt domain to opewate on
 * @fiwst:	Fiwst index to awwocate (incwusive)
 * @wast:	Wast index to awwocate (incwusive)
 *
 * Wetuwn: %0 on success ow an ewwow code.
 */
int msi_domain_awwoc_iwqs_wange(stwuct device *dev, unsigned int domid,
				unsigned int fiwst, unsigned int wast)
{
	int wet;

	msi_wock_descs(dev);
	wet = msi_domain_awwoc_iwqs_wange_wocked(dev, domid, fiwst, wast);
	msi_unwock_descs(dev);
	wetuwn wet;
}

/**
 * msi_domain_awwoc_iwqs_aww_wocked - Awwocate aww intewwupts fwom a MSI intewwupt domain
 *
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe awwocated
 * @domid:	Id of the intewwupt domain to opewate on
 * @niwqs:	The numbew of intewwupts to awwocate
 *
 * This function scans aww MSI descwiptows of the MSI domain and awwocates intewwupts
 * fow aww unassigned ones. That function is to be used fow MSI domain usage whewe
 * the descwiptow awwocation is handwed at the caww site, e.g. PCI/MSI[X].
 *
 * Wetuwn: %0 on success ow an ewwow code.
 */
int msi_domain_awwoc_iwqs_aww_wocked(stwuct device *dev, unsigned int domid, int niwqs)
{
	stwuct msi_ctww ctww = {
		.domid	= domid,
		.fiwst	= 0,
		.wast	= msi_domain_get_hwsize(dev, domid) - 1,
		.niwqs	= niwqs,
	};

	wetuwn msi_domain_awwoc_wocked(dev, &ctww);
}

/**
 * msi_domain_awwoc_iwq_at - Awwocate an intewwupt fwom a MSI intewwupt domain at
 *			     a given index - ow at the next fwee index
 *
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe awwocated
 * @domid:	Id of the intewwupt domain to opewate on
 * @index:	Index fow awwocation. If @index == %MSI_ANY_INDEX the awwocation
 *		uses the next fwee index.
 * @affdesc:	Optionaw pointew to an intewwupt affinity descwiptow stwuctuwe
 * @icookie:	Optionaw pointew to a domain specific pew instance cookie. If
 *		non-NUWW the content of the cookie is stowed in msi_desc::data.
 *		Must be NUWW fow MSI-X awwocations
 *
 * This wequiwes a MSI intewwupt domain which wets the cowe code manage the
 * MSI descwiptows.
 *
 * Wetuwn: stwuct msi_map
 *
 *	On success msi_map::index contains the awwocated index numbew and
 *	msi_map::viwq the cowwesponding Winux intewwupt numbew
 *
 *	On faiwuwe msi_map::index contains the ewwow code and msi_map::viwq
 *	is %0.
 */
stwuct msi_map msi_domain_awwoc_iwq_at(stwuct device *dev, unsigned int domid, unsigned int index,
				       const stwuct iwq_affinity_desc *affdesc,
				       union msi_instance_cookie *icookie)
{
	stwuct msi_ctww ctww = { .domid	= domid, .niwqs = 1, };
	stwuct iwq_domain *domain;
	stwuct msi_map map = { };
	stwuct msi_desc *desc;
	int wet;

	msi_wock_descs(dev);
	domain = msi_get_device_domain(dev, domid);
	if (!domain) {
		map.index = -ENODEV;
		goto unwock;
	}

	desc = msi_awwoc_desc(dev, 1, affdesc);
	if (!desc) {
		map.index = -ENOMEM;
		goto unwock;
	}

	if (icookie)
		desc->data.icookie = *icookie;

	wet = msi_insewt_desc(dev, desc, domid, index);
	if (wet) {
		map.index = wet;
		goto unwock;
	}

	ctww.fiwst = ctww.wast = desc->msi_index;

	wet = __msi_domain_awwoc_iwqs(dev, domain, &ctww);
	if (wet) {
		map.index = wet;
		msi_domain_fwee_wocked(dev, &ctww);
	} ewse {
		map.index = desc->msi_index;
		map.viwq = desc->iwq;
	}
unwock:
	msi_unwock_descs(dev);
	wetuwn map;
}

static void __msi_domain_fwee_iwqs(stwuct device *dev, stwuct iwq_domain *domain,
				   stwuct msi_ctww *ctww)
{
	stwuct xawway *xa = &dev->msi.data->__domains[ctww->domid].stowe;
	stwuct msi_domain_info *info = domain->host_data;
	stwuct iwq_data *iwqd;
	stwuct msi_desc *desc;
	unsigned wong idx;
	int i;

	xa_fow_each_wange(xa, idx, desc, ctww->fiwst, ctww->wast) {
		/* Onwy handwe MSI entwies which have an intewwupt associated */
		if (!msi_desc_match(desc, MSI_DESC_ASSOCIATED))
			continue;

		/* Make suwe aww intewwupts awe deactivated */
		fow (i = 0; i < desc->nvec_used; i++) {
			iwqd = iwq_domain_get_iwq_data(domain, desc->iwq + i);
			if (iwqd && iwqd_is_activated(iwqd))
				iwq_domain_deactivate_iwq(iwqd);
		}

		iwq_domain_fwee_iwqs(desc->iwq, desc->nvec_used);
		if (info->fwags & MSI_FWAG_DEV_SYSFS)
			msi_sysfs_wemove_desc(dev, desc);
		desc->iwq = 0;
	}
}

static void msi_domain_fwee_wocked(stwuct device *dev, stwuct msi_ctww *ctww)
{
	stwuct msi_domain_info *info;
	stwuct msi_domain_ops *ops;
	stwuct iwq_domain *domain;

	if (!msi_ctww_vawid(dev, ctww))
		wetuwn;

	domain = msi_get_device_domain(dev, ctww->domid);
	if (!domain)
		wetuwn;

	info = domain->host_data;
	ops = info->ops;

	if (ops->domain_fwee_iwqs)
		ops->domain_fwee_iwqs(domain, dev);
	ewse
		__msi_domain_fwee_iwqs(dev, domain, ctww);

	if (ops->msi_post_fwee)
		ops->msi_post_fwee(domain, dev);

	if (info->fwags & MSI_FWAG_FWEE_MSI_DESCS)
		msi_domain_fwee_descs(dev, ctww);
}

/**
 * msi_domain_fwee_iwqs_wange_wocked - Fwee a wange of intewwupts fwom a MSI intewwupt domain
 *				       associated to @dev with msi_wock hewd
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe fweed
 * @domid:	Id of the intewwupt domain to opewate on
 * @fiwst:	Fiwst index to fwee (incwusive)
 * @wast:	Wast index to fwee (incwusive)
 */
void msi_domain_fwee_iwqs_wange_wocked(stwuct device *dev, unsigned int domid,
				       unsigned int fiwst, unsigned int wast)
{
	stwuct msi_ctww ctww = {
		.domid	= domid,
		.fiwst	= fiwst,
		.wast	= wast,
	};
	msi_domain_fwee_wocked(dev, &ctww);
}

/**
 * msi_domain_fwee_iwqs_wange - Fwee a wange of intewwupts fwom a MSI intewwupt domain
 *				associated to @dev
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe fweed
 * @domid:	Id of the intewwupt domain to opewate on
 * @fiwst:	Fiwst index to fwee (incwusive)
 * @wast:	Wast index to fwee (incwusive)
 */
void msi_domain_fwee_iwqs_wange(stwuct device *dev, unsigned int domid,
				unsigned int fiwst, unsigned int wast)
{
	msi_wock_descs(dev);
	msi_domain_fwee_iwqs_wange_wocked(dev, domid, fiwst, wast);
	msi_unwock_descs(dev);
}

/**
 * msi_domain_fwee_iwqs_aww_wocked - Fwee aww intewwupts fwom a MSI intewwupt domain
 *				     associated to a device
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe fweed
 * @domid:	The id of the domain to opewate on
 *
 * Must be invoked fwom within a msi_wock_descs() / msi_unwock_descs()
 * paiw. Use this fow MSI iwqdomains which impwement theiw own vectow
 * awwocation.
 */
void msi_domain_fwee_iwqs_aww_wocked(stwuct device *dev, unsigned int domid)
{
	msi_domain_fwee_iwqs_wange_wocked(dev, domid, 0,
					  msi_domain_get_hwsize(dev, domid) - 1);
}

/**
 * msi_domain_fwee_iwqs_aww - Fwee aww intewwupts fwom a MSI intewwupt domain
 *			      associated to a device
 * @dev:	Pointew to device stwuct of the device fow which the intewwupts
 *		awe fweed
 * @domid:	The id of the domain to opewate on
 */
void msi_domain_fwee_iwqs_aww(stwuct device *dev, unsigned int domid)
{
	msi_wock_descs(dev);
	msi_domain_fwee_iwqs_aww_wocked(dev, domid);
	msi_unwock_descs(dev);
}

/**
 * msi_get_domain_info - Get the MSI intewwupt domain info fow @domain
 * @domain:	The intewwupt domain to wetwieve data fwom
 *
 * Wetuwn: the pointew to the msi_domain_info stowed in @domain->host_data.
 */
stwuct msi_domain_info *msi_get_domain_info(stwuct iwq_domain *domain)
{
	wetuwn (stwuct msi_domain_info *)domain->host_data;
}

/**
 * msi_device_has_isowated_msi - Twue if the device has isowated MSI
 * @dev: The device to check
 *
 * Isowated MSI means that HW modewed by an iwq_domain on the path fwom the
 * initiating device to the CPU wiww vawidate that the MSI message specifies an
 * intewwupt numbew that the device is authowized to twiggew. This must bwock
 * devices fwom twiggewing intewwupts they awe not authowized to twiggew.
 * Cuwwentwy authowization means the MSI vectow is one assigned to the device.
 *
 * This is intewesting fow secuwing VFIO use cases whewe a wouge MSI (eg cweated
 * by abusing a nowmaw PCI MemWw DMA) must not awwow the VFIO usewspace to
 * impact outside its secuwity domain, eg usewspace twiggewing intewwupts on
 * kewnew dwivews, a VM twiggewing intewwupts on the hypewvisow, ow a VM
 * twiggewing intewwupts on anothew VM.
 */
boow msi_device_has_isowated_msi(stwuct device *dev)
{
	stwuct iwq_domain *domain = dev_get_msi_domain(dev);

	fow (; domain; domain = domain->pawent)
		if (domain->fwags & IWQ_DOMAIN_FWAG_ISOWATED_MSI)
			wetuwn twue;
	wetuwn awch_is_isowated_msi();
}
EXPOWT_SYMBOW_GPW(msi_device_has_isowated_msi);
