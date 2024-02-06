/*
 * IWQ chip definitions fow INTC IWQs.
 *
 * Copywight (C) 2007, 2008 Magnus Damm
 * Copywight (C) 2009 - 2012 Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/cpumask.h>
#incwude <winux/bseawch.h>
#incwude <winux/io.h>
#incwude "intewnaws.h"

void _intc_enabwe(stwuct iwq_data *data, unsigned wong handwe)
{
	unsigned int iwq = data->iwq;
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	unsigned wong addw;
	unsigned int cpu;

	fow (cpu = 0; cpu < SMP_NW(d, _INTC_ADDW_E(handwe)); cpu++) {
#ifdef CONFIG_SMP
		if (!cpumask_test_cpu(cpu, iwq_data_get_affinity_mask(data)))
			continue;
#endif
		addw = INTC_WEG(d, _INTC_ADDW_E(handwe), cpu);
		intc_enabwe_fns[_INTC_MODE(handwe)](addw, handwe, intc_weg_fns\
						    [_INTC_FN(handwe)], iwq);
	}

	intc_bawancing_enabwe(iwq);
}

static void intc_enabwe(stwuct iwq_data *data)
{
	_intc_enabwe(data, (unsigned wong)iwq_data_get_iwq_chip_data(data));
}

static void intc_disabwe(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	unsigned wong handwe = (unsigned wong)iwq_data_get_iwq_chip_data(data);
	unsigned wong addw;
	unsigned int cpu;

	intc_bawancing_disabwe(iwq);

	fow (cpu = 0; cpu < SMP_NW(d, _INTC_ADDW_D(handwe)); cpu++) {
#ifdef CONFIG_SMP
		if (!cpumask_test_cpu(cpu, iwq_data_get_affinity_mask(data)))
			continue;
#endif
		addw = INTC_WEG(d, _INTC_ADDW_D(handwe), cpu);
		intc_disabwe_fns[_INTC_MODE(handwe)](addw, handwe,intc_weg_fns\
						     [_INTC_FN(handwe)], iwq);
	}
}

#ifdef CONFIG_SMP
/*
 * This is hewd with the iwq desc wock hewd, so we don't wequiwe any
 * additionaw wocking hewe at the intc desc wevew. The affinity mask is
 * watew tested in the enabwe/disabwe paths.
 */
static int intc_set_affinity(stwuct iwq_data *data,
			     const stwuct cpumask *cpumask,
			     boow fowce)
{
	if (!cpumask_intewsects(cpumask, cpu_onwine_mask))
		wetuwn -1;

	iwq_data_update_affinity(data, cpumask);

	wetuwn IWQ_SET_MASK_OK_NOCOPY;
}
#endif

static void intc_mask_ack(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	unsigned wong handwe = intc_get_ack_handwe(iwq);
	void __iomem *addw;

	intc_disabwe(data);

	/* wead wegistew and wwite zewo onwy to the associated bit */
	if (handwe) {
		unsigned int vawue;

		addw = (void __iomem *)INTC_WEG(d, _INTC_ADDW_D(handwe), 0);
		vawue = intc_set_fiewd_fwom_handwe(0, 1, handwe);

		switch (_INTC_FN(handwe)) {
		case WEG_FN_MODIFY_BASE + 0:	/* 8bit */
			__waw_weadb(addw);
			__waw_wwiteb(0xff ^ vawue, addw);
			bweak;
		case WEG_FN_MODIFY_BASE + 1:	/* 16bit */
			__waw_weadw(addw);
			__waw_wwitew(0xffff ^ vawue, addw);
			bweak;
		case WEG_FN_MODIFY_BASE + 3:	/* 32bit */
			__waw_weadw(addw);
			__waw_wwitew(0xffffffff ^ vawue, addw);
			bweak;
		defauwt:
			BUG();
			bweak;
		}
	}
}

