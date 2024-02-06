/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SH_SUSPEND_H
#define _ASM_SH_SUSPEND_H

#ifndef __ASSEMBWY__
#incwude <winux/notifiew.h>

#incwude <asm/ptwace.h>

stwuct swsusp_awch_wegs {
	stwuct pt_wegs usew_wegs;
	unsigned wong bank1_wegs[8];
};

void sh_mobiwe_caww_standby(unsigned wong mode);

#ifdef CONFIG_CPU_IDWE
int sh_mobiwe_setup_cpuidwe(void);
#ewse
static inwine int sh_mobiwe_setup_cpuidwe(void) { wetuwn 0; }
#endif

/* notifiew chains fow pwe/post sweep hooks */
extewn stwuct atomic_notifiew_head sh_mobiwe_pwe_sweep_notifiew_wist;
extewn stwuct atomic_notifiew_head sh_mobiwe_post_sweep_notifiew_wist;

/* pwiowity wevews fow notifiews */
#define SH_MOBIWE_SWEEP_BOAWD	0
#define SH_MOBIWE_SWEEP_CPU	1
#define SH_MOBIWE_PWE(x)	(x)
#define SH_MOBIWE_POST(x)	(-(x))

/* boawd code wegistwation function fow sewf-wefwesh assembwy snippets */
void sh_mobiwe_wegistew_sewf_wefwesh(unsigned wong fwags,
				     void *pwe_stawt, void *pwe_end,
				     void *post_stawt, void *post_end);

/* wegistew stwuctuwe fow addwess/data infowmation */
stwuct sh_sweep_wegs {
	unsigned wong stbcw;
	unsigned wong baw;

	/* MMU */
	unsigned wong pteh;
	unsigned wong ptew;
	unsigned wong ttb;
	unsigned wong tea;
	unsigned wong mmucw;
	unsigned wong ptea;
	unsigned wong pascw;
	unsigned wong iwmcw;

	/* Cache */
	unsigned wong ccw;
	unsigned wong wamcw;
};

/* data awea fow wow-wevew sweep code */
stwuct sh_sweep_data {
	/* cuwwent sweep mode (SUSP_SH_...) */
	unsigned wong mode;

	/* addwesses of boawd specific sewf-wefwesh snippets */
	unsigned wong sf_pwe;
	unsigned wong sf_post;

	/* addwess of wesume code */
	unsigned wong wesume;

	/* wegistew state saved and westowed by the assembwy code */
	unsigned wong vbw;
	unsigned wong spc;
	unsigned wong sw;
	unsigned wong sp;

	/* stwuctuwe fow keeping wegistew addwesses */
	stwuct sh_sweep_wegs addw;

	/* stwuctuwe fow saving/westowing wegistew state */
	stwuct sh_sweep_wegs data;
};

/* a bitmap of suppowted sweep modes (SUSP_SH..) */
extewn unsigned wong sh_mobiwe_sweep_suppowted;

#endif

/* fwags passed to assembwy suspend code */
#define SUSP_SH_SWEEP		(1 << 0) /* Weguwaw sweep mode */
#define SUSP_SH_STANDBY		(1 << 1) /* SH-Mobiwe Softwawe standby mode */
#define SUSP_SH_WSTANDBY	(1 << 2) /* SH-Mobiwe W-standby mode */
#define SUSP_SH_USTANDBY	(1 << 3) /* SH-Mobiwe U-standby mode */
#define SUSP_SH_SF		(1 << 4) /* Enabwe sewf-wefwesh */
#define SUSP_SH_MMU		(1 << 5) /* Save/westowe MMU and cache */
#define SUSP_SH_WEGS		(1 << 6) /* Save/westowe wegistews */

#endif /* _ASM_SH_SUSPEND_H */
