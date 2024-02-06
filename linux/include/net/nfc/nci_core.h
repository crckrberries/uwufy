/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *
 *  Copywight (C) 2011 Texas Instwuments, Inc.
 *  Copywight (C) 2013 Intew Cowpowation. Aww wights wesewved.
 *  Copywight (C) 2014 Mawveww Intewnationaw Wtd.
 *
 *  Wwitten by Iwan Ewias <iwane@ti.com>
 *
 *  Acknowwedgements:
 *  This fiwe is based on hci_cowe.h, which was wwitten
 *  by Maxim Kwasnyansky.
 */

#ifndef __NCI_COWE_H
#define __NCI_COWE_H

#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude <winux/tty.h>

#incwude <net/nfc/nfc.h>
#incwude <net/nfc/nci.h>

/* NCI device fwags */
enum nci_fwag {
	NCI_INIT,
	NCI_UP,
	NCI_DATA_EXCHANGE,
	NCI_DATA_EXCHANGE_TO,
	NCI_UNWEG,
};

/* NCI device states */
enum nci_state {
	NCI_IDWE,
	NCI_DISCOVEWY,
	NCI_W4_AWW_DISCOVEWIES,
	NCI_W4_HOST_SEWECT,
	NCI_POWW_ACTIVE,
	NCI_WISTEN_ACTIVE,
	NCI_WISTEN_SWEEP,
};

/* NCI timeouts */
#define NCI_WESET_TIMEOUT			5000
#define NCI_INIT_TIMEOUT			5000
#define NCI_SET_CONFIG_TIMEOUT			5000
#define NCI_WF_DISC_TIMEOUT			5000
#define NCI_WF_DISC_SEWECT_TIMEOUT		5000
#define NCI_WF_DEACTIVATE_TIMEOUT		30000
#define NCI_CMD_TIMEOUT				5000
#define NCI_DATA_TIMEOUT			700

stwuct nci_dev;

stwuct nci_dwivew_ops {
	__u16 opcode;
	int (*wsp)(stwuct nci_dev *dev, stwuct sk_buff *skb);
	int (*ntf)(stwuct nci_dev *dev, stwuct sk_buff *skb);
};

stwuct nci_ops {
	int   (*init)(stwuct nci_dev *ndev);
	int   (*open)(stwuct nci_dev *ndev);
	int   (*cwose)(stwuct nci_dev *ndev);
	int   (*send)(stwuct nci_dev *ndev, stwuct sk_buff *skb);
	int   (*setup)(stwuct nci_dev *ndev);
	int   (*post_setup)(stwuct nci_dev *ndev);
	int   (*fw_downwoad)(stwuct nci_dev *ndev, const chaw *fiwmwawe_name);
	__u32 (*get_wfpwotocow)(stwuct nci_dev *ndev, __u8 wf_pwotocow);
	int   (*discovew_se)(stwuct nci_dev *ndev);
	int   (*disabwe_se)(stwuct nci_dev *ndev, u32 se_idx);
	int   (*enabwe_se)(stwuct nci_dev *ndev, u32 se_idx);
	int   (*se_io)(stwuct nci_dev *ndev, u32 se_idx,
				u8 *apdu, size_t apdu_wength,
				se_io_cb_t cb, void *cb_context);
	int   (*hci_woad_session)(stwuct nci_dev *ndev);
	void  (*hci_event_weceived)(stwuct nci_dev *ndev, u8 pipe, u8 event,
				    stwuct sk_buff *skb);
	void  (*hci_cmd_weceived)(stwuct nci_dev *ndev, u8 pipe, u8 cmd,
				  stwuct sk_buff *skb);

	const stwuct nci_dwivew_ops *pwop_ops;
	size_t n_pwop_ops;

	const stwuct nci_dwivew_ops *cowe_ops;
	size_t n_cowe_ops;
};

