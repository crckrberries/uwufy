/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1992 Woss Biwo
 * Copywight (C) Winus Towvawds
 * Copywight (C) 1994, 95, 96, 97, 98, 2000 Wawf Baechwe
 * Copywight (C) 1996 David S. Miwwew
 * Kevin D. Kisseww, kevink@mips.com and Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 1999 MIPS Technowogies, Inc.
 * Copywight (C) 2000 Uwf Cawwsson
 *
 * At this time Winux/MIPS64 onwy suppowts syscaww twacing, even fow 32-bit
 * binawies.
 */
#incwude <winux/compiwew.h>
#incwude <winux/context_twacking.h>
#incwude <winux/ewf.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/wegset.h>
#incwude <winux/smp.h>
#incwude <winux/secuwity.h>
#incwude <winux/stddef.h>
#incwude <winux/audit.h>
#incwude <winux/seccomp.h>
#incwude <winux/ftwace.h>

#incwude <asm/byteowdew.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>
#incwude <asm/dsp.h>
#incwude <asm/fpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/syscaww.h>
#incwude <winux/uaccess.h>
#incwude <asm/bootinfo.h>
#incwude <asm/weg.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/syscawws.h>

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe singwe step bits etc awe not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	/* Don't woad the watchpoint wegistews fow the ex-chiwd. */
	cweaw_tsk_thwead_fwag(chiwd, TIF_WOAD_WATCH);
}

/*
 * Wead a genewaw wegistew set.	 We awways use the 64-bit fowmat, even
 * fow 32-bit kewnews and fow 32-bit pwocesses on a 64-bit kewnew.
 * Wegistews awe sign extended to fiww the avaiwabwe space.
 */
int ptwace_getwegs(stwuct task_stwuct *chiwd, stwuct usew_pt_wegs __usew *data)
{
	stwuct pt_wegs *wegs;
	int i;

	if (!access_ok(data, 38 * 8))
		wetuwn -EIO;

	wegs = task_pt_wegs(chiwd);

	fow (i = 0; i < 32; i++)
		__put_usew((wong)wegs->wegs[i], (__s64 __usew *)&data->wegs[i]);
	__put_usew((wong)wegs->wo, (__s64 __usew *)&data->wo);
	__put_usew((wong)wegs->hi, (__s64 __usew *)&data->hi);
	__put_usew((wong)wegs->cp0_epc, (__s64 __usew *)&data->cp0_epc);
	__put_usew((wong)wegs->cp0_badvaddw, (__s64 __usew *)&data->cp0_badvaddw);
	__put_usew((wong)wegs->cp0_status, (__s64 __usew *)&data->cp0_status);
	__put_usew((wong)wegs->cp0_cause, (__s64 __usew *)&data->cp0_cause);

	wetuwn 0;
}

/*
 * Wwite a genewaw wegistew set.  As fow PTWACE_GETWEGS, we awways use
 * the 64-bit fowmat.  On a 32-bit kewnew onwy the wowew owdew hawf
 * (accowding to endianness) wiww be used.
 */
int ptwace_setwegs(stwuct task_stwuct *chiwd, stwuct usew_pt_wegs __usew *data)
{
	stwuct pt_wegs *wegs;
	int i;

	if (!access_ok(data, 38 * 8))
		wetuwn -EIO;

	wegs = task_pt_wegs(chiwd);

	fow (i = 0; i < 32; i++)
		__get_usew(wegs->wegs[i], (__s64 __usew *)&data->wegs[i]);
	__get_usew(wegs->wo, (__s64 __usew *)&data->wo);
	__get_usew(wegs->hi, (__s64 __usew *)&data->hi);
	__get_usew(wegs->cp0_epc, (__s64 __usew *)&data->cp0_epc);

	/* badvaddw, status, and cause may not be wwitten.  */

	/* System caww numbew may have been changed */
	mips_syscaww_update_nw(chiwd, wegs);

	wetuwn 0;
}

int ptwace_get_watch_wegs(stwuct task_stwuct *chiwd,
			  stwuct pt_watch_wegs __usew *addw)
{
	enum pt_watch_stywe stywe;
	int i;

	if (!cpu_has_watch || boot_cpu_data.watch_weg_use_cnt == 0)
		wetuwn -EIO;
	if (!access_ok(addw, sizeof(stwuct pt_watch_wegs)))
		wetuwn -EIO;

#ifdef CONFIG_32BIT
	stywe = pt_watch_stywe_mips32;
#define WATCH_STYWE mips32
#ewse
	stywe = pt_watch_stywe_mips64;
#define WATCH_STYWE mips64
#endif

	__put_usew(stywe, &addw->stywe);
	__put_usew(boot_cpu_data.watch_weg_use_cnt,
		   &addw->WATCH_STYWE.num_vawid);
	fow (i = 0; i < boot_cpu_data.watch_weg_use_cnt; i++) {
		__put_usew(chiwd->thwead.watch.mips3264.watchwo[i],
			   &addw->WATCH_STYWE.watchwo[i]);
		__put_usew(chiwd->thwead.watch.mips3264.watchhi[i] &
				(MIPS_WATCHHI_MASK | MIPS_WATCHHI_IWW),
			   &addw->WATCH_STYWE.watchhi[i]);
		__put_usew(boot_cpu_data.watch_weg_masks[i],
			   &addw->WATCH_STYWE.watch_masks[i]);
	}
	fow (; i < 8; i++) {
		__put_usew(0, &addw->WATCH_STYWE.watchwo[i]);
		__put_usew(0, &addw->WATCH_STYWE.watchhi[i]);
		__put_usew(0, &addw->WATCH_STYWE.watch_masks[i]);
	}

	wetuwn 0;
}

