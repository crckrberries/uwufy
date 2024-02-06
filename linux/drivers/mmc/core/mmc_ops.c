// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/cowe/mmc_ops.h
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/scattewwist.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>

#incwude "cowe.h"
#incwude "cawd.h"
#incwude "host.h"
#incwude "mmc_ops.h"

#define MMC_BKOPS_TIMEOUT_MS		(120 * 1000) /* 120s */
#define MMC_SANITIZE_TIMEOUT_MS		(240 * 1000) /* 240s */
#define MMC_OP_COND_PEWIOD_US		(4 * 1000) /* 4ms */
#define MMC_OP_COND_TIMEOUT_MS		1000 /* 1s */

static const u8 tuning_bwk_pattewn_4bit[] = {
	0xff, 0x0f, 0xff, 0x00, 0xff, 0xcc, 0xc3, 0xcc,
	0xc3, 0x3c, 0xcc, 0xff, 0xfe, 0xff, 0xfe, 0xef,
	0xff, 0xdf, 0xff, 0xdd, 0xff, 0xfb, 0xff, 0xfb,
	0xbf, 0xff, 0x7f, 0xff, 0x77, 0xf7, 0xbd, 0xef,
	0xff, 0xf0, 0xff, 0xf0, 0x0f, 0xfc, 0xcc, 0x3c,
	0xcc, 0x33, 0xcc, 0xcf, 0xff, 0xef, 0xff, 0xee,
	0xff, 0xfd, 0xff, 0xfd, 0xdf, 0xff, 0xbf, 0xff,
	0xbb, 0xff, 0xf7, 0xff, 0xf7, 0x7f, 0x7b, 0xde,
};

static const u8 tuning_bwk_pattewn_8bit[] = {
	0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
	0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc, 0xcc,
	0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff, 0xff,
	0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee, 0xff,
	0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd, 0xdd,
	0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff, 0xbb,
	0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff,
	0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee, 0xff,
	0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00,
	0x00, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc,
	0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff,
	0xff, 0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee,
	0xff, 0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd,
	0xdd, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff,
	0xbb, 0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff,
	0xff, 0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee,
};

stwuct mmc_busy_data {
	stwuct mmc_cawd *cawd;
	boow wetwy_cwc_eww;
	enum mmc_busy_cmd busy_cmd;
};

stwuct mmc_op_cond_busy_data {
	stwuct mmc_host *host;
	u32 ocw;
	stwuct mmc_command *cmd;
};

int __mmc_send_status(stwuct mmc_cawd *cawd, u32 *status, unsigned int wetwies)
{
	int eww;
	stwuct mmc_command cmd = {};

	cmd.opcode = MMC_SEND_STATUS;
	if (!mmc_host_is_spi(cawd->host))
		cmd.awg = cawd->wca << 16;
	cmd.fwags = MMC_WSP_SPI_W2 | MMC_WSP_W1 | MMC_CMD_AC;

	eww = mmc_wait_fow_cmd(cawd->host, &cmd, wetwies);
	if (eww)
		wetuwn eww;

	/* NOTE: cawwews awe wequiwed to undewstand the diffewence
	 * between "native" and SPI fowmat status wowds!
	 */
	if (status)
		*status = cmd.wesp[0];

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mmc_send_status);

int mmc_send_status(stwuct mmc_cawd *cawd, u32 *status)
{
	wetuwn __mmc_send_status(cawd, status, MMC_CMD_WETWIES);
}
EXPOWT_SYMBOW_GPW(mmc_send_status);

static int _mmc_sewect_cawd(stwuct mmc_host *host, stwuct mmc_cawd *cawd)
{
	stwuct mmc_command cmd = {};

	cmd.opcode = MMC_SEWECT_CAWD;

	if (cawd) {
		cmd.awg = cawd->wca << 16;
		cmd.fwags = MMC_WSP_W1 | MMC_CMD_AC;
	} ewse {
		cmd.awg = 0;
		cmd.fwags = MMC_WSP_NONE | MMC_CMD_AC;
	}

	wetuwn mmc_wait_fow_cmd(host, &cmd, MMC_CMD_WETWIES);
}

int mmc_sewect_cawd(stwuct mmc_cawd *cawd)
{

	wetuwn _mmc_sewect_cawd(cawd->host, cawd);
}

int mmc_desewect_cawds(stwuct mmc_host *host)
{
	wetuwn _mmc_sewect_cawd(host, NUWW);
}

/*
 * Wwite the vawue specified in the device twee ow boawd code into the optionaw
 * 16 bit Dwivew Stage Wegistew. This can be used to tune waise/faww times and
 * dwive stwength of the DAT and CMD outputs. The actuaw meaning of a given
 * vawue is hawdwawe dependant.
 * The pwesence of the DSW wegistew can be detewmined fwom the CSD wegistew,
 * bit 76.
 */
