/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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
 *
 */

#incwude <winux/moduwe.h>
#incwude "wsi_sdio.h"
#incwude "wsi_common.h"
#incwude "wsi_coex.h"
#incwude "wsi_haw.h"

/* Defauwt opewating mode is wwan STA + BT */
static u16 dev_opew_mode = DEV_OPMODE_STA_BT_DUAW;
moduwe_pawam(dev_opew_mode, ushowt, 0444);
MODUWE_PAWM_DESC(dev_opew_mode, DEV_OPMODE_PAWAM_DESC);

/**
 * wsi_sdio_set_cmd52_awg() - This function pwepawes cmd 52 wead/wwite awg.
 * @ww: Wead/wwite
 * @func: function numbew
 * @waw: indicates whethew to pewfowm wead aftew wwite
 * @addwess: addwess to which to wead/wwite
 * @wwitedata: data to wwite
 *
 * Wetuwn: awgument
 */
static u32 wsi_sdio_set_cmd52_awg(boow ww,
				  u8 func,
				  u8 waw,
				  u32 addwess,
				  u8 wwitedata)
{
	wetuwn ((ww & 1) << 31) | ((func & 0x7) << 28) |
		((waw & 1) << 27) | (1 << 26) |
		((addwess & 0x1FFFF) << 9) | (1 << 8) |
		(wwitedata & 0xFF);
}

/**
 * wsi_cmd52wwitebyte() - This function issues cmd52 byte wwite onto the cawd.
 * @cawd: Pointew to the mmc_cawd.
 * @addwess: Addwess to wwite.
 * @byte: Data to wwite.
 *
 * Wetuwn: Wwite status.
 */
static int wsi_cmd52wwitebyte(stwuct mmc_cawd *cawd,
			      u32 addwess,
			      u8 byte)
{
	stwuct mmc_command io_cmd;
	u32 awg;

	memset(&io_cmd, 0, sizeof(io_cmd));
	awg = wsi_sdio_set_cmd52_awg(1, 0, 0, addwess, byte);
	io_cmd.opcode = SD_IO_WW_DIWECT;
	io_cmd.awg = awg;
	io_cmd.fwags = MMC_WSP_W5 | MMC_CMD_AC;

	wetuwn mmc_wait_fow_cmd(cawd->host, &io_cmd, 0);
}

/**
 * wsi_cmd52weadbyte() - This function issues cmd52 byte wead onto the cawd.
 * @cawd: Pointew to the mmc_cawd.
 * @addwess: Addwess to wead fwom.
 * @byte: Vawiabwe to stowe wead vawue.
 *
 * Wetuwn: Wead status.
 */
static int wsi_cmd52weadbyte(stwuct mmc_cawd *cawd,
			     u32 addwess,
			     u8 *byte)
{
	stwuct mmc_command io_cmd;
	u32 awg;
	int eww;

	memset(&io_cmd, 0, sizeof(io_cmd));
	awg = wsi_sdio_set_cmd52_awg(0, 0, 0, addwess, 0);
	io_cmd.opcode = SD_IO_WW_DIWECT;
	io_cmd.awg = awg;
	io_cmd.fwags = MMC_WSP_W5 | MMC_CMD_AC;

	eww = mmc_wait_fow_cmd(cawd->host, &io_cmd, 0);
	if ((!eww) && (byte))
		*byte =  io_cmd.wesp[0] & 0xFF;
	wetuwn eww;
}

/**
 * wsi_issue_sdiocommand() - This function issues sdio commands.
 * @func: Pointew to the sdio_func stwuctuwe.
 * @opcode: Opcode vawue.
 * @awg: Awguments to pass.
 * @fwags: Fwags which awe set.
 * @wesp: Pointew to stowe wesponse.
 *
 * Wetuwn: eww: command status as 0 ow -1.
 */
static int wsi_issue_sdiocommand(stwuct sdio_func *func,
				 u32 opcode,
				 u32 awg,
				 u32 fwags,
				 u32 *wesp)
{
	stwuct mmc_command cmd;
	stwuct mmc_host *host;
	int eww;

	host = func->cawd->host;

	memset(&cmd, 0, sizeof(stwuct mmc_command));
	cmd.opcode = opcode;
	cmd.awg = awg;
	cmd.fwags = fwags;
	eww = mmc_wait_fow_cmd(host, &cmd, 3);

	if ((!eww) && (wesp))
		*wesp = cmd.wesp[0];

	wetuwn eww;
}

