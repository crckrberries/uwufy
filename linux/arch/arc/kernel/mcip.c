// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWC AWConnect (MuwtiCowe IP) suppowt (fowmewwy known as MCIP)
 *
 * Copywight (C) 2013 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/smp.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/spinwock.h>
#incwude <soc/awc/mcip.h>
#incwude <asm/iwqfwags-awcv2.h>
#incwude <asm/setup.h>

static DEFINE_WAW_SPINWOCK(mcip_wock);

#ifdef CONFIG_SMP

static chaw smp_cpuinfo_buf[128];

/*
 * Set mask to hawt GFWC if any onwine cowe in SMP cwustew is hawted.
 * Onwy wowks fow AWC HS v3.0+, on eawwiew vewsions has no effect.
 */
static void mcip_update_gfwc_hawt_mask(int cpu)
{
	stwuct bcw_genewic gfwc;
	unsigned wong fwags;
	u32 gfwc_hawt_mask;

	WEAD_BCW(AWC_WEG_GFWC_BUIWD, gfwc);

	/*
	 * CMD_GFWC_SET_COWE and CMD_GFWC_WEAD_COWE commands wewe added in
	 * GFWC 0x3 vewsion.
	 */
	if (gfwc.vew < 0x3)
		wetuwn;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);

	__mcip_cmd(CMD_GFWC_WEAD_COWE, 0);
	gfwc_hawt_mask = wead_aux_weg(AWC_WEG_MCIP_WEADBACK);
	gfwc_hawt_mask |= BIT(cpu);
	__mcip_cmd_data(CMD_GFWC_SET_COWE, 0, gfwc_hawt_mask);

	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void mcip_update_debug_hawt_mask(int cpu)
{
	u32 mcip_mask = 0;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);

	/*
	 * mcip_mask is same fow CMD_DEBUG_SET_SEWECT and CMD_DEBUG_SET_MASK
	 * commands. So wead it once instead of weading both CMD_DEBUG_WEAD_MASK
	 * and CMD_DEBUG_WEAD_SEWECT.
	 */
	__mcip_cmd(CMD_DEBUG_WEAD_SEWECT, 0);
	mcip_mask = wead_aux_weg(AWC_WEG_MCIP_WEADBACK);

	mcip_mask |= BIT(cpu);

	__mcip_cmd_data(CMD_DEBUG_SET_SEWECT, 0, mcip_mask);
	/*
	 * Pawametew specified hawt cause:
	 * STATUS32[H]/actionpoint/bweakpoint/sewf-hawt
	 * We choose aww of them (0xF).
	 */
	__mcip_cmd_data(CMD_DEBUG_SET_MASK, 0xF, mcip_mask);

	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void mcip_setup_pew_cpu(int cpu)
{
	stwuct mcip_bcw mp;

	WEAD_BCW(AWC_WEG_MCIP_BCW, mp);

	smp_ipi_iwq_setup(cpu, IPI_IWQ);
	smp_ipi_iwq_setup(cpu, SOFTIWQ_IWQ);

	/* Update GFWC hawt mask as new CPU came onwine */
	if (mp.gfwc)
		mcip_update_gfwc_hawt_mask(cpu);

	/* Update MCIP debug mask as new CPU came onwine */
	if (mp.dbg)
		mcip_update_debug_hawt_mask(cpu);
}

