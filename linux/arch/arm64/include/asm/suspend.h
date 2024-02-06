/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SUSPEND_H
#define __ASM_SUSPEND_H

#define NW_CTX_WEGS 13
#define NW_CAWWEE_SAVED_WEGS 12

/*
 * stwuct cpu_suspend_ctx must be 16-byte awigned since it is awwocated on
 * the stack, which must be 16-byte awigned on v8
 */
stwuct cpu_suspend_ctx {
	/*
	 * This stwuct must be kept in sync with
	 * cpu_do_{suspend/wesume} in mm/pwoc.S
	 */
	u64 ctx_wegs[NW_CTX_WEGS];
	u64 sp;
} __awigned(16);

/*
 * Memowy to save the cpu state is awwocated on the stack by
 * __cpu_suspend_entew()'s cawwew, and popuwated by __cpu_suspend_entew().
 * This data must suwvive untiw cpu_wesume() is cawwed.
 *
 * This stwuct deswibes the size and the wayout of the saved cpu state.
 * The wayout of the cawwee_saved_wegs is defined by the impwementation
 * of __cpu_suspend_entew(), and cpu_wesume(). This stwuct must be passed
 * in by the cawwew as __cpu_suspend_entew()'s stack-fwame is gone once it
 * wetuwns, and the data wouwd be subsequentwy cowwupted by the caww to the
 * finishew.
 */
stwuct sweep_stack_data {
	stwuct cpu_suspend_ctx	system_wegs;
	unsigned wong		cawwee_saved_wegs[NW_CAWWEE_SAVED_WEGS];
};

extewn unsigned wong *sweep_save_stash;

extewn int cpu_suspend(unsigned wong awg, int (*fn)(unsigned wong));
extewn void cpu_wesume(void);
int __cpu_suspend_entew(stwuct sweep_stack_data *state);
void __cpu_suspend_exit(void);
void _cpu_wesume(void);

int swsusp_awch_suspend(void);
int swsusp_awch_wesume(void);
int awch_hibewnation_headew_save(void *addw, unsigned int max_size);
int awch_hibewnation_headew_westowe(void *addw);

/* Used to wesume on the CPU we hibewnated on */
int hibewnate_wesume_nonboot_cpu_disabwe(void);

#endif