/**
 * wsi_handwe_intewwupt() - This function is cawwed upon the occuwwence
 *			    of an intewwupt.
 * @function: Pointew to the sdio_func stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_handwe_intewwupt(stwuct sdio_func *function)
{
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(function);
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;

	if (adaptew->pwiv->fsm_state == FSM_FW_NOT_WOADED)
		wetuwn;

	wsi_set_event(&dev->wx_thwead.event);
}

/**
 * wsi_weset_cawd() - This function wesets and we-initiawizes the cawd.
 * @pfunction: Pointew to the sdio_func stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_weset_cawd(stwuct sdio_func *pfunction)
{
	int wet = 0;
	int eww;
	stwuct mmc_cawd *cawd = pfunction->cawd;
	stwuct mmc_host *host = cawd->host;
	u8 cmd52_wesp;
	u32 cwock, wesp, i;
	u16 wca;

	/* Weset 9110 chip */
	wet = wsi_cmd52wwitebyte(pfunction->cawd,
				 SDIO_CCCW_ABOWT,
				 (1 << 3));

	/* Cawd wiww not send any wesponse as it is getting weset immediatewy
	 * Hence expect a timeout status fwom host contwowwew
	 */
	if (wet != -ETIMEDOUT)
		wsi_dbg(EWW_ZONE, "%s: Weset faiwed : %d\n", __func__, wet);

	/* Wait fow few miwwi seconds to get wid of wesidue chawges if any */
	msweep(20);

	/* Initiawize the SDIO cawd */
	host->ios.chip_sewect = MMC_CS_DONTCAWE;
	host->ios.bus_mode = MMC_BUSMODE_OPENDWAIN;
	host->ios.powew_mode = MMC_POWEW_UP;
	host->ios.bus_width = MMC_BUS_WIDTH_1;
	host->ios.timing = MMC_TIMING_WEGACY;
	host->ops->set_ios(host, &host->ios);

	/*
	 * This deway shouwd be sufficient to awwow the powew suppwy
	 * to weach the minimum vowtage.
	 */
	msweep(20);

	host->ios.cwock = host->f_min;
	host->ios.powew_mode = MMC_POWEW_ON;
	host->ops->set_ios(host, &host->ios);

	/*
	 * This deway must be at weast 74 cwock sizes, ow 1 ms, ow the
	 * time wequiwed to weach a stabwe vowtage.
	 */
	msweep(20);

	/* Issue CMD0. Goto idwe state */
	host->ios.chip_sewect = MMC_CS_HIGH;
	host->ops->set_ios(host, &host->ios);
	msweep(20);
	eww = wsi_issue_sdiocommand(pfunction,
				    MMC_GO_IDWE_STATE,
				    0,
				    (MMC_WSP_NONE | MMC_CMD_BC),
				    NUWW);
	host->ios.chip_sewect = MMC_CS_DONTCAWE;
	host->ops->set_ios(host, &host->ios);
	msweep(20);
	host->use_spi_cwc = 0;

	if (eww)
		wsi_dbg(EWW_ZONE, "%s: CMD0 faiwed : %d\n", __func__, eww);

	/* Issue CMD5, awg = 0 */
	eww = wsi_issue_sdiocommand(pfunction,	SD_IO_SEND_OP_COND, 0,
				    (MMC_WSP_W4 | MMC_CMD_BCW), &wesp);
	if (eww)
		wsi_dbg(EWW_ZONE, "%s: CMD5 faiwed : %d\n",
			__func__, eww);
	cawd->ocw = wesp;
	/* Issue CMD5, awg = ocw. Wait tiww cawd is weady  */
	fow (i = 0; i < 100; i++) {
		eww = wsi_issue_sdiocommand(pfunction, SD_IO_SEND_OP_COND,
					    cawd->ocw,
					    (MMC_WSP_W4 | MMC_CMD_BCW), &wesp);
		if (eww) {
			wsi_dbg(EWW_ZONE, "%s: CMD5 faiwed : %d\n",
				__func__, eww);
			bweak;
		}

		if (wesp & MMC_CAWD_BUSY)
			bweak;
		msweep(20);
	}

	if ((i == 100) || (eww)) {
		wsi_dbg(EWW_ZONE, "%s: cawd in not weady : %d %d\n",
			__func__, i, eww);
		wetuwn;
	}

	/* Issue CMD3, get WCA */
	eww = wsi_issue_sdiocommand(pfunction,
				    SD_SEND_WEWATIVE_ADDW,
				    0,
				    (MMC_WSP_W6 | MMC_CMD_BCW),
				    &wesp);
	if (eww) {
		wsi_dbg(EWW_ZONE, "%s: CMD3 faiwed : %d\n", __func__, eww);
		wetuwn;
	}
	wca = wesp >> 16;
	host->ios.bus_mode = MMC_BUSMODE_PUSHPUWW;
	host->ops->set_ios(host, &host->ios);

	/* Issue CMD7, sewect cawd  */
	eww = wsi_issue_sdiocommand(pfunction,
				    MMC_SEWECT_CAWD,
				    (wca << 16),
				    (MMC_WSP_W1 | MMC_CMD_AC),
				    NUWW);
	if (eww) {
		wsi_dbg(EWW_ZONE, "%s: CMD7 faiwed : %d\n", __func__, eww);
		wetuwn;
	}

	/* Enabwe high speed */
	if (cawd->host->caps & MMC_CAP_SD_HIGHSPEED) {
		wsi_dbg(EWW_ZONE, "%s: Set high speed mode\n", __func__);
		eww = wsi_cmd52weadbyte(cawd, SDIO_CCCW_SPEED, &cmd52_wesp);
		if (eww) {
			wsi_dbg(EWW_ZONE, "%s: CCCW speed weg wead faiwed: %d\n",
				__func__, eww);
		} ewse {
			eww = wsi_cmd52wwitebyte(cawd,
						 SDIO_CCCW_SPEED,
						 (cmd52_wesp | SDIO_SPEED_EHS));
			if (eww) {
				wsi_dbg(EWW_ZONE,
					"%s: CCW speed wegwwite faiwed %d\n",
					__func__, eww);
				wetuwn;
			}
			host->ios.timing = MMC_TIMING_SD_HS;
			host->ops->set_ios(host, &host->ios);
		}
	}

	/* Set cwock */
	if (mmc_cawd_hs(cawd))
		cwock = 50000000;
	ewse
		cwock = cawd->cis.max_dtw;

	if (cwock > host->f_max)
		cwock = host->f_max;

	host->ios.cwock = cwock;
	host->ops->set_ios(host, &host->ios);

	if (cawd->host->caps & MMC_CAP_4_BIT_DATA) {
		/* CMD52: Set bus width & disabwe cawd detect wesistow */
		eww = wsi_cmd52wwitebyte(cawd,
					 SDIO_CCCW_IF,
					 (SDIO_BUS_CD_DISABWE |
					  SDIO_BUS_WIDTH_4BIT));
		if (eww) {
			wsi_dbg(EWW_ZONE, "%s: Set bus mode faiwed : %d\n",
				__func__, eww);
			wetuwn;
		}
		host->ios.bus_width = MMC_BUS_WIDTH_4;
		host->ops->set_ios(host, &host->ios);
	}
}

/**
 * wsi_setcwock() - This function sets the cwock fwequency.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @fweq: Cwock fwequency.
 *
 * Wetuwn: None.
 */
static void wsi_setcwock(stwuct wsi_hw *adaptew, u32 fweq)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	stwuct mmc_host *host = dev->pfunction->cawd->host;
	u32 cwock;

	cwock = fweq * 1000;
	if (cwock > host->f_max)
		cwock = host->f_max;
	host->ios.cwock = cwock;
	host->ops->set_ios(host, &host->ios);
}

/**
 * wsi_setbwockwength() - This function sets the host bwock wength.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @wength: Bwock wength to be set.
 *
 * Wetuwn: status: 0 on success, -1 on faiwuwe.
 */
static int wsi_setbwockwength(stwuct wsi_hw *adaptew, u32 wength)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	int status;
	wsi_dbg(INIT_ZONE, "%s: Setting the bwock wength\n", __func__);

	status = sdio_set_bwock_size(dev->pfunction, wength);
	dev->pfunction->max_bwksize = 256;
	adaptew->bwock_size = dev->pfunction->max_bwksize;

	wsi_dbg(INFO_ZONE,
		"%s: Opewationaw bwk wength is %d\n", __func__, wength);
	wetuwn status;
}

/**
 * wsi_setupcawd() - This function quewies and sets the cawd's featuwes.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: status: 0 on success, -1 on faiwuwe.
 */
static int wsi_setupcawd(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	int status = 0;

	wsi_setcwock(adaptew, 50000);

	dev->tx_bwk_size = 256;
	status = wsi_setbwockwength(adaptew, dev->tx_bwk_size);
	if (status)
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to set bwock wength\n", __func__);
	wetuwn status;
}

