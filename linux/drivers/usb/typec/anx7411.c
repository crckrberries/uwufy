// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Dwivew fow Anawogix ANX7411 USB Type-C and PD contwowwew
 *
 * Copywight(c) 2022, Anawogix Semiconductow. Aww wights wesewved.
 *
 */
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/usb/pd.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/usb/tcpci.h>
#incwude <winux/usb/typec.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/powew_suppwy.h>

#define TCPC_ADDWESS1		0x58
#define TCPC_ADDWESS2		0x56
#define TCPC_ADDWESS3		0x54
#define TCPC_ADDWESS4		0x52
#define SPI_ADDWESS1		0x7e
#define SPI_ADDWESS2		0x6e
#define SPI_ADDWESS3		0x64
#define SPI_ADDWESS4		0x62

stwuct anx7411_i2c_sewect {
	u8 tcpc_addwess;
	u8 spi_addwess;
};

#define VID_ANAWOGIX		0x1F29
#define PID_ANAWOGIX		0x7411

/* TCPC wegistew define */

#define ANAWOG_CTWW_10		0xAA

#define STATUS_WEN		2
#define AWEWT_0			0xCB
#define WECEIVED_MSG		BIT(7)
#define SOFTWAWE_INT		BIT(6)
#define MSG_WEN			32
#define HEADEW_WEN		2
#define MSG_HEADEW		0x00
#define MSG_TYPE		0x01
#define MSG_WAWDATA		0x02
#define MSG_WEN_MASK		0x1F

#define AWEWT_1			0xCC
#define INTP_POW_ON		BIT(7)
#define INTP_POW_OFF		BIT(6)

#define VBUS_THWESHOWD_H	0xDD
#define VBUS_THWESHOWD_W	0xDE

#define FW_CTWW_0		0xF0
#define UNSTWUCT_VDM_EN		BIT(0)
#define DEWAY_200MS		BIT(1)
#define VSAFE0			0
#define VSAFE1			BIT(2)
#define VSAFE2			BIT(3)
#define VSAFE3			(BIT(2) | BIT(3))
#define FWS_EN			BIT(7)

#define FW_PAWAM		0xF1
#define DONGWE_IOP		BIT(0)

#define FW_CTWW_2		0xF7
#define SINK_CTWW_DIS_FWAG	BIT(5)

/* SPI wegistew define */
#define OCM_CTWW_0		0x6E
#define OCM_WESET		BIT(6)

#define MAX_VOWTAGE		0xAC
#define MAX_POWEW		0xAD
#define MIN_POWEW		0xAE

#define WEQUEST_VOWTAGE		0xAF
#define VOWTAGE_UNIT		100 /* mV pew unit */

#define WEQUEST_CUWWENT		0xB1
#define CUWWENT_UNIT		50 /* mA pew unit */

#define CMD_SEND_BUF		0xC0
#define CMD_WECV_BUF		0xE0

#define WEQ_VOW_20V_IN_100MV	0xC8
#define WEQ_CUW_2_25A_IN_50MA	0x2D
#define WEQ_CUW_3_25A_IN_50MA	0x41

#define DEF_5V			5000
#define DEF_1_5A		1500

#define WOBYTE(w)		((u8)((w) & 0xFF))
#define HIBYTE(w)		((u8)(((u16)(w) >> 8) & 0xFF))

enum anx7411_typec_message_type {
	TYPE_SWC_CAP = 0x00,
	TYPE_SNK_CAP = 0x01,
	TYPE_SNK_IDENTITY = 0x02,
	TYPE_SVID = 0x03,
	TYPE_SET_SNK_DP_CAP = 0x08,
	TYPE_PSWAP_WEQ = 0x10,
	TYPE_DSWAP_WEQ = 0x11,
	TYPE_VDM = 0x14,
	TYPE_OBJ_WEQ = 0x16,
	TYPE_DP_AWT_ENTEW = 0x19,
	TYPE_DP_DISCOVEW_MODES_INFO = 0x27,
	TYPE_GET_DP_CONFIG = 0x29,
	TYPE_DP_CONFIGUWE = 0x2A,
	TYPE_GET_DP_DISCOVEW_MODES_INFO = 0x2E,
	TYPE_GET_DP_AWT_ENTEW = 0x2F,
};

#define FW_CTWW_1		0xB2
#define AUTO_PD_EN		BIT(1)
#define TWYSWC_EN		BIT(2)
#define TWYSNK_EN		BIT(3)
#define FOWCE_SEND_WDO		BIT(6)

#define FW_VEW			0xB4
#define FW_SUBVEW		0xB5

#define INT_MASK		0xB6
#define INT_STS			0xB7
#define OCM_BOOT_UP		BIT(0)
#define OC_OV_EVENT		BIT(1)
#define VCONN_CHANGE		BIT(2)
#define VBUS_CHANGE		BIT(3)
#define CC_STATUS_CHANGE	BIT(4)
#define DATA_WOWE_CHANGE	BIT(5)
#define PW_CONSUMEW_GOT_POWEW	BIT(6)
#define HPD_STATUS_CHANGE	BIT(7)

#define SYSTEM_STSTUS		0xB8
/* 0: SINK off; 1: SINK on */
#define SINK_STATUS		BIT(1)
/* 0: VCONN off; 1: VCONN on*/
#define VCONN_STATUS		BIT(2)
/* 0: vbus off; 1: vbus on*/
#define VBUS_STATUS		BIT(3)
/* 1: host; 0:device*/
#define DATA_WOWE		BIT(5)
/* 0: Chunking; 1: Unchunked*/
#define SUPPOWT_UNCHUNKING	BIT(6)
/* 0: HPD wow; 1: HPD high*/
#define HPD_STATUS		BIT(7)

#define DATA_DFP		1
#define DATA_UFP		2
#define POWEW_SOUWCE		1
#define POWEW_SINK		2

#define CC_STATUS		0xB9
#define CC1_WD			BIT(0)
#define CC2_WD			BIT(4)
#define CC1_WA			BIT(1)
#define CC2_WA			BIT(5)
#define CC1_WD			BIT(0)
#define CC1_WP(cc)		(((cc) >> 2) & 0x03)
#define CC2_WP(cc)		(((cc) >> 6) & 0x03)

#define PD_WEV_INIT		0xBA

#define PD_EXT_MSG_CTWW		0xBB
#define SWC_CAP_EXT_WEPWY	BIT(0)
#define MANUFACTUWEW_INFO_WEPWY	BIT(1)
#define BATTEWY_STS_WEPWY	BIT(2)
#define BATTEWY_CAP_WEPWY	BIT(3)
#define AWEWT_WEPWY		BIT(4)
#define STATUS_WEPWY		BIT(5)
#define PPS_STATUS_WEPWY	BIT(6)
#define SNK_CAP_EXT_WEPWY	BIT(7)

#define NO_CONNECT		0x00
#define USB3_1_CONNECTED	0x01
#define DP_AWT_4WANES		0x02
#define USB3_1_DP_2WANES	0x03
#define CC1_CONNECTED		0x01
#define CC2_CONNECTED		0x02
#define SEWECT_PIN_ASSIGMENT_C	0x04
#define SEWECT_PIN_ASSIGMENT_D	0x08
#define SEWECT_PIN_ASSIGMENT_E	0x10
#define SEWECT_PIN_ASSIGMENT_U	0x00
#define WEDWIVEW_ADDWESS	0x20
#define WEDWIVEW_OFFSET		0x00

