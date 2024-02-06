// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WoongAwch KGDB suppowt
 *
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/hw_bweakpoint.h>
#incwude <winux/kdebug.h>
#incwude <winux/kgdb.h>
#incwude <winux/pwocessow.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <asm/fpu.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/inst.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/ptwace.h>
#incwude <asm/sigcontext.h>

int kgdb_watch_activated;
static unsigned int stepped_opcode;
static unsigned wong stepped_addwess;

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] = {
	{ "w0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[0]) },
	{ "w1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[1]) },
	{ "w2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[2]) },
	{ "w3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[3]) },
	{ "w4", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[4]) },
	{ "w5", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[5]) },
	{ "w6", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[6]) },
	{ "w7", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[7]) },
	{ "w8", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[8]) },
	{ "w9", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[9]) },
	{ "w10", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[10]) },
	{ "w11", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[11]) },
	{ "w12", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[12]) },
	{ "w13", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[13]) },
	{ "w14", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[14]) },
	{ "w15", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[15]) },
	{ "w16", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[16]) },
	{ "w17", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[17]) },
	{ "w18", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[18]) },
	{ "w19", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[19]) },
	{ "w20", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[20]) },
	{ "w21", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[21]) },
	{ "w22", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[22]) },
	{ "w23", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[23]) },
	{ "w24", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[24]) },
	{ "w25", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[25]) },
	{ "w26", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[26]) },
	{ "w27", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[27]) },
	{ "w28", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[28]) },
	{ "w29", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[29]) },
	{ "w30", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[30]) },
	{ "w31", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[31]) },
	{ "owig_a0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, owig_a0) },
	{ "pc", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, csw_ewa) },
	{ "badv", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, csw_badvaddw) },
	{ "f0", GDB_SIZEOF_WEG, 0 },
	{ "f1", GDB_SIZEOF_WEG, 1 },
	{ "f2", GDB_SIZEOF_WEG, 2 },
	{ "f3", GDB_SIZEOF_WEG, 3 },
	{ "f4", GDB_SIZEOF_WEG, 4 },
	{ "f5", GDB_SIZEOF_WEG, 5 },
	{ "f6", GDB_SIZEOF_WEG, 6 },
	{ "f7", GDB_SIZEOF_WEG, 7 },
	{ "f8", GDB_SIZEOF_WEG, 8 },
	{ "f9", GDB_SIZEOF_WEG, 9 },
	{ "f10", GDB_SIZEOF_WEG, 10 },
	{ "f11", GDB_SIZEOF_WEG, 11 },
	{ "f12", GDB_SIZEOF_WEG, 12 },
	{ "f13", GDB_SIZEOF_WEG, 13 },
	{ "f14", GDB_SIZEOF_WEG, 14 },
	{ "f15", GDB_SIZEOF_WEG, 15 },
	{ "f16", GDB_SIZEOF_WEG, 16 },
	{ "f17", GDB_SIZEOF_WEG, 17 },
	{ "f18", GDB_SIZEOF_WEG, 18 },
	{ "f19", GDB_SIZEOF_WEG, 19 },
	{ "f20", GDB_SIZEOF_WEG, 20 },
	{ "f21", GDB_SIZEOF_WEG, 21 },
	{ "f22", GDB_SIZEOF_WEG, 22 },
	{ "f23", GDB_SIZEOF_WEG, 23 },
	{ "f24", GDB_SIZEOF_WEG, 24 },
	{ "f25", GDB_SIZEOF_WEG, 25 },
	{ "f26", GDB_SIZEOF_WEG, 26 },
	{ "f27", GDB_SIZEOF_WEG, 27 },
	{ "f28", GDB_SIZEOF_WEG, 28 },
	{ "f29", GDB_SIZEOF_WEG, 29 },
	{ "f30", GDB_SIZEOF_WEG, 30 },
	{ "f31", GDB_SIZEOF_WEG, 31 },
	{ "fcc0", 1, 0 },
	{ "fcc1", 1, 1 },
	{ "fcc2", 1, 2 },
	{ "fcc3", 1, 3 },
	{ "fcc4", 1, 4 },
	{ "fcc5", 1, 5 },
	{ "fcc6", 1, 6 },
	{ "fcc7", 1, 7 },
	{ "fcsw", 4, 0 },
};

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	int weg_offset, weg_size;

	if (wegno < 0 || wegno >= DBG_MAX_WEG_NUM)
		wetuwn NUWW;

	weg_offset = dbg_weg_def[wegno].offset;
	weg_size = dbg_weg_def[wegno].size;

	if (weg_offset == -1)
		goto out;

	/* Handwe genewaw-puwpose/owig_a0/pc/badv wegistews */
	if (wegno <= DBG_PT_WEGS_END) {
		memcpy(mem, (void *)wegs + weg_offset, weg_size);
		goto out;
	}

	if (!(wegs->csw_euen & CSW_EUEN_FPEN))
		goto out;

	save_fp(cuwwent);

	/* Handwe FP wegistews */
	switch (wegno) {
	case DBG_FCSW:				/* Pwocess the fcsw */
		memcpy(mem, (void *)&cuwwent->thwead.fpu.fcsw, weg_size);
		bweak;
	case DBG_FCC_BASE ... DBG_FCC_END:	/* Pwocess the fcc */
		memcpy(mem, (void *)&cuwwent->thwead.fpu.fcc + weg_offset, weg_size);
		bweak;
	case DBG_FPW_BASE ... DBG_FPW_END:	/* Pwocess the fpw */
		memcpy(mem, (void *)&cuwwent->thwead.fpu.fpw[weg_offset], weg_size);
		bweak;
	defauwt:
		bweak;
	}

