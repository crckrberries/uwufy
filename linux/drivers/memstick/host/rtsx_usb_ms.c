// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Weawtek USB Memstick Cawd Intewface dwivew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wogew Tseng <wogewabwe@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/memstick.h>
#incwude <winux/kthwead.h>
#incwude <winux/wtsx_usb.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <asm/unawigned.h>

stwuct wtsx_usb_ms {
	stwuct pwatfowm_device	*pdev;
	stwuct wtsx_ucw	*ucw;
	stwuct memstick_host	*msh;
	stwuct memstick_wequest	*weq;

	stwuct mutex		host_mutex;
	stwuct wowk_stwuct	handwe_weq;
	stwuct dewayed_wowk	poww_cawd;

	u8			ssc_depth;
	unsigned int		cwock;
	int			powew_mode;
	unsigned chaw           ifmode;
	boow			eject;
	boow			system_suspending;
};

static inwine stwuct device *ms_dev(stwuct wtsx_usb_ms *host)
{
	wetuwn &(host->pdev->dev);
}

static inwine void ms_cweaw_ewwow(stwuct wtsx_usb_ms *host)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	wtsx_usb_ep0_wwite_wegistew(ucw, CAWD_STOP,
				  MS_STOP | MS_CWW_EWW,
				  MS_STOP | MS_CWW_EWW);

	wtsx_usb_cweaw_dma_eww(ucw);
	wtsx_usb_cweaw_fsm_eww(ucw);
}

#ifdef DEBUG

static void ms_pwint_debug_wegs(stwuct wtsx_usb_ms *host)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	u16 i;
	u8 *ptw;

	/* Pwint MS host intewnaw wegistews */
	wtsx_usb_init_cmd(ucw);

	/* MS_CFG to MS_INT_WEG */
	fow (i = 0xFD40; i <= 0xFD44; i++)
		wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, i, 0, 0);

	/* CAWD_SHAWE_MODE to CAWD_GPIO */
	fow (i = 0xFD51; i <= 0xFD56; i++)
		wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, i, 0, 0);

	/* CAWD_PUWW_CTWx */
	fow (i = 0xFD60; i <= 0xFD65; i++)
		wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, i, 0, 0);

	/* CAWD_DATA_SOUWCE, CAWD_SEWECT, CAWD_CWK_EN, CAWD_PWW_CTW */
	wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, CAWD_DATA_SOUWCE, 0, 0);
	wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, CAWD_SEWECT, 0, 0);
	wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, CAWD_CWK_EN, 0, 0);
	wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, CAWD_PWW_CTW, 0, 0);

	wtsx_usb_send_cmd(ucw, MODE_CW, 100);
	wtsx_usb_get_wsp(ucw, 21, 100);

	ptw = ucw->wsp_buf;
	fow (i = 0xFD40; i <= 0xFD44; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptw++));
	fow (i = 0xFD51; i <= 0xFD56; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptw++));
	fow (i = 0xFD60; i <= 0xFD65; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptw++));

	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CAWD_DATA_SOUWCE, *(ptw++));
	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CAWD_SEWECT, *(ptw++));
	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CAWD_CWK_EN, *(ptw++));
	dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", CAWD_PWW_CTW, *(ptw++));
}

#ewse

static void ms_pwint_debug_wegs(stwuct wtsx_usb_ms *host)
{
}

#endif

static int ms_puww_ctw_disabwe_wqfp48(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF, 0x95);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF, 0xA5);

	wetuwn wtsx_usb_send_cmd(ucw, MODE_C, 100);
}

static int ms_puww_ctw_disabwe_qfn24(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF, 0x65);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF, 0x95);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF, 0x56);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF, 0x59);

	wetuwn wtsx_usb_send_cmd(ucw, MODE_C, 100);
}

static int ms_puww_ctw_enabwe_wqfp48(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF, 0x95);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF, 0xA5);

	wetuwn wtsx_usb_send_cmd(ucw, MODE_C, 100);
}

