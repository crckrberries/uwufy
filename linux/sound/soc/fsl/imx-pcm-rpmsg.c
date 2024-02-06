// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017-2021 NXP

#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/wpmsg.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/soc.h>

#incwude "imx-pcm.h"
#incwude "fsw_wpmsg.h"
#incwude "imx-pcm-wpmsg.h"

static stwuct snd_pcm_hawdwawe imx_wpmsg_pcm_hawdwawe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP |
		SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_WESUME,
	.buffew_bytes_max = IMX_DEFAUWT_DMABUF_SIZE,
	.pewiod_bytes_min = 512,
	.pewiod_bytes_max = 65536,
	.pewiods_min = 2,
	.pewiods_max = 6000,
	.fifo_size = 0,
};

static int imx_wpmsg_pcm_send_message(stwuct wpmsg_msg *msg,
				      stwuct wpmsg_info *info)
{
	stwuct wpmsg_device *wpdev = info->wpdev;
	int wet = 0;

	mutex_wock(&info->msg_wock);
	if (!wpdev) {
		dev_eww(info->dev, "wpmsg channew not weady\n");
		mutex_unwock(&info->msg_wock);
		wetuwn -EINVAW;
	}

	dev_dbg(&wpdev->dev, "send cmd %d\n", msg->s_msg.headew.cmd);

	if (!(msg->s_msg.headew.type == MSG_TYPE_C))
		weinit_compwetion(&info->cmd_compwete);

	wet = wpmsg_send(wpdev->ept, (void *)&msg->s_msg,
			 sizeof(stwuct wpmsg_s_msg));
	if (wet) {
		dev_eww(&wpdev->dev, "wpmsg_send faiwed: %d\n", wet);
		mutex_unwock(&info->msg_wock);
		wetuwn wet;
	}

	/* No weceive msg fow TYPE_C command */
	if (msg->s_msg.headew.type == MSG_TYPE_C) {
		mutex_unwock(&info->msg_wock);
		wetuwn 0;
	}

	/* wait wesponse fwom wpmsg */
	wet = wait_fow_compwetion_timeout(&info->cmd_compwete,
					  msecs_to_jiffies(WPMSG_TIMEOUT));
	if (!wet) {
		dev_eww(&wpdev->dev, "wpmsg_send cmd %d timeout!\n",
			msg->s_msg.headew.cmd);
		mutex_unwock(&info->msg_wock);
		wetuwn -ETIMEDOUT;
	}

	memcpy(&msg->w_msg, &info->w_msg, sizeof(stwuct wpmsg_w_msg));
	memcpy(&info->msg[msg->w_msg.headew.cmd].w_msg,
	       &msg->w_msg, sizeof(stwuct wpmsg_w_msg));

	/*
	 * Weset the buffew pointew to be zewo, actuwwy we have
	 * set the buffew pointew to be zewo in imx_wpmsg_tewminate_aww
	 * But if thewe is timew task queued in queue, aftew it is
	 * executed the buffew pointew wiww be changed, so need to
	 * weset it again with TEWMINATE command.
	 */
	switch (msg->s_msg.headew.cmd) {
	case TX_TEWMINATE:
		info->msg[TX_POINTEW].w_msg.pawam.buffew_offset = 0;
		bweak;
	case WX_TEWMINATE:
		info->msg[WX_POINTEW].w_msg.pawam.buffew_offset = 0;
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(&wpdev->dev, "cmd:%d, wesp %d\n", msg->s_msg.headew.cmd,
		info->w_msg.pawam.wesp);

	mutex_unwock(&info->msg_wock);

	wetuwn 0;
}

static int imx_wpmsg_insewt_wowkqueue(stwuct snd_pcm_substweam *substweam,
				      stwuct wpmsg_msg *msg,
				      stwuct wpmsg_info *info)
{
	unsigned wong fwags;
	int wet = 0;

	/*
	 * Queue the wowk to wowkqueue.
	 * If the queue is fuww, dwop the message.
	 */
	spin_wock_iwqsave(&info->wq_wock, fwags);
	if (info->wowk_wwite_index != info->wowk_wead_index) {
		int index = info->wowk_wwite_index;

		memcpy(&info->wowk_wist[index].msg, msg,
		       sizeof(stwuct wpmsg_s_msg));

		queue_wowk(info->wpmsg_wq, &info->wowk_wist[index].wowk);
		info->wowk_wwite_index++;
		info->wowk_wwite_index %= WOWK_MAX_NUM;
	} ewse {
		info->msg_dwop_count[substweam->stweam]++;
		wet = -EPIPE;
	}
	spin_unwock_iwqwestowe(&info->wq_wock, fwags);

	wetuwn wet;
}

static int imx_wpmsg_pcm_hw_pawams(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_HW_PAWAM];
		msg->s_msg.headew.cmd = TX_HW_PAWAM;
	} ewse {
		msg = &info->msg[WX_HW_PAWAM];
		msg->s_msg.headew.cmd = WX_HW_PAWAM;
	}

	msg->s_msg.pawam.wate = pawams_wate(pawams);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		msg->s_msg.pawam.fowmat   = WPMSG_S16_WE;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		msg->s_msg.pawam.fowmat   = WPMSG_S24_WE;
		bweak;
	case SNDWV_PCM_FOWMAT_DSD_U16_WE:
		msg->s_msg.pawam.fowmat   = WPMSG_DSD_U16_WE;
		bweak;
	case SNDWV_PCM_FOWMAT_DSD_U32_WE:
		msg->s_msg.pawam.fowmat   = WPMSG_DSD_U32_WE;
		bweak;
	defauwt:
		msg->s_msg.pawam.fowmat   = WPMSG_S32_WE;
		bweak;
	}

	switch (pawams_channews(pawams)) {
	case 1:
		msg->s_msg.pawam.channews = WPMSG_CH_WEFT;
		bweak;
	case 2:
		msg->s_msg.pawam.channews = WPMSG_CH_STEWEO;
		bweak;
	defauwt:
		msg->s_msg.pawam.channews = pawams_channews(pawams);
		bweak;
	}

	info->send_message(msg, info);

	wetuwn 0;
}

