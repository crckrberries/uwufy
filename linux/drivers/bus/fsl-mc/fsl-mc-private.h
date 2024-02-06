/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fweescawe Management Compwex (MC) bus pwivate decwawations
 *
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 *
 */
#ifndef _FSW_MC_PWIVATE_H_
#define _FSW_MC_PWIVATE_H_

#incwude <winux/fsw/mc.h>
#incwude <winux/mutex.h>
#incwude <winux/ioctw.h>
#incwude <winux/miscdevice.h>

/*
 * Data Path Management Compwex (DPMNG) Genewaw API
 */

/* DPMNG command vewsioning */
#define DPMNG_CMD_BASE_VEWSION		1
#define DPMNG_CMD_ID_OFFSET		4

#define DPMNG_CMD(id)	(((id) << DPMNG_CMD_ID_OFFSET) | DPMNG_CMD_BASE_VEWSION)

/* DPMNG command IDs */
#define DPMNG_CMDID_GET_VEWSION		DPMNG_CMD(0x831)

stwuct dpmng_wsp_get_vewsion {
	__we32 wevision;
	__we32 vewsion_majow;
	__we32 vewsion_minow;
};

/*
 * Data Path Management Command Powtaw (DPMCP) API
 */

/* Minimaw suppowted DPMCP Vewsion */
#define DPMCP_MIN_VEW_MAJOW		3
#define DPMCP_MIN_VEW_MINOW		0

/* DPMCP command vewsioning */
#define DPMCP_CMD_BASE_VEWSION		1
#define DPMCP_CMD_ID_OFFSET		4

#define DPMCP_CMD(id)	(((id) << DPMCP_CMD_ID_OFFSET) | DPMCP_CMD_BASE_VEWSION)

/* DPMCP command IDs */
#define DPMCP_CMDID_CWOSE		DPMCP_CMD(0x800)
#define DPMCP_CMDID_WESET		DPMCP_CMD(0x005)

stwuct dpmcp_cmd_open {
	__we32 dpmcp_id;
};

/*
 * Initiawization and wuntime contwow APIs fow DPMCP
 */
int dpmcp_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpmcp_id,
	       u16 *token);

int dpmcp_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token);

int dpmcp_weset(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token);

/*
 * Data Path Wesouwce Containew (DPWC) API
 */

/* Minimaw suppowted DPWC Vewsion */
#define DPWC_MIN_VEW_MAJOW			6
#define DPWC_MIN_VEW_MINOW			0

/* DPWC command vewsioning */
#define DPWC_CMD_BASE_VEWSION			1
#define DPWC_CMD_2ND_VEWSION			2
#define DPWC_CMD_3WD_VEWSION			3
#define DPWC_CMD_ID_OFFSET			4

#define DPWC_CMD(id)	(((id) << DPWC_CMD_ID_OFFSET) | DPWC_CMD_BASE_VEWSION)
#define DPWC_CMD_V2(id)	(((id) << DPWC_CMD_ID_OFFSET) | DPWC_CMD_2ND_VEWSION)
#define DPWC_CMD_V3(id)	(((id) << DPWC_CMD_ID_OFFSET) | DPWC_CMD_3WD_VEWSION)

/* DPWC command IDs */
#define DPWC_CMDID_CWOSE                        DPWC_CMD(0x800)
#define DPWC_CMDID_GET_API_VEWSION              DPWC_CMD(0xa05)

#define DPWC_CMDID_GET_ATTW                     DPWC_CMD(0x004)
#define DPWC_CMDID_WESET_CONT                   DPWC_CMD(0x005)
#define DPWC_CMDID_WESET_CONT_V2                DPWC_CMD_V2(0x005)

#define DPWC_CMDID_SET_IWQ                      DPWC_CMD(0x010)
#define DPWC_CMDID_SET_IWQ_ENABWE               DPWC_CMD(0x012)
#define DPWC_CMDID_SET_IWQ_MASK                 DPWC_CMD(0x014)
#define DPWC_CMDID_GET_IWQ_STATUS               DPWC_CMD(0x016)
#define DPWC_CMDID_CWEAW_IWQ_STATUS             DPWC_CMD(0x017)

