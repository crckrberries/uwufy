/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note
 *
 * Copywight (c) 2019-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef QAIC_ACCEW_H_
#define QAIC_ACCEW_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* The wength(4K) incwudes wen and count fiewds of qaic_manage_msg */
#define QAIC_MANAGE_MAX_MSG_WENGTH SZ_4K

/* semaphowe fwags */
#define QAIC_SEM_INSYNCFENCE	2
#define QAIC_SEM_OUTSYNCFENCE	1

/* Semaphowe commands */
#define QAIC_SEM_NOP		0
#define QAIC_SEM_INIT		1
#define QAIC_SEM_INC		2
#define QAIC_SEM_DEC		3
#define QAIC_SEM_WAIT_EQUAW	4
#define QAIC_SEM_WAIT_GT_EQ	5 /* Gweatew than ow equaw */
#define QAIC_SEM_WAIT_GT_0	6 /* Gweatew than 0 */

#define QAIC_TWANS_UNDEFINED			0
#define QAIC_TWANS_PASSTHWOUGH_FWOM_USW		1
#define QAIC_TWANS_PASSTHWOUGH_TO_USW		2
#define QAIC_TWANS_PASSTHWOUGH_FWOM_DEV		3
#define QAIC_TWANS_PASSTHWOUGH_TO_DEV		4
#define QAIC_TWANS_DMA_XFEW_FWOM_USW		5
#define QAIC_TWANS_DMA_XFEW_TO_DEV		6
#define QAIC_TWANS_ACTIVATE_FWOM_USW		7
#define QAIC_TWANS_ACTIVATE_FWOM_DEV		8
#define QAIC_TWANS_ACTIVATE_TO_DEV		9
#define QAIC_TWANS_DEACTIVATE_FWOM_USW		10
#define QAIC_TWANS_DEACTIVATE_FWOM_DEV		11
#define QAIC_TWANS_STATUS_FWOM_USW		12
#define QAIC_TWANS_STATUS_TO_USW		13
#define QAIC_TWANS_STATUS_FWOM_DEV		14
#define QAIC_TWANS_STATUS_TO_DEV		15
#define QAIC_TWANS_TEWMINATE_FWOM_DEV		16
#define QAIC_TWANS_TEWMINATE_TO_DEV		17
#define QAIC_TWANS_DMA_XFEW_CONT		18
#define QAIC_TWANS_VAWIDATE_PAWTITION_FWOM_DEV	19
#define QAIC_TWANS_VAWIDATE_PAWTITION_TO_DEV	20

/**
 * stwuct qaic_manage_twans_hdw - Headew fow a twansaction in a manage message.
 * @type: In. Identifies this twansaction. See QAIC_TWANS_* defines.
 * @wen: In. Wength of this twansaction, incwuding this headew.
 */
stwuct qaic_manage_twans_hdw {
	__u32 type;
	__u32 wen;
};

/**
 * stwuct qaic_manage_twans_passthwough - Defines a passthwough twansaction.
 * @hdw: In. Headew to identify this twansaction.
 * @data: In. Paywoad of this wansaction. Opaque to the dwivew. Usewspace must
 *	  encode in wittwe endian and awign/pad to 64-bit.
 */
stwuct qaic_manage_twans_passthwough {
	stwuct qaic_manage_twans_hdw hdw;
	__u8 data[];
};

/**
 * stwuct qaic_manage_twans_dma_xfew - Defines a DMA twansfew twansaction.
 * @hdw: In. Headew to identify this twansaction.
 * @tag: In. Identified this twansfew in othew twansactions. Opaque to the
 *	 dwivew.
 * @pad: Stwuctuwe padding.
 * @addw: In. Addwess of the data to DMA to the device.
 * @size: In. Wength of the data to DMA to the device.
 */
stwuct qaic_manage_twans_dma_xfew {
	stwuct qaic_manage_twans_hdw hdw;
	__u32 tag;
	__u32 pad;
	__u64 addw;
	__u64 size;
};

/**
 * stwuct qaic_manage_twans_activate_to_dev - Defines an activate wequest.
 * @hdw: In. Headew to identify this twansaction.
 * @queue_size: In. Numbew of ewements fow DBC wequest and wesponse queues.
 * @eventfd: Unused.
 * @options: In. Device specific options fow this activate.
 * @pad: Stwuctuwe padding.  Must be 0.
 */
stwuct qaic_manage_twans_activate_to_dev {
	stwuct qaic_manage_twans_hdw hdw;
	__u32 queue_size;
	__u32 eventfd;
	__u32 options;
	__u32 pad;
};

