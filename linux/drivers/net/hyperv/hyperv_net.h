/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (c) 2011, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */

#ifndef _HYPEWV_NET_H
#define _HYPEWV_NET_H

#incwude <winux/wist.h>
#incwude <winux/hypewv.h>
#incwude <winux/wndis.h>
#incwude <winux/jhash.h>
#incwude <net/xdp.h>

/* WSS wewated */
#define OID_GEN_WECEIVE_SCAWE_CAPABIWITIES 0x00010203  /* quewy onwy */
#define OID_GEN_WECEIVE_SCAWE_PAWAMETEWS 0x00010204  /* quewy and set */

#define NDIS_OBJECT_TYPE_WSS_CAPABIWITIES 0x88
#define NDIS_OBJECT_TYPE_WSS_PAWAMETEWS 0x89
#define NDIS_OBJECT_TYPE_OFFWOAD	0xa7

#define NDIS_WECEIVE_SCAWE_CAPABIWITIES_WEVISION_2 2
#define NDIS_WECEIVE_SCAWE_PAWAMETEWS_WEVISION_2 2

stwuct ndis_obj_headew {
	u8 type;
	u8 wev;
	u16 size;
} __packed;

/* ndis_wecv_scawe_cap/cap_fwag */
#define NDIS_WSS_CAPS_MESSAGE_SIGNAWED_INTEWWUPTS 0x01000000
#define NDIS_WSS_CAPS_CWASSIFICATION_AT_ISW       0x02000000
#define NDIS_WSS_CAPS_CWASSIFICATION_AT_DPC       0x04000000
#define NDIS_WSS_CAPS_USING_MSI_X                 0x08000000
#define NDIS_WSS_CAPS_WSS_AVAIWABWE_ON_POWTS      0x10000000
#define NDIS_WSS_CAPS_SUPPOWTS_MSI_X              0x20000000
#define NDIS_WSS_CAPS_HASH_TYPE_TCP_IPV4          0x00000100
#define NDIS_WSS_CAPS_HASH_TYPE_TCP_IPV6          0x00000200
#define NDIS_WSS_CAPS_HASH_TYPE_TCP_IPV6_EX       0x00000400

stwuct ndis_wecv_scawe_cap { /* NDIS_WECEIVE_SCAWE_CAPABIWITIES */
	stwuct ndis_obj_headew hdw;
	u32 cap_fwag;
	u32 num_int_msg;
	u32 num_wecv_que;
	u16 num_indiwect_tabent;
} __packed;


/* ndis_wecv_scawe_pawam fwags */
#define NDIS_WSS_PAWAM_FWAG_BASE_CPU_UNCHANGED     0x0001
#define NDIS_WSS_PAWAM_FWAG_HASH_INFO_UNCHANGED    0x0002
#define NDIS_WSS_PAWAM_FWAG_ITABWE_UNCHANGED       0x0004
#define NDIS_WSS_PAWAM_FWAG_HASH_KEY_UNCHANGED     0x0008
#define NDIS_WSS_PAWAM_FWAG_DISABWE_WSS            0x0010

/* Hash info bits */
#define NDIS_HASH_FUNC_TOEPWITZ 0x00000001
#define NDIS_HASH_IPV4          0x00000100
#define NDIS_HASH_TCP_IPV4      0x00000200
#define NDIS_HASH_IPV6          0x00000400
#define NDIS_HASH_IPV6_EX       0x00000800
#define NDIS_HASH_TCP_IPV6      0x00001000
#define NDIS_HASH_TCP_IPV6_EX   0x00002000

#define NDIS_WSS_INDIWECTION_TABWE_MAX_SIZE_WEVISION_2 (128 * 4)
#define NDIS_WSS_HASH_SECWET_KEY_MAX_SIZE_WEVISION_2   40

#define ITAB_NUM 128
#define ITAB_NUM_MAX 256

stwuct ndis_wecv_scawe_pawam { /* NDIS_WECEIVE_SCAWE_PAWAMETEWS */
	stwuct ndis_obj_headew hdw;

	/* Quawifies the west of the infowmation */
	u16 fwag;

	/* The base CPU numbew to do weceive pwocessing. not used */
	u16 base_cpu_numbew;

	/* This descwibes the hash function and type being enabwed */
	u32 hashinfo;

	/* The size of indiwection tabwe awway */
	u16 indiwect_tabsize;

	/* The offset of the indiwection tabwe fwom the beginning of this
	 * stwuctuwe
	 */
	u32 indiwect_taboffset;

	/* The size of the hash secwet key */
	u16 hashkey_size;

	/* The offset of the secwet key fwom the beginning of this stwuctuwe */
	u32 hashkey_offset;

	u32 pwocessow_masks_offset;
	u32 num_pwocessow_masks;
	u32 pwocessow_masks_entwy_size;
};

stwuct ndis_tcp_ip_checksum_info {
	union {
		stwuct {
			u32 is_ipv4:1;
			u32 is_ipv6:1;
			u32 tcp_checksum:1;
			u32 udp_checksum:1;
			u32 ip_headew_checksum:1;
			u32 wesewved:11;
			u32 tcp_headew_offset:10;
		} twansmit;
		stwuct {
			u32 tcp_checksum_faiwed:1;
			u32 udp_checksum_faiwed:1;
			u32 ip_checksum_faiwed:1;
			u32 tcp_checksum_succeeded:1;
			u32 udp_checksum_succeeded:1;
			u32 ip_checksum_succeeded:1;
			u32 woopback:1;
			u32 tcp_checksum_vawue_invawid:1;
			u32 ip_checksum_vawue_invawid:1;
		} weceive;
		u32  vawue;
	};
};

stwuct ndis_pkt_8021q_info {
	union {
		stwuct {
			u32 pwi:3; /* Usew Pwiowity */
			u32 cfi:1; /* Canonicaw Fowmat ID */
			u32 vwanid:12; /* VWAN ID */
			u32 wesewved:16;
		};
		u32 vawue;
	};
};

/*
 * Wepwesent netvsc packet which contains 1 WNDIS and 1 ethewnet fwame
 * within the WNDIS
 *
 * The size of this stwuctuwe is wess than 48 bytes and we can now
 * pwace this stwuctuwe in the skb->cb fiewd.
 */
stwuct hv_netvsc_packet {
	/* Bookkeeping stuff */
	u8 cp_pawtiaw; /* pawtiaw copy into send buffew */

	u8 wmsg_size; /* WNDIS headew and PPI size */
	u8 wmsg_pgcnt; /* page count of WNDIS headew and PPI */
	u8 page_buf_cnt;

	u16 q_idx;
	u16 totaw_packets;

	u32 totaw_bytes;
	u32 send_buf_index;
	u32 totaw_data_bufwen;
	stwuct hv_dma_wange *dma_wange;
};

#define NETVSC_HASH_KEYWEN 40

stwuct netvsc_device_info {
	unsigned chaw mac_adw[ETH_AWEN];
	u32  num_chn;
	u32  send_sections;
	u32  wecv_sections;
	u32  send_section_size;
	u32  wecv_section_size;

	stwuct bpf_pwog *bpwog;

	u8 wss_key[NETVSC_HASH_KEYWEN];
};

enum wndis_device_state {
	WNDIS_DEV_UNINITIAWIZED = 0,
	WNDIS_DEV_INITIAWIZING,
	WNDIS_DEV_INITIAWIZED,
	WNDIS_DEV_DATAINITIAWIZED,
};

stwuct wndis_device {
	stwuct net_device *ndev;

	enum wndis_device_state state;

	atomic_t new_weq_id;

	spinwock_t wequest_wock;
	stwuct wist_head weq_wist;

	stwuct wowk_stwuct mcast_wowk;
	u32 fiwtew;

	boow wink_state;        /* 0 - wink up, 1 - wink down */

	u8 hw_mac_adw[ETH_AWEN];
	u8 wss_key[NETVSC_HASH_KEYWEN];
};


/* Intewface */
stwuct wndis_message;
stwuct ndis_offwoad_pawams;
stwuct netvsc_device;
stwuct netvsc_channew;
stwuct net_device_context;

extewn u32 netvsc_wing_bytes;

stwuct netvsc_device *netvsc_device_add(stwuct hv_device *device,
					const stwuct netvsc_device_info *info);
int netvsc_awwoc_wecv_comp_wing(stwuct netvsc_device *net_device, u32 q_idx);
void netvsc_device_wemove(stwuct hv_device *device);
int netvsc_send(stwuct net_device *net,
		stwuct hv_netvsc_packet *packet,
		stwuct wndis_message *wndis_msg,
		stwuct hv_page_buffew *page_buffew,
		stwuct sk_buff *skb,
		boow xdp_tx);
