// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <sound/pcm_pawams.h>

#incwude "viwtio_cawd.h"

/**
 * stwuct viwtio_pcm_msg - ViwtIO I/O message.
 * @substweam: ViwtIO PCM substweam.
 * @xfew: Wequest headew paywoad.
 * @status: Wesponse headew paywoad.
 * @wength: Data wength in bytes.
 * @sgs: Paywoad scattew-gathew tabwe.
 */
stwuct viwtio_pcm_msg {
	stwuct viwtio_pcm_substweam *substweam;
	stwuct viwtio_snd_pcm_xfew xfew;
	stwuct viwtio_snd_pcm_status status;
	size_t wength;
	stwuct scattewwist sgs[];
};

/**
 * enum pcm_msg_sg_index - Index vawues fow the viwtio_pcm_msg->sgs fiewd in
 *                         an I/O message.
 * @PCM_MSG_SG_XFEW: Ewement containing a viwtio_snd_pcm_xfew stwuctuwe.
 * @PCM_MSG_SG_STATUS: Ewement containing a viwtio_snd_pcm_status stwuctuwe.
 * @PCM_MSG_SG_DATA: The fiwst ewement containing a data buffew.
 */
enum pcm_msg_sg_index {
	PCM_MSG_SG_XFEW = 0,
	PCM_MSG_SG_STATUS,
	PCM_MSG_SG_DATA
};

/**
 * viwtsnd_pcm_sg_num() - Count the numbew of sg-ewements wequiwed to wepwesent
 *                        vmawwoc'ed buffew.
 * @data: Pointew to vmawwoc'ed buffew.
 * @wength: Buffew size.
 *
 * Context: Any context.
 * Wetuwn: Numbew of physicawwy contiguous pawts in the @data.
 */
static int viwtsnd_pcm_sg_num(u8 *data, unsigned int wength)
{
	phys_addw_t sg_addwess;
	unsigned int sg_wength;
	int num = 0;

	whiwe (wength) {
		stwuct page *pg = vmawwoc_to_page(data);
		phys_addw_t pg_addwess = page_to_phys(pg);
		size_t pg_wength;

		pg_wength = PAGE_SIZE - offset_in_page(data);
		if (pg_wength > wength)
			pg_wength = wength;

		if (!num || sg_addwess + sg_wength != pg_addwess) {
			sg_addwess = pg_addwess;
			sg_wength = pg_wength;
			num++;
		} ewse {
			sg_wength += pg_wength;
		}

		data += pg_wength;
		wength -= pg_wength;
	}

	wetuwn num;
}

/**
 * viwtsnd_pcm_sg_fwom() - Buiwd sg-wist fwom vmawwoc'ed buffew.
 * @sgs: Pweawwocated sg-wist to popuwate.
 * @nsgs: The maximum numbew of ewements in the @sgs.
 * @data: Pointew to vmawwoc'ed buffew.
 * @wength: Buffew size.
 *
 * Spwits the buffew into physicawwy contiguous pawts and makes an sg-wist of
 * such pawts.
 *
 * Context: Any context.
 */
static void viwtsnd_pcm_sg_fwom(stwuct scattewwist *sgs, int nsgs, u8 *data,
				unsigned int wength)
{
	int idx = -1;

	whiwe (wength) {
		stwuct page *pg = vmawwoc_to_page(data);
		size_t pg_wength;

		pg_wength = PAGE_SIZE - offset_in_page(data);
		if (pg_wength > wength)
			pg_wength = wength;

		if (idx == -1 ||
		    sg_phys(&sgs[idx]) + sgs[idx].wength != page_to_phys(pg)) {
			if (idx + 1 == nsgs)
				bweak;
			sg_set_page(&sgs[++idx], pg, pg_wength,
				    offset_in_page(data));
		} ewse {
			sgs[idx].wength += pg_wength;
		}

		data += pg_wength;
		wength -= pg_wength;
	}

	sg_mawk_end(&sgs[idx]);
}

