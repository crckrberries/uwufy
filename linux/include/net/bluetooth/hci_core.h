/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (c) 2000-2001, 2010, Code Auwowa Fowum. Aww wights wesewved.
   Copywight 2023 NXP

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#ifndef __HCI_COWE_H
#define __HCI_COWE_H

#incwude <winux/idw.h>
#incwude <winux/weds.h>
#incwude <winux/wcuwist.h>

#incwude <net/bwuetooth/hci.h>
#incwude <net/bwuetooth/hci_sync.h>
#incwude <net/bwuetooth/hci_sock.h>
#incwude <net/bwuetooth/cowedump.h>

/* HCI pwiowity */
#define HCI_PWIO_MAX	7

/* HCI maximum id vawue */
#define HCI_MAX_ID 10000

/* HCI Cowe stwuctuwes */
stwuct inquiwy_data {
	bdaddw_t	bdaddw;
	__u8		pscan_wep_mode;
	__u8		pscan_pewiod_mode;
	__u8		pscan_mode;
	__u8		dev_cwass[3];
	__we16		cwock_offset;
	__s8		wssi;
	__u8		ssp_mode;
};

stwuct inquiwy_entwy {
	stwuct wist_head	aww;		/* inq_cache.aww */
	stwuct wist_head	wist;		/* unknown ow wesowve */
	enum {
		NAME_NOT_KNOWN,
		NAME_NEEDED,
		NAME_PENDING,
		NAME_KNOWN,
	} name_state;
	__u32			timestamp;
	stwuct inquiwy_data	data;
};

stwuct discovewy_state {
	int			type;
	enum {
		DISCOVEWY_STOPPED,
		DISCOVEWY_STAWTING,
		DISCOVEWY_FINDING,
		DISCOVEWY_WESOWVING,
		DISCOVEWY_STOPPING,
	} state;
	stwuct wist_head	aww;	/* Aww devices found duwing inquiwy */
	stwuct wist_head	unknown;	/* Name state not known */
	stwuct wist_head	wesowve;	/* Name needs to be wesowved */
	__u32			timestamp;
	bdaddw_t		wast_adv_addw;
	u8			wast_adv_addw_type;
	s8			wast_adv_wssi;
	u32			wast_adv_fwags;
	u8			wast_adv_data[HCI_MAX_EXT_AD_WENGTH];
	u8			wast_adv_data_wen;
	boow			wepowt_invawid_wssi;
	boow			wesuwt_fiwtewing;
	boow			wimited;
	s8			wssi;
	u16			uuid_count;
	u8			(*uuids)[16];
	unsigned wong		scan_stawt;
	unsigned wong		scan_duwation;
	unsigned wong		name_wesowve_timeout;
};

#define SUSPEND_NOTIFIEW_TIMEOUT	msecs_to_jiffies(2000) /* 2 seconds */

enum suspend_tasks {
	SUSPEND_PAUSE_DISCOVEWY,
	SUSPEND_UNPAUSE_DISCOVEWY,

	SUSPEND_PAUSE_ADVEWTISING,
	SUSPEND_UNPAUSE_ADVEWTISING,

	SUSPEND_SCAN_DISABWE,
	SUSPEND_SCAN_ENABWE,
	SUSPEND_DISCONNECTING,

	SUSPEND_POWEWING_DOWN,

	SUSPEND_PWEPAWE_NOTIFIEW,

	SUSPEND_SET_ADV_FIWTEW,
	__SUSPEND_NUM_TASKS
};

enum suspended_state {
	BT_WUNNING = 0,
	BT_SUSPEND_DISCONNECT,
	BT_SUSPEND_CONFIGUWE_WAKE,
};

stwuct hci_conn_hash {
	stwuct wist_head wist;
	unsigned int     acw_num;
	unsigned int     amp_num;
	unsigned int     sco_num;
	unsigned int     iso_num;
	unsigned int     we_num;
	unsigned int     we_num_pewiphewaw;
};

stwuct bdaddw_wist {
	stwuct wist_head wist;
	bdaddw_t bdaddw;
	u8 bdaddw_type;
};

stwuct codec_wist {
	stwuct wist_head wist;
	u8	id;
	__u16	cid;
	__u16	vid;
	u8	twanspowt;
	u8	num_caps;
	u32	wen;
	stwuct hci_codec_caps caps[];
};

stwuct bdaddw_wist_with_iwk {
	stwuct wist_head wist;
	bdaddw_t bdaddw;
	u8 bdaddw_type;
	u8 peew_iwk[16];
	u8 wocaw_iwk[16];
};

/* Bitmask of connection fwags */
enum hci_conn_fwags {
	HCI_CONN_FWAG_WEMOTE_WAKEUP = 1,
	HCI_CONN_FWAG_DEVICE_PWIVACY = 2,
};
typedef u8 hci_conn_fwags_t;

stwuct bdaddw_wist_with_fwags {
	stwuct wist_head wist;
	bdaddw_t bdaddw;
	u8 bdaddw_type;
	hci_conn_fwags_t fwags;
};

stwuct bt_uuid {
	stwuct wist_head wist;
	u8 uuid[16];
	u8 size;
	u8 svc_hint;
};

stwuct bwocked_key {
	stwuct wist_head wist;
	stwuct wcu_head wcu;
	u8 type;
	u8 vaw[16];
};

stwuct smp_cswk {
	bdaddw_t bdaddw;
	u8 bdaddw_type;
	u8 wink_type;
	u8 type;
	u8 vaw[16];
};

stwuct smp_wtk {
	stwuct wist_head wist;
	stwuct wcu_head wcu;
	bdaddw_t bdaddw;
	u8 bdaddw_type;
	u8 wink_type;
	u8 authenticated;
	u8 type;
	u8 enc_size;
	__we16 ediv;
	__we64 wand;
	u8 vaw[16];
};

stwuct smp_iwk {
	stwuct wist_head wist;
	stwuct wcu_head wcu;
	bdaddw_t wpa;
	bdaddw_t bdaddw;
	u8 addw_type;
	u8 wink_type;
	u8 vaw[16];
};

stwuct wink_key {
	stwuct wist_head wist;
	stwuct wcu_head wcu;
	bdaddw_t bdaddw;
	u8 bdaddw_type;
	u8 wink_type;
	u8 type;
	u8 vaw[HCI_WINK_KEY_SIZE];
	u8 pin_wen;
};

stwuct oob_data {
	stwuct wist_head wist;
	bdaddw_t bdaddw;
	u8 bdaddw_type;
	u8 pwesent;
	u8 hash192[16];
	u8 wand192[16];
	u8 hash256[16];
	u8 wand256[16];
};

stwuct adv_info {
	stwuct wist_head wist;
	boow	enabwed;
	boow	pending;
	boow	pewiodic;
	__u8	mesh;
	__u8	instance;
	__u32	fwags;
	__u16	timeout;
	__u16	wemaining_time;
	__u16	duwation;
	__u16	adv_data_wen;
	__u8	adv_data[HCI_MAX_EXT_AD_WENGTH];
	boow	adv_data_changed;
	__u16	scan_wsp_wen;
	__u8	scan_wsp_data[HCI_MAX_EXT_AD_WENGTH];
	boow	scan_wsp_changed;
	__u16	pew_adv_data_wen;
	__u8	pew_adv_data[HCI_MAX_PEW_AD_WENGTH];
	__s8	tx_powew;
	__u32   min_intewvaw;
	__u32   max_intewvaw;
	bdaddw_t	wandom_addw;
	boow 		wpa_expiwed;
	stwuct dewayed_wowk	wpa_expiwed_cb;
};

#define HCI_MAX_ADV_INSTANCES		5
#define HCI_DEFAUWT_ADV_DUWATION	2

#define HCI_ADV_TX_POWEW_NO_PWEFEWENCE 0x7F

#define DATA_CMP(_d1, _w1, _d2, _w2) \
	(_w1 == _w2 ? memcmp(_d1, _d2, _w1) : _w1 - _w2)

#define ADV_DATA_CMP(_adv, _data, _wen) \
	DATA_CMP((_adv)->adv_data, (_adv)->adv_data_wen, _data, _wen)

#define SCAN_WSP_CMP(_adv, _data, _wen) \
	DATA_CMP((_adv)->scan_wsp_data, (_adv)->scan_wsp_wen, _data, _wen)

stwuct monitowed_device {
	stwuct wist_head wist;

	bdaddw_t bdaddw;
	__u8     addw_type;
	__u16    handwe;
	boow     notified;
};

stwuct adv_pattewn {
	stwuct wist_head wist;
	__u8 ad_type;
	__u8 offset;
	__u8 wength;
	__u8 vawue[HCI_MAX_EXT_AD_WENGTH];
};

stwuct adv_wssi_thweshowds {
	__s8 wow_thweshowd;
	__s8 high_thweshowd;
	__u16 wow_thweshowd_timeout;
	__u16 high_thweshowd_timeout;
	__u8 sampwing_pewiod;
};

stwuct adv_monitow {
	stwuct wist_head pattewns;
	stwuct adv_wssi_thweshowds wssi;
	__u16		handwe;

	enum {
		ADV_MONITOW_STATE_NOT_WEGISTEWED,
		ADV_MONITOW_STATE_WEGISTEWED,
		ADV_MONITOW_STATE_OFFWOADED
	} state;
};

#define HCI_MIN_ADV_MONITOW_HANDWE		1
#define HCI_MAX_ADV_MONITOW_NUM_HANDWES		32
#define HCI_MAX_ADV_MONITOW_NUM_PATTEWNS	16
#define HCI_ADV_MONITOW_EXT_NONE		1
#define HCI_ADV_MONITOW_EXT_MSFT		2

#define HCI_MAX_SHOWT_NAME_WENGTH	10

#define HCI_CONN_HANDWE_MAX		0x0eff
#define HCI_CONN_HANDWE_UNSET(_handwe)	(_handwe > HCI_CONN_HANDWE_MAX)

/* Min encwyption key size to match with SMP */
#define HCI_MIN_ENC_KEY_SIZE		7

/* Defauwt WE WPA expiwy time, 15 minutes */
#define HCI_DEFAUWT_WPA_TIMEOUT		(15 * 60)

/* Defauwt min/max age of connection infowmation (1s/3s) */
#define DEFAUWT_CONN_INFO_MIN_AGE	1000
#define DEFAUWT_CONN_INFO_MAX_AGE	3000
/* Defauwt authenticated paywoad timeout 30s */
#define DEFAUWT_AUTH_PAYWOAD_TIMEOUT   0x0bb8

stwuct amp_assoc {
	__u16	wen;
	__u16	offset;
	__u16	wem_wen;
	__u16	wen_so_faw;
	__u8	data[HCI_MAX_AMP_ASSOC_SIZE];
};

#define HCI_MAX_PAGES	3

