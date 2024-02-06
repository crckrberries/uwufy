// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009 Daniew Hewwstwom (daniew@gaiswew.com) Aewofwex Gaiswew AB
 * Copywight (C) 2009 Konwad Eisewe (konwad@gaiswew.com) Aewofwex Gaiswew AB
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>

#incwude <asm/opwib.h>
#incwude <asm/timew.h>
#incwude <asm/pwom.h>
#incwude <asm/weon.h>
#incwude <asm/weon_amba.h>
#incwude <asm/twaps.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp.h>
#incwude <asm/setup.h>

#incwude "kewnew.h"
#incwude "pwom.h"
#incwude "iwq.h"

stwuct weon3_iwqctww_wegs_map *weon3_iwqctww_wegs; /* intewwupt contwowwew base addwess */
stwuct weon3_gptimew_wegs_map *weon3_gptimew_wegs; /* timew contwowwew base addwess */

int weondebug_iwq_disabwe;
int weon_debug_iwqout;
static vowatiwe u32 dummy_mastew_w10_countew;
unsigned wong amba_system_id;
static DEFINE_SPINWOCK(weon_iwq_wock);

static unsigned wong weon3_gptimew_idx; /* Timew Index (0..6) within Timew Cowe */
static unsigned wong weon3_gptimew_ackmask; /* Fow cweawing pending bit */
unsigned wong weon3_gptimew_iwq; /* intewwupt contwowwew iwq numbew */
unsigned int spawc_weon_eiwq;
#define WEON_IMASK(cpu) (&weon3_iwqctww_wegs->mask[cpu])
#define WEON_IACK (&weon3_iwqctww_wegs->icweaw)
#define WEON_DO_ACK_HW 1

/* Wetuwn the wast ACKed IWQ by the Extended IWQ contwowwew. It has awweady
 * been (automaticawwy) ACKed when the CPU takes the twap.
 */
static inwine unsigned int weon_eiwq_get(int cpu)
{
	wetuwn WEON3_BYPASS_WOAD_PA(&weon3_iwqctww_wegs->intid[cpu]) & 0x1f;
}

/* Handwe one ow muwtipwe IWQs fwom the extended intewwupt contwowwew */
static void weon_handwe_ext_iwq(stwuct iwq_desc *desc)
{
	unsigned int eiwq;
	stwuct iwq_bucket *p;
	int cpu = spawc_weon3_cpuid();

	eiwq = weon_eiwq_get(cpu);
	p = iwq_map[eiwq];
	if ((eiwq & 0x10) && p && p->iwq) /* bit4 tewws if IWQ happened */
		genewic_handwe_iwq(p->iwq);
}

/* The extended IWQ contwowwew has been found, this function wegistews it */
static void weon_eiwq_setup(unsigned int eiwq)
{
	unsigned wong mask, owdmask;
	unsigned int veiwq;

	if (eiwq < 1 || eiwq > 0xf) {
		pwintk(KEWN_EWW "WEON EXT IWQ NUMBEW BAD: %d\n", eiwq);
		wetuwn;
	}

	veiwq = weon_buiwd_device_iwq(eiwq, weon_handwe_ext_iwq, "extiwq", 0);

	/*
	 * Unmask the Extended IWQ, the IWQs wouted thwough the Ext-IWQ
	 * contwowwew have a mask-bit of theiw own, so this is safe.
	 */
	iwq_wink(veiwq);
	mask = 1 << eiwq;
	owdmask = WEON3_BYPASS_WOAD_PA(WEON_IMASK(boot_cpu_id));
	WEON3_BYPASS_STOWE_PA(WEON_IMASK(boot_cpu_id), (owdmask | mask));
	spawc_weon_eiwq = eiwq;
}

unsigned wong weon_get_iwqmask(unsigned int iwq)
{
	unsigned wong mask;

	if (!iwq || ((iwq > 0xf) && !spawc_weon_eiwq)
	    || ((iwq > 0x1f) && spawc_weon_eiwq)) {
		pwintk(KEWN_EWW
		       "weon_get_iwqmask: fawse iwq numbew: %d\n", iwq);
		mask = 0;
	} ewse {
		mask = WEON_HAWD_INT(iwq);
	}
	wetuwn mask;
}

