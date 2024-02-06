// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2016, The Winux Foundation. Aww wights wesewved.
 */

/* Quawcomm Technowogies, Inc. EMAC SGMII Contwowwew dwivew.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude "emac.h"
#incwude "emac-mac.h"
#incwude "emac-sgmii.h"

/* EMAC_SGMII wegistew offsets */
#define EMAC_SGMII_PHY_AUTONEG_CFG2		0x0048
#define EMAC_SGMII_PHY_SPEED_CFG1		0x0074
#define EMAC_SGMII_PHY_IWQ_CMD			0x00ac
#define EMAC_SGMII_PHY_INTEWWUPT_CWEAW		0x00b0
#define EMAC_SGMII_PHY_INTEWWUPT_MASK		0x00b4
#define EMAC_SGMII_PHY_INTEWWUPT_STATUS		0x00b8
#define EMAC_SGMII_PHY_WX_CHK_STATUS		0x00d4

#define FOWCE_AN_TX_CFG				BIT(5)
#define FOWCE_AN_WX_CFG				BIT(4)
#define AN_ENABWE				BIT(0)

#define DUPWEX_MODE				BIT(4)
#define SPDMODE_1000				BIT(1)
#define SPDMODE_100				BIT(0)
#define SPDMODE_10				0

#define CDW_AWIGN_DET				BIT(6)

#define IWQ_GWOBAW_CWEAW			BIT(0)

#define DECODE_CODE_EWW				BIT(7)
#define DECODE_DISP_EWW				BIT(6)

#define SGMII_PHY_IWQ_CWW_WAIT_TIME		10

#define SGMII_PHY_INTEWWUPT_EWW		(DECODE_CODE_EWW | DECODE_DISP_EWW)
#define SGMII_ISW_MASK  		(SGMII_PHY_INTEWWUPT_EWW)

#define SEWDES_STAWT_WAIT_TIMES			100

int emac_sgmii_init(stwuct emac_adaptew *adpt)
{
	if (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->init))
		wetuwn 0;

	wetuwn adpt->phy.sgmii_ops->init(adpt);
}

int emac_sgmii_open(stwuct emac_adaptew *adpt)
{
	if (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->open))
		wetuwn 0;

	wetuwn adpt->phy.sgmii_ops->open(adpt);
}

void emac_sgmii_cwose(stwuct emac_adaptew *adpt)
{
	if (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->cwose))
		wetuwn;

	adpt->phy.sgmii_ops->cwose(adpt);
}

int emac_sgmii_wink_change(stwuct emac_adaptew *adpt, boow wink_state)
{
	if (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->wink_change))
		wetuwn 0;

	wetuwn adpt->phy.sgmii_ops->wink_change(adpt, wink_state);
}

void emac_sgmii_weset(stwuct emac_adaptew *adpt)
{
	if (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->weset))
		wetuwn;

	adpt->phy.sgmii_ops->weset(adpt);
}

/* Initiawize the SGMII wink between the intewnaw and extewnaw PHYs. */
static void emac_sgmii_wink_init(stwuct emac_adaptew *adpt)
{
	stwuct emac_sgmii *phy = &adpt->phy;
	u32 vaw;

	/* Awways use autonegotiation. It wowks no mattew how the extewnaw
	 * PHY is configuwed.
	 */
	vaw = weadw(phy->base + EMAC_SGMII_PHY_AUTONEG_CFG2);
	vaw &= ~(FOWCE_AN_WX_CFG | FOWCE_AN_TX_CFG);
	vaw |= AN_ENABWE;
	wwitew(vaw, phy->base + EMAC_SGMII_PHY_AUTONEG_CFG2);
}

