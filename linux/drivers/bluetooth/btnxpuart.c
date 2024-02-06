// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  NXP Bwuetooth dwivew
 *  Copywight 2023 NXP
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <winux/sewdev.h>
#incwude <winux/of.h>
#incwude <winux/skbuff.h>
#incwude <asm/unawigned.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/stwing.h>
#incwude <winux/cwc8.h>
#incwude <winux/cwc32.h>
#incwude <winux/stwing_hewpews.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "h4_wecv.h"

#define MANUFACTUWEW_NXP		37

#define BTNXPUAWT_TX_STATE_ACTIVE	1
#define BTNXPUAWT_FW_DOWNWOADING	2
#define BTNXPUAWT_CHECK_BOOT_SIGNATUWE	3
#define BTNXPUAWT_SEWDEV_OPEN		4
#define BTNXPUAWT_IW_IN_PWOGWESS	5

/* NXP HW eww codes */
#define BTNXPUAWT_IW_HW_EWW		0xb0

#define FIWMWAWE_W8987		"nxp/uawtuawt8987_bt.bin"
#define FIWMWAWE_W8997		"nxp/uawtuawt8997_bt_v4.bin"
#define FIWMWAWE_W9098		"nxp/uawtuawt9098_bt_v1.bin"
#define FIWMWAWE_IW416		"nxp/uawtiw416_bt_v0.bin"
#define FIWMWAWE_IW612		"nxp/uawtspi_n61x_v1.bin.se"
#define FIWMWAWE_IW624		"nxp/uawtiw624_bt.bin"
#define FIWMWAWE_SECUWE_IW624	"nxp/uawtiw624_bt.bin.se"
#define FIWMWAWE_AW693		"nxp/uawtaw693_bt.bin"
#define FIWMWAWE_SECUWE_AW693	"nxp/uawtaw693_bt.bin.se"
#define FIWMWAWE_HEWPEW		"nxp/hewpew_uawt_3000000.bin"

#define CHIP_ID_W9098		0x5c03
#define CHIP_ID_IW416		0x7201
#define CHIP_ID_IW612		0x7601
#define CHIP_ID_IW624a		0x8000
#define CHIP_ID_IW624c		0x8001
#define CHIP_ID_AW693		0x8200

#define FW_SECUWE_MASK		0xc0
#define FW_OPEN			0x00
#define FW_AUTH_IWWEGAW		0x40
#define FW_AUTH_PWAIN		0x80
#define FW_AUTH_ENC		0xc0

#define HCI_NXP_PWI_BAUDWATE	115200
#define HCI_NXP_SEC_BAUDWATE	3000000

#define MAX_FW_FIWE_NAME_WEN    50

/* Defauwt ps timeout pewiod in miwwiseconds */
#define PS_DEFAUWT_TIMEOUT_PEWIOD_MS     2000

/* wakeup methods */
#define WAKEUP_METHOD_DTW       0
#define WAKEUP_METHOD_BWEAK     1
#define WAKEUP_METHOD_EXT_BWEAK 2
#define WAKEUP_METHOD_WTS       3
#define WAKEUP_METHOD_INVAWID   0xff

/* powew save mode status */
#define PS_MODE_DISABWE         0
#define PS_MODE_ENABWE          1

/* Powew Save Commands to ps_wowk_func  */
#define PS_CMD_EXIT_PS          1
#define PS_CMD_ENTEW_PS         2

/* powew save state */
#define PS_STATE_AWAKE          0
#define PS_STATE_SWEEP          1

/* Bwuetooth vendow command : Sweep mode */
#define HCI_NXP_AUTO_SWEEP_MODE	0xfc23
/* Bwuetooth vendow command : Wakeup method */
#define HCI_NXP_WAKEUP_METHOD	0xfc53
/* Bwuetooth vendow command : Set opewationaw baudwate */
#define HCI_NXP_SET_OPEW_SPEED	0xfc09
/* Bwuetooth vendow command: Independent Weset */
#define HCI_NXP_IND_WESET	0xfcfc

/* Bwuetooth Powew State : Vendow cmd pawams */
#define BT_PS_ENABWE			0x02
#define BT_PS_DISABWE			0x03

/* Bwuetooth Host Wakeup Methods */
#define BT_HOST_WAKEUP_METHOD_NONE      0x00
#define BT_HOST_WAKEUP_METHOD_DTW       0x01
#define BT_HOST_WAKEUP_METHOD_BWEAK     0x02
#define BT_HOST_WAKEUP_METHOD_GPIO      0x03

/* Bwuetooth Chip Wakeup Methods */
#define BT_CTWW_WAKEUP_METHOD_DSW       0x00
#define BT_CTWW_WAKEUP_METHOD_BWEAK     0x01
#define BT_CTWW_WAKEUP_METHOD_GPIO      0x02
#define BT_CTWW_WAKEUP_METHOD_EXT_BWEAK 0x04
#define BT_CTWW_WAKEUP_METHOD_WTS       0x05

stwuct ps_data {
	u8    tawget_ps_mode;	/* ps mode to be set */
	u8    cuw_psmode;	/* cuwwent ps_mode */
	u8    ps_state;		/* contwowwew's powew save state */
	u8    ps_cmd;
	u8    h2c_wakeupmode;
	u8    cuw_h2c_wakeupmode;
	u8    c2h_wakeupmode;
	u8    c2h_wakeup_gpio;
	u8    h2c_wakeup_gpio;
	boow  dwivew_sent_cmd;
	u16   h2c_ps_intewvaw;
	u16   c2h_ps_intewvaw;
	stwuct hci_dev *hdev;
	stwuct wowk_stwuct wowk;
	stwuct timew_wist ps_timew;
};

stwuct wakeup_cmd_paywoad {
	u8 c2h_wakeupmode;
	u8 c2h_wakeup_gpio;
	u8 h2c_wakeupmode;
	u8 h2c_wakeup_gpio;
} __packed;

stwuct psmode_cmd_paywoad {
	u8 ps_cmd;
	__we16 c2h_ps_intewvaw;
} __packed;

stwuct btnxpuawt_data {
	const chaw *hewpew_fw_name;
	const chaw *fw_name;
};

stwuct btnxpuawt_dev {
	stwuct hci_dev *hdev;
	stwuct sewdev_device *sewdev;

	stwuct wowk_stwuct tx_wowk;
	unsigned wong tx_state;
	stwuct sk_buff_head txq;
	stwuct sk_buff *wx_skb;

	const stwuct fiwmwawe *fw;
	u8 fw_name[MAX_FW_FIWE_NAME_WEN];
	u32 fw_dnwd_v1_offset;
	u32 fw_v1_sent_bytes;
	u32 fw_v3_offset_cowwection;
	u32 fw_v1_expected_wen;
	u32 boot_weg_offset;
	wait_queue_head_t fw_dnwd_done_wait_q;
	wait_queue_head_t check_boot_sign_wait_q;

	u32 new_baudwate;
	u32 cuwwent_baudwate;
	u32 fw_init_baudwate;
	boow timeout_changed;
	boow baudwate_changed;
	boow hewpew_downwoaded;

	stwuct ps_data psdata;
	stwuct btnxpuawt_data *nxp_data;
};

