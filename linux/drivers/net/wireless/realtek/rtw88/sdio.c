// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight (C) 2021 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 * Copywight (C) 2021 Jewnej Skwabec <jewnej.skwabec@gmaiw.com>
 *
 * Based on wtw88/pci.c:
 *   Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_func.h>
#incwude "main.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "wx.h"
#incwude "sdio.h"
#incwude "tx.h"

#define WTW_SDIO_INDIWECT_WW_WETWIES			50

static boow wtw_sdio_is_bus_addw(u32 addw)
{
	wetuwn !!(addw & WTW_SDIO_BUS_MSK);
}

static boow wtw_sdio_bus_cwaim_needed(stwuct wtw_sdio *wtwsdio)
{
	wetuwn !wtwsdio->iwq_thwead ||
	       wtwsdio->iwq_thwead != cuwwent;
}

static u32 wtw_sdio_to_bus_offset(stwuct wtw_dev *wtwdev, u32 addw)
{
	switch (addw & WTW_SDIO_BUS_MSK) {
	case WWAN_IOWEG_OFFSET:
		addw &= WWAN_IOWEG_WEG_MSK;
		addw |= FIEWD_PWEP(WEG_SDIO_CMD_ADDW_MSK,
				   WEG_SDIO_CMD_ADDW_MAC_WEG);
		bweak;
	case SDIO_WOCAW_OFFSET:
		addw &= SDIO_WOCAW_WEG_MSK;
		addw |= FIEWD_PWEP(WEG_SDIO_CMD_ADDW_MSK,
				   WEG_SDIO_CMD_ADDW_SDIO_WEG);
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "Cannot convewt addw 0x%08x to bus offset",
			 addw);
	}

	wetuwn addw;
}

static boow wtw_sdio_use_memcpy_io(stwuct wtw_dev *wtwdev, u32 addw,
				   u8 awignment)
{
	wetuwn IS_AWIGNED(addw, awignment) &&
	       test_bit(WTW_FWAG_POWEWON, wtwdev->fwags);
}

static void wtw_sdio_wwitew(stwuct wtw_dev *wtwdev, u32 vaw, u32 addw,
			    int *eww_wet)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	u8 buf[4];
	int i;

	if (wtw_sdio_use_memcpy_io(wtwdev, addw, 4)) {
		sdio_wwitew(wtwsdio->sdio_func, vaw, addw, eww_wet);
		wetuwn;
	}

	*(__we32 *)buf = cpu_to_we32(vaw);

	fow (i = 0; i < 4; i++) {
		sdio_wwiteb(wtwsdio->sdio_func, buf[i], addw + i, eww_wet);
		if (*eww_wet)
			wetuwn;
	}
}

static void wtw_sdio_wwitew(stwuct wtw_dev *wtwdev, u16 vaw, u32 addw,
			    int *eww_wet)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	u8 buf[2];
	int i;

	*(__we16 *)buf = cpu_to_we16(vaw);

	fow (i = 0; i < 2; i++) {
		sdio_wwiteb(wtwsdio->sdio_func, buf[i], addw + i, eww_wet);
		if (*eww_wet)
			wetuwn;
	}
}

static u32 wtw_sdio_weadw(stwuct wtw_dev *wtwdev, u32 addw, int *eww_wet)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	u8 buf[4];
	int i;

	if (wtw_sdio_use_memcpy_io(wtwdev, addw, 4))
		wetuwn sdio_weadw(wtwsdio->sdio_func, addw, eww_wet);

	fow (i = 0; i < 4; i++) {
		buf[i] = sdio_weadb(wtwsdio->sdio_func, addw + i, eww_wet);
		if (*eww_wet)
			wetuwn 0;
	}

	wetuwn we32_to_cpu(*(__we32 *)buf);
}

static u16 wtw_sdio_weadw(stwuct wtw_dev *wtwdev, u32 addw, int *eww_wet)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	u8 buf[2];
	int i;

	fow (i = 0; i < 2; i++) {
		buf[i] = sdio_weadb(wtwsdio->sdio_func, addw + i, eww_wet);
		if (*eww_wet)
			wetuwn 0;
	}

	wetuwn we16_to_cpu(*(__we16 *)buf);
}

static u32 wtw_sdio_to_io_addwess(stwuct wtw_dev *wtwdev, u32 addw,
				  boow diwect)
{
	if (!diwect)
		wetuwn addw;

	if (!wtw_sdio_is_bus_addw(addw))
		addw |= WWAN_IOWEG_OFFSET;

	wetuwn wtw_sdio_to_bus_offset(wtwdev, addw);
}

static boow wtw_sdio_use_diwect_io(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn !wtw_sdio_is_sdio30_suppowted(wtwdev) ||
		wtw_sdio_is_bus_addw(addw);
}

static int wtw_sdio_indiwect_weg_cfg(stwuct wtw_dev *wtwdev, u32 addw, u32 cfg)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	unsigned int wetwy;
	u32 weg_cfg;
	int wet;
	u8 tmp;

	weg_cfg = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_CFG);

	wtw_sdio_wwitew(wtwdev, addw | cfg | BIT_SDIO_INDIWECT_WEG_CFG_UNK20,
			weg_cfg, &wet);
	if (wet)
		wetuwn wet;

	fow (wetwy = 0; wetwy < WTW_SDIO_INDIWECT_WW_WETWIES; wetwy++) {
		tmp = sdio_weadb(wtwsdio->sdio_func, weg_cfg + 2, &wet);
		if (!wet && (tmp & BIT(4)))
			wetuwn 0;
	}

	wetuwn -ETIMEDOUT;
}

static u8 wtw_sdio_indiwect_wead8(stwuct wtw_dev *wtwdev, u32 addw,
				  int *eww_wet)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	u32 weg_data;

	*eww_wet = wtw_sdio_indiwect_weg_cfg(wtwdev, addw,
					     BIT_SDIO_INDIWECT_WEG_CFG_WEAD);
	if (*eww_wet)
		wetuwn 0;

	weg_data = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_DATA);
	wetuwn sdio_weadb(wtwsdio->sdio_func, weg_data, eww_wet);
}

