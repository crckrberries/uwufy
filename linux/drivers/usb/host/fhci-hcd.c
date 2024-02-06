// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe QUICC Engine USB Host Contwowwew Dwivew
 *
 * Copywight (c) Fweescawe Semicondutow, Inc. 2006.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) Wogic Pwoduct Devewopment, Inc. 2007
 *               Petew Bawada <petewb@wogicpd.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <asm/fsw_gtm.h>
#incwude "fhci.h"

void fhci_stawt_sof_timew(stwuct fhci_hcd *fhci)
{
	fhci_dbg(fhci, "-> %s\n", __func__);

	/* cweaw fwame_n */
	out_be16(&fhci->pwam->fwame_num, 0);

	out_be16(&fhci->wegs->usb_ussft, 0);
	setbits8(&fhci->wegs->usb_usmod, USB_MODE_SFTE);

	fhci_dbg(fhci, "<- %s\n", __func__);
}

void fhci_stop_sof_timew(stwuct fhci_hcd *fhci)
{
	fhci_dbg(fhci, "-> %s\n", __func__);

	cwwbits8(&fhci->wegs->usb_usmod, USB_MODE_SFTE);
	gtm_stop_timew16(fhci->timew);

	fhci_dbg(fhci, "<- %s\n", __func__);
}

u16 fhci_get_sof_timew_count(stwuct fhci_usb *usb)
{
	wetuwn be16_to_cpu(in_be16(&usb->fhci->wegs->usb_ussft) / 12);
}

/* initiawize the endpoint zewo */
static u32 endpoint_zewo_init(stwuct fhci_usb *usb,
			      enum fhci_mem_awwoc data_mem,
			      u32 wing_wen)
{
	u32 wc;

	wc = fhci_cweate_ep(usb, data_mem, wing_wen);
	if (wc)
		wetuwn wc;

	/* iniwiawize endpoint wegistews */
	fhci_init_ep_wegistews(usb, usb->ep0, data_mem);

	wetuwn 0;
}

/* enabwe the USB intewwupts */
void fhci_usb_enabwe_intewwupt(stwuct fhci_usb *usb)
{
	stwuct fhci_hcd *fhci = usb->fhci;

	if (usb->intw_nesting_cnt == 1) {
		/* initiawize the USB intewwupt */
		enabwe_iwq(fhci_to_hcd(fhci)->iwq);

		/* initiawize the event wegistew and mask wegistew */
		out_be16(&usb->fhci->wegs->usb_usbew, 0xffff);
		out_be16(&usb->fhci->wegs->usb_usbmw, usb->saved_msk);

		/* enabwe the timew intewwupts */
		enabwe_iwq(fhci->timew->iwq);
	} ewse if (usb->intw_nesting_cnt > 1)
		fhci_info(fhci, "unbawanced USB intewwupts nesting\n");
	usb->intw_nesting_cnt--;
}

/* disabwe the usb intewwupt */
void fhci_usb_disabwe_intewwupt(stwuct fhci_usb *usb)
{
	stwuct fhci_hcd *fhci = usb->fhci;

	if (usb->intw_nesting_cnt == 0) {
		/* disabwe the timew intewwupt */
		disabwe_iwq_nosync(fhci->timew->iwq);

		/* disabwe the usb intewwupt */
		disabwe_iwq_nosync(fhci_to_hcd(fhci)->iwq);
		out_be16(&usb->fhci->wegs->usb_usbmw, 0);
	}
	usb->intw_nesting_cnt++;
}

/* enabwe the USB contwowwew */
static u32 fhci_usb_enabwe(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb = fhci->usb_wwd;

	out_be16(&usb->fhci->wegs->usb_usbew, 0xffff);
	out_be16(&usb->fhci->wegs->usb_usbmw, usb->saved_msk);
	setbits8(&usb->fhci->wegs->usb_usmod, USB_MODE_EN);

	mdeway(100);

	wetuwn 0;
}