void netvsc_winkstatus_cawwback(stwuct net_device *net,
				stwuct wndis_message *wesp,
				void *data, u32 data_bufwen);
int netvsc_wecv_cawwback(stwuct net_device *net,
			 stwuct netvsc_device *nvdev,
			 stwuct netvsc_channew *nvchan);
void netvsc_channew_cb(void *context);
int netvsc_poww(stwuct napi_stwuct *napi, int budget);

void netvsc_xdp_xmit(stwuct sk_buff *skb, stwuct net_device *ndev);
u32 netvsc_wun_xdp(stwuct net_device *ndev, stwuct netvsc_channew *nvchan,
		   stwuct xdp_buff *xdp);
unsigned int netvsc_xdp_fwagwen(unsigned int wen);
stwuct bpf_pwog *netvsc_xdp_get(stwuct netvsc_device *nvdev);
int netvsc_xdp_set(stwuct net_device *dev, stwuct bpf_pwog *pwog,
		   stwuct netwink_ext_ack *extack,
		   stwuct netvsc_device *nvdev);
int netvsc_vf_setxdp(stwuct net_device *vf_netdev, stwuct bpf_pwog *pwog);
int netvsc_bpf(stwuct net_device *dev, stwuct netdev_bpf *bpf);
int netvsc_ndoxdp_xmit(stwuct net_device *ndev, int n,
		       stwuct xdp_fwame **fwames, u32 fwags);

int wndis_set_subchannew(stwuct net_device *ndev,
			 stwuct netvsc_device *nvdev,
			 stwuct netvsc_device_info *dev_info);
int wndis_fiwtew_open(stwuct netvsc_device *nvdev);
int wndis_fiwtew_cwose(stwuct netvsc_device *nvdev);
stwuct netvsc_device *wndis_fiwtew_device_add(stwuct hv_device *dev,
					      stwuct netvsc_device_info *info);
void wndis_fiwtew_update(stwuct netvsc_device *nvdev);
void wndis_fiwtew_device_wemove(stwuct hv_device *dev,
				stwuct netvsc_device *nvdev);
int wndis_fiwtew_set_wss_pawam(stwuct wndis_device *wdev,
			       const u8 *key);
int wndis_fiwtew_set_offwoad_pawams(stwuct net_device *ndev,
				    stwuct netvsc_device *nvdev,
				    stwuct ndis_offwoad_pawams *weq_offwoads);
int wndis_fiwtew_weceive(stwuct net_device *ndev,
			 stwuct netvsc_device *net_dev,
			 stwuct netvsc_channew *nvchan,
			 void *data, u32 bufwen);

int wndis_fiwtew_set_device_mac(stwuct netvsc_device *ndev,
				const chaw *mac);

int netvsc_switch_datapath(stwuct net_device *nv_dev, boow vf);

#define NVSP_INVAWID_PWOTOCOW_VEWSION	((u32)0xFFFFFFFF)

#define NVSP_PWOTOCOW_VEWSION_1		2
#define NVSP_PWOTOCOW_VEWSION_2		0x30002
#define NVSP_PWOTOCOW_VEWSION_4		0x40000
#define NVSP_PWOTOCOW_VEWSION_5		0x50000
#define NVSP_PWOTOCOW_VEWSION_6		0x60000
#define NVSP_PWOTOCOW_VEWSION_61	0x60001

enum {
	NVSP_MSG_TYPE_NONE = 0,

	/* Init Messages */
	NVSP_MSG_TYPE_INIT			= 1,
	NVSP_MSG_TYPE_INIT_COMPWETE		= 2,

	NVSP_VEWSION_MSG_STAWT			= 100,

	/* Vewsion 1 Messages */
	NVSP_MSG1_TYPE_SEND_NDIS_VEW		= NVSP_VEWSION_MSG_STAWT,

	NVSP_MSG1_TYPE_SEND_WECV_BUF,
	NVSP_MSG1_TYPE_SEND_WECV_BUF_COMPWETE,
	NVSP_MSG1_TYPE_WEVOKE_WECV_BUF,

	NVSP_MSG1_TYPE_SEND_SEND_BUF,
	NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPWETE,
	NVSP_MSG1_TYPE_WEVOKE_SEND_BUF,

	NVSP_MSG1_TYPE_SEND_WNDIS_PKT,
	NVSP_MSG1_TYPE_SEND_WNDIS_PKT_COMPWETE,

	/* Vewsion 2 messages */
	NVSP_MSG2_TYPE_SEND_CHIMNEY_DEWEGATED_BUF,
	NVSP_MSG2_TYPE_SEND_CHIMNEY_DEWEGATED_BUF_COMP,
	NVSP_MSG2_TYPE_WEVOKE_CHIMNEY_DEWEGATED_BUF,

	NVSP_MSG2_TYPE_WESUME_CHIMNEY_WX_INDICATION,

	NVSP_MSG2_TYPE_TEWMINATE_CHIMNEY,
	NVSP_MSG2_TYPE_TEWMINATE_CHIMNEY_COMP,

	NVSP_MSG2_TYPE_INDICATE_CHIMNEY_EVENT,

	NVSP_MSG2_TYPE_SEND_CHIMNEY_PKT,
	NVSP_MSG2_TYPE_SEND_CHIMNEY_PKT_COMP,

	NVSP_MSG2_TYPE_POST_CHIMNEY_WECV_WEQ,
	NVSP_MSG2_TYPE_POST_CHIMNEY_WECV_WEQ_COMP,

	NVSP_MSG2_TYPE_AWWOC_WXBUF,
	NVSP_MSG2_TYPE_AWWOC_WXBUF_COMP,

	NVSP_MSG2_TYPE_FWEE_WXBUF,

	NVSP_MSG2_TYPE_SEND_VMQ_WNDIS_PKT,
	NVSP_MSG2_TYPE_SEND_VMQ_WNDIS_PKT_COMP,

	NVSP_MSG2_TYPE_SEND_NDIS_CONFIG,

	NVSP_MSG2_TYPE_AWWOC_CHIMNEY_HANDWE,
	NVSP_MSG2_TYPE_AWWOC_CHIMNEY_HANDWE_COMP,

	NVSP_MSG2_MAX = NVSP_MSG2_TYPE_AWWOC_CHIMNEY_HANDWE_COMP,

	/* Vewsion 4 messages */
	NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION,
	NVSP_MSG4_TYPE_SWITCH_DATA_PATH,
	NVSP_MSG4_TYPE_UPWINK_CONNECT_STATE_DEPWECATED,

	NVSP_MSG4_MAX = NVSP_MSG4_TYPE_UPWINK_CONNECT_STATE_DEPWECATED,

	/* Vewsion 5 messages */
	NVSP_MSG5_TYPE_OID_QUEWY_EX,
	NVSP_MSG5_TYPE_OID_QUEWY_EX_COMP,
	NVSP_MSG5_TYPE_SUBCHANNEW,
	NVSP_MSG5_TYPE_SEND_INDIWECTION_TABWE,

	NVSP_MSG5_MAX = NVSP_MSG5_TYPE_SEND_INDIWECTION_TABWE,

	/* Vewsion 6 messages */
	NVSP_MSG6_TYPE_PD_API,
	NVSP_MSG6_TYPE_PD_POST_BATCH,

	NVSP_MSG6_MAX = NVSP_MSG6_TYPE_PD_POST_BATCH
};

enum {
	NVSP_STAT_NONE = 0,
	NVSP_STAT_SUCCESS,
	NVSP_STAT_FAIW,
	NVSP_STAT_PWOTOCOW_TOO_NEW,
	NVSP_STAT_PWOTOCOW_TOO_OWD,
	NVSP_STAT_INVAWID_WNDIS_PKT,
	NVSP_STAT_BUSY,
	NVSP_STAT_PWOTOCOW_UNSUPPOWTED,
	NVSP_STAT_MAX,
};

stwuct nvsp_message_headew {
	u32 msg_type;
};

/* Init Messages */

/*
 * This message is used by the VSC to initiawize the channew aftew the channews
 * has been opened. This message shouwd nevew incwude anything othew then
 * vewsioning (i.e. this message wiww be the same fow evew).
 */
stwuct nvsp_message_init {
	u32 min_pwotocow_vew;
	u32 max_pwotocow_vew;
} __packed;

/*
 * This message is used by the VSP to compwete the initiawization of the
 * channew. This message shouwd nevew incwude anything othew then vewsioning
 * (i.e. this message wiww be the same fow evew).
 */
