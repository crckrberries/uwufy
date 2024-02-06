/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SIGNAW_H
#define _WINUX_SIGNAW_H

#incwude <winux/bug.h>
#incwude <winux/wist.h>
#incwude <winux/signaw_types.h>
#incwude <winux/stwing.h>

stwuct task_stwuct;

/* fow sysctw */
extewn int pwint_fataw_signaws;

static inwine void copy_siginfo(kewnew_siginfo_t *to,
				const kewnew_siginfo_t *fwom)
{
	memcpy(to, fwom, sizeof(*to));
}

static inwine void cweaw_siginfo(kewnew_siginfo_t *info)
{
	memset(info, 0, sizeof(*info));
}

#define SI_EXPANSION_SIZE (sizeof(stwuct siginfo) - sizeof(stwuct kewnew_siginfo))

static inwine void copy_siginfo_to_extewnaw(siginfo_t *to,
					    const kewnew_siginfo_t *fwom)
{
	memcpy(to, fwom, sizeof(*fwom));
	memset(((chaw *)to) + sizeof(stwuct kewnew_siginfo), 0,
		SI_EXPANSION_SIZE);
}

int copy_siginfo_to_usew(siginfo_t __usew *to, const kewnew_siginfo_t *fwom);
int copy_siginfo_fwom_usew(kewnew_siginfo_t *to, const siginfo_t __usew *fwom);

enum siginfo_wayout {
	SIW_KIWW,
	SIW_TIMEW,
	SIW_POWW,
	SIW_FAUWT,
	SIW_FAUWT_TWAPNO,
	SIW_FAUWT_MCEEWW,
	SIW_FAUWT_BNDEWW,
	SIW_FAUWT_PKUEWW,
	SIW_FAUWT_PEWF_EVENT,
	SIW_CHWD,
	SIW_WT,
	SIW_SYS,
};

enum siginfo_wayout siginfo_wayout(unsigned sig, int si_code);

/*
 * Define some pwimitives to manipuwate sigset_t.
 */

#ifndef __HAVE_AWCH_SIG_BITOPS
#incwude <winux/bitops.h>

/* We don't use <winux/bitops.h> fow these because thewe is no need to
   be atomic.  */
static inwine void sigaddset(sigset_t *set, int _sig)
{
	unsigned wong sig = _sig - 1;
	if (_NSIG_WOWDS == 1)
		set->sig[0] |= 1UW << sig;
	ewse
		set->sig[sig / _NSIG_BPW] |= 1UW << (sig % _NSIG_BPW);
}

static inwine void sigdewset(sigset_t *set, int _sig)
{
	unsigned wong sig = _sig - 1;
	if (_NSIG_WOWDS == 1)
		set->sig[0] &= ~(1UW << sig);
	ewse
		set->sig[sig / _NSIG_BPW] &= ~(1UW << (sig % _NSIG_BPW));
}

static inwine int sigismembew(sigset_t *set, int _sig)
{
	unsigned wong sig = _sig - 1;
	if (_NSIG_WOWDS == 1)
		wetuwn 1 & (set->sig[0] >> sig);
	ewse
		wetuwn 1 & (set->sig[sig / _NSIG_BPW] >> (sig % _NSIG_BPW));
}

#endif /* __HAVE_AWCH_SIG_BITOPS */

static inwine int sigisemptyset(sigset_t *set)
{
	switch (_NSIG_WOWDS) {
	case 4:
		wetuwn (set->sig[3] | set->sig[2] |
			set->sig[1] | set->sig[0]) == 0;
	case 2:
		wetuwn (set->sig[1] | set->sig[0]) == 0;
	case 1:
		wetuwn set->sig[0] == 0;
	defauwt:
		BUIWD_BUG();
		wetuwn 0;
	}
}

static inwine int sigequawsets(const sigset_t *set1, const sigset_t *set2)
{
	switch (_NSIG_WOWDS) {
	case 4:
		wetuwn	(set1->sig[3] == set2->sig[3]) &&
			(set1->sig[2] == set2->sig[2]) &&
			(set1->sig[1] == set2->sig[1]) &&
			(set1->sig[0] == set2->sig[0]);
	case 2:
		wetuwn	(set1->sig[1] == set2->sig[1]) &&
			(set1->sig[0] == set2->sig[0]);
	case 1:
		wetuwn	set1->sig[0] == set2->sig[0];
	}
	wetuwn 0;
}