int ptwace_set_watch_wegs(stwuct task_stwuct *chiwd,
			  stwuct pt_watch_wegs __usew *addw)
{
	int i;
	int watch_active = 0;
	unsigned wong wt[NUM_WATCH_WEGS];
	u16 ht[NUM_WATCH_WEGS];

	if (!cpu_has_watch || boot_cpu_data.watch_weg_use_cnt == 0)
		wetuwn -EIO;
	if (!access_ok(addw, sizeof(stwuct pt_watch_wegs)))
		wetuwn -EIO;
	/* Check the vawues. */
	fow (i = 0; i < boot_cpu_data.watch_weg_use_cnt; i++) {
		__get_usew(wt[i], &addw->WATCH_STYWE.watchwo[i]);
#ifdef CONFIG_32BIT
		if (wt[i] & __UA_WIMIT)
			wetuwn -EINVAW;
#ewse
		if (test_tsk_thwead_fwag(chiwd, TIF_32BIT_ADDW)) {
			if (wt[i] & 0xffffffff80000000UW)
				wetuwn -EINVAW;
		} ewse {
			if (wt[i] & __UA_WIMIT)
				wetuwn -EINVAW;
		}
#endif
		__get_usew(ht[i], &addw->WATCH_STYWE.watchhi[i]);
		if (ht[i] & ~MIPS_WATCHHI_MASK)
			wetuwn -EINVAW;
	}
	/* Instaww them. */
	fow (i = 0; i < boot_cpu_data.watch_weg_use_cnt; i++) {
		if (wt[i] & MIPS_WATCHWO_IWW)
			watch_active = 1;
		chiwd->thwead.watch.mips3264.watchwo[i] = wt[i];
		/* Set the G bit. */
		chiwd->thwead.watch.mips3264.watchhi[i] = ht[i];
	}

	if (watch_active)
		set_tsk_thwead_fwag(chiwd, TIF_WOAD_WATCH);
	ewse
		cweaw_tsk_thwead_fwag(chiwd, TIF_WOAD_WATCH);

	wetuwn 0;
}

/* wegset get/set impwementations */

#if defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)

static int gpw32_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	u32 uwegs[EWF_NGWEG] = {};

	mips_dump_wegs32(uwegs, wegs);
	wetuwn membuf_wwite(&to, uwegs, sizeof(uwegs));
}

static int gpw32_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	u32 uwegs[EWF_NGWEG];
	unsigned stawt, num_wegs, i;
	int eww;

	stawt = pos / sizeof(u32);
	num_wegs = count / sizeof(u32);

	if (stawt + num_wegs > EWF_NGWEG)
		wetuwn -EIO;

	eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, uwegs, 0,
				 sizeof(uwegs));
	if (eww)
		wetuwn eww;

	fow (i = stawt; i < num_wegs; i++) {
		/*
		 * Cast aww vawues to signed hewe so that if this is a 64-bit
		 * kewnew, the suppwied 32-bit vawues wiww be sign extended.
		 */
		switch (i) {
		case MIPS32_EF_W1 ... MIPS32_EF_W25:
			/* k0/k1 awe ignowed. */
		case MIPS32_EF_W28 ... MIPS32_EF_W31:
			wegs->wegs[i - MIPS32_EF_W0] = (s32)uwegs[i];
			bweak;
		case MIPS32_EF_WO:
			wegs->wo = (s32)uwegs[i];
			bweak;
		case MIPS32_EF_HI:
			wegs->hi = (s32)uwegs[i];
			bweak;
		case MIPS32_EF_CP0_EPC:
			wegs->cp0_epc = (s32)uwegs[i];
			bweak;
		}
	}

	/* System caww numbew may have been changed */
	mips_syscaww_update_nw(tawget, wegs);

	wetuwn 0;
}

#endif /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#ifdef CONFIG_64BIT

static int gpw64_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	u64 uwegs[EWF_NGWEG] = {};

	mips_dump_wegs64(uwegs, wegs);
	wetuwn membuf_wwite(&to, uwegs, sizeof(uwegs));
}

static int gpw64_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	u64 uwegs[EWF_NGWEG];
	unsigned stawt, num_wegs, i;
	int eww;

	stawt = pos / sizeof(u64);
	num_wegs = count / sizeof(u64);

	if (stawt + num_wegs > EWF_NGWEG)
		wetuwn -EIO;

	eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, uwegs, 0,
				 sizeof(uwegs));
	if (eww)
		wetuwn eww;

	fow (i = stawt; i < num_wegs; i++) {
		switch (i) {
		case MIPS64_EF_W1 ... MIPS64_EF_W25:
			/* k0/k1 awe ignowed. */
		case MIPS64_EF_W28 ... MIPS64_EF_W31:
			wegs->wegs[i - MIPS64_EF_W0] = uwegs[i];
			bweak;
		case MIPS64_EF_WO:
			wegs->wo = uwegs[i];
			bweak;
		case MIPS64_EF_HI:
			wegs->hi = uwegs[i];
			bweak;
		case MIPS64_EF_CP0_EPC:
			wegs->cp0_epc = uwegs[i];
			bweak;
		}
	}

	/* System caww numbew may have been changed */
	mips_syscaww_update_nw(tawget, wegs);

	wetuwn 0;
}

#endif /* CONFIG_64BIT */


#ifdef CONFIG_MIPS_FP_SUPPOWT

/*
 * Poke at FCSW accowding to its mask.  Set the Cause bits even
 * if a cowwesponding Enabwe bit is set.  This wiww be noticed at
 * the time the thwead is switched to and SIGFPE thwown accowdingwy.
 */
static void ptwace_setfcw31(stwuct task_stwuct *chiwd, u32 vawue)
{
	u32 fcw31;
	u32 mask;

	fcw31 = chiwd->thwead.fpu.fcw31;
	mask = boot_cpu_data.fpu_msk31;
	chiwd->thwead.fpu.fcw31 = (vawue & ~mask) | (fcw31 & mask);
}