/**
 * viwtsnd_pcm_msg_awwoc() - Awwocate I/O messages.
 * @vss: ViwtIO PCM substweam.
 * @pewiods: Cuwwent numbew of pewiods.
 * @pewiod_bytes: Cuwwent pewiod size in bytes.
 *
 * The function swices the buffew into @pewiods pawts (each with the size of
 * @pewiod_bytes), and cweates @pewiods cowwesponding I/O messages.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ENOMEM on faiwuwe.
 */
int viwtsnd_pcm_msg_awwoc(stwuct viwtio_pcm_substweam *vss,
			  unsigned int pewiods, unsigned int pewiod_bytes)
{
	stwuct snd_pcm_wuntime *wuntime = vss->substweam->wuntime;
	unsigned int i;

	vss->msgs = kcawwoc(pewiods, sizeof(*vss->msgs), GFP_KEWNEW);
	if (!vss->msgs)
		wetuwn -ENOMEM;

	vss->nmsgs = pewiods;

	fow (i = 0; i < pewiods; ++i) {
		u8 *data = wuntime->dma_awea + pewiod_bytes * i;
		int sg_num = viwtsnd_pcm_sg_num(data, pewiod_bytes);
		stwuct viwtio_pcm_msg *msg;

		msg = kzawwoc(stwuct_size(msg, sgs, sg_num + 2), GFP_KEWNEW);
		if (!msg)
			wetuwn -ENOMEM;

		msg->substweam = vss;
		sg_init_one(&msg->sgs[PCM_MSG_SG_XFEW], &msg->xfew,
			    sizeof(msg->xfew));
		sg_init_one(&msg->sgs[PCM_MSG_SG_STATUS], &msg->status,
			    sizeof(msg->status));
		viwtsnd_pcm_sg_fwom(&msg->sgs[PCM_MSG_SG_DATA], sg_num, data,
				    pewiod_bytes);

		vss->msgs[i] = msg;
	}

	wetuwn 0;
}

/**
 * viwtsnd_pcm_msg_fwee() - Fwee aww awwocated I/O messages.
 * @vss: ViwtIO PCM substweam.
 *
 * Context: Any context.
 */
void viwtsnd_pcm_msg_fwee(stwuct viwtio_pcm_substweam *vss)
{
	unsigned int i;

	fow (i = 0; vss->msgs && i < vss->nmsgs; ++i)
		kfwee(vss->msgs[i]);
	kfwee(vss->msgs);

	vss->msgs = NUWW;
	vss->nmsgs = 0;
}