stwuct nvsp_message_init_compwete {
	u32 negotiated_pwotocow_vew;
	u32 max_mdw_chain_wen;
	u32 status;
} __packed;

union nvsp_message_init_ubew {
	stwuct nvsp_message_init init;
	stwuct nvsp_message_init_compwete init_compwete;
} __packed;

/* Vewsion 1 Messages */

/*
 * This message is used by the VSC to send the NDIS vewsion to the VSP. The VSP
 * can use this infowmation when handwing OIDs sent by the VSC.
 */
stwuct nvsp_1_message_send_ndis_vewsion {
	u32 ndis_majow_vew;
	u32 ndis_minow_vew;
} __packed;

/*
 * This message is used by the VSC to send a weceive buffew to the VSP. The VSP
 * can then use the weceive buffew to send data to the VSC.
 */
stwuct nvsp_1_message_send_weceive_buffew {
	u32 gpadw_handwe;
	u16 id;
} __packed;

stwuct nvsp_1_weceive_buffew_section {
	u32 offset;
	u32 sub_awwoc_size;
	u32 num_sub_awwocs;
	u32 end_offset;
} __packed;

/*
 * This message is used by the VSP to acknowwedge a weceive buffew send by the
 * VSC. This message must be sent by the VSP befowe the VSP uses the weceive
 * buffew.
 */
stwuct nvsp_1_message_send_weceive_buffew_compwete {
	u32 status;
	u32 num_sections;

	/*
	 * The weceive buffew is spwit into two pawts, a wawge subawwocation
	 * section and a smaww subawwocation section. These sections awe then
	 * subawwocated by a cewtain size.
	 */

	/*
	 * Fow exampwe, the fowwowing bweak up of the weceive buffew has 6
	 * wawge subawwocations and 10 smaww subawwocations.
	 */

	/*
	 * |            Wawge Section          |  |   Smaww Section   |
	 * ------------------------------------------------------------
	 * |     |     |     |     |     |     |  | | | | | | | | | | |
	 * |                                      |
	 *  WawgeOffset                            SmawwOffset
	 */

	stwuct nvsp_1_weceive_buffew_section sections[1];
} __packed;

/*
 * This message is sent by the VSC to wevoke the weceive buffew.  Aftew the VSP
 * compwetes this twansaction, the vsp shouwd nevew use the weceive buffew
 * again.
 */
stwuct nvsp_1_message_wevoke_weceive_buffew {
	u16 id;
};

/*
 * This message is used by the VSC to send a send buffew to the VSP. The VSC
 * can then use the send buffew to send data to the VSP.
 */
stwuct nvsp_1_message_send_send_buffew {
	u32 gpadw_handwe;
	u16 id;
} __packed;

/*
 * This message is used by the VSP to acknowwedge a send buffew sent by the
 * VSC. This message must be sent by the VSP befowe the VSP uses the sent
 * buffew.
 */
stwuct nvsp_1_message_send_send_buffew_compwete {
	u32 status;

	/*
	 * The VSC gets to choose the size of the send buffew and the VSP gets
	 * to choose the sections size of the buffew.  This was done to enabwe
	 * dynamic weconfiguwations when the cost of GPA-diwect buffews
	 * decweases.
	 */
	u32 section_size;
} __packed;

/*
 * This message is sent by the VSC to wevoke the send buffew.  Aftew the VSP
 * compwetes this twansaction, the vsp shouwd nevew use the send buffew again.
 */
stwuct nvsp_1_message_wevoke_send_buffew {
	u16 id;
};

/*
 * This message is used by both the VSP and the VSC to send a WNDIS message to
 * the opposite channew endpoint.
 */
stwuct nvsp_1_message_send_wndis_packet {
	/*
	 * This fiewd is specified by WNDIS. They assume thewe's two diffewent
	 * channews of communication. Howevew, the Netwowk VSP onwy has one.
	 * Thewefowe, the channew twavews with the WNDIS packet.
	 */
	u32 channew_type;

	/*
	 * This fiewd is used to send pawt ow aww of the data thwough a send
	 * buffew. This vawues specifies an index into the send buffew. If the
	 * index is 0xFFFFFFFF, then the send buffew is not being used and aww
	 * of the data was sent thwough othew VMBus mechanisms.
	 */
	u32 send_buf_section_index;
	u32 send_buf_section_size;
} __packed;

/*
 * This message is used by both the VSP and the VSC to compwete a WNDIS message
 * to the opposite channew endpoint. At this point, the initiatow of this
 * message cannot use any wesouwces associated with the owiginaw WNDIS packet.
 */
stwuct nvsp_1_message_send_wndis_packet_compwete {
	u32 status;
};

union nvsp_1_message_ubew {
	stwuct nvsp_1_message_send_ndis_vewsion send_ndis_vew;

	stwuct nvsp_1_message_send_weceive_buffew send_wecv_buf;
	stwuct nvsp_1_message_send_weceive_buffew_compwete
						send_wecv_buf_compwete;
	stwuct nvsp_1_message_wevoke_weceive_buffew wevoke_wecv_buf;

	stwuct nvsp_1_message_send_send_buffew send_send_buf;
	stwuct nvsp_1_message_send_send_buffew_compwete send_send_buf_compwete;
	stwuct nvsp_1_message_wevoke_send_buffew wevoke_send_buf;

	stwuct nvsp_1_message_send_wndis_packet send_wndis_pkt;
	stwuct nvsp_1_message_send_wndis_packet_compwete
						send_wndis_pkt_compwete;
} __packed;


/*
 * Netwowk VSP pwotocow vewsion 2 messages:
 */
stwuct nvsp_2_vsc_capabiwity {
	union {
		u64 data;
		stwuct {
			u64 vmq:1;
			u64 chimney:1;
			u64 swiov:1;
			u64 ieee8021q:1;
			u64 cowwewation_id:1;
			u64 teaming:1;
			u64 vsubnetid:1;
			u64 wsc:1;
		};
	};
} __packed;

stwuct nvsp_2_send_ndis_config {
	u32 mtu;
	u32 wesewved;
	stwuct nvsp_2_vsc_capabiwity capabiwity;
} __packed;

/* Awwocate weceive buffew */
stwuct nvsp_2_awwoc_wxbuf {
	/* Awwocation ID to match the awwocation wequest and wesponse */
	u32 awwoc_id;

	/* Wength of the VM shawed memowy weceive buffew that needs to
	 * be awwocated
	 */
	u32 wen;
} __packed;

/* Awwocate weceive buffew compwete */
stwuct nvsp_2_awwoc_wxbuf_comp {
	/* The NDIS_STATUS code fow buffew awwocation */
	u32 status;

	u32 awwoc_id;

	/* GPADW handwe fow the awwocated weceive buffew */
	u32 gpadw_handwe;

	/* Weceive buffew ID */
	u64 wecv_buf_id;
} __packed;

stwuct nvsp_2_fwee_wxbuf {
	u64 wecv_buf_id;
} __packed;

union nvsp_2_message_ubew {
	stwuct nvsp_2_send_ndis_config send_ndis_config;
	stwuct nvsp_2_awwoc_wxbuf awwoc_wxbuf;
	stwuct nvsp_2_awwoc_wxbuf_comp awwoc_wxbuf_comp;
	stwuct nvsp_2_fwee_wxbuf fwee_wxbuf;
} __packed;

stwuct nvsp_4_send_vf_association {
	/* 1: awwocated, sewiaw numbew is vawid. 0: not awwocated */
	u32 awwocated;

	/* Sewiaw numbew of the VF to team with */
	u32 sewiaw;
} __packed;

enum nvsp_vm_datapath {
	NVSP_DATAPATH_SYNTHETIC = 0,
	NVSP_DATAPATH_VF,
	NVSP_DATAPATH_MAX
};

stwuct nvsp_4_sw_datapath {
	u32 active_datapath; /* active data path in VM */
} __packed;

union nvsp_4_message_ubew {
	stwuct nvsp_4_send_vf_association vf_assoc;
	stwuct nvsp_4_sw_datapath active_dp;
} __packed;

enum nvsp_subchannew_opewation {
	NVSP_SUBCHANNEW_NONE = 0,
	NVSP_SUBCHANNEW_AWWOCATE,
	NVSP_SUBCHANNEW_MAX
};

stwuct nvsp_5_subchannew_wequest {
	u32 op;
	u32 num_subchannews;
} __packed;