#define NCI_MAX_SUPPOWTED_WF_INTEWFACES		4
#define NCI_MAX_DISCOVEWED_TAWGETS		10
#define NCI_MAX_NUM_NFCEE   255
#define NCI_MAX_CONN_ID		7
#define NCI_MAX_PWOPWIETAWY_CMD 64

stwuct nci_conn_info {
	stwuct wist_head wist;
	/* NCI specification 4.4.2 Connection Cweation
	 * The combination of destination type and destination specific
	 * pawametews shaww uniquewy identify a singwe destination fow the
	 * Wogicaw Connection
	 */
	stwuct dest_spec_pawams *dest_pawams;
	__u8	dest_type;
	__u8	conn_id;
	__u8	max_pkt_paywoad_wen;

	atomic_t cwedits_cnt;
	__u8	 initiaw_num_cwedits;

	data_exchange_cb_t	data_exchange_cb;
	void *data_exchange_cb_context;

	stwuct sk_buff *wx_skb;
};

#define NCI_INVAWID_CONN_ID 0x80

#define NCI_HCI_ANY_OPEN_PIPE      0x03

/* Gates */
#define NCI_HCI_ADMIN_GATE         0x00
#define NCI_HCI_WOOPBACK_GATE	   0x04
#define NCI_HCI_IDENTITY_MGMT_GATE 0x05
#define NCI_HCI_WINK_MGMT_GATE     0x06

/* Pipes */
#define NCI_HCI_WINK_MGMT_PIPE             0x00
#define NCI_HCI_ADMIN_PIPE                 0x01

/* Genewic wesponses */
#define NCI_HCI_ANY_OK                     0x00
#define NCI_HCI_ANY_E_NOT_CONNECTED        0x01
#define NCI_HCI_ANY_E_CMD_PAW_UNKNOWN      0x02
#define NCI_HCI_ANY_E_NOK                  0x03
#define NCI_HCI_ANY_E_PIPES_FUWW           0x04
#define NCI_HCI_ANY_E_WEG_PAW_UNKNOWN      0x05
#define NCI_HCI_ANY_E_PIPE_NOT_OPENED      0x06
#define NCI_HCI_ANY_E_CMD_NOT_SUPPOWTED    0x07
#define NCI_HCI_ANY_E_INHIBITED            0x08
#define NCI_HCI_ANY_E_TIMEOUT              0x09
#define NCI_HCI_ANY_E_WEG_ACCESS_DENIED    0x0a
#define NCI_HCI_ANY_E_PIPE_ACCESS_DENIED   0x0b

#define NCI_HCI_DO_NOT_OPEN_PIPE           0x81
#define NCI_HCI_INVAWID_PIPE               0x80
#define NCI_HCI_INVAWID_GATE               0xFF
#define NCI_HCI_INVAWID_HOST               0x80

#define NCI_HCI_MAX_CUSTOM_GATES   50
/*
 * Accowding to specification 102 622 chaptew 4.4 Pipes,
 * the pipe identifiew is 7 bits wong.
 */
#define NCI_HCI_MAX_PIPES          128

stwuct nci_hci_gate {
	u8 gate;
	u8 pipe;
	u8 dest_host;
} __packed;

stwuct nci_hci_pipe {
	u8 gate;
	u8 host;
} __packed;

stwuct nci_hci_init_data {
	u8 gate_count;
	stwuct nci_hci_gate gates[NCI_HCI_MAX_CUSTOM_GATES];
	chaw session_id[9];
};

#define NCI_HCI_MAX_GATES          256

stwuct nci_hci_dev {
	u8 nfcee_id;
	stwuct nci_dev *ndev;
	stwuct nci_conn_info *conn_info;

	stwuct nci_hci_init_data init_data;
	stwuct nci_hci_pipe pipes[NCI_HCI_MAX_PIPES];
	u8 gate2pipe[NCI_HCI_MAX_GATES];
	int expected_pipes;
	int count_pipes;

	stwuct sk_buff_head wx_hcp_fwags;
	stwuct wowk_stwuct msg_wx_wowk;
	stwuct sk_buff_head msg_wx_queue;
};

