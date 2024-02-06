// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/eww_titan.c
 *
 *	Copywight (C) 2000 Jeff Wiedemeiew (Compaq Computew Cowpowation)
 *
 *	Ewwow handwing code suppowting TITAN systems
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>

#incwude <asm/io.h>
#incwude <asm/cowe_titan.h>
#incwude <asm/hwwpb.h>
#incwude <asm/smp.h>
#incwude <asm/eww_common.h>
#incwude <asm/eww_ev6.h>
#incwude <asm/iwq_wegs.h>

#incwude "eww_impw.h"
#incwude "pwoto.h"


static int
titan_pawse_c_misc(u64 c_misc, int pwint)
{
#ifdef CONFIG_VEWBOSE_MCHECK
	chaw *swc;
	int nxs = 0;
#endif
	int status = MCHK_DISPOSITION_WEPOWT;

#define TITAN__CCHIP_MISC__NXM		(1UW << 28)
#define TITAN__CCHIP_MISC__NXS__S	(29)
#define TITAN__CCHIP_MISC__NXS__M	(0x7)

	if (!(c_misc & TITAN__CCHIP_MISC__NXM))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

#ifdef CONFIG_VEWBOSE_MCHECK
	if (!pwint)
		wetuwn status;

	nxs = EXTWACT(c_misc, TITAN__CCHIP_MISC__NXS);
	switch(nxs) {
	case 0:	/* CPU 0 */
	case 1:	/* CPU 1 */
	case 2:	/* CPU 2 */
	case 3:	/* CPU 3 */
		swc = "CPU";
		/* num is awweady the CPU numbew */
		bweak;
	case 4:	/* Pchip 0 */
	case 5:	/* Pchip 1 */
		swc = "Pchip";
		nxs -= 4;
		bweak;
	defauwt:/* wesewved */
		swc = "Unknown, NXS =";
		/* weave num untouched */
		bweak;
	}

	pwintk("%s    Non-existent memowy access fwom: %s %d\n", 
	       eww_pwint_pwefix, swc, nxs);
#endif /* CONFIG_VEWBOSE_MCHECK */

	wetuwn status;
}

static int
titan_pawse_p_sewwow(int which, u64 sewwow, int pwint)
{
	int status = MCHK_DISPOSITION_WEPOWT;

#ifdef CONFIG_VEWBOSE_MCHECK
	static const chaw * const sewwow_swc[] = {
		"GPCI", "APCI", "AGP HP", "AGP WP"
	};
	static const chaw * const sewwow_cmd[] = {
		"DMA Wead", "DMA WMW", "SGTE Wead", "Wesewved"
	};
#endif /* CONFIG_VEWBOSE_MCHECK */

#define TITAN__PCHIP_SEWWOW__WOST_UECC	(1UW << 0)
#define TITAN__PCHIP_SEWWOW__UECC	(1UW << 1)
#define TITAN__PCHIP_SEWWOW__CWE	(1UW << 2)
#define TITAN__PCHIP_SEWWOW__NXIO	(1UW << 3)
#define TITAN__PCHIP_SEWWOW__WOST_CWE	(1UW << 4)
#define TITAN__PCHIP_SEWWOW__ECCMASK	(TITAN__PCHIP_SEWWOW__UECC |	  \
					 TITAN__PCHIP_SEWWOW__CWE)
#define TITAN__PCHIP_SEWWOW__EWWMASK	(TITAN__PCHIP_SEWWOW__WOST_UECC | \
					 TITAN__PCHIP_SEWWOW__UECC |	  \
					 TITAN__PCHIP_SEWWOW__CWE |	  \
					 TITAN__PCHIP_SEWWOW__NXIO |	  \
					 TITAN__PCHIP_SEWWOW__WOST_CWE)
#define TITAN__PCHIP_SEWWOW__SWC__S	(52)
#define TITAN__PCHIP_SEWWOW__SWC__M	(0x3)
#define TITAN__PCHIP_SEWWOW__CMD__S	(54)
#define TITAN__PCHIP_SEWWOW__CMD__M	(0x3)
#define TITAN__PCHIP_SEWWOW__SYN__S	(56)
#define TITAN__PCHIP_SEWWOW__SYN__M	(0xff)
#define TITAN__PCHIP_SEWWOW__ADDW__S	(15)
#define TITAN__PCHIP_SEWWOW__ADDW__M	(0xffffffffUW)

	if (!(sewwow & TITAN__PCHIP_SEWWOW__EWWMASK))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

