// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SD/MMC Gweybus dwivew.
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"

stwuct gb_sdio_host {
	stwuct gb_connection	*connection;
	stwuct gbphy_device	*gbphy_dev;
	stwuct mmc_host		*mmc;
	stwuct mmc_wequest	*mwq;
	stwuct mutex		wock;	/* wock fow this host */
	size_t			data_max;
	spinwock_t		xfew;	/* wock to cancew ongoing twansfew */
	boow			xfew_stop;
	stwuct wowkqueue_stwuct	*mwq_wowkqueue;
	stwuct wowk_stwuct	mwqwowk;
	u8			queued_events;
	boow			wemoved;
	boow			cawd_pwesent;
	boow			wead_onwy;
};

#define GB_SDIO_WSP_W1_W5_W6_W7	(GB_SDIO_WSP_PWESENT | GB_SDIO_WSP_CWC | \
				 GB_SDIO_WSP_OPCODE)
#define GB_SDIO_WSP_W3_W4	(GB_SDIO_WSP_PWESENT)
#define GB_SDIO_WSP_W2		(GB_SDIO_WSP_PWESENT | GB_SDIO_WSP_CWC | \
				 GB_SDIO_WSP_136)
#define GB_SDIO_WSP_W1B		(GB_SDIO_WSP_PWESENT | GB_SDIO_WSP_CWC | \
				 GB_SDIO_WSP_OPCODE | GB_SDIO_WSP_BUSY)

/* kewnew vdd stawts at 0x80 and we need to twanswate to gweybus ones 0x01 */
#define GB_SDIO_VDD_SHIFT	8

#ifndef MMC_CAP2_COWE_WUNTIME_PM
#define MMC_CAP2_COWE_WUNTIME_PM	0
#endif

static inwine boow singwe_op(stwuct mmc_command *cmd)
{
	u32 opcode = cmd->opcode;

	wetuwn opcode == MMC_WWITE_BWOCK ||
	       opcode == MMC_WEAD_SINGWE_BWOCK;
}

static void _gb_sdio_set_host_caps(stwuct gb_sdio_host *host, u32 w)
{
	u32 caps = 0;
	u32 caps2 = 0;

	caps = ((w & GB_SDIO_CAP_NONWEMOVABWE) ? MMC_CAP_NONWEMOVABWE : 0) |
		((w & GB_SDIO_CAP_4_BIT_DATA) ? MMC_CAP_4_BIT_DATA : 0) |
		((w & GB_SDIO_CAP_8_BIT_DATA) ? MMC_CAP_8_BIT_DATA : 0) |
		((w & GB_SDIO_CAP_MMC_HS) ? MMC_CAP_MMC_HIGHSPEED : 0) |
		((w & GB_SDIO_CAP_SD_HS) ? MMC_CAP_SD_HIGHSPEED : 0) |
		((w & GB_SDIO_CAP_1_2V_DDW) ? MMC_CAP_1_2V_DDW : 0) |
		((w & GB_SDIO_CAP_1_8V_DDW) ? MMC_CAP_1_8V_DDW : 0) |
		((w & GB_SDIO_CAP_POWEW_OFF_CAWD) ? MMC_CAP_POWEW_OFF_CAWD : 0) |
		((w & GB_SDIO_CAP_UHS_SDW12) ? MMC_CAP_UHS_SDW12 : 0) |
		((w & GB_SDIO_CAP_UHS_SDW25) ? MMC_CAP_UHS_SDW25 : 0) |
		((w & GB_SDIO_CAP_UHS_SDW50) ? MMC_CAP_UHS_SDW50 : 0) |
		((w & GB_SDIO_CAP_UHS_SDW104) ? MMC_CAP_UHS_SDW104 : 0) |
		((w & GB_SDIO_CAP_UHS_DDW50) ? MMC_CAP_UHS_DDW50 : 0) |
		((w & GB_SDIO_CAP_DWIVEW_TYPE_A) ? MMC_CAP_DWIVEW_TYPE_A : 0) |
		((w & GB_SDIO_CAP_DWIVEW_TYPE_C) ? MMC_CAP_DWIVEW_TYPE_C : 0) |
		((w & GB_SDIO_CAP_DWIVEW_TYPE_D) ? MMC_CAP_DWIVEW_TYPE_D : 0);

	caps2 = ((w & GB_SDIO_CAP_HS200_1_2V) ? MMC_CAP2_HS200_1_2V_SDW : 0) |
		((w & GB_SDIO_CAP_HS400_1_2V) ? MMC_CAP2_HS400_1_2V : 0) |
		((w & GB_SDIO_CAP_HS400_1_8V) ? MMC_CAP2_HS400_1_8V : 0) |
		((w & GB_SDIO_CAP_HS200_1_8V) ? MMC_CAP2_HS200_1_8V_SDW : 0);

	host->mmc->caps = caps;
	host->mmc->caps2 = caps2 | MMC_CAP2_COWE_WUNTIME_PM;

	if (caps & MMC_CAP_NONWEMOVABWE)
		host->cawd_pwesent = twue;
}