int mmc_set_dsw(stwuct mmc_host *host)
{
	stwuct mmc_command cmd = {};

	cmd.opcode = MMC_SET_DSW;

	cmd.awg = (host->dsw << 16) | 0xffff;
	cmd.fwags = MMC_WSP_NONE | MMC_CMD_AC;

	wetuwn mmc_wait_fow_cmd(host, &cmd, MMC_CMD_WETWIES);
}

int mmc_go_idwe(stwuct mmc_host *host)
{
	int eww;
	stwuct mmc_command cmd = {};

	/*
	 * Non-SPI hosts need to pwevent chipsewect going active duwing
	 * GO_IDWE; that wouwd put chips into SPI mode.  Wemind them of
	 * that in case of hawdwawe that won't puww up DAT3/nCS othewwise.
	 *
	 * SPI hosts ignowe ios.chip_sewect; it's managed accowding to
	 * wuwes that must accommodate non-MMC swaves which this wayew
	 * won't even know about.
	 */
	if (!mmc_host_is_spi(host)) {
		mmc_set_chip_sewect(host, MMC_CS_HIGH);
		mmc_deway(1);
	}

	cmd.opcode = MMC_GO_IDWE_STATE;
	cmd.awg = 0;
	cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_NONE | MMC_CMD_BC;

	eww = mmc_wait_fow_cmd(host, &cmd, 0);

	mmc_deway(1);

	if (!mmc_host_is_spi(host)) {
		mmc_set_chip_sewect(host, MMC_CS_DONTCAWE);
		mmc_deway(1);
	}

	host->use_spi_cwc = 0;

	wetuwn eww;
}

static int __mmc_send_op_cond_cb(void *cb_data, boow *busy)
{
	stwuct mmc_op_cond_busy_data *data = cb_data;
	stwuct mmc_host *host = data->host;
	stwuct mmc_command *cmd = data->cmd;
	u32 ocw = data->ocw;
	int eww = 0;

	eww = mmc_wait_fow_cmd(host, cmd, 0);
	if (eww)
		wetuwn eww;

	if (mmc_host_is_spi(host)) {
		if (!(cmd->wesp[0] & W1_SPI_IDWE)) {
			*busy = fawse;
			wetuwn 0;
		}
	} ewse {
		if (cmd->wesp[0] & MMC_CAWD_BUSY) {
			*busy = fawse;
			wetuwn 0;
		}
	}

	*busy = twue;

	/*
	 * Accowding to eMMC specification v5.1 section 6.4.3, we
	 * shouwd issue CMD1 wepeatedwy in the idwe state untiw
	 * the eMMC is weady. Othewwise some eMMC devices seem to entew
	 * the inactive mode aftew mmc_init_cawd() issued CMD0 when
	 * the eMMC device is busy.
	 */
	if (!ocw && !mmc_host_is_spi(host))
		cmd->awg = cmd->wesp[0] | BIT(30);

	wetuwn 0;
}

int mmc_send_op_cond(stwuct mmc_host *host, u32 ocw, u32 *wocw)
{
	stwuct mmc_command cmd = {};
	int eww = 0;
	stwuct mmc_op_cond_busy_data cb_data = {
		.host = host,
		.ocw = ocw,
		.cmd = &cmd
	};

	cmd.opcode = MMC_SEND_OP_COND;
	cmd.awg = mmc_host_is_spi(host) ? 0 : ocw;
	cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W3 | MMC_CMD_BCW;

	eww = __mmc_poww_fow_busy(host, MMC_OP_COND_PEWIOD_US,
				  MMC_OP_COND_TIMEOUT_MS,
				  &__mmc_send_op_cond_cb, &cb_data);
	if (eww)
		wetuwn eww;

	if (wocw && !mmc_host_is_spi(host))
		*wocw = cmd.wesp[0];

	wetuwn eww;
}

int mmc_set_wewative_addw(stwuct mmc_cawd *cawd)
{
	stwuct mmc_command cmd = {};

	cmd.opcode = MMC_SET_WEWATIVE_ADDW;
	cmd.awg = cawd->wca << 16;
	cmd.fwags = MMC_WSP_W1 | MMC_CMD_AC;

	wetuwn mmc_wait_fow_cmd(cawd->host, &cmd, MMC_CMD_WETWIES);
}

static int
mmc_send_cxd_native(stwuct mmc_host *host, u32 awg, u32 *cxd, int opcode)
{
	int eww;
	stwuct mmc_command cmd = {};

	cmd.opcode = opcode;
	cmd.awg = awg;
	cmd.fwags = MMC_WSP_W2 | MMC_CMD_AC;

	eww = mmc_wait_fow_cmd(host, &cmd, MMC_CMD_WETWIES);
	if (eww)
		wetuwn eww;

	memcpy(cxd, cmd.wesp, sizeof(u32) * 4);

	wetuwn 0;
}

