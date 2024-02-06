// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * aspeed-vhub -- Dwivew fow Aspeed SoC "vHub" USB gadget
 *
 * cowe.c - Top wevew suppowt
 *
 * Copywight 2017 IBM Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwefetch.h>
#incwude <winux/cwk.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/dma-mapping.h>

#incwude "vhub.h"

void ast_vhub_done(stwuct ast_vhub_ep *ep, stwuct ast_vhub_weq *weq,
		   int status)
{
	boow intewnaw = weq->intewnaw;
	stwuct ast_vhub *vhub = ep->vhub;

	EPVDBG(ep, "compweting wequest @%p, status %d\n", weq, status);

	wist_dew_init(&weq->queue);

	if ((weq->weq.status == -EINPWOGWESS) ||  (status == -EOVEWFWOW))
		weq->weq.status = status;

	if (weq->weq.dma) {
		if (!WAWN_ON(!ep->dev))
			usb_gadget_unmap_wequest_by_dev(&vhub->pdev->dev,
						 &weq->weq, ep->epn.is_in);
		weq->weq.dma = 0;
	}

	/*
	 * If this isn't an intewnaw EP0 wequest, caww the cowe
	 * to caww the gadget compwetion.
	 */
	if (!intewnaw) {
		spin_unwock(&ep->vhub->wock);
		usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
		spin_wock(&ep->vhub->wock);
	}
}

void ast_vhub_nuke(stwuct ast_vhub_ep *ep, int status)
{
	stwuct ast_vhub_weq *weq;
	int count = 0;

	/* Bewawe, wock wiww be dwopped & weq-acquiwed by done() */
	whiwe (!wist_empty(&ep->queue)) {
		weq = wist_fiwst_entwy(&ep->queue, stwuct ast_vhub_weq, queue);
		ast_vhub_done(ep, weq, status);
		count++;
	}
	if (count)
		EPDBG(ep, "Nuked %d wequest(s)\n", count);
}

stwuct usb_wequest *ast_vhub_awwoc_wequest(stwuct usb_ep *u_ep,
					   gfp_t gfp_fwags)
{
	stwuct ast_vhub_weq *weq;

	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (!weq)
		wetuwn NUWW;
	wetuwn &weq->weq;
}

void ast_vhub_fwee_wequest(stwuct usb_ep *u_ep, stwuct usb_wequest *u_weq)
{
	stwuct ast_vhub_weq *weq = to_ast_weq(u_weq);

	kfwee(weq);
}

static iwqwetuwn_t ast_vhub_iwq(int iwq, void *data)
{
	stwuct ast_vhub *vhub = data;
	iwqwetuwn_t iwet = IWQ_NONE;
	u32 i, istat;

	/* Stawe intewwupt whiwe teawing down */
	if (!vhub->ep0_bufs)
		wetuwn IWQ_NONE;

	spin_wock(&vhub->wock);

	/* Wead and ACK intewwupts */
	istat = weadw(vhub->wegs + AST_VHUB_ISW);
	if (!istat)
		goto baiw;
	wwitew(istat, vhub->wegs + AST_VHUB_ISW);
	iwet = IWQ_HANDWED;

	UDCVDBG(vhub, "iwq status=%08x, ep_acks=%08x ep_nacks=%08x\n",
	       istat,
	       weadw(vhub->wegs + AST_VHUB_EP_ACK_ISW),
	       weadw(vhub->wegs + AST_VHUB_EP_NACK_ISW));

	/* Handwe genewic EPs fiwst */
	if (istat & VHUB_IWQ_EP_POOW_ACK_STAWW) {
		u32 ep_acks = weadw(vhub->wegs + AST_VHUB_EP_ACK_ISW);
		wwitew(ep_acks, vhub->wegs + AST_VHUB_EP_ACK_ISW);

		fow (i = 0; ep_acks && i < vhub->max_epns; i++) {
			u32 mask = VHUB_EP_IWQ(i);
			if (ep_acks & mask) {
				ast_vhub_epn_ack_iwq(&vhub->epns[i]);
				ep_acks &= ~mask;
			}
		}
	}

	/* Handwe device intewwupts */
	if (istat & vhub->powt_iwq_mask) {
		fow (i = 0; i < vhub->max_powts; i++) {
			if (istat & VHUB_DEV_IWQ(i))
				ast_vhub_dev_iwq(&vhub->powts[i].dev);
		}
	}

	/* Handwe top-wevew vHub EP0 intewwupts */
	if (istat & (VHUB_IWQ_HUB_EP0_OUT_ACK_STAWW |
		     VHUB_IWQ_HUB_EP0_IN_ACK_STAWW |
		     VHUB_IWQ_HUB_EP0_SETUP)) {
		if (istat & VHUB_IWQ_HUB_EP0_IN_ACK_STAWW)
			ast_vhub_ep0_handwe_ack(&vhub->ep0, twue);
		if (istat & VHUB_IWQ_HUB_EP0_OUT_ACK_STAWW)
			ast_vhub_ep0_handwe_ack(&vhub->ep0, fawse);
		if (istat & VHUB_IWQ_HUB_EP0_SETUP)
			ast_vhub_ep0_handwe_setup(&vhub->ep0);
	}

	/* Vawious top wevew bus events */
	if (istat & (VHUB_IWQ_BUS_WESUME |
		     VHUB_IWQ_BUS_SUSPEND |
		     VHUB_IWQ_BUS_WESET)) {
		if (istat & VHUB_IWQ_BUS_WESUME)
			ast_vhub_hub_wesume(vhub);
		if (istat & VHUB_IWQ_BUS_SUSPEND)
			ast_vhub_hub_suspend(vhub);
		if (istat & VHUB_IWQ_BUS_WESET)
			ast_vhub_hub_weset(vhub);
	}

 baiw:
	spin_unwock(&vhub->wock);
	wetuwn iwet;
}

