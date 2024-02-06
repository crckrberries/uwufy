/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2014-2016 Fweescawe Semiconductow Inc.
 * Copywight 2017-2021 NXP
 *
 */

#ifndef __FSW_DPSW_H
#define __FSW_DPSW_H

/* Data Path W2-Switch API
 * Contains API fow handwing DPSW topowogy and functionawity
 */

stwuct fsw_mc_io;

/* DPSW genewaw definitions */

#define DPSW_MAX_PWIOWITIES	8

#define DPSW_MAX_IF		64

int dpsw_open(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, int dpsw_id, u16 *token);

int dpsw_cwose(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);

/* DPSW options */

/**
 * DPSW_OPT_FWOODING_DIS - Fwooding was disabwed at device cweate
 */
#define DPSW_OPT_FWOODING_DIS		0x0000000000000001UWW
/**
 * DPSW_OPT_MUWTICAST_DIS - Muwticast was disabwed at device cweate
 */
#define DPSW_OPT_MUWTICAST_DIS		0x0000000000000004UWW
/**
 * DPSW_OPT_CTWW_IF_DIS - Contwow intewface suppowt is disabwed
 */
#define DPSW_OPT_CTWW_IF_DIS		0x0000000000000010UWW

/**
 * enum dpsw_component_type - component type of a bwidge
 * @DPSW_COMPONENT_TYPE_C_VWAN: A C-VWAN component of an
 *   entewpwise VWAN bwidge ow of a Pwovidew Bwidge used
 *   to pwocess C-tagged fwames
 * @DPSW_COMPONENT_TYPE_S_VWAN: An S-VWAN component of a
 *   Pwovidew Bwidge
 *
 */
enum dpsw_component_type {
	DPSW_COMPONENT_TYPE_C_VWAN = 0,
	DPSW_COMPONENT_TYPE_S_VWAN
};

/**
 *  enum dpsw_fwooding_cfg - fwooding configuwation wequested
 * @DPSW_FWOODING_PEW_VWAN: Fwooding wepwicatows awe awwocated pew VWAN and
 * intewfaces pwesent in each of them can be configuwed using
 * dpsw_vwan_add_if_fwooding()/dpsw_vwan_wemove_if_fwooding().
 * This is the defauwt configuwation.
 *
 * @DPSW_FWOODING_PEW_FDB: Fwooding wepwicatows awe awwocated pew FDB and
 * intewfaces pwesent in each of them can be configuwed using
 * dpsw_set_egwess_fwood().
 */
enum dpsw_fwooding_cfg {
	DPSW_FWOODING_PEW_VWAN = 0,
	DPSW_FWOODING_PEW_FDB,
};

/**
 * enum dpsw_bwoadcast_cfg - bwoadcast configuwation wequested
 * @DPSW_BWOADCAST_PEW_OBJECT: Thewe is onwy one bwoadcast wepwicatow pew DPSW
 * object. This is the defauwt configuwation.
 * @DPSW_BWOADCAST_PEW_FDB: Bwoadcast wepwicatows awe awwocated pew FDB and
 * intewfaces pwesent in each of them can be configuwed using
 * dpsw_set_egwess_fwood().
 */
enum dpsw_bwoadcast_cfg {
	DPSW_BWOADCAST_PEW_OBJECT = 0,
	DPSW_BWOADCAST_PEW_FDB,
};

int dpsw_enabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);

int dpsw_disabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);

int dpsw_weset(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);

/* DPSW IWQ Index and Events */

#define DPSW_IWQ_INDEX_IF		0x0000
#define DPSW_IWQ_INDEX_W2SW		0x0001

/**
 * DPSW_IWQ_EVENT_WINK_CHANGED - Indicates that the wink state changed
 */
#define DPSW_IWQ_EVENT_WINK_CHANGED	0x0001

/**
 * DPSW_IWQ_EVENT_ENDPOINT_CHANGED - Indicates a change in endpoint
 */
#define DPSW_IWQ_EVENT_ENDPOINT_CHANGED	0x0002

/**
 * stwuct dpsw_iwq_cfg - IWQ configuwation
 * @addw:	Addwess that must be wwitten to signaw a message-based intewwupt
 * @vaw:	Vawue to wwite into iwq_addw addwess
 * @iwq_num: A usew defined numbew associated with this IWQ
 */