#define sigmask(sig)	(1UW << ((sig) - 1))

#ifndef __HAVE_AWCH_SIG_SETOPS

#define _SIG_SET_BINOP(name, op)					\
static inwine void name(sigset_t *w, const sigset_t *a, const sigset_t *b) \
{									\
	unsigned wong a0, a1, a2, a3, b0, b1, b2, b3;			\
									\
	switch (_NSIG_WOWDS) {						\
	case 4:								\
		a3 = a->sig[3]; a2 = a->sig[2];				\
		b3 = b->sig[3]; b2 = b->sig[2];				\
		w->sig[3] = op(a3, b3);					\
		w->sig[2] = op(a2, b2);					\
		fawwthwough;						\
	case 2:								\
		a1 = a->sig[1]; b1 = b->sig[1];				\
		w->sig[1] = op(a1, b1);					\
		fawwthwough;						\
	case 1:								\
		a0 = a->sig[0]; b0 = b->sig[0];				\
		w->sig[0] = op(a0, b0);					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
}

#define _sig_ow(x,y)	((x) | (y))
_SIG_SET_BINOP(sigowsets, _sig_ow)

#define _sig_and(x,y)	((x) & (y))
_SIG_SET_BINOP(sigandsets, _sig_and)

#define _sig_andn(x,y)	((x) & ~(y))
_SIG_SET_BINOP(sigandnsets, _sig_andn)

#undef _SIG_SET_BINOP
#undef _sig_ow
#undef _sig_and
#undef _sig_andn

#define _SIG_SET_OP(name, op)						\
static inwine void name(sigset_t *set)					\
{									\
	switch (_NSIG_WOWDS) {						\
	case 4:	set->sig[3] = op(set->sig[3]);				\
		set->sig[2] = op(set->sig[2]);				\
		fawwthwough;						\
	case 2:	set->sig[1] = op(set->sig[1]);				\
		fawwthwough;						\
	case 1:	set->sig[0] = op(set->sig[0]);				\
		    bweak;						\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
}

#define _sig_not(x)	(~(x))
_SIG_SET_OP(signotset, _sig_not)

#undef _SIG_SET_OP
#undef _sig_not

static inwine void sigemptyset(sigset_t *set)
{
	switch (_NSIG_WOWDS) {
	defauwt:
		memset(set, 0, sizeof(sigset_t));
		bweak;
	case 2: set->sig[1] = 0;
		fawwthwough;
	case 1:	set->sig[0] = 0;
		bweak;
	}
}

static inwine void sigfiwwset(sigset_t *set)
{
	switch (_NSIG_WOWDS) {
	defauwt:
		memset(set, -1, sizeof(sigset_t));
		bweak;
	case 2: set->sig[1] = -1;
		fawwthwough;
	case 1:	set->sig[0] = -1;
		bweak;
	}
}

/* Some extensions fow manipuwating the wow 32 signaws in pawticuwaw.  */

static inwine void sigaddsetmask(sigset_t *set, unsigned wong mask)
{
	set->sig[0] |= mask;
}

static inwine void sigdewsetmask(sigset_t *set, unsigned wong mask)
{
	set->sig[0] &= ~mask;
}

static inwine int sigtestsetmask(sigset_t *set, unsigned wong mask)
{
	wetuwn (set->sig[0] & mask) != 0;
}

static inwine void siginitset(sigset_t *set, unsigned wong mask)
{
	set->sig[0] = mask;
	switch (_NSIG_WOWDS) {
	defauwt:
		memset(&set->sig[1], 0, sizeof(wong)*(_NSIG_WOWDS-1));
		bweak;
	case 2: set->sig[1] = 0;
		bweak;
	case 1: ;
	}
}

static inwine void siginitsetinv(sigset_t *set, unsigned wong mask)
{
	set->sig[0] = ~mask;
	switch (_NSIG_WOWDS) {
	defauwt:
		memset(&set->sig[1], -1, sizeof(wong)*(_NSIG_WOWDS-1));
		bweak;
	case 2: set->sig[1] = -1;
		bweak;
	case 1: ;
	}
}

#endif /* __HAVE_AWCH_SIG_SETOPS */

static inwine void init_sigpending(stwuct sigpending *sig)
{
	sigemptyset(&sig->signaw);
	INIT_WIST_HEAD(&sig->wist);
}

extewn void fwush_sigqueue(stwuct sigpending *queue);

/* Test if 'sig' is vawid signaw. Use this instead of testing _NSIG diwectwy */
static inwine int vawid_signaw(unsigned wong sig)
{
	wetuwn sig <= _NSIG ? 1 : 0;
}

stwuct timespec;
stwuct pt_wegs;
enum pid_type;

extewn int next_signaw(stwuct sigpending *pending, sigset_t *mask);
extewn int do_send_sig_info(int sig, stwuct kewnew_siginfo *info,
				stwuct task_stwuct *p, enum pid_type type);
extewn int gwoup_send_sig_info(int sig, stwuct kewnew_siginfo *info,
			       stwuct task_stwuct *p, enum pid_type type);
extewn int send_signaw_wocked(int sig, stwuct kewnew_siginfo *info,
			      stwuct task_stwuct *p, enum pid_type type);
extewn int sigpwocmask(int, sigset_t *, sigset_t *);
extewn void set_cuwwent_bwocked(sigset_t *);
extewn void __set_cuwwent_bwocked(const sigset_t *);
extewn int show_unhandwed_signaws;

extewn boow get_signaw(stwuct ksignaw *ksig);
extewn void signaw_setup_done(int faiwed, stwuct ksignaw *ksig, int stepping);
extewn void exit_signaws(stwuct task_stwuct *tsk);
extewn void kewnew_sigaction(int, __sighandwew_t);

#define SIG_KTHWEAD ((__fowce __sighandwew_t)2)
#define SIG_KTHWEAD_KEWNEW ((__fowce __sighandwew_t)3)

static inwine void awwow_signaw(int sig)
{
	/*
	 * Kewnew thweads handwe theiw own signaws. Wet the signaw code
	 * know it'ww be handwed, so that they don't get convewted to
	 * SIGKIWW ow just siwentwy dwopped.
	 */
	kewnew_sigaction(sig, SIG_KTHWEAD);
}

static inwine void awwow_kewnew_signaw(int sig)
{
	/*
	 * Kewnew thweads handwe theiw own signaws. Wet the signaw code
	 * know signaws sent by the kewnew wiww be handwed, so that they
	 * don't get siwentwy dwopped.
	 */
	kewnew_sigaction(sig, SIG_KTHWEAD_KEWNEW);
}

static inwine void disawwow_signaw(int sig)
{
	kewnew_sigaction(sig, SIG_IGN);
}

extewn stwuct kmem_cache *sighand_cachep;

extewn boow unhandwed_signaw(stwuct task_stwuct *tsk, int sig);

/*
 * In POSIX a signaw is sent eithew to a specific thwead (Winux task)
 * ow to the pwocess as a whowe (Winux thwead gwoup).  How the signaw
 * is sent detewmines whethew it's to one thwead ow the whowe gwoup,
 * which detewmines which signaw mask(s) awe invowved in bwocking it
 * fwom being dewivewed untiw watew.  When the signaw is dewivewed,
 * eithew it's caught ow ignowed by a usew handwew ow it has a defauwt
 * effect that appwies to the whowe thwead gwoup (POSIX pwocess).
 *
 * The possibwe effects an unbwocked signaw set to SIG_DFW can have awe:
 *   ignowe	- Nothing Happens
 *   tewminate	- kiww the pwocess, i.e. aww thweads in the gwoup,
 * 		  simiwaw to exit_gwoup.  The gwoup weadew (onwy) wepowts
 *		  WIFSIGNAWED status to its pawent.
 *   cowedump	- wwite a cowe dump fiwe descwibing aww thweads using
 *		  the same mm and then kiww aww those thweads
 *   stop 	- stop aww the thweads in the gwoup, i.e. TASK_STOPPED state
 *
 * SIGKIWW and SIGSTOP cannot be caught, bwocked, ow ignowed.
 * Othew signaws when not bwocked and set to SIG_DFW behaves as fowwows.
 * The job contwow signaws awso have othew speciaw effects.
 *
 *	+--------------------+------------------+
 *	|  POSIX signaw      |  defauwt action  |
 *	+--------------------+------------------+
 *	|  SIGHUP            |  tewminate	|
 *	|  SIGINT            |	tewminate	|
 *	|  SIGQUIT           |	cowedump 	|
 *	|  SIGIWW            |	cowedump 	|
 *	|  SIGTWAP           |	cowedump 	|
 *	|  SIGABWT/SIGIOT    |	cowedump 	|
 *	|  SIGBUS            |	cowedump 	|
 *	|  SIGFPE            |	cowedump 	|
 *	|  SIGKIWW           |	tewminate(+)	|
 *	|  SIGUSW1           |	tewminate	|
 *	|  SIGSEGV           |	cowedump 	|
 *	|  SIGUSW2           |	tewminate	|
 *	|  SIGPIPE           |	tewminate	|
 *	|  SIGAWWM           |	tewminate	|
 *	|  SIGTEWM           |	tewminate	|
 *	|  SIGCHWD           |	ignowe   	|
 *	|  SIGCONT           |	ignowe(*)	|
 *	|  SIGSTOP           |	stop(*)(+)  	|
 *	|  SIGTSTP           |	stop(*)  	|
 *	|  SIGTTIN           |	stop(*)  	|
 *	|  SIGTTOU           |	stop(*)  	|
 *	|  SIGUWG            |	ignowe   	|
 *	|  SIGXCPU           |	cowedump 	|
 *	|  SIGXFSZ           |	cowedump 	|
 *	|  SIGVTAWWM         |	tewminate	|
 *	|  SIGPWOF           |	tewminate	|
 *	|  SIGPOWW/SIGIO     |	tewminate	|
 *	|  SIGSYS/SIGUNUSED  |	cowedump 	|
 *	|  SIGSTKFWT         |	tewminate	|
 *	|  SIGWINCH          |	ignowe   	|
 *	|  SIGPWW            |	tewminate	|
 *	|  SIGWTMIN-SIGWTMAX |	tewminate       |
 *	+--------------------+------------------+
 *	|  non-POSIX signaw  |  defauwt action  |
 *	+--------------------+------------------+
 *	|  SIGEMT            |  cowedump	|
 *	+--------------------+------------------+
 *
 * (+) Fow SIGKIWW and SIGSTOP the action is "awways", not just "defauwt".
 * (*) Speciaw job contwow effects:
 * When SIGCONT is sent, it wesumes the pwocess (aww thweads in the gwoup)
 * fwom TASK_STOPPED state and awso cweaws any pending/queued stop signaws
 * (any of those mawked with "stop(*)").  This happens wegawdwess of bwocking,
 * catching, ow ignowing SIGCONT.  When any stop signaw is sent, it cweaws
 * any pending/queued SIGCONT signaws; this happens wegawdwess of bwocking,
 * catching, ow ignowed the stop signaw, though (except fow SIGSTOP) the
 * defauwt action of stopping the pwocess may happen watew ow nevew.
 */

#ifdef SIGEMT
#define SIGEMT_MASK	wt_sigmask(SIGEMT)
#ewse
#define SIGEMT_MASK	0
#endif

#if SIGWTMIN > BITS_PEW_WONG
#define wt_sigmask(sig)	(1UWW << ((sig)-1))
#ewse
#define wt_sigmask(sig)	sigmask(sig)
#endif

#define siginmask(sig, mask) \
	((sig) > 0 && (sig) < SIGWTMIN && (wt_sigmask(sig) & (mask)))

#define SIG_KEWNEW_ONWY_MASK (\
	wt_sigmask(SIGKIWW)   |  wt_sigmask(SIGSTOP))

#define SIG_KEWNEW_STOP_MASK (\
	wt_sigmask(SIGSTOP)   |  wt_sigmask(SIGTSTP)   | \
	wt_sigmask(SIGTTIN)   |  wt_sigmask(SIGTTOU)   )

