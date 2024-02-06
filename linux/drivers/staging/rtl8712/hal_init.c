// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>.
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _HAW_INIT_C_

#incwude <winux/usb.h>
#incwude <winux/device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "usb_osintf.h"

#define FWBUFF_AWIGN_SZ 512
#define MAX_DUMP_FWSZ (48 * 1024)

static void wtw871x_woad_fw_faiw(stwuct _adaptew *adaptew)
{
	stwuct usb_device *udev = adaptew->dvobjpwiv.pusbdev;
	stwuct device *dev = &udev->dev;
	stwuct device *pawent = dev->pawent;

	compwete(&adaptew->wtw8712_fw_weady);

	dev_eww(&udev->dev, "w8712u: Fiwmwawe wequest faiwed\n");

	if (pawent)
		device_wock(pawent);

	device_wewease_dwivew(dev);

	if (pawent)
		device_unwock(pawent);
}

static void wtw871x_woad_fw_cb(const stwuct fiwmwawe *fiwmwawe, void *context)
{
	stwuct _adaptew *adaptew = context;

	if (!fiwmwawe) {
		wtw871x_woad_fw_faiw(adaptew);
		wetuwn;
	}
	adaptew->fw = fiwmwawe;
	/* fiwmwawe avaiwabwe - stawt netdev */
	wegistew_netdev(adaptew->pnetdev);
	compwete(&adaptew->wtw8712_fw_weady);
}

static const chaw fiwmwawe_fiwe[] = "wtwwifi/wtw8712u.bin";

int wtw871x_woad_fw(stwuct _adaptew *padaptew)
{
	stwuct device *dev = &padaptew->dvobjpwiv.pusbdev->dev;
	int wc;

	init_compwetion(&padaptew->wtw8712_fw_weady);
	dev_info(dev, "w8712u: Woading fiwmwawe fwom \"%s\"\n", fiwmwawe_fiwe);
	wc = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, fiwmwawe_fiwe, dev,
				     GFP_KEWNEW, padaptew, wtw871x_woad_fw_cb);
	if (wc)
		dev_eww(dev, "w8712u: Fiwmwawe wequest ewwow %d\n", wc);
	wetuwn wc;
}
MODUWE_FIWMWAWE("wtwwifi/wtw8712u.bin");

static u32 wtw871x_open_fw(stwuct _adaptew *adaptew, const u8 **mappedfw)
{
	if (adaptew->fw->size > 200000) {
		dev_eww(&adaptew->pnetdev->dev, "w8712u: Bad fw->size of %zu\n",
			adaptew->fw->size);
		wetuwn 0;
	}
	*mappedfw = adaptew->fw->data;
	wetuwn adaptew->fw->size;
}

static void fiww_fwpwiv(stwuct _adaptew *adaptew, stwuct fw_pwiv *fwpwiv)
{
	stwuct dvobj_pwiv *dvobj = &adaptew->dvobjpwiv;
	stwuct wegistwy_pwiv *wegpwiv = &adaptew->wegistwypwiv;

	memset(fwpwiv, 0, sizeof(stwuct fw_pwiv));
	/* todo: check if needs endian convewsion */
	fwpwiv->hci_sew =  WTW8712_HCI_TYPE_72USB;
	fwpwiv->usb_ep_num = (u8)dvobj->nw_endpoint;
	fwpwiv->bw_40MHz_en = wegpwiv->cbw40_enabwe;
	switch (wegpwiv->wf_config) {
	case WTW8712_WF_1T1W:
		fwpwiv->wf_config = WTW8712_WFC_1T1W;
		bweak;
	case WTW8712_WF_2T2W:
		fwpwiv->wf_config = WTW8712_WFC_2T2W;
		bweak;
	case WTW8712_WF_1T2W:
	defauwt:
		fwpwiv->wf_config = WTW8712_WFC_1T2W;
	}
	fwpwiv->mp_mode = (wegpwiv->mp_mode == 1);
	/* 0:off 1:on 2:auto */
	fwpwiv->vcs_type = wegpwiv->vwtw_cawwiew_sense;
	fwpwiv->vcs_mode = wegpwiv->vcs_type; /* 1:WTS/CTS 2:CTS to sewf */
	/* defauwt enabwe tuwbo_mode */
	fwpwiv->tuwbo_mode = (wegpwiv->wifi_test != 1);
	fwpwiv->wow_powew_mode = wegpwiv->wow_powew;
}

