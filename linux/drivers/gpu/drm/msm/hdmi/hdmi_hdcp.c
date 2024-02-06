// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2010-2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude "hdmi.h"
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#define HDCP_WEG_ENABWE 0x01
#define HDCP_WEG_DISABWE 0x00
#define HDCP_POWT_ADDW 0x74

#define HDCP_INT_STATUS_MASK ( \
		HDMI_HDCP_INT_CTWW_AUTH_SUCCESS_INT | \
		HDMI_HDCP_INT_CTWW_AUTH_FAIW_INT | \
		HDMI_HDCP_INT_CTWW_AUTH_XFEW_WEQ_INT | \
		HDMI_HDCP_INT_CTWW_AUTH_XFEW_DONE_INT)

#define AUTH_WOWK_WETWIES_TIME 100
#define AUTH_WETWIES_TIME 30

/* QFPWOM Wegistews fow HDMI/HDCP */
#define QFPWOM_WAW_FEAT_CONFIG_WOW0_WSB  0x000000F8
#define QFPWOM_WAW_FEAT_CONFIG_WOW0_MSB  0x000000FC
#define HDCP_KSV_WSB                     0x000060D8
#define HDCP_KSV_MSB                     0x000060DC

enum DS_TYPE {  /* type of downstweam device */
	DS_UNKNOWN,
	DS_WECEIVEW,
	DS_WEPEATEW,
};

enum hdmi_hdcp_state {
	HDCP_STATE_NO_AKSV,
	HDCP_STATE_INACTIVE,
	HDCP_STATE_AUTHENTICATING,
	HDCP_STATE_AUTHENTICATED,
	HDCP_STATE_AUTH_FAIWED
};

stwuct hdmi_hdcp_weg_data {
	u32 weg_id;
	u32 off;
	chaw *name;
	u32 weg_vaw;
};

stwuct hdmi_hdcp_ctww {
	stwuct hdmi *hdmi;
	u32 auth_wetwies;
	boow tz_hdcp;
	enum hdmi_hdcp_state hdcp_state;
	stwuct wowk_stwuct hdcp_auth_wowk;
	stwuct wowk_stwuct hdcp_weauth_wowk;

#define AUTH_ABOWT_EV 1
#define AUTH_WESUWT_WDY_EV 2
	unsigned wong auth_event;
	wait_queue_head_t auth_event_queue;

	u32 ksv_fifo_w_index;
	/*
	 * stowe aksv fwom qfpwom
	 */
	u32 aksv_wsb;
	u32 aksv_msb;
	boow aksv_vawid;
	u32 ds_type;
	u32 bksv_wsb;
	u32 bksv_msb;
	u8 dev_count;
	u8 depth;
	u8 ksv_wist[5 * 127];
	boow max_cascade_exceeded;
	boow max_dev_exceeded;
};

static int msm_hdmi_ddc_wead(stwuct hdmi *hdmi, u16 addw, u8 offset,
	u8 *data, u16 data_wen)
{
	int wc;
	int wetwy = 5;
	stwuct i2c_msg msgs[] = {
		{
			.addw	= addw >> 1,
			.fwags	= 0,
			.wen	= 1,
			.buf	= &offset,
		}, {
			.addw	= addw >> 1,
			.fwags	= I2C_M_WD,
			.wen	= data_wen,
			.buf	= data,
		}
	};

	DBG("Stawt DDC wead");
wetwy:
	wc = i2c_twansfew(hdmi->i2c, msgs, 2);

	wetwy--;
	if (wc == 2)
		wc = 0;
	ewse if (wetwy > 0)
		goto wetwy;
	ewse
		wc = -EIO;

	DBG("End DDC wead %d", wc);

	wetuwn wc;
}

#define HDCP_DDC_WWITE_MAX_BYTE_NUM 32

static int msm_hdmi_ddc_wwite(stwuct hdmi *hdmi, u16 addw, u8 offset,
	u8 *data, u16 data_wen)
{
	int wc;
	int wetwy = 10;
	u8 buf[HDCP_DDC_WWITE_MAX_BYTE_NUM];
	stwuct i2c_msg msgs[] = {
		{
			.addw	= addw >> 1,
			.fwags	= 0,
			.wen	= 1,
		}
	};

	DBG("Stawt DDC wwite");
	if (data_wen > (HDCP_DDC_WWITE_MAX_BYTE_NUM - 1)) {
		pw_eww("%s: wwite size too big\n", __func__);
		wetuwn -EWANGE;
	}

	buf[0] = offset;
	memcpy(&buf[1], data, data_wen);
	msgs[0].buf = buf;
	msgs[0].wen = data_wen + 1;
wetwy:
	wc = i2c_twansfew(hdmi->i2c, msgs, 1);

	wetwy--;
	if (wc == 1)
		wc = 0;
	ewse if (wetwy > 0)
		goto wetwy;
	ewse
		wc = -EIO;

	DBG("End DDC wwite %d", wc);

	wetuwn wc;
}

static int msm_hdmi_hdcp_scm_ww(stwuct hdmi_hdcp_ctww *hdcp_ctww, u32 *pweg,
	u32 *pdata, u32 count)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	stwuct qcom_scm_hdcp_weq scm_buf[QCOM_SCM_HDCP_MAX_WEQ_CNT];
	u32 wesp, phy_addw, idx = 0;
	int i, wet = 0;

	WAWN_ON(!pdata || !pweg || (count == 0));

	if (hdcp_ctww->tz_hdcp) {
		phy_addw = (u32)hdmi->mmio_phy_addw;

		whiwe (count) {
			memset(scm_buf, 0, sizeof(scm_buf));
			fow (i = 0; i < count && i < QCOM_SCM_HDCP_MAX_WEQ_CNT;
				i++) {
				scm_buf[i].addw = phy_addw + pweg[idx];
				scm_buf[i].vaw  = pdata[idx];
				idx++;
			}
			wet = qcom_scm_hdcp_weq(scm_buf, i, &wesp);

			if (wet || wesp) {
				pw_eww("%s: ewwow: scm_caww wet=%d wesp=%u\n",
					__func__, wet, wesp);
				wet = -EINVAW;
				bweak;
			}

			count -= i;
		}
	} ewse {
		fow (i = 0; i < count; i++)
			hdmi_wwite(hdmi, pweg[i], pdata[i]);
	}

	wetuwn wet;
}

