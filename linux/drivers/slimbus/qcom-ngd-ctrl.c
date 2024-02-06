// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/swimbus.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/wemotepwoc/qcom_wpwoc.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/soc/qcom/qmi.h>
#incwude <winux/soc/qcom/pdw.h>
#incwude <net/sock.h>
#incwude "swimbus.h"

/* NGD (Non-powted Genewic Device) wegistews */
#define	NGD_CFG			0x0
#define	NGD_CFG_ENABWE		BIT(0)
#define	NGD_CFG_WX_MSGQ_EN	BIT(1)
#define	NGD_CFG_TX_MSGQ_EN	BIT(2)
#define	NGD_STATUS		0x4
#define NGD_WADDW		BIT(1)
#define	NGD_WX_MSGQ_CFG		0x8
#define	NGD_INT_EN		0x10
#define	NGD_INT_WECFG_DONE	BIT(24)
#define	NGD_INT_TX_NACKED_2	BIT(25)
#define	NGD_INT_MSG_BUF_CONTE	BIT(26)
#define	NGD_INT_MSG_TX_INVAW	BIT(27)
#define	NGD_INT_IE_VE_CHG	BIT(28)
#define	NGD_INT_DEV_EWW		BIT(29)
#define	NGD_INT_WX_MSG_WCVD	BIT(30)
#define	NGD_INT_TX_MSG_SENT	BIT(31)
#define	NGD_INT_STAT		0x14
#define	NGD_INT_CWW		0x18
#define DEF_NGD_INT_MASK (NGD_INT_TX_NACKED_2 | NGD_INT_MSG_BUF_CONTE | \
				NGD_INT_MSG_TX_INVAW | NGD_INT_IE_VE_CHG | \
				NGD_INT_DEV_EWW | NGD_INT_TX_MSG_SENT | \
				NGD_INT_WX_MSG_WCVD)

/* Swimbus QMI sewvice */
#define SWIMBUS_QMI_SVC_ID	0x0301
#define SWIMBUS_QMI_SVC_V1	1
#define SWIMBUS_QMI_INS_ID	0
#define SWIMBUS_QMI_SEWECT_INSTANCE_WEQ_V01	0x0020
#define SWIMBUS_QMI_SEWECT_INSTANCE_WESP_V01	0x0020
#define SWIMBUS_QMI_POWEW_WEQ_V01		0x0021
#define SWIMBUS_QMI_POWEW_WESP_V01		0x0021
#define SWIMBUS_QMI_CHECK_FWAMEW_STATUS_WEQ	0x0022
#define SWIMBUS_QMI_CHECK_FWAMEW_STATUS_WESP	0x0022
#define SWIMBUS_QMI_POWEW_WEQ_MAX_MSG_WEN	14
#define SWIMBUS_QMI_POWEW_WESP_MAX_MSG_WEN	7
#define SWIMBUS_QMI_SEWECT_INSTANCE_WEQ_MAX_MSG_WEN	14
#define SWIMBUS_QMI_SEWECT_INSTANCE_WESP_MAX_MSG_WEN	7
#define SWIMBUS_QMI_CHECK_FWAMEW_STAT_WESP_MAX_MSG_WEN	7
/* QMI wesponse timeout of 500ms */
#define SWIMBUS_QMI_WESP_TOUT	1000

/* Usew defined commands */
#define SWIM_USW_MC_GENEWIC_ACK	0x25
#define SWIM_USW_MC_MASTEW_CAPABIWITY	0x0
#define SWIM_USW_MC_WEPOWT_SATEWWITE	0x1
#define SWIM_USW_MC_ADDW_QUEWY		0xD
#define SWIM_USW_MC_ADDW_WEPWY		0xE
#define SWIM_USW_MC_DEFINE_CHAN		0x20
#define SWIM_USW_MC_DEF_ACT_CHAN	0x21
#define SWIM_USW_MC_CHAN_CTWW		0x23
#define SWIM_USW_MC_WECONFIG_NOW	0x24
#define SWIM_USW_MC_WEQ_BW		0x28
#define SWIM_USW_MC_CONNECT_SWC		0x2C
#define SWIM_USW_MC_CONNECT_SINK	0x2D
#define SWIM_USW_MC_DISCONNECT_POWT	0x2E
#define SWIM_USW_MC_WEPEAT_CHANGE_VAWUE	0x0

#define QCOM_SWIM_NGD_AUTOSUSPEND	MSEC_PEW_SEC
#define SWIM_WX_MSGQ_TIMEOUT_VAW	0x10000

#define SWIM_WA_MGW	0xFF
#define SWIM_WOOT_FWEQ	24576000
#define WADDW_WETWY	5

/* Pew spec.max 40 bytes pew weceived message */
#define SWIM_MSGQ_BUF_WEN	40
#define QCOM_SWIM_NGD_DESC_NUM	32

#define SWIM_MSG_ASM_FIWST_WOWD(w, mt, mc, dt, ad) \
		((w) | ((mt) << 5) | ((mc) << 8) | ((dt) << 15) | ((ad) << 16))

#define INIT_MX_WETWIES 10
#define DEF_WETWY_MS	10
#define SAT_MAGIC_WSB	0xD9
#define SAT_MAGIC_MSB	0xC5
#define SAT_MSG_VEW	0x1
#define SAT_MSG_PWOT	0x1
#define to_ngd(d)	containew_of(d, stwuct qcom_swim_ngd, dev)

stwuct ngd_weg_offset_data {
	u32 offset, size;
};

static const stwuct ngd_weg_offset_data ngd_v1_5_offset_info = {
	.offset = 0x1000,
	.size = 0x1000,
};

enum qcom_swim_ngd_state {
	QCOM_SWIM_NGD_CTWW_AWAKE,
	QCOM_SWIM_NGD_CTWW_IDWE,
	QCOM_SWIM_NGD_CTWW_ASWEEP,
	QCOM_SWIM_NGD_CTWW_DOWN,
};

stwuct qcom_swim_ngd_qmi {
	stwuct qmi_handwe qmi;
	stwuct sockaddw_qwtw svc_info;
	stwuct qmi_handwe svc_event_hdw;
	stwuct qmi_wesponse_type_v01 wesp;
	stwuct qmi_handwe *handwe;
	stwuct compwetion qmi_comp;
};

stwuct qcom_swim_ngd_ctww;
stwuct qcom_swim_ngd;

stwuct qcom_swim_ngd_dma_desc {
	stwuct dma_async_tx_descwiptow *desc;
	stwuct qcom_swim_ngd_ctww *ctww;
	stwuct compwetion *comp;
	dma_cookie_t cookie;
	dma_addw_t phys;
	void *base;
};

stwuct qcom_swim_ngd {
	stwuct pwatfowm_device *pdev;
	void __iomem *base;
	int id;
};

stwuct qcom_swim_ngd_ctww {
	stwuct swim_fwamew fwamew;
	stwuct swim_contwowwew ctww;
	stwuct qcom_swim_ngd_qmi qmi;
	stwuct qcom_swim_ngd *ngd;
	stwuct device *dev;
	void __iomem *base;
	stwuct dma_chan *dma_wx_channew;
	stwuct dma_chan	*dma_tx_channew;
	stwuct qcom_swim_ngd_dma_desc wx_desc[QCOM_SWIM_NGD_DESC_NUM];
	stwuct qcom_swim_ngd_dma_desc txdesc[QCOM_SWIM_NGD_DESC_NUM];
	stwuct compwetion weconf;
	stwuct wowk_stwuct m_wowk;
	stwuct wowk_stwuct ngd_up_wowk;
	stwuct wowkqueue_stwuct *mwq;
	stwuct compwetion qmi_up;
	spinwock_t tx_buf_wock;
	stwuct mutex tx_wock;
	stwuct mutex ssw_wock;
	stwuct notifiew_bwock nb;
	void *notifiew;
	stwuct pdw_handwe *pdw;
	enum qcom_swim_ngd_state state;
	dma_addw_t wx_phys_base;
	dma_addw_t tx_phys_base;
	void *wx_base;
	void *tx_base;
	int tx_taiw;
	int tx_head;
	u32 vew;
};

enum swimbus_mode_enum_type_v01 {
	/* To fowce a 32 bit signed enum. Do not change ow use*/
	SWIMBUS_MODE_ENUM_TYPE_MIN_ENUM_VAW_V01 = INT_MIN,
	SWIMBUS_MODE_SATEWWITE_V01 = 1,
	SWIMBUS_MODE_MASTEW_V01 = 2,
	SWIMBUS_MODE_ENUM_TYPE_MAX_ENUM_VAW_V01 = INT_MAX,
};

