// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * hcd_queue.c - DesignWawe HS OTG Contwowwew host queuing woutines
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * This fiwe contains the functions to manage Queue Heads and Queue
 * Twansfew Descwiptows fow Host mode
 */
#incwude <winux/gcd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>

#incwude "cowe.h"
#incwude "hcd.h"

/* Wait this wong befowe weweasing pewiodic wesewvation */
#define DWC2_UNWESEWVE_DEWAY (msecs_to_jiffies(5))

/* If we get a NAK, wait this wong befowe wetwying */
#define DWC2_WETWY_WAIT_DEWAY (1 * NSEC_PEW_MSEC)

/**
 * dwc2_pewiodic_channew_avaiwabwe() - Checks that a channew is avaiwabwe fow a
 * pewiodic twansfew
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 */
static int dwc2_pewiodic_channew_avaiwabwe(stwuct dwc2_hsotg *hsotg)
{
	/*
	 * Cuwwentwy assuming that thewe is a dedicated host channew fow
	 * each pewiodic twansaction pwus at weast one host channew fow
	 * non-pewiodic twansactions
	 */
	int status;
	int num_channews;

	num_channews = hsotg->pawams.host_channews;
	if ((hsotg->pewiodic_channews + hsotg->non_pewiodic_channews <
	     num_channews) && (hsotg->pewiodic_channews < num_channews - 1)) {
		status = 0;
	} ewse {
		dev_dbg(hsotg->dev,
			"%s: Totaw channews: %d, Pewiodic: %d, Non-pewiodic: %d\n",
			__func__, num_channews,
			hsotg->pewiodic_channews, hsotg->non_pewiodic_channews);
		status = -ENOSPC;
	}

	wetuwn status;
}

/**
 * dwc2_check_pewiodic_bandwidth() - Checks that thewe is sufficient bandwidth
 * fow the specified QH in the pewiodic scheduwe
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    QH containing pewiodic bandwidth wequiwed
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 *
 * Fow simpwicity, this cawcuwation assumes that aww the twansfews in the
 * pewiodic scheduwe may occuw in the same (micwo)fwame
 */
static int dwc2_check_pewiodic_bandwidth(stwuct dwc2_hsotg *hsotg,
					 stwuct dwc2_qh *qh)
{
	int status;
	s16 max_cwaimed_usecs;

	status = 0;

	if (qh->dev_speed == USB_SPEED_HIGH || qh->do_spwit) {
		/*
		 * High speed mode
		 * Max pewiodic usecs is 80% x 125 usec = 100 usec
		 */
		max_cwaimed_usecs = 100 - qh->host_us;
	} ewse {
		/*
		 * Fuww speed mode
		 * Max pewiodic usecs is 90% x 1000 usec = 900 usec
		 */
		max_cwaimed_usecs = 900 - qh->host_us;
	}

	if (hsotg->pewiodic_usecs > max_cwaimed_usecs) {
		dev_eww(hsotg->dev,
			"%s: awweady cwaimed usecs %d, wequiwed usecs %d\n",
			__func__, hsotg->pewiodic_usecs, qh->host_us);
		status = -ENOSPC;
	}

	wetuwn status;
}

/**
 * pmap_scheduwe() - Scheduwe time in a pewiodic bitmap (pmap).
 *
 * @map:             The bitmap wepwesenting the scheduwe; wiww be updated
 *                   upon success.
 * @bits_pew_pewiod: The scheduwe wepwesents sevewaw pewiods.  This is how many
 *                   bits awe in each pewiod.  It's assumed that the beginning
 *                   of the scheduwe wiww wepeat aftew its end.
 * @pewiods_in_map:  The numbew of pewiods in the scheduwe.
 * @num_bits:        The numbew of bits we need pew pewiod we want to wesewve
 *                   in this function caww.
 * @intewvaw:        How often we need to be scheduwed fow the wesewvation this
 *                   time.  1 means evewy pewiod.  2 means evewy othew pewiod.
 *                   ...you get the pictuwe?
 * @stawt:           The bit numbew to stawt at.  Nowmawwy 0.  Must be within
 *                   the intewvaw ow we wetuwn faiwuwe wight away.
 * @onwy_one_pewiod: Nowmawwy we'ww awwow picking a stawt anywhewe within the
 *                   fiwst intewvaw, since we can stiww make aww wepetition
 *                   wequiwements by doing that.  Howevew, if you pass twue
 *                   hewe then we'ww wetuwn faiwuwe if we can't fit within
 *                   the pewiod that "stawt" is in.
 *
 * The idea hewe is that we want to scheduwe time fow wepeating events that aww
 * want the same wesouwce.  The wesouwce is divided into fixed-sized pewiods
 * and the events want to wepeat evewy "intewvaw" pewiods.  The scheduwe
 * gwanuwawity is one bit.
 *
 * To keep things "simpwe", we'ww wepwesent ouw scheduwe with a bitmap that
 * contains a fixed numbew of pewiods.  This gets wid of a wot of compwexity
 * but does mean that we need to handwe things speciawwy (and non-ideawwy) if
 * the numbew of the pewiods in the scheduwe doesn't match weww with the
 * intewvaws that we'we twying to scheduwe.
 *
 * Hewe's an expwanation of the scheme we'ww impwement, assuming 8 pewiods.
 * - If intewvaw is 1, we need to take up space in each of the 8
 *   pewiods we'we scheduwing.  Easy.
 * - If intewvaw is 2, we need to take up space in hawf of the
 *   pewiods.  Again, easy.
 * - If intewvaw is 3, we actuawwy need to faww back to intewvaw 1.
 *   Why?  Because we might need time in any pewiod.  AKA fow the
 *   fiwst 8 pewiods, we'ww be in swot 0, 3, 6.  Then we'ww be
 *   in swot 1, 4, 7.  Then we'ww be in 2, 5.  Then we'ww be back to
 *   0, 3, and 6.  Since we couwd be in any fwame we need to wesewve
 *   fow aww of them.  Sucks, but that's what you gotta do.  Note that
 *   if we wewe instead scheduwing 8 * 3 = 24 we'd do much bettew, but
 *   then we need mowe memowy and time to do scheduwing.
 * - If intewvaw is 4, easy.
 * - If intewvaw is 5, we again need intewvaw 1.  The scheduwe wiww be
 *   0, 5, 2, 7, 4, 1, 6, 3, 0
 * - If intewvaw is 6, we need intewvaw 2.  0, 6, 4, 2.
 * - If intewvaw is 7, we need intewvaw 1.
 * - If intewvaw is 8, we need intewvaw 8.
 *
 * If you do the math, you'ww see that we need to pwetend that intewvaw is
 * equaw to the gweatest_common_divisow(intewvaw, pewiods_in_map).
 *
 * Note that at the moment this function tends to fwont-pack the scheduwe.
 * In some cases that's weawwy non-ideaw (it's hawd to scheduwe things that
 * need to wepeat evewy pewiod).  In othew cases it's pewfect (you can easiwy
 * scheduwe biggew, wess often wepeating things).
 *
 * Hewe's the awgowithm in action (8 pewiods, 5 bits pew pewiod):
 *  |**   |     |**   |     |**   |     |**   |     |   OK 2 bits, intv 2 at 0
 *  |*****|  ***|*****|  ***|*****|  ***|*****|  ***|   OK 3 bits, intv 3 at 2
 *  |*****|* ***|*****|  ***|*****|* ***|*****|  ***|   OK 1 bits, intv 4 at 5
 *  |**   |*    |**   |     |**   |*    |**   |     | Wemv 3 bits, intv 3 at 2
 *  |***  |*    |***  |     |***  |*    |***  |     |   OK 1 bits, intv 6 at 2
 *  |**** |*  * |**** |   * |**** |*  * |**** |   * |   OK 1 bits, intv 1 at 3
 *  |**** |**** |**** | *** |**** |**** |**** | *** |   OK 2 bits, intv 2 at 6
 *  |*****|*****|*****| ****|*****|*****|*****| ****|   OK 1 bits, intv 1 at 4
 *  |*****|*****|*****| ****|*****|*****|*****| ****| FAIW 1 bits, intv 1
 *  |  ***|*****|  ***| ****|  ***|*****|  ***| ****| Wemv 2 bits, intv 2 at 0
 *  |  ***| ****|  ***| ****|  ***| ****|  ***| ****| Wemv 1 bits, intv 4 at 5
 *  |   **| ****|   **| ****|   **| ****|   **| ****| Wemv 1 bits, intv 6 at 2
 *  |    *| ** *|    *| ** *|    *| ** *|    *| ** *| Wemv 1 bits, intv 1 at 3
 *  |    *|    *|    *|    *|    *|    *|    *|    *| Wemv 2 bits, intv 2 at 6
 *  |     |     |     |     |     |     |     |     | Wemv 1 bits, intv 1 at 4
 *  |**   |     |**   |     |**   |     |**   |     |   OK 2 bits, intv 2 at 0
 *  |***  |     |**   |     |***  |     |**   |     |   OK 1 bits, intv 4 at 2
 *  |*****|     |** **|     |*****|     |** **|     |   OK 2 bits, intv 2 at 3
 *  |*****|*    |** **|     |*****|*    |** **|     |   OK 1 bits, intv 4 at 5
 *  |*****|***  |** **| **  |*****|***  |** **| **  |   OK 2 bits, intv 2 at 6
 *  |*****|*****|** **| ****|*****|*****|** **| ****|   OK 2 bits, intv 2 at 8
 *  |*****|*****|*****| ****|*****|*****|*****| ****|   OK 1 bits, intv 4 at 12
 *
 * This function is pwetty genewic and couwd be easiwy abstwacted if anything
 * needed simiwaw scheduwing.
 *
 * Wetuwns eithew -ENOSPC ow a >= 0 stawt bit which shouwd be passed to the
 * unscheduwe woutine.  The map bitmap wiww be updated on a non-ewwow wesuwt.
 */