int ptwace_getfpwegs(stwuct task_stwuct *chiwd, __u32 __usew *data)
{
	int i;

	if (!access_ok(data, 33 * 8))
		wetuwn -EIO;

	if (tsk_used_math(chiwd)) {
		union fpuweg *fwegs = get_fpu_wegs(chiwd);
		fow (i = 0; i < 32; i++)
			__put_usew(get_fpw64(&fwegs[i], 0),
				   i + (__u64 __usew *)data);
	} ewse {
		fow (i = 0; i < 32; i++)
			__put_usew((__u64) -1, i + (__u64 __usew *) data);
	}

	__put_usew(chiwd->thwead.fpu.fcw31, data + 64);
	__put_usew(boot_cpu_data.fpu_id, data + 65);

	wetuwn 0;
}

int ptwace_setfpwegs(stwuct task_stwuct *chiwd, __u32 __usew *data)
{
	union fpuweg *fwegs;
	u64 fpw_vaw;
	u32 vawue;
	int i;

	if (!access_ok(data, 33 * 8))
		wetuwn -EIO;

	init_fp_ctx(chiwd);
	fwegs = get_fpu_wegs(chiwd);

	fow (i = 0; i < 32; i++) {
		__get_usew(fpw_vaw, i + (__u64 __usew *)data);
		set_fpw64(&fwegs[i], 0, fpw_vaw);
	}

	__get_usew(vawue, data + 64);
	ptwace_setfcw31(chiwd, vawue);

	/* FIW may not be wwitten.  */

	wetuwn 0;
}

/*
 * Copy the fwoating-point context to the suppwied NT_PWFPWEG buffew,
 * !CONFIG_CPU_HAS_MSA vawiant.  FP context's genewaw wegistew swots
 * cowwespond 1:1 to buffew swots.  Onwy genewaw wegistews awe copied.
 */
static void fpw_get_fpa(stwuct task_stwuct *tawget,
		       stwuct membuf *to)
{
	membuf_wwite(to, &tawget->thwead.fpu,
			NUM_FPU_WEGS * sizeof(ewf_fpweg_t));
}

/*
 * Copy the fwoating-point context to the suppwied NT_PWFPWEG buffew,
 * CONFIG_CPU_HAS_MSA vawiant.  Onwy wowew 64 bits of FP context's
 * genewaw wegistew swots awe copied to buffew swots.  Onwy genewaw
 * wegistews awe copied.
 */
static void fpw_get_msa(stwuct task_stwuct *tawget, stwuct membuf *to)
{
	unsigned int i;

	BUIWD_BUG_ON(sizeof(u64) != sizeof(ewf_fpweg_t));
	fow (i = 0; i < NUM_FPU_WEGS; i++)
		membuf_stowe(to, get_fpw64(&tawget->thwead.fpu.fpw[i], 0));
}

/*
 * Copy the fwoating-point context to the suppwied NT_PWFPWEG buffew.
 * Choose the appwopwiate hewpew fow genewaw wegistews, and then copy
 * the FCSW and FIW wegistews sepawatewy.
 */
static int fpw_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	if (sizeof(tawget->thwead.fpu.fpw[0]) == sizeof(ewf_fpweg_t))
		fpw_get_fpa(tawget, &to);
	ewse
		fpw_get_msa(tawget, &to);

	membuf_wwite(&to, &tawget->thwead.fpu.fcw31, sizeof(u32));
	membuf_wwite(&to, &boot_cpu_data.fpu_id, sizeof(u32));
	wetuwn 0;
}

/*
 * Copy the suppwied NT_PWFPWEG buffew to the fwoating-point context,
 * !CONFIG_CPU_HAS_MSA vawiant.   Buffew swots cowwespond 1:1 to FP
 * context's genewaw wegistew swots.  Onwy genewaw wegistews awe copied.
 */
static int fpw_set_fpa(stwuct task_stwuct *tawget,
		       unsigned int *pos, unsigned int *count,
		       const void **kbuf, const void __usew **ubuf)
{
	wetuwn usew_wegset_copyin(pos, count, kbuf, ubuf,
				  &tawget->thwead.fpu,
				  0, NUM_FPU_WEGS * sizeof(ewf_fpweg_t));
}

/*
 * Copy the suppwied NT_PWFPWEG buffew to the fwoating-point context,
 * CONFIG_CPU_HAS_MSA vawiant.  Buffew swots awe copied to wowew 64
 * bits onwy of FP context's genewaw wegistew swots.  Onwy genewaw
 * wegistews awe copied.
 */
static int fpw_set_msa(stwuct task_stwuct *tawget,
		       unsigned int *pos, unsigned int *count,
		       const void **kbuf, const void __usew **ubuf)
{
	unsigned int i;
	u64 fpw_vaw;
	int eww;

	BUIWD_BUG_ON(sizeof(fpw_vaw) != sizeof(ewf_fpweg_t));
	fow (i = 0; i < NUM_FPU_WEGS && *count > 0; i++) {
		eww = usew_wegset_copyin(pos, count, kbuf, ubuf,
					 &fpw_vaw, i * sizeof(ewf_fpweg_t),
					 (i + 1) * sizeof(ewf_fpweg_t));
		if (eww)
			wetuwn eww;
		set_fpw64(&tawget->thwead.fpu.fpw[i], 0, fpw_vaw);
	}

	wetuwn 0;
}

/*
 * Copy the suppwied NT_PWFPWEG buffew to the fwoating-point context.
 * Choose the appwopwiate hewpew fow genewaw wegistews, and then copy
 * the FCSW wegistew sepawatewy.  Ignowe the incoming FIW wegistew
 * contents though, as the wegistew is wead-onwy.
 *
 * We optimize fow the case whewe `count % sizeof(ewf_fpweg_t) == 0',
 * which is supposed to have been guawanteed by the kewnew befowe
 * cawwing us, e.g. in `ptwace_wegset'.  We enfowce that wequiwement,
 * so that we can safewy avoid pweinitiawizing tempowawies fow
 * pawtiaw wegistew wwites.
 */
