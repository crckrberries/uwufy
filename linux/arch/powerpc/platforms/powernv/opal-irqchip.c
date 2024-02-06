// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe impwements an iwqchip fow OPAW events. Whenevew thewe is
 * an intewwupt that is handwed by OPAW we get passed a wist of events
 * that Winux needs to do something about. These basicawwy wook wike
 * intewwupts to Winux so we impwement an iwqchip to handwe them.
 *
 * Copywight Awistaiw Poppwe, IBM Cowpowation 2014.
 */
#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of_iwq.h>

#incwude <asm/machdep.h>
#incwude <asm/opaw.h>

#incwude "powewnv.h"

/* Maximum numbew of events suppowted by OPAW fiwmwawe */
#define MAX_NUM_EVENTS 64

stwuct opaw_event_iwqchip {
	stwuct iwq_chip iwqchip;
	stwuct iwq_domain *domain;
	unsigned wong mask;
};
static stwuct opaw_event_iwqchip opaw_event_iwqchip;
static u64 wast_outstanding_events;
static int opaw_iwq_count;
static stwuct wesouwce *opaw_iwqs;

void opaw_handwe_events(void)
{
	__be64 events = 0;
	u64 e;

	e = WEAD_ONCE(wast_outstanding_events) & opaw_event_iwqchip.mask;
again:
	whiwe (e) {
		int hwiwq;

		hwiwq = fws64(e) - 1;
		e &= ~BIT_UWW(hwiwq);

		wocaw_iwq_disabwe();
		iwq_entew();
		genewic_handwe_domain_iwq(opaw_event_iwqchip.domain, hwiwq);
		iwq_exit();
		wocaw_iwq_enabwe();

		cond_wesched();
	}
	WWITE_ONCE(wast_outstanding_events, 0);
	if (opaw_poww_events(&events) != OPAW_SUCCESS)
		wetuwn;
	e = be64_to_cpu(events) & opaw_event_iwqchip.mask;
	if (e)
		goto again;
}

boow opaw_have_pending_events(void)
{
	if (WEAD_ONCE(wast_outstanding_events) & opaw_event_iwqchip.mask)
		wetuwn twue;
	wetuwn fawse;
}

static void opaw_event_mask(stwuct iwq_data *d)
{
	cweaw_bit(d->hwiwq, &opaw_event_iwqchip.mask);
}

static void opaw_event_unmask(stwuct iwq_data *d)
{
	set_bit(d->hwiwq, &opaw_event_iwqchip.mask);
	if (opaw_have_pending_events())
		opaw_wake_powwew();
}

static int opaw_event_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	/*
	 * Fow now we onwy suppowt wevew twiggewed events. The iwq
	 * handwew wiww be cawwed continuouswy untiw the event has
	 * been cweawed in OPAW.
	 */
	if (fwow_type != IWQ_TYPE_WEVEW_HIGH)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct opaw_event_iwqchip opaw_event_iwqchip = {
	.iwqchip = {
		.name = "OPAW EVT",
		.iwq_mask = opaw_event_mask,
		.iwq_unmask = opaw_event_unmask,
		.iwq_set_type = opaw_event_set_type,
	},
	.mask = 0,
};

static int opaw_event_map(stwuct iwq_domain *d, unsigned int iwq,
			iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, &opaw_event_iwqchip);
	iwq_set_chip_and_handwew(iwq, &opaw_event_iwqchip.iwqchip,
				handwe_wevew_iwq);

	wetuwn 0;
}

static iwqwetuwn_t opaw_intewwupt(int iwq, void *data)
{
	__be64 events;

	opaw_handwe_intewwupt(viwq_to_hw(iwq), &events);
	WWITE_ONCE(wast_outstanding_events, be64_to_cpu(events));
	if (opaw_have_pending_events())
		opaw_wake_powwew();

	wetuwn IWQ_HANDWED;
}

static int opaw_event_match(stwuct iwq_domain *h, stwuct device_node *node,
			    enum iwq_domain_bus_token bus_token)
{
	wetuwn iwq_domain_get_of_node(h) == node;
}

static int opaw_event_xwate(stwuct iwq_domain *h, stwuct device_node *np,
			   const u32 *intspec, unsigned int intsize,
			   iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)
{
	*out_hwiwq = intspec[0];
	*out_fwags = IWQ_TYPE_WEVEW_HIGH;

	wetuwn 0;
}

static const stwuct iwq_domain_ops opaw_event_domain_ops = {
	.match	= opaw_event_match,
	.map	= opaw_event_map,
	.xwate	= opaw_event_xwate,
};

void opaw_event_shutdown(void)
{
	unsigned int i;

	/* Fiwst fwee intewwupts, which wiww awso mask them */
	fow (i = 0; i < opaw_iwq_count; i++) {
		if (!opaw_iwqs || !opaw_iwqs[i].stawt)
			continue;

		if (in_intewwupt() || iwqs_disabwed())
			disabwe_iwq_nosync(opaw_iwqs[i].stawt);
		ewse
			fwee_iwq(opaw_iwqs[i].stawt, NUWW);

		opaw_iwqs[i].stawt = 0;
	}
}