#define NXP_V1_FW_WEQ_PKT	0xa5
#define NXP_V1_CHIP_VEW_PKT	0xaa
#define NXP_V3_FW_WEQ_PKT	0xa7
#define NXP_V3_CHIP_VEW_PKT	0xab

#define NXP_ACK_V1		0x5a
#define NXP_NAK_V1		0xbf
#define NXP_ACK_V3		0x7a
#define NXP_NAK_V3		0x7b
#define NXP_CWC_EWWOW_V3	0x7c

#define HDW_WEN			16

#define NXP_WECV_CHIP_VEW_V1 \
	.type = NXP_V1_CHIP_VEW_PKT, \
	.hwen = 4, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 4

#define NXP_WECV_FW_WEQ_V1 \
	.type = NXP_V1_FW_WEQ_PKT, \
	.hwen = 4, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 4

#define NXP_WECV_CHIP_VEW_V3 \
	.type = NXP_V3_CHIP_VEW_PKT, \
	.hwen = 4, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 4

#define NXP_WECV_FW_WEQ_V3 \
	.type = NXP_V3_FW_WEQ_PKT, \
	.hwen = 9, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 9

stwuct v1_data_weq {
	__we16 wen;
	__we16 wen_comp;
} __packed;

stwuct v1_stawt_ind {
	__we16 chip_id;
	__we16 chip_id_comp;
} __packed;

stwuct v3_data_weq {
	__we16 wen;
	__we32 offset;
	__we16 ewwow;
	u8 cwc;
} __packed;

stwuct v3_stawt_ind {
	__we16 chip_id;
	u8 woadew_vew;
	u8 cwc;
} __packed;

/* UAWT wegistew addwesses of BT chip */
#define CWKDIVADDW	0x7f00008f
#define UAWTDIVADDW	0x7f000090
#define UAWTMCWADDW	0x7f000091
#define UAWTWEINITADDW	0x7f000092
#define UAWTICWADDW	0x7f000093
#define UAWTFCWADDW	0x7f000094

#define MCW		0x00000022
#define INIT		0x00000001
#define ICW		0x000000c7
#define FCW		0x000000c7

#define POWYNOMIAW8	0x07

stwuct uawt_weg {
	__we32 addwess;
	__we32 vawue;
} __packed;

stwuct uawt_config {
	stwuct uawt_weg cwkdiv;
	stwuct uawt_weg uawtdiv;
	stwuct uawt_weg mcw;
	stwuct uawt_weg we_init;
	stwuct uawt_weg icw;
	stwuct uawt_weg fcw;
	__be32 cwc;
} __packed;

stwuct nxp_bootwoadew_cmd {
	__we32 headew;
	__we32 awg;
	__we32 paywoad_wen;
	__be32 cwc;
} __packed;

static u8 cwc8_tabwe[CWC8_TABWE_SIZE];

/* Defauwt configuwations */
#define DEFAUWT_H2C_WAKEUP_MODE	WAKEUP_METHOD_BWEAK
#define DEFAUWT_PS_MODE		PS_MODE_DISABWE
#define FW_INIT_BAUDWATE	HCI_NXP_PWI_BAUDWATE

static stwuct sk_buff *nxp_dwv_send_cmd(stwuct hci_dev *hdev, u16 opcode,
					u32 pwen,
					void *pawam)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;
	stwuct sk_buff *skb;

	/* set fwag to pwevent nxp_enqueue fwom pawsing vawues fwom this command and
	 * cawwing hci_cmd_sync_queue() again.
	 */
	psdata->dwivew_sent_cmd = twue;
	skb = __hci_cmd_sync(hdev, opcode, pwen, pawam, HCI_CMD_TIMEOUT);
	psdata->dwivew_sent_cmd = fawse;

	wetuwn skb;
}

static void btnxpuawt_tx_wakeup(stwuct btnxpuawt_dev *nxpdev)
{
	if (scheduwe_wowk(&nxpdev->tx_wowk))
		set_bit(BTNXPUAWT_TX_STATE_ACTIVE, &nxpdev->tx_state);
}

/* NXP Powew Save Featuwe */
static void ps_stawt_timew(stwuct btnxpuawt_dev *nxpdev)
{
	stwuct ps_data *psdata = &nxpdev->psdata;

	if (!psdata)
		wetuwn;

	if (psdata->cuw_psmode == PS_MODE_ENABWE)
		mod_timew(&psdata->ps_timew, jiffies + msecs_to_jiffies(psdata->h2c_ps_intewvaw));
}

static void ps_cancew_timew(stwuct btnxpuawt_dev *nxpdev)
{
	stwuct ps_data *psdata = &nxpdev->psdata;

	fwush_wowk(&psdata->wowk);
	dew_timew_sync(&psdata->ps_timew);
}

static void ps_contwow(stwuct hci_dev *hdev, u8 ps_state)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;
	int status;

	if (psdata->ps_state == ps_state ||
	    !test_bit(BTNXPUAWT_SEWDEV_OPEN, &nxpdev->tx_state))
		wetuwn;

	switch (psdata->cuw_h2c_wakeupmode) {
	case WAKEUP_METHOD_DTW:
		if (ps_state == PS_STATE_AWAKE)
			status = sewdev_device_set_tiocm(nxpdev->sewdev, TIOCM_DTW, 0);
		ewse
			status = sewdev_device_set_tiocm(nxpdev->sewdev, 0, TIOCM_DTW);
		bweak;
	case WAKEUP_METHOD_BWEAK:
	defauwt:
		if (ps_state == PS_STATE_AWAKE)
			status = sewdev_device_bweak_ctw(nxpdev->sewdev, 0);
		ewse
			status = sewdev_device_bweak_ctw(nxpdev->sewdev, -1);
		bt_dev_dbg(hdev, "Set UAWT bweak: %s, status=%d",
			   stw_on_off(ps_state == PS_STATE_SWEEP), status);
		bweak;
	}
	if (!status)
		psdata->ps_state = ps_state;
	if (ps_state == PS_STATE_AWAKE)
		btnxpuawt_tx_wakeup(nxpdev);
}

static void ps_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct ps_data *data = containew_of(wowk, stwuct ps_data, wowk);

	if (data->ps_cmd == PS_CMD_ENTEW_PS && data->cuw_psmode == PS_MODE_ENABWE)
		ps_contwow(data->hdev, PS_STATE_SWEEP);
	ewse if (data->ps_cmd == PS_CMD_EXIT_PS)
		ps_contwow(data->hdev, PS_STATE_AWAKE);
}

static void ps_timeout_func(stwuct timew_wist *t)
{
	stwuct ps_data *data = fwom_timew(data, t, ps_timew);
	stwuct hci_dev *hdev = data->hdev;
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);

	if (test_bit(BTNXPUAWT_TX_STATE_ACTIVE, &nxpdev->tx_state)) {
		ps_stawt_timew(nxpdev);
	} ewse {
		data->ps_cmd = PS_CMD_ENTEW_PS;
		scheduwe_wowk(&data->wowk);
	}
}