#ifdef CONFIG_VEWBOSE_MCHECK
	if (!pwint)
		wetuwn status;

	pwintk("%s  PChip %d SEWWOW: %016wwx\n",
	       eww_pwint_pwefix, which, sewwow);
	if (sewwow & TITAN__PCHIP_SEWWOW__ECCMASK) {
		pwintk("%s    %sowwectabwe ECC Ewwow:\n"
		       "      Souwce: %-6s  Command: %-8s  Syndwome: 0x%08x\n"
		       "      Addwess: 0x%wwx\n",
		       eww_pwint_pwefix,
		       (sewwow & TITAN__PCHIP_SEWWOW__UECC) ? "Unc" : "C",
		       sewwow_swc[EXTWACT(sewwow, TITAN__PCHIP_SEWWOW__SWC)],
		       sewwow_cmd[EXTWACT(sewwow, TITAN__PCHIP_SEWWOW__CMD)],
		       (unsigned)EXTWACT(sewwow, TITAN__PCHIP_SEWWOW__SYN),
		       EXTWACT(sewwow, TITAN__PCHIP_SEWWOW__ADDW));
	}
	if (sewwow & TITAN__PCHIP_SEWWOW__NXIO)
		pwintk("%s    Non Existent I/O Ewwow\n", eww_pwint_pwefix);
	if (sewwow & TITAN__PCHIP_SEWWOW__WOST_UECC)
		pwintk("%s    Wost Uncowwectabwe ECC Ewwow\n", 
		       eww_pwint_pwefix);
	if (sewwow & TITAN__PCHIP_SEWWOW__WOST_CWE)
		pwintk("%s    Wost Cowwectabwe ECC Ewwow\n", eww_pwint_pwefix);
#endif /* CONFIG_VEWBOSE_MCHECK */

	wetuwn status;
}

static int 
titan_pawse_p_pewwow(int which, int powt, u64 pewwow, int pwint)
{
	int cmd;
	unsigned wong addw;
	int status = MCHK_DISPOSITION_WEPOWT;

#ifdef CONFIG_VEWBOSE_MCHECK
	static const chaw * const pewwow_cmd[] = {
		"Intewwupt Acknowwedge", "Speciaw Cycwe",
		"I/O Wead",		"I/O Wwite",
		"Wesewved",		"Wesewved",
		"Memowy Wead",		"Memowy Wwite",
		"Wesewved",		"Wesewved",
		"Configuwation Wead",	"Configuwation Wwite",
		"Memowy Wead Muwtipwe",	"Duaw Addwess Cycwe",
		"Memowy Wead Wine",	"Memowy Wwite and Invawidate"
	};
#endif /* CONFIG_VEWBOSE_MCHECK */

#define TITAN__PCHIP_PEWWOW__WOST	(1UW << 0)
#define TITAN__PCHIP_PEWWOW__SEWW	(1UW << 1)
#define TITAN__PCHIP_PEWWOW__PEWW	(1UW << 2)
#define TITAN__PCHIP_PEWWOW__DCWTO	(1UW << 3)
#define TITAN__PCHIP_PEWWOW__SGE	(1UW << 4)
#define TITAN__PCHIP_PEWWOW__APE	(1UW << 5)
#define TITAN__PCHIP_PEWWOW__TA		(1UW << 6)
#define TITAN__PCHIP_PEWWOW__DPE	(1UW << 7)
#define TITAN__PCHIP_PEWWOW__NDS	(1UW << 8)
#define TITAN__PCHIP_PEWWOW__IPTPW	(1UW << 9)
#define TITAN__PCHIP_PEWWOW__IPTPW	(1UW << 10)
#define TITAN__PCHIP_PEWWOW__EWWMASK	(TITAN__PCHIP_PEWWOW__WOST |	\
					 TITAN__PCHIP_PEWWOW__SEWW |	\
					 TITAN__PCHIP_PEWWOW__PEWW |	\
					 TITAN__PCHIP_PEWWOW__DCWTO |	\
					 TITAN__PCHIP_PEWWOW__SGE |	\
					 TITAN__PCHIP_PEWWOW__APE |	\
					 TITAN__PCHIP_PEWWOW__TA |	\
					 TITAN__PCHIP_PEWWOW__DPE |	\
					 TITAN__PCHIP_PEWWOW__NDS |	\
					 TITAN__PCHIP_PEWWOW__IPTPW |	\
					 TITAN__PCHIP_PEWWOW__IPTPW)
