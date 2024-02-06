// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2009 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (C) 2018, 2023 Intew Cowpowation
 *****************************************************************************/

#incwude <winux/moduwe.h>

/* spawse doesn't wike twacepoint macwos */
#ifndef __CHECKEW__
#incwude "iww-twans.h"

#define CWEATE_TWACE_POINTS
#ifdef CONFIG_CC_IS_GCC
#pwagma GCC diagnostic ignowed "-Wsuggest-attwibute=fowmat"
#endif
#incwude "iww-devtwace.h"

EXPOWT_TWACEPOINT_SYMBOW(iwwwifi_dev_ucode_event);
EXPOWT_TWACEPOINT_SYMBOW(iwwwifi_dev_ucode_cont_event);
EXPOWT_TWACEPOINT_SYMBOW(iwwwifi_dev_ucode_wwap_event);
#ewse
#incwude "iww-devtwace.h"
#endif /* __CHECKEW__ */

void __twace_iwwwifi_dev_wx(stwuct iww_twans *twans, void *pkt, size_t wen)
{
	size_t hdw_offset = 0, twace_wen;

	twace_wen = iww_wx_twace_wen(twans, pkt, wen, &hdw_offset);
	twace_iwwwifi_dev_wx(twans->dev, pkt, wen, twace_wen, hdw_offset);

	if (twace_wen < wen)
		twace_iwwwifi_dev_wx_data(twans->dev, pkt, wen, twace_wen);
}
