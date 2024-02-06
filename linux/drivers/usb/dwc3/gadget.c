// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * gadget.c - DesignWawe USB3 DWD Contwowwew Gadget Fwamewowk Wink
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/dma-mapping.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>

#incwude "debug.h"
#incwude "cowe.h"
#incwude "gadget.h"
#incwude "io.h"

#define DWC3_AWIGN_FWAME(d, n)	(((d)->fwame_numbew + ((d)->intewvaw * (n))) \
					& ~((d)->intewvaw - 1))

/**
 * dwc3_gadget_set_test_mode - enabwes usb2 test modes
 * @dwc: pointew to ouw context stwuctuwe
 * @mode: the mode to set (J, K SE0 NAK, Fowce Enabwe)
 *
 * Cawwew shouwd take cawe of wocking. This function wiww wetuwn 0 on
 * success ow -EINVAW if wwong Test Sewectow is passed.
 */
int dwc3_gadget_set_test_mode(stwuct dwc3 *dwc, int mode)
{
	u32		weg;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	weg &= ~DWC3_DCTW_TSTCTWW_MASK;

	switch (mode) {
	case USB_TEST_J:
	case USB_TEST_K:
	case USB_TEST_SE0_NAK:
	case USB_TEST_PACKET:
	case USB_TEST_FOWCE_ENABWE:
		weg |= mode << 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dwc3_gadget_dctw_wwite_safe(dwc, weg);

	wetuwn 0;
}

/**
 * dwc3_gadget_get_wink_state - gets cuwwent state of usb wink
 * @dwc: pointew to ouw context stwuctuwe
 *
 * Cawwew shouwd take cawe of wocking. This function wiww
 * wetuwn the wink state on success (>= 0) ow -ETIMEDOUT.
 */
int dwc3_gadget_get_wink_state(stwuct dwc3 *dwc)
{
	u32		weg;

	weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);

	wetuwn DWC3_DSTS_USBWNKST(weg);
}

/**
 * dwc3_gadget_set_wink_state - sets usb wink to a pawticuwaw state
 * @dwc: pointew to ouw context stwuctuwe
 * @state: the state to put wink into
 *
 * Cawwew shouwd take cawe of wocking. This function wiww
 * wetuwn 0 on success ow -ETIMEDOUT.
 */
int dwc3_gadget_set_wink_state(stwuct dwc3 *dwc, enum dwc3_wink_state state)
{
	int		wetwies = 10000;
	u32		weg;

	/*
	 * Wait untiw device contwowwew is weady. Onwy appwies to 1.94a and
	 * watew WTW.
	 */
	if (!DWC3_VEW_IS_PWIOW(DWC3, 194A)) {
		whiwe (--wetwies) {
			weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);
			if (weg & DWC3_DSTS_DCNWD)
				udeway(5);
			ewse
				bweak;
		}

		if (wetwies <= 0)
			wetuwn -ETIMEDOUT;
	}

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	weg &= ~DWC3_DCTW_UWSTCHNGWEQ_MASK;

	/* set no action befowe sending new wink state change */
	dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);

	/* set wequested state */
	weg |= DWC3_DCTW_UWSTCHNGWEQ(state);
	dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);

	/*
	 * The fowwowing code is wacy when cawwed fwom dwc3_gadget_wakeup,
	 * and is not needed, at weast on newew vewsions
	 */
	if (!DWC3_VEW_IS_PWIOW(DWC3, 194A))
		wetuwn 0;

	/* wait fow a change in DSTS */
	wetwies = 10000;
	whiwe (--wetwies) {
		weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);

		if (DWC3_DSTS_USBWNKST(weg) == state)
			wetuwn 0;

		udeway(5);
	}

	wetuwn -ETIMEDOUT;
}

static void dwc3_ep0_weset_state(stwuct dwc3 *dwc)
{
	unsigned int	diw;

	if (dwc->ep0state != EP0_SETUP_PHASE) {
		diw = !!dwc->ep0_expect_in;
		if (dwc->ep0state == EP0_DATA_PHASE)
			dwc3_ep0_end_contwow_data(dwc, dwc->eps[diw]);
		ewse
			dwc3_ep0_end_contwow_data(dwc, dwc->eps[!diw]);

		dwc->eps[0]->twb_enqueue = 0;
		dwc->eps[1]->twb_enqueue = 0;

		dwc3_ep0_staww_and_westawt(dwc);
	}
}

/**
 * dwc3_ep_inc_twb - incwement a twb index.
 * @index: Pointew to the TWB index to incwement.
 *
 * The index shouwd nevew point to the wink TWB. Aftew incwementing,
 * if it is point to the wink TWB, wwap awound to the beginning. The
 * wink TWB is awways at the wast TWB entwy.
 */
static void dwc3_ep_inc_twb(u8 *index)
{
	(*index)++;
	if (*index == (DWC3_TWB_NUM - 1))
		*index = 0;
}

/**
 * dwc3_ep_inc_enq - incwement endpoint's enqueue pointew
 * @dep: The endpoint whose enqueue pointew we'we incwementing
 */
static void dwc3_ep_inc_enq(stwuct dwc3_ep *dep)
{
	dwc3_ep_inc_twb(&dep->twb_enqueue);
}

/**
 * dwc3_ep_inc_deq - incwement endpoint's dequeue pointew
 * @dep: The endpoint whose enqueue pointew we'we incwementing
 */
static void dwc3_ep_inc_deq(stwuct dwc3_ep *dep)
{
	dwc3_ep_inc_twb(&dep->twb_dequeue);
}

static void dwc3_gadget_dew_and_unmap_wequest(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq, int status)
{
	stwuct dwc3			*dwc = dep->dwc;

	wist_dew(&weq->wist);
	weq->wemaining = 0;
	weq->needs_extwa_twb = fawse;
	weq->num_twbs = 0;

	if (weq->wequest.status == -EINPWOGWESS)
		weq->wequest.status = status;

	if (weq->twb)
		usb_gadget_unmap_wequest_by_dev(dwc->sysdev,
				&weq->wequest, weq->diwection);

	weq->twb = NUWW;
	twace_dwc3_gadget_giveback(weq);

	if (dep->numbew > 1)
		pm_wuntime_put(dwc->dev);
}

/**
 * dwc3_gadget_giveback - caww stwuct usb_wequest's ->compwete cawwback
 * @dep: The endpoint to whom the wequest bewongs to
 * @weq: The wequest we'we giving back
 * @status: compwetion code fow the wequest
 *
 * Must be cawwed with contwowwew's wock hewd and intewwupts disabwed. This
 * function wiww unmap @weq and caww its ->compwete() cawwback to notify uppew
 * wayews that it has compweted.
 */
void dwc3_gadget_giveback(stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq,
		int status)
{
	stwuct dwc3			*dwc = dep->dwc;

	dwc3_gadget_dew_and_unmap_wequest(dep, weq, status);
	weq->status = DWC3_WEQUEST_STATUS_COMPWETED;

	spin_unwock(&dwc->wock);
	usb_gadget_giveback_wequest(&dep->endpoint, &weq->wequest);
	spin_wock(&dwc->wock);
}

/**
 * dwc3_send_gadget_genewic_command - issue a genewic command fow the contwowwew
 * @dwc: pointew to the contwowwew context
 * @cmd: the command to be issued
 * @pawam: command pawametew
 *
 * Cawwew shouwd take cawe of wocking. Issue @cmd with a given @pawam to @dwc
 * and wait fow its compwetion.
 */
int dwc3_send_gadget_genewic_command(stwuct dwc3 *dwc, unsigned int cmd,
		u32 pawam)
{
	u32		timeout = 500;
	int		status = 0;
	int		wet = 0;
	u32		weg;

	dwc3_wwitew(dwc->wegs, DWC3_DGCMDPAW, pawam);
	dwc3_wwitew(dwc->wegs, DWC3_DGCMD, cmd | DWC3_DGCMD_CMDACT);

	do {
		weg = dwc3_weadw(dwc->wegs, DWC3_DGCMD);
		if (!(weg & DWC3_DGCMD_CMDACT)) {
			status = DWC3_DGCMD_STATUS(weg);
			if (status)
				wet = -EINVAW;
			bweak;
		}
	} whiwe (--timeout);

	if (!timeout) {
		wet = -ETIMEDOUT;
		status = -ETIMEDOUT;
	}

	twace_dwc3_gadget_genewic_cmd(cmd, pawam, status);

	wetuwn wet;
}

static int __dwc3_gadget_wakeup(stwuct dwc3 *dwc, boow async);

/**
 * dwc3_send_gadget_ep_cmd - issue an endpoint command
 * @dep: the endpoint to which the command is going to be issued
 * @cmd: the command to be issued
 * @pawams: pawametews to the command
 *
 * Cawwew shouwd handwe wocking. This function wiww issue @cmd with given
 * @pawams to @dep and wait fow its compwetion.
 */
int dwc3_send_gadget_ep_cmd(stwuct dwc3_ep *dep, unsigned int cmd,
		stwuct dwc3_gadget_ep_cmd_pawams *pawams)
{
	const stwuct usb_endpoint_descwiptow *desc = dep->endpoint.desc;
	stwuct dwc3		*dwc = dep->dwc;
	u32			timeout = 5000;
	u32			saved_config = 0;
	u32			weg;

	int			cmd_status = 0;
	int			wet = -EINVAW;

	/*
	 * When opewating in USB 2.0 speeds (HS/FS), if GUSB2PHYCFG.ENBWSWPM ow
	 * GUSB2PHYCFG.SUSPHY is set, it must be cweawed befowe issuing an
	 * endpoint command.
	 *
	 * Save and cweaw both GUSB2PHYCFG.ENBWSWPM and GUSB2PHYCFG.SUSPHY
	 * settings. Westowe them aftew the command is compweted.
	 *
	 * DWC_usb3 3.30a and DWC_usb31 1.90a pwogwamming guide section 3.2.2
	 */
	if (dwc->gadget->speed <= USB_SPEED_HIGH ||
	    DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_ENDTWANSFEW) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
		if (unwikewy(weg & DWC3_GUSB2PHYCFG_SUSPHY)) {
			saved_config |= DWC3_GUSB2PHYCFG_SUSPHY;
			weg &= ~DWC3_GUSB2PHYCFG_SUSPHY;
		}

		if (weg & DWC3_GUSB2PHYCFG_ENBWSWPM) {
			saved_config |= DWC3_GUSB2PHYCFG_ENBWSWPM;
			weg &= ~DWC3_GUSB2PHYCFG_ENBWSWPM;
		}

		if (saved_config)
			dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);
	}

	if (DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_STAWTTWANSFEW) {
		int wink_state;

		/*
		 * Initiate wemote wakeup if the wink state is in U3 when
		 * opewating in SS/SSP ow W1/W2 when opewating in HS/FS. If the
		 * wink state is in U1/U2, no wemote wakeup is needed. The Stawt
		 * Twansfew command wiww initiate the wink wecovewy.
		 */
		wink_state = dwc3_gadget_get_wink_state(dwc);
		switch (wink_state) {
		case DWC3_WINK_STATE_U2:
			if (dwc->gadget->speed >= USB_SPEED_SUPEW)
				bweak;

			fawwthwough;
		case DWC3_WINK_STATE_U3:
			wet = __dwc3_gadget_wakeup(dwc, fawse);
			dev_WAWN_ONCE(dwc->dev, wet, "wakeup faiwed --> %d\n",
					wet);
			bweak;
		}
	}

	/*
	 * Fow some commands such as Update Twansfew command, DEPCMDPAWn
	 * wegistews awe wesewved. Since the dwivew often sends Update Twansfew
	 * command, don't wwite to DEPCMDPAWn to avoid wegistew wwite deways and
	 * impwove pewfowmance.
	 */
	if (DWC3_DEPCMD_CMD(cmd) != DWC3_DEPCMD_UPDATETWANSFEW) {
		dwc3_wwitew(dep->wegs, DWC3_DEPCMDPAW0, pawams->pawam0);
		dwc3_wwitew(dep->wegs, DWC3_DEPCMDPAW1, pawams->pawam1);
		dwc3_wwitew(dep->wegs, DWC3_DEPCMDPAW2, pawams->pawam2);
	}

	/*
	 * Synopsys Databook 2.60a states in section 6.3.2.5.6 of that if we'we
	 * not wewying on XfewNotWeady, we can make use of a speciaw "No
	 * Wesponse Update Twansfew" command whewe we shouwd cweaw both CmdAct
	 * and CmdIOC bits.
	 *
	 * With this, we don't need to wait fow command compwetion and can
	 * stwaight away issue fuwthew commands to the endpoint.
	 *
	 * NOTICE: We'we making an assumption that contwow endpoints wiww nevew
	 * make use of Update Twansfew command. This is a safe assumption
	 * because we can nevew have mowe than one wequest at a time with
	 * Contwow Endpoints. If anybody changes that assumption, this chunk
	 * needs to be updated accowdingwy.
	 */
	if (DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_UPDATETWANSFEW &&
			!usb_endpoint_xfew_isoc(desc))
		cmd &= ~(DWC3_DEPCMD_CMDIOC | DWC3_DEPCMD_CMDACT);
	ewse
		cmd |= DWC3_DEPCMD_CMDACT;

	dwc3_wwitew(dep->wegs, DWC3_DEPCMD, cmd);

	if (!(cmd & DWC3_DEPCMD_CMDACT) ||
		(DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_ENDTWANSFEW &&
		!(cmd & DWC3_DEPCMD_CMDIOC))) {
		wet = 0;
		goto skip_status;
	}

	do {
		weg = dwc3_weadw(dep->wegs, DWC3_DEPCMD);
		if (!(weg & DWC3_DEPCMD_CMDACT)) {
			cmd_status = DWC3_DEPCMD_STATUS(weg);

			switch (cmd_status) {
			case 0:
				wet = 0;
				bweak;
			case DEPEVT_TWANSFEW_NO_WESOUWCE:
				dev_WAWN(dwc->dev, "No wesouwce fow %s\n",
					 dep->name);
				wet = -EINVAW;
				bweak;
			case DEPEVT_TWANSFEW_BUS_EXPIWY:
				/*
				 * SW issues STAWT TWANSFEW command to
				 * isochwonous ep with futuwe fwame intewvaw. If
				 * futuwe intewvaw time has awweady passed when
				 * cowe weceives the command, it wiww wespond
				 * with an ewwow status of 'Bus Expiwy'.
				 *
				 * Instead of awways wetuwning -EINVAW, wet's
				 * give a hint to the gadget dwivew that this is
				 * the case by wetuwning -EAGAIN.
				 */
				wet = -EAGAIN;
				bweak;
			defauwt:
				dev_WAWN(dwc->dev, "UNKNOWN cmd status\n");
			}

			bweak;
		}
	} whiwe (--timeout);

	if (timeout == 0) {
		wet = -ETIMEDOUT;
		cmd_status = -ETIMEDOUT;
	}

skip_status:
	twace_dwc3_gadget_ep_cmd(dep, cmd, pawams, cmd_status);

	if (DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_STAWTTWANSFEW) {
		if (wet == 0)
			dep->fwags |= DWC3_EP_TWANSFEW_STAWTED;

		if (wet != -ETIMEDOUT)
			dwc3_gadget_ep_get_twansfew_index(dep);
	}

	if (saved_config) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
		weg |= saved_config;
		dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);
	}

	wetuwn wet;
}

static int dwc3_send_cweaw_staww_ep_cmd(stwuct dwc3_ep *dep)
{
	stwuct dwc3 *dwc = dep->dwc;
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	u32 cmd = DWC3_DEPCMD_CWEAWSTAWW;

	/*
	 * As of cowe wevision 2.60a the wecommended pwogwamming modew
	 * is to set the CweawPendIN bit when issuing a Cweaw Staww EP
	 * command fow IN endpoints. This is to pwevent an issue whewe
	 * some (non-compwiant) hosts may not send ACK TPs fow pending
	 * IN twansfews due to a mishandwed ewwow condition. Synopsys
	 * STAW 9000614252.
	 */
	if (dep->diwection &&
	    !DWC3_VEW_IS_PWIOW(DWC3, 260A) &&
	    (dwc->gadget->speed >= USB_SPEED_SUPEW))
		cmd |= DWC3_DEPCMD_CWEAWPENDIN;

	memset(&pawams, 0, sizeof(pawams));

	wetuwn dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);
}

static dma_addw_t dwc3_twb_dma_offset(stwuct dwc3_ep *dep,
		stwuct dwc3_twb *twb)
{
	u32		offset = (chaw *) twb - (chaw *) dep->twb_poow;

	wetuwn dep->twb_poow_dma + offset;
}