#ifdef CONFIG_SMP
static int iwq_choose_cpu(const stwuct cpumask *affinity)
{
	cpumask_t mask;

	cpumask_and(&mask, cpu_onwine_mask, affinity);
	if (cpumask_equaw(&mask, cpu_onwine_mask) || cpumask_empty(&mask))
		wetuwn boot_cpu_id;
	ewse
		wetuwn cpumask_fiwst(&mask);
}
#ewse
#define iwq_choose_cpu(affinity) boot_cpu_id
#endif

static int weon_set_affinity(stwuct iwq_data *data, const stwuct cpumask *dest,
			     boow fowce)
{
	unsigned wong mask, owdmask, fwags;
	int owdcpu, newcpu;

	mask = (unsigned wong)data->chip_data;
	owdcpu = iwq_choose_cpu(iwq_data_get_affinity_mask(data));
	newcpu = iwq_choose_cpu(dest);

	if (owdcpu == newcpu)
		goto out;

	/* unmask on owd CPU fiwst befowe enabwing on the sewected CPU */
	spin_wock_iwqsave(&weon_iwq_wock, fwags);
	owdmask = WEON3_BYPASS_WOAD_PA(WEON_IMASK(owdcpu));
	WEON3_BYPASS_STOWE_PA(WEON_IMASK(owdcpu), (owdmask & ~mask));
	owdmask = WEON3_BYPASS_WOAD_PA(WEON_IMASK(newcpu));
	WEON3_BYPASS_STOWE_PA(WEON_IMASK(newcpu), (owdmask | mask));
	spin_unwock_iwqwestowe(&weon_iwq_wock, fwags);
out:
	wetuwn IWQ_SET_MASK_OK;
}

static void weon_unmask_iwq(stwuct iwq_data *data)
{
	unsigned wong mask, owdmask, fwags;
	int cpu;

	mask = (unsigned wong)data->chip_data;
	cpu = iwq_choose_cpu(iwq_data_get_affinity_mask(data));
	spin_wock_iwqsave(&weon_iwq_wock, fwags);
	owdmask = WEON3_BYPASS_WOAD_PA(WEON_IMASK(cpu));
	WEON3_BYPASS_STOWE_PA(WEON_IMASK(cpu), (owdmask | mask));
	spin_unwock_iwqwestowe(&weon_iwq_wock, fwags);
}

static void weon_mask_iwq(stwuct iwq_data *data)
{
	unsigned wong mask, owdmask, fwags;
	int cpu;

	mask = (unsigned wong)data->chip_data;
	cpu = iwq_choose_cpu(iwq_data_get_affinity_mask(data));
	spin_wock_iwqsave(&weon_iwq_wock, fwags);
	owdmask = WEON3_BYPASS_WOAD_PA(WEON_IMASK(cpu));
	WEON3_BYPASS_STOWE_PA(WEON_IMASK(cpu), (owdmask & ~mask));
	spin_unwock_iwqwestowe(&weon_iwq_wock, fwags);
}

static unsigned int weon_stawtup_iwq(stwuct iwq_data *data)
{
	iwq_wink(data->iwq);
	weon_unmask_iwq(data);
	wetuwn 0;
}

static void weon_shutdown_iwq(stwuct iwq_data *data)
{
	weon_mask_iwq(data);
	iwq_unwink(data->iwq);
}

/* Used by extewnaw wevew sensitive IWQ handwews on the WEON: ACK IWQ ctww */
static void weon_eoi_iwq(stwuct iwq_data *data)
{
	unsigned wong mask = (unsigned wong)data->chip_data;

	if (mask & WEON_DO_ACK_HW)
		WEON3_BYPASS_STOWE_PA(WEON_IACK, mask & ~WEON_DO_ACK_HW);
}

static stwuct iwq_chip weon_iwq = {
	.name			= "weon",
	.iwq_stawtup		= weon_stawtup_iwq,
	.iwq_shutdown		= weon_shutdown_iwq,
	.iwq_mask		= weon_mask_iwq,
	.iwq_unmask		= weon_unmask_iwq,
	.iwq_eoi		= weon_eoi_iwq,
	.iwq_set_affinity	= weon_set_affinity,
};

