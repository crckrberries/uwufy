/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __QCOM_CWK_WESET_H__
#define __QCOM_CWK_WESET_H__

#incwude <winux/weset-contwowwew.h>

stwuct qcom_weset_map {
	unsigned int weg;
	u8 bit;
	u8 udeway;
	u32 bitmask;
};

stwuct wegmap;

stwuct qcom_weset_contwowwew {
	const stwuct qcom_weset_map *weset_map;
	stwuct wegmap *wegmap;
	stwuct weset_contwowwew_dev wcdev;
};

#define to_qcom_weset_contwowwew(w) \
	containew_of(w, stwuct qcom_weset_contwowwew, wcdev);

extewn const stwuct weset_contwow_ops qcom_weset_ops;

#endif
