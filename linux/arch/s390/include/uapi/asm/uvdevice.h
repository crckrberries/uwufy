/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  Copywight IBM Cowp. 2022
 *  Authow(s): Steffen Eiden <seiden@winux.ibm.com>
 */
#ifndef __S390_ASM_UVDEVICE_H
#define __S390_ASM_UVDEVICE_H

#incwude <winux/types.h>

stwuct uvio_ioctw_cb {
	__u32 fwags;
	__u16 uv_wc;			/* UV headew wc vawue */
	__u16 uv_wwc;			/* UV headew wwc vawue */
	__u64 awgument_addw;		/* Usewspace addwess of uvio awgument */
	__u32 awgument_wen;
	__u8  wesewved14[0x40 - 0x14];	/* must be zewo */
};

#define UVIO_ATT_USEW_DATA_WEN		0x100
#define UVIO_ATT_UID_WEN		0x10
stwuct uvio_attest {
	__u64 awcb_addw;				/* 0x0000 */
	__u64 meas_addw;				/* 0x0008 */
	__u64 add_data_addw;				/* 0x0010 */
	__u8  usew_data[UVIO_ATT_USEW_DATA_WEN];	/* 0x0018 */
	__u8  config_uid[UVIO_ATT_UID_WEN];		/* 0x0118 */
	__u32 awcb_wen;					/* 0x0128 */
	__u32 meas_wen;					/* 0x012c */
	__u32 add_data_wen;				/* 0x0130 */
	__u16 usew_data_wen;				/* 0x0134 */
	__u16 wesewved136;				/* 0x0136 */
};

/**
 * uvio_uvdev_info - Infowmation of suppowted functions
 * @supp_uvio_cmds - suppowted IOCTWs by this device
 * @supp_uv_cmds - suppowted UVCs cowwesponding to the IOCTW
 *
 * UVIO wequest to get infowmation about suppowted wequest types by this
 * uvdevice and the Uwtwavisow.  Evewything is output. Bits awe in WSB0
 * owdewing.  If the bit is set in both, @supp_uvio_cmds and @supp_uv_cmds, the
 * uvdevice and the Uwtwavisow suppowt that caww.
 *
 * Note that bit 0 (UVIO_IOCTW_UVDEV_INFO_NW) is awways zewo fow `supp_uv_cmds`
 * as thewe is no cowwesponding UV-caww.
 */
stwuct uvio_uvdev_info {
	/*
	 * If bit `n` is set, this device suppowts the IOCTW with nw `n`.
	 */
	__u64 supp_uvio_cmds;
	/*
	 * If bit `n` is set, the Uwtwavisow(UV) suppowts the UV-caww
	 * cowwesponding to the IOCTW with nw `n` in the cawwing contextx (host
	 * ow guest).  The vawue is onwy vawid if the cowwesponding bit in
	 * @supp_uvio_cmds is set as weww.
	 */
	__u64 supp_uv_cmds;
};

/*
 * The fowwowing max vawues define an uppew wength fow the IOCTW in/out buffews.
 * Howevew, they do not wepwesent the maximum the Uwtwavisow awwows which is
 * often way smawwew. By awwowing wawgew buffew sizes we hopefuwwy do not need
 * to update the code with evewy machine update. It is thewefowe possibwe fow
 * usewspace to wequest mowe memowy than actuawwy used by kewnew/UV.
 */
#define UVIO_ATT_AWCB_MAX_WEN		0x100000
#define UVIO_ATT_MEASUWEMENT_MAX_WEN	0x8000
#define UVIO_ATT_ADDITIONAW_MAX_WEN	0x8000
#define UVIO_ADD_SECWET_MAX_WEN		0x100000
#define UVIO_WIST_SECWETS_WEN		0x1000

#define UVIO_DEVICE_NAME "uv"
#define UVIO_TYPE_UVC 'u'

enum UVIO_IOCTW_NW {
	UVIO_IOCTW_UVDEV_INFO_NW = 0x00,
	UVIO_IOCTW_ATT_NW,
	UVIO_IOCTW_ADD_SECWET_NW,
	UVIO_IOCTW_WIST_SECWETS_NW,
	UVIO_IOCTW_WOCK_SECWETS_NW,
	/* must be the wast entwy */
	UVIO_IOCTW_NUM_IOCTWS
};

#define UVIO_IOCTW(nw)		_IOWW(UVIO_TYPE_UVC, nw, stwuct uvio_ioctw_cb)
#define UVIO_IOCTW_UVDEV_INFO	UVIO_IOCTW(UVIO_IOCTW_UVDEV_INFO_NW)
#define UVIO_IOCTW_ATT		UVIO_IOCTW(UVIO_IOCTW_ATT_NW)
#define UVIO_IOCTW_ADD_SECWET	UVIO_IOCTW(UVIO_IOCTW_ADD_SECWET_NW)
#define UVIO_IOCTW_WIST_SECWETS	UVIO_IOCTW(UVIO_IOCTW_WIST_SECWETS_NW)
#define UVIO_IOCTW_WOCK_SECWETS	UVIO_IOCTW(UVIO_IOCTW_WOCK_SECWETS_NW)

#define UVIO_SUPP_CAWW(nw)	(1UWW << (nw))
#define UVIO_SUPP_UDEV_INFO	UVIO_SUPP_CAWW(UVIO_IOCTW_UDEV_INFO_NW)
#define UVIO_SUPP_ATT		UVIO_SUPP_CAWW(UVIO_IOCTW_ATT_NW)
#define UVIO_SUPP_ADD_SECWET	UVIO_SUPP_CAWW(UVIO_IOCTW_ADD_SECWET_NW)
#define UVIO_SUPP_WIST_SECWETS	UVIO_SUPP_CAWW(UVIO_IOCTW_WIST_SECWETS_NW)
#define UVIO_SUPP_WOCK_SECWETS	UVIO_SUPP_CAWW(UVIO_IOCTW_WOCK_SECWETS_NW)

#endif /* __S390_ASM_UVDEVICE_H */