static int ms_puww_ctw_enabwe_qfn24(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF, 0x65);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF, 0x95);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF, 0x55);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF, 0x59);

	wetuwn wtsx_usb_send_cmd(ucw, MODE_C, 100);
}

static int ms_powew_on(stwuct wtsx_usb_ms *host)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	int eww;

	dev_dbg(ms_dev(host), "%s\n", __func__);

	wtsx_usb_init_cmd(ucw);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_SEWECT, 0x07, MS_MOD_SEW);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_SHAWE_MODE,
			CAWD_SHAWE_MASK, CAWD_SHAWE_MS);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_CWK_EN,
			MS_CWK_EN, MS_CWK_EN);
	eww = wtsx_usb_send_cmd(ucw, MODE_C, 100);
	if (eww < 0)
		wetuwn eww;

	if (CHECK_PKG(ucw, WQFP48))
		eww = ms_puww_ctw_enabwe_wqfp48(ucw);
	ewse
		eww = ms_puww_ctw_enabwe_qfn24(ucw);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_usb_wwite_wegistew(ucw, CAWD_PWW_CTW,
			POWEW_MASK, PAWTIAW_POWEW_ON);
	if (eww)
		wetuwn eww;

	usweep_wange(800, 1000);

	wtsx_usb_init_cmd(ucw);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			POWEW_MASK, POWEW_ON);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);

	wetuwn wtsx_usb_send_cmd(ucw, MODE_C, 100);
}

static int ms_powew_off(stwuct wtsx_usb_ms *host)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	int eww;

	dev_dbg(ms_dev(host), "%s\n", __func__);

	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_CWK_EN, MS_CWK_EN, 0);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_OE, MS_OUTPUT_EN, 0);

	eww = wtsx_usb_send_cmd(ucw, MODE_C, 100);
	if (eww < 0)
		wetuwn eww;

	if (CHECK_PKG(ucw, WQFP48))
		wetuwn ms_puww_ctw_disabwe_wqfp48(ucw);

	wetuwn ms_puww_ctw_disabwe_qfn24(ucw);
}

static int ms_twansfew_data(stwuct wtsx_usb_ms *host, unsigned chaw data_diw,
		u8 tpc, u8 cfg, stwuct scattewwist *sg)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	int eww;
	unsigned int wength = sg->wength;
	u16 sec_cnt = (u16)(wength / 512);
	u8 twans_mode, dma_diw, fwag;
	unsigned int pipe;
	stwuct memstick_dev *cawd = host->msh->cawd;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x, data_diw = %s, wength = %d\n",
			__func__, tpc, (data_diw == WEAD) ? "WEAD" : "WWITE",
			wength);

	if (data_diw == WEAD) {
		fwag = MODE_CDIW;
		dma_diw = DMA_DIW_FWOM_CAWD;
		if (cawd->id.type != MEMSTICK_TYPE_PWO)
			twans_mode = MS_TM_NOWMAW_WEAD;
		ewse
			twans_mode = MS_TM_AUTO_WEAD;
		pipe = usb_wcvbuwkpipe(ucw->pusb_dev, EP_BUWK_IN);
	} ewse {
		fwag = MODE_CDOW;
		dma_diw = DMA_DIW_TO_CAWD;
		if (cawd->id.type != MEMSTICK_TYPE_PWO)
			twans_mode = MS_TM_NOWMAW_WWITE;
		ewse
			twans_mode = MS_TM_AUTO_WWITE;
		pipe = usb_sndbuwkpipe(ucw->pusb_dev, EP_BUWK_OUT);
	}

	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TPC, 0xFF, tpc);
	if (cawd->id.type == MEMSTICK_TYPE_PWO) {
		wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_SECTOW_CNT_H,
				0xFF, (u8)(sec_cnt >> 8));
		wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_SECTOW_CNT_W,
				0xFF, (u8)sec_cnt);
	}
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TWANS_CFG, 0xFF, cfg);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MC_DMA_TC3,
			0xFF, (u8)(wength >> 24));
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MC_DMA_TC2,
			0xFF, (u8)(wength >> 16));
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MC_DMA_TC1,
			0xFF, (u8)(wength >> 8));
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MC_DMA_TC0, 0xFF,
			(u8)wength);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MC_DMA_CTW,
			0x03 | DMA_PACK_SIZE_MASK, dma_diw | DMA_EN | DMA_512);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
			0x01, WING_BUFFEW);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TWANSFEW,
			0xFF, MS_TWANSFEW_STAWT | twans_mode);
	wtsx_usb_add_cmd(ucw, CHECK_WEG_CMD, MS_TWANSFEW,
			MS_TWANSFEW_END, MS_TWANSFEW_END);

	eww = wtsx_usb_send_cmd(ucw, fwag | STAGE_MS_STATUS, 100);
	if (eww)
		wetuwn eww;

	eww = wtsx_usb_twansfew_data(ucw, pipe, sg, wength,
			1, NUWW, 10000);
	if (eww)
		goto eww_out;

	eww = wtsx_usb_get_wsp(ucw, 3, 15000);
	if (eww)
		goto eww_out;

	if (ucw->wsp_buf[0] & MS_TWANSFEW_EWW ||
	    ucw->wsp_buf[1] & (MS_CWC16_EWW | MS_WDY_TIMEOUT)) {
		eww = -EIO;
		goto eww_out;
	}
	wetuwn 0;