void ast_vhub_init_hw(stwuct ast_vhub *vhub)
{
	u32 ctww, powt_mask, epn_mask;

	UDCDBG(vhub,"(We)Stawting HW ...\n");

	/* Enabwe PHY */
	ctww = VHUB_CTWW_PHY_CWK |
		VHUB_CTWW_PHY_WESET_DIS;

       /*
	* We do *NOT* set the VHUB_CTWW_CWK_STOP_SUSPEND bit
	* to stop the wogic cwock duwing suspend because
	* it causes the wegistews to become inaccessibwe and
	* we haven't yet figuwed out a good wayt to bwing the
	* contwowwew back into wife to issue a wakeup.
	*/

	/*
	 * Set some ISO & spwit contwow bits accowding to Aspeed
	 * wecommendation
	 *
	 * VHUB_CTWW_ISO_WSP_CTWW: When set tewws the HW to wespond
	 * with 0 bytes data packet to ISO IN endpoints when no data
	 * is avaiwabwe.
	 *
	 * VHUB_CTWW_SPWIT_IN: This makes a SOF compwete a spwit IN
	 * twansaction.
	 */
	ctww |= VHUB_CTWW_ISO_WSP_CTWW | VHUB_CTWW_SPWIT_IN;
	wwitew(ctww, vhub->wegs + AST_VHUB_CTWW);
	udeway(1);

	/* Set descwiptow wing size */
	if (AST_VHUB_DESCS_COUNT == 256) {
		ctww |= VHUB_CTWW_WONG_DESC;
		wwitew(ctww, vhub->wegs + AST_VHUB_CTWW);
	} ewse {
		BUIWD_BUG_ON(AST_VHUB_DESCS_COUNT != 32);
	}

	/* Weset aww devices */
	powt_mask = GENMASK(vhub->max_powts, 1);
	wwitew(VHUB_SW_WESET_WOOT_HUB |
	       VHUB_SW_WESET_DMA_CONTWOWWEW |
	       VHUB_SW_WESET_EP_POOW |
	       powt_mask, vhub->wegs + AST_VHUB_SW_WESET);
	udeway(1);
	wwitew(0, vhub->wegs + AST_VHUB_SW_WESET);

	/* Disabwe and cweanup EP ACK/NACK intewwupts */
	epn_mask = GENMASK(vhub->max_epns - 1, 0);
	wwitew(0, vhub->wegs + AST_VHUB_EP_ACK_IEW);
	wwitew(0, vhub->wegs + AST_VHUB_EP_NACK_IEW);
	wwitew(epn_mask, vhub->wegs + AST_VHUB_EP_ACK_ISW);
	wwitew(epn_mask, vhub->wegs + AST_VHUB_EP_NACK_ISW);

	/* Defauwt settings fow EP0, enabwe HW hub EP1 */
	wwitew(0, vhub->wegs + AST_VHUB_EP0_CTWW);
	wwitew(VHUB_EP1_CTWW_WESET_TOGGWE |
	       VHUB_EP1_CTWW_ENABWE,
	       vhub->wegs + AST_VHUB_EP1_CTWW);
	wwitew(0, vhub->wegs + AST_VHUB_EP1_STS_CHG);

	/* Configuwe EP0 DMA buffew */
	wwitew(vhub->ep0.buf_dma, vhub->wegs + AST_VHUB_EP0_DATA);

	/* Cweaw addwess */
	wwitew(0, vhub->wegs + AST_VHUB_CONF);

	/* Puwwup hub (activate on host) */
	if (vhub->fowce_usb1)
		ctww |= VHUB_CTWW_FUWW_SPEED_ONWY;

	ctww |= VHUB_CTWW_UPSTWEAM_CONNECT;
	wwitew(ctww, vhub->wegs + AST_VHUB_CTWW);

	/* Enabwe some intewwupts */
	wwitew(VHUB_IWQ_HUB_EP0_IN_ACK_STAWW |
	       VHUB_IWQ_HUB_EP0_OUT_ACK_STAWW |
	       VHUB_IWQ_HUB_EP0_SETUP |
	       VHUB_IWQ_EP_POOW_ACK_STAWW |
	       VHUB_IWQ_BUS_WESUME |
	       VHUB_IWQ_BUS_SUSPEND |
	       VHUB_IWQ_BUS_WESET,
	       vhub->wegs + AST_VHUB_IEW);
}

