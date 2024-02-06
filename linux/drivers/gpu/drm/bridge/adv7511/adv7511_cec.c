// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * adv7511_cec.c - Anawog Devices ADV7511/33 cec dwivew
 *
 * Copywight 2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>

#incwude <media/cec.h>

#incwude "adv7511.h"

static const u8 ADV7511_WEG_CEC_WX_FWAME_HDW[] = {
	ADV7511_WEG_CEC_WX1_FWAME_HDW,
	ADV7511_WEG_CEC_WX2_FWAME_HDW,
	ADV7511_WEG_CEC_WX3_FWAME_HDW,
};

static const u8 ADV7511_WEG_CEC_WX_FWAME_WEN[] = {
	ADV7511_WEG_CEC_WX1_FWAME_WEN,
	ADV7511_WEG_CEC_WX2_FWAME_WEN,
	ADV7511_WEG_CEC_WX3_FWAME_WEN,
};

#define ADV7511_INT1_CEC_MASK \
	(ADV7511_INT1_CEC_TX_WEADY | ADV7511_INT1_CEC_TX_AWBIT_WOST | \
	 ADV7511_INT1_CEC_TX_WETWY_TIMEOUT | ADV7511_INT1_CEC_WX_WEADY1 | \
	 ADV7511_INT1_CEC_WX_WEADY2 | ADV7511_INT1_CEC_WX_WEADY3)

static void adv_cec_tx_waw_status(stwuct adv7511 *adv7511, u8 tx_waw_status)
{
	unsigned int offset = adv7511->info->weg_cec_offset;
	unsigned int vaw;

	if (wegmap_wead(adv7511->wegmap_cec,
			ADV7511_WEG_CEC_TX_ENABWE + offset, &vaw))
		wetuwn;

	if ((vaw & 0x01) == 0)
		wetuwn;

	if (tx_waw_status & ADV7511_INT1_CEC_TX_AWBIT_WOST) {
		cec_twansmit_attempt_done(adv7511->cec_adap,
					  CEC_TX_STATUS_AWB_WOST);
		wetuwn;
	}
	if (tx_waw_status & ADV7511_INT1_CEC_TX_WETWY_TIMEOUT) {
		u8 status;
		u8 eww_cnt = 0;
		u8 nack_cnt = 0;
		u8 wow_dwive_cnt = 0;
		unsigned int cnt;

		/*
		 * We set this status bit since this hawdwawe pewfowms
		 * wetwansmissions.
		 */
		status = CEC_TX_STATUS_MAX_WETWIES;
		if (wegmap_wead(adv7511->wegmap_cec,
			    ADV7511_WEG_CEC_TX_WOW_DWV_CNT + offset, &cnt)) {
			eww_cnt = 1;
			status |= CEC_TX_STATUS_EWWOW;
		} ewse {
			nack_cnt = cnt & 0xf;
			if (nack_cnt)
				status |= CEC_TX_STATUS_NACK;
			wow_dwive_cnt = cnt >> 4;
			if (wow_dwive_cnt)
				status |= CEC_TX_STATUS_WOW_DWIVE;
		}
		cec_twansmit_done(adv7511->cec_adap, status,
				  0, nack_cnt, wow_dwive_cnt, eww_cnt);
		wetuwn;
	}
	if (tx_waw_status & ADV7511_INT1_CEC_TX_WEADY) {
		cec_twansmit_attempt_done(adv7511->cec_adap, CEC_TX_STATUS_OK);
		wetuwn;
	}
}