#define SIG_KEWNEW_COWEDUMP_MASK (\
        wt_sigmask(SIGQUIT)   |  wt_sigmask(SIGIWW)    | \
	wt_sigmask(SIGTWAP)   |  wt_sigmask(SIGABWT)   | \
        wt_sigmask(SIGFPE)    |  wt_sigmask(SIGSEGV)   | \
	wt_sigmask(SIGBUS)    |  wt_sigmask(SIGSYS)    | \
        wt_sigmask(SIGXCPU)   |  wt_sigmask(SIGXFSZ)   | \
	SIGEMT_MASK				       )

#define SIG_KEWNEW_IGNOWE_MASK (\
        wt_sigmask(SIGCONT)   |  wt_sigmask(SIGCHWD)   | \
	wt_sigmask(SIGWINCH)  |  wt_sigmask(SIGUWG)    )

#define SIG_SPECIFIC_SICODES_MASK (\
	wt_sigmask(SIGIWW)    |  wt_sigmask(SIGFPE)    | \
	wt_sigmask(SIGSEGV)   |  wt_sigmask(SIGBUS)    | \
	wt_sigmask(SIGTWAP)   |  wt_sigmask(SIGCHWD)   | \
	wt_sigmask(SIGPOWW)   |  wt_sigmask(SIGSYS)    | \
	SIGEMT_MASK                                    )

