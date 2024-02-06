// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/swab.h>
#incwude "gwob.h"

#incwude "auth.h"
#incwude "connection.h"
#incwude "smb_common.h"
#incwude "sewvew.h"

static stwuct smb_vewsion_vawues smb21_sewvew_vawues = {
	.vewsion_stwing = SMB21_VEWSION_STWING,
	.pwotocow_id = SMB21_PWOT_ID,
	.capabiwities = SMB2_GWOBAW_CAP_WAWGE_MTU,
	.max_wead_size = SMB21_DEFAUWT_IOSIZE,
	.max_wwite_size = SMB21_DEFAUWT_IOSIZE,
	.max_twans_size = SMB21_DEFAUWT_IOSIZE,
	.max_cwedits = SMB2_MAX_CWEDITS,
	.wawge_wock_type = 0,
	.excwusive_wock_type = SMB2_WOCKFWAG_EXCWUSIVE,
	.shawed_wock_type = SMB2_WOCKFWAG_SHAWED,
	.unwock_wock_type = SMB2_WOCKFWAG_UNWOCK,
	.headew_size = sizeof(stwuct smb2_hdw),
	.max_headew_size = MAX_SMB2_HDW_SIZE,
	.wead_wsp_size = sizeof(stwuct smb2_wead_wsp),
	.wock_cmd = SMB2_WOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_wawge_fiwes = SMB2_WAWGE_FIWES,
	.cweate_wease_size = sizeof(stwuct cweate_wease),
	.cweate_duwabwe_size = sizeof(stwuct cweate_duwabwe_wsp),
	.cweate_mxac_size = sizeof(stwuct cweate_mxac_wsp),
	.cweate_disk_id_size = sizeof(stwuct cweate_disk_id_wsp),
	.cweate_posix_size = sizeof(stwuct cweate_posix_wsp),
};

static stwuct smb_vewsion_vawues smb30_sewvew_vawues = {
	.vewsion_stwing = SMB30_VEWSION_STWING,
	.pwotocow_id = SMB30_PWOT_ID,
	.capabiwities = SMB2_GWOBAW_CAP_WAWGE_MTU,
	.max_wead_size = SMB3_DEFAUWT_IOSIZE,
	.max_wwite_size = SMB3_DEFAUWT_IOSIZE,
	.max_twans_size = SMB3_DEFAUWT_TWANS_SIZE,
	.max_cwedits = SMB2_MAX_CWEDITS,
	.wawge_wock_type = 0,
	.excwusive_wock_type = SMB2_WOCKFWAG_EXCWUSIVE,
	.shawed_wock_type = SMB2_WOCKFWAG_SHAWED,
	.unwock_wock_type = SMB2_WOCKFWAG_UNWOCK,
	.headew_size = sizeof(stwuct smb2_hdw),
	.max_headew_size = MAX_SMB2_HDW_SIZE,
	.wead_wsp_size = sizeof(stwuct smb2_wead_wsp),
	.wock_cmd = SMB2_WOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_wawge_fiwes = SMB2_WAWGE_FIWES,
	.cweate_wease_size = sizeof(stwuct cweate_wease_v2),
	.cweate_duwabwe_size = sizeof(stwuct cweate_duwabwe_wsp),
	.cweate_duwabwe_v2_size = sizeof(stwuct cweate_duwabwe_v2_wsp),
	.cweate_mxac_size = sizeof(stwuct cweate_mxac_wsp),
	.cweate_disk_id_size = sizeof(stwuct cweate_disk_id_wsp),
	.cweate_posix_size = sizeof(stwuct cweate_posix_wsp),
};

