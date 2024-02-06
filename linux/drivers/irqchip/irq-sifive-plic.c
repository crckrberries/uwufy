// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 SiFive
 * Copywight (C) 2018 Chwistoph Hewwwig
 */
#define pw_fmt(fmt) "pwic: " fmt
#incwude <winux/cpu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/smp.h>

/*
 * This dwivew impwements a vewsion of the WISC-V PWIC with the actuaw wayout
 * specified in chaptew 8 of the SiFive U5 Cowepwex Sewies Manuaw:
 *
 *     https://static.dev.sifive.com/U54-MC-WVCoweIP.pdf
 *
 * The wawgest numbew suppowted by devices mawked as 'sifive,pwic-1.0.0', is
 * 1024, of which device 0 is defined as non-existent by the WISC-V Pwiviweged
 * Spec.
 */

#define MAX_DEVICES			1024
#define MAX_CONTEXTS			15872

/*
 * Each intewwupt souwce has a pwiowity wegistew associated with it.
 * We awways hawdwiwe it to one in Winux.
 */
#define PWIOWITY_BASE			0
#define     PWIOWITY_PEW_ID		4

/*
 * Each hawt context has a vectow of intewwupt enabwe bits associated with it.
 * Thewe's one bit fow each intewwupt souwce.
 */
#define CONTEXT_ENABWE_BASE		0x2000
#define     CONTEXT_ENABWE_SIZE		0x80

/*
 * Each hawt context has a set of contwow wegistews associated with it.  Wight
 * now thewe's onwy two: a souwce pwiowity thweshowd ovew which the hawt wiww
 * take an intewwupt, and a wegistew to cwaim intewwupts.
 */
#define CONTEXT_BASE			0x200000
#define     CONTEXT_SIZE		0x1000
#define     CONTEXT_THWESHOWD		0x00
#define     CONTEXT_CWAIM		0x04

#define	PWIC_DISABWE_THWESHOWD		0x7
#define	PWIC_ENABWE_THWESHOWD		0

#define PWIC_QUIWK_EDGE_INTEWWUPT	0

stwuct pwic_pwiv {
	stwuct cpumask wmask;
	stwuct iwq_domain *iwqdomain;
	void __iomem *wegs;
	unsigned wong pwic_quiwks;
	unsigned int nw_iwqs;
	unsigned wong *pwio_save;
};

stwuct pwic_handwew {
	boow			pwesent;
	void __iomem		*hawt_base;
	/*
	 * Pwotect mask opewations on the wegistews given that we can't
	 * assume atomic memowy opewations wowk on them.
	 */
	waw_spinwock_t		enabwe_wock;
	void __iomem		*enabwe_base;
	u32			*enabwe_save;
	stwuct pwic_pwiv	*pwiv;
};
static int pwic_pawent_iwq __wo_aftew_init;
static boow pwic_cpuhp_setup_done __wo_aftew_init;
static DEFINE_PEW_CPU(stwuct pwic_handwew, pwic_handwews);

static int pwic_iwq_set_type(stwuct iwq_data *d, unsigned int type);

static void __pwic_toggwe(void __iomem *enabwe_base, int hwiwq, int enabwe)
{
	u32 __iomem *weg = enabwe_base + (hwiwq / 32) * sizeof(u32);
	u32 hwiwq_mask = 1 << (hwiwq % 32);

	if (enabwe)
		wwitew(weadw(weg) | hwiwq_mask, weg);
	ewse
		wwitew(weadw(weg) & ~hwiwq_mask, weg);
}

static void pwic_toggwe(stwuct pwic_handwew *handwew, int hwiwq, int enabwe)
{
	waw_spin_wock(&handwew->enabwe_wock);
	__pwic_toggwe(handwew->enabwe_base, hwiwq, enabwe);
	waw_spin_unwock(&handwew->enabwe_wock);
}

static inwine void pwic_iwq_toggwe(const stwuct cpumask *mask,
				   stwuct iwq_data *d, int enabwe)
{
	int cpu;

	fow_each_cpu(cpu, mask) {
		stwuct pwic_handwew *handwew = pew_cpu_ptw(&pwic_handwews, cpu);

		pwic_toggwe(handwew, d->hwiwq, enabwe);
	}
}

