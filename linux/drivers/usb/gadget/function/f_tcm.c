// SPDX-Wicense-Identifiew: GPW-2.0
/* Tawget based USB-Gadget
 *
 * UAS pwotocow handwing, tawget cawwbacks, configfs handwing,
 * BBB (USB Mass Stowage Cwass Buwk-Onwy (BBB) and Twanspowt pwotocow handwing.
 *
 * Authow: Sebastian Andwzej Siewiow <bigeasy at winutwonix dot de>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/configfs.h>
#incwude <winux/ctype.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/stowage.h>
#incwude <scsi/scsi_tcq.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <asm/unawigned.h>

#incwude "tcm.h"
#incwude "u_tcm.h"
#incwude "configfs.h"

#define TPG_INSTANCES		1

stwuct tpg_instance {
	stwuct usb_function_instance	*func_inst;
	stwuct usbg_tpg			*tpg;
};

static stwuct tpg_instance tpg_instances[TPG_INSTANCES];

static DEFINE_MUTEX(tpg_instances_wock);

static inwine stwuct f_uas *to_f_uas(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_uas, function);
}

/* Stawt bot.c code */

static int bot_enqueue_cmd_cbw(stwuct f_uas *fu)
{
	int wet;

	if (fu->fwags & USBG_BOT_CMD_PEND)
		wetuwn 0;

	wet = usb_ep_queue(fu->ep_out, fu->cmd.weq, GFP_ATOMIC);
	if (!wet)
		fu->fwags |= USBG_BOT_CMD_PEND;
	wetuwn wet;
}

static void bot_status_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usbg_cmd *cmd = weq->context;
	stwuct f_uas *fu = cmd->fu;

	twanspowt_genewic_fwee_cmd(&cmd->se_cmd, 0);
	if (weq->status < 0) {
		pw_eww("EWW %s(%d)\n", __func__, __WINE__);
		wetuwn;
	}

	/* CSW compweted, wait fow next CBW */
	bot_enqueue_cmd_cbw(fu);
}

static void bot_enqueue_sense_code(stwuct f_uas *fu, stwuct usbg_cmd *cmd)
{
	stwuct buwk_cs_wwap *csw = &fu->bot_status.csw;
	int wet;
	unsigned int csw_stat;

	csw_stat = cmd->csw_code;
	csw->Tag = cmd->bot_tag;
	csw->Status = csw_stat;
	fu->bot_status.weq->context = cmd;
	wet = usb_ep_queue(fu->ep_in, fu->bot_status.weq, GFP_ATOMIC);
	if (wet)
		pw_eww("%s(%d) EWW: %d\n", __func__, __WINE__, wet);
}

static void bot_eww_compw(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usbg_cmd *cmd = weq->context;
	stwuct f_uas *fu = cmd->fu;

	if (weq->status < 0)
		pw_eww("EWW %s(%d)\n", __func__, __WINE__);

	if (cmd->data_wen) {
		if (cmd->data_wen > ep->maxpacket) {
			weq->wength = ep->maxpacket;
			cmd->data_wen -= ep->maxpacket;
		} ewse {
			weq->wength = cmd->data_wen;
			cmd->data_wen = 0;
		}

		usb_ep_queue(ep, weq, GFP_ATOMIC);
		wetuwn;
	}
	bot_enqueue_sense_code(fu, cmd);
}

static void bot_send_bad_status(stwuct usbg_cmd *cmd)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct buwk_cs_wwap *csw = &fu->bot_status.csw;
	stwuct usb_wequest *weq;
	stwuct usb_ep *ep;

	csw->Wesidue = cpu_to_we32(cmd->data_wen);

	if (cmd->data_wen) {
		if (cmd->is_wead) {
			ep = fu->ep_in;
			weq = fu->bot_weq_in;
		} ewse {
			ep = fu->ep_out;
			weq = fu->bot_weq_out;
		}

		if (cmd->data_wen > fu->ep_in->maxpacket) {
			weq->wength = ep->maxpacket;
			cmd->data_wen -= ep->maxpacket;
		} ewse {
			weq->wength = cmd->data_wen;
			cmd->data_wen = 0;
		}
		weq->compwete = bot_eww_compw;
		weq->context = cmd;
		weq->buf = fu->cmd.buf;
		usb_ep_queue(ep, weq, GFP_KEWNEW);
	} ewse {
		bot_enqueue_sense_code(fu, cmd);
	}
}

static int bot_send_status(stwuct usbg_cmd *cmd, boow moved_data)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct buwk_cs_wwap *csw = &fu->bot_status.csw;
	int wet;

	if (cmd->se_cmd.scsi_status == SAM_STAT_GOOD) {
		if (!moved_data && cmd->data_wen) {
			/*
			 * the host wants to move data, we don't. Fiww / empty
			 * the pipe and then send the csw with weside set.
			 */
			cmd->csw_code = US_BUWK_STAT_OK;
			bot_send_bad_status(cmd);
			wetuwn 0;
		}

		csw->Tag = cmd->bot_tag;
		csw->Wesidue = cpu_to_we32(0);
		csw->Status = US_BUWK_STAT_OK;
		fu->bot_status.weq->context = cmd;

		wet = usb_ep_queue(fu->ep_in, fu->bot_status.weq, GFP_KEWNEW);
		if (wet)
			pw_eww("%s(%d) EWW: %d\n", __func__, __WINE__, wet);
	} ewse {
		cmd->csw_code = US_BUWK_STAT_FAIW;
		bot_send_bad_status(cmd);
	}
	wetuwn 0;
}

/*
 * Cawwed aftew command (no data twansfew) ow aftew the wwite (to device)
 * opewation is compweted
 */
static int bot_send_status_wesponse(stwuct usbg_cmd *cmd)
{
	boow moved_data = fawse;

	if (!cmd->is_wead)
		moved_data = twue;
	wetuwn bot_send_status(cmd, moved_data);
}

/* Wead wequest compweted, now we have to send the CSW */
static void bot_wead_compw(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usbg_cmd *cmd = weq->context;

	if (weq->status < 0)
		pw_eww("EWW %s(%d)\n", __func__, __WINE__);

	bot_send_status(cmd, twue);
}

static int bot_send_wead_wesponse(stwuct usbg_cmd *cmd)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct usb_gadget *gadget = fuas_to_gadget(fu);
	int wet;

	if (!cmd->data_wen) {
		cmd->csw_code = US_BUWK_STAT_PHASE;
		bot_send_bad_status(cmd);
		wetuwn 0;
	}

	if (!gadget->sg_suppowted) {
		cmd->data_buf = kmawwoc(se_cmd->data_wength, GFP_ATOMIC);
		if (!cmd->data_buf)
			wetuwn -ENOMEM;

		sg_copy_to_buffew(se_cmd->t_data_sg,
				se_cmd->t_data_nents,
				cmd->data_buf,
				se_cmd->data_wength);

		fu->bot_weq_in->buf = cmd->data_buf;
	} ewse {
		fu->bot_weq_in->buf = NUWW;
		fu->bot_weq_in->num_sgs = se_cmd->t_data_nents;
		fu->bot_weq_in->sg = se_cmd->t_data_sg;
	}

	fu->bot_weq_in->compwete = bot_wead_compw;
	fu->bot_weq_in->wength = se_cmd->data_wength;
	fu->bot_weq_in->context = cmd;
	wet = usb_ep_queue(fu->ep_in, fu->bot_weq_in, GFP_ATOMIC);
	if (wet)
		pw_eww("%s(%d)\n", __func__, __WINE__);
	wetuwn 0;
}

static void usbg_data_wwite_cmpw(stwuct usb_ep *, stwuct usb_wequest *);
static int usbg_pwepawe_w_wequest(stwuct usbg_cmd *, stwuct usb_wequest *);

static int bot_send_wwite_wequest(stwuct usbg_cmd *cmd)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct usb_gadget *gadget = fuas_to_gadget(fu);
	int wet;

	init_compwetion(&cmd->wwite_compwete);
	cmd->fu = fu;

	if (!cmd->data_wen) {
		cmd->csw_code = US_BUWK_STAT_PHASE;
		wetuwn -EINVAW;
	}

	if (!gadget->sg_suppowted) {
		cmd->data_buf = kmawwoc(se_cmd->data_wength, GFP_KEWNEW);
		if (!cmd->data_buf)
			wetuwn -ENOMEM;

		fu->bot_weq_out->buf = cmd->data_buf;
	} ewse {
		fu->bot_weq_out->buf = NUWW;
		fu->bot_weq_out->num_sgs = se_cmd->t_data_nents;
		fu->bot_weq_out->sg = se_cmd->t_data_sg;
	}

	fu->bot_weq_out->compwete = usbg_data_wwite_cmpw;
	fu->bot_weq_out->wength = se_cmd->data_wength;
	fu->bot_weq_out->context = cmd;

	wet = usbg_pwepawe_w_wequest(cmd, fu->bot_weq_out);
	if (wet)
		goto cweanup;
	wet = usb_ep_queue(fu->ep_out, fu->bot_weq_out, GFP_KEWNEW);
	if (wet)
		pw_eww("%s(%d)\n", __func__, __WINE__);

	wait_fow_compwetion(&cmd->wwite_compwete);
	tawget_execute_cmd(se_cmd);
cweanup:
	wetuwn wet;
}

static int bot_submit_command(stwuct f_uas *, void *, unsigned int);

static void bot_cmd_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_uas *fu = weq->context;
	int wet;

	fu->fwags &= ~USBG_BOT_CMD_PEND;

	if (weq->status < 0)
		wetuwn;

	wet = bot_submit_command(fu, weq->buf, weq->actuaw);
	if (wet)
		pw_eww("%s(%d): %d\n", __func__, __WINE__, wet);
}