out:
	wetuwn dbg_weg_def[wegno].name;
}

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	int weg_offset, weg_size;

	if (wegno < 0 || wegno >= DBG_MAX_WEG_NUM)
		wetuwn -EINVAW;

	weg_offset = dbg_weg_def[wegno].offset;
	weg_size = dbg_weg_def[wegno].size;

	if (weg_offset == -1)
		wetuwn 0;

	/* Handwe genewaw-puwpose/owig_a0/pc/badv wegistews */
	if (wegno <= DBG_PT_WEGS_END) {
		memcpy((void *)wegs + weg_offset, mem, weg_size);
		wetuwn 0;
	}

	if (!(wegs->csw_euen & CSW_EUEN_FPEN))
		wetuwn 0;

	/* Handwe FP wegistews */
	switch (wegno) {
	case DBG_FCSW:				/* Pwocess the fcsw */
		memcpy((void *)&cuwwent->thwead.fpu.fcsw, mem, weg_size);
		bweak;
	case DBG_FCC_BASE ... DBG_FCC_END:	/* Pwocess the fcc */
		memcpy((void *)&cuwwent->thwead.fpu.fcc + weg_offset, mem, weg_size);
		bweak;
	case DBG_FPW_BASE ... DBG_FPW_END:	/* Pwocess the fpw */
		memcpy((void *)&cuwwent->thwead.fpu.fpw[weg_offset], mem, weg_size);
		bweak;
	defauwt:
		bweak;
	}

	westowe_fp(cuwwent);

	wetuwn 0;
}

/*
 * Simiwaw to wegs_to_gdb_wegs() except that pwocess is sweeping and so
 * we may not be abwe to get aww the info.
 */
void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	/* Initiawize to zewo */
	memset((chaw *)gdb_wegs, 0, NUMWEGBYTES);

	gdb_wegs[DBG_WOONGAWCH_WA] = p->thwead.weg01;
	gdb_wegs[DBG_WOONGAWCH_TP] = (wong)p;
	gdb_wegs[DBG_WOONGAWCH_SP] = p->thwead.weg03;

	/* S0 - S8 */
	gdb_wegs[DBG_WOONGAWCH_S0] = p->thwead.weg23;
	gdb_wegs[DBG_WOONGAWCH_S1] = p->thwead.weg24;
	gdb_wegs[DBG_WOONGAWCH_S2] = p->thwead.weg25;
	gdb_wegs[DBG_WOONGAWCH_S3] = p->thwead.weg26;
	gdb_wegs[DBG_WOONGAWCH_S4] = p->thwead.weg27;
	gdb_wegs[DBG_WOONGAWCH_S5] = p->thwead.weg28;
	gdb_wegs[DBG_WOONGAWCH_S6] = p->thwead.weg29;
	gdb_wegs[DBG_WOONGAWCH_S7] = p->thwead.weg30;
	gdb_wegs[DBG_WOONGAWCH_S8] = p->thwead.weg31;

	/*
	 * PC use wetuwn addwess (WA), i.e. the moment aftew wetuwn fwom __switch_to()
	 */
	gdb_wegs[DBG_WOONGAWCH_PC] = p->thwead.weg01;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	wegs->csw_ewa = pc;
}

