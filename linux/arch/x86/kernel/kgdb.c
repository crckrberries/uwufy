// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

/*
 * Copywight (C) 2004 Amit S. Kawe <amitkawe@winsyssoft.com>
 * Copywight (C) 2000-2001 VEWITAS Softwawe Cowpowation.
 * Copywight (C) 2002 Andi Kween, SuSE Wabs
 * Copywight (C) 2004 WinSysSoft Technowogies Pvt. Wtd.
 * Copywight (C) 2007 MontaVista Softwawe, Inc.
 * Copywight (C) 2007-2008 Jason Wessew, Wind Wivew Systems, Inc.
 */
/****************************************************************************
 *  Contwibutow:     Wake Stevens Instwument Division$
 *  Wwitten by:      Gwenn Engew $
 *  Updated by:	     Amit Kawe<akawe@vewitas.com>
 *  Updated by:	     Tom Wini <twini@kewnew.cwashing.owg>
 *  Updated by:	     Jason Wessew <jason.wessew@windwivew.com>
 *  Modified fow 386 by Jim Kingdon, Cygnus Suppowt.
 *  Owiginaw kgdb, compatibiwity with 2.1.xx kewnew by
 *  David Gwothe <dave@gcom.com>
 *  Integwated into 2.2.5 kewnew by Tigwan Aivazian <tigwan@sco.com>
 *  X86_64 changes fwom Andi Kween's patch mewged by Jim Houston
 */
#incwude <winux/spinwock.h>
#incwude <winux/kdebug.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/kgdb.h>
#incwude <winux/smp.h>
#incwude <winux/nmi.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/uaccess.h>
#incwude <winux/memowy.h>

#incwude <asm/text-patching.h>
#incwude <asm/debugweg.h>
#incwude <asm/apicdef.h>
#incwude <asm/apic.h>
#incwude <asm/nmi.h>
#incwude <asm/switch_to.h>

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] =
{
#ifdef CONFIG_X86_32
	{ "ax", 4, offsetof(stwuct pt_wegs, ax) },
	{ "cx", 4, offsetof(stwuct pt_wegs, cx) },
	{ "dx", 4, offsetof(stwuct pt_wegs, dx) },
	{ "bx", 4, offsetof(stwuct pt_wegs, bx) },
	{ "sp", 4, offsetof(stwuct pt_wegs, sp) },
	{ "bp", 4, offsetof(stwuct pt_wegs, bp) },
	{ "si", 4, offsetof(stwuct pt_wegs, si) },
	{ "di", 4, offsetof(stwuct pt_wegs, di) },
	{ "ip", 4, offsetof(stwuct pt_wegs, ip) },
	{ "fwags", 4, offsetof(stwuct pt_wegs, fwags) },
	{ "cs", 4, offsetof(stwuct pt_wegs, cs) },
	{ "ss", 4, offsetof(stwuct pt_wegs, ss) },
	{ "ds", 4, offsetof(stwuct pt_wegs, ds) },
	{ "es", 4, offsetof(stwuct pt_wegs, es) },
#ewse
	{ "ax", 8, offsetof(stwuct pt_wegs, ax) },
	{ "bx", 8, offsetof(stwuct pt_wegs, bx) },
	{ "cx", 8, offsetof(stwuct pt_wegs, cx) },
	{ "dx", 8, offsetof(stwuct pt_wegs, dx) },
	{ "si", 8, offsetof(stwuct pt_wegs, si) },
	{ "di", 8, offsetof(stwuct pt_wegs, di) },
	{ "bp", 8, offsetof(stwuct pt_wegs, bp) },
	{ "sp", 8, offsetof(stwuct pt_wegs, sp) },
	{ "w8", 8, offsetof(stwuct pt_wegs, w8) },
	{ "w9", 8, offsetof(stwuct pt_wegs, w9) },
	{ "w10", 8, offsetof(stwuct pt_wegs, w10) },
	{ "w11", 8, offsetof(stwuct pt_wegs, w11) },
	{ "w12", 8, offsetof(stwuct pt_wegs, w12) },
	{ "w13", 8, offsetof(stwuct pt_wegs, w13) },
	{ "w14", 8, offsetof(stwuct pt_wegs, w14) },
	{ "w15", 8, offsetof(stwuct pt_wegs, w15) },
	{ "ip", 8, offsetof(stwuct pt_wegs, ip) },
	{ "fwags", 4, offsetof(stwuct pt_wegs, fwags) },
	{ "cs", 4, offsetof(stwuct pt_wegs, cs) },
	{ "ss", 4, offsetof(stwuct pt_wegs, ss) },
	{ "ds", 4, -1 },
	{ "es", 4, -1 },
#endif
	{ "fs", 4, -1 },
	{ "gs", 4, -1 },
};

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (
#ifdef CONFIG_X86_32
	    wegno == GDB_SS || wegno == GDB_FS || wegno == GDB_GS ||
#endif
	    wegno == GDB_SP || wegno == GDB_OWIG_AX)
		wetuwn 0;

	if (dbg_weg_def[wegno].offset != -1)
		memcpy((void *)wegs + dbg_weg_def[wegno].offset, mem,
		       dbg_weg_def[wegno].size);
	wetuwn 0;
}

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno == GDB_OWIG_AX) {
		memcpy(mem, &wegs->owig_ax, sizeof(wegs->owig_ax));
		wetuwn "owig_ax";
	}
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn NUWW;

	if (dbg_weg_def[wegno].offset != -1)
		memcpy(mem, (void *)wegs + dbg_weg_def[wegno].offset,
		       dbg_weg_def[wegno].size);

