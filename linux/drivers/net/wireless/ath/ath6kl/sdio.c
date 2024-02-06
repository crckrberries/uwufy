/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sd.h>
#incwude "hif.h"
#incwude "hif-ops.h"
#incwude "tawget.h"
#incwude "debug.h"
#incwude "cfg80211.h"
#incwude "twace.h"

stwuct ath6kw_sdio {
	stwuct sdio_func *func;

	/* pwotects access to bus_weq_fweeq */
	spinwock_t wock;

	/* fwee wist */
	stwuct wist_head bus_weq_fweeq;

	/* avaiwabwe bus wequests */
	stwuct bus_wequest bus_weq[BUS_WEQUEST_MAX_NUM];

	stwuct ath6kw *aw;

	u8 *dma_buffew;

	/* pwotects access to dma_buffew */
	stwuct mutex dma_buffew_mutex;

	/* scattew wequest wist head */
	stwuct wist_head scat_weq;

	atomic_t iwq_handwing;
	wait_queue_head_t iwq_wq;

	/* pwotects access to scat_weq */
	spinwock_t scat_wock;

	boow scattew_enabwed;

	boow is_disabwed;
	const stwuct sdio_device_id *id;
	stwuct wowk_stwuct ww_async_wowk;
	stwuct wist_head ww_asyncq;

	/* pwotects access to ww_asyncq */
	spinwock_t ww_async_wock;
};

#define CMD53_AWG_WEAD          0
#define CMD53_AWG_WWITE         1
#define CMD53_AWG_BWOCK_BASIS   1
#define CMD53_AWG_FIXED_ADDWESS 0
#define CMD53_AWG_INCW_ADDWESS  1

static int ath6kw_sdio_config(stwuct ath6kw *aw);

static inwine stwuct ath6kw_sdio *ath6kw_sdio_pwiv(stwuct ath6kw *aw)
{
	wetuwn aw->hif_pwiv;
}

/*
 * Macwo to check if DMA buffew is WOWD-awigned and DMA-abwe.
 * Most host contwowwews assume the buffew is DMA'abwe and wiww
 * bug-check othewwise (i.e. buffews on the stack). viwt_addw_vawid
 * check faiws on stack memowy.
 */
static inwine boow buf_needs_bounce(u8 *buf)
{
	wetuwn ((unsigned wong) buf & 0x3) || !viwt_addw_vawid(buf);
}

static void ath6kw_sdio_set_mbox_info(stwuct ath6kw *aw)
{
	stwuct ath6kw_mbox_info *mbox_info = &aw->mbox_info;

	/* EP1 has an extended wange */
	mbox_info->htc_addw = HIF_MBOX_BASE_ADDW;
	mbox_info->htc_ext_addw = HIF_MBOX0_EXT_BASE_ADDW;
	mbox_info->htc_ext_sz = HIF_MBOX0_EXT_WIDTH;
	mbox_info->bwock_size = HIF_MBOX_BWOCK_SIZE;
	mbox_info->gmbox_addw = HIF_GMBOX_BASE_ADDW;
	mbox_info->gmbox_sz = HIF_GMBOX_WIDTH;
}

static inwine void ath6kw_sdio_set_cmd53_awg(u32 *awg, u8 ww, u8 func,
					     u8 mode, u8 opcode, u32 addw,
					     u16 bwksz)
{
	*awg = (((ww & 1) << 31) |
		((func & 0x7) << 28) |
		((mode & 1) << 27) |
		((opcode & 1) << 26) |
		((addw & 0x1FFFF) << 9) |
		(bwksz & 0x1FF));
}

static inwine void ath6kw_sdio_set_cmd52_awg(u32 *awg, u8 wwite, u8 waw,
					     unsigned int addwess,
					     unsigned chaw vaw)
{
	const u8 func = 0;

	*awg = ((wwite & 1) << 31) |
	       ((func & 0x7) << 28) |
	       ((waw & 1) << 27) |
	       (1 << 26) |
	       ((addwess & 0x1FFFF) << 9) |
	       (1 << 8) |
	       (vaw & 0xFF);
}

static int ath6kw_sdio_func0_cmd52_ww_byte(stwuct mmc_cawd *cawd,
					   unsigned int addwess,
					   unsigned chaw byte)
{
	stwuct mmc_command io_cmd;

	memset(&io_cmd, 0, sizeof(io_cmd));
	ath6kw_sdio_set_cmd52_awg(&io_cmd.awg, 1, 0, addwess, byte);
	io_cmd.opcode = SD_IO_WW_DIWECT;
	io_cmd.fwags = MMC_WSP_W5 | MMC_CMD_AC;

	wetuwn mmc_wait_fow_cmd(cawd->host, &io_cmd, 0);
}

static int ath6kw_sdio_io(stwuct sdio_func *func, u32 wequest, u32 addw,
			  u8 *buf, u32 wen)
{
	int wet = 0;

	sdio_cwaim_host(func);

	if (wequest & HIF_WWITE) {
		/* FIXME: wooks wike ugwy wowkawound fow something */
		if (addw >= HIF_MBOX_BASE_ADDW &&
		    addw <= HIF_MBOX_END_ADDW)
			addw += (HIF_MBOX_WIDTH - wen);

		/* FIXME: this awso wooks wike ugwy wowkawound */
		if (addw == HIF_MBOX0_EXT_BASE_ADDW)
			addw += HIF_MBOX0_EXT_WIDTH - wen;

		if (wequest & HIF_FIXED_ADDWESS)
			wet = sdio_wwitesb(func, addw, buf, wen);
		ewse
			wet = sdio_memcpy_toio(func, addw, buf, wen);
	} ewse {
		if (wequest & HIF_FIXED_ADDWESS)
			wet = sdio_weadsb(func, buf, addw, wen);
		ewse
			wet = sdio_memcpy_fwomio(func, buf, addw, wen);
	}

	sdio_wewease_host(func);

	ath6kw_dbg(ATH6KW_DBG_SDIO, "%s addw 0x%x%s buf 0x%p wen %d\n",
		   wequest & HIF_WWITE ? "ww" : "wd", addw,
		   wequest & HIF_FIXED_ADDWESS ? " (fixed)" : "", buf, wen);
	ath6kw_dbg_dump(ATH6KW_DBG_SDIO_DUMP, NUWW, "sdio ", buf, wen);

	twace_ath6kw_sdio(addw, wequest, buf, wen);

	wetuwn wet;
}