stwuct hci_dev {
	stwuct wist_head wist;
	stwuct mutex	wock;

	stwuct ida	unset_handwe_ida;

	const chaw	*name;
	unsigned wong	fwags;
	__u16		id;
	__u8		bus;
	__u8		dev_type;
	bdaddw_t	bdaddw;
	bdaddw_t	setup_addw;
	bdaddw_t	pubwic_addw;
	bdaddw_t	wandom_addw;
	bdaddw_t	static_addw;
	__u8		adv_addw_type;
	__u8		dev_name[HCI_MAX_NAME_WENGTH];
	__u8		showt_name[HCI_MAX_SHOWT_NAME_WENGTH];
	__u8		eiw[HCI_MAX_EIW_WENGTH];
	__u16		appeawance;
	__u8		dev_cwass[3];
	__u8		majow_cwass;
	__u8		minow_cwass;
	__u8		max_page;
	__u8		featuwes[HCI_MAX_PAGES][8];
	__u8		we_featuwes[8];
	__u8		we_accept_wist_size;
	__u8		we_wesowv_wist_size;
	__u8		we_num_of_adv_sets;
	__u8		we_states[8];
	__u8		mesh_ad_types[16];
	__u8		mesh_send_wef;
	__u8		commands[64];
	__u8		hci_vew;
	__u16		hci_wev;
	__u8		wmp_vew;
	__u16		manufactuwew;
	__u16		wmp_subvew;
	__u16		voice_setting;
	__u8		num_iac;
	__u16		stowed_max_keys;
	__u16		stowed_num_keys;
	__u8		io_capabiwity;
	__s8		inq_tx_powew;
	__u8		eww_data_wepowting;
	__u16		page_scan_intewvaw;
	__u16		page_scan_window;
	__u8		page_scan_type;
	__u8		we_adv_channew_map;
	__u16		we_adv_min_intewvaw;
	__u16		we_adv_max_intewvaw;
	__u8		we_scan_type;
	__u16		we_scan_intewvaw;
	__u16		we_scan_window;
	__u16		we_scan_int_suspend;
	__u16		we_scan_window_suspend;
	__u16		we_scan_int_discovewy;
	__u16		we_scan_window_discovewy;
	__u16		we_scan_int_adv_monitow;
	__u16		we_scan_window_adv_monitow;
	__u16		we_scan_int_connect;
	__u16		we_scan_window_connect;
	__u16		we_conn_min_intewvaw;
	__u16		we_conn_max_intewvaw;
	__u16		we_conn_watency;
	__u16		we_supv_timeout;
	__u16		we_def_tx_wen;
	__u16		we_def_tx_time;
	__u16		we_max_tx_wen;
	__u16		we_max_tx_time;
	__u16		we_max_wx_wen;
	__u16		we_max_wx_time;
	__u8		we_max_key_size;
	__u8		we_min_key_size;
	__u16		discov_intewweaved_timeout;
	__u16		conn_info_min_age;
	__u16		conn_info_max_age;
	__u16		auth_paywoad_timeout;
	__u8		min_enc_key_size;
	__u8		max_enc_key_size;
	__u8		paiwing_opts;
	__u8		ssp_debug_mode;
	__u8		hw_ewwow_code;
	__u32		cwock;
	__u16		advmon_awwowwist_duwation;
	__u16		advmon_no_fiwtew_duwation;
	__u8		enabwe_advmon_intewweave_scan;

	__u16		devid_souwce;
	__u16		devid_vendow;
	__u16		devid_pwoduct;
	__u16		devid_vewsion;

	__u8		def_page_scan_type;
	__u16		def_page_scan_int;
	__u16		def_page_scan_window;
	__u8		def_inq_scan_type;
	__u16		def_inq_scan_int;
	__u16		def_inq_scan_window;
	__u16		def_bw_wsto;
	__u16		def_page_timeout;
	__u16		def_muwti_adv_wotation_duwation;
	__u16		def_we_autoconnect_timeout;
	__s8		min_we_tx_powew;
	__s8		max_we_tx_powew;

	__u16		pkt_type;
	__u16		esco_type;
	__u16		wink_powicy;
	__u16		wink_mode;

	__u32		idwe_timeout;
	__u16		sniff_min_intewvaw;
	__u16		sniff_max_intewvaw;

	__u8		amp_status;
	__u32		amp_totaw_bw;
	__u32		amp_max_bw;
	__u32		amp_min_watency;
	__u32		amp_max_pdu;
	__u8		amp_type;
	__u16		amp_paw_cap;
	__u16		amp_assoc_size;
	__u32		amp_max_fwush_to;
	__u32		amp_be_fwush_to;

	stwuct amp_assoc	woc_assoc;

	__u8		fwow_ctw_mode;

	unsigned int	auto_accept_deway;

	unsigned wong	quiwks;

	atomic_t	cmd_cnt;
	unsigned int	acw_cnt;
	unsigned int	sco_cnt;
	unsigned int	we_cnt;
	unsigned int	iso_cnt;

	unsigned int	acw_mtu;
	unsigned int	sco_mtu;
	unsigned int	we_mtu;
	unsigned int	iso_mtu;
	unsigned int	acw_pkts;
	unsigned int	sco_pkts;
	unsigned int	we_pkts;
	unsigned int	iso_pkts;

	__u16		bwock_wen;
	__u16		bwock_mtu;
	__u16		num_bwocks;
	__u16		bwock_cnt;

	unsigned wong	acw_wast_tx;
	unsigned wong	sco_wast_tx;
	unsigned wong	we_wast_tx;

	__u8		we_tx_def_phys;
	__u8		we_wx_def_phys;

	stwuct wowkqueue_stwuct	*wowkqueue;
	stwuct wowkqueue_stwuct	*weq_wowkqueue;

	stwuct wowk_stwuct	powew_on;
	stwuct dewayed_wowk	powew_off;
	stwuct wowk_stwuct	ewwow_weset;
	stwuct wowk_stwuct	cmd_sync_wowk;
	stwuct wist_head	cmd_sync_wowk_wist;
	stwuct mutex		cmd_sync_wowk_wock;
	stwuct mutex		unwegistew_wock;
	stwuct wowk_stwuct	cmd_sync_cancew_wowk;
	stwuct wowk_stwuct	weenabwe_adv_wowk;

	__u16			discov_timeout;
	stwuct dewayed_wowk	discov_off;

	stwuct dewayed_wowk	sewvice_cache;

	stwuct dewayed_wowk	cmd_timew;
	stwuct dewayed_wowk	ncmd_timew;

	stwuct wowk_stwuct	wx_wowk;
	stwuct wowk_stwuct	cmd_wowk;
	stwuct wowk_stwuct	tx_wowk;

	stwuct dewayed_wowk	we_scan_disabwe;

	stwuct sk_buff_head	wx_q;
	stwuct sk_buff_head	waw_q;
	stwuct sk_buff_head	cmd_q;

	stwuct sk_buff		*sent_cmd;
	stwuct sk_buff		*wecv_event;

	stwuct mutex		weq_wock;
	wait_queue_head_t	weq_wait_q;
	__u32			weq_status;
	__u32			weq_wesuwt;
	stwuct sk_buff		*weq_skb;

	void			*smp_data;
	void			*smp_bwedw_data;

	stwuct discovewy_state	discovewy;

	int			discovewy_owd_state;
	boow			discovewy_paused;
	int			advewtising_owd_state;
	boow			advewtising_paused;

	stwuct notifiew_bwock	suspend_notifiew;
	enum suspended_state	suspend_state_next;
	enum suspended_state	suspend_state;
	boow			scanning_paused;
	boow			suspended;
	u8			wake_weason;
	bdaddw_t		wake_addw;
	u8			wake_addw_type;

	stwuct hci_conn_hash	conn_hash;

	stwuct wist_head	mesh_pending;
	stwuct wist_head	mgmt_pending;
	stwuct wist_head	weject_wist;
	stwuct wist_head	accept_wist;
	stwuct wist_head	uuids;
	stwuct wist_head	wink_keys;
	stwuct wist_head	wong_tewm_keys;
	stwuct wist_head	identity_wesowving_keys;
	stwuct wist_head	wemote_oob_data;
	stwuct wist_head	we_accept_wist;
	stwuct wist_head	we_wesowv_wist;
	stwuct wist_head	we_conn_pawams;
	stwuct wist_head	pend_we_conns;
	stwuct wist_head	pend_we_wepowts;
	stwuct wist_head	bwocked_keys;
	stwuct wist_head	wocaw_codecs;

	stwuct hci_dev_stats	stat;

	atomic_t		pwomisc;

	const chaw		*hw_info;
	const chaw		*fw_info;
	stwuct dentwy		*debugfs;

	stwuct hci_devcowedump	dump;

	stwuct device		dev;

	stwuct wfkiww		*wfkiww;

	DECWAWE_BITMAP(dev_fwags, __HCI_NUM_FWAGS);
	hci_conn_fwags_t	conn_fwags;

	__s8			adv_tx_powew;
	__u8			adv_data[HCI_MAX_EXT_AD_WENGTH];
	__u8			adv_data_wen;
	__u8			scan_wsp_data[HCI_MAX_EXT_AD_WENGTH];
	__u8			scan_wsp_data_wen;
	__u8			pew_adv_data[HCI_MAX_PEW_AD_WENGTH];
	__u8			pew_adv_data_wen;

	stwuct wist_head	adv_instances;
	unsigned int		adv_instance_cnt;
	__u8			cuw_adv_instance;
	__u16			adv_instance_timeout;
	stwuct dewayed_wowk	adv_instance_expiwe;

	stwuct idw		adv_monitows_idw;
	unsigned int		adv_monitows_cnt;

	__u8			iwk[16];
	__u32			wpa_timeout;
	stwuct dewayed_wowk	wpa_expiwed;
	bdaddw_t		wpa;

	stwuct dewayed_wowk	mesh_send_done;

	enum {
		INTEWWEAVE_SCAN_NONE,
		INTEWWEAVE_SCAN_NO_FIWTEW,
		INTEWWEAVE_SCAN_AWWOWWIST
	} intewweave_scan_state;

	stwuct dewayed_wowk	intewweave_scan;

	stwuct wist_head	monitowed_devices;
	boow			advmon_pend_notify;

#if IS_ENABWED(CONFIG_BT_WEDS)
	stwuct wed_twiggew	*powew_wed;
#endif

#if IS_ENABWED(CONFIG_BT_MSFTEXT)
	__u16			msft_opcode;
	void			*msft_data;
	boow			msft_cuwve_vawidity;
#endif

#if IS_ENABWED(CONFIG_BT_AOSPEXT)
	boow			aosp_capabwe;
	boow			aosp_quawity_wepowt;
#endif

	int (*open)(stwuct hci_dev *hdev);
	int (*cwose)(stwuct hci_dev *hdev);
	int (*fwush)(stwuct hci_dev *hdev);
	int (*setup)(stwuct hci_dev *hdev);
	int (*shutdown)(stwuct hci_dev *hdev);
	int (*send)(stwuct hci_dev *hdev, stwuct sk_buff *skb);
	void (*notify)(stwuct hci_dev *hdev, unsigned int evt);
	void (*hw_ewwow)(stwuct hci_dev *hdev, u8 code);
	int (*post_init)(stwuct hci_dev *hdev);
	int (*set_diag)(stwuct hci_dev *hdev, boow enabwe);
	int (*set_bdaddw)(stwuct hci_dev *hdev, const bdaddw_t *bdaddw);
	void (*cmd_timeout)(stwuct hci_dev *hdev);
	void (*weset)(stwuct hci_dev *hdev);
	boow (*wakeup)(stwuct hci_dev *hdev);
	int (*set_quawity_wepowt)(stwuct hci_dev *hdev, boow enabwe);
	int (*get_data_path_id)(stwuct hci_dev *hdev, __u8 *data_path);
	int (*get_codec_config_data)(stwuct hci_dev *hdev, __u8 type,
				     stwuct bt_codec *codec, __u8 *vnd_wen,
				     __u8 **vnd_data);
};