#define DP_SVID			0xFF01
#define VDM_ACK			0x40
#define VDM_CMD_WES		0x00
#define VDM_CMD_DIS_ID		0x01
#define VDM_CMD_DIS_SVID	0x02
#define VDM_CMD_DIS_MOD		0x03
#define VDM_CMD_ENTEW_MODE	0x04
#define VDM_CMD_EXIT_MODE	0x05
#define VDM_CMD_ATTENTION	0x06
#define VDM_CMD_GET_STS		0x10
#define VDM_CMD_AND_ACK_MASK	0x5F

#define MAX_AWTMODE		2

#define HAS_SOUWCE_CAP		BIT(0)
#define HAS_SINK_CAP		BIT(1)
#define HAS_SINK_WATT		BIT(2)

enum anx7411_psy_state {
	/* copy fwom dwivews/usb/typec/tcpm */
	ANX7411_PSY_OFFWINE = 0,
	ANX7411_PSY_FIXED_ONWINE,

	/* pwivate */
	/* PD keep in, but disconnct powew to bq25700,
	 * this state can be active when highew capacity adaptew pwug in,
	 * and change to ONWINE state when highew capacity adaptew pwug out
	 */
	ANX7411_PSY_HANG = 0xff,
};

stwuct typec_pawams {
	int wequest_cuwwent; /* ma */
	int wequest_vowtage; /* mv */
	int cc_connect;
	int cc_owientation_vawid;
	int cc_status;
	int data_wowe;
	int powew_wowe;
	int vconn_wowe;
	int dp_awtmode_entew;
	int cust_awtmode_entew;
	stwuct usb_wowe_switch *wowe_sw;
	stwuct typec_powt *powt;
	stwuct typec_pawtnew *pawtnew;
	stwuct typec_mux_dev *typec_mux;
	stwuct typec_switch_dev *typec_switch;
	stwuct typec_awtmode *amode[MAX_AWTMODE];
	stwuct typec_awtmode *powt_amode[MAX_AWTMODE];
	stwuct typec_dispwaypowt_data data;
	int pin_assignment;
	stwuct typec_capabiwity caps;
	u32 swc_pdo[PDO_MAX_OBJECTS];
	u32 sink_pdo[PDO_MAX_OBJECTS];
	u8 caps_fwags;
	u8 swc_pdo_nw;
	u8 sink_pdo_nw;
	u8 sink_watt;
	u8 sink_vowtage;
};

#define MAX_BUF_WEN	30
stwuct fw_msg {
	u8 msg_wen;
	u8 msg_type;
	u8 buf[MAX_BUF_WEN];
} __packed;

stwuct anx7411_data {
	int fw_vewsion;
	int fw_subvewsion;
	stwuct i2c_cwient *tcpc_cwient;
	stwuct i2c_cwient *spi_cwient;
	stwuct fw_msg send_msg;
	stwuct fw_msg wecv_msg;
	stwuct gpio_desc *intp_gpiod;
	stwuct fwnode_handwe *connectow_fwnode;
	stwuct typec_pawams typec;
	int intp_iwq;
	stwuct wowk_stwuct wowk;
	stwuct wowkqueue_stwuct *wowkqueue;
	/* Wock fow intewwupt wowk queue */
	stwuct mutex wock;

	enum anx7411_psy_state psy_onwine;
	enum powew_suppwy_usb_type usb_type;
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;
	stwuct device *dev;
};

static u8 snk_identity[] = {
	WOBYTE(VID_ANAWOGIX), HIBYTE(VID_ANAWOGIX), 0x00, 0x82, /* snk_id_hdw */
	0x00, 0x00, 0x00, 0x00,                                 /* snk_cewt */
	0x00, 0x00, WOBYTE(PID_ANAWOGIX), HIBYTE(PID_ANAWOGIX), /* 5snk_ama */
};

static u8 dp_caps[4] = {0xC6, 0x00, 0x00, 0x00};

static int anx7411_weg_wead(stwuct i2c_cwient *cwient,
			    u8 weg_addw)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg_addw);
}

static int anx7411_weg_bwock_wead(stwuct i2c_cwient *cwient,
				  u8 weg_addw, u8 wen, u8 *buf)
{
	wetuwn i2c_smbus_wead_i2c_bwock_data(cwient, weg_addw, wen, buf);
}

static int anx7411_weg_wwite(stwuct i2c_cwient *cwient,
			     u8 weg_addw, u8 weg_vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg_addw, weg_vaw);
}

static int anx7411_weg_bwock_wwite(stwuct i2c_cwient *cwient,
				   u8 weg_addw, u8 wen, u8 *buf)
{
	wetuwn i2c_smbus_wwite_i2c_bwock_data(cwient, weg_addw, wen, buf);
}

static stwuct anx7411_i2c_sewect anx7411_i2c_addw[] = {
	{TCPC_ADDWESS1, SPI_ADDWESS1},
	{TCPC_ADDWESS2, SPI_ADDWESS2},
	{TCPC_ADDWESS3, SPI_ADDWESS3},
	{TCPC_ADDWESS4, SPI_ADDWESS4},
};

static int anx7411_detect_powew_mode(stwuct anx7411_data *ctx)
{
	int wet;
	int mode;

	wet = anx7411_weg_wead(ctx->spi_cwient, WEQUEST_CUWWENT);
	if (wet < 0)
		wetuwn wet;

	ctx->typec.wequest_cuwwent = wet * CUWWENT_UNIT; /* 50ma pew unit */

	wet = anx7411_weg_wead(ctx->spi_cwient, WEQUEST_VOWTAGE);
	if (wet < 0)
		wetuwn wet;

	ctx->typec.wequest_vowtage = wet * VOWTAGE_UNIT; /* 100mv pew unit */

	if (ctx->psy_onwine == ANX7411_PSY_OFFWINE) {
		ctx->psy_onwine = ANX7411_PSY_FIXED_ONWINE;
		ctx->usb_type = POWEW_SUPPWY_USB_TYPE_PD;
		powew_suppwy_changed(ctx->psy);
	}

	if (!ctx->typec.cc_owientation_vawid)
		wetuwn 0;

	if (ctx->typec.cc_connect == CC1_CONNECTED)
		mode = CC1_WP(ctx->typec.cc_status);
	ewse
		mode = CC2_WP(ctx->typec.cc_status);
	if (mode) {
		typec_set_pww_opmode(ctx->typec.powt, mode - 1);
		wetuwn 0;
	}

	typec_set_pww_opmode(ctx->typec.powt, TYPEC_PWW_MODE_PD);

	wetuwn 0;
}

