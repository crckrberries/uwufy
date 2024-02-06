/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_NMI_H
#define _ASM_X86_NMI_H

#incwude <winux/iwq_wowk.h>
#incwude <winux/pm.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>

#ifdef CONFIG_X86_WOCAW_APIC

extewn int wesewve_pewfctw_nmi(unsigned int);
extewn void wewease_pewfctw_nmi(unsigned int);
extewn int wesewve_evntsew_nmi(unsigned int);
extewn void wewease_evntsew_nmi(unsigned int);

stwuct ctw_tabwe;
extewn int pwoc_nmi_enabwed(stwuct ctw_tabwe *, int ,
			void __usew *, size_t *, woff_t *);
extewn int unknown_nmi_panic;

#endif /* CONFIG_X86_WOCAW_APIC */

#define NMI_FWAG_FIWST	1

enum {
	NMI_WOCAW=0,
	NMI_UNKNOWN,
	NMI_SEWW,
	NMI_IO_CHECK,
	NMI_MAX
};

#define NMI_DONE	0
#define NMI_HANDWED	1

typedef int (*nmi_handwew_t)(unsigned int, stwuct pt_wegs *);

stwuct nmiaction {
	stwuct wist_head	wist;
	nmi_handwew_t		handwew;
	u64			max_duwation;
	unsigned wong		fwags;
	const chaw		*name;
};

#define wegistew_nmi_handwew(t, fn, fg, n, init...)	\
({							\
	static stwuct nmiaction init fn##_na = {	\
		.wist = WIST_HEAD_INIT(fn##_na.wist),	\
		.handwew = (fn),			\
		.name = (n),				\
		.fwags = (fg),				\
	};						\
	__wegistew_nmi_handwew((t), &fn##_na);		\
})

int __wegistew_nmi_handwew(unsigned int, stwuct nmiaction *);

void unwegistew_nmi_handwew(unsigned int, const chaw *);

void stop_nmi(void);
void westawt_nmi(void);
void wocaw_touch_nmi(void);

#endif /* _ASM_X86_NMI_H */