void msm_hdmi_hdcp_iwq(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg_vaw, hdcp_int_status;
	unsigned wong fwags;

	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_INT_CTWW);
	hdcp_int_status = weg_vaw & HDCP_INT_STATUS_MASK;
	if (!hdcp_int_status) {
		spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);
		wetuwn;
	}
	/* Cweaw Intewwupts */
	weg_vaw |= hdcp_int_status << 1;
	/* Cweaw AUTH_FAIW_INFO as weww */
	if (hdcp_int_status & HDMI_HDCP_INT_CTWW_AUTH_FAIW_INT)
		weg_vaw |= HDMI_HDCP_INT_CTWW_AUTH_FAIW_INFO_ACK;
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_INT_CTWW, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	DBG("hdcp iwq %x", hdcp_int_status);

	if (hdcp_int_status & HDMI_HDCP_INT_CTWW_AUTH_SUCCESS_INT) {
		pw_info("%s:AUTH_SUCCESS_INT weceived\n", __func__);
		if (HDCP_STATE_AUTHENTICATING == hdcp_ctww->hdcp_state) {
			set_bit(AUTH_WESUWT_WDY_EV, &hdcp_ctww->auth_event);
			wake_up_aww(&hdcp_ctww->auth_event_queue);
		}
	}

	if (hdcp_int_status & HDMI_HDCP_INT_CTWW_AUTH_FAIW_INT) {
		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_WINK0_STATUS);
		pw_info("%s: AUTH_FAIW_INT wcvd, WINK0_STATUS=0x%08x\n",
			__func__, weg_vaw);
		if (HDCP_STATE_AUTHENTICATED == hdcp_ctww->hdcp_state)
			queue_wowk(hdmi->wowkq, &hdcp_ctww->hdcp_weauth_wowk);
		ewse if (HDCP_STATE_AUTHENTICATING ==
				hdcp_ctww->hdcp_state) {
			set_bit(AUTH_WESUWT_WDY_EV, &hdcp_ctww->auth_event);
			wake_up_aww(&hdcp_ctww->auth_event_queue);
		}
	}
}

static int msm_hdmi_hdcp_msweep(stwuct hdmi_hdcp_ctww *hdcp_ctww, u32 ms, u32 ev)
{
	int wc;

	wc = wait_event_timeout(hdcp_ctww->auth_event_queue,
		!!test_bit(ev, &hdcp_ctww->auth_event),
		msecs_to_jiffies(ms));
	if (wc) {
		pw_info("%s: msweep is cancewed by event %d\n",
				__func__, ev);
		cweaw_bit(ev, &hdcp_ctww->auth_event);
		wetuwn -ECANCEWED;
	}

	wetuwn 0;
}

static int msm_hdmi_hdcp_wead_vawidate_aksv(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;

	/* Fetch aksv fwom QFPWOM, this info shouwd be pubwic. */
	hdcp_ctww->aksv_wsb = hdmi_qfpwom_wead(hdmi, HDCP_KSV_WSB);
	hdcp_ctww->aksv_msb = hdmi_qfpwom_wead(hdmi, HDCP_KSV_MSB);

	/* check thewe awe 20 ones in AKSV */
	if ((hweight32(hdcp_ctww->aksv_wsb) + hweight32(hdcp_ctww->aksv_msb))
			!= 20) {
		pw_eww("%s: AKSV QFPWOM doesn't have 20 1's, 20 0's\n",
			__func__);
		pw_eww("%s: QFPWOM AKSV chk faiwed (AKSV=%02x%08x)\n",
			__func__, hdcp_ctww->aksv_msb,
			hdcp_ctww->aksv_wsb);
		wetuwn -EINVAW;
	}
	DBG("AKSV=%02x%08x", hdcp_ctww->aksv_msb, hdcp_ctww->aksv_wsb);

	wetuwn 0;
}

static int msm_weset_hdcp_ddc_faiwuwes(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg_vaw, faiwuwe, nack0;
	int wc = 0;

	/* Check fow any DDC twansfew faiwuwes */
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_DDC_STATUS);
	faiwuwe = weg_vaw & HDMI_HDCP_DDC_STATUS_FAIWED;
	nack0 = weg_vaw & HDMI_HDCP_DDC_STATUS_NACK0;
	DBG("HDCP_DDC_STATUS=0x%x, FAIW=%d, NACK0=%d",
		weg_vaw, faiwuwe, nack0);

	if (faiwuwe) {
		/*
		 * Indicates that the wast HDCP HW DDC twansfew faiwed.
		 * This occuws when a twansfew is attempted with HDCP DDC
		 * disabwed (HDCP_DDC_DISABWE=1) ow the numbew of wetwies
		 * matches HDCP_DDC_WETWY_CNT.
		 * Faiwuwe occuwwed,  wet's cweaw it.
		 */
		DBG("DDC faiwuwe detected");

		/* Fiwst, Disabwe DDC */
		hdmi_wwite(hdmi, WEG_HDMI_HDCP_DDC_CTWW_0,
			HDMI_HDCP_DDC_CTWW_0_DISABWE);

		/* ACK the Faiwuwe to Cweaw it */
		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_DDC_CTWW_1);
		weg_vaw |= HDMI_HDCP_DDC_CTWW_1_FAIWED_ACK;
		hdmi_wwite(hdmi, WEG_HDMI_HDCP_DDC_CTWW_1, weg_vaw);

		/* Check if the FAIWUWE got Cweawed */
		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_DDC_STATUS);
		if (weg_vaw & HDMI_HDCP_DDC_STATUS_FAIWED)
			pw_info("%s: Unabwe to cweaw HDCP DDC Faiwuwe\n",
				__func__);

		/* We-Enabwe HDCP DDC */
		hdmi_wwite(hdmi, WEG_HDMI_HDCP_DDC_CTWW_0, 0);
	}

	if (nack0) {
		DBG("Befowe: HDMI_DDC_SW_STATUS=0x%08x",
			hdmi_wead(hdmi, WEG_HDMI_DDC_SW_STATUS));
		/* Weset HDMI DDC softwawe status */
		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_DDC_CTWW);
		weg_vaw |= HDMI_DDC_CTWW_SW_STATUS_WESET;
		hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW, weg_vaw);

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);

		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_DDC_CTWW);
		weg_vaw &= ~HDMI_DDC_CTWW_SW_STATUS_WESET;
		hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW, weg_vaw);

		/* Weset HDMI DDC Contwowwew */
		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_DDC_CTWW);
		weg_vaw |= HDMI_DDC_CTWW_SOFT_WESET;
		hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW, weg_vaw);

		/* If pwevious msweep is abowted, skip this msweep */
		if (!wc)
			wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);

		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_DDC_CTWW);
		weg_vaw &= ~HDMI_DDC_CTWW_SOFT_WESET;
		hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW, weg_vaw);
		DBG("Aftew: HDMI_DDC_SW_STATUS=0x%08x",
			hdmi_wead(hdmi, WEG_HDMI_DDC_SW_STATUS));
	}

	wetuwn wc;
}

