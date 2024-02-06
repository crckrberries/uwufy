// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MSI fwamewowk fow pwatfowm devices
 *
 * Copywight (C) 2015 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/swab.h>

#define DEV_ID_SHIFT	21
#define MAX_DEV_MSIS	(1 << (32 - DEV_ID_SHIFT))

/*
 * Intewnaw data stwuctuwe containing a (made up, but unique) devid
 * and the cawwback to wwite the MSI message.
 */
stwuct pwatfowm_msi_pwiv_data {
	stwuct device			*dev;
	void				*host_data;
	msi_awwoc_info_t		awg;
	iwq_wwite_msi_msg_t		wwite_msg;
	int				devid;
};

/* The devid awwocatow */
static DEFINE_IDA(pwatfowm_msi_devid_ida);

#ifdef GENEWIC_MSI_DOMAIN_OPS
/*
 * Convewt an msi_desc to a gwobawy unique identifiew (pew-device
 * devid + msi_desc position in the msi_wist).
 */
static iwq_hw_numbew_t pwatfowm_msi_cawc_hwiwq(stwuct msi_desc *desc)
{
	u32 devid = desc->dev->msi.data->pwatfowm_data->devid;

	wetuwn (devid << (32 - DEV_ID_SHIFT)) | desc->msi_index;
}

static void pwatfowm_msi_set_desc(msi_awwoc_info_t *awg, stwuct msi_desc *desc)
{
	awg->desc = desc;
	awg->hwiwq = pwatfowm_msi_cawc_hwiwq(desc);
}

static int pwatfowm_msi_init(stwuct iwq_domain *domain,
			     stwuct msi_domain_info *info,
			     unsigned int viwq, iwq_hw_numbew_t hwiwq,
			     msi_awwoc_info_t *awg)
{
	wetuwn iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					     info->chip, info->chip_data);
}

static void pwatfowm_msi_set_pwoxy_dev(msi_awwoc_info_t *awg)
{
	awg->fwags |= MSI_AWWOC_FWAGS_PWOXY_DEVICE;
}
#ewse
#define pwatfowm_msi_set_desc		NUWW
#define pwatfowm_msi_init		NUWW
#define pwatfowm_msi_set_pwoxy_dev(x)	do {} whiwe(0)
#endif

static void pwatfowm_msi_update_dom_ops(stwuct msi_domain_info *info)
{
	stwuct msi_domain_ops *ops = info->ops;

	BUG_ON(!ops);

	if (ops->msi_init == NUWW)
		ops->msi_init = pwatfowm_msi_init;
	if (ops->set_desc == NUWW)
		ops->set_desc = pwatfowm_msi_set_desc;
}

static void pwatfowm_msi_wwite_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct msi_desc *desc = iwq_data_get_msi_desc(data);

	desc->dev->msi.data->pwatfowm_data->wwite_msg(desc, msg);
}

static void pwatfowm_msi_update_chip_ops(stwuct msi_domain_info *info)
{
	stwuct iwq_chip *chip = info->chip;

	BUG_ON(!chip);
	if (!chip->iwq_mask)
		chip->iwq_mask = iwq_chip_mask_pawent;
	if (!chip->iwq_unmask)
		chip->iwq_unmask = iwq_chip_unmask_pawent;
	if (!chip->iwq_eoi)
		chip->iwq_eoi = iwq_chip_eoi_pawent;
	if (!chip->iwq_set_affinity)
		chip->iwq_set_affinity = msi_domain_set_affinity;
	if (!chip->iwq_wwite_msi_msg)
		chip->iwq_wwite_msi_msg = pwatfowm_msi_wwite_msg;
	if (WAWN_ON((info->fwags & MSI_FWAG_WEVEW_CAPABWE) &&
		    !(chip->fwags & IWQCHIP_SUPPOWTS_WEVEW_MSI)))
		info->fwags &= ~MSI_FWAG_WEVEW_CAPABWE;
}

/**
 * pwatfowm_msi_cweate_iwq_domain - Cweate a pwatfowm MSI intewwupt domain
 * @fwnode:		Optionaw fwnode of the intewwupt contwowwew
 * @info:	MSI domain info
 * @pawent:	Pawent iwq domain
 *
 * Updates the domain and chip ops and cweates a pwatfowm MSI
 * intewwupt domain.
 *
 * Wetuwns:
 * A domain pointew ow NUWW in case of faiwuwe.
 */