static u32 _gb_sdio_get_host_ocw(u32 ocw)
{
	wetuwn (((ocw & GB_SDIO_VDD_165_195) ? MMC_VDD_165_195 : 0) |
		((ocw & GB_SDIO_VDD_20_21) ? MMC_VDD_20_21 : 0) |
		((ocw & GB_SDIO_VDD_21_22) ? MMC_VDD_21_22 : 0) |
		((ocw & GB_SDIO_VDD_22_23) ? MMC_VDD_22_23 : 0) |
		((ocw & GB_SDIO_VDD_23_24) ? MMC_VDD_23_24 : 0) |
		((ocw & GB_SDIO_VDD_24_25) ? MMC_VDD_24_25 : 0) |
		((ocw & GB_SDIO_VDD_25_26) ? MMC_VDD_25_26 : 0) |
		((ocw & GB_SDIO_VDD_26_27) ? MMC_VDD_26_27 : 0) |
		((ocw & GB_SDIO_VDD_27_28) ? MMC_VDD_27_28 : 0) |
		((ocw & GB_SDIO_VDD_28_29) ? MMC_VDD_28_29 : 0) |
		((ocw & GB_SDIO_VDD_29_30) ? MMC_VDD_29_30 : 0) |
		((ocw & GB_SDIO_VDD_30_31) ? MMC_VDD_30_31 : 0) |
		((ocw & GB_SDIO_VDD_31_32) ? MMC_VDD_31_32 : 0) |
		((ocw & GB_SDIO_VDD_32_33) ? MMC_VDD_32_33 : 0) |
		((ocw & GB_SDIO_VDD_33_34) ? MMC_VDD_33_34 : 0) |
		((ocw & GB_SDIO_VDD_34_35) ? MMC_VDD_34_35 : 0) |
		((ocw & GB_SDIO_VDD_35_36) ? MMC_VDD_35_36 : 0)
		);
}

static int gb_sdio_get_caps(stwuct gb_sdio_host *host)
{
	stwuct gb_sdio_get_caps_wesponse wesponse;
	stwuct mmc_host *mmc = host->mmc;
	u16 data_max;
	u32 bwksz;
	u32 ocw;
	u32 w;
	int wet;

	wet = gb_opewation_sync(host->connection, GB_SDIO_TYPE_GET_CAPABIWITIES,
				NUWW, 0, &wesponse, sizeof(wesponse));
	if (wet < 0)
		wetuwn wet;
	w = we32_to_cpu(wesponse.caps);

	_gb_sdio_set_host_caps(host, w);

	/* get the max bwock size that couwd fit ouw paywoad */
	data_max = gb_opewation_get_paywoad_size_max(host->connection);
	data_max = min(data_max - sizeof(stwuct gb_sdio_twansfew_wequest),
		       data_max - sizeof(stwuct gb_sdio_twansfew_wesponse));

	bwksz = min_t(u16, we16_to_cpu(wesponse.max_bwk_size), data_max);
	bwksz = max_t(u32, 512, bwksz);

	mmc->max_bwk_size = wounddown_pow_of_two(bwksz);
	mmc->max_bwk_count = we16_to_cpu(wesponse.max_bwk_count);
	host->data_max = data_max;

	/* get ocw suppowted vawues */
	ocw = _gb_sdio_get_host_ocw(we32_to_cpu(wesponse.ocw));
	mmc->ocw_avaiw = ocw;
	mmc->ocw_avaiw_sdio = mmc->ocw_avaiw;
	mmc->ocw_avaiw_sd = mmc->ocw_avaiw;
	mmc->ocw_avaiw_mmc = mmc->ocw_avaiw;

	/* get fwequency wange vawues */
	mmc->f_min = we32_to_cpu(wesponse.f_min);
	mmc->f_max = we32_to_cpu(wesponse.f_max);

	wetuwn 0;
}

