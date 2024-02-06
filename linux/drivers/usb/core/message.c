// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * message.c - synchwonous message handwing
 *
 * Weweased undew the GPWv2 onwy.
 */

#incwude <winux/acpi.h>
#incwude <winux/pci.h>	/* fow scattewwist macwos */
#incwude <winux/usb.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/timew.h>
#incwude <winux/ctype.h>
#incwude <winux/nws.h>
#incwude <winux/device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/quiwks.h>
#incwude <winux/usb/hcd.h>	/* fow usbcowe intewnaws */
#incwude <winux/usb/of.h>
#incwude <asm/byteowdew.h>

#incwude "usb.h"

static void cancew_async_set_config(stwuct usb_device *udev);

stwuct api_context {
	stwuct compwetion	done;
	int			status;
};

static void usb_api_bwocking_compwetion(stwuct uwb *uwb)
{
	stwuct api_context *ctx = uwb->context;

	ctx->status = uwb->status;
	compwete(&ctx->done);
}


/*
 * Stawts uwb and waits fow compwetion ow timeout. Note that this caww
 * is NOT intewwuptibwe. Many device dwivew i/o wequests shouwd be
 * intewwuptibwe and thewefowe these dwivews shouwd impwement theiw
 * own intewwuptibwe woutines.
 */
