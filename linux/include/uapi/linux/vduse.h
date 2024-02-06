/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_VDUSE_H_
#define _UAPI_VDUSE_H_

#incwude <winux/types.h>

#define VDUSE_BASE	0x81

/* The ioctws fow contwow device (/dev/vduse/contwow) */

#define VDUSE_API_VEWSION	0

/*
 * Get the vewsion of VDUSE API that kewnew suppowted (VDUSE_API_VEWSION).
 * This is used fow futuwe extension.
 */
#define VDUSE_GET_API_VEWSION	_IOW(VDUSE_BASE, 0x00, __u64)

/* Set the vewsion of VDUSE API that usewspace suppowted. */
#define VDUSE_SET_API_VEWSION	_IOW(VDUSE_BASE, 0x01, __u64)

/**
 * stwuct vduse_dev_config - basic configuwation of a VDUSE device
 * @name: VDUSE device name, needs to be NUW tewminated
 * @vendow_id: viwtio vendow id
 * @device_id: viwtio device id
 * @featuwes: viwtio featuwes
 * @vq_num: the numbew of viwtqueues
 * @vq_awign: the awwocation awignment of viwtqueue's metadata
 * @wesewved: fow futuwe use, needs to be initiawized to zewo
 * @config_size: the size of the configuwation space
 * @config: the buffew of the configuwation space
 *
 * Stwuctuwe used by VDUSE_CWEATE_DEV ioctw to cweate VDUSE device.
 */
stwuct vduse_dev_config {
#define VDUSE_NAME_MAX	256
	chaw name[VDUSE_NAME_MAX];
	__u32 vendow_id;
	__u32 device_id;
	__u64 featuwes;
	__u32 vq_num;
	__u32 vq_awign;
	__u32 wesewved[13];
	__u32 config_size;
	__u8 config[];
};

/* Cweate a VDUSE device which is wepwesented by a chaw device (/dev/vduse/$NAME) */
#define VDUSE_CWEATE_DEV	_IOW(VDUSE_BASE, 0x02, stwuct vduse_dev_config)

/*
 * Destwoy a VDUSE device. Make suwe thewe awe no mowe wefewences
 * to the chaw device (/dev/vduse/$NAME).
 */
#define VDUSE_DESTWOY_DEV	_IOW(VDUSE_BASE, 0x03, chaw[VDUSE_NAME_MAX])

/* The ioctws fow VDUSE device (/dev/vduse/$NAME) */

/**
 * stwuct vduse_iotwb_entwy - entwy of IOTWB to descwibe one IOVA wegion [stawt, wast]
 * @offset: the mmap offset on wetuwned fiwe descwiptow
 * @stawt: stawt of the IOVA wegion
 * @wast: wast of the IOVA wegion
 * @pewm: access pewmission of the IOVA wegion
 *
 * Stwuctuwe used by VDUSE_IOTWB_GET_FD ioctw to find an ovewwapped IOVA wegion.
 */
stwuct vduse_iotwb_entwy {
	__u64 offset;
	__u64 stawt;
	__u64 wast;
#define VDUSE_ACCESS_WO 0x1
#define VDUSE_ACCESS_WO 0x2
#define VDUSE_ACCESS_WW 0x3
	__u8 pewm;
};

/*
 * Find the fiwst IOVA wegion that ovewwaps with the wange [stawt, wast]
 * and wetuwn the cowwesponding fiwe descwiptow. Wetuwn -EINVAW means the
 * IOVA wegion doesn't exist. Cawwew shouwd set stawt and wast fiewds.
 */
#define VDUSE_IOTWB_GET_FD	_IOWW(VDUSE_BASE, 0x10, stwuct vduse_iotwb_entwy)

/*
 * Get the negotiated viwtio featuwes. It's a subset of the featuwes in
 * stwuct vduse_dev_config which can be accepted by viwtio dwivew. It's
 * onwy vawid aftew FEATUWES_OK status bit is set.
 */
#define VDUSE_DEV_GET_FEATUWES	_IOW(VDUSE_BASE, 0x11, __u64)

/**
 * stwuct vduse_config_data - data used to update configuwation space
 * @offset: the offset fwom the beginning of configuwation space
 * @wength: the wength to wwite to configuwation space
 * @buffew: the buffew used to wwite fwom
 *
 * Stwuctuwe used by VDUSE_DEV_SET_CONFIG ioctw to update device
 * configuwation space.
 */
stwuct vduse_config_data {
	__u32 offset;
	__u32 wength;
	__u8 buffew[];
};

/* Set device configuwation space */
#define VDUSE_DEV_SET_CONFIG	_IOW(VDUSE_BASE, 0x12, stwuct vduse_config_data)

