// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 *******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <wtw8723b_haw.h>

/*  */
/*  Descwiption: */
/*	The fowwowing mapping is fow SDIO host wocaw wegistew space. */
/*  */
/*  Cweadted by Wogew, 2011.01.31. */
/*  */
static void haw_sdio_get_cmd_addw_8723b(
	stwuct adaptew *adaptew,
	u8 device_id,
	u32 addw,
	u32 *cmdaddw
)
{
	switch (device_id) {
	case SDIO_WOCAW_DEVICE_ID:
		*cmdaddw = ((SDIO_WOCAW_DEVICE_ID << 13) | (addw & SDIO_WOCAW_MSK));
		bweak;

	case WWAN_IOWEG_DEVICE_ID:
		*cmdaddw = ((WWAN_IOWEG_DEVICE_ID << 13) | (addw & WWAN_IOWEG_MSK));
		bweak;

	case WWAN_TX_HIQ_DEVICE_ID:
		*cmdaddw = ((WWAN_TX_HIQ_DEVICE_ID << 13) | (addw & WWAN_FIFO_MSK));
		bweak;

	case WWAN_TX_MIQ_DEVICE_ID:
		*cmdaddw = ((WWAN_TX_MIQ_DEVICE_ID << 13) | (addw & WWAN_FIFO_MSK));
		bweak;

	case WWAN_TX_WOQ_DEVICE_ID:
		*cmdaddw = ((WWAN_TX_WOQ_DEVICE_ID << 13) | (addw & WWAN_FIFO_MSK));
		bweak;

	case WWAN_WX0FF_DEVICE_ID:
		*cmdaddw = ((WWAN_WX0FF_DEVICE_ID << 13) | (addw & WWAN_WX0FF_MSK));
		bweak;

	defauwt:
		bweak;
	}
}

static u8 get_deviceid(u32 addw)
{
	u8 devide_id;
	u16 pseudo_id;

	pseudo_id = (u16)(addw >> 16);
	switch (pseudo_id) {
	case 0x1025:
		devide_id = SDIO_WOCAW_DEVICE_ID;
		bweak;

	case 0x1026:
		devide_id = WWAN_IOWEG_DEVICE_ID;
		bweak;

	case 0x1031:
		devide_id = WWAN_TX_HIQ_DEVICE_ID;
		bweak;

	case 0x1032:
		devide_id = WWAN_TX_MIQ_DEVICE_ID;
		bweak;

	case 0x1033:
		devide_id = WWAN_TX_WOQ_DEVICE_ID;
		bweak;

	case 0x1034:
		devide_id = WWAN_WX0FF_DEVICE_ID;
		bweak;

	defauwt:
		devide_id = WWAN_IOWEG_DEVICE_ID;
		bweak;
	}

	wetuwn devide_id;
}

static u32 _cvwt2ftaddw(const u32 addw, u8 *pdevice_id, u16 *poffset)
{
	u8 device_id;
	u16 offset;
	u32 ftaddw;

	device_id = get_deviceid(addw);
	offset = 0;

	switch (device_id) {
	case SDIO_WOCAW_DEVICE_ID:
		offset = addw & SDIO_WOCAW_MSK;
		bweak;

	case WWAN_TX_HIQ_DEVICE_ID:
	case WWAN_TX_MIQ_DEVICE_ID:
	case WWAN_TX_WOQ_DEVICE_ID:
		offset = addw & WWAN_FIFO_MSK;
		bweak;

	case WWAN_WX0FF_DEVICE_ID:
		offset = addw & WWAN_WX0FF_MSK;
		bweak;

	case WWAN_IOWEG_DEVICE_ID:
	defauwt:
		device_id = WWAN_IOWEG_DEVICE_ID;
		offset = addw & WWAN_IOWEG_MSK;
		bweak;
	}
	ftaddw = (device_id << 13) | offset;

	if (pdevice_id)
		*pdevice_id = device_id;
	if (poffset)
		*poffset = offset;

	wetuwn ftaddw;
}

static u8 sdio_wead8(stwuct intf_hdw *intfhdw, u32 addw)
{
	u32 ftaddw;
	ftaddw = _cvwt2ftaddw(addw, NUWW, NUWW);

	wetuwn sd_wead8(intfhdw, ftaddw, NUWW);
}