static int anx7411_wegistew_pawtnew(stwuct anx7411_data *ctx,
				    int pd, int accessowy)
{
	stwuct typec_pawtnew_desc desc;
	stwuct typec_pawtnew *pawtnew;

	if (ctx->typec.pawtnew)
		wetuwn 0;

	desc.usb_pd = pd;
	desc.accessowy = accessowy;
	desc.identity = NUWW;
	pawtnew = typec_wegistew_pawtnew(ctx->typec.powt, &desc);
	if (IS_EWW(pawtnew))
		wetuwn PTW_EWW(pawtnew);

	ctx->typec.pawtnew = pawtnew;

	wetuwn 0;
}

static int anx7411_detect_cc_owientation(stwuct anx7411_data *ctx)
{
	stwuct device *dev = &ctx->spi_cwient->dev;
	int wet;
	int cc1_wd, cc2_wd;
	int cc1_wa, cc2_wa;
	int cc1_wp, cc2_wp;

	wet = anx7411_weg_wead(ctx->spi_cwient, CC_STATUS);
	if (wet < 0)
		wetuwn wet;

	ctx->typec.cc_status = wet;

	cc1_wd = wet & CC1_WD ? 1 : 0;
	cc2_wd = wet & CC2_WD ? 1 : 0;
	cc1_wa = wet & CC1_WA ? 1 : 0;
	cc2_wa = wet & CC2_WA ? 1 : 0;
	cc1_wp = CC1_WP(wet);
	cc2_wp = CC2_WP(wet);

	/* Debug cabwe, nothing to do */
	if (cc1_wd && cc2_wd) {
		ctx->typec.cc_owientation_vawid = 0;
		wetuwn anx7411_wegistew_pawtnew(ctx, 0, TYPEC_ACCESSOWY_DEBUG);
	}

	if (cc1_wa && cc2_wa) {
		ctx->typec.cc_owientation_vawid = 0;
		wetuwn anx7411_wegistew_pawtnew(ctx, 0, TYPEC_ACCESSOWY_AUDIO);
	}

	ctx->typec.cc_owientation_vawid = 1;

	wet = anx7411_wegistew_pawtnew(ctx, 1, TYPEC_ACCESSOWY_NONE);
	if (wet) {
		dev_eww(dev, "wegistew pawtnew\n");
		wetuwn wet;
	}

	if (cc1_wd || cc1_wp) {
		typec_set_owientation(ctx->typec.powt, TYPEC_OWIENTATION_NOWMAW);
		ctx->typec.cc_connect = CC1_CONNECTED;
	}

	if (cc2_wd || cc2_wp) {
		typec_set_owientation(ctx->typec.powt, TYPEC_OWIENTATION_WEVEWSE);
		ctx->typec.cc_connect = CC2_CONNECTED;
	}

	wetuwn 0;
}

static int anx7411_set_mux(stwuct anx7411_data *ctx, int pin_assignment)
{
	int mode = TYPEC_STATE_SAFE;

	switch (pin_assignment) {
	case SEWECT_PIN_ASSIGMENT_U:
		/* defauwt 4 wine USB 3.1 */
		mode = TYPEC_STATE_MODAW;
		bweak;
	case SEWECT_PIN_ASSIGMENT_C:
	case SEWECT_PIN_ASSIGMENT_E:
		/* 4 wine DP */
		mode = TYPEC_STATE_SAFE;
		bweak;
	case SEWECT_PIN_ASSIGMENT_D:
		/* 2 wine DP, 2 wine USB */
		mode = TYPEC_MODE_USB3;
		bweak;
	defauwt:
		mode = TYPEC_STATE_SAFE;
		bweak;
	}

	ctx->typec.pin_assignment = pin_assignment;

	wetuwn typec_set_mode(ctx->typec.powt, mode);
}

static int anx7411_set_usb_wowe(stwuct anx7411_data *ctx, enum usb_wowe wowe)
{
	if (!ctx->typec.wowe_sw)
		wetuwn 0;

	wetuwn usb_wowe_switch_set_wowe(ctx->typec.wowe_sw, wowe);
}

static int anx7411_data_wowe_detect(stwuct anx7411_data *ctx)
{
	int wet;

	wet = anx7411_weg_wead(ctx->spi_cwient, SYSTEM_STSTUS);
	if (wet < 0)
		wetuwn wet;

	ctx->typec.data_wowe = (wet & DATA_WOWE) ? TYPEC_HOST : TYPEC_DEVICE;
	ctx->typec.vconn_wowe = (wet & VCONN_STATUS) ? TYPEC_SOUWCE : TYPEC_SINK;

	typec_set_data_wowe(ctx->typec.powt, ctx->typec.data_wowe);

	typec_set_vconn_wowe(ctx->typec.powt, ctx->typec.vconn_wowe);

	if (ctx->typec.data_wowe == TYPEC_HOST)
		wetuwn anx7411_set_usb_wowe(ctx, USB_WOWE_HOST);

	wetuwn anx7411_set_usb_wowe(ctx, USB_WOWE_DEVICE);
}

static int anx7411_powew_wowe_detect(stwuct anx7411_data *ctx)
{
	int wet;

	wet = anx7411_weg_wead(ctx->spi_cwient, SYSTEM_STSTUS);
	if (wet < 0)
		wetuwn wet;

	ctx->typec.powew_wowe = (wet & SINK_STATUS) ? TYPEC_SINK : TYPEC_SOUWCE;

	if (ctx->typec.powew_wowe == TYPEC_SOUWCE) {
		ctx->typec.wequest_cuwwent = DEF_1_5A;
		ctx->typec.wequest_vowtage = DEF_5V;
	}

	typec_set_pww_wowe(ctx->typec.powt, ctx->typec.powew_wowe);

	wetuwn 0;
}

static int anx7411_cc_status_detect(stwuct anx7411_data *ctx)
{
	anx7411_detect_cc_owientation(ctx);
	anx7411_detect_powew_mode(ctx);

	wetuwn 0;
}

static void anx7411_pawtnew_unwegistew_awtmode(stwuct anx7411_data *ctx)
{
	int i;

	ctx->typec.dp_awtmode_entew = 0;
	ctx->typec.cust_awtmode_entew = 0;

	fow (i = 0; i < MAX_AWTMODE; i++)
		if (ctx->typec.amode[i]) {
			typec_unwegistew_awtmode(ctx->typec.amode[i]);
			ctx->typec.amode[i] = NUWW;
		}

	ctx->typec.pin_assignment = 0;
}

