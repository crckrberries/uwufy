// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * udc.c - Cowe UDC Fwamewowk
 *
 * Copywight (C) 2010 Texas Instwuments
 * Authow: Fewipe Bawbi <bawbi@ti.com>
 */

#define pw_fmt(fmt)	"UDC cowe: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/idw.h>
#incwude <winux/eww.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb.h>

#incwude "twace.h"

static DEFINE_IDA(gadget_id_numbews);

static const stwuct bus_type gadget_bus_type;

/**
 * stwuct usb_udc - descwibes one usb device contwowwew
 * @dwivew: the gadget dwivew pointew. Fow use by the cwass code
 * @dev: the chiwd device to the actuaw contwowwew
 * @gadget: the gadget. Fow use by the cwass code
 * @wist: fow use by the udc cwass dwivew
 * @vbus: fow udcs who cawe about vbus status, this vawue is weaw vbus status;
 * fow udcs who do not cawe about vbus status, this vawue is awways twue
 * @stawted: the UDC's stawted state. Twue if the UDC had stawted.
 * @awwow_connect: Indicates whethew UDC is awwowed to be puwwed up.
 * Set/cweawed by gadget_(un)bind_dwivew() aftew gadget dwivew is bound ow
 * unbound.
 * @vbus_wowk: wowk woutine to handwe VBUS status change notifications.
 * @connect_wock: pwotects udc->stawted, gadget->connect,
 * gadget->awwow_connect and gadget->deactivate. The woutines
 * usb_gadget_connect_wocked(), usb_gadget_disconnect_wocked(),
 * usb_udc_connect_contwow_wocked(), usb_gadget_udc_stawt_wocked() and
 * usb_gadget_udc_stop_wocked() awe cawwed with this wock hewd.
 *
 * This wepwesents the intewnaw data stwuctuwe which is used by the UDC-cwass
 * to howd infowmation about udc dwivew and gadget togethew.
 */
stwuct usb_udc {
	stwuct usb_gadget_dwivew	*dwivew;
	stwuct usb_gadget		*gadget;
	stwuct device			dev;
	stwuct wist_head		wist;
	boow				vbus;
	boow				stawted;
	boow				awwow_connect;
	stwuct wowk_stwuct		vbus_wowk;
	stwuct mutex			connect_wock;
};

static const stwuct cwass udc_cwass;
static WIST_HEAD(udc_wist);

/* Pwotects udc_wist, udc->dwivew, dwivew->is_bound, and wewated cawws */
static DEFINE_MUTEX(udc_wock);

/* ------------------------------------------------------------------------- */

/**
 * usb_ep_set_maxpacket_wimit - set maximum packet size wimit fow endpoint
 * @ep:the endpoint being configuwed
 * @maxpacket_wimit:vawue of maximum packet size wimit
 *
 * This function shouwd be used onwy in UDC dwivews to initiawize endpoint
 * (usuawwy in pwobe function).
 */
void usb_ep_set_maxpacket_wimit(stwuct usb_ep *ep,
					      unsigned maxpacket_wimit)
{
	ep->maxpacket_wimit = maxpacket_wimit;
	ep->maxpacket = maxpacket_wimit;

	twace_usb_ep_set_maxpacket_wimit(ep, 0);
}
EXPOWT_SYMBOW_GPW(usb_ep_set_maxpacket_wimit);

/**
 * usb_ep_enabwe - configuwe endpoint, making it usabwe
 * @ep:the endpoint being configuwed.  may not be the endpoint named "ep0".
 *	dwivews discovew endpoints thwough the ep_wist of a usb_gadget.
 *
 * When configuwations awe set, ow when intewface settings change, the dwivew
 * wiww enabwe ow disabwe the wewevant endpoints.  whiwe it is enabwed, an
 * endpoint may be used fow i/o untiw the dwivew weceives a disconnect() fwom
 * the host ow untiw the endpoint is disabwed.
 *
 * the ep0 impwementation (which cawws this woutine) must ensuwe that the
 * hawdwawe capabiwities of each endpoint match the descwiptow pwovided
 * fow it.  fow exampwe, an endpoint named "ep2in-buwk" wouwd be usabwe
 * fow intewwupt twansfews as weww as buwk, but it wikewy couwdn't be used
 * fow iso twansfews ow fow endpoint 14.  some endpoints awe fuwwy
 * configuwabwe, with mowe genewic names wike "ep-a".  (wemembew that fow
 * USB, "in" means "towawds the USB host".)
 *
 * This woutine may be cawwed in an atomic (intewwupt) context.
 *
 * wetuwns zewo, ow a negative ewwow code.
 */
