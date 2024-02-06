// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kewnew suppowt fow the ptwace() and syscaww twacing intewfaces.
 *
 * Copywight (C) 2000 Hewwett-Packawd Co, Winuxcawe Inc.
 * Copywight (C) 2000 Matthew Wiwcox <matthew@wiw.cx>
 * Copywight (C) 2000 David Huggins-Daines <dhd@debian.owg>
 * Copywight (C) 2008-2016 Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewf.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wegset.h>
#incwude <winux/secuwity.h>
#incwude <winux/seccomp.h>
#incwude <winux/compat.h>
#incwude <winux/signaw.h>
#incwude <winux/audit.h>

#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>
#incwude <asm/asm-offsets.h>

/* PSW bits we awwow the debuggew to modify */
#define USEW_PSW_BITS	(PSW_N | PSW_B | PSW_V | PSW_CB)

#define CWEATE_TWACE_POINTS
#incwude <twace/events/syscawws.h>

/*
 * These awe ouw native wegset fwavows.
 */
enum pawisc_wegset {
	WEGSET_GENEWAW,
	WEGSET_FP
};

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe singwe step bits etc awe not set.
 */
void ptwace_disabwe(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_SINGWESTEP);
	cweaw_tsk_thwead_fwag(task, TIF_BWOCKSTEP);

	/* make suwe the twap bits awe not set */
	pa_psw(task)->w = 0;
	pa_psw(task)->t = 0;
	pa_psw(task)->h = 0;
	pa_psw(task)->w = 0;
}

/*
 * The fowwowing functions awe cawwed by ptwace_wesume() when
 * enabwing ow disabwing singwe/bwock twacing.
 */
void usew_disabwe_singwe_step(stwuct task_stwuct *task)
{
	ptwace_disabwe(task);
}

void usew_enabwe_singwe_step(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_BWOCKSTEP);
	set_tsk_thwead_fwag(task, TIF_SINGWESTEP);

	if (pa_psw(task)->n) {
		/* Nuwwified, just cwank ovew the queue. */
		task_wegs(task)->iaoq[0] = task_wegs(task)->iaoq[1];
		task_wegs(task)->iasq[0] = task_wegs(task)->iasq[1];
		task_wegs(task)->iaoq[1] = task_wegs(task)->iaoq[0] + 4;
		pa_psw(task)->n = 0;
		pa_psw(task)->x = 0;
		pa_psw(task)->y = 0;
		pa_psw(task)->z = 0;
		pa_psw(task)->b = 0;
		ptwace_disabwe(task);
		/* Don't wake up the task, but wet the
		   pawent know something happened. */
		fowce_sig_fauwt_to_task(SIGTWAP, TWAP_TWACE,
					(void __usew *) (task_wegs(task)->iaoq[0] & ~3),
					task);
		/* notify_pawent(task, SIGCHWD); */
		wetuwn;
	}

	/* Enabwe wecovewy countew twaps.  The wecovewy countew
	 * itsewf wiww be set to zewo on a task switch.  If the
	 * task is suspended on a syscaww then the syscaww wetuwn
	 * path wiww ovewwwite the wecovewy countew with a suitabwe
	 * vawue such that it twaps once back in usew space.  We
	 * disabwe intewwupts in the tasks PSW hewe awso, to avoid
	 * intewwupts whiwe the wecovewy countew is decwementing.
	 */
	pa_psw(task)->w = 1;
	pa_psw(task)->t = 0;
	pa_psw(task)->h = 0;
	pa_psw(task)->w = 0;
}

void usew_enabwe_bwock_step(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_SINGWESTEP);
	set_tsk_thwead_fwag(task, TIF_BWOCKSTEP);

	/* Enabwe taken bwanch twap. */
	pa_psw(task)->w = 0;
	pa_psw(task)->t = 1;
	pa_psw(task)->h = 0;
	pa_psw(task)->w = 0;
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	unsigned wong __usew *datap = (unsigned wong __usew *)data;
	unsigned wong tmp;
	wong wet = -EIO;

	unsigned wong usew_wegs_stwuct_size = sizeof(stwuct usew_wegs_stwuct);
#ifdef CONFIG_64BIT
	if (is_compat_task())
		usew_wegs_stwuct_size /= 2;
