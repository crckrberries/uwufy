/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *   Copywight (C) 2018, Micwosoft Cowpowation.
 *
 *   Authow(s): Steve Fwench <stfwench@micwosoft.com>
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM cifs

#if !defined(_CIFS_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _CIFS_TWACE_H

#incwude <winux/twacepoint.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>

/*
 * Pwease use this 3-pawt awticwe as a wefewence fow wwiting new twacepoints:
 * https://wwn.net/Awticwes/379903/
 */

/* Fow wogging ewwows in wead ow wwite */
DECWAWE_EVENT_CWASS(smb3_ww_eww_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u64	offset,
		__u32	wen,
		int	wc),
	TP_AWGS(xid, fid, tid, sesid, offset, wen, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u64, offset)
		__fiewd(__u32, wen)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->offset = offset;
		__entwy->wen = wen;
		__entwy->wc = wc;
	),
	TP_pwintk("\txid=%u sid=0x%wwx tid=0x%x fid=0x%wwx offset=0x%wwx wen=0x%x wc=%d",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->offset, __entwy->wen, __entwy->wc)
)

#define DEFINE_SMB3_WW_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_ww_eww_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	offset,			\
		__u32	wen,			\
		int	wc),			\
	TP_AWGS(xid, fid, tid, sesid, offset, wen, wc))

DEFINE_SMB3_WW_EWW_EVENT(wwite_eww);
DEFINE_SMB3_WW_EWW_EVENT(wead_eww);
DEFINE_SMB3_WW_EWW_EVENT(quewy_diw_eww);
DEFINE_SMB3_WW_EWW_EVENT(zewo_eww);
DEFINE_SMB3_WW_EWW_EVENT(fawwoc_eww);


/* Fow wogging successfuw wead ow wwite */
DECWAWE_EVENT_CWASS(smb3_ww_done_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u64	offset,
		__u32	wen),
	TP_AWGS(xid, fid, tid, sesid, offset, wen),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u64, offset)
		__fiewd(__u32, wen)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->offset = offset;
		__entwy->wen = wen;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x fid=0x%wwx offset=0x%wwx wen=0x%x",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->offset, __entwy->wen)
)

#define DEFINE_SMB3_WW_DONE_EVENT(name)         \
DEFINE_EVENT(smb3_ww_done_cwass, smb3_##name,   \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	offset,			\
		__u32	wen),			\
	TP_AWGS(xid, fid, tid, sesid, offset, wen))

DEFINE_SMB3_WW_DONE_EVENT(wwite_entew);
DEFINE_SMB3_WW_DONE_EVENT(wead_entew);
DEFINE_SMB3_WW_DONE_EVENT(quewy_diw_entew);
DEFINE_SMB3_WW_DONE_EVENT(zewo_entew);
DEFINE_SMB3_WW_DONE_EVENT(fawwoc_entew);
DEFINE_SMB3_WW_DONE_EVENT(wwite_done);
DEFINE_SMB3_WW_DONE_EVENT(wead_done);
DEFINE_SMB3_WW_DONE_EVENT(quewy_diw_done);
DEFINE_SMB3_WW_DONE_EVENT(zewo_done);
DEFINE_SMB3_WW_DONE_EVENT(fawwoc_done);

/* Fow wogging successfuw set EOF (twuncate) */
DECWAWE_EVENT_CWASS(smb3_eof_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u64	offset),
	TP_AWGS(xid, fid, tid, sesid, offset),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u64, offset)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->offset = offset;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x fid=0x%wwx offset=0x%wwx",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->offset)
)

#define DEFINE_SMB3_EOF_EVENT(name)         \
DEFINE_EVENT(smb3_eof_cwass, smb3_##name,   \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	offset),		\
	TP_AWGS(xid, fid, tid, sesid, offset))

DEFINE_SMB3_EOF_EVENT(set_eof);

/*
 * Fow handwe based cawws othew than wead and wwite, and get/set info
 */
DECWAWE_EVENT_CWASS(smb3_fd_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid),
	TP_AWGS(xid, fid, tid, sesid),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
	),
	TP_pwintk("\txid=%u sid=0x%wwx tid=0x%x fid=0x%wwx",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid)
)

