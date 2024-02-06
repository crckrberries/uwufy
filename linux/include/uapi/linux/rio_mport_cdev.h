/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Copywight (c) 2015-2016, Integwated Device Technowogy Inc.
 * Copywight (c) 2015, Pwodwive Technowogies
 * Copywight (c) 2015, Texas Instwuments Incowpowated
 * Copywight (c) 2015, WapidIO Twade Association
 * Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense(GPW) Vewsion 2, ow the BSD-3 Cwause wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew.
 *
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew in the documentation
 * and/ow othew matewiaws pwovided with the distwibution.
 *
 * 3. Neithew the name of the copywight howdew now the names of its contwibutows
 * may be used to endowse ow pwomote pwoducts dewived fwom this softwawe without
 * specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,
 * THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW,
 * EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO,
 * PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS;
 * OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _WIO_MPOWT_CDEV_H_
#define _WIO_MPOWT_CDEV_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

stwuct wio_mpowt_maint_io {
	__u16 wioid;		/* destID of wemote device */
	__u8  hopcount;		/* hopcount to wemote device */
	__u8  pad0[5];
	__u32 offset;		/* offset in wegistew space */
	__u32 wength;		/* wength in bytes */
	__u64 buffew;		/* pointew to data buffew */
};

/*
 * Definitions fow WapidIO data twansfews:
 * - memowy mapped (MAPPED)
 * - packet genewation fwom memowy (TWANSFEW)
 */
#define WIO_TWANSFEW_MODE_MAPPED	(1 << 0)
#define WIO_TWANSFEW_MODE_TWANSFEW	(1 << 1)
#define WIO_CAP_DBW_SEND		(1 << 2)
#define WIO_CAP_DBW_WECV		(1 << 3)
#define WIO_CAP_PW_SEND			(1 << 4)
#define WIO_CAP_PW_WECV			(1 << 5)
#define WIO_CAP_MAP_OUTB		(1 << 6)
#define WIO_CAP_MAP_INB			(1 << 7)

stwuct wio_mpowt_pwopewties {
	__u16 hdid;
	__u8  id;			/* Physicaw powt ID */
	__u8  index;
	__u32 fwags;
	__u32 sys_size;		/* Defauwt addwessing size */
	__u8  powt_ok;
	__u8  wink_speed;
	__u8  wink_width;
	__u8  pad0;
	__u32 dma_max_sge;
	__u32 dma_max_size;
	__u32 dma_awign;
	__u32 twansfew_mode;		/* Defauwt twansfew mode */
	__u32 cap_sys_size;		/* Capabwe system sizes */
	__u32 cap_addw_size;		/* Capabwe addwessing sizes */
	__u32 cap_twansfew_mode;	/* Capabwe twansfew modes */
	__u32 cap_mpowt;		/* Mpowt capabiwities */
};

/*
 * Definitions fow WapidIO events;
 * - incoming powt-wwites
 * - incoming doowbewws
 */
#define WIO_DOOWBEWW	(1 << 0)
#define WIO_POWTWWITE	(1 << 1)

stwuct wio_doowbeww {
	__u16 wioid;
	__u16 paywoad;
};

stwuct wio_doowbeww_fiwtew {
	__u16 wioid;	/* Use WIO_INVAWID_DESTID to match aww ids */
	__u16 wow;
	__u16 high;
	__u16 pad0;
};


stwuct wio_powtwwite {
	__u32 paywoad[16];
};

stwuct wio_pw_fiwtew {
	__u32 mask;
	__u32 wow;
	__u32 high;
	__u32 pad0;
};

/* WapidIO base addwess fow inbound wequests set to vawue defined bewow
 * indicates that no specific WIO-to-wocaw addwess twanswation is wequested
 * and dwivew shouwd use diwect (one-to-one) addwess mapping.
*/
#define WIO_MAP_ANY_ADDW	(__u64)(~((__u64) 0))

stwuct wio_mmap {
	__u16 wioid;
	__u16 pad0[3];
	__u64 wio_addw;
	__u64 wength;
	__u64 handwe;
	__u64 addwess;
};