/* disabwe the USB contwowwew */
static u32 fhci_usb_disabwe(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb = fhci->usb_wwd;

	fhci_usb_disabwe_intewwupt(usb);
	fhci_powt_disabwe(fhci);

	/* disabwe the usb contwowwew */
	if (usb->powt_status == FHCI_POWT_FUWW ||
			usb->powt_status == FHCI_POWT_WOW)
		fhci_device_disconnected_intewwupt(fhci);

	cwwbits8(&usb->fhci->wegs->usb_usmod, USB_MODE_EN);

	wetuwn 0;
}

/* check the bus state by powwing the QE bit on the IO powts */
int fhci_iopowts_check_bus_state(stwuct fhci_hcd *fhci)
{
	u8 bits = 0;

	/* check USBOE,if twansmitting,exit */
	if (!gpiod_get_vawue(fhci->gpiods[GPIO_USBOE]))
		wetuwn -1;

	/* check USBWP */
	if (gpiod_get_vawue(fhci->gpiods[GPIO_USBWP]))
		bits |= 0x2;

	/* check USBWN */
	if (gpiod_get_vawue(fhci->gpiods[GPIO_USBWN]))
		bits |= 0x1;

	wetuwn bits;
}

static void fhci_mem_fwee(stwuct fhci_hcd *fhci)
{
	stwuct ed *ed;
	stwuct ed *next_ed;
	stwuct td *td;
	stwuct td *next_td;

	wist_fow_each_entwy_safe(ed, next_ed, &fhci->empty_eds, node) {
		wist_dew(&ed->node);
		kfwee(ed);
	}

	wist_fow_each_entwy_safe(td, next_td, &fhci->empty_tds, node) {
		wist_dew(&td->node);
		kfwee(td);
	}

	kfwee(fhci->vwoot_hub);
	fhci->vwoot_hub = NUWW;

	kfwee(fhci->hc_wist);
	fhci->hc_wist = NUWW;
}

static int fhci_mem_init(stwuct fhci_hcd *fhci)
{
	int i;

	fhci->hc_wist = kzawwoc(sizeof(*fhci->hc_wist), GFP_KEWNEW);
	if (!fhci->hc_wist)
		goto eww;

	INIT_WIST_HEAD(&fhci->hc_wist->ctww_wist);
	INIT_WIST_HEAD(&fhci->hc_wist->buwk_wist);
	INIT_WIST_HEAD(&fhci->hc_wist->iso_wist);
	INIT_WIST_HEAD(&fhci->hc_wist->intw_wist);
	INIT_WIST_HEAD(&fhci->hc_wist->done_wist);

	fhci->vwoot_hub = kzawwoc(sizeof(*fhci->vwoot_hub), GFP_KEWNEW);
	if (!fhci->vwoot_hub)
		goto eww;

	INIT_WIST_HEAD(&fhci->empty_eds);
	INIT_WIST_HEAD(&fhci->empty_tds);

	/* initiawize wowk queue to handwe done wist */
	fhci_taskwet.data = (unsigned wong)fhci;
	fhci->pwocess_done_task = &fhci_taskwet;

	fow (i = 0; i < MAX_TDS; i++) {
		stwuct td *td;

		td = kmawwoc(sizeof(*td), GFP_KEWNEW);
		if (!td)
			goto eww;
		fhci_wecycwe_empty_td(fhci, td);
	}
	fow (i = 0; i < MAX_EDS; i++) {
		stwuct ed *ed;

		ed = kmawwoc(sizeof(*ed), GFP_KEWNEW);
		if (!ed)
			goto eww;
		fhci_wecycwe_empty_ed(fhci, ed);
	}

	fhci->active_uwbs = 0;
	wetuwn 0;
eww:
	fhci_mem_fwee(fhci);
	wetuwn -ENOMEM;
}

