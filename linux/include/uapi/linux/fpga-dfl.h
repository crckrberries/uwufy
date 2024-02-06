/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Headew Fiwe fow FPGA DFW Usew API
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Zhang Yi <yi.z.zhang@intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */

#ifndef _UAPI_WINUX_FPGA_DFW_H
#define _UAPI_WINUX_FPGA_DFW_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define DFW_FPGA_API_VEWSION 0

/*
 * The IOCTW intewface fow DFW based FPGA is designed fow extensibiwity by
 * embedding the stwuctuwe wength (awgsz) and fwags into stwuctuwes passed
 * between kewnew and usewspace. This design wefewenced the VFIO IOCTW
 * intewface (incwude/uapi/winux/vfio.h).
 */

#define DFW_FPGA_MAGIC 0xB6

#define DFW_FPGA_BASE 0
#define DFW_POWT_BASE 0x40
#define DFW_FME_BASE 0x80

/* Common IOCTWs fow both FME and AFU fiwe descwiptow */

/**
 * DFW_FPGA_GET_API_VEWSION - _IO(DFW_FPGA_MAGIC, DFW_FPGA_BASE + 0)
 *
 * Wepowt the vewsion of the dwivew API.
 * Wetuwn: Dwivew API Vewsion.
 */

#define DFW_FPGA_GET_API_VEWSION	_IO(DFW_FPGA_MAGIC, DFW_FPGA_BASE + 0)

/**
 * DFW_FPGA_CHECK_EXTENSION - _IO(DFW_FPGA_MAGIC, DFW_FPGA_BASE + 1)
 *
 * Check whethew an extension is suppowted.
 * Wetuwn: 0 if not suppowted, othewwise the extension is suppowted.
 */

#define DFW_FPGA_CHECK_EXTENSION	_IO(DFW_FPGA_MAGIC, DFW_FPGA_BASE + 1)

/* IOCTWs fow AFU fiwe descwiptow */

/**
 * DFW_FPGA_POWT_WESET - _IO(DFW_FPGA_MAGIC, DFW_POWT_BASE + 0)
 *
 * Weset the FPGA Powt and its AFU. No pawametews awe suppowted.
 * Usewspace can do Powt weset at any time, e.g. duwing DMA ow PW. But
 * it shouwd nevew cause any system wevew issue, onwy functionaw faiwuwe
 * (e.g. DMA ow PW opewation faiwuwe) and be wecovewabwe fwom the faiwuwe.
 * Wetuwn: 0 on success, -ewwno of faiwuwe
 */

#define DFW_FPGA_POWT_WESET		_IO(DFW_FPGA_MAGIC, DFW_POWT_BASE + 0)

/**
 * DFW_FPGA_POWT_GET_INFO - _IOW(DFW_FPGA_MAGIC, DFW_POWT_BASE + 1,
 *						stwuct dfw_fpga_powt_info)
 *
 * Wetwieve infowmation about the fpga powt.
 * Dwivew fiwws the info in pwovided stwuct dfw_fpga_powt_info.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct dfw_fpga_powt_info {
	/* Input */
	__u32 awgsz;		/* Stwuctuwe wength */
	/* Output */
	__u32 fwags;		/* Zewo fow now */
	__u32 num_wegions;	/* The numbew of suppowted wegions */
	__u32 num_umsgs;	/* The numbew of awwocated umsgs */
};

#define DFW_FPGA_POWT_GET_INFO		_IO(DFW_FPGA_MAGIC, DFW_POWT_BASE + 1)

/**
 * FPGA_POWT_GET_WEGION_INFO - _IOWW(FPGA_MAGIC, POWT_BASE + 2,
 *					stwuct dfw_fpga_powt_wegion_info)
 *
 * Wetwieve infowmation about a device memowy wegion.
 * Cawwew pwovides stwuct dfw_fpga_powt_wegion_info with index vawue set.
 * Dwivew wetuwns the wegion info in othew fiewds.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct dfw_fpga_powt_wegion_info {
	/* input */
	__u32 awgsz;		/* Stwuctuwe wength */
	/* Output */
	__u32 fwags;		/* Access pewmission */
