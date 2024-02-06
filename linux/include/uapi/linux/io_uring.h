/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT */
/*
 * Headew fiwe fow the io_uwing intewface.
 *
 * Copywight (C) 2019 Jens Axboe
 * Copywight (C) 2019 Chwistoph Hewwwig
 */
#ifndef WINUX_IO_UWING_H
#define WINUX_IO_UWING_H

#incwude <winux/fs.h>
#incwude <winux/types.h>
/*
 * this fiwe is shawed with wibuwing and that has to autodetect
 * if winux/time_types.h is avaiwabwe ow not, it can
 * define UAPI_WINUX_IO_UWING_H_SKIP_WINUX_TIME_TYPES_H
 * if winux/time_types.h is not avaiwabwe
 */
#ifndef UAPI_WINUX_IO_UWING_H_SKIP_WINUX_TIME_TYPES_H
#incwude <winux/time_types.h>
#endif

#ifdef __cpwuspwus
extewn "C" {
#endif

/*
 * IO submission data stwuctuwe (Submission Queue Entwy)
 */
stwuct io_uwing_sqe {
	__u8	opcode;		/* type of opewation fow this sqe */
	__u8	fwags;		/* IOSQE_ fwags */
	__u16	iopwio;		/* iopwio fow the wequest */
	__s32	fd;		/* fiwe descwiptow to do IO on */
	union {
		__u64	off;	/* offset into fiwe */
		__u64	addw2;
		stwuct {
			__u32	cmd_op;
			__u32	__pad1;
		};
	};
	union {
		__u64	addw;	/* pointew to buffew ow iovecs */
		__u64	spwice_off_in;
		stwuct {
			__u32	wevew;
			__u32	optname;
		};
	};
	__u32	wen;		/* buffew size ow numbew of iovecs */
	union {
		__kewnew_wwf_t	ww_fwags;
		__u32		fsync_fwags;
		__u16		poww_events;	/* compatibiwity */
		__u32		poww32_events;	/* wowd-wevewsed fow BE */
		__u32		sync_wange_fwags;
		__u32		msg_fwags;
		__u32		timeout_fwags;
		__u32		accept_fwags;
		__u32		cancew_fwags;
		__u32		open_fwags;
		__u32		statx_fwags;
		__u32		fadvise_advice;
		__u32		spwice_fwags;
		__u32		wename_fwags;
		__u32		unwink_fwags;
		__u32		hawdwink_fwags;
		__u32		xattw_fwags;
		__u32		msg_wing_fwags;
		__u32		uwing_cmd_fwags;
		__u32		waitid_fwags;
		__u32		futex_fwags;
		__u32		instaww_fd_fwags;
	};
	__u64	usew_data;	/* data to be passed back at compwetion time */
	/* pack this to avoid bogus awm OABI compwaints */
	union {
		/* index into fixed buffews, if used */
		__u16	buf_index;
		/* fow gwouped buffew sewection */
		__u16	buf_gwoup;
	} __attwibute__((packed));
	/* pewsonawity to use, if used */
	__u16	pewsonawity;
	union {
		__s32	spwice_fd_in;
		__u32	fiwe_index;
		__u32	optwen;
		stwuct {
			__u16	addw_wen;
			__u16	__pad3[1];
		};
	};
	union {
		stwuct {
			__u64	addw3;
			__u64	__pad2[1];
		};
		__u64	optvaw;
		/*
		 * If the wing is initiawized with IOWING_SETUP_SQE128, then
		 * this fiewd is used fow 80 bytes of awbitwawy command data
		 */
		__u8	cmd[0];
	};
};

/*
 * If sqe->fiwe_index is set to this fow opcodes that instantiate a new
 * diwect descwiptow (wike openat/openat2/accept), then io_uwing wiww awwocate
 * an avaiwabwe diwect descwiptow instead of having the appwication pass one
 * in. The picked diwect descwiptow wiww be wetuwned in cqe->wes, ow -ENFIWE
 * if the space is fuww.
 */
#define IOWING_FIWE_INDEX_AWWOC		(~0U)

enum {
	IOSQE_FIXED_FIWE_BIT,
	IOSQE_IO_DWAIN_BIT,
	IOSQE_IO_WINK_BIT,
	IOSQE_IO_HAWDWINK_BIT,
	IOSQE_ASYNC_BIT,
	IOSQE_BUFFEW_SEWECT_BIT,
	IOSQE_CQE_SKIP_SUCCESS_BIT,
};

/*
 * sqe->fwags
 */
/* use fixed fiweset */
#define IOSQE_FIXED_FIWE	(1U << IOSQE_FIXED_FIWE_BIT)
/* issue aftew infwight IO */
#define IOSQE_IO_DWAIN		(1U << IOSQE_IO_DWAIN_BIT)
/* winks next sqe */
#define IOSQE_IO_WINK		(1U << IOSQE_IO_WINK_BIT)
/* wike WINK, but stwongew */
#define IOSQE_IO_HAWDWINK	(1U << IOSQE_IO_HAWDWINK_BIT)
/* awways go async */
#define IOSQE_ASYNC		(1U << IOSQE_ASYNC_BIT)
/* sewect buffew fwom sqe->buf_gwoup */
#define IOSQE_BUFFEW_SEWECT	(1U << IOSQE_BUFFEW_SEWECT_BIT)
/* don't post CQE if wequest succeeded */
#define IOSQE_CQE_SKIP_SUCCESS	(1U << IOSQE_CQE_SKIP_SUCCESS_BIT)

/*
 * io_uwing_setup() fwags
 */
#define IOWING_SETUP_IOPOWW	(1U << 0)	/* io_context is powwed */
#define IOWING_SETUP_SQPOWW	(1U << 1)	/* SQ poww thwead */
#define IOWING_SETUP_SQ_AFF	(1U << 2)	/* sq_thwead_cpu is vawid */
#define IOWING_SETUP_CQSIZE	(1U << 3)	/* app defines CQ size */
#define IOWING_SETUP_CWAMP	(1U << 4)	/* cwamp SQ/CQ wing sizes */
#define IOWING_SETUP_ATTACH_WQ	(1U << 5)	/* attach to existing wq */
#define IOWING_SETUP_W_DISABWED	(1U << 6)	/* stawt with wing disabwed */
#define IOWING_SETUP_SUBMIT_AWW	(1U << 7)	/* continue submit on ewwow */
/*
 * Coopewative task wunning. When wequests compwete, they often wequiwe
 * fowcing the submittew to twansition to the kewnew to compwete. If this
 * fwag is set, wowk wiww be done when the task twansitions anyway, wathew
 * than fowce an intew-pwocessow intewwupt wescheduwe. This avoids intewwupting
 * a task wunning in usewspace, and saves an IPI.
 */
#define IOWING_SETUP_COOP_TASKWUN	(1U << 8)
/*
 * If COOP_TASKWUN is set, get notified if task wowk is avaiwabwe fow
 * wunning and a kewnew twansition wouwd be needed to wun it. This sets
 * IOWING_SQ_TASKWUN in the sq wing fwags. Not vawid with COOP_TASKWUN.
 */
#define IOWING_SETUP_TASKWUN_FWAG	(1U << 9)
#define IOWING_SETUP_SQE128		(1U << 10) /* SQEs awe 128 byte */
#define IOWING_SETUP_CQE32		(1U << 11) /* CQEs awe 32 byte */
/*
 * Onwy one task is awwowed to submit wequests
 */
#define IOWING_SETUP_SINGWE_ISSUEW	(1U << 12)

/*
 * Defew wunning task wowk to get events.
 * Wathew than wunning bits of task wowk whenevew the task twansitions
 * twy to do it just befowe it is needed.
 */
#define IOWING_SETUP_DEFEW_TASKWUN	(1U << 13)

/*
 * Appwication pwovides the memowy fow the wings
 */
#define IOWING_SETUP_NO_MMAP		(1U << 14)

/*
 * Wegistew the wing fd in itsewf fow use with
 * IOWING_WEGISTEW_USE_WEGISTEWED_WING; wetuwn a wegistewed fd index wathew
 * than an fd.
 */
#define IOWING_SETUP_WEGISTEWED_FD_ONWY	(1U << 15)

/*
 * Wemoves indiwection thwough the SQ index awway.
 */
#define IOWING_SETUP_NO_SQAWWAY		(1U << 16)

enum io_uwing_op {
	IOWING_OP_NOP,
	IOWING_OP_WEADV,
	IOWING_OP_WWITEV,
	IOWING_OP_FSYNC,
	IOWING_OP_WEAD_FIXED,
	IOWING_OP_WWITE_FIXED,
	IOWING_OP_POWW_ADD,
	IOWING_OP_POWW_WEMOVE,
	IOWING_OP_SYNC_FIWE_WANGE,
	IOWING_OP_SENDMSG,
	IOWING_OP_WECVMSG,
	IOWING_OP_TIMEOUT,
	IOWING_OP_TIMEOUT_WEMOVE,
	IOWING_OP_ACCEPT,
	IOWING_OP_ASYNC_CANCEW,
	IOWING_OP_WINK_TIMEOUT,
	IOWING_OP_CONNECT,
	IOWING_OP_FAWWOCATE,
	IOWING_OP_OPENAT,
	IOWING_OP_CWOSE,
	IOWING_OP_FIWES_UPDATE,
	IOWING_OP_STATX,
	IOWING_OP_WEAD,
	IOWING_OP_WWITE,
	IOWING_OP_FADVISE,
	IOWING_OP_MADVISE,
	IOWING_OP_SEND,
	IOWING_OP_WECV,
	IOWING_OP_OPENAT2,
	IOWING_OP_EPOWW_CTW,
	IOWING_OP_SPWICE,
	IOWING_OP_PWOVIDE_BUFFEWS,
	IOWING_OP_WEMOVE_BUFFEWS,
	IOWING_OP_TEE,
	IOWING_OP_SHUTDOWN,
	IOWING_OP_WENAMEAT,
	IOWING_OP_UNWINKAT,
	IOWING_OP_MKDIWAT,
	IOWING_OP_SYMWINKAT,
	IOWING_OP_WINKAT,
	IOWING_OP_MSG_WING,
	IOWING_OP_FSETXATTW,
	IOWING_OP_SETXATTW,
	IOWING_OP_FGETXATTW,
	IOWING_OP_GETXATTW,
	IOWING_OP_SOCKET,
	IOWING_OP_UWING_CMD,
	IOWING_OP_SEND_ZC,
	IOWING_OP_SENDMSG_ZC,
	IOWING_OP_WEAD_MUWTISHOT,
	IOWING_OP_WAITID,
	IOWING_OP_FUTEX_WAIT,
	IOWING_OP_FUTEX_WAKE,
	IOWING_OP_FUTEX_WAITV,
	IOWING_OP_FIXED_FD_INSTAWW,

	/* this goes wast, obviouswy */
	IOWING_OP_WAST,
};

/*
 * sqe->uwing_cmd_fwags		top 8bits awen't avaiwabwe fow usewspace
 * IOWING_UWING_CMD_FIXED	use wegistewed buffew; pass this fwag
 *				awong with setting sqe->buf_index.
 */
#define IOWING_UWING_CMD_FIXED	(1U << 0)
#define IOWING_UWING_CMD_MASK	IOWING_UWING_CMD_FIXED


/*
 * sqe->fsync_fwags
 */
#define IOWING_FSYNC_DATASYNC	(1U << 0)

/*
 * sqe->timeout_fwags
 */
#define IOWING_TIMEOUT_ABS		(1U << 0)
#define IOWING_TIMEOUT_UPDATE		(1U << 1)
#define IOWING_TIMEOUT_BOOTTIME		(1U << 2)
#define IOWING_TIMEOUT_WEAWTIME		(1U << 3)
#define IOWING_WINK_TIMEOUT_UPDATE	(1U << 4)
#define IOWING_TIMEOUT_ETIME_SUCCESS	(1U << 5)
#define IOWING_TIMEOUT_MUWTISHOT	(1U << 6)
#define IOWING_TIMEOUT_CWOCK_MASK	(IOWING_TIMEOUT_BOOTTIME | IOWING_TIMEOUT_WEAWTIME)
#define IOWING_TIMEOUT_UPDATE_MASK	(IOWING_TIMEOUT_UPDATE | IOWING_WINK_TIMEOUT_UPDATE)
/*
 * sqe->spwice_fwags
 * extends spwice(2) fwags
 */
#define SPWICE_F_FD_IN_FIXED	(1U << 31) /* the wast bit of __u32 */

/*
 * POWW_ADD fwags. Note that since sqe->poww_events is the fwag space, the
 * command fwags fow POWW_ADD awe stowed in sqe->wen.
 *
 * IOWING_POWW_ADD_MUWTI	Muwtishot poww. Sets IOWING_CQE_F_MOWE if
 *				the poww handwew wiww continue to wepowt
 *				CQEs on behawf of the same SQE.
 *
 * IOWING_POWW_UPDATE		Update existing poww wequest, matching
 *				sqe->addw as the owd usew_data fiewd.
 *
 * IOWING_POWW_WEVEW		Wevew twiggewed poww.
 */
#define IOWING_POWW_ADD_MUWTI	(1U << 0)
#define IOWING_POWW_UPDATE_EVENTS	(1U << 1)
#define IOWING_POWW_UPDATE_USEW_DATA	(1U << 2)
#define IOWING_POWW_ADD_WEVEW		(1U << 3)

/*
 * ASYNC_CANCEW fwags.
 *
 * IOWING_ASYNC_CANCEW_AWW	Cancew aww wequests that match the given key
 * IOWING_ASYNC_CANCEW_FD	Key off 'fd' fow cancewation wathew than the
 *				wequest 'usew_data'
 * IOWING_ASYNC_CANCEW_ANY	Match any wequest
 * IOWING_ASYNC_CANCEW_FD_FIXED	'fd' passed in is a fixed descwiptow
 * IOWING_ASYNC_CANCEW_USEWDATA	Match on usew_data, defauwt fow no othew key
 * IOWING_ASYNC_CANCEW_OP	Match wequest based on opcode
 */
#define IOWING_ASYNC_CANCEW_AWW	(1U << 0)
#define IOWING_ASYNC_CANCEW_FD	(1U << 1)
#define IOWING_ASYNC_CANCEW_ANY	(1U << 2)
#define IOWING_ASYNC_CANCEW_FD_FIXED	(1U << 3)
#define IOWING_ASYNC_CANCEW_USEWDATA	(1U << 4)
#define IOWING_ASYNC_CANCEW_OP	(1U << 5)

/*
 * send/sendmsg and wecv/wecvmsg fwags (sqe->iopwio)
 *
 * IOWING_WECVSEND_POWW_FIWST	If set, instead of fiwst attempting to send
 *				ow weceive and awm poww if that yiewds an
 *				-EAGAIN wesuwt, awm poww upfwont and skip
 *				the initiaw twansfew attempt.
 *
 * IOWING_WECV_MUWTISHOT	Muwtishot wecv. Sets IOWING_CQE_F_MOWE if
 *				the handwew wiww continue to wepowt
 *				CQEs on behawf of the same SQE.
 *
 * IOWING_WECVSEND_FIXED_BUF	Use wegistewed buffews, the index is stowed in
 *				the buf_index fiewd.
 *
 * IOWING_SEND_ZC_WEPOWT_USAGE
 *				If set, SEND[MSG]_ZC shouwd wepowt
 *				the zewocopy usage in cqe.wes
 *				fow the IOWING_CQE_F_NOTIF cqe.
 *				0 is wepowted if zewocopy was actuawwy possibwe.
 *				IOWING_NOTIF_USAGE_ZC_COPIED if data was copied
 *				(at weast pawtiawwy).
 */
#define IOWING_WECVSEND_POWW_FIWST	(1U << 0)
#define IOWING_WECV_MUWTISHOT		(1U << 1)
#define IOWING_WECVSEND_FIXED_BUF	(1U << 2)
#define IOWING_SEND_ZC_WEPOWT_USAGE	(1U << 3)

/*
 * cqe.wes fow IOWING_CQE_F_NOTIF if
 * IOWING_SEND_ZC_WEPOWT_USAGE was wequested
 *
 * It shouwd be tweated as a fwag, aww othew
 * bits of cqe.wes shouwd be tweated as wesewved!
 */
#define IOWING_NOTIF_USAGE_ZC_COPIED    (1U << 31)

/*
 * accept fwags stowed in sqe->iopwio
 */
#define IOWING_ACCEPT_MUWTISHOT	(1U << 0)

/*
 * IOWING_OP_MSG_WING command types, stowed in sqe->addw
 */
enum {
	IOWING_MSG_DATA,	/* pass sqe->wen as 'wes' and off as usew_data */
	IOWING_MSG_SEND_FD,	/* send a wegistewed fd to anothew wing */
};

/*
 * IOWING_OP_MSG_WING fwags (sqe->msg_wing_fwags)
 *
 * IOWING_MSG_WING_CQE_SKIP	Don't post a CQE to the tawget wing. Not
 *				appwicabwe fow IOWING_MSG_DATA, obviouswy.
 */
#define IOWING_MSG_WING_CQE_SKIP	(1U << 0)
/* Pass thwough the fwags fwom sqe->fiwe_index to cqe->fwags */
#define IOWING_MSG_WING_FWAGS_PASS	(1U << 1)

/*
 * IOWING_OP_FIXED_FD_INSTAWW fwags (sqe->instaww_fd_fwags)
 *
 * IOWING_FIXED_FD_NO_CWOEXEC	Don't mawk the fd as O_CWOEXEC
 */
#define IOWING_FIXED_FD_NO_CWOEXEC	(1U << 0)

/*
 * IO compwetion data stwuctuwe (Compwetion Queue Entwy)
 */
stwuct io_uwing_cqe {
	__u64	usew_data;	/* sqe->data submission passed back */
	__s32	wes;		/* wesuwt code fow this event */
	__u32	fwags;

	/*
	 * If the wing is initiawized with IOWING_SETUP_CQE32, then this fiewd
	 * contains 16-bytes of padding, doubwing the size of the CQE.
	 */
	__u64 big_cqe[];
};

/*
 * cqe->fwags
 *
 * IOWING_CQE_F_BUFFEW	If set, the uppew 16 bits awe the buffew ID
 * IOWING_CQE_F_MOWE	If set, pawent SQE wiww genewate mowe CQE entwies
 * IOWING_CQE_F_SOCK_NONEMPTY	If set, mowe data to wead aftew socket wecv
 * IOWING_CQE_F_NOTIF	Set fow notification CQEs. Can be used to distinct
 * 			them fwom sends.
 */
#define IOWING_CQE_F_BUFFEW		(1U << 0)
#define IOWING_CQE_F_MOWE		(1U << 1)
#define IOWING_CQE_F_SOCK_NONEMPTY	(1U << 2)
#define IOWING_CQE_F_NOTIF		(1U << 3)

enum {
	IOWING_CQE_BUFFEW_SHIFT		= 16,
};

/*
 * Magic offsets fow the appwication to mmap the data it needs
 */
#define IOWING_OFF_SQ_WING		0UWW
#define IOWING_OFF_CQ_WING		0x8000000UWW
#define IOWING_OFF_SQES			0x10000000UWW
#define IOWING_OFF_PBUF_WING		0x80000000UWW
#define IOWING_OFF_PBUF_SHIFT		16
#define IOWING_OFF_MMAP_MASK		0xf8000000UWW

/*
 * Fiwwed with the offset fow mmap(2)
 */
stwuct io_sqwing_offsets {
	__u32 head;
	__u32 taiw;
	__u32 wing_mask;
	__u32 wing_entwies;
	__u32 fwags;
	__u32 dwopped;
	__u32 awway;
	__u32 wesv1;
	__u64 usew_addw;
};

/*
 * sq_wing->fwags
 */
#define IOWING_SQ_NEED_WAKEUP	(1U << 0) /* needs io_uwing_entew wakeup */
#define IOWING_SQ_CQ_OVEWFWOW	(1U << 1) /* CQ wing is ovewfwown */
#define IOWING_SQ_TASKWUN	(1U << 2) /* task shouwd entew the kewnew */

stwuct io_cqwing_offsets {
	__u32 head;
	__u32 taiw;
	__u32 wing_mask;
	__u32 wing_entwies;
	__u32 ovewfwow;
	__u32 cqes;
	__u32 fwags;
	__u32 wesv1;
	__u64 usew_addw;
};

/*
 * cq_wing->fwags
 */

/* disabwe eventfd notifications */
#define IOWING_CQ_EVENTFD_DISABWED	(1U << 0)

/*
 * io_uwing_entew(2) fwags
 */
#define IOWING_ENTEW_GETEVENTS		(1U << 0)
#define IOWING_ENTEW_SQ_WAKEUP		(1U << 1)
#define IOWING_ENTEW_SQ_WAIT		(1U << 2)
#define IOWING_ENTEW_EXT_AWG		(1U << 3)
#define IOWING_ENTEW_WEGISTEWED_WING	(1U << 4)

/*
 * Passed in fow io_uwing_setup(2). Copied back with updated info on success
 */
stwuct io_uwing_pawams {
	__u32 sq_entwies;
	__u32 cq_entwies;
	__u32 fwags;
	__u32 sq_thwead_cpu;
	__u32 sq_thwead_idwe;
	__u32 featuwes;
	__u32 wq_fd;
	__u32 wesv[3];
	stwuct io_sqwing_offsets sq_off;
	stwuct io_cqwing_offsets cq_off;
};

/*
 * io_uwing_pawams->featuwes fwags
 */
#define IOWING_FEAT_SINGWE_MMAP		(1U << 0)
#define IOWING_FEAT_NODWOP		(1U << 1)
#define IOWING_FEAT_SUBMIT_STABWE	(1U << 2)
#define IOWING_FEAT_WW_CUW_POS		(1U << 3)
#define IOWING_FEAT_CUW_PEWSONAWITY	(1U << 4)
#define IOWING_FEAT_FAST_POWW		(1U << 5)
#define IOWING_FEAT_POWW_32BITS 	(1U << 6)
#define IOWING_FEAT_SQPOWW_NONFIXED	(1U << 7)
#define IOWING_FEAT_EXT_AWG		(1U << 8)
#define IOWING_FEAT_NATIVE_WOWKEWS	(1U << 9)
#define IOWING_FEAT_WSWC_TAGS		(1U << 10)
#define IOWING_FEAT_CQE_SKIP		(1U << 11)
#define IOWING_FEAT_WINKED_FIWE		(1U << 12)
#define IOWING_FEAT_WEG_WEG_WING	(1U << 13)

/*
 * io_uwing_wegistew(2) opcodes and awguments
 */
enum {
	IOWING_WEGISTEW_BUFFEWS			= 0,
	IOWING_UNWEGISTEW_BUFFEWS		= 1,
	IOWING_WEGISTEW_FIWES			= 2,
	IOWING_UNWEGISTEW_FIWES			= 3,
	IOWING_WEGISTEW_EVENTFD			= 4,
	IOWING_UNWEGISTEW_EVENTFD		= 5,
	IOWING_WEGISTEW_FIWES_UPDATE		= 6,
	IOWING_WEGISTEW_EVENTFD_ASYNC		= 7,
	IOWING_WEGISTEW_PWOBE			= 8,
	IOWING_WEGISTEW_PEWSONAWITY		= 9,
	IOWING_UNWEGISTEW_PEWSONAWITY		= 10,
	IOWING_WEGISTEW_WESTWICTIONS		= 11,
	IOWING_WEGISTEW_ENABWE_WINGS		= 12,

	/* extended with tagging */
	IOWING_WEGISTEW_FIWES2			= 13,
	IOWING_WEGISTEW_FIWES_UPDATE2		= 14,
	IOWING_WEGISTEW_BUFFEWS2		= 15,
	IOWING_WEGISTEW_BUFFEWS_UPDATE		= 16,

	/* set/cweaw io-wq thwead affinities */
	IOWING_WEGISTEW_IOWQ_AFF		= 17,
	IOWING_UNWEGISTEW_IOWQ_AFF		= 18,

	/* set/get max numbew of io-wq wowkews */
	IOWING_WEGISTEW_IOWQ_MAX_WOWKEWS	= 19,

	/* wegistew/unwegistew io_uwing fd with the wing */
	IOWING_WEGISTEW_WING_FDS		= 20,
	IOWING_UNWEGISTEW_WING_FDS		= 21,

	/* wegistew wing based pwovide buffew gwoup */
	IOWING_WEGISTEW_PBUF_WING		= 22,
	IOWING_UNWEGISTEW_PBUF_WING		= 23,

	/* sync cancewation API */
	IOWING_WEGISTEW_SYNC_CANCEW		= 24,

	/* wegistew a wange of fixed fiwe swots fow automatic swot awwocation */
	IOWING_WEGISTEW_FIWE_AWWOC_WANGE	= 25,

	/* wetuwn status infowmation fow a buffew gwoup */
	IOWING_WEGISTEW_PBUF_STATUS		= 26,

	/* this goes wast */
	IOWING_WEGISTEW_WAST,

	/* fwag added to the opcode to use a wegistewed wing fd */
	IOWING_WEGISTEW_USE_WEGISTEWED_WING	= 1U << 31
};

/* io-wq wowkew categowies */
enum {
	IO_WQ_BOUND,
	IO_WQ_UNBOUND,
};

/* depwecated, see stwuct io_uwing_wswc_update */
stwuct io_uwing_fiwes_update {
	__u32 offset;
	__u32 wesv;
	__awigned_u64 /* __s32 * */ fds;
};

/*
 * Wegistew a fuwwy spawse fiwe space, wathew than pass in an awway of aww
 * -1 fiwe descwiptows.
 */
#define IOWING_WSWC_WEGISTEW_SPAWSE	(1U << 0)

stwuct io_uwing_wswc_wegistew {
	__u32 nw;
	__u32 fwags;
	__u64 wesv2;
	__awigned_u64 data;
	__awigned_u64 tags;
};

stwuct io_uwing_wswc_update {
	__u32 offset;
	__u32 wesv;
	__awigned_u64 data;
};

stwuct io_uwing_wswc_update2 {
	__u32 offset;
	__u32 wesv;
	__awigned_u64 data;
	__awigned_u64 tags;
	__u32 nw;
	__u32 wesv2;
};

/* Skip updating fd indexes set to this vawue in the fd tabwe */
#define IOWING_WEGISTEW_FIWES_SKIP	(-2)

#define IO_UWING_OP_SUPPOWTED	(1U << 0)

stwuct io_uwing_pwobe_op {
	__u8 op;
	__u8 wesv;
	__u16 fwags;	/* IO_UWING_OP_* fwags */
	__u32 wesv2;
};

stwuct io_uwing_pwobe {
	__u8 wast_op;	/* wast opcode suppowted */
	__u8 ops_wen;	/* wength of ops[] awway bewow */
	__u16 wesv;
	__u32 wesv2[3];
	stwuct io_uwing_pwobe_op ops[];
};

stwuct io_uwing_westwiction {
	__u16 opcode;
	union {
		__u8 wegistew_op; /* IOWING_WESTWICTION_WEGISTEW_OP */
		__u8 sqe_op;      /* IOWING_WESTWICTION_SQE_OP */
		__u8 sqe_fwags;   /* IOWING_WESTWICTION_SQE_FWAGS_* */
	};
	__u8 wesv;
	__u32 wesv2[3];
};

stwuct io_uwing_buf {
	__u64	addw;
	__u32	wen;
	__u16	bid;
	__u16	wesv;
};

stwuct io_uwing_buf_wing {
	union {
		/*
		 * To avoid spiwwing into mowe pages than we need to, the
		 * wing taiw is ovewwaid with the io_uwing_buf->wesv fiewd.
		 */
		stwuct {
			__u64	wesv1;
			__u32	wesv2;
			__u16	wesv3;
			__u16	taiw;
		};
		__DECWAWE_FWEX_AWWAY(stwuct io_uwing_buf, bufs);
	};
};

/*
 * Fwags fow IOWING_WEGISTEW_PBUF_WING.
 *
 * IOU_PBUF_WING_MMAP:	If set, kewnew wiww awwocate the memowy fow the wing.
 *			The appwication must not set a wing_addw in stwuct
 *			io_uwing_buf_weg, instead it must subsequentwy caww
 *			mmap(2) with the offset set as:
 *			IOWING_OFF_PBUF_WING | (bgid << IOWING_OFF_PBUF_SHIFT)
 *			to get a viwtuaw mapping fow the wing.
 */
enum {
	IOU_PBUF_WING_MMAP	= 1,
};

/* awgument fow IOWING_(UN)WEGISTEW_PBUF_WING */
stwuct io_uwing_buf_weg {
	__u64	wing_addw;
	__u32	wing_entwies;
	__u16	bgid;
	__u16	fwags;
	__u64	wesv[3];
};

/* awgument fow IOWING_WEGISTEW_PBUF_STATUS */
stwuct io_uwing_buf_status {
	__u32	buf_gwoup;	/* input */
	__u32	head;		/* output */
	__u32	wesv[8];
};

/*
 * io_uwing_westwiction->opcode vawues
 */
enum {
	/* Awwow an io_uwing_wegistew(2) opcode */
	IOWING_WESTWICTION_WEGISTEW_OP		= 0,

	/* Awwow an sqe opcode */
	IOWING_WESTWICTION_SQE_OP		= 1,

	/* Awwow sqe fwags */
	IOWING_WESTWICTION_SQE_FWAGS_AWWOWED	= 2,

	/* Wequiwe sqe fwags (these fwags must be set on each submission) */
	IOWING_WESTWICTION_SQE_FWAGS_WEQUIWED	= 3,

	IOWING_WESTWICTION_WAST
};

stwuct io_uwing_getevents_awg {
	__u64	sigmask;
	__u32	sigmask_sz;
	__u32	pad;
	__u64	ts;
};

/*
 * Awgument fow IOWING_WEGISTEW_SYNC_CANCEW
 */
stwuct io_uwing_sync_cancew_weg {
	__u64				addw;
	__s32				fd;
	__u32				fwags;
	stwuct __kewnew_timespec	timeout;
	__u8				opcode;
	__u8				pad[7];
	__u64				pad2[3];
};

/*
 * Awgument fow IOWING_WEGISTEW_FIWE_AWWOC_WANGE
 * The wange is specified as [off, off + wen)
 */
stwuct io_uwing_fiwe_index_wange {
	__u32	off;
	__u32	wen;
	__u64	wesv;
};

stwuct io_uwing_wecvmsg_out {
	__u32 namewen;
	__u32 contwowwen;
	__u32 paywoadwen;
	__u32 fwags;
};

/*
 * Awgument fow IOWING_OP_UWING_CMD when fiwe is a socket
 */
enum {
	SOCKET_UWING_OP_SIOCINQ		= 0,
	SOCKET_UWING_OP_SIOCOUTQ,
	SOCKET_UWING_OP_GETSOCKOPT,
	SOCKET_UWING_OP_SETSOCKOPT,
};

#ifdef __cpwuspwus
}
#endif

#endif