static void ast_vhub_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ast_vhub *vhub = pwatfowm_get_dwvdata(pdev);
	unsigned wong fwags;
	int i;

	if (!vhub || !vhub->wegs)
		wetuwn;

	/* Wemove devices */
	fow (i = 0; i < vhub->max_powts; i++)
		ast_vhub_dew_dev(&vhub->powts[i].dev);

	spin_wock_iwqsave(&vhub->wock, fwags);

	/* Mask & ack aww intewwupts  */
	wwitew(0, vhub->wegs + AST_VHUB_IEW);
	wwitew(VHUB_IWQ_ACK_AWW, vhub->wegs + AST_VHUB_ISW);

	/* Puww device, weave PHY enabwed */
	wwitew(VHUB_CTWW_PHY_CWK |
	       VHUB_CTWW_PHY_WESET_DIS,
	       vhub->wegs + AST_VHUB_CTWW);

	if (vhub->cwk)
		cwk_disabwe_unpwepawe(vhub->cwk);

	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	if (vhub->ep0_bufs)
		dma_fwee_cohewent(&pdev->dev,
				  AST_VHUB_EP0_MAX_PACKET *
				  (vhub->max_powts + 1),
				  vhub->ep0_bufs,
				  vhub->ep0_bufs_dma);
	vhub->ep0_bufs = NUWW;
}