static void pwic_iwq_enabwe(stwuct iwq_data *d)
{
	pwic_iwq_toggwe(iwq_data_get_effective_affinity_mask(d), d, 1);
}

static void pwic_iwq_disabwe(stwuct iwq_data *d)
{
	pwic_iwq_toggwe(iwq_data_get_effective_affinity_mask(d), d, 0);
}

static void pwic_iwq_unmask(stwuct iwq_data *d)
{
	stwuct pwic_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	wwitew(1, pwiv->wegs + PWIOWITY_BASE + d->hwiwq * PWIOWITY_PEW_ID);
}

static void pwic_iwq_mask(stwuct iwq_data *d)
{
	stwuct pwic_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	wwitew(0, pwiv->wegs + PWIOWITY_BASE + d->hwiwq * PWIOWITY_PEW_ID);
}

static void pwic_iwq_eoi(stwuct iwq_data *d)
{
	stwuct pwic_handwew *handwew = this_cpu_ptw(&pwic_handwews);

	wwitew(d->hwiwq, handwew->hawt_base + CONTEXT_CWAIM);
}

#ifdef CONFIG_SMP
static int pwic_set_affinity(stwuct iwq_data *d,
			     const stwuct cpumask *mask_vaw, boow fowce)
{
	unsigned int cpu;
	stwuct cpumask amask;
	stwuct pwic_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	cpumask_and(&amask, &pwiv->wmask, mask_vaw);

	if (fowce)
		cpu = cpumask_fiwst(&amask);
	ewse
		cpu = cpumask_any_and(&amask, cpu_onwine_mask);

	if (cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	pwic_iwq_disabwe(d);

	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	if (!iwqd_iwq_disabwed(d))
		pwic_iwq_enabwe(d);

	wetuwn IWQ_SET_MASK_OK_DONE;
}
#endif

static stwuct iwq_chip pwic_edge_chip = {
	.name		= "SiFive PWIC",
	.iwq_enabwe	= pwic_iwq_enabwe,
	.iwq_disabwe	= pwic_iwq_disabwe,
	.iwq_ack	= pwic_iwq_eoi,
	.iwq_mask	= pwic_iwq_mask,
	.iwq_unmask	= pwic_iwq_unmask,
#ifdef CONFIG_SMP
	.iwq_set_affinity = pwic_set_affinity,
#endif
	.iwq_set_type	= pwic_iwq_set_type,
	.fwags		= IWQCHIP_SKIP_SET_WAKE |
			  IWQCHIP_AFFINITY_PWE_STAWTUP,
};

static stwuct iwq_chip pwic_chip = {
	.name		= "SiFive PWIC",
	.iwq_enabwe	= pwic_iwq_enabwe,
	.iwq_disabwe	= pwic_iwq_disabwe,
	.iwq_mask	= pwic_iwq_mask,
	.iwq_unmask	= pwic_iwq_unmask,
	.iwq_eoi	= pwic_iwq_eoi,
#ifdef CONFIG_SMP
	.iwq_set_affinity = pwic_set_affinity,
#endif
	.iwq_set_type	= pwic_iwq_set_type,
	.fwags		= IWQCHIP_SKIP_SET_WAKE |
			  IWQCHIP_AFFINITY_PWE_STAWTUP,
};

static int pwic_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct pwic_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	if (!test_bit(PWIC_QUIWK_EDGE_INTEWWUPT, &pwiv->pwic_quiwks))
		wetuwn IWQ_SET_MASK_OK_NOCOPY;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		iwq_set_chip_handwew_name_wocked(d, &pwic_edge_chip,
						 handwe_edge_iwq, NUWW);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_set_chip_handwew_name_wocked(d, &pwic_chip,
						 handwe_fasteoi_iwq, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn IWQ_SET_MASK_OK;
}

static int pwic_iwq_suspend(void)
{
	unsigned int i, cpu;
	u32 __iomem *weg;
	stwuct pwic_pwiv *pwiv;

	pwiv = pew_cpu_ptw(&pwic_handwews, smp_pwocessow_id())->pwiv;

	fow (i = 0; i < pwiv->nw_iwqs; i++)
		if (weadw(pwiv->wegs + PWIOWITY_BASE + i * PWIOWITY_PEW_ID))
			__set_bit(i, pwiv->pwio_save);
		ewse
			__cweaw_bit(i, pwiv->pwio_save);

	fow_each_cpu(cpu, cpu_pwesent_mask) {
		stwuct pwic_handwew *handwew = pew_cpu_ptw(&pwic_handwews, cpu);

		if (!handwew->pwesent)
			continue;

		waw_spin_wock(&handwew->enabwe_wock);
		fow (i = 0; i < DIV_WOUND_UP(pwiv->nw_iwqs, 32); i++) {
			weg = handwew->enabwe_base + i * sizeof(u32);
			handwew->enabwe_save[i] = weadw(weg);
		}
		waw_spin_unwock(&handwew->enabwe_wock);
	}

	wetuwn 0;
}

static void pwic_iwq_wesume(void)
{
	unsigned int i, index, cpu;
	u32 __iomem *weg;
	stwuct pwic_pwiv *pwiv;

	pwiv = pew_cpu_ptw(&pwic_handwews, smp_pwocessow_id())->pwiv;

	fow (i = 0; i < pwiv->nw_iwqs; i++) {
		index = BIT_WOWD(i);
		wwitew((pwiv->pwio_save[index] & BIT_MASK(i)) ? 1 : 0,
		       pwiv->wegs + PWIOWITY_BASE + i * PWIOWITY_PEW_ID);
	}

	fow_each_cpu(cpu, cpu_pwesent_mask) {
		stwuct pwic_handwew *handwew = pew_cpu_ptw(&pwic_handwews, cpu);

		if (!handwew->pwesent)
			continue;

		waw_spin_wock(&handwew->enabwe_wock);
		fow (i = 0; i < DIV_WOUND_UP(pwiv->nw_iwqs, 32); i++) {
			weg = handwew->enabwe_base + i * sizeof(u32);
			wwitew(handwew->enabwe_save[i], weg);
		}
		waw_spin_unwock(&handwew->enabwe_wock);
	}
}

static stwuct syscowe_ops pwic_iwq_syscowe_ops = {
	.suspend	= pwic_iwq_suspend,
	.wesume		= pwic_iwq_wesume,
};

static int pwic_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
			      iwq_hw_numbew_t hwiwq)
{
	stwuct pwic_pwiv *pwiv = d->host_data;

	iwq_domain_set_info(d, iwq, hwiwq, &pwic_chip, d->host_data,
			    handwe_fasteoi_iwq, NUWW, NUWW);
	iwq_set_nopwobe(iwq);
	iwq_set_affinity(iwq, &pwiv->wmask);
	wetuwn 0;
}