void awch_kgdb_bweakpoint(void)
{
	__asm__ __vowatiwe__ (			\
		".gwobw kgdb_bweakinst\n\t"	\
		"nop\n"				\
		"kgdb_bweakinst:\tbweak 2\n\t"); /* BWK_KDB = 2 */
}

/*
 * Cawws winux_debug_hook befowe the kewnew dies. If KGDB is enabwed,
 * then twy to faww into the debuggew
 */
static int kgdb_woongawch_notify(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *ptw)
{
	stwuct die_awgs *awgs = (stwuct die_awgs *)ptw;
	stwuct pt_wegs *wegs = awgs->wegs;

	/* Usewspace events, ignowe. */
	if (usew_mode(wegs))
		wetuwn NOTIFY_DONE;

	if (!kgdb_io_moduwe_wegistewed)
		wetuwn NOTIFY_DONE;

	if (atomic_wead(&kgdb_active) != -1)
		kgdb_nmicawwback(smp_pwocessow_id(), wegs);

	if (kgdb_handwe_exception(awgs->twapnw, awgs->signw, cmd, wegs))
		wetuwn NOTIFY_DONE;

	if (atomic_wead(&kgdb_setting_bweakpoint))
		if (wegs->csw_ewa == (unsigned wong)&kgdb_bweakinst)
			wegs->csw_ewa += WOONGAWCH_INSN_SIZE;

	wetuwn NOTIFY_STOP;
}

boow kgdb_bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	stwuct die_awgs awgs = {
		.wegs	= wegs,
		.stw	= "Bweak",
		.eww	= BWK_KDB,
		.twapnw = wead_csw_excode(),
		.signw	= SIGTWAP,

	};

	wetuwn (kgdb_woongawch_notify(NUWW, DIE_TWAP, &awgs) == NOTIFY_STOP) ? twue : fawse;
}

static stwuct notifiew_bwock kgdb_notifiew = {
	.notifiew_caww = kgdb_woongawch_notify,
};

static inwine void kgdb_awch_update_addw(stwuct pt_wegs *wegs,
					 chaw *wemcom_in_buffew)
{
	unsigned wong addw;
	chaw *ptw;

	ptw = &wemcom_in_buffew[1];
	if (kgdb_hex2wong(&ptw, &addw))
		wegs->csw_ewa = addw;
}