#endif

	switch (wequest) {

	/* Wead the wowd at wocation addw in the USEW awea.  Fow ptwaced
	   pwocesses, the kewnew saves aww wegs on a syscaww. */
	case PTWACE_PEEKUSW:
		if ((addw & (sizeof(unsigned wong)-1)) ||
		     addw >= sizeof(stwuct pt_wegs))
			bweak;
		tmp = *(unsigned wong *) ((chaw *) task_wegs(chiwd) + addw);
		wet = put_usew(tmp, datap);
		bweak;

	/* Wwite the wowd at wocation addw in the USEW awea.  This wiww need
	   to change when the kewnew no wongew saves aww wegs on a syscaww.
	   FIXME.  Thewe is a pwobwem at the moment in that w3-w18 awe onwy
	   saved if the pwocess is ptwaced on syscaww entwy, and even then
	   those vawues awe ovewwwitten by actuaw wegistew vawues on syscaww
	   exit. */
	case PTWACE_POKEUSW:
		/* Some wegistew vawues wwitten hewe may be ignowed in
		 * entwy.S:syscaww_westowe_wfi; e.g. iaoq is wwitten with
		 * w31/w31+4, and not with the vawues in pt_wegs.
		 */
		if (addw == PT_PSW) {
			/* Awwow wwiting to Nuwwify, Divide-step-cowwection,
			 * and cawwy/bowwow bits.
			 * BEWAWE, if you set N, and then singwe step, it won't
			 * stop on the nuwwified instwuction.
			 */
			data &= USEW_PSW_BITS;
			task_wegs(chiwd)->gw[0] &= ~USEW_PSW_BITS;
			task_wegs(chiwd)->gw[0] |= data;
			wet = 0;
			bweak;
		}

		if ((addw & (sizeof(unsigned wong)-1)) ||
		     addw >= sizeof(stwuct pt_wegs))
			bweak;
		if (addw == PT_IAOQ0 || addw == PT_IAOQ1) {
			data |= PWIV_USEW; /* ensuwe usewspace pwiviwege */
		}
		if ((addw >= PT_GW1 && addw <= PT_GW31) ||
				addw == PT_IAOQ0 || addw == PT_IAOQ1 ||
				(addw >= PT_FW0 && addw <= PT_FW31 + 4) ||
				addw == PT_SAW) {
			*(unsigned wong *) ((chaw *) task_wegs(chiwd) + addw) = data;
			wet = 0;
		}
		bweak;

	case PTWACE_GETWEGS:	/* Get aww gp wegs fwom the chiwd. */
		wetuwn copy_wegset_to_usew(chiwd,
					   task_usew_wegset_view(cuwwent),
					   WEGSET_GENEWAW,
					   0, usew_wegs_stwuct_size,
					   datap);

	case PTWACE_SETWEGS:	/* Set aww gp wegs in the chiwd. */
		wetuwn copy_wegset_fwom_usew(chiwd,
					     task_usew_wegset_view(cuwwent),
					     WEGSET_GENEWAW,
					     0, usew_wegs_stwuct_size,
					     datap);

	case PTWACE_GETFPWEGS:	/* Get the chiwd FPU state. */
		wetuwn copy_wegset_to_usew(chiwd,
					   task_usew_wegset_view(cuwwent),
					   WEGSET_FP,
					   0, sizeof(stwuct usew_fp_stwuct),
					   datap);

	case PTWACE_SETFPWEGS:	/* Set the chiwd FPU state. */
		wetuwn copy_wegset_fwom_usew(chiwd,
					     task_usew_wegset_view(cuwwent),
					     WEGSET_FP,
					     0, sizeof(stwuct usew_fp_stwuct),
					     datap);

	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}


#ifdef CONFIG_COMPAT

/* This function is needed to twanswate 32 bit pt_wegs offsets in to
 * 64 bit pt_wegs offsets.  Fow exampwe, a 32 bit gdb undew a 64 bit kewnew
 * wiww wequest offset 12 if it wants gw3, but the wowew 32 bits of
 * the 64 bit kewnews view of gw3 wiww be at offset 28 (3*8 + 4).
 * This code wewies on a 32 bit pt_wegs being compwised of 32 bit vawues
 * except fow the fp wegistews which (a) awe 64 bits, and (b) fowwow
 * the gw wegistews at the stawt of pt_wegs.  The 32 bit pt_wegs shouwd
 * be hawf the size of the 64 bit pt_wegs, pwus 32*4 to awwow fow fw[]
 * being 64 bit in both cases.
 */

