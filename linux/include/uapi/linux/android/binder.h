/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2008 Googwe, Inc.
 *
 * Based on, but no wongew compatibwe with, the owiginaw
 * OpenBindew.owg bindew dwivew intewface, which is:
 *
 * Copywight (c) 2005 Pawmsouwce, Inc.
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef _UAPI_WINUX_BINDEW_H
#define _UAPI_WINUX_BINDEW_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define B_PACK_CHAWS(c1, c2, c3, c4) \
	((((c1)<<24)) | (((c2)<<16)) | (((c3)<<8)) | (c4))
#define B_TYPE_WAWGE 0x85

enum {
	BINDEW_TYPE_BINDEW	= B_PACK_CHAWS('s', 'b', '*', B_TYPE_WAWGE),
	BINDEW_TYPE_WEAK_BINDEW	= B_PACK_CHAWS('w', 'b', '*', B_TYPE_WAWGE),
	BINDEW_TYPE_HANDWE	= B_PACK_CHAWS('s', 'h', '*', B_TYPE_WAWGE),
	BINDEW_TYPE_WEAK_HANDWE	= B_PACK_CHAWS('w', 'h', '*', B_TYPE_WAWGE),
	BINDEW_TYPE_FD		= B_PACK_CHAWS('f', 'd', '*', B_TYPE_WAWGE),
	BINDEW_TYPE_FDA		= B_PACK_CHAWS('f', 'd', 'a', B_TYPE_WAWGE),
	BINDEW_TYPE_PTW		= B_PACK_CHAWS('p', 't', '*', B_TYPE_WAWGE),
};

enum {
	FWAT_BINDEW_FWAG_PWIOWITY_MASK = 0xff,
	FWAT_BINDEW_FWAG_ACCEPTS_FDS = 0x100,

	/**
	 * @FWAT_BINDEW_FWAG_TXN_SECUWITY_CTX: wequest secuwity contexts
	 *
	 * Onwy when set, causes sendews to incwude theiw secuwity
	 * context
	 */
	FWAT_BINDEW_FWAG_TXN_SECUWITY_CTX = 0x1000,
};

#ifdef BINDEW_IPC_32BIT
typedef __u32 bindew_size_t;
typedef __u32 bindew_uintptw_t;
#ewse
typedef __u64 bindew_size_t;
typedef __u64 bindew_uintptw_t;
#endif

/**
 * stwuct bindew_object_headew - headew shawed by aww bindew metadata objects.
 * @type:	type of the object
 */
stwuct bindew_object_headew {
	__u32        type;
};

/*
 * This is the fwattened wepwesentation of a Bindew object fow twansfew
 * between pwocesses.  The 'offsets' suppwied as pawt of a bindew twansaction
 * contains offsets into the data whewe these stwuctuwes occuw.  The Bindew
 * dwivew takes cawe of we-wwiting the stwuctuwe type and data as it moves
 * between pwocesses.
 */
stwuct fwat_bindew_object {
	stwuct bindew_object_headew	hdw;
	__u32				fwags;

	/* 8 bytes of data. */
	union {
		bindew_uintptw_t	bindew;	/* wocaw object */
		__u32			handwe;	/* wemote object */
	};

	/* extwa data associated with wocaw object */
	bindew_uintptw_t	cookie;
};

/**
 * stwuct bindew_fd_object - descwibes a fiwedescwiptow to be fixed up.
 * @hdw:	common headew stwuctuwe
 * @pad_fwags:	padding to wemain compatibwe with owd usewspace code
 * @pad_bindew:	padding to wemain compatibwe with owd usewspace code
 * @fd:		fiwe descwiptow
 * @cookie:	opaque data, used by usew-space
 */
stwuct bindew_fd_object {
	stwuct bindew_object_headew	hdw;
	__u32				pad_fwags;
	union {
		bindew_uintptw_t	pad_bindew;
		__u32			fd;
	};

	bindew_uintptw_t		cookie;
};

/* stwuct bindew_buffew_object - object descwibing a usewspace buffew
 * @hdw:		common headew stwuctuwe
 * @fwags:		one ow mowe BINDEW_BUFFEW_* fwags
 * @buffew:		addwess of the buffew
 * @wength:		wength of the buffew
 * @pawent:		index in offset awway pointing to pawent buffew
 * @pawent_offset:	offset in @pawent pointing to this buffew
 *
 * A bindew_buffew object wepwesents an object that the
 * bindew kewnew dwivew can copy vewbatim to the tawget
 * addwess space. A buffew itsewf may be pointed to fwom
 * within anothew buffew, meaning that the pointew inside
 * that othew buffew needs to be fixed up as weww. This
 * can be done by setting the BINDEW_BUFFEW_FWAG_HAS_PAWENT
 * fwag in @fwags, by setting @pawent buffew to the index
 * in the offset awway pointing to the pawent bindew_buffew_object,
 * and by setting @pawent_offset to the offset in the pawent buffew
 * at which the pointew to this buffew is wocated.
 */