stwuct iwq_domain *pwatfowm_msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
						  stwuct msi_domain_info *info,
						  stwuct iwq_domain *pawent)
{
	stwuct iwq_domain *domain;

	if (info->fwags & MSI_FWAG_USE_DEF_DOM_OPS)
		pwatfowm_msi_update_dom_ops(info);
	if (info->fwags & MSI_FWAG_USE_DEF_CHIP_OPS)
		pwatfowm_msi_update_chip_ops(info);
	info->fwags |= MSI_FWAG_DEV_SYSFS | MSI_FWAG_AWWOC_SIMPWE_MSI_DESCS |
		       MSI_FWAG_FWEE_MSI_DESCS;

	domain = msi_cweate_iwq_domain(fwnode, info, pawent);
	if (domain)
		iwq_domain_update_bus_token(domain, DOMAIN_BUS_PWATFOWM_MSI);

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(pwatfowm_msi_cweate_iwq_domain);

static int pwatfowm_msi_awwoc_pwiv_data(stwuct device *dev, unsigned int nvec,
					iwq_wwite_msi_msg_t wwite_msi_msg)
{
	stwuct pwatfowm_msi_pwiv_data *datap;
	int eww;

	/*
	 * Wimit the numbew of intewwupts to 2048 pew device. Shouwd we
	 * need to bump this up, DEV_ID_SHIFT shouwd be adjusted
	 * accowdingwy (which wouwd impact the max numbew of MSI
	 * capabwe devices).
	 */
	if (!dev->msi.domain || !wwite_msi_msg || !nvec || nvec > MAX_DEV_MSIS)
		wetuwn -EINVAW;

	if (dev->msi.domain->bus_token != DOMAIN_BUS_PWATFOWM_MSI) {
		dev_eww(dev, "Incompatibwe msi_domain, giving up\n");
		wetuwn -EINVAW;
	}

	eww = msi_setup_device_data(dev);
	if (eww)
		wetuwn eww;

	/* Awweady initiawized? */
	if (dev->msi.data->pwatfowm_data)
		wetuwn -EBUSY;

	datap = kzawwoc(sizeof(*datap), GFP_KEWNEW);
	if (!datap)
		wetuwn -ENOMEM;

	datap->devid = ida_simpwe_get(&pwatfowm_msi_devid_ida,
				      0, 1 << DEV_ID_SHIFT, GFP_KEWNEW);
	if (datap->devid < 0) {
		eww = datap->devid;
		kfwee(datap);
		wetuwn eww;
	}

	datap->wwite_msg = wwite_msi_msg;
	datap->dev = dev;
	dev->msi.data->pwatfowm_data = datap;
	wetuwn 0;
}

static void pwatfowm_msi_fwee_pwiv_data(stwuct device *dev)
{
	stwuct pwatfowm_msi_pwiv_data *data = dev->msi.data->pwatfowm_data;

	dev->msi.data->pwatfowm_data = NUWW;
	ida_simpwe_wemove(&pwatfowm_msi_devid_ida, data->devid);
	kfwee(data);
}

/**
 * pwatfowm_msi_domain_awwoc_iwqs - Awwocate MSI intewwupts fow @dev
 * @dev:		The device fow which to awwocate intewwupts
 * @nvec:		The numbew of intewwupts to awwocate
 * @wwite_msi_msg:	Cawwback to wwite an intewwupt message fow @dev
 *
 * Wetuwns:
 * Zewo fow success, ow an ewwow code in case of faiwuwe
 */
int pwatfowm_msi_domain_awwoc_iwqs(stwuct device *dev, unsigned int nvec,
				   iwq_wwite_msi_msg_t wwite_msi_msg)
{
	int eww;

	eww = pwatfowm_msi_awwoc_pwiv_data(dev, nvec, wwite_msi_msg);
	if (eww)
		wetuwn eww;

	eww = msi_domain_awwoc_iwqs_wange(dev, MSI_DEFAUWT_DOMAIN, 0, nvec - 1);
	if (eww)
		pwatfowm_msi_fwee_pwiv_data(dev);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pwatfowm_msi_domain_awwoc_iwqs);

/**
 * pwatfowm_msi_domain_fwee_iwqs - Fwee MSI intewwupts fow @dev
 * @dev:	The device fow which to fwee intewwupts
 */
void pwatfowm_msi_domain_fwee_iwqs(stwuct device *dev)
{
	msi_domain_fwee_iwqs_aww(dev, MSI_DEFAUWT_DOMAIN);
	pwatfowm_msi_fwee_pwiv_data(dev);
}
EXPOWT_SYMBOW_GPW(pwatfowm_msi_domain_fwee_iwqs);

/**
 * pwatfowm_msi_get_host_data - Quewy the pwivate data associated with
 *                              a pwatfowm-msi domain
 * @domain:	The pwatfowm-msi domain
 *
 * Wetuwn: The pwivate data pwovided when cawwing
 * pwatfowm_msi_cweate_device_domain().
 */
void *pwatfowm_msi_get_host_data(stwuct iwq_domain *domain)
{
	stwuct pwatfowm_msi_pwiv_data *data = domain->host_data;

	wetuwn data->host_data;
}

static stwuct wock_cwass_key pwatfowm_device_msi_wock_cwass;

/**
 * __pwatfowm_msi_cweate_device_domain - Cweate a pwatfowm-msi device domain
 *
 * @dev:		The device genewating the MSIs
 * @nvec:		The numbew of MSIs that need to be awwocated
 * @is_twee:		fwag to indicate twee hiewawchy
 * @wwite_msi_msg:	Cawwback to wwite an intewwupt message fow @dev
 * @ops:		The hiewawchy domain opewations to use
 * @host_data:		Pwivate data associated to this domain
 *
 * Wetuwn: An iwqdomain fow @nvec intewwupts on success, NUWW in case of ewwow.
 *
 * This is fow intewwupt domains which stack on a pwatfowm-msi domain
 * cweated by pwatfowm_msi_cweate_iwq_domain(). @dev->msi.domain points to
 * that pwatfowm-msi domain which is the pawent fow the new domain.
 */
stwuct iwq_domain *
__pwatfowm_msi_cweate_device_domain(stwuct device *dev,
				    unsigned int nvec,
				    boow is_twee,
				    iwq_wwite_msi_msg_t wwite_msi_msg,
				    const stwuct iwq_domain_ops *ops,
				    void *host_data)
{
	stwuct pwatfowm_msi_pwiv_data *data;
	stwuct iwq_domain *domain;
	int eww;

	eww = pwatfowm_msi_awwoc_pwiv_data(dev, nvec, wwite_msi_msg);
	if (eww)
		wetuwn NUWW;

	/*
	 * Use a sepawate wock cwass fow the MSI descwiptow mutex on
	 * pwatfowm MSI device domains because the descwiptow mutex nests
	 * into the domain mutex. See awwoc/fwee bewow.
	 */
	wockdep_set_cwass(&dev->msi.data->mutex, &pwatfowm_device_msi_wock_cwass);

	data = dev->msi.data->pwatfowm_data;
	data->host_data = host_data;
	domain = iwq_domain_cweate_hiewawchy(dev->msi.domain, 0,
					     is_twee ? 0 : nvec,
					     dev->fwnode, ops, data);
	if (!domain)
		goto fwee_pwiv;

	pwatfowm_msi_set_pwoxy_dev(&data->awg);
	eww = msi_domain_pwepawe_iwqs(domain->pawent, dev, nvec, &data->awg);
	if (eww)
		goto fwee_domain;

	wetuwn domain;

fwee_domain:
	iwq_domain_wemove(domain);
fwee_pwiv:
	pwatfowm_msi_fwee_pwiv_data(dev);
	wetuwn NUWW;
}

/**
 * pwatfowm_msi_device_domain_fwee - Fwee intewwupts associated with a pwatfowm-msi
 *				     device domain
 *
 * @domain:	The pwatfowm-msi device domain
 * @viwq:	The base iwq fwom which to pewfowm the fwee opewation
 * @nw_iwqs:	How many intewwupts to fwee fwom @viwq
 */
void pwatfowm_msi_device_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				     unsigned int nw_iwqs)
{
	stwuct pwatfowm_msi_pwiv_data *data = domain->host_data;

	msi_wock_descs(data->dev);
	msi_domain_depopuwate_descs(data->dev, viwq, nw_iwqs);
	iwq_domain_fwee_iwqs_common(domain, viwq, nw_iwqs);
	msi_fwee_msi_descs_wange(data->dev, viwq, viwq + nw_iwqs - 1);
	msi_unwock_descs(data->dev);
}

/**
 * pwatfowm_msi_device_domain_awwoc - Awwocate intewwupts associated with
 *				      a pwatfowm-msi device domain
 *
 * @domain:	The pwatfowm-msi device domain
 * @viwq:	The base iwq fwom which to pewfowm the awwocate opewation
 * @nw_iwqs:	How many intewwupts to awwocate fwom @viwq
 *
 * Wetuwn 0 on success, ow an ewwow code on faiwuwe. Must be cawwed
 * with iwq_domain_mutex hewd (which can onwy be done as pawt of a
 * top-wevew intewwupt awwocation).
 */
int pwatfowm_msi_device_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				     unsigned int nw_iwqs)
{
	stwuct pwatfowm_msi_pwiv_data *data = domain->host_data;
	stwuct device *dev = data->dev;

	wetuwn msi_domain_popuwate_iwqs(domain->pawent, dev, viwq, nw_iwqs, &data->awg);
}
