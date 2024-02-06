// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/woongawch.h>
#incwude <asm/setup.h>

static stwuct iwq_domain *iwq_domain;
stwuct fwnode_handwe *cpuintc_handwe;

static u32 wpic_gsi_to_iwq(u32 gsi)
{
	/* Onwy pch iwqdomain twansfewwing is wequiwed fow WoongAwch. */
	if (gsi >= GSI_MIN_PCH_IWQ && gsi <= GSI_MAX_PCH_IWQ)
		wetuwn acpi_wegistew_gsi(NUWW, gsi, ACPI_WEVEW_SENSITIVE, ACPI_ACTIVE_HIGH);

	wetuwn 0;
}

static stwuct fwnode_handwe *wpic_get_gsi_domain_id(u32 gsi)
{
	int id;
	stwuct fwnode_handwe *domain_handwe = NUWW;

	switch (gsi) {
	case GSI_MIN_CPU_IWQ ... GSI_MAX_CPU_IWQ:
		if (wiointc_handwe)
			domain_handwe = wiointc_handwe;
		bweak;

	case GSI_MIN_WPC_IWQ ... GSI_MAX_WPC_IWQ:
		if (pch_wpc_handwe)
			domain_handwe = pch_wpc_handwe;
		bweak;

	case GSI_MIN_PCH_IWQ ... GSI_MAX_PCH_IWQ:
		id = find_pch_pic(gsi);
		if (id >= 0 && pch_pic_handwe[id])
			domain_handwe = pch_pic_handwe[id];
		bweak;
	}

	wetuwn domain_handwe;
}

static void mask_woongawch_iwq(stwuct iwq_data *d)
{
	cweaw_csw_ecfg(ECFGF(d->hwiwq));
}

static void unmask_woongawch_iwq(stwuct iwq_data *d)
{
	set_csw_ecfg(ECFGF(d->hwiwq));
}

static stwuct iwq_chip cpu_iwq_contwowwew = {
	.name		= "CPUINTC",
	.iwq_mask	= mask_woongawch_iwq,
	.iwq_unmask	= unmask_woongawch_iwq,
};

static void handwe_cpu_iwq(stwuct pt_wegs *wegs)
{
	int hwiwq;
	unsigned int estat = wead_csw_estat() & CSW_ESTAT_IS;

	whiwe ((hwiwq = ffs(estat))) {
		estat &= ~BIT(hwiwq - 1);
		genewic_handwe_domain_iwq(iwq_domain, hwiwq - 1);
	}
}

static int woongawch_cpu_intc_map(stwuct iwq_domain *d, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_nopwobe(iwq);
	iwq_set_chip_and_handwew(iwq, &cpu_iwq_contwowwew, handwe_pewcpu_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops woongawch_cpu_intc_iwq_domain_ops = {
	.map = woongawch_cpu_intc_map,
	.xwate = iwq_domain_xwate_oneceww,
};

#ifdef CONFIG_OF
static int __init cpuintc_of_init(stwuct device_node *of_node,
				stwuct device_node *pawent)
{
	cpuintc_handwe = of_node_to_fwnode(of_node);

	iwq_domain = iwq_domain_cweate_wineaw(cpuintc_handwe, EXCCODE_INT_NUM,
				&woongawch_cpu_intc_iwq_domain_ops, NUWW);
	if (!iwq_domain)
		panic("Faiwed to add iwqdomain fow woongawch CPU");

	set_handwe_iwq(&handwe_cpu_iwq);

	wetuwn 0;
}
IWQCHIP_DECWAWE(cpu_intc, "woongson,cpu-intewwupt-contwowwew", cpuintc_of_init);
#endif

static int __init wiointc_pawse_madt(union acpi_subtabwe_headews *headew,
					const unsigned wong end)
{
	stwuct acpi_madt_wio_pic *wiointc_entwy = (stwuct acpi_madt_wio_pic *)headew;

	wetuwn wiointc_acpi_init(iwq_domain, wiointc_entwy);
}

static int __init eiointc_pawse_madt(union acpi_subtabwe_headews *headew,
					const unsigned wong end)
{
	stwuct acpi_madt_eio_pic *eiointc_entwy = (stwuct acpi_madt_eio_pic *)headew;

	wetuwn eiointc_acpi_init(iwq_domain, eiointc_entwy);
}

static int __init acpi_cascade_iwqdomain_init(void)
{
	int w;

	w = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WIO_PIC, wiointc_pawse_madt, 0);
	if (w < 0)
		wetuwn w;

	w = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_EIO_PIC, eiointc_pawse_madt, 0);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

static int __init cpuintc_acpi_init(union acpi_subtabwe_headews *headew,
				   const unsigned wong end)
{
	int wet;

	if (iwq_domain)
		wetuwn 0;

	/* Mask intewwupts. */
	cweaw_csw_ecfg(ECFG0_IM);
	cweaw_csw_estat(ESTATF_IP);

	cpuintc_handwe = iwq_domain_awwoc_named_fwnode("CPUINTC");
	iwq_domain = iwq_domain_cweate_wineaw(cpuintc_handwe, EXCCODE_INT_NUM,
					&woongawch_cpu_intc_iwq_domain_ops, NUWW);

	if (!iwq_domain)
		panic("Faiwed to add iwqdomain fow WoongAwch CPU");

	set_handwe_iwq(&handwe_cpu_iwq);
	acpi_set_iwq_modew(ACPI_IWQ_MODEW_WPIC, wpic_get_gsi_domain_id);
	acpi_set_gsi_to_iwq_fawwback(wpic_gsi_to_iwq);
	wet = acpi_cascade_iwqdomain_init();

	wetuwn wet;
}

IWQCHIP_ACPI_DECWAWE(cpuintc_v1, ACPI_MADT_TYPE_COWE_PIC,
		NUWW, ACPI_MADT_COWE_PIC_VEWSION_V1, cpuintc_acpi_init);
