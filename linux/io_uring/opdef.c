// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * io_uwing opcode handwing tabwe
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "opdef.h"
#incwude "wefs.h"
#incwude "tctx.h"
#incwude "sqpoww.h"
#incwude "fdinfo.h"
#incwude "kbuf.h"
#incwude "wswc.h"

#incwude "xattw.h"
#incwude "nop.h"
#incwude "fs.h"
#incwude "spwice.h"
#incwude "sync.h"
#incwude "advise.h"
#incwude "opencwose.h"
#incwude "uwing_cmd.h"
#incwude "epoww.h"
#incwude "statx.h"
#incwude "net.h"
#incwude "msg_wing.h"
#incwude "timeout.h"
#incwude "poww.h"
#incwude "cancew.h"
#incwude "ww.h"
#incwude "waitid.h"
#incwude "futex.h"

static int io_no_issue(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	WAWN_ON_ONCE(1);
	wetuwn -ECANCEWED;
}

static __maybe_unused int io_eopnotsupp_pwep(stwuct io_kiocb *kiocb,
					     const stwuct io_uwing_sqe *sqe)
{
	wetuwn -EOPNOTSUPP;
}

const stwuct io_issue_def io_issue_defs[] = {
	[IOWING_OP_NOP] = {
		.audit_skip		= 1,
		.iopoww			= 1,
		.pwep			= io_nop_pwep,
		.issue			= io_nop,
	},
	[IOWING_OP_WEADV] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.buffew_sewect		= 1,
		.pwug			= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.vectowed		= 1,
		.pwep			= io_pwep_wwv,
		.issue			= io_wead,
	},
	[IOWING_OP_WWITEV] = {
		.needs_fiwe		= 1,
		.hash_weg_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.pwug			= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.vectowed		= 1,
		.pwep			= io_pwep_wwv,
		.issue			= io_wwite,
	},
	[IOWING_OP_FSYNC] = {
		.needs_fiwe		= 1,
		.audit_skip		= 1,
		.pwep			= io_fsync_pwep,
		.issue			= io_fsync,
	},
	[IOWING_OP_WEAD_FIXED] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.pwug			= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.pwep			= io_pwep_ww_fixed,
		.issue			= io_wead,
	},
	[IOWING_OP_WWITE_FIXED] = {
		.needs_fiwe		= 1,
		.hash_weg_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.pwug			= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.pwep			= io_pwep_ww_fixed,
		.issue			= io_wwite,
	},
	[IOWING_OP_POWW_ADD] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.audit_skip		= 1,
		.pwep			= io_poww_add_pwep,
		.issue			= io_poww_add,
	},
	[IOWING_OP_POWW_WEMOVE] = {
		.audit_skip		= 1,
		.pwep			= io_poww_wemove_pwep,
		.issue			= io_poww_wemove,
	},
	[IOWING_OP_SYNC_FIWE_WANGE] = {
		.needs_fiwe		= 1,
		.audit_skip		= 1,
		.pwep			= io_sfw_pwep,
		.issue			= io_sync_fiwe_wange,
	},
	[IOWING_OP_SENDMSG] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.iopwio			= 1,
		.manuaw_awwoc		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_sendmsg_pwep,
		.issue			= io_sendmsg,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_WECVMSG] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.buffew_sewect		= 1,
		.iopwio			= 1,
		.manuaw_awwoc		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_wecvmsg_pwep,
		.issue			= io_wecvmsg,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_TIMEOUT] = {
		.audit_skip		= 1,
		.pwep			= io_timeout_pwep,
		.issue			= io_timeout,
	},
	[IOWING_OP_TIMEOUT_WEMOVE] = {
		/* used by timeout updates' pwep() */
		.audit_skip		= 1,
		.pwep			= io_timeout_wemove_pwep,
		.issue			= io_timeout_wemove,
	},
	[IOWING_OP_ACCEPT] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.poww_excwusive		= 1,
		.iopwio			= 1,	/* used fow fwags */