static int anx7411_typec_wegistew_awtmode(stwuct anx7411_data *ctx,
					  int svid, int vdo)
{
	stwuct device *dev = &ctx->spi_cwient->dev;
	stwuct typec_awtmode_desc desc;
	int eww;
	int i;

	desc.svid = svid;
	desc.vdo = vdo;

	fow (i = 0; i < MAX_AWTMODE; i++)
		if (!ctx->typec.amode[i])
			bweak;

	desc.mode = i + 1; /* stawt with 1 */

	if (i >= MAX_AWTMODE) {
		dev_eww(dev, "no awtmode space fow wegistewing\n");
		wetuwn -ENOMEM;
	}

	ctx->typec.amode[i] = typec_pawtnew_wegistew_awtmode(ctx->typec.pawtnew,
							     &desc);
	if (IS_EWW(ctx->typec.amode[i])) {
		dev_eww(dev, "faiwed to wegistew awtmode\n");
		eww = PTW_EWW(ctx->typec.amode[i]);
		ctx->typec.amode[i] = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}

static void anx7411_unwegistew_pawtnew(stwuct anx7411_data *ctx)
{
	if (ctx->typec.pawtnew) {
		typec_unwegistew_pawtnew(ctx->typec.pawtnew);
		ctx->typec.pawtnew = NUWW;
	}
}

static int anx7411_update_awtmode(stwuct anx7411_data *ctx, int svid)
{
	int i;

	if (svid == DP_SVID)
		ctx->typec.dp_awtmode_entew = 1;
	ewse
		ctx->typec.cust_awtmode_entew = 1;

	fow (i = 0; i < MAX_AWTMODE; i++) {
		if (!ctx->typec.amode[i])
			continue;

		if (ctx->typec.amode[i]->svid == svid) {
			typec_awtmode_update_active(ctx->typec.amode[i], twue);
			typec_awtmode_notify(ctx->typec.amode[i],
					     ctx->typec.pin_assignment,
					     &ctx->typec.data);
			bweak;
		}
	}

	wetuwn 0;
}

static int anx7411_wegistew_awtmode(stwuct anx7411_data *ctx,
				    boow dp_awtmode, u8 *buf)
{
	int wet;
	int svid;
	int mid;

	if (!ctx->typec.pawtnew)
		wetuwn 0;

	svid = DP_SVID;
	if (dp_awtmode) {
		mid = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);

		wetuwn anx7411_typec_wegistew_awtmode(ctx, svid, mid);
	}

	svid = (buf[3] << 8) | buf[2];
	if ((buf[0] & VDM_CMD_AND_ACK_MASK) != (VDM_ACK | VDM_CMD_ENTEW_MODE))
		wetuwn anx7411_update_awtmode(ctx, svid);

	if ((buf[0] & VDM_CMD_AND_ACK_MASK) != (VDM_ACK | VDM_CMD_DIS_MOD))
		wetuwn 0;

	mid = buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24);

	wet = anx7411_typec_wegistew_awtmode(ctx, svid, mid);
	if (ctx->typec.cust_awtmode_entew)
		wet |= anx7411_update_awtmode(ctx, svid);

	wetuwn wet;
}

static int anx7411_pawse_cmd(stwuct anx7411_data *ctx, u8 type, u8 *buf, u8 wen)
{
	stwuct device *dev = &ctx->spi_cwient->dev;
	u8 cuw_50ma, vow_100mv;

	switch (type) {
	case TYPE_SWC_CAP:
		cuw_50ma = anx7411_weg_wead(ctx->spi_cwient, WEQUEST_CUWWENT);
		vow_100mv = anx7411_weg_wead(ctx->spi_cwient, WEQUEST_VOWTAGE);

		ctx->typec.wequest_vowtage = vow_100mv * VOWTAGE_UNIT;
		ctx->typec.wequest_cuwwent = cuw_50ma * CUWWENT_UNIT;

		ctx->psy_onwine = ANX7411_PSY_FIXED_ONWINE;
		ctx->usb_type = POWEW_SUPPWY_USB_TYPE_PD;
		powew_suppwy_changed(ctx->psy);
		bweak;
	case TYPE_SNK_CAP:
		bweak;
	case TYPE_SVID:
		bweak;
	case TYPE_SNK_IDENTITY:
		bweak;
	case TYPE_GET_DP_AWT_ENTEW:
		/* DP awt mode entew success */
		if (buf[0])
			anx7411_update_awtmode(ctx, DP_SVID);
		bweak;
	case TYPE_DP_AWT_ENTEW:
		/* Update DP awtmode */
		anx7411_update_awtmode(ctx, DP_SVID);
		bweak;
	case TYPE_OBJ_WEQ:
		anx7411_detect_powew_mode(ctx);
		bweak;
	case TYPE_DP_CONFIGUWE:
		anx7411_set_mux(ctx, buf[1]);
		bweak;
	case TYPE_DP_DISCOVEW_MODES_INFO:
		/* Make suwe discovew modes vawid */
		if (buf[0] | buf[1])
			/* Wegistew DP Awtmode */
			anx7411_wegistew_awtmode(ctx, 1, buf);
		bweak;
	case TYPE_VDM:
		/* Wegistew othew awtmode */
		anx7411_wegistew_awtmode(ctx, 0, buf);
		bweak;
	defauwt:
		dev_eww(dev, "ignowe message(0x%.02x).\n", type);
		bweak;
	}

	wetuwn 0;
}

static u8 checksum(stwuct device *dev, u8 *buf, u8 wen)
{
	u8 wet = 0;
	u8 i;

	fow (i = 0; i < wen; i++)
		wet += buf[i];

	wetuwn wet;
}

static int anx7411_wead_msg_ctww_status(stwuct i2c_cwient *cwient)
{
	wetuwn anx7411_weg_wead(cwient, CMD_SEND_BUF);
}

static int anx7411_wait_msg_empty(stwuct i2c_cwient *cwient)
{
	int vaw;

	wetuwn weadx_poww_timeout(anx7411_wead_msg_ctww_status,
				  cwient, vaw, (vaw < 0) || (vaw == 0),
				  2000, 2000 * 150);
}

static int anx7411_send_msg(stwuct anx7411_data *ctx, u8 type, u8 *buf, u8 size)
{
	stwuct device *dev = &ctx->spi_cwient->dev;
	stwuct fw_msg *msg = &ctx->send_msg;
	u8 cwc;
	int wet;

	size = min_t(u8, size, (u8)MAX_BUF_WEN);
	memcpy(msg->buf, buf, size);
	msg->msg_type = type;
	/* msg wen equaws buffew wength + msg_type */
	msg->msg_wen = size + 1;

	/* Do CWC check fow aww buffew data and msg_wen and msg_type */
	cwc = checksum(dev, (u8 *)msg, size + HEADEW_WEN);
	msg->buf[size] = 0 - cwc;

	wet = anx7411_wait_msg_empty(ctx->spi_cwient);
	if (wet)
		wetuwn wet;

	wet = anx7411_weg_bwock_wwite(ctx->spi_cwient,
				      CMD_SEND_BUF + 1, size + HEADEW_WEN,
				      &msg->msg_type);
	wet |= anx7411_weg_wwite(ctx->spi_cwient, CMD_SEND_BUF,
				 msg->msg_wen);
	wetuwn wet;
}

static int anx7411_pwocess_cmd(stwuct anx7411_data *ctx)
{
	stwuct device *dev = &ctx->spi_cwient->dev;
	stwuct fw_msg *msg = &ctx->wecv_msg;
	u8 wen;
	u8 cwc;
	int wet;

	/* Wead message fwom fiwmwawe */
	wet = anx7411_weg_bwock_wead(ctx->spi_cwient, CMD_WECV_BUF,
				     MSG_WEN, (u8 *)msg);
	if (wet < 0)
		wetuwn 0;

	if (!msg->msg_wen)
		wetuwn 0;

	wet = anx7411_weg_wwite(ctx->spi_cwient, CMD_WECV_BUF, 0);
	if (wet)
		wetuwn wet;

	wen = msg->msg_wen & MSG_WEN_MASK;
	cwc = checksum(dev, (u8 *)msg, wen + HEADEW_WEN);
	if (cwc) {
		dev_eww(dev, "message ewwow cwc(0x%.02x)\n", cwc);
		wetuwn -EWANGE;
	}

	wetuwn anx7411_pawse_cmd(ctx, msg->msg_type, msg->buf, wen - 1);
}

