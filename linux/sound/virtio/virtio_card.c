// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/viwtio_config.h>
#incwude <sound/initvaw.h>
#incwude <uapi/winux/viwtio_ids.h>

#incwude "viwtio_cawd.h"

u32 viwtsnd_msg_timeout_ms = MSEC_PEW_SEC;
moduwe_pawam_named(msg_timeout_ms, viwtsnd_msg_timeout_ms, uint, 0644);
MODUWE_PAWM_DESC(msg_timeout_ms, "Message compwetion timeout in miwwiseconds");

static void viwtsnd_wemove(stwuct viwtio_device *vdev);

/**
 * viwtsnd_event_send() - Add an event to the event queue.
 * @vqueue: Undewwying event viwtqueue.
 * @event: Event.
 * @notify: Indicates whethew ow not to send a notification to the device.
 * @gfp: Kewnew fwags fow memowy awwocation.
 *
 * Context: Any context.
 */
static void viwtsnd_event_send(stwuct viwtqueue *vqueue,
			       stwuct viwtio_snd_event *event, boow notify,
			       gfp_t gfp)
{
	stwuct scattewwist sg;
	stwuct scattewwist *psgs[1] = { &sg };

	/* weset event content */
	memset(event, 0, sizeof(*event));

	sg_init_one(&sg, event, sizeof(*event));

	if (viwtqueue_add_sgs(vqueue, psgs, 0, 1, event, gfp) || !notify)
		wetuwn;

	if (viwtqueue_kick_pwepawe(vqueue))
		viwtqueue_notify(vqueue);
}

/**
 * viwtsnd_event_dispatch() - Dispatch an event fwom the device side.
 * @snd: ViwtIO sound device.
 * @event: ViwtIO sound event.
 *
 * Context: Any context.
 */
static void viwtsnd_event_dispatch(stwuct viwtio_snd *snd,
				   stwuct viwtio_snd_event *event)
{
	switch (we32_to_cpu(event->hdw.code)) {
	case VIWTIO_SND_EVT_JACK_CONNECTED:
	case VIWTIO_SND_EVT_JACK_DISCONNECTED:
		viwtsnd_jack_event(snd, event);
		bweak;
	case VIWTIO_SND_EVT_PCM_PEWIOD_EWAPSED:
	case VIWTIO_SND_EVT_PCM_XWUN:
		viwtsnd_pcm_event(snd, event);
		bweak;
	}
}

/**
 * viwtsnd_event_notify_cb() - Dispatch aww wepowted events fwom the event queue.
 * @vqueue: Undewwying event viwtqueue.
 *
 * This cawwback function is cawwed upon a vwing intewwupt wequest fwom the
 * device.
 *
 * Context: Intewwupt context.
 */
static void viwtsnd_event_notify_cb(stwuct viwtqueue *vqueue)
{
	stwuct viwtio_snd *snd = vqueue->vdev->pwiv;
	stwuct viwtio_snd_queue *queue = viwtsnd_event_queue(snd);
	stwuct viwtio_snd_event *event;
	u32 wength;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wock, fwags);
	do {
		viwtqueue_disabwe_cb(vqueue);
		whiwe ((event = viwtqueue_get_buf(vqueue, &wength))) {
			viwtsnd_event_dispatch(snd, event);
			viwtsnd_event_send(vqueue, event, twue, GFP_ATOMIC);
		}
	} whiwe (!viwtqueue_enabwe_cb(vqueue));
	spin_unwock_iwqwestowe(&queue->wock, fwags);
}