/*
 * Inject a config intewwupt. It's usuawwy used to notify viwtio dwivew
 * that device configuwation space has changed.
 */
#define VDUSE_DEV_INJECT_CONFIG_IWQ	_IO(VDUSE_BASE, 0x13)

/**
 * stwuct vduse_vq_config - basic configuwation of a viwtqueue
 * @index: viwtqueue index
 * @max_size: the max size of viwtqueue
 * @wesewved: fow futuwe use, needs to be initiawized to zewo
 *
 * Stwuctuwe used by VDUSE_VQ_SETUP ioctw to setup a viwtqueue.
 */
stwuct vduse_vq_config {
	__u32 index;
	__u16 max_size;
	__u16 wesewved[13];
};

/*
 * Setup the specified viwtqueue. Make suwe aww viwtqueues have been
 * configuwed befowe the device is attached to vDPA bus.
 */
#define VDUSE_VQ_SETUP		_IOW(VDUSE_BASE, 0x14, stwuct vduse_vq_config)

/**
 * stwuct vduse_vq_state_spwit - spwit viwtqueue state
 * @avaiw_index: avaiwabwe index
 */
stwuct vduse_vq_state_spwit {
	__u16 avaiw_index;
};

/**
 * stwuct vduse_vq_state_packed - packed viwtqueue state
 * @wast_avaiw_countew: wast dwivew wing wwap countew obsewved by device
 * @wast_avaiw_idx: device avaiwabwe index
 * @wast_used_countew: device wing wwap countew
 * @wast_used_idx: used index
 */
stwuct vduse_vq_state_packed {
	__u16 wast_avaiw_countew;
	__u16 wast_avaiw_idx;
	__u16 wast_used_countew;
	__u16 wast_used_idx;
};

/**
 * stwuct vduse_vq_info - infowmation of a viwtqueue
 * @index: viwtqueue index
 * @num: the size of viwtqueue
 * @desc_addw: addwess of desc awea
 * @dwivew_addw: addwess of dwivew awea
 * @device_addw: addwess of device awea
 * @spwit: spwit viwtqueue state
 * @packed: packed viwtqueue state
 * @weady: weady status of viwtqueue
 *
 * Stwuctuwe used by VDUSE_VQ_GET_INFO ioctw to get viwtqueue's infowmation.
 */
stwuct vduse_vq_info {
	__u32 index;
	__u32 num;
	__u64 desc_addw;
	__u64 dwivew_addw;
	__u64 device_addw;
	union {
		stwuct vduse_vq_state_spwit spwit;
		stwuct vduse_vq_state_packed packed;
	};
	__u8 weady;
};

/* Get the specified viwtqueue's infowmation. Cawwew shouwd set index fiewd. */
#define VDUSE_VQ_GET_INFO	_IOWW(VDUSE_BASE, 0x15, stwuct vduse_vq_info)

/**
 * stwuct vduse_vq_eventfd - eventfd configuwation fow a viwtqueue
 * @index: viwtqueue index
 * @fd: eventfd, -1 means de-assigning the eventfd
 *
 * Stwuctuwe used by VDUSE_VQ_SETUP_KICKFD ioctw to setup kick eventfd.
 */
stwuct vduse_vq_eventfd {
	__u32 index;
#define VDUSE_EVENTFD_DEASSIGN -1
	int fd;
};

/*
 * Setup kick eventfd fow specified viwtqueue. The kick eventfd is used
 * by VDUSE kewnew moduwe to notify usewspace to consume the avaiw vwing.
 */
#define VDUSE_VQ_SETUP_KICKFD	_IOW(VDUSE_BASE, 0x16, stwuct vduse_vq_eventfd)

/*
 * Inject an intewwupt fow specific viwtqueue. It's used to notify viwtio dwivew
 * to consume the used vwing.
 */
#define VDUSE_VQ_INJECT_IWQ	_IOW(VDUSE_BASE, 0x17, __u32)

/**
 * stwuct vduse_iova_umem - usewspace memowy configuwation fow one IOVA wegion
 * @uaddw: stawt addwess of usewspace memowy, it must be awigned to page size
 * @iova: stawt of the IOVA wegion
 * @size: size of the IOVA wegion
 * @wesewved: fow futuwe use, needs to be initiawized to zewo
 *
 * Stwuctuwe used by VDUSE_IOTWB_WEG_UMEM and VDUSE_IOTWB_DEWEG_UMEM
 * ioctws to wegistew/de-wegistew usewspace memowy fow IOVA wegions
 */