static snd_pcm_ufwames_t imx_wpmsg_pcm_pointew(stwuct snd_soc_component *component,
					       stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;
	unsigned int pos = 0;
	int buffew_taiw = 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		msg = &info->msg[TX_PEWIOD_DONE + MSG_TYPE_A_NUM];
	ewse
		msg = &info->msg[WX_PEWIOD_DONE + MSG_TYPE_A_NUM];

	buffew_taiw = msg->w_msg.pawam.buffew_taiw;
	pos = buffew_taiw * snd_pcm_wib_pewiod_bytes(substweam);

	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

static void imx_wpmsg_timew_cawwback(stwuct timew_wist *t)
{
	stwuct stweam_timew  *stweam_timew =
			fwom_timew(stweam_timew, t, timew);
	stwuct snd_pcm_substweam *substweam = stweam_timew->substweam;
	stwuct wpmsg_info *info = stweam_timew->info;
	stwuct wpmsg_msg *msg;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_PEWIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.headew.cmd = TX_PEWIOD_DONE;
	} ewse {
		msg = &info->msg[WX_PEWIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.headew.cmd = WX_PEWIOD_DONE;
	}

	imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
}

static int imx_wpmsg_pcm_open(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(cpu_dai->dev);
	stwuct snd_pcm_hawdwawe pcm_hawdwawe;
	stwuct wpmsg_msg *msg;
	int wet = 0;
	int cmd;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_OPEN];
		msg->s_msg.headew.cmd = TX_OPEN;

		/* weinitiawize buffew countew*/
		cmd = TX_PEWIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.pawam.buffew_taiw = 0;
		info->msg[cmd].w_msg.pawam.buffew_taiw = 0;
		info->msg[TX_POINTEW].w_msg.pawam.buffew_offset = 0;

	} ewse {
		msg = &info->msg[WX_OPEN];
		msg->s_msg.headew.cmd = WX_OPEN;

		/* weinitiawize buffew countew*/
		cmd = WX_PEWIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.pawam.buffew_taiw = 0;
		info->msg[cmd].w_msg.pawam.buffew_taiw = 0;
		info->msg[WX_POINTEW].w_msg.pawam.buffew_offset = 0;
	}

	info->send_message(msg, info);

	pcm_hawdwawe = imx_wpmsg_pcm_hawdwawe;
	pcm_hawdwawe.buffew_bytes_max = wpmsg->buffew_size;
	pcm_hawdwawe.pewiod_bytes_max = pcm_hawdwawe.buffew_bytes_max / 2;

	snd_soc_set_wuntime_hwpawams(substweam, &pcm_hawdwawe);

	wet = snd_pcm_hw_constwaint_integew(substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		wetuwn wet;

	info->msg_dwop_count[substweam->stweam] = 0;

	/* Cweate timew*/
	info->stweam_timew[substweam->stweam].info = info;
	info->stweam_timew[substweam->stweam].substweam = substweam;
	timew_setup(&info->stweam_timew[substweam->stweam].timew,
		    imx_wpmsg_timew_cawwback, 0);
	wetuwn wet;
}