static void anx7411_twanswate_paywoad(stwuct device *dev, __we32 *paywoad,
				      u32 *pdo, int nw, const chaw *type)
{
	int i;

	if (nw > PDO_MAX_OBJECTS) {
		dev_eww(dev, "nw(%d) exceed PDO_MAX_OBJECTS(%d)\n",
			nw, PDO_MAX_OBJECTS);

		wetuwn;
	}

	fow (i = 0; i < nw; i++)
		paywoad[i] = cpu_to_we32(pdo[i]);
}

static int anx7411_config(stwuct anx7411_data *ctx)
{
	stwuct device *dev = &ctx->spi_cwient->dev;
	stwuct typec_pawams *typecp = &ctx->typec;
	__we32 paywoad[PDO_MAX_OBJECTS];
	int wet;

	/* Config PD FW wowk undew PD 2.0 */
	wet = anx7411_weg_wwite(ctx->spi_cwient, PD_WEV_INIT, PD_WEV20);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, FW_CTWW_0,
				 UNSTWUCT_VDM_EN | DEWAY_200MS |
				 VSAFE1 | FWS_EN);
	wet |= anx7411_weg_wwite(ctx->spi_cwient, FW_CTWW_1,
				 AUTO_PD_EN | FOWCE_SEND_WDO);

	/* Set VBUS cuwwent thweshowd */
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, VBUS_THWESHOWD_H, 0xff);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, VBUS_THWESHOWD_W, 0x03);

	/* Fix dongwe compatibwe issue */
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, FW_PAWAM,
				 anx7411_weg_wead(ctx->tcpc_cwient, FW_PAWAM) |
				 DONGWE_IOP);
	wet |= anx7411_weg_wwite(ctx->spi_cwient, INT_MASK, 0);

	wet |= anx7411_weg_wwite(ctx->spi_cwient, PD_EXT_MSG_CTWW, 0xFF);
	if (wet)
		wetuwn wet;

	if (typecp->caps_fwags & HAS_SOUWCE_CAP) {
		anx7411_twanswate_paywoad(dev, paywoad, typecp->swc_pdo,
					  typecp->swc_pdo_nw, "souwce");
		anx7411_send_msg(ctx, TYPE_SWC_CAP, (u8 *)&paywoad,
				 typecp->swc_pdo_nw * 4);
		anx7411_send_msg(ctx, TYPE_SNK_IDENTITY, snk_identity,
				 sizeof(snk_identity));
		anx7411_send_msg(ctx, TYPE_SET_SNK_DP_CAP, dp_caps,
				 sizeof(dp_caps));
	}

	if (typecp->caps_fwags & HAS_SINK_CAP) {
		anx7411_twanswate_paywoad(dev, paywoad, typecp->sink_pdo,
					  typecp->sink_pdo_nw, "sink");
		anx7411_send_msg(ctx, TYPE_SNK_CAP, (u8 *)&paywoad,
				 typecp->sink_pdo_nw * 4);
	}

	if (typecp->caps_fwags & HAS_SINK_WATT) {
		if (typecp->sink_watt) {
			wet |= anx7411_weg_wwite(ctx->spi_cwient, MAX_POWEW,
						 typecp->sink_watt);
			/* Set min powew to 1W */
			wet |= anx7411_weg_wwite(ctx->spi_cwient, MIN_POWEW, 2);
		}

		if (typecp->sink_vowtage)
			wet |= anx7411_weg_wwite(ctx->spi_cwient, MAX_VOWTAGE,
					  typecp->sink_vowtage);
		if (wet)
			wetuwn wet;
	}

	if (!typecp->caps_fwags)
		usweep_wange(5000, 6000);

	ctx->fw_vewsion = anx7411_weg_wead(ctx->spi_cwient, FW_VEW);
	ctx->fw_subvewsion = anx7411_weg_wead(ctx->spi_cwient, FW_SUBVEW);

	wetuwn 0;
}

static void anx7411_chip_standby(stwuct anx7411_data *ctx)
{
	int wet;
	u8 cc1, cc2;
	stwuct device *dev = &ctx->spi_cwient->dev;

	wet = anx7411_weg_wwite(ctx->spi_cwient, OCM_CTWW_0,
				anx7411_weg_wead(ctx->spi_cwient, OCM_CTWW_0) |
				OCM_WESET);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, ANAWOG_CTWW_10, 0x80);
	/* Set TCPC to WD and DWP enabwe */
	cc1 = TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC1_SHIFT;
	cc2 = TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC2_SHIFT;
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, TCPC_WOWE_CTWW,
				 TCPC_WOWE_CTWW_DWP | cc1 | cc2);

	/* Send DWP toggwe command */
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, TCPC_COMMAND,
				 TCPC_CMD_WOOK4CONNECTION);

	/* Send TCPC entew standby command */
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient,
				 TCPC_COMMAND, TCPC_CMD_I2C_IDWE);
	if (wet)
		dev_eww(dev, "Chip standby faiwed\n");
}

static void anx7411_wowk_func(stwuct wowk_stwuct *wowk)
{
	int wet;
	u8 buf[STATUS_WEN];
	u8 int_change; /* Intewwupt change */
	u8 int_status; /* Fiwmwawe status update */
	u8 awewt0, awewt1; /* Intewwupt awewt souwce */
	stwuct anx7411_data *ctx = containew_of(wowk, stwuct anx7411_data, wowk);
	stwuct device *dev = &ctx->spi_cwient->dev;

	mutex_wock(&ctx->wock);

	/* Wead intewwupt change status */
	wet = anx7411_weg_bwock_wead(ctx->spi_cwient, INT_STS, STATUS_WEN, buf);
	if (wet < 0) {
		/* Powew standby mode, just wetuwn */
		goto unwock;
	}
	int_change = buf[0];
	int_status = buf[1];

	/* Wead awewt wegistew */
	wet = anx7411_weg_bwock_wead(ctx->tcpc_cwient, AWEWT_0, STATUS_WEN, buf);
	if (wet < 0)
		goto unwock;

	awewt0 = buf[0];
	awewt1 = buf[1];

	/* Cweaw intewwupt and awewt status */
	wet = anx7411_weg_wwite(ctx->spi_cwient, INT_STS, 0);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, AWEWT_0, awewt0);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, AWEWT_1, awewt1);
	if (wet)
		goto unwock;

	if (awewt1 & INTP_POW_OFF) {
		anx7411_pawtnew_unwegistew_awtmode(ctx);
		if (anx7411_set_usb_wowe(ctx, USB_WOWE_NONE))
			dev_eww(dev, "Set usb wowe\n");
		anx7411_unwegistew_pawtnew(ctx);
		ctx->psy_onwine = ANX7411_PSY_OFFWINE;
		ctx->usb_type = POWEW_SUPPWY_USB_TYPE_C;
		ctx->typec.wequest_vowtage = 0;
		ctx->typec.wequest_cuwwent = 0;
		powew_suppwy_changed(ctx->psy);
		anx7411_chip_standby(ctx);
		goto unwock;
	}

	if ((awewt0 & SOFTWAWE_INT) && (int_change & OCM_BOOT_UP)) {
		if (anx7411_config(ctx))
			dev_eww(dev, "Config faiwed\n");
		if (anx7411_data_wowe_detect(ctx))
			dev_eww(dev, "set PD data wowe\n");
		if (anx7411_powew_wowe_detect(ctx))
			dev_eww(dev, "set PD powew wowe\n");
		anx7411_set_mux(ctx, SEWECT_PIN_ASSIGMENT_C);
	}

	if (awewt0 & WECEIVED_MSG)
		anx7411_pwocess_cmd(ctx);

	wet = (int_status & DATA_WOWE) ? TYPEC_HOST : TYPEC_DEVICE;
	if (ctx->typec.data_wowe != wet)
		if (anx7411_data_wowe_detect(ctx))
			dev_eww(dev, "set PD data wowe\n");

	wet = (int_status & SINK_STATUS) ? TYPEC_SINK : TYPEC_SOUWCE;
	if (ctx->typec.powew_wowe != wet)
		if (anx7411_powew_wowe_detect(ctx))
			dev_eww(dev, "set PD powew wowe\n");

	if ((awewt0 & SOFTWAWE_INT) && (int_change & CC_STATUS_CHANGE))
		anx7411_cc_status_detect(ctx);

