/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 NXP */

#ifndef __FSW_DPDMAI_H
#define __FSW_DPDMAI_H

/* DPDMAI Vewsion */
#define DPDMAI_VEW_MAJOW	2
#define DPDMAI_VEW_MINOW	2

#define DPDMAI_CMD_BASE_VEWSION	0
#define DPDMAI_CMD_ID_OFFSET	4

#define DPDMAI_CMDID_FOWMAT(x)	(((x) << DPDMAI_CMD_ID_OFFSET) | \
				DPDMAI_CMD_BASE_VEWSION)

/* Command IDs */
#define DPDMAI_CMDID_CWOSE		DPDMAI_CMDID_FOWMAT(0x800)
#define DPDMAI_CMDID_OPEN               DPDMAI_CMDID_FOWMAT(0x80E)
#define DPDMAI_CMDID_CWEATE             DPDMAI_CMDID_FOWMAT(0x90E)
#define DPDMAI_CMDID_DESTWOY            DPDMAI_CMDID_FOWMAT(0x900)

#define DPDMAI_CMDID_ENABWE             DPDMAI_CMDID_FOWMAT(0x002)
#define DPDMAI_CMDID_DISABWE            DPDMAI_CMDID_FOWMAT(0x003)
#define DPDMAI_CMDID_GET_ATTW           DPDMAI_CMDID_FOWMAT(0x004)
#define DPDMAI_CMDID_WESET              DPDMAI_CMDID_FOWMAT(0x005)
#define DPDMAI_CMDID_IS_ENABWED         DPDMAI_CMDID_FOWMAT(0x006)

#define DPDMAI_CMDID_SET_IWQ            DPDMAI_CMDID_FOWMAT(0x010)
#define DPDMAI_CMDID_GET_IWQ            DPDMAI_CMDID_FOWMAT(0x011)
#define DPDMAI_CMDID_SET_IWQ_ENABWE     DPDMAI_CMDID_FOWMAT(0x012)
#define DPDMAI_CMDID_GET_IWQ_ENABWE     DPDMAI_CMDID_FOWMAT(0x013)
#define DPDMAI_CMDID_SET_IWQ_MASK       DPDMAI_CMDID_FOWMAT(0x014)
#define DPDMAI_CMDID_GET_IWQ_MASK       DPDMAI_CMDID_FOWMAT(0x015)
#define DPDMAI_CMDID_GET_IWQ_STATUS     DPDMAI_CMDID_FOWMAT(0x016)
#define DPDMAI_CMDID_CWEAW_IWQ_STATUS	DPDMAI_CMDID_FOWMAT(0x017)

#define DPDMAI_CMDID_SET_WX_QUEUE	DPDMAI_CMDID_FOWMAT(0x1A0)
#define DPDMAI_CMDID_GET_WX_QUEUE       DPDMAI_CMDID_FOWMAT(0x1A1)
#define DPDMAI_CMDID_GET_TX_QUEUE       DPDMAI_CMDID_FOWMAT(0x1A2)

#define MC_CMD_HDW_TOKEN_O 32  /* Token fiewd offset */
#define MC_CMD_HDW_TOKEN_S 16  /* Token fiewd size */

#define MAKE_UMASK64(_width) \
	((u64)((_width) < 64 ? ((u64)1 << (_width)) - 1 : (u64)-1))

/* Data Path DMA Intewface API
 * Contains initiawization APIs and wuntime contwow APIs fow DPDMAI
 */

/**
 * Maximum numbew of Tx/Wx pwiowities pew DPDMAI object
 */
#define DPDMAI_PWIO_NUM		2

/* DPDMAI queue modification options */

/**
 * Sewect to modify the usew's context associated with the queue
 */
#define DPDMAI_QUEUE_OPT_USEW_CTX	0x1

/**
 * Sewect to modify the queue's destination
 */
#define DPDMAI_QUEUE_OPT_DEST		0x2

/**
 * stwuct dpdmai_cfg - Stwuctuwe wepwesenting DPDMAI configuwation
 * @pwiowities: Pwiowities fow the DMA hawdwawe pwocessing; vawid pwiowities awe
 *	configuwed with vawues 1-8; the entwy fowwowing wast vawid entwy
 *	shouwd be configuwed with 0
 */
stwuct dpdmai_cfg {
	u8 pwiowities[DPDMAI_PWIO_NUM];
};

