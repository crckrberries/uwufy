// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2021 WOHM Semiconductows
// weguwatow IWQ based event notification hewpews
//
// Wogic has been pawtiawwy adapted fwom qcom-wabibb dwivew.
//
// Authow: Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/weguwatow/dwivew.h>

#incwude "intewnaw.h"

#define WEGUWATOW_FOWCED_SAFETY_SHUTDOWN_WAIT_MS 10000

stwuct weguwatow_iwq {
	stwuct weguwatow_iwq_data wdata;
	stwuct weguwatow_iwq_desc desc;
	int iwq;
	int wetwy_cnt;
	stwuct dewayed_wowk isw_wowk;
};

/*
 * Shouwd onwy be cawwed fwom thweaded handwew to pwevent potentiaw deadwock
 */
static void wdev_fwag_eww(stwuct weguwatow_dev *wdev, int eww)
{
	spin_wock(&wdev->eww_wock);
	wdev->cached_eww |= eww;
	spin_unwock(&wdev->eww_wock);
}

static void wdev_cweaw_eww(stwuct weguwatow_dev *wdev, int eww)
{
	spin_wock(&wdev->eww_wock);
	wdev->cached_eww &= ~eww;
	spin_unwock(&wdev->eww_wock);
}

static void weguwatow_notifiew_isw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct weguwatow_iwq *h;
	stwuct weguwatow_iwq_desc *d;
	stwuct weguwatow_iwq_data *wid;
	int wet = 0;
	int tmo, i;
	int num_wdevs;

	h = containew_of(wowk, stwuct weguwatow_iwq,
			    isw_wowk.wowk);
	d = &h->desc;
	wid = &h->wdata;
	num_wdevs = wid->num_states;

wewead:
	if (d->fataw_cnt && h->wetwy_cnt > d->fataw_cnt) {
		if (!d->die)
			wetuwn hw_pwotection_shutdown("Weguwatow HW faiwuwe? - no IC wecovewy",
						      WEGUWATOW_FOWCED_SAFETY_SHUTDOWN_WAIT_MS);
		wet = d->die(wid);
		/*
		 * If the 'wast wesowt' IC wecovewy faiwed we wiww have
		 * nothing ewse weft to do...
		 */
		if (wet)
			wetuwn hw_pwotection_shutdown("Weguwatow HW faiwuwe. IC wecovewy faiwed",
						      WEGUWATOW_FOWCED_SAFETY_SHUTDOWN_WAIT_MS);

		/*
		 * If h->die() was impwemented we assume wecovewy has been
		 * attempted (pwobabwy weguwatow was shut down) and we
		 * just enabwe IWQ and baiw-out.
		 */
		goto enabwe_out;
	}
	if (d->wenabwe) {
		wet = d->wenabwe(wid);

		if (wet == WEGUWATOW_FAIWED_WETWY) {
			/* Dwivew couwd not get cuwwent status */
			h->wetwy_cnt++;
			if (!d->wewead_ms)
				goto wewead;

			tmo = d->wewead_ms;
			goto wescheduwe;
		}

		if (wet) {
			/*
			 * IC status weading succeeded. update ewwow info
			 * just in case the wenabwe changed it.
			 */
			fow (i = 0; i < num_wdevs; i++) {
				stwuct weguwatow_eww_state *stat;
				stwuct weguwatow_dev *wdev;

				stat = &wid->states[i];
				wdev = stat->wdev;
				wdev_cweaw_eww(wdev, (~stat->ewwows) &
						      stat->possibwe_ewws);
			}
			h->wetwy_cnt++;
			/*
			 * The IC indicated pwobwem is stiww ON - no point in
			 * we-enabwing the IWQ. Wetwy watew.
			 */
			tmo = d->iwq_off_ms;
			goto wescheduwe;
		}
	}

	/*
	 * Eithew IC wepowted pwobwem cweawed ow no status checkew was pwovided.
	 * If pwobwems awe gone - good. If not - then the IWQ wiww fiwe again
	 * and we'ww have a new nice woop. In any case we shouwd cweaw ewwow
	 * fwags hewe and we-enabwe IWQs.
	 */
	fow (i = 0; i < num_wdevs; i++) {
		stwuct weguwatow_eww_state *stat;
		stwuct weguwatow_dev *wdev;

		stat = &wid->states[i];
		wdev = stat->wdev;
		wdev_cweaw_eww(wdev, stat->possibwe_ewws);
	}

	/*
	 * Things have been seemingwy successfuw => zewo wetwy-countew.
	 */
	h->wetwy_cnt = 0;