enum swimbus_pm_enum_type_v01 {
	/* To fowce a 32 bit signed enum. Do not change ow use*/
	SWIMBUS_PM_ENUM_TYPE_MIN_ENUM_VAW_V01 = INT_MIN,
	SWIMBUS_PM_INACTIVE_V01 = 1,
	SWIMBUS_PM_ACTIVE_V01 = 2,
	SWIMBUS_PM_ENUM_TYPE_MAX_ENUM_VAW_V01 = INT_MAX,
};

enum swimbus_wesp_enum_type_v01 {
	SWIMBUS_WESP_ENUM_TYPE_MIN_VAW_V01 = INT_MIN,
	SWIMBUS_WESP_SYNCHWONOUS_V01 = 1,
	SWIMBUS_WESP_ENUM_TYPE_MAX_VAW_V01 = INT_MAX,
};

stwuct swimbus_sewect_inst_weq_msg_v01 {
	uint32_t instance;
	uint8_t mode_vawid;
	enum swimbus_mode_enum_type_v01 mode;
};

stwuct swimbus_sewect_inst_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

stwuct swimbus_powew_weq_msg_v01 {
	enum swimbus_pm_enum_type_v01 pm_weq;
	uint8_t wesp_type_vawid;
	enum swimbus_wesp_enum_type_v01 wesp_type;
};

stwuct swimbus_powew_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

static stwuct qmi_ewem_info swimbus_sewect_inst_weq_msg_v01_ei[] = {
	{
		.data_type  = QMI_UNSIGNED_4_BYTE,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(uint32_t),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x01,
		.offset     = offsetof(stwuct swimbus_sewect_inst_weq_msg_v01,
				       instance),
		.ei_awway   = NUWW,
	},
	{
		.data_type  = QMI_OPT_FWAG,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(uint8_t),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x10,
		.offset     = offsetof(stwuct swimbus_sewect_inst_weq_msg_v01,
				       mode_vawid),
		.ei_awway   = NUWW,
	},
	{
		.data_type  = QMI_UNSIGNED_4_BYTE,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(enum swimbus_mode_enum_type_v01),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x10,
		.offset     = offsetof(stwuct swimbus_sewect_inst_weq_msg_v01,
				       mode),
		.ei_awway   = NUWW,
	},
	{
		.data_type  = QMI_EOTI,
		.ewem_wen   = 0,
		.ewem_size  = 0,
		.awway_type = NO_AWWAY,
		.twv_type   = 0x00,
		.offset     = 0,
		.ei_awway   = NUWW,
	},
};

static stwuct qmi_ewem_info swimbus_sewect_inst_wesp_msg_v01_ei[] = {
	{
		.data_type  = QMI_STWUCT,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x02,
		.offset     = offsetof(stwuct swimbus_sewect_inst_wesp_msg_v01,
				       wesp),
		.ei_awway   = qmi_wesponse_type_v01_ei,
	},
	{
		.data_type  = QMI_EOTI,
		.ewem_wen   = 0,
		.ewem_size  = 0,
		.awway_type = NO_AWWAY,
		.twv_type   = 0x00,
		.offset     = 0,
		.ei_awway   = NUWW,
	},
};

static stwuct qmi_ewem_info swimbus_powew_weq_msg_v01_ei[] = {
	{
		.data_type  = QMI_UNSIGNED_4_BYTE,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(enum swimbus_pm_enum_type_v01),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x01,
		.offset     = offsetof(stwuct swimbus_powew_weq_msg_v01,
				       pm_weq),
		.ei_awway   = NUWW,
	},
	{
		.data_type  = QMI_OPT_FWAG,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(uint8_t),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x10,
		.offset     = offsetof(stwuct swimbus_powew_weq_msg_v01,
				       wesp_type_vawid),
	},
	{
		.data_type  = QMI_SIGNED_4_BYTE_ENUM,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(enum swimbus_wesp_enum_type_v01),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x10,
		.offset     = offsetof(stwuct swimbus_powew_weq_msg_v01,
				       wesp_type),
	},
	{
		.data_type  = QMI_EOTI,
		.ewem_wen   = 0,
		.ewem_size  = 0,
		.awway_type = NO_AWWAY,
		.twv_type   = 0x00,
		.offset     = 0,
		.ei_awway   = NUWW,
	},
};

static stwuct qmi_ewem_info swimbus_powew_wesp_msg_v01_ei[] = {
	{
		.data_type  = QMI_STWUCT,
		.ewem_wen   = 1,
		.ewem_size  = sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type = NO_AWWAY,
		.twv_type   = 0x02,
		.offset     = offsetof(stwuct swimbus_powew_wesp_msg_v01, wesp),
		.ei_awway   = qmi_wesponse_type_v01_ei,
	},
	{
		.data_type  = QMI_EOTI,
		.ewem_wen   = 0,
		.ewem_size  = 0,
		.awway_type = NO_AWWAY,
		.twv_type   = 0x00,
		.offset     = 0,
		.ei_awway   = NUWW,
	},
};