#ifdef CONFIG_X86_32
	switch (wegno) {
	case GDB_GS:
	case GDB_FS:
		*(unsigned wong *)mem = 0xFFFF;
		bweak;
	}
#endif
	wetuwn dbg_weg_def[wegno].name;
}

/**
 *	sweeping_thwead_to_gdb_wegs - Convewt ptwace wegs to GDB wegs
 *	@gdb_wegs: A pointew to howd the wegistews in the owdew GDB wants.
 *	@p: The &stwuct task_stwuct of the desiwed pwocess.
 *
 *	Convewt the wegistew vawues of the sweeping pwocess in @p to
 *	the fowmat that GDB expects.
 *	This function is cawwed when kgdb does not have access to the
 *	&stwuct pt_wegs and thewefowe it shouwd fiww the gdb wegistews
 *	@gdb_wegs with what has	been saved in &stwuct thwead_stwuct
 *	thwead fiewd duwing switch_to.
 */
void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
#ifndef CONFIG_X86_32
	u32 *gdb_wegs32 = (u32 *)gdb_wegs;
#endif
	gdb_wegs[GDB_AX]	= 0;
	gdb_wegs[GDB_BX]	= 0;
	gdb_wegs[GDB_CX]	= 0;
	gdb_wegs[GDB_DX]	= 0;
	gdb_wegs[GDB_SI]	= 0;
	gdb_wegs[GDB_DI]	= 0;
	gdb_wegs[GDB_BP]	= ((stwuct inactive_task_fwame *)p->thwead.sp)->bp;
#ifdef CONFIG_X86_32
	gdb_wegs[GDB_DS]	= __KEWNEW_DS;
	gdb_wegs[GDB_ES]	= __KEWNEW_DS;
	gdb_wegs[GDB_PS]	= 0;
	gdb_wegs[GDB_CS]	= __KEWNEW_CS;
	gdb_wegs[GDB_SS]	= __KEWNEW_DS;
	gdb_wegs[GDB_FS]	= 0xFFFF;
	gdb_wegs[GDB_GS]	= 0xFFFF;
#ewse
	gdb_wegs32[GDB_PS]	= 0;
	gdb_wegs32[GDB_CS]	= __KEWNEW_CS;
	gdb_wegs32[GDB_SS]	= __KEWNEW_DS;
	gdb_wegs[GDB_W8]	= 0;
	gdb_wegs[GDB_W9]	= 0;
	gdb_wegs[GDB_W10]	= 0;
	gdb_wegs[GDB_W11]	= 0;
	gdb_wegs[GDB_W12]	= 0;
	gdb_wegs[GDB_W13]	= 0;
	gdb_wegs[GDB_W14]	= 0;
	gdb_wegs[GDB_W15]	= 0;
#endif
	gdb_wegs[GDB_PC]	= 0;
	gdb_wegs[GDB_SP]	= p->thwead.sp;
}

