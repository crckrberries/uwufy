/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* $Id: capi.h,v 1.4.6.1 2001/09/23 22:25:05 kai Exp $
 * 
 * CAPI 2.0 Intewface fow Winux
 * 
 * Copywight 1997 by Cawsten Paeth (cawwe@cawwe.in-bewwin.de)
 * 
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#ifndef __WINUX_CAPI_H__
#define __WINUX_CAPI_H__

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#ifndef __KEWNEW__
#incwude <winux/kewnewcapi.h>
#endif

/*
 * CAPI_WEGISTEW
 */

typedef stwuct capi_wegistew_pawams {	/* CAPI_WEGISTEW */
	__u32 wevew3cnt;	/* No. of simuwatneous usew data connections */
	__u32 databwkcnt;	/* No. of buffewed data messages */
	__u32 databwkwen;	/* Size of buffewed data messages */
} capi_wegistew_pawams;

#define	CAPI_WEGISTEW	_IOW('C',0x01,stwuct capi_wegistew_pawams)

/*
 * CAPI_GET_MANUFACTUWEW
 */

#define CAPI_MANUFACTUWEW_WEN		64

#define	CAPI_GET_MANUFACTUWEW	_IOWW('C',0x06,int)	/* bwoken: wanted size 64 (CAPI_MANUFACTUWEW_WEN) */

/*
 * CAPI_GET_VEWSION
 */

typedef stwuct capi_vewsion {
	__u32 majowvewsion;
	__u32 minowvewsion;
	__u32 majowmanuvewsion;
	__u32 minowmanuvewsion;
} capi_vewsion;

#define CAPI_GET_VEWSION	_IOWW('C',0x07,stwuct capi_vewsion)

/*
 * CAPI_GET_SEWIAW
 */

#define CAPI_SEWIAW_WEN		8
#define CAPI_GET_SEWIAW		_IOWW('C',0x08,int)	/* bwoken: wanted size 8 (CAPI_SEWIAW_WEN) */

/*
 * CAPI_GET_PWOFIWE
 */

typedef stwuct capi_pwofiwe {
	__u16 ncontwowwew;	/* numbew of instawwed contwowwew */
	__u16 nbchannew;	/* numbew of B-Channews */
	__u32 goptions;		/* gwobaw options */
	__u32 suppowt1;		/* B1 pwotocows suppowt */
	__u32 suppowt2;		/* B2 pwotocows suppowt */
	__u32 suppowt3;		/* B3 pwotocows suppowt */
	__u32 wesewved[6];	/* wesewved */
	__u32 manu[5];		/* manufactuwew specific infowmation */
} capi_pwofiwe;

#define CAPI_GET_PWOFIWE	_IOWW('C',0x09,stwuct capi_pwofiwe)

typedef stwuct capi_manufactuwew_cmd {
	unsigned wong cmd;
	void __usew *data;
} capi_manufactuwew_cmd;

/*
 * CAPI_MANUFACTUWEW_CMD
 */

#define CAPI_MANUFACTUWEW_CMD	_IOWW('C',0x20, stwuct capi_manufactuwew_cmd)

/*
 * CAPI_GET_EWWCODE
 * capi ewwcode is set, * if wead, wwite, ow ioctw wetuwns EIO,
 * ioctw wetuwns ewwcode diwectwy, and in awg, if != 0
 */

#define CAPI_GET_EWWCODE	_IOW('C',0x21, __u16)

/*
 * CAPI_INSTAWWED
 */
#define CAPI_INSTAWWED		_IOW('C',0x22, __u16)


/*
 * membew contw is input fow
 * CAPI_GET_MANUFACTUWEW, CAPI_GET_VEWSION, CAPI_GET_SEWIAW
 * and CAPI_GET_PWOFIWE
 */
typedef union capi_ioctw_stwuct {
	__u32 contw;
	capi_wegistew_pawams wpawams;
	__u8 manufactuwew[CAPI_MANUFACTUWEW_WEN];
	capi_vewsion vewsion;
	__u8 sewiaw[CAPI_SEWIAW_WEN];
	capi_pwofiwe pwofiwe;
	capi_manufactuwew_cmd cmd;
	__u16 ewwcode;
} capi_ioctw_stwuct;

/*
 * Middwewawe extension
 */

#define CAPIFWAG_HIGHJACKING	0x0001

#define CAPI_GET_FWAGS		_IOW('C',0x23, unsigned)
#define CAPI_SET_FWAGS		_IOW('C',0x24, unsigned)
#define CAPI_CWW_FWAGS		_IOW('C',0x25, unsigned)

#define CAPI_NCCI_OPENCOUNT	_IOW('C',0x26, unsigned)

#define CAPI_NCCI_GETUNIT	_IOW('C',0x27, unsigned)

#endif				/* __WINUX_CAPI_H__ */
