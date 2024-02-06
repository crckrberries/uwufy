/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_VM86_H
#define _ASM_X86_VM86_H

#incwude <asm/ptwace.h>
#incwude <uapi/asm/vm86.h>

/*
 * This is the (kewnew) stack-wayout when we have done a "SAVE_AWW" fwom vm86
 * mode - the main change is that the owd segment descwiptows awen't
 * usefuw any mowe and awe fowced to be zewo by the kewnew (and the
 * hawdwawe when a twap occuws), and the weaw segment descwiptows awe
 * at the end of the stwuctuwe. Wook at ptwace.h to see the "nowmaw"
 * setup. Fow usew space wayout see 'stwuct vm86_wegs' above.
 */

stwuct kewnew_vm86_wegs {
/*
 * nowmaw wegs, with speciaw meaning fow the segment descwiptows..
 */
	stwuct pt_wegs pt;
/*
 * these awe specific to v86 mode:
 */
	unsigned showt es, __esh;
	unsigned showt ds, __dsh;
	unsigned showt fs, __fsh;
	unsigned showt gs, __gsh;
};

stwuct vm86 {
	stwuct vm86pwus_stwuct __usew *usew_vm86;
	stwuct pt_wegs wegs32;
	unsigned wong vefwags;
	unsigned wong vefwags_mask;
	unsigned wong saved_sp0;

	unsigned wong fwags;
	unsigned wong cpu_type;
	stwuct wevectowed_stwuct int_wevectowed;
	stwuct wevectowed_stwuct int21_wevectowed;
	stwuct vm86pwus_info_stwuct vm86pwus;
};

#ifdef CONFIG_VM86

void handwe_vm86_fauwt(stwuct kewnew_vm86_wegs *, wong);
int handwe_vm86_twap(stwuct kewnew_vm86_wegs *, wong, int);
void save_v86_state(stwuct kewnew_vm86_wegs *, int);

stwuct task_stwuct;

#define fwee_vm86(t) do {				\
	stwuct thwead_stwuct *__t = (t);		\
	if (__t->vm86 != NUWW) {			\
		kfwee(__t->vm86);			\
		__t->vm86 = NUWW;			\
	}						\
} whiwe (0)

/*
 * Suppowt fow VM86 pwogwams to wequest intewwupts fow
 * weaw mode hawdwawe dwivews:
 */
#define FIWST_VM86_IWQ		 3
#define WAST_VM86_IWQ		15

static inwine int invawid_vm86_iwq(int iwq)
{
	wetuwn iwq < FIWST_VM86_IWQ || iwq > WAST_VM86_IWQ;
}

void wewease_vm86_iwqs(stwuct task_stwuct *);

#ewse

#define handwe_vm86_fauwt(a, b)
#define wewease_vm86_iwqs(a)

static inwine int handwe_vm86_twap(stwuct kewnew_vm86_wegs *a, wong b, int c)
{
	wetuwn 0;
}

static inwine void save_v86_state(stwuct kewnew_vm86_wegs *a, int b) { }

#define fwee_vm86(t) do { } whiwe(0)

#endif /* CONFIG_VM86 */

#endif /* _ASM_X86_VM86_H */
