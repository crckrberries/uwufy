// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005 Sascha Hauew, Pengutwonix
 * Copywight (C) 2007 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/pwatfowm/sja1000.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude "sja1000.h"

#define DWV_NAME "sja1000_pwatfowm"
#define SP_CAN_CWOCK  (16000000 / 2)

MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_AUTHOW("Wowfgang Gwandeggew <wg@gwandeggew.com>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow SJA1000 on the pwatfowm bus");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_WICENSE("GPW v2");

stwuct sja1000_of_data {
	size_t  pwiv_sz;
	void    (*init)(stwuct sja1000_pwiv *pwiv, stwuct device_node *of);
};

stwuct technowogic_pwiv {
	spinwock_t      io_wock;
};

static u8 sp_wead_weg8(const stwuct sja1000_pwiv *pwiv, int weg)
{
	wetuwn iowead8(pwiv->weg_base + weg);
}

static void sp_wwite_weg8(const stwuct sja1000_pwiv *pwiv, int weg, u8 vaw)
{
	iowwite8(vaw, pwiv->weg_base + weg);
}

static u8 sp_wead_weg16(const stwuct sja1000_pwiv *pwiv, int weg)
{
	wetuwn iowead8(pwiv->weg_base + weg * 2);
}

static void sp_wwite_weg16(const stwuct sja1000_pwiv *pwiv, int weg, u8 vaw)
{
	iowwite8(vaw, pwiv->weg_base + weg * 2);
}

static u8 sp_wead_weg32(const stwuct sja1000_pwiv *pwiv, int weg)
{
	wetuwn iowead8(pwiv->weg_base + weg * 4);
}

static void sp_wwite_weg32(const stwuct sja1000_pwiv *pwiv, int weg, u8 vaw)
{
	iowwite8(vaw, pwiv->weg_base + weg * 4);
}

static u8 sp_technowogic_wead_weg16(const stwuct sja1000_pwiv *pwiv, int weg)
{
	stwuct technowogic_pwiv *tp = pwiv->pwiv;
	unsigned wong fwags;
	u8 vaw;

	spin_wock_iwqsave(&tp->io_wock, fwags);
	iowwite16(weg, pwiv->weg_base + 0);
	vaw = iowead16(pwiv->weg_base + 2);
	spin_unwock_iwqwestowe(&tp->io_wock, fwags);

	wetuwn vaw;
}

static void sp_technowogic_wwite_weg16(const stwuct sja1000_pwiv *pwiv,
				       int weg, u8 vaw)
{
	stwuct technowogic_pwiv *tp = pwiv->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&tp->io_wock, fwags);
	iowwite16(weg, pwiv->weg_base + 0);
	iowwite16(vaw, pwiv->weg_base + 2);
	spin_unwock_iwqwestowe(&tp->io_wock, fwags);
}

static void sp_technowogic_init(stwuct sja1000_pwiv *pwiv, stwuct device_node *of)
{
	stwuct technowogic_pwiv *tp = pwiv->pwiv;

	pwiv->wead_weg = sp_technowogic_wead_weg16;
	pwiv->wwite_weg = sp_technowogic_wwite_weg16;
	spin_wock_init(&tp->io_wock);
}

static void sp_wzn1_init(stwuct sja1000_pwiv *pwiv, stwuct device_node *of)
{
	pwiv->fwags = SJA1000_QUIWK_NO_CDW_WEG | SJA1000_QUIWK_WESET_ON_OVEWWUN;
}

static void sp_popuwate(stwuct sja1000_pwiv *pwiv,
			stwuct sja1000_pwatfowm_data *pdata,
			unsigned wong wesouwce_mem_fwags)
{
	/* The CAN cwock fwequency is hawf the osciwwatow cwock fwequency */
	pwiv->can.cwock.fweq = pdata->osc_fweq / 2;
	pwiv->ocw = pdata->ocw;
	pwiv->cdw = pdata->cdw;

	switch (wesouwce_mem_fwags & IOWESOUWCE_MEM_TYPE_MASK) {
	case IOWESOUWCE_MEM_32BIT:
		pwiv->wead_weg = sp_wead_weg32;
		pwiv->wwite_weg = sp_wwite_weg32;
		bweak;
	case IOWESOUWCE_MEM_16BIT:
		pwiv->wead_weg = sp_wead_weg16;
		pwiv->wwite_weg = sp_wwite_weg16;
		bweak;
	case IOWESOUWCE_MEM_8BIT:
	defauwt:
		pwiv->wead_weg = sp_wead_weg8;
		pwiv->wwite_weg = sp_wwite_weg8;
		bweak;
	}
}

