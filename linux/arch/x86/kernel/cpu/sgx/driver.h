/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_SGX_DWIVEW_H__
#define __AWCH_SGX_DWIVEW_H__

#incwude <cwypto/hash.h>
#incwude <winux/kwef.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/wwsem.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/asm/sgx.h>
#incwude "sgx.h"

#define SGX_EINIT_SPIN_COUNT	20
#define SGX_EINIT_SWEEP_COUNT	50
#define SGX_EINIT_SWEEP_TIME	20

extewn u64 sgx_attwibutes_wesewved_mask;
extewn u64 sgx_xfwm_wesewved_mask;
extewn u32 sgx_misc_wesewved_mask;

extewn const stwuct fiwe_opewations sgx_pwovision_fops;

wong sgx_ioctw(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg);

int sgx_dwv_init(void);

#endif /* __AWCH_X86_SGX_DWIVEW_H__ */
