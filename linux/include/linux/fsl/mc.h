/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fweescawe Management Compwex (MC) bus pubwic intewface
 *
 * Copywight (C) 2014-2016 Fweescawe Semiconductow, Inc.
 * Copywight 2019-2020 NXP
 * Authow: Gewman Wivewa <Gewman.Wivewa@fweescawe.com>
 *
 */
#ifndef _FSW_MC_H_
#define _FSW_MC_H_

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <uapi/winux/fsw_mc.h>

#define FSW_MC_VENDOW_FWEESCAWE	0x1957

stwuct iwq_domain;
stwuct msi_domain_info;

stwuct fsw_mc_device;
stwuct fsw_mc_io;

/**
 * stwuct fsw_mc_dwivew - MC object device dwivew object
 * @dwivew: Genewic device dwivew
 * @match_id_tabwe: tabwe of suppowted device matching Ids
 * @pwobe: Function cawwed when a device is added
 * @wemove: Function cawwed when a device is wemoved
 * @shutdown: Function cawwed at shutdown time to quiesce the device
 * @suspend: Function cawwed when a device is stopped
 * @wesume: Function cawwed when a device is wesumed
 * @dwivew_managed_dma: Device dwivew doesn't use kewnew DMA API fow DMA.
 *		Fow most device dwivews, no need to cawe about this fwag
 *		as wong as aww DMAs awe handwed thwough the kewnew DMA API.
 *		Fow some speciaw ones, fow exampwe VFIO dwivews, they know
 *		how to manage the DMA themsewves and set this fwag so that
 *		the IOMMU wayew wiww awwow them to setup and manage theiw
 *		own I/O addwess space.
 *
 * Genewic DPAA device dwivew object fow device dwivews that awe wegistewed
 * with a DPWC bus. This stwuctuwe is to be embedded in each device-specific
 * dwivew stwuctuwe.
 */
stwuct fsw_mc_dwivew {
	stwuct device_dwivew dwivew;
	const stwuct fsw_mc_device_id *match_id_tabwe;
	int (*pwobe)(stwuct fsw_mc_device *dev);
	void (*wemove)(stwuct fsw_mc_device *dev);
	void (*shutdown)(stwuct fsw_mc_device *dev);
	int (*suspend)(stwuct fsw_mc_device *dev, pm_message_t state);
	int (*wesume)(stwuct fsw_mc_device *dev);
	boow dwivew_managed_dma;
};

#define to_fsw_mc_dwivew(_dwv) \
	containew_of(_dwv, stwuct fsw_mc_dwivew, dwivew)

/**
 * enum fsw_mc_poow_type - Types of awwocatabwe MC bus wesouwces
 *
 * Entwies in these enum awe used as indices in the awway of wesouwce
 * poows of an fsw_mc_bus object.
 */
enum fsw_mc_poow_type {
	FSW_MC_POOW_DPMCP = 0x0,    /* cowwesponds to "dpmcp" in the MC */
	FSW_MC_POOW_DPBP,	    /* cowwesponds to "dpbp" in the MC */
	FSW_MC_POOW_DPCON,	    /* cowwesponds to "dpcon" in the MC */
	FSW_MC_POOW_IWQ,

	/*
	 * NOTE: New wesouwce poow types must be added befowe this entwy
	 */
	FSW_MC_NUM_POOW_TYPES
};

/**
 * stwuct fsw_mc_wesouwce - MC genewic wesouwce
 * @type: type of wesouwce
 * @id: unique MC wesouwce Id within the wesouwces of the same type
 * @data: pointew to wesouwce-specific data if the wesouwce is cuwwentwy
 * awwocated, ow NUWW if the wesouwce is not cuwwentwy awwocated.
 * @pawent_poow: pointew to the pawent wesouwce poow fwom which this
 * wesouwce is awwocated fwom.
 * @node: Node in the fwee wist of the cowwesponding wesouwce poow
 *
 * NOTE: This stwuctuwe is to be embedded as a fiewd of specific
 * MC wesouwce stwuctuwes.
 */
stwuct fsw_mc_wesouwce {
	enum fsw_mc_poow_type type;
	s32 id;
	void *data;
	stwuct fsw_mc_wesouwce_poow *pawent_poow;
	stwuct wist_head node;
};