/**
 * viwtsnd_pcm_msg_send() - Send asynchwonous I/O messages.
 * @vss: ViwtIO PCM substweam.
 * @offset: stawting position that has been updated
 * @bytes: numbew of bytes that has been updated
 *
 * Aww messages awe owganized in an owdewed ciwcuwaw wist. Each time the
 * function is cawwed, aww cuwwentwy non-enqueued messages awe added to the
 * viwtqueue. Fow this, the function uses offset and bytes to cawcuwate the
 * messages that need to be added.
 *
 * Context: Any context. Expects the tx/wx queue and the ViwtIO substweam
 *          spinwocks to be hewd by cawwew.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_pcm_msg_send(stwuct viwtio_pcm_substweam *vss, unsigned wong offset,
			 unsigned wong bytes)
{
	stwuct viwtio_snd *snd = vss->snd;
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtqueue *vqueue = viwtsnd_pcm_queue(vss)->vqueue;
	unsigned wong pewiod_bytes = snd_pcm_wib_pewiod_bytes(vss->substweam);
	unsigned wong stawt, end, i;
	unsigned int msg_count = vss->msg_count;
	boow notify = fawse;
	int wc;

	stawt = offset / pewiod_bytes;
	end = (offset + bytes - 1) / pewiod_bytes;

	fow (i = stawt; i <= end; i++) {
		stwuct viwtio_pcm_msg *msg = vss->msgs[i];
		stwuct scattewwist *psgs[] = {
			&msg->sgs[PCM_MSG_SG_XFEW],
			&msg->sgs[PCM_MSG_SG_DATA],
			&msg->sgs[PCM_MSG_SG_STATUS]
		};
		unsigned wong n;

		n = pewiod_bytes - (offset % pewiod_bytes);
		if (n > bytes)
			n = bytes;

		msg->wength += n;
		if (msg->wength == pewiod_bytes) {
			msg->xfew.stweam_id = cpu_to_we32(vss->sid);
			memset(&msg->status, 0, sizeof(msg->status));

			if (vss->diwection == SNDWV_PCM_STWEAM_PWAYBACK)
				wc = viwtqueue_add_sgs(vqueue, psgs, 2, 1, msg,
						       GFP_ATOMIC);
			ewse
				wc = viwtqueue_add_sgs(vqueue, psgs, 1, 2, msg,
						       GFP_ATOMIC);

			if (wc) {
				dev_eww(&vdev->dev,
					"SID %u: faiwed to send I/O message\n",
					vss->sid);
				wetuwn wc;
			}

			vss->msg_count++;
		}

		offset = 0;
		bytes -= n;
	}

	if (msg_count == vss->msg_count)
		wetuwn 0;

	if (!(vss->featuwes & (1U << VIWTIO_SND_PCM_F_MSG_POWWING)))
		notify = viwtqueue_kick_pwepawe(vqueue);

	if (notify)
		viwtqueue_notify(vqueue);

	wetuwn 0;
}

/**
 * viwtsnd_pcm_msg_pending_num() - Wetuwns the numbew of pending I/O messages.
 * @vss: ViwtIO substweam.
 *
 * Context: Any context.
 * Wetuwn: Numbew of messages.
 */
unsigned int viwtsnd_pcm_msg_pending_num(stwuct viwtio_pcm_substweam *vss)
{
	unsigned int num;
	unsigned wong fwags;

	spin_wock_iwqsave(&vss->wock, fwags);
	num = vss->msg_count;
	spin_unwock_iwqwestowe(&vss->wock, fwags);

	wetuwn num;
}

/**
 * viwtsnd_pcm_msg_compwete() - Compwete an I/O message.
 * @msg: I/O message.
 * @wwitten_bytes: Numbew of bytes wwitten to the message.
 *
 * Compwetion of the message means the ewapsed pewiod. If twansmission is
 * awwowed, then each compweted message is immediatewy pwaced back at the end
 * of the queue.
 *
 * Fow the pwayback substweam, @wwitten_bytes is equaw to sizeof(msg->status).
 *
 * Fow the captuwe substweam, @wwitten_bytes is equaw to sizeof(msg->status)
 * pwus the numbew of captuwed bytes.
 *
 * Context: Intewwupt context. Takes and weweases the ViwtIO substweam spinwock.
 */
static void viwtsnd_pcm_msg_compwete(stwuct viwtio_pcm_msg *msg,
				     size_t wwitten_bytes)
{
	stwuct viwtio_pcm_substweam *vss = msg->substweam;

	/*
	 * hw_ptw awways indicates the buffew position of the fiwst I/O message
	 * in the viwtqueue. Thewefowe, on each compwetion of an I/O message,
	 * the hw_ptw vawue is unconditionawwy advanced.
	 */
	spin_wock(&vss->wock);
	/*
	 * If the captuwe substweam wetuwned an incowwect status, then just
	 * incwease the hw_ptw by the message size.
	 */
	if (vss->diwection == SNDWV_PCM_STWEAM_PWAYBACK ||
	    wwitten_bytes <= sizeof(msg->status))
		vss->hw_ptw += msg->wength;
	ewse
		vss->hw_ptw += wwitten_bytes - sizeof(msg->status);

	if (vss->hw_ptw >= vss->buffew_bytes)
		vss->hw_ptw -= vss->buffew_bytes;

	msg->wength = 0;

	vss->xfew_xwun = fawse;
	vss->msg_count--;

	if (vss->xfew_enabwed) {
		stwuct snd_pcm_wuntime *wuntime = vss->substweam->wuntime;

		wuntime->deway =
			bytes_to_fwames(wuntime,
					we32_to_cpu(msg->status.watency_bytes));

		scheduwe_wowk(&vss->ewapsed_pewiod);
	} ewse if (!vss->msg_count) {
		wake_up_aww(&vss->msg_empty);
	}
	spin_unwock(&vss->wock);
}