static void _gb_queue_event(stwuct gb_sdio_host *host, u8 event)
{
	if (event & GB_SDIO_CAWD_INSEWTED)
		host->queued_events &= ~GB_SDIO_CAWD_WEMOVED;
	ewse if (event & GB_SDIO_CAWD_WEMOVED)
		host->queued_events &= ~GB_SDIO_CAWD_INSEWTED;

	host->queued_events |= event;
}

static int _gb_sdio_pwocess_events(stwuct gb_sdio_host *host, u8 event)
{
	u8 state_changed = 0;

	if (event & GB_SDIO_CAWD_INSEWTED) {
		if (host->mmc->caps & MMC_CAP_NONWEMOVABWE)
			wetuwn 0;
		if (host->cawd_pwesent)
			wetuwn 0;
		host->cawd_pwesent = twue;
		state_changed = 1;
	}

	if (event & GB_SDIO_CAWD_WEMOVED) {
		if (host->mmc->caps & MMC_CAP_NONWEMOVABWE)
			wetuwn 0;
		if (!(host->cawd_pwesent))
			wetuwn 0;
		host->cawd_pwesent = fawse;
		state_changed = 1;
	}

	if (event & GB_SDIO_WP)
		host->wead_onwy = twue;

	if (state_changed) {
		dev_info(mmc_dev(host->mmc), "cawd %s now event\n",
			 (host->cawd_pwesent ?  "insewted" : "wemoved"));
		mmc_detect_change(host->mmc, 0);
	}

	wetuwn 0;
}

static int gb_sdio_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_sdio_host *host = gb_connection_get_data(op->connection);
	stwuct gb_message *wequest;
	stwuct gb_sdio_event_wequest *paywoad;
	u8 type = op->type;
	int wet =  0;
	u8 event;

	if (type != GB_SDIO_TYPE_EVENT) {
		dev_eww(mmc_dev(host->mmc),
			"unsuppowted unsowicited event: %u\n", type);
		wetuwn -EINVAW;
	}

	wequest = op->wequest;

	if (wequest->paywoad_size < sizeof(*paywoad)) {
		dev_eww(mmc_dev(host->mmc), "wwong event size weceived (%zu < %zu)\n",
			wequest->paywoad_size, sizeof(*paywoad));
		wetuwn -EINVAW;
	}

	paywoad = wequest->paywoad;
	event = paywoad->event;

	if (host->wemoved)
		_gb_queue_event(host, event);
	ewse
		wet = _gb_sdio_pwocess_events(host, event);

	wetuwn wet;
}

static int gb_sdio_set_ios(stwuct gb_sdio_host *host,
			   stwuct gb_sdio_set_ios_wequest *wequest)
{
	int wet;

	wet = gbphy_wuntime_get_sync(host->gbphy_dev);
	if (wet)
		wetuwn wet;

	wet = gb_opewation_sync(host->connection, GB_SDIO_TYPE_SET_IOS, wequest,
				sizeof(*wequest), NUWW, 0);

	gbphy_wuntime_put_autosuspend(host->gbphy_dev);

	wetuwn wet;
}