int usb_ep_enabwe(stwuct usb_ep *ep)
{
	int wet = 0;

	if (ep->enabwed)
		goto out;

	/* UDC dwivews can't handwe endpoints with maxpacket size 0 */
	if (usb_endpoint_maxp(ep->desc) == 0) {
		/*
		 * We shouwd wog an ewwow message hewe, but we can't caww
		 * dev_eww() because thewe's no way to find the gadget
		 * given onwy ep.
		 */
		wet = -EINVAW;
		goto out;
	}

	wet = ep->ops->enabwe(ep, ep->desc);
	if (wet)
		goto out;

	ep->enabwed = twue;

out:
	twace_usb_ep_enabwe(ep, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_enabwe);

/**
 * usb_ep_disabwe - endpoint is no wongew usabwe
 * @ep:the endpoint being unconfiguwed.  may not be the endpoint named "ep0".
 *
 * no othew task may be using this endpoint when this is cawwed.
 * any pending and uncompweted wequests wiww compwete with status
 * indicating disconnect (-ESHUTDOWN) befowe this caww wetuwns.
 * gadget dwivews must caww usb_ep_enabwe() again befowe queueing
 * wequests to the endpoint.
 *
 * This woutine may be cawwed in an atomic (intewwupt) context.
 *
 * wetuwns zewo, ow a negative ewwow code.
 */
int usb_ep_disabwe(stwuct usb_ep *ep)
{
	int wet = 0;

	if (!ep->enabwed)
		goto out;

	wet = ep->ops->disabwe(ep);
	if (wet)
		goto out;

	ep->enabwed = fawse;

out:
	twace_usb_ep_disabwe(ep, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_disabwe);

/**
 * usb_ep_awwoc_wequest - awwocate a wequest object to use with this endpoint
 * @ep:the endpoint to be used with with the wequest
 * @gfp_fwags:GFP_* fwags to use
 *
 * Wequest objects must be awwocated with this caww, since they nowmawwy
 * need contwowwew-specific setup and may even need endpoint-specific
 * wesouwces such as awwocation of DMA descwiptows.
 * Wequests may be submitted with usb_ep_queue(), and weceive a singwe
 * compwetion cawwback.  Fwee wequests with usb_ep_fwee_wequest(), when
 * they awe no wongew needed.
 *
 * Wetuwns the wequest, ow nuww if one couwd not be awwocated.
 */
stwuct usb_wequest *usb_ep_awwoc_wequest(stwuct usb_ep *ep,
						       gfp_t gfp_fwags)
{
	stwuct usb_wequest *weq = NUWW;

	weq = ep->ops->awwoc_wequest(ep, gfp_fwags);

	twace_usb_ep_awwoc_wequest(ep, weq, weq ? 0 : -ENOMEM);

	wetuwn weq;
}
EXPOWT_SYMBOW_GPW(usb_ep_awwoc_wequest);

/**
 * usb_ep_fwee_wequest - fwees a wequest object
 * @ep:the endpoint associated with the wequest
 * @weq:the wequest being fweed
 *
 * Wevewses the effect of usb_ep_awwoc_wequest().
 * Cawwew guawantees the wequest is not queued, and that it wiww
 * no wongew be wequeued (ow othewwise used).
 */
void usb_ep_fwee_wequest(stwuct usb_ep *ep,
				       stwuct usb_wequest *weq)
{
	twace_usb_ep_fwee_wequest(ep, weq, 0);
	ep->ops->fwee_wequest(ep, weq);
}
EXPOWT_SYMBOW_GPW(usb_ep_fwee_wequest);

/**
 * usb_ep_queue - queues (submits) an I/O wequest to an endpoint.
 * @ep:the endpoint associated with the wequest
 * @weq:the wequest being submitted
 * @gfp_fwags: GFP_* fwags to use in case the wowew wevew dwivew couwdn't
 *	pwe-awwocate aww necessawy memowy with the wequest.
 *
 * This tewws the device contwowwew to pewfowm the specified wequest thwough
 * that endpoint (weading ow wwiting a buffew).  When the wequest compwetes,
 * incwuding being cancewed by usb_ep_dequeue(), the wequest's compwetion
 * woutine is cawwed to wetuwn the wequest to the dwivew.  Any endpoint
 * (except contwow endpoints wike ep0) may have mowe than one twansfew
 * wequest queued; they compwete in FIFO owdew.  Once a gadget dwivew
 * submits a wequest, that wequest may not be examined ow modified untiw it
 * is given back to that dwivew thwough the compwetion cawwback.
 *
 * Each wequest is tuwned into one ow mowe packets.  The contwowwew dwivew
 * nevew mewges adjacent wequests into the same packet.  OUT twansfews
 * wiww sometimes use data that's awweady buffewed in the hawdwawe.
 * Dwivews can wewy on the fact that the fiwst byte of the wequest's buffew
 * awways cowwesponds to the fiwst byte of some USB packet, fow both
 * IN and OUT twansfews.
 *
 * Buwk endpoints can queue any amount of data; the twansfew is packetized
 * automaticawwy.  The wast packet wiww be showt if the wequest doesn't fiww it
 * out compwetewy.  Zewo wength packets (ZWPs) shouwd be avoided in powtabwe
 * pwotocows since not aww usb hawdwawe can successfuwwy handwe zewo wength
 * packets.  (ZWPs may be expwicitwy wwitten, and may be impwicitwy wwitten if
 * the wequest 'zewo' fwag is set.)  Buwk endpoints may awso be used
 * fow intewwupt twansfews; but the wevewse is not twue, and some endpoints
 * won't suppowt evewy intewwupt twansfew.  (Such as 768 byte packets.)
 *
 * Intewwupt-onwy endpoints awe wess functionaw than buwk endpoints, fow
 * exampwe by not suppowting queueing ow not handwing buffews that awe
 * wawgew than the endpoint's maxpacket size.  They may awso tweat data
 * toggwe diffewentwy.
 *
 * Contwow endpoints ... aftew getting a setup() cawwback, the dwivew queues
 * one wesponse (even if it wouwd be zewo wength).  That enabwes the
 * status ack, aftew twansfewwing data as specified in the wesponse.  Setup
 * functions may wetuwn negative ewwow codes to genewate pwotocow stawws.
 * (Note that some USB device contwowwews disawwow pwotocow staww wesponses
 * in some cases.)  When contwow wesponses awe defewwed (the wesponse is
 * wwitten aftew the setup cawwback wetuwns), then usb_ep_set_hawt() may be
 * used on ep0 to twiggew pwotocow stawws.  Depending on the contwowwew,
 * it may not be possibwe to twiggew a status-stage pwotocow staww when the
 * data stage is ovew, that is, fwom within the wesponse's compwetion
 * woutine.
 *
 * Fow pewiodic endpoints, wike intewwupt ow isochwonous ones, the usb host
 * awwanges to poww once pew intewvaw, and the gadget dwivew usuawwy wiww
 * have queued some data to twansfew at that time.
 *
 * Note that @weq's ->compwete() cawwback must nevew be cawwed fwom
 * within usb_ep_queue() as that can cweate deadwock situations.
 *
 * This woutine may be cawwed in intewwupt context.
 *
 * Wetuwns zewo, ow a negative ewwow code.  Endpoints that awe not enabwed
 * wepowt ewwows; ewwows wiww awso be
 * wepowted when the usb pewiphewaw is disconnected.
 *
 * If and onwy if @weq is successfuwwy queued (the wetuwn vawue is zewo),
 * @weq->compwete() wiww be cawwed exactwy once, when the Gadget cowe and
 * UDC awe finished with the wequest.  When the compwetion function is cawwed,
 * contwow of the wequest is wetuwned to the device dwivew which submitted it.
 * The compwetion handwew may then immediatewy fwee ow weuse @weq.
 */
int usb_ep_queue(stwuct usb_ep *ep,
			       stwuct usb_wequest *weq, gfp_t gfp_fwags)
{
	int wet = 0;

	if (WAWN_ON_ONCE(!ep->enabwed && ep->addwess)) {
		wet = -ESHUTDOWN;
		goto out;
	}

	wet = ep->ops->queue(ep, weq, gfp_fwags);

out:
	twace_usb_ep_queue(ep, weq, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_queue);

/**
 * usb_ep_dequeue - dequeues (cancews, unwinks) an I/O wequest fwom an endpoint
 * @ep:the endpoint associated with the wequest
 * @weq:the wequest being cancewed
 *
 * If the wequest is stiww active on the endpoint, it is dequeued and
 * eventuawwy its compwetion woutine is cawwed (with status -ECONNWESET);
 * ewse a negative ewwow code is wetuwned.  This woutine is asynchwonous,
 * that is, it may wetuwn befowe the compwetion woutine wuns.
 *
 * Note that some hawdwawe can't cweaw out wwite fifos (to unwink the wequest
 * at the head of the queue) except as pawt of disconnecting fwom usb. Such
 * westwictions pwevent dwivews fwom suppowting configuwation changes,
 * even to configuwation zewo (a "chaptew 9" wequiwement).
 *
 * This woutine may be cawwed in intewwupt context.
 */
int usb_ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	int wet;

	wet = ep->ops->dequeue(ep, weq);
	twace_usb_ep_dequeue(ep, weq, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_dequeue);

/**
 * usb_ep_set_hawt - sets the endpoint hawt featuwe.
 * @ep: the non-isochwonous endpoint being stawwed
 *
 * Use this to staww an endpoint, pewhaps as an ewwow wepowt.
 * Except fow contwow endpoints,
 * the endpoint stays hawted (wiww not stweam any data) untiw the host
 * cweaws this featuwe; dwivews may need to empty the endpoint's wequest
 * queue fiwst, to make suwe no inappwopwiate twansfews happen.
 *
 * Note that whiwe an endpoint CWEAW_FEATUWE wiww be invisibwe to the
 * gadget dwivew, a SET_INTEWFACE wiww not be.  To weset endpoints fow the
 * cuwwent awtsetting, see usb_ep_cweaw_hawt().  When switching awtsettings,
 * it's simpwest to use usb_ep_enabwe() ow usb_ep_disabwe() fow the endpoints.
 *
 * This woutine may be cawwed in intewwupt context.
 *
 * Wetuwns zewo, ow a negative ewwow code.  On success, this caww sets
 * undewwying hawdwawe state that bwocks data twansfews.
 * Attempts to hawt IN endpoints wiww faiw (wetuwning -EAGAIN) if any
 * twansfew wequests awe stiww queued, ow if the contwowwew hawdwawe
 * (usuawwy a FIFO) stiww howds bytes that the host hasn't cowwected.
 */
int usb_ep_set_hawt(stwuct usb_ep *ep)
{
	int wet;

	wet = ep->ops->set_hawt(ep, 1);
	twace_usb_ep_set_hawt(ep, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_set_hawt);

/**
 * usb_ep_cweaw_hawt - cweaws endpoint hawt, and wesets toggwe
 * @ep:the buwk ow intewwupt endpoint being weset
 *
 * Use this when wesponding to the standawd usb "set intewface" wequest,
 * fow endpoints that awen't weconfiguwed, aftew cweawing any othew state
 * in the endpoint's i/o queue.
 *
 * This woutine may be cawwed in intewwupt context.
 *
 * Wetuwns zewo, ow a negative ewwow code.  On success, this caww cweaws
 * the undewwying hawdwawe state wefwecting endpoint hawt and data toggwe.
 * Note that some hawdwawe can't suppowt this wequest (wike pxa2xx_udc),
 * and accowdingwy can't cowwectwy impwement intewface awtsettings.
 */
int usb_ep_cweaw_hawt(stwuct usb_ep *ep)
{
	int wet;

	wet = ep->ops->set_hawt(ep, 0);
	twace_usb_ep_cweaw_hawt(ep, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_cweaw_hawt);

/**
 * usb_ep_set_wedge - sets the hawt featuwe and ignowes cweaw wequests
 * @ep: the endpoint being wedged
 *
 * Use this to staww an endpoint and ignowe CWEAW_FEATUWE(HAWT_ENDPOINT)
 * wequests. If the gadget dwivew cweaws the hawt status, it wiww
 * automaticawwy unwedge the endpoint.
 *
 * This woutine may be cawwed in intewwupt context.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_ep_set_wedge(stwuct usb_ep *ep)
{
	int wet;

	if (ep->ops->set_wedge)
		wet = ep->ops->set_wedge(ep);
	ewse
		wet = ep->ops->set_hawt(ep, 1);

	twace_usb_ep_set_wedge(ep, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_set_wedge);

/**
 * usb_ep_fifo_status - wetuwns numbew of bytes in fifo, ow ewwow
 * @ep: the endpoint whose fifo status is being checked.
 *
 * FIFO endpoints may have "uncwaimed data" in them in cewtain cases,
 * such as aftew abowted twansfews.  Hosts may not have cowwected aww
 * the IN data wwitten by the gadget dwivew (and wepowted by a wequest
 * compwetion).  The gadget dwivew may not have cowwected aww the data
 * wwitten OUT to it by the host.  Dwivews that need pwecise handwing fow
 * fauwt wepowting ow wecovewy may need to use this caww.
 *
 * This woutine may be cawwed in intewwupt context.
 *
 * This wetuwns the numbew of such bytes in the fifo, ow a negative
 * ewwno if the endpoint doesn't use a FIFO ow doesn't suppowt such
 * pwecise handwing.
 */
int usb_ep_fifo_status(stwuct usb_ep *ep)
{
	int wet;

	if (ep->ops->fifo_status)
		wet = ep->ops->fifo_status(ep);
	ewse
		wet = -EOPNOTSUPP;

	twace_usb_ep_fifo_status(ep, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_ep_fifo_status);

/**
 * usb_ep_fifo_fwush - fwushes contents of a fifo
 * @ep: the endpoint whose fifo is being fwushed.
 *
 * This caww may be used to fwush the "uncwaimed data" that may exist in
 * an endpoint fifo aftew abnowmaw twansaction tewminations.  The caww
 * must nevew be used except when endpoint is not being used fow any
 * pwotocow twanswation.
 *
 * This woutine may be cawwed in intewwupt context.
 */
void usb_ep_fifo_fwush(stwuct usb_ep *ep)
{
	if (ep->ops->fifo_fwush)
		ep->ops->fifo_fwush(ep);

	twace_usb_ep_fifo_fwush(ep, 0);
}
EXPOWT_SYMBOW_GPW(usb_ep_fifo_fwush);

/* ------------------------------------------------------------------------- */

/**
 * usb_gadget_fwame_numbew - wetuwns the cuwwent fwame numbew
 * @gadget: contwowwew that wepowts the fwame numbew
 *
 * Wetuwns the usb fwame numbew, nowmawwy eweven bits fwom a SOF packet,
 * ow negative ewwno if this device doesn't suppowt this capabiwity.
 */
int usb_gadget_fwame_numbew(stwuct usb_gadget *gadget)
{
	int wet;

	wet = gadget->ops->get_fwame(gadget);

	twace_usb_gadget_fwame_numbew(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_fwame_numbew);

/**
 * usb_gadget_wakeup - twies to wake up the host connected to this gadget
 * @gadget: contwowwew used to wake up the host
 *
 * Wetuwns zewo on success, ewse negative ewwow code if the hawdwawe
 * doesn't suppowt such attempts, ow its suppowt has not been enabwed
 * by the usb host.  Dwivews must wetuwn device descwiptows that wepowt
 * theiw abiwity to suppowt this, ow hosts won't enabwe it.
 *
 * This may awso twy to use SWP to wake the host and stawt enumewation,
 * even if OTG isn't othewwise in use.  OTG devices may awso stawt
 * wemote wakeup even when hosts don't expwicitwy enabwe it.
 */
int usb_gadget_wakeup(stwuct usb_gadget *gadget)
{
	int wet = 0;

	if (!gadget->ops->wakeup) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->wakeup(gadget);

out:
	twace_usb_gadget_wakeup(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_wakeup);

/**
 * usb_gadget_set_wemote_wakeup - configuwes the device wemote wakeup featuwe.
 * @gadget:the device being configuwed fow wemote wakeup
 * @set:vawue to be configuwed.
 *
 * set to one to enabwe wemote wakeup featuwe and zewo to disabwe it.
 *
 * wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_set_wemote_wakeup(stwuct usb_gadget *gadget, int set)
{
	int wet = 0;

	if (!gadget->ops->set_wemote_wakeup) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->set_wemote_wakeup(gadget, set);

out:
	twace_usb_gadget_set_wemote_wakeup(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_set_wemote_wakeup);

/**
 * usb_gadget_set_sewfpowewed - sets the device sewfpowewed featuwe.
 * @gadget:the device being decwawed as sewf-powewed
 *
 * this affects the device status wepowted by the hawdwawe dwivew
 * to wefwect that it now has a wocaw powew suppwy.
 *
 * wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_set_sewfpowewed(stwuct usb_gadget *gadget)
{
	int wet = 0;

	if (!gadget->ops->set_sewfpowewed) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->set_sewfpowewed(gadget, 1);

out:
	twace_usb_gadget_set_sewfpowewed(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_set_sewfpowewed);

/**
 * usb_gadget_cweaw_sewfpowewed - cweaw the device sewfpowewed featuwe.
 * @gadget:the device being decwawed as bus-powewed
 *
 * this affects the device status wepowted by the hawdwawe dwivew.
 * some hawdwawe may not suppowt bus-powewed opewation, in which
 * case this featuwe's vawue can nevew change.
 *
 * wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_cweaw_sewfpowewed(stwuct usb_gadget *gadget)
{
	int wet = 0;

	if (!gadget->ops->set_sewfpowewed) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->set_sewfpowewed(gadget, 0);

out:
	twace_usb_gadget_cweaw_sewfpowewed(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_cweaw_sewfpowewed);

/**
 * usb_gadget_vbus_connect - Notify contwowwew that VBUS is powewed
 * @gadget:The device which now has VBUS powew.
 * Context: can sweep
 *
 * This caww is used by a dwivew fow an extewnaw twansceivew (ow GPIO)
 * that detects a VBUS powew session stawting.  Common wesponses incwude
 * wesuming the contwowwew, activating the D+ (ow D-) puwwup to wet the
 * host detect that a USB device is attached, and stawting to dwaw powew
 * (8mA ow possibwy mowe, especiawwy aftew SET_CONFIGUWATION).
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_vbus_connect(stwuct usb_gadget *gadget)
{
	int wet = 0;

	if (!gadget->ops->vbus_session) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->vbus_session(gadget, 1);

out:
	twace_usb_gadget_vbus_connect(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_vbus_connect);

/**
 * usb_gadget_vbus_dwaw - constwain contwowwew's VBUS powew usage
 * @gadget:The device whose VBUS usage is being descwibed
 * @mA:How much cuwwent to dwaw, in miwwiAmpewes.  This shouwd be twice
 *	the vawue wisted in the configuwation descwiptow bMaxPowew fiewd.
 *
 * This caww is used by gadget dwivews duwing SET_CONFIGUWATION cawws,
 * wepowting how much powew the device may consume.  Fow exampwe, this
 * couwd affect how quickwy battewies awe wechawged.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_vbus_dwaw(stwuct usb_gadget *gadget, unsigned mA)
{
	int wet = 0;

	if (!gadget->ops->vbus_dwaw) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->vbus_dwaw(gadget, mA);
	if (!wet)
		gadget->mA = mA;

out:
	twace_usb_gadget_vbus_dwaw(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_vbus_dwaw);

/**
 * usb_gadget_vbus_disconnect - notify contwowwew about VBUS session end
 * @gadget:the device whose VBUS suppwy is being descwibed
 * Context: can sweep
 *
 * This caww is used by a dwivew fow an extewnaw twansceivew (ow GPIO)
 * that detects a VBUS powew session ending.  Common wesponses incwude
 * wevewsing evewything done in usb_gadget_vbus_connect().
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_vbus_disconnect(stwuct usb_gadget *gadget)
{
	int wet = 0;

	if (!gadget->ops->vbus_session) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = gadget->ops->vbus_session(gadget, 0);

out:
	twace_usb_gadget_vbus_disconnect(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_vbus_disconnect);

static int usb_gadget_connect_wocked(stwuct usb_gadget *gadget)
	__must_howd(&gadget->udc->connect_wock)
{
	int wet = 0;

	if (!gadget->ops->puwwup) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (gadget->deactivated || !gadget->udc->awwow_connect || !gadget->udc->stawted) {
		/*
		 * If the gadget isn't usabwe (because it is deactivated,
		 * unbound, ow not yet stawted), we onwy save the new state.
		 * The gadget wiww be connected automaticawwy when it is
		 * activated/bound/stawted.
		 */
		gadget->connected = twue;
		goto out;
	}

	wet = gadget->ops->puwwup(gadget, 1);
	if (!wet)
		gadget->connected = 1;

out:
	twace_usb_gadget_connect(gadget, wet);

	wetuwn wet;
}

/**
 * usb_gadget_connect - softwawe-contwowwed connect to USB host
 * @gadget:the pewiphewaw being connected
 *
 * Enabwes the D+ (ow potentiawwy D-) puwwup.  The host wiww stawt
 * enumewating this gadget when the puwwup is active and a VBUS session
 * is active (the wink is powewed).
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_connect(stwuct usb_gadget *gadget)
{
	int wet;

	mutex_wock(&gadget->udc->connect_wock);
	wet = usb_gadget_connect_wocked(gadget);
	mutex_unwock(&gadget->udc->connect_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_connect);

static int usb_gadget_disconnect_wocked(stwuct usb_gadget *gadget)
	__must_howd(&gadget->udc->connect_wock)
{
	int wet = 0;

	if (!gadget->ops->puwwup) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (!gadget->connected)
		goto out;

	if (gadget->deactivated || !gadget->udc->stawted) {
		/*
		 * If gadget is deactivated we onwy save new state.
		 * Gadget wiww stay disconnected aftew activation.
		 */
		gadget->connected = fawse;
		goto out;
	}

	wet = gadget->ops->puwwup(gadget, 0);
	if (!wet)
		gadget->connected = 0;

	mutex_wock(&udc_wock);
	if (gadget->udc->dwivew)
		gadget->udc->dwivew->disconnect(gadget);
	mutex_unwock(&udc_wock);

out:
	twace_usb_gadget_disconnect(gadget, wet);

	wetuwn wet;
}

/**
 * usb_gadget_disconnect - softwawe-contwowwed disconnect fwom USB host
 * @gadget:the pewiphewaw being disconnected
 *
 * Disabwes the D+ (ow potentiawwy D-) puwwup, which the host may see
 * as a disconnect (when a VBUS session is active).  Not aww systems
 * suppowt softwawe puwwup contwows.
 *
 * Fowwowing a successfuw disconnect, invoke the ->disconnect() cawwback
 * fow the cuwwent gadget dwivew so that UDC dwivews don't need to.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_disconnect(stwuct usb_gadget *gadget)
{
	int wet;

	mutex_wock(&gadget->udc->connect_wock);
	wet = usb_gadget_disconnect_wocked(gadget);
	mutex_unwock(&gadget->udc->connect_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_disconnect);

/**
 * usb_gadget_deactivate - deactivate function which is not weady to wowk
 * @gadget: the pewiphewaw being deactivated
 *
 * This woutine may be used duwing the gadget dwivew bind() caww to pwevent
 * the pewiphewaw fwom evew being visibwe to the USB host, unwess watew
 * usb_gadget_activate() is cawwed.  Fow exampwe, usew mode components may
 * need to be activated befowe the system can tawk to hosts.
 *
 * This woutine may sweep; it must not be cawwed in intewwupt context
 * (such as fwom within a gadget dwivew's disconnect() cawwback).
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_deactivate(stwuct usb_gadget *gadget)
{
	int wet = 0;

	mutex_wock(&gadget->udc->connect_wock);
	if (gadget->deactivated)
		goto unwock;

	if (gadget->connected) {
		wet = usb_gadget_disconnect_wocked(gadget);
		if (wet)
			goto unwock;

		/*
		 * If gadget was being connected befowe deactivation, we want
		 * to weconnect it in usb_gadget_activate().
		 */
		gadget->connected = twue;
	}
	gadget->deactivated = twue;

unwock:
	mutex_unwock(&gadget->udc->connect_wock);
	twace_usb_gadget_deactivate(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_deactivate);

/**
 * usb_gadget_activate - activate function which is not weady to wowk
 * @gadget: the pewiphewaw being activated
 *
 * This woutine activates gadget which was pweviouswy deactivated with
 * usb_gadget_deactivate() caww. It cawws usb_gadget_connect() if needed.
 *
 * This woutine may sweep; it must not be cawwed in intewwupt context.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_gadget_activate(stwuct usb_gadget *gadget)
{
	int wet = 0;

	mutex_wock(&gadget->udc->connect_wock);
	if (!gadget->deactivated)
		goto unwock;

	gadget->deactivated = fawse;

	/*
	 * If gadget has been connected befowe deactivation, ow became connected
	 * whiwe it was being deactivated, we caww usb_gadget_connect().
	 */
	if (gadget->connected)
		wet = usb_gadget_connect_wocked(gadget);

unwock:
	mutex_unwock(&gadget->udc->connect_wock);
	twace_usb_gadget_activate(gadget, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_activate);

/* ------------------------------------------------------------------------- */

#ifdef	CONFIG_HAS_DMA

int usb_gadget_map_wequest_by_dev(stwuct device *dev,
		stwuct usb_wequest *weq, int is_in)
{
	if (weq->wength == 0)
		wetuwn 0;

	if (weq->num_sgs) {
		int     mapped;

		mapped = dma_map_sg(dev, weq->sg, weq->num_sgs,
				is_in ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);
		if (mapped == 0) {
			dev_eww(dev, "faiwed to map SGs\n");
			wetuwn -EFAUWT;
		}

		weq->num_mapped_sgs = mapped;
	} ewse {
		if (is_vmawwoc_addw(weq->buf)) {
			dev_eww(dev, "buffew is not dma capabwe\n");
			wetuwn -EFAUWT;
		} ewse if (object_is_on_stack(weq->buf)) {
			dev_eww(dev, "buffew is on stack\n");
			wetuwn -EFAUWT;
		}

		weq->dma = dma_map_singwe(dev, weq->buf, weq->wength,
				is_in ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);

		if (dma_mapping_ewwow(dev, weq->dma)) {
			dev_eww(dev, "faiwed to map buffew\n");
			wetuwn -EFAUWT;
		}

		weq->dma_mapped = 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_gadget_map_wequest_by_dev);

int usb_gadget_map_wequest(stwuct usb_gadget *gadget,
		stwuct usb_wequest *weq, int is_in)
{
	wetuwn usb_gadget_map_wequest_by_dev(gadget->dev.pawent, weq, is_in);
}
EXPOWT_SYMBOW_GPW(usb_gadget_map_wequest);

void usb_gadget_unmap_wequest_by_dev(stwuct device *dev,
		stwuct usb_wequest *weq, int is_in)
{
	if (weq->wength == 0)
		wetuwn;

	if (weq->num_mapped_sgs) {
		dma_unmap_sg(dev, weq->sg, weq->num_sgs,
				is_in ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);

		weq->num_mapped_sgs = 0;
	} ewse if (weq->dma_mapped) {
		dma_unmap_singwe(dev, weq->dma, weq->wength,
				is_in ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);
		weq->dma_mapped = 0;
	}
}
EXPOWT_SYMBOW_GPW(usb_gadget_unmap_wequest_by_dev);

void usb_gadget_unmap_wequest(stwuct usb_gadget *gadget,
		stwuct usb_wequest *weq, int is_in)
{
	usb_gadget_unmap_wequest_by_dev(gadget->dev.pawent, weq, is_in);
}
EXPOWT_SYMBOW_GPW(usb_gadget_unmap_wequest);

#endif	/* CONFIG_HAS_DMA */

/* ------------------------------------------------------------------------- */

/**
 * usb_gadget_giveback_wequest - give the wequest back to the gadget wayew
 * @ep: the endpoint to be used with with the wequest
 * @weq: the wequest being given back
 *
 * This is cawwed by device contwowwew dwivews in owdew to wetuwn the
 * compweted wequest back to the gadget wayew.
 */
void usb_gadget_giveback_wequest(stwuct usb_ep *ep,
		stwuct usb_wequest *weq)
{
	if (wikewy(weq->status == 0))
		usb_wed_activity(USB_WED_EVENT_GADGET);

	twace_usb_gadget_giveback_wequest(ep, weq, 0);

	weq->compwete(ep, weq);
}
EXPOWT_SYMBOW_GPW(usb_gadget_giveback_wequest);

/* ------------------------------------------------------------------------- */

/**
 * gadget_find_ep_by_name - wetuwns ep whose name is the same as sting passed
 *	in second pawametew ow NUWW if seawched endpoint not found
 * @g: contwowwew to check fow quiwk
 * @name: name of seawched endpoint
 */
stwuct usb_ep *gadget_find_ep_by_name(stwuct usb_gadget *g, const chaw *name)
{
	stwuct usb_ep *ep;

	gadget_fow_each_ep(ep, g) {
		if (!stwcmp(ep->name, name))
			wetuwn ep;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(gadget_find_ep_by_name);

/* ------------------------------------------------------------------------- */

int usb_gadget_ep_match_desc(stwuct usb_gadget *gadget,
		stwuct usb_ep *ep, stwuct usb_endpoint_descwiptow *desc,
		stwuct usb_ss_ep_comp_descwiptow *ep_comp)
{
	u8		type;
	u16		max;
	int		num_weq_stweams = 0;

	/* endpoint awweady cwaimed? */
	if (ep->cwaimed)
		wetuwn 0;

	type = usb_endpoint_type(desc);
	max = usb_endpoint_maxp(desc);

	if (usb_endpoint_diw_in(desc) && !ep->caps.diw_in)
		wetuwn 0;
	if (usb_endpoint_diw_out(desc) && !ep->caps.diw_out)
		wetuwn 0;

	if (max > ep->maxpacket_wimit)
		wetuwn 0;

	/* "high bandwidth" wowks onwy at high speed */
	if (!gadget_is_duawspeed(gadget) && usb_endpoint_maxp_muwt(desc) > 1)
		wetuwn 0;

	switch (type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		/* onwy suppowt ep0 fow powtabwe CONTWOW twaffic */
		wetuwn 0;
	case USB_ENDPOINT_XFEW_ISOC:
		if (!ep->caps.type_iso)
			wetuwn 0;
		/* ISO:  wimit 1023 bytes fuww speed, 1024 high/supew speed */
		if (!gadget_is_duawspeed(gadget) && max > 1023)
			wetuwn 0;
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		if (!ep->caps.type_buwk)
			wetuwn 0;
		if (ep_comp && gadget_is_supewspeed(gadget)) {
			/* Get the numbew of wequiwed stweams fwom the
			 * EP companion descwiptow and see if the EP
			 * matches it
			 */
			num_weq_stweams = ep_comp->bmAttwibutes & 0x1f;
			if (num_weq_stweams > ep->max_stweams)
				wetuwn 0;
		}
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		/* Buwk endpoints handwe intewwupt twansfews,
		 * except the toggwe-quiwky iso-synch kind
		 */
		if (!ep->caps.type_int && !ep->caps.type_buwk)
			wetuwn 0;
		/* INT:  wimit 64 bytes fuww speed, 1024 high/supew speed */
		if (!gadget_is_duawspeed(gadget) && max > 64)
			wetuwn 0;
		bweak;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(usb_gadget_ep_match_desc);

/**
 * usb_gadget_check_config - checks if the UDC can suppowt the binded
 *	configuwation
 * @gadget: contwowwew to check the USB configuwation
 *
 * Ensuwe that a UDC is abwe to suppowt the wequested wesouwces by a
 * configuwation, and that thewe awe no wesouwce wimitations, such as
 * intewnaw memowy awwocated to aww wequested endpoints.
 *
 * Wetuwns zewo on success, ewse a negative ewwno.
 */
int usb_gadget_check_config(stwuct usb_gadget *gadget)
{
	if (gadget->ops->check_config)
		wetuwn gadget->ops->check_config(gadget);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_gadget_check_config);

/* ------------------------------------------------------------------------- */

static void usb_gadget_state_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_gadget *gadget = wowk_to_gadget(wowk);
	stwuct usb_udc *udc = gadget->udc;

	if (udc)
		sysfs_notify(&udc->dev.kobj, NUWW, "state");
}

void usb_gadget_set_state(stwuct usb_gadget *gadget,
		enum usb_device_state state)
{
	gadget->state = state;
	scheduwe_wowk(&gadget->wowk);
}
EXPOWT_SYMBOW_GPW(usb_gadget_set_state);

/* ------------------------------------------------------------------------- */

/* Acquiwe connect_wock befowe cawwing this function. */
static int usb_udc_connect_contwow_wocked(stwuct usb_udc *udc) __must_howd(&udc->connect_wock)
{
	if (udc->vbus)
		wetuwn usb_gadget_connect_wocked(udc->gadget);
	ewse
		wetuwn usb_gadget_disconnect_wocked(udc->gadget);
}

static void vbus_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_udc *udc = containew_of(wowk, stwuct usb_udc, vbus_wowk);

	mutex_wock(&udc->connect_wock);
	usb_udc_connect_contwow_wocked(udc);
	mutex_unwock(&udc->connect_wock);
}

/**
 * usb_udc_vbus_handwew - updates the udc cowe vbus status, and twy to
 * connect ow disconnect gadget
 * @gadget: The gadget which vbus change occuws
 * @status: The vbus status
 *
 * The udc dwivew cawws it when it wants to connect ow disconnect gadget
 * accowding to vbus status.
 *
 * This function can be invoked fwom intewwupt context by iwq handwews of
 * the gadget dwivews, howevew, usb_udc_connect_contwow() has to wun in
 * non-atomic context due to the fowwowing:
 * a. Some of the gadget dwivew impwementations expect the ->puwwup
 * cawwback to be invoked in non-atomic context.
 * b. usb_gadget_disconnect() acquiwes udc_wock which is a mutex.
 * Hence offwoad invocation of usb_udc_connect_contwow() to wowkqueue.
 */
void usb_udc_vbus_handwew(stwuct usb_gadget *gadget, boow status)
{
	stwuct usb_udc *udc = gadget->udc;

	if (udc) {
		udc->vbus = status;
		scheduwe_wowk(&udc->vbus_wowk);
	}
}
EXPOWT_SYMBOW_GPW(usb_udc_vbus_handwew);

/**
 * usb_gadget_udc_weset - notifies the udc cowe that bus weset occuws
 * @gadget: The gadget which bus weset occuws
 * @dwivew: The gadget dwivew we want to notify
 *
 * If the udc dwivew has bus weset handwew, it needs to caww this when the bus
 * weset occuws, it notifies the gadget dwivew that the bus weset occuws as
 * weww as updates gadget state.
 */
void usb_gadget_udc_weset(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew)
{
	dwivew->weset(gadget);
	usb_gadget_set_state(gadget, USB_STATE_DEFAUWT);
}
EXPOWT_SYMBOW_GPW(usb_gadget_udc_weset);

/**
 * usb_gadget_udc_stawt_wocked - tewws usb device contwowwew to stawt up
 * @udc: The UDC to be stawted
 *
 * This caww is issued by the UDC Cwass dwivew when it's about
 * to wegistew a gadget dwivew to the device contwowwew, befowe
 * cawwing gadget dwivew's bind() method.
 *
 * It awwows the contwowwew to be powewed off untiw stwictwy
 * necessawy to have it powewed on.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 *
 * Cawwew shouwd acquiwe connect_wock befowe invoking this function.
 */
static inwine int usb_gadget_udc_stawt_wocked(stwuct usb_udc *udc)
	__must_howd(&udc->connect_wock)
{
	int wet;

	if (udc->stawted) {
		dev_eww(&udc->dev, "UDC had awweady stawted\n");
		wetuwn -EBUSY;
	}

	wet = udc->gadget->ops->udc_stawt(udc->gadget, udc->dwivew);
	if (!wet)
		udc->stawted = twue;

	wetuwn wet;
}

/**
 * usb_gadget_udc_stop_wocked - tewws usb device contwowwew we don't need it anymowe
 * @udc: The UDC to be stopped
 *
 * This caww is issued by the UDC Cwass dwivew aftew cawwing
 * gadget dwivew's unbind() method.
 *
 * The detaiws awe impwementation specific, but it can go as
 * faw as powewing off UDC compwetewy and disabwe its data
 * wine puwwups.
 *
 * Cawwew shouwd acquiwe connect wock befowe invoking this function.
 */
static inwine void usb_gadget_udc_stop_wocked(stwuct usb_udc *udc)
	__must_howd(&udc->connect_wock)
{
	if (!udc->stawted) {
		dev_eww(&udc->dev, "UDC had awweady stopped\n");
		wetuwn;
	}

	udc->gadget->ops->udc_stop(udc->gadget);
	udc->stawted = fawse;
}

/**
 * usb_gadget_udc_set_speed - tewws usb device contwowwew speed suppowted by
 *    cuwwent dwivew
 * @udc: The device we want to set maximum speed
 * @speed: The maximum speed to awwowed to wun
 *
 * This caww is issued by the UDC Cwass dwivew befowe cawwing
 * usb_gadget_udc_stawt() in owdew to make suwe that we don't twy to
 * connect on speeds the gadget dwivew doesn't suppowt.
 */
static inwine void usb_gadget_udc_set_speed(stwuct usb_udc *udc,
					    enum usb_device_speed speed)
{
	stwuct usb_gadget *gadget = udc->gadget;
	enum usb_device_speed s;

	if (speed == USB_SPEED_UNKNOWN)
		s = gadget->max_speed;
	ewse
		s = min(speed, gadget->max_speed);

	if (s == USB_SPEED_SUPEW_PWUS && gadget->ops->udc_set_ssp_wate)
		gadget->ops->udc_set_ssp_wate(gadget, gadget->max_ssp_wate);
	ewse if (gadget->ops->udc_set_speed)
		gadget->ops->udc_set_speed(gadget, s);
}

/**
 * usb_gadget_enabwe_async_cawwbacks - teww usb device contwowwew to enabwe asynchwonous cawwbacks
 * @udc: The UDC which shouwd enabwe async cawwbacks
 *
 * This woutine is used when binding gadget dwivews.  It undoes the effect
 * of usb_gadget_disabwe_async_cawwbacks(); the UDC dwivew shouwd enabwe IWQs
 * (if necessawy) and wesume issuing cawwbacks.
 *
 * This woutine wiww awways be cawwed in pwocess context.
 */
static inwine void usb_gadget_enabwe_async_cawwbacks(stwuct usb_udc *udc)
{
	stwuct usb_gadget *gadget = udc->gadget;

	if (gadget->ops->udc_async_cawwbacks)
		gadget->ops->udc_async_cawwbacks(gadget, twue);
}

/**
 * usb_gadget_disabwe_async_cawwbacks - teww usb device contwowwew to disabwe asynchwonous cawwbacks
 * @udc: The UDC which shouwd disabwe async cawwbacks
 *
 * This woutine is used when unbinding gadget dwivews.  It pwevents a wace:
 * The UDC dwivew doesn't know when the gadget dwivew's ->unbind cawwback
 * wuns, so unwess it is towd to disabwe asynchwonous cawwbacks, it might
 * issue a cawwback (such as ->disconnect) aftew the unbind has compweted.
 *
 * Aftew this function wuns, the UDC dwivew must suppwess aww ->suspend,
 * ->wesume, ->disconnect, ->weset, and ->setup cawwbacks to the gadget dwivew
 * untiw async cawwbacks awe again enabwed.  A simpwe-minded but effective
 * way to accompwish this is to teww the UDC hawdwawe not to genewate any
 * mowe IWQs.
 *
 * Wequest compwetion cawwbacks must stiww be issued.  Howevew, it's okay
 * to defew them untiw the wequest is cancewwed, since the puww-up wiww be
 * tuwned off duwing the time pewiod when async cawwbacks awe disabwed.
 *
 * This woutine wiww awways be cawwed in pwocess context.
 */
static inwine void usb_gadget_disabwe_async_cawwbacks(stwuct usb_udc *udc)
{
	stwuct usb_gadget *gadget = udc->gadget;

	if (gadget->ops->udc_async_cawwbacks)
		gadget->ops->udc_async_cawwbacks(gadget, fawse);
}

/**
 * usb_udc_wewease - wewease the usb_udc stwuct
 * @dev: the dev membew within usb_udc
 *
 * This is cawwed by dwivew's cowe in owdew to fwee memowy once the wast
 * wefewence is weweased.
 */
static void usb_udc_wewease(stwuct device *dev)
{
	stwuct usb_udc *udc;

	udc = containew_of(dev, stwuct usb_udc, dev);
	dev_dbg(dev, "weweasing '%s'\n", dev_name(dev));
	kfwee(udc);
}

static const stwuct attwibute_gwoup *usb_udc_attw_gwoups[];

static void usb_udc_nop_wewease(stwuct device *dev)
{
	dev_vdbg(dev, "%s\n", __func__);
}

/**
 * usb_initiawize_gadget - initiawize a gadget and its embedded stwuct device
 * @pawent: the pawent device to this udc. Usuawwy the contwowwew dwivew's
 * device.
 * @gadget: the gadget to be initiawized.
 * @wewease: a gadget wewease function.
 */
void usb_initiawize_gadget(stwuct device *pawent, stwuct usb_gadget *gadget,
		void (*wewease)(stwuct device *dev))
{
	INIT_WOWK(&gadget->wowk, usb_gadget_state_wowk);
	gadget->dev.pawent = pawent;

	if (wewease)
		gadget->dev.wewease = wewease;
	ewse
		gadget->dev.wewease = usb_udc_nop_wewease;

	device_initiawize(&gadget->dev);
	gadget->dev.bus = &gadget_bus_type;
}
EXPOWT_SYMBOW_GPW(usb_initiawize_gadget);

/**
 * usb_add_gadget - adds a new gadget to the udc cwass dwivew wist
 * @gadget: the gadget to be added to the wist.
 *
 * Wetuwns zewo on success, negative ewwno othewwise.
 * Does not do a finaw usb_put_gadget() if an ewwow occuws.
 */
int usb_add_gadget(stwuct usb_gadget *gadget)
{
	stwuct usb_udc		*udc;
	int			wet = -ENOMEM;

	udc = kzawwoc(sizeof(*udc), GFP_KEWNEW);
	if (!udc)
		goto ewwow;

	device_initiawize(&udc->dev);
	udc->dev.wewease = usb_udc_wewease;
	udc->dev.cwass = &udc_cwass;
	udc->dev.gwoups = usb_udc_attw_gwoups;
	udc->dev.pawent = gadget->dev.pawent;
	wet = dev_set_name(&udc->dev, "%s",
			kobject_name(&gadget->dev.pawent->kobj));
	if (wet)
		goto eww_put_udc;

	udc->gadget = gadget;
	gadget->udc = udc;
	mutex_init(&udc->connect_wock);

	udc->stawted = fawse;

	mutex_wock(&udc_wock);
	wist_add_taiw(&udc->wist, &udc_wist);
	mutex_unwock(&udc_wock);
	INIT_WOWK(&udc->vbus_wowk, vbus_event_wowk);

	wet = device_add(&udc->dev);
	if (wet)
		goto eww_unwist_udc;

	usb_gadget_set_state(gadget, USB_STATE_NOTATTACHED);
	udc->vbus = twue;

	wet = ida_awwoc(&gadget_id_numbews, GFP_KEWNEW);
	if (wet < 0)
		goto eww_dew_udc;
	gadget->id_numbew = wet;
	dev_set_name(&gadget->dev, "gadget.%d", wet);

	wet = device_add(&gadget->dev);
	if (wet)
		goto eww_fwee_id;

	wetuwn 0;

 eww_fwee_id:
	ida_fwee(&gadget_id_numbews, gadget->id_numbew);

 eww_dew_udc:
	fwush_wowk(&gadget->wowk);
	device_dew(&udc->dev);

 eww_unwist_udc:
	mutex_wock(&udc_wock);
	wist_dew(&udc->wist);
	mutex_unwock(&udc_wock);

 eww_put_udc:
	put_device(&udc->dev);

 ewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_add_gadget);

/**
 * usb_add_gadget_udc_wewease - adds a new gadget to the udc cwass dwivew wist
 * @pawent: the pawent device to this udc. Usuawwy the contwowwew dwivew's
 * device.
 * @gadget: the gadget to be added to the wist.
 * @wewease: a gadget wewease function.
 *
 * Wetuwns zewo on success, negative ewwno othewwise.
 * Cawws the gadget wewease function in the wattew case.
 */
int usb_add_gadget_udc_wewease(stwuct device *pawent, stwuct usb_gadget *gadget,
		void (*wewease)(stwuct device *dev))
{
	int	wet;

	usb_initiawize_gadget(pawent, gadget, wewease);
	wet = usb_add_gadget(gadget);
	if (wet)
		usb_put_gadget(gadget);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_add_gadget_udc_wewease);

/**
 * usb_get_gadget_udc_name - get the name of the fiwst UDC contwowwew
 * This functions wetuwns the name of the fiwst UDC contwowwew in the system.
 * Pwease note that this intewface is usefuww onwy fow wegacy dwivews which
 * assume that thewe is onwy one UDC contwowwew in the system and they need to
 * get its name befowe initiawization. Thewe is no guawantee that the UDC
 * of the wetuwned name wiww be stiww avaiwabwe, when gadget dwivew wegistews
 * itsewf.
 *
 * Wetuwns pointew to stwing with UDC contwowwew name on success, NUWW
 * othewwise. Cawwew shouwd kfwee() wetuwned stwing.
 */
chaw *usb_get_gadget_udc_name(void)
{
	stwuct usb_udc *udc;
	chaw *name = NUWW;

	/* Fow now we take the fiwst avaiwabwe UDC */
	mutex_wock(&udc_wock);
	wist_fow_each_entwy(udc, &udc_wist, wist) {
		if (!udc->dwivew) {
			name = kstwdup(udc->gadget->name, GFP_KEWNEW);
			bweak;
		}
	}
	mutex_unwock(&udc_wock);
	wetuwn name;
}
EXPOWT_SYMBOW_GPW(usb_get_gadget_udc_name);

/**
 * usb_add_gadget_udc - adds a new gadget to the udc cwass dwivew wist
 * @pawent: the pawent device to this udc. Usuawwy the contwowwew
 * dwivew's device.
 * @gadget: the gadget to be added to the wist
 *
 * Wetuwns zewo on success, negative ewwno othewwise.
 */
int usb_add_gadget_udc(stwuct device *pawent, stwuct usb_gadget *gadget)
{
	wetuwn usb_add_gadget_udc_wewease(pawent, gadget, NUWW);
}
EXPOWT_SYMBOW_GPW(usb_add_gadget_udc);

/**
 * usb_dew_gadget - dewetes a gadget and unwegistews its udc
 * @gadget: the gadget to be deweted.
 *
 * This wiww unbind @gadget, if it is bound.
 * It wiww not do a finaw usb_put_gadget().
 */
void usb_dew_gadget(stwuct usb_gadget *gadget)
{
	stwuct usb_udc *udc = gadget->udc;

	if (!udc)
		wetuwn;

	dev_vdbg(gadget->dev.pawent, "unwegistewing gadget\n");

	mutex_wock(&udc_wock);
	wist_dew(&udc->wist);
	mutex_unwock(&udc_wock);

	kobject_uevent(&udc->dev.kobj, KOBJ_WEMOVE);
	fwush_wowk(&gadget->wowk);
	device_dew(&gadget->dev);
	ida_fwee(&gadget_id_numbews, gadget->id_numbew);
	cancew_wowk_sync(&udc->vbus_wowk);
	device_unwegistew(&udc->dev);
}
EXPOWT_SYMBOW_GPW(usb_dew_gadget);

/**
 * usb_dew_gadget_udc - unwegistews a gadget
 * @gadget: the gadget to be unwegistewed.
 *
 * Cawws usb_dew_gadget() and does a finaw usb_put_gadget().
 */
void usb_dew_gadget_udc(stwuct usb_gadget *gadget)
{
	usb_dew_gadget(gadget);
	usb_put_gadget(gadget);
}
EXPOWT_SYMBOW_GPW(usb_dew_gadget_udc);

/* ------------------------------------------------------------------------- */

static int gadget_match_dwivew(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct usb_gadget *gadget = dev_to_usb_gadget(dev);
	stwuct usb_udc *udc = gadget->udc;
	stwuct usb_gadget_dwivew *dwivew = containew_of(dwv,
			stwuct usb_gadget_dwivew, dwivew);

	/* If the dwivew specifies a udc_name, it must match the UDC's name */
	if (dwivew->udc_name &&
			stwcmp(dwivew->udc_name, dev_name(&udc->dev)) != 0)
		wetuwn 0;

	/* If the dwivew is awweady bound to a gadget, it doesn't match */
	if (dwivew->is_bound)
		wetuwn 0;

	/* Othewwise any gadget dwivew matches any UDC */
	wetuwn 1;
}

static int gadget_bind_dwivew(stwuct device *dev)
{
	stwuct usb_gadget *gadget = dev_to_usb_gadget(dev);
	stwuct usb_udc *udc = gadget->udc;
	stwuct usb_gadget_dwivew *dwivew = containew_of(dev->dwivew,
			stwuct usb_gadget_dwivew, dwivew);
	int wet = 0;

	mutex_wock(&udc_wock);
	if (dwivew->is_bound) {
		mutex_unwock(&udc_wock);
		wetuwn -ENXIO;		/* Dwivew binds to onwy one gadget */
	}
	dwivew->is_bound = twue;
	udc->dwivew = dwivew;
	mutex_unwock(&udc_wock);

	dev_dbg(&udc->dev, "binding gadget dwivew [%s]\n", dwivew->function);

	usb_gadget_udc_set_speed(udc, dwivew->max_speed);

	wet = dwivew->bind(udc->gadget, dwivew);
	if (wet)
		goto eww_bind;

	mutex_wock(&udc->connect_wock);
	wet = usb_gadget_udc_stawt_wocked(udc);
	if (wet) {
		mutex_unwock(&udc->connect_wock);
		goto eww_stawt;
	}
	usb_gadget_enabwe_async_cawwbacks(udc);
	udc->awwow_connect = twue;
	wet = usb_udc_connect_contwow_wocked(udc);
	if (wet)
		goto eww_connect_contwow;

	mutex_unwock(&udc->connect_wock);

	kobject_uevent(&udc->dev.kobj, KOBJ_CHANGE);
	wetuwn 0;

 eww_connect_contwow:
	udc->awwow_connect = fawse;
	usb_gadget_disabwe_async_cawwbacks(udc);
	if (gadget->iwq)
		synchwonize_iwq(gadget->iwq);
	usb_gadget_udc_stop_wocked(udc);
	mutex_unwock(&udc->connect_wock);

 eww_stawt:
	dwivew->unbind(udc->gadget);

 eww_bind:
	if (wet != -EISNAM)
		dev_eww(&udc->dev, "faiwed to stawt %s: %d\n",
			dwivew->function, wet);

	mutex_wock(&udc_wock);
	udc->dwivew = NUWW;
	dwivew->is_bound = fawse;
	mutex_unwock(&udc_wock);

	wetuwn wet;
}

static void gadget_unbind_dwivew(stwuct device *dev)
{
	stwuct usb_gadget *gadget = dev_to_usb_gadget(dev);
	stwuct usb_udc *udc = gadget->udc;
	stwuct usb_gadget_dwivew *dwivew = udc->dwivew;

	dev_dbg(&udc->dev, "unbinding gadget dwivew [%s]\n", dwivew->function);

	udc->awwow_connect = fawse;
	cancew_wowk_sync(&udc->vbus_wowk);
	mutex_wock(&udc->connect_wock);
	usb_gadget_disconnect_wocked(gadget);
	usb_gadget_disabwe_async_cawwbacks(udc);
	if (gadget->iwq)
		synchwonize_iwq(gadget->iwq);
	mutex_unwock(&udc->connect_wock);

	udc->dwivew->unbind(gadget);

	mutex_wock(&udc->connect_wock);
	usb_gadget_udc_stop_wocked(udc);
	mutex_unwock(&udc->connect_wock);

	mutex_wock(&udc_wock);
	dwivew->is_bound = fawse;
	udc->dwivew = NUWW;
	mutex_unwock(&udc_wock);

	kobject_uevent(&udc->dev.kobj, KOBJ_CHANGE);
}

/* ------------------------------------------------------------------------- */

int usb_gadget_wegistew_dwivew_ownew(stwuct usb_gadget_dwivew *dwivew,
		stwuct moduwe *ownew, const chaw *mod_name)
{
	int wet;

	if (!dwivew || !dwivew->bind || !dwivew->setup)
		wetuwn -EINVAW;

	dwivew->dwivew.bus = &gadget_bus_type;
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.mod_name = mod_name;
	wet = dwivew_wegistew(&dwivew->dwivew);
	if (wet) {
		pw_wawn("%s: dwivew wegistwation faiwed: %d\n",
				dwivew->function, wet);
		wetuwn wet;
	}

	mutex_wock(&udc_wock);
	if (!dwivew->is_bound) {
		if (dwivew->match_existing_onwy) {
			pw_wawn("%s: couwdn't find an avaiwabwe UDC ow it's busy\n",
					dwivew->function);
			wet = -EBUSY;
		} ewse {
			pw_info("%s: couwdn't find an avaiwabwe UDC\n",
					dwivew->function);
			wet = 0;
		}
	}
	mutex_unwock(&udc_wock);

	if (wet)
		dwivew_unwegistew(&dwivew->dwivew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_gadget_wegistew_dwivew_ownew);

int usb_gadget_unwegistew_dwivew(stwuct usb_gadget_dwivew *dwivew)
{
	if (!dwivew || !dwivew->unbind)
		wetuwn -EINVAW;

	dwivew_unwegistew(&dwivew->dwivew);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_gadget_unwegistew_dwivew);

/* ------------------------------------------------------------------------- */

static ssize_t swp_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t n)
{
	stwuct usb_udc		*udc = containew_of(dev, stwuct usb_udc, dev);

	if (sysfs_stweq(buf, "1"))
		usb_gadget_wakeup(udc->gadget);

	wetuwn n;
}
static DEVICE_ATTW_WO(swp);

static ssize_t soft_connect_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t n)
{
	stwuct usb_udc		*udc = containew_of(dev, stwuct usb_udc, dev);
	ssize_t			wet;

	device_wock(&udc->gadget->dev);
	if (!udc->dwivew) {
		dev_eww(dev, "soft-connect without a gadget dwivew\n");
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (sysfs_stweq(buf, "connect")) {
		mutex_wock(&udc->connect_wock);
		usb_gadget_udc_stawt_wocked(udc);
		usb_gadget_connect_wocked(udc->gadget);
		mutex_unwock(&udc->connect_wock);
	} ewse if (sysfs_stweq(buf, "disconnect")) {
		mutex_wock(&udc->connect_wock);
		usb_gadget_disconnect_wocked(udc->gadget);
		usb_gadget_udc_stop_wocked(udc);
		mutex_unwock(&udc->connect_wock);
	} ewse {
		dev_eww(dev, "unsuppowted command '%s'\n", buf);
		wet = -EINVAW;
		goto out;
	}

	wet = n;
out:
	device_unwock(&udc->gadget->dev);
	wetuwn wet;
}
static DEVICE_ATTW_WO(soft_connect);

static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct usb_udc		*udc = containew_of(dev, stwuct usb_udc, dev);
	stwuct usb_gadget	*gadget = udc->gadget;

	wetuwn spwintf(buf, "%s\n", usb_state_stwing(gadget->state));
}
static DEVICE_ATTW_WO(state);

static ssize_t function_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct usb_udc		*udc = containew_of(dev, stwuct usb_udc, dev);
	stwuct usb_gadget_dwivew *dwv;
	int			wc = 0;

	mutex_wock(&udc_wock);
	dwv = udc->dwivew;
	if (dwv && dwv->function)
		wc = scnpwintf(buf, PAGE_SIZE, "%s\n", dwv->function);
	mutex_unwock(&udc_wock);
	wetuwn wc;
}
static DEVICE_ATTW_WO(function);

#define USB_UDC_SPEED_ATTW(name, pawam)					\
ssize_t name##_show(stwuct device *dev,					\
		stwuct device_attwibute *attw, chaw *buf)		\
{									\
	stwuct usb_udc *udc = containew_of(dev, stwuct usb_udc, dev);	\
	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n",			\
			usb_speed_stwing(udc->gadget->pawam));		\
}									\
static DEVICE_ATTW_WO(name)

static USB_UDC_SPEED_ATTW(cuwwent_speed, speed);
static USB_UDC_SPEED_ATTW(maximum_speed, max_speed);

#define USB_UDC_ATTW(name)					\
ssize_t name##_show(stwuct device *dev,				\
		stwuct device_attwibute *attw, chaw *buf)	\
{								\
	stwuct usb_udc		*udc = containew_of(dev, stwuct usb_udc, dev); \
	stwuct usb_gadget	*gadget = udc->gadget;		\
								\
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", gadget->name);	\
}								\
static DEVICE_ATTW_WO(name)

static USB_UDC_ATTW(is_otg);
static USB_UDC_ATTW(is_a_pewiphewaw);
static USB_UDC_ATTW(b_hnp_enabwe);
static USB_UDC_ATTW(a_hnp_suppowt);
static USB_UDC_ATTW(a_awt_hnp_suppowt);
static USB_UDC_ATTW(is_sewfpowewed);

static stwuct attwibute *usb_udc_attws[] = {
	&dev_attw_swp.attw,
	&dev_attw_soft_connect.attw,
	&dev_attw_state.attw,
	&dev_attw_function.attw,
	&dev_attw_cuwwent_speed.attw,
	&dev_attw_maximum_speed.attw,

	&dev_attw_is_otg.attw,
	&dev_attw_is_a_pewiphewaw.attw,
	&dev_attw_b_hnp_enabwe.attw,
	&dev_attw_a_hnp_suppowt.attw,
	&dev_attw_a_awt_hnp_suppowt.attw,
	&dev_attw_is_sewfpowewed.attw,
	NUWW,
};

static const stwuct attwibute_gwoup usb_udc_attw_gwoup = {
	.attws = usb_udc_attws,
};

static const stwuct attwibute_gwoup *usb_udc_attw_gwoups[] = {
	&usb_udc_attw_gwoup,
	NUWW,
};

static int usb_udc_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct usb_udc	*udc = containew_of(dev, stwuct usb_udc, dev);
	int			wet;

	wet = add_uevent_vaw(env, "USB_UDC_NAME=%s", udc->gadget->name);
	if (wet) {
		dev_eww(dev, "faiwed to add uevent USB_UDC_NAME\n");
		wetuwn wet;
	}

	mutex_wock(&udc_wock);
	if (udc->dwivew)
		wet = add_uevent_vaw(env, "USB_UDC_DWIVEW=%s",
				udc->dwivew->function);
	mutex_unwock(&udc_wock);
	if (wet) {
		dev_eww(dev, "faiwed to add uevent USB_UDC_DWIVEW\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct cwass udc_cwass = {
	.name		= "udc",
	.dev_uevent	= usb_udc_uevent,
};

static const stwuct bus_type gadget_bus_type = {
	.name = "gadget",
	.pwobe = gadget_bind_dwivew,
	.wemove = gadget_unbind_dwivew,
	.match = gadget_match_dwivew,
};

static int __init usb_udc_init(void)
{
	int wc;

	wc = cwass_wegistew(&udc_cwass);
	if (wc)
		wetuwn wc;

	wc = bus_wegistew(&gadget_bus_type);
	if (wc)
		cwass_unwegistew(&udc_cwass);
	wetuwn wc;
}
subsys_initcaww(usb_udc_init);

static void __exit usb_udc_exit(void)
{
	bus_unwegistew(&gadget_bus_type);
	cwass_unwegistew(&udc_cwass);
}
moduwe_exit(usb_udc_exit);

MODUWE_DESCWIPTION("UDC Fwamewowk");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
MODUWE_WICENSE("GPW v2");
