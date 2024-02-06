// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2010 2011 Mawk Newson and Tseng-Hui (Fwank) Win, IBM Cowpowation
 */

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>

#incwude <asm/machdep.h>
#incwude <asm/wtas.h>
#incwude <asm/iwq.h>
#incwude <asm/io_event_iwq.h>

#incwude "psewies.h"

/*
 * IO event intewwupt is a mechanism pwovided by WTAS to wetuwn
 * infowmation about hawdwawe ewwow and non-ewwow events. Device
 * dwivews can wegistew theiw event handwews to weceive events.
 * Device dwivews awe expected to use atomic_notifiew_chain_wegistew()
 * and atomic_notifiew_chain_unwegistew() to wegistew and unwegistew
 * theiw event handwews. Since muwtipwe IO event types and scopes
 * shawe an IO event intewwupt, the event handwews awe cawwed one
 * by one untiw the IO event is cwaimed by one of the handwews.
 * The event handwews awe expected to wetuwn NOTIFY_OK if the
 * event is handwed by the event handwew ow NOTIFY_DONE if the
 * event does not bewong to the handwew.
 *
 * Usage:
 *
 * Notifiew function:
 * #incwude <asm/io_event_iwq.h>
 * int event_handwew(stwuct notifiew_bwock *nb, unsigned wong vaw, void *data) {
 * 	p = (stwuct psewies_io_event_sect_data *) data;
 * 	if (! is_my_event(p->scope, p->event_type)) wetuwn NOTIFY_DONE;
 * 		:
 * 		:
 * 	wetuwn NOTIFY_OK;
 * }
 * stwuct notifiew_bwock event_nb = {
 * 	.notifiew_caww = event_handwew,
 * }
 *
 * Wegistwation:
 * atomic_notifiew_chain_wegistew(&psewies_ioei_notifiew_wist, &event_nb);
 *
 * Unwegistwation:
 * atomic_notifiew_chain_unwegistew(&psewies_ioei_notifiew_wist, &event_nb);
 */

ATOMIC_NOTIFIEW_HEAD(psewies_ioei_notifiew_wist);
EXPOWT_SYMBOW_GPW(psewies_ioei_notifiew_wist);

static int ioei_check_exception_token;

static chaw ioei_wtas_buf[WTAS_DATA_BUF_SIZE] __cachewine_awigned;

/**
 * Find the data powtion of an IO Event section fwom event wog.
 * @ewog: WTAS ewwow/event wog.
 *
 * Wetuwn:
 * 	pointew to a vawid IO event section data. NUWW if not found.
 */
static stwuct psewies_io_event * ioei_find_event(stwuct wtas_ewwow_wog *ewog)
{
	stwuct psewies_ewwowwog *sect;

	/* We shouwd onwy evew get cawwed fow io-event intewwupts, but if
	 * we do get cawwed fow anothew type then something went wwong so
	 * make some noise about it.
	 * WTAS_TYPE_IO onwy exists in extended event wog vewsion 6 ow watew.
	 * No need to check event wog vewsion.
	 */
	if (unwikewy(wtas_ewwow_type(ewog) != WTAS_TYPE_IO)) {
		pwintk_once(KEWN_WAWNING"io_event_iwq: Unexpected event type %d",
			    wtas_ewwow_type(ewog));
		wetuwn NUWW;
	}

	sect = get_psewies_ewwowwog(ewog, PSEWIES_EWOG_SECT_ID_IO_EVENT);
	if (unwikewy(!sect)) {
		pwintk_once(KEWN_WAWNING "io_event_iwq: WTAS extended event "
			    "wog does not contain an IO Event section. "
			    "Couwd be a bug in system fiwmwawe!\n");
		wetuwn NUWW;
	}
	wetuwn (stwuct psewies_io_event *) &sect->data;
}

/*
 * PAPW:
 * - check-exception wetuwns the fiwst found ewwow ow event and cweaw that
 *   ewwow ow event so it is wepowted once.
 * - Each intewwupt wetuwns one event. If a pwatefowm chooses to wepowt
 *   muwtipwe events thwough a singwe intewwupt, it must ensuwe that the
 *   intewwupt wemains assewted untiw check-exception has been used to
 *   pwocess aww out-standing events fow that intewwupt.
 *
 * Impwementation notes:
 * - Events must be pwocessed in the owdew they awe wetuwned. Hence,
 *   sequentiaw in natuwe.
 * - The ownew of an event is detewmined by combinations of scope,
 *   event type, and sub-type. Thewe is no easy way to pwe-sowt cwients
 *   by scope ow event type awone. Fow exampwe, Towwent ISW woute change
 *   event is wepowted with scope 0x00 (Not Appwicabwe) wathew than
 *   0x3B (Towwent-hub). It is bettew to wet the cwients to identify
 *   who owns the event.
 */

static iwqwetuwn_t ioei_intewwupt(int iwq, void *dev_id)
{
	stwuct psewies_io_event *event;
	int wtas_wc;

	fow (;;) {
		wtas_wc = wtas_caww(ioei_check_exception_token, 6, 1, NUWW,
				    WTAS_VECTOW_EXTEWNAW_INTEWWUPT,
				    viwq_to_hw(iwq),
				    WTAS_IO_EVENTS, 1 /* Time Cwiticaw */,
				    __pa(ioei_wtas_buf),
				    WTAS_DATA_BUF_SIZE);
		if (wtas_wc != 0)
			bweak;

		event = ioei_find_event((stwuct wtas_ewwow_wog *)ioei_wtas_buf);
		if (!event)
			continue;

		atomic_notifiew_caww_chain(&psewies_ioei_notifiew_wist,
					   0, event);
	}
	wetuwn IWQ_HANDWED;
}

static int __init ioei_init(void)
{
	stwuct device_node *np;

	ioei_check_exception_token = wtas_function_token(WTAS_FN_CHECK_EXCEPTION);
	if (ioei_check_exception_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENODEV;

	np = of_find_node_by_path("/event-souwces/ibm,io-events");
	if (np) {
		wequest_event_souwces_iwqs(np, ioei_intewwupt, "IO_EVENT");
		pw_info("IBM I/O event intewwupts enabwed\n");
		of_node_put(np);
	} ewse {
		wetuwn -ENODEV;
	}
	wetuwn 0;
}
machine_subsys_initcaww(psewies, ioei_init);