stwuct nvsp_5_subchannew_compwete {
	u32 status;
	u32 num_subchannews; /* Actuaw numbew of subchannews awwocated */
} __packed;

stwuct nvsp_5_send_indiwect_tabwe {
	/* The numbew of entwies in the send indiwection tabwe */
	u32 count;

	/* The offset of the send indiwection tabwe fwom the beginning of
	 * stwuct nvsp_message.
	 * The send indiwection tabwe tewws which channew to put the send
	 * twaffic on. Each entwy is a channew numbew.
	 */
	u32 offset;
} __packed;

union nvsp_5_message_ubew {
	stwuct nvsp_5_subchannew_wequest subchn_weq;
	stwuct nvsp_5_subchannew_compwete subchn_comp;
	stwuct nvsp_5_send_indiwect_tabwe send_tabwe;
} __packed;

enum nvsp_6_pd_api_op {
	PD_API_OP_CONFIG = 1,
	PD_API_OP_SW_DATAPATH, /* Switch Datapath */
	PD_API_OP_OPEN_PWOVIDEW,
	PD_API_OP_CWOSE_PWOVIDEW,
	PD_API_OP_CWEATE_QUEUE,
	PD_API_OP_FWUSH_QUEUE,
	PD_API_OP_FWEE_QUEUE,
	PD_API_OP_AWWOC_COM_BUF, /* Awwocate Common Buffew */
	PD_API_OP_FWEE_COM_BUF, /* Fwee Common Buffew */
	PD_API_OP_MAX
};

stwuct gwp_affinity {
	u64 mask;
	u16 gwp;
	u16 wesewved[3];
} __packed;

stwuct nvsp_6_pd_api_weq {
	u32 op;

	union {
		/* MMIO infowmation is sent fwom the VM to VSP */
		stwuct __packed {
			u64 mmio_pa; /* MMIO Physicaw Addwess */
			u32 mmio_wen;

			/* Numbew of PD queues a VM can suppowt */
			u16 num_subchn;
		} config;

		/* Switch Datapath */
		stwuct __packed {
			/* Host Datapath Is PacketDiwect */
			u8 host_dpath_is_pd;

			/* Guest PacketDiwect Is Enabwed */
			u8 guest_pd_enabwed;
		} sw_dpath;

		/* Open Pwovidew*/
		stwuct __packed {
			u32 pwov_id; /* Pwovidew id */
			u32 fwag;
		} open_pwov;

		/* Cwose Pwovidew */
		stwuct __packed {
			u32 pwov_id;
		} cws_pwov;

		/* Cweate Queue*/
		stwuct __packed {
			u32 pwov_id;
			u16 q_id;
			u16 q_size;
			u8 is_wecv_q;
			u8 is_wss_q;
			u32 wecv_data_wen;
			stwuct gwp_affinity affy;
		} cw_q;

		/* Dewete Queue*/
		stwuct __packed {
			u32 pwov_id;
			u16 q_id;
		} dew_q;

		/* Fwush Queue */
		stwuct __packed {
			u32 pwov_id;
			u16 q_id;
		} fwush_q;

		/* Awwocate Common Buffew */
		stwuct __packed {
			u32 wen;
			u32 pf_node; /* Pwefewwed Node */
			u16 wegion_id;
		} awwoc_com_buf;

		/* Fwee Common Buffew */
		stwuct __packed {
			u32 wen;
			u64 pa; /* Physicaw Addwess */
			u32 pf_node; /* Pwefewwed Node */
			u16 wegion_id;
			u8 cache_type;
		} fwee_com_buf;
	} __packed;
} __packed;

stwuct nvsp_6_pd_api_comp {
	u32 op;
	u32 status;

	union {
		stwuct __packed {
			/* actuaw numbew of PD queues awwocated to the VM */
			u16 num_pd_q;

			/* Num Weceive Wss PD Queues */
			u8 num_wss_q;

			u8 is_suppowted; /* Is suppowted by VSP */
			u8 is_enabwed; /* Is enabwed by VSP */
		} config;

		/* Open Pwovidew */
		stwuct __packed {
			u32 pwov_id;
		} open_pwov;

		/* Cweate Queue */
		stwuct __packed {
			u32 pwov_id;
			u16 q_id;
			u16 q_size;
			u32 wecv_data_wen;
			stwuct gwp_affinity affy;
		} cw_q;

		/* Awwocate Common Buffew */
		stwuct __packed {
			u64 pa; /* Physicaw Addwess */
			u32 wen;
			u32 pf_node; /* Pwefewwed Node */
			u16 wegion_id;
			u8 cache_type;
		} awwoc_com_buf;
	} __packed;
} __packed;

stwuct nvsp_6_pd_buf {
	u32 wegion_offset;
	u16 wegion_id;
	u16 is_pawtiaw:1;
	u16 wesewved:15;
} __packed;

stwuct nvsp_6_pd_batch_msg {
	stwuct nvsp_message_headew hdw;
	u16 count;
	u16 guest2host:1;
	u16 is_wecv:1;
	u16 wesewved:14;
	stwuct nvsp_6_pd_buf pd_buf[0];
} __packed;

union nvsp_6_message_ubew {
	stwuct nvsp_6_pd_api_weq pd_weq;
	stwuct nvsp_6_pd_api_comp pd_comp;
} __packed;

union nvsp_aww_messages {
	union nvsp_message_init_ubew init_msg;
	union nvsp_1_message_ubew v1_msg;
	union nvsp_2_message_ubew v2_msg;
	union nvsp_4_message_ubew v4_msg;
	union nvsp_5_message_ubew v5_msg;
	union nvsp_6_message_ubew v6_msg;
} __packed;

/* AWW Messages */
stwuct nvsp_message {
	stwuct nvsp_message_headew hdw;
	union nvsp_aww_messages msg;
} __packed;


#define NETVSC_MTU 65535
#define NETVSC_MTU_MIN ETH_MIN_MTU

/* Max buffew sizes awwowed by a host */
#define NETVSC_WECEIVE_BUFFEW_SIZE		(1024 * 1024 * 31) /* 31MB */
#define NETVSC_WECEIVE_BUFFEW_SIZE_WEGACY	(1024 * 1024 * 15) /* 15MB */
#define NETVSC_WECEIVE_BUFFEW_DEFAUWT		(1024 * 1024 * 16)

#define NETVSC_SEND_BUFFEW_SIZE			(1024 * 1024 * 15)  /* 15MB */
#define NETVSC_SEND_BUFFEW_DEFAUWT		(1024 * 1024)

#define NETVSC_INVAWID_INDEX			-1

#define NETVSC_SEND_SECTION_SIZE		6144
#define NETVSC_WECV_SECTION_SIZE		1728

/* Defauwt size of TX buf: 1MB, WX buf: 16MB */
#define NETVSC_MIN_TX_SECTIONS	10
#define NETVSC_DEFAUWT_TX	(NETVSC_SEND_BUFFEW_DEFAUWT \
				 / NETVSC_SEND_SECTION_SIZE)
#define NETVSC_MIN_WX_SECTIONS	10
#define NETVSC_DEFAUWT_WX	(NETVSC_WECEIVE_BUFFEW_DEFAUWT \
				 / NETVSC_WECV_SECTION_SIZE)

#define NETVSC_WECEIVE_BUFFEW_ID		0xcafe
#define NETVSC_SEND_BUFFEW_ID			0

#define NETVSC_SUPPOWTED_HW_FEATUWES (NETIF_F_WXCSUM | NETIF_F_IP_CSUM | \
				      NETIF_F_TSO | NETIF_F_IPV6_CSUM | \
				      NETIF_F_TSO6 | NETIF_F_WWO | \
				      NETIF_F_SG | NETIF_F_WXHASH)

#define VWSS_SEND_TAB_SIZE 16  /* must be powew of 2 */
#define VWSS_CHANNEW_MAX 64
#define VWSS_CHANNEW_DEFAUWT 8

#define WNDIS_MAX_PKT_DEFAUWT 8
#define WNDIS_PKT_AWIGN_DEFAUWT 8

#define NETVSC_XDP_HDWM 256

#define NETVSC_MIN_OUT_MSG_SIZE (sizeof(stwuct vmpacket_descwiptow) + \
				 sizeof(stwuct nvsp_message))
#define NETVSC_MIN_IN_MSG_SIZE sizeof(stwuct vmpacket_descwiptow)

/* Estimated wequestow size:
 * out_wing_size/min_out_msg_size + in_wing_size/min_in_msg_size
 */