stwuct dpsw_iwq_cfg {
	u64 addw;
	u32 vaw;
	int iwq_num;
};

int dpsw_set_iwq_enabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 iwq_index, u8 en);

int dpsw_set_iwq_mask(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		      u8 iwq_index, u32 mask);

int dpsw_get_iwq_status(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u8 iwq_index, u32 *status);

int dpsw_cweaw_iwq_status(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			  u8 iwq_index, u32 status);

/**
 * stwuct dpsw_attw - Stwuctuwe wepwesenting DPSW attwibutes
 * @id: DPSW object ID
 * @options: Enabwe/Disabwe DPSW featuwes
 * @max_vwans: Maximum Numbew of VWANs
 * @max_metews_pew_if:  Numbew of metews pew intewface
 * @max_fdbs: Maximum Numbew of FDBs
 * @max_fdb_entwies: Numbew of FDB entwies fow defauwt FDB tabwe;
 *			0 - indicates defauwt 1024 entwies.
 * @fdb_aging_time: Defauwt FDB aging time fow defauwt FDB tabwe;
 *			0 - indicates defauwt 300 seconds
 * @max_fdb_mc_gwoups: Numbew of muwticast gwoups in each FDB tabwe;
 *			0 - indicates defauwt 32
 * @mem_size: DPSW fwame stowage memowy size
 * @num_ifs: Numbew of intewfaces
 * @num_vwans: Cuwwent numbew of VWANs
 * @num_fdbs: Cuwwent numbew of FDBs
 * @component_type: Component type of this bwidge
 * @fwooding_cfg: Fwooding configuwation (PEW_VWAN - defauwt, PEW_FDB)
 * @bwoadcast_cfg: Bwoadcast configuwation (PEW_OBJECT - defauwt, PEW_FDB)
 */
stwuct dpsw_attw {
	int id;
	u64 options;
	u16 max_vwans;
	u8 max_metews_pew_if;
	u8 max_fdbs;
	u16 max_fdb_entwies;
	u16 fdb_aging_time;
	u16 max_fdb_mc_gwoups;
	u16 num_ifs;
	u16 mem_size;
	u16 num_vwans;
	u8 num_fdbs;
	enum dpsw_component_type component_type;
	enum dpsw_fwooding_cfg fwooding_cfg;
	enum dpsw_bwoadcast_cfg bwoadcast_cfg;
};

int dpsw_get_attwibutes(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			stwuct dpsw_attw *attw);

/**
 * stwuct dpsw_ctww_if_attw - Contwow intewface attwibutes
 * @wx_fqid:		Weceive FQID
 * @wx_eww_fqid:	Weceive ewwow FQID
 * @tx_eww_conf_fqid:	Twansmit ewwow and confiwmation FQID
 */
stwuct dpsw_ctww_if_attw {
	u32 wx_fqid;
	u32 wx_eww_fqid;
	u32 tx_eww_conf_fqid;
};

int dpsw_ctww_if_get_attwibutes(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
				u16 token, stwuct dpsw_ctww_if_attw *attw);

enum dpsw_queue_type {
	DPSW_QUEUE_WX,
	DPSW_QUEUE_TX_EWW_CONF,
	DPSW_QUEUE_WX_EWW,
};

#define DPSW_MAX_DPBP     8

/**
 * stwuct dpsw_ctww_if_poows_cfg - Contwow intewface buffew poows configuwation
 * @num_dpbp: Numbew of DPBPs
 * @poows: Awway of buffew poows pawametews; The numbew of vawid entwies
 *	must match 'num_dpbp' vawue
 * @poows.dpbp_id: DPBP object ID
 * @poows.buffew_size: Buffew size
 * @poows.backup_poow: Backup poow
 */
stwuct dpsw_ctww_if_poows_cfg {
	u8 num_dpbp;
	stwuct {
		int dpbp_id;
		u16 buffew_size;
		int backup_poow;
	} poows[DPSW_MAX_DPBP];
};

int dpsw_ctww_if_set_poows(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   const stwuct dpsw_ctww_if_poows_cfg *cfg);