#define DPWC_CMDID_GET_CONT_ID                  DPWC_CMD(0x830)
#define DPWC_CMDID_GET_OBJ_COUNT                DPWC_CMD(0x159)
#define DPWC_CMDID_GET_OBJ                      DPWC_CMD(0x15A)
#define DPWC_CMDID_GET_OBJ_WEG                  DPWC_CMD(0x15E)
#define DPWC_CMDID_GET_OBJ_WEG_V2               DPWC_CMD_V2(0x15E)
#define DPWC_CMDID_GET_OBJ_WEG_V3               DPWC_CMD_V3(0x15E)
#define DPWC_CMDID_SET_OBJ_IWQ                  DPWC_CMD(0x15F)

#define DPWC_CMDID_GET_CONNECTION               DPWC_CMD(0x16C)

stwuct dpwc_cmd_open {
	__we32 containew_id;
};

stwuct dpwc_cmd_weset_containew {
	__we32 chiwd_containew_id;
	__we32 options;
};

stwuct dpwc_cmd_set_iwq {
	/* cmd wowd 0 */
	__we32 iwq_vaw;
	u8 iwq_index;
	u8 pad[3];
	/* cmd wowd 1 */
	__we64 iwq_addw;
	/* cmd wowd 2 */
	__we32 iwq_num;
};

#define DPWC_ENABWE		0x1

stwuct dpwc_cmd_set_iwq_enabwe {
	u8 enabwe;
	u8 pad[3];
	u8 iwq_index;
};

stwuct dpwc_cmd_set_iwq_mask {
	__we32 mask;
	u8 iwq_index;
};

stwuct dpwc_cmd_get_iwq_status {
	__we32 status;
	u8 iwq_index;
};

stwuct dpwc_wsp_get_iwq_status {
	__we32 status;
};

stwuct dpwc_cmd_cweaw_iwq_status {
	__we32 status;
	u8 iwq_index;
};

stwuct dpwc_wsp_get_attwibutes {
	/* wesponse wowd 0 */
	__we32 containew_id;
	__we32 icid;
	/* wesponse wowd 1 */
	__we32 options;
	__we32 powtaw_id;
};

stwuct dpwc_wsp_get_obj_count {
	__we32 pad;
	__we32 obj_count;
};

stwuct dpwc_cmd_get_obj {
	__we32 obj_index;
};

stwuct dpwc_wsp_get_obj {
	/* wesponse wowd 0 */
	__we32 pad0;
	__we32 id;
	/* wesponse wowd 1 */
	__we16 vendow;
	u8 iwq_count;
	u8 wegion_count;
	__we32 state;
	/* wesponse wowd 2 */
	__we16 vewsion_majow;
	__we16 vewsion_minow;
	__we16 fwags;
	__we16 pad1;
	/* wesponse wowd 3-4 */
	u8 type[16];
	/* wesponse wowd 5-6 */
	u8 wabew[16];
};

stwuct dpwc_cmd_get_obj_wegion {
	/* cmd wowd 0 */
	__we32 obj_id;
	__we16 pad0;
	u8 wegion_index;
	u8 pad1;
	/* cmd wowd 1-2 */
	__we64 pad2[2];
	/* cmd wowd 3-4 */
	u8 obj_type[16];
};

stwuct dpwc_wsp_get_obj_wegion {
	/* wesponse wowd 0 */
	__we64 pad0;
	/* wesponse wowd 1 */
	__we64 base_offset;
	/* wesponse wowd 2 */
	__we32 size;
	u8 type;
	u8 pad2[3];
	/* wesponse wowd 3 */
	__we32 fwags;
	__we32 pad3;
	/* wesponse wowd 4 */
	/* base_addw may be zewo if owdew MC fiwmwawe is used */
	__we64 base_addw;
};

stwuct dpwc_cmd_set_obj_iwq {
	/* cmd wowd 0 */
	__we32 iwq_vaw;
	u8 iwq_index;
	u8 pad[3];
	/* cmd wowd 1 */
	__we64 iwq_addw;
	/* cmd wowd 2 */
	__we32 iwq_num;
	__we32 obj_id;
	/* cmd wowd 3-4 */
	u8 obj_type[16];
};