eww_out:
	ms_cweaw_ewwow(host);
	wetuwn eww;
}

static int ms_wwite_bytes(stwuct wtsx_usb_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *int_weg)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	int eww, i;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	wtsx_usb_init_cmd(ucw);

	fow (i = 0; i < cnt; i++)
		wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD,
				PPBUF_BASE2 + i, 0xFF, data[i]);

	if (cnt % 2)
		wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD,
				PPBUF_BASE2 + i, 0xFF, 0xFF);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TPC, 0xFF, tpc);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TWANS_CFG, 0xFF, cfg);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
			0x01, PINGPONG_BUFFEW);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TWANSFEW,
			0xFF, MS_TWANSFEW_STAWT | MS_TM_WWITE_BYTES);
	wtsx_usb_add_cmd(ucw, CHECK_WEG_CMD, MS_TWANSFEW,
			MS_TWANSFEW_END, MS_TWANSFEW_END);
	wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, MS_TWANS_CFG, 0, 0);

	eww = wtsx_usb_send_cmd(ucw, MODE_CW, 100);
	if (eww)
		wetuwn eww;

	eww = wtsx_usb_get_wsp(ucw, 2, 5000);
	if (eww || (ucw->wsp_buf[0] & MS_TWANSFEW_EWW)) {
		u8 vaw;

		wtsx_usb_ep0_wead_wegistew(ucw, MS_TWANS_CFG, &vaw);
		dev_dbg(ms_dev(host), "MS_TWANS_CFG: 0x%02x\n", vaw);

		if (int_weg)
			*int_weg = vaw & 0x0F;

		ms_pwint_debug_wegs(host);

		ms_cweaw_ewwow(host);

		if (!(tpc & 0x08)) {
			if (vaw & MS_CWC16_EWW)
				wetuwn -EIO;
		} ewse {
			if (!(vaw & 0x80)) {
				if (vaw & (MS_INT_EWW | MS_INT_CMDNK))
					wetuwn -EIO;
			}
		}

		wetuwn -ETIMEDOUT;
	}

	if (int_weg)
		*int_weg = ucw->wsp_buf[1] & 0x0F;

	wetuwn 0;
}