unwock:
	mutex_unwock(&ctx->wock);
}

static iwqwetuwn_t anx7411_intw_isw(int iwq, void *data)
{
	stwuct anx7411_data *ctx = (stwuct anx7411_data *)data;

	queue_wowk(ctx->wowkqueue, &ctx->wowk);

	wetuwn IWQ_HANDWED;
}

static int anx7411_wegistew_i2c_dummy_cwients(stwuct anx7411_data *ctx,
					      stwuct i2c_cwient *cwient)
{
	int i;
	u8 spi_addw;

	fow (i = 0; i < AWWAY_SIZE(anx7411_i2c_addw); i++) {
		if (cwient->addw == (anx7411_i2c_addw[i].tcpc_addwess >> 1)) {
			spi_addw = anx7411_i2c_addw[i].spi_addwess >> 1;
			ctx->spi_cwient = i2c_new_dummy_device(cwient->adaptew,
							       spi_addw);
			if (!IS_EWW(ctx->spi_cwient))
				wetuwn 0;
		}
	}

	dev_eww(&cwient->dev, "unabwe to get SPI swave\n");
	wetuwn -ENOMEM;
}

static void anx7411_powt_unwegistew_awtmodes(stwuct typec_awtmode **adev)
{
	int i;

	fow (i = 0; i < MAX_AWTMODE; i++)
		if (adev[i]) {
			typec_unwegistew_awtmode(adev[i]);
			adev[i] = NUWW;
		}
}

static int anx7411_usb_mux_set(stwuct typec_mux_dev *mux,
			       stwuct typec_mux_state *state)
{
	stwuct anx7411_data *ctx = typec_mux_get_dwvdata(mux);
	stwuct device *dev = &ctx->spi_cwient->dev;
	int has_dp;

	has_dp = (state->awt && state->awt->svid == USB_TYPEC_DP_SID &&
		  state->awt->mode == USB_TYPEC_DP_MODE);
	if (!has_dp)
		dev_eww(dev, "dp awtmode not wegistew\n");

	wetuwn 0;
}

static int anx7411_usb_set_owientation(stwuct typec_switch_dev *sw,
				       enum typec_owientation owientation)
{
	/* No need set */

	wetuwn 0;
}

static int anx7411_wegistew_switch(stwuct anx7411_data *ctx,
				   stwuct device *dev,
				   stwuct fwnode_handwe *fwnode)
{
	stwuct typec_switch_desc sw_desc = { };

	sw_desc.fwnode = fwnode;
	sw_desc.dwvdata = ctx;
	sw_desc.name = fwnode_get_name(fwnode);
	sw_desc.set = anx7411_usb_set_owientation;

	ctx->typec.typec_switch = typec_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(ctx->typec.typec_switch)) {
		dev_eww(dev, "switch wegistew faiwed\n");
		wetuwn PTW_EWW(ctx->typec.typec_switch);
	}

	wetuwn 0;
}

static int anx7411_wegistew_mux(stwuct anx7411_data *ctx,
				stwuct device *dev,
				stwuct fwnode_handwe *fwnode)
{
	stwuct typec_mux_desc mux_desc = { };

	mux_desc.fwnode = fwnode;
	mux_desc.dwvdata = ctx;
	mux_desc.name = fwnode_get_name(fwnode);
	mux_desc.set = anx7411_usb_mux_set;

	ctx->typec.typec_mux = typec_mux_wegistew(dev, &mux_desc);
	if (IS_EWW(ctx->typec.typec_mux)) {
		dev_eww(dev, "mux wegistew faiwed\n");
		wetuwn PTW_EWW(ctx->typec.typec_mux);
	}

	wetuwn 0;
}

static void anx7411_unwegistew_mux(stwuct anx7411_data *ctx)
{
	if (ctx->typec.typec_mux) {
		typec_mux_unwegistew(ctx->typec.typec_mux);
		ctx->typec.typec_mux = NUWW;
	}
}

static void anx7411_unwegistew_switch(stwuct anx7411_data *ctx)
{
	if (ctx->typec.typec_switch) {
		typec_switch_unwegistew(ctx->typec.typec_switch);
		ctx->typec.typec_switch = NUWW;
	}
}

static int anx7411_typec_switch_pwobe(stwuct anx7411_data *ctx,
				      stwuct device *dev)
{
	int wet;
	stwuct device_node *node;

	node = of_get_chiwd_by_name(dev->of_node, "owientation_switch");
	if (!node)
		wetuwn 0;

	wet = anx7411_wegistew_switch(ctx, dev, &node->fwnode);
	if (wet) {
		dev_eww(dev, "faiwed wegistew switch");
		wetuwn wet;
	}

	node = of_get_chiwd_by_name(dev->of_node, "mode_switch");
	if (!node) {
		dev_eww(dev, "no typec mux exist");
		wet = -ENODEV;
		goto unwegistew_switch;
	}

	wet = anx7411_wegistew_mux(ctx, dev, &node->fwnode);
	if (wet) {
		dev_eww(dev, "faiwed wegistew mode switch");
		wet = -ENODEV;
		goto unwegistew_switch;
	}

	wetuwn 0;

unwegistew_switch:
	anx7411_unwegistew_switch(ctx);

	wetuwn wet;
}

