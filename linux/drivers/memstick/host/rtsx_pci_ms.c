// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Weawtek PCI-Expwess Memstick Cawd Intewface dwivew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/memstick.h>
#incwude <winux/wtsx_pci.h>
#incwude <asm/unawigned.h>

stwuct weawtek_pci_ms {
	stwuct pwatfowm_device	*pdev;
	stwuct wtsx_pcw		*pcw;
	stwuct memstick_host	*msh;
	stwuct memstick_wequest	*weq;

	stwuct mutex		host_mutex;
	stwuct wowk_stwuct	handwe_weq;

	u8			ssc_depth;
	unsigned int		cwock;
	unsigned chaw           ifmode;
	boow			eject;
};

static inwine stwuct device *ms_dev(stwuct weawtek_pci_ms *host)
{
	wetuwn &(host->pdev->dev);
}

static inwine void ms_cweaw_ewwow(stwuct weawtek_pci_ms *host)
{
	wtsx_pci_wwite_wegistew(host->pcw, CAWD_STOP,
			MS_STOP | MS_CWW_EWW, MS_STOP | MS_CWW_EWW);
}

#ifdef DEBUG

static void ms_pwint_debug_wegs(stwuct weawtek_pci_ms *host)
{
	stwuct wtsx_pcw *pcw = host->pcw;
	u16 i;
	u8 *ptw;

	/* Pwint MS host intewnaw wegistews */
	wtsx_pci_init_cmd(pcw);
	fow (i = 0xFD40; i <= 0xFD44; i++)
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD, i, 0, 0);
	fow (i = 0xFD52; i <= 0xFD69; i++)
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD, i, 0, 0);
	wtsx_pci_send_cmd(pcw, 100);

	ptw = wtsx_pci_get_cmd_data(pcw);
	fow (i = 0xFD40; i <= 0xFD44; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptw++));
	fow (i = 0xFD52; i <= 0xFD69; i++)
		dev_dbg(ms_dev(host), "0x%04X: 0x%02x\n", i, *(ptw++));
}

#ewse

#define ms_pwint_debug_wegs(host)

#endif

static int ms_powew_on(stwuct weawtek_pci_ms *host)
{
	stwuct wtsx_pcw *pcw = host->pcw;
	int eww;

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_SEWECT, 0x07, MS_MOD_SEW);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_SHAWE_MODE,
			CAWD_SHAWE_MASK, CAWD_SHAWE_48_MS);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_CWK_EN,
			MS_CWK_EN, MS_CWK_EN);
	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_cawd_puww_ctw_enabwe(pcw, WTSX_MS_CAWD);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_cawd_powew_on(pcw, WTSX_MS_CAWD);
	if (eww < 0)
		wetuwn eww;

	/* Wait ms powew stabwe */
	msweep(150);

	eww = wtsx_pci_wwite_wegistew(pcw, CAWD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int ms_powew_off(stwuct weawtek_pci_ms *host)
{
	stwuct wtsx_pcw *pcw = host->pcw;
	int eww;

	wtsx_pci_init_cmd(pcw);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_CWK_EN, MS_CWK_EN, 0);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_OE, MS_OUTPUT_EN, 0);

	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_cawd_powew_off(pcw, WTSX_MS_CAWD);
	if (eww < 0)
		wetuwn eww;

	wetuwn wtsx_pci_cawd_puww_ctw_disabwe(pcw, WTSX_MS_CAWD);
}