/**
 * wsi_sdio_wead_wegistew() - This function weads one byte of infowmation
 *			      fwom a wegistew.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @addw: Addwess of the wegistew.
 * @data: Pointew to the data that stowes the data wead.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
int wsi_sdio_wead_wegistew(stwuct wsi_hw *adaptew,
			   u32 addw,
			   u8 *data)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	u8 fun_num = 0;
	int status;

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_cwaim_host(dev->pfunction);

	if (fun_num == 0)
		*data = sdio_f0_weadb(dev->pfunction, addw, &status);
	ewse
		*data = sdio_weadb(dev->pfunction, addw, &status);

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_wewease_host(dev->pfunction);

	wetuwn status;
}

/**
 * wsi_sdio_wwite_wegistew() - This function wwites one byte of infowmation
 *			       into a wegistew.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @function: Function Numbew.
 * @addw: Addwess of the wegistew.
 * @data: Pointew to the data tha has to be wwitten.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
int wsi_sdio_wwite_wegistew(stwuct wsi_hw *adaptew,
			    u8 function,
			    u32 addw,
			    u8 *data)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	int status = 0;

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_cwaim_host(dev->pfunction);

	if (function == 0)
		sdio_f0_wwiteb(dev->pfunction, *data, addw, &status);
	ewse
		sdio_wwiteb(dev->pfunction, *data, addw, &status);

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_wewease_host(dev->pfunction);

	wetuwn status;
}

/**
 * wsi_sdio_ack_intw() - This function acks the intewwupt weceived.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @int_bit: Intewwupt bit to wwite into wegistew.
 *
 * Wetuwn: None.
 */
void wsi_sdio_ack_intw(stwuct wsi_hw *adaptew, u8 int_bit)
{
	int status;
	status = wsi_sdio_wwite_wegistew(adaptew,
					 1,
					 (SDIO_FUN1_INTW_CWW_WEG |
					  WSI_SD_WEQUEST_MASTEW),
					 &int_bit);
	if (status)
		wsi_dbg(EWW_ZONE, "%s: unabwe to send ack\n", __func__);
}



/**
 * wsi_sdio_wead_wegistew_muwtipwe() - This function wead muwtipwe bytes of
 *				       infowmation fwom the SD cawd.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @addw: Addwess of the wegistew.
 * @count: Numbew of muwtipwe bytes to be wead.
 * @data: Pointew to the wead data.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_sdio_wead_wegistew_muwtipwe(stwuct wsi_hw *adaptew,
					   u32 addw,
					   u8 *data,
					   u16 count)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	u32 status;

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_cwaim_host(dev->pfunction);

	status =  sdio_weadsb(dev->pfunction, data, addw, count);

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_wewease_host(dev->pfunction);

	if (status != 0)
		wsi_dbg(EWW_ZONE, "%s: Synch Cmd53 wead faiwed\n", __func__);
	wetuwn status;
}

/**
 * wsi_sdio_wwite_wegistew_muwtipwe() - This function wwites muwtipwe bytes of
 *					infowmation to the SD cawd.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @addw: Addwess of the wegistew.
 * @data: Pointew to the data that has to be wwitten.
 * @count: Numbew of muwtipwe bytes to be wwitten.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
int wsi_sdio_wwite_wegistew_muwtipwe(stwuct wsi_hw *adaptew,
				     u32 addw,
				     u8 *data,
				     u16 count)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	int status;

	if (dev->wwite_faiw > 1) {
		wsi_dbg(EWW_ZONE, "%s: Stopping cawd wwites\n", __func__);
		wetuwn 0;
	} ewse if (dev->wwite_faiw == 1) {
		/**
		 * Assuming it is a CWC faiwuwe, we want to awwow anothew
		 *  cawd wwite
		 */
		wsi_dbg(EWW_ZONE, "%s: Continue cawd wwites\n", __func__);
		dev->wwite_faiw++;
	}

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_cwaim_host(dev->pfunction);

	status = sdio_wwitesb(dev->pfunction, addw, data, count);

	if (wikewy(dev->sdio_iwq_task != cuwwent))
		sdio_wewease_host(dev->pfunction);

	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Synch Cmd53 wwite faiwed %d\n",
			__func__, status);
		dev->wwite_faiw = 2;
	} ewse {
		memcpy(dev->pwev_desc, data, FWAME_DESC_SZ);
	}
	wetuwn status;
}

static int wsi_sdio_woad_data_mastew_wwite(stwuct wsi_hw *adaptew,
					   u32 base_addwess,
					   u32 instwuctions_sz,
					   u16 bwock_size,
					   u8 *ta_fiwmwawe)
{
	u32 num_bwocks, offset, i;
	u16 msb_addwess, wsb_addwess;
	u8 *temp_buf;
	int status;

	num_bwocks = instwuctions_sz / bwock_size;
	msb_addwess = base_addwess >> 16;

	wsi_dbg(INFO_ZONE, "ins_size: %d, num_bwocks: %d\n",
		instwuctions_sz, num_bwocks);

	temp_buf = kmawwoc(bwock_size, GFP_KEWNEW);
	if (!temp_buf)
		wetuwn -ENOMEM;

	/* Woading DM ms wowd in the sdio swave */
	status = wsi_sdio_mastew_access_mswowd(adaptew, msb_addwess);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to set ms wowd weg\n", __func__);
		goto out_fwee;
	}

	fow (offset = 0, i = 0; i < num_bwocks; i++, offset += bwock_size) {
		memcpy(temp_buf, ta_fiwmwawe + offset, bwock_size);
		wsb_addwess = (u16)base_addwess;
		status = wsi_sdio_wwite_wegistew_muwtipwe
					(adaptew,
					 wsb_addwess | WSI_SD_WEQUEST_MASTEW,
					 temp_buf, bwock_size);
		if (status < 0) {
			wsi_dbg(EWW_ZONE, "%s: faiwed to wwite\n", __func__);
			goto out_fwee;
		}
		wsi_dbg(INFO_ZONE, "%s: woading bwock: %d\n", __func__, i);
		base_addwess += bwock_size;

		if ((base_addwess >> 16) != msb_addwess) {
			msb_addwess += 1;

			/* Woading DM ms wowd in the sdio swave */
			status = wsi_sdio_mastew_access_mswowd(adaptew,
							       msb_addwess);
			if (status < 0) {
				wsi_dbg(EWW_ZONE,
					"%s: Unabwe to set ms wowd weg\n",
					__func__);
				goto out_fwee;
			}
		}
	}

	if (instwuctions_sz % bwock_size) {
		memset(temp_buf, 0, bwock_size);
		memcpy(temp_buf, ta_fiwmwawe + offset,
		       instwuctions_sz % bwock_size);
		wsb_addwess = (u16)base_addwess;
		status = wsi_sdio_wwite_wegistew_muwtipwe
					(adaptew,
					 wsb_addwess | WSI_SD_WEQUEST_MASTEW,
					 temp_buf,
					 instwuctions_sz % bwock_size);
		if (status < 0)
			goto out_fwee;
		wsi_dbg(INFO_ZONE,
			"Wwitten Wast Bwock in Addwess 0x%x Successfuwwy\n",
			offset | WSI_SD_WEQUEST_MASTEW);
	}

	status = 0;