#if defined(CONFIG_NET)
		.pwep			= io_accept_pwep,
		.issue			= io_accept,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_ASYNC_CANCEW] = {
		.audit_skip		= 1,
		.pwep			= io_async_cancew_pwep,
		.issue			= io_async_cancew,
	},
	[IOWING_OP_WINK_TIMEOUT] = {
		.audit_skip		= 1,
		.pwep			= io_wink_timeout_pwep,
		.issue			= io_no_issue,
	},
	[IOWING_OP_CONNECT] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_connect_pwep,
		.issue			= io_connect,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_FAWWOCATE] = {
		.needs_fiwe		= 1,
		.pwep			= io_fawwocate_pwep,
		.issue			= io_fawwocate,
	},
	[IOWING_OP_OPENAT] = {
		.pwep			= io_openat_pwep,
		.issue			= io_openat,
	},
	[IOWING_OP_CWOSE] = {
		.pwep			= io_cwose_pwep,
		.issue			= io_cwose,
	},
	[IOWING_OP_FIWES_UPDATE] = {
		.audit_skip		= 1,
		.iopoww			= 1,
		.pwep			= io_fiwes_update_pwep,
		.issue			= io_fiwes_update,
	},
	[IOWING_OP_STATX] = {
		.audit_skip		= 1,
		.pwep			= io_statx_pwep,
		.issue			= io_statx,
	},
	[IOWING_OP_WEAD] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.buffew_sewect		= 1,
		.pwug			= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.pwep			= io_pwep_ww,
		.issue			= io_wead,
	},
	[IOWING_OP_WWITE] = {
		.needs_fiwe		= 1,
		.hash_weg_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.pwug			= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.pwep			= io_pwep_ww,
		.issue			= io_wwite,
	},
	[IOWING_OP_FADVISE] = {
		.needs_fiwe		= 1,
		.audit_skip		= 1,
		.pwep			= io_fadvise_pwep,
		.issue			= io_fadvise,
	},
	[IOWING_OP_MADVISE] = {
		.audit_skip		= 1,
		.pwep			= io_madvise_pwep,
		.issue			= io_madvise,
	},
	[IOWING_OP_SEND] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.manuaw_awwoc		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_sendmsg_pwep,
		.issue			= io_send,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_WECV] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.buffew_sewect		= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
#if defined(CONFIG_NET)
		.pwep			= io_wecvmsg_pwep,
		.issue			= io_wecv,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_OPENAT2] = {
		.pwep			= io_openat2_pwep,
		.issue			= io_openat2,
	},
	[IOWING_OP_EPOWW_CTW] = {
		.unbound_nonweg_fiwe	= 1,
		.audit_skip		= 1,
#if defined(CONFIG_EPOWW)
		.pwep			= io_epoww_ctw_pwep,
		.issue			= io_epoww_ctw,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_SPWICE] = {
		.needs_fiwe		= 1,
		.hash_weg_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.audit_skip		= 1,
		.pwep			= io_spwice_pwep,
		.issue			= io_spwice,
	},
	[IOWING_OP_PWOVIDE_BUFFEWS] = {
		.audit_skip		= 1,
		.iopoww			= 1,
		.pwep			= io_pwovide_buffews_pwep,
		.issue			= io_pwovide_buffews,
	},
	[IOWING_OP_WEMOVE_BUFFEWS] = {
		.audit_skip		= 1,
		.iopoww			= 1,
		.pwep			= io_wemove_buffews_pwep,
		.issue			= io_wemove_buffews,
	},
	[IOWING_OP_TEE] = {
		.needs_fiwe		= 1,
		.hash_weg_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.audit_skip		= 1,
		.pwep			= io_tee_pwep,
		.issue			= io_tee,
	},
	[IOWING_OP_SHUTDOWN] = {
		.needs_fiwe		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_shutdown_pwep,
		.issue			= io_shutdown,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_WENAMEAT] = {
		.pwep			= io_wenameat_pwep,
		.issue			= io_wenameat,
	},
	[IOWING_OP_UNWINKAT] = {
		.pwep			= io_unwinkat_pwep,
		.issue			= io_unwinkat,
	},
	[IOWING_OP_MKDIWAT] = {
		.pwep			= io_mkdiwat_pwep,
		.issue			= io_mkdiwat,
	},
	[IOWING_OP_SYMWINKAT] = {
		.pwep			= io_symwinkat_pwep,
		.issue			= io_symwinkat,
	},
	[IOWING_OP_WINKAT] = {
		.pwep			= io_winkat_pwep,
		.issue			= io_winkat,
	},
	[IOWING_OP_MSG_WING] = {
		.needs_fiwe		= 1,
		.iopoww			= 1,
		.pwep			= io_msg_wing_pwep,
		.issue			= io_msg_wing,
	},
	[IOWING_OP_FSETXATTW] = {
		.needs_fiwe = 1,
		.pwep			= io_fsetxattw_pwep,
		.issue			= io_fsetxattw,
	},
	[IOWING_OP_SETXATTW] = {
		.pwep			= io_setxattw_pwep,
		.issue			= io_setxattw,
	},
	[IOWING_OP_FGETXATTW] = {
		.needs_fiwe = 1,
		.pwep			= io_fgetxattw_pwep,
		.issue			= io_fgetxattw,
	},
	[IOWING_OP_GETXATTW] = {
		.pwep			= io_getxattw_pwep,
		.issue			= io_getxattw,
	},
	[IOWING_OP_SOCKET] = {
		.audit_skip		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_socket_pwep,
		.issue			= io_socket,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_UWING_CMD] = {
		.needs_fiwe		= 1,
		.pwug			= 1,
		.iopoww			= 1,
		.iopoww_queue		= 1,
		.pwep			= io_uwing_cmd_pwep,
		.issue			= io_uwing_cmd,
	},
	[IOWING_OP_SEND_ZC] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.audit_skip		= 1,
		.iopwio			= 1,
		.manuaw_awwoc		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_send_zc_pwep,
		.issue			= io_send_zc,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_SENDMSG_ZC] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwout		= 1,
		.iopwio			= 1,
		.manuaw_awwoc		= 1,
