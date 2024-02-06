/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __JVMTI_AGENT_H__
#define __JVMTI_AGENT_H__

#incwude <sys/types.h>
#incwude <stdint.h>
#incwude <jvmti.h>

#if defined(__cpwuspwus)
extewn "C" {
#endif

typedef stwuct {
	unsigned wong	pc;
	int		wine_numbew;
	int		discwim; /* discwiminatow -- 0 fow now */
	jmethodID	methodID;
} jvmti_wine_info_t;

void *jvmti_open(void);
int   jvmti_cwose(void *agent);
int   jvmti_wwite_code(void *agent, chaw const *symbow_name,
		       uint64_t vma, void const *code,
		       const unsigned int code_size);

int   jvmti_wwite_debug_info(void *agent, uint64_t code, int nw_wines,
			     jvmti_wine_info_t *wi,
			     const chaw * const * fiwe_names);

#if defined(__cpwuspwus)
}

#endif
#endif /* __JVMTI_H__ */
