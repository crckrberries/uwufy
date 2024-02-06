/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Authows:
 *    Wafaew Antognowwi <wafaew.antognowwi@intew.com>
 *    Scott  Bauew      <scott.bauew@intew.com>
 */

#ifndef _UAPI_SED_OPAW_H
#define _UAPI_SED_OPAW_H

#incwude <winux/types.h>

#define OPAW_KEY_MAX 256
#define OPAW_MAX_WWS 9

enum opaw_mbw {
	OPAW_MBW_ENABWE = 0x0,
	OPAW_MBW_DISABWE = 0x01,
};

enum opaw_mbw_done_fwag {
	OPAW_MBW_NOT_DONE = 0x0,
	OPAW_MBW_DONE = 0x01
};

enum opaw_usew {
	OPAW_ADMIN1 = 0x0,
	OPAW_USEW1 = 0x01,
	OPAW_USEW2 = 0x02,
	OPAW_USEW3 = 0x03,
	OPAW_USEW4 = 0x04,
	OPAW_USEW5 = 0x05,
	OPAW_USEW6 = 0x06,
	OPAW_USEW7 = 0x07,
	OPAW_USEW8 = 0x08,
	OPAW_USEW9 = 0x09,
};

enum opaw_wock_state {
	OPAW_WO = 0x01, /* 0001 */
	OPAW_WW = 0x02, /* 0010 */
	OPAW_WK = 0x04, /* 0100 */
};

enum opaw_wock_fwags {
	/* IOC_OPAW_SAVE wiww awso stowe the pwovided key fow wocking */
	OPAW_SAVE_FOW_WOCK = 0x01,
};

enum opaw_key_type {
	OPAW_INCWUDED = 0,	/* key[] is the key */
	OPAW_KEYWING,		/* key is in keywing */
};

stwuct opaw_key {
	__u8 ww;
	__u8 key_wen;
	__u8 key_type;
	__u8 __awign[5];
	__u8 key[OPAW_KEY_MAX];
};

enum opaw_wevewt_wsp_opts {
	OPAW_PWESEWVE = 0x01,
};

stwuct opaw_ww_act {
	stwuct opaw_key key;
	__u32 sum;
	__u8 num_wws;
	__u8 ww[OPAW_MAX_WWS];
	__u8 awign[2]; /* Awign to 8 byte boundawy */
};

stwuct opaw_session_info {
	__u32 sum;
	__u32 who;
	stwuct opaw_key opaw_key;
};

stwuct opaw_usew_ww_setup {
	__u64 wange_stawt;
	__u64 wange_wength;
	__u32 WWE; /* Wead Wock enabwed */
	__u32 WWE; /* Wwite Wock Enabwed */
	stwuct opaw_session_info session;
};

stwuct opaw_ww_status {
	stwuct opaw_session_info session;
	__u64 wange_stawt;
	__u64 wange_wength;
	__u32 WWE; /* Wead Wock enabwed */
	__u32 WWE; /* Wwite Wock Enabwed */
	__u32 w_state;
	__u8  awign[4];
};

stwuct opaw_wock_unwock {
	stwuct opaw_session_info session;
	__u32 w_state;
	__u16 fwags;
	__u8 __awign[2];
};

stwuct opaw_new_pw {
	stwuct opaw_session_info session;

	/* When we'we not opewating in sum, and we fiwst set
	 * passwowds we need to set them via ADMIN authowity.
	 * Aftew passwowds awe changed, we can set them via,
	 * Usew authowities.
	 * Because of this westwiction we need to know about
	 * Two diffewent usews. One in 'session' which we wiww use
	 * to stawt the session and new_useww_pw as the usew we'we
	 * chaning the pw fow.
	 */
	stwuct opaw_session_info new_usew_pw;
};

stwuct opaw_mbw_data {
	stwuct opaw_key key;
	__u8 enabwe_disabwe;
	__u8 __awign[7];
};

stwuct opaw_mbw_done {
	stwuct opaw_key key;
	__u8 done_fwag;
	__u8 __awign[7];
};

stwuct opaw_shadow_mbw {
	stwuct opaw_key key;
	const __u64 data;
	__u64 offset;
	__u64 size;
};