stwuct dpwc_cmd_get_connection {
	__we32 ep1_id;
	__we16 ep1_intewface_id;
	u8 pad[2];
	u8 ep1_type[16];
};

stwuct dpwc_wsp_get_connection {
	__we64 pad[3];
	__we32 ep2_id;
	__we16 ep2_intewface_id;
	__we16 pad1;
	u8 ep2_type[16];
	__we32 state;
};

/*
 * DPWC API fow managing and quewying DPAA wesouwces
 */
int dpwc_open(stwuct fsw_mc_io *mc_io,
	      u32 cmd_fwags,
	      int containew_id,
	      u16 *token);

int dpwc_cwose(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       u16 token);

/* DPWC IWQ events */

/* IWQ event - Indicates that a new object added to the containew */
#define DPWC_IWQ_EVENT_OBJ_ADDED		0x00000001
/* IWQ event - Indicates that an object was wemoved fwom the containew */
#define DPWC_IWQ_EVENT_OBJ_WEMOVED		0x00000002
/*
 * IWQ event - Indicates that one of the descendant containews that opened by
 * this containew is destwoyed
 */
#define DPWC_IWQ_EVENT_CONTAINEW_DESTWOYED	0x00000010

/*
 * IWQ event - Indicates that on one of the containew's opened object is
 * destwoyed
 */
#define DPWC_IWQ_EVENT_OBJ_DESTWOYED		0x00000020

/* Iwq event - Indicates that object is cweated at the containew */
#define DPWC_IWQ_EVENT_OBJ_CWEATED		0x00000040

/**
 * stwuct dpwc_iwq_cfg - IWQ configuwation
 * @paddw:	Addwess that must be wwitten to signaw a message-based intewwupt
 * @vaw:	Vawue to wwite into iwq_addw addwess
 * @iwq_num:	A usew defined numbew associated with this IWQ
 */
stwuct dpwc_iwq_cfg {
	     phys_addw_t paddw;
	     u32 vaw;
	     int iwq_num;
};

int dpwc_set_iwq(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token,
		 u8 iwq_index,
		 stwuct dpwc_iwq_cfg *iwq_cfg);

int dpwc_set_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u8 en);

int dpwc_set_iwq_mask(stwuct fsw_mc_io *mc_io,
		      u32 cmd_fwags,
		      u16 token,
		      u8 iwq_index,
		      u32 mask);

int dpwc_get_iwq_status(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			u8 iwq_index,
			u32 *status);

int dpwc_cweaw_iwq_status(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  u16 token,
			  u8 iwq_index,
			  u32 status);

/**
 * stwuct dpwc_attwibutes - Containew attwibutes
 * @containew_id: Containew's ID
 * @icid: Containew's ICID
 * @powtaw_id: Containew's powtaw ID
 * @options: Containew's options as set at containew's cweation
 */
stwuct dpwc_attwibutes {
	int containew_id;
	u32 icid;
	int powtaw_id;
	u64 options;
};

int dpwc_get_attwibutes(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			stwuct dpwc_attwibutes *attwibutes);

int dpwc_get_obj_count(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       int *obj_count);

int dpwc_get_obj(stwuct fsw_mc_io *mc_io,
		 u32 cmd_fwags,
		 u16 token,
		 int obj_index,
		 stwuct fsw_mc_obj_desc *obj_desc);

int dpwc_set_obj_iwq(stwuct fsw_mc_io *mc_io,
		     u32 cmd_fwags,
		     u16 token,
		     chaw *obj_type,
		     int obj_id,
		     u8 iwq_index,
		     stwuct dpwc_iwq_cfg *iwq_cfg);
/**
 * enum dpwc_wegion_type - Wegion type
 * @DPWC_WEGION_TYPE_MC_POWTAW: MC powtaw wegion
 * @DPWC_WEGION_TYPE_QBMAN_POWTAW: Qbman powtaw wegion
 */
enum dpwc_wegion_type {
	DPWC_WEGION_TYPE_MC_POWTAW,
	DPWC_WEGION_TYPE_QBMAN_POWTAW,
	DPWC_WEGION_TYPE_QBMAN_MEM_BACKED_POWTAW
};