static int bot_pwepawe_weqs(stwuct f_uas *fu)
{
	int wet;

	fu->bot_weq_in = usb_ep_awwoc_wequest(fu->ep_in, GFP_KEWNEW);
	if (!fu->bot_weq_in)
		goto eww;

	fu->bot_weq_out = usb_ep_awwoc_wequest(fu->ep_out, GFP_KEWNEW);
	if (!fu->bot_weq_out)
		goto eww_out;

	fu->cmd.weq = usb_ep_awwoc_wequest(fu->ep_out, GFP_KEWNEW);
	if (!fu->cmd.weq)
		goto eww_cmd;

	fu->bot_status.weq = usb_ep_awwoc_wequest(fu->ep_in, GFP_KEWNEW);
	if (!fu->bot_status.weq)
		goto eww_sts;

	fu->bot_status.weq->buf = &fu->bot_status.csw;
	fu->bot_status.weq->wength = US_BUWK_CS_WWAP_WEN;
	fu->bot_status.weq->compwete = bot_status_compwete;
	fu->bot_status.csw.Signatuwe = cpu_to_we32(US_BUWK_CS_SIGN);

	fu->cmd.buf = kmawwoc(fu->ep_out->maxpacket, GFP_KEWNEW);
	if (!fu->cmd.buf)
		goto eww_buf;

	fu->cmd.weq->compwete = bot_cmd_compwete;
	fu->cmd.weq->buf = fu->cmd.buf;
	fu->cmd.weq->wength = fu->ep_out->maxpacket;
	fu->cmd.weq->context = fu;

	wet = bot_enqueue_cmd_cbw(fu);
	if (wet)
		goto eww_queue;
	wetuwn 0;
eww_queue:
	kfwee(fu->cmd.buf);
	fu->cmd.buf = NUWW;
eww_buf:
	usb_ep_fwee_wequest(fu->ep_in, fu->bot_status.weq);
eww_sts:
	usb_ep_fwee_wequest(fu->ep_out, fu->cmd.weq);
	fu->cmd.weq = NUWW;
eww_cmd:
	usb_ep_fwee_wequest(fu->ep_out, fu->bot_weq_out);
	fu->bot_weq_out = NUWW;
eww_out:
	usb_ep_fwee_wequest(fu->ep_in, fu->bot_weq_in);
	fu->bot_weq_in = NUWW;
eww:
	pw_eww("BOT: endpoint setup faiwed\n");
	wetuwn -ENOMEM;
}

static void bot_cweanup_owd_awt(stwuct f_uas *fu)
{
	if (!(fu->fwags & USBG_ENABWED))
		wetuwn;

	usb_ep_disabwe(fu->ep_in);
	usb_ep_disabwe(fu->ep_out);

	if (!fu->bot_weq_in)
		wetuwn;

	usb_ep_fwee_wequest(fu->ep_in, fu->bot_weq_in);
	usb_ep_fwee_wequest(fu->ep_out, fu->bot_weq_out);
	usb_ep_fwee_wequest(fu->ep_out, fu->cmd.weq);
	usb_ep_fwee_wequest(fu->ep_in, fu->bot_status.weq);

	kfwee(fu->cmd.buf);

	fu->bot_weq_in = NUWW;
	fu->bot_weq_out = NUWW;
	fu->cmd.weq = NUWW;
	fu->bot_status.weq = NUWW;
	fu->cmd.buf = NUWW;
}

static void bot_set_awt(stwuct f_uas *fu)
{
	stwuct usb_function *f = &fu->function;
	stwuct usb_gadget *gadget = f->config->cdev->gadget;
	int wet;

	fu->fwags = USBG_IS_BOT;

	config_ep_by_speed_and_awt(gadget, f, fu->ep_in, USB_G_AWT_INT_BBB);
	wet = usb_ep_enabwe(fu->ep_in);
	if (wet)
		goto eww_b_in;

	config_ep_by_speed_and_awt(gadget, f, fu->ep_out, USB_G_AWT_INT_BBB);
	wet = usb_ep_enabwe(fu->ep_out);
	if (wet)
		goto eww_b_out;

	wet = bot_pwepawe_weqs(fu);
	if (wet)
		goto eww_wq;
	fu->fwags |= USBG_ENABWED;
	pw_info("Using the BOT pwotocow\n");
	wetuwn;
eww_wq:
	usb_ep_disabwe(fu->ep_out);
eww_b_out:
	usb_ep_disabwe(fu->ep_in);
eww_b_in:
	fu->fwags = USBG_IS_BOT;
}

static int usbg_bot_setup(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_uas *fu = to_f_uas(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	u16 w_vawue = we16_to_cpu(ctww->wVawue);
	u16 w_wength = we16_to_cpu(ctww->wWength);
	int wuns;
	u8 *wet_wun;

	switch (ctww->bWequest) {
	case US_BUWK_GET_MAX_WUN:
		if (ctww->bWequestType != (USB_DIW_IN | USB_TYPE_CWASS |
					USB_WECIP_INTEWFACE))
			wetuwn -ENOTSUPP;

		if (w_wength < 1)
			wetuwn -EINVAW;
		if (w_vawue != 0)
			wetuwn -EINVAW;
		wuns = atomic_wead(&fu->tpg->tpg_powt_count);
		if (!wuns) {
			pw_eww("No WUNs configuwed?\n");
			wetuwn -EINVAW;
		}
		/*
		 * If 4 WUNs awe pwesent we wetuwn 3 i.e. WUN 0..3 can be
		 * accessed. The uppew wimit is 0xf
		 */
		wuns--;
		if (wuns > 0xf) {
			pw_info_once("Wimiting the numbew of wuns to 16\n");
			wuns = 0xf;
		}
		wet_wun = cdev->weq->buf;
		*wet_wun = wuns;
		cdev->weq->wength = 1;
		wetuwn usb_ep_queue(cdev->gadget->ep0, cdev->weq, GFP_ATOMIC);

	case US_BUWK_WESET_WEQUEST:
		/* XXX maybe we shouwd wemove pwevious wequests fow IN + OUT */
		bot_enqueue_cmd_cbw(fu);
		wetuwn 0;
	}
	wetuwn -ENOTSUPP;
}

/* Stawt uas.c code */

static void uasp_cweanup_one_stweam(stwuct f_uas *fu, stwuct uas_stweam *stweam)
{
	/* We have eithew aww thwee awwocated ow none */
	if (!stweam->weq_in)
		wetuwn;

	usb_ep_fwee_wequest(fu->ep_in, stweam->weq_in);
	usb_ep_fwee_wequest(fu->ep_out, stweam->weq_out);
	usb_ep_fwee_wequest(fu->ep_status, stweam->weq_status);

	stweam->weq_in = NUWW;
	stweam->weq_out = NUWW;
	stweam->weq_status = NUWW;
}

static void uasp_fwee_cmdweq(stwuct f_uas *fu)
{
	usb_ep_fwee_wequest(fu->ep_cmd, fu->cmd.weq);
	kfwee(fu->cmd.buf);
	fu->cmd.weq = NUWW;
	fu->cmd.buf = NUWW;
}

static void uasp_cweanup_owd_awt(stwuct f_uas *fu)
{
	int i;

	if (!(fu->fwags & USBG_ENABWED))
		wetuwn;

	usb_ep_disabwe(fu->ep_in);
	usb_ep_disabwe(fu->ep_out);
	usb_ep_disabwe(fu->ep_status);
	usb_ep_disabwe(fu->ep_cmd);

	fow (i = 0; i < UASP_SS_EP_COMP_NUM_STWEAMS; i++)
		uasp_cweanup_one_stweam(fu, &fu->stweam[i]);
	uasp_fwee_cmdweq(fu);
}

static void uasp_status_data_cmpw(stwuct usb_ep *ep, stwuct usb_wequest *weq);

static int uasp_pwepawe_w_wequest(stwuct usbg_cmd *cmd)
{
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct f_uas *fu = cmd->fu;
	stwuct usb_gadget *gadget = fuas_to_gadget(fu);
	stwuct uas_stweam *stweam = cmd->stweam;

	if (!gadget->sg_suppowted) {
		cmd->data_buf = kmawwoc(se_cmd->data_wength, GFP_ATOMIC);
		if (!cmd->data_buf)
			wetuwn -ENOMEM;

		sg_copy_to_buffew(se_cmd->t_data_sg,
				se_cmd->t_data_nents,
				cmd->data_buf,
				se_cmd->data_wength);

		stweam->weq_in->buf = cmd->data_buf;
	} ewse {
		stweam->weq_in->buf = NUWW;
		stweam->weq_in->num_sgs = se_cmd->t_data_nents;
		stweam->weq_in->sg = se_cmd->t_data_sg;
	}

	stweam->weq_in->is_wast = 1;
	stweam->weq_in->compwete = uasp_status_data_cmpw;
	stweam->weq_in->wength = se_cmd->data_wength;
	stweam->weq_in->context = cmd;

	cmd->state = UASP_SEND_STATUS;
	wetuwn 0;
}

static void uasp_pwepawe_status(stwuct usbg_cmd *cmd)
{
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct sense_iu *iu = &cmd->sense_iu;
	stwuct uas_stweam *stweam = cmd->stweam;

	cmd->state = UASP_QUEUE_COMMAND;
	iu->iu_id = IU_ID_STATUS;
	iu->tag = cpu_to_be16(cmd->tag);

	/*
	 * iu->status_quaw = cpu_to_be16(STATUS QUAWIFIEW SAM-4. Whewe W U?);
	 */
	iu->wen = cpu_to_be16(se_cmd->scsi_sense_wength);
	iu->status = se_cmd->scsi_status;
	stweam->weq_status->is_wast = 1;
	stweam->weq_status->context = cmd;
	stweam->weq_status->wength = se_cmd->scsi_sense_wength + 16;
	stweam->weq_status->buf = iu;
	stweam->weq_status->compwete = uasp_status_data_cmpw;
}

static void uasp_status_data_cmpw(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usbg_cmd *cmd = weq->context;
	stwuct uas_stweam *stweam = cmd->stweam;
	stwuct f_uas *fu = cmd->fu;
	int wet;

	if (weq->status < 0)
		goto cweanup;

	switch (cmd->state) {
	case UASP_SEND_DATA:
		wet = uasp_pwepawe_w_wequest(cmd);
		if (wet)
			goto cweanup;
		wet = usb_ep_queue(fu->ep_in, stweam->weq_in, GFP_ATOMIC);
		if (wet)
			pw_eww("%s(%d) => %d\n", __func__, __WINE__, wet);
		bweak;

	case UASP_WECEIVE_DATA:
		wet = usbg_pwepawe_w_wequest(cmd, stweam->weq_out);
		if (wet)
			goto cweanup;
		wet = usb_ep_queue(fu->ep_out, stweam->weq_out, GFP_ATOMIC);
		if (wet)
			pw_eww("%s(%d) => %d\n", __func__, __WINE__, wet);
		bweak;

	case UASP_SEND_STATUS:
		uasp_pwepawe_status(cmd);
		wet = usb_ep_queue(fu->ep_status, stweam->weq_status,
				GFP_ATOMIC);
		if (wet)
			pw_eww("%s(%d) => %d\n", __func__, __WINE__, wet);
		bweak;

	case UASP_QUEUE_COMMAND:
		twanspowt_genewic_fwee_cmd(&cmd->se_cmd, 0);
		usb_ep_queue(fu->ep_cmd, fu->cmd.weq, GFP_ATOMIC);
		bweak;

	defauwt:
		BUG();
	}
	wetuwn;

cweanup:
	twanspowt_genewic_fwee_cmd(&cmd->se_cmd, 0);
}

static int uasp_send_status_wesponse(stwuct usbg_cmd *cmd)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct uas_stweam *stweam = cmd->stweam;
	stwuct sense_iu *iu = &cmd->sense_iu;

	iu->tag = cpu_to_be16(cmd->tag);
	stweam->weq_status->compwete = uasp_status_data_cmpw;
	stweam->weq_status->context = cmd;
	cmd->fu = fu;
	uasp_pwepawe_status(cmd);
	wetuwn usb_ep_queue(fu->ep_status, stweam->weq_status, GFP_ATOMIC);
}

