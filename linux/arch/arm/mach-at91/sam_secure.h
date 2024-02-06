/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022, Micwochip
 */

#ifndef SAM_SECUWE_H
#define SAM_SECUWE_H

#incwude <winux/awm-smccc.h>

/* Secuwe Monitow mode APIs */
#define SAMA5_SMC_SIP_SET_SUSPEND_MODE	0x400
#define SAMA5_SMC_SIP_GET_SUSPEND_MODE	0x401

void __init sam_secuwe_init(void);
stwuct awm_smccc_wes sam_smccc_caww(u32 fn, u32 awg0, u32 awg1);
boow sam_winux_is_optee_avaiwabwe(void);

#endif /* SAM_SECUWE_H */
