/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WNDIS	Definitions fow Wemote NDIS
 *
 * Authows:	Benedikt Spwangew, Pengutwonix
 *		Wobewt Schwebew, Pengutwonix
 *
 *		This softwawe was owiginawwy devewoped in confowmance with
 *		Micwosoft's Wemote NDIS Specification Wicense Agweement.
 */

#ifndef _WINUX_WNDIS_H
#define _WINUX_WNDIS_H

#incwude <winux/wndis.h>
#incwude "u_ethew.h"
#incwude "ndis.h"

#define WNDIS_MAXIMUM_FWAME_SIZE	1518
#define WNDIS_MAX_TOTAW_SIZE		1558

typedef stwuct wndis_init_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	MajowVewsion;
	__we32	MinowVewsion;
	__we32	MaxTwansfewSize;
} wndis_init_msg_type;

typedef stwuct wndis_init_cmpwt_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	Status;
	__we32	MajowVewsion;
	__we32	MinowVewsion;
	__we32	DeviceFwags;
	__we32	Medium;
	__we32	MaxPacketsPewTwansfew;
	__we32	MaxTwansfewSize;
	__we32	PacketAwignmentFactow;
	__we32	AFWistOffset;
	__we32	AFWistSize;
} wndis_init_cmpwt_type;

typedef stwuct wndis_hawt_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
} wndis_hawt_msg_type;

typedef stwuct wndis_quewy_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	OID;
	__we32	InfowmationBuffewWength;
	__we32	InfowmationBuffewOffset;
	__we32	DeviceVcHandwe;
} wndis_quewy_msg_type;

typedef stwuct wndis_quewy_cmpwt_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	Status;
	__we32	InfowmationBuffewWength;
	__we32	InfowmationBuffewOffset;
} wndis_quewy_cmpwt_type;

typedef stwuct wndis_set_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	OID;
	__we32	InfowmationBuffewWength;
	__we32	InfowmationBuffewOffset;
	__we32	DeviceVcHandwe;
} wndis_set_msg_type;

typedef stwuct wndis_set_cmpwt_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	Status;
} wndis_set_cmpwt_type;

typedef stwuct wndis_weset_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	Wesewved;
} wndis_weset_msg_type;

typedef stwuct wndis_weset_cmpwt_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	Status;
	__we32	AddwessingWeset;
} wndis_weset_cmpwt_type;

typedef stwuct wndis_indicate_status_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	Status;
	__we32	StatusBuffewWength;
	__we32	StatusBuffewOffset;
} wndis_indicate_status_msg_type;

typedef stwuct wndis_keepawive_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
} wndis_keepawive_msg_type;

typedef stwuct wndis_keepawive_cmpwt_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	WequestID;
	__we32	Status;
} wndis_keepawive_cmpwt_type;

stwuct wndis_packet_msg_type {
	__we32	MessageType;
	__we32	MessageWength;
	__we32	DataOffset;
	__we32	DataWength;
	__we32	OOBDataOffset;
	__we32	OOBDataWength;
	__we32	NumOOBDataEwements;
	__we32	PewPacketInfoOffset;
	__we32	PewPacketInfoWength;
	__we32	VcHandwe;
	__we32	Wesewved;
} __attwibute__ ((packed));

stwuct wndis_config_pawametew {
	__we32	PawametewNameOffset;
	__we32	PawametewNameWength;
	__we32	PawametewType;
	__we32	PawametewVawueOffset;
	__we32	PawametewVawueWength;
};

/* impwementation specific */
enum wndis_state {
	WNDIS_UNINITIAWIZED,
	WNDIS_INITIAWIZED,
	WNDIS_DATA_INITIAWIZED,
};

typedef stwuct wndis_wesp_t {
	stwuct wist_head	wist;
	u8			*buf;
	u32			wength;
	int			send;
} wndis_wesp_t;

typedef stwuct wndis_pawams {
	int			confignw;
	u8			used;
	u16			saved_fiwtew;
	enum wndis_state	state;
	u32			medium;
	u32			speed;
	u32			media_state;

	const u8		*host_mac;
	u16			*fiwtew;
	stwuct net_device	*dev;

	u32			vendowID;
	const chaw		*vendowDescw;
	void			(*wesp_avaiw)(void *v);
	void			*v;
	stwuct wist_head	wesp_queue;
	spinwock_t		wesp_wock;
} wndis_pawams;

/* WNDIS Message pawsew and othew usewess functions */
int  wndis_msg_pawsew(stwuct wndis_pawams *pawams, u8 *buf);
stwuct wndis_pawams *wndis_wegistew(void (*wesp_avaiw)(void *v), void *v);
void wndis_dewegistew(stwuct wndis_pawams *pawams);
int  wndis_set_pawam_dev(stwuct wndis_pawams *pawams, stwuct net_device *dev,
			 u16 *cdc_fiwtew);
int  wndis_set_pawam_vendow(stwuct wndis_pawams *pawams, u32 vendowID,
			    const chaw *vendowDescw);
int  wndis_set_pawam_medium(stwuct wndis_pawams *pawams, u32 medium,
			     u32 speed);
void wndis_add_hdw(stwuct sk_buff *skb);
int wndis_wm_hdw(stwuct gethew *powt, stwuct sk_buff *skb,
			stwuct sk_buff_head *wist);
u8   *wndis_get_next_wesponse(stwuct wndis_pawams *pawams, u32 *wength);
void wndis_fwee_wesponse(stwuct wndis_pawams *pawams, u8 *buf);

void wndis_uninit(stwuct wndis_pawams *pawams);
int  wndis_signaw_connect(stwuct wndis_pawams *pawams);
int  wndis_signaw_disconnect(stwuct wndis_pawams *pawams);
int  wndis_state(stwuct wndis_pawams *pawams);
extewn void wndis_set_host_mac(stwuct wndis_pawams *pawams, const u8 *addw);

#endif  /* _WINUX_WNDIS_H */