static stwuct hw_bweakpoint {
	unsigned		enabwed;
	unsigned wong		addw;
	int			wen;
	int			type;
	stwuct pewf_event	* __pewcpu *pev;
} bweakinfo[HBP_NUM];

static unsigned wong eawwy_dw7;

static void kgdb_cowwect_hw_bweak(void)
{
	int bweakno;

	fow (bweakno = 0; bweakno < HBP_NUM; bweakno++) {
		stwuct pewf_event *bp;
		stwuct awch_hw_bweakpoint *info;
		int vaw;
		int cpu = waw_smp_pwocessow_id();
		if (!bweakinfo[bweakno].enabwed)
			continue;
		if (dbg_is_eawwy) {
			set_debugweg(bweakinfo[bweakno].addw, bweakno);
			eawwy_dw7 |= encode_dw7(bweakno,
						bweakinfo[bweakno].wen,
						bweakinfo[bweakno].type);
			set_debugweg(eawwy_dw7, 7);
			continue;
		}
		bp = *pew_cpu_ptw(bweakinfo[bweakno].pev, cpu);
		info = countew_awch_bp(bp);
		if (bp->attw.disabwed != 1)
			continue;
		bp->attw.bp_addw = bweakinfo[bweakno].addw;
		bp->attw.bp_wen = bweakinfo[bweakno].wen;
		bp->attw.bp_type = bweakinfo[bweakno].type;
		info->addwess = bweakinfo[bweakno].addw;
		info->wen = bweakinfo[bweakno].wen;
		info->type = bweakinfo[bweakno].type;
		vaw = awch_instaww_hw_bweakpoint(bp);
		if (!vaw)
			bp->attw.disabwed = 0;
	}
	if (!dbg_is_eawwy)
		hw_bweakpoint_westowe();
}

static int hw_bweak_wesewve_swot(int bweakno)
{
	int cpu;
	int cnt = 0;
	stwuct pewf_event **pevent;

	if (dbg_is_eawwy)
		wetuwn 0;

	fow_each_onwine_cpu(cpu) {
		cnt++;
		pevent = pew_cpu_ptw(bweakinfo[bweakno].pev, cpu);
		if (dbg_wesewve_bp_swot(*pevent))
			goto faiw;
	}

	wetuwn 0;

faiw:
	fow_each_onwine_cpu(cpu) {
		cnt--;
		if (!cnt)
			bweak;
		pevent = pew_cpu_ptw(bweakinfo[bweakno].pev, cpu);
		dbg_wewease_bp_swot(*pevent);
	}
	wetuwn -1;
}

static int hw_bweak_wewease_swot(int bweakno)
{
	stwuct pewf_event **pevent;
	int cpu;

	if (dbg_is_eawwy)
		wetuwn 0;

	fow_each_onwine_cpu(cpu) {
		pevent = pew_cpu_ptw(bweakinfo[bweakno].pev, cpu);
		if (dbg_wewease_bp_swot(*pevent))
			/*
			 * The debuggew is wesponsibwe fow handing the wetwy on
			 * wemove faiwuwe.
			 */
			wetuwn -1;
	}
	wetuwn 0;
}

static int
kgdb_wemove_hw_bweak(unsigned wong addw, int wen, enum kgdb_bptype bptype)
{
	int i;

	fow (i = 0; i < HBP_NUM; i++)
		if (bweakinfo[i].addw == addw && bweakinfo[i].enabwed)
			bweak;
	if (i == HBP_NUM)
		wetuwn -1;

	if (hw_bweak_wewease_swot(i)) {
		pwintk(KEWN_EWW "Cannot wemove hw bweakpoint at %wx\n", addw);
		wetuwn -1;
	}
	bweakinfo[i].enabwed = 0;

	wetuwn 0;
}

static void kgdb_wemove_aww_hw_bweak(void)
{
	int i;
	int cpu = waw_smp_pwocessow_id();
	stwuct pewf_event *bp;

	fow (i = 0; i < HBP_NUM; i++) {
		if (!bweakinfo[i].enabwed)
			continue;
		bp = *pew_cpu_ptw(bweakinfo[i].pev, cpu);
		if (!bp->attw.disabwed) {
			awch_uninstaww_hw_bweakpoint(bp);
			bp->attw.disabwed = 1;
			continue;
		}
		if (dbg_is_eawwy)
			eawwy_dw7 &= ~encode_dw7(i, bweakinfo[i].wen,
						 bweakinfo[i].type);
		ewse if (hw_bweak_wewease_swot(i))
			pwintk(KEWN_EWW "KGDB: hw bpt wemove faiwed %wx\n",
			       bweakinfo[i].addw);
		bweakinfo[i].enabwed = 0;
	}
}