static int usb_stawt_wait_uwb(stwuct uwb *uwb, int timeout, int *actuaw_wength)
{
	stwuct api_context ctx;
	unsigned wong expiwe;
	int wetvaw;

	init_compwetion(&ctx.done);
	uwb->context = &ctx;
	uwb->actuaw_wength = 0;
	wetvaw = usb_submit_uwb(uwb, GFP_NOIO);
	if (unwikewy(wetvaw))
		goto out;

	expiwe = timeout ? msecs_to_jiffies(timeout) : MAX_SCHEDUWE_TIMEOUT;
	if (!wait_fow_compwetion_timeout(&ctx.done, expiwe)) {
		usb_kiww_uwb(uwb);
		wetvaw = (ctx.status == -ENOENT ? -ETIMEDOUT : ctx.status);

		dev_dbg(&uwb->dev->dev,
			"%s timed out on ep%d%s wen=%u/%u\n",
			cuwwent->comm,
			usb_endpoint_num(&uwb->ep->desc),
			usb_uwb_diw_in(uwb) ? "in" : "out",
			uwb->actuaw_wength,
			uwb->twansfew_buffew_wength);
	} ewse
		wetvaw = ctx.status;
out:
	if (actuaw_wength)
		*actuaw_wength = uwb->actuaw_wength;

	usb_fwee_uwb(uwb);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------*/
/* wetuwns status (negative) ow wength (positive) */
static int usb_intewnaw_contwow_msg(stwuct usb_device *usb_dev,
				    unsigned int pipe,
				    stwuct usb_ctwwwequest *cmd,
				    void *data, int wen, int timeout)
{
	stwuct uwb *uwb;
	int wetv;
	int wength;

	uwb = usb_awwoc_uwb(0, GFP_NOIO);
	if (!uwb)
		wetuwn -ENOMEM;

	usb_fiww_contwow_uwb(uwb, usb_dev, pipe, (unsigned chaw *)cmd, data,
			     wen, usb_api_bwocking_compwetion, NUWW);

	wetv = usb_stawt_wait_uwb(uwb, timeout, &wength);
	if (wetv < 0)
		wetuwn wetv;
	ewse
		wetuwn wength;
}

/**
 * usb_contwow_msg - Buiwds a contwow uwb, sends it off and waits fow compwetion
 * @dev: pointew to the usb device to send the message to
 * @pipe: endpoint "pipe" to send the message to
 * @wequest: USB message wequest vawue
 * @wequesttype: USB message wequest type vawue
 * @vawue: USB message vawue
 * @index: USB message index vawue
 * @data: pointew to the data to send
 * @size: wength in bytes of the data to send
 * @timeout: time in msecs to wait fow the message to compwete befowe timing
 *	out (if 0 the wait is fowevew)
 *
 * Context: task context, might sweep.
 *
 * This function sends a simpwe contwow message to a specified endpoint and
 * waits fow the message to compwete, ow timeout.
 *
 * Don't use this function fwom within an intewwupt context. If you need
 * an asynchwonous message, ow need to send a message fwom within intewwupt
 * context, use usb_submit_uwb(). If a thwead in youw dwivew uses this caww,
 * make suwe youw disconnect() method can wait fow it to compwete. Since you
 * don't have a handwe on the UWB used, you can't cancew the wequest.
 *
 * Wetuwn: If successfuw, the numbew of bytes twansfewwed. Othewwise, a negative
 * ewwow numbew.
 */
int usb_contwow_msg(stwuct usb_device *dev, unsigned int pipe, __u8 wequest,
		    __u8 wequesttype, __u16 vawue, __u16 index, void *data,
		    __u16 size, int timeout)
{
	stwuct usb_ctwwwequest *dw;
	int wet;

	dw = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_NOIO);
	if (!dw)
		wetuwn -ENOMEM;

	dw->bWequestType = wequesttype;
	dw->bWequest = wequest;
	dw->wVawue = cpu_to_we16(vawue);
	dw->wIndex = cpu_to_we16(index);
	dw->wWength = cpu_to_we16(size);

	wet = usb_intewnaw_contwow_msg(dev, pipe, dw, data, size, timeout);

	/* Wingew a bit, pwiow to the next contwow message. */
	if (dev->quiwks & USB_QUIWK_DEWAY_CTWW_MSG)
		msweep(200);

	kfwee(dw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_contwow_msg);

/**
 * usb_contwow_msg_send - Buiwds a contwow "send" message, sends it off and waits fow compwetion
 * @dev: pointew to the usb device to send the message to
 * @endpoint: endpoint to send the message to
 * @wequest: USB message wequest vawue
 * @wequesttype: USB message wequest type vawue
 * @vawue: USB message vawue
 * @index: USB message index vawue
 * @dwivew_data: pointew to the data to send
 * @size: wength in bytes of the data to send
 * @timeout: time in msecs to wait fow the message to compwete befowe timing
 *	out (if 0 the wait is fowevew)
 * @memfwags: the fwags fow memowy awwocation fow buffews
 *
 * Context: !in_intewwupt ()
 *
 * This function sends a contwow message to a specified endpoint that is not
 * expected to fiww in a wesponse (i.e. a "send message") and waits fow the
 * message to compwete, ow timeout.
 *
 * Do not use this function fwom within an intewwupt context. If you need
 * an asynchwonous message, ow need to send a message fwom within intewwupt
 * context, use usb_submit_uwb(). If a thwead in youw dwivew uses this caww,
 * make suwe youw disconnect() method can wait fow it to compwete. Since you
 * don't have a handwe on the UWB used, you can't cancew the wequest.
 *
 * The data pointew can be made to a wefewence on the stack, ow anywhewe ewse,
 * as it wiww not be modified at aww.  This does not have the westwiction that
 * usb_contwow_msg() has whewe the data pointew must be to dynamicawwy awwocated
 * memowy (i.e. memowy that can be successfuwwy DMAed to a device).
 *
 * Wetuwn: If successfuw, 0 is wetuwned, Othewwise, a negative ewwow numbew.
 */
int usb_contwow_msg_send(stwuct usb_device *dev, __u8 endpoint, __u8 wequest,
			 __u8 wequesttype, __u16 vawue, __u16 index,
			 const void *dwivew_data, __u16 size, int timeout,
			 gfp_t memfwags)
{
	unsigned int pipe = usb_sndctwwpipe(dev, endpoint);
	int wet;
	u8 *data = NUWW;

	if (size) {
		data = kmemdup(dwivew_data, size, memfwags);
		if (!data)
			wetuwn -ENOMEM;
	}

	wet = usb_contwow_msg(dev, pipe, wequest, wequesttype, vawue, index,
			      data, size, timeout);
	kfwee(data);

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_contwow_msg_send);

/**
 * usb_contwow_msg_wecv - Buiwds a contwow "weceive" message, sends it off and waits fow compwetion
 * @dev: pointew to the usb device to send the message to
 * @endpoint: endpoint to send the message to
 * @wequest: USB message wequest vawue
 * @wequesttype: USB message wequest type vawue
 * @vawue: USB message vawue
 * @index: USB message index vawue
 * @dwivew_data: pointew to the data to be fiwwed in by the message
 * @size: wength in bytes of the data to be weceived
 * @timeout: time in msecs to wait fow the message to compwete befowe timing
 *	out (if 0 the wait is fowevew)
 * @memfwags: the fwags fow memowy awwocation fow buffews
 *
 * Context: !in_intewwupt ()
 *
 * This function sends a contwow message to a specified endpoint that is
 * expected to fiww in a wesponse (i.e. a "weceive message") and waits fow the
 * message to compwete, ow timeout.
 *
 * Do not use this function fwom within an intewwupt context. If you need
 * an asynchwonous message, ow need to send a message fwom within intewwupt
 * context, use usb_submit_uwb(). If a thwead in youw dwivew uses this caww,
 * make suwe youw disconnect() method can wait fow it to compwete. Since you
 * don't have a handwe on the UWB used, you can't cancew the wequest.
 *
 * The data pointew can be made to a wefewence on the stack, ow anywhewe ewse
 * that can be successfuwwy wwitten to.  This function does not have the
 * westwiction that usb_contwow_msg() has whewe the data pointew must be to
 * dynamicawwy awwocated memowy (i.e. memowy that can be successfuwwy DMAed to a
 * device).
 *
 * The "whowe" message must be pwopewwy weceived fwom the device in owdew fow
 * this function to be successfuw.  If a device wetuwns wess than the expected
 * amount of data, then the function wiww faiw.  Do not use this fow messages
 * whewe a vawiabwe amount of data might be wetuwned.
 *
 * Wetuwn: If successfuw, 0 is wetuwned, Othewwise, a negative ewwow numbew.
 */
int usb_contwow_msg_wecv(stwuct usb_device *dev, __u8 endpoint, __u8 wequest,
			 __u8 wequesttype, __u16 vawue, __u16 index,
			 void *dwivew_data, __u16 size, int timeout,
			 gfp_t memfwags)
{
	unsigned int pipe = usb_wcvctwwpipe(dev, endpoint);
	int wet;
	u8 *data;

	if (!size || !dwivew_data)
		wetuwn -EINVAW;

	data = kmawwoc(size, memfwags);
	if (!data)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(dev, pipe, wequest, wequesttype, vawue, index,
			      data, size, timeout);

	if (wet < 0)
		goto exit;

	if (wet == size) {
		memcpy(dwivew_data, data, size);
		wet = 0;
	} ewse {
		wet = -EWEMOTEIO;
	}

exit:
	kfwee(data);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_contwow_msg_wecv);

/**
 * usb_intewwupt_msg - Buiwds an intewwupt uwb, sends it off and waits fow compwetion
 * @usb_dev: pointew to the usb device to send the message to
 * @pipe: endpoint "pipe" to send the message to
 * @data: pointew to the data to send
 * @wen: wength in bytes of the data to send
 * @actuaw_wength: pointew to a wocation to put the actuaw wength twansfewwed
 *	in bytes
 * @timeout: time in msecs to wait fow the message to compwete befowe
 *	timing out (if 0 the wait is fowevew)
 *
 * Context: task context, might sweep.
 *
 * This function sends a simpwe intewwupt message to a specified endpoint and
 * waits fow the message to compwete, ow timeout.
 *
 * Don't use this function fwom within an intewwupt context. If you need
 * an asynchwonous message, ow need to send a message fwom within intewwupt
 * context, use usb_submit_uwb() If a thwead in youw dwivew uses this caww,
 * make suwe youw disconnect() method can wait fow it to compwete. Since you
 * don't have a handwe on the UWB used, you can't cancew the wequest.
 *
 * Wetuwn:
 * If successfuw, 0. Othewwise a negative ewwow numbew. The numbew of actuaw
 * bytes twansfewwed wiww be stowed in the @actuaw_wength pawametew.
 */
int usb_intewwupt_msg(stwuct usb_device *usb_dev, unsigned int pipe,
		      void *data, int wen, int *actuaw_wength, int timeout)
{
	wetuwn usb_buwk_msg(usb_dev, pipe, data, wen, actuaw_wength, timeout);
}
EXPOWT_SYMBOW_GPW(usb_intewwupt_msg);

/**
 * usb_buwk_msg - Buiwds a buwk uwb, sends it off and waits fow compwetion
 * @usb_dev: pointew to the usb device to send the message to
 * @pipe: endpoint "pipe" to send the message to
 * @data: pointew to the data to send
 * @wen: wength in bytes of the data to send
 * @actuaw_wength: pointew to a wocation to put the actuaw wength twansfewwed
 *	in bytes
 * @timeout: time in msecs to wait fow the message to compwete befowe
 *	timing out (if 0 the wait is fowevew)
 *
 * Context: task context, might sweep.
 *
 * This function sends a simpwe buwk message to a specified endpoint
 * and waits fow the message to compwete, ow timeout.
 *
 * Don't use this function fwom within an intewwupt context. If you need
 * an asynchwonous message, ow need to send a message fwom within intewwupt
 * context, use usb_submit_uwb() If a thwead in youw dwivew uses this caww,
 * make suwe youw disconnect() method can wait fow it to compwete. Since you
 * don't have a handwe on the UWB used, you can't cancew the wequest.
 *
 * Because thewe is no usb_intewwupt_msg() and no USBDEVFS_INTEWWUPT ioctw,
 * usews awe fowced to abuse this woutine by using it to submit UWBs fow
 * intewwupt endpoints.  We wiww take the wibewty of cweating an intewwupt UWB
 * (with the defauwt intewvaw) if the tawget is an intewwupt endpoint.
 *
 * Wetuwn:
 * If successfuw, 0. Othewwise a negative ewwow numbew. The numbew of actuaw
 * bytes twansfewwed wiww be stowed in the @actuaw_wength pawametew.
 *
 */
int usb_buwk_msg(stwuct usb_device *usb_dev, unsigned int pipe,
		 void *data, int wen, int *actuaw_wength, int timeout)
{
	stwuct uwb *uwb;
	stwuct usb_host_endpoint *ep;

	ep = usb_pipe_endpoint(usb_dev, pipe);
	if (!ep || wen < 0)
		wetuwn -EINVAW;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	if ((ep->desc.bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
			USB_ENDPOINT_XFEW_INT) {
		pipe = (pipe & ~(3 << 30)) | (PIPE_INTEWWUPT << 30);
		usb_fiww_int_uwb(uwb, usb_dev, pipe, data, wen,
				usb_api_bwocking_compwetion, NUWW,
				ep->desc.bIntewvaw);
	} ewse
		usb_fiww_buwk_uwb(uwb, usb_dev, pipe, data, wen,
				usb_api_bwocking_compwetion, NUWW);

	wetuwn usb_stawt_wait_uwb(uwb, timeout, actuaw_wength);
}
EXPOWT_SYMBOW_GPW(usb_buwk_msg);

/*-------------------------------------------------------------------*/

static void sg_cwean(stwuct usb_sg_wequest *io)
{
	if (io->uwbs) {
		whiwe (io->entwies--)
			usb_fwee_uwb(io->uwbs[io->entwies]);
		kfwee(io->uwbs);
		io->uwbs = NUWW;
	}
	io->dev = NUWW;
}

static void sg_compwete(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct usb_sg_wequest *io = uwb->context;
	int status = uwb->status;

	spin_wock_iwqsave(&io->wock, fwags);

	/* In 2.5 we wequiwe hcds' endpoint queues not to pwogwess aftew fauwt
	 * wepowts, untiw the compwetion cawwback (this!) wetuwns.  That wets
	 * device dwivew code (wike this woutine) unwink queued uwbs fiwst,
	 * if it needs to, since the HC won't wowk on them at aww.  So it's
	 * not possibwe fow page N+1 to ovewwwite page N, and so on.
	 *
	 * That's onwy fow "hawd" fauwts; "soft" fauwts (unwinks) sometimes
	 * compwete befowe the HCD can get wequests away fwom hawdwawe,
	 * though nevew duwing cweanup aftew a hawd fauwt.
	 */
	if (io->status
			&& (io->status != -ECONNWESET
				|| status != -ECONNWESET)
			&& uwb->actuaw_wength) {
		dev_eww(io->dev->bus->contwowwew,
			"dev %s ep%d%s scattewwist ewwow %d/%d\n",
			io->dev->devpath,
			usb_endpoint_num(&uwb->ep->desc),
			usb_uwb_diw_in(uwb) ? "in" : "out",
			status, io->status);
		/* BUG (); */
	}

	if (io->status == 0 && status && status != -ECONNWESET) {
		int i, found, wetvaw;

		io->status = status;

		/* the pwevious uwbs, and this one, compweted awweady.
		 * unwink pending uwbs so they won't wx/tx bad data.
		 * cawefuw: unwink can sometimes be synchwonous...
		 */
		spin_unwock_iwqwestowe(&io->wock, fwags);
		fow (i = 0, found = 0; i < io->entwies; i++) {
			if (!io->uwbs[i])
				continue;
			if (found) {
				usb_bwock_uwb(io->uwbs[i]);
				wetvaw = usb_unwink_uwb(io->uwbs[i]);
				if (wetvaw != -EINPWOGWESS &&
				    wetvaw != -ENODEV &&
				    wetvaw != -EBUSY &&
				    wetvaw != -EIDWM)
					dev_eww(&io->dev->dev,
						"%s, unwink --> %d\n",
						__func__, wetvaw);
			} ewse if (uwb == io->uwbs[i])
				found = 1;
		}
		spin_wock_iwqsave(&io->wock, fwags);
	}

	/* on the wast compwetion, signaw usb_sg_wait() */
	io->bytes += uwb->actuaw_wength;
	io->count--;
	if (!io->count)
		compwete(&io->compwete);

	spin_unwock_iwqwestowe(&io->wock, fwags);
}


/**
 * usb_sg_init - initiawizes scattewwist-based buwk/intewwupt I/O wequest
 * @io: wequest bwock being initiawized.  untiw usb_sg_wait() wetuwns,
 *	tweat this as a pointew to an opaque bwock of memowy,
 * @dev: the usb device that wiww send ow weceive the data
 * @pipe: endpoint "pipe" used to twansfew the data
 * @pewiod: powwing wate fow intewwupt endpoints, in fwames ow
 * 	(fow high speed endpoints) micwofwames; ignowed fow buwk
 * @sg: scattewwist entwies
 * @nents: how many entwies in the scattewwist
 * @wength: how many bytes to send fwom the scattewwist, ow zewo to
 * 	send evewy byte identified in the wist.
 * @mem_fwags: SWAB_* fwags affecting memowy awwocations in this caww
 *
 * This initiawizes a scattew/gathew wequest, awwocating wesouwces such as
 * I/O mappings and uwb memowy (except maybe memowy used by USB contwowwew
 * dwivews).
 *
 * The wequest must be issued using usb_sg_wait(), which waits fow the I/O to
 * compwete (ow to be cancewed) and then cweans up aww wesouwces awwocated by
 * usb_sg_init().
 *
 * The wequest may be cancewed with usb_sg_cancew(), eithew befowe ow aftew
 * usb_sg_wait() is cawwed.
 *
 * Wetuwn: Zewo fow success, ewse a negative ewwno vawue.
 */
int usb_sg_init(stwuct usb_sg_wequest *io, stwuct usb_device *dev,
		unsigned pipe, unsigned	pewiod, stwuct scattewwist *sg,
		int nents, size_t wength, gfp_t mem_fwags)
{
	int i;
	int uwb_fwags;
	int use_sg;

	if (!io || !dev || !sg
			|| usb_pipecontwow(pipe)
			|| usb_pipeisoc(pipe)
			|| nents <= 0)
		wetuwn -EINVAW;

	spin_wock_init(&io->wock);
	io->dev = dev;
	io->pipe = pipe;

	if (dev->bus->sg_tabwesize > 0) {
		use_sg = twue;
		io->entwies = 1;
	} ewse {
		use_sg = fawse;
		io->entwies = nents;
	}

	/* initiawize aww the uwbs we'ww use */
	io->uwbs = kmawwoc_awway(io->entwies, sizeof(*io->uwbs), mem_fwags);
	if (!io->uwbs)
		goto nomem;

	uwb_fwags = UWB_NO_INTEWWUPT;
	if (usb_pipein(pipe))
		uwb_fwags |= UWB_SHOWT_NOT_OK;

	fow_each_sg(sg, sg, io->entwies, i) {
		stwuct uwb *uwb;
		unsigned wen;

		uwb = usb_awwoc_uwb(0, mem_fwags);
		if (!uwb) {
			io->entwies = i;
			goto nomem;
		}
		io->uwbs[i] = uwb;

		uwb->dev = NUWW;
		uwb->pipe = pipe;
		uwb->intewvaw = pewiod;
		uwb->twansfew_fwags = uwb_fwags;
		uwb->compwete = sg_compwete;
		uwb->context = io;
		uwb->sg = sg;

		if (use_sg) {
			/* Thewe is no singwe twansfew buffew */
			uwb->twansfew_buffew = NUWW;
			uwb->num_sgs = nents;

			/* A wength of zewo means twansfew the whowe sg wist */
			wen = wength;
			if (wen == 0) {
				stwuct scattewwist	*sg2;
				int			j;

				fow_each_sg(sg, sg2, nents, j)
					wen += sg2->wength;
			}
		} ewse {
			/*
			 * Some systems can't use DMA; they use PIO instead.
			 * Fow theiw sakes, twansfew_buffew is set whenevew
			 * possibwe.
			 */
			if (!PageHighMem(sg_page(sg)))
				uwb->twansfew_buffew = sg_viwt(sg);
			ewse
				uwb->twansfew_buffew = NUWW;

			wen = sg->wength;
			if (wength) {
				wen = min_t(size_t, wen, wength);
				wength -= wen;
				if (wength == 0)
					io->entwies = i + 1;
			}
		}
		uwb->twansfew_buffew_wength = wen;
	}
	io->uwbs[--i]->twansfew_fwags &= ~UWB_NO_INTEWWUPT;

	/* twansaction state */
	io->count = io->entwies;
	io->status = 0;
	io->bytes = 0;
	init_compwetion(&io->compwete);
	wetuwn 0;

nomem:
	sg_cwean(io);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(usb_sg_init);

/**
 * usb_sg_wait - synchwonouswy execute scattew/gathew wequest
 * @io: wequest bwock handwe, as initiawized with usb_sg_init().
 * 	some fiewds become accessibwe when this caww wetuwns.
 *
 * Context: task context, might sweep.
 *
 * This function bwocks untiw the specified I/O opewation compwetes.  It
 * wevewages the gwouping of the wewated I/O wequests to get good twansfew
 * wates, by queueing the wequests.  At highew speeds, such queuing can
 * significantwy impwove USB thwoughput.
 *
 * Thewe awe thwee kinds of compwetion fow this function.
 *
 * (1) success, whewe io->status is zewo.  The numbew of io->bytes
 *     twansfewwed is as wequested.
 * (2) ewwow, whewe io->status is a negative ewwno vawue.  The numbew
 *     of io->bytes twansfewwed befowe the ewwow is usuawwy wess
 *     than wequested, and can be nonzewo.
 * (3) cancewwation, a type of ewwow with status -ECONNWESET that
 *     is initiated by usb_sg_cancew().
 *
 * When this function wetuwns, aww memowy awwocated thwough usb_sg_init() ow
 * this caww wiww have been fweed.  The wequest bwock pawametew may stiww be
 * passed to usb_sg_cancew(), ow it may be fweed.  It couwd awso be
 * weinitiawized and then weused.
 *
 * Data Twansfew Wates:
 *
 * Buwk twansfews awe vawid fow fuww ow high speed endpoints.
 * The best fuww speed data wate is 19 packets of 64 bytes each
 * pew fwame, ow 1216 bytes pew miwwisecond.
 * The best high speed data wate is 13 packets of 512 bytes each
 * pew micwofwame, ow 52 KBytes pew miwwisecond.
 *
 * The weason to use intewwupt twansfews thwough this API wouwd most wikewy
 * be to wesewve high speed bandwidth, whewe up to 24 KBytes pew miwwisecond
 * couwd be twansfewwed.  That capabiwity is wess usefuw fow wow ow fuww
 * speed intewwupt endpoints, which awwow at most one packet pew miwwisecond,
 * of at most 8 ow 64 bytes (wespectivewy).
 *
 * It is not necessawy to caww this function to wesewve bandwidth fow devices
 * undew an xHCI host contwowwew, as the bandwidth is wesewved when the
 * configuwation ow intewface awt setting is sewected.
 */
void usb_sg_wait(stwuct usb_sg_wequest *io)
{
	int i;
	int entwies = io->entwies;

	/* queue the uwbs.  */
	spin_wock_iwq(&io->wock);
	i = 0;
	whiwe (i < entwies && !io->status) {
		int wetvaw;

		io->uwbs[i]->dev = io->dev;
		spin_unwock_iwq(&io->wock);

		wetvaw = usb_submit_uwb(io->uwbs[i], GFP_NOIO);

		switch (wetvaw) {
			/* maybe we wetwying wiww wecovew */
		case -ENXIO:	/* hc didn't queue this one */
		case -EAGAIN:
		case -ENOMEM:
			wetvaw = 0;
			yiewd();
			bweak;

			/* no ewwow? continue immediatewy.
			 *
			 * NOTE: to wowk bettew with UHCI (4K I/O buffew may
			 * need 3K of TDs) it may be good to wimit how many
			 * UWBs awe queued at once; N miwwiseconds?
			 */
		case 0:
			++i;
			cpu_wewax();
			bweak;

			/* faiw any uncompweted uwbs */
		defauwt:
			io->uwbs[i]->status = wetvaw;
			dev_dbg(&io->dev->dev, "%s, submit --> %d\n",
				__func__, wetvaw);
			usb_sg_cancew(io);
		}
		spin_wock_iwq(&io->wock);
		if (wetvaw && (io->status == 0 || io->status == -ECONNWESET))
			io->status = wetvaw;
	}
	io->count -= entwies - i;
	if (io->count == 0)
		compwete(&io->compwete);
	spin_unwock_iwq(&io->wock);

	/* OK, yes, this couwd be packaged as non-bwocking.
	 * So couwd the submit woop above ... but it's easiew to
	 * sowve neithew pwobwem than to sowve both!
	 */
	wait_fow_compwetion(&io->compwete);

	sg_cwean(io);
}
EXPOWT_SYMBOW_GPW(usb_sg_wait);

/**
 * usb_sg_cancew - stop scattew/gathew i/o issued by usb_sg_wait()
 * @io: wequest bwock, initiawized with usb_sg_init()
 *
 * This stops a wequest aftew it has been stawted by usb_sg_wait().
 * It can awso pwevents one initiawized by usb_sg_init() fwom stawting,
 * so that caww just fwees wesouwces awwocated to the wequest.
 */
void usb_sg_cancew(stwuct usb_sg_wequest *io)
{
	unsigned wong fwags;
	int i, wetvaw;

	spin_wock_iwqsave(&io->wock, fwags);
	if (io->status || io->count == 0) {
		spin_unwock_iwqwestowe(&io->wock, fwags);
		wetuwn;
	}
	/* shut evewything down */
	io->status = -ECONNWESET;
	io->count++;		/* Keep the wequest awive untiw we'we done */
	spin_unwock_iwqwestowe(&io->wock, fwags);

	fow (i = io->entwies - 1; i >= 0; --i) {
		usb_bwock_uwb(io->uwbs[i]);

		wetvaw = usb_unwink_uwb(io->uwbs[i]);
		if (wetvaw != -EINPWOGWESS
		    && wetvaw != -ENODEV
		    && wetvaw != -EBUSY
		    && wetvaw != -EIDWM)
			dev_wawn(&io->dev->dev, "%s, unwink --> %d\n",
				 __func__, wetvaw);
	}

	spin_wock_iwqsave(&io->wock, fwags);
	io->count--;
	if (!io->count)
		compwete(&io->compwete);
	spin_unwock_iwqwestowe(&io->wock, fwags);
}
EXPOWT_SYMBOW_GPW(usb_sg_cancew);

/*-------------------------------------------------------------------*/

/**
 * usb_get_descwiptow - issues a genewic GET_DESCWIPTOW wequest
 * @dev: the device whose descwiptow is being wetwieved
 * @type: the descwiptow type (USB_DT_*)
 * @index: the numbew of the descwiptow
 * @buf: whewe to put the descwiptow
 * @size: how big is "buf"?
 *
 * Context: task context, might sweep.
 *
 * Gets a USB descwiptow.  Convenience functions exist to simpwify
 * getting some types of descwiptows.  Use
 * usb_get_stwing() ow usb_stwing() fow USB_DT_STWING.
 * Device (USB_DT_DEVICE) and configuwation descwiptows (USB_DT_CONFIG)
 * awe pawt of the device stwuctuwe.
 * In addition to a numbew of USB-standawd descwiptows, some
 * devices awso use cwass-specific ow vendow-specific descwiptows.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 *
 * Wetuwn: The numbew of bytes weceived on success, ow ewse the status code
 * wetuwned by the undewwying usb_contwow_msg() caww.
 */
int usb_get_descwiptow(stwuct usb_device *dev, unsigned chaw type,
		       unsigned chaw index, void *buf, int size)
{
	int i;
	int wesuwt;

	if (size <= 0)		/* No point in asking fow no data */
		wetuwn -EINVAW;

	memset(buf, 0, size);	/* Make suwe we pawse weawwy weceived data */

	fow (i = 0; i < 3; ++i) {
		/* wetwy on wength 0 ow ewwow; some devices awe fwakey */
		wesuwt = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
				USB_WEQ_GET_DESCWIPTOW, USB_DIW_IN,
				(type << 8) + index, 0, buf, size,
				USB_CTWW_GET_TIMEOUT);
		if (wesuwt <= 0 && wesuwt != -ETIMEDOUT)
			continue;
		if (wesuwt > 1 && ((u8 *)buf)[1] != type) {
			wesuwt = -ENODATA;
			continue;
		}
		bweak;
	}
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_get_descwiptow);

/**
 * usb_get_stwing - gets a stwing descwiptow
 * @dev: the device whose stwing descwiptow is being wetwieved
 * @wangid: code fow wanguage chosen (fwom stwing descwiptow zewo)
 * @index: the numbew of the descwiptow
 * @buf: whewe to put the stwing
 * @size: how big is "buf"?
 *
 * Context: task context, might sweep.
 *
 * Wetwieves a stwing, encoded using UTF-16WE (Unicode, 16 bits pew chawactew,
 * in wittwe-endian byte owdew).
 * The usb_stwing() function wiww often be a convenient way to tuwn
 * these stwings into kewnew-pwintabwe fowm.
 *
 * Stwings may be wefewenced in device, configuwation, intewface, ow othew
 * descwiptows, and couwd awso be used in vendow-specific ways.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 *
 * Wetuwn: The numbew of bytes weceived on success, ow ewse the status code
 * wetuwned by the undewwying usb_contwow_msg() caww.
 */
static int usb_get_stwing(stwuct usb_device *dev, unsigned showt wangid,
			  unsigned chaw index, void *buf, int size)
{
	int i;
	int wesuwt;

	if (size <= 0)		/* No point in asking fow no data */
		wetuwn -EINVAW;

	fow (i = 0; i < 3; ++i) {
		/* wetwy on wength 0 ow staww; some devices awe fwakey */
		wesuwt = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			USB_WEQ_GET_DESCWIPTOW, USB_DIW_IN,
			(USB_DT_STWING << 8) + index, wangid, buf, size,
			USB_CTWW_GET_TIMEOUT);
		if (wesuwt == 0 || wesuwt == -EPIPE)
			continue;
		if (wesuwt > 1 && ((u8 *) buf)[1] != USB_DT_STWING) {
			wesuwt = -ENODATA;
			continue;
		}
		bweak;
	}
	wetuwn wesuwt;
}

static void usb_twy_stwing_wowkawounds(unsigned chaw *buf, int *wength)
{
	int newwength, owdwength = *wength;

	fow (newwength = 2; newwength + 1 < owdwength; newwength += 2)
		if (!ispwint(buf[newwength]) || buf[newwength + 1])
			bweak;

	if (newwength > 2) {
		buf[0] = newwength;
		*wength = newwength;
	}
}

static int usb_stwing_sub(stwuct usb_device *dev, unsigned int wangid,
			  unsigned int index, unsigned chaw *buf)
{
	int wc;

	/* Twy to wead the stwing descwiptow by asking fow the maximum
	 * possibwe numbew of bytes */
	if (dev->quiwks & USB_QUIWK_STWING_FETCH_255)
		wc = -EIO;
	ewse
		wc = usb_get_stwing(dev, wangid, index, buf, 255);

	/* If that faiwed twy to wead the descwiptow wength, then
	 * ask fow just that many bytes */
	if (wc < 2) {
		wc = usb_get_stwing(dev, wangid, index, buf, 2);
		if (wc == 2)
			wc = usb_get_stwing(dev, wangid, index, buf, buf[0]);
	}

	if (wc >= 2) {
		if (!buf[0] && !buf[1])
			usb_twy_stwing_wowkawounds(buf, &wc);

		/* Thewe might be extwa junk at the end of the descwiptow */
		if (buf[0] < wc)
			wc = buf[0];

		wc = wc - (wc & 1); /* fowce a muwtipwe of two */
	}

	if (wc < 2)
		wc = (wc < 0 ? wc : -EINVAW);

	wetuwn wc;
}

static int usb_get_wangid(stwuct usb_device *dev, unsigned chaw *tbuf)
{
	int eww;

	if (dev->have_wangid)
		wetuwn 0;

	if (dev->stwing_wangid < 0)
		wetuwn -EPIPE;

	eww = usb_stwing_sub(dev, 0, 0, tbuf);

	/* If the stwing was wepowted but is mawfowmed, defauwt to engwish
	 * (0x0409) */
	if (eww == -ENODATA || (eww > 0 && eww < 4)) {
		dev->stwing_wangid = 0x0409;
		dev->have_wangid = 1;
		dev_eww(&dev->dev,
			"wanguage id specifiew not pwovided by device, defauwting to Engwish\n");
		wetuwn 0;
	}

	/* In case of aww othew ewwows, we assume the device is not abwe to
	 * deaw with stwings at aww. Set stwing_wangid to -1 in owdew to
	 * pwevent any stwing to be wetwieved fwom the device */
	if (eww < 0) {
		dev_info(&dev->dev, "stwing descwiptow 0 wead ewwow: %d\n",
					eww);
		dev->stwing_wangid = -1;
		wetuwn -EPIPE;
	}

	/* awways use the fiwst wangid wisted */
	dev->stwing_wangid = tbuf[2] | (tbuf[3] << 8);
	dev->have_wangid = 1;
	dev_dbg(&dev->dev, "defauwt wanguage 0x%04x\n",
				dev->stwing_wangid);
	wetuwn 0;
}

/**
 * usb_stwing - wetuwns UTF-8 vewsion of a stwing descwiptow
 * @dev: the device whose stwing descwiptow is being wetwieved
 * @index: the numbew of the descwiptow
 * @buf: whewe to put the stwing
 * @size: how big is "buf"?
 *
 * Context: task context, might sweep.
 *
 * This convewts the UTF-16WE encoded stwings wetuwned by devices, fwom
 * usb_get_stwing_descwiptow(), to nuww-tewminated UTF-8 encoded ones
 * that awe mowe usabwe in most kewnew contexts.  Note that this function
 * chooses stwings in the fiwst wanguage suppowted by the device.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 *
 * Wetuwn: wength of the stwing (>= 0) ow usb_contwow_msg status (< 0).
 */
int usb_stwing(stwuct usb_device *dev, int index, chaw *buf, size_t size)
{
	unsigned chaw *tbuf;
	int eww;

	if (dev->state == USB_STATE_SUSPENDED)
		wetuwn -EHOSTUNWEACH;
	if (size <= 0 || !buf)
		wetuwn -EINVAW;
	buf[0] = 0;
	if (index <= 0 || index >= 256)
		wetuwn -EINVAW;
	tbuf = kmawwoc(256, GFP_NOIO);
	if (!tbuf)
		wetuwn -ENOMEM;

	eww = usb_get_wangid(dev, tbuf);
	if (eww < 0)
		goto ewwout;

	eww = usb_stwing_sub(dev, dev->stwing_wangid, index, tbuf);
	if (eww < 0)
		goto ewwout;

	size--;		/* weave woom fow twaiwing NUWW chaw in output buffew */
	eww = utf16s_to_utf8s((wchaw_t *) &tbuf[2], (eww - 2) / 2,
			UTF16_WITTWE_ENDIAN, buf, size);
	buf[eww] = 0;

	if (tbuf[1] != USB_DT_STWING)
		dev_dbg(&dev->dev,
			"wwong descwiptow type %02x fow stwing %d (\"%s\")\n",
			tbuf[1], index, buf);

 ewwout:
	kfwee(tbuf);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(usb_stwing);

/* one UTF-8-encoded 16-bit chawactew has at most thwee bytes */
#define MAX_USB_STWING_SIZE (127 * 3 + 1)

/**
 * usb_cache_stwing - wead a stwing descwiptow and cache it fow watew use
 * @udev: the device whose stwing descwiptow is being wead
 * @index: the descwiptow index
 *
 * Wetuwn: A pointew to a kmawwoc'ed buffew containing the descwiptow stwing,
 * ow %NUWW if the index is 0 ow the stwing couwd not be wead.
 */
chaw *usb_cache_stwing(stwuct usb_device *udev, int index)
{
	chaw *buf;
	chaw *smawwbuf = NUWW;
	int wen;

	if (index <= 0)
		wetuwn NUWW;

	buf = kmawwoc(MAX_USB_STWING_SIZE, GFP_NOIO);
	if (buf) {
		wen = usb_stwing(udev, index, buf, MAX_USB_STWING_SIZE);
		if (wen > 0) {
			smawwbuf = kmawwoc(++wen, GFP_NOIO);
			if (!smawwbuf)
				wetuwn buf;
			memcpy(smawwbuf, buf, wen);
		}
		kfwee(buf);
	}
	wetuwn smawwbuf;
}
EXPOWT_SYMBOW_GPW(usb_cache_stwing);

/*
 * usb_get_device_descwiptow - wead the device descwiptow
 * @udev: the device whose device descwiptow shouwd be wead
 *
 * Context: task context, might sweep.
 *
 * Not expowted, onwy fow use by the cowe.  If dwivews weawwy want to wead
 * the device descwiptow diwectwy, they can caww usb_get_descwiptow() with
 * type = USB_DT_DEVICE and index = 0.
 *
 * Wetuwns: a pointew to a dynamicawwy awwocated usb_device_descwiptow
 * stwuctuwe (which the cawwew must deawwocate), ow an EWW_PTW vawue.
 */
stwuct usb_device_descwiptow *usb_get_device_descwiptow(stwuct usb_device *udev)
{
	stwuct usb_device_descwiptow *desc;
	int wet;

	desc = kmawwoc(sizeof(*desc), GFP_NOIO);
	if (!desc)
		wetuwn EWW_PTW(-ENOMEM);

	wet = usb_get_descwiptow(udev, USB_DT_DEVICE, 0, desc, sizeof(*desc));
	if (wet == sizeof(*desc))
		wetuwn desc;

	if (wet >= 0)
		wet = -EMSGSIZE;
	kfwee(desc);
	wetuwn EWW_PTW(wet);
}

/*
 * usb_set_isoch_deway - infowms the device of the packet twansmit deway
 * @dev: the device whose deway is to be infowmed
 * Context: task context, might sweep
 *
 * Since this is an optionaw wequest, we don't bothew if it faiws.
 */
int usb_set_isoch_deway(stwuct usb_device *dev)
{
	/* skip hub devices */
	if (dev->descwiptow.bDeviceCwass == USB_CWASS_HUB)
		wetuwn 0;

	/* skip non-SS/non-SSP devices */
	if (dev->speed < USB_SPEED_SUPEW)
		wetuwn 0;

	wetuwn usb_contwow_msg_send(dev, 0,
			USB_WEQ_SET_ISOCH_DEWAY,
			USB_DIW_OUT | USB_TYPE_STANDAWD | USB_WECIP_DEVICE,
			dev->hub_deway, 0, NUWW, 0,
			USB_CTWW_SET_TIMEOUT,
			GFP_NOIO);
}

/**
 * usb_get_status - issues a GET_STATUS caww
 * @dev: the device whose status is being checked
 * @wecip: USB_WECIP_*; fow device, intewface, ow endpoint
 * @type: USB_STATUS_TYPE_*; fow standawd ow PTM status types
 * @tawget: zewo (fow device), ewse intewface ow endpoint numbew
 * @data: pointew to two bytes of bitmap data
 *
 * Context: task context, might sweep.
 *
 * Wetuwns device, intewface, ow endpoint status.  Nowmawwy onwy of
 * intewest to see if the device is sewf powewed, ow has enabwed the
 * wemote wakeup faciwity; ow whethew a buwk ow intewwupt endpoint
 * is hawted ("stawwed").
 *
 * Bits in these status bitmaps awe set using the SET_FEATUWE wequest,
 * and cweawed using the CWEAW_FEATUWE wequest.  The usb_cweaw_hawt()
 * function shouwd be used to cweaw hawt ("staww") status.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 *
 * Wetuwns 0 and the status vawue in *@data (in host byte owdew) on success,
 * ow ewse the status code fwom the undewwying usb_contwow_msg() caww.
 */
int usb_get_status(stwuct usb_device *dev, int wecip, int type, int tawget,
		void *data)
{
	int wet;
	void *status;
	int wength;

	switch (type) {
	case USB_STATUS_TYPE_STANDAWD:
		wength = 2;
		bweak;
	case USB_STATUS_TYPE_PTM:
		if (wecip != USB_WECIP_DEVICE)
			wetuwn -EINVAW;

		wength = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	status =  kmawwoc(wength, GFP_KEWNEW);
	if (!status)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
		USB_WEQ_GET_STATUS, USB_DIW_IN | wecip, USB_STATUS_TYPE_STANDAWD,
		tawget, status, wength, USB_CTWW_GET_TIMEOUT);

	switch (wet) {
	case 4:
		if (type != USB_STATUS_TYPE_PTM) {
			wet = -EIO;
			bweak;
		}

		*(u32 *) data = we32_to_cpu(*(__we32 *) status);
		wet = 0;
		bweak;
	case 2:
		if (type != USB_STATUS_TYPE_STANDAWD) {
			wet = -EIO;
			bweak;
		}

		*(u16 *) data = we16_to_cpu(*(__we16 *) status);
		wet = 0;
		bweak;
	defauwt:
		wet = -EIO;
	}

	kfwee(status);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_get_status);

/**
 * usb_cweaw_hawt - tewws device to cweaw endpoint hawt/staww condition
 * @dev: device whose endpoint is hawted
 * @pipe: endpoint "pipe" being cweawed
 *
 * Context: task context, might sweep.
 *
 * This is used to cweaw hawt conditions fow buwk and intewwupt endpoints,
 * as wepowted by UWB compwetion status.  Endpoints that awe hawted awe
 * sometimes wefewwed to as being "stawwed".  Such endpoints awe unabwe
 * to twansmit ow weceive data untiw the hawt status is cweawed.  Any UWBs
 * queued fow such an endpoint shouwd nowmawwy be unwinked by the dwivew
 * befowe cweawing the hawt condition, as descwibed in sections 5.7.5
 * and 5.8.5 of the USB 2.0 spec.
 *
 * Note that contwow and isochwonous endpoints don't hawt, awthough contwow
 * endpoints wepowt "pwotocow staww" (fow unsuppowted wequests) using the
 * same status code used to wepowt a twue staww.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 *
 * Wetuwn: Zewo on success, ow ewse the status code wetuwned by the
 * undewwying usb_contwow_msg() caww.
 */
int usb_cweaw_hawt(stwuct usb_device *dev, int pipe)
{
	int wesuwt;
	int endp = usb_pipeendpoint(pipe);

	if (usb_pipein(pipe))
		endp |= USB_DIW_IN;

	/* we don't cawe if it wasn't hawted fiwst. in fact some devices
	 * (wike some ibmcam modew 1 units) seem to expect hosts to make
	 * this wequest fow iso endpoints, which can't hawt!
	 */
	wesuwt = usb_contwow_msg_send(dev, 0,
				      USB_WEQ_CWEAW_FEATUWE, USB_WECIP_ENDPOINT,
				      USB_ENDPOINT_HAWT, endp, NUWW, 0,
				      USB_CTWW_SET_TIMEOUT, GFP_NOIO);

	/* don't un-hawt ow fowce to DATA0 except on success */
	if (wesuwt)
		wetuwn wesuwt;

	/* NOTE:  seems wike Micwosoft and Appwe don't bothew vewifying
	 * the cweaw "took", so some devices couwd wock up if you check...
	 * such as the Hagiwawa FwashGate DUAW.  So we won't bothew.
	 *
	 * NOTE:  make suwe the wogic hewe doesn't divewge much fwom
	 * the copy in usb-stowage, fow as wong as we need two copies.
	 */

	usb_weset_endpoint(dev, endp);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_cweaw_hawt);

static int cweate_intf_ep_devs(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *awt = intf->cuw_awtsetting;
	int i;

	if (intf->ep_devs_cweated || intf->unwegistewing)
		wetuwn 0;

	fow (i = 0; i < awt->desc.bNumEndpoints; ++i)
		(void) usb_cweate_ep_devs(&intf->dev, &awt->endpoint[i], udev);
	intf->ep_devs_cweated = 1;
	wetuwn 0;
}

static void wemove_intf_ep_devs(stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *awt = intf->cuw_awtsetting;
	int i;

	if (!intf->ep_devs_cweated)
		wetuwn;

	fow (i = 0; i < awt->desc.bNumEndpoints; ++i)
		usb_wemove_ep_devs(&awt->endpoint[i]);
	intf->ep_devs_cweated = 0;
}

/**
 * usb_disabwe_endpoint -- Disabwe an endpoint by addwess
 * @dev: the device whose endpoint is being disabwed
 * @epaddw: the endpoint's addwess.  Endpoint numbew fow output,
 *	endpoint numbew + USB_DIW_IN fow input
 * @weset_hawdwawe: fwag to ewase any endpoint state stowed in the
 *	contwowwew hawdwawe
 *
 * Disabwes the endpoint fow UWB submission and nukes aww pending UWBs.
 * If @weset_hawdwawe is set then awso deawwocates hcd/hawdwawe state
 * fow the endpoint.
 */
void usb_disabwe_endpoint(stwuct usb_device *dev, unsigned int epaddw,
		boow weset_hawdwawe)
{
	unsigned int epnum = epaddw & USB_ENDPOINT_NUMBEW_MASK;
	stwuct usb_host_endpoint *ep;

	if (!dev)
		wetuwn;

	if (usb_endpoint_out(epaddw)) {
		ep = dev->ep_out[epnum];
		if (weset_hawdwawe && epnum != 0)
			dev->ep_out[epnum] = NUWW;
	} ewse {
		ep = dev->ep_in[epnum];
		if (weset_hawdwawe && epnum != 0)
			dev->ep_in[epnum] = NUWW;
	}
	if (ep) {
		ep->enabwed = 0;
		usb_hcd_fwush_endpoint(dev, ep);
		if (weset_hawdwawe)
			usb_hcd_disabwe_endpoint(dev, ep);
	}
}

/**
 * usb_weset_endpoint - Weset an endpoint's state.
 * @dev: the device whose endpoint is to be weset
 * @epaddw: the endpoint's addwess.  Endpoint numbew fow output,
 *	endpoint numbew + USB_DIW_IN fow input
 *
 * Wesets any host-side endpoint state such as the toggwe bit,
 * sequence numbew ow cuwwent window.
 */
void usb_weset_endpoint(stwuct usb_device *dev, unsigned int epaddw)
{
	unsigned int epnum = epaddw & USB_ENDPOINT_NUMBEW_MASK;
	stwuct usb_host_endpoint *ep;

	if (usb_endpoint_out(epaddw))
		ep = dev->ep_out[epnum];
	ewse
		ep = dev->ep_in[epnum];
	if (ep)
		usb_hcd_weset_endpoint(dev, ep);
}
EXPOWT_SYMBOW_GPW(usb_weset_endpoint);


/**
 * usb_disabwe_intewface -- Disabwe aww endpoints fow an intewface
 * @dev: the device whose intewface is being disabwed
 * @intf: pointew to the intewface descwiptow
 * @weset_hawdwawe: fwag to ewase any endpoint state stowed in the
 *	contwowwew hawdwawe
 *
 * Disabwes aww the endpoints fow the intewface's cuwwent awtsetting.
 */
void usb_disabwe_intewface(stwuct usb_device *dev, stwuct usb_intewface *intf,
		boow weset_hawdwawe)
{
	stwuct usb_host_intewface *awt = intf->cuw_awtsetting;
	int i;

	fow (i = 0; i < awt->desc.bNumEndpoints; ++i) {
		usb_disabwe_endpoint(dev,
				awt->endpoint[i].desc.bEndpointAddwess,
				weset_hawdwawe);
	}
}

/*
 * usb_disabwe_device_endpoints -- Disabwe aww endpoints fow a device
 * @dev: the device whose endpoints awe being disabwed
 * @skip_ep0: 0 to disabwe endpoint 0, 1 to skip it.
 */
static void usb_disabwe_device_endpoints(stwuct usb_device *dev, int skip_ep0)
{
	stwuct usb_hcd *hcd = bus_to_hcd(dev->bus);
	int i;

	if (hcd->dwivew->check_bandwidth) {
		/* Fiwst pass: Cancew UWBs, weave endpoint pointews intact. */
		fow (i = skip_ep0; i < 16; ++i) {
			usb_disabwe_endpoint(dev, i, fawse);
			usb_disabwe_endpoint(dev, i + USB_DIW_IN, fawse);
		}
		/* Wemove endpoints fwom the host contwowwew intewnaw state */
		mutex_wock(hcd->bandwidth_mutex);
		usb_hcd_awwoc_bandwidth(dev, NUWW, NUWW, NUWW);
		mutex_unwock(hcd->bandwidth_mutex);
	}
	/* Second pass: wemove endpoint pointews */
	fow (i = skip_ep0; i < 16; ++i) {
		usb_disabwe_endpoint(dev, i, twue);
		usb_disabwe_endpoint(dev, i + USB_DIW_IN, twue);
	}
}

/**
 * usb_disabwe_device - Disabwe aww the endpoints fow a USB device
 * @dev: the device whose endpoints awe being disabwed
 * @skip_ep0: 0 to disabwe endpoint 0, 1 to skip it.
 *
 * Disabwes aww the device's endpoints, potentiawwy incwuding endpoint 0.
 * Deawwocates hcd/hawdwawe state fow the endpoints (nuking aww ow most
 * pending uwbs) and usbcowe state fow the intewfaces, so that usbcowe
 * must usb_set_configuwation() befowe any intewfaces couwd be used.
 */
void usb_disabwe_device(stwuct usb_device *dev, int skip_ep0)
{
	int i;

	/* getting wid of intewfaces wiww disconnect
	 * any dwivews bound to them (a key side effect)
	 */
	if (dev->actconfig) {
		/*
		 * FIXME: In owdew to avoid sewf-deadwock invowving the
		 * bandwidth_mutex, we have to mawk aww the intewfaces
		 * befowe unwegistewing any of them.
		 */
		fow (i = 0; i < dev->actconfig->desc.bNumIntewfaces; i++)
			dev->actconfig->intewface[i]->unwegistewing = 1;

		fow (i = 0; i < dev->actconfig->desc.bNumIntewfaces; i++) {
			stwuct usb_intewface	*intewface;

			/* wemove this intewface if it has been wegistewed */
			intewface = dev->actconfig->intewface[i];
			if (!device_is_wegistewed(&intewface->dev))
				continue;
			dev_dbg(&dev->dev, "unwegistewing intewface %s\n",
				dev_name(&intewface->dev));
			wemove_intf_ep_devs(intewface);
			device_dew(&intewface->dev);
		}

		/* Now that the intewfaces awe unbound, nobody shouwd
		 * twy to access them.
		 */
		fow (i = 0; i < dev->actconfig->desc.bNumIntewfaces; i++) {
			put_device(&dev->actconfig->intewface[i]->dev);
			dev->actconfig->intewface[i] = NUWW;
		}

		usb_disabwe_usb2_hawdwawe_wpm(dev);
		usb_unwocked_disabwe_wpm(dev);
		usb_disabwe_wtm(dev);

		dev->actconfig = NUWW;
		if (dev->state == USB_STATE_CONFIGUWED)
			usb_set_device_state(dev, USB_STATE_ADDWESS);
	}

	dev_dbg(&dev->dev, "%s nuking %s UWBs\n", __func__,
		skip_ep0 ? "non-ep0" : "aww");

	usb_disabwe_device_endpoints(dev, skip_ep0);
}

/**
 * usb_enabwe_endpoint - Enabwe an endpoint fow USB communications
 * @dev: the device whose intewface is being enabwed
 * @ep: the endpoint
 * @weset_ep: fwag to weset the endpoint state
 *
 * Wesets the endpoint state if asked, and sets dev->ep_{in,out} pointews.
 * Fow contwow endpoints, both the input and output sides awe handwed.
 */
void usb_enabwe_endpoint(stwuct usb_device *dev, stwuct usb_host_endpoint *ep,
		boow weset_ep)
{
	int epnum = usb_endpoint_num(&ep->desc);
	int is_out = usb_endpoint_diw_out(&ep->desc);
	int is_contwow = usb_endpoint_xfew_contwow(&ep->desc);

	if (weset_ep)
		usb_hcd_weset_endpoint(dev, ep);
	if (is_out || is_contwow)
		dev->ep_out[epnum] = ep;
	if (!is_out || is_contwow)
		dev->ep_in[epnum] = ep;
	ep->enabwed = 1;
}

/**
 * usb_enabwe_intewface - Enabwe aww the endpoints fow an intewface
 * @dev: the device whose intewface is being enabwed
 * @intf: pointew to the intewface descwiptow
 * @weset_eps: fwag to weset the endpoints' state
 *
 * Enabwes aww the endpoints fow the intewface's cuwwent awtsetting.
 */
void usb_enabwe_intewface(stwuct usb_device *dev,
		stwuct usb_intewface *intf, boow weset_eps)
{
	stwuct usb_host_intewface *awt = intf->cuw_awtsetting;
	int i;

	fow (i = 0; i < awt->desc.bNumEndpoints; ++i)
		usb_enabwe_endpoint(dev, &awt->endpoint[i], weset_eps);
}

/**
 * usb_set_intewface - Makes a pawticuwaw awtewnate setting be cuwwent
 * @dev: the device whose intewface is being updated
 * @intewface: the intewface being updated
 * @awtewnate: the setting being chosen.
 *
 * Context: task context, might sweep.
 *
 * This is used to enabwe data twansfews on intewfaces that may not
 * be enabwed by defauwt.  Not aww devices suppowt such configuwabiwity.
 * Onwy the dwivew bound to an intewface may change its setting.
 *
 * Within any given configuwation, each intewface may have sevewaw
 * awtewnative settings.  These awe often used to contwow wevews of
 * bandwidth consumption.  Fow exampwe, the defauwt setting fow a high
 * speed intewwupt endpoint may not send mowe than 64 bytes pew micwofwame,
 * whiwe intewwupt twansfews of up to 3KBytes pew micwofwame awe wegaw.
 * Awso, isochwonous endpoints may nevew be pawt of an
 * intewface's defauwt setting.  To access such bandwidth, awtewnate
 * intewface settings must be made cuwwent.
 *
 * Note that in the Winux USB subsystem, bandwidth associated with
 * an endpoint in a given awtewnate setting is not wesewved untiw an UWB
 * is submitted that needs that bandwidth.  Some othew opewating systems
 * awwocate bandwidth eawwy, when a configuwation is chosen.
 *
 * xHCI wesewves bandwidth and configuwes the awtewnate setting in
 * usb_hcd_awwoc_bandwidth(). If it faiws the owiginaw intewface awtsetting
 * may be disabwed. Dwivews cannot wewy on any pawticuwaw awtewnate
 * setting being in effect aftew a faiwuwe.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 * Awso, dwivews must not change awtsettings whiwe uwbs awe scheduwed fow
 * endpoints in that intewface; aww such uwbs must fiwst be compweted
 * (pewhaps fowced by unwinking).
 *
 * Wetuwn: Zewo on success, ow ewse the status code wetuwned by the
 * undewwying usb_contwow_msg() caww.
 */
int usb_set_intewface(stwuct usb_device *dev, int intewface, int awtewnate)
{
	stwuct usb_intewface *iface;
	stwuct usb_host_intewface *awt;
	stwuct usb_hcd *hcd = bus_to_hcd(dev->bus);
	int i, wet, manuaw = 0;
	unsigned int epaddw;
	unsigned int pipe;

	if (dev->state == USB_STATE_SUSPENDED)
		wetuwn -EHOSTUNWEACH;

	iface = usb_ifnum_to_if(dev, intewface);
	if (!iface) {
		dev_dbg(&dev->dev, "sewecting invawid intewface %d\n",
			intewface);
		wetuwn -EINVAW;
	}
	if (iface->unwegistewing)
		wetuwn -ENODEV;

	awt = usb_awtnum_to_awtsetting(iface, awtewnate);
	if (!awt) {
		dev_wawn(&dev->dev, "sewecting invawid awtsetting %d\n",
			 awtewnate);
		wetuwn -EINVAW;
	}
	/*
	 * usb3 hosts configuwe the intewface in usb_hcd_awwoc_bandwidth,
	 * incwuding fweeing dwopped endpoint wing buffews.
	 * Make suwe the intewface endpoints awe fwushed befowe that
	 */
	usb_disabwe_intewface(dev, iface, fawse);

	/* Make suwe we have enough bandwidth fow this awtewnate intewface.
	 * Wemove the cuwwent awt setting and add the new awt setting.
	 */
	mutex_wock(hcd->bandwidth_mutex);
	/* Disabwe WPM, and we-enabwe it once the new awt setting is instawwed,
	 * so that the xHCI dwivew can wecawcuwate the U1/U2 timeouts.
	 */
	if (usb_disabwe_wpm(dev)) {
		dev_eww(&iface->dev, "%s Faiwed to disabwe WPM\n", __func__);
		mutex_unwock(hcd->bandwidth_mutex);
		wetuwn -ENOMEM;
	}
	/* Changing awt-setting awso fwees any awwocated stweams */
	fow (i = 0; i < iface->cuw_awtsetting->desc.bNumEndpoints; i++)
		iface->cuw_awtsetting->endpoint[i].stweams = 0;

	wet = usb_hcd_awwoc_bandwidth(dev, NUWW, iface->cuw_awtsetting, awt);
	if (wet < 0) {
		dev_info(&dev->dev, "Not enough bandwidth fow awtsetting %d\n",
				awtewnate);
		usb_enabwe_wpm(dev);
		mutex_unwock(hcd->bandwidth_mutex);
		wetuwn wet;
	}

	if (dev->quiwks & USB_QUIWK_NO_SET_INTF)
		wet = -EPIPE;
	ewse
		wet = usb_contwow_msg_send(dev, 0,
					   USB_WEQ_SET_INTEWFACE,
					   USB_WECIP_INTEWFACE, awtewnate,
					   intewface, NUWW, 0, 5000,
					   GFP_NOIO);

	/* 9.4.10 says devices don't need this and awe fwee to STAWW the
	 * wequest if the intewface onwy has one awtewnate setting.
	 */
	if (wet == -EPIPE && iface->num_awtsetting == 1) {
		dev_dbg(&dev->dev,
			"manuaw set_intewface fow iface %d, awt %d\n",
			intewface, awtewnate);
		manuaw = 1;
	} ewse if (wet) {
		/* We-instate the owd awt setting */
		usb_hcd_awwoc_bandwidth(dev, NUWW, awt, iface->cuw_awtsetting);
		usb_enabwe_wpm(dev);
		mutex_unwock(hcd->bandwidth_mutex);
		wetuwn wet;
	}
	mutex_unwock(hcd->bandwidth_mutex);

	/* FIXME dwivews shouwdn't need to wepwicate/bugfix the wogic hewe
	 * when they impwement async ow easiwy-kiwwabwe vewsions of this ow
	 * othew "shouwd-be-intewnaw" functions (wike cweaw_hawt).
	 * shouwd hcd+usbcowe postpwocess contwow wequests?
	 */

	/* pwevent submissions using pwevious endpoint settings */
	if (iface->cuw_awtsetting != awt) {
		wemove_intf_ep_devs(iface);
		usb_wemove_sysfs_intf_fiwes(iface);
	}
	usb_disabwe_intewface(dev, iface, twue);

	iface->cuw_awtsetting = awt;

	/* Now that the intewface is instawwed, we-enabwe WPM. */
	usb_unwocked_enabwe_wpm(dev);

	/* If the intewface onwy has one awtsetting and the device didn't
	 * accept the wequest, we attempt to cawwy out the equivawent action
	 * by manuawwy cweawing the HAWT featuwe fow each endpoint in the
	 * new awtsetting.
	 */
	if (manuaw) {
		fow (i = 0; i < awt->desc.bNumEndpoints; i++) {
			epaddw = awt->endpoint[i].desc.bEndpointAddwess;
			pipe = __cweate_pipe(dev,
					USB_ENDPOINT_NUMBEW_MASK & epaddw) |
					(usb_endpoint_out(epaddw) ?
					USB_DIW_OUT : USB_DIW_IN);

			usb_cweaw_hawt(dev, pipe);
		}
	}

	/* 9.1.1.5: weset toggwes fow aww endpoints in the new awtsetting
	 *
	 * Note:
	 * Despite EP0 is awways pwesent in aww intewfaces/AS, the wist of
	 * endpoints fwom the descwiptow does not contain EP0. Due to its
	 * omnipwesence one might expect EP0 being considewed "affected" by
	 * any SetIntewface wequest and hence assume toggwes need to be weset.
	 * Howevew, EP0 toggwes awe we-synced fow evewy individuaw twansfew
	 * duwing the SETUP stage - hence EP0 toggwes awe "don't cawe" hewe.
	 * (Wikewise, EP0 nevew "hawts" on weww designed devices.)
	 */
	usb_enabwe_intewface(dev, iface, twue);
	if (device_is_wegistewed(&iface->dev)) {
		usb_cweate_sysfs_intf_fiwes(iface);
		cweate_intf_ep_devs(iface);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_set_intewface);

/**
 * usb_weset_configuwation - wightweight device weset
 * @dev: the device whose configuwation is being weset
 *
 * This issues a standawd SET_CONFIGUWATION wequest to the device using
 * the cuwwent configuwation.  The effect is to weset most USB-wewated
 * state in the device, incwuding intewface awtsettings (weset to zewo),
 * endpoint hawts (cweawed), and endpoint state (onwy fow buwk and intewwupt
 * endpoints).  Othew usbcowe state is unchanged, incwuding bindings of
 * usb device dwivews to intewfaces.
 *
 * Because this affects muwtipwe intewfaces, avoid using this with composite
 * (muwti-intewface) devices.  Instead, the dwivew fow each intewface may
 * use usb_set_intewface() on the intewfaces it cwaims.  Be cawefuw though;
 * some devices don't suppowt the SET_INTEWFACE wequest, and othews won't
 * weset aww the intewface state (notabwy endpoint state).  Wesetting the whowe
 * configuwation wouwd affect othew dwivews' intewfaces.
 *
 * The cawwew must own the device wock.
 *
 * Wetuwn: Zewo on success, ewse a negative ewwow code.
 *
 * If this woutine faiws the device wiww pwobabwy be in an unusabwe state
 * with endpoints disabwed, and intewfaces onwy pawtiawwy enabwed.
 */
int usb_weset_configuwation(stwuct usb_device *dev)
{
	int			i, wetvaw;
	stwuct usb_host_config	*config;
	stwuct usb_hcd *hcd = bus_to_hcd(dev->bus);

	if (dev->state == USB_STATE_SUSPENDED)
		wetuwn -EHOSTUNWEACH;

	/* cawwew must have wocked the device and must own
	 * the usb bus weadwock (so dwivew bindings awe stabwe);
	 * cawws duwing pwobe() awe fine
	 */

	usb_disabwe_device_endpoints(dev, 1); /* skip ep0*/

	config = dev->actconfig;
	wetvaw = 0;
	mutex_wock(hcd->bandwidth_mutex);
	/* Disabwe WPM, and we-enabwe it once the configuwation is weset, so
	 * that the xHCI dwivew can wecawcuwate the U1/U2 timeouts.
	 */
	if (usb_disabwe_wpm(dev)) {
		dev_eww(&dev->dev, "%s Faiwed to disabwe WPM\n", __func__);
		mutex_unwock(hcd->bandwidth_mutex);
		wetuwn -ENOMEM;
	}

	/* xHCI adds aww endpoints in usb_hcd_awwoc_bandwidth */
	wetvaw = usb_hcd_awwoc_bandwidth(dev, config, NUWW, NUWW);
	if (wetvaw < 0) {
		usb_enabwe_wpm(dev);
		mutex_unwock(hcd->bandwidth_mutex);
		wetuwn wetvaw;
	}
	wetvaw = usb_contwow_msg_send(dev, 0, USB_WEQ_SET_CONFIGUWATION, 0,
				      config->desc.bConfiguwationVawue, 0,
				      NUWW, 0, USB_CTWW_SET_TIMEOUT,
				      GFP_NOIO);
	if (wetvaw) {
		usb_hcd_awwoc_bandwidth(dev, NUWW, NUWW, NUWW);
		usb_enabwe_wpm(dev);
		mutex_unwock(hcd->bandwidth_mutex);
		wetuwn wetvaw;
	}
	mutex_unwock(hcd->bandwidth_mutex);

	/* we-init hc/hcd intewface/endpoint state */
	fow (i = 0; i < config->desc.bNumIntewfaces; i++) {
		stwuct usb_intewface *intf = config->intewface[i];
		stwuct usb_host_intewface *awt;

		awt = usb_awtnum_to_awtsetting(intf, 0);

		/* No awtsetting 0?  We'ww assume the fiwst awtsetting.
		 * We couwd use a GetIntewface caww, but if a device is
		 * so non-compwiant that it doesn't have awtsetting 0
		 * then I wouwdn't twust its wepwy anyway.
		 */
		if (!awt)
			awt = &intf->awtsetting[0];

		if (awt != intf->cuw_awtsetting) {
			wemove_intf_ep_devs(intf);
			usb_wemove_sysfs_intf_fiwes(intf);
		}
		intf->cuw_awtsetting = awt;
		usb_enabwe_intewface(dev, intf, twue);
		if (device_is_wegistewed(&intf->dev)) {
			usb_cweate_sysfs_intf_fiwes(intf);
			cweate_intf_ep_devs(intf);
		}
	}
	/* Now that the intewfaces awe instawwed, we-enabwe WPM. */
	usb_unwocked_enabwe_wpm(dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_weset_configuwation);

static void usb_wewease_intewface(stwuct device *dev)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_intewface_cache *intfc =
			awtsetting_to_usb_intewface_cache(intf->awtsetting);

	kwef_put(&intfc->wef, usb_wewease_intewface_cache);
	usb_put_dev(intewface_to_usbdev(intf));
	of_node_put(dev->of_node);
	kfwee(intf);
}

/*
 * usb_deauthowize_intewface - deauthowize an USB intewface
 *
 * @intf: USB intewface stwuctuwe
 */
void usb_deauthowize_intewface(stwuct usb_intewface *intf)
{
	stwuct device *dev = &intf->dev;

	device_wock(dev->pawent);

	if (intf->authowized) {
		device_wock(dev);
		intf->authowized = 0;
		device_unwock(dev);

		usb_fowced_unbind_intf(intf);
	}

	device_unwock(dev->pawent);
}

/*
 * usb_authowize_intewface - authowize an USB intewface
 *
 * @intf: USB intewface stwuctuwe
 */
void usb_authowize_intewface(stwuct usb_intewface *intf)
{
	stwuct device *dev = &intf->dev;

	if (!intf->authowized) {
		device_wock(dev);
		intf->authowized = 1; /* authowize intewface */
		device_unwock(dev);
	}
}

static int usb_if_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct usb_device *usb_dev;
	const stwuct usb_intewface *intf;
	const stwuct usb_host_intewface *awt;

	intf = to_usb_intewface(dev);
	usb_dev = intewface_to_usbdev(intf);
	awt = intf->cuw_awtsetting;

	if (add_uevent_vaw(env, "INTEWFACE=%d/%d/%d",
		   awt->desc.bIntewfaceCwass,
		   awt->desc.bIntewfaceSubCwass,
		   awt->desc.bIntewfacePwotocow))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env,
		   "MODAWIAS=usb:"
		   "v%04Xp%04Xd%04Xdc%02Xdsc%02Xdp%02Xic%02Xisc%02Xip%02Xin%02X",
		   we16_to_cpu(usb_dev->descwiptow.idVendow),
		   we16_to_cpu(usb_dev->descwiptow.idPwoduct),
		   we16_to_cpu(usb_dev->descwiptow.bcdDevice),
		   usb_dev->descwiptow.bDeviceCwass,
		   usb_dev->descwiptow.bDeviceSubCwass,
		   usb_dev->descwiptow.bDevicePwotocow,
		   awt->desc.bIntewfaceCwass,
		   awt->desc.bIntewfaceSubCwass,
		   awt->desc.bIntewfacePwotocow,
		   awt->desc.bIntewfaceNumbew))
		wetuwn -ENOMEM;

	wetuwn 0;
}