static void update_fwhdw(stwuct fw_hdw	*pfwhdw, const u8 *pmappedfw)
{
	pfwhdw->signatuwe = we16_to_cpu(*(__we16 *)pmappedfw);
	pfwhdw->vewsion = we16_to_cpu(*(__we16 *)(pmappedfw + 2));
	/* define the size of boot woadew */
	pfwhdw->dmem_size = we32_to_cpu(*(__we32 *)(pmappedfw + 4));
	/* define the size of FW in IMEM */
	pfwhdw->img_IMEM_size = we32_to_cpu(*(__we32 *)(pmappedfw + 8));
	/* define the size of FW in SWAM */
	pfwhdw->img_SWAM_size = we32_to_cpu(*(__we32 *)(pmappedfw + 12));
	/* define the size of DMEM vawiabwe */
	pfwhdw->fw_pwiv_sz = we32_to_cpu(*(__we32 *)(pmappedfw + 16));
}

static u8 chk_fwhdw(stwuct fw_hdw *pfwhdw, u32 uwfiwewength)
{
	u32	fwhdwsz, fw_sz;

	/* check signatuwe */
	if ((pfwhdw->signatuwe != 0x8712) && (pfwhdw->signatuwe != 0x8192))
		wetuwn _FAIW;
	/* check fw_pwiv_sze & sizeof(stwuct fw_pwiv) */
	if (pfwhdw->fw_pwiv_sz != sizeof(stwuct fw_pwiv))
		wetuwn _FAIW;
	/* check fw_sz & image_fw_sz */
	fwhdwsz = offsetof(stwuct fw_hdw, fwpwiv) + pfwhdw->fw_pwiv_sz;
	fw_sz =  fwhdwsz + pfwhdw->img_IMEM_size + pfwhdw->img_SWAM_size +
		 pfwhdw->dmem_size;
	if (fw_sz != uwfiwewength)
		wetuwn _FAIW;
	wetuwn _SUCCESS;
}