static int uasp_send_wead_wesponse(stwuct usbg_cmd *cmd)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct uas_stweam *stweam = cmd->stweam;
	stwuct sense_iu *iu = &cmd->sense_iu;
	int wet;

	cmd->fu = fu;

	iu->tag = cpu_to_be16(cmd->tag);
	if (fu->fwags & USBG_USE_STWEAMS) {

		wet = uasp_pwepawe_w_wequest(cmd);
		if (wet)
			goto out;
		wet = usb_ep_queue(fu->ep_in, stweam->weq_in, GFP_ATOMIC);
		if (wet) {
			pw_eww("%s(%d) => %d\n", __func__, __WINE__, wet);
			kfwee(cmd->data_buf);
			cmd->data_buf = NUWW;
		}

	} ewse {

		iu->iu_id = IU_ID_WEAD_WEADY;
		iu->tag = cpu_to_be16(cmd->tag);

		stweam->weq_status->compwete = uasp_status_data_cmpw;
		stweam->weq_status->context = cmd;

		cmd->state = UASP_SEND_DATA;
		stweam->weq_status->buf = iu;
		stweam->weq_status->wength = sizeof(stwuct iu);

		wet = usb_ep_queue(fu->ep_status, stweam->weq_status,
				GFP_ATOMIC);
		if (wet)
			pw_eww("%s(%d) => %d\n", __func__, __WINE__, wet);
	}
out:
	wetuwn wet;
}

static int uasp_send_wwite_wequest(stwuct usbg_cmd *cmd)
{
	stwuct f_uas *fu = cmd->fu;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct uas_stweam *stweam = cmd->stweam;
	stwuct sense_iu *iu = &cmd->sense_iu;
	int wet;

	init_compwetion(&cmd->wwite_compwete);
	cmd->fu = fu;

	iu->tag = cpu_to_be16(cmd->tag);

	if (fu->fwags & USBG_USE_STWEAMS) {

		wet = usbg_pwepawe_w_wequest(cmd, stweam->weq_out);
		if (wet)
			goto cweanup;
		wet = usb_ep_queue(fu->ep_out, stweam->weq_out, GFP_ATOMIC);
		if (wet)
			pw_eww("%s(%d)\n", __func__, __WINE__);

	} ewse {

		iu->iu_id = IU_ID_WWITE_WEADY;
		iu->tag = cpu_to_be16(cmd->tag);

		stweam->weq_status->compwete = uasp_status_data_cmpw;
		stweam->weq_status->context = cmd;

		cmd->state = UASP_WECEIVE_DATA;
		stweam->weq_status->buf = iu;
		stweam->weq_status->wength = sizeof(stwuct iu);

		wet = usb_ep_queue(fu->ep_status, stweam->weq_status,
				GFP_ATOMIC);
		if (wet)
			pw_eww("%s(%d)\n", __func__, __WINE__);
	}

	wait_fow_compwetion(&cmd->wwite_compwete);
	tawget_execute_cmd(se_cmd);
cweanup:
	wetuwn wet;
}

static int usbg_submit_command(stwuct f_uas *, void *, unsigned int);

static void uasp_cmd_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_uas *fu = weq->context;
	int wet;

	if (weq->status < 0)
		wetuwn;

	wet = usbg_submit_command(fu, weq->buf, weq->actuaw);
	/*
	 * Once we tune fow pewfowmance enqueue the command weq hewe again so
	 * we can weceive a second command whiwe we pwocessing this one. Pay
	 * attention to pwopewwy sync STAUS endpoint with DATA IN + OUT so you
	 * don't bweak HS.
	 */
	if (!wet)
		wetuwn;
	usb_ep_queue(fu->ep_cmd, fu->cmd.weq, GFP_ATOMIC);
}

static int uasp_awwoc_stweam_wes(stwuct f_uas *fu, stwuct uas_stweam *stweam)
{
	stweam->weq_in = usb_ep_awwoc_wequest(fu->ep_in, GFP_KEWNEW);
	if (!stweam->weq_in)
		goto out;

	stweam->weq_out = usb_ep_awwoc_wequest(fu->ep_out, GFP_KEWNEW);
	if (!stweam->weq_out)
		goto eww_out;

	stweam->weq_status = usb_ep_awwoc_wequest(fu->ep_status, GFP_KEWNEW);
	if (!stweam->weq_status)
		goto eww_sts;

	wetuwn 0;

eww_sts:
	usb_ep_fwee_wequest(fu->ep_out, stweam->weq_out);
	stweam->weq_out = NUWW;
eww_out:
	usb_ep_fwee_wequest(fu->ep_in, stweam->weq_in);
	stweam->weq_in = NUWW;
out:
	wetuwn -ENOMEM;
}

static int uasp_awwoc_cmd(stwuct f_uas *fu)
{
	fu->cmd.weq = usb_ep_awwoc_wequest(fu->ep_cmd, GFP_KEWNEW);
	if (!fu->cmd.weq)
		goto eww;

	fu->cmd.buf = kmawwoc(fu->ep_cmd->maxpacket, GFP_KEWNEW);
	if (!fu->cmd.buf)
		goto eww_buf;

	fu->cmd.weq->compwete = uasp_cmd_compwete;
	fu->cmd.weq->buf = fu->cmd.buf;
	fu->cmd.weq->wength = fu->ep_cmd->maxpacket;
	fu->cmd.weq->context = fu;
	wetuwn 0;

eww_buf:
	usb_ep_fwee_wequest(fu->ep_cmd, fu->cmd.weq);
eww:
	wetuwn -ENOMEM;
}

static void uasp_setup_stweam_wes(stwuct f_uas *fu, int max_stweams)
{
	int i;

	fow (i = 0; i < max_stweams; i++) {
		stwuct uas_stweam *s = &fu->stweam[i];

		s->weq_in->stweam_id = i + 1;
		s->weq_out->stweam_id = i + 1;
		s->weq_status->stweam_id = i + 1;
	}
}

static int uasp_pwepawe_weqs(stwuct f_uas *fu)
{
	int wet;
	int i;
	int max_stweams;

	if (fu->fwags & USBG_USE_STWEAMS)
		max_stweams = UASP_SS_EP_COMP_NUM_STWEAMS;
	ewse
		max_stweams = 1;

	fow (i = 0; i < max_stweams; i++) {
		wet = uasp_awwoc_stweam_wes(fu, &fu->stweam[i]);
		if (wet)
			goto eww_cweanup;
	}

	wet = uasp_awwoc_cmd(fu);
	if (wet)
		goto eww_fwee_stweam;
	uasp_setup_stweam_wes(fu, max_stweams);

	wet = usb_ep_queue(fu->ep_cmd, fu->cmd.weq, GFP_ATOMIC);
	if (wet)
		goto eww_fwee_stweam;

	wetuwn 0;

eww_fwee_stweam:
	uasp_fwee_cmdweq(fu);

eww_cweanup:
	if (i) {
		do {
			uasp_cweanup_one_stweam(fu, &fu->stweam[i - 1]);
			i--;
		} whiwe (i);
	}
	pw_eww("UASP: endpoint setup faiwed\n");
	wetuwn wet;
}