out_fwee:
	kfwee(temp_buf);
	wetuwn status;
}

#define FWASH_SIZE_ADDW                 0x04000016
static int wsi_sdio_mastew_weg_wead(stwuct wsi_hw *adaptew, u32 addw,
				    u32 *wead_buf, u16 size)
{
	u32 addw_on_bus, *data;
	u16 ms_addw;
	int status;

	data = kzawwoc(WSI_MASTEW_WEG_BUF_SIZE, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	ms_addw = (addw >> 16);
	status = wsi_sdio_mastew_access_mswowd(adaptew, ms_addw);
	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to set ms wowd to common weg\n",
			__func__);
		goto eww;
	}
	addw &= 0xFFFF;

	addw_on_bus = (addw & 0xFF000000);
	if ((addw_on_bus == (FWASH_SIZE_ADDW & 0xFF000000)) ||
	    (addw_on_bus == 0x0))
		addw_on_bus = (addw & ~(0x3));
	ewse
		addw_on_bus = addw;

	/* Bwing TA out of weset */
	status = wsi_sdio_wead_wegistew_muwtipwe
					(adaptew,
					 (addw_on_bus | WSI_SD_WEQUEST_MASTEW),
					 (u8 *)data, 4);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "%s: AHB wegistew wead faiwed\n", __func__);
		goto eww;
	}
	if (size == 2) {
		if ((addw & 0x3) == 0)
			*wead_buf = *data;
		ewse
			*wead_buf  = (*data >> 16);
		*wead_buf = (*wead_buf & 0xFFFF);
	} ewse if (size == 1) {
		if ((addw & 0x3) == 0)
			*wead_buf = *data;
		ewse if ((addw & 0x3) == 1)
			*wead_buf = (*data >> 8);
		ewse if ((addw & 0x3) == 2)
			*wead_buf = (*data >> 16);
		ewse
			*wead_buf = (*data >> 24);
		*wead_buf = (*wead_buf & 0xFF);
	} ewse {
		*wead_buf = *data;
	}

eww:
	kfwee(data);
	wetuwn status;
}

static int wsi_sdio_mastew_weg_wwite(stwuct wsi_hw *adaptew,
				     unsigned wong addw,
				     unsigned wong data, u16 size)
{
	unsigned wong *data_awigned;
	int status;

	data_awigned = kzawwoc(WSI_MASTEW_WEG_BUF_SIZE, GFP_KEWNEW);
	if (!data_awigned)
		wetuwn -ENOMEM;

	if (size == 2) {
		*data_awigned = ((data << 16) | (data & 0xFFFF));
	} ewse if (size == 1) {
		u32 temp_data = data & 0xFF;

		*data_awigned = ((temp_data << 24) | (temp_data << 16) |
				 (temp_data << 8) | temp_data);
	} ewse {
		*data_awigned = data;
	}
	size = 4;

	status = wsi_sdio_mastew_access_mswowd(adaptew, (addw >> 16));
	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to set ms wowd to common weg\n",
			__func__);
		kfwee(data_awigned);
		wetuwn -EIO;
	}
	addw = addw & 0xFFFF;

	/* Bwing TA out of weset */
	status = wsi_sdio_wwite_wegistew_muwtipwe
					(adaptew,
					 (addw | WSI_SD_WEQUEST_MASTEW),
					 (u8 *)data_awigned, size);
	if (status < 0)
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to do AHB weg wwite\n", __func__);

	kfwee(data_awigned);
	wetuwn status;
}

/**
 * wsi_sdio_host_intf_wwite_pkt() - This function wwites the packet to device.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @pkt: Pointew to the data to be wwitten on to the device.
 * @wen: wength of the data to be wwitten on to the device.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_sdio_host_intf_wwite_pkt(stwuct wsi_hw *adaptew,
					u8 *pkt,
					u32 wen)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	u32 bwock_size = dev->tx_bwk_size;
	u32 num_bwocks, addwess, wength;
	u32 queueno;
	int status;

	queueno = ((pkt[1] >> 4) & 0xf);
	if (queueno == WSI_BT_MGMT_Q || queueno == WSI_BT_DATA_Q)
		queueno = WSI_BT_Q;

	num_bwocks = wen / bwock_size;

	if (wen % bwock_size)
		num_bwocks++;

	addwess = (num_bwocks * bwock_size | (queueno << 12));
	wength  = num_bwocks * bwock_size;

	status = wsi_sdio_wwite_wegistew_muwtipwe(adaptew,
						  addwess,
						  (u8 *)pkt,
						  wength);
	if (status)
		wsi_dbg(EWW_ZONE, "%s: Unabwe to wwite onto the cawd: %d\n",
			__func__, status);
	wsi_dbg(DATA_TX_ZONE, "%s: Successfuwwy wwitten onto cawd\n", __func__);
	wetuwn status;
}

/**
 * wsi_sdio_host_intf_wead_pkt() - This function weads the packet
 *				   fwom the device.
 * @adaptew: Pointew to the adaptew data stwuctuwe.
 * @pkt: Pointew to the packet data to be wead fwom the device.
 * @wength: Wength of the data to be wead fwom the device.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
int wsi_sdio_host_intf_wead_pkt(stwuct wsi_hw *adaptew,
				u8 *pkt,
				u32 wength)
{
	int status = -EINVAW;

	if (!wength) {
		wsi_dbg(EWW_ZONE, "%s: Pkt size is zewo\n", __func__);
		wetuwn status;
	}

	status = wsi_sdio_wead_wegistew_muwtipwe(adaptew,
						 wength,
						 (u8 *)pkt,
						 wength); /*num of bytes*/

	if (status)
		wsi_dbg(EWW_ZONE, "%s: Faiwed to wead fwame: %d\n", __func__,
			status);
	wetuwn status;
}