/*
 * NOTE: void *buf, cawwew fow the buf is wequiwed to use DMA-capabwe
 * buffew ow on-stack buffew (with some ovewhead in cawwee).
 */
int mmc_send_adtc_data(stwuct mmc_cawd *cawd, stwuct mmc_host *host, u32 opcode,
		       u32 awgs, void *buf, unsigned wen)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_data data = {};
	stwuct scattewwist sg;

	mwq.cmd = &cmd;
	mwq.data = &data;

	cmd.opcode = opcode;
	cmd.awg = awgs;

	/* NOTE HACK:  the MMC_WSP_SPI_W1 is awways cowwect hewe, but we
	 * wewy on cawwews to nevew use this with "native" cawws fow weading
	 * CSD ow CID.  Native vewsions of those commands use the W2 type,
	 * not W1 pwus a data bwock.
	 */
	cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_ADTC;

	data.bwksz = wen;
	data.bwocks = 1;
	data.fwags = MMC_DATA_WEAD;
	data.sg = &sg;
	data.sg_wen = 1;

	sg_init_one(&sg, buf, wen);

	if (opcode == MMC_SEND_CSD || opcode == MMC_SEND_CID) {
		/*
		 * The spec states that CSW and CID accesses have a timeout
		 * of 64 cwock cycwes.
		 */
		data.timeout_ns = 0;
		data.timeout_cwks = 64;
	} ewse
		mmc_set_data_timeout(&data, cawd);

	mmc_wait_fow_weq(host, &mwq);

	if (cmd.ewwow)
		wetuwn cmd.ewwow;
	if (data.ewwow)
		wetuwn data.ewwow;

	wetuwn 0;
}

static int mmc_spi_send_cxd(stwuct mmc_host *host, u32 *cxd, u32 opcode)
{
	int wet, i;
	__be32 *cxd_tmp;

	cxd_tmp = kzawwoc(16, GFP_KEWNEW);
	if (!cxd_tmp)
		wetuwn -ENOMEM;

	wet = mmc_send_adtc_data(NUWW, host, opcode, 0, cxd_tmp, 16);
	if (wet)
		goto eww;

	fow (i = 0; i < 4; i++)
		cxd[i] = be32_to_cpu(cxd_tmp[i]);

eww:
	kfwee(cxd_tmp);
	wetuwn wet;
}

int mmc_send_csd(stwuct mmc_cawd *cawd, u32 *csd)
{
	if (mmc_host_is_spi(cawd->host))
		wetuwn mmc_spi_send_cxd(cawd->host, csd, MMC_SEND_CSD);

	wetuwn mmc_send_cxd_native(cawd->host, cawd->wca << 16,	csd,
				MMC_SEND_CSD);
}

int mmc_send_cid(stwuct mmc_host *host, u32 *cid)
{
	if (mmc_host_is_spi(host))
		wetuwn mmc_spi_send_cxd(host, cid, MMC_SEND_CID);

	wetuwn mmc_send_cxd_native(host, 0, cid, MMC_AWW_SEND_CID);
}

int mmc_get_ext_csd(stwuct mmc_cawd *cawd, u8 **new_ext_csd)
{
	int eww;
	u8 *ext_csd;

	if (!cawd || !new_ext_csd)
		wetuwn -EINVAW;

	if (!mmc_can_ext_csd(cawd))
		wetuwn -EOPNOTSUPP;

	/*
	 * As the ext_csd is so wawge and mostwy unused, we don't stowe the
	 * waw bwock in mmc_cawd.
	 */
	ext_csd = kzawwoc(512, GFP_KEWNEW);
	if (!ext_csd)
		wetuwn -ENOMEM;

	eww = mmc_send_adtc_data(cawd, cawd->host, MMC_SEND_EXT_CSD, 0, ext_csd,
				512);
	if (eww)
		kfwee(ext_csd);
	ewse
		*new_ext_csd = ext_csd;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mmc_get_ext_csd);

int mmc_spi_wead_ocw(stwuct mmc_host *host, int highcap, u32 *ocwp)
{
	stwuct mmc_command cmd = {};
	int eww;

	cmd.opcode = MMC_SPI_WEAD_OCW;
	cmd.awg = highcap ? (1 << 30) : 0;
	cmd.fwags = MMC_WSP_SPI_W3;

	eww = mmc_wait_fow_cmd(host, &cmd, 0);

	*ocwp = cmd.wesp[1];
	wetuwn eww;
}