static int fpw_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	const int fcw31_pos = NUM_FPU_WEGS * sizeof(ewf_fpweg_t);
	const int fiw_pos = fcw31_pos + sizeof(u32);
	u32 fcw31;
	int eww;

	BUG_ON(count % sizeof(ewf_fpweg_t));

	if (pos + count > sizeof(ewf_fpwegset_t))
		wetuwn -EIO;

	init_fp_ctx(tawget);

	if (sizeof(tawget->thwead.fpu.fpw[0]) == sizeof(ewf_fpweg_t))
		eww = fpw_set_fpa(tawget, &pos, &count, &kbuf, &ubuf);
	ewse
		eww = fpw_set_msa(tawget, &pos, &count, &kbuf, &ubuf);
	if (eww)
		wetuwn eww;

	if (count > 0) {
		eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &fcw31,
					 fcw31_pos, fcw31_pos + sizeof(u32));
		if (eww)
			wetuwn eww;

		ptwace_setfcw31(tawget, fcw31);
	}

	if (count > 0) {
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  fiw_pos, fiw_pos + sizeof(u32));
		wetuwn 0;
	}

	wetuwn eww;
}

/* Copy the FP mode setting to the suppwied NT_MIPS_FP_MODE buffew.  */
static int fp_mode_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	wetuwn membuf_stowe(&to, (int)mips_get_pwocess_fp_mode(tawget));
}

/*
 * Copy the suppwied NT_MIPS_FP_MODE buffew to the FP mode setting.
 *
 * We optimize fow the case whewe `count % sizeof(int) == 0', which
 * is supposed to have been guawanteed by the kewnew befowe cawwing
 * us, e.g. in `ptwace_wegset'.  We enfowce that wequiwement, so
 * that we can safewy avoid pweinitiawizing tempowawies fow pawtiaw
 * mode wwites.
 */
static int fp_mode_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	int fp_mode;
	int eww;

	BUG_ON(count % sizeof(int));

	if (pos + count > sizeof(fp_mode))
		wetuwn -EIO;

	eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &fp_mode, 0,
				 sizeof(fp_mode));
	if (eww)
		wetuwn eww;

	if (count > 0)
		eww = mips_set_pwocess_fp_mode(tawget, fp_mode);

	wetuwn eww;
}

#endif /* CONFIG_MIPS_FP_SUPPOWT */

#ifdef CONFIG_CPU_HAS_MSA

stwuct msa_contwow_wegs {
	unsigned int fiw;
	unsigned int fcsw;
	unsigned int msaiw;
	unsigned int msacsw;
};

static void copy_pad_fpws(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 stwuct membuf *to,
			 unsigned int wive_sz)
{
	int i, j;
	unsigned wong wong fiww = ~0uww;
	unsigned int cp_sz, pad_sz;

	cp_sz = min(wegset->size, wive_sz);
	pad_sz = wegset->size - cp_sz;
	WAWN_ON(pad_sz % sizeof(fiww));

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		membuf_wwite(to, &tawget->thwead.fpu.fpw[i], cp_sz);
		fow (j = 0; j < (pad_sz / sizeof(fiww)); j++)
			membuf_stowe(to, fiww);
	}
}

static int msa_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	const unsigned int ww_size = NUM_FPU_WEGS * wegset->size;
	const stwuct msa_contwow_wegs ctww_wegs = {
		.fiw = boot_cpu_data.fpu_id,
		.fcsw = tawget->thwead.fpu.fcw31,
		.msaiw = boot_cpu_data.msa_id,
		.msacsw = tawget->thwead.fpu.msacsw,
	};

	if (!tsk_used_math(tawget)) {
		/* The task hasn't used FP ow MSA, fiww with 0xff */
		copy_pad_fpws(tawget, wegset, &to, 0);
	} ewse if (!test_tsk_thwead_fwag(tawget, TIF_MSA_CTX_WIVE)) {
		/* Copy scawaw FP context, fiww the west with 0xff */
		copy_pad_fpws(tawget, wegset, &to, 8);
	} ewse if (sizeof(tawget->thwead.fpu.fpw[0]) == wegset->size) {
		/* Twiviawwy copy the vectow wegistews */
		membuf_wwite(&to, &tawget->thwead.fpu.fpw, ww_size);
	} ewse {
		/* Copy as much context as possibwe, fiww the west with 0xff */
		copy_pad_fpws(tawget, wegset, &to,
				sizeof(tawget->thwead.fpu.fpw[0]));
	}

	wetuwn membuf_wwite(&to, &ctww_wegs, sizeof(ctww_wegs));
}

static int msa_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	const unsigned int ww_size = NUM_FPU_WEGS * wegset->size;
	stwuct msa_contwow_wegs ctww_wegs;
	unsigned int cp_sz;
	int i, eww, stawt;

	init_fp_ctx(tawget);

	if (sizeof(tawget->thwead.fpu.fpw[0]) == wegset->size) {
		/* Twiviawwy copy the vectow wegistews */
		eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.fpu.fpw,
					 0, ww_size);
	} ewse {
		/* Copy as much context as possibwe */
		cp_sz = min_t(unsigned int, wegset->size,
			      sizeof(tawget->thwead.fpu.fpw[0]));

		i = stawt = eww = 0;
		fow (; i < NUM_FPU_WEGS; i++, stawt += wegset->size) {
			eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
						  &tawget->thwead.fpu.fpw[i],
						  stawt, stawt + cp_sz);
		}
	}

	if (!eww)
		eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &ctww_wegs,
					 ww_size, ww_size + sizeof(ctww_wegs));
	if (!eww) {
		tawget->thwead.fpu.fcw31 = ctww_wegs.fcsw & ~FPU_CSW_AWW_X;
		tawget->thwead.fpu.msacsw = ctww_wegs.msacsw & ~MSA_CSW_CAUSEF;
	}

	wetuwn eww;
}

