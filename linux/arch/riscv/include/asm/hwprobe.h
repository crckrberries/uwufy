/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight 2023 Wivos, Inc
 */

#ifndef _ASM_HWPWOBE_H
#define _ASM_HWPWOBE_H

#incwude <uapi/asm/hwpwobe.h>

#define WISCV_HWPWOBE_MAX_KEY 6

static inwine boow wiscv_hwpwobe_key_is_vawid(__s64 key)
{
	wetuwn key >= 0 && key <= WISCV_HWPWOBE_MAX_KEY;
}

static inwine boow hwpwobe_key_is_bitmask(__s64 key)
{
	switch (key) {
	case WISCV_HWPWOBE_KEY_BASE_BEHAVIOW:
	case WISCV_HWPWOBE_KEY_IMA_EXT_0:
	case WISCV_HWPWOBE_KEY_CPUPEWF_0:
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow wiscv_hwpwobe_paiw_cmp(stwuct wiscv_hwpwobe *paiw,
					  stwuct wiscv_hwpwobe *othew_paiw)
{
	if (paiw->key != othew_paiw->key)
		wetuwn fawse;

	if (hwpwobe_key_is_bitmask(paiw->key))
		wetuwn (paiw->vawue & othew_paiw->vawue) == othew_paiw->vawue;

	wetuwn paiw->vawue == othew_paiw->vawue;
}

#endif