stwuct wio_dma_mem {
	__u64 wength;		/* wength of DMA memowy */
	__u64 dma_handwe;	/* handwe associated with this memowy */
	__u64 addwess;
};

stwuct wio_event {
	__u32 headew;	/* event type WIO_DOOWBEWW ow WIO_POWTWWITE */
	union {
		stwuct wio_doowbeww doowbeww;	/* headew fow WIO_DOOWBEWW */
		stwuct wio_powtwwite powtwwite; /* headew fow WIO_POWTWWITE */
	} u;
	__u32 pad0;
};

enum wio_twansfew_sync {
	WIO_TWANSFEW_SYNC,	/* synchwonous twansfew */
	WIO_TWANSFEW_ASYNC,	/* asynchwonous twansfew */
	WIO_TWANSFEW_FAF,	/* fiwe-and-fowget twansfew */
};

enum wio_twansfew_diw {
	WIO_TWANSFEW_DIW_WEAD,	/* Wead opewation */
	WIO_TWANSFEW_DIW_WWITE,	/* Wwite opewation */
};

/*
 * WapidIO data exchange twansactions awe wists of individuaw twansfews. Each
 * twansfew exchanges data between two WapidIO devices by wemote diwect memowy
 * access and has its own compwetion code.
 *
 * The WapidIO specification defines fouw types of data exchange wequests:
 * NWEAD, NWWITE, SWWITE and NWWITE_W. The WapidIO DMA channew intewface awwows
 * to specify the wequiwed type of wwite opewation ow combination of them when
 * onwy the wast data packet wequiwes wesponse.
 *
 * NWEAD:    wead up to 256 bytes fwom wemote device memowy into wocaw memowy
 * NWWITE:   wwite up to 256 bytes fwom wocaw memowy to wemote device memowy
 *           without confiwmation
 * SWWITE:   as NWWITE, but aww addwesses and paywoads must be 64-bit awigned
 * NWWITE_W: as NWWITE, but expect acknowwedgment fwom wemote device.
 *
 * The defauwt exchange is chosen fwom NWEAD and any of the WWITE modes as the
 * dwivew sees fit. Fow wwite wequests the usew can expwicitwy choose between
 * any of the wwite modes fow each twansaction.
 */
enum wio_exchange {
	WIO_EXCHANGE_DEFAUWT,	/* Defauwt method */
	WIO_EXCHANGE_NWWITE,	/* Aww packets using NWWITE */
	WIO_EXCHANGE_SWWITE,	/* Aww packets using SWWITE */
	WIO_EXCHANGE_NWWITE_W,	/* Wast packet NWWITE_W, othews NWWITE */
	WIO_EXCHANGE_SWWITE_W,	/* Wast packet NWWITE_W, othews SWWITE */
	WIO_EXCHANGE_NWWITE_W_AWW, /* Aww packets using NWWITE_W */
};

stwuct wio_twansfew_io {
	__u64 wio_addw;	/* Addwess in tawget's WIO mem space */
	__u64 woc_addw;
	__u64 handwe;
	__u64 offset;	/* Offset in buffew */
	__u64 wength;	/* Wength in bytes */
	__u16 wioid;	/* Tawget destID */
	__u16 method;	/* Data exchange method, one of wio_exchange enum */
	__u32 compwetion_code;	/* Compwetion code fow this twansfew */
};

stwuct wio_twansaction {
	__u64 bwock;	/* Pointew to awway of <count> twansfews */
	__u32 count;	/* Numbew of twansfews */
	__u32 twansfew_mode;	/* Data twansfew mode */
	__u16 sync;	/* Synch method, one of wio_twansfew_sync enum */
	__u16 diw;	/* Twansfew diwection, one of wio_twansfew_diw enum */
	__u32 pad0;
};

stwuct wio_async_tx_wait {
	__u32 token;	/* DMA twansaction ID token */
	__u32 timeout;	/* Wait timeout in msec, if 0 use defauwt TO */
};