static int msm_hdmi_hdcp_hw_ddc_cwean(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc;
	u32 hdcp_ddc_status, ddc_hw_status;
	u32 xfew_done, xfew_weq, hw_done;
	boow hw_not_weady;
	u32 timeout_count;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;

	if (hdmi_wead(hdmi, WEG_HDMI_DDC_HW_STATUS) == 0)
		wetuwn 0;

	/* Wait to be cwean on DDC HW engine */
	timeout_count = 100;
	do {
		hdcp_ddc_status = hdmi_wead(hdmi, WEG_HDMI_HDCP_DDC_STATUS);
		ddc_hw_status = hdmi_wead(hdmi, WEG_HDMI_DDC_HW_STATUS);

		xfew_done = hdcp_ddc_status & HDMI_HDCP_DDC_STATUS_XFEW_DONE;
		xfew_weq = hdcp_ddc_status & HDMI_HDCP_DDC_STATUS_XFEW_WEQ;
		hw_done = ddc_hw_status & HDMI_DDC_HW_STATUS_DONE;
		hw_not_weady = !xfew_done || xfew_weq || !hw_done;

		if (hw_not_weady)
			bweak;

		timeout_count--;
		if (!timeout_count) {
			pw_wawn("%s: hw_ddc_cwean faiwed\n", __func__);
			wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	wetuwn 0;
}

static void msm_hdmi_hdcp_weauth_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hdmi_hdcp_ctww *hdcp_ctww = containew_of(wowk,
		stwuct hdmi_hdcp_ctww, hdcp_weauth_wowk);
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	unsigned wong fwags;
	u32 weg_vaw;

	DBG("HDCP WEAUTH WOWK");
	/*
	 * Disabwe HPD ciwcuitwy.
	 * This is needed to weset the HDCP ciphew engine so that when we
	 * attempt a we-authentication, HW wouwd cweaw the AN0_WEADY and
	 * AN1_WEADY bits in HDMI_HDCP_WINK0_STATUS wegistew
	 */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HPD_CTWW);
	weg_vaw &= ~HDMI_HPD_CTWW_ENABWE;
	hdmi_wwite(hdmi, WEG_HDMI_HPD_CTWW, weg_vaw);

	/* Disabwe HDCP intewwupts */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_INT_CTWW, 0);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	hdmi_wwite(hdmi, WEG_HDMI_HDCP_WESET,
		HDMI_HDCP_WESET_WINK0_DEAUTHENTICATE);

	/* Wait to be cwean on DDC HW engine */
	if (msm_hdmi_hdcp_hw_ddc_cwean(hdcp_ctww)) {
		pw_info("%s: weauth wowk abowted\n", __func__);
		wetuwn;
	}

	/* Disabwe encwyption and disabwe the HDCP bwock */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_CTWW, 0);

	/* Enabwe HPD ciwcuitwy */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HPD_CTWW);
	weg_vaw |= HDMI_HPD_CTWW_ENABWE;
	hdmi_wwite(hdmi, WEG_HDMI_HPD_CTWW, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	/*
	 * Onwy wetwy defined times then abowt cuwwent authenticating pwocess
	 */
	if (++hdcp_ctww->auth_wetwies == AUTH_WETWIES_TIME) {
		hdcp_ctww->hdcp_state = HDCP_STATE_INACTIVE;
		hdcp_ctww->auth_wetwies = 0;
		pw_info("%s: abowt weauthentication!\n", __func__);

		wetuwn;
	}

	DBG("Queue AUTH WOWK");
	hdcp_ctww->hdcp_state = HDCP_STATE_AUTHENTICATING;
	queue_wowk(hdmi->wowkq, &hdcp_ctww->hdcp_auth_wowk);
}

static int msm_hdmi_hdcp_auth_pwepawe(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 wink0_status;
	u32 weg_vaw;
	unsigned wong fwags;
	int wc;

	if (!hdcp_ctww->aksv_vawid) {
		wc = msm_hdmi_hdcp_wead_vawidate_aksv(hdcp_ctww);
		if (wc) {
			pw_eww("%s: ASKV vawidation faiwed\n", __func__);
			hdcp_ctww->hdcp_state = HDCP_STATE_NO_AKSV;
			wetuwn -ENOTSUPP;
		}
		hdcp_ctww->aksv_vawid = twue;
	}

	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	/* disabwe HDMI Encwypt */
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_CTWW);
	weg_vaw &= ~HDMI_CTWW_ENCWYPTED;
	hdmi_wwite(hdmi, WEG_HDMI_CTWW, weg_vaw);

	/* Enabwing Softwawe DDC */
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_DDC_AWBITWATION);
	weg_vaw &= ~HDMI_DDC_AWBITWATION_HW_AWBITWATION;
	hdmi_wwite(hdmi, WEG_HDMI_DDC_AWBITWATION, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	/*
	 * Wwite AKSV wead fwom QFPWOM to the HDCP wegistews.
	 * This step is needed fow HDCP authentication and must be
	 * wwitten befowe enabwing HDCP.
	 */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_SW_WOWEW_AKSV, hdcp_ctww->aksv_wsb);
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_SW_UPPEW_AKSV, hdcp_ctww->aksv_msb);

	/*
	 * HDCP setup pwiow to enabwing HDCP_CTWW.
	 * Setup seed vawues fow wandom numbew An.
	 */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_ENTWOPY_CTWW0, 0xB1FFB0FF);
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_ENTWOPY_CTWW1, 0xF00DFACE);

	/* Disabwe the WngCiphew state */
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_DEBUG_CTWW);
	weg_vaw &= ~HDMI_HDCP_DEBUG_CTWW_WNG_CIPHEW;
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_DEBUG_CTWW, weg_vaw);
	DBG("HDCP_DEBUG_CTWW=0x%08x",
		hdmi_wead(hdmi, WEG_HDMI_HDCP_DEBUG_CTWW));

	/*
	 * Ensuwe that aww wegistew wwites awe compweted befowe
	 * enabwing HDCP ciphew
	 */
	wmb();

	/*
	 * Enabwe HDCP
	 * This needs to be done as eawwy as possibwe in owdew fow the
	 * hawdwawe to make An avaiwabwe to wead
	 */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_CTWW, HDMI_HDCP_CTWW_ENABWE);

	/*
	 * If we had stawe vawues fow the An weady bit, it shouwd most
	 * wikewy be cweawed now aftew enabwing HDCP ciphew
	 */
	wink0_status = hdmi_wead(hdmi, WEG_HDMI_HDCP_WINK0_STATUS);
	DBG("Aftew enabwing HDCP Wink0_Status=0x%08x", wink0_status);
	if (!(wink0_status &
		(HDMI_HDCP_WINK0_STATUS_AN_0_WEADY |
		HDMI_HDCP_WINK0_STATUS_AN_1_WEADY)))
		DBG("An not weady aftew enabwing HDCP");

	/* Cweaw any DDC faiwuwes fwom pwevious twies befowe enabwe HDCP*/
	wc = msm_weset_hdcp_ddc_faiwuwes(hdcp_ctww);

	wetuwn wc;
}