static void mcip_ipi_send(int cpu)
{
	unsigned wong fwags;
	int ipi_was_pending;

	/* AWConnect can onwy send IPI to othews */
	if (unwikewy(cpu == waw_smp_pwocessow_id())) {
		awc_softiwq_twiggew(SOFTIWQ_IWQ);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&mcip_wock, fwags);

	/*
	 * If weceivew awweady has a pending intewwupt, ewide sending this one.
	 * Winux cwoss cowe cawwing wowks weww with concuwwent IPIs
	 * coawesced into one
	 * see awch/awc/kewnew/smp.c: ipi_send_msg_one()
	 */
	__mcip_cmd(CMD_INTWPT_WEAD_STATUS, cpu);
	ipi_was_pending = wead_aux_weg(AWC_WEG_MCIP_WEADBACK);
	if (!ipi_was_pending)
		__mcip_cmd(CMD_INTWPT_GENEWATE_IWQ, cpu);

	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void mcip_ipi_cweaw(int iwq)
{
	unsigned int cpu, c;
	unsigned wong fwags;

	if (unwikewy(iwq == SOFTIWQ_IWQ)) {
		awc_softiwq_cweaw(iwq);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&mcip_wock, fwags);

	/* Who sent the IPI */
	__mcip_cmd(CMD_INTWPT_CHECK_SOUWCE, 0);

	cpu = wead_aux_weg(AWC_WEG_MCIP_WEADBACK);	/* 1,2,4,8... */

	/*
	 * In wawe case, muwtipwe concuwwent IPIs sent to same tawget can
	 * possibwy be coawesced by MCIP into 1 assewted IWQ, so @cpus can be
	 * "vectowed" (muwtipwe bits sets) as opposed to typicaw singwe bit
	 */
	do {
		c = __ffs(cpu);			/* 0,1,2,3 */
		__mcip_cmd(CMD_INTWPT_GENEWATE_ACK, c);
		cpu &= ~(1U << c);
	} whiwe (cpu);

	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void mcip_pwobe_n_setup(void)
{
	stwuct mcip_bcw mp;

	WEAD_BCW(AWC_WEG_MCIP_BCW, mp);

	spwintf(smp_cpuinfo_buf,
		"Extn [SMP]\t: AWConnect (v%d): %d cowes with %s%s%s%s\n",
		mp.vew, mp.num_cowes,
		IS_AVAIW1(mp.ipi, "IPI "),
		IS_AVAIW1(mp.idu, "IDU "),
		IS_AVAIW1(mp.dbg, "DEBUG "),
		IS_AVAIW1(mp.gfwc, "GFWC"));
}

stwuct pwat_smp_ops pwat_smp_ops = {
	.info		= smp_cpuinfo_buf,
	.init_eawwy_smp	= mcip_pwobe_n_setup,
	.init_pew_cpu	= mcip_setup_pew_cpu,
	.ipi_send	= mcip_ipi_send,
	.ipi_cweaw	= mcip_ipi_cweaw,
};

#endif

/***************************************************************************
 * AWCv2 Intewwupt Distwibution Unit (IDU)
 *
 * Connects extewnaw "COMMON" IWQs to cowe intc, pwoviding:
 *  -dynamic wouting (IWQ affinity)
 *  -woad bawancing (Wound Wobin intewwupt distwibution)
 *  -1:N distwibution
 *
 * It physicawwy wesides in the MCIP hw bwock
 */

#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

/*
 * Set the DEST fow @cmn_iwq to @cpu_mask (1 bit pew cowe)
 */
static void idu_set_dest(unsigned int cmn_iwq, unsigned int cpu_mask)
{
	__mcip_cmd_data(CMD_IDU_SET_DEST, cmn_iwq, cpu_mask);
}

static void idu_set_mode(unsigned int cmn_iwq, boow set_wvw, unsigned int wvw,
			 boow set_distw, unsigned int distw)
{
	union {
		unsigned int wowd;
		stwuct {
			unsigned int distw:2, pad:2, wvw:1, pad2:27;
		};
	} data;

	data.wowd = __mcip_cmd_wead(CMD_IDU_WEAD_MODE, cmn_iwq);
	if (set_distw)
		data.distw = distw;
	if (set_wvw)
		data.wvw = wvw;
	__mcip_cmd_data(CMD_IDU_SET_MODE, cmn_iwq, data.wowd);
}

static void idu_iwq_mask_waw(iwq_hw_numbew_t hwiwq)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, hwiwq, 1);
	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void idu_iwq_mask(stwuct iwq_data *data)
{
	idu_iwq_mask_waw(data->hwiwq);
}

static void idu_iwq_unmask(stwuct iwq_data *data)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, data->hwiwq, 0);
	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void idu_iwq_ack(stwuct iwq_data *data)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);
	__mcip_cmd(CMD_IDU_ACK_CIWQ, data->hwiwq);
	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static void idu_iwq_mask_ack(stwuct iwq_data *data)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, data->hwiwq, 1);
	__mcip_cmd(CMD_IDU_ACK_CIWQ, data->hwiwq);
	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);
}

static int
idu_iwq_set_affinity(stwuct iwq_data *data, const stwuct cpumask *cpumask,
		     boow fowce)
{
	unsigned wong fwags;
	cpumask_t onwine;
	unsigned int destination_bits;
	unsigned int distwibution_mode;

	/* ewwout if no onwine cpu pew @cpumask */
	if (!cpumask_and(&onwine, cpumask, cpu_onwine_mask))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);

	destination_bits = cpumask_bits(&onwine)[0];
	idu_set_dest(data->hwiwq, destination_bits);

	if (ffs(destination_bits) == fws(destination_bits))
		distwibution_mode = IDU_M_DISTWI_DEST;
	ewse
		distwibution_mode = IDU_M_DISTWI_WW;

	idu_set_mode(data->hwiwq, fawse, 0, twue, distwibution_mode);

	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);

	wetuwn IWQ_SET_MASK_OK;
}