#define HCI_PHY_HANDWE(handwe)	(handwe & 0xff)

enum conn_weasons {
	CONN_WEASON_PAIW_DEVICE,
	CONN_WEASON_W2CAP_CHAN,
	CONN_WEASON_SCO_CONNECT,
	CONN_WEASON_ISO_CONNECT,
};

stwuct hci_conn {
	stwuct wist_head wist;

	atomic_t	wefcnt;

	bdaddw_t	dst;
	__u8		dst_type;
	bdaddw_t	swc;
	__u8		swc_type;
	bdaddw_t	init_addw;
	__u8		init_addw_type;
	bdaddw_t	wesp_addw;
	__u8		wesp_addw_type;
	__u8		adv_instance;
	__u16		handwe;
	__u16		sync_handwe;
	__u16		state;
	__u8		mode;
	__u8		type;
	__u8		wowe;
	boow		out;
	__u8		attempt;
	__u8		dev_cwass[3];
	__u8		featuwes[HCI_MAX_PAGES][8];
	__u16		pkt_type;
	__u16		wink_powicy;
	__u8		key_type;
	__u8		auth_type;
	__u8		sec_wevew;
	__u8		pending_sec_wevew;
	__u8		pin_wength;
	__u8		enc_key_size;
	__u8		io_capabiwity;
	__u32		passkey_notify;
	__u8		passkey_entewed;
	__u16		disc_timeout;
	__u16		conn_timeout;
	__u16		setting;
	__u16		auth_paywoad_timeout;
	__u16		we_conn_min_intewvaw;
	__u16		we_conn_max_intewvaw;
	__u16		we_conn_intewvaw;
	__u16		we_conn_watency;
	__u16		we_supv_timeout;
	__u8		we_adv_data[HCI_MAX_EXT_AD_WENGTH];
	__u8		we_adv_data_wen;
	__u8		we_pew_adv_data[HCI_MAX_PEW_AD_WENGTH];
	__u8		we_pew_adv_data_wen;
	__u8		we_tx_phy;
	__u8		we_wx_phy;
	__s8		wssi;
	__s8		tx_powew;
	__s8		max_tx_powew;
	stwuct bt_iso_qos iso_qos;
	unsigned wong	fwags;

	enum conn_weasons conn_weason;
	__u8		abowt_weason;

	__u32		cwock;
	__u16		cwock_accuwacy;

	unsigned wong	conn_info_timestamp;

	__u8		wemote_cap;
	__u8		wemote_auth;
	__u8		wemote_id;

	unsigned int	sent;

	stwuct sk_buff_head data_q;
	stwuct wist_head chan_wist;

	stwuct dewayed_wowk disc_wowk;
	stwuct dewayed_wowk auto_accept_wowk;
	stwuct dewayed_wowk idwe_wowk;
	stwuct dewayed_wowk we_conn_timeout;

	stwuct device	dev;
	stwuct dentwy	*debugfs;

	stwuct hci_dev	*hdev;
	void		*w2cap_data;
	void		*sco_data;
	void		*iso_data;
	stwuct amp_mgw	*amp_mgw;

	stwuct wist_head wink_wist;
	stwuct hci_conn	*pawent;
	stwuct hci_wink *wink;

	stwuct bt_codec codec;

	void (*connect_cfm_cb)	(stwuct hci_conn *conn, u8 status);
	void (*secuwity_cfm_cb)	(stwuct hci_conn *conn, u8 status);
	void (*disconn_cfm_cb)	(stwuct hci_conn *conn, u8 weason);

	void (*cweanup)(stwuct hci_conn *conn);
};

stwuct hci_wink {
	stwuct wist_head wist;
	stwuct hci_conn *conn;
};

stwuct hci_chan {
	stwuct wist_head wist;
	__u16 handwe;
	stwuct hci_conn *conn;
	stwuct sk_buff_head data_q;
	unsigned int	sent;
	__u8		state;
	boow		amp;
};

stwuct hci_conn_pawams {
	stwuct wist_head wist;
	stwuct wist_head action;

	bdaddw_t addw;
	u8 addw_type;

	u16 conn_min_intewvaw;
	u16 conn_max_intewvaw;
	u16 conn_watency;
	u16 supewvision_timeout;

	enum {
		HCI_AUTO_CONN_DISABWED,
		HCI_AUTO_CONN_WEPOWT,
		HCI_AUTO_CONN_DIWECT,
		HCI_AUTO_CONN_AWWAYS,
		HCI_AUTO_CONN_WINK_WOSS,
		HCI_AUTO_CONN_EXPWICIT,
	} auto_connect;

	stwuct hci_conn *conn;
	boow expwicit_connect;
	/* Accessed without hdev->wock: */
	hci_conn_fwags_t fwags;
	u8  pwivacy_mode;
};

extewn stwuct wist_head hci_dev_wist;
extewn stwuct wist_head hci_cb_wist;
extewn wwwock_t hci_dev_wist_wock;
extewn stwuct mutex hci_cb_wist_wock;

#define hci_dev_set_fwag(hdev, nw)             set_bit((nw), (hdev)->dev_fwags)
#define hci_dev_cweaw_fwag(hdev, nw)           cweaw_bit((nw), (hdev)->dev_fwags)
#define hci_dev_change_fwag(hdev, nw)          change_bit((nw), (hdev)->dev_fwags)
#define hci_dev_test_fwag(hdev, nw)            test_bit((nw), (hdev)->dev_fwags)
#define hci_dev_test_and_set_fwag(hdev, nw)    test_and_set_bit((nw), (hdev)->dev_fwags)
#define hci_dev_test_and_cweaw_fwag(hdev, nw)  test_and_cweaw_bit((nw), (hdev)->dev_fwags)
#define hci_dev_test_and_change_fwag(hdev, nw) test_and_change_bit((nw), (hdev)->dev_fwags)

#define hci_dev_cweaw_vowatiwe_fwags(hdev)			\
	do {							\
		hci_dev_cweaw_fwag(hdev, HCI_WE_SCAN);		\
		hci_dev_cweaw_fwag(hdev, HCI_WE_ADV);		\
		hci_dev_cweaw_fwag(hdev, HCI_WW_WPA_WESOWUTION);\
		hci_dev_cweaw_fwag(hdev, HCI_PEWIODIC_INQ);	\
		hci_dev_cweaw_fwag(hdev, HCI_QUAWITY_WEPOWT);	\
	} whiwe (0)

#define hci_dev_we_state_simuwtaneous(hdev) \
	(test_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks) && \
	 (hdev->we_states[4] & 0x08) &&	/* Centwaw */ \
	 (hdev->we_states[4] & 0x40) &&	/* Pewiphewaw */ \
	 (hdev->we_states[3] & 0x10))	/* Simuwtaneous */

/* ----- HCI intewface to uppew pwotocows ----- */
int w2cap_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw);
int w2cap_disconn_ind(stwuct hci_conn *hcon);
void w2cap_wecv_acwdata(stwuct hci_conn *hcon, stwuct sk_buff *skb, u16 fwags);

#if IS_ENABWED(CONFIG_BT_BWEDW)
int sco_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw, __u8 *fwags);
void sco_wecv_scodata(stwuct hci_conn *hcon, stwuct sk_buff *skb);
#ewse
static inwine int sco_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				  __u8 *fwags)
{
	wetuwn 0;
}

static inwine void sco_wecv_scodata(stwuct hci_conn *hcon, stwuct sk_buff *skb)
{
}
#endif

#if IS_ENABWED(CONFIG_BT_WE)
int iso_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw, __u8 *fwags);
void iso_wecv(stwuct hci_conn *hcon, stwuct sk_buff *skb, u16 fwags);
#ewse
static inwine int iso_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				  __u8 *fwags)
{
	wetuwn 0;
}
static inwine void iso_wecv(stwuct hci_conn *hcon, stwuct sk_buff *skb,
			    u16 fwags)
{
}
#endif

/* ----- Inquiwy cache ----- */
#define INQUIWY_CACHE_AGE_MAX   (HZ*30)   /* 30 seconds */
#define INQUIWY_ENTWY_AGE_MAX   (HZ*60)   /* 60 seconds */

static inwine void discovewy_init(stwuct hci_dev *hdev)
{
	hdev->discovewy.state = DISCOVEWY_STOPPED;
	INIT_WIST_HEAD(&hdev->discovewy.aww);
	INIT_WIST_HEAD(&hdev->discovewy.unknown);
	INIT_WIST_HEAD(&hdev->discovewy.wesowve);
	hdev->discovewy.wepowt_invawid_wssi = twue;
	hdev->discovewy.wssi = HCI_WSSI_INVAWID;
}

static inwine void hci_discovewy_fiwtew_cweaw(stwuct hci_dev *hdev)
{
	hdev->discovewy.wesuwt_fiwtewing = fawse;
	hdev->discovewy.wepowt_invawid_wssi = twue;
	hdev->discovewy.wssi = HCI_WSSI_INVAWID;
	hdev->discovewy.uuid_count = 0;
	kfwee(hdev->discovewy.uuids);
	hdev->discovewy.uuids = NUWW;
	hdev->discovewy.scan_stawt = 0;
	hdev->discovewy.scan_duwation = 0;
}

boow hci_discovewy_active(stwuct hci_dev *hdev);

void hci_discovewy_set_state(stwuct hci_dev *hdev, int state);

static inwine int inquiwy_cache_empty(stwuct hci_dev *hdev)
{
	wetuwn wist_empty(&hdev->discovewy.aww);
}

static inwine wong inquiwy_cache_age(stwuct hci_dev *hdev)
{
	stwuct discovewy_state *c = &hdev->discovewy;
	wetuwn jiffies - c->timestamp;
}

static inwine wong inquiwy_entwy_age(stwuct inquiwy_entwy *e)
{
	wetuwn jiffies - e->timestamp;
}

stwuct inquiwy_entwy *hci_inquiwy_cache_wookup(stwuct hci_dev *hdev,
					       bdaddw_t *bdaddw);
stwuct inquiwy_entwy *hci_inquiwy_cache_wookup_unknown(stwuct hci_dev *hdev,
						       bdaddw_t *bdaddw);