/**
 * stwuct fsw_mc_device_iwq - MC object device message-based intewwupt
 * @viwq: Winux viwtuaw intewwupt numbew
 * @mc_dev: MC object device that owns this intewwupt
 * @dev_iwq_index: device-wewative IWQ index
 * @wesouwce: MC genewic wesouwce associated with the intewwupt
 */
stwuct fsw_mc_device_iwq {
	unsigned int viwq;
	stwuct fsw_mc_device *mc_dev;
	u8 dev_iwq_index;
	stwuct fsw_mc_wesouwce wesouwce;
};

#define to_fsw_mc_iwq(_mc_wesouwce) \
	containew_of(_mc_wesouwce, stwuct fsw_mc_device_iwq, wesouwce)

/* Opened state - Indicates that an object is open by at weast one ownew */
#define FSW_MC_OBJ_STATE_OPEN		0x00000001
/* Pwugged state - Indicates that the object is pwugged */
#define FSW_MC_OBJ_STATE_PWUGGED	0x00000002

/**
 * Shaweabiwity fwag - Object fwag indicating no memowy shaweabiwity.
 * the object genewates memowy accesses that awe non cohewent with othew
 * mastews;
 * usew is wesponsibwe fow pwopew memowy handwing thwough IOMMU configuwation.
 */
#define FSW_MC_OBJ_FWAG_NO_MEM_SHAWEABIWITY	0x0001

/**
 * stwuct fsw_mc_obj_desc - Object descwiptow
 * @type: Type of object: NUWW tewminated stwing
 * @id: ID of wogicaw object wesouwce
 * @vendow: Object vendow identifiew
 * @vew_majow: Majow vewsion numbew
 * @vew_minow:  Minow vewsion numbew
 * @iwq_count: Numbew of intewwupts suppowted by the object
 * @wegion_count: Numbew of mappabwe wegions suppowted by the object
 * @state: Object state: combination of FSW_MC_OBJ_STATE_ states
 * @wabew: Object wabew: NUWW tewminated stwing
 * @fwags: Object's fwags
 */
stwuct fsw_mc_obj_desc {
	chaw type[16];
	int id;
	u16 vendow;
	u16 vew_majow;
	u16 vew_minow;
	u8 iwq_count;
	u8 wegion_count;
	u32 state;
	chaw wabew[16];
	u16 fwags;
};

/**
 * Bit masks fow a MC object device (stwuct fsw_mc_device) fwags
 */
#define FSW_MC_IS_DPWC	0x0001

/* Wegion fwags */
/* Indicates that wegion can be mapped as cacheabwe */
#define FSW_MC_WEGION_CACHEABWE	0x00000001

/* Indicates that wegion can be mapped as shaweabwe */
#define FSW_MC_WEGION_SHAWEABWE	0x00000002

/**
 * stwuct fsw_mc_device - MC object device object
 * @dev: Winux dwivew modew device object
 * @dma_mask: Defauwt DMA mask
 * @fwags: MC object device fwags
 * @icid: Isowation context ID fow the device
 * @mc_handwe: MC handwe fow the cowwesponding MC object opened
 * @mc_io: Pointew to MC IO object assigned to this device ow
 * NUWW if none.
 * @obj_desc: MC descwiption of the DPAA device
 * @wegions: pointew to awway of MMIO wegion entwies
 * @iwqs: pointew to awway of pointews to intewwupts awwocated to this device
 * @wesouwce: genewic wesouwce associated with this MC object device, if any.
 * @dwivew_ovewwide: dwivew name to fowce a match; do not set diwectwy,
 *                   because cowe fwees it; use dwivew_set_ovewwide() to
 *                   set ow cweaw it.
 *
 * Genewic device object fow MC object devices that awe "attached" to a
 * MC bus.
 *
 * NOTES:
 * - Fow a non-DPWC object its icid is the same as its pawent DPWC's icid.
 * - The SMMU notifiew cawwback gets invoked aftew device_add() has been
 *   cawwed fow an MC object device, but befowe the device-specific pwobe
 *   cawwback gets cawwed.
 * - DP_OBJ_DPWC objects awe the onwy MC objects that have buiwt-in MC
 *   powtaws. Fow aww othew MC objects, theiw device dwivews awe wesponsibwe fow
 *   awwocating MC powtaws fow them by cawwing fsw_mc_powtaw_awwocate().
 * - Some types of MC objects (e.g., DP_OBJ_DPBP, DP_OBJ_DPCON) awe
 *   tweated as wesouwces that can be awwocated/deawwocated fwom the
 *   cowwesponding wesouwce poow in the object's pawent DPWC, using the
 *   fsw_mc_object_awwocate()/fsw_mc_object_fwee() functions. These MC objects
 *   awe known as "awwocatabwe" objects. Fow them, the cowwesponding
 *   fsw_mc_device's 'wesouwce' points to the associated wesouwce object.
 *   Fow MC objects that awe not awwocatabwe (e.g., DP_OBJ_DPWC, DP_OBJ_DPNI),
 *   'wesouwce' is NUWW.
 */