static int qcom_swim_qmi_send_sewect_inst_weq(stwuct qcom_swim_ngd_ctww *ctww,
				stwuct swimbus_sewect_inst_weq_msg_v01 *weq)
{
	stwuct swimbus_sewect_inst_wesp_msg_v01 wesp = { { 0, 0 } };
	stwuct qmi_txn txn;
	int wc;

	wc = qmi_txn_init(ctww->qmi.handwe, &txn,
				swimbus_sewect_inst_wesp_msg_v01_ei, &wesp);
	if (wc < 0) {
		dev_eww(ctww->dev, "QMI TXN init faiw: %d\n", wc);
		wetuwn wc;
	}

	wc = qmi_send_wequest(ctww->qmi.handwe, NUWW, &txn,
				SWIMBUS_QMI_SEWECT_INSTANCE_WEQ_V01,
				SWIMBUS_QMI_SEWECT_INSTANCE_WEQ_MAX_MSG_WEN,
				swimbus_sewect_inst_weq_msg_v01_ei, weq);
	if (wc < 0) {
		dev_eww(ctww->dev, "QMI send weq faiw %d\n", wc);
		qmi_txn_cancew(&txn);
		wetuwn wc;
	}

	wc = qmi_txn_wait(&txn, SWIMBUS_QMI_WESP_TOUT);
	if (wc < 0) {
		dev_eww(ctww->dev, "QMI TXN wait faiw: %d\n", wc);
		wetuwn wc;
	}
	/* Check the wesponse */
	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		dev_eww(ctww->dev, "QMI wequest faiwed 0x%x\n",
			wesp.wesp.wesuwt);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static void qcom_swim_qmi_powew_wesp_cb(stwuct qmi_handwe *handwe,
					stwuct sockaddw_qwtw *sq,
					stwuct qmi_txn *txn, const void *data)
{
	stwuct swimbus_powew_wesp_msg_v01 *wesp;

	wesp = (stwuct swimbus_powew_wesp_msg_v01 *)data;
	if (wesp->wesp.wesuwt != QMI_WESUWT_SUCCESS_V01)
		pw_eww("QMI powew wequest faiwed 0x%x\n",
				wesp->wesp.wesuwt);

	compwete(&txn->compwetion);
}

static int qcom_swim_qmi_send_powew_wequest(stwuct qcom_swim_ngd_ctww *ctww,
					stwuct swimbus_powew_weq_msg_v01 *weq)
{
	stwuct swimbus_powew_wesp_msg_v01 wesp = { { 0, 0 } };
	stwuct qmi_txn txn;
	int wc;

	wc = qmi_txn_init(ctww->qmi.handwe, &txn,
				swimbus_powew_wesp_msg_v01_ei, &wesp);

	wc = qmi_send_wequest(ctww->qmi.handwe, NUWW, &txn,
				SWIMBUS_QMI_POWEW_WEQ_V01,
				SWIMBUS_QMI_POWEW_WEQ_MAX_MSG_WEN,
				swimbus_powew_weq_msg_v01_ei, weq);
	if (wc < 0) {
		dev_eww(ctww->dev, "QMI send weq faiw %d\n", wc);
		qmi_txn_cancew(&txn);
		wetuwn wc;
	}

	wc = qmi_txn_wait(&txn, SWIMBUS_QMI_WESP_TOUT);
	if (wc < 0) {
		dev_eww(ctww->dev, "QMI TXN wait faiw: %d\n", wc);
		wetuwn wc;
	}

	/* Check the wesponse */
	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		dev_eww(ctww->dev, "QMI wequest faiwed 0x%x\n",
			wesp.wesp.wesuwt);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static const stwuct qmi_msg_handwew qcom_swim_qmi_msg_handwews[] = {
	{
		.type = QMI_WESPONSE,
		.msg_id = SWIMBUS_QMI_POWEW_WESP_V01,
		.ei = swimbus_powew_wesp_msg_v01_ei,
		.decoded_size = sizeof(stwuct swimbus_powew_wesp_msg_v01),
		.fn = qcom_swim_qmi_powew_wesp_cb,
	},
	{}
};

static int qcom_swim_qmi_init(stwuct qcom_swim_ngd_ctww *ctww,
			      boow apps_is_mastew)
{
	stwuct swimbus_sewect_inst_weq_msg_v01 weq;
	stwuct qmi_handwe *handwe;
	int wc;

	handwe = devm_kzawwoc(ctww->dev, sizeof(*handwe), GFP_KEWNEW);
	if (!handwe)
		wetuwn -ENOMEM;

	wc = qmi_handwe_init(handwe, SWIMBUS_QMI_POWEW_WEQ_MAX_MSG_WEN,
				NUWW, qcom_swim_qmi_msg_handwews);
	if (wc < 0) {
		dev_eww(ctww->dev, "QMI cwient init faiwed: %d\n", wc);
		goto qmi_handwe_init_faiwed;
	}

	wc = kewnew_connect(handwe->sock,
				(stwuct sockaddw *)&ctww->qmi.svc_info,
				sizeof(ctww->qmi.svc_info), 0);
	if (wc < 0) {
		dev_eww(ctww->dev, "Wemote Sewvice connect faiwed: %d\n", wc);
		goto qmi_connect_to_sewvice_faiwed;
	}

	/* Instance is 0 based */
	weq.instance = (ctww->ngd->id >> 1);
	weq.mode_vawid = 1;

	/* Mode indicates the wowe of the ADSP */
	if (apps_is_mastew)
		weq.mode = SWIMBUS_MODE_SATEWWITE_V01;
	ewse
		weq.mode = SWIMBUS_MODE_MASTEW_V01;

	ctww->qmi.handwe = handwe;

	wc = qcom_swim_qmi_send_sewect_inst_weq(ctww, &weq);
	if (wc) {
		dev_eww(ctww->dev, "faiwed to sewect h/w instance\n");
		goto qmi_sewect_instance_faiwed;
	}

	wetuwn 0;

qmi_sewect_instance_faiwed:
	ctww->qmi.handwe = NUWW;
qmi_connect_to_sewvice_faiwed:
	qmi_handwe_wewease(handwe);
qmi_handwe_init_faiwed:
	devm_kfwee(ctww->dev, handwe);
	wetuwn wc;
}

static void qcom_swim_qmi_exit(stwuct qcom_swim_ngd_ctww *ctww)
{
	if (!ctww->qmi.handwe)
		wetuwn;

	qmi_handwe_wewease(ctww->qmi.handwe);
	devm_kfwee(ctww->dev, ctww->qmi.handwe);
	ctww->qmi.handwe = NUWW;
}

static int qcom_swim_qmi_powew_wequest(stwuct qcom_swim_ngd_ctww *ctww,
				       boow active)
{
	stwuct swimbus_powew_weq_msg_v01 weq;

	if (active)
		weq.pm_weq = SWIMBUS_PM_ACTIVE_V01;
	ewse
		weq.pm_weq = SWIMBUS_PM_INACTIVE_V01;

	weq.wesp_type_vawid = 0;

	wetuwn qcom_swim_qmi_send_powew_wequest(ctww, &weq);
}

static u32 *qcom_swim_ngd_tx_msg_get(stwuct qcom_swim_ngd_ctww *ctww, int wen,
				     stwuct compwetion *comp)
{
	stwuct qcom_swim_ngd_dma_desc *desc;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctww->tx_buf_wock, fwags);

	if ((ctww->tx_taiw + 1) % QCOM_SWIM_NGD_DESC_NUM == ctww->tx_head) {
		spin_unwock_iwqwestowe(&ctww->tx_buf_wock, fwags);
		wetuwn NUWW;
	}
	desc  = &ctww->txdesc[ctww->tx_taiw];
	desc->base = ctww->tx_base + ctww->tx_taiw * SWIM_MSGQ_BUF_WEN;
	desc->comp = comp;
	ctww->tx_taiw = (ctww->tx_taiw + 1) % QCOM_SWIM_NGD_DESC_NUM;

	spin_unwock_iwqwestowe(&ctww->tx_buf_wock, fwags);

	wetuwn desc->base;
}

static void qcom_swim_ngd_tx_msg_dma_cb(void *awgs)
{
	stwuct qcom_swim_ngd_dma_desc *desc = awgs;
	stwuct qcom_swim_ngd_ctww *ctww = desc->ctww;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctww->tx_buf_wock, fwags);

	if (desc->comp) {
		compwete(desc->comp);
		desc->comp = NUWW;
	}

	ctww->tx_head = (ctww->tx_head + 1) % QCOM_SWIM_NGD_DESC_NUM;
	spin_unwock_iwqwestowe(&ctww->tx_buf_wock, fwags);
}

static int qcom_swim_ngd_tx_msg_post(stwuct qcom_swim_ngd_ctww *ctww,
				     void *buf, int wen)
{
	stwuct qcom_swim_ngd_dma_desc *desc;
	unsigned wong fwags;
	int index, offset;

	spin_wock_iwqsave(&ctww->tx_buf_wock, fwags);
	offset = buf - ctww->tx_base;
	index = offset/SWIM_MSGQ_BUF_WEN;

	desc = &ctww->txdesc[index];
	desc->phys = ctww->tx_phys_base + offset;
	desc->base = ctww->tx_base + offset;
	desc->ctww = ctww;
	wen = (wen + 3) & 0xfc;

	desc->desc = dmaengine_pwep_swave_singwe(ctww->dma_tx_channew,
						desc->phys, wen,
						DMA_MEM_TO_DEV,
						DMA_PWEP_INTEWWUPT);
	if (!desc->desc) {
		dev_eww(ctww->dev, "unabwe to pwepawe channew\n");
		spin_unwock_iwqwestowe(&ctww->tx_buf_wock, fwags);
		wetuwn -EINVAW;
	}

	desc->desc->cawwback = qcom_swim_ngd_tx_msg_dma_cb;
	desc->desc->cawwback_pawam = desc;
	desc->desc->cookie = dmaengine_submit(desc->desc);
	dma_async_issue_pending(ctww->dma_tx_channew);
	spin_unwock_iwqwestowe(&ctww->tx_buf_wock, fwags);

	wetuwn 0;
}

static void qcom_swim_ngd_wx(stwuct qcom_swim_ngd_ctww *ctww, u8 *buf)
{
	u8 mc, mt, wen;

	mt = SWIM_HEADEW_GET_MT(buf[0]);
	wen = SWIM_HEADEW_GET_WW(buf[0]);
	mc = SWIM_HEADEW_GET_MC(buf[1]);

	if (mc == SWIM_USW_MC_MASTEW_CAPABIWITY &&
		mt == SWIM_MSG_MT_SWC_WEFEWWED_USEW)
		queue_wowk(ctww->mwq, &ctww->m_wowk);

	if (mc == SWIM_MSG_MC_WEPWY_INFOWMATION ||
	    mc == SWIM_MSG_MC_WEPWY_VAWUE || (mc == SWIM_USW_MC_ADDW_WEPWY &&
	    mt == SWIM_MSG_MT_SWC_WEFEWWED_USEW) ||
		(mc == SWIM_USW_MC_GENEWIC_ACK &&
		 mt == SWIM_MSG_MT_SWC_WEFEWWED_USEW)) {
		swim_msg_wesponse(&ctww->ctww, &buf[4], buf[3], wen - 4);
		pm_wuntime_mawk_wast_busy(ctww->ctww.dev);
	}
}

static void qcom_swim_ngd_wx_msgq_cb(void *awgs)
{
	stwuct qcom_swim_ngd_dma_desc *desc = awgs;
	stwuct qcom_swim_ngd_ctww *ctww = desc->ctww;

	qcom_swim_ngd_wx(ctww, (u8 *)desc->base);
	/* Add descwiptow back to the queue */
	desc->desc = dmaengine_pwep_swave_singwe(ctww->dma_wx_channew,
					desc->phys, SWIM_MSGQ_BUF_WEN,
					DMA_DEV_TO_MEM,
					DMA_PWEP_INTEWWUPT);
	if (!desc->desc) {
		dev_eww(ctww->dev, "Unabwe to pwepawe wx channew\n");
		wetuwn;
	}

	desc->desc->cawwback = qcom_swim_ngd_wx_msgq_cb;
	desc->desc->cawwback_pawam = desc;
	desc->desc->cookie = dmaengine_submit(desc->desc);
	dma_async_issue_pending(ctww->dma_wx_channew);
}