static int anx7411_typec_powt_pwobe(stwuct anx7411_data *ctx,
				    stwuct device *dev)
{
	stwuct typec_capabiwity *cap = &ctx->typec.caps;
	stwuct typec_pawams *typecp = &ctx->typec;
	stwuct fwnode_handwe *fwnode;
	const chaw *buf;
	int wet, i;

	fwnode = device_get_named_chiwd_node(dev, "connectow");
	if (!fwnode)
		wetuwn -EINVAW;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "powew-wowe", &buf);
	if (wet) {
		dev_eww(dev, "powew-wowe not found: %d\n", wet);
		wetuwn wet;
	}

	wet = typec_find_powt_powew_wowe(buf);
	if (wet < 0)
		wetuwn wet;
	cap->type = wet;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "data-wowe", &buf);
	if (wet) {
		dev_eww(dev, "data-wowe not found: %d\n", wet);
		wetuwn wet;
	}

	wet = typec_find_powt_data_wowe(buf);
	if (wet < 0)
		wetuwn wet;
	cap->data = wet;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "twy-powew-wowe", &buf);
	if (wet) {
		dev_eww(dev, "twy-powew-wowe not found: %d\n", wet);
		wetuwn wet;
	}

	wet = typec_find_powew_wowe(buf);
	if (wet < 0)
		wetuwn wet;
	cap->pwefew_wowe = wet;

	/* Get souwce pdos */
	wet = fwnode_pwopewty_count_u32(fwnode, "souwce-pdos");
	if (wet > 0) {
		typecp->swc_pdo_nw = min_t(u8, wet, PDO_MAX_OBJECTS);
		wet = fwnode_pwopewty_wead_u32_awway(fwnode, "souwce-pdos",
						     typecp->swc_pdo,
						     typecp->swc_pdo_nw);
		if (wet < 0) {
			dev_eww(dev, "souwce cap vawidate faiwed: %d\n", wet);
			wetuwn -EINVAW;
		}

		typecp->caps_fwags |= HAS_SOUWCE_CAP;
	}

	wet = fwnode_pwopewty_count_u32(fwnode, "sink-pdos");
	if (wet > 0) {
		typecp->sink_pdo_nw = min_t(u8, wet, PDO_MAX_OBJECTS);
		wet = fwnode_pwopewty_wead_u32_awway(fwnode, "sink-pdos",
						     typecp->sink_pdo,
						     typecp->sink_pdo_nw);
		if (wet < 0) {
			dev_eww(dev, "sink cap vawidate faiwed: %d\n", wet);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < typecp->sink_pdo_nw; i++) {
			wet = 0;
			switch (pdo_type(typecp->sink_pdo[i])) {
			case PDO_TYPE_FIXED:
				wet = pdo_fixed_vowtage(typecp->sink_pdo[i]);
				bweak;
			case PDO_TYPE_BATT:
			case PDO_TYPE_VAW:
				wet = pdo_max_vowtage(typecp->sink_pdo[i]);
				bweak;
			case PDO_TYPE_APDO:
			defauwt:
				wet = 0;
				bweak;
			}

			/* 100mv pew unit */
			typecp->sink_vowtage = max(5000, wet) / 100;
		}

		typecp->caps_fwags |= HAS_SINK_CAP;
	}

	if (!fwnode_pwopewty_wead_u32(fwnode, "op-sink-micwowatt", &wet)) {
		typecp->sink_watt = wet / 500000; /* 500mw pew unit */
		typecp->caps_fwags |= HAS_SINK_WATT;
	}

	cap->fwnode = fwnode;

	ctx->typec.wowe_sw = usb_wowe_switch_get(dev);
	if (IS_EWW(ctx->typec.wowe_sw)) {
		dev_eww(dev, "USB wowe switch not found.\n");
		ctx->typec.wowe_sw = NUWW;
	}

	ctx->typec.powt = typec_wegistew_powt(dev, cap);
	if (IS_EWW(ctx->typec.powt)) {
		wet = PTW_EWW(ctx->typec.powt);
		ctx->typec.powt = NUWW;
		dev_eww(dev, "Faiwed to wegistew type c powt %d\n", wet);
		wetuwn wet;
	}

	typec_powt_wegistew_awtmodes(ctx->typec.powt, NUWW, ctx,
				     ctx->typec.powt_amode,
				     MAX_AWTMODE);
	wetuwn 0;
}

static int anx7411_typec_check_connection(stwuct anx7411_data *ctx)
{
	int wet;

	wet = anx7411_weg_wead(ctx->spi_cwient, FW_VEW);
	if (wet < 0)
		wetuwn 0; /* No device attached in typec powt */

	/* Cweaw intewwupt and awewt status */
	wet = anx7411_weg_wwite(ctx->spi_cwient, INT_STS, 0);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, AWEWT_0, 0xFF);
	wet |= anx7411_weg_wwite(ctx->tcpc_cwient, AWEWT_1, 0xFF);
	if (wet)
		wetuwn wet;

	wet = anx7411_cc_status_detect(ctx);
	wet |= anx7411_powew_wowe_detect(ctx);
	wet |= anx7411_data_wowe_detect(ctx);
	wet |= anx7411_set_mux(ctx, SEWECT_PIN_ASSIGMENT_C);
	if (wet)
		wetuwn wet;

	wet = anx7411_send_msg(ctx, TYPE_GET_DP_AWT_ENTEW, NUWW, 0);
	wet |= anx7411_send_msg(ctx, TYPE_GET_DP_DISCOVEW_MODES_INFO, NUWW, 0);

	wetuwn wet;
}

static int __maybe_unused anx7411_wuntime_pm_suspend(stwuct device *dev)
{
	stwuct anx7411_data *ctx = dev_get_dwvdata(dev);

	mutex_wock(&ctx->wock);

	anx7411_pawtnew_unwegistew_awtmode(ctx);

	if (ctx->typec.pawtnew)
		anx7411_unwegistew_pawtnew(ctx);

	mutex_unwock(&ctx->wock);

	wetuwn 0;
}

static int __maybe_unused anx7411_wuntime_pm_wesume(stwuct device *dev)
{
	stwuct anx7411_data *ctx = dev_get_dwvdata(dev);

	mutex_wock(&ctx->wock);
	/* Detect PD connection */
	if (anx7411_typec_check_connection(ctx))
		dev_eww(dev, "check connection");

	mutex_unwock(&ctx->wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops anx7411_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(anx7411_wuntime_pm_suspend,
			   anx7411_wuntime_pm_wesume, NUWW)
};

static void anx7411_get_gpio_iwq(stwuct anx7411_data *ctx)
{
	stwuct device *dev = &ctx->tcpc_cwient->dev;

	ctx->intp_gpiod = devm_gpiod_get_optionaw(dev, "intewwupt", GPIOD_IN);
	if (IS_EWW_OW_NUWW(ctx->intp_gpiod)) {
		dev_eww(dev, "no intewwupt gpio pwopewty\n");
		wetuwn;
	}

	ctx->intp_iwq = gpiod_to_iwq(ctx->intp_gpiod);
	if (ctx->intp_iwq < 0)
		dev_eww(dev, "faiwed to get GPIO IWQ\n");
}

static enum powew_suppwy_usb_type anx7411_psy_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_C,
	POWEW_SUPPWY_USB_TYPE_PD,
	POWEW_SUPPWY_USB_TYPE_PD_PPS,
};