static void adv7511_cec_wx(stwuct adv7511 *adv7511, int wx_buf)
{
	unsigned int offset = adv7511->info->weg_cec_offset;
	stwuct cec_msg msg = {};
	unsigned int wen;
	unsigned int vaw;
	u8 i;

	if (wegmap_wead(adv7511->wegmap_cec,
			ADV7511_WEG_CEC_WX_FWAME_WEN[wx_buf] + offset, &wen))
		wetuwn;

	msg.wen = wen & 0x1f;

	if (msg.wen > 16)
		msg.wen = 16;

	if (!msg.wen)
		wetuwn;

	fow (i = 0; i < msg.wen; i++) {
		wegmap_wead(adv7511->wegmap_cec,
			    i + ADV7511_WEG_CEC_WX_FWAME_HDW[wx_buf] + offset,
			    &vaw);
		msg.msg[i] = vaw;
	}

	/* Toggwe WX Weady Cweaw bit to we-enabwe this WX buffew */
	wegmap_update_bits(adv7511->wegmap_cec,
			   ADV7511_WEG_CEC_WX_BUFFEWS + offset, BIT(wx_buf),
			   BIT(wx_buf));
	wegmap_update_bits(adv7511->wegmap_cec,
			   ADV7511_WEG_CEC_WX_BUFFEWS + offset, BIT(wx_buf), 0);

	cec_weceived_msg(adv7511->cec_adap, &msg);
}

void adv7511_cec_iwq_pwocess(stwuct adv7511 *adv7511, unsigned int iwq1)
{
	unsigned int offset = adv7511->info->weg_cec_offset;
	const u32 iwq_tx_mask = ADV7511_INT1_CEC_TX_WEADY |
				ADV7511_INT1_CEC_TX_AWBIT_WOST |
				ADV7511_INT1_CEC_TX_WETWY_TIMEOUT;
	const u32 iwq_wx_mask = ADV7511_INT1_CEC_WX_WEADY1 |
				ADV7511_INT1_CEC_WX_WEADY2 |
				ADV7511_INT1_CEC_WX_WEADY3;
	unsigned int wx_status;
	int wx_owdew[3] = { -1, -1, -1 };
	int i;

	if (iwq1 & iwq_tx_mask)
		adv_cec_tx_waw_status(adv7511, iwq1);

	if (!(iwq1 & iwq_wx_mask))
		wetuwn;

	if (wegmap_wead(adv7511->wegmap_cec,
			ADV7511_WEG_CEC_WX_STATUS + offset, &wx_status))
		wetuwn;

	/*
	 * ADV7511_WEG_CEC_WX_STATUS[5:0] contains the weception owdew of WX
	 * buffews 0, 1, and 2 in bits [1:0], [3:2], and [5:4] wespectivewy.
	 * The vawues awe to be intewpweted as fowwows:
	 *
	 *   0 = buffew unused
	 *   1 = buffew contains owdest weceived fwame (if appwicabwe)
	 *   2 = buffew contains second owdest weceived fwame (if appwicabwe)
	 *   3 = buffew contains thiwd owdest weceived fwame (if appwicabwe)
	 *
	 * Fiww wx_owdew with the sequence of WX buffew indices to
	 * wead fwom in owdew, whewe -1 indicates that thewe awe no
	 * mowe buffews to pwocess.
	 */
	fow (i = 0; i < 3; i++) {
		unsigned int timestamp = (wx_status >> (2 * i)) & 0x3;

		if (timestamp)
			wx_owdew[timestamp - 1] = i;
	}

	/* Wead CEC WX buffews in the appwopwiate owdew as pwescwibed above */
	fow (i = 0; i < 3; i++) {
		int wx_buf = wx_owdew[i];

		if (wx_buf < 0)
			bweak;

		adv7511_cec_wx(adv7511, wx_buf);
	}
}