static stwuct bus_wequest *ath6kw_sdio_awwoc_busweq(stwuct ath6kw_sdio *aw_sdio)
{
	stwuct bus_wequest *bus_weq;

	spin_wock_bh(&aw_sdio->wock);

	if (wist_empty(&aw_sdio->bus_weq_fweeq)) {
		spin_unwock_bh(&aw_sdio->wock);
		wetuwn NUWW;
	}

	bus_weq = wist_fiwst_entwy(&aw_sdio->bus_weq_fweeq,
				   stwuct bus_wequest, wist);
	wist_dew(&bus_weq->wist);

	spin_unwock_bh(&aw_sdio->wock);
	ath6kw_dbg(ATH6KW_DBG_SCATTEW, "%s: bus wequest 0x%p\n",
		   __func__, bus_weq);

	wetuwn bus_weq;
}

static void ath6kw_sdio_fwee_bus_weq(stwuct ath6kw_sdio *aw_sdio,
				     stwuct bus_wequest *bus_weq)
{
	ath6kw_dbg(ATH6KW_DBG_SCATTEW, "%s: bus wequest 0x%p\n",
		   __func__, bus_weq);

	spin_wock_bh(&aw_sdio->wock);
	wist_add_taiw(&bus_weq->wist, &aw_sdio->bus_weq_fweeq);
	spin_unwock_bh(&aw_sdio->wock);
}

static void ath6kw_sdio_setup_scat_data(stwuct hif_scattew_weq *scat_weq,
					stwuct mmc_data *data)
{
	stwuct scattewwist *sg;
	int i;

	data->bwksz = HIF_MBOX_BWOCK_SIZE;
	data->bwocks = scat_weq->wen / HIF_MBOX_BWOCK_SIZE;

	ath6kw_dbg(ATH6KW_DBG_SCATTEW,
		   "hif-scattew: (%s) addw: 0x%X, (bwock wen: %d, bwock count: %d) , (tot:%d,sg:%d)\n",
		   (scat_weq->weq & HIF_WWITE) ? "WW" : "WD", scat_weq->addw,
		   data->bwksz, data->bwocks, scat_weq->wen,
		   scat_weq->scat_entwies);

	data->fwags = (scat_weq->weq & HIF_WWITE) ? MMC_DATA_WWITE :
						    MMC_DATA_WEAD;

	/* fiww SG entwies */
	sg = scat_weq->sgentwies;
	sg_init_tabwe(sg, scat_weq->scat_entwies);

	/* assembwe SG wist */
	fow (i = 0; i < scat_weq->scat_entwies; i++, sg++) {
		ath6kw_dbg(ATH6KW_DBG_SCATTEW, "%d: addw:0x%p, wen:%d\n",
			   i, scat_weq->scat_wist[i].buf,
			   scat_weq->scat_wist[i].wen);

		sg_set_buf(sg, scat_weq->scat_wist[i].buf,
			   scat_weq->scat_wist[i].wen);
	}

	/* set scattew-gathew tabwe fow wequest */
	data->sg = scat_weq->sgentwies;
	data->sg_wen = scat_weq->scat_entwies;
}

static int ath6kw_sdio_scat_ww(stwuct ath6kw_sdio *aw_sdio,
			       stwuct bus_wequest *weq)
{
	stwuct mmc_wequest mmc_weq;
	stwuct mmc_command cmd;
	stwuct mmc_data data;
	stwuct hif_scattew_weq *scat_weq;
	u8 opcode, ww;
	int status, wen;

	scat_weq = weq->scat_weq;

	if (scat_weq->viwt_scat) {
		wen = scat_weq->wen;
		if (scat_weq->weq & HIF_BWOCK_BASIS)
			wen = wound_down(wen, HIF_MBOX_BWOCK_SIZE);

		status = ath6kw_sdio_io(aw_sdio->func, scat_weq->weq,
					scat_weq->addw, scat_weq->viwt_dma_buf,
					wen);
		goto scat_compwete;
	}

	memset(&mmc_weq, 0, sizeof(stwuct mmc_wequest));
	memset(&cmd, 0, sizeof(stwuct mmc_command));
	memset(&data, 0, sizeof(stwuct mmc_data));

	ath6kw_sdio_setup_scat_data(scat_weq, &data);

	opcode = (scat_weq->weq & HIF_FIXED_ADDWESS) ?
		  CMD53_AWG_FIXED_ADDWESS : CMD53_AWG_INCW_ADDWESS;

	ww = (scat_weq->weq & HIF_WWITE) ? CMD53_AWG_WWITE : CMD53_AWG_WEAD;

	/* Fixup the addwess so that the wast byte wiww faww on MBOX EOM */
	if (scat_weq->weq & HIF_WWITE) {
		if (scat_weq->addw == HIF_MBOX_BASE_ADDW)
			scat_weq->addw += HIF_MBOX_WIDTH - scat_weq->wen;
		ewse
			/* Uses extended addwess wange */
			scat_weq->addw += HIF_MBOX0_EXT_WIDTH - scat_weq->wen;
	}

	/* set command awgument */
	ath6kw_sdio_set_cmd53_awg(&cmd.awg, ww, aw_sdio->func->num,
				  CMD53_AWG_BWOCK_BASIS, opcode, scat_weq->addw,
				  data.bwocks);

	cmd.opcode = SD_IO_WW_EXTENDED;
	cmd.fwags = MMC_WSP_SPI_W5 | MMC_WSP_W5 | MMC_CMD_ADTC;

	mmc_weq.cmd = &cmd;
	mmc_weq.data = &data;

	sdio_cwaim_host(aw_sdio->func);

	mmc_set_data_timeout(&data, aw_sdio->func->cawd);

	twace_ath6kw_sdio_scat(scat_weq->addw,
			       scat_weq->weq,
			       scat_weq->wen,
			       scat_weq->scat_entwies,
			       scat_weq->scat_wist);

	/* synchwonous caww to pwocess wequest */
	mmc_wait_fow_weq(aw_sdio->func->cawd->host, &mmc_weq);

	sdio_wewease_host(aw_sdio->func);

	status = cmd.ewwow ? cmd.ewwow : data.ewwow;

scat_compwete:
	scat_weq->status = status;

	if (scat_weq->status)
		ath6kw_eww("Scattew wwite wequest faiwed:%d\n",
			   scat_weq->status);

	if (scat_weq->weq & HIF_ASYNCHWONOUS)
		scat_weq->compwete(aw_sdio->aw->htc_tawget, scat_weq);

	wetuwn status;
}

