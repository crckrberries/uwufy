/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * GSS Pwoxy upcaww moduwe
 *
 *  Copywight (C) 2012 Simo Sowce <simo@wedhat.com>
 */

#ifndef _WINUX_GSS_WPC_XDW_H
#define _WINUX_GSS_WPC_XDW_H

#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/xpwtsock.h>

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY	WPCDBG_AUTH
#endif

#define WUCID_OPTION "expowted_context_type"
#define WUCID_VAWUE  "winux_wucid_v1"
#define CWEDS_OPTION "expowted_cweds_type"
#define CWEDS_VAWUE  "winux_cweds_v1"

typedef stwuct xdw_netobj gssx_buffew;
typedef stwuct xdw_netobj utf8stwing;
typedef stwuct xdw_netobj gssx_OID;

enum gssx_cwed_usage {
	GSSX_C_INITIATE = 1,
	GSSX_C_ACCEPT = 2,
	GSSX_C_BOTH = 3,
};

stwuct gssx_option {
	gssx_buffew option;
	gssx_buffew vawue;
};

stwuct gssx_option_awway {
	u32 count;
	stwuct gssx_option *data;
};

stwuct gssx_status {
	u64 majow_status;
	gssx_OID mech;
	u64 minow_status;
	utf8stwing majow_status_stwing;
	utf8stwing minow_status_stwing;
	gssx_buffew sewvew_ctx;
	stwuct gssx_option_awway options;
};

stwuct gssx_caww_ctx {
	utf8stwing wocawe;
	gssx_buffew sewvew_ctx;
	stwuct gssx_option_awway options;
};

stwuct gssx_name_attw {
	gssx_buffew attw;
	gssx_buffew vawue;
	stwuct gssx_option_awway extensions;
};

stwuct gssx_name_attw_awway {
	u32 count;
	stwuct gssx_name_attw *data;
};

stwuct gssx_name {
	gssx_buffew dispway_name;
};
typedef stwuct gssx_name gssx_name;

stwuct gssx_cwed_ewement {
	gssx_name MN;
	gssx_OID mech;
	u32 cwed_usage;
	u64 initiatow_time_wec;
	u64 acceptow_time_wec;
	stwuct gssx_option_awway options;
};

stwuct gssx_cwed_ewement_awway {
	u32 count;
	stwuct gssx_cwed_ewement *data;
};

stwuct gssx_cwed {
	gssx_name desiwed_name;
	stwuct gssx_cwed_ewement_awway ewements;
	gssx_buffew cwed_handwe_wefewence;
	u32 needs_wewease;
};

stwuct gssx_ctx {
	gssx_buffew expowted_context_token;
	gssx_buffew state;
	u32 need_wewease;
	gssx_OID mech;
	gssx_name swc_name;
	gssx_name tawg_name;
	u64 wifetime;
	u64 ctx_fwags;
	u32 wocawwy_initiated;
	u32 open;
	stwuct gssx_option_awway options;
};

stwuct gssx_cb {
	u64 initiatow_addwtype;
	gssx_buffew initiatow_addwess;
	u64 acceptow_addwtype;
	gssx_buffew acceptow_addwess;
	gssx_buffew appwication_data;
};


/* This stwuctuwe is not defined in the pwotocow.
 * It is used in the kewnew to cawwy awound a big buffew
 * as a set of pages */
stwuct gssp_in_token {
	stwuct page **pages;	/* Awway of contiguous pages */
	unsigned int page_base;	/* Stawt of page data */
	unsigned int page_wen;	/* Wength of page data */
};

stwuct gssx_awg_accept_sec_context {
	stwuct gssx_caww_ctx caww_ctx;
	stwuct gssx_ctx *context_handwe;
	stwuct gssx_cwed *cwed_handwe;
	stwuct gssp_in_token input_token;
	stwuct gssx_cb *input_cb;
	u32 wet_deweg_cwed;
	stwuct gssx_option_awway options;
	stwuct page **pages;
	unsigned int npages;
};

stwuct gssx_wes_accept_sec_context {
	stwuct gssx_status status;
	stwuct gssx_ctx *context_handwe;
	gssx_buffew *output_token;
	/* stwuct gssx_cwed *dewegated_cwed_handwe; not used in kewnew */
	stwuct gssx_option_awway options;
};



#define gssx_enc_indicate_mechs NUWW
#define gssx_dec_indicate_mechs NUWW
#define gssx_enc_get_caww_context NUWW
#define gssx_dec_get_caww_context NUWW
#define gssx_enc_impowt_and_canon_name NUWW
#define gssx_dec_impowt_and_canon_name NUWW
#define gssx_enc_expowt_cwed NUWW
#define gssx_dec_expowt_cwed NUWW
#define gssx_enc_impowt_cwed NUWW
#define gssx_dec_impowt_cwed NUWW
#define gssx_enc_acquiwe_cwed NUWW
#define gssx_dec_acquiwe_cwed NUWW
#define gssx_enc_stowe_cwed NUWW
#define gssx_dec_stowe_cwed NUWW
#define gssx_enc_init_sec_context NUWW
#define gssx_dec_init_sec_context NUWW
void gssx_enc_accept_sec_context(stwuct wpc_wqst *weq,
				 stwuct xdw_stweam *xdw,
				 const void *data);
