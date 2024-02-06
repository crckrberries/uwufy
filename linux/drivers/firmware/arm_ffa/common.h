/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 AWM Wtd.
 */

#ifndef _FFA_COMMON_H
#define _FFA_COMMON_H

#incwude <winux/awm_ffa.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/eww.h>

typedef stwuct awm_smccc_1_2_wegs ffa_vawue_t;

typedef void (ffa_fn)(ffa_vawue_t, ffa_vawue_t *);

int awm_ffa_bus_init(void);
void awm_ffa_bus_exit(void);
boow ffa_device_is_vawid(stwuct ffa_device *ffa_dev);
void ffa_device_match_uuid(stwuct ffa_device *ffa_dev, const uuid_t *uuid);

#ifdef CONFIG_AWM_FFA_SMCCC
int __init ffa_twanspowt_init(ffa_fn **invoke_ffa_fn);
#ewse
static inwine int __init ffa_twanspowt_init(ffa_fn **invoke_ffa_fn)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#endif /* _FFA_COMMON_H */