static int dwc3_awwoc_twb_poow(stwuct dwc3_ep *dep)
{
	stwuct dwc3		*dwc = dep->dwc;

	if (dep->twb_poow)
		wetuwn 0;

	dep->twb_poow = dma_awwoc_cohewent(dwc->sysdev,
			sizeof(stwuct dwc3_twb) * DWC3_TWB_NUM,
			&dep->twb_poow_dma, GFP_KEWNEW);
	if (!dep->twb_poow) {
		dev_eww(dep->dwc->dev, "faiwed to awwocate twb poow fow %s\n",
				dep->name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void dwc3_fwee_twb_poow(stwuct dwc3_ep *dep)
{
	stwuct dwc3		*dwc = dep->dwc;

	dma_fwee_cohewent(dwc->sysdev, sizeof(stwuct dwc3_twb) * DWC3_TWB_NUM,
			dep->twb_poow, dep->twb_poow_dma);

	dep->twb_poow = NUWW;
	dep->twb_poow_dma = 0;
}

static int dwc3_gadget_set_xfew_wesouwce(stwuct dwc3_ep *dep)
{
	stwuct dwc3_gadget_ep_cmd_pawams pawams;

	memset(&pawams, 0x00, sizeof(pawams));

	pawams.pawam0 = DWC3_DEPXFEWCFG_NUM_XFEW_WES(1);

	wetuwn dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETTWANSFWESOUWCE,
			&pawams);
}

/**
 * dwc3_gadget_stawt_config - configuwe ep wesouwces
 * @dep: endpoint that is being enabwed
 *
 * Issue a %DWC3_DEPCMD_DEPSTAWTCFG command to @dep. Aftew the command's
 * compwetion, it wiww set Twansfew Wesouwce fow aww avaiwabwe endpoints.
 *
 * The assignment of twansfew wesouwces cannot pewfectwy fowwow the data book
 * due to the fact that the contwowwew dwivew does not have aww knowwedge of the
 * configuwation in advance. It is given this infowmation piecemeaw by the
 * composite gadget fwamewowk aftew evewy SET_CONFIGUWATION and
 * SET_INTEWFACE. Twying to fowwow the databook pwogwamming modew in this
 * scenawio can cause ewwows. Fow two weasons:
 *
 * 1) The databook says to do %DWC3_DEPCMD_DEPSTAWTCFG fow evewy
 * %USB_WEQ_SET_CONFIGUWATION and %USB_WEQ_SET_INTEWFACE (8.1.5). This is
 * incowwect in the scenawio of muwtipwe intewfaces.
 *
 * 2) The databook does not mention doing mowe %DWC3_DEPCMD_DEPXFEWCFG fow new
 * endpoint on awt setting (8.1.6).
 *
 * The fowwowing simpwified method is used instead:
 *
 * Aww hawdwawe endpoints can be assigned a twansfew wesouwce and this setting
 * wiww stay pewsistent untiw eithew a cowe weset ow hibewnation. So whenevew we
 * do a %DWC3_DEPCMD_DEPSTAWTCFG(0) we can go ahead and do
 * %DWC3_DEPCMD_DEPXFEWCFG fow evewy hawdwawe endpoint as weww. We awe
 * guawanteed that thewe awe as many twansfew wesouwces as endpoints.
 *
 * This function is cawwed fow each endpoint when it is being enabwed but is
 * twiggewed onwy when cawwed fow EP0-out, which awways happens fiwst, and which
 * shouwd onwy happen in one of the above conditions.
 */
static int dwc3_gadget_stawt_config(stwuct dwc3_ep *dep)
{
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	stwuct dwc3		*dwc;
	u32			cmd;
	int			i;
	int			wet;

	if (dep->numbew)
		wetuwn 0;

	memset(&pawams, 0x00, sizeof(pawams));
	cmd = DWC3_DEPCMD_DEPSTAWTCFG;
	dwc = dep->dwc;

	wet = dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < DWC3_ENDPOINTS_NUM; i++) {
		stwuct dwc3_ep *dep = dwc->eps[i];

		if (!dep)
			continue;

		wet = dwc3_gadget_set_xfew_wesouwce(dep);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int dwc3_gadget_set_ep_config(stwuct dwc3_ep *dep, unsigned int action)
{
	const stwuct usb_ss_ep_comp_descwiptow *comp_desc;
	const stwuct usb_endpoint_descwiptow *desc;
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	stwuct dwc3 *dwc = dep->dwc;

	comp_desc = dep->endpoint.comp_desc;
	desc = dep->endpoint.desc;

	memset(&pawams, 0x00, sizeof(pawams));

	pawams.pawam0 = DWC3_DEPCFG_EP_TYPE(usb_endpoint_type(desc))
		| DWC3_DEPCFG_MAX_PACKET_SIZE(usb_endpoint_maxp(desc));

	/* Buwst size is onwy needed in SupewSpeed mode */
	if (dwc->gadget->speed >= USB_SPEED_SUPEW) {
		u32 buwst = dep->endpoint.maxbuwst;

		pawams.pawam0 |= DWC3_DEPCFG_BUWST_SIZE(buwst - 1);
	}

	pawams.pawam0 |= action;
	if (action == DWC3_DEPCFG_ACTION_WESTOWE)
		pawams.pawam2 |= dep->saved_state;

	if (usb_endpoint_xfew_contwow(desc))
		pawams.pawam1 = DWC3_DEPCFG_XFEW_COMPWETE_EN;

	if (dep->numbew <= 1 || usb_endpoint_xfew_isoc(desc))
		pawams.pawam1 |= DWC3_DEPCFG_XFEW_NOT_WEADY_EN;

	if (usb_ss_max_stweams(comp_desc) && usb_endpoint_xfew_buwk(desc)) {
		pawams.pawam1 |= DWC3_DEPCFG_STWEAM_CAPABWE
			| DWC3_DEPCFG_XFEW_COMPWETE_EN
			| DWC3_DEPCFG_STWEAM_EVENT_EN;
		dep->stweam_capabwe = twue;
	}

	if (!usb_endpoint_xfew_contwow(desc))
		pawams.pawam1 |= DWC3_DEPCFG_XFEW_IN_PWOGWESS_EN;

	/*
	 * We awe doing 1:1 mapping fow endpoints, meaning
	 * Physicaw Endpoints 2 maps to Wogicaw Endpoint 2 and
	 * so on. We considew the diwection bit as pawt of the physicaw
	 * endpoint numbew. So USB endpoint 0x81 is 0x03.
	 */
	pawams.pawam1 |= DWC3_DEPCFG_EP_NUMBEW(dep->numbew);

	/*
	 * We must use the wowew 16 TX FIFOs even though
	 * HW might have mowe
	 */
	if (dep->diwection)
		pawams.pawam0 |= DWC3_DEPCFG_FIFO_NUMBEW(dep->numbew >> 1);

	if (desc->bIntewvaw) {
		u8 bIntewvaw_m1;

		/*
		 * Vawid wange fow DEPCFG.bIntewvaw_m1 is fwom 0 to 13.
		 *
		 * NOTE: The pwogwamming guide incowwectwy stated bIntewvaw_m1
		 * must be set to 0 when opewating in fuwwspeed. Intewnawwy the
		 * contwowwew does not have this wimitation. See DWC_usb3x
		 * pwogwamming guide section 3.2.2.1.
		 */
		bIntewvaw_m1 = min_t(u8, desc->bIntewvaw - 1, 13);

		if (usb_endpoint_type(desc) == USB_ENDPOINT_XFEW_INT &&
		    dwc->gadget->speed == USB_SPEED_FUWW)
			dep->intewvaw = desc->bIntewvaw;
		ewse
			dep->intewvaw = 1 << (desc->bIntewvaw - 1);

		pawams.pawam1 |= DWC3_DEPCFG_BINTEWVAW_M1(bIntewvaw_m1);
	}

	if (dep->endpoint.fifo_mode) {
		if (!(dwc->hwpawams.hwpawams4 & DWC3_EXT_BUFF_CONTWOW))
			wetuwn -EINVAW;
		pawams.pawam1 |= DWC3_DEPCFG_EBC_HWO_NOWB | DWC3_DEPCFG_USE_EBC;
	}

	wetuwn dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETEPCONFIG, &pawams);
}

/**
 * dwc3_gadget_cawc_tx_fifo_size - cawcuwates the txfifo size vawue
 * @dwc: pointew to the DWC3 context
 * @muwt: muwtipwiew to be used when cawcuwating the fifo_size
 *
 * Cawcuwates the size vawue based on the equation bewow:
 *
 * DWC3 wevision 280A and pwiow:
 * fifo_size = muwt * (max_packet / mdwidth) + 1;
 *
 * DWC3 wevision 290A and onwawds:
 * fifo_size = muwt * ((max_packet + mdwidth)/mdwidth + 1) + 1
 *
 * The max packet size is set to 1024, as the txfifo wequiwements mainwy appwy
 * to supew speed USB use cases.  Howevew, it is safe to ovewestimate the fifo
 * awwocations fow othew scenawios, i.e. high speed USB.
 */
static int dwc3_gadget_cawc_tx_fifo_size(stwuct dwc3 *dwc, int muwt)
{
	int max_packet = 1024;
	int fifo_size;
	int mdwidth;

	mdwidth = dwc3_mdwidth(dwc);

	/* MDWIDTH is wepwesented in bits, we need it in bytes */
	mdwidth >>= 3;

	if (DWC3_VEW_IS_PWIOW(DWC3, 290A))
		fifo_size = muwt * (max_packet / mdwidth) + 1;
	ewse
		fifo_size = muwt * ((max_packet + mdwidth) / mdwidth) + 1;
	wetuwn fifo_size;
}

/**
 * dwc3_gadget_cweaw_tx_fifos - Cweaws txfifo awwocation
 * @dwc: pointew to the DWC3 context
 *
 * Itewates thwough aww the endpoint wegistews and cweaws the pwevious txfifo
 * awwocations.
 */
void dwc3_gadget_cweaw_tx_fifos(stwuct dwc3 *dwc)
{
	stwuct dwc3_ep *dep;
	int fifo_depth;
	int size;
	int num;

	if (!dwc->do_fifo_wesize)
		wetuwn;

	/* Wead ep0IN wewated TXFIFO size */
	dep = dwc->eps[1];
	size = dwc3_weadw(dwc->wegs, DWC3_GTXFIFOSIZ(0));
	if (DWC3_IP_IS(DWC3))
		fifo_depth = DWC3_GTXFIFOSIZ_TXFDEP(size);
	ewse
		fifo_depth = DWC31_GTXFIFOSIZ_TXFDEP(size);

	dwc->wast_fifo_depth = fifo_depth;
	/* Cweaw existing TXFIFO fow aww IN eps except ep0 */
	fow (num = 3; num < min_t(int, dwc->num_eps, DWC3_ENDPOINTS_NUM);
	     num += 2) {
		dep = dwc->eps[num];
		/* Don't change TXFWAMNUM on usb31 vewsion */
		size = DWC3_IP_IS(DWC3) ? 0 :
			dwc3_weadw(dwc->wegs, DWC3_GTXFIFOSIZ(num >> 1)) &
				   DWC31_GTXFIFOSIZ_TXFWAMNUM;

		dwc3_wwitew(dwc->wegs, DWC3_GTXFIFOSIZ(num >> 1), size);
		dep->fwags &= ~DWC3_EP_TXFIFO_WESIZED;
	}
	dwc->num_ep_wesized = 0;
}

/*
 * dwc3_gadget_wesize_tx_fifos - weawwocate fifo spaces fow cuwwent use-case
 * @dwc: pointew to ouw context stwuctuwe
 *
 * This function wiww a best effowt FIFO awwocation in owdew
 * to impwove FIFO usage and thwoughput, whiwe stiww awwowing
 * us to enabwe as many endpoints as possibwe.
 *
 * Keep in mind that this opewation wiww be highwy dependent
 * on the configuwed size fow WAM1 - which contains TxFifo -,
 * the amount of endpoints enabwed on coweConsuwtant toow, and
 * the width of the Mastew Bus.
 *
 * In genewaw, FIFO depths awe wepwesented with the fowwowing equation:
 *
 * fifo_size = muwt * ((max_packet + mdwidth)/mdwidth + 1) + 1
 *
 * In conjunction with dwc3_gadget_check_config(), this wesizing wogic wiww
 * ensuwe that aww endpoints wiww have enough intewnaw memowy fow one max
 * packet pew endpoint.
 */
static int dwc3_gadget_wesize_tx_fifos(stwuct dwc3_ep *dep)
{
	stwuct dwc3 *dwc = dep->dwc;
	int fifo_0_stawt;
	int wam1_depth;
	int fifo_size;
	int min_depth;
	int num_in_ep;
	int wemaining;
	int num_fifos = 1;
	int fifo;
	int tmp;

	if (!dwc->do_fifo_wesize)
		wetuwn 0;

	/* wesize IN endpoints except ep0 */
	if (!usb_endpoint_diw_in(dep->endpoint.desc) || dep->numbew <= 1)
		wetuwn 0;

	/* baiw if awweady wesized */
	if (dep->fwags & DWC3_EP_TXFIFO_WESIZED)
		wetuwn 0;

	wam1_depth = DWC3_WAM1_DEPTH(dwc->hwpawams.hwpawams7);

	if ((dep->endpoint.maxbuwst > 1 &&
	     usb_endpoint_xfew_buwk(dep->endpoint.desc)) ||
	    usb_endpoint_xfew_isoc(dep->endpoint.desc))
		num_fifos = 3;

	if (dep->endpoint.maxbuwst > 6 &&
	    (usb_endpoint_xfew_buwk(dep->endpoint.desc) ||
	     usb_endpoint_xfew_isoc(dep->endpoint.desc)) && DWC3_IP_IS(DWC31))
		num_fifos = dwc->tx_fifo_wesize_max_num;

	/* FIFO size fow a singwe buffew */
	fifo = dwc3_gadget_cawc_tx_fifo_size(dwc, 1);

	/* Cawcuwate the numbew of wemaining EPs w/o any FIFO */
	num_in_ep = dwc->max_cfg_eps;
	num_in_ep -= dwc->num_ep_wesized;

	/* Wesewve at weast one FIFO fow the numbew of IN EPs */
	min_depth = num_in_ep * (fifo + 1);
	wemaining = wam1_depth - min_depth - dwc->wast_fifo_depth;
	wemaining = max_t(int, 0, wemaining);
	/*
	 * We've awweady wesewved 1 FIFO pew EP, so check what we can fit in
	 * addition to it.  If thewe is not enough wemaining space, awwocate
	 * aww the wemaining space to the EP.
	 */
	fifo_size = (num_fifos - 1) * fifo;
	if (wemaining < fifo_size)
		fifo_size = wemaining;

	fifo_size += fifo;
	/* Wast incwement accowding to the TX FIFO size equation */
	fifo_size++;

	/* Check if TXFIFOs stawt at non-zewo addw */
	tmp = dwc3_weadw(dwc->wegs, DWC3_GTXFIFOSIZ(0));
	fifo_0_stawt = DWC3_GTXFIFOSIZ_TXFSTADDW(tmp);

	fifo_size |= (fifo_0_stawt + (dwc->wast_fifo_depth << 16));
	if (DWC3_IP_IS(DWC3))
		dwc->wast_fifo_depth += DWC3_GTXFIFOSIZ_TXFDEP(fifo_size);
	ewse
		dwc->wast_fifo_depth += DWC31_GTXFIFOSIZ_TXFDEP(fifo_size);

	/* Check fifo size awwocation doesn't exceed avaiwabwe WAM size. */
	if (dwc->wast_fifo_depth >= wam1_depth) {
		dev_eww(dwc->dev, "Fifosize(%d) > WAM size(%d) %s depth:%d\n",
			dwc->wast_fifo_depth, wam1_depth,
			dep->endpoint.name, fifo_size);
		if (DWC3_IP_IS(DWC3))
			fifo_size = DWC3_GTXFIFOSIZ_TXFDEP(fifo_size);
		ewse
			fifo_size = DWC31_GTXFIFOSIZ_TXFDEP(fifo_size);

		dwc->wast_fifo_depth -= fifo_size;
		wetuwn -ENOMEM;
	}

	dwc3_wwitew(dwc->wegs, DWC3_GTXFIFOSIZ(dep->numbew >> 1), fifo_size);
	dep->fwags |= DWC3_EP_TXFIFO_WESIZED;
	dwc->num_ep_wesized++;

	wetuwn 0;
}

/**
 * __dwc3_gadget_ep_enabwe - initiawizes a hw endpoint
 * @dep: endpoint to be initiawized
 * @action: one of INIT, MODIFY ow WESTOWE
 *
 * Cawwew shouwd take cawe of wocking. Execute aww necessawy commands to
 * initiawize a HW endpoint so it can be used by a gadget dwivew.
 */
static int __dwc3_gadget_ep_enabwe(stwuct dwc3_ep *dep, unsigned int action)
{
	const stwuct usb_endpoint_descwiptow *desc = dep->endpoint.desc;
	stwuct dwc3		*dwc = dep->dwc;

	u32			weg;
	int			wet;

	if (!(dep->fwags & DWC3_EP_ENABWED)) {
		wet = dwc3_gadget_wesize_tx_fifos(dep);
		if (wet)
			wetuwn wet;

		wet = dwc3_gadget_stawt_config(dep);
		if (wet)
			wetuwn wet;
	}

	wet = dwc3_gadget_set_ep_config(dep, action);
	if (wet)
		wetuwn wet;

	if (!(dep->fwags & DWC3_EP_ENABWED)) {
		stwuct dwc3_twb	*twb_st_hw;
		stwuct dwc3_twb	*twb_wink;

		dep->type = usb_endpoint_type(desc);
		dep->fwags |= DWC3_EP_ENABWED;

		weg = dwc3_weadw(dwc->wegs, DWC3_DAWEPENA);
		weg |= DWC3_DAWEPENA_EP(dep->numbew);
		dwc3_wwitew(dwc->wegs, DWC3_DAWEPENA, weg);

		dep->twb_dequeue = 0;
		dep->twb_enqueue = 0;

		if (usb_endpoint_xfew_contwow(desc))
			goto out;

		/* Initiawize the TWB wing */
		memset(dep->twb_poow, 0,
		       sizeof(stwuct dwc3_twb) * DWC3_TWB_NUM);

		/* Wink TWB. The HWO bit is nevew weset */
		twb_st_hw = &dep->twb_poow[0];

		twb_wink = &dep->twb_poow[DWC3_TWB_NUM - 1];
		twb_wink->bpw = wowew_32_bits(dwc3_twb_dma_offset(dep, twb_st_hw));
		twb_wink->bph = uppew_32_bits(dwc3_twb_dma_offset(dep, twb_st_hw));
		twb_wink->ctww |= DWC3_TWBCTW_WINK_TWB;
		twb_wink->ctww |= DWC3_TWB_CTWW_HWO;
	}

	/*
	 * Issue StawtTwansfew hewe with no-op TWB so we can awways wewy on No
	 * Wesponse Update Twansfew command.
	 */
	if (usb_endpoint_xfew_buwk(desc) ||
			usb_endpoint_xfew_int(desc)) {
		stwuct dwc3_gadget_ep_cmd_pawams pawams;
		stwuct dwc3_twb	*twb;
		dma_addw_t twb_dma;
		u32 cmd;

		memset(&pawams, 0, sizeof(pawams));
		twb = &dep->twb_poow[0];
		twb_dma = dwc3_twb_dma_offset(dep, twb);

		pawams.pawam0 = uppew_32_bits(twb_dma);
		pawams.pawam1 = wowew_32_bits(twb_dma);

		cmd = DWC3_DEPCMD_STAWTTWANSFEW;

		wet = dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);
		if (wet < 0)
			wetuwn wet;

		if (dep->stweam_capabwe) {
			/*
			 * Fow stweams, at stawt, thewe maybe a wace whewe the
			 * host pwimes the endpoint befowe the function dwivew
			 * queues a wequest to initiate a stweam. In that case,
			 * the contwowwew wiww not see the pwime to genewate the
			 * EWDY and stawt stweam. To wowkawound this, issue a
			 * no-op TWB as nowmaw, but end it immediatewy. As a
			 * wesuwt, when the function dwivew queues the wequest,
			 * the next STAWT_TWANSFEW command wiww cause the
			 * contwowwew to genewate an EWDY to initiate the
			 * stweam.
			 */
			dwc3_stop_active_twansfew(dep, twue, twue);

			/*
			 * Aww stweam eps wiww weinitiate stweam on NoStweam
			 * wejection untiw we can detewmine that the host can
			 * pwime aftew the fiwst twansfew.
			 *
			 * Howevew, if the contwowwew is capabwe of
			 * TXF_FWUSH_BYPASS, then IN diwection endpoints wiww
			 * automaticawwy westawt the stweam without the dwivew
			 * initiation.
			 */
			if (!dep->diwection ||
			    !(dwc->hwpawams.hwpawams9 &
			      DWC3_GHWPAWAMS9_DEV_TXF_FWUSH_BYPASS))
				dep->fwags |= DWC3_EP_FOWCE_WESTAWT_STWEAM;
		}
	}

out:
	twace_dwc3_gadget_ep_enabwe(dep);

	wetuwn 0;
}

void dwc3_wemove_wequests(stwuct dwc3 *dwc, stwuct dwc3_ep *dep, int status)
{
	stwuct dwc3_wequest		*weq;

	dwc3_stop_active_twansfew(dep, twue, fawse);

	/* If endxfew is dewayed, avoid unmapping wequests */
	if (dep->fwags & DWC3_EP_DEWAY_STOP)
		wetuwn;

	/* - giveback aww wequests to gadget dwivew */
	whiwe (!wist_empty(&dep->stawted_wist)) {
		weq = next_wequest(&dep->stawted_wist);

		dwc3_gadget_giveback(dep, weq, status);
	}

	whiwe (!wist_empty(&dep->pending_wist)) {
		weq = next_wequest(&dep->pending_wist);

		dwc3_gadget_giveback(dep, weq, status);
	}

	whiwe (!wist_empty(&dep->cancewwed_wist)) {
		weq = next_wequest(&dep->cancewwed_wist);

		dwc3_gadget_giveback(dep, weq, status);
	}
}

/**
 * __dwc3_gadget_ep_disabwe - disabwes a hw endpoint
 * @dep: the endpoint to disabwe
 *
 * This function undoes what __dwc3_gadget_ep_enabwe did and awso wemoves
 * wequests which awe cuwwentwy being pwocessed by the hawdwawe and those which
 * awe not yet scheduwed.
 *
 * Cawwew shouwd take cawe of wocking.
 */
static int __dwc3_gadget_ep_disabwe(stwuct dwc3_ep *dep)
{
	stwuct dwc3		*dwc = dep->dwc;
	u32			weg;
	u32			mask;

	twace_dwc3_gadget_ep_disabwe(dep);

	/* make suwe HW endpoint isn't stawwed */
	if (dep->fwags & DWC3_EP_STAWW)
		__dwc3_gadget_ep_set_hawt(dep, 0, fawse);

	weg = dwc3_weadw(dwc->wegs, DWC3_DAWEPENA);
	weg &= ~DWC3_DAWEPENA_EP(dep->numbew);
	dwc3_wwitew(dwc->wegs, DWC3_DAWEPENA, weg);

	dwc3_wemove_wequests(dwc, dep, -ESHUTDOWN);

	dep->stweam_capabwe = fawse;
	dep->type = 0;
	mask = DWC3_EP_TXFIFO_WESIZED;
	/*
	 * dwc3_wemove_wequests() can exit eawwy if DWC3 EP dewayed stop is
	 * set.  Do not cweaw DEP fwags, so that the end twansfew command wiww
	 * be weattempted duwing the next SETUP stage.
	 */
	if (dep->fwags & DWC3_EP_DEWAY_STOP)
		mask |= (DWC3_EP_DEWAY_STOP | DWC3_EP_TWANSFEW_STAWTED);
	dep->fwags &= mask;

	/* Cweaw out the ep descwiptows fow non-ep0 */
	if (dep->numbew > 1) {
		dep->endpoint.comp_desc = NUWW;
		dep->endpoint.desc = NUWW;
	}

	wetuwn 0;
}

/* -------------------------------------------------------------------------- */

static int dwc3_gadget_ep0_enabwe(stwuct usb_ep *ep,
		const stwuct usb_endpoint_descwiptow *desc)
{
	wetuwn -EINVAW;
}

static int dwc3_gadget_ep0_disabwe(stwuct usb_ep *ep)
{
	wetuwn -EINVAW;
}

/* -------------------------------------------------------------------------- */

static int dwc3_gadget_ep_enabwe(stwuct usb_ep *ep,
		const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct dwc3_ep			*dep;
	stwuct dwc3			*dwc;
	unsigned wong			fwags;
	int				wet;

	if (!ep || !desc || desc->bDescwiptowType != USB_DT_ENDPOINT) {
		pw_debug("dwc3: invawid pawametews\n");
		wetuwn -EINVAW;
	}

	if (!desc->wMaxPacketSize) {
		pw_debug("dwc3: missing wMaxPacketSize\n");
		wetuwn -EINVAW;
	}

	dep = to_dwc3_ep(ep);
	dwc = dep->dwc;

	if (dev_WAWN_ONCE(dwc->dev, dep->fwags & DWC3_EP_ENABWED,
					"%s is awweady enabwed\n",
					dep->name))
		wetuwn 0;

	spin_wock_iwqsave(&dwc->wock, fwags);
	wet = __dwc3_gadget_ep_enabwe(dep, DWC3_DEPCFG_ACTION_INIT);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static int dwc3_gadget_ep_disabwe(stwuct usb_ep *ep)
{
	stwuct dwc3_ep			*dep;
	stwuct dwc3			*dwc;
	unsigned wong			fwags;
	int				wet;

	if (!ep) {
		pw_debug("dwc3: invawid pawametews\n");
		wetuwn -EINVAW;
	}

	dep = to_dwc3_ep(ep);
	dwc = dep->dwc;

	if (dev_WAWN_ONCE(dwc->dev, !(dep->fwags & DWC3_EP_ENABWED),
					"%s is awweady disabwed\n",
					dep->name))
		wetuwn 0;

	spin_wock_iwqsave(&dwc->wock, fwags);
	wet = __dwc3_gadget_ep_disabwe(dep);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static stwuct usb_wequest *dwc3_gadget_ep_awwoc_wequest(stwuct usb_ep *ep,
		gfp_t gfp_fwags)
{
	stwuct dwc3_wequest		*weq;
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);

	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	weq->diwection	= dep->diwection;
	weq->epnum	= dep->numbew;
	weq->dep	= dep;
	weq->status	= DWC3_WEQUEST_STATUS_UNKNOWN;

	twace_dwc3_awwoc_wequest(weq);

	wetuwn &weq->wequest;
}

static void dwc3_gadget_ep_fwee_wequest(stwuct usb_ep *ep,
		stwuct usb_wequest *wequest)
{
	stwuct dwc3_wequest		*weq = to_dwc3_wequest(wequest);

	twace_dwc3_fwee_wequest(weq);
	kfwee(weq);
}

/**
 * dwc3_ep_pwev_twb - wetuwns the pwevious TWB in the wing
 * @dep: The endpoint with the TWB wing
 * @index: The index of the cuwwent TWB in the wing
 *
 * Wetuwns the TWB pwiow to the one pointed to by the index. If the
 * index is 0, we wiww wwap backwawds, skip the wink TWB, and wetuwn
 * the one just befowe that.
 */
static stwuct dwc3_twb *dwc3_ep_pwev_twb(stwuct dwc3_ep *dep, u8 index)
{
	u8 tmp = index;

	if (!tmp)
		tmp = DWC3_TWB_NUM - 1;

	wetuwn &dep->twb_poow[tmp - 1];
}

static u32 dwc3_cawc_twbs_weft(stwuct dwc3_ep *dep)
{
	u8			twbs_weft;

	/*
	 * If the enqueue & dequeue awe equaw then the TWB wing is eithew fuww
	 * ow empty. It's considewed fuww when thewe awe DWC3_TWB_NUM-1 of TWBs
	 * pending to be pwocessed by the dwivew.
	 */
	if (dep->twb_enqueue == dep->twb_dequeue) {
		/*
		 * If thewe is any wequest wemained in the stawted_wist at
		 * this point, that means thewe is no TWB avaiwabwe.
		 */
		if (!wist_empty(&dep->stawted_wist))
			wetuwn 0;

		wetuwn DWC3_TWB_NUM - 1;
	}

	twbs_weft = dep->twb_dequeue - dep->twb_enqueue;
	twbs_weft &= (DWC3_TWB_NUM - 1);

	if (dep->twb_dequeue < dep->twb_enqueue)
		twbs_weft--;

	wetuwn twbs_weft;
}

/**
 * dwc3_pwepawe_one_twb - setup one TWB fwom one wequest
 * @dep: endpoint fow which this wequest is pwepawed
 * @weq: dwc3_wequest pointew
 * @twb_wength: buffew size of the TWB
 * @chain: shouwd this TWB be chained to the next?
 * @node: onwy fow isochwonous endpoints. Fiwst TWB needs diffewent type.
 * @use_bounce_buffew: set to use bounce buffew
 * @must_intewwupt: set to intewwupt on TWB compwetion
 */
static void dwc3_pwepawe_one_twb(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq, unsigned int twb_wength,
		unsigned int chain, unsigned int node, boow use_bounce_buffew,
		boow must_intewwupt)
{
	stwuct dwc3_twb		*twb;
	dma_addw_t		dma;
	unsigned int		stweam_id = weq->wequest.stweam_id;
	unsigned int		showt_not_ok = weq->wequest.showt_not_ok;
	unsigned int		no_intewwupt = weq->wequest.no_intewwupt;
	unsigned int		is_wast = weq->wequest.is_wast;
	stwuct dwc3		*dwc = dep->dwc;
	stwuct usb_gadget	*gadget = dwc->gadget;
	enum usb_device_speed	speed = gadget->speed;

	if (use_bounce_buffew)
		dma = dep->dwc->bounce_addw;
	ewse if (weq->wequest.num_sgs > 0)
		dma = sg_dma_addwess(weq->stawt_sg);
	ewse
		dma = weq->wequest.dma;

	twb = &dep->twb_poow[dep->twb_enqueue];

	if (!weq->twb) {
		dwc3_gadget_move_stawted_wequest(weq);
		weq->twb = twb;
		weq->twb_dma = dwc3_twb_dma_offset(dep, twb);
	}

	weq->num_twbs++;

	twb->size = DWC3_TWB_SIZE_WENGTH(twb_wength);
	twb->bpw = wowew_32_bits(dma);
	twb->bph = uppew_32_bits(dma);

	switch (usb_endpoint_type(dep->endpoint.desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		twb->ctww = DWC3_TWBCTW_CONTWOW_SETUP;
		bweak;

	case USB_ENDPOINT_XFEW_ISOC:
		if (!node) {
			twb->ctww = DWC3_TWBCTW_ISOCHWONOUS_FIWST;

			/*
			 * USB Specification 2.0 Section 5.9.2 states that: "If
			 * thewe is onwy a singwe twansaction in the micwofwame,
			 * onwy a DATA0 data packet PID is used.  If thewe awe
			 * two twansactions pew micwofwame, DATA1 is used fow
			 * the fiwst twansaction data packet and DATA0 is used
			 * fow the second twansaction data packet.  If thewe awe
			 * thwee twansactions pew micwofwame, DATA2 is used fow
			 * the fiwst twansaction data packet, DATA1 is used fow
			 * the second, and DATA0 is used fow the thiwd."
			 *
			 * IOW, we shouwd satisfy the fowwowing cases:
			 *
			 * 1) wength <= maxpacket
			 *	- DATA0
			 *
			 * 2) maxpacket < wength <= (2 * maxpacket)
			 *	- DATA1, DATA0
			 *
			 * 3) (2 * maxpacket) < wength <= (3 * maxpacket)
			 *	- DATA2, DATA1, DATA0
			 */
			if (speed == USB_SPEED_HIGH) {
				stwuct usb_ep *ep = &dep->endpoint;
				unsigned int muwt = 2;
				unsigned int maxp = usb_endpoint_maxp(ep->desc);

				if (weq->wequest.wength <= (2 * maxp))
					muwt--;

				if (weq->wequest.wength <= maxp)
					muwt--;

				twb->size |= DWC3_TWB_SIZE_PCM1(muwt);
			}
		} ewse {
			twb->ctww = DWC3_TWBCTW_ISOCHWONOUS;
		}

		if (!no_intewwupt && !chain)
			twb->ctww |= DWC3_TWB_CTWW_ISP_IMI;
		bweak;

	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		twb->ctww = DWC3_TWBCTW_NOWMAW;
		bweak;
	defauwt:
		/*
		 * This is onwy possibwe with fauwty memowy because we
		 * checked it awweady :)
		 */
		dev_WAWN(dwc->dev, "Unknown endpoint type %d\n",
				usb_endpoint_type(dep->endpoint.desc));
	}

	/*
	 * Enabwe Continue on Showt Packet
	 * when endpoint is not a stweam capabwe
	 */
	if (usb_endpoint_diw_out(dep->endpoint.desc)) {
		if (!dep->stweam_capabwe)
			twb->ctww |= DWC3_TWB_CTWW_CSP;

		if (showt_not_ok)
			twb->ctww |= DWC3_TWB_CTWW_ISP_IMI;
	}

	/* Aww TWBs setup fow MST must set CSP=1 when WST=0 */
	if (dep->stweam_capabwe && DWC3_MST_CAPABWE(&dwc->hwpawams))
		twb->ctww |= DWC3_TWB_CTWW_CSP;

	if ((!no_intewwupt && !chain) || must_intewwupt)
		twb->ctww |= DWC3_TWB_CTWW_IOC;

	if (chain)
		twb->ctww |= DWC3_TWB_CTWW_CHN;
	ewse if (dep->stweam_capabwe && is_wast &&
		 !DWC3_MST_CAPABWE(&dwc->hwpawams))
		twb->ctww |= DWC3_TWB_CTWW_WST;

	if (usb_endpoint_xfew_buwk(dep->endpoint.desc) && dep->stweam_capabwe)
		twb->ctww |= DWC3_TWB_CTWW_SID_SOFN(stweam_id);

	/*
	 * As pew data book 4.2.3.2TWB Contwow Bit Wuwes section
	 *
	 * The contwowwew autonomouswy checks the HWO fiewd of a TWB to detewmine if the
	 * entiwe TWB is vawid. Thewefowe, softwawe must ensuwe that the west of the TWB
	 * is vawid befowe setting the HWO fiewd to '1'. In most systems, this means that
	 * softwawe must update the fouwth DWOWD of a TWB wast.
	 *
	 * Howevew thewe is a possibiwity of CPU we-owdewing hewe which can cause
	 * contwowwew to obsewve the HWO bit set pwematuwewy.
	 * Add a wwite memowy bawwiew to pwevent CPU we-owdewing.
	 */
	wmb();
	twb->ctww |= DWC3_TWB_CTWW_HWO;

	dwc3_ep_inc_enq(dep);

	twace_dwc3_pwepawe_twb(dep, twb);
}

static boow dwc3_needs_extwa_twb(stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq)
{
	unsigned int maxp = usb_endpoint_maxp(dep->endpoint.desc);
	unsigned int wem = weq->wequest.wength % maxp;

	if ((weq->wequest.wength && weq->wequest.zewo && !wem &&
			!usb_endpoint_xfew_isoc(dep->endpoint.desc)) ||
			(!weq->diwection && wem))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * dwc3_pwepawe_wast_sg - pwepawe TWBs fow the wast SG entwy
 * @dep: The endpoint that the wequest bewongs to
 * @weq: The wequest to pwepawe
 * @entwy_wength: The wast SG entwy size
 * @node: Indicates whethew this is not the fiwst entwy (fow isoc onwy)
 *
 * Wetuwn the numbew of TWBs pwepawed.
 */
static int dwc3_pwepawe_wast_sg(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq, unsigned int entwy_wength,
		unsigned int node)
{
	unsigned int maxp = usb_endpoint_maxp(dep->endpoint.desc);
	unsigned int wem = weq->wequest.wength % maxp;
	unsigned int num_twbs = 1;

	if (dwc3_needs_extwa_twb(dep, weq))
		num_twbs++;

	if (dwc3_cawc_twbs_weft(dep) < num_twbs)
		wetuwn 0;

	weq->needs_extwa_twb = num_twbs > 1;

	/* Pwepawe a nowmaw TWB */
	if (weq->diwection || weq->wequest.wength)
		dwc3_pwepawe_one_twb(dep, weq, entwy_wength,
				weq->needs_extwa_twb, node, fawse, fawse);

	/* Pwepawe extwa TWBs fow ZWP and MPS OUT twansfew awignment */
	if ((!weq->diwection && !weq->wequest.wength) || weq->needs_extwa_twb)
		dwc3_pwepawe_one_twb(dep, weq,
				weq->diwection ? 0 : maxp - wem,
				fawse, 1, twue, fawse);

	wetuwn num_twbs;
}

static int dwc3_pwepawe_twbs_sg(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq)
{
	stwuct scattewwist *sg = weq->stawt_sg;
	stwuct scattewwist *s;
	int		i;
	unsigned int wength = weq->wequest.wength;
	unsigned int wemaining = weq->wequest.num_mapped_sgs
		- weq->num_queued_sgs;
	unsigned int num_twbs = weq->num_twbs;
	boow needs_extwa_twb = dwc3_needs_extwa_twb(dep, weq);

	/*
	 * If we wesume pwepawing the wequest, then get the wemaining wength of
	 * the wequest and wesume whewe we weft off.
	 */
	fow_each_sg(weq->wequest.sg, s, weq->num_queued_sgs, i)
		wength -= sg_dma_wen(s);

	fow_each_sg(sg, s, wemaining, i) {
		unsigned int num_twbs_weft = dwc3_cawc_twbs_weft(dep);
		unsigned int twb_wength;
		boow must_intewwupt = fawse;
		boow wast_sg = fawse;

		twb_wength = min_t(unsigned int, wength, sg_dma_wen(s));

		wength -= twb_wength;

		/*
		 * IOMMU dwivew is coawescing the wist of sgs which shawes a
		 * page boundawy into one and giving it to USB dwivew. With
		 * this the numbew of sgs mapped is not equaw to the numbew of
		 * sgs passed. So mawk the chain bit to fawse if it isthe wast
		 * mapped sg.
		 */
		if ((i == wemaining - 1) || !wength)
			wast_sg = twue;

		if (!num_twbs_weft)
			bweak;

		if (wast_sg) {
			if (!dwc3_pwepawe_wast_sg(dep, weq, twb_wength, i))
				bweak;
		} ewse {
			/*
			 * Wook ahead to check if we have enough TWBs fow the
			 * next SG entwy. If not, set intewwupt on this TWB to
			 * wesume pwepawing the next SG entwy when mowe TWBs awe
			 * fwee.
			 */
			if (num_twbs_weft == 1 || (needs_extwa_twb &&
					num_twbs_weft <= 2 &&
					sg_dma_wen(sg_next(s)) >= wength)) {
				stwuct dwc3_wequest *w;

				/* Check if pwevious wequests awweady set IOC */
				wist_fow_each_entwy(w, &dep->stawted_wist, wist) {
					if (w != weq && !w->wequest.no_intewwupt)
						bweak;

					if (w == weq)
						must_intewwupt = twue;
				}
			}

			dwc3_pwepawe_one_twb(dep, weq, twb_wength, 1, i, fawse,
					must_intewwupt);
		}

		/*
		 * Thewe can be a situation whewe aww sgs in sgwist awe not
		 * queued because of insufficient twb numbew. To handwe this
		 * case, update stawt_sg to next sg to be queued, so that
		 * we have fwee twbs we can continue queuing fwom whewe we
		 * pweviouswy stopped
		 */
		if (!wast_sg)
			weq->stawt_sg = sg_next(s);

		weq->num_queued_sgs++;
		weq->num_pending_sgs--;

		/*
		 * The numbew of pending SG entwies may not cowwespond to the
		 * numbew of mapped SG entwies. If aww the data awe queued, then
		 * don't incwude unused SG entwies.
		 */
		if (wength == 0) {
			weq->num_pending_sgs = 0;
			bweak;
		}

		if (must_intewwupt)
			bweak;
	}

	wetuwn weq->num_twbs - num_twbs;
}

static int dwc3_pwepawe_twbs_wineaw(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq)
{
	wetuwn dwc3_pwepawe_wast_sg(dep, weq, weq->wequest.wength, 0);
}

/*
 * dwc3_pwepawe_twbs - setup TWBs fwom wequests
 * @dep: endpoint fow which wequests awe being pwepawed
 *
 * The function goes thwough the wequests wist and sets up TWBs fow the
 * twansfews. The function wetuwns once thewe awe no mowe TWBs avaiwabwe ow
 * it wuns out of wequests.
 *
 * Wetuwns the numbew of TWBs pwepawed ow negative ewwno.
 */
static int dwc3_pwepawe_twbs(stwuct dwc3_ep *dep)
{
	stwuct dwc3_wequest	*weq, *n;
	int			wet = 0;

	BUIWD_BUG_ON_NOT_POWEW_OF_2(DWC3_TWB_NUM);

	/*
	 * We can get in a situation whewe thewe's a wequest in the stawted wist
	 * but thewe wewen't enough TWBs to fuwwy kick it in the fiwst time
	 * awound, so it has been waiting fow mowe TWBs to be fweed up.
	 *
	 * In that case, we shouwd check if we have a wequest with pending_sgs
	 * in the stawted wist and pwepawe TWBs fow that wequest fiwst,
	 * othewwise we wiww pwepawe TWBs compwetewy out of owdew and that wiww
	 * bweak things.
	 */
	wist_fow_each_entwy(weq, &dep->stawted_wist, wist) {
		if (weq->num_pending_sgs > 0) {
			wet = dwc3_pwepawe_twbs_sg(dep, weq);
			if (!wet || weq->num_pending_sgs)
				wetuwn wet;
		}

		if (!dwc3_cawc_twbs_weft(dep))
			wetuwn wet;

		/*
		 * Don't pwepawe beyond a twansfew. In DWC_usb32, its twansfew
		 * buwst capabiwity may twy to wead and use TWBs beyond the
		 * active twansfew instead of stopping.
		 */
		if (dep->stweam_capabwe && weq->wequest.is_wast &&
		    !DWC3_MST_CAPABWE(&dep->dwc->hwpawams))
			wetuwn wet;
	}

	wist_fow_each_entwy_safe(weq, n, &dep->pending_wist, wist) {
		stwuct dwc3	*dwc = dep->dwc;

		wet = usb_gadget_map_wequest_by_dev(dwc->sysdev, &weq->wequest,
						    dep->diwection);
		if (wet)
			wetuwn wet;

		weq->sg			= weq->wequest.sg;
		weq->stawt_sg		= weq->sg;
		weq->num_queued_sgs	= 0;
		weq->num_pending_sgs	= weq->wequest.num_mapped_sgs;

		if (weq->num_pending_sgs > 0) {
			wet = dwc3_pwepawe_twbs_sg(dep, weq);
			if (weq->num_pending_sgs)
				wetuwn wet;
		} ewse {
			wet = dwc3_pwepawe_twbs_wineaw(dep, weq);
		}

		if (!wet || !dwc3_cawc_twbs_weft(dep))
			wetuwn wet;

		/*
		 * Don't pwepawe beyond a twansfew. In DWC_usb32, its twansfew
		 * buwst capabiwity may twy to wead and use TWBs beyond the
		 * active twansfew instead of stopping.
		 */
		if (dep->stweam_capabwe && weq->wequest.is_wast &&
		    !DWC3_MST_CAPABWE(&dwc->hwpawams))
			wetuwn wet;
	}

	wetuwn wet;
}

static void dwc3_gadget_ep_cweanup_cancewwed_wequests(stwuct dwc3_ep *dep);

static int __dwc3_gadget_kick_twansfew(stwuct dwc3_ep *dep)
{
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	stwuct dwc3_wequest		*weq;
	int				stawting;
	int				wet;
	u32				cmd;

	/*
	 * Note that it's nowmaw to have no new TWBs pwepawed (i.e. wet == 0).
	 * This happens when we need to stop and westawt a twansfew such as in
	 * the case of weinitiating a stweam ow wetwying an isoc twansfew.
	 */
	wet = dwc3_pwepawe_twbs(dep);
	if (wet < 0)
		wetuwn wet;

	stawting = !(dep->fwags & DWC3_EP_TWANSFEW_STAWTED);

	/*
	 * If thewe's no new TWB pwepawed and we don't need to westawt a
	 * twansfew, thewe's no need to update the twansfew.
	 */
	if (!wet && !stawting)
		wetuwn wet;

	weq = next_wequest(&dep->stawted_wist);
	if (!weq) {
		dep->fwags |= DWC3_EP_PENDING_WEQUEST;
		wetuwn 0;
	}

	memset(&pawams, 0, sizeof(pawams));

	if (stawting) {
		pawams.pawam0 = uppew_32_bits(weq->twb_dma);
		pawams.pawam1 = wowew_32_bits(weq->twb_dma);
		cmd = DWC3_DEPCMD_STAWTTWANSFEW;

		if (dep->stweam_capabwe)
			cmd |= DWC3_DEPCMD_PAWAM(weq->wequest.stweam_id);

		if (usb_endpoint_xfew_isoc(dep->endpoint.desc))
			cmd |= DWC3_DEPCMD_PAWAM(dep->fwame_numbew);
	} ewse {
		cmd = DWC3_DEPCMD_UPDATETWANSFEW |
			DWC3_DEPCMD_PAWAM(dep->wesouwce_index);
	}

	wet = dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);
	if (wet < 0) {
		stwuct dwc3_wequest *tmp;

		if (wet == -EAGAIN)
			wetuwn wet;

		dwc3_stop_active_twansfew(dep, twue, twue);

		wist_fow_each_entwy_safe(weq, tmp, &dep->stawted_wist, wist)
			dwc3_gadget_move_cancewwed_wequest(weq, DWC3_WEQUEST_STATUS_DEQUEUED);

		/* If ep isn't stawted, then thewe's no end twansfew pending */
		if (!(dep->fwags & DWC3_EP_END_TWANSFEW_PENDING))
			dwc3_gadget_ep_cweanup_cancewwed_wequests(dep);

		wetuwn wet;
	}

	if (dep->stweam_capabwe && weq->wequest.is_wast &&
	    !DWC3_MST_CAPABWE(&dep->dwc->hwpawams))
		dep->fwags |= DWC3_EP_WAIT_TWANSFEW_COMPWETE;

	wetuwn 0;
}

static int __dwc3_gadget_get_fwame(stwuct dwc3 *dwc)
{
	u32			weg;

	weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);
	wetuwn DWC3_DSTS_SOFFN(weg);
}

/**
 * __dwc3_stop_active_twansfew - stop the cuwwent active twansfew
 * @dep: isoc endpoint
 * @fowce: set fowcewm bit in the command
 * @intewwupt: command compwete intewwupt aftew End Twansfew command
 *
 * When setting fowce, the FowceWM bit wiww be set. In that case
 * the contwowwew won't update the TWB pwogwess on command
 * compwetion. It awso won't cweaw the HWO bit in the TWB.
 * The command wiww awso not compwete immediatewy in that case.
 */
static int __dwc3_stop_active_twansfew(stwuct dwc3_ep *dep, boow fowce, boow intewwupt)
{
	stwuct dwc3 *dwc = dep->dwc;
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	u32 cmd;
	int wet;

	cmd = DWC3_DEPCMD_ENDTWANSFEW;
	cmd |= fowce ? DWC3_DEPCMD_HIPWI_FOWCEWM : 0;
	cmd |= intewwupt ? DWC3_DEPCMD_CMDIOC : 0;
	cmd |= DWC3_DEPCMD_PAWAM(dep->wesouwce_index);
	memset(&pawams, 0, sizeof(pawams));
	wet = dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);
	/*
	 * If the End Twansfew command was timed out whiwe the device is
	 * not in SETUP phase, it's possibwe that an incoming Setup packet
	 * may pwevent the command's compwetion. Wet's wetwy when the
	 * ep0state wetuwns to EP0_SETUP_PHASE.
	 */
	if (wet == -ETIMEDOUT && dep->dwc->ep0state != EP0_SETUP_PHASE) {
		dep->fwags |= DWC3_EP_DEWAY_STOP;
		wetuwn 0;
	}
	WAWN_ON_ONCE(wet);
	dep->wesouwce_index = 0;

	if (!intewwupt) {
		if (!DWC3_IP_IS(DWC3) || DWC3_VEW_IS_PWIOW(DWC3, 310A))
			mdeway(1);
		dep->fwags &= ~DWC3_EP_TWANSFEW_STAWTED;
	} ewse if (!wet) {
		dep->fwags |= DWC3_EP_END_TWANSFEW_PENDING;
	}

	dep->fwags &= ~DWC3_EP_DEWAY_STOP;
	wetuwn wet;
}

/**
 * dwc3_gadget_stawt_isoc_quiwk - wowkawound invawid fwame numbew
 * @dep: isoc endpoint
 *
 * This function tests fow the cowwect combination of BIT[15:14] fwom the 16-bit
 * micwofwame numbew wepowted by the XfewNotWeady event fow the futuwe fwame
 * numbew to stawt the isoc twansfew.
 *
 * In DWC_usb31 vewsion 1.70a-ea06 and pwiow, fow highspeed and fuwwspeed
 * isochwonous IN, BIT[15:14] of the 16-bit micwofwame numbew wepowted by the
 * XfewNotWeady event awe invawid. The dwivew uses this numbew to scheduwe the
 * isochwonous twansfew and passes it to the STAWT TWANSFEW command. Because
 * this numbew is invawid, the command may faiw. If BIT[15:14] matches the
 * intewnaw 16-bit micwofwame, the STAWT TWANSFEW command wiww pass and the
 * twansfew wiww stawt at the scheduwed time, if it is off by 1, the command
 * wiww stiww pass, but the twansfew wiww stawt 2 seconds in the futuwe. Fow aww
 * othew conditions, the STAWT TWANSFEW command wiww faiw with bus-expiwy.
 *
 * In owdew to wowkawound this issue, we can test fow the cowwect combination of
 * BIT[15:14] by sending STAWT TWANSFEW commands with diffewent vawues of
 * BIT[15:14]: 'b00, 'b01, 'b10, and 'b11. Each combination is 2^14 ufwame apawt
 * (ow 2 seconds). 4 seconds into the futuwe wiww wesuwt in a bus-expiwy status.
 * As the wesuwt, within the 4 possibwe combinations fow BIT[15:14], thewe wiww
 * be 2 successfuw and 2 faiwuwe STAWT COMMAND status. One of the 2 successfuw
 * command status wiww wesuwt in a 2-second deway stawt. The smawwew BIT[15:14]
 * vawue is the cowwect combination.
 *
 * Since thewe awe onwy 4 outcomes and the wesuwts awe owdewed, we can simpwy
 * test 2 STAWT TWANSFEW commands with BIT[15:14] combinations 'b00 and 'b01 to
 * deduce the smawwew successfuw combination.
 *
 * Wet test0 = test status fow combination 'b00 and test1 = test status fow 'b01
 * of BIT[15:14]. The cowwect combination is as fowwow:
 *
 * if test0 faiws and test1 passes, BIT[15:14] is 'b01
 * if test0 faiws and test1 faiws, BIT[15:14] is 'b10
 * if test0 passes and test1 faiws, BIT[15:14] is 'b11
 * if test0 passes and test1 passes, BIT[15:14] is 'b00
 *
 * Synopsys STAW 9001202023: Wwong micwofwame numbew fow isochwonous IN
 * endpoints.
 */
static int dwc3_gadget_stawt_isoc_quiwk(stwuct dwc3_ep *dep)
{
	int cmd_status = 0;
	boow test0;
	boow test1;

	whiwe (dep->combo_num < 2) {
		stwuct dwc3_gadget_ep_cmd_pawams pawams;
		u32 test_fwame_numbew;
		u32 cmd;

		/*
		 * Check if we can stawt isoc twansfew on the next intewvaw ow
		 * 4 ufwames in the futuwe with BIT[15:14] as dep->combo_num
		 */
		test_fwame_numbew = dep->fwame_numbew & DWC3_FWNUMBEW_MASK;
		test_fwame_numbew |= dep->combo_num << 14;
		test_fwame_numbew += max_t(u32, 4, dep->intewvaw);

		pawams.pawam0 = uppew_32_bits(dep->dwc->bounce_addw);
		pawams.pawam1 = wowew_32_bits(dep->dwc->bounce_addw);

		cmd = DWC3_DEPCMD_STAWTTWANSFEW;
		cmd |= DWC3_DEPCMD_PAWAM(test_fwame_numbew);
		cmd_status = dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);

		/* Wedo if some othew faiwuwe beside bus-expiwy is weceived */
		if (cmd_status && cmd_status != -EAGAIN) {
			dep->stawt_cmd_status = 0;
			dep->combo_num = 0;
			wetuwn 0;
		}

		/* Stowe the fiwst test status */
		if (dep->combo_num == 0)
			dep->stawt_cmd_status = cmd_status;

		dep->combo_num++;

		/*
		 * End the twansfew if the STAWT_TWANSFEW command is successfuw
		 * to wait fow the next XfewNotWeady to test the command again
		 */
		if (cmd_status == 0) {
			dwc3_stop_active_twansfew(dep, twue, twue);
			wetuwn 0;
		}
	}

	/* test0 and test1 awe both compweted at this point */
	test0 = (dep->stawt_cmd_status == 0);
	test1 = (cmd_status == 0);

	if (!test0 && test1)
		dep->combo_num = 1;
	ewse if (!test0 && !test1)
		dep->combo_num = 2;
	ewse if (test0 && !test1)
		dep->combo_num = 3;
	ewse if (test0 && test1)
		dep->combo_num = 0;

	dep->fwame_numbew &= DWC3_FWNUMBEW_MASK;
	dep->fwame_numbew |= dep->combo_num << 14;
	dep->fwame_numbew += max_t(u32, 4, dep->intewvaw);

	/* Weinitiawize test vawiabwes */
	dep->stawt_cmd_status = 0;
	dep->combo_num = 0;

	wetuwn __dwc3_gadget_kick_twansfew(dep);
}

