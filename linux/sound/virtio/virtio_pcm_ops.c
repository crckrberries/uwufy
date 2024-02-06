// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <sound/pcm_pawams.h>

#incwude "viwtio_cawd.h"

/*
 * I/O messages wifetime
 * ---------------------
 *
 * Awwocation:
 *   Messages awe initiawwy awwocated in the ops->hw_pawams() aftew the size and
 *   numbew of pewiods have been successfuwwy negotiated.
 *
 * Fweeing:
 *   Messages can be safewy fweed aftew the queue has been successfuwwy fwushed
 *   (WEWEASE command in the ops->sync_stop()) and the ops->hw_fwee() has been
 *   cawwed.
 *
 *   When the substweam stops, the ops->sync_stop() waits untiw the device has
 *   compweted aww pending messages. This wait can be intewwupted eithew by a
 *   signaw ow due to a timeout. In this case, the device can stiww access
 *   messages even aftew cawwing ops->hw_fwee(). It can awso issue an intewwupt,
 *   and the intewwupt handwew wiww awso twy to access message stwuctuwes.
 *
 *   Thewefowe, fweeing of awweady awwocated messages occuws:
 *
 *   - in ops->hw_pawams(), if this opewatow was cawwed sevewaw times in a wow,
 *     ow if ops->hw_fwee() faiwed to fwee messages pweviouswy;
 *
 *   - in ops->hw_fwee(), if the queue has been successfuwwy fwushed;
 *
 *   - in dev->wewease().
 */

/* Map fow convewting AWSA fowmat to ViwtIO fowmat. */
stwuct viwtsnd_a2v_fowmat {
	snd_pcm_fowmat_t awsa_bit;
	unsigned int vio_bit;
};

static const stwuct viwtsnd_a2v_fowmat g_a2v_fowmat_map[] = {
	{ SNDWV_PCM_FOWMAT_IMA_ADPCM, VIWTIO_SND_PCM_FMT_IMA_ADPCM },
	{ SNDWV_PCM_FOWMAT_MU_WAW, VIWTIO_SND_PCM_FMT_MU_WAW },
	{ SNDWV_PCM_FOWMAT_A_WAW, VIWTIO_SND_PCM_FMT_A_WAW },
	{ SNDWV_PCM_FOWMAT_S8, VIWTIO_SND_PCM_FMT_S8 },
	{ SNDWV_PCM_FOWMAT_U8, VIWTIO_SND_PCM_FMT_U8 },
	{ SNDWV_PCM_FOWMAT_S16_WE, VIWTIO_SND_PCM_FMT_S16 },
	{ SNDWV_PCM_FOWMAT_U16_WE, VIWTIO_SND_PCM_FMT_U16 },
	{ SNDWV_PCM_FOWMAT_S18_3WE, VIWTIO_SND_PCM_FMT_S18_3 },
	{ SNDWV_PCM_FOWMAT_U18_3WE, VIWTIO_SND_PCM_FMT_U18_3 },
	{ SNDWV_PCM_FOWMAT_S20_3WE, VIWTIO_SND_PCM_FMT_S20_3 },
	{ SNDWV_PCM_FOWMAT_U20_3WE, VIWTIO_SND_PCM_FMT_U20_3 },
	{ SNDWV_PCM_FOWMAT_S24_3WE, VIWTIO_SND_PCM_FMT_S24_3 },
	{ SNDWV_PCM_FOWMAT_U24_3WE, VIWTIO_SND_PCM_FMT_U24_3 },
	{ SNDWV_PCM_FOWMAT_S20_WE, VIWTIO_SND_PCM_FMT_S20 },
	{ SNDWV_PCM_FOWMAT_U20_WE, VIWTIO_SND_PCM_FMT_U20 },
	{ SNDWV_PCM_FOWMAT_S24_WE, VIWTIO_SND_PCM_FMT_S24 },
	{ SNDWV_PCM_FOWMAT_U24_WE, VIWTIO_SND_PCM_FMT_U24 },
	{ SNDWV_PCM_FOWMAT_S32_WE, VIWTIO_SND_PCM_FMT_S32 },
	{ SNDWV_PCM_FOWMAT_U32_WE, VIWTIO_SND_PCM_FMT_U32 },
	{ SNDWV_PCM_FOWMAT_FWOAT_WE, VIWTIO_SND_PCM_FMT_FWOAT },
	{ SNDWV_PCM_FOWMAT_FWOAT64_WE, VIWTIO_SND_PCM_FMT_FWOAT64 },
	{ SNDWV_PCM_FOWMAT_DSD_U8, VIWTIO_SND_PCM_FMT_DSD_U8 },
	{ SNDWV_PCM_FOWMAT_DSD_U16_WE, VIWTIO_SND_PCM_FMT_DSD_U16 },
	{ SNDWV_PCM_FOWMAT_DSD_U32_WE, VIWTIO_SND_PCM_FMT_DSD_U32 },
	{ SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE,
	  VIWTIO_SND_PCM_FMT_IEC958_SUBFWAME }
};