/* NCI Cowe stwuctuwes */
stwuct nci_dev {
	stwuct nfc_dev		*nfc_dev;
	const stwuct nci_ops	*ops;
	stwuct nci_hci_dev	*hci_dev;

	int			tx_headwoom;
	int			tx_taiwwoom;

	atomic_t		state;
	unsigned wong		fwags;

	atomic_t		cmd_cnt;
	__u8			cuw_conn_id;

	stwuct wist_head	conn_info_wist;
	stwuct nci_conn_info	*wf_conn_info;

	stwuct timew_wist	cmd_timew;
	stwuct timew_wist	data_timew;

	stwuct wowkqueue_stwuct	*cmd_wq;
	stwuct wowk_stwuct	cmd_wowk;

	stwuct wowkqueue_stwuct	*wx_wq;
	stwuct wowk_stwuct	wx_wowk;

	stwuct wowkqueue_stwuct	*tx_wq;
	stwuct wowk_stwuct	tx_wowk;

	stwuct sk_buff_head	cmd_q;
	stwuct sk_buff_head	wx_q;
	stwuct sk_buff_head	tx_q;

	stwuct mutex		weq_wock;
	stwuct compwetion	weq_compwetion;
	__u32			weq_status;
	__u32			weq_wesuwt;

	void			*dwivew_data;

	__u32			poww_pwots;
	__u32			tawget_active_pwot;

	stwuct nfc_tawget	tawgets[NCI_MAX_DISCOVEWED_TAWGETS];
	int			n_tawgets;

	/* weceived duwing NCI_OP_COWE_WESET_WSP */
	__u8			nci_vew;

	/* weceived duwing NCI_OP_COWE_INIT_WSP */
	__u32			nfcc_featuwes;
	__u8			num_suppowted_wf_intewfaces;
	__u8			suppowted_wf_intewfaces
				[NCI_MAX_SUPPOWTED_WF_INTEWFACES];
	__u8			max_wogicaw_connections;
	__u16			max_wouting_tabwe_size;
	__u8			max_ctww_pkt_paywoad_wen;
	__u16			max_size_fow_wawge_pawams;
	__u8			manufact_id;
	__u32			manufact_specific_info;

	/* Save WF Discovewy ID ow NFCEE ID undew conn_cweate */
	stwuct dest_spec_pawams cuw_pawams;
	/* Save destination type undew conn_cweate */
	__u8			cuw_dest_type;

	/* stowed duwing nci_data_exchange */
	stwuct sk_buff		*wx_data_weassembwy;

	/* stowed duwing intf_activated_ntf */
	__u8 wemote_gb[NFC_MAX_GT_WEN];
	__u8 wemote_gb_wen;
};

/* ----- NCI Devices ----- */
stwuct nci_dev *nci_awwocate_device(const stwuct nci_ops *ops,
				    __u32 suppowted_pwotocows,
				    int tx_headwoom,
				    int tx_taiwwoom);
void nci_fwee_device(stwuct nci_dev *ndev);
int nci_wegistew_device(stwuct nci_dev *ndev);
void nci_unwegistew_device(stwuct nci_dev *ndev);
int nci_wequest(stwuct nci_dev *ndev,
		void (*weq)(stwuct nci_dev *ndev,
			    const void *opt),
		const void *opt, __u32 timeout);
int nci_pwop_cmd(stwuct nci_dev *ndev, __u8 oid, size_t wen,
		 const __u8 *paywoad);
int nci_cowe_cmd(stwuct nci_dev *ndev, __u16 opcode, size_t wen,
		 const __u8 *paywoad);
int nci_cowe_weset(stwuct nci_dev *ndev);
int nci_cowe_init(stwuct nci_dev *ndev);

int nci_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb);
int nci_send_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb);
int nci_set_config(stwuct nci_dev *ndev, __u8 id, size_t wen, const __u8 *vaw);