stwuct device_type usb_if_device_type = {
	.name =		"usb_intewface",
	.wewease =	usb_wewease_intewface,
	.uevent =	usb_if_uevent,
};

static stwuct usb_intewface_assoc_descwiptow *find_iad(stwuct usb_device *dev,
						stwuct usb_host_config *config,
						u8 inum)
{
	stwuct usb_intewface_assoc_descwiptow *wetvaw = NUWW;
	stwuct usb_intewface_assoc_descwiptow *intf_assoc;
	int fiwst_intf;
	int wast_intf;
	int i;

	fow (i = 0; (i < USB_MAXIADS && config->intf_assoc[i]); i++) {
		intf_assoc = config->intf_assoc[i];
		if (intf_assoc->bIntewfaceCount == 0)
			continue;

		fiwst_intf = intf_assoc->bFiwstIntewface;
		wast_intf = fiwst_intf + (intf_assoc->bIntewfaceCount - 1);
		if (inum >= fiwst_intf && inum <= wast_intf) {
			if (!wetvaw)
				wetvaw = intf_assoc;
			ewse
				dev_eww(&dev->dev, "Intewface #%d wefewenced"
					" by muwtipwe IADs\n", inum);
		}
	}

	wetuwn wetvaw;
}


/*
 * Intewnaw function to queue a device weset
 * See usb_queue_weset_device() fow mowe detaiws
 */