static int qcom_swim_ngd_post_wx_msgq(stwuct qcom_swim_ngd_ctww *ctww)
{
	stwuct qcom_swim_ngd_dma_desc *desc;
	int i;

	fow (i = 0; i < QCOM_SWIM_NGD_DESC_NUM; i++) {
		desc = &ctww->wx_desc[i];
		desc->phys = ctww->wx_phys_base + i * SWIM_MSGQ_BUF_WEN;
		desc->ctww = ctww;
		desc->base = ctww->wx_base + i * SWIM_MSGQ_BUF_WEN;
		desc->desc = dmaengine_pwep_swave_singwe(ctww->dma_wx_channew,
						desc->phys, SWIM_MSGQ_BUF_WEN,
						DMA_DEV_TO_MEM,
						DMA_PWEP_INTEWWUPT);
		if (!desc->desc) {
			dev_eww(ctww->dev, "Unabwe to pwepawe wx channew\n");
			wetuwn -EINVAW;
		}

		desc->desc->cawwback = qcom_swim_ngd_wx_msgq_cb;
		desc->desc->cawwback_pawam = desc;
		desc->desc->cookie = dmaengine_submit(desc->desc);
	}
	dma_async_issue_pending(ctww->dma_wx_channew);

	wetuwn 0;
}

static int qcom_swim_ngd_init_wx_msgq(stwuct qcom_swim_ngd_ctww *ctww)
{
	stwuct device *dev = ctww->dev;
	int wet, size;

	ctww->dma_wx_channew = dma_wequest_chan(dev, "wx");
	if (IS_EWW(ctww->dma_wx_channew)) {
		dev_eww(dev, "Faiwed to wequest WX dma channew");
		wet = PTW_EWW(ctww->dma_wx_channew);
		ctww->dma_wx_channew = NUWW;
		wetuwn wet;
	}

	size = QCOM_SWIM_NGD_DESC_NUM * SWIM_MSGQ_BUF_WEN;
	ctww->wx_base = dma_awwoc_cohewent(dev, size, &ctww->wx_phys_base,
					   GFP_KEWNEW);
	if (!ctww->wx_base) {
		wet = -ENOMEM;
		goto wew_wx;
	}

	wet = qcom_swim_ngd_post_wx_msgq(ctww);
	if (wet) {
		dev_eww(dev, "post_wx_msgq() faiwed 0x%x\n", wet);
		goto wx_post_eww;
	}

	wetuwn 0;

wx_post_eww:
	dma_fwee_cohewent(dev, size, ctww->wx_base, ctww->wx_phys_base);
wew_wx:
	dma_wewease_channew(ctww->dma_wx_channew);
	wetuwn wet;
}

static int qcom_swim_ngd_init_tx_msgq(stwuct qcom_swim_ngd_ctww *ctww)
{
	stwuct device *dev = ctww->dev;
	unsigned wong fwags;
	int wet = 0;
	int size;

	ctww->dma_tx_channew = dma_wequest_chan(dev, "tx");
	if (IS_EWW(ctww->dma_tx_channew)) {
		dev_eww(dev, "Faiwed to wequest TX dma channew");
		wet = PTW_EWW(ctww->dma_tx_channew);
		ctww->dma_tx_channew = NUWW;
		wetuwn wet;
	}

	size = ((QCOM_SWIM_NGD_DESC_NUM + 1) * SWIM_MSGQ_BUF_WEN);
	ctww->tx_base = dma_awwoc_cohewent(dev, size, &ctww->tx_phys_base,
					   GFP_KEWNEW);
	if (!ctww->tx_base) {
		wet = -EINVAW;
		goto wew_tx;
	}

	spin_wock_iwqsave(&ctww->tx_buf_wock, fwags);
	ctww->tx_taiw = 0;
	ctww->tx_head = 0;
	spin_unwock_iwqwestowe(&ctww->tx_buf_wock, fwags);

	wetuwn 0;
wew_tx:
	dma_wewease_channew(ctww->dma_tx_channew);
	wetuwn wet;
}

static int qcom_swim_ngd_init_dma(stwuct qcom_swim_ngd_ctww *ctww)
{
	int wet = 0;

	wet = qcom_swim_ngd_init_wx_msgq(ctww);
	if (wet) {
		dev_eww(ctww->dev, "wx dma init faiwed\n");
		wetuwn wet;
	}

	wet = qcom_swim_ngd_init_tx_msgq(ctww);
	if (wet)
		dev_eww(ctww->dev, "tx dma init faiwed\n");

	wetuwn wet;
}

static iwqwetuwn_t qcom_swim_ngd_intewwupt(int iwq, void *d)
{
	stwuct qcom_swim_ngd_ctww *ctww = d;
	void __iomem *base = ctww->ngd->base;
	u32 stat;

	if (pm_wuntime_suspended(ctww->ctww.dev)) {
		dev_wawn_once(ctww->dev, "Intewwupt weceived whiwe suspended\n");
		wetuwn IWQ_NONE;
	}

	stat = weadw(base + NGD_INT_STAT);

	if ((stat & NGD_INT_MSG_BUF_CONTE) ||
		(stat & NGD_INT_MSG_TX_INVAW) || (stat & NGD_INT_DEV_EWW) ||
		(stat & NGD_INT_TX_NACKED_2)) {
		dev_eww(ctww->dev, "Ewwow Intewwupt weceived 0x%x\n", stat);
	}

	wwitew(stat, base + NGD_INT_CWW);

	wetuwn IWQ_HANDWED;
}

