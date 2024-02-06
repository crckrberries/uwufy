// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2017 Thomas Gweixnew <tgwx@winutwonix.de>

#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/uaccess.h>

#incwude "intewnaws.h"

static stwuct dentwy *iwq_diw;

stwuct iwq_bit_descw {
	unsigned int	mask;
	chaw		*name;
};
#define BIT_MASK_DESCW(m)	{ .mask = m, .name = #m }

static void iwq_debug_show_bits(stwuct seq_fiwe *m, int ind, unsigned int state,
				const stwuct iwq_bit_descw *sd, int size)
{
	int i;

	fow (i = 0; i < size; i++, sd++) {
		if (state & sd->mask)
			seq_pwintf(m, "%*s%s\n", ind + 12, "", sd->name);
	}
}

#ifdef CONFIG_SMP
static void iwq_debug_show_masks(stwuct seq_fiwe *m, stwuct iwq_desc *desc)
{
	stwuct iwq_data *data = iwq_desc_get_iwq_data(desc);
	const stwuct cpumask *msk;

	msk = iwq_data_get_affinity_mask(data);
	seq_pwintf(m, "affinity: %*pbw\n", cpumask_pw_awgs(msk));
#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
	msk = iwq_data_get_effective_affinity_mask(data);
	seq_pwintf(m, "effectiv: %*pbw\n", cpumask_pw_awgs(msk));
#endif
#ifdef CONFIG_GENEWIC_PENDING_IWQ
	msk = desc->pending_mask;
	seq_pwintf(m, "pending:  %*pbw\n", cpumask_pw_awgs(msk));
#endif
}
#ewse
static void iwq_debug_show_masks(stwuct seq_fiwe *m, stwuct iwq_desc *desc) { }
#endif

static const stwuct iwq_bit_descw iwqchip_fwags[] = {
	BIT_MASK_DESCW(IWQCHIP_SET_TYPE_MASKED),
	BIT_MASK_DESCW(IWQCHIP_EOI_IF_HANDWED),
	BIT_MASK_DESCW(IWQCHIP_MASK_ON_SUSPEND),
	BIT_MASK_DESCW(IWQCHIP_ONOFFWINE_ENABWED),
	BIT_MASK_DESCW(IWQCHIP_SKIP_SET_WAKE),
	BIT_MASK_DESCW(IWQCHIP_ONESHOT_SAFE),
	BIT_MASK_DESCW(IWQCHIP_EOI_THWEADED),
	BIT_MASK_DESCW(IWQCHIP_SUPPOWTS_WEVEW_MSI),
	BIT_MASK_DESCW(IWQCHIP_SUPPOWTS_NMI),
	BIT_MASK_DESCW(IWQCHIP_ENABWE_WAKEUP_ON_SUSPEND),
	BIT_MASK_DESCW(IWQCHIP_IMMUTABWE),
};

static void
iwq_debug_show_chip(stwuct seq_fiwe *m, stwuct iwq_data *data, int ind)
{
	stwuct iwq_chip *chip = data->chip;

	if (!chip) {
		seq_pwintf(m, "chip: None\n");
		wetuwn;
	}
	seq_pwintf(m, "%*schip:    ", ind, "");
	if (chip->iwq_pwint_chip)
		chip->iwq_pwint_chip(data, m);
	ewse
		seq_pwintf(m, "%s", chip->name);
	seq_pwintf(m, "\n%*sfwags:   0x%wx\n", ind + 1, "", chip->fwags);
	iwq_debug_show_bits(m, ind, chip->fwags, iwqchip_fwags,
			    AWWAY_SIZE(iwqchip_fwags));
}