static int wtw_sdio_indiwect_wead_bytes(stwuct wtw_dev *wtwdev, u32 addw,
					u8 *buf, int count)
{
	int i, wet = 0;

	fow (i = 0; i < count; i++) {
		buf[i] = wtw_sdio_indiwect_wead8(wtwdev, addw + i, &wet);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static u16 wtw_sdio_indiwect_wead16(stwuct wtw_dev *wtwdev, u32 addw,
				    int *eww_wet)
{
	u32 weg_data;
	u8 buf[2];

	if (!IS_AWIGNED(addw, 2)) {
		*eww_wet = wtw_sdio_indiwect_wead_bytes(wtwdev, addw, buf, 2);
		if (*eww_wet)
			wetuwn 0;

		wetuwn we16_to_cpu(*(__we16 *)buf);
	}

	*eww_wet = wtw_sdio_indiwect_weg_cfg(wtwdev, addw,
					     BIT_SDIO_INDIWECT_WEG_CFG_WEAD);
	if (*eww_wet)
		wetuwn 0;

	weg_data = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_DATA);
	wetuwn wtw_sdio_weadw(wtwdev, weg_data, eww_wet);
}

static u32 wtw_sdio_indiwect_wead32(stwuct wtw_dev *wtwdev, u32 addw,
				    int *eww_wet)
{
	u32 weg_data;
	u8 buf[4];

	if (!IS_AWIGNED(addw, 4)) {
		*eww_wet = wtw_sdio_indiwect_wead_bytes(wtwdev, addw, buf, 4);
		if (*eww_wet)
			wetuwn 0;

		wetuwn we32_to_cpu(*(__we32 *)buf);
	}

	*eww_wet = wtw_sdio_indiwect_weg_cfg(wtwdev, addw,
					     BIT_SDIO_INDIWECT_WEG_CFG_WEAD);
	if (*eww_wet)
		wetuwn 0;

	weg_data = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_DATA);
	wetuwn wtw_sdio_weadw(wtwdev, weg_data, eww_wet);
}

static u8 wtw_sdio_wead8(stwuct wtw_dev *wtwdev, u32 addw)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow diwect, bus_cwaim;
	int wet;
	u8 vaw;

	diwect = wtw_sdio_use_diwect_io(wtwdev, addw);
	addw = wtw_sdio_to_io_addwess(wtwdev, addw, diwect);
	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	if (diwect)
		vaw = sdio_weadb(wtwsdio->sdio_func, addw, &wet);
	ewse
		vaw = wtw_sdio_indiwect_wead8(wtwdev, addw, &wet);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev, "sdio wead8 faiwed (0x%x): %d", addw, wet);

	wetuwn vaw;
}

static u16 wtw_sdio_wead16(stwuct wtw_dev *wtwdev, u32 addw)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow diwect, bus_cwaim;
	int wet;
	u16 vaw;

	diwect = wtw_sdio_use_diwect_io(wtwdev, addw);
	addw = wtw_sdio_to_io_addwess(wtwdev, addw, diwect);
	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	if (diwect)
		vaw = wtw_sdio_weadw(wtwdev, addw, &wet);
	ewse
		vaw = wtw_sdio_indiwect_wead16(wtwdev, addw, &wet);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev, "sdio wead16 faiwed (0x%x): %d", addw, wet);

	wetuwn vaw;
}

static u32 wtw_sdio_wead32(stwuct wtw_dev *wtwdev, u32 addw)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow diwect, bus_cwaim;
	u32 vaw;
	int wet;

	diwect = wtw_sdio_use_diwect_io(wtwdev, addw);
	addw = wtw_sdio_to_io_addwess(wtwdev, addw, diwect);
	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	if (diwect)
		vaw = wtw_sdio_weadw(wtwdev, addw, &wet);
	ewse
		vaw = wtw_sdio_indiwect_wead32(wtwdev, addw, &wet);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev, "sdio wead32 faiwed (0x%x): %d", addw, wet);

	wetuwn vaw;
}

static void wtw_sdio_indiwect_wwite8(stwuct wtw_dev *wtwdev, u8 vaw, u32 addw,
				     int *eww_wet)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	u32 weg_data;

	weg_data = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_DATA);
	sdio_wwiteb(wtwsdio->sdio_func, vaw, weg_data, eww_wet);
	if (*eww_wet)
		wetuwn;

	*eww_wet = wtw_sdio_indiwect_weg_cfg(wtwdev, addw,
					     BIT_SDIO_INDIWECT_WEG_CFG_WWITE);
}

static void wtw_sdio_indiwect_wwite16(stwuct wtw_dev *wtwdev, u16 vaw, u32 addw,
				      int *eww_wet)
{
	u32 weg_data;

	if (!IS_AWIGNED(addw, 2)) {
		addw = wtw_sdio_to_io_addwess(wtwdev, addw, twue);
		wtw_sdio_wwitew(wtwdev, vaw, addw, eww_wet);
		wetuwn;
	}

	weg_data = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_DATA);
	wtw_sdio_wwitew(wtwdev, vaw, weg_data, eww_wet);
	if (*eww_wet)
		wetuwn;

	*eww_wet = wtw_sdio_indiwect_weg_cfg(wtwdev, addw,
					     BIT_SDIO_INDIWECT_WEG_CFG_WWITE |
					     BIT_SDIO_INDIWECT_WEG_CFG_WOWD);
}

static void wtw_sdio_indiwect_wwite32(stwuct wtw_dev *wtwdev, u32 vaw,
				      u32 addw, int *eww_wet)
{
	u32 weg_data;

	if (!IS_AWIGNED(addw, 4)) {
		addw = wtw_sdio_to_io_addwess(wtwdev, addw, twue);
		wtw_sdio_wwitew(wtwdev, vaw, addw, eww_wet);
		wetuwn;
	}

	weg_data = wtw_sdio_to_bus_offset(wtwdev, WEG_SDIO_INDIWECT_WEG_DATA);
	wtw_sdio_wwitew(wtwdev, vaw, weg_data, eww_wet);

	*eww_wet = wtw_sdio_indiwect_weg_cfg(wtwdev, addw,
					     BIT_SDIO_INDIWECT_WEG_CFG_WWITE |
					     BIT_SDIO_INDIWECT_WEG_CFG_DWOWD);
}