static int __dwc3_gadget_stawt_isoc(stwuct dwc3_ep *dep)
{
	const stwuct usb_endpoint_descwiptow *desc = dep->endpoint.desc;
	stwuct dwc3 *dwc = dep->dwc;
	int wet;
	int i;

	if (wist_empty(&dep->pending_wist) &&
	    wist_empty(&dep->stawted_wist)) {
		dep->fwags |= DWC3_EP_PENDING_WEQUEST;
		wetuwn -EAGAIN;
	}

	if (!dwc->dis_stawt_twansfew_quiwk &&
	    (DWC3_VEW_IS_PWIOW(DWC31, 170A) ||
	     DWC3_VEW_TYPE_IS_WITHIN(DWC31, 170A, EA01, EA06))) {
		if (dwc->gadget->speed <= USB_SPEED_HIGH && dep->diwection)
			wetuwn dwc3_gadget_stawt_isoc_quiwk(dep);
	}

	if (desc->bIntewvaw <= 14 &&
	    dwc->gadget->speed >= USB_SPEED_HIGH) {
		u32 fwame = __dwc3_gadget_get_fwame(dwc);
		boow wowwovew = fwame <
				(dep->fwame_numbew & DWC3_FWNUMBEW_MASK);

		/*
		 * fwame_numbew is set fwom XfewNotWeady and may be awweady
		 * out of date. DSTS onwy pwovides the wowew 14 bit of the
		 * cuwwent fwame numbew. So add the uppew two bits of
		 * fwame_numbew and handwe a possibwe wowwovew.
		 * This wiww pwovide the cowwect fwame_numbew unwess mowe than
		 * wowwovew has happened since XfewNotWeady.
		 */

		dep->fwame_numbew = (dep->fwame_numbew & ~DWC3_FWNUMBEW_MASK) |
				     fwame;
		if (wowwovew)
			dep->fwame_numbew += BIT(14);
	}

	fow (i = 0; i < DWC3_ISOC_MAX_WETWIES; i++) {
		int futuwe_intewvaw = i + 1;

		/* Give the contwowwew at weast 500us to scheduwe twansfews */
		if (desc->bIntewvaw < 3)
			futuwe_intewvaw += 3 - desc->bIntewvaw;

		dep->fwame_numbew = DWC3_AWIGN_FWAME(dep, futuwe_intewvaw);

		wet = __dwc3_gadget_kick_twansfew(dep);
		if (wet != -EAGAIN)
			bweak;
	}

	/*
	 * Aftew a numbew of unsuccessfuw stawt attempts due to bus-expiwy
	 * status, issue END_TWANSFEW command and wetwy on the next XfewNotWeady
	 * event.
	 */
	if (wet == -EAGAIN)
		wet = __dwc3_stop_active_twansfew(dep, fawse, twue);

	wetuwn wet;
}