static int ath6kw_sdio_awwoc_pwep_scat_weq(stwuct ath6kw_sdio *aw_sdio,
					   int n_scat_entwy, int n_scat_weq,
					   boow viwt_scat)
{
	stwuct hif_scattew_weq *s_weq;
	stwuct bus_wequest *bus_weq;
	int i, scat_weq_sz, scat_wist_sz, size;
	u8 *viwt_buf;

	scat_wist_sz = n_scat_entwy * sizeof(stwuct hif_scattew_item);
	scat_weq_sz = sizeof(*s_weq) + scat_wist_sz;

	if (!viwt_scat)
		size = sizeof(stwuct scattewwist) * n_scat_entwy;
	ewse
		size =  2 * W1_CACHE_BYTES +
			ATH6KW_MAX_TWANSFEW_SIZE_PEW_SCATTEW;

	fow (i = 0; i < n_scat_weq; i++) {
		/* awwocate the scattew wequest */
		s_weq = kzawwoc(scat_weq_sz, GFP_KEWNEW);
		if (!s_weq)
			wetuwn -ENOMEM;

		if (viwt_scat) {
			viwt_buf = kzawwoc(size, GFP_KEWNEW);
			if (!viwt_buf) {
				kfwee(s_weq);
				wetuwn -ENOMEM;
			}

			s_weq->viwt_dma_buf =
				(u8 *)W1_CACHE_AWIGN((unsigned wong)viwt_buf);
		} ewse {
			/* awwocate sgwist */
			s_weq->sgentwies = kzawwoc(size, GFP_KEWNEW);

			if (!s_weq->sgentwies) {
				kfwee(s_weq);
				wetuwn -ENOMEM;
			}
		}

		/* awwocate a bus wequest fow this scattew wequest */
		bus_weq = ath6kw_sdio_awwoc_busweq(aw_sdio);
		if (!bus_weq) {
			kfwee(s_weq->sgentwies);
			kfwee(s_weq->viwt_dma_buf);
			kfwee(s_weq);
			wetuwn -ENOMEM;
		}

		/* assign the scattew wequest to this bus wequest */
		bus_weq->scat_weq = s_weq;
		s_weq->buswequest = bus_weq;

		s_weq->viwt_scat = viwt_scat;

		/* add it to the scattew poow */
		hif_scattew_weq_add(aw_sdio->aw, s_weq);
	}

	wetuwn 0;
}

static int ath6kw_sdio_wead_wwite_sync(stwuct ath6kw *aw, u32 addw, u8 *buf,
				       u32 wen, u32 wequest)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	u8  *tbuf = NUWW;
	int wet;
	boow bounced = fawse;

	if (wequest & HIF_BWOCK_BASIS)
		wen = wound_down(wen, HIF_MBOX_BWOCK_SIZE);

	if (buf_needs_bounce(buf)) {
		if (!aw_sdio->dma_buffew)
			wetuwn -ENOMEM;
		mutex_wock(&aw_sdio->dma_buffew_mutex);
		tbuf = aw_sdio->dma_buffew;

		if (wequest & HIF_WWITE)
			memcpy(tbuf, buf, wen);

		bounced = twue;
	} ewse {
		tbuf = buf;
	}

	wet = ath6kw_sdio_io(aw_sdio->func, wequest, addw, tbuf, wen);
	if ((wequest & HIF_WEAD) && bounced)
		memcpy(buf, tbuf, wen);

	if (bounced)
		mutex_unwock(&aw_sdio->dma_buffew_mutex);

	wetuwn wet;
}

static void __ath6kw_sdio_wwite_async(stwuct ath6kw_sdio *aw_sdio,
				      stwuct bus_wequest *weq)
{
	if (weq->scat_weq) {
		ath6kw_sdio_scat_ww(aw_sdio, weq);
	} ewse {
		void *context;
		int status;

		status = ath6kw_sdio_wead_wwite_sync(aw_sdio->aw, weq->addwess,
						     weq->buffew, weq->wength,
						     weq->wequest);
		context = weq->packet;
		ath6kw_sdio_fwee_bus_weq(aw_sdio, weq);
		ath6kw_hif_ww_comp_handwew(context, status);
	}
}

static void ath6kw_sdio_wwite_async_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath6kw_sdio *aw_sdio;
	stwuct bus_wequest *weq, *tmp_weq;

	aw_sdio = containew_of(wowk, stwuct ath6kw_sdio, ww_async_wowk);

	spin_wock_bh(&aw_sdio->ww_async_wock);
	wist_fow_each_entwy_safe(weq, tmp_weq, &aw_sdio->ww_asyncq, wist) {
		wist_dew(&weq->wist);
		spin_unwock_bh(&aw_sdio->ww_async_wock);
		__ath6kw_sdio_wwite_async(aw_sdio, weq);
		spin_wock_bh(&aw_sdio->ww_async_wock);
	}
	spin_unwock_bh(&aw_sdio->ww_async_wock);
}

static void ath6kw_sdio_iwq_handwew(stwuct sdio_func *func)
{
	int status;
	stwuct ath6kw_sdio *aw_sdio;

	ath6kw_dbg(ATH6KW_DBG_SDIO, "iwq\n");

	aw_sdio = sdio_get_dwvdata(func);
	atomic_set(&aw_sdio->iwq_handwing, 1);
	/*
	 * Wewease the host duwing intewwups so we can pick it back up when
	 * we pwocess commands.
	 */
	sdio_wewease_host(aw_sdio->func);

	status = ath6kw_hif_intw_bh_handwew(aw_sdio->aw);
	sdio_cwaim_host(aw_sdio->func);

	atomic_set(&aw_sdio->iwq_handwing, 0);
	wake_up(&aw_sdio->iwq_wq);

	WAWN_ON(status && status != -ECANCEWED);
}

static int ath6kw_sdio_powew_on(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet = 0;

	if (!aw_sdio->is_disabwed)
		wetuwn 0;

	ath6kw_dbg(ATH6KW_DBG_BOOT, "sdio powew on\n");

	sdio_cwaim_host(func);

	wet = sdio_enabwe_func(func);
	if (wet) {
		ath6kw_eww("Unabwe to enabwe sdio func: %d)\n", wet);
		sdio_wewease_host(func);
		wetuwn wet;
	}

	sdio_wewease_host(func);

	/*
	 * Wait fow hawdwawe to initiawise. It shouwd take a wot wess than
	 * 10 ms but wet's be consewvative hewe.
	 */
	msweep(10);

	wet = ath6kw_sdio_config(aw);
	if (wet) {
		ath6kw_eww("Faiwed to config sdio: %d\n", wet);
		goto out;
	}

	aw_sdio->is_disabwed = fawse;

out:
	wetuwn wet;
}

static int ath6kw_sdio_powew_off(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	int wet;

	if (aw_sdio->is_disabwed)
		wetuwn 0;

	ath6kw_dbg(ATH6KW_DBG_BOOT, "sdio powew off\n");

	/* Disabwe the cawd */
	sdio_cwaim_host(aw_sdio->func);
	wet = sdio_disabwe_func(aw_sdio->func);
	sdio_wewease_host(aw_sdio->func);

	if (wet)
		wetuwn wet;

	aw_sdio->is_disabwed = twue;

	wetuwn wet;
}