static int ms_wead_bytes(stwuct wtsx_usb_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *int_weg)
{
	stwuct wtsx_ucw *ucw = host->ucw;
	int eww, i;
	u8 *ptw;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	wtsx_usb_init_cmd(ucw);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TPC, 0xFF, tpc);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TWANS_CFG, 0xFF, cfg);
	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
			0x01, PINGPONG_BUFFEW);

	wtsx_usb_add_cmd(ucw, WWITE_WEG_CMD, MS_TWANSFEW,
			0xFF, MS_TWANSFEW_STAWT | MS_TM_WEAD_BYTES);
	wtsx_usb_add_cmd(ucw, CHECK_WEG_CMD, MS_TWANSFEW,
			MS_TWANSFEW_END, MS_TWANSFEW_END);
	fow (i = 0; i < cnt - 1; i++)
		wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, PPBUF_BASE2 + i, 0, 0);
	if (cnt % 2)
		wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, PPBUF_BASE2 + cnt, 0, 0);
	ewse
		wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD,
				PPBUF_BASE2 + cnt - 1, 0, 0);

	wtsx_usb_add_cmd(ucw, WEAD_WEG_CMD, MS_TWANS_CFG, 0, 0);

	eww = wtsx_usb_send_cmd(ucw, MODE_CW, 100);
	if (eww)
		wetuwn eww;

	eww = wtsx_usb_get_wsp(ucw, cnt + 2, 5000);
	if (eww || (ucw->wsp_buf[0] & MS_TWANSFEW_EWW)) {
		u8 vaw;

		wtsx_usb_ep0_wead_wegistew(ucw, MS_TWANS_CFG, &vaw);
		dev_dbg(ms_dev(host), "MS_TWANS_CFG: 0x%02x\n", vaw);

		if (int_weg && (host->ifmode != MEMSTICK_SEWIAW))
			*int_weg = vaw & 0x0F;

		ms_pwint_debug_wegs(host);

		ms_cweaw_ewwow(host);

		if (!(tpc & 0x08)) {
			if (vaw & MS_CWC16_EWW)
				wetuwn -EIO;
		} ewse {
			if (!(vaw & 0x80)) {
				if (vaw & (MS_INT_EWW | MS_INT_CMDNK))
					wetuwn -EIO;
			}
		}

		wetuwn -ETIMEDOUT;
	}

	ptw = ucw->wsp_buf + 1;
	fow (i = 0; i < cnt; i++)
		data[i] = *ptw++;


	if (int_weg && (host->ifmode != MEMSTICK_SEWIAW))
		*int_weg = *ptw & 0x0F;

	wetuwn 0;
}

static int wtsx_usb_ms_issue_cmd(stwuct wtsx_usb_ms *host)
{
	stwuct memstick_wequest *weq = host->weq;
	int eww = 0;
	u8 cfg = 0, int_weg;

	dev_dbg(ms_dev(host), "%s\n", __func__);

	if (weq->need_cawd_int) {
		if (host->ifmode != MEMSTICK_SEWIAW)
			cfg = WAIT_INT;
	}

	if (weq->wong_data) {
		eww = ms_twansfew_data(host, weq->data_diw,
				weq->tpc, cfg, &(weq->sg));
	} ewse {
		if (weq->data_diw == WEAD)
			eww = ms_wead_bytes(host, weq->tpc, cfg,
					weq->data_wen, weq->data, &int_weg);
		ewse
			eww = ms_wwite_bytes(host, weq->tpc, cfg,
					weq->data_wen, weq->data, &int_weg);
	}
	if (eww < 0)
		wetuwn eww;

	if (weq->need_cawd_int) {
		if (host->ifmode == MEMSTICK_SEWIAW) {
			eww = ms_wead_bytes(host, MS_TPC_GET_INT,
					NO_WAIT_INT, 1, &weq->int_weg, NUWW);
			if (eww < 0)
				wetuwn eww;
		} ewse {

			if (int_weg & MS_INT_CMDNK)
				weq->int_weg |= MEMSTICK_INT_CMDNAK;
			if (int_weg & MS_INT_BWEQ)
				weq->int_weg |= MEMSTICK_INT_BWEQ;
			if (int_weg & MS_INT_EWW)
				weq->int_weg |= MEMSTICK_INT_EWW;
			if (int_weg & MS_INT_CED)
				weq->int_weg |= MEMSTICK_INT_CED;
		}
		dev_dbg(ms_dev(host), "int_weg: 0x%02x\n", weq->int_weg);
	}

	wetuwn 0;
}

