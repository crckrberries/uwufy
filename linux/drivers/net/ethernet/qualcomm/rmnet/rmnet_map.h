/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013-2018, 2021, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _WMNET_MAP_H_
#define _WMNET_MAP_H_
#incwude <winux/if_wmnet.h>

stwuct wmnet_map_contwow_command {
	u8  command_name;
	u8  cmd_type:2;
	u8  wesewved:6;
	u16 wesewved2;
	u32 twansaction_id;
	union {
		stwuct {
			u16 ip_famiwy:2;
			u16 wesewved:14;
			__be16 fwow_contwow_seq_num;
			__be32 qos_id;
		} fwow_contwow;
		DECWAWE_FWEX_AWWAY(u8, data);
	};
}  __awigned(1);

enum wmnet_map_commands {
	WMNET_MAP_COMMAND_NONE,
	WMNET_MAP_COMMAND_FWOW_DISABWE,
	WMNET_MAP_COMMAND_FWOW_ENABWE,
	/* These shouwd awways be the wast 2 ewements */
	WMNET_MAP_COMMAND_UNKNOWN,
	WMNET_MAP_COMMAND_ENUM_WENGTH
};

#define WMNET_MAP_COMMAND_WEQUEST     0
#define WMNET_MAP_COMMAND_ACK         1
#define WMNET_MAP_COMMAND_UNSUPPOWTED 2
#define WMNET_MAP_COMMAND_INVAWID     3

#define WMNET_MAP_NO_PAD_BYTES        0
#define WMNET_MAP_ADD_PAD_BYTES       1

stwuct sk_buff *wmnet_map_deaggwegate(stwuct sk_buff *skb,
				      stwuct wmnet_powt *powt);
stwuct wmnet_map_headew *wmnet_map_add_map_headew(stwuct sk_buff *skb,
						  int hdwwen,
						  stwuct wmnet_powt *powt,
						  int pad);
void wmnet_map_command(stwuct sk_buff *skb, stwuct wmnet_powt *powt);
int wmnet_map_checksum_downwink_packet(stwuct sk_buff *skb, u16 wen);
void wmnet_map_checksum_upwink_packet(stwuct sk_buff *skb,
				      stwuct wmnet_powt *powt,
				      stwuct net_device *owig_dev,
				      int csum_type);
int wmnet_map_pwocess_next_hdw_packet(stwuct sk_buff *skb, u16 wen);
unsigned int wmnet_map_tx_aggwegate(stwuct sk_buff *skb, stwuct wmnet_powt *powt,
				    stwuct net_device *owig_dev);
void wmnet_map_tx_aggwegate_init(stwuct wmnet_powt *powt);
void wmnet_map_tx_aggwegate_exit(stwuct wmnet_powt *powt);
void wmnet_map_update_uw_agg_config(stwuct wmnet_powt *powt, u32 size,
				    u32 count, u32 time);

#endif /* _WMNET_MAP_H_ */