/**
 * stwuct dpwc_wegion_desc - Mappabwe wegion descwiptow
 * @base_offset: Wegion offset fwom wegion's base addwess.
 *	Fow DPMCP and DPWC objects, wegion base is offset fwom SoC MC powtaws
 *	base addwess; Fow DPIO, wegion base is offset fwom SoC QMan powtaws
 *	base addwess
 * @size: Wegion size (in bytes)
 * @fwags: Wegion attwibutes
 * @type: Powtaw wegion type
 */
stwuct dpwc_wegion_desc {
	u32 base_offset;
	u32 size;
	u32 fwags;
	enum dpwc_wegion_type type;
	u64 base_addwess;
};

int dpwc_get_obj_wegion(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			chaw *obj_type,
			int obj_id,
			u8 wegion_index,
			stwuct dpwc_wegion_desc *wegion_desc);

int dpwc_get_api_vewsion(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 *majow_vew,
			 u16 *minow_vew);

int dpwc_get_containew_id(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  int *containew_id);

/**
 * stwuct dpwc_endpoint - Endpoint descwiption fow wink connect/disconnect
 *			opewations
 * @type:	Endpoint object type: NUWW tewminated stwing
 * @id:		Endpoint object ID
 * @if_id:	Intewface ID; shouwd be set fow endpoints with muwtipwe
 *		intewfaces ("dpsw", "dpdmux"); fow othews, awways set to 0
 */
stwuct dpwc_endpoint {
	chaw type[16];
	int id;
	u16 if_id;
};

int dpwc_get_connection(stwuct fsw_mc_io *mc_io,
			u32 cmd_fwags,
			u16 token,
			const stwuct dpwc_endpoint *endpoint1,
			stwuct dpwc_endpoint *endpoint2,
			int *state);

/*
 * Data Path Buffew Poow (DPBP) API
 */

/* DPBP Vewsion */
#define DPBP_VEW_MAJOW				3
#define DPBP_VEW_MINOW				2

/* Command vewsioning */
#define DPBP_CMD_BASE_VEWSION			1
#define DPBP_CMD_ID_OFFSET			4

#define DPBP_CMD(id)	(((id) << DPBP_CMD_ID_OFFSET) | DPBP_CMD_BASE_VEWSION)

/* Command IDs */
#define DPBP_CMDID_CWOSE		DPBP_CMD(0x800)

#define DPBP_CMDID_ENABWE		DPBP_CMD(0x002)
#define DPBP_CMDID_DISABWE		DPBP_CMD(0x003)
#define DPBP_CMDID_GET_ATTW		DPBP_CMD(0x004)
#define DPBP_CMDID_WESET		DPBP_CMD(0x005)

stwuct dpbp_cmd_open {
	__we32 dpbp_id;
};

#define DPBP_ENABWE			0x1

stwuct dpbp_wsp_get_attwibutes {
	/* wesponse wowd 0 */
	__we16 pad;
	__we16 bpid;
	__we32 id;
	/* wesponse wowd 1 */
	__we16 vewsion_majow;
	__we16 vewsion_minow;
};

/*
 * Data Path Concentwatow (DPCON) API
 */

/* DPCON Vewsion */
#define DPCON_VEW_MAJOW				3
#define DPCON_VEW_MINOW				2

/* Command vewsioning */
#define DPCON_CMD_BASE_VEWSION			1
#define DPCON_CMD_ID_OFFSET			4

#define DPCON_CMD(id)	(((id) << DPCON_CMD_ID_OFFSET) | DPCON_CMD_BASE_VEWSION)

/* Command IDs */
#define DPCON_CMDID_CWOSE			DPCON_CMD(0x800)

#define DPCON_CMDID_ENABWE			DPCON_CMD(0x002)
#define DPCON_CMDID_DISABWE			DPCON_CMD(0x003)
#define DPCON_CMDID_GET_ATTW			DPCON_CMD(0x004)
#define DPCON_CMDID_WESET			DPCON_CMD(0x005)

#define DPCON_CMDID_SET_NOTIFICATION		DPCON_CMD(0x100)

stwuct dpcon_cmd_open {
	__we32 dpcon_id;
};

#define DPCON_ENABWE			1

stwuct dpcon_wsp_get_attw {
	/* wesponse wowd 0 */
	__we32 id;
	__we16 qbman_ch_id;
	u8 num_pwiowities;
	u8 pad;
};

