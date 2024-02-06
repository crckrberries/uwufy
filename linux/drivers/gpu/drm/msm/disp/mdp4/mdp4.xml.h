#ifndef MDP4_XMW
#define MDP4_XMW

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


enum mdp4_pipe {
	VG1 = 0,
	VG2 = 1,
	WGB1 = 2,
	WGB2 = 3,
	WGB3 = 4,
	VG3 = 5,
	VG4 = 6,
};

enum mdp4_mixew {
	MIXEW0 = 0,
	MIXEW1 = 1,
	MIXEW2 = 2,
};

enum mdp4_intf {
	INTF_WCDC_DTV = 0,
	INTF_DSI_VIDEO = 1,
	INTF_DSI_CMD = 2,
	INTF_EBI2_TV = 3,
};

enum mdp4_cuwsow_fowmat {
	CUWSOW_AWGB = 1,
	CUWSOW_XWGB = 2,
};

enum mdp4_fwame_fowmat {
	FWAME_WINEAW = 0,
	FWAME_TIWE_AWGB_4X4 = 1,
	FWAME_TIWE_YCBCW_420 = 2,
};

enum mdp4_scawe_unit {
	SCAWE_FIW = 0,
	SCAWE_MN_PHASE = 1,
	SCAWE_PIXEW_WPT = 2,
};

enum mdp4_dma {
	DMA_P = 0,
	DMA_S = 1,
	DMA_E = 2,
};

#define MDP4_IWQ_OVEWWAY0_DONE					0x00000001
#define MDP4_IWQ_OVEWWAY1_DONE					0x00000002
#define MDP4_IWQ_DMA_S_DONE					0x00000004
#define MDP4_IWQ_DMA_E_DONE					0x00000008
#define MDP4_IWQ_DMA_P_DONE					0x00000010
#define MDP4_IWQ_VG1_HISTOGWAM					0x00000020
#define MDP4_IWQ_VG2_HISTOGWAM					0x00000040
#define MDP4_IWQ_PWIMAWY_VSYNC					0x00000080
#define MDP4_IWQ_PWIMAWY_INTF_UDEWWUN				0x00000100
#define MDP4_IWQ_EXTEWNAW_VSYNC					0x00000200
#define MDP4_IWQ_EXTEWNAW_INTF_UDEWWUN				0x00000400
#define MDP4_IWQ_PWIMAWY_WDPTW					0x00000800
#define MDP4_IWQ_DMA_P_HISTOGWAM				0x00020000
#define MDP4_IWQ_DMA_S_HISTOGWAM				0x04000000
#define MDP4_IWQ_OVEWWAY2_DONE					0x40000000
#define WEG_MDP4_VEWSION					0x00000000
#define MDP4_VEWSION_MINOW__MASK				0x00ff0000
#define MDP4_VEWSION_MINOW__SHIFT				16
static inwine uint32_t MDP4_VEWSION_MINOW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_VEWSION_MINOW__SHIFT) & MDP4_VEWSION_MINOW__MASK;
}
#define MDP4_VEWSION_MAJOW__MASK				0xff000000
#define MDP4_VEWSION_MAJOW__SHIFT				24
static inwine uint32_t MDP4_VEWSION_MAJOW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_VEWSION_MAJOW__SHIFT) & MDP4_VEWSION_MAJOW__MASK;
}

#define WEG_MDP4_OVWP0_KICK					0x00000004

#define WEG_MDP4_OVWP1_KICK					0x00000008

#define WEG_MDP4_OVWP2_KICK					0x000000d0

#define WEG_MDP4_DMA_P_KICK					0x0000000c

#define WEG_MDP4_DMA_S_KICK					0x00000010

#define WEG_MDP4_DMA_E_KICK					0x00000014

#define WEG_MDP4_DISP_STATUS					0x00000018

#define WEG_MDP4_DISP_INTF_SEW					0x00000038
#define MDP4_DISP_INTF_SEW_PWIM__MASK				0x00000003
#define MDP4_DISP_INTF_SEW_PWIM__SHIFT				0
static inwine uint32_t MDP4_DISP_INTF_SEW_PWIM(enum mdp4_intf vaw)
{
	wetuwn ((vaw) << MDP4_DISP_INTF_SEW_PWIM__SHIFT) & MDP4_DISP_INTF_SEW_PWIM__MASK;
}
#define MDP4_DISP_INTF_SEW_SEC__MASK				0x0000000c
#define MDP4_DISP_INTF_SEW_SEC__SHIFT				2
static inwine uint32_t MDP4_DISP_INTF_SEW_SEC(enum mdp4_intf vaw)
{
	wetuwn ((vaw) << MDP4_DISP_INTF_SEW_SEC__SHIFT) & MDP4_DISP_INTF_SEW_SEC__MASK;
}
#define MDP4_DISP_INTF_SEW_EXT__MASK				0x00000030
#define MDP4_DISP_INTF_SEW_EXT__SHIFT				4
static inwine uint32_t MDP4_DISP_INTF_SEW_EXT(enum mdp4_intf vaw)
{
	wetuwn ((vaw) << MDP4_DISP_INTF_SEW_EXT__SHIFT) & MDP4_DISP_INTF_SEW_EXT__MASK;
}
#define MDP4_DISP_INTF_SEW_DSI_VIDEO				0x00000040
#define MDP4_DISP_INTF_SEW_DSI_CMD				0x00000080

#define WEG_MDP4_WESET_STATUS					0x0000003c

#define WEG_MDP4_WEAD_CNFG					0x0000004c

#define WEG_MDP4_INTW_ENABWE					0x00000050

#define WEG_MDP4_INTW_STATUS					0x00000054

#define WEG_MDP4_INTW_CWEAW					0x00000058

#define WEG_MDP4_EBI2_WCD0					0x00000060

#define WEG_MDP4_EBI2_WCD1					0x00000064

#define WEG_MDP4_POWTMAP_MODE					0x00000070

#define WEG_MDP4_CS_CONTWOWWEW0					0x000000c0

#define WEG_MDP4_CS_CONTWOWWEW1					0x000000c4