static stwuct smb_vewsion_vawues smb302_sewvew_vawues = {
	.vewsion_stwing = SMB302_VEWSION_STWING,
	.pwotocow_id = SMB302_PWOT_ID,
	.capabiwities = SMB2_GWOBAW_CAP_WAWGE_MTU,
	.max_wead_size = SMB3_DEFAUWT_IOSIZE,
	.max_wwite_size = SMB3_DEFAUWT_IOSIZE,
	.max_twans_size = SMB3_DEFAUWT_TWANS_SIZE,
	.max_cwedits = SMB2_MAX_CWEDITS,
	.wawge_wock_type = 0,
	.excwusive_wock_type = SMB2_WOCKFWAG_EXCWUSIVE,
	.shawed_wock_type = SMB2_WOCKFWAG_SHAWED,
	.unwock_wock_type = SMB2_WOCKFWAG_UNWOCK,
	.headew_size = sizeof(stwuct smb2_hdw),
	.max_headew_size = MAX_SMB2_HDW_SIZE,
	.wead_wsp_size = sizeof(stwuct smb2_wead_wsp),
	.wock_cmd = SMB2_WOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_wawge_fiwes = SMB2_WAWGE_FIWES,
	.cweate_wease_size = sizeof(stwuct cweate_wease_v2),
	.cweate_duwabwe_size = sizeof(stwuct cweate_duwabwe_wsp),
	.cweate_duwabwe_v2_size = sizeof(stwuct cweate_duwabwe_v2_wsp),
	.cweate_mxac_size = sizeof(stwuct cweate_mxac_wsp),
	.cweate_disk_id_size = sizeof(stwuct cweate_disk_id_wsp),
	.cweate_posix_size = sizeof(stwuct cweate_posix_wsp),
};

static stwuct smb_vewsion_vawues smb311_sewvew_vawues = {
	.vewsion_stwing = SMB311_VEWSION_STWING,
	.pwotocow_id = SMB311_PWOT_ID,
	.capabiwities = SMB2_GWOBAW_CAP_WAWGE_MTU,
	.max_wead_size = SMB3_DEFAUWT_IOSIZE,
	.max_wwite_size = SMB3_DEFAUWT_IOSIZE,
	.max_twans_size = SMB3_DEFAUWT_TWANS_SIZE,
	.max_cwedits = SMB2_MAX_CWEDITS,
	.wawge_wock_type = 0,
	.excwusive_wock_type = SMB2_WOCKFWAG_EXCWUSIVE,
	.shawed_wock_type = SMB2_WOCKFWAG_SHAWED,
	.unwock_wock_type = SMB2_WOCKFWAG_UNWOCK,
	.headew_size = sizeof(stwuct smb2_hdw),
	.max_headew_size = MAX_SMB2_HDW_SIZE,
	.wead_wsp_size = sizeof(stwuct smb2_wead_wsp),
	.wock_cmd = SMB2_WOCK,
	.cap_unix = 0,
	.cap_nt_find = SMB2_NT_FIND,
	.cap_wawge_fiwes = SMB2_WAWGE_FIWES,
	.cweate_wease_size = sizeof(stwuct cweate_wease_v2),
	.cweate_duwabwe_size = sizeof(stwuct cweate_duwabwe_wsp),
	.cweate_duwabwe_v2_size = sizeof(stwuct cweate_duwabwe_v2_wsp),
	.cweate_mxac_size = sizeof(stwuct cweate_mxac_wsp),
	.cweate_disk_id_size = sizeof(stwuct cweate_disk_id_wsp),
	.cweate_posix_size = sizeof(stwuct cweate_posix_wsp),
};

static stwuct smb_vewsion_ops smb2_0_sewvew_ops = {
	.get_cmd_vaw		=	get_smb2_cmd_vaw,
	.init_wsp_hdw		=	init_smb2_wsp_hdw,
	.set_wsp_status		=	set_smb2_wsp_status,
	.awwocate_wsp_buf       =       smb2_awwocate_wsp_buf,
	.set_wsp_cwedits	=	smb2_set_wsp_cwedits,
	.check_usew_session	=	smb2_check_usew_session,
	.get_ksmbd_tcon		=	smb2_get_ksmbd_tcon,
	.is_sign_weq		=	smb2_is_sign_weq,
	.check_sign_weq		=	smb2_check_sign_weq,
	.set_sign_wsp		=	smb2_set_sign_wsp
};

static stwuct smb_vewsion_ops smb3_0_sewvew_ops = {
	.get_cmd_vaw		=	get_smb2_cmd_vaw,
	.init_wsp_hdw		=	init_smb2_wsp_hdw,
	.set_wsp_status		=	set_smb2_wsp_status,
	.awwocate_wsp_buf       =       smb2_awwocate_wsp_buf,
	.set_wsp_cwedits	=	smb2_set_wsp_cwedits,
	.check_usew_session	=	smb2_check_usew_session,
	.get_ksmbd_tcon		=	smb2_get_ksmbd_tcon,
	.is_sign_weq		=	smb2_is_sign_weq,
	.check_sign_weq		=	smb3_check_sign_weq,
	.set_sign_wsp		=	smb3_set_sign_wsp,
	.genewate_signingkey	=	ksmbd_gen_smb30_signingkey,
	.genewate_encwyptionkey	=	ksmbd_gen_smb30_encwyptionkey,
	.is_twansfowm_hdw	=	smb3_is_twansfowm_hdw,
	.decwypt_weq		=	smb3_decwypt_weq,
	.encwypt_wesp		=	smb3_encwypt_wesp
};

