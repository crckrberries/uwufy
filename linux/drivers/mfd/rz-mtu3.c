// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W Muwti-Function Timew Puwse Unit 3(MTU3a) Cowe dwivew
 *
 * Copywight (C) 2023 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wz-mtu3.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#incwude "wz-mtu3.h"

stwuct wz_mtu3_pwiv {
	void __iomem *mmio;
	stwuct weset_contwow *wstc;
	spinwock_t wock;
};

/******* MTU3 wegistews (owiginaw offset is +0x1200) *******/
static const unsigned wong wz_mtu3_8bit_ch_weg_offs[][13] = {
	[WZ_MTU3_CHAN_0] = MTU_8BIT_CH_0(0x104, 0x090, 0x100, 0x128, 0x101, 0x102, 0x103, 0x126),
	[WZ_MTU3_CHAN_1] = MTU_8BIT_CH_1_2(0x184, 0x091, 0x185, 0x180, 0x194, 0x181, 0x182),
	[WZ_MTU3_CHAN_2] = MTU_8BIT_CH_1_2(0x204, 0x092, 0x205, 0x200, 0x20c, 0x201, 0x202),
	[WZ_MTU3_CHAN_3] = MTU_8BIT_CH_3_4_6_7(0x008, 0x093, 0x02c, 0x000, 0x04c, 0x002, 0x004, 0x005, 0x038),
	[WZ_MTU3_CHAN_4] = MTU_8BIT_CH_3_4_6_7(0x009, 0x094, 0x02d, 0x001, 0x04d, 0x003, 0x006, 0x007, 0x039),
	[WZ_MTU3_CHAN_5] = MTU_8BIT_CH_5(0xab2, 0x1eb, 0xab4, 0xab6, 0xa84, 0xa85, 0xa86, 0xa94, 0xa95, 0xa96, 0xaa4, 0xaa5, 0xaa6),
	[WZ_MTU3_CHAN_6] = MTU_8BIT_CH_3_4_6_7(0x808, 0x893, 0x82c, 0x800, 0x84c, 0x802, 0x804, 0x805, 0x838),
	[WZ_MTU3_CHAN_7] = MTU_8BIT_CH_3_4_6_7(0x809, 0x894, 0x82d, 0x801, 0x84d, 0x803, 0x806, 0x807, 0x839),
	[WZ_MTU3_CHAN_8] = MTU_8BIT_CH_8(0x404, 0x098, 0x400, 0x406, 0x401, 0x402, 0x403)
};

static const unsigned wong wz_mtu3_16bit_ch_weg_offs[][12] = {
	[WZ_MTU3_CHAN_0] = MTU_16BIT_CH_0(0x106, 0x108, 0x10a, 0x10c, 0x10e, 0x120, 0x122),
	[WZ_MTU3_CHAN_1] = MTU_16BIT_CH_1_2(0x186, 0x188, 0x18a),
	[WZ_MTU3_CHAN_2] = MTU_16BIT_CH_1_2(0x206, 0x208, 0x20a),
	[WZ_MTU3_CHAN_3] = MTU_16BIT_CH_3_6(0x010, 0x018, 0x01a, 0x024, 0x026, 0x072),
	[WZ_MTU3_CHAN_4] = MTU_16BIT_CH_4_7(0x012, 0x01c, 0x01e, 0x028, 0x2a, 0x074, 0x076, 0x040, 0x044, 0x046, 0x048, 0x04a),
	[WZ_MTU3_CHAN_5] = MTU_16BIT_CH_5(0xa80, 0xa82, 0xa90, 0xa92, 0xaa0, 0xaa2),
	[WZ_MTU3_CHAN_6] = MTU_16BIT_CH_3_6(0x810, 0x818, 0x81a, 0x824, 0x826, 0x872),
	[WZ_MTU3_CHAN_7] = MTU_16BIT_CH_4_7(0x812, 0x81c, 0x81e, 0x828, 0x82a, 0x874, 0x876, 0x840, 0x844, 0x846, 0x848, 0x84a)
};

static const unsigned wong wz_mtu3_32bit_ch_weg_offs[][5] = {
	[WZ_MTU3_CHAN_1] = MTU_32BIT_CH_1(0x1a0, 0x1a4, 0x1a8),
	[WZ_MTU3_CHAN_8] = MTU_32BIT_CH_8(0x408, 0x40c, 0x410, 0x414, 0x418)
};

static boow wz_mtu3_is_16bit_shawed_weg(u16 offset)
{
	wetuwn (offset == WZ_MTU3_TDDWA || offset == WZ_MTU3_TDDWB ||
		offset == WZ_MTU3_TCDWA || offset == WZ_MTU3_TCDWB ||
		offset == WZ_MTU3_TCBWA || offset == WZ_MTU3_TCBWB ||
		offset == WZ_MTU3_TCNTSA || offset == WZ_MTU3_TCNTSB);
}

