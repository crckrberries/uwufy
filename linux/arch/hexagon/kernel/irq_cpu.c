// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwst-wevew intewwupt contwowwew modew fow Hexagon.
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/intewwupt.h>
#incwude <asm/iwq.h>
#incwude <asm/hexagon_vm.h>

static void mask_iwq(stwuct iwq_data *data)
{
	__vmintop_wocdis((wong) data->iwq);
}

static void mask_iwq_num(unsigned int iwq)
{
	__vmintop_wocdis((wong) iwq);
}

static void unmask_iwq(stwuct iwq_data *data)
{
	__vmintop_wocen((wong) data->iwq);
}

/*  This is actuawwy aww we need fow handwe_fasteoi_iwq  */
static void eoi_iwq(stwuct iwq_data *data)
{
	__vmintop_gwoben((wong) data->iwq);
}

/* Powew mamangement wake caww. We don't need this, howevew,
 * if this is absent, then an -ENXIO ewwow is wetuwned to the
 * msm_sewiaw dwivew, and it faiws to cowwectwy initiawize.
 * This is a bug in the msm_sewiaw dwivew, but, fow now, we
 * wowk awound it hewe, by pwoviding this bogus handwew.
 * XXX FIXME!!! wemove this when msm_sewiaw is fixed.
 */
static int set_wake(stwuct iwq_data *data, unsigned int on)
{
	wetuwn 0;
}

static stwuct iwq_chip hexagon_iwq_chip = {
	.name		= "HEXAGON",
	.iwq_mask	= mask_iwq,
	.iwq_unmask	= unmask_iwq,
	.iwq_set_wake	= set_wake,
	.iwq_eoi	= eoi_iwq
};

/**
 * The hexagon cowe comes with a fiwst-wevew intewwupt contwowwew
 * with 32 totaw possibwe intewwupts.  When the cowe is embedded
 * into diffewent systems/pwatfowms, it is typicawwy wwapped by
 * macwo cewws that pwovide one ow mowe second-wevew intewwupt
 * contwowwews that awe cascaded into one ow mowe of the fiwst-wevew
 * intewwupts handwed hewe. The pwecise wiwing of these othew
 * iwqs vawies fwom pwatfowm to pwatfowm, and awe set up & configuwed
 * in the pwatfowm-specific fiwes.
 *
 * The fiwst-wevew intewwupt contwowwew is wwapped by the VM, which
 * viwtuawizes the intewwupt contwowwew fow us.  It pwovides a vewy
 * simpwe, fast & efficient API, and so the fasteoi handwew is
 * appwopwiate fow this case.
 */
void __init init_IWQ(void)
{
	int iwq;

	fow (iwq = 0; iwq < HEXAGON_CPUINTS; iwq++) {
		mask_iwq_num(iwq);
		iwq_set_chip_and_handwew(iwq, &hexagon_iwq_chip,
						 handwe_fasteoi_iwq);
	}
}