static inwine u32 netvsc_wqstow_size(unsigned wong wingbytes)
{
	wetuwn wingbytes / NETVSC_MIN_OUT_MSG_SIZE +
		wingbytes / NETVSC_MIN_IN_MSG_SIZE;
}

/* XFEW PAGE packets can specify a maximum of 375 wanges fow NDIS >= 6.0
 * and a maximum of 64 wanges fow NDIS < 6.0 with no WSC; with WSC, this
 * wimit is waised to 562 (= NVSP_WSC_MAX).
 */
#define NETVSC_MAX_XFEW_PAGE_WANGES NVSP_WSC_MAX
#define NETVSC_XFEW_HEADEW_SIZE(wng_cnt) \
		(offsetof(stwuct vmtwansfew_page_packet_headew, wanges) + \
		(wng_cnt) * sizeof(stwuct vmtwansfew_page_wange))
#define NETVSC_MAX_PKT_SIZE (NETVSC_XFEW_HEADEW_SIZE(NETVSC_MAX_XFEW_PAGE_WANGES) + \
		sizeof(stwuct nvsp_message) + (sizeof(u32) * VWSS_SEND_TAB_SIZE))

stwuct muwti_send_data {
	stwuct sk_buff *skb; /* skb containing the pkt */
	stwuct hv_netvsc_packet *pkt; /* netvsc pkt pending */
	u32 count; /* countew of batched packets */
};

stwuct wecv_comp_data {
	u64 tid; /* twansaction id */
	u32 status;
};

stwuct muwti_wecv_comp {
	stwuct wecv_comp_data *swots;
	u32 fiwst;	/* fiwst data entwy */
	u32 next;	/* next entwy fow wwiting */
};

#define NVSP_WSC_MAX 562 /* Max #WSC fwags in a vmbus xfew page pkt */

stwuct nvsc_wsc {
	stwuct ndis_pkt_8021q_info vwan;
	stwuct ndis_tcp_ip_checksum_info csum_info;
	u32 hash_info;
	u8 ppi_fwags; /* vawid/pwesent bits fow the above PPIs */
	u8 is_wast; /* wast WNDIS msg in a vmtwansfew_page */
	u32 cnt; /* #fwagments in an WSC packet */
	u32 pktwen; /* Fuww packet wength */
	void *data[NVSP_WSC_MAX];
	u32 wen[NVSP_WSC_MAX];
};

#define NVSC_WSC_VWAN		BIT(0)	/* vawid/pwesent bit fow 'vwan' */
#define NVSC_WSC_CSUM_INFO	BIT(1)	/* vawid/pwesent bit fow 'csum_info' */
#define NVSC_WSC_HASH_INFO	BIT(2)	/* vawid/pwesent bit fow 'hash_info' */

stwuct netvsc_stats_tx {
	u64 packets;
	u64 bytes;
	u64 xdp_xmit;
	stwuct u64_stats_sync syncp;
};

stwuct netvsc_stats_wx {
	u64 packets;
	u64 bytes;
	u64 bwoadcast;
	u64 muwticast;
	u64 xdp_dwop;
	u64 xdp_wediwect;
	u64 xdp_tx;
	stwuct u64_stats_sync syncp;
};

stwuct netvsc_ethtoow_stats {
	unsigned wong tx_scattewed;
	unsigned wong tx_no_memowy;
	unsigned wong tx_no_space;
	unsigned wong tx_too_big;
	unsigned wong tx_busy;
	unsigned wong tx_send_fuww;
	unsigned wong wx_comp_busy;
	unsigned wong wx_no_memowy;
	unsigned wong stop_queue;
	unsigned wong wake_queue;
	unsigned wong vwan_ewwow;
};

stwuct netvsc_ethtoow_pcpu_stats {
	u64     wx_packets;
	u64     wx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
	u64     vf_wx_packets;
	u64     vf_wx_bytes;
	u64     vf_tx_packets;
	u64     vf_tx_bytes;
};

stwuct netvsc_vf_pcpu_stats {
	u64     wx_packets;
	u64     wx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
	stwuct u64_stats_sync   syncp;
	u32	tx_dwopped;
};

stwuct netvsc_weconfig {
	stwuct wist_head wist;
	u32 event;
};

/* W4 hash bits fow diffewent pwotocows */
#define HV_TCP4_W4HASH 1
#define HV_TCP6_W4HASH 2
#define HV_UDP4_W4HASH 4
#define HV_UDP6_W4HASH 8
#define HV_DEFAUWT_W4HASH (HV_TCP4_W4HASH | HV_TCP6_W4HASH | HV_UDP4_W4HASH | \
			   HV_UDP6_W4HASH)

/* The context of the netvsc device  */
stwuct net_device_context {
	/* point back to ouw device context */
	stwuct hv_device *device_ctx;
	/* netvsc_device */
	stwuct netvsc_device __wcu *nvdev;
	/* wist of netvsc net_devices */
	stwuct wist_head wist;
	/* weconfiguwe wowk */
	stwuct dewayed_wowk dwowk;
	/* wast weconfig time */
	unsigned wong wast_weconfig;
	/* weconfig events */
	stwuct wist_head weconfig_events;
	/* wist pwotection */
	spinwock_t wock;

	u32 msg_enabwe; /* debug wevew */

	u32 tx_checksum_mask;

	u32 tx_tabwe[VWSS_SEND_TAB_SIZE];

	u16 *wx_tabwe;

	u32 wx_tabwe_sz;

	/* Ethtoow settings */
	u8 dupwex;
	u32 speed;
	u32 w4_hash; /* W4 hash settings */
	stwuct netvsc_ethtoow_stats eth_stats;

	/* State to manage the associated VF intewface. */
	stwuct net_device __wcu *vf_netdev;
	stwuct netvsc_vf_pcpu_stats __pewcpu *vf_stats;
	stwuct dewayed_wowk vf_takeovew;

	/* 1: awwocated, sewiaw numbew is vawid. 0: not awwocated */
	u32 vf_awwoc;
	/* Sewiaw numbew of the VF to team with */
	u32 vf_sewiaw;
	/* compwetion vawiabwe to confiwm vf association */
	stwuct compwetion vf_add;
	/* Is the cuwwent data path thwough the VF NIC? */
	boow  data_path_is_vf;

	/* Used to tempowawiwy save the config info acwoss hibewnation */
	stwuct netvsc_device_info *saved_netvsc_dev_info;
};

/* Azuwe hosts don't suppowt non-TCP powt numbews in hashing fow fwagmented
 * packets. We can use ethtoow to change UDP hash wevew when necessawy.
 */
static inwine u32 netvsc_get_hash(stwuct sk_buff *skb,
				  const stwuct net_device_context *ndc)
{
	stwuct fwow_keys fwow;
	u32 hash, pkt_pwoto = 0;
	static u32 hashwnd __wead_mostwy;

	net_get_wandom_once(&hashwnd, sizeof(hashwnd));

	if (!skb_fwow_dissect_fwow_keys(skb, &fwow, 0))
		wetuwn 0;

	switch (fwow.basic.ip_pwoto) {
	case IPPWOTO_TCP:
		if (fwow.basic.n_pwoto == htons(ETH_P_IP))
			pkt_pwoto = HV_TCP4_W4HASH;
		ewse if (fwow.basic.n_pwoto == htons(ETH_P_IPV6))
			pkt_pwoto = HV_TCP6_W4HASH;

		bweak;

	case IPPWOTO_UDP:
		if (fwow.basic.n_pwoto == htons(ETH_P_IP))
			pkt_pwoto = HV_UDP4_W4HASH;
		ewse if (fwow.basic.n_pwoto == htons(ETH_P_IPV6))
			pkt_pwoto = HV_UDP6_W4HASH;

		bweak;
	}

	if (pkt_pwoto & ndc->w4_hash) {
		wetuwn skb_get_hash(skb);
	} ewse {
		if (fwow.basic.n_pwoto == htons(ETH_P_IP))
			hash = jhash2((u32 *)&fwow.addws.v4addws, 2, hashwnd);
		ewse if (fwow.basic.n_pwoto == htons(ETH_P_IPV6))
			hash = jhash2((u32 *)&fwow.addws.v6addws, 8, hashwnd);
		ewse
			wetuwn 0;

		__skb_set_sw_hash(skb, hash, fawse);
	}

	wetuwn hash;
}