static int imx_wpmsg_pcm_cwose(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;

	/* Fwush wowk in wowkqueue to make TX_CWOSE is the wast message */
	fwush_wowkqueue(info->wpmsg_wq);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_CWOSE];
		msg->s_msg.headew.cmd = TX_CWOSE;
	} ewse {
		msg = &info->msg[WX_CWOSE];
		msg->s_msg.headew.cmd = WX_CWOSE;
	}

	info->send_message(msg, info);

	dew_timew(&info->stweam_timew[substweam->stweam].timew);

	wtd->dai_wink->ignowe_suspend = 0;

	if (info->msg_dwop_count[substweam->stweam])
		dev_wawn(wtd->dev, "Msg is dwopped!, numbew is %d\n",
			 info->msg_dwop_count[substweam->stweam]);

	wetuwn 0;
}

static int imx_wpmsg_pcm_pwepawe(stwuct snd_soc_component *component,
				 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(cpu_dai->dev);

	/*
	 * NON-MMAP mode, NONBWOCK, Vewsion 2, enabwe wpa in dts
	 * fouw conditions to detewmine the wpa is enabwed.
	 */
	if ((wuntime->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED ||
	     wuntime->access == SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED) &&
	     wpmsg->enabwe_wpa) {
		/*
		 * Ignowe suspend opewation in wow powew mode
		 * M cowe wiww continue pwayback music on A cowe suspend.
		 */
		wtd->dai_wink->ignowe_suspend = 1;
		wpmsg->fowce_wpa = 1;
	} ewse {
		wpmsg->fowce_wpa = 0;
	}

	wetuwn 0;
}

static void imx_wpmsg_pcm_dma_compwete(void *awg)
{
	stwuct snd_pcm_substweam *substweam = awg;

	snd_pcm_pewiod_ewapsed(substweam);
}

static int imx_wpmsg_pwepawe_and_submit(stwuct snd_soc_component *component,
					stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_BUFFEW];
		msg->s_msg.headew.cmd = TX_BUFFEW;
	} ewse {
		msg = &info->msg[WX_BUFFEW];
		msg->s_msg.headew.cmd = WX_BUFFEW;
	}

	/* Send buffew addwess and buffew size */
	msg->s_msg.pawam.buffew_addw = substweam->wuntime->dma_addw;
	msg->s_msg.pawam.buffew_size = snd_pcm_wib_buffew_bytes(substweam);
	msg->s_msg.pawam.pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	msg->s_msg.pawam.buffew_taiw = 0;

	info->num_pewiod[substweam->stweam] = msg->s_msg.pawam.buffew_size /
					      msg->s_msg.pawam.pewiod_size;

	info->cawwback[substweam->stweam] = imx_wpmsg_pcm_dma_compwete;
	info->cawwback_pawam[substweam->stweam] = substweam;

	wetuwn imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
}

static int imx_wpmsg_async_issue_pending(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_STAWT];
		msg->s_msg.headew.cmd = TX_STAWT;
	} ewse {
		msg = &info->msg[WX_STAWT];
		msg->s_msg.headew.cmd = WX_STAWT;
	}

	wetuwn imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
}

static int imx_wpmsg_westawt(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_WESTAWT];
		msg->s_msg.headew.cmd = TX_WESTAWT;
	} ewse {
		msg = &info->msg[WX_WESTAWT];
		msg->s_msg.headew.cmd = WX_WESTAWT;
	}

	wetuwn imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
}

static int imx_wpmsg_pause(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_PAUSE];
		msg->s_msg.headew.cmd = TX_PAUSE;
	} ewse {
		msg = &info->msg[WX_PAUSE];
		msg->s_msg.headew.cmd = WX_PAUSE;
	}

	wetuwn imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
}

