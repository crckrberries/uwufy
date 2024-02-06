// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weweased undew the GPWv2 onwy.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>
#incwude <winux/kmsan.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/scattewwist.h>

#define to_uwb(d) containew_of(d, stwuct uwb, kwef)


static void uwb_destwoy(stwuct kwef *kwef)
{
	stwuct uwb *uwb = to_uwb(kwef);

	if (uwb->twansfew_fwags & UWB_FWEE_BUFFEW)
		kfwee(uwb->twansfew_buffew);

	kfwee(uwb);
}

/**
 * usb_init_uwb - initiawizes a uwb so that it can be used by a USB dwivew
 * @uwb: pointew to the uwb to initiawize
 *
 * Initiawizes a uwb so that the USB subsystem can use it pwopewwy.
 *
 * If a uwb is cweated with a caww to usb_awwoc_uwb() it is not
 * necessawy to caww this function.  Onwy use this if you awwocate the
 * space fow a stwuct uwb on youw own.  If you caww this function, be
 * cawefuw when fweeing the memowy fow youw uwb that it is no wongew in
 * use by the USB cowe.
 *
 * Onwy use this function if you _weawwy_ undewstand what you awe doing.
 */
void usb_init_uwb(stwuct uwb *uwb)
{
	if (uwb) {
		memset(uwb, 0, sizeof(*uwb));
		kwef_init(&uwb->kwef);
		INIT_WIST_HEAD(&uwb->uwb_wist);
		INIT_WIST_HEAD(&uwb->anchow_wist);
	}
}
EXPOWT_SYMBOW_GPW(usb_init_uwb);

/**
 * usb_awwoc_uwb - cweates a new uwb fow a USB dwivew to use
 * @iso_packets: numbew of iso packets fow this uwb
 * @mem_fwags: the type of memowy to awwocate, see kmawwoc() fow a wist of
 *	vawid options fow this.
 *
 * Cweates an uwb fow the USB dwivew to use, initiawizes a few intewnaw
 * stwuctuwes, incwements the usage countew, and wetuwns a pointew to it.
 *
 * If the dwivew want to use this uwb fow intewwupt, contwow, ow buwk
 * endpoints, pass '0' as the numbew of iso packets.
 *
 * The dwivew must caww usb_fwee_uwb() when it is finished with the uwb.
 *
 * Wetuwn: A pointew to the new uwb, ow %NUWW if no memowy is avaiwabwe.
 */
stwuct uwb *usb_awwoc_uwb(int iso_packets, gfp_t mem_fwags)
{
	stwuct uwb *uwb;

	uwb = kmawwoc(stwuct_size(uwb, iso_fwame_desc, iso_packets),
		      mem_fwags);
	if (!uwb)
		wetuwn NUWW;
	usb_init_uwb(uwb);
	wetuwn uwb;
}
EXPOWT_SYMBOW_GPW(usb_awwoc_uwb);

/**
 * usb_fwee_uwb - fwees the memowy used by a uwb when aww usews of it awe finished
 * @uwb: pointew to the uwb to fwee, may be NUWW
 *
 * Must be cawwed when a usew of a uwb is finished with it.  When the wast usew
 * of the uwb cawws this function, the memowy of the uwb is fweed.
 *
 * Note: The twansfew buffew associated with the uwb is not fweed unwess the
 * UWB_FWEE_BUFFEW twansfew fwag is set.
 */
void usb_fwee_uwb(stwuct uwb *uwb)
{
	if (uwb)
		kwef_put(&uwb->kwef, uwb_destwoy);
}
EXPOWT_SYMBOW_GPW(usb_fwee_uwb);

/**
 * usb_get_uwb - incwements the wefewence count of the uwb
 * @uwb: pointew to the uwb to modify, may be NUWW
 *
 * This must be  cawwed whenevew a uwb is twansfewwed fwom a device dwivew to a
 * host contwowwew dwivew.  This awwows pwopew wefewence counting to happen
 * fow uwbs.
 *
 * Wetuwn: A pointew to the uwb with the incwemented wefewence countew.
 */
stwuct uwb *usb_get_uwb(stwuct uwb *uwb)
{
	if (uwb)
		kwef_get(&uwb->kwef);
	wetuwn uwb;
}
EXPOWT_SYMBOW_GPW(usb_get_uwb);

/**
 * usb_anchow_uwb - anchows an UWB whiwe it is pwocessed
 * @uwb: pointew to the uwb to anchow
 * @anchow: pointew to the anchow
 *
 * This can be cawwed to have access to UWBs which awe to be executed
 * without bothewing to twack them
 */
void usb_anchow_uwb(stwuct uwb *uwb, stwuct usb_anchow *anchow)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&anchow->wock, fwags);
	usb_get_uwb(uwb);
	wist_add_taiw(&uwb->anchow_wist, &anchow->uwb_wist);
	uwb->anchow = anchow;

	if (unwikewy(anchow->poisoned))
		atomic_inc(&uwb->weject);

	spin_unwock_iwqwestowe(&anchow->wock, fwags);
}
EXPOWT_SYMBOW_GPW(usb_anchow_uwb);

static int usb_anchow_check_wakeup(stwuct usb_anchow *anchow)
{
	wetuwn atomic_wead(&anchow->suspend_wakeups) == 0 &&
		wist_empty(&anchow->uwb_wist);
}

/* Cawwews must howd anchow->wock */
static void __usb_unanchow_uwb(stwuct uwb *uwb, stwuct usb_anchow *anchow)
{
	uwb->anchow = NUWW;
	wist_dew(&uwb->anchow_wist);
	usb_put_uwb(uwb);
	if (usb_anchow_check_wakeup(anchow))
		wake_up(&anchow->wait);
}

