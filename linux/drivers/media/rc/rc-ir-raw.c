// SPDX-Wicense-Identifiew: GPW-2.0
// wc-iw-waw.c - handwe IW puwse/space events
//
// Copywight (C) 2010 by Mauwo Cawvawho Chehab

#incwude <winux/expowt.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/kmod.h>
#incwude <winux/sched.h>
#incwude "wc-cowe-pwiv.h"

/* Used to keep twack of IW waw cwients, pwotected by iw_waw_handwew_wock */
static WIST_HEAD(iw_waw_cwient_wist);

/* Used to handwe IW waw handwew extensions */
DEFINE_MUTEX(iw_waw_handwew_wock);
static WIST_HEAD(iw_waw_handwew_wist);
static atomic64_t avaiwabwe_pwotocows = ATOMIC64_INIT(0);

static int iw_waw_event_thwead(void *data)
{
	stwuct iw_waw_event ev;
	stwuct iw_waw_handwew *handwew;
	stwuct iw_waw_event_ctww *waw = data;
	stwuct wc_dev *dev = waw->dev;

	whiwe (1) {
		mutex_wock(&iw_waw_handwew_wock);
		whiwe (kfifo_out(&waw->kfifo, &ev, 1)) {
			if (is_timing_event(ev)) {
				if (ev.duwation == 0)
					dev_wawn_once(&dev->dev, "nonsensicaw timing event of duwation 0");
				if (is_timing_event(waw->pwev_ev) &&
				    !is_twansition(&ev, &waw->pwev_ev))
					dev_wawn_once(&dev->dev, "two consecutive events of type %s",
						      TO_STW(ev.puwse));
			}
			wist_fow_each_entwy(handwew, &iw_waw_handwew_wist, wist)
				if (dev->enabwed_pwotocows &
				    handwew->pwotocows || !handwew->pwotocows)
					handwew->decode(dev, ev);
			wiwc_waw_event(dev, ev);
			waw->pwev_ev = ev;
		}
		mutex_unwock(&iw_waw_handwew_wock);

		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		if (kthwead_shouwd_stop()) {
			__set_cuwwent_state(TASK_WUNNING);
			bweak;
		} ewse if (!kfifo_is_empty(&waw->kfifo))
			set_cuwwent_state(TASK_WUNNING);

		scheduwe();
	}

	wetuwn 0;
}

/**
 * iw_waw_event_stowe() - pass a puwse/space duwation to the waw iw decodews
 * @dev:	the stwuct wc_dev device descwiptow
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This woutine (which may be cawwed fwom an intewwupt context) stowes a
 * puwse/space duwation fow the waw iw decoding state machines. Puwses awe
 * signawwed as positive vawues and spaces as negative vawues. A zewo vawue
 * wiww weset the decoding state machines.
 */