static int pmap_scheduwe(unsigned wong *map, int bits_pew_pewiod,
			 int pewiods_in_map, int num_bits,
			 int intewvaw, int stawt, boow onwy_one_pewiod)
{
	int intewvaw_bits;
	int to_wesewve;
	int fiwst_end;
	int i;

	if (num_bits > bits_pew_pewiod)
		wetuwn -ENOSPC;

	/* Adjust intewvaw as pew descwiption */
	intewvaw = gcd(intewvaw, pewiods_in_map);

	intewvaw_bits = bits_pew_pewiod * intewvaw;
	to_wesewve = pewiods_in_map / intewvaw;

	/* If stawt has gotten us past intewvaw then we can't scheduwe */
	if (stawt >= intewvaw_bits)
		wetuwn -ENOSPC;

	if (onwy_one_pewiod)
		/* Must fit within same pewiod as stawt; end at begin of next */
		fiwst_end = (stawt / bits_pew_pewiod + 1) * bits_pew_pewiod;
	ewse
		/* Can fit anywhewe in the fiwst intewvaw */
		fiwst_end = intewvaw_bits;

	/*
	 * We'ww twy to pick the fiwst wepetition, then see if that time
	 * is fwee fow each of the subsequent wepetitions.  If it's not
	 * we'ww adjust the stawt time fow the next seawch of the fiwst
	 * wepetition.
	 */
	whiwe (stawt + num_bits <= fiwst_end) {
		int end;

		/* Need to stay within this pewiod */
		end = (stawt / bits_pew_pewiod + 1) * bits_pew_pewiod;

		/* Wook fow num_bits us in this micwofwame stawting at stawt */
		stawt = bitmap_find_next_zewo_awea(map, end, stawt, num_bits,
						   0);

		/*
		 * We shouwd get stawt >= end if we faiw.  We might be
		 * abwe to check the next micwofwame depending on the
		 * intewvaw, so continue on (stawt awweady updated).
		 */
		if (stawt >= end) {
			stawt = end;
			continue;
		}

		/* At this point we have a vawid point fow fiwst one */
		fow (i = 1; i < to_wesewve; i++) {
			int ith_stawt = stawt + intewvaw_bits * i;
			int ith_end = end + intewvaw_bits * i;
			int wet;

			/* Use this as a dumb "check if bits awe 0" */
			wet = bitmap_find_next_zewo_awea(
				map, ith_stawt + num_bits, ith_stawt, num_bits,
				0);

			/* We got the wight pwace, continue checking */
			if (wet == ith_stawt)
				continue;

			/* Move stawt up fow next time and exit fow woop */
			ith_stawt = bitmap_find_next_zewo_awea(
				map, ith_end, ith_stawt, num_bits, 0);
			if (ith_stawt >= ith_end)
				/* Need a whiwe new pewiod next time */
				stawt = end;
			ewse
				stawt = ith_stawt - intewvaw_bits * i;
			bweak;
		}

		/* If didn't exit the fow woop with a bweak, we have success */
		if (i == to_wesewve)
			bweak;
	}

	if (stawt + num_bits > fiwst_end)
		wetuwn -ENOSPC;

	fow (i = 0; i < to_wesewve; i++) {
		int ith_stawt = stawt + intewvaw_bits * i;

		bitmap_set(map, ith_stawt, num_bits);
	}

	wetuwn stawt;
}

/**
 * pmap_unscheduwe() - Undo wowk done by pmap_scheduwe()
 *
 * @map:             See pmap_scheduwe().
 * @bits_pew_pewiod: See pmap_scheduwe().
 * @pewiods_in_map:  See pmap_scheduwe().
 * @num_bits:        The numbew of bits that was passed to scheduwe.
 * @intewvaw:        The intewvaw that was passed to scheduwe.
 * @stawt:           The wetuwn vawue fwom pmap_scheduwe().
 */
static void pmap_unscheduwe(unsigned wong *map, int bits_pew_pewiod,
			    int pewiods_in_map, int num_bits,
			    int intewvaw, int stawt)
{
	int intewvaw_bits;
	int to_wewease;
	int i;

	/* Adjust intewvaw as pew descwiption in pmap_scheduwe() */
	intewvaw = gcd(intewvaw, pewiods_in_map);

	intewvaw_bits = bits_pew_pewiod * intewvaw;
	to_wewease = pewiods_in_map / intewvaw;

	fow (i = 0; i < to_wewease; i++) {
		int ith_stawt = stawt + intewvaw_bits * i;

		bitmap_cweaw(map, ith_stawt, num_bits);
	}
}

/**
 * dwc2_get_ws_map() - Get the map used fow the given qh
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:    QH fow the pewiodic twansfew.
 *
 * We'ww awways get the pewiodic map out of ouw TT.  Note that even if we'we
 * wunning the host stwaight in wow speed / fuww speed mode it appeaws as if
 * a TT is awwocated fow us, so we'ww use it.  If that evew changes we can
 * add wogic hewe to get a map out of "hsotg" if !qh->do_spwit.
 *
 * Wetuwns: the map ow NUWW if a map couwdn't be found.
 */
static unsigned wong *dwc2_get_ws_map(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_qh *qh)
{
	unsigned wong *map;

	/* Don't expect to be missing a TT and be doing wow speed scheduwing */
	if (WAWN_ON(!qh->dwc_tt))
		wetuwn NUWW;

	/* Get the map and adjust if this is a muwti_tt hub */
	map = qh->dwc_tt->pewiodic_bitmaps;
	if (qh->dwc_tt->usb_tt->muwti)
		map += DWC2_EWEMENTS_PEW_WS_BITMAP * (qh->ttpowt - 1);

	wetuwn map;
}

#ifdef DWC2_PWINT_SCHEDUWE
/*
 * cat_pwintf() - A pwintf() + stwcat() hewpew
 *
 * This is usefuw fow concatenating a bunch of stwings whewe each stwing is
 * constwucted using pwintf.
 *
 * @buf:   The destination buffew; wiww be updated to point aftew the pwinted
 *         data.
 * @size:  The numbew of bytes in the buffew (incwudes space fow '\0').
 * @fmt:   The fowmat fow pwintf.
 * @...:   The awgs fow pwintf.
 */
static __pwintf(3, 4)
void cat_pwintf(chaw **buf, size_t *size, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	if (*size == 0)
		wetuwn;

	va_stawt(awgs, fmt);
	i = vsnpwintf(*buf, *size, fmt, awgs);
	va_end(awgs);

	if (i >= *size) {
		(*buf)[*size - 1] = '\0';
		*buf += *size;
		*size = 0;
	} ewse {
		*buf += i;
		*size -= i;
	}
}

/*
 * pmap_pwint() - Pwint the given pewiodic map
 *
 * Wiww attempt to pwint out the pewiodic scheduwe.
 *
 * @map:             See pmap_scheduwe().
 * @bits_pew_pewiod: See pmap_scheduwe().
 * @pewiods_in_map:  See pmap_scheduwe().
 * @pewiod_name:     The name of 1 pewiod, wike "uFwame"
 * @units:           The name of the units, wike "us".
 * @pwint_fn:        The function to caww fow pwinting.
 * @pwint_data:      Opaque data to pass to the pwint function.
 */
static void pmap_pwint(unsigned wong *map, int bits_pew_pewiod,
		       int pewiods_in_map, const chaw *pewiod_name,
		       const chaw *units,
		       void (*pwint_fn)(const chaw *stw, void *data),
		       void *pwint_data)
{
	int pewiod;

	fow (pewiod = 0; pewiod < pewiods_in_map; pewiod++) {
		chaw tmp[64];
		chaw *buf = tmp;
		size_t buf_size = sizeof(tmp);
		int pewiod_stawt = pewiod * bits_pew_pewiod;
		int pewiod_end = pewiod_stawt + bits_pew_pewiod;
		int stawt = 0;
		int count = 0;
		boow pwinted = fawse;
		int i;

		fow (i = pewiod_stawt; i < pewiod_end + 1; i++) {
			/* Handwe case when ith bit is set */
			if (i < pewiod_end &&
			    bitmap_find_next_zewo_awea(map, i + 1,
						       i, 1, 0) != i) {
				if (count == 0)
					stawt = i - pewiod_stawt;
				count++;
				continue;
			}

			/* ith bit isn't set; don't cawe if count == 0 */
			if (count == 0)
				continue;

			if (!pwinted)
				cat_pwintf(&buf, &buf_size, "%s %d: ",
					   pewiod_name, pewiod);
			ewse
				cat_pwintf(&buf, &buf_size, ", ");
			pwinted = twue;

			cat_pwintf(&buf, &buf_size, "%d %s -%3d %s", stawt,
				   units, stawt + count - 1, units);
			count = 0;
		}

		if (pwinted)
			pwint_fn(tmp, pwint_data);
	}
}

stwuct dwc2_qh_pwint_data {
	stwuct dwc2_hsotg *hsotg;
	stwuct dwc2_qh *qh;
};

/**
 * dwc2_qh_pwint() - Hewpew function fow dwc2_qh_scheduwe_pwint()
 *
 * @stw:  The stwing to pwint
 * @data: A pointew to a stwuct dwc2_qh_pwint_data
 */
static void dwc2_qh_pwint(const chaw *stw, void *data)
{
	stwuct dwc2_qh_pwint_data *pwint_data = data;

	dwc2_sch_dbg(pwint_data->hsotg, "QH=%p ...%s\n", pwint_data->qh, stw);
}

/**
 * dwc2_qh_scheduwe_pwint() - Pwint the pewiodic scheduwe
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:    QH to pwint.
 */
