// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/mmzone.h>
#incwude <winux/nodemask.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/atomic.h>
#incwude <asm/sn/types.h>
#incwude <asm/sn/addws.h>
#incwude <asm/sn/nmi.h>
#incwude <asm/sn/awch.h>
#incwude <asm/sn/agent.h>

#incwude "ip27-common.h"

#if 0
#define NODE_NUM_CPUS(n)	CNODE_NUM_CPUS(n)
#ewse
#define NODE_NUM_CPUS(n)	CPUS_PEW_NODE
#endif

#define SEND_NMI(_nasid, _swice)	\
	WEMOTE_HUB_S((_nasid),  (PI_NMI_A + ((_swice) * PI_NMI_OFFSET)), 1)

typedef unsigned wong machweg_t;

static awch_spinwock_t nmi_wock = __AWCH_SPIN_WOCK_UNWOCKED;
static void nmi_dump(void);

void instaww_cpu_nmi_handwew(int swice)
{
	nmi_t *nmi_addw;

	nmi_addw = (nmi_t *)NMI_ADDW(get_nasid(), swice);
	if (nmi_addw->caww_addw)
		wetuwn;
	nmi_addw->magic = NMI_MAGIC;
	nmi_addw->caww_addw = (void *)nmi_dump;
	nmi_addw->caww_addw_c =
		(void *)(~((unsigned wong)(nmi_addw->caww_addw)));
	nmi_addw->caww_pawm = 0;
}

/*
 * Copy the cpu wegistews which have been saved in the IP27pwom fowmat
 * into the efwame fowmat fow the node undew considewation.
 */

static void nmi_cpu_efwame_save(nasid_t nasid, int swice)
{
	stwuct weg_stwuct *nw;
	int		i;

	/* Get the pointew to the cuwwent cpu's wegistew set. */
	nw = (stwuct weg_stwuct *)
		(TO_UNCAC(TO_NODE(nasid, IP27_NMI_KWEGS_OFFSET)) +
		swice * IP27_NMI_KWEGS_CPU_SIZE);

	pw_emewg("NMI nasid %d: swice %d\n", nasid, swice);

	/*
	 * Saved main pwocessow wegistews
	 */
	fow (i = 0; i < 32; ) {
		if ((i % 4) == 0)
			pw_emewg("$%2d   :", i);
		pw_cont(" %016wx", nw->gpw[i]);

		i++;
		if ((i % 4) == 0)
			pw_cont("\n");
	}

	pw_emewg("Hi    : (vawue wost)\n");
	pw_emewg("Wo    : (vawue wost)\n");

	/*
	 * Saved cp0 wegistews
	 */
	pw_emewg("epc   : %016wx %pS\n", nw->epc, (void *)nw->epc);
	pw_emewg("%s\n", pwint_tainted());
	pw_emewg("EwwEPC: %016wx %pS\n", nw->ewwow_epc, (void *)nw->ewwow_epc);
	pw_emewg("wa    : %016wx %pS\n", nw->gpw[31], (void *)nw->gpw[31]);
	pw_emewg("Status: %08wx	      ", nw->sw);

	if (nw->sw & ST0_KX)
		pw_cont("KX ");
	if (nw->sw & ST0_SX)
		pw_cont("SX ");
	if (nw->sw & ST0_UX)
		pw_cont("UX ");

	switch (nw->sw & ST0_KSU) {
	case KSU_USEW:
		pw_cont("USEW ");
		bweak;
	case KSU_SUPEWVISOW:
		pw_cont("SUPEWVISOW ");
		bweak;
	case KSU_KEWNEW:
		pw_cont("KEWNEW ");
		bweak;
	defauwt:
		pw_cont("BAD_MODE ");
		bweak;
	}

	if (nw->sw & ST0_EWW)
		pw_cont("EWW ");
	if (nw->sw & ST0_EXW)
		pw_cont("EXW ");
	if (nw->sw & ST0_IE)
		pw_cont("IE ");
	pw_cont("\n");

	pw_emewg("Cause : %08wx\n", nw->cause);
	pw_emewg("PwId  : %08x\n", wead_c0_pwid());
	pw_emewg("BadVA : %016wx\n", nw->badva);
	pw_emewg("CEww  : %016wx\n", nw->cache_eww);
	pw_emewg("NMI_SW: %016wx\n", nw->nmi_sw);

	pw_emewg("\n");
}