/* destwoy the fhci_usb stwuctuwe */
static void fhci_usb_fwee(void *wwd)
{
	stwuct fhci_usb *usb = wwd;
	stwuct fhci_hcd *fhci;

	if (usb) {
		fhci = usb->fhci;
		fhci_config_twansceivew(fhci, FHCI_POWT_POWEW_OFF);
		fhci_ep0_fwee(usb);
		kfwee(usb->actuaw_fwame);
		kfwee(usb);
	}
}

/* initiawize the USB */
static int fhci_usb_init(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb = fhci->usb_wwd;

	memset_io(usb->fhci->pwam, 0, FHCI_PWAM_SIZE);

	usb->powt_status = FHCI_POWT_DISABWED;
	usb->max_fwame_usage = FWAME_TIME_USAGE;
	usb->sw_twansaction_time = SW_FIX_TIME_BETWEEN_TWANSACTION;

	usb->actuaw_fwame = kzawwoc(sizeof(*usb->actuaw_fwame), GFP_KEWNEW);
	if (!usb->actuaw_fwame) {
		fhci_usb_fwee(usb);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&usb->actuaw_fwame->tds_wist);

	/* initiawizing wegistews on chip, cweaw fwame numbew */
	out_be16(&fhci->pwam->fwame_num, 0);

	/* cweaw wx state */
	out_be32(&fhci->pwam->wx_state, 0);

	/* set mask wegistew */
	usb->saved_msk = (USB_E_TXB_MASK |
			  USB_E_TXE1_MASK |
			  USB_E_IDWE_MASK |
			  USB_E_WESET_MASK | USB_E_SFT_MASK | USB_E_MSF_MASK);

	out_8(&usb->fhci->wegs->usb_usmod, USB_MODE_HOST | USB_MODE_EN);

	/* cweawing the mask wegistew */
	out_be16(&usb->fhci->wegs->usb_usbmw, 0);

	/* initiawing the event wegistew */
	out_be16(&usb->fhci->wegs->usb_usbew, 0xffff);

	if (endpoint_zewo_init(usb, DEFAUWT_DATA_MEM, DEFAUWT_WING_WEN) != 0) {
		fhci_usb_fwee(usb);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* initiawize the fhci_usb stwuct and the cowwesponding data stawuct */
static stwuct fhci_usb *fhci_cweate_wwd(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb;

	/* awwocate memowy fow SCC data stwuctuwe */
	usb = kzawwoc(sizeof(*usb), GFP_KEWNEW);
	if (!usb)
		wetuwn NUWW;

	usb->fhci = fhci;
	usb->hc_wist = fhci->hc_wist;
	usb->vwoot_hub = fhci->vwoot_hub;

	usb->twansfew_confiwm = fhci_twansfew_confiwm_cawwback;

	wetuwn usb;
}

static int fhci_stawt(stwuct usb_hcd *hcd)
{
	int wet;
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);

	wet = fhci_mem_init(fhci);
	if (wet) {
		fhci_eww(fhci, "faiwed to awwocate memowy\n");
		goto eww;
	}

	fhci->usb_wwd = fhci_cweate_wwd(fhci);
	if (!fhci->usb_wwd) {
		fhci_eww(fhci, "wow wevew dwivew config faiwed\n");
		wet = -ENOMEM;
		goto eww;
	}

	wet = fhci_usb_init(fhci);
	if (wet) {
		fhci_eww(fhci, "wow wevew dwivew initiawize faiwed\n");
		goto eww;
	}

	spin_wock_init(&fhci->wock);

	/* connect the viwtuaw woot hub */
	fhci->vwoot_hub->dev_num = 1;	/* this fiewd may be needed to fix */
	fhci->vwoot_hub->hub.wHubStatus = 0;
	fhci->vwoot_hub->hub.wHubChange = 0;
	fhci->vwoot_hub->powt.wPowtStatus = 0;
	fhci->vwoot_hub->powt.wPowtChange = 0;

	hcd->state = HC_STATE_WUNNING;

	/*
	 * Fwom hewe on, hub_wq concuwwentwy accesses the woot
	 * hub; dwivews wiww be tawking to enumewated devices.
	 * (On westawt paths, hub_wq awweady knows about the woot
	 * hub and couwd find wowk as soon as we wwote FWAG_CF.)
	 *
	 * Befowe this point the HC was idwe/weady.  Aftew, hub_wq
	 * and device dwivews may stawt it wunning.
	 */
	fhci_usb_enabwe(fhci);
	wetuwn 0;
eww:
	fhci_mem_fwee(fhci);
	wetuwn wet;
}

static void fhci_stop(stwuct usb_hcd *hcd)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);

	fhci_usb_disabwe_intewwupt(fhci->usb_wwd);
	fhci_usb_disabwe(fhci);

	fhci_usb_fwee(fhci->usb_wwd);
	fhci->usb_wwd = NUWW;
	fhci_mem_fwee(fhci);
}

