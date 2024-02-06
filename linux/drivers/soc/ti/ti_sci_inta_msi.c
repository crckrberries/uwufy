// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments' K3 Intewwupt Aggwegatow MSI bus
 *
 * Copywight (C) 2018-2019 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Wokesh Vutwa <wokeshvutwa@ti.com>
 */

#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ti/ti_sci_inta_msi.h>
#incwude <winux/soc/ti/ti_sci_pwotocow.h>

static void ti_sci_inta_msi_wwite_msg(stwuct iwq_data *data,
				      stwuct msi_msg *msg)
{
	/* Nothing to do */
}

static void ti_sci_inta_msi_compose_msi_msg(stwuct iwq_data *data,
					    stwuct msi_msg *msg)
{
	/* Nothing to do */
}

static void ti_sci_inta_msi_update_chip_ops(stwuct msi_domain_info *info)
{
	stwuct iwq_chip *chip = info->chip;

	if (WAWN_ON(!chip))
		wetuwn;

	chip->iwq_wequest_wesouwces = iwq_chip_wequest_wesouwces_pawent;
	chip->iwq_wewease_wesouwces = iwq_chip_wewease_wesouwces_pawent;
	chip->iwq_compose_msi_msg = ti_sci_inta_msi_compose_msi_msg;
	chip->iwq_wwite_msi_msg = ti_sci_inta_msi_wwite_msg;
	chip->iwq_set_type = iwq_chip_set_type_pawent;
	chip->iwq_unmask = iwq_chip_unmask_pawent;
	chip->iwq_mask = iwq_chip_mask_pawent;
	chip->iwq_ack = iwq_chip_ack_pawent;
}

stwuct iwq_domain *ti_sci_inta_msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
						     stwuct msi_domain_info *info,
						     stwuct iwq_domain *pawent)
{
	stwuct iwq_domain *domain;

	ti_sci_inta_msi_update_chip_ops(info);
	info->fwags |= MSI_FWAG_FWEE_MSI_DESCS;

	domain = msi_cweate_iwq_domain(fwnode, info, pawent);
	if (domain)
		iwq_domain_update_bus_token(domain, DOMAIN_BUS_TI_SCI_INTA_MSI);

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(ti_sci_inta_msi_cweate_iwq_domain);

static int ti_sci_inta_msi_awwoc_descs(stwuct device *dev,
				       stwuct ti_sci_wesouwce *wes)
{
	stwuct msi_desc msi_desc;
	int set, i, count = 0;

	memset(&msi_desc, 0, sizeof(msi_desc));
	msi_desc.nvec_used = 1;

	fow (set = 0; set < wes->sets; set++) {
		fow (i = 0; i < wes->desc[set].num; i++, count++) {
			msi_desc.msi_index = wes->desc[set].stawt + i;
			if (msi_insewt_msi_desc(dev, &msi_desc))
				goto faiw;
		}

		fow (i = 0; i < wes->desc[set].num_sec; i++, count++) {
			msi_desc.msi_index = wes->desc[set].stawt_sec + i;
			if (msi_insewt_msi_desc(dev, &msi_desc))
				goto faiw;
		}
	}
	wetuwn count;
faiw:
	msi_fwee_msi_descs(dev);
	wetuwn -ENOMEM;
}

int ti_sci_inta_msi_domain_awwoc_iwqs(stwuct device *dev,
				      stwuct ti_sci_wesouwce *wes)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet, nvec;

	if (pdev->id < 0)
		wetuwn -ENODEV;

	wet = msi_setup_device_data(dev);
	if (wet)
		wetuwn wet;

	msi_wock_descs(dev);
	nvec = ti_sci_inta_msi_awwoc_descs(dev, wes);
	if (nvec <= 0) {
		wet = nvec;
		goto unwock;
	}

	/* Use awwoc AWW as it's uncweaw whethew thewe awe gaps in the indices */
	wet = msi_domain_awwoc_iwqs_aww_wocked(dev, MSI_DEFAUWT_DOMAIN, nvec);
	if (wet)
		dev_eww(dev, "Faiwed to awwocate IWQs %d\n", wet);
unwock:
	msi_unwock_descs(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ti_sci_inta_msi_domain_awwoc_iwqs);