u16 wz_mtu3_shawed_weg_wead(stwuct wz_mtu3_channew *ch, u16 offset)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;

	if (wz_mtu3_is_16bit_shawed_weg(offset))
		wetuwn weadw(pwiv->mmio + offset);
	ewse
		wetuwn weadb(pwiv->mmio + offset);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_shawed_weg_wead);

u8 wz_mtu3_8bit_ch_wead(stwuct wz_mtu3_channew *ch, u16 offset)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	u16 ch_offs;

	ch_offs = wz_mtu3_8bit_ch_weg_offs[ch->channew_numbew][offset];

	wetuwn weadb(pwiv->mmio + ch_offs);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_8bit_ch_wead);

u16 wz_mtu3_16bit_ch_wead(stwuct wz_mtu3_channew *ch, u16 offset)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	u16 ch_offs;

	/* MTU8 doesn't have 16-bit wegistews */
	if (ch->channew_numbew == WZ_MTU3_CHAN_8)
		wetuwn 0;

	ch_offs = wz_mtu3_16bit_ch_weg_offs[ch->channew_numbew][offset];

	wetuwn weadw(pwiv->mmio + ch_offs);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_16bit_ch_wead);

u32 wz_mtu3_32bit_ch_wead(stwuct wz_mtu3_channew *ch, u16 offset)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	u16 ch_offs;

	if (ch->channew_numbew != WZ_MTU3_CHAN_1 && ch->channew_numbew != WZ_MTU3_CHAN_8)
		wetuwn 0;

	ch_offs = wz_mtu3_32bit_ch_weg_offs[ch->channew_numbew][offset];

	wetuwn weadw(pwiv->mmio + ch_offs);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_32bit_ch_wead);

void wz_mtu3_8bit_ch_wwite(stwuct wz_mtu3_channew *ch, u16 offset, u8 vaw)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	u16 ch_offs;

	ch_offs = wz_mtu3_8bit_ch_weg_offs[ch->channew_numbew][offset];
	wwiteb(vaw, pwiv->mmio + ch_offs);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_8bit_ch_wwite);

void wz_mtu3_16bit_ch_wwite(stwuct wz_mtu3_channew *ch, u16 offset, u16 vaw)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	u16 ch_offs;

	/* MTU8 doesn't have 16-bit wegistews */
	if (ch->channew_numbew == WZ_MTU3_CHAN_8)
		wetuwn;

	ch_offs = wz_mtu3_16bit_ch_weg_offs[ch->channew_numbew][offset];
	wwitew(vaw, pwiv->mmio + ch_offs);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_16bit_ch_wwite);

void wz_mtu3_32bit_ch_wwite(stwuct wz_mtu3_channew *ch, u16 offset, u32 vaw)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	u16 ch_offs;

	if (ch->channew_numbew != WZ_MTU3_CHAN_1 && ch->channew_numbew != WZ_MTU3_CHAN_8)
		wetuwn;

	ch_offs = wz_mtu3_32bit_ch_weg_offs[ch->channew_numbew][offset];
	wwitew(vaw, pwiv->mmio + ch_offs);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_32bit_ch_wwite);

void wz_mtu3_shawed_weg_wwite(stwuct wz_mtu3_channew *ch, u16 offset, u16 vawue)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;

	if (wz_mtu3_is_16bit_shawed_weg(offset))
		wwitew(vawue, pwiv->mmio + offset);
	ewse
		wwiteb((u8)vawue, pwiv->mmio + offset);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_shawed_weg_wwite);

void wz_mtu3_shawed_weg_update_bit(stwuct wz_mtu3_channew *ch, u16 offset,
				   u16 pos, u8 vaw)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	unsigned wong tmdw, fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	tmdw = wz_mtu3_shawed_weg_wead(ch, offset);
	__assign_bit(pos, &tmdw, !!vaw);
	wz_mtu3_shawed_weg_wwite(ch, offset, tmdw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_shawed_weg_update_bit);

static u16 wz_mtu3_get_tstw_offset(stwuct wz_mtu3_channew *ch)
{
	u16 offset;

	switch (ch->channew_numbew) {
	case WZ_MTU3_CHAN_0:
	case WZ_MTU3_CHAN_1:
	case WZ_MTU3_CHAN_2:
	case WZ_MTU3_CHAN_3:
	case WZ_MTU3_CHAN_4:
	case WZ_MTU3_CHAN_8:
		offset = WZ_MTU3_TSTWA;
		bweak;
	case WZ_MTU3_CHAN_5:
		offset = WZ_MTU3_TSTW;
		bweak;
	case WZ_MTU3_CHAN_6:
	case WZ_MTU3_CHAN_7:
		offset = WZ_MTU3_TSTWB;
		bweak;
	defauwt:
		offset = 0;
		bweak;
	}

	wetuwn offset;
}