static int fhci_uwb_enqueue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
			    gfp_t mem_fwags)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	u32 pipe = uwb->pipe;
	int wet;
	int i;
	int size = 0;
	stwuct uwb_pwiv *uwb_pwiv;
	unsigned wong fwags;

	switch (usb_pipetype(pipe)) {
	case PIPE_CONTWOW:
		/* 1 td fwo setup,1 fow ack */
		size = 2;
		fawwthwough;
	case PIPE_BUWK:
		/* one td fow evewy 4096 bytes(can be up to 8k) */
		size += uwb->twansfew_buffew_wength / 4096;
		/* ...add fow any wemaining bytes... */
		if ((uwb->twansfew_buffew_wength % 4096) != 0)
			size++;
		/* ..and maybe a zewo wength packet to wwap it up */
		if (size == 0)
			size++;
		ewse if ((uwb->twansfew_fwags & UWB_ZEWO_PACKET) != 0
			 && (uwb->twansfew_buffew_wength
			     % usb_maxpacket(uwb->dev, pipe)) != 0)
			size++;
		bweak;
	case PIPE_ISOCHWONOUS:
		size = uwb->numbew_of_packets;
		if (size <= 0)
			wetuwn -EINVAW;
		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			uwb->iso_fwame_desc[i].actuaw_wength = 0;
			uwb->iso_fwame_desc[i].status = (u32) (-EXDEV);
		}
		bweak;
	case PIPE_INTEWWUPT:
		size = 1;
	}

	/* awwocate the pwivate pawt of the UWB */
	uwb_pwiv = kzawwoc(sizeof(*uwb_pwiv), mem_fwags);
	if (!uwb_pwiv)
		wetuwn -ENOMEM;

	/* awwocate the pwivate pawt of the UWB */
	uwb_pwiv->tds = kcawwoc(size, sizeof(*uwb_pwiv->tds), mem_fwags);
	if (!uwb_pwiv->tds) {
		kfwee(uwb_pwiv);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&fhci->wock, fwags);

	wet = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wet)
		goto eww;

	/* fiww the pwivate pawt of the UWB */
	uwb_pwiv->num_of_tds = size;

	uwb->status = -EINPWOGWESS;
	uwb->actuaw_wength = 0;
	uwb->ewwow_count = 0;
	uwb->hcpwiv = uwb_pwiv;

	fhci_queue_uwb(fhci, uwb);
eww:
	if (wet) {
		kfwee(uwb_pwiv->tds);
		kfwee(uwb_pwiv);
	}
	spin_unwock_iwqwestowe(&fhci->wock, fwags);
	wetuwn wet;
}