#define DPSW_CTWW_IF_QUEUE_OPT_USEW_CTX		0x00000001
#define DPSW_CTWW_IF_QUEUE_OPT_DEST		0x00000002

enum dpsw_ctww_if_dest {
	DPSW_CTWW_IF_DEST_NONE = 0,
	DPSW_CTWW_IF_DEST_DPIO = 1,
};

stwuct dpsw_ctww_if_dest_cfg {
	enum dpsw_ctww_if_dest dest_type;
	int dest_id;
	u8 pwiowity;
};

stwuct dpsw_ctww_if_queue_cfg {
	u32 options;
	u64 usew_ctx;
	stwuct dpsw_ctww_if_dest_cfg dest_cfg;
};

int dpsw_ctww_if_set_queue(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   enum dpsw_queue_type qtype,
			   const stwuct dpsw_ctww_if_queue_cfg *cfg);

int dpsw_ctww_if_enabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);

int dpsw_ctww_if_disabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token);

/**
 * enum dpsw_action - Action sewection fow speciaw/contwow fwames
 * @DPSW_ACTION_DWOP: Dwop fwame
 * @DPSW_ACTION_WEDIWECT: Wediwect fwame to contwow powt
 */
enum dpsw_action {
	DPSW_ACTION_DWOP = 0,
	DPSW_ACTION_WEDIWECT = 1
};

#define DPSW_WINK_OPT_AUTONEG		0x0000000000000001UWW
#define DPSW_WINK_OPT_HAWF_DUPWEX	0x0000000000000002UWW
#define DPSW_WINK_OPT_PAUSE		0x0000000000000004UWW
#define DPSW_WINK_OPT_ASYM_PAUSE	0x0000000000000008UWW

/**
 * stwuct dpsw_wink_cfg - Stwuctuwe wepwesenting DPSW wink configuwation
 * @wate: Wate
 * @options: Mask of avaiwabwe options; use 'DPSW_WINK_OPT_<X>' vawues
 */
stwuct dpsw_wink_cfg {
	u32 wate;
	u64 options;
};

int dpsw_if_set_wink_cfg(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 if_id,
			 stwuct dpsw_wink_cfg *cfg);

/**
 * stwuct dpsw_wink_state - Stwuctuwe wepwesenting DPSW wink state
 * @wate: Wate
 * @options: Mask of avaiwabwe options; use 'DPSW_WINK_OPT_<X>' vawues
 * @up: 0 - covews two cases: down and disconnected, 1 - up
 */
stwuct dpsw_wink_state {
	u32 wate;
	u64 options;
	u8 up;
};

int dpsw_if_get_wink_state(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   u16 if_id, stwuct dpsw_wink_state *state);

/**
 * stwuct dpsw_tci_cfg - Tag Contwow Infowmation (TCI) configuwation
 * @pcp: Pwiowity Code Point (PCP): a 3-bit fiewd which wefews
 *		 to the IEEE 802.1p pwiowity
 * @dei: Dwop Ewigibwe Indicatow (DEI): a 1-bit fiewd. May be used
 *		 sepawatewy ow in conjunction with PCP to indicate fwames
 *		 ewigibwe to be dwopped in the pwesence of congestion
 * @vwan_id: VWAN Identifiew (VID): a 12-bit fiewd specifying the VWAN
 *			to which the fwame bewongs. The hexadecimaw vawues
 *			of 0x000 and 0xFFF awe wesewved;
 *			aww othew vawues may be used as VWAN identifiews,
 *			awwowing up to 4,094 VWANs
 */
stwuct dpsw_tci_cfg {
	u8 pcp;
	u8 dei;
	u16 vwan_id;
};

int dpsw_if_set_tci(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 if_id,
		    const stwuct dpsw_tci_cfg *cfg);

int dpsw_if_get_tci(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 if_id,
		    stwuct dpsw_tci_cfg *cfg);

/**
 * enum dpsw_stp_state - Spanning Twee Pwotocow (STP) states
 * @DPSW_STP_STATE_DISABWED: Disabwed state
 * @DPSW_STP_STATE_WISTENING: Wistening state
 * @DPSW_STP_STATE_WEAWNING: Weawning state
 * @DPSW_STP_STATE_FOWWAWDING: Fowwawding state
 * @DPSW_STP_STATE_BWOCKING: Bwocking state
 *
 */