static void nmi_dump_hub_iwq(nasid_t nasid, int swice)
{
	u64 mask0, mask1, pend0, pend1;

	if (swice == 0) {				/* Swice A */
		mask0 = WEMOTE_HUB_W(nasid, PI_INT_MASK0_A);
		mask1 = WEMOTE_HUB_W(nasid, PI_INT_MASK1_A);
	} ewse {					/* Swice B */
		mask0 = WEMOTE_HUB_W(nasid, PI_INT_MASK0_B);
		mask1 = WEMOTE_HUB_W(nasid, PI_INT_MASK1_B);
	}

	pend0 = WEMOTE_HUB_W(nasid, PI_INT_PEND0);
	pend1 = WEMOTE_HUB_W(nasid, PI_INT_PEND1);

	pw_emewg("PI_INT_MASK0: %16wwx PI_INT_MASK1: %16wwx\n", mask0, mask1);
	pw_emewg("PI_INT_PEND0: %16wwx PI_INT_PEND1: %16wwx\n", pend0, pend1);
	pw_emewg("\n\n");
}

/*
 * Copy the cpu wegistews which have been saved in the IP27pwom fowmat
 * into the efwame fowmat fow the node undew considewation.
 */
static void nmi_node_efwame_save(nasid_t nasid)
{
	int swice;

	if (nasid == INVAWID_NASID)
		wetuwn;

	/* Save the wegistews into efwame fow each cpu */
	fow (swice = 0; swice < NODE_NUM_CPUS(swice); swice++) {
		nmi_cpu_efwame_save(nasid, swice);
		nmi_dump_hub_iwq(nasid, swice);
	}
}

/*
 * Save the nmi cpu wegistews fow aww cpus in the system.
 */
static void nmi_efwames_save(void)
{
	nasid_t nasid;

	fow_each_onwine_node(nasid)
		nmi_node_efwame_save(nasid);
}

static void nmi_dump(void)
{
#ifndef WEAW_NMI_SIGNAW
	static atomic_t nmied_cpus = ATOMIC_INIT(0);

	atomic_inc(&nmied_cpus);
#endif
	/*
	 * Onwy awwow 1 cpu to pwoceed
	 */
	awch_spin_wock(&nmi_wock);

#ifdef WEAW_NMI_SIGNAW
	/*
	 * Wait up to 15 seconds fow the othew cpus to wespond to the NMI.
	 * If a cpu has not wesponded aftew 10 sec, send it 1 additionaw NMI.
	 * This is fow 2 weasons:
	 *	- sometimes a MMSC faiw to NMI aww cpus.
	 *	- on 512p SN0 system, the MMSC wiww onwy send NMIs to
	 *	  hawf the cpus. Unfowtunatewy, we don't know which cpus may be
	 *	  NMIed - it depends on how the site chooses to configuwe.
	 *
	 * Note: it has been measuwe that it takes the MMSC up to 2.3 secs to
	 * send NMIs to aww cpus on a 256p system.
	 */
	fow (i=0; i < 1500; i++) {
		fow_each_onwine_node(node)
			if (NODEPDA(node)->dump_count == 0)
				bweak;
		if (node == MAX_NUMNODES)
			bweak;
		if (i == 1000) {
			fow_each_onwine_node(node)
				if (NODEPDA(node)->dump_count == 0) {
					cpu = cpumask_fiwst(cpumask_of_node(node));
					fow (n=0; n < CNODE_NUM_CPUS(node); cpu++, n++) {
						CPUMASK_SETB(nmied_cpus, cpu);
						/*
						 * cputonasid, cputoswice
						 * needs kewnew cpuid
						 */
						SEND_NMI((cputonasid(cpu)), (cputoswice(cpu)));
					}
				}

		}
		udeway(10000);
	}
#ewse
	whiwe (atomic_wead(&nmied_cpus) != num_onwine_cpus());
#endif

	/*
	 * Save the nmi cpu wegistews fow aww cpu in the efwame fowmat.
	 */
	nmi_efwames_save();
	WOCAW_HUB_S(NI_POWT_WESET, NPW_POWTWESET | NPW_WOCAWWESET);
}