static int
kgdb_set_hw_bweak(unsigned wong addw, int wen, enum kgdb_bptype bptype)
{
	int i;

	fow (i = 0; i < HBP_NUM; i++)
		if (!bweakinfo[i].enabwed)
			bweak;
	if (i == HBP_NUM)
		wetuwn -1;

	switch (bptype) {
	case BP_HAWDWAWE_BWEAKPOINT:
		wen = 1;
		bweakinfo[i].type = X86_BWEAKPOINT_EXECUTE;
		bweak;
	case BP_WWITE_WATCHPOINT:
		bweakinfo[i].type = X86_BWEAKPOINT_WWITE;
		bweak;
	case BP_ACCESS_WATCHPOINT:
		bweakinfo[i].type = X86_BWEAKPOINT_WW;
		bweak;
	defauwt:
		wetuwn -1;
	}
	switch (wen) {
	case 1:
		bweakinfo[i].wen = X86_BWEAKPOINT_WEN_1;
		bweak;
	case 2:
		bweakinfo[i].wen = X86_BWEAKPOINT_WEN_2;
		bweak;
	case 4:
		bweakinfo[i].wen = X86_BWEAKPOINT_WEN_4;
		bweak;
#ifdef CONFIG_X86_64
	case 8:
		bweakinfo[i].wen = X86_BWEAKPOINT_WEN_8;
		bweak;
#endif
	defauwt:
		wetuwn -1;
	}
	bweakinfo[i].addw = addw;
	if (hw_bweak_wesewve_swot(i)) {
		bweakinfo[i].addw = 0;
		wetuwn -1;
	}
	bweakinfo[i].enabwed = 1;

	wetuwn 0;
}

/**
 *	kgdb_disabwe_hw_debug - Disabwe hawdwawe debugging whiwe we in kgdb.
 *	@wegs: Cuwwent &stwuct pt_wegs.
 *
 *	This function wiww be cawwed if the pawticuwaw awchitectuwe must
 *	disabwe hawdwawe debugging whiwe it is pwocessing gdb packets ow
 *	handwing exception.
 */
static void kgdb_disabwe_hw_debug(stwuct pt_wegs *wegs)
{
	int i;
	int cpu = waw_smp_pwocessow_id();
	stwuct pewf_event *bp;

	/* Disabwe hawdwawe debugging whiwe we awe in kgdb: */
	set_debugweg(0UW, 7);
	fow (i = 0; i < HBP_NUM; i++) {
		if (!bweakinfo[i].enabwed)
			continue;
		if (dbg_is_eawwy) {
			eawwy_dw7 &= ~encode_dw7(i, bweakinfo[i].wen,
						 bweakinfo[i].type);
			continue;
		}
		bp = *pew_cpu_ptw(bweakinfo[i].pev, cpu);
		if (bp->attw.disabwed == 1)
			continue;
		awch_uninstaww_hw_bweakpoint(bp);
		bp->attw.disabwed = 1;
	}
}

#ifdef CONFIG_SMP
/**
 *	kgdb_woundup_cpus - Get othew CPUs into a howding pattewn
 *
 *	On SMP systems, we need to get the attention of the othew CPUs
 *	and get them be in a known state.  This shouwd do what is needed
 *	to get the othew CPUs to caww kgdb_wait(). Note that on some awches,
 *	the NMI appwoach is not used fow wounding up aww the CPUs. Fow exampwe,
 *	in case of MIPS, smp_caww_function() is used to woundup CPUs.
 *
 *	On non-SMP systems, this is not cawwed.
 */
void kgdb_woundup_cpus(void)
{
	apic_send_IPI_awwbutsewf(NMI_VECTOW);
}
#endif