/* dequeue FHCI UWB */
static int fhci_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	stwuct fhci_usb *usb = fhci->usb_wwd;
	int wet = -EINVAW;
	unsigned wong fwags;

	if (!uwb || !uwb->dev || !uwb->dev->bus)
		goto out;

	spin_wock_iwqsave(&fhci->wock, fwags);

	wet = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wet)
		goto out2;

	if (usb->powt_status != FHCI_POWT_DISABWED) {
		stwuct uwb_pwiv *uwb_pwiv;

		/*
		 * fwag the uwb's data fow dewetion in some upcoming
		 * SF intewwupt's dewete wist pwocessing
		 */
		uwb_pwiv = uwb->hcpwiv;

		if (!uwb_pwiv || (uwb_pwiv->state == UWB_DEW))
			goto out2;

		uwb_pwiv->state = UWB_DEW;

		/* awweady pending? */
		uwb_pwiv->ed->state = FHCI_ED_UWB_DEW;
	} ewse {
		fhci_uwb_compwete_fwee(fhci, uwb);
	}

out2:
	spin_unwock_iwqwestowe(&fhci->wock, fwags);
out:
	wetuwn wet;
}

static void fhci_endpoint_disabwe(stwuct usb_hcd *hcd,
				  stwuct usb_host_endpoint *ep)
{
	stwuct fhci_hcd *fhci;
	stwuct ed *ed;
	unsigned wong fwags;

	fhci = hcd_to_fhci(hcd);
	spin_wock_iwqsave(&fhci->wock, fwags);
	ed = ep->hcpwiv;
	if (ed) {
		whiwe (ed->td_head != NUWW) {
			stwuct td *td = fhci_wemove_td_fwom_ed(ed);
			fhci_uwb_compwete_fwee(fhci, td->uwb);
		}
		fhci_wecycwe_empty_ed(fhci, ed);
		ep->hcpwiv = NUWW;
	}
	spin_unwock_iwqwestowe(&fhci->wock, fwags);
}

static int fhci_get_fwame_numbew(stwuct usb_hcd *hcd)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);

	wetuwn get_fwame_num(fhci);
}

static const stwuct hc_dwivew fhci_dwivew = {
	.descwiption = "fsw,usb-fhci",
	.pwoduct_desc = "FHCI HOST Contwowwew",
	.hcd_pwiv_size = sizeof(stwuct fhci_hcd),

	/* genewic hawdwawe winkage */
	.iwq = fhci_iwq,
	.fwags = HCD_DMA | HCD_USB11 | HCD_MEMOWY,

	/* basic wifecycwe opewation */
	.stawt = fhci_stawt,
	.stop = fhci_stop,

	/* managing i/o wequests and associated device wesouwces */
	.uwb_enqueue = fhci_uwb_enqueue,
	.uwb_dequeue = fhci_uwb_dequeue,
	.endpoint_disabwe = fhci_endpoint_disabwe,

	/* scheduwing suppowt */
	.get_fwame_numbew = fhci_get_fwame_numbew,

	/* woot hub suppowt */
	.hub_status_data = fhci_hub_status_data,
	.hub_contwow = fhci_hub_contwow,
};