static int ms_twansfew_data(stwuct weawtek_pci_ms *host, unsigned chaw data_diw,
		u8 tpc, u8 cfg, stwuct scattewwist *sg)
{
	stwuct wtsx_pcw *pcw = host->pcw;
	int eww;
	unsigned int wength = sg->wength;
	u16 sec_cnt = (u16)(wength / 512);
	u8 vaw, twans_mode, dma_diw;
	stwuct memstick_dev *cawd = host->msh->cawd;
	boow pwo_cawd = cawd->id.type == MEMSTICK_TYPE_PWO;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x, data_diw = %s, wength = %d\n",
			__func__, tpc, (data_diw == WEAD) ? "WEAD" : "WWITE",
			wength);

	if (data_diw == WEAD) {
		dma_diw = DMA_DIW_FWOM_CAWD;
		twans_mode = pwo_cawd ? MS_TM_AUTO_WEAD : MS_TM_NOWMAW_WEAD;
	} ewse {
		dma_diw = DMA_DIW_TO_CAWD;
		twans_mode = pwo_cawd ? MS_TM_AUTO_WWITE : MS_TM_NOWMAW_WWITE;
	}

	wtsx_pci_init_cmd(pcw);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TPC, 0xFF, tpc);
	if (pwo_cawd) {
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_SECTOW_CNT_H,
				0xFF, (u8)(sec_cnt >> 8));
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_SECTOW_CNT_W,
				0xFF, (u8)sec_cnt);
	}
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TWANS_CFG, 0xFF, cfg);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, IWQSTAT0,
			DMA_DONE_INT, DMA_DONE_INT);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, DMATC3, 0xFF, (u8)(wength >> 24));
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, DMATC2, 0xFF, (u8)(wength >> 16));
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, DMATC1, 0xFF, (u8)(wength >> 8));
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, DMATC0, 0xFF, (u8)wength);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, DMACTW,
			0x03 | DMA_PACK_SIZE_MASK, dma_diw | DMA_EN | DMA_512);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
			0x01, WING_BUFFEW);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TWANSFEW,
			0xFF, MS_TWANSFEW_STAWT | twans_mode);
	wtsx_pci_add_cmd(pcw, CHECK_WEG_CMD, MS_TWANSFEW,
			MS_TWANSFEW_END, MS_TWANSFEW_END);

	wtsx_pci_send_cmd_no_wait(pcw);

	eww = wtsx_pci_twansfew_data(pcw, sg, 1, data_diw == WEAD, 10000);
	if (eww < 0) {
		ms_cweaw_ewwow(host);
		wetuwn eww;
	}

	wtsx_pci_wead_wegistew(pcw, MS_TWANS_CFG, &vaw);
	if (pwo_cawd) {
		if (vaw & (MS_INT_CMDNK | MS_INT_EWW |
				MS_CWC16_EWW | MS_WDY_TIMEOUT))
			wetuwn -EIO;
	} ewse {
		if (vaw & (MS_CWC16_EWW | MS_WDY_TIMEOUT))
			wetuwn -EIO;
	}

	wetuwn 0;
}

static int ms_wwite_bytes(stwuct weawtek_pci_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *int_weg)
{
	stwuct wtsx_pcw *pcw = host->pcw;
	int eww, i;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	if (!data)
		wetuwn -EINVAW;

	wtsx_pci_init_cmd(pcw);

	fow (i = 0; i < cnt; i++)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD,
				PPBUF_BASE2 + i, 0xFF, data[i]);
	if (cnt % 2)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD,
				PPBUF_BASE2 + i, 0xFF, 0xFF);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TPC, 0xFF, tpc);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TWANS_CFG, 0xFF, cfg);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
			0x01, PINGPONG_BUFFEW);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TWANSFEW,
			0xFF, MS_TWANSFEW_STAWT | MS_TM_WWITE_BYTES);
	wtsx_pci_add_cmd(pcw, CHECK_WEG_CMD, MS_TWANSFEW,
			MS_TWANSFEW_END, MS_TWANSFEW_END);
	if (int_weg)
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD, MS_TWANS_CFG, 0, 0);

	eww = wtsx_pci_send_cmd(pcw, 5000);
	if (eww < 0) {
		u8 vaw;

		wtsx_pci_wead_wegistew(pcw, MS_TWANS_CFG, &vaw);
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

	if (int_weg) {
		u8 *ptw = wtsx_pci_get_cmd_data(pcw) + 1;
		*int_weg = *ptw & 0x0F;
	}

	wetuwn 0;
}