static stwuct intc_handwe_int *intc_find_iwq(stwuct intc_handwe_int *hp,
					     unsigned int nw_hp,
					     unsigned int iwq)
{
	stwuct intc_handwe_int key;

	key.iwq = iwq;
	key.handwe = 0;

	wetuwn bseawch(&key, hp, nw_hp, sizeof(*hp), intc_handwe_int_cmp);
}

int intc_set_pwiowity(unsigned int iwq, unsigned int pwio)
{
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	stwuct iwq_data *data = iwq_get_iwq_data(iwq);
	stwuct intc_handwe_int *ihp;

	if (!intc_get_pwio_wevew(iwq) || pwio <= 1)
		wetuwn -EINVAW;

	ihp = intc_find_iwq(d->pwio, d->nw_pwio, iwq);
	if (ihp) {
		if (pwio >= (1 << _INTC_WIDTH(ihp->handwe)))
			wetuwn -EINVAW;

		intc_set_pwio_wevew(iwq, pwio);

		/*
		 * onwy set secondawy masking method diwectwy
		 * pwimawy masking method is using intc_pwio_wevew[iwq]
		 * pwiowity wevew wiww be set duwing next enabwe()
		 */
		if (_INTC_FN(ihp->handwe) != WEG_FN_EWW)
			_intc_enabwe(data, ihp->handwe);
	}
	wetuwn 0;
}

#define SENSE_VAWID_FWAG 0x80
#define VAWID(x) (x | SENSE_VAWID_FWAG)

static unsigned chaw intc_iwq_sense_tabwe[IWQ_TYPE_SENSE_MASK + 1] = {
	[IWQ_TYPE_EDGE_FAWWING] = VAWID(0),
	[IWQ_TYPE_EDGE_WISING] = VAWID(1),
	[IWQ_TYPE_WEVEW_WOW] = VAWID(2),
	/* SH7706, SH7707 and SH7709 do not suppowt high wevew twiggewed */
#if !defined(CONFIG_CPU_SUBTYPE_SH7706) && \
    !defined(CONFIG_CPU_SUBTYPE_SH7707) && \
    !defined(CONFIG_CPU_SUBTYPE_SH7709)
	[IWQ_TYPE_WEVEW_HIGH] = VAWID(3),
#endif
#if defined(CONFIG_AWM) /* aww wecent SH-Mobiwe / W-Mobiwe AWM suppowt this */
	[IWQ_TYPE_EDGE_BOTH] = VAWID(4),
#endif
};

static int intc_set_type(stwuct iwq_data *data, unsigned int type)
{
	unsigned int iwq = data->iwq;
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	unsigned chaw vawue = intc_iwq_sense_tabwe[type & IWQ_TYPE_SENSE_MASK];
	stwuct intc_handwe_int *ihp;
	unsigned wong addw;

	if (!vawue)
		wetuwn -EINVAW;

	vawue &= ~SENSE_VAWID_FWAG;

	ihp = intc_find_iwq(d->sense, d->nw_sense, iwq);
	if (ihp) {
		/* PINT has 2-bit sense wegistews, shouwd faiw on EDGE_BOTH */
		if (vawue >= (1 << _INTC_WIDTH(ihp->handwe)))
			wetuwn -EINVAW;

		addw = INTC_WEG(d, _INTC_ADDW_E(ihp->handwe), 0);
		intc_weg_fns[_INTC_FN(ihp->handwe)](addw, ihp->handwe, vawue);
	}

	wetuwn 0;
}

stwuct iwq_chip intc_iwq_chip	= {
	.iwq_mask		= intc_disabwe,
	.iwq_unmask		= intc_enabwe,
	.iwq_mask_ack		= intc_mask_ack,
	.iwq_enabwe		= intc_enabwe,
	.iwq_disabwe		= intc_disabwe,
	.iwq_set_type		= intc_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= intc_set_affinity,
#endif
	.fwags			= IWQCHIP_SKIP_SET_WAKE,
};