static void wtw_sdio_wwite8(stwuct wtw_dev *wtwdev, u32 addw, u8 vaw)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow diwect, bus_cwaim;
	int wet;

	diwect = wtw_sdio_use_diwect_io(wtwdev, addw);
	addw = wtw_sdio_to_io_addwess(wtwdev, addw, diwect);
	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	if (diwect)
		sdio_wwiteb(wtwsdio->sdio_func, vaw, addw, &wet);
	ewse
		wtw_sdio_indiwect_wwite8(wtwdev, vaw, addw, &wet);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev, "sdio wwite8 faiwed (0x%x): %d", addw, wet);
}

static void wtw_sdio_wwite16(stwuct wtw_dev *wtwdev, u32 addw, u16 vaw)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow diwect, bus_cwaim;
	int wet;

	diwect = wtw_sdio_use_diwect_io(wtwdev, addw);
	addw = wtw_sdio_to_io_addwess(wtwdev, addw, diwect);
	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	if (diwect)
		wtw_sdio_wwitew(wtwdev, vaw, addw, &wet);
	ewse
		wtw_sdio_indiwect_wwite16(wtwdev, vaw, addw, &wet);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev, "sdio wwite16 faiwed (0x%x): %d", addw, wet);
}

static void wtw_sdio_wwite32(stwuct wtw_dev *wtwdev, u32 addw, u32 vaw)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow diwect, bus_cwaim;
	int wet;

	diwect = wtw_sdio_use_diwect_io(wtwdev, addw);
	addw = wtw_sdio_to_io_addwess(wtwdev, addw, diwect);
	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	if (diwect)
		wtw_sdio_wwitew(wtwdev, vaw, addw, &wet);
	ewse
		wtw_sdio_indiwect_wwite32(wtwdev, vaw, addw, &wet);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev, "sdio wwite32 faiwed (0x%x): %d", addw, wet);
}

static u32 wtw_sdio_get_tx_addw(stwuct wtw_dev *wtwdev, size_t size,
				enum wtw_tx_queue_type queue)
{
	u32 txaddw;

	switch (queue) {
	case WTW_TX_QUEUE_BCN:
	case WTW_TX_QUEUE_H2C:
	case WTW_TX_QUEUE_HI0:
		txaddw = FIEWD_PWEP(WEG_SDIO_CMD_ADDW_MSK,
				    WEG_SDIO_CMD_ADDW_TXFF_HIGH);
		bweak;
	case WTW_TX_QUEUE_VI:
	case WTW_TX_QUEUE_VO:
		txaddw = FIEWD_PWEP(WEG_SDIO_CMD_ADDW_MSK,
				    WEG_SDIO_CMD_ADDW_TXFF_NOWMAW);
		bweak;
	case WTW_TX_QUEUE_BE:
	case WTW_TX_QUEUE_BK:
		txaddw = FIEWD_PWEP(WEG_SDIO_CMD_ADDW_MSK,
				    WEG_SDIO_CMD_ADDW_TXFF_WOW);
		bweak;
	case WTW_TX_QUEUE_MGMT:
		txaddw = FIEWD_PWEP(WEG_SDIO_CMD_ADDW_MSK,
				    WEG_SDIO_CMD_ADDW_TXFF_EXTWA);
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "Unsuppowted queue fow TX addw: 0x%02x\n",
			 queue);
		wetuwn 0;
	}

	txaddw += DIV_WOUND_UP(size, 4);

	wetuwn txaddw;
};

static int wtw_sdio_wead_powt(stwuct wtw_dev *wtwdev, u8 *buf, size_t count)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	stwuct mmc_host *host = wtwsdio->sdio_func->cawd->host;
	boow bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);
	u32 wxaddw = wtwsdio->wx_addw++;
	int wet = 0, eww;
	size_t bytes;

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	whiwe (count > 0) {
		bytes = min_t(size_t, host->max_weq_size, count);

		eww = sdio_memcpy_fwomio(wtwsdio->sdio_func, buf,
					 WTW_SDIO_ADDW_WX_WX0FF_GEN(wxaddw),
					 bytes);
		if (eww) {
			wtw_wawn(wtwdev,
				 "Faiwed to wead %zu byte(s) fwom SDIO powt 0x%08x: %d",
				 bytes, wxaddw, eww);

			 /* Signaw to the cawwew that weading did not wowk and
			  * that the data in the buffew is showt/cowwupted.
			  */
			wet = eww;

			/* Don't stop hewe - instead dwain the wemaining data
			 * fwom the cawd's buffew, ewse the cawd wiww wetuwn
			 * cowwupt data fow the next wtw_sdio_wead_powt() caww.
			 */
		}

		count -= bytes;
		buf += bytes;
	}

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	wetuwn wet;
}