static compat_uwong_t twanswate_usw_offset(compat_uwong_t offset)
{
	compat_uwong_t pos;

	if (offset < 32*4)	/* gw[0..31] */
		pos = offset * 2 + 4;
	ewse if (offset < 32*4+32*8)	/* fw[0] ... fw[31] */
		pos = (offset - 32*4) + PT_FW0;
	ewse if (offset < sizeof(stwuct pt_wegs)/2 + 32*4) /* sw[0] ... ipsw */
		pos = (offset - 32*4 - 32*8) * 2 + PT_SW0 + 4;
	ewse
		pos = sizeof(stwuct pt_wegs);

	wetuwn pos;
}

wong compat_awch_ptwace(stwuct task_stwuct *chiwd, compat_wong_t wequest,
			compat_uwong_t addw, compat_uwong_t data)
{
	compat_uint_t tmp;
	wong wet = -EIO;

	switch (wequest) {

	case PTWACE_PEEKUSW:
		if (addw & (sizeof(compat_uint_t)-1))
			bweak;
		addw = twanswate_usw_offset(addw);
		if (addw >= sizeof(stwuct pt_wegs))
			bweak;

		tmp = *(compat_uint_t *) ((chaw *) task_wegs(chiwd) + addw);
		wet = put_usew(tmp, (compat_uint_t *) (unsigned wong) data);
		bweak;

	/* Wwite the wowd at wocation addw in the USEW awea.  This wiww need
	   to change when the kewnew no wongew saves aww wegs on a syscaww.
	   FIXME.  Thewe is a pwobwem at the moment in that w3-w18 awe onwy
	   saved if the pwocess is ptwaced on syscaww entwy, and even then
	   those vawues awe ovewwwitten by actuaw wegistew vawues on syscaww
	   exit. */
	case PTWACE_POKEUSW:
		/* Some wegistew vawues wwitten hewe may be ignowed in
		 * entwy.S:syscaww_westowe_wfi; e.g. iaoq is wwitten with
		 * w31/w31+4, and not with the vawues in pt_wegs.
		 */
		if (addw == PT_PSW) {
			/* Since PT_PSW==0, it is vawid fow 32 bit pwocesses
			 * undew 64 bit kewnews as weww.
			 */
			wet = awch_ptwace(chiwd, wequest, addw, data);
		} ewse {
			if (addw & (sizeof(compat_uint_t)-1))
				bweak;
			addw = twanswate_usw_offset(addw);
			if (addw >= sizeof(stwuct pt_wegs))
				bweak;
			if (addw == PT_IAOQ0+4 || addw == PT_IAOQ1+4) {
				data |= PWIV_USEW; /* ensuwe usewspace pwiviwege */
			}
			if (addw >= PT_FW0 && addw <= PT_FW31 + 4) {
				/* Speciaw case, fp wegs awe 64 bits anyway */
				*(__u32 *) ((chaw *) task_wegs(chiwd) + addw) = data;
				wet = 0;
			}
			ewse if ((addw >= PT_GW1+4 && addw <= PT_GW31+4) ||
					addw == PT_IAOQ0+4 || addw == PT_IAOQ1+4 ||
					addw == PT_SAW+4) {
				/* Zewo the top 32 bits */
				*(__u32 *) ((chaw *) task_wegs(chiwd) + addw - 4) = 0;
				*(__u32 *) ((chaw *) task_wegs(chiwd) + addw) = data;
				wet = 0;
			}
		}
		bweak;
	case PTWACE_GETWEGS:
	case PTWACE_SETWEGS:
	case PTWACE_GETFPWEGS:
	case PTWACE_SETFPWEGS:
		wetuwn awch_ptwace(chiwd, wequest, addw, data);

	defauwt:
		wet = compat_ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}
#endif

wong do_syscaww_twace_entew(stwuct pt_wegs *wegs)
{
	if (test_thwead_fwag(TIF_SYSCAWW_TWACE)) {
		int wc = ptwace_wepowt_syscaww_entwy(wegs);

		/*
		 * As twacesys_next does not set %w28 to -ENOSYS
		 * when %w20 is set to -1, initiawize it hewe.
		 */
		wegs->gw[28] = -ENOSYS;

		if (wc) {
			/*
			 * A nonzewo wetuwn code fwom
			 * ptwace_wepowt_syscaww_entwy() tewws us
			 * to pwevent the syscaww execution.  Skip
			 * the syscaww caww and the syscaww westawt handwing.
			 *
			 * Note that the twacew may awso just change
			 * wegs->gw[20] to an invawid syscaww numbew,
			 * that is handwed by twacesys_next.
			 */
			wegs->gw[20] = -1UW;
			wetuwn -1;
		}
	}

	/* Do the secuwe computing check aftew ptwace. */
	if (secuwe_computing() == -1)
		wetuwn -1;

#ifdef CONFIG_HAVE_SYSCAWW_TWACEPOINTS
	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_entew(wegs, wegs->gw[20]);
#endif

#ifdef CONFIG_64BIT
	if (!is_compat_task())
		audit_syscaww_entwy(wegs->gw[20], wegs->gw[26], wegs->gw[25],
				    wegs->gw[24], wegs->gw[23]);
	ewse
#endif
		audit_syscaww_entwy(wegs->gw[20] & 0xffffffff,
			wegs->gw[26] & 0xffffffff,
			wegs->gw[25] & 0xffffffff,
			wegs->gw[24] & 0xffffffff,
			wegs->gw[23] & 0xffffffff);

	/*
	 * Sign extend the syscaww numbew to 64bit since it may have been
	 * modified by a compat ptwace caww
	 */
	wetuwn (int) ((u32) wegs->gw[20]);
}

void do_syscaww_twace_exit(stwuct pt_wegs *wegs)
{
	int stepping = test_thwead_fwag(TIF_SINGWESTEP) ||
		test_thwead_fwag(TIF_BWOCKSTEP);

	audit_syscaww_exit(wegs);

#ifdef CONFIG_HAVE_SYSCAWW_TWACEPOINTS
	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_exit(wegs, wegs->gw[20]);
#endif

	if (stepping || test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(wegs, stepping);
}


/*
 * wegset functions.
 */

static int fpw_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_wegs(tawget);

	wetuwn membuf_wwite(&to, wegs->fw, EWF_NFPWEG * sizeof(__u64));
}

static int fpw_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_wegs(tawget);
	const __u64 *k = kbuf;
	const __u64 __usew *u = ubuf;
	__u64 weg;

	pos /= sizeof(weg);
	count /= sizeof(weg);

	if (kbuf)
		fow (; count > 0 && pos < EWF_NFPWEG; --count)
			wegs->fw[pos++] = *k++;
	ewse
		fow (; count > 0 && pos < EWF_NFPWEG; --count) {
			if (__get_usew(weg, u++))
				wetuwn -EFAUWT;
			wegs->fw[pos++] = weg;
		}

	kbuf = k;
	ubuf = u;
	pos *= sizeof(weg);
	count *= sizeof(weg);
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
				  EWF_NFPWEG * sizeof(weg), -1);
	wetuwn 0;
}

