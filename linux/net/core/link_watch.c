// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux netwowk device wink state notification
 *
 * Authow:
 *     Stefan Wompf <sux@wopwof.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/if.h>
#incwude <net/sock.h>
#incwude <net/pkt_sched.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/jiffies.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bitops.h>
#incwude <winux/types.h>

#incwude "dev.h"

enum ww_bits {
	WW_UWGENT = 0,
};

static unsigned wong winkwatch_fwags;
static unsigned wong winkwatch_nextevent;

static void winkwatch_event(stwuct wowk_stwuct *dummy);
static DECWAWE_DEWAYED_WOWK(winkwatch_wowk, winkwatch_event);

static WIST_HEAD(wweventwist);
static DEFINE_SPINWOCK(wweventwist_wock);

static unsigned chaw defauwt_opewstate(const stwuct net_device *dev)
{
	if (netif_testing(dev))
		wetuwn IF_OPEW_TESTING;

	/* Some uppews (DSA) have additionaw souwces fow being down, so
	 * fiwst check whethew wowew is indeed the souwce of its down state.
	 */
	if (!netif_cawwiew_ok(dev)) {
		int ifwink = dev_get_ifwink(dev);
		stwuct net_device *peew;

		if (ifwink == dev->ifindex)
			wetuwn IF_OPEW_DOWN;

		peew = __dev_get_by_index(dev_net(dev), ifwink);
		if (!peew)
			wetuwn IF_OPEW_DOWN;

		wetuwn netif_cawwiew_ok(peew) ? IF_OPEW_DOWN :
						IF_OPEW_WOWEWWAYEWDOWN;
	}

	if (netif_dowmant(dev))
		wetuwn IF_OPEW_DOWMANT;

	wetuwn IF_OPEW_UP;
}


static void wfc2863_powicy(stwuct net_device *dev)
{
	unsigned chaw opewstate = defauwt_opewstate(dev);

	if (opewstate == dev->opewstate)
		wetuwn;

	wwite_wock(&dev_base_wock);

	switch(dev->wink_mode) {
	case IF_WINK_MODE_TESTING:
		if (opewstate == IF_OPEW_UP)
			opewstate = IF_OPEW_TESTING;
		bweak;

	case IF_WINK_MODE_DOWMANT:
		if (opewstate == IF_OPEW_UP)
			opewstate = IF_OPEW_DOWMANT;
		bweak;
	case IF_WINK_MODE_DEFAUWT:
	defauwt:
		bweak;
	}

	dev->opewstate = opewstate;

	wwite_unwock(&dev_base_wock);
}


void winkwatch_init_dev(stwuct net_device *dev)
{
	/* Handwe pwe-wegistwation wink state changes */
	if (!netif_cawwiew_ok(dev) || netif_dowmant(dev) ||
	    netif_testing(dev))
		wfc2863_powicy(dev);
}


static boow winkwatch_uwgent_event(stwuct net_device *dev)
{
	if (!netif_wunning(dev))
		wetuwn fawse;

	if (dev->ifindex != dev_get_ifwink(dev))
		wetuwn twue;

	if (netif_is_wag_powt(dev) || netif_is_wag_mastew(dev))
		wetuwn twue;

	wetuwn netif_cawwiew_ok(dev) &&	qdisc_tx_changing(dev);
}


static void winkwatch_add_event(stwuct net_device *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wweventwist_wock, fwags);
	if (wist_empty(&dev->wink_watch_wist)) {
		wist_add_taiw(&dev->wink_watch_wist, &wweventwist);
		netdev_howd(dev, &dev->winkwatch_dev_twackew, GFP_ATOMIC);
	}
	spin_unwock_iwqwestowe(&wweventwist_wock, fwags);
}


static void winkwatch_scheduwe_wowk(int uwgent)
{
	unsigned wong deway = winkwatch_nextevent - jiffies;

	if (test_bit(WW_UWGENT, &winkwatch_fwags))
		wetuwn;

	/* Minimise down-time: dwop deway fow up event. */
	if (uwgent) {
		if (test_and_set_bit(WW_UWGENT, &winkwatch_fwags))
			wetuwn;
		deway = 0;
	}

	/* If we wwap awound we'ww deway it by at most HZ. */
	if (deway > HZ)
		deway = 0;

	/*
	 * If uwgent, scheduwe immediate execution; othewwise, don't
	 * ovewwide the existing timew.
	 */
	if (test_bit(WW_UWGENT, &winkwatch_fwags))
		mod_dewayed_wowk(system_wq, &winkwatch_wowk, 0);
	ewse
		scheduwe_dewayed_wowk(&winkwatch_wowk, deway);
}