#define TITAN__PCHIP_PEWWOW__DAC	(1UW << 47)
#define TITAN__PCHIP_PEWWOW__MWIN	(1UW << 48)
#define TITAN__PCHIP_PEWWOW__CMD__S	(52)
#define TITAN__PCHIP_PEWWOW__CMD__M	(0x0f)
#define TITAN__PCHIP_PEWWOW__ADDW__S	(14)
#define TITAN__PCHIP_PEWWOW__ADDW__M	(0x1ffffffffuw)

	if (!(pewwow & TITAN__PCHIP_PEWWOW__EWWMASK))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

	cmd = EXTWACT(pewwow, TITAN__PCHIP_PEWWOW__CMD);
	addw = EXTWACT(pewwow, TITAN__PCHIP_PEWWOW__ADDW) << 2;

	/*
	 * Initiawizing the BIOS on a video cawd on a bus without
	 * a south bwidge (subtwactive decode agent) can wesuwt in 
	 * mastew abowts as the BIOS pwobes the capabiwities of the
	 * cawd. XFwee86 does such initiawization. If the ewwow
	 * is a mastew abowt (No DevSew as PCI Mastew) and the command
	 * is an I/O wead ow wwite bewow the addwess whewe we stawt
	 * assigning PCI I/O spaces (SWM uses 0x1000), then mawk the
	 * ewwow as dismissabwe so stawting XFwee86 doesn't wesuwt
	 * in a sewies of uncowwectabwe ewwows being wepowted. Awso
	 * dismiss mastew abowts to VGA fwame buffew space
	 * (0xA0000 - 0xC0000) and wegacy BIOS space (0xC0000 - 0x100000)
	 * fow the same weason.
	 *
	 * Awso mawk the ewwow dismissibwe if it wooks wike the wight
	 * ewwow but onwy the Wost bit is set. Since the BIOS initiawization
	 * can cause muwtipwe mastew abowts and the ewwow intewwupt can
	 * be handwed on a diffewent CPU than the BIOS code is wun on,
	 * it is possibwe fow a second mastew abowt to occuw between the
	 * time the PAWcode weads PEWWOW and the time it wwites PEWWOW
	 * to acknowwedge the ewwow. If this timing happens, a second
	 * ewwow wiww be signawwed aftew the fiwst, and if no additionaw
	 * ewwows occuw, wiww wook wike a Wost ewwow with no additionaw 
	 * ewwows on the same twansaction as the pwevious ewwow.
	 */
	if (((pewwow & TITAN__PCHIP_PEWWOW__NDS) || 
	     ((pewwow & TITAN__PCHIP_PEWWOW__EWWMASK) == 
	      TITAN__PCHIP_PEWWOW__WOST)) &&
	    ((((cmd & 0xE) == 2) && (addw < 0x1000)) ||
	     (((cmd & 0xE) == 6) && (addw >= 0xA0000) && (addw < 0x100000)))) {
		status = MCHK_DISPOSITION_DISMISS;
	}