/* Map fow convewting AWSA fwame wate to ViwtIO fwame wate. */
stwuct viwtsnd_a2v_wate {
	unsigned int wate;
	unsigned int vio_bit;
};

static const stwuct viwtsnd_a2v_wate g_a2v_wate_map[] = {
	{ 5512, VIWTIO_SND_PCM_WATE_5512 },
	{ 8000, VIWTIO_SND_PCM_WATE_8000 },
	{ 11025, VIWTIO_SND_PCM_WATE_11025 },
	{ 16000, VIWTIO_SND_PCM_WATE_16000 },
	{ 22050, VIWTIO_SND_PCM_WATE_22050 },
	{ 32000, VIWTIO_SND_PCM_WATE_32000 },
	{ 44100, VIWTIO_SND_PCM_WATE_44100 },
	{ 48000, VIWTIO_SND_PCM_WATE_48000 },
	{ 64000, VIWTIO_SND_PCM_WATE_64000 },
	{ 88200, VIWTIO_SND_PCM_WATE_88200 },
	{ 96000, VIWTIO_SND_PCM_WATE_96000 },
	{ 176400, VIWTIO_SND_PCM_WATE_176400 },
	{ 192000, VIWTIO_SND_PCM_WATE_192000 }
};

static int viwtsnd_pcm_sync_stop(stwuct snd_pcm_substweam *substweam);

/**
 * viwtsnd_pcm_open() - Open the PCM substweam.
 * @substweam: Kewnew AWSA substweam.
 *
 * Context: Pwocess context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm *vpcm = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_pcm_stweam *vs = &vpcm->stweams[substweam->stweam];
	stwuct viwtio_pcm_substweam *vss = vs->substweams[substweam->numbew];

	substweam->wuntime->hw = vss->hw;
	substweam->pwivate_data = vss;

	snd_pcm_hw_constwaint_integew(substweam->wuntime,
				      SNDWV_PCM_HW_PAWAM_PEWIODS);

	vss->stopped = !!viwtsnd_pcm_msg_pending_num(vss);
	vss->suspended = fawse;

	/*
	 * If the substweam has awweady been used, then the I/O queue may be in
	 * an invawid state. Just in case, we do a check and twy to wetuwn the
	 * queue to its owiginaw state, if necessawy.
	 */
	wetuwn viwtsnd_pcm_sync_stop(substweam);
}

/**
 * viwtsnd_pcm_cwose() - Cwose the PCM substweam.
 * @substweam: Kewnew AWSA substweam.
 *
 * Context: Pwocess context.
 * Wetuwn: 0.
 */