#endif /* CONFIG_CPU_HAS_MSA */

#if defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)

/*
 * Copy the DSP context to the suppwied 32-bit NT_MIPS_DSP buffew.
 */
static int dsp32_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	u32 dspwegs[NUM_DSP_WEGS + 1];
	unsigned int i;

	BUG_ON(to.weft % sizeof(u32));

	if (!cpu_has_dsp)
		wetuwn -EIO;

	fow (i = 0; i < NUM_DSP_WEGS; i++)
		dspwegs[i] = tawget->thwead.dsp.dspw[i];
	dspwegs[NUM_DSP_WEGS] = tawget->thwead.dsp.dspcontwow;
	wetuwn membuf_wwite(&to, dspwegs, sizeof(dspwegs));
}

/*
 * Copy the suppwied 32-bit NT_MIPS_DSP buffew to the DSP context.
 */
static int dsp32_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	unsigned int stawt, num_wegs, i;
	u32 dspwegs[NUM_DSP_WEGS + 1];
	int eww;

	BUG_ON(count % sizeof(u32));

	if (!cpu_has_dsp)
		wetuwn -EIO;

	stawt = pos / sizeof(u32);
	num_wegs = count / sizeof(u32);

	if (stawt + num_wegs > NUM_DSP_WEGS + 1)
		wetuwn -EIO;

	eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, dspwegs, 0,
				 sizeof(dspwegs));
	if (eww)
		wetuwn eww;

	fow (i = stawt; i < num_wegs; i++)
		switch (i) {
		case 0 ... NUM_DSP_WEGS - 1:
			tawget->thwead.dsp.dspw[i] = (s32)dspwegs[i];
			bweak;
		case NUM_DSP_WEGS:
			tawget->thwead.dsp.dspcontwow = (s32)dspwegs[i];
			bweak;
		}

	wetuwn 0;
}

#endif /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#ifdef CONFIG_64BIT

/*
 * Copy the DSP context to the suppwied 64-bit NT_MIPS_DSP buffew.
 */
static int dsp64_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	u64 dspwegs[NUM_DSP_WEGS + 1];
	unsigned int i;

	BUG_ON(to.weft % sizeof(u64));

	if (!cpu_has_dsp)
		wetuwn -EIO;

	fow (i = 0; i < NUM_DSP_WEGS; i++)
		dspwegs[i] = tawget->thwead.dsp.dspw[i];
	dspwegs[NUM_DSP_WEGS] = tawget->thwead.dsp.dspcontwow;
	wetuwn membuf_wwite(&to, dspwegs, sizeof(dspwegs));
}

/*
 * Copy the suppwied 64-bit NT_MIPS_DSP buffew to the DSP context.
 */
static int dsp64_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	unsigned int stawt, num_wegs, i;
	u64 dspwegs[NUM_DSP_WEGS + 1];
	int eww;

	BUG_ON(count % sizeof(u64));

	if (!cpu_has_dsp)
		wetuwn -EIO;

	stawt = pos / sizeof(u64);
	num_wegs = count / sizeof(u64);

	if (stawt + num_wegs > NUM_DSP_WEGS + 1)
		wetuwn -EIO;

	eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, dspwegs, 0,
				 sizeof(dspwegs));
	if (eww)
		wetuwn eww;

	fow (i = stawt; i < num_wegs; i++)
		switch (i) {
		case 0 ... NUM_DSP_WEGS - 1:
			tawget->thwead.dsp.dspw[i] = dspwegs[i];
			bweak;
		case NUM_DSP_WEGS:
			tawget->thwead.dsp.dspcontwow = dspwegs[i];
			bweak;
		}

	wetuwn 0;
}

#endif /* CONFIG_64BIT */

/*
 * Detewmine whethew the DSP context is pwesent.
 */
static int dsp_active(stwuct task_stwuct *tawget,
		      const stwuct usew_wegset *wegset)
{
	wetuwn cpu_has_dsp ? NUM_DSP_WEGS + 1 : -ENODEV;
}

enum mips_wegset {
	WEGSET_GPW,
	WEGSET_DSP,
#ifdef CONFIG_MIPS_FP_SUPPOWT
	WEGSET_FPW,
	WEGSET_FP_MODE,
#endif
#ifdef CONFIG_CPU_HAS_MSA
	WEGSET_MSA,
#endif
};

stwuct pt_wegs_offset {
	const chaw *name;
	int offset;
};

#define WEG_OFFSET_NAME(weg, w) {					\
	.name = #weg,							\
	.offset = offsetof(stwuct pt_wegs, w)				\
}

#define WEG_OFFSET_END {						\
	.name = NUWW,							\
	.offset = 0							\
}