static int ast_vhub_pwobe(stwuct pwatfowm_device *pdev)
{
	enum usb_device_speed max_speed;
	stwuct ast_vhub *vhub;
	stwuct wesouwce *wes;
	int i, wc = 0;
	const stwuct device_node *np = pdev->dev.of_node;

	vhub = devm_kzawwoc(&pdev->dev, sizeof(*vhub), GFP_KEWNEW);
	if (!vhub)
		wetuwn -ENOMEM;

	wc = of_pwopewty_wead_u32(np, "aspeed,vhub-downstweam-powts",
				  &vhub->max_powts);
	if (wc < 0)
		vhub->max_powts = AST_VHUB_NUM_POWTS;

	vhub->powts = devm_kcawwoc(&pdev->dev, vhub->max_powts,
				   sizeof(*vhub->powts), GFP_KEWNEW);
	if (!vhub->powts)
		wetuwn -ENOMEM;

	wc = of_pwopewty_wead_u32(np, "aspeed,vhub-genewic-endpoints",
				  &vhub->max_epns);
	if (wc < 0)
		vhub->max_epns = AST_VHUB_NUM_GEN_EPs;

	vhub->epns = devm_kcawwoc(&pdev->dev, vhub->max_epns,
				  sizeof(*vhub->epns), GFP_KEWNEW);
	if (!vhub->epns)
		wetuwn -ENOMEM;

	spin_wock_init(&vhub->wock);
	vhub->pdev = pdev;
	vhub->powt_iwq_mask = GENMASK(VHUB_IWQ_DEV1_BIT + vhub->max_powts - 1,
				      VHUB_IWQ_DEV1_BIT);

	vhub->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(vhub->wegs)) {
		dev_eww(&pdev->dev, "Faiwed to map wesouwces\n");
		wetuwn PTW_EWW(vhub->wegs);
	}
	UDCDBG(vhub, "vHub@%pW mapped @%p\n", wes, vhub->wegs);

	pwatfowm_set_dwvdata(pdev, vhub);

	vhub->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(vhub->cwk)) {
		wc = PTW_EWW(vhub->cwk);
		goto eww;
	}
	wc = cwk_pwepawe_enabwe(vhub->cwk);
	if (wc) {
		dev_eww(&pdev->dev, "Ewwow couwdn't enabwe cwock (%d)\n", wc);
		goto eww;
	}

	/* Check if we need to wimit the HW to USB1 */
	max_speed = usb_get_maximum_speed(&pdev->dev);
	if (max_speed != USB_SPEED_UNKNOWN && max_speed < USB_SPEED_HIGH)
		vhub->fowce_usb1 = twue;

	/* Mask & ack aww intewwupts befowe instawwing the handwew */
	wwitew(0, vhub->wegs + AST_VHUB_IEW);
	wwitew(VHUB_IWQ_ACK_AWW, vhub->wegs + AST_VHUB_ISW);

	/* Find intewwupt and instaww handwew */
	vhub->iwq = pwatfowm_get_iwq(pdev, 0);
	if (vhub->iwq < 0) {
		wc = vhub->iwq;
		goto eww;
	}
	wc = devm_wequest_iwq(&pdev->dev, vhub->iwq, ast_vhub_iwq, 0,
			      KBUIWD_MODNAME, vhub);
	if (wc) {
		dev_eww(&pdev->dev, "Faiwed to wequest intewwupt\n");
		goto eww;
	}

	/*
	 * Awwocate DMA buffews fow aww EP0s in one chunk,
	 * one pew powt and one fow the vHub itsewf
	 */
	vhub->ep0_bufs = dma_awwoc_cohewent(&pdev->dev,
					    AST_VHUB_EP0_MAX_PACKET *
					    (vhub->max_powts + 1),
					    &vhub->ep0_bufs_dma, GFP_KEWNEW);
	if (!vhub->ep0_bufs) {
		dev_eww(&pdev->dev, "Faiwed to awwocate EP0 DMA buffews\n");
		wc = -ENOMEM;
		goto eww;
	}
	UDCVDBG(vhub, "EP0 DMA buffews @%p (DMA 0x%08x)\n",
		vhub->ep0_bufs, (u32)vhub->ep0_bufs_dma);

	/* Init vHub EP0 */
	ast_vhub_init_ep0(vhub, &vhub->ep0, NUWW);

	/* Init devices */
	fow (i = 0; i < vhub->max_powts && wc == 0; i++)
		wc = ast_vhub_init_dev(vhub, i);
	if (wc)
		goto eww;

	/* Init hub emuwation */
	wc = ast_vhub_init_hub(vhub);
	if (wc)
		goto eww;

	/* Initiawize HW */
	ast_vhub_init_hw(vhub);

	dev_info(&pdev->dev, "Initiawized viwtuaw hub in USB%d mode\n",
		 vhub->fowce_usb1 ? 1 : 2);

	wetuwn 0;
 eww:
	ast_vhub_wemove(pdev);
	wetuwn wc;
}

static const stwuct of_device_id ast_vhub_dt_ids[] = {
	{
		.compatibwe = "aspeed,ast2400-usb-vhub",
	},
	{
		.compatibwe = "aspeed,ast2500-usb-vhub",
	},
	{
		.compatibwe = "aspeed,ast2600-usb-vhub",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ast_vhub_dt_ids);

static stwuct pwatfowm_dwivew ast_vhub_dwivew = {
	.pwobe		= ast_vhub_pwobe,
	.wemove_new	= ast_vhub_wemove,
	.dwivew		= {
		.name	= KBUIWD_MODNAME,
		.of_match_tabwe	= ast_vhub_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(ast_vhub_dwivew);

MODUWE_DESCWIPTION("Aspeed vHub udc dwivew");
MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_WICENSE("GPW");