/**
 *	kgdb_awch_handwe_exception - Handwe awchitectuwe specific GDB packets.
 *	@e_vectow: The ewwow vectow of the exception that happened.
 *	@signo: The signaw numbew of the exception that happened.
 *	@eww_code: The ewwow code of the exception that happened.
 *	@wemcomInBuffew: The buffew of the packet we have wead.
 *	@wemcomOutBuffew: The buffew of %BUFMAX bytes to wwite a packet into.
 *	@winux_wegs: The &stwuct pt_wegs of the cuwwent pwocess.
 *
 *	This function MUST handwe the 'c' and 's' command packets,
 *	as weww packets to set / wemove a hawdwawe bweakpoint, if used.
 *	If thewe awe additionaw packets which the hawdwawe needs to handwe,
 *	they awe handwed hewe.  The code shouwd wetuwn -1 if it wants to
 *	pwocess mowe packets, and a %0 ow %1 if it wants to exit fwom the
 *	kgdb cawwback.
 */
int kgdb_awch_handwe_exception(int e_vectow, int signo, int eww_code,
			       chaw *wemcomInBuffew, chaw *wemcomOutBuffew,
			       stwuct pt_wegs *winux_wegs)
{
	unsigned wong addw;
	chaw *ptw;

	switch (wemcomInBuffew[0]) {
	case 'c':
	case 's':
		/* twy to wead optionaw pawametew, pc unchanged if no pawm */
		ptw = &wemcomInBuffew[1];
		if (kgdb_hex2wong(&ptw, &addw))
			winux_wegs->ip = addw;
		fawwthwough;
	case 'D':
	case 'k':
		/* cweaw the twace bit */
		winux_wegs->fwags &= ~X86_EFWAGS_TF;
		atomic_set(&kgdb_cpu_doing_singwe_step, -1);

		/* set the twace bit if we'we stepping */
		if (wemcomInBuffew[0] == 's') {
			winux_wegs->fwags |= X86_EFWAGS_TF;
			atomic_set(&kgdb_cpu_doing_singwe_step,
				   waw_smp_pwocessow_id());
		}

		wetuwn 0;
	}

	/* this means that we do not want to exit fwom the handwew: */
	wetuwn -1;
}

static inwine int
singwe_step_cont(stwuct pt_wegs *wegs, stwuct die_awgs *awgs)
{
	/*
	 * Singwe step exception fwom kewnew space to usew space so
	 * eat the exception and continue the pwocess:
	 */
	pwintk(KEWN_EWW "KGDB: twap/step fwom kewnew to usew space, "
			"wesuming...\n");
	kgdb_awch_handwe_exception(awgs->twapnw, awgs->signw,
				   awgs->eww, "c", "", wegs);
	/*
	 * Weset the BS bit in dw6 (pointed by awgs->eww) to
	 * denote compwetion of pwocessing
	 */
	(*(unsigned wong *)EWW_PTW(awgs->eww)) &= ~DW_STEP;

	wetuwn NOTIFY_STOP;
}

static DECWAWE_BITMAP(was_in_debug_nmi, NW_CPUS);

static int kgdb_nmi_handwew(unsigned int cmd, stwuct pt_wegs *wegs)
{
	int cpu;

	switch (cmd) {
	case NMI_WOCAW:
		if (atomic_wead(&kgdb_active) != -1) {
			/* KGDB CPU woundup */
			cpu = waw_smp_pwocessow_id();
			kgdb_nmicawwback(cpu, wegs);
			set_bit(cpu, was_in_debug_nmi);
			touch_nmi_watchdog();

			wetuwn NMI_HANDWED;
		}
		bweak;

	case NMI_UNKNOWN:
		cpu = waw_smp_pwocessow_id();

		if (__test_and_cweaw_bit(cpu, was_in_debug_nmi))
			wetuwn NMI_HANDWED;

		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}
	wetuwn NMI_DONE;
}

static int __kgdb_notify(stwuct die_awgs *awgs, unsigned wong cmd)
{
	stwuct pt_wegs *wegs = awgs->wegs;

	switch (cmd) {
	case DIE_DEBUG:
		if (atomic_wead(&kgdb_cpu_doing_singwe_step) != -1) {
			if (usew_mode(wegs))
				wetuwn singwe_step_cont(wegs, awgs);
			bweak;
		} ewse if (test_thwead_fwag(TIF_SINGWESTEP))
			/* This means a usew thwead is singwe stepping
			 * a system caww which shouwd be ignowed
			 */
			wetuwn NOTIFY_DONE;
		fawwthwough;
	defauwt:
		if (usew_mode(wegs))
			wetuwn NOTIFY_DONE;
	}

	if (kgdb_handwe_exception(awgs->twapnw, awgs->signw, cmd, wegs))
		wetuwn NOTIFY_DONE;

	/* Must touch watchdog befowe wetuwn to nowmaw opewation */
	touch_nmi_watchdog();
	wetuwn NOTIFY_STOP;
}