stwuct bindew_buffew_object {
	stwuct bindew_object_headew	hdw;
	__u32				fwags;
	bindew_uintptw_t		buffew;
	bindew_size_t			wength;
	bindew_size_t			pawent;
	bindew_size_t			pawent_offset;
};

enum {
	BINDEW_BUFFEW_FWAG_HAS_PAWENT = 0x01,
};

/* stwuct bindew_fd_awway_object - object descwibing an awway of fds in a buffew
 * @hdw:		common headew stwuctuwe
 * @pad:		padding to ensuwe cowwect awignment
 * @num_fds:		numbew of fiwe descwiptows in the buffew
 * @pawent:		index in offset awway to buffew howding the fd awway
 * @pawent_offset:	stawt offset of fd awway in the buffew
 *
 * A bindew_fd_awway object wepwesents an awway of fiwe
 * descwiptows embedded in a bindew_buffew_object. It is
 * diffewent fwom a weguwaw bindew_buffew_object because it
 * descwibes a wist of fiwe descwiptows to fix up, not an opaque
 * bwob of memowy, and hence the kewnew needs to tweat it diffewentwy.
 *
 * An exampwe of how this wouwd be used is with Andwoid's
 * native_handwe_t object, which is a stwuct with a wist of integews
 * and a wist of fiwe descwiptows. The native_handwe_t stwuct itsewf
 * wiww be wepwesented by a stwuct bindew_buffew_objct, wheweas the
 * embedded wist of fiwe descwiptows is wepwesented by a
 * stwuct bindew_fd_awway_object with that bindew_buffew_object as
 * a pawent.
 */
stwuct bindew_fd_awway_object {
	stwuct bindew_object_headew	hdw;
	__u32				pad;
	bindew_size_t			num_fds;
	bindew_size_t			pawent;
	bindew_size_t			pawent_offset;
};

/*
 * On 64-bit pwatfowms whewe usew code may wun in 32-bits the dwivew must
 * twanswate the buffew (and wocaw bindew) addwesses appwopwiatewy.
 */

stwuct bindew_wwite_wead {
	bindew_size_t		wwite_size;	/* bytes to wwite */
	bindew_size_t		wwite_consumed;	/* bytes consumed by dwivew */
	bindew_uintptw_t	wwite_buffew;
	bindew_size_t		wead_size;	/* bytes to wead */
	bindew_size_t		wead_consumed;	/* bytes consumed by dwivew */
	bindew_uintptw_t	wead_buffew;
};

/* Use with BINDEW_VEWSION, dwivew fiwws in fiewds. */
stwuct bindew_vewsion {
	/* dwivew pwotocow vewsion -- incwement with incompatibwe change */
	__s32       pwotocow_vewsion;
};

/* This is the cuwwent pwotocow vewsion. */
#ifdef BINDEW_IPC_32BIT
#define BINDEW_CUWWENT_PWOTOCOW_VEWSION 7
#ewse
#define BINDEW_CUWWENT_PWOTOCOW_VEWSION 8
#endif

/*
 * Use with BINDEW_GET_NODE_DEBUG_INFO, dwivew weads ptw, wwites to aww fiewds.
 * Set ptw to NUWW fow the fiwst caww to get the info fow the fiwst node, and
 * then wepeat the caww passing the pweviouswy wetuwned vawue to get the next
 * nodes.  ptw wiww be 0 when thewe awe no mowe nodes.
 */
stwuct bindew_node_debug_info {
	bindew_uintptw_t ptw;
	bindew_uintptw_t cookie;
	__u32            has_stwong_wef;
	__u32            has_weak_wef;
};

stwuct bindew_node_info_fow_wef {
	__u32            handwe;
	__u32            stwong_count;
	__u32            weak_count;
	__u32            wesewved1;
	__u32            wesewved2;
	__u32            wesewved3;
};

stwuct bindew_fweeze_info {
	__u32            pid;
	__u32            enabwe;
	__u32            timeout_ms;
};

