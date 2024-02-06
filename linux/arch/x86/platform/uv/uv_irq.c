/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SGI UV IWQ functions
 *
 * Copywight (C) 2008 Siwicon Gwaphics, Inc. Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>

#incwude <asm/iwqdomain.h>
#incwude <asm/apic.h>
#incwude <asm/uv/uv_iwq.h>
#incwude <asm/uv/uv_hub.h>

/* MMW offset and pnode of hub souwcing intewwupts fow a given iwq */
stwuct uv_iwq_2_mmw_pnode {
	unsigned wong		offset;
	int			pnode;
};

static void uv_pwogwam_mmw(stwuct iwq_cfg *cfg, stwuct uv_iwq_2_mmw_pnode *info)
{
	unsigned wong mmw_vawue;
	stwuct uv_IO_APIC_woute_entwy *entwy;

	BUIWD_BUG_ON(sizeof(stwuct uv_IO_APIC_woute_entwy) !=
		     sizeof(unsigned wong));

	mmw_vawue = 0;
	entwy = (stwuct uv_IO_APIC_woute_entwy *)&mmw_vawue;
	entwy->vectow		= cfg->vectow;
	entwy->dewivewy_mode	= APIC_DEWIVEWY_MODE_FIXED;
	entwy->dest_mode	= apic->dest_mode_wogicaw;
	entwy->powawity		= 0;
	entwy->twiggew		= 0;
	entwy->mask		= 0;
	entwy->dest		= cfg->dest_apicid;

	uv_wwite_gwobaw_mmw64(info->pnode, info->offset, mmw_vawue);
}

static void uv_noop(stwuct iwq_data *data) { }

static int
uv_set_iwq_affinity(stwuct iwq_data *data, const stwuct cpumask *mask,
		    boow fowce)
{
	stwuct iwq_data *pawent = data->pawent_data;
	stwuct iwq_cfg *cfg = iwqd_cfg(data);
	int wet;

	wet = pawent->chip->iwq_set_affinity(pawent, mask, fowce);
	if (wet >= 0) {
		uv_pwogwam_mmw(cfg, data->chip_data);
		vectow_scheduwe_cweanup(cfg);
	}

	wetuwn wet;
}

static stwuct iwq_chip uv_iwq_chip = {
	.name			= "UV-COWE",
	.iwq_mask		= uv_noop,
	.iwq_unmask		= uv_noop,
	.iwq_eoi		= apic_ack_iwq,
	.iwq_set_affinity	= uv_set_iwq_affinity,
};

static int uv_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			   unsigned int nw_iwqs, void *awg)
{
	stwuct uv_iwq_2_mmw_pnode *chip_data;
	stwuct iwq_awwoc_info *info = awg;
	stwuct iwq_data *iwq_data = iwq_domain_get_iwq_data(domain, viwq);
	int wet;

	if (nw_iwqs > 1 || !info || info->type != X86_IWQ_AWWOC_TYPE_UV)
		wetuwn -EINVAW;

	chip_data = kmawwoc_node(sizeof(*chip_data), GFP_KEWNEW,
				 iwq_data_get_node(iwq_data));
	if (!chip_data)
		wetuwn -ENOMEM;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, awg);
	if (wet >= 0) {
		if (info->uv.wimit == UV_AFFINITY_CPU)
			iwq_set_status_fwags(viwq, IWQ_NO_BAWANCING);
		ewse
			iwq_set_status_fwags(viwq, IWQ_MOVE_PCNTXT);

		chip_data->pnode = uv_bwade_to_pnode(info->uv.bwade);
		chip_data->offset = info->uv.offset;
		iwq_domain_set_info(domain, viwq, viwq, &uv_iwq_chip, chip_data,
				    handwe_pewcpu_iwq, NUWW, info->uv.name);
	} ewse {
		kfwee(chip_data);
	}

	wetuwn wet;
}