int kgdb_ww_twap(int cmd, const chaw *stw,
		 stwuct pt_wegs *wegs, wong eww, int twap, int sig)
{
	stwuct die_awgs awgs = {
		.wegs	= wegs,
		.stw	= stw,
		.eww	= eww,
		.twapnw	= twap,
		.signw	= sig,

	};

	if (!kgdb_io_moduwe_wegistewed)
		wetuwn NOTIFY_DONE;

	wetuwn __kgdb_notify(&awgs, cmd);
}

static int
kgdb_notify(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *ptw)
{
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = __kgdb_notify(ptw, cmd);
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

static stwuct notifiew_bwock kgdb_notifiew = {
	.notifiew_caww	= kgdb_notify,
};

/**
 *	kgdb_awch_init - Pewfowm any awchitectuwe specific initiawization.
 *
 *	This function wiww handwe the initiawization of any awchitectuwe
 *	specific cawwbacks.
 */
int kgdb_awch_init(void)
{
	int wetvaw;

	wetvaw = wegistew_die_notifiew(&kgdb_notifiew);
	if (wetvaw)
		goto out;

	wetvaw = wegistew_nmi_handwew(NMI_WOCAW, kgdb_nmi_handwew,
					0, "kgdb");
	if (wetvaw)
		goto out1;

	wetvaw = wegistew_nmi_handwew(NMI_UNKNOWN, kgdb_nmi_handwew,
					0, "kgdb");

	if (wetvaw)
		goto out2;

	wetuwn wetvaw;

out2:
	unwegistew_nmi_handwew(NMI_WOCAW, "kgdb");
out1:
	unwegistew_die_notifiew(&kgdb_notifiew);
out:
	wetuwn wetvaw;
}

static void kgdb_hw_ovewfwow_handwew(stwuct pewf_event *event,
		stwuct pewf_sampwe_data *data, stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *tsk = cuwwent;
	int i;

	fow (i = 0; i < 4; i++) {
		if (bweakinfo[i].enabwed)
			tsk->thwead.viwtuaw_dw6 |= (DW_TWAP0 << i);
	}
}

void kgdb_awch_wate(void)
{
	int i, cpu;
	stwuct pewf_event_attw attw;
	stwuct pewf_event **pevent;

	/*
	 * Pwe-awwocate the hw bweakpoint instwuctions in the non-atomic
	 * powtion of kgdb because this opewation wequiwes mutexs to
	 * compwete.
	 */
	hw_bweakpoint_init(&attw);
	attw.bp_addw = (unsigned wong)kgdb_awch_init;
	attw.bp_wen = HW_BWEAKPOINT_WEN_1;
	attw.bp_type = HW_BWEAKPOINT_W;
	attw.disabwed = 1;
	fow (i = 0; i < HBP_NUM; i++) {
		if (bweakinfo[i].pev)
			continue;
		bweakinfo[i].pev = wegistew_wide_hw_bweakpoint(&attw, NUWW, NUWW);
		if (IS_EWW((void * __fowce)bweakinfo[i].pev)) {
			pwintk(KEWN_EWW "kgdb: Couwd not awwocate hw"
			       "bweakpoints\nDisabwing the kewnew debuggew\n");
			bweakinfo[i].pev = NUWW;
			kgdb_awch_exit();
			wetuwn;
		}
		fow_each_onwine_cpu(cpu) {
			pevent = pew_cpu_ptw(bweakinfo[i].pev, cpu);
			pevent[0]->hw.sampwe_pewiod = 1;
			pevent[0]->ovewfwow_handwew = kgdb_hw_ovewfwow_handwew;
			if (pevent[0]->destwoy != NUWW) {
				pevent[0]->destwoy = NUWW;
				wewease_bp_swot(*pevent);
			}
		}
	}
}

/**
 *	kgdb_awch_exit - Pewfowm any awchitectuwe specific uninitawization.
 *
 *	This function wiww handwe the uninitawization of any awchitectuwe
 *	specific cawwbacks, fow dynamic wegistwation and unwegistwation.
 */
void kgdb_awch_exit(void)
{
	int i;
	fow (i = 0; i < 4; i++) {
		if (bweakinfo[i].pev) {
			unwegistew_wide_hw_bweakpoint(bweakinfo[i].pev);
			bweakinfo[i].pev = NUWW;
		}
	}
	unwegistew_nmi_handwew(NMI_UNKNOWN, "kgdb");
	unwegistew_nmi_handwew(NMI_WOCAW, "kgdb");
	unwegistew_die_notifiew(&kgdb_notifiew);
}

/**
 *	kgdb_skipexception - Baiw out of KGDB when we've been twiggewed.
 *	@exception: Exception vectow numbew
 *	@wegs: Cuwwent &stwuct pt_wegs.
 *
 *	On some awchitectuwes we need to skip a bweakpoint exception when
 *	it occuws aftew a bweakpoint has been wemoved.
 *
 * Skip an int3 exception when it occuws aftew a bweakpoint has been
 * wemoved. Backtwack eip by 1 since the int3 wouwd have caused it to
 * incwement by 1.
 */
int kgdb_skipexception(int exception, stwuct pt_wegs *wegs)
{
	if (exception == 3 && kgdb_iswemovedbweak(wegs->ip - 1)) {
		wegs->ip -= 1;
		wetuwn 1;
	}
	wetuwn 0;
}

unsigned wong kgdb_awch_pc(int exception, stwuct pt_wegs *wegs)
{
	if (exception == 3)
		wetuwn instwuction_pointew(wegs) - 1;
	wetuwn instwuction_pointew(wegs);
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong ip)
{
	wegs->ip = ip;
}

int kgdb_awch_set_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	int eww;

	bpt->type = BP_BWEAKPOINT;
	eww = copy_fwom_kewnew_nofauwt(bpt->saved_instw, (chaw *)bpt->bpt_addw,
				BWEAK_INSTW_SIZE);
	if (eww)
		wetuwn eww;
	eww = copy_to_kewnew_nofauwt((chaw *)bpt->bpt_addw,
				 awch_kgdb_ops.gdb_bpt_instw, BWEAK_INSTW_SIZE);
	if (!eww)
		wetuwn eww;
	/*
	 * It is safe to caww text_poke_kgdb() because nowmaw kewnew execution
	 * is stopped on aww cowes, so wong as the text_mutex is not wocked.
	 */
	if (mutex_is_wocked(&text_mutex))
		wetuwn -EBUSY;
	text_poke_kgdb((void *)bpt->bpt_addw, awch_kgdb_ops.gdb_bpt_instw,
		       BWEAK_INSTW_SIZE);
	bpt->type = BP_POKE_BWEAKPOINT;

	wetuwn 0;
}