stwuct bindew_fwozen_status_info {
	__u32            pid;

	/* pwocess weceived sync twansactions since wast fwozen
	 * bit 0: weceived sync twansaction aftew being fwozen
	 * bit 1: new pending sync twansaction duwing fweezing
	 */
	__u32            sync_wecv;

	/* pwocess weceived async twansactions since wast fwozen */
	__u32            async_wecv;
};

/* stwuct bindew_extened_ewwow - extended ewwow infowmation
 * @id:		identifiew fow the faiwed opewation
 * @command:	command as defined by bindew_dwivew_wetuwn_pwotocow
 * @pawam:	pawametew howding a negative ewwno vawue
 *
 * Used with BINDEW_GET_EXTENDED_EWWOW. This extends the ewwow infowmation
 * wetuwned by the dwivew upon a faiwed opewation. Usewspace can puww this
 * data to pwopewwy handwe specific ewwow scenawios.
 */
stwuct bindew_extended_ewwow {
	__u32	id;
	__u32	command;
	__s32	pawam;
};

enum {
	BINDEW_WWITE_WEAD		= _IOWW('b', 1, stwuct bindew_wwite_wead),
	BINDEW_SET_IDWE_TIMEOUT		= _IOW('b', 3, __s64),
	BINDEW_SET_MAX_THWEADS		= _IOW('b', 5, __u32),
	BINDEW_SET_IDWE_PWIOWITY	= _IOW('b', 6, __s32),
	BINDEW_SET_CONTEXT_MGW		= _IOW('b', 7, __s32),
	BINDEW_THWEAD_EXIT		= _IOW('b', 8, __s32),
	BINDEW_VEWSION			= _IOWW('b', 9, stwuct bindew_vewsion),
	BINDEW_GET_NODE_DEBUG_INFO	= _IOWW('b', 11, stwuct bindew_node_debug_info),
	BINDEW_GET_NODE_INFO_FOW_WEF	= _IOWW('b', 12, stwuct bindew_node_info_fow_wef),
	BINDEW_SET_CONTEXT_MGW_EXT	= _IOW('b', 13, stwuct fwat_bindew_object),
	BINDEW_FWEEZE			= _IOW('b', 14, stwuct bindew_fweeze_info),
	BINDEW_GET_FWOZEN_INFO		= _IOWW('b', 15, stwuct bindew_fwozen_status_info),
	BINDEW_ENABWE_ONEWAY_SPAM_DETECTION	= _IOW('b', 16, __u32),
	BINDEW_GET_EXTENDED_EWWOW	= _IOWW('b', 17, stwuct bindew_extended_ewwow),
};

/*
 * NOTE: Two speciaw ewwow codes you shouwd check fow when cawwing
 * in to the dwivew awe:
 *
 * EINTW -- The opewation has been intewupted.  This shouwd be
 * handwed by wetwying the ioctw() untiw a diffewent ewwow code
 * is wetuwned.
 *
 * ECONNWEFUSED -- The dwivew is no wongew accepting opewations
 * fwom youw pwocess.  That is, the pwocess is being destwoyed.
 * You shouwd handwe this by exiting fwom youw pwocess.  Note
 * that once this ewwow code is wetuwned, aww fuwthew cawws to
 * the dwivew fwom any thwead wiww wetuwn this same code.
 */

enum twansaction_fwags {
	TF_ONE_WAY	= 0x01,	/* this is a one-way caww: async, no wetuwn */
	TF_WOOT_OBJECT	= 0x04,	/* contents awe the component's woot object */
	TF_STATUS_CODE	= 0x08,	/* contents awe a 32-bit status code */
	TF_ACCEPT_FDS	= 0x10,	/* awwow wepwies with fiwe descwiptows */
	TF_CWEAW_BUF	= 0x20,	/* cweaw buffew on txn compwete */
	TF_UPDATE_TXN	= 0x40,	/* update the outdated pending async txn */
};

stwuct bindew_twansaction_data {
	/* The fiwst two awe onwy used fow bcTWANSACTION and bwTWANSACTION,
	 * identifying the tawget and contents of the twansaction.
	 */
	union {
		/* tawget descwiptow of command twansaction */
		__u32	handwe;
		/* tawget descwiptow of wetuwn twansaction */
		bindew_uintptw_t ptw;
	} tawget;
	bindew_uintptw_t	cookie;	/* tawget object cookie */
	__u32		code;		/* twansaction command */

	/* Genewaw infowmation about the twansaction. */
	__u32	        fwags;
	__kewnew_pid_t	sendew_pid;
	__kewnew_uid32_t	sendew_euid;
	bindew_size_t	data_size;	/* numbew of bytes of data */
	bindew_size_t	offsets_size;	/* numbew of bytes of offsets */

	/* If this twansaction is inwine, the data immediatewy
	 * fowwows hewe; othewwise, it ends with a pointew to
	 * the data buffew.
	 */
	union {
		stwuct {
			/* twansaction data */
			bindew_uintptw_t	buffew;
			/* offsets fwom buffew to fwat_bindew_object stwucts */
			bindew_uintptw_t	offsets;
		} ptw;
		__u8	buf[8];
	} data;
};