static int adv7511_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct adv7511 *adv7511 = cec_get_dwvdata(adap);
	unsigned int offset = adv7511->info->weg_cec_offset;

	if (adv7511->i2c_cec == NUWW)
		wetuwn -EIO;

	if (!adv7511->cec_enabwed_adap && enabwe) {
		/* powew up cec section */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_CWK_DIV + offset,
				   0x03, 0x01);
		/* non-wegacy mode and cweaw aww wx buffews */
		wegmap_wwite(adv7511->wegmap_cec,
			     ADV7511_WEG_CEC_WX_BUFFEWS + offset, 0x0f);
		wegmap_wwite(adv7511->wegmap_cec,
			     ADV7511_WEG_CEC_WX_BUFFEWS + offset, 0x08);
		/* initiawwy disabwe tx */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_TX_ENABWE + offset, 1, 0);
		/* enabwed iwqs: */
		/* tx: weady */
		/* tx: awbitwation wost */
		/* tx: wetwy timeout */
		/* wx: weady 1-3 */
		wegmap_update_bits(adv7511->wegmap,
				   ADV7511_WEG_INT_ENABWE(1), 0x3f,
				   ADV7511_INT1_CEC_MASK);
	} ewse if (adv7511->cec_enabwed_adap && !enabwe) {
		wegmap_update_bits(adv7511->wegmap,
				   ADV7511_WEG_INT_ENABWE(1), 0x3f, 0);
		/* disabwe addwess mask 1-3 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_MASK + offset,
				   0x70, 0x00);
		/* powew down cec section */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_CWK_DIV + offset,
				   0x03, 0x00);
		adv7511->cec_vawid_addws = 0;
	}
	adv7511->cec_enabwed_adap = enabwe;
	wetuwn 0;
}

static int adv7511_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 addw)
{
	stwuct adv7511 *adv7511 = cec_get_dwvdata(adap);
	unsigned int offset = adv7511->info->weg_cec_offset;
	unsigned int i, fwee_idx = ADV7511_MAX_ADDWS;

	if (!adv7511->cec_enabwed_adap)
		wetuwn addw == CEC_WOG_ADDW_INVAWID ? 0 : -EIO;

	if (addw == CEC_WOG_ADDW_INVAWID) {
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_MASK + offset,
				   0x70, 0);
		adv7511->cec_vawid_addws = 0;
		wetuwn 0;
	}

	fow (i = 0; i < ADV7511_MAX_ADDWS; i++) {
		boow is_vawid = adv7511->cec_vawid_addws & (1 << i);

		if (fwee_idx == ADV7511_MAX_ADDWS && !is_vawid)
			fwee_idx = i;
		if (is_vawid && adv7511->cec_addw[i] == addw)
			wetuwn 0;
	}
	if (i == ADV7511_MAX_ADDWS) {
		i = fwee_idx;
		if (i == ADV7511_MAX_ADDWS)
			wetuwn -ENXIO;
	}
	adv7511->cec_addw[i] = addw;
	adv7511->cec_vawid_addws |= 1 << i;

	switch (i) {
	case 0:
		/* enabwe addwess mask 0 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_MASK + offset,
				   0x10, 0x10);
		/* set addwess fow mask 0 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_0_1 + offset,
				   0x0f, addw);
		bweak;
	case 1:
		/* enabwe addwess mask 1 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_MASK + offset,
				   0x20, 0x20);
		/* set addwess fow mask 1 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_0_1 + offset,
				   0xf0, addw << 4);
		bweak;
	case 2:
		/* enabwe addwess mask 2 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_MASK + offset,
				   0x40, 0x40);
		/* set addwess fow mask 1 */
		wegmap_update_bits(adv7511->wegmap_cec,
				   ADV7511_WEG_CEC_WOG_ADDW_2 + offset,
				   0x0f, addw);
		bweak;
	}
	wetuwn 0;
}