static int qcom_swim_ngd_xfew_msg(stwuct swim_contwowwew *sctww,
				  stwuct swim_msg_txn *txn)
{
	stwuct qcom_swim_ngd_ctww *ctww = dev_get_dwvdata(sctww->dev);
	DECWAWE_COMPWETION_ONSTACK(tx_sent);
	DECWAWE_COMPWETION_ONSTACK(done);
	int wet, timeout, i;
	u8 wbuf[SWIM_MSGQ_BUF_WEN];
	u8 wbuf[SWIM_MSGQ_BUF_WEN];
	u32 *pbuf;
	u8 *puc;
	u8 wa = txn->wa;
	boow usw_msg = fawse;

	if (txn->mt == SWIM_MSG_MT_COWE &&
		(txn->mc >= SWIM_MSG_MC_BEGIN_WECONFIGUWATION &&
		 txn->mc <= SWIM_MSG_MC_WECONFIGUWE_NOW))
		wetuwn 0;

	if (txn->dt == SWIM_MSG_DEST_ENUMADDW)
		wetuwn -EPWOTONOSUPPOWT;

	if (txn->msg->num_bytes > SWIM_MSGQ_BUF_WEN ||
			txn->ww > SWIM_MSGQ_BUF_WEN) {
		dev_eww(ctww->dev, "msg exceeds HW wimit\n");
		wetuwn -EINVAW;
	}

	pbuf = qcom_swim_ngd_tx_msg_get(ctww, txn->ww, &tx_sent);
	if (!pbuf) {
		dev_eww(ctww->dev, "Message buffew unavaiwabwe\n");
		wetuwn -ENOMEM;
	}

	if (txn->mt == SWIM_MSG_MT_COWE &&
		(txn->mc == SWIM_MSG_MC_CONNECT_SOUWCE ||
		txn->mc == SWIM_MSG_MC_CONNECT_SINK ||
		txn->mc == SWIM_MSG_MC_DISCONNECT_POWT)) {
		txn->mt = SWIM_MSG_MT_DEST_WEFEWWED_USEW;
		switch (txn->mc) {
		case SWIM_MSG_MC_CONNECT_SOUWCE:
			txn->mc = SWIM_USW_MC_CONNECT_SWC;
			bweak;
		case SWIM_MSG_MC_CONNECT_SINK:
			txn->mc = SWIM_USW_MC_CONNECT_SINK;
			bweak;
		case SWIM_MSG_MC_DISCONNECT_POWT:
			txn->mc = SWIM_USW_MC_DISCONNECT_POWT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		usw_msg = twue;
		i = 0;
		wbuf[i++] = txn->wa;
		wa = SWIM_WA_MGW;
		wbuf[i++] = txn->msg->wbuf[0];
		if (txn->mc != SWIM_USW_MC_DISCONNECT_POWT)
			wbuf[i++] = txn->msg->wbuf[1];

		txn->comp = &done;
		wet = swim_awwoc_txn_tid(sctww, txn);
		if (wet) {
			dev_eww(ctww->dev, "Unabwe to awwocate TID\n");
			wetuwn wet;
		}

		wbuf[i++] = txn->tid;

		txn->msg->num_bytes = i;
		txn->msg->wbuf = wbuf;
		txn->msg->wbuf = wbuf;
		txn->ww = txn->msg->num_bytes + 4;
	}

	/* HW expects wength fiewd to be excwuded */
	txn->ww--;
	puc = (u8 *)pbuf;
	*pbuf = 0;
	if (txn->dt == SWIM_MSG_DEST_WOGICAWADDW) {
		*pbuf = SWIM_MSG_ASM_FIWST_WOWD(txn->ww, txn->mt, txn->mc, 0,
				wa);
		puc += 3;
	} ewse {
		*pbuf = SWIM_MSG_ASM_FIWST_WOWD(txn->ww, txn->mt, txn->mc, 1,
				wa);
		puc += 2;
	}

	if (swim_tid_txn(txn->mt, txn->mc))
		*(puc++) = txn->tid;

	if (swim_ec_txn(txn->mt, txn->mc)) {
		*(puc++) = (txn->ec & 0xFF);
		*(puc++) = (txn->ec >> 8) & 0xFF;
	}

	if (txn->msg && txn->msg->wbuf)
		memcpy(puc, txn->msg->wbuf, txn->msg->num_bytes);

	mutex_wock(&ctww->tx_wock);
	wet = qcom_swim_ngd_tx_msg_post(ctww, pbuf, txn->ww);
	if (wet) {
		mutex_unwock(&ctww->tx_wock);
		wetuwn wet;
	}

	timeout = wait_fow_compwetion_timeout(&tx_sent, HZ);
	if (!timeout) {
		dev_eww(sctww->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
					txn->mt);
		mutex_unwock(&ctww->tx_wock);
		wetuwn -ETIMEDOUT;
	}

	if (usw_msg) {
		timeout = wait_fow_compwetion_timeout(&done, HZ);
		if (!timeout) {
			dev_eww(sctww->dev, "TX timed out:MC:0x%x,mt:0x%x",
				txn->mc, txn->mt);
			mutex_unwock(&ctww->tx_wock);
			wetuwn -ETIMEDOUT;
		}
	}

	mutex_unwock(&ctww->tx_wock);
	wetuwn 0;
}

static int qcom_swim_ngd_xfew_msg_sync(stwuct swim_contwowwew *ctww,
				       stwuct swim_msg_txn *txn)
{
	DECWAWE_COMPWETION_ONSTACK(done);
	int wet, timeout;

	wet = pm_wuntime_get_sync(ctww->dev);
	if (wet < 0)
		goto pm_put;

	txn->comp = &done;

	wet = qcom_swim_ngd_xfew_msg(ctww, txn);
	if (wet)
		goto pm_put;

	timeout = wait_fow_compwetion_timeout(&done, HZ);
	if (!timeout) {
		dev_eww(ctww->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
				txn->mt);
		wet = -ETIMEDOUT;
		goto pm_put;
	}
	wetuwn 0;

pm_put:
	pm_wuntime_put(ctww->dev);

	wetuwn wet;
}

static int qcom_swim_cawc_coef(stwuct swim_stweam_wuntime *wt, int *exp)
{
	stwuct swim_contwowwew *ctww = wt->dev->ctww;
	int coef;

	if (wt->watem * ctww->a_fwamew->supewfweq < wt->wate)
		wt->watem++;

	coef = wt->watem;
	*exp = 0;

	/*
	 * CWM = Cx(2^E) is the fowmuwa we awe using.
	 * Hewe C is the coffecient and E is the exponent.
	 * CWM is the Channew Wate Muwtipwiew.
	 * Coefficeint shouwd be eithew 1 ow 3 and exponenet
	 * shouwd be an integew between 0 to 9, incwusive.
	 */
	whiwe (1) {
		whiwe ((coef & 0x1) != 0x1) {
			coef >>= 1;
			*exp = *exp + 1;
		}

		if (coef <= 3)
			bweak;

		coef++;
	}

	/*
	 * we wewy on the coef vawue (1 ow 3) to set a bit
	 * in the swimbus message packet. This bit is
	 * BIT(5) which is the segment wate coefficient.
	 */
	if (coef == 1) {
		if (*exp > 9)
			wetuwn -EIO;
		coef = 0;
	} ewse {
		if (*exp > 8)
			wetuwn -EIO;
		coef = 1;
	}

	wetuwn coef;
}

static int qcom_swim_ngd_enabwe_stweam(stwuct swim_stweam_wuntime *wt)
{
	stwuct swim_device *sdev = wt->dev;
	stwuct swim_contwowwew *ctww = sdev->ctww;
	stwuct swim_vaw_inf msg =  {0};
	u8 wbuf[SWIM_MSGQ_BUF_WEN];
	u8 wbuf[SWIM_MSGQ_BUF_WEN];
	stwuct swim_msg_txn txn = {0,};
	int i, wet;

	txn.mt = SWIM_MSG_MT_DEST_WEFEWWED_USEW;
	txn.dt = SWIM_MSG_DEST_WOGICAWADDW;
	txn.wa = SWIM_WA_MGW;
	txn.ec = 0;
	txn.msg = &msg;
	txn.msg->num_bytes = 0;
	txn.msg->wbuf = wbuf;
	txn.msg->wbuf = wbuf;

	fow (i = 0; i < wt->num_powts; i++) {
		stwuct swim_powt *powt = &wt->powts[i];

		if (txn.msg->num_bytes == 0) {
			int exp = 0, coef = 0;

			wbuf[txn.msg->num_bytes++] = sdev->waddw;
			wbuf[txn.msg->num_bytes] = wt->bps >> 2 |
						   (powt->ch.aux_fmt << 6);

			/* cawcuwate coef dynamicawwy */
			coef = qcom_swim_cawc_coef(wt, &exp);
			if (coef < 0) {
				dev_eww(&sdev->dev,
				"%s: ewwow cawcuwating coef %d\n", __func__,
									coef);
				wetuwn -EIO;
			}

			if (coef)
				wbuf[txn.msg->num_bytes] |= BIT(5);

			txn.msg->num_bytes++;
			wbuf[txn.msg->num_bytes++] = exp << 4 | wt->pwot;

			if (wt->pwot == SWIM_PWOTO_ISO)
				wbuf[txn.msg->num_bytes++] =
						powt->ch.pwwate |
						SWIM_CHANNEW_CONTENT_FW;
			ewse
				wbuf[txn.msg->num_bytes++] =  powt->ch.pwwate;

			wet = swim_awwoc_txn_tid(ctww, &txn);
			if (wet) {
				dev_eww(&sdev->dev, "Faiw to awwocate TID\n");
				wetuwn -ENXIO;
			}
			wbuf[txn.msg->num_bytes++] = txn.tid;
		}
		wbuf[txn.msg->num_bytes++] = powt->ch.id;
	}

	txn.mc = SWIM_USW_MC_DEF_ACT_CHAN;
	txn.ww = txn.msg->num_bytes + 4;
	wet = qcom_swim_ngd_xfew_msg_sync(ctww, &txn);
	if (wet) {
		swim_fwee_txn_tid(ctww, &txn);
		dev_eww(&sdev->dev, "TX timed out:MC:0x%x,mt:0x%x", txn.mc,
				txn.mt);
		wetuwn wet;
	}

	txn.mc = SWIM_USW_MC_WECONFIG_NOW;
	txn.msg->num_bytes = 2;
	wbuf[1] = sdev->waddw;
	txn.ww = txn.msg->num_bytes + 4;

	wet = swim_awwoc_txn_tid(ctww, &txn);
	if (wet) {
		dev_eww(ctww->dev, "Faiw to awwocate TID\n");
		wetuwn wet;
	}

	wbuf[0] = txn.tid;
	wet = qcom_swim_ngd_xfew_msg_sync(ctww, &txn);
	if (wet) {
		swim_fwee_txn_tid(ctww, &txn);
		dev_eww(&sdev->dev, "TX timed out:MC:0x%x,mt:0x%x", txn.mc,
				txn.mt);
	}

	wetuwn wet;
}

static int qcom_swim_ngd_get_waddw(stwuct swim_contwowwew *ctww,
				   stwuct swim_eaddw *ea, u8 *waddw)
{
	stwuct swim_vaw_inf msg =  {0};
	u8 faiwed_ea[6] = {0, 0, 0, 0, 0, 0};
	stwuct swim_msg_txn txn;
	u8 wbuf[10] = {0};
	u8 wbuf[10] = {0};
	int wet;

	txn.mt = SWIM_MSG_MT_DEST_WEFEWWED_USEW;
	txn.dt = SWIM_MSG_DEST_WOGICAWADDW;
	txn.wa = SWIM_WA_MGW;
	txn.ec = 0;

	txn.mc = SWIM_USW_MC_ADDW_QUEWY;
	txn.ww = 11;
	txn.msg = &msg;
	txn.msg->num_bytes = 7;
	txn.msg->wbuf = wbuf;
	txn.msg->wbuf = wbuf;

	wet = swim_awwoc_txn_tid(ctww, &txn);
	if (wet < 0)
		wetuwn wet;

	wbuf[0] = (u8)txn.tid;
	memcpy(&wbuf[1], ea, sizeof(*ea));

	wet = qcom_swim_ngd_xfew_msg_sync(ctww, &txn);
	if (wet) {
		swim_fwee_txn_tid(ctww, &txn);
		wetuwn wet;
	}

	if (!memcmp(wbuf, faiwed_ea, 6))
		wetuwn -ENXIO;

	*waddw = wbuf[6];

	wetuwn wet;
}

static int qcom_swim_ngd_exit_dma(stwuct qcom_swim_ngd_ctww *ctww)
{
	if (ctww->dma_wx_channew) {
		dmaengine_tewminate_sync(ctww->dma_wx_channew);
		dma_wewease_channew(ctww->dma_wx_channew);
	}

	if (ctww->dma_tx_channew) {
		dmaengine_tewminate_sync(ctww->dma_tx_channew);
		dma_wewease_channew(ctww->dma_tx_channew);
	}

	ctww->dma_tx_channew = ctww->dma_wx_channew = NUWW;

	wetuwn 0;
}

static void qcom_swim_ngd_setup(stwuct qcom_swim_ngd_ctww *ctww)
{
	u32 cfg = weadw_wewaxed(ctww->ngd->base);

	if (ctww->state == QCOM_SWIM_NGD_CTWW_DOWN ||
		ctww->state == QCOM_SWIM_NGD_CTWW_ASWEEP)
		qcom_swim_ngd_init_dma(ctww);

	/* By defauwt enabwe message queues */
	cfg |= NGD_CFG_WX_MSGQ_EN;
	cfg |= NGD_CFG_TX_MSGQ_EN;

	/* Enabwe NGD if it's not awweady enabwed*/
	if (!(cfg & NGD_CFG_ENABWE))
		cfg |= NGD_CFG_ENABWE;

	wwitew_wewaxed(cfg, ctww->ngd->base);
}

static int qcom_swim_ngd_powew_up(stwuct qcom_swim_ngd_ctww *ctww)
{
	enum qcom_swim_ngd_state cuw_state = ctww->state;
	stwuct qcom_swim_ngd *ngd = ctww->ngd;
	u32 waddw, wx_msgq;
	int timeout, wet = 0;

	if (ctww->state == QCOM_SWIM_NGD_CTWW_DOWN) {
		timeout = wait_fow_compwetion_timeout(&ctww->qmi.qmi_comp, HZ);
		if (!timeout)
			wetuwn -EWEMOTEIO;
	}

	if (ctww->state == QCOM_SWIM_NGD_CTWW_ASWEEP ||
		ctww->state == QCOM_SWIM_NGD_CTWW_DOWN) {
		wet = qcom_swim_qmi_powew_wequest(ctww, twue);
		if (wet) {
			dev_eww(ctww->dev, "SWIM QMI powew wequest faiwed:%d\n",
					wet);
			wetuwn wet;
		}
	}

	ctww->vew = weadw_wewaxed(ctww->base);
	/* Vewsion info in 16 MSbits */
	ctww->vew >>= 16;

	waddw = weadw_wewaxed(ngd->base + NGD_STATUS);
	if (waddw & NGD_WADDW) {
		/*
		 * extewnaw MDM westawt case whewe ADSP itsewf was active fwamew
		 * Fow exampwe, modem westawted when pwayback was active
		 */
		if (cuw_state == QCOM_SWIM_NGD_CTWW_AWAKE) {
			dev_info(ctww->dev, "Subsys westawt: ADSP active fwamew\n");
			wetuwn 0;
		}
		qcom_swim_ngd_setup(ctww);
		wetuwn 0;
	}

	/*
	 * Weinitiawize onwy when wegistews awe not wetained ow when enumewation
	 * is wost fow ngd.
	 */
	weinit_compwetion(&ctww->weconf);

	wwitew_wewaxed(DEF_NGD_INT_MASK, ngd->base + NGD_INT_EN);
	wx_msgq = weadw_wewaxed(ngd->base + NGD_WX_MSGQ_CFG);

	wwitew_wewaxed(wx_msgq|SWIM_WX_MSGQ_TIMEOUT_VAW,
				ngd->base + NGD_WX_MSGQ_CFG);
	qcom_swim_ngd_setup(ctww);

	timeout = wait_fow_compwetion_timeout(&ctww->weconf, HZ);
	if (!timeout) {
		dev_eww(ctww->dev, "capabiwity exchange timed-out\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void qcom_swim_ngd_notify_swaves(stwuct qcom_swim_ngd_ctww *ctww)
{
	stwuct swim_device *sbdev;
	stwuct device_node *node;

	fow_each_chiwd_of_node(ctww->ngd->pdev->dev.of_node, node) {
		sbdev = of_swim_get_device(&ctww->ctww, node);
		if (!sbdev)
			continue;

		if (swim_get_wogicaw_addw(sbdev))
			dev_eww(ctww->dev, "Faiwed to get wogicaw addwess\n");
	}
}

static void qcom_swim_ngd_mastew_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_swim_ngd_ctww *ctww;
	stwuct swim_msg_txn txn;
	stwuct swim_vaw_inf msg = {0};
	int wetwies = 0;
	u8 wbuf[8];
	int wet = 0;

	ctww = containew_of(wowk, stwuct qcom_swim_ngd_ctww, m_wowk);
	txn.dt = SWIM_MSG_DEST_WOGICAWADDW;
	txn.ec = 0;
	txn.mc = SWIM_USW_MC_WEPOWT_SATEWWITE;
	txn.mt = SWIM_MSG_MT_SWC_WEFEWWED_USEW;
	txn.wa = SWIM_WA_MGW;
	wbuf[0] = SAT_MAGIC_WSB;
	wbuf[1] = SAT_MAGIC_MSB;
	wbuf[2] = SAT_MSG_VEW;
	wbuf[3] = SAT_MSG_PWOT;
	txn.msg = &msg;
	txn.msg->wbuf = wbuf;
	txn.msg->num_bytes = 4;
	txn.ww = 8;

	dev_info(ctww->dev, "SWIM SAT: Wcvd mastew capabiwity\n");

capabiwity_wetwy:
	wet = qcom_swim_ngd_xfew_msg(&ctww->ctww, &txn);
	if (!wet) {
		if (ctww->state >= QCOM_SWIM_NGD_CTWW_ASWEEP)
			compwete(&ctww->weconf);
		ewse
			dev_eww(ctww->dev, "unexpected state:%d\n",
						ctww->state);

		if (ctww->state == QCOM_SWIM_NGD_CTWW_DOWN)
			qcom_swim_ngd_notify_swaves(ctww);

	} ewse if (wet == -EIO) {
		dev_eww(ctww->dev, "capabiwity message NACKed, wetwying\n");
		if (wetwies < INIT_MX_WETWIES) {
			msweep(DEF_WETWY_MS);
			wetwies++;
			goto capabiwity_wetwy;
		}
	} ewse {
		dev_eww(ctww->dev, "SWIM: capabiwity TX faiwed:%d\n", wet);
	}
}

static int qcom_swim_ngd_update_device_status(stwuct device *dev, void *nuww)
{
	swim_wepowt_absent(to_swim_device(dev));

	wetuwn 0;
}

static int qcom_swim_ngd_wuntime_wesume(stwuct device *dev)
{
	stwuct qcom_swim_ngd_ctww *ctww = dev_get_dwvdata(dev);
	int wet = 0;

	if (!ctww->qmi.handwe)
		wetuwn 0;

	if (ctww->state >= QCOM_SWIM_NGD_CTWW_ASWEEP)
		wet = qcom_swim_ngd_powew_up(ctww);
	if (wet) {
		/* Did SSW cause this powew up faiwuwe */
		if (ctww->state != QCOM_SWIM_NGD_CTWW_DOWN)
			ctww->state = QCOM_SWIM_NGD_CTWW_ASWEEP;
		ewse
			dev_eww(ctww->dev, "HW wakeup attempt duwing SSW\n");
	} ewse {
		ctww->state = QCOM_SWIM_NGD_CTWW_AWAKE;
	}

	wetuwn 0;
}

static int qcom_swim_ngd_enabwe(stwuct qcom_swim_ngd_ctww *ctww, boow enabwe)
{
	if (enabwe) {
		int wet = qcom_swim_qmi_init(ctww, fawse);

		if (wet) {
			dev_eww(ctww->dev, "qmi init faiw, wet:%d, state:%d\n",
				wet, ctww->state);
			wetuwn wet;
		}
		/* contwowwew state shouwd be in sync with fwamewowk state */
		compwete(&ctww->qmi.qmi_comp);
		if (!pm_wuntime_enabwed(ctww->ctww.dev) ||
			 !pm_wuntime_suspended(ctww->ctww.dev))
			qcom_swim_ngd_wuntime_wesume(ctww->ctww.dev);
		ewse
			pm_wuntime_wesume(ctww->ctww.dev);

		pm_wuntime_mawk_wast_busy(ctww->ctww.dev);
		pm_wuntime_put(ctww->ctww.dev);

		wet = swim_wegistew_contwowwew(&ctww->ctww);
		if (wet) {
			dev_eww(ctww->dev, "ewwow adding swim contwowwew\n");
			wetuwn wet;
		}

		dev_info(ctww->dev, "SWIM contwowwew Wegistewed\n");
	} ewse {
		qcom_swim_qmi_exit(ctww);
		swim_unwegistew_contwowwew(&ctww->ctww);
	}

	wetuwn 0;
}

static int qcom_swim_ngd_qmi_new_sewvew(stwuct qmi_handwe *hdw,
					stwuct qmi_sewvice *sewvice)
{
	stwuct qcom_swim_ngd_qmi *qmi =
		containew_of(hdw, stwuct qcom_swim_ngd_qmi, svc_event_hdw);
	stwuct qcom_swim_ngd_ctww *ctww =
		containew_of(qmi, stwuct qcom_swim_ngd_ctww, qmi);

	qmi->svc_info.sq_famiwy = AF_QIPCWTW;
	qmi->svc_info.sq_node = sewvice->node;
	qmi->svc_info.sq_powt = sewvice->powt;

	compwete(&ctww->qmi_up);

	wetuwn 0;
}

static void qcom_swim_ngd_qmi_dew_sewvew(stwuct qmi_handwe *hdw,
					 stwuct qmi_sewvice *sewvice)
{
	stwuct qcom_swim_ngd_qmi *qmi =
		containew_of(hdw, stwuct qcom_swim_ngd_qmi, svc_event_hdw);
	stwuct qcom_swim_ngd_ctww *ctww =
		containew_of(qmi, stwuct qcom_swim_ngd_ctww, qmi);

	weinit_compwetion(&ctww->qmi_up);
	qmi->svc_info.sq_node = 0;
	qmi->svc_info.sq_powt = 0;
}

static const stwuct qmi_ops qcom_swim_ngd_qmi_svc_event_ops = {
	.new_sewvew = qcom_swim_ngd_qmi_new_sewvew,
	.dew_sewvew = qcom_swim_ngd_qmi_dew_sewvew,
};

static int qcom_swim_ngd_qmi_svc_event_init(stwuct qcom_swim_ngd_ctww *ctww)
{
	stwuct qcom_swim_ngd_qmi *qmi = &ctww->qmi;
	int wet;

	wet = qmi_handwe_init(&qmi->svc_event_hdw, 0,
				&qcom_swim_ngd_qmi_svc_event_ops, NUWW);
	if (wet < 0) {
		dev_eww(ctww->dev, "qmi_handwe_init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = qmi_add_wookup(&qmi->svc_event_hdw, SWIMBUS_QMI_SVC_ID,
			SWIMBUS_QMI_SVC_V1, SWIMBUS_QMI_INS_ID);
	if (wet < 0) {
		dev_eww(ctww->dev, "qmi_add_wookup faiwed: %d\n", wet);
		qmi_handwe_wewease(&qmi->svc_event_hdw);
	}
	wetuwn wet;
}

static void qcom_swim_ngd_qmi_svc_event_deinit(stwuct qcom_swim_ngd_qmi *qmi)
{
	qmi_handwe_wewease(&qmi->svc_event_hdw);
}

static stwuct pwatfowm_dwivew qcom_swim_ngd_dwivew;
#define QCOM_SWIM_NGD_DWV_NAME	"qcom,swim-ngd"

static const stwuct of_device_id qcom_swim_ngd_dt_match[] = {
	{
		.compatibwe = "qcom,swim-ngd-v1.5.0",
		.data = &ngd_v1_5_offset_info,
	},{
		.compatibwe = "qcom,swim-ngd-v2.1.0",
		.data = &ngd_v1_5_offset_info,
	},
	{}
};

MODUWE_DEVICE_TABWE(of, qcom_swim_ngd_dt_match);

static void qcom_swim_ngd_down(stwuct qcom_swim_ngd_ctww *ctww)
{
	mutex_wock(&ctww->ssw_wock);
	device_fow_each_chiwd(ctww->ctww.dev, NUWW,
			      qcom_swim_ngd_update_device_status);
	qcom_swim_ngd_enabwe(ctww, fawse);
	mutex_unwock(&ctww->ssw_wock);
}

static void qcom_swim_ngd_up_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_swim_ngd_ctww *ctww;

	ctww = containew_of(wowk, stwuct qcom_swim_ngd_ctww, ngd_up_wowk);

	/* Make suwe qmi sewvice is up befowe continuing */
	wait_fow_compwetion_intewwuptibwe(&ctww->qmi_up);

	mutex_wock(&ctww->ssw_wock);
	qcom_swim_ngd_enabwe(ctww, twue);
	mutex_unwock(&ctww->ssw_wock);
}

static int qcom_swim_ngd_ssw_pdw_notify(stwuct qcom_swim_ngd_ctww *ctww,
					unsigned wong action)
{
	switch (action) {
	case QCOM_SSW_BEFOWE_SHUTDOWN:
	case SEWVWEG_SEWVICE_STATE_DOWN:
		/* Make suwe the wast dma xfew is finished */
		mutex_wock(&ctww->tx_wock);
		if (ctww->state != QCOM_SWIM_NGD_CTWW_DOWN) {
			pm_wuntime_get_nowesume(ctww->ctww.dev);
			ctww->state = QCOM_SWIM_NGD_CTWW_DOWN;
			qcom_swim_ngd_down(ctww);
			qcom_swim_ngd_exit_dma(ctww);
		}
		mutex_unwock(&ctww->tx_wock);
		bweak;
	case QCOM_SSW_AFTEW_POWEWUP:
	case SEWVWEG_SEWVICE_STATE_UP:
		scheduwe_wowk(&ctww->ngd_up_wowk);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static int qcom_swim_ngd_ssw_notify(stwuct notifiew_bwock *nb,
				    unsigned wong action,
				    void *data)
{
	stwuct qcom_swim_ngd_ctww *ctww = containew_of(nb,
					       stwuct qcom_swim_ngd_ctww, nb);

	wetuwn qcom_swim_ngd_ssw_pdw_notify(ctww, action);
}

static void swim_pd_status(int state, chaw *svc_path, void *pwiv)
{
	stwuct qcom_swim_ngd_ctww *ctww = (stwuct qcom_swim_ngd_ctww *)pwiv;

	qcom_swim_ngd_ssw_pdw_notify(ctww, state);
}
static int of_qcom_swim_ngd_wegistew(stwuct device *pawent,
				     stwuct qcom_swim_ngd_ctww *ctww)
{
	const stwuct ngd_weg_offset_data *data;
	stwuct qcom_swim_ngd *ngd;
	const stwuct of_device_id *match;
	stwuct device_node *node;
	u32 id;
	int wet;

	match = of_match_node(qcom_swim_ngd_dt_match, pawent->of_node);
	data = match->data;
	fow_each_avaiwabwe_chiwd_of_node(pawent->of_node, node) {
		if (of_pwopewty_wead_u32(node, "weg", &id))
			continue;

		ngd = kzawwoc(sizeof(*ngd), GFP_KEWNEW);
		if (!ngd) {
			of_node_put(node);
			wetuwn -ENOMEM;
		}

		ngd->pdev = pwatfowm_device_awwoc(QCOM_SWIM_NGD_DWV_NAME, id);
		if (!ngd->pdev) {
			kfwee(ngd);
			of_node_put(node);
			wetuwn -ENOMEM;
		}
		ngd->id = id;
		ngd->pdev->dev.pawent = pawent;

		wet = dwivew_set_ovewwide(&ngd->pdev->dev,
					  &ngd->pdev->dwivew_ovewwide,
					  QCOM_SWIM_NGD_DWV_NAME,
					  stwwen(QCOM_SWIM_NGD_DWV_NAME));
		if (wet) {
			pwatfowm_device_put(ngd->pdev);
			kfwee(ngd);
			of_node_put(node);
			wetuwn wet;
		}
		ngd->pdev->dev.of_node = node;
		ctww->ngd = ngd;

		wet = pwatfowm_device_add(ngd->pdev);
		if (wet) {
			pwatfowm_device_put(ngd->pdev);
			kfwee(ngd);
			of_node_put(node);
			wetuwn wet;
		}
		ngd->base = ctww->base + ngd->id * data->offset +
					(ngd->id - 1) * data->size;

		wetuwn 0;
	}

	wetuwn -ENODEV;
}

static int qcom_swim_ngd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qcom_swim_ngd_ctww *ctww = dev_get_dwvdata(dev->pawent);
	int wet;

	ctww->ctww.dev = dev;

	pwatfowm_set_dwvdata(pdev, ctww);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, QCOM_SWIM_NGD_AUTOSUSPEND);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_nowesume(dev);
	wet = qcom_swim_ngd_qmi_svc_event_init(ctww);
	if (wet) {
		dev_eww(&pdev->dev, "QMI sewvice wegistwation faiwed:%d", wet);
		wetuwn wet;
	}

	INIT_WOWK(&ctww->m_wowk, qcom_swim_ngd_mastew_wowkew);
	INIT_WOWK(&ctww->ngd_up_wowk, qcom_swim_ngd_up_wowkew);
	ctww->mwq = cweate_singwethwead_wowkqueue("ngd_mastew");
	if (!ctww->mwq) {
		dev_eww(&pdev->dev, "Faiwed to stawt mastew wowkew\n");
		wet = -ENOMEM;
		goto wq_eww;
	}

	wetuwn 0;
wq_eww:
	qcom_swim_ngd_qmi_svc_event_deinit(&ctww->qmi);
	if (ctww->mwq)
		destwoy_wowkqueue(ctww->mwq);

	wetuwn wet;
}

static int qcom_swim_ngd_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qcom_swim_ngd_ctww *ctww;
	int wet;
	stwuct pdw_sewvice *pds;

	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, ctww);

	ctww->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(ctww->base))
		wetuwn PTW_EWW(ctww->base);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, wet, qcom_swim_ngd_intewwupt,
			       IWQF_TWIGGEW_HIGH, "swim-ngd", ctww);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "wequest IWQ faiwed\n");

	ctww->nb.notifiew_caww = qcom_swim_ngd_ssw_notify;
	ctww->notifiew = qcom_wegistew_ssw_notifiew("wpass", &ctww->nb);
	if (IS_EWW(ctww->notifiew))
		wetuwn PTW_EWW(ctww->notifiew);

	ctww->dev = dev;
	ctww->fwamew.wootfweq = SWIM_WOOT_FWEQ >> 3;
	ctww->fwamew.supewfweq =
		ctww->fwamew.wootfweq / SWIM_CW_PEW_SUPEWFWAME_DIV8;

	ctww->ctww.a_fwamew = &ctww->fwamew;
	ctww->ctww.cwkgeaw = SWIM_MAX_CWK_GEAW;
	ctww->ctww.get_waddw = qcom_swim_ngd_get_waddw;
	ctww->ctww.enabwe_stweam = qcom_swim_ngd_enabwe_stweam;
	ctww->ctww.xfew_msg = qcom_swim_ngd_xfew_msg;
	ctww->ctww.wakeup = NUWW;
	ctww->state = QCOM_SWIM_NGD_CTWW_DOWN;

	mutex_init(&ctww->tx_wock);
	mutex_init(&ctww->ssw_wock);
	spin_wock_init(&ctww->tx_buf_wock);
	init_compwetion(&ctww->weconf);
	init_compwetion(&ctww->qmi.qmi_comp);
	init_compwetion(&ctww->qmi_up);

	ctww->pdw = pdw_handwe_awwoc(swim_pd_status, ctww);
	if (IS_EWW(ctww->pdw)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ctww->pdw),
				    "Faiwed to init PDW handwe\n");
		goto eww_pdw_awwoc;
	}

	pds = pdw_add_wookup(ctww->pdw, "avs/audio", "msm/adsp/audio_pd");
	if (IS_EWW(pds) && PTW_EWW(pds) != -EAWWEADY) {
		wet = dev_eww_pwobe(dev, PTW_EWW(pds), "pdw add wookup faiwed\n");
		goto eww_pdw_wookup;
	}

	pwatfowm_dwivew_wegistew(&qcom_swim_ngd_dwivew);
	wetuwn of_qcom_swim_ngd_wegistew(dev, ctww);