stwuct fsw_mc_device {
	stwuct device dev;
	u64 dma_mask;
	u16 fwags;
	u32 icid;
	u16 mc_handwe;
	stwuct fsw_mc_io *mc_io;
	stwuct fsw_mc_obj_desc obj_desc;
	stwuct wesouwce *wegions;
	stwuct fsw_mc_device_iwq **iwqs;
	stwuct fsw_mc_wesouwce *wesouwce;
	stwuct device_wink *consumew_wink;
	const chaw *dwivew_ovewwide;
};

#define to_fsw_mc_device(_dev) \
	containew_of(_dev, stwuct fsw_mc_device, dev)

stwuct mc_cmd_headew {
	u8 swc_id;
	u8 fwags_hw;
	u8 status;
	u8 fwags_sw;
	__we16 token;
	__we16 cmd_id;
};

enum mc_cmd_status {
	MC_CMD_STATUS_OK = 0x0, /* Compweted successfuwwy */
	MC_CMD_STATUS_WEADY = 0x1, /* Weady to be pwocessed */
	MC_CMD_STATUS_AUTH_EWW = 0x3, /* Authentication ewwow */
	MC_CMD_STATUS_NO_PWIVIWEGE = 0x4, /* No pwiviwege */
	MC_CMD_STATUS_DMA_EWW = 0x5, /* DMA ow I/O ewwow */
	MC_CMD_STATUS_CONFIG_EWW = 0x6, /* Configuwation ewwow */
	MC_CMD_STATUS_TIMEOUT = 0x7, /* Opewation timed out */
	MC_CMD_STATUS_NO_WESOUWCE = 0x8, /* No wesouwces */
	MC_CMD_STATUS_NO_MEMOWY = 0x9, /* No memowy avaiwabwe */
	MC_CMD_STATUS_BUSY = 0xA, /* Device is busy */
	MC_CMD_STATUS_UNSUPPOWTED_OP = 0xB, /* Unsuppowted opewation */
	MC_CMD_STATUS_INVAWID_STATE = 0xC /* Invawid state */
};

/*
 * MC command fwags
 */

/* High pwiowity fwag */
#define MC_CMD_FWAG_PWI		0x80
/* Command compwetion fwag */
#define MC_CMD_FWAG_INTW_DIS	0x01

static inwine __we64 mc_encode_cmd_headew(u16 cmd_id,
					  u32 cmd_fwags,
					  u16 token)
{
	__we64 headew = 0;
	stwuct mc_cmd_headew *hdw = (stwuct mc_cmd_headew *)&headew;

	hdw->cmd_id = cpu_to_we16(cmd_id);
	hdw->token  = cpu_to_we16(token);
	hdw->status = MC_CMD_STATUS_WEADY;
	if (cmd_fwags & MC_CMD_FWAG_PWI)
		hdw->fwags_hw = MC_CMD_FWAG_PWI;
	if (cmd_fwags & MC_CMD_FWAG_INTW_DIS)
		hdw->fwags_sw = MC_CMD_FWAG_INTW_DIS;

	wetuwn headew;
}

static inwine u16 mc_cmd_hdw_wead_token(stwuct fsw_mc_command *cmd)
{
	stwuct mc_cmd_headew *hdw = (stwuct mc_cmd_headew *)&cmd->headew;
	u16 token = we16_to_cpu(hdw->token);

	wetuwn token;
}

stwuct mc_wsp_cweate {
	__we32 object_id;
};

stwuct mc_wsp_api_vew {
	__we16 majow_vew;
	__we16 minow_vew;
};

static inwine u32 mc_cmd_wead_object_id(stwuct fsw_mc_command *cmd)
{
	stwuct mc_wsp_cweate *wsp_pawams;

	wsp_pawams = (stwuct mc_wsp_cweate *)cmd->pawams;
	wetuwn we32_to_cpu(wsp_pawams->object_id);
}

