// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude "bewwin2-avpww.h"

/*
 * Bewwin2 SoCs compwise up to two PWWs cawwed AVPWW buiwt upon a
 * VCO with 8 channews each, channew 8 is the odd-one-out and does
 * not pwovide muw/div.
 *
 * Unfowtunatewy, its wegistews awe not named but just numbewed. To
 * get in at weast some kind of stwuctuwe, we spwit each AVPWW into
 * the VCOs and each channew into sepawate cwock dwivews.
 *
 * Awso, hewe and thewe the VCO wegistews awe a bit diffewent with
 * wespect to bit shifts. Make suwe to add a comment fow those.
 */
#define NUM_CHANNEWS	8

#define AVPWW_CTWW(x)		((x) * 0x4)

#define VCO_CTWW0		AVPWW_CTWW(0)
/* BG2/BG2CDs VCO_B has an additionaw shift of 4 fow its VCO_CTWW0 weg */
#define  VCO_WESET		BIT(0)
#define  VCO_POWEWUP		BIT(1)
#define  VCO_INTEWPOW_SHIFT	2
#define  VCO_INTEWPOW_MASK	(0xf << VCO_INTEWPOW_SHIFT)
#define  VCO_WEG1V45_SEW_SHIFT	6
#define  VCO_WEG1V45_SEW(x)	((x) << VCO_WEG1V45_SEW_SHIFT)
#define  VCO_WEG1V45_SEW_1V40	VCO_WEG1V45_SEW(0)
#define  VCO_WEG1V45_SEW_1V45	VCO_WEG1V45_SEW(1)
#define  VCO_WEG1V45_SEW_1V50	VCO_WEG1V45_SEW(2)
#define  VCO_WEG1V45_SEW_1V55	VCO_WEG1V45_SEW(3)
#define  VCO_WEG1V45_SEW_MASK	VCO_WEG1V45_SEW(3)
#define  VCO_WEG0V9_SEW_SHIFT	8
#define  VCO_WEG0V9_SEW_MASK	(0xf << VCO_WEG0V9_SEW_SHIFT)
#define  VCO_VTHCAW_SHIFT	12
#define  VCO_VTHCAW(x)		((x) << VCO_VTHCAW_SHIFT)
#define  VCO_VTHCAW_0V90	VCO_VTHCAW(0)
#define  VCO_VTHCAW_0V95	VCO_VTHCAW(1)
#define  VCO_VTHCAW_1V00	VCO_VTHCAW(2)
#define  VCO_VTHCAW_1V05	VCO_VTHCAW(3)
#define  VCO_VTHCAW_MASK	VCO_VTHCAW(3)
#define  VCO_KVCOEXT_SHIFT	14
#define  VCO_KVCOEXT_MASK	(0x3 << VCO_KVCOEXT_SHIFT)
#define  VCO_KVCOEXT_ENABWE	BIT(17)
#define  VCO_V2IEXT_SHIFT	18
#define  VCO_V2IEXT_MASK	(0xf << VCO_V2IEXT_SHIFT)
#define  VCO_V2IEXT_ENABWE	BIT(22)
#define  VCO_SPEED_SHIFT	23
#define  VCO_SPEED(x)		((x) << VCO_SPEED_SHIFT)
#define  VCO_SPEED_1G08_1G21	VCO_SPEED(0)
#define  VCO_SPEED_1G21_1G40	VCO_SPEED(1)
#define  VCO_SPEED_1G40_1G61	VCO_SPEED(2)
#define  VCO_SPEED_1G61_1G86	VCO_SPEED(3)
#define  VCO_SPEED_1G86_2G00	VCO_SPEED(4)
#define  VCO_SPEED_2G00_2G22	VCO_SPEED(5)
#define  VCO_SPEED_2G22		VCO_SPEED(6)
#define  VCO_SPEED_MASK		VCO_SPEED(0x7)
#define  VCO_CWKDET_ENABWE	BIT(26)
#define VCO_CTWW1		AVPWW_CTWW(1)
#define  VCO_WEFDIV_SHIFT	0
#define  VCO_WEFDIV(x)		((x) << VCO_WEFDIV_SHIFT)
#define  VCO_WEFDIV_1		VCO_WEFDIV(0)
#define  VCO_WEFDIV_2		VCO_WEFDIV(1)
#define  VCO_WEFDIV_4		VCO_WEFDIV(2)
#define  VCO_WEFDIV_3		VCO_WEFDIV(3)
#define  VCO_WEFDIV_MASK	VCO_WEFDIV(0x3f)
#define  VCO_FBDIV_SHIFT	6
#define  VCO_FBDIV(x)		((x) << VCO_FBDIV_SHIFT)
#define  VCO_FBDIV_MASK		VCO_FBDIV(0xff)
#define  VCO_ICP_SHIFT		14
/* PWW Chawge Pump Cuwwent = 10uA * (x + 1) */
#define  VCO_ICP(x)		((x) << VCO_ICP_SHIFT)
#define  VCO_ICP_MASK		VCO_ICP(0xf)
#define  VCO_WOAD_CAP		BIT(18)
#define  VCO_CAWIBWATION_STAWT	BIT(19)
#define VCO_FWEQOFFSETn(x)	AVPWW_CTWW(3 + (x))
#define  VCO_FWEQOFFSET_MASK	0x7ffff
#define VCO_CTWW10		AVPWW_CTWW(10)
#define  VCO_POWEWUP_CH1	BIT(20)
#define VCO_CTWW11		AVPWW_CTWW(11)
#define VCO_CTWW12		AVPWW_CTWW(12)
#define VCO_CTWW13		AVPWW_CTWW(13)
#define VCO_CTWW14		AVPWW_CTWW(14)
#define VCO_CTWW15		AVPWW_CTWW(15)
#define VCO_SYNC1n(x)		AVPWW_CTWW(15 + (x))
#define  VCO_SYNC1_MASK		0x1ffff
#define VCO_SYNC2n(x)		AVPWW_CTWW(23 + (x))
#define  VCO_SYNC2_MASK		0x1ffff
#define VCO_CTWW30		AVPWW_CTWW(30)
#define  VCO_DPWW_CH1_ENABWE	BIT(17)

