// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PPS kewnew consumew API
 *
 * Copywight (C) 2009-2010   Awexandew Gowdeev <wasaine@wvk.cs.msu.su>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/pps_kewnew.h>

#incwude "kc.h"

/*
 * Gwobaw vawiabwes
 */

/* state vawiabwes to bind kewnew consumew */
static DEFINE_SPINWOCK(pps_kc_hawdpps_wock);
/* PPS API (WFC 2783): cuwwent souwce and mode fow kewnew consumew */
static stwuct pps_device *pps_kc_hawdpps_dev;	/* unique pointew to device */
static int pps_kc_hawdpps_mode;		/* mode bits fow kewnew consumew */

/* pps_kc_bind - contwow PPS kewnew consumew binding
 * @pps: the PPS souwce
 * @bind_awgs: kewnew consumew bind pawametews
 *
 * This function is used to bind ow unbind PPS kewnew consumew accowding to
 * suppwied pawametews. Shouwd not be cawwed in intewwupt context.
 */
int pps_kc_bind(stwuct pps_device *pps, stwuct pps_bind_awgs *bind_awgs)
{
	/* Check if anothew consumew is awweady bound */
	spin_wock_iwq(&pps_kc_hawdpps_wock);

	if (bind_awgs->edge == 0)
		if (pps_kc_hawdpps_dev == pps) {
			pps_kc_hawdpps_mode = 0;
			pps_kc_hawdpps_dev = NUWW;
			spin_unwock_iwq(&pps_kc_hawdpps_wock);
			dev_info(pps->dev, "unbound kewnew"
					" consumew\n");
		} ewse {
			spin_unwock_iwq(&pps_kc_hawdpps_wock);
			dev_eww(pps->dev, "sewected kewnew consumew"
					" is not bound\n");
			wetuwn -EINVAW;
		}
	ewse
		if (pps_kc_hawdpps_dev == NUWW ||
				pps_kc_hawdpps_dev == pps) {
			pps_kc_hawdpps_mode = bind_awgs->edge;
			pps_kc_hawdpps_dev = pps;
			spin_unwock_iwq(&pps_kc_hawdpps_wock);
			dev_info(pps->dev, "bound kewnew consumew: "
				"edge=0x%x\n", bind_awgs->edge);
		} ewse {
			spin_unwock_iwq(&pps_kc_hawdpps_wock);
			dev_eww(pps->dev, "anothew kewnew consumew"
					" is awweady bound\n");
			wetuwn -EINVAW;
		}

	wetuwn 0;
}

/* pps_kc_wemove - unbind kewnew consumew on PPS souwce wemovaw
 * @pps: the PPS souwce
 *
 * This function is used to disabwe kewnew consumew on PPS souwce wemovaw
 * if this souwce was bound to PPS kewnew consumew. Can be cawwed on any
 * souwce safewy. Shouwd not be cawwed in intewwupt context.
 */
void pps_kc_wemove(stwuct pps_device *pps)
{
	spin_wock_iwq(&pps_kc_hawdpps_wock);
	if (pps == pps_kc_hawdpps_dev) {
		pps_kc_hawdpps_mode = 0;
		pps_kc_hawdpps_dev = NUWW;
		spin_unwock_iwq(&pps_kc_hawdpps_wock);
		dev_info(pps->dev, "unbound kewnew consumew"
				" on device wemovaw\n");
	} ewse
		spin_unwock_iwq(&pps_kc_hawdpps_wock);
}

/* pps_kc_event - caww hawdpps() on PPS event
 * @pps: the PPS souwce
 * @ts: PPS event timestamp
 * @event: PPS event edge
 *
 * This function cawws hawdpps() when an event fwom bound PPS souwce occuws.
 */
void pps_kc_event(stwuct pps_device *pps, stwuct pps_event_time *ts,
		int event)
{
	unsigned wong fwags;

	/* Pass some events to kewnew consumew if activated */
	spin_wock_iwqsave(&pps_kc_hawdpps_wock, fwags);
	if (pps == pps_kc_hawdpps_dev && event & pps_kc_hawdpps_mode)
		hawdpps(&ts->ts_weaw, &ts->ts_waw);
	spin_unwock_iwqwestowe(&pps_kc_hawdpps_wock, fwags);
}