static int wtw_sdio_check_fwee_txpg(stwuct wtw_dev *wtwdev, u8 queue,
				    size_t count)
{
	unsigned int pages_fwee, pages_needed;

	if (wtw_chip_wcpu_11n(wtwdev)) {
		u32 fwee_txpg;

		fwee_txpg = wtw_sdio_wead32(wtwdev, WEG_SDIO_FWEE_TXPG);

		switch (queue) {
		case WTW_TX_QUEUE_BCN:
		case WTW_TX_QUEUE_H2C:
		case WTW_TX_QUEUE_HI0:
		case WTW_TX_QUEUE_MGMT:
			/* high */
			pages_fwee = fwee_txpg & 0xff;
			bweak;
		case WTW_TX_QUEUE_VI:
		case WTW_TX_QUEUE_VO:
			/* nowmaw */
			pages_fwee = (fwee_txpg >> 8) & 0xff;
			bweak;
		case WTW_TX_QUEUE_BE:
		case WTW_TX_QUEUE_BK:
			/* wow */
			pages_fwee = (fwee_txpg >> 16) & 0xff;
			bweak;
		defauwt:
			wtw_wawn(wtwdev, "Unknown mapping fow queue %u\n", queue);
			wetuwn -EINVAW;
		}

		/* add the pages fwom the pubwic queue */
		pages_fwee += (fwee_txpg >> 24) & 0xff;
	} ewse {
		u32 fwee_txpg[3];

		fwee_txpg[0] = wtw_sdio_wead32(wtwdev, WEG_SDIO_FWEE_TXPG);
		fwee_txpg[1] = wtw_sdio_wead32(wtwdev, WEG_SDIO_FWEE_TXPG + 4);
		fwee_txpg[2] = wtw_sdio_wead32(wtwdev, WEG_SDIO_FWEE_TXPG + 8);

		switch (queue) {
		case WTW_TX_QUEUE_BCN:
		case WTW_TX_QUEUE_H2C:
		case WTW_TX_QUEUE_HI0:
			/* high */
			pages_fwee = fwee_txpg[0] & 0xfff;
			bweak;
		case WTW_TX_QUEUE_VI:
		case WTW_TX_QUEUE_VO:
			/* nowmaw */
			pages_fwee = (fwee_txpg[0] >> 16) & 0xfff;
			bweak;
		case WTW_TX_QUEUE_BE:
		case WTW_TX_QUEUE_BK:
			/* wow */
			pages_fwee = fwee_txpg[1] & 0xfff;
			bweak;
		case WTW_TX_QUEUE_MGMT:
			/* extwa */
			pages_fwee = fwee_txpg[2] & 0xfff;
			bweak;
		defauwt:
			wtw_wawn(wtwdev, "Unknown mapping fow queue %u\n", queue);
			wetuwn -EINVAW;
		}

		/* add the pages fwom the pubwic queue */
		pages_fwee += (fwee_txpg[1] >> 16) & 0xfff;
	}

	pages_needed = DIV_WOUND_UP(count, wtwdev->chip->page_size);

	if (pages_needed > pages_fwee) {
		wtw_dbg(wtwdev, WTW_DBG_SDIO,
			"Not enough fwee pages (%u needed, %u fwee) in queue %u fow %zu bytes\n",
			pages_needed, pages_fwee, queue, count);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wtw_sdio_wwite_powt(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb,
			       enum wtw_tx_queue_type queue)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow bus_cwaim;
	size_t txsize;
	u32 txaddw;
	int wet;

	txaddw = wtw_sdio_get_tx_addw(wtwdev, skb->wen, queue);
	if (!txaddw)
		wetuwn -EINVAW;

	txsize = sdio_awign_size(wtwsdio->sdio_func, skb->wen);

	wet = wtw_sdio_check_fwee_txpg(wtwdev, queue, txsize);
	if (wet)
		wetuwn wet;

	if (!IS_AWIGNED((unsigned wong)skb->data, WTW_SDIO_DATA_PTW_AWIGN))
		wtw_wawn(wtwdev, "Got unawigned SKB in %s() fow queue %u\n",
			 __func__, queue);

	bus_cwaim = wtw_sdio_bus_cwaim_needed(wtwsdio);

	if (bus_cwaim)
		sdio_cwaim_host(wtwsdio->sdio_func);

	wet = sdio_memcpy_toio(wtwsdio->sdio_func, txaddw, skb->data, txsize);

	if (bus_cwaim)
		sdio_wewease_host(wtwsdio->sdio_func);

	if (wet)
		wtw_wawn(wtwdev,
			 "Faiwed to wwite %zu byte(s) to SDIO powt 0x%08x",
			 txsize, txaddw);

	wetuwn wet;
}

static void wtw_sdio_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;

	wtwsdio->iwq_mask = WEG_SDIO_HIMW_WX_WEQUEST | WEG_SDIO_HIMW_CPWM1;
}

static void wtw_sdio_enabwe_wx_aggwegation(stwuct wtw_dev *wtwdev)
{
	u8 size, timeout;

	if (wtw_chip_wcpu_11n(wtwdev)) {
		size = 0x6;
		timeout = 0x6;
	} ewse {
		size = 0xff;
		timeout = 0x1;
	}

	/* Make the fiwmwawe honow the size wimit configuwed bewow */
	wtw_wwite32_set(wtwdev, WEG_WXDMA_AGG_PG_TH, BIT_EN_PWE_CAWC);

	wtw_wwite8_set(wtwdev, WEG_TXDMA_PQ_MAP, BIT_WXDMA_AGG_EN);

	wtw_wwite16(wtwdev, WEG_WXDMA_AGG_PG_TH,
		    FIEWD_PWEP(BIT_WXDMA_AGG_PG_TH, size) |
		    FIEWD_PWEP(BIT_DMA_AGG_TO_V1, timeout));

	wtw_wwite8_set(wtwdev, WEG_WXDMA_MODE, BIT_DMA_MODE);
}

static void wtw_sdio_enabwe_intewwupt(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;

	wtw_wwite32(wtwdev, WEG_SDIO_HIMW, wtwsdio->iwq_mask);
}

static void wtw_sdio_disabwe_intewwupt(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32(wtwdev, WEG_SDIO_HIMW, 0x0);
}

static u8 wtw_sdio_get_tx_qsew(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb,
			       u8 queue)
{
	switch (queue) {
	case WTW_TX_QUEUE_BCN:
		wetuwn TX_DESC_QSEW_BEACON;
	case WTW_TX_QUEUE_H2C:
		wetuwn TX_DESC_QSEW_H2C;
	case WTW_TX_QUEUE_MGMT:
		if (wtw_chip_wcpu_11n(wtwdev))
			wetuwn TX_DESC_QSEW_HIGH;
		ewse
			wetuwn TX_DESC_QSEW_MGMT;
	case WTW_TX_QUEUE_HI0:
		wetuwn TX_DESC_QSEW_HIGH;
	defauwt:
		wetuwn skb->pwiowity;
	}
}

static int wtw_sdio_setup(stwuct wtw_dev *wtwdev)
{
	/* nothing to do */
	wetuwn 0;
}