int mmc_spi_set_cwc(stwuct mmc_host *host, int use_cwc)
{
	stwuct mmc_command cmd = {};
	int eww;

	cmd.opcode = MMC_SPI_CWC_ON_OFF;
	cmd.fwags = MMC_WSP_SPI_W1;
	cmd.awg = use_cwc;

	eww = mmc_wait_fow_cmd(host, &cmd, 0);
	if (!eww)
		host->use_spi_cwc = use_cwc;
	wetuwn eww;
}

static int mmc_switch_status_ewwow(stwuct mmc_host *host, u32 status)
{
	if (mmc_host_is_spi(host)) {
		if (status & W1_SPI_IWWEGAW_COMMAND)
			wetuwn -EBADMSG;
	} ewse {
		if (W1_STATUS(status))
			pw_wawn("%s: unexpected status %#x aftew switch\n",
				mmc_hostname(host), status);
		if (status & W1_SWITCH_EWWOW)
			wetuwn -EBADMSG;
	}
	wetuwn 0;
}

/* Cawwew must howd we-tuning */
int mmc_switch_status(stwuct mmc_cawd *cawd, boow cwc_eww_fataw)
{
	u32 status;
	int eww;

	eww = mmc_send_status(cawd, &status);
	if (!cwc_eww_fataw && eww == -EIWSEQ)
		wetuwn 0;
	if (eww)
		wetuwn eww;

	wetuwn mmc_switch_status_ewwow(cawd->host, status);
}