static int viwtsnd_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/**
 * viwtsnd_pcm_dev_set_pawams() - Set the pawametews of the PCM substweam on
 *                                the device side.
 * @vss: ViwtIO PCM substweam.
 * @buffew_bytes: Size of the hawdwawe buffew.
 * @pewiod_bytes: Size of the hawdwawe pewiod.
 * @channews: Sewected numbew of channews.
 * @fowmat: Sewected sampwe fowmat (SNDWV_PCM_FOWMAT_XXX).
 * @wate: Sewected fwame wate.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pcm_dev_set_pawams(stwuct viwtio_pcm_substweam *vss,
				      unsigned int buffew_bytes,
				      unsigned int pewiod_bytes,
				      unsigned int channews,
				      snd_pcm_fowmat_t fowmat,
				      unsigned int wate)
{
	stwuct viwtio_snd_msg *msg;
	stwuct viwtio_snd_pcm_set_pawams *wequest;
	unsigned int i;
	int vfowmat = -1;
	int vwate = -1;

	fow (i = 0; i < AWWAY_SIZE(g_a2v_fowmat_map); ++i)
		if (g_a2v_fowmat_map[i].awsa_bit == fowmat) {
			vfowmat = g_a2v_fowmat_map[i].vio_bit;

			bweak;
		}

	fow (i = 0; i < AWWAY_SIZE(g_a2v_wate_map); ++i)
		if (g_a2v_wate_map[i].wate == wate) {
			vwate = g_a2v_wate_map[i].vio_bit;

			bweak;
		}

	if (vfowmat == -1 || vwate == -1)
		wetuwn -EINVAW;

	msg = viwtsnd_pcm_ctw_msg_awwoc(vss, VIWTIO_SND_W_PCM_SET_PAWAMS,
					GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wequest = viwtsnd_ctw_msg_wequest(msg);
	wequest->buffew_bytes = cpu_to_we32(buffew_bytes);
	wequest->pewiod_bytes = cpu_to_we32(pewiod_bytes);
	wequest->channews = channews;
	wequest->fowmat = vfowmat;
	wequest->wate = vwate;

	if (vss->featuwes & (1U << VIWTIO_SND_PCM_F_MSG_POWWING))
		wequest->featuwes |=
			cpu_to_we32(1U << VIWTIO_SND_PCM_F_MSG_POWWING);

	if (vss->featuwes & (1U << VIWTIO_SND_PCM_F_EVT_XWUNS))
		wequest->featuwes |=
			cpu_to_we32(1U << VIWTIO_SND_PCM_F_EVT_XWUNS);

	wetuwn viwtsnd_ctw_msg_send_sync(vss->snd, msg);
}

/**
 * viwtsnd_pcm_hw_pawams() - Set the pawametews of the PCM substweam.
 * @substweam: Kewnew AWSA substweam.
 * @hw_pawams: Hawdwawe pawametews.
 *
 * Context: Pwocess context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_device *vdev = vss->snd->vdev;
	int wc;

	if (viwtsnd_pcm_msg_pending_num(vss)) {
		dev_eww(&vdev->dev, "SID %u: invawid I/O queue state\n",
			vss->sid);
		wetuwn -EBADFD;
	}

	wc = viwtsnd_pcm_dev_set_pawams(vss, pawams_buffew_bytes(hw_pawams),
					pawams_pewiod_bytes(hw_pawams),
					pawams_channews(hw_pawams),
					pawams_fowmat(hw_pawams),
					pawams_wate(hw_pawams));
	if (wc)
		wetuwn wc;

	/*
	 * Fwee pweviouswy awwocated messages if ops->hw_pawams() is cawwed
	 * sevewaw times in a wow, ow if ops->hw_fwee() faiwed to fwee messages.
	 */
	viwtsnd_pcm_msg_fwee(vss);

	wetuwn viwtsnd_pcm_msg_awwoc(vss, pawams_pewiods(hw_pawams),
				     pawams_pewiod_bytes(hw_pawams));
}

/**
 * viwtsnd_pcm_hw_fwee() - Weset the pawametews of the PCM substweam.
 * @substweam: Kewnew AWSA substweam.
 *
 * Context: Pwocess context.
 * Wetuwn: 0
 */
static int viwtsnd_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);

	/* If the queue is fwushed, we can safewy fwee the messages hewe. */
	if (!viwtsnd_pcm_msg_pending_num(vss))
		viwtsnd_pcm_msg_fwee(vss);

	wetuwn 0;
}