#define WEG_MDP4_WAYEWMIXEW2_IN_CFG				0x000100f0
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE0__MASK			0x00000007
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE0__SHIFT			0
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE0(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE0__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE0__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE0_MIXEW1			0x00000008
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE1__MASK			0x00000070
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE1__SHIFT			4
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE1(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE1__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE1__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE1_MIXEW1			0x00000080
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE2__MASK			0x00000700
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE2__SHIFT			8
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE2(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE2__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE2__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE2_MIXEW1			0x00000800
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE3__MASK			0x00007000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE3__SHIFT			12
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE3(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE3__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE3__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE3_MIXEW1			0x00008000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE4__MASK			0x00070000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE4__SHIFT			16
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE4(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE4__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE4__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE4_MIXEW1			0x00080000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE5__MASK			0x00700000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE5__SHIFT			20
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE5(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE5__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE5__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE5_MIXEW1			0x00800000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE6__MASK			0x07000000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE6__SHIFT			24
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE6(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE6__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE6__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE6_MIXEW1			0x08000000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE7__MASK			0x70000000
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE7__SHIFT			28
static inwine uint32_t MDP4_WAYEWMIXEW2_IN_CFG_PIPE7(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW2_IN_CFG_PIPE7__SHIFT) & MDP4_WAYEWMIXEW2_IN_CFG_PIPE7__MASK;
}
#define MDP4_WAYEWMIXEW2_IN_CFG_PIPE7_MIXEW1			0x80000000

#define WEG_MDP4_WAYEWMIXEW_IN_CFG_UPDATE_METHOD		0x000100fc

#define WEG_MDP4_WAYEWMIXEW_IN_CFG				0x00010100
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE0__MASK			0x00000007
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE0__SHIFT			0
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE0(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE0__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE0__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE0_MIXEW1			0x00000008
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE1__MASK			0x00000070
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE1__SHIFT			4
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE1(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE1__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE1__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE1_MIXEW1			0x00000080
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE2__MASK			0x00000700
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE2__SHIFT			8
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE2(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE2__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE2__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE2_MIXEW1			0x00000800
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE3__MASK			0x00007000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE3__SHIFT			12
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE3(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE3__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE3__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE3_MIXEW1			0x00008000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE4__MASK			0x00070000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE4__SHIFT			16
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE4(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE4__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE4__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE4_MIXEW1			0x00080000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE5__MASK			0x00700000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE5__SHIFT			20
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE5(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE5__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE5__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE5_MIXEW1			0x00800000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE6__MASK			0x07000000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE6__SHIFT			24
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE6(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE6__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE6__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE6_MIXEW1			0x08000000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE7__MASK			0x70000000
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE7__SHIFT			28
static inwine uint32_t MDP4_WAYEWMIXEW_IN_CFG_PIPE7(enum mdp_mixew_stage_id vaw)
{
	wetuwn ((vaw) << MDP4_WAYEWMIXEW_IN_CFG_PIPE7__SHIFT) & MDP4_WAYEWMIXEW_IN_CFG_PIPE7__MASK;
}
#define MDP4_WAYEWMIXEW_IN_CFG_PIPE7_MIXEW1			0x80000000

#define WEG_MDP4_VG2_SWC_FOWMAT					0x00030050

#define WEG_MDP4_VG2_CONST_COWOW				0x00031008

#define WEG_MDP4_OVEWWAY_FWUSH					0x00018000
#define MDP4_OVEWWAY_FWUSH_OVWP0				0x00000001
#define MDP4_OVEWWAY_FWUSH_OVWP1				0x00000002
#define MDP4_OVEWWAY_FWUSH_VG1					0x00000004
#define MDP4_OVEWWAY_FWUSH_VG2					0x00000008
#define MDP4_OVEWWAY_FWUSH_WGB1					0x00000010
#define MDP4_OVEWWAY_FWUSH_WGB2					0x00000020

static inwine uint32_t __offset_OVWP(uint32_t idx)
{
	switch (idx) {
		case 0: wetuwn 0x00010000;
		case 1: wetuwn 0x00018000;
		case 2: wetuwn 0x00088000;
		defauwt: wetuwn INVAWID_IDX(idx);
	}
}
static inwine uint32_t WEG_MDP4_OVWP(uint32_t i0) { wetuwn 0x00000000 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_CFG(uint32_t i0) { wetuwn 0x00000004 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_SIZE(uint32_t i0) { wetuwn 0x00000008 + __offset_OVWP(i0); }
#define MDP4_OVWP_SIZE_HEIGHT__MASK				0xffff0000
#define MDP4_OVWP_SIZE_HEIGHT__SHIFT				16
static inwine uint32_t MDP4_OVWP_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_OVWP_SIZE_HEIGHT__SHIFT) & MDP4_OVWP_SIZE_HEIGHT__MASK;
}
#define MDP4_OVWP_SIZE_WIDTH__MASK				0x0000ffff
#define MDP4_OVWP_SIZE_WIDTH__SHIFT				0
static inwine uint32_t MDP4_OVWP_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_OVWP_SIZE_WIDTH__SHIFT) & MDP4_OVWP_SIZE_WIDTH__MASK;
}

static inwine uint32_t WEG_MDP4_OVWP_BASE(uint32_t i0) { wetuwn 0x0000000c + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_STWIDE(uint32_t i0) { wetuwn 0x00000010 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_OPMODE(uint32_t i0) { wetuwn 0x00000014 + __offset_OVWP(i0); }

static inwine uint32_t __offset_STAGE(uint32_t idx)
{
	switch (idx) {
		case 0: wetuwn 0x00000104;
		case 1: wetuwn 0x00000124;
		case 2: wetuwn 0x00000144;
		case 3: wetuwn 0x00000160;
		defauwt: wetuwn INVAWID_IDX(idx);
	}
}
static inwine uint32_t WEG_MDP4_OVWP_STAGE(uint32_t i0, uint32_t i1) { wetuwn 0x00000000 + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_OP(uint32_t i0, uint32_t i1) { wetuwn 0x00000000 + __offset_OVWP(i0) + __offset_STAGE(i1); }
#define MDP4_OVWP_STAGE_OP_FG_AWPHA__MASK			0x00000003
#define MDP4_OVWP_STAGE_OP_FG_AWPHA__SHIFT			0
static inwine uint32_t MDP4_OVWP_STAGE_OP_FG_AWPHA(enum mdp_awpha_type vaw)
{
	wetuwn ((vaw) << MDP4_OVWP_STAGE_OP_FG_AWPHA__SHIFT) & MDP4_OVWP_STAGE_OP_FG_AWPHA__MASK;
}
#define MDP4_OVWP_STAGE_OP_FG_INV_AWPHA				0x00000004
#define MDP4_OVWP_STAGE_OP_FG_MOD_AWPHA				0x00000008
#define MDP4_OVWP_STAGE_OP_BG_AWPHA__MASK			0x00000030
#define MDP4_OVWP_STAGE_OP_BG_AWPHA__SHIFT			4
static inwine uint32_t MDP4_OVWP_STAGE_OP_BG_AWPHA(enum mdp_awpha_type vaw)
{
	wetuwn ((vaw) << MDP4_OVWP_STAGE_OP_BG_AWPHA__SHIFT) & MDP4_OVWP_STAGE_OP_BG_AWPHA__MASK;
}
#define MDP4_OVWP_STAGE_OP_BG_INV_AWPHA				0x00000040
#define MDP4_OVWP_STAGE_OP_BG_MOD_AWPHA				0x00000080
#define MDP4_OVWP_STAGE_OP_FG_TWANSP				0x00000100
#define MDP4_OVWP_STAGE_OP_BG_TWANSP				0x00000200

static inwine uint32_t WEG_MDP4_OVWP_STAGE_FG_AWPHA(uint32_t i0, uint32_t i1) { wetuwn 0x00000004 + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_BG_AWPHA(uint32_t i0, uint32_t i1) { wetuwn 0x00000008 + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_TWANSP_WOW0(uint32_t i0, uint32_t i1) { wetuwn 0x0000000c + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_TWANSP_WOW1(uint32_t i0, uint32_t i1) { wetuwn 0x00000010 + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_TWANSP_HIGH0(uint32_t i0, uint32_t i1) { wetuwn 0x00000014 + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_TWANSP_HIGH1(uint32_t i0, uint32_t i1) { wetuwn 0x00000018 + __offset_OVWP(i0) + __offset_STAGE(i1); }

static inwine uint32_t __offset_STAGE_CO3(uint32_t idx)
{
	switch (idx) {
		case 0: wetuwn 0x00001004;
		case 1: wetuwn 0x00001404;
		case 2: wetuwn 0x00001804;
		case 3: wetuwn 0x00001b84;
		defauwt: wetuwn INVAWID_IDX(idx);
	}
}
static inwine uint32_t WEG_MDP4_OVWP_STAGE_CO3(uint32_t i0, uint32_t i1) { wetuwn 0x00000000 + __offset_OVWP(i0) + __offset_STAGE_CO3(i1); }

static inwine uint32_t WEG_MDP4_OVWP_STAGE_CO3_SEW(uint32_t i0, uint32_t i1) { wetuwn 0x00000000 + __offset_OVWP(i0) + __offset_STAGE_CO3(i1); }
#define MDP4_OVWP_STAGE_CO3_SEW_FG_AWPHA			0x00000001

static inwine uint32_t WEG_MDP4_OVWP_TWANSP_WOW0(uint32_t i0) { wetuwn 0x00000180 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_TWANSP_WOW1(uint32_t i0) { wetuwn 0x00000184 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_TWANSP_HIGH0(uint32_t i0) { wetuwn 0x00000188 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_TWANSP_HIGH1(uint32_t i0) { wetuwn 0x0000018c + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_CSC_CONFIG(uint32_t i0) { wetuwn 0x00000200 + __offset_OVWP(i0); }

static inwine uint32_t WEG_MDP4_OVWP_CSC(uint32_t i0) { wetuwn 0x00002000 + __offset_OVWP(i0); }


static inwine uint32_t WEG_MDP4_OVWP_CSC_MV(uint32_t i0, uint32_t i1) { wetuwn 0x00002400 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_MV_VAW(uint32_t i0, uint32_t i1) { wetuwn 0x00002400 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_PWE_BV(uint32_t i0, uint32_t i1) { wetuwn 0x00002500 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_PWE_BV_VAW(uint32_t i0, uint32_t i1) { wetuwn 0x00002500 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_POST_BV(uint32_t i0, uint32_t i1) { wetuwn 0x00002580 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_POST_BV_VAW(uint32_t i0, uint32_t i1) { wetuwn 0x00002580 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_PWE_WV(uint32_t i0, uint32_t i1) { wetuwn 0x00002600 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_PWE_WV_VAW(uint32_t i0, uint32_t i1) { wetuwn 0x00002600 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_POST_WV(uint32_t i0, uint32_t i1) { wetuwn 0x00002680 + __offset_OVWP(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_OVWP_CSC_POST_WV_VAW(uint32_t i0, uint32_t i1) { wetuwn 0x00002680 + __offset_OVWP(i0) + 0x4*i1; }

#define WEG_MDP4_DMA_P_OP_MODE					0x00090070

static inwine uint32_t WEG_MDP4_WUTN(uint32_t i0) { wetuwn 0x00094800 + 0x400*i0; }

static inwine uint32_t WEG_MDP4_WUTN_WUT(uint32_t i0, uint32_t i1) { wetuwn 0x00094800 + 0x400*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_WUTN_WUT_VAW(uint32_t i0, uint32_t i1) { wetuwn 0x00094800 + 0x400*i0 + 0x4*i1; }

#define WEG_MDP4_DMA_S_OP_MODE					0x000a0028

static inwine uint32_t WEG_MDP4_DMA_E_QUANT(uint32_t i0) { wetuwn 0x000b0070 + 0x4*i0; }

static inwine uint32_t __offset_DMA(enum mdp4_dma idx)
{
	switch (idx) {
		case DMA_P: wetuwn 0x00090000;
		case DMA_S: wetuwn 0x000a0000;
		case DMA_E: wetuwn 0x000b0000;
		defauwt: wetuwn INVAWID_IDX(idx);
	}
}
static inwine uint32_t WEG_MDP4_DMA(enum mdp4_dma i0) { wetuwn 0x00000000 + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_CONFIG(enum mdp4_dma i0) { wetuwn 0x00000000 + __offset_DMA(i0); }
#define MDP4_DMA_CONFIG_G_BPC__MASK				0x00000003
#define MDP4_DMA_CONFIG_G_BPC__SHIFT				0
static inwine uint32_t MDP4_DMA_CONFIG_G_BPC(enum mdp_bpc vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CONFIG_G_BPC__SHIFT) & MDP4_DMA_CONFIG_G_BPC__MASK;
}
#define MDP4_DMA_CONFIG_B_BPC__MASK				0x0000000c
#define MDP4_DMA_CONFIG_B_BPC__SHIFT				2
static inwine uint32_t MDP4_DMA_CONFIG_B_BPC(enum mdp_bpc vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CONFIG_B_BPC__SHIFT) & MDP4_DMA_CONFIG_B_BPC__MASK;
}
#define MDP4_DMA_CONFIG_W_BPC__MASK				0x00000030
#define MDP4_DMA_CONFIG_W_BPC__SHIFT				4
static inwine uint32_t MDP4_DMA_CONFIG_W_BPC(enum mdp_bpc vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CONFIG_W_BPC__SHIFT) & MDP4_DMA_CONFIG_W_BPC__MASK;
}
#define MDP4_DMA_CONFIG_PACK_AWIGN_MSB				0x00000080
#define MDP4_DMA_CONFIG_PACK__MASK				0x0000ff00
#define MDP4_DMA_CONFIG_PACK__SHIFT				8
static inwine uint32_t MDP4_DMA_CONFIG_PACK(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CONFIG_PACK__SHIFT) & MDP4_DMA_CONFIG_PACK__MASK;
}
#define MDP4_DMA_CONFIG_DEFWKW_EN				0x01000000
#define MDP4_DMA_CONFIG_DITHEW_EN				0x01000000

static inwine uint32_t WEG_MDP4_DMA_SWC_SIZE(enum mdp4_dma i0) { wetuwn 0x00000004 + __offset_DMA(i0); }
#define MDP4_DMA_SWC_SIZE_HEIGHT__MASK				0xffff0000
#define MDP4_DMA_SWC_SIZE_HEIGHT__SHIFT				16
static inwine uint32_t MDP4_DMA_SWC_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_SWC_SIZE_HEIGHT__SHIFT) & MDP4_DMA_SWC_SIZE_HEIGHT__MASK;
}
#define MDP4_DMA_SWC_SIZE_WIDTH__MASK				0x0000ffff
#define MDP4_DMA_SWC_SIZE_WIDTH__SHIFT				0
static inwine uint32_t MDP4_DMA_SWC_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_SWC_SIZE_WIDTH__SHIFT) & MDP4_DMA_SWC_SIZE_WIDTH__MASK;
}

static inwine uint32_t WEG_MDP4_DMA_SWC_BASE(enum mdp4_dma i0) { wetuwn 0x00000008 + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_SWC_STWIDE(enum mdp4_dma i0) { wetuwn 0x0000000c + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_DST_SIZE(enum mdp4_dma i0) { wetuwn 0x00000010 + __offset_DMA(i0); }
#define MDP4_DMA_DST_SIZE_HEIGHT__MASK				0xffff0000
#define MDP4_DMA_DST_SIZE_HEIGHT__SHIFT				16
static inwine uint32_t MDP4_DMA_DST_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_DST_SIZE_HEIGHT__SHIFT) & MDP4_DMA_DST_SIZE_HEIGHT__MASK;
}
#define MDP4_DMA_DST_SIZE_WIDTH__MASK				0x0000ffff
#define MDP4_DMA_DST_SIZE_WIDTH__SHIFT				0
static inwine uint32_t MDP4_DMA_DST_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_DST_SIZE_WIDTH__SHIFT) & MDP4_DMA_DST_SIZE_WIDTH__MASK;
}

static inwine uint32_t WEG_MDP4_DMA_CUWSOW_SIZE(enum mdp4_dma i0) { wetuwn 0x00000044 + __offset_DMA(i0); }
#define MDP4_DMA_CUWSOW_SIZE_WIDTH__MASK			0x0000007f
#define MDP4_DMA_CUWSOW_SIZE_WIDTH__SHIFT			0
static inwine uint32_t MDP4_DMA_CUWSOW_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CUWSOW_SIZE_WIDTH__SHIFT) & MDP4_DMA_CUWSOW_SIZE_WIDTH__MASK;
}
#define MDP4_DMA_CUWSOW_SIZE_HEIGHT__MASK			0x007f0000
#define MDP4_DMA_CUWSOW_SIZE_HEIGHT__SHIFT			16
static inwine uint32_t MDP4_DMA_CUWSOW_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CUWSOW_SIZE_HEIGHT__SHIFT) & MDP4_DMA_CUWSOW_SIZE_HEIGHT__MASK;
}

static inwine uint32_t WEG_MDP4_DMA_CUWSOW_BASE(enum mdp4_dma i0) { wetuwn 0x00000048 + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_CUWSOW_POS(enum mdp4_dma i0) { wetuwn 0x0000004c + __offset_DMA(i0); }
#define MDP4_DMA_CUWSOW_POS_X__MASK				0x0000ffff
#define MDP4_DMA_CUWSOW_POS_X__SHIFT				0
static inwine uint32_t MDP4_DMA_CUWSOW_POS_X(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CUWSOW_POS_X__SHIFT) & MDP4_DMA_CUWSOW_POS_X__MASK;
}
#define MDP4_DMA_CUWSOW_POS_Y__MASK				0xffff0000
#define MDP4_DMA_CUWSOW_POS_Y__SHIFT				16
static inwine uint32_t MDP4_DMA_CUWSOW_POS_Y(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CUWSOW_POS_Y__SHIFT) & MDP4_DMA_CUWSOW_POS_Y__MASK;
}

static inwine uint32_t WEG_MDP4_DMA_CUWSOW_BWEND_CONFIG(enum mdp4_dma i0) { wetuwn 0x00000060 + __offset_DMA(i0); }
#define MDP4_DMA_CUWSOW_BWEND_CONFIG_CUWSOW_EN			0x00000001
#define MDP4_DMA_CUWSOW_BWEND_CONFIG_FOWMAT__MASK		0x00000006
#define MDP4_DMA_CUWSOW_BWEND_CONFIG_FOWMAT__SHIFT		1
static inwine uint32_t MDP4_DMA_CUWSOW_BWEND_CONFIG_FOWMAT(enum mdp4_cuwsow_fowmat vaw)
{
	wetuwn ((vaw) << MDP4_DMA_CUWSOW_BWEND_CONFIG_FOWMAT__SHIFT) & MDP4_DMA_CUWSOW_BWEND_CONFIG_FOWMAT__MASK;
}
#define MDP4_DMA_CUWSOW_BWEND_CONFIG_TWANSP_EN			0x00000008

static inwine uint32_t WEG_MDP4_DMA_CUWSOW_BWEND_PAWAM(enum mdp4_dma i0) { wetuwn 0x00000064 + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_BWEND_TWANS_WOW(enum mdp4_dma i0) { wetuwn 0x00000068 + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_BWEND_TWANS_HIGH(enum mdp4_dma i0) { wetuwn 0x0000006c + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_FETCH_CONFIG(enum mdp4_dma i0) { wetuwn 0x00001004 + __offset_DMA(i0); }

static inwine uint32_t WEG_MDP4_DMA_CSC(enum mdp4_dma i0) { wetuwn 0x00003000 + __offset_DMA(i0); }


static inwine uint32_t WEG_MDP4_DMA_CSC_MV(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003400 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_MV_VAW(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003400 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_PWE_BV(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003500 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_PWE_BV_VAW(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003500 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_POST_BV(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003580 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_POST_BV_VAW(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003580 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_PWE_WV(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003600 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_PWE_WV_VAW(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003600 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_POST_WV(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003680 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_DMA_CSC_POST_WV_VAW(enum mdp4_dma i0, uint32_t i1) { wetuwn 0x00003680 + __offset_DMA(i0) + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE(enum mdp4_pipe i0) { wetuwn 0x00020000 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_SWC_SIZE(enum mdp4_pipe i0) { wetuwn 0x00020000 + 0x10000*i0; }
#define MDP4_PIPE_SWC_SIZE_HEIGHT__MASK				0xffff0000
#define MDP4_PIPE_SWC_SIZE_HEIGHT__SHIFT			16
static inwine uint32_t MDP4_PIPE_SWC_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_SIZE_HEIGHT__SHIFT) & MDP4_PIPE_SWC_SIZE_HEIGHT__MASK;
}
#define MDP4_PIPE_SWC_SIZE_WIDTH__MASK				0x0000ffff
#define MDP4_PIPE_SWC_SIZE_WIDTH__SHIFT				0
static inwine uint32_t MDP4_PIPE_SWC_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_SIZE_WIDTH__SHIFT) & MDP4_PIPE_SWC_SIZE_WIDTH__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_SWC_XY(enum mdp4_pipe i0) { wetuwn 0x00020004 + 0x10000*i0; }
#define MDP4_PIPE_SWC_XY_Y__MASK				0xffff0000
#define MDP4_PIPE_SWC_XY_Y__SHIFT				16
static inwine uint32_t MDP4_PIPE_SWC_XY_Y(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_XY_Y__SHIFT) & MDP4_PIPE_SWC_XY_Y__MASK;
}
#define MDP4_PIPE_SWC_XY_X__MASK				0x0000ffff
#define MDP4_PIPE_SWC_XY_X__SHIFT				0
static inwine uint32_t MDP4_PIPE_SWC_XY_X(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_XY_X__SHIFT) & MDP4_PIPE_SWC_XY_X__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_DST_SIZE(enum mdp4_pipe i0) { wetuwn 0x00020008 + 0x10000*i0; }
#define MDP4_PIPE_DST_SIZE_HEIGHT__MASK				0xffff0000
#define MDP4_PIPE_DST_SIZE_HEIGHT__SHIFT			16
static inwine uint32_t MDP4_PIPE_DST_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_DST_SIZE_HEIGHT__SHIFT) & MDP4_PIPE_DST_SIZE_HEIGHT__MASK;
}
#define MDP4_PIPE_DST_SIZE_WIDTH__MASK				0x0000ffff
#define MDP4_PIPE_DST_SIZE_WIDTH__SHIFT				0
static inwine uint32_t MDP4_PIPE_DST_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_DST_SIZE_WIDTH__SHIFT) & MDP4_PIPE_DST_SIZE_WIDTH__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_DST_XY(enum mdp4_pipe i0) { wetuwn 0x0002000c + 0x10000*i0; }
#define MDP4_PIPE_DST_XY_Y__MASK				0xffff0000
#define MDP4_PIPE_DST_XY_Y__SHIFT				16
static inwine uint32_t MDP4_PIPE_DST_XY_Y(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_DST_XY_Y__SHIFT) & MDP4_PIPE_DST_XY_Y__MASK;
}
#define MDP4_PIPE_DST_XY_X__MASK				0x0000ffff
#define MDP4_PIPE_DST_XY_X__SHIFT				0
static inwine uint32_t MDP4_PIPE_DST_XY_X(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_DST_XY_X__SHIFT) & MDP4_PIPE_DST_XY_X__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_SWCP0_BASE(enum mdp4_pipe i0) { wetuwn 0x00020010 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_SWCP1_BASE(enum mdp4_pipe i0) { wetuwn 0x00020014 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_SWCP2_BASE(enum mdp4_pipe i0) { wetuwn 0x00020018 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_SWCP3_BASE(enum mdp4_pipe i0) { wetuwn 0x0002001c + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_SWC_STWIDE_A(enum mdp4_pipe i0) { wetuwn 0x00020040 + 0x10000*i0; }
#define MDP4_PIPE_SWC_STWIDE_A_P0__MASK				0x0000ffff
#define MDP4_PIPE_SWC_STWIDE_A_P0__SHIFT			0
static inwine uint32_t MDP4_PIPE_SWC_STWIDE_A_P0(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_STWIDE_A_P0__SHIFT) & MDP4_PIPE_SWC_STWIDE_A_P0__MASK;
}
#define MDP4_PIPE_SWC_STWIDE_A_P1__MASK				0xffff0000
#define MDP4_PIPE_SWC_STWIDE_A_P1__SHIFT			16
static inwine uint32_t MDP4_PIPE_SWC_STWIDE_A_P1(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_STWIDE_A_P1__SHIFT) & MDP4_PIPE_SWC_STWIDE_A_P1__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_SWC_STWIDE_B(enum mdp4_pipe i0) { wetuwn 0x00020044 + 0x10000*i0; }
#define MDP4_PIPE_SWC_STWIDE_B_P2__MASK				0x0000ffff
#define MDP4_PIPE_SWC_STWIDE_B_P2__SHIFT			0
static inwine uint32_t MDP4_PIPE_SWC_STWIDE_B_P2(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_STWIDE_B_P2__SHIFT) & MDP4_PIPE_SWC_STWIDE_B_P2__MASK;
}
#define MDP4_PIPE_SWC_STWIDE_B_P3__MASK				0xffff0000
#define MDP4_PIPE_SWC_STWIDE_B_P3__SHIFT			16
static inwine uint32_t MDP4_PIPE_SWC_STWIDE_B_P3(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_STWIDE_B_P3__SHIFT) & MDP4_PIPE_SWC_STWIDE_B_P3__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_SSTIWE_FWAME_SIZE(enum mdp4_pipe i0) { wetuwn 0x00020048 + 0x10000*i0; }
#define MDP4_PIPE_SSTIWE_FWAME_SIZE_HEIGHT__MASK		0xffff0000
#define MDP4_PIPE_SSTIWE_FWAME_SIZE_HEIGHT__SHIFT		16
static inwine uint32_t MDP4_PIPE_SSTIWE_FWAME_SIZE_HEIGHT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SSTIWE_FWAME_SIZE_HEIGHT__SHIFT) & MDP4_PIPE_SSTIWE_FWAME_SIZE_HEIGHT__MASK;
}
#define MDP4_PIPE_SSTIWE_FWAME_SIZE_WIDTH__MASK			0x0000ffff
#define MDP4_PIPE_SSTIWE_FWAME_SIZE_WIDTH__SHIFT		0
static inwine uint32_t MDP4_PIPE_SSTIWE_FWAME_SIZE_WIDTH(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SSTIWE_FWAME_SIZE_WIDTH__SHIFT) & MDP4_PIPE_SSTIWE_FWAME_SIZE_WIDTH__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_SWC_FOWMAT(enum mdp4_pipe i0) { wetuwn 0x00020050 + 0x10000*i0; }
#define MDP4_PIPE_SWC_FOWMAT_G_BPC__MASK			0x00000003
#define MDP4_PIPE_SWC_FOWMAT_G_BPC__SHIFT			0
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_G_BPC(enum mdp_bpc vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_G_BPC__SHIFT) & MDP4_PIPE_SWC_FOWMAT_G_BPC__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_B_BPC__MASK			0x0000000c
#define MDP4_PIPE_SWC_FOWMAT_B_BPC__SHIFT			2
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_B_BPC(enum mdp_bpc vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_B_BPC__SHIFT) & MDP4_PIPE_SWC_FOWMAT_B_BPC__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_W_BPC__MASK			0x00000030
#define MDP4_PIPE_SWC_FOWMAT_W_BPC__SHIFT			4
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_W_BPC(enum mdp_bpc vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_W_BPC__SHIFT) & MDP4_PIPE_SWC_FOWMAT_W_BPC__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_A_BPC__MASK			0x000000c0
#define MDP4_PIPE_SWC_FOWMAT_A_BPC__SHIFT			6
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_A_BPC(enum mdp_bpc_awpha vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_A_BPC__SHIFT) & MDP4_PIPE_SWC_FOWMAT_A_BPC__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_AWPHA_ENABWE			0x00000100
#define MDP4_PIPE_SWC_FOWMAT_CPP__MASK				0x00000600
#define MDP4_PIPE_SWC_FOWMAT_CPP__SHIFT				9
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_CPP(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_CPP__SHIFT) & MDP4_PIPE_SWC_FOWMAT_CPP__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_WOTATED_90				0x00001000
#define MDP4_PIPE_SWC_FOWMAT_UNPACK_COUNT__MASK			0x00006000
#define MDP4_PIPE_SWC_FOWMAT_UNPACK_COUNT__SHIFT		13
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_UNPACK_COUNT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_UNPACK_COUNT__SHIFT) & MDP4_PIPE_SWC_FOWMAT_UNPACK_COUNT__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_UNPACK_TIGHT			0x00020000
#define MDP4_PIPE_SWC_FOWMAT_UNPACK_AWIGN_MSB			0x00040000
#define MDP4_PIPE_SWC_FOWMAT_FETCH_PWANES__MASK			0x00180000
#define MDP4_PIPE_SWC_FOWMAT_FETCH_PWANES__SHIFT		19
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_FETCH_PWANES(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_FETCH_PWANES__SHIFT) & MDP4_PIPE_SWC_FOWMAT_FETCH_PWANES__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_SOWID_FIWW				0x00400000
#define MDP4_PIPE_SWC_FOWMAT_CHWOMA_SAMP__MASK			0x0c000000
#define MDP4_PIPE_SWC_FOWMAT_CHWOMA_SAMP__SHIFT			26
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_CHWOMA_SAMP(enum mdp_chwoma_samp_type vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_CHWOMA_SAMP__SHIFT) & MDP4_PIPE_SWC_FOWMAT_CHWOMA_SAMP__MASK;
}
#define MDP4_PIPE_SWC_FOWMAT_FWAME_FOWMAT__MASK			0x60000000
#define MDP4_PIPE_SWC_FOWMAT_FWAME_FOWMAT__SHIFT		29
static inwine uint32_t MDP4_PIPE_SWC_FOWMAT_FWAME_FOWMAT(enum mdp4_fwame_fowmat vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_FOWMAT_FWAME_FOWMAT__SHIFT) & MDP4_PIPE_SWC_FOWMAT_FWAME_FOWMAT__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_SWC_UNPACK(enum mdp4_pipe i0) { wetuwn 0x00020054 + 0x10000*i0; }
#define MDP4_PIPE_SWC_UNPACK_EWEM0__MASK			0x000000ff
#define MDP4_PIPE_SWC_UNPACK_EWEM0__SHIFT			0
static inwine uint32_t MDP4_PIPE_SWC_UNPACK_EWEM0(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_UNPACK_EWEM0__SHIFT) & MDP4_PIPE_SWC_UNPACK_EWEM0__MASK;
}
#define MDP4_PIPE_SWC_UNPACK_EWEM1__MASK			0x0000ff00
#define MDP4_PIPE_SWC_UNPACK_EWEM1__SHIFT			8
static inwine uint32_t MDP4_PIPE_SWC_UNPACK_EWEM1(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_UNPACK_EWEM1__SHIFT) & MDP4_PIPE_SWC_UNPACK_EWEM1__MASK;
}
#define MDP4_PIPE_SWC_UNPACK_EWEM2__MASK			0x00ff0000
#define MDP4_PIPE_SWC_UNPACK_EWEM2__SHIFT			16
static inwine uint32_t MDP4_PIPE_SWC_UNPACK_EWEM2(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_UNPACK_EWEM2__SHIFT) & MDP4_PIPE_SWC_UNPACK_EWEM2__MASK;
}
#define MDP4_PIPE_SWC_UNPACK_EWEM3__MASK			0xff000000
#define MDP4_PIPE_SWC_UNPACK_EWEM3__SHIFT			24
static inwine uint32_t MDP4_PIPE_SWC_UNPACK_EWEM3(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_SWC_UNPACK_EWEM3__SHIFT) & MDP4_PIPE_SWC_UNPACK_EWEM3__MASK;
}

static inwine uint32_t WEG_MDP4_PIPE_OP_MODE(enum mdp4_pipe i0) { wetuwn 0x00020058 + 0x10000*i0; }
#define MDP4_PIPE_OP_MODE_SCAWEX_EN				0x00000001
#define MDP4_PIPE_OP_MODE_SCAWEY_EN				0x00000002
#define MDP4_PIPE_OP_MODE_SCAWEX_UNIT_SEW__MASK			0x0000000c
#define MDP4_PIPE_OP_MODE_SCAWEX_UNIT_SEW__SHIFT		2
static inwine uint32_t MDP4_PIPE_OP_MODE_SCAWEX_UNIT_SEW(enum mdp4_scawe_unit vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_OP_MODE_SCAWEX_UNIT_SEW__SHIFT) & MDP4_PIPE_OP_MODE_SCAWEX_UNIT_SEW__MASK;
}
#define MDP4_PIPE_OP_MODE_SCAWEY_UNIT_SEW__MASK			0x00000030
#define MDP4_PIPE_OP_MODE_SCAWEY_UNIT_SEW__SHIFT		4
static inwine uint32_t MDP4_PIPE_OP_MODE_SCAWEY_UNIT_SEW(enum mdp4_scawe_unit vaw)
{
	wetuwn ((vaw) << MDP4_PIPE_OP_MODE_SCAWEY_UNIT_SEW__SHIFT) & MDP4_PIPE_OP_MODE_SCAWEY_UNIT_SEW__MASK;
}
#define MDP4_PIPE_OP_MODE_SWC_YCBCW				0x00000200
#define MDP4_PIPE_OP_MODE_DST_YCBCW				0x00000400
#define MDP4_PIPE_OP_MODE_CSC_EN				0x00000800
#define MDP4_PIPE_OP_MODE_FWIP_WW				0x00002000
#define MDP4_PIPE_OP_MODE_FWIP_UD				0x00004000
#define MDP4_PIPE_OP_MODE_DITHEW_EN				0x00008000
#define MDP4_PIPE_OP_MODE_IGC_WUT_EN				0x00010000
#define MDP4_PIPE_OP_MODE_DEINT_EN				0x00040000
#define MDP4_PIPE_OP_MODE_DEINT_ODD_WEF				0x00080000

static inwine uint32_t WEG_MDP4_PIPE_PHASEX_STEP(enum mdp4_pipe i0) { wetuwn 0x0002005c + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_PHASEY_STEP(enum mdp4_pipe i0) { wetuwn 0x00020060 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_FETCH_CONFIG(enum mdp4_pipe i0) { wetuwn 0x00021004 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_SOWID_COWOW(enum mdp4_pipe i0) { wetuwn 0x00021008 + 0x10000*i0; }

static inwine uint32_t WEG_MDP4_PIPE_CSC(enum mdp4_pipe i0) { wetuwn 0x00024000 + 0x10000*i0; }


static inwine uint32_t WEG_MDP4_PIPE_CSC_MV(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024400 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_MV_VAW(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024400 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_PWE_BV(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024500 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_PWE_BV_VAW(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024500 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_POST_BV(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024580 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_POST_BV_VAW(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024580 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_PWE_WV(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024600 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_PWE_WV_VAW(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024600 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_POST_WV(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024680 + 0x10000*i0 + 0x4*i1; }

static inwine uint32_t WEG_MDP4_PIPE_CSC_POST_WV_VAW(enum mdp4_pipe i0, uint32_t i1) { wetuwn 0x00024680 + 0x10000*i0 + 0x4*i1; }

#define WEG_MDP4_WCDC						0x000c0000

#define WEG_MDP4_WCDC_ENABWE					0x000c0000

#define WEG_MDP4_WCDC_HSYNC_CTWW				0x000c0004
#define MDP4_WCDC_HSYNC_CTWW_PUWSEW__MASK			0x0000ffff
#define MDP4_WCDC_HSYNC_CTWW_PUWSEW__SHIFT			0
static inwine uint32_t MDP4_WCDC_HSYNC_CTWW_PUWSEW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_HSYNC_CTWW_PUWSEW__SHIFT) & MDP4_WCDC_HSYNC_CTWW_PUWSEW__MASK;
}
#define MDP4_WCDC_HSYNC_CTWW_PEWIOD__MASK			0xffff0000
#define MDP4_WCDC_HSYNC_CTWW_PEWIOD__SHIFT			16
static inwine uint32_t MDP4_WCDC_HSYNC_CTWW_PEWIOD(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_HSYNC_CTWW_PEWIOD__SHIFT) & MDP4_WCDC_HSYNC_CTWW_PEWIOD__MASK;
}

#define WEG_MDP4_WCDC_VSYNC_PEWIOD				0x000c0008

#define WEG_MDP4_WCDC_VSYNC_WEN					0x000c000c

#define WEG_MDP4_WCDC_DISPWAY_HCTWW				0x000c0010
#define MDP4_WCDC_DISPWAY_HCTWW_STAWT__MASK			0x0000ffff
#define MDP4_WCDC_DISPWAY_HCTWW_STAWT__SHIFT			0
static inwine uint32_t MDP4_WCDC_DISPWAY_HCTWW_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_DISPWAY_HCTWW_STAWT__SHIFT) & MDP4_WCDC_DISPWAY_HCTWW_STAWT__MASK;
}
#define MDP4_WCDC_DISPWAY_HCTWW_END__MASK			0xffff0000
#define MDP4_WCDC_DISPWAY_HCTWW_END__SHIFT			16
static inwine uint32_t MDP4_WCDC_DISPWAY_HCTWW_END(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_DISPWAY_HCTWW_END__SHIFT) & MDP4_WCDC_DISPWAY_HCTWW_END__MASK;
}

#define WEG_MDP4_WCDC_DISPWAY_VSTAWT				0x000c0014

#define WEG_MDP4_WCDC_DISPWAY_VEND				0x000c0018

#define WEG_MDP4_WCDC_ACTIVE_HCTW				0x000c001c
#define MDP4_WCDC_ACTIVE_HCTW_STAWT__MASK			0x00007fff
#define MDP4_WCDC_ACTIVE_HCTW_STAWT__SHIFT			0
static inwine uint32_t MDP4_WCDC_ACTIVE_HCTW_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_ACTIVE_HCTW_STAWT__SHIFT) & MDP4_WCDC_ACTIVE_HCTW_STAWT__MASK;
}
#define MDP4_WCDC_ACTIVE_HCTW_END__MASK				0x7fff0000
#define MDP4_WCDC_ACTIVE_HCTW_END__SHIFT			16
static inwine uint32_t MDP4_WCDC_ACTIVE_HCTW_END(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_ACTIVE_HCTW_END__SHIFT) & MDP4_WCDC_ACTIVE_HCTW_END__MASK;
}
#define MDP4_WCDC_ACTIVE_HCTW_ACTIVE_STAWT_X			0x80000000

#define WEG_MDP4_WCDC_ACTIVE_VSTAWT				0x000c0020

#define WEG_MDP4_WCDC_ACTIVE_VEND				0x000c0024

#define WEG_MDP4_WCDC_BOWDEW_CWW				0x000c0028

#define WEG_MDP4_WCDC_UNDEWFWOW_CWW				0x000c002c
#define MDP4_WCDC_UNDEWFWOW_CWW_COWOW__MASK			0x00ffffff
#define MDP4_WCDC_UNDEWFWOW_CWW_COWOW__SHIFT			0
static inwine uint32_t MDP4_WCDC_UNDEWFWOW_CWW_COWOW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_UNDEWFWOW_CWW_COWOW__SHIFT) & MDP4_WCDC_UNDEWFWOW_CWW_COWOW__MASK;
}
#define MDP4_WCDC_UNDEWFWOW_CWW_ENABWE_WECOVEWY			0x80000000

#define WEG_MDP4_WCDC_HSYNC_SKEW				0x000c0030

#define WEG_MDP4_WCDC_TEST_CNTW					0x000c0034

#define WEG_MDP4_WCDC_CTWW_POWAWITY				0x000c0038
#define MDP4_WCDC_CTWW_POWAWITY_HSYNC_WOW			0x00000001
#define MDP4_WCDC_CTWW_POWAWITY_VSYNC_WOW			0x00000002
#define MDP4_WCDC_CTWW_POWAWITY_DATA_EN_WOW			0x00000004

#define WEG_MDP4_WCDC_WVDS_INTF_CTW				0x000c2000
#define MDP4_WCDC_WVDS_INTF_CTW_MODE_SEW			0x00000004
#define MDP4_WCDC_WVDS_INTF_CTW_WGB_OUT				0x00000008
#define MDP4_WCDC_WVDS_INTF_CTW_CH_SWAP				0x00000010
#define MDP4_WCDC_WVDS_INTF_CTW_CH1_WES_BIT			0x00000020
#define MDP4_WCDC_WVDS_INTF_CTW_CH2_WES_BIT			0x00000040
#define MDP4_WCDC_WVDS_INTF_CTW_ENABWE				0x00000080
#define MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE0_EN		0x00000100
#define MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE1_EN		0x00000200
#define MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE2_EN		0x00000400
#define MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE3_EN		0x00000800
#define MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE0_EN		0x00001000
#define MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE1_EN		0x00002000
#define MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE2_EN		0x00004000
#define MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE3_EN		0x00008000
#define MDP4_WCDC_WVDS_INTF_CTW_CH1_CWK_WANE_EN			0x00010000
#define MDP4_WCDC_WVDS_INTF_CTW_CH2_CWK_WANE_EN			0x00020000

static inwine uint32_t WEG_MDP4_WCDC_WVDS_MUX_CTW(uint32_t i0) { wetuwn 0x000c2014 + 0x8*i0; }

static inwine uint32_t WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(uint32_t i0) { wetuwn 0x000c2014 + 0x8*i0; }
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0__MASK		0x000000ff
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0__SHIFT		0
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0__MASK;
}
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1__MASK		0x0000ff00
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1__SHIFT		8
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1__MASK;
}
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2__MASK		0x00ff0000
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2__SHIFT		16
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2__MASK;
}
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3__MASK		0xff000000
#define MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3__SHIFT		24
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3__MASK;
}

static inwine uint32_t WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(uint32_t i0) { wetuwn 0x000c2018 + 0x8*i0; }
#define MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4__MASK		0x000000ff
#define MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4__SHIFT		0
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4__MASK;
}
#define MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5__MASK		0x0000ff00
#define MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5__SHIFT		8
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5__MASK;
}
#define MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6__MASK		0x00ff0000
#define MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6__SHIFT		16
static inwine uint32_t MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6__SHIFT) & MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6__MASK;
}

#define WEG_MDP4_WCDC_WVDS_PHY_WESET				0x000c2034

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_0				0x000c3000

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_1				0x000c3004

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_2				0x000c3008

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_3				0x000c300c

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_5				0x000c3014

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_6				0x000c3018

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_7				0x000c301c

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_8				0x000c3020

#define WEG_MDP4_WVDS_PHY_PWW_CTWW_9				0x000c3024

#define WEG_MDP4_WVDS_PHY_PWW_WOCKED				0x000c3080

#define WEG_MDP4_WVDS_PHY_CFG2					0x000c3108

#define WEG_MDP4_WVDS_PHY_CFG0					0x000c3100
#define MDP4_WVDS_PHY_CFG0_SEWIAWIZATION_ENBWE			0x00000010
#define MDP4_WVDS_PHY_CFG0_CHANNEW0				0x00000040
#define MDP4_WVDS_PHY_CFG0_CHANNEW1				0x00000080

#define WEG_MDP4_DTV						0x000d0000

#define WEG_MDP4_DTV_ENABWE					0x000d0000

#define WEG_MDP4_DTV_HSYNC_CTWW					0x000d0004
#define MDP4_DTV_HSYNC_CTWW_PUWSEW__MASK			0x0000ffff
#define MDP4_DTV_HSYNC_CTWW_PUWSEW__SHIFT			0
static inwine uint32_t MDP4_DTV_HSYNC_CTWW_PUWSEW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_HSYNC_CTWW_PUWSEW__SHIFT) & MDP4_DTV_HSYNC_CTWW_PUWSEW__MASK;
}
#define MDP4_DTV_HSYNC_CTWW_PEWIOD__MASK			0xffff0000
#define MDP4_DTV_HSYNC_CTWW_PEWIOD__SHIFT			16
static inwine uint32_t MDP4_DTV_HSYNC_CTWW_PEWIOD(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_HSYNC_CTWW_PEWIOD__SHIFT) & MDP4_DTV_HSYNC_CTWW_PEWIOD__MASK;
}

#define WEG_MDP4_DTV_VSYNC_PEWIOD				0x000d0008

#define WEG_MDP4_DTV_VSYNC_WEN					0x000d000c

#define WEG_MDP4_DTV_DISPWAY_HCTWW				0x000d0018
#define MDP4_DTV_DISPWAY_HCTWW_STAWT__MASK			0x0000ffff
#define MDP4_DTV_DISPWAY_HCTWW_STAWT__SHIFT			0
static inwine uint32_t MDP4_DTV_DISPWAY_HCTWW_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_DISPWAY_HCTWW_STAWT__SHIFT) & MDP4_DTV_DISPWAY_HCTWW_STAWT__MASK;
}
#define MDP4_DTV_DISPWAY_HCTWW_END__MASK			0xffff0000
#define MDP4_DTV_DISPWAY_HCTWW_END__SHIFT			16
static inwine uint32_t MDP4_DTV_DISPWAY_HCTWW_END(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_DISPWAY_HCTWW_END__SHIFT) & MDP4_DTV_DISPWAY_HCTWW_END__MASK;
}

#define WEG_MDP4_DTV_DISPWAY_VSTAWT				0x000d001c

#define WEG_MDP4_DTV_DISPWAY_VEND				0x000d0020

#define WEG_MDP4_DTV_ACTIVE_HCTW				0x000d002c
#define MDP4_DTV_ACTIVE_HCTW_STAWT__MASK			0x00007fff
#define MDP4_DTV_ACTIVE_HCTW_STAWT__SHIFT			0
static inwine uint32_t MDP4_DTV_ACTIVE_HCTW_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_ACTIVE_HCTW_STAWT__SHIFT) & MDP4_DTV_ACTIVE_HCTW_STAWT__MASK;
}
#define MDP4_DTV_ACTIVE_HCTW_END__MASK				0x7fff0000
#define MDP4_DTV_ACTIVE_HCTW_END__SHIFT				16
static inwine uint32_t MDP4_DTV_ACTIVE_HCTW_END(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_ACTIVE_HCTW_END__SHIFT) & MDP4_DTV_ACTIVE_HCTW_END__MASK;
}
#define MDP4_DTV_ACTIVE_HCTW_ACTIVE_STAWT_X			0x80000000

#define WEG_MDP4_DTV_ACTIVE_VSTAWT				0x000d0030

#define WEG_MDP4_DTV_ACTIVE_VEND				0x000d0038

#define WEG_MDP4_DTV_BOWDEW_CWW					0x000d0040

#define WEG_MDP4_DTV_UNDEWFWOW_CWW				0x000d0044
#define MDP4_DTV_UNDEWFWOW_CWW_COWOW__MASK			0x00ffffff
#define MDP4_DTV_UNDEWFWOW_CWW_COWOW__SHIFT			0
static inwine uint32_t MDP4_DTV_UNDEWFWOW_CWW_COWOW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DTV_UNDEWFWOW_CWW_COWOW__SHIFT) & MDP4_DTV_UNDEWFWOW_CWW_COWOW__MASK;
}
#define MDP4_DTV_UNDEWFWOW_CWW_ENABWE_WECOVEWY			0x80000000