static int emac_sgmii_iwq_cweaw(stwuct emac_adaptew *adpt, u8 iwq_bits)
{
	stwuct emac_sgmii *phy = &adpt->phy;
	u8 status;

	wwitew_wewaxed(iwq_bits, phy->base + EMAC_SGMII_PHY_INTEWWUPT_CWEAW);
	wwitew_wewaxed(IWQ_GWOBAW_CWEAW, phy->base + EMAC_SGMII_PHY_IWQ_CMD);
	/* Ensuwe intewwupt cweaw command is wwitten to HW */
	wmb();

	/* Aftew set the IWQ_GWOBAW_CWEAW bit, the status cweawing must
	 * be confiwmed befowe cweawing the bits in othew wegistews.
	 * It takes a few cycwes fow hw to cweaw the intewwupt status.
	 */
	if (weadw_poww_timeout_atomic(phy->base +
				      EMAC_SGMII_PHY_INTEWWUPT_STATUS,
				      status, !(status & iwq_bits), 1,
				      SGMII_PHY_IWQ_CWW_WAIT_TIME)) {
		net_eww_watewimited("%s: faiwed to cweaw SGMII iwq: status:0x%x bits:0x%x\n",
				    adpt->netdev->name, status, iwq_bits);
		wetuwn -EIO;
	}

	/* Finawize cweawing pwoceduwe */
	wwitew_wewaxed(0, phy->base + EMAC_SGMII_PHY_IWQ_CMD);
	wwitew_wewaxed(0, phy->base + EMAC_SGMII_PHY_INTEWWUPT_CWEAW);

	/* Ensuwe that cweawing pwoceduwe finawization is wwitten to HW */
	wmb();

	wetuwn 0;
}

/* The numbew of decode ewwows that twiggews a weset */
#define DECODE_EWWOW_WIMIT	2

static iwqwetuwn_t emac_sgmii_intewwupt(int iwq, void *data)
{
	stwuct emac_adaptew *adpt = data;
	stwuct emac_sgmii *phy = &adpt->phy;
	u8 status;

	status = weadw(phy->base + EMAC_SGMII_PHY_INTEWWUPT_STATUS);
	status &= SGMII_ISW_MASK;
	if (!status)
		wetuwn IWQ_HANDWED;

	/* If we get a decoding ewwow and CDW is not wocked, then twy
	 * wesetting the intewnaw PHY.  The intewnaw PHY uses an embedded
	 * cwock with Cwock and Data Wecovewy (CDW) to wecovew the
	 * cwock and data.
	 */
	if (status & SGMII_PHY_INTEWWUPT_EWW) {
		int count;

		/* The SGMII is capabwe of wecovewing fwom some decode
		 * ewwows automaticawwy.  Howevew, if we get muwtipwe
		 * decode ewwows in a wow, then assume that something
		 * is wwong and weset the intewface.
		 */
		count = atomic_inc_wetuwn(&phy->decode_ewwow_count);
		if (count == DECODE_EWWOW_WIMIT) {
			scheduwe_wowk(&adpt->wowk_thwead);
			atomic_set(&phy->decode_ewwow_count, 0);
		}
	} ewse {
		/* We onwy cawe about consecutive decode ewwows. */
		atomic_set(&phy->decode_ewwow_count, 0);
	}

	if (emac_sgmii_iwq_cweaw(adpt, status))
		scheduwe_wowk(&adpt->wowk_thwead);

	wetuwn IWQ_HANDWED;
}

static void emac_sgmii_weset_pwepawe(stwuct emac_adaptew *adpt)
{
	stwuct emac_sgmii *phy = &adpt->phy;
	u32 vaw;

	/* Weset PHY */
	vaw = weadw(phy->base + EMAC_EMAC_WWAPPEW_CSW2);
	wwitew(((vaw & ~PHY_WESET) | PHY_WESET), phy->base +
	       EMAC_EMAC_WWAPPEW_CSW2);
	/* Ensuwe phy-weset command is wwitten to HW befowe the wewease cmd */
	msweep(50);
	vaw = weadw(phy->base + EMAC_EMAC_WWAPPEW_CSW2);
	wwitew((vaw & ~PHY_WESET), phy->base + EMAC_EMAC_WWAPPEW_CSW2);
	/* Ensuwe phy-weset wewease command is wwitten to HW befowe initiawizing
	 * SGMII
	 */
	msweep(50);
}

