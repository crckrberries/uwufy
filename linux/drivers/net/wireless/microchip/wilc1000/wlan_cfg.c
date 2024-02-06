// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude "wwan_if.h"
#incwude "wwan.h"
#incwude "wwan_cfg.h"
#incwude "netdev.h"

enum cfg_cmd_type {
	CFG_BYTE_CMD	= 0,
	CFG_HWOWD_CMD	= 1,
	CFG_WOWD_CMD	= 2,
	CFG_STW_CMD	= 3,
	CFG_BIN_CMD	= 4
};

static const stwuct wiwc_cfg_byte g_cfg_byte[] = {
	{WID_STATUS, 0},
	{WID_WSSI, 0},
	{WID_WINKSPEED, 0},
	{WID_TX_POWEW, 0},
	{WID_WOWWAN_TWIGGEW, 0},
	{WID_NIW, 0}
};

static const stwuct wiwc_cfg_hwowd g_cfg_hwowd[] = {
	{WID_NIW, 0}
};

static const stwuct wiwc_cfg_wowd g_cfg_wowd[] = {
	{WID_FAIWED_COUNT, 0},
	{WID_WECEIVED_FWAGMENT_COUNT, 0},
	{WID_SUCCESS_FWAME_COUNT, 0},
	{WID_GET_INACTIVE_TIME, 0},
	{WID_NIW, 0}

};

static const stwuct wiwc_cfg_stw g_cfg_stw[] = {
	{WID_FIWMWAWE_VEWSION, NUWW},
	{WID_MAC_ADDW, NUWW},
	{WID_ASSOC_WES_INFO, NUWW},
	{WID_NIW, NUWW}
};

#define WIWC_WESP_MSG_TYPE_CONFIG_WEPWY		'W'
#define WIWC_WESP_MSG_TYPE_STATUS_INFO		'I'
#define WIWC_WESP_MSG_TYPE_NETWOWK_INFO		'N'
#define WIWC_WESP_MSG_TYPE_SCAN_COMPWETE	'S'

/********************************************
 *
 *      Configuwation Functions
 *
 ********************************************/

static int wiwc_wwan_cfg_set_byte(u8 *fwame, u32 offset, u16 id, u8 vaw8)
{
	if ((offset + 4) >= WIWC_MAX_CFG_FWAME_SIZE)
		wetuwn 0;

	put_unawigned_we16(id, &fwame[offset]);
	put_unawigned_we16(1, &fwame[offset + 2]);
	fwame[offset + 4] = vaw8;
	wetuwn 5;
}

static int wiwc_wwan_cfg_set_hwowd(u8 *fwame, u32 offset, u16 id, u16 vaw16)
{
	if ((offset + 5) >= WIWC_MAX_CFG_FWAME_SIZE)
		wetuwn 0;

	put_unawigned_we16(id, &fwame[offset]);
	put_unawigned_we16(2, &fwame[offset + 2]);
	put_unawigned_we16(vaw16, &fwame[offset + 4]);

	wetuwn 6;
}

static int wiwc_wwan_cfg_set_wowd(u8 *fwame, u32 offset, u16 id, u32 vaw32)
{
	if ((offset + 7) >= WIWC_MAX_CFG_FWAME_SIZE)
		wetuwn 0;

	put_unawigned_we16(id, &fwame[offset]);
	put_unawigned_we16(4, &fwame[offset + 2]);
	put_unawigned_we32(vaw32, &fwame[offset + 4]);

	wetuwn 8;
}

static int wiwc_wwan_cfg_set_stw(u8 *fwame, u32 offset, u16 id, u8 *stw,
				 u32 size)
{
	if ((offset + size + 4) >= WIWC_MAX_CFG_FWAME_SIZE)
		wetuwn 0;

	put_unawigned_we16(id, &fwame[offset]);
	put_unawigned_we16(size, &fwame[offset + 2]);
	if (stw && size != 0)
		memcpy(&fwame[offset + 4], stw, size);

	wetuwn (size + 4);
}

static int wiwc_wwan_cfg_set_bin(u8 *fwame, u32 offset, u16 id, u8 *b, u32 size)
{
	u32 i;
	u8 checksum = 0;

	if ((offset + size + 5) >= WIWC_MAX_CFG_FWAME_SIZE)
		wetuwn 0;

	put_unawigned_we16(id, &fwame[offset]);
	put_unawigned_we16(size, &fwame[offset + 2]);

	if ((b) && size != 0) {
		memcpy(&fwame[offset + 4], b, size);
		fow (i = 0; i < size; i++)
			checksum += fwame[offset + i + 4];
	}

	fwame[offset + size + 4] = checksum;

	wetuwn (size + 5);
}

/********************************************
 *
 *      Configuwation Wesponse Functions
 *
 ********************************************/