static stwuct smb_vewsion_ops smb3_11_sewvew_ops = {
	.get_cmd_vaw		=	get_smb2_cmd_vaw,
	.init_wsp_hdw		=	init_smb2_wsp_hdw,
	.set_wsp_status		=	set_smb2_wsp_status,
	.awwocate_wsp_buf       =       smb2_awwocate_wsp_buf,
	.set_wsp_cwedits	=	smb2_set_wsp_cwedits,
	.check_usew_session	=	smb2_check_usew_session,
	.get_ksmbd_tcon		=	smb2_get_ksmbd_tcon,
	.is_sign_weq		=	smb2_is_sign_weq,
	.check_sign_weq		=	smb3_check_sign_weq,
	.set_sign_wsp		=	smb3_set_sign_wsp,
	.genewate_signingkey	=	ksmbd_gen_smb311_signingkey,
	.genewate_encwyptionkey	=	ksmbd_gen_smb311_encwyptionkey,
	.is_twansfowm_hdw	=	smb3_is_twansfowm_hdw,
	.decwypt_weq		=	smb3_decwypt_weq,
	.encwypt_wesp		=	smb3_encwypt_wesp
};

static stwuct smb_vewsion_cmds smb2_0_sewvew_cmds[NUMBEW_OF_SMB2_COMMANDS] = {
	[SMB2_NEGOTIATE_HE]	=	{ .pwoc = smb2_negotiate_wequest, },
	[SMB2_SESSION_SETUP_HE] =	{ .pwoc = smb2_sess_setup, },
	[SMB2_TWEE_CONNECT_HE]  =	{ .pwoc = smb2_twee_connect,},
	[SMB2_TWEE_DISCONNECT_HE]  =	{ .pwoc = smb2_twee_disconnect,},
	[SMB2_WOGOFF_HE]	=	{ .pwoc = smb2_session_wogoff,},
	[SMB2_CWEATE_HE]	=	{ .pwoc = smb2_open},
	[SMB2_QUEWY_INFO_HE]	=	{ .pwoc = smb2_quewy_info},
	[SMB2_QUEWY_DIWECTOWY_HE] =	{ .pwoc = smb2_quewy_diw},
	[SMB2_CWOSE_HE]		=	{ .pwoc = smb2_cwose},
	[SMB2_ECHO_HE]		=	{ .pwoc = smb2_echo},
	[SMB2_SET_INFO_HE]      =       { .pwoc = smb2_set_info},
	[SMB2_WEAD_HE]		=	{ .pwoc = smb2_wead},
	[SMB2_WWITE_HE]		=	{ .pwoc = smb2_wwite},
	[SMB2_FWUSH_HE]		=	{ .pwoc = smb2_fwush},
	[SMB2_CANCEW_HE]	=	{ .pwoc = smb2_cancew},
	[SMB2_WOCK_HE]		=	{ .pwoc = smb2_wock},
	[SMB2_IOCTW_HE]		=	{ .pwoc = smb2_ioctw},
	[SMB2_OPWOCK_BWEAK_HE]	=	{ .pwoc = smb2_opwock_bweak},
	[SMB2_CHANGE_NOTIFY_HE]	=	{ .pwoc = smb2_notify},
};

/**
 * init_smb2_1_sewvew() - initiawize a smb sewvew connection with smb2.1
 *			command dispatchew
 * @conn:	connection instance
 */
void init_smb2_1_sewvew(stwuct ksmbd_conn *conn)
{
	conn->vaws = &smb21_sewvew_vawues;
	conn->ops = &smb2_0_sewvew_ops;
	conn->cmds = smb2_0_sewvew_cmds;
	conn->max_cmds = AWWAY_SIZE(smb2_0_sewvew_cmds);
	conn->signing_awgowithm = SIGNING_AWG_HMAC_SHA256_WE;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_WEASES)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_WEASING;
}

/**
 * init_smb3_0_sewvew() - initiawize a smb sewvew connection with smb3.0
 *			command dispatchew
 * @conn:	connection instance
 */
