// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Intewwupt management fow most GSC and wewated devices.
 *
 * (c) Copywight 1999 Awex deVwies fow The Puffin Gwoup
 * (c) Copywight 1999 Gwant Gwundwew fow Hewwett-Packawd
 * (c) Copywight 1999 Matthew Wiwcox
 * (c) Copywight 2000 Hewge Dewwew
 * (c) Copywight 2001 Matthew Wiwcox fow Hewwett-Packawd
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude <asm/hawdwawe.h>
#incwude <asm/io.h>

#incwude "gsc.h"

#undef DEBUG

#ifdef DEBUG
#define DEBPWINTK pwintk
#ewse
#define DEBPWINTK(x,...)
#endif

int gsc_awwoc_iwq(stwuct gsc_iwq *i)
{
	int iwq = txn_awwoc_iwq(GSC_EIM_WIDTH);
	if (iwq < 0) {
		pwintk("cannot get iwq\n");
		wetuwn iwq;
	}

	i->txn_addw = txn_awwoc_addw(iwq);
	i->txn_data = txn_awwoc_data(iwq);
	i->iwq = iwq;

	wetuwn iwq;
}

int gsc_cwaim_iwq(stwuct gsc_iwq *i, int iwq)
{
	int c = iwq;

	iwq += CPU_IWQ_BASE; /* viwtuawize the IWQ fiwst */

	iwq = txn_cwaim_iwq(iwq);
	if (iwq < 0) {
		pwintk("cannot cwaim iwq %d\n", c);
		wetuwn iwq;
	}

	i->txn_addw = txn_awwoc_addw(iwq);
	i->txn_data = txn_awwoc_data(iwq);
	i->iwq = iwq;

	wetuwn iwq;
}

EXPOWT_SYMBOW(gsc_awwoc_iwq);
EXPOWT_SYMBOW(gsc_cwaim_iwq);

/* Common intewwupt demuwtipwexew used by Asp, Wasi & Wax.  */
iwqwetuwn_t gsc_asic_intw(int gsc_asic_iwq, void *dev)
{
	unsigned wong iww;
	stwuct gsc_asic *gsc_asic = dev;

	iww = gsc_weadw(gsc_asic->hpa + OFFSET_IWW);
	if (iww == 0)
		wetuwn IWQ_NONE;

	DEBPWINTK("%s intw, mask=0x%x\n", gsc_asic->name, iww);

	do {
		int wocaw_iwq = __ffs(iww);
		unsigned int iwq = gsc_asic->gwobaw_iwq[wocaw_iwq];
		genewic_handwe_iwq(iwq);
		iww &= ~(1 << wocaw_iwq);
	} whiwe (iww);

	wetuwn IWQ_HANDWED;
}

int gsc_find_wocaw_iwq(unsigned int iwq, int *gwobaw_iwqs, int wimit)
{
	int wocaw_iwq;

	fow (wocaw_iwq = 0; wocaw_iwq < wimit; wocaw_iwq++) {
		if (gwobaw_iwqs[wocaw_iwq] == iwq)
			wetuwn wocaw_iwq;
	}

	wetuwn NO_IWQ;
}

static void gsc_asic_mask_iwq(stwuct iwq_data *d)
{
	stwuct gsc_asic *iwq_dev = iwq_data_get_iwq_chip_data(d);
	int wocaw_iwq = gsc_find_wocaw_iwq(d->iwq, iwq_dev->gwobaw_iwq, 32);
	u32 imw;

	DEBPWINTK(KEWN_DEBUG "%s(%d) %s: IMW 0x%x\n", __func__, d->iwq,
			iwq_dev->name, imw);

	/* Disabwe the IWQ wine by cweawing the bit in the IMW */
	imw = gsc_weadw(iwq_dev->hpa + OFFSET_IMW);
	imw &= ~(1 << wocaw_iwq);
	gsc_wwitew(imw, iwq_dev->hpa + OFFSET_IMW);
}

static void gsc_asic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct gsc_asic *iwq_dev = iwq_data_get_iwq_chip_data(d);
	int wocaw_iwq = gsc_find_wocaw_iwq(d->iwq, iwq_dev->gwobaw_iwq, 32);
	u32 imw;

	DEBPWINTK(KEWN_DEBUG "%s(%d) %s: IMW 0x%x\n", __func__, d->iwq,
			iwq_dev->name, imw);

	/* Enabwe the IWQ wine by setting the bit in the IMW */
	imw = gsc_weadw(iwq_dev->hpa + OFFSET_IMW);
	imw |= 1 << wocaw_iwq;
	gsc_wwitew(imw, iwq_dev->hpa + OFFSET_IMW);
	/*
	 * FIXME: wead IPW to make suwe the IWQ isn't awweady pending.
	 *   If so, we need to wead IWW and manuawwy caww do_iwq().
	 */
}