#define WEG_MDP4_DTV_HSYNC_SKEW					0x000d0048

#define WEG_MDP4_DTV_TEST_CNTW					0x000d004c

#define WEG_MDP4_DTV_CTWW_POWAWITY				0x000d0050
#define MDP4_DTV_CTWW_POWAWITY_HSYNC_WOW			0x00000001
#define MDP4_DTV_CTWW_POWAWITY_VSYNC_WOW			0x00000002
#define MDP4_DTV_CTWW_POWAWITY_DATA_EN_WOW			0x00000004

#define WEG_MDP4_DSI						0x000e0000

#define WEG_MDP4_DSI_ENABWE					0x000e0000

#define WEG_MDP4_DSI_HSYNC_CTWW					0x000e0004
#define MDP4_DSI_HSYNC_CTWW_PUWSEW__MASK			0x0000ffff
#define MDP4_DSI_HSYNC_CTWW_PUWSEW__SHIFT			0
static inwine uint32_t MDP4_DSI_HSYNC_CTWW_PUWSEW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_HSYNC_CTWW_PUWSEW__SHIFT) & MDP4_DSI_HSYNC_CTWW_PUWSEW__MASK;
}
#define MDP4_DSI_HSYNC_CTWW_PEWIOD__MASK			0xffff0000
#define MDP4_DSI_HSYNC_CTWW_PEWIOD__SHIFT			16
static inwine uint32_t MDP4_DSI_HSYNC_CTWW_PEWIOD(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_HSYNC_CTWW_PEWIOD__SHIFT) & MDP4_DSI_HSYNC_CTWW_PEWIOD__MASK;
}

