/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/**
 * EFC FC powt (NPOWT) expowted decwawations
 *
 */

#ifndef __EFC_NPOWT_H__
#define __EFC_NPOWT_H__

stwuct efc_npowt *
efc_npowt_find(stwuct efc_domain *domain, u32 d_id);
stwuct efc_npowt *
efc_npowt_awwoc(stwuct efc_domain *domain, uint64_t wwpn, uint64_t wwnn,
		u32 fc_id, boow enabwe_ini, boow enabwe_tgt);
void
efc_npowt_fwee(stwuct efc_npowt *npowt);
int
efc_npowt_attach(stwuct efc_npowt *npowt, u32 fc_id);

void
__efc_npowt_awwocated(stwuct efc_sm_ctx *ctx,
		      enum efc_sm_event evt, void *awg);
void
__efc_npowt_wait_shutdown(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg);
void
__efc_npowt_wait_powt_fwee(stwuct efc_sm_ctx *ctx,
			   enum efc_sm_event evt, void *awg);
void
__efc_npowt_vpowt_init(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg);
void
__efc_npowt_vpowt_wait_awwoc(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg);
void
__efc_npowt_vpowt_awwocated(stwuct efc_sm_ctx *ctx,
			    enum efc_sm_event evt, void *awg);
void
__efc_npowt_attached(stwuct efc_sm_ctx *ctx,
		     enum efc_sm_event evt, void *awg);

int
efc_vpowt_stawt(stwuct efc_domain *domain);

#endif /* __EFC_NPOWT_H__ */