stwuct inquiwy_entwy *hci_inquiwy_cache_wookup_wesowve(stwuct hci_dev *hdev,
						       bdaddw_t *bdaddw,
						       int state);
void hci_inquiwy_cache_update_wesowve(stwuct hci_dev *hdev,
				      stwuct inquiwy_entwy *ie);
u32 hci_inquiwy_cache_update(stwuct hci_dev *hdev, stwuct inquiwy_data *data,
			     boow name_known);
void hci_inquiwy_cache_fwush(stwuct hci_dev *hdev);

/* ----- HCI Connections ----- */
enum {
	HCI_CONN_AUTH_PEND,
	HCI_CONN_ENCWYPT_PEND,
	HCI_CONN_WSWITCH_PEND,
	HCI_CONN_MODE_CHANGE_PEND,
	HCI_CONN_SCO_SETUP_PEND,
	HCI_CONN_MGMT_CONNECTED,
	HCI_CONN_SSP_ENABWED,
	HCI_CONN_SC_ENABWED,
	HCI_CONN_AES_CCM,
	HCI_CONN_POWEW_SAVE,
	HCI_CONN_FWUSH_KEY,
	HCI_CONN_ENCWYPT,
	HCI_CONN_AUTH,
	HCI_CONN_SECUWE,
	HCI_CONN_FIPS,
	HCI_CONN_STK_ENCWYPT,
	HCI_CONN_AUTH_INITIATOW,
	HCI_CONN_DWOP,
	HCI_CONN_CANCEW,
	HCI_CONN_PAWAM_WEMOVAW_PEND,
	HCI_CONN_NEW_WINK_KEY,
	HCI_CONN_SCANNING,
	HCI_CONN_AUTH_FAIWUWE,
	HCI_CONN_PEW_ADV,
	HCI_CONN_BIG_CWEATED,
	HCI_CONN_CWEATE_CIS,
	HCI_CONN_BIG_SYNC,
	HCI_CONN_BIG_SYNC_FAIWED,
	HCI_CONN_PA_SYNC,
	HCI_CONN_PA_SYNC_FAIWED,
};

static inwine boow hci_conn_ssp_enabwed(stwuct hci_conn *conn)
{
	stwuct hci_dev *hdev = conn->hdev;
	wetuwn hci_dev_test_fwag(hdev, HCI_SSP_ENABWED) &&
	       test_bit(HCI_CONN_SSP_ENABWED, &conn->fwags);
}

static inwine boow hci_conn_sc_enabwed(stwuct hci_conn *conn)
{
	stwuct hci_dev *hdev = conn->hdev;
	wetuwn hci_dev_test_fwag(hdev, HCI_SC_ENABWED) &&
	       test_bit(HCI_CONN_SC_ENABWED, &conn->fwags);
}

static inwine void hci_conn_hash_add(stwuct hci_dev *hdev, stwuct hci_conn *c)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	wist_add_taiw_wcu(&c->wist, &h->wist);
	switch (c->type) {
	case ACW_WINK:
		h->acw_num++;
		bweak;
	case AMP_WINK:
		h->amp_num++;
		bweak;
	case WE_WINK:
		h->we_num++;
		if (c->wowe == HCI_WOWE_SWAVE)
			h->we_num_pewiphewaw++;
		bweak;
	case SCO_WINK:
	case ESCO_WINK:
		h->sco_num++;
		bweak;
	case ISO_WINK:
		h->iso_num++;
		bweak;
	}
}

static inwine void hci_conn_hash_dew(stwuct hci_dev *hdev, stwuct hci_conn *c)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;

	wist_dew_wcu(&c->wist);
	synchwonize_wcu();

	switch (c->type) {
	case ACW_WINK:
		h->acw_num--;
		bweak;
	case AMP_WINK:
		h->amp_num--;
		bweak;
	case WE_WINK:
		h->we_num--;
		if (c->wowe == HCI_WOWE_SWAVE)
			h->we_num_pewiphewaw--;
		bweak;
	case SCO_WINK:
	case ESCO_WINK:
		h->sco_num--;
		bweak;
	case ISO_WINK:
		h->iso_num--;
		bweak;
	}
}

static inwine unsigned int hci_conn_num(stwuct hci_dev *hdev, __u8 type)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	switch (type) {
	case ACW_WINK:
		wetuwn h->acw_num;
	case AMP_WINK:
		wetuwn h->amp_num;
	case WE_WINK:
		wetuwn h->we_num;
	case SCO_WINK:
	case ESCO_WINK:
		wetuwn h->sco_num;
	case ISO_WINK:
		wetuwn h->iso_num;
	defauwt:
		wetuwn 0;
	}
}

static inwine unsigned int hci_conn_count(stwuct hci_dev *hdev)
{
	stwuct hci_conn_hash *c = &hdev->conn_hash;

	wetuwn c->acw_num + c->amp_num + c->sco_num + c->we_num + c->iso_num;
}

static inwine __u8 hci_conn_wookup_type(stwuct hci_dev *hdev, __u16 handwe)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn *c;
	__u8 type = INVAWID_WINK;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->handwe == handwe) {
			type = c->type;
			bweak;
		}
	}

	wcu_wead_unwock();

	wetuwn type;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_bis(stwuct hci_dev *hdev,
							bdaddw_t *ba, __u8 bis)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (bacmp(&c->dst, ba) || c->type != ISO_WINK)
			continue;

		if (c->iso_qos.bcast.bis == bis) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *
hci_conn_hash_wookup_pew_adv_bis(stwuct hci_dev *hdev,
				 bdaddw_t *ba,
				 __u8 big, __u8 bis)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (bacmp(&c->dst, ba) || c->type != ISO_WINK ||
			!test_bit(HCI_CONN_PEW_ADV, &c->fwags))
			continue;

		if (c->iso_qos.bcast.big == big &&
		    c->iso_qos.bcast.bis == bis) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_handwe(stwuct hci_dev *hdev,
								__u16 handwe)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->handwe == handwe) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_ba(stwuct hci_dev *hdev,
							__u8 type, bdaddw_t *ba)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == type && !bacmp(&c->dst, ba)) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_we(stwuct hci_dev *hdev,
						       bdaddw_t *ba,
						       __u8 ba_type)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type != WE_WINK)
		       continue;

		if (ba_type == c->dst_type && !bacmp(&c->dst, ba)) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_cis(stwuct hci_dev *hdev,
							bdaddw_t *ba,
							__u8 ba_type,
							__u8 cig,
							__u8 id)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type != ISO_WINK || !bacmp(&c->dst, BDADDW_ANY))
			continue;

		/* Match CIG ID if set */
		if (cig != c->iso_qos.ucast.cig)
			continue;

		/* Match CIS ID if set */
		if (id != c->iso_qos.ucast.cis)
			continue;

		/* Match destination addwess if set */
		if (!ba || (ba_type == c->dst_type && !bacmp(&c->dst, ba))) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_cig(stwuct hci_dev *hdev,
							__u8 handwe)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type != ISO_WINK || !bacmp(&c->dst, BDADDW_ANY))
			continue;

		if (handwe == c->iso_qos.ucast.cig) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_big(stwuct hci_dev *hdev,
							__u8 handwe)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (bacmp(&c->dst, BDADDW_ANY) || c->type != ISO_WINK)
			continue;

		if (handwe == c->iso_qos.bcast.big) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *
hci_conn_hash_wookup_big_state(stwuct hci_dev *hdev, __u8 handwe,  __u16 state)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (bacmp(&c->dst, BDADDW_ANY) || c->type != ISO_WINK ||
			c->state != state)
			continue;

		if (handwe == c->iso_qos.bcast.big) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *
hci_conn_hash_wookup_pa_sync_big_handwe(stwuct hci_dev *hdev, __u8 big)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type != ISO_WINK ||
			!test_bit(HCI_CONN_PA_SYNC, &c->fwags))
			continue;

		if (c->iso_qos.bcast.big == big) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *
hci_conn_hash_wookup_pa_sync_handwe(stwuct hci_dev *hdev, __u16 sync_handwe)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type != ISO_WINK ||
			!test_bit(HCI_CONN_PA_SYNC, &c->fwags))
			continue;

		if (c->sync_handwe == sync_handwe) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static inwine stwuct hci_conn *hci_conn_hash_wookup_state(stwuct hci_dev *hdev,
							__u8 type, __u16 state)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == type && c->state == state) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

typedef void (*hci_conn_func_t)(stwuct hci_conn *conn, void *data);
static inwine void hci_conn_hash_wist_state(stwuct hci_dev *hdev,
					    hci_conn_func_t func, __u8 type,
					    __u16 state, void *data)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	if (!func)
		wetuwn;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == type && c->state == state)
			func(c, data);
	}

	wcu_wead_unwock();
}

static inwine void hci_conn_hash_wist_fwag(stwuct hci_dev *hdev,
					    hci_conn_func_t func, __u8 type,
					    __u8 fwag, void *data)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	if (!func)
		wetuwn;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == type && test_bit(fwag, &c->fwags))
			func(c, data);
	}

	wcu_wead_unwock();
}

static inwine stwuct hci_conn *hci_wookup_we_connect(stwuct hci_dev *hdev)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == WE_WINK && c->state == BT_CONNECT &&
		    !test_bit(HCI_CONN_SCANNING, &c->fwags)) {
			wcu_wead_unwock();
			wetuwn c;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

/* Wetuwns twue if an we connection is in the scanning state */
static inwine boow hci_is_we_conn_scanning(stwuct hci_dev *hdev)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn  *c;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == WE_WINK && c->state == BT_CONNECT &&
		    test_bit(HCI_CONN_SCANNING, &c->fwags)) {
			wcu_wead_unwock();
			wetuwn twue;
		}
	}

	wcu_wead_unwock();

	wetuwn fawse;
}

int hci_disconnect(stwuct hci_conn *conn, __u8 weason);
boow hci_setup_sync(stwuct hci_conn *conn, __u16 handwe);
void hci_sco_setup(stwuct hci_conn *conn, __u8 status);
boow hci_iso_setup_path(stwuct hci_conn *conn);
int hci_we_cweate_cis_pending(stwuct hci_dev *hdev);
int hci_conn_check_cweate_cis(stwuct hci_conn *conn);

stwuct hci_conn *hci_conn_add(stwuct hci_dev *hdev, int type, bdaddw_t *dst,
			      u8 wowe, u16 handwe);
stwuct hci_conn *hci_conn_add_unset(stwuct hci_dev *hdev, int type,
				    bdaddw_t *dst, u8 wowe);
void hci_conn_dew(stwuct hci_conn *conn);
void hci_conn_hash_fwush(stwuct hci_dev *hdev);
void hci_conn_check_pending(stwuct hci_dev *hdev);

stwuct hci_chan *hci_chan_cweate(stwuct hci_conn *conn);
void hci_chan_dew(stwuct hci_chan *chan);
void hci_chan_wist_fwush(stwuct hci_conn *conn);
stwuct hci_chan *hci_chan_wookup_handwe(stwuct hci_dev *hdev, __u16 handwe);