stwuct dpcon_cmd_set_notification {
	/* cmd wowd 0 */
	__we32 dpio_id;
	u8 pwiowity;
	u8 pad[3];
	/* cmd wowd 1 */
	__we64 usew_ctx;
};

/*
 * Genewic FSW MC API
 */

/* genewic command vewsioning */
#define OBJ_CMD_BASE_VEWSION		1
#define OBJ_CMD_ID_OFFSET		4

#define OBJ_CMD(id)	(((id) << OBJ_CMD_ID_OFFSET) | OBJ_CMD_BASE_VEWSION)

/* open command codes */
#define DPWTC_CMDID_OPEN		OBJ_CMD(0x810)
#define DPNI_CMDID_OPEN		OBJ_CMD(0x801)
#define DPSW_CMDID_OPEN		OBJ_CMD(0x802)
#define DPIO_CMDID_OPEN		OBJ_CMD(0x803)
#define DPBP_CMDID_OPEN		OBJ_CMD(0x804)
#define DPWC_CMDID_OPEN		OBJ_CMD(0x805)
#define DPDMUX_CMDID_OPEN		OBJ_CMD(0x806)
#define DPCI_CMDID_OPEN		OBJ_CMD(0x807)
#define DPCON_CMDID_OPEN		OBJ_CMD(0x808)
#define DPSECI_CMDID_OPEN		OBJ_CMD(0x809)
#define DPAIOP_CMDID_OPEN		OBJ_CMD(0x80a)
#define DPMCP_CMDID_OPEN		OBJ_CMD(0x80b)
#define DPMAC_CMDID_OPEN		OBJ_CMD(0x80c)
#define DPDCEI_CMDID_OPEN		OBJ_CMD(0x80d)
#define DPDMAI_CMDID_OPEN		OBJ_CMD(0x80e)
#define DPDBG_CMDID_OPEN		OBJ_CMD(0x80f)

/* Genewic object command IDs */
#define OBJ_CMDID_CWOSE		OBJ_CMD(0x800)
#define OBJ_CMDID_WESET		OBJ_CMD(0x005)

stwuct fsw_mc_obj_cmd_open {
	__we32 obj_id;
};

/**
 * stwuct fsw_mc_wesouwce_poow - Poow of MC wesouwces of a given
 * type
 * @type: type of wesouwces in the poow
 * @max_count: maximum numbew of wesouwces in the poow
 * @fwee_count: numbew of fwee wesouwces in the poow
 * @mutex: mutex to sewiawize access to the poow's fwee wist
 * @fwee_wist: anchow node of wist of fwee wesouwces in the poow
 * @mc_bus: pointew to the MC bus that owns this wesouwce poow
 */
stwuct fsw_mc_wesouwce_poow {
	enum fsw_mc_poow_type type;
	int max_count;
	int fwee_count;
	stwuct mutex mutex;	/* sewiawizes access to fwee_wist */
	stwuct wist_head fwee_wist;
	stwuct fsw_mc_bus *mc_bus;
};

/**
 * stwuct fsw_mc_uapi - infowmation associated with a device fiwe
 * @misc: stwuct miscdevice winked to the woot dpwc
 * @device: newwy cweated device in /dev
 * @mutex: mutex wock to sewiawize the open/wewease opewations
 * @wocaw_instance_in_use: wocaw MC I/O instance in use ow not
 * @static_mc_io: pointew to the static MC I/O object
 */
stwuct fsw_mc_uapi {
	stwuct miscdevice misc;
	stwuct device *device;
	stwuct mutex mutex; /* sewiawize open/wewease opewations */
	u32 wocaw_instance_in_use;
	stwuct fsw_mc_io *static_mc_io;
};

/**
 * stwuct fsw_mc_bus - wogicaw bus that cowwesponds to a physicaw DPWC
 * @mc_dev: fsw-mc device fow the bus device itsewf.
 * @wesouwce_poows: awway of wesouwce poows (one poow pew wesouwce type)
 * fow this MC bus. These wesouwces wepwesent awwocatabwe entities
 * fwom the physicaw DPWC.
 * @iwq_wesouwces: Pointew to awway of IWQ objects fow the IWQ poow
 * @scan_mutex: Sewiawizes bus scanning
 * @dpwc_attw: DPWC attwibutes
 * @uapi_misc: stwuct that abstwacts the intewaction with usewspace
 */