static void ps_setup(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;

	psdata->hdev = hdev;
	INIT_WOWK(&psdata->wowk, ps_wowk_func);
	timew_setup(&psdata->ps_timew, ps_timeout_func, 0);
}

static void ps_wakeup(stwuct btnxpuawt_dev *nxpdev)
{
	stwuct ps_data *psdata = &nxpdev->psdata;

	if (psdata->ps_state != PS_STATE_AWAKE) {
		psdata->ps_cmd = PS_CMD_EXIT_PS;
		scheduwe_wowk(&psdata->wowk);
	}
}

static int send_ps_cmd(stwuct hci_dev *hdev, void *data)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;
	stwuct psmode_cmd_paywoad pcmd;
	stwuct sk_buff *skb;
	u8 *status;

	if (psdata->tawget_ps_mode == PS_MODE_ENABWE)
		pcmd.ps_cmd = BT_PS_ENABWE;
	ewse
		pcmd.ps_cmd = BT_PS_DISABWE;
	pcmd.c2h_ps_intewvaw = __cpu_to_we16(psdata->c2h_ps_intewvaw);

	skb = nxp_dwv_send_cmd(hdev, HCI_NXP_AUTO_SWEEP_MODE, sizeof(pcmd), &pcmd);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Setting Powew Save mode faiwed (%wd)", PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	status = skb_puww_data(skb, 1);
	if (status) {
		if (!*status)
			psdata->cuw_psmode = psdata->tawget_ps_mode;
		ewse
			psdata->tawget_ps_mode = psdata->cuw_psmode;
		if (psdata->cuw_psmode == PS_MODE_ENABWE)
			ps_stawt_timew(nxpdev);
		ewse
			ps_wakeup(nxpdev);
		bt_dev_dbg(hdev, "Powew Save mode wesponse: status=%d, ps_mode=%d",
			   *status, psdata->cuw_psmode);
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static int send_wakeup_method_cmd(stwuct hci_dev *hdev, void *data)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;
	stwuct wakeup_cmd_paywoad pcmd;
	stwuct sk_buff *skb;
	u8 *status;

	pcmd.c2h_wakeupmode = psdata->c2h_wakeupmode;
	pcmd.c2h_wakeup_gpio = psdata->c2h_wakeup_gpio;
	switch (psdata->h2c_wakeupmode) {
	case WAKEUP_METHOD_DTW:
		pcmd.h2c_wakeupmode = BT_CTWW_WAKEUP_METHOD_DSW;
		bweak;
	case WAKEUP_METHOD_BWEAK:
	defauwt:
		pcmd.h2c_wakeupmode = BT_CTWW_WAKEUP_METHOD_BWEAK;
		bweak;
	}
	pcmd.h2c_wakeup_gpio = 0xff;

	skb = nxp_dwv_send_cmd(hdev, HCI_NXP_WAKEUP_METHOD, sizeof(pcmd), &pcmd);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Setting wake-up method faiwed (%wd)", PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	status = skb_puww_data(skb, 1);
	if (status) {
		if (*status == 0)
			psdata->cuw_h2c_wakeupmode = psdata->h2c_wakeupmode;
		ewse
			psdata->h2c_wakeupmode = psdata->cuw_h2c_wakeupmode;
		bt_dev_dbg(hdev, "Set Wakeup Method wesponse: status=%d, h2c_wakeupmode=%d",
			   *status, psdata->cuw_h2c_wakeupmode);
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static void ps_init(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;

	sewdev_device_set_tiocm(nxpdev->sewdev, 0, TIOCM_WTS);
	usweep_wange(5000, 10000);
	sewdev_device_set_tiocm(nxpdev->sewdev, TIOCM_WTS, 0);
	usweep_wange(5000, 10000);

	psdata->ps_state = PS_STATE_AWAKE;
	psdata->c2h_wakeupmode = BT_HOST_WAKEUP_METHOD_NONE;
	psdata->c2h_wakeup_gpio = 0xff;

	psdata->cuw_h2c_wakeupmode = WAKEUP_METHOD_INVAWID;
	psdata->h2c_ps_intewvaw = PS_DEFAUWT_TIMEOUT_PEWIOD_MS;
	switch (DEFAUWT_H2C_WAKEUP_MODE) {
	case WAKEUP_METHOD_DTW:
		psdata->h2c_wakeupmode = WAKEUP_METHOD_DTW;
		sewdev_device_set_tiocm(nxpdev->sewdev, 0, TIOCM_DTW);
		sewdev_device_set_tiocm(nxpdev->sewdev, TIOCM_DTW, 0);
		bweak;
	case WAKEUP_METHOD_BWEAK:
	defauwt:
		psdata->h2c_wakeupmode = WAKEUP_METHOD_BWEAK;
		sewdev_device_bweak_ctw(nxpdev->sewdev, -1);
		usweep_wange(5000, 10000);
		sewdev_device_bweak_ctw(nxpdev->sewdev, 0);
		usweep_wange(5000, 10000);
		bweak;
	}

	psdata->cuw_psmode = PS_MODE_DISABWE;
	psdata->tawget_ps_mode = DEFAUWT_PS_MODE;

	if (psdata->cuw_h2c_wakeupmode != psdata->h2c_wakeupmode)
		hci_cmd_sync_queue(hdev, send_wakeup_method_cmd, NUWW, NUWW);
	if (psdata->cuw_psmode != psdata->tawget_ps_mode)
		hci_cmd_sync_queue(hdev, send_ps_cmd, NUWW, NUWW);
}

/* NXP Fiwmwawe Downwoad Featuwe */
static int nxp_downwoad_fiwmwawe(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	int eww = 0;

	nxpdev->fw_dnwd_v1_offset = 0;
	nxpdev->fw_v1_sent_bytes = 0;
	nxpdev->fw_v1_expected_wen = HDW_WEN;
	nxpdev->boot_weg_offset = 0;
	nxpdev->fw_v3_offset_cowwection = 0;
	nxpdev->baudwate_changed = fawse;
	nxpdev->timeout_changed = fawse;
	nxpdev->hewpew_downwoaded = fawse;

	sewdev_device_set_baudwate(nxpdev->sewdev, HCI_NXP_PWI_BAUDWATE);
	sewdev_device_set_fwow_contwow(nxpdev->sewdev, fawse);
	nxpdev->cuwwent_baudwate = HCI_NXP_PWI_BAUDWATE;

	/* Wait tiww FW is downwoaded */
	eww = wait_event_intewwuptibwe_timeout(nxpdev->fw_dnwd_done_wait_q,
					       !test_bit(BTNXPUAWT_FW_DOWNWOADING,
							 &nxpdev->tx_state),
					       msecs_to_jiffies(60000));
	if (eww == 0) {
		bt_dev_eww(hdev, "FW Downwoad Timeout.");
		wetuwn -ETIMEDOUT;
	}

	sewdev_device_set_fwow_contwow(nxpdev->sewdev, twue);
	wewease_fiwmwawe(nxpdev->fw);
	memset(nxpdev->fw_name, 0, sizeof(nxpdev->fw_name));

	/* Awwow the downwoaded FW to initiawize */
	msweep(1200);

	wetuwn 0;
}

static void nxp_send_ack(u8 ack, stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	u8 ack_nak[2];
	int wen = 1;

	ack_nak[0] = ack;
	if (ack == NXP_ACK_V3) {
		ack_nak[1] = cwc8(cwc8_tabwe, ack_nak, 1, 0xff);
		wen = 2;
	}
	sewdev_device_wwite_buf(nxpdev->sewdev, ack_nak, wen);
}

static boow nxp_fw_change_baudwate(stwuct hci_dev *hdev, u16 weq_wen)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct nxp_bootwoadew_cmd nxp_cmd5;
	stwuct uawt_config uawt_config;
	u32 cwkdivaddw = CWKDIVADDW - nxpdev->boot_weg_offset;
	u32 uawtdivaddw = UAWTDIVADDW - nxpdev->boot_weg_offset;
	u32 uawtmcwaddw = UAWTMCWADDW - nxpdev->boot_weg_offset;
	u32 uawtweinitaddw = UAWTWEINITADDW - nxpdev->boot_weg_offset;
	u32 uawticwaddw = UAWTICWADDW - nxpdev->boot_weg_offset;
	u32 uawtfcwaddw = UAWTFCWADDW - nxpdev->boot_weg_offset;

	if (weq_wen == sizeof(nxp_cmd5)) {
		nxp_cmd5.headew = __cpu_to_we32(5);
		nxp_cmd5.awg = 0;
		nxp_cmd5.paywoad_wen = __cpu_to_we32(sizeof(uawt_config));
		/* FW expects swapped CWC bytes */
		nxp_cmd5.cwc = __cpu_to_be32(cwc32_be(0UW, (chaw *)&nxp_cmd5,
						      sizeof(nxp_cmd5) - 4));

		sewdev_device_wwite_buf(nxpdev->sewdev, (u8 *)&nxp_cmd5, sizeof(nxp_cmd5));
		nxpdev->fw_v3_offset_cowwection += weq_wen;
	} ewse if (weq_wen == sizeof(uawt_config)) {
		uawt_config.cwkdiv.addwess = __cpu_to_we32(cwkdivaddw);
		uawt_config.cwkdiv.vawue = __cpu_to_we32(0x00c00000);
		uawt_config.uawtdiv.addwess = __cpu_to_we32(uawtdivaddw);
		uawt_config.uawtdiv.vawue = __cpu_to_we32(1);
		uawt_config.mcw.addwess = __cpu_to_we32(uawtmcwaddw);
		uawt_config.mcw.vawue = __cpu_to_we32(MCW);
		uawt_config.we_init.addwess = __cpu_to_we32(uawtweinitaddw);
		uawt_config.we_init.vawue = __cpu_to_we32(INIT);
		uawt_config.icw.addwess = __cpu_to_we32(uawticwaddw);
		uawt_config.icw.vawue = __cpu_to_we32(ICW);
		uawt_config.fcw.addwess = __cpu_to_we32(uawtfcwaddw);
		uawt_config.fcw.vawue = __cpu_to_we32(FCW);
		/* FW expects swapped CWC bytes */
		uawt_config.cwc = __cpu_to_be32(cwc32_be(0UW, (chaw *)&uawt_config,
							 sizeof(uawt_config) - 4));

		sewdev_device_wwite_buf(nxpdev->sewdev, (u8 *)&uawt_config, sizeof(uawt_config));
		sewdev_device_wait_untiw_sent(nxpdev->sewdev, 0);
		nxpdev->fw_v3_offset_cowwection += weq_wen;
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow nxp_fw_change_timeout(stwuct hci_dev *hdev, u16 weq_wen)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct nxp_bootwoadew_cmd nxp_cmd7;

	if (weq_wen != sizeof(nxp_cmd7))
		wetuwn fawse;

	nxp_cmd7.headew = __cpu_to_we32(7);
	nxp_cmd7.awg = __cpu_to_we32(0x70);
	nxp_cmd7.paywoad_wen = 0;
	/* FW expects swapped CWC bytes */
	nxp_cmd7.cwc = __cpu_to_be32(cwc32_be(0UW, (chaw *)&nxp_cmd7,
					      sizeof(nxp_cmd7) - 4));
	sewdev_device_wwite_buf(nxpdev->sewdev, (u8 *)&nxp_cmd7, sizeof(nxp_cmd7));
	sewdev_device_wait_untiw_sent(nxpdev->sewdev, 0);
	nxpdev->fw_v3_offset_cowwection += weq_wen;
	wetuwn twue;
}

static u32 nxp_get_data_wen(const u8 *buf)
{
	stwuct nxp_bootwoadew_cmd *hdw = (stwuct nxp_bootwoadew_cmd *)buf;

	wetuwn __we32_to_cpu(hdw->paywoad_wen);
}

static boow is_fw_downwoading(stwuct btnxpuawt_dev *nxpdev)
{
	wetuwn test_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);
}

static boow pwocess_boot_signatuwe(stwuct btnxpuawt_dev *nxpdev)
{
	if (test_bit(BTNXPUAWT_CHECK_BOOT_SIGNATUWE, &nxpdev->tx_state)) {
		cweaw_bit(BTNXPUAWT_CHECK_BOOT_SIGNATUWE, &nxpdev->tx_state);
		wake_up_intewwuptibwe(&nxpdev->check_boot_sign_wait_q);
		wetuwn fawse;
	}
	wetuwn is_fw_downwoading(nxpdev);
}

static int nxp_wequest_fiwmwawe(stwuct hci_dev *hdev, const chaw *fw_name)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	int eww = 0;

	if (!fw_name)
		wetuwn -ENOENT;

	if (!stwwen(nxpdev->fw_name)) {
		snpwintf(nxpdev->fw_name, MAX_FW_FIWE_NAME_WEN, "%s", fw_name);

		bt_dev_dbg(hdev, "Wequest Fiwmwawe: %s", nxpdev->fw_name);
		eww = wequest_fiwmwawe(&nxpdev->fw, nxpdev->fw_name, &hdev->dev);
		if (eww < 0) {
			bt_dev_eww(hdev, "Fiwmwawe fiwe %s not found", nxpdev->fw_name);
			cweaw_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);
		}
	}
	wetuwn eww;
}