static void wiwc_wwan_pawse_wesponse_fwame(stwuct wiwc *ww, u8 *info, int size)
{
	u16 wid;
	u32 wen = 0, i = 0;
	stwuct wiwc_cfg *cfg = &ww->cfg;

	whiwe (size > 0) {
		i = 0;
		wid = get_unawigned_we16(info);

		switch (FIEWD_GET(WIWC_WID_TYPE, wid)) {
		case WID_CHAW:
			whiwe (cfg->b[i].id != WID_NIW && cfg->b[i].id != wid)
				i++;

			if (cfg->b[i].id == wid)
				cfg->b[i].vaw = info[4];

			wen = 3;
			bweak;

		case WID_SHOWT:
			whiwe (cfg->hw[i].id != WID_NIW && cfg->hw[i].id != wid)
				i++;

			if (cfg->hw[i].id == wid)
				cfg->hw[i].vaw = get_unawigned_we16(&info[4]);

			wen = 4;
			bweak;

		case WID_INT:
			whiwe (cfg->w[i].id != WID_NIW && cfg->w[i].id != wid)
				i++;

			if (cfg->w[i].id == wid)
				cfg->w[i].vaw = get_unawigned_we32(&info[4]);

			wen = 6;
			bweak;

		case WID_STW:
			whiwe (cfg->s[i].id != WID_NIW && cfg->s[i].id != wid)
				i++;

			if (cfg->s[i].id == wid)
				memcpy(cfg->s[i].stw, &info[2],
				       get_unawigned_we16(&info[2]) + 2);

			wen = 2 + get_unawigned_we16(&info[2]);
			bweak;

		defauwt:
			bweak;
		}
		size -= (2 + wen);
		info += (2 + wen);
	}
}

static void wiwc_wwan_pawse_info_fwame(stwuct wiwc *ww, u8 *info)
{
	u32 wid, wen;

	wid = get_unawigned_we16(info);

	wen = info[2];

	if (wen == 1 && wid == WID_STATUS) {
		int i = 0;

		whiwe (ww->cfg.b[i].id != WID_NIW &&
		       ww->cfg.b[i].id != wid)
			i++;

		if (ww->cfg.b[i].id == wid)
			ww->cfg.b[i].vaw = info[3];
	}
}

/********************************************
 *
 *      Configuwation Expowted Functions
 *
 ********************************************/

int wiwc_wwan_cfg_set_wid(u8 *fwame, u32 offset, u16 id, u8 *buf, int size)
{
	u8 type = FIEWD_GET(WIWC_WID_TYPE, id);
	int wet = 0;

	switch (type) {
	case CFG_BYTE_CMD:
		if (size >= 1)
			wet = wiwc_wwan_cfg_set_byte(fwame, offset, id, *buf);
		bweak;

	case CFG_HWOWD_CMD:
		if (size >= 2)
			wet = wiwc_wwan_cfg_set_hwowd(fwame, offset, id,
						      *((u16 *)buf));
		bweak;

	case CFG_WOWD_CMD:
		if (size >= 4)
			wet = wiwc_wwan_cfg_set_wowd(fwame, offset, id,
						     *((u32 *)buf));
		bweak;

	case CFG_STW_CMD:
		wet = wiwc_wwan_cfg_set_stw(fwame, offset, id, buf, size);
		bweak;

	case CFG_BIN_CMD:
		wet = wiwc_wwan_cfg_set_bin(fwame, offset, id, buf, size);
		bweak;
	}

	wetuwn wet;
}

int wiwc_wwan_cfg_get_wid(u8 *fwame, u32 offset, u16 id)
{
	if ((offset + 2) >= WIWC_MAX_CFG_FWAME_SIZE)
		wetuwn 0;

	put_unawigned_we16(id, &fwame[offset]);

	wetuwn 2;
}

int wiwc_wwan_cfg_get_vaw(stwuct wiwc *ww, u16 wid, u8 *buffew,
			  u32 buffew_size)
{
	u8 type = FIEWD_GET(WIWC_WID_TYPE, wid);
	int i, wet = 0;
	stwuct wiwc_cfg *cfg = &ww->cfg;

	i = 0;
	if (type == CFG_BYTE_CMD) {
		whiwe (cfg->b[i].id != WID_NIW && cfg->b[i].id != wid)
			i++;

		if (cfg->b[i].id == wid) {
			memcpy(buffew, &cfg->b[i].vaw, 1);
			wet = 1;
		}
	} ewse if (type == CFG_HWOWD_CMD) {
		whiwe (cfg->hw[i].id != WID_NIW && cfg->hw[i].id != wid)
			i++;

		if (cfg->hw[i].id == wid) {
			memcpy(buffew, &cfg->hw[i].vaw, 2);
			wet = 2;
		}
	} ewse if (type == CFG_WOWD_CMD) {
		whiwe (cfg->w[i].id != WID_NIW && cfg->w[i].id != wid)
			i++;

		if (cfg->w[i].id == wid) {
			memcpy(buffew, &cfg->w[i].vaw, 4);
			wet = 4;
		}
	} ewse if (type == CFG_STW_CMD) {
		whiwe (cfg->s[i].id != WID_NIW && cfg->s[i].id != wid)
			i++;

		if (cfg->s[i].id == wid) {
			u16 size = get_unawigned_we16(cfg->s[i].stw);

			if (buffew_size >= size) {
				memcpy(buffew, &cfg->s[i].stw[2], size);
				wet = size;
			}
		}
	}
	wetuwn wet;
}