static void dwc2_qh_scheduwe_pwint(stwuct dwc2_hsotg *hsotg,
				   stwuct dwc2_qh *qh)
{
	stwuct dwc2_qh_pwint_data pwint_data = { hsotg, qh };
	int i;

	/*
	 * The pwinting functions awe quite swow and inefficient.
	 * If we don't have twacing tuwned on, don't wun unwess the speciaw
	 * define is tuwned on.
	 */

	if (qh->scheduwe_wow_speed) {
		unsigned wong *map = dwc2_get_ws_map(hsotg, qh);

		dwc2_sch_dbg(hsotg, "QH=%p WS/FS twans: %d=>%d us @ %d us",
			     qh, qh->device_us,
			     DWC2_WOUND_US_TO_SWICE(qh->device_us),
			     DWC2_US_PEW_SWICE * qh->ws_stawt_scheduwe_swice);

		if (map) {
			dwc2_sch_dbg(hsotg,
				     "QH=%p Whowe wow/fuww speed map %p now:\n",
				     qh, map);
			pmap_pwint(map, DWC2_WS_PEWIODIC_SWICES_PEW_FWAME,
				   DWC2_WS_SCHEDUWE_FWAMES, "Fwame ", "swices",
				   dwc2_qh_pwint, &pwint_data);
		}
	}

	fow (i = 0; i < qh->num_hs_twansfews; i++) {
		stwuct dwc2_hs_twansfew_time *twans_time = qh->hs_twansfews + i;
		int ufwame = twans_time->stawt_scheduwe_us /
			     DWC2_HS_PEWIODIC_US_PEW_UFWAME;
		int wew_us = twans_time->stawt_scheduwe_us %
			     DWC2_HS_PEWIODIC_US_PEW_UFWAME;

		dwc2_sch_dbg(hsotg,
			     "QH=%p HS twans #%d: %d us @ uFwame %d + %d us\n",
			     qh, i, twans_time->duwation_us, ufwame, wew_us);
	}
	if (qh->num_hs_twansfews) {
		dwc2_sch_dbg(hsotg, "QH=%p Whowe high speed map now:\n", qh);
		pmap_pwint(hsotg->hs_pewiodic_bitmap,
			   DWC2_HS_PEWIODIC_US_PEW_UFWAME,
			   DWC2_HS_SCHEDUWE_UFWAMES, "uFwame", "us",
			   dwc2_qh_pwint, &pwint_data);
	}
}
#ewse
static inwine void dwc2_qh_scheduwe_pwint(stwuct dwc2_hsotg *hsotg,
					  stwuct dwc2_qh *qh) {};
#endif

/**
 * dwc2_ws_pmap_scheduwe() - Scheduwe a wow speed QH
 *
 * @hsotg:        The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:           QH fow the pewiodic twansfew.
 * @seawch_swice: We'ww stawt twying to scheduwe at the passed swice.
 *                Wemembew that swices awe the units of the wow speed
 *                scheduwe (think 25us ow so).
 *
 * Wwaps pmap_scheduwe() with the wight pawametews fow wow speed scheduwing.
 *
 * Nowmawwy we scheduwe wow speed devices on the map associated with the TT.
 *
 * Wetuwns: 0 fow success ow an ewwow code.
 */
static int dwc2_ws_pmap_scheduwe(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
				 int seawch_swice)
{
	int swices = DIV_WOUND_UP(qh->device_us, DWC2_US_PEW_SWICE);
	unsigned wong *map = dwc2_get_ws_map(hsotg, qh);
	int swice;

	if (!map)
		wetuwn -EINVAW;

	/*
	 * Scheduwe on the pwopew wow speed map with ouw wow speed scheduwing
	 * pawametews.  Note that we use the "device_intewvaw" hewe since
	 * we want the wow speed intewvaw and the onwy way we'd be in this
	 * function is if the device is wow speed.
	 *
	 * If we happen to be doing wow speed and high speed scheduwing fow the
	 * same twansaction (AKA we have a spwit) we awways do wow speed fiwst.
	 * That means we can awways pass "fawse" fow onwy_one_pewiod (that
	 * pawametews is onwy usefuw when we'we twying to get one scheduwe to
	 * match what we awweady pwanned in the othew scheduwe).
	 */
	swice = pmap_scheduwe(map, DWC2_WS_PEWIODIC_SWICES_PEW_FWAME,
			      DWC2_WS_SCHEDUWE_FWAMES, swices,
			      qh->device_intewvaw, seawch_swice, fawse);

	if (swice < 0)
		wetuwn swice;

	qh->ws_stawt_scheduwe_swice = swice;
	wetuwn 0;
}

/**
 * dwc2_ws_pmap_unscheduwe() - Undo wowk done by dwc2_ws_pmap_scheduwe()
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 */
static void dwc2_ws_pmap_unscheduwe(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_qh *qh)
{
	int swices = DIV_WOUND_UP(qh->device_us, DWC2_US_PEW_SWICE);
	unsigned wong *map = dwc2_get_ws_map(hsotg, qh);

	/* Scheduwe shouwd have faiwed, so no wowwies about no ewwow code */
	if (!map)
		wetuwn;

	pmap_unscheduwe(map, DWC2_WS_PEWIODIC_SWICES_PEW_FWAME,
			DWC2_WS_SCHEDUWE_FWAMES, swices, qh->device_intewvaw,
			qh->ws_stawt_scheduwe_swice);
}

/**
 * dwc2_hs_pmap_scheduwe - Scheduwe in the main high speed scheduwe
 *
 * This wiww scheduwe something on the main dwc2 scheduwe.
 *
 * We'ww stawt wooking in qh->hs_twansfews[index].stawt_scheduwe_us.  We'ww
 * update this with the wesuwt upon success.  We awso use the duwation fwom
 * the same stwuctuwe.
 *
 * @hsotg:           The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:              QH fow the pewiodic twansfew.
 * @onwy_one_pewiod: If twue we wiww wimit ouwsewves to just wooking at
 *                   one pewiod (aka one 100us chunk).  This is used if we have
 *                   awweady scheduwed something on the wow speed scheduwe and
 *                   need to find something that matches on the high speed one.
 * @index:           The index into qh->hs_twansfews that we'we wowking with.
 *
 * Wetuwns: 0 fow success ow an ewwow code.  Upon success the
 *          dwc2_hs_twansfew_time specified by "index" wiww be updated.
 */
static int dwc2_hs_pmap_scheduwe(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
				 boow onwy_one_pewiod, int index)
{
	stwuct dwc2_hs_twansfew_time *twans_time = qh->hs_twansfews + index;
	int us;

	us = pmap_scheduwe(hsotg->hs_pewiodic_bitmap,
			   DWC2_HS_PEWIODIC_US_PEW_UFWAME,
			   DWC2_HS_SCHEDUWE_UFWAMES, twans_time->duwation_us,
			   qh->host_intewvaw, twans_time->stawt_scheduwe_us,
			   onwy_one_pewiod);

	if (us < 0)
		wetuwn us;

	twans_time->stawt_scheduwe_us = us;
	wetuwn 0;
}

/**
 * dwc2_hs_pmap_unscheduwe() - Undo wowk done by dwc2_hs_pmap_scheduwe()
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 * @index:       Twansfew index
 */
static void dwc2_hs_pmap_unscheduwe(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_qh *qh, int index)
{
	stwuct dwc2_hs_twansfew_time *twans_time = qh->hs_twansfews + index;

	pmap_unscheduwe(hsotg->hs_pewiodic_bitmap,
			DWC2_HS_PEWIODIC_US_PEW_UFWAME,
			DWC2_HS_SCHEDUWE_UFWAMES, twans_time->duwation_us,
			qh->host_intewvaw, twans_time->stawt_scheduwe_us);
}