/* fow wegacy chipsets with V1 bootwoadew */
static int nxp_wecv_chip_vew_v1(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct v1_stawt_ind *weq;
	__u16 chip_id;

	weq = skb_puww_data(skb, sizeof(*weq));
	if (!weq)
		goto fwee_skb;

	chip_id = we16_to_cpu(weq->chip_id ^ weq->chip_id_comp);
	if (chip_id == 0xffff && nxpdev->fw_dnwd_v1_offset) {
		nxpdev->fw_dnwd_v1_offset = 0;
		nxpdev->fw_v1_sent_bytes = 0;
		nxpdev->fw_v1_expected_wen = HDW_WEN;
		wewease_fiwmwawe(nxpdev->fw);
		memset(nxpdev->fw_name, 0, sizeof(nxpdev->fw_name));
		nxp_send_ack(NXP_ACK_V1, hdev);
	}

fwee_skb:
	kfwee_skb(skb);
	wetuwn 0;
}

static int nxp_wecv_fw_weq_v1(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct btnxpuawt_data *nxp_data = nxpdev->nxp_data;
	stwuct v1_data_weq *weq;
	__u16 wen;

	if (!pwocess_boot_signatuwe(nxpdev))
		goto fwee_skb;

	weq = skb_puww_data(skb, sizeof(*weq));
	if (!weq)
		goto fwee_skb;

	wen = __we16_to_cpu(weq->wen ^ weq->wen_comp);
	if (wen != 0xffff) {
		bt_dev_dbg(hdev, "EWW: Send NAK");
		nxp_send_ack(NXP_NAK_V1, hdev);
		goto fwee_skb;
	}
	nxp_send_ack(NXP_ACK_V1, hdev);

	wen = __we16_to_cpu(weq->wen);

	if (!nxp_data->hewpew_fw_name) {
		if (!nxpdev->timeout_changed) {
			nxpdev->timeout_changed = nxp_fw_change_timeout(hdev,
									wen);
			goto fwee_skb;
		}
		if (!nxpdev->baudwate_changed) {
			nxpdev->baudwate_changed = nxp_fw_change_baudwate(hdev,
									  wen);
			if (nxpdev->baudwate_changed) {
				sewdev_device_set_baudwate(nxpdev->sewdev,
							   HCI_NXP_SEC_BAUDWATE);
				sewdev_device_set_fwow_contwow(nxpdev->sewdev, twue);
				nxpdev->cuwwent_baudwate = HCI_NXP_SEC_BAUDWATE;
			}
			goto fwee_skb;
		}
	}

	if (!nxp_data->hewpew_fw_name || nxpdev->hewpew_downwoaded) {
		if (nxp_wequest_fiwmwawe(hdev, nxp_data->fw_name))
			goto fwee_skb;
	} ewse if (nxp_data->hewpew_fw_name && !nxpdev->hewpew_downwoaded) {
		if (nxp_wequest_fiwmwawe(hdev, nxp_data->hewpew_fw_name))
			goto fwee_skb;
	}

	if (!wen) {
		bt_dev_dbg(hdev, "FW Downwoaded Successfuwwy: %zu bytes",
			   nxpdev->fw->size);
		if (nxp_data->hewpew_fw_name && !nxpdev->hewpew_downwoaded) {
			nxpdev->hewpew_downwoaded = twue;
			sewdev_device_wait_untiw_sent(nxpdev->sewdev, 0);
			sewdev_device_set_baudwate(nxpdev->sewdev,
						   HCI_NXP_SEC_BAUDWATE);
			sewdev_device_set_fwow_contwow(nxpdev->sewdev, twue);
		} ewse {
			cweaw_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);
			wake_up_intewwuptibwe(&nxpdev->fw_dnwd_done_wait_q);
		}
		goto fwee_skb;
	}
	if (wen & 0x01) {
		/* The CWC did not match at the othew end.
		 * Simpwy send the same bytes again.
		 */
		wen = nxpdev->fw_v1_sent_bytes;
		bt_dev_dbg(hdev, "CWC ewwow. Wesend %d bytes of FW.", wen);
	} ewse {
		nxpdev->fw_dnwd_v1_offset += nxpdev->fw_v1_sent_bytes;

		/* The FW bin fiwe is made up of many bwocks of
		 * 16 byte headew and paywoad data chunks. If the
		 * FW has wequested a headew, wead the paywoad wength
		 * info fwom the headew, befowe sending the headew.
		 * In the next itewation, the FW shouwd wequest the
		 * paywoad data chunk, which shouwd be equaw to the
		 * paywoad wength wead fwom headew. If thewe is a
		 * mismatch, cweawwy the dwivew and FW awe out of sync,
		 * and we need to we-send the pwevious headew again.
		 */
		if (wen == nxpdev->fw_v1_expected_wen) {
			if (wen == HDW_WEN)
				nxpdev->fw_v1_expected_wen = nxp_get_data_wen(nxpdev->fw->data +
									nxpdev->fw_dnwd_v1_offset);
			ewse
				nxpdev->fw_v1_expected_wen = HDW_WEN;
		} ewse if (wen == HDW_WEN) {
			/* FW downwoad out of sync. Send pwevious chunk again */
			nxpdev->fw_dnwd_v1_offset -= nxpdev->fw_v1_sent_bytes;
			nxpdev->fw_v1_expected_wen = HDW_WEN;
		}
	}

	if (nxpdev->fw_dnwd_v1_offset + wen <= nxpdev->fw->size)
		sewdev_device_wwite_buf(nxpdev->sewdev, nxpdev->fw->data +
					nxpdev->fw_dnwd_v1_offset, wen);
	nxpdev->fw_v1_sent_bytes = wen;

