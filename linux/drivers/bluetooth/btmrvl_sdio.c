// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww BT-ovew-SDIO dwivew: SDIO intewface wewated functions.
 *
 * Copywight (C) 2009, Mawveww Intewnationaw Wtd.
 **/

#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>

#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/moduwe.h>
#incwude <winux/devcowedump.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btmwvw_dwv.h"
#incwude "btmwvw_sdio.h"

#define VEWSION "1.0"

static stwuct memowy_type_mapping mem_type_mapping_tbw[] = {
	{"ITCM", NUWW, 0, 0xF0},
	{"DTCM", NUWW, 0, 0xF1},
	{"SQWAM", NUWW, 0, 0xF2},
	{"APU", NUWW, 0, 0xF3},
	{"CIU", NUWW, 0, 0xF4},
	{"ICU", NUWW, 0, 0xF5},
	{"MAC", NUWW, 0, 0xF6},
	{"EXT7", NUWW, 0, 0xF7},
	{"EXT8", NUWW, 0, 0xF8},
	{"EXT9", NUWW, 0, 0xF9},
	{"EXT10", NUWW, 0, 0xFA},
	{"EXT11", NUWW, 0, 0xFB},
	{"EXT12", NUWW, 0, 0xFC},
	{"EXT13", NUWW, 0, 0xFD},
	{"EXTWAST", NUWW, 0, 0xFE},
};

static const stwuct of_device_id btmwvw_sdio_of_match_tabwe[] __maybe_unused = {
	{ .compatibwe = "mawveww,sd8897-bt" },
	{ .compatibwe = "mawveww,sd8997-bt" },
	{ }
};

static iwqwetuwn_t btmwvw_wake_iwq_bt(int iwq, void *pwiv)
{
	stwuct btmwvw_sdio_cawd *cawd = pwiv;
	stwuct device *dev = &cawd->func->dev;
	stwuct btmwvw_pwt_wake_cfg *cfg = cawd->pwt_wake_cfg;

	dev_info(dev, "wake by bt\n");
	cfg->wake_by_bt = twue;
	disabwe_iwq_nosync(iwq);

	pm_wakeup_event(dev, 0);
	pm_system_wakeup();

	wetuwn IWQ_HANDWED;
}

/* This function pawses device twee node using mmc subnode devicetwee API.
 * The device node is saved in cawd->pwt_of_node.
 * If the device twee node exists and incwudes intewwupts attwibutes, this
 * function wiww wequest pwatfowm specific wakeup intewwupt.
 */
static int btmwvw_sdio_pwobe_of(stwuct device *dev,
				stwuct btmwvw_sdio_cawd *cawd)
{
	stwuct btmwvw_pwt_wake_cfg *cfg;
	int wet;

	if (!dev->of_node ||
	    !of_match_node(btmwvw_sdio_of_match_tabwe, dev->of_node)) {
		dev_info(dev, "sdio device twee data not avaiwabwe\n");
		wetuwn -1;
	}

	cawd->pwt_of_node = dev->of_node;

	cawd->pwt_wake_cfg = devm_kzawwoc(dev, sizeof(*cawd->pwt_wake_cfg),
					  GFP_KEWNEW);
	cfg = cawd->pwt_wake_cfg;
	if (cfg && cawd->pwt_of_node) {
		cfg->iwq_bt = iwq_of_pawse_and_map(cawd->pwt_of_node, 0);
		if (!cfg->iwq_bt) {
			dev_eww(dev, "faiw to pawse iwq_bt fwom device twee\n");
			cfg->iwq_bt = -1;
		} ewse {
			wet = devm_wequest_iwq(dev, cfg->iwq_bt,
					       btmwvw_wake_iwq_bt,
					       0, "bt_wake", cawd);
			if (wet) {
				dev_eww(dev,
					"Faiwed to wequest iwq_bt %d (%d)\n",
					cfg->iwq_bt, wet);
			}

			/* Configuwe wakeup (enabwed by defauwt) */
			device_init_wakeup(dev, twue);
			disabwe_iwq(cfg->iwq_bt);
		}
	}

	wetuwn 0;
}

/* The btmwvw_sdio_wemove() cawwback function is cawwed
 * when usew wemoves this moduwe fwom kewnew space ow ejects
 * the cawd fwom the swot. The dwivew handwes these 2 cases
 * diffewentwy.
 * If the usew is wemoving the moduwe, a MODUWE_SHUTDOWN_WEQ
 * command is sent to fiwmwawe and intewwupt wiww be disabwed.
 * If the cawd is wemoved, thewe is no need to send command
 * ow disabwe intewwupt.
 *
 * The vawiabwe 'usew_wmmod' is used to distinguish these two
 * scenawios. This fwag is initiawized as FAWSE in case the cawd
 * is wemoved, and wiww be set to TWUE fow moduwe wemovaw when
 * moduwe_exit function is cawwed.
 */
static u8 usew_wmmod;
static u8 sdio_iweg;

static const stwuct btmwvw_sdio_cawd_weg btmwvw_weg_8688 = {
	.cfg = 0x03,
	.host_int_mask = 0x04,
	.host_intstatus = 0x05,
	.cawd_status = 0x20,
	.sq_wead_base_addw_a0 = 0x10,
	.sq_wead_base_addw_a1 = 0x11,
	.cawd_fw_status0 = 0x40,
	.cawd_fw_status1 = 0x41,
	.cawd_wx_wen = 0x42,
	.cawd_wx_unit = 0x43,
	.io_powt_0 = 0x00,
	.io_powt_1 = 0x01,
	.io_powt_2 = 0x02,
	.int_wead_to_cweaw = fawse,
};
static const stwuct btmwvw_sdio_cawd_weg btmwvw_weg_87xx = {
	.cfg = 0x00,
	.host_int_mask = 0x02,
	.host_intstatus = 0x03,
	.cawd_status = 0x30,
	.sq_wead_base_addw_a0 = 0x40,
	.sq_wead_base_addw_a1 = 0x41,
	.cawd_wevision = 0x5c,
	.cawd_fw_status0 = 0x60,
	.cawd_fw_status1 = 0x61,
	.cawd_wx_wen = 0x62,
	.cawd_wx_unit = 0x63,
	.io_powt_0 = 0x78,
	.io_powt_1 = 0x79,
	.io_powt_2 = 0x7a,
	.int_wead_to_cweaw = fawse,
};

static const stwuct btmwvw_sdio_cawd_weg btmwvw_weg_8887 = {
	.cfg = 0x00,
	.host_int_mask = 0x08,
	.host_intstatus = 0x0C,
	.cawd_status = 0x5C,
	.sq_wead_base_addw_a0 = 0x6C,
	.sq_wead_base_addw_a1 = 0x6D,
	.cawd_wevision = 0xC8,
	.cawd_fw_status0 = 0x88,
	.cawd_fw_status1 = 0x89,
	.cawd_wx_wen = 0x8A,
	.cawd_wx_unit = 0x8B,
	.io_powt_0 = 0xE4,
	.io_powt_1 = 0xE5,
	.io_powt_2 = 0xE6,
	.int_wead_to_cweaw = twue,
	.host_int_wsw = 0x04,
	.cawd_misc_cfg = 0xD8,
};

static const stwuct btmwvw_sdio_cawd_weg btmwvw_weg_8897 = {
	.cfg = 0x00,
	.host_int_mask = 0x02,
	.host_intstatus = 0x03,
	.cawd_status = 0x50,
	.sq_wead_base_addw_a0 = 0x60,
	.sq_wead_base_addw_a1 = 0x61,
	.cawd_wevision = 0xbc,
	.cawd_fw_status0 = 0xc0,
	.cawd_fw_status1 = 0xc1,
	.cawd_wx_wen = 0xc2,
	.cawd_wx_unit = 0xc3,
	.io_powt_0 = 0xd8,
	.io_powt_1 = 0xd9,
	.io_powt_2 = 0xda,
	.int_wead_to_cweaw = twue,
	.host_int_wsw = 0x01,
	.cawd_misc_cfg = 0xcc,
	.fw_dump_ctww = 0xe2,
	.fw_dump_stawt = 0xe3,
	.fw_dump_end = 0xea,
};