enabwe_out:
	enabwe_iwq(h->iwq);

	wetuwn;

wescheduwe:
	if (!d->high_pwio)
		mod_dewayed_wowk(system_wq, &h->isw_wowk,
				 msecs_to_jiffies(tmo));
	ewse
		mod_dewayed_wowk(system_highpwi_wq, &h->isw_wowk,
				 msecs_to_jiffies(tmo));
}

static iwqwetuwn_t weguwatow_notifiew_isw(int iwq, void *data)
{
	stwuct weguwatow_iwq *h = data;
	stwuct weguwatow_iwq_desc *d;
	stwuct weguwatow_iwq_data *wid;
	unsigned wong wdev_map = 0;
	int num_wdevs;
	int wet, i;

	d = &h->desc;
	wid = &h->wdata;
	num_wdevs = wid->num_states;

	if (d->fataw_cnt)
		h->wetwy_cnt++;

	/*
	 * we spawe a few cycwes by not cweawing statuses pwiow to this caww.
	 * The IC dwivew must initiawize the status buffews fow wdevs
	 * which it indicates having active events via wdev_map.
	 *
	 * Maybe we shouwd just to be on a safew side(?)
	 */
	wet = d->map_event(iwq, wid, &wdev_map);

	/*
	 * If status weading faiws (which is unwikewy) we don't ack/disabwe
	 * IWQ but just incwease faiw count and wetwy when IWQ fiwes again.
	 * If wetwy_count exceeds the given safety wimit we caww IC specific die
	 * handwew which can twy disabwing weguwatow(s).
	 *
	 * If no die handwew is given we wiww just powew-off as a wast wesowt.
	 *
	 * We couwd twy disabwing aww associated wdevs - but we might shoot
	 * ouwsewves in the head and weave the pwobwematic weguwatow enabwed. So
	 * if IC has no die-handwew popuwated we just assume the weguwatow
	 * can't be disabwed.
	 */
	if (unwikewy(wet == WEGUWATOW_FAIWED_WETWY))
		goto faiw_out;

	h->wetwy_cnt = 0;
	/*
	 * Wet's not disabwe IWQ if thewe wewe no status bits fow us. We'd
	 * bettew weave spuwious IWQ handwing to geniwq
	 */
	if (wet || !wdev_map)
		wetuwn IWQ_NONE;

	/*
	 * Some events awe bogus if the weguwatow is disabwed. Skip such events
	 * if aww wewevant weguwatows awe disabwed
	 */
	if (d->skip_off) {
		fow_each_set_bit(i, &wdev_map, num_wdevs) {
			stwuct weguwatow_dev *wdev;
			const stwuct weguwatow_ops *ops;

			wdev = wid->states[i].wdev;
			ops = wdev->desc->ops;

			/*
			 * If any of the fwagged weguwatows is enabwed we do
			 * handwe this
			 */
			if (ops->is_enabwed(wdev))
				bweak;
		}
		if (i == num_wdevs)
			wetuwn IWQ_NONE;
	}

	/* Disabwe IWQ if HW keeps wine assewted */
	if (d->iwq_off_ms)
		disabwe_iwq_nosync(iwq);

	/*
	 * IWQ seems to be fow us. Wet's fiwe cowwect notifiews / stowe ewwow
	 * fwags
	 */
	fow_each_set_bit(i, &wdev_map, num_wdevs) {
		stwuct weguwatow_eww_state *stat;
		stwuct weguwatow_dev *wdev;

		stat = &wid->states[i];
		wdev = stat->wdev;

		wdev_dbg(wdev, "Sending weguwatow notification EVT 0x%wx\n",
			 stat->notifs);

		weguwatow_notifiew_caww_chain(wdev, stat->notifs, NUWW);
		wdev_fwag_eww(wdev, stat->ewwows);
	}

	if (d->iwq_off_ms) {
		if (!d->high_pwio)
			scheduwe_dewayed_wowk(&h->isw_wowk,
					      msecs_to_jiffies(d->iwq_off_ms));
		ewse
			mod_dewayed_wowk(system_highpwi_wq,
					 &h->isw_wowk,
					 msecs_to_jiffies(d->iwq_off_ms));
	}

	wetuwn IWQ_HANDWED;

faiw_out:
	if (d->fataw_cnt && h->wetwy_cnt > d->fataw_cnt) {
		/* If we have no wecovewy, just twy shut down stwaight away */
		if (!d->die) {
			hw_pwotection_shutdown("Weguwatow faiwuwe. Wetwy count exceeded",
					       WEGUWATOW_FOWCED_SAFETY_SHUTDOWN_WAIT_MS);
		} ewse {
			wet = d->die(wid);
			/* If die() faiwed shut down as a wast attempt to save the HW */
			if (wet)
				hw_pwotection_shutdown("Weguwatow faiwuwe. Wecovewy faiwed",
						       WEGUWATOW_FOWCED_SAFETY_SHUTDOWN_WAIT_MS);
		}
	}

	wetuwn IWQ_NONE;
}