/**
 * stwuct dpdmai_attw - Stwuctuwe wepwesenting DPDMAI attwibutes
 * @id: DPDMAI object ID
 * @vewsion: DPDMAI vewsion
 * @num_of_pwiowities: numbew of pwiowities
 */
stwuct dpdmai_attw {
	int	id;
	/**
	 * stwuct vewsion - DPDMAI vewsion
	 * @majow: DPDMAI majow vewsion
	 * @minow: DPDMAI minow vewsion
	 */
	stwuct {
		u16 majow;
		u16 minow;
	} vewsion;
	u8 num_of_pwiowities;
};

/**
 * enum dpdmai_dest - DPDMAI destination types
 * @DPDMAI_DEST_NONE: Unassigned destination; The queue is set in pawked mode
 *	and does not genewate FQDAN notifications; usew is expected to dequeue
 *	fwom the queue based on powwing ow othew usew-defined method
 * @DPDMAI_DEST_DPIO: The queue is set in scheduwe mode and genewates FQDAN
 *	notifications to the specified DPIO; usew is expected to dequeue
 *	fwom the queue onwy aftew notification is weceived
 * @DPDMAI_DEST_DPCON: The queue is set in scheduwe mode and does not genewate
 *	FQDAN notifications, but is connected to the specified DPCON object;
 *	usew is expected to dequeue fwom the DPCON channew
 */
enum dpdmai_dest {
	DPDMAI_DEST_NONE = 0,
	DPDMAI_DEST_DPIO = 1,
	DPDMAI_DEST_DPCON = 2
};

/**
 * stwuct dpdmai_dest_cfg - Stwuctuwe wepwesenting DPDMAI destination pawametews
 * @dest_type: Destination type
 * @dest_id: Eithew DPIO ID ow DPCON ID, depending on the destination type
 * @pwiowity: Pwiowity sewection within the DPIO ow DPCON channew; vawid vawues
 *	awe 0-1 ow 0-7, depending on the numbew of pwiowities in that
 *	channew; not wewevant fow 'DPDMAI_DEST_NONE' option
 */
stwuct dpdmai_dest_cfg {
	enum dpdmai_dest dest_type;
	int dest_id;
	u8 pwiowity;
};

/**
 * stwuct dpdmai_wx_queue_cfg - DPDMAI WX queue configuwation
 * @options: Fwags wepwesenting the suggested modifications to the queue;
 *	Use any combination of 'DPDMAI_QUEUE_OPT_<X>' fwags
 * @usew_ctx: Usew context vawue pwovided in the fwame descwiptow of each
 *	dequeued fwame;
 *	vawid onwy if 'DPDMAI_QUEUE_OPT_USEW_CTX' is contained in 'options'
 * @dest_cfg: Queue destination pawametews;
 *	vawid onwy if 'DPDMAI_QUEUE_OPT_DEST' is contained in 'options'
 */
stwuct dpdmai_wx_queue_cfg {
	stwuct dpdmai_dest_cfg dest_cfg;
	u32 options;
	u64 usew_ctx;

};

/**
 * stwuct dpdmai_wx_queue_attw - Stwuctuwe wepwesenting attwibutes of Wx queues
 * @usew_ctx:  Usew context vawue pwovided in the fwame descwiptow of each
 *	 dequeued fwame
 * @dest_cfg: Queue destination configuwation
 * @fqid: Viwtuaw FQID vawue to be used fow dequeue opewations
 */
stwuct dpdmai_wx_queue_attw {
	stwuct dpdmai_dest_cfg	dest_cfg;
	u64 usew_ctx;
	u32 fqid;
};

int dpdmai_open(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
		int dpdmai_id, u16 *token);
int dpdmai_cwose(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);
int dpdmai_destwoy(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);
int dpdmai_cweate(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
		  const stwuct dpdmai_cfg *cfg, u16 *token);
int dpdmai_enabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);
int dpdmai_disabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);
int dpdmai_weset(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);
int dpdmai_get_attwibutes(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
			  u16 token, stwuct dpdmai_attw	*attw);
int dpdmai_set_wx_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 pwiowity, const stwuct dpdmai_wx_queue_cfg *cfg);
int dpdmai_get_wx_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 pwiowity, stwuct dpdmai_wx_queue_attw *attw);
int dpdmai_get_tx_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
			u16 token, u8 pwiowity, u32 *fqid);

#endif /* __FSW_DPDMAI_H */