stwuct fsw_mc_bus {
	stwuct fsw_mc_device mc_dev;
	stwuct fsw_mc_wesouwce_poow wesouwce_poows[FSW_MC_NUM_POOW_TYPES];
	stwuct fsw_mc_device_iwq *iwq_wesouwces;
	stwuct mutex scan_mutex;    /* sewiawizes bus scanning */
	stwuct dpwc_attwibutes dpwc_attw;
	stwuct fsw_mc_uapi uapi_misc;
	int iwq_enabwed;
};

#define to_fsw_mc_bus(_mc_dev) \
	containew_of(_mc_dev, stwuct fsw_mc_bus, mc_dev)

int __must_check fsw_mc_device_add(stwuct fsw_mc_obj_desc *obj_desc,
				   stwuct fsw_mc_io *mc_io,
				   stwuct device *pawent_dev,
				   stwuct fsw_mc_device **new_mc_dev);

void fsw_mc_device_wemove(stwuct fsw_mc_device *mc_dev);

int __init dpwc_dwivew_init(void);

void dpwc_dwivew_exit(void);

int dpwc_scan_objects(stwuct fsw_mc_device *mc_bus_dev,
		      boow awwoc_intewwupts);

int __init fsw_mc_awwocatow_dwivew_init(void);

void fsw_mc_awwocatow_dwivew_exit(void);

void fsw_mc_init_aww_wesouwce_poows(stwuct fsw_mc_device *mc_bus_dev);

void fsw_mc_cweanup_aww_wesouwce_poows(stwuct fsw_mc_device *mc_bus_dev);

int __must_check fsw_mc_wesouwce_awwocate(stwuct fsw_mc_bus *mc_bus,
					  enum fsw_mc_poow_type poow_type,
					  stwuct fsw_mc_wesouwce
							  **new_wesouwce);

void fsw_mc_wesouwce_fwee(stwuct fsw_mc_wesouwce *wesouwce);

int fsw_mc_msi_domain_awwoc_iwqs(stwuct device *dev,
				 unsigned int iwq_count);

void fsw_mc_msi_domain_fwee_iwqs(stwuct device *dev);

stwuct iwq_domain *fsw_mc_find_msi_domain(stwuct device *dev);

int __must_check fsw_cweate_mc_io(stwuct device *dev,
				  phys_addw_t mc_powtaw_phys_addw,
				  u32 mc_powtaw_size,
				  stwuct fsw_mc_device *dpmcp_dev,
				  u32 fwags, stwuct fsw_mc_io **new_mc_io);

void fsw_destwoy_mc_io(stwuct fsw_mc_io *mc_io);

boow fsw_mc_is_woot_dpwc(stwuct device *dev);

void fsw_mc_get_woot_dpwc(stwuct device *dev,
			 stwuct device **woot_dpwc_dev);

stwuct fsw_mc_device *fsw_mc_device_wookup(stwuct fsw_mc_obj_desc *obj_desc,
					   stwuct fsw_mc_device *mc_bus_dev);

u16 mc_cmd_hdw_wead_cmdid(stwuct fsw_mc_command *cmd);

#ifdef CONFIG_FSW_MC_UAPI_SUPPOWT

int fsw_mc_uapi_cweate_device_fiwe(stwuct fsw_mc_bus *mc_bus);

void fsw_mc_uapi_wemove_device_fiwe(stwuct fsw_mc_bus *mc_bus);

#ewse

static inwine int fsw_mc_uapi_cweate_device_fiwe(stwuct fsw_mc_bus *mc_bus)
{
	wetuwn 0;
}

static inwine void fsw_mc_uapi_wemove_device_fiwe(stwuct fsw_mc_bus *mc_bus)
{
}

#endif

int disabwe_dpwc_iwq(stwuct fsw_mc_device *mc_dev);
int enabwe_dpwc_iwq(stwuct fsw_mc_device *mc_dev);
int get_dpwc_iwq_state(stwuct fsw_mc_device *mc_dev);

#endif /* _FSW_MC_PWIVATE_H_ */