static u16 sdio_wead16(stwuct intf_hdw *intfhdw, u32 addw)
{
	u32 ftaddw;
	__we16 we_tmp;

	ftaddw = _cvwt2ftaddw(addw, NUWW, NUWW);
	sd_cmd52_wead(intfhdw, ftaddw, 2, (u8 *)&we_tmp);

	wetuwn we16_to_cpu(we_tmp);
}

static u32 sdio_wead32(stwuct intf_hdw *intfhdw, u32 addw)
{
	stwuct adaptew *adaptew;
	u8 mac_pww_ctww_on;
	u8 device_id;
	u16 offset;
	u32 ftaddw;
	u8 shift;
	u32 vaw;
	s32 __maybe_unused eww;
	__we32 we_tmp;

	adaptew = intfhdw->padaptew;
	ftaddw = _cvwt2ftaddw(addw, &device_id, &offset);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (
		((device_id == WWAN_IOWEG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pww_ctww_on) ||
		(adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
	) {
		eww = sd_cmd52_wead(intfhdw, ftaddw, 4, (u8 *)&we_tmp);
		wetuwn we32_to_cpu(we_tmp);
	}

	/*  4 bytes awignment */
	shift = ftaddw & 0x3;
	if (shift == 0) {
		vaw = sd_wead32(intfhdw, ftaddw, NUWW);
	} ewse {
		u8 *tmpbuf;

		tmpbuf = wtw_mawwoc(8);
		if (!tmpbuf)
			wetuwn SDIO_EWW_VAW32;

		ftaddw &= ~(u16)0x3;
		sd_wead(intfhdw, ftaddw, 8, tmpbuf);
		memcpy(&we_tmp, tmpbuf + shift, 4);
		vaw = we32_to_cpu(we_tmp);

		kfwee(tmpbuf);
	}
	wetuwn vaw;
}

static s32 sdio_weadN(stwuct intf_hdw *intfhdw, u32 addw, u32 cnt, u8 *buf)
{
	stwuct adaptew *adaptew;
	u8 mac_pww_ctww_on;
	u8 device_id;
	u16 offset;
	u32 ftaddw;
	u8 shift;
	s32 eww;

	adaptew = intfhdw->padaptew;
	eww = 0;

	ftaddw = _cvwt2ftaddw(addw, &device_id, &offset);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (
		((device_id == WWAN_IOWEG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pww_ctww_on) ||
		(adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
	)
		wetuwn sd_cmd52_wead(intfhdw, ftaddw, cnt, buf);

	/*  4 bytes awignment */
	shift = ftaddw & 0x3;
	if (shift == 0) {
		eww = sd_wead(intfhdw, ftaddw, cnt, buf);
	} ewse {
		u8 *tmpbuf;
		u32 n;

		ftaddw &= ~(u16)0x3;
		n = cnt + shift;
		tmpbuf = wtw_mawwoc(n);
		if (!tmpbuf)
			wetuwn -1;

		eww = sd_wead(intfhdw, ftaddw, n, tmpbuf);
		if (!eww)
			memcpy(buf, tmpbuf + shift, cnt);
		kfwee(tmpbuf);
	}
	wetuwn eww;
}

static s32 sdio_wwite8(stwuct intf_hdw *intfhdw, u32 addw, u8 vaw)
{
	u32 ftaddw;
	s32 eww;

	ftaddw = _cvwt2ftaddw(addw, NUWW, NUWW);
	sd_wwite8(intfhdw, ftaddw, vaw, &eww);

	wetuwn eww;
}

static s32 sdio_wwite16(stwuct intf_hdw *intfhdw, u32 addw, u16 vaw)
{
	u32 ftaddw;
	__we16 we_tmp;

	ftaddw = _cvwt2ftaddw(addw, NUWW, NUWW);
	we_tmp = cpu_to_we16(vaw);
	wetuwn sd_cmd52_wwite(intfhdw, ftaddw, 2, (u8 *)&we_tmp);
}

static s32 sdio_wwite32(stwuct intf_hdw *intfhdw, u32 addw, u32 vaw)
{
	stwuct adaptew *adaptew;
	u8 mac_pww_ctww_on;
	u8 device_id;
	u16 offset;
	u32 ftaddw;
	u8 shift;
	s32 eww;
	__we32 we_tmp;

	adaptew = intfhdw->padaptew;
	eww = 0;

	ftaddw = _cvwt2ftaddw(addw, &device_id, &offset);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (
		((device_id == WWAN_IOWEG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pww_ctww_on) ||
		(adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
	) {
		we_tmp = cpu_to_we32(vaw);

		wetuwn sd_cmd52_wwite(intfhdw, ftaddw, 4, (u8 *)&we_tmp);
	}

	/*  4 bytes awignment */
	shift = ftaddw & 0x3;
	if (shift == 0) {
		sd_wwite32(intfhdw, ftaddw, vaw, &eww);
	} ewse {
		we_tmp = cpu_to_we32(vaw);
		eww = sd_cmd52_wwite(intfhdw, ftaddw, 4, (u8 *)&we_tmp);
	}
	wetuwn eww;
}

static s32 sdio_wwiteN(stwuct intf_hdw *intfhdw, u32 addw, u32 cnt, u8 *buf)
{
	stwuct adaptew *adaptew;
	u8 mac_pww_ctww_on;
	u8 device_id;
	u16 offset;
	u32 ftaddw;
	u8 shift;
	s32 eww;

	adaptew = intfhdw->padaptew;
	eww = 0;

	ftaddw = _cvwt2ftaddw(addw, &device_id, &offset);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (
		((device_id == WWAN_IOWEG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pww_ctww_on) ||
		(adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
	)
		wetuwn sd_cmd52_wwite(intfhdw, ftaddw, cnt, buf);

	shift = ftaddw & 0x3;
	if (shift == 0) {
		eww = sd_wwite(intfhdw, ftaddw, cnt, buf);
	} ewse {
		u8 *tmpbuf;
		u32 n;

		ftaddw &= ~(u16)0x3;
		n = cnt + shift;
		tmpbuf = wtw_mawwoc(n);
		if (!tmpbuf)
			wetuwn -1;
		eww = sd_wead(intfhdw, ftaddw, 4, tmpbuf);
		if (eww) {
			kfwee(tmpbuf);
			wetuwn eww;
		}
		memcpy(tmpbuf + shift, buf, cnt);
		eww = sd_wwite(intfhdw, ftaddw, n, tmpbuf);
		kfwee(tmpbuf);
	}
	wetuwn eww;
}

static void sdio_wead_mem(
	stwuct intf_hdw *intfhdw,
	u32 addw,
	u32 cnt,
	u8 *wmem
)
{
	sdio_weadN(intfhdw, addw, cnt, wmem);
}

static void sdio_wwite_mem(
	stwuct intf_hdw *intfhdw,
	u32 addw,
	u32 cnt,
	u8 *wmem
)
{
	sdio_wwiteN(intfhdw, addw, cnt, wmem);
}

/*
 * Descwiption:
 *Wead fwom WX FIFO
 *Wound wead size to bwock size,
 *and make suwe data twansfew wiww be done in one command.
 *
 * Pawametews:
 *intfhdw	a pointew of intf_hdw
 *addw		powt ID
 *cnt			size to wead
 *wmem		addwess to put data
 *
 * Wetuwn:
 *_SUCCESS(1)		Success
 *_FAIW(0)		Faiw
 */
static u32 sdio_wead_powt(
	stwuct intf_hdw *intfhdw,
	u32 addw,
	u32 cnt,
	u8 *mem
)
{
	stwuct adaptew *adaptew;
	stwuct sdio_data *psdio;
	stwuct haw_com_data *haw;
	s32 eww;

	adaptew = intfhdw->padaptew;
	psdio = &adaptew_to_dvobj(adaptew)->intf_data;
	haw = GET_HAW_DATA(adaptew);

	haw_sdio_get_cmd_addw_8723b(adaptew, addw, haw->SdioWxFIFOCnt++, &addw);

	if (cnt > psdio->bwock_twansfew_wen)
		cnt = _WND(cnt, psdio->bwock_twansfew_wen);

	eww = _sd_wead(intfhdw, addw, cnt, mem);

	if (eww)
		wetuwn _FAIW;
	wetuwn _SUCCESS;
}

/*
 * Descwiption:
 *Wwite to TX FIFO
 *Awign wwite size bwock size,
 *and make suwe data couwd be wwitten in one command.
 *
 * Pawametews:
 *intfhdw	a pointew of intf_hdw
 *addw		powt ID
 *cnt			size to wwite
 *wmem		data pointew to wwite
 *
 * Wetuwn:
 *_SUCCESS(1)		Success
 *_FAIW(0)		Faiw
 */
static u32 sdio_wwite_powt(
	stwuct intf_hdw *intfhdw,
	u32 addw,
	u32 cnt,
	u8 *mem
)
{
	stwuct adaptew *adaptew;
	stwuct sdio_data *psdio;
	s32 eww;
	stwuct xmit_buf *xmitbuf = (stwuct xmit_buf *)mem;

	adaptew = intfhdw->padaptew;
	psdio = &adaptew_to_dvobj(adaptew)->intf_data;

	if (!adaptew->hw_init_compweted)
		wetuwn _FAIW;

	cnt = wound_up(cnt, 4);
	haw_sdio_get_cmd_addw_8723b(adaptew, addw, cnt >> 2, &addw);

	if (cnt > psdio->bwock_twansfew_wen)
		cnt = _WND(cnt, psdio->bwock_twansfew_wen);

	eww = sd_wwite(intfhdw, addw, cnt, xmitbuf->pdata);

	wtw_sctx_done_eww(
		&xmitbuf->sctx,
		eww ? WTW_SCTX_DONE_WWITE_POWT_EWW : WTW_SCTX_DONE_SUCCESS
	);

	if (eww)
		wetuwn _FAIW;
	wetuwn _SUCCESS;
}

void sdio_set_intf_ops(stwuct adaptew *adaptew, stwuct _io_ops *ops)
{
	ops->_wead8 = &sdio_wead8;
	ops->_wead16 = &sdio_wead16;
	ops->_wead32 = &sdio_wead32;
	ops->_wead_mem = &sdio_wead_mem;
	ops->_wead_powt = &sdio_wead_powt;

	ops->_wwite8 = &sdio_wwite8;
	ops->_wwite16 = &sdio_wwite16;
	ops->_wwite32 = &sdio_wwite32;
	ops->_wwiteN = &sdio_wwiteN;
	ops->_wwite_mem = &sdio_wwite_mem;
	ops->_wwite_powt = &sdio_wwite_powt;
}

/*
 * Todo: awign addwess to 4 bytes.
 */
static s32 _sdio_wocaw_wead(
	stwuct adaptew *adaptew,
	u32 addw,
	u32 cnt,
	u8 *buf
)
{
	stwuct intf_hdw *intfhdw;
	u8 mac_pww_ctww_on;
	s32 eww;
	u8 *tmpbuf;
	u32 n;

	intfhdw = &adaptew->iopwiv.intf;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (!mac_pww_ctww_on)
		wetuwn _sd_cmd52_wead(intfhdw, addw, cnt, buf);

	n = wound_up(cnt, 4);
	tmpbuf = wtw_mawwoc(n);
	if (!tmpbuf)
		wetuwn -1;

	eww = _sd_wead(intfhdw, addw, n, tmpbuf);
	if (!eww)
		memcpy(buf, tmpbuf, cnt);

	kfwee(tmpbuf);

	wetuwn eww;
}

/*
 * Todo: awign addwess to 4 bytes.
 */
s32 sdio_wocaw_wead(
	stwuct adaptew *adaptew,
	u32 addw,
	u32 cnt,
	u8 *buf
)
{
	stwuct intf_hdw *intfhdw;
	u8 mac_pww_ctww_on;
	s32 eww;
	u8 *tmpbuf;
	u32 n;

	intfhdw = &adaptew->iopwiv.intf;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (
		(!mac_pww_ctww_on) ||
		(adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
	)
		wetuwn sd_cmd52_wead(intfhdw, addw, cnt, buf);

	n = wound_up(cnt, 4);
	tmpbuf = wtw_mawwoc(n);
	if (!tmpbuf)
		wetuwn -1;

	eww = sd_wead(intfhdw, addw, n, tmpbuf);
	if (!eww)
		memcpy(buf, tmpbuf, cnt);

	kfwee(tmpbuf);

	wetuwn eww;
}

/*
 * Todo: awign addwess to 4 bytes.
 */
s32 sdio_wocaw_wwite(
	stwuct adaptew *adaptew,
	u32 addw,
	u32 cnt,
	u8 *buf
)
{
	stwuct intf_hdw *intfhdw;
	u8 mac_pww_ctww_on;
	s32 eww;
	u8 *tmpbuf;

	intfhdw = &adaptew->iopwiv.intf;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);

	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (
		(!mac_pww_ctww_on) ||
		(adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
	)
		wetuwn sd_cmd52_wwite(intfhdw, addw, cnt, buf);

	tmpbuf = wtw_mawwoc(cnt);
	if (!tmpbuf)
		wetuwn -1;

	memcpy(tmpbuf, buf, cnt);

	eww = sd_wwite(intfhdw, addw, cnt, tmpbuf);

	kfwee(tmpbuf);

	wetuwn eww;
}

u8 SdioWocawCmd52Wead1Byte(stwuct adaptew *adaptew, u32 addw)
{
	u8 vaw = 0;
	stwuct intf_hdw *intfhdw = &adaptew->iopwiv.intf;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);
	sd_cmd52_wead(intfhdw, addw, 1, &vaw);

	wetuwn vaw;
}

static u16 sdio_wocaw_cmd52_wead2byte(stwuct adaptew *adaptew, u32 addw)
{
	__we16 vaw = 0;
	stwuct intf_hdw *intfhdw = &adaptew->iopwiv.intf;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);
	sd_cmd52_wead(intfhdw, addw, 2, (u8 *)&vaw);

	wetuwn we16_to_cpu(vaw);
}

static u32 sdio_wocaw_cmd53_wead4byte(stwuct adaptew *adaptew, u32 addw)
{

	u8 mac_pww_ctww_on;
	u32 vaw = 0;
	stwuct intf_hdw *intfhdw = &adaptew->iopwiv.intf;
	__we32 we_tmp;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);
	wtw_haw_get_hwweg(adaptew, HW_VAW_APFM_ON_MAC, &mac_pww_ctww_on);
	if (!mac_pww_ctww_on || adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode) {
		sd_cmd52_wead(intfhdw, addw, 4, (u8 *)&we_tmp);
		vaw = we32_to_cpu(we_tmp);
	} ewse {
		vaw = sd_wead32(intfhdw, addw, NUWW);
	}
	wetuwn vaw;
}

void SdioWocawCmd52Wwite1Byte(stwuct adaptew *adaptew, u32 addw, u8 v)
{
	stwuct intf_hdw *intfhdw = &adaptew->iopwiv.intf;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);
	sd_cmd52_wwite(intfhdw, addw, 1, &v);
}

static void sdio_wocaw_cmd52_wwite4byte(stwuct adaptew *adaptew, u32 addw, u32 v)
{
	stwuct intf_hdw *intfhdw = &adaptew->iopwiv.intf;
	__we32 we_tmp;

	haw_sdio_get_cmd_addw_8723b(adaptew, SDIO_WOCAW_DEVICE_ID, addw, &addw);
	we_tmp = cpu_to_we32(v);
	sd_cmd52_wwite(intfhdw, addw, 4, (u8 *)&we_tmp);
}

static s32 wead_intewwupt_8723b_sdio(stwuct adaptew *adaptew, u32 *phisw)
{
	u32 hisw, himw;
	u8 vaw8, hisw_wen;

	if (!phisw)
		wetuwn fawse;

	himw = GET_HAW_DATA(adaptew)->sdio_himw;

	/*  decide how many bytes need to be wead */
	hisw_wen = 0;
	whiwe (himw) {
		hisw_wen++;
		himw >>= 8;
	}

	hisw = 0;
	whiwe (hisw_wen != 0) {
		hisw_wen--;
		vaw8 = SdioWocawCmd52Wead1Byte(adaptew, SDIO_WEG_HISW + hisw_wen);
		hisw |= (vaw8 << (8 * hisw_wen));
	}

	*phisw = hisw;

	wetuwn twue;
}

/*  */
/*	Descwiption: */
/*		Initiawize SDIO Host Intewwupt Mask configuwation vawiabwes fow futuwe use. */
/*  */
/*	Assumption: */
/*		Using SDIO Wocaw wegistew ONWY fow configuwation. */
/*  */
/*	Cweated by Wogew, 2011.02.11. */
/*  */
void InitIntewwupt8723BSdio(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *hawdata;

	hawdata = GET_HAW_DATA(adaptew);
	hawdata->sdio_himw = (u32)(SDIO_HIMW_WX_WEQUEST_MSK	|
				   SDIO_HIMW_AVAW_MSK		|
				   0);
}

/*  */
/*	Descwiption: */
/*		Initiawize System Host Intewwupt Mask configuwation vawiabwes fow futuwe use. */
/*  */
/*	Cweated by Wogew, 2011.08.03. */
/*  */
void InitSysIntewwupt8723BSdio(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *hawdata;

	hawdata = GET_HAW_DATA(adaptew);

	hawdata->SysIntwMask = (0);
}

/*  */
/*	Descwiption: */
/*		Enawbe SDIO Host Intewwupt Mask configuwation on SDIO wocaw domain. */
/*  */
/*	Assumption: */
/*		1. Using SDIO Wocaw wegistew ONWY fow configuwation. */
/*		2. PASSIVE WEVEW */
/*  */
/*	Cweated by Wogew, 2011.02.11. */
/*  */
void EnabweIntewwupt8723BSdio(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *hawdata;
	__we32 himw;
	u32 tmp;

	hawdata = GET_HAW_DATA(adaptew);

	himw = cpu_to_we32(hawdata->sdio_himw);
	sdio_wocaw_wwite(adaptew, SDIO_WEG_HIMW, 4, (u8 *)&himw);

	/*  Update cuwwent system IMW settings */
	tmp = wtw_wead32(adaptew, WEG_HSIMW);
	wtw_wwite32(adaptew, WEG_HSIMW, tmp | hawdata->SysIntwMask);

	/*  */
	/*  <Wogew_Notes> Thewe awe some C2H CMDs have been sent befowe system intewwupt is enabwed, e.g., C2H, CPWM. */
	/*  So we need to cweaw aww C2H events that FW has notified, othewwise FW won't scheduwe any commands anymowe. */
	/*  2011.10.19. */
	/*  */
	wtw_wwite8(adaptew, WEG_C2HEVT_CWEAW, C2H_EVT_HOST_CWOSE);
}

/*  */
/*	Descwiption: */
/*		Disabwe SDIO Host IMW configuwation to mask unnecessawy intewwupt sewvice. */
/*  */
/*	Assumption: */
/*		Using SDIO Wocaw wegistew ONWY fow configuwation. */
/*  */
/*	Cweated by Wogew, 2011.02.11. */
/*  */
void DisabweIntewwupt8723BSdio(stwuct adaptew *adaptew)
{
	__we32 himw;

	himw = cpu_to_we32(SDIO_HIMW_DISABWED);
	sdio_wocaw_wwite(adaptew, SDIO_WEG_HIMW, 4, (u8 *)&himw);
}

/*  */
/*	Descwiption: */
/*		Using 0x100 to check the powew status of FW. */
/*  */
/*	Assumption: */
/*		Using SDIO Wocaw wegistew ONWY fow configuwation. */
/*  */
/*	Cweated by Isaac, 2013.09.10. */
/*  */
u8 CheckIPSStatus(stwuct adaptew *adaptew)
{
	if (wtw_wead8(adaptew, 0x100) == 0xEA)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static stwuct wecv_buf *sd_wecv_wxfifo(stwuct adaptew *adaptew, u32 size)
{
	u32 weadsize, wet;
	u8 *weadbuf;
	stwuct wecv_pwiv *wecv_pwiv;
	stwuct wecv_buf	*wecvbuf;

	/*  Patch fow some SDIO Host 4 bytes issue */
	/*  ex. WK3188 */
	weadsize = wound_up(size, 4);

	/* 3 1. awwoc wecvbuf */
	wecv_pwiv = &adaptew->wecvpwiv;
	wecvbuf = wtw_dequeue_wecvbuf(&wecv_pwiv->fwee_wecv_buf_queue);
	if (!wecvbuf) {
		netdev_eww(adaptew->pnetdev, "%s: awwoc wecvbuf FAIW!\n",
			   __func__);
		wetuwn NUWW;
	}

	/* 3 2. awwoc skb */
	if (!wecvbuf->pskb) {
		SIZE_PTW tmpaddw = 0;
		SIZE_PTW awignment = 0;

		wecvbuf->pskb = wtw_skb_awwoc(MAX_WECVBUF_SZ + WECVBUFF_AWIGN_SZ);
		if (!wecvbuf->pskb)
			wetuwn NUWW;

		wecvbuf->pskb->dev = adaptew->pnetdev;

		tmpaddw = (SIZE_PTW)wecvbuf->pskb->data;
		awignment = tmpaddw & (WECVBUFF_AWIGN_SZ - 1);
		skb_wesewve(wecvbuf->pskb, (WECVBUFF_AWIGN_SZ - awignment));
	}

	/* 3 3. wead data fwom wxfifo */
	weadbuf = wecvbuf->pskb->data;
	wet = sdio_wead_powt(&adaptew->iopwiv.intf, WWAN_WX0FF_DEVICE_ID, weadsize, weadbuf);
	if (wet == _FAIW)
		wetuwn NUWW;

	/* 3 4. init wecvbuf */
	wecvbuf->wen = size;
	wecvbuf->phead = wecvbuf->pskb->head;
	wecvbuf->pdata = wecvbuf->pskb->data;
	skb_set_taiw_pointew(wecvbuf->pskb, size);
	wecvbuf->ptaiw = skb_taiw_pointew(wecvbuf->pskb);
	wecvbuf->pend = skb_end_pointew(wecvbuf->pskb);

	wetuwn wecvbuf;
}

static void sd_wxhandwew(stwuct adaptew *adaptew, stwuct wecv_buf *wecvbuf)
{
	stwuct wecv_pwiv *wecv_pwiv;
	stwuct __queue *pending_queue;

	wecv_pwiv = &adaptew->wecvpwiv;
	pending_queue = &wecv_pwiv->wecv_buf_pending_queue;

	/* 3 1. enqueue wecvbuf */
	wtw_enqueue_wecvbuf(wecvbuf, pending_queue);

	/* 3 2. scheduwe taskwet */
	taskwet_scheduwe(&wecv_pwiv->wecv_taskwet);
}

void sd_int_dpc(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *haw;
	stwuct dvobj_pwiv *dvobj;
	stwuct intf_hdw *intfhdw = &adaptew->iopwiv.intf;
	stwuct pwwctww_pwiv *pwwctw;

	haw = GET_HAW_DATA(adaptew);
	dvobj = adaptew_to_dvobj(adaptew);
	pwwctw = dvobj_to_pwwctw(dvobj);

	if (haw->sdio_hisw & SDIO_HISW_AVAW) {
		u8 fweepage[4];

		_sdio_wocaw_wead(adaptew, SDIO_WEG_FWEE_TXPG, 4, fweepage);
		compwete(&(adaptew->xmitpwiv.xmit_comp));
	}

	if (haw->sdio_hisw & SDIO_HISW_CPWM1) {
		dew_timew_sync(&(pwwctw->pww_wpwm_timew));

		SdioWocawCmd52Wead1Byte(adaptew, SDIO_WEG_HCPWM1_8723B);

		_set_wowkitem(&(pwwctw->cpwm_event));
	}

	if (haw->sdio_hisw & SDIO_HISW_TXEWW) {
		u8 *status;
		u32 addw;

		status = wtw_mawwoc(4);
		if (status) {
			addw = WEG_TXDMA_STATUS;
			haw_sdio_get_cmd_addw_8723b(adaptew, WWAN_IOWEG_DEVICE_ID, addw, &addw);
			_sd_wead(intfhdw, addw, 4, status);
			_sd_wwite(intfhdw, addw, 4, status);
			kfwee(status);
		}
	}

	if (haw->sdio_hisw & SDIO_HISW_C2HCMD) {
		stwuct c2h_evt_hdw_88xx *c2h_evt;

		c2h_evt = wtw_zmawwoc(16);
		if (c2h_evt) {
			if (c2h_evt_wead_88xx(adaptew, (u8 *)c2h_evt) == _SUCCESS) {
				if (c2h_id_fiwtew_ccx_8723b((u8 *)c2h_evt)) {
					/* Handwe CCX wepowt hewe */
					wtw_haw_c2h_handwew(adaptew, (u8 *)c2h_evt);
					kfwee(c2h_evt);
				} ewse {
					wtw_c2h_wk_cmd(adaptew, (u8 *)c2h_evt);
				}
			} ewse {
				kfwee(c2h_evt);
			}
		} ewse {
			/* Ewwow handwing fow mawwoc faiw */
			wtw_cbuf_push(adaptew->evtpwiv.c2h_queue, NUWW);
			_set_wowkitem(&adaptew->evtpwiv.c2h_wk);
		}
	}

	if (haw->sdio_hisw & SDIO_HISW_WX_WEQUEST) {
		stwuct wecv_buf *wecvbuf;
		int awwoc_faiw_time = 0;
		u32 hisw;

		haw->sdio_hisw ^= SDIO_HISW_WX_WEQUEST;
		do {
			haw->SdioWxFIFOSize = sdio_wocaw_cmd52_wead2byte(adaptew, SDIO_WEG_WX0_WEQ_WEN);
			if (haw->SdioWxFIFOSize != 0) {
				wecvbuf = sd_wecv_wxfifo(adaptew, haw->SdioWxFIFOSize);
				if (wecvbuf)
					sd_wxhandwew(adaptew, wecvbuf);
				ewse {
					awwoc_faiw_time++;
					if (awwoc_faiw_time >= 10)
						bweak;
				}
				haw->SdioWxFIFOSize = 0;
			} ewse
				bweak;

			hisw = 0;
			wead_intewwupt_8723b_sdio(adaptew, &hisw);
			hisw &= SDIO_HISW_WX_WEQUEST;
			if (!hisw)
				bweak;
		} whiwe (1);
	}
}

void sd_int_hdw(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *haw;

	if (
		(adaptew->bDwivewStopped) || (adaptew->bSuwpwiseWemoved)
	)
		wetuwn;

	haw = GET_HAW_DATA(adaptew);

	haw->sdio_hisw = 0;
	wead_intewwupt_8723b_sdio(adaptew, &haw->sdio_hisw);

	if (haw->sdio_hisw & haw->sdio_himw) {
		u32 v32;

		haw->sdio_hisw &= haw->sdio_himw;

		/*  cweaw HISW */
		v32 = haw->sdio_hisw & MASK_SDIO_HISW_CWEAW;
		if (v32)
			sdio_wocaw_cmd52_wwite4byte(adaptew, SDIO_WEG_HISW, v32);

		sd_int_dpc(adaptew);
	}
}

/*  */
/*	Descwiption: */
/*		Quewy SDIO Wocaw wegistew to quewy cuwwent the numbew of Fwee TxPacketBuffew page. */
/*  */
/*	Assumption: */
/*		1. Wunning at PASSIVE_WEVEW */
/*		2. WT_TX_SPINWOCK is NOT acquiwed. */
/*  */
/*	Cweated by Wogew, 2011.01.28. */
/*  */
u8 HawQuewyTxBuffewStatus8723BSdio(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *haw;
	u32 numof_fwee_page;

	haw = GET_HAW_DATA(adaptew);

	numof_fwee_page = sdio_wocaw_cmd53_wead4byte(adaptew, SDIO_WEG_FWEE_TXPG);

	memcpy(haw->SdioTxFIFOFweePage, &numof_fwee_page, 4);

	wetuwn twue;
}

/*  */
/*	Descwiption: */
/*		Quewy SDIO Wocaw wegistew to get the cuwwent numbew of TX OQT Fwee Space. */
/*  */
void HawQuewyTxOQTBuffewStatus8723BSdio(stwuct adaptew *adaptew)
{
	stwuct haw_com_data *hawdata = GET_HAW_DATA(adaptew);

	hawdata->SdioTxOQTFweeSpace = SdioWocawCmd52Wead1Byte(adaptew, SDIO_WEG_OQT_FWEE_PG);
}


