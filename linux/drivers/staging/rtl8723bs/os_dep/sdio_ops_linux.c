// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 *******************************************************************************/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>

static boow wtw_sdio_cwaim_host_needed(stwuct sdio_func *func)
{
	stwuct dvobj_pwiv *dvobj = sdio_get_dwvdata(func);
	stwuct sdio_data *sdio_data = &dvobj->intf_data;

	if (sdio_data->sys_sdio_iwq_thd && sdio_data->sys_sdio_iwq_thd == cuwwent)
		wetuwn fawse;
	wetuwn twue;
}

inwine void wtw_sdio_set_iwq_thd(stwuct dvobj_pwiv *dvobj, void *thd_hdw)
{
	stwuct sdio_data *sdio_data = &dvobj->intf_data;

	sdio_data->sys_sdio_iwq_thd = thd_hdw;
}

/*
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 _sd_cmd52_wead(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	int eww = 0, i;
	stwuct sdio_func *func;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;

	fow (i = 0; i < cnt; i++) {
		pdata[i] = sdio_weadb(func, addw + i, &eww);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/*
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 sd_cmd52_wead(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	int eww = 0;
	stwuct sdio_func *func;
	boow cwaim_needed;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	eww = _sd_cmd52_wead(pintfhdw, addw, cnt, pdata);
	if (cwaim_needed)
		sdio_wewease_host(func);
	wetuwn eww;
}

/*
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 _sd_cmd52_wwite(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	int eww = 0, i;
	stwuct sdio_func *func;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;

	fow (i = 0; i < cnt; i++) {
		sdio_wwiteb(func, pdata[i], addw + i, &eww);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/*
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 sd_cmd52_wwite(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	int eww = 0;
	stwuct sdio_func *func;
	boow cwaim_needed;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	eww = _sd_cmd52_wwite(pintfhdw, addw, cnt, pdata);
	if (cwaim_needed)
		sdio_wewease_host(func);
	wetuwn eww;
}

u8 sd_wead8(stwuct intf_hdw *pintfhdw, u32 addw, s32 *eww)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	u8 v = 0;
	stwuct sdio_func *func;
	boow cwaim_needed;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn v;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	v = sdio_weadb(func, addw, eww);
	if (cwaim_needed)
		sdio_wewease_host(func);
	wetuwn v;
}

u32 sd_wead32(stwuct intf_hdw *pintfhdw, u32 addw, s32 *eww)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;
	u32 v = 0;
	stwuct sdio_func *func;
	boow cwaim_needed;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn v;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	v = sdio_weadw(func, addw, eww);
	if (cwaim_needed)
		sdio_wewease_host(func);

	if (eww && *eww) {
		int i;

		*eww = 0;
		fow (i = 0; i < SD_IO_TWY_CNT; i++) {
			if (cwaim_needed)
				sdio_cwaim_host(func);
			v = sdio_weadw(func, addw, eww);
			if (cwaim_needed)
				sdio_wewease_host(func);

			if (*eww == 0) {
				wtw_weset_continuaw_io_ewwow(psdiodev);
				bweak;
			} ewse {
				if ((-ESHUTDOWN == *eww) || (-ENODEV == *eww))
					padaptew->bSuwpwiseWemoved = twue;

				if (wtw_inc_and_chk_continuaw_io_ewwow(psdiodev) == twue) {
					padaptew->bSuwpwiseWemoved = twue;
					bweak;
				}
			}
		}
	}
	wetuwn  v;
}

void sd_wwite8(stwuct intf_hdw *pintfhdw, u32 addw, u8 v, s32 *eww)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;
	stwuct sdio_func *func;
	boow cwaim_needed;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	sdio_wwiteb(func, v, addw, eww);
	if (cwaim_needed)
		sdio_wewease_host(func);
}

void sd_wwite32(stwuct intf_hdw *pintfhdw, u32 addw, u32 v, s32 *eww)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;
	stwuct sdio_func *func;
	boow cwaim_needed;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	sdio_wwitew(func, v, addw, eww);
	if (cwaim_needed)
		sdio_wewease_host(func);

	if (eww && *eww) {
		int i;

		*eww = 0;
		fow (i = 0; i < SD_IO_TWY_CNT; i++) {
			if (cwaim_needed)
				sdio_cwaim_host(func);
			sdio_wwitew(func, v, addw, eww);
			if (cwaim_needed)
				sdio_wewease_host(func);
			if (*eww == 0) {
				wtw_weset_continuaw_io_ewwow(psdiodev);
				bweak;
			} ewse {
				if ((-ESHUTDOWN == *eww) || (-ENODEV == *eww))
					padaptew->bSuwpwiseWemoved = twue;

				if (wtw_inc_and_chk_continuaw_io_ewwow(psdiodev) == twue) {
					padaptew->bSuwpwiseWemoved = twue;
					bweak;
				}
			}
		}

	}
}

/*
 * Use CMD53 to wead data fwom SDIO device.
 * This function MUST be cawwed aftew sdio_cwaim_host() ow
 * in SDIO ISW(host had been cwaimed).
 *
 * Pawametews:
 *psdio	pointew of SDIO_DATA
 *addw	addwess to wead
 *cnt		amount to wead
 *pdata	pointew to put data, this shouwd be a "DMA:abwe scwatch buffew"!
 *
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 _sd_wead(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, void *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	int eww = -EPEWM;
	stwuct sdio_func *func;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;

	if (unwikewy((cnt == 1) || (cnt == 2))) {
		int i;
		u8 *pbuf = pdata;

		fow (i = 0; i < cnt; i++) {
			*(pbuf + i) = sdio_weadb(func, addw + i, &eww);

			if (eww)
				bweak;
		}
		wetuwn eww;
	}

	eww = sdio_memcpy_fwomio(func, pdata, addw, cnt);

	wetuwn eww;
}

/*
 * Use CMD53 to wead data fwom SDIO device.
 *
 * Pawametews:
 *psdio	pointew of SDIO_DATA
 *addw	addwess to wead
 *cnt		amount to wead
 *pdata	pointew to put data, this shouwd be a "DMA:abwe scwatch buffew"!
 *
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 sd_wead(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, void *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	stwuct sdio_func *func;
	boow cwaim_needed;
	s32 eww = -EPEWM;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	eww = _sd_wead(pintfhdw, addw, cnt, pdata);
	if (cwaim_needed)
		sdio_wewease_host(func);
	wetuwn eww;
}

/*
 * Use CMD53 to wwite data to SDIO device.
 * This function MUST be cawwed aftew sdio_cwaim_host() ow
 * in SDIO ISW(host had been cwaimed).
 *
 * Pawametews:
 *psdio	pointew of SDIO_DATA
 *addw	addwess to wwite
 *cnt		amount to wwite
 *pdata	data pointew, this shouwd be a "DMA:abwe scwatch buffew"!
 *
 * Wetuwn:
 *0		Success
 *othews	Faiw
 */