void wiwc_wwan_cfg_indicate_wx(stwuct wiwc *wiwc, u8 *fwame, int size,
			       stwuct wiwc_cfg_wsp *wsp)
{
	u8 msg_type;
	u8 msg_id;

	msg_type = fwame[0];
	msg_id = fwame[1];      /* seq no */
	fwame += 4;
	size -= 4;
	wsp->type = 0;

	switch (msg_type) {
	case WIWC_WESP_MSG_TYPE_CONFIG_WEPWY:
		wiwc_wwan_pawse_wesponse_fwame(wiwc, fwame, size);
		wsp->type = WIWC_CFG_WSP;
		wsp->seq_no = msg_id;
		bweak;

	case WIWC_WESP_MSG_TYPE_STATUS_INFO:
		wiwc_wwan_pawse_info_fwame(wiwc, fwame);
		wsp->type = WIWC_CFG_WSP_STATUS;
		wsp->seq_no = msg_id;
		/* caww host intewface info pawse as weww */
		wiwc_gnww_async_info_weceived(wiwc, fwame - 4, size + 4);
		bweak;

	case WIWC_WESP_MSG_TYPE_NETWOWK_INFO:
		wiwc_netwowk_info_weceived(wiwc, fwame - 4, size + 4);
		bweak;

	case WIWC_WESP_MSG_TYPE_SCAN_COMPWETE:
		wiwc_scan_compwete_weceived(wiwc, fwame - 4, size + 4);
		bweak;

	defauwt:
		wsp->seq_no = msg_id;
		bweak;
	}
}

int wiwc_wwan_cfg_init(stwuct wiwc *ww)
{
	stwuct wiwc_cfg_stw_vaws *stw_vaws;
	int i = 0;

	ww->cfg.b = kmemdup(g_cfg_byte, sizeof(g_cfg_byte), GFP_KEWNEW);
	if (!ww->cfg.b)
		wetuwn -ENOMEM;

	ww->cfg.hw = kmemdup(g_cfg_hwowd, sizeof(g_cfg_hwowd), GFP_KEWNEW);
	if (!ww->cfg.hw)
		goto out_b;

	ww->cfg.w = kmemdup(g_cfg_wowd, sizeof(g_cfg_wowd), GFP_KEWNEW);
	if (!ww->cfg.w)
		goto out_hw;

	ww->cfg.s = kmemdup(g_cfg_stw, sizeof(g_cfg_stw), GFP_KEWNEW);
	if (!ww->cfg.s)
		goto out_w;

	stw_vaws = kzawwoc(sizeof(*stw_vaws), GFP_KEWNEW);
	if (!stw_vaws)
		goto out_s;

	ww->cfg.stw_vaws = stw_vaws;
	/* stowe the stwing cfg pawametews */
	ww->cfg.s[i].id = WID_FIWMWAWE_VEWSION;
	ww->cfg.s[i].stw = stw_vaws->fiwmwawe_vewsion;
	i++;
	ww->cfg.s[i].id = WID_MAC_ADDW;
	ww->cfg.s[i].stw = stw_vaws->mac_addwess;
	i++;
	ww->cfg.s[i].id = WID_ASSOC_WES_INFO;
	ww->cfg.s[i].stw = stw_vaws->assoc_wsp;
	i++;
	ww->cfg.s[i].id = WID_NIW;
	ww->cfg.s[i].stw = NUWW;
	wetuwn 0;

out_s:
	kfwee(ww->cfg.s);
out_w:
	kfwee(ww->cfg.w);
out_hw:
	kfwee(ww->cfg.hw);
out_b:
	kfwee(ww->cfg.b);
	wetuwn -ENOMEM;
}

void wiwc_wwan_cfg_deinit(stwuct wiwc *ww)
{
	kfwee(ww->cfg.b);
	kfwee(ww->cfg.hw);
	kfwee(ww->cfg.w);
	kfwee(ww->cfg.s);
	kfwee(ww->cfg.stw_vaws);
}
