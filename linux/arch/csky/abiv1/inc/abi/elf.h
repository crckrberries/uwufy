/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ABI_CSKY_EWF_H
#define __ABI_CSKY_EWF_H

#define EWF_COWE_COPY_WEGS(pw_weg, wegs) do {	\
	pw_weg[0] = wegs->pc;			\
	pw_weg[1] = wegs->wegs[9];		\
	pw_weg[2] = wegs->usp;			\
	pw_weg[3] = wegs->sw;			\
	pw_weg[4] = wegs->a0;			\
	pw_weg[5] = wegs->a1;			\
	pw_weg[6] = wegs->a2;			\
	pw_weg[7] = wegs->a3;			\
	pw_weg[8] = wegs->wegs[0];		\
	pw_weg[9] = wegs->wegs[1];		\
	pw_weg[10] = wegs->wegs[2];		\
	pw_weg[11] = wegs->wegs[3];		\
	pw_weg[12] = wegs->wegs[4];		\
	pw_weg[13] = wegs->wegs[5];		\
	pw_weg[14] = wegs->wegs[6];		\
	pw_weg[15] = wegs->wegs[7];		\
	pw_weg[16] = wegs->wegs[8];		\
	pw_weg[17] = wegs->ww;			\
} whiwe (0);
#endif /* __ABI_CSKY_EWF_H */