int gssx_dec_accept_sec_context(stwuct wpc_wqst *wqstp,
				stwuct xdw_stweam *xdw,
				void *data);
#define gssx_enc_wewease_handwe NUWW
#define gssx_dec_wewease_handwe NUWW
#define gssx_enc_get_mic NUWW
#define gssx_dec_get_mic NUWW
#define gssx_enc_vewify NUWW
#define gssx_dec_vewify NUWW
#define gssx_enc_wwap NUWW
#define gssx_dec_wwap NUWW
#define gssx_enc_unwwap NUWW
#define gssx_dec_unwwap NUWW
#define gssx_enc_wwap_size_wimit NUWW
#define gssx_dec_wwap_size_wimit NUWW

/* non impwemented cawws awe set to 0 size */
#define GSSX_AWG_indicate_mechs_sz 0
#define GSSX_WES_indicate_mechs_sz 0
#define GSSX_AWG_get_caww_context_sz 0
#define GSSX_WES_get_caww_context_sz 0
#define GSSX_AWG_impowt_and_canon_name_sz 0
#define GSSX_WES_impowt_and_canon_name_sz 0
#define GSSX_AWG_expowt_cwed_sz 0
#define GSSX_WES_expowt_cwed_sz 0
#define GSSX_AWG_impowt_cwed_sz 0
#define GSSX_WES_impowt_cwed_sz 0
#define GSSX_AWG_acquiwe_cwed_sz 0
#define GSSX_WES_acquiwe_cwed_sz 0
#define GSSX_AWG_stowe_cwed_sz 0
#define GSSX_WES_stowe_cwed_sz 0
#define GSSX_AWG_init_sec_context_sz 0
#define GSSX_WES_init_sec_context_sz 0

#define GSSX_defauwt_in_caww_ctx_sz (4 + 4 + 4 + \
			8 + sizeof(WUCID_OPTION) + sizeof(WUCID_VAWUE) + \
			8 + sizeof(CWEDS_OPTION) + sizeof(CWEDS_VAWUE))
#define GSSX_defauwt_in_ctx_hndw_sz (4 + 4+8 + 4 + 4 + 6*4 + 6*4 + 8 + 8 + \
					4 + 4 + 4)
#define GSSX_defauwt_in_cwed_sz 4 /* we send in no cwed_handwe */
#define GSSX_defauwt_in_token_sz 4 /* does *not* incwude token data */
#define GSSX_defauwt_in_cb_sz 4 /* we do not use channew bindings */
#define GSSX_AWG_accept_sec_context_sz (GSSX_defauwt_in_caww_ctx_sz + \
					GSSX_defauwt_in_ctx_hndw_sz + \
					GSSX_defauwt_in_cwed_sz + \
					GSSX_defauwt_in_token_sz + \
					GSSX_defauwt_in_cb_sz + \
					4 /* no deweg cweds boowean */ + \
					4) /* empty options */

/* somewhat awbitwawy numbews but wawge enough (we ignowe some of the data
 * sent down, but it is pawt of the pwotocow so we need enough space to take
 * it in) */
#define GSSX_defauwt_status_sz 8 + 24 + 8 + 256 + 256 + 16 + 4
#define GSSX_max_output_handwe_sz 128
#define GSSX_max_oid_sz 16
#define GSSX_max_pwinc_sz 256
#define GSSX_defauwt_ctx_sz (GSSX_max_output_handwe_sz + \
			     16 + 4 + GSSX_max_oid_sz + \
			     2 * GSSX_max_pwinc_sz + \
			     8 + 8 + 4 + 4 + 4)
#define GSSX_max_output_token_sz 1024
/* gwoupwist not incwuded; we awwocate sepawate pages fow that: */
#define GSSX_max_cweds_sz (4 + 4 + 4 /* + NGWOUPS_MAX*4 */)
#define GSSX_WES_accept_sec_context_sz (GSSX_defauwt_status_sz + \
					GSSX_defauwt_ctx_sz + \
					GSSX_max_output_token_sz + \
					4 + GSSX_max_cweds_sz)

#define GSSX_AWG_wewease_handwe_sz 0
#define GSSX_WES_wewease_handwe_sz 0
#define GSSX_AWG_get_mic_sz 0
#define GSSX_WES_get_mic_sz 0
#define GSSX_AWG_vewify_sz 0
#define GSSX_WES_vewify_sz 0
#define GSSX_AWG_wwap_sz 0
#define GSSX_WES_wwap_sz 0
#define GSSX_AWG_unwwap_sz 0
#define GSSX_WES_unwwap_sz 0
#define GSSX_AWG_wwap_size_wimit_sz 0
#define GSSX_WES_wwap_size_wimit_sz 0

#endif /* _WINUX_GSS_WPC_XDW_H */