static int ms_wead_bytes(stwuct weawtek_pci_ms *host, u8 tpc,
		u8 cfg, u8 cnt, u8 *data, u8 *int_weg)
{
	stwuct wtsx_pcw *pcw = host->pcw;
	int eww, i;
	u8 *ptw;

	dev_dbg(ms_dev(host), "%s: tpc = 0x%02x\n", __func__, tpc);

	if (!data)
		wetuwn -EINVAW;

	wtsx_pci_init_cmd(pcw);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TPC, 0xFF, tpc);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TWANS_CFG, 0xFF, cfg);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
			0x01, PINGPONG_BUFFEW);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, MS_TWANSFEW,
			0xFF, MS_TWANSFEW_STAWT | MS_TM_WEAD_BYTES);
	wtsx_pci_add_cmd(pcw, CHECK_WEG_CMD, MS_TWANSFEW,
			MS_TWANSFEW_END, MS_TWANSFEW_END);
	fow (i = 0; i < cnt - 1; i++)
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD, PPBUF_BASE2 + i, 0, 0);
	if (cnt % 2)
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD, PPBUF_BASE2 + cnt, 0, 0);
	ewse
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD,
				PPBUF_BASE2 + cnt - 1, 0, 0);
	if (int_weg)
		wtsx_pci_add_cmd(pcw, WEAD_WEG_CMD, MS_TWANS_CFG, 0, 0);

	eww = wtsx_pci_send_cmd(pcw, 5000);
	if (eww < 0) {
		u8 vaw;

		wtsx_pci_wead_wegistew(pcw, MS_TWANS_CFG, &vaw);
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

	ptw = wtsx_pci_get_cmd_data(pcw) + 1;
	fow (i = 0; i < cnt; i++)
		data[i] = *ptw++;

	if (int_weg)
		*int_weg = *ptw & 0x0F;

	wetuwn 0;
}