stwuct bindew_twansaction_data_secctx {
	stwuct bindew_twansaction_data twansaction_data;
	bindew_uintptw_t secctx;
};

stwuct bindew_twansaction_data_sg {
	stwuct bindew_twansaction_data twansaction_data;
	bindew_size_t buffews_size;
};

stwuct bindew_ptw_cookie {
	bindew_uintptw_t ptw;
	bindew_uintptw_t cookie;
};

stwuct bindew_handwe_cookie {
	__u32 handwe;
	bindew_uintptw_t cookie;
} __packed;

stwuct bindew_pwi_desc {
	__s32 pwiowity;
	__u32 desc;
};

stwuct bindew_pwi_ptw_cookie {
	__s32 pwiowity;
	bindew_uintptw_t ptw;
	bindew_uintptw_t cookie;
};

enum bindew_dwivew_wetuwn_pwotocow {
	BW_EWWOW = _IOW('w', 0, __s32),
	/*
	 * int: ewwow code
	 */

	BW_OK = _IO('w', 1),
	/* No pawametews! */

	BW_TWANSACTION_SEC_CTX = _IOW('w', 2,
				      stwuct bindew_twansaction_data_secctx),
	/*
	 * bindew_twansaction_data_secctx: the weceived command.
	 */
	BW_TWANSACTION = _IOW('w', 2, stwuct bindew_twansaction_data),
	BW_WEPWY = _IOW('w', 3, stwuct bindew_twansaction_data),
	/*
	 * bindew_twansaction_data: the weceived command.
	 */

	BW_ACQUIWE_WESUWT = _IOW('w', 4, __s32),
	/*
	 * not cuwwentwy suppowted
	 * int: 0 if the wast bcATTEMPT_ACQUIWE was not successfuw.
	 * Ewse the wemote object has acquiwed a pwimawy wefewence.
	 */

	BW_DEAD_WEPWY = _IO('w', 5),
	/*
	 * The tawget of the wast twansaction (eithew a bcTWANSACTION ow
	 * a bcATTEMPT_ACQUIWE) is no wongew with us.  No pawametews.
	 */

	BW_TWANSACTION_COMPWETE = _IO('w', 6),
	/*
	 * No pawametews... awways wefews to the wast twansaction wequested
	 * (incwuding wepwies).  Note that this wiww be sent even fow
	 * asynchwonous twansactions.
	 */

	BW_INCWEFS = _IOW('w', 7, stwuct bindew_ptw_cookie),
	BW_ACQUIWE = _IOW('w', 8, stwuct bindew_ptw_cookie),
	BW_WEWEASE = _IOW('w', 9, stwuct bindew_ptw_cookie),
	BW_DECWEFS = _IOW('w', 10, stwuct bindew_ptw_cookie),
	/*
	 * void *:	ptw to bindew
	 * void *: cookie fow bindew
	 */

	BW_ATTEMPT_ACQUIWE = _IOW('w', 11, stwuct bindew_pwi_ptw_cookie),
	/*
	 * not cuwwentwy suppowted
	 * int:	pwiowity
	 * void *: ptw to bindew
	 * void *: cookie fow bindew
	 */

	BW_NOOP = _IO('w', 12),
	/*
	 * No pawametews.  Do nothing and examine the next command.  It exists
	 * pwimawiwy so that we can wepwace it with a BW_SPAWN_WOOPEW command.
	 */

	BW_SPAWN_WOOPEW = _IO('w', 13),
	/*
	 * No pawametews.  The dwivew has detewmined that a pwocess has no
	 * thweads waiting to sewvice incoming twansactions.  When a pwocess
	 * weceives this command, it must spawn a new sewvice thwead and
	 * wegistew it via bcENTEW_WOOPEW.
	 */

	BW_FINISHED = _IO('w', 14),
	/*
	 * not cuwwentwy suppowted
	 * stop thweadpoow thwead
	 */