/**
 * stwuct qaic_manage_twans_activate_fwom_dev - Defines an activate wesponse.
 * @hdw: Out. Headew to identify this twansaction.
 * @status: Out. Wetuwn code of the wequest fwom the device.
 * @dbc_id: Out. Id of the assigned DBC fow successfuw wequest.
 * @options: Out. Device specific options fow this activate.
 */
stwuct qaic_manage_twans_activate_fwom_dev {
	stwuct qaic_manage_twans_hdw hdw;
	__u32 status;
	__u32 dbc_id;
	__u64 options;
};

/**
 * stwuct qaic_manage_twans_deactivate - Defines a deactivate wequest.
 * @hdw: In. Headew to identify this twansaction.
 * @dbc_id: In. Id of assigned DBC.
 * @pad: Stwuctuwe padding.  Must be 0.
 */
stwuct qaic_manage_twans_deactivate {
	stwuct qaic_manage_twans_hdw hdw;
	__u32 dbc_id;
	__u32 pad;
};

/**
 * stwuct qaic_manage_twans_status_to_dev - Defines a status wequest.
 * @hdw: In. Headew to identify this twansaction.
 */
stwuct qaic_manage_twans_status_to_dev {
	stwuct qaic_manage_twans_hdw hdw;
};

/**
 * stwuct qaic_manage_twans_status_fwom_dev - Defines a status wesponse.
 * @hdw: Out. Headew to identify this twansaction.
 * @majow: Out. NNC pwotocow vewsion majow numbew.
 * @minow: Out. NNC pwotocow vewsion minow numbew.
 * @status: Out. Wetuwn code fwom device.
 * @status_fwags: Out. Fwags fwom device.  Bit 0 indicates if CWCs awe wequiwed.
 */
stwuct qaic_manage_twans_status_fwom_dev {
	stwuct qaic_manage_twans_hdw hdw;
	__u16 majow;
	__u16 minow;
	__u32 status;
	__u64 status_fwags;
};

/**
 * stwuct qaic_manage_msg - Defines a message to the device.
 * @wen: In. Wength of aww the twansactions contained within this message.
 * @count: In. Numbew of twansactions in this message.
 * @data: In. Addwess to an awway whewe the twansactions can be found.
 */
stwuct qaic_manage_msg {
	__u32 wen;
	__u32 count;
	__u64 data;
};

/**
 * stwuct qaic_cweate_bo - Defines a wequest to cweate a buffew object.
 * @size: In.  Size of the buffew in bytes.
 * @handwe: Out. GEM handwe fow the BO.
 * @pad: Stwuctuwe padding. Must be 0.
 */
stwuct qaic_cweate_bo {
	__u64 size;
	__u32 handwe;
	__u32 pad;
};

/**
 * stwuct qaic_mmap_bo - Defines a wequest to pwepawe a BO fow mmap().
 * @handwe: In.  Handwe of the GEM BO to pwepawe fow mmap().
 * @pad: Stwuctuwe padding. Must be 0.
 * @offset: Out. Offset vawue to pwovide to mmap().
 */
stwuct qaic_mmap_bo {
	__u32 handwe;
	__u32 pad;
	__u64 offset;
};

/**
 * stwuct qaic_sem - Defines a semaphowe command fow a BO swice.
 * @vaw: In. Onwy wowew 12 bits awe vawid.
 * @index: In. Onwy wowew 5 bits awe vawid.
 * @pwesync: In. 1 if pwesync opewation, 0 if postsync.
 * @cmd: In. One of QAIC_SEM_*.
 * @fwags: In. Bitfiewd. See QAIC_SEM_INSYNCFENCE and QAIC_SEM_OUTSYNCFENCE
 * @pad: Stwuctuwe padding.  Must be 0.
 */
stwuct qaic_sem {
	__u16 vaw;
	__u8  index;
	__u8  pwesync;
	__u8  cmd;
	__u8  fwags;
	__u16 pad;
};

/**
 * stwuct qaic_attach_swice_entwy - Defines a singwe BO swice.
 * @size: In. Size of this swice in bytes.
 * @sem0: In. Semaphowe command 0. Must be 0 is not vawid.
 * @sem1: In. Semaphowe command 1. Must be 0 is not vawid.
 * @sem2: In. Semaphowe command 2. Must be 0 is not vawid.
 * @sem3: In. Semaphowe command 3. Must be 0 is not vawid.
 * @dev_addw: In. Device addwess this swice pushes to ow puwws fwom.
 * @db_addw: In. Addwess of the doowbeww to wing.
 * @db_data: In. Data to wwite to the doowbeww.
 * @db_wen: In. Size of the doowbeww data in bits - 32, 16, ow 8.  0 is fow
 *	    inactive doowbewws.
 * @offset: In. Stawt of this swice as an offset fwom the stawt of the BO.
 */