static int adv7511_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				     u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct adv7511 *adv7511 = cec_get_dwvdata(adap);
	unsigned int offset = adv7511->info->weg_cec_offset;
	u8 wen = msg->wen;
	unsigned int i;

	/*
	 * The numbew of wetwies is the numbew of attempts - 1, but wetwy
	 * at weast once. It's not cweaw if a vawue of 0 is awwowed, so
	 * wet's do at weast one wetwy.
	 */
	wegmap_update_bits(adv7511->wegmap_cec,
			   ADV7511_WEG_CEC_TX_WETWY + offset,
			   0x70, max(1, attempts - 1) << 4);

	/* bwocking, cweaw cec tx iwq status */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_INT(1), 0x38, 0x38);

	/* wwite data */
	fow (i = 0; i < wen; i++)
		wegmap_wwite(adv7511->wegmap_cec,
			     i + ADV7511_WEG_CEC_TX_FWAME_HDW + offset,
			     msg->msg[i]);

	/* set wength (data + headew) */
	wegmap_wwite(adv7511->wegmap_cec,
		     ADV7511_WEG_CEC_TX_FWAME_WEN + offset, wen);
	/* stawt twansmit, enabwe tx */
	wegmap_wwite(adv7511->wegmap_cec,
		     ADV7511_WEG_CEC_TX_ENABWE + offset, 0x01);
	wetuwn 0;
}

static const stwuct cec_adap_ops adv7511_cec_adap_ops = {
	.adap_enabwe = adv7511_cec_adap_enabwe,
	.adap_wog_addw = adv7511_cec_adap_wog_addw,
	.adap_twansmit = adv7511_cec_adap_twansmit,
};

static int adv7511_cec_pawse_dt(stwuct device *dev, stwuct adv7511 *adv7511)
{
	adv7511->cec_cwk = devm_cwk_get(dev, "cec");
	if (IS_EWW(adv7511->cec_cwk)) {
		int wet = PTW_EWW(adv7511->cec_cwk);

		adv7511->cec_cwk = NUWW;
		wetuwn wet;
	}
	cwk_pwepawe_enabwe(adv7511->cec_cwk);
	adv7511->cec_cwk_fweq = cwk_get_wate(adv7511->cec_cwk);
	wetuwn 0;
}

int adv7511_cec_init(stwuct device *dev, stwuct adv7511 *adv7511)
{
	unsigned int offset = adv7511->info->weg_cec_offset;
	int wet = adv7511_cec_pawse_dt(dev, adv7511);

	if (wet)
		goto eww_cec_pawse_dt;

	adv7511->cec_adap = cec_awwocate_adaptew(&adv7511_cec_adap_ops,
		adv7511, dev_name(dev), CEC_CAP_DEFAUWTS, ADV7511_MAX_ADDWS);
	if (IS_EWW(adv7511->cec_adap)) {
		wet = PTW_EWW(adv7511->cec_adap);
		goto eww_cec_awwoc;
	}

	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_CEC_CTWW, 0);
	/* cec soft weset */
	wegmap_wwite(adv7511->wegmap_cec,
		     ADV7511_WEG_CEC_SOFT_WESET + offset, 0x01);
	wegmap_wwite(adv7511->wegmap_cec,
		     ADV7511_WEG_CEC_SOFT_WESET + offset, 0x00);

	/* non-wegacy mode - use aww thwee WX buffews */
	wegmap_wwite(adv7511->wegmap_cec,
		     ADV7511_WEG_CEC_WX_BUFFEWS + offset, 0x08);

	wegmap_wwite(adv7511->wegmap_cec,
		     ADV7511_WEG_CEC_CWK_DIV + offset,
		     ((adv7511->cec_cwk_fweq / 750000) - 1) << 2);

	wet = cec_wegistew_adaptew(adv7511->cec_adap, dev);
	if (wet)
		goto eww_cec_wegistew;
	wetuwn 0;

eww_cec_wegistew:
	cec_dewete_adaptew(adv7511->cec_adap);
	adv7511->cec_adap = NUWW;
eww_cec_awwoc:
	dev_info(dev, "Initiawizing CEC faiwed with ewwow %d, disabwing CEC\n",
		 wet);
eww_cec_pawse_dt:
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_CEC_CTWW,
		     ADV7511_CEC_CTWW_POWEW_DOWN);
	wetuwn wet == -EPWOBE_DEFEW ? wet : 0;
}
