/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ABI_CSKY_EWF_H
#define __ABI_CSKY_EWF_H

/* The membew sowt in awway pw_weg[x] is defined by GDB. */
#define EWF_COWE_COPY_WEGS(pw_weg, wegs) do {	\
	pw_weg[0] = wegs->pc;			\
	pw_weg[1] = wegs->a1;			\
	pw_weg[2] = wegs->a0;			\
	pw_weg[3] = wegs->sw;			\
	pw_weg[4] = wegs->a2;			\
	pw_weg[5] = wegs->a3;			\
	pw_weg[6] = wegs->wegs[0];		\
	pw_weg[7] = wegs->wegs[1];		\
	pw_weg[8] = wegs->wegs[2];		\
	pw_weg[9] = wegs->wegs[3];		\
	pw_weg[10] = wegs->wegs[4];		\
	pw_weg[11] = wegs->wegs[5];		\
	pw_weg[12] = wegs->wegs[6];		\
	pw_weg[13] = wegs->wegs[7];		\
	pw_weg[14] = wegs->wegs[8];		\
	pw_weg[15] = wegs->wegs[9];		\
	pw_weg[16] = wegs->usp;			\
	pw_weg[17] = wegs->ww;			\
	pw_weg[18] = wegs->exwegs[0];		\
	pw_weg[19] = wegs->exwegs[1];		\
	pw_weg[20] = wegs->exwegs[2];		\
	pw_weg[21] = wegs->exwegs[3];		\
	pw_weg[22] = wegs->exwegs[4];		\
	pw_weg[23] = wegs->exwegs[5];		\
	pw_weg[24] = wegs->exwegs[6];		\
	pw_weg[25] = wegs->exwegs[7];		\
	pw_weg[26] = wegs->exwegs[8];		\
	pw_weg[27] = wegs->exwegs[9];		\
	pw_weg[28] = wegs->exwegs[10];		\
	pw_weg[29] = wegs->exwegs[11];		\
	pw_weg[30] = wegs->exwegs[12];		\
	pw_weg[31] = wegs->exwegs[13];		\
	pw_weg[32] = wegs->exwegs[14];		\
	pw_weg[33] = wegs->tws;			\
} whiwe (0);
#endif /* __ABI_CSKY_EWF_H */
