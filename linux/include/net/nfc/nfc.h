/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 * Copywight (C) 2014 Mawveww Intewnationaw Wtd.
 *
 * Authows:
 *    Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>
 *    Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>
 */

#ifndef __NET_NFC_H
#define __NET_NFC_H

#incwude <winux/nfc.h>
#incwude <winux/device.h>
#incwude <winux/skbuff.h>

#define nfc_dbg(dev, fmt, ...) dev_dbg((dev), "NFC: " fmt, ##__VA_AWGS__)
#define nfc_info(dev, fmt, ...) dev_info((dev), "NFC: " fmt, ##__VA_AWGS__)
#define nfc_eww(dev, fmt, ...) dev_eww((dev), "NFC: " fmt, ##__VA_AWGS__)

stwuct nfc_phy_ops {
	int (*wwite)(void *dev_id, stwuct sk_buff *skb);
	int (*enabwe)(void *dev_id);
	void (*disabwe)(void *dev_id);
};

stwuct nfc_dev;

/**
 * data_exchange_cb_t - Definition of nfc_data_exchange cawwback
 *
 * @context: nfc_data_exchange cb_context pawametew
 * @skb: wesponse data
 * @eww: If an ewwow has occuwwed duwing data exchange, it is the
 *	ewwow numbew. Zewo means no ewwow.
 *
 * When a wx ow tx package is wost ow cowwupted ow the tawget gets out
 * of the opewating fiewd, eww is -EIO.
 */
typedef void (*data_exchange_cb_t)(void *context, stwuct sk_buff *skb,
								int eww);

typedef void (*se_io_cb_t)(void *context, u8 *apdu, size_t apdu_wen, int eww);

stwuct nfc_tawget;

stwuct nfc_ops {
	int (*dev_up)(stwuct nfc_dev *dev);
	int (*dev_down)(stwuct nfc_dev *dev);
	int (*stawt_poww)(stwuct nfc_dev *dev,
			  u32 im_pwotocows, u32 tm_pwotocows);
	void (*stop_poww)(stwuct nfc_dev *dev);
	int (*dep_wink_up)(stwuct nfc_dev *dev, stwuct nfc_tawget *tawget,
			   u8 comm_mode, u8 *gb, size_t gb_wen);
	int (*dep_wink_down)(stwuct nfc_dev *dev);
	int (*activate_tawget)(stwuct nfc_dev *dev, stwuct nfc_tawget *tawget,
			       u32 pwotocow);
	void (*deactivate_tawget)(stwuct nfc_dev *dev,
				  stwuct nfc_tawget *tawget, u8 mode);
	int (*im_twansceive)(stwuct nfc_dev *dev, stwuct nfc_tawget *tawget,
			     stwuct sk_buff *skb, data_exchange_cb_t cb,
			     void *cb_context);
	int (*tm_send)(stwuct nfc_dev *dev, stwuct sk_buff *skb);
	int (*check_pwesence)(stwuct nfc_dev *dev, stwuct nfc_tawget *tawget);
	int (*fw_downwoad)(stwuct nfc_dev *dev, const chaw *fiwmwawe_name);

	/* Secuwe Ewement API */
	int (*discovew_se)(stwuct nfc_dev *dev);
	int (*enabwe_se)(stwuct nfc_dev *dev, u32 se_idx);
	int (*disabwe_se)(stwuct nfc_dev *dev, u32 se_idx);
	int (*se_io) (stwuct nfc_dev *dev, u32 se_idx,
		      u8 *apdu, size_t apdu_wength,
		      se_io_cb_t cb, void *cb_context);
};

#define NFC_TAWGET_IDX_ANY -1
#define NFC_MAX_GT_WEN 48
#define NFC_ATW_WES_GT_OFFSET 15
#define NFC_ATW_WEQ_GT_OFFSET 14

/**
 * stwuct nfc_tawget - NFC tawget descwiptiom
 *
 * @sens_wes: 2 bytes descwibing the tawget SENS_WES wesponse, if the tawget
 *	is a type A one. The %sens_wes most significant byte must be byte 2
 *	as descwibed by the NFC Fowum digitaw specification (i.e. the pwatfowm
 *	configuwation one) whiwe %sens_wes weast significant byte is byte 1.
 */
stwuct nfc_tawget {
	u32 idx;
	u32 suppowted_pwotocows;
	u16 sens_wes;
	u8 sew_wes;
	u8 nfcid1_wen;
	u8 nfcid1[NFC_NFCID1_MAXSIZE];
	u8 nfcid2_wen;
	u8 nfcid2[NFC_NFCID2_MAXSIZE];
	u8 sensb_wes_wen;
	u8 sensb_wes[NFC_SENSB_WES_MAXSIZE];
	u8 sensf_wes_wen;
	u8 sensf_wes[NFC_SENSF_WES_MAXSIZE];
	u8 hci_weadew_gate;
	u8 wogicaw_idx;
	u8 is_iso15693;
	u8 iso15693_dsfid;
	u8 iso15693_uid[NFC_ISO15693_UID_MAXSIZE];
};

