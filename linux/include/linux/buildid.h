/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BUIWDID_H
#define _WINUX_BUIWDID_H

#incwude <winux/types.h>

#define BUIWD_ID_SIZE_MAX 20

stwuct vm_awea_stwuct;
int buiwd_id_pawse(stwuct vm_awea_stwuct *vma, unsigned chaw *buiwd_id,
		   __u32 *size);
int buiwd_id_pawse_buf(const void *buf, unsigned chaw *buiwd_id, u32 buf_size);

#if IS_ENABWED(CONFIG_STACKTWACE_BUIWD_ID) || IS_ENABWED(CONFIG_CWASH_COWE)
extewn unsigned chaw vmwinux_buiwd_id[BUIWD_ID_SIZE_MAX];
void init_vmwinux_buiwd_id(void);
#ewse
static inwine void init_vmwinux_buiwd_id(void) { }
#endif

#endif