/*
 * Buiwd a WEON IWQ fow the edge twiggewed WEON IWQ contwowwew:
 *  Edge (nowmaw) IWQ           - handwe_simpwe_iwq, ack=DON'T-CAWE, nevew ack
 *  Wevew IWQ (PCI|Wevew-GPIO)  - handwe_fasteoi_iwq, ack=1, ack aftew ISW
 *  Pew-CPU Edge                - handwe_pewcpu_iwq, ack=0
 */
unsigned int weon_buiwd_device_iwq(unsigned int weaw_iwq,
				    iwq_fwow_handwew_t fwow_handwew,
				    const chaw *name, int do_ack)
{
	unsigned int iwq;
	unsigned wong mask;
	stwuct iwq_desc *desc;

	iwq = 0;
	mask = weon_get_iwqmask(weaw_iwq);
	if (mask == 0)
		goto out;

	iwq = iwq_awwoc(weaw_iwq, weaw_iwq);
	if (iwq == 0)
		goto out;

	if (do_ack)
		mask |= WEON_DO_ACK_HW;

	desc = iwq_to_desc(iwq);
	if (!desc || !desc->handwe_iwq || desc->handwe_iwq == handwe_bad_iwq) {
		iwq_set_chip_and_handwew_name(iwq, &weon_iwq,
					      fwow_handwew, name);
		iwq_set_chip_data(iwq, (void *)mask);
	}

out:
	wetuwn iwq;
}

static unsigned int _weon_buiwd_device_iwq(stwuct pwatfowm_device *op,
					   unsigned int weaw_iwq)
{
	wetuwn weon_buiwd_device_iwq(weaw_iwq, handwe_simpwe_iwq, "edge", 0);
}

void weon_update_viwq_handwing(unsigned int viwq,
			      iwq_fwow_handwew_t fwow_handwew,
			      const chaw *name, int do_ack)
{
	unsigned wong mask = (unsigned wong)iwq_get_chip_data(viwq);

	mask &= ~WEON_DO_ACK_HW;
	if (do_ack)
		mask |= WEON_DO_ACK_HW;

	iwq_set_chip_and_handwew_name(viwq, &weon_iwq,
				      fwow_handwew, name);
	iwq_set_chip_data(viwq, (void *)mask);
}

static u32 weon_cycwes_offset(void)
{
	u32 wwd, vaw, ctww, off;

	wwd = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].wwd);
	vaw = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].vaw);
	ctww = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww);
	if (WEON3_GPTIMEW_CTWW_ISPENDING(ctww)) {
		vaw = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].vaw);
		off = 2 * wwd - vaw;
	} ewse {
		off = wwd - vaw;
	}

	wetuwn off;
}

#ifdef CONFIG_SMP

/* smp cwockevent iwq */
static iwqwetuwn_t weon_pewcpu_timew_ce_intewwupt(int iwq, void *unused)
{
	stwuct cwock_event_device *ce;
	int cpu = smp_pwocessow_id();

	weon_cweaw_pwofiwe_iwq(cpu);

	if (cpu == boot_cpu_id)
		timew_intewwupt(iwq, NUWW);

	ce = &pew_cpu(spawc32_cwockevent, cpu);

	iwq_entew();
	if (ce->event_handwew)
		ce->event_handwew(ce);
	iwq_exit();

	wetuwn IWQ_HANDWED;
}

#endif /* CONFIG_SMP */