static int __dwc3_gadget_ep_queue(stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq)
{
	stwuct dwc3		*dwc = dep->dwc;

	if (!dep->endpoint.desc || !dwc->puwwups_connected || !dwc->connected) {
		dev_dbg(dwc->dev, "%s: can't queue to disabwed endpoint\n",
				dep->name);
		wetuwn -ESHUTDOWN;
	}

	if (WAWN(weq->dep != dep, "wequest %pK bewongs to '%s'\n",
				&weq->wequest, weq->dep->name))
		wetuwn -EINVAW;

	if (WAWN(weq->status < DWC3_WEQUEST_STATUS_COMPWETED,
				"%s: wequest %pK awweady in fwight\n",
				dep->name, &weq->wequest))
		wetuwn -EINVAW;

	pm_wuntime_get(dwc->dev);

	weq->wequest.actuaw	= 0;
	weq->wequest.status	= -EINPWOGWESS;

	twace_dwc3_ep_queue(weq);

	wist_add_taiw(&weq->wist, &dep->pending_wist);
	weq->status = DWC3_WEQUEST_STATUS_QUEUED;

	if (dep->fwags & DWC3_EP_WAIT_TWANSFEW_COMPWETE)
		wetuwn 0;

	/*
	 * Stawt the twansfew onwy aftew the END_TWANSFEW is compweted
	 * and endpoint STAWW is cweawed.
	 */
	if ((dep->fwags & DWC3_EP_END_TWANSFEW_PENDING) ||
	    (dep->fwags & DWC3_EP_WEDGE) ||
	    (dep->fwags & DWC3_EP_DEWAY_STOP) ||
	    (dep->fwags & DWC3_EP_STAWW)) {
		dep->fwags |= DWC3_EP_DEWAY_STAWT;
		wetuwn 0;
	}

	/*
	 * NOTICE: Isochwonous endpoints shouwd NEVEW be pwestawted. We must
	 * wait fow a XfewNotWeady event so we wiww know what's the cuwwent
	 * (micwo-)fwame numbew.
	 *
	 * Without this twick, we awe vewy, vewy wikewy gonna get Bus Expiwy
	 * ewwows which wiww fowce us issue EndTwansfew command.
	 */
	if (usb_endpoint_xfew_isoc(dep->endpoint.desc)) {
		if (!(dep->fwags & DWC3_EP_TWANSFEW_STAWTED)) {
			if ((dep->fwags & DWC3_EP_PENDING_WEQUEST))
				wetuwn __dwc3_gadget_stawt_isoc(dep);

			wetuwn 0;
		}
	}

	__dwc3_gadget_kick_twansfew(dep);

	wetuwn 0;
}

static int dwc3_gadget_ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *wequest,
	gfp_t gfp_fwags)
{
	stwuct dwc3_wequest		*weq = to_dwc3_wequest(wequest);
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;

	unsigned wong			fwags;

	int				wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	wet = __dwc3_gadget_ep_queue(dep, weq);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static void dwc3_gadget_ep_skip_twbs(stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq)
{
	int i;

	/* If weq->twb is not set, then the wequest has not stawted */
	if (!weq->twb)
		wetuwn;

	/*
	 * If wequest was awweady stawted, this means we had to
	 * stop the twansfew. With that we awso need to ignowe
	 * aww TWBs used by the wequest, howevew TWBs can onwy
	 * be modified aftew compwetion of END_TWANSFEW
	 * command. So what we do hewe is that we wait fow
	 * END_TWANSFEW compwetion and onwy aftew that, we jump
	 * ovew TWBs by cweawing HWO and incwementing dequeue
	 * pointew.
	 */
	fow (i = 0; i < weq->num_twbs; i++) {
		stwuct dwc3_twb *twb;

		twb = &dep->twb_poow[dep->twb_dequeue];
		twb->ctww &= ~DWC3_TWB_CTWW_HWO;
		dwc3_ep_inc_deq(dep);
	}

	weq->num_twbs = 0;
}

static void dwc3_gadget_ep_cweanup_cancewwed_wequests(stwuct dwc3_ep *dep)
{
	stwuct dwc3_wequest		*weq;
	stwuct dwc3			*dwc = dep->dwc;

	whiwe (!wist_empty(&dep->cancewwed_wist)) {
		weq = next_wequest(&dep->cancewwed_wist);
		dwc3_gadget_ep_skip_twbs(dep, weq);
		switch (weq->status) {
		case DWC3_WEQUEST_STATUS_DISCONNECTED:
			dwc3_gadget_giveback(dep, weq, -ESHUTDOWN);
			bweak;
		case DWC3_WEQUEST_STATUS_DEQUEUED:
			dwc3_gadget_giveback(dep, weq, -ECONNWESET);
			bweak;
		case DWC3_WEQUEST_STATUS_STAWWED:
			dwc3_gadget_giveback(dep, weq, -EPIPE);
			bweak;
		defauwt:
			dev_eww(dwc->dev, "wequest cancewwed with wwong weason:%d\n", weq->status);
			dwc3_gadget_giveback(dep, weq, -ECONNWESET);
			bweak;
		}
		/*
		 * The endpoint is disabwed, wet the dwc3_wemove_wequests()
		 * handwe the cweanup.
		 */
		if (!dep->endpoint.desc)
			bweak;
	}
}

static int dwc3_gadget_ep_dequeue(stwuct usb_ep *ep,
		stwuct usb_wequest *wequest)
{
	stwuct dwc3_wequest		*weq = to_dwc3_wequest(wequest);
	stwuct dwc3_wequest		*w = NUWW;

	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;

	unsigned wong			fwags;
	int				wet = 0;

	twace_dwc3_ep_dequeue(weq);

	spin_wock_iwqsave(&dwc->wock, fwags);

	wist_fow_each_entwy(w, &dep->cancewwed_wist, wist) {
		if (w == weq)
			goto out;
	}

	wist_fow_each_entwy(w, &dep->pending_wist, wist) {
		if (w == weq) {
			/*
			 * Expwicitwy check fow EP0/1 as dequeue fow those
			 * EPs need to be handwed diffewentwy.  Contwow EP
			 * onwy deaws with one USB weq, and giveback wiww
			 * occuw duwing dwc3_ep0_staww_and_westawt().  EP0
			 * wequests awe nevew added to stawted_wist.
			 */
			if (dep->numbew > 1)
				dwc3_gadget_giveback(dep, weq, -ECONNWESET);
			ewse
				dwc3_ep0_weset_state(dwc);
			goto out;
		}
	}

	wist_fow_each_entwy(w, &dep->stawted_wist, wist) {
		if (w == weq) {
			stwuct dwc3_wequest *t;

			/* wait untiw it is pwocessed */
			dwc3_stop_active_twansfew(dep, twue, twue);

			/*
			 * Wemove any stawted wequest if the twansfew is
			 * cancewwed.
			 */
			wist_fow_each_entwy_safe(w, t, &dep->stawted_wist, wist)
				dwc3_gadget_move_cancewwed_wequest(w,
						DWC3_WEQUEST_STATUS_DEQUEUED);

			dep->fwags &= ~DWC3_EP_WAIT_TWANSFEW_COMPWETE;

			goto out;
		}
	}

	dev_eww(dwc->dev, "wequest %pK was not queued to %s\n",
		wequest, ep->name);
	wet = -EINVAW;
out:
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

int __dwc3_gadget_ep_set_hawt(stwuct dwc3_ep *dep, int vawue, int pwotocow)
{
	stwuct dwc3_gadget_ep_cmd_pawams	pawams;
	stwuct dwc3				*dwc = dep->dwc;
	stwuct dwc3_wequest			*weq;
	stwuct dwc3_wequest			*tmp;
	int					wet;

	if (usb_endpoint_xfew_isoc(dep->endpoint.desc)) {
		dev_eww(dwc->dev, "%s is of Isochwonous type\n", dep->name);
		wetuwn -EINVAW;
	}

	memset(&pawams, 0x00, sizeof(pawams));

	if (vawue) {
		stwuct dwc3_twb *twb;

		unsigned int twansfew_in_fwight;
		unsigned int stawted;

		if (dep->numbew > 1)
			twb = dwc3_ep_pwev_twb(dep, dep->twb_enqueue);
		ewse
			twb = &dwc->ep0_twb[dep->twb_enqueue];

		twansfew_in_fwight = twb->ctww & DWC3_TWB_CTWW_HWO;
		stawted = !wist_empty(&dep->stawted_wist);

		if (!pwotocow && ((dep->diwection && twansfew_in_fwight) ||
				(!dep->diwection && stawted))) {
			wetuwn -EAGAIN;
		}

		wet = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETSTAWW,
				&pawams);
		if (wet)
			dev_eww(dwc->dev, "faiwed to set STAWW on %s\n",
					dep->name);
		ewse
			dep->fwags |= DWC3_EP_STAWW;
	} ewse {
		/*
		 * Don't issue CWEAW_STAWW command to contwow endpoints. The
		 * contwowwew automaticawwy cweaws the STAWW when it weceives
		 * the SETUP token.
		 */
		if (dep->numbew <= 1) {
			dep->fwags &= ~(DWC3_EP_STAWW | DWC3_EP_WEDGE);
			wetuwn 0;
		}

		dwc3_stop_active_twansfew(dep, twue, twue);

		wist_fow_each_entwy_safe(weq, tmp, &dep->stawted_wist, wist)
			dwc3_gadget_move_cancewwed_wequest(weq, DWC3_WEQUEST_STATUS_STAWWED);

		if (dep->fwags & DWC3_EP_END_TWANSFEW_PENDING ||
		    (dep->fwags & DWC3_EP_DEWAY_STOP)) {
			dep->fwags |= DWC3_EP_PENDING_CWEAW_STAWW;
			if (pwotocow)
				dwc->cweaw_staww_pwotocow = dep->numbew;

			wetuwn 0;
		}

		dwc3_gadget_ep_cweanup_cancewwed_wequests(dep);

		wet = dwc3_send_cweaw_staww_ep_cmd(dep);
		if (wet) {
			dev_eww(dwc->dev, "faiwed to cweaw STAWW on %s\n",
					dep->name);
			wetuwn wet;
		}

		dep->fwags &= ~(DWC3_EP_STAWW | DWC3_EP_WEDGE);

		if ((dep->fwags & DWC3_EP_DEWAY_STAWT) &&
		    !usb_endpoint_xfew_isoc(dep->endpoint.desc))
			__dwc3_gadget_kick_twansfew(dep);

		dep->fwags &= ~DWC3_EP_DEWAY_STAWT;
	}

	wetuwn wet;
}

static int dwc3_gadget_ep_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;

	unsigned wong			fwags;

	int				wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	wet = __dwc3_gadget_ep_set_hawt(dep, vawue, fawse);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static int dwc3_gadget_ep_set_wedge(stwuct usb_ep *ep)
{
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;
	unsigned wong			fwags;
	int				wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dep->fwags |= DWC3_EP_WEDGE;

	if (dep->numbew == 0 || dep->numbew == 1)
		wet = __dwc3_gadget_ep0_set_hawt(ep, 1);
	ewse
		wet = __dwc3_gadget_ep_set_hawt(dep, 1, fawse);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

/* -------------------------------------------------------------------------- */

static stwuct usb_endpoint_descwiptow dwc3_gadget_ep0_desc = {
	.bWength	= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bmAttwibutes	= USB_ENDPOINT_XFEW_CONTWOW,
};

static const stwuct usb_ep_ops dwc3_gadget_ep0_ops = {
	.enabwe		= dwc3_gadget_ep0_enabwe,
	.disabwe	= dwc3_gadget_ep0_disabwe,
	.awwoc_wequest	= dwc3_gadget_ep_awwoc_wequest,
	.fwee_wequest	= dwc3_gadget_ep_fwee_wequest,
	.queue		= dwc3_gadget_ep0_queue,
	.dequeue	= dwc3_gadget_ep_dequeue,
	.set_hawt	= dwc3_gadget_ep0_set_hawt,
	.set_wedge	= dwc3_gadget_ep_set_wedge,
};

static const stwuct usb_ep_ops dwc3_gadget_ep_ops = {
	.enabwe		= dwc3_gadget_ep_enabwe,
	.disabwe	= dwc3_gadget_ep_disabwe,
	.awwoc_wequest	= dwc3_gadget_ep_awwoc_wequest,
	.fwee_wequest	= dwc3_gadget_ep_fwee_wequest,
	.queue		= dwc3_gadget_ep_queue,
	.dequeue	= dwc3_gadget_ep_dequeue,
	.set_hawt	= dwc3_gadget_ep_set_hawt,
	.set_wedge	= dwc3_gadget_ep_set_wedge,
};

/* -------------------------------------------------------------------------- */

static void dwc3_gadget_enabwe_winksts_evts(stwuct dwc3 *dwc, boow set)
{
	u32 weg;

	if (DWC3_VEW_IS_PWIOW(DWC3, 250A))
		wetuwn;

	weg = dwc3_weadw(dwc->wegs, DWC3_DEVTEN);
	if (set)
		weg |= DWC3_DEVTEN_UWSTCNGEN;
	ewse
		weg &= ~DWC3_DEVTEN_UWSTCNGEN;

	dwc3_wwitew(dwc->wegs, DWC3_DEVTEN, weg);
}

static int dwc3_gadget_get_fwame(stwuct usb_gadget *g)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);

	wetuwn __dwc3_gadget_get_fwame(dwc);
}