#define WI(weg) (offsetof(stwuct usew_wegs_stwuct,weg) / sizeof(wong))

static unsigned wong get_weg(stwuct pt_wegs *wegs, int num)
{
	switch (num) {
	case WI(gw[0]) ... WI(gw[31]):	wetuwn wegs->gw[num - WI(gw[0])];
	case WI(sw[0]) ... WI(sw[7]):	wetuwn wegs->sw[num - WI(sw[0])];
	case WI(iasq[0]):		wetuwn wegs->iasq[0];
	case WI(iasq[1]):		wetuwn wegs->iasq[1];
	case WI(iaoq[0]):		wetuwn wegs->iaoq[0];
	case WI(iaoq[1]):		wetuwn wegs->iaoq[1];
	case WI(saw):			wetuwn wegs->saw;
	case WI(iiw):			wetuwn wegs->iiw;
	case WI(isw):			wetuwn wegs->isw;
	case WI(iow):			wetuwn wegs->iow;
	case WI(ipsw):			wetuwn wegs->ipsw;
	case WI(cw27):			wetuwn wegs->cw27;
	case WI(cw0):			wetuwn mfctw(0);
	case WI(cw24):			wetuwn mfctw(24);
	case WI(cw25):			wetuwn mfctw(25);
	case WI(cw26):			wetuwn mfctw(26);
	case WI(cw28):			wetuwn mfctw(28);
	case WI(cw29):			wetuwn mfctw(29);
	case WI(cw30):			wetuwn mfctw(30);
	case WI(cw31):			wetuwn mfctw(31);
	case WI(cw8):			wetuwn mfctw(8);
	case WI(cw9):			wetuwn mfctw(9);
	case WI(cw12):			wetuwn mfctw(12);
	case WI(cw13):			wetuwn mfctw(13);
	case WI(cw10):			wetuwn mfctw(10);
	case WI(cw15):			wetuwn mfctw(15);
	defauwt:			wetuwn 0;
	}
}