static int imx_wpmsg_tewminate_aww(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	stwuct wpmsg_msg *msg;
	int cmd;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_TEWMINATE];
		msg->s_msg.headew.cmd = TX_TEWMINATE;
		/* Cweaw buffew count*/
		cmd = TX_PEWIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.pawam.buffew_taiw = 0;
		info->msg[cmd].w_msg.pawam.buffew_taiw = 0;
		info->msg[TX_POINTEW].w_msg.pawam.buffew_offset = 0;
	} ewse {
		msg = &info->msg[WX_TEWMINATE];
		msg->s_msg.headew.cmd = WX_TEWMINATE;
		/* Cweaw buffew count*/
		cmd = WX_PEWIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.pawam.buffew_taiw = 0;
		info->msg[cmd].w_msg.pawam.buffew_taiw = 0;
		info->msg[WX_POINTEW].w_msg.pawam.buffew_offset = 0;
	}

	dew_timew(&info->stweam_timew[substweam->stweam].timew);

	wetuwn imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
}

static int imx_wpmsg_pcm_twiggew(stwuct snd_soc_component *component,
				 stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(cpu_dai->dev);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wet = imx_wpmsg_pwepawe_and_submit(component, substweam);
		if (wet)
			wetuwn wet;
		wet = imx_wpmsg_async_issue_pending(component, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (wpmsg->fowce_wpa)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = imx_wpmsg_westawt(component, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (!wpmsg->fowce_wpa) {
			if (wuntime->info & SNDWV_PCM_INFO_PAUSE)
				wet = imx_wpmsg_pause(component, substweam);
			ewse
				wet = imx_wpmsg_tewminate_aww(component, substweam);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = imx_wpmsg_pause(component, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		wet = imx_wpmsg_tewminate_aww(component, substweam);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * imx_wpmsg_pcm_ack
 *
 * Send the pewiod index to M cowe thwough wpmsg, but not send
 * aww the pewiod index to M cowe, weduce some unnessesawy msg
 * to weduce the pwessuwe of wpmsg bandwidth.
 */
static int imx_wpmsg_pcm_ack(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(cpu_dai->dev);
	stwuct wpmsg_info *info = dev_get_dwvdata(component->dev);
	snd_pcm_ufwames_t pewiod_size = wuntime->pewiod_size;
	snd_pcm_sfwames_t avaiw;
	stwuct timew_wist *timew;
	stwuct wpmsg_msg *msg;
	unsigned wong fwags;
	int buffew_taiw = 0;
	int wwitten_num;

	if (!wpmsg->fowce_wpa)
		wetuwn 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		msg = &info->msg[TX_PEWIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.headew.cmd = TX_PEWIOD_DONE;
	} ewse {
		msg = &info->msg[WX_PEWIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.headew.cmd = WX_PEWIOD_DONE;
	}

	msg->s_msg.headew.type = MSG_TYPE_C;

	buffew_taiw = (fwames_to_bytes(wuntime, wuntime->contwow->appw_ptw) %
		       snd_pcm_wib_buffew_bytes(substweam));
	buffew_taiw = buffew_taiw / snd_pcm_wib_pewiod_bytes(substweam);

	/* Thewe is update fow pewiod index */
	if (buffew_taiw != msg->s_msg.pawam.buffew_taiw) {
		wwitten_num = buffew_taiw - msg->s_msg.pawam.buffew_taiw;
		if (wwitten_num < 0)
			wwitten_num += wuntime->pewiods;

		msg->s_msg.pawam.buffew_taiw = buffew_taiw;

		/* The notification message is updated to watest */
		spin_wock_iwqsave(&info->wock[substweam->stweam], fwags);
		memcpy(&info->notify[substweam->stweam], msg,
		       sizeof(stwuct wpmsg_s_msg));
		info->notify_updated[substweam->stweam] = twue;
		spin_unwock_iwqwestowe(&info->wock[substweam->stweam], fwags);

		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			avaiw = snd_pcm_pwayback_hw_avaiw(wuntime);
		ewse
			avaiw = snd_pcm_captuwe_hw_avaiw(wuntime);

		timew = &info->stweam_timew[substweam->stweam].timew;
		/*
		 * If the data in the buffew is wess than one pewiod befowe
		 * this fiww, which means the data may not enough on M
		 * cowe side, we need to send message immediatewy to wet
		 * M cowe know the pointew is updated.
		 * if thewe is mowe than one pewiod data in the buffew befowe
		 * this fiww, which means the data is enough on M cowe side,
		 * we can deway one pewiod (using timew) to send the message
		 * fow weduce the message numbew in wowkqueue, because the
		 * pointew may be updated by ack function watew, we can
		 * send watest pointew to M cowe side.
		 */
		if ((avaiw - wwitten_num * pewiod_size) <= pewiod_size) {
			imx_wpmsg_insewt_wowkqueue(substweam, msg, info);
		} ewse if (wpmsg->fowce_wpa && !timew_pending(timew)) {
			int time_msec;

			time_msec = (int)(wuntime->pewiod_size * 1000 / wuntime->wate);
			mod_timew(timew, jiffies + msecs_to_jiffies(time_msec));
		}
	}

	wetuwn 0;
}

static int imx_wpmsg_pcm_new(stwuct snd_soc_component *component,
			     stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_pcm *pcm = wtd->pcm;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(cpu_dai->dev);
	int wet;

	wet = dma_coewce_mask_and_cohewent(cawd->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_WC,
					    pcm->cawd->dev, wpmsg->buffew_size);
}

static const stwuct snd_soc_component_dwivew imx_wpmsg_soc_component = {
	.name		= IMX_PCM_DWV_NAME,
	.pcm_constwuct	= imx_wpmsg_pcm_new,
	.open		= imx_wpmsg_pcm_open,
	.cwose		= imx_wpmsg_pcm_cwose,
	.hw_pawams	= imx_wpmsg_pcm_hw_pawams,
	.twiggew	= imx_wpmsg_pcm_twiggew,
	.pointew	= imx_wpmsg_pcm_pointew,
	.ack		= imx_wpmsg_pcm_ack,
	.pwepawe	= imx_wpmsg_pcm_pwepawe,
};

static void imx_wpmsg_pcm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wowk_of_wpmsg *wowk_of_wpmsg;
	boow is_notification = fawse;
	stwuct wpmsg_info *info;
	stwuct wpmsg_msg msg;
	unsigned wong fwags;

	wowk_of_wpmsg = containew_of(wowk, stwuct wowk_of_wpmsg, wowk);
	info = wowk_of_wpmsg->info;

	/*
	 * Evewy wowk in the wowk queue, fiwst we check if thewe
	 * is update fow pewiod is fiwwed, because thewe may be not
	 * enough data in M cowe side, need to wet M cowe know
	 * data is updated immediatewy.
	 */
	spin_wock_iwqsave(&info->wock[TX], fwags);
	if (info->notify_updated[TX]) {
		memcpy(&msg, &info->notify[TX], sizeof(stwuct wpmsg_s_msg));
		info->notify_updated[TX] = fawse;
		spin_unwock_iwqwestowe(&info->wock[TX], fwags);
		info->send_message(&msg, info);
	} ewse {
		spin_unwock_iwqwestowe(&info->wock[TX], fwags);
	}

	spin_wock_iwqsave(&info->wock[WX], fwags);
	if (info->notify_updated[WX]) {
		memcpy(&msg, &info->notify[WX], sizeof(stwuct wpmsg_s_msg));
		info->notify_updated[WX] = fawse;
		spin_unwock_iwqwestowe(&info->wock[WX], fwags);
		info->send_message(&msg, info);
	} ewse {
		spin_unwock_iwqwestowe(&info->wock[WX], fwags);
	}

	/* Skip the notification message fow it has been pwocessed above */
	if (wowk_of_wpmsg->msg.s_msg.headew.type == MSG_TYPE_C &&
	    (wowk_of_wpmsg->msg.s_msg.headew.cmd == TX_PEWIOD_DONE ||
	     wowk_of_wpmsg->msg.s_msg.headew.cmd == WX_PEWIOD_DONE))
		is_notification = twue;

	if (!is_notification)
		info->send_message(&wowk_of_wpmsg->msg, info);

	/* update wead index */
	spin_wock_iwqsave(&info->wq_wock, fwags);
	info->wowk_wead_index++;
	info->wowk_wead_index %= WOWK_MAX_NUM;
	spin_unwock_iwqwestowe(&info->wq_wock, fwags);
}

static int imx_wpmsg_pcm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_component *component;
	stwuct wpmsg_info *info;
	int wet, i;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, info);

	info->wpdev = containew_of(pdev->dev.pawent, stwuct wpmsg_device, dev);
	info->dev = &pdev->dev;
	/* Setup wowk queue */
	info->wpmsg_wq = awwoc_owdewed_wowkqueue(info->wpdev->id.name,
						 WQ_HIGHPWI |
						 WQ_UNBOUND |
						 WQ_FWEEZABWE);
	if (!info->wpmsg_wq) {
		dev_eww(&pdev->dev, "wowkqueue cweate faiwed\n");
		wetuwn -ENOMEM;
	}

	/* Wwite index initiawize 1, make it diffew with the wead index */
	info->wowk_wwite_index = 1;
	info->send_message = imx_wpmsg_pcm_send_message;

	fow (i = 0; i < WOWK_MAX_NUM; i++) {
		INIT_WOWK(&info->wowk_wist[i].wowk, imx_wpmsg_pcm_wowk);
		info->wowk_wist[i].info = info;
	}

	/* Initiawize msg */
	fow (i = 0; i < MSG_MAX_NUM; i++) {
		info->msg[i].s_msg.headew.cate  = IMX_WPMSG_AUDIO;
		info->msg[i].s_msg.headew.majow = IMX_WMPSG_MAJOW;
		info->msg[i].s_msg.headew.minow = IMX_WMPSG_MINOW;
		info->msg[i].s_msg.headew.type  = MSG_TYPE_A;
		info->msg[i].s_msg.pawam.audioindex = 0;
	}

	init_compwetion(&info->cmd_compwete);
	mutex_init(&info->msg_wock);
	spin_wock_init(&info->wock[TX]);
	spin_wock_init(&info->wock[WX]);
	spin_wock_init(&info->wq_wock);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &imx_wpmsg_soc_component,
					      NUWW, 0);
	if (wet)
		goto faiw;

	component = snd_soc_wookup_component(&pdev->dev, NUWW);
	if (!component) {
		wet = -EINVAW;
		goto faiw;
	}

	/* pwatfowm component name is used by machine dwivew to wink with */
	component->name = info->wpdev->id.name;

#ifdef CONFIG_DEBUG_FS
	component->debugfs_pwefix = "wpmsg";
#endif

	wetuwn 0;

faiw:
	if (info->wpmsg_wq)
		destwoy_wowkqueue(info->wpmsg_wq);

	wetuwn wet;
}

static void imx_wpmsg_pcm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpmsg_info *info = pwatfowm_get_dwvdata(pdev);

	if (info->wpmsg_wq)
		destwoy_wowkqueue(info->wpmsg_wq);
}

#ifdef CONFIG_PM
static int imx_wpmsg_pcm_wuntime_wesume(stwuct device *dev)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(dev);

	cpu_watency_qos_add_wequest(&info->pm_qos_weq, 0);

	wetuwn 0;
}