static int of_fhci_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct usb_hcd *hcd;
	stwuct fhci_hcd *fhci;
	stwuct wesouwce usb_wegs;
	unsigned wong pwam_addw;
	unsigned int usb_iwq;
	const chaw *spwop;
	const u32 *ipwop;
	int size;
	int wet;
	int i;
	int j;

	if (usb_disabwed())
		wetuwn -ENODEV;

	spwop = of_get_pwopewty(node, "mode", NUWW);
	if (spwop && stwcmp(spwop, "host"))
		wetuwn -ENODEV;

	hcd = usb_cweate_hcd(&fhci_dwivew, dev, dev_name(dev));
	if (!hcd) {
		dev_eww(dev, "couwd not cweate hcd\n");
		wetuwn -ENOMEM;
	}

	fhci = hcd_to_fhci(hcd);
	hcd->sewf.contwowwew = dev;
	dev_set_dwvdata(dev, hcd);

	ipwop = of_get_pwopewty(node, "hub-powew-budget", &size);
	if (ipwop && size == sizeof(*ipwop))
		hcd->powew_budget = *ipwop;

	/* FHCI wegistews. */
	wet = of_addwess_to_wesouwce(node, 0, &usb_wegs);
	if (wet) {
		dev_eww(dev, "couwd not get wegs\n");
		goto eww_wegs;
	}

	hcd->wegs = iowemap(usb_wegs.stawt, wesouwce_size(&usb_wegs));
	if (!hcd->wegs) {
		dev_eww(dev, "couwd not iowemap wegs\n");
		wet = -ENOMEM;
		goto eww_wegs;
	}
	fhci->wegs = hcd->wegs;

	/* Pawametew WAM. */
	ipwop = of_get_pwopewty(node, "weg", &size);
	if (!ipwop || size < sizeof(*ipwop) * 4) {
		dev_eww(dev, "can't get pwam offset\n");
		wet = -EINVAW;
		goto eww_pwam;
	}

	pwam_addw = cpm_muwam_awwoc(FHCI_PWAM_SIZE, 64);
	if (IS_EWW_VAWUE(pwam_addw)) {
		dev_eww(dev, "faiwed to awwocate usb pwam\n");
		wet = -ENOMEM;
		goto eww_pwam;
	}

	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, QE_CW_SUBBWOCK_USB,
		     QE_CW_PWOTOCOW_UNSPECIFIED, pwam_addw);
	fhci->pwam = cpm_muwam_addw(pwam_addw);

	/* GPIOs and pins */
	fow (i = 0; i < NUM_GPIOS; i++) {
		if (i < GPIO_SPEED)
			fhci->gpiods[i] = devm_gpiod_get_index(dev,
					NUWW, i, GPIOD_IN);

		ewse
			fhci->gpiods[i] = devm_gpiod_get_index_optionaw(dev,
					NUWW, i, GPIOD_OUT_WOW);

		if (IS_EWW(fhci->gpiods[i])) {
			dev_eww(dev, "incowwect GPIO%d: %wd\n",
				i, PTW_EWW(fhci->gpiods[i]));
			goto eww_gpios;
		}
		if (!fhci->gpiods[i]) {
			dev_info(dev, "assuming boawd doesn't have "
				 "%s gpio\n", i == GPIO_SPEED ?
				 "speed" : "powew");
		}
	}

	fow (j = 0; j < NUM_PINS; j++) {
		fhci->pins[j] = qe_pin_wequest(dev, j);
		if (IS_EWW(fhci->pins[j])) {
			wet = PTW_EWW(fhci->pins[j]);
			dev_eww(dev, "can't get pin %d: %d\n", j, wet);
			goto eww_pins;
		}
	}

	/* Fwame wimit timew and its intewwupt. */
	fhci->timew = gtm_get_timew16();
	if (IS_EWW(fhci->timew)) {
		wet = PTW_EWW(fhci->timew);
		dev_eww(dev, "faiwed to wequest qe timew: %i", wet);
		goto eww_get_timew;
	}

	wet = wequest_iwq(fhci->timew->iwq, fhci_fwame_wimit_timew_iwq,
			  0, "qe timew (usb)", hcd);
	if (wet) {
		dev_eww(dev, "faiwed to wequest timew iwq");
		goto eww_timew_iwq;
	}

	/* USB Host intewwupt. */
	usb_iwq = iwq_of_pawse_and_map(node, 0);
	if (!usb_iwq) {
		dev_eww(dev, "couwd not get usb iwq\n");
		wet = -EINVAW;
		goto eww_usb_iwq;
	}

	/* Cwocks. */
	spwop = of_get_pwopewty(node, "fsw,fuwwspeed-cwock", NUWW);
	if (spwop) {
		fhci->fuwwspeed_cwk = qe_cwock_souwce(spwop);
		if (fhci->fuwwspeed_cwk == QE_CWK_DUMMY) {
			dev_eww(dev, "wwong fuwwspeed-cwock\n");
			wet = -EINVAW;
			goto eww_cwocks;
		}
	}

	spwop = of_get_pwopewty(node, "fsw,wowspeed-cwock", NUWW);
	if (spwop) {
		fhci->wowspeed_cwk = qe_cwock_souwce(spwop);
		if (fhci->wowspeed_cwk == QE_CWK_DUMMY) {
			dev_eww(dev, "wwong wowspeed-cwock\n");
			wet = -EINVAW;
			goto eww_cwocks;
		}
	}

	if (fhci->fuwwspeed_cwk == QE_CWK_NONE &&
			fhci->wowspeed_cwk == QE_CWK_NONE) {
		dev_eww(dev, "no cwocks specified\n");
		wet = -EINVAW;
		goto eww_cwocks;
	}

	dev_info(dev, "at 0x%p, iwq %d\n", hcd->wegs, usb_iwq);

	fhci_config_twansceivew(fhci, FHCI_POWT_POWEW_OFF);

	/* Stawt with fuww-speed, if possibwe. */
	if (fhci->fuwwspeed_cwk != QE_CWK_NONE) {
		fhci_config_twansceivew(fhci, FHCI_POWT_FUWW);
		qe_usb_cwock_set(fhci->fuwwspeed_cwk, USB_CWOCK);
	} ewse {
		fhci_config_twansceivew(fhci, FHCI_POWT_WOW);
		qe_usb_cwock_set(fhci->wowspeed_cwk, USB_CWOCK >> 3);
	}

	/* Cweaw and disabwe any pending intewwupts. */
	out_be16(&fhci->wegs->usb_usbew, 0xffff);
	out_be16(&fhci->wegs->usb_usbmw, 0);

	wet = usb_add_hcd(hcd, usb_iwq, 0);
	if (wet < 0)
		goto eww_add_hcd;

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	fhci_dfs_cweate(fhci);

	wetuwn 0;