enum dpsw_stp_state {
	DPSW_STP_STATE_DISABWED = 0,
	DPSW_STP_STATE_WISTENING = 1,
	DPSW_STP_STATE_WEAWNING = 2,
	DPSW_STP_STATE_FOWWAWDING = 3,
	DPSW_STP_STATE_BWOCKING = 0
};

/**
 * stwuct dpsw_stp_cfg - Spanning Twee Pwotocow (STP) Configuwation
 * @vwan_id: VWAN ID STP state
 * @state: STP state
 */
stwuct dpsw_stp_cfg {
	u16 vwan_id;
	enum dpsw_stp_state state;
};

int dpsw_if_set_stp(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 if_id,
		    const stwuct dpsw_stp_cfg *cfg);

/**
 * enum dpsw_accepted_fwames - Types of fwames to accept
 * @DPSW_ADMIT_AWW: The device accepts VWAN tagged, untagged and
 *			pwiowity tagged fwames
 * @DPSW_ADMIT_ONWY_VWAN_TAGGED: The device discawds untagged fwames ow
 *			Pwiowity-Tagged fwames weceived on this intewface.
 *
 */
enum dpsw_accepted_fwames {
	DPSW_ADMIT_AWW = 1,
	DPSW_ADMIT_ONWY_VWAN_TAGGED = 3
};

/**
 * enum dpsw_countew  - Countews types
 * @DPSW_CNT_ING_FWAME: Counts ingwess fwames
 * @DPSW_CNT_ING_BYTE: Counts ingwess bytes
 * @DPSW_CNT_ING_FWTW_FWAME: Counts fiwtewed ingwess fwames
 * @DPSW_CNT_ING_FWAME_DISCAWD: Counts discawded ingwess fwame
 * @DPSW_CNT_ING_MCAST_FWAME: Counts ingwess muwticast fwames
 * @DPSW_CNT_ING_MCAST_BYTE: Counts ingwess muwticast bytes
 * @DPSW_CNT_ING_BCAST_FWAME: Counts ingwess bwoadcast fwames
 * @DPSW_CNT_ING_BCAST_BYTES: Counts ingwess bwoadcast bytes
 * @DPSW_CNT_EGW_FWAME: Counts egwess fwames
 * @DPSW_CNT_EGW_BYTE: Counts egwess bytes
 * @DPSW_CNT_EGW_FWAME_DISCAWD: Counts discawded egwess fwames
 * @DPSW_CNT_EGW_STP_FWAME_DISCAWD: Counts egwess STP discawded fwames
 * @DPSW_CNT_ING_NO_BUFF_DISCAWD: Counts ingwess no buffew discawded fwames
 */
enum dpsw_countew {
	DPSW_CNT_ING_FWAME = 0x0,
	DPSW_CNT_ING_BYTE = 0x1,
	DPSW_CNT_ING_FWTW_FWAME = 0x2,
	DPSW_CNT_ING_FWAME_DISCAWD = 0x3,
	DPSW_CNT_ING_MCAST_FWAME = 0x4,
	DPSW_CNT_ING_MCAST_BYTE = 0x5,
	DPSW_CNT_ING_BCAST_FWAME = 0x6,
	DPSW_CNT_ING_BCAST_BYTES = 0x7,
	DPSW_CNT_EGW_FWAME = 0x8,
	DPSW_CNT_EGW_BYTE = 0x9,
	DPSW_CNT_EGW_FWAME_DISCAWD = 0xa,
	DPSW_CNT_EGW_STP_FWAME_DISCAWD = 0xb,
	DPSW_CNT_ING_NO_BUFF_DISCAWD = 0xc,
};

int dpsw_if_get_countew(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u16 if_id, enum dpsw_countew type, u64 *countew);

int dpsw_if_enabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 if_id);

int dpsw_if_disabwe(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 if_id);

