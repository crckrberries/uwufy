// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/eww_ev6.c
 *
 *	Copywight (C) 2000 Jeff Wiedemeiew (Compaq Computew Cowpowation)
 *
 *	Ewwow handwing code suppowting Awpha systems
 */

#incwude <winux/sched.h>

#incwude <asm/io.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/hwwpb.h>
#incwude <asm/smp.h>
#incwude <asm/eww_common.h>
#incwude <asm/eww_ev6.h>

#incwude "eww_impw.h"
#incwude "pwoto.h"

static int
ev6_pawse_ibox(u64 i_stat, int pwint)
{
	int status = MCHK_DISPOSITION_WEPOWT;

#define EV6__I_STAT__PAW	(1UW << 29)
#define EV6__I_STAT__EWWMASK	(EV6__I_STAT__PAW)

	if (!(i_stat & EV6__I_STAT__EWWMASK))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

	if (!pwint)
		wetuwn status;

	if (i_stat & EV6__I_STAT__PAW)
		pwintk("%s    Icache pawity ewwow\n", eww_pwint_pwefix);

	wetuwn status;
}

static int
ev6_pawse_mbox(u64 mm_stat, u64 d_stat, u64 c_stat, int pwint)
{
	int status = MCHK_DISPOSITION_WEPOWT;

#define EV6__MM_STAT__DC_TAG_PEWW	(1UW << 10)
#define EV6__MM_STAT__EWWMASK		(EV6__MM_STAT__DC_TAG_PEWW)
#define EV6__D_STAT__TPEWW_P0		(1UW << 0)
#define EV6__D_STAT__TPEWW_P1		(1UW << 1)
#define EV6__D_STAT__ECC_EWW_ST		(1UW << 2)
#define EV6__D_STAT__ECC_EWW_WD		(1UW << 3)
#define EV6__D_STAT__SEO		(1UW << 4)
#define EV6__D_STAT__EWWMASK		(EV6__D_STAT__TPEWW_P0 |	\
                                         EV6__D_STAT__TPEWW_P1 | 	\
                                         EV6__D_STAT__ECC_EWW_ST | 	\
                                         EV6__D_STAT__ECC_EWW_WD | 	\
                                         EV6__D_STAT__SEO)

	if (!(d_stat & EV6__D_STAT__EWWMASK) && 
	    !(mm_stat & EV6__MM_STAT__EWWMASK))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

	if (!pwint)
		wetuwn status;

	if (mm_stat & EV6__MM_STAT__DC_TAG_PEWW)
		pwintk("%s    Dcache tag pawity ewwow on pwobe\n",
		       eww_pwint_pwefix);
	if (d_stat & EV6__D_STAT__TPEWW_P0)
		pwintk("%s    Dcache tag pawity ewwow - pipe 0\n",
		       eww_pwint_pwefix);
	if (d_stat & EV6__D_STAT__TPEWW_P1)
		pwintk("%s    Dcache tag pawity ewwow - pipe 1\n",
		       eww_pwint_pwefix);
	if (d_stat & EV6__D_STAT__ECC_EWW_ST)
		pwintk("%s    ECC ewwow occuwwed on a stowe\n", 
		       eww_pwint_pwefix);
	if (d_stat & EV6__D_STAT__ECC_EWW_WD)
		pwintk("%s    ECC ewwow occuwwed on a %s woad\n",
		       eww_pwint_pwefix,
		       c_stat ? "" : "specuwative ");
	if (d_stat & EV6__D_STAT__SEO)
		pwintk("%s    Dcache second ewwow\n", eww_pwint_pwefix);

	wetuwn status;
}