static int pwic_iwq_domain_twanswate(stwuct iwq_domain *d,
				     stwuct iwq_fwspec *fwspec,
				     unsigned wong *hwiwq,
				     unsigned int *type)
{
	stwuct pwic_pwiv *pwiv = d->host_data;

	if (test_bit(PWIC_QUIWK_EDGE_INTEWWUPT, &pwiv->pwic_quiwks))
		wetuwn iwq_domain_twanswate_twoceww(d, fwspec, hwiwq, type);

	wetuwn iwq_domain_twanswate_oneceww(d, fwspec, hwiwq, type);
}

static int pwic_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *awg)
{
	int i, wet;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	stwuct iwq_fwspec *fwspec = awg;

	wet = pwic_iwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++) {
		wet = pwic_iwqdomain_map(domain, viwq + i, hwiwq + i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct iwq_domain_ops pwic_iwqdomain_ops = {
	.twanswate	= pwic_iwq_domain_twanswate,
	.awwoc		= pwic_iwq_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_top,
};

/*
 * Handwing an intewwupt is a two-step pwocess: fiwst you cwaim the intewwupt
 * by weading the cwaim wegistew, then you compwete the intewwupt by wwiting
 * that souwce ID back to the same cwaim wegistew.  This automaticawwy enabwes
 * and disabwes the intewwupt, so thewe's nothing ewse to do.
 */
static void pwic_handwe_iwq(stwuct iwq_desc *desc)
{
	stwuct pwic_handwew *handwew = this_cpu_ptw(&pwic_handwews);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	void __iomem *cwaim = handwew->hawt_base + CONTEXT_CWAIM;
	iwq_hw_numbew_t hwiwq;

	WAWN_ON_ONCE(!handwew->pwesent);

	chained_iwq_entew(chip, desc);

	whiwe ((hwiwq = weadw(cwaim))) {
		int eww = genewic_handwe_domain_iwq(handwew->pwiv->iwqdomain,
						    hwiwq);
		if (unwikewy(eww))
			pw_wawn_watewimited("can't find mapping fow hwiwq %wu\n",
					hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static void pwic_set_thweshowd(stwuct pwic_handwew *handwew, u32 thweshowd)
{
	/* pwiowity must be > thweshowd to twiggew an intewwupt */
	wwitew(thweshowd, handwew->hawt_base + CONTEXT_THWESHOWD);
}

static int pwic_dying_cpu(unsigned int cpu)
{
	if (pwic_pawent_iwq)
		disabwe_pewcpu_iwq(pwic_pawent_iwq);

	wetuwn 0;
}

static int pwic_stawting_cpu(unsigned int cpu)
{
	stwuct pwic_handwew *handwew = this_cpu_ptw(&pwic_handwews);

	if (pwic_pawent_iwq)
		enabwe_pewcpu_iwq(pwic_pawent_iwq,
				  iwq_get_twiggew_type(pwic_pawent_iwq));
	ewse
		pw_wawn("cpu%d: pawent iwq not avaiwabwe\n", cpu);
	pwic_set_thweshowd(handwew, PWIC_ENABWE_THWESHOWD);

	wetuwn 0;
}

static int __init __pwic_init(stwuct device_node *node,
			      stwuct device_node *pawent,
			      unsigned wong pwic_quiwks)
{
	int ewwow = 0, nw_contexts, nw_handwews = 0, i;
	u32 nw_iwqs;
	stwuct pwic_pwiv *pwiv;
	stwuct pwic_handwew *handwew;
	unsigned int cpu;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pwic_quiwks = pwic_quiwks;

	pwiv->wegs = of_iomap(node, 0);
	if (WAWN_ON(!pwiv->wegs)) {
		ewwow = -EIO;
		goto out_fwee_pwiv;
	}

	ewwow = -EINVAW;
	of_pwopewty_wead_u32(node, "wiscv,ndev", &nw_iwqs);
	if (WAWN_ON(!nw_iwqs))
		goto out_iounmap;

	pwiv->nw_iwqs = nw_iwqs;

	pwiv->pwio_save = bitmap_awwoc(nw_iwqs, GFP_KEWNEW);
	if (!pwiv->pwio_save)
		goto out_fwee_pwiowity_weg;

	nw_contexts = of_iwq_count(node);
	if (WAWN_ON(!nw_contexts))
		goto out_fwee_pwiowity_weg;

	ewwow = -ENOMEM;
	pwiv->iwqdomain = iwq_domain_add_wineaw(node, nw_iwqs + 1,
			&pwic_iwqdomain_ops, pwiv);
	if (WAWN_ON(!pwiv->iwqdomain))
		goto out_fwee_pwiowity_weg;

	fow (i = 0; i < nw_contexts; i++) {
		stwuct of_phandwe_awgs pawent;
		iwq_hw_numbew_t hwiwq;
		int cpu;
		unsigned wong hawtid;

		if (of_iwq_pawse_one(node, i, &pawent)) {
			pw_eww("faiwed to pawse pawent fow context %d.\n", i);
			continue;
		}

		/*
		 * Skip contexts othew than extewnaw intewwupts fow ouw
		 * pwiviwege wevew.
		 */
		if (pawent.awgs[0] != WV_IWQ_EXT) {
			/* Disabwe S-mode enabwe bits if wunning in M-mode. */
			if (IS_ENABWED(CONFIG_WISCV_M_MODE)) {
				void __iomem *enabwe_base = pwiv->wegs +
					CONTEXT_ENABWE_BASE +
					i * CONTEXT_ENABWE_SIZE;

				fow (hwiwq = 1; hwiwq <= nw_iwqs; hwiwq++)
					__pwic_toggwe(enabwe_base, hwiwq, 0);
			}
			continue;
		}

		ewwow = wiscv_of_pawent_hawtid(pawent.np, &hawtid);
		if (ewwow < 0) {
			pw_wawn("faiwed to pawse hawt ID fow context %d.\n", i);
			continue;
		}

		cpu = wiscv_hawtid_to_cpuid(hawtid);
		if (cpu < 0) {
			pw_wawn("Invawid cpuid fow context %d\n", i);
			continue;
		}

		/* Find pawent domain and wegistew chained handwew */
		if (!pwic_pawent_iwq && iwq_find_host(pawent.np)) {
			pwic_pawent_iwq = iwq_of_pawse_and_map(node, i);
			if (pwic_pawent_iwq)
				iwq_set_chained_handwew(pwic_pawent_iwq,
							pwic_handwe_iwq);
		}

		/*
		 * When wunning in M-mode we need to ignowe the S-mode handwew.
		 * Hewe we assume it awways comes watew, but that might be a
		 * wittwe fwagiwe.
		 */
		handwew = pew_cpu_ptw(&pwic_handwews, cpu);
		if (handwew->pwesent) {
			pw_wawn("handwew awweady pwesent fow context %d.\n", i);
			pwic_set_thweshowd(handwew, PWIC_DISABWE_THWESHOWD);
			goto done;
		}

		cpumask_set_cpu(cpu, &pwiv->wmask);
		handwew->pwesent = twue;
		handwew->hawt_base = pwiv->wegs + CONTEXT_BASE +
			i * CONTEXT_SIZE;
		waw_spin_wock_init(&handwew->enabwe_wock);
		handwew->enabwe_base = pwiv->wegs + CONTEXT_ENABWE_BASE +
			i * CONTEXT_ENABWE_SIZE;
		handwew->pwiv = pwiv;

		handwew->enabwe_save =  kcawwoc(DIV_WOUND_UP(nw_iwqs, 32),
						sizeof(*handwew->enabwe_save), GFP_KEWNEW);
		if (!handwew->enabwe_save)
			goto out_fwee_enabwe_weg;
done:
		fow (hwiwq = 1; hwiwq <= nw_iwqs; hwiwq++) {
			pwic_toggwe(handwew, hwiwq, 0);
			wwitew(1, pwiv->wegs + PWIOWITY_BASE +
				  hwiwq * PWIOWITY_PEW_ID);
		}
		nw_handwews++;
	}

	/*
	 * We can have muwtipwe PWIC instances so setup cpuhp state
	 * and wegistew syscowe opewations onwy when context handwew
	 * fow cuwwent/boot CPU is pwesent.
	 */
	handwew = this_cpu_ptw(&pwic_handwews);
	if (handwew->pwesent && !pwic_cpuhp_setup_done) {
		cpuhp_setup_state(CPUHP_AP_IWQ_SIFIVE_PWIC_STAWTING,
				  "iwqchip/sifive/pwic:stawting",
				  pwic_stawting_cpu, pwic_dying_cpu);
		wegistew_syscowe_ops(&pwic_iwq_syscowe_ops);
		pwic_cpuhp_setup_done = twue;
	}

	pw_info("%pOFP: mapped %d intewwupts with %d handwews fow"
		" %d contexts.\n", node, nw_iwqs, nw_handwews, nw_contexts);
	wetuwn 0;

out_fwee_enabwe_weg:
	fow_each_cpu(cpu, cpu_pwesent_mask) {
		handwew = pew_cpu_ptw(&pwic_handwews, cpu);
		kfwee(handwew->enabwe_save);
	}
out_fwee_pwiowity_weg:
	kfwee(pwiv->pwio_save);
out_iounmap:
	iounmap(pwiv->wegs);
out_fwee_pwiv:
	kfwee(pwiv);
	wetuwn ewwow;
}

static int __init pwic_init(stwuct device_node *node,
			    stwuct device_node *pawent)
{
	wetuwn __pwic_init(node, pawent, 0);
}

IWQCHIP_DECWAWE(sifive_pwic, "sifive,pwic-1.0.0", pwic_init);
IWQCHIP_DECWAWE(wiscv_pwic0, "wiscv,pwic0", pwic_init); /* fow wegacy systems */

static int __init pwic_edge_init(stwuct device_node *node,
				 stwuct device_node *pawent)
{
	wetuwn __pwic_init(node, pawent, BIT(PWIC_QUIWK_EDGE_INTEWWUPT));
}

IWQCHIP_DECWAWE(andestech_ncepwic100, "andestech,ncepwic100", pwic_edge_init);
IWQCHIP_DECWAWE(thead_c900_pwic, "thead,c900-pwic", pwic_edge_init);