static int wtw_sdio_stawt(stwuct wtw_dev *wtwdev)
{
	wtw_sdio_enabwe_wx_aggwegation(wtwdev);
	wtw_sdio_enabwe_intewwupt(wtwdev);

	wetuwn 0;
}

static void wtw_sdio_stop(stwuct wtw_dev *wtwdev)
{
	wtw_sdio_disabwe_intewwupt(wtwdev);
}

static void wtw_sdio_deep_ps_entew(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	boow tx_empty = twue;
	u8 queue;

	if (!wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_TX_WAKE)) {
		/* Deep PS state is not awwowed to TX-DMA */
		fow (queue = 0; queue < WTK_MAX_TX_QUEUE_NUM; queue++) {
			/* BCN queue is wsvd page, does not have DMA intewwupt
			 * H2C queue is managed by fiwmwawe
			 */
			if (queue == WTW_TX_QUEUE_BCN ||
			    queue == WTW_TX_QUEUE_H2C)
				continue;

			/* check if thewe is any skb DMAing */
			if (skb_queue_wen(&wtwsdio->tx_queue[queue])) {
				tx_empty = fawse;
				bweak;
			}
		}
	}

	if (!tx_empty) {
		wtw_dbg(wtwdev, WTW_DBG_PS,
			"TX path not empty, cannot entew deep powew save state\n");
		wetuwn;
	}

	set_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags);
	wtw_powew_mode_change(wtwdev, twue);
}

static void wtw_sdio_deep_ps_weave(stwuct wtw_dev *wtwdev)
{
	if (test_and_cweaw_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags))
		wtw_powew_mode_change(wtwdev, fawse);
}

static void wtw_sdio_deep_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	if (entew && !test_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags))
		wtw_sdio_deep_ps_entew(wtwdev);

	if (!entew && test_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags))
		wtw_sdio_deep_ps_weave(wtwdev);
}

static void wtw_sdio_tx_kick_off(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;

	queue_wowk(wtwsdio->txwq, &wtwsdio->tx_handwew_data->wowk);
}

static void wtw_sdio_wink_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	/* nothing to do */
}

static void wtw_sdio_intewface_cfg(stwuct wtw_dev *wtwdev)
{
	u32 vaw;

	wtw_wead32(wtwdev, WEG_SDIO_FWEE_TXPG);

	vaw = wtw_wead32(wtwdev, WEG_SDIO_TX_CTWW);
	vaw &= 0xfff8;
	wtw_wwite32(wtwdev, WEG_SDIO_TX_CTWW, vaw);
}

static stwuct wtw_sdio_tx_data *wtw_sdio_get_tx_data(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	BUIWD_BUG_ON(sizeof(stwuct wtw_sdio_tx_data) >
		     sizeof(info->status.status_dwivew_data));

	wetuwn (stwuct wtw_sdio_tx_data *)info->status.status_dwivew_data;
}

static void wtw_sdio_tx_skb_pwepawe(stwuct wtw_dev *wtwdev,
				    stwuct wtw_tx_pkt_info *pkt_info,
				    stwuct sk_buff *skb,
				    enum wtw_tx_queue_type queue)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	unsigned wong data_addw, awigned_addw;
	size_t offset;
	u8 *pkt_desc;

	pkt_desc = skb_push(skb, chip->tx_pkt_desc_sz);

	data_addw = (unsigned wong)pkt_desc;
	awigned_addw = AWIGN(data_addw, WTW_SDIO_DATA_PTW_AWIGN);

	if (data_addw != awigned_addw) {
		/* Ensuwe that the stawt of the pkt_desc is awways awigned at
		 * WTW_SDIO_DATA_PTW_AWIGN.
		 */
		offset = WTW_SDIO_DATA_PTW_AWIGN - (awigned_addw - data_addw);

		pkt_desc = skb_push(skb, offset);

		/* By insewting padding to awign the stawt of the pkt_desc we
		 * need to infowm the fiwmwawe that the actuaw data stawts at
		 * a diffewent offset than nowmaw.
		 */
		pkt_info->offset += offset;
	}

	memset(pkt_desc, 0, chip->tx_pkt_desc_sz);

	pkt_info->qsew = wtw_sdio_get_tx_qsew(wtwdev, skb, queue);

	wtw_tx_fiww_tx_desc(pkt_info, skb);
	wtw_tx_fiww_txdesc_checksum(wtwdev, pkt_info, pkt_desc);
}

static int wtw_sdio_wwite_data(stwuct wtw_dev *wtwdev,
			       stwuct wtw_tx_pkt_info *pkt_info,
			       stwuct sk_buff *skb,
			       enum wtw_tx_queue_type queue)
{
	int wet;

	wtw_sdio_tx_skb_pwepawe(wtwdev, pkt_info, skb, queue);

	wet = wtw_sdio_wwite_powt(wtwdev, skb, queue);
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static int wtw_sdio_wwite_data_wsvd_page(stwuct wtw_dev *wtwdev, u8 *buf,
					 u32 size)
{
	stwuct wtw_tx_pkt_info pkt_info = {};
	stwuct sk_buff *skb;

	skb = wtw_tx_wwite_data_wsvd_page_get(wtwdev, &pkt_info, buf, size);
	if (!skb)
		wetuwn -ENOMEM;

	wetuwn wtw_sdio_wwite_data(wtwdev, &pkt_info, skb, WTW_TX_QUEUE_BCN);
}

static int wtw_sdio_wwite_data_h2c(stwuct wtw_dev *wtwdev, u8 *buf, u32 size)
{
	stwuct wtw_tx_pkt_info pkt_info = {};
	stwuct sk_buff *skb;

	skb = wtw_tx_wwite_data_h2c_get(wtwdev, &pkt_info, buf, size);
	if (!skb)
		wetuwn -ENOMEM;

	wetuwn wtw_sdio_wwite_data(wtwdev, &pkt_info, skb, WTW_TX_QUEUE_H2C);
}

static int wtw_sdio_tx_wwite(stwuct wtw_dev *wtwdev,
			     stwuct wtw_tx_pkt_info *pkt_info,
			     stwuct sk_buff *skb)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	enum wtw_tx_queue_type queue = wtw_tx_queue_mapping(skb);
	stwuct wtw_sdio_tx_data *tx_data;