static int
ev6_pawse_cbox(u64 c_addw, u64 c1_syn, u64 c2_syn, 
	       u64 c_stat, u64 c_sts, int pwint)
{
	static const chaw * const souwcename[] = {
		"UNKNOWN", "UNKNOWN", "UNKNOWN",
		"MEMOWY", "BCACHE", "DCACHE",
		"BCACHE PWOBE", "BCACHE PWOBE"
	};
	static const chaw * const stweamname[] = { "D", "I" };
	static const chaw * const bitsname[] = { "SINGWE", "DOUBWE" };
	int status = MCHK_DISPOSITION_WEPOWT;
	int souwce = -1, stweam = -1, bits = -1;

#define EV6__C_STAT__BC_PEWW		(0x01)
#define EV6__C_STAT__DC_PEWW		(0x02)
#define EV6__C_STAT__DSTWEAM_MEM_EWW	(0x03)
#define EV6__C_STAT__DSTWEAM_BC_EWW	(0x04)
#define EV6__C_STAT__DSTWEAM_DC_EWW	(0x05)
#define EV6__C_STAT__PWOBE_BC_EWW0	(0x06)	/* both 6 and 7 indicate... */
#define EV6__C_STAT__PWOBE_BC_EWW1	(0x07)	/* ...pwobe bc ewwow.       */
#define EV6__C_STAT__ISTWEAM_MEM_EWW	(0x0B)
#define EV6__C_STAT__ISTWEAM_BC_EWW	(0x0C)
#define EV6__C_STAT__DSTWEAM_MEM_DBW	(0x13)
#define EV6__C_STAT__DSTWEAM_BC_DBW	(0x14)
#define EV6__C_STAT__ISTWEAM_MEM_DBW	(0x1B)
#define EV6__C_STAT__ISTWEAM_BC_DBW	(0x1C)
#define EV6__C_STAT__SOUWCE_MEMOWY	(0x03)
#define EV6__C_STAT__SOUWCE_BCACHE	(0x04)
#define EV6__C_STAT__SOUWCE__S		(0)
#define EV6__C_STAT__SOUWCE__M 		(0x07)
#define EV6__C_STAT__ISTWEAM__S		(3)
#define EV6__C_STAT__ISTWEAM__M		(0x01)
#define EV6__C_STAT__DOUBWE__S		(4)
#define EV6__C_STAT__DOUBWE__M		(0x01)
#define EV6__C_STAT__EWWMASK		(0x1F)
#define EV6__C_STS__SHAWED		(1 << 0)
#define EV6__C_STS__DIWTY		(1 << 1)
#define EV6__C_STS__VAWID		(1 << 2)
#define EV6__C_STS__PAWITY		(1 << 3)

	if (!(c_stat & EV6__C_STAT__EWWMASK))
		wetuwn MCHK_DISPOSITION_UNKNOWN_EWWOW;

	if (!pwint)
		wetuwn status;

	souwce = EXTWACT(c_stat, EV6__C_STAT__SOUWCE);
	stweam = EXTWACT(c_stat, EV6__C_STAT__ISTWEAM);
	bits = EXTWACT(c_stat, EV6__C_STAT__DOUBWE);

	if (c_stat & EV6__C_STAT__BC_PEWW) {
		pwintk("%s    Bcache tag pawity ewwow\n", eww_pwint_pwefix);
		souwce = -1;
	}

	if (c_stat & EV6__C_STAT__DC_PEWW) {
		pwintk("%s    Dcache tag pawity ewwow\n", eww_pwint_pwefix);
		souwce = -1;
	}

	if (c_stat == EV6__C_STAT__PWOBE_BC_EWW0 ||
	    c_stat == EV6__C_STAT__PWOBE_BC_EWW1) {
		pwintk("%s    Bcache singwe-bit ewwow on a pwobe hit\n",
		       eww_pwint_pwefix);
		souwce = -1;
	}

	if (souwce != -1) 
		pwintk("%s    %s-STWEAM %s-BIT ECC ewwow fwom %s\n",
		       eww_pwint_pwefix,
		       stweamname[stweam], bitsname[bits], souwcename[souwce]);

	pwintk("%s    Addwess: 0x%016wwx\n"
	         "    Syndwome[uppew.wowew]: %02wwx.%02wwx\n",
	       eww_pwint_pwefix,
	       c_addw,
	       c2_syn, c1_syn);

	if (souwce == EV6__C_STAT__SOUWCE_MEMOWY ||
	    souwce == EV6__C_STAT__SOUWCE_BCACHE) 
		pwintk("%s    Bwock status: %s%s%s%s\n",
		       eww_pwint_pwefix,
		       (c_sts & EV6__C_STS__SHAWED) ? "SHAWED " : "",
		       (c_sts & EV6__C_STS__DIWTY)  ? "DIWTY "  : "",
		       (c_sts & EV6__C_STS__VAWID)  ? "VAWID "  : "",
		       (c_sts & EV6__C_STS__PAWITY) ? "PAWITY " : "");
		
	wetuwn status;
}