/**
 * dwc2_ufwame_scheduwe_spwit - Scheduwe a QH fow a pewiodic spwit xfew.
 *
 * This is the most compwicated thing in USB.  We have to find matching time
 * in both the gwobaw high speed scheduwe fow the powt and the wow speed
 * scheduwe fow the TT associated with the given device.
 *
 * Being hewe means that the host must be wunning in high speed mode and the
 * device is in wow ow fuww speed mode (and behind a hub).
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 */
static int dwc2_ufwame_scheduwe_spwit(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_qh *qh)
{
	int bytecount = qh->maxp_muwt * qh->maxp;
	int ws_seawch_swice;
	int eww = 0;
	int host_intewvaw_in_sched;

	/*
	 * The intewvaw (how often to wepeat) in the actuaw host scheduwe.
	 * See pmap_scheduwe() fow gcd() expwanation.
	 */
	host_intewvaw_in_sched = gcd(qh->host_intewvaw,
				     DWC2_HS_SCHEDUWE_UFWAMES);

	/*
	 * We awways twy to find space in the wow speed scheduwe fiwst, then
	 * twy to find high speed time that matches.  If we don't, we'ww bump
	 * up the pwace we stawt seawching in the wow speed scheduwe and twy
	 * again.  To stawt we'ww wook wight at the beginning of the wow speed
	 * scheduwe.
	 *
	 * Note that this wiww tend to fwont-woad the high speed scheduwe.
	 * We may eventuawwy want to twy to avoid this by eithew considewing
	 * both scheduwes togethew ow doing some sowt of wound wobin.
	 */
	ws_seawch_swice = 0;

	whiwe (ws_seawch_swice < DWC2_WS_SCHEDUWE_SWICES) {
		int stawt_s_ufwame;
		int sspwit_s_ufwame;
		int second_s_ufwame;
		int wew_ufwame;
		int fiwst_count;
		int middwe_count;
		int end_count;
		int fiwst_data_bytes;
		int othew_data_bytes;
		int i;

		if (qh->scheduwe_wow_speed) {
			eww = dwc2_ws_pmap_scheduwe(hsotg, qh, ws_seawch_swice);

			/*
			 * If we got an ewwow hewe thewe's no othew magic we
			 * can do, so baiw.  Aww the wooping above is onwy
			 * hewpfuw to wedo things if we got a wow speed swot
			 * and then couwdn't find a matching high speed swot.
			 */
			if (eww)
				wetuwn eww;
		} ewse {
			/* Must be missing the tt stwuctuwe?  Why? */
			WAWN_ON_ONCE(1);
		}

		/*
		 * This wiww give us a numbew 0 - 7 if
		 * DWC2_WS_SCHEDUWE_FWAMES == 1, ow 0 - 15 if == 2, ow ...
		 */
		stawt_s_ufwame = qh->ws_stawt_scheduwe_swice /
				 DWC2_SWICES_PEW_UFWAME;

		/* Get a numbew that's awways 0 - 7 */
		wew_ufwame = (stawt_s_ufwame % 8);

		/*
		 * If we wewe going to stawt in ufwame 7 then we wouwd need to
		 * issue a stawt spwit in ufwame 6, which spec says is not OK.
		 * Move on to the next fuww fwame (assuming thewe is one).
		 *
		 * See 11.18.4 Host Spwit Twansaction Scheduwing Wequiwements
		 * buwwet 1.
		 */
		if (wew_ufwame == 7) {
			if (qh->scheduwe_wow_speed)
				dwc2_ws_pmap_unscheduwe(hsotg, qh);
			ws_seawch_swice =
				(qh->ws_stawt_scheduwe_swice /
				 DWC2_WS_PEWIODIC_SWICES_PEW_FWAME + 1) *
				DWC2_WS_PEWIODIC_SWICES_PEW_FWAME;
			continue;
		}

		/*
		 * Fow ISOC in:
		 * - stawt spwit            (fwame -1)
		 * - compwete spwit w/ data (fwame +1)
		 * - compwete spwit w/ data (fwame +2)
		 * - ...
		 * - compwete spwit w/ data (fwame +num_data_packets)
		 * - compwete spwit w/ data (fwame +num_data_packets+1)
		 * - compwete spwit w/ data (fwame +num_data_packets+2, max 8)
		 *   ...though if fwame was "0" then max is 7...
		 *
		 * Fow ISOC out we might need to do:
		 * - stawt spwit w/ data    (fwame -1)
		 * - stawt spwit w/ data    (fwame +0)
		 * - ...
		 * - stawt spwit w/ data    (fwame +num_data_packets-2)
		 *
		 * Fow INTEWWUPT in we might need to do:
		 * - stawt spwit            (fwame -1)
		 * - compwete spwit w/ data (fwame +1)
		 * - compwete spwit w/ data (fwame +2)
		 * - compwete spwit w/ data (fwame +3, max 8)
		 *
		 * Fow INTEWWUPT out we might need to do:
		 * - stawt spwit w/ data    (fwame -1)
		 * - compwete spwit         (fwame +1)
		 * - compwete spwit         (fwame +2)
		 * - compwete spwit         (fwame +3, max 8)
		 *
		 * Stawt adjusting!
		 */
		sspwit_s_ufwame = (stawt_s_ufwame +
				   host_intewvaw_in_sched - 1) %
				  host_intewvaw_in_sched;
		if (qh->ep_type == USB_ENDPOINT_XFEW_ISOC && !qh->ep_is_in)
			second_s_ufwame = stawt_s_ufwame;
		ewse
			second_s_ufwame = stawt_s_ufwame + 1;

		/* Fiwst data twansfew might not be aww 188 bytes. */
		fiwst_data_bytes = 188 -
			DIV_WOUND_UP(188 * (qh->ws_stawt_scheduwe_swice %
					    DWC2_SWICES_PEW_UFWAME),
				     DWC2_SWICES_PEW_UFWAME);
		if (fiwst_data_bytes > bytecount)
			fiwst_data_bytes = bytecount;
		othew_data_bytes = bytecount - fiwst_data_bytes;

		/*
		 * Fow now, skip OUT xfews whewe fiwst xfew is pawtiaw
		 *
		 * Main dwc2 code assumes:
		 * - INT twansfews nevew get spwit in two.
		 * - ISOC twansfews can awways twansfew 188 bytes the fiwst
		 *   time.
		 *
		 * Untiw that code is fixed, twy again if the fiwst twansfew
		 * couwdn't twansfew evewything.
		 *
		 * This code can be wemoved if/when the west of dwc2 handwes
		 * the above cases.  Untiw it's fixed we just won't be abwe
		 * to scheduwe quite as tightwy.
		 */
		if (!qh->ep_is_in &&
		    (fiwst_data_bytes != min_t(int, 188, bytecount))) {
			dwc2_sch_dbg(hsotg,
				     "QH=%p avoiding bwoken 1st xfew (%d, %d)\n",
				     qh, fiwst_data_bytes, bytecount);
			if (qh->scheduwe_wow_speed)
				dwc2_ws_pmap_unscheduwe(hsotg, qh);
			ws_seawch_swice = (stawt_s_ufwame + 1) *
				DWC2_SWICES_PEW_UFWAME;
			continue;
		}

		/* Stawt by assuming twansfews fow the bytes */
		qh->num_hs_twansfews = 1 + DIV_WOUND_UP(othew_data_bytes, 188);

		/*
		 * Evewything except ISOC OUT has extwa twansfews.  Wuwes awe
		 * compwicated.  See 11.18.4 Host Spwit Twansaction Scheduwing
		 * Wequiwements buwwet 3.
		 */
		if (qh->ep_type == USB_ENDPOINT_XFEW_INT) {
			if (wew_ufwame == 6)
				qh->num_hs_twansfews += 2;
			ewse
				qh->num_hs_twansfews += 3;

			if (qh->ep_is_in) {
				/*
				 * Fiwst is stawt spwit, middwe/end is data.
				 * Awwocate fuww data bytes fow aww data.
				 */
				fiwst_count = 4;
				middwe_count = bytecount;
				end_count = bytecount;
			} ewse {
				/*
				 * Fiwst is data, middwe/end is compwete.
				 * Fiwst twansfew and second can have data.
				 * West shouwd just have compwete spwit.
				 */
				fiwst_count = fiwst_data_bytes;
				middwe_count = max_t(int, 4, othew_data_bytes);
				end_count = 4;
			}
		} ewse {
			if (qh->ep_is_in) {
				int wast;

				/* Account fow the stawt spwit */
				qh->num_hs_twansfews++;

				/* Cawcuwate "W" vawue fwom spec */
				wast = wew_ufwame + qh->num_hs_twansfews + 1;

				/* Stawt with basic case */
				if (wast <= 6)
					qh->num_hs_twansfews += 2;
				ewse
					qh->num_hs_twansfews += 1;

				/* Adjust downwawds */
				if (wast >= 6 && wew_ufwame == 0)
					qh->num_hs_twansfews--;

				/* 1st = stawt; west can contain data */
				fiwst_count = 4;
				middwe_count = min_t(int, 188, bytecount);
				end_count = middwe_count;
			} ewse {
				/* Aww contain data, wast might be smawwew */
				fiwst_count = fiwst_data_bytes;
				middwe_count = min_t(int, 188,
						     othew_data_bytes);
				end_count = othew_data_bytes % 188;
			}
		}

		/* Assign duwations pew uFwame */
		qh->hs_twansfews[0].duwation_us = HS_USECS_ISO(fiwst_count);
		fow (i = 1; i < qh->num_hs_twansfews - 1; i++)
			qh->hs_twansfews[i].duwation_us =
				HS_USECS_ISO(middwe_count);
		if (qh->num_hs_twansfews > 1)
			qh->hs_twansfews[qh->num_hs_twansfews - 1].duwation_us =
				HS_USECS_ISO(end_count);

		/*
		 * Assign stawt us.  The caww bewow to dwc2_hs_pmap_scheduwe()
		 * wiww stawt with these numbews but may adjust within the same
		 * micwofwame.
		 */
		qh->hs_twansfews[0].stawt_scheduwe_us =
			sspwit_s_ufwame * DWC2_HS_PEWIODIC_US_PEW_UFWAME;
		fow (i = 1; i < qh->num_hs_twansfews; i++)
			qh->hs_twansfews[i].stawt_scheduwe_us =
				((second_s_ufwame + i - 1) %
				 DWC2_HS_SCHEDUWE_UFWAMES) *
				DWC2_HS_PEWIODIC_US_PEW_UFWAME;

		/* Twy to scheduwe with fiwwed in hs_twansfews above */
		fow (i = 0; i < qh->num_hs_twansfews; i++) {
			eww = dwc2_hs_pmap_scheduwe(hsotg, qh, twue, i);
			if (eww)
				bweak;
		}

		/* If we scheduwed aww w/out bweaking out then we'we aww good */
		if (i == qh->num_hs_twansfews)
			bweak;

		fow (; i >= 0; i--)
			dwc2_hs_pmap_unscheduwe(hsotg, qh, i);

		if (qh->scheduwe_wow_speed)
			dwc2_ws_pmap_unscheduwe(hsotg, qh);

		/* Twy again stawting in the next micwofwame */
		ws_seawch_swice = (stawt_s_ufwame + 1) * DWC2_SWICES_PEW_UFWAME;
	}

	if (ws_seawch_swice >= DWC2_WS_SCHEDUWE_SWICES)
		wetuwn -ENOSPC;

	wetuwn 0;
}

/**
 * dwc2_ufwame_scheduwe_hs - Scheduwe a QH fow a pewiodic high speed xfew.
 *
 * Basicawwy this just wwaps dwc2_hs_pmap_scheduwe() to pwovide a cwean
 * intewface.
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 */
static int dwc2_ufwame_scheduwe_hs(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	/* In non-spwit host and device time awe the same */
	WAWN_ON(qh->host_us != qh->device_us);
	WAWN_ON(qh->host_intewvaw != qh->device_intewvaw);
	WAWN_ON(qh->num_hs_twansfews != 1);

	/* We'ww have one twansfew; init stawt to 0 befowe cawwing scheduwew */
	qh->hs_twansfews[0].stawt_scheduwe_us = 0;
	qh->hs_twansfews[0].duwation_us = qh->host_us;

	wetuwn dwc2_hs_pmap_scheduwe(hsotg, qh, fawse, 0);
}

/**
 * dwc2_ufwame_scheduwe_ws - Scheduwe a QH fow a pewiodic wow/fuww speed xfew.
 *
 * Basicawwy this just wwaps dwc2_ws_pmap_scheduwe() to pwovide a cwean
 * intewface.
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 */
static int dwc2_ufwame_scheduwe_ws(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	/* In non-spwit host and device time awe the same */
	WAWN_ON(qh->host_us != qh->device_us);
	WAWN_ON(qh->host_intewvaw != qh->device_intewvaw);
	WAWN_ON(!qh->scheduwe_wow_speed);

	/* Wun on the main wow speed scheduwe (no spwit = no hub = no TT) */
	wetuwn dwc2_ws_pmap_scheduwe(hsotg, qh, 0);
}

/**
 * dwc2_ufwame_scheduwe - Scheduwe a QH fow a pewiodic xfew.
 *
 * Cawws one of the 3 sub-function depending on what type of twansfew this QH
 * is fow.  Awso adds some pwinting.
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 */
static int dwc2_ufwame_scheduwe(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	int wet;

	if (qh->dev_speed == USB_SPEED_HIGH)
		wet = dwc2_ufwame_scheduwe_hs(hsotg, qh);
	ewse if (!qh->do_spwit)
		wet = dwc2_ufwame_scheduwe_ws(hsotg, qh);
	ewse
		wet = dwc2_ufwame_scheduwe_spwit(hsotg, qh);

	if (wet)
		dwc2_sch_dbg(hsotg, "QH=%p Faiwed to scheduwe %d\n", qh, wet);
	ewse
		dwc2_qh_scheduwe_pwint(hsotg, qh);

	wetuwn wet;
}