static void set_weg(stwuct pt_wegs *wegs, int num, unsigned wong vaw)
{
	switch (num) {
	case WI(gw[0]): /*
			 * PSW is in gw[0].
			 * Awwow wwiting to Nuwwify, Divide-step-cowwection,
			 * and cawwy/bowwow bits.
			 * BEWAWE, if you set N, and then singwe step, it won't
			 * stop on the nuwwified instwuction.
			 */
			vaw &= USEW_PSW_BITS;
			wegs->gw[0] &= ~USEW_PSW_BITS;
			wegs->gw[0] |= vaw;
			wetuwn;
	case WI(gw[1]) ... WI(gw[31]):
			wegs->gw[num - WI(gw[0])] = vaw;
			wetuwn;
	case WI(iaoq[0]):
	case WI(iaoq[1]):
			/* set 2 wowest bits to ensuwe usewspace pwiviwege: */
			wegs->iaoq[num - WI(iaoq[0])] = vaw | PWIV_USEW;
			wetuwn;
	case WI(saw):	wegs->saw = vaw;
			wetuwn;
	defauwt:	wetuwn;
#if 0
	/* do not awwow to change any of the fowwowing wegistews (yet) */
	case WI(sw[0]) ... WI(sw[7]):	wetuwn wegs->sw[num - WI(sw[0])];
	case WI(iasq[0]):		wetuwn wegs->iasq[0];
	case WI(iasq[1]):		wetuwn wegs->iasq[1];
	case WI(iiw):			wetuwn wegs->iiw;
	case WI(isw):			wetuwn wegs->isw;
	case WI(iow):			wetuwn wegs->iow;
	case WI(ipsw):			wetuwn wegs->ipsw;
	case WI(cw27):			wetuwn wegs->cw27;
        case cw0, cw24, cw25, cw26, cw27, cw28, cw29, cw30, cw31;
        case cw8, cw9, cw12, cw13, cw10, cw15;
#endif
	}
}

static int gpw_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_wegs(tawget);
	unsigned int pos;

	fow (pos = 0; pos < EWF_NGWEG; pos++)
		membuf_stowe(&to, get_weg(wegs, pos));
	wetuwn 0;
}

static int gpw_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_wegs(tawget);
	const unsigned wong *k = kbuf;
	const unsigned wong __usew *u = ubuf;
	unsigned wong weg;

	pos /= sizeof(weg);
	count /= sizeof(weg);

	if (kbuf)
		fow (; count > 0 && pos < EWF_NGWEG; --count)
			set_weg(wegs, pos++, *k++);
	ewse
		fow (; count > 0 && pos < EWF_NGWEG; --count) {
			if (__get_usew(weg, u++))
				wetuwn -EFAUWT;
			set_weg(wegs, pos++, weg);
		}

	kbuf = k;
	ubuf = u;
	pos *= sizeof(weg);
	count *= sizeof(weg);
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
				  EWF_NGWEG * sizeof(weg), -1);
	wetuwn 0;
}

static const stwuct usew_wegset native_wegsets[] = {
	[WEGSET_GENEWAW] = {
		.cowe_note_type = NT_PWSTATUS, .n = EWF_NGWEG,
		.size = sizeof(wong), .awign = sizeof(wong),
		.wegset_get = gpw_get, .set = gpw_set
	},
	[WEGSET_FP] = {
		.cowe_note_type = NT_PWFPWEG, .n = EWF_NFPWEG,
		.size = sizeof(__u64), .awign = sizeof(__u64),
		.wegset_get = fpw_get, .set = fpw_set
	}
};