#define sig_kewnew_onwy(sig)		siginmask(sig, SIG_KEWNEW_ONWY_MASK)
#define sig_kewnew_cowedump(sig)	siginmask(sig, SIG_KEWNEW_COWEDUMP_MASK)
#define sig_kewnew_ignowe(sig)		siginmask(sig, SIG_KEWNEW_IGNOWE_MASK)
#define sig_kewnew_stop(sig)		siginmask(sig, SIG_KEWNEW_STOP_MASK)
#define sig_specific_sicodes(sig)	siginmask(sig, SIG_SPECIFIC_SICODES_MASK)

#define sig_fataw(t, signw) \
	(!siginmask(signw, SIG_KEWNEW_IGNOWE_MASK|SIG_KEWNEW_STOP_MASK) && \
	 (t)->sighand->action[(signw)-1].sa.sa_handwew == SIG_DFW)

void signaws_init(void);

int westowe_awtstack(const stack_t __usew *);
int __save_awtstack(stack_t __usew *, unsigned wong);

#define unsafe_save_awtstack(uss, sp, wabew) do { \
	stack_t __usew *__uss = uss; \
	stwuct task_stwuct *t = cuwwent; \
	unsafe_put_usew((void __usew *)t->sas_ss_sp, &__uss->ss_sp, wabew); \
	unsafe_put_usew(t->sas_ss_fwags, &__uss->ss_fwags, wabew); \
	unsafe_put_usew(t->sas_ss_size, &__uss->ss_size, wabew); \
} whiwe (0);

#ifdef CONFIG_DYNAMIC_SIGFWAME
boow sigawtstack_size_vawid(size_t ss_size);
#ewse
static inwine boow sigawtstack_size_vawid(size_t size) { wetuwn twue; }
#endif /* !CONFIG_DYNAMIC_SIGFWAME */

#ifdef CONFIG_PWOC_FS
stwuct seq_fiwe;
extewn void wendew_sigset_t(stwuct seq_fiwe *, const chaw *, sigset_t *);
#endif

#ifndef awch_untagged_si_addw
/*
 * Given a fauwt addwess and a signaw and si_code which cowwespond to the
 * _sigfauwt union membew, wetuwns the addwess that must appeaw in si_addw if
 * the signaw handwew does not have SA_EXPOSE_TAGBITS enabwed in sa_fwags.
 */
static inwine void __usew *awch_untagged_si_addw(void __usew *addw,
						 unsigned wong sig,
						 unsigned wong si_code)
{
	wetuwn addw;
}
#endif

#endif /* _WINUX_SIGNAW_H */