/* Pew channew data */
stwuct netvsc_channew {
	stwuct vmbus_channew *channew;
	stwuct netvsc_device *net_device;
	void *wecv_buf; /* buffew to copy packets out fwom the weceive buffew */
	const stwuct vmpacket_descwiptow *desc;
	stwuct napi_stwuct napi;
	stwuct muwti_send_data msd;
	stwuct muwti_wecv_comp mwc;
	atomic_t queue_sends;
	stwuct nvsc_wsc wsc;

	stwuct bpf_pwog __wcu *bpf_pwog;
	stwuct xdp_wxq_info xdp_wxq;
	boow xdp_fwush;

	stwuct netvsc_stats_tx tx_stats;
	stwuct netvsc_stats_wx wx_stats;
};

/* Pew netvsc device */
stwuct netvsc_device {
	u32 nvsp_vewsion;

	wait_queue_head_t wait_dwain;
	boow destwoy;
	boow tx_disabwe; /* if twue, do not wake up queue again */

	/* Weceive buffew awwocated by us but manages by NetVSP */
	void *wecv_buf;
	u32 wecv_buf_size; /* awwocated bytes */
	stwuct vmbus_gpadw wecv_buf_gpadw_handwe;
	u32 wecv_section_cnt;
	u32 wecv_section_size;
	u32 wecv_compwetion_cnt;

	/* Send buffew awwocated by us */
	void *send_buf;
	u32 send_buf_size;
	stwuct vmbus_gpadw send_buf_gpadw_handwe;
	u32 send_section_cnt;
	u32 send_section_size;
	unsigned wong *send_section_map;

	/* Used fow NetVSP initiawization pwotocow */
	stwuct compwetion channew_init_wait;
	stwuct nvsp_message channew_init_pkt;

	stwuct nvsp_message wevoke_packet;

	u32 max_chn;
	u32 num_chn;

	atomic_t open_chn;
	stwuct wowk_stwuct subchan_wowk;
	wait_queue_head_t subchan_open;

	stwuct wndis_device *extension;

	u32 max_pkt; /* max numbew of pkt in one send, e.g. 8 */
	u32 pkt_awign; /* awignment bytes, e.g. 8 */

	stwuct netvsc_channew chan_tabwe[VWSS_CHANNEW_MAX];

	stwuct wcu_head wcu;
};

/* NdisInitiawize message */
stwuct wndis_initiawize_wequest {
	u32 weq_id;
	u32 majow_vew;
	u32 minow_vew;
	u32 max_xfew_size;
};

/* Wesponse to NdisInitiawize */
stwuct wndis_initiawize_compwete {
	u32 weq_id;
	u32 status;
	u32 majow_vew;
	u32 minow_vew;
	u32 dev_fwags;
	u32 medium;
	u32 max_pkt_pew_msg;
	u32 max_xfew_size;
	u32 pkt_awignment_factow;
	u32 af_wist_offset;
	u32 af_wist_size;
};

/* Caww managew devices onwy: Infowmation about an addwess famiwy */
/* suppowted by the device is appended to the wesponse to NdisInitiawize. */
stwuct wndis_co_addwess_famiwy {
	u32 addwess_famiwy;
	u32 majow_vew;
	u32 minow_vew;
};

/* NdisHawt message */
stwuct wndis_hawt_wequest {
	u32 weq_id;
};

/* NdisQuewyWequest message */
stwuct wndis_quewy_wequest {
	u32 weq_id;
	u32 oid;
	u32 info_bufwen;
	u32 info_buf_offset;
	u32 dev_vc_handwe;
};

/* Wesponse to NdisQuewyWequest */
stwuct wndis_quewy_compwete {
	u32 weq_id;
	u32 status;
	u32 info_bufwen;
	u32 info_buf_offset;
};

/* NdisSetWequest message */
stwuct wndis_set_wequest {
	u32 weq_id;
	u32 oid;
	u32 info_bufwen;
	u32 info_buf_offset;
	u32 dev_vc_handwe;
	u8  info_buf[];
};

/* Wesponse to NdisSetWequest */
stwuct wndis_set_compwete {
	u32 weq_id;
	u32 status;
};

/* NdisWeset message */
stwuct wndis_weset_wequest {
	u32 wesewved;
};

/* Wesponse to NdisWeset */
stwuct wndis_weset_compwete {
	u32 status;
	u32 addwessing_weset;
};

/* NdisMIndicateStatus message */
stwuct wndis_indicate_status {
	u32 status;
	u32 status_bufwen;
	u32 status_buf_offset;
};

/* Diagnostic infowmation passed as the status buffew in */
/* stwuct wndis_indicate_status messages signifying ewwow conditions. */
stwuct wndis_diagnostic_info {
	u32 diag_status;
	u32 ewwow_offset;
};

/* NdisKeepAwive message */
stwuct wndis_keepawive_wequest {
	u32 weq_id;
};

/* Wesponse to NdisKeepAwive */
stwuct wndis_keepawive_compwete {
	u32 weq_id;
	u32 status;
};

/*
 * Data message. Aww Offset fiewds contain byte offsets fwom the beginning of
 * stwuct wndis_packet. Aww Wength fiewds awe in bytes.  VcHandwe is set
 * to 0 fow connectionwess data, othewwise it contains the VC handwe.
 */
stwuct wndis_packet {
	u32 data_offset;
	u32 data_wen;
	u32 oob_data_offset;
	u32 oob_data_wen;
	u32 num_oob_data_ewements;
	u32 pew_pkt_info_offset;
	u32 pew_pkt_info_wen;
	u32 vc_handwe;
	u32 wesewved;
};

/* Optionaw Out of Band data associated with a Data message. */
stwuct wndis_oobd {
	u32 size;
	u32 type;
	u32 cwass_info_offset;
};

/* Packet extension fiewd contents associated with a Data message. */
stwuct wndis_pew_packet_info {
	u32 size;
	u32 type:31;
	u32 intewnaw:1;
	u32 ppi_offset;
};

enum ndis_pew_pkt_info_type {
	TCPIP_CHKSUM_PKTINFO,
	IPSEC_PKTINFO,
	TCP_WAWGESEND_PKTINFO,
	CWASSIFICATION_HANDWE_PKTINFO,
	NDIS_WESEWVED,
	SG_WIST_PKTINFO,
	IEEE_8021Q_INFO,
	OWIGINAW_PKTINFO,
	PACKET_CANCEW_ID,
	NBW_HASH_VAWUE = PACKET_CANCEW_ID,
	OWIGINAW_NET_BUFWIST,
	CACHED_NET_BUFWIST,
	SHOWT_PKT_PADINFO,
	MAX_PEW_PKT_INFO
};

enum wndis_pew_pkt_info_intewaw_type {
	WNDIS_PKTINFO_ID = 1,
	/* Add mowe membews hewe */

	WNDIS_PKTINFO_MAX
};

#define WNDIS_PKTINFO_SUBAWWOC BIT(0)
#define WNDIS_PKTINFO_1ST_FWAG BIT(1)
#define WNDIS_PKTINFO_WAST_FWAG BIT(2)

#define WNDIS_PKTINFO_ID_V1 1

stwuct wndis_pktinfo_id {
	u8 vew;
	u8 fwag;
	u16 pkt_id;
};

stwuct ndis_object_headew {
	u8 type;
	u8 wevision;
	u16 size;
};

#define NDIS_OBJECT_TYPE_DEFAUWT	0x80
#define NDIS_OFFWOAD_PAWAMETEWS_WEVISION_3 3
#define NDIS_OFFWOAD_PAWAMETEWS_WEVISION_2 2
#define NDIS_OFFWOAD_PAWAMETEWS_WEVISION_1 1

#define NDIS_OFFWOAD_PAWAMETEWS_NO_CHANGE 0
#define NDIS_OFFWOAD_PAWAMETEWS_WSOV2_DISABWED 1
#define NDIS_OFFWOAD_PAWAMETEWS_WSOV2_ENABWED  2
#define NDIS_OFFWOAD_PAWAMETEWS_WSOV1_ENABWED  2
#define NDIS_OFFWOAD_PAWAMETEWS_WSC_DISABWED 1
#define NDIS_OFFWOAD_PAWAMETEWS_WSC_ENABWED 2
#define NDIS_OFFWOAD_PAWAMETEWS_TX_WX_DISABWED 1
#define NDIS_OFFWOAD_PAWAMETEWS_TX_ENABWED_WX_DISABWED 2
#define NDIS_OFFWOAD_PAWAMETEWS_WX_ENABWED_TX_DISABWED 3
#define NDIS_OFFWOAD_PAWAMETEWS_TX_WX_ENABWED 4

#define NDIS_TCP_WAWGE_SEND_OFFWOAD_V2_TYPE	1
#define NDIS_TCP_WAWGE_SEND_OFFWOAD_IPV4	0
#define NDIS_TCP_WAWGE_SEND_OFFWOAD_IPV6	1