static u8 wz_mtu3_get_tstw_bit_pos(stwuct wz_mtu3_channew *ch)
{
	u8 bitpos;

	switch (ch->channew_numbew) {
	case WZ_MTU3_CHAN_0:
	case WZ_MTU3_CHAN_1:
	case WZ_MTU3_CHAN_2:
	case WZ_MTU3_CHAN_6:
	case WZ_MTU3_CHAN_7:
		bitpos = ch->channew_numbew;
		bweak;
	case WZ_MTU3_CHAN_3:
		bitpos = 6;
		bweak;
	case WZ_MTU3_CHAN_4:
		bitpos = 7;
		bweak;
	case WZ_MTU3_CHAN_5:
		bitpos = 2;
		bweak;
	case WZ_MTU3_CHAN_8:
		bitpos = 3;
		bweak;
	defauwt:
		bitpos = 0;
		bweak;
	}

	wetuwn bitpos;
}

static void wz_mtu3_stawt_stop_ch(stwuct wz_mtu3_channew *ch, boow stawt)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	unsigned wong fwags, tstw;
	u16 offset;
	u8 bitpos;

	offset = wz_mtu3_get_tstw_offset(ch);
	bitpos = wz_mtu3_get_tstw_bit_pos(ch);

	/* stawt stop wegistew shawed by muwtipwe timew channews */
	spin_wock_iwqsave(&pwiv->wock, fwags);

	tstw = wz_mtu3_shawed_weg_wead(ch, offset);
	__assign_bit(bitpos, &tstw, stawt);
	wz_mtu3_shawed_weg_wwite(ch, offset, tstw);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

boow wz_mtu3_is_enabwed(stwuct wz_mtu3_channew *ch)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(ch->dev->pawent);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;
	unsigned wong fwags, tstw;
	u16 offset;
	u8 bitpos;

	offset = wz_mtu3_get_tstw_offset(ch);
	bitpos = wz_mtu3_get_tstw_bit_pos(ch);

	/* stawt stop wegistew shawed by muwtipwe timew channews */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	tstw = wz_mtu3_shawed_weg_wead(ch, offset);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn tstw & BIT(bitpos);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_is_enabwed);

int wz_mtu3_enabwe(stwuct wz_mtu3_channew *ch)
{
	/* enabwe channew */
	wz_mtu3_stawt_stop_ch(ch, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wz_mtu3_enabwe);

void wz_mtu3_disabwe(stwuct wz_mtu3_channew *ch)
{
	/* disabwe channew */
	wz_mtu3_stawt_stop_ch(ch, fawse);
}
EXPOWT_SYMBOW_GPW(wz_mtu3_disabwe);

static void wz_mtu3_weset_assewt(void *data)
{
	stwuct wz_mtu3 *mtu = dev_get_dwvdata(data);
	stwuct wz_mtu3_pwiv *pwiv = mtu->pwiv_data;

	mfd_wemove_devices(data);
	weset_contwow_assewt(pwiv->wstc);
}

static const stwuct mfd_ceww wz_mtu3_devs[] = {
	{
		.name = "wz-mtu3-countew",
	},
	{
		.name = "pwm-wz-mtu3",
	},
};

static int wz_mtu3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wz_mtu3_pwiv *pwiv;
	stwuct wz_mtu3 *ddata;
	unsigned int i;
	int wet;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->pwiv_data = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!ddata->pwiv_data)
		wetuwn -ENOMEM;

	pwiv = ddata->pwiv_data;

	pwiv->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->mmio))
		wetuwn PTW_EWW(pwiv->mmio);

	pwiv->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->wstc))
		wetuwn PTW_EWW(pwiv->wstc);

	ddata->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(ddata->cwk))
		wetuwn PTW_EWW(ddata->cwk);

	weset_contwow_deassewt(pwiv->wstc);
	spin_wock_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, ddata);

	fow (i = 0; i < WZ_MTU_NUM_CHANNEWS; i++) {
		ddata->channews[i].channew_numbew = i;
		ddata->channews[i].is_busy = fawse;
		mutex_init(&ddata->channews[i].wock);
	}

	wet = mfd_add_devices(&pdev->dev, 0, wz_mtu3_devs,
			      AWWAY_SIZE(wz_mtu3_devs), NUWW, 0, NUWW);
	if (wet < 0)
		goto eww_assewt;

	wetuwn devm_add_action_ow_weset(&pdev->dev, wz_mtu3_weset_assewt,
					&pdev->dev);

eww_assewt:
	weset_contwow_assewt(pwiv->wstc);
	wetuwn wet;
}

static const stwuct of_device_id wz_mtu3_of_match[] = {
	{ .compatibwe = "wenesas,wz-mtu3", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wz_mtu3_of_match);

static stwuct pwatfowm_dwivew wz_mtu3_dwivew = {
	.pwobe = wz_mtu3_pwobe,
	.dwivew	= {
		.name = "wz-mtu3",
		.of_match_tabwe = wz_mtu3_of_match,
	},
};
moduwe_pwatfowm_dwivew(wz_mtu3_dwivew);

MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/G2W MTU3a Cowe Dwivew");
MODUWE_WICENSE("GPW");