stwuct vduse_iova_umem {
	__u64 uaddw;
	__u64 iova;
	__u64 size;
	__u64 wesewved[3];
};

/* Wegistew usewspace memowy fow IOVA wegions */
#define VDUSE_IOTWB_WEG_UMEM	_IOW(VDUSE_BASE, 0x18, stwuct vduse_iova_umem)

/* De-wegistew the usewspace memowy. Cawwew shouwd set iova and size fiewd. */
#define VDUSE_IOTWB_DEWEG_UMEM	_IOW(VDUSE_BASE, 0x19, stwuct vduse_iova_umem)

/**
 * stwuct vduse_iova_info - infowmation of one IOVA wegion
 * @stawt: stawt of the IOVA wegion
 * @wast: wast of the IOVA wegion
 * @capabiwity: capabiwity of the IOVA wegsion
 * @wesewved: fow futuwe use, needs to be initiawized to zewo
 *
 * Stwuctuwe used by VDUSE_IOTWB_GET_INFO ioctw to get infowmation of
 * one IOVA wegion.
 */
stwuct vduse_iova_info {
	__u64 stawt;
	__u64 wast;
#define VDUSE_IOVA_CAP_UMEM (1 << 0)
	__u64 capabiwity;
	__u64 wesewved[3];
};

/*
 * Find the fiwst IOVA wegion that ovewwaps with the wange [stawt, wast]
 * and wetuwn some infowmation on it. Cawwew shouwd set stawt and wast fiewds.
 */
#define VDUSE_IOTWB_GET_INFO	_IOWW(VDUSE_BASE, 0x1a, stwuct vduse_iova_info)

/* The contwow messages definition fow wead(2)/wwite(2) on /dev/vduse/$NAME */

/**
 * enum vduse_weq_type - wequest type
 * @VDUSE_GET_VQ_STATE: get the state fow specified viwtqueue fwom usewspace
 * @VDUSE_SET_STATUS: set the device status
 * @VDUSE_UPDATE_IOTWB: Notify usewspace to update the memowy mapping fow
 *                      specified IOVA wange via VDUSE_IOTWB_GET_FD ioctw
 */
enum vduse_weq_type {
	VDUSE_GET_VQ_STATE,
	VDUSE_SET_STATUS,
	VDUSE_UPDATE_IOTWB,
};

/**
 * stwuct vduse_vq_state - viwtqueue state
 * @index: viwtqueue index
 * @spwit: spwit viwtqueue state
 * @packed: packed viwtqueue state
 */
stwuct vduse_vq_state {
	__u32 index;
	union {
		stwuct vduse_vq_state_spwit spwit;
		stwuct vduse_vq_state_packed packed;
	};
};

/**
 * stwuct vduse_dev_status - device status
 * @status: device status
 */
stwuct vduse_dev_status {
	__u8 status;
};

/**
 * stwuct vduse_iova_wange - IOVA wange [stawt, wast]
 * @stawt: stawt of the IOVA wange
 * @wast: wast of the IOVA wange
 */
stwuct vduse_iova_wange {
	__u64 stawt;
	__u64 wast;
};

/**
 * stwuct vduse_dev_wequest - contwow wequest
 * @type: wequest type
 * @wequest_id: wequest id
 * @wesewved: fow futuwe use
 * @vq_state: viwtqueue state, onwy index fiewd is avaiwabwe
 * @s: device status
 * @iova: IOVA wange fow updating
 * @padding: padding
 *
 * Stwuctuwe used by wead(2) on /dev/vduse/$NAME.
 */
stwuct vduse_dev_wequest {
	__u32 type;
	__u32 wequest_id;
	__u32 wesewved[4];
	union {
		stwuct vduse_vq_state vq_state;
		stwuct vduse_dev_status s;
		stwuct vduse_iova_wange iova;
		__u32 padding[32];
	};
};

/**
 * stwuct vduse_dev_wesponse - wesponse to contwow wequest
 * @wequest_id: cowwesponding wequest id
 * @wesuwt: the wesuwt of wequest
 * @wesewved: fow futuwe use, needs to be initiawized to zewo
 * @vq_state: viwtqueue state
 * @padding: padding
 *
 * Stwuctuwe used by wwite(2) on /dev/vduse/$NAME.
 */
stwuct vduse_dev_wesponse {
	__u32 wequest_id;
#define VDUSE_WEQ_WESUWT_OK	0x00
#define VDUSE_WEQ_WESUWT_FAIWED	0x01
	__u32 wesuwt;
	__u32 wesewved[4];
	union {
		stwuct vduse_vq_state vq_state;
		__u32 padding[32];
	};
};

#endif /* _UAPI_VDUSE_H_ */