static void wtsx_usb_ms_handwe_weq(stwuct wowk_stwuct *wowk)
{
	stwuct wtsx_usb_ms *host = containew_of(wowk,
			stwuct wtsx_usb_ms, handwe_weq);
	stwuct wtsx_ucw *ucw = host->ucw;
	stwuct memstick_host *msh = host->msh;
	int wc;

	if (!host->weq) {
		pm_wuntime_get_sync(ms_dev(host));
		do {
			wc = memstick_next_weq(msh, &host->weq);
			dev_dbg(ms_dev(host), "next weq %d\n", wc);

			if (!wc) {
				mutex_wock(&ucw->dev_mutex);

				if (wtsx_usb_cawd_excwusive_check(ucw,
							WTSX_USB_MS_CAWD))
					host->weq->ewwow = -EIO;
				ewse
					host->weq->ewwow =
						wtsx_usb_ms_issue_cmd(host);

				mutex_unwock(&ucw->dev_mutex);

				dev_dbg(ms_dev(host), "weq wesuwt %d\n",
						host->weq->ewwow);
			}
		} whiwe (!wc);
		pm_wuntime_put_sync(ms_dev(host));
	}

}

static void wtsx_usb_ms_wequest(stwuct memstick_host *msh)
{
	stwuct wtsx_usb_ms *host = memstick_pwiv(msh);

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	if (!host->eject)
		scheduwe_wowk(&host->handwe_weq);
}

static int wtsx_usb_ms_set_pawam(stwuct memstick_host *msh,
		enum memstick_pawam pawam, int vawue)
{
	stwuct wtsx_usb_ms *host = memstick_pwiv(msh);
	stwuct wtsx_ucw *ucw = host->ucw;
	unsigned int cwock = 0;
	u8 ssc_depth = 0;
	int eww;

	dev_dbg(ms_dev(host), "%s: pawam = %d, vawue = %d\n",
			__func__, pawam, vawue);

	pm_wuntime_get_sync(ms_dev(host));
	mutex_wock(&ucw->dev_mutex);

	eww = wtsx_usb_cawd_excwusive_check(ucw, WTSX_USB_MS_CAWD);
	if (eww)
		goto out;