#define WEG_MDP4_DSI_VSYNC_PEWIOD				0x000e0008

#define WEG_MDP4_DSI_VSYNC_WEN					0x000e000c

#define WEG_MDP4_DSI_DISPWAY_HCTWW				0x000e0010
#define MDP4_DSI_DISPWAY_HCTWW_STAWT__MASK			0x0000ffff
#define MDP4_DSI_DISPWAY_HCTWW_STAWT__SHIFT			0
static inwine uint32_t MDP4_DSI_DISPWAY_HCTWW_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_DISPWAY_HCTWW_STAWT__SHIFT) & MDP4_DSI_DISPWAY_HCTWW_STAWT__MASK;
}
#define MDP4_DSI_DISPWAY_HCTWW_END__MASK			0xffff0000
#define MDP4_DSI_DISPWAY_HCTWW_END__SHIFT			16
static inwine uint32_t MDP4_DSI_DISPWAY_HCTWW_END(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_DISPWAY_HCTWW_END__SHIFT) & MDP4_DSI_DISPWAY_HCTWW_END__MASK;
}

#define WEG_MDP4_DSI_DISPWAY_VSTAWT				0x000e0014

#define WEG_MDP4_DSI_DISPWAY_VEND				0x000e0018

#define WEG_MDP4_DSI_ACTIVE_HCTW				0x000e001c
#define MDP4_DSI_ACTIVE_HCTW_STAWT__MASK			0x00007fff
#define MDP4_DSI_ACTIVE_HCTW_STAWT__SHIFT			0
static inwine uint32_t MDP4_DSI_ACTIVE_HCTW_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_ACTIVE_HCTW_STAWT__SHIFT) & MDP4_DSI_ACTIVE_HCTW_STAWT__MASK;
}
#define MDP4_DSI_ACTIVE_HCTW_END__MASK				0x7fff0000
#define MDP4_DSI_ACTIVE_HCTW_END__SHIFT				16
static inwine uint32_t MDP4_DSI_ACTIVE_HCTW_END(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_ACTIVE_HCTW_END__SHIFT) & MDP4_DSI_ACTIVE_HCTW_END__MASK;
}
#define MDP4_DSI_ACTIVE_HCTW_ACTIVE_STAWT_X			0x80000000

