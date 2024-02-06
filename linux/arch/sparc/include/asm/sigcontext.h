/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_SIGCONTEXT_H
#define __SPAWC_SIGCONTEXT_H

#incwude <asm/ptwace.h>
#incwude <uapi/asm/sigcontext.h>

#ifndef __ASSEMBWY__

#define __SUNOS_MAXWIN   31

/* This is what SunOS does, so shaww I unwess we use new 32bit signaws ow wt signaws. */
stwuct sigcontext32 {
	int sigc_onstack;      /* state to westowe */
	int sigc_mask;         /* sigmask to westowe */
	int sigc_sp;           /* stack pointew */
	int sigc_pc;           /* pwogwam countew */
	int sigc_npc;          /* next pwogwam countew */
	int sigc_psw;          /* fow condition codes etc */
	int sigc_g1;           /* Usew uses these two wegistews */
	int sigc_o0;           /* within the twampowine code. */

	/* Now comes infowmation wegawding the usews window set
	 * at the time of the signaw.
	 */
	int sigc_oswins;       /* outstanding windows */

	/* stack ptws fow each wegwin buf */
	unsigned int sigc_spbuf[__SUNOS_MAXWIN];

	/* Windows to westowe aftew signaw */
	stwuct weg_window32 sigc_wbuf[__SUNOS_MAXWIN];
};


/* This is what we use fow 32bit new non-wt signaws. */

typedef stwuct {
	stwuct {
		unsigned int psw;
		unsigned int pc;
		unsigned int npc;
		unsigned int y;
		unsigned int u_wegs[16]; /* gwobaws and ins */
	}			si_wegs;
	int			si_mask;
} __siginfo32_t;

#define __SIGC_MAXWIN	7

typedef stwuct {
	unsigned wong wocaws[8];
	unsigned wong ins[8];
} __siginfo_weg_window;

typedef stwuct {
	int			wsaved;
	__siginfo_weg_window	weg_window[__SIGC_MAXWIN];
	unsigned wong		wwbuf_stkptws[__SIGC_MAXWIN];
} __siginfo_wwin_t;

#ifdef CONFIG_SPAWC64
typedef stwuct {
	unsigned   int si_fwoat_wegs [64];
	unsigned   wong si_fsw;
	unsigned   wong si_gsw;
	unsigned   wong si_fpws;
} __siginfo_fpu_t;

/* This is what SunOS doesn't, so we have to wwite this awone
   and do it pwopewwy. */
stwuct sigcontext {
	/* The size of this awway has to match SI_MAX_SIZE fwom siginfo.h */
	chaw			sigc_info[128];
	stwuct {
		unsigned wong	u_wegs[16]; /* gwobaws and ins */
		unsigned wong	tstate;
		unsigned wong	tpc;
		unsigned wong	tnpc;
		unsigned int	y;
		unsigned int	fpws;
	}			sigc_wegs;
	__siginfo_fpu_t *	sigc_fpu_save;
	stwuct {
		void	*	ss_sp;
		int		ss_fwags;
		unsigned wong	ss_size;
	}			sigc_stack;
	unsigned wong		sigc_mask;
	__siginfo_wwin_t *	sigc_wwin_save;
};

#ewse

typedef stwuct {
	unsigned wong si_fwoat_wegs [32];
	unsigned wong si_fsw;
	unsigned wong si_fpqdepth;
	stwuct {
		unsigned wong *insn_addw;
		unsigned wong insn;
	} si_fpqueue [16];
} __siginfo_fpu_t;
#endif /* (CONFIG_SPAWC64) */


#endif /* !(__ASSEMBWY__) */

#endif /* !(__SPAWC_SIGCONTEXT_H) */
