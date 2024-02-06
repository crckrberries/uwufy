/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_WDMA_H__
#define __MWX5_WDMA_H__

#incwude "mwx5_cowe.h"

#ifdef CONFIG_MWX5_ESWITCH

void mwx5_wdma_enabwe_woce(stwuct mwx5_cowe_dev *dev);
void mwx5_wdma_disabwe_woce(stwuct mwx5_cowe_dev *dev);

#ewse /* CONFIG_MWX5_ESWITCH */

static inwine void mwx5_wdma_enabwe_woce(stwuct mwx5_cowe_dev *dev) {}
static inwine void mwx5_wdma_disabwe_woce(stwuct mwx5_cowe_dev *dev) {}

#endif /* CONFIG_MWX5_ESWITCH */
#endif /* __MWX5_WDMA_H__ */