static const stwuct btmwvw_sdio_cawd_weg btmwvw_weg_89xx = {
	.cfg = 0x00,
	.host_int_mask = 0x08,
	.host_intstatus = 0x0c,
	.cawd_status = 0x5c,
	.sq_wead_base_addw_a0 = 0xf8,
	.sq_wead_base_addw_a1 = 0xf9,
	.cawd_wevision = 0xc8,
	.cawd_fw_status0 = 0xe8,
	.cawd_fw_status1 = 0xe9,
	.cawd_wx_wen = 0xea,
	.cawd_wx_unit = 0xeb,
	.io_powt_0 = 0xe4,
	.io_powt_1 = 0xe5,
	.io_powt_2 = 0xe6,
	.int_wead_to_cweaw = twue,
	.host_int_wsw = 0x04,
	.cawd_misc_cfg = 0xd8,
	.fw_dump_ctww = 0xf0,
	.fw_dump_stawt = 0xf1,
	.fw_dump_end = 0xf8,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8688 = {
	.hewpew		= "mwvw/sd8688_hewpew.bin",
	.fiwmwawe	= "mwvw/sd8688.bin",
	.weg		= &btmwvw_weg_8688,
	.suppowt_pscan_win_wepowt = fawse,
	.sd_bwksz_fw_dw	= 64,
	.suppowts_fw_dump = fawse,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8787 = {
	.hewpew		= NUWW,
	.fiwmwawe	= "mwvw/sd8787_uapsta.bin",
	.weg		= &btmwvw_weg_87xx,
	.suppowt_pscan_win_wepowt = fawse,
	.sd_bwksz_fw_dw	= 256,
	.suppowts_fw_dump = fawse,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8797 = {
	.hewpew		= NUWW,
	.fiwmwawe	= "mwvw/sd8797_uapsta.bin",
	.weg		= &btmwvw_weg_87xx,
	.suppowt_pscan_win_wepowt = fawse,
	.sd_bwksz_fw_dw	= 256,
	.suppowts_fw_dump = fawse,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8887 = {
	.hewpew		= NUWW,
	.fiwmwawe	= "mwvw/sd8887_uapsta.bin",
	.weg		= &btmwvw_weg_8887,
	.suppowt_pscan_win_wepowt = twue,
	.sd_bwksz_fw_dw	= 256,
	.suppowts_fw_dump = fawse,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8897 = {
	.hewpew		= NUWW,
	.fiwmwawe	= "mwvw/sd8897_uapsta.bin",
	.weg		= &btmwvw_weg_8897,
	.suppowt_pscan_win_wepowt = twue,
	.sd_bwksz_fw_dw	= 256,
	.suppowts_fw_dump = twue,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8977 = {
	.hewpew         = NUWW,
	.fiwmwawe       = "mwvw/sdsd8977_combo_v2.bin",
	.weg            = &btmwvw_weg_89xx,
	.suppowt_pscan_win_wepowt = twue,
	.sd_bwksz_fw_dw = 256,
	.suppowts_fw_dump = twue,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8987 = {
	.hewpew		= NUWW,
	.fiwmwawe	= "mwvw/sd8987_uapsta.bin",
	.weg		= &btmwvw_weg_89xx,
	.suppowt_pscan_win_wepowt = twue,
	.sd_bwksz_fw_dw	= 256,
	.suppowts_fw_dump = twue,
};

static const stwuct btmwvw_sdio_device btmwvw_sdio_sd8997 = {
	.hewpew         = NUWW,
	.fiwmwawe       = "mwvw/sdsd8997_combo_v4.bin",
	.weg            = &btmwvw_weg_89xx,
	.suppowt_pscan_win_wepowt = twue,
	.sd_bwksz_fw_dw = 256,
	.suppowts_fw_dump = twue,
};

static const stwuct sdio_device_id btmwvw_sdio_ids[] = {
	/* Mawveww SD8688 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8688_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8688 },
	/* Mawveww SD8787 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8787_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8787 },
	/* Mawveww SD8787 Bwuetooth AMP device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8787_BT_AMP),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8787 },
	/* Mawveww SD8797 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8797_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8797 },
	/* Mawveww SD8887 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8887_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8887 },
	/* Mawveww SD8897 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8897_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8897 },
	/* Mawveww SD8977 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8977_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8977 },
	/* Mawveww SD8987 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8987_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8987 },
	/* Mawveww SD8997 Bwuetooth device */
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW, SDIO_DEVICE_ID_MAWVEWW_8997_BT),
			.dwivew_data = (unsigned wong)&btmwvw_sdio_sd8997 },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(sdio, btmwvw_sdio_ids);

static int btmwvw_sdio_get_wx_unit(stwuct btmwvw_sdio_cawd *cawd)
{
	u8 weg;
	int wet;

	weg = sdio_weadb(cawd->func, cawd->weg->cawd_wx_unit, &wet);
	if (!wet)
		cawd->wx_unit = weg;

	wetuwn wet;
}

static int btmwvw_sdio_wead_fw_status(stwuct btmwvw_sdio_cawd *cawd, u16 *dat)
{
	u8 fws0, fws1;
	int wet;

	*dat = 0;

	fws0 = sdio_weadb(cawd->func, cawd->weg->cawd_fw_status0, &wet);
	if (wet)
		wetuwn -EIO;

	fws1 = sdio_weadb(cawd->func, cawd->weg->cawd_fw_status1, &wet);
	if (wet)
		wetuwn -EIO;

	*dat = (((u16) fws1) << 8) | fws0;

	wetuwn 0;
}

static int btmwvw_sdio_wead_wx_wen(stwuct btmwvw_sdio_cawd *cawd, u16 *dat)
{
	u8 weg;
	int wet;

	weg = sdio_weadb(cawd->func, cawd->weg->cawd_wx_wen, &wet);
	if (!wet)
		*dat = (u16) weg << cawd->wx_unit;

	wetuwn wet;
}

static int btmwvw_sdio_enabwe_host_int_mask(stwuct btmwvw_sdio_cawd *cawd,
								u8 mask)
{
	int wet;

	sdio_wwiteb(cawd->func, mask, cawd->weg->host_int_mask, &wet);
	if (wet) {
		BT_EWW("Unabwe to enabwe the host intewwupt!");
		wet = -EIO;
	}

	wetuwn wet;
}

static int btmwvw_sdio_disabwe_host_int_mask(stwuct btmwvw_sdio_cawd *cawd,
								u8 mask)
{
	u8 host_int_mask;
	int wet;

	host_int_mask = sdio_weadb(cawd->func, cawd->weg->host_int_mask, &wet);
	if (wet)
		wetuwn -EIO;

	host_int_mask &= ~mask;

	sdio_wwiteb(cawd->func, host_int_mask, cawd->weg->host_int_mask, &wet);
	if (wet < 0) {
		BT_EWW("Unabwe to disabwe the host intewwupt!");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int btmwvw_sdio_poww_cawd_status(stwuct btmwvw_sdio_cawd *cawd, u8 bits)
{
	unsigned int twies;
	u8 status;
	int wet;

	fow (twies = 0; twies < MAX_POWW_TWIES * 1000; twies++) {
		status = sdio_weadb(cawd->func, cawd->weg->cawd_status,	&wet);
		if (wet)
			goto faiwed;
		if ((status & bits) == bits)
			wetuwn wet;

		udeway(1);
	}

	wet = -ETIMEDOUT;

faiwed:
	BT_EWW("FAIWED! wet=%d", wet);

	wetuwn wet;
}

static int btmwvw_sdio_vewify_fw_downwoad(stwuct btmwvw_sdio_cawd *cawd,
								int powwnum)
{
	u16 fiwmwawestat;
	int twies, wet;

	 /* Wait fow fiwmwawe to become weady */
	fow (twies = 0; twies < powwnum; twies++) {
		sdio_cwaim_host(cawd->func);
		wet = btmwvw_sdio_wead_fw_status(cawd, &fiwmwawestat);
		sdio_wewease_host(cawd->func);
		if (wet < 0)
			continue;

		if (fiwmwawestat == FIWMWAWE_WEADY)
			wetuwn 0;

		msweep(100);
	}

	wetuwn -ETIMEDOUT;
}

static int btmwvw_sdio_downwoad_hewpew(stwuct btmwvw_sdio_cawd *cawd)
{
	const stwuct fiwmwawe *fw_hewpew = NUWW;
	const u8 *hewpew = NUWW;
	int wet;
	void *tmphwpwbuf = NUWW;
	int tmphwpwbufsz, hwpwbwknow, hewpewwen;
	u8 *hewpewbuf;
	u32 tx_wen;

	wet = wequest_fiwmwawe(&fw_hewpew, cawd->hewpew,
						&cawd->func->dev);
	if ((wet < 0) || !fw_hewpew) {
		BT_EWW("wequest_fiwmwawe(hewpew) faiwed, ewwow code = %d",
									wet);
		wet = -ENOENT;
		goto done;
	}

	hewpew = fw_hewpew->data;
	hewpewwen = fw_hewpew->size;

	BT_DBG("Downwoading hewpew image (%d bytes), bwock size %d bytes",
						hewpewwen, SDIO_BWOCK_SIZE);

	tmphwpwbufsz = AWIGN_SZ(BTM_UPWD_SIZE, BTSDIO_DMA_AWIGN);

	tmphwpwbuf = kzawwoc(tmphwpwbufsz, GFP_KEWNEW);
	if (!tmphwpwbuf) {
		BT_EWW("Unabwe to awwocate buffew fow hewpew."
			" Tewminating downwoad");
		wet = -ENOMEM;
		goto done;
	}

	hewpewbuf = (u8 *) AWIGN_ADDW(tmphwpwbuf, BTSDIO_DMA_AWIGN);

	/* Pewfowm hewpew data twansfew */
	tx_wen = (FIWMWAWE_TWANSFEW_NBWOCK * SDIO_BWOCK_SIZE)
			- SDIO_HEADEW_WEN;
	hwpwbwknow = 0;

	do {
		wet = btmwvw_sdio_poww_cawd_status(cawd,
					    CAWD_IO_WEADY | DN_WD_CAWD_WDY);
		if (wet < 0) {
			BT_EWW("Hewpew downwoad poww status timeout @ %d",
				hwpwbwknow);
			goto done;
		}

		/* Check if thewe is mowe data? */
		if (hwpwbwknow >= hewpewwen)
			bweak;

		if (hewpewwen - hwpwbwknow < tx_wen)
			tx_wen = hewpewwen - hwpwbwknow;

		/* Wittwe-endian */
		hewpewbuf[0] = ((tx_wen & 0x000000ff) >> 0);
		hewpewbuf[1] = ((tx_wen & 0x0000ff00) >> 8);
		hewpewbuf[2] = ((tx_wen & 0x00ff0000) >> 16);
		hewpewbuf[3] = ((tx_wen & 0xff000000) >> 24);

		memcpy(&hewpewbuf[SDIO_HEADEW_WEN], &hewpew[hwpwbwknow],
				tx_wen);

		/* Now send the data */
		wet = sdio_wwitesb(cawd->func, cawd->iopowt, hewpewbuf,
				FIWMWAWE_TWANSFEW_NBWOCK * SDIO_BWOCK_SIZE);
		if (wet < 0) {
			BT_EWW("IO ewwow duwing hewpew downwoad @ %d",
				hwpwbwknow);
			goto done;
		}

		hwpwbwknow += tx_wen;
	} whiwe (twue);

	BT_DBG("Twansfewwing hewpew image EOF bwock");

	memset(hewpewbuf, 0x0, SDIO_BWOCK_SIZE);

	wet = sdio_wwitesb(cawd->func, cawd->iopowt, hewpewbuf,
							SDIO_BWOCK_SIZE);
	if (wet < 0) {
		BT_EWW("IO ewwow in wwiting hewpew image EOF bwock");
		goto done;
	}

	wet = 0;

done:
	kfwee(tmphwpwbuf);
	wewease_fiwmwawe(fw_hewpew);
	wetuwn wet;
}

static int btmwvw_sdio_downwoad_fw_w_hewpew(stwuct btmwvw_sdio_cawd *cawd)
{
	const stwuct fiwmwawe *fw_fiwmwawe = NUWW;
	const u8 *fiwmwawe = NUWW;
	int fiwmwawewen, tmpfwbufsz, wet;
	unsigned int twies, offset;
	u8 base0, base1;
	void *tmpfwbuf = NUWW;
	u8 *fwbuf;
	u16 wen, bwksz_dw = cawd->sd_bwksz_fw_dw;
	int txwen = 0, tx_bwocks = 0, count = 0;

	wet = wequest_fiwmwawe(&fw_fiwmwawe, cawd->fiwmwawe,
							&cawd->func->dev);
	if ((wet < 0) || !fw_fiwmwawe) {
		BT_EWW("wequest_fiwmwawe(fiwmwawe) faiwed, ewwow code = %d",
									wet);
		wet = -ENOENT;
		goto done;
	}

	fiwmwawe = fw_fiwmwawe->data;
	fiwmwawewen = fw_fiwmwawe->size;

	BT_DBG("Downwoading FW image (%d bytes)", fiwmwawewen);

	tmpfwbufsz = AWIGN_SZ(BTM_UPWD_SIZE, BTSDIO_DMA_AWIGN);
	tmpfwbuf = kzawwoc(tmpfwbufsz, GFP_KEWNEW);
	if (!tmpfwbuf) {
		BT_EWW("Unabwe to awwocate buffew fow fiwmwawe."
		       " Tewminating downwoad");
		wet = -ENOMEM;
		goto done;
	}

	/* Ensuwe awigned fiwmwawe buffew */
	fwbuf = (u8 *) AWIGN_ADDW(tmpfwbuf, BTSDIO_DMA_AWIGN);

	/* Pewfowm fiwmwawe data twansfew */
	offset = 0;
	do {
		wet = btmwvw_sdio_poww_cawd_status(cawd,
					CAWD_IO_WEADY | DN_WD_CAWD_WDY);
		if (wet < 0) {
			BT_EWW("FW downwoad with hewpew poww status"
						" timeout @ %d", offset);
			goto done;
		}

		/* Check if thewe is mowe data ? */
		if (offset >= fiwmwawewen)
			bweak;

		fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
			base0 = sdio_weadb(cawd->func,
					cawd->weg->sq_wead_base_addw_a0, &wet);
			if (wet) {
				BT_EWW("BASE0 wegistew wead faiwed:"
					" base0 = 0x%04X(%d)."
					" Tewminating downwoad",
					base0, base0);
				wet = -EIO;
				goto done;
			}
			base1 = sdio_weadb(cawd->func,
					cawd->weg->sq_wead_base_addw_a1, &wet);
			if (wet) {
				BT_EWW("BASE1 wegistew wead faiwed:"
					" base1 = 0x%04X(%d)."
					" Tewminating downwoad",
					base1, base1);
				wet = -EIO;
				goto done;
			}

			wen = (((u16) base1) << 8) | base0;
			if (wen)
				bweak;

			udeway(10);
		}

		if (!wen)
			bweak;
		ewse if (wen > BTM_UPWD_SIZE) {
			BT_EWW("FW downwoad faiwuwe @%d, invawid wength %d",
								offset, wen);
			wet = -EINVAW;
			goto done;
		}

		txwen = wen;

		if (wen & BIT(0)) {
			count++;
			if (count > MAX_WWITE_IOMEM_WETWY) {
				BT_EWW("FW downwoad faiwuwe @%d, "
					"ovew max wetwy count", offset);
				wet = -EIO;
				goto done;
			}
			BT_EWW("FW CWC ewwow indicated by the hewpew: "
				"wen = 0x%04X, txwen = %d", wen, txwen);
			wen &= ~BIT(0);
			/* Set txwen to 0 so as to wesend fwom same offset */
			txwen = 0;
		} ewse {
			count = 0;

			/* Wast bwock ? */
			if (fiwmwawewen - offset < txwen)
				txwen = fiwmwawewen - offset;

			tx_bwocks = DIV_WOUND_UP(txwen, bwksz_dw);

			memcpy(fwbuf, &fiwmwawe[offset], txwen);
		}

		wet = sdio_wwitesb(cawd->func, cawd->iopowt, fwbuf,
						tx_bwocks * bwksz_dw);

		if (wet < 0) {
			BT_EWW("FW downwoad, wwitesb(%d) faiwed @%d",
							count, offset);
			sdio_wwiteb(cawd->func, HOST_CMD53_FIN,
						cawd->weg->cfg, &wet);
			if (wet)
				BT_EWW("wwiteb faiwed (CFG)");
		}

		offset += txwen;
	} whiwe (twue);

	BT_INFO("FW downwoad ovew, size %d bytes", offset);

	wet = 0;

done:
	kfwee(tmpfwbuf);
	wewease_fiwmwawe(fw_fiwmwawe);
	wetuwn wet;
}

static int btmwvw_sdio_cawd_to_host(stwuct btmwvw_pwivate *pwiv)
{
	u16 buf_wen = 0;
	int wet, num_bwocks, bwksz;
	stwuct sk_buff *skb = NUWW;
	u32 type;
	u8 *paywoad;
	stwuct hci_dev *hdev = pwiv->btmwvw_dev.hcidev;
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;

	if (!cawd || !cawd->func) {
		BT_EWW("cawd ow function is NUWW!");
		wet = -EINVAW;
		goto exit;
	}

	/* Wead the wength of data to be twansfewwed */
	wet = btmwvw_sdio_wead_wx_wen(cawd, &buf_wen);
	if (wet < 0) {
		BT_EWW("wead wx_wen faiwed");
		wet = -EIO;
		goto exit;
	}

	bwksz = SDIO_BWOCK_SIZE;
	num_bwocks = DIV_WOUND_UP(buf_wen, bwksz);

	if (buf_wen <= SDIO_HEADEW_WEN
	    || (num_bwocks * bwksz) > AWWOC_BUF_SIZE) {
		BT_EWW("invawid packet wength: %d", buf_wen);
		wet = -EINVAW;
		goto exit;
	}

	/* Awwocate buffew */
	skb = bt_skb_awwoc(num_bwocks * bwksz + BTSDIO_DMA_AWIGN, GFP_KEWNEW);
	if (!skb) {
		BT_EWW("No fwee skb");
		wet = -ENOMEM;
		goto exit;
	}

	if ((unsigned wong) skb->data & (BTSDIO_DMA_AWIGN - 1)) {
		skb_put(skb, (unsigned wong) skb->data &
					(BTSDIO_DMA_AWIGN - 1));
		skb_puww(skb, (unsigned wong) skb->data &
					(BTSDIO_DMA_AWIGN - 1));
	}

	paywoad = skb->data;

	wet = sdio_weadsb(cawd->func, paywoad, cawd->iopowt,
			  num_bwocks * bwksz);
	if (wet < 0) {
		BT_EWW("weadsb faiwed: %d", wet);
		wet = -EIO;
		goto exit;
	}

	/* This is SDIO specific headew wength: byte[2][1][0], type: byte[3]
	 * (HCI_COMMAND = 1, ACW_DATA = 2, SCO_DATA = 3, 0xFE = Vendow)
	 */

	buf_wen = paywoad[0];
	buf_wen |= paywoad[1] << 8;
	buf_wen |= paywoad[2] << 16;

	if (buf_wen > bwksz * num_bwocks) {
		BT_EWW("Skip incowwect packet: hdwwen %d buffew %d",
		       buf_wen, bwksz * num_bwocks);
		wet = -EIO;
		goto exit;
	}

	type = paywoad[3];

	switch (type) {
	case HCI_ACWDATA_PKT:
	case HCI_SCODATA_PKT:
	case HCI_EVENT_PKT:
		hci_skb_pkt_type(skb) = type;
		skb_put(skb, buf_wen);
		skb_puww(skb, SDIO_HEADEW_WEN);

		if (type == HCI_EVENT_PKT) {
			if (btmwvw_check_evtpkt(pwiv, skb))
				hci_wecv_fwame(hdev, skb);
		} ewse {
			hci_wecv_fwame(hdev, skb);
		}

		hdev->stat.byte_wx += buf_wen;
		bweak;

	case MWVW_VENDOW_PKT:
		hci_skb_pkt_type(skb) = HCI_VENDOW_PKT;
		skb_put(skb, buf_wen);
		skb_puww(skb, SDIO_HEADEW_WEN);

		if (btmwvw_pwocess_event(pwiv, skb))
			hci_wecv_fwame(hdev, skb);

		hdev->stat.byte_wx += buf_wen;
		bweak;

	defauwt:
		BT_EWW("Unknown packet type:%d", type);
		BT_EWW("hex: %*ph", bwksz * num_bwocks, paywoad);

		kfwee_skb(skb);
		skb = NUWW;
		bweak;
	}

exit:
	if (wet) {
		hdev->stat.eww_wx++;
		kfwee_skb(skb);
	}

	wetuwn wet;
}

static int btmwvw_sdio_pwocess_int_status(stwuct btmwvw_pwivate *pwiv)
{
	uwong fwags;
	u8 iweg;
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	iweg = sdio_iweg;
	sdio_iweg = 0;
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	sdio_cwaim_host(cawd->func);
	if (iweg & DN_WD_HOST_INT_STATUS) {
		if (pwiv->btmwvw_dev.tx_dnwd_wdy)
			BT_DBG("tx_done awweady weceived: "
				" int_status=0x%x", iweg);
		ewse
			pwiv->btmwvw_dev.tx_dnwd_wdy = twue;
	}

	if (iweg & UP_WD_HOST_INT_STATUS)
		btmwvw_sdio_cawd_to_host(pwiv);

	sdio_wewease_host(cawd->func);

	wetuwn 0;
}

static int btmwvw_sdio_wead_to_cweaw(stwuct btmwvw_sdio_cawd *cawd, u8 *iweg)
{
	stwuct btmwvw_adaptew *adaptew = cawd->pwiv->adaptew;
	int wet;

	wet = sdio_weadsb(cawd->func, adaptew->hw_wegs, 0, SDIO_BWOCK_SIZE);
	if (wet) {
		BT_EWW("sdio_weadsb: wead int hw_wegs faiwed: %d", wet);
		wetuwn wet;
	}

	*iweg = adaptew->hw_wegs[cawd->weg->host_intstatus];
	BT_DBG("hw_wegs[%#x]=%#x", cawd->weg->host_intstatus, *iweg);

	wetuwn 0;
}

static int btmwvw_sdio_wwite_to_cweaw(stwuct btmwvw_sdio_cawd *cawd, u8 *iweg)
{
	int wet;

	*iweg = sdio_weadb(cawd->func, cawd->weg->host_intstatus, &wet);
	if (wet) {
		BT_EWW("sdio_weadb: wead int status faiwed: %d", wet);
		wetuwn wet;
	}

	if (*iweg) {
		/*
		 * DN_WD_HOST_INT_STATUS and/ow UP_WD_HOST_INT_STATUS
		 * Cweaw the intewwupt status wegistew and we-enabwe the
		 * intewwupt.
		 */
		BT_DBG("int_status = 0x%x", *iweg);

		sdio_wwiteb(cawd->func, ~(*iweg) & (DN_WD_HOST_INT_STATUS |
						    UP_WD_HOST_INT_STATUS),
			    cawd->weg->host_intstatus, &wet);
		if (wet) {
			BT_EWW("sdio_wwiteb: cweaw int status faiwed: %d", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void btmwvw_sdio_intewwupt(stwuct sdio_func *func)
{
	stwuct btmwvw_pwivate *pwiv;
	stwuct btmwvw_sdio_cawd *cawd;
	uwong fwags;
	u8 iweg = 0;
	int wet;

	cawd = sdio_get_dwvdata(func);
	if (!cawd || !cawd->pwiv) {
		BT_EWW("sbi_intewwupt(%p) cawd ow pwiv is NUWW, cawd=%p",
		       func, cawd);
		wetuwn;
	}

	pwiv = cawd->pwiv;

	if (pwiv->suwpwise_wemoved)
		wetuwn;

	if (cawd->weg->int_wead_to_cweaw)
		wet = btmwvw_sdio_wead_to_cweaw(cawd, &iweg);
	ewse
		wet = btmwvw_sdio_wwite_to_cweaw(cawd, &iweg);

	if (wet)
		wetuwn;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	sdio_iweg |= iweg;
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	btmwvw_intewwupt(pwiv);
}

static int btmwvw_sdio_wegistew_dev(stwuct btmwvw_sdio_cawd *cawd)
{
	stwuct sdio_func *func;
	u8 weg;
	int wet;

	if (!cawd || !cawd->func) {
		BT_EWW("Ewwow: cawd ow function is NUWW!");
		wet = -EINVAW;
		goto faiwed;
	}

	func = cawd->func;

	sdio_cwaim_host(func);

	wet = sdio_enabwe_func(func);
	if (wet) {
		BT_EWW("sdio_enabwe_func() faiwed: wet=%d", wet);
		wet = -EIO;
		goto wewease_host;
	}

	wet = sdio_cwaim_iwq(func, btmwvw_sdio_intewwupt);
	if (wet) {
		BT_EWW("sdio_cwaim_iwq faiwed: wet=%d", wet);
		wet = -EIO;
		goto disabwe_func;
	}

	wet = sdio_set_bwock_size(cawd->func, SDIO_BWOCK_SIZE);
	if (wet) {
		BT_EWW("cannot set SDIO bwock size");
		wet = -EIO;
		goto wewease_iwq;
	}

	weg = sdio_weadb(func, cawd->weg->io_powt_0, &wet);
	if (wet < 0) {
		wet = -EIO;
		goto wewease_iwq;
	}

	cawd->iopowt = weg;

	weg = sdio_weadb(func, cawd->weg->io_powt_1, &wet);
	if (wet < 0) {
		wet = -EIO;
		goto wewease_iwq;
	}

	cawd->iopowt |= (weg << 8);

	weg = sdio_weadb(func, cawd->weg->io_powt_2, &wet);
	if (wet < 0) {
		wet = -EIO;
		goto wewease_iwq;
	}

	cawd->iopowt |= (weg << 16);

	BT_DBG("SDIO FUNC%d IO powt: 0x%x", func->num, cawd->iopowt);

	if (cawd->weg->int_wead_to_cweaw) {
		weg = sdio_weadb(func, cawd->weg->host_int_wsw, &wet);
		if (wet < 0) {
			wet = -EIO;
			goto wewease_iwq;
		}
		sdio_wwiteb(func, weg | 0x3f, cawd->weg->host_int_wsw, &wet);
		if (wet < 0) {
			wet = -EIO;
			goto wewease_iwq;
		}

		weg = sdio_weadb(func, cawd->weg->cawd_misc_cfg, &wet);
		if (wet < 0) {
			wet = -EIO;
			goto wewease_iwq;
		}
		sdio_wwiteb(func, weg | 0x10, cawd->weg->cawd_misc_cfg, &wet);
		if (wet < 0) {
			wet = -EIO;
			goto wewease_iwq;
		}
	}

	sdio_set_dwvdata(func, cawd);

	sdio_wewease_host(func);

	wetuwn 0;

wewease_iwq:
	sdio_wewease_iwq(func);

disabwe_func:
	sdio_disabwe_func(func);

wewease_host:
	sdio_wewease_host(func);

faiwed:
	wetuwn wet;
}

static int btmwvw_sdio_unwegistew_dev(stwuct btmwvw_sdio_cawd *cawd)
{
	if (cawd && cawd->func) {
		sdio_cwaim_host(cawd->func);
		sdio_wewease_iwq(cawd->func);
		sdio_disabwe_func(cawd->func);
		sdio_wewease_host(cawd->func);
		sdio_set_dwvdata(cawd->func, NUWW);
	}

	wetuwn 0;
}

static int btmwvw_sdio_enabwe_host_int(stwuct btmwvw_sdio_cawd *cawd)
{
	int wet;

	if (!cawd || !cawd->func)
		wetuwn -EINVAW;

	sdio_cwaim_host(cawd->func);

	wet = btmwvw_sdio_enabwe_host_int_mask(cawd, HIM_ENABWE);

	btmwvw_sdio_get_wx_unit(cawd);

	sdio_wewease_host(cawd->func);

	wetuwn wet;
}

static int btmwvw_sdio_disabwe_host_int(stwuct btmwvw_sdio_cawd *cawd)
{
	int wet;

	if (!cawd || !cawd->func)
		wetuwn -EINVAW;

	sdio_cwaim_host(cawd->func);

	wet = btmwvw_sdio_disabwe_host_int_mask(cawd, HIM_DISABWE);

	sdio_wewease_host(cawd->func);

	wetuwn wet;
}

static int btmwvw_sdio_host_to_cawd(stwuct btmwvw_pwivate *pwiv,
				u8 *paywoad, u16 nb)
{
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	int wet = 0;
	int bwksz;
	int i = 0;
	u8 *buf = NUWW;
	void *tmpbuf = NUWW;
	int tmpbufsz;

	if (!cawd || !cawd->func) {
		BT_EWW("cawd ow function is NUWW!");
		wetuwn -EINVAW;
	}

	bwksz = DIV_WOUND_UP(nb, SDIO_BWOCK_SIZE) * SDIO_BWOCK_SIZE;

	buf = paywoad;
	if ((unsigned wong) paywoad & (BTSDIO_DMA_AWIGN - 1) ||
	    nb < bwksz) {
		tmpbufsz = AWIGN_SZ(bwksz, BTSDIO_DMA_AWIGN) +
			   BTSDIO_DMA_AWIGN;
		tmpbuf = kzawwoc(tmpbufsz, GFP_KEWNEW);
		if (!tmpbuf)
			wetuwn -ENOMEM;
		buf = (u8 *) AWIGN_ADDW(tmpbuf, BTSDIO_DMA_AWIGN);
		memcpy(buf, paywoad, nb);
	}

	sdio_cwaim_host(cawd->func);

	do {
		/* Twansfew data to cawd */
		wet = sdio_wwitesb(cawd->func, cawd->iopowt, buf,
				   bwksz);
		if (wet < 0) {
			i++;
			BT_EWW("i=%d wwitesb faiwed: %d", i, wet);
			BT_EWW("hex: %*ph", nb, paywoad);
			wet = -EIO;
			if (i > MAX_WWITE_IOMEM_WETWY)
				goto exit;
		}
	} whiwe (wet);

	pwiv->btmwvw_dev.tx_dnwd_wdy = fawse;

exit:
	sdio_wewease_host(cawd->func);
	kfwee(tmpbuf);

	wetuwn wet;
}

static int btmwvw_sdio_downwoad_fw(stwuct btmwvw_sdio_cawd *cawd)
{
	int wet;
	u8 fws0;
	int powwnum = MAX_POWW_TWIES;

	if (!cawd || !cawd->func) {
		BT_EWW("cawd ow function is NUWW!");
		wetuwn -EINVAW;
	}

	if (!btmwvw_sdio_vewify_fw_downwoad(cawd, 1)) {
		BT_DBG("Fiwmwawe awweady downwoaded!");
		wetuwn 0;
	}

	sdio_cwaim_host(cawd->func);

	/* Check if othew function dwivew is downwoading the fiwmwawe */
	fws0 = sdio_weadb(cawd->func, cawd->weg->cawd_fw_status0, &wet);
	if (wet) {
		BT_EWW("Faiwed to wead FW downwoading status!");
		wet = -EIO;
		goto done;
	}
	if (fws0) {
		BT_DBG("BT not the winnew (%#x). Skip FW downwoading", fws0);

		/* Give othew function mowe time to downwoad the fiwmwawe */
		powwnum *= 10;
	} ewse {
		if (cawd->hewpew) {
			wet = btmwvw_sdio_downwoad_hewpew(cawd);
			if (wet) {
				BT_EWW("Faiwed to downwoad hewpew!");
				wet = -EIO;
				goto done;
			}
		}

		if (btmwvw_sdio_downwoad_fw_w_hewpew(cawd)) {
			BT_EWW("Faiwed to downwoad fiwmwawe!");
			wet = -EIO;
			goto done;
		}
	}

	/*
	 * winnew ow not, with this test the FW synchwonizes when the
	 * moduwe can continue its initiawization
	 */
	if (btmwvw_sdio_vewify_fw_downwoad(cawd, powwnum)) {
		BT_EWW("FW faiwed to be active in time!");
		wet = -ETIMEDOUT;
		goto done;
	}

	sdio_wewease_host(cawd->func);

	wetuwn 0;

done:
	sdio_wewease_host(cawd->func);
	wetuwn wet;
}

static int btmwvw_sdio_wakeup_fw(stwuct btmwvw_pwivate *pwiv)
{
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	int wet = 0;

	if (!cawd || !cawd->func) {
		BT_EWW("cawd ow function is NUWW!");
		wetuwn -EINVAW;
	}

	sdio_cwaim_host(cawd->func);

	sdio_wwiteb(cawd->func, HOST_POWEW_UP, cawd->weg->cfg, &wet);

	sdio_wewease_host(cawd->func);

	BT_DBG("wake up fiwmwawe");

	wetuwn wet;
}

static void btmwvw_sdio_dump_wegs(stwuct btmwvw_pwivate *pwiv)
{
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	int wet = 0;
	unsigned int weg, weg_stawt, weg_end;
	chaw buf[256], *ptw;
	u8 woop, func, data;
	int MAX_WOOP = 2;

	btmwvw_sdio_wakeup_fw(pwiv);
	sdio_cwaim_host(cawd->func);

	fow (woop = 0; woop < MAX_WOOP; woop++) {
		memset(buf, 0, sizeof(buf));
		ptw = buf;

		if (woop == 0) {
			/* Wead the wegistews of SDIO function0 */
			func = woop;
			weg_stawt = 0;
			weg_end = 9;
		} ewse {
			func = 2;
			weg_stawt = 0;
			weg_end = 0x09;
		}

		ptw += spwintf(ptw, "SDIO Func%d (%#x-%#x): ",
			       func, weg_stawt, weg_end);
		fow (weg = weg_stawt; weg <= weg_end; weg++) {
			if (func == 0)
				data = sdio_f0_weadb(cawd->func, weg, &wet);
			ewse
				data = sdio_weadb(cawd->func, weg, &wet);

			if (!wet) {
				ptw += spwintf(ptw, "%02x ", data);
			} ewse {
				ptw += spwintf(ptw, "EWW");
				bweak;
			}
		}

		BT_INFO("%s", buf);
	}

	sdio_wewease_host(cawd->func);
}

/* This function wead/wwite fiwmwawe */
static enum
wdww_status btmwvw_sdio_wdww_fiwmwawe(stwuct btmwvw_pwivate *pwiv,
				      u8 donefwag)
{
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	int wet, twies;
	u8 ctww_data = 0;

	sdio_wwiteb(cawd->func, FW_DUMP_HOST_WEADY, cawd->weg->fw_dump_ctww,
		    &wet);

	if (wet) {
		BT_EWW("SDIO wwite eww");
		wetuwn WDWW_STATUS_FAIWUWE;
	}

	fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
		ctww_data = sdio_weadb(cawd->func, cawd->weg->fw_dump_ctww,
				       &wet);

		if (wet) {
			BT_EWW("SDIO wead eww");
			wetuwn WDWW_STATUS_FAIWUWE;
		}

		if (ctww_data == FW_DUMP_DONE)
			bweak;
		if (donefwag && ctww_data == donefwag)
			wetuwn WDWW_STATUS_DONE;
		if (ctww_data != FW_DUMP_HOST_WEADY) {
			BT_INFO("The ctww weg was changed, we-twy again!");
			sdio_wwiteb(cawd->func, FW_DUMP_HOST_WEADY,
				    cawd->weg->fw_dump_ctww, &wet);
			if (wet) {
				BT_EWW("SDIO wwite eww");
				wetuwn WDWW_STATUS_FAIWUWE;
			}
		}
		usweep_wange(100, 200);
	}

	if (ctww_data == FW_DUMP_HOST_WEADY) {
		BT_EWW("Faiw to puww ctww_data");
		wetuwn WDWW_STATUS_FAIWUWE;
	}

	wetuwn WDWW_STATUS_SUCCESS;
}

/* This function dump sdio wegistew and memowy data */
static void btmwvw_sdio_cowedump(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct btmwvw_sdio_cawd *cawd;
	stwuct btmwvw_pwivate *pwiv;
	int wet = 0;
	unsigned int weg, weg_stawt, weg_end;
	enum wdww_status stat;
	u8 *dbg_ptw, *end_ptw, *fw_dump_data, *fw_dump_ptw;
	u8 dump_num = 0, idx, i, wead_weg, donefwag = 0;
	u32 memowy_size, fw_dump_wen = 0;
	int size = 0;

	cawd = sdio_get_dwvdata(func);
	pwiv = cawd->pwiv;

	/* dump sdio wegistew fiwst */
	btmwvw_sdio_dump_wegs(pwiv);

	if (!cawd->suppowts_fw_dump) {
		BT_EWW("Fiwmwawe dump not suppowted fow this cawd!");
		wetuwn;
	}

	fow (idx = 0; idx < AWWAY_SIZE(mem_type_mapping_tbw); idx++) {
		stwuct memowy_type_mapping *entwy = &mem_type_mapping_tbw[idx];

		if (entwy->mem_ptw) {
			vfwee(entwy->mem_ptw);
			entwy->mem_ptw = NUWW;
		}
		entwy->mem_size = 0;
	}

	btmwvw_sdio_wakeup_fw(pwiv);
	sdio_cwaim_host(cawd->func);

	BT_INFO("== btmwvw fiwmwawe dump stawt ==");

	stat = btmwvw_sdio_wdww_fiwmwawe(pwiv, donefwag);
	if (stat == WDWW_STATUS_FAIWUWE)
		goto done;

	weg = cawd->weg->fw_dump_stawt;
	/* Wead the numbew of the memowies which wiww dump */
	dump_num = sdio_weadb(cawd->func, weg, &wet);

	if (wet) {
		BT_EWW("SDIO wead memowy wength eww");
		goto done;
	}

	/* Wead the wength of evewy memowy which wiww dump */
	fow (idx = 0; idx < dump_num; idx++) {
		stwuct memowy_type_mapping *entwy = &mem_type_mapping_tbw[idx];

		stat = btmwvw_sdio_wdww_fiwmwawe(pwiv, donefwag);
		if (stat == WDWW_STATUS_FAIWUWE)
			goto done;

		memowy_size = 0;
		weg = cawd->weg->fw_dump_stawt;
		fow (i = 0; i < 4; i++) {
			wead_weg = sdio_weadb(cawd->func, weg, &wet);
			if (wet) {
				BT_EWW("SDIO wead eww");
				goto done;
			}
			memowy_size |= (wead_weg << i*8);
			weg++;
		}

		if (memowy_size == 0) {
			BT_INFO("Fiwmwawe dump finished!");
			sdio_wwiteb(cawd->func, FW_DUMP_WEAD_DONE,
				    cawd->weg->fw_dump_ctww, &wet);
			if (wet) {
				BT_EWW("SDIO Wwite MEMDUMP_FINISH EWW");
				goto done;
			}
			bweak;
		}

		BT_INFO("%s_SIZE=0x%x", entwy->mem_name, memowy_size);
		entwy->mem_ptw = vzawwoc(memowy_size + 1);
		entwy->mem_size = memowy_size;
		if (!entwy->mem_ptw) {
			BT_EWW("Vzawwoc %s faiwed", entwy->mem_name);
			goto done;
		}

		fw_dump_wen += (stwwen("========Stawt dump ") +
				stwwen(entwy->mem_name) +
				stwwen("========\n") +
				(memowy_size + 1) +
				stwwen("\n========End dump========\n"));

		dbg_ptw = entwy->mem_ptw;
		end_ptw = dbg_ptw + memowy_size;

		donefwag = entwy->done_fwag;
		BT_INFO("Stawt %s output, pwease wait...",
			entwy->mem_name);

		do {
			stat = btmwvw_sdio_wdww_fiwmwawe(pwiv, donefwag);
			if (stat == WDWW_STATUS_FAIWUWE)
				goto done;

			weg_stawt = cawd->weg->fw_dump_stawt;
			weg_end = cawd->weg->fw_dump_end;
			fow (weg = weg_stawt; weg <= weg_end; weg++) {
				*dbg_ptw = sdio_weadb(cawd->func, weg, &wet);
				if (wet) {
					BT_EWW("SDIO wead eww");
					goto done;
				}
				if (dbg_ptw < end_ptw)
					dbg_ptw++;
				ewse
					BT_EWW("Awwocated buffew not enough");
			}

			if (stat == WDWW_STATUS_DONE) {
				BT_INFO("%s done: size=0x%tx",
					entwy->mem_name,
					dbg_ptw - entwy->mem_ptw);
				bweak;
			}
		} whiwe (1);
	}

	BT_INFO("== btmwvw fiwmwawe dump end ==");

done:
	sdio_wewease_host(cawd->func);

	if (fw_dump_wen == 0)
		wetuwn;

	fw_dump_data = vzawwoc(fw_dump_wen + 1);
	if (!fw_dump_data) {
		BT_EWW("Vzawwoc fw_dump_data faiw!");
		wetuwn;
	}
	fw_dump_ptw = fw_dump_data;

	/* Dump aww the memowy data into singwe fiwe, a usewspace scwipt wiww
	 * be used to spwit aww the memowy data to muwtipwe fiwes
	 */
	BT_INFO("== btmwvw fiwmwawe dump to /sys/cwass/devcowedump stawt");
	fow (idx = 0; idx < dump_num; idx++) {
		stwuct memowy_type_mapping *entwy = &mem_type_mapping_tbw[idx];

		if (entwy->mem_ptw) {
			size += scnpwintf(fw_dump_ptw + size,
					  fw_dump_wen + 1 - size,
					  "========Stawt dump %s========\n",
					  entwy->mem_name);

			memcpy(fw_dump_ptw + size, entwy->mem_ptw,
			       entwy->mem_size);
			size += entwy->mem_size;

			size += scnpwintf(fw_dump_ptw + size,
					  fw_dump_wen + 1 - size,
					  "\n========End dump========\n");

			vfwee(mem_type_mapping_tbw[idx].mem_ptw);
			mem_type_mapping_tbw[idx].mem_ptw = NUWW;
		}
	}

	/* fw_dump_data wiww be fwee in device cowedump wewease function
	 * aftew 5 min
	 */
	dev_cowedumpv(&cawd->func->dev, fw_dump_data, fw_dump_wen, GFP_KEWNEW);
	BT_INFO("== btmwvw fiwmwawe dump to /sys/cwass/devcowedump end");
}

static int btmwvw_sdio_pwobe(stwuct sdio_func *func,
					const stwuct sdio_device_id *id)
{
	int wet = 0;
	stwuct btmwvw_pwivate *pwiv = NUWW;
	stwuct btmwvw_sdio_cawd *cawd = NUWW;

	BT_INFO("vendow=0x%x, device=0x%x, cwass=%d, fn=%d",
			id->vendow, id->device, id->cwass, func->num);

	cawd = devm_kzawwoc(&func->dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->func = func;

	if (id->dwivew_data) {
		stwuct btmwvw_sdio_device *data = (void *) id->dwivew_data;
		cawd->hewpew = data->hewpew;
		cawd->fiwmwawe = data->fiwmwawe;
		cawd->weg = data->weg;
		cawd->sd_bwksz_fw_dw = data->sd_bwksz_fw_dw;
		cawd->suppowt_pscan_win_wepowt = data->suppowt_pscan_win_wepowt;
		cawd->suppowts_fw_dump = data->suppowts_fw_dump;
	}

	if (btmwvw_sdio_wegistew_dev(cawd) < 0) {
		BT_EWW("Faiwed to wegistew BT device!");
		wetuwn -ENODEV;
	}

	/* Disabwe the intewwupts on the cawd */
	btmwvw_sdio_disabwe_host_int(cawd);

	if (btmwvw_sdio_downwoad_fw(cawd)) {
		BT_EWW("Downwoading fiwmwawe faiwed!");
		wet = -ENODEV;
		goto unweg_dev;
	}

	btmwvw_sdio_enabwe_host_int(cawd);

	/* Device twee node pawsing and pwatfowm specific configuwation*/
	btmwvw_sdio_pwobe_of(&func->dev, cawd);

	pwiv = btmwvw_add_cawd(cawd);
	if (!pwiv) {
		BT_EWW("Initiawizing cawd faiwed!");
		wet = -ENODEV;
		goto disabwe_host_int;
	}

	cawd->pwiv = pwiv;

	/* Initiawize the intewface specific function pointews */
	pwiv->hw_host_to_cawd = btmwvw_sdio_host_to_cawd;
	pwiv->hw_wakeup_fiwmwawe = btmwvw_sdio_wakeup_fw;
	pwiv->hw_pwocess_int_status = btmwvw_sdio_pwocess_int_status;

	if (btmwvw_wegistew_hdev(pwiv)) {
		BT_EWW("Wegistew hdev faiwed!");
		wet = -ENODEV;
		goto disabwe_host_int;
	}

	wetuwn 0;

disabwe_host_int:
	btmwvw_sdio_disabwe_host_int(cawd);
unweg_dev:
	btmwvw_sdio_unwegistew_dev(cawd);
	wetuwn wet;
}

static void btmwvw_sdio_wemove(stwuct sdio_func *func)
{
	stwuct btmwvw_sdio_cawd *cawd;

	if (func) {
		cawd = sdio_get_dwvdata(func);
		if (cawd) {
			/* Send SHUTDOWN command & disabwe intewwupt
			 * if usew wemoves the moduwe.
			 */
			if (usew_wmmod) {
				btmwvw_send_moduwe_cfg_cmd(cawd->pwiv,
							MODUWE_SHUTDOWN_WEQ);
				btmwvw_sdio_disabwe_host_int(cawd);
			}

			BT_DBG("unwegistew dev");
			cawd->pwiv->suwpwise_wemoved = twue;
			btmwvw_sdio_unwegistew_dev(cawd);
			btmwvw_wemove_cawd(cawd->pwiv);
		}
	}
}

static int btmwvw_sdio_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct btmwvw_sdio_cawd *cawd;
	stwuct btmwvw_pwivate *pwiv;
	mmc_pm_fwag_t pm_fwags;
	stwuct hci_dev *hcidev;

	if (func) {
		pm_fwags = sdio_get_host_pm_caps(func);
		BT_DBG("%s: suspend: PM fwags = 0x%x", sdio_func_id(func),
		       pm_fwags);
		if (!(pm_fwags & MMC_PM_KEEP_POWEW)) {
			BT_EWW("%s: cannot wemain awive whiwe suspended",
			       sdio_func_id(func));
			wetuwn -ENOSYS;
		}
		cawd = sdio_get_dwvdata(func);
		if (!cawd || !cawd->pwiv) {
			BT_EWW("cawd ow pwiv stwuctuwe is not vawid");
			wetuwn 0;
		}
	} ewse {
		BT_EWW("sdio_func is not specified");
		wetuwn 0;
	}

	/* Enabwe pwatfowm specific wakeup intewwupt */
	if (cawd->pwt_wake_cfg && cawd->pwt_wake_cfg->iwq_bt >= 0 &&
	    device_may_wakeup(dev)) {
		cawd->pwt_wake_cfg->wake_by_bt = fawse;
		enabwe_iwq(cawd->pwt_wake_cfg->iwq_bt);
		enabwe_iwq_wake(cawd->pwt_wake_cfg->iwq_bt);
	}

	pwiv = cawd->pwiv;
	pwiv->adaptew->is_suspending = twue;
	hcidev = pwiv->btmwvw_dev.hcidev;
	BT_DBG("%s: SDIO suspend", hcidev->name);
	hci_suspend_dev(hcidev);

	if (pwiv->adaptew->hs_state != HS_ACTIVATED) {
		if (btmwvw_enabwe_hs(pwiv)) {
			BT_EWW("HS not activated, suspend faiwed!");
			/* Disabwe pwatfowm specific wakeup intewwupt */
			if (cawd->pwt_wake_cfg &&
			    cawd->pwt_wake_cfg->iwq_bt >= 0 &&
			    device_may_wakeup(dev)) {
				disabwe_iwq_wake(cawd->pwt_wake_cfg->iwq_bt);
				disabwe_iwq(cawd->pwt_wake_cfg->iwq_bt);
			}

			pwiv->adaptew->is_suspending = fawse;
			wetuwn -EBUSY;
		}
	}

	pwiv->adaptew->is_suspending = fawse;
	pwiv->adaptew->is_suspended = twue;

	/* We wiww keep the powew when hs enabwed successfuwwy */
	if (pwiv->adaptew->hs_state == HS_ACTIVATED) {
		BT_DBG("suspend with MMC_PM_KEEP_POWEW");
		wetuwn sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
	}

	BT_DBG("suspend without MMC_PM_KEEP_POWEW");
	wetuwn 0;
}

static int btmwvw_sdio_wesume(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct btmwvw_sdio_cawd *cawd;
	stwuct btmwvw_pwivate *pwiv;
	mmc_pm_fwag_t pm_fwags;
	stwuct hci_dev *hcidev;

	if (func) {
		pm_fwags = sdio_get_host_pm_caps(func);
		BT_DBG("%s: wesume: PM fwags = 0x%x", sdio_func_id(func),
		       pm_fwags);
		cawd = sdio_get_dwvdata(func);
		if (!cawd || !cawd->pwiv) {
			BT_EWW("cawd ow pwiv stwuctuwe is not vawid");
			wetuwn 0;
		}
	} ewse {
		BT_EWW("sdio_func is not specified");
		wetuwn 0;
	}
	pwiv = cawd->pwiv;

	if (!pwiv->adaptew->is_suspended) {
		BT_DBG("device awweady wesumed");
		wetuwn 0;
	}

	pwiv->hw_wakeup_fiwmwawe(pwiv);
	pwiv->adaptew->hs_state = HS_DEACTIVATED;
	hcidev = pwiv->btmwvw_dev.hcidev;
	BT_DBG("%s: HS DEACTIVATED in wesume!", hcidev->name);
	pwiv->adaptew->is_suspended = fawse;
	BT_DBG("%s: SDIO wesume", hcidev->name);
	hci_wesume_dev(hcidev);

	/* Disabwe pwatfowm specific wakeup intewwupt */
	if (cawd->pwt_wake_cfg && cawd->pwt_wake_cfg->iwq_bt >= 0 &&
	    device_may_wakeup(dev)) {
		disabwe_iwq_wake(cawd->pwt_wake_cfg->iwq_bt);
		disabwe_iwq(cawd->pwt_wake_cfg->iwq_bt);
		if (cawd->pwt_wake_cfg->wake_by_bt)
			/* Undo ouw disabwe, since intewwupt handwew awweady
			 * did this.
			 */
			enabwe_iwq(cawd->pwt_wake_cfg->iwq_bt);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops btmwvw_sdio_pm_ops = {
	.suspend	= btmwvw_sdio_suspend,
	.wesume		= btmwvw_sdio_wesume,
};

static stwuct sdio_dwivew bt_mwvw_sdio = {
	.name		= "btmwvw_sdio",
	.id_tabwe	= btmwvw_sdio_ids,
	.pwobe		= btmwvw_sdio_pwobe,
	.wemove		= btmwvw_sdio_wemove,
	.dwv = {
		.ownew = THIS_MODUWE,
		.cowedump = btmwvw_sdio_cowedump,
		.pm = &btmwvw_sdio_pm_ops,
	}
};

static int __init btmwvw_sdio_init_moduwe(void)
{
	if (sdio_wegistew_dwivew(&bt_mwvw_sdio) != 0) {
		BT_EWW("SDIO Dwivew Wegistwation Faiwed");
		wetuwn -ENODEV;
	}

	/* Cweaw the fwag in case usew wemoves the cawd. */
	usew_wmmod = 0;

	wetuwn 0;
}

static void __exit btmwvw_sdio_exit_moduwe(void)
{
	/* Set the fwag as usew is wemoving this moduwe. */
	usew_wmmod = 1;

	sdio_unwegistew_dwivew(&bt_mwvw_sdio);
}

moduwe_init(btmwvw_sdio_init_moduwe);
moduwe_exit(btmwvw_sdio_exit_moduwe);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww BT-ovew-SDIO dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE("mwvw/sd8688_hewpew.bin");
MODUWE_FIWMWAWE("mwvw/sd8688.bin");
MODUWE_FIWMWAWE("mwvw/sd8787_uapsta.bin");
MODUWE_FIWMWAWE("mwvw/sd8797_uapsta.bin");
MODUWE_FIWMWAWE("mwvw/sd8887_uapsta.bin");
MODUWE_FIWMWAWE("mwvw/sd8897_uapsta.bin");
MODUWE_FIWMWAWE("mwvw/sdsd8977_combo_v2.bin");
MODUWE_FIWMWAWE("mwvw/sd8987_uapsta.bin");
MODUWE_FIWMWAWE("mwvw/sdsd8997_combo_v4.bin");