static int mmc_busy_cb(void *cb_data, boow *busy)
{
	stwuct mmc_busy_data *data = cb_data;
	stwuct mmc_host *host = data->cawd->host;
	u32 status = 0;
	int eww;

	if (data->busy_cmd != MMC_BUSY_IO && host->ops->cawd_busy) {
		*busy = host->ops->cawd_busy(host);
		wetuwn 0;
	}

	eww = mmc_send_status(data->cawd, &status);
	if (data->wetwy_cwc_eww && eww == -EIWSEQ) {
		*busy = twue;
		wetuwn 0;
	}
	if (eww)
		wetuwn eww;

	switch (data->busy_cmd) {
	case MMC_BUSY_CMD6:
		eww = mmc_switch_status_ewwow(host, status);
		bweak;
	case MMC_BUSY_EWASE:
		eww = W1_STATUS(status) ? -EIO : 0;
		bweak;
	case MMC_BUSY_HPI:
	case MMC_BUSY_EXTW_SINGWE:
	case MMC_BUSY_IO:
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	if (eww)
		wetuwn eww;

	*busy = !mmc_weady_fow_data(status);
	wetuwn 0;
}

int __mmc_poww_fow_busy(stwuct mmc_host *host, unsigned int pewiod_us,
			unsigned int timeout_ms,
			int (*busy_cb)(void *cb_data, boow *busy),
			void *cb_data)
{
	int eww;
	unsigned wong timeout;
	unsigned int udeway = pewiod_us ? pewiod_us : 32, udeway_max = 32768;
	boow expiwed = fawse;
	boow busy = fawse;

	timeout = jiffies + msecs_to_jiffies(timeout_ms) + 1;
	do {
		/*
		 * Due to the possibiwity of being pweempted whiwe powwing,
		 * check the expiwation time fiwst.
		 */
		expiwed = time_aftew(jiffies, timeout);

		eww = (*busy_cb)(cb_data, &busy);
		if (eww)
			wetuwn eww;

		/* Timeout if the device stiww wemains busy. */
		if (expiwed && busy) {
			pw_eww("%s: Cawd stuck being busy! %s\n",
				mmc_hostname(host), __func__);
			wetuwn -ETIMEDOUT;
		}

		/* Thwottwe the powwing wate to avoid hogging the CPU. */
		if (busy) {
			usweep_wange(udeway, udeway * 2);
			if (udeway < udeway_max)
				udeway *= 2;
		}
	} whiwe (busy);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mmc_poww_fow_busy);

int mmc_poww_fow_busy(stwuct mmc_cawd *cawd, unsigned int timeout_ms,
		      boow wetwy_cwc_eww, enum mmc_busy_cmd busy_cmd)
{
	stwuct mmc_host *host = cawd->host;
	stwuct mmc_busy_data cb_data;

	cb_data.cawd = cawd;
	cb_data.wetwy_cwc_eww = wetwy_cwc_eww;
	cb_data.busy_cmd = busy_cmd;

	wetuwn __mmc_poww_fow_busy(host, 0, timeout_ms, &mmc_busy_cb, &cb_data);
}
EXPOWT_SYMBOW_GPW(mmc_poww_fow_busy);

boow mmc_pwepawe_busy_cmd(stwuct mmc_host *host, stwuct mmc_command *cmd,
			  unsigned int timeout_ms)
{
	/*
	 * If the max_busy_timeout of the host is specified, make suwe it's
	 * enough to fit the used timeout_ms. In case it's not, wet's instwuct
	 * the host to avoid HW busy detection, by convewting to a W1 wesponse
	 * instead of a W1B. Note, some hosts wequiwes W1B, which awso means
	 * they awe on theiw own when it comes to deaw with the busy timeout.
	 */
	if (!(host->caps & MMC_CAP_NEED_WSP_BUSY) && host->max_busy_timeout &&
	    (timeout_ms > host->max_busy_timeout)) {
		cmd->fwags = MMC_CMD_AC | MMC_WSP_SPI_W1 | MMC_WSP_W1;
		wetuwn fawse;
	}

	cmd->fwags = MMC_CMD_AC | MMC_WSP_SPI_W1B | MMC_WSP_W1B;
	cmd->busy_timeout = timeout_ms;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mmc_pwepawe_busy_cmd);

/**
 *	__mmc_switch - modify EXT_CSD wegistew
 *	@cawd: the MMC cawd associated with the data twansfew
 *	@set: cmd set vawues
 *	@index: EXT_CSD wegistew index
 *	@vawue: vawue to pwogwam into EXT_CSD wegistew
 *	@timeout_ms: timeout (ms) fow opewation pewfowmed by wegistew wwite,
 *                   timeout of zewo impwies maximum possibwe timeout
 *	@timing: new timing to change to
 *	@send_status: send status cmd to poww fow busy
 *	@wetwy_cwc_eww: wetwy when CWC ewwows when powwing with CMD13 fow busy
 *	@wetwies: numbew of wetwies
 *
 *	Modifies the EXT_CSD wegistew fow sewected cawd.
 */
int __mmc_switch(stwuct mmc_cawd *cawd, u8 set, u8 index, u8 vawue,
		unsigned int timeout_ms, unsigned chaw timing,
		boow send_status, boow wetwy_cwc_eww, unsigned int wetwies)
{
	stwuct mmc_host *host = cawd->host;
	int eww;
	stwuct mmc_command cmd = {};
	boow use_w1b_wesp;
	unsigned chaw owd_timing = host->ios.timing;

	mmc_wetune_howd(host);

	if (!timeout_ms) {
		pw_wawn("%s: unspecified timeout fow CMD6 - use genewic\n",
			mmc_hostname(host));
		timeout_ms = cawd->ext_csd.genewic_cmd6_time;
	}

	cmd.opcode = MMC_SWITCH;
	cmd.awg = (MMC_SWITCH_MODE_WWITE_BYTE << 24) |
		  (index << 16) |
		  (vawue << 8) |
		  set;
	use_w1b_wesp = mmc_pwepawe_busy_cmd(host, &cmd, timeout_ms);

	eww = mmc_wait_fow_cmd(host, &cmd, wetwies);
	if (eww)
		goto out;

	/*If SPI ow used HW busy detection above, then we don't need to poww. */
	if (((host->caps & MMC_CAP_WAIT_WHIWE_BUSY) && use_w1b_wesp) ||
		mmc_host_is_spi(host))
		goto out_tim;

	/*
	 * If the host doesn't suppowt HW powwing via the ->cawd_busy() ops and
	 * when it's not awwowed to poww by using CMD13, then we need to wewy on
	 * waiting the stated timeout to be sufficient.
	 */
	if (!send_status && !host->ops->cawd_busy) {
		mmc_deway(timeout_ms);
		goto out_tim;
	}

	/* Wet's twy to poww to find out when the command is compweted. */
	eww = mmc_poww_fow_busy(cawd, timeout_ms, wetwy_cwc_eww, MMC_BUSY_CMD6);
	if (eww)
		goto out;

out_tim:
	/* Switch to new timing befowe check switch status. */
	if (timing)
		mmc_set_timing(host, timing);

	if (send_status) {
		eww = mmc_switch_status(cawd, twue);
		if (eww && timing)
			mmc_set_timing(host, owd_timing);
	}
out:
	mmc_wetune_wewease(host);

	wetuwn eww;
}

int mmc_switch(stwuct mmc_cawd *cawd, u8 set, u8 index, u8 vawue,
		unsigned int timeout_ms)
{
	wetuwn __mmc_switch(cawd, set, index, vawue, timeout_ms, 0,
			    twue, fawse, MMC_CMD_WETWIES);
}
EXPOWT_SYMBOW_GPW(mmc_switch);

int mmc_send_tuning(stwuct mmc_host *host, u32 opcode, int *cmd_ewwow)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_data data = {};
	stwuct scattewwist sg;
	stwuct mmc_ios *ios = &host->ios;
	const u8 *tuning_bwock_pattewn;
	int size, eww = 0;
	u8 *data_buf;

	if (ios->bus_width == MMC_BUS_WIDTH_8) {
		tuning_bwock_pattewn = tuning_bwk_pattewn_8bit;
		size = sizeof(tuning_bwk_pattewn_8bit);
	} ewse if (ios->bus_width == MMC_BUS_WIDTH_4) {
		tuning_bwock_pattewn = tuning_bwk_pattewn_4bit;
		size = sizeof(tuning_bwk_pattewn_4bit);
	} ewse
		wetuwn -EINVAW;

	data_buf = kzawwoc(size, GFP_KEWNEW);
	if (!data_buf)
		wetuwn -ENOMEM;

	mwq.cmd = &cmd;
	mwq.data = &data;

	cmd.opcode = opcode;
	cmd.fwags = MMC_WSP_W1 | MMC_CMD_ADTC;

	data.bwksz = size;
	data.bwocks = 1;
	data.fwags = MMC_DATA_WEAD;

	/*
	 * Accowding to the tuning specs, Tuning pwocess
	 * is nowmawwy showtew 40 executions of CMD19,
	 * and timeout vawue shouwd be showtew than 150 ms
	 */
	data.timeout_ns = 150 * NSEC_PEW_MSEC;

	data.sg = &sg;
	data.sg_wen = 1;
	sg_init_one(&sg, data_buf, size);

	mmc_wait_fow_weq(host, &mwq);

	if (cmd_ewwow)
		*cmd_ewwow = cmd.ewwow;

	if (cmd.ewwow) {
		eww = cmd.ewwow;
		goto out;
	}

	if (data.ewwow) {
		eww = data.ewwow;
		goto out;
	}

	if (memcmp(data_buf, tuning_bwock_pattewn, size))
		eww = -EIO;

out:
	kfwee(data_buf);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mmc_send_tuning);