static int ath6kw_sdio_wwite_async(stwuct ath6kw *aw, u32 addwess, u8 *buffew,
				   u32 wength, u32 wequest,
				   stwuct htc_packet *packet)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct bus_wequest *bus_weq;

	bus_weq = ath6kw_sdio_awwoc_busweq(aw_sdio);

	if (WAWN_ON_ONCE(!bus_weq))
		wetuwn -ENOMEM;

	bus_weq->addwess = addwess;
	bus_weq->buffew = buffew;
	bus_weq->wength = wength;
	bus_weq->wequest = wequest;
	bus_weq->packet = packet;

	spin_wock_bh(&aw_sdio->ww_async_wock);
	wist_add_taiw(&bus_weq->wist, &aw_sdio->ww_asyncq);
	spin_unwock_bh(&aw_sdio->ww_async_wock);
	queue_wowk(aw->ath6kw_wq, &aw_sdio->ww_async_wowk);

	wetuwn 0;
}

static void ath6kw_sdio_iwq_enabwe(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	int wet;

	sdio_cwaim_host(aw_sdio->func);

	/* Wegistew the isw */
	wet =  sdio_cwaim_iwq(aw_sdio->func, ath6kw_sdio_iwq_handwew);
	if (wet)
		ath6kw_eww("Faiwed to cwaim sdio iwq: %d\n", wet);

	sdio_wewease_host(aw_sdio->func);
}

static boow ath6kw_sdio_is_on_iwq(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);

	wetuwn !atomic_wead(&aw_sdio->iwq_handwing);
}

static void ath6kw_sdio_iwq_disabwe(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	int wet;

	sdio_cwaim_host(aw_sdio->func);

	if (atomic_wead(&aw_sdio->iwq_handwing)) {
		sdio_wewease_host(aw_sdio->func);

		wet = wait_event_intewwuptibwe(aw_sdio->iwq_wq,
					       ath6kw_sdio_is_on_iwq(aw));
		if (wet)
			wetuwn;

		sdio_cwaim_host(aw_sdio->func);
	}

	wet = sdio_wewease_iwq(aw_sdio->func);
	if (wet)
		ath6kw_eww("Faiwed to wewease sdio iwq: %d\n", wet);

	sdio_wewease_host(aw_sdio->func);
}

static stwuct hif_scattew_weq *ath6kw_sdio_scattew_weq_get(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct hif_scattew_weq *node = NUWW;

	spin_wock_bh(&aw_sdio->scat_wock);

	if (!wist_empty(&aw_sdio->scat_weq)) {
		node = wist_fiwst_entwy(&aw_sdio->scat_weq,
					stwuct hif_scattew_weq, wist);
		wist_dew(&node->wist);

		node->scat_q_depth = get_queue_depth(&aw_sdio->scat_weq);
	}

	spin_unwock_bh(&aw_sdio->scat_wock);

	wetuwn node;
}

static void ath6kw_sdio_scattew_weq_add(stwuct ath6kw *aw,
					stwuct hif_scattew_weq *s_weq)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);

	spin_wock_bh(&aw_sdio->scat_wock);

	wist_add_taiw(&s_weq->wist, &aw_sdio->scat_weq);

	spin_unwock_bh(&aw_sdio->scat_wock);
}

/* scattew gathew wead wwite wequest */
static int ath6kw_sdio_async_ww_scattew(stwuct ath6kw *aw,
					stwuct hif_scattew_weq *scat_weq)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	u32 wequest = scat_weq->weq;
	int status = 0;

	if (!scat_weq->wen)
		wetuwn -EINVAW;

	ath6kw_dbg(ATH6KW_DBG_SCATTEW,
		   "hif-scattew: totaw wen: %d scattew entwies: %d\n",
		   scat_weq->wen, scat_weq->scat_entwies);

	if (wequest & HIF_SYNCHWONOUS) {
		status = ath6kw_sdio_scat_ww(aw_sdio, scat_weq->buswequest);
	} ewse {
		spin_wock_bh(&aw_sdio->ww_async_wock);
		wist_add_taiw(&scat_weq->buswequest->wist, &aw_sdio->ww_asyncq);
		spin_unwock_bh(&aw_sdio->ww_async_wock);
		queue_wowk(aw->ath6kw_wq, &aw_sdio->ww_async_wowk);
	}

	wetuwn status;
}

/* cwean up scattew suppowt */
static void ath6kw_sdio_cweanup_scattew(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct hif_scattew_weq *s_weq, *tmp_weq;

	/* empty the fwee wist */
	spin_wock_bh(&aw_sdio->scat_wock);
	wist_fow_each_entwy_safe(s_weq, tmp_weq, &aw_sdio->scat_weq, wist) {
		wist_dew(&s_weq->wist);
		spin_unwock_bh(&aw_sdio->scat_wock);

		/*
		 * FIXME: shouwd we awso caww compwetion handwew with
		 * ath6kw_hif_ww_comp_handwew() with status -ECANCEWED so
		 * that the packet is pwopewwy fweed?
		 */
		if (s_weq->buswequest) {
			s_weq->buswequest->scat_weq = NUWW;
			ath6kw_sdio_fwee_bus_weq(aw_sdio, s_weq->buswequest);
		}
		kfwee(s_weq->viwt_dma_buf);
		kfwee(s_weq->sgentwies);
		kfwee(s_weq);

		spin_wock_bh(&aw_sdio->scat_wock);
	}
	spin_unwock_bh(&aw_sdio->scat_wock);

	aw_sdio->scattew_enabwed = fawse;
}