s32 _sd_wwite(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, void *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;

	stwuct sdio_func *func;
	u32 size;
	s32 eww =  -EPEWM;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;
/*	size = sdio_awign_size(func, cnt); */

	if (unwikewy((cnt == 1) || (cnt == 2))) {
		int i;
		u8 *pbuf = pdata;

		fow (i = 0; i < cnt; i++) {
			sdio_wwiteb(func, *(pbuf + i), addw + i, &eww);
			if (eww)
				bweak;
		}

		wetuwn eww;
	}

	size = cnt;
	eww = sdio_memcpy_toio(func, addw, pdata, size);

	wetuwn eww;
}

/*
 * Use CMD53 to wwite data to SDIO device.
 *
 * Pawametews:
 *  psdio	pointew of SDIO_DATA
 *  addw	addwess to wwite
 *  cnt		amount to wwite
 *  pdata	data pointew, this shouwd be a "DMA:abwe scwatch buffew"!
 *
 * Wetuwn:
 *  0		Success
 *  othews	Faiw
 */
s32 sd_wwite(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, void *pdata)
{
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *psdiodev;
	stwuct sdio_data *psdio;
	stwuct sdio_func *func;
	boow cwaim_needed;
	s32 eww =  -EPEWM;

	padaptew = pintfhdw->padaptew;
	psdiodev = pintfhdw->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn eww;

	func = psdio->func;
	cwaim_needed = wtw_sdio_cwaim_host_needed(func);

	if (cwaim_needed)
		sdio_cwaim_host(func);
	eww = _sd_wwite(pintfhdw, addw, cnt, pdata);
	if (cwaim_needed)
		sdio_wewease_host(func);
	wetuwn eww;
}