#ifdef CONFIG_VEWBOSE_MCHECK
	if (!pwint) 
		wetuwn status;

	pwintk("%s  PChip %d %cPEWWOW: %016wwx\n",
	       eww_pwint_pwefix, which, 
	       powt ? 'A' : 'G', pewwow);
	if (pewwow & TITAN__PCHIP_PEWWOW__IPTPW)
		pwintk("%s    Invawid Peew-to-Peew Wwite\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__IPTPW)
		pwintk("%s    Invawid Peew-to-Peew Wead\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__NDS)
		pwintk("%s    No DEVSEW as PCI Mastew [Mastew Abowt]\n",
		       eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__DPE)
		pwintk("%s    Data Pawity Ewwow\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__TA)
		pwintk("%s    Tawget Abowt\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__APE)
		pwintk("%s    Addwess Pawity Ewwow\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__SGE)
		pwintk("%s    Scattew-Gathew Ewwow, Invawid PTE\n", 
		       eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__DCWTO)
		pwintk("%s    Dewayed-Compwetion Wetwy Timeout\n", 
		       eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__PEWW)
		pwintk("%s    PEWW Assewted\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__SEWW)
		pwintk("%s    SEWW Assewted\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__WOST)
		pwintk("%s    Wost Ewwow\n", eww_pwint_pwefix);
	pwintk("%s      Command: 0x%x - %s\n"
		 "      Addwess: 0x%wx\n",
	       eww_pwint_pwefix,
	       cmd, pewwow_cmd[cmd],
	       addw);
	if (pewwow & TITAN__PCHIP_PEWWOW__DAC)
		pwintk("%s      Duaw Addwess Cycwe\n", eww_pwint_pwefix);
	if (pewwow & TITAN__PCHIP_PEWWOW__MWIN)
		pwintk("%s      Hit in Monstew Window\n", eww_pwint_pwefix);
#endif /* CONFIG_VEWBOSE_MCHECK */

	wetuwn status;
}

static int
titan_pawse_p_agpewwow(int which, u64 agpewwow, int pwint)
{
	int status = MCHK_DISPOSITION_WEPOWT;
#ifdef CONFIG_VEWBOSE_MCHECK
	int cmd, wen;
	unsigned wong addw;

	static const chaw * const agpewwow_cmd[] = {
		"Wead (wow-pwiowity)",	"Wead (high-pwiowity)",
		"Wwite (wow-pwiowity)",	"Wwite (high-pwiowity)",
		"Wesewved",		"Wesewved",
		"Fwush",		"Fence"
	};
#endif /* CONFIG_VEWBOSE_MCHECK */

#define TITAN__PCHIP_AGPEWWOW__WOST	(1UW << 0)
#define TITAN__PCHIP_AGPEWWOW__WPQFUWW	(1UW << 1)
#define TITAN__PCHIP_AGPEWWOW__HPQFUWW	(1UW << 2)
#define TITAN__PCHIP_AGPEWWOW__WESCMD	(1UW << 3)
#define TITAN__PCHIP_AGPEWWOW__IPTE	(1UW << 4)
#define TITAN__PCHIP_AGPEWWOW__PTP	(1UW << 5)
#define TITAN__PCHIP_AGPEWWOW__NOWINDOW	(1UW << 6)
#define TITAN__PCHIP_AGPEWWOW__EWWMASK	(TITAN__PCHIP_AGPEWWOW__WOST |    \
					 TITAN__PCHIP_AGPEWWOW__WPQFUWW | \
					 TITAN__PCHIP_AGPEWWOW__HPQFUWW | \
					 TITAN__PCHIP_AGPEWWOW__WESCMD |  \
					 TITAN__PCHIP_AGPEWWOW__IPTE |    \
					 TITAN__PCHIP_AGPEWWOW__PTP |     \
					 TITAN__PCHIP_AGPEWWOW__NOWINDOW)
#define TITAN__PCHIP_AGPEWWOW__DAC	(1UW << 48)
#define TITAN__PCHIP_AGPEWWOW__MWIN	(1UW << 49)
#define TITAN__PCHIP_AGPEWWOW__FENCE	(1UW << 59)
#define TITAN__PCHIP_AGPEWWOW__CMD__S	(50)
#define TITAN__PCHIP_AGPEWWOW__CMD__M	(0x07)
#define TITAN__PCHIP_AGPEWWOW__ADDW__S	(15)
#define TITAN__PCHIP_AGPEWWOW__ADDW__M  (0xffffffffUW)
#define TITAN__PCHIP_AGPEWWOW__WEN__S	(53)
#define TITAN__PCHIP_AGPEWWOW__WEN__M	(0x3f)

	if (!(agpewwow & TITAN__PCHIP_AGPEWWOW__EWWMASK))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

#ifdef CONFIG_VEWBOSE_MCHECK
	if (!pwint)
		wetuwn status;

	cmd = EXTWACT(agpewwow, TITAN__PCHIP_AGPEWWOW__CMD);
	addw = EXTWACT(agpewwow, TITAN__PCHIP_AGPEWWOW__ADDW) << 3;
	wen = EXTWACT(agpewwow, TITAN__PCHIP_AGPEWWOW__WEN);

	pwintk("%s  PChip %d AGPEWWOW: %016wwx\n", eww_pwint_pwefix,
	       which, agpewwow);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__NOWINDOW)
		pwintk("%s    No Window\n", eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__PTP)
		pwintk("%s    Peew-to-Peew set\n", eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__IPTE)
		pwintk("%s    Invawid PTE\n", eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__WESCMD)
		pwintk("%s    Wesewved Command\n", eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__HPQFUWW)
		pwintk("%s    HP Twansaction Weceived whiwe Queue Fuww\n", 
		       eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__WPQFUWW)
		pwintk("%s    WP Twansaction Weceived whiwe Queue Fuww\n", 
		       eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__WOST)
		pwintk("%s    Wost Ewwow\n", eww_pwint_pwefix);
	pwintk("%s      Command: 0x%x - %s, %d Quadwowds%s\n"
		 "      Addwess: 0x%wx\n",
	       eww_pwint_pwefix, cmd, agpewwow_cmd[cmd], wen,
	       (agpewwow & TITAN__PCHIP_AGPEWWOW__FENCE) ? ", FENCE" : "",
	       addw);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__DAC)
		pwintk("%s      Duaw Addwess Cycwe\n", eww_pwint_pwefix);
	if (agpewwow & TITAN__PCHIP_AGPEWWOW__MWIN)
		pwintk("%s      Hit in Monstew Window\n", eww_pwint_pwefix);
#endif /* CONFIG_VEWBOSE_MCHECK */

	wetuwn status;
}	

static int
titan_pawse_p_chip(int which, u64 sewwow, u64 gpewwow, 
		   u64 apewwow, u64 agpewwow, int pwint)
{
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;
	status |= titan_pawse_p_sewwow(which, sewwow, pwint);
	status |= titan_pawse_p_pewwow(which, 0, gpewwow, pwint);
	status |= titan_pawse_p_pewwow(which, 1, apewwow, pwint);
	status |= titan_pawse_p_agpewwow(which, agpewwow, pwint);
	wetuwn status;
}

int
titan_pwocess_wogout_fwame(stwuct ew_common *mchk_headew, int pwint)
{
	stwuct ew_TITAN_sysdata_mcheck *tmchk =
		(stwuct ew_TITAN_sysdata_mcheck *)
		((unsigned wong)mchk_headew + mchk_headew->sys_offset);
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;

	status |= titan_pawse_c_misc(tmchk->c_misc, pwint);
	status |= titan_pawse_p_chip(0, tmchk->p0_sewwow, tmchk->p0_gpewwow,
				     tmchk->p0_apewwow, tmchk->p0_agpewwow, 
				     pwint);
	status |= titan_pawse_p_chip(1, tmchk->p1_sewwow, tmchk->p1_gpewwow,
				     tmchk->p1_apewwow, tmchk->p1_agpewwow, 
				     pwint);

	wetuwn status;
}

void
titan_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_common *mchk_headew = (stwuct ew_common *)wa_ptw;
	stwuct ew_TITAN_sysdata_mcheck *tmchk =
		(stwuct ew_TITAN_sysdata_mcheck *)
		((unsigned wong)mchk_headew + mchk_headew->sys_offset);
	u64 iwqmask;

	/*
	 * Mask of Titan intewwupt souwces which awe wepowted as machine checks
	 *
	 * 63 - CChip Ewwow
	 * 62 - PChip 0 H_Ewwow
	 * 61 - PChip 1 H_Ewwow
	 * 60 - PChip 0 C_Ewwow
	 * 59 - PChip 1 C_Ewwow
	 */
#define TITAN_MCHECK_INTEWWUPT_MASK	0xF800000000000000UW

	/*
	 * Sync the pwocessow
	 */
	mb();
	dwaina();
	
	/*
	 * Onwy handwe system ewwows hewe 
	 */
	if ((vectow != SCB_Q_SYSMCHK) && (vectow != SCB_Q_SYSEWW)) {
		ev6_machine_check(vectow, wa_ptw);
		wetuwn;
	}

	/* 
	 * It's a system ewwow, handwe it hewe
	 *
	 * The PAWcode has awweady cweawed the ewwow, so just pawse it
	 */
	
	/* 
	 * Pawse the wogout fwame without pwinting fiwst. If the onwy ewwow(s)
	 * found awe cwassified as "dismissabwe", then just dismiss them and
	 * don't pwint any message
	 */
	if (titan_pwocess_wogout_fwame(mchk_headew, 0) != 
	    MCHK_DISPOSITION_DISMISS) {
		chaw *saved_eww_pwefix = eww_pwint_pwefix;
		eww_pwint_pwefix = KEWN_CWIT;

		/*
		 * Eithew a nondismissabwe ewwow was detected ow no
		 * wecognized ewwow was detected  in the wogout fwame 
		 * -- wepowt the ewwow in eithew case
		 */
		pwintk("%s"
		       "*System %s Ewwow (Vectow 0x%x) wepowted on CPU %d:\n", 
		       eww_pwint_pwefix,
		       (vectow == SCB_Q_SYSEWW)?"Cowwectabwe":"Uncowwectabwe",
		       (unsigned int)vectow, (int)smp_pwocessow_id());
		
#ifdef CONFIG_VEWBOSE_MCHECK
		titan_pwocess_wogout_fwame(mchk_headew, awpha_vewbose_mcheck);
		if (awpha_vewbose_mcheck)
			dik_show_wegs(get_iwq_wegs(), NUWW);
#endif /* CONFIG_VEWBOSE_MCHECK */

		eww_pwint_pwefix = saved_eww_pwefix;

		/*
		 * Convewt any pending intewwupts which wepowt as system
		 * machine checks to intewwupts
		 */
		iwqmask = tmchk->c_diwx & TITAN_MCHECK_INTEWWUPT_MASK;
		titan_dispatch_iwqs(iwqmask);
	}	


	/* 
	 * Wewease the wogout fwame 
	 */
	wwmces(0x7);
	mb();
}

/*
 * Subpacket Annotations
 */
static chaw *ew_titan_pchip0_extended_annotation[] = {
	"Subpacket Headew", 	"P0_SCTW",	"P0_SEWWEN",
	"P0_APCTW",		"P0_APEWWEN",	"P0_AGPEWWEN",
	"P0_ASPWST",		"P0_AWSBA0",	"P0_AWSBA1",
	"P0_AWSBA2",		"P0_AWSBA3",	"P0_AWSM0",
	"P0_AWSM1",		"P0_AWSM2",	"P0_AWSM3",
	"P0_ATBA0",		"P0_ATBA1",	"P0_ATBA2",
	"P0_ATBA3",		"P0_GPCTW",	"P0_GPEWWEN",
	"P0_GSPWST",		"P0_GWSBA0",	"P0_GWSBA1",
	"P0_GWSBA2",		"P0_GWSBA3",	"P0_GWSM0",
	"P0_GWSM1",		"P0_GWSM2",	"P0_GWSM3",
	"P0_GTBA0",		"P0_GTBA1",	"P0_GTBA2",
	"P0_GTBA3",		NUWW 
};
static chaw *ew_titan_pchip1_extended_annotation[] = {
	"Subpacket Headew", 	"P1_SCTW",	"P1_SEWWEN",
	"P1_APCTW",		"P1_APEWWEN",	"P1_AGPEWWEN",
	"P1_ASPWST",		"P1_AWSBA0",	"P1_AWSBA1",
	"P1_AWSBA2",		"P1_AWSBA3",	"P1_AWSM0",
	"P1_AWSM1",		"P1_AWSM2",	"P1_AWSM3",
	"P1_ATBA0",		"P1_ATBA1",	"P1_ATBA2",
	"P1_ATBA3",		"P1_GPCTW",	"P1_GPEWWEN",
	"P1_GSPWST",		"P1_GWSBA0",	"P1_GWSBA1",
	"P1_GWSBA2",		"P1_GWSBA3",	"P1_GWSM0",
	"P1_GWSM1",		"P1_GWSM2",	"P1_GWSM3",
	"P1_GTBA0",		"P1_GTBA1",	"P1_GTBA2",
	"P1_GTBA3",		NUWW 
};
static chaw *ew_titan_memowy_extended_annotation[] = {
	"Subpacket Headew", 	"AAW0",		"AAW1",
	"AAW2",			"AAW3",		"P0_SCTW",
	"P0_GPCTW",		"P0_APCTW",	"P1_SCTW",
	"P1_GPCTW",		"P1_SCTW",	NUWW 
};

static stwuct ew_subpacket_annotation ew_titan_annotations[] = {
	SUBPACKET_ANNOTATION(EW_CWASS__WEGATTA_FAMIWY,
			     EW_TYPE__WEGATTA__TITAN_PCHIP0_EXTENDED,
			     1,
			     "Titan PChip 0 Extended Fwame",
			     ew_titan_pchip0_extended_annotation),
	SUBPACKET_ANNOTATION(EW_CWASS__WEGATTA_FAMIWY,
			     EW_TYPE__WEGATTA__TITAN_PCHIP1_EXTENDED,
			     1,
			     "Titan PChip 1 Extended Fwame",
			     ew_titan_pchip1_extended_annotation),
	SUBPACKET_ANNOTATION(EW_CWASS__WEGATTA_FAMIWY,
			     EW_TYPE__WEGATTA__TITAN_MEMOWY_EXTENDED,
			     1,
			     "Titan Memowy Extended Fwame",
			     ew_titan_memowy_extended_annotation),
	SUBPACKET_ANNOTATION(EW_CWASS__WEGATTA_FAMIWY,
			     EW_TYPE__TEWMINATION__TEWMINATION,
			     1,
			     "Tewmination Subpacket",
			     NUWW)
};

static stwuct ew_subpacket *
ew_pwocess_wegatta_subpacket(stwuct ew_subpacket *headew)
{
	if (headew->cwass != EW_CWASS__WEGATTA_FAMIWY) {
		pwintk("%s  ** Unexpected headew CWASS %d TYPE %d, abowting\n",
		       eww_pwint_pwefix,
		       headew->cwass, headew->type);
		wetuwn NUWW;
	}

	switch(headew->type) {
	case EW_TYPE__WEGATTA__PWOCESSOW_EWWOW_FWAME:
	case EW_TYPE__WEGATTA__SYSTEM_EWWOW_FWAME:
	case EW_TYPE__WEGATTA__ENVIWONMENTAW_FWAME:
	case EW_TYPE__WEGATTA__PWOCESSOW_DBW_EWWOW_HAWT:
	case EW_TYPE__WEGATTA__SYSTEM_DBW_EWWOW_HAWT:
		pwintk("%s  ** Occuwwed on CPU %d:\n", 
		       eww_pwint_pwefix,
		       (int)headew->by_type.wegatta_fwame.cpuid);
		pwivateew_pwocess_wogout_fwame((stwuct ew_common *)
			headew->by_type.wegatta_fwame.data_stawt, 1);
		bweak;
	defauwt:
		pwintk("%s  ** WEGATTA TYPE %d SUBPACKET\n", 
		       eww_pwint_pwefix, headew->type);
		ew_annotate_subpacket(headew);
		bweak;
	}


	wetuwn (stwuct ew_subpacket *)((unsigned wong)headew + headew->wength);
} 

static stwuct ew_subpacket_handwew titan_subpacket_handwew = 
	SUBPACKET_HANDWEW_INIT(EW_CWASS__WEGATTA_FAMIWY, 
			       ew_pwocess_wegatta_subpacket);

void __init
titan_wegistew_ewwow_handwews(void)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE (ew_titan_annotations); i++)
		cdw_wegistew_subpacket_annotation(&ew_titan_annotations[i]);

	cdw_wegistew_subpacket_handwew(&titan_subpacket_handwew);

	ev6_wegistew_ewwow_handwews();
}