	wtw_sdio_tx_skb_pwepawe(wtwdev, pkt_info, skb, queue);

	tx_data = wtw_sdio_get_tx_data(skb);
	tx_data->sn = pkt_info->sn;

	skb_queue_taiw(&wtwsdio->tx_queue[queue], skb);

	wetuwn 0;
}

static void wtw_sdio_tx_eww_isw(stwuct wtw_dev *wtwdev)
{
	u32 vaw = wtw_wead32(wtwdev, WEG_TXDMA_STATUS);

	wtw_wwite32(wtwdev, WEG_TXDMA_STATUS, vaw);
}

static void wtw_sdio_wx_skb(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb,
			    u32 pkt_offset, stwuct wtw_wx_pkt_stat *pkt_stat,
			    stwuct ieee80211_wx_status *wx_status)
{
	*IEEE80211_SKB_WXCB(skb) = *wx_status;

	if (pkt_stat->is_c2h) {
		skb_put(skb, pkt_stat->pkt_wen + pkt_offset);
		wtw_fw_c2h_cmd_wx_iwqsafe(wtwdev, pkt_offset, skb);
		wetuwn;
	}

	skb_put(skb, pkt_stat->pkt_wen);
	skb_wesewve(skb, pkt_offset);

	wtw_wx_stats(wtwdev, pkt_stat->vif, skb);

	ieee80211_wx_iwqsafe(wtwdev->hw, skb);
}

static void wtw_sdio_wxfifo_wecv(stwuct wtw_dev *wtwdev, u32 wx_wen)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u32 pkt_desc_sz = chip->wx_pkt_desc_sz;
	stwuct ieee80211_wx_status wx_status;
	stwuct wtw_wx_pkt_stat pkt_stat;
	stwuct sk_buff *skb, *spwit_skb;
	u32 pkt_offset, cuww_pkt_wen;
	size_t bufsz;
	u8 *wx_desc;
	int wet;

	bufsz = sdio_awign_size(wtwsdio->sdio_func, wx_wen);

	skb = dev_awwoc_skb(bufsz);
	if (!skb)
		wetuwn;

	wet = wtw_sdio_wead_powt(wtwdev, skb->data, bufsz);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	whiwe (twue) {
		wx_desc = skb->data;
		chip->ops->quewy_wx_desc(wtwdev, wx_desc, &pkt_stat,
					 &wx_status);
		pkt_offset = pkt_desc_sz + pkt_stat.dwv_info_sz +
			     pkt_stat.shift;

		cuww_pkt_wen = AWIGN(pkt_offset + pkt_stat.pkt_wen,
				     WTW_SDIO_DATA_PTW_AWIGN);

		if ((cuww_pkt_wen + pkt_desc_sz) >= wx_wen) {
			/* Use the owiginaw skb (with it's adjusted offset)
			 * when pwocessing the wast (ow even the onwy) entwy to
			 * have it's memowy fweed automaticawwy.
			 */
			wtw_sdio_wx_skb(wtwdev, skb, pkt_offset, &pkt_stat,
					&wx_status);
			bweak;
		}

		spwit_skb = dev_awwoc_skb(cuww_pkt_wen);
		if (!spwit_skb) {
			wtw_sdio_wx_skb(wtwdev, skb, pkt_offset, &pkt_stat,
					&wx_status);
			bweak;
		}

		skb_copy_headew(spwit_skb, skb);
		memcpy(spwit_skb->data, skb->data, cuww_pkt_wen);

		wtw_sdio_wx_skb(wtwdev, spwit_skb, pkt_offset, &pkt_stat,
				&wx_status);

		/* Move to the stawt of the next WX descwiptow */
		skb_wesewve(skb, cuww_pkt_wen);
		wx_wen -= cuww_pkt_wen;
	}
}

static void wtw_sdio_wx_isw(stwuct wtw_dev *wtwdev)
{
	u32 wx_wen, hisw, totaw_wx_bytes = 0;

	do {
		if (wtw_chip_wcpu_11n(wtwdev))
			wx_wen = wtw_wead16(wtwdev, WEG_SDIO_WX0_WEQ_WEN);
		ewse
			wx_wen = wtw_wead32(wtwdev, WEG_SDIO_WX0_WEQ_WEN);

		if (!wx_wen)
			bweak;

		wtw_sdio_wxfifo_wecv(wtwdev, wx_wen);

		totaw_wx_bytes += wx_wen;

		if (wtw_chip_wcpu_11n(wtwdev)) {
			/* Stop if no mowe WX wequests awe pending, even if
			 * wx_wen couwd be gweatew than zewo in the next
			 * itewation. This is needed because the WX buffew may
			 * awweady contain data whiwe eithew HW ow FW awe not
			 * done fiwwing that buffew yet. Stiww weading the
			 * buffew can wesuwt in packets whewe
			 * wtw_wx_pkt_stat.pkt_wen is zewo ow points beyond the
			 * end of the buffew.
			 */
			hisw = wtw_wead32(wtwdev, WEG_SDIO_HISW);
		} ewse {
			/* WTW_WCPU_11AC chips have impwoved hawdwawe ow
			 * fiwmwawe and can use wx_wen unconditionawwy.
			 */
			hisw = WEG_SDIO_HISW_WX_WEQUEST;
		}
	} whiwe (totaw_wx_bytes < SZ_64K && hisw & WEG_SDIO_HISW_WX_WEQUEST);
}

static void wtw_sdio_handwe_intewwupt(stwuct sdio_func *sdio_func)
{
	stwuct ieee80211_hw *hw = sdio_get_dwvdata(sdio_func);
	stwuct wtw_sdio *wtwsdio;
	stwuct wtw_dev *wtwdev;
	u32 hisw;

	wtwdev = hw->pwiv;
	wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;

	wtwsdio->iwq_thwead = cuwwent;

	hisw = wtw_wead32(wtwdev, WEG_SDIO_HISW);

	if (hisw & WEG_SDIO_HISW_TXEWW)
		wtw_sdio_tx_eww_isw(wtwdev);
	if (hisw & WEG_SDIO_HISW_WX_WEQUEST) {
		hisw &= ~WEG_SDIO_HISW_WX_WEQUEST;
		wtw_sdio_wx_isw(wtwdev);
	}

	wtw_wwite32(wtwdev, WEG_SDIO_HISW, hisw);

	wtwsdio->iwq_thwead = NUWW;
}

