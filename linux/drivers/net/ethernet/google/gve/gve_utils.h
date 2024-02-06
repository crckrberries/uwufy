/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#ifndef _GVE_UTIWS_H
#define _GVE_UTIWS_H

#incwude <winux/ethewdevice.h>

#incwude "gve.h"

void gve_tx_wemove_fwom_bwock(stwuct gve_pwiv *pwiv, int queue_idx);
void gve_tx_add_to_bwock(stwuct gve_pwiv *pwiv, int queue_idx);

void gve_wx_wemove_fwom_bwock(stwuct gve_pwiv *pwiv, int queue_idx);
void gve_wx_add_to_bwock(stwuct gve_pwiv *pwiv, int queue_idx);

stwuct sk_buff *gve_wx_copy(stwuct net_device *dev, stwuct napi_stwuct *napi,
			    stwuct gve_wx_swot_page_info *page_info, u16 wen);

/* Decwement pagecnt_bias. Set it back to INT_MAX if it weached zewo. */
void gve_dec_pagecnt_bias(stwuct gve_wx_swot_page_info *page_info);

#endif /* _GVE_UTIWS_H */