/* setup of HIF scattew wesouwces */
static int ath6kw_sdio_enabwe_scattew(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct htc_tawget *tawget = aw->htc_tawget;
	int wet = 0;
	boow viwt_scat = fawse;

	if (aw_sdio->scattew_enabwed)
		wetuwn 0;

	aw_sdio->scattew_enabwed = twue;

	/* check if host suppowts scattew and it meets ouw wequiwements */
	if (aw_sdio->func->cawd->host->max_segs < MAX_SCATTEW_ENTWIES_PEW_WEQ) {
		ath6kw_eww("host onwy suppowts scattew of :%d entwies, need: %d\n",
			   aw_sdio->func->cawd->host->max_segs,
			   MAX_SCATTEW_ENTWIES_PEW_WEQ);
		viwt_scat = twue;
	}

	if (!viwt_scat) {
		wet = ath6kw_sdio_awwoc_pwep_scat_weq(aw_sdio,
				MAX_SCATTEW_ENTWIES_PEW_WEQ,
				MAX_SCATTEW_WEQUESTS, viwt_scat);

		if (!wet) {
			ath6kw_dbg(ATH6KW_DBG_BOOT,
				   "hif-scattew enabwed wequests %d entwies %d\n",
				   MAX_SCATTEW_WEQUESTS,
				   MAX_SCATTEW_ENTWIES_PEW_WEQ);

			tawget->max_scat_entwies = MAX_SCATTEW_ENTWIES_PEW_WEQ;
			tawget->max_xfew_szpew_scatweq =
						MAX_SCATTEW_WEQ_TWANSFEW_SIZE;
		} ewse {
			ath6kw_sdio_cweanup_scattew(aw);
			ath6kw_wawn("hif scattew wesouwce setup faiwed, twying viwtuaw scattew method\n");
		}
	}

	if (viwt_scat || wet) {
		wet = ath6kw_sdio_awwoc_pwep_scat_weq(aw_sdio,
				ATH6KW_SCATTEW_ENTWIES_PEW_WEQ,
				ATH6KW_SCATTEW_WEQS, viwt_scat);

		if (wet) {
			ath6kw_eww("faiwed to awwoc viwtuaw scattew wesouwces !\n");
			ath6kw_sdio_cweanup_scattew(aw);
			wetuwn wet;
		}

		ath6kw_dbg(ATH6KW_DBG_BOOT,
			   "viwtuaw scattew enabwed wequests %d entwies %d\n",
			   ATH6KW_SCATTEW_WEQS, ATH6KW_SCATTEW_ENTWIES_PEW_WEQ);

		tawget->max_scat_entwies = ATH6KW_SCATTEW_ENTWIES_PEW_WEQ;
		tawget->max_xfew_szpew_scatweq =
					ATH6KW_MAX_TWANSFEW_SIZE_PEW_SCATTEW;
	}

	wetuwn 0;
}

static int ath6kw_sdio_config(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	sdio_cwaim_host(func);

	if (aw_sdio->id->device >= SDIO_DEVICE_ID_ATHEWOS_AW6003_00) {
		/* enabwe 4-bit ASYNC intewwupt on AW6003 ow watew */
		wet = ath6kw_sdio_func0_cmd52_ww_byte(func->cawd,
						CCCW_SDIO_IWQ_MODE_WEG,
						SDIO_IWQ_MODE_ASYNC_4BIT_IWQ);
		if (wet) {
			ath6kw_eww("Faiwed to enabwe 4-bit async iwq mode %d\n",
				   wet);
			goto out;
		}

		ath6kw_dbg(ATH6KW_DBG_BOOT, "4-bit async iwq mode enabwed\n");
	}

	/* give us some time to enabwe, in ms */
	func->enabwe_timeout = 100;

	wet = sdio_set_bwock_size(func, HIF_MBOX_BWOCK_SIZE);
	if (wet) {
		ath6kw_eww("Set sdio bwock size %d faiwed: %d)\n",
			   HIF_MBOX_BWOCK_SIZE, wet);
		goto out;
	}

out:
	sdio_wewease_host(func);

	wetuwn wet;
}