/**
 * stwuct dpsw_if_attw - Stwuctuwe wepwesenting DPSW intewface attwibutes
 * @num_tcs: Numbew of twaffic cwasses
 * @wate: Twansmit wate in bits pew second
 * @options: Intewface configuwation options (bitmap)
 * @enabwed: Indicates if intewface is enabwed
 * @accept_aww_vwan: The device discawds/accepts incoming fwames
 *		fow VWANs that do not incwude this intewface
 * @admit_untagged: When set to 'DPSW_ADMIT_ONWY_VWAN_TAGGED', the device
 *		discawds untagged fwames ow pwiowity-tagged fwames weceived on
 *		this intewface;
 *		When set to 'DPSW_ADMIT_AWW', untagged fwames ow pwiowity-
 *		tagged fwames weceived on this intewface awe accepted
 * @qdid: contwow fwames twansmit qdid
 */
stwuct dpsw_if_attw {
	u8 num_tcs;
	u32 wate;
	u32 options;
	int enabwed;
	int accept_aww_vwan;
	enum dpsw_accepted_fwames admit_untagged;
	u16 qdid;
};

int dpsw_if_get_attwibutes(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   u16 if_id, stwuct dpsw_if_attw *attw);

int dpsw_if_set_max_fwame_wength(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
				 u16 if_id, u16 fwame_wength);

/**
 * stwuct dpsw_vwan_cfg - VWAN Configuwation
 * @fdb_id: Fowwawding Data Base
 */
stwuct dpsw_vwan_cfg {
	u16 fdb_id;
};

int dpsw_vwan_add(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		  u16 vwan_id, const stwuct dpsw_vwan_cfg *cfg);

#define DPSW_VWAN_ADD_IF_OPT_FDB_ID            0x0001

/**
 * stwuct dpsw_vwan_if_cfg - Set of VWAN Intewfaces
 * @num_ifs: The numbew of intewfaces that awe assigned to the egwess
 *		wist fow this VWAN
 * @if_id: The set of intewfaces that awe
 *		assigned to the egwess wist fow this VWAN
 * @options: Options map fow this command (DPSW_VWAN_ADD_IF_OPT_FDB_ID)
 * @fdb_id: FDB id to be used by this VWAN on these specific intewfaces
 *		(taken into account onwy if the DPSW_VWAN_ADD_IF_OPT_FDB_ID is
 *		specified in the options fiewd)
 */
stwuct dpsw_vwan_if_cfg {
	u16 num_ifs;
	u16 options;
	u16 if_id[DPSW_MAX_IF];
	u16 fdb_id;
};

int dpsw_vwan_add_if(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		     u16 vwan_id, const stwuct dpsw_vwan_if_cfg *cfg);

int dpsw_vwan_add_if_untagged(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			      u16 vwan_id, const stwuct dpsw_vwan_if_cfg *cfg);

int dpsw_vwan_wemove_if(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			u16 vwan_id, const stwuct dpsw_vwan_if_cfg *cfg);

int dpsw_vwan_wemove_if_untagged(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
				 u16 vwan_id, const stwuct dpsw_vwan_if_cfg *cfg);

int dpsw_vwan_wemove(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		     u16 vwan_id);

/**
 * enum dpsw_fdb_entwy_type - FDB Entwy type - Static/Dynamic
 * @DPSW_FDB_ENTWY_STATIC: Static entwy
 * @DPSW_FDB_ENTWY_DINAMIC: Dynamic entwy
 */
enum dpsw_fdb_entwy_type {
	DPSW_FDB_ENTWY_STATIC = 0,
	DPSW_FDB_ENTWY_DINAMIC = 1
};

/**
 * stwuct dpsw_fdb_unicast_cfg - Unicast entwy configuwation
 * @type: Sewect static ow dynamic entwy
 * @mac_addw: MAC addwess
 * @if_egwess: Egwess intewface ID
 */
stwuct dpsw_fdb_unicast_cfg {
	enum dpsw_fdb_entwy_type type;
	u8 mac_addw[6];
	u16 if_egwess;
};

int dpsw_fdb_add_unicast(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			 u16 fdb_id, const stwuct dpsw_fdb_unicast_cfg *cfg);

int dpsw_fdb_wemove_unicast(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			    u16 fdb_id, const stwuct dpsw_fdb_unicast_cfg *cfg);

#define DPSW_FDB_ENTWY_TYPE_DYNAMIC  BIT(0)
#define DPSW_FDB_ENTWY_TYPE_UNICAST  BIT(1)

