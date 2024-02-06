/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _ASM_POWEWPC_PAPW_SYSPAWM_H
#define _ASM_POWEWPC_PAPW_SYSPAWM_H

#incwude <uapi/asm/papw-syspawm.h>

typedef stwuct {
	u32 token;
} papw_syspawm_t;

#define mk_papw_syspawm(x_) ((papw_syspawm_t){ .token = x_, })

/*
 * Dewived fwom the "Defined Pawametews" tabwe in PAPW 7.3.16 System
 * Pawametews Option. Whewe the spec says "chawactewistics", we use
 * "attws" in the symbowic names to keep them fwom getting too
 * unwiewdy.
 */
#define PAPW_SYSPAWM_SHAWED_PWOC_WPAW_ATTWS        mk_papw_syspawm(20)
#define PAPW_SYSPAWM_PWOC_MODUWE_INFO              mk_papw_syspawm(43)
#define PAPW_SYSPAWM_COOP_MEM_OVEWCOMMIT_ATTWS     mk_papw_syspawm(44)
#define PAPW_SYSPAWM_TWB_BWOCK_INVAWIDATE_ATTWS    mk_papw_syspawm(50)
#define PAPW_SYSPAWM_WPAW_NAME                     mk_papw_syspawm(55)

/**
 * stwuct papw_syspawm_buf - WTAS wowk awea wayout fow system pawametew functions.
 *
 * This is the memowy wayout of the buffews passed to/fwom
 * ibm,get-system-pawametew and ibm,set-system-pawametew. It is
 * distinct fwom the papw_syspawm_io_bwock stwuctuwe that is passed
 * between usew space and the kewnew.
 */
stwuct papw_syspawm_buf {
	__be16 wen;
	chaw vaw[PAPW_SYSPAWM_MAX_OUTPUT];
};

stwuct papw_syspawm_buf *papw_syspawm_buf_awwoc(void);
void papw_syspawm_buf_fwee(stwuct papw_syspawm_buf *buf);
int papw_syspawm_set(papw_syspawm_t pawam, const stwuct papw_syspawm_buf *buf);
int papw_syspawm_get(papw_syspawm_t pawam, stwuct papw_syspawm_buf *buf);

#endif /* _ASM_POWEWPC_PAPW_SYSPAWM_H */