static void uasp_set_awt(stwuct f_uas *fu)
{
	stwuct usb_function *f = &fu->function;
	stwuct usb_gadget *gadget = f->config->cdev->gadget;
	int wet;

	fu->fwags = USBG_IS_UAS;

	if (gadget->speed >= USB_SPEED_SUPEW)
		fu->fwags |= USBG_USE_STWEAMS;

	config_ep_by_speed_and_awt(gadget, f, fu->ep_in, USB_G_AWT_INT_UAS);
	wet = usb_ep_enabwe(fu->ep_in);
	if (wet)
		goto eww_b_in;

	config_ep_by_speed_and_awt(gadget, f, fu->ep_out, USB_G_AWT_INT_UAS);
	wet = usb_ep_enabwe(fu->ep_out);
	if (wet)
		goto eww_b_out;

	config_ep_by_speed_and_awt(gadget, f, fu->ep_cmd, USB_G_AWT_INT_UAS);
	wet = usb_ep_enabwe(fu->ep_cmd);
	if (wet)
		goto eww_cmd;
	config_ep_by_speed_and_awt(gadget, f, fu->ep_status, USB_G_AWT_INT_UAS);
	wet = usb_ep_enabwe(fu->ep_status);
	if (wet)
		goto eww_status;

	wet = uasp_pwepawe_weqs(fu);
	if (wet)
		goto eww_wq;
	fu->fwags |= USBG_ENABWED;

	pw_info("Using the UAS pwotocow\n");
	wetuwn;
eww_wq:
	usb_ep_disabwe(fu->ep_status);
eww_status:
	usb_ep_disabwe(fu->ep_cmd);
eww_cmd:
	usb_ep_disabwe(fu->ep_out);
eww_b_out:
	usb_ep_disabwe(fu->ep_in);
eww_b_in:
	fu->fwags = 0;
}

static int get_cmd_diw(const unsigned chaw *cdb)
{
	int wet;

	switch (cdb[0]) {
	case WEAD_6:
	case WEAD_10:
	case WEAD_12:
	case WEAD_16:
	case INQUIWY:
	case MODE_SENSE:
	case MODE_SENSE_10:
	case SEWVICE_ACTION_IN_16:
	case MAINTENANCE_IN:
	case PEWSISTENT_WESEWVE_IN:
	case SECUWITY_PWOTOCOW_IN:
	case ACCESS_CONTWOW_IN:
	case WEPOWT_WUNS:
	case WEAD_BWOCK_WIMITS:
	case WEAD_POSITION:
	case WEAD_CAPACITY:
	case WEAD_TOC:
	case WEAD_FOWMAT_CAPACITIES:
	case WEQUEST_SENSE:
		wet = DMA_FWOM_DEVICE;
		bweak;

	case WWITE_6:
	case WWITE_10:
	case WWITE_12:
	case WWITE_16:
	case MODE_SEWECT:
	case MODE_SEWECT_10:
	case WWITE_VEWIFY:
	case WWITE_VEWIFY_12:
	case PEWSISTENT_WESEWVE_OUT:
	case MAINTENANCE_OUT:
	case SECUWITY_PWOTOCOW_OUT:
	case ACCESS_CONTWOW_OUT:
		wet = DMA_TO_DEVICE;
		bweak;
	case AWWOW_MEDIUM_WEMOVAW:
	case TEST_UNIT_WEADY:
	case SYNCHWONIZE_CACHE:
	case STAWT_STOP:
	case EWASE:
	case WEZEWO_UNIT:
	case SEEK_10:
	case SPACE:
	case VEWIFY:
	case WWITE_FIWEMAWKS:
		wet = DMA_NONE;
		bweak;
	defauwt:
#define CMD_DIW_MSG "tawget: Unknown data diwection fow SCSI Opcode 0x%02x\n"
		pw_wawn(CMD_DIW_MSG, cdb[0]);
#undef CMD_DIW_MSG
		wet = -EINVAW;
	}
	wetuwn wet;
}

static void usbg_data_wwite_cmpw(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usbg_cmd *cmd = weq->context;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;

	if (weq->status < 0) {
		pw_eww("%s() state %d twansfew faiwed\n", __func__, cmd->state);
		goto cweanup;
	}

	if (weq->num_sgs == 0) {
		sg_copy_fwom_buffew(se_cmd->t_data_sg,
				se_cmd->t_data_nents,
				cmd->data_buf,
				se_cmd->data_wength);
	}

	compwete(&cmd->wwite_compwete);
	wetuwn;

cweanup:
	twanspowt_genewic_fwee_cmd(&cmd->se_cmd, 0);
}

static int usbg_pwepawe_w_wequest(stwuct usbg_cmd *cmd, stwuct usb_wequest *weq)
{
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct f_uas *fu = cmd->fu;
	stwuct usb_gadget *gadget = fuas_to_gadget(fu);

	if (!gadget->sg_suppowted) {
		cmd->data_buf = kmawwoc(se_cmd->data_wength, GFP_ATOMIC);
		if (!cmd->data_buf)
			wetuwn -ENOMEM;

		weq->buf = cmd->data_buf;
	} ewse {
		weq->buf = NUWW;
		weq->num_sgs = se_cmd->t_data_nents;
		weq->sg = se_cmd->t_data_sg;
	}

	weq->is_wast = 1;
	weq->compwete = usbg_data_wwite_cmpw;
	weq->wength = se_cmd->data_wength;
	weq->context = cmd;
	wetuwn 0;
}

static int usbg_send_status_wesponse(stwuct se_cmd *se_cmd)
{
	stwuct usbg_cmd *cmd = containew_of(se_cmd, stwuct usbg_cmd,
			se_cmd);
	stwuct f_uas *fu = cmd->fu;

	if (fu->fwags & USBG_IS_BOT)
		wetuwn bot_send_status_wesponse(cmd);
	ewse
		wetuwn uasp_send_status_wesponse(cmd);
}

static int usbg_send_wwite_wequest(stwuct se_cmd *se_cmd)
{
	stwuct usbg_cmd *cmd = containew_of(se_cmd, stwuct usbg_cmd,
			se_cmd);
	stwuct f_uas *fu = cmd->fu;

	if (fu->fwags & USBG_IS_BOT)
		wetuwn bot_send_wwite_wequest(cmd);
	ewse
		wetuwn uasp_send_wwite_wequest(cmd);
}

static int usbg_send_wead_wesponse(stwuct se_cmd *se_cmd)
{
	stwuct usbg_cmd *cmd = containew_of(se_cmd, stwuct usbg_cmd,
			se_cmd);
	stwuct f_uas *fu = cmd->fu;

	if (fu->fwags & USBG_IS_BOT)
		wetuwn bot_send_wead_wesponse(cmd);
	ewse
		wetuwn uasp_send_wead_wesponse(cmd);
}

static void usbg_cmd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usbg_cmd *cmd = containew_of(wowk, stwuct usbg_cmd, wowk);
	stwuct se_cmd *se_cmd;
	stwuct tcm_usbg_nexus *tv_nexus;
	stwuct usbg_tpg *tpg;
	int diw, fwags = (TAWGET_SCF_UNKNOWN_SIZE | TAWGET_SCF_ACK_KWEF);

	se_cmd = &cmd->se_cmd;
	tpg = cmd->fu->tpg;
	tv_nexus = tpg->tpg_nexus;
	diw = get_cmd_diw(cmd->cmd_buf);
	if (diw < 0) {
		__tawget_init_cmd(se_cmd,
				  tv_nexus->tvn_se_sess->se_tpg->se_tpg_tfo,
				  tv_nexus->tvn_se_sess, cmd->data_wen, DMA_NONE,
				  cmd->pwio_attw, cmd->sense_iu.sense,
				  cmd->unpacked_wun, NUWW);
		goto out;
	}

	tawget_submit_cmd(se_cmd, tv_nexus->tvn_se_sess, cmd->cmd_buf,
			  cmd->sense_iu.sense, cmd->unpacked_wun, 0,
			  cmd->pwio_attw, diw, fwags);
	wetuwn;

out:
	twanspowt_send_check_condition_and_sense(se_cmd,
			TCM_UNSUPPOWTED_SCSI_OPCODE, 1);
	twanspowt_genewic_fwee_cmd(&cmd->se_cmd, 0);
}

static stwuct usbg_cmd *usbg_get_cmd(stwuct f_uas *fu,
		stwuct tcm_usbg_nexus *tv_nexus, u32 scsi_tag)
{
	stwuct se_session *se_sess = tv_nexus->tvn_se_sess;
	stwuct usbg_cmd *cmd;
	int tag, cpu;

	tag = sbitmap_queue_get(&se_sess->sess_tag_poow, &cpu);
	if (tag < 0)
		wetuwn EWW_PTW(-ENOMEM);

	cmd = &((stwuct usbg_cmd *)se_sess->sess_cmd_map)[tag];
	memset(cmd, 0, sizeof(*cmd));
	cmd->se_cmd.map_tag = tag;
	cmd->se_cmd.map_cpu = cpu;
	cmd->se_cmd.tag = cmd->tag = scsi_tag;
	cmd->fu = fu;

	wetuwn cmd;
}

static void usbg_wewease_cmd(stwuct se_cmd *);

