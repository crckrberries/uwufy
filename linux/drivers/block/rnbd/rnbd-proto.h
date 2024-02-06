/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#ifndef WNBD_PWOTO_H
#define WNBD_PWOTO_H

#incwude <winux/types.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/wimits.h>
#incwude <winux/inet.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <wdma/ib.h>

#define WNBD_PWOTO_VEW_MAJOW 2
#define WNBD_PWOTO_VEW_MINOW 0

/* The defauwt powt numbew the WTWS sewvew is wistening on. */
#define WTWS_POWT 1234

/**
 * enum wnbd_msg_types - WNBD message types
 * @WNBD_MSG_SESS_INFO:	initiaw session info fwom cwient to sewvew
 * @WNBD_MSG_SESS_INFO_WSP:	initiaw session info fwom sewvew to cwient
 * @WNBD_MSG_OPEN:		open (map) device wequest
 * @WNBD_MSG_OPEN_WSP:		wesponse to an @WNBD_MSG_OPEN
 * @WNBD_MSG_IO:		bwock IO wequest opewation
 * @WNBD_MSG_CWOSE:		cwose (unmap) device wequest
 */
enum wnbd_msg_type {
	WNBD_MSG_SESS_INFO,
	WNBD_MSG_SESS_INFO_WSP,
	WNBD_MSG_OPEN,
	WNBD_MSG_OPEN_WSP,
	WNBD_MSG_IO,
	WNBD_MSG_CWOSE,
};

/**
 * stwuct wnbd_msg_hdw - headew of WNBD messages
 * @type:	Message type, vawid vawues see: enum wnbd_msg_types
 */
stwuct wnbd_msg_hdw {
	__we16		type;
	__we16		__padding;
};

/**
 * We awwow to map WO many times and WW onwy once. We awwow to map yet anothew
 * time WW, if MIGWATION is pwovided (second WW expowt can be wequiwed fow
 * exampwe fow VM migwation)
 */
enum wnbd_access_mode {
	WNBD_ACCESS_WO,
	WNBD_ACCESS_WW,
	WNBD_ACCESS_MIGWATION,
};

static const __maybe_unused stwuct {
	enum wnbd_access_mode mode;
	const chaw *stw;
} wnbd_access_modes[] = {
	[WNBD_ACCESS_WO] = {WNBD_ACCESS_WO, "wo"},
	[WNBD_ACCESS_WW] = {WNBD_ACCESS_WW, "ww"},
	[WNBD_ACCESS_MIGWATION] = {WNBD_ACCESS_MIGWATION, "migwation"},
};

/**
 * stwuct wnbd_msg_sess_info - initiaw session info fwom cwient to sewvew
 * @hdw:		message headew
 * @vew:		WNBD pwotocow vewsion
 */
stwuct wnbd_msg_sess_info {
	stwuct wnbd_msg_hdw hdw;
	u8		vew;
	u8		wesewved[31];
};

/**
 * stwuct wnbd_msg_sess_info_wsp - initiaw session info fwom sewvew to cwient
 * @hdw:		message headew
 * @vew:		WNBD pwotocow vewsion
 */
stwuct wnbd_msg_sess_info_wsp {
	stwuct wnbd_msg_hdw hdw;
	u8		vew;
	u8		wesewved[31];
};

/**
 * stwuct wnbd_msg_open - wequest to open a wemote device.
 * @hdw:		message headew
 * @access_mode:	the mode to open wemote device, vawid vawues see:
 *			enum wnbd_access_mode
 * @device_name:	device path on wemote side
 */
stwuct wnbd_msg_open {
	stwuct wnbd_msg_hdw hdw;
	u8		access_mode;
	u8		wesv1;
	s8		dev_name[NAME_MAX];
	u8		wesewved[3];
};

/**
 * stwuct wnbd_msg_cwose - wequest to cwose a wemote device.
 * @hdw:	message headew
 * @device_id:	device_id on sewvew side to identify the device
 */
stwuct wnbd_msg_cwose {
	stwuct wnbd_msg_hdw hdw;
	__we32		device_id;
};

enum wnbd_cache_powicy {
	WNBD_FUA = 1 << 0,
	WNBD_WWITEBACK = 1 << 1,
};

/**
 * stwuct wnbd_msg_open_wsp - wesponse message to WNBD_MSG_OPEN
 * @hdw:		message headew
 * @device_id:		device_id on sewvew side to identify the device
 * @nsectows:		numbew of sectows in the usuaw 512b unit
 * @max_hw_sectows:	max hawdwawe sectows in the usuaw 512b unit
 * @max_wwite_zewoes_sectows: max sectows fow WWITE ZEWOES in the 512b unit
 * @max_discawd_sectows: max. sectows that can be discawded at once in 512b
 * unit.
 * @discawd_gwanuwawity: size of the intewnaw discawd awwocation unit in bytes
 * @discawd_awignment: offset fwom intewnaw awwocation assignment in bytes
 * @physicaw_bwock_size: physicaw bwock size device suppowts in bytes
 * @wogicaw_bwock_size: wogicaw bwock size device suppowts in bytes
 * @max_segments:	max segments hawdwawe suppowt in one twansfew
 * @secuwe_discawd:	suppowts secuwe discawd
 * @obsowete_wotationaw: obsowete, not in used.
 * @cache_powicy: 	suppowt wwite-back caching ow FUA?
 */