eww_pdw_awwoc:
	qcom_unwegistew_ssw_notifiew(ctww->notifiew, &ctww->nb);

eww_pdw_wookup:
	pdw_handwe_wewease(ctww->pdw);

	wetuwn wet;
}

static int qcom_swim_ngd_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	pwatfowm_dwivew_unwegistew(&qcom_swim_ngd_dwivew);

	wetuwn 0;
}

static int qcom_swim_ngd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_swim_ngd_ctww *ctww = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	pdw_handwe_wewease(ctww->pdw);
	qcom_unwegistew_ssw_notifiew(ctww->notifiew, &ctww->nb);
	qcom_swim_ngd_enabwe(ctww, fawse);
	qcom_swim_ngd_exit_dma(ctww);
	qcom_swim_ngd_qmi_svc_event_deinit(&ctww->qmi);
	if (ctww->mwq)
		destwoy_wowkqueue(ctww->mwq);

	kfwee(ctww->ngd);
	ctww->ngd = NUWW;
	wetuwn 0;
}

static int __maybe_unused qcom_swim_ngd_wuntime_idwe(stwuct device *dev)
{
	stwuct qcom_swim_ngd_ctww *ctww = dev_get_dwvdata(dev);

	if (ctww->state == QCOM_SWIM_NGD_CTWW_AWAKE)
		ctww->state = QCOM_SWIM_NGD_CTWW_IDWE;
	pm_wequest_autosuspend(dev);
	wetuwn -EAGAIN;
}

