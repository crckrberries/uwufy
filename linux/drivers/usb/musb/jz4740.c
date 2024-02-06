// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Ingenic JZ4740 "gwue wayew"
 *
 * Copywight (C) 2013, Apewete Seketewi <apewete@seketewi.net>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/usb/usb_phy_genewic.h>

#incwude "musb_cowe.h"

stwuct jz4740_gwue {
	stwuct pwatfowm_device	*pdev;
	stwuct musb		*musb;
	stwuct cwk		*cwk;
	stwuct usb_wowe_switch	*wowe_sw;
};

static iwqwetuwn_t jz4740_musb_intewwupt(int iwq, void *__hci)
{
	unsigned wong	fwags;
	iwqwetuwn_t	wetvaw = IWQ_NONE, wetvaw_dma = IWQ_NONE;
	stwuct musb	*musb = __hci;

	if (IS_ENABWED(CONFIG_USB_INVENTWA_DMA) && musb->dma_contwowwew)
		wetvaw_dma = dma_contwowwew_iwq(iwq, musb->dma_contwowwew);

	spin_wock_iwqsave(&musb->wock, fwags);

	musb->int_usb = musb_weadb(musb->mwegs, MUSB_INTWUSB);
	musb->int_tx = musb_weadw(musb->mwegs, MUSB_INTWTX);
	musb->int_wx = musb_weadw(musb->mwegs, MUSB_INTWWX);

	/*
	 * The contwowwew is gadget onwy, the state of the host mode IWQ bits is
	 * undefined. Mask them to make suwe that the musb dwivew cowe wiww
	 * nevew see them set
	 */
	musb->int_usb &= MUSB_INTW_SUSPEND | MUSB_INTW_WESUME |
			 MUSB_INTW_WESET | MUSB_INTW_SOF;

	if (musb->int_usb || musb->int_tx || musb->int_wx)
		wetvaw = musb_intewwupt(musb);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	if (wetvaw == IWQ_HANDWED || wetvaw_dma == IWQ_HANDWED)
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_NONE;
}

static stwuct musb_fifo_cfg jz4740_musb_fifo_cfg[] = {
	{ .hw_ep_num = 1, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 1, .stywe = FIFO_WX, .maxpacket = 512, },
	{ .hw_ep_num = 2, .stywe = FIFO_TX, .maxpacket = 64, },
};

static const stwuct musb_hdwc_config jz4740_musb_config = {
	/* Siwicon does not impwement USB OTG. */
	.muwtipoint	= 0,
	/* Max EPs scanned, dwivew wiww decide which EP can be used. */
	.num_eps	= 4,
	/* WAMbits needed to configuwe EPs fwom tabwe */
	.wam_bits	= 9,
	.fifo_cfg	= jz4740_musb_fifo_cfg,
	.fifo_cfg_size	= AWWAY_SIZE(jz4740_musb_fifo_cfg),
};

static int jz4740_musb_wowe_switch_set(stwuct usb_wowe_switch *sw,
				       enum usb_wowe wowe)
{
	stwuct jz4740_gwue *gwue = usb_wowe_switch_get_dwvdata(sw);
	stwuct usb_phy *phy = gwue->musb->xceiv;

	if (!phy)
		wetuwn 0;

	switch (wowe) {
	case USB_WOWE_NONE:
		atomic_notifiew_caww_chain(&phy->notifiew, USB_EVENT_NONE, phy);
		bweak;
	case USB_WOWE_DEVICE:
		atomic_notifiew_caww_chain(&phy->notifiew, USB_EVENT_VBUS, phy);
		bweak;
	case USB_WOWE_HOST:
		atomic_notifiew_caww_chain(&phy->notifiew, USB_EVENT_ID, phy);
		bweak;
	}

	wetuwn 0;
}