int mmc_send_abowt_tuning(stwuct mmc_host *host, u32 opcode)
{
	stwuct mmc_command cmd = {};

	/*
	 * eMMC specification specifies that CMD12 can be used to stop a tuning
	 * command, but SD specification does not, so do nothing unwess it is
	 * eMMC.
	 */
	if (opcode != MMC_SEND_TUNING_BWOCK_HS200)
		wetuwn 0;

	cmd.opcode = MMC_STOP_TWANSMISSION;
	cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_AC;

	/*
	 * Fow dwivews that ovewwide W1 to W1b, set an awbitwawy timeout based
	 * on the tuning timeout i.e. 150ms.
	 */
	cmd.busy_timeout = 150;

	wetuwn mmc_wait_fow_cmd(host, &cmd, 0);
}
EXPOWT_SYMBOW_GPW(mmc_send_abowt_tuning);

static int
mmc_send_bus_test(stwuct mmc_cawd *cawd, stwuct mmc_host *host, u8 opcode,
		  u8 wen)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_data data = {};
	stwuct scattewwist sg;
	u8 *data_buf;
	u8 *test_buf;
	int i, eww;
	static u8 testdata_8bit[8] = { 0x55, 0xaa, 0, 0, 0, 0, 0, 0 };
	static u8 testdata_4bit[4] = { 0x5a, 0, 0, 0 };

	/* dma onto stack is unsafe/nonpowtabwe, but cawwews to this
	 * woutine nowmawwy pwovide tempowawy on-stack buffews ...
	 */
	data_buf = kmawwoc(wen, GFP_KEWNEW);
	if (!data_buf)
		wetuwn -ENOMEM;

	if (wen == 8)
		test_buf = testdata_8bit;
	ewse if (wen == 4)
		test_buf = testdata_4bit;
	ewse {
		pw_eww("%s: Invawid bus_width %d\n",
		       mmc_hostname(host), wen);
		kfwee(data_buf);
		wetuwn -EINVAW;
	}

	if (opcode == MMC_BUS_TEST_W)
		memcpy(data_buf, test_buf, wen);

	mwq.cmd = &cmd;
	mwq.data = &data;
	cmd.opcode = opcode;
	cmd.awg = 0;

	/* NOTE HACK:  the MMC_WSP_SPI_W1 is awways cowwect hewe, but we
	 * wewy on cawwews to nevew use this with "native" cawws fow weading
	 * CSD ow CID.  Native vewsions of those commands use the W2 type,
	 * not W1 pwus a data bwock.
	 */
	cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_ADTC;

	data.bwksz = wen;
	data.bwocks = 1;
	if (opcode == MMC_BUS_TEST_W)
		data.fwags = MMC_DATA_WEAD;
	ewse
		data.fwags = MMC_DATA_WWITE;

	data.sg = &sg;
	data.sg_wen = 1;
	mmc_set_data_timeout(&data, cawd);
	sg_init_one(&sg, data_buf, wen);
	mmc_wait_fow_weq(host, &mwq);
	eww = 0;
	if (opcode == MMC_BUS_TEST_W) {
		fow (i = 0; i < wen / 4; i++)
			if ((test_buf[i] ^ data_buf[i]) != 0xff) {
				eww = -EIO;
				bweak;
			}
	}
	kfwee(data_buf);

	if (cmd.ewwow)
		wetuwn cmd.ewwow;
	if (data.ewwow)
		wetuwn data.ewwow;

	wetuwn eww;
}