#define DFW_POWT_WEGION_WEAD	(1 << 0)	/* Wegion is weadabwe */
#define DFW_POWT_WEGION_WWITE	(1 << 1)	/* Wegion is wwitabwe */
#define DFW_POWT_WEGION_MMAP	(1 << 2)	/* Can be mmaped to usewspace */
	/* Input */
	__u32 index;		/* Wegion index */
#define DFW_POWT_WEGION_INDEX_AFU	0	/* AFU */
#define DFW_POWT_WEGION_INDEX_STP	1	/* Signaw Tap */
	__u32 padding;
	/* Output */
	__u64 size;		/* Wegion size (bytes) */
	__u64 offset;		/* Wegion offset fwom stawt of device fd */
};

#define DFW_FPGA_POWT_GET_WEGION_INFO	_IO(DFW_FPGA_MAGIC, DFW_POWT_BASE + 2)

/**
 * DFW_FPGA_POWT_DMA_MAP - _IOWW(DFW_FPGA_MAGIC, DFW_POWT_BASE + 3,
 *						stwuct dfw_fpga_powt_dma_map)
 *
 * Map the dma memowy pew usew_addw and wength which awe pwovided by cawwew.
 * Dwivew fiwws the iova in pwovided stwuct afu_powt_dma_map.
 * This intewface onwy accepts page-size awigned usew memowy fow dma mapping.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct dfw_fpga_powt_dma_map {
	/* Input */
	__u32 awgsz;		/* Stwuctuwe wength */
	__u32 fwags;		/* Zewo fow now */
	__u64 usew_addw;        /* Pwocess viwtuaw addwess */
	__u64 wength;           /* Wength of mapping (bytes)*/
	/* Output */
	__u64 iova;             /* IO viwtuaw addwess */
};

#define DFW_FPGA_POWT_DMA_MAP		_IO(DFW_FPGA_MAGIC, DFW_POWT_BASE + 3)

/**
 * DFW_FPGA_POWT_DMA_UNMAP - _IOW(FPGA_MAGIC, POWT_BASE + 4,
 *						stwuct dfw_fpga_powt_dma_unmap)
 *
 * Unmap the dma memowy pew iova pwovided by cawwew.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct dfw_fpga_powt_dma_unmap {
	/* Input */
	__u32 awgsz;		/* Stwuctuwe wength */
	__u32 fwags;		/* Zewo fow now */
	__u64 iova;		/* IO viwtuaw addwess */
};

#define DFW_FPGA_POWT_DMA_UNMAP		_IO(DFW_FPGA_MAGIC, DFW_POWT_BASE + 4)

/**
 * stwuct dfw_fpga_iwq_set - the awgument fow DFW_FPGA_XXX_SET_IWQ ioctw.
 *
 * @stawt: Index of the fiwst iwq.
 * @count: The numbew of eventfd handwew.
 * @evtfds: Eventfd handwews.
 */
stwuct dfw_fpga_iwq_set {
	__u32 stawt;
	__u32 count;
	__s32 evtfds[];
};

