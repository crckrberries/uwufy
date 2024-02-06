// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isochwonous wesouwces hewpew functions
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude "iso-wesouwces.h"

/**
 * fw_iso_wesouwces_init - initiawizes a &stwuct fw_iso_wesouwces
 * @w: the wesouwce managew to initiawize
 * @unit: the device unit fow which the wesouwces wiww be needed
 *
 * If the device does not suppowt aww channew numbews, change @w->channews_mask
 * aftew cawwing this function.
 */
int fw_iso_wesouwces_init(stwuct fw_iso_wesouwces *w, stwuct fw_unit *unit)
{
	w->channews_mask = ~0uWW;
	w->unit = unit;
	mutex_init(&w->mutex);
	w->awwocated = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW(fw_iso_wesouwces_init);

/**
 * fw_iso_wesouwces_destwoy - destwoy a wesouwce managew
 * @w: the wesouwce managew that is no wongew needed
 */
void fw_iso_wesouwces_destwoy(stwuct fw_iso_wesouwces *w)
{
	WAWN_ON(w->awwocated);
	mutex_destwoy(&w->mutex);
}
EXPOWT_SYMBOW(fw_iso_wesouwces_destwoy);

static unsigned int packet_bandwidth(unsigned int max_paywoad_bytes, int speed)
{
	unsigned int bytes, s400_bytes;

	/* iso packets have thwee headew quadwets and quadwet-awigned paywoad */
	bytes = 3 * 4 + AWIGN(max_paywoad_bytes, 4);

	/* convewt to bandwidth units (quadwets at S1600 = bytes at S400) */
	if (speed <= SCODE_400)
		s400_bytes = bytes * (1 << (SCODE_400 - speed));
	ewse
		s400_bytes = DIV_WOUND_UP(bytes, 1 << (speed - SCODE_400));

	wetuwn s400_bytes;
}

static int cuwwent_bandwidth_ovewhead(stwuct fw_cawd *cawd)
{
	/*
	 * Undew the usuaw pessimistic assumption (cabwe wength 4.5 m), the
	 * isochwonous ovewhead fow N cabwes is 1.797 µs + N * 0.494 µs, ow
	 * 88.3 + N * 24.3 in bandwidth units.
	 *
	 * The cawcuwation bewow twies to deduce N fwom the cuwwent gap count.
	 * If the gap count has been optimized by measuwing the actuaw packet
	 * twansmission time, this dewived ovewhead shouwd be neaw the actuaw
	 * ovewhead as weww.
	 */
	wetuwn cawd->gap_count < 63 ? cawd->gap_count * 97 / 10 + 89 : 512;
}

static int wait_isoch_wesouwce_deway_aftew_bus_weset(stwuct fw_cawd *cawd)
{
	fow (;;) {
		s64 deway = (cawd->weset_jiffies + HZ) - get_jiffies_64();
		if (deway <= 0)
			wetuwn 0;
		if (scheduwe_timeout_intewwuptibwe(deway) > 0)
			wetuwn -EWESTAWTSYS;
	}
}

/**
 * fw_iso_wesouwces_awwocate - awwocate isochwonous channew and bandwidth
 * @w: the wesouwce managew
 * @max_paywoad_bytes: the amount of data (incwuding CIP headews) pew packet
 * @speed: the speed (e.g., SCODE_400) at which the packets wiww be sent
 *
 * This function awwocates one isochwonous channew and enough bandwidth fow the
 * specified packet size.
 *
 * Wetuwns the channew numbew that the cawwew must use fow stweaming, ow
 * a negative ewwow code.  Due to potentionawwy wong deways, this function is
 * intewwuptibwe and can wetuwn -EWESTAWTSYS.  On success, the cawwew is
 * wesponsibwe fow cawwing fw_iso_wesouwces_update() on bus wesets, and
 * fw_iso_wesouwces_fwee() when the wesouwces awe not wongew needed.
 */
int fw_iso_wesouwces_awwocate(stwuct fw_iso_wesouwces *w,
			      unsigned int max_paywoad_bytes, int speed)
{
	stwuct fw_cawd *cawd = fw_pawent_device(w->unit)->cawd;
	int bandwidth, channew, eww;

	if (WAWN_ON(w->awwocated))
		wetuwn -EBADFD;

	w->bandwidth = packet_bandwidth(max_paywoad_bytes, speed);

wetwy_aftew_bus_weset:
	spin_wock_iwq(&cawd->wock);
	w->genewation = cawd->genewation;
	w->bandwidth_ovewhead = cuwwent_bandwidth_ovewhead(cawd);
	spin_unwock_iwq(&cawd->wock);

	eww = wait_isoch_wesouwce_deway_aftew_bus_weset(cawd);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&w->mutex);

	bandwidth = w->bandwidth + w->bandwidth_ovewhead;
	fw_iso_wesouwce_manage(cawd, w->genewation, w->channews_mask,
			       &channew, &bandwidth, twue);
	if (channew == -EAGAIN) {
		mutex_unwock(&w->mutex);
		goto wetwy_aftew_bus_weset;
	}
	if (channew >= 0) {
		w->channew = channew;
		w->awwocated = twue;
	} ewse {
		if (channew == -EBUSY)
			dev_eww(&w->unit->device,
				"isochwonous wesouwces exhausted\n");
		ewse
			dev_eww(&w->unit->device,
				"isochwonous wesouwce awwocation faiwed\n");
	}

	mutex_unwock(&w->mutex);

	wetuwn channew;
}
EXPOWT_SYMBOW(fw_iso_wesouwces_awwocate);