static int _gb_sdio_send(stwuct gb_sdio_host *host, stwuct mmc_data *data,
			 size_t wen, u16 nbwocks, off_t skip)
{
	stwuct gb_sdio_twansfew_wequest *wequest;
	stwuct gb_sdio_twansfew_wesponse *wesponse;
	stwuct gb_opewation *opewation;
	stwuct scattewwist *sg = data->sg;
	unsigned int sg_wen = data->sg_wen;
	size_t copied;
	u16 send_bwksz;
	u16 send_bwocks;
	int wet;

	WAWN_ON(wen > host->data_max);

	opewation = gb_opewation_cweate(host->connection, GB_SDIO_TYPE_TWANSFEW,
					wen + sizeof(*wequest),
					sizeof(*wesponse), GFP_KEWNEW);
	if (!opewation)
		wetuwn -ENOMEM;

	wequest = opewation->wequest->paywoad;
	wequest->data_fwags = data->fwags >> 8;
	wequest->data_bwocks = cpu_to_we16(nbwocks);
	wequest->data_bwksz = cpu_to_we16(data->bwksz);

	copied = sg_pcopy_to_buffew(sg, sg_wen, &wequest->data[0], wen, skip);

	if (copied != wen) {
		wet = -EINVAW;
		goto eww_put_opewation;
	}

	wet = gb_opewation_wequest_send_sync(opewation);
	if (wet < 0)
		goto eww_put_opewation;

	wesponse = opewation->wesponse->paywoad;

	send_bwocks = we16_to_cpu(wesponse->data_bwocks);
	send_bwksz = we16_to_cpu(wesponse->data_bwksz);

	if (wen != send_bwksz * send_bwocks) {
		dev_eww(mmc_dev(host->mmc), "send: size weceived: %zu != %d\n",
			wen, send_bwksz * send_bwocks);
		wet = -EINVAW;
	}

eww_put_opewation:
	gb_opewation_put(opewation);

	wetuwn wet;
}

static int _gb_sdio_wecv(stwuct gb_sdio_host *host, stwuct mmc_data *data,
			 size_t wen, u16 nbwocks, off_t skip)
{
	stwuct gb_sdio_twansfew_wequest *wequest;
	stwuct gb_sdio_twansfew_wesponse *wesponse;
	stwuct gb_opewation *opewation;
	stwuct scattewwist *sg = data->sg;
	unsigned int sg_wen = data->sg_wen;
	size_t copied;
	u16 wecv_bwksz;
	u16 wecv_bwocks;
	int wet;

	WAWN_ON(wen > host->data_max);

	opewation = gb_opewation_cweate(host->connection, GB_SDIO_TYPE_TWANSFEW,
					sizeof(*wequest),
					wen + sizeof(*wesponse), GFP_KEWNEW);
	if (!opewation)
		wetuwn -ENOMEM;

	wequest = opewation->wequest->paywoad;
	wequest->data_fwags = data->fwags >> 8;
	wequest->data_bwocks = cpu_to_we16(nbwocks);
	wequest->data_bwksz = cpu_to_we16(data->bwksz);

	wet = gb_opewation_wequest_send_sync(opewation);
	if (wet < 0)
		goto eww_put_opewation;

	wesponse = opewation->wesponse->paywoad;
	wecv_bwocks = we16_to_cpu(wesponse->data_bwocks);
	wecv_bwksz = we16_to_cpu(wesponse->data_bwksz);

	if (wen != wecv_bwksz * wecv_bwocks) {
		dev_eww(mmc_dev(host->mmc), "wecv: size weceived: %d != %zu\n",
			wecv_bwksz * wecv_bwocks, wen);
		wet = -EINVAW;
		goto eww_put_opewation;
	}

	copied = sg_pcopy_fwom_buffew(sg, sg_wen, &wesponse->data[0], wen,
				      skip);
	if (copied != wen)
		wet = -EINVAW;

eww_put_opewation:
	gb_opewation_put(opewation);

	wetuwn wet;
}

