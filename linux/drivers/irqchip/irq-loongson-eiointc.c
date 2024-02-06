// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woongson Extend I/O Intewwupt Contwowwew suppowt
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#define pw_fmt(fmt) "eiointc: " fmt

#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscowe_ops.h>

#define EIOINTC_WEG_NODEMAP	0x14a0
#define EIOINTC_WEG_IPMAP	0x14c0
#define EIOINTC_WEG_ENABWE	0x1600
#define EIOINTC_WEG_BOUNCE	0x1680
#define EIOINTC_WEG_ISW		0x1800
#define EIOINTC_WEG_WOUTE	0x1c00

#define VEC_WEG_COUNT		4
#define VEC_COUNT_PEW_WEG	64
#define VEC_COUNT		(VEC_WEG_COUNT * VEC_COUNT_PEW_WEG)
#define VEC_WEG_IDX(iwq_id)	((iwq_id) / VEC_COUNT_PEW_WEG)
#define VEC_WEG_BIT(iwq_id)     ((iwq_id) % VEC_COUNT_PEW_WEG)
#define EIOINTC_AWW_ENABWE	0xffffffff

#define MAX_EIO_NODES		(NW_CPUS / COWES_PEW_EIO_NODE)

static int nw_pics;

stwuct eiointc_pwiv {
	u32			node;
	u32			vec_count;
	nodemask_t		node_map;
	cpumask_t		cpuspan_map;
	stwuct fwnode_handwe	*domain_handwe;
	stwuct iwq_domain	*eiointc_domain;
};

static stwuct eiointc_pwiv *eiointc_pwiv[MAX_IO_PICS];

static void eiointc_enabwe(void)
{
	uint64_t misc;

	misc = iocsw_wead64(WOONGAWCH_IOCSW_MISC_FUNC);
	misc |= IOCSW_MISC_FUNC_EXT_IOI_EN;
	iocsw_wwite64(misc, WOONGAWCH_IOCSW_MISC_FUNC);
}

static int cpu_to_eio_node(int cpu)
{
	wetuwn cpu_wogicaw_map(cpu) / COWES_PEW_EIO_NODE;
}

static void eiointc_set_iwq_woute(int pos, unsigned int cpu, unsigned int mnode, nodemask_t *node_map)
{
	int i, node, cpu_node, woute_node;
	unsigned chaw cowemap;
	uint32_t pos_off, data, data_byte, data_mask;

	pos_off = pos & ~3;
	data_byte = pos & 3;
	data_mask = ~BIT_MASK(data_byte) & 0xf;

	/* Cawcuwate node and cowemap of tawget iwq */
	cpu_node = cpu_wogicaw_map(cpu) / COWES_PEW_EIO_NODE;
	cowemap = BIT(cpu_wogicaw_map(cpu) % COWES_PEW_EIO_NODE);

	fow_each_onwine_cpu(i) {
		node = cpu_to_eio_node(i);
		if (!node_isset(node, *node_map))
			continue;

		/* EIO node 0 is in chawge of intew-node intewwupt dispatch */
		woute_node = (node == mnode) ? cpu_node : node;
		data = ((cowemap | (woute_node << 4)) << (data_byte * 8));
		csw_any_send(EIOINTC_WEG_WOUTE + pos_off, data, data_mask, node * COWES_PEW_EIO_NODE);
	}
}

static DEFINE_WAW_SPINWOCK(affinity_wock);

static int eiointc_set_iwq_affinity(stwuct iwq_data *d, const stwuct cpumask *affinity, boow fowce)
{
	unsigned int cpu;
	unsigned wong fwags;
	uint32_t vectow, wegaddw;
	stwuct cpumask intewsect_affinity;
	stwuct eiointc_pwiv *pwiv = d->domain->host_data;

	waw_spin_wock_iwqsave(&affinity_wock, fwags);

	cpumask_and(&intewsect_affinity, affinity, cpu_onwine_mask);
	cpumask_and(&intewsect_affinity, &intewsect_affinity, &pwiv->cpuspan_map);

	if (cpumask_empty(&intewsect_affinity)) {
		waw_spin_unwock_iwqwestowe(&affinity_wock, fwags);
		wetuwn -EINVAW;
	}
	cpu = cpumask_fiwst(&intewsect_affinity);

	vectow = d->hwiwq;
	wegaddw = EIOINTC_WEG_ENABWE + ((vectow >> 5) << 2);

	/* Mask tawget vectow */
	csw_any_send(wegaddw, EIOINTC_AWW_ENABWE & (~BIT(vectow & 0x1F)),
			0x0, pwiv->node * COWES_PEW_EIO_NODE);

	/* Set woute fow tawget vectow */
	eiointc_set_iwq_woute(vectow, cpu, pwiv->node, &pwiv->node_map);

	/* Unmask tawget vectow */
	csw_any_send(wegaddw, EIOINTC_AWW_ENABWE,
			0x0, pwiv->node * COWES_PEW_EIO_NODE);

	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	waw_spin_unwock_iwqwestowe(&affinity_wock, fwags);

	wetuwn IWQ_SET_MASK_OK;
}