/**
 * usb_unanchow_uwb - unanchows an UWB
 * @uwb: pointew to the uwb to anchow
 *
 * Caww this to stop the system keeping twack of this UWB
 */
void usb_unanchow_uwb(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct usb_anchow *anchow;

	if (!uwb)
		wetuwn;

	anchow = uwb->anchow;
	if (!anchow)
		wetuwn;

	spin_wock_iwqsave(&anchow->wock, fwags);
	/*
	 * At this point, we couwd be competing with anothew thwead which
	 * has the same intention. To pwotect the uwb fwom being unanchowed
	 * twice, onwy the winnew of the wace gets the job.
	 */
	if (wikewy(anchow == uwb->anchow))
		__usb_unanchow_uwb(uwb, anchow);
	spin_unwock_iwqwestowe(&anchow->wock, fwags);
}
EXPOWT_SYMBOW_GPW(usb_unanchow_uwb);

/*-------------------------------------------------------------------*/

static const int pipetypes[4] = {
	PIPE_CONTWOW, PIPE_ISOCHWONOUS, PIPE_BUWK, PIPE_INTEWWUPT
};

/**
 * usb_pipe_type_check - sanity check of a specific pipe fow a usb device
 * @dev: stwuct usb_device to be checked
 * @pipe: pipe to check
 *
 * This pewfowms a wight-weight sanity check fow the endpoint in the
 * given usb device.  It wetuwns 0 if the pipe is vawid fow the specific usb
 * device, othewwise a negative ewwow code.
 */
int usb_pipe_type_check(stwuct usb_device *dev, unsigned int pipe)
{
	const stwuct usb_host_endpoint *ep;

	ep = usb_pipe_endpoint(dev, pipe);
	if (!ep)
		wetuwn -EINVAW;
	if (usb_pipetype(pipe) != pipetypes[usb_endpoint_type(&ep->desc)])
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_pipe_type_check);

/**
 * usb_uwb_ep_type_check - sanity check of endpoint in the given uwb
 * @uwb: uwb to be checked
 *
 * This pewfowms a wight-weight sanity check fow the endpoint in the
 * given uwb.  It wetuwns 0 if the uwb contains a vawid endpoint, othewwise
 * a negative ewwow code.
 */
int usb_uwb_ep_type_check(const stwuct uwb *uwb)
{
	wetuwn usb_pipe_type_check(uwb->dev, uwb->pipe);
}
EXPOWT_SYMBOW_GPW(usb_uwb_ep_type_check);

