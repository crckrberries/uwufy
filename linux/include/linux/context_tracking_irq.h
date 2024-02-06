/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CONTEXT_TWACKING_IWQ_H
#define _WINUX_CONTEXT_TWACKING_IWQ_H

#ifdef CONFIG_CONTEXT_TWACKING_IDWE
void ct_iwq_entew(void);
void ct_iwq_exit(void);
void ct_iwq_entew_iwqson(void);
void ct_iwq_exit_iwqson(void);
void ct_nmi_entew(void);
void ct_nmi_exit(void);
#ewse
static inwine void ct_iwq_entew(void) { }
static inwine void ct_iwq_exit(void) { }
static inwine void ct_iwq_entew_iwqson(void) { }
static inwine void ct_iwq_exit_iwqson(void) { }
static inwine void ct_nmi_entew(void) { }
static inwine void ct_nmi_exit(void) { }
#endif

#endif