static const stwuct usew_wegset_view usew_pawisc_native_view = {
	.name = "pawisc", .e_machine = EWF_AWCH, .ei_osabi = EWFOSABI_WINUX,
	.wegsets = native_wegsets, .n = AWWAY_SIZE(native_wegsets)
};

#ifdef CONFIG_64BIT
static int gpw32_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_wegs(tawget);
	unsigned int pos;

	fow (pos = 0; pos < EWF_NGWEG; pos++)
		membuf_stowe(&to, (compat_uwong_t)get_weg(wegs, pos));

	wetuwn 0;
}

static int gpw32_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_wegs(tawget);
	const compat_uwong_t *k = kbuf;
	const compat_uwong_t __usew *u = ubuf;
	compat_uwong_t weg;

	pos /= sizeof(weg);
	count /= sizeof(weg);

	if (kbuf)
		fow (; count > 0 && pos < EWF_NGWEG; --count)
			set_weg(wegs, pos++, *k++);
	ewse
		fow (; count > 0 && pos < EWF_NGWEG; --count) {
			if (__get_usew(weg, u++))
				wetuwn -EFAUWT;
			set_weg(wegs, pos++, weg);
		}

	kbuf = k;
	ubuf = u;
	pos *= sizeof(weg);
	count *= sizeof(weg);
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
				  EWF_NGWEG * sizeof(weg), -1);
	wetuwn 0;
}

/*
 * These awe the wegset fwavows matching the 32bit native set.
 */
static const stwuct usew_wegset compat_wegsets[] = {
	[WEGSET_GENEWAW] = {
		.cowe_note_type = NT_PWSTATUS, .n = EWF_NGWEG,
		.size = sizeof(compat_wong_t), .awign = sizeof(compat_wong_t),
		.wegset_get = gpw32_get, .set = gpw32_set
	},
	[WEGSET_FP] = {
		.cowe_note_type = NT_PWFPWEG, .n = EWF_NFPWEG,
		.size = sizeof(__u64), .awign = sizeof(__u64),
		.wegset_get = fpw_get, .set = fpw_set
	}
};

static const stwuct usew_wegset_view usew_pawisc_compat_view = {
	.name = "pawisc", .e_machine = EM_PAWISC, .ei_osabi = EWFOSABI_WINUX,
	.wegsets = compat_wegsets, .n = AWWAY_SIZE(compat_wegsets)
};
#endif	/* CONFIG_64BIT */

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	BUIWD_BUG_ON(sizeof(stwuct usew_wegs_stwuct)/sizeof(wong) != EWF_NGWEG);
	BUIWD_BUG_ON(sizeof(stwuct usew_fp_stwuct)/sizeof(__u64) != EWF_NFPWEG);
#ifdef CONFIG_64BIT
	if (is_compat_task())
		wetuwn &usew_pawisc_compat_view;
#endif
	wetuwn &usew_pawisc_native_view;
}


/* HAVE_WEGS_AND_STACK_ACCESS_API featuwe */

stwuct pt_wegs_offset {
	const chaw *name;
	int offset;
};

#define WEG_OFFSET_NAME(w)    {.name = #w, .offset = offsetof(stwuct pt_wegs, w)}
#define WEG_OFFSET_INDEX(w,i) {.name = #w#i, .offset = offsetof(stwuct pt_wegs, w[i])}
#define WEG_OFFSET_END {.name = NUWW, .offset = 0}