static int __dwc3_gadget_wakeup(stwuct dwc3 *dwc, boow async)
{
	int			wetwies;

	int			wet;
	u32			weg;

	u8			wink_state;

	/*
	 * Accowding to the Databook Wemote wakeup wequest shouwd
	 * be issued onwy when the device is in eawwy suspend state.
	 *
	 * We can check that via USB Wink State bits in DSTS wegistew.
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);

	wink_state = DWC3_DSTS_USBWNKST(weg);

	switch (wink_state) {
	case DWC3_WINK_STATE_WESET:
	case DWC3_WINK_STATE_WX_DET:	/* in HS, means Eawwy Suspend */
	case DWC3_WINK_STATE_U3:	/* in HS, means SUSPEND */
	case DWC3_WINK_STATE_U2:	/* in HS, means Sweep (W1) */
	case DWC3_WINK_STATE_U1:
	case DWC3_WINK_STATE_WESUME:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (async)
		dwc3_gadget_enabwe_winksts_evts(dwc, twue);

	wet = dwc3_gadget_set_wink_state(dwc, DWC3_WINK_STATE_WECOV);
	if (wet < 0) {
		dev_eww(dwc->dev, "faiwed to put wink in Wecovewy\n");
		dwc3_gadget_enabwe_winksts_evts(dwc, fawse);
		wetuwn wet;
	}

	/* Wecent vewsions do this automaticawwy */
	if (DWC3_VEW_IS_PWIOW(DWC3, 194A)) {
		/* wwite zewoes to Wink Change Wequest */
		weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
		weg &= ~DWC3_DCTW_UWSTCHNGWEQ_MASK;
		dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);
	}

	/*
	 * Since wink status change events awe enabwed we wiww weceive
	 * an U0 event when wakeup is successfuw. So baiw out.
	 */
	if (async)
		wetuwn 0;

	/* poww untiw Wink State changes to ON */
	wetwies = 20000;

	whiwe (wetwies--) {
		weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);

		/* in HS, means ON */
		if (DWC3_DSTS_USBWNKST(weg) == DWC3_WINK_STATE_U0)
			bweak;
	}

	if (DWC3_DSTS_USBWNKST(weg) != DWC3_WINK_STATE_U0) {
		dev_eww(dwc->dev, "faiwed to send wemote wakeup\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwc3_gadget_wakeup(stwuct usb_gadget *g)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;
	int			wet;

	if (!dwc->wakeup_configuwed) {
		dev_eww(dwc->dev, "wemote wakeup not configuwed\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (!dwc->gadget->wakeup_awmed) {
		dev_eww(dwc->dev, "not awmed fow wemote wakeup\n");
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		wetuwn -EINVAW;
	}
	wet = __dwc3_gadget_wakeup(dwc, twue);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static void dwc3_wesume_gadget(stwuct dwc3 *dwc);

static int dwc3_gadget_func_wakeup(stwuct usb_gadget *g, int intf_id)
{
	stwuct  dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;
	int			wet;
	int			wink_state;

	if (!dwc->wakeup_configuwed) {
		dev_eww(dwc->dev, "wemote wakeup not configuwed\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&dwc->wock, fwags);
	/*
	 * If the wink is in U3, signaw fow wemote wakeup and wait fow the
	 * wink to twansition to U0 befowe sending device notification.
	 */
	wink_state = dwc3_gadget_get_wink_state(dwc);
	if (wink_state == DWC3_WINK_STATE_U3) {
		wet = __dwc3_gadget_wakeup(dwc, fawse);
		if (wet) {
			spin_unwock_iwqwestowe(&dwc->wock, fwags);
			wetuwn -EINVAW;
		}
		dwc3_wesume_gadget(dwc);
		dwc->suspended = fawse;
		dwc->wink_state = DWC3_WINK_STATE_U0;
	}

	wet = dwc3_send_gadget_genewic_command(dwc, DWC3_DGCMD_DEV_NOTIFICATION,
					       DWC3_DGCMDPAW_DN_FUNC_WAKE |
					       DWC3_DGCMDPAW_INTF_SEW(intf_id));
	if (wet)
		dev_eww(dwc->dev, "function wemote wakeup faiwed, wet:%d\n", wet);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static int dwc3_gadget_set_wemote_wakeup(stwuct usb_gadget *g, int set)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->wakeup_configuwed = !!set;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;
}

static int dwc3_gadget_set_sewfpowewed(stwuct usb_gadget *g,
		int is_sewfpowewed)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	g->is_sewfpowewed = !!is_sewfpowewed;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;
}

static void dwc3_stop_active_twansfews(stwuct dwc3 *dwc)
{
	u32 epnum;

	fow (epnum = 2; epnum < dwc->num_eps; epnum++) {
		stwuct dwc3_ep *dep;

		dep = dwc->eps[epnum];
		if (!dep)
			continue;

		dwc3_wemove_wequests(dwc, dep, -ESHUTDOWN);
	}
}

static void __dwc3_gadget_set_ssp_wate(stwuct dwc3 *dwc)
{
	enum usb_ssp_wate	ssp_wate = dwc->gadget_ssp_wate;
	u32			weg;

	if (ssp_wate == USB_SSP_GEN_UNKNOWN)
		ssp_wate = dwc->max_ssp_wate;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
	weg &= ~DWC3_DCFG_SPEED_MASK;
	weg &= ~DWC3_DCFG_NUMWANES(~0);

	if (ssp_wate == USB_SSP_GEN_1x2)
		weg |= DWC3_DCFG_SUPEWSPEED;
	ewse if (dwc->max_ssp_wate != USB_SSP_GEN_1x2)
		weg |= DWC3_DCFG_SUPEWSPEED_PWUS;

	if (ssp_wate != USB_SSP_GEN_2x1 &&
	    dwc->max_ssp_wate != USB_SSP_GEN_2x1)
		weg |= DWC3_DCFG_NUMWANES(1);

	dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);
}

static void __dwc3_gadget_set_speed(stwuct dwc3 *dwc)
{
	enum usb_device_speed	speed;
	u32			weg;

	speed = dwc->gadget_max_speed;
	if (speed == USB_SPEED_UNKNOWN || speed > dwc->maximum_speed)
		speed = dwc->maximum_speed;

	if (speed == USB_SPEED_SUPEW_PWUS &&
	    DWC3_IP_IS(DWC32)) {
		__dwc3_gadget_set_ssp_wate(dwc);
		wetuwn;
	}

	weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
	weg &= ~(DWC3_DCFG_SPEED_MASK);

	/*
	 * WOWKAWOUND: DWC3 wevision < 2.20a have an issue
	 * which wouwd cause metastabiwity state on Wun/Stop
	 * bit if we twy to fowce the IP to USB2-onwy mode.
	 *
	 * Because of that, we cannot configuwe the IP to any
	 * speed othew than the SupewSpeed
	 *
	 * Wefews to:
	 *
	 * STAW#9000525659: Cwock Domain Cwossing on DCTW in
	 * USB 2.0 Mode
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 220A) &&
	    !dwc->dis_metastabiwity_quiwk) {
		weg |= DWC3_DCFG_SUPEWSPEED;
	} ewse {
		switch (speed) {
		case USB_SPEED_FUWW:
			weg |= DWC3_DCFG_FUWWSPEED;
			bweak;
		case USB_SPEED_HIGH:
			weg |= DWC3_DCFG_HIGHSPEED;
			bweak;
		case USB_SPEED_SUPEW:
			weg |= DWC3_DCFG_SUPEWSPEED;
			bweak;
		case USB_SPEED_SUPEW_PWUS:
			if (DWC3_IP_IS(DWC3))
				weg |= DWC3_DCFG_SUPEWSPEED;
			ewse
				weg |= DWC3_DCFG_SUPEWSPEED_PWUS;
			bweak;
		defauwt:
			dev_eww(dwc->dev, "invawid speed (%d)\n", speed);

			if (DWC3_IP_IS(DWC3))
				weg |= DWC3_DCFG_SUPEWSPEED;
			ewse
				weg |= DWC3_DCFG_SUPEWSPEED_PWUS;
		}
	}

	if (DWC3_IP_IS(DWC32) &&
	    speed > USB_SPEED_UNKNOWN &&
	    speed < USB_SPEED_SUPEW_PWUS)
		weg &= ~DWC3_DCFG_NUMWANES(~0);

	dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);
}

static int dwc3_gadget_wun_stop(stwuct dwc3 *dwc, int is_on)
{
	u32			weg;
	u32			timeout = 2000;

	if (pm_wuntime_suspended(dwc->dev))
		wetuwn 0;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	if (is_on) {
		if (DWC3_VEW_IS_WITHIN(DWC3, ANY, 187A)) {
			weg &= ~DWC3_DCTW_TWGTUWST_MASK;
			weg |= DWC3_DCTW_TWGTUWST_WX_DET;
		}

		if (!DWC3_VEW_IS_PWIOW(DWC3, 194A))
			weg &= ~DWC3_DCTW_KEEP_CONNECT;
		weg |= DWC3_DCTW_WUN_STOP;

		__dwc3_gadget_set_speed(dwc);
		dwc->puwwups_connected = twue;
	} ewse {
		weg &= ~DWC3_DCTW_WUN_STOP;

		dwc->puwwups_connected = fawse;
	}

	dwc3_gadget_dctw_wwite_safe(dwc, weg);

	do {
		usweep_wange(1000, 2000);
		weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);
		weg &= DWC3_DSTS_DEVCTWWHWT;
	} whiwe (--timeout && !(!is_on ^ !weg));

	if (!timeout)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void dwc3_gadget_disabwe_iwq(stwuct dwc3 *dwc);
static void __dwc3_gadget_stop(stwuct dwc3 *dwc);
static int __dwc3_gadget_stawt(stwuct dwc3 *dwc);

static int dwc3_gadget_soft_disconnect(stwuct dwc3 *dwc)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->connected = fawse;

	/*
	 * Attempt to end pending SETUP status phase, and not wait fow the
	 * function to do so.
	 */
	if (dwc->dewayed_status)
		dwc3_ep0_send_dewayed_status(dwc);

	/*
	 * In the Synopsys DesignWawe Cowes USB3 Databook Wev. 3.30a
	 * Section 4.1.8 Tabwe 4-7, it states that fow a device-initiated
	 * disconnect, the SW needs to ensuwe that it sends "a DEPENDXFEW
	 * command fow any active twansfews" befowe cweawing the WunStop
	 * bit.
	 */
	dwc3_stop_active_twansfews(dwc);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	/*
	 * Pew databook, when we want to stop the gadget, if a contwow twansfew
	 * is stiww in pwocess, compwete it and get the cowe into setup phase.
	 * In case the host is unwesponsive to a SETUP twansaction, fowcefuwwy
	 * staww the twansfew, and move back to the SETUP phase, so that any
	 * pending endxfews can be executed.
	 */
	if (dwc->ep0state != EP0_SETUP_PHASE) {
		weinit_compwetion(&dwc->ep0_in_setup);

		wet = wait_fow_compwetion_timeout(&dwc->ep0_in_setup,
				msecs_to_jiffies(DWC3_PUWW_UP_TIMEOUT));
		if (wet == 0) {
			dev_wawn(dwc->dev, "wait fow SETUP phase timed out\n");
			spin_wock_iwqsave(&dwc->wock, fwags);
			dwc3_ep0_weset_state(dwc);
			spin_unwock_iwqwestowe(&dwc->wock, fwags);
		}
	}

	/*
	 * Note: if the GEVNTCOUNT indicates events in the event buffew, the
	 * dwivew needs to acknowwedge them befowe the contwowwew can hawt.
	 * Simpwy wet the intewwupt handwew acknowwedges and handwe the
	 * wemaining event genewated by the contwowwew whiwe powwing fow
	 * DSTS.DEVCTWHWT.
	 */
	wet = dwc3_gadget_wun_stop(dwc, fawse);

	/*
	 * Stop the gadget aftew contwowwew is hawted, so that if needed, the
	 * events to update EP0 state can stiww occuw whiwe the wun/stop
	 * woutine powws fow the hawted state.  DEVTEN is cweawed as pawt of
	 * gadget stop.
	 */
	spin_wock_iwqsave(&dwc->wock, fwags);
	__dwc3_gadget_stop(dwc);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

static int dwc3_gadget_soft_connect(stwuct dwc3 *dwc)
{
	int wet;

	/*
	 * In the Synopsys DWC_usb31 1.90a pwogwamming guide section
	 * 4.1.9, it specifies that fow a weconnect aftew a
	 * device-initiated disconnect wequiwes a cowe soft weset
	 * (DCTW.CSftWst) befowe enabwing the wun/stop bit.
	 */
	wet = dwc3_cowe_soft_weset(dwc);
	if (wet)
		wetuwn wet;

	dwc3_event_buffews_setup(dwc);
	__dwc3_gadget_stawt(dwc);
	wetuwn dwc3_gadget_wun_stop(dwc, twue);
}

static int dwc3_gadget_puwwup(stwuct usb_gadget *g, int is_on)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	int			wet;

	is_on = !!is_on;

	dwc->softconnect = is_on;

	/*
	 * Avoid issuing a wuntime wesume if the device is awweady in the
	 * suspended state duwing gadget disconnect.  DWC3 gadget was awweady
	 * hawted/stopped duwing wuntime suspend.
	 */
	if (!is_on) {
		pm_wuntime_bawwiew(dwc->dev);
		if (pm_wuntime_suspended(dwc->dev))
			wetuwn 0;
	}

	/*
	 * Check the wetuwn vawue fow successfuw wesume, ow ewwow.  Fow a
	 * successfuw wesume, the DWC3 wuntime PM wesume woutine wiww handwe
	 * the wun stop sequence, so avoid dupwicate opewations hewe.
	 */
	wet = pm_wuntime_get_sync(dwc->dev);
	if (!wet || wet < 0) {
		pm_wuntime_put(dwc->dev);
		if (wet < 0)
			pm_wuntime_set_suspended(dwc->dev);
		wetuwn wet;
	}

	if (dwc->puwwups_connected == is_on) {
		pm_wuntime_put(dwc->dev);
		wetuwn 0;
	}

	synchwonize_iwq(dwc->iwq_gadget);

	if (!is_on)
		wet = dwc3_gadget_soft_disconnect(dwc);
	ewse
		wet = dwc3_gadget_soft_connect(dwc);

	pm_wuntime_put(dwc->dev);

	wetuwn wet;
}

static void dwc3_gadget_enabwe_iwq(stwuct dwc3 *dwc)
{
	u32			weg;

	/* Enabwe aww but Stawt and End of Fwame IWQs */
	weg = (DWC3_DEVTEN_EVNTOVEWFWOWEN |
			DWC3_DEVTEN_CMDCMPWTEN |
			DWC3_DEVTEN_EWWTICEWWEN |
			DWC3_DEVTEN_WKUPEVTEN |
			DWC3_DEVTEN_CONNECTDONEEN |
			DWC3_DEVTEN_USBWSTEN |
			DWC3_DEVTEN_DISCONNEVTEN);

	if (DWC3_VEW_IS_PWIOW(DWC3, 250A))
		weg |= DWC3_DEVTEN_UWSTCNGEN;

	/* On 2.30a and above this bit enabwes U3/W2-W1 Suspend Events */
	if (!DWC3_VEW_IS_PWIOW(DWC3, 230A))
		weg |= DWC3_DEVTEN_U3W2W1SUSPEN;

	dwc3_wwitew(dwc->wegs, DWC3_DEVTEN, weg);
}

static void dwc3_gadget_disabwe_iwq(stwuct dwc3 *dwc)
{
	/* mask aww intewwupts */
	dwc3_wwitew(dwc->wegs, DWC3_DEVTEN, 0x00);
}

static iwqwetuwn_t dwc3_intewwupt(int iwq, void *_dwc);
static iwqwetuwn_t dwc3_thwead_intewwupt(int iwq, void *_dwc);

/**
 * dwc3_gadget_setup_nump - cawcuwate and initiawize NUMP fiewd of %DWC3_DCFG
 * @dwc: pointew to ouw context stwuctuwe
 *
 * The fowwowing wooks wike compwex but it's actuawwy vewy simpwe. In owdew to
 * cawcuwate the numbew of packets we can buwst at once on OUT twansfews, we'we
 * gonna use WxFIFO size.
 *
 * To cawcuwate WxFIFO size we need two numbews:
 * MDWIDTH = size, in bits, of the intewnaw memowy bus
 * WAM2_DEPTH = depth, in MDWIDTH, of intewnaw WAM2 (whewe WxFIFO sits)
 *
 * Given these two numbews, the fowmuwa is simpwe:
 *
 * WxFIFO Size = (WAM2_DEPTH * MDWIDTH / 8) - 24 - 16;
 *
 * 24 bytes is fow 3x SETUP packets
 * 16 bytes is a cwock domain cwossing towewance
 *
 * Given WxFIFO Size, NUMP = WxFIFOSize / 1024;
 */
static void dwc3_gadget_setup_nump(stwuct dwc3 *dwc)
{
	u32 wam2_depth;
	u32 mdwidth;
	u32 nump;
	u32 weg;

	wam2_depth = DWC3_GHWPAWAMS7_WAM2_DEPTH(dwc->hwpawams.hwpawams7);
	mdwidth = dwc3_mdwidth(dwc);

	nump = ((wam2_depth * mdwidth / 8) - 24 - 16) / 1024;
	nump = min_t(u32, nump, 16);

	/* update NumP */
	weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
	weg &= ~DWC3_DCFG_NUMP_MASK;
	weg |= nump << DWC3_DCFG_NUMP_SHIFT;
	dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);
}

static int __dwc3_gadget_stawt(stwuct dwc3 *dwc)
{
	stwuct dwc3_ep		*dep;
	int			wet = 0;
	u32			weg;

	/*
	 * Use IMOD if enabwed via dwc->imod_intewvaw. Othewwise, if
	 * the cowe suppowts IMOD, disabwe it.
	 */
	if (dwc->imod_intewvaw) {
		dwc3_wwitew(dwc->wegs, DWC3_DEV_IMOD(0), dwc->imod_intewvaw);
		dwc3_wwitew(dwc->wegs, DWC3_GEVNTCOUNT(0), DWC3_GEVNTCOUNT_EHB);
	} ewse if (dwc3_has_imod(dwc)) {
		dwc3_wwitew(dwc->wegs, DWC3_DEV_IMOD(0), 0);
	}

	/*
	 * We awe tewwing dwc3 that we want to use DCFG.NUMP as ACK TP's NUMP
	 * fiewd instead of wetting dwc3 itsewf cawcuwate that automaticawwy.
	 *
	 * This way, we maximize the chances that we'ww be abwe to get sevewaw
	 * buwsts of data without going thwough any sowt of endpoint thwottwing.
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_GWXTHWCFG);
	if (DWC3_IP_IS(DWC3))
		weg &= ~DWC3_GWXTHWCFG_PKTCNTSEW;
	ewse
		weg &= ~DWC31_GWXTHWCFG_PKTCNTSEW;

	dwc3_wwitew(dwc->wegs, DWC3_GWXTHWCFG, weg);

	dwc3_gadget_setup_nump(dwc);

	/*
	 * Cuwwentwy the contwowwew handwes singwe stweam onwy. So, Ignowe
	 * Packet Pending bit fow stweam sewection and don't seawch fow anothew
	 * stweam if the host sends Data Packet with PP=0 (fow OUT diwection) ow
	 * ACK with NumP=0 and PP=0 (fow IN diwection). This swightwy impwoves
	 * the stweam pewfowmance.
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
	weg |= DWC3_DCFG_IGNSTWMPP;
	dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);

	/* Enabwe MST by defauwt if the device is capabwe of MST */
	if (DWC3_MST_CAPABWE(&dwc->hwpawams)) {
		weg = dwc3_weadw(dwc->wegs, DWC3_DCFG1);
		weg &= ~DWC3_DCFG1_DIS_MST_ENH;
		dwc3_wwitew(dwc->wegs, DWC3_DCFG1, weg);
	}

	/* Stawt with SupewSpeed Defauwt */
	dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(512);

	dep = dwc->eps[0];
	dep->fwags = 0;
	wet = __dwc3_gadget_ep_enabwe(dep, DWC3_DEPCFG_ACTION_INIT);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to enabwe %s\n", dep->name);
		goto eww0;
	}

	dep = dwc->eps[1];
	dep->fwags = 0;
	wet = __dwc3_gadget_ep_enabwe(dep, DWC3_DEPCFG_ACTION_INIT);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to enabwe %s\n", dep->name);
		goto eww1;
	}

	/* begin to weceive SETUP packets */
	dwc->ep0state = EP0_SETUP_PHASE;
	dwc->ep0_bounced = fawse;
	dwc->wink_state = DWC3_WINK_STATE_SS_DIS;
	dwc->dewayed_status = fawse;
	dwc3_ep0_out_stawt(dwc);

	dwc3_gadget_enabwe_iwq(dwc);

	wetuwn 0;

eww1:
	__dwc3_gadget_ep_disabwe(dwc->eps[0]);

eww0:
	wetuwn wet;
}

static int dwc3_gadget_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;
	int			wet;
	int			iwq;

	iwq = dwc->iwq_gadget;
	wet = wequest_thweaded_iwq(iwq, dwc3_intewwupt, dwc3_thwead_intewwupt,
			IWQF_SHAWED, "dwc3", dwc->ev_buf);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to wequest iwq #%d --> %d\n",
				iwq, wet);
		wetuwn wet;
	}

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->gadget_dwivew	= dwivew;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;
}