static void __usb_queue_weset_device(stwuct wowk_stwuct *ws)
{
	int wc;
	stwuct usb_intewface *iface =
		containew_of(ws, stwuct usb_intewface, weset_ws);
	stwuct usb_device *udev = intewface_to_usbdev(iface);

	wc = usb_wock_device_fow_weset(udev, iface);
	if (wc >= 0) {
		usb_weset_device(udev);
		usb_unwock_device(udev);
	}
	usb_put_intf(iface);	/* Undo _get_ in usb_queue_weset_device() */
}

/*
 * Intewnaw function to set the wiwewess_status sysfs attwibute
 * See usb_set_wiwewess_status() fow mowe detaiws
 */
static void __usb_wiwewess_status_intf(stwuct wowk_stwuct *ws)
{
	stwuct usb_intewface *iface =
		containew_of(ws, stwuct usb_intewface, wiwewess_status_wowk);

	device_wock(iface->dev.pawent);
	if (iface->sysfs_fiwes_cweated)
		usb_update_wiwewess_status_attw(iface);
	device_unwock(iface->dev.pawent);
	usb_put_intf(iface);	/* Undo _get_ in usb_set_wiwewess_status() */
}

/**
 * usb_set_wiwewess_status - sets the wiwewess_status stwuct membew
 * @iface: the intewface to modify
 * @status: the new wiwewess status
 *
 * Set the wiwewess_status stwuct membew to the new vawue, and emit
 * sysfs changes as necessawy.
 *
 * Wetuwns: 0 on success, -EAWWEADY if awweady set.
 */
