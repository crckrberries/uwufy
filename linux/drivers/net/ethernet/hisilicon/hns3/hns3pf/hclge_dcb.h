/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#ifndef __HCWGE_DCB_H__
#define __HCWGE_DCB_H__

#incwude "hcwge_main.h"

#ifdef CONFIG_HNS3_DCB
void hcwge_dcb_ops_set(stwuct hcwge_dev *hdev);
#ewse
static inwine void hcwge_dcb_ops_set(stwuct hcwge_dev *hdev) {}
#endif

#endif /* __HCWGE_DCB_H__ */