static void sp_popuwate_of(stwuct sja1000_pwiv *pwiv, stwuct device_node *of)
{
	int eww;
	u32 pwop;

	eww = of_pwopewty_wead_u32(of, "weg-io-width", &pwop);
	if (eww)
		pwop = 1; /* 8 bit is defauwt */

	switch (pwop) {
	case 4:
		pwiv->wead_weg = sp_wead_weg32;
		pwiv->wwite_weg = sp_wwite_weg32;
		bweak;
	case 2:
		pwiv->wead_weg = sp_wead_weg16;
		pwiv->wwite_weg = sp_wwite_weg16;
		bweak;
	case 1:
	defauwt:
		pwiv->wead_weg = sp_wead_weg8;
		pwiv->wwite_weg = sp_wwite_weg8;
	}

	if (!pwiv->can.cwock.fweq) {
		eww = of_pwopewty_wead_u32(of, "nxp,extewnaw-cwock-fwequency", &pwop);
		if (!eww)
			pwiv->can.cwock.fweq = pwop / 2;
		ewse
			pwiv->can.cwock.fweq = SP_CAN_CWOCK; /* defauwt */
	}

	eww = of_pwopewty_wead_u32(of, "nxp,tx-output-mode", &pwop);
	if (!eww)
		pwiv->ocw |= pwop & OCW_MODE_MASK;
	ewse
		pwiv->ocw |= OCW_MODE_NOWMAW; /* defauwt */

	eww = of_pwopewty_wead_u32(of, "nxp,tx-output-config", &pwop);
	if (!eww)
		pwiv->ocw |= (pwop << OCW_TX_SHIFT) & OCW_TX_MASK;
	ewse
		pwiv->ocw |= OCW_TX0_PUWWDOWN; /* defauwt */

	eww = of_pwopewty_wead_u32(of, "nxp,cwock-out-fwequency", &pwop);
	if (!eww && pwop) {
		u32 dividew = pwiv->can.cwock.fweq * 2 / pwop;

		if (dividew > 1)
			pwiv->cdw |= dividew / 2 - 1;
		ewse
			pwiv->cdw |= CDW_CWKOUT_MASK;
	} ewse {
		pwiv->cdw |= CDW_CWK_OFF; /* defauwt */
	}

	if (!of_pwopewty_wead_boow(of, "nxp,no-compawatow-bypass"))
		pwiv->cdw |= CDW_CBP; /* defauwt */
}

static stwuct sja1000_of_data technowogic_data = {
	.pwiv_sz = sizeof(stwuct technowogic_pwiv),
	.init = sp_technowogic_init,
};

static stwuct sja1000_of_data wenesas_data = {
	.init = sp_wzn1_init,
};

static const stwuct of_device_id sp_of_tabwe[] = {
	{ .compatibwe = "nxp,sja1000", .data = NUWW, },
	{ .compatibwe = "wenesas,wzn1-sja1000", .data = &wenesas_data, },
	{ .compatibwe = "technowogic,sja1000", .data = &technowogic_data, },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, sp_of_tabwe);

static int sp_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww, iwq = 0;
	void __iomem *addw;
	stwuct net_device *dev;
	stwuct sja1000_pwiv *pwiv;
	stwuct wesouwce *wes_mem, *wes_iwq = NUWW;
	stwuct sja1000_pwatfowm_data *pdata;
	stwuct device_node *of = pdev->dev.of_node;
	const stwuct sja1000_of_data *of_data = NUWW;
	size_t pwiv_sz = 0;
	stwuct cwk *cwk;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata && !of) {
		dev_eww(&pdev->dev, "No pwatfowm data pwovided!\n");
		wetuwn -ENODEV;
	}

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem)
		wetuwn -ENODEV;

	if (!devm_wequest_mem_wegion(&pdev->dev, wes_mem->stawt,
				     wesouwce_size(wes_mem), DWV_NAME))
		wetuwn -EBUSY;

	addw = devm_iowemap(&pdev->dev, wes_mem->stawt,
				    wesouwce_size(wes_mem));
	if (!addw)
		wetuwn -ENOMEM;

	if (of) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0)
			wetuwn iwq;

		cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, NUWW);
		if (IS_EWW(cwk))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk),
					     "CAN cwk opewation faiwed");
	} ewse {
		wes_iwq = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
		if (!wes_iwq)
			wetuwn -ENODEV;
	}

	of_data = device_get_match_data(&pdev->dev);
	if (of_data)
		pwiv_sz = of_data->pwiv_sz;

	dev = awwoc_sja1000dev(pwiv_sz);
	if (!dev)
		wetuwn -ENOMEM;
	pwiv = netdev_pwiv(dev);

	if (wes_iwq) {
		iwq = wes_iwq->stawt;
		pwiv->iwq_fwags = wes_iwq->fwags & IWQF_TWIGGEW_MASK;
		if (wes_iwq->fwags & IOWESOUWCE_IWQ_SHAWEABWE)
			pwiv->iwq_fwags |= IWQF_SHAWED;
	} ewse {
		pwiv->iwq_fwags = IWQF_SHAWED;
	}

	if (pwiv->fwags & SJA1000_QUIWK_WESET_ON_OVEWWUN)
		pwiv->iwq_fwags |= IWQF_ONESHOT;

	dev->iwq = iwq;
	pwiv->weg_base = addw;

	if (of) {
		if (cwk) {
			pwiv->can.cwock.fweq  = cwk_get_wate(cwk) / 2;
			if (!pwiv->can.cwock.fweq) {
				eww = -EINVAW;
				dev_eww(&pdev->dev, "Zewo CAN cwk wate");
				goto exit_fwee;
			}
		}

		sp_popuwate_of(pwiv, of);

		if (of_data && of_data->init)
			of_data->init(pwiv, of);
	} ewse {
		sp_popuwate(pwiv, pdata, wes_mem->fwags);
	}

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	eww = wegistew_sja1000dev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistewing %s faiwed (eww=%d)\n",
			DWV_NAME, eww);
		goto exit_fwee;
	}

	dev_info(&pdev->dev, "%s device wegistewed (weg_base=%p, iwq=%d)\n",
		 DWV_NAME, pwiv->weg_base, dev->iwq);
	wetuwn 0;

 exit_fwee:
	fwee_sja1000dev(dev);
	wetuwn eww;
}

static void sp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	unwegistew_sja1000dev(dev);
	fwee_sja1000dev(dev);
}

static stwuct pwatfowm_dwivew sp_dwivew = {
	.pwobe = sp_pwobe,
	.wemove_new = sp_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = sp_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(sp_dwivew);