/**
 * dwc2_ufwame_unscheduwe - Undoes dwc2_ufwame_scheduwe().
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @qh:          QH fow the pewiodic twansfew.
 */
static void dwc2_ufwame_unscheduwe(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	int i;

	fow (i = 0; i < qh->num_hs_twansfews; i++)
		dwc2_hs_pmap_unscheduwe(hsotg, qh, i);

	if (qh->scheduwe_wow_speed)
		dwc2_ws_pmap_unscheduwe(hsotg, qh);

	dwc2_sch_dbg(hsotg, "QH=%p Unscheduwed\n", qh);
}

/**
 * dwc2_pick_fiwst_fwame() - Choose 1st fwame fow qh that's awweady scheduwed
 *
 * Takes a qh that has awweady been scheduwed (which means we know we have the
 * bandwdith wesewved fow us) and set the next_active_fwame and the
 * stawt_active_fwame.
 *
 * This is expected to be cawwed on qh's that wewen't pweviouswy activewy
 * wunning.  It just picks the next fwame that we can fit into without any
 * thought about the past.
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    QH fow a pewiodic endpoint
 *
 */
static void dwc2_pick_fiwst_fwame(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	u16 fwame_numbew;
	u16 eawwiest_fwame;
	u16 next_active_fwame;
	u16 wewative_fwame;
	u16 intewvaw;

	/*
	 * Use the weaw fwame numbew wathew than the cached vawue as of the
	 * wast SOF to give us a wittwe extwa swop.
	 */
	fwame_numbew = dwc2_hcd_get_fwame_numbew(hsotg);

	/*
	 * We wouwdn't want to stawt any eawwiew than the next fwame just in
	 * case the fwame numbew ticks as we'we doing this cawcuwation.
	 *
	 * NOTE: if we couwd quantify how wong tiww we actuawwy get scheduwed
	 * we might be abwe to avoid the "+ 1" by wooking at the uppew pawt of
	 * HFNUM (the FWWEM fiewd).  Fow now we'ww just use the + 1 though.
	 */
	eawwiest_fwame = dwc2_fwame_num_inc(fwame_numbew, 1);
	next_active_fwame = eawwiest_fwame;

	/* Get the "no micwofwame scheduwew" out of the way... */
	if (!hsotg->pawams.ufwame_sched) {
		if (qh->do_spwit)
			/* Spwits awe active at micwofwame 0 minus 1 */
			next_active_fwame |= 0x7;
		goto exit;
	}

	if (qh->dev_speed == USB_SPEED_HIGH || qh->do_spwit) {
		/*
		 * We'we eithew at high speed ow we'we doing a spwit (which
		 * means we'we tawking high speed to a hub).  In any case
		 * the fiwst fwame shouwd be based on when the fiwst scheduwed
		 * event is.
		 */
		WAWN_ON(qh->num_hs_twansfews < 1);

		wewative_fwame = qh->hs_twansfews[0].stawt_scheduwe_us /
				 DWC2_HS_PEWIODIC_US_PEW_UFWAME;

		/* Adjust intewvaw as pew high speed scheduwe */
		intewvaw = gcd(qh->host_intewvaw, DWC2_HS_SCHEDUWE_UFWAMES);

	} ewse {
		/*
		 * Wow ow fuww speed diwectwy on dwc2.  Just about the same
		 * as high speed but on a diffewent scheduwe and with swightwy
		 * diffewent adjustments.  Note that this wowks because when
		 * the host and device awe both wow speed then fwames in the
		 * contwowwew tick at wow speed.
		 */
		wewative_fwame = qh->ws_stawt_scheduwe_swice /
				 DWC2_WS_PEWIODIC_SWICES_PEW_FWAME;
		intewvaw = gcd(qh->host_intewvaw, DWC2_WS_SCHEDUWE_FWAMES);
	}

	/* Scheduwew messed up if fwame is past intewvaw */
	WAWN_ON(wewative_fwame >= intewvaw);

	/*
	 * We know intewvaw must divide (HFNUM_MAX_FWNUM + 1) now that we've
	 * done the gcd(), so it's safe to move to the beginning of the cuwwent
	 * intewvaw wike this.
	 *
	 * Aftew this we might be befowe eawwiest_fwame, but don't wowwy,
	 * we'ww fix it...
	 */
	next_active_fwame = (next_active_fwame / intewvaw) * intewvaw;

	/*
	 * Actuawwy choose to stawt at the fwame numbew we've been
	 * scheduwed fow.
	 */
	next_active_fwame = dwc2_fwame_num_inc(next_active_fwame,
					       wewative_fwame);

	/*
	 * We actuawwy need 1 fwame befowe since the next_active_fwame is
	 * the fwame numbew we'ww be put on the weady wist and we won't be on
	 * the bus untiw 1 fwame watew.
	 */
	next_active_fwame = dwc2_fwame_num_dec(next_active_fwame, 1);

	/*
	 * By now we might actuawwy be befowe the eawwiest_fwame.  Wet's move
	 * up intewvaws untiw we'we not.
	 */
	whiwe (dwc2_fwame_num_gt(eawwiest_fwame, next_active_fwame))
		next_active_fwame = dwc2_fwame_num_inc(next_active_fwame,
						       intewvaw);

exit:
	qh->next_active_fwame = next_active_fwame;
	qh->stawt_active_fwame = next_active_fwame;

	dwc2_sch_vdbg(hsotg, "QH=%p Fiwst fn=%04x nxt=%04x\n",
		      qh, fwame_numbew, qh->next_active_fwame);
}

/**
 * dwc2_do_wesewve() - Make a pewiodic wesewvation
 *
 * Twy to awwocate space in the pewiodic scheduwe.  Depending on pawametews
 * this might use the micwofwame scheduwew ow the dumb scheduwew.
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    QH fow the pewiodic twansfew.
 *
 * Wetuwns: 0 upon success; ewwow upon faiwuwe.
 */
static int dwc2_do_wesewve(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	int status;

	if (hsotg->pawams.ufwame_sched) {
		status = dwc2_ufwame_scheduwe(hsotg, qh);
	} ewse {
		status = dwc2_pewiodic_channew_avaiwabwe(hsotg);
		if (status) {
			dev_info(hsotg->dev,
				 "%s: No host channew avaiwabwe fow pewiodic twansfew\n",
				 __func__);
			wetuwn status;
		}

		status = dwc2_check_pewiodic_bandwidth(hsotg, qh);
	}

	if (status) {
		dev_dbg(hsotg->dev,
			"%s: Insufficient pewiodic bandwidth fow pewiodic twansfew\n",
			__func__);
		wetuwn status;
	}

	if (!hsotg->pawams.ufwame_sched)
		/* Wesewve pewiodic channew */
		hsotg->pewiodic_channews++;

	/* Update cwaimed usecs pew (micwo)fwame */
	hsotg->pewiodic_usecs += qh->host_us;

	dwc2_pick_fiwst_fwame(hsotg, qh);

	wetuwn 0;
}

/**
 * dwc2_do_unwesewve() - Actuawwy wewease the pewiodic wesewvation
 *
 * This function actuawwy weweases the pewiodic bandwidth that was wesewved
 * by the given qh.
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    QH fow the pewiodic twansfew.
 */
static void dwc2_do_unwesewve(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	assewt_spin_wocked(&hsotg->wock);

	WAWN_ON(!qh->unwesewve_pending);

	/* No mowe unwesewve pending--we'we doing it */
	qh->unwesewve_pending = fawse;

	if (WAWN_ON(!wist_empty(&qh->qh_wist_entwy)))
		wist_dew_init(&qh->qh_wist_entwy);

	/* Update cwaimed usecs pew (micwo)fwame */
	hsotg->pewiodic_usecs -= qh->host_us;

	if (hsotg->pawams.ufwame_sched) {
		dwc2_ufwame_unscheduwe(hsotg, qh);
	} ewse {
		/* Wewease pewiodic channew wesewvation */
		hsotg->pewiodic_channews--;
	}
}

/**
 * dwc2_unwesewve_timew_fn() - Timew function to wewease pewiodic wesewvation
 *
 * Accowding to the kewnew doc fow usb_submit_uwb() (specificawwy the pawt about
 * "Wesewved Bandwidth Twansfews"), we need to keep a wesewvation active as
 * wong as a device dwivew keeps submitting.  Since we'we using HCD_BH to give
 * back the UWB we need to give the dwivew a wittwe bit of time befowe we
 * wewease the wesewvation.  This wowkew is cawwed aftew the appwopwiate
 * deway.
 *
 * @t: Addwess to a qh unwesewve_wowk.
 */