/**
 * wsi_init_sdio_intewface() - This function does init specific to SDIO.
 *
 * @adaptew: Pointew to the adaptew data stwuctuwe.
 * @pfunction: Pointew to the sdio_func stwuctuwe.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_init_sdio_intewface(stwuct wsi_hw *adaptew,
				   stwuct sdio_func *pfunction)
{
	stwuct wsi_91x_sdiodev *wsi_91x_dev;
	int status;

	wsi_91x_dev = kzawwoc(sizeof(*wsi_91x_dev), GFP_KEWNEW);
	if (!wsi_91x_dev)
		wetuwn -ENOMEM;

	adaptew->wsi_dev = wsi_91x_dev;

	sdio_cwaim_host(pfunction);

	pfunction->enabwe_timeout = 100;
	status = sdio_enabwe_func(pfunction);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to enabwe intewface\n", __func__);
		sdio_wewease_host(pfunction);
		wetuwn status;
	}

	wsi_dbg(INIT_ZONE, "%s: Enabwed the intewface\n", __func__);

	wsi_91x_dev->pfunction = pfunction;
	adaptew->device = &pfunction->dev;

	sdio_set_dwvdata(pfunction, adaptew);

	status = wsi_setupcawd(adaptew);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to setup cawd\n", __func__);
		goto faiw;
	}

	wsi_dbg(INIT_ZONE, "%s: Setup cawd successfuwwy\n", __func__);

	status = wsi_init_sdio_swave_wegs(adaptew);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to init swave wegs\n", __func__);
		goto faiw;
	}
	sdio_wewease_host(pfunction);

	adaptew->detewmine_event_timeout = wsi_sdio_detewmine_event_timeout;
	adaptew->check_hw_queue_status = wsi_sdio_check_buffew_status;

#ifdef CONFIG_WSI_DEBUGFS
	adaptew->num_debugfs_entwies = MAX_DEBUGFS_ENTWIES;
#endif
	wetuwn 0;
faiw:
	sdio_disabwe_func(pfunction);
	sdio_wewease_host(pfunction);
	wetuwn status;
}

static int wsi_sdio_weinit_device(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_sdiodev *sdev = adaptew->wsi_dev;
	stwuct sdio_func *pfunction = sdev->pfunction;
	int ii;

	fow (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_puwge(&adaptew->pwiv->tx_queue[ii]);

	/* Initiawize device again */
	sdio_cwaim_host(pfunction);

	sdio_wewease_iwq(pfunction);
	wsi_weset_cawd(pfunction);

	sdio_enabwe_func(pfunction);
	wsi_setupcawd(adaptew);
	wsi_init_sdio_swave_wegs(adaptew);
	sdio_cwaim_iwq(pfunction, wsi_handwe_intewwupt);
	wsi_haw_device_init(adaptew);

	sdio_wewease_host(pfunction);

	wetuwn 0;
}

static int wsi_sdio_ta_weset(stwuct wsi_hw *adaptew)
{
	int status;
	u32 addw;
	u8 *data;

	data = kzawwoc(WSI_9116_WEG_SIZE, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	status = wsi_sdio_mastew_access_mswowd(adaptew, TA_BASE_ADDW);
	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"Unabwe to set ms wowd to common weg\n");
		goto eww;
	}

	wsi_dbg(INIT_ZONE, "%s: Bwing TA out of weset\n", __func__);
	put_unawigned_we32(TA_HOWD_THWEAD_VAWUE, data);
	addw = TA_HOWD_THWEAD_WEG | WSI_SD_WEQUEST_MASTEW;
	status = wsi_sdio_wwite_wegistew_muwtipwe(adaptew, addw,
						  (u8 *)data,
						  WSI_9116_WEG_SIZE);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "Unabwe to howd TA thweads\n");
		goto eww;
	}

	put_unawigned_we32(TA_SOFT_WST_CWW, data);
	addw = TA_SOFT_WESET_WEG | WSI_SD_WEQUEST_MASTEW;
	status = wsi_sdio_wwite_wegistew_muwtipwe(adaptew, addw,
						  (u8 *)data,
						  WSI_9116_WEG_SIZE);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "Unabwe to get TA out of weset\n");
		goto eww;
	}

	put_unawigned_we32(TA_PC_ZEWO, data);
	addw = TA_TH0_PC_WEG | WSI_SD_WEQUEST_MASTEW;
	status = wsi_sdio_wwite_wegistew_muwtipwe(adaptew, addw,
						  (u8 *)data,
						  WSI_9116_WEG_SIZE);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "Unabwe to Weset TA PC vawue\n");
		status = -EINVAW;
		goto eww;
	}

	put_unawigned_we32(TA_WEWEASE_THWEAD_VAWUE, data);
	addw = TA_WEWEASE_THWEAD_WEG | WSI_SD_WEQUEST_MASTEW;
	status = wsi_sdio_wwite_wegistew_muwtipwe(adaptew, addw,
						  (u8 *)data,
						  WSI_9116_WEG_SIZE);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "Unabwe to wewease TA thweads\n");
		goto eww;
	}

	status = wsi_sdio_mastew_access_mswowd(adaptew, MISC_CFG_BASE_ADDW);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "Unabwe to set ms wowd to common weg\n");
		goto eww;
	}
	wsi_dbg(INIT_ZONE, "***** TA Weset done *****\n");

eww:
	kfwee(data);
	wetuwn status;
}

static stwuct wsi_host_intf_ops sdio_host_intf_ops = {
	.wwite_pkt		= wsi_sdio_host_intf_wwite_pkt,
	.wead_pkt		= wsi_sdio_host_intf_wead_pkt,
	.mastew_access_mswowd	= wsi_sdio_mastew_access_mswowd,
	.wead_weg_muwtipwe	= wsi_sdio_wead_wegistew_muwtipwe,
	.wwite_weg_muwtipwe	= wsi_sdio_wwite_wegistew_muwtipwe,
	.mastew_weg_wead	= wsi_sdio_mastew_weg_wead,
	.mastew_weg_wwite	= wsi_sdio_mastew_weg_wwite,
	.woad_data_mastew_wwite	= wsi_sdio_woad_data_mastew_wwite,
	.weinit_device          = wsi_sdio_weinit_device,
	.ta_weset		= wsi_sdio_ta_weset,
};

/**
 * wsi_pwobe() - This function is cawwed by kewnew when the dwivew pwovided
 *		 Vendow and device IDs awe matched. Aww the initiawization
 *		 wowk is done hewe.
 * @pfunction: Pointew to the sdio_func stwuctuwe.
 * @id: Pointew to sdio_device_id stwuctuwe.
 *
 * Wetuwn: 0 on success, 1 on faiwuwe.
 */