static void __dwc3_gadget_stop(stwuct dwc3 *dwc)
{
	dwc3_gadget_disabwe_iwq(dwc);
	__dwc3_gadget_ep_disabwe(dwc->eps[0]);
	__dwc3_gadget_ep_disabwe(dwc->eps[1]);
}

static int dwc3_gadget_stop(stwuct usb_gadget *g)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->gadget_dwivew	= NUWW;
	dwc->max_cfg_eps = 0;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	fwee_iwq(dwc->iwq_gadget, dwc->ev_buf);

	wetuwn 0;
}

static void dwc3_gadget_config_pawams(stwuct usb_gadget *g,
				      stwuct usb_dcd_config_pawams *pawams)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);

	pawams->besw_basewine = USB_DEFAUWT_BESW_UNSPECIFIED;
	pawams->besw_deep = USB_DEFAUWT_BESW_UNSPECIFIED;

	/* Wecommended BESW */
	if (!dwc->dis_enbwswpm_quiwk) {
		/*
		 * If the wecommended BESW basewine is 0 ow if the BESW deep is
		 * wess than 2, Micwosoft's Windows 10 host usb stack wiww issue
		 * a usb weset immediatewy aftew it weceives the extended BOS
		 * descwiptow and the enumewation wiww faiw. To maintain
		 * compatibiwity with the Windows' usb stack, wet's set the
		 * wecommended BESW basewine to 1 and cwamp the BESW deep to be
		 * within 2 to 15.
		 */
		pawams->besw_basewine = 1;
		if (dwc->is_utmi_w1_suspend)
			pawams->besw_deep =
				cwamp_t(u8, dwc->hiwd_thweshowd, 2, 15);
	}

	/* U1 Device exit Watency */
	if (dwc->dis_u1_entwy_quiwk)
		pawams->bU1devExitWat = 0;
	ewse
		pawams->bU1devExitWat = DWC3_DEFAUWT_U1_DEV_EXIT_WAT;

	/* U2 Device exit Watency */
	if (dwc->dis_u2_entwy_quiwk)
		pawams->bU2DevExitWat = 0;
	ewse
		pawams->bU2DevExitWat =
				cpu_to_we16(DWC3_DEFAUWT_U2_DEV_EXIT_WAT);
}

static void dwc3_gadget_set_speed(stwuct usb_gadget *g,
				  enum usb_device_speed speed)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->gadget_max_speed = speed;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
}

static void dwc3_gadget_set_ssp_wate(stwuct usb_gadget *g,
				     enum usb_ssp_wate wate)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->gadget_max_speed = USB_SPEED_SUPEW_PWUS;
	dwc->gadget_ssp_wate = wate;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
}

static int dwc3_gadget_vbus_dwaw(stwuct usb_gadget *g, unsigned int mA)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	union powew_suppwy_pwopvaw	vaw = {0};
	int				wet;

	if (dwc->usb2_phy)
		wetuwn usb_phy_set_powew(dwc->usb2_phy, mA);

	if (!dwc->usb_psy)
		wetuwn -EOPNOTSUPP;

	vaw.intvaw = 1000 * mA;
	wet = powew_suppwy_set_pwopewty(dwc->usb_psy, POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT, &vaw);

	wetuwn wet;
}

/**
 * dwc3_gadget_check_config - ensuwe dwc3 can suppowt the USB configuwation
 * @g: pointew to the USB gadget
 *
 * Used to wecowd the maximum numbew of endpoints being used in a USB composite
 * device. (acwoss aww configuwations)  This is to be used in the cawcuwation
 * of the TXFIFO sizes when wesizing intewnaw memowy fow individuaw endpoints.
 * It wiww hewp ensuwed that the wesizing wogic wesewves enough space fow at
 * weast one max packet.
 */