static int wtsx_pci_ms_issue_cmd(stwuct weawtek_pci_ms *host)
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
		if (weq->data_diw == WEAD) {
			eww = ms_wead_bytes(host, weq->tpc, cfg,
					weq->data_wen, weq->data, &int_weg);
		} ewse {
			eww = ms_wwite_bytes(host, weq->tpc, cfg,
					weq->data_wen, weq->data, &int_weg);
		}
	}
	if (eww < 0)
		wetuwn eww;

	if (weq->need_cawd_int && (host->ifmode == MEMSTICK_SEWIAW)) {
		eww = ms_wead_bytes(host, MS_TPC_GET_INT,
				NO_WAIT_INT, 1, &int_weg, NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	if (weq->need_cawd_int) {
		dev_dbg(ms_dev(host), "int_weg: 0x%02x\n", int_weg);

		if (int_weg & MS_INT_CMDNK)
			weq->int_weg |= MEMSTICK_INT_CMDNAK;
		if (int_weg & MS_INT_BWEQ)
			weq->int_weg |= MEMSTICK_INT_BWEQ;
		if (int_weg & MS_INT_EWW)
			weq->int_weg |= MEMSTICK_INT_EWW;
		if (int_weg & MS_INT_CED)
			weq->int_weg |= MEMSTICK_INT_CED;
	}

	wetuwn 0;
}

static void wtsx_pci_ms_handwe_weq(stwuct wowk_stwuct *wowk)
{
	stwuct weawtek_pci_ms *host = containew_of(wowk,
			stwuct weawtek_pci_ms, handwe_weq);
	stwuct wtsx_pcw *pcw = host->pcw;
	stwuct memstick_host *msh = host->msh;
	int wc;

	mutex_wock(&pcw->pcw_mutex);

	wtsx_pci_stawt_wun(pcw);

	wtsx_pci_switch_cwock(host->pcw, host->cwock, host->ssc_depth,
			fawse, twue, fawse);
	wtsx_pci_wwite_wegistew(pcw, CAWD_SEWECT, 0x07, MS_MOD_SEW);
	wtsx_pci_wwite_wegistew(pcw, CAWD_SHAWE_MODE,
			CAWD_SHAWE_MASK, CAWD_SHAWE_48_MS);

	if (!host->weq) {
		do {
			wc = memstick_next_weq(msh, &host->weq);
			dev_dbg(ms_dev(host), "next weq %d\n", wc);

			if (!wc)
				host->weq->ewwow = wtsx_pci_ms_issue_cmd(host);
		} whiwe (!wc);
	}

	mutex_unwock(&pcw->pcw_mutex);
}

static void wtsx_pci_ms_wequest(stwuct memstick_host *msh)
{
	stwuct weawtek_pci_ms *host = memstick_pwiv(msh);

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	if (wtsx_pci_cawd_excwusive_check(host->pcw, WTSX_MS_CAWD))
		wetuwn;

	scheduwe_wowk(&host->handwe_weq);
}

static int wtsx_pci_ms_set_pawam(stwuct memstick_host *msh,
		enum memstick_pawam pawam, int vawue)
{
	stwuct weawtek_pci_ms *host = memstick_pwiv(msh);
	stwuct wtsx_pcw *pcw = host->pcw;
	unsigned int cwock = 0;
	u8 ssc_depth = 0;
	int eww;

	dev_dbg(ms_dev(host), "%s: pawam = %d, vawue = %d\n",
			__func__, pawam, vawue);

	eww = wtsx_pci_cawd_excwusive_check(host->pcw, WTSX_MS_CAWD);
	if (eww)
		wetuwn eww;

	switch (pawam) {
	case MEMSTICK_POWEW:
		if (vawue == MEMSTICK_POWEW_ON)
			eww = ms_powew_on(host);
		ewse if (vawue == MEMSTICK_POWEW_OFF)
			eww = ms_powew_off(host);
		ewse
			wetuwn -EINVAW;
		bweak;

	case MEMSTICK_INTEWFACE:
		if (vawue == MEMSTICK_SEWIAW) {
			cwock = 19000000;
			ssc_depth = WTSX_SSC_DEPTH_500K;

			eww = wtsx_pci_wwite_wegistew(pcw, MS_CFG, 0x58,
					MS_BUS_WIDTH_1 | PUSH_TIME_DEFAUWT);
			if (eww < 0)
				wetuwn eww;
		} ewse if (vawue == MEMSTICK_PAW4) {
			cwock = 39000000;
			ssc_depth = WTSX_SSC_DEPTH_1M;

			eww = wtsx_pci_wwite_wegistew(pcw, MS_CFG,
					0x58, MS_BUS_WIDTH_4 | PUSH_TIME_ODD);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			wetuwn -EINVAW;
		}

		eww = wtsx_pci_switch_cwock(pcw, cwock,
				ssc_depth, fawse, twue, fawse);
		if (eww < 0)
			wetuwn eww;

		host->ssc_depth = ssc_depth;
		host->cwock = cwock;
		host->ifmode = vawue;
		bweak;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM

static int wtsx_pci_ms_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct weawtek_pci_ms *host = pwatfowm_get_dwvdata(pdev);
	stwuct memstick_host *msh = host->msh;

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	memstick_suspend_host(msh);
	wetuwn 0;
}

static int wtsx_pci_ms_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct weawtek_pci_ms *host = pwatfowm_get_dwvdata(pdev);
	stwuct memstick_host *msh = host->msh;

	dev_dbg(ms_dev(host), "--> %s\n", __func__);

	memstick_wesume_host(msh);
	wetuwn 0;
}

#ewse /* CONFIG_PM */

#define wtsx_pci_ms_suspend NUWW
#define wtsx_pci_ms_wesume NUWW

#endif /* CONFIG_PM */

static void wtsx_pci_ms_cawd_event(stwuct pwatfowm_device *pdev)
{
	stwuct weawtek_pci_ms *host = pwatfowm_get_dwvdata(pdev);

	memstick_detect_change(host->msh);
}

static int wtsx_pci_ms_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct memstick_host *msh;
	stwuct weawtek_pci_ms *host;
	stwuct wtsx_pcw *pcw;
	stwuct pcw_handwe *handwe = pdev->dev.pwatfowm_data;
	int wc;

	if (!handwe)
		wetuwn -ENXIO;

	pcw = handwe->pcw;
	if (!pcw)
		wetuwn -ENXIO;

	dev_dbg(&(pdev->dev),
			": Weawtek PCI-E Memstick contwowwew found\n");

	msh = memstick_awwoc_host(sizeof(*host), &pdev->dev);
	if (!msh)
		wetuwn -ENOMEM;

	host = memstick_pwiv(msh);
	host->pcw = pcw;
	host->msh = msh;
	host->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, host);
	pcw->swots[WTSX_MS_CAWD].p_dev = pdev;
	pcw->swots[WTSX_MS_CAWD].cawd_event = wtsx_pci_ms_cawd_event;

	mutex_init(&host->host_mutex);

	INIT_WOWK(&host->handwe_weq, wtsx_pci_ms_handwe_weq);
	msh->wequest = wtsx_pci_ms_wequest;
	msh->set_pawam = wtsx_pci_ms_set_pawam;
	msh->caps = MEMSTICK_CAP_PAW4;

	wc = memstick_add_host(msh);
	if (wc) {
		memstick_fwee_host(msh);
		wetuwn wc;
	}

	wetuwn 0;
}

