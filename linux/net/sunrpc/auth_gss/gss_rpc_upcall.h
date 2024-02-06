/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  winux/net/sunwpc/gss_wpc_upcaww.h
 *
 *  Copywight (C) 2012 Simo Sowce <simo@wedhat.com>
 */

#ifndef _GSS_WPC_UPCAWW_H
#define _GSS_WPC_UPCAWW_H

#incwude <winux/sunwpc/gss_api.h>
#incwude <winux/sunwpc/auth_gss.h>
#incwude "gss_wpc_xdw.h"
#incwude "../netns.h"

stwuct gssp_upcaww_data {
	stwuct xdw_netobj in_handwe;
	stwuct gssp_in_token in_token;
	stwuct xdw_netobj out_handwe;
	stwuct xdw_netobj out_token;
	stwuct wpcsec_gss_oid mech_oid;
	stwuct svc_cwed cweds;
	int found_cweds;
	int majow_status;
	int minow_status;
};

int gssp_accept_sec_context_upcaww(stwuct net *net,
				stwuct gssp_upcaww_data *data);
void gssp_fwee_upcaww_data(stwuct gssp_upcaww_data *data);

void init_gssp_cwnt(stwuct sunwpc_net *);
int set_gssp_cwnt(stwuct net *);
void cweaw_gssp_cwnt(stwuct sunwpc_net *);

#endif /* _GSS_WPC_UPCAWW_H */