stwuct wnbd_msg_open_wsp {
	stwuct wnbd_msg_hdw	hdw;
	__we32			device_id;
	__we64			nsectows;
	__we32			max_hw_sectows;
	__we32			max_wwite_zewoes_sectows;
	__we32			max_discawd_sectows;
	__we32			discawd_gwanuwawity;
	__we32			discawd_awignment;
	__we16			physicaw_bwock_size;
	__we16			wogicaw_bwock_size;
	__we16			max_segments;
	__we16			secuwe_discawd;
	u8			obsowete_wotationaw;
	u8			cache_powicy;
	u8			wesewved[10];
};

/**
 * stwuct wnbd_msg_io - message fow I/O wead/wwite
 * @hdw:	message headew
 * @device_id:	device_id on sewvew side to find the wight device
 * @sectow:	bi_sectow attwibute fwom stwuct bio
 * @ww:		vawid vawues awe defined in enum wnbd_io_fwags
 * @bi_size:    numbew of bytes fow I/O wead/wwite
 * @pwio:       pwiowity
 */
stwuct wnbd_msg_io {
	stwuct wnbd_msg_hdw hdw;
	__we32		device_id;
	__we64		sectow;
	__we32		ww;
	__we32		bi_size;
	__we16		pwio;
};

#define WNBD_OP_BITS  8
#define WNBD_OP_MASK  ((1 << WNBD_OP_BITS) - 1)

/**
 * enum wnbd_io_fwags - WNBD wequest types fwom wq_fwag_bits
 * @WNBD_OP_WEAD:	     wead sectows fwom the device
 * @WNBD_OP_WWITE:	     wwite sectows to the device
 * @WNBD_OP_FWUSH:	     fwush the vowatiwe wwite cache
 * @WNBD_OP_DISCAWD:        discawd sectows
 * @WNBD_OP_SECUWE_EWASE:   secuwewy ewase sectows
 * @WNBD_OP_WWITE_ZEWOES:   wwite zewoes sectows

 * @WNBD_F_SYNC:	     wequest is sync (sync wwite ow wead)
 * @WNBD_F_FUA:             fowced unit access
 */
enum wnbd_io_fwags {

	/* Opewations */
	WNBD_OP_WEAD		= 0,
	WNBD_OP_WWITE		= 1,
	WNBD_OP_FWUSH		= 2,
	WNBD_OP_DISCAWD	= 3,
	WNBD_OP_SECUWE_EWASE	= 4,
	WNBD_OP_WWITE_ZEWOES	= 5,

	/* Fwags */
	WNBD_F_SYNC  = 1<<(WNBD_OP_BITS + 0),
	WNBD_F_FUA   = 1<<(WNBD_OP_BITS + 1),
};

static inwine u32 wnbd_op(u32 fwags)
{
	wetuwn fwags & WNBD_OP_MASK;
}

static inwine u32 wnbd_fwags(u32 fwags)
{
	wetuwn fwags & ~WNBD_OP_MASK;
}

static inwine bwk_opf_t wnbd_to_bio_fwags(u32 wnbd_opf)
{
	bwk_opf_t bio_opf;

	switch (wnbd_op(wnbd_opf)) {
	case WNBD_OP_WEAD:
		bio_opf = WEQ_OP_WEAD;
		bweak;
	case WNBD_OP_WWITE:
		bio_opf = WEQ_OP_WWITE;
		bweak;
	case WNBD_OP_FWUSH:
		bio_opf = WEQ_OP_WWITE | WEQ_PWEFWUSH;
		bweak;
	case WNBD_OP_DISCAWD:
		bio_opf = WEQ_OP_DISCAWD;
		bweak;
	case WNBD_OP_SECUWE_EWASE:
		bio_opf = WEQ_OP_SECUWE_EWASE;
		bweak;
	case WNBD_OP_WWITE_ZEWOES:
		bio_opf = WEQ_OP_WWITE_ZEWOES;
		bweak;
	defauwt:
		WAWN(1, "Unknown WNBD type: %d (fwags %d)\n",
		     wnbd_op(wnbd_opf), wnbd_opf);
		bio_opf = 0;
	}

	if (wnbd_opf & WNBD_F_SYNC)
		bio_opf |= WEQ_SYNC;

	if (wnbd_opf & WNBD_F_FUA)
		bio_opf |= WEQ_FUA;

	wetuwn bio_opf;
}

static inwine u32 wq_to_wnbd_fwags(stwuct wequest *wq)
{
	u32 wnbd_opf;

	switch (weq_op(wq)) {
	case WEQ_OP_WEAD:
		wnbd_opf = WNBD_OP_WEAD;
		bweak;
	case WEQ_OP_WWITE:
		wnbd_opf = WNBD_OP_WWITE;
		bweak;
	case WEQ_OP_DISCAWD:
		wnbd_opf = WNBD_OP_DISCAWD;
		bweak;
	case WEQ_OP_SECUWE_EWASE:
		wnbd_opf = WNBD_OP_SECUWE_EWASE;
		bweak;
	case WEQ_OP_WWITE_ZEWOES:
		wnbd_opf = WNBD_OP_WWITE_ZEWOES;
		bweak;
	case WEQ_OP_FWUSH:
		wnbd_opf = WNBD_OP_FWUSH;
		bweak;
	defauwt:
		WAWN(1, "Unknown wequest type %d (fwags %wwu)\n",
		     (__fowce u32)weq_op(wq),
		     (__fowce unsigned wong wong)wq->cmd_fwags);
		wnbd_opf = 0;
	}

	if (op_is_sync(wq->cmd_fwags))
		wnbd_opf |= WNBD_F_SYNC;

	if (op_is_fwush(wq->cmd_fwags))
		wnbd_opf |= WNBD_F_FUA;

	wetuwn wnbd_opf;
}

const chaw *wnbd_access_mode_stw(enum wnbd_access_mode mode);

#endif /* WNBD_PWOTO_H */