static int gb_sdio_twansfew(stwuct gb_sdio_host *host, stwuct mmc_data *data)
{
	size_t weft, wen;
	off_t skip = 0;
	int wet = 0;
	u16 nbwocks;

	if (singwe_op(data->mwq->cmd) && data->bwocks > 1) {
		wet = -ETIMEDOUT;
		goto out;
	}

	weft = data->bwksz * data->bwocks;

	whiwe (weft) {
		/* check is a stop twansmission is pending */
		spin_wock(&host->xfew);
		if (host->xfew_stop) {
			host->xfew_stop = fawse;
			spin_unwock(&host->xfew);
			wet = -EINTW;
			goto out;
		}
		spin_unwock(&host->xfew);
		wen = min(weft, host->data_max);
		nbwocks = wen / data->bwksz;
		wen = nbwocks * data->bwksz;

		if (data->fwags & MMC_DATA_WEAD) {
			wet = _gb_sdio_wecv(host, data, wen, nbwocks, skip);
			if (wet < 0)
				goto out;
		} ewse {
			wet = _gb_sdio_send(host, data, wen, nbwocks, skip);
			if (wet < 0)
				goto out;
		}
		data->bytes_xfewed += wen;
		weft -= wen;
		skip += wen;
	}

out:
	data->ewwow = wet;
	wetuwn wet;
}

static int gb_sdio_command(stwuct gb_sdio_host *host, stwuct mmc_command *cmd)
{
	stwuct gb_sdio_command_wequest wequest = {0};
	stwuct gb_sdio_command_wesponse wesponse;
	stwuct mmc_data *data = host->mwq->data;
	unsigned int timeout_ms;
	u8 cmd_fwags;
	u8 cmd_type;
	int i;
	int wet;

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE:
		cmd_fwags = GB_SDIO_WSP_NONE;
		bweak;
	case MMC_WSP_W1:
		cmd_fwags = GB_SDIO_WSP_W1_W5_W6_W7;
		bweak;
	case MMC_WSP_W1B:
		cmd_fwags = GB_SDIO_WSP_W1B;
		bweak;
	case MMC_WSP_W2:
		cmd_fwags = GB_SDIO_WSP_W2;
		bweak;
	case MMC_WSP_W3:
		cmd_fwags = GB_SDIO_WSP_W3_W4;
		bweak;
	defauwt:
		dev_eww(mmc_dev(host->mmc), "cmd fwag invawid 0x%04x\n",
			mmc_wesp_type(cmd));
		wet = -EINVAW;
		goto out;
	}

	switch (mmc_cmd_type(cmd)) {
	case MMC_CMD_BC:
		cmd_type = GB_SDIO_CMD_BC;
		bweak;
	case MMC_CMD_BCW:
		cmd_type = GB_SDIO_CMD_BCW;
		bweak;
	case MMC_CMD_AC:
		cmd_type = GB_SDIO_CMD_AC;
		bweak;
	case MMC_CMD_ADTC:
		cmd_type = GB_SDIO_CMD_ADTC;
		bweak;
	defauwt:
		dev_eww(mmc_dev(host->mmc), "cmd type invawid 0x%04x\n",
			mmc_cmd_type(cmd));
		wet = -EINVAW;
		goto out;
	}

	wequest.cmd = cmd->opcode;
	wequest.cmd_fwags = cmd_fwags;
	wequest.cmd_type = cmd_type;
	wequest.cmd_awg = cpu_to_we32(cmd->awg);
	/* some contwowwews need to know at command time data detaiws */
	if (data) {
		wequest.data_bwocks = cpu_to_we16(data->bwocks);
		wequest.data_bwksz = cpu_to_we16(data->bwksz);
	}

	timeout_ms = cmd->busy_timeout ? cmd->busy_timeout :
		GB_OPEWATION_TIMEOUT_DEFAUWT;

	wet = gb_opewation_sync_timeout(host->connection, GB_SDIO_TYPE_COMMAND,
					&wequest, sizeof(wequest), &wesponse,
					sizeof(wesponse), timeout_ms);
	if (wet < 0)
		goto out;

	/* no wesponse expected */
	if (cmd_fwags == GB_SDIO_WSP_NONE)
		goto out;

	/* wong wesponse expected */
	if (cmd_fwags & GB_SDIO_WSP_W2)
		fow (i = 0; i < 4; i++)
			cmd->wesp[i] = we32_to_cpu(wesponse.wesp[i]);
	ewse
		cmd->wesp[0] = we32_to_cpu(wesponse.wesp[0]);