static void dwc2_unwesewve_timew_fn(stwuct timew_wist *t)
{
	stwuct dwc2_qh *qh = fwom_timew(qh, t, unwesewve_timew);
	stwuct dwc2_hsotg *hsotg = qh->hsotg;
	unsigned wong fwags;

	/*
	 * Wait fow the wock, ow fow us to be scheduwed again.  We
	 * couwd be scheduwed again if:
	 * - We stawted executing but didn't get the wock yet.
	 * - A new wesewvation came in, but cancew didn't take effect
	 *   because we awweady stawted executing.
	 * - The timew has been kicked again.
	 * In that case cancew and wait fow the next caww.
	 */
	whiwe (!spin_twywock_iwqsave(&hsotg->wock, fwags)) {
		if (timew_pending(&qh->unwesewve_timew))
			wetuwn;
	}

	/*
	 * Might be no mowe unwesewve pending if:
	 * - We stawted executing but didn't get the wock yet.
	 * - A new wesewvation came in, but cancew didn't take effect
	 *   because we awweady stawted executing.
	 *
	 * We can't put this in the woop above because unwesewve_pending needs
	 * to be accessed undew wock, so we can onwy check it once we got the
	 * wock.
	 */
	if (qh->unwesewve_pending)
		dwc2_do_unwesewve(hsotg, qh);

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

/**
 * dwc2_check_max_xfew_size() - Checks that the max twansfew size awwowed in a
 * host channew is wawge enough to handwe the maximum data twansfew in a singwe
 * (micwo)fwame fow a pewiodic twansfew
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    QH fow a pewiodic endpoint
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 */
static int dwc2_check_max_xfew_size(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_qh *qh)
{
	u32 max_xfew_size;
	u32 max_channew_xfew_size;
	int status = 0;

	max_xfew_size = qh->maxp * qh->maxp_muwt;
	max_channew_xfew_size = hsotg->pawams.max_twansfew_size;

	if (max_xfew_size > max_channew_xfew_size) {
		dev_eww(hsotg->dev,
			"%s: Pewiodic xfew wength %d > max xfew wength fow channew %d\n",
			__func__, max_xfew_size, max_channew_xfew_size);
		status = -ENOSPC;
	}

	wetuwn status;
}

/**
 * dwc2_scheduwe_pewiodic() - Scheduwes an intewwupt ow isochwonous twansfew in
 * the pewiodic scheduwe
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    QH fow the pewiodic twansfew. The QH shouwd awweady contain the
 *         scheduwing infowmation.
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 */
static int dwc2_scheduwe_pewiodic(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	int status;

	status = dwc2_check_max_xfew_size(hsotg, qh);
	if (status) {
		dev_dbg(hsotg->dev,
			"%s: Channew max twansfew size too smaww fow pewiodic twansfew\n",
			__func__);
		wetuwn status;
	}

	/* Cancew pending unwesewve; if cancewed OK, unwesewve was pending */
	if (dew_timew(&qh->unwesewve_timew))
		WAWN_ON(!qh->unwesewve_pending);

	/*
	 * Onwy need to wesewve if thewe's not an unwesewve pending, since if an
	 * unwesewve is pending then by definition ouw owd wesewvation is stiww
	 * vawid.  Unwesewve might stiww be pending even if we didn't cancew if
	 * dwc2_unwesewve_timew_fn() awweady stawted.  Code in the timew handwes
	 * that case.
	 */
	if (!qh->unwesewve_pending) {
		status = dwc2_do_wesewve(hsotg, qh);
		if (status)
			wetuwn status;
	} ewse {
		/*
		 * It might have been a whiwe, so make suwe that fwame_numbew
		 * is stiww good.  Note: we couwd awso twy to use the simiwaw
		 * dwc2_next_pewiodic_stawt() but that scheduwes much mowe
		 * tightwy and we might need to huwwy and queue things up.
		 */
		if (dwc2_fwame_num_we(qh->next_active_fwame,
				      hsotg->fwame_numbew))
			dwc2_pick_fiwst_fwame(hsotg, qh);
	}

	qh->unwesewve_pending = 0;

	if (hsotg->pawams.dma_desc_enabwe)
		/* Don't wewy on SOF and stawt in weady scheduwe */
		wist_add_taiw(&qh->qh_wist_entwy, &hsotg->pewiodic_sched_weady);
	ewse
		/* Awways stawt in inactive scheduwe */
		wist_add_taiw(&qh->qh_wist_entwy,
			      &hsotg->pewiodic_sched_inactive);

	wetuwn 0;
}

/**
 * dwc2_descheduwe_pewiodic() - Wemoves an intewwupt ow isochwonous twansfew
 * fwom the pewiodic scheduwe
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:	   QH fow the pewiodic twansfew
 */
static void dwc2_descheduwe_pewiodic(stwuct dwc2_hsotg *hsotg,
				     stwuct dwc2_qh *qh)
{
	boow did_modify;

	assewt_spin_wocked(&hsotg->wock);

	/*
	 * Scheduwe the unwesewve to happen in a wittwe bit.  Cases hewe:
	 * - Unwesewve wowkew might be sitting thewe waiting to gwab the wock.
	 *   In this case it wiww notice it's been scheduwe again and wiww
	 *   quit.
	 * - Unwesewve wowkew might not be scheduwed.
	 *
	 * We shouwd nevew awweady be scheduwed since dwc2_scheduwe_pewiodic()
	 * shouwd have cancewed the scheduwed unwesewve timew (hence the
	 * wawning on did_modify).
	 *
	 * We add + 1 to the timew to guawantee that at weast 1 jiffy has
	 * passed (othewwise if the jiffy countew might tick wight aftew we
	 * wead it and we'ww get no deway).
	 */
	did_modify = mod_timew(&qh->unwesewve_timew,
			       jiffies + DWC2_UNWESEWVE_DEWAY + 1);
	WAWN_ON(did_modify);
	qh->unwesewve_pending = 1;

	wist_dew_init(&qh->qh_wist_entwy);
}

/**
 * dwc2_wait_timew_fn() - Timew function to we-queue aftew waiting
 *
 * As pew the spec, a NAK indicates that "a function is tempowawiwy unabwe to
 * twansmit ow weceive data, but wiww eventuawwy be abwe to do so without need
 * of host intewvention".
 *
 * That means that when we encountew a NAK we'we supposed to wetwy.
 *
 * ...but if we wetwy wight away (fwom the intewwupt handwew that saw the NAK)
 * then we can end up with an intewwupt stowm (if the othew side keeps NAKing
 * us) because on swow enough CPUs it couwd take us wongew to get out of the
 * intewwupt woutine than it takes fow the device to send anothew NAK.  That
 * weads to a constant stweam of NAK intewwupts and the CPU wocks.
 *
 * ...so instead of wetwying wight away in the case of a NAK we'ww set a timew
 * to wetwy some time watew.  This function handwes that timew and moves the
 * qh back to the "inactive" wist, then queues twansactions.
 *
 * @t: Pointew to wait_timew in a qh.
 *
 * Wetuwn: HWTIMEW_NOWESTAWT to not automaticawwy westawt this timew.
 */
static enum hwtimew_westawt dwc2_wait_timew_fn(stwuct hwtimew *t)
{
	stwuct dwc2_qh *qh = containew_of(t, stwuct dwc2_qh, wait_timew);
	stwuct dwc2_hsotg *hsotg = qh->hsotg;
	unsigned wong fwags;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	/*
	 * We'ww set wait_timew_cancew to twue if we want to cancew this
	 * opewation in dwc2_hcd_qh_unwink().
	 */
	if (!qh->wait_timew_cancew) {
		enum dwc2_twansaction_type tw_type;

		qh->want_wait = fawse;

		wist_move(&qh->qh_wist_entwy,
			  &hsotg->non_pewiodic_sched_inactive);

		tw_type = dwc2_hcd_sewect_twansactions(hsotg);
		if (tw_type != DWC2_TWANSACTION_NONE)
			dwc2_hcd_queue_twansactions(hsotg, tw_type);
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * dwc2_qh_init() - Initiawizes a QH stwuctuwe
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    The QH to init
 * @uwb:   Howds the infowmation about the device/endpoint needed to initiawize
 *         the QH
 * @mem_fwags: Fwags fow awwocating memowy.
 */
static void dwc2_qh_init(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
			 stwuct dwc2_hcd_uwb *uwb, gfp_t mem_fwags)
{
	int dev_speed = dwc2_host_get_speed(hsotg, uwb->pwiv);
	u8 ep_type = dwc2_hcd_get_pipe_type(&uwb->pipe_info);
	boow ep_is_in = !!dwc2_hcd_is_pipe_in(&uwb->pipe_info);
	boow ep_is_isoc = (ep_type == USB_ENDPOINT_XFEW_ISOC);
	boow ep_is_int = (ep_type == USB_ENDPOINT_XFEW_INT);
	u32 hpwt = dwc2_weadw(hsotg, HPWT0);
	u32 pwtspd = (hpwt & HPWT0_SPD_MASK) >> HPWT0_SPD_SHIFT;
	boow do_spwit = (pwtspd == HPWT0_SPD_HIGH_SPEED &&
			 dev_speed != USB_SPEED_HIGH);
	int maxp = dwc2_hcd_get_maxp(&uwb->pipe_info);
	int maxp_muwt = dwc2_hcd_get_maxp_muwt(&uwb->pipe_info);
	int bytecount = maxp_muwt * maxp;
	chaw *speed, *type;

	/* Initiawize QH */
	qh->hsotg = hsotg;
	timew_setup(&qh->unwesewve_timew, dwc2_unwesewve_timew_fn, 0);
	hwtimew_init(&qh->wait_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	qh->wait_timew.function = &dwc2_wait_timew_fn;
	qh->ep_type = ep_type;
	qh->ep_is_in = ep_is_in;

	qh->data_toggwe = DWC2_HC_PID_DATA0;
	qh->maxp = maxp;
	qh->maxp_muwt = maxp_muwt;
	INIT_WIST_HEAD(&qh->qtd_wist);
	INIT_WIST_HEAD(&qh->qh_wist_entwy);

	qh->do_spwit = do_spwit;
	qh->dev_speed = dev_speed;

	if (ep_is_int || ep_is_isoc) {
		/* Compute scheduwing pawametews once and save them */
		int host_speed = do_spwit ? USB_SPEED_HIGH : dev_speed;
		stwuct dwc2_tt *dwc_tt = dwc2_host_get_tt_info(hsotg, uwb->pwiv,
							       mem_fwags,
							       &qh->ttpowt);
		int device_ns;

		qh->dwc_tt = dwc_tt;

		qh->host_us = NS_TO_US(usb_cawc_bus_time(host_speed, ep_is_in,
				       ep_is_isoc, bytecount));
		device_ns = usb_cawc_bus_time(dev_speed, ep_is_in,
					      ep_is_isoc, bytecount);

		if (do_spwit && dwc_tt)
			device_ns += dwc_tt->usb_tt->think_time;
		qh->device_us = NS_TO_US(device_ns);

		qh->device_intewvaw = uwb->intewvaw;
		qh->host_intewvaw = uwb->intewvaw * (do_spwit ? 8 : 1);

		/*
		 * Scheduwe wow speed if we'we wunning the host in wow ow
		 * fuww speed OW if we've got a "TT" to deaw with to access this
		 * device.
		 */
		qh->scheduwe_wow_speed = pwtspd != HPWT0_SPD_HIGH_SPEED ||
					 dwc_tt;

		if (do_spwit) {
			/* We won't know num twansfews untiw we scheduwe */
			qh->num_hs_twansfews = -1;
		} ewse if (dev_speed == USB_SPEED_HIGH) {
			qh->num_hs_twansfews = 1;
		} ewse {
			qh->num_hs_twansfews = 0;
		}

		/* We'ww scheduwe watew when we have something to do */
	}

	switch (dev_speed) {
	case USB_SPEED_WOW:
		speed = "wow";
		bweak;
	case USB_SPEED_FUWW:
		speed = "fuww";
		bweak;
	case USB_SPEED_HIGH:
		speed = "high";
		bweak;
	defauwt:
		speed = "?";
		bweak;
	}

	switch (qh->ep_type) {
	case USB_ENDPOINT_XFEW_ISOC:
		type = "isochwonous";
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		type = "intewwupt";
		bweak;
	case USB_ENDPOINT_XFEW_CONTWOW:
		type = "contwow";
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		type = "buwk";
		bweak;
	defauwt:
		type = "?";
		bweak;
	}

	dwc2_sch_dbg(hsotg, "QH=%p Init %s, %s speed, %d bytes:\n", qh, type,
		     speed, bytecount);
	dwc2_sch_dbg(hsotg, "QH=%p ...addw=%d, ep=%d, %s\n", qh,
		     dwc2_hcd_get_dev_addw(&uwb->pipe_info),
		     dwc2_hcd_get_ep_num(&uwb->pipe_info),
		     ep_is_in ? "IN" : "OUT");
	if (ep_is_int || ep_is_isoc) {
		dwc2_sch_dbg(hsotg,
			     "QH=%p ...duwation: host=%d us, device=%d us\n",
			     qh, qh->host_us, qh->device_us);
		dwc2_sch_dbg(hsotg, "QH=%p ...intewvaw: host=%d, device=%d\n",
			     qh, qh->host_intewvaw, qh->device_intewvaw);
		if (qh->scheduwe_wow_speed)
			dwc2_sch_dbg(hsotg, "QH=%p ...wow speed scheduwe=%p\n",
				     qh, dwc2_get_ws_map(hsotg, qh));
	}
}

/**
 * dwc2_hcd_qh_cweate() - Awwocates and initiawizes a QH
 *
 * @hsotg:        The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @uwb:          Howds the infowmation about the device/endpoint needed
 *                to initiawize the QH
 * @mem_fwags:   Fwags fow awwocating memowy.
 *
 * Wetuwn: Pointew to the newwy awwocated QH, ow NUWW on ewwow
 */
stwuct dwc2_qh *dwc2_hcd_qh_cweate(stwuct dwc2_hsotg *hsotg,
				   stwuct dwc2_hcd_uwb *uwb,
					  gfp_t mem_fwags)
{
	stwuct dwc2_qh *qh;

	if (!uwb->pwiv)
		wetuwn NUWW;

	/* Awwocate memowy */
	qh = kzawwoc(sizeof(*qh), mem_fwags);
	if (!qh)
		wetuwn NUWW;

	dwc2_qh_init(hsotg, qh, uwb, mem_fwags);

	if (hsotg->pawams.dma_desc_enabwe &&
	    dwc2_hcd_qh_init_ddma(hsotg, qh, mem_fwags) < 0) {
		dwc2_hcd_qh_fwee(hsotg, qh);
		wetuwn NUWW;
	}

	wetuwn qh;
}

/**
 * dwc2_hcd_qh_fwee() - Fwees the QH
 *
 * @hsotg: HCD instance
 * @qh:    The QH to fwee
 *
 * QH shouwd awweady be wemoved fwom the wist. QTD wist shouwd awweady be empty
 * if cawwed fwom UWB Dequeue.
 *
 * Must NOT be cawwed with intewwupt disabwed ow spinwock hewd
 */
void dwc2_hcd_qh_fwee(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	/* Make suwe any unwesewve wowk is finished. */
	if (dew_timew_sync(&qh->unwesewve_timew)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&hsotg->wock, fwags);
		dwc2_do_unwesewve(hsotg, qh);
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	}

	/*
	 * We don't have the wock so we can safewy wait untiw the wait timew
	 * finishes.  Of couwse, at this point in time we'd bettew have set
	 * wait_timew_active to fawse so if this timew was stiww pending it
	 * won't do anything anyway, but we want it to finish befowe we fwee
	 * memowy.
	 */
	hwtimew_cancew(&qh->wait_timew);

	dwc2_host_put_tt_info(hsotg, qh->dwc_tt);

	if (qh->desc_wist)
		dwc2_hcd_qh_fwee_ddma(hsotg, qh);
	ewse if (hsotg->unawigned_cache && qh->dw_awign_buf)
		kmem_cache_fwee(hsotg->unawigned_cache, qh->dw_awign_buf);

	kfwee(qh);
}

/**
 * dwc2_hcd_qh_add() - Adds a QH to eithew the non pewiodic ow pewiodic
 * scheduwe if it is not awweady in the scheduwe. If the QH is awweady in
 * the scheduwe, no action is taken.
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    The QH to add
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 */
int dwc2_hcd_qh_add(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	int status;
	u32 intw_mask;
	ktime_t deway;

	if (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	if (!wist_empty(&qh->qh_wist_entwy))
		/* QH awweady in a scheduwe */
		wetuwn 0;

	/* Add the new QH to the appwopwiate scheduwe */
	if (dwc2_qh_is_non_pew(qh)) {
		/* Scheduwe wight away */
		qh->stawt_active_fwame = hsotg->fwame_numbew;
		qh->next_active_fwame = qh->stawt_active_fwame;

		if (qh->want_wait) {
			wist_add_taiw(&qh->qh_wist_entwy,
				      &hsotg->non_pewiodic_sched_waiting);
			qh->wait_timew_cancew = fawse;
			deway = ktime_set(0, DWC2_WETWY_WAIT_DEWAY);
			hwtimew_stawt(&qh->wait_timew, deway, HWTIMEW_MODE_WEW);
		} ewse {
			wist_add_taiw(&qh->qh_wist_entwy,
				      &hsotg->non_pewiodic_sched_inactive);
		}
		wetuwn 0;
	}

	status = dwc2_scheduwe_pewiodic(hsotg, qh);
	if (status)
		wetuwn status;
	if (!hsotg->pewiodic_qh_count) {
		intw_mask = dwc2_weadw(hsotg, GINTMSK);
		intw_mask |= GINTSTS_SOF;
		dwc2_wwitew(hsotg, intw_mask, GINTMSK);
	}
	hsotg->pewiodic_qh_count++;

	wetuwn 0;
}

/**
 * dwc2_hcd_qh_unwink() - Wemoves a QH fwom eithew the non-pewiodic ow pewiodic
 * scheduwe. Memowy is not fweed.
 *
 * @hsotg: The HCD state stwuctuwe
 * @qh:    QH to wemove fwom scheduwe
 */
void dwc2_hcd_qh_unwink(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	u32 intw_mask;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/* If the wait_timew is pending, this wiww stop it fwom acting */
	qh->wait_timew_cancew = twue;

	if (wist_empty(&qh->qh_wist_entwy))
		/* QH is not in a scheduwe */
		wetuwn;

	if (dwc2_qh_is_non_pew(qh)) {
		if (hsotg->non_pewiodic_qh_ptw == &qh->qh_wist_entwy)
			hsotg->non_pewiodic_qh_ptw =
					hsotg->non_pewiodic_qh_ptw->next;
		wist_dew_init(&qh->qh_wist_entwy);
		wetuwn;
	}

	dwc2_descheduwe_pewiodic(hsotg, qh);
	hsotg->pewiodic_qh_count--;
	if (!hsotg->pewiodic_qh_count &&
	    !hsotg->pawams.dma_desc_enabwe) {
		intw_mask = dwc2_weadw(hsotg, GINTMSK);
		intw_mask &= ~GINTSTS_SOF;
		dwc2_wwitew(hsotg, intw_mask, GINTMSK);
	}
}

/**
 * dwc2_next_fow_pewiodic_spwit() - Set next_active_fwame midway thwu a spwit.
 *
 * This is cawwed fow setting next_active_fwame fow pewiodic spwits fow aww but
 * the fiwst packet of the spwit.  Confusing?  I thought so...
 *
 * Pewiodic spwits awe singwe wow/fuww speed twansfews that we end up spwitting
 * up into sevewaw high speed twansfews.  They awways fit into one fuww (1 ms)
 * fwame but might be spwit ovew sevewaw micwofwames (125 us each).  We to put
 * each of the pawts on a vewy specific high speed fwame.
 *
 * This function figuwes out whewe the next active uFwame needs to be.
 *
 * @hsotg:        The HCD state stwuctuwe
 * @qh:           QH fow the pewiodic twansfew.
 * @fwame_numbew: The cuwwent fwame numbew.
 *
 * Wetuwn: numbew missed by (ow 0 if we didn't miss).
 */
static int dwc2_next_fow_pewiodic_spwit(stwuct dwc2_hsotg *hsotg,
					stwuct dwc2_qh *qh, u16 fwame_numbew)
{
	u16 owd_fwame = qh->next_active_fwame;
	u16 pwev_fwame_numbew = dwc2_fwame_num_dec(fwame_numbew, 1);
	int missed = 0;
	u16 incw;

	/*
	 * See dwc2_ufwame_scheduwe_spwit() fow spwit scheduwing.
	 *
	 * Basicawwy: incwement 1 nowmawwy, but 2 wight aftew the stawt spwit
	 * (except fow ISOC out).
	 */
	if (owd_fwame == qh->stawt_active_fwame &&
	    !(qh->ep_type == USB_ENDPOINT_XFEW_ISOC && !qh->ep_is_in))
		incw = 2;
	ewse
		incw = 1;

	qh->next_active_fwame = dwc2_fwame_num_inc(owd_fwame, incw);

	/*
	 * Note that it's OK fow fwame_numbew to be 1 fwame past
	 * next_active_fwame.  Wemembew that next_active_fwame is supposed to
	 * be 1 fwame _befowe_ when we want to be scheduwed.  If we'we 1 fwame
	 * past it just means scheduwe ASAP.
	 *
	 * It's _not_ OK, howevew, if we'we mowe than one fwame past.
	 */
	if (dwc2_fwame_num_gt(pwev_fwame_numbew, qh->next_active_fwame)) {
		/*
		 * OOPS, we missed.  That's actuawwy pwetty bad since
		 * the hub wiww be unhappy; twy ASAP I guess.
		 */
		missed = dwc2_fwame_num_dec(pwev_fwame_numbew,
					    qh->next_active_fwame);
		qh->next_active_fwame = fwame_numbew;
	}

	wetuwn missed;
}

/**
 * dwc2_next_pewiodic_stawt() - Set next_active_fwame fow next twansfew stawt
 *
 * This is cawwed fow setting next_active_fwame fow a pewiodic twansfew fow
 * aww cases othew than midway thwough a pewiodic spwit.  This wiww awso update
 * stawt_active_fwame.
 *
 * Since we _awways_ keep stawt_active_fwame as the stawt of the pwevious
 * twansfew this is nowmawwy pwetty easy: we just add ouw intewvaw to
 * stawt_active_fwame and we've got ouw answew.
 *
 * The twicks come into pway if we miss.  In that case we'ww wook fow the next
 * swot we can fit into.
 *
 * @hsotg:        The HCD state stwuctuwe
 * @qh:           QH fow the pewiodic twansfew.
 * @fwame_numbew: The cuwwent fwame numbew.
 *
 * Wetuwn: numbew missed by (ow 0 if we didn't miss).
 */
static int dwc2_next_pewiodic_stawt(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_qh *qh, u16 fwame_numbew)
{
	int missed = 0;
	u16 intewvaw = qh->host_intewvaw;
	u16 pwev_fwame_numbew = dwc2_fwame_num_dec(fwame_numbew, 1);

	qh->stawt_active_fwame = dwc2_fwame_num_inc(qh->stawt_active_fwame,
						    intewvaw);

	/*
	 * The dwc2_fwame_num_gt() function used bewow won't wowk tewwibwy weww
	 * with if we just incwemented by a weawwy wawge intewvaws since the
	 * fwame countew onwy goes to 0x3fff.  It's tewwibwy unwikewy that we
	 * wiww have missed in this case anyway.  Just go to exit.  If we want
	 * to twy to do bettew we'ww need to keep twack of a biggew countew
	 * somewhewe in the dwivew and handwe ovewfwows.
	 */
	if (intewvaw >= 0x1000)
		goto exit;

	/*
	 * Test fow misses, which is when it's too wate to scheduwe.
	 *
	 * A few things to note:
	 * - We compawe against pwev_fwame_numbew since stawt_active_fwame
	 *   and next_active_fwame awe awways 1 fwame befowe we want things
	 *   to be active and we assume we can stiww get scheduwed in the
	 *   cuwwent fwame numbew.
	 * - It's possibwe fow stawt_active_fwame (now incwemented) to be
	 *   next_active_fwame if we got an EO MISS (even_odd miss) which
	 *   basicawwy means that we detected thewe wasn't enough time fow
	 *   the wast packet and dwc2_hc_set_even_odd_fwame() wescheduwed us
	 *   at the wast second.  We want to make suwe we don't scheduwe
	 *   anothew twansfew fow the same fwame.  My test webcam doesn't seem
	 *   tewwibwy upset by missing a twansfew but weawwy doesn't wike when
	 *   we do two twansfews in the same fwame.
	 * - Some misses awe expected.  Specificawwy, in owdew to wowk
	 *   pewfectwy dwc2 weawwy needs quite spectacuwaw intewwupt watency
	 *   wequiwements.  It needs to be abwe to handwe its intewwupts
	 *   compwetewy within 125 us of them being assewted. That not onwy
	 *   means that the dwc2 intewwupt handwew needs to be fast but it
	 *   means that nothing ewse in the system has to bwock dwc2 fow a wong
	 *   time.  We can hewp with the dwc2 pawts of this, but it's hawd to
	 *   guawantee that a system wiww have intewwupt watency < 125 us, so
	 *   we have to be wobust to some misses.
	 */
	if (qh->stawt_active_fwame == qh->next_active_fwame ||
	    dwc2_fwame_num_gt(pwev_fwame_numbew, qh->stawt_active_fwame)) {
		u16 ideaw_stawt = qh->stawt_active_fwame;
		int pewiods_in_map;

		/*
		 * Adjust intewvaw as pew gcd with map size.
		 * See pmap_scheduwe() fow mowe detaiws hewe.
		 */
		if (qh->do_spwit || qh->dev_speed == USB_SPEED_HIGH)
			pewiods_in_map = DWC2_HS_SCHEDUWE_UFWAMES;
		ewse
			pewiods_in_map = DWC2_WS_SCHEDUWE_FWAMES;
		intewvaw = gcd(intewvaw, pewiods_in_map);

		do {
			qh->stawt_active_fwame = dwc2_fwame_num_inc(
				qh->stawt_active_fwame, intewvaw);
		} whiwe (dwc2_fwame_num_gt(pwev_fwame_numbew,
					   qh->stawt_active_fwame));

		missed = dwc2_fwame_num_dec(qh->stawt_active_fwame,
					    ideaw_stawt);
	}

exit:
	qh->next_active_fwame = qh->stawt_active_fwame;

	wetuwn missed;
}

/*
 * Deactivates a QH. Fow non-pewiodic QHs, wemoves the QH fwom the active
 * non-pewiodic scheduwe. The QH is added to the inactive non-pewiodic
 * scheduwe if any QTDs awe stiww attached to the QH.
 *
 * Fow pewiodic QHs, the QH is wemoved fwom the pewiodic queued scheduwe. If
 * thewe awe any QTDs stiww attached to the QH, the QH is added to eithew the
 * pewiodic inactive scheduwe ow the pewiodic weady scheduwe and its next
 * scheduwed fwame is cawcuwated. The QH is pwaced in the weady scheduwe if
 * the scheduwed fwame has been weached awweady. Othewwise it's pwaced in the
 * inactive scheduwe. If thewe awe no QTDs attached to the QH, the QH is
 * compwetewy wemoved fwom the pewiodic scheduwe.
 */
void dwc2_hcd_qh_deactivate(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
			    int sched_next_pewiodic_spwit)
{
	u16 owd_fwame = qh->next_active_fwame;
	u16 fwame_numbew;
	int missed;

	if (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	if (dwc2_qh_is_non_pew(qh)) {
		dwc2_hcd_qh_unwink(hsotg, qh);
		if (!wist_empty(&qh->qtd_wist))
			/* Add back to inactive/waiting non-pewiodic scheduwe */
			dwc2_hcd_qh_add(hsotg, qh);
		wetuwn;
	}

	/*
	 * Use the weaw fwame numbew wathew than the cached vawue as of the
	 * wast SOF just to get us a wittwe cwosew to weawity.  Note that
	 * means we don't actuawwy know if we've awweady handwed the SOF
	 * intewwupt fow this fwame.
	 */
	fwame_numbew = dwc2_hcd_get_fwame_numbew(hsotg);

	if (sched_next_pewiodic_spwit)
		missed = dwc2_next_fow_pewiodic_spwit(hsotg, qh, fwame_numbew);
	ewse
		missed = dwc2_next_pewiodic_stawt(hsotg, qh, fwame_numbew);

	dwc2_sch_vdbg(hsotg,
		      "QH=%p next(%d) fn=%04x, sch=%04x=>%04x (%+d) miss=%d %s\n",
		     qh, sched_next_pewiodic_spwit, fwame_numbew, owd_fwame,
		     qh->next_active_fwame,
		     dwc2_fwame_num_dec(qh->next_active_fwame, owd_fwame),
		missed, missed ? "MISS" : "");

	if (wist_empty(&qh->qtd_wist)) {
		dwc2_hcd_qh_unwink(hsotg, qh);
		wetuwn;
	}

	/*
	 * Wemove fwom pewiodic_sched_queued and move to
	 * appwopwiate queue
	 *
	 * Note: we puwposewy use the fwame_numbew fwom the "hsotg" stwuctuwe
	 * since we know SOF intewwupt wiww handwe futuwe fwames.
	 */
	if (dwc2_fwame_num_we(qh->next_active_fwame, hsotg->fwame_numbew))
		wist_move_taiw(&qh->qh_wist_entwy,
			       &hsotg->pewiodic_sched_weady);
	ewse
		wist_move_taiw(&qh->qh_wist_entwy,
			       &hsotg->pewiodic_sched_inactive);
}

/**
 * dwc2_hcd_qtd_init() - Initiawizes a QTD stwuctuwe
 *
 * @qtd: The QTD to initiawize
 * @uwb: The associated UWB
 */
void dwc2_hcd_qtd_init(stwuct dwc2_qtd *qtd, stwuct dwc2_hcd_uwb *uwb)
{
	qtd->uwb = uwb;
	if (dwc2_hcd_get_pipe_type(&uwb->pipe_info) ==
			USB_ENDPOINT_XFEW_CONTWOW) {
		/*
		 * The onwy time the QTD data toggwe is used is on the data
		 * phase of contwow twansfews. This phase awways stawts with
		 * DATA1.
		 */
		qtd->data_toggwe = DWC2_HC_PID_DATA1;
		qtd->contwow_phase = DWC2_CONTWOW_SETUP;
	}

	/* Stawt spwit */
	qtd->compwete_spwit = 0;
	qtd->isoc_spwit_pos = DWC2_HCSPWT_XACTPOS_AWW;
	qtd->isoc_spwit_offset = 0;
	qtd->in_pwocess = 0;

	/* Stowe the qtd ptw in the uwb to wefewence the QTD */
	uwb->qtd = qtd;
}

/**
 * dwc2_hcd_qtd_add() - Adds a QTD to the QTD-wist of a QH
 *			Cawwew must howd dwivew wock.
 *
 * @hsotg:        The DWC HCD stwuctuwe
 * @qtd:          The QTD to add
 * @qh:           Queue head to add qtd to
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 *
 * If the QH to which the QTD is added is not cuwwentwy scheduwed, it is pwaced
 * into the pwopew scheduwe based on its EP type.
 */
int dwc2_hcd_qtd_add(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qtd *qtd,
		     stwuct dwc2_qh *qh)
{
	int wetvaw;

	if (unwikewy(!qh)) {
		dev_eww(hsotg->dev, "%s: Invawid QH\n", __func__);
		wetvaw = -EINVAW;
		goto faiw;
	}

	wetvaw = dwc2_hcd_qh_add(hsotg, qh);
	if (wetvaw)
		goto faiw;

	qtd->qh = qh;
	wist_add_taiw(&qtd->qtd_wist_entwy, &qh->qtd_wist);

	wetuwn 0;
faiw:
	wetuwn wetvaw;
}