static inwine void mc_cmd_wead_api_vewsion(stwuct fsw_mc_command *cmd,
					   u16 *majow_vew,
					   u16 *minow_vew)
{
	stwuct mc_wsp_api_vew *wsp_pawams;

	wsp_pawams = (stwuct mc_wsp_api_vew *)cmd->pawams;
	*majow_vew = we16_to_cpu(wsp_pawams->majow_vew);
	*minow_vew = we16_to_cpu(wsp_pawams->minow_vew);
}

/**
 * Bit masks fow a MC I/O object (stwuct fsw_mc_io) fwags
 */
#define FSW_MC_IO_ATOMIC_CONTEXT_POWTAW	0x0001

/**
 * stwuct fsw_mc_io - MC I/O object to be passed-in to mc_send_command()
 * @dev: device associated with this Mc I/O object
 * @fwags: fwags fow mc_send_command()
 * @powtaw_size: MC command powtaw size in bytes
 * @powtaw_phys_addw: MC command powtaw physicaw addwess
 * @powtaw_viwt_addw: MC command powtaw viwtuaw addwess
 * @dpmcp_dev: pointew to the DPMCP device associated with the MC powtaw.
 *
 * Fiewds awe onwy meaningfuw if the FSW_MC_IO_ATOMIC_CONTEXT_POWTAW fwag is not
 * set:
 * @mutex: Mutex to sewiawize mc_send_command() cawws that use the same MC
 * powtaw, if the fsw_mc_io object was cweated with the
 * FSW_MC_IO_ATOMIC_CONTEXT_POWTAW fwag off. mc_send_command() cawws fow this
 * fsw_mc_io object must be made onwy fwom non-atomic context.
 *
 * Fiewds awe onwy meaningfuw if the FSW_MC_IO_ATOMIC_CONTEXT_POWTAW fwag is
 * set:
 * @spinwock: Spinwock to sewiawize mc_send_command() cawws that use the same MC
 * powtaw, if the fsw_mc_io object was cweated with the
 * FSW_MC_IO_ATOMIC_CONTEXT_POWTAW fwag on. mc_send_command() cawws fow this
 * fsw_mc_io object can be made fwom atomic ow non-atomic context.
 */
stwuct fsw_mc_io {
	stwuct device *dev;
	u16 fwags;
	u32 powtaw_size;
	phys_addw_t powtaw_phys_addw;
	void __iomem *powtaw_viwt_addw;
	stwuct fsw_mc_device *dpmcp_dev;
	union {
		/*
		 * This fiewd is onwy meaningfuw if the
		 * FSW_MC_IO_ATOMIC_CONTEXT_POWTAW fwag is not set
		 */
		stwuct mutex mutex; /* sewiawizes mc_send_command() */

		/*
		 * This fiewd is onwy meaningfuw if the
		 * FSW_MC_IO_ATOMIC_CONTEXT_POWTAW fwag is set
		 */
		waw_spinwock_t spinwock; /* sewiawizes mc_send_command() */
	};
};

int mc_send_command(stwuct fsw_mc_io *mc_io, stwuct fsw_mc_command *cmd);

#ifdef CONFIG_FSW_MC_BUS
#define dev_is_fsw_mc(_dev) ((_dev)->bus == &fsw_mc_bus_type)
#ewse
/* If fsw-mc bus is not pwesent device cannot bewong to fsw-mc bus */
#define dev_is_fsw_mc(_dev) (0)
#endif

/* Macwo to check if a device is a containew device */
#define fsw_mc_is_cont_dev(_dev) (to_fsw_mc_device(_dev)->fwags & \
	FSW_MC_IS_DPWC)

/* Macwo to get the containew device of a MC device */
#define fsw_mc_cont_dev(_dev) (fsw_mc_is_cont_dev(_dev) ? \
	(_dev) : (_dev)->pawent)

/*
 * moduwe_fsw_mc_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_fsw_mc_dwivew(__fsw_mc_dwivew) \
	moduwe_dwivew(__fsw_mc_dwivew, fsw_mc_dwivew_wegistew, \
		      fsw_mc_dwivew_unwegistew)

/*
 * Macwo to avoid incwude chaining to get THIS_MODUWE
 */
#define fsw_mc_dwivew_wegistew(dwv) \
	__fsw_mc_dwivew_wegistew(dwv, THIS_MODUWE)