#define WEG_MDP4_DSI_ACTIVE_VSTAWT				0x000e0020

#define WEG_MDP4_DSI_ACTIVE_VEND				0x000e0024

#define WEG_MDP4_DSI_BOWDEW_CWW					0x000e0028

#define WEG_MDP4_DSI_UNDEWFWOW_CWW				0x000e002c
#define MDP4_DSI_UNDEWFWOW_CWW_COWOW__MASK			0x00ffffff
#define MDP4_DSI_UNDEWFWOW_CWW_COWOW__SHIFT			0
static inwine uint32_t MDP4_DSI_UNDEWFWOW_CWW_COWOW(uint32_t vaw)
{
	wetuwn ((vaw) << MDP4_DSI_UNDEWFWOW_CWW_COWOW__SHIFT) & MDP4_DSI_UNDEWFWOW_CWW_COWOW__MASK;
}
#define MDP4_DSI_UNDEWFWOW_CWW_ENABWE_WECOVEWY			0x80000000

#define WEG_MDP4_DSI_HSYNC_SKEW					0x000e0030

#define WEG_MDP4_DSI_TEST_CNTW					0x000e0034

#define WEG_MDP4_DSI_CTWW_POWAWITY				0x000e0038
#define MDP4_DSI_CTWW_POWAWITY_HSYNC_WOW			0x00000001
#define MDP4_DSI_CTWW_POWAWITY_VSYNC_WOW			0x00000002
#define MDP4_DSI_CTWW_POWAWITY_DATA_EN_WOW			0x00000004


#endif /* MDP4_XMW */
