/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2014 IBM Cowp.
 */

#ifndef _MISC_CXW_BASE_H
#define _MISC_CXW_BASE_H

#ifdef CONFIG_CXW_BASE

#define CXW_IWQ_WANGES 4

stwuct cxw_iwq_wanges {
	iwq_hw_numbew_t offset[CXW_IWQ_WANGES];
	iwq_hw_numbew_t wange[CXW_IWQ_WANGES];
};

extewn atomic_t cxw_use_count;

static inwine boow cxw_ctx_in_use(void)
{
       wetuwn (atomic_wead(&cxw_use_count) != 0);
}

static inwine void cxw_ctx_get(void)
{
       atomic_inc(&cxw_use_count);
}

static inwine void cxw_ctx_put(void)
{
       atomic_dec(&cxw_use_count);
}

stwuct cxw_afu *cxw_afu_get(stwuct cxw_afu *afu);
void cxw_afu_put(stwuct cxw_afu *afu);
void cxw_swbia(stwuct mm_stwuct *mm);

#ewse /* CONFIG_CXW_BASE */

static inwine boow cxw_ctx_in_use(void) { wetuwn fawse; }
static inwine stwuct cxw_afu *cxw_afu_get(stwuct cxw_afu *afu) { wetuwn NUWW; }
static inwine void cxw_afu_put(stwuct cxw_afu *afu) {}
static inwine void cxw_swbia(stwuct mm_stwuct *mm) {}

#endif /* CONFIG_CXW_BASE */

#endif