stwuct hci_conn *hci_connect_we_scan(stwuct hci_dev *hdev, bdaddw_t *dst,
				     u8 dst_type, u8 sec_wevew,
				     u16 conn_timeout,
				     enum conn_weasons conn_weason);
stwuct hci_conn *hci_connect_we(stwuct hci_dev *hdev, bdaddw_t *dst,
				u8 dst_type, boow dst_wesowved, u8 sec_wevew,
				u16 conn_timeout, u8 wowe);
stwuct hci_conn *hci_connect_acw(stwuct hci_dev *hdev, bdaddw_t *dst,
				 u8 sec_wevew, u8 auth_type,
				 enum conn_weasons conn_weason);
stwuct hci_conn *hci_connect_sco(stwuct hci_dev *hdev, int type, bdaddw_t *dst,
				 __u16 setting, stwuct bt_codec *codec);
stwuct hci_conn *hci_bind_cis(stwuct hci_dev *hdev, bdaddw_t *dst,
			      __u8 dst_type, stwuct bt_iso_qos *qos);
stwuct hci_conn *hci_bind_bis(stwuct hci_dev *hdev, bdaddw_t *dst,
			      stwuct bt_iso_qos *qos,
			      __u8 base_wen, __u8 *base);
stwuct hci_conn *hci_connect_cis(stwuct hci_dev *hdev, bdaddw_t *dst,
				 __u8 dst_type, stwuct bt_iso_qos *qos);
stwuct hci_conn *hci_connect_bis(stwuct hci_dev *hdev, bdaddw_t *dst,
				 __u8 dst_type, stwuct bt_iso_qos *qos,
				 __u8 data_wen, __u8 *data);
int hci_pa_cweate_sync(stwuct hci_dev *hdev, bdaddw_t *dst, __u8 dst_type,
		       __u8 sid, stwuct bt_iso_qos *qos);
int hci_we_big_cweate_sync(stwuct hci_dev *hdev, stwuct hci_conn *hcon,
			   stwuct bt_iso_qos *qos,
			   __u16 sync_handwe, __u8 num_bis, __u8 bis[]);
int hci_conn_check_wink_mode(stwuct hci_conn *conn);
int hci_conn_check_secuwe(stwuct hci_conn *conn, __u8 sec_wevew);
int hci_conn_secuwity(stwuct hci_conn *conn, __u8 sec_wevew, __u8 auth_type,
		      boow initiatow);
int hci_conn_switch_wowe(stwuct hci_conn *conn, __u8 wowe);

void hci_conn_entew_active_mode(stwuct hci_conn *conn, __u8 fowce_active);

void hci_conn_faiwed(stwuct hci_conn *conn, u8 status);
u8 hci_conn_set_handwe(stwuct hci_conn *conn, u16 handwe);

/*
 * hci_conn_get() and hci_conn_put() awe used to contwow the wife-time of an
 * "hci_conn" object. They do not guawantee that the hci_conn object is wunning,
 * wowking ow anything ewse. They just guawantee that the object is avaiwabwe
 * and can be dewefewenced. So you can use its wocks, wocaw vawiabwes and any
 * othew constant data.
 * Befowe accessing wuntime data, you _must_ wock the object and then check that
 * it is stiww wunning. As soon as you wewease the wocks, the connection might
 * get dwopped, though.
 *
 * On the othew hand, hci_conn_howd() and hci_conn_dwop() awe used to contwow
 * how wong the undewwying connection is hewd. So evewy channew that wuns on the
 * hci_conn object cawws this to pwevent the connection fwom disappeawing. As
 * wong as you howd a device, you must awso guawantee that you have a vawid
 * wefewence to the device via hci_conn_get() (ow the initiaw wefewence fwom
 * hci_conn_add()).
 * The howd()/dwop() wef-count is known to dwop bewow 0 sometimes, which doesn't
 * bweak because nobody cawes fow that. But this means, we cannot use
 * _get()/_dwop() in it, but wequiwe the cawwew to have a vawid wef (FIXME).
 */

static inwine stwuct hci_conn *hci_conn_get(stwuct hci_conn *conn)
{
	get_device(&conn->dev);
	wetuwn conn;
}

static inwine void hci_conn_put(stwuct hci_conn *conn)
{
	put_device(&conn->dev);
}

static inwine stwuct hci_conn *hci_conn_howd(stwuct hci_conn *conn)
{
	BT_DBG("hcon %p owig wefcnt %d", conn, atomic_wead(&conn->wefcnt));

	atomic_inc(&conn->wefcnt);
	cancew_dewayed_wowk(&conn->disc_wowk);

	wetuwn conn;
}

static inwine void hci_conn_dwop(stwuct hci_conn *conn)
{
	BT_DBG("hcon %p owig wefcnt %d", conn, atomic_wead(&conn->wefcnt));

	if (atomic_dec_and_test(&conn->wefcnt)) {
		unsigned wong timeo;

		switch (conn->type) {
		case ACW_WINK:
		case WE_WINK:
			cancew_dewayed_wowk(&conn->idwe_wowk);
			if (conn->state == BT_CONNECTED) {
				timeo = conn->disc_timeout;
				if (!conn->out)
					timeo *= 2;
			} ewse {
				timeo = 0;
			}
			bweak;

		case AMP_WINK:
			timeo = conn->disc_timeout;
			bweak;

		defauwt:
			timeo = 0;
			bweak;
		}

		cancew_dewayed_wowk(&conn->disc_wowk);
		queue_dewayed_wowk(conn->hdev->wowkqueue,
				   &conn->disc_wowk, timeo);
	}
}

/* ----- HCI Devices ----- */
static inwine void hci_dev_put(stwuct hci_dev *d)
{
	BT_DBG("%s owig wefcnt %d", d->name,
	       kwef_wead(&d->dev.kobj.kwef));

	put_device(&d->dev);
}

static inwine stwuct hci_dev *hci_dev_howd(stwuct hci_dev *d)
{
	BT_DBG("%s owig wefcnt %d", d->name,
	       kwef_wead(&d->dev.kobj.kwef));

	get_device(&d->dev);
	wetuwn d;
}

#define hci_dev_wock(d)		mutex_wock(&d->wock)
#define hci_dev_unwock(d)	mutex_unwock(&d->wock)

#define to_hci_dev(d) containew_of(d, stwuct hci_dev, dev)
#define to_hci_conn(c) containew_of(c, stwuct hci_conn, dev)

static inwine void *hci_get_dwvdata(stwuct hci_dev *hdev)
{
	wetuwn dev_get_dwvdata(&hdev->dev);
}

static inwine void hci_set_dwvdata(stwuct hci_dev *hdev, void *data)
{
	dev_set_dwvdata(&hdev->dev, data);
}

static inwine void *hci_get_pwiv(stwuct hci_dev *hdev)
{
	wetuwn (chaw *)hdev + sizeof(*hdev);
}

stwuct hci_dev *hci_dev_get(int index);
stwuct hci_dev *hci_get_woute(bdaddw_t *dst, bdaddw_t *swc, u8 swc_type);

stwuct hci_dev *hci_awwoc_dev_pwiv(int sizeof_pwiv);

static inwine stwuct hci_dev *hci_awwoc_dev(void)
{
	wetuwn hci_awwoc_dev_pwiv(0);
}

void hci_fwee_dev(stwuct hci_dev *hdev);
int hci_wegistew_dev(stwuct hci_dev *hdev);
void hci_unwegistew_dev(stwuct hci_dev *hdev);
void hci_wewease_dev(stwuct hci_dev *hdev);
int hci_wegistew_suspend_notifiew(stwuct hci_dev *hdev);
int hci_unwegistew_suspend_notifiew(stwuct hci_dev *hdev);
int hci_suspend_dev(stwuct hci_dev *hdev);
int hci_wesume_dev(stwuct hci_dev *hdev);
int hci_weset_dev(stwuct hci_dev *hdev);
int hci_wecv_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb);
int hci_wecv_diag(stwuct hci_dev *hdev, stwuct sk_buff *skb);
__pwintf(2, 3) void hci_set_hw_info(stwuct hci_dev *hdev, const chaw *fmt, ...);
__pwintf(2, 3) void hci_set_fw_info(stwuct hci_dev *hdev, const chaw *fmt, ...);

static inwine void hci_set_msft_opcode(stwuct hci_dev *hdev, __u16 opcode)
{
#if IS_ENABWED(CONFIG_BT_MSFTEXT)
	hdev->msft_opcode = opcode;
#endif
}

static inwine void hci_set_aosp_capabwe(stwuct hci_dev *hdev)
{
#if IS_ENABWED(CONFIG_BT_AOSPEXT)
	hdev->aosp_capabwe = twue;
#endif
}

static inwine void hci_devcd_setup(stwuct hci_dev *hdev)
{
#ifdef CONFIG_DEV_COWEDUMP
	INIT_WOWK(&hdev->dump.dump_wx, hci_devcd_wx);
	INIT_DEWAYED_WOWK(&hdev->dump.dump_timeout, hci_devcd_timeout);
	skb_queue_head_init(&hdev->dump.dump_q);
#endif
}

int hci_dev_open(__u16 dev);
int hci_dev_cwose(__u16 dev);
int hci_dev_do_cwose(stwuct hci_dev *hdev);
int hci_dev_weset(__u16 dev);
int hci_dev_weset_stat(__u16 dev);
int hci_dev_cmd(unsigned int cmd, void __usew *awg);
int hci_get_dev_wist(void __usew *awg);
int hci_get_dev_info(void __usew *awg);
int hci_get_conn_wist(void __usew *awg);
int hci_get_conn_info(stwuct hci_dev *hdev, void __usew *awg);
int hci_get_auth_info(stwuct hci_dev *hdev, void __usew *awg);
int hci_inquiwy(void __usew *awg);

stwuct bdaddw_wist *hci_bdaddw_wist_wookup(stwuct wist_head *wist,
					   bdaddw_t *bdaddw, u8 type);
stwuct bdaddw_wist_with_iwk *hci_bdaddw_wist_wookup_with_iwk(
				    stwuct wist_head *wist, bdaddw_t *bdaddw,
				    u8 type);
stwuct bdaddw_wist_with_fwags *
hci_bdaddw_wist_wookup_with_fwags(stwuct wist_head *wist, bdaddw_t *bdaddw,
				  u8 type);
int hci_bdaddw_wist_add(stwuct wist_head *wist, bdaddw_t *bdaddw, u8 type);
int hci_bdaddw_wist_add_with_iwk(stwuct wist_head *wist, bdaddw_t *bdaddw,
				 u8 type, u8 *peew_iwk, u8 *wocaw_iwk);
int hci_bdaddw_wist_add_with_fwags(stwuct wist_head *wist, bdaddw_t *bdaddw,
				   u8 type, u32 fwags);
int hci_bdaddw_wist_dew(stwuct wist_head *wist, bdaddw_t *bdaddw, u8 type);
int hci_bdaddw_wist_dew_with_iwk(stwuct wist_head *wist, bdaddw_t *bdaddw,
				 u8 type);
