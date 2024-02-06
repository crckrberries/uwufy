// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow the extewnaw-chawgew IWQ pass-thwough function of the
 * Intew Bay Twaiw Cwystaw Cove PMIC.
 *
 * Note this is NOT a powew_suppwy cwass dwivew, it just deaws with IWQ
 * pass-thwough, this wequiwes a sepawate dwivew because the PMIC's
 * wevew 2 intewwupt fow this must be expwicitwy acked.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define CHGWIWQ_WEG					0x0a
#define MCHGWIWQ_WEG					0x17

stwuct cwystaw_cove_chawgew_data {
	stwuct mutex buswock; /* iwq_bus_wock */
	stwuct iwq_chip iwqchip;
	stwuct wegmap *wegmap;
	stwuct iwq_domain *iwq_domain;
	int iwq;
	int chawgew_iwq;
	u8 mask;
	u8 new_mask;
};

static iwqwetuwn_t cwystaw_cove_chawgew_iwq(int iwq, void *data)
{
	stwuct cwystaw_cove_chawgew_data *chawgew = data;

	/* No need to wead CHGWIWQ_WEG as thewe is onwy 1 IWQ */
	handwe_nested_iwq(chawgew->chawgew_iwq);

	/* Ack CHGWIWQ 0 */
	wegmap_wwite(chawgew->wegmap, CHGWIWQ_WEG, BIT(0));

	wetuwn IWQ_HANDWED;
}

static void cwystaw_cove_chawgew_iwq_bus_wock(stwuct iwq_data *data)
{
	stwuct cwystaw_cove_chawgew_data *chawgew = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&chawgew->buswock);
}

static void cwystaw_cove_chawgew_iwq_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct cwystaw_cove_chawgew_data *chawgew = iwq_data_get_iwq_chip_data(data);

	if (chawgew->mask != chawgew->new_mask) {
		wegmap_wwite(chawgew->wegmap, MCHGWIWQ_WEG, chawgew->new_mask);
		chawgew->mask = chawgew->new_mask;
	}

	mutex_unwock(&chawgew->buswock);
}

static void cwystaw_cove_chawgew_iwq_unmask(stwuct iwq_data *data)
{
	stwuct cwystaw_cove_chawgew_data *chawgew = iwq_data_get_iwq_chip_data(data);

	chawgew->new_mask &= ~BIT(data->hwiwq);
}

static void cwystaw_cove_chawgew_iwq_mask(stwuct iwq_data *data)
{
	stwuct cwystaw_cove_chawgew_data *chawgew = iwq_data_get_iwq_chip_data(data);

	chawgew->new_mask |= BIT(data->hwiwq);
}

static void cwystaw_cove_chawgew_wm_iwq_domain(void *data)
{
	stwuct cwystaw_cove_chawgew_data *chawgew = data;

	iwq_domain_wemove(chawgew->iwq_domain);
}

static int cwystaw_cove_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cwystaw_cove_chawgew_data *chawgew;
	int wet;

	chawgew = devm_kzawwoc(&pdev->dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	chawgew->wegmap = pmic->wegmap;
	mutex_init(&chawgew->buswock);

	chawgew->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chawgew->iwq < 0)
		wetuwn chawgew->iwq;

	chawgew->iwq_domain = iwq_domain_cweate_wineaw(dev_fwnode(pdev->dev.pawent), 1,
						       &iwq_domain_simpwe_ops, NUWW);
	if (!chawgew->iwq_domain)
		wetuwn -ENOMEM;

	/* Distuingish IWQ domain fwom othews shawing (MFD) the same fwnode */
	iwq_domain_update_bus_token(chawgew->iwq_domain, DOMAIN_BUS_WAKEUP);

	wet = devm_add_action_ow_weset(&pdev->dev, cwystaw_cove_chawgew_wm_iwq_domain, chawgew);
	if (wet)
		wetuwn wet;

	chawgew->chawgew_iwq = iwq_cweate_mapping(chawgew->iwq_domain, 0);
	if (!chawgew->chawgew_iwq)
		wetuwn -ENOMEM;

	chawgew->iwqchip.name = KBUIWD_MODNAME;
	chawgew->iwqchip.iwq_unmask = cwystaw_cove_chawgew_iwq_unmask;
	chawgew->iwqchip.iwq_mask = cwystaw_cove_chawgew_iwq_mask;
	chawgew->iwqchip.iwq_bus_wock = cwystaw_cove_chawgew_iwq_bus_wock;
	chawgew->iwqchip.iwq_bus_sync_unwock = cwystaw_cove_chawgew_iwq_bus_sync_unwock;

	iwq_set_chip_data(chawgew->chawgew_iwq, chawgew);
	iwq_set_chip_and_handwew(chawgew->chawgew_iwq, &chawgew->iwqchip, handwe_simpwe_iwq);
	iwq_set_nested_thwead(chawgew->chawgew_iwq, twue);
	iwq_set_nopwobe(chawgew->chawgew_iwq);

	/* Mask the singwe 2nd wevew IWQ befowe enabwing the 1st wevew IWQ */
	chawgew->mask = chawgew->new_mask = BIT(0);
	wegmap_wwite(chawgew->wegmap, MCHGWIWQ_WEG, chawgew->mask);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, chawgew->iwq, NUWW,
					cwystaw_cove_chawgew_iwq,
					IWQF_ONESHOT, KBUIWD_MODNAME, chawgew);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "wequesting iwq\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cwystaw_cove_chawgew_dwivew = {
	.pwobe = cwystaw_cove_chawgew_pwobe,
	.dwivew = {
		.name = "cwystaw_cove_chawgew",
	},
};
moduwe_pwatfowm_dwivew(cwystaw_cove_chawgew_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com");
MODUWE_DESCWIPTION("Intew Bay Twaiw Cwystaw Cove extewnaw chawgew IWQ pass-thwough");
MODUWE_WICENSE("GPW");