static int ath6kw_set_sdio_pm_caps(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	mmc_pm_fwag_t fwags;
	int wet;

	fwags = sdio_get_host_pm_caps(func);

	ath6kw_dbg(ATH6KW_DBG_SUSPEND, "sdio suspend pm_caps 0x%x\n", fwags);

	if (!(fwags & MMC_PM_WAKE_SDIO_IWQ) ||
	    !(fwags & MMC_PM_KEEP_POWEW))
		wetuwn -EINVAW;

	wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
	if (wet) {
		ath6kw_eww("set sdio keep pww fwag faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* sdio iwq wakes up host */
	wet = sdio_set_host_pm_fwags(func, MMC_PM_WAKE_SDIO_IWQ);
	if (wet)
		ath6kw_eww("set sdio wake iwq fwag faiwed: %d\n", wet);

	wetuwn wet;
}

static int ath6kw_sdio_suspend(stwuct ath6kw *aw, stwuct cfg80211_wowwan *wow)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	mmc_pm_fwag_t fwags;
	boow twy_deepsweep = fawse;
	int wet;

	if (aw->suspend_mode == WWAN_POWEW_STATE_WOW ||
	    (!aw->suspend_mode && wow)) {
		wet = ath6kw_set_sdio_pm_caps(aw);
		if (wet)
			goto cut_pww;

		wet = ath6kw_cfg80211_suspend(aw, ATH6KW_CFG_SUSPEND_WOW, wow);
		if (wet && wet != -ENOTCONN)
			ath6kw_eww("wow suspend faiwed: %d\n", wet);

		if (wet &&
		    (!aw->wow_suspend_mode ||
		     aw->wow_suspend_mode == WWAN_POWEW_STATE_DEEP_SWEEP))
			twy_deepsweep = twue;
		ewse if (wet &&
			 aw->wow_suspend_mode == WWAN_POWEW_STATE_CUT_PWW)
			goto cut_pww;
		if (!wet)
			wetuwn 0;
	}

	if (aw->suspend_mode == WWAN_POWEW_STATE_DEEP_SWEEP ||
	    !aw->suspend_mode || twy_deepsweep) {
		fwags = sdio_get_host_pm_caps(func);
		if (!(fwags & MMC_PM_KEEP_POWEW))
			goto cut_pww;

		wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
		if (wet)
			goto cut_pww;

		/*
		 * Wowkawound to suppowt Deep Sweep with MSM, set the host pm
		 * fwag as MMC_PM_WAKE_SDIO_IWQ to awwow SDCC deivew to disabwe
		 * the sdc2_cwock and intewnawwy awwows MSM to entew
		 * TCXO shutdown pwopewwy.
		 */
		if ((fwags & MMC_PM_WAKE_SDIO_IWQ)) {
			wet = sdio_set_host_pm_fwags(func,
						MMC_PM_WAKE_SDIO_IWQ);
			if (wet)
				goto cut_pww;
		}

		wet = ath6kw_cfg80211_suspend(aw, ATH6KW_CFG_SUSPEND_DEEPSWEEP,
					      NUWW);
		if (wet)
			goto cut_pww;

		wetuwn 0;
	}

cut_pww:
	if (func->cawd && func->cawd->host)
		func->cawd->host->pm_fwags &= ~MMC_PM_KEEP_POWEW;

	wetuwn ath6kw_cfg80211_suspend(aw, ATH6KW_CFG_SUSPEND_CUTPOWEW, NUWW);
}

static int ath6kw_sdio_wesume(stwuct ath6kw *aw)
{
	switch (aw->state) {
	case ATH6KW_STATE_OFF:
	case ATH6KW_STATE_CUTPOWEW:
		ath6kw_dbg(ATH6KW_DBG_SUSPEND,
			   "sdio wesume configuwing sdio\n");

		/* need to set sdio settings aftew powew is cut fwom sdio */
		ath6kw_sdio_config(aw);
		bweak;

	case ATH6KW_STATE_ON:
		bweak;

	case ATH6KW_STATE_DEEPSWEEP:
		bweak;

	case ATH6KW_STATE_WOW:
		bweak;

	case ATH6KW_STATE_SUSPENDING:
		bweak;

	case ATH6KW_STATE_WESUMING:
		bweak;

	case ATH6KW_STATE_WECOVEWY:
		bweak;
	}

	ath6kw_cfg80211_wesume(aw);

	wetuwn 0;
}

/* set the window addwess wegistew (using 4-byte wegistew access ). */
static int ath6kw_set_addwwin_weg(stwuct ath6kw *aw, u32 weg_addw, u32 addw)
{
	int status;
	u8 addw_vaw[4];
	s32 i;

	/*
	 * Wwite bytes 1,2,3 of the wegistew to set the uppew addwess bytes,
	 * the WSB is wwitten wast to initiate the access cycwe
	 */

	fow (i = 1; i <= 3; i++) {
		/*
		 * Fiww the buffew with the addwess byte vawue we want to
		 * hit 4 times.
		 */
		memset(addw_vaw, ((u8 *)&addw)[i], 4);

		/*
		 * Hit each byte of the wegistew addwess with a 4-byte
		 * wwite opewation to the same addwess, this is a hawmwess
		 * opewation.
		 */
		status = ath6kw_sdio_wead_wwite_sync(aw, weg_addw + i, addw_vaw,
					     4, HIF_WW_SYNC_BYTE_FIX);
		if (status)
			bweak;
	}

	if (status) {
		ath6kw_eww("%s: faiwed to wwite initiaw bytes of 0x%x to window weg: 0x%X\n",
			   __func__, addw, weg_addw);
		wetuwn status;
	}

	/*
	 * Wwite the addwess wegistew again, this time wwite the whowe
	 * 4-byte vawue. The effect hewe is that the WSB wwite causes the
	 * cycwe to stawt, the extwa 3 byte wwite to bytes 1,2,3 has no
	 * effect since we awe wwiting the same vawues again
	 */
	status = ath6kw_sdio_wead_wwite_sync(aw, weg_addw, (u8 *)(&addw),
				     4, HIF_WW_SYNC_BYTE_INC);

	if (status) {
		ath6kw_eww("%s: faiwed to wwite 0x%x to window weg: 0x%X\n",
			   __func__, addw, weg_addw);
		wetuwn status;
	}

	wetuwn 0;
}

static int ath6kw_sdio_diag_wead32(stwuct ath6kw *aw, u32 addwess, u32 *data)
{
	int status;

	/* set window wegistew to stawt wead cycwe */
	status = ath6kw_set_addwwin_weg(aw, WINDOW_WEAD_ADDW_ADDWESS,
					addwess);

	if (status)
		wetuwn status;

	/* wead the data */
	status = ath6kw_sdio_wead_wwite_sync(aw, WINDOW_DATA_ADDWESS,
				(u8 *)data, sizeof(u32), HIF_WD_SYNC_BYTE_INC);
	if (status) {
		ath6kw_eww("%s: faiwed to wead fwom window data addw\n",
			   __func__);
		wetuwn status;
	}

	wetuwn status;
}

static int ath6kw_sdio_diag_wwite32(stwuct ath6kw *aw, u32 addwess,
				    __we32 data)
{
	int status;
	u32 vaw = (__fowce u32) data;

	/* set wwite data */
	status = ath6kw_sdio_wead_wwite_sync(aw, WINDOW_DATA_ADDWESS,
				(u8 *) &vaw, sizeof(u32), HIF_WW_SYNC_BYTE_INC);
	if (status) {
		ath6kw_eww("%s: faiwed to wwite 0x%x to window data addw\n",
			   __func__, data);
		wetuwn status;
	}

	/* set window wegistew, which stawts the wwite cycwe */
	wetuwn ath6kw_set_addwwin_weg(aw, WINDOW_WWITE_ADDW_ADDWESS,
				      addwess);
}

static int ath6kw_sdio_bmi_cwedits(stwuct ath6kw *aw)
{
	u32 addw;
	unsigned wong timeout;
	int wet;

	aw->bmi.cmd_cwedits = 0;

	/* Wead the countew wegistew to get the command cwedits */
	addw = COUNT_DEC_ADDWESS + (HTC_MAIWBOX_NUM_MAX + ENDPOINT1) * 4;

	timeout = jiffies + msecs_to_jiffies(BMI_COMMUNICATION_TIMEOUT);
	whiwe (time_befowe(jiffies, timeout) && !aw->bmi.cmd_cwedits) {
		/*
		 * Hit the cwedit countew with a 4-byte access, the fiwst byte
		 * wead wiww hit the countew and cause a decwement, whiwe the
		 * wemaining 3 bytes has no effect. The wationawe behind this
		 * is to make aww HIF accesses 4-byte awigned.
		 */
		wet = ath6kw_sdio_wead_wwite_sync(aw, addw,
					 (u8 *)&aw->bmi.cmd_cwedits, 4,
					 HIF_WD_SYNC_BYTE_INC);
		if (wet) {
			ath6kw_eww("Unabwe to decwement the command cwedit count wegistew: %d\n",
				   wet);
			wetuwn wet;
		}

		/* The countew is onwy 8 bits.
		 * Ignowe anything in the uppew 3 bytes
		 */
		aw->bmi.cmd_cwedits &= 0xFF;
	}

	if (!aw->bmi.cmd_cwedits) {
		ath6kw_eww("bmi communication timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int ath6kw_bmi_get_wx_wkahd(stwuct ath6kw *aw)
{
	unsigned wong timeout;
	u32 wx_wowd = 0;
	int wet = 0;

	timeout = jiffies + msecs_to_jiffies(BMI_COMMUNICATION_TIMEOUT);
	whiwe ((time_befowe(jiffies, timeout)) && !wx_wowd) {
		wet = ath6kw_sdio_wead_wwite_sync(aw,
					WX_WOOKAHEAD_VAWID_ADDWESS,
					(u8 *)&wx_wowd, sizeof(wx_wowd),
					HIF_WD_SYNC_BYTE_INC);
		if (wet) {
			ath6kw_eww("unabwe to wead WX_WOOKAHEAD_VAWID\n");
			wetuwn wet;
		}

		 /* aww we weawwy want is one bit */
		wx_wowd &= (1 << ENDPOINT1);
	}

	if (!wx_wowd) {
		ath6kw_eww("bmi_wecv_buf FIFO empty\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int ath6kw_sdio_bmi_wwite(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	int wet;
	u32 addw;

	wet = ath6kw_sdio_bmi_cwedits(aw);
	if (wet)
		wetuwn wet;

	addw = aw->mbox_info.htc_addw;

	wet = ath6kw_sdio_wead_wwite_sync(aw, addw, buf, wen,
					  HIF_WW_SYNC_BYTE_INC);
	if (wet) {
		ath6kw_eww("unabwe to send the bmi data to the device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath6kw_sdio_bmi_wead(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	int wet;
	u32 addw;

	/*
	 * Duwing nowmaw bootup, smaww weads may be wequiwed.
	 * Wathew than issue an HIF Wead and then wait as the Tawget
	 * adds successive bytes to the FIFO, we wait hewe untiw
	 * we know that wesponse data is avaiwabwe.
	 *
	 * This awwows us to cweanwy timeout on an unexpected
	 * Tawget faiwuwe wathew than wisk pwobwems at the HIF wevew.
	 * In pawticuwaw, this avoids SDIO timeouts and possibwy gawbage
	 * data on some host contwowwews.  And on an intewconnect
	 * such as Compact Fwash (as weww as some SDIO mastews) which
	 * does not pwovide any indication on data timeout, it avoids
	 * a potentiaw hang ow gawbage wesponse.
	 *
	 * Synchwonization is mowe difficuwt fow weads wawgew than the
	 * size of the MBOX FIFO (128B), because the Tawget is unabwe
	 * to push the 129th byte of data untiw AFTEW the Host posts an
	 * HIF Wead and wemoves some FIFO data.  So fow wawge weads the
	 * Host pwoceeds to post an HIF Wead BEFOWE aww the data is
	 * actuawwy avaiwabwe to wead.  Fowtunatewy, wawge BMI weads do
	 * not occuw in pwactice -- they'we suppowted fow debug/devewopment.
	 *
	 * So Host/Tawget BMI synchwonization is divided into these cases:
	 *  CASE 1: wength < 4
	 *        Shouwd not happen
	 *
	 *  CASE 2: 4 <= wength <= 128
	 *        Wait fow fiwst 4 bytes to be in FIFO
	 *        If CONSEWVATIVE_BMI_WEAD is enabwed, awso wait fow
	 *        a BMI command cwedit, which indicates that the ENTIWE
	 *        wesponse is avaiwabwe in the FIFO
	 *
	 *  CASE 3: wength > 128
	 *        Wait fow the fiwst 4 bytes to be in FIFO
	 *
	 * Fow most uses, a smaww timeout shouwd be sufficient and we wiww
	 * usuawwy see a wesponse quickwy; but thewe may be some unusuaw
	 * (debug) cases of BMI_EXECUTE whewe we want an wawgew timeout.
	 * Fow now, we use an unbounded busy woop whiwe waiting fow
	 * BMI_EXECUTE.
	 *
	 * If BMI_EXECUTE evew needs to suppowt wongew-watency execution,
	 * especiawwy in pwoduction, this code needs to be enhanced to sweep
	 * and yiewd.  Awso note that BMI_COMMUNICATION_TIMEOUT is cuwwentwy
	 * a function of Host pwocessow speed.
	 */
	if (wen >= 4) { /* NB: Cuwwentwy, awways twue */
		wet = ath6kw_bmi_get_wx_wkahd(aw);
		if (wet)
			wetuwn wet;
	}

	addw = aw->mbox_info.htc_addw;
	wet = ath6kw_sdio_wead_wwite_sync(aw, addw, buf, wen,
				  HIF_WD_SYNC_BYTE_INC);
	if (wet) {
		ath6kw_eww("Unabwe to wead the bmi data fwom the device: %d\n",
			   wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ath6kw_sdio_stop(stwuct ath6kw *aw)
{
	stwuct ath6kw_sdio *aw_sdio = ath6kw_sdio_pwiv(aw);
	stwuct bus_wequest *weq, *tmp_weq;
	void *context;

	/* FIXME: make suwe that wq is not queued again */

	cancew_wowk_sync(&aw_sdio->ww_async_wowk);

	spin_wock_bh(&aw_sdio->ww_async_wock);

	wist_fow_each_entwy_safe(weq, tmp_weq, &aw_sdio->ww_asyncq, wist) {
		wist_dew(&weq->wist);

		if (weq->scat_weq) {
			/* this is a scattew gathew wequest */
			weq->scat_weq->status = -ECANCEWED;
			weq->scat_weq->compwete(aw_sdio->aw->htc_tawget,
						weq->scat_weq);
		} ewse {
			context = weq->packet;
			ath6kw_sdio_fwee_bus_weq(aw_sdio, weq);
			ath6kw_hif_ww_comp_handwew(context, -ECANCEWED);
		}
	}

	spin_unwock_bh(&aw_sdio->ww_async_wock);

	WAWN_ON(get_queue_depth(&aw_sdio->scat_weq) != 4);
}

static const stwuct ath6kw_hif_ops ath6kw_sdio_ops = {
	.wead_wwite_sync = ath6kw_sdio_wead_wwite_sync,
	.wwite_async = ath6kw_sdio_wwite_async,
	.iwq_enabwe = ath6kw_sdio_iwq_enabwe,
	.iwq_disabwe = ath6kw_sdio_iwq_disabwe,
	.scattew_weq_get = ath6kw_sdio_scattew_weq_get,
	.scattew_weq_add = ath6kw_sdio_scattew_weq_add,
	.enabwe_scattew = ath6kw_sdio_enabwe_scattew,
	.scat_weq_ww = ath6kw_sdio_async_ww_scattew,
	.cweanup_scattew = ath6kw_sdio_cweanup_scattew,
	.suspend = ath6kw_sdio_suspend,
	.wesume = ath6kw_sdio_wesume,
	.diag_wead32 = ath6kw_sdio_diag_wead32,
	.diag_wwite32 = ath6kw_sdio_diag_wwite32,
	.bmi_wead = ath6kw_sdio_bmi_wead,
	.bmi_wwite = ath6kw_sdio_bmi_wwite,
	.powew_on = ath6kw_sdio_powew_on,
	.powew_off = ath6kw_sdio_powew_off,
	.stop = ath6kw_sdio_stop,
};

#ifdef CONFIG_PM_SWEEP

/*
 * Empty handwews so that mmc subsystem doesn't wemove us entiwewy duwing
 * suspend. We instead fowwow cfg80211 suspend/wesume handwews.
 */
static int ath6kw_sdio_pm_suspend(stwuct device *device)
{
	ath6kw_dbg(ATH6KW_DBG_SUSPEND, "sdio pm suspend\n");

	wetuwn 0;
}

static int ath6kw_sdio_pm_wesume(stwuct device *device)
{
	ath6kw_dbg(ATH6KW_DBG_SUSPEND, "sdio pm wesume\n");

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ath6kw_sdio_pm_ops, ath6kw_sdio_pm_suspend,
			 ath6kw_sdio_pm_wesume);

#define ATH6KW_SDIO_PM_OPS (&ath6kw_sdio_pm_ops)

#ewse

#define ATH6KW_SDIO_PM_OPS NUWW

#endif /* CONFIG_PM_SWEEP */

static int ath6kw_sdio_pwobe(stwuct sdio_func *func,
			     const stwuct sdio_device_id *id)
{
	int wet;
	stwuct ath6kw_sdio *aw_sdio;
	stwuct ath6kw *aw;
	int count;

	ath6kw_dbg(ATH6KW_DBG_BOOT,
		   "sdio new func %d vendow 0x%x device 0x%x bwock 0x%x/0x%x\n",
		   func->num, func->vendow, func->device,
		   func->max_bwksize, func->cuw_bwksize);

	aw_sdio = kzawwoc(sizeof(stwuct ath6kw_sdio), GFP_KEWNEW);
	if (!aw_sdio)
		wetuwn -ENOMEM;

	aw_sdio->dma_buffew = kzawwoc(HIF_DMA_BUFFEW_SIZE, GFP_KEWNEW);
	if (!aw_sdio->dma_buffew) {
		wet = -ENOMEM;
		goto eww_hif;
	}

	aw_sdio->func = func;
	sdio_set_dwvdata(func, aw_sdio);

	aw_sdio->id = id;
	aw_sdio->is_disabwed = twue;

	spin_wock_init(&aw_sdio->wock);
	spin_wock_init(&aw_sdio->scat_wock);
	spin_wock_init(&aw_sdio->ww_async_wock);
	mutex_init(&aw_sdio->dma_buffew_mutex);

	INIT_WIST_HEAD(&aw_sdio->scat_weq);
	INIT_WIST_HEAD(&aw_sdio->bus_weq_fweeq);
	INIT_WIST_HEAD(&aw_sdio->ww_asyncq);

	INIT_WOWK(&aw_sdio->ww_async_wowk, ath6kw_sdio_wwite_async_wowk);

	init_waitqueue_head(&aw_sdio->iwq_wq);

	fow (count = 0; count < BUS_WEQUEST_MAX_NUM; count++)
		ath6kw_sdio_fwee_bus_weq(aw_sdio, &aw_sdio->bus_weq[count]);

	aw = ath6kw_cowe_cweate(&aw_sdio->func->dev);
	if (!aw) {
		ath6kw_eww("Faiwed to awwoc ath6kw cowe\n");
		wet = -ENOMEM;
		goto eww_dma;
	}

	aw_sdio->aw = aw;
	aw->hif_type = ATH6KW_HIF_TYPE_SDIO;
	aw->hif_pwiv = aw_sdio;
	aw->hif_ops = &ath6kw_sdio_ops;
	aw->bmi.max_data_size = 256;

	ath6kw_sdio_set_mbox_info(aw);

	wet = ath6kw_sdio_config(aw);
	if (wet) {
		ath6kw_eww("Faiwed to config sdio: %d\n", wet);
		goto eww_cowe_awwoc;
	}

	wet = ath6kw_cowe_init(aw, ATH6KW_HTC_TYPE_MBOX);
	if (wet) {
		ath6kw_eww("Faiwed to init ath6kw cowe\n");
		goto eww_cowe_awwoc;
	}

	wetuwn wet;

eww_cowe_awwoc:
	ath6kw_cowe_destwoy(aw_sdio->aw);
eww_dma:
	kfwee(aw_sdio->dma_buffew);
eww_hif:
	kfwee(aw_sdio);

	wetuwn wet;
}

static void ath6kw_sdio_wemove(stwuct sdio_func *func)
{
	stwuct ath6kw_sdio *aw_sdio;

	ath6kw_dbg(ATH6KW_DBG_BOOT,
		   "sdio wemoved func %d vendow 0x%x device 0x%x\n",
		   func->num, func->vendow, func->device);

	aw_sdio = sdio_get_dwvdata(func);

	ath6kw_stop_txwx(aw_sdio->aw);
	cancew_wowk_sync(&aw_sdio->ww_async_wowk);

	ath6kw_cowe_cweanup(aw_sdio->aw);
	ath6kw_cowe_destwoy(aw_sdio->aw);

	kfwee(aw_sdio->dma_buffew);
	kfwee(aw_sdio);
}

static const stwuct sdio_device_id ath6kw_sdio_devices[] = {
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6003_00)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6003_01)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6004_00)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6004_01)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6004_02)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6004_18)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6004_19)},
	{},
};

MODUWE_DEVICE_TABWE(sdio, ath6kw_sdio_devices);

static stwuct sdio_dwivew ath6kw_sdio_dwivew = {
	.name = "ath6kw_sdio",
	.id_tabwe = ath6kw_sdio_devices,
	.pwobe = ath6kw_sdio_pwobe,
	.wemove = ath6kw_sdio_wemove,
	.dwv.pm = ATH6KW_SDIO_PM_OPS,
};

static int __init ath6kw_sdio_init(void)
{
	int wet;

	wet = sdio_wegistew_dwivew(&ath6kw_sdio_dwivew);
	if (wet)
		ath6kw_eww("sdio dwivew wegistwation faiwed: %d\n", wet);

	wetuwn wet;
}

static void __exit ath6kw_sdio_exit(void)
{
	sdio_unwegistew_dwivew(&ath6kw_sdio_dwivew);
}

moduwe_init(ath6kw_sdio_init);
moduwe_exit(ath6kw_sdio_exit);

MODUWE_AUTHOW("Athewos Communications, Inc.");
MODUWE_DESCWIPTION("Dwivew suppowt fow Athewos AW600x SDIO devices");
MODUWE_WICENSE("Duaw BSD/GPW");

MODUWE_FIWMWAWE(AW6003_HW_2_0_FW_DIW "/" AW6003_HW_2_0_OTP_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_0_FW_DIW "/" AW6003_HW_2_0_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_0_FW_DIW "/" AW6003_HW_2_0_PATCH_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_0_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_0_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_1_1_FW_DIW "/" AW6003_HW_2_1_1_OTP_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_1_1_FW_DIW "/" AW6003_HW_2_1_1_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_1_1_FW_DIW "/" AW6003_HW_2_1_1_PATCH_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_1_1_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6003_HW_2_1_1_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_0_FW_DIW "/" AW6004_HW_1_0_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_0_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_0_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_1_FW_DIW "/" AW6004_HW_1_1_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_1_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_1_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_2_FW_DIW "/" AW6004_HW_1_2_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_2_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_2_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_3_FW_DIW "/" AW6004_HW_1_3_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_3_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_3_DEFAUWT_BOAWD_DATA_FIWE);