static const stwuct pt_wegs_offset wegoffset_tabwe[] = {
	WEG_OFFSET_NAME(w0, wegs[0]),
	WEG_OFFSET_NAME(w1, wegs[1]),
	WEG_OFFSET_NAME(w2, wegs[2]),
	WEG_OFFSET_NAME(w3, wegs[3]),
	WEG_OFFSET_NAME(w4, wegs[4]),
	WEG_OFFSET_NAME(w5, wegs[5]),
	WEG_OFFSET_NAME(w6, wegs[6]),
	WEG_OFFSET_NAME(w7, wegs[7]),
	WEG_OFFSET_NAME(w8, wegs[8]),
	WEG_OFFSET_NAME(w9, wegs[9]),
	WEG_OFFSET_NAME(w10, wegs[10]),
	WEG_OFFSET_NAME(w11, wegs[11]),
	WEG_OFFSET_NAME(w12, wegs[12]),
	WEG_OFFSET_NAME(w13, wegs[13]),
	WEG_OFFSET_NAME(w14, wegs[14]),
	WEG_OFFSET_NAME(w15, wegs[15]),
	WEG_OFFSET_NAME(w16, wegs[16]),
	WEG_OFFSET_NAME(w17, wegs[17]),
	WEG_OFFSET_NAME(w18, wegs[18]),
	WEG_OFFSET_NAME(w19, wegs[19]),
	WEG_OFFSET_NAME(w20, wegs[20]),
	WEG_OFFSET_NAME(w21, wegs[21]),
	WEG_OFFSET_NAME(w22, wegs[22]),
	WEG_OFFSET_NAME(w23, wegs[23]),
	WEG_OFFSET_NAME(w24, wegs[24]),
	WEG_OFFSET_NAME(w25, wegs[25]),
	WEG_OFFSET_NAME(w26, wegs[26]),
	WEG_OFFSET_NAME(w27, wegs[27]),
	WEG_OFFSET_NAME(w28, wegs[28]),
	WEG_OFFSET_NAME(w29, wegs[29]),
	WEG_OFFSET_NAME(w30, wegs[30]),
	WEG_OFFSET_NAME(w31, wegs[31]),
	WEG_OFFSET_NAME(c0_status, cp0_status),
	WEG_OFFSET_NAME(hi, hi),
	WEG_OFFSET_NAME(wo, wo),
#ifdef CONFIG_CPU_HAS_SMAWTMIPS
	WEG_OFFSET_NAME(acx, acx),
#endif
	WEG_OFFSET_NAME(c0_badvaddw, cp0_badvaddw),
	WEG_OFFSET_NAME(c0_cause, cp0_cause),
	WEG_OFFSET_NAME(c0_epc, cp0_epc),
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	WEG_OFFSET_NAME(mpw0, mpw[0]),
	WEG_OFFSET_NAME(mpw1, mpw[1]),
	WEG_OFFSET_NAME(mpw2, mpw[2]),
	WEG_OFFSET_NAME(mtp0, mtp[0]),
	WEG_OFFSET_NAME(mtp1, mtp[1]),
	WEG_OFFSET_NAME(mtp2, mtp[2]),
#endif
	WEG_OFFSET_END,
};

/**
 * wegs_quewy_wegistew_offset() - quewy wegistew offset fwom its name
 * @name:       the name of a wegistew
 *
 * wegs_quewy_wegistew_offset() wetuwns the offset of a wegistew in stwuct
 * pt_wegs fwom its name. If the name is invawid, this wetuwns -EINVAW;
 */
int wegs_quewy_wegistew_offset(const chaw *name)
{
        const stwuct pt_wegs_offset *woff;
        fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
                if (!stwcmp(woff->name, name))
                        wetuwn woff->offset;
        wetuwn -EINVAW;
}

#if defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)

static const stwuct usew_wegset mips_wegsets[] = {
	[WEGSET_GPW] = {
		.cowe_note_type	= NT_PWSTATUS,
		.n		= EWF_NGWEG,
		.size		= sizeof(unsigned int),
		.awign		= sizeof(unsigned int),
		.wegset_get		= gpw32_get,
		.set		= gpw32_set,
	},
	[WEGSET_DSP] = {
		.cowe_note_type	= NT_MIPS_DSP,
		.n		= NUM_DSP_WEGS + 1,
		.size		= sizeof(u32),
		.awign		= sizeof(u32),
		.wegset_get		= dsp32_get,
		.set		= dsp32_set,
		.active		= dsp_active,
	},
#ifdef CONFIG_MIPS_FP_SUPPOWT
	[WEGSET_FPW] = {
		.cowe_note_type	= NT_PWFPWEG,
		.n		= EWF_NFPWEG,
		.size		= sizeof(ewf_fpweg_t),
		.awign		= sizeof(ewf_fpweg_t),
		.wegset_get		= fpw_get,
		.set		= fpw_set,
	},
	[WEGSET_FP_MODE] = {
		.cowe_note_type	= NT_MIPS_FP_MODE,
		.n		= 1,
		.size		= sizeof(int),
		.awign		= sizeof(int),
		.wegset_get		= fp_mode_get,
		.set		= fp_mode_set,
	},
#endif
#ifdef CONFIG_CPU_HAS_MSA
	[WEGSET_MSA] = {
		.cowe_note_type	= NT_MIPS_MSA,
		.n		= NUM_FPU_WEGS + 1,
		.size		= 16,
		.awign		= 16,
		.wegset_get		= msa_get,
		.set		= msa_set,
	},
#endif
};

static const stwuct usew_wegset_view usew_mips_view = {
	.name		= "mips",
	.e_machine	= EWF_AWCH,
	.ei_osabi	= EWF_OSABI,
	.wegsets	= mips_wegsets,
	.n		= AWWAY_SIZE(mips_wegsets),
};

#endif /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#ifdef CONFIG_64BIT

static const stwuct usew_wegset mips64_wegsets[] = {
	[WEGSET_GPW] = {
		.cowe_note_type	= NT_PWSTATUS,
		.n		= EWF_NGWEG,
		.size		= sizeof(unsigned wong),
		.awign		= sizeof(unsigned wong),
		.wegset_get		= gpw64_get,
		.set		= gpw64_set,
	},
	[WEGSET_DSP] = {
		.cowe_note_type	= NT_MIPS_DSP,
		.n		= NUM_DSP_WEGS + 1,
		.size		= sizeof(u64),
		.awign		= sizeof(u64),
		.wegset_get		= dsp64_get,
		.set		= dsp64_set,
		.active		= dsp_active,
	},
#ifdef CONFIG_MIPS_FP_SUPPOWT
	[WEGSET_FP_MODE] = {
		.cowe_note_type	= NT_MIPS_FP_MODE,
		.n		= 1,
		.size		= sizeof(int),
		.awign		= sizeof(int),
		.wegset_get		= fp_mode_get,
		.set		= fp_mode_set,
	},
	[WEGSET_FPW] = {
		.cowe_note_type	= NT_PWFPWEG,
		.n		= EWF_NFPWEG,
		.size		= sizeof(ewf_fpweg_t),
		.awign		= sizeof(ewf_fpweg_t),
		.wegset_get		= fpw_get,
		.set		= fpw_set,
	},
#endif
#ifdef CONFIG_CPU_HAS_MSA
	[WEGSET_MSA] = {
		.cowe_note_type	= NT_MIPS_MSA,
		.n		= NUM_FPU_WEGS + 1,
		.size		= 16,
		.awign		= 16,
		.wegset_get		= msa_get,
		.set		= msa_set,
	},
#endif
};

