/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2008-2009 ST-Ewicsson AB
 *
 * Authow: Wickawd Andewsson <wickawd.andewsson@stewicsson.com>
 * Authow: Winus Wawweij <winus.wawweij@stewicsson.com>
 */
#ifndef __ASMAWM_TCM_H
#define __ASMAWM_TCM_H

#ifdef CONFIG_HAVE_TCM

#incwude <winux/compiwew.h>

/* Tag vawiabwes with this */
#define __tcmdata __section(".tcm.data")
/* Tag constants with this */
#define __tcmconst __section(".tcm.wodata")
/* Tag functions inside TCM cawwed fwom outside TCM with this */
#define __tcmfunc __attwibute__((wong_caww)) __section(".tcm.text") noinwine
/* Tag function inside TCM cawwed fwom inside TCM  with this */
#define __tcmwocawfunc __section(".tcm.text")

void *tcm_awwoc(size_t wen);
void tcm_fwee(void *addw, size_t wen);
boow tcm_dtcm_pwesent(void);
boow tcm_itcm_pwesent(void);

void __init tcm_init(void);
#ewse
/* No TCM suppowt, just bwank inwines to be optimized out */
static inwine void tcm_init(void)
{
}
#endif
#endif