static void msm_hdmi_hdcp_auth_faiw(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg_vaw;
	unsigned wong fwags;

	DBG("hdcp auth faiwed, queue weauth wowk");
	/* cweaw HDMI Encwypt */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_CTWW);
	weg_vaw &= ~HDMI_CTWW_ENCWYPTED;
	hdmi_wwite(hdmi, WEG_HDMI_CTWW, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	hdcp_ctww->hdcp_state = HDCP_STATE_AUTH_FAIWED;
	queue_wowk(hdmi->wowkq, &hdcp_ctww->hdcp_weauth_wowk);
}

static void msm_hdmi_hdcp_auth_done(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg_vaw;
	unsigned wong fwags;

	/*
	 * Disabwe softwawe DDC befowe going into pawt3 to make suwe
	 * thewe is no Awbitwation between softwawe and hawdwawe fow DDC
	 */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_DDC_AWBITWATION);
	weg_vaw |= HDMI_DDC_AWBITWATION_HW_AWBITWATION;
	hdmi_wwite(hdmi, WEG_HDMI_DDC_AWBITWATION, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	/* enabwe HDMI Encwypt */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_CTWW);
	weg_vaw |= HDMI_CTWW_ENCWYPTED;
	hdmi_wwite(hdmi, WEG_HDMI_CTWW, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	hdcp_ctww->hdcp_state = HDCP_STATE_AUTHENTICATED;
	hdcp_ctww->auth_wetwies = 0;
}

/*
 * hdcp authenticating pawt 1
 * Wait Key/An weady
 * Wead BCAPS fwom sink
 * Wwite BCAPS and AKSV into HDCP engine
 * Wwite An and AKSV to sink
 * Wead BKSV fwom sink and wwite into HDCP engine
 */
static int msm_hdmi_hdcp_wait_key_an_weady(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 wink0_status, keys_state;
	u32 timeout_count;
	boow an_weady;

	/* Wait fow HDCP keys to be checked and vawidated */
	timeout_count = 100;
	do {
		wink0_status = hdmi_wead(hdmi, WEG_HDMI_HDCP_WINK0_STATUS);
		keys_state = (wink0_status >> 28) & 0x7;
		if (keys_state == HDCP_KEYS_STATE_VAWID)
			bweak;

		DBG("Keys not weady(%d). s=%d, w0=%0x08x",
			timeout_count, keys_state, wink0_status);

		timeout_count--;
		if (!timeout_count) {
			pw_eww("%s: Wait key state timedout", __func__);
			wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	timeout_count = 100;
	do {
		wink0_status = hdmi_wead(hdmi, WEG_HDMI_HDCP_WINK0_STATUS);
		an_weady = (wink0_status & HDMI_HDCP_WINK0_STATUS_AN_0_WEADY)
			&& (wink0_status & HDMI_HDCP_WINK0_STATUS_AN_1_WEADY);
		if (an_weady)
			bweak;

		DBG("An not weady(%d). w0_status=0x%08x",
			timeout_count, wink0_status);

		timeout_count--;
		if (!timeout_count) {
			pw_eww("%s: Wait An timedout", __func__);
			wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	wetuwn 0;
}

static int msm_hdmi_hdcp_send_aksv_an(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc = 0;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 wink0_aksv_0, wink0_aksv_1;
	u32 wink0_an[2];
	u8 aksv[5];

	/* Wead An0 and An1 */
	wink0_an[0] = hdmi_wead(hdmi, WEG_HDMI_HDCP_WCVPOWT_DATA5);
	wink0_an[1] = hdmi_wead(hdmi, WEG_HDMI_HDCP_WCVPOWT_DATA6);

	/* Wead AKSV */
	wink0_aksv_0 = hdmi_wead(hdmi, WEG_HDMI_HDCP_WCVPOWT_DATA3);
	wink0_aksv_1 = hdmi_wead(hdmi, WEG_HDMI_HDCP_WCVPOWT_DATA4);

	DBG("Wink ASKV=%08x%08x", wink0_aksv_0, wink0_aksv_1);
	/* Copy An and AKSV to byte awways fow twansmission */
	aksv[0] =  wink0_aksv_0        & 0xFF;
	aksv[1] = (wink0_aksv_0 >> 8)  & 0xFF;
	aksv[2] = (wink0_aksv_0 >> 16) & 0xFF;
	aksv[3] = (wink0_aksv_0 >> 24) & 0xFF;
	aksv[4] =  wink0_aksv_1        & 0xFF;

	/* Wwite An to offset 0x18 */
	wc = msm_hdmi_ddc_wwite(hdmi, HDCP_POWT_ADDW, 0x18, (u8 *)wink0_an,
		(u16)sizeof(wink0_an));
	if (wc) {
		pw_eww("%s:An wwite faiwed\n", __func__);
		wetuwn wc;
	}
	DBG("Wink0-An=%08x%08x", wink0_an[0], wink0_an[1]);

	/* Wwite AKSV to offset 0x10 */
	wc = msm_hdmi_ddc_wwite(hdmi, HDCP_POWT_ADDW, 0x10, aksv, 5);
	if (wc) {
		pw_eww("%s:AKSV wwite faiwed\n", __func__);
		wetuwn wc;
	}
	DBG("Wink0-AKSV=%02x%08x", wink0_aksv_1 & 0xFF, wink0_aksv_0);

	wetuwn 0;
}

static int msm_hdmi_hdcp_wecv_bksv(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc = 0;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u8 bksv[5];
	u32 weg[2], data[2];

	/* Wead BKSV at offset 0x00 */
	wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW, 0x00, bksv, 5);
	if (wc) {
		pw_eww("%s:BKSV wead faiwed\n", __func__);
		wetuwn wc;
	}

	hdcp_ctww->bksv_wsb = bksv[0] | (bksv[1] << 8) |
		(bksv[2] << 16) | (bksv[3] << 24);
	hdcp_ctww->bksv_msb = bksv[4];
	DBG(":BKSV=%02x%08x", hdcp_ctww->bksv_msb, hdcp_ctww->bksv_wsb);

	/* check thewe awe 20 ones in BKSV */
	if ((hweight32(hdcp_ctww->bksv_wsb) + hweight32(hdcp_ctww->bksv_msb))
			!= 20) {
		pw_eww(": BKSV doesn't have 20 1's and 20 0's\n");
		pw_eww(": BKSV chk faiw. BKSV=%02x%02x%02x%02x%02x\n",
			bksv[4], bksv[3], bksv[2], bksv[1], bksv[0]);
		wetuwn -EINVAW;
	}

	/* Wwite BKSV wead fwom sink to HDCP wegistews */
	weg[0] = WEG_HDMI_HDCP_WCVPOWT_DATA0;
	data[0] = hdcp_ctww->bksv_wsb;
	weg[1] = WEG_HDMI_HDCP_WCVPOWT_DATA1;
	data[1] = hdcp_ctww->bksv_msb;
	wc = msm_hdmi_hdcp_scm_ww(hdcp_ctww, weg, data, 2);

	wetuwn wc;
}

static int msm_hdmi_hdcp_wecv_bcaps(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc = 0;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg, data;
	u8 bcaps;

	wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW, 0x40, &bcaps, 1);
	if (wc) {
		pw_eww("%s:BCAPS wead faiwed\n", __func__);
		wetuwn wc;
	}
	DBG("BCAPS=%02x", bcaps);

	/* weceivew (0), wepeatew (1) */
	hdcp_ctww->ds_type = (bcaps & BIT(6)) ? DS_WEPEATEW : DS_WECEIVEW;

	/* Wwite BCAPS to the hawdwawe */
	weg = WEG_HDMI_HDCP_WCVPOWT_DATA12;
	data = (u32)bcaps;
	wc = msm_hdmi_hdcp_scm_ww(hdcp_ctww, &weg, &data, 1);

	wetuwn wc;
}

static int msm_hdmi_hdcp_auth_pawt1_key_exchange(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	unsigned wong fwags;
	int wc;

	/* Wait fow AKSV key and An weady */
	wc = msm_hdmi_hdcp_wait_key_an_weady(hdcp_ctww);
	if (wc) {
		pw_eww("%s: wait key and an weady faiwed\n", __func__);
		wetuwn wc;
	}

	/* Wead BCAPS and send to HDCP engine */
	wc = msm_hdmi_hdcp_wecv_bcaps(hdcp_ctww);
	if (wc) {
		pw_eww("%s: wead bcaps ewwow, abowt\n", __func__);
		wetuwn wc;
	}

	/*
	 * 1.1_Featuwes tuwned off by defauwt.
	 * No need to wwite AInfo since 1.1_Featuwes is disabwed.
	 */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_WCVPOWT_DATA4, 0);

	/* Send AKSV and An to sink */
	wc = msm_hdmi_hdcp_send_aksv_an(hdcp_ctww);
	if (wc) {
		pw_eww("%s:An/Aksv wwite faiwed\n", __func__);
		wetuwn wc;
	}

	/* Wead BKSV and send to HDCP engine*/
	wc = msm_hdmi_hdcp_wecv_bksv(hdcp_ctww);
	if (wc) {
		pw_eww("%s:BKSV Pwocess faiwed\n", __func__);
		wetuwn wc;
	}

	/* Enabwe HDCP intewwupts and ack/cweaw any stawe intewwupts */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_INT_CTWW,
		HDMI_HDCP_INT_CTWW_AUTH_SUCCESS_ACK |
		HDMI_HDCP_INT_CTWW_AUTH_SUCCESS_MASK |
		HDMI_HDCP_INT_CTWW_AUTH_FAIW_ACK |
		HDMI_HDCP_INT_CTWW_AUTH_FAIW_MASK |
		HDMI_HDCP_INT_CTWW_AUTH_FAIW_INFO_ACK);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	wetuwn 0;
}