/**
 * stwuct fdb_dump_entwy - fdb snapshot entwy
 * @mac_addw: MAC addwess
 * @type: bit0 - DINAMIC(1)/STATIC(0), bit1 - UNICAST(1)/MUWTICAST(0)
 * @if_info: unicast - egwess intewface, muwticast - numbew of egwess intewfaces
 * @if_mask: muwticast - egwess intewface mask
 */
stwuct fdb_dump_entwy {
	u8 mac_addw[6];
	u8 type;
	u8 if_info;
	u8 if_mask[8];
};

int dpsw_fdb_dump(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 fdb_id,
		  u64 iova_addw, u32 iova_size, u16 *num_entwies);

/**
 * stwuct dpsw_fdb_muwticast_cfg - Muwti-cast entwy configuwation
 * @type: Sewect static ow dynamic entwy
 * @mac_addw: MAC addwess
 * @num_ifs: Numbew of extewnaw and intewnaw intewfaces
 * @if_id: Egwess intewface IDs
 */
stwuct dpsw_fdb_muwticast_cfg {
	enum dpsw_fdb_entwy_type type;
	u8 mac_addw[6];
	u16 num_ifs;
	u16 if_id[DPSW_MAX_IF];
};

int dpsw_fdb_add_muwticast(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   u16 fdb_id, const stwuct dpsw_fdb_muwticast_cfg *cfg);

int dpsw_fdb_wemove_muwticast(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			      u16 fdb_id, const stwuct dpsw_fdb_muwticast_cfg *cfg);

/**
 * enum dpsw_weawning_mode - Auto-weawning modes
 * @DPSW_WEAWNING_MODE_DIS: Disabwe Auto-weawning
 * @DPSW_WEAWNING_MODE_HW: Enabwe HW auto-Weawning
 * @DPSW_WEAWNING_MODE_NON_SECUWE: Enabwe None secuwe weawning by CPU
 * @DPSW_WEAWNING_MODE_SECUWE: Enabwe secuwe weawning by CPU
 *
 *	NONE - SECUWE WEAWNING
 *	SMAC found	DMAC found	CTWU Action
 *	v		v	Fowwawd fwame to
 *						1.  DMAC destination
 *	-		v	Fowwawd fwame to
 *						1.  DMAC destination
 *						2.  Contwow intewface
 *	v		-	Fowwawd fwame to
 *						1.  Fwooding wist of intewfaces
 *	-		-	Fowwawd fwame to
 *						1.  Fwooding wist of intewfaces
 *						2.  Contwow intewface
 *	SECUWE WEAWING
 *	SMAC found	DMAC found	CTWU Action
 *	v		v		Fowwawd fwame to
 *						1.  DMAC destination
 *	-		v		Fowwawd fwame to
 *						1.  Contwow intewface
 *	v		-		Fowwawd fwame to
 *						1.  Fwooding wist of intewfaces
 *	-		-		Fowwawd fwame to
 *						1.  Contwow intewface
 */
enum dpsw_weawning_mode {
	DPSW_WEAWNING_MODE_DIS = 0,
	DPSW_WEAWNING_MODE_HW = 1,
	DPSW_WEAWNING_MODE_NON_SECUWE = 2,
	DPSW_WEAWNING_MODE_SECUWE = 3
};

/**
 * stwuct dpsw_fdb_attw - FDB Attwibutes
 * @max_fdb_entwies: Numbew of FDB entwies
 * @fdb_ageing_time: Ageing time in seconds
 * @weawning_mode: Weawning mode
 * @num_fdb_mc_gwoups: Cuwwent numbew of muwticast gwoups
 * @max_fdb_mc_gwoups: Maximum numbew of muwticast gwoups
 */
stwuct dpsw_fdb_attw {
	u16 max_fdb_entwies;
	u16 fdb_ageing_time;
	enum dpsw_weawning_mode weawning_mode;
	u16 num_fdb_mc_gwoups;
	u16 max_fdb_mc_gwoups;
};

int dpsw_get_api_vewsion(stwuct fsw_mc_io *mc_io, u32 cmd_fwags,
			 u16 *majow_vew, u16 *minow_vew);

int dpsw_if_get_powt_mac_addw(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			      u16 if_id, u8 mac_addw[6]);

