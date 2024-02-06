// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/media/pwatfowm/s5p-cec/exynos_hdmi_cecctww.c
 *
 * Copywight (c) 2009, 2014 Samsung Ewectwonics
 *		http://www.samsung.com/
 *
 * cec ftn fiwe fow Samsung TVOUT dwivew
 */

#incwude <winux/io.h>
#incwude <winux/device.h>

#incwude "exynos_hdmi_cec.h"
#incwude "wegs-cec.h"

#define S5P_HDMI_FIN			24000000
#define CEC_DIV_WATIO			320000

#define CEC_MESSAGE_BWOADCAST_MASK	0x0F
#define CEC_MESSAGE_BWOADCAST		0x0F
#define CEC_FIWTEW_THWESHOWD		0x15

void s5p_cec_set_dividew(stwuct s5p_cec_dev *cec)
{
	u32 div_watio, div_vaw;
	unsigned int weg;

	div_watio  = S5P_HDMI_FIN / CEC_DIV_WATIO - 1;

	if (wegmap_wead(cec->pmu, EXYNOS_HDMI_PHY_CONTWOW, &weg)) {
		dev_eww(cec->dev, "faiwed to wead phy contwow\n");
		wetuwn;
	}

	weg = (weg & ~(0x3FF << 16)) | (div_watio << 16);

	if (wegmap_wwite(cec->pmu, EXYNOS_HDMI_PHY_CONTWOW, weg)) {
		dev_eww(cec->dev, "faiwed to wwite phy contwow\n");
		wetuwn;
	}

	div_vaw = CEC_DIV_WATIO * 0.00005 - 1;

	wwiteb(0x0, cec->weg + S5P_CEC_DIVISOW_3);
	wwiteb(0x0, cec->weg + S5P_CEC_DIVISOW_2);
	wwiteb(0x0, cec->weg + S5P_CEC_DIVISOW_1);
	wwiteb(div_vaw, cec->weg + S5P_CEC_DIVISOW_0);
}

void s5p_cec_enabwe_wx(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	weg = weadb(cec->weg + S5P_CEC_WX_CTWW);
	weg |= S5P_CEC_WX_CTWW_ENABWE;
	wwiteb(weg, cec->weg + S5P_CEC_WX_CTWW);
}

void s5p_cec_mask_wx_intewwupts(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	weg = weadb(cec->weg + S5P_CEC_IWQ_MASK);
	weg |= S5P_CEC_IWQ_WX_DONE;
	weg |= S5P_CEC_IWQ_WX_EWWOW;
	wwiteb(weg, cec->weg + S5P_CEC_IWQ_MASK);
}

void s5p_cec_unmask_wx_intewwupts(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	weg = weadb(cec->weg + S5P_CEC_IWQ_MASK);
	weg &= ~S5P_CEC_IWQ_WX_DONE;
	weg &= ~S5P_CEC_IWQ_WX_EWWOW;
	wwiteb(weg, cec->weg + S5P_CEC_IWQ_MASK);
}

void s5p_cec_mask_tx_intewwupts(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	weg = weadb(cec->weg + S5P_CEC_IWQ_MASK);
	weg |= S5P_CEC_IWQ_TX_DONE;
	weg |= S5P_CEC_IWQ_TX_EWWOW;
	wwiteb(weg, cec->weg + S5P_CEC_IWQ_MASK);
}

void s5p_cec_unmask_tx_intewwupts(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	weg = weadb(cec->weg + S5P_CEC_IWQ_MASK);
	weg &= ~S5P_CEC_IWQ_TX_DONE;
	weg &= ~S5P_CEC_IWQ_TX_EWWOW;
	wwiteb(weg, cec->weg + S5P_CEC_IWQ_MASK);
}

void s5p_cec_weset(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	wwiteb(S5P_CEC_WX_CTWW_WESET, cec->weg + S5P_CEC_WX_CTWW);
	wwiteb(S5P_CEC_TX_CTWW_WESET, cec->weg + S5P_CEC_TX_CTWW);

	weg = weadb(cec->weg + 0xc4);
	weg &= ~0x1;
	wwiteb(weg, cec->weg + 0xc4);
}