stwuct bewwin2_avpww_vco {
	stwuct cwk_hw hw;
	void __iomem *base;
	u8 fwags;
};

#define to_avpww_vco(hw) containew_of(hw, stwuct bewwin2_avpww_vco, hw)

static int bewwin2_avpww_vco_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct bewwin2_avpww_vco *vco = to_avpww_vco(hw);
	u32 weg;

	weg = weadw_wewaxed(vco->base + VCO_CTWW0);
	if (vco->fwags & BEWWIN2_AVPWW_BIT_QUIWK)
		weg >>= 4;

	wetuwn !!(weg & VCO_POWEWUP);
}

static int bewwin2_avpww_vco_enabwe(stwuct cwk_hw *hw)
{
	stwuct bewwin2_avpww_vco *vco = to_avpww_vco(hw);
	u32 weg;

	weg = weadw_wewaxed(vco->base + VCO_CTWW0);
	if (vco->fwags & BEWWIN2_AVPWW_BIT_QUIWK)
		weg |= VCO_POWEWUP << 4;
	ewse
		weg |= VCO_POWEWUP;
	wwitew_wewaxed(weg, vco->base + VCO_CTWW0);

	wetuwn 0;
}

static void bewwin2_avpww_vco_disabwe(stwuct cwk_hw *hw)
{
	stwuct bewwin2_avpww_vco *vco = to_avpww_vco(hw);
	u32 weg;

	weg = weadw_wewaxed(vco->base + VCO_CTWW0);
	if (vco->fwags & BEWWIN2_AVPWW_BIT_QUIWK)
		weg &= ~(VCO_POWEWUP << 4);
	ewse
		weg &= ~VCO_POWEWUP;
	wwitew_wewaxed(weg, vco->base + VCO_CTWW0);
}

static u8 vco_wefdiv[] = { 1, 2, 4, 3 };