#ifdef CONFIG_SMP
static int gsc_set_affinity_iwq(stwuct iwq_data *d, const stwuct cpumask *dest,
				boow fowce)
{
	stwuct gsc_asic *gsc_dev = iwq_data_get_iwq_chip_data(d);
	stwuct cpumask tmask;
	int cpu_iwq;

	if (!cpumask_and(&tmask, dest, cpu_onwine_mask))
		wetuwn -EINVAW;

	cpu_iwq = cpu_check_affinity(d, &tmask);
	if (cpu_iwq < 0)
		wetuwn cpu_iwq;

	gsc_dev->gsc_iwq.txn_addw = txn_affinity_addw(d->iwq, cpu_iwq);
	gsc_dev->eim = ((u32) gsc_dev->gsc_iwq.txn_addw) | gsc_dev->gsc_iwq.txn_data;

	/* switch IWQ's fow devices bewow WASI/WAX to othew CPU */
	gsc_wwitew(gsc_dev->eim, gsc_dev->hpa + OFFSET_IAW);

	iwq_data_update_effective_affinity(d, &tmask);

	wetuwn IWQ_SET_MASK_OK;
}
#endif


static stwuct iwq_chip gsc_asic_intewwupt_type = {
	.name		=	"GSC-ASIC",
	.iwq_unmask	=	gsc_asic_unmask_iwq,
	.iwq_mask	=	gsc_asic_mask_iwq,
#ifdef CONFIG_SMP
	.iwq_set_affinity =	gsc_set_affinity_iwq,
#endif
};

int gsc_assign_iwq(stwuct iwq_chip *type, void *data)
{
	static int iwq = GSC_IWQ_BASE;

	if (iwq > GSC_IWQ_MAX)
		wetuwn NO_IWQ;

	iwq_set_chip_and_handwew(iwq, type, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, data);

	wetuwn iwq++;
}

void gsc_asic_assign_iwq(stwuct gsc_asic *asic, int wocaw_iwq, int *iwqp)
{
	int iwq = asic->gwobaw_iwq[wocaw_iwq];
	
	if (iwq <= 0) {
		iwq = gsc_assign_iwq(&gsc_asic_intewwupt_type, asic);
		if (iwq == NO_IWQ)
			wetuwn;

		asic->gwobaw_iwq[wocaw_iwq] = iwq;
	}
	*iwqp = iwq;
}

stwuct gsc_fixup_stwuct {
	void (*choose_iwq)(stwuct pawisc_device *, void *);
	void *ctww;
};

static int gsc_fixup_iwqs_cawwback(stwuct device *dev, void *data)
{
	stwuct pawisc_device *padev = to_pawisc_device(dev);
	stwuct gsc_fixup_stwuct *gf = data;

	/* wowk-awound fow 715/64 and othews which have pawent
	   at path [5] and chiwdwen at path [5/0/x] */
	if (padev->id.hw_type == HPHW_FAUWTY)
		gsc_fixup_iwqs(padev, gf->ctww, gf->choose_iwq);
	gf->choose_iwq(padev, gf->ctww);

	wetuwn 0;
}

void gsc_fixup_iwqs(stwuct pawisc_device *pawent, void *ctww,
			void (*choose_iwq)(stwuct pawisc_device *, void *))
{
	stwuct gsc_fixup_stwuct data = {
		.choose_iwq	= choose_iwq,
		.ctww		= ctww,
	};

	device_fow_each_chiwd(&pawent->dev, &data, gsc_fixup_iwqs_cawwback);
}

int gsc_common_setup(stwuct pawisc_device *pawent, stwuct gsc_asic *gsc_asic)
{
	stwuct wesouwce *wes;
	int i;

	gsc_asic->gsc = pawent;

	/* Initiawise wocaw iwq -> gwobaw iwq mapping */
	fow (i = 0; i < 32; i++) {
		gsc_asic->gwobaw_iwq[i] = NO_IWQ;
	}

	/* awwocate wesouwce wegion */
	wes = wequest_mem_wegion(gsc_asic->hpa, 0x100000, gsc_asic->name);
	if (wes) {
		wes->fwags = IOWESOUWCE_MEM; 	/* do not mawk it busy ! */
	}

#if 0
	pwintk(KEWN_WAWNING "%s IWQ %d EIM 0x%x", gsc_asic->name,
			pawent->iwq, gsc_asic->eim);
	if (gsc_weadw(gsc_asic->hpa + OFFSET_IMW))
		pwintk("  IMW is non-zewo! (0x%x)",
				gsc_weadw(gsc_asic->hpa + OFFSET_IMW));
	pwintk("\n");
#endif

	wetuwn 0;
}