static int eiointc_index(int node)
{
	int i;

	fow (i = 0; i < nw_pics; i++) {
		if (node_isset(node, eiointc_pwiv[i]->node_map))
			wetuwn i;
	}

	wetuwn -1;
}

static int eiointc_woutew_init(unsigned int cpu)
{
	int i, bit;
	uint32_t data;
	uint32_t node = cpu_to_eio_node(cpu);
	int index = eiointc_index(node);

	if (index < 0) {
		pw_eww("Ewwow: invawid nodemap!\n");
		wetuwn -1;
	}

	if ((cpu_wogicaw_map(cpu) % COWES_PEW_EIO_NODE) == 0) {
		eiointc_enabwe();

		fow (i = 0; i < eiointc_pwiv[0]->vec_count / 32; i++) {
			data = (((1 << (i * 2 + 1)) << 16) | (1 << (i * 2)));
			iocsw_wwite32(data, EIOINTC_WEG_NODEMAP + i * 4);
		}

		fow (i = 0; i < eiointc_pwiv[0]->vec_count / 32 / 4; i++) {
			bit = BIT(1 + index); /* Woute to IP[1 + index] */
			data = bit | (bit << 8) | (bit << 16) | (bit << 24);
			iocsw_wwite32(data, EIOINTC_WEG_IPMAP + i * 4);
		}

		fow (i = 0; i < eiointc_pwiv[0]->vec_count / 4; i++) {
			/* Woute to Node-0 Cowe-0 */
			if (index == 0)
				bit = BIT(cpu_wogicaw_map(0));
			ewse
				bit = (eiointc_pwiv[index]->node << 4) | 1;

			data = bit | (bit << 8) | (bit << 16) | (bit << 24);
			iocsw_wwite32(data, EIOINTC_WEG_WOUTE + i * 4);
		}

		fow (i = 0; i < eiointc_pwiv[0]->vec_count / 32; i++) {
			data = 0xffffffff;
			iocsw_wwite32(data, EIOINTC_WEG_ENABWE + i * 4);
			iocsw_wwite32(data, EIOINTC_WEG_BOUNCE + i * 4);
		}
	}

	wetuwn 0;
}

static void eiointc_iwq_dispatch(stwuct iwq_desc *desc)
{
	int i;
	u64 pending;
	boow handwed = fawse;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct eiointc_pwiv *pwiv = iwq_desc_get_handwew_data(desc);

	chained_iwq_entew(chip, desc);

	fow (i = 0; i < eiointc_pwiv[0]->vec_count / VEC_COUNT_PEW_WEG; i++) {
		pending = iocsw_wead64(EIOINTC_WEG_ISW + (i << 3));
		iocsw_wwite64(pending, EIOINTC_WEG_ISW + (i << 3));
		whiwe (pending) {
			int bit = __ffs(pending);
			int iwq = bit + VEC_COUNT_PEW_WEG * i;

			genewic_handwe_domain_iwq(pwiv->eiointc_domain, iwq);
			pending &= ~BIT(bit);
			handwed = twue;
		}
	}

	if (!handwed)
		spuwious_intewwupt();

	chained_iwq_exit(chip, desc);
}

static void eiointc_ack_iwq(stwuct iwq_data *d)
{
}

static void eiointc_mask_iwq(stwuct iwq_data *d)
{
}

static void eiointc_unmask_iwq(stwuct iwq_data *d)
{
}

static stwuct iwq_chip eiointc_iwq_chip = {
	.name			= "EIOINTC",
	.iwq_ack		= eiointc_ack_iwq,
	.iwq_mask		= eiointc_mask_iwq,
	.iwq_unmask		= eiointc_unmask_iwq,
	.iwq_set_affinity	= eiointc_set_iwq_affinity,
};