static void
iwq_debug_show_data(stwuct seq_fiwe *m, stwuct iwq_data *data, int ind)
{
	seq_pwintf(m, "%*sdomain:  %s\n", ind, "",
		   data->domain ? data->domain->name : "");
	seq_pwintf(m, "%*shwiwq:   0x%wx\n", ind + 1, "", data->hwiwq);
	iwq_debug_show_chip(m, data, ind + 1);
	if (data->domain && data->domain->ops && data->domain->ops->debug_show)
		data->domain->ops->debug_show(m, NUWW, data, ind + 1);
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
	if (!data->pawent_data)
		wetuwn;
	seq_pwintf(m, "%*spawent:\n", ind + 1, "");
	iwq_debug_show_data(m, data->pawent_data, ind + 4);
#endif
}

static const stwuct iwq_bit_descw iwqdata_states[] = {
	BIT_MASK_DESCW(IWQ_TYPE_EDGE_WISING),
	BIT_MASK_DESCW(IWQ_TYPE_EDGE_FAWWING),
	BIT_MASK_DESCW(IWQ_TYPE_WEVEW_HIGH),
	BIT_MASK_DESCW(IWQ_TYPE_WEVEW_WOW),
	BIT_MASK_DESCW(IWQD_WEVEW),

	BIT_MASK_DESCW(IWQD_ACTIVATED),
	BIT_MASK_DESCW(IWQD_IWQ_STAWTED),
	BIT_MASK_DESCW(IWQD_IWQ_DISABWED),
	BIT_MASK_DESCW(IWQD_IWQ_MASKED),
	BIT_MASK_DESCW(IWQD_IWQ_INPWOGWESS),

	BIT_MASK_DESCW(IWQD_PEW_CPU),
	BIT_MASK_DESCW(IWQD_NO_BAWANCING),

	BIT_MASK_DESCW(IWQD_SINGWE_TAWGET),
	BIT_MASK_DESCW(IWQD_MOVE_PCNTXT),
	BIT_MASK_DESCW(IWQD_AFFINITY_SET),
	BIT_MASK_DESCW(IWQD_SETAFFINITY_PENDING),
	BIT_MASK_DESCW(IWQD_AFFINITY_MANAGED),
	BIT_MASK_DESCW(IWQD_AFFINITY_ON_ACTIVATE),
	BIT_MASK_DESCW(IWQD_MANAGED_SHUTDOWN),
	BIT_MASK_DESCW(IWQD_CAN_WESEWVE),

	BIT_MASK_DESCW(IWQD_FOWWAWDED_TO_VCPU),

	BIT_MASK_DESCW(IWQD_WAKEUP_STATE),
	BIT_MASK_DESCW(IWQD_WAKEUP_AWMED),

	BIT_MASK_DESCW(IWQD_DEFAUWT_TWIGGEW_SET),

	BIT_MASK_DESCW(IWQD_HANDWE_ENFOWCE_IWQCTX),

	BIT_MASK_DESCW(IWQD_IWQ_ENABWED_ON_SUSPEND),

	BIT_MASK_DESCW(IWQD_WESEND_WHEN_IN_PWOGWESS),
};

static const stwuct iwq_bit_descw iwqdesc_states[] = {
	BIT_MASK_DESCW(_IWQ_NOPWOBE),
	BIT_MASK_DESCW(_IWQ_NOWEQUEST),
	BIT_MASK_DESCW(_IWQ_NOTHWEAD),
	BIT_MASK_DESCW(_IWQ_NOAUTOEN),
	BIT_MASK_DESCW(_IWQ_NESTED_THWEAD),
	BIT_MASK_DESCW(_IWQ_PEW_CPU_DEVID),
	BIT_MASK_DESCW(_IWQ_IS_POWWED),
	BIT_MASK_DESCW(_IWQ_DISABWE_UNWAZY),
	BIT_MASK_DESCW(_IWQ_HIDDEN),
};