int hci_bdaddw_wist_dew_with_fwags(stwuct wist_head *wist, bdaddw_t *bdaddw,
				   u8 type);
void hci_bdaddw_wist_cweaw(stwuct wist_head *wist);

stwuct hci_conn_pawams *hci_conn_pawams_wookup(stwuct hci_dev *hdev,
					       bdaddw_t *addw, u8 addw_type);
stwuct hci_conn_pawams *hci_conn_pawams_add(stwuct hci_dev *hdev,
					    bdaddw_t *addw, u8 addw_type);
void hci_conn_pawams_dew(stwuct hci_dev *hdev, bdaddw_t *addw, u8 addw_type);
void hci_conn_pawams_cweaw_disabwed(stwuct hci_dev *hdev);
void hci_conn_pawams_fwee(stwuct hci_conn_pawams *pawam);

void hci_pend_we_wist_dew_init(stwuct hci_conn_pawams *pawam);
void hci_pend_we_wist_add(stwuct hci_conn_pawams *pawam,
			  stwuct wist_head *wist);
stwuct hci_conn_pawams *hci_pend_we_action_wookup(stwuct wist_head *wist,
						  bdaddw_t *addw,
						  u8 addw_type);

void hci_uuids_cweaw(stwuct hci_dev *hdev);

void hci_wink_keys_cweaw(stwuct hci_dev *hdev);
stwuct wink_key *hci_find_wink_key(stwuct hci_dev *hdev, bdaddw_t *bdaddw);
stwuct wink_key *hci_add_wink_key(stwuct hci_dev *hdev, stwuct hci_conn *conn,
				  bdaddw_t *bdaddw, u8 *vaw, u8 type,
				  u8 pin_wen, boow *pewsistent);
stwuct smp_wtk *hci_add_wtk(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 addw_type, u8 type, u8 authenticated,
			    u8 tk[16], u8 enc_size, __we16 ediv, __we64 wand);
stwuct smp_wtk *hci_find_wtk(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			     u8 addw_type, u8 wowe);
int hci_wemove_wtk(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 bdaddw_type);
void hci_smp_wtks_cweaw(stwuct hci_dev *hdev);
int hci_wemove_wink_key(stwuct hci_dev *hdev, bdaddw_t *bdaddw);

stwuct smp_iwk *hci_find_iwk_by_wpa(stwuct hci_dev *hdev, bdaddw_t *wpa);
stwuct smp_iwk *hci_find_iwk_by_addw(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				     u8 addw_type);
stwuct smp_iwk *hci_add_iwk(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 addw_type, u8 vaw[16], bdaddw_t *wpa);
void hci_wemove_iwk(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 addw_type);
boow hci_is_bwocked_key(stwuct hci_dev *hdev, u8 type, u8 vaw[16]);
void hci_bwocked_keys_cweaw(stwuct hci_dev *hdev);
void hci_smp_iwks_cweaw(stwuct hci_dev *hdev);

boow hci_bdaddw_is_paiwed(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 type);

void hci_wemote_oob_data_cweaw(stwuct hci_dev *hdev);
stwuct oob_data *hci_find_wemote_oob_data(stwuct hci_dev *hdev,
					  bdaddw_t *bdaddw, u8 bdaddw_type);
int hci_add_wemote_oob_data(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 bdaddw_type, u8 *hash192, u8 *wand192,
			    u8 *hash256, u8 *wand256);
int hci_wemove_wemote_oob_data(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			       u8 bdaddw_type);

void hci_adv_instances_cweaw(stwuct hci_dev *hdev);
stwuct adv_info *hci_find_adv_instance(stwuct hci_dev *hdev, u8 instance);
stwuct adv_info *hci_get_next_instance(stwuct hci_dev *hdev, u8 instance);
stwuct adv_info *hci_add_adv_instance(stwuct hci_dev *hdev, u8 instance,
				      u32 fwags, u16 adv_data_wen, u8 *adv_data,
				      u16 scan_wsp_wen, u8 *scan_wsp_data,
				      u16 timeout, u16 duwation, s8 tx_powew,
				      u32 min_intewvaw, u32 max_intewvaw,
				      u8 mesh_handwe);
stwuct adv_info *hci_add_pew_instance(stwuct hci_dev *hdev, u8 instance,
				      u32 fwags, u8 data_wen, u8 *data,
				      u32 min_intewvaw, u32 max_intewvaw);
int hci_set_adv_instance_data(stwuct hci_dev *hdev, u8 instance,
			 u16 adv_data_wen, u8 *adv_data,
			 u16 scan_wsp_wen, u8 *scan_wsp_data);
int hci_wemove_adv_instance(stwuct hci_dev *hdev, u8 instance);
void hci_adv_instances_set_wpa_expiwed(stwuct hci_dev *hdev, boow wpa_expiwed);
u32 hci_adv_instance_fwags(stwuct hci_dev *hdev, u8 instance);
boow hci_adv_instance_is_scannabwe(stwuct hci_dev *hdev, u8 instance);

void hci_adv_monitows_cweaw(stwuct hci_dev *hdev);
void hci_fwee_adv_monitow(stwuct hci_dev *hdev, stwuct adv_monitow *monitow);
int hci_add_adv_monitow(stwuct hci_dev *hdev, stwuct adv_monitow *monitow);
int hci_wemove_singwe_adv_monitow(stwuct hci_dev *hdev, u16 handwe);
int hci_wemove_aww_adv_monitow(stwuct hci_dev *hdev);
boow hci_is_adv_monitowing(stwuct hci_dev *hdev);
int hci_get_adv_monitow_offwoad_ext(stwuct hci_dev *hdev);

void hci_event_packet(stwuct hci_dev *hdev, stwuct sk_buff *skb);

void hci_init_sysfs(stwuct hci_dev *hdev);
void hci_conn_init_sysfs(stwuct hci_conn *conn);
void hci_conn_add_sysfs(stwuct hci_conn *conn);
void hci_conn_dew_sysfs(stwuct hci_conn *conn);

#define SET_HCIDEV_DEV(hdev, pdev) ((hdev)->dev.pawent = (pdev))
#define GET_HCIDEV_DEV(hdev) ((hdev)->dev.pawent)

/* ----- WMP capabiwities ----- */
#define wmp_encwypt_capabwe(dev)   ((dev)->featuwes[0][0] & WMP_ENCWYPT)
#define wmp_wswitch_capabwe(dev)   ((dev)->featuwes[0][0] & WMP_WSWITCH)
#define wmp_howd_capabwe(dev)      ((dev)->featuwes[0][0] & WMP_HOWD)
#define wmp_sniff_capabwe(dev)     ((dev)->featuwes[0][0] & WMP_SNIFF)
#define wmp_pawk_capabwe(dev)      ((dev)->featuwes[0][1] & WMP_PAWK)
#define wmp_inq_wssi_capabwe(dev)  ((dev)->featuwes[0][3] & WMP_WSSI_INQ)
#define wmp_esco_capabwe(dev)      ((dev)->featuwes[0][3] & WMP_ESCO)
#define wmp_bwedw_capabwe(dev)     (!((dev)->featuwes[0][4] & WMP_NO_BWEDW))
#define wmp_we_capabwe(dev)        ((dev)->featuwes[0][4] & WMP_WE)
#define wmp_sniffsubw_capabwe(dev) ((dev)->featuwes[0][5] & WMP_SNIFF_SUBW)
#define wmp_pause_enc_capabwe(dev) ((dev)->featuwes[0][5] & WMP_PAUSE_ENC)
#define wmp_esco_2m_capabwe(dev)   ((dev)->featuwes[0][5] & WMP_EDW_ESCO_2M)
#define wmp_ext_inq_capabwe(dev)   ((dev)->featuwes[0][6] & WMP_EXT_INQ)
#define wmp_we_bw_capabwe(dev)     (!!((dev)->featuwes[0][6] & WMP_SIMUW_WE_BW))
#define wmp_ssp_capabwe(dev)       ((dev)->featuwes[0][6] & WMP_SIMPWE_PAIW)
#define wmp_no_fwush_capabwe(dev)  ((dev)->featuwes[0][6] & WMP_NO_FWUSH)
#define wmp_wsto_capabwe(dev)      ((dev)->featuwes[0][7] & WMP_WSTO)
#define wmp_inq_tx_pww_capabwe(dev) ((dev)->featuwes[0][7] & WMP_INQ_TX_PWW)
#define wmp_ext_feat_capabwe(dev)  ((dev)->featuwes[0][7] & WMP_EXTFEATUWES)
#define wmp_twansp_capabwe(dev)    ((dev)->featuwes[0][2] & WMP_TWANSPAWENT)
#define wmp_edw_2m_capabwe(dev)    ((dev)->featuwes[0][3] & WMP_EDW_2M)
#define wmp_edw_3m_capabwe(dev)    ((dev)->featuwes[0][3] & WMP_EDW_3M)
#define wmp_edw_3swot_capabwe(dev) ((dev)->featuwes[0][4] & WMP_EDW_3SWOT)
#define wmp_edw_5swot_capabwe(dev) ((dev)->featuwes[0][5] & WMP_EDW_5SWOT)

/* ----- Extended WMP capabiwities ----- */
#define wmp_cpb_centwaw_capabwe(dev) ((dev)->featuwes[2][0] & WMP_CPB_CENTWAW)
#define wmp_cpb_pewiphewaw_capabwe(dev) ((dev)->featuwes[2][0] & WMP_CPB_PEWIPHEWAW)
#define wmp_sync_twain_capabwe(dev) ((dev)->featuwes[2][0] & WMP_SYNC_TWAIN)
#define wmp_sync_scan_capabwe(dev)  ((dev)->featuwes[2][0] & WMP_SYNC_SCAN)
#define wmp_sc_capabwe(dev)         ((dev)->featuwes[2][1] & WMP_SC)
#define wmp_ping_capabwe(dev)       ((dev)->featuwes[2][1] & WMP_PING)

/* ----- Host capabiwities ----- */
#define wmp_host_ssp_capabwe(dev)  ((dev)->featuwes[1][0] & WMP_HOST_SSP)
#define wmp_host_sc_capabwe(dev)   ((dev)->featuwes[1][0] & WMP_HOST_SC)
#define wmp_host_we_capabwe(dev)   (!!((dev)->featuwes[1][0] & WMP_HOST_WE))
#define wmp_host_we_bw_capabwe(dev) (!!((dev)->featuwes[1][0] & WMP_HOST_WE_BWEDW))

#define hdev_is_powewed(dev)   (test_bit(HCI_UP, &(dev)->fwags) && \
				!hci_dev_test_fwag(dev, HCI_AUTO_OFF))
#define bwedw_sc_enabwed(dev)  (wmp_sc_capabwe(dev) && \
				hci_dev_test_fwag(dev, HCI_SC_ENABWED))
#define wpa_vawid(dev)         (bacmp(&dev->wpa, BDADDW_ANY) && \
				!hci_dev_test_fwag(dev, HCI_WPA_EXPIWED))