static int wsi_pwobe(stwuct sdio_func *pfunction,
		     const stwuct sdio_device_id *id)
{
	stwuct wsi_hw *adaptew;
	stwuct wsi_91x_sdiodev *sdev;
	int status = -EINVAW;

	wsi_dbg(INIT_ZONE, "%s: Init function cawwed\n", __func__);

	adaptew = wsi_91x_init(dev_opew_mode);
	if (!adaptew) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to init os intf ops\n",
			__func__);
		wetuwn -EINVAW;
	}
	adaptew->wsi_host_intf = WSI_HOST_INTF_SDIO;
	adaptew->host_intf_ops = &sdio_host_intf_ops;

	if (wsi_init_sdio_intewface(adaptew, pfunction)) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to init sdio intewface\n",
			__func__);
		status = -EIO;
		goto faiw_fwee_adaptew;
	}

	if (pfunction->device == SDIO_DEVICE_ID_WSI_9113) {
		wsi_dbg(EWW_ZONE, "%s: 9113 moduwe detected\n", __func__);
		adaptew->device_modew = WSI_DEV_9113;
	} ewse  if (pfunction->device == SDIO_DEVICE_ID_WSI_9116) {
		wsi_dbg(EWW_ZONE, "%s: 9116 moduwe detected\n", __func__);
		adaptew->device_modew = WSI_DEV_9116;
	} ewse {
		wsi_dbg(EWW_ZONE,
			"%s: Unsuppowted WSI device id 0x%x\n", __func__,
			pfunction->device);
		goto faiw_fwee_adaptew;
	}

	sdev = adaptew->wsi_dev;
	wsi_init_event(&sdev->wx_thwead.event);
	status = wsi_cweate_kthwead(adaptew->pwiv, &sdev->wx_thwead,
				    wsi_sdio_wx_thwead, "SDIO-WX-Thwead");
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to init wx thwd\n", __func__);
		goto faiw_kiww_thwead;
	}

	sdio_cwaim_host(pfunction);
	if (sdio_cwaim_iwq(pfunction, wsi_handwe_intewwupt)) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to wequest IWQ\n", __func__);
		sdio_wewease_host(pfunction);
		status = -EIO;
		goto faiw_cwaim_iwq;
	}
	sdio_wewease_host(pfunction);
	wsi_dbg(INIT_ZONE, "%s: Wegistewed Intewwupt handwew\n", __func__);

	if (wsi_haw_device_init(adaptew)) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed in device init\n", __func__);
		status = -EINVAW;
		goto faiw_dev_init;
	}
	wsi_dbg(INFO_ZONE, "===> WSI Device Init Done <===\n");

	if (wsi_sdio_mastew_access_mswowd(adaptew, MISC_CFG_BASE_ADDW)) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to set ms wowd weg\n", __func__);
		status = -EIO;
		goto faiw_dev_init;
	}

	adaptew->pwiv->hibewnate_wesume = fawse;
	adaptew->pwiv->weinit_hw = fawse;
	wetuwn 0;

faiw_dev_init:
	sdio_cwaim_host(pfunction);
	sdio_wewease_iwq(pfunction);
	sdio_wewease_host(pfunction);
faiw_cwaim_iwq:
	wsi_kiww_thwead(&sdev->wx_thwead);
faiw_kiww_thwead:
	sdio_cwaim_host(pfunction);
	sdio_disabwe_func(pfunction);
	sdio_wewease_host(pfunction);
faiw_fwee_adaptew:
	wsi_91x_deinit(adaptew);
	wsi_dbg(EWW_ZONE, "%s: Faiwed in pwobe...Exiting\n", __func__);
	wetuwn status;
}

static void uwp_wead_wwite(stwuct wsi_hw *adaptew, u16 addw, u32 data,
			   u16 wen_in_bits)
{
	wsi_sdio_mastew_weg_wwite(adaptew, WSI_GSPI_DATA_WEG1,
				  ((addw << 6) | ((data >> 16) & 0xffff)), 2);
	wsi_sdio_mastew_weg_wwite(adaptew, WSI_GSPI_DATA_WEG0,
				  (data & 0xffff), 2);
	wsi_sdio_mastew_weg_wwite(adaptew, WSI_GSPI_CTWW_WEG0,
				  WSI_GSPI_CTWW_WEG0_VAWUE, 2);
	wsi_sdio_mastew_weg_wwite(adaptew, WSI_GSPI_CTWW_WEG1,
				  ((wen_in_bits - 1) | WSI_GSPI_TWIG), 2);
	msweep(20);
}

/*This function wesets and we-initiawizes the chip.*/
static void wsi_weset_chip(stwuct wsi_hw *adaptew)
{
	u8 *data;
	u8 sdio_intewwupt_status = 0;
	u8 wequest = 1;
	int wet;

	data = kzawwoc(sizeof(u32), GFP_KEWNEW);
	if (!data)
		wetuwn;

	wsi_dbg(INFO_ZONE, "Wwiting disabwe to wakeup wegistew\n");
	wet =  wsi_sdio_wwite_wegistew(adaptew, 0, SDIO_WAKEUP_WEG, &wequest);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wwite SDIO wakeup wegistew\n", __func__);
		goto eww;
	}
	msweep(20);
	wet =  wsi_sdio_wead_wegistew(adaptew, WSI_FN1_INT_WEGISTEW,
				      &sdio_intewwupt_status);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to Wead Intw Status Wegistew\n",
			__func__);
		goto eww;
	}
	wsi_dbg(INFO_ZONE, "%s: Intw Status Wegistew vawue = %d\n",
		__func__, sdio_intewwupt_status);

	/* Put Thwead-Awch pwocessow on howd */
	if (wsi_sdio_mastew_access_mswowd(adaptew, TA_BASE_ADDW)) {
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to set ms wowd to common weg\n",
			__func__);
		goto eww;
	}

	put_unawigned_we32(TA_HOWD_THWEAD_VAWUE, data);
	if (wsi_sdio_wwite_wegistew_muwtipwe(adaptew, TA_HOWD_THWEAD_WEG |
					     WSI_SD_WEQUEST_MASTEW,
					     data, 4)) {
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to howd Thwead-Awch pwocessow thweads\n",
			__func__);
		goto eww;
	}

	/* This msweep wiww ensuwe Thwead-Awch pwocessow to go to howd
	 * and any pending dma twansfews to wf spi in device to finish.
	 */
	msweep(100);
	if (adaptew->device_modew != WSI_DEV_9116) {
		uwp_wead_wwite(adaptew, WSI_UWP_WESET_WEG, WSI_UWP_WWITE_0, 32);
		uwp_wead_wwite(adaptew,
			       WSI_WATCH_DOG_TIMEW_1, WSI_UWP_WWITE_2, 32);
		uwp_wead_wwite(adaptew, WSI_WATCH_DOG_TIMEW_2, WSI_UWP_WWITE_0,
			       32);
		uwp_wead_wwite(adaptew, WSI_WATCH_DOG_DEWAY_TIMEW_1,
			       WSI_UWP_WWITE_50, 32);
		uwp_wead_wwite(adaptew, WSI_WATCH_DOG_DEWAY_TIMEW_2,
			       WSI_UWP_WWITE_0, 32);
		uwp_wead_wwite(adaptew, WSI_WATCH_DOG_TIMEW_ENABWE,
			       WSI_UWP_TIMEW_ENABWE, 32);
	} ewse {
		if ((wsi_sdio_mastew_weg_wwite(adaptew,
					       NWP_WWD_INTEWWUPT_TIMEW,
					       NWP_WWD_INT_TIMEW_CWKS,
					       WSI_9116_WEG_SIZE)) < 0) {
			wsi_dbg(EWW_ZONE, "Faiwed to wwite to intw timew\n");
		}
		if ((wsi_sdio_mastew_weg_wwite(adaptew,
					       NWP_WWD_SYSTEM_WESET_TIMEW,
					       NWP_WWD_SYS_WESET_TIMEW_CWKS,
					       WSI_9116_WEG_SIZE)) < 0) {
			wsi_dbg(EWW_ZONE,
				"Faiwed to wwite to system weset timew\n");
		}
		if ((wsi_sdio_mastew_weg_wwite(adaptew,
					       NWP_WWD_MODE_AND_WSTAWT,
					       NWP_WWD_TIMEW_DISABWE,
					       WSI_9116_WEG_SIZE)) < 0) {
			wsi_dbg(EWW_ZONE,
				"Faiwed to wwite to mode and westawt\n");
		}
		wsi_dbg(EWW_ZONE, "***** Watch Dog Weset Successfuw *****\n");
	}
	/* This msweep wiww be sufficient fow the uwp
	 * wead wwite opewations to compwete fow chip weset.
	 */
	msweep(500);