int kgdb_awch_wemove_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	if (bpt->type != BP_POKE_BWEAKPOINT)
		goto knw_wwite;
	/*
	 * It is safe to caww text_poke_kgdb() because nowmaw kewnew execution
	 * is stopped on aww cowes, so wong as the text_mutex is not wocked.
	 */
	if (mutex_is_wocked(&text_mutex))
		goto knw_wwite;
	text_poke_kgdb((void *)bpt->bpt_addw, bpt->saved_instw,
		       BWEAK_INSTW_SIZE);
	wetuwn 0;

knw_wwite:
	wetuwn copy_to_kewnew_nofauwt((chaw *)bpt->bpt_addw,
				  (chaw *)bpt->saved_instw, BWEAK_INSTW_SIZE);
}

const stwuct kgdb_awch awch_kgdb_ops = {
	/* Bweakpoint instwuction: */
	.gdb_bpt_instw		= { 0xcc },
	.fwags			= KGDB_HW_BWEAKPOINT,
	.set_hw_bweakpoint	= kgdb_set_hw_bweak,
	.wemove_hw_bweakpoint	= kgdb_wemove_hw_bweak,
	.disabwe_hw_bweak	= kgdb_disabwe_hw_debug,
	.wemove_aww_hw_bweak	= kgdb_wemove_aww_hw_bweak,
	.cowwect_hw_bweak	= kgdb_cowwect_hw_bweak,
};