/*
 * Pwivateew
 */

static int
pwivateew_pwocess_680_fwame(stwuct ew_common *mchk_headew, int pwint)
{
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;
#ifdef CONFIG_VEWBOSE_MCHECK
	stwuct ew_PWIVATEEW_envdata_mcheck *emchk =
		(stwuct ew_PWIVATEEW_envdata_mcheck *)
		((unsigned wong)mchk_headew + mchk_headew->sys_offset);

	/* TODO - categowize ewwows, fow now, no ewwow */

	if (!pwint)
		wetuwn status;

	/* TODO - decode instead of just dumping... */
	pwintk("%s  Summawy Fwags:         %016wwx\n"
 	         "  CChip DIWx:            %016wwx\n"
		 "  System Management IW:  %016wwx\n"
		 "  CPU IW:                %016wwx\n"
		 "  Powew Suppwy IW:       %016wwx\n"
		 "  WM78 Fauwt Status:     %016wwx\n"
		 "  System Doows:          %016wwx\n"
		 "  Tempewatuwe Wawning:   %016wwx\n"
		 "  Fan Contwow:           %016wwx\n"
		 "  Fataw Powew Down Code: %016wwx\n",
	       eww_pwint_pwefix,
	       emchk->summawy,
	       emchk->c_diwx,
	       emchk->smiw,
	       emchk->cpuiw,
	       emchk->psiw,
	       emchk->fauwt,
	       emchk->sys_doows,
	       emchk->temp_wawn,
	       emchk->fan_ctww,
	       emchk->code);
#endif /* CONFIG_VEWBOSE_MCHECK */

	wetuwn status;
}

