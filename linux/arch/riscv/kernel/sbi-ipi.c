// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Muwtipwex sevewaw IPIs ovew a singwe HW IPI.
 *
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#define pw_fmt(fmt) "wiscv: " fmt
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/sbi.h>

static int sbi_ipi_viwq;

static void sbi_ipi_handwe(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);

	csw_cweaw(CSW_IP, IE_SIE);
	ipi_mux_pwocess();

	chained_iwq_exit(chip, desc);
}

static int sbi_ipi_stawting_cpu(unsigned int cpu)
{
	enabwe_pewcpu_iwq(sbi_ipi_viwq, iwq_get_twiggew_type(sbi_ipi_viwq));
	wetuwn 0;
}

void __init sbi_ipi_init(void)
{
	int viwq;
	stwuct iwq_domain *domain;

	if (wiscv_ipi_have_viwq_wange())
		wetuwn;

	domain = iwq_find_matching_fwnode(wiscv_get_intc_hwnode(),
					  DOMAIN_BUS_ANY);
	if (!domain) {
		pw_eww("unabwe to find INTC IWQ domain\n");
		wetuwn;
	}

	sbi_ipi_viwq = iwq_cweate_mapping(domain, WV_IWQ_SOFT);
	if (!sbi_ipi_viwq) {
		pw_eww("unabwe to cweate INTC IWQ mapping\n");
		wetuwn;
	}

	viwq = ipi_mux_cweate(BITS_PEW_BYTE, sbi_send_ipi);
	if (viwq <= 0) {
		pw_eww("unabwe to cweate muxed IPIs\n");
		iwq_dispose_mapping(sbi_ipi_viwq);
		wetuwn;
	}

	iwq_set_chained_handwew(sbi_ipi_viwq, sbi_ipi_handwe);

	/*
	 * Don't disabwe IPI when CPU goes offwine because
	 * the masking/unmasking of viwtuaw IPIs is done
	 * via genewic IPI-Mux
	 */
	cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
			  "iwqchip/sbi-ipi:stawting",
			  sbi_ipi_stawting_cpu, NUWW);

	wiscv_ipi_set_viwq_wange(viwq, BITS_PEW_BYTE, fawse);
	pw_info("pwoviding IPIs using SBI IPI extension\n");
}