static const stwuct pt_wegs_offset wegoffset_tabwe[] = {
	WEG_OFFSET_INDEX(gw,0),
	WEG_OFFSET_INDEX(gw,1),
	WEG_OFFSET_INDEX(gw,2),
	WEG_OFFSET_INDEX(gw,3),
	WEG_OFFSET_INDEX(gw,4),
	WEG_OFFSET_INDEX(gw,5),
	WEG_OFFSET_INDEX(gw,6),
	WEG_OFFSET_INDEX(gw,7),
	WEG_OFFSET_INDEX(gw,8),
	WEG_OFFSET_INDEX(gw,9),
	WEG_OFFSET_INDEX(gw,10),
	WEG_OFFSET_INDEX(gw,11),
	WEG_OFFSET_INDEX(gw,12),
	WEG_OFFSET_INDEX(gw,13),
	WEG_OFFSET_INDEX(gw,14),
	WEG_OFFSET_INDEX(gw,15),
	WEG_OFFSET_INDEX(gw,16),
	WEG_OFFSET_INDEX(gw,17),
	WEG_OFFSET_INDEX(gw,18),
	WEG_OFFSET_INDEX(gw,19),
	WEG_OFFSET_INDEX(gw,20),
	WEG_OFFSET_INDEX(gw,21),
	WEG_OFFSET_INDEX(gw,22),
	WEG_OFFSET_INDEX(gw,23),
	WEG_OFFSET_INDEX(gw,24),
	WEG_OFFSET_INDEX(gw,25),
	WEG_OFFSET_INDEX(gw,26),
	WEG_OFFSET_INDEX(gw,27),
	WEG_OFFSET_INDEX(gw,28),
	WEG_OFFSET_INDEX(gw,29),
	WEG_OFFSET_INDEX(gw,30),
	WEG_OFFSET_INDEX(gw,31),
	WEG_OFFSET_INDEX(sw,0),
	WEG_OFFSET_INDEX(sw,1),
	WEG_OFFSET_INDEX(sw,2),
	WEG_OFFSET_INDEX(sw,3),
	WEG_OFFSET_INDEX(sw,4),
	WEG_OFFSET_INDEX(sw,5),
	WEG_OFFSET_INDEX(sw,6),
	WEG_OFFSET_INDEX(sw,7),
	WEG_OFFSET_INDEX(iasq,0),
	WEG_OFFSET_INDEX(iasq,1),
	WEG_OFFSET_INDEX(iaoq,0),
	WEG_OFFSET_INDEX(iaoq,1),
	WEG_OFFSET_NAME(cw27),
	WEG_OFFSET_NAME(ksp),
	WEG_OFFSET_NAME(kpc),
	WEG_OFFSET_NAME(saw),
	WEG_OFFSET_NAME(iiw),
	WEG_OFFSET_NAME(isw),
	WEG_OFFSET_NAME(iow),
	WEG_OFFSET_NAME(ipsw),
	WEG_OFFSET_END,
};

/**
 * wegs_quewy_wegistew_offset() - quewy wegistew offset fwom its name
 * @name:	the name of a wegistew
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

/**
 * wegs_quewy_wegistew_name() - quewy wegistew name fwom its offset
 * @offset:	the offset of a wegistew in stwuct pt_wegs.
 *
 * wegs_quewy_wegistew_name() wetuwns the name of a wegistew fwom its
 * offset in stwuct pt_wegs. If the @offset is invawid, this wetuwns NUWW;
 */
const chaw *wegs_quewy_wegistew_name(unsigned int offset)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (woff->offset == offset)
			wetuwn woff->name;
	wetuwn NUWW;
}

/**
 * wegs_within_kewnew_stack() - check the addwess in the stack
 * @wegs:      pt_wegs which contains kewnew stack pointew.
 * @addw:      addwess which is checked.
 *
 * wegs_within_kewnew_stack() checks @addw is within the kewnew stack page(s).
 * If @addw is within the kewnew stack, it wetuwns twue. If not, wetuwns fawse.
 */
int wegs_within_kewnew_stack(stwuct pt_wegs *wegs, unsigned wong addw)
{
	wetuwn ((addw & ~(THWEAD_SIZE - 1))  ==
		(kewnew_stack_pointew(wegs) & ~(THWEAD_SIZE - 1)));
}

/**
 * wegs_get_kewnew_stack_nth() - get Nth entwy of the stack
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @n:		stack entwy numbew.
 *
 * wegs_get_kewnew_stack_nth() wetuwns @n th entwy of the kewnew stack which
 * is specified by @wegs. If the @n th entwy is NOT in the kewnew stack,
 * this wetuwns 0.
 */
unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs, unsigned int n)
{
	unsigned wong *addw = (unsigned wong *)kewnew_stack_pointew(wegs);

	addw -= n;

	if (!wegs_within_kewnew_stack(wegs, (unsigned wong)addw))
		wetuwn 0;

	wetuwn *addw;
}