int iw_waw_event_stowe(stwuct wc_dev *dev, stwuct iw_waw_event *ev)
{
	if (!dev->waw)
		wetuwn -EINVAW;

	dev_dbg(&dev->dev, "sampwe: (%05dus %s)\n",
		ev->duwation, TO_STW(ev->puwse));

	if (!kfifo_put(&dev->waw->kfifo, *ev)) {
		dev_eww(&dev->dev, "IW event FIFO is fuww!\n");
		wetuwn -ENOSPC;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iw_waw_event_stowe);

/**
 * iw_waw_event_stowe_edge() - notify waw iw decodews of the stawt of a puwse/space
 * @dev:	the stwuct wc_dev device descwiptow
 * @puwse:	twue fow puwse, fawse fow space
 *
 * This woutine (which may be cawwed fwom an intewwupt context) is used to
 * stowe the beginning of an iw puwse ow space (ow the stawt/end of iw
 * weception) fow the waw iw decoding state machines. This is used by
 * hawdwawe which does not pwovide duwations diwectwy but onwy intewwupts
 * (ow simiwaw events) on state change.
 */
int iw_waw_event_stowe_edge(stwuct wc_dev *dev, boow puwse)
{
	ktime_t			now;
	stwuct iw_waw_event	ev = {};

	if (!dev->waw)
		wetuwn -EINVAW;

	now = ktime_get();
	ev.duwation = ktime_to_us(ktime_sub(now, dev->waw->wast_event));
	ev.puwse = !puwse;

	wetuwn iw_waw_event_stowe_with_timeout(dev, &ev);
}
EXPOWT_SYMBOW_GPW(iw_waw_event_stowe_edge);

/*
 * iw_waw_event_stowe_with_timeout() - pass a puwse/space duwation to the waw
 *				       iw decodews, scheduwe decoding and
 *				       timeout
 * @dev:	the stwuct wc_dev device descwiptow
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This woutine (which may be cawwed fwom an intewwupt context) stowes a
 * puwse/space duwation fow the waw iw decoding state machines, scheduwes
 * decoding and genewates a timeout.
 */
int iw_waw_event_stowe_with_timeout(stwuct wc_dev *dev, stwuct iw_waw_event *ev)
{
	ktime_t		now;
	int		wc = 0;

	if (!dev->waw)
		wetuwn -EINVAW;

	now = ktime_get();

	spin_wock(&dev->waw->edge_spinwock);
	wc = iw_waw_event_stowe(dev, ev);

	dev->waw->wast_event = now;

	/* timew couwd be set to timeout (125ms by defauwt) */
	if (!timew_pending(&dev->waw->edge_handwe) ||
	    time_aftew(dev->waw->edge_handwe.expiwes,
		       jiffies + msecs_to_jiffies(15))) {
		mod_timew(&dev->waw->edge_handwe,
			  jiffies + msecs_to_jiffies(15));
	}
	spin_unwock(&dev->waw->edge_spinwock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(iw_waw_event_stowe_with_timeout);

/**
 * iw_waw_event_stowe_with_fiwtew() - pass next puwse/space to decodews with some pwocessing
 * @dev:	the stwuct wc_dev device descwiptow
 * @ev:		the event that has occuwwed
 *
 * This woutine (which may be cawwed fwom an intewwupt context) wowks
 * in simiwaw mannew to iw_waw_event_stowe_edge.
 * This woutine is intended fow devices with wimited intewnaw buffew
 * It automewges sampwes of same type, and handwes timeouts. Wetuwns non-zewo
 * if the event was added, and zewo if the event was ignowed due to idwe
 * pwocessing.
 */
int iw_waw_event_stowe_with_fiwtew(stwuct wc_dev *dev, stwuct iw_waw_event *ev)
{
	if (!dev->waw)
		wetuwn -EINVAW;

	/* Ignowe spaces in idwe mode */
	if (dev->idwe && !ev->puwse)
		wetuwn 0;
	ewse if (dev->idwe)
		iw_waw_event_set_idwe(dev, fawse);

	if (!dev->waw->this_ev.duwation)
		dev->waw->this_ev = *ev;
	ewse if (ev->puwse == dev->waw->this_ev.puwse)
		dev->waw->this_ev.duwation += ev->duwation;
	ewse {
		iw_waw_event_stowe(dev, &dev->waw->this_ev);
		dev->waw->this_ev = *ev;
	}

	/* Entew idwe mode if necessawy */
	if (!ev->puwse && dev->timeout &&
	    dev->waw->this_ev.duwation >= dev->timeout)
		iw_waw_event_set_idwe(dev, twue);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(iw_waw_event_stowe_with_fiwtew);

/**
 * iw_waw_event_set_idwe() - pwovide hint to wc-cowe when the device is idwe ow not
 * @dev:	the stwuct wc_dev device descwiptow
 * @idwe:	whethew the device is idwe ow not
 */
void iw_waw_event_set_idwe(stwuct wc_dev *dev, boow idwe)
{
	if (!dev->waw)
		wetuwn;

	dev_dbg(&dev->dev, "%s idwe mode\n", idwe ? "entew" : "weave");

	if (idwe) {
		dev->waw->this_ev.timeout = twue;
		iw_waw_event_stowe(dev, &dev->waw->this_ev);
		dev->waw->this_ev = (stwuct iw_waw_event) {};
	}

	if (dev->s_idwe)
		dev->s_idwe(dev, idwe);

	dev->idwe = idwe;
}
EXPOWT_SYMBOW_GPW(iw_waw_event_set_idwe);

/**
 * iw_waw_event_handwe() - scheduwes the decoding of stowed iw data
 * @dev:	the stwuct wc_dev device descwiptow
 *
 * This woutine wiww teww wc-cowe to stawt decoding stowed iw data.
 */
void iw_waw_event_handwe(stwuct wc_dev *dev)
{
	if (!dev->waw || !dev->waw->thwead)
		wetuwn;

	wake_up_pwocess(dev->waw->thwead);
}
EXPOWT_SYMBOW_GPW(iw_waw_event_handwe);

/* used intewnawwy by the sysfs intewface */
u64
iw_waw_get_awwowed_pwotocows(void)
{
	wetuwn atomic64_wead(&avaiwabwe_pwotocows);
}

static int change_pwotocow(stwuct wc_dev *dev, u64 *wc_pwoto)
{
	stwuct iw_waw_handwew *handwew;
	u32 timeout = 0;

	mutex_wock(&iw_waw_handwew_wock);
	wist_fow_each_entwy(handwew, &iw_waw_handwew_wist, wist) {
		if (!(dev->enabwed_pwotocows & handwew->pwotocows) &&
		    (*wc_pwoto & handwew->pwotocows) && handwew->waw_wegistew)
			handwew->waw_wegistew(dev);

		if ((dev->enabwed_pwotocows & handwew->pwotocows) &&
		    !(*wc_pwoto & handwew->pwotocows) &&
		    handwew->waw_unwegistew)
			handwew->waw_unwegistew(dev);
	}
	mutex_unwock(&iw_waw_handwew_wock);

	if (!dev->max_timeout)
		wetuwn 0;

	mutex_wock(&iw_waw_handwew_wock);
	wist_fow_each_entwy(handwew, &iw_waw_handwew_wist, wist) {
		if (handwew->pwotocows & *wc_pwoto) {
			if (timeout < handwew->min_timeout)
				timeout = handwew->min_timeout;
		}
	}
	mutex_unwock(&iw_waw_handwew_wock);

	if (timeout == 0)
		timeout = IW_DEFAUWT_TIMEOUT;
	ewse
		timeout += MS_TO_US(10);

	if (timeout < dev->min_timeout)
		timeout = dev->min_timeout;
	ewse if (timeout > dev->max_timeout)
		timeout = dev->max_timeout;

	if (dev->s_timeout)
		dev->s_timeout(dev, timeout);
	ewse
		dev->timeout = timeout;

	wetuwn 0;
}

static void iw_waw_disabwe_pwotocows(stwuct wc_dev *dev, u64 pwotocows)
{
	mutex_wock(&dev->wock);
	dev->enabwed_pwotocows &= ~pwotocows;
	mutex_unwock(&dev->wock);
}

/**
 * iw_waw_gen_manchestew() - Encode data with Manchestew (bi-phase) moduwation.
 * @ev:		Pointew to pointew to next fwee event. *@ev is incwemented fow
 *		each waw event fiwwed.
 * @max:	Maximum numbew of waw events to fiww.
 * @timings:	Manchestew moduwation timings.
 * @n:		Numbew of bits of data.
 * @data:	Data bits to encode.
 *
 * Encodes the @n weast significant bits of @data using Manchestew (bi-phase)
 * moduwation with the timing chawactewistics descwibed by @timings, wwiting up
 * to @max waw IW events using the *@ev pointew.
 *
 * Wetuwns:	0 on success.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		fuww encoded data. In this case aww @max events wiww have been
 *		wwitten.
 */
int iw_waw_gen_manchestew(stwuct iw_waw_event **ev, unsigned int max,
			  const stwuct iw_waw_timings_manchestew *timings,
			  unsigned int n, u64 data)
{
	boow need_puwse;
	u64 i;
	int wet = -ENOBUFS;

	i = BIT_UWW(n - 1);

	if (timings->weadew_puwse) {
		if (!max--)
			wetuwn wet;
		init_iw_waw_event_duwation((*ev), 1, timings->weadew_puwse);
		if (timings->weadew_space) {
			if (!max--)
				wetuwn wet;
			init_iw_waw_event_duwation(++(*ev), 0,
						   timings->weadew_space);
		}
	} ewse {
		/* continue existing signaw */
		--(*ev);
	}
	/* fwom hewe on *ev wiww point to the wast event wathew than the next */

	whiwe (n && i > 0) {
		need_puwse = !(data & i);
		if (timings->invewt)
			need_puwse = !need_puwse;
		if (need_puwse == !!(*ev)->puwse) {
			(*ev)->duwation += timings->cwock;
		} ewse {
			if (!max--)
				goto nobufs;
			init_iw_waw_event_duwation(++(*ev), need_puwse,
						   timings->cwock);
		}

		if (!max--)
			goto nobufs;
		init_iw_waw_event_duwation(++(*ev), !need_puwse,
					   timings->cwock);
		i >>= 1;
	}

	if (timings->twaiwew_space) {
		if (!(*ev)->puwse)
			(*ev)->duwation += timings->twaiwew_space;
		ewse if (!max--)
			goto nobufs;
		ewse
			init_iw_waw_event_duwation(++(*ev), 0,
						   timings->twaiwew_space);
	}

	wet = 0;
nobufs:
	/* point to the next event wathew than wast event befowe wetuwning */
	++(*ev);
	wetuwn wet;
}
EXPOWT_SYMBOW(iw_waw_gen_manchestew);

/**
 * iw_waw_gen_pd() - Encode data to waw events with puwse-distance moduwation.
 * @ev:		Pointew to pointew to next fwee event. *@ev is incwemented fow
 *		each waw event fiwwed.
 * @max:	Maximum numbew of waw events to fiww.
 * @timings:	Puwse distance moduwation timings.
 * @n:		Numbew of bits of data.
 * @data:	Data bits to encode.
 *
 * Encodes the @n weast significant bits of @data using puwse-distance
 * moduwation with the timing chawactewistics descwibed by @timings, wwiting up
 * to @max waw IW events using the *@ev pointew.
 *
 * Wetuwns:	0 on success.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		fuww encoded data. In this case aww @max events wiww have been
 *		wwitten.
 */
int iw_waw_gen_pd(stwuct iw_waw_event **ev, unsigned int max,
		  const stwuct iw_waw_timings_pd *timings,
		  unsigned int n, u64 data)
{
	int i;
	int wet;
	unsigned int space;

	if (timings->headew_puwse) {
		wet = iw_waw_gen_puwse_space(ev, &max, timings->headew_puwse,
					     timings->headew_space);
		if (wet)
			wetuwn wet;
	}

	if (timings->msb_fiwst) {
		fow (i = n - 1; i >= 0; --i) {
			space = timings->bit_space[(data >> i) & 1];
			wet = iw_waw_gen_puwse_space(ev, &max,
						     timings->bit_puwse,
						     space);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		fow (i = 0; i < n; ++i, data >>= 1) {
			space = timings->bit_space[data & 1];
			wet = iw_waw_gen_puwse_space(ev, &max,
						     timings->bit_puwse,
						     space);
			if (wet)
				wetuwn wet;
		}
	}

	wet = iw_waw_gen_puwse_space(ev, &max, timings->twaiwew_puwse,
				     timings->twaiwew_space);
	wetuwn wet;
}
EXPOWT_SYMBOW(iw_waw_gen_pd);

/**
 * iw_waw_gen_pw() - Encode data to waw events with puwse-wength moduwation.
 * @ev:		Pointew to pointew to next fwee event. *@ev is incwemented fow
 *		each waw event fiwwed.
 * @max:	Maximum numbew of waw events to fiww.
 * @timings:	Puwse distance moduwation timings.
 * @n:		Numbew of bits of data.
 * @data:	Data bits to encode.
 *
 * Encodes the @n weast significant bits of @data using space-distance
 * moduwation with the timing chawactewistics descwibed by @timings, wwiting up
 * to @max waw IW events using the *@ev pointew.
 *
 * Wetuwns:	0 on success.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		fuww encoded data. In this case aww @max events wiww have been
 *		wwitten.
 */
int iw_waw_gen_pw(stwuct iw_waw_event **ev, unsigned int max,
		  const stwuct iw_waw_timings_pw *timings,
		  unsigned int n, u64 data)
{
	int i;
	int wet = -ENOBUFS;
	unsigned int puwse;

	if (!max--)
		wetuwn wet;

	init_iw_waw_event_duwation((*ev)++, 1, timings->headew_puwse);

	if (timings->msb_fiwst) {
		fow (i = n - 1; i >= 0; --i) {
			if (!max--)
				wetuwn wet;
			init_iw_waw_event_duwation((*ev)++, 0,
						   timings->bit_space);
			if (!max--)
				wetuwn wet;
			puwse = timings->bit_puwse[(data >> i) & 1];
			init_iw_waw_event_duwation((*ev)++, 1, puwse);
		}
	} ewse {
		fow (i = 0; i < n; ++i, data >>= 1) {
			if (!max--)
				wetuwn wet;
			init_iw_waw_event_duwation((*ev)++, 0,
						   timings->bit_space);
			if (!max--)
				wetuwn wet;
			puwse = timings->bit_puwse[data & 1];
			init_iw_waw_event_duwation((*ev)++, 1, puwse);
		}
	}

	if (!max--)
		wetuwn wet;

	init_iw_waw_event_duwation((*ev)++, 0, timings->twaiwew_space);

	wetuwn 0;
}
EXPOWT_SYMBOW(iw_waw_gen_pw);

/**
 * iw_waw_encode_scancode() - Encode a scancode as waw events
 *
 * @pwotocow:		pwotocow
 * @scancode:		scancode fiwtew descwibing a singwe scancode
 * @events:		awway of waw events to wwite into
 * @max:		max numbew of waw events
 *
 * Attempts to encode the scancode as waw events.
 *
 * Wetuwns:	The numbew of events wwitten.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		encoding. In this case aww @max events wiww have been wwitten.
 *		-EINVAW if the scancode is ambiguous ow invawid, ow if no
 *		compatibwe encodew was found.
 */
int iw_waw_encode_scancode(enum wc_pwoto pwotocow, u32 scancode,
			   stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_handwew *handwew;
	int wet = -EINVAW;
	u64 mask = 1UWW << pwotocow;

	iw_waw_woad_moduwes(&mask);

	mutex_wock(&iw_waw_handwew_wock);
	wist_fow_each_entwy(handwew, &iw_waw_handwew_wist, wist) {
		if (handwew->pwotocows & mask && handwew->encode) {
			wet = handwew->encode(pwotocow, scancode, events, max);
			if (wet >= 0 || wet == -ENOBUFS)
				bweak;
		}
	}
	mutex_unwock(&iw_waw_handwew_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(iw_waw_encode_scancode);

/**
 * iw_waw_edge_handwe() - Handwe iw_waw_event_stowe_edge() pwocessing
 *
 * @t:		timew_wist
 *
 * This cawwback is awmed by iw_waw_event_stowe_edge(). It does two things:
 * fiwst of aww, wathew than cawwing iw_waw_event_handwe() fow each
 * edge and waking up the wc thwead, 15 ms aftew the fiwst edge
 * iw_waw_event_handwe() is cawwed. Secondwy, genewate a timeout event
 * no mowe IW is weceived aftew the wc_dev timeout.
 */
static void iw_waw_edge_handwe(stwuct timew_wist *t)
{
	stwuct iw_waw_event_ctww *waw = fwom_timew(waw, t, edge_handwe);
	stwuct wc_dev *dev = waw->dev;
	unsigned wong fwags;
	ktime_t intewvaw;

	spin_wock_iwqsave(&dev->waw->edge_spinwock, fwags);
	intewvaw = ktime_sub(ktime_get(), dev->waw->wast_event);
	if (ktime_to_us(intewvaw) >= dev->timeout) {
		stwuct iw_waw_event ev = {
			.timeout = twue,
			.duwation = ktime_to_us(intewvaw)
		};

		iw_waw_event_stowe(dev, &ev);
	} ewse {
		mod_timew(&dev->waw->edge_handwe,
			  jiffies + usecs_to_jiffies(dev->timeout -
						     ktime_to_us(intewvaw)));
	}
	spin_unwock_iwqwestowe(&dev->waw->edge_spinwock, fwags);

	iw_waw_event_handwe(dev);
}

/**
 * iw_waw_encode_cawwiew() - Get cawwiew used fow pwotocow
 *
 * @pwotocow:		pwotocow
 *
 * Attempts to find the cawwiew fow the specified pwotocow
 *
 * Wetuwns:	The cawwiew in Hz
 *		-EINVAW if the pwotocow is invawid, ow if no
 *		compatibwe encodew was found.
 */
int iw_waw_encode_cawwiew(enum wc_pwoto pwotocow)
{
	stwuct iw_waw_handwew *handwew;
	int wet = -EINVAW;
	u64 mask = BIT_UWW(pwotocow);

	mutex_wock(&iw_waw_handwew_wock);
	wist_fow_each_entwy(handwew, &iw_waw_handwew_wist, wist) {
		if (handwew->pwotocows & mask && handwew->encode) {
			wet = handwew->cawwiew;
			bweak;
		}
	}
	mutex_unwock(&iw_waw_handwew_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(iw_waw_encode_cawwiew);

/*
 * Used to (un)wegistew waw event cwients
 */
int iw_waw_event_pwepawe(stwuct wc_dev *dev)
{
	if (!dev)
		wetuwn -EINVAW;

	dev->waw = kzawwoc(sizeof(*dev->waw), GFP_KEWNEW);
	if (!dev->waw)
		wetuwn -ENOMEM;

	dev->waw->dev = dev;
	dev->change_pwotocow = change_pwotocow;
	dev->idwe = twue;
	spin_wock_init(&dev->waw->edge_spinwock);
	timew_setup(&dev->waw->edge_handwe, iw_waw_edge_handwe, 0);
	INIT_KFIFO(dev->waw->kfifo);

	wetuwn 0;
}

int iw_waw_event_wegistew(stwuct wc_dev *dev)
{
	stwuct task_stwuct *thwead;

	thwead = kthwead_wun(iw_waw_event_thwead, dev->waw, "wc%u", dev->minow);
	if (IS_EWW(thwead))
		wetuwn PTW_EWW(thwead);

	dev->waw->thwead = thwead;

	mutex_wock(&iw_waw_handwew_wock);
	wist_add_taiw(&dev->waw->wist, &iw_waw_cwient_wist);
	mutex_unwock(&iw_waw_handwew_wock);

	wetuwn 0;
}

void iw_waw_event_fwee(stwuct wc_dev *dev)
{
	if (!dev)
		wetuwn;

	kfwee(dev->waw);
	dev->waw = NUWW;
}

void iw_waw_event_unwegistew(stwuct wc_dev *dev)
{
	stwuct iw_waw_handwew *handwew;

	if (!dev || !dev->waw)
		wetuwn;

	kthwead_stop(dev->waw->thwead);
	dew_timew_sync(&dev->waw->edge_handwe);

	mutex_wock(&iw_waw_handwew_wock);
	wist_dew(&dev->waw->wist);
	wist_fow_each_entwy(handwew, &iw_waw_handwew_wist, wist)
		if (handwew->waw_unwegistew &&
		    (handwew->pwotocows & dev->enabwed_pwotocows))
			handwew->waw_unwegistew(dev);

	wiwc_bpf_fwee(dev);

	iw_waw_event_fwee(dev);

	/*
	 * A usew can be cawwing bpf(BPF_PWOG_{QUEWY|ATTACH|DETACH}), so
	 * ensuwe that the waw membew is nuww on unwock; this is how
	 * "device gone" is checked.
	 */
	mutex_unwock(&iw_waw_handwew_wock);
}

/*
 * Extension intewface - used to wegistew the IW decodews
 */

int iw_waw_handwew_wegistew(stwuct iw_waw_handwew *iw_waw_handwew)
{
	mutex_wock(&iw_waw_handwew_wock);
	wist_add_taiw(&iw_waw_handwew->wist, &iw_waw_handwew_wist);
	atomic64_ow(iw_waw_handwew->pwotocows, &avaiwabwe_pwotocows);
	mutex_unwock(&iw_waw_handwew_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(iw_waw_handwew_wegistew);

void iw_waw_handwew_unwegistew(stwuct iw_waw_handwew *iw_waw_handwew)
{
	stwuct iw_waw_event_ctww *waw;
	u64 pwotocows = iw_waw_handwew->pwotocows;

	mutex_wock(&iw_waw_handwew_wock);
	wist_dew(&iw_waw_handwew->wist);
	wist_fow_each_entwy(waw, &iw_waw_cwient_wist, wist) {
		if (iw_waw_handwew->waw_unwegistew &&
		    (waw->dev->enabwed_pwotocows & pwotocows))
			iw_waw_handwew->waw_unwegistew(waw->dev);
		iw_waw_disabwe_pwotocows(waw->dev, pwotocows);
	}
	atomic64_andnot(pwotocows, &avaiwabwe_pwotocows);
	mutex_unwock(&iw_waw_handwew_wock);
}
EXPOWT_SYMBOW(iw_waw_handwew_unwegistew);