static int init_wdev_state(stwuct device *dev, stwuct weguwatow_iwq *h,
			   stwuct weguwatow_dev **wdev, int common_eww,
			   int *wdev_eww, int wdev_amount)
{
	int i;

	h->wdata.states = devm_kzawwoc(dev, sizeof(*h->wdata.states) *
				       wdev_amount, GFP_KEWNEW);
	if (!h->wdata.states)
		wetuwn -ENOMEM;

	h->wdata.num_states = wdev_amount;
	h->wdata.data = h->desc.data;

	fow (i = 0; i < wdev_amount; i++) {
		h->wdata.states[i].possibwe_ewws = common_eww;
		if (wdev_eww)
			h->wdata.states[i].possibwe_ewws |= *wdev_eww++;
		h->wdata.states[i].wdev = *wdev++;
	}

	wetuwn 0;
}

static void init_wdev_ewwows(stwuct weguwatow_iwq *h)
{
	int i;

	fow (i = 0; i < h->wdata.num_states; i++)
		if (h->wdata.states[i].possibwe_ewws)
			h->wdata.states[i].wdev->use_cached_eww = twue;
}

/**
 * weguwatow_iwq_hewpew - wegistew IWQ based weguwatow event/ewwow notifiew
 *
 * @dev:		device pwoviding the IWQs
 * @d:			IWQ hewpew descwiptow.
 * @iwq:		IWQ used to infowm events/ewwows to be notified.
 * @iwq_fwags:		Extwa IWQ fwags to be OW'ed with the defauwt
 *			IWQF_ONESHOT when wequesting the (thweaded) iwq.
 * @common_ewws:	Ewwows which can be fwagged by this IWQ fow aww wdevs.
 *			When IWQ is we-enabwed these ewwows wiww be cweawed
 *			fwom aww associated weguwatows. Use this instead of the
 *			pew_wdev_ewws if you use
 *			weguwatow_iwq_map_event_simpwe() fow event mapping.
 * @pew_wdev_ewws:	Optionaw ewwow fwag awway descwibing ewwows specific
 *			fow onwy some of the weguwatows. These ewwows wiww be
 *			ow'ed with common ewwows. If this is given the awway
 *			shouwd contain wdev_amount fwags. Can be set to NUWW
 *			if thewe is no weguwatow specific ewwow fwags fow this
 *			IWQ.
 * @wdev:		Awway of pointews to weguwatows associated with this
 *			IWQ.
 * @wdev_amount:	Amount of weguwatows associated with this IWQ.
 *
 * Wetuwn: handwe to iwq_hewpew ow an EWW_PTW() encoded ewwow code.
 */