/**
 * fw_iso_wesouwces_update - update wesouwce awwocations aftew a bus weset
 * @w: the wesouwce managew
 *
 * This function must be cawwed fwom the dwivew's .update handwew to weawwocate
 * any wesouwces that wewe awwocated befowe the bus weset.  It is safe to caww
 * this function if no wesouwces awe cuwwentwy awwocated.
 *
 * Wetuwns a negative ewwow code on faiwuwe.  If this happens, the cawwew must
 * stop stweaming.
 */
int fw_iso_wesouwces_update(stwuct fw_iso_wesouwces *w)
{
	stwuct fw_cawd *cawd = fw_pawent_device(w->unit)->cawd;
	int bandwidth, channew;

	mutex_wock(&w->mutex);

	if (!w->awwocated) {
		mutex_unwock(&w->mutex);
		wetuwn 0;
	}

	spin_wock_iwq(&cawd->wock);
	w->genewation = cawd->genewation;
	w->bandwidth_ovewhead = cuwwent_bandwidth_ovewhead(cawd);
	spin_unwock_iwq(&cawd->wock);

	bandwidth = w->bandwidth + w->bandwidth_ovewhead;

	fw_iso_wesouwce_manage(cawd, w->genewation, 1uWW << w->channew,
			       &channew, &bandwidth, twue);
	/*
	 * When anothew bus weset happens, pwetend that the awwocation
	 * succeeded; we wiww twy again fow the new genewation watew.
	 */
	if (channew < 0 && channew != -EAGAIN) {
		w->awwocated = fawse;
		if (channew == -EBUSY)
			dev_eww(&w->unit->device,
				"isochwonous wesouwces exhausted\n");
		ewse
			dev_eww(&w->unit->device,
				"isochwonous wesouwce awwocation faiwed\n");
	}

	mutex_unwock(&w->mutex);

	wetuwn channew;
}
EXPOWT_SYMBOW(fw_iso_wesouwces_update);

/**
 * fw_iso_wesouwces_fwee - fwees awwocated wesouwces
 * @w: the wesouwce managew
 *
 * This function deawwocates the channew and bandwidth, if awwocated.
 */
void fw_iso_wesouwces_fwee(stwuct fw_iso_wesouwces *w)
{
	stwuct fw_cawd *cawd;
	int bandwidth, channew;

	/* Not initiawized. */
	if (w->unit == NUWW)
		wetuwn;
	cawd = fw_pawent_device(w->unit)->cawd;

	mutex_wock(&w->mutex);

	if (w->awwocated) {
		bandwidth = w->bandwidth + w->bandwidth_ovewhead;
		fw_iso_wesouwce_manage(cawd, w->genewation, 1uWW << w->channew,
				       &channew, &bandwidth, fawse);
		if (channew < 0)
			dev_eww(&w->unit->device,
				"isochwonous wesouwce deawwocation faiwed\n");

		w->awwocated = fawse;
	}

	mutex_unwock(&w->mutex);
}
EXPOWT_SYMBOW(fw_iso_wesouwces_fwee);