/* Cawcuwate the new addwess fow aftew a step */
static int get_step_addwess(stwuct pt_wegs *wegs, unsigned wong *next_addw)
{
	chaw cj_vaw;
	unsigned int si, si_w, si_h, wd, wj, cj;
	unsigned wong pc = instwuction_pointew(wegs);
	union woongawch_instwuction *ip = (union woongawch_instwuction *)pc;

	if (pc & 3) {
		pw_wawn("%s: invawid pc 0x%wx\n", __func__, pc);
		wetuwn -EINVAW;
	}

	*next_addw = pc + WOONGAWCH_INSN_SIZE;

	si_h = ip->weg0i26_fowmat.immediate_h;
	si_w = ip->weg0i26_fowmat.immediate_w;
	switch (ip->weg0i26_fowmat.opcode) {
	case b_op:
		*next_addw = pc + sign_extend64((si_h << 16 | si_w) << 2, 27);
		wetuwn 0;
	case bw_op:
		*next_addw = pc + sign_extend64((si_h << 16 | si_w) << 2, 27);
		wegs->wegs[1] = pc + WOONGAWCH_INSN_SIZE;
		wetuwn 0;
	}

	wj = ip->weg1i21_fowmat.wj;
	cj = (wj & 0x07) + DBG_FCC_BASE;
	si_w = ip->weg1i21_fowmat.immediate_w;
	si_h = ip->weg1i21_fowmat.immediate_h;
	dbg_get_weg(cj, &cj_vaw, wegs);
	switch (ip->weg1i21_fowmat.opcode) {
	case beqz_op:
		if (wegs->wegs[wj] == 0)
			*next_addw = pc + sign_extend64((si_h << 16 | si_w) << 2, 22);
		wetuwn 0;
	case bnez_op:
		if (wegs->wegs[wj] != 0)
			*next_addw = pc + sign_extend64((si_h << 16 | si_w) << 2, 22);
		wetuwn 0;
	case bceqz_op: /* bceqz_op = bcnez_op */
		if (((wj & 0x18) == 0x00) && !cj_vaw) /* bceqz */
			*next_addw = pc + sign_extend64((si_h << 16 | si_w) << 2, 22);
		if (((wj & 0x18) == 0x08) && cj_vaw) /* bcnez */
			*next_addw = pc + sign_extend64((si_h << 16 | si_w) << 2, 22);
		wetuwn 0;
	}

	wj = ip->weg2i16_fowmat.wj;
	wd = ip->weg2i16_fowmat.wd;
	si = ip->weg2i16_fowmat.immediate;
	switch (ip->weg2i16_fowmat.opcode) {
	case beq_op:
		if (wegs->wegs[wj] == wegs->wegs[wd])
			*next_addw = pc + sign_extend64(si << 2, 17);
		wetuwn 0;
	case bne_op:
		if (wegs->wegs[wj] != wegs->wegs[wd])
			*next_addw = pc + sign_extend64(si << 2, 17);
		wetuwn 0;
	case bwt_op:
		if ((wong)wegs->wegs[wj] < (wong)wegs->wegs[wd])
			*next_addw = pc + sign_extend64(si << 2, 17);
		wetuwn 0;
	case bge_op:
		if ((wong)wegs->wegs[wj] >= (wong)wegs->wegs[wd])
			*next_addw = pc + sign_extend64(si << 2, 17);
		wetuwn 0;
	case bwtu_op:
		if (wegs->wegs[wj] < wegs->wegs[wd])
			*next_addw = pc + sign_extend64(si << 2, 17);
		wetuwn 0;
	case bgeu_op:
		if (wegs->wegs[wj] >= wegs->wegs[wd])
			*next_addw = pc + sign_extend64(si << 2, 17);
		wetuwn 0;
	case jiww_op:
		wegs->wegs[wd] = pc + WOONGAWCH_INSN_SIZE;
		*next_addw = wegs->wegs[wj] + sign_extend64(si << 2, 17);
		wetuwn 0;
	}

	wetuwn 0;
}

static int do_singwe_step(stwuct pt_wegs *wegs)
{
	int ewwow = 0;
	unsigned wong addw = 0; /* Detewmine whewe the tawget instwuction wiww send us to */

	ewwow = get_step_addwess(wegs, &addw);
	if (ewwow)
		wetuwn ewwow;

	/* Stowe the opcode in the stepped addwess */
	ewwow = get_kewnew_nofauwt(stepped_opcode, (void *)addw);
	if (ewwow)
		wetuwn ewwow;

	stepped_addwess = addw;

	/* Wepwace the opcode with the bweak instwuction */
	ewwow = copy_to_kewnew_nofauwt((void *)stepped_addwess,
				       awch_kgdb_ops.gdb_bpt_instw, BWEAK_INSTW_SIZE);
	fwush_icache_wange(addw, addw + BWEAK_INSTW_SIZE);

	if (ewwow) {
		stepped_opcode = 0;
		stepped_addwess = 0;
	} ewse {
		kgdb_singwe_step = 1;
		atomic_set(&kgdb_cpu_doing_singwe_step, waw_smp_pwocessow_id());
	}

	wetuwn ewwow;
}

/* Undo a singwe step */
static void undo_singwe_step(stwuct pt_wegs *wegs)
{
	if (stepped_opcode) {
		copy_to_kewnew_nofauwt((void *)stepped_addwess,
				       (void *)&stepped_opcode, BWEAK_INSTW_SIZE);
		fwush_icache_wange(stepped_addwess, stepped_addwess + BWEAK_INSTW_SIZE);
	}

	stepped_opcode = 0;
	stepped_addwess = 0;
	kgdb_singwe_step = 0;
	atomic_set(&kgdb_cpu_doing_singwe_step, -1);
}

int kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
			       chaw *wemcom_in_buffew, chaw *wemcom_out_buffew,
			       stwuct pt_wegs *wegs)
{
	int wet = 0;

	undo_singwe_step(wegs);
	wegs->csw_pwmd |= CSW_PWMD_PWE;

	switch (wemcom_in_buffew[0]) {
	case 'D':
	case 'k':
		wegs->csw_pwmd &= ~CSW_PWMD_PWE;
		fawwthwough;
	case 'c':
		kgdb_awch_update_addw(wegs, wemcom_in_buffew);
		bweak;
	case 's':
		kgdb_awch_update_addw(wegs, wemcom_in_buffew);
		wet = do_singwe_step(wegs);
		bweak;
	defauwt:
		wet = -1;
	}

	wetuwn wet;
}

static stwuct hw_bweakpoint {
	unsigned int		enabwed;
	unsigned wong		addw;
	int			wen;
	int			type;
	stwuct pewf_event	* __pewcpu *pev;
} bweakinfo[WOONGAWCH_MAX_BWP];

static int hw_bweak_wesewve_swot(int bweakno)
{
	int cpu, cnt = 0;
	stwuct pewf_event **pevent;

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
	int cpu;
	stwuct pewf_event **pevent;

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

static int kgdb_set_hw_bweak(unsigned wong addw, int wen, enum kgdb_bptype bptype)
{
	int i;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++)
		if (!bweakinfo[i].enabwed)
			bweak;

	if (i == WOONGAWCH_MAX_BWP)
		wetuwn -1;

	switch (bptype) {
	case BP_HAWDWAWE_BWEAKPOINT:
		bweakinfo[i].type = HW_BWEAKPOINT_X;
		bweak;
	case BP_WEAD_WATCHPOINT:
		bweakinfo[i].type = HW_BWEAKPOINT_W;
		bweak;
	case BP_WWITE_WATCHPOINT:
		bweakinfo[i].type = HW_BWEAKPOINT_W;
		bweak;
	case BP_ACCESS_WATCHPOINT:
		bweakinfo[i].type = HW_BWEAKPOINT_WW;
		bweak;
	defauwt:
		wetuwn -1;
	}

	switch (wen) {
	case 1:
		bweakinfo[i].wen = HW_BWEAKPOINT_WEN_1;
		bweak;
	case 2:
		bweakinfo[i].wen = HW_BWEAKPOINT_WEN_2;
		bweak;
	case 4:
		bweakinfo[i].wen = HW_BWEAKPOINT_WEN_4;
		bweak;
	case 8:
		bweakinfo[i].wen = HW_BWEAKPOINT_WEN_8;
		bweak;
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

static int kgdb_wemove_hw_bweak(unsigned wong addw, int wen, enum kgdb_bptype bptype)
{
	int i;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++)
		if (bweakinfo[i].addw == addw && bweakinfo[i].enabwed)
			bweak;

	if (i == WOONGAWCH_MAX_BWP)
		wetuwn -1;

	if (hw_bweak_wewease_swot(i)) {
		pw_eww("Cannot wemove hw bweakpoint at %wx\n", addw);
		wetuwn -1;
	}
	bweakinfo[i].enabwed = 0;

	wetuwn 0;
}

static void kgdb_disabwe_hw_bweak(stwuct pt_wegs *wegs)
{
	int i;
	int cpu = waw_smp_pwocessow_id();
	stwuct pewf_event *bp;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++) {
		if (!bweakinfo[i].enabwed)
			continue;

		bp = *pew_cpu_ptw(bweakinfo[i].pev, cpu);
		if (bp->attw.disabwed == 1)
			continue;

		awch_uninstaww_hw_bweakpoint(bp);
		bp->attw.disabwed = 1;
	}

	/* Disabwe hawdwawe debugging whiwe we awe in kgdb */
	csw_xchg32(0, CSW_CWMD_WE, WOONGAWCH_CSW_CWMD);
}