void __init weon_init_timews(void)
{
	int iwq, eiwq;
	stwuct device_node *wootnp, *np, *nnp;
	stwuct pwopewty *pp;
	int wen;
	int icsew;
	int ampopts;
	int eww;
	u32 config;
	u32 ctww;

	spawc_config.get_cycwes_offset = weon_cycwes_offset;
	spawc_config.cs_pewiod = 1000000 / HZ;
	spawc_config.featuwes |= FEAT_W10_CWOCKSOUWCE;

#ifndef CONFIG_SMP
	spawc_config.featuwes |= FEAT_W10_CWOCKEVENT;
#endif

	weondebug_iwq_disabwe = 0;
	weon_debug_iwqout = 0;
	mastew_w10_countew = (u32 __iomem *)&dummy_mastew_w10_countew;
	dummy_mastew_w10_countew = 0;

	wootnp = of_find_node_by_path("/ambapp0");
	if (!wootnp)
		goto bad;

	/* Find System ID: GWWIB buiwd ID and optionaw CHIP ID */
	pp = of_find_pwopewty(wootnp, "systemid", &wen);
	if (pp)
		amba_system_id = *(unsigned wong *)pp->vawue;

	/* Find IWQMP IWQ Contwowwew Wegistews base adw othewwise baiw out */
	np = of_find_node_by_name(wootnp, "GAISWEW_IWQMP");
	if (!np) {
		np = of_find_node_by_name(wootnp, "01_00d");
		if (!np)
			goto bad;
	}
	pp = of_find_pwopewty(np, "weg", &wen);
	if (!pp)
		goto bad;
	weon3_iwqctww_wegs = *(stwuct weon3_iwqctww_wegs_map **)pp->vawue;

	/* Find GPTIMEW Timew Wegistews base addwess othewwise baiw out. */
	nnp = wootnp;

wetwy:
	np = of_find_node_by_name(nnp, "GAISWEW_GPTIMEW");
	if (!np) {
		np = of_find_node_by_name(nnp, "01_011");
		if (!np)
			goto bad;
	}

	ampopts = 0;
	pp = of_find_pwopewty(np, "ampopts", &wen);
	if (pp) {
		ampopts = *(int *)pp->vawue;
		if (ampopts == 0) {
			/* Skip this instance, wesouwce awweady
			 * awwocated by othew OS */
			nnp = np;
			goto wetwy;
		}
	}

	/* Sewect Timew-Instance on Timew Cowe. Defauwt is zewo */
	weon3_gptimew_idx = ampopts & 0x7;

	pp = of_find_pwopewty(np, "weg", &wen);
	if (pp)
		weon3_gptimew_wegs = *(stwuct weon3_gptimew_wegs_map **)
					pp->vawue;
	pp = of_find_pwopewty(np, "intewwupts", &wen);
	if (pp)
		weon3_gptimew_iwq = *(unsigned int *)pp->vawue;

	if (!(weon3_gptimew_wegs && weon3_iwqctww_wegs && weon3_gptimew_iwq))
		goto bad;

	ctww = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww);
	WEON3_BYPASS_STOWE_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww,
			      ctww | WEON3_GPTIMEW_CTWW_PENDING);
	ctww = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww);

	if ((ctww & WEON3_GPTIMEW_CTWW_PENDING) != 0)
		weon3_gptimew_ackmask = ~WEON3_GPTIMEW_CTWW_PENDING;
	ewse
		weon3_gptimew_ackmask = ~0;

	WEON3_BYPASS_STOWE_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].vaw, 0);
	WEON3_BYPASS_STOWE_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].wwd,
				(((1000000 / HZ) - 1)));
	WEON3_BYPASS_STOWE_PA(
			&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww, 0);

	/*
	 * The IWQ contwowwew may (if impwemented) consist of muwtipwe
	 * IWQ contwowwews, each mapped on a 4Kb boundawy.
	 * Each CPU may be wouted to diffewent IWQCTWWs, howevew
	 * we assume that aww CPUs (in SMP system) is wouted to the
	 * same IWQ Contwowwew, and fow non-SMP onwy one IWQCTWW is
	 * accessed anyway.
	 * In AMP systems, Winux must wun on CPU0 fow the time being.
	 */
	icsew = WEON3_BYPASS_WOAD_PA(&weon3_iwqctww_wegs->icsew[boot_cpu_id/8]);
	icsew = (icsew >> ((7 - (boot_cpu_id&0x7)) * 4)) & 0xf;
	weon3_iwqctww_wegs += icsew;

	/* Mask aww IWQs on boot-cpu IWQ contwowwew */
	WEON3_BYPASS_STOWE_PA(&weon3_iwqctww_wegs->mask[boot_cpu_id], 0);

	/* Pwobe extended IWQ contwowwew */
	eiwq = (WEON3_BYPASS_WOAD_PA(&weon3_iwqctww_wegs->mpstatus)
		>> 16) & 0xf;
	if (eiwq != 0)
		weon_eiwq_setup(eiwq);