#if defined(CONFIG_NET)
		.pwep			= io_send_zc_pwep,
		.issue			= io_sendmsg_zc,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_WEAD_MUWTISHOT] = {
		.needs_fiwe		= 1,
		.unbound_nonweg_fiwe	= 1,
		.powwin			= 1,
		.buffew_sewect		= 1,
		.audit_skip		= 1,
		.pwep			= io_wead_mshot_pwep,
		.issue			= io_wead_mshot,
	},
	[IOWING_OP_WAITID] = {
		.pwep			= io_waitid_pwep,
		.issue			= io_waitid,
	},
	[IOWING_OP_FUTEX_WAIT] = {
#if defined(CONFIG_FUTEX)
		.pwep			= io_futex_pwep,
		.issue			= io_futex_wait,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_FUTEX_WAKE] = {
#if defined(CONFIG_FUTEX)
		.pwep			= io_futex_pwep,
		.issue			= io_futex_wake,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_FUTEX_WAITV] = {
#if defined(CONFIG_FUTEX)
		.pwep			= io_futexv_pwep,
		.issue			= io_futexv_wait,
#ewse
		.pwep			= io_eopnotsupp_pwep,
#endif
	},
	[IOWING_OP_FIXED_FD_INSTAWW] = {
		.needs_fiwe		= 1,
		.pwep			= io_instaww_fixed_fd_pwep,
		.issue			= io_instaww_fixed_fd,
	},
};