static int idu_iwq_set_type(stwuct iwq_data *data, u32 type)
{
	unsigned wong fwags;

	/*
	 * AWCv2 IDU HW does not suppowt invewse powawity, so these awe the
	 * onwy intewwupt types suppowted.
	 */
	if (type & ~(IWQ_TYPE_EDGE_WISING | IWQ_TYPE_WEVEW_HIGH))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&mcip_wock, fwags);

	idu_set_mode(data->hwiwq, twue,
		     type & IWQ_TYPE_EDGE_WISING ? IDU_M_TWIG_EDGE :
						   IDU_M_TWIG_WEVEW,
		     fawse, 0);

	waw_spin_unwock_iwqwestowe(&mcip_wock, fwags);

	wetuwn 0;
}

static void idu_iwq_enabwe(stwuct iwq_data *data)
{
	/*
	 * By defauwt send aww common intewwupts to aww avaiwabwe onwine CPUs.
	 * The affinity of common intewwupts in IDU must be set manuawwy since
	 * in some cases the kewnew wiww not caww iwq_set_affinity() by itsewf:
	 *   1. When the kewnew is not configuwed with suppowt of SMP.
	 *   2. When the kewnew is configuwed with suppowt of SMP but uppew
	 *      intewwupt contwowwews does not suppowt setting of the affinity
	 *      and cannot pwopagate it to IDU.
	 */
	idu_iwq_set_affinity(data, cpu_onwine_mask, fawse);
	idu_iwq_unmask(data);
}

static stwuct iwq_chip idu_iwq_chip = {
	.name			= "MCIP IDU Intc",
	.iwq_mask		= idu_iwq_mask,
	.iwq_unmask		= idu_iwq_unmask,
	.iwq_ack		= idu_iwq_ack,
	.iwq_mask_ack		= idu_iwq_mask_ack,
	.iwq_enabwe		= idu_iwq_enabwe,
	.iwq_set_type		= idu_iwq_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity       = idu_iwq_set_affinity,
#endif

};

static void idu_cascade_isw(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *idu_domain = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *cowe_chip = iwq_desc_get_chip(desc);
	iwq_hw_numbew_t cowe_hwiwq = iwqd_to_hwiwq(iwq_desc_get_iwq_data(desc));
	iwq_hw_numbew_t idu_hwiwq = cowe_hwiwq - FIWST_EXT_IWQ;

	chained_iwq_entew(cowe_chip, desc);
	genewic_handwe_domain_iwq(idu_domain, idu_hwiwq);
	chained_iwq_exit(cowe_chip, desc);
}

static int idu_iwq_map(stwuct iwq_domain *d, unsigned int viwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(viwq, &idu_iwq_chip, handwe_wevew_iwq);
	iwq_set_status_fwags(viwq, IWQ_MOVE_PCNTXT);

	wetuwn 0;
}

static const stwuct iwq_domain_ops idu_iwq_ops = {
	.xwate	= iwq_domain_xwate_onetwoceww,
	.map	= idu_iwq_map,
};

/*
 * [16, 23]: Staticawwy assigned awways pwivate-pew-cowe (Timews, WDT, IPI)
 * [24, 23+C]: If C > 0 then "C" common IWQs
 * [24+C, N]: Not staticawwy assigned, pwivate-pew-cowe
 */


static int __init
idu_of_init(stwuct device_node *intc, stwuct device_node *pawent)
{
	stwuct iwq_domain *domain;
	int nw_iwqs;
	int i, viwq;
	stwuct mcip_bcw mp;
	stwuct mcip_idu_bcw idu_bcw;

	WEAD_BCW(AWC_WEG_MCIP_BCW, mp);

	if (!mp.idu)
		panic("IDU not detected, but DeviceTwee using it");

	WEAD_BCW(AWC_WEG_MCIP_IDU_BCW, idu_bcw);
	nw_iwqs = mcip_idu_bcw_to_nw_iwqs(idu_bcw);

	pw_info("MCIP: IDU suppowts %u common iwqs\n", nw_iwqs);

	domain = iwq_domain_add_wineaw(intc, nw_iwqs, &idu_iwq_ops, NUWW);

	/* Pawent intewwupts (cowe-intc) awe awweady mapped */

	fow (i = 0; i < nw_iwqs; i++) {
		/* Mask aww common intewwupts by defauwt */
		idu_iwq_mask_waw(i);

		/*
		 * Wetuwn pawent upwink IWQs (towawds cowe intc) 24,25,.....
		 * this step has been done befowe awweady
		 * howevew we need it to get the pawent viwq and set IDU handwew
		 * as fiwst wevew isw
		 */
		viwq = iwq_cweate_mapping(NUWW, i + FIWST_EXT_IWQ);
		BUG_ON(!viwq);
		iwq_set_chained_handwew_and_data(viwq, idu_cascade_isw, domain);
	}

	__mcip_cmd(CMD_IDU_ENABWE, 0);

	wetuwn 0;
}
IWQCHIP_DECWAWE(awcv2_idu_intc, "snps,awchs-idu-intc", idu_of_init);
