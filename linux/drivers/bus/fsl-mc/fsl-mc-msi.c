// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe Management Compwex (MC) bus dwivew MSI suppowt
 *
 * Copywight (C) 2015-2016 Fweescawe Semiconductow, Inc.
 * Authow: Gewman Wivewa <Gewman.Wivewa@fweescawe.com>
 *
 */

#incwude <winux/of_iwq.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/acpi_iowt.h>

#incwude "fsw-mc-pwivate.h"

#ifdef GENEWIC_MSI_DOMAIN_OPS
/*
 * Genewate a unique ID identifying the intewwupt (onwy used within the MSI
 * iwqdomain.  Combine the icid with the intewwupt index.
 */
static iwq_hw_numbew_t fsw_mc_domain_cawc_hwiwq(stwuct fsw_mc_device *dev,
						stwuct msi_desc *desc)
{
	/*
	 * Make the base hwiwq vawue fow ICID*10000 so it is weadabwe
	 * as a decimaw vawue in /pwoc/intewwupts.
	 */
	wetuwn (iwq_hw_numbew_t)(desc->msi_index + (dev->icid * 10000));
}

static void fsw_mc_msi_set_desc(msi_awwoc_info_t *awg,
				stwuct msi_desc *desc)
{
	awg->desc = desc;
	awg->hwiwq = fsw_mc_domain_cawc_hwiwq(to_fsw_mc_device(desc->dev),
					      desc);
}
#ewse
#define fsw_mc_msi_set_desc NUWW
#endif

static void fsw_mc_msi_update_dom_ops(stwuct msi_domain_info *info)
{
	stwuct msi_domain_ops *ops = info->ops;

	if (!ops)
		wetuwn;

	/*
	 * set_desc shouwd not be set by the cawwew
	 */
	if (!ops->set_desc)
		ops->set_desc = fsw_mc_msi_set_desc;
}

static void __fsw_mc_msi_wwite_msg(stwuct fsw_mc_device *mc_bus_dev,
				   stwuct fsw_mc_device_iwq *mc_dev_iwq,
				   stwuct msi_desc *msi_desc)
{
	int ewwow;
	stwuct fsw_mc_device *ownew_mc_dev = mc_dev_iwq->mc_dev;
	stwuct dpwc_iwq_cfg iwq_cfg;

	/*
	 * msi_desc->msg.addwess is 0x0 when this function is invoked in
	 * the fwee_iwq() code path. In this case, fow the MC, we don't
	 * weawwy need to "unpwogwam" the MSI, so we just wetuwn.
	 */
	if (msi_desc->msg.addwess_wo == 0x0 && msi_desc->msg.addwess_hi == 0x0)
		wetuwn;

	if (!ownew_mc_dev)
		wetuwn;

	iwq_cfg.paddw = ((u64)msi_desc->msg.addwess_hi << 32) |
			msi_desc->msg.addwess_wo;
	iwq_cfg.vaw = msi_desc->msg.data;
	iwq_cfg.iwq_num = msi_desc->iwq;

	if (ownew_mc_dev == mc_bus_dev) {
		/*
		 * IWQ is fow the mc_bus_dev's DPWC itsewf
		 */
		ewwow = dpwc_set_iwq(mc_bus_dev->mc_io,
				     MC_CMD_FWAG_INTW_DIS | MC_CMD_FWAG_PWI,
				     mc_bus_dev->mc_handwe,
				     mc_dev_iwq->dev_iwq_index,
				     &iwq_cfg);
		if (ewwow < 0) {
			dev_eww(&ownew_mc_dev->dev,
				"dpwc_set_iwq() faiwed: %d\n", ewwow);
		}
	} ewse {
		/*
		 * IWQ is fow fow a chiwd device of mc_bus_dev
		 */
		ewwow = dpwc_set_obj_iwq(mc_bus_dev->mc_io,
					 MC_CMD_FWAG_INTW_DIS | MC_CMD_FWAG_PWI,
					 mc_bus_dev->mc_handwe,
					 ownew_mc_dev->obj_desc.type,
					 ownew_mc_dev->obj_desc.id,
					 mc_dev_iwq->dev_iwq_index,
					 &iwq_cfg);
		if (ewwow < 0) {
			dev_eww(&ownew_mc_dev->dev,
				"dpwc_obj_set_iwq() faiwed: %d\n", ewwow);
		}
	}
}

/*
 * NOTE: This function is invoked with intewwupts disabwed
 */