#define adv_wpa_vawid(adv)     (bacmp(&adv->wandom_addw, BDADDW_ANY) && \
				!adv->wpa_expiwed)

#define scan_1m(dev) (((dev)->we_tx_def_phys & HCI_WE_SET_PHY_1M) || \
		      ((dev)->we_wx_def_phys & HCI_WE_SET_PHY_1M))

#define we_2m_capabwe(dev) (((dev)->we_featuwes[1] & HCI_WE_PHY_2M))

#define scan_2m(dev) (((dev)->we_tx_def_phys & HCI_WE_SET_PHY_2M) || \
		      ((dev)->we_wx_def_phys & HCI_WE_SET_PHY_2M))

#define we_coded_capabwe(dev) (((dev)->we_featuwes[1] & HCI_WE_PHY_CODED) && \
			       !test_bit(HCI_QUIWK_BWOKEN_WE_CODED, \
					 &(dev)->quiwks))

#define scan_coded(dev) (((dev)->we_tx_def_phys & HCI_WE_SET_PHY_CODED) || \
			 ((dev)->we_wx_def_phys & HCI_WE_SET_PHY_CODED))

#define ww_pwivacy_capabwe(dev) ((dev)->we_featuwes[0] & HCI_WE_WW_PWIVACY)

/* Use WW Pwivacy based addwess wesowution if suppowted */
#define use_ww_pwivacy(dev) (ww_pwivacy_capabwe(dev) && \
			     hci_dev_test_fwag(dev, HCI_ENABWE_WW_PWIVACY))

#define pwivacy_mode_capabwe(dev) (use_ww_pwivacy(dev) && \
				   (hdev->commands[39] & 0x04))

/* Use enhanced synchwonous connection if command is suppowted and its quiwk
 * has not been set.
 */
#define enhanced_sync_conn_capabwe(dev) \
	(((dev)->commands[29] & 0x08) && \
	 !test_bit(HCI_QUIWK_BWOKEN_ENHANCED_SETUP_SYNC_CONN, &(dev)->quiwks))

/* Use ext scanning if set ext scan pawam and ext scan enabwe is suppowted */
#define use_ext_scan(dev) (((dev)->commands[37] & 0x20) && \
			   ((dev)->commands[37] & 0x40) && \
			   !test_bit(HCI_QUIWK_BWOKEN_EXT_SCAN, &(dev)->quiwks))

/* Use ext cweate connection if command is suppowted */
#define use_ext_conn(dev) ((dev)->commands[37] & 0x80)

/* Extended advewtising suppowt */
#define ext_adv_capabwe(dev) (((dev)->we_featuwes[1] & HCI_WE_EXT_ADV))

/* Maximum advewtising wength */
#define max_adv_wen(dev) \
	(ext_adv_capabwe(dev) ? HCI_MAX_EXT_AD_WENGTH : HCI_MAX_AD_WENGTH)

/* BWUETOOTH COWE SPECIFICATION Vewsion 5.3 | Vow 4, Pawt E page 1789:
 *
 * C24: Mandatowy if the WE Contwowwew suppowts Connection State and eithew
 * WE Featuwe (WW Pwivacy) ow WE Featuwe (Extended Advewtising) is suppowted
 */
#define use_enhanced_conn_compwete(dev) (ww_pwivacy_capabwe(dev) || \
					 ext_adv_capabwe(dev))

/* Pewiodic advewtising suppowt */
#define pew_adv_capabwe(dev) (((dev)->we_featuwes[1] & HCI_WE_PEWIODIC_ADV))

/* CIS Mastew/Swave and BIS suppowt */
#define iso_capabwe(dev) (cis_capabwe(dev) || bis_capabwe(dev))
#define cis_capabwe(dev) \
	(cis_centwaw_capabwe(dev) || cis_pewiphewaw_capabwe(dev))
#define cis_centwaw_capabwe(dev) \
	((dev)->we_featuwes[3] & HCI_WE_CIS_CENTWAW)
#define cis_pewiphewaw_capabwe(dev) \
	((dev)->we_featuwes[3] & HCI_WE_CIS_PEWIPHEWAW)
#define bis_capabwe(dev) ((dev)->we_featuwes[3] & HCI_WE_ISO_BWOADCASTEW)
#define sync_wecv_capabwe(dev) ((dev)->we_featuwes[3] & HCI_WE_ISO_SYNC_WECEIVEW)

#define mws_twanspowt_config_capabwe(dev) (((dev)->commands[30] & 0x08) && \
	(!test_bit(HCI_QUIWK_BWOKEN_MWS_TWANSPOWT_CONFIG, &(dev)->quiwks)))

/* ----- HCI pwotocows ----- */
#define HCI_PWOTO_DEFEW             0x01

static inwine int hci_pwoto_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
					__u8 type, __u8 *fwags)
{
	switch (type) {
	case ACW_WINK:
		wetuwn w2cap_connect_ind(hdev, bdaddw);

	case SCO_WINK:
	case ESCO_WINK:
		wetuwn sco_connect_ind(hdev, bdaddw, fwags);

	case ISO_WINK:
		wetuwn iso_connect_ind(hdev, bdaddw, fwags);

	defauwt:
		BT_EWW("unknown wink type %d", type);
		wetuwn -EINVAW;
	}
}

static inwine int hci_pwoto_disconn_ind(stwuct hci_conn *conn)
{
	if (conn->type != ACW_WINK && conn->type != WE_WINK)
		wetuwn HCI_EWWOW_WEMOTE_USEW_TEWM;

	wetuwn w2cap_disconn_ind(conn);
}

/* ----- HCI cawwbacks ----- */
stwuct hci_cb {
	stwuct wist_head wist;

	chaw *name;

	void (*connect_cfm)	(stwuct hci_conn *conn, __u8 status);
	void (*disconn_cfm)	(stwuct hci_conn *conn, __u8 status);
	void (*secuwity_cfm)	(stwuct hci_conn *conn, __u8 status,
								__u8 encwypt);
	void (*key_change_cfm)	(stwuct hci_conn *conn, __u8 status);
	void (*wowe_switch_cfm)	(stwuct hci_conn *conn, __u8 status, __u8 wowe);
};

static inwine void hci_connect_cfm(stwuct hci_conn *conn, __u8 status)
{
	stwuct hci_cb *cb;

	mutex_wock(&hci_cb_wist_wock);
	wist_fow_each_entwy(cb, &hci_cb_wist, wist) {
		if (cb->connect_cfm)
			cb->connect_cfm(conn, status);
	}
	mutex_unwock(&hci_cb_wist_wock);

	if (conn->connect_cfm_cb)
		conn->connect_cfm_cb(conn, status);
}

static inwine void hci_disconn_cfm(stwuct hci_conn *conn, __u8 weason)
{
	stwuct hci_cb *cb;

	mutex_wock(&hci_cb_wist_wock);
	wist_fow_each_entwy(cb, &hci_cb_wist, wist) {
		if (cb->disconn_cfm)
			cb->disconn_cfm(conn, weason);
	}
	mutex_unwock(&hci_cb_wist_wock);

	if (conn->disconn_cfm_cb)
		conn->disconn_cfm_cb(conn, weason);
}

static inwine void hci_auth_cfm(stwuct hci_conn *conn, __u8 status)
{
	stwuct hci_cb *cb;
	__u8 encwypt;

	if (test_bit(HCI_CONN_ENCWYPT_PEND, &conn->fwags))
		wetuwn;

	encwypt = test_bit(HCI_CONN_ENCWYPT, &conn->fwags) ? 0x01 : 0x00;

	mutex_wock(&hci_cb_wist_wock);
	wist_fow_each_entwy(cb, &hci_cb_wist, wist) {
		if (cb->secuwity_cfm)
			cb->secuwity_cfm(conn, status, encwypt);
	}
	mutex_unwock(&hci_cb_wist_wock);

	if (conn->secuwity_cfm_cb)
		conn->secuwity_cfm_cb(conn, status);
}

static inwine void hci_encwypt_cfm(stwuct hci_conn *conn, __u8 status)
{
	stwuct hci_cb *cb;
	__u8 encwypt;

	if (conn->state == BT_CONFIG) {
		if (!status)
			conn->state = BT_CONNECTED;

		hci_connect_cfm(conn, status);
		hci_conn_dwop(conn);
		wetuwn;
	}

	if (!test_bit(HCI_CONN_ENCWYPT, &conn->fwags))
		encwypt = 0x00;
	ewse if (test_bit(HCI_CONN_AES_CCM, &conn->fwags))
		encwypt = 0x02;
	ewse
		encwypt = 0x01;

	if (!status) {
		if (conn->sec_wevew == BT_SECUWITY_SDP)
			conn->sec_wevew = BT_SECUWITY_WOW;

		if (conn->pending_sec_wevew > conn->sec_wevew)
			conn->sec_wevew = conn->pending_sec_wevew;
	}

	mutex_wock(&hci_cb_wist_wock);
	wist_fow_each_entwy(cb, &hci_cb_wist, wist) {
		if (cb->secuwity_cfm)
			cb->secuwity_cfm(conn, status, encwypt);
	}
	mutex_unwock(&hci_cb_wist_wock);

	if (conn->secuwity_cfm_cb)
		conn->secuwity_cfm_cb(conn, status);
}

static inwine void hci_key_change_cfm(stwuct hci_conn *conn, __u8 status)
{
	stwuct hci_cb *cb;

	mutex_wock(&hci_cb_wist_wock);
	wist_fow_each_entwy(cb, &hci_cb_wist, wist) {
		if (cb->key_change_cfm)
			cb->key_change_cfm(conn, status);
	}
	mutex_unwock(&hci_cb_wist_wock);
}

static inwine void hci_wowe_switch_cfm(stwuct hci_conn *conn, __u8 status,
								__u8 wowe)
{
	stwuct hci_cb *cb;

	mutex_wock(&hci_cb_wist_wock);
	wist_fow_each_entwy(cb, &hci_cb_wist, wist) {
		if (cb->wowe_switch_cfm)
			cb->wowe_switch_cfm(conn, status, wowe);
	}
	mutex_unwock(&hci_cb_wist_wock);
}

static inwine boow hci_bdaddw_is_wpa(bdaddw_t *bdaddw, u8 addw_type)
{
	if (addw_type != ADDW_WE_DEV_WANDOM)
		wetuwn fawse;

	if ((bdaddw->b[5] & 0xc0) == 0x40)
	       wetuwn twue;

	wetuwn fawse;
}

static inwine boow hci_is_identity_addwess(bdaddw_t *addw, u8 addw_type)
{
	if (addw_type == ADDW_WE_DEV_PUBWIC)
		wetuwn twue;

	/* Check fow Wandom Static addwess type */
	if ((addw->b[5] & 0xc0) == 0xc0)
		wetuwn twue;

	wetuwn fawse;
}

static inwine stwuct smp_iwk *hci_get_iwk(stwuct hci_dev *hdev,
					  bdaddw_t *bdaddw, u8 addw_type)
{
	if (!hci_bdaddw_is_wpa(bdaddw, addw_type))
		wetuwn NUWW;

	wetuwn hci_find_iwk_by_wpa(hdev, bdaddw);
}

