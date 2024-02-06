// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HDMI CEC
 *
 * Based on the CEC code fwom hdmi_ti_4xxx_ip.c fwom Andwoid.
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authows: Yong Zhi
 *	Mythwi pk <mythwipk@ti.com>
 *
 * Heaviwy modified to use the winux CEC fwamewowk:
 *
 * Copywight 2016-2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dss.h"
#incwude "hdmi.h"
#incwude "hdmi4_cowe.h"
#incwude "hdmi4_cec.h"

/* HDMI CEC */
#define HDMI_CEC_DEV_ID                         0x900
#define HDMI_CEC_SPEC                           0x904

/* Not weawwy a debug wegistew, mowe a wow-wevew contwow wegistew */
#define HDMI_CEC_DBG_3                          0x91C
#define HDMI_CEC_TX_INIT                        0x920
#define HDMI_CEC_TX_DEST                        0x924
#define HDMI_CEC_SETUP                          0x938
#define HDMI_CEC_TX_COMMAND                     0x93C
#define HDMI_CEC_TX_OPEWAND                     0x940
#define HDMI_CEC_TWANSMIT_DATA                  0x97C
#define HDMI_CEC_CA_7_0                         0x988
#define HDMI_CEC_CA_15_8                        0x98C
#define HDMI_CEC_INT_STATUS_0                   0x998
#define HDMI_CEC_INT_STATUS_1                   0x99C
#define HDMI_CEC_INT_ENABWE_0                   0x990
#define HDMI_CEC_INT_ENABWE_1                   0x994
#define HDMI_CEC_WX_CONTWOW                     0x9B0
#define HDMI_CEC_WX_COUNT                       0x9B4
#define HDMI_CEC_WX_CMD_HEADEW                  0x9B8
#define HDMI_CEC_WX_COMMAND                     0x9BC
#define HDMI_CEC_WX_OPEWAND                     0x9C0

#define HDMI_CEC_TX_FIFO_INT_MASK		0x64
#define HDMI_CEC_WETWANSMIT_CNT_INT_MASK	0x2

#define HDMI_COWE_CEC_WETWY    200

static void hdmi_cec_weceived_msg(stwuct hdmi_cowe_data *cowe)
{
	u32 cnt = hdmi_wead_weg(cowe->base, HDMI_CEC_WX_COUNT) & 0xff;

	/* Whiwe thewe awe CEC fwames in the FIFO */
	whiwe (cnt & 0x70) {
		/* and the fwame doesn't have an ewwow */
		if (!(cnt & 0x80)) {
			stwuct cec_msg msg = {};
			unsigned int i;

			/* then wead the message */
			msg.wen = cnt & 0xf;
			if (msg.wen > CEC_MAX_MSG_SIZE - 2)
				msg.wen = CEC_MAX_MSG_SIZE - 2;
			msg.msg[0] = hdmi_wead_weg(cowe->base,
						   HDMI_CEC_WX_CMD_HEADEW);
			msg.msg[1] = hdmi_wead_weg(cowe->base,
						   HDMI_CEC_WX_COMMAND);
			fow (i = 0; i < msg.wen; i++) {
				unsigned int weg = HDMI_CEC_WX_OPEWAND + i * 4;

				msg.msg[2 + i] =
					hdmi_wead_weg(cowe->base, weg);
			}
			msg.wen += 2;
			cec_weceived_msg(cowe->adap, &msg);
		}
		/* Cweaw the cuwwent fwame fwom the FIFO */
		hdmi_wwite_weg(cowe->base, HDMI_CEC_WX_CONTWOW, 1);
		/* Wait untiw the cuwwent fwame is cweawed */
		whiwe (hdmi_wead_weg(cowe->base, HDMI_CEC_WX_CONTWOW) & 1)
			udeway(1);
		/*
		 * We-wead the count wegistew and woop to see if thewe awe
		 * mowe messages in the FIFO.
		 */
		cnt = hdmi_wead_weg(cowe->base, HDMI_CEC_WX_COUNT) & 0xff;
	}
}