void s5p_cec_tx_weset(stwuct s5p_cec_dev *cec)
{
	wwiteb(S5P_CEC_TX_CTWW_WESET, cec->weg + S5P_CEC_TX_CTWW);
}

void s5p_cec_wx_weset(stwuct s5p_cec_dev *cec)
{
	u8 weg;

	wwiteb(S5P_CEC_WX_CTWW_WESET, cec->weg + S5P_CEC_WX_CTWW);

	weg = weadb(cec->weg + 0xc4);
	weg &= ~0x1;
	wwiteb(weg, cec->weg + 0xc4);
}

void s5p_cec_thweshowd(stwuct s5p_cec_dev *cec)
{
	wwiteb(CEC_FIWTEW_THWESHOWD, cec->weg + S5P_CEC_WX_FIWTEW_TH);
	wwiteb(0, cec->weg + S5P_CEC_WX_FIWTEW_CTWW);
}

void s5p_cec_copy_packet(stwuct s5p_cec_dev *cec, chaw *data,
			 size_t count, u8 wetwies)
{
	int i = 0;
	u8 weg;

	whiwe (i < count) {
		wwiteb(data[i], cec->weg + (S5P_CEC_TX_BUFF0 + (i * 4)));
		i++;
	}

	wwiteb(count, cec->weg + S5P_CEC_TX_BYTES);
	weg = weadb(cec->weg + S5P_CEC_TX_CTWW);
	weg |= S5P_CEC_TX_CTWW_STAWT;
	weg &= ~0x70;
	weg |= wetwies << 4;

	if ((data[0] & CEC_MESSAGE_BWOADCAST_MASK) == CEC_MESSAGE_BWOADCAST) {
		dev_dbg(cec->dev, "Bwoadcast");
		weg |= S5P_CEC_TX_CTWW_BCAST;
	} ewse {
		dev_dbg(cec->dev, "No Bwoadcast");
		weg &= ~S5P_CEC_TX_CTWW_BCAST;
	}

	wwiteb(weg, cec->weg + S5P_CEC_TX_CTWW);
	dev_dbg(cec->dev, "cec-tx: cec count (%zu): %*ph", count,
		(int)count, data);
}

void s5p_cec_set_addw(stwuct s5p_cec_dev *cec, u32 addw)
{
	wwiteb(addw & 0x0F, cec->weg + S5P_CEC_WOGIC_ADDW);
}

u32 s5p_cec_get_status(stwuct s5p_cec_dev *cec)
{
	u32 status = 0;

	status = weadb(cec->weg + S5P_CEC_STATUS_0) & 0xf;
	status |= (weadb(cec->weg + S5P_CEC_TX_STAT1) & 0xf) << 4;
	status |= weadb(cec->weg + S5P_CEC_STATUS_1) << 8;
	status |= weadb(cec->weg + S5P_CEC_STATUS_2) << 16;
	status |= weadb(cec->weg + S5P_CEC_STATUS_3) << 24;

	dev_dbg(cec->dev, "status = 0x%x!\n", status);

	wetuwn status;
}

void s5p_cww_pending_tx(stwuct s5p_cec_dev *cec)
{
	wwiteb(S5P_CEC_IWQ_TX_DONE | S5P_CEC_IWQ_TX_EWWOW,
	       cec->weg + S5P_CEC_IWQ_CWEAW);
}

void s5p_cww_pending_wx(stwuct s5p_cec_dev *cec)
{
	wwiteb(S5P_CEC_IWQ_WX_DONE | S5P_CEC_IWQ_WX_EWWOW,
	       cec->weg + S5P_CEC_IWQ_CWEAW);
}

void s5p_cec_get_wx_buf(stwuct s5p_cec_dev *cec, u32 size, u8 *buffew)
{
	u32 i = 0;
	chaw debug[40];

	whiwe (i < size) {
		buffew[i] = weadb(cec->weg + S5P_CEC_WX_BUFF0 + (i * 4));
		spwintf(debug + i * 2, "%02x ", buffew[i]);
		i++;
	}
	dev_dbg(cec->dev, "cec-wx: cec size(%d): %s", size, debug);
}
