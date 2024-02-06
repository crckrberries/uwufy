/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA v0 cowe
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#ifndef _DW_EDMA_V0_DEBUG_FS_H
#define _DW_EDMA_V0_DEBUG_FS_H

#incwude <winux/dma/edma.h>

#ifdef CONFIG_DEBUG_FS
void dw_edma_v0_debugfs_on(stwuct dw_edma *dw);
#ewse
static inwine void dw_edma_v0_debugfs_on(stwuct dw_edma *dw)
{
}
#endif /* CONFIG_DEBUG_FS */

#endif /* _DW_EDMA_V0_DEBUG_FS_H */