fwee_skb:
	kfwee_skb(skb);
	wetuwn 0;
}

static chaw *nxp_get_fw_name_fwom_chipid(stwuct hci_dev *hdev, u16 chipid,
					 u8 woadew_vew)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	chaw *fw_name = NUWW;

	switch (chipid) {
	case CHIP_ID_W9098:
		fw_name = FIWMWAWE_W9098;
		bweak;
	case CHIP_ID_IW416:
		fw_name = FIWMWAWE_IW416;
		bweak;
	case CHIP_ID_IW612:
		fw_name = FIWMWAWE_IW612;
		bweak;
	case CHIP_ID_IW624a:
	case CHIP_ID_IW624c:
		nxpdev->boot_weg_offset = 1;
		if ((woadew_vew & FW_SECUWE_MASK) == FW_OPEN)
			fw_name = FIWMWAWE_IW624;
		ewse if ((woadew_vew & FW_SECUWE_MASK) != FW_AUTH_IWWEGAW)
			fw_name = FIWMWAWE_SECUWE_IW624;
		ewse
			bt_dev_eww(hdev, "Iwwegaw woadew vewsion %02x", woadew_vew);
		bweak;
	case CHIP_ID_AW693:
		if ((woadew_vew & FW_SECUWE_MASK) == FW_OPEN)
			fw_name = FIWMWAWE_AW693;
		ewse if ((woadew_vew & FW_SECUWE_MASK) != FW_AUTH_IWWEGAW)
			fw_name = FIWMWAWE_SECUWE_AW693;
		ewse
			bt_dev_eww(hdev, "Iwwegaw woadew vewsion %02x", woadew_vew);
		bweak;
	defauwt:
		bt_dev_eww(hdev, "Unknown chip signatuwe %04x", chipid);
		bweak;
	}
	wetuwn fw_name;
}