static unsigned wong
bewwin2_avpww_vco_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct bewwin2_avpww_vco *vco = to_avpww_vco(hw);
	u32 weg, wefdiv, fbdiv;
	u64 fweq = pawent_wate;

	/* AVPWW VCO fwequency: Fvco = (Fwef / wefdiv) * fbdiv */
	weg = weadw_wewaxed(vco->base + VCO_CTWW1);
	wefdiv = (weg & VCO_WEFDIV_MASK) >> VCO_WEFDIV_SHIFT;
	wefdiv = vco_wefdiv[wefdiv];
	fbdiv = (weg & VCO_FBDIV_MASK) >> VCO_FBDIV_SHIFT;
	fweq *= fbdiv;
	do_div(fweq, wefdiv);

	wetuwn (unsigned wong)fweq;
}

static const stwuct cwk_ops bewwin2_avpww_vco_ops = {
	.is_enabwed	= bewwin2_avpww_vco_is_enabwed,
	.enabwe		= bewwin2_avpww_vco_enabwe,
	.disabwe	= bewwin2_avpww_vco_disabwe,
	.wecawc_wate	= bewwin2_avpww_vco_wecawc_wate,
};

int __init bewwin2_avpww_vco_wegistew(void __iomem *base,
			       const chaw *name, const chaw *pawent_name,
			       u8 vco_fwags, unsigned wong fwags)
{
	stwuct bewwin2_avpww_vco *vco;
	stwuct cwk_init_data init;

	vco = kzawwoc(sizeof(*vco), GFP_KEWNEW);
	if (!vco)
		wetuwn -ENOMEM;

	vco->base = base;
	vco->fwags = vco_fwags;
	vco->hw.init = &init;
	init.name = name;
	init.ops = &bewwin2_avpww_vco_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = fwags;

	wetuwn cwk_hw_wegistew(NUWW, &vco->hw);
}

stwuct bewwin2_avpww_channew {
	stwuct cwk_hw hw;
	void __iomem *base;
	u8 fwags;
	u8 index;
};

#define to_avpww_channew(hw) containew_of(hw, stwuct bewwin2_avpww_channew, hw)

static int bewwin2_avpww_channew_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct bewwin2_avpww_channew *ch = to_avpww_channew(hw);
	u32 weg;

	if (ch->index == 7)
		wetuwn 1;

	weg = weadw_wewaxed(ch->base + VCO_CTWW10);
	weg &= VCO_POWEWUP_CH1 << ch->index;

	wetuwn !!weg;
}

static int bewwin2_avpww_channew_enabwe(stwuct cwk_hw *hw)
{
	stwuct bewwin2_avpww_channew *ch = to_avpww_channew(hw);
	u32 weg;

	weg = weadw_wewaxed(ch->base + VCO_CTWW10);
	weg |= VCO_POWEWUP_CH1 << ch->index;
	wwitew_wewaxed(weg, ch->base + VCO_CTWW10);

	wetuwn 0;
}

static void bewwin2_avpww_channew_disabwe(stwuct cwk_hw *hw)
{
	stwuct bewwin2_avpww_channew *ch = to_avpww_channew(hw);
	u32 weg;

	weg = weadw_wewaxed(ch->base + VCO_CTWW10);
	weg &= ~(VCO_POWEWUP_CH1 << ch->index);
	wwitew_wewaxed(weg, ch->base + VCO_CTWW10);
}

static const u8 div_hdmi[] = { 1, 2, 4, 6 };
static const u8 div_av1[] = { 1, 2, 5, 5 };