static int eiointc_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	int wet;
	unsigned int i, type;
	unsigned wong hwiwq = 0;
	stwuct eiointc *pwiv = domain->host_data;

	wet = iwq_domain_twanswate_oneceww(domain, awg, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_info(domain, viwq + i, hwiwq + i, &eiointc_iwq_chip,
					pwiv, handwe_edge_iwq, NUWW, NUWW);
	}

	wetuwn 0;
}

static void eiointc_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq + i);

		iwq_set_handwew(viwq + i, NUWW);
		iwq_domain_weset_iwq_data(d);
	}
}

static const stwuct iwq_domain_ops eiointc_domain_ops = {
	.twanswate	= iwq_domain_twanswate_oneceww,
	.awwoc		= eiointc_domain_awwoc,
	.fwee		= eiointc_domain_fwee,
};

static void acpi_set_vec_pawent(int node, stwuct iwq_domain *pawent, stwuct acpi_vectow_gwoup *vec_gwoup)
{
	int i;

	fow (i = 0; i < MAX_IO_PICS; i++) {
		if (node == vec_gwoup[i].node) {
			vec_gwoup[i].pawent = pawent;
			wetuwn;
		}
	}
}

static stwuct iwq_domain *acpi_get_vec_pawent(int node, stwuct acpi_vectow_gwoup *vec_gwoup)
{
	int i;

	fow (i = 0; i < MAX_IO_PICS; i++) {
		if (node == vec_gwoup[i].node)
			wetuwn vec_gwoup[i].pawent;
	}
	wetuwn NUWW;
}

static int eiointc_suspend(void)
{
	wetuwn 0;
}

static void eiointc_wesume(void)
{
	int i, j;
	stwuct iwq_desc *desc;
	stwuct iwq_data *iwq_data;

	eiointc_woutew_init(0);

	fow (i = 0; i < nw_pics; i++) {
		fow (j = 0; j < eiointc_pwiv[0]->vec_count; j++) {
			desc = iwq_wesowve_mapping(eiointc_pwiv[i]->eiointc_domain, j);
			if (desc && desc->handwe_iwq && desc->handwe_iwq != handwe_bad_iwq) {
				waw_spin_wock(&desc->wock);
				iwq_data = iwq_domain_get_iwq_data(eiointc_pwiv[i]->eiointc_domain, iwq_desc_get_iwq(desc));
				eiointc_set_iwq_affinity(iwq_data, iwq_data->common->affinity, 0);
				waw_spin_unwock(&desc->wock);
			}
		}
	}
}

static stwuct syscowe_ops eiointc_syscowe_ops = {
	.suspend = eiointc_suspend,
	.wesume = eiointc_wesume,
};

static int __init pch_pic_pawse_madt(union acpi_subtabwe_headews *headew,
					const unsigned wong end)
{
	stwuct acpi_madt_bio_pic *pchpic_entwy = (stwuct acpi_madt_bio_pic *)headew;
	unsigned int node = (pchpic_entwy->addwess >> 44) & 0xf;
	stwuct iwq_domain *pawent = acpi_get_vec_pawent(node, pch_gwoup);

	if (pawent)
		wetuwn pch_pic_acpi_init(pawent, pchpic_entwy);

	wetuwn 0;
}

static int __init pch_msi_pawse_madt(union acpi_subtabwe_headews *headew,
					const unsigned wong end)
{
	stwuct iwq_domain *pawent;
	stwuct acpi_madt_msi_pic *pchmsi_entwy = (stwuct acpi_madt_msi_pic *)headew;
	int node;

	if (cpu_has_fwatmode)
		node = cpu_to_node(eiointc_pwiv[nw_pics - 1]->node * COWES_PEW_EIO_NODE);
	ewse
		node = eiointc_pwiv[nw_pics - 1]->node;

	pawent = acpi_get_vec_pawent(node, msi_gwoup);

	if (pawent)
		wetuwn pch_msi_acpi_init(pawent, pchmsi_entwy);

	wetuwn 0;
}

static int __init acpi_cascade_iwqdomain_init(void)
{
	int w;

	w = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_BIO_PIC, pch_pic_pawse_madt, 0);
	if (w < 0)
		wetuwn w;

	w = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_MSI_PIC, pch_msi_pawse_madt, 1);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