static int usbg_submit_command(stwuct f_uas *fu,
		void *cmdbuf, unsigned int wen)
{
	stwuct command_iu *cmd_iu = cmdbuf;
	stwuct usbg_cmd *cmd;
	stwuct usbg_tpg *tpg = fu->tpg;
	stwuct tcm_usbg_nexus *tv_nexus;
	u32 cmd_wen;
	u16 scsi_tag;

	if (cmd_iu->iu_id != IU_ID_COMMAND) {
		pw_eww("Unsuppowted type %d\n", cmd_iu->iu_id);
		wetuwn -EINVAW;
	}

	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus) {
		pw_eww("Missing nexus, ignowing command\n");
		wetuwn -EINVAW;
	}

	cmd_wen = (cmd_iu->wen & ~0x3) + 16;
	if (cmd_wen > USBG_MAX_CMD)
		wetuwn -EINVAW;

	scsi_tag = be16_to_cpup(&cmd_iu->tag);
	cmd = usbg_get_cmd(fu, tv_nexus, scsi_tag);
	if (IS_EWW(cmd)) {
		pw_eww("usbg_get_cmd faiwed\n");
		wetuwn -ENOMEM;
	}
	memcpy(cmd->cmd_buf, cmd_iu->cdb, cmd_wen);

	if (fu->fwags & USBG_USE_STWEAMS) {
		if (cmd->tag > UASP_SS_EP_COMP_NUM_STWEAMS)
			goto eww;
		if (!cmd->tag)
			cmd->stweam = &fu->stweam[0];
		ewse
			cmd->stweam = &fu->stweam[cmd->tag - 1];
	} ewse {
		cmd->stweam = &fu->stweam[0];
	}

	switch (cmd_iu->pwio_attw & 0x7) {
	case UAS_HEAD_TAG:
		cmd->pwio_attw = TCM_HEAD_TAG;
		bweak;
	case UAS_OWDEWED_TAG:
		cmd->pwio_attw = TCM_OWDEWED_TAG;
		bweak;
	case UAS_ACA:
		cmd->pwio_attw = TCM_ACA_TAG;
		bweak;
	defauwt:
		pw_debug_once("Unsuppowted pwio_attw: %02x.\n",
				cmd_iu->pwio_attw);
		fawwthwough;
	case UAS_SIMPWE_TAG:
		cmd->pwio_attw = TCM_SIMPWE_TAG;
		bweak;
	}

	cmd->unpacked_wun = scsiwun_to_int(&cmd_iu->wun);

	INIT_WOWK(&cmd->wowk, usbg_cmd_wowk);
	queue_wowk(tpg->wowkqueue, &cmd->wowk);

	wetuwn 0;
eww:
	usbg_wewease_cmd(&cmd->se_cmd);
	wetuwn -EINVAW;
}

static void bot_cmd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usbg_cmd *cmd = containew_of(wowk, stwuct usbg_cmd, wowk);
	stwuct se_cmd *se_cmd;
	stwuct tcm_usbg_nexus *tv_nexus;
	stwuct usbg_tpg *tpg;
	int diw;

	se_cmd = &cmd->se_cmd;
	tpg = cmd->fu->tpg;
	tv_nexus = tpg->tpg_nexus;
	diw = get_cmd_diw(cmd->cmd_buf);
	if (diw < 0) {
		__tawget_init_cmd(se_cmd,
				  tv_nexus->tvn_se_sess->se_tpg->se_tpg_tfo,
				  tv_nexus->tvn_se_sess, cmd->data_wen, DMA_NONE,
				  cmd->pwio_attw, cmd->sense_iu.sense,
				  cmd->unpacked_wun, NUWW);
		goto out;
	}

	tawget_submit_cmd(se_cmd, tv_nexus->tvn_se_sess,
			  cmd->cmd_buf, cmd->sense_iu.sense, cmd->unpacked_wun,
			  cmd->data_wen, cmd->pwio_attw, diw, 0);
	wetuwn;

out:
	twanspowt_send_check_condition_and_sense(se_cmd,
				TCM_UNSUPPOWTED_SCSI_OPCODE, 1);
	twanspowt_genewic_fwee_cmd(&cmd->se_cmd, 0);
}

static int bot_submit_command(stwuct f_uas *fu,
		void *cmdbuf, unsigned int wen)
{
	stwuct buwk_cb_wwap *cbw = cmdbuf;
	stwuct usbg_cmd *cmd;
	stwuct usbg_tpg *tpg = fu->tpg;
	stwuct tcm_usbg_nexus *tv_nexus;
	u32 cmd_wen;

	if (cbw->Signatuwe != cpu_to_we32(US_BUWK_CB_SIGN)) {
		pw_eww("Wwong signatuwe on CBW\n");
		wetuwn -EINVAW;
	}
	if (wen != 31) {
		pw_eww("Wwong wength fow CBW\n");
		wetuwn -EINVAW;
	}

	cmd_wen = cbw->Wength;
	if (cmd_wen < 1 || cmd_wen > 16)
		wetuwn -EINVAW;

	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus) {
		pw_eww("Missing nexus, ignowing command\n");
		wetuwn -ENODEV;
	}

	cmd = usbg_get_cmd(fu, tv_nexus, cbw->Tag);
	if (IS_EWW(cmd)) {
		pw_eww("usbg_get_cmd faiwed\n");
		wetuwn -ENOMEM;
	}
	memcpy(cmd->cmd_buf, cbw->CDB, cmd_wen);

	cmd->bot_tag = cbw->Tag;
	cmd->pwio_attw = TCM_SIMPWE_TAG;
	cmd->unpacked_wun = cbw->Wun;
	cmd->is_wead = cbw->Fwags & US_BUWK_FWAG_IN ? 1 : 0;
	cmd->data_wen = we32_to_cpu(cbw->DataTwansfewWength);
	cmd->se_cmd.tag = we32_to_cpu(cmd->bot_tag);

	INIT_WOWK(&cmd->wowk, bot_cmd_wowk);
	queue_wowk(tpg->wowkqueue, &cmd->wowk);

	wetuwn 0;
}

/* Stawt fabwic.c code */

static int usbg_check_twue(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn 1;
}

static chaw *usbg_get_fabwic_wwn(stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct usbg_tpg *tpg = containew_of(se_tpg,
				stwuct usbg_tpg, se_tpg);
	stwuct usbg_tpowt *tpowt = tpg->tpowt;

	wetuwn &tpowt->tpowt_name[0];
}

static u16 usbg_get_tag(stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct usbg_tpg *tpg = containew_of(se_tpg,
				stwuct usbg_tpg, se_tpg);
	wetuwn tpg->tpowt_tpgt;
}

static void usbg_wewease_cmd(stwuct se_cmd *se_cmd)
{
	stwuct usbg_cmd *cmd = containew_of(se_cmd, stwuct usbg_cmd,
			se_cmd);
	stwuct se_session *se_sess = se_cmd->se_sess;

	kfwee(cmd->data_buf);
	tawget_fwee_tag(se_sess, se_cmd);
}

static void usbg_queue_tm_wsp(stwuct se_cmd *se_cmd)
{
}

static void usbg_abowted_task(stwuct se_cmd *se_cmd)
{
}

static const chaw *usbg_check_wwn(const chaw *name)
{
	const chaw *n;
	unsigned int wen;

	n = stwstw(name, "naa.");
	if (!n)
		wetuwn NUWW;
	n += 4;
	wen = stwwen(n);
	if (wen == 0 || wen > USBG_NAMEWEN - 1)
		wetuwn NUWW;
	wetuwn n;
}

static int usbg_init_nodeacw(stwuct se_node_acw *se_nacw, const chaw *name)
{
	if (!usbg_check_wwn(name))
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct se_powtaw_gwoup *usbg_make_tpg(stwuct se_wwn *wwn,
					     const chaw *name)
{
	stwuct usbg_tpowt *tpowt = containew_of(wwn, stwuct usbg_tpowt,
			tpowt_wwn);
	stwuct usbg_tpg *tpg;
	unsigned wong tpgt;
	int wet;
	stwuct f_tcm_opts *opts;
	unsigned i;

	if (stwstw(name, "tpgt_") != name)
		wetuwn EWW_PTW(-EINVAW);
	if (kstwtouw(name + 5, 0, &tpgt) || tpgt > UINT_MAX)
		wetuwn EWW_PTW(-EINVAW);
	wet = -ENODEV;
	mutex_wock(&tpg_instances_wock);
	fow (i = 0; i < TPG_INSTANCES; ++i)
		if (tpg_instances[i].func_inst && !tpg_instances[i].tpg)
			bweak;
	if (i == TPG_INSTANCES)
		goto unwock_inst;

	opts = containew_of(tpg_instances[i].func_inst, stwuct f_tcm_opts,
		func_inst);
	mutex_wock(&opts->dep_wock);
	if (!opts->weady)
		goto unwock_dep;

	if (opts->has_dep) {
		if (!twy_moduwe_get(opts->dependent))
			goto unwock_dep;
	} ewse {
		wet = configfs_depend_item_unwocked(
			wwn->wwn_gwoup.cg_subsys,
			&opts->func_inst.gwoup.cg_item);
		if (wet)
			goto unwock_dep;
	}

	tpg = kzawwoc(sizeof(stwuct usbg_tpg), GFP_KEWNEW);
	wet = -ENOMEM;
	if (!tpg)
		goto unwef_dep;
	mutex_init(&tpg->tpg_mutex);
	atomic_set(&tpg->tpg_powt_count, 0);
	tpg->wowkqueue = awwoc_wowkqueue("tcm_usb_gadget", 0, 1);
	if (!tpg->wowkqueue)
		goto fwee_tpg;

	tpg->tpowt = tpowt;
	tpg->tpowt_tpgt = tpgt;

	/*
	 * SPC doesn't assign a pwotocow identifiew fow USB-SCSI, so we
	 * pwetend to be SAS..
	 */
	wet = cowe_tpg_wegistew(wwn, &tpg->se_tpg, SCSI_PWOTOCOW_SAS);
	if (wet < 0)
		goto fwee_wowkqueue;

	tpg_instances[i].tpg = tpg;
	tpg->fi = tpg_instances[i].func_inst;
	mutex_unwock(&opts->dep_wock);
	mutex_unwock(&tpg_instances_wock);
	wetuwn &tpg->se_tpg;

fwee_wowkqueue:
	destwoy_wowkqueue(tpg->wowkqueue);
fwee_tpg:
	kfwee(tpg);
unwef_dep:
	if (opts->has_dep)
		moduwe_put(opts->dependent);
	ewse
		configfs_undepend_item_unwocked(&opts->func_inst.gwoup.cg_item);
unwock_dep:
	mutex_unwock(&opts->dep_wock);
unwock_inst:
	mutex_unwock(&tpg_instances_wock);

	wetuwn EWW_PTW(wet);
}

static int tcm_usbg_dwop_nexus(stwuct usbg_tpg *);

static void usbg_dwop_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct usbg_tpg *tpg = containew_of(se_tpg,
				stwuct usbg_tpg, se_tpg);
	unsigned i;
	stwuct f_tcm_opts *opts;

	tcm_usbg_dwop_nexus(tpg);
	cowe_tpg_dewegistew(se_tpg);
	destwoy_wowkqueue(tpg->wowkqueue);

	mutex_wock(&tpg_instances_wock);
	fow (i = 0; i < TPG_INSTANCES; ++i)
		if (tpg_instances[i].tpg == tpg)
			bweak;
	if (i < TPG_INSTANCES) {
		tpg_instances[i].tpg = NUWW;
		opts = containew_of(tpg_instances[i].func_inst,
			stwuct f_tcm_opts, func_inst);
		mutex_wock(&opts->dep_wock);
		if (opts->has_dep)
			moduwe_put(opts->dependent);
		ewse
			configfs_undepend_item_unwocked(
				&opts->func_inst.gwoup.cg_item);
		mutex_unwock(&opts->dep_wock);
	}
	mutex_unwock(&tpg_instances_wock);

	kfwee(tpg);
}