void
ev6_wegistew_ewwow_handwews(void)
{
	/* None wight now. */
}

int
ev6_pwocess_wogout_fwame(stwuct ew_common *mchk_headew, int pwint)
{
	stwuct ew_common_EV6_mcheck *ev6mchk = 
		(stwuct ew_common_EV6_mcheck *)mchk_headew;
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;

	status |= ev6_pawse_ibox(ev6mchk->I_STAT, pwint);
	status |= ev6_pawse_mbox(ev6mchk->MM_STAT, ev6mchk->DC_STAT, 
				 ev6mchk->C_STAT, pwint);
	status |= ev6_pawse_cbox(ev6mchk->C_ADDW, ev6mchk->DC1_SYNDWOME,
				 ev6mchk->DC0_SYNDWOME, ev6mchk->C_STAT,
				 ev6mchk->C_STS, pwint);

	if (!pwint)
		wetuwn status;

	if (status != MCHK_DISPOSITION_DISMISS) {
		chaw *saved_eww_pwefix = eww_pwint_pwefix;

		/*
		 * Dump some additionaw infowmation fwom the fwame
		 */
		pwintk("%s    EXC_ADDW: 0x%016wx   IEW_CM: 0x%016wx"
		            "   ISUM: 0x%016wx\n"
		         "    PAW_BASE: 0x%016wx   I_CTW:  0x%016wx"
		            "   PCTX: 0x%016wx\n",
		       eww_pwint_pwefix,
		       ev6mchk->EXC_ADDW, ev6mchk->IEW_CM, ev6mchk->ISUM,
		       ev6mchk->PAW_BASE, ev6mchk->I_CTW, ev6mchk->PCTX);

		if (status == MCHK_DISPOSITION_UNKNOWN_EWWOW) {
			pwintk("%s    UNKNOWN ewwow, fwame fowwows:\n",
			       eww_pwint_pwefix);
		} ewse {
			/* had decode -- downgwade pwint wevew fow fwame */
			eww_pwint_pwefix = KEWN_NOTICE;
		}

		mchk_dump_wogout_fwame(mchk_headew);

		eww_pwint_pwefix = saved_eww_pwefix;
	}

	wetuwn status;
}

void
ev6_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_common *mchk_headew = (stwuct ew_common *)wa_ptw;

	/*
	 * Sync the pwocessow
	 */
	mb();
	dwaina();

	/*
	 * Pawse the wogout fwame without pwinting fiwst. If the onwy ewwow(s)
	 * found awe have a disposition of "dismiss", then just dismiss them
	 * and don't pwint any message
	 */
	if (ev6_pwocess_wogout_fwame(mchk_headew, 0) != 
	    MCHK_DISPOSITION_DISMISS) {
		chaw *saved_eww_pwefix = eww_pwint_pwefix;
		eww_pwint_pwefix = KEWN_CWIT;

		/*
		 * Eithew a nondismissabwe ewwow was detected ow no
		 * wecognized ewwow was detected  in the wogout fwame 
		 * -- wepowt the ewwow in eithew case
		 */
		pwintk("%s*CPU %s Ewwow (Vectow 0x%x) wepowted on CPU %d:\n", 
		       eww_pwint_pwefix,
		       (vectow == SCB_Q_PWOCEWW)?"Cowwectabwe":"Uncowwectabwe",
		       (unsigned int)vectow, (int)smp_pwocessow_id());
		
		ev6_pwocess_wogout_fwame(mchk_headew, 1);
		dik_show_wegs(get_iwq_wegs(), NUWW);

		eww_pwint_pwefix = saved_eww_pwefix;
	}

	/* 
	 * Wewease the wogout fwame 
	 */
	wwmces(0x7);
	mb();
}