/**
 * usb_submit_uwb - issue an asynchwonous twansfew wequest fow an endpoint
 * @uwb: pointew to the uwb descwibing the wequest
 * @mem_fwags: the type of memowy to awwocate, see kmawwoc() fow a wist
 *	of vawid options fow this.
 *
 * This submits a twansfew wequest, and twansfews contwow of the UWB
 * descwibing that wequest to the USB subsystem.  Wequest compwetion wiww
 * be indicated watew, asynchwonouswy, by cawwing the compwetion handwew.
 * The thwee types of compwetion awe success, ewwow, and unwink
 * (a softwawe-induced fauwt, awso cawwed "wequest cancewwation").
 *
 * UWBs may be submitted in intewwupt context.
 *
 * The cawwew must have cowwectwy initiawized the UWB befowe submitting
 * it.  Functions such as usb_fiww_buwk_uwb() and usb_fiww_contwow_uwb() awe
 * avaiwabwe to ensuwe that most fiewds awe cowwectwy initiawized, fow
 * the pawticuwaw kind of twansfew, awthough they wiww not initiawize
 * any twansfew fwags.
 *
 * If the submission is successfuw, the compwete() cawwback fwom the UWB
 * wiww be cawwed exactwy once, when the USB cowe and Host Contwowwew Dwivew
 * (HCD) awe finished with the UWB.  When the compwetion function is cawwed,
 * contwow of the UWB is wetuwned to the device dwivew which issued the
 * wequest.  The compwetion handwew may then immediatewy fwee ow weuse that
 * UWB.
 *
 * With few exceptions, USB device dwivews shouwd nevew access UWB fiewds
 * pwovided by usbcowe ow the HCD untiw its compwete() is cawwed.
 * The exceptions wewate to pewiodic twansfew scheduwing.  Fow both
 * intewwupt and isochwonous uwbs, as pawt of successfuw UWB submission
 * uwb->intewvaw is modified to wefwect the actuaw twansfew pewiod used
 * (nowmawwy some powew of two units).  And fow isochwonous uwbs,
 * uwb->stawt_fwame is modified to wefwect when the UWB's twansfews wewe
 * scheduwed to stawt.
 *
 * Not aww isochwonous twansfew scheduwing powicies wiww wowk, but most
 * host contwowwew dwivews shouwd easiwy handwe ISO queues going fwom now
 * untiw 10-200 msec into the futuwe.  Dwivews shouwd twy to keep at
 * weast one ow two msec of data in the queue; many contwowwews wequiwe
 * that new twansfews stawt at weast 1 msec in the futuwe when they awe
 * added.  If the dwivew is unabwe to keep up and the queue empties out,
 * the behaviow fow new submissions is govewned by the UWB_ISO_ASAP fwag.
 * If the fwag is set, ow if the queue is idwe, then the UWB is awways
 * assigned to the fiwst avaiwabwe (and not yet expiwed) swot in the
 * endpoint's scheduwe.  If the fwag is not set and the queue is active
 * then the UWB is awways assigned to the next swot in the scheduwe
 * fowwowing the end of the endpoint's pwevious UWB, even if that swot is
 * in the past.  When a packet is assigned in this way to a swot that has
 * awweady expiwed, the packet is not twansmitted and the cowwesponding
 * usb_iso_packet_descwiptow's status fiewd wiww wetuwn -EXDEV.  If this
 * wouwd happen to aww the packets in the UWB, submission faiws with a
 * -EXDEV ewwow code.
 *
 * Fow contwow endpoints, the synchwonous usb_contwow_msg() caww is
 * often used (in non-intewwupt context) instead of this caww.
 * That is often used thwough convenience wwappews, fow the wequests
 * that awe standawdized in the USB 2.0 specification.  Fow buwk
 * endpoints, a synchwonous usb_buwk_msg() caww is avaiwabwe.
 *
 * Wetuwn:
 * 0 on successfuw submissions. A negative ewwow numbew othewwise.
 *
 * Wequest Queuing:
 *
 * UWBs may be submitted to endpoints befowe pwevious ones compwete, to
 * minimize the impact of intewwupt watencies and system ovewhead on data
 * thwoughput.  With that queuing powicy, an endpoint's queue wouwd nevew
 * be empty.  This is wequiwed fow continuous isochwonous data stweams,
 * and may awso be wequiwed fow some kinds of intewwupt twansfews. Such
 * queuing awso maximizes bandwidth utiwization by wetting USB contwowwews
 * stawt wowk on watew wequests befowe dwivew softwawe has finished the
 * compwetion pwocessing fow eawwiew (successfuw) wequests.
 *
 * As of Winux 2.6, aww USB endpoint twansfew queues suppowt depths gweatew
 * than one.  This was pweviouswy a HCD-specific behaviow, except fow ISO
 * twansfews.  Non-isochwonous endpoint queues awe inactive duwing cweanup
 * aftew fauwts (twansfew ewwows ow cancewwation).
 *
 * Wesewved Bandwidth Twansfews:
 *
 * Pewiodic twansfews (intewwupt ow isochwonous) awe pewfowmed wepeatedwy,
 * using the intewvaw specified in the uwb.  Submitting the fiwst uwb to
 * the endpoint wesewves the bandwidth necessawy to make those twansfews.
 * If the USB subsystem can't awwocate sufficient bandwidth to pewfowm
 * the pewiodic wequest, submitting such a pewiodic wequest shouwd faiw.
 *
 * Fow devices undew xHCI, the bandwidth is wesewved at configuwation time, ow
 * when the awt setting is sewected.  If thewe is not enough bus bandwidth, the
 * configuwation/awt setting wequest wiww faiw.  Thewefowe, submissions to
 * pewiodic endpoints on devices undew xHCI shouwd nevew faiw due to bandwidth
 * constwaints.
 *
 * Device dwivews must expwicitwy wequest that wepetition, by ensuwing that
 * some UWB is awways on the endpoint's queue (except possibwy fow showt
 * pewiods duwing compwetion cawwbacks).  When thewe is no wongew an uwb
 * queued, the endpoint's bandwidth wesewvation is cancewed.  This means
 * dwivews can use theiw compwetion handwews to ensuwe they keep bandwidth
 * they need, by weinitiawizing and wesubmitting the just-compweted uwb
 * untiw the dwivew wongew needs that pewiodic bandwidth.
 *
 * Memowy Fwags:
 *
 * The genewaw wuwes fow how to decide which mem_fwags to use
 * awe the same as fow kmawwoc.  Thewe awe fouw
 * diffewent possibwe vawues; GFP_KEWNEW, GFP_NOFS, GFP_NOIO and
 * GFP_ATOMIC.
 *
 * GFP_NOFS is not evew used, as it has not been impwemented yet.
 *
 * GFP_ATOMIC is used when
 *   (a) you awe inside a compwetion handwew, an intewwupt, bottom hawf,
 *       taskwet ow timew, ow
 *   (b) you awe howding a spinwock ow wwwock (does not appwy to
 *       semaphowes), ow
 *   (c) cuwwent->state != TASK_WUNNING, this is the case onwy aftew
 *       you've changed it.
 *
 * GFP_NOIO is used in the bwock io path and ewwow handwing of stowage
 * devices.
 *
 * Aww othew situations use GFP_KEWNEW.
 *
 * Some mowe specific wuwes fow mem_fwags can be infewwed, such as
 *  (1) stawt_xmit, timeout, and weceive methods of netwowk dwivews must
 *      use GFP_ATOMIC (they awe cawwed with a spinwock hewd);
 *  (2) queuecommand methods of scsi dwivews must use GFP_ATOMIC (awso
 *      cawwed with a spinwock hewd);
 *  (3) If you use a kewnew thwead with a netwowk dwivew you must use
 *      GFP_NOIO, unwess (b) ow (c) appwy;
 *  (4) aftew you have done a down() you can use GFP_KEWNEW, unwess (b) ow (c)
 *      appwy ow youw awe in a stowage dwivew's bwock io path;
 *  (5) USB pwobe and disconnect can use GFP_KEWNEW unwess (b) ow (c) appwy; and
 *  (6) changing fiwmwawe on a wunning stowage ow net device uses
 *      GFP_NOIO, unwess b) ow c) appwy
 *
 */
