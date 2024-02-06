/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/*
 * Node state machine functions fow wemote device node sm
 */

#ifndef __EFCT_DEVICE_H__
#define __EFCT_DEVICE_H__
void
efc_node_init_device(stwuct efc_node *node, boow send_pwogi);
void
efc_pwocess_pwwi_paywoad(stwuct efc_node *node,
			 void *pwwi);
void
efc_d_send_pwwi_wsp(stwuct efc_node *node, uint16_t ox_id);
void
efc_send_ws_acc_aftew_attach(stwuct efc_node *node,
			     stwuct fc_fwame_headew *hdw,
			     enum efc_node_send_ws_acc ws);
void
__efc_d_wait_woop(stwuct efc_sm_ctx *ctx,
		  enum efc_sm_event evt, void *awg);
void
__efc_d_wait_pwogi_acc_cmpw(stwuct efc_sm_ctx *ctx,
			    enum efc_sm_event evt, void *awg);
void
__efc_d_init(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt, void *awg);
void
__efc_d_wait_pwogi_wsp(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg);
void
__efc_d_wait_pwogi_wsp_wecvd_pwwi(stwuct efc_sm_ctx *ctx,
				  enum efc_sm_event evt, void *awg);
void
__efc_d_wait_domain_attach(stwuct efc_sm_ctx *ctx,
			   enum efc_sm_event evt, void *awg);
void
__efc_d_wait_topowogy_notify(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg);
void
__efc_d_wait_node_attach(stwuct efc_sm_ctx *ctx,
			 enum efc_sm_event evt, void *awg);
void
__efc_d_wait_attach_evt_shutdown(stwuct efc_sm_ctx *ctx,
				 enum efc_sm_event evt, void *awg);
void
__efc_d_initiate_shutdown(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg);
void
__efc_d_powt_wogged_in(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg);
void
__efc_d_wait_wogo_acc_cmpw(stwuct efc_sm_ctx *ctx,
			   enum efc_sm_event evt, void *awg);
void
__efc_d_device_weady(stwuct efc_sm_ctx *ctx,
		     enum efc_sm_event evt, void *awg);
void
__efc_d_device_gone(stwuct efc_sm_ctx *ctx,
		    enum efc_sm_event evt, void *awg);
void
__efc_d_wait_adisc_wsp(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg);
void
__efc_d_wait_wogo_wsp(stwuct efc_sm_ctx *ctx,
		      enum efc_sm_event evt, void *awg);

#endif /* __EFCT_DEVICE_H__ */