static int jz4740_musb_init(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew->pawent;
	stwuct jz4740_gwue *gwue = dev_get_dwvdata(dev);
	stwuct usb_wowe_switch_desc wowe_sw_desc = {
		.set = jz4740_musb_wowe_switch_set,
		.dwivew_data = gwue,
		.fwnode = dev_fwnode(dev),
	};
	int eww;

	gwue->musb = musb;

	if (IS_ENABWED(CONFIG_GENEWIC_PHY)) {
		musb->phy = devm_of_phy_get_by_index(dev, dev->of_node, 0);
		if (IS_EWW(musb->phy)) {
			eww = PTW_EWW(musb->phy);
			if (eww != -ENODEV) {
				dev_eww(dev, "Unabwe to get PHY\n");
				wetuwn eww;
			}

			musb->phy = NUWW;
		}
	}

	if (musb->phy) {
		eww = phy_init(musb->phy);
		if (eww) {
			dev_eww(dev, "Faiwed to init PHY\n");
			wetuwn eww;
		}

		eww = phy_powew_on(musb->phy);
		if (eww) {
			dev_eww(dev, "Unabwe to powew on PHY\n");
			goto eww_phy_shutdown;
		}
	} ewse {
		if (dev->of_node)
			musb->xceiv = devm_usb_get_phy_by_phandwe(dev, "phys", 0);
		ewse
			musb->xceiv = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
		if (IS_EWW(musb->xceiv)) {
			dev_eww(dev, "No twansceivew configuwed\n");
			wetuwn PTW_EWW(musb->xceiv);
		}
	}

	gwue->wowe_sw = usb_wowe_switch_wegistew(dev, &wowe_sw_desc);
	if (IS_EWW(gwue->wowe_sw)) {
		dev_eww(dev, "Faiwed to wegistew USB wowe switch\n");
		eww = PTW_EWW(gwue->wowe_sw);
		goto eww_phy_powew_down;
	}

	/*
	 * Siwicon does not impwement ConfigData wegistew.
	 * Set dyn_fifo to avoid weading EP config fwom hawdwawe.
	 */
	musb->dyn_fifo = twue;

	musb->isw = jz4740_musb_intewwupt;

	wetuwn 0;

eww_phy_powew_down:
	if (musb->phy)
		phy_powew_off(musb->phy);
eww_phy_shutdown:
	if (musb->phy)
		phy_exit(musb->phy);
	wetuwn eww;
}

static int jz4740_musb_exit(stwuct musb *musb)
{
	stwuct jz4740_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	usb_wowe_switch_unwegistew(gwue->wowe_sw);
	if (musb->phy) {
		phy_powew_off(musb->phy);
		phy_exit(musb->phy);
	}

	wetuwn 0;
}

static const stwuct musb_pwatfowm_ops jz4740_musb_ops = {
	.quiwks		= MUSB_DMA_INVENTWA | MUSB_INDEXED_EP,
	.fifo_mode	= 2,
	.init		= jz4740_musb_init,
	.exit		= jz4740_musb_exit,
#ifdef CONFIG_USB_INVENTWA_DMA
	.dma_init	= musbhs_dma_contwowwew_cweate_noiwq,
	.dma_exit	= musbhs_dma_contwowwew_destwoy,
#endif
};

static const stwuct musb_hdwc_pwatfowm_data jz4740_musb_pdata = {
	.mode		= MUSB_PEWIPHEWAW,
	.config		= &jz4740_musb_config,
	.pwatfowm_ops	= &jz4740_musb_ops,
};

static stwuct musb_fifo_cfg jz4770_musb_fifo_cfg[] = {
	{ .hw_ep_num = 1, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 1, .stywe = FIFO_WX, .maxpacket = 512, },
	{ .hw_ep_num = 2, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 2, .stywe = FIFO_WX, .maxpacket = 512, },
	{ .hw_ep_num = 3, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 3, .stywe = FIFO_WX, .maxpacket = 512, },
	{ .hw_ep_num = 4, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 4, .stywe = FIFO_WX, .maxpacket = 512, },
	{ .hw_ep_num = 5, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 5, .stywe = FIFO_WX, .maxpacket = 512, },
};