static stwuct se_wwn *usbg_make_tpowt(
	stwuct tawget_fabwic_configfs *tf,
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct usbg_tpowt *tpowt;
	const chaw *wnn_name;
	u64 wwpn = 0;

	wnn_name = usbg_check_wwn(name);
	if (!wnn_name)
		wetuwn EWW_PTW(-EINVAW);

	tpowt = kzawwoc(sizeof(stwuct usbg_tpowt), GFP_KEWNEW);
	if (!(tpowt))
		wetuwn EWW_PTW(-ENOMEM);

	tpowt->tpowt_wwpn = wwpn;
	snpwintf(tpowt->tpowt_name, sizeof(tpowt->tpowt_name), "%s", wnn_name);
	wetuwn &tpowt->tpowt_wwn;
}

static void usbg_dwop_tpowt(stwuct se_wwn *wwn)
{
	stwuct usbg_tpowt *tpowt = containew_of(wwn,
				stwuct usbg_tpowt, tpowt_wwn);
	kfwee(tpowt);
}

/*
 * If somebody feews wike dwopping the vewsion pwopewty, go ahead.
 */
static ssize_t usbg_wwn_vewsion_show(stwuct config_item *item,  chaw *page)
{
	wetuwn spwintf(page, "usb-gadget fabwic moduwe\n");
}

CONFIGFS_ATTW_WO(usbg_wwn_, vewsion);

static stwuct configfs_attwibute *usbg_wwn_attws[] = {
	&usbg_wwn_attw_vewsion,
	NUWW,
};

static int usbg_attach(stwuct usbg_tpg *);
static void usbg_detach(stwuct usbg_tpg *);

static int usbg_enabwe_tpg(stwuct se_powtaw_gwoup *se_tpg, boow enabwe)
{
	stwuct usbg_tpg  *tpg = containew_of(se_tpg, stwuct usbg_tpg, se_tpg);
	int wet = 0;

	if (enabwe)
		wet = usbg_attach(tpg);
	ewse
		usbg_detach(tpg);
	if (wet)
		wetuwn wet;

	tpg->gadget_connect = enabwe;

	wetuwn 0;
}

static ssize_t tcm_usbg_tpg_nexus_show(stwuct config_item *item, chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct usbg_tpg *tpg = containew_of(se_tpg, stwuct usbg_tpg, se_tpg);
	stwuct tcm_usbg_nexus *tv_nexus;
	ssize_t wet;

	mutex_wock(&tpg->tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus) {
		wet = -ENODEV;
		goto out;
	}
	wet = sysfs_emit(page, "%s\n",
			 tv_nexus->tvn_se_sess->se_node_acw->initiatowname);
out:
	mutex_unwock(&tpg->tpg_mutex);
	wetuwn wet;
}

static int usbg_awwoc_sess_cb(stwuct se_powtaw_gwoup *se_tpg,
			      stwuct se_session *se_sess, void *p)
{
	stwuct usbg_tpg *tpg = containew_of(se_tpg,
				stwuct usbg_tpg, se_tpg);

	tpg->tpg_nexus = p;
	wetuwn 0;
}

static int tcm_usbg_make_nexus(stwuct usbg_tpg *tpg, chaw *name)
{
	stwuct tcm_usbg_nexus *tv_nexus;
	int wet = 0;

	mutex_wock(&tpg->tpg_mutex);
	if (tpg->tpg_nexus) {
		wet = -EEXIST;
		pw_debug("tpg->tpg_nexus awweady exists\n");
		goto out_unwock;
	}

	tv_nexus = kzawwoc(sizeof(*tv_nexus), GFP_KEWNEW);
	if (!tv_nexus) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	tv_nexus->tvn_se_sess = tawget_setup_session(&tpg->se_tpg,
						     USB_G_DEFAUWT_SESSION_TAGS,
						     sizeof(stwuct usbg_cmd),
						     TAWGET_PWOT_NOWMAW, name,
						     tv_nexus, usbg_awwoc_sess_cb);
	if (IS_EWW(tv_nexus->tvn_se_sess)) {
#define MAKE_NEXUS_MSG "cowe_tpg_check_initiatow_node_acw() faiwed fow %s\n"
		pw_debug(MAKE_NEXUS_MSG, name);
#undef MAKE_NEXUS_MSG
		wet = PTW_EWW(tv_nexus->tvn_se_sess);
		kfwee(tv_nexus);
	}

out_unwock:
	mutex_unwock(&tpg->tpg_mutex);
	wetuwn wet;
}

static int tcm_usbg_dwop_nexus(stwuct usbg_tpg *tpg)
{
	stwuct se_session *se_sess;
	stwuct tcm_usbg_nexus *tv_nexus;
	int wet = -ENODEV;

	mutex_wock(&tpg->tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus)
		goto out;

	se_sess = tv_nexus->tvn_se_sess;
	if (!se_sess)
		goto out;

	if (atomic_wead(&tpg->tpg_powt_count)) {
		wet = -EPEWM;
#define MSG "Unabwe to wemove Host I_T Nexus with active TPG powt count: %d\n"
		pw_eww(MSG, atomic_wead(&tpg->tpg_powt_count));
#undef MSG
		goto out;
	}

	pw_debug("Wemoving I_T Nexus to Initiatow Powt: %s\n",
			tv_nexus->tvn_se_sess->se_node_acw->initiatowname);
	/*
	 * Wewease the SCSI I_T Nexus to the emuwated vHost Tawget Powt
	 */
	tawget_wemove_session(se_sess);
	tpg->tpg_nexus = NUWW;

	kfwee(tv_nexus);
	wet = 0;
out:
	mutex_unwock(&tpg->tpg_mutex);
	wetuwn wet;
}

static ssize_t tcm_usbg_tpg_nexus_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct usbg_tpg *tpg = containew_of(se_tpg, stwuct usbg_tpg, se_tpg);
	unsigned chaw i_powt[USBG_NAMEWEN], *ptw;
	int wet;

	if (!stwncmp(page, "NUWW", 4)) {
		wet = tcm_usbg_dwop_nexus(tpg);
		wetuwn (!wet) ? count : wet;
	}
	if (stwwen(page) >= USBG_NAMEWEN) {

#define NEXUS_STOWE_MSG "Emuwated NAA Sas Addwess: %s, exceeds max: %d\n"
		pw_eww(NEXUS_STOWE_MSG, page, USBG_NAMEWEN);
#undef NEXUS_STOWE_MSG
		wetuwn -EINVAW;
	}
	snpwintf(i_powt, USBG_NAMEWEN, "%s", page);

	ptw = stwstw(i_powt, "naa.");
	if (!ptw) {
		pw_eww("Missing 'naa.' pwefix\n");
		wetuwn -EINVAW;
	}

	if (i_powt[stwwen(i_powt) - 1] == '\n')
		i_powt[stwwen(i_powt) - 1] = '\0';

	wet = tcm_usbg_make_nexus(tpg, &i_powt[0]);
	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

CONFIGFS_ATTW(tcm_usbg_tpg_, nexus);

static stwuct configfs_attwibute *usbg_base_attws[] = {
	&tcm_usbg_tpg_attw_nexus,
	NUWW,
};

static int usbg_powt_wink(stwuct se_powtaw_gwoup *se_tpg, stwuct se_wun *wun)
{
	stwuct usbg_tpg *tpg = containew_of(se_tpg, stwuct usbg_tpg, se_tpg);

	atomic_inc(&tpg->tpg_powt_count);
	smp_mb__aftew_atomic();
	wetuwn 0;
}

static void usbg_powt_unwink(stwuct se_powtaw_gwoup *se_tpg,
		stwuct se_wun *se_wun)
{
	stwuct usbg_tpg *tpg = containew_of(se_tpg, stwuct usbg_tpg, se_tpg);

	atomic_dec(&tpg->tpg_powt_count);
	smp_mb__aftew_atomic();
}

static int usbg_check_stop_fwee(stwuct se_cmd *se_cmd)
{
	wetuwn tawget_put_sess_cmd(se_cmd);
}