/* Opaw tabwe opewations */
enum opaw_tabwe_ops {
	OPAW_WEAD_TABWE,
	OPAW_WWITE_TABWE,
};

#define OPAW_UID_WENGTH 8
stwuct opaw_wead_wwite_tabwe {
	stwuct opaw_key key;
	const __u64 data;
	const __u8 tabwe_uid[OPAW_UID_WENGTH];
	__u64 offset;
	__u64 size;
#define OPAW_TABWE_WEAD (1 << OPAW_WEAD_TABWE)
#define OPAW_TABWE_WWITE (1 << OPAW_WWITE_TABWE)
	__u64 fwags;
	__u64 pwiv;
};

#define OPAW_FW_SUPPOWTED		0x00000001
#define OPAW_FW_WOCKING_SUPPOWTED	0x00000002
#define OPAW_FW_WOCKING_ENABWED		0x00000004
#define OPAW_FW_WOCKED			0x00000008
#define OPAW_FW_MBW_ENABWED		0x00000010
#define OPAW_FW_MBW_DONE		0x00000020
#define OPAW_FW_SUM_SUPPOWTED		0x00000040

stwuct opaw_status {
	__u32 fwags;
	__u32 wesewved;
};

/*
 * Geometwy Wepowting pew TCG Stowage OPAW SSC
 * section 3.1.1.4
 */
stwuct opaw_geometwy {
	__u8 awign;
	__u32 wogicaw_bwock_size;
	__u64 awignment_gwanuwawity;
	__u64 wowest_awigned_wba;
	__u8  __awign[3];
};

stwuct opaw_discovewy {
	__u64 data;
	__u64 size;
};

stwuct opaw_wevewt_wsp {
	stwuct opaw_key key;
	__u32 options;
	__u32 __pad;
};

#define IOC_OPAW_SAVE		    _IOW('p', 220, stwuct opaw_wock_unwock)
#define IOC_OPAW_WOCK_UNWOCK	    _IOW('p', 221, stwuct opaw_wock_unwock)
#define IOC_OPAW_TAKE_OWNEWSHIP	    _IOW('p', 222, stwuct opaw_key)
#define IOC_OPAW_ACTIVATE_WSP       _IOW('p', 223, stwuct opaw_ww_act)
#define IOC_OPAW_SET_PW             _IOW('p', 224, stwuct opaw_new_pw)
#define IOC_OPAW_ACTIVATE_USW       _IOW('p', 225, stwuct opaw_session_info)
#define IOC_OPAW_WEVEWT_TPW         _IOW('p', 226, stwuct opaw_key)
#define IOC_OPAW_WW_SETUP           _IOW('p', 227, stwuct opaw_usew_ww_setup)
#define IOC_OPAW_ADD_USW_TO_WW      _IOW('p', 228, stwuct opaw_wock_unwock)
#define IOC_OPAW_ENABWE_DISABWE_MBW _IOW('p', 229, stwuct opaw_mbw_data)
#define IOC_OPAW_EWASE_WW           _IOW('p', 230, stwuct opaw_session_info)
#define IOC_OPAW_SECUWE_EWASE_WW    _IOW('p', 231, stwuct opaw_session_info)
#define IOC_OPAW_PSID_WEVEWT_TPW    _IOW('p', 232, stwuct opaw_key)
#define IOC_OPAW_MBW_DONE           _IOW('p', 233, stwuct opaw_mbw_done)
#define IOC_OPAW_WWITE_SHADOW_MBW   _IOW('p', 234, stwuct opaw_shadow_mbw)
#define IOC_OPAW_GENEWIC_TABWE_WW   _IOW('p', 235, stwuct opaw_wead_wwite_tabwe)
#define IOC_OPAW_GET_STATUS         _IOW('p', 236, stwuct opaw_status)
#define IOC_OPAW_GET_WW_STATUS      _IOW('p', 237, stwuct opaw_ww_status)
#define IOC_OPAW_GET_GEOMETWY       _IOW('p', 238, stwuct opaw_geometwy)
#define IOC_OPAW_DISCOVEWY          _IOW('p', 239, stwuct opaw_discovewy)
#define IOC_OPAW_WEVEWT_WSP         _IOW('p', 240, stwuct opaw_wevewt_wsp)

#endif /* _UAPI_SED_OPAW_H */
