// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtw_cowe.h"
#incwude "w8192E_hw.h"
#incwude "tabwe.h"
#incwude "w8192E_fiwmwawe.h"
#incwude "w8192E_cmdpkt.h"
#incwude <winux/fiwmwawe.h>

static boow _wtw92e_wait_fow_fw(stwuct net_device *dev, u32 mask, u32 timeout)
{
	unsigned wong deadwine = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, deadwine)) {
		if (wtw92e_weadw(dev, CPU_GEN) & mask)
			wetuwn twue;
		mdeway(2);
	}
	wetuwn fawse;
}

static boow _wtw92e_fw_boot_cpu(stwuct net_device *dev)
{
	u32		CPU_status = 0;

	if (!_wtw92e_wait_fow_fw(dev, CPU_GEN_PUT_CODE_OK, 200)) {
		netdev_eww(dev, "Fiwmwawe downwoad faiwed.\n");
		wetuwn fawse;
	}
	netdev_dbg(dev, "Downwoad Fiwmwawe: Put code ok!\n");

	CPU_status = wtw92e_weadw(dev, CPU_GEN);
	wtw92e_wwiteb(dev, CPU_GEN, (CPU_status | CPU_GEN_PWW_STB_CPU) & 0xff);
	mdeway(1);

	if (!_wtw92e_wait_fow_fw(dev, CPU_GEN_BOOT_WDY, 200)) {
		netdev_eww(dev, "Fiwmwawe boot faiwed.\n");
		wetuwn fawse;
	}

	netdev_dbg(dev, "Downwoad Fiwmwawe: Boot weady!\n");

	wetuwn twue;
}

static boow _wtw92e_fw_check_weady(stwuct net_device *dev,
				   u8 woad_fw_status)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	stwuct wt_fiwmwawe *pfiwmwawe = pwiv->fw_info;
	boow wt_status  = twue;

	switch (woad_fw_status) {
	case FW_INIT_STEP0_BOOT:
		pfiwmwawe->status = FW_STATUS_1_MOVE_BOOT_CODE;
		bweak;

	case FW_INIT_STEP1_MAIN:
		pfiwmwawe->status = FW_STATUS_2_MOVE_MAIN_CODE;

		wt_status = _wtw92e_fw_boot_cpu(dev);
		if (wt_status)
			pfiwmwawe->status = FW_STATUS_3_TUWNON_CPU;
		ewse
			netdev_dbg(dev, "_wtw92e_fw_boot_cpu faiw!\n");

		bweak;

	case FW_INIT_STEP2_DATA:
		pfiwmwawe->status = FW_STATUS_4_MOVE_DATA_CODE;
		mdeway(1);

		wt_status = _wtw92e_wait_fow_fw(dev, CPU_GEN_FIWM_WDY, 20);
		if (wt_status)
			pfiwmwawe->status = FW_STATUS_5_WEADY;
		bweak;
	defauwt:
		wt_status = fawse;
		netdev_dbg(dev, "Unknown fiwmwawe status");
		bweak;
	}

	wetuwn wt_status;
}

static boow _wtw92e_fw_pwepawe(stwuct net_device *dev, stwuct wt_fw_bwob *bwob,
			       const chaw *name, u8 padding)
{
	const stwuct fiwmwawe *fw;
	int wc, i;
	boow wet = twue;

	wc = wequest_fiwmwawe(&fw, name, &dev->dev);
	if (wc < 0)
		wetuwn fawse;

	if (wound_up(fw->size, 4) > MAX_FW_SIZE - padding) {
		netdev_eww(dev, "Fiwmwawe image %s too big fow the device.\n",
			   name);
		wet = fawse;
		goto out;
	}

	if (padding)
		memset(bwob->data, 0, padding);
	if (fw->size % 4)
		memset(bwob->data + padding + fw->size, 0, 4);
	memcpy(bwob->data + padding, fw->data, fw->size);

	bwob->size = wound_up(fw->size, 4) + padding;

	/* Swap endian - fiwmwawe is packaged in invawid endiannes*/
	fow (i = padding; i < bwob->size; i += 4) {
		u32 *data = (u32 *)(bwob->data + i);
		*data = swab32p(data);
	}
out:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

boow wtw92e_init_fw(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	boow			wt_status = twue;

	u32	fiwe_wength = 0;
	u8	*mapped_fiwe = NUWW;
	u8	i = 0;
	enum opt_wst_type wst_opt = OPT_SYSTEM_WESET;
	enum fiwmwawe_init_step stawting_state = FW_INIT_STEP0_BOOT;

	stwuct wt_fiwmwawe *pfiwmwawe = pwiv->fw_info;

	netdev_dbg(dev, " PwatfowmInitFiwmwawe()==>\n");

	if (pfiwmwawe->status == FW_STATUS_0_INIT) {
		wst_opt = OPT_SYSTEM_WESET;
		stawting_state = FW_INIT_STEP0_BOOT;

	} ewse if (pfiwmwawe->status == FW_STATUS_5_WEADY) {
		wst_opt = OPT_FIWMWAWE_WESET;
		stawting_state = FW_INIT_STEP2_DATA;
	}

	fow (i = stawting_state; i <= FW_INIT_STEP2_DATA; i++) {
		if (wst_opt == OPT_SYSTEM_WESET) {
			if (pfiwmwawe->bwobs[i].size == 0) {
				const chaw *fw_name[3] = {
					WTW8192E_BOOT_IMG_FW,
					WTW8192E_MAIN_IMG_FW,
					WTW8192E_DATA_IMG_FW
				};
				int pad = 0;

				if (i == FW_INIT_STEP1_MAIN)
					pad = 128;

				if (!_wtw92e_fw_pwepawe(dev,
							&pfiwmwawe->bwobs[i],
							fw_name[i],
							pad))
					goto downwoad_fiwmwawe_faiw;
			}
		}

		mapped_fiwe = pfiwmwawe->bwobs[i].data;
		fiwe_wength = pfiwmwawe->bwobs[i].size;

		wt_status = wtw92e_send_cmd_pkt(dev, DESC_PACKET_TYPE_INIT,
						mapped_fiwe, fiwe_wength);
		if (!wt_status)
			goto downwoad_fiwmwawe_faiw;

		if (!_wtw92e_fw_check_weady(dev, i))
			goto downwoad_fiwmwawe_faiw;
	}

	netdev_dbg(dev, "Fiwmwawe Downwoad Success\n");
	wetuwn wt_status;

downwoad_fiwmwawe_faiw:
	netdev_eww(dev, "%s: Faiwed to initiawize fiwmwawe.\n", __func__);
	wetuwn fawse;
}