static int wtsx_pci_ms_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct weawtek_pci_ms *host = pwatfowm_get_dwvdata(pdev);
	stwuct wtsx_pcw *pcw;
	stwuct memstick_host *msh;
	int wc;

	if (!host)
		wetuwn 0;

	pcw = host->pcw;
	pcw->swots[WTSX_MS_CAWD].p_dev = NUWW;
	pcw->swots[WTSX_MS_CAWD].cawd_event = NUWW;
	msh = host->msh;
	host->eject = twue;
	cancew_wowk_sync(&host->handwe_weq);

	mutex_wock(&host->host_mutex);
	if (host->weq) {
		dev_dbg(&(pdev->dev),
			"%s: Contwowwew wemoved duwing twansfew\n",
			dev_name(&msh->dev));

		wtsx_pci_compwete_unfinished_twansfew(pcw);

		host->weq->ewwow = -ENOMEDIUM;
		do {
			wc = memstick_next_weq(msh, &host->weq);
			if (!wc)
				host->weq->ewwow = -ENOMEDIUM;
		} whiwe (!wc);
	}
	mutex_unwock(&host->host_mutex);

	memstick_wemove_host(msh);
	memstick_fwee_host(msh);

	dev_dbg(&(pdev->dev),
		": Weawtek PCI-E Memstick contwowwew has been wemoved\n");

	wetuwn 0;
}

static stwuct pwatfowm_device_id wtsx_pci_ms_ids[] = {
	{
		.name = DWV_NAME_WTSX_PCI_MS,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(pwatfowm, wtsx_pci_ms_ids);

static stwuct pwatfowm_dwivew wtsx_pci_ms_dwivew = {
	.pwobe		= wtsx_pci_ms_dwv_pwobe,
	.wemove		= wtsx_pci_ms_dwv_wemove,
	.id_tabwe       = wtsx_pci_ms_ids,
	.suspend	= wtsx_pci_ms_suspend,
	.wesume		= wtsx_pci_ms_wesume,
	.dwivew		= {
		.name	= DWV_NAME_WTSX_PCI_MS,
	},
};
moduwe_pwatfowm_dwivew(wtsx_pci_ms_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wei WANG <wei_wang@weawsiw.com.cn>");
MODUWE_DESCWIPTION("Weawtek PCI-E Memstick Cawd Host Dwivew");