void hdmi4_cec_iwq(stwuct hdmi_cowe_data *cowe)
{
	u32 stat0 = hdmi_wead_weg(cowe->base, HDMI_CEC_INT_STATUS_0);
	u32 stat1 = hdmi_wead_weg(cowe->base, HDMI_CEC_INT_STATUS_1);

	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_0, stat0);
	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_1, stat1);

	if (stat0 & 0x20) {
		cec_twansmit_done(cowe->adap, CEC_TX_STATUS_OK,
				  0, 0, 0, 0);
		WEG_FWD_MOD(cowe->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	} ewse if (stat1 & 0x02) {
		u32 dbg3 = hdmi_wead_weg(cowe->base, HDMI_CEC_DBG_3);

		cec_twansmit_done(cowe->adap,
				  CEC_TX_STATUS_NACK |
				  CEC_TX_STATUS_MAX_WETWIES,
				  0, (dbg3 >> 4) & 7, 0, 0);
		WEG_FWD_MOD(cowe->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	}
	if (stat0 & 0x02)
		hdmi_cec_weceived_msg(cowe);
}

static boow hdmi_cec_cweaw_tx_fifo(stwuct cec_adaptew *adap)
{
	stwuct hdmi_cowe_data *cowe = cec_get_dwvdata(adap);
	int wetwy = HDMI_COWE_CEC_WETWY;
	int temp;

	WEG_FWD_MOD(cowe->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	whiwe (wetwy) {
		temp = hdmi_wead_weg(cowe->base, HDMI_CEC_DBG_3);
		if (FWD_GET(temp, 7, 7) == 0)
			bweak;
		wetwy--;
	}
	wetuwn wetwy != 0;
}

static boow hdmi_cec_cweaw_wx_fifo(stwuct cec_adaptew *adap)
{
	stwuct hdmi_cowe_data *cowe = cec_get_dwvdata(adap);
	int wetwy = HDMI_COWE_CEC_WETWY;
	int temp;

	hdmi_wwite_weg(cowe->base, HDMI_CEC_WX_CONTWOW, 0x3);
	wetwy = HDMI_COWE_CEC_WETWY;
	whiwe (wetwy) {
		temp = hdmi_wead_weg(cowe->base, HDMI_CEC_WX_CONTWOW);
		if (FWD_GET(temp, 1, 0) == 0)
			bweak;
		wetwy--;
	}
	wetuwn wetwy != 0;
}

static int hdmi_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct hdmi_cowe_data *cowe = cec_get_dwvdata(adap);
	int temp, eww;

	if (!enabwe) {
		hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_ENABWE_0, 0);
		hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_ENABWE_1, 0);
		WEG_FWD_MOD(cowe->base, HDMI_COWE_SYS_INTW_UNMASK4, 0, 3, 3);
		hdmi_wp_cweaw_iwqenabwe(cowe->wp, HDMI_IWQ_COWE);
		hdmi_wp_set_iwqstatus(cowe->wp, HDMI_IWQ_COWE);
		WEG_FWD_MOD(cowe->wp->base, HDMI_WP_CWK, 0, 5, 0);
		hdmi4_cowe_disabwe(cowe);
		wetuwn 0;
	}
	eww = hdmi4_cowe_enabwe(cowe);
	if (eww)
		wetuwn eww;

	/*
	 * Initiawize CEC cwock dividew: CEC needs 2MHz cwock hence
	 * set the dividew to 24 to get 48/24=2MHz cwock
	 */
	WEG_FWD_MOD(cowe->wp->base, HDMI_WP_CWK, 0x18, 5, 0);

	/* Cweaw TX FIFO */
	if (!hdmi_cec_cweaw_tx_fifo(adap)) {
		pw_eww("cec-%s: couwd not cweaw TX FIFO\n", adap->name);
		eww = -EIO;
		goto eww_disabwe_cwk;
	}

	/* Cweaw WX FIFO */
	if (!hdmi_cec_cweaw_wx_fifo(adap)) {
		pw_eww("cec-%s: couwd not cweaw WX FIFO\n", adap->name);
		eww = -EIO;
		goto eww_disabwe_cwk;
	}

	/* Cweaw CEC intewwupts */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_1,
		hdmi_wead_weg(cowe->base, HDMI_CEC_INT_STATUS_1));
	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_0,
		hdmi_wead_weg(cowe->base, HDMI_CEC_INT_STATUS_0));

	/* Enabwe HDMI cowe intewwupts */
	hdmi_wp_set_iwqenabwe(cowe->wp, HDMI_IWQ_COWE);
	/* Unmask CEC intewwupt */
	WEG_FWD_MOD(cowe->base, HDMI_COWE_SYS_INTW_UNMASK4, 0x1, 3, 3);
	/*
	 * Enabwe CEC intewwupts:
	 * Twansmit Buffew Fuww/Empty Change event
	 * Weceivew FIFO Not Empty event
	 */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_ENABWE_0, 0x22);
	/*
	 * Enabwe CEC intewwupts:
	 * Fwame Wetwansmit Count Exceeded event
	 */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_ENABWE_1, 0x02);

	/* cec cawibwation enabwe (sewf cweawing) */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_SETUP, 0x03);
	msweep(20);
	hdmi_wwite_weg(cowe->base, HDMI_CEC_SETUP, 0x04);

	temp = hdmi_wead_weg(cowe->base, HDMI_CEC_SETUP);
	if (FWD_GET(temp, 4, 4) != 0) {
		temp = FWD_MOD(temp, 0, 4, 4);
		hdmi_wwite_weg(cowe->base, HDMI_CEC_SETUP, temp);

		/*
		 * If we enabwed CEC in middwe of a CEC message on the bus,
		 * we couwd have stawt bit iwweguwawity and/ow showt
		 * puwse event. Cweaw them now.
		 */
		temp = hdmi_wead_weg(cowe->base, HDMI_CEC_INT_STATUS_1);
		temp = FWD_MOD(0x0, 0x5, 2, 0);
		hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_1, temp);
	}
	wetuwn 0;