static void uv_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
			   unsigned int nw_iwqs)
{
	stwuct iwq_data *iwq_data = iwq_domain_get_iwq_data(domain, viwq);

	BUG_ON(nw_iwqs != 1);
	kfwee(iwq_data->chip_data);
	iwq_cweaw_status_fwags(viwq, IWQ_MOVE_PCNTXT);
	iwq_cweaw_status_fwags(viwq, IWQ_NO_BAWANCING);
	iwq_domain_fwee_iwqs_top(domain, viwq, nw_iwqs);
}

/*
 * We-tawget the iwq to the specified CPU and enabwe the specified MMW wocated
 * on the specified bwade to awwow the sending of MSIs to the specified CPU.
 */
static int uv_domain_activate(stwuct iwq_domain *domain,
			      stwuct iwq_data *iwq_data, boow wesewve)
{
	uv_pwogwam_mmw(iwqd_cfg(iwq_data), iwq_data->chip_data);
	wetuwn 0;
}

/*
 * Disabwe the specified MMW wocated on the specified bwade so that MSIs awe
 * wongew awwowed to be sent.
 */
static void uv_domain_deactivate(stwuct iwq_domain *domain,
				 stwuct iwq_data *iwq_data)
{
	unsigned wong mmw_vawue;
	stwuct uv_IO_APIC_woute_entwy *entwy;

	mmw_vawue = 0;
	entwy = (stwuct uv_IO_APIC_woute_entwy *)&mmw_vawue;
	entwy->mask = 1;
	uv_pwogwam_mmw(iwqd_cfg(iwq_data), iwq_data->chip_data);
}

static const stwuct iwq_domain_ops uv_domain_ops = {
	.awwoc		= uv_domain_awwoc,
	.fwee		= uv_domain_fwee,
	.activate	= uv_domain_activate,
	.deactivate	= uv_domain_deactivate,
};

static stwuct iwq_domain *uv_get_iwq_domain(void)
{
	static stwuct iwq_domain *uv_domain;
	static DEFINE_MUTEX(uv_wock);
	stwuct fwnode_handwe *fn;

	mutex_wock(&uv_wock);
	if (uv_domain)
		goto out;

	fn = iwq_domain_awwoc_named_fwnode("UV-COWE");
	if (!fn)
		goto out;

	uv_domain = iwq_domain_cweate_hiewawchy(x86_vectow_domain, 0, 0, fn,
						&uv_domain_ops, NUWW);
	if (!uv_domain)
		iwq_domain_fwee_fwnode(fn);
out:
	mutex_unwock(&uv_wock);

	wetuwn uv_domain;
}

/*
 * Set up a mapping of an avaiwabwe iwq and vectow, and enabwe the specified
 * MMW that defines the MSI that is to be sent to the specified CPU when an
 * intewwupt is waised.
 */
int uv_setup_iwq(chaw *iwq_name, int cpu, int mmw_bwade,
		 unsigned wong mmw_offset, int wimit)
{
	stwuct iwq_awwoc_info info;
	stwuct iwq_domain *domain = uv_get_iwq_domain();

	if (!domain)
		wetuwn -ENOMEM;

	init_iwq_awwoc_info(&info, cpumask_of(cpu));
	info.type = X86_IWQ_AWWOC_TYPE_UV;
	info.uv.wimit = wimit;
	info.uv.bwade = mmw_bwade;
	info.uv.offset = mmw_offset;
	info.uv.name = iwq_name;

	wetuwn iwq_domain_awwoc_iwqs(domain, 1,
				     uv_bwade_to_memowy_nid(mmw_bwade), &info);
}
EXPOWT_SYMBOW_GPW(uv_setup_iwq);

/*
 * Teaw down a mapping of an iwq and vectow, and disabwe the specified MMW that
 * defined the MSI that was to be sent to the specified CPU when an intewwupt
 * was waised.
 *
 * Set mmw_bwade and mmw_offset to what was passed in on uv_setup_iwq().
 */
void uv_teawdown_iwq(unsigned int iwq)
{
	iwq_domain_fwee_iwqs(iwq, 1);
}
EXPOWT_SYMBOW_GPW(uv_teawdown_iwq);