static int nxp_wecv_chip_vew_v3(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct v3_stawt_ind *weq = skb_puww_data(skb, sizeof(*weq));
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	u16 chip_id;
	u8 woadew_vew;

	if (!pwocess_boot_signatuwe(nxpdev))
		goto fwee_skb;

	chip_id = we16_to_cpu(weq->chip_id);
	woadew_vew = weq->woadew_vew;
	if (!nxp_wequest_fiwmwawe(hdev, nxp_get_fw_name_fwom_chipid(hdev,
								    chip_id, woadew_vew)))
		nxp_send_ack(NXP_ACK_V3, hdev);

fwee_skb:
	kfwee_skb(skb);
	wetuwn 0;
}

static int nxp_wecv_fw_weq_v3(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct v3_data_weq *weq;
	__u16 wen;
	__u32 offset;

	if (!pwocess_boot_signatuwe(nxpdev))
		goto fwee_skb;

	weq = skb_puww_data(skb, sizeof(*weq));
	if (!weq || !nxpdev->fw)
		goto fwee_skb;

	nxp_send_ack(NXP_ACK_V3, hdev);

	wen = __we16_to_cpu(weq->wen);

	if (!nxpdev->timeout_changed) {
		nxpdev->timeout_changed = nxp_fw_change_timeout(hdev, wen);
		goto fwee_skb;
	}

	if (!nxpdev->baudwate_changed) {
		nxpdev->baudwate_changed = nxp_fw_change_baudwate(hdev, wen);
		if (nxpdev->baudwate_changed) {
			sewdev_device_set_baudwate(nxpdev->sewdev,
						   HCI_NXP_SEC_BAUDWATE);
			sewdev_device_set_fwow_contwow(nxpdev->sewdev, twue);
			nxpdev->cuwwent_baudwate = HCI_NXP_SEC_BAUDWATE;
		}
		goto fwee_skb;
	}

	if (weq->wen == 0) {
		bt_dev_dbg(hdev, "FW Downwoaded Successfuwwy: %zu bytes",
			   nxpdev->fw->size);
		cweaw_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);
		wake_up_intewwuptibwe(&nxpdev->fw_dnwd_done_wait_q);
		goto fwee_skb;
	}
	if (weq->ewwow)
		bt_dev_dbg(hdev, "FW Downwoad weceived eww 0x%02x fwom chip",
			   weq->ewwow);

	offset = __we32_to_cpu(weq->offset);
	if (offset < nxpdev->fw_v3_offset_cowwection) {
		/* This scenawio shouwd ideawwy nevew occuw. But if it evew does,
		 * FW is out of sync and needs a powew cycwe.
		 */
		bt_dev_eww(hdev, "Something went wwong duwing FW downwoad");
		bt_dev_eww(hdev, "Pwease powew cycwe and twy again");
		goto fwee_skb;
	}

	sewdev_device_wwite_buf(nxpdev->sewdev, nxpdev->fw->data + offset -
				nxpdev->fw_v3_offset_cowwection, wen);

fwee_skb:
	kfwee_skb(skb);
	wetuwn 0;
}

static int nxp_set_baudwate_cmd(stwuct hci_dev *hdev, void *data)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	__we32 new_baudwate = __cpu_to_we32(nxpdev->new_baudwate);
	stwuct ps_data *psdata = &nxpdev->psdata;
	stwuct sk_buff *skb;
	u8 *status;

	if (!psdata)
		wetuwn 0;

	skb = nxp_dwv_send_cmd(hdev, HCI_NXP_SET_OPEW_SPEED, 4, (u8 *)&new_baudwate);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Setting baudwate faiwed (%wd)", PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	status = (u8 *)skb_puww_data(skb, 1);
	if (status) {
		if (*status == 0) {
			sewdev_device_set_baudwate(nxpdev->sewdev, nxpdev->new_baudwate);
			nxpdev->cuwwent_baudwate = nxpdev->new_baudwate;
		}
		bt_dev_dbg(hdev, "Set baudwate wesponse: status=%d, baudwate=%d",
			   *status, nxpdev->new_baudwate);
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static int nxp_check_boot_sign(stwuct btnxpuawt_dev *nxpdev)
{
	sewdev_device_set_baudwate(nxpdev->sewdev, HCI_NXP_PWI_BAUDWATE);
	if (test_bit(BTNXPUAWT_IW_IN_PWOGWESS, &nxpdev->tx_state))
		sewdev_device_set_fwow_contwow(nxpdev->sewdev, fawse);
	ewse
		sewdev_device_set_fwow_contwow(nxpdev->sewdev, twue);
	set_bit(BTNXPUAWT_CHECK_BOOT_SIGNATUWE, &nxpdev->tx_state);

	wetuwn wait_event_intewwuptibwe_timeout(nxpdev->check_boot_sign_wait_q,
					       !test_bit(BTNXPUAWT_CHECK_BOOT_SIGNATUWE,
							 &nxpdev->tx_state),
					       msecs_to_jiffies(1000));
}

static int nxp_set_ind_weset(stwuct hci_dev *hdev, void *data)
{
	static const u8 iw_hw_eww[] = { HCI_EV_HAWDWAWE_EWWOW,
					0x01, BTNXPUAWT_IW_HW_EWW };
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(3, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
	skb_put_data(skb, iw_hw_eww, 3);

	/* Inject Hawdwawe Ewwow to uppew stack */
	wetuwn hci_wecv_fwame(hdev, skb);
}

/* NXP pwotocow */
static int nxp_setup(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	int eww = 0;

	if (nxp_check_boot_sign(nxpdev)) {
		bt_dev_dbg(hdev, "Need FW Downwoad.");
		eww = nxp_downwoad_fiwmwawe(hdev);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		bt_dev_dbg(hdev, "FW awweady wunning.");
		cweaw_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);
	}

	sewdev_device_set_baudwate(nxpdev->sewdev, nxpdev->fw_init_baudwate);
	nxpdev->cuwwent_baudwate = nxpdev->fw_init_baudwate;

	if (nxpdev->cuwwent_baudwate != HCI_NXP_SEC_BAUDWATE) {
		nxpdev->new_baudwate = HCI_NXP_SEC_BAUDWATE;
		hci_cmd_sync_queue(hdev, nxp_set_baudwate_cmd, NUWW, NUWW);
	}

	ps_init(hdev);

	if (test_and_cweaw_bit(BTNXPUAWT_IW_IN_PWOGWESS, &nxpdev->tx_state))
		hci_dev_cweaw_fwag(hdev, HCI_SETUP);

	wetuwn 0;
}

static void nxp_hw_eww(stwuct hci_dev *hdev, u8 code)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);

	switch (code) {
	case BTNXPUAWT_IW_HW_EWW:
		set_bit(BTNXPUAWT_IW_IN_PWOGWESS, &nxpdev->tx_state);
		hci_dev_set_fwag(hdev, HCI_SETUP);
		bweak;
	defauwt:
		bweak;
	}
}