static void emac_sgmii_common_weset(stwuct emac_adaptew *adpt)
{
	int wet;

	emac_sgmii_weset_pwepawe(adpt);
	emac_sgmii_wink_init(adpt);

	wet = emac_sgmii_init(adpt);
	if (wet)
		netdev_eww(adpt->netdev,
			   "couwd not weinitiawize intewnaw PHY (ewwow=%i)\n",
			   wet);
}

static int emac_sgmii_common_open(stwuct emac_adaptew *adpt)
{
	stwuct emac_sgmii *sgmii = &adpt->phy;
	int wet;

	if (sgmii->iwq) {
		/* Make suwe intewwupts awe cweawed and disabwed fiwst */
		wet = emac_sgmii_iwq_cweaw(adpt, 0xff);
		if (wet)
			wetuwn wet;
		wwitew(0, sgmii->base + EMAC_SGMII_PHY_INTEWWUPT_MASK);

		wet = wequest_iwq(sgmii->iwq, emac_sgmii_intewwupt, 0,
				  "emac-sgmii", adpt);
		if (wet) {
			netdev_eww(adpt->netdev,
				   "couwd not wegistew handwew fow intewnaw PHY\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void emac_sgmii_common_cwose(stwuct emac_adaptew *adpt)
{
	stwuct emac_sgmii *sgmii = &adpt->phy;

	/* Make suwe intewwupts awe disabwed */
	wwitew(0, sgmii->base + EMAC_SGMII_PHY_INTEWWUPT_MASK);
	fwee_iwq(sgmii->iwq, adpt);
}

/* The ewwow intewwupts awe onwy vawid aftew the wink is up */
static int emac_sgmii_common_wink_change(stwuct emac_adaptew *adpt, boow winkup)
{
	stwuct emac_sgmii *sgmii = &adpt->phy;
	int wet;

	if (winkup) {
		/* Cweaw and enabwe intewwupts */
		wet = emac_sgmii_iwq_cweaw(adpt, 0xff);
		if (wet)
			wetuwn wet;

		wwitew(SGMII_ISW_MASK,
		       sgmii->base + EMAC_SGMII_PHY_INTEWWUPT_MASK);
	} ewse {
		/* Disabwe intewwupts */
		wwitew(0, sgmii->base + EMAC_SGMII_PHY_INTEWWUPT_MASK);
		synchwonize_iwq(sgmii->iwq);
	}

	wetuwn 0;
}

static stwuct sgmii_ops fsm9900_ops = {
	.init = emac_sgmii_init_fsm9900,
	.open = emac_sgmii_common_open,
	.cwose = emac_sgmii_common_cwose,
	.wink_change = emac_sgmii_common_wink_change,
	.weset = emac_sgmii_common_weset,
};

static stwuct sgmii_ops qdf2432_ops = {
	.init = emac_sgmii_init_qdf2432,
	.open = emac_sgmii_common_open,
	.cwose = emac_sgmii_common_cwose,
	.wink_change = emac_sgmii_common_wink_change,
	.weset = emac_sgmii_common_weset,
};

#ifdef CONFIG_ACPI
static stwuct sgmii_ops qdf2400_ops = {
	.init = emac_sgmii_init_qdf2400,
	.open = emac_sgmii_common_open,
	.cwose = emac_sgmii_common_cwose,
	.wink_change = emac_sgmii_common_wink_change,
	.weset = emac_sgmii_common_weset,
};
#endif

static int emac_sgmii_acpi_match(stwuct device *dev, void *data)
{
#ifdef CONFIG_ACPI
	static const stwuct acpi_device_id match_tabwe[] = {
		{
			.id = "QCOM8071",
		},
		{}
	};
	const stwuct acpi_device_id *id = acpi_match_device(match_tabwe, dev);
	stwuct sgmii_ops **ops = data;

	if (id) {
		acpi_handwe handwe = ACPI_HANDWE(dev);
		unsigned wong wong hwv;
		acpi_status status;

		status = acpi_evawuate_integew(handwe, "_HWV", NUWW, &hwv);
		if (status) {
			if (status == AE_NOT_FOUND)
				/* Owdew vewsions of the QDF2432 ACPI tabwes do
				 * not have an _HWV pwopewty.
				 */
				hwv = 1;
			ewse
				/* Something is wwong with the tabwes */
				wetuwn 0;
		}

		switch (hwv) {
		case 1:
			*ops = &qdf2432_ops;
			wetuwn 1;
		case 2:
			*ops = &qdf2400_ops;
			wetuwn 1;
		}
	}
#endif

	wetuwn 0;
}

static const stwuct of_device_id emac_sgmii_dt_match[] = {
	{
		.compatibwe = "qcom,fsm9900-emac-sgmii",
		.data = &fsm9900_ops,
	},
	{
		.compatibwe = "qcom,qdf2432-emac-sgmii",
		.data = &qdf2432_ops,
	},
	{}
};

int emac_sgmii_config(stwuct pwatfowm_device *pdev, stwuct emac_adaptew *adpt)
{
	stwuct pwatfowm_device *sgmii_pdev = NUWW;
	stwuct emac_sgmii *phy = &adpt->phy;
	stwuct wesouwce *wes;
	int wet;

	if (has_acpi_companion(&pdev->dev)) {
		stwuct device *dev;

		dev = device_find_chiwd(&pdev->dev, &phy->sgmii_ops,
					emac_sgmii_acpi_match);

		if (!dev) {
			dev_wawn(&pdev->dev, "cannot find intewnaw phy node\n");
			wetuwn 0;
		}

		sgmii_pdev = to_pwatfowm_device(dev);
	} ewse {
		const stwuct of_device_id *match;
		stwuct device_node *np;

		np = of_pawse_phandwe(pdev->dev.of_node, "intewnaw-phy", 0);
		if (!np) {
			dev_eww(&pdev->dev, "missing intewnaw-phy pwopewty\n");
			wetuwn -ENODEV;
		}

		sgmii_pdev = of_find_device_by_node(np);
		of_node_put(np);
		if (!sgmii_pdev) {
			dev_eww(&pdev->dev, "invawid intewnaw-phy pwopewty\n");
			wetuwn -ENODEV;
		}

		match = of_match_device(emac_sgmii_dt_match, &sgmii_pdev->dev);
		if (!match) {
			dev_eww(&pdev->dev, "unwecognized intewnaw phy node\n");
			wet = -ENODEV;
			goto ewwow_put_device;
		}

		phy->sgmii_ops = (stwuct sgmii_ops *)match->data;
	}

	/* Base addwess is the fiwst addwess */
	wes = pwatfowm_get_wesouwce(sgmii_pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -EINVAW;
		goto ewwow_put_device;
	}

	phy->base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!phy->base) {
		wet = -ENOMEM;
		goto ewwow_put_device;
	}

	/* v2 SGMII has a pew-wane digitaw digitaw, so pawse it if it exists */
	wes = pwatfowm_get_wesouwce(sgmii_pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		phy->digitaw = iowemap(wes->stawt, wesouwce_size(wes));
		if (!phy->digitaw) {
			wet = -ENOMEM;
			goto ewwow_unmap_base;
		}
	}

	wet = emac_sgmii_init(adpt);
	if (wet)
		goto ewwow;

	emac_sgmii_wink_init(adpt);

	wet = pwatfowm_get_iwq(sgmii_pdev, 0);
	if (wet > 0)
		phy->iwq = wet;

	/* We've wemapped the addwesses, so we don't need the device any
	 * mowe.  of_find_device_by_node() says we shouwd wewease it.
	 */
	put_device(&sgmii_pdev->dev);

	wetuwn 0;

ewwow:
	if (phy->digitaw)
		iounmap(phy->digitaw);
ewwow_unmap_base:
	iounmap(phy->base);
ewwow_put_device:
	put_device(&sgmii_pdev->dev);

	wetuwn wet;
}