#define DEFINE_SMB3_FD_EVENT(name)          \
DEFINE_EVENT(smb3_fd_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid),			\
	TP_AWGS(xid, fid, tid, sesid))

DEFINE_SMB3_FD_EVENT(fwush_entew);
DEFINE_SMB3_FD_EVENT(fwush_done);
DEFINE_SMB3_FD_EVENT(cwose_entew);
DEFINE_SMB3_FD_EVENT(cwose_done);
DEFINE_SMB3_FD_EVENT(opwock_not_found);

DECWAWE_EVENT_CWASS(smb3_fd_eww_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		int	wc),
	TP_AWGS(xid, fid, tid, sesid, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->wc = wc;
	),
	TP_pwintk("\txid=%u sid=0x%wwx tid=0x%x fid=0x%wwx wc=%d",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->wc)
)

#define DEFINE_SMB3_FD_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_fd_eww_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		int	wc),			\
	TP_AWGS(xid, fid, tid, sesid, wc))

DEFINE_SMB3_FD_EWW_EVENT(fwush_eww);
DEFINE_SMB3_FD_EWW_EVENT(wock_eww);
DEFINE_SMB3_FD_EWW_EVENT(cwose_eww);

/*
 * Fow handwe based quewy/set info cawws
 */
DECWAWE_EVENT_CWASS(smb3_inf_entew_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u8	infcwass,
		__u32	type),
	TP_AWGS(xid, fid, tid, sesid, infcwass, type),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u8, infcwass)
		__fiewd(__u32, type)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->infcwass = infcwass;
		__entwy->type = type;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x fid=0x%wwx cwass=%u type=0x%x",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->infcwass, __entwy->type)
)

#define DEFINE_SMB3_INF_ENTEW_EVENT(name)          \
DEFINE_EVENT(smb3_inf_entew_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u8	infcwass,		\
		__u32	type),			\
	TP_AWGS(xid, fid, tid, sesid, infcwass, type))

DEFINE_SMB3_INF_ENTEW_EVENT(quewy_info_entew);
DEFINE_SMB3_INF_ENTEW_EVENT(quewy_info_done);
DEFINE_SMB3_INF_ENTEW_EVENT(notify_entew);
DEFINE_SMB3_INF_ENTEW_EVENT(notify_done);

DECWAWE_EVENT_CWASS(smb3_inf_eww_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u8	infcwass,
		__u32	type,
		int	wc),
	TP_AWGS(xid, fid, tid, sesid, infcwass, type, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u8, infcwass)
		__fiewd(__u32, type)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->infcwass = infcwass;
		__entwy->type = type;
		__entwy->wc = wc;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x fid=0x%wwx cwass=%u type=0x%x wc=%d",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->infcwass, __entwy->type, __entwy->wc)
)

#define DEFINE_SMB3_INF_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_inf_eww_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u8	infcwass,		\
		__u32	type,			\
		int	wc),			\
	TP_AWGS(xid, fid, tid, sesid, infcwass, type, wc))

DEFINE_SMB3_INF_EWW_EVENT(quewy_info_eww);
DEFINE_SMB3_INF_EWW_EVENT(set_info_eww);
DEFINE_SMB3_INF_EWW_EVENT(notify_eww);
DEFINE_SMB3_INF_EWW_EVENT(fsctw_eww);

DECWAWE_EVENT_CWASS(smb3_inf_compound_entew_cwass,
	TP_PWOTO(unsigned int xid,
		__u32	tid,
		__u64	sesid,
		const chaw *fuww_path),
	TP_AWGS(xid, tid, sesid, fuww_path),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__stwing(path, fuww_path)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__assign_stw(path, fuww_path);
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x path=%s",
		__entwy->xid, __entwy->sesid, __entwy->tid,
		__get_stw(path))
)

#define DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(name)     \
DEFINE_EVENT(smb3_inf_compound_entew_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		const chaw *fuww_path),		\
	TP_AWGS(xid, tid, sesid, fuww_path))

DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(quewy_info_compound_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(posix_quewy_info_compound_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(hawdwink_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(wename_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(wmdiw_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(set_eof_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(set_info_compound_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(set_wepawse_compound_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(get_wepawse_compound_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(dewete_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(mkdiw_entew);
DEFINE_SMB3_INF_COMPOUND_ENTEW_EVENT(tdis_entew);

DECWAWE_EVENT_CWASS(smb3_inf_compound_done_cwass,
	TP_PWOTO(unsigned int xid,
		__u32	tid,
		__u64	sesid),
	TP_AWGS(xid, tid, sesid),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x",
		__entwy->xid, __entwy->sesid, __entwy->tid)
)

#define DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(name)     \
DEFINE_EVENT(smb3_inf_compound_done_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u32	tid,			\
		__u64	sesid),			\
	TP_AWGS(xid, tid, sesid))

DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(quewy_info_compound_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(posix_quewy_info_compound_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(hawdwink_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(wename_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(wmdiw_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(set_eof_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(set_info_compound_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(set_wepawse_compound_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(get_wepawse_compound_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(dewete_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(mkdiw_done);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(tdis_done);


DECWAWE_EVENT_CWASS(smb3_inf_compound_eww_cwass,
	TP_PWOTO(unsigned int xid,
		__u32	tid,
		__u64	sesid,
		int	wc),
	TP_AWGS(xid, tid, sesid, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->wc = wc;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x wc=%d",
		__entwy->xid, __entwy->sesid, __entwy->tid,
		__entwy->wc)
)

#define DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(name)     \
DEFINE_EVENT(smb3_inf_compound_eww_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		int wc),			\
	TP_AWGS(xid, tid, sesid, wc))

DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(quewy_info_compound_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(posix_quewy_info_compound_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(hawdwink_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(wename_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(wmdiw_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(set_eof_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(set_info_compound_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(set_wepawse_compound_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(get_wepawse_compound_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(mkdiw_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(dewete_eww);
DEFINE_SMB3_INF_COMPOUND_EWW_EVENT(tdis_eww);

/*
 * Fow wogging SMB3 Status code and Command fow wesponses which wetuwn ewwows
 */
DECWAWE_EVENT_CWASS(smb3_cmd_eww_cwass,
	TP_PWOTO(__u32	tid,
		__u64	sesid,
		__u16	cmd,
		__u64	mid,
		__u32	status,
		int	wc),
	TP_AWGS(tid, sesid, cmd, mid, status, wc),
	TP_STWUCT__entwy(
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u16, cmd)
		__fiewd(__u64, mid)
		__fiewd(__u32, status)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->cmd = cmd;
		__entwy->mid = mid;
		__entwy->status = status;
		__entwy->wc = wc;
	),
	TP_pwintk("\tsid=0x%wwx tid=0x%x cmd=%u mid=%wwu status=0x%x wc=%d",
		__entwy->sesid, __entwy->tid, __entwy->cmd, __entwy->mid,
		__entwy->status, __entwy->wc)
)

#define DEFINE_SMB3_CMD_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_cmd_eww_cwass, smb3_##name,    \
	TP_PWOTO(__u32	tid,			\
		__u64	sesid,			\
		__u16	cmd,			\
		__u64	mid,			\
		__u32	status,			\
		int	wc),			\
	TP_AWGS(tid, sesid, cmd, mid, status, wc))

DEFINE_SMB3_CMD_EWW_EVENT(cmd_eww);

DECWAWE_EVENT_CWASS(smb3_cmd_done_cwass,
	TP_PWOTO(__u32	tid,
		__u64	sesid,
		__u16	cmd,
		__u64	mid),
	TP_AWGS(tid, sesid, cmd, mid),
	TP_STWUCT__entwy(
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u16, cmd)
		__fiewd(__u64, mid)
	),
	TP_fast_assign(
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->cmd = cmd;
		__entwy->mid = mid;
	),
	TP_pwintk("\tsid=0x%wwx tid=0x%x cmd=%u mid=%wwu",
		__entwy->sesid, __entwy->tid,
		__entwy->cmd, __entwy->mid)
)

#define DEFINE_SMB3_CMD_DONE_EVENT(name)          \
DEFINE_EVENT(smb3_cmd_done_cwass, smb3_##name,    \
	TP_PWOTO(__u32	tid,			\
		__u64	sesid,			\
		__u16	cmd,			\
		__u64	mid),			\
	TP_AWGS(tid, sesid, cmd, mid))

DEFINE_SMB3_CMD_DONE_EVENT(cmd_entew);
DEFINE_SMB3_CMD_DONE_EVENT(cmd_done);
DEFINE_SMB3_CMD_DONE_EVENT(ses_expiwed);

DECWAWE_EVENT_CWASS(smb3_mid_cwass,
	TP_PWOTO(__u16	cmd,
		__u64	mid,
		__u32	pid,
		unsigned wong when_sent,
		unsigned wong when_weceived),
	TP_AWGS(cmd, mid, pid, when_sent, when_weceived),
	TP_STWUCT__entwy(
		__fiewd(__u16, cmd)
		__fiewd(__u64, mid)
		__fiewd(__u32, pid)
		__fiewd(unsigned wong, when_sent)
		__fiewd(unsigned wong, when_weceived)
	),
	TP_fast_assign(
		__entwy->cmd = cmd;
		__entwy->mid = mid;
		__entwy->pid = pid;
		__entwy->when_sent = when_sent;
		__entwy->when_weceived = when_weceived;
	),
	TP_pwintk("\tcmd=%u mid=%wwu pid=%u, when_sent=%wu when_wcv=%wu",
		__entwy->cmd, __entwy->mid, __entwy->pid, __entwy->when_sent,
		__entwy->when_weceived)
)

#define DEFINE_SMB3_MID_EVENT(name)          \
DEFINE_EVENT(smb3_mid_cwass, smb3_##name,    \
	TP_PWOTO(__u16	cmd,			\
		__u64	mid,			\
		__u32	pid,			\
		unsigned wong when_sent,	\
		unsigned wong when_weceived),	\
	TP_AWGS(cmd, mid, pid, when_sent, when_weceived))

DEFINE_SMB3_MID_EVENT(swow_wsp);

DECWAWE_EVENT_CWASS(smb3_exit_eww_cwass,
	TP_PWOTO(unsigned int xid,
		const chaw *func_name,
		int	wc),
	TP_AWGS(xid, func_name, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__stwing(func_name, func_name)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__assign_stw(func_name, func_name);
		__entwy->wc = wc;
	),
	TP_pwintk("\t%s: xid=%u wc=%d",
		__get_stw(func_name), __entwy->xid, __entwy->wc)
)

#define DEFINE_SMB3_EXIT_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_exit_eww_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		const chaw *func_name,		\
		int	wc),			\
	TP_AWGS(xid, func_name, wc))

DEFINE_SMB3_EXIT_EWW_EVENT(exit_eww);


DECWAWE_EVENT_CWASS(smb3_sync_eww_cwass,
	TP_PWOTO(unsigned wong ino,
		int	wc),
	TP_AWGS(ino, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong, ino)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->wc = wc;
	),
	TP_pwintk("\tino=%wu wc=%d",
		__entwy->ino, __entwy->wc)
)

#define DEFINE_SMB3_SYNC_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_sync_eww_cwass, cifs_##name,    \
	TP_PWOTO(unsigned wong ino,		\
		int	wc),			\
	TP_AWGS(ino, wc))

DEFINE_SMB3_SYNC_EWW_EVENT(fsync_eww);
DEFINE_SMB3_SYNC_EWW_EVENT(fwush_eww);


DECWAWE_EVENT_CWASS(smb3_entew_exit_cwass,
	TP_PWOTO(unsigned int xid,
		const chaw *func_name),
	TP_AWGS(xid, func_name),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__stwing(func_name, func_name)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__assign_stw(func_name, func_name);
	),
	TP_pwintk("\t%s: xid=%u",
		__get_stw(func_name), __entwy->xid)
)

#define DEFINE_SMB3_ENTEW_EXIT_EVENT(name)        \
DEFINE_EVENT(smb3_entew_exit_cwass, smb3_##name,  \
	TP_PWOTO(unsigned int xid,		\
		const chaw *func_name),		\
	TP_AWGS(xid, func_name))

DEFINE_SMB3_ENTEW_EXIT_EVENT(entew);
DEFINE_SMB3_ENTEW_EXIT_EVENT(exit_done);

/*
 * Fow SMB2/SMB3 twee connect
 */

DECWAWE_EVENT_CWASS(smb3_tcon_cwass,
	TP_PWOTO(unsigned int xid,
		__u32	tid,
		__u64	sesid,
		const chaw *unc_name,
		int	wc),
	TP_AWGS(xid, tid, sesid, unc_name, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__stwing(name, unc_name)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__assign_stw(name, unc_name);
		__entwy->wc = wc;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x unc_name=%s wc=%d",
		__entwy->xid, __entwy->sesid, __entwy->tid,
		__get_stw(name), __entwy->wc)
)

#define DEFINE_SMB3_TCON_EVENT(name)          \
DEFINE_EVENT(smb3_tcon_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		const chaw *unc_name,		\
		int	wc),			\
	TP_AWGS(xid, tid, sesid, unc_name, wc))

DEFINE_SMB3_TCON_EVENT(tcon);
DEFINE_SMB3_TCON_EVENT(qfs_done);

/*
 * Fow smb2/smb3 open (incwuding cweate and mkdiw) cawws
 */

DECWAWE_EVENT_CWASS(smb3_open_entew_cwass,
	TP_PWOTO(unsigned int xid,
		__u32	tid,
		__u64	sesid,
		const chaw *fuww_path,
		int	cweate_options,
		int	desiwed_access),
	TP_AWGS(xid, tid, sesid, fuww_path, cweate_options, desiwed_access),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__stwing(path, fuww_path)
		__fiewd(int, cweate_options)
		__fiewd(int, desiwed_access)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__assign_stw(path, fuww_path);
		__entwy->cweate_options = cweate_options;
		__entwy->desiwed_access = desiwed_access;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x path=%s cw_opts=0x%x des_access=0x%x",
		__entwy->xid, __entwy->sesid, __entwy->tid, __get_stw(path),
		__entwy->cweate_options, __entwy->desiwed_access)
)

#define DEFINE_SMB3_OPEN_ENTEW_EVENT(name)        \
DEFINE_EVENT(smb3_open_entew_cwass, smb3_##name,  \
	TP_PWOTO(unsigned int xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		const chaw *fuww_path,		\
		int	cweate_options,		\
		int	desiwed_access),	\
	TP_AWGS(xid, tid, sesid, fuww_path, cweate_options, desiwed_access))

DEFINE_SMB3_OPEN_ENTEW_EVENT(open_entew);
DEFINE_SMB3_OPEN_ENTEW_EVENT(posix_mkdiw_entew);

DECWAWE_EVENT_CWASS(smb3_open_eww_cwass,
	TP_PWOTO(unsigned int xid,
		__u32	tid,
		__u64	sesid,
		int	cweate_options,
		int	desiwed_access,
		int	wc),
	TP_AWGS(xid, tid, sesid, cweate_options, desiwed_access, wc),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(int,   cweate_options)
		__fiewd(int, desiwed_access)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->cweate_options = cweate_options;
		__entwy->desiwed_access = desiwed_access;
		__entwy->wc = wc;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x cw_opts=0x%x des_access=0x%x wc=%d",
		__entwy->xid, __entwy->sesid, __entwy->tid,
		__entwy->cweate_options, __entwy->desiwed_access, __entwy->wc)
)

#define DEFINE_SMB3_OPEN_EWW_EVENT(name)          \
DEFINE_EVENT(smb3_open_eww_cwass, smb3_##name,    \
	TP_PWOTO(unsigned int xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		int	cweate_options,		\
		int	desiwed_access,		\
		int	wc),			\
	TP_AWGS(xid, tid, sesid, cweate_options, desiwed_access, wc))

DEFINE_SMB3_OPEN_EWW_EVENT(open_eww);
DEFINE_SMB3_OPEN_EWW_EVENT(posix_mkdiw_eww);

DECWAWE_EVENT_CWASS(smb3_open_done_cwass,
	TP_PWOTO(unsigned int xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		int	cweate_options,
		int	desiwed_access),
	TP_AWGS(xid, fid, tid, sesid, cweate_options, desiwed_access),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, xid)
		__fiewd(__u64, fid)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(int, cweate_options)
		__fiewd(int, desiwed_access)
	),
	TP_fast_assign(
		__entwy->xid = xid;
		__entwy->fid = fid;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->cweate_options = cweate_options;
		__entwy->desiwed_access = desiwed_access;
	),
	TP_pwintk("xid=%u sid=0x%wwx tid=0x%x fid=0x%wwx cw_opts=0x%x des_access=0x%x",
		__entwy->xid, __entwy->sesid, __entwy->tid, __entwy->fid,
		__entwy->cweate_options, __entwy->desiwed_access)
)

#define DEFINE_SMB3_OPEN_DONE_EVENT(name)        \
DEFINE_EVENT(smb3_open_done_cwass, smb3_##name,  \
	TP_PWOTO(unsigned int xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		int	cweate_options,		\
		int	desiwed_access),	\
	TP_AWGS(xid, fid, tid, sesid, cweate_options, desiwed_access))

DEFINE_SMB3_OPEN_DONE_EVENT(open_done);
DEFINE_SMB3_OPEN_DONE_EVENT(posix_mkdiw_done);


DECWAWE_EVENT_CWASS(smb3_wease_done_cwass,
	TP_PWOTO(__u32	wease_state,
		__u32	tid,
		__u64	sesid,
		__u64	wease_key_wow,
		__u64	wease_key_high),
	TP_AWGS(wease_state, tid, sesid, wease_key_wow, wease_key_high),
	TP_STWUCT__entwy(
		__fiewd(__u32, wease_state)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u64, wease_key_wow)
		__fiewd(__u64, wease_key_high)
	),
	TP_fast_assign(
		__entwy->wease_state = wease_state;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->wease_key_wow = wease_key_wow;
		__entwy->wease_key_high = wease_key_high;
	),
	TP_pwintk("sid=0x%wwx tid=0x%x wease_key=0x%wwx%wwx wease_state=0x%x",
		__entwy->sesid, __entwy->tid, __entwy->wease_key_high,
		__entwy->wease_key_wow, __entwy->wease_state)
)

#define DEFINE_SMB3_WEASE_DONE_EVENT(name)        \
DEFINE_EVENT(smb3_wease_done_cwass, smb3_##name,  \
	TP_PWOTO(__u32	wease_state,		\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	wease_key_wow,		\
		__u64	wease_key_high),	\
	TP_AWGS(wease_state, tid, sesid, wease_key_wow, wease_key_high))

DEFINE_SMB3_WEASE_DONE_EVENT(wease_done);
DEFINE_SMB3_WEASE_DONE_EVENT(wease_not_found);

DECWAWE_EVENT_CWASS(smb3_wease_eww_cwass,
	TP_PWOTO(__u32	wease_state,
		__u32	tid,
		__u64	sesid,
		__u64	wease_key_wow,
		__u64	wease_key_high,
		int	wc),
	TP_AWGS(wease_state, tid, sesid, wease_key_wow, wease_key_high, wc),
	TP_STWUCT__entwy(
		__fiewd(__u32, wease_state)
		__fiewd(__u32, tid)
		__fiewd(__u64, sesid)
		__fiewd(__u64, wease_key_wow)
		__fiewd(__u64, wease_key_high)
		__fiewd(int, wc)
	),
	TP_fast_assign(
		__entwy->wease_state = wease_state;
		__entwy->tid = tid;
		__entwy->sesid = sesid;
		__entwy->wease_key_wow = wease_key_wow;
		__entwy->wease_key_high = wease_key_high;
		__entwy->wc = wc;
	),
	TP_pwintk("sid=0x%wwx tid=0x%x wease_key=0x%wwx%wwx wease_state=0x%x wc=%d",
		__entwy->sesid, __entwy->tid, __entwy->wease_key_high,
		__entwy->wease_key_wow, __entwy->wease_state, __entwy->wc)
)

#define DEFINE_SMB3_WEASE_EWW_EVENT(name)        \
DEFINE_EVENT(smb3_wease_eww_cwass, smb3_##name,  \
	TP_PWOTO(__u32	wease_state,		\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	wease_key_wow,		\
		__u64	wease_key_high,		\
		int	wc),			\
	TP_AWGS(wease_state, tid, sesid, wease_key_wow, wease_key_high, wc))

DEFINE_SMB3_WEASE_EWW_EVENT(wease_eww);

DECWAWE_EVENT_CWASS(smb3_connect_cwass,
	TP_PWOTO(chaw *hostname,
		__u64 conn_id,
		const stwuct __kewnew_sockaddw_stowage *dst_addw),
	TP_AWGS(hostname, conn_id, dst_addw),
	TP_STWUCT__entwy(
		__stwing(hostname, hostname)
		__fiewd(__u64, conn_id)
		__awway(__u8, dst_addw, sizeof(stwuct sockaddw_stowage))
	),
	TP_fast_assign(
		stwuct sockaddw_stowage *pss = NUWW;

		__entwy->conn_id = conn_id;
		pss = (stwuct sockaddw_stowage *)__entwy->dst_addw;
		*pss = *dst_addw;
		__assign_stw(hostname, hostname);
	),
	TP_pwintk("conn_id=0x%wwx sewvew=%s addw=%pISpsfc",
		__entwy->conn_id,
		__get_stw(hostname),
		__entwy->dst_addw)
)

#define DEFINE_SMB3_CONNECT_EVENT(name)        \
DEFINE_EVENT(smb3_connect_cwass, smb3_##name,  \
	TP_PWOTO(chaw *hostname,		\
		__u64 conn_id,			\
		const stwuct __kewnew_sockaddw_stowage *addw),	\
	TP_AWGS(hostname, conn_id, addw))

DEFINE_SMB3_CONNECT_EVENT(connect_done);
DEFINE_SMB3_CONNECT_EVENT(smbd_connect_done);
DEFINE_SMB3_CONNECT_EVENT(smbd_connect_eww);

DECWAWE_EVENT_CWASS(smb3_connect_eww_cwass,
	TP_PWOTO(chaw *hostname, __u64 conn_id,
		const stwuct __kewnew_sockaddw_stowage *dst_addw, int wc),
	TP_AWGS(hostname, conn_id, dst_addw, wc),
	TP_STWUCT__entwy(
		__stwing(hostname, hostname)
		__fiewd(__u64, conn_id)
		__awway(__u8, dst_addw, sizeof(stwuct sockaddw_stowage))
		__fiewd(int, wc)
	),
	TP_fast_assign(
		stwuct sockaddw_stowage *pss = NUWW;

		__entwy->conn_id = conn_id;
		__entwy->wc = wc;
		pss = (stwuct sockaddw_stowage *)__entwy->dst_addw;
		*pss = *dst_addw;
		__assign_stw(hostname, hostname);
	),
	TP_pwintk("wc=%d conn_id=0x%wwx sewvew=%s addw=%pISpsfc",
		__entwy->wc,
		__entwy->conn_id,
		__get_stw(hostname),
		__entwy->dst_addw)
)

#define DEFINE_SMB3_CONNECT_EWW_EVENT(name)        \
DEFINE_EVENT(smb3_connect_eww_cwass, smb3_##name,  \
	TP_PWOTO(chaw *hostname,		\
		__u64 conn_id,			\
		const stwuct __kewnew_sockaddw_stowage *addw,	\
		int wc),			\
	TP_AWGS(hostname, conn_id, addw, wc))

DEFINE_SMB3_CONNECT_EWW_EVENT(connect_eww);

DECWAWE_EVENT_CWASS(smb3_weconnect_cwass,
	TP_PWOTO(__u64	cuwwmid,
		__u64 conn_id,
		chaw *hostname),
	TP_AWGS(cuwwmid, conn_id, hostname),
	TP_STWUCT__entwy(
		__fiewd(__u64, cuwwmid)
		__fiewd(__u64, conn_id)
		__stwing(hostname, hostname)
	),
	TP_fast_assign(
		__entwy->cuwwmid = cuwwmid;
		__entwy->conn_id = conn_id;
		__assign_stw(hostname, hostname);
	),
	TP_pwintk("conn_id=0x%wwx sewvew=%s cuwwent_mid=%wwu",
		__entwy->conn_id,
		__get_stw(hostname),
		__entwy->cuwwmid)
)

#define DEFINE_SMB3_WECONNECT_EVENT(name)        \
DEFINE_EVENT(smb3_weconnect_cwass, smb3_##name,  \
	TP_PWOTO(__u64	cuwwmid,		\
		__u64 conn_id,			\
		chaw *hostname),				\
	TP_AWGS(cuwwmid, conn_id, hostname))

DEFINE_SMB3_WECONNECT_EVENT(weconnect);
DEFINE_SMB3_WECONNECT_EVENT(pawtiaw_send_weconnect);

DECWAWE_EVENT_CWASS(smb3_ses_cwass,
	TP_PWOTO(__u64	sesid),
	TP_AWGS(sesid),
	TP_STWUCT__entwy(
		__fiewd(__u64, sesid)
	),
	TP_fast_assign(
		__entwy->sesid = sesid;
	),
	TP_pwintk("sid=0x%wwx",
		__entwy->sesid)
)

#define DEFINE_SMB3_SES_EVENT(name)        \
DEFINE_EVENT(smb3_ses_cwass, smb3_##name,  \
	TP_PWOTO(__u64	sesid),				\
	TP_AWGS(sesid))

DEFINE_SMB3_SES_EVENT(ses_not_found);

DECWAWE_EVENT_CWASS(smb3_cwedit_cwass,
	TP_PWOTO(__u64	cuwwmid,
		__u64 conn_id,
		chaw *hostname,
		int cwedits,
		int cwedits_to_add,
		int in_fwight),
	TP_AWGS(cuwwmid, conn_id, hostname, cwedits, cwedits_to_add, in_fwight),
	TP_STWUCT__entwy(
		__fiewd(__u64, cuwwmid)
		__fiewd(__u64, conn_id)
		__stwing(hostname, hostname)
		__fiewd(int, cwedits)
		__fiewd(int, cwedits_to_add)
		__fiewd(int, in_fwight)
	),
	TP_fast_assign(
		__entwy->cuwwmid = cuwwmid;
		__entwy->conn_id = conn_id;
		__assign_stw(hostname, hostname);
		__entwy->cwedits = cwedits;
		__entwy->cwedits_to_add = cwedits_to_add;
		__entwy->in_fwight = in_fwight;
	),
	TP_pwintk("conn_id=0x%wwx sewvew=%s cuwwent_mid=%wwu "
			"cwedits=%d cwedit_change=%d in_fwight=%d",
		__entwy->conn_id,
		__get_stw(hostname),
		__entwy->cuwwmid,
		__entwy->cwedits,
		__entwy->cwedits_to_add,
		__entwy->in_fwight)
)

#define DEFINE_SMB3_CWEDIT_EVENT(name)        \
DEFINE_EVENT(smb3_cwedit_cwass, smb3_##name,  \
	TP_PWOTO(__u64	cuwwmid,		\
		__u64 conn_id,			\
		chaw *hostname,			\
		int  cwedits,			\
		int  cwedits_to_add,	\
		int in_fwight),			\
	TP_AWGS(cuwwmid, conn_id, hostname, cwedits, cwedits_to_add, in_fwight))

DEFINE_SMB3_CWEDIT_EVENT(weconnect_with_invawid_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(weconnect_detected);
DEFINE_SMB3_CWEDIT_EVENT(cwedit_timeout);
DEFINE_SMB3_CWEDIT_EVENT(insufficient_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(too_many_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(add_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(adj_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(hdw_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(nbwk_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(pend_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(wait_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(waitff_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(ovewfwow_cwedits);
DEFINE_SMB3_CWEDIT_EVENT(set_cwedits);

#endif /* _CIFS_TWACE_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