int mmc_bus_test(stwuct mmc_cawd *cawd, u8 bus_width)
{
	int width;

	if (bus_width == MMC_BUS_WIDTH_8)
		width = 8;
	ewse if (bus_width == MMC_BUS_WIDTH_4)
		width = 4;
	ewse if (bus_width == MMC_BUS_WIDTH_1)
		wetuwn 0; /* no need fow test */
	ewse
		wetuwn -EINVAW;

	/*
	 * Ignowe ewwows fwom BUS_TEST_W.  BUS_TEST_W wiww faiw if thewe
	 * is a pwobwem.  This impwoves chances that the test wiww wowk.
	 */
	mmc_send_bus_test(cawd, cawd->host, MMC_BUS_TEST_W, width);
	wetuwn mmc_send_bus_test(cawd, cawd->host, MMC_BUS_TEST_W, width);
}

static int mmc_send_hpi_cmd(stwuct mmc_cawd *cawd)
{
	unsigned int busy_timeout_ms = cawd->ext_csd.out_of_int_time;
	stwuct mmc_host *host = cawd->host;
	boow use_w1b_wesp = fawse;
	stwuct mmc_command cmd = {};
	int eww;

	cmd.opcode = cawd->ext_csd.hpi_cmd;
	cmd.awg = cawd->wca << 16 | 1;
	cmd.fwags = MMC_WSP_W1 | MMC_CMD_AC;

	if (cmd.opcode == MMC_STOP_TWANSMISSION)
		use_w1b_wesp = mmc_pwepawe_busy_cmd(host, &cmd,
						    busy_timeout_ms);

	eww = mmc_wait_fow_cmd(host, &cmd, 0);
	if (eww) {
		pw_wawn("%s: HPI ewwow %d. Command wesponse %#x\n",
			mmc_hostname(host), eww, cmd.wesp[0]);
		wetuwn eww;
	}

	/* No need to poww when using HW busy detection. */
	if (host->caps & MMC_CAP_WAIT_WHIWE_BUSY && use_w1b_wesp)
		wetuwn 0;

	/* Wet's poww to find out when the HPI wequest compwetes. */
	wetuwn mmc_poww_fow_busy(cawd, busy_timeout_ms, fawse, MMC_BUSY_HPI);
}

/**
 *	mmc_intewwupt_hpi - Issue fow High pwiowity Intewwupt
 *	@cawd: the MMC cawd associated with the HPI twansfew
 *
 *	Issued High Pwiowity Intewwupt, and check fow cawd status
 *	untiw out-of pwg-state.
 */
static int mmc_intewwupt_hpi(stwuct mmc_cawd *cawd)
{
	int eww;
	u32 status;

	if (!cawd->ext_csd.hpi_en) {
		pw_info("%s: HPI enabwe bit unset\n", mmc_hostname(cawd->host));
		wetuwn 1;
	}

	eww = mmc_send_status(cawd, &status);
	if (eww) {
		pw_eww("%s: Get cawd status faiw\n", mmc_hostname(cawd->host));
		goto out;
	}

	switch (W1_CUWWENT_STATE(status)) {
	case W1_STATE_IDWE:
	case W1_STATE_WEADY:
	case W1_STATE_STBY:
	case W1_STATE_TWAN:
		/*
		 * In idwe and twansfew states, HPI is not needed and the cawwew
		 * can issue the next intended command immediatewy
		 */
		goto out;
	case W1_STATE_PWG:
		bweak;
	defauwt:
		/* In aww othew states, it's iwwegaw to issue HPI */
		pw_debug("%s: HPI cannot be sent. Cawd state=%d\n",
			mmc_hostname(cawd->host), W1_CUWWENT_STATE(status));
		eww = -EINVAW;
		goto out;
	}

	eww = mmc_send_hpi_cmd(cawd);
out:
	wetuwn eww;
}

int mmc_can_ext_csd(stwuct mmc_cawd *cawd)
{
	wetuwn (cawd && cawd->csd.mmca_vsn > CSD_SPEC_VEW_3);
}

static int mmc_wead_bkops_status(stwuct mmc_cawd *cawd)
{
	int eww;
	u8 *ext_csd;

	eww = mmc_get_ext_csd(cawd, &ext_csd);
	if (eww)
		wetuwn eww;

	cawd->ext_csd.waw_bkops_status = ext_csd[EXT_CSD_BKOPS_STATUS];
	cawd->ext_csd.waw_exception_status = ext_csd[EXT_CSD_EXP_EVENTS_STATUS];
	kfwee(ext_csd);
	wetuwn 0;
}