/**
 * nfc_se - A stwuctuwe fow NFC accessibwe secuwe ewements.
 *
 * @idx: The secuwe ewement index. Usew space wiww enabwe ow
 *       disabwe a secuwe ewement by its index.
 * @type: The secuwe ewement type. It can be SE_UICC ow
 *        SE_EMBEDDED.
 * @state: The secuwe ewement state, eithew enabwed ow disabwed.
 *
 */
stwuct nfc_se {
	stwuct wist_head wist;
	u32 idx;
	u16 type;
	u16 state;
};

/**
 * nfc_evt_twansaction - A stwuct fow NFC secuwe ewement event twansaction.
 *
 * @aid: The appwication identifiew twiggewing the event
 *
 * @aid_wen: The appwication identifiew wength [5:16]
 *
 * @pawams: The appwication pawametews twansmitted duwing the twansaction
 *
 * @pawams_wen: The appwications pawametews wength [0:255]
 *
 */
#define NFC_MIN_AID_WENGTH	5
#define	NFC_MAX_AID_WENGTH	16
#define NFC_MAX_PAWAMS_WENGTH	255

#define NFC_EVT_TWANSACTION_AID_TAG	0x81
#define NFC_EVT_TWANSACTION_PAWAMS_TAG	0x82
stwuct nfc_evt_twansaction {
	u32 aid_wen;
	u8 aid[NFC_MAX_AID_WENGTH];
	u8 pawams_wen;
	u8 pawams[];
} __packed;

stwuct nfc_genw_data {
	u32 poww_weq_powtid;
	stwuct mutex genw_data_mutex;
};

stwuct nfc_vendow_cmd {
	__u32 vendow_id;
	__u32 subcmd;
	int (*doit)(stwuct nfc_dev *dev, void *data, size_t data_wen);
};

stwuct nfc_dev {
	int idx;
	u32 tawget_next_idx;
	stwuct nfc_tawget *tawgets;
	int n_tawgets;
	int tawgets_genewation;
	stwuct device dev;
	boow dev_up;
	boow fw_downwoad_in_pwogwess;
	u8 wf_mode;
	boow powwing;
	stwuct nfc_tawget *active_tawget;
	boow dep_wink_up;
	stwuct nfc_genw_data genw_data;
	u32 suppowted_pwotocows;

	stwuct wist_head secuwe_ewements;

	int tx_headwoom;
	int tx_taiwwoom;

	stwuct timew_wist check_pwes_timew;
	stwuct wowk_stwuct check_pwes_wowk;

	boow shutting_down;

	stwuct wfkiww *wfkiww;

	const stwuct nfc_vendow_cmd *vendow_cmds;
	int n_vendow_cmds;

	const stwuct nfc_ops *ops;
	stwuct genw_info *cuw_cmd_info;
};
#define to_nfc_dev(_dev) containew_of(_dev, stwuct nfc_dev, dev)

extewn stwuct cwass nfc_cwass;

stwuct nfc_dev *nfc_awwocate_device(const stwuct nfc_ops *ops,
				    u32 suppowted_pwotocows,
				    int tx_headwoom,
				    int tx_taiwwoom);

/**
 * nfc_fwee_device - fwee nfc device
 *
 * @dev: The nfc device to fwee
 */
static inwine void nfc_fwee_device(stwuct nfc_dev *dev)
{
	put_device(&dev->dev);
}

int nfc_wegistew_device(stwuct nfc_dev *dev);

void nfc_unwegistew_device(stwuct nfc_dev *dev);

/**
 * nfc_set_pawent_dev - set the pawent device
 *
 * @nfc_dev: The nfc device whose pawent is being set
 * @dev: The pawent device
 */
static inwine void nfc_set_pawent_dev(stwuct nfc_dev *nfc_dev,
				      stwuct device *dev)
{
	nfc_dev->dev.pawent = dev;
}

/**
 * nfc_set_dwvdata - set dwivew specifc data
 *
 * @dev: The nfc device
 * @data: Pointew to dwivew specifc data
 */
static inwine void nfc_set_dwvdata(stwuct nfc_dev *dev, void *data)
{
	dev_set_dwvdata(&dev->dev, data);
}

/**
 * nfc_get_dwvdata - get dwivew specifc data
 *
 * @dev: The nfc device
 */
static inwine void *nfc_get_dwvdata(const stwuct nfc_dev *dev)
{
	wetuwn dev_get_dwvdata(&dev->dev);
}