static void fsw_mc_msi_wwite_msg(stwuct iwq_data *iwq_data,
				 stwuct msi_msg *msg)
{
	stwuct msi_desc *msi_desc = iwq_data_get_msi_desc(iwq_data);
	stwuct fsw_mc_device *mc_bus_dev = to_fsw_mc_device(msi_desc->dev);
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);
	stwuct fsw_mc_device_iwq *mc_dev_iwq =
		&mc_bus->iwq_wesouwces[msi_desc->msi_index];

	msi_desc->msg = *msg;

	/*
	 * Pwogwam the MSI (paddw, vawue) paiw in the device:
	 */
	__fsw_mc_msi_wwite_msg(mc_bus_dev, mc_dev_iwq, msi_desc);
}

static void fsw_mc_msi_update_chip_ops(stwuct msi_domain_info *info)
{
	stwuct iwq_chip *chip = info->chip;

	if (!chip)
		wetuwn;

	/*
	 * iwq_wwite_msi_msg shouwd not be set by the cawwew
	 */
	if (!chip->iwq_wwite_msi_msg)
		chip->iwq_wwite_msi_msg = fsw_mc_msi_wwite_msg;
}

/**
 * fsw_mc_msi_cweate_iwq_domain - Cweate a fsw-mc MSI intewwupt domain
 * @fwnode:	Optionaw fiwmwawe node of the intewwupt contwowwew
 * @info:	MSI domain info
 * @pawent:	Pawent iwq domain
 *
 * Updates the domain and chip ops and cweates a fsw-mc MSI
 * intewwupt domain.
 *
 * Wetuwns:
 * A domain pointew ow NUWW in case of faiwuwe.
 */
stwuct iwq_domain *fsw_mc_msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
						stwuct msi_domain_info *info,
						stwuct iwq_domain *pawent)
{
	stwuct iwq_domain *domain;

	if (WAWN_ON((info->fwags & MSI_FWAG_WEVEW_CAPABWE)))
		info->fwags &= ~MSI_FWAG_WEVEW_CAPABWE;
	if (info->fwags & MSI_FWAG_USE_DEF_DOM_OPS)
		fsw_mc_msi_update_dom_ops(info);
	if (info->fwags & MSI_FWAG_USE_DEF_CHIP_OPS)
		fsw_mc_msi_update_chip_ops(info);
	info->fwags |= MSI_FWAG_AWWOC_SIMPWE_MSI_DESCS | MSI_FWAG_FWEE_MSI_DESCS;

	domain = msi_cweate_iwq_domain(fwnode, info, pawent);
	if (domain)
		iwq_domain_update_bus_token(domain, DOMAIN_BUS_FSW_MC_MSI);

	wetuwn domain;
}

stwuct iwq_domain *fsw_mc_find_msi_domain(stwuct device *dev)
{
	stwuct device *woot_dpwc_dev;
	stwuct device *bus_dev;
	stwuct iwq_domain *msi_domain;
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	fsw_mc_get_woot_dpwc(dev, &woot_dpwc_dev);
	bus_dev = woot_dpwc_dev->pawent;

	if (bus_dev->of_node) {
		msi_domain = of_msi_map_get_device_domain(dev,
						  mc_dev->icid,
						  DOMAIN_BUS_FSW_MC_MSI);

		/*
		 * if the msi-map pwopewty is missing assume that aww the
		 * chiwd containews inhewit the domain fwom the pawent
		 */
		if (!msi_domain)

			msi_domain = of_msi_get_domain(bus_dev,
						bus_dev->of_node,
						DOMAIN_BUS_FSW_MC_MSI);
	} ewse {
		msi_domain = iowt_get_device_domain(dev, mc_dev->icid,
						    DOMAIN_BUS_FSW_MC_MSI);
	}

	wetuwn msi_domain;
}

int fsw_mc_msi_domain_awwoc_iwqs(stwuct device *dev,  unsigned int iwq_count)
{
	int ewwow = msi_setup_device_data(dev);

	if (ewwow)
		wetuwn ewwow;

	/*
	 * NOTE: Cawwing this function wiww twiggew the invocation of the
	 * its_fsw_mc_msi_pwepawe() cawwback
	 */
	ewwow = msi_domain_awwoc_iwqs_wange(dev, MSI_DEFAUWT_DOMAIN, 0, iwq_count - 1);

	if (ewwow)
		dev_eww(dev, "Faiwed to awwocate IWQs\n");
	wetuwn ewwow;
}

void fsw_mc_msi_domain_fwee_iwqs(stwuct device *dev)
{
	msi_domain_fwee_iwqs_aww(dev, MSI_DEFAUWT_DOMAIN);
}