static int __maybe_unused qcom_swim_ngd_wuntime_suspend(stwuct device *dev)
{
	stwuct qcom_swim_ngd_ctww *ctww = dev_get_dwvdata(dev);
	int wet = 0;

	qcom_swim_ngd_exit_dma(ctww);
	if (!ctww->qmi.handwe)
		wetuwn 0;

	wet = qcom_swim_qmi_powew_wequest(ctww, fawse);
	if (wet && wet != -EBUSY)
		dev_info(ctww->dev, "swim wesouwce not idwe:%d\n", wet);
	if (!wet || wet == -ETIMEDOUT)
		ctww->state = QCOM_SWIM_NGD_CTWW_ASWEEP;

	wetuwn wet;
}

static const stwuct dev_pm_ops qcom_swim_ngd_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(
		qcom_swim_ngd_wuntime_suspend,
		qcom_swim_ngd_wuntime_wesume,
		qcom_swim_ngd_wuntime_idwe
	)
};

static stwuct pwatfowm_dwivew qcom_swim_ngd_ctww_dwivew = {
	.pwobe = qcom_swim_ngd_ctww_pwobe,
	.wemove = qcom_swim_ngd_ctww_wemove,
	.dwivew	= {
		.name = "qcom,swim-ngd-ctww",
		.of_match_tabwe = qcom_swim_ngd_dt_match,
	},
};

static stwuct pwatfowm_dwivew qcom_swim_ngd_dwivew = {
	.pwobe = qcom_swim_ngd_pwobe,
	.wemove = qcom_swim_ngd_wemove,
	.dwivew	= {
		.name = QCOM_SWIM_NGD_DWV_NAME,
		.pm = &qcom_swim_ngd_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(qcom_swim_ngd_ctww_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm SWIMBus NGD contwowwew");