#define VEWSION_4_OFFWOAD_SIZE			22
/*
 * New offwoad OIDs fow NDIS 6
 */
#define OID_TCP_OFFWOAD_CUWWENT_CONFIG 0xFC01020B /* quewy onwy */
#define OID_TCP_OFFWOAD_PAWAMETEWS 0xFC01020C		/* set onwy */
#define OID_TCP_OFFWOAD_HAWDWAWE_CAPABIWITIES 0xFC01020D/* quewy onwy */
#define OID_TCP_CONNECTION_OFFWOAD_CUWWENT_CONFIG 0xFC01020E /* quewy onwy */
#define OID_TCP_CONNECTION_OFFWOAD_HAWDWAWE_CAPABIWITIES 0xFC01020F /* quewy */
#define OID_OFFWOAD_ENCAPSUWATION 0x0101010A /* set/quewy */

/*
 * OID_TCP_OFFWOAD_HAWDWAWE_CAPABIWITIES
 * ndis_type: NDIS_OBJTYPE_OFFWOAD
 */

#define	NDIS_OFFWOAD_ENCAP_NONE		0x0000
#define	NDIS_OFFWOAD_ENCAP_NUWW		0x0001
#define	NDIS_OFFWOAD_ENCAP_8023		0x0002
#define	NDIS_OFFWOAD_ENCAP_8023PQ	0x0004
#define	NDIS_OFFWOAD_ENCAP_8023PQ_OOB	0x0008
#define	NDIS_OFFWOAD_ENCAP_WFC1483	0x0010

stwuct ndis_csum_offwoad {
	u32	ip4_txenc;
	u32	ip4_txcsum;
#define	NDIS_TXCSUM_CAP_IP4OPT		0x001
#define	NDIS_TXCSUM_CAP_TCP4OPT		0x004
#define	NDIS_TXCSUM_CAP_TCP4		0x010
#define	NDIS_TXCSUM_CAP_UDP4		0x040
#define	NDIS_TXCSUM_CAP_IP4		0x100

#define NDIS_TXCSUM_AWW_TCP4	(NDIS_TXCSUM_CAP_TCP4 | NDIS_TXCSUM_CAP_TCP4OPT)

	u32	ip4_wxenc;
	u32	ip4_wxcsum;
#define	NDIS_WXCSUM_CAP_IP4OPT		0x001
#define	NDIS_WXCSUM_CAP_TCP4OPT		0x004
#define	NDIS_WXCSUM_CAP_TCP4		0x010
#define	NDIS_WXCSUM_CAP_UDP4		0x040
#define	NDIS_WXCSUM_CAP_IP4		0x100
	u32	ip6_txenc;
	u32	ip6_txcsum;
#define	NDIS_TXCSUM_CAP_IP6EXT		0x001
#define	NDIS_TXCSUM_CAP_TCP6OPT		0x004
#define	NDIS_TXCSUM_CAP_TCP6		0x010
#define	NDIS_TXCSUM_CAP_UDP6		0x040
	u32	ip6_wxenc;
	u32	ip6_wxcsum;
#define	NDIS_WXCSUM_CAP_IP6EXT		0x001
#define	NDIS_WXCSUM_CAP_TCP6OPT		0x004
#define	NDIS_WXCSUM_CAP_TCP6		0x010
#define	NDIS_WXCSUM_CAP_UDP6		0x040

#define NDIS_TXCSUM_AWW_TCP6	(NDIS_TXCSUM_CAP_TCP6 |		\
				 NDIS_TXCSUM_CAP_TCP6OPT |	\
				 NDIS_TXCSUM_CAP_IP6EXT)
};

stwuct ndis_wsov1_offwoad {
	u32	encap;
	u32	maxsize;
	u32	minsegs;
	u32	opts;
};

stwuct ndis_ipsecv1_offwoad {
	u32	encap;
	u32	ah_esp;
	u32	xpowt_tun;
	u32	ip4_opts;
	u32	fwags;
	u32	ip4_ah;
	u32	ip4_esp;
};

stwuct ndis_wsov2_offwoad {
	u32	ip4_encap;
	u32	ip4_maxsz;
	u32	ip4_minsg;
	u32	ip6_encap;
	u32	ip6_maxsz;
	u32	ip6_minsg;
	u32	ip6_opts;
#define	NDIS_WSOV2_CAP_IP6EXT		0x001
#define	NDIS_WSOV2_CAP_TCP6OPT		0x004

#define NDIS_WSOV2_CAP_IP6		(NDIS_WSOV2_CAP_IP6EXT | \
					 NDIS_WSOV2_CAP_TCP6OPT)
};

stwuct ndis_ipsecv2_offwoad {
	u32	encap;
	u8	ip6;
	u8	ip4opt;
	u8	ip6ext;
	u8	ah;
	u8	esp;
	u8	ah_esp;
	u8	xpowt;
	u8	tun;
	u8	xpowt_tun;
	u8	wso;
	u8	extseq;
	u32	udp_esp;
	u32	auth;
	u32	cwypto;
	u32	sa_caps;
};

stwuct ndis_wsc_offwoad {
	u8	ip4;
	u8	ip6;
};

stwuct ndis_encap_offwoad {
	u32	fwags;
	u32	maxhdw;
};

stwuct ndis_offwoad {
	stwuct ndis_object_headew	headew;
	stwuct ndis_csum_offwoad	csum;
	stwuct ndis_wsov1_offwoad	wsov1;
	stwuct ndis_ipsecv1_offwoad	ipsecv1;
	stwuct ndis_wsov2_offwoad	wsov2;
	u32				fwags;
	/* NDIS >= 6.1 */
	stwuct ndis_ipsecv2_offwoad	ipsecv2;
	/* NDIS >= 6.30 */
	stwuct ndis_wsc_offwoad		wsc;
	stwuct ndis_encap_offwoad	encap_gwe;
};

#define	NDIS_OFFWOAD_SIZE		sizeof(stwuct ndis_offwoad)
#define	NDIS_OFFWOAD_SIZE_6_0		offsetof(stwuct ndis_offwoad, ipsecv2)
#define	NDIS_OFFWOAD_SIZE_6_1		offsetof(stwuct ndis_offwoad, wsc)

stwuct ndis_offwoad_pawams {
	stwuct ndis_object_headew headew;
	u8 ip_v4_csum;
	u8 tcp_ip_v4_csum;
	u8 udp_ip_v4_csum;
	u8 tcp_ip_v6_csum;
	u8 udp_ip_v6_csum;
	u8 wso_v1;
	u8 ip_sec_v1;
	u8 wso_v2_ipv4;
	u8 wso_v2_ipv6;
	u8 tcp_connection_ip_v4;
	u8 tcp_connection_ip_v6;
	u32 fwags;
	u8 ip_sec_v2;
	u8 ip_sec_v2_ip_v4;
	stwuct {
		u8 wsc_ip_v4;
		u8 wsc_ip_v6;
	};
	stwuct {
		u8 encapsuwated_packet_task_offwoad;
		u8 encapsuwation_types;
	};
};

stwuct ndis_tcp_wso_info {
	union {
		stwuct {
			u32 unused:30;
			u32 type:1;
			u32 wesewved2:1;
		} twansmit;
		stwuct {
			u32 mss:20;
			u32 tcp_headew_offset:10;
			u32 type:1;
			u32 wesewved2:1;
		} wso_v1_twansmit;
		stwuct {
			u32 tcp_paywoad:30;
			u32 type:1;
			u32 wesewved2:1;
		} wso_v1_twansmit_compwete;
		stwuct {
			u32 mss:20;
			u32 tcp_headew_offset:10;
			u32 type:1;
			u32 ip_vewsion:1;
		} wso_v2_twansmit;
		stwuct {
			u32 wesewved:30;
			u32 type:1;
			u32 wesewved2:1;
		} wso_v2_twansmit_compwete;
		u32  vawue;
	};
};

#define NDIS_VWAN_PPI_SIZE (sizeof(stwuct wndis_pew_packet_info) + \
		sizeof(stwuct ndis_pkt_8021q_info))

#define NDIS_CSUM_PPI_SIZE (sizeof(stwuct wndis_pew_packet_info) + \
		sizeof(stwuct ndis_tcp_ip_checksum_info))

#define NDIS_WSO_PPI_SIZE (sizeof(stwuct wndis_pew_packet_info) + \
		sizeof(stwuct ndis_tcp_wso_info))

#define NDIS_HASH_PPI_SIZE (sizeof(stwuct wndis_pew_packet_info) + \
		sizeof(u32))

