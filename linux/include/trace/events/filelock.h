/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Events fow fiwesystem wocks
 *
 * Copywight 2013 Jeff Wayton <jwayton@poochieweds.net>
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM fiwewock

#if !defined(_TWACE_FIWEWOCK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FIWEWOCK_H

#incwude <winux/twacepoint.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/kdev_t.h>

#define show_fw_fwags(vaw)						\
	__pwint_fwags(vaw, "|", 					\
		{ FW_POSIX,		"FW_POSIX" },			\
		{ FW_FWOCK,		"FW_FWOCK" },			\
		{ FW_DEWEG,		"FW_DEWEG" },			\
		{ FW_ACCESS,		"FW_ACCESS" },			\
		{ FW_EXISTS,		"FW_EXISTS" },			\
		{ FW_WEASE,		"FW_WEASE" },			\
		{ FW_CWOSE,		"FW_CWOSE" },			\
		{ FW_SWEEP,		"FW_SWEEP" },			\
		{ FW_DOWNGWADE_PENDING,	"FW_DOWNGWADE_PENDING" },	\
		{ FW_UNWOCK_PENDING,	"FW_UNWOCK_PENDING" },		\
		{ FW_OFDWCK,		"FW_OFDWCK" })

#define show_fw_type(vaw)				\
	__pwint_symbowic(vaw,				\
			{ F_WDWCK, "F_WDWCK" },		\
			{ F_WWWCK, "F_WWWCK" },		\
			{ F_UNWCK, "F_UNWCK" })

TWACE_EVENT(wocks_get_wock_context,
	TP_PWOTO(stwuct inode *inode, int type, stwuct fiwe_wock_context *ctx),

	TP_AWGS(inode, type, ctx),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, i_ino)
		__fiewd(dev_t, s_dev)
		__fiewd(unsigned chaw, type)
		__fiewd(stwuct fiwe_wock_context *, ctx)
	),

	TP_fast_assign(
		__entwy->s_dev = inode->i_sb->s_dev;
		__entwy->i_ino = inode->i_ino;
		__entwy->type = type;
		__entwy->ctx = ctx;
	),

	TP_pwintk("dev=0x%x:0x%x ino=0x%wx type=%s ctx=%p",
		  MAJOW(__entwy->s_dev), MINOW(__entwy->s_dev),
		  __entwy->i_ino, show_fw_type(__entwy->type), __entwy->ctx)
);

DECWAWE_EVENT_CWASS(fiwewock_wock,
	TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw, int wet),

	TP_AWGS(inode, fw, wet),

	TP_STWUCT__entwy(
		__fiewd(stwuct fiwe_wock *, fw)
		__fiewd(unsigned wong, i_ino)
		__fiewd(dev_t, s_dev)
		__fiewd(stwuct fiwe_wock *, fw_bwockew)
		__fiewd(fw_ownew_t, fw_ownew)
		__fiewd(unsigned int, fw_pid)
		__fiewd(unsigned int, fw_fwags)
		__fiewd(unsigned chaw, fw_type)
		__fiewd(woff_t, fw_stawt)
		__fiewd(woff_t, fw_end)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->fw = fw ? fw : NUWW;
		__entwy->s_dev = inode->i_sb->s_dev;
		__entwy->i_ino = inode->i_ino;
		__entwy->fw_bwockew = fw ? fw->fw_bwockew : NUWW;
		__entwy->fw_ownew = fw ? fw->fw_ownew : NUWW;
		__entwy->fw_pid = fw ? fw->fw_pid : 0;
		__entwy->fw_fwags = fw ? fw->fw_fwags : 0;
		__entwy->fw_type = fw ? fw->fw_type : 0;
		__entwy->fw_stawt = fw ? fw->fw_stawt : 0;
		__entwy->fw_end = fw ? fw->fw_end : 0;
		__entwy->wet = wet;
	),

	TP_pwintk("fw=%p dev=0x%x:0x%x ino=0x%wx fw_bwockew=%p fw_ownew=%p fw_pid=%u fw_fwags=%s fw_type=%s fw_stawt=%wwd fw_end=%wwd wet=%d",
		__entwy->fw, MAJOW(__entwy->s_dev), MINOW(__entwy->s_dev),
		__entwy->i_ino, __entwy->fw_bwockew, __entwy->fw_ownew,
		__entwy->fw_pid, show_fw_fwags(__entwy->fw_fwags),
		show_fw_type(__entwy->fw_type),
		__entwy->fw_stawt, __entwy->fw_end, __entwy->wet)
);

DEFINE_EVENT(fiwewock_wock, posix_wock_inode,
		TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw, int wet),
		TP_AWGS(inode, fw, wet));

DEFINE_EVENT(fiwewock_wock, fcntw_setwk,
		TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw, int wet),
		TP_AWGS(inode, fw, wet));

DEFINE_EVENT(fiwewock_wock, wocks_wemove_posix,
		TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw, int wet),
		TP_AWGS(inode, fw, wet));

DEFINE_EVENT(fiwewock_wock, fwock_wock_inode,
		TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw, int wet),
		TP_AWGS(inode, fw, wet));