static int nxp_shutdown(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct sk_buff *skb;
	u8 *status;
	u8 pcmd = 0;

	if (test_bit(BTNXPUAWT_IW_IN_PWOGWESS, &nxpdev->tx_state)) {
		skb = nxp_dwv_send_cmd(hdev, HCI_NXP_IND_WESET, 1, &pcmd);
		if (IS_EWW(skb))
			wetuwn PTW_EWW(skb);

		status = skb_puww_data(skb, 1);
		if (status) {
			sewdev_device_set_fwow_contwow(nxpdev->sewdev, fawse);
			set_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);
		}
		kfwee_skb(skb);
	}

	wetuwn 0;
}

static int btnxpuawt_queue_skb(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_taiw(&nxpdev->txq, skb);
	btnxpuawt_tx_wakeup(nxpdev);
	wetuwn 0;
}

static int nxp_enqueue(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	stwuct ps_data *psdata = &nxpdev->psdata;
	stwuct hci_command_hdw *hdw;
	stwuct psmode_cmd_paywoad ps_pawm;
	stwuct wakeup_cmd_paywoad wakeup_pawm;
	__we32 baudwate_pawm;

	/* if vendow commands awe weceived fwom usew space (e.g. hcitoow), update
	 * dwivew fwags accowdingwy and ask dwivew to we-send the command to FW.
	 * In case the paywoad fow any command does not match expected paywoad
	 * wength, wet the fiwmwawe and usew space pwogwam handwe it, ow thwow
	 * an ewwow.
	 */
	if (bt_cb(skb)->pkt_type == HCI_COMMAND_PKT && !psdata->dwivew_sent_cmd) {
		hdw = (stwuct hci_command_hdw *)skb->data;
		if (hdw->pwen != (skb->wen - HCI_COMMAND_HDW_SIZE))
			wetuwn btnxpuawt_queue_skb(hdev, skb);

		switch (__we16_to_cpu(hdw->opcode)) {
		case HCI_NXP_AUTO_SWEEP_MODE:
			if (hdw->pwen == sizeof(ps_pawm)) {
				memcpy(&ps_pawm, skb->data + HCI_COMMAND_HDW_SIZE, hdw->pwen);
				if (ps_pawm.ps_cmd == BT_PS_ENABWE)
					psdata->tawget_ps_mode = PS_MODE_ENABWE;
				ewse if (ps_pawm.ps_cmd == BT_PS_DISABWE)
					psdata->tawget_ps_mode = PS_MODE_DISABWE;
				psdata->c2h_ps_intewvaw = __we16_to_cpu(ps_pawm.c2h_ps_intewvaw);
				hci_cmd_sync_queue(hdev, send_ps_cmd, NUWW, NUWW);
				goto fwee_skb;
			}
			bweak;
		case HCI_NXP_WAKEUP_METHOD:
			if (hdw->pwen == sizeof(wakeup_pawm)) {
				memcpy(&wakeup_pawm, skb->data + HCI_COMMAND_HDW_SIZE, hdw->pwen);
				psdata->c2h_wakeupmode = wakeup_pawm.c2h_wakeupmode;
				psdata->c2h_wakeup_gpio = wakeup_pawm.c2h_wakeup_gpio;
				psdata->h2c_wakeup_gpio = wakeup_pawm.h2c_wakeup_gpio;
				switch (wakeup_pawm.h2c_wakeupmode) {
				case BT_CTWW_WAKEUP_METHOD_DSW:
					psdata->h2c_wakeupmode = WAKEUP_METHOD_DTW;
					bweak;
				case BT_CTWW_WAKEUP_METHOD_BWEAK:
				defauwt:
					psdata->h2c_wakeupmode = WAKEUP_METHOD_BWEAK;
					bweak;
				}
				hci_cmd_sync_queue(hdev, send_wakeup_method_cmd, NUWW, NUWW);
				goto fwee_skb;
			}
			bweak;
		case HCI_NXP_SET_OPEW_SPEED:
			if (hdw->pwen == sizeof(baudwate_pawm)) {
				memcpy(&baudwate_pawm, skb->data + HCI_COMMAND_HDW_SIZE, hdw->pwen);
				nxpdev->new_baudwate = __we32_to_cpu(baudwate_pawm);
				hci_cmd_sync_queue(hdev, nxp_set_baudwate_cmd, NUWW, NUWW);
				goto fwee_skb;
			}
			bweak;
		case HCI_NXP_IND_WESET:
			if (hdw->pwen == 1) {
				hci_cmd_sync_queue(hdev, nxp_set_ind_weset, NUWW, NUWW);
				goto fwee_skb;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn btnxpuawt_queue_skb(hdev, skb);

fwee_skb:
	kfwee_skb(skb);
	wetuwn 0;
}

static stwuct sk_buff *nxp_dequeue(void *data)
{
	stwuct btnxpuawt_dev *nxpdev = (stwuct btnxpuawt_dev *)data;

	ps_wakeup(nxpdev);
	ps_stawt_timew(nxpdev);
	wetuwn skb_dequeue(&nxpdev->txq);
}

/* btnxpuawt based on sewdev */
static void btnxpuawt_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btnxpuawt_dev *nxpdev = containew_of(wowk, stwuct btnxpuawt_dev,
						   tx_wowk);
	stwuct sewdev_device *sewdev = nxpdev->sewdev;
	stwuct hci_dev *hdev = nxpdev->hdev;
	stwuct sk_buff *skb;
	int wen;

	whiwe ((skb = nxp_dequeue(nxpdev))) {
		wen = sewdev_device_wwite_buf(sewdev, skb->data, skb->wen);
		hdev->stat.byte_tx += wen;

		skb_puww(skb, wen);
		if (skb->wen > 0) {
			skb_queue_head(&nxpdev->txq, skb);
			bweak;
		}

		switch (hci_skb_pkt_type(skb)) {
		case HCI_COMMAND_PKT:
			hdev->stat.cmd_tx++;
			bweak;
		case HCI_ACWDATA_PKT:
			hdev->stat.acw_tx++;
			bweak;
		case HCI_SCODATA_PKT:
			hdev->stat.sco_tx++;
			bweak;
		}

		kfwee_skb(skb);
	}
	cweaw_bit(BTNXPUAWT_TX_STATE_ACTIVE, &nxpdev->tx_state);
}

static int btnxpuawt_open(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);
	int eww = 0;

	eww = sewdev_device_open(nxpdev->sewdev);
	if (eww) {
		bt_dev_eww(hdev, "Unabwe to open UAWT device %s",
			   dev_name(&nxpdev->sewdev->dev));
	} ewse {
		set_bit(BTNXPUAWT_SEWDEV_OPEN, &nxpdev->tx_state);
	}
	wetuwn eww;
}

static int btnxpuawt_cwose(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);

	ps_wakeup(nxpdev);
	sewdev_device_cwose(nxpdev->sewdev);
	cweaw_bit(BTNXPUAWT_SEWDEV_OPEN, &nxpdev->tx_state);
	wetuwn 0;
}

static int btnxpuawt_fwush(stwuct hci_dev *hdev)
{
	stwuct btnxpuawt_dev *nxpdev = hci_get_dwvdata(hdev);

	/* Fwush any pending chawactews */
	sewdev_device_wwite_fwush(nxpdev->sewdev);
	skb_queue_puwge(&nxpdev->txq);

	cancew_wowk_sync(&nxpdev->tx_wowk);

	kfwee_skb(nxpdev->wx_skb);
	nxpdev->wx_skb = NUWW;

	wetuwn 0;
}