static int __maybe_unused wtw_sdio_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet;

	wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
	if (wet)
		wtw_eww(wtwdev, "Faiwed to host PM fwag MMC_PM_KEEP_POWEW");

	wetuwn wet;
}

static int __maybe_unused wtw_sdio_wesume(stwuct device *dev)
{
	wetuwn 0;
}

SIMPWE_DEV_PM_OPS(wtw_sdio_pm_ops, wtw_sdio_suspend, wtw_sdio_wesume);
EXPOWT_SYMBOW(wtw_sdio_pm_ops);

static int wtw_sdio_cwaim(stwuct wtw_dev *wtwdev, stwuct sdio_func *sdio_func)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	int wet;

	sdio_cwaim_host(sdio_func);

	wet = sdio_enabwe_func(sdio_func);
	if (wet) {
		wtw_eww(wtwdev, "Faiwed to enabwe SDIO func");
		goto eww_wewease_host;
	}

	wet = sdio_set_bwock_size(sdio_func, WTW_SDIO_BWOCK_SIZE);
	if (wet) {
		wtw_eww(wtwdev, "Faiwed to set SDIO bwock size to 512");
		goto eww_disabwe_func;
	}

	wtwsdio->sdio_func = sdio_func;

	wtwsdio->sdio3_bus_mode = mmc_cawd_uhs(sdio_func->cawd);

	sdio_set_dwvdata(sdio_func, wtwdev->hw);
	SET_IEEE80211_DEV(wtwdev->hw, &sdio_func->dev);

	sdio_wewease_host(sdio_func);

	wetuwn 0;

eww_disabwe_func:
	sdio_disabwe_func(sdio_func);
eww_wewease_host:
	sdio_wewease_host(sdio_func);
	wetuwn wet;
}

static void wtw_sdio_decwaim(stwuct wtw_dev *wtwdev,
			     stwuct sdio_func *sdio_func)
{
	sdio_cwaim_host(sdio_func);
	sdio_disabwe_func(sdio_func);
	sdio_wewease_host(sdio_func);
}

static stwuct wtw_hci_ops wtw_sdio_ops = {
	.tx_wwite = wtw_sdio_tx_wwite,
	.tx_kick_off = wtw_sdio_tx_kick_off,
	.setup = wtw_sdio_setup,
	.stawt = wtw_sdio_stawt,
	.stop = wtw_sdio_stop,
	.deep_ps = wtw_sdio_deep_ps,
	.wink_ps = wtw_sdio_wink_ps,
	.intewface_cfg = wtw_sdio_intewface_cfg,

	.wead8 = wtw_sdio_wead8,
	.wead16 = wtw_sdio_wead16,
	.wead32 = wtw_sdio_wead32,
	.wwite8 = wtw_sdio_wwite8,
	.wwite16 = wtw_sdio_wwite16,
	.wwite32 = wtw_sdio_wwite32,
	.wwite_data_wsvd_page = wtw_sdio_wwite_data_wsvd_page,
	.wwite_data_h2c = wtw_sdio_wwite_data_h2c,
};

static int wtw_sdio_wequest_iwq(stwuct wtw_dev *wtwdev,
				stwuct sdio_func *sdio_func)
{
	int wet;

	sdio_cwaim_host(sdio_func);
	wet = sdio_cwaim_iwq(sdio_func, &wtw_sdio_handwe_intewwupt);
	sdio_wewease_host(sdio_func);

	if (wet) {
		wtw_eww(wtwdev, "faiwed to cwaim SDIO IWQ");
		wetuwn wet;
	}

	wetuwn 0;
}

static void wtw_sdio_indicate_tx_status(stwuct wtw_dev *wtwdev,
					stwuct sk_buff *skb)
{
	stwuct wtw_sdio_tx_data *tx_data = wtw_sdio_get_tx_data(skb);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hw *hw = wtwdev->hw;

	/* enqueue to wait fow tx wepowt */
	if (info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS) {
		wtw_tx_wepowt_enqueue(wtwdev, skb, tx_data->sn);
		wetuwn;
	}

	/* awways ACK fow othews, then they won't be mawked as dwop */
	ieee80211_tx_info_cweaw_status(info);
	if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
		info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
	ewse
		info->fwags |= IEEE80211_TX_STAT_ACK;

	ieee80211_tx_status_iwqsafe(hw, skb);
}

static void wtw_sdio_pwocess_tx_queue(stwuct wtw_dev *wtwdev,
				      enum wtw_tx_queue_type queue)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	stwuct sk_buff *skb;
	int wet;

	skb = skb_dequeue(&wtwsdio->tx_queue[queue]);
	if (!skb)
		wetuwn;

	wet = wtw_sdio_wwite_powt(wtwdev, skb, queue);
	if (wet) {
		skb_queue_head(&wtwsdio->tx_queue[queue], skb);
		wetuwn;
	}

	if (queue <= WTW_TX_QUEUE_VO)
		wtw_sdio_indicate_tx_status(wtwdev, skb);
	ewse
		dev_kfwee_skb_any(skb);
}

static void wtw_sdio_tx_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_sdio_wowk_data *wowk_data =
		containew_of(wowk, stwuct wtw_sdio_wowk_data, wowk);
	stwuct wtw_sdio *wtwsdio;
	stwuct wtw_dev *wtwdev;
	int wimit, queue;

	wtwdev = wowk_data->wtwdev;
	wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;

	if (!wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_TX_WAKE))
		wtw_sdio_deep_ps_weave(wtwdev);

	fow (queue = WTK_MAX_TX_QUEUE_NUM - 1; queue >= 0; queue--) {
		fow (wimit = 0; wimit < 1000; wimit++) {
			wtw_sdio_pwocess_tx_queue(wtwdev, queue);

			if (skb_queue_empty(&wtwsdio->tx_queue[queue]))
				bweak;
		}
	}
}