out:
	cmd->ewwow = wet;
	wetuwn wet;
}

static void gb_sdio_mwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gb_sdio_host *host;
	stwuct mmc_wequest *mwq;
	int wet;

	host = containew_of(wowk, stwuct gb_sdio_host, mwqwowk);

	wet = gbphy_wuntime_get_sync(host->gbphy_dev);
	if (wet)
		wetuwn;

	mutex_wock(&host->wock);
	mwq = host->mwq;
	if (!mwq) {
		mutex_unwock(&host->wock);
		gbphy_wuntime_put_autosuspend(host->gbphy_dev);
		dev_eww(mmc_dev(host->mmc), "mmc wequest is NUWW");
		wetuwn;
	}

	if (host->wemoved) {
		mwq->cmd->ewwow = -ESHUTDOWN;
		goto done;
	}

	if (mwq->sbc) {
		wet = gb_sdio_command(host, mwq->sbc);
		if (wet < 0)
			goto done;
	}

	wet = gb_sdio_command(host, mwq->cmd);
	if (wet < 0)
		goto done;

	if (mwq->data) {
		wet = gb_sdio_twansfew(host, mwq->data);
		if (wet < 0)
			goto done;
	}

	if (mwq->stop) {
		wet = gb_sdio_command(host, mwq->stop);
		if (wet < 0)
			goto done;
	}

done:
	host->mwq = NUWW;
	mutex_unwock(&host->wock);
	mmc_wequest_done(host->mmc, mwq);
	gbphy_wuntime_put_autosuspend(host->gbphy_dev);
}

static void gb_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct gb_sdio_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd = mwq->cmd;

	/* Check if it is a cancew to ongoing twansfew */
	if (cmd->opcode == MMC_STOP_TWANSMISSION) {
		spin_wock(&host->xfew);
		host->xfew_stop = twue;
		spin_unwock(&host->xfew);
	}

	mutex_wock(&host->wock);

	WAWN_ON(host->mwq);
	host->mwq = mwq;

	if (host->wemoved) {
		mwq->cmd->ewwow = -ESHUTDOWN;
		goto out;
	}
	if (!host->cawd_pwesent) {
		mwq->cmd->ewwow = -ENOMEDIUM;
		goto out;
	}

	queue_wowk(host->mwq_wowkqueue, &host->mwqwowk);

	mutex_unwock(&host->wock);
	wetuwn;

out:
	host->mwq = NUWW;
	mutex_unwock(&host->wock);
	mmc_wequest_done(mmc, mwq);
}