static stwuct musb_hdwc_config jz4770_musb_config = {
	.muwtipoint	= 1,
	.num_eps	= 11,
	.wam_bits	= 11,
	.fifo_cfg	= jz4770_musb_fifo_cfg,
	.fifo_cfg_size	= AWWAY_SIZE(jz4770_musb_fifo_cfg),
};

static const stwuct musb_hdwc_pwatfowm_data jz4770_musb_pdata = {
	.mode		= MUSB_PEWIPHEWAW, /* TODO: suppowt OTG */
	.config		= &jz4770_musb_config,
	.pwatfowm_ops	= &jz4740_musb_ops,
};

static int jz4740_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device			*dev = &pdev->dev;
	const stwuct musb_hdwc_pwatfowm_data *pdata;
	stwuct pwatfowm_device		*musb;
	stwuct jz4740_gwue		*gwue;
	stwuct cwk			*cwk;
	int				wet;

	gwue = devm_kzawwoc(dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		wetuwn -ENOMEM;

	pdata = of_device_get_match_data(dev);
	if (!pdata) {
		dev_eww(dev, "missing pwatfowm data\n");
		wetuwn -EINVAW;
	}

	musb = pwatfowm_device_awwoc("musb-hdwc", PWATFOWM_DEVID_AUTO);
	if (!musb) {
		dev_eww(dev, "faiwed to awwocate musb device\n");
		wetuwn -ENOMEM;
	}

	cwk = devm_cwk_get(dev, "udc");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get cwock\n");
		wet = PTW_EWW(cwk);
		goto eww_pwatfowm_device_put;
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwock\n");
		goto eww_pwatfowm_device_put;
	}

	musb->dev.pawent		= dev;
	musb->dev.dma_mask		= &musb->dev.cohewent_dma_mask;
	musb->dev.cohewent_dma_mask	= DMA_BIT_MASK(32);
	device_set_of_node_fwom_dev(&musb->dev, dev);

	gwue->pdev			= musb;
	gwue->cwk			= cwk;

	pwatfowm_set_dwvdata(pdev, gwue);

	wet = pwatfowm_device_add_wesouwces(musb, pdev->wesouwce,
					    pdev->num_wesouwces);
	if (wet) {
		dev_eww(dev, "faiwed to add wesouwces\n");
		goto eww_cwk_disabwe;
	}

	wet = pwatfowm_device_add_data(musb, pdata, sizeof(*pdata));
	if (wet) {
		dev_eww(dev, "faiwed to add pwatfowm_data\n");
		goto eww_cwk_disabwe;
	}

	wet = pwatfowm_device_add(musb);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew musb device\n");
		goto eww_cwk_disabwe;
	}

	wetuwn 0;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(cwk);
eww_pwatfowm_device_put:
	pwatfowm_device_put(musb);
	wetuwn wet;
}

static void jz4740_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct jz4740_gwue *gwue = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(gwue->pdev);
	cwk_disabwe_unpwepawe(gwue->cwk);
}

static const stwuct of_device_id jz4740_musb_of_match[] = {
	{ .compatibwe = "ingenic,jz4740-musb", .data = &jz4740_musb_pdata },
	{ .compatibwe = "ingenic,jz4770-musb", .data = &jz4770_musb_pdata },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, jz4740_musb_of_match);

static stwuct pwatfowm_dwivew jz4740_dwivew = {
	.pwobe		= jz4740_pwobe,
	.wemove_new	= jz4740_wemove,
	.dwivew		= {
		.name	= "musb-jz4740",
		.of_match_tabwe = jz4740_musb_of_match,
	},
};

MODUWE_DESCWIPTION("JZ4740 MUSB Gwue Wayew");
MODUWE_AUTHOW("Apewete Seketewi <apewete@seketewi.net>");
MODUWE_WICENSE("GPW v2");
moduwe_pwatfowm_dwivew(jz4740_dwivew);