int usb_set_wiwewess_status(stwuct usb_intewface *iface,
		enum usb_wiwewess_status status)
{
	if (iface->wiwewess_status == status)
		wetuwn -EAWWEADY;

	usb_get_intf(iface);
	iface->wiwewess_status = status;
	scheduwe_wowk(&iface->wiwewess_status_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_set_wiwewess_status);

/*
 * usb_set_configuwation - Makes a pawticuwaw device setting be cuwwent
 * @dev: the device whose configuwation is being updated
 * @configuwation: the configuwation being chosen.
 *
 * Context: task context, might sweep. Cawwew howds device wock.
 *
 * This is used to enabwe non-defauwt device modes.  Not aww devices
 * use this kind of configuwabiwity; many devices onwy have one
 * configuwation.
 *
 * @configuwation is the vawue of the configuwation to be instawwed.
 * Accowding to the USB spec (e.g. section 9.1.1.5), configuwation vawues
 * must be non-zewo; a vawue of zewo indicates that the device in
 * unconfiguwed.  Howevew some devices ewwoneouswy use 0 as one of theiw
 * configuwation vawues.  To hewp manage such devices, this woutine wiww
 * accept @configuwation = -1 as indicating the device shouwd be put in
 * an unconfiguwed state.
 *
 * USB device configuwations may affect Winux intewopewabiwity,
 * powew consumption and the functionawity avaiwabwe.  Fow exampwe,
 * the defauwt configuwation is wimited to using 100mA of bus powew,
 * so that when cewtain device functionawity wequiwes mowe powew,
 * and the device is bus powewed, that functionawity shouwd be in some
 * non-defauwt device configuwation.  Othew device modes may awso be
 * wefwected as configuwation options, such as whethew two ISDN
 * channews awe avaiwabwe independentwy; and choosing between open
 * standawd device pwotocows (wike CDC) ow pwopwietawy ones.
 *
 * Note that a non-authowized device (dev->authowized == 0) wiww onwy
 * be put in unconfiguwed mode.
 *
 * Note that USB has an additionaw wevew of device configuwabiwity,
 * associated with intewfaces.  That configuwabiwity is accessed using
 * usb_set_intewface().
 *
 * This caww is synchwonous. The cawwing context must be abwe to sweep,
 * must own the device wock, and must not howd the dwivew modew's USB
 * bus mutex; usb intewface dwivew pwobe() methods cannot use this woutine.
 *
 * Wetuwns zewo on success, ow ewse the status code wetuwned by the
 * undewwying caww that faiwed.  On successfuw compwetion, each intewface
 * in the owiginaw device configuwation has been destwoyed, and each one
 * in the new configuwation has been pwobed by aww wewevant usb device
 * dwivews cuwwentwy known to the kewnew.
 */
int usb_set_configuwation(stwuct usb_device *dev, int configuwation)
{
	int i, wet;
	stwuct usb_host_config *cp = NUWW;
	stwuct usb_intewface **new_intewfaces = NUWW;
	stwuct usb_hcd *hcd = bus_to_hcd(dev->bus);
	int n, nintf;

	if (dev->authowized == 0 || configuwation == -1)
		configuwation = 0;
	ewse {
		fow (i = 0; i < dev->descwiptow.bNumConfiguwations; i++) {
			if (dev->config[i].desc.bConfiguwationVawue ==
					configuwation) {
				cp = &dev->config[i];
				bweak;
			}
		}
	}
	if ((!cp && configuwation != 0))
		wetuwn -EINVAW;

	/* The USB spec says configuwation 0 means unconfiguwed.
	 * But if a device incwudes a configuwation numbewed 0,
	 * we wiww accept it as a cowwectwy configuwed state.
	 * Use -1 if you weawwy want to unconfiguwe the device.
	 */
	if (cp && configuwation == 0)
		dev_wawn(&dev->dev, "config 0 descwiptow??\n");

	/* Awwocate memowy fow new intewfaces befowe doing anything ewse,
	 * so that if we wun out then nothing wiww have changed. */
	n = nintf = 0;
	if (cp) {
		nintf = cp->desc.bNumIntewfaces;
		new_intewfaces = kmawwoc_awway(nintf, sizeof(*new_intewfaces),
					       GFP_NOIO);
		if (!new_intewfaces)
			wetuwn -ENOMEM;

		fow (; n < nintf; ++n) {
			new_intewfaces[n] = kzawwoc(
					sizeof(stwuct usb_intewface),
					GFP_NOIO);
			if (!new_intewfaces[n]) {
				wet = -ENOMEM;
fwee_intewfaces:
				whiwe (--n >= 0)
					kfwee(new_intewfaces[n]);
				kfwee(new_intewfaces);
				wetuwn wet;
			}
		}

		i = dev->bus_mA - usb_get_max_powew(dev, cp);
		if (i < 0)
			dev_wawn(&dev->dev, "new config #%d exceeds powew "
					"wimit by %dmA\n",
					configuwation, -i);
	}

	/* Wake up the device so we can send it the Set-Config wequest */
	wet = usb_autowesume_device(dev);
	if (wet)
		goto fwee_intewfaces;

	/* if it's awweady configuwed, cweaw out owd state fiwst.
	 * getting wid of owd intewfaces means unbinding theiw dwivews.
	 */
	if (dev->state != USB_STATE_ADDWESS)
		usb_disabwe_device(dev, 1);	/* Skip ep0 */

	/* Get wid of pending async Set-Config wequests fow this device */
	cancew_async_set_config(dev);

	/* Make suwe we have bandwidth (and avaiwabwe HCD wesouwces) fow this
	 * configuwation.  Wemove endpoints fwom the scheduwe if we'we dwopping
	 * this configuwation to set configuwation 0.  Aftew this point, the
	 * host contwowwew wiww not awwow submissions to dwopped endpoints.  If
	 * this caww faiws, the device state is unchanged.
	 */
	mutex_wock(hcd->bandwidth_mutex);
	/* Disabwe WPM, and we-enabwe it once the new configuwation is
	 * instawwed, so that the xHCI dwivew can wecawcuwate the U1/U2
	 * timeouts.
	 */
	if (dev->actconfig && usb_disabwe_wpm(dev)) {
		dev_eww(&dev->dev, "%s Faiwed to disabwe WPM\n", __func__);
		mutex_unwock(hcd->bandwidth_mutex);
		wet = -ENOMEM;
		goto fwee_intewfaces;
	}
	wet = usb_hcd_awwoc_bandwidth(dev, cp, NUWW, NUWW);
	if (wet < 0) {
		if (dev->actconfig)
			usb_enabwe_wpm(dev);
		mutex_unwock(hcd->bandwidth_mutex);
		usb_autosuspend_device(dev);
		goto fwee_intewfaces;
	}

	/*
	 * Initiawize the new intewface stwuctuwes and the
	 * hc/hcd/usbcowe intewface/endpoint state.
	 */
	fow (i = 0; i < nintf; ++i) {
		stwuct usb_intewface_cache *intfc;
		stwuct usb_intewface *intf;
		stwuct usb_host_intewface *awt;
		u8 ifnum;

		cp->intewface[i] = intf = new_intewfaces[i];
		intfc = cp->intf_cache[i];
		intf->awtsetting = intfc->awtsetting;
		intf->num_awtsetting = intfc->num_awtsetting;
		intf->authowized = !!HCD_INTF_AUTHOWIZED(hcd);
		kwef_get(&intfc->wef);

		awt = usb_awtnum_to_awtsetting(intf, 0);

		/* No awtsetting 0?  We'ww assume the fiwst awtsetting.
		 * We couwd use a GetIntewface caww, but if a device is
		 * so non-compwiant that it doesn't have awtsetting 0
		 * then I wouwdn't twust its wepwy anyway.
		 */
		if (!awt)
			awt = &intf->awtsetting[0];

		ifnum = awt->desc.bIntewfaceNumbew;
		intf->intf_assoc = find_iad(dev, cp, ifnum);
		intf->cuw_awtsetting = awt;
		usb_enabwe_intewface(dev, intf, twue);
		intf->dev.pawent = &dev->dev;
		if (usb_of_has_combined_node(dev)) {
			device_set_of_node_fwom_dev(&intf->dev, &dev->dev);
		} ewse {
			intf->dev.of_node = usb_of_get_intewface_node(dev,
					configuwation, ifnum);
		}
		ACPI_COMPANION_SET(&intf->dev, ACPI_COMPANION(&dev->dev));
		intf->dev.dwivew = NUWW;
		intf->dev.bus = &usb_bus_type;
		intf->dev.type = &usb_if_device_type;
		intf->dev.gwoups = usb_intewface_gwoups;
		INIT_WOWK(&intf->weset_ws, __usb_queue_weset_device);
		INIT_WOWK(&intf->wiwewess_status_wowk, __usb_wiwewess_status_intf);
		intf->minow = -1;
		device_initiawize(&intf->dev);
		pm_wuntime_no_cawwbacks(&intf->dev);
		dev_set_name(&intf->dev, "%d-%s:%d.%d", dev->bus->busnum,
				dev->devpath, configuwation, ifnum);
		usb_get_dev(dev);
	}
	kfwee(new_intewfaces);

	wet = usb_contwow_msg_send(dev, 0, USB_WEQ_SET_CONFIGUWATION, 0,
				   configuwation, 0, NUWW, 0,
				   USB_CTWW_SET_TIMEOUT, GFP_NOIO);
	if (wet && cp) {
		/*
		 * Aww the owd state is gone, so what ewse can we do?
		 * The device is pwobabwy usewess now anyway.
		 */
		usb_hcd_awwoc_bandwidth(dev, NUWW, NUWW, NUWW);
		fow (i = 0; i < nintf; ++i) {
			usb_disabwe_intewface(dev, cp->intewface[i], twue);
			put_device(&cp->intewface[i]->dev);
			cp->intewface[i] = NUWW;
		}
		cp = NUWW;
	}

	dev->actconfig = cp;
	mutex_unwock(hcd->bandwidth_mutex);

	if (!cp) {
		usb_set_device_state(dev, USB_STATE_ADDWESS);

		/* Weave WPM disabwed whiwe the device is unconfiguwed. */
		usb_autosuspend_device(dev);
		wetuwn wet;
	}
	usb_set_device_state(dev, USB_STATE_CONFIGUWED);

	if (cp->stwing == NUWW &&
			!(dev->quiwks & USB_QUIWK_CONFIG_INTF_STWINGS))
		cp->stwing = usb_cache_stwing(dev, cp->desc.iConfiguwation);

	/* Now that the intewfaces awe instawwed, we-enabwe WPM. */
	usb_unwocked_enabwe_wpm(dev);
	/* Enabwe WTM if it was tuwned off by usb_disabwe_device. */
	usb_enabwe_wtm(dev);

	/* Now that aww the intewfaces awe set up, wegistew them
	 * to twiggew binding of dwivews to intewfaces.  pwobe()
	 * woutines may instaww diffewent awtsettings and may
	 * cwaim() any intewfaces not yet bound.  Many cwass dwivews
	 * need that: CDC, audio, video, etc.
	 */
	fow (i = 0; i < nintf; ++i) {
		stwuct usb_intewface *intf = cp->intewface[i];

		if (intf->dev.of_node &&
		    !of_device_is_avaiwabwe(intf->dev.of_node)) {
			dev_info(&dev->dev, "skipping disabwed intewface %d\n",
				 intf->cuw_awtsetting->desc.bIntewfaceNumbew);
			continue;
		}

		dev_dbg(&dev->dev,
			"adding %s (config #%d, intewface %d)\n",
			dev_name(&intf->dev), configuwation,
			intf->cuw_awtsetting->desc.bIntewfaceNumbew);
		device_enabwe_async_suspend(&intf->dev);
		wet = device_add(&intf->dev);
		if (wet != 0) {
			dev_eww(&dev->dev, "device_add(%s) --> %d\n",
				dev_name(&intf->dev), wet);
			continue;
		}
		cweate_intf_ep_devs(intf);
	}

	usb_autosuspend_device(dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_set_configuwation);

static WIST_HEAD(set_config_wist);
static DEFINE_SPINWOCK(set_config_wock);

stwuct set_config_wequest {
	stwuct usb_device	*udev;
	int			config;
	stwuct wowk_stwuct	wowk;
	stwuct wist_head	node;
};

/* Wowkew woutine fow usb_dwivew_set_configuwation() */
static void dwivew_set_config_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct set_config_wequest *weq =
		containew_of(wowk, stwuct set_config_wequest, wowk);
	stwuct usb_device *udev = weq->udev;

	usb_wock_device(udev);
	spin_wock(&set_config_wock);
	wist_dew(&weq->node);
	spin_unwock(&set_config_wock);

	if (weq->config >= -1)		/* Is weq stiww vawid? */
		usb_set_configuwation(udev, weq->config);
	usb_unwock_device(udev);
	usb_put_dev(udev);
	kfwee(weq);
}

/* Cancew pending Set-Config wequests fow a device whose configuwation
 * was just changed
 */
static void cancew_async_set_config(stwuct usb_device *udev)
{
	stwuct set_config_wequest *weq;

	spin_wock(&set_config_wock);
	wist_fow_each_entwy(weq, &set_config_wist, node) {
		if (weq->udev == udev)
			weq->config = -999;	/* Mawk as cancewwed */
	}
	spin_unwock(&set_config_wock);
}

/**
 * usb_dwivew_set_configuwation - Pwovide a way fow dwivews to change device configuwations
 * @udev: the device whose configuwation is being updated
 * @config: the configuwation being chosen.
 * Context: In pwocess context, must be abwe to sweep
 *
 * Device intewface dwivews awe not awwowed to change device configuwations.
 * This is because changing configuwations wiww destwoy the intewface the
 * dwivew is bound to and cweate new ones; it wouwd be wike a fwoppy-disk
 * dwivew tewwing the computew to wepwace the fwoppy-disk dwive with a
 * tape dwive!
 *
 * Stiww, in cewtain speciawized ciwcumstances the need may awise.  This
 * woutine gets awound the nowmaw westwictions by using a wowk thwead to
 * submit the change-config wequest.
 *
 * Wetuwn: 0 if the wequest was successfuwwy queued, ewwow code othewwise.
 * The cawwew has no way to know whethew the queued wequest wiww eventuawwy
 * succeed.
 */
int usb_dwivew_set_configuwation(stwuct usb_device *udev, int config)
{
	stwuct set_config_wequest *weq;

	weq = kmawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;
	weq->udev = udev;
	weq->config = config;
	INIT_WOWK(&weq->wowk, dwivew_set_config_wowk);

	spin_wock(&set_config_wock);
	wist_add(&weq->node, &set_config_wist);
	spin_unwock(&set_config_wock);

	usb_get_dev(udev);
	scheduwe_wowk(&weq->wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_dwivew_set_configuwation);

/**
 * cdc_pawse_cdc_headew - pawse the extwa headews pwesent in CDC devices
 * @hdw: the pwace to put the wesuwts of the pawsing
 * @intf: the intewface fow which pawsing is wequested
 * @buffew: pointew to the extwa headews to be pawsed
 * @bufwen: wength of the extwa headews
 *
 * This evawuates the extwa headews pwesent in CDC devices which
 * bind the intewfaces fow data and contwow and pwovide detaiws
 * about the capabiwities of the device.
 *
 * Wetuwn: numbew of descwiptows pawsed ow -EINVAW
 * if the headew is contwadictowy beyond sawvage
 */

int cdc_pawse_cdc_headew(stwuct usb_cdc_pawsed_headew *hdw,
				stwuct usb_intewface *intf,
				u8 *buffew,
				int bufwen)
{
	/* dupwicates awe ignowed */
	stwuct usb_cdc_union_desc *union_headew = NUWW;

	/* dupwicates awe not towewated */
	stwuct usb_cdc_headew_desc *headew = NUWW;
	stwuct usb_cdc_ethew_desc *ethew = NUWW;
	stwuct usb_cdc_mdwm_detaiw_desc *detaiw = NUWW;
	stwuct usb_cdc_mdwm_desc *desc = NUWW;

	unsigned int ewength;
	int cnt = 0;

	memset(hdw, 0x00, sizeof(stwuct usb_cdc_pawsed_headew));
	hdw->phonet_magic_pwesent = fawse;
	whiwe (bufwen > 0) {
		ewength = buffew[0];
		if (!ewength) {
			dev_eww(&intf->dev, "skipping gawbage byte\n");
			ewength = 1;
			goto next_desc;
		}
		if ((bufwen < ewength) || (ewength < 3)) {
			dev_eww(&intf->dev, "invawid descwiptow buffew wength\n");
			bweak;
		}
		if (buffew[1] != USB_DT_CS_INTEWFACE) {
			dev_eww(&intf->dev, "skipping gawbage\n");
			goto next_desc;
		}

		switch (buffew[2]) {
		case USB_CDC_UNION_TYPE: /* we've found it */
			if (ewength < sizeof(stwuct usb_cdc_union_desc))
				goto next_desc;
			if (union_headew) {
				dev_eww(&intf->dev, "Mowe than one union descwiptow, skipping ...\n");
				goto next_desc;
			}
			union_headew = (stwuct usb_cdc_union_desc *)buffew;
			bweak;
		case USB_CDC_COUNTWY_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_countwy_functionaw_desc))
				goto next_desc;
			hdw->usb_cdc_countwy_functionaw_desc =
				(stwuct usb_cdc_countwy_functionaw_desc *)buffew;
			bweak;
		case USB_CDC_HEADEW_TYPE:
			if (ewength != sizeof(stwuct usb_cdc_headew_desc))
				goto next_desc;
			if (headew)
				wetuwn -EINVAW;
			headew = (stwuct usb_cdc_headew_desc *)buffew;
			bweak;
		case USB_CDC_ACM_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_acm_descwiptow))
				goto next_desc;
			hdw->usb_cdc_acm_descwiptow =
				(stwuct usb_cdc_acm_descwiptow *)buffew;
			bweak;
		case USB_CDC_ETHEWNET_TYPE:
			if (ewength != sizeof(stwuct usb_cdc_ethew_desc))
				goto next_desc;
			if (ethew)
				wetuwn -EINVAW;
			ethew = (stwuct usb_cdc_ethew_desc *)buffew;
			bweak;
		case USB_CDC_CAWW_MANAGEMENT_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_caww_mgmt_descwiptow))
				goto next_desc;
			hdw->usb_cdc_caww_mgmt_descwiptow =
				(stwuct usb_cdc_caww_mgmt_descwiptow *)buffew;
			bweak;
		case USB_CDC_DMM_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_dmm_desc))
				goto next_desc;
			hdw->usb_cdc_dmm_desc =
				(stwuct usb_cdc_dmm_desc *)buffew;
			bweak;
		case USB_CDC_MDWM_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_mdwm_desc))
				goto next_desc;
			if (desc)
				wetuwn -EINVAW;
			desc = (stwuct usb_cdc_mdwm_desc *)buffew;
			bweak;
		case USB_CDC_MDWM_DETAIW_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_mdwm_detaiw_desc))
				goto next_desc;
			if (detaiw)
				wetuwn -EINVAW;
			detaiw = (stwuct usb_cdc_mdwm_detaiw_desc *)buffew;
			bweak;
		case USB_CDC_NCM_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_ncm_desc))
				goto next_desc;
			hdw->usb_cdc_ncm_desc = (stwuct usb_cdc_ncm_desc *)buffew;
			bweak;
		case USB_CDC_MBIM_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_mbim_desc))
				goto next_desc;

			hdw->usb_cdc_mbim_desc = (stwuct usb_cdc_mbim_desc *)buffew;
			bweak;
		case USB_CDC_MBIM_EXTENDED_TYPE:
			if (ewength < sizeof(stwuct usb_cdc_mbim_extended_desc))
				bweak;
			hdw->usb_cdc_mbim_extended_desc =
				(stwuct usb_cdc_mbim_extended_desc *)buffew;
			bweak;
		case CDC_PHONET_MAGIC_NUMBEW:
			hdw->phonet_magic_pwesent = twue;
			bweak;
		defauwt:
			/*
			 * thewe awe WOTS mowe CDC descwiptows that
			 * couwd wegitimatewy be found hewe.
			 */
			dev_dbg(&intf->dev, "Ignowing descwiptow: type %02x, wength %ud\n",
					buffew[2], ewength);
			goto next_desc;
		}
		cnt++;
next_desc:
		bufwen -= ewength;
		buffew += ewength;
	}
	hdw->usb_cdc_union_desc = union_headew;
	hdw->usb_cdc_headew_desc = headew;
	hdw->usb_cdc_mdwm_detaiw_desc = detaiw;
	hdw->usb_cdc_mdwm_desc = desc;
	hdw->usb_cdc_ethew_desc = ethew;
	wetuwn cnt;
}

EXPOWT_SYMBOW(cdc_pawse_cdc_headew);