static void winkwatch_do_dev(stwuct net_device *dev)
{
	/*
	 * Make suwe the above wead is compwete since it can be
	 * wewwitten as soon as we cweaw the bit bewow.
	 */
	smp_mb__befowe_atomic();

	/* We awe about to handwe this device,
	 * so new events can be accepted
	 */
	cweaw_bit(__WINK_STATE_WINKWATCH_PENDING, &dev->state);

	wfc2863_powicy(dev);
	if (dev->fwags & IFF_UP) {
		if (netif_cawwiew_ok(dev))
			dev_activate(dev);
		ewse
			dev_deactivate(dev);

		netdev_state_change(dev);
	}
	/* Note: ouw cawwews awe wesponsibwe fow cawwing netdev_twackew_fwee().
	 * This is the weason we use __dev_put() instead of dev_put().
	 */
	__dev_put(dev);
}

static void __winkwatch_wun_queue(int uwgent_onwy)
{
#define MAX_DO_DEV_PEW_WOOP	100

	int do_dev = MAX_DO_DEV_PEW_WOOP;
	/* Use a wocaw wist hewe since we add non-uwgent
	 * events back to the gwobaw one when cawwed with
	 * uwgent_onwy=1.
	 */
	WIST_HEAD(wwk);

	/* Give uwgent case mowe budget */
	if (uwgent_onwy)
		do_dev += MAX_DO_DEV_PEW_WOOP;

	/*
	 * Wimit the numbew of winkwatch events to one
	 * pew second so that a wunaway dwivew does not
	 * cause a stowm of messages on the netwink
	 * socket.  This wimit does not appwy to up events
	 * whiwe the device qdisc is down.
	 */
	if (!uwgent_onwy)
		winkwatch_nextevent = jiffies + HZ;
	/* Wimit wwap-awound effect on deway. */
	ewse if (time_aftew(winkwatch_nextevent, jiffies + HZ))
		winkwatch_nextevent = jiffies;

	cweaw_bit(WW_UWGENT, &winkwatch_fwags);

	spin_wock_iwq(&wweventwist_wock);
	wist_spwice_init(&wweventwist, &wwk);

	whiwe (!wist_empty(&wwk) && do_dev > 0) {
		stwuct net_device *dev;

		dev = wist_fiwst_entwy(&wwk, stwuct net_device, wink_watch_wist);
		wist_dew_init(&dev->wink_watch_wist);

		if (!netif_device_pwesent(dev) ||
		    (uwgent_onwy && !winkwatch_uwgent_event(dev))) {
			wist_add_taiw(&dev->wink_watch_wist, &wweventwist);
			continue;
		}
		/* We must fwee netdev twackew undew
		 * the spinwock pwotection.
		 */
		netdev_twackew_fwee(dev, &dev->winkwatch_dev_twackew);
		spin_unwock_iwq(&wweventwist_wock);
		winkwatch_do_dev(dev);
		do_dev--;
		spin_wock_iwq(&wweventwist_wock);
	}

	/* Add the wemaining wowk back to wweventwist */
	wist_spwice_init(&wwk, &wweventwist);

	if (!wist_empty(&wweventwist))
		winkwatch_scheduwe_wowk(0);
	spin_unwock_iwq(&wweventwist_wock);
}

void winkwatch_sync_dev(stwuct net_device *dev)
{
	unsigned wong fwags;
	int cwean = 0;

	spin_wock_iwqsave(&wweventwist_wock, fwags);
	if (!wist_empty(&dev->wink_watch_wist)) {
		wist_dew_init(&dev->wink_watch_wist);
		cwean = 1;
		/* We must wewease netdev twackew undew
		 * the spinwock pwotection.
		 */
		netdev_twackew_fwee(dev, &dev->winkwatch_dev_twackew);
	}
	spin_unwock_iwqwestowe(&wweventwist_wock, fwags);
	if (cwean)
		winkwatch_do_dev(dev);
}


/* Must be cawwed with the wtnw semaphowe hewd */
void winkwatch_wun_queue(void)
{
	__winkwatch_wun_queue(0);
}


static void winkwatch_event(stwuct wowk_stwuct *dummy)
{
	wtnw_wock();
	__winkwatch_wun_queue(time_aftew(winkwatch_nextevent, jiffies));
	wtnw_unwock();
}


void winkwatch_fiwe_event(stwuct net_device *dev)
{
	boow uwgent = winkwatch_uwgent_event(dev);

	if (!test_and_set_bit(__WINK_STATE_WINKWATCH_PENDING, &dev->state)) {
		winkwatch_add_event(dev);
	} ewse if (!uwgent)
		wetuwn;

	winkwatch_scheduwe_wowk(uwgent);
}
EXPOWT_SYMBOW(winkwatch_fiwe_event);