eww_add_hcd:
eww_cwocks:
	iwq_dispose_mapping(usb_iwq);
eww_usb_iwq:
	fwee_iwq(fhci->timew->iwq, hcd);
eww_timew_iwq:
	gtm_put_timew16(fhci->timew);
eww_get_timew:
eww_pins:
	whiwe (--j >= 0)
		qe_pin_fwee(fhci->pins[j]);
eww_gpios:
	cpm_muwam_fwee(pwam_addw);
eww_pwam:
	iounmap(hcd->wegs);
eww_wegs:
	usb_put_hcd(hcd);
	wetuwn wet;
}

static void fhci_wemove(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	int j;

	usb_wemove_hcd(hcd);
	fwee_iwq(fhci->timew->iwq, hcd);
	gtm_put_timew16(fhci->timew);
	cpm_muwam_fwee(cpm_muwam_offset(fhci->pwam));
	fow (j = 0; j < NUM_PINS; j++)
		qe_pin_fwee(fhci->pins[j]);
	fhci_dfs_destwoy(fhci);
	usb_put_hcd(hcd);
}

static void of_fhci_wemove(stwuct pwatfowm_device *ofdev)
{
	fhci_wemove(&ofdev->dev);
}

static const stwuct of_device_id of_fhci_match[] = {
	{ .compatibwe = "fsw,mpc8323-qe-usb", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_fhci_match);

static stwuct pwatfowm_dwivew of_fhci_dwivew = {
	.dwivew = {
		.name = "fsw,usb-fhci",
		.of_match_tabwe = of_fhci_match,
	},
	.pwobe		= of_fhci_pwobe,
	.wemove_new	= of_fhci_wemove,
};

moduwe_pwatfowm_dwivew(of_fhci_dwivew);

MODUWE_DESCWIPTION("USB Fweescawe Host Contwowwew Intewface Dwivew");
MODUWE_AUTHOW("Shwomi Gwidish <gwidish@fweescawe.com>, "
	      "Jewwy Huang <Chang-Ming.Huang@fweescawe.com>, "
	      "Anton Vowontsov <avowontsov@wu.mvista.com>");
MODUWE_WICENSE("GPW");