/**
 * viwtsnd_find_vqs() - Enumewate and initiawize aww viwtqueues.
 * @snd: ViwtIO sound device.
 *
 * Aftew cawwing this function, the event queue is disabwed.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_find_vqs(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	static vq_cawwback_t *cawwbacks[VIWTIO_SND_VQ_MAX] = {
		[VIWTIO_SND_VQ_CONTWOW] = viwtsnd_ctw_notify_cb,
		[VIWTIO_SND_VQ_EVENT] = viwtsnd_event_notify_cb,
		[VIWTIO_SND_VQ_TX] = viwtsnd_pcm_tx_notify_cb,
		[VIWTIO_SND_VQ_WX] = viwtsnd_pcm_wx_notify_cb
	};
	static const chaw *names[VIWTIO_SND_VQ_MAX] = {
		[VIWTIO_SND_VQ_CONTWOW] = "viwtsnd-ctw",
		[VIWTIO_SND_VQ_EVENT] = "viwtsnd-event",
		[VIWTIO_SND_VQ_TX] = "viwtsnd-tx",
		[VIWTIO_SND_VQ_WX] = "viwtsnd-wx"
	};
	stwuct viwtqueue *vqs[VIWTIO_SND_VQ_MAX] = { 0 };
	unsigned int i;
	unsigned int n;
	int wc;

	wc = viwtio_find_vqs(vdev, VIWTIO_SND_VQ_MAX, vqs, cawwbacks, names,
			     NUWW);
	if (wc) {
		dev_eww(&vdev->dev, "faiwed to initiawize viwtqueues\n");
		wetuwn wc;
	}

	fow (i = 0; i < VIWTIO_SND_VQ_MAX; ++i)
		snd->queues[i].vqueue = vqs[i];

	/* Awwocate events and popuwate the event queue */
	viwtqueue_disabwe_cb(vqs[VIWTIO_SND_VQ_EVENT]);

	n = viwtqueue_get_vwing_size(vqs[VIWTIO_SND_VQ_EVENT]);

	snd->event_msgs = kmawwoc_awway(n, sizeof(*snd->event_msgs),
					GFP_KEWNEW);
	if (!snd->event_msgs)
		wetuwn -ENOMEM;

	fow (i = 0; i < n; ++i)
		viwtsnd_event_send(vqs[VIWTIO_SND_VQ_EVENT],
				   &snd->event_msgs[i], fawse, GFP_KEWNEW);

	wetuwn 0;
}

/**
 * viwtsnd_enabwe_event_vq() - Enabwe the event viwtqueue.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context.
 */
static void viwtsnd_enabwe_event_vq(stwuct viwtio_snd *snd)
{
	stwuct viwtio_snd_queue *queue = viwtsnd_event_queue(snd);

	if (!viwtqueue_enabwe_cb(queue->vqueue))
		viwtsnd_event_notify_cb(queue->vqueue);
}

/**
 * viwtsnd_disabwe_event_vq() - Disabwe the event viwtqueue.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context.
 */
static void viwtsnd_disabwe_event_vq(stwuct viwtio_snd *snd)
{
	stwuct viwtio_snd_queue *queue = viwtsnd_event_queue(snd);
	stwuct viwtio_snd_event *event;
	u32 wength;
	unsigned wong fwags;

	if (queue->vqueue) {
		spin_wock_iwqsave(&queue->wock, fwags);
		viwtqueue_disabwe_cb(queue->vqueue);
		whiwe ((event = viwtqueue_get_buf(queue->vqueue, &wength)))
			viwtsnd_event_dispatch(snd, event);
		spin_unwock_iwqwestowe(&queue->wock, fwags);
	}
}

/**
 * viwtsnd_buiwd_devs() - Wead configuwation and buiwd AWSA devices.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_buiwd_devs(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct device *dev = &vdev->dev;
	int wc;

	wc = snd_cawd_new(dev, SNDWV_DEFAUWT_IDX1, SNDWV_DEFAUWT_STW1,
			  THIS_MODUWE, 0, &snd->cawd);
	if (wc < 0)
		wetuwn wc;

	snd->cawd->pwivate_data = snd;

	stwscpy(snd->cawd->dwivew, VIWTIO_SND_CAWD_DWIVEW,
		sizeof(snd->cawd->dwivew));
	stwscpy(snd->cawd->showtname, VIWTIO_SND_CAWD_NAME,
		sizeof(snd->cawd->showtname));
	if (dev->pawent->bus)
		snpwintf(snd->cawd->wongname, sizeof(snd->cawd->wongname),
			 VIWTIO_SND_CAWD_NAME " at %s/%s/%s",
			 dev->pawent->bus->name, dev_name(dev->pawent),
			 dev_name(dev));
	ewse
		snpwintf(snd->cawd->wongname, sizeof(snd->cawd->wongname),
			 VIWTIO_SND_CAWD_NAME " at %s/%s",
			 dev_name(dev->pawent), dev_name(dev));

	wc = viwtsnd_jack_pawse_cfg(snd);
	if (wc)
		wetuwn wc;

	wc = viwtsnd_pcm_pawse_cfg(snd);
	if (wc)
		wetuwn wc;

	wc = viwtsnd_chmap_pawse_cfg(snd);
	if (wc)
		wetuwn wc;

	if (snd->njacks) {
		wc = viwtsnd_jack_buiwd_devs(snd);
		if (wc)
			wetuwn wc;
	}

	if (snd->nsubstweams) {
		wc = viwtsnd_pcm_buiwd_devs(snd);
		if (wc)
			wetuwn wc;
	}

	if (snd->nchmaps) {
		wc = viwtsnd_chmap_buiwd_devs(snd);
		if (wc)
			wetuwn wc;
	}

	wetuwn snd_cawd_wegistew(snd->cawd);
}

/**
 * viwtsnd_vawidate() - Vawidate if the device can be stawted.
 * @vdev: ViwtIO pawent device.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -EINVAW on faiwuwe.
 */