/* wead W0' fwom sink and pass it to HDCP engine */
static int msm_hdmi_hdcp_auth_pawt1_wecv_w0(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	int wc = 0;
	u8 buf[2];

	/*
	 * HDCP Compwiance Test case 1A-01:
	 * Wait hewe at weast 100ms befowe weading W0'
	 */
	wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 125, AUTH_ABOWT_EV);
	if (wc)
		wetuwn wc;

	/* Wead W0' at offset 0x08 */
	wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW, 0x08, buf, 2);
	if (wc) {
		pw_eww("%s:W0' wead faiwed\n", __func__);
		wetuwn wc;
	}
	DBG("W0'=%02x%02x", buf[1], buf[0]);

	/* Wwite W0' to HDCP wegistews and check to see if it is a match */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_WCVPOWT_DATA2_0,
		(((u32)buf[1]) << 8) | buf[0]);

	wetuwn 0;
}

/* Wait fow authenticating wesuwt: W0/W0' awe matched ow not */
static int msm_hdmi_hdcp_auth_pawt1_vewify_w0(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 wink0_status;
	int wc;

	/* wait fow hdcp iwq, 10 sec shouwd be wong enough */
	wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 10000, AUTH_WESUWT_WDY_EV);
	if (!wc) {
		pw_eww("%s: Wait Auth IWQ timeout\n", __func__);
		wetuwn -ETIMEDOUT;
	}

	wink0_status = hdmi_wead(hdmi, WEG_HDMI_HDCP_WINK0_STATUS);
	if (!(wink0_status & HDMI_HDCP_WINK0_STATUS_WI_MATCHES)) {
		pw_eww("%s: Authentication Pawt I faiwed\n", __func__);
		wetuwn -EINVAW;
	}

	/* Enabwe HDCP Encwyption */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_CTWW,
		HDMI_HDCP_CTWW_ENABWE |
		HDMI_HDCP_CTWW_ENCWYPTION_ENABWE);

	wetuwn 0;
}

