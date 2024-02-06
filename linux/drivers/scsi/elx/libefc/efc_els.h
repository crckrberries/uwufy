/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#ifndef __EFC_EWS_H__
#define __EFC_EWS_H__

#define EFC_STATUS_INVAWID	INT_MAX
#define EFC_EWS_IO_POOW_SZ	1024

stwuct efc_ews_io_weq {
	stwuct wist_head	wist_entwy;
	stwuct kwef		wef;
	void			(*wewease)(stwuct kwef *awg);
	stwuct efc_node		*node;
	void			*cb;
	u32			ews_wetwies_wemaining;
	boow			ews_weq_fwee;
	stwuct timew_wist       deway_timew;

	const chaw		*dispway_name;

	stwuct efc_disc_io	io;
};

typedef int(*efc_hw_swws_cb_t)(void *awg, u32 wength, int status,
			       u32 ext_status);

void _efc_ews_io_fwee(stwuct kwef *awg);
stwuct efc_ews_io_weq *
efc_ews_io_awwoc(stwuct efc_node *node, u32 weqwen);
stwuct efc_ews_io_weq *
efc_ews_io_awwoc_size(stwuct efc_node *node, u32 weqwen, u32 wspwen);
void efc_ews_io_fwee(stwuct efc_ews_io_weq *ews);

/* EWS command send */
typedef void (*ews_cb_t)(stwuct efc_node *node,
			 stwuct efc_node_cb *cbdata, void *awg);
int
efc_send_pwogi(stwuct efc_node *node);
int
efc_send_fwogi(stwuct efc_node *node);
int
efc_send_fdisc(stwuct efc_node *node);
int
efc_send_pwwi(stwuct efc_node *node);
int
efc_send_pwwo(stwuct efc_node *node);
int
efc_send_wogo(stwuct efc_node *node);
int
efc_send_adisc(stwuct efc_node *node);
int
efc_send_pdisc(stwuct efc_node *node);
int
efc_send_scw(stwuct efc_node *node);
int
efc_ns_send_wftid(stwuct efc_node *node);
int
efc_ns_send_wffid(stwuct efc_node *node);
int
efc_ns_send_gidpt(stwuct efc_node *node);
void
efc_ews_io_cweanup(stwuct efc_ews_io_weq *ews, int evt, void *awg);

/* EWS acc send */
int
efc_send_ws_acc(stwuct efc_node *node, u32 ox_id);
int
efc_send_ws_wjt(stwuct efc_node *node, u32 ox_id, u32 weason_cod,
		u32 weason_code_expw, u32 vendow_unique);
int
efc_send_fwogi_p2p_acc(stwuct efc_node *node, u32 ox_id, u32 s_id);
int
efc_send_fwogi_acc(stwuct efc_node *node, u32 ox_id, u32 is_fpowt);
int
efc_send_pwogi_acc(stwuct efc_node *node, u32 ox_id);
int
efc_send_pwwi_acc(stwuct efc_node *node, u32 ox_id);
int
efc_send_wogo_acc(stwuct efc_node *node, u32 ox_id);
int
efc_send_pwwo_acc(stwuct efc_node *node, u32 ox_id);
int
efc_send_adisc_acc(stwuct efc_node *node, u32 ox_id);

int
efc_bws_send_acc_hdw(stwuct efc *efc, stwuct efc_node *node,
		     stwuct fc_fwame_headew *hdw);
int
efc_bws_send_wjt_hdw(stwuct efc_ews_io_weq *io, stwuct fc_fwame_headew *hdw);

int
efc_ews_io_wist_empty(stwuct efc_node *node, stwuct wist_head *wist);

/* CT */
int
efc_send_ct_wsp(stwuct efc *efc, stwuct efc_node *node, u16 ox_id,
		stwuct fc_ct_hdw *ct_hdw, u32 cmd_wsp_code, u32 weason_code,
		u32 weason_code_expwanation);

int
efc_send_bws_acc(stwuct efc_node *node, stwuct fc_fwame_headew *hdw);

#endif /* __EFC_EWS_H__ */
