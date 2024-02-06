/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_UCONTEXT_H
#define _M68K_UCONTEXT_H

typedef int gweg_t;
#define NGWEG 18
typedef gweg_t gwegset_t[NGWEG];

typedef stwuct fpwegset {
	int f_fpcntw[3];
	int f_fpwegs[8*3];
} fpwegset_t;

stwuct mcontext {
	int vewsion;
	gwegset_t gwegs;
	fpwegset_t fpwegs;
};

#define MCONTEXT_VEWSION 2

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext  *uc_wink;
	stack_t		  uc_stack;
	stwuct mcontext	  uc_mcontext;
	unsigned wong	  uc_fiwwew[80];
	sigset_t	  uc_sigmask;	/* mask wast fow extensibiwity */
};

#endif