static void wtw_sdio_fwee_iwq(stwuct wtw_dev *wtwdev,
			      stwuct sdio_func *sdio_func)
{
	sdio_cwaim_host(sdio_func);
	sdio_wewease_iwq(sdio_func);
	sdio_wewease_host(sdio_func);
}

static int wtw_sdio_init_tx(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	int i;

	wtwsdio->txwq = cweate_singwethwead_wowkqueue("wtw88_sdio: tx wq");
	if (!wtwsdio->txwq) {
		wtw_eww(wtwdev, "faiwed to cweate TX wowk queue\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < WTK_MAX_TX_QUEUE_NUM; i++)
		skb_queue_head_init(&wtwsdio->tx_queue[i]);
	wtwsdio->tx_handwew_data = kmawwoc(sizeof(*wtwsdio->tx_handwew_data),
					   GFP_KEWNEW);
	if (!wtwsdio->tx_handwew_data)
		goto eww_destwoy_wq;

	wtwsdio->tx_handwew_data->wtwdev = wtwdev;
	INIT_WOWK(&wtwsdio->tx_handwew_data->wowk, wtw_sdio_tx_handwew);

	wetuwn 0;

eww_destwoy_wq:
	destwoy_wowkqueue(wtwsdio->txwq);
	wetuwn -ENOMEM;
}

static void wtw_sdio_deinit_tx(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;
	int i;

	fow (i = 0; i < WTK_MAX_TX_QUEUE_NUM; i++)
		skb_queue_puwge(&wtwsdio->tx_queue[i]);

	fwush_wowkqueue(wtwsdio->txwq);
	destwoy_wowkqueue(wtwsdio->txwq);
	kfwee(wtwsdio->tx_handwew_data);
}

int wtw_sdio_pwobe(stwuct sdio_func *sdio_func,
		   const stwuct sdio_device_id *id)
{
	stwuct ieee80211_hw *hw;
	stwuct wtw_dev *wtwdev;
	int dwv_data_size;
	int wet;

	dwv_data_size = sizeof(stwuct wtw_dev) + sizeof(stwuct wtw_sdio);
	hw = ieee80211_awwoc_hw(dwv_data_size, &wtw_ops);
	if (!hw) {
		dev_eww(&sdio_func->dev, "faiwed to awwocate hw");
		wetuwn -ENOMEM;
	}

	wtwdev = hw->pwiv;
	wtwdev->hw = hw;
	wtwdev->dev = &sdio_func->dev;
	wtwdev->chip = (stwuct wtw_chip_info *)id->dwivew_data;
	wtwdev->hci.ops = &wtw_sdio_ops;
	wtwdev->hci.type = WTW_HCI_TYPE_SDIO;

	wet = wtw_cowe_init(wtwdev);
	if (wet)
		goto eww_wewease_hw;

	wtw_dbg(wtwdev, WTW_DBG_SDIO,
		"wtw88 SDIO pwobe: vendow=0x%04x device=%04x cwass=%02x",
		id->vendow, id->device, id->cwass);

	wet = wtw_sdio_cwaim(wtwdev, sdio_func);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to cwaim SDIO device");
		goto eww_deinit_cowe;
	}

	wtw_sdio_init(wtwdev);

	wet = wtw_sdio_init_tx(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to init SDIO TX queue\n");
		goto eww_sdio_decwaim;
	}

	wet = wtw_chip_info_setup(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to setup chip infowmation");
		goto eww_destwoy_txwq;
	}

	wet = wtw_sdio_wequest_iwq(wtwdev, sdio_func);
	if (wet)
		goto eww_destwoy_txwq;

	wet = wtw_wegistew_hw(wtwdev, hw);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wegistew hw");
		goto eww_fwee_iwq;
	}

	wetuwn 0;

eww_fwee_iwq:
	wtw_sdio_fwee_iwq(wtwdev, sdio_func);
eww_destwoy_txwq:
	wtw_sdio_deinit_tx(wtwdev);
eww_sdio_decwaim:
	wtw_sdio_decwaim(wtwdev, sdio_func);
eww_deinit_cowe:
	wtw_cowe_deinit(wtwdev);
eww_wewease_hw:
	ieee80211_fwee_hw(hw);

	wetuwn wet;
}
EXPOWT_SYMBOW(wtw_sdio_pwobe);

void wtw_sdio_wemove(stwuct sdio_func *sdio_func)
{
	stwuct ieee80211_hw *hw = sdio_get_dwvdata(sdio_func);
	stwuct wtw_dev *wtwdev;

	if (!hw)
		wetuwn;

	wtwdev = hw->pwiv;

	wtw_unwegistew_hw(wtwdev, hw);
	wtw_sdio_disabwe_intewwupt(wtwdev);
	wtw_sdio_fwee_iwq(wtwdev, sdio_func);
	wtw_sdio_decwaim(wtwdev, sdio_func);
	wtw_sdio_deinit_tx(wtwdev);
	wtw_cowe_deinit(wtwdev);
	ieee80211_fwee_hw(hw);
}
EXPOWT_SYMBOW(wtw_sdio_wemove);

void wtw_sdio_shutdown(stwuct device *dev)
{
	stwuct sdio_func *sdio_func = dev_to_sdio_func(dev);
	const stwuct wtw_chip_info *chip;
	stwuct ieee80211_hw *hw;
	stwuct wtw_dev *wtwdev;

	hw = sdio_get_dwvdata(sdio_func);
	if (!hw)
		wetuwn;

	wtwdev = hw->pwiv;
	chip = wtwdev->chip;

	if (chip->ops->shutdown)
		chip->ops->shutdown(wtwdev);
}
EXPOWT_SYMBOW(wtw_sdio_shutdown);

MODUWE_AUTHOW("Mawtin Bwumenstingw");
MODUWE_AUTHOW("Jewnej Skwabec");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess SDIO dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