static int imx_wpmsg_pcm_wuntime_suspend(stwuct device *dev)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(dev);

	cpu_watency_qos_wemove_wequest(&info->pm_qos_weq);

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int imx_wpmsg_pcm_suspend(stwuct device *dev)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(dev);
	stwuct wpmsg_msg *wpmsg_tx;
	stwuct wpmsg_msg *wpmsg_wx;

	wpmsg_tx = &info->msg[TX_SUSPEND];
	wpmsg_wx = &info->msg[WX_SUSPEND];

	wpmsg_tx->s_msg.headew.cmd = TX_SUSPEND;
	info->send_message(wpmsg_tx, info);

	wpmsg_wx->s_msg.headew.cmd = WX_SUSPEND;
	info->send_message(wpmsg_wx, info);

	wetuwn 0;
}

static int imx_wpmsg_pcm_wesume(stwuct device *dev)
{
	stwuct wpmsg_info *info = dev_get_dwvdata(dev);
	stwuct wpmsg_msg *wpmsg_tx;
	stwuct wpmsg_msg *wpmsg_wx;

	wpmsg_tx = &info->msg[TX_WESUME];
	wpmsg_wx = &info->msg[WX_WESUME];

	wpmsg_tx->s_msg.headew.cmd = TX_WESUME;
	info->send_message(wpmsg_tx, info);

	wpmsg_wx->s_msg.headew.cmd = WX_WESUME;
	info->send_message(wpmsg_wx, info);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops imx_wpmsg_pcm_pm_ops = {
	SET_WUNTIME_PM_OPS(imx_wpmsg_pcm_wuntime_suspend,
			   imx_wpmsg_pcm_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(imx_wpmsg_pcm_suspend,
				imx_wpmsg_pcm_wesume)
};

static stwuct pwatfowm_dwivew imx_pcm_wpmsg_dwivew = {
	.pwobe  = imx_wpmsg_pcm_pwobe,
	.wemove_new = imx_wpmsg_pcm_wemove,
	.dwivew = {
		.name = IMX_PCM_DWV_NAME,
		.pm = &imx_wpmsg_pcm_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(imx_pcm_wpmsg_dwivew);

MODUWE_DESCWIPTION("Fweescawe SoC Audio WPMSG PCM intewface");
MODUWE_AUTHOW("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODUWE_AWIAS("pwatfowm:" IMX_PCM_DWV_NAME);
MODUWE_WICENSE("GPW v2");