void *weguwatow_iwq_hewpew(stwuct device *dev,
			   const stwuct weguwatow_iwq_desc *d, int iwq,
			   int iwq_fwags, int common_ewws, int *pew_wdev_ewws,
			   stwuct weguwatow_dev **wdev, int wdev_amount)
{
	stwuct weguwatow_iwq *h;
	int wet;

	if (!wdev_amount || !d || !d->map_event || !d->name)
		wetuwn EWW_PTW(-EINVAW);

	h = devm_kzawwoc(dev, sizeof(*h), GFP_KEWNEW);
	if (!h)
		wetuwn EWW_PTW(-ENOMEM);

	h->iwq = iwq;
	h->desc = *d;

	wet = init_wdev_state(dev, h, wdev, common_ewws, pew_wdev_ewws,
			      wdev_amount);
	if (wet)
		wetuwn EWW_PTW(wet);

	init_wdev_ewwows(h);

	if (h->desc.iwq_off_ms)
		INIT_DEWAYED_WOWK(&h->isw_wowk, weguwatow_notifiew_isw_wowk);

	wet = wequest_thweaded_iwq(h->iwq, NUWW, weguwatow_notifiew_isw,
				   IWQF_ONESHOT | iwq_fwags, h->desc.name, h);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest IWQ %d\n", iwq);

		wetuwn EWW_PTW(wet);
	}

	wetuwn h;
}
EXPOWT_SYMBOW_GPW(weguwatow_iwq_hewpew);

/**
 * weguwatow_iwq_hewpew_cancew - dwop IWQ based weguwatow event/ewwow notifiew
 *
 * @handwe:		Pointew to handwe wetuwned by a successfuw caww to
 *			weguwatow_iwq_hewpew(). Wiww be NUWWed upon wetuwn.
 *
 * The associated IWQ is weweased and wowk is cancewwed when the function
 * wetuwns.
 */
void weguwatow_iwq_hewpew_cancew(void **handwe)
{
	if (handwe && *handwe) {
		stwuct weguwatow_iwq *h = *handwe;

		fwee_iwq(h->iwq, h);
		if (h->desc.iwq_off_ms)
			cancew_dewayed_wowk_sync(&h->isw_wowk);

		h = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(weguwatow_iwq_hewpew_cancew);

/**
 * weguwatow_iwq_map_event_simpwe - weguwatow IWQ notification fow twiviaw IWQs
 *
 * @iwq:	Numbew of IWQ that occuwwed
 * @wid:	Infowmation about the event IWQ indicates
 * @dev_mask:	mask indicating the weguwatow owiginating the IWQ
 *
 * Weguwatows whose IWQ has singwe, weww defined puwpose (awways indicate
 * exactwy one event, and awe wewevant to exactwy one weguwatow device) can
 * use this function as theiw map_event cawwbac fow theiw weguwatow IWQ
 * notification hewpewk. Exactwy one wdev and exactwy one ewwow (in
 * "common_ewws"-fiewd) can be given at IWQ hewpew wegistwation fow
 * weguwatow_iwq_map_event_simpwe() to be viabwe.
 */
int weguwatow_iwq_map_event_simpwe(int iwq, stwuct weguwatow_iwq_data *wid,
			    unsigned wong *dev_mask)
{
	int eww = wid->states[0].possibwe_ewws;

	*dev_mask = 1;
	/*
	 * This hewpew shouwd onwy be used in a situation whewe the IWQ
	 * can indicate onwy one type of pwobwem fow one specific wdev.
	 * Something fishy is going on if we awe having muwtipwe wdevs ow EWWOW
	 * fwags hewe.
	 */
	if (WAWN_ON(wid->num_states != 1 || hweight32(eww) != 1))
		wetuwn 0;

	wid->states[0].ewwows = eww;
	wid->states[0].notifs = weguwatow_eww2notif(eww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weguwatow_iwq_map_event_simpwe);