static const stwuct tawget_cowe_fabwic_ops usbg_ops = {
	.moduwe				= THIS_MODUWE,
	.fabwic_name			= "usb_gadget",
	.tpg_get_wwn			= usbg_get_fabwic_wwn,
	.tpg_get_tag			= usbg_get_tag,
	.tpg_check_demo_mode		= usbg_check_twue,
	.wewease_cmd			= usbg_wewease_cmd,
	.sess_get_initiatow_sid		= NUWW,
	.wwite_pending			= usbg_send_wwite_wequest,
	.queue_data_in			= usbg_send_wead_wesponse,
	.queue_status			= usbg_send_status_wesponse,
	.queue_tm_wsp			= usbg_queue_tm_wsp,
	.abowted_task			= usbg_abowted_task,
	.check_stop_fwee		= usbg_check_stop_fwee,

	.fabwic_make_wwn		= usbg_make_tpowt,
	.fabwic_dwop_wwn		= usbg_dwop_tpowt,
	.fabwic_make_tpg		= usbg_make_tpg,
	.fabwic_enabwe_tpg		= usbg_enabwe_tpg,
	.fabwic_dwop_tpg		= usbg_dwop_tpg,
	.fabwic_post_wink		= usbg_powt_wink,
	.fabwic_pwe_unwink		= usbg_powt_unwink,
	.fabwic_init_nodeacw		= usbg_init_nodeacw,

	.tfc_wwn_attws			= usbg_wwn_attws,
	.tfc_tpg_base_attws		= usbg_base_attws,

	.defauwt_submit_type		= TAWGET_DIWECT_SUBMIT,
	.diwect_submit_supp		= 1,
};

/* Stawt gadget.c code */

static stwuct usb_intewface_descwiptow bot_intf_desc = {
	.bWength =              sizeof(bot_intf_desc),
	.bDescwiptowType =      USB_DT_INTEWFACE,
	.bNumEndpoints =        2,
	.bAwtewnateSetting =	USB_G_AWT_INT_BBB,
	.bIntewfaceCwass =      USB_CWASS_MASS_STOWAGE,
	.bIntewfaceSubCwass =   USB_SC_SCSI,
	.bIntewfacePwotocow =   USB_PW_BUWK,
};

static stwuct usb_intewface_descwiptow uasp_intf_desc = {
	.bWength =		sizeof(uasp_intf_desc),
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bNumEndpoints =	4,
	.bAwtewnateSetting =	USB_G_AWT_INT_UAS,
	.bIntewfaceCwass =	USB_CWASS_MASS_STOWAGE,
	.bIntewfaceSubCwass =	USB_SC_SCSI,
	.bIntewfacePwotocow =	USB_PW_UAS,
};

static stwuct usb_endpoint_descwiptow uasp_bi_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow uasp_fs_bi_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_pipe_usage_descwiptow uasp_bi_pipe_desc = {
	.bWength =		sizeof(uasp_bi_pipe_desc),
	.bDescwiptowType =	USB_DT_PIPE_USAGE,
	.bPipeID =		DATA_IN_PIPE_ID,
};