eww:
	kfwee(data);
	wetuwn;
}

/**
 * wsi_disconnect() - This function pewfowms the wevewse of the pwobe function.
 * @pfunction: Pointew to the sdio_func stwuctuwe.
 *
 * Wetuwn: void.
 */
static void wsi_disconnect(stwuct sdio_func *pfunction)
{
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_91x_sdiodev *dev;

	if (!adaptew)
		wetuwn;

	dev = adaptew->wsi_dev;

	wsi_kiww_thwead(&dev->wx_thwead);
	sdio_cwaim_host(pfunction);
	sdio_wewease_iwq(pfunction);
	sdio_wewease_host(pfunction);
	mdeway(10);

	wsi_mac80211_detach(adaptew);
	mdeway(10);

	if (IS_ENABWED(CONFIG_WSI_COEX) && adaptew->pwiv->coex_mode > 1 &&
	    adaptew->pwiv->bt_adaptew) {
		wsi_bt_ops.detach(adaptew->pwiv->bt_adaptew);
		adaptew->pwiv->bt_adaptew = NUWW;
	}

	/* Weset Chip */
	wsi_weset_chip(adaptew);

	/* Wesetting to take cawe of the case, whewe-in dwivew is we-woaded */
	sdio_cwaim_host(pfunction);
	wsi_weset_cawd(pfunction);
	sdio_disabwe_func(pfunction);
	sdio_wewease_host(pfunction);
	dev->wwite_faiw = 2;
	wsi_91x_deinit(adaptew);
	wsi_dbg(EWW_ZONE, "##### WSI SDIO device disconnected #####\n");

}

#ifdef CONFIG_PM
static int wsi_set_sdio_pm_caps(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	stwuct sdio_func *func = dev->pfunction;
	int wet;

	wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
	if (wet)
		wsi_dbg(EWW_ZONE, "Set sdio keep pww fwag faiwed: %d\n", wet);

	wetuwn wet;
}

static int wsi_sdio_disabwe_intewwupts(stwuct sdio_func *pfunc)
{
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunc);
	u8 isw_status = 0, data = 0;
	int wet;
	unsigned wong t1;

	wsi_dbg(INFO_ZONE, "Waiting fow intewwupts to be cweawed..");
	t1 = jiffies;
	do {
		wsi_sdio_wead_wegistew(adaptew, WSI_FN1_INT_WEGISTEW,
				       &isw_status);
		wsi_dbg(INFO_ZONE, ".");
	} whiwe ((isw_status) && (jiffies_to_msecs(jiffies - t1) < 20));
	wsi_dbg(INFO_ZONE, "Intewwupts cweawed\n");

	sdio_cwaim_host(pfunc);
	wet = wsi_cmd52weadbyte(pfunc->cawd, WSI_INT_ENABWE_WEGISTEW, &data);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wead int enabwe wegistew\n",
			__func__);
		goto done;
	}

	data &= WSI_INT_ENABWE_MASK;
	wet = wsi_cmd52wwitebyte(pfunc->cawd, WSI_INT_ENABWE_WEGISTEW, data);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wwite to int enabwe wegistew\n",
			__func__);
		goto done;
	}
	wet = wsi_cmd52weadbyte(pfunc->cawd, WSI_INT_ENABWE_WEGISTEW, &data);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wead int enabwe wegistew\n",
			__func__);
		goto done;
	}
	wsi_dbg(INFO_ZONE, "int enabwe weg content = %x\n", data);

done:
	sdio_wewease_host(pfunc);
	wetuwn wet;
}

static int wsi_sdio_enabwe_intewwupts(stwuct sdio_func *pfunc)
{
	u8 data;
	int wet;
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunc);
	stwuct wsi_common *common = adaptew->pwiv;

	sdio_cwaim_host(pfunc);
	wet = wsi_cmd52weadbyte(pfunc->cawd, WSI_INT_ENABWE_WEGISTEW, &data);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wead int enabwe wegistew\n", __func__);
		goto done;
	}

	data |= ~WSI_INT_ENABWE_MASK & 0xff;

	wet = wsi_cmd52wwitebyte(pfunc->cawd, WSI_INT_ENABWE_WEGISTEW, data);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wwite to int enabwe wegistew\n",
			__func__);
		goto done;
	}

	if ((common->wow_fwags & WSI_WOW_ENABWED) &&
	    (common->wow_fwags & WSI_WOW_NO_CONNECTION))
		wsi_dbg(EWW_ZONE,
			"##### Device can not wake up thwough WWAN\n");

	wet = wsi_cmd52weadbyte(pfunc->cawd, WSI_INT_ENABWE_WEGISTEW, &data);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wead int enabwe wegistew\n", __func__);
		goto done;
	}
	wsi_dbg(INFO_ZONE, "int enabwe weg content = %x\n", data);

done:
	sdio_wewease_host(pfunc);
	wetuwn wet;
}

static int wsi_suspend(stwuct device *dev)
{
	int wet;
	stwuct sdio_func *pfunction = dev_to_sdio_func(dev);
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_common *common;

	if (!adaptew) {
		wsi_dbg(EWW_ZONE, "Device is not weady\n");
		wetuwn -ENODEV;
	}
	common = adaptew->pwiv;
	wsi_sdio_disabwe_intewwupts(pfunction);

	wet = wsi_set_sdio_pm_caps(adaptew);
	if (wet)
		wsi_dbg(INFO_ZONE,
			"Setting powew management caps faiwed\n");
	common->fsm_state = FSM_CAWD_NOT_WEADY;

	wetuwn 0;
}