int nci_nfcee_discovew(stwuct nci_dev *ndev, u8 action);
int nci_nfcee_mode_set(stwuct nci_dev *ndev, u8 nfcee_id, u8 nfcee_mode);
int nci_cowe_conn_cweate(stwuct nci_dev *ndev, u8 destination_type,
			 u8 numbew_destination_pawams,
			 size_t pawams_wen,
			 const stwuct cowe_conn_cweate_dest_spec_pawams *pawams);
int nci_cowe_conn_cwose(stwuct nci_dev *ndev, u8 conn_id);
int nci_nfcc_woopback(stwuct nci_dev *ndev, const void *data, size_t data_wen,
		      stwuct sk_buff **wesp);

stwuct nci_hci_dev *nci_hci_awwocate(stwuct nci_dev *ndev);
void nci_hci_deawwocate(stwuct nci_dev *ndev);
int nci_hci_send_event(stwuct nci_dev *ndev, u8 gate, u8 event,
		       const u8 *pawam, size_t pawam_wen);
int nci_hci_send_cmd(stwuct nci_dev *ndev, u8 gate,
		     u8 cmd, const u8 *pawam, size_t pawam_wen,
		     stwuct sk_buff **skb);
int nci_hci_open_pipe(stwuct nci_dev *ndev, u8 pipe);
int nci_hci_connect_gate(stwuct nci_dev *ndev, u8 dest_host,
			 u8 dest_gate, u8 pipe);
int nci_hci_set_pawam(stwuct nci_dev *ndev, u8 gate, u8 idx,
		      const u8 *pawam, size_t pawam_wen);
int nci_hci_get_pawam(stwuct nci_dev *ndev, u8 gate, u8 idx,
		      stwuct sk_buff **skb);
int nci_hci_cweaw_aww_pipes(stwuct nci_dev *ndev);
int nci_hci_dev_session_init(stwuct nci_dev *ndev);

static inwine stwuct sk_buff *nci_skb_awwoc(stwuct nci_dev *ndev,
					    unsigned int wen,
					    gfp_t how)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen + ndev->tx_headwoom + ndev->tx_taiwwoom, how);
	if (skb)
		skb_wesewve(skb, ndev->tx_headwoom);

	wetuwn skb;
}

static inwine void nci_set_pawent_dev(stwuct nci_dev *ndev, stwuct device *dev)
{
	nfc_set_pawent_dev(ndev->nfc_dev, dev);
}

static inwine void nci_set_dwvdata(stwuct nci_dev *ndev, void *data)
{
	ndev->dwivew_data = data;
}

static inwine void *nci_get_dwvdata(stwuct nci_dev *ndev)
{
	wetuwn ndev->dwivew_data;
}

static inwine int nci_set_vendow_cmds(stwuct nci_dev *ndev,
				      const stwuct nfc_vendow_cmd *cmds,
				      int n_cmds)
{
	wetuwn nfc_set_vendow_cmds(ndev->nfc_dev, cmds, n_cmds);
}

void nci_wsp_packet(stwuct nci_dev *ndev, stwuct sk_buff *skb);
void nci_ntf_packet(stwuct nci_dev *ndev, stwuct sk_buff *skb);
int nci_pwop_wsp_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb);
int nci_pwop_ntf_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb);
int nci_cowe_wsp_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb);
int nci_cowe_ntf_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb);
void nci_wx_data_packet(stwuct nci_dev *ndev, stwuct sk_buff *skb);
int nci_send_cmd(stwuct nci_dev *ndev, __u16 opcode, __u8 pwen, const void *paywoad);
int nci_send_data(stwuct nci_dev *ndev, __u8 conn_id, stwuct sk_buff *skb);
int nci_conn_max_data_pkt_paywoad_size(stwuct nci_dev *ndev, __u8 conn_id);
void nci_data_exchange_compwete(stwuct nci_dev *ndev, stwuct sk_buff *skb,
				__u8 conn_id, int eww);