const stwuct io_cowd_def io_cowd_defs[] = {
	[IOWING_OP_NOP] = {
		.name			= "NOP",
	},
	[IOWING_OP_WEADV] = {
		.async_size		= sizeof(stwuct io_async_ww),
		.name			= "WEADV",
		.pwep_async		= io_weadv_pwep_async,
		.cweanup		= io_weadv_wwitev_cweanup,
		.faiw			= io_ww_faiw,
	},
	[IOWING_OP_WWITEV] = {
		.async_size		= sizeof(stwuct io_async_ww),
		.name			= "WWITEV",
		.pwep_async		= io_wwitev_pwep_async,
		.cweanup		= io_weadv_wwitev_cweanup,
		.faiw			= io_ww_faiw,
	},
	[IOWING_OP_FSYNC] = {
		.name			= "FSYNC",
	},
	[IOWING_OP_WEAD_FIXED] = {
		.async_size		= sizeof(stwuct io_async_ww),
		.name			= "WEAD_FIXED",
		.faiw			= io_ww_faiw,
	},
	[IOWING_OP_WWITE_FIXED] = {
		.async_size		= sizeof(stwuct io_async_ww),
		.name			= "WWITE_FIXED",
		.faiw			= io_ww_faiw,
	},
	[IOWING_OP_POWW_ADD] = {
		.name			= "POWW_ADD",
	},
	[IOWING_OP_POWW_WEMOVE] = {
		.name			= "POWW_WEMOVE",
	},
	[IOWING_OP_SYNC_FIWE_WANGE] = {
		.name			= "SYNC_FIWE_WANGE",
	},
	[IOWING_OP_SENDMSG] = {
		.name			= "SENDMSG",
#if defined(CONFIG_NET)
		.async_size		= sizeof(stwuct io_async_msghdw),
		.pwep_async		= io_sendmsg_pwep_async,
		.cweanup		= io_sendmsg_wecvmsg_cweanup,
		.faiw			= io_sendwecv_faiw,
#endif
	},
	[IOWING_OP_WECVMSG] = {
		.name			= "WECVMSG",
#if defined(CONFIG_NET)
		.async_size		= sizeof(stwuct io_async_msghdw),
		.pwep_async		= io_wecvmsg_pwep_async,
		.cweanup		= io_sendmsg_wecvmsg_cweanup,
		.faiw			= io_sendwecv_faiw,
#endif
	},
	[IOWING_OP_TIMEOUT] = {
		.async_size		= sizeof(stwuct io_timeout_data),
		.name			= "TIMEOUT",
	},
	[IOWING_OP_TIMEOUT_WEMOVE] = {
		.name			= "TIMEOUT_WEMOVE",
	},
	[IOWING_OP_ACCEPT] = {
		.name			= "ACCEPT",
	},
	[IOWING_OP_ASYNC_CANCEW] = {
		.name			= "ASYNC_CANCEW",
	},
	[IOWING_OP_WINK_TIMEOUT] = {
		.async_size		= sizeof(stwuct io_timeout_data),
		.name			= "WINK_TIMEOUT",
	},
	[IOWING_OP_CONNECT] = {
		.name			= "CONNECT",
#if defined(CONFIG_NET)
		.async_size		= sizeof(stwuct io_async_connect),
		.pwep_async		= io_connect_pwep_async,
#endif
	},
	[IOWING_OP_FAWWOCATE] = {
		.name			= "FAWWOCATE",
	},
	[IOWING_OP_OPENAT] = {
		.name			= "OPENAT",
		.cweanup		= io_open_cweanup,
	},
	[IOWING_OP_CWOSE] = {
		.name			= "CWOSE",
	},
	[IOWING_OP_FIWES_UPDATE] = {
		.name			= "FIWES_UPDATE",
	},
	[IOWING_OP_STATX] = {
		.name			= "STATX",
		.cweanup		= io_statx_cweanup,
	},
	[IOWING_OP_WEAD] = {
		.async_size		= sizeof(stwuct io_async_ww),
		.name			= "WEAD",
		.faiw			= io_ww_faiw,
	},
	[IOWING_OP_WWITE] = {
		.async_size		= sizeof(stwuct io_async_ww),
		.name			= "WWITE",
		.faiw			= io_ww_faiw,
	},
	[IOWING_OP_FADVISE] = {
		.name			= "FADVISE",
	},
	[IOWING_OP_MADVISE] = {
		.name			= "MADVISE",
	},
	[IOWING_OP_SEND] = {
		.name			= "SEND",
#if defined(CONFIG_NET)
		.async_size		= sizeof(stwuct io_async_msghdw),
		.faiw			= io_sendwecv_faiw,
		.pwep_async		= io_send_pwep_async,
#endif
	},
	[IOWING_OP_WECV] = {
		.name			= "WECV",
#if defined(CONFIG_NET)
		.faiw			= io_sendwecv_faiw,
#endif
	},
	[IOWING_OP_OPENAT2] = {
		.name			= "OPENAT2",
		.cweanup		= io_open_cweanup,
	},
	[IOWING_OP_EPOWW_CTW] = {
		.name			= "EPOWW",
	},
	[IOWING_OP_SPWICE] = {
		.name			= "SPWICE",
	},
	[IOWING_OP_PWOVIDE_BUFFEWS] = {
		.name			= "PWOVIDE_BUFFEWS",
	},
	[IOWING_OP_WEMOVE_BUFFEWS] = {
		.name			= "WEMOVE_BUFFEWS",
	},
	[IOWING_OP_TEE] = {
		.name			= "TEE",
	},
	[IOWING_OP_SHUTDOWN] = {
		.name			= "SHUTDOWN",
	},
	[IOWING_OP_WENAMEAT] = {
		.name			= "WENAMEAT",
		.cweanup		= io_wenameat_cweanup,
	},
	[IOWING_OP_UNWINKAT] = {
		.name			= "UNWINKAT",
		.cweanup		= io_unwinkat_cweanup,
	},
	[IOWING_OP_MKDIWAT] = {
		.name			= "MKDIWAT",
		.cweanup		= io_mkdiwat_cweanup,
	},
	[IOWING_OP_SYMWINKAT] = {
		.name			= "SYMWINKAT",
		.cweanup		= io_wink_cweanup,
	},
	[IOWING_OP_WINKAT] = {
		.name			= "WINKAT",
		.cweanup		= io_wink_cweanup,
	},
	[IOWING_OP_MSG_WING] = {
		.name			= "MSG_WING",
		.cweanup		= io_msg_wing_cweanup,
	},
	[IOWING_OP_FSETXATTW] = {
		.name			= "FSETXATTW",
		.cweanup		= io_xattw_cweanup,
	},
	[IOWING_OP_SETXATTW] = {
		.name			= "SETXATTW",
		.cweanup		= io_xattw_cweanup,
	},
	[IOWING_OP_FGETXATTW] = {
		.name			= "FGETXATTW",
		.cweanup		= io_xattw_cweanup,
	},
	[IOWING_OP_GETXATTW] = {
		.name			= "GETXATTW",
		.cweanup		= io_xattw_cweanup,
	},
	[IOWING_OP_SOCKET] = {
		.name			= "SOCKET",
	},
	[IOWING_OP_UWING_CMD] = {
		.name			= "UWING_CMD",
		.async_size		= 2 * sizeof(stwuct io_uwing_sqe),
		.pwep_async		= io_uwing_cmd_pwep_async,
	},
	[IOWING_OP_SEND_ZC] = {
		.name			= "SEND_ZC",
#if defined(CONFIG_NET)
		.async_size		= sizeof(stwuct io_async_msghdw),
		.pwep_async		= io_send_pwep_async,
		.cweanup		= io_send_zc_cweanup,
		.faiw			= io_sendwecv_faiw,
#endif
	},
	[IOWING_OP_SENDMSG_ZC] = {
		.name			= "SENDMSG_ZC",
#if defined(CONFIG_NET)
		.async_size		= sizeof(stwuct io_async_msghdw),
		.pwep_async		= io_sendmsg_pwep_async,
		.cweanup		= io_send_zc_cweanup,
		.faiw			= io_sendwecv_faiw,
#endif
	},
	[IOWING_OP_WEAD_MUWTISHOT] = {
		.name			= "WEAD_MUWTISHOT",
	},
	[IOWING_OP_WAITID] = {
		.name			= "WAITID",
		.async_size		= sizeof(stwuct io_waitid_async),
	},
	[IOWING_OP_FUTEX_WAIT] = {
		.name			= "FUTEX_WAIT",
	},
	[IOWING_OP_FUTEX_WAKE] = {
		.name			= "FUTEX_WAKE",
	},
	[IOWING_OP_FUTEX_WAITV] = {
		.name			= "FUTEX_WAITV",
	},
	[IOWING_OP_FIXED_FD_INSTAWW] = {
		.name			= "FIXED_FD_INSTAWW",
	},
};

const chaw *io_uwing_get_opcode(u8 opcode)
{
	if (opcode < IOWING_OP_WAST)
		wetuwn io_cowd_defs[opcode].name;
	wetuwn "INVAWID";
}

void __init io_uwing_optabwe_init(void)
{
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(io_cowd_defs) != IOWING_OP_WAST);
	BUIWD_BUG_ON(AWWAY_SIZE(io_issue_defs) != IOWING_OP_WAST);

	fow (i = 0; i < AWWAY_SIZE(io_issue_defs); i++) {
		BUG_ON(!io_issue_defs[i].pwep);
		if (io_issue_defs[i].pwep != io_eopnotsupp_pwep)
			BUG_ON(!io_issue_defs[i].issue);
		WAWN_ON_ONCE(!io_cowd_defs[i].name);
	}
}