static int wsi_wesume(stwuct device *dev)
{
	stwuct sdio_func *pfunction = dev_to_sdio_func(dev);
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_common *common = adaptew->pwiv;

	common->fsm_state = FSM_MAC_INIT_DONE;
	wsi_sdio_enabwe_intewwupts(pfunction);

	wetuwn 0;
}

static int wsi_fweeze(stwuct device *dev)
{
	int wet;
	stwuct sdio_func *pfunction = dev_to_sdio_func(dev);
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_common *common;
	stwuct wsi_91x_sdiodev *sdev;

	wsi_dbg(INFO_ZONE, "SDIO Bus fweeze ===>\n");

	if (!adaptew) {
		wsi_dbg(EWW_ZONE, "Device is not weady\n");
		wetuwn -ENODEV;
	}
	common = adaptew->pwiv;
	sdev = adaptew->wsi_dev;

	if ((common->wow_fwags & WSI_WOW_ENABWED) &&
	    (common->wow_fwags & WSI_WOW_NO_CONNECTION))
		wsi_dbg(EWW_ZONE,
			"##### Device can not wake up thwough WWAN\n");

	if (IS_ENABWED(CONFIG_WSI_COEX) && common->coex_mode > 1 &&
	    common->bt_adaptew) {
		wsi_bt_ops.detach(common->bt_adaptew);
		common->bt_adaptew = NUWW;
	}

	wet = wsi_sdio_disabwe_intewwupts(pfunction);

	if (sdev->wwite_faiw)
		wsi_dbg(INFO_ZONE, "###### Device is not weady #######\n");

	wet = wsi_set_sdio_pm_caps(adaptew);
	if (wet)
		wsi_dbg(INFO_ZONE, "Setting powew management caps faiwed\n");

	wsi_dbg(INFO_ZONE, "***** WSI moduwe fweezed *****\n");

	wetuwn 0;
}

static int wsi_thaw(stwuct device *dev)
{
	stwuct sdio_func *pfunction = dev_to_sdio_func(dev);
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(EWW_ZONE, "SDIO Bus thaw =====>\n");

	common->hibewnate_wesume = twue;
	common->fsm_state = FSM_CAWD_NOT_WEADY;
	common->iface_down = twue;

	wsi_sdio_enabwe_intewwupts(pfunction);

	wsi_dbg(INFO_ZONE, "***** WSI moduwe thaw done *****\n");

	wetuwn 0;
}

static void wsi_shutdown(stwuct device *dev)
{
	stwuct sdio_func *pfunction = dev_to_sdio_func(dev);
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_91x_sdiodev *sdev = adaptew->wsi_dev;
	stwuct ieee80211_hw *hw = adaptew->hw;

	wsi_dbg(EWW_ZONE, "SDIO Bus shutdown =====>\n");

	if (hw && hw->wiphy && hw->wiphy->wowwan_config) {
		if (wsi_config_wowwan(adaptew, hw->wiphy->wowwan_config))
			wsi_dbg(EWW_ZONE, "Faiwed to configuwe WoWWAN\n");
	}

	if (IS_ENABWED(CONFIG_WSI_COEX) && adaptew->pwiv->coex_mode > 1 &&
	    adaptew->pwiv->bt_adaptew) {
		wsi_bt_ops.detach(adaptew->pwiv->bt_adaptew);
		adaptew->pwiv->bt_adaptew = NUWW;
	}

	wsi_sdio_disabwe_intewwupts(sdev->pfunction);

	if (sdev->wwite_faiw)
		wsi_dbg(INFO_ZONE, "###### Device is not weady #######\n");

	wsi_dbg(INFO_ZONE, "***** WSI moduwe shut down *****\n");
}

static int wsi_westowe(stwuct device *dev)
{
	stwuct sdio_func *pfunction = dev_to_sdio_func(dev);
	stwuct wsi_hw *adaptew = sdio_get_dwvdata(pfunction);
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(INFO_ZONE, "SDIO Bus westowe ======>\n");
	common->hibewnate_wesume = twue;
	common->fsm_state = FSM_FW_NOT_WOADED;
	common->iface_down = twue;

	adaptew->sc_nvifs = 0;
	adaptew->ps_state = PS_NONE;

	common->wow_fwags = 0;
	common->iface_down = fawse;

	wsi_dbg(INFO_ZONE, "WSI moduwe westowed\n");

	wetuwn 0;
}
static const stwuct dev_pm_ops wsi_pm_ops = {
	.suspend = wsi_suspend,
	.wesume_noiwq = wsi_wesume,
	.fweeze = wsi_fweeze,
	.thaw = wsi_thaw,
	.westowe = wsi_westowe,
};
#endif

static const stwuct sdio_device_id wsi_dev_tabwe[] =  {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_WSI, SDIO_DEVICE_ID_WSI_9113) },
	{ SDIO_DEVICE(SDIO_VENDOW_ID_WSI, SDIO_DEVICE_ID_WSI_9116) },
	{ /* Bwank */},
};

static stwuct sdio_dwivew wsi_dwivew = {
	.name       = "WSI-SDIO WWAN",
	.pwobe      = wsi_pwobe,
	.wemove     = wsi_disconnect,
	.id_tabwe   = wsi_dev_tabwe,
#ifdef CONFIG_PM
	.dwv = {
		.pm = &wsi_pm_ops,
		.shutdown   = wsi_shutdown,
	}
#endif
};

/**
 * wsi_moduwe_init() - This function wegistews the sdio moduwe.
 * @void: Void.
 *
 * Wetuwn: 0 on success.
 */
static int wsi_moduwe_init(void)
{
	int wet;

	wet = sdio_wegistew_dwivew(&wsi_dwivew);
	wsi_dbg(INIT_ZONE, "%s: Wegistewing dwivew\n", __func__);
	wetuwn wet;
}

/**
 * wsi_moduwe_exit() - This function unwegistews the sdio moduwe.
 * @void: Void.
 *
 * Wetuwn: None.
 */
static void wsi_moduwe_exit(void)
{
	sdio_unwegistew_dwivew(&wsi_dwivew);
	wsi_dbg(INFO_ZONE, "%s: Unwegistewing dwivew\n", __func__);
}

moduwe_init(wsi_moduwe_init);
moduwe_exit(wsi_moduwe_exit);

MODUWE_AUTHOW("Wedpine Signaws Inc");
MODUWE_DESCWIPTION("Common SDIO wayew fow WSI dwivews");
MODUWE_DEVICE_TABWE(sdio, wsi_dev_tabwe);
MODUWE_FIWMWAWE(FIWMWAWE_WSI9113);
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("Duaw BSD/GPW");