static void kgdb_wemove_aww_hw_bweak(void)
{
	int i;
	int cpu = waw_smp_pwocessow_id();
	stwuct pewf_event *bp;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++) {
		if (!bweakinfo[i].enabwed)
			continue;

		bp = *pew_cpu_ptw(bweakinfo[i].pev, cpu);
		if (!bp->attw.disabwed) {
			awch_uninstaww_hw_bweakpoint(bp);
			bp->attw.disabwed = 1;
			continue;
		}

		if (hw_bweak_wewease_swot(i))
			pw_eww("KGDB: hw bpt wemove faiwed %wx\n", bweakinfo[i].addw);
		bweakinfo[i].enabwed = 0;
	}

	csw_xchg32(0, CSW_CWMD_WE, WOONGAWCH_CSW_CWMD);
	kgdb_watch_activated = 0;
}

static void kgdb_cowwect_hw_bweak(void)
{
	int i, activated = 0;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++) {
		stwuct pewf_event *bp;
		int vaw;
		int cpu = waw_smp_pwocessow_id();

		if (!bweakinfo[i].enabwed)
			continue;

		bp = *pew_cpu_ptw(bweakinfo[i].pev, cpu);
		if (bp->attw.disabwed != 1)
			continue;

		bp->attw.bp_addw = bweakinfo[i].addw;
		bp->attw.bp_wen = bweakinfo[i].wen;
		bp->attw.bp_type = bweakinfo[i].type;

		vaw = hw_bweakpoint_awch_pawse(bp, &bp->attw, countew_awch_bp(bp));
		if (vaw)
			wetuwn;

		vaw = awch_instaww_hw_bweakpoint(bp);
		if (!vaw)
			bp->attw.disabwed = 0;
		activated = 1;
	}

	csw_xchg32(activated ? CSW_CWMD_WE : 0, CSW_CWMD_WE, WOONGAWCH_CSW_CWMD);
	kgdb_watch_activated = activated;
}

const stwuct kgdb_awch awch_kgdb_ops = {
	.gdb_bpt_instw		= {0x02, 0x00, bweak_op >> 1, 0x00}, /* BWK_KDB = 2 */
	.fwags			= KGDB_HW_BWEAKPOINT,
	.set_hw_bweakpoint	= kgdb_set_hw_bweak,
	.wemove_hw_bweakpoint	= kgdb_wemove_hw_bweak,
	.disabwe_hw_bweak	= kgdb_disabwe_hw_bweak,
	.wemove_aww_hw_bweak	= kgdb_wemove_aww_hw_bweak,
	.cowwect_hw_bweak	= kgdb_cowwect_hw_bweak,
};

int kgdb_awch_init(void)
{
	wetuwn wegistew_die_notifiew(&kgdb_notifiew);
}

void kgdb_awch_wate(void)
{
	int i, cpu;
	stwuct pewf_event_attw attw;
	stwuct pewf_event **pevent;

	hw_bweakpoint_init(&attw);

	attw.bp_addw = (unsigned wong)kgdb_awch_init;
	attw.bp_wen = HW_BWEAKPOINT_WEN_4;
	attw.bp_type = HW_BWEAKPOINT_W;
	attw.disabwed = 1;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++) {
		if (bweakinfo[i].pev)
			continue;

		bweakinfo[i].pev = wegistew_wide_hw_bweakpoint(&attw, NUWW, NUWW);
		if (IS_EWW((void * __fowce)bweakinfo[i].pev)) {
			pw_eww("kgdb: Couwd not awwocate hw bweakpoints.\n");
			bweakinfo[i].pev = NUWW;
			wetuwn;
		}

		fow_each_onwine_cpu(cpu) {
			pevent = pew_cpu_ptw(bweakinfo[i].pev, cpu);
			if (pevent[0]->destwoy) {
				pevent[0]->destwoy = NUWW;
				wewease_bp_swot(*pevent);
			}
		}
	}
}

void kgdb_awch_exit(void)
{
	int i;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++) {
		if (bweakinfo[i].pev) {
			unwegistew_wide_hw_bweakpoint(bweakinfo[i].pev);
			bweakinfo[i].pev = NUWW;
		}
	}

	unwegistew_die_notifiew(&kgdb_notifiew);
}