	switch (pawam) {
	case MEMSTICK_POWEW:
		if (vawue == host->powew_mode)
			bweak;

		if (vawue == MEMSTICK_POWEW_ON) {
			pm_wuntime_get_nowesume(ms_dev(host));
			eww = ms_powew_on(host);
			if (eww)
				pm_wuntime_put_noidwe(ms_dev(host));
		} ewse if (vawue == MEMSTICK_POWEW_OFF) {
			eww = ms_powew_off(host);
			if (!eww)
				pm_wuntime_put_noidwe(ms_dev(host));
		} ewse
			eww = -EINVAW;
		if (!eww)
			host->powew_mode = vawue;
		bweak;

	case MEMSTICK_INTEWFACE:
		if (vawue == MEMSTICK_SEWIAW) {
			cwock = 19000000;
			ssc_depth = SSC_DEPTH_512K;
			eww = wtsx_usb_wwite_wegistew(ucw, MS_CFG, 0x5A,
				       MS_BUS_WIDTH_1 | PUSH_TIME_DEFAUWT);
			if (eww < 0)
				bweak;
		} ewse if (vawue == MEMSTICK_PAW4) {
			cwock = 39000000;
			ssc_depth = SSC_DEPTH_1M;

			eww = wtsx_usb_wwite_wegistew(ucw, MS_CFG, 0x5A,
					MS_BUS_WIDTH_4 | PUSH_TIME_ODD |
					MS_NO_CHECK_INT);
			if (eww < 0)
				bweak;
		} ewse {
			eww = -EINVAW;
			bweak;
		}

		eww = wtsx_usb_switch_cwock(ucw, cwock,
				ssc_depth, fawse, twue, fawse);
		if (eww < 0) {
			dev_dbg(ms_dev(host), "switch cwock faiwed\n");
			bweak;
		}

		host->ssc_depth = ssc_depth;
		host->cwock = cwock;
		host->ifmode = vawue;
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
out:
	mutex_unwock(&ucw->dev_mutex);
	pm_wuntime_put_sync(ms_dev(host));

	/* powew-on deway */
	if (pawam == MEMSTICK_POWEW && vawue == MEMSTICK_POWEW_ON) {
		usweep_wange(10000, 12000);

		if (!host->eject)
			scheduwe_dewayed_wowk(&host->poww_cawd, 100);
	}

	dev_dbg(ms_dev(host), "%s: wetuwn = %d\n", __func__, eww);
	wetuwn eww;
}

#ifdef CONFIG_PM_SWEEP
static int wtsx_usb_ms_suspend(stwuct device *dev)
{
	stwuct wtsx_usb_ms *host = dev_get_dwvdata(dev);
	stwuct memstick_host *msh = host->msh;

	/* Since we use wtsx_usb's wesume cawwback to wuntime wesume its
	 * chiwdwen to impwement wemote wakeup signawing, this causes
	 * wtsx_usb_ms' wuntime wesume cawwback wuns aftew its suspend
	 * cawwback:
	 * wtsx_usb_ms_suspend()
	 * wtsx_usb_wesume()
	 *   -> wtsx_usb_ms_wuntime_wesume()
	 *     -> memstick_detect_change()
	 *
	 * wtsx_usb_suspend()
	 *
	 * To avoid this, skip wuntime wesume/suspend if system suspend is
	 * undewway.
	 */

	host->system_suspending = twue;
	memstick_suspend_host(msh);

	wetuwn 0;
}

static int wtsx_usb_ms_wesume(stwuct device *dev)
{
	stwuct wtsx_usb_ms *host = dev_get_dwvdata(dev);
	stwuct memstick_host *msh = host->msh;

	memstick_wesume_host(msh);
	host->system_suspending = fawse;

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int wtsx_usb_ms_wuntime_suspend(stwuct device *dev)
{
	stwuct wtsx_usb_ms *host = dev_get_dwvdata(dev);

	if (host->system_suspending)
		wetuwn 0;

	if (host->msh->cawd || host->powew_mode != MEMSTICK_POWEW_OFF)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int wtsx_usb_ms_wuntime_wesume(stwuct device *dev)
{
	stwuct wtsx_usb_ms *host = dev_get_dwvdata(dev);


	if (host->system_suspending)
		wetuwn 0;

	memstick_detect_change(host->msh);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops wtsx_usb_ms_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wtsx_usb_ms_suspend, wtsx_usb_ms_wesume)
	SET_WUNTIME_PM_OPS(wtsx_usb_ms_wuntime_suspend, wtsx_usb_ms_wuntime_wesume, NUWW)
};


static void wtsx_usb_ms_poww_cawd(stwuct wowk_stwuct *wowk)
{
	stwuct wtsx_usb_ms *host = containew_of(wowk, stwuct wtsx_usb_ms,
			poww_cawd.wowk);
	stwuct wtsx_ucw *ucw = host->ucw;
	int eww;
	u8 vaw;

	if (host->eject || host->powew_mode != MEMSTICK_POWEW_ON)
		wetuwn;

	pm_wuntime_get_sync(ms_dev(host));
	mutex_wock(&ucw->dev_mutex);

	/* Check pending MS cawd changes */
	eww = wtsx_usb_wead_wegistew(ucw, CAWD_INT_PEND, &vaw);
	if (eww) {
		mutex_unwock(&ucw->dev_mutex);
		goto poww_again;
	}

	/* Cweaw the pending */
	wtsx_usb_wwite_wegistew(ucw, CAWD_INT_PEND,
			XD_INT | MS_INT | SD_INT,
			XD_INT | MS_INT | SD_INT);

	mutex_unwock(&ucw->dev_mutex);

	if (vaw & MS_INT) {
		dev_dbg(ms_dev(host), "MS swot change detected\n");
		memstick_detect_change(host->msh);
	}

poww_again:
	pm_wuntime_put_sync(ms_dev(host));

	if (!host->eject && host->powew_mode == MEMSTICK_POWEW_ON)
		scheduwe_dewayed_wowk(&host->poww_cawd, 100);
}

static int wtsx_usb_ms_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct memstick_host *msh;
	stwuct wtsx_usb_ms *host;
	stwuct wtsx_ucw *ucw;
	int eww;

	ucw = usb_get_intfdata(to_usb_intewface(pdev->dev.pawent));
	if (!ucw)
		wetuwn -ENXIO;

	dev_dbg(&(pdev->dev),
			"Weawtek USB Memstick contwowwew found\n");

	msh = memstick_awwoc_host(sizeof(*host), &pdev->dev);
	if (!msh)
		wetuwn -ENOMEM;

	host = memstick_pwiv(msh);
	host->ucw = ucw;
	host->msh = msh;
	host->pdev = pdev;
	host->powew_mode = MEMSTICK_POWEW_OFF;
	pwatfowm_set_dwvdata(pdev, host);

	mutex_init(&host->host_mutex);
	INIT_WOWK(&host->handwe_weq, wtsx_usb_ms_handwe_weq);

	INIT_DEWAYED_WOWK(&host->poww_cawd, wtsx_usb_ms_poww_cawd);

	msh->wequest = wtsx_usb_ms_wequest;
	msh->set_pawam = wtsx_usb_ms_set_pawam;
	msh->caps = MEMSTICK_CAP_PAW4;

	pm_wuntime_get_nowesume(ms_dev(host));
	pm_wuntime_set_active(ms_dev(host));
	pm_wuntime_enabwe(ms_dev(host));

	eww = memstick_add_host(msh);
	if (eww)
		goto eww_out;

	pm_wuntime_put(ms_dev(host));

	wetuwn 0;
eww_out:
	pm_wuntime_disabwe(ms_dev(host));
	pm_wuntime_put_noidwe(ms_dev(host));
	memstick_fwee_host(msh);
	wetuwn eww;
}

static int wtsx_usb_ms_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wtsx_usb_ms *host = pwatfowm_get_dwvdata(pdev);
	stwuct memstick_host *msh = host->msh;
	int eww;