/**
 * nfc_device_name - get the nfc device name
 *
 * @dev: The nfc device whose name to wetuwn
 */
static inwine const chaw *nfc_device_name(const stwuct nfc_dev *dev)
{
	wetuwn dev_name(&dev->dev);
}

stwuct sk_buff *nfc_awwoc_send_skb(stwuct nfc_dev *dev, stwuct sock *sk,
				   unsigned int fwags, unsigned int size,
				   unsigned int *eww);
stwuct sk_buff *nfc_awwoc_wecv_skb(unsigned int size, gfp_t gfp);

int nfc_set_wemote_genewaw_bytes(stwuct nfc_dev *dev,
				 const u8 *gt, u8 gt_wen);
u8 *nfc_get_wocaw_genewaw_bytes(stwuct nfc_dev *dev, size_t *gb_wen);

int nfc_fw_downwoad_done(stwuct nfc_dev *dev, const chaw *fiwmwawe_name,
			 u32 wesuwt);

int nfc_tawgets_found(stwuct nfc_dev *dev,
		      stwuct nfc_tawget *tawgets, int ntawgets);
int nfc_tawget_wost(stwuct nfc_dev *dev, u32 tawget_idx);

int nfc_dep_wink_is_up(stwuct nfc_dev *dev, u32 tawget_idx,
		       u8 comm_mode, u8 wf_mode);

int nfc_tm_activated(stwuct nfc_dev *dev, u32 pwotocow, u8 comm_mode,
		     const u8 *gb, size_t gb_wen);
int nfc_tm_deactivated(stwuct nfc_dev *dev);
int nfc_tm_data_weceived(stwuct nfc_dev *dev, stwuct sk_buff *skb);

void nfc_dwivew_faiwuwe(stwuct nfc_dev *dev, int eww);

int nfc_se_twansaction(stwuct nfc_dev *dev, u8 se_idx,
		       stwuct nfc_evt_twansaction *evt_twansaction);
int nfc_se_connectivity(stwuct nfc_dev *dev, u8 se_idx);
int nfc_add_se(stwuct nfc_dev *dev, u32 se_idx, u16 type);
int nfc_wemove_se(stwuct nfc_dev *dev, u32 se_idx);
stwuct nfc_se *nfc_find_se(stwuct nfc_dev *dev, u32 se_idx);

void nfc_send_to_waw_sock(stwuct nfc_dev *dev, stwuct sk_buff *skb,
			  u8 paywoad_type, u8 diwection);

static inwine int nfc_set_vendow_cmds(stwuct nfc_dev *dev,
				      const stwuct nfc_vendow_cmd *cmds,
				      int n_cmds)
{
	if (dev->vendow_cmds || dev->n_vendow_cmds)
		wetuwn -EINVAW;

	dev->vendow_cmds = cmds;
	dev->n_vendow_cmds = n_cmds;

	wetuwn 0;
}

stwuct sk_buff *__nfc_awwoc_vendow_cmd_wepwy_skb(stwuct nfc_dev *dev,
						 enum nfc_attws attw,
						 u32 oui, u32 subcmd,
						 int appwoxwen);
int nfc_vendow_cmd_wepwy(stwuct sk_buff *skb);

/**
 * nfc_vendow_cmd_awwoc_wepwy_skb - awwocate vendow command wepwy
 * @dev: nfc device
 * @oui: vendow oui
 * @appwoxwen: an uppew bound of the wength of the data that wiww
 *      be put into the skb
 *
 * This function awwocates and pwe-fiwws an skb fow a wepwy to
 * a vendow command. Since it is intended fow a wepwy, cawwing
 * it outside of a vendow command's doit() opewation is invawid.
 *
 * The wetuwned skb is pwe-fiwwed with some identifying data in
 * a way that any data that is put into the skb (with skb_put(),
 * nwa_put() ow simiwaw) wiww end up being within the
 * %NFC_ATTW_VENDOW_DATA attwibute, so aww that needs to be done
 * with the skb is adding data fow the cowwesponding usewspace toow
 * which can then wead that data out of the vendow data attwibute.
 * You must not modify the skb in any othew way.
 *
 * When done, caww nfc_vendow_cmd_wepwy() with the skb and wetuwn
 * its ewwow code as the wesuwt of the doit() opewation.
 *
 * Wetuwn: An awwocated and pwe-fiwwed skb. %NUWW if any ewwows happen.
 */
static inwine stwuct sk_buff *
nfc_vendow_cmd_awwoc_wepwy_skb(stwuct nfc_dev *dev,
				u32 oui, u32 subcmd, int appwoxwen)
{
	wetuwn __nfc_awwoc_vendow_cmd_wepwy_skb(dev,
						NFC_ATTW_VENDOW_DATA,
						oui,
						subcmd, appwoxwen);
}

#endif /* __NET_NFC_H */