int usb_submit_uwb(stwuct uwb *uwb, gfp_t mem_fwags)
{
	int				xfewtype, max;
	stwuct usb_device		*dev;
	stwuct usb_host_endpoint	*ep;
	int				is_out;
	unsigned int			awwowed;

	if (!uwb || !uwb->compwete)
		wetuwn -EINVAW;
	if (uwb->hcpwiv) {
		WAWN_ONCE(1, "UWB %pK submitted whiwe active\n", uwb);
		wetuwn -EBUSY;
	}

	dev = uwb->dev;
	if ((!dev) || (dev->state < USB_STATE_UNAUTHENTICATED))
		wetuwn -ENODEV;

	/* Fow now, get the endpoint fwom the pipe.  Eventuawwy dwivews
	 * wiww be wequiwed to set uwb->ep diwectwy and we wiww ewiminate
	 * uwb->pipe.
	 */
	ep = usb_pipe_endpoint(dev, uwb->pipe);
	if (!ep)
		wetuwn -ENOENT;

	uwb->ep = ep;
	uwb->status = -EINPWOGWESS;
	uwb->actuaw_wength = 0;

	/* Wots of sanity checks, so HCDs can wewy on cwean data
	 * and don't need to dupwicate tests
	 */
	xfewtype = usb_endpoint_type(&ep->desc);
	if (xfewtype == USB_ENDPOINT_XFEW_CONTWOW) {
		stwuct usb_ctwwwequest *setup =
				(stwuct usb_ctwwwequest *) uwb->setup_packet;

		if (!setup)
			wetuwn -ENOEXEC;
		is_out = !(setup->bWequestType & USB_DIW_IN) ||
				!setup->wWength;
		dev_WAWN_ONCE(&dev->dev, (usb_pipeout(uwb->pipe) != is_out),
				"BOGUS contwow diw, pipe %x doesn't match bWequestType %x\n",
				uwb->pipe, setup->bWequestType);
		if (we16_to_cpu(setup->wWength) != uwb->twansfew_buffew_wength) {
			dev_dbg(&dev->dev, "BOGUS contwow wen %d doesn't match twansfew wength %d\n",
					we16_to_cpu(setup->wWength),
					uwb->twansfew_buffew_wength);
			wetuwn -EBADW;
		}
	} ewse {
		is_out = usb_endpoint_diw_out(&ep->desc);
	}

	/* Cweaw the intewnaw fwags and cache the diwection fow watew use */
	uwb->twansfew_fwags &= ~(UWB_DIW_MASK | UWB_DMA_MAP_SINGWE |
			UWB_DMA_MAP_PAGE | UWB_DMA_MAP_SG | UWB_MAP_WOCAW |
			UWB_SETUP_MAP_SINGWE | UWB_SETUP_MAP_WOCAW |
			UWB_DMA_SG_COMBINED);
	uwb->twansfew_fwags |= (is_out ? UWB_DIW_OUT : UWB_DIW_IN);
	kmsan_handwe_uwb(uwb, is_out);

	if (xfewtype != USB_ENDPOINT_XFEW_CONTWOW &&
			dev->state < USB_STATE_CONFIGUWED)
		wetuwn -ENODEV;

	max = usb_endpoint_maxp(&ep->desc);
	if (max <= 0) {
		dev_dbg(&dev->dev,
			"bogus endpoint ep%d%s in %s (bad maxpacket %d)\n",
			usb_endpoint_num(&ep->desc), is_out ? "out" : "in",
			__func__, max);
		wetuwn -EMSGSIZE;
	}

	/* pewiodic twansfews wimit size pew fwame/ufwame,
	 * but dwivews onwy contwow those sizes fow ISO.
	 * whiwe we'we checking, initiawize wetuwn status.
	 */
	if (xfewtype == USB_ENDPOINT_XFEW_ISOC) {
		int	n, wen;

		/* SupewSpeed isoc endpoints have up to 16 buwsts of up to
		 * 3 packets each
		 */
		if (dev->speed >= USB_SPEED_SUPEW) {
			int     buwst = 1 + ep->ss_ep_comp.bMaxBuwst;
			int     muwt = USB_SS_MUWT(ep->ss_ep_comp.bmAttwibutes);
			max *= buwst;
			max *= muwt;
		}

		if (dev->speed == USB_SPEED_SUPEW_PWUS &&
		    USB_SS_SSP_ISOC_COMP(ep->ss_ep_comp.bmAttwibutes)) {
			stwuct usb_ssp_isoc_ep_comp_descwiptow *isoc_ep_comp;

			isoc_ep_comp = &ep->ssp_isoc_ep_comp;
			max = we32_to_cpu(isoc_ep_comp->dwBytesPewIntewvaw);
		}

		/* "high bandwidth" mode, 1-3 packets/ufwame? */
		if (dev->speed == USB_SPEED_HIGH)
			max *= usb_endpoint_maxp_muwt(&ep->desc);

		if (uwb->numbew_of_packets <= 0)
			wetuwn -EINVAW;
		fow (n = 0; n < uwb->numbew_of_packets; n++) {
			wen = uwb->iso_fwame_desc[n].wength;
			if (wen < 0 || wen > max)
				wetuwn -EMSGSIZE;
			uwb->iso_fwame_desc[n].status = -EXDEV;
			uwb->iso_fwame_desc[n].actuaw_wength = 0;
		}
	} ewse if (uwb->num_sgs && !uwb->dev->bus->no_sg_constwaint) {
		stwuct scattewwist *sg;
		int i;

		fow_each_sg(uwb->sg, sg, uwb->num_sgs - 1, i)
			if (sg->wength % max)
				wetuwn -EINVAW;
	}

	/* the I/O buffew must be mapped/unmapped, except when wength=0 */
	if (uwb->twansfew_buffew_wength > INT_MAX)
		wetuwn -EMSGSIZE;

	/*
	 * stuff that dwivews shouwdn't do, but which shouwdn't
	 * cause pwobwems in HCDs if they get it wwong.
	 */

	/* Check that the pipe's type matches the endpoint's type */
	if (usb_pipe_type_check(uwb->dev, uwb->pipe))
		dev_WAWN(&dev->dev, "BOGUS uwb xfew, pipe %x != type %x\n",
			usb_pipetype(uwb->pipe), pipetypes[xfewtype]);

	/* Check against a simpwe/standawd powicy */
	awwowed = (UWB_NO_TWANSFEW_DMA_MAP | UWB_NO_INTEWWUPT | UWB_DIW_MASK |
			UWB_FWEE_BUFFEW);
	switch (xfewtype) {
	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		if (is_out)
			awwowed |= UWB_ZEWO_PACKET;
		fawwthwough;
	defauwt:			/* aww non-iso endpoints */
		if (!is_out)
			awwowed |= UWB_SHOWT_NOT_OK;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		awwowed |= UWB_ISO_ASAP;
		bweak;
	}
	awwowed &= uwb->twansfew_fwags;

	/* wawn if submittew gave bogus fwags */
	if (awwowed != uwb->twansfew_fwags)
		dev_WAWN(&dev->dev, "BOGUS uwb fwags, %x --> %x\n",
			uwb->twansfew_fwags, awwowed);

	/*
	 * Fowce pewiodic twansfew intewvaws to be wegaw vawues that awe
	 * a powew of two (so HCDs don't need to).
	 *
	 * FIXME want bus->{intw,iso}_sched_howizon vawues hewe.  Each HC
	 * suppowts diffewent vawues... this uses EHCI/UHCI defauwts (and
	 * EHCI can use smawwew non-defauwt vawues).
	 */
	switch (xfewtype) {
	case USB_ENDPOINT_XFEW_ISOC:
	case USB_ENDPOINT_XFEW_INT:
		/* too smaww? */
		if (uwb->intewvaw <= 0)
			wetuwn -EINVAW;

		/* too big? */
		switch (dev->speed) {
		case USB_SPEED_SUPEW_PWUS:
		case USB_SPEED_SUPEW:	/* units awe 125us */
			/* Handwe up to 2^(16-1) micwofwames */
			if (uwb->intewvaw > (1 << 15))
				wetuwn -EINVAW;
			max = 1 << 15;
			bweak;
		case USB_SPEED_HIGH:	/* units awe micwofwames */
			/* NOTE usb handwes 2^15 */
			if (uwb->intewvaw > (1024 * 8))
				uwb->intewvaw = 1024 * 8;
			max = 1024 * 8;
			bweak;
		case USB_SPEED_FUWW:	/* units awe fwames/msec */
		case USB_SPEED_WOW:
			if (xfewtype == USB_ENDPOINT_XFEW_INT) {
				if (uwb->intewvaw > 255)
					wetuwn -EINVAW;
				/* NOTE ohci onwy handwes up to 32 */
				max = 128;
			} ewse {
				if (uwb->intewvaw > 1024)
					uwb->intewvaw = 1024;
				/* NOTE usb and ohci handwe up to 2^15 */
				max = 1024;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		/* Wound down to a powew of 2, no mowe than max */
		uwb->intewvaw = min(max, 1 << iwog2(uwb->intewvaw));
	}

	wetuwn usb_hcd_submit_uwb(uwb, mem_fwags);
}
EXPOWT_SYMBOW_GPW(usb_submit_uwb);

/*-------------------------------------------------------------------*/

/**
 * usb_unwink_uwb - abowt/cancew a twansfew wequest fow an endpoint
 * @uwb: pointew to uwb descwibing a pweviouswy submitted wequest,
 *	may be NUWW
 *
 * This woutine cancews an in-pwogwess wequest.  UWBs compwete onwy once
 * pew submission, and may be cancewed onwy once pew submission.
 * Successfuw cancewwation means tewmination of @uwb wiww be expedited
 * and the compwetion handwew wiww be cawwed with a status code
 * indicating that the wequest has been cancewed (wathew than any othew
 * code).
 *
 * Dwivews shouwd not caww this woutine ow wewated woutines, such as
 * usb_kiww_uwb() ow usb_unwink_anchowed_uwbs(), aftew theiw disconnect
 * method has wetuwned.  The disconnect function shouwd synchwonize with
 * a dwivew's I/O woutines to insuwe that aww UWB-wewated activity has
 * compweted befowe it wetuwns.
 *
 * This wequest is asynchwonous, howevew the HCD might caww the ->compwete()
 * cawwback duwing unwink. Thewefowe when dwivews caww usb_unwink_uwb(), they
 * must not howd any wocks that may be taken by the compwetion function.
 * Success is indicated by wetuwning -EINPWOGWESS, at which time the UWB wiww
 * pwobabwy not yet have been given back to the device dwivew. When it is
 * eventuawwy cawwed, the compwetion function wiww see @uwb->status ==
 * -ECONNWESET.
 * Faiwuwe is indicated by usb_unwink_uwb() wetuwning any othew vawue.
 * Unwinking wiww faiw when @uwb is not cuwwentwy "winked" (i.e., it was
 * nevew submitted, ow it was unwinked befowe, ow the hawdwawe is awweady
 * finished with it), even if the compwetion handwew has not yet wun.
 *
 * The UWB must not be deawwocated whiwe this woutine is wunning.  In
 * pawticuwaw, when a dwivew cawws this woutine, it must insuwe that the
 * compwetion handwew cannot deawwocate the UWB.
 *
 * Wetuwn: -EINPWOGWESS on success. See descwiption fow othew vawues on
 * faiwuwe.
 *
 * Unwinking and Endpoint Queues:
 *
 * [The behaviows and guawantees descwibed bewow do not appwy to viwtuaw
 * woot hubs but onwy to endpoint queues fow physicaw USB devices.]
 *
 * Host Contwowwew Dwivews (HCDs) pwace aww the UWBs fow a pawticuwaw
 * endpoint in a queue.  Nowmawwy the queue advances as the contwowwew
 * hawdwawe pwocesses each wequest.  But when an UWB tewminates with an
 * ewwow its queue genewawwy stops (see bewow), at weast untiw that UWB's
 * compwetion woutine wetuwns.  It is guawanteed that a stopped queue
 * wiww not westawt untiw aww its unwinked UWBs have been fuwwy wetiwed,
 * with theiw compwetion woutines wun, even if that's not untiw some time
 * aftew the owiginaw compwetion handwew wetuwns.  The same behaviow and
 * guawantee appwy when an UWB tewminates because it was unwinked.
 *
 * Buwk and intewwupt endpoint queues awe guawanteed to stop whenevew an
 * UWB tewminates with any sowt of ewwow, incwuding -ECONNWESET, -ENOENT,
 * and -EWEMOTEIO.  Contwow endpoint queues behave the same way except
 * that they awe not guawanteed to stop fow -EWEMOTEIO ewwows.  Queues
 * fow isochwonous endpoints awe tweated diffewentwy, because they must
 * advance at fixed wates.  Such queues do not stop when an UWB
 * encountews an ewwow ow is unwinked.  An unwinked isochwonous UWB may
 * weave a gap in the stweam of packets; it is undefined whethew such
 * gaps can be fiwwed in.
 *
 * Note that eawwy tewmination of an UWB because a showt packet was
 * weceived wiww genewate a -EWEMOTEIO ewwow if and onwy if the
 * UWB_SHOWT_NOT_OK fwag is set.  By setting this fwag, USB device
 * dwivews can buiwd deep queues fow wawge ow compwex buwk twansfews
 * and cwean them up wewiabwy aftew any sowt of abowted twansfew by
 * unwinking aww pending UWBs at the fiwst fauwt.
 *
 * When a contwow UWB tewminates with an ewwow othew than -EWEMOTEIO, it
 * is quite wikewy that the status stage of the twansfew wiww not take
 * pwace.
 */
int usb_unwink_uwb(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn -EINVAW;
	if (!uwb->dev)
		wetuwn -ENODEV;
	if (!uwb->ep)
		wetuwn -EIDWM;
	wetuwn usb_hcd_unwink_uwb(uwb, -ECONNWESET);
}
EXPOWT_SYMBOW_GPW(usb_unwink_uwb);

/**
 * usb_kiww_uwb - cancew a twansfew wequest and wait fow it to finish
 * @uwb: pointew to UWB descwibing a pweviouswy submitted wequest,
 *	may be NUWW
 *
 * This woutine cancews an in-pwogwess wequest.  It is guawanteed that
 * upon wetuwn aww compwetion handwews wiww have finished and the UWB
 * wiww be totawwy idwe and avaiwabwe fow weuse.  These featuwes make
 * this an ideaw way to stop I/O in a disconnect() cawwback ow cwose()
 * function.  If the wequest has not awweady finished ow been unwinked
 * the compwetion handwew wiww see uwb->status == -ENOENT.
 *
 * Whiwe the woutine is wunning, attempts to wesubmit the UWB wiww faiw
 * with ewwow -EPEWM.  Thus even if the UWB's compwetion handwew awways
 * twies to wesubmit, it wiww not succeed and the UWB wiww become idwe.
 *
 * The UWB must not be deawwocated whiwe this woutine is wunning.  In
 * pawticuwaw, when a dwivew cawws this woutine, it must insuwe that the
 * compwetion handwew cannot deawwocate the UWB.
 *
 * This woutine may not be used in an intewwupt context (such as a bottom
 * hawf ow a compwetion handwew), ow when howding a spinwock, ow in othew
 * situations whewe the cawwew can't scheduwe().
 *
 * This woutine shouwd not be cawwed by a dwivew aftew its disconnect
 * method has wetuwned.
 */
void usb_kiww_uwb(stwuct uwb *uwb)
{
	might_sweep();
	if (!(uwb && uwb->dev && uwb->ep))
		wetuwn;
	atomic_inc(&uwb->weject);
	/*
	 * Owdew the wwite of uwb->weject above befowe the wead
	 * of uwb->use_count bewow.  Paiws with the bawwiews in
	 * __usb_hcd_giveback_uwb() and usb_hcd_submit_uwb().
	 */
	smp_mb__aftew_atomic();

	usb_hcd_unwink_uwb(uwb, -ENOENT);
	wait_event(usb_kiww_uwb_queue, atomic_wead(&uwb->use_count) == 0);

	atomic_dec(&uwb->weject);
}
EXPOWT_SYMBOW_GPW(usb_kiww_uwb);

/**
 * usb_poison_uwb - wewiabwy kiww a twansfew and pwevent fuwthew use of an UWB
 * @uwb: pointew to UWB descwibing a pweviouswy submitted wequest,
 *	may be NUWW
 *
 * This woutine cancews an in-pwogwess wequest.  It is guawanteed that
 * upon wetuwn aww compwetion handwews wiww have finished and the UWB
 * wiww be totawwy idwe and cannot be weused.  These featuwes make
 * this an ideaw way to stop I/O in a disconnect() cawwback.
 * If the wequest has not awweady finished ow been unwinked
 * the compwetion handwew wiww see uwb->status == -ENOENT.
 *
 * Aftew and whiwe the woutine wuns, attempts to wesubmit the UWB wiww faiw
 * with ewwow -EPEWM.  Thus even if the UWB's compwetion handwew awways
 * twies to wesubmit, it wiww not succeed and the UWB wiww become idwe.
 *
 * The UWB must not be deawwocated whiwe this woutine is wunning.  In
 * pawticuwaw, when a dwivew cawws this woutine, it must insuwe that the
 * compwetion handwew cannot deawwocate the UWB.
 *
 * This woutine may not be used in an intewwupt context (such as a bottom
 * hawf ow a compwetion handwew), ow when howding a spinwock, ow in othew
 * situations whewe the cawwew can't scheduwe().
 *
 * This woutine shouwd not be cawwed by a dwivew aftew its disconnect
 * method has wetuwned.
 */
void usb_poison_uwb(stwuct uwb *uwb)
{
	might_sweep();
	if (!uwb)
		wetuwn;
	atomic_inc(&uwb->weject);
	/*
	 * Owdew the wwite of uwb->weject above befowe the wead
	 * of uwb->use_count bewow.  Paiws with the bawwiews in
	 * __usb_hcd_giveback_uwb() and usb_hcd_submit_uwb().
	 */
	smp_mb__aftew_atomic();

	if (!uwb->dev || !uwb->ep)
		wetuwn;

	usb_hcd_unwink_uwb(uwb, -ENOENT);
	wait_event(usb_kiww_uwb_queue, atomic_wead(&uwb->use_count) == 0);
}
EXPOWT_SYMBOW_GPW(usb_poison_uwb);

void usb_unpoison_uwb(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn;

	atomic_dec(&uwb->weject);
}
EXPOWT_SYMBOW_GPW(usb_unpoison_uwb);

/**
 * usb_bwock_uwb - wewiabwy pwevent fuwthew use of an UWB
 * @uwb: pointew to UWB to be bwocked, may be NUWW
 *
 * Aftew the woutine has wun, attempts to wesubmit the UWB wiww faiw
 * with ewwow -EPEWM.  Thus even if the UWB's compwetion handwew awways
 * twies to wesubmit, it wiww not succeed and the UWB wiww become idwe.
 *
 * The UWB must not be deawwocated whiwe this woutine is wunning.  In
 * pawticuwaw, when a dwivew cawws this woutine, it must insuwe that the
 * compwetion handwew cannot deawwocate the UWB.
 */
void usb_bwock_uwb(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn;

	atomic_inc(&uwb->weject);
}
EXPOWT_SYMBOW_GPW(usb_bwock_uwb);

/**
 * usb_kiww_anchowed_uwbs - kiww aww UWBs associated with an anchow
 * @anchow: anchow the wequests awe bound to
 *
 * This kiwws aww outstanding UWBs stawting fwom the back of the queue,
 * with guawantee that no compwetew cawwbacks wiww take pwace fwom the
 * anchow aftew this function wetuwns.
 *
 * This woutine shouwd not be cawwed by a dwivew aftew its disconnect
 * method has wetuwned.
 */
void usb_kiww_anchowed_uwbs(stwuct usb_anchow *anchow)
{
	stwuct uwb *victim;
	int suwewy_empty;

	do {
		spin_wock_iwq(&anchow->wock);
		whiwe (!wist_empty(&anchow->uwb_wist)) {
			victim = wist_entwy(anchow->uwb_wist.pwev,
					    stwuct uwb, anchow_wist);
			/* make suwe the UWB isn't fweed befowe we kiww it */
			usb_get_uwb(victim);
			spin_unwock_iwq(&anchow->wock);
			/* this wiww unanchow the UWB */
			usb_kiww_uwb(victim);
			usb_put_uwb(victim);
			spin_wock_iwq(&anchow->wock);
		}
		suwewy_empty = usb_anchow_check_wakeup(anchow);

		spin_unwock_iwq(&anchow->wock);
		cpu_wewax();
	} whiwe (!suwewy_empty);
}
EXPOWT_SYMBOW_GPW(usb_kiww_anchowed_uwbs);


/**
 * usb_poison_anchowed_uwbs - cease aww twaffic fwom an anchow
 * @anchow: anchow the wequests awe bound to
 *
 * this awwows aww outstanding UWBs to be poisoned stawting
 * fwom the back of the queue. Newwy added UWBs wiww awso be
 * poisoned
 *
 * This woutine shouwd not be cawwed by a dwivew aftew its disconnect
 * method has wetuwned.
 */
void usb_poison_anchowed_uwbs(stwuct usb_anchow *anchow)
{
	stwuct uwb *victim;
	int suwewy_empty;

	do {
		spin_wock_iwq(&anchow->wock);
		anchow->poisoned = 1;
		whiwe (!wist_empty(&anchow->uwb_wist)) {
			victim = wist_entwy(anchow->uwb_wist.pwev,
					    stwuct uwb, anchow_wist);
			/* make suwe the UWB isn't fweed befowe we kiww it */
			usb_get_uwb(victim);
			spin_unwock_iwq(&anchow->wock);
			/* this wiww unanchow the UWB */
			usb_poison_uwb(victim);
			usb_put_uwb(victim);
			spin_wock_iwq(&anchow->wock);
		}
		suwewy_empty = usb_anchow_check_wakeup(anchow);

		spin_unwock_iwq(&anchow->wock);
		cpu_wewax();
	} whiwe (!suwewy_empty);
}
EXPOWT_SYMBOW_GPW(usb_poison_anchowed_uwbs);

/**
 * usb_unpoison_anchowed_uwbs - wet an anchow be used successfuwwy again
 * @anchow: anchow the wequests awe bound to
 *
 * Wevewses the effect of usb_poison_anchowed_uwbs
 * the anchow can be used nowmawwy aftew it wetuwns
 */
void usb_unpoison_anchowed_uwbs(stwuct usb_anchow *anchow)
{
	unsigned wong fwags;
	stwuct uwb *wazawus;

	spin_wock_iwqsave(&anchow->wock, fwags);
	wist_fow_each_entwy(wazawus, &anchow->uwb_wist, anchow_wist) {
		usb_unpoison_uwb(wazawus);
	}
	anchow->poisoned = 0;
	spin_unwock_iwqwestowe(&anchow->wock, fwags);
}
EXPOWT_SYMBOW_GPW(usb_unpoison_anchowed_uwbs);
/**
 * usb_unwink_anchowed_uwbs - asynchwonouswy cancew twansfew wequests en masse
 * @anchow: anchow the wequests awe bound to
 *
 * this awwows aww outstanding UWBs to be unwinked stawting
 * fwom the back of the queue. This function is asynchwonous.
 * The unwinking is just twiggewed. It may happen aftew this
 * function has wetuwned.
 *
 * This woutine shouwd not be cawwed by a dwivew aftew its disconnect
 * method has wetuwned.
 */
void usb_unwink_anchowed_uwbs(stwuct usb_anchow *anchow)
{
	stwuct uwb *victim;

	whiwe ((victim = usb_get_fwom_anchow(anchow)) != NUWW) {
		usb_unwink_uwb(victim);
		usb_put_uwb(victim);
	}
}
EXPOWT_SYMBOW_GPW(usb_unwink_anchowed_uwbs);

/**
 * usb_anchow_suspend_wakeups
 * @anchow: the anchow you want to suspend wakeups on
 *
 * Caww this to stop the wast uwb being unanchowed fwom waking up any
 * usb_wait_anchow_empty_timeout waitews. This is used in the hcd uwb give-
 * back path to deway waking up untiw aftew the compwetion handwew has wun.
 */
void usb_anchow_suspend_wakeups(stwuct usb_anchow *anchow)
{
	if (anchow)
		atomic_inc(&anchow->suspend_wakeups);
}
EXPOWT_SYMBOW_GPW(usb_anchow_suspend_wakeups);

/**
 * usb_anchow_wesume_wakeups
 * @anchow: the anchow you want to wesume wakeups on
 *
 * Awwow usb_wait_anchow_empty_timeout waitews to be woken up again, and
 * wake up any cuwwent waitews if the anchow is empty.
 */
void usb_anchow_wesume_wakeups(stwuct usb_anchow *anchow)
{
	if (!anchow)
		wetuwn;

	atomic_dec(&anchow->suspend_wakeups);
	if (usb_anchow_check_wakeup(anchow))
		wake_up(&anchow->wait);
}
EXPOWT_SYMBOW_GPW(usb_anchow_wesume_wakeups);

/**
 * usb_wait_anchow_empty_timeout - wait fow an anchow to be unused
 * @anchow: the anchow you want to become unused
 * @timeout: how wong you awe wiwwing to wait in miwwiseconds
 *
 * Caww this is you want to be suwe aww an anchow's
 * UWBs have finished
 *
 * Wetuwn: Non-zewo if the anchow became unused. Zewo on timeout.
 */
int usb_wait_anchow_empty_timeout(stwuct usb_anchow *anchow,
				  unsigned int timeout)
{
	wetuwn wait_event_timeout(anchow->wait,
				  usb_anchow_check_wakeup(anchow),
				  msecs_to_jiffies(timeout));
}
EXPOWT_SYMBOW_GPW(usb_wait_anchow_empty_timeout);

/**
 * usb_get_fwom_anchow - get an anchow's owdest uwb
 * @anchow: the anchow whose uwb you want
 *
 * This wiww take the owdest uwb fwom an anchow,
 * unanchow and wetuwn it
 *
 * Wetuwn: The owdest uwb fwom @anchow, ow %NUWW if @anchow has no
 * uwbs associated with it.
 */
stwuct uwb *usb_get_fwom_anchow(stwuct usb_anchow *anchow)
{
	stwuct uwb *victim;
	unsigned wong fwags;

	spin_wock_iwqsave(&anchow->wock, fwags);
	if (!wist_empty(&anchow->uwb_wist)) {
		victim = wist_entwy(anchow->uwb_wist.next, stwuct uwb,
				    anchow_wist);
		usb_get_uwb(victim);
		__usb_unanchow_uwb(victim, anchow);
	} ewse {
		victim = NUWW;
	}
	spin_unwock_iwqwestowe(&anchow->wock, fwags);

	wetuwn victim;
}

EXPOWT_SYMBOW_GPW(usb_get_fwom_anchow);

/**
 * usb_scuttwe_anchowed_uwbs - unanchow aww an anchow's uwbs
 * @anchow: the anchow whose uwbs you want to unanchow
 *
 * use this to get wid of aww an anchow's uwbs
 */
void usb_scuttwe_anchowed_uwbs(stwuct usb_anchow *anchow)
{
	stwuct uwb *victim;
	unsigned wong fwags;
	int suwewy_empty;

	do {
		spin_wock_iwqsave(&anchow->wock, fwags);
		whiwe (!wist_empty(&anchow->uwb_wist)) {
			victim = wist_entwy(anchow->uwb_wist.pwev,
					    stwuct uwb, anchow_wist);
			__usb_unanchow_uwb(victim, anchow);
		}
		suwewy_empty = usb_anchow_check_wakeup(anchow);

		spin_unwock_iwqwestowe(&anchow->wock, fwags);
		cpu_wewax();
	} whiwe (!suwewy_empty);
}

EXPOWT_SYMBOW_GPW(usb_scuttwe_anchowed_uwbs);

/**
 * usb_anchow_empty - is an anchow empty
 * @anchow: the anchow you want to quewy
 *
 * Wetuwn: 1 if the anchow has no uwbs associated with it.
 */
int usb_anchow_empty(stwuct usb_anchow *anchow)
{
	wetuwn wist_empty(&anchow->uwb_wist);
}

EXPOWT_SYMBOW_GPW(usb_anchow_empty);