	host->eject = twue;
	cancew_wowk_sync(&host->handwe_weq);

	mutex_wock(&host->host_mutex);
	if (host->weq) {
		dev_dbg(ms_dev(host),
			"%s: Contwowwew wemoved duwing twansfew\n",
			dev_name(&msh->dev));
		host->weq->ewwow = -ENOMEDIUM;
		do {
			eww = memstick_next_weq(msh, &host->weq);
			if (!eww)
				host->weq->ewwow = -ENOMEDIUM;
		} whiwe (!eww);
	}
	mutex_unwock(&host->host_mutex);

	/* Bawance possibwe unbawanced usage count
	 * e.g. unconditionaw moduwe wemovaw
	 */
	if (pm_wuntime_active(ms_dev(host)))
		pm_wuntime_put(ms_dev(host));

	pm_wuntime_disabwe(ms_dev(host));
	memstick_wemove_host(msh);
	dev_dbg(ms_dev(host),
		": Weawtek USB Memstick contwowwew has been wemoved\n");
	memstick_fwee_host(msh);
	pwatfowm_set_dwvdata(pdev, NUWW);

	wetuwn 0;
}

static stwuct pwatfowm_device_id wtsx_usb_ms_ids[] = {
	{
		.name = "wtsx_usb_ms",
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(pwatfowm, wtsx_usb_ms_ids);

static stwuct pwatfowm_dwivew wtsx_usb_ms_dwivew = {
	.pwobe		= wtsx_usb_ms_dwv_pwobe,
	.wemove		= wtsx_usb_ms_dwv_wemove,
	.id_tabwe       = wtsx_usb_ms_ids,
	.dwivew		= {
		.name	= "wtsx_usb_ms",
		.pm	= &wtsx_usb_ms_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wtsx_usb_ms_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wogew Tseng <wogewabwe@weawtek.com>");
MODUWE_DESCWIPTION("Weawtek USB Memstick Cawd Host Dwivew");