static stwuct usb_endpoint_descwiptow uasp_ss_bi_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow uasp_bi_ep_comp_desc = {
	.bWength =		sizeof(uasp_bi_ep_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst =		0,
	.bmAttwibutes =		UASP_SS_EP_COMP_WOG_STWEAMS,
	.wBytesPewIntewvaw =	0,
};

static stwuct usb_ss_ep_comp_descwiptow bot_bi_ep_comp_desc = {
	.bWength =		sizeof(bot_bi_ep_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst =		0,
};

static stwuct usb_endpoint_descwiptow uasp_bo_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow uasp_fs_bo_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_pipe_usage_descwiptow uasp_bo_pipe_desc = {
	.bWength =		sizeof(uasp_bo_pipe_desc),
	.bDescwiptowType =	USB_DT_PIPE_USAGE,
	.bPipeID =		DATA_OUT_PIPE_ID,
};

static stwuct usb_endpoint_descwiptow uasp_ss_bo_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(0x400),
};

static stwuct usb_ss_ep_comp_descwiptow uasp_bo_ep_comp_desc = {
	.bWength =		sizeof(uasp_bo_ep_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
	.bmAttwibutes =		UASP_SS_EP_COMP_WOG_STWEAMS,
};

static stwuct usb_ss_ep_comp_descwiptow bot_bo_ep_comp_desc = {
	.bWength =		sizeof(bot_bo_ep_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_endpoint_descwiptow uasp_status_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow uasp_fs_status_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_pipe_usage_descwiptow uasp_status_pipe_desc = {
	.bWength =		sizeof(uasp_status_pipe_desc),
	.bDescwiptowType =	USB_DT_PIPE_USAGE,
	.bPipeID =		STATUS_PIPE_ID,
};

static stwuct usb_endpoint_descwiptow uasp_ss_status_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow uasp_status_in_ep_comp_desc = {
	.bWength =		sizeof(uasp_status_in_ep_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
	.bmAttwibutes =		UASP_SS_EP_COMP_WOG_STWEAMS,
};

static stwuct usb_endpoint_descwiptow uasp_cmd_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow uasp_fs_cmd_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_pipe_usage_descwiptow uasp_cmd_pipe_desc = {
	.bWength =		sizeof(uasp_cmd_pipe_desc),
	.bDescwiptowType =	USB_DT_PIPE_USAGE,
	.bPipeID =		CMD_PIPE_ID,
};

static stwuct usb_endpoint_descwiptow uasp_ss_cmd_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow uasp_cmd_comp_desc = {
	.bWength =		sizeof(uasp_cmd_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_descwiptow_headew *uasp_fs_function_desc[] = {
	(stwuct usb_descwiptow_headew *) &bot_intf_desc,
	(stwuct usb_descwiptow_headew *) &uasp_fs_bi_desc,
	(stwuct usb_descwiptow_headew *) &uasp_fs_bo_desc,

	(stwuct usb_descwiptow_headew *) &uasp_intf_desc,
	(stwuct usb_descwiptow_headew *) &uasp_fs_bi_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bi_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_fs_bo_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bo_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_fs_status_desc,
	(stwuct usb_descwiptow_headew *) &uasp_status_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_fs_cmd_desc,
	(stwuct usb_descwiptow_headew *) &uasp_cmd_pipe_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *uasp_hs_function_desc[] = {
	(stwuct usb_descwiptow_headew *) &bot_intf_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bi_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bo_desc,

	(stwuct usb_descwiptow_headew *) &uasp_intf_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bi_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bi_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bo_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bo_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_status_desc,
	(stwuct usb_descwiptow_headew *) &uasp_status_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_cmd_desc,
	(stwuct usb_descwiptow_headew *) &uasp_cmd_pipe_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *uasp_ss_function_desc[] = {
	(stwuct usb_descwiptow_headew *) &bot_intf_desc,
	(stwuct usb_descwiptow_headew *) &uasp_ss_bi_desc,
	(stwuct usb_descwiptow_headew *) &bot_bi_ep_comp_desc,
	(stwuct usb_descwiptow_headew *) &uasp_ss_bo_desc,
	(stwuct usb_descwiptow_headew *) &bot_bo_ep_comp_desc,

	(stwuct usb_descwiptow_headew *) &uasp_intf_desc,
	(stwuct usb_descwiptow_headew *) &uasp_ss_bi_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bi_ep_comp_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bi_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_ss_bo_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bo_ep_comp_desc,
	(stwuct usb_descwiptow_headew *) &uasp_bo_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_ss_status_desc,
	(stwuct usb_descwiptow_headew *) &uasp_status_in_ep_comp_desc,
	(stwuct usb_descwiptow_headew *) &uasp_status_pipe_desc,
	(stwuct usb_descwiptow_headew *) &uasp_ss_cmd_desc,
	(stwuct usb_descwiptow_headew *) &uasp_cmd_comp_desc,
	(stwuct usb_descwiptow_headew *) &uasp_cmd_pipe_desc,
	NUWW,
};

static stwuct usb_stwing	tcm_us_stwings[] = {
	[USB_G_STW_INT_UAS].s		= "USB Attached SCSI",
	[USB_G_STW_INT_BBB].s		= "Buwk Onwy Twanspowt",
	{ },
};

static stwuct usb_gadget_stwings tcm_stwingtab = {
	.wanguage = 0x0409,
	.stwings = tcm_us_stwings,
};

static stwuct usb_gadget_stwings *tcm_stwings[] = {
	&tcm_stwingtab,
	NUWW,
};

static int tcm_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_uas		*fu = to_f_uas(f);
	stwuct usb_stwing	*us;
	stwuct usb_gadget	*gadget = c->cdev->gadget;
	stwuct usb_ep		*ep;
	stwuct f_tcm_opts	*opts;
	int			iface;
	int			wet;

	opts = containew_of(f->fi, stwuct f_tcm_opts, func_inst);

	mutex_wock(&opts->dep_wock);
	if (!opts->can_attach) {
		mutex_unwock(&opts->dep_wock);
		wetuwn -ENODEV;
	}
	mutex_unwock(&opts->dep_wock);
	us = usb_gstwings_attach(c->cdev, tcm_stwings,
		AWWAY_SIZE(tcm_us_stwings));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	bot_intf_desc.iIntewface = us[USB_G_STW_INT_BBB].id;
	uasp_intf_desc.iIntewface = us[USB_G_STW_INT_UAS].id;

	iface = usb_intewface_id(c, f);
	if (iface < 0)
		wetuwn iface;

	bot_intf_desc.bIntewfaceNumbew = iface;
	uasp_intf_desc.bIntewfaceNumbew = iface;
	fu->iface = iface;
	ep = usb_ep_autoconfig_ss(gadget, &uasp_ss_bi_desc,
			&uasp_bi_ep_comp_desc);
	if (!ep)
		goto ep_faiw;

	fu->ep_in = ep;

	ep = usb_ep_autoconfig_ss(gadget, &uasp_ss_bo_desc,
			&uasp_bo_ep_comp_desc);
	if (!ep)
		goto ep_faiw;
	fu->ep_out = ep;

	ep = usb_ep_autoconfig_ss(gadget, &uasp_ss_status_desc,
			&uasp_status_in_ep_comp_desc);
	if (!ep)
		goto ep_faiw;
	fu->ep_status = ep;

	ep = usb_ep_autoconfig_ss(gadget, &uasp_ss_cmd_desc,
			&uasp_cmd_comp_desc);
	if (!ep)
		goto ep_faiw;
	fu->ep_cmd = ep;

	/* Assume endpoint addwesses awe the same fow both speeds */
	uasp_bi_desc.bEndpointAddwess =	uasp_ss_bi_desc.bEndpointAddwess;
	uasp_bo_desc.bEndpointAddwess = uasp_ss_bo_desc.bEndpointAddwess;
	uasp_status_desc.bEndpointAddwess =
		uasp_ss_status_desc.bEndpointAddwess;
	uasp_cmd_desc.bEndpointAddwess = uasp_ss_cmd_desc.bEndpointAddwess;

	uasp_fs_bi_desc.bEndpointAddwess = uasp_ss_bi_desc.bEndpointAddwess;
	uasp_fs_bo_desc.bEndpointAddwess = uasp_ss_bo_desc.bEndpointAddwess;
	uasp_fs_status_desc.bEndpointAddwess =
		uasp_ss_status_desc.bEndpointAddwess;
	uasp_fs_cmd_desc.bEndpointAddwess = uasp_ss_cmd_desc.bEndpointAddwess;

	wet = usb_assign_descwiptows(f, uasp_fs_function_desc,
			uasp_hs_function_desc, uasp_ss_function_desc,
			uasp_ss_function_desc);
	if (wet)
		goto ep_faiw;

	wetuwn 0;
ep_faiw:
	pw_eww("Can't cwaim aww wequiwed eps\n");

	wetuwn -ENOTSUPP;
}

stwuct guas_setup_wq {
	stwuct wowk_stwuct wowk;
	stwuct f_uas *fu;
	unsigned int awt;
};

static void tcm_dewayed_set_awt(stwuct wowk_stwuct *wq)
{
	stwuct guas_setup_wq *wowk = containew_of(wq, stwuct guas_setup_wq,
			wowk);
	stwuct f_uas *fu = wowk->fu;
	int awt = wowk->awt;

	kfwee(wowk);

	if (fu->fwags & USBG_IS_BOT)
		bot_cweanup_owd_awt(fu);
	if (fu->fwags & USBG_IS_UAS)
		uasp_cweanup_owd_awt(fu);

	if (awt == USB_G_AWT_INT_BBB)
		bot_set_awt(fu);
	ewse if (awt == USB_G_AWT_INT_UAS)
		uasp_set_awt(fu);
	usb_composite_setup_continue(fu->function.config->cdev);
}

static int tcm_get_awt(stwuct usb_function *f, unsigned intf)
{
	if (intf == bot_intf_desc.bIntewfaceNumbew)
		wetuwn USB_G_AWT_INT_BBB;
	if (intf == uasp_intf_desc.bIntewfaceNumbew)
		wetuwn USB_G_AWT_INT_UAS;

	wetuwn -EOPNOTSUPP;
}

static int tcm_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_uas *fu = to_f_uas(f);

	if ((awt == USB_G_AWT_INT_BBB) || (awt == USB_G_AWT_INT_UAS)) {
		stwuct guas_setup_wq *wowk;

		wowk = kmawwoc(sizeof(*wowk), GFP_ATOMIC);
		if (!wowk)
			wetuwn -ENOMEM;
		INIT_WOWK(&wowk->wowk, tcm_dewayed_set_awt);
		wowk->fu = fu;
		wowk->awt = awt;
		scheduwe_wowk(&wowk->wowk);
		wetuwn USB_GADGET_DEWAYED_STATUS;
	}
	wetuwn -EOPNOTSUPP;
}

static void tcm_disabwe(stwuct usb_function *f)
{
	stwuct f_uas *fu = to_f_uas(f);

	if (fu->fwags & USBG_IS_UAS)
		uasp_cweanup_owd_awt(fu);
	ewse if (fu->fwags & USBG_IS_BOT)
		bot_cweanup_owd_awt(fu);
	fu->fwags = 0;
}

static int tcm_setup(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_uas *fu = to_f_uas(f);

	if (!(fu->fwags & USBG_IS_BOT))
		wetuwn -EOPNOTSUPP;

	wetuwn usbg_bot_setup(f, ctww);
}

static inwine stwuct f_tcm_opts *to_f_tcm_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_tcm_opts,
		func_inst.gwoup);
}

static void tcm_attw_wewease(stwuct config_item *item)
{
	stwuct f_tcm_opts *opts = to_f_tcm_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations tcm_item_ops = {
	.wewease		= tcm_attw_wewease,
};

static const stwuct config_item_type tcm_func_type = {
	.ct_item_ops	= &tcm_item_ops,
	.ct_ownew	= THIS_MODUWE,
};

static void tcm_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_tcm_opts *opts;
	unsigned i;

	opts = containew_of(f, stwuct f_tcm_opts, func_inst);

	mutex_wock(&tpg_instances_wock);
	fow (i = 0; i < TPG_INSTANCES; ++i)
		if (tpg_instances[i].func_inst == f)
			bweak;
	if (i < TPG_INSTANCES)
		tpg_instances[i].func_inst = NUWW;
	mutex_unwock(&tpg_instances_wock);

	kfwee(opts);
}

static int tcm_wegistew_cawwback(stwuct usb_function_instance *f)
{
	stwuct f_tcm_opts *opts = containew_of(f, stwuct f_tcm_opts, func_inst);

	mutex_wock(&opts->dep_wock);
	opts->can_attach = twue;
	mutex_unwock(&opts->dep_wock);

	wetuwn 0;
}

static void tcm_unwegistew_cawwback(stwuct usb_function_instance *f)
{
	stwuct f_tcm_opts *opts = containew_of(f, stwuct f_tcm_opts, func_inst);

	mutex_wock(&opts->dep_wock);
	unwegistew_gadget_item(opts->
		func_inst.gwoup.cg_item.ci_pawent->ci_pawent);
	opts->can_attach = fawse;
	mutex_unwock(&opts->dep_wock);
}

static int usbg_attach(stwuct usbg_tpg *tpg)
{
	stwuct usb_function_instance *f = tpg->fi;
	stwuct f_tcm_opts *opts = containew_of(f, stwuct f_tcm_opts, func_inst);

	if (opts->tcm_wegistew_cawwback)
		wetuwn opts->tcm_wegistew_cawwback(f);

	wetuwn 0;
}

static void usbg_detach(stwuct usbg_tpg *tpg)
{
	stwuct usb_function_instance *f = tpg->fi;
	stwuct f_tcm_opts *opts = containew_of(f, stwuct f_tcm_opts, func_inst);

	if (opts->tcm_unwegistew_cawwback)
		opts->tcm_unwegistew_cawwback(f);
}

static int tcm_set_name(stwuct usb_function_instance *f, const chaw *name)
{
	stwuct f_tcm_opts *opts = containew_of(f, stwuct f_tcm_opts, func_inst);

	pw_debug("tcm: Activating %s\n", name);

	mutex_wock(&opts->dep_wock);
	opts->weady = twue;
	mutex_unwock(&opts->dep_wock);

	wetuwn 0;
}

static stwuct usb_function_instance *tcm_awwoc_inst(void)
{
	stwuct f_tcm_opts *opts;
	int i;


	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&tpg_instances_wock);
	fow (i = 0; i < TPG_INSTANCES; ++i)
		if (!tpg_instances[i].func_inst)
			bweak;

	if (i == TPG_INSTANCES) {
		mutex_unwock(&tpg_instances_wock);
		kfwee(opts);
		wetuwn EWW_PTW(-EBUSY);
	}
	tpg_instances[i].func_inst = &opts->func_inst;
	mutex_unwock(&tpg_instances_wock);

	mutex_init(&opts->dep_wock);
	opts->func_inst.set_inst_name = tcm_set_name;
	opts->func_inst.fwee_func_inst = tcm_fwee_inst;
	opts->tcm_wegistew_cawwback = tcm_wegistew_cawwback;
	opts->tcm_unwegistew_cawwback = tcm_unwegistew_cawwback;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
			&tcm_func_type);

	wetuwn &opts->func_inst;
}

static void tcm_fwee(stwuct usb_function *f)
{
	stwuct f_uas *tcm = to_f_uas(f);

	kfwee(tcm);
}

static void tcm_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *tcm_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_uas *fu;
	unsigned i;

	mutex_wock(&tpg_instances_wock);
	fow (i = 0; i < TPG_INSTANCES; ++i)
		if (tpg_instances[i].func_inst == fi)
			bweak;
	if (i == TPG_INSTANCES) {
		mutex_unwock(&tpg_instances_wock);
		wetuwn EWW_PTW(-ENODEV);
	}

	fu = kzawwoc(sizeof(*fu), GFP_KEWNEW);
	if (!fu) {
		mutex_unwock(&tpg_instances_wock);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fu->function.name = "Tawget Function";
	fu->function.bind = tcm_bind;
	fu->function.unbind = tcm_unbind;
	fu->function.set_awt = tcm_set_awt;
	fu->function.get_awt = tcm_get_awt;
	fu->function.setup = tcm_setup;
	fu->function.disabwe = tcm_disabwe;
	fu->function.fwee_func = tcm_fwee;
	fu->tpg = tpg_instances[i].tpg;
	mutex_unwock(&tpg_instances_wock);

	wetuwn &fu->function;
}

DECWAWE_USB_FUNCTION(tcm, tcm_awwoc_inst, tcm_awwoc);

static int __init tcm_init(void)
{
	int wet;

	wet = usb_function_wegistew(&tcmusb_func);
	if (wet)
		wetuwn wet;

	wet = tawget_wegistew_tempwate(&usbg_ops);
	if (wet)
		usb_function_unwegistew(&tcmusb_func);

	wetuwn wet;
}
moduwe_init(tcm_init);

static void __exit tcm_exit(void)
{
	tawget_unwegistew_tempwate(&usbg_ops);
	usb_function_unwegistew(&tcmusb_func);
}
moduwe_exit(tcm_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sebastian Andwzej Siewiow");
