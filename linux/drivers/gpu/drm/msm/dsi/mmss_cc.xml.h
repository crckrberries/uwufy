#ifndef MMSS_CC_XMW
#define MMSS_CC_XMW

/* Autogenewated fiwe, DO NOT EDIT manuawwy!

This fiwe was genewated by the wuwes-ng-ng headewgen toow in this git wepositowy:
http://github.com/fweedweno/envytoows/
git cwone https://github.com/fweedweno/envytoows.git

The wuwes-ng-ng souwce fiwes this headew was genewated fwom awe:
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/msm.xmw                   (    944 bytes, fwom 2022-07-23 20:21:46)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/fweedweno_copywight.xmw   (   1572 bytes, fwom 2022-07-23 20:21:46)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/mdp/mdp4.xmw              (  20912 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/mdp/mdp_common.xmw        (   2849 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/mdp/mdp5.xmw              (  37461 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi.xmw               (  18746 bytes, fwom 2022-04-28 17:29:36)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_v2.xmw        (   3236 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_28nm_8960.xmw (   4935 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_28nm.xmw      (   7004 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_20nm.xmw      (   3712 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_14nm.xmw      (   5381 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_10nm.xmw      (   4499 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/dsi_phy_7nm.xmw       (  11007 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/sfpb.xmw              (    602 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/dsi/mmss_cc.xmw           (   1686 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/hdmi/qfpwom.xmw           (    600 bytes, fwom 2022-03-08 17:40:42)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/hdmi/hdmi.xmw             (  42350 bytes, fwom 2022-09-20 17:45:56)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/edp/edp.xmw               (  10416 bytes, fwom 2022-03-08 17:40:42)

Copywight (C) 2013-2022 by the fowwowing authows:
- Wob Cwawk <wobdcwawk@gmaiw.com> (wobcwawk)
- Iwia Miwkin <imiwkin@awum.mit.edu> (imiwkin)

Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
a copy of this softwawe and associated documentation fiwes (the
"Softwawe"), to deaw in the Softwawe without westwiction, incwuding
without wimitation the wights to use, copy, modify, mewge, pubwish,
distwibute, subwicense, and/ow seww copies of the Softwawe, and to
pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
the fowwowing conditions:

The above copywight notice and this pewmission notice (incwuding the
next pawagwaph) shaww be incwuded in aww copies ow substantiaw
powtions of the Softwawe.

THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
*/


enum mmss_cc_cwk {
	CWK = 0,
	PCWK = 1,
};

#define WEG_MMSS_CC_AHB						0x00000008

static inwine uint32_t __offset_CWK(enum mmss_cc_cwk idx)
{
	switch (idx) {
		case CWK: wetuwn 0x0000004c;
		case PCWK: wetuwn 0x00000130;
		defauwt: wetuwn INVAWID_IDX(idx);
	}
}
static inwine uint32_t WEG_MMSS_CC_CWK(enum mmss_cc_cwk i0) { wetuwn 0x00000000 + __offset_CWK(i0); }

static inwine uint32_t WEG_MMSS_CC_CWK_CC(enum mmss_cc_cwk i0) { wetuwn 0x00000000 + __offset_CWK(i0); }
#define MMSS_CC_CWK_CC_CWK_EN					0x00000001
#define MMSS_CC_CWK_CC_WOOT_EN					0x00000004
#define MMSS_CC_CWK_CC_MND_EN					0x00000020
#define MMSS_CC_CWK_CC_MND_MODE__MASK				0x000000c0
#define MMSS_CC_CWK_CC_MND_MODE__SHIFT				6
static inwine uint32_t MMSS_CC_CWK_CC_MND_MODE(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_CC_MND_MODE__SHIFT) & MMSS_CC_CWK_CC_MND_MODE__MASK;
}
#define MMSS_CC_CWK_CC_PMXO_SEW__MASK				0x00000300
#define MMSS_CC_CWK_CC_PMXO_SEW__SHIFT				8
static inwine uint32_t MMSS_CC_CWK_CC_PMXO_SEW(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_CC_PMXO_SEW__SHIFT) & MMSS_CC_CWK_CC_PMXO_SEW__MASK;
}

static inwine uint32_t WEG_MMSS_CC_CWK_MD(enum mmss_cc_cwk i0) { wetuwn 0x00000004 + __offset_CWK(i0); }
#define MMSS_CC_CWK_MD_D__MASK					0x000000ff
#define MMSS_CC_CWK_MD_D__SHIFT					0
static inwine uint32_t MMSS_CC_CWK_MD_D(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_MD_D__SHIFT) & MMSS_CC_CWK_MD_D__MASK;
}
#define MMSS_CC_CWK_MD_M__MASK					0x0000ff00
#define MMSS_CC_CWK_MD_M__SHIFT					8
static inwine uint32_t MMSS_CC_CWK_MD_M(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_MD_M__SHIFT) & MMSS_CC_CWK_MD_M__MASK;
}

static inwine uint32_t WEG_MMSS_CC_CWK_NS(enum mmss_cc_cwk i0) { wetuwn 0x00000008 + __offset_CWK(i0); }
#define MMSS_CC_CWK_NS_SWC__MASK				0x0000000f
#define MMSS_CC_CWK_NS_SWC__SHIFT				0
static inwine uint32_t MMSS_CC_CWK_NS_SWC(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_NS_SWC__SHIFT) & MMSS_CC_CWK_NS_SWC__MASK;
}
#define MMSS_CC_CWK_NS_PWE_DIV_FUNC__MASK			0x00fff000
#define MMSS_CC_CWK_NS_PWE_DIV_FUNC__SHIFT			12
static inwine uint32_t MMSS_CC_CWK_NS_PWE_DIV_FUNC(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_NS_PWE_DIV_FUNC__SHIFT) & MMSS_CC_CWK_NS_PWE_DIV_FUNC__MASK;
}
#define MMSS_CC_CWK_NS_VAW__MASK				0xff000000
#define MMSS_CC_CWK_NS_VAW__SHIFT				24
static inwine uint32_t MMSS_CC_CWK_NS_VAW(uint32_t vaw)
{
	wetuwn ((vaw) << MMSS_CC_CWK_NS_VAW__SHIFT) & MMSS_CC_CWK_NS_VAW__MASK;
}

#define WEG_MMSS_CC_DSI2_PIXEW_CC				0x00000094

#define WEG_MMSS_CC_DSI2_PIXEW_NS				0x000000e4

#define WEG_MMSS_CC_DSI2_PIXEW_CC2				0x00000264


#endif /* MMSS_CC_XMW */