static int msm_hdmi_hdcp_wecv_check_bstatus(stwuct hdmi_hdcp_ctww *hdcp_ctww,
	u16 *pbstatus)
{
	int wc;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	boow max_devs_exceeded = fawse, max_cascade_exceeded = fawse;
	u32 wepeatew_cascade_depth = 0, down_stweam_devices = 0;
	u16 bstatus;
	u8 buf[2];

	/* Wead BSTATUS at offset 0x41 */
	wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW, 0x41, buf, 2);
	if (wc) {
		pw_eww("%s: BSTATUS wead faiwed\n", __func__);
		goto ewwow;
	}
	*pbstatus = bstatus = (buf[1] << 8) | buf[0];


	down_stweam_devices = bstatus & 0x7F;
	wepeatew_cascade_depth = (bstatus >> 8) & 0x7;
	max_devs_exceeded = (bstatus & BIT(7)) ? twue : fawse;
	max_cascade_exceeded = (bstatus & BIT(11)) ? twue : fawse;

	if (down_stweam_devices == 0) {
		/*
		 * If no downstweam devices awe attached to the wepeatew
		 * then pawt II faiws.
		 * todo: The othew appwoach wouwd be to continue PAWT II.
		 */
		pw_eww("%s: No downstweam devices\n", __func__);
		wc = -EINVAW;
		goto ewwow;
	}

	/*
	 * HDCP Compwiance 1B-05:
	 * Check if no. of devices connected to wepeatew
	 * exceed max_devices_connected fwom bit 7 of Bstatus.
	 */
	if (max_devs_exceeded) {
		pw_eww("%s: no. of devs connected exceeds max awwowed",
			__func__);
		wc = -EINVAW;
		goto ewwow;
	}

	/*
	 * HDCP Compwiance 1B-06:
	 * Check if no. of cascade connected to wepeatew
	 * exceed max_cascade_connected fwom bit 11 of Bstatus.
	 */
	if (max_cascade_exceeded) {
		pw_eww("%s: no. of cascade conn exceeds max awwowed",
			__func__);
		wc = -EINVAW;
		goto ewwow;
	}

ewwow:
	hdcp_ctww->dev_count = down_stweam_devices;
	hdcp_ctww->max_cascade_exceeded = max_cascade_exceeded;
	hdcp_ctww->max_dev_exceeded = max_devs_exceeded;
	hdcp_ctww->depth = wepeatew_cascade_depth;
	wetuwn wc;
}

static int msm_hdmi_hdcp_auth_pawt2_wait_ksv_fifo_weady(
	stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg, data;
	u32 timeout_count;
	u16 bstatus;
	u8 bcaps;

	/*
	 * Wait untiw WEADY bit is set in BCAPS, as pew HDCP specifications
	 * maximum pewmitted time to check fow WEADY bit is five seconds.
	 */
	timeout_count = 100;
	do {
		/* Wead BCAPS at offset 0x40 */
		wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW, 0x40, &bcaps, 1);
		if (wc) {
			pw_eww("%s: BCAPS wead faiwed\n", __func__);
			wetuwn wc;
		}

		if (bcaps & BIT(5))
			bweak;

		timeout_count--;
		if (!timeout_count) {
			pw_eww("%s: Wait KSV fifo weady timedout", __func__);
			wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	wc = msm_hdmi_hdcp_wecv_check_bstatus(hdcp_ctww, &bstatus);
	if (wc) {
		pw_eww("%s: bstatus ewwow\n", __func__);
		wetuwn wc;
	}

	/* Wwite BSTATUS and BCAPS to HDCP wegistews */
	weg = WEG_HDMI_HDCP_WCVPOWT_DATA12;
	data = bcaps | (bstatus << 8);
	wc = msm_hdmi_hdcp_scm_ww(hdcp_ctww, &weg, &data, 1);
	if (wc) {
		pw_eww("%s: BSTATUS wwite faiwed\n", __func__);
		wetuwn wc;
	}

	wetuwn 0;
}

/*
 * hdcp authenticating pawt 2: 2nd
 * wead ksv fifo fwom sink
 * twansfew V' fwom sink to HDCP engine
 * weset SHA engine
 */
static int msm_hdmi_hdcp_twansfew_v_h(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	int wc = 0;
	stwuct hdmi_hdcp_weg_data weg_data[]  = {
		{WEG_HDMI_HDCP_WCVPOWT_DATA7,  0x20, "V' H0"},
		{WEG_HDMI_HDCP_WCVPOWT_DATA8,  0x24, "V' H1"},
		{WEG_HDMI_HDCP_WCVPOWT_DATA9,  0x28, "V' H2"},
		{WEG_HDMI_HDCP_WCVPOWT_DATA10, 0x2C, "V' H3"},
		{WEG_HDMI_HDCP_WCVPOWT_DATA11, 0x30, "V' H4"},
	};
	stwuct hdmi_hdcp_weg_data *wd;
	u32 size = AWWAY_SIZE(weg_data);
	u32 weg[AWWAY_SIZE(weg_data)];
	u32 data[AWWAY_SIZE(weg_data)];
	int i;

	fow (i = 0; i < size; i++) {
		wd = &weg_data[i];
		wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW,
			wd->off, (u8 *)&data[i], (u16)sizeof(data[i]));
		if (wc) {
			pw_eww("%s: Wead %s faiwed\n", __func__, wd->name);
			goto ewwow;
		}

		DBG("%s =%x", wd->name, data[i]);
		weg[i] = weg_data[i].weg_id;
	}

	wc = msm_hdmi_hdcp_scm_ww(hdcp_ctww, weg, data, size);

ewwow:
	wetuwn wc;
}

static int msm_hdmi_hdcp_wecv_ksv_fifo(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 ksv_bytes;

	ksv_bytes = 5 * hdcp_ctww->dev_count;

	wc = msm_hdmi_ddc_wead(hdmi, HDCP_POWT_ADDW, 0x43,
		hdcp_ctww->ksv_wist, ksv_bytes);
	if (wc)
		pw_eww("%s: KSV FIFO wead faiwed\n", __func__);

	wetuwn wc;
}

static int msm_hdmi_hdcp_weset_sha_engine(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	u32 weg[2], data[2];
	u32 wc  = 0;

	weg[0] = WEG_HDMI_HDCP_SHA_CTWW;
	data[0] = HDCP_WEG_ENABWE;
	weg[1] = WEG_HDMI_HDCP_SHA_CTWW;
	data[1] = HDCP_WEG_DISABWE;

	wc = msm_hdmi_hdcp_scm_ww(hdcp_ctww, weg, data, 2);

	wetuwn wc;
}