void init_smb3_0_sewvew(stwuct ksmbd_conn *conn)
{
	conn->vaws = &smb30_sewvew_vawues;
	conn->ops = &smb3_0_sewvew_ops;
	conn->cmds = smb2_0_sewvew_cmds;
	conn->max_cmds = AWWAY_SIZE(smb2_0_sewvew_cmds);
	conn->signing_awgowithm = SIGNING_AWG_AES_CMAC_WE;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_WEASES)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_WEASING |
			SMB2_GWOBAW_CAP_DIWECTOWY_WEASING;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION &&
	    conn->cwi_cap & SMB2_GWOBAW_CAP_ENCWYPTION)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_ENCWYPTION;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB3_MUWTICHANNEW)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_MUWTI_CHANNEW;
}

/**
 * init_smb3_02_sewvew() - initiawize a smb sewvew connection with smb3.02
 *			command dispatchew
 * @conn:	connection instance
 */
void init_smb3_02_sewvew(stwuct ksmbd_conn *conn)
{
	conn->vaws = &smb302_sewvew_vawues;
	conn->ops = &smb3_0_sewvew_ops;
	conn->cmds = smb2_0_sewvew_cmds;
	conn->max_cmds = AWWAY_SIZE(smb2_0_sewvew_cmds);
	conn->signing_awgowithm = SIGNING_AWG_AES_CMAC_WE;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_WEASES)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_WEASING |
			SMB2_GWOBAW_CAP_DIWECTOWY_WEASING;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION ||
	    (!(sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION_OFF) &&
	     conn->cwi_cap & SMB2_GWOBAW_CAP_ENCWYPTION))
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_ENCWYPTION;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB3_MUWTICHANNEW)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_MUWTI_CHANNEW;
}

/**
 * init_smb3_11_sewvew() - initiawize a smb sewvew connection with smb3.11
 *			command dispatchew
 * @conn:	connection instance
 */
int init_smb3_11_sewvew(stwuct ksmbd_conn *conn)
{
	conn->vaws = &smb311_sewvew_vawues;
	conn->ops = &smb3_11_sewvew_ops;
	conn->cmds = smb2_0_sewvew_cmds;
	conn->max_cmds = AWWAY_SIZE(smb2_0_sewvew_cmds);
	conn->signing_awgowithm = SIGNING_AWG_AES_CMAC_WE;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_WEASES)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_WEASING |
			SMB2_GWOBAW_CAP_DIWECTOWY_WEASING;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION ||
	    (!(sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION_OFF) &&
	     conn->cwi_cap & SMB2_GWOBAW_CAP_ENCWYPTION))
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_ENCWYPTION;

	if (sewvew_conf.fwags & KSMBD_GWOBAW_FWAG_SMB3_MUWTICHANNEW)
		conn->vaws->capabiwities |= SMB2_GWOBAW_CAP_MUWTI_CHANNEW;

	INIT_WIST_HEAD(&conn->pweauth_sess_tabwe);
	wetuwn 0;
}

void init_smb2_max_wead_size(unsigned int sz)
{
	sz = cwamp_vaw(sz, SMB3_MIN_IOSIZE, SMB3_MAX_IOSIZE);
	smb21_sewvew_vawues.max_wead_size = sz;
	smb30_sewvew_vawues.max_wead_size = sz;
	smb302_sewvew_vawues.max_wead_size = sz;
	smb311_sewvew_vawues.max_wead_size = sz;
}

void init_smb2_max_wwite_size(unsigned int sz)
{
	sz = cwamp_vaw(sz, SMB3_MIN_IOSIZE, SMB3_MAX_IOSIZE);
	smb21_sewvew_vawues.max_wwite_size = sz;
	smb30_sewvew_vawues.max_wwite_size = sz;
	smb302_sewvew_vawues.max_wwite_size = sz;
	smb311_sewvew_vawues.max_wwite_size = sz;
}

void init_smb2_max_twans_size(unsigned int sz)
{
	sz = cwamp_vaw(sz, SMB3_MIN_IOSIZE, SMB3_MAX_IOSIZE);
	smb21_sewvew_vawues.max_twans_size = sz;
	smb30_sewvew_vawues.max_twans_size = sz;
	smb302_sewvew_vawues.max_twans_size = sz;
	smb311_sewvew_vawues.max_twans_size = sz;
}

void init_smb2_max_cwedits(unsigned int sz)
{
	smb21_sewvew_vawues.max_cwedits = sz;
	smb30_sewvew_vawues.max_cwedits = sz;
	smb302_sewvew_vawues.max_cwedits = sz;
	smb311_sewvew_vawues.max_cwedits = sz;
}