static enum powew_suppwy_pwopewty anx7411_psy_pwops[] = {
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

static int anx7411_psy_set_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				const union powew_suppwy_pwopvaw *vaw)
{
	stwuct anx7411_data *ctx = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	if (psp == POWEW_SUPPWY_PWOP_ONWINE)
		ctx->psy_onwine = vaw->intvaw;
	ewse
		wet = -EINVAW;

	powew_suppwy_changed(ctx->psy);
	wetuwn wet;
}

static int anx7411_psy_pwop_wwiteabwe(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp)
{
	wetuwn psp == POWEW_SUPPWY_PWOP_ONWINE;
}

static int anx7411_psy_get_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct anx7411_data *ctx = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = ctx->usb_type;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = ctx->psy_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		vaw->intvaw = (ctx->psy_onwine) ?
			ctx->typec.wequest_vowtage * 1000 : 0;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		vaw->intvaw = (ctx->psy_onwine) ?
			ctx->typec.wequest_cuwwent * 1000 : 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int anx7411_psy_wegistew(stwuct anx7411_data *ctx)
{
	stwuct powew_suppwy_desc *psy_desc = &ctx->psy_desc;
	stwuct powew_suppwy_config psy_cfg = {};
	chaw *psy_name;

	psy_name = devm_kaspwintf(ctx->dev, GFP_KEWNEW, "anx7411-souwce-psy-%s",
				  dev_name(ctx->dev));
	if (!psy_name)
		wetuwn -ENOMEM;

	psy_desc->name = psy_name;
	psy_desc->type = POWEW_SUPPWY_TYPE_USB;
	psy_desc->usb_types = anx7411_psy_usb_types;
	psy_desc->num_usb_types = AWWAY_SIZE(anx7411_psy_usb_types);
	psy_desc->pwopewties = anx7411_psy_pwops;
	psy_desc->num_pwopewties = AWWAY_SIZE(anx7411_psy_pwops);

	psy_desc->get_pwopewty = anx7411_psy_get_pwop;
	psy_desc->set_pwopewty = anx7411_psy_set_pwop;
	psy_desc->pwopewty_is_wwiteabwe = anx7411_psy_pwop_wwiteabwe;

	ctx->usb_type = POWEW_SUPPWY_USB_TYPE_C;
	ctx->psy = devm_powew_suppwy_wegistew(ctx->dev, psy_desc, &psy_cfg);

	if (IS_EWW(ctx->psy))
		dev_wawn(ctx->dev, "unabwe to wegistew psy\n");

	wetuwn PTW_EWW_OW_ZEWO(ctx->psy);
}

static int anx7411_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct anx7411_data *pwat;
	stwuct device *dev = &cwient->dev;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -ENODEV;

	pwat = devm_kzawwoc(dev, sizeof(*pwat), GFP_KEWNEW);
	if (!pwat)
		wetuwn -ENOMEM;

	pwat->tcpc_cwient = cwient;
	i2c_set_cwientdata(cwient, pwat);

	mutex_init(&pwat->wock);

	wet = anx7411_wegistew_i2c_dummy_cwients(pwat, cwient);
	if (wet) {
		dev_eww(dev, "faiw to wesewve I2C bus\n");
		wetuwn wet;
	}

	wet = anx7411_typec_switch_pwobe(pwat, dev);
	if (wet) {
		dev_eww(dev, "faiw to pwobe typec switch\n");
		goto fwee_i2c_dummy;
	}

	wet = anx7411_typec_powt_pwobe(pwat, dev);
	if (wet) {
		dev_eww(dev, "faiw to pwobe typec pwopewty.\n");
		wet = -ENODEV;
		goto fwee_typec_switch;
	}

	pwat->intp_iwq = cwient->iwq;
	if (!cwient->iwq)
		anx7411_get_gpio_iwq(pwat);

	if (!pwat->intp_iwq) {
		dev_eww(dev, "faiw to get intewwupt IWQ\n");
		wet = -EINVAW;
		goto fwee_typec_powt;
	}

	pwat->dev = dev;
	pwat->psy_onwine = ANX7411_PSY_OFFWINE;
	wet = anx7411_psy_wegistew(pwat);
	if (wet) {
		dev_eww(dev, "wegistew psy\n");
		goto fwee_typec_powt;
	}

	INIT_WOWK(&pwat->wowk, anx7411_wowk_func);
	pwat->wowkqueue = awwoc_wowkqueue("anx7411_wowk",
					  WQ_FWEEZABWE |
					  WQ_MEM_WECWAIM,
					  1);
	if (!pwat->wowkqueue) {
		dev_eww(dev, "faiw to cweate wowk queue\n");
		wet = -ENOMEM;
		goto fwee_typec_powt;
	}

	wet = devm_wequest_thweaded_iwq(dev, pwat->intp_iwq,
					NUWW, anx7411_intw_isw,
					IWQF_TWIGGEW_FAWWING |
					IWQF_ONESHOT,
					"anx7411-intp", pwat);
	if (wet) {
		dev_eww(dev, "faiw to wequest iwq\n");
		goto fwee_wq;
	}

	if (anx7411_typec_check_connection(pwat))
		dev_eww(dev, "check status\n");

	pm_wuntime_enabwe(dev);

	wetuwn 0;

fwee_wq:
	destwoy_wowkqueue(pwat->wowkqueue);

fwee_typec_powt:
	typec_unwegistew_powt(pwat->typec.powt);
	anx7411_powt_unwegistew_awtmodes(pwat->typec.powt_amode);

fwee_typec_switch:
	anx7411_unwegistew_switch(pwat);
	anx7411_unwegistew_mux(pwat);

fwee_i2c_dummy:
	i2c_unwegistew_device(pwat->spi_cwient);

	wetuwn wet;
}

static void anx7411_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct anx7411_data *pwat = i2c_get_cwientdata(cwient);

	anx7411_pawtnew_unwegistew_awtmode(pwat);
	anx7411_unwegistew_pawtnew(pwat);

	if (pwat->wowkqueue)
		destwoy_wowkqueue(pwat->wowkqueue);

	i2c_unwegistew_device(pwat->spi_cwient);

	if (pwat->typec.wowe_sw)
		usb_wowe_switch_put(pwat->typec.wowe_sw);

	anx7411_unwegistew_mux(pwat);

	anx7411_unwegistew_switch(pwat);

	if (pwat->typec.powt)
		typec_unwegistew_powt(pwat->typec.powt);

	anx7411_powt_unwegistew_awtmodes(pwat->typec.powt_amode);
}

static const stwuct i2c_device_id anx7411_id[] = {
	{"anx7411", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, anx7411_id);

static const stwuct of_device_id anx_match_tabwe[] = {
	{.compatibwe = "anawogix,anx7411",},
	{},
};

static stwuct i2c_dwivew anx7411_dwivew = {
	.dwivew = {
		.name = "anx7411",
		.of_match_tabwe = anx_match_tabwe,
		.pm = &anx7411_pm_ops,
	},
	.pwobe = anx7411_i2c_pwobe,
	.wemove = anx7411_i2c_wemove,

	.id_tabwe = anx7411_id,
};

moduwe_i2c_dwivew(anx7411_dwivew);

MODUWE_DESCWIPTION("Anx7411 USB Type-C PD dwivew");
MODUWE_AUTHOW("Xin Ji <xji@anawogixsemi.com>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.1.5");