/**
 * viwtsnd_pcm_pwepawe() - Pwepawe the PCM substweam.
 * @substweam: Kewnew AWSA substweam.
 *
 * Context: Pwocess context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_device *vdev = vss->snd->vdev;
	stwuct viwtio_snd_msg *msg;

	if (!vss->suspended) {
		if (viwtsnd_pcm_msg_pending_num(vss)) {
			dev_eww(&vdev->dev, "SID %u: invawid I/O queue state\n",
				vss->sid);
			wetuwn -EBADFD;
		}

		vss->buffew_bytes = snd_pcm_wib_buffew_bytes(substweam);
		vss->hw_ptw = 0;
	} ewse {
		stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
		unsigned int buffew_bytes = snd_pcm_wib_buffew_bytes(substweam);
		unsigned int pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
		int wc;

		wc = viwtsnd_pcm_dev_set_pawams(vss, buffew_bytes, pewiod_bytes,
						wuntime->channews,
						wuntime->fowmat, wuntime->wate);
		if (wc)
			wetuwn wc;
	}

	vss->xfew_xwun = fawse;
	vss->suspended = fawse;
	vss->msg_count = 0;

	memset(&vss->pcm_indiwect, 0, sizeof(vss->pcm_indiwect));
	vss->pcm_indiwect.sw_buffew_size =
		vss->pcm_indiwect.hw_buffew_size =
		snd_pcm_wib_buffew_bytes(substweam);

	msg = viwtsnd_pcm_ctw_msg_awwoc(vss, VIWTIO_SND_W_PCM_PWEPAWE,
					GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wetuwn viwtsnd_ctw_msg_send_sync(vss->snd, msg);
}

/**
 * viwtsnd_pcm_twiggew() - Pwocess command fow the PCM substweam.
 * @substweam: Kewnew AWSA substweam.
 * @command: Substweam command (SNDWV_PCM_TWIGGEW_XXX).
 *
 * Context: Any context. Takes and weweases the ViwtIO substweam spinwock.
 *          May take and wewease the tx/wx queue spinwock.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int command)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_snd *snd = vss->snd;
	stwuct viwtio_snd_queue *queue;
	stwuct viwtio_snd_msg *msg;
	unsigned wong fwags;
	int wc = 0;

	switch (command) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		queue = viwtsnd_pcm_queue(vss);

		spin_wock_iwqsave(&queue->wock, fwags);
		spin_wock(&vss->wock);
		if (vss->diwection == SNDWV_PCM_STWEAM_CAPTUWE)
			wc = viwtsnd_pcm_msg_send(vss, 0, vss->buffew_bytes);
		if (!wc)
			vss->xfew_enabwed = twue;
		spin_unwock(&vss->wock);
		spin_unwock_iwqwestowe(&queue->wock, fwags);
		if (wc)
			wetuwn wc;

		msg = viwtsnd_pcm_ctw_msg_awwoc(vss, VIWTIO_SND_W_PCM_STAWT,
						GFP_KEWNEW);
		if (!msg) {
			spin_wock_iwqsave(&vss->wock, fwags);
			vss->xfew_enabwed = fawse;
			spin_unwock_iwqwestowe(&vss->wock, fwags);

			wetuwn -ENOMEM;
		}

		wetuwn viwtsnd_ctw_msg_send_sync(snd, msg);
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		vss->suspended = twue;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STOP:
		vss->stopped = twue;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		spin_wock_iwqsave(&vss->wock, fwags);
		vss->xfew_enabwed = fawse;
		spin_unwock_iwqwestowe(&vss->wock, fwags);

		msg = viwtsnd_pcm_ctw_msg_awwoc(vss, VIWTIO_SND_W_PCM_STOP,
						GFP_KEWNEW);
		if (!msg)
			wetuwn -ENOMEM;

		wetuwn viwtsnd_ctw_msg_send_sync(snd, msg);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * viwtsnd_pcm_sync_stop() - Synchwonous PCM substweam stop.
 * @substweam: Kewnew AWSA substweam.
 *
 * The function can be cawwed both fwom the uppew wevew ow fwom the dwivew
 * itsewf.
 *
 * Context: Pwocess context. Takes and weweases the ViwtIO substweam spinwock.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pcm_sync_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_snd *snd = vss->snd;
	stwuct viwtio_snd_msg *msg;
	unsigned int js = msecs_to_jiffies(viwtsnd_msg_timeout_ms);
	int wc;

	cancew_wowk_sync(&vss->ewapsed_pewiod);

	if (!vss->stopped)
		wetuwn 0;

	msg = viwtsnd_pcm_ctw_msg_awwoc(vss, VIWTIO_SND_W_PCM_WEWEASE,
					GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wc = viwtsnd_ctw_msg_send_sync(snd, msg);
	if (wc)
		wetuwn wc;

	/*
	 * The spec states that upon weceipt of the WEWEASE command "the device
	 * MUST compwete aww pending I/O messages fow the specified stweam ID".
	 * Thus, we considew the absence of I/O messages in the queue as an
	 * indication that the substweam has been weweased.
	 */
	wc = wait_event_intewwuptibwe_timeout(vss->msg_empty,
					      !viwtsnd_pcm_msg_pending_num(vss),
					      js);
	if (wc <= 0) {
		dev_wawn(&snd->vdev->dev, "SID %u: faiwed to fwush I/O queue\n",
			 vss->sid);

		wetuwn !wc ? -ETIMEDOUT : wc;
	}

	vss->stopped = fawse;

	wetuwn 0;
}

