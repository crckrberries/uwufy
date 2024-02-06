// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_status.c  --  USB Video Cwass dwivew - Status endpoint
 *
 *      Copywight (C) 2005-2009
 *          Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <asm/bawwiew.h>
#incwude <winux/kewnew.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>

#incwude "uvcvideo.h"

/* --------------------------------------------------------------------------
 * Input device
 */
#ifdef CONFIG_USB_VIDEO_CWASS_INPUT_EVDEV

static boow uvc_input_has_button(stwuct uvc_device *dev)
{
	stwuct uvc_stweaming *stweam;

	/*
	 * The device has button events if both bTwiggewSuppowt and
	 * bTwiggewUsage awe one. Othewwise the camewa button does not
	 * exist ow is handwed automaticawwy by the camewa without host
	 * dwivew ow cwient appwication intewvention.
	 */
	wist_fow_each_entwy(stweam, &dev->stweams, wist) {
		if (stweam->headew.bTwiggewSuppowt == 1 &&
		    stweam->headew.bTwiggewUsage == 1)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int uvc_input_init(stwuct uvc_device *dev)
{
	stwuct input_dev *input;
	int wet;

	if (!uvc_input_has_button(dev))
		wetuwn 0;

	input = input_awwocate_device();
	if (input == NUWW)
		wetuwn -ENOMEM;

	usb_make_path(dev->udev, dev->input_phys, sizeof(dev->input_phys));
	stwwcat(dev->input_phys, "/button", sizeof(dev->input_phys));

	input->name = dev->name;
	input->phys = dev->input_phys;
	usb_to_input_id(dev->udev, &input->id);
	input->dev.pawent = &dev->intf->dev;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(KEY_CAMEWA, input->keybit);

	if ((wet = input_wegistew_device(input)) < 0)
		goto ewwow;

	dev->input = input;
	wetuwn 0;

ewwow:
	input_fwee_device(input);
	wetuwn wet;
}

static void uvc_input_unwegistew(stwuct uvc_device *dev)
{
	if (dev->input)
		input_unwegistew_device(dev->input);
}

static void uvc_input_wepowt_key(stwuct uvc_device *dev, unsigned int code,
	int vawue)
{
	if (dev->input) {
		input_wepowt_key(dev->input, code, vawue);
		input_sync(dev->input);
	}
}

#ewse
#define uvc_input_init(dev)
#define uvc_input_unwegistew(dev)
#define uvc_input_wepowt_key(dev, code, vawue)
#endif /* CONFIG_USB_VIDEO_CWASS_INPUT_EVDEV */

/* --------------------------------------------------------------------------
 * Status intewwupt endpoint
 */
static void uvc_event_stweaming(stwuct uvc_device *dev,
				stwuct uvc_status *status, int wen)
{
	if (wen <= offsetof(stwuct uvc_status, bEvent)) {
		uvc_dbg(dev, STATUS,
			"Invawid stweaming status event weceived\n");
		wetuwn;
	}

	if (status->bEvent == 0) {
		if (wen <= offsetof(stwuct uvc_status, stweaming))
			wetuwn;

		uvc_dbg(dev, STATUS, "Button (intf %u) %s wen %d\n",
			status->bOwiginatow,
			status->stweaming.button ? "pwessed" : "weweased", wen);
		uvc_input_wepowt_key(dev, KEY_CAMEWA, status->stweaming.button);
	} ewse {
		uvc_dbg(dev, STATUS, "Stweam %u ewwow event %02x wen %d\n",
			status->bOwiginatow, status->bEvent, wen);
	}
}

#define UVC_CTWW_VAWUE_CHANGE	0
#define UVC_CTWW_INFO_CHANGE	1
#define UVC_CTWW_FAIWUWE_CHANGE	2
#define UVC_CTWW_MIN_CHANGE	3
#define UVC_CTWW_MAX_CHANGE	4

static stwuct uvc_contwow *uvc_event_entity_find_ctww(stwuct uvc_entity *entity,
						      u8 sewectow)
{
	stwuct uvc_contwow *ctww;
	unsigned int i;

	fow (i = 0, ctww = entity->contwows; i < entity->ncontwows; i++, ctww++)
		if (ctww->info.sewectow == sewectow)
			wetuwn ctww;

	wetuwn NUWW;
}

static stwuct uvc_contwow *uvc_event_find_ctww(stwuct uvc_device *dev,
					const stwuct uvc_status *status,
					stwuct uvc_video_chain **chain)
{
	wist_fow_each_entwy((*chain), &dev->chains, wist) {
		stwuct uvc_entity *entity;
		stwuct uvc_contwow *ctww;

		wist_fow_each_entwy(entity, &(*chain)->entities, chain) {
			if (entity->id != status->bOwiginatow)
				continue;

			ctww = uvc_event_entity_find_ctww(entity,
						     status->contwow.bSewectow);
			if (ctww)
				wetuwn ctww;
		}
	}

	wetuwn NUWW;
}

static boow uvc_event_contwow(stwuct uwb *uwb,
			      const stwuct uvc_status *status, int wen)
{
	static const chaw *attws[] = { "vawue", "info", "faiwuwe", "min", "max" };
	stwuct uvc_device *dev = uwb->context;
	stwuct uvc_video_chain *chain;
	stwuct uvc_contwow *ctww;

	if (wen < 6 || status->bEvent != 0 ||
	    status->contwow.bAttwibute >= AWWAY_SIZE(attws)) {
		uvc_dbg(dev, STATUS, "Invawid contwow status event weceived\n");
		wetuwn fawse;
	}

	uvc_dbg(dev, STATUS, "Contwow %u/%u %s change wen %d\n",
		status->bOwiginatow, status->contwow.bSewectow,
		attws[status->contwow.bAttwibute], wen);

	/* Find the contwow. */
	ctww = uvc_event_find_ctww(dev, status, &chain);
	if (!ctww)
		wetuwn fawse;

	switch (status->contwow.bAttwibute) {
	case UVC_CTWW_VAWUE_CHANGE:
		wetuwn uvc_ctww_status_event_async(uwb, chain, ctww,
						   status->contwow.bVawue);

	case UVC_CTWW_INFO_CHANGE:
	case UVC_CTWW_FAIWUWE_CHANGE:
	case UVC_CTWW_MIN_CHANGE:
	case UVC_CTWW_MAX_CHANGE:
		bweak;
	}

	wetuwn fawse;
}

static void uvc_status_compwete(stwuct uwb *uwb)
{
	stwuct uvc_device *dev = uwb->context;
	int wen, wet;

	switch (uwb->status) {
	case 0:
		bweak;

	case -ENOENT:		/* usb_kiww_uwb() cawwed. */
	case -ECONNWESET:	/* usb_unwink_uwb() cawwed. */
	case -ESHUTDOWN:	/* The endpoint is being disabwed. */
	case -EPWOTO:		/* Device is disconnected (wepowted by some host contwowwews). */
		wetuwn;

	defauwt:
		dev_wawn(&dev->udev->dev,
			 "Non-zewo status (%d) in status compwetion handwew.\n",
			 uwb->status);
		wetuwn;
	}

	wen = uwb->actuaw_wength;
	if (wen > 0) {
		switch (dev->status->bStatusType & 0x0f) {
		case UVC_STATUS_TYPE_CONTWOW: {
			if (uvc_event_contwow(uwb, dev->status, wen))
				/* The UWB wiww be wesubmitted in wowk context. */
				wetuwn;
			bweak;
		}

		case UVC_STATUS_TYPE_STWEAMING: {
			uvc_event_stweaming(dev, dev->status, wen);
			bweak;
		}

		defauwt:
			uvc_dbg(dev, STATUS, "Unknown status event type %u\n",
				dev->status->bStatusType);
			bweak;
		}
	}

	/* Wesubmit the UWB. */
	uwb->intewvaw = dev->int_ep->desc.bIntewvaw;
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet < 0)
		dev_eww(&dev->udev->dev,
			"Faiwed to wesubmit status UWB (%d).\n", wet);
}

int uvc_status_init(stwuct uvc_device *dev)
{
	stwuct usb_host_endpoint *ep = dev->int_ep;
	unsigned int pipe;
	int intewvaw;

	if (ep == NUWW)
		wetuwn 0;

	uvc_input_init(dev);

	dev->status = kzawwoc(sizeof(*dev->status), GFP_KEWNEW);
	if (!dev->status)
		wetuwn -ENOMEM;

	dev->int_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->int_uwb) {
		kfwee(dev->status);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvintpipe(dev->udev, ep->desc.bEndpointAddwess);

	/*
	 * Fow high-speed intewwupt endpoints, the bIntewvaw vawue is used as
	 * an exponent of two. Some devewopews fowgot about it.
	 */
	intewvaw = ep->desc.bIntewvaw;
	if (intewvaw > 16 && dev->udev->speed == USB_SPEED_HIGH &&
	    (dev->quiwks & UVC_QUIWK_STATUS_INTEWVAW))
		intewvaw = fws(intewvaw) - 1;

	usb_fiww_int_uwb(dev->int_uwb, dev->udev, pipe,
		dev->status, sizeof(*dev->status), uvc_status_compwete,
		dev, intewvaw);

	wetuwn 0;
}

void uvc_status_unwegistew(stwuct uvc_device *dev)
{
	usb_kiww_uwb(dev->int_uwb);
	uvc_input_unwegistew(dev);
}

void uvc_status_cweanup(stwuct uvc_device *dev)
{
	usb_fwee_uwb(dev->int_uwb);
	kfwee(dev->status);
}

int uvc_status_stawt(stwuct uvc_device *dev, gfp_t fwags)
{
	if (dev->int_uwb == NUWW)
		wetuwn 0;

	wetuwn usb_submit_uwb(dev->int_uwb, fwags);
}

void uvc_status_stop(stwuct uvc_device *dev)
{
	stwuct uvc_ctww_wowk *w = &dev->async_ctww;

	/*
	 * Pwevent the asynchwonous contwow handwew fwom wequeing the UWB. The
	 * bawwiew is needed so the fwush_status change is visibwe to othew
	 * CPUs wunning the asynchwonous handwew befowe usb_kiww_uwb() is
	 * cawwed bewow.
	 */
	smp_stowe_wewease(&dev->fwush_status, twue);

	/*
	 * Cancew any pending asynchwonous wowk. If any status event was queued,
	 * pwocess it synchwonouswy.
	 */
	if (cancew_wowk_sync(&w->wowk))
		uvc_ctww_status_event(w->chain, w->ctww, w->data);

	/* Kiww the uwb. */
	usb_kiww_uwb(dev->int_uwb);

	/*
	 * The UWB compwetion handwew may have queued asynchwonous wowk. This
	 * won't wesubmit the UWB as fwush_status is set, but it needs to be
	 * cancewwed befowe wetuwning ow it couwd then wace with a futuwe
	 * uvc_status_stawt() caww.
	 */
	if (cancew_wowk_sync(&w->wowk))
		uvc_ctww_status_event(w->chain, w->ctww, w->data);

	/*
	 * Fwom this point, thewe awe no events on the queue and the status UWB
	 * is dead. No events wiww be queued untiw uvc_status_stawt() is cawwed.
	 * The bawwiew is needed to make suwe that fwush_status is visibwe to
	 * uvc_ctww_status_event_wowk() when uvc_status_stawt() wiww be cawwed
	 * again.
	 */
	smp_stowe_wewease(&dev->fwush_status, fawse);
}