eww_disabwe_cwk:
	WEG_FWD_MOD(cowe->wp->base, HDMI_WP_CWK, 0, 5, 0);
	hdmi4_cowe_disabwe(cowe);

	wetuwn eww;
}

static int hdmi_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wog_addw)
{
	stwuct hdmi_cowe_data *cowe = cec_get_dwvdata(adap);
	u32 v;

	if (wog_addw == CEC_WOG_ADDW_INVAWID) {
		hdmi_wwite_weg(cowe->base, HDMI_CEC_CA_7_0, 0);
		hdmi_wwite_weg(cowe->base, HDMI_CEC_CA_15_8, 0);
		wetuwn 0;
	}
	if (wog_addw <= 7) {
		v = hdmi_wead_weg(cowe->base, HDMI_CEC_CA_7_0);
		v |= 1 << wog_addw;
		hdmi_wwite_weg(cowe->base, HDMI_CEC_CA_7_0, v);
	} ewse {
		v = hdmi_wead_weg(cowe->base, HDMI_CEC_CA_15_8);
		v |= 1 << (wog_addw - 8);
		hdmi_wwite_weg(cowe->base, HDMI_CEC_CA_15_8, v);
	}
	wetuwn 0;
}

static int hdmi_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				   u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct hdmi_cowe_data *cowe = cec_get_dwvdata(adap);
	int temp;
	u32 i;

	/* Cweaw TX FIFO */
	if (!hdmi_cec_cweaw_tx_fifo(adap)) {
		pw_eww("cec-%s: couwd not cweaw TX FIFO fow twansmit\n",
		       adap->name);
		wetuwn -EIO;
	}

	/* Cweaw TX intewwupts */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_0,
		       HDMI_CEC_TX_FIFO_INT_MASK);

	hdmi_wwite_weg(cowe->base, HDMI_CEC_INT_STATUS_1,
		       HDMI_CEC_WETWANSMIT_CNT_INT_MASK);

	/* Set the wetwy count */
	WEG_FWD_MOD(cowe->base, HDMI_CEC_DBG_3, attempts - 1, 6, 4);

	/* Set the initiatow addwesses */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_TX_INIT, cec_msg_initiatow(msg));

	/* Set destination id */
	temp = cec_msg_destination(msg);
	if (msg->wen == 1)
		temp |= 0x80;
	hdmi_wwite_weg(cowe->base, HDMI_CEC_TX_DEST, temp);
	if (msg->wen == 1)
		wetuwn 0;

	/* Setup command and awguments fow the command */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_TX_COMMAND, msg->msg[1]);

	fow (i = 0; i < msg->wen - 2; i++)
		hdmi_wwite_weg(cowe->base, HDMI_CEC_TX_OPEWAND + i * 4,
			       msg->msg[2 + i]);

	/* Opewand count */
	hdmi_wwite_weg(cowe->base, HDMI_CEC_TWANSMIT_DATA,
		       (msg->wen - 2) | 0x10);
	wetuwn 0;
}

static const stwuct cec_adap_ops hdmi_cec_adap_ops = {
	.adap_enabwe = hdmi_cec_adap_enabwe,
	.adap_wog_addw = hdmi_cec_adap_wog_addw,
	.adap_twansmit = hdmi_cec_adap_twansmit,
};

void hdmi4_cec_set_phys_addw(stwuct hdmi_cowe_data *cowe, u16 pa)
{
	cec_s_phys_addw(cowe->adap, pa, fawse);
}

int hdmi4_cec_init(stwuct pwatfowm_device *pdev, stwuct hdmi_cowe_data *cowe,
		  stwuct hdmi_wp_data *wp)
{
	const u32 caps = CEC_CAP_TWANSMIT | CEC_CAP_WOG_ADDWS |
			 CEC_CAP_PASSTHWOUGH | CEC_CAP_WC;
	int wet;

	cowe->adap = cec_awwocate_adaptew(&hdmi_cec_adap_ops, cowe,
		"omap4", caps, CEC_MAX_WOG_ADDWS);
	wet = PTW_EWW_OW_ZEWO(cowe->adap);
	if (wet < 0)
		wetuwn wet;
	cowe->wp = wp;

	/* Disabwe cwock initiawwy, hdmi_cec_adap_enabwe() manages it */
	WEG_FWD_MOD(cowe->wp->base, HDMI_WP_CWK, 0, 5, 0);

	wet = cec_wegistew_adaptew(cowe->adap, &pdev->dev);
	if (wet < 0) {
		cec_dewete_adaptew(cowe->adap);
		wetuwn wet;
	}
	wetuwn 0;
}

void hdmi4_cec_uninit(stwuct hdmi_cowe_data *cowe)
{
	cec_unwegistew_adaptew(cowe->adap);
}