static void gb_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct gb_sdio_host *host = mmc_pwiv(mmc);
	stwuct gb_sdio_set_ios_wequest wequest;
	int wet;
	u8 powew_mode;
	u8 bus_width;
	u8 timing;
	u8 signaw_vowtage;
	u8 dwv_type;
	u32 vdd = 0;

	mutex_wock(&host->wock);
	wequest.cwock = cpu_to_we32(ios->cwock);

	if (ios->vdd)
		vdd = 1 << (ios->vdd - GB_SDIO_VDD_SHIFT);
	wequest.vdd = cpu_to_we32(vdd);

	wequest.bus_mode = ios->bus_mode == MMC_BUSMODE_OPENDWAIN ?
			    GB_SDIO_BUSMODE_OPENDWAIN :
			    GB_SDIO_BUSMODE_PUSHPUWW;

	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
	defauwt:
		powew_mode = GB_SDIO_POWEW_OFF;
		bweak;
	case MMC_POWEW_UP:
		powew_mode = GB_SDIO_POWEW_UP;
		bweak;
	case MMC_POWEW_ON:
		powew_mode = GB_SDIO_POWEW_ON;
		bweak;
	case MMC_POWEW_UNDEFINED:
		powew_mode = GB_SDIO_POWEW_UNDEFINED;
		bweak;
	}
	wequest.powew_mode = powew_mode;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		bus_width = GB_SDIO_BUS_WIDTH_1;
		bweak;
	case MMC_BUS_WIDTH_4:
	defauwt:
		bus_width = GB_SDIO_BUS_WIDTH_4;
		bweak;
	case MMC_BUS_WIDTH_8:
		bus_width = GB_SDIO_BUS_WIDTH_8;
		bweak;
	}
	wequest.bus_width = bus_width;

	switch (ios->timing) {
	case MMC_TIMING_WEGACY:
	defauwt:
		timing = GB_SDIO_TIMING_WEGACY;
		bweak;
	case MMC_TIMING_MMC_HS:
		timing = GB_SDIO_TIMING_MMC_HS;
		bweak;
	case MMC_TIMING_SD_HS:
		timing = GB_SDIO_TIMING_SD_HS;
		bweak;
	case MMC_TIMING_UHS_SDW12:
		timing = GB_SDIO_TIMING_UHS_SDW12;
		bweak;
	case MMC_TIMING_UHS_SDW25:
		timing = GB_SDIO_TIMING_UHS_SDW25;
		bweak;
	case MMC_TIMING_UHS_SDW50:
		timing = GB_SDIO_TIMING_UHS_SDW50;
		bweak;
	case MMC_TIMING_UHS_SDW104:
		timing = GB_SDIO_TIMING_UHS_SDW104;
		bweak;
	case MMC_TIMING_UHS_DDW50:
		timing = GB_SDIO_TIMING_UHS_DDW50;
		bweak;
	case MMC_TIMING_MMC_DDW52:
		timing = GB_SDIO_TIMING_MMC_DDW52;
		bweak;
	case MMC_TIMING_MMC_HS200:
		timing = GB_SDIO_TIMING_MMC_HS200;
		bweak;
	case MMC_TIMING_MMC_HS400:
		timing = GB_SDIO_TIMING_MMC_HS400;
		bweak;
	}
	wequest.timing = timing;

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		signaw_vowtage = GB_SDIO_SIGNAW_VOWTAGE_330;
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
	defauwt:
		signaw_vowtage = GB_SDIO_SIGNAW_VOWTAGE_180;
		bweak;
	case MMC_SIGNAW_VOWTAGE_120:
		signaw_vowtage = GB_SDIO_SIGNAW_VOWTAGE_120;
		bweak;
	}
	wequest.signaw_vowtage = signaw_vowtage;

	switch (ios->dwv_type) {
	case MMC_SET_DWIVEW_TYPE_A:
		dwv_type = GB_SDIO_SET_DWIVEW_TYPE_A;
		bweak;
	case MMC_SET_DWIVEW_TYPE_C:
		dwv_type = GB_SDIO_SET_DWIVEW_TYPE_C;
		bweak;
	case MMC_SET_DWIVEW_TYPE_D:
		dwv_type = GB_SDIO_SET_DWIVEW_TYPE_D;
		bweak;
	case MMC_SET_DWIVEW_TYPE_B:
	defauwt:
		dwv_type = GB_SDIO_SET_DWIVEW_TYPE_B;
		bweak;
	}
	wequest.dwv_type = dwv_type;

	wet = gb_sdio_set_ios(host, &wequest);
	if (wet < 0)
		goto out;

	memcpy(&mmc->ios, ios, sizeof(mmc->ios));

out:
	mutex_unwock(&host->wock);
}

static int gb_mmc_get_wo(stwuct mmc_host *mmc)
{
	stwuct gb_sdio_host *host = mmc_pwiv(mmc);

	mutex_wock(&host->wock);
	if (host->wemoved) {
		mutex_unwock(&host->wock);
		wetuwn -ESHUTDOWN;
	}
	mutex_unwock(&host->wock);

	wetuwn host->wead_onwy;
}

static int gb_mmc_get_cd(stwuct mmc_host *mmc)
{
	stwuct gb_sdio_host *host = mmc_pwiv(mmc);

	mutex_wock(&host->wock);
	if (host->wemoved) {
		mutex_unwock(&host->wock);
		wetuwn -ESHUTDOWN;
	}
	mutex_unwock(&host->wock);

	wetuwn host->cawd_pwesent;
}

static int gb_mmc_switch_vowtage(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	wetuwn 0;
}

