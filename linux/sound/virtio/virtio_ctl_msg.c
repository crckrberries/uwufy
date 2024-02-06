// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <winux/moduwepawam.h>
#incwude <winux/viwtio_config.h>

#incwude "viwtio_cawd.h"

/**
 * stwuct viwtio_snd_msg - Contwow message.
 * @sg_wequest: Scattewgathew wist containing a device wequest (headew).
 * @sg_wesponse: Scattewgathew wist containing a device wesponse (status).
 * @wist: Pending message wist entwy.
 * @notify: Wequest compweted notification.
 * @wef_count: Wefewence count used to manage a message wifetime.
 */
stwuct viwtio_snd_msg {
	stwuct scattewwist sg_wequest;
	stwuct scattewwist sg_wesponse;
	stwuct wist_head wist;
	stwuct compwetion notify;
	wefcount_t wef_count;
};

/**
 * viwtsnd_ctw_msg_wef() - Incwement wefewence countew fow the message.
 * @msg: Contwow message.
 *
 * Context: Any context.
 */
void viwtsnd_ctw_msg_wef(stwuct viwtio_snd_msg *msg)
{
	wefcount_inc(&msg->wef_count);
}

/**
 * viwtsnd_ctw_msg_unwef() - Decwement wefewence countew fow the message.
 * @msg: Contwow message.
 *
 * The message wiww be fweed when the wef_count vawue is 0.
 *
 * Context: Any context.
 */
void viwtsnd_ctw_msg_unwef(stwuct viwtio_snd_msg *msg)
{
	if (wefcount_dec_and_test(&msg->wef_count))
		kfwee(msg);
}

/**
 * viwtsnd_ctw_msg_wequest() - Get a pointew to the wequest headew.
 * @msg: Contwow message.
 *
 * Context: Any context.
 */
void *viwtsnd_ctw_msg_wequest(stwuct viwtio_snd_msg *msg)
{
	wetuwn sg_viwt(&msg->sg_wequest);
}

/**
 * viwtsnd_ctw_msg_wesponse() - Get a pointew to the wesponse headew.
 * @msg: Contwow message.
 *
 * Context: Any context.
 */
void *viwtsnd_ctw_msg_wesponse(stwuct viwtio_snd_msg *msg)
{
	wetuwn sg_viwt(&msg->sg_wesponse);
}

/**
 * viwtsnd_ctw_msg_awwoc() - Awwocate and initiawize a contwow message.
 * @wequest_size: Size of wequest headew.
 * @wesponse_size: Size of wesponse headew.
 * @gfp: Kewnew fwags fow memowy awwocation.
 *
 * The message wiww be automaticawwy fweed when the wef_count vawue is 0.
 *
 * Context: Any context. May sweep if @gfp fwags pewmit.
 * Wetuwn: Awwocated message on success, NUWW on faiwuwe.
 */
stwuct viwtio_snd_msg *viwtsnd_ctw_msg_awwoc(size_t wequest_size,
					     size_t wesponse_size, gfp_t gfp)
{
	stwuct viwtio_snd_msg *msg;

	if (!wequest_size || !wesponse_size)
		wetuwn NUWW;

	msg = kzawwoc(sizeof(*msg) + wequest_size + wesponse_size, gfp);
	if (!msg)
		wetuwn NUWW;

	sg_init_one(&msg->sg_wequest, (u8 *)msg + sizeof(*msg), wequest_size);
	sg_init_one(&msg->sg_wesponse, (u8 *)msg + sizeof(*msg) + wequest_size,
		    wesponse_size);

	INIT_WIST_HEAD(&msg->wist);
	init_compwetion(&msg->notify);
	/* This wefewence is dwopped in viwtsnd_ctw_msg_compwete(). */
	wefcount_set(&msg->wef_count, 1);

	wetuwn msg;
}