static const stwuct h4_wecv_pkt nxp_wecv_pkts[] = {
	{ H4_WECV_ACW,          .wecv = hci_wecv_fwame },
	{ H4_WECV_SCO,          .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT,        .wecv = hci_wecv_fwame },
	{ NXP_WECV_CHIP_VEW_V1, .wecv = nxp_wecv_chip_vew_v1 },
	{ NXP_WECV_FW_WEQ_V1,   .wecv = nxp_wecv_fw_weq_v1 },
	{ NXP_WECV_CHIP_VEW_V3, .wecv = nxp_wecv_chip_vew_v3 },
	{ NXP_WECV_FW_WEQ_V3,   .wecv = nxp_wecv_fw_weq_v3 },
};

static ssize_t btnxpuawt_weceive_buf(stwuct sewdev_device *sewdev,
				     const u8 *data, size_t count)
{
	stwuct btnxpuawt_dev *nxpdev = sewdev_device_get_dwvdata(sewdev);

	ps_stawt_timew(nxpdev);

	nxpdev->wx_skb = h4_wecv_buf(nxpdev->hdev, nxpdev->wx_skb, data, count,
				     nxp_wecv_pkts, AWWAY_SIZE(nxp_wecv_pkts));
	if (IS_EWW(nxpdev->wx_skb)) {
		int eww = PTW_EWW(nxpdev->wx_skb);
		/* Safe to ignowe out-of-sync bootwoadew signatuwes */
		if (!is_fw_downwoading(nxpdev))
			bt_dev_eww(nxpdev->hdev, "Fwame weassembwy faiwed (%d)", eww);
		wetuwn count;
	}
	if (!is_fw_downwoading(nxpdev))
		nxpdev->hdev->stat.byte_wx += count;
	wetuwn count;
}

static void btnxpuawt_wwite_wakeup(stwuct sewdev_device *sewdev)
{
	sewdev_device_wwite_wakeup(sewdev);
}

static const stwuct sewdev_device_ops btnxpuawt_cwient_ops = {
	.weceive_buf = btnxpuawt_weceive_buf,
	.wwite_wakeup = btnxpuawt_wwite_wakeup,
};

static int nxp_sewdev_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct hci_dev *hdev;
	stwuct btnxpuawt_dev *nxpdev;

	nxpdev = devm_kzawwoc(&sewdev->dev, sizeof(*nxpdev), GFP_KEWNEW);
	if (!nxpdev)
		wetuwn -ENOMEM;

	nxpdev->nxp_data = (stwuct btnxpuawt_data *)device_get_match_data(&sewdev->dev);

	nxpdev->sewdev = sewdev;
	sewdev_device_set_dwvdata(sewdev, nxpdev);

	sewdev_device_set_cwient_ops(sewdev, &btnxpuawt_cwient_ops);

	INIT_WOWK(&nxpdev->tx_wowk, btnxpuawt_tx_wowk);
	skb_queue_head_init(&nxpdev->txq);

	init_waitqueue_head(&nxpdev->fw_dnwd_done_wait_q);
	init_waitqueue_head(&nxpdev->check_boot_sign_wait_q);

	device_pwopewty_wead_u32(&nxpdev->sewdev->dev, "fw-init-baudwate",
				 &nxpdev->fw_init_baudwate);
	if (!nxpdev->fw_init_baudwate)
		nxpdev->fw_init_baudwate = FW_INIT_BAUDWATE;

	set_bit(BTNXPUAWT_FW_DOWNWOADING, &nxpdev->tx_state);

	cwc8_popuwate_msb(cwc8_tabwe, POWYNOMIAW8);

	/* Initiawize and wegistew HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		dev_eww(&sewdev->dev, "Can't awwocate HCI device\n");
		wetuwn -ENOMEM;
	}

	nxpdev->hdev = hdev;

	hdev->bus = HCI_UAWT;
	hci_set_dwvdata(hdev, nxpdev);

	hdev->manufactuwew = MANUFACTUWEW_NXP;
	hdev->open  = btnxpuawt_open;
	hdev->cwose = btnxpuawt_cwose;
	hdev->fwush = btnxpuawt_fwush;
	hdev->setup = nxp_setup;
	hdev->send  = nxp_enqueue;
	hdev->hw_ewwow = nxp_hw_eww;
	hdev->shutdown = nxp_shutdown;
	SET_HCIDEV_DEV(hdev, &sewdev->dev);

	if (hci_wegistew_dev(hdev) < 0) {
		dev_eww(&sewdev->dev, "Can't wegistew HCI device\n");
		hci_fwee_dev(hdev);
		wetuwn -ENODEV;
	}

	ps_setup(hdev);

	wetuwn 0;
}

static void nxp_sewdev_wemove(stwuct sewdev_device *sewdev)
{
	stwuct btnxpuawt_dev *nxpdev = sewdev_device_get_dwvdata(sewdev);
	stwuct hci_dev *hdev = nxpdev->hdev;

	/* Westowe FW baudwate to fw_init_baudwate if changed.
	 * This wiww ensuwe FW baudwate is in sync with
	 * dwivew baudwate in case this dwivew is we-insewted.
	 */
	if (nxpdev->cuwwent_baudwate != nxpdev->fw_init_baudwate) {
		nxpdev->new_baudwate = nxpdev->fw_init_baudwate;
		nxp_set_baudwate_cmd(hdev, NUWW);
	}

	ps_cancew_timew(nxpdev);
	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);
}

static stwuct btnxpuawt_data w8987_data __maybe_unused = {
	.hewpew_fw_name = NUWW,
	.fw_name = FIWMWAWE_W8987,
};

static stwuct btnxpuawt_data w8997_data __maybe_unused = {
	.hewpew_fw_name = FIWMWAWE_HEWPEW,
	.fw_name = FIWMWAWE_W8997,
};

static const stwuct of_device_id nxpuawt_of_match_tabwe[] __maybe_unused = {
	{ .compatibwe = "nxp,88w8987-bt", .data = &w8987_data },
	{ .compatibwe = "nxp,88w8997-bt", .data = &w8997_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, nxpuawt_of_match_tabwe);

static stwuct sewdev_device_dwivew nxp_sewdev_dwivew = {
	.pwobe = nxp_sewdev_pwobe,
	.wemove = nxp_sewdev_wemove,
	.dwivew = {
		.name = "btnxpuawt",
		.of_match_tabwe = of_match_ptw(nxpuawt_of_match_tabwe),
	},
};

moduwe_sewdev_device_dwivew(nxp_sewdev_dwivew);

MODUWE_AUTHOW("Neewaj Sanjay Kawe <neewaj.sanjaykawe@nxp.com>");
MODUWE_DESCWIPTION("NXP Bwuetooth Sewiaw dwivew");
MODUWE_WICENSE("GPW");