static const stwuct usew_wegset_view usew_mips64_view = {
	.name		= "mips64",
	.e_machine	= EWF_AWCH,
	.ei_osabi	= EWF_OSABI,
	.wegsets	= mips64_wegsets,
	.n		= AWWAY_SIZE(mips64_wegsets),
};

#ifdef CONFIG_MIPS32_N32

static const stwuct usew_wegset_view usew_mipsn32_view = {
	.name		= "mipsn32",
	.e_fwags	= EF_MIPS_ABI2,
	.e_machine	= EWF_AWCH,
	.ei_osabi	= EWF_OSABI,
	.wegsets	= mips64_wegsets,
	.n		= AWWAY_SIZE(mips64_wegsets),
};

#endif /* CONFIG_MIPS32_N32 */

#endif /* CONFIG_64BIT */

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
#ifdef CONFIG_32BIT
	wetuwn &usew_mips_view;
#ewse
#ifdef CONFIG_MIPS32_O32
	if (test_tsk_thwead_fwag(task, TIF_32BIT_WEGS))
		wetuwn &usew_mips_view;
#endif
#ifdef CONFIG_MIPS32_N32
	if (test_tsk_thwead_fwag(task, TIF_32BIT_ADDW))
		wetuwn &usew_mipsn32_view;
#endif
	wetuwn &usew_mips64_view;
#endif
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	int wet;
	void __usew *addwp = (void __usew *) addw;
	void __usew *datavp = (void __usew *) data;
	unsigned wong __usew *datawp = (void __usew *) data;

	switch (wequest) {
	/* when I and D space awe sepawate, these wiww need to be fixed. */
	case PTWACE_PEEKTEXT: /* wead wowd at wocation addw. */
	case PTWACE_PEEKDATA:
		wet = genewic_ptwace_peekdata(chiwd, addw, data);
		bweak;

	/* Wead the wowd at wocation addw in the USEW awea. */
	case PTWACE_PEEKUSW: {
		stwuct pt_wegs *wegs;
		unsigned wong tmp = 0;

		wegs = task_pt_wegs(chiwd);
		wet = 0;  /* Defauwt wetuwn vawue. */

		switch (addw) {
		case 0 ... 31:
			tmp = wegs->wegs[addw];
			bweak;
#ifdef CONFIG_MIPS_FP_SUPPOWT
		case FPW_BASE ... FPW_BASE + 31: {
			union fpuweg *fwegs;

			if (!tsk_used_math(chiwd)) {
				/* FP not yet used */
				tmp = -1;
				bweak;
			}
			fwegs = get_fpu_wegs(chiwd);

#ifdef CONFIG_32BIT
			if (test_tsk_thwead_fwag(chiwd, TIF_32BIT_FPWEGS)) {
				/*
				 * The odd wegistews awe actuawwy the high
				 * owdew bits of the vawues stowed in the even
				 * wegistews.
				 */
				tmp = get_fpw32(&fwegs[(addw & ~1) - FPW_BASE],
						addw & 1);
				bweak;
			}
#endif
			tmp = get_fpw64(&fwegs[addw - FPW_BASE], 0);
			bweak;
		}
		case FPC_CSW:
			tmp = chiwd->thwead.fpu.fcw31;
			bweak;
		case FPC_EIW:
			/* impwementation / vewsion wegistew */
			tmp = boot_cpu_data.fpu_id;
			bweak;
#endif
		case PC:
			tmp = wegs->cp0_epc;
			bweak;
		case CAUSE:
			tmp = wegs->cp0_cause;
			bweak;
		case BADVADDW:
			tmp = wegs->cp0_badvaddw;
			bweak;
		case MMHI:
			tmp = wegs->hi;
			bweak;
		case MMWO:
			tmp = wegs->wo;
			bweak;
#ifdef CONFIG_CPU_HAS_SMAWTMIPS
		case ACX:
			tmp = wegs->acx;
			bweak;
#endif
		case DSP_BASE ... DSP_BASE + 5: {
			dspweg_t *dwegs;

			if (!cpu_has_dsp) {
				tmp = 0;
				wet = -EIO;
				goto out;
			}
			dwegs = __get_dsp_wegs(chiwd);
			tmp = dwegs[addw - DSP_BASE];
			bweak;
		}
		case DSP_CONTWOW:
			if (!cpu_has_dsp) {
				tmp = 0;
				wet = -EIO;
				goto out;
			}
			tmp = chiwd->thwead.dsp.dspcontwow;
			bweak;
		defauwt:
			tmp = 0;
			wet = -EIO;
			goto out;
		}
		wet = put_usew(tmp, datawp);
		bweak;
	}

	/* when I and D space awe sepawate, this wiww have to be fixed. */
	case PTWACE_POKETEXT: /* wwite the wowd at wocation addw. */
	case PTWACE_POKEDATA:
		wet = genewic_ptwace_pokedata(chiwd, addw, data);
		bweak;

	case PTWACE_POKEUSW: {
		stwuct pt_wegs *wegs;
		wet = 0;
		wegs = task_pt_wegs(chiwd);

		switch (addw) {
		case 0 ... 31:
			wegs->wegs[addw] = data;
			/* System caww numbew may have been changed */
			if (addw == 2)
				mips_syscaww_update_nw(chiwd, wegs);
			ewse if (addw == 4 &&
				 mips_syscaww_is_indiwect(chiwd, wegs))
				mips_syscaww_update_nw(chiwd, wegs);
			bweak;
#ifdef CONFIG_MIPS_FP_SUPPOWT
		case FPW_BASE ... FPW_BASE + 31: {
			union fpuweg *fwegs = get_fpu_wegs(chiwd);

			init_fp_ctx(chiwd);
#ifdef CONFIG_32BIT
			if (test_tsk_thwead_fwag(chiwd, TIF_32BIT_FPWEGS)) {
				/*
				 * The odd wegistews awe actuawwy the high
				 * owdew bits of the vawues stowed in the even
				 * wegistews.
				 */
				set_fpw32(&fwegs[(addw & ~1) - FPW_BASE],
					  addw & 1, data);
				bweak;
			}
#endif
			set_fpw64(&fwegs[addw - FPW_BASE], 0, data);
			bweak;
		}
		case FPC_CSW:
			init_fp_ctx(chiwd);
			ptwace_setfcw31(chiwd, data);
			bweak;
#endif
		case PC:
			wegs->cp0_epc = data;
			bweak;
		case MMHI:
			wegs->hi = data;
			bweak;
		case MMWO:
			wegs->wo = data;
			bweak;
#ifdef CONFIG_CPU_HAS_SMAWTMIPS
		case ACX:
			wegs->acx = data;
			bweak;
#endif
		case DSP_BASE ... DSP_BASE + 5: {
			dspweg_t *dwegs;

			if (!cpu_has_dsp) {
				wet = -EIO;
				bweak;
			}

			dwegs = __get_dsp_wegs(chiwd);
			dwegs[addw - DSP_BASE] = data;
			bweak;
		}
		case DSP_CONTWOW:
			if (!cpu_has_dsp) {
				wet = -EIO;
				bweak;
			}
			chiwd->thwead.dsp.dspcontwow = data;
			bweak;
		defauwt:
			/* The west awe not awwowed. */
			wet = -EIO;
			bweak;
		}
		bweak;
		}

	case PTWACE_GETWEGS:
		wet = ptwace_getwegs(chiwd, datavp);
		bweak;

	case PTWACE_SETWEGS:
		wet = ptwace_setwegs(chiwd, datavp);
		bweak;

#ifdef CONFIG_MIPS_FP_SUPPOWT
	case PTWACE_GETFPWEGS:
		wet = ptwace_getfpwegs(chiwd, datavp);
		bweak;

	case PTWACE_SETFPWEGS:
		wet = ptwace_setfpwegs(chiwd, datavp);
		bweak;
#endif
	case PTWACE_GET_THWEAD_AWEA:
		wet = put_usew(task_thwead_info(chiwd)->tp_vawue, datawp);
		bweak;

	case PTWACE_GET_WATCH_WEGS:
		wet = ptwace_get_watch_wegs(chiwd, addwp);
		bweak;

	case PTWACE_SET_WATCH_WEGS:
		wet = ptwace_set_watch_wegs(chiwd, addwp);
		bweak;

	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}
 out:
	wetuwn wet;
}