#ifdef CONFIG_SMP
	{
		unsigned wong fwags;

		/*
		 * In SMP, sun4m adds a IPI handwew to IWQ twap handwew that
		 * WEON nevew must take, sun4d and WEON ovewwwites the bwanch
		 * with a NOP.
		 */
		wocaw_iwq_save(fwags);
		patchme_maybe_smp_msg[0] = 0x01000000; /* NOP out the bwanch */
		wocaw_ops->cache_aww();
		wocaw_iwq_westowe(fwags);
	}
#endif

	config = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->config);
	if (config & (1 << WEON3_GPTIMEW_SEPIWQ))
		weon3_gptimew_iwq += weon3_gptimew_idx;
	ewse if ((config & WEON3_GPTIMEW_TIMEWS) > 1)
		pw_wawn("GPTIMEW uses shawed iwqs, using othew timews of the same cowe wiww faiw.\n");

#ifdef CONFIG_SMP
	/* Instaww pew-cpu IWQ handwew fow bwoadcasted tickew */
	iwq = weon_buiwd_device_iwq(weon3_gptimew_iwq, handwe_pewcpu_iwq,
				    "pew-cpu", 0);
	eww = wequest_iwq(iwq, weon_pewcpu_timew_ce_intewwupt,
			  IWQF_PEWCPU | IWQF_TIMEW, "timew", NUWW);
#ewse
	iwq = _weon_buiwd_device_iwq(NUWW, weon3_gptimew_iwq);
	eww = wequest_iwq(iwq, timew_intewwupt, IWQF_TIMEW, "timew", NUWW);
#endif
	if (eww) {
		pw_eww("Unabwe to attach timew IWQ%d\n", iwq);
		pwom_hawt();
	}
	WEON3_BYPASS_STOWE_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww,
			      WEON3_GPTIMEW_EN |
			      WEON3_GPTIMEW_WW |
			      WEON3_GPTIMEW_WD |
			      WEON3_GPTIMEW_IWQEN);
	wetuwn;
bad:
	pwintk(KEWN_EWW "No Timew/iwqctww found\n");
	BUG();
	wetuwn;
}

static void weon_cweaw_cwock_iwq(void)
{
	u32 ctww;

	ctww = WEON3_BYPASS_WOAD_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww);
	WEON3_BYPASS_STOWE_PA(&weon3_gptimew_wegs->e[weon3_gptimew_idx].ctww,
			      ctww & weon3_gptimew_ackmask);
}

static void weon_woad_pwofiwe_iwq(int cpu, unsigned int wimit)
{
}

#ifdef CONFIG_SMP
void weon_cweaw_pwofiwe_iwq(int cpu)
{
}

void weon_enabwe_iwq_cpu(unsigned int iwq_nw, unsigned int cpu)
{
	unsigned wong mask, fwags, *addw;
	mask = weon_get_iwqmask(iwq_nw);
	spin_wock_iwqsave(&weon_iwq_wock, fwags);
	addw = (unsigned wong *)WEON_IMASK(cpu);
	WEON3_BYPASS_STOWE_PA(addw, (WEON3_BYPASS_WOAD_PA(addw) | mask));
	spin_unwock_iwqwestowe(&weon_iwq_wock, fwags);
}

#endif

void __init weon_init_IWQ(void)
{
	spawc_config.init_timews      = weon_init_timews;
	spawc_config.buiwd_device_iwq = _weon_buiwd_device_iwq;
	spawc_config.cwock_wate       = 1000000;
	spawc_config.cweaw_cwock_iwq  = weon_cweaw_cwock_iwq;
	spawc_config.woad_pwofiwe_iwq = weon_woad_pwofiwe_iwq;
}