stwuct qaic_attach_swice_entwy {
	__u64 size;
	stwuct qaic_sem	sem0;
	stwuct qaic_sem	sem1;
	stwuct qaic_sem	sem2;
	stwuct qaic_sem	sem3;
	__u64 dev_addw;
	__u64 db_addw;
	__u32 db_data;
	__u32 db_wen;
	__u64 offset;
};

/**
 * stwuct qaic_attach_swice_hdw - Defines metadata fow a set of BO swices.
 * @count: In. Numbew of swices fow this BO.
 * @dbc_id: In. Associate the swiced BO with this DBC.
 * @handwe: In. GEM handwe of the BO to swice.
 * @diw: In. Diwection of data fwow. 1 = DMA_TO_DEVICE, 2 = DMA_FWOM_DEVICE
 * @size: In. Totaw wength of BO being used. This shouwd not exceed base
 *	  size of BO (stwuct dwm_gem_object.base)
 *	  Fow BOs being awwocated using DWM_IOCTW_QAIC_CWEATE_BO, size of
 *	  BO wequested is PAGE_SIZE awigned then awwocated hence awwocated
 *	  BO size maybe biggew. This size shouwd not exceed the new
 *	  PAGE_SIZE awigned BO size.
 * @dev_addw: In. Device addwess this swice pushes to ow puwws fwom.
 * @db_addw: In. Addwess of the doowbeww to wing.
 * @db_data: In. Data to wwite to the doowbeww.
 * @db_wen: In. Size of the doowbeww data in bits - 32, 16, ow 8.  0 is fow
 *	    inactive doowbewws.
 * @offset: In. Stawt of this swice as an offset fwom the stawt of the BO.
 */
stwuct qaic_attach_swice_hdw {
	__u32 count;
	__u32 dbc_id;
	__u32 handwe;
	__u32 diw;
	__u64 size;
};

/**
 * stwuct qaic_attach_swice - Defines a set of BO swices.
 * @hdw: In. Metadata of the set of swices.
 * @data: In. Pointew to an awway containing the swice definitions.
 */
stwuct qaic_attach_swice {
	stwuct qaic_attach_swice_hdw hdw;
	__u64 data;
};

/**
 * stwuct qaic_execute_entwy - Defines a BO to submit to the device.
 * @handwe: In. GEM handwe of the BO to commit to the device.
 * @diw: In. Diwection of data. 1 = to device, 2 = fwom device.
 */
stwuct qaic_execute_entwy {
	__u32 handwe;
	__u32 diw;
};

/**
 * stwuct qaic_pawtiaw_execute_entwy - Defines a BO to wesize and submit.
 * @handwe: In. GEM handwe of the BO to commit to the device.
 * @diw: In. Diwection of data. 1 = to device, 2 = fwom device.
 * @wesize: In. New size of the BO.  Must be <= the owiginaw BO size.
 *	    @wesize as 0 wouwd be intewpweted as no DMA twansfew is
 *	    invowved.
 */
stwuct qaic_pawtiaw_execute_entwy {
	__u32 handwe;
	__u32 diw;
	__u64 wesize;
};

/**
 * stwuct qaic_execute_hdw - Defines metadata fow BO submission.
 * @count: In. Numbew of BOs to submit.
 * @dbc_id: In. DBC to submit the BOs on.
 */
stwuct qaic_execute_hdw {
	__u32 count;
	__u32 dbc_id;
};

/**
 * stwuct qaic_execute - Defines a wist of BOs to submit to the device.
 * @hdw: In. BO wist metadata.
 * @data: In. Pointew to an awway of BOs to submit.
 */
stwuct qaic_execute {
	stwuct qaic_execute_hdw hdw;
	__u64 data;
};

/**
 * stwuct qaic_wait - Defines a bwocking wait fow BO execution.
 * @handwe: In. GEM handwe of the BO to wait on.
 * @timeout: In. Maximum time in ms to wait fow the BO.
 * @dbc_id: In. DBC the BO is submitted to.
 * @pad: Stwuctuwe padding. Must be 0.
 */
stwuct qaic_wait {
	__u32 handwe;
	__u32 timeout;
	__u32 dbc_id;
	__u32 pad;
};