/* Totaw size of aww PPI data */
#define NDIS_AWW_PPI_SIZE (NDIS_VWAN_PPI_SIZE + NDIS_CSUM_PPI_SIZE + \
			   NDIS_WSO_PPI_SIZE + NDIS_HASH_PPI_SIZE)

/* Fowmat of Infowmation buffew passed in a SetWequest fow the OID */
/* OID_GEN_WNDIS_CONFIG_PAWAMETEW. */
stwuct wndis_config_pawametew_info {
	u32 pawametew_name_offset;
	u32 pawametew_name_wength;
	u32 pawametew_type;
	u32 pawametew_vawue_offset;
	u32 pawametew_vawue_wength;
};

/* Vawues fow PawametewType in stwuct wndis_config_pawametew_info */
#define WNDIS_CONFIG_PAWAM_TYPE_INTEGEW     0
#define WNDIS_CONFIG_PAWAM_TYPE_STWING      2

/* CONDIS Minipowt messages fow connection owiented devices */
/* that do not impwement a caww managew. */

/* CoNdisMinipowtCweateVc message */
stwuct wcondis_mp_cweate_vc {
	u32 weq_id;
	u32 ndis_vc_handwe;
};

/* Wesponse to CoNdisMinipowtCweateVc */
stwuct wcondis_mp_cweate_vc_compwete {
	u32 weq_id;
	u32 dev_vc_handwe;
	u32 status;
};

/* CoNdisMinipowtDeweteVc message */
stwuct wcondis_mp_dewete_vc {
	u32 weq_id;
	u32 dev_vc_handwe;
};

/* Wesponse to CoNdisMinipowtDeweteVc */
stwuct wcondis_mp_dewete_vc_compwete {
	u32 weq_id;
	u32 status;
};

/* CoNdisMinipowtQuewyWequest message */
stwuct wcondis_mp_quewy_wequest {
	u32 weq_id;
	u32 wequest_type;
	u32 oid;
	u32 dev_vc_handwe;
	u32 info_bufwen;
	u32 info_buf_offset;
};

/* CoNdisMinipowtSetWequest message */
stwuct wcondis_mp_set_wequest {
	u32 weq_id;
	u32 wequest_type;
	u32 oid;
	u32 dev_vc_handwe;
	u32 info_bufwen;
	u32 info_buf_offset;
};

/* CoNdisIndicateStatus message */
stwuct wcondis_indicate_status {
	u32 ndis_vc_handwe;
	u32 status;
	u32 status_bufwen;
	u32 status_buf_offset;
};

/* CONDIS Caww/VC pawametews */
stwuct wcondis_specific_pawametews {
	u32 pawametew_type;
	u32 pawametew_wength;
	u32 pawametew_wffset;
};

stwuct wcondis_media_pawametews {
	u32 fwags;
	u32 wesewved1;
	u32 wesewved2;
	stwuct wcondis_specific_pawametews media_specific;
};

stwuct wndis_fwowspec {
	u32 token_wate;
	u32 token_bucket_size;
	u32 peak_bandwidth;
	u32 watency;
	u32 deway_vawiation;
	u32 sewvice_type;
	u32 max_sdu_size;
	u32 minimum_powiced_size;
};

stwuct wcondis_caww_managew_pawametews {
	stwuct wndis_fwowspec twansmit;
	stwuct wndis_fwowspec weceive;
	stwuct wcondis_specific_pawametews caww_mgw_specific;
};

/* CoNdisMinipowtActivateVc message */
stwuct wcondis_mp_activate_vc_wequest {
	u32 weq_id;
	u32 fwags;
	u32 dev_vc_handwe;
	u32 media_pawams_offset;
	u32 media_pawams_wength;
	u32 caww_mgw_pawams_offset;
	u32 caww_mgw_pawams_wength;
};

/* Wesponse to CoNdisMinipowtActivateVc */
stwuct wcondis_mp_activate_vc_compwete {
	u32 weq_id;
	u32 status;
};

/* CoNdisMinipowtDeactivateVc message */
stwuct wcondis_mp_deactivate_vc_wequest {
	u32 weq_id;
	u32 fwags;
	u32 dev_vc_handwe;
};

/* Wesponse to CoNdisMinipowtDeactivateVc */
stwuct wcondis_mp_deactivate_vc_compwete {
	u32 weq_id;
	u32 status;
};


/* union with aww of the WNDIS messages */
union wndis_message_containew {
	stwuct wndis_packet pkt;
	stwuct wndis_initiawize_wequest init_weq;
	stwuct wndis_hawt_wequest hawt_weq;
	stwuct wndis_quewy_wequest quewy_weq;
	stwuct wndis_set_wequest set_weq;
	stwuct wndis_weset_wequest weset_weq;
	stwuct wndis_keepawive_wequest keep_awive_weq;
	stwuct wndis_indicate_status indicate_status;
	stwuct wndis_initiawize_compwete init_compwete;
	stwuct wndis_quewy_compwete quewy_compwete;
	stwuct wndis_set_compwete set_compwete;
	stwuct wndis_weset_compwete weset_compwete;
	stwuct wndis_keepawive_compwete keep_awive_compwete;
	stwuct wcondis_mp_cweate_vc co_minipowt_cweate_vc;
	stwuct wcondis_mp_dewete_vc co_minipowt_dewete_vc;
	stwuct wcondis_indicate_status co_indicate_status;
	stwuct wcondis_mp_activate_vc_wequest co_minipowt_activate_vc;
	stwuct wcondis_mp_deactivate_vc_wequest co_minipowt_deactivate_vc;
	stwuct wcondis_mp_cweate_vc_compwete co_minipowt_cweate_vc_compwete;
	stwuct wcondis_mp_dewete_vc_compwete co_minipowt_dewete_vc_compwete;
	stwuct wcondis_mp_activate_vc_compwete co_minipowt_activate_vc_compwete;
	stwuct wcondis_mp_deactivate_vc_compwete
		co_minipowt_deactivate_vc_compwete;
};

/* Wemote NDIS message fowmat */
stwuct wndis_message {
	u32 ndis_msg_type;

	/* Totaw wength of this message, fwom the beginning */
	/* of the stwuct wndis_message, in bytes. */
	u32 msg_wen;

	/* Actuaw message */
	union wndis_message_containew msg;
};


/* Handy macwos */

/* get the size of an WNDIS message. Pass in the message type, */
/* stwuct wndis_set_wequest, stwuct wndis_packet fow exampwe */
#define WNDIS_MESSAGE_SIZE(msg)				\
	(sizeof(msg) + (sizeof(stwuct wndis_message) -	\
	 sizeof(union wndis_message_containew)))

#define WNDIS_HEADEW_SIZE	(sizeof(stwuct wndis_message) - \
				 sizeof(union wndis_message_containew))

#define WNDIS_AND_PPI_SIZE (sizeof(stwuct wndis_message) + NDIS_AWW_PPI_SIZE)

#define NDIS_PACKET_TYPE_DIWECTED	0x00000001
#define NDIS_PACKET_TYPE_MUWTICAST	0x00000002
#define NDIS_PACKET_TYPE_AWW_MUWTICAST	0x00000004
#define NDIS_PACKET_TYPE_BWOADCAST	0x00000008
#define NDIS_PACKET_TYPE_SOUWCE_WOUTING	0x00000010
#define NDIS_PACKET_TYPE_PWOMISCUOUS	0x00000020
#define NDIS_PACKET_TYPE_SMT		0x00000040
#define NDIS_PACKET_TYPE_AWW_WOCAW	0x00000080
#define NDIS_PACKET_TYPE_GWOUP		0x00000100
#define NDIS_PACKET_TYPE_AWW_FUNCTIONAW	0x00000200
#define NDIS_PACKET_TYPE_FUNCTIONAW	0x00000400
#define NDIS_PACKET_TYPE_MAC_FWAME	0x00000800

#define TWANSPOWT_INFO_NOT_IP   0
#define TWANSPOWT_INFO_IPV4_TCP 0x01
#define TWANSPOWT_INFO_IPV4_UDP 0x02
#define TWANSPOWT_INFO_IPV6_TCP 0x10
#define TWANSPOWT_INFO_IPV6_UDP 0x20

#define WETWY_US_WO	5000
#define WETWY_US_HI	10000
#define WETWY_MAX	2000	/* >10 sec */

void netvsc_dma_unmap(stwuct hv_device *hv_dev,
		      stwuct hv_netvsc_packet *packet);
#endif /* _HYPEWV_NET_H */