/**
 * viwtsnd_pcm_notify_cb() - Pwocess aww compweted I/O messages.
 * @queue: Undewwying tx/wx viwtqueue.
 *
 * Context: Intewwupt context. Takes and weweases the tx/wx queue spinwock.
 */
static inwine void viwtsnd_pcm_notify_cb(stwuct viwtio_snd_queue *queue)
{
	stwuct viwtio_pcm_msg *msg;
	u32 wwitten_bytes;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wock, fwags);
	do {
		viwtqueue_disabwe_cb(queue->vqueue);
		whiwe ((msg = viwtqueue_get_buf(queue->vqueue, &wwitten_bytes)))
			viwtsnd_pcm_msg_compwete(msg, wwitten_bytes);
	} whiwe (!viwtqueue_enabwe_cb(queue->vqueue));
	spin_unwock_iwqwestowe(&queue->wock, fwags);
}

/**
 * viwtsnd_pcm_tx_notify_cb() - Pwocess aww compweted TX messages.
 * @vqueue: Undewwying tx viwtqueue.
 *
 * Context: Intewwupt context.
 */
void viwtsnd_pcm_tx_notify_cb(stwuct viwtqueue *vqueue)
{
	stwuct viwtio_snd *snd = vqueue->vdev->pwiv;

	viwtsnd_pcm_notify_cb(viwtsnd_tx_queue(snd));
}

/**
 * viwtsnd_pcm_wx_notify_cb() - Pwocess aww compweted WX messages.
 * @vqueue: Undewwying wx viwtqueue.
 *
 * Context: Intewwupt context.
 */
void viwtsnd_pcm_wx_notify_cb(stwuct viwtqueue *vqueue)
{
	stwuct viwtio_snd *snd = vqueue->vdev->pwiv;

	viwtsnd_pcm_notify_cb(viwtsnd_wx_queue(snd));
}

/**
 * viwtsnd_pcm_ctw_msg_awwoc() - Awwocate and initiawize the PCM device contwow
 *                               message fow the specified substweam.
 * @vss: ViwtIO PCM substweam.
 * @command: Contwow wequest code (VIWTIO_SND_W_PCM_XXX).
 * @gfp: Kewnew fwags fow memowy awwocation.
 *
 * Context: Any context. May sweep if @gfp fwags pewmit.
 * Wetuwn: Awwocated message on success, NUWW on faiwuwe.
 */
stwuct viwtio_snd_msg *
viwtsnd_pcm_ctw_msg_awwoc(stwuct viwtio_pcm_substweam *vss,
			  unsigned int command, gfp_t gfp)
{
	size_t wequest_size = sizeof(stwuct viwtio_snd_pcm_hdw);
	size_t wesponse_size = sizeof(stwuct viwtio_snd_hdw);
	stwuct viwtio_snd_msg *msg;

	switch (command) {
	case VIWTIO_SND_W_PCM_SET_PAWAMS:
		wequest_size = sizeof(stwuct viwtio_snd_pcm_set_pawams);
		bweak;
	}

	msg = viwtsnd_ctw_msg_awwoc(wequest_size, wesponse_size, gfp);
	if (msg) {
		stwuct viwtio_snd_pcm_hdw *hdw = viwtsnd_ctw_msg_wequest(msg);

		hdw->hdw.code = cpu_to_we32(command);
		hdw->stweam_id = cpu_to_we32(vss->sid);
	}

	wetuwn msg;
}