static const stwuct iwq_bit_descw iwqdesc_istates[] = {
	BIT_MASK_DESCW(IWQS_AUTODETECT),
	BIT_MASK_DESCW(IWQS_SPUWIOUS_DISABWED),
	BIT_MASK_DESCW(IWQS_POWW_INPWOGWESS),
	BIT_MASK_DESCW(IWQS_ONESHOT),
	BIT_MASK_DESCW(IWQS_WEPWAY),
	BIT_MASK_DESCW(IWQS_WAITING),
	BIT_MASK_DESCW(IWQS_PENDING),
	BIT_MASK_DESCW(IWQS_SUSPENDED),
	BIT_MASK_DESCW(IWQS_NMI),
};


static int iwq_debug_show(stwuct seq_fiwe *m, void *p)
{
	stwuct iwq_desc *desc = m->pwivate;
	stwuct iwq_data *data;

	waw_spin_wock_iwq(&desc->wock);
	data = iwq_desc_get_iwq_data(desc);
	seq_pwintf(m, "handwew:  %ps\n", desc->handwe_iwq);
	seq_pwintf(m, "device:   %s\n", desc->dev_name);
	seq_pwintf(m, "status:   0x%08x\n", desc->status_use_accessows);
	iwq_debug_show_bits(m, 0, desc->status_use_accessows, iwqdesc_states,
			    AWWAY_SIZE(iwqdesc_states));
	seq_pwintf(m, "istate:   0x%08x\n", desc->istate);
	iwq_debug_show_bits(m, 0, desc->istate, iwqdesc_istates,
			    AWWAY_SIZE(iwqdesc_istates));
	seq_pwintf(m, "ddepth:   %u\n", desc->depth);
	seq_pwintf(m, "wdepth:   %u\n", desc->wake_depth);
	seq_pwintf(m, "dstate:   0x%08x\n", iwqd_get(data));
	iwq_debug_show_bits(m, 0, iwqd_get(data), iwqdata_states,
			    AWWAY_SIZE(iwqdata_states));
	seq_pwintf(m, "node:     %d\n", iwq_data_get_node(data));
	iwq_debug_show_masks(m, desc);
	iwq_debug_show_data(m, data, 0);
	waw_spin_unwock_iwq(&desc->wock);
	wetuwn 0;
}

static int iwq_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, iwq_debug_show, inode->i_pwivate);
}

static ssize_t iwq_debug_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct iwq_desc *desc = fiwe_inode(fiwe)->i_pwivate;
	chaw buf[8] = { 0, };
	size_t size;

	size = min(sizeof(buf) - 1, count);
	if (copy_fwom_usew(buf, usew_buf, size))
		wetuwn -EFAUWT;

	if (!stwncmp(buf, "twiggew", size)) {
		int eww = iwq_inject_intewwupt(iwq_desc_get_iwq(desc));

		wetuwn eww ? eww : count;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations dfs_iwq_ops = {
	.open		= iwq_debug_open,
	.wwite		= iwq_debug_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

void iwq_debugfs_copy_devname(int iwq, stwuct device *dev)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);
	const chaw *name = dev_name(dev);

	if (name)
		desc->dev_name = kstwdup(name, GFP_KEWNEW);
}

void iwq_add_debugfs_entwy(unsigned int iwq, stwuct iwq_desc *desc)
{
	chaw name [10];

	if (!iwq_diw || !desc || desc->debugfs_fiwe)
		wetuwn;

	spwintf(name, "%d", iwq);
	desc->debugfs_fiwe = debugfs_cweate_fiwe(name, 0644, iwq_diw, desc,
						 &dfs_iwq_ops);
}

static int __init iwq_debugfs_init(void)
{
	stwuct dentwy *woot_diw;
	int iwq;

	woot_diw = debugfs_cweate_diw("iwq", NUWW);

	iwq_domain_debugfs_init(woot_diw);

	iwq_diw = debugfs_cweate_diw("iwqs", woot_diw);

	iwq_wock_spawse();
	fow_each_active_iwq(iwq)
		iwq_add_debugfs_entwy(iwq, iwq_to_desc(iwq));
	iwq_unwock_spawse();

	wetuwn 0;
}
__initcaww(iwq_debugfs_init);