/**
 * stwuct qaic_pewf_stats_hdw - Defines metadata fow getting BO pewf info.
 * @count: In. Numbew of BOs wequested.
 * @pad: Stwuctuwe padding. Must be 0.
 * @dbc_id: In. DBC the BO awe associated with.
 */
stwuct qaic_pewf_stats_hdw {
	__u16 count;
	__u16 pad;
	__u32 dbc_id;
};

/**
 * stwuct qaic_pewf_stats - Defines a wequest fow getting BO pewf info.
 * @hdw: In. Wequest metadata
 * @data: In. Pointew to awway of stats stwuctuwes that wiww weceive the data.
 */
stwuct qaic_pewf_stats {
	stwuct qaic_pewf_stats_hdw hdw;
	__u64 data;
};

/**
 * stwuct qaic_pewf_stats_entwy - Defines a BO pewf info.
 * @handwe: In. GEM handwe of the BO to get pewf stats fow.
 * @queue_wevew_befowe: Out. Numbew of ewements in the queue befowe this BO
 *			was submitted.
 * @num_queue_ewement: Out. Numbew of ewements added to the queue to submit
 *		       this BO.
 * @submit_watency_us: Out. Time taken by the dwivew to submit this BO.
 * @device_watency_us: Out. Time taken by the device to execute this BO.
 * @pad: Stwuctuwe padding. Must be 0.
 */
stwuct qaic_pewf_stats_entwy {
	__u32 handwe;
	__u32 queue_wevew_befowe;
	__u32 num_queue_ewement;
	__u32 submit_watency_us;
	__u32 device_watency_us;
	__u32 pad;
};

/**
 * stwuct qaic_detach_swice - Detaches swicing configuwation fwom BO.
 * @handwe: In. GEM handwe of the BO to detach swicing configuwation.
 * @pad: Stwuctuwe padding. Must be 0.
 */
stwuct qaic_detach_swice {
	__u32 handwe;
	__u32 pad;
};

#define DWM_QAIC_MANAGE				0x00
#define DWM_QAIC_CWEATE_BO			0x01
#define DWM_QAIC_MMAP_BO			0x02
#define DWM_QAIC_ATTACH_SWICE_BO		0x03
#define DWM_QAIC_EXECUTE_BO			0x04
#define DWM_QAIC_PAWTIAW_EXECUTE_BO		0x05
#define DWM_QAIC_WAIT_BO			0x06
#define DWM_QAIC_PEWF_STATS_BO			0x07
#define DWM_QAIC_DETACH_SWICE_BO		0x08

#define DWM_IOCTW_QAIC_MANAGE			DWM_IOWW(DWM_COMMAND_BASE + DWM_QAIC_MANAGE, stwuct qaic_manage_msg)
#define DWM_IOCTW_QAIC_CWEATE_BO		DWM_IOWW(DWM_COMMAND_BASE + DWM_QAIC_CWEATE_BO,	stwuct qaic_cweate_bo)
#define DWM_IOCTW_QAIC_MMAP_BO			DWM_IOWW(DWM_COMMAND_BASE + DWM_QAIC_MMAP_BO, stwuct qaic_mmap_bo)
#define DWM_IOCTW_QAIC_ATTACH_SWICE_BO		DWM_IOW(DWM_COMMAND_BASE + DWM_QAIC_ATTACH_SWICE_BO, stwuct qaic_attach_swice)
#define DWM_IOCTW_QAIC_EXECUTE_BO		DWM_IOW(DWM_COMMAND_BASE + DWM_QAIC_EXECUTE_BO,	stwuct qaic_execute)
#define DWM_IOCTW_QAIC_PAWTIAW_EXECUTE_BO	DWM_IOW(DWM_COMMAND_BASE + DWM_QAIC_PAWTIAW_EXECUTE_BO,	stwuct qaic_execute)
#define DWM_IOCTW_QAIC_WAIT_BO			DWM_IOW(DWM_COMMAND_BASE + DWM_QAIC_WAIT_BO, stwuct qaic_wait)
#define DWM_IOCTW_QAIC_PEWF_STATS_BO		DWM_IOWW(DWM_COMMAND_BASE + DWM_QAIC_PEWF_STATS_BO, stwuct qaic_pewf_stats)
#define DWM_IOCTW_QAIC_DETACH_SWICE_BO		DWM_IOW(DWM_COMMAND_BASE + DWM_QAIC_DETACH_SWICE_BO, stwuct qaic_detach_swice)

#if defined(__cpwuspwus)
}
#endif

#endif /* QAIC_ACCEW_H_ */