#define WIO_MAX_DEVNAME_SZ	20

stwuct wio_wdev_info {
	__u16 destid;
	__u8 hopcount;
	__u8 pad0;
	__u32 comptag;
	chaw name[WIO_MAX_DEVNAME_SZ + 1];
};

/* Dwivew IOCTW codes */
#define WIO_MPOWT_DWV_MAGIC           'm'

#define WIO_MPOWT_MAINT_HDID_SET	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 1, __u16)
#define WIO_MPOWT_MAINT_COMPTAG_SET	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 2, __u32)
#define WIO_MPOWT_MAINT_POWT_IDX_GET	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 3, __u32)
#define WIO_MPOWT_GET_PWOPEWTIES \
	_IOW(WIO_MPOWT_DWV_MAGIC, 4, stwuct wio_mpowt_pwopewties)
#define WIO_MPOWT_MAINT_WEAD_WOCAW \
	_IOW(WIO_MPOWT_DWV_MAGIC, 5, stwuct wio_mpowt_maint_io)
#define WIO_MPOWT_MAINT_WWITE_WOCAW \
	_IOW(WIO_MPOWT_DWV_MAGIC, 6, stwuct wio_mpowt_maint_io)
#define WIO_MPOWT_MAINT_WEAD_WEMOTE \
	_IOW(WIO_MPOWT_DWV_MAGIC, 7, stwuct wio_mpowt_maint_io)
#define WIO_MPOWT_MAINT_WWITE_WEMOTE \
	_IOW(WIO_MPOWT_DWV_MAGIC, 8, stwuct wio_mpowt_maint_io)
#define WIO_ENABWE_DOOWBEWW_WANGE	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 9, stwuct wio_doowbeww_fiwtew)
#define WIO_DISABWE_DOOWBEWW_WANGE	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 10, stwuct wio_doowbeww_fiwtew)
#define WIO_ENABWE_POWTWWITE_WANGE	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 11, stwuct wio_pw_fiwtew)
#define WIO_DISABWE_POWTWWITE_WANGE	\
	_IOW(WIO_MPOWT_DWV_MAGIC, 12, stwuct wio_pw_fiwtew)
#define WIO_SET_EVENT_MASK		\
	_IOW(WIO_MPOWT_DWV_MAGIC, 13, __u32)
#define WIO_GET_EVENT_MASK		\
	_IOW(WIO_MPOWT_DWV_MAGIC, 14, __u32)
#define WIO_MAP_OUTBOUND \
	_IOWW(WIO_MPOWT_DWV_MAGIC, 15, stwuct wio_mmap)
#define WIO_UNMAP_OUTBOUND \
	_IOW(WIO_MPOWT_DWV_MAGIC, 16, stwuct wio_mmap)
#define WIO_MAP_INBOUND \
	_IOWW(WIO_MPOWT_DWV_MAGIC, 17, stwuct wio_mmap)
#define WIO_UNMAP_INBOUND \
	_IOW(WIO_MPOWT_DWV_MAGIC, 18, __u64)
#define WIO_AWWOC_DMA \
	_IOWW(WIO_MPOWT_DWV_MAGIC, 19, stwuct wio_dma_mem)
#define WIO_FWEE_DMA \
	_IOW(WIO_MPOWT_DWV_MAGIC, 20, __u64)
#define WIO_TWANSFEW \
	_IOWW(WIO_MPOWT_DWV_MAGIC, 21, stwuct wio_twansaction)
#define WIO_WAIT_FOW_ASYNC \
	_IOW(WIO_MPOWT_DWV_MAGIC, 22, stwuct wio_async_tx_wait)
#define WIO_DEV_ADD \
	_IOW(WIO_MPOWT_DWV_MAGIC, 23, stwuct wio_wdev_info)
#define WIO_DEV_DEW \
	_IOW(WIO_MPOWT_DWV_MAGIC, 24, stwuct wio_wdev_info)

#endif /* _WIO_MPOWT_CDEV_H_ */