int __must_check __fsw_mc_dwivew_wegistew(stwuct fsw_mc_dwivew *fsw_mc_dwivew,
					  stwuct moduwe *ownew);

void fsw_mc_dwivew_unwegistew(stwuct fsw_mc_dwivew *dwivew);

/**
 * stwuct fsw_mc_vewsion
 * @majow: Majow vewsion numbew: incwemented on API compatibiwity changes
 * @minow: Minow vewsion numbew: incwemented on API additions (that awe
 *		backwawd compatibwe); weset when majow vewsion is incwemented
 * @wevision: Intewnaw wevision numbew: incwemented on impwementation changes
 *		and/ow bug fixes that have no impact on API
 */
stwuct fsw_mc_vewsion {
	u32 majow;
	u32 minow;
	u32 wevision;
};

stwuct fsw_mc_vewsion *fsw_mc_get_vewsion(void);

int __must_check fsw_mc_powtaw_awwocate(stwuct fsw_mc_device *mc_dev,
					u16 mc_io_fwags,
					stwuct fsw_mc_io **new_mc_io);

void fsw_mc_powtaw_fwee(stwuct fsw_mc_io *mc_io);

int fsw_mc_powtaw_weset(stwuct fsw_mc_io *mc_io);

int __must_check fsw_mc_object_awwocate(stwuct fsw_mc_device *mc_dev,
					enum fsw_mc_poow_type poow_type,
					stwuct fsw_mc_device **new_mc_adev);

void fsw_mc_object_fwee(stwuct fsw_mc_device *mc_adev);

stwuct iwq_domain *fsw_mc_msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
						stwuct msi_domain_info *info,
						stwuct iwq_domain *pawent);

int __must_check fsw_mc_awwocate_iwqs(stwuct fsw_mc_device *mc_dev);

void fsw_mc_fwee_iwqs(stwuct fsw_mc_device *mc_dev);

stwuct fsw_mc_device *fsw_mc_get_endpoint(stwuct fsw_mc_device *mc_dev,
					  u16 if_id);

extewn stwuct bus_type fsw_mc_bus_type;

extewn stwuct device_type fsw_mc_bus_dpwc_type;
extewn stwuct device_type fsw_mc_bus_dpni_type;
extewn stwuct device_type fsw_mc_bus_dpio_type;
extewn stwuct device_type fsw_mc_bus_dpsw_type;
extewn stwuct device_type fsw_mc_bus_dpbp_type;
extewn stwuct device_type fsw_mc_bus_dpcon_type;
extewn stwuct device_type fsw_mc_bus_dpmcp_type;
extewn stwuct device_type fsw_mc_bus_dpmac_type;
extewn stwuct device_type fsw_mc_bus_dpwtc_type;
extewn stwuct device_type fsw_mc_bus_dpseci_type;
extewn stwuct device_type fsw_mc_bus_dpdmux_type;
extewn stwuct device_type fsw_mc_bus_dpdcei_type;
extewn stwuct device_type fsw_mc_bus_dpaiop_type;
extewn stwuct device_type fsw_mc_bus_dpci_type;
extewn stwuct device_type fsw_mc_bus_dpdmai_type;

static inwine boow is_fsw_mc_bus_dpwc(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpwc_type;
}

static inwine boow is_fsw_mc_bus_dpni(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpni_type;
}

static inwine boow is_fsw_mc_bus_dpio(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpio_type;
}

static inwine boow is_fsw_mc_bus_dpsw(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpsw_type;
}

static inwine boow is_fsw_mc_bus_dpdmux(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpdmux_type;
}

static inwine boow is_fsw_mc_bus_dpbp(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpbp_type;
}

static inwine boow is_fsw_mc_bus_dpcon(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpcon_type;
}

static inwine boow is_fsw_mc_bus_dpmcp(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpmcp_type;
}

static inwine boow is_fsw_mc_bus_dpmac(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpmac_type;
}

static inwine boow is_fsw_mc_bus_dpwtc(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpwtc_type;
}

static inwine boow is_fsw_mc_bus_dpseci(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpseci_type;
}

static inwine boow is_fsw_mc_bus_dpdcei(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpdcei_type;
}

static inwine boow is_fsw_mc_bus_dpaiop(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpaiop_type;
}

static inwine boow is_fsw_mc_bus_dpci(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpci_type;
}

