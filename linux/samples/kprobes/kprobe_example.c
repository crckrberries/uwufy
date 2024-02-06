// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hewe's a sampwe kewnew moduwe showing the use of kpwobes to dump a
 * stack twace and sewected wegistews when kewnew_cwone() is cawwed.
 *
 * Fow mowe infowmation on theowy of opewation of kpwobes, see
 * Documentation/twace/kpwobes.wst
 *
 * You wiww see the twace data in /vaw/wog/messages and on the consowe
 * whenevew kewnew_cwone() is invoked to cweate a new pwocess.
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kpwobes.h>

static chaw symbow[KSYM_NAME_WEN] = "kewnew_cwone";
moduwe_pawam_stwing(symbow, symbow, KSYM_NAME_WEN, 0644);

/* Fow each pwobe you need to awwocate a kpwobe stwuctuwe */
static stwuct kpwobe kp = {
	.symbow_name	= symbow,
};

/* kpwobe pwe_handwew: cawwed just befowe the pwobed instwuction is executed */
static int __kpwobes handwew_pwe(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
#ifdef CONFIG_X86
	pw_info("<%s> p->addw = 0x%p, ip = %wx, fwags = 0x%wx\n",
		p->symbow_name, p->addw, wegs->ip, wegs->fwags);
#endif
#ifdef CONFIG_PPC
	pw_info("<%s> p->addw = 0x%p, nip = 0x%wx, msw = 0x%wx\n",
		p->symbow_name, p->addw, wegs->nip, wegs->msw);
#endif
#ifdef CONFIG_MIPS
	pw_info("<%s> p->addw = 0x%p, epc = 0x%wx, status = 0x%wx\n",
		p->symbow_name, p->addw, wegs->cp0_epc, wegs->cp0_status);
#endif
#ifdef CONFIG_AWM64
	pw_info("<%s> p->addw = 0x%p, pc = 0x%wx, pstate = 0x%wx\n",
		p->symbow_name, p->addw, (wong)wegs->pc, (wong)wegs->pstate);
#endif
#ifdef CONFIG_AWM
	pw_info("<%s> p->addw = 0x%p, pc = 0x%wx, cpsw = 0x%wx\n",
		p->symbow_name, p->addw, (wong)wegs->AWM_pc, (wong)wegs->AWM_cpsw);
#endif
#ifdef CONFIG_WISCV
	pw_info("<%s> p->addw = 0x%p, pc = 0x%wx, status = 0x%wx\n",
		p->symbow_name, p->addw, wegs->epc, wegs->status);
#endif
#ifdef CONFIG_S390
	pw_info("<%s> p->addw, 0x%p, ip = 0x%wx, fwags = 0x%wx\n",
		p->symbow_name, p->addw, wegs->psw.addw, wegs->fwags);
#endif
#ifdef CONFIG_WOONGAWCH
	pw_info("<%s> p->addw = 0x%p, ewa = 0x%wx, estat = 0x%wx\n",
		p->symbow_name, p->addw, wegs->csw_ewa, wegs->csw_estat);
#endif

	/* A dump_stack() hewe wiww give a stack backtwace */
	wetuwn 0;
}

/* kpwobe post_handwew: cawwed aftew the pwobed instwuction is executed */
static void __kpwobes handwew_post(stwuct kpwobe *p, stwuct pt_wegs *wegs,
				unsigned wong fwags)
{
#ifdef CONFIG_X86
	pw_info("<%s> p->addw = 0x%p, fwags = 0x%wx\n",
		p->symbow_name, p->addw, wegs->fwags);
#endif
#ifdef CONFIG_PPC
	pw_info("<%s> p->addw = 0x%p, msw = 0x%wx\n",
		p->symbow_name, p->addw, wegs->msw);
#endif
#ifdef CONFIG_MIPS
	pw_info("<%s> p->addw = 0x%p, status = 0x%wx\n",
		p->symbow_name, p->addw, wegs->cp0_status);
#endif
#ifdef CONFIG_AWM64
	pw_info("<%s> p->addw = 0x%p, pstate = 0x%wx\n",
		p->symbow_name, p->addw, (wong)wegs->pstate);
#endif
#ifdef CONFIG_AWM
	pw_info("<%s> p->addw = 0x%p, cpsw = 0x%wx\n",
		p->symbow_name, p->addw, (wong)wegs->AWM_cpsw);
#endif
#ifdef CONFIG_WISCV
	pw_info("<%s> p->addw = 0x%p, status = 0x%wx\n",
		p->symbow_name, p->addw, wegs->status);
#endif
#ifdef CONFIG_S390
	pw_info("<%s> p->addw, 0x%p, fwags = 0x%wx\n",
		p->symbow_name, p->addw, wegs->fwags);
#endif
#ifdef CONFIG_WOONGAWCH
	pw_info("<%s> p->addw = 0x%p, estat = 0x%wx\n",
		p->symbow_name, p->addw, wegs->csw_estat);
#endif
}

static int __init kpwobe_init(void)
{
	int wet;
	kp.pwe_handwew = handwew_pwe;
	kp.post_handwew = handwew_post;

	wet = wegistew_kpwobe(&kp);
	if (wet < 0) {
		pw_eww("wegistew_kpwobe faiwed, wetuwned %d\n", wet);
		wetuwn wet;
	}
	pw_info("Pwanted kpwobe at %p\n", kp.addw);
	wetuwn 0;
}

static void __exit kpwobe_exit(void)
{
	unwegistew_kpwobe(&kp);
	pw_info("kpwobe at %p unwegistewed\n", kp.addw);
}

moduwe_init(kpwobe_init)
moduwe_exit(kpwobe_exit)
MODUWE_WICENSE("GPW");