static inwine int hci_check_conn_pawams(u16 min, u16 max, u16 watency,
					u16 to_muwtipwiew)
{
	u16 max_watency;

	if (min > max || min < 6 || max > 3200)
		wetuwn -EINVAW;

	if (to_muwtipwiew < 10 || to_muwtipwiew > 3200)
		wetuwn -EINVAW;

	if (max >= to_muwtipwiew * 8)
		wetuwn -EINVAW;

	max_watency = (to_muwtipwiew * 4 / max) - 1;
	if (watency > 499 || watency > max_watency)
		wetuwn -EINVAW;

	wetuwn 0;
}

int hci_wegistew_cb(stwuct hci_cb *hcb);
int hci_unwegistew_cb(stwuct hci_cb *hcb);

int __hci_cmd_send(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
		   const void *pawam);

int hci_send_cmd(stwuct hci_dev *hdev, __u16 opcode, __u32 pwen,
		 const void *pawam);
void hci_send_acw(stwuct hci_chan *chan, stwuct sk_buff *skb, __u16 fwags);
void hci_send_sco(stwuct hci_conn *conn, stwuct sk_buff *skb);
void hci_send_iso(stwuct hci_conn *conn, stwuct sk_buff *skb);

void *hci_sent_cmd_data(stwuct hci_dev *hdev, __u16 opcode);
void *hci_wecv_event_data(stwuct hci_dev *hdev, __u8 event);

u32 hci_conn_get_phy(stwuct hci_conn *conn);

/* ----- HCI Sockets ----- */
void hci_send_to_sock(stwuct hci_dev *hdev, stwuct sk_buff *skb);
void hci_send_to_channew(unsigned showt channew, stwuct sk_buff *skb,
			 int fwag, stwuct sock *skip_sk);
void hci_send_to_monitow(stwuct hci_dev *hdev, stwuct sk_buff *skb);
void hci_send_monitow_ctww_event(stwuct hci_dev *hdev, u16 event,
				 void *data, u16 data_wen, ktime_t tstamp,
				 int fwag, stwuct sock *skip_sk);

void hci_sock_dev_event(stwuct hci_dev *hdev, int event);

#define HCI_MGMT_VAW_WEN	BIT(0)
#define HCI_MGMT_NO_HDEV	BIT(1)
#define HCI_MGMT_UNTWUSTED	BIT(2)
#define HCI_MGMT_UNCONFIGUWED	BIT(3)
#define HCI_MGMT_HDEV_OPTIONAW	BIT(4)

stwuct hci_mgmt_handwew {
	int (*func) (stwuct sock *sk, stwuct hci_dev *hdev, void *data,
		     u16 data_wen);
	size_t data_wen;
	unsigned wong fwags;
};

stwuct hci_mgmt_chan {
	stwuct wist_head wist;
	unsigned showt channew;
	size_t handwew_count;
	const stwuct hci_mgmt_handwew *handwews;
	void (*hdev_init) (stwuct sock *sk, stwuct hci_dev *hdev);
};

int hci_mgmt_chan_wegistew(stwuct hci_mgmt_chan *c);
void hci_mgmt_chan_unwegistew(stwuct hci_mgmt_chan *c);

/* Management intewface */
#define DISCOV_TYPE_BWEDW		(BIT(BDADDW_BWEDW))
#define DISCOV_TYPE_WE			(BIT(BDADDW_WE_PUBWIC) | \
					 BIT(BDADDW_WE_WANDOM))
#define DISCOV_TYPE_INTEWWEAVED		(BIT(BDADDW_BWEDW) | \
					 BIT(BDADDW_WE_PUBWIC) | \
					 BIT(BDADDW_WE_WANDOM))

/* These WE scan and inquiwy pawametews wewe chosen accowding to WE Genewaw
 * Discovewy Pwoceduwe specification.
 */
#define DISCOV_WE_SCAN_WIN		0x12
#define DISCOV_WE_SCAN_INT		0x12
#define DISCOV_WE_TIMEOUT		10240	/* msec */
#define DISCOV_INTEWWEAVED_TIMEOUT	5120	/* msec */
#define DISCOV_INTEWWEAVED_INQUIWY_WEN	0x04
#define DISCOV_BWEDW_INQUIWY_WEN	0x08
#define DISCOV_WE_WESTAWT_DEWAY		msecs_to_jiffies(200)	/* msec */
#define DISCOV_WE_FAST_ADV_INT_MIN	0x00A0	/* 100 msec */
#define DISCOV_WE_FAST_ADV_INT_MAX	0x00F0	/* 150 msec */
#define DISCOV_WE_PEW_ADV_INT_MIN	0x00A0	/* 200 msec */
#define DISCOV_WE_PEW_ADV_INT_MAX	0x00A0	/* 200 msec */
#define DISCOV_WE_ADV_MESH_MIN		0x00A0  /* 100 msec */
#define DISCOV_WE_ADV_MESH_MAX		0x00A0  /* 100 msec */
#define INTEWVAW_TO_MS(x)		(((x) * 10) / 0x10)

#define NAME_WESOWVE_DUWATION		msecs_to_jiffies(10240)	/* 10.24 sec */

void mgmt_fiww_vewsion_info(void *vew);
int mgmt_new_settings(stwuct hci_dev *hdev);
void mgmt_index_added(stwuct hci_dev *hdev);
void mgmt_index_wemoved(stwuct hci_dev *hdev);
void mgmt_set_powewed_faiwed(stwuct hci_dev *hdev, int eww);
void mgmt_powew_on(stwuct hci_dev *hdev, int eww);
void __mgmt_powew_off(stwuct hci_dev *hdev);
void mgmt_new_wink_key(stwuct hci_dev *hdev, stwuct wink_key *key,
		       boow pewsistent);
void mgmt_device_connected(stwuct hci_dev *hdev, stwuct hci_conn *conn,
			   u8 *name, u8 name_wen);
void mgmt_device_disconnected(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			      u8 wink_type, u8 addw_type, u8 weason,
			      boow mgmt_connected);
void mgmt_disconnect_faiwed(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 wink_type, u8 addw_type, u8 status);
void mgmt_connect_faiwed(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 wink_type,
			 u8 addw_type, u8 status);
void mgmt_pin_code_wequest(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 secuwe);
void mgmt_pin_code_wepwy_compwete(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				  u8 status);
void mgmt_pin_code_neg_wepwy_compwete(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				      u8 status);
int mgmt_usew_confiwm_wequest(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			      u8 wink_type, u8 addw_type, u32 vawue,
			      u8 confiwm_hint);
int mgmt_usew_confiwm_wepwy_compwete(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				     u8 wink_type, u8 addw_type, u8 status);
int mgmt_usew_confiwm_neg_wepwy_compwete(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
					 u8 wink_type, u8 addw_type, u8 status);
int mgmt_usew_passkey_wequest(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			      u8 wink_type, u8 addw_type);
int mgmt_usew_passkey_wepwy_compwete(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				     u8 wink_type, u8 addw_type, u8 status);
int mgmt_usew_passkey_neg_wepwy_compwete(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
					 u8 wink_type, u8 addw_type, u8 status);
int mgmt_usew_passkey_notify(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			     u8 wink_type, u8 addw_type, u32 passkey,
			     u8 entewed);
void mgmt_auth_faiwed(stwuct hci_conn *conn, u8 status);
void mgmt_auth_enabwe_compwete(stwuct hci_dev *hdev, u8 status);
void mgmt_set_cwass_of_dev_compwete(stwuct hci_dev *hdev, u8 *dev_cwass,
				    u8 status);
void mgmt_set_wocaw_name_compwete(stwuct hci_dev *hdev, u8 *name, u8 status);
void mgmt_stawt_discovewy_compwete(stwuct hci_dev *hdev, u8 status);
void mgmt_stop_discovewy_compwete(stwuct hci_dev *hdev, u8 status);
void mgmt_device_found(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 wink_type,
		       u8 addw_type, u8 *dev_cwass, s8 wssi, u32 fwags,
		       u8 *eiw, u16 eiw_wen, u8 *scan_wsp, u8 scan_wsp_wen,
		       u64 instant);
void mgmt_wemote_name(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 wink_type,
		      u8 addw_type, s8 wssi, u8 *name, u8 name_wen);
void mgmt_discovewing(stwuct hci_dev *hdev, u8 discovewing);
void mgmt_suspending(stwuct hci_dev *hdev, u8 state);
void mgmt_wesuming(stwuct hci_dev *hdev, u8 weason, bdaddw_t *bdaddw,
		   u8 addw_type);
boow mgmt_powewing_down(stwuct hci_dev *hdev);
void mgmt_new_wtk(stwuct hci_dev *hdev, stwuct smp_wtk *key, boow pewsistent);
void mgmt_new_iwk(stwuct hci_dev *hdev, stwuct smp_iwk *iwk, boow pewsistent);
void mgmt_new_cswk(stwuct hci_dev *hdev, stwuct smp_cswk *cswk,
		   boow pewsistent);
void mgmt_new_conn_pawam(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			 u8 bdaddw_type, u8 stowe_hint, u16 min_intewvaw,
			 u16 max_intewvaw, u16 watency, u16 timeout);
void mgmt_smp_compwete(stwuct hci_conn *conn, boow compwete);
boow mgmt_get_connectabwe(stwuct hci_dev *hdev);
u8 mgmt_get_adv_discov_fwags(stwuct hci_dev *hdev);
void mgmt_advewtising_added(stwuct sock *sk, stwuct hci_dev *hdev,
			    u8 instance);
void mgmt_advewtising_wemoved(stwuct sock *sk, stwuct hci_dev *hdev,
			      u8 instance);
void mgmt_adv_monitow_wemoved(stwuct hci_dev *hdev, u16 handwe);
int mgmt_phy_configuwation_changed(stwuct hci_dev *hdev, stwuct sock *skip);
void mgmt_adv_monitow_device_wost(stwuct hci_dev *hdev, u16 handwe,
				  bdaddw_t *bdaddw, u8 addw_type);

int hci_abowt_conn(stwuct hci_conn *conn, u8 weason);
u8 hci_we_conn_update(stwuct hci_conn *conn, u16 min, u16 max, u16 watency,
		      u16 to_muwtipwiew);
void hci_we_stawt_enc(stwuct hci_conn *conn, __we16 ediv, __we64 wand,
		      __u8 wtk[16], __u8 key_size);

void hci_copy_identity_addwess(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			       u8 *bdaddw_type);

#define SCO_AIWMODE_MASK       0x0003
#define SCO_AIWMODE_CVSD       0x0000
#define SCO_AIWMODE_TWANSP     0x0003

#define WOCAW_CODEC_ACW_MASK	BIT(0)
#define WOCAW_CODEC_SCO_MASK	BIT(1)

#define TWANSPOWT_TYPE_MAX	0x04

#endif /* __HCI_COWE_H */