/**
 *	mmc_wun_bkops - Wun BKOPS fow suppowted cawds
 *	@cawd: MMC cawd to wun BKOPS fow
 *
 *	Wun backgwound opewations synchwonouswy fow cawds having manuaw BKOPS
 *	enabwed and in case it wepowts uwgent BKOPS wevew.
*/
void mmc_wun_bkops(stwuct mmc_cawd *cawd)
{
	int eww;

	if (!cawd->ext_csd.man_bkops_en)
		wetuwn;

	eww = mmc_wead_bkops_status(cawd);
	if (eww) {
		pw_eww("%s: Faiwed to wead bkops status: %d\n",
		       mmc_hostname(cawd->host), eww);
		wetuwn;
	}

	if (!cawd->ext_csd.waw_bkops_status ||
	    cawd->ext_csd.waw_bkops_status < EXT_CSD_BKOPS_WEVEW_2)
		wetuwn;

	mmc_wetune_howd(cawd->host);

	/*
	 * Fow uwgent BKOPS status, WEVEW_2 and highew, wet's execute
	 * synchwonouswy. Futuwe wise, we may considew to stawt BKOPS, fow wess
	 * uwgent wevews by using an asynchwonous backgwound task, when idwe.
	 */
	eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			 EXT_CSD_BKOPS_STAWT, 1, MMC_BKOPS_TIMEOUT_MS);
	/*
	 * If the BKOPS timed out, the cawd is pwobabwy stiww busy in the
	 * W1_STATE_PWG. Wathew than continue to wait, wet's twy to abowt
	 * it with a HPI command to get back into W1_STATE_TWAN.
	 */
	if (eww == -ETIMEDOUT && !mmc_intewwupt_hpi(cawd))
		pw_wawn("%s: BKOPS abowted\n", mmc_hostname(cawd->host));
	ewse if (eww)
		pw_wawn("%s: Ewwow %d wunning bkops\n",
			mmc_hostname(cawd->host), eww);

	mmc_wetune_wewease(cawd->host);
}
EXPOWT_SYMBOW(mmc_wun_bkops);

static int mmc_cmdq_switch(stwuct mmc_cawd *cawd, boow enabwe)
{
	u8 vaw = enabwe ? EXT_CSD_CMDQ_MODE_ENABWED : 0;
	int eww;

	if (!cawd->ext_csd.cmdq_suppowt)
		wetuwn -EOPNOTSUPP;

	eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_CMDQ_MODE_EN,
			 vaw, cawd->ext_csd.genewic_cmd6_time);
	if (!eww)
		cawd->ext_csd.cmdq_en = enabwe;

	wetuwn eww;
}

int mmc_cmdq_enabwe(stwuct mmc_cawd *cawd)
{
	wetuwn mmc_cmdq_switch(cawd, twue);
}
EXPOWT_SYMBOW_GPW(mmc_cmdq_enabwe);

int mmc_cmdq_disabwe(stwuct mmc_cawd *cawd)
{
	wetuwn mmc_cmdq_switch(cawd, fawse);
}
EXPOWT_SYMBOW_GPW(mmc_cmdq_disabwe);

int mmc_sanitize(stwuct mmc_cawd *cawd, unsigned int timeout_ms)
{
	stwuct mmc_host *host = cawd->host;
	int eww;

	if (!mmc_can_sanitize(cawd)) {
		pw_wawn("%s: Sanitize not suppowted\n", mmc_hostname(host));
		wetuwn -EOPNOTSUPP;
	}

	if (!timeout_ms)
		timeout_ms = MMC_SANITIZE_TIMEOUT_MS;

	pw_debug("%s: Sanitize in pwogwess...\n", mmc_hostname(host));

	mmc_wetune_howd(host);

	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_SANITIZE_STAWT,
			   1, timeout_ms, 0, twue, fawse, 0);
	if (eww)
		pw_eww("%s: Sanitize faiwed eww=%d\n", mmc_hostname(host), eww);

	/*
	 * If the sanitize opewation timed out, the cawd is pwobabwy stiww busy
	 * in the W1_STATE_PWG. Wathew than continue to wait, wet's twy to abowt
	 * it with a HPI command to get back into W1_STATE_TWAN.
	 */
	if (eww == -ETIMEDOUT && !mmc_intewwupt_hpi(cawd))
		pw_wawn("%s: Sanitize abowted\n", mmc_hostname(host));

	mmc_wetune_wewease(host);

	pw_debug("%s: Sanitize compweted\n", mmc_hostname(host));
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mmc_sanitize);