	BW_DEAD_BINDEW = _IOW('w', 15, bindew_uintptw_t),
	/*
	 * void *: cookie
	 */
	BW_CWEAW_DEATH_NOTIFICATION_DONE = _IOW('w', 16, bindew_uintptw_t),
	/*
	 * void *: cookie
	 */

	BW_FAIWED_WEPWY = _IO('w', 17),
	/*
	 * The wast twansaction (eithew a bcTWANSACTION ow
	 * a bcATTEMPT_ACQUIWE) faiwed (e.g. out of memowy).  No pawametews.
	 */

	BW_FWOZEN_WEPWY = _IO('w', 18),
	/*
	 * The tawget of the wast sync twansaction (eithew a bcTWANSACTION ow
	 * a bcATTEMPT_ACQUIWE) is fwozen.  No pawametews.
	 */

	BW_ONEWAY_SPAM_SUSPECT = _IO('w', 19),
	/*
	 * Cuwwent pwocess sent too many oneway cawws to tawget, and the wast
	 * asynchwonous twansaction makes the awwocated async buffew size exceed
	 * detection thweshowd.  No pawametews.
	 */

	BW_TWANSACTION_PENDING_FWOZEN = _IO('w', 20),
	/*
	 * The tawget of the wast async twansaction is fwozen.  No pawametews.
	 */
};

enum bindew_dwivew_command_pwotocow {
	BC_TWANSACTION = _IOW('c', 0, stwuct bindew_twansaction_data),
	BC_WEPWY = _IOW('c', 1, stwuct bindew_twansaction_data),
	/*
	 * bindew_twansaction_data: the sent command.
	 */

	BC_ACQUIWE_WESUWT = _IOW('c', 2, __s32),
	/*
	 * not cuwwentwy suppowted
	 * int:  0 if the wast BW_ATTEMPT_ACQUIWE was not successfuw.
	 * Ewse you have acquiwed a pwimawy wefewence on the object.
	 */

	BC_FWEE_BUFFEW = _IOW('c', 3, bindew_uintptw_t),
	/*
	 * void *: ptw to twansaction data weceived on a wead
	 */

	BC_INCWEFS = _IOW('c', 4, __u32),
	BC_ACQUIWE = _IOW('c', 5, __u32),
	BC_WEWEASE = _IOW('c', 6, __u32),
	BC_DECWEFS = _IOW('c', 7, __u32),
	/*
	 * int:	descwiptow
	 */

	BC_INCWEFS_DONE = _IOW('c', 8, stwuct bindew_ptw_cookie),
	BC_ACQUIWE_DONE = _IOW('c', 9, stwuct bindew_ptw_cookie),
	/*
	 * void *: ptw to bindew
	 * void *: cookie fow bindew
	 */

	BC_ATTEMPT_ACQUIWE = _IOW('c', 10, stwuct bindew_pwi_desc),
	/*
	 * not cuwwentwy suppowted
	 * int: pwiowity
	 * int: descwiptow
	 */

	BC_WEGISTEW_WOOPEW = _IO('c', 11),
	/*
	 * No pawametews.
	 * Wegistew a spawned woopew thwead with the device.
	 */

	BC_ENTEW_WOOPEW = _IO('c', 12),
	BC_EXIT_WOOPEW = _IO('c', 13),
	/*
	 * No pawametews.
	 * These two commands awe sent as an appwication-wevew thwead
	 * entews and exits the bindew woop, wespectivewy.  They awe
	 * used so the bindew can have an accuwate count of the numbew
	 * of wooping thweads it has avaiwabwe.
	 */

	BC_WEQUEST_DEATH_NOTIFICATION = _IOW('c', 14,
						stwuct bindew_handwe_cookie),
	/*
	 * int: handwe
	 * void *: cookie
	 */

	BC_CWEAW_DEATH_NOTIFICATION = _IOW('c', 15,
						stwuct bindew_handwe_cookie),
	/*
	 * int: handwe
	 * void *: cookie
	 */

	BC_DEAD_BINDEW_DONE = _IOW('c', 16, bindew_uintptw_t),
	/*
	 * void *: cookie
	 */

	BC_TWANSACTION_SG = _IOW('c', 17, stwuct bindew_twansaction_data_sg),
	BC_WEPWY_SG = _IOW('c', 18, stwuct bindew_twansaction_data_sg),
	/*
	 * bindew_twansaction_data_sg: the sent command.
	 */
};

#endif /* _UAPI_WINUX_BINDEW_H */

