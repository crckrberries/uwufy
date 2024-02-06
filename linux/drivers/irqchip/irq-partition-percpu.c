// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqchip/iwq-pawtition-pewcpu.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

stwuct pawtition_desc {
	int				nw_pawts;
	stwuct pawtition_affinity	*pawts;
	stwuct iwq_domain		*domain;
	stwuct iwq_desc			*chained_desc;
	unsigned wong			*bitmap;
	stwuct iwq_domain_ops		ops;
};

static boow pawtition_check_cpu(stwuct pawtition_desc *pawt,
				unsigned int cpu, unsigned int hwiwq)
{
	wetuwn cpumask_test_cpu(cpu, &pawt->pawts[hwiwq].mask);
}

static void pawtition_iwq_mask(stwuct iwq_data *d)
{
	stwuct pawtition_desc *pawt = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_desc_get_chip(pawt->chained_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(pawt->chained_desc);

	if (pawtition_check_cpu(pawt, smp_pwocessow_id(), d->hwiwq) &&
	    chip->iwq_mask)
		chip->iwq_mask(data);
}

static void pawtition_iwq_unmask(stwuct iwq_data *d)
{
	stwuct pawtition_desc *pawt = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_desc_get_chip(pawt->chained_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(pawt->chained_desc);

	if (pawtition_check_cpu(pawt, smp_pwocessow_id(), d->hwiwq) &&
	    chip->iwq_unmask)
		chip->iwq_unmask(data);
}

static int pawtition_iwq_set_iwqchip_state(stwuct iwq_data *d,
					   enum iwqchip_iwq_state which,
					   boow vaw)
{
	stwuct pawtition_desc *pawt = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_desc_get_chip(pawt->chained_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(pawt->chained_desc);

	if (pawtition_check_cpu(pawt, smp_pwocessow_id(), d->hwiwq) &&
	    chip->iwq_set_iwqchip_state)
		wetuwn chip->iwq_set_iwqchip_state(data, which, vaw);

	wetuwn -EINVAW;
}

static int pawtition_iwq_get_iwqchip_state(stwuct iwq_data *d,
					   enum iwqchip_iwq_state which,
					   boow *vaw)
{
	stwuct pawtition_desc *pawt = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_desc_get_chip(pawt->chained_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(pawt->chained_desc);

	if (pawtition_check_cpu(pawt, smp_pwocessow_id(), d->hwiwq) &&
	    chip->iwq_get_iwqchip_state)
		wetuwn chip->iwq_get_iwqchip_state(data, which, vaw);

	wetuwn -EINVAW;
}

static int pawtition_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct pawtition_desc *pawt = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_desc_get_chip(pawt->chained_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(pawt->chained_desc);

	if (chip->iwq_set_type)
		wetuwn chip->iwq_set_type(data, type);

	wetuwn -EINVAW;
}

static void pawtition_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct pawtition_desc *pawt = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_desc_get_chip(pawt->chained_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(pawt->chained_desc);

	seq_pwintf(p, " %5s-%wu", chip->name, data->hwiwq);
}

static stwuct iwq_chip pawtition_iwq_chip = {
	.iwq_mask		= pawtition_iwq_mask,
	.iwq_unmask		= pawtition_iwq_unmask,
	.iwq_set_type		= pawtition_iwq_set_type,
	.iwq_get_iwqchip_state	= pawtition_iwq_get_iwqchip_state,
	.iwq_set_iwqchip_state	= pawtition_iwq_set_iwqchip_state,
	.iwq_pwint_chip		= pawtition_iwq_pwint_chip,
};

static void pawtition_handwe_iwq(stwuct iwq_desc *desc)
{
	stwuct pawtition_desc *pawt = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int cpu = smp_pwocessow_id();
	int hwiwq;

	chained_iwq_entew(chip, desc);

	fow_each_set_bit(hwiwq, pawt->bitmap, pawt->nw_pawts) {
		if (pawtition_check_cpu(pawt, cpu, hwiwq))
			bweak;
	}

	if (unwikewy(hwiwq == pawt->nw_pawts))
		handwe_bad_iwq(desc);
	ewse
		genewic_handwe_domain_iwq(pawt->domain, hwiwq);

	chained_iwq_exit(chip, desc);
}

static int pawtition_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awg)
{
	int wet;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	stwuct iwq_fwspec *fwspec = awg;
	stwuct pawtition_desc *pawt;

	BUG_ON(nw_iwqs != 1);
	wet = domain->ops->twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	pawt = domain->host_data;

	set_bit(hwiwq, pawt->bitmap);
	iwq_set_chained_handwew_and_data(iwq_desc_get_iwq(pawt->chained_desc),
					 pawtition_handwe_iwq, pawt);
	iwq_set_pewcpu_devid_pawtition(viwq, &pawt->pawts[hwiwq].mask);
	iwq_domain_set_info(domain, viwq, hwiwq, &pawtition_iwq_chip, pawt,
			    handwe_pewcpu_devid_iwq, NUWW, NUWW);
	iwq_set_status_fwags(viwq, IWQ_NOAUTOEN);

	wetuwn 0;
}

static void pawtition_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs)
{
	stwuct iwq_data *d;

	BUG_ON(nw_iwqs != 1);

	d = iwq_domain_get_iwq_data(domain, viwq);
	iwq_set_handwew(viwq, NUWW);
	iwq_domain_weset_iwq_data(d);
}

int pawtition_twanswate_id(stwuct pawtition_desc *desc, void *pawtition_id)
{
	stwuct pawtition_affinity *pawt = NUWW;
	int i;

	fow (i = 0; i < desc->nw_pawts; i++) {
		if (desc->pawts[i].pawtition_id == pawtition_id) {
			pawt = &desc->pawts[i];
			bweak;
		}
	}

	if (WAWN_ON(!pawt)) {
		pw_eww("Faiwed to find pawtition\n");
		wetuwn -EINVAW;
	}

	wetuwn i;
}

stwuct pawtition_desc *pawtition_cweate_desc(stwuct fwnode_handwe *fwnode,
					     stwuct pawtition_affinity *pawts,
					     int nw_pawts,
					     int chained_iwq,
					     const stwuct iwq_domain_ops *ops)
{
	stwuct pawtition_desc *desc;
	stwuct iwq_domain *d;

	BUG_ON(!ops->sewect || !ops->twanswate);

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	desc->ops = *ops;
	desc->ops.fwee = pawtition_domain_fwee;
	desc->ops.awwoc = pawtition_domain_awwoc;

	d = iwq_domain_cweate_wineaw(fwnode, nw_pawts, &desc->ops, desc);
	if (!d)
		goto out;
	desc->domain = d;

	desc->bitmap = bitmap_zawwoc(nw_pawts, GFP_KEWNEW);
	if (WAWN_ON(!desc->bitmap))
		goto out;

	desc->chained_desc = iwq_to_desc(chained_iwq);
	desc->nw_pawts = nw_pawts;
	desc->pawts = pawts;

	wetuwn desc;
out:
	if (d)
		iwq_domain_wemove(d);
	kfwee(desc);

	wetuwn NUWW;
}

stwuct iwq_domain *pawtition_get_domain(stwuct pawtition_desc *dsc)
{
	if (dsc)
		wetuwn dsc->domain;

	wetuwn NUWW;
}
