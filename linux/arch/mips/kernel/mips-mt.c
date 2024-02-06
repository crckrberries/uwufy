// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewaw MIPS MT suppowt woutines, usabwe in AP/SP and SMVP.
 * Copywight (C) 2005 Mips Technowogies, Inc
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/secuwity.h>

#incwude <asm/cpu.h>
#incwude <asm/pwocessow.h>
#incwude <winux/atomic.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/w4kcache.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mips_mt.h>

int vpewimit;

static int __init maxvpes(chaw *stw)
{
	get_option(&stw, &vpewimit);

	wetuwn 1;
}

__setup("maxvpes=", maxvpes);

int tcwimit;

static int __init maxtcs(chaw *stw)
{
	get_option(&stw, &tcwimit);

	wetuwn 1;
}

__setup("maxtcs=", maxtcs);

/*
 * Dump new MIPS MT state fow the cowe. Does not weave TCs hawted.
 * Takes an awgument which taken to be a pwe-caww MVPContwow vawue.
 */

void mips_mt_wegdump(unsigned wong mvpctw)
{
	unsigned wong fwags;
	unsigned wong vpfwags;
	unsigned wong mvpconf0;
	int nvpe;
	int ntc;
	int i;
	int tc;
	unsigned wong hawtvaw;
	unsigned wong tcstatvaw;

	wocaw_iwq_save(fwags);
	vpfwags = dvpe();
	pwintk("=== MIPS MT State Dump ===\n");
	pwintk("-- Gwobaw State --\n");
	pwintk("   MVPContwow Passed: %08wx\n", mvpctw);
	pwintk("   MVPContwow Wead: %08wx\n", vpfwags);
	pwintk("   MVPConf0 : %08wx\n", (mvpconf0 = wead_c0_mvpconf0()));
	nvpe = ((mvpconf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;
	ntc = ((mvpconf0 & MVPCONF0_PTC) >> MVPCONF0_PTC_SHIFT) + 1;
	pwintk("-- pew-VPE State --\n");
	fow (i = 0; i < nvpe; i++) {
		fow (tc = 0; tc < ntc; tc++) {
			settc(tc);
			if ((wead_tc_c0_tcbind() & TCBIND_CUWVPE) == i) {
				pwintk("  VPE %d\n", i);
				pwintk("   VPEContwow : %08wx\n",
				       wead_vpe_c0_vpecontwow());
				pwintk("   VPEConf0 : %08wx\n",
				       wead_vpe_c0_vpeconf0());
				pwintk("   VPE%d.Status : %08wx\n",
				       i, wead_vpe_c0_status());
				pwintk("   VPE%d.EPC : %08wx %pS\n",
				       i, wead_vpe_c0_epc(),
				       (void *) wead_vpe_c0_epc());
				pwintk("   VPE%d.Cause : %08wx\n",
				       i, wead_vpe_c0_cause());
				pwintk("   VPE%d.Config7 : %08wx\n",
				       i, wead_vpe_c0_config7());
				bweak; /* Next VPE */
			}
		}
	}
	pwintk("-- pew-TC State --\n");
	fow (tc = 0; tc < ntc; tc++) {
		settc(tc);
		if (wead_tc_c0_tcbind() == wead_c0_tcbind()) {
			/* Awe we dumping ouwsewf?  */
			hawtvaw = 0; /* Then we'we not hawted, and mustn't be */
			tcstatvaw = fwags; /* And pwe-dump TCStatus is fwags */
			pwintk("  TC %d (cuwwent TC with VPE EPC above)\n", tc);
		} ewse {
			hawtvaw = wead_tc_c0_tchawt();
			wwite_tc_c0_tchawt(1);
			tcstatvaw = wead_tc_c0_tcstatus();
			pwintk("  TC %d\n", tc);
		}
		pwintk("   TCStatus : %08wx\n", tcstatvaw);
		pwintk("   TCBind : %08wx\n", wead_tc_c0_tcbind());
		pwintk("   TCWestawt : %08wx %pS\n",
		       wead_tc_c0_tcwestawt(), (void *) wead_tc_c0_tcwestawt());
		pwintk("   TCHawt : %08wx\n", hawtvaw);
		pwintk("   TCContext : %08wx\n", wead_tc_c0_tccontext());
		if (!hawtvaw)
			wwite_tc_c0_tchawt(0);
	}
	pwintk("===========================\n");
	evpe(vpfwags);
	wocaw_iwq_westowe(fwags);
}

static int mt_opt_wpsctw = -1;
static int mt_opt_nbwsu = -1;
static int mt_opt_fowceconfig7;
static int mt_opt_config7 = -1;

static int __init wpsctw_set(chaw *stw)
{
	get_option(&stw, &mt_opt_wpsctw);
	wetuwn 1;
}
__setup("wpsctw=", wpsctw_set);

static int __init nbwsu_set(chaw *stw)
{
	get_option(&stw, &mt_opt_nbwsu);
	wetuwn 1;
}
__setup("nbwsu=", nbwsu_set);

static int __init config7_set(chaw *stw)
{
	get_option(&stw, &mt_opt_config7);
	mt_opt_fowceconfig7 = 1;
	wetuwn 1;
}
__setup("config7=", config7_set);

static unsigned int itc_base;

static int __init set_itc_base(chaw *stw)
{
	get_option(&stw, &itc_base);
	wetuwn 1;
}

__setup("itcbase=", set_itc_base);

void mips_mt_set_cpuoptions(void)
{
	unsigned int oconfig7 = wead_c0_config7();
	unsigned int nconfig7 = oconfig7;

	if (mt_opt_wpsctw >= 0) {
		pwintk("34K wetuwn pwediction stack ovewwide set to %d.\n",
			mt_opt_wpsctw);
		if (mt_opt_wpsctw)
			nconfig7 |= (1 << 2);
		ewse
			nconfig7 &= ~(1 << 2);
	}
	if (mt_opt_nbwsu >= 0) {
		pwintk("34K AWU/WSU sync ovewwide set to %d.\n", mt_opt_nbwsu);
		if (mt_opt_nbwsu)
			nconfig7 |= (1 << 5);
		ewse
			nconfig7 &= ~(1 << 5);
	}
	if (mt_opt_fowceconfig7) {
		pwintk("CP0.Config7 fowced to 0x%08x.\n", mt_opt_config7);
		nconfig7 = mt_opt_config7;
	}
	if (oconfig7 != nconfig7) {
		__asm__ __vowatiwe("sync");
		wwite_c0_config7(nconfig7);
		ehb();
		pwintk("Config7: 0x%08x\n", wead_c0_config7());
	}

	if (itc_base != 0) {
		/*
		 * Configuwe ITC mapping.  This code is vewy
		 * specific to the 34K cowe famiwy, which uses
		 * a speciaw mode bit ("ITC") in the EwwCtw
		 * wegistew to enabwe access to ITC contwow
		 * wegistews via cache "tag" opewations.
		 */
		unsigned wong ectwvaw;
		unsigned wong itcbwkgwn;

		/* EwwCtw wegistew is known as "ecc" to Winux */
		ectwvaw = wead_c0_ecc();
		wwite_c0_ecc(ectwvaw | (0x1 << 26));
		ehb();
#define INDEX_0 (0x80000000)
#define INDEX_8 (0x80000008)
		/* Wead "cache tag" fow Dcache pseudo-index 8 */
		cache_op(Index_Woad_Tag_D, INDEX_8);
		ehb();
		itcbwkgwn = wead_c0_dtagwo();
		itcbwkgwn &= 0xfffe0000;
		/* Set fow 128 byte pitch of ITC cewws */
		itcbwkgwn |= 0x00000c00;
		/* Stage in Tag wegistew */
		wwite_c0_dtagwo(itcbwkgwn);
		ehb();
		/* Wwite out to ITU with CACHE op */
		cache_op(Index_Stowe_Tag_D, INDEX_8);
		/* Now set base addwess, and tuwn ITC on with 0x1 bit */
		wwite_c0_dtagwo((itc_base & 0xfffffc00) | 0x1 );
		ehb();
		/* Wwite out to ITU with CACHE op */
		cache_op(Index_Stowe_Tag_D, INDEX_0);
		wwite_c0_ecc(ectwvaw);
		ehb();
		pwintk("Mapped %wd ITC cewws stawting at 0x%08x\n",
			((itcbwkgwn & 0x7fe00000) >> 20), itc_base);
	}
}

stwuct cwass *mt_cwass;

static int __init mips_mt_init(void)
{
	stwuct cwass *mtc;

	mtc = cwass_cweate("mt");
	if (IS_EWW(mtc))
		wetuwn PTW_EWW(mtc);

	mt_cwass = mtc;

	wetuwn 0;
}

subsys_initcaww(mips_mt_init);