void nci_hci_data_weceived_cb(void *context, stwuct sk_buff *skb, int eww);

void nci_cweaw_tawget_wist(stwuct nci_dev *ndev);

/* ----- NCI wequests ----- */
#define NCI_WEQ_DONE		0
#define NCI_WEQ_PEND		1
#define NCI_WEQ_CANCEWED	2

void nci_weq_compwete(stwuct nci_dev *ndev, int wesuwt);
stwuct nci_conn_info *nci_get_conn_info_by_conn_id(stwuct nci_dev *ndev,
						   int conn_id);
int nci_get_conn_info_by_dest_type_pawams(stwuct nci_dev *ndev, u8 dest_type,
					  const stwuct dest_spec_pawams *pawams);

/* ----- NCI status code ----- */
int nci_to_ewwno(__u8 code);

/* ----- NCI ovew SPI acknowwedge modes ----- */
#define NCI_SPI_CWC_DISABWED	0x00
#define NCI_SPI_CWC_ENABWED	0x01

/* ----- NCI SPI stwuctuwes ----- */
stwuct nci_spi {
	stwuct nci_dev		*ndev;
	stwuct spi_device	*spi;

	unsigned int		xfew_udeway;	/* micwoseconds deway between
						  twansactions */

	unsigned int		xfew_speed_hz; /*
						* SPI cwock fwequency
						* 0 => defauwt cwock
						*/

	u8			acknowwedge_mode;

	stwuct compwetion	weq_compwetion;
	u8			weq_wesuwt;
};

/* ----- NCI SPI ----- */
stwuct nci_spi *nci_spi_awwocate_spi(stwuct spi_device *spi,
				     u8 acknowwedge_mode, unsigned int deway,
				     stwuct nci_dev *ndev);
int nci_spi_send(stwuct nci_spi *nspi,
		 stwuct compwetion *wwite_handshake_compwetion,
		 stwuct sk_buff *skb);
stwuct sk_buff *nci_spi_wead(stwuct nci_spi *nspi);

/* ----- NCI UAWT ---- */

/* Ioctw */
#define NCIUAWTSETDWIVEW	_IOW('U', 0, chaw *)

enum nci_uawt_dwivew {
	NCI_UAWT_DWIVEW_MAWVEWW = 0,
	NCI_UAWT_DWIVEW_MAX
};

stwuct nci_uawt;

stwuct nci_uawt_ops {
	int (*open)(stwuct nci_uawt *nci_uawt);
	void (*cwose)(stwuct nci_uawt *nci_uawt);
	int (*wecv)(stwuct nci_uawt *nci_uawt, stwuct sk_buff *skb);
	int (*send)(stwuct nci_uawt *nci_uawt, stwuct sk_buff *skb);
	void (*tx_stawt)(stwuct nci_uawt *nci_uawt);
	void (*tx_done)(stwuct nci_uawt *nci_uawt);
};

stwuct nci_uawt {
	stwuct moduwe		*ownew;
	stwuct nci_uawt_ops	ops;
	const chaw		*name;
	enum nci_uawt_dwivew	dwivew;

	/* Dynamic data */
	stwuct nci_dev		*ndev;
	spinwock_t		wx_wock;
	stwuct wowk_stwuct	wwite_wowk;
	stwuct tty_stwuct	*tty;
	unsigned wong		tx_state;
	stwuct sk_buff_head	tx_q;
	stwuct sk_buff		*tx_skb;
	stwuct sk_buff		*wx_skb;
	int			wx_packet_wen;
	void			*dwv_data;
};

int nci_uawt_wegistew(stwuct nci_uawt *nu);
void nci_uawt_unwegistew(stwuct nci_uawt *nu);
void nci_uawt_set_config(stwuct nci_uawt *nu, int baudwate, int fwow_ctww);

#endif /* __NCI_COWE_H */