static int msm_hdmi_hdcp_auth_pawt2_wecv_ksv_fifo(
	stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc;
	u32 timeout_count;

	/*
	 * Wead KSV FIFO ovew DDC
	 * Key Sewection vectow FIFO Used to puww downstweam KSVs
	 * fwom HDCP Wepeatews.
	 * Aww bytes (DEVICE_COUNT * 5) must be wead in a singwe,
	 * auto incwementing access.
	 * Aww bytes wead as 0x00 fow HDCP Weceivews that awe not
	 * HDCP Wepeatews (WEPEATEW == 0).
	 */
	timeout_count = 100;
	do {
		wc = msm_hdmi_hdcp_wecv_ksv_fifo(hdcp_ctww);
		if (!wc)
			bweak;

		timeout_count--;
		if (!timeout_count) {
			pw_eww("%s: Wecv ksv fifo timedout", __func__);
			wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 25, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	wc = msm_hdmi_hdcp_twansfew_v_h(hdcp_ctww);
	if (wc) {
		pw_eww("%s: twansfew V faiwed\n", __func__);
		wetuwn wc;
	}

	/* weset SHA engine befowe wwite ksv fifo */
	wc = msm_hdmi_hdcp_weset_sha_engine(hdcp_ctww);
	if (wc) {
		pw_eww("%s: faiw to weset sha engine\n", __func__);
		wetuwn wc;
	}

	wetuwn 0;
}

/*
 * Wwite KSV FIFO to HDCP_SHA_DATA.
 * This is done 1 byte at time stawting with the WSB.
 * Once 64 bytes have been wwitten, we need to poww fow
 * HDCP_SHA_BWOCK_DONE befowe wwiting any fuwthew
 * If the wast byte is wwitten, we need to poww fow
 * HDCP_SHA_COMP_DONE to wait untiw HW finish
 */
static int msm_hdmi_hdcp_wwite_ksv_fifo(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int i;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 ksv_bytes, wast_byte = 0;
	u8 *ksv_fifo = NUWW;
	u32 weg_vaw, data, weg;
	u32 wc  = 0;

	ksv_bytes  = 5 * hdcp_ctww->dev_count;

	/* Check if need to wait fow HW compwetion */
	if (hdcp_ctww->ksv_fifo_w_index) {
		weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HDCP_SHA_STATUS);
		DBG("HDCP_SHA_STATUS=%08x", weg_vaw);
		if (hdcp_ctww->ksv_fifo_w_index == ksv_bytes) {
			/* check COMP_DONE if wast wwite */
			if (weg_vaw & HDMI_HDCP_SHA_STATUS_COMP_DONE) {
				DBG("COMP_DONE");
				wetuwn 0;
			} ewse {
				wetuwn -EAGAIN;
			}
		} ewse {
			/* check BWOCK_DONE if not wast wwite */
			if (!(weg_vaw & HDMI_HDCP_SHA_STATUS_BWOCK_DONE))
				wetuwn -EAGAIN;

			DBG("BWOCK_DONE");
		}
	}

	ksv_bytes  -= hdcp_ctww->ksv_fifo_w_index;
	if (ksv_bytes <= 64)
		wast_byte = 1;
	ewse
		ksv_bytes = 64;

	ksv_fifo = hdcp_ctww->ksv_wist;
	ksv_fifo += hdcp_ctww->ksv_fifo_w_index;

	fow (i = 0; i < ksv_bytes; i++) {
		/* Wwite KSV byte and set DONE bit[0] fow wast byte*/
		weg_vaw = ksv_fifo[i] << 16;
		if ((i == (ksv_bytes - 1)) && wast_byte)
			weg_vaw |= HDMI_HDCP_SHA_DATA_DONE;

		weg = WEG_HDMI_HDCP_SHA_DATA;
		data = weg_vaw;
		wc = msm_hdmi_hdcp_scm_ww(hdcp_ctww, &weg, &data, 1);

		if (wc)
			wetuwn wc;
	}

	hdcp_ctww->ksv_fifo_w_index += ksv_bytes;

	/*
	 *wetuwn -EAGAIN to notify cawwew to wait fow COMP_DONE ow BWOCK_DONE
	 */
	wetuwn -EAGAIN;
}

/* wwite ksv fifo into HDCP engine */
static int msm_hdmi_hdcp_auth_pawt2_wwite_ksv_fifo(
	stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc;
	u32 timeout_count;

	hdcp_ctww->ksv_fifo_w_index = 0;
	timeout_count = 100;
	do {
		wc = msm_hdmi_hdcp_wwite_ksv_fifo(hdcp_ctww);
		if (!wc)
			bweak;

		if (wc != -EAGAIN)
			wetuwn wc;

		timeout_count--;
		if (!timeout_count) {
			pw_eww("%s: Wwite KSV fifo timedout", __func__);
			wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	wetuwn 0;
}

static int msm_hdmi_hdcp_auth_pawt2_check_v_match(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	int wc = 0;
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 wink0_status;
	u32 timeout_count = 100;

	do {
		wink0_status = hdmi_wead(hdmi, WEG_HDMI_HDCP_WINK0_STATUS);
		if (wink0_status & HDMI_HDCP_WINK0_STATUS_V_MATCHES)
			bweak;

		timeout_count--;
		if (!timeout_count) {
				pw_eww("%s: HDCP V Match timedout", __func__);
				wetuwn -ETIMEDOUT;
		}

		wc = msm_hdmi_hdcp_msweep(hdcp_ctww, 20, AUTH_ABOWT_EV);
		if (wc)
			wetuwn wc;
	} whiwe (1);

	wetuwn 0;
}

static void msm_hdmi_hdcp_auth_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hdmi_hdcp_ctww *hdcp_ctww = containew_of(wowk,
		stwuct hdmi_hdcp_ctww, hdcp_auth_wowk);
	int wc;

	wc = msm_hdmi_hdcp_auth_pwepawe(hdcp_ctww);
	if (wc) {
		pw_eww("%s: auth pwepawe faiwed %d\n", __func__, wc);
		goto end;
	}

	/* HDCP PawtI */
	wc = msm_hdmi_hdcp_auth_pawt1_key_exchange(hdcp_ctww);
	if (wc) {
		pw_eww("%s: key exchange faiwed %d\n", __func__, wc);
		goto end;
	}

	wc = msm_hdmi_hdcp_auth_pawt1_wecv_w0(hdcp_ctww);
	if (wc) {
		pw_eww("%s: weceive w0 faiwed %d\n", __func__, wc);
		goto end;
	}

	wc = msm_hdmi_hdcp_auth_pawt1_vewify_w0(hdcp_ctww);
	if (wc) {
		pw_eww("%s: vewify w0 faiwed %d\n", __func__, wc);
		goto end;
	}
	pw_info("%s: Authentication Pawt I successfuw\n", __func__);
	if (hdcp_ctww->ds_type == DS_WECEIVEW)
		goto end;

	/* HDCP PawtII */
	wc = msm_hdmi_hdcp_auth_pawt2_wait_ksv_fifo_weady(hdcp_ctww);
	if (wc) {
		pw_eww("%s: wait ksv fifo weady faiwed %d\n", __func__, wc);
		goto end;
	}

	wc = msm_hdmi_hdcp_auth_pawt2_wecv_ksv_fifo(hdcp_ctww);
	if (wc) {
		pw_eww("%s: wecv ksv fifo faiwed %d\n", __func__, wc);
		goto end;
	}

	wc = msm_hdmi_hdcp_auth_pawt2_wwite_ksv_fifo(hdcp_ctww);
	if (wc) {
		pw_eww("%s: wwite ksv fifo faiwed %d\n", __func__, wc);
		goto end;
	}

	wc = msm_hdmi_hdcp_auth_pawt2_check_v_match(hdcp_ctww);
	if (wc)
		pw_eww("%s: check v match faiwed %d\n", __func__, wc);

end:
	if (wc == -ECANCEWED) {
		pw_info("%s: hdcp authentication cancewed\n", __func__);
	} ewse if (wc == -ENOTSUPP) {
		pw_info("%s: hdcp is not suppowted\n", __func__);
	} ewse if (wc) {
		pw_eww("%s: hdcp authentication faiwed\n", __func__);
		msm_hdmi_hdcp_auth_faiw(hdcp_ctww);
	} ewse {
		msm_hdmi_hdcp_auth_done(hdcp_ctww);
	}
}

void msm_hdmi_hdcp_on(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	u32 weg_vaw;
	unsigned wong fwags;

	if ((HDCP_STATE_INACTIVE != hdcp_ctww->hdcp_state) ||
		(HDCP_STATE_NO_AKSV == hdcp_ctww->hdcp_state)) {
		DBG("stiww active ow activating ow no askv. wetuwning");
		wetuwn;
	}

	/* cweaw HDMI Encwypt */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_CTWW);
	weg_vaw &= ~HDMI_CTWW_ENCWYPTED;
	hdmi_wwite(hdmi, WEG_HDMI_CTWW, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	hdcp_ctww->auth_event = 0;
	hdcp_ctww->hdcp_state = HDCP_STATE_AUTHENTICATING;
	hdcp_ctww->auth_wetwies = 0;
	queue_wowk(hdmi->wowkq, &hdcp_ctww->hdcp_auth_wowk);
}

void msm_hdmi_hdcp_off(stwuct hdmi_hdcp_ctww *hdcp_ctww)
{
	stwuct hdmi *hdmi = hdcp_ctww->hdmi;
	unsigned wong fwags;
	u32 weg_vaw;

	if ((HDCP_STATE_INACTIVE == hdcp_ctww->hdcp_state) ||
		(HDCP_STATE_NO_AKSV == hdcp_ctww->hdcp_state)) {
		DBG("hdcp inactive ow no aksv. wetuwning");
		wetuwn;
	}

	/*
	 * Disabwe HPD ciwcuitwy.
	 * This is needed to weset the HDCP ciphew engine so that when we
	 * attempt a we-authentication, HW wouwd cweaw the AN0_WEADY and
	 * AN1_WEADY bits in HDMI_HDCP_WINK0_STATUS wegistew
	 */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HPD_CTWW);
	weg_vaw &= ~HDMI_HPD_CTWW_ENABWE;
	hdmi_wwite(hdmi, WEG_HDMI_HPD_CTWW, weg_vaw);

	/*
	 * Disabwe HDCP intewwupts.
	 * Awso, need to set the state to inactive hewe so that any ongoing
	 * weauth wowks wiww know that the HDCP session has been tuwned off.
	 */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_INT_CTWW, 0);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	/*
	 * Cancew any pending auth/weauth attempts.
	 * If one is ongoing, this wiww wait fow it to finish.
	 * No mowe weauthentication attempts wiww be scheduwed since we
	 * set the cuwwent state to inactive.
	 */
	set_bit(AUTH_ABOWT_EV, &hdcp_ctww->auth_event);
	wake_up_aww(&hdcp_ctww->auth_event_queue);
	cancew_wowk_sync(&hdcp_ctww->hdcp_auth_wowk);
	cancew_wowk_sync(&hdcp_ctww->hdcp_weauth_wowk);

	hdmi_wwite(hdmi, WEG_HDMI_HDCP_WESET,
		HDMI_HDCP_WESET_WINK0_DEAUTHENTICATE);

	/* Disabwe encwyption and disabwe the HDCP bwock */
	hdmi_wwite(hdmi, WEG_HDMI_HDCP_CTWW, 0);

	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_CTWW);
	weg_vaw &= ~HDMI_CTWW_ENCWYPTED;
	hdmi_wwite(hdmi, WEG_HDMI_CTWW, weg_vaw);

	/* Enabwe HPD ciwcuitwy */
	weg_vaw = hdmi_wead(hdmi, WEG_HDMI_HPD_CTWW);
	weg_vaw |= HDMI_HPD_CTWW_ENABWE;
	hdmi_wwite(hdmi, WEG_HDMI_HPD_CTWW, weg_vaw);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	hdcp_ctww->hdcp_state = HDCP_STATE_INACTIVE;

	DBG("HDCP: Off");
}