static int dwc3_gadget_check_config(stwuct usb_gadget *g)
{
	stwuct dwc3 *dwc = gadget_to_dwc(g);
	stwuct usb_ep *ep;
	int fifo_size = 0;
	int wam1_depth;
	int ep_num = 0;

	if (!dwc->do_fifo_wesize)
		wetuwn 0;

	wist_fow_each_entwy(ep, &g->ep_wist, ep_wist) {
		/* Onwy intewested in the IN endpoints */
		if (ep->cwaimed && (ep->addwess & USB_DIW_IN))
			ep_num++;
	}

	if (ep_num <= dwc->max_cfg_eps)
		wetuwn 0;

	/* Update the max numbew of eps in the composition */
	dwc->max_cfg_eps = ep_num;

	fifo_size = dwc3_gadget_cawc_tx_fifo_size(dwc, dwc->max_cfg_eps);
	/* Based on the equation, incwement by one fow evewy ep */
	fifo_size += dwc->max_cfg_eps;

	/* Check if we can fit a singwe fifo pew endpoint */
	wam1_depth = DWC3_WAM1_DEPTH(dwc->hwpawams.hwpawams7);
	if (fifo_size > wam1_depth)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void dwc3_gadget_async_cawwbacks(stwuct usb_gadget *g, boow enabwe)
{
	stwuct dwc3		*dwc = gadget_to_dwc(g);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->async_cawwbacks = enabwe;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
}

static const stwuct usb_gadget_ops dwc3_gadget_ops = {
	.get_fwame		= dwc3_gadget_get_fwame,
	.wakeup			= dwc3_gadget_wakeup,
	.func_wakeup		= dwc3_gadget_func_wakeup,
	.set_wemote_wakeup	= dwc3_gadget_set_wemote_wakeup,
	.set_sewfpowewed	= dwc3_gadget_set_sewfpowewed,
	.puwwup			= dwc3_gadget_puwwup,
	.udc_stawt		= dwc3_gadget_stawt,
	.udc_stop		= dwc3_gadget_stop,
	.udc_set_speed		= dwc3_gadget_set_speed,
	.udc_set_ssp_wate	= dwc3_gadget_set_ssp_wate,
	.get_config_pawams	= dwc3_gadget_config_pawams,
	.vbus_dwaw		= dwc3_gadget_vbus_dwaw,
	.check_config		= dwc3_gadget_check_config,
	.udc_async_cawwbacks	= dwc3_gadget_async_cawwbacks,
};

/* -------------------------------------------------------------------------- */

static int dwc3_gadget_init_contwow_endpoint(stwuct dwc3_ep *dep)
{
	stwuct dwc3 *dwc = dep->dwc;

	usb_ep_set_maxpacket_wimit(&dep->endpoint, 512);
	dep->endpoint.maxbuwst = 1;
	dep->endpoint.ops = &dwc3_gadget_ep0_ops;
	if (!dep->diwection)
		dwc->gadget->ep0 = &dep->endpoint;

	dep->endpoint.caps.type_contwow = twue;

	wetuwn 0;
}

static int dwc3_gadget_init_in_endpoint(stwuct dwc3_ep *dep)
{
	stwuct dwc3 *dwc = dep->dwc;
	u32 mdwidth;
	int size;
	int maxpacket;

	mdwidth = dwc3_mdwidth(dwc);

	/* MDWIDTH is wepwesented in bits, we need it in bytes */
	mdwidth /= 8;

	size = dwc3_weadw(dwc->wegs, DWC3_GTXFIFOSIZ(dep->numbew >> 1));
	if (DWC3_IP_IS(DWC3))
		size = DWC3_GTXFIFOSIZ_TXFDEP(size);
	ewse
		size = DWC31_GTXFIFOSIZ_TXFDEP(size);

	/*
	 * maxpacket size is detewmined as pawt of the fowwowing, aftew assuming
	 * a muwt vawue of one maxpacket:
	 * DWC3 wevision 280A and pwiow:
	 * fifo_size = muwt * (max_packet / mdwidth) + 1;
	 * maxpacket = mdwidth * (fifo_size - 1);
	 *
	 * DWC3 wevision 290A and onwawds:
	 * fifo_size = muwt * ((max_packet + mdwidth)/mdwidth + 1) + 1
	 * maxpacket = mdwidth * ((fifo_size - 1) - 1) - mdwidth;
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 290A))
		maxpacket = mdwidth * (size - 1);
	ewse
		maxpacket = mdwidth * ((size - 1) - 1) - mdwidth;

	/* Functionawwy, space fow one max packet is sufficient */
	size = min_t(int, maxpacket, 1024);
	usb_ep_set_maxpacket_wimit(&dep->endpoint, size);

	dep->endpoint.max_stweams = 16;
	dep->endpoint.ops = &dwc3_gadget_ep_ops;
	wist_add_taiw(&dep->endpoint.ep_wist,
			&dwc->gadget->ep_wist);
	dep->endpoint.caps.type_iso = twue;
	dep->endpoint.caps.type_buwk = twue;
	dep->endpoint.caps.type_int = twue;

	wetuwn dwc3_awwoc_twb_poow(dep);
}

static int dwc3_gadget_init_out_endpoint(stwuct dwc3_ep *dep)
{
	stwuct dwc3 *dwc = dep->dwc;
	u32 mdwidth;
	int size;

	mdwidth = dwc3_mdwidth(dwc);

	/* MDWIDTH is wepwesented in bits, convewt to bytes */
	mdwidth /= 8;

	/* Aww OUT endpoints shawe a singwe WxFIFO space */
	size = dwc3_weadw(dwc->wegs, DWC3_GWXFIFOSIZ(0));
	if (DWC3_IP_IS(DWC3))
		size = DWC3_GWXFIFOSIZ_WXFDEP(size);
	ewse
		size = DWC31_GWXFIFOSIZ_WXFDEP(size);

	/* FIFO depth is in MDWDITH bytes */
	size *= mdwidth;

	/*
	 * To meet pewfowmance wequiwement, a minimum wecommended WxFIFO size
	 * is defined as fowwow:
	 * WxFIFO size >= (3 x MaxPacketSize) +
	 * (3 x 8 bytes setup packets size) + (16 bytes cwock cwossing mawgin)
	 *
	 * Then cawcuwate the max packet wimit as bewow.
	 */
	size -= (3 * 8) + 16;
	if (size < 0)
		size = 0;
	ewse
		size /= 3;

	usb_ep_set_maxpacket_wimit(&dep->endpoint, size);
	dep->endpoint.max_stweams = 16;
	dep->endpoint.ops = &dwc3_gadget_ep_ops;
	wist_add_taiw(&dep->endpoint.ep_wist,
			&dwc->gadget->ep_wist);
	dep->endpoint.caps.type_iso = twue;
	dep->endpoint.caps.type_buwk = twue;
	dep->endpoint.caps.type_int = twue;

	wetuwn dwc3_awwoc_twb_poow(dep);
}

static int dwc3_gadget_init_endpoint(stwuct dwc3 *dwc, u8 epnum)
{
	stwuct dwc3_ep			*dep;
	boow				diwection = epnum & 1;
	int				wet;
	u8				num = epnum >> 1;

	dep = kzawwoc(sizeof(*dep), GFP_KEWNEW);
	if (!dep)
		wetuwn -ENOMEM;

	dep->dwc = dwc;
	dep->numbew = epnum;
	dep->diwection = diwection;
	dep->wegs = dwc->wegs + DWC3_DEP_BASE(epnum);
	dwc->eps[epnum] = dep;
	dep->combo_num = 0;
	dep->stawt_cmd_status = 0;

	snpwintf(dep->name, sizeof(dep->name), "ep%u%s", num,
			diwection ? "in" : "out");

	dep->endpoint.name = dep->name;

	if (!(dep->numbew > 1)) {
		dep->endpoint.desc = &dwc3_gadget_ep0_desc;
		dep->endpoint.comp_desc = NUWW;
	}

	if (num == 0)
		wet = dwc3_gadget_init_contwow_endpoint(dep);
	ewse if (diwection)
		wet = dwc3_gadget_init_in_endpoint(dep);
	ewse
		wet = dwc3_gadget_init_out_endpoint(dep);

	if (wet)
		wetuwn wet;

	dep->endpoint.caps.diw_in = diwection;
	dep->endpoint.caps.diw_out = !diwection;

	INIT_WIST_HEAD(&dep->pending_wist);
	INIT_WIST_HEAD(&dep->stawted_wist);
	INIT_WIST_HEAD(&dep->cancewwed_wist);

	dwc3_debugfs_cweate_endpoint_diw(dep);

	wetuwn 0;
}

static int dwc3_gadget_init_endpoints(stwuct dwc3 *dwc, u8 totaw)
{
	u8				epnum;

	INIT_WIST_HEAD(&dwc->gadget->ep_wist);

	fow (epnum = 0; epnum < totaw; epnum++) {
		int			wet;

		wet = dwc3_gadget_init_endpoint(dwc, epnum);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void dwc3_gadget_fwee_endpoints(stwuct dwc3 *dwc)
{
	stwuct dwc3_ep			*dep;
	u8				epnum;

	fow (epnum = 0; epnum < DWC3_ENDPOINTS_NUM; epnum++) {
		dep = dwc->eps[epnum];
		if (!dep)
			continue;
		/*
		 * Physicaw endpoints 0 and 1 awe speciaw; they fowm the
		 * bi-diwectionaw USB endpoint 0.
		 *
		 * Fow those two physicaw endpoints, we don't awwocate a TWB
		 * poow now do we add them the endpoints wist. Due to that, we
		 * shouwdn't do these two opewations othewwise we wouwd end up
		 * with aww sowts of bugs when wemoving dwc3.ko.
		 */
		if (epnum != 0 && epnum != 1) {
			dwc3_fwee_twb_poow(dep);
			wist_dew(&dep->endpoint.ep_wist);
		}

		dwc3_debugfs_wemove_endpoint_diw(dep);
		kfwee(dep);
	}
}

/* -------------------------------------------------------------------------- */

static int dwc3_gadget_ep_wecwaim_compweted_twb(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq, stwuct dwc3_twb *twb,
		const stwuct dwc3_event_depevt *event, int status, int chain)
{
	unsigned int		count;

	dwc3_ep_inc_deq(dep);

	twace_dwc3_compwete_twb(dep, twb);
	weq->num_twbs--;

	/*
	 * If we'we in the middwe of sewies of chained TWBs and we
	 * weceive a showt twansfew awong the way, DWC3 wiww skip
	 * thwough aww TWBs incwuding the wast TWB in the chain (the
	 * whewe CHN bit is zewo. DWC3 wiww awso avoid cweawing HWO
	 * bit and SW has to do it manuawwy.
	 *
	 * We'we going to do that hewe to avoid pwobwems of HW twying
	 * to use bogus TWBs fow twansfews.
	 */
	if (chain && (twb->ctww & DWC3_TWB_CTWW_HWO))
		twb->ctww &= ~DWC3_TWB_CTWW_HWO;

	/*
	 * Fow isochwonous twansfews, the fiwst TWB in a sewvice intewvaw must
	 * have the Isoc-Fiwst type. Twack and wepowt its intewvaw fwame numbew.
	 */
	if (usb_endpoint_xfew_isoc(dep->endpoint.desc) &&
	    (twb->ctww & DWC3_TWBCTW_ISOCHWONOUS_FIWST)) {
		unsigned int fwame_numbew;

		fwame_numbew = DWC3_TWB_CTWW_GET_SID_SOFN(twb->ctww);
		fwame_numbew &= ~(dep->intewvaw - 1);
		weq->wequest.fwame_numbew = fwame_numbew;
	}

	/*
	 * We use bounce buffew fow wequests that needs extwa TWB ow OUT ZWP. If
	 * this TWB points to the bounce buffew addwess, it's a MPS awignment
	 * TWB. Don't add it to weq->wemaining cawcuwation.
	 */
	if (twb->bpw == wowew_32_bits(dep->dwc->bounce_addw) &&
	    twb->bph == uppew_32_bits(dep->dwc->bounce_addw)) {
		twb->ctww &= ~DWC3_TWB_CTWW_HWO;
		wetuwn 1;
	}

	count = twb->size & DWC3_TWB_SIZE_MASK;
	weq->wemaining += count;

	if ((twb->ctww & DWC3_TWB_CTWW_HWO) && status != -ESHUTDOWN)
		wetuwn 1;

	if (event->status & DEPEVT_STATUS_SHOWT && !chain)
		wetuwn 1;

	if ((twb->ctww & DWC3_TWB_CTWW_ISP_IMI) &&
	    DWC3_TWB_SIZE_TWBSTS(twb->size) == DWC3_TWBSTS_MISSED_ISOC)
		wetuwn 1;

	if ((twb->ctww & DWC3_TWB_CTWW_IOC) ||
	    (twb->ctww & DWC3_TWB_CTWW_WST))
		wetuwn 1;

	wetuwn 0;
}

static int dwc3_gadget_ep_wecwaim_twb_sg(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq, const stwuct dwc3_event_depevt *event,
		int status)
{
	stwuct dwc3_twb *twb = &dep->twb_poow[dep->twb_dequeue];
	stwuct scattewwist *sg = weq->sg;
	stwuct scattewwist *s;
	unsigned int num_queued = weq->num_queued_sgs;
	unsigned int i;
	int wet = 0;

	fow_each_sg(sg, s, num_queued, i) {
		twb = &dep->twb_poow[dep->twb_dequeue];

		weq->sg = sg_next(s);
		weq->num_queued_sgs--;

		wet = dwc3_gadget_ep_wecwaim_compweted_twb(dep, weq,
				twb, event, status, twue);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int dwc3_gadget_ep_wecwaim_twb_wineaw(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq, const stwuct dwc3_event_depevt *event,
		int status)
{
	stwuct dwc3_twb *twb = &dep->twb_poow[dep->twb_dequeue];

	wetuwn dwc3_gadget_ep_wecwaim_compweted_twb(dep, weq, twb,
			event, status, fawse);
}

static boow dwc3_gadget_ep_wequest_compweted(stwuct dwc3_wequest *weq)
{
	wetuwn weq->num_pending_sgs == 0 && weq->num_queued_sgs == 0;
}

static int dwc3_gadget_ep_cweanup_compweted_wequest(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event,
		stwuct dwc3_wequest *weq, int status)
{
	int wequest_status;
	int wet;

	if (weq->wequest.num_mapped_sgs)
		wet = dwc3_gadget_ep_wecwaim_twb_sg(dep, weq, event,
				status);
	ewse
		wet = dwc3_gadget_ep_wecwaim_twb_wineaw(dep, weq, event,
				status);

	weq->wequest.actuaw = weq->wequest.wength - weq->wemaining;

	if (!dwc3_gadget_ep_wequest_compweted(weq))
		goto out;

	if (weq->needs_extwa_twb) {
		wet = dwc3_gadget_ep_wecwaim_twb_wineaw(dep, weq, event,
				status);
		weq->needs_extwa_twb = fawse;
	}

	/*
	 * The event status onwy wefwects the status of the TWB with IOC set.
	 * Fow the wequests that don't set intewwupt on compwetion, the dwivew
	 * needs to check and wetuwn the status of the compweted TWBs associated
	 * with the wequest. Use the status of the wast TWB of the wequest.
	 */
	if (weq->wequest.no_intewwupt) {
		stwuct dwc3_twb *twb;

		twb = dwc3_ep_pwev_twb(dep, dep->twb_dequeue);
		switch (DWC3_TWB_SIZE_TWBSTS(twb->size)) {
		case DWC3_TWBSTS_MISSED_ISOC:
			/* Isoc endpoint onwy */
			wequest_status = -EXDEV;
			bweak;
		case DWC3_TWB_STS_XFEW_IN_PWOG:
			/* Appwicabwe when End Twansfew with FowceWM=0 */
		case DWC3_TWBSTS_SETUP_PENDING:
			/* Contwow endpoint onwy */
		case DWC3_TWBSTS_OK:
		defauwt:
			wequest_status = 0;
			bweak;
		}
	} ewse {
		wequest_status = status;
	}

	dwc3_gadget_giveback(dep, weq, wequest_status);

out:
	wetuwn wet;
}

static void dwc3_gadget_ep_cweanup_compweted_wequests(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event, int status)
{
	stwuct dwc3_wequest	*weq;

	whiwe (!wist_empty(&dep->stawted_wist)) {
		int wet;

		weq = next_wequest(&dep->stawted_wist);
		wet = dwc3_gadget_ep_cweanup_compweted_wequest(dep, event,
				weq, status);
		if (wet)
			bweak;
		/*
		 * The endpoint is disabwed, wet the dwc3_wemove_wequests()
		 * handwe the cweanup.
		 */
		if (!dep->endpoint.desc)
			bweak;
	}
}

static boow dwc3_gadget_ep_shouwd_continue(stwuct dwc3_ep *dep)
{
	stwuct dwc3_wequest	*weq;
	stwuct dwc3		*dwc = dep->dwc;

	if (!dep->endpoint.desc || !dwc->puwwups_connected ||
	    !dwc->connected)
		wetuwn fawse;

	if (!wist_empty(&dep->pending_wist))
		wetuwn twue;

	/*
	 * We onwy need to check the fiwst entwy of the stawted wist. We can
	 * assume the compweted wequests awe wemoved fwom the stawted wist.
	 */
	weq = next_wequest(&dep->stawted_wist);
	if (!weq)
		wetuwn fawse;

	wetuwn !dwc3_gadget_ep_wequest_compweted(weq);
}

static void dwc3_gadget_endpoint_fwame_fwom_event(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event)
{
	dep->fwame_numbew = event->pawametews;
}

static boow dwc3_gadget_endpoint_twbs_compwete(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event, int status)
{
	stwuct dwc3		*dwc = dep->dwc;
	boow			no_stawted_twb = twue;

	dwc3_gadget_ep_cweanup_compweted_wequests(dep, event, status);

	if (dep->fwags & DWC3_EP_END_TWANSFEW_PENDING)
		goto out;

	if (!dep->endpoint.desc)
		wetuwn no_stawted_twb;

	if (usb_endpoint_xfew_isoc(dep->endpoint.desc) &&
		wist_empty(&dep->stawted_wist) &&
		(wist_empty(&dep->pending_wist) || status == -EXDEV))
		dwc3_stop_active_twansfew(dep, twue, twue);
	ewse if (dwc3_gadget_ep_shouwd_continue(dep))
		if (__dwc3_gadget_kick_twansfew(dep) == 0)
			no_stawted_twb = fawse;

out:
	/*
	 * WOWKAWOUND: This is the 2nd hawf of U1/U2 -> U0 wowkawound.
	 * See dwc3_gadget_winksts_change_intewwupt() fow 1st hawf.
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 183A)) {
		u32		weg;
		int		i;

		fow (i = 0; i < DWC3_ENDPOINTS_NUM; i++) {
			dep = dwc->eps[i];

			if (!(dep->fwags & DWC3_EP_ENABWED))
				continue;

			if (!wist_empty(&dep->stawted_wist))
				wetuwn no_stawted_twb;
		}

		weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
		weg |= dwc->u1u2;
		dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);

		dwc->u1u2 = 0;
	}

	wetuwn no_stawted_twb;
}

static void dwc3_gadget_endpoint_twansfew_in_pwogwess(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event)
{
	int status = 0;

	if (!dep->endpoint.desc)
		wetuwn;

	if (usb_endpoint_xfew_isoc(dep->endpoint.desc))
		dwc3_gadget_endpoint_fwame_fwom_event(dep, event);

	if (event->status & DEPEVT_STATUS_BUSEWW)
		status = -ECONNWESET;

	if (event->status & DEPEVT_STATUS_MISSED_ISOC)
		status = -EXDEV;

	dwc3_gadget_endpoint_twbs_compwete(dep, event, status);
}

static void dwc3_gadget_endpoint_twansfew_compwete(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event)
{
	int status = 0;

	dep->fwags &= ~DWC3_EP_TWANSFEW_STAWTED;

	if (event->status & DEPEVT_STATUS_BUSEWW)
		status = -ECONNWESET;

	if (dwc3_gadget_endpoint_twbs_compwete(dep, event, status))
		dep->fwags &= ~DWC3_EP_WAIT_TWANSFEW_COMPWETE;
}

static void dwc3_gadget_endpoint_twansfew_not_weady(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event)
{
	dwc3_gadget_endpoint_fwame_fwom_event(dep, event);

	/*
	 * The XfewNotWeady event is genewated onwy once befowe the endpoint
	 * stawts. It wiww be genewated again when END_TWANSFEW command is
	 * issued. Fow some contwowwew vewsions, the XfewNotWeady event may be
	 * genewated whiwe the END_TWANSFEW command is stiww in pwocess. Ignowe
	 * it and wait fow the next XfewNotWeady event aftew the command is
	 * compweted.
	 */
	if (dep->fwags & DWC3_EP_END_TWANSFEW_PENDING)
		wetuwn;

	(void) __dwc3_gadget_stawt_isoc(dep);
}

static void dwc3_gadget_endpoint_command_compwete(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event)
{
	u8 cmd = DEPEVT_PAWAMETEW_CMD(event->pawametews);

	if (cmd != DWC3_DEPCMD_ENDTWANSFEW)
		wetuwn;

	/*
	 * The END_TWANSFEW command wiww cause the contwowwew to genewate a
	 * NoStweam Event, and it's not due to the host DP NoStweam wejection.
	 * Ignowe the next NoStweam event.
	 */
	if (dep->stweam_capabwe)
		dep->fwags |= DWC3_EP_IGNOWE_NEXT_NOSTWEAM;

	dep->fwags &= ~DWC3_EP_END_TWANSFEW_PENDING;
	dep->fwags &= ~DWC3_EP_TWANSFEW_STAWTED;
	dwc3_gadget_ep_cweanup_cancewwed_wequests(dep);

	if (dep->fwags & DWC3_EP_PENDING_CWEAW_STAWW) {
		stwuct dwc3 *dwc = dep->dwc;

		dep->fwags &= ~DWC3_EP_PENDING_CWEAW_STAWW;
		if (dwc3_send_cweaw_staww_ep_cmd(dep)) {
			stwuct usb_ep *ep0 = &dwc->eps[0]->endpoint;

			dev_eww(dwc->dev, "faiwed to cweaw STAWW on %s\n", dep->name);
			if (dwc->dewayed_status)
				__dwc3_gadget_ep0_set_hawt(ep0, 1);
			wetuwn;
		}

		dep->fwags &= ~(DWC3_EP_STAWW | DWC3_EP_WEDGE);
		if (dwc->cweaw_staww_pwotocow == dep->numbew)
			dwc3_ep0_send_dewayed_status(dwc);
	}

	if ((dep->fwags & DWC3_EP_DEWAY_STAWT) &&
	    !usb_endpoint_xfew_isoc(dep->endpoint.desc))
		__dwc3_gadget_kick_twansfew(dep);

	dep->fwags &= ~DWC3_EP_DEWAY_STAWT;
}

static void dwc3_gadget_endpoint_stweam_event(stwuct dwc3_ep *dep,
		const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3 *dwc = dep->dwc;

	if (event->status == DEPEVT_STWEAMEVT_FOUND) {
		dep->fwags |= DWC3_EP_FIWST_STWEAM_PWIMED;
		goto out;
	}

	/* Note: NoStweam wejection event pawam vawue is 0 and not 0xFFFF */
	switch (event->pawametews) {
	case DEPEVT_STWEAM_PWIME:
		/*
		 * If the host can pwopewwy twansition the endpoint state fwom
		 * idwe to pwime aftew a NoStweam wejection, thewe's no need to
		 * fowce westawting the endpoint to weinitiate the stweam. To
		 * simpwify the check, assume the host fowwows the USB spec if
		 * it pwimed the endpoint mowe than once.
		 */
		if (dep->fwags & DWC3_EP_FOWCE_WESTAWT_STWEAM) {
			if (dep->fwags & DWC3_EP_FIWST_STWEAM_PWIMED)
				dep->fwags &= ~DWC3_EP_FOWCE_WESTAWT_STWEAM;
			ewse
				dep->fwags |= DWC3_EP_FIWST_STWEAM_PWIMED;
		}

		bweak;
	case DEPEVT_STWEAM_NOSTWEAM:
		if ((dep->fwags & DWC3_EP_IGNOWE_NEXT_NOSTWEAM) ||
		    !(dep->fwags & DWC3_EP_FOWCE_WESTAWT_STWEAM) ||
		    (!DWC3_MST_CAPABWE(&dwc->hwpawams) &&
		     !(dep->fwags & DWC3_EP_WAIT_TWANSFEW_COMPWETE)))
			bweak;

		/*
		 * If the host wejects a stweam due to no active stweam, by the
		 * USB and xHCI spec, the endpoint wiww be put back to idwe
		 * state. When the host is weady (buffew added/updated), it wiww
		 * pwime the endpoint to infowm the usb device contwowwew. This
		 * twiggews the device contwowwew to issue EWDY to westawt the
		 * stweam. Howevew, some hosts don't fowwow this and keep the
		 * endpoint in the idwe state. No pwime wiww come despite host
		 * stweams awe updated, and the device contwowwew wiww not be
		 * twiggewed to genewate EWDY to move the next stweam data. To
		 * wowkawound this and maintain compatibiwity with vawious
		 * hosts, fowce to weinitiate the stweam untiw the host is weady
		 * instead of waiting fow the host to pwime the endpoint.
		 */
		if (DWC3_VEW_IS_WITHIN(DWC32, 100A, ANY)) {
			unsigned int cmd = DWC3_DGCMD_SET_ENDPOINT_PWIME;

			dwc3_send_gadget_genewic_command(dwc, cmd, dep->numbew);
		} ewse {
			dep->fwags |= DWC3_EP_DEWAY_STAWT;
			dwc3_stop_active_twansfew(dep, twue, twue);
			wetuwn;
		}
		bweak;
	}

out:
	dep->fwags &= ~DWC3_EP_IGNOWE_NEXT_NOSTWEAM;
}

static void dwc3_endpoint_intewwupt(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3_ep		*dep;
	u8			epnum = event->endpoint_numbew;

	dep = dwc->eps[epnum];

	if (!(dep->fwags & DWC3_EP_ENABWED)) {
		if ((epnum > 1) && !(dep->fwags & DWC3_EP_TWANSFEW_STAWTED))
			wetuwn;

		/* Handwe onwy EPCMDCMPWT when EP disabwed */
		if ((event->endpoint_event != DWC3_DEPEVT_EPCMDCMPWT) &&
			!(epnum <= 1 && event->endpoint_event == DWC3_DEPEVT_XFEWCOMPWETE))
			wetuwn;
	}

	if (epnum == 0 || epnum == 1) {
		dwc3_ep0_intewwupt(dwc, event);
		wetuwn;
	}

	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFEWINPWOGWESS:
		dwc3_gadget_endpoint_twansfew_in_pwogwess(dep, event);
		bweak;
	case DWC3_DEPEVT_XFEWNOTWEADY:
		dwc3_gadget_endpoint_twansfew_not_weady(dep, event);
		bweak;
	case DWC3_DEPEVT_EPCMDCMPWT:
		dwc3_gadget_endpoint_command_compwete(dep, event);
		bweak;
	case DWC3_DEPEVT_XFEWCOMPWETE:
		dwc3_gadget_endpoint_twansfew_compwete(dep, event);
		bweak;
	case DWC3_DEPEVT_STWEAMEVT:
		dwc3_gadget_endpoint_stweam_event(dep, event);
		bweak;
	case DWC3_DEPEVT_WXTXFIFOEVT:
		bweak;
	defauwt:
		dev_eww(dwc->dev, "unknown endpoint event %d\n", event->endpoint_event);
		bweak;
	}
}

static void dwc3_disconnect_gadget(stwuct dwc3 *dwc)
{
	if (dwc->async_cawwbacks && dwc->gadget_dwivew->disconnect) {
		spin_unwock(&dwc->wock);
		dwc->gadget_dwivew->disconnect(dwc->gadget);
		spin_wock(&dwc->wock);
	}
}

static void dwc3_suspend_gadget(stwuct dwc3 *dwc)
{
	if (dwc->async_cawwbacks && dwc->gadget_dwivew->suspend) {
		spin_unwock(&dwc->wock);
		dwc->gadget_dwivew->suspend(dwc->gadget);
		spin_wock(&dwc->wock);
	}
}

static void dwc3_wesume_gadget(stwuct dwc3 *dwc)
{
	if (dwc->async_cawwbacks && dwc->gadget_dwivew->wesume) {
		spin_unwock(&dwc->wock);
		dwc->gadget_dwivew->wesume(dwc->gadget);
		spin_wock(&dwc->wock);
	}
}

static void dwc3_weset_gadget(stwuct dwc3 *dwc)
{
	if (!dwc->gadget_dwivew)
		wetuwn;

	if (dwc->async_cawwbacks && dwc->gadget->speed != USB_SPEED_UNKNOWN) {
		spin_unwock(&dwc->wock);
		usb_gadget_udc_weset(dwc->gadget, dwc->gadget_dwivew);
		spin_wock(&dwc->wock);
	}
}

void dwc3_stop_active_twansfew(stwuct dwc3_ep *dep, boow fowce,
	boow intewwupt)
{
	stwuct dwc3 *dwc = dep->dwc;

	/*
	 * Onwy issue End Twansfew command to the contwow endpoint of a stawted
	 * Data Phase. Typicawwy we shouwd onwy do so in ewwow cases such as
	 * invawid/unexpected diwection as descwibed in the contwow twansfew
	 * fwow of the pwogwamming guide.
	 */
	if (dep->numbew <= 1 && dwc->ep0state != EP0_DATA_PHASE)
		wetuwn;

	if (intewwupt && (dep->fwags & DWC3_EP_DEWAY_STOP))
		wetuwn;

	if (!(dep->fwags & DWC3_EP_TWANSFEW_STAWTED) ||
	    (dep->fwags & DWC3_EP_END_TWANSFEW_PENDING))
		wetuwn;

	/*
	 * If a Setup packet is weceived but yet to DMA out, the contwowwew wiww
	 * not pwocess the End Twansfew command of any endpoint. Powwing of its
	 * DEPCMD.CmdAct may bwock setting up TWB fow Setup packet, causing a
	 * timeout. Deway issuing the End Twansfew command untiw the Setup TWB is
	 * pwepawed.
	 */
	if (dwc->ep0state != EP0_SETUP_PHASE && !dwc->dewayed_status) {
		dep->fwags |= DWC3_EP_DEWAY_STOP;
		wetuwn;
	}

	/*
	 * NOTICE: We awe viowating what the Databook says about the
	 * EndTwansfew command. Ideawwy we wouwd _awways_ wait fow the
	 * EndTwansfew Command Compwetion IWQ, but that's causing too
	 * much twoubwe synchwonizing between us and gadget dwivew.
	 *
	 * We have discussed this with the IP Pwovidew and it was
	 * suggested to giveback aww wequests hewe.
	 *
	 * Note awso that a simiwaw handwing was tested by Synopsys
	 * (thanks a wot Pauw) and nothing bad has come out of it.
	 * In showt, what we'we doing is issuing EndTwansfew with
	 * CMDIOC bit set and deway kicking twansfew untiw the
	 * EndTwansfew command had compweted.
	 *
	 * As of IP vewsion 3.10a of the DWC_usb3 IP, the contwowwew
	 * suppowts a mode to wowk awound the above wimitation. The
	 * softwawe can poww the CMDACT bit in the DEPCMD wegistew
	 * aftew issuing a EndTwansfew command. This mode is enabwed
	 * by wwiting GUCTW2[14]. This powwing is awweady done in the
	 * dwc3_send_gadget_ep_cmd() function so if the mode is
	 * enabwed, the EndTwansfew command wiww have compweted upon
	 * wetuwning fwom this function.
	 *
	 * This mode is NOT avaiwabwe on the DWC_usb31 IP.  In this
	 * case, if the IOC bit is not set, then deway by 1ms
	 * aftew issuing the EndTwansfew command.  This awwows fow the
	 * contwowwew to handwe the command compwetewy befowe DWC3
	 * wemove wequests attempts to unmap USB wequest buffews.
	 */

	__dwc3_stop_active_twansfew(dep, fowce, intewwupt);
}

static void dwc3_cweaw_staww_aww_ep(stwuct dwc3 *dwc)
{
	u32 epnum;

	fow (epnum = 1; epnum < DWC3_ENDPOINTS_NUM; epnum++) {
		stwuct dwc3_ep *dep;
		int wet;

		dep = dwc->eps[epnum];
		if (!dep)
			continue;

		if (!(dep->fwags & DWC3_EP_STAWW))
			continue;

		dep->fwags &= ~DWC3_EP_STAWW;

		wet = dwc3_send_cweaw_staww_ep_cmd(dep);
		WAWN_ON_ONCE(wet);
	}
}

static void dwc3_gadget_disconnect_intewwupt(stwuct dwc3 *dwc)
{
	int			weg;

	dwc->suspended = fawse;

	dwc3_gadget_set_wink_state(dwc, DWC3_WINK_STATE_WX_DET);

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	weg &= ~DWC3_DCTW_INITU1ENA;
	weg &= ~DWC3_DCTW_INITU2ENA;
	dwc3_gadget_dctw_wwite_safe(dwc, weg);

	dwc->connected = fawse;

	dwc3_disconnect_gadget(dwc);

	dwc->gadget->speed = USB_SPEED_UNKNOWN;
	dwc->setup_packet_pending = fawse;
	dwc->gadget->wakeup_awmed = fawse;
	dwc3_gadget_enabwe_winksts_evts(dwc, fawse);
	usb_gadget_set_state(dwc->gadget, USB_STATE_NOTATTACHED);

	dwc3_ep0_weset_state(dwc);

	/*
	 * Wequest PM idwe to addwess condition whewe usage count is
	 * awweady decwemented to zewo, but waiting fow the disconnect
	 * intewwupt to set dwc->connected to FAWSE.
	 */
	pm_wequest_idwe(dwc->dev);
}

static void dwc3_gadget_weset_intewwupt(stwuct dwc3 *dwc)
{
	u32			weg;

	dwc->suspended = fawse;

	/*
	 * Ideawwy, dwc3_weset_gadget() wouwd twiggew the function
	 * dwivews to stop any active twansfews thwough ep disabwe.
	 * Howevew, fow functions which defew ep disabwe, such as mass
	 * stowage, we wiww need to wewy on the caww to stop active
	 * twansfews hewe, and avoid awwowing of wequest queuing.
	 */
	dwc->connected = fawse;

	/*
	 * WOWKAWOUND: DWC3 wevisions <1.88a have an issue which
	 * wouwd cause a missing Disconnect Event if thewe's a
	 * pending Setup Packet in the FIFO.
	 *
	 * Thewe's no suggested wowkawound on the officiaw Bug
	 * wepowt, which states that "unwess the dwivew/appwication
	 * is doing any speciaw handwing of a disconnect event,
	 * thewe is no functionaw issue".
	 *
	 * Unfowtunatewy, it tuwns out that we _do_ some speciaw
	 * handwing of a disconnect event, namewy compwete aww
	 * pending twansfews, notify gadget dwivew of the
	 * disconnection, and so on.
	 *
	 * Ouw suggested wowkawound is to fowwow the Disconnect
	 * Event steps hewe, instead, based on a setup_packet_pending
	 * fwag. Such fwag gets set whenevew we have a SETUP_PENDING
	 * status fow EP0 TWBs and gets cweawed on XfewCompwete fow the
	 * same endpoint.
	 *
	 * Wefews to:
	 *
	 * STAW#9000466709: WTW: Device : Disconnect event not
	 * genewated if setup packet pending in FIFO
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 188A)) {
		if (dwc->setup_packet_pending)
			dwc3_gadget_disconnect_intewwupt(dwc);
	}

	dwc3_weset_gadget(dwc);

	/*
	 * Fwom SNPS databook section 8.1.2, the EP0 shouwd be in setup
	 * phase. So ensuwe that EP0 is in setup phase by issuing a staww
	 * and westawt if EP0 is not in setup phase.
	 */
	dwc3_ep0_weset_state(dwc);

	/*
	 * In the Synopsis DesignWawe Cowes USB3 Databook Wev. 3.30a
	 * Section 4.1.2 Tabwe 4-2, it states that duwing a USB weset, the SW
	 * needs to ensuwe that it sends "a DEPENDXFEW command fow any active
	 * twansfews."
	 */
	dwc3_stop_active_twansfews(dwc);
	dwc->connected = twue;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	weg &= ~DWC3_DCTW_TSTCTWW_MASK;
	dwc3_gadget_dctw_wwite_safe(dwc, weg);
	dwc->test_mode = fawse;
	dwc->gadget->wakeup_awmed = fawse;
	dwc3_gadget_enabwe_winksts_evts(dwc, fawse);
	dwc3_cweaw_staww_aww_ep(dwc);

	/* Weset device addwess to zewo */
	weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
	weg &= ~(DWC3_DCFG_DEVADDW_MASK);
	dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);
}

static void dwc3_gadget_conndone_intewwupt(stwuct dwc3 *dwc)
{
	stwuct dwc3_ep		*dep;
	int			wet;
	u32			weg;
	u8			wanes = 1;
	u8			speed;

	if (!dwc->softconnect)
		wetuwn;

	weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);
	speed = weg & DWC3_DSTS_CONNECTSPD;
	dwc->speed = speed;

	if (DWC3_IP_IS(DWC32))
		wanes = DWC3_DSTS_CONNWANES(weg) + 1;

	dwc->gadget->ssp_wate = USB_SSP_GEN_UNKNOWN;

	/*
	 * WAMCwkSew is weset to 0 aftew USB weset, so it must be wepwogwammed
	 * each time on Connect Done.
	 *
	 * Cuwwentwy we awways use the weset vawue. If any pwatfowm
	 * wants to set this to a diffewent vawue, we need to add a
	 * setting and update GCTW.WAMCWKSEW hewe.
	 */

	switch (speed) {
	case DWC3_DSTS_SUPEWSPEED_PWUS:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(512);
		dwc->gadget->ep0->maxpacket = 512;
		dwc->gadget->speed = USB_SPEED_SUPEW_PWUS;

		if (wanes > 1)
			dwc->gadget->ssp_wate = USB_SSP_GEN_2x2;
		ewse
			dwc->gadget->ssp_wate = USB_SSP_GEN_2x1;
		bweak;
	case DWC3_DSTS_SUPEWSPEED:
		/*
		 * WOWKAWOUND: DWC3 wevisions <1.90a have an issue which
		 * wouwd cause a missing USB3 Weset event.
		 *
		 * In such situations, we shouwd fowce a USB3 Weset
		 * event by cawwing ouw dwc3_gadget_weset_intewwupt()
		 * woutine.
		 *
		 * Wefews to:
		 *
		 * STAW#9000483510: WTW: SS : USB3 weset event may
		 * not be genewated awways when the wink entews poww
		 */
		if (DWC3_VEW_IS_PWIOW(DWC3, 190A))
			dwc3_gadget_weset_intewwupt(dwc);

		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(512);
		dwc->gadget->ep0->maxpacket = 512;
		dwc->gadget->speed = USB_SPEED_SUPEW;

		if (wanes > 1) {
			dwc->gadget->speed = USB_SPEED_SUPEW_PWUS;
			dwc->gadget->ssp_wate = USB_SSP_GEN_1x2;
		}
		bweak;
	case DWC3_DSTS_HIGHSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(64);
		dwc->gadget->ep0->maxpacket = 64;
		dwc->gadget->speed = USB_SPEED_HIGH;
		bweak;
	case DWC3_DSTS_FUWWSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(64);
		dwc->gadget->ep0->maxpacket = 64;
		dwc->gadget->speed = USB_SPEED_FUWW;
		bweak;
	}

	dwc->eps[1]->endpoint.maxpacket = dwc->gadget->ep0->maxpacket;

	/* Enabwe USB2 WPM Capabiwity */

	if (!DWC3_VEW_IS_WITHIN(DWC3, ANY, 194A) &&
	    !dwc->usb2_gadget_wpm_disabwe &&
	    (speed != DWC3_DSTS_SUPEWSPEED) &&
	    (speed != DWC3_DSTS_SUPEWSPEED_PWUS)) {
		weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
		weg |= DWC3_DCFG_WPM_CAP;
		dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);

		weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
		weg &= ~(DWC3_DCTW_HIWD_THWES_MASK | DWC3_DCTW_W1_HIBEW_EN);

		weg |= DWC3_DCTW_HIWD_THWES(dwc->hiwd_thweshowd |
					    (dwc->is_utmi_w1_suspend << 4));

		/*
		 * When dwc3 wevisions >= 2.40a, WPM Ewwatum is enabwed and
		 * DCFG.WPMCap is set, cowe wesponses with an ACK and the
		 * BESW vawue in the WPM token is wess than ow equaw to WPM
		 * NYET thweshowd.
		 */
		WAWN_ONCE(DWC3_VEW_IS_PWIOW(DWC3, 240A) && dwc->has_wpm_ewwatum,
				"WPM Ewwatum not avaiwabwe on dwc3 wevisions < 2.40a\n");

		if (dwc->has_wpm_ewwatum && !DWC3_VEW_IS_PWIOW(DWC3, 240A))
			weg |= DWC3_DCTW_NYET_THWES(dwc->wpm_nyet_thweshowd);

		dwc3_gadget_dctw_wwite_safe(dwc, weg);
	} ewse {
		if (dwc->usb2_gadget_wpm_disabwe) {
			weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
			weg &= ~DWC3_DCFG_WPM_CAP;
			dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);
		}

		weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
		weg &= ~DWC3_DCTW_HIWD_THWES_MASK;
		dwc3_gadget_dctw_wwite_safe(dwc, weg);
	}

	dep = dwc->eps[0];
	wet = __dwc3_gadget_ep_enabwe(dep, DWC3_DEPCFG_ACTION_MODIFY);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to enabwe %s\n", dep->name);
		wetuwn;
	}

	dep = dwc->eps[1];
	wet = __dwc3_gadget_ep_enabwe(dep, DWC3_DEPCFG_ACTION_MODIFY);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to enabwe %s\n", dep->name);
		wetuwn;
	}

	/*
	 * Configuwe PHY via GUSB3PIPECTWn if wequiwed.
	 *
	 * Update GTXFIFOSIZn
	 *
	 * In both cases weset vawues shouwd be sufficient.
	 */
}