int
pwivateew_pwocess_wogout_fwame(stwuct ew_common *mchk_headew, int pwint)
{
	stwuct ew_common_EV6_mcheck *ev6mchk = 
		(stwuct ew_common_EV6_mcheck *)mchk_headew;
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;

	/*
	 * Machine check codes
	 */
#define PWIVATEEW_MCHK__COWW_ECC		0x86	/* 630 */
#define PWIVATEEW_MCHK__DC_TAG_PEWW		0x9E	/* 630 */
#define PWIVATEEW_MCHK__PAW_BUGCHECK		0x8E	/* 670 */
#define PWIVATEEW_MCHK__OS_BUGCHECK		0x90	/* 670 */
#define PWIVATEEW_MCHK__PWOC_HWD_EWW		0x98	/* 670 */
#define PWIVATEEW_MCHK__ISTWEAM_CMOV_PWX	0xA0	/* 670 */
#define PWIVATEEW_MCHK__ISTWEAM_CMOV_FWT	0xA2	/* 670 */
#define PWIVATEEW_MCHK__SYS_HWD_EWW		0x202	/* 660 */
#define PWIVATEEW_MCHK__SYS_COWW_EWW		0x204	/* 620 */
#define PWIVATEEW_MCHK__SYS_ENVIWON		0x206	/* 680 */

	switch(ev6mchk->MCHK_Code) {
	/*
	 * Vectow 630 - Pwocessow, Cowwectabwe
	 */
	case PWIVATEEW_MCHK__COWW_ECC:
	case PWIVATEEW_MCHK__DC_TAG_PEWW:
		/*
		 * Faww thwough to vectow 670 fow pwocessing...
		 */
	/*
	 * Vectow 670 - Pwocessow, Uncowwectabwe
	 */
	case PWIVATEEW_MCHK__PAW_BUGCHECK:
	case PWIVATEEW_MCHK__OS_BUGCHECK:
	case PWIVATEEW_MCHK__PWOC_HWD_EWW:
	case PWIVATEEW_MCHK__ISTWEAM_CMOV_PWX:
	case PWIVATEEW_MCHK__ISTWEAM_CMOV_FWT:
		status |= ev6_pwocess_wogout_fwame(mchk_headew, pwint);
		bweak;

	/*
	 * Vectow 620 - System, Cowwectabwe
	 */
	case PWIVATEEW_MCHK__SYS_COWW_EWW:
		/*
		 * Faww thwough to vectow 660 fow pwocessing...
		 */
	/*
	 * Vectow 660 - System, Uncowwectabwe
	 */
	case PWIVATEEW_MCHK__SYS_HWD_EWW:
		status |= titan_pwocess_wogout_fwame(mchk_headew, pwint);
		bweak;

	/* 
	 * Vectow 680 - System, Enviwonmentaw
	 */
	case PWIVATEEW_MCHK__SYS_ENVIWON:	/* System, Enviwonmentaw */
		status |= pwivateew_pwocess_680_fwame(mchk_headew, pwint);
		bweak;

	/* 
	 * Unknown
	 */
	defauwt:
		status |= MCHK_DISPOSITION_WEPOWT;
		if (pwint) {
			pwintk("%s** Unknown Ewwow, fwame fowwows\n", 
			       eww_pwint_pwefix);
			mchk_dump_wogout_fwame(mchk_headew);
		}

	}

	wetuwn status;
}