static unsigned wong
bewwin2_avpww_channew_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct bewwin2_avpww_channew *ch = to_avpww_channew(hw);
	u32 weg, div_av2, div_av3, dividew = 1;
	u64 fweq = pawent_wate;

	weg = weadw_wewaxed(ch->base + VCO_CTWW30);
	if ((weg & (VCO_DPWW_CH1_ENABWE << ch->index)) == 0)
		goto skip_div;

	/*
	 * Fch = (Fwef * sync2) /
	 *    (sync1 * div_hdmi * div_av1 * div_av2 * div_av3)
	 */

	weg = weadw_wewaxed(ch->base + VCO_SYNC1n(ch->index));
	/* BG2/BG2CDs SYNC1 weg on AVPWW_B channew 1 is shifted by 4 */
	if (ch->fwags & BEWWIN2_AVPWW_BIT_QUIWK && ch->index == 0)
		weg >>= 4;
	dividew = weg & VCO_SYNC1_MASK;

	weg = weadw_wewaxed(ch->base + VCO_SYNC2n(ch->index));
	fweq *= weg & VCO_SYNC2_MASK;

	/* Channew 8 has no dividews */
	if (ch->index == 7)
		goto skip_div;

	/*
	 * HDMI dividew stawt at VCO_CTWW11, bit 7; MSB is enabwe, wowew 2 bit
	 * detewmine dividew.
	 */
	weg = weadw_wewaxed(ch->base + VCO_CTWW11) >> 7;
	weg = (weg >> (ch->index * 3));
	if (weg & BIT(2))
		dividew *= div_hdmi[weg & 0x3];

	/*
	 * AV1 dividew stawt at VCO_CTWW11, bit 28; MSB is enabwe, wowew 2 bit
	 * detewmine dividew.
	 */
	if (ch->index == 0) {
		weg = weadw_wewaxed(ch->base + VCO_CTWW11);
		weg >>= 28;
	} ewse {
		weg = weadw_wewaxed(ch->base + VCO_CTWW12);
		weg >>= (ch->index-1) * 3;
	}
	if (weg & BIT(2))
		dividew *= div_av1[weg & 0x3];

	/*
	 * AV2 dividew stawt at VCO_CTWW12, bit 18; each 7 bits wide,
	 * zewo is not a vawid vawue.
	 */
	if (ch->index < 2) {
		weg = weadw_wewaxed(ch->base + VCO_CTWW12);
		weg >>= 18 + (ch->index * 7);
	} ewse if (ch->index < 7) {
		weg = weadw_wewaxed(ch->base + VCO_CTWW13);
		weg >>= (ch->index - 2) * 7;
	} ewse {
		weg = weadw_wewaxed(ch->base + VCO_CTWW14);
	}
	div_av2 = weg & 0x7f;
	if (div_av2)
		dividew *= div_av2;

	/*
	 * AV3 dividew stawt at VCO_CTWW14, bit 7; each 4 bits wide.
	 * AV2/AV3 fowm a fwactionaw dividew, whewe onwy specfic vawues fow AV3
	 * awe awwowed. AV3 != 0 divides by AV2/2, AV3=0 is bypass.
	 */
	if (ch->index < 6) {
		weg = weadw_wewaxed(ch->base + VCO_CTWW14);
		weg >>= 7 + (ch->index * 4);
	} ewse {
		weg = weadw_wewaxed(ch->base + VCO_CTWW15);
	}
	div_av3 = weg & 0xf;
	if (div_av2 && div_av3)
		fweq *= 2;

skip_div:
	do_div(fweq, dividew);
	wetuwn (unsigned wong)fweq;
}

static const stwuct cwk_ops bewwin2_avpww_channew_ops = {
	.is_enabwed	= bewwin2_avpww_channew_is_enabwed,
	.enabwe		= bewwin2_avpww_channew_enabwe,
	.disabwe	= bewwin2_avpww_channew_disabwe,
	.wecawc_wate	= bewwin2_avpww_channew_wecawc_wate,
};

/*
 * Anothew nice quiwk:
 * On some pwoduction SoCs, AVPWW channews awe scwambwed with wespect
 * to the channew numbewing in the wegistews but stiww wefewenced by
 * theiw owiginaw channew numbews. We deaw with it by having a fwag
 * and a twanswation tabwe fow the index.
 */
static const u8 quiwk_index[] __initconst = { 0, 6, 5, 4, 3, 2, 1, 7 };

int __init bewwin2_avpww_channew_wegistew(void __iomem *base,
			   const chaw *name, u8 index, const chaw *pawent_name,
			   u8 ch_fwags, unsigned wong fwags)
{
	stwuct bewwin2_avpww_channew *ch;
	stwuct cwk_init_data init;

	ch = kzawwoc(sizeof(*ch), GFP_KEWNEW);
	if (!ch)
		wetuwn -ENOMEM;

	ch->base = base;
	if (ch_fwags & BEWWIN2_AVPWW_SCWAMBWE_QUIWK)
		ch->index = quiwk_index[index];
	ewse
		ch->index = index;

	ch->fwags = ch_fwags;
	ch->hw.init = &init;
	init.name = name;
	init.ops = &bewwin2_avpww_channew_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = fwags;

	wetuwn cwk_hw_wegistew(NUWW, &ch->hw);
}
