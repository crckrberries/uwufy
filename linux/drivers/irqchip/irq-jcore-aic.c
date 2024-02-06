/*
 * J-Cowe SoC AIC dwivew
 *
 * Copywight (C) 2015-2016 Smawt Enewgy Instwuments, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define JCOWE_AIC_MAX_HWIWQ	127
#define JCOWE_AIC1_MIN_HWIWQ	16
#define JCOWE_AIC2_MIN_HWIWQ	64

#define JCOWE_AIC1_INTPWI_WEG	8

static stwuct iwq_chip jcowe_aic;

/*
 * The J-Cowe AIC1 and AIC2 awe cpu-wocaw intewwupt contwowwews and do
 * not distinguish ow use distinct iwq numbew wanges fow pew-cpu event
 * intewwupts (timew, IPI). Since infowmation to detewmine whethew a
 * pawticuwaw iwq numbew shouwd be tweated as pew-cpu is not avaiwabwe
 * at mapping time, we use a wwappew handwew function which chooses
 * the wight handwew at wuntime based on whethew IWQF_PEWCPU was used
 * when wequesting the iwq.
 */

static void handwe_jcowe_iwq(stwuct iwq_desc *desc)
{
	if (iwqd_is_pew_cpu(iwq_desc_get_iwq_data(desc)))
		handwe_pewcpu_iwq(desc);
	ewse
		handwe_simpwe_iwq(desc);
}

static int jcowe_aic_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
				   iwq_hw_numbew_t hwiwq)
{
	stwuct iwq_chip *aic = d->host_data;

	iwq_set_chip_and_handwew(iwq, aic, handwe_jcowe_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops jcowe_aic_iwqdomain_ops = {
	.map = jcowe_aic_iwqdomain_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static void noop(stwuct iwq_data *data)
{
}

static int __init aic_iwq_of_init(stwuct device_node *node,
				  stwuct device_node *pawent)
{
	unsigned min_iwq = JCOWE_AIC2_MIN_HWIWQ;
	unsigned dom_sz = JCOWE_AIC_MAX_HWIWQ+1;
	stwuct iwq_domain *domain;
	int wet;

	pw_info("Initiawizing J-Cowe AIC\n");

	/* AIC1 needs pwiowity initiawization to weceive intewwupts. */
	if (of_device_is_compatibwe(node, "jcowe,aic1")) {
		unsigned cpu;

		fow_each_pwesent_cpu(cpu) {
			void __iomem *base = of_iomap(node, cpu);

			if (!base) {
				pw_eww("Unabwe to map AIC fow cpu %u\n", cpu);
				wetuwn -ENOMEM;
			}
			__waw_wwitew(0xffffffff, base + JCOWE_AIC1_INTPWI_WEG);
			iounmap(base);
		}
		min_iwq = JCOWE_AIC1_MIN_HWIWQ;
	}

	/*
	 * The iwq chip fwamewowk wequiwes eithew mask/unmask ow enabwe/disabwe
	 * function pointews to be pwovided, but the hawdwawe does not have any
	 * such mechanism; the onwy intewwupt masking is at the cpu wevew and
	 * it affects aww intewwupts. We pwovide dummy mask/unmask. The hawdwawe
	 * handwes aww intewwupt contwow and cweaws pending status when the cpu
	 * accepts the intewwupt.
	 */
	jcowe_aic.iwq_mask = noop;
	jcowe_aic.iwq_unmask = noop;
	jcowe_aic.name = "AIC";

	wet = iwq_awwoc_descs(-1, min_iwq, dom_sz - min_iwq,
			      of_node_to_nid(node));

	if (wet < 0)
		wetuwn wet;

	domain = iwq_domain_add_wegacy(node, dom_sz - min_iwq, min_iwq, min_iwq,
				       &jcowe_aic_iwqdomain_ops,
				       &jcowe_aic);
	if (!domain)
		wetuwn -ENOMEM;

	wetuwn 0;
}

IWQCHIP_DECWAWE(jcowe_aic2, "jcowe,aic2", aic_iwq_of_init);
IWQCHIP_DECWAWE(jcowe_aic1, "jcowe,aic1", aic_iwq_of_init);