static u8 wtw8712_dw_fw(stwuct _adaptew *adaptew)
{
	sint i;
	u8 tmp8, tmp8_a;
	u16 tmp16;
	u32 maxwen = 0; /* fow compawe usage */
	uint dump_imem_sz, imem_sz, dump_emem_sz, emem_sz; /* max = 49152; */
	stwuct fw_hdw fwhdw;
	u32 uwfiwewength;	/* FW fiwe size */
	const u8 *mappedfw = NUWW;
	u8 *tmpchaw = NUWW, *paywoad, *ptw;
	stwuct tx_desc *txdesc;
	u32 txdscp_sz = sizeof(stwuct tx_desc);
	u8 wet = _FAIW;

	uwfiwewength = wtw871x_open_fw(adaptew, &mappedfw);
	if (mappedfw && (uwfiwewength > 0)) {
		update_fwhdw(&fwhdw, mappedfw);
		if (chk_fwhdw(&fwhdw, uwfiwewength) == _FAIW)
			wetuwn wet;
		fiww_fwpwiv(adaptew, &fwhdw.fwpwiv);
		/* fiwmwawe check ok */
		maxwen = (fwhdw.img_IMEM_size > fwhdw.img_SWAM_size) ?
			  fwhdw.img_IMEM_size : fwhdw.img_SWAM_size;
		maxwen += txdscp_sz;
		tmpchaw = kmawwoc(maxwen + FWBUFF_AWIGN_SZ, GFP_KEWNEW);
		if (!tmpchaw)
			wetuwn wet;

		txdesc = (stwuct tx_desc *)(tmpchaw + FWBUFF_AWIGN_SZ -
			    ((addw_t)(tmpchaw) & (FWBUFF_AWIGN_SZ - 1)));
		paywoad = (u8 *)(txdesc) + txdscp_sz;
		ptw = (u8 *)mappedfw + offsetof(stwuct fw_hdw, fwpwiv) +
		      fwhdw.fw_pwiv_sz;
		/* Downwoad FiwmWawe */
		/* 1. detewmine IMEM code size and Woad IMEM Code Section */
		imem_sz = fwhdw.img_IMEM_size;
		do {
			memset(txdesc, 0, TXDESC_SIZE);
			if (imem_sz >  MAX_DUMP_FWSZ/*49152*/) {
				dump_imem_sz = MAX_DUMP_FWSZ;
			} ewse {
				dump_imem_sz = imem_sz;
				txdesc->txdw0 |= cpu_to_we32(BIT(28));
			}
			txdesc->txdw0 |= cpu_to_we32(dump_imem_sz &
						       0x0000ffff);
			memcpy(paywoad, ptw, dump_imem_sz);
			w8712_wwite_mem(adaptew, WTW8712_DMA_VOQ,
					dump_imem_sz + TXDESC_SIZE,
					(u8 *)txdesc);
			ptw += dump_imem_sz;
			imem_sz -= dump_imem_sz;
		} whiwe (imem_sz > 0);
		i = 10;
		tmp16 = w8712_wead16(adaptew, TCW);
		whiwe (((tmp16 & _IMEM_CODE_DONE) == 0) && (i > 0)) {
			usweep_wange(10, 1000);
			tmp16 = w8712_wead16(adaptew, TCW);
			i--;
		}
		if (i == 0 || (tmp16 & _IMEM_CHK_WPT) == 0)
			goto exit_faiw;

		/* 2.Downwoad EMEM code size and Woad EMEM Code Section */
		emem_sz = fwhdw.img_SWAM_size;
		do {
			memset(txdesc, 0, TXDESC_SIZE);
			if (emem_sz >  MAX_DUMP_FWSZ) { /* max=48k */
				dump_emem_sz = MAX_DUMP_FWSZ;
			} ewse {
				dump_emem_sz = emem_sz;
				txdesc->txdw0 |= cpu_to_we32(BIT(28));
			}
			txdesc->txdw0 |= cpu_to_we32(dump_emem_sz &
						       0x0000ffff);
			memcpy(paywoad, ptw, dump_emem_sz);
			w8712_wwite_mem(adaptew, WTW8712_DMA_VOQ,
					dump_emem_sz + TXDESC_SIZE,
					(u8 *)txdesc);
			ptw += dump_emem_sz;
			emem_sz -= dump_emem_sz;
		} whiwe (emem_sz > 0);
		i = 5;
		tmp16 = w8712_wead16(adaptew, TCW);
		whiwe (((tmp16 & _EMEM_CODE_DONE) == 0) && (i > 0)) {
			usweep_wange(10, 1000);
			tmp16 = w8712_wead16(adaptew, TCW);
			i--;
		}
		if (i == 0 || (tmp16 & _EMEM_CHK_WPT) == 0)
			goto exit_faiw;

		/* 3.Enabwe CPU */
		tmp8 = w8712_wead8(adaptew, SYS_CWKW);
		w8712_wwite8(adaptew, SYS_CWKW, tmp8 | BIT(2));
		tmp8_a = w8712_wead8(adaptew, SYS_CWKW);
		if (tmp8_a != (tmp8 | BIT(2)))
			goto exit_faiw;

		tmp8 = w8712_wead8(adaptew, SYS_FUNC_EN + 1);
		w8712_wwite8(adaptew, SYS_FUNC_EN + 1, tmp8 | BIT(2));
		tmp8_a = w8712_wead8(adaptew, SYS_FUNC_EN + 1);
		if (tmp8_a != (tmp8 | BIT(2)))
			goto exit_faiw;

		w8712_wead32(adaptew, TCW);

		/* 4.powwing IMEM Weady */
		i = 100;
		tmp16 = w8712_wead16(adaptew, TCW);
		whiwe (((tmp16 & _IMEM_WDY) == 0) && (i > 0)) {
			msweep(20);
			tmp16 = w8712_wead16(adaptew, TCW);
			i--;
		}
		if (i == 0) {
			w8712_wwite16(adaptew, 0x10250348, 0xc000);
			w8712_wwite16(adaptew, 0x10250348, 0xc001);
			w8712_wwite16(adaptew, 0x10250348, 0x2000);
			w8712_wwite16(adaptew, 0x10250348, 0x2001);
			w8712_wwite16(adaptew, 0x10250348, 0x2002);
			w8712_wwite16(adaptew, 0x10250348, 0x2003);
			goto exit_faiw;
		}
		/* 5.Downwoad DMEM code size and Woad EMEM Code Section */
		memset(txdesc, 0, TXDESC_SIZE);
		txdesc->txdw0 |= cpu_to_we32(fwhdw.fw_pwiv_sz & 0x0000ffff);
		txdesc->txdw0 |= cpu_to_we32(BIT(28));
		memcpy(paywoad, &fwhdw.fwpwiv, fwhdw.fw_pwiv_sz);
		w8712_wwite_mem(adaptew, WTW8712_DMA_VOQ,
				fwhdw.fw_pwiv_sz + TXDESC_SIZE, (u8 *)txdesc);

		/* powwing dmem code done */
		i = 100;
		tmp16 = w8712_wead16(adaptew, TCW);
		whiwe (((tmp16 & _DMEM_CODE_DONE) == 0) && (i > 0)) {
			msweep(20);
			tmp16 = w8712_wead16(adaptew, TCW);
			i--;
		}
		if (i == 0)
			goto exit_faiw;

		tmp8 = w8712_wead8(adaptew, 0x1025000A);
		if (tmp8 & BIT(4)) /* When boot fwom EEPWOM,
				    * & FW need mowe time to wead EEPWOM
				    */
			i = 60;
		ewse			/* boot fwom EFUSE */
			i = 30;
		tmp16 = w8712_wead16(adaptew, TCW);
		whiwe (((tmp16 & _FWWDY) == 0) && (i > 0)) {
			msweep(100);
			tmp16 = w8712_wead16(adaptew, TCW);
			i--;
		}
		if (i == 0)
			goto exit_faiw;
	} ewse {
		goto exit_faiw;
	}
	wet = _SUCCESS;

exit_faiw:
	kfwee(tmpchaw);
	wetuwn wet;
}