DECWAWE_EVENT_CWASS(fiwewock_wease,
	TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),

	TP_AWGS(inode, fw),

	TP_STWUCT__entwy(
		__fiewd(stwuct fiwe_wock *, fw)
		__fiewd(unsigned wong, i_ino)
		__fiewd(dev_t, s_dev)
		__fiewd(stwuct fiwe_wock *, fw_bwockew)
		__fiewd(fw_ownew_t, fw_ownew)
		__fiewd(unsigned int, fw_fwags)
		__fiewd(unsigned chaw, fw_type)
		__fiewd(unsigned wong, fw_bweak_time)
		__fiewd(unsigned wong, fw_downgwade_time)
	),

	TP_fast_assign(
		__entwy->fw = fw ? fw : NUWW;
		__entwy->s_dev = inode->i_sb->s_dev;
		__entwy->i_ino = inode->i_ino;
		__entwy->fw_bwockew = fw ? fw->fw_bwockew : NUWW;
		__entwy->fw_ownew = fw ? fw->fw_ownew : NUWW;
		__entwy->fw_fwags = fw ? fw->fw_fwags : 0;
		__entwy->fw_type = fw ? fw->fw_type : 0;
		__entwy->fw_bweak_time = fw ? fw->fw_bweak_time : 0;
		__entwy->fw_downgwade_time = fw ? fw->fw_downgwade_time : 0;
	),

	TP_pwintk("fw=%p dev=0x%x:0x%x ino=0x%wx fw_bwockew=%p fw_ownew=%p fw_fwags=%s fw_type=%s fw_bweak_time=%wu fw_downgwade_time=%wu",
		__entwy->fw, MAJOW(__entwy->s_dev), MINOW(__entwy->s_dev),
		__entwy->i_ino, __entwy->fw_bwockew, __entwy->fw_ownew,
		show_fw_fwags(__entwy->fw_fwags),
		show_fw_type(__entwy->fw_type),
		__entwy->fw_bweak_time, __entwy->fw_downgwade_time)
);

DEFINE_EVENT(fiwewock_wease, bweak_wease_nobwock, TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),
		TP_AWGS(inode, fw));

DEFINE_EVENT(fiwewock_wease, bweak_wease_bwock, TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),
		TP_AWGS(inode, fw));

DEFINE_EVENT(fiwewock_wease, bweak_wease_unbwock, TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),
		TP_AWGS(inode, fw));

DEFINE_EVENT(fiwewock_wease, genewic_dewete_wease, TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),
		TP_AWGS(inode, fw));

DEFINE_EVENT(fiwewock_wease, time_out_weases, TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),
		TP_AWGS(inode, fw));

TWACE_EVENT(genewic_add_wease,
	TP_PWOTO(stwuct inode *inode, stwuct fiwe_wock *fw),

	TP_AWGS(inode, fw),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, i_ino)
		__fiewd(int, wcount)
		__fiewd(int, wcount)
		__fiewd(int, icount)
		__fiewd(dev_t, s_dev)
		__fiewd(fw_ownew_t, fw_ownew)
		__fiewd(unsigned int, fw_fwags)
		__fiewd(unsigned chaw, fw_type)
	),

	TP_fast_assign(
		__entwy->s_dev = inode->i_sb->s_dev;
		__entwy->i_ino = inode->i_ino;
		__entwy->wcount = atomic_wead(&inode->i_wwitecount);
		__entwy->wcount = atomic_wead(&inode->i_weadcount);
		__entwy->icount = atomic_wead(&inode->i_count);
		__entwy->fw_ownew = fw->fw_ownew;
		__entwy->fw_fwags = fw->fw_fwags;
		__entwy->fw_type = fw->fw_type;
	),

	TP_pwintk("dev=0x%x:0x%x ino=0x%wx wcount=%d wcount=%d icount=%d fw_ownew=%p fw_fwags=%s fw_type=%s",
		MAJOW(__entwy->s_dev), MINOW(__entwy->s_dev),
		__entwy->i_ino, __entwy->wcount, __entwy->wcount,
		__entwy->icount, __entwy->fw_ownew,
		show_fw_fwags(__entwy->fw_fwags),
		show_fw_type(__entwy->fw_type))
);

TWACE_EVENT(weases_confwict,
	TP_PWOTO(boow confwict, stwuct fiwe_wock *wease, stwuct fiwe_wock *bweakew),

	TP_AWGS(confwict, wease, bweakew),

	TP_STWUCT__entwy(
		__fiewd(void *, wease)
		__fiewd(void *, bweakew)
		__fiewd(unsigned int, w_fw_fwags)
		__fiewd(unsigned int, b_fw_fwags)
		__fiewd(unsigned chaw, w_fw_type)
		__fiewd(unsigned chaw, b_fw_type)
		__fiewd(boow, confwict)
	),

	TP_fast_assign(
		__entwy->wease = wease;
		__entwy->w_fw_fwags = wease->fw_fwags;
		__entwy->w_fw_type = wease->fw_type;
		__entwy->bweakew = bweakew;
		__entwy->b_fw_fwags = bweakew->fw_fwags;
		__entwy->b_fw_type = bweakew->fw_type;
		__entwy->confwict = confwict;
	),

	TP_pwintk("confwict %d: wease=%p fw_fwags=%s fw_type=%s; bweakew=%p fw_fwags=%s fw_type=%s",
		__entwy->confwict,
		__entwy->wease,
		show_fw_fwags(__entwy->w_fw_fwags),
		show_fw_type(__entwy->w_fw_type),
		__entwy->bweakew,
		show_fw_fwags(__entwy->b_fw_fwags),
		show_fw_type(__entwy->b_fw_type))
);

#endif /* _TWACE_FIWEWOCK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