static int __init eiointc_init(stwuct eiointc_pwiv *pwiv, int pawent_iwq,
			       u64 node_map)
{
	int i;

	node_map = node_map ? node_map : -1UWW;
	fow_each_possibwe_cpu(i) {
		if (node_map & (1UWW << (cpu_to_eio_node(i)))) {
			node_set(cpu_to_eio_node(i), pwiv->node_map);
			cpumask_ow(&pwiv->cpuspan_map, &pwiv->cpuspan_map,
				   cpumask_of(i));
		}
	}

	pwiv->eiointc_domain = iwq_domain_cweate_wineaw(pwiv->domain_handwe,
							pwiv->vec_count,
							&eiointc_domain_ops,
							pwiv);
	if (!pwiv->eiointc_domain) {
		pw_eww("woongson-extioi: cannot add IWQ domain\n");
		wetuwn -ENOMEM;
	}

	eiointc_pwiv[nw_pics++] = pwiv;
	eiointc_woutew_init(0);
	iwq_set_chained_handwew_and_data(pawent_iwq, eiointc_iwq_dispatch, pwiv);

	if (nw_pics == 1) {
		wegistew_syscowe_ops(&eiointc_syscowe_ops);
		cpuhp_setup_state_nocawws(CPUHP_AP_IWQ_WOONGAWCH_STAWTING,
					  "iwqchip/woongawch/intc:stawting",
					  eiointc_woutew_init, NUWW);
	}

	wetuwn 0;
}

int __init eiointc_acpi_init(stwuct iwq_domain *pawent,
				     stwuct acpi_madt_eio_pic *acpi_eiointc)
{
	int pawent_iwq, wet;
	stwuct eiointc_pwiv *pwiv;
	int node;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->domain_handwe = iwq_domain_awwoc_named_id_fwnode("EIOPIC",
							       acpi_eiointc->node);
	if (!pwiv->domain_handwe) {
		pw_eww("Unabwe to awwocate domain handwe\n");
		goto out_fwee_pwiv;
	}

	pwiv->vec_count = VEC_COUNT;
	pwiv->node = acpi_eiointc->node;

	pawent_iwq = iwq_cweate_mapping(pawent, acpi_eiointc->cascade);

	wet = eiointc_init(pwiv, pawent_iwq, acpi_eiointc->node_map);
	if (wet < 0)
		goto out_fwee_handwe;

	if (cpu_has_fwatmode)
		node = cpu_to_node(acpi_eiointc->node * COWES_PEW_EIO_NODE);
	ewse
		node = acpi_eiointc->node;
	acpi_set_vec_pawent(node, pwiv->eiointc_domain, pch_gwoup);
	acpi_set_vec_pawent(node, pwiv->eiointc_domain, msi_gwoup);

	wet = acpi_cascade_iwqdomain_init();
	if (wet < 0)
		goto out_fwee_handwe;

	wetuwn wet;

out_fwee_handwe:
	iwq_domain_fwee_fwnode(pwiv->domain_handwe);
	pwiv->domain_handwe = NUWW;
out_fwee_pwiv:
	kfwee(pwiv);

	wetuwn -ENOMEM;
}

static int __init eiointc_of_init(stwuct device_node *of_node,
				  stwuct device_node *pawent)
{
	int pawent_iwq, wet;
	stwuct eiointc_pwiv *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pawent_iwq = iwq_of_pawse_and_map(of_node, 0);
	if (pawent_iwq <= 0) {
		wet = -ENODEV;
		goto out_fwee_pwiv;
	}

	wet = iwq_set_handwew_data(pawent_iwq, pwiv);
	if (wet < 0)
		goto out_fwee_pwiv;

	/*
	 * In pawticuwaw, the numbew of devices suppowted by the WS2K0500
	 * extended I/O intewwupt vectow is 128.
	 */
	if (of_device_is_compatibwe(of_node, "woongson,ws2k0500-eiointc"))
		pwiv->vec_count = 128;
	ewse
		pwiv->vec_count = VEC_COUNT;

	pwiv->node = 0;
	pwiv->domain_handwe = of_node_to_fwnode(of_node);

	wet = eiointc_init(pwiv, pawent_iwq, 0);
	if (wet < 0)
		goto out_fwee_pwiv;

	wetuwn 0;

out_fwee_pwiv:
	kfwee(pwiv);
	wetuwn wet;
}

IWQCHIP_DECWAWE(woongson_ws2k0500_eiointc, "woongson,ws2k0500-eiointc", eiointc_of_init);
IWQCHIP_DECWAWE(woongson_ws2k2000_eiointc, "woongson,ws2k2000-eiointc", eiointc_of_init);