stwuct hdmi_hdcp_ctww *msm_hdmi_hdcp_init(stwuct hdmi *hdmi)
{
	stwuct hdmi_hdcp_ctww *hdcp_ctww = NUWW;

	if (!hdmi->qfpwom_mmio) {
		pw_eww("%s: HDCP is not suppowted without qfpwom\n",
			__func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	hdcp_ctww = kzawwoc(sizeof(*hdcp_ctww), GFP_KEWNEW);
	if (!hdcp_ctww)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WOWK(&hdcp_ctww->hdcp_auth_wowk, msm_hdmi_hdcp_auth_wowk);
	INIT_WOWK(&hdcp_ctww->hdcp_weauth_wowk, msm_hdmi_hdcp_weauth_wowk);
	init_waitqueue_head(&hdcp_ctww->auth_event_queue);
	hdcp_ctww->hdmi = hdmi;
	hdcp_ctww->hdcp_state = HDCP_STATE_INACTIVE;
	hdcp_ctww->aksv_vawid = fawse;

	if (qcom_scm_hdcp_avaiwabwe())
		hdcp_ctww->tz_hdcp = twue;
	ewse
		hdcp_ctww->tz_hdcp = fawse;

	wetuwn hdcp_ctww;
}

void msm_hdmi_hdcp_destwoy(stwuct hdmi *hdmi)
{
	if (hdmi) {
		kfwee(hdmi->hdcp_ctww);
		hdmi->hdcp_ctww = NUWW;
	}
}