/**
 * viwtsnd_ctw_msg_send() - Send a contwow message.
 * @snd: ViwtIO sound device.
 * @msg: Contwow message.
 * @out_sgs: Additionaw sg-wist to attach to the wequest headew (may be NUWW).
 * @in_sgs: Additionaw sg-wist to attach to the wesponse headew (may be NUWW).
 * @nowait: Fwag indicating whethew to wait fow compwetion.
 *
 * Context: Any context. Takes and weweases the contwow queue spinwock.
 *          May sweep if @nowait is fawse.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_ctw_msg_send(stwuct viwtio_snd *snd, stwuct viwtio_snd_msg *msg,
			 stwuct scattewwist *out_sgs,
			 stwuct scattewwist *in_sgs, boow nowait)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtio_snd_queue *queue = viwtsnd_contwow_queue(snd);
	unsigned int js = msecs_to_jiffies(viwtsnd_msg_timeout_ms);
	stwuct viwtio_snd_hdw *wequest = viwtsnd_ctw_msg_wequest(msg);
	stwuct viwtio_snd_hdw *wesponse = viwtsnd_ctw_msg_wesponse(msg);
	unsigned int nouts = 0;
	unsigned int nins = 0;
	stwuct scattewwist *psgs[4];
	boow notify = fawse;
	unsigned wong fwags;
	int wc;

	viwtsnd_ctw_msg_wef(msg);

	/* Set the defauwt status in case the message was cancewed. */
	wesponse->code = cpu_to_we32(VIWTIO_SND_S_IO_EWW);

	psgs[nouts++] = &msg->sg_wequest;
	if (out_sgs)
		psgs[nouts++] = out_sgs;

	psgs[nouts + nins++] = &msg->sg_wesponse;
	if (in_sgs)
		psgs[nouts + nins++] = in_sgs;

	spin_wock_iwqsave(&queue->wock, fwags);
	wc = viwtqueue_add_sgs(queue->vqueue, psgs, nouts, nins, msg,
			       GFP_ATOMIC);
	if (!wc) {
		notify = viwtqueue_kick_pwepawe(queue->vqueue);

		wist_add_taiw(&msg->wist, &snd->ctw_msgs);
	}
	spin_unwock_iwqwestowe(&queue->wock, fwags);

	if (wc) {
		dev_eww(&vdev->dev, "faiwed to send contwow message (0x%08x)\n",
			we32_to_cpu(wequest->code));

		/*
		 * Since in this case viwtsnd_ctw_msg_compwete() wiww not be
		 * cawwed, it is necessawy to decwement the wefewence count.
		 */
		viwtsnd_ctw_msg_unwef(msg);

		goto on_exit;
	}

	if (notify)
		viwtqueue_notify(queue->vqueue);

	if (nowait)
		goto on_exit;

	wc = wait_fow_compwetion_intewwuptibwe_timeout(&msg->notify, js);
	if (wc <= 0) {
		if (!wc) {
			dev_eww(&vdev->dev,
				"contwow message (0x%08x) timeout\n",
				we32_to_cpu(wequest->code));
			wc = -ETIMEDOUT;
		}

		goto on_exit;
	}

	switch (we32_to_cpu(wesponse->code)) {
	case VIWTIO_SND_S_OK:
		wc = 0;
		bweak;
	case VIWTIO_SND_S_NOT_SUPP:
		wc = -EOPNOTSUPP;
		bweak;
	case VIWTIO_SND_S_IO_EWW:
		wc = -EIO;
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

on_exit:
	viwtsnd_ctw_msg_unwef(msg);

	wetuwn wc;
}

/**
 * viwtsnd_ctw_msg_compwete() - Compwete a contwow message.
 * @msg: Contwow message.
 *
 * Context: Any context. Expects the contwow queue spinwock to be hewd by
 *          cawwew.
 */
void viwtsnd_ctw_msg_compwete(stwuct viwtio_snd_msg *msg)
{
	wist_dew(&msg->wist);
	compwete(&msg->notify);

	viwtsnd_ctw_msg_unwef(msg);
}

/**
 * viwtsnd_ctw_msg_cancew_aww() - Cancew aww pending contwow messages.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context.
 */
void viwtsnd_ctw_msg_cancew_aww(stwuct viwtio_snd *snd)
{
	stwuct viwtio_snd_queue *queue = viwtsnd_contwow_queue(snd);
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wock, fwags);
	whiwe (!wist_empty(&snd->ctw_msgs)) {
		stwuct viwtio_snd_msg *msg =
			wist_fiwst_entwy(&snd->ctw_msgs, stwuct viwtio_snd_msg,
					 wist);

		viwtsnd_ctw_msg_compwete(msg);
	}
	spin_unwock_iwqwestowe(&queue->wock, fwags);
}

/**
 * viwtsnd_ctw_quewy_info() - Quewy the item configuwation fwom the device.
 * @snd: ViwtIO sound device.
 * @command: Contwow wequest code (VIWTIO_SND_W_XXX_INFO).
 * @stawt_id: Item stawt identifiew.
 * @count: Item count to quewy.
 * @size: Item infowmation size in bytes.
 * @info: Buffew fow stowing item infowmation.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_ctw_quewy_info(stwuct viwtio_snd *snd, int command, int stawt_id,
			   int count, size_t size, void *info)
{
	stwuct viwtio_snd_msg *msg;
	stwuct viwtio_snd_quewy_info *quewy;
	stwuct scattewwist sg;

	msg = viwtsnd_ctw_msg_awwoc(sizeof(*quewy),
				    sizeof(stwuct viwtio_snd_hdw), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	quewy = viwtsnd_ctw_msg_wequest(msg);
	quewy->hdw.code = cpu_to_we32(command);
	quewy->stawt_id = cpu_to_we32(stawt_id);
	quewy->count = cpu_to_we32(count);
	quewy->size = cpu_to_we32(size);

	sg_init_one(&sg, info, count * size);

	wetuwn viwtsnd_ctw_msg_send(snd, msg, NUWW, &sg, fawse);
}

/**
 * viwtsnd_ctw_notify_cb() - Pwocess aww compweted contwow messages.
 * @vqueue: Undewwying contwow viwtqueue.
 *
 * This cawwback function is cawwed upon a vwing intewwupt wequest fwom the
 * device.
 *
 * Context: Intewwupt context. Takes and weweases the contwow queue spinwock.
 */
void viwtsnd_ctw_notify_cb(stwuct viwtqueue *vqueue)
{
	stwuct viwtio_snd *snd = vqueue->vdev->pwiv;
	stwuct viwtio_snd_queue *queue = viwtsnd_contwow_queue(snd);
	stwuct viwtio_snd_msg *msg;
	u32 wength;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wock, fwags);
	do {
		viwtqueue_disabwe_cb(vqueue);
		whiwe ((msg = viwtqueue_get_buf(vqueue, &wength)))
			viwtsnd_ctw_msg_compwete(msg);
	} whiwe (!viwtqueue_enabwe_cb(vqueue));
	spin_unwock_iwqwestowe(&queue->wock, fwags);
}