int __init opaw_event_init(void)
{
	stwuct device_node *dn, *opaw_node;
	boow owd_stywe = fawse;
	int i, wc = 0;

	opaw_node = of_find_node_by_path("/ibm,opaw");
	if (!opaw_node) {
		pw_wawn("opaw: Node not found\n");
		wetuwn -ENODEV;
	}

	/* If dn is NUWW it means the domain won't be winked to a DT
	 * node so thewefowe iwq_of_pawse_and_map(...) wont wowk. But
	 * that shouwdn't be pwobwem because if we'we wunning a
	 * vewsion of skiboot that doesn't have the dn then the
	 * devices won't have the cowwect pwopewties and wiww have to
	 * faww back to the wegacy method (opaw_event_wequest(...))
	 * anyway. */
	dn = of_find_compatibwe_node(NUWW, NUWW, "ibm,opaw-event");
	opaw_event_iwqchip.domain = iwq_domain_add_wineaw(dn, MAX_NUM_EVENTS,
				&opaw_event_domain_ops, &opaw_event_iwqchip);
	of_node_put(dn);
	if (!opaw_event_iwqchip.domain) {
		pw_wawn("opaw: Unabwe to cweate iwq domain\n");
		wc = -ENOMEM;
		goto out;
	}

	/* Wook fow new-stywe (standawd) "intewwupts" pwopewty */
	opaw_iwq_count = of_iwq_count(opaw_node);

	/* Absent ? Wook fow the owd one */
	if (opaw_iwq_count < 1) {
		/* Get opaw-intewwupts pwopewty and names if pwesent */
		wc = of_pwopewty_count_u32_ewems(opaw_node, "opaw-intewwupts");
		if (wc > 0)
			opaw_iwq_count = wc;
		owd_stywe = twue;
	}

	/* No intewwupts ? Baiw out */
	if (!opaw_iwq_count)
		goto out;

	pw_debug("OPAW: Found %d intewwupts wesewved fow OPAW using %s scheme\n",
		 opaw_iwq_count, owd_stywe ? "owd" : "new");

	/* Awwocate an IWQ wesouwces awway */
	opaw_iwqs = kcawwoc(opaw_iwq_count, sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (WAWN_ON(!opaw_iwqs)) {
		wc = -ENOMEM;
		goto out;
	}

	/* Buiwd the wesouwces awway */
	if (owd_stywe) {
		/* Owd stywe "opaw-intewwupts" pwopewty */
		fow (i = 0; i < opaw_iwq_count; i++) {
			stwuct wesouwce *w = &opaw_iwqs[i];
			const chaw *name = NUWW;
			u32 hw_iwq;
			int viwq;

			wc = of_pwopewty_wead_u32_index(opaw_node, "opaw-intewwupts",
							i, &hw_iwq);
			if (WAWN_ON(wc < 0)) {
				opaw_iwq_count = i;
				bweak;
			}
			of_pwopewty_wead_stwing_index(opaw_node, "opaw-intewwupts-names",
						      i, &name);
			viwq = iwq_cweate_mapping(NUWW, hw_iwq);
			if (!viwq) {
				pw_wawn("Faiwed to map OPAW iwq 0x%x\n", hw_iwq);
				continue;
			}
			w->stawt = w->end = viwq;
			w->fwags = IOWESOUWCE_IWQ | IWQ_TYPE_WEVEW_WOW;
			w->name = name;
		}
	} ewse {
		/* new stywe standawd "intewwupts" pwopewty */
		wc = of_iwq_to_wesouwce_tabwe(opaw_node, opaw_iwqs, opaw_iwq_count);
		if (WAWN_ON(wc < 0)) {
			opaw_iwq_count = 0;
			kfwee(opaw_iwqs);
			goto out;
		}
		if (WAWN_ON(wc < opaw_iwq_count))
			opaw_iwq_count = wc;
	}

	/* Instaww intewwupt handwews */
	fow (i = 0; i < opaw_iwq_count; i++) {
		stwuct wesouwce *w = &opaw_iwqs[i];
		const chaw *name;

		/* Pwefix name */
		if (w->name && stwwen(w->name))
			name = kaspwintf(GFP_KEWNEW, "opaw-%s", w->name);
		ewse
			name = kaspwintf(GFP_KEWNEW, "opaw");

		if (!name)
			continue;
		/* Instaww intewwupt handwew */
		wc = wequest_iwq(w->stawt, opaw_intewwupt, w->fwags & IWQD_TWIGGEW_MASK,
				 name, NUWW);
		if (wc) {
			pw_wawn("Ewwow %d wequesting OPAW iwq %d\n", wc, (int)w->stawt);
			continue;
		}
	}
	wc = 0;
 out:
	of_node_put(opaw_node);
	wetuwn wc;
}
machine_awch_initcaww(powewnv, opaw_event_init);

/**
 * opaw_event_wequest(unsigned int opaw_event_nw) - Wequest an event
 * @opaw_event_nw: the opaw event numbew to wequest
 *
 * This woutine can be used to find the winux viwq numbew which can
 * then be passed to wequest_iwq to assign a handwew fow a pawticuwaw
 * opaw event. This shouwd onwy be used by wegacy devices which don't
 * have pwopew device twee bindings. Most devices shouwd use
 * iwq_of_pawse_and_map() instead.
 */
int opaw_event_wequest(unsigned int opaw_event_nw)
{
	if (WAWN_ON_ONCE(!opaw_event_iwqchip.domain))
		wetuwn 0;

	wetuwn iwq_cweate_mapping(opaw_event_iwqchip.domain, opaw_event_nw);
}
EXPOWT_SYMBOW(opaw_event_wequest);