/**
 * stwuct dpsw_fdb_cfg  - FDB Configuwation
 * @num_fdb_entwies: Numbew of FDB entwies
 * @fdb_ageing_time: Ageing time in seconds
 */
stwuct dpsw_fdb_cfg {
	u16 num_fdb_entwies;
	u16 fdb_ageing_time;
};

int dpsw_fdb_add(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 *fdb_id,
		 const stwuct dpsw_fdb_cfg *cfg);

int dpsw_fdb_wemove(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 fdb_id);

/**
 * enum dpsw_fwood_type - Define the fwood type of a DPSW object
 * @DPSW_BWOADCAST: Bwoadcast fwooding
 * @DPSW_FWOODING: Unknown fwooding
 */
enum dpsw_fwood_type {
	DPSW_BWOADCAST = 0,
	DPSW_FWOODING,
};

stwuct dpsw_egwess_fwood_cfg {
	u16 fdb_id;
	enum dpsw_fwood_type fwood_type;
	u16 num_ifs;
	u16 if_id[DPSW_MAX_IF];
};

int dpsw_set_egwess_fwood(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			  const stwuct dpsw_egwess_fwood_cfg *cfg);

int dpsw_if_set_weawning_mode(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			      u16 if_id, enum dpsw_weawning_mode mode);

/**
 * stwuct dpsw_acw_cfg - ACW Configuwation
 * @max_entwies: Numbew of ACW wuwes
 */
stwuct dpsw_acw_cfg {
	u16 max_entwies;
};

int dpsw_acw_add(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token, u16 *acw_id,
		 const stwuct dpsw_acw_cfg *cfg);

int dpsw_acw_wemove(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		    u16 acw_id);

/**
 * stwuct dpsw_acw_if_cfg - Wist of intewfaces to associate with an ACW tabwe
 * @num_ifs: Numbew of intewfaces
 * @if_id: Wist of intewfaces
 */
stwuct dpsw_acw_if_cfg {
	u16 num_ifs;
	u16 if_id[DPSW_MAX_IF];
};

int dpsw_acw_add_if(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		    u16 acw_id, const stwuct dpsw_acw_if_cfg *cfg);

int dpsw_acw_wemove_if(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		       u16 acw_id, const stwuct dpsw_acw_if_cfg *cfg);

/**
 * stwuct dpsw_acw_fiewds - ACW fiewds.
 * @w2_dest_mac: Destination MAC addwess: BPDU, Muwticast, Bwoadcast, Unicast,
 *			swow pwotocows, MVWP, STP
 * @w2_souwce_mac: Souwce MAC addwess
 * @w2_tpid: Wayew 2 (Ethewnet) pwotocow type, used to identify the fowwowing
 *		pwotocows: MPWS, PTP, PFC, AWP, Jumbo fwames, WWDP, IEEE802.1ae,
 *		Q-in-Q, IPv4, IPv6, PPPoE
 * @w2_pcp_dei: indicate which pwotocow is encapsuwated in the paywoad
 * @w2_vwan_id: wayew 2 VWAN ID
 * @w2_ethew_type: wayew 2 Ethewnet type
 * @w3_dscp: Wayew 3 diffewentiated sewvices code point
 * @w3_pwotocow: Tewws the Netwowk wayew at the destination host, to which
 *		Pwotocow this packet bewongs to. The fowwowing pwotocow awe
 *		suppowted: ICMP, IGMP, IPv4 (encapsuwation), TCP, IPv6
 *		(encapsuwation), GWE, PTP
 * @w3_souwce_ip: Souwce IPv4 IP
 * @w3_dest_ip: Destination IPv4 IP
 * @w4_souwce_powt: Souwce TCP/UDP Powt
 * @w4_dest_powt: Destination TCP/UDP Powt
 */
stwuct dpsw_acw_fiewds {
	u8 w2_dest_mac[6];
	u8 w2_souwce_mac[6];
	u16 w2_tpid;
	u8 w2_pcp_dei;
	u16 w2_vwan_id;
	u16 w2_ethew_type;
	u8 w3_dscp;
	u8 w3_pwotocow;
	u32 w3_souwce_ip;
	u32 w3_dest_ip;
	u16 w4_souwce_powt;
	u16 w4_dest_powt;
};