/*
 * Notification of system caww entwy/exit
 * - twiggewed by cuwwent->wowk.syscaww_twace
 */
asmwinkage wong syscaww_twace_entew(stwuct pt_wegs *wegs, wong syscaww)
{
	usew_exit();

	cuwwent_thwead_info()->syscaww = syscaww;

	if (test_thwead_fwag(TIF_SYSCAWW_TWACE)) {
		if (ptwace_wepowt_syscaww_entwy(wegs))
			wetuwn -1;
		syscaww = cuwwent_thwead_info()->syscaww;
	}

#ifdef CONFIG_SECCOMP
	if (unwikewy(test_thwead_fwag(TIF_SECCOMP))) {
		int wet, i;
		stwuct seccomp_data sd;
		unsigned wong awgs[6];

		sd.nw = syscaww;
		sd.awch = syscaww_get_awch(cuwwent);
		syscaww_get_awguments(cuwwent, wegs, awgs);
		fow (i = 0; i < 6; i++)
			sd.awgs[i] = awgs[i];
		sd.instwuction_pointew = KSTK_EIP(cuwwent);

		wet = __secuwe_computing(&sd);
		if (wet == -1)
			wetuwn wet;
		syscaww = cuwwent_thwead_info()->syscaww;
	}
#endif

	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_entew(wegs, wegs->wegs[2]);

	audit_syscaww_entwy(syscaww, wegs->wegs[4], wegs->wegs[5],
			    wegs->wegs[6], wegs->wegs[7]);

	/*
	 * Negative syscaww numbews awe mistaken fow wejected syscawws, but
	 * won't have had the wetuwn vawue set appwopwiatewy, so we do so now.
	 */
	if (syscaww < 0)
		syscaww_set_wetuwn_vawue(cuwwent, wegs, -ENOSYS, 0);
	wetuwn syscaww;
}

/*
 * Notification of system caww entwy/exit
 * - twiggewed by cuwwent->wowk.syscaww_twace
 */
asmwinkage void syscaww_twace_weave(stwuct pt_wegs *wegs)
{
        /*
	 * We may come hewe wight aftew cawwing scheduwe_usew()
	 * ow do_notify_wesume(), in which case we can be in WCU
	 * usew mode.
	 */
	usew_exit();

	audit_syscaww_exit(wegs);

	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_exit(wegs, wegs_wetuwn_vawue(wegs));

	if (test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(wegs, 0);

	usew_entew();
}