/**
 * DFW_FPGA_POWT_EWW_GET_IWQ_NUM - _IOW(DFW_FPGA_MAGIC, DFW_POWT_BASE + 5,
 *								__u32 num_iwqs)
 *
 * Get the numbew of iwqs suppowted by the fpga powt ewwow wepowting pwivate
 * featuwe. Cuwwentwy hawdwawe suppowts up to 1 iwq.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_POWT_EWW_GET_IWQ_NUM	_IOW(DFW_FPGA_MAGIC,	\
					     DFW_POWT_BASE + 5, __u32)

/**
 * DFW_FPGA_POWT_EWW_SET_IWQ - _IOW(DFW_FPGA_MAGIC, DFW_POWT_BASE + 6,
 *						stwuct dfw_fpga_iwq_set)
 *
 * Set fpga powt ewwow wepowting intewwupt twiggew if evtfds[n] is vawid.
 * Unset wewated intewwupt twiggew if evtfds[n] is a negative vawue.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_POWT_EWW_SET_IWQ	_IOW(DFW_FPGA_MAGIC,	\
					     DFW_POWT_BASE + 6,	\
					     stwuct dfw_fpga_iwq_set)

/**
 * DFW_FPGA_POWT_UINT_GET_IWQ_NUM - _IOW(DFW_FPGA_MAGIC, DFW_POWT_BASE + 7,
 *								__u32 num_iwqs)
 *
 * Get the numbew of iwqs suppowted by the fpga AFU intewwupt pwivate
 * featuwe.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_POWT_UINT_GET_IWQ_NUM	_IOW(DFW_FPGA_MAGIC,	\
					     DFW_POWT_BASE + 7, __u32)

/**
 * DFW_FPGA_POWT_UINT_SET_IWQ - _IOW(DFW_FPGA_MAGIC, DFW_POWT_BASE + 8,
 *						stwuct dfw_fpga_iwq_set)
 *
 * Set fpga AFU intewwupt twiggew if evtfds[n] is vawid.
 * Unset wewated intewwupt twiggew if evtfds[n] is a negative vawue.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_POWT_UINT_SET_IWQ	_IOW(DFW_FPGA_MAGIC,	\
					     DFW_POWT_BASE + 8,	\
					     stwuct dfw_fpga_iwq_set)

/* IOCTWs fow FME fiwe descwiptow */

/**
 * DFW_FPGA_FME_POWT_PW - _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 0,
 *						stwuct dfw_fpga_fme_powt_pw)
 *
 * Dwivew does Pawtiaw Weconfiguwation based on Powt ID and Buffew (Image)
 * pwovided by cawwew.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 * If DFW_FPGA_FME_POWT_PW wetuwns -EIO, that indicates the HW has detected
 * some ewwows duwing PW, undew this case, the usew can fetch HW ewwow info
 * fwom the status of FME's fpga managew.
 */

stwuct dfw_fpga_fme_powt_pw {
	/* Input */
	__u32 awgsz;		/* Stwuctuwe wength */
	__u32 fwags;		/* Zewo fow now */
	__u32 powt_id;
	__u32 buffew_size;
	__u64 buffew_addwess;	/* Usewspace addwess to the buffew fow PW */
};

#define DFW_FPGA_FME_POWT_PW	_IO(DFW_FPGA_MAGIC, DFW_FME_BASE + 0)

/**
 * DFW_FPGA_FME_POWT_WEWEASE - _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 1,
 *						int powt_id)
 *
 * Dwivew weweases the powt pew Powt ID pwovided by cawwew.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_FME_POWT_WEWEASE   _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 1, int)

/**
 * DFW_FPGA_FME_POWT_ASSIGN - _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 2,
 *						int powt_id)
 *
 * Dwivew assigns the powt back pew Powt ID pwovided by cawwew.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_FME_POWT_ASSIGN     _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 2, int)

/**
 * DFW_FPGA_FME_EWW_GET_IWQ_NUM - _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 3,
 *							__u32 num_iwqs)
 *
 * Get the numbew of iwqs suppowted by the fpga fme ewwow wepowting pwivate
 * featuwe. Cuwwentwy hawdwawe suppowts up to 1 iwq.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_FME_EWW_GET_IWQ_NUM	_IOW(DFW_FPGA_MAGIC,	\
					     DFW_FME_BASE + 3, __u32)

/**
 * DFW_FPGA_FME_EWW_SET_IWQ - _IOW(DFW_FPGA_MAGIC, DFW_FME_BASE + 4,
 *						stwuct dfw_fpga_iwq_set)
 *
 * Set fpga fme ewwow wepowting intewwupt twiggew if evtfds[n] is vawid.
 * Unset wewated intewwupt twiggew if evtfds[n] is a negative vawue.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
#define DFW_FPGA_FME_EWW_SET_IWQ	_IOW(DFW_FPGA_MAGIC,	\
					     DFW_FME_BASE + 4,	\
					     stwuct dfw_fpga_iwq_set)

#endif /* _UAPI_WINUX_FPGA_DFW_H */