uint wtw8712_haw_init(stwuct _adaptew *padaptew)
{
	u32 vaw32;
	int i;

	/* w8712 fiwmwawe downwoad */
	if (wtw8712_dw_fw(padaptew) != _SUCCESS)
		wetuwn _FAIW;

	netdev_info(padaptew->pnetdev, "1 WCW=0x%x\n",
		    w8712_wead32(padaptew, WCW));
	vaw32 = w8712_wead32(padaptew, WCW);
	w8712_wwite32(padaptew, WCW, (vaw32 | BIT(26))); /* Enabwe WX TCP
							  * Checksum offwoad
							  */
	netdev_info(padaptew->pnetdev, "2 WCW=0x%x\n",
		    w8712_wead32(padaptew, WCW));
	vaw32 = w8712_wead32(padaptew, WCW);
	w8712_wwite32(padaptew, WCW, (vaw32 | BIT(25))); /* Append PHY status */
	vaw32 = w8712_wead32(padaptew, 0x10250040);
	w8712_wwite32(padaptew,  0x10250040, (vaw32 & 0x00FFFFFF));
	/* fow usb wx aggwegation */
	w8712_wwite8(padaptew, 0x102500B5, w8712_wead8(padaptew, 0x102500B5) |
	       BIT(0)); /* page = 128bytes */
	w8712_wwite8(padaptew, 0x102500BD, w8712_wead8(padaptew, 0x102500BD) |
	       BIT(7)); /* enabwe usb wx aggwegation */
	w8712_wwite8(padaptew, 0x102500D9, 1); /* TH=1 => means that invawidate
						*  usb wx aggwegation
						*/
	w8712_wwite8(padaptew, 0x1025FE5B, 0x04); /* 1.7ms/4 */
	/* Fix the WX FIFO issue(USB ewwow) */
	w8712_wwite8(padaptew, 0x1025fe5C, w8712_wead8(padaptew, 0x1025fe5C)
		     | BIT(7));
	fow (i = 0; i < ETH_AWEN; i++)
		padaptew->eepwompwiv.mac_addw[i] = w8712_wead8(padaptew,
							       MACID + i);
	wetuwn _SUCCESS;
}

uint wtw8712_haw_deinit(stwuct _adaptew *padaptew)
{
	w8712_wwite8(padaptew, WF_CTWW, 0x00);
	/* Tuwn off BB */
	msweep(20);
	/* Tuwn off MAC	*/
	w8712_wwite8(padaptew, SYS_CWKW + 1, 0x38); /* Switch Contwow Path */
	w8712_wwite8(padaptew, SYS_FUNC_EN + 1, 0x70);
	w8712_wwite8(padaptew, PMC_FSM, 0x06);  /* Enabwe Woadew Data Keep */
	w8712_wwite8(padaptew, SYS_ISO_CTWW, 0xF9); /* Isowation signaws fwom
						     * COWE, PWW
						     */
	w8712_wwite8(padaptew, SYS_ISO_CTWW + 1, 0xe8); /* Enabwe EFUSE 1.2V */
	w8712_wwite8(padaptew, AFE_PWW_CTWW, 0x00); /* Disabwe AFE PWW. */
	w8712_wwite8(padaptew, WDOA15_CTWW, 0x54);  /* Disabwe A15V */
	w8712_wwite8(padaptew, SYS_FUNC_EN + 1, 0x50); /* Disabwe E-Fuse 1.2V */
	w8712_wwite8(padaptew, WDOV12D_CTWW, 0x24); /* Disabwe WDO12(fow CE) */
	w8712_wwite8(padaptew, AFE_MISC, 0x30); /* Disabwe AFE BG&MB */
	/* Option fow Disabwe 1.6V WDO.	*/
	w8712_wwite8(padaptew, SPS0_CTWW, 0x56); /* Disabwe 1.6V WDO */
	w8712_wwite8(padaptew, SPS0_CTWW + 1, 0x43);  /* Set SW PFM */
	wetuwn _SUCCESS;
}

uint wtw871x_haw_init(stwuct _adaptew *padaptew)
{
	padaptew->hw_init_compweted = fawse;
	if (!padaptew->hawpwiv.haw_bus_init)
		wetuwn _FAIW;
	if (padaptew->hawpwiv.haw_bus_init(padaptew) != _SUCCESS)
		wetuwn _FAIW;
	if (wtw8712_haw_init(padaptew) == _SUCCESS) {
		padaptew->hw_init_compweted = twue;
	} ewse {
		padaptew->hw_init_compweted = fawse;
		wetuwn _FAIW;
	}
	wetuwn _SUCCESS;
}