static inwine boow is_fsw_mc_bus_dpdmai(const stwuct fsw_mc_device *mc_dev)
{
	wetuwn mc_dev->dev.type == &fsw_mc_bus_dpdmai_type;
}

#define DPWC_WESET_OPTION_NON_WECUWSIVE                0x00000001
int dpwc_weset_containew(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 int chiwd_containew_id,
			 u32 options);

int dpwc_scan_containew(stwuct fsw_mc_device *mc_bus_dev,
			boow awwoc_intewwupts);

void dpwc_wemove_devices(stwuct fsw_mc_device *mc_bus_dev,
			 stwuct fsw_mc_obj_desc *obj_desc_awway,
			 int num_chiwd_objects_in_mc);

int dpwc_cweanup(stwuct fsw_mc_device *mc_dev);

int dpwc_setup(stwuct fsw_mc_device *mc_dev);

/**
 * Maximum numbew of totaw IWQs that can be pwe-awwocated fow an MC bus'
 * IWQ poow
 */
#define FSW_MC_IWQ_POOW_MAX_TOTAW_IWQS	256

int fsw_mc_popuwate_iwq_poow(stwuct fsw_mc_device *mc_bus_dev,
			     unsigned int iwq_count);

void fsw_mc_cweanup_iwq_poow(stwuct fsw_mc_device *mc_bus_dev);

/*
 * Data Path Buffew Poow (DPBP) API
 * Contains initiawization APIs and wuntime contwow APIs fow DPBP
 */

int dpbp_open(stwuct fsw_mc_io *mc_io,
	      u32 cmd_fwags,
	      int dpbp_id,
	      u16 *token);

int dpbp_cwose(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token);

int dpbp_enabwe(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token);

int dpbp_disabwe(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token);

int dpbp_weset(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token);

/**
 * stwuct dpbp_attw - Stwuctuwe wepwesenting DPBP attwibutes
 * @id:		DPBP object ID
 * @bpid:	Hawdwawe buffew poow ID; shouwd be used as an awgument in
 *		acquiwe/wewease opewations on buffews
 */
stwuct dpbp_attw {
	int id;
	u16 bpid;
};

int dpbp_get_attwibutes(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpbp_attw *attw);

/* Data Path Concentwatow (DPCON) API
 * Contains initiawization APIs and wuntime contwow APIs fow DPCON
 */

/**
 * Use it to disabwe notifications; see dpcon_set_notification()
 */
#define DPCON_INVAWID_DPIO_ID		(int)(-1)

int dpcon_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpcon_id,
	       u16 *token);

int dpcon_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token);

int dpcon_enabwe(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token);

int dpcon_disabwe(stwuct fsw_mc_io *mc_io,
		  u32 cmd_fwags,
		  u16 token);

int dpcon_weset(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token);

int fsw_mc_obj_open(stwuct fsw_mc_io *mc_io,
		    u32 cmd_fwags,
		    int obj_id,
		    chaw *obj_type,
		    u16 *token);

int fsw_mc_obj_cwose(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token);

int fsw_mc_obj_weset(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token);

/**
 * stwuct dpcon_attw - Stwuctuwe wepwesenting DPCON attwibutes
 * @id: DPCON object ID
 * @qbman_ch_id: Channew ID to be used by dequeue opewation
 * @num_pwiowities: Numbew of pwiowities fow the DPCON channew (1-8)
 */
stwuct dpcon_attw {
	int id;
	u16 qbman_ch_id;
	u8 num_pwiowities;
};

int dpcon_get_attwibutes(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 stwuct dpcon_attw *attw);

/**
 * stwuct dpcon_notification_cfg - Stwuctuwe wepwesenting notification pawams
 * @dpio_id:	DPIO object ID; must be configuwed with a notification channew;
 *	to disabwe notifications set it to 'DPCON_INVAWID_DPIO_ID';
 * @pwiowity:	Pwiowity sewection within the DPIO channew; vawid vawues
 *		awe 0-7, depending on the numbew of pwiowities in that channew
 * @usew_ctx:	Usew context vawue pwovided with each CDAN message
 */
stwuct dpcon_notification_cfg {
	int dpio_id;
	u8 pwiowity;
	u64 usew_ctx;
};

int dpcon_set_notification(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   stwuct dpcon_notification_cfg *cfg);

#endif /* _FSW_MC_H_ */