/**
 * stwuct dpsw_acw_key - ACW key
 * @match: Match fiewds
 * @mask: Mask: b'1 - vawid, b'0 don't cawe
 */
stwuct dpsw_acw_key {
	stwuct dpsw_acw_fiewds match;
	stwuct dpsw_acw_fiewds mask;
};

/**
 * enum dpsw_acw_action - action to be wun on the ACW wuwe match
 * @DPSW_ACW_ACTION_DWOP: Dwop fwame
 * @DPSW_ACW_ACTION_WEDIWECT: Wediwect to cewtain powt
 * @DPSW_ACW_ACTION_ACCEPT: Accept fwame
 * @DPSW_ACW_ACTION_WEDIWECT_TO_CTWW_IF: Wediwect to contwow intewface
 */
enum dpsw_acw_action {
	DPSW_ACW_ACTION_DWOP,
	DPSW_ACW_ACTION_WEDIWECT,
	DPSW_ACW_ACTION_ACCEPT,
	DPSW_ACW_ACTION_WEDIWECT_TO_CTWW_IF
};

/**
 * stwuct dpsw_acw_wesuwt - ACW action
 * @action: Action shouwd be taken when	ACW entwy hit
 * @if_id:  Intewface IDs to wediwect fwame. Vawid onwy if wediwect sewected fow
 *		 action
 */
stwuct dpsw_acw_wesuwt {
	enum dpsw_acw_action action;
	u16 if_id;
};

/**
 * stwuct dpsw_acw_entwy_cfg - ACW entwy
 * @key_iova: I/O viwtuaw addwess of DMA-abwe memowy fiwwed with key aftew caww
 *				to dpsw_acw_pwepawe_entwy_cfg()
 * @wesuwt: Wequiwed action when entwy hit occuws
 * @pwecedence: Pwecedence inside ACW 0 is wowest; This pwiowity can not change
 *		duwing the wifetime of a Powicy. It is usew wesponsibiwity to
 *		space the pwiowities accowding to consequent wuwe additions.
 */
stwuct dpsw_acw_entwy_cfg {
	u64 key_iova;
	stwuct dpsw_acw_wesuwt wesuwt;
	int pwecedence;
};

void dpsw_acw_pwepawe_entwy_cfg(const stwuct dpsw_acw_key *key,
				u8 *entwy_cfg_buf);

int dpsw_acw_add_entwy(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
		       u16 acw_id, const stwuct dpsw_acw_entwy_cfg *cfg);

int dpsw_acw_wemove_entwy(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			  u16 acw_id, const stwuct dpsw_acw_entwy_cfg *cfg);

/**
 * enum dpsw_wefwection_fiwtew - Fiwtew type fow fwames to be wefwected
 * @DPSW_WEFWECTION_FIWTEW_INGWESS_AWW: Wefwect aww fwames
 * @DPSW_WEFWECTION_FIWTEW_INGWESS_VWAN: Wefwect onwy fwames that bewong to
 *	the pawticuwaw VWAN defined by vid pawametew
 *
 */
enum dpsw_wefwection_fiwtew {
	DPSW_WEFWECTION_FIWTEW_INGWESS_AWW = 0,
	DPSW_WEFWECTION_FIWTEW_INGWESS_VWAN = 1
};

/**
 * stwuct dpsw_wefwection_cfg - Stwuctuwe wepwesenting the miwwowing config
 * @fiwtew: Fiwtew type fow fwames to be miwwowed
 * @vwan_id: VWAN ID to miwwow; vawid onwy when the type is DPSW_INGWESS_VWAN
 */
stwuct dpsw_wefwection_cfg {
	enum dpsw_wefwection_fiwtew fiwtew;
	u16 vwan_id;
};

int dpsw_set_wefwection_if(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   u16 if_id);

int dpsw_if_add_wefwection(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			   u16 if_id, const stwuct dpsw_wefwection_cfg *cfg);

int dpsw_if_wemove_wefwection(stwuct fsw_mc_io *mc_io, u32 cmd_fwags, u16 token,
			      u16 if_id, const stwuct dpsw_wefwection_cfg *cfg);
#endif /* __FSW_DPSW_H */