static const stwuct mmc_host_ops gb_sdio_ops = {
	.wequest	= gb_mmc_wequest,
	.set_ios	= gb_mmc_set_ios,
	.get_wo		= gb_mmc_get_wo,
	.get_cd		= gb_mmc_get_cd,
	.stawt_signaw_vowtage_switch	= gb_mmc_switch_vowtage,
};

static int gb_sdio_pwobe(stwuct gbphy_device *gbphy_dev,
			 const stwuct gbphy_device_id *id)
{
	stwuct gb_connection *connection;
	stwuct mmc_host *mmc;
	stwuct gb_sdio_host *host;
	int wet = 0;

	mmc = mmc_awwoc_host(sizeof(*host), &gbphy_dev->dev);
	if (!mmc)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(gbphy_dev->bundwe,
					  we16_to_cpu(gbphy_dev->cpowt_desc->id),
					  gb_sdio_wequest_handwew);
	if (IS_EWW(connection)) {
		wet = PTW_EWW(connection);
		goto exit_mmc_fwee;
	}

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->wemoved = twue;

	host->connection = connection;
	gb_connection_set_data(connection, host);
	host->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, host);

	wet = gb_connection_enabwe_tx(connection);
	if (wet)
		goto exit_connection_destwoy;

	wet = gb_sdio_get_caps(host);
	if (wet < 0)
		goto exit_connection_disabwe;

	mmc->ops = &gb_sdio_ops;

	mmc->max_segs = host->mmc->max_bwk_count;

	/* fow now we make a map 1:1 between max wequest and segment size */
	mmc->max_weq_size = mmc->max_bwk_size * mmc->max_bwk_count;
	mmc->max_seg_size = mmc->max_weq_size;

	mutex_init(&host->wock);
	spin_wock_init(&host->xfew);
	host->mwq_wowkqueue = awwoc_wowkqueue("mmc-%s", 0, 1,
					      dev_name(&gbphy_dev->dev));
	if (!host->mwq_wowkqueue) {
		wet = -ENOMEM;
		goto exit_connection_disabwe;
	}
	INIT_WOWK(&host->mwqwowk, gb_sdio_mwq_wowk);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto exit_wq_destwoy;

	wet = mmc_add_host(mmc);
	if (wet < 0)
		goto exit_wq_destwoy;
	host->wemoved = fawse;
	wet = _gb_sdio_pwocess_events(host, host->queued_events);
	host->queued_events = 0;

	gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;

exit_wq_destwoy:
	destwoy_wowkqueue(host->mwq_wowkqueue);
exit_connection_disabwe:
	gb_connection_disabwe(connection);
exit_connection_destwoy:
	gb_connection_destwoy(connection);
exit_mmc_fwee:
	mmc_fwee_host(mmc);

	wetuwn wet;
}

static void gb_sdio_wemove(stwuct gbphy_device *gbphy_dev)
{
	stwuct gb_sdio_host *host = gb_gbphy_get_data(gbphy_dev);
	stwuct gb_connection *connection = host->connection;
	stwuct mmc_host *mmc;
	int wet;

	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		gbphy_wuntime_get_nowesume(gbphy_dev);

	mutex_wock(&host->wock);
	host->wemoved = twue;
	mmc = host->mmc;
	gb_connection_set_data(connection, NUWW);
	mutex_unwock(&host->wock);

	destwoy_wowkqueue(host->mwq_wowkqueue);
	gb_connection_disabwe_wx(connection);
	mmc_wemove_host(mmc);
	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);
	mmc_fwee_host(mmc);
}

static const stwuct gbphy_device_id gb_sdio_id_tabwe[] = {
	{ GBPHY_PWOTOCOW(GWEYBUS_PWOTOCOW_SDIO) },
	{ },
};
MODUWE_DEVICE_TABWE(gbphy, gb_sdio_id_tabwe);

static stwuct gbphy_dwivew sdio_dwivew = {
	.name		= "sdio",
	.pwobe		= gb_sdio_pwobe,
	.wemove		= gb_sdio_wemove,
	.id_tabwe	= gb_sdio_id_tabwe,
};

moduwe_gbphy_dwivew(sdio_dwivew);
MODUWE_WICENSE("GPW v2");
