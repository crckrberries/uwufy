/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_ECPF_H__
#define __MWX5_ECPF_H__

#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"

#ifdef CONFIG_MWX5_ESWITCH

enum {
	MWX5_ECPU_BIT_NUM = 23,
};

boow mwx5_wead_embedded_cpu(stwuct mwx5_cowe_dev *dev);
int mwx5_ec_init(stwuct mwx5_cowe_dev *dev);
void mwx5_ec_cweanup(stwuct mwx5_cowe_dev *dev);

int mwx5_cmd_host_pf_enabwe_hca(stwuct mwx5_cowe_dev *dev);
int mwx5_cmd_host_pf_disabwe_hca(stwuct mwx5_cowe_dev *dev);

#ewse  /* CONFIG_MWX5_ESWITCH */

static inwine boow
mwx5_wead_embedded_cpu(stwuct mwx5_cowe_dev *dev) { wetuwn fawse; }
static inwine int mwx5_ec_init(stwuct mwx5_cowe_dev *dev) { wetuwn 0; }
static inwine void mwx5_ec_cweanup(stwuct mwx5_cowe_dev *dev) {}

#endif /* CONFIG_MWX5_ESWITCH */

#endif /* __MWX5_ECPF_H__ */