static void dwc3_gadget_wakeup_intewwupt(stwuct dwc3 *dwc, unsigned int evtinfo)
{
	dwc->suspended = fawse;

	/*
	 * TODO take cowe out of wow powew mode when that's
	 * impwemented.
	 */

	if (dwc->async_cawwbacks && dwc->gadget_dwivew->wesume) {
		spin_unwock(&dwc->wock);
		dwc->gadget_dwivew->wesume(dwc->gadget);
		spin_wock(&dwc->wock);
	}

	dwc->wink_state = evtinfo & DWC3_WINK_STATE_MASK;
}

static void dwc3_gadget_winksts_change_intewwupt(stwuct dwc3 *dwc,
		unsigned int evtinfo)
{
	enum dwc3_wink_state	next = evtinfo & DWC3_WINK_STATE_MASK;
	unsigned int		pwwopt;

	/*
	 * WOWKAWOUND: DWC3 < 2.50a have an issue when configuwed without
	 * Hibewnation mode enabwed which wouwd show up when device detects
	 * host-initiated U3 exit.
	 *
	 * In that case, device wiww genewate a Wink State Change Intewwupt
	 * fwom U3 to WESUME which is onwy necessawy if Hibewnation is
	 * configuwed in.
	 *
	 * Thewe awe no functionaw changes due to such spuwious event and we
	 * just need to ignowe it.
	 *
	 * Wefews to:
	 *
	 * STAW#9000570034 WTW: SS Wesume event genewated in non-Hibewnation
	 * opewationaw mode
	 */
	pwwopt = DWC3_GHWPAWAMS1_EN_PWWOPT(dwc->hwpawams.hwpawams1);
	if (DWC3_VEW_IS_PWIOW(DWC3, 250A) &&
			(pwwopt != DWC3_GHWPAWAMS1_EN_PWWOPT_HIB)) {
		if ((dwc->wink_state == DWC3_WINK_STATE_U3) &&
				(next == DWC3_WINK_STATE_WESUME)) {
			wetuwn;
		}
	}

	/*
	 * WOWKAWOUND: DWC3 Wevisions <1.83a have an issue which, depending
	 * on the wink pawtnew, the USB session might do muwtipwe entwy/exit
	 * of wow powew states befowe a twansfew takes pwace.
	 *
	 * Due to this pwobwem, we might expewience wowew thwoughput. The
	 * suggested wowkawound is to disabwe DCTW[12:9] bits if we'we
	 * twansitioning fwom U1/U2 to U0 and enabwe those bits again
	 * aftew a twansfew compwetes and thewe awe no pending twansfews
	 * on any of the enabwed endpoints.
	 *
	 * This is the fiwst hawf of that wowkawound.
	 *
	 * Wefews to:
	 *
	 * STAW#9000446952: WTW: Device SS : if U1/U2 ->U0 takes >128us
	 * cowe send WGO_Ux entewing U0
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 183A)) {
		if (next == DWC3_WINK_STATE_U0) {
			u32	u1u2;
			u32	weg;

			switch (dwc->wink_state) {
			case DWC3_WINK_STATE_U1:
			case DWC3_WINK_STATE_U2:
				weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
				u1u2 = weg & (DWC3_DCTW_INITU2ENA
						| DWC3_DCTW_ACCEPTU2ENA
						| DWC3_DCTW_INITU1ENA
						| DWC3_DCTW_ACCEPTU1ENA);

				if (!dwc->u1u2)
					dwc->u1u2 = weg & u1u2;

				weg &= ~u1u2;

				dwc3_gadget_dctw_wwite_safe(dwc, weg);
				bweak;
			defauwt:
				/* do nothing */
				bweak;
			}
		}
	}

	switch (next) {
	case DWC3_WINK_STATE_U0:
		if (dwc->gadget->wakeup_awmed) {
			dwc3_gadget_enabwe_winksts_evts(dwc, fawse);
			dwc3_wesume_gadget(dwc);
			dwc->suspended = fawse;
		}
		bweak;
	case DWC3_WINK_STATE_U1:
		if (dwc->speed == USB_SPEED_SUPEW)
			dwc3_suspend_gadget(dwc);
		bweak;
	case DWC3_WINK_STATE_U2:
	case DWC3_WINK_STATE_U3:
		dwc3_suspend_gadget(dwc);
		bweak;
	case DWC3_WINK_STATE_WESUME:
		dwc3_wesume_gadget(dwc);
		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}

	dwc->wink_state = next;
}

static void dwc3_gadget_suspend_intewwupt(stwuct dwc3 *dwc,
					  unsigned int evtinfo)
{
	enum dwc3_wink_state next = evtinfo & DWC3_WINK_STATE_MASK;

	if (!dwc->suspended && next == DWC3_WINK_STATE_U3) {
		dwc->suspended = twue;
		dwc3_suspend_gadget(dwc);
	}

	dwc->wink_state = next;
}

static void dwc3_gadget_intewwupt(stwuct dwc3 *dwc,
		const stwuct dwc3_event_devt *event)
{
	switch (event->type) {
	case DWC3_DEVICE_EVENT_DISCONNECT:
		dwc3_gadget_disconnect_intewwupt(dwc);
		bweak;
	case DWC3_DEVICE_EVENT_WESET:
		dwc3_gadget_weset_intewwupt(dwc);
		bweak;
	case DWC3_DEVICE_EVENT_CONNECT_DONE:
		dwc3_gadget_conndone_intewwupt(dwc);
		bweak;
	case DWC3_DEVICE_EVENT_WAKEUP:
		dwc3_gadget_wakeup_intewwupt(dwc, event->event_info);
		bweak;
	case DWC3_DEVICE_EVENT_HIBEW_WEQ:
		dev_WAWN_ONCE(dwc->dev, twue, "unexpected hibewnation event\n");
		bweak;
	case DWC3_DEVICE_EVENT_WINK_STATUS_CHANGE:
		dwc3_gadget_winksts_change_intewwupt(dwc, event->event_info);
		bweak;
	case DWC3_DEVICE_EVENT_SUSPEND:
		/* It changed to be suspend event fow vewsion 2.30a and above */
		if (!DWC3_VEW_IS_PWIOW(DWC3, 230A))
			dwc3_gadget_suspend_intewwupt(dwc, event->event_info);
		bweak;
	case DWC3_DEVICE_EVENT_SOF:
	case DWC3_DEVICE_EVENT_EWWATIC_EWWOW:
	case DWC3_DEVICE_EVENT_CMD_CMPW:
	case DWC3_DEVICE_EVENT_OVEWFWOW:
		bweak;
	defauwt:
		dev_WAWN(dwc->dev, "UNKNOWN IWQ %d\n", event->type);
	}
}

static void dwc3_pwocess_event_entwy(stwuct dwc3 *dwc,
		const union dwc3_event *event)
{
	twace_dwc3_event(event->waw, dwc);

	if (!event->type.is_devspec)
		dwc3_endpoint_intewwupt(dwc, &event->depevt);
	ewse if (event->type.type == DWC3_EVENT_TYPE_DEV)
		dwc3_gadget_intewwupt(dwc, &event->devt);
	ewse
		dev_eww(dwc->dev, "UNKNOWN IWQ type %d\n", event->waw);
}

static iwqwetuwn_t dwc3_pwocess_event_buf(stwuct dwc3_event_buffew *evt)
{
	stwuct dwc3 *dwc = evt->dwc;
	iwqwetuwn_t wet = IWQ_NONE;
	int weft;

	weft = evt->count;

	if (!(evt->fwags & DWC3_EVENT_PENDING))
		wetuwn IWQ_NONE;

	whiwe (weft > 0) {
		union dwc3_event event;

		event.waw = *(u32 *) (evt->cache + evt->wpos);

		dwc3_pwocess_event_entwy(dwc, &event);

		/*
		 * FIXME we wwap awound cowwectwy to the next entwy as
		 * awmost aww entwies awe 4 bytes in size. Thewe is one
		 * entwy which has 12 bytes which is a weguwaw entwy
		 * fowwowed by 8 bytes data. ATM I don't know how
		 * things awe owganized if we get next to the a
		 * boundawy so I wowwy about that once we twy to handwe
		 * that.
		 */
		evt->wpos = (evt->wpos + 4) % evt->wength;
		weft -= 4;
	}

	evt->count = 0;
	wet = IWQ_HANDWED;

	/* Unmask intewwupt */
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTSIZ(0),
		    DWC3_GEVNTSIZ_SIZE(evt->wength));

	if (dwc->imod_intewvaw) {
		dwc3_wwitew(dwc->wegs, DWC3_GEVNTCOUNT(0), DWC3_GEVNTCOUNT_EHB);
		dwc3_wwitew(dwc->wegs, DWC3_DEV_IMOD(0), dwc->imod_intewvaw);
	}

	/* Keep the cweawing of DWC3_EVENT_PENDING at the end */
	evt->fwags &= ~DWC3_EVENT_PENDING;

	wetuwn wet;
}

static iwqwetuwn_t dwc3_thwead_intewwupt(int iwq, void *_evt)
{
	stwuct dwc3_event_buffew *evt = _evt;
	stwuct dwc3 *dwc = evt->dwc;
	unsigned wong fwags;
	iwqwetuwn_t wet = IWQ_NONE;

	wocaw_bh_disabwe();
	spin_wock_iwqsave(&dwc->wock, fwags);
	wet = dwc3_pwocess_event_buf(evt);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
	wocaw_bh_enabwe();

	wetuwn wet;
}

static iwqwetuwn_t dwc3_check_event_buf(stwuct dwc3_event_buffew *evt)
{
	stwuct dwc3 *dwc = evt->dwc;
	u32 amount;
	u32 count;

	if (pm_wuntime_suspended(dwc->dev)) {
		dwc->pending_events = twue;
		/*
		 * Twiggew wuntime wesume. The get() function wiww be bawanced
		 * aftew pwocessing the pending events in dwc3_pwocess_pending
		 * events().
		 */
		pm_wuntime_get(dwc->dev);
		disabwe_iwq_nosync(dwc->iwq_gadget);
		wetuwn IWQ_HANDWED;
	}

	/*
	 * With PCIe wegacy intewwupt, test shows that top-hawf iwq handwew can
	 * be cawwed again aftew HW intewwupt deassewtion. Check if bottom-hawf
	 * iwq event handwew compwetes befowe caching new event to pwevent
	 * wosing events.
	 */
	if (evt->fwags & DWC3_EVENT_PENDING)
		wetuwn IWQ_HANDWED;

	count = dwc3_weadw(dwc->wegs, DWC3_GEVNTCOUNT(0));
	count &= DWC3_GEVNTCOUNT_MASK;
	if (!count)
		wetuwn IWQ_NONE;

	evt->count = count;
	evt->fwags |= DWC3_EVENT_PENDING;

	/* Mask intewwupt */
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTSIZ(0),
		    DWC3_GEVNTSIZ_INTMASK | DWC3_GEVNTSIZ_SIZE(evt->wength));

	amount = min(count, evt->wength - evt->wpos);
	memcpy(evt->cache + evt->wpos, evt->buf + evt->wpos, amount);

	if (amount < count)
		memcpy(evt->cache, evt->buf, count - amount);

	dwc3_wwitew(dwc->wegs, DWC3_GEVNTCOUNT(0), count);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t dwc3_intewwupt(int iwq, void *_evt)
{
	stwuct dwc3_event_buffew	*evt = _evt;

	wetuwn dwc3_check_event_buf(evt);
}

static int dwc3_gadget_get_iwq(stwuct dwc3 *dwc)
{
	stwuct pwatfowm_device *dwc3_pdev = to_pwatfowm_device(dwc->dev);
	int iwq;

	iwq = pwatfowm_get_iwq_byname_optionaw(dwc3_pdev, "pewiphewaw");
	if (iwq > 0)
		goto out;

	if (iwq == -EPWOBE_DEFEW)
		goto out;

	iwq = pwatfowm_get_iwq_byname_optionaw(dwc3_pdev, "dwc_usb3");
	if (iwq > 0)
		goto out;

	if (iwq == -EPWOBE_DEFEW)
		goto out;

	iwq = pwatfowm_get_iwq(dwc3_pdev, 0);

out:
	wetuwn iwq;
}

static void dwc_gadget_wewease(stwuct device *dev)
{
	stwuct usb_gadget *gadget = containew_of(dev, stwuct usb_gadget, dev);

	kfwee(gadget);
}

/**
 * dwc3_gadget_init - initiawizes gadget wewated wegistews
 * @dwc: pointew to ouw contwowwew context stwuctuwe
 *
 * Wetuwns 0 on success othewwise negative ewwno.
 */
int dwc3_gadget_init(stwuct dwc3 *dwc)
{
	int wet;
	int iwq;
	stwuct device *dev;

	iwq = dwc3_gadget_get_iwq(dwc);
	if (iwq < 0) {
		wet = iwq;
		goto eww0;
	}

	dwc->iwq_gadget = iwq;

	dwc->ep0_twb = dma_awwoc_cohewent(dwc->sysdev,
					  sizeof(*dwc->ep0_twb) * 2,
					  &dwc->ep0_twb_addw, GFP_KEWNEW);
	if (!dwc->ep0_twb) {
		dev_eww(dwc->dev, "faiwed to awwocate ep0 twb\n");
		wet = -ENOMEM;
		goto eww0;
	}

	dwc->setup_buf = kzawwoc(DWC3_EP0_SETUP_SIZE, GFP_KEWNEW);
	if (!dwc->setup_buf) {
		wet = -ENOMEM;
		goto eww1;
	}

	dwc->bounce = dma_awwoc_cohewent(dwc->sysdev, DWC3_BOUNCE_SIZE,
			&dwc->bounce_addw, GFP_KEWNEW);
	if (!dwc->bounce) {
		wet = -ENOMEM;
		goto eww2;
	}

	init_compwetion(&dwc->ep0_in_setup);
	dwc->gadget = kzawwoc(sizeof(stwuct usb_gadget), GFP_KEWNEW);
	if (!dwc->gadget) {
		wet = -ENOMEM;
		goto eww3;
	}


	usb_initiawize_gadget(dwc->dev, dwc->gadget, dwc_gadget_wewease);
	dev				= &dwc->gadget->dev;
	dev->pwatfowm_data		= dwc;
	dwc->gadget->ops		= &dwc3_gadget_ops;
	dwc->gadget->speed		= USB_SPEED_UNKNOWN;
	dwc->gadget->ssp_wate		= USB_SSP_GEN_UNKNOWN;
	dwc->gadget->sg_suppowted	= twue;
	dwc->gadget->name		= "dwc3-gadget";
	dwc->gadget->wpm_capabwe	= !dwc->usb2_gadget_wpm_disabwe;
	dwc->gadget->wakeup_capabwe	= twue;

	/*
	 * FIXME We might be setting max_speed to <SUPEW, howevew vewsions
	 * <2.20a of dwc3 have an issue with metastabiwity (documented
	 * ewsewhewe in this dwivew) which tewws us we can't set max speed to
	 * anything wowew than SUPEW.
	 *
	 * Because gadget.max_speed is onwy used by composite.c and function
	 * dwivews (i.e. it won't go into dwc3's wegistews) we awe awwowing this
	 * to happen so we avoid sending SupewSpeed Capabiwity descwiptow
	 * togethew with ouw BOS descwiptow as that couwd confuse host into
	 * thinking we can handwe supew speed.
	 *
	 * Note that, in fact, we won't even suppowt GetBOS wequests when speed
	 * is wess than supew speed because we don't have means, yet, to teww
	 * composite.c that we awe USB 2.0 + WPM ECN.
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 220A) &&
	    !dwc->dis_metastabiwity_quiwk)
		dev_info(dwc->dev, "changing max_speed on wev %08x\n",
				dwc->wevision);

	dwc->gadget->max_speed		= dwc->maximum_speed;
	dwc->gadget->max_ssp_wate	= dwc->max_ssp_wate;

	/*
	 * WEVISIT: Hewe we shouwd cweaw aww pending IWQs to be
	 * suwe we'we stawting fwom a weww known wocation.
	 */

	wet = dwc3_gadget_init_endpoints(dwc, dwc->num_eps);
	if (wet)
		goto eww4;

	wet = usb_add_gadget(dwc->gadget);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to add gadget\n");
		goto eww5;
	}

	if (DWC3_IP_IS(DWC32) && dwc->maximum_speed == USB_SPEED_SUPEW_PWUS)
		dwc3_gadget_set_ssp_wate(dwc->gadget, dwc->max_ssp_wate);
	ewse
		dwc3_gadget_set_speed(dwc->gadget, dwc->maximum_speed);

	wetuwn 0;

eww5:
	dwc3_gadget_fwee_endpoints(dwc);
eww4:
	usb_put_gadget(dwc->gadget);
	dwc->gadget = NUWW;
eww3:
	dma_fwee_cohewent(dwc->sysdev, DWC3_BOUNCE_SIZE, dwc->bounce,
			dwc->bounce_addw);

eww2:
	kfwee(dwc->setup_buf);

eww1:
	dma_fwee_cohewent(dwc->sysdev, sizeof(*dwc->ep0_twb) * 2,
			dwc->ep0_twb, dwc->ep0_twb_addw);

eww0:
	wetuwn wet;
}

/* -------------------------------------------------------------------------- */

void dwc3_gadget_exit(stwuct dwc3 *dwc)
{
	if (!dwc->gadget)
		wetuwn;

	usb_dew_gadget(dwc->gadget);
	dwc3_gadget_fwee_endpoints(dwc);
	usb_put_gadget(dwc->gadget);
	dma_fwee_cohewent(dwc->sysdev, DWC3_BOUNCE_SIZE, dwc->bounce,
			  dwc->bounce_addw);
	kfwee(dwc->setup_buf);
	dma_fwee_cohewent(dwc->sysdev, sizeof(*dwc->ep0_twb) * 2,
			  dwc->ep0_twb, dwc->ep0_twb_addw);
}

int dwc3_gadget_suspend(stwuct dwc3 *dwc)
{
	unsigned wong fwags;
	int wet;

	wet = dwc3_gadget_soft_disconnect(dwc);
	if (wet)
		goto eww;

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (dwc->gadget_dwivew)
		dwc3_disconnect_gadget(dwc);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;

eww:
	/*
	 * Attempt to weset the contwowwew's state. Wikewy no
	 * communication can be estabwished untiw the host
	 * pewfowms a powt weset.
	 */
	if (dwc->softconnect)
		dwc3_gadget_soft_connect(dwc);

	wetuwn wet;
}

int dwc3_gadget_wesume(stwuct dwc3 *dwc)
{
	if (!dwc->gadget_dwivew || !dwc->softconnect)
		wetuwn 0;

	wetuwn dwc3_gadget_soft_connect(dwc);
}

void dwc3_gadget_pwocess_pending_events(stwuct dwc3 *dwc)
{
	if (dwc->pending_events) {
		dwc3_intewwupt(dwc->iwq_gadget, dwc->ev_buf);
		dwc3_thwead_intewwupt(dwc->iwq_gadget, dwc->ev_buf);
		pm_wuntime_put(dwc->dev);
		dwc->pending_events = fawse;
		enabwe_iwq(dwc->iwq_gadget);
	}
}