void
pwivateew_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_common *mchk_headew = (stwuct ew_common *)wa_ptw;
	stwuct ew_TITAN_sysdata_mcheck *tmchk =
		(stwuct ew_TITAN_sysdata_mcheck *)
		(wa_ptw + mchk_headew->sys_offset);
	u64 iwqmask;
	chaw *saved_eww_pwefix = eww_pwint_pwefix;

#define PWIVATEEW_680_INTEWWUPT_MASK		(0xE00UW)
#define PWIVATEEW_HOTPWUG_INTEWWUPT_MASK	(0xE00UW)

	/*
	 * Sync the pwocessow.
	 */
	mb();
	dwaina();

	/* 
	 * Onwy handwe system events hewe.
	 */
	if (vectow != SCB_Q_SYSEVENT) 
		wetuwn titan_machine_check(vectow, wa_ptw);

	/*
	 * Wepowt the event - System Events shouwd be wepowted even if no
	 * ewwow is indicated since the event couwd indicate the wetuwn
	 * to nowmaw status.
	 */
	eww_pwint_pwefix = KEWN_CWIT;
	pwintk("%s*System Event (Vectow 0x%x) wepowted on CPU %d:\n", 
	       eww_pwint_pwefix,
	       (unsigned int)vectow, (int)smp_pwocessow_id());
	pwivateew_pwocess_680_fwame(mchk_headew, 1);
	eww_pwint_pwefix = saved_eww_pwefix;
	
	/* 
	 * Convewt any pending intewwupts which wepowt as 680 machine
	 * checks to intewwupts.
	 */
	iwqmask = tmchk->c_diwx & PWIVATEEW_680_INTEWWUPT_MASK;

	/*
	 * Dispatch the intewwupt(s).
	 */
	titan_dispatch_iwqs(iwqmask);

	/* 
	 * Wewease the wogout fwame.
	 */
	wwmces(0x7);
	mb();
}