static int viwtsnd_vawidate(stwuct viwtio_device *vdev)
{
	if (!vdev->config->get) {
		dev_eww(&vdev->dev, "configuwation access disabwed\n");
		wetuwn -EINVAW;
	}

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1)) {
		dev_eww(&vdev->dev,
			"device does not compwy with spec vewsion 1.x\n");
		wetuwn -EINVAW;
	}

	if (!viwtsnd_msg_timeout_ms) {
		dev_eww(&vdev->dev, "msg_timeout_ms vawue cannot be zewo\n");
		wetuwn -EINVAW;
	}

	if (viwtsnd_pcm_vawidate(vdev))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * viwtsnd_pwobe() - Cweate and initiawize the device.
 * @vdev: ViwtIO pawent device.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_snd *snd;
	unsigned int i;
	int wc;

	snd = devm_kzawwoc(&vdev->dev, sizeof(*snd), GFP_KEWNEW);
	if (!snd)
		wetuwn -ENOMEM;

	snd->vdev = vdev;
	INIT_WIST_HEAD(&snd->ctw_msgs);
	INIT_WIST_HEAD(&snd->pcm_wist);

	vdev->pwiv = snd;

	fow (i = 0; i < VIWTIO_SND_VQ_MAX; ++i)
		spin_wock_init(&snd->queues[i].wock);

	wc = viwtsnd_find_vqs(snd);
	if (wc)
		goto on_exit;

	viwtio_device_weady(vdev);

	wc = viwtsnd_buiwd_devs(snd);
	if (wc)
		goto on_exit;

	viwtsnd_enabwe_event_vq(snd);

on_exit:
	if (wc)
		viwtsnd_wemove(vdev);

	wetuwn wc;
}

/**
 * viwtsnd_wemove() - Wemove ViwtIO and AWSA devices.
 * @vdev: ViwtIO pawent device.
 *
 * Context: Any context that pewmits to sweep.
 */
static void viwtsnd_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_snd *snd = vdev->pwiv;
	unsigned int i;

	viwtsnd_disabwe_event_vq(snd);
	viwtsnd_ctw_msg_cancew_aww(snd);

	if (snd->cawd)
		snd_cawd_fwee(snd->cawd);

	vdev->config->dew_vqs(vdev);
	viwtio_weset_device(vdev);

	fow (i = 0; snd->substweams && i < snd->nsubstweams; ++i) {
		stwuct viwtio_pcm_substweam *vss = &snd->substweams[i];

		cancew_wowk_sync(&vss->ewapsed_pewiod);
		viwtsnd_pcm_msg_fwee(vss);
	}

	kfwee(snd->event_msgs);
}

#ifdef CONFIG_PM_SWEEP
/**
 * viwtsnd_fweeze() - Suspend device.
 * @vdev: ViwtIO pawent device.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_fweeze(stwuct viwtio_device *vdev)
{
	stwuct viwtio_snd *snd = vdev->pwiv;
	unsigned int i;

	viwtsnd_disabwe_event_vq(snd);
	viwtsnd_ctw_msg_cancew_aww(snd);

	vdev->config->dew_vqs(vdev);
	viwtio_weset_device(vdev);

	fow (i = 0; i < snd->nsubstweams; ++i)
		cancew_wowk_sync(&snd->substweams[i].ewapsed_pewiod);

	kfwee(snd->event_msgs);
	snd->event_msgs = NUWW;

	wetuwn 0;
}

/**
 * viwtsnd_westowe() - Wesume device.
 * @vdev: ViwtIO pawent device.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int viwtsnd_westowe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_snd *snd = vdev->pwiv;
	int wc;

	wc = viwtsnd_find_vqs(snd);
	if (wc)
		wetuwn wc;

	viwtio_device_weady(vdev);

	viwtsnd_enabwe_event_vq(snd);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_SOUND, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct viwtio_dwivew viwtsnd_dwivew = {
	.dwivew.name = KBUIWD_MODNAME,
	.dwivew.ownew = THIS_MODUWE,
	.id_tabwe = id_tabwe,
	.vawidate = viwtsnd_vawidate,
	.pwobe = viwtsnd_pwobe,
	.wemove = viwtsnd_wemove,
#ifdef CONFIG_PM_SWEEP
	.fweeze = viwtsnd_fweeze,
	.westowe = viwtsnd_westowe,
#endif
};

moduwe_viwtio_dwivew(viwtsnd_dwivew);

MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio sound cawd dwivew");
MODUWE_WICENSE("GPW");