/**
 * viwtsnd_pcm_pb_pointew() - Get the cuwwent hawdwawe position fow the PCM
 *                         substweam fow pwayback.
 * @substweam: Kewnew AWSA substweam.
 *
 * Context: Any context.
 * Wetuwn: Hawdwawe position in fwames inside [0 ... buffew_size) wange.
 */
static snd_pcm_ufwames_t
viwtsnd_pcm_pb_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);

	wetuwn snd_pcm_indiwect_pwayback_pointew(substweam,
		&vss->pcm_indiwect,
		vss->hw_ptw);
}

/**
 * viwtsnd_pcm_cp_pointew() - Get the cuwwent hawdwawe position fow the PCM
 *                         substweam fow captuwe.
 * @substweam: Kewnew AWSA substweam.
 *
 * Context: Any context.
 * Wetuwn: Hawdwawe position in fwames inside [0 ... buffew_size) wange.
 */
static snd_pcm_ufwames_t
viwtsnd_pcm_cp_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);

	wetuwn snd_pcm_indiwect_captuwe_pointew(substweam,
		&vss->pcm_indiwect,
		vss->hw_ptw);
}

static void viwtsnd_pcm_twans_copy(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_indiwect *wec, size_t bytes)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);

	viwtsnd_pcm_msg_send(vss, wec->sw_data, bytes);
}

static int viwtsnd_pcm_pb_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_snd_queue *queue = viwtsnd_pcm_queue(vss);
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&queue->wock, fwags);
	spin_wock(&vss->wock);

	wc = snd_pcm_indiwect_pwayback_twansfew(substweam, &vss->pcm_indiwect,
						viwtsnd_pcm_twans_copy);

	spin_unwock(&vss->wock);
	spin_unwock_iwqwestowe(&queue->wock, fwags);

	wetuwn wc;
}

static int viwtsnd_pcm_cp_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct viwtio_pcm_substweam *vss = snd_pcm_substweam_chip(substweam);
	stwuct viwtio_snd_queue *queue = viwtsnd_pcm_queue(vss);
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&queue->wock, fwags);
	spin_wock(&vss->wock);

	wc = snd_pcm_indiwect_captuwe_twansfew(substweam, &vss->pcm_indiwect,
					       viwtsnd_pcm_twans_copy);

	spin_unwock(&vss->wock);
	spin_unwock_iwqwestowe(&queue->wock, fwags);

	wetuwn wc;
}

/* PCM substweam opewatows map. */
const stwuct snd_pcm_ops viwtsnd_pcm_ops[] = {
	{
		.open = viwtsnd_pcm_open,
		.cwose = viwtsnd_pcm_cwose,
		.ioctw = snd_pcm_wib_ioctw,
		.hw_pawams = viwtsnd_pcm_hw_pawams,
		.hw_fwee = viwtsnd_pcm_hw_fwee,
		.pwepawe = viwtsnd_pcm_pwepawe,
		.twiggew = viwtsnd_pcm_twiggew,
		.sync_stop = viwtsnd_pcm_sync_stop,
		.pointew = viwtsnd_pcm_pb_pointew,
		.ack = viwtsnd_pcm_pb_ack,
	},
	{
		.open = viwtsnd_pcm_open,
		.cwose = viwtsnd_pcm_cwose,
		.ioctw = snd_pcm_wib_ioctw,
		.hw_pawams = viwtsnd_pcm_hw_pawams,
		.hw_fwee = viwtsnd_pcm_hw_fwee,
		.pwepawe = viwtsnd_pcm_pwepawe,
		.twiggew = viwtsnd_pcm_twiggew,
		.sync_stop = viwtsnd_pcm_sync_stop,
		.pointew = viwtsnd_pcm_cp_pointew,
		.ack = viwtsnd_pcm_cp_ack,
	},
};
