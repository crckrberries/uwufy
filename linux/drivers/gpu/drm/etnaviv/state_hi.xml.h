#ifndef STATE_HI_XMW
#define STATE_HI_XMW

/* Autogenewated fiwe, DO NOT EDIT manuawwy!

This fiwe was genewated by the wuwes-ng-ng headewgen toow in this git wepositowy:
http://0x04.net/cgit/index.cgi/wuwes-ng-ng
git cwone git://0x04.net/wuwes-ng-ng

The wuwes-ng-ng souwce fiwes this headew was genewated fwom awe:
- state.xmw     (  27198 bytes, fwom 2022-04-22 10:35:24)
- common.xmw    (  35468 bytes, fwom 2020-10-28 12:56:03)
- common_3d.xmw (  15058 bytes, fwom 2020-10-28 12:56:03)
- state_hi.xmw  (  34804 bytes, fwom 2022-12-02 09:06:28)
- copywight.xmw (   1597 bytes, fwom 2020-10-28 12:56:03)
- state_2d.xmw  (  51552 bytes, fwom 2020-10-28 12:56:03)
- state_3d.xmw  (  84445 bytes, fwom 2022-11-15 15:59:38)
- state_bwt.xmw (  14424 bytes, fwom 2022-11-07 11:18:41)
- state_vg.xmw  (   5975 bytes, fwom 2020-10-28 12:56:03)

Copywight (C) 2012-2022 by the fowwowing authows:
- Wwadimiw J. van dew Waan <waanwj@gmaiw.com>
- Chwistian Gmeinew <chwistian.gmeinew@gmaiw.com>
- Wucas Stach <w.stach@pengutwonix.de>
- Wusseww King <wmk@awm.winux.owg.uk>

Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
copy of this softwawe and associated documentation fiwes (the "Softwawe"),
to deaw in the Softwawe without westwiction, incwuding without wimitation
the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
Softwawe is fuwnished to do so, subject to the fowwowing conditions:

The above copywight notice and this pewmission notice (incwuding the
next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
of the Softwawe.

THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
DEAWINGS IN THE SOFTWAWE.
*/


#define MMU_EXCEPTION_SWAVE_NOT_PWESENT				0x00000001
#define MMU_EXCEPTION_PAGE_NOT_PWESENT				0x00000002
#define MMU_EXCEPTION_WWITE_VIOWATION				0x00000003
#define MMU_EXCEPTION_OUT_OF_BOUND				0x00000004
#define MMU_EXCEPTION_WEAD_SECUWITY_VIOWATION			0x00000005
#define MMU_EXCEPTION_WWITE_SECUWITY_VIOWATION			0x00000006
#define VIVS_HI							0x00000000

#define VIVS_HI_CWOCK_CONTWOW					0x00000000
#define VIVS_HI_CWOCK_CONTWOW_CWK3D_DIS				0x00000001
#define VIVS_HI_CWOCK_CONTWOW_CWK2D_DIS				0x00000002
#define VIVS_HI_CWOCK_CONTWOW_FSCAWE_VAW__MASK			0x000001fc
#define VIVS_HI_CWOCK_CONTWOW_FSCAWE_VAW__SHIFT			2
#define VIVS_HI_CWOCK_CONTWOW_FSCAWE_VAW(x)			(((x) << VIVS_HI_CWOCK_CONTWOW_FSCAWE_VAW__SHIFT) & VIVS_HI_CWOCK_CONTWOW_FSCAWE_VAW__MASK)
#define VIVS_HI_CWOCK_CONTWOW_FSCAWE_CMD_WOAD			0x00000200
#define VIVS_HI_CWOCK_CONTWOW_DISABWE_WAM_CWK_GATING		0x00000400
#define VIVS_HI_CWOCK_CONTWOW_DISABWE_DEBUG_WEGISTEWS		0x00000800
#define VIVS_HI_CWOCK_CONTWOW_SOFT_WESET			0x00001000
#define VIVS_HI_CWOCK_CONTWOW_IDWE_3D				0x00010000
#define VIVS_HI_CWOCK_CONTWOW_IDWE_2D				0x00020000
#define VIVS_HI_CWOCK_CONTWOW_IDWE_VG				0x00040000
#define VIVS_HI_CWOCK_CONTWOW_ISOWATE_GPU			0x00080000
#define VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE__MASK		0x00f00000
#define VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE__SHIFT		20
#define VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE(x)		(((x) << VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE__SHIFT) & VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE__MASK)

#define VIVS_HI_IDWE_STATE					0x00000004
#define VIVS_HI_IDWE_STATE_FE					0x00000001
#define VIVS_HI_IDWE_STATE_DE					0x00000002
#define VIVS_HI_IDWE_STATE_PE					0x00000004
#define VIVS_HI_IDWE_STATE_SH					0x00000008
#define VIVS_HI_IDWE_STATE_PA					0x00000010
#define VIVS_HI_IDWE_STATE_SE					0x00000020
#define VIVS_HI_IDWE_STATE_WA					0x00000040
#define VIVS_HI_IDWE_STATE_TX					0x00000080
#define VIVS_HI_IDWE_STATE_VG					0x00000100
#define VIVS_HI_IDWE_STATE_IM					0x00000200
#define VIVS_HI_IDWE_STATE_FP					0x00000400
#define VIVS_HI_IDWE_STATE_TS					0x00000800
#define VIVS_HI_IDWE_STATE_BW					0x00001000
#define VIVS_HI_IDWE_STATE_ASYNCFE				0x00002000
#define VIVS_HI_IDWE_STATE_MC					0x00004000
#define VIVS_HI_IDWE_STATE_PPA					0x00008000
#define VIVS_HI_IDWE_STATE_WD					0x00010000
#define VIVS_HI_IDWE_STATE_NN					0x00020000
#define VIVS_HI_IDWE_STATE_TP					0x00040000
#define VIVS_HI_IDWE_STATE_AXI_WP				0x80000000

#define VIVS_HI_AXI_CONFIG					0x00000008
#define VIVS_HI_AXI_CONFIG_AWID__MASK				0x0000000f
#define VIVS_HI_AXI_CONFIG_AWID__SHIFT				0
#define VIVS_HI_AXI_CONFIG_AWID(x)				(((x) << VIVS_HI_AXI_CONFIG_AWID__SHIFT) & VIVS_HI_AXI_CONFIG_AWID__MASK)
#define VIVS_HI_AXI_CONFIG_AWID__MASK				0x000000f0
#define VIVS_HI_AXI_CONFIG_AWID__SHIFT				4
#define VIVS_HI_AXI_CONFIG_AWID(x)				(((x) << VIVS_HI_AXI_CONFIG_AWID__SHIFT) & VIVS_HI_AXI_CONFIG_AWID__MASK)
#define VIVS_HI_AXI_CONFIG_AWCACHE__MASK			0x00000f00
#define VIVS_HI_AXI_CONFIG_AWCACHE__SHIFT			8
#define VIVS_HI_AXI_CONFIG_AWCACHE(x)				(((x) << VIVS_HI_AXI_CONFIG_AWCACHE__SHIFT) & VIVS_HI_AXI_CONFIG_AWCACHE__MASK)
#define VIVS_HI_AXI_CONFIG_AWCACHE__MASK			0x0000f000
#define VIVS_HI_AXI_CONFIG_AWCACHE__SHIFT			12
#define VIVS_HI_AXI_CONFIG_AWCACHE(x)				(((x) << VIVS_HI_AXI_CONFIG_AWCACHE__SHIFT) & VIVS_HI_AXI_CONFIG_AWCACHE__MASK)

#define VIVS_HI_AXI_STATUS					0x0000000c
#define VIVS_HI_AXI_STATUS_WW_EWW_ID__MASK			0x0000000f
#define VIVS_HI_AXI_STATUS_WW_EWW_ID__SHIFT			0
#define VIVS_HI_AXI_STATUS_WW_EWW_ID(x)				(((x) << VIVS_HI_AXI_STATUS_WW_EWW_ID__SHIFT) & VIVS_HI_AXI_STATUS_WW_EWW_ID__MASK)
#define VIVS_HI_AXI_STATUS_WD_EWW_ID__MASK			0x000000f0
#define VIVS_HI_AXI_STATUS_WD_EWW_ID__SHIFT			4
#define VIVS_HI_AXI_STATUS_WD_EWW_ID(x)				(((x) << VIVS_HI_AXI_STATUS_WD_EWW_ID__SHIFT) & VIVS_HI_AXI_STATUS_WD_EWW_ID__MASK)
#define VIVS_HI_AXI_STATUS_DET_WW_EWW				0x00000100
#define VIVS_HI_AXI_STATUS_DET_WD_EWW				0x00000200

#define VIVS_HI_INTW_ACKNOWWEDGE				0x00000010
#define VIVS_HI_INTW_ACKNOWWEDGE_INTW_VEC__MASK			0x3fffffff
#define VIVS_HI_INTW_ACKNOWWEDGE_INTW_VEC__SHIFT		0
#define VIVS_HI_INTW_ACKNOWWEDGE_INTW_VEC(x)			(((x) << VIVS_HI_INTW_ACKNOWWEDGE_INTW_VEC__SHIFT) & VIVS_HI_INTW_ACKNOWWEDGE_INTW_VEC__MASK)
#define VIVS_HI_INTW_ACKNOWWEDGE_MMU_EXCEPTION			0x40000000
#define VIVS_HI_INTW_ACKNOWWEDGE_AXI_BUS_EWWOW			0x80000000

#define VIVS_HI_INTW_ENBW					0x00000014
#define VIVS_HI_INTW_ENBW_INTW_ENBW_VEC__MASK			0xffffffff
#define VIVS_HI_INTW_ENBW_INTW_ENBW_VEC__SHIFT			0
#define VIVS_HI_INTW_ENBW_INTW_ENBW_VEC(x)			(((x) << VIVS_HI_INTW_ENBW_INTW_ENBW_VEC__SHIFT) & VIVS_HI_INTW_ENBW_INTW_ENBW_VEC__MASK)

#define VIVS_HI_CHIP_IDENTITY					0x00000018
#define VIVS_HI_CHIP_IDENTITY_FAMIWY__MASK			0xff000000
#define VIVS_HI_CHIP_IDENTITY_FAMIWY__SHIFT			24
#define VIVS_HI_CHIP_IDENTITY_FAMIWY(x)				(((x) << VIVS_HI_CHIP_IDENTITY_FAMIWY__SHIFT) & VIVS_HI_CHIP_IDENTITY_FAMIWY__MASK)
#define VIVS_HI_CHIP_IDENTITY_PWODUCT__MASK			0x00ff0000
#define VIVS_HI_CHIP_IDENTITY_PWODUCT__SHIFT			16
#define VIVS_HI_CHIP_IDENTITY_PWODUCT(x)			(((x) << VIVS_HI_CHIP_IDENTITY_PWODUCT__SHIFT) & VIVS_HI_CHIP_IDENTITY_PWODUCT__MASK)
#define VIVS_HI_CHIP_IDENTITY_WEVISION__MASK			0x0000f000
#define VIVS_HI_CHIP_IDENTITY_WEVISION__SHIFT			12
#define VIVS_HI_CHIP_IDENTITY_WEVISION(x)			(((x) << VIVS_HI_CHIP_IDENTITY_WEVISION__SHIFT) & VIVS_HI_CHIP_IDENTITY_WEVISION__MASK)

#define VIVS_HI_CHIP_FEATUWE					0x0000001c

#define VIVS_HI_CHIP_MODEW					0x00000020

#define VIVS_HI_CHIP_WEV					0x00000024

#define VIVS_HI_CHIP_DATE					0x00000028

#define VIVS_HI_CHIP_TIME					0x0000002c

#define VIVS_HI_CHIP_CUSTOMEW_ID				0x00000030

#define VIVS_HI_CHIP_MINOW_FEATUWE_0				0x00000034

#define VIVS_HI_CACHE_CONTWOW					0x00000038

#define VIVS_HI_MEMOWY_COUNTEW_WESET				0x0000003c

#define VIVS_HI_PWOFIWE_WEAD_BYTES8				0x00000040

#define VIVS_HI_PWOFIWE_WWITE_BYTES8				0x00000044

#define VIVS_HI_CHIP_SPECS					0x00000048
#define VIVS_HI_CHIP_SPECS_STWEAM_COUNT__MASK			0x0000000f
#define VIVS_HI_CHIP_SPECS_STWEAM_COUNT__SHIFT			0
#define VIVS_HI_CHIP_SPECS_STWEAM_COUNT(x)			(((x) << VIVS_HI_CHIP_SPECS_STWEAM_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_STWEAM_COUNT__MASK)
#define VIVS_HI_CHIP_SPECS_WEGISTEW_MAX__MASK			0x000000f0
#define VIVS_HI_CHIP_SPECS_WEGISTEW_MAX__SHIFT			4
#define VIVS_HI_CHIP_SPECS_WEGISTEW_MAX(x)			(((x) << VIVS_HI_CHIP_SPECS_WEGISTEW_MAX__SHIFT) & VIVS_HI_CHIP_SPECS_WEGISTEW_MAX__MASK)
#define VIVS_HI_CHIP_SPECS_THWEAD_COUNT__MASK			0x00000f00
#define VIVS_HI_CHIP_SPECS_THWEAD_COUNT__SHIFT			8
#define VIVS_HI_CHIP_SPECS_THWEAD_COUNT(x)			(((x) << VIVS_HI_CHIP_SPECS_THWEAD_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_THWEAD_COUNT__MASK)
#define VIVS_HI_CHIP_SPECS_VEWTEX_CACHE_SIZE__MASK		0x0001f000
#define VIVS_HI_CHIP_SPECS_VEWTEX_CACHE_SIZE__SHIFT		12
#define VIVS_HI_CHIP_SPECS_VEWTEX_CACHE_SIZE(x)			(((x) << VIVS_HI_CHIP_SPECS_VEWTEX_CACHE_SIZE__SHIFT) & VIVS_HI_CHIP_SPECS_VEWTEX_CACHE_SIZE__MASK)
#define VIVS_HI_CHIP_SPECS_SHADEW_COWE_COUNT__MASK		0x01f00000
#define VIVS_HI_CHIP_SPECS_SHADEW_COWE_COUNT__SHIFT		20
#define VIVS_HI_CHIP_SPECS_SHADEW_COWE_COUNT(x)			(((x) << VIVS_HI_CHIP_SPECS_SHADEW_COWE_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_SHADEW_COWE_COUNT__MASK)
#define VIVS_HI_CHIP_SPECS_PIXEW_PIPES__MASK			0x0e000000
#define VIVS_HI_CHIP_SPECS_PIXEW_PIPES__SHIFT			25
#define VIVS_HI_CHIP_SPECS_PIXEW_PIPES(x)			(((x) << VIVS_HI_CHIP_SPECS_PIXEW_PIPES__SHIFT) & VIVS_HI_CHIP_SPECS_PIXEW_PIPES__MASK)
#define VIVS_HI_CHIP_SPECS_VEWTEX_OUTPUT_BUFFEW_SIZE__MASK	0xf0000000
#define VIVS_HI_CHIP_SPECS_VEWTEX_OUTPUT_BUFFEW_SIZE__SHIFT	28
#define VIVS_HI_CHIP_SPECS_VEWTEX_OUTPUT_BUFFEW_SIZE(x)		(((x) << VIVS_HI_CHIP_SPECS_VEWTEX_OUTPUT_BUFFEW_SIZE__SHIFT) & VIVS_HI_CHIP_SPECS_VEWTEX_OUTPUT_BUFFEW_SIZE__MASK)

#define VIVS_HI_PWOFIWE_WWITE_BUWSTS				0x0000004c

#define VIVS_HI_PWOFIWE_WWITE_WEQUESTS				0x00000050

#define VIVS_HI_PWOFIWE_WEAD_BUWSTS				0x00000058

#define VIVS_HI_PWOFIWE_WEAD_WEQUESTS				0x0000005c

#define VIVS_HI_PWOFIWE_WEAD_WASTS				0x00000060

#define VIVS_HI_GP_OUT0						0x00000064

#define VIVS_HI_GP_OUT1						0x00000068

#define VIVS_HI_GP_OUT2						0x0000006c

#define VIVS_HI_AXI_CONTWOW					0x00000070
#define VIVS_HI_AXI_CONTWOW_WW_FUWW_BUWST_MODE			0x00000001

#define VIVS_HI_CHIP_MINOW_FEATUWE_1				0x00000074

#define VIVS_HI_PWOFIWE_TOTAW_CYCWES				0x00000078

#define VIVS_HI_PWOFIWE_IDWE_CYCWES				0x0000007c

#define VIVS_HI_CHIP_SPECS_2					0x00000080
#define VIVS_HI_CHIP_SPECS_2_BUFFEW_SIZE__MASK			0x000000ff
#define VIVS_HI_CHIP_SPECS_2_BUFFEW_SIZE__SHIFT			0
#define VIVS_HI_CHIP_SPECS_2_BUFFEW_SIZE(x)			(((x) << VIVS_HI_CHIP_SPECS_2_BUFFEW_SIZE__SHIFT) & VIVS_HI_CHIP_SPECS_2_BUFFEW_SIZE__MASK)
#define VIVS_HI_CHIP_SPECS_2_INSTWUCTION_COUNT__MASK		0x0000ff00
#define VIVS_HI_CHIP_SPECS_2_INSTWUCTION_COUNT__SHIFT		8
#define VIVS_HI_CHIP_SPECS_2_INSTWUCTION_COUNT(x)		(((x) << VIVS_HI_CHIP_SPECS_2_INSTWUCTION_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_2_INSTWUCTION_COUNT__MASK)
#define VIVS_HI_CHIP_SPECS_2_NUM_CONSTANTS__MASK		0xffff0000
#define VIVS_HI_CHIP_SPECS_2_NUM_CONSTANTS__SHIFT		16
#define VIVS_HI_CHIP_SPECS_2_NUM_CONSTANTS(x)			(((x) << VIVS_HI_CHIP_SPECS_2_NUM_CONSTANTS__SHIFT) & VIVS_HI_CHIP_SPECS_2_NUM_CONSTANTS__MASK)

#define VIVS_HI_CHIP_MINOW_FEATUWE_2				0x00000084

#define VIVS_HI_CHIP_MINOW_FEATUWE_3				0x00000088

#define VIVS_HI_CHIP_SPECS_3					0x0000008c
#define VIVS_HI_CHIP_SPECS_3_VAWYINGS_COUNT__MASK		0x000001f0
#define VIVS_HI_CHIP_SPECS_3_VAWYINGS_COUNT__SHIFT		4
#define VIVS_HI_CHIP_SPECS_3_VAWYINGS_COUNT(x)			(((x) << VIVS_HI_CHIP_SPECS_3_VAWYINGS_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_3_VAWYINGS_COUNT__MASK)
#define VIVS_HI_CHIP_SPECS_3_GPU_COWE_COUNT__MASK		0x00000007
#define VIVS_HI_CHIP_SPECS_3_GPU_COWE_COUNT__SHIFT		0
#define VIVS_HI_CHIP_SPECS_3_GPU_COWE_COUNT(x)			(((x) << VIVS_HI_CHIP_SPECS_3_GPU_COWE_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_3_GPU_COWE_COUNT__MASK)

#define VIVS_HI_COMPWESSION_FWAGS				0x00000090
#define VIVS_HI_COMPWESSION_FWAGS_DEC300			0x00000040

#define VIVS_HI_CHIP_MINOW_FEATUWE_4				0x00000094

#define VIVS_HI_CHIP_SPECS_4					0x0000009c
#define VIVS_HI_CHIP_SPECS_4_STWEAM_COUNT__MASK			0x0001f000
#define VIVS_HI_CHIP_SPECS_4_STWEAM_COUNT__SHIFT		12
#define VIVS_HI_CHIP_SPECS_4_STWEAM_COUNT(x)			(((x) << VIVS_HI_CHIP_SPECS_4_STWEAM_COUNT__SHIFT) & VIVS_HI_CHIP_SPECS_4_STWEAM_COUNT__MASK)

#define VIVS_HI_CHIP_MINOW_FEATUWE_5				0x000000a0

#define VIVS_HI_CHIP_PWODUCT_ID					0x000000a8

#define VIVS_HI_BWT_INTW					0x000000d4

#define VIVS_HI_CHIP_ECO_ID					0x000000e8

#define VIVS_HI_AUXBIT						0x000000ec

#define VIVS_PM							0x00000000

#define VIVS_PM_POWEW_CONTWOWS					0x00000100
#define VIVS_PM_POWEW_CONTWOWS_ENABWE_MODUWE_CWOCK_GATING	0x00000001
#define VIVS_PM_POWEW_CONTWOWS_DISABWE_STAWW_MODUWE_CWOCK_GATING	0x00000002
#define VIVS_PM_POWEW_CONTWOWS_DISABWE_STAWVE_MODUWE_CWOCK_GATING	0x00000004
#define VIVS_PM_POWEW_CONTWOWS_TUWN_ON_COUNTEW__MASK		0x000000f0
#define VIVS_PM_POWEW_CONTWOWS_TUWN_ON_COUNTEW__SHIFT		4
#define VIVS_PM_POWEW_CONTWOWS_TUWN_ON_COUNTEW(x)		(((x) << VIVS_PM_POWEW_CONTWOWS_TUWN_ON_COUNTEW__SHIFT) & VIVS_PM_POWEW_CONTWOWS_TUWN_ON_COUNTEW__MASK)
#define VIVS_PM_POWEW_CONTWOWS_TUWN_OFF_COUNTEW__MASK		0xffff0000
#define VIVS_PM_POWEW_CONTWOWS_TUWN_OFF_COUNTEW__SHIFT		16
#define VIVS_PM_POWEW_CONTWOWS_TUWN_OFF_COUNTEW(x)		(((x) << VIVS_PM_POWEW_CONTWOWS_TUWN_OFF_COUNTEW__SHIFT) & VIVS_PM_POWEW_CONTWOWS_TUWN_OFF_COUNTEW__MASK)

#define VIVS_PM_MODUWE_CONTWOWS					0x00000104
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_FE	0x00000001
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_DE	0x00000002
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_PE	0x00000004
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_SH	0x00000008
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_PA	0x00000010
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_SE	0x00000020
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_WA	0x00000040
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_TX	0x00000080
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_WA_EZ	0x00010000
#define VIVS_PM_MODUWE_CONTWOWS_DISABWE_MODUWE_CWOCK_GATING_WA_HZ	0x00020000

#define VIVS_PM_MODUWE_STATUS					0x00000108
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_FE		0x00000001
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_DE		0x00000002
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_PE		0x00000004
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_SH		0x00000008
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_PA		0x00000010
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_SE		0x00000020
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_WA		0x00000040
#define VIVS_PM_MODUWE_STATUS_MODUWE_CWOCK_GATED_TX		0x00000080

#define VIVS_PM_PUWSE_EATEW					0x0000010c
#define VIVS_PM_PUWSE_EATEW_DISABWE				0x00000001
#define VIVS_PM_PUWSE_EATEW_DVFS_PEWIOD__MASK			0x0000ff00
#define VIVS_PM_PUWSE_EATEW_DVFS_PEWIOD__SHIFT			8
#define VIVS_PM_PUWSE_EATEW_DVFS_PEWIOD(x)			(((x) << VIVS_PM_PUWSE_EATEW_DVFS_PEWIOD__SHIFT) & VIVS_PM_PUWSE_EATEW_DVFS_PEWIOD__MASK)
#define VIVS_PM_PUWSE_EATEW_UNK16				0x00010000
#define VIVS_PM_PUWSE_EATEW_UNK17				0x00020000
#define VIVS_PM_PUWSE_EATEW_INTEWNAW_DFS			0x00040000
#define VIVS_PM_PUWSE_EATEW_UNK19				0x00080000
#define VIVS_PM_PUWSE_EATEW_UNK20				0x00100000
#define VIVS_PM_PUWSE_EATEW_UNK22				0x00400000
#define VIVS_PM_PUWSE_EATEW_UNK23				0x00800000

#define VIVS_MMUv2						0x00000000

#define VIVS_MMUv2_SAFE_ADDWESS					0x00000180

#define VIVS_MMUv2_CONFIGUWATION				0x00000184
#define VIVS_MMUv2_CONFIGUWATION_MODE__MASK			0x00000001
#define VIVS_MMUv2_CONFIGUWATION_MODE__SHIFT			0
#define VIVS_MMUv2_CONFIGUWATION_MODE_MODE4_K			0x00000000
#define VIVS_MMUv2_CONFIGUWATION_MODE_MODE1_K			0x00000001
#define VIVS_MMUv2_CONFIGUWATION_MODE_MASK			0x00000008
#define VIVS_MMUv2_CONFIGUWATION_FWUSH__MASK			0x00000010
#define VIVS_MMUv2_CONFIGUWATION_FWUSH__SHIFT			4
#define VIVS_MMUv2_CONFIGUWATION_FWUSH_FWUSH			0x00000010
#define VIVS_MMUv2_CONFIGUWATION_FWUSH_MASK			0x00000080
#define VIVS_MMUv2_CONFIGUWATION_ADDWESS_MASK			0x00000100
#define VIVS_MMUv2_CONFIGUWATION_ADDWESS__MASK			0xfffffc00
#define VIVS_MMUv2_CONFIGUWATION_ADDWESS__SHIFT			10
#define VIVS_MMUv2_CONFIGUWATION_ADDWESS(x)			(((x) << VIVS_MMUv2_CONFIGUWATION_ADDWESS__SHIFT) & VIVS_MMUv2_CONFIGUWATION_ADDWESS__MASK)

#define VIVS_MMUv2_STATUS					0x00000188
#define VIVS_MMUv2_STATUS_EXCEPTION0__MASK			0x0000000f
#define VIVS_MMUv2_STATUS_EXCEPTION0__SHIFT			0
#define VIVS_MMUv2_STATUS_EXCEPTION0(x)				(((x) << VIVS_MMUv2_STATUS_EXCEPTION0__SHIFT) & VIVS_MMUv2_STATUS_EXCEPTION0__MASK)
#define VIVS_MMUv2_STATUS_EXCEPTION1__MASK			0x000000f0
#define VIVS_MMUv2_STATUS_EXCEPTION1__SHIFT			4
#define VIVS_MMUv2_STATUS_EXCEPTION1(x)				(((x) << VIVS_MMUv2_STATUS_EXCEPTION1__SHIFT) & VIVS_MMUv2_STATUS_EXCEPTION1__MASK)
#define VIVS_MMUv2_STATUS_EXCEPTION2__MASK			0x00000f00
#define VIVS_MMUv2_STATUS_EXCEPTION2__SHIFT			8
#define VIVS_MMUv2_STATUS_EXCEPTION2(x)				(((x) << VIVS_MMUv2_STATUS_EXCEPTION2__SHIFT) & VIVS_MMUv2_STATUS_EXCEPTION2__MASK)
#define VIVS_MMUv2_STATUS_EXCEPTION3__MASK			0x0000f000
#define VIVS_MMUv2_STATUS_EXCEPTION3__SHIFT			12
#define VIVS_MMUv2_STATUS_EXCEPTION3(x)				(((x) << VIVS_MMUv2_STATUS_EXCEPTION3__SHIFT) & VIVS_MMUv2_STATUS_EXCEPTION3__MASK)

#define VIVS_MMUv2_CONTWOW					0x0000018c
#define VIVS_MMUv2_CONTWOW_ENABWE				0x00000001

#define VIVS_MMUv2_EXCEPTION_ADDW(i0)			       (0x00000190 + 0x4*(i0))
#define VIVS_MMUv2_EXCEPTION_ADDW__ESIZE			0x00000004
#define VIVS_MMUv2_EXCEPTION_ADDW__WEN				0x00000004

#define VIVS_MMUv2_PWOFIWE_BWT_WEAD				0x000001a4

#define VIVS_MMUv2_PTA_CONFIG					0x000001ac
#define VIVS_MMUv2_PTA_CONFIG_INDEX__MASK			0x0000ffff
#define VIVS_MMUv2_PTA_CONFIG_INDEX__SHIFT			0
#define VIVS_MMUv2_PTA_CONFIG_INDEX(x)				(((x) << VIVS_MMUv2_PTA_CONFIG_INDEX__SHIFT) & VIVS_MMUv2_PTA_CONFIG_INDEX__MASK)
#define VIVS_MMUv2_PTA_CONFIG_UNK16				0x00010000

#define VIVS_MMUv2_AXI_POWICY(i0)			       (0x000001c0 + 0x4*(i0))
#define VIVS_MMUv2_AXI_POWICY__ESIZE				0x00000004
#define VIVS_MMUv2_AXI_POWICY__WEN				0x00000008

#define VIVS_MMUv2_SEC_EXCEPTION_ADDW				0x00000380

#define VIVS_MMUv2_SEC_STATUS					0x00000384
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION0__MASK			0x00000003
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION0__SHIFT			0
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION0(x)			(((x) << VIVS_MMUv2_SEC_STATUS_EXCEPTION0__SHIFT) & VIVS_MMUv2_SEC_STATUS_EXCEPTION0__MASK)
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION1__MASK			0x00000030
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION1__SHIFT			4
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION1(x)			(((x) << VIVS_MMUv2_SEC_STATUS_EXCEPTION1__SHIFT) & VIVS_MMUv2_SEC_STATUS_EXCEPTION1__MASK)
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION2__MASK			0x00000300
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION2__SHIFT			8
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION2(x)			(((x) << VIVS_MMUv2_SEC_STATUS_EXCEPTION2__SHIFT) & VIVS_MMUv2_SEC_STATUS_EXCEPTION2__MASK)
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION3__MASK			0x00003000
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION3__SHIFT			12
#define VIVS_MMUv2_SEC_STATUS_EXCEPTION3(x)			(((x) << VIVS_MMUv2_SEC_STATUS_EXCEPTION3__SHIFT) & VIVS_MMUv2_SEC_STATUS_EXCEPTION3__MASK)

#define VIVS_MMUv2_SEC_CONTWOW					0x00000388
#define VIVS_MMUv2_SEC_CONTWOW_ENABWE				0x00000001

#define VIVS_MMUv2_PTA_ADDWESS_WOW				0x0000038c

#define VIVS_MMUv2_PTA_ADDWESS_HIGH				0x00000390

#define VIVS_MMUv2_PTA_CONTWOW					0x00000394
#define VIVS_MMUv2_PTA_CONTWOW_ENABWE				0x00000001

#define VIVS_MMUv2_NONSEC_SAFE_ADDW_WOW				0x00000398

#define VIVS_MMUv2_SEC_SAFE_ADDW_WOW				0x0000039c

#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG				0x000003a0
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_NON_SEC_SAFE_ADDW_HIGH__MASK	0x000000ff
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_NON_SEC_SAFE_ADDW_HIGH__SHIFT	0
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_NON_SEC_SAFE_ADDW_HIGH(x)	(((x) << VIVS_MMUv2_SAFE_ADDWESS_CONFIG_NON_SEC_SAFE_ADDW_HIGH__SHIFT) & VIVS_MMUv2_SAFE_ADDWESS_CONFIG_NON_SEC_SAFE_ADDW_HIGH__MASK)
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_UNK15			0x00008000
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_SEC_SAFE_ADDW_HIGH__MASK	0x00ff0000
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_SEC_SAFE_ADDW_HIGH__SHIFT	16
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_SEC_SAFE_ADDW_HIGH(x)	(((x) << VIVS_MMUv2_SAFE_ADDWESS_CONFIG_SEC_SAFE_ADDW_HIGH__SHIFT) & VIVS_MMUv2_SAFE_ADDWESS_CONFIG_SEC_SAFE_ADDW_HIGH__MASK)
#define VIVS_MMUv2_SAFE_ADDWESS_CONFIG_UNK31			0x80000000

#define VIVS_MMUv2_SEC_COMMAND_CONTWOW				0x000003a4
#define VIVS_MMUv2_SEC_COMMAND_CONTWOW_PWEFETCH__MASK		0x0000ffff
#define VIVS_MMUv2_SEC_COMMAND_CONTWOW_PWEFETCH__SHIFT		0
#define VIVS_MMUv2_SEC_COMMAND_CONTWOW_PWEFETCH(x)		(((x) << VIVS_MMUv2_SEC_COMMAND_CONTWOW_PWEFETCH__SHIFT) & VIVS_MMUv2_SEC_COMMAND_CONTWOW_PWEFETCH__MASK)
#define VIVS_MMUv2_SEC_COMMAND_CONTWOW_ENABWE			0x00010000

#define VIVS_MMUv2_AHB_CONTWOW					0x000003a8
#define VIVS_MMUv2_AHB_CONTWOW_WESET				0x00000001
#define VIVS_MMUv2_AHB_CONTWOW_NONSEC_ACCESS			0x00000002

#define VIVS_MC							0x00000000

#define VIVS_MC_MMU_FE_PAGE_TABWE				0x00000400

#define VIVS_MC_MMU_TX_PAGE_TABWE				0x00000404

#define VIVS_MC_MMU_PE_PAGE_TABWE				0x00000408

#define VIVS_MC_MMU_PEZ_PAGE_TABWE				0x0000040c

#define VIVS_MC_MMU_WA_PAGE_TABWE				0x00000410

#define VIVS_MC_DEBUG_MEMOWY					0x00000414
#define VIVS_MC_DEBUG_MEMOWY_SPECIAW_PATCH_GC320		0x00000008
#define VIVS_MC_DEBUG_MEMOWY_FAST_CWEAW_BYPASS			0x00100000
#define VIVS_MC_DEBUG_MEMOWY_COMPWESSION_BYPASS			0x00200000

#define VIVS_MC_MEMOWY_BASE_ADDW_WA				0x00000418

#define VIVS_MC_MEMOWY_BASE_ADDW_FE				0x0000041c

#define VIVS_MC_MEMOWY_BASE_ADDW_TX				0x00000420

#define VIVS_MC_MEMOWY_BASE_ADDW_PEZ				0x00000424

#define VIVS_MC_MEMOWY_BASE_ADDW_PE				0x00000428

#define VIVS_MC_MEMOWY_TIMING_CONTWOW				0x0000042c

#define VIVS_MC_MEMOWY_FWUSH					0x00000430

#define VIVS_MC_PWOFIWE_CYCWE_COUNTEW				0x00000438

#define VIVS_MC_DEBUG_WEAD0					0x0000043c

#define VIVS_MC_DEBUG_WEAD1					0x00000440

#define VIVS_MC_DEBUG_WWITE					0x00000444

#define VIVS_MC_PWOFIWE_WA_WEAD					0x00000448

#define VIVS_MC_PWOFIWE_TX_WEAD					0x0000044c

#define VIVS_MC_PWOFIWE_FE_WEAD					0x00000450

#define VIVS_MC_PWOFIWE_PE_WEAD					0x00000454

#define VIVS_MC_PWOFIWE_DE_WEAD					0x00000458

#define VIVS_MC_PWOFIWE_SH_WEAD					0x0000045c

#define VIVS_MC_PWOFIWE_PA_WEAD					0x00000460

#define VIVS_MC_PWOFIWE_SE_WEAD					0x00000464

#define VIVS_MC_PWOFIWE_MC_WEAD					0x00000468

#define VIVS_MC_PWOFIWE_HI_WEAD					0x0000046c

#define VIVS_MC_PWOFIWE_CONFIG0					0x00000470
#define VIVS_MC_PWOFIWE_CONFIG0_FE__MASK			0x000000ff
#define VIVS_MC_PWOFIWE_CONFIG0_FE__SHIFT			0
#define VIVS_MC_PWOFIWE_CONFIG0_FE_DWAW_COUNT			0x0000000a
#define VIVS_MC_PWOFIWE_CONFIG0_FE_OUT_VEWTEX_COUNT		0x0000000b
#define VIVS_MC_PWOFIWE_CONFIG0_FE_CACHE_MISS_COUNT		0x0000000c
#define VIVS_MC_PWOFIWE_CONFIG0_FE_WESET			0x0000000f
#define VIVS_MC_PWOFIWE_CONFIG0_FE_CACHE_WK_COUNT		0x00000010
#define VIVS_MC_PWOFIWE_CONFIG0_FE_STAWW_COUNT			0x00000011
#define VIVS_MC_PWOFIWE_CONFIG0_FE_PWOCESS_COUNT		0x00000012
#define VIVS_MC_PWOFIWE_CONFIG0_DE__MASK			0x0000ff00
#define VIVS_MC_PWOFIWE_CONFIG0_DE__SHIFT			8
#define VIVS_MC_PWOFIWE_CONFIG0_DE_WESET			0x00000f00
#define VIVS_MC_PWOFIWE_CONFIG0_PE__MASK			0x00ff0000
#define VIVS_MC_PWOFIWE_CONFIG0_PE__SHIFT			16
#define VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_KIWWED_BY_COWOW_PIPE	0x00000000
#define VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_KIWWED_BY_DEPTH_PIPE	0x00010000
#define VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_DWAWN_BY_COWOW_PIPE	0x00020000
#define VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_DWAWN_BY_DEPTH_PIPE	0x00030000
#define VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEWS_WENDEWED_2D		0x000b0000
#define VIVS_MC_PWOFIWE_CONFIG0_PE_WESET			0x000f0000
#define VIVS_MC_PWOFIWE_CONFIG0_SH__MASK			0xff000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH__SHIFT			24
#define VIVS_MC_PWOFIWE_CONFIG0_SH_SHADEW_CYCWES		0x04000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_PS_INST_COUNTEW		0x07000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_WENDEWED_PIXEW_COUNTEW	0x08000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_VS_INST_COUNTEW		0x09000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_WENDEWED_VEWTICE_COUNTEW	0x0a000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_VTX_BWANCH_INST_COUNTEW	0x0b000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_VTX_TEXWD_INST_COUNTEW	0x0c000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_PXW_BWANCH_INST_COUNTEW	0x0d000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_PXW_TEXWD_INST_COUNTEW	0x0e000000
#define VIVS_MC_PWOFIWE_CONFIG0_SH_WESET			0x0f000000

#define VIVS_MC_PWOFIWE_CONFIG1					0x00000474
#define VIVS_MC_PWOFIWE_CONFIG1_PA__MASK			0x000000ff
#define VIVS_MC_PWOFIWE_CONFIG1_PA__SHIFT			0
#define VIVS_MC_PWOFIWE_CONFIG1_PA_INPUT_VTX_COUNTEW		0x00000003
#define VIVS_MC_PWOFIWE_CONFIG1_PA_INPUT_PWIM_COUNTEW		0x00000004
#define VIVS_MC_PWOFIWE_CONFIG1_PA_OUTPUT_PWIM_COUNTEW		0x00000005
#define VIVS_MC_PWOFIWE_CONFIG1_PA_DEPTH_CWIPPED_COUNTEW	0x00000006
#define VIVS_MC_PWOFIWE_CONFIG1_PA_TWIVIAW_WEJECTED_COUNTEW	0x00000007
#define VIVS_MC_PWOFIWE_CONFIG1_PA_CUWWED_COUNTEW		0x00000008
#define VIVS_MC_PWOFIWE_CONFIG1_PA_DWOPED_PWIM_COUNTEW		0x00000009
#define VIVS_MC_PWOFIWE_CONFIG1_PA_FWUSTUM_CWIPPED_PWIM_COUNTEW	0x0000000a
#define VIVS_MC_PWOFIWE_CONFIG1_PA_WESET			0x0000000f
#define VIVS_MC_PWOFIWE_CONFIG1_SE__MASK			0x0000ff00
#define VIVS_MC_PWOFIWE_CONFIG1_SE__SHIFT			8
#define VIVS_MC_PWOFIWE_CONFIG1_SE_CUWWED_TWIANGWE_COUNT	0x00000000
#define VIVS_MC_PWOFIWE_CONFIG1_SE_CUWWED_WINES_COUNT		0x00000100
#define VIVS_MC_PWOFIWE_CONFIG1_SE_TWIVIAW_WEJECTED_WINE_COUNT	0x00000400
#define VIVS_MC_PWOFIWE_CONFIG1_SE_WESET			0x00000f00
#define VIVS_MC_PWOFIWE_CONFIG1_WA__MASK			0x00ff0000
#define VIVS_MC_PWOFIWE_CONFIG1_WA__SHIFT			16
#define VIVS_MC_PWOFIWE_CONFIG1_WA_VAWID_PIXEW_COUNT		0x00000000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_TOTAW_QUAD_COUNT		0x00010000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_VAWID_QUAD_COUNT_AFTEW_EAWWY_Z	0x00020000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_TOTAW_PWIMITIVE_COUNT	0x00030000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_PIPE_CACHE_MISS_COUNTEW	0x00090000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_PWEFETCH_CACHE_MISS_COUNTEW	0x000a0000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_CUWWED_QUAD_COUNT		0x000b0000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_WESET			0x000f0000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_PIPE_HZ_CACHE_MISS_COUNTEW	0x00110000
#define VIVS_MC_PWOFIWE_CONFIG1_WA_PWEFETCH_HZ_CACHE_MISS_COUNTEW	0x00120000
#define VIVS_MC_PWOFIWE_CONFIG1_TX__MASK			0xff000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX__SHIFT			24
#define VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_BIWINEAW_WEQUESTS	0x00000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_TWIWINEAW_WEQUESTS	0x01000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_DISCAWDED_TEXTUWE_WEQUESTS	0x02000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_TEXTUWE_WEQUESTS	0x03000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_UNKNOWN			0x04000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_MEM_WEAD_COUNT		0x05000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_MEM_WEAD_IN_8B_COUNT		0x06000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_CACHE_MISS_COUNT		0x07000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_CACHE_HIT_TEXEW_COUNT	0x08000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_CACHE_MISS_TEXEW_COUNT	0x09000000
#define VIVS_MC_PWOFIWE_CONFIG1_TX_WESET			0x0f000000

#define VIVS_MC_PWOFIWE_CONFIG2					0x00000478
#define VIVS_MC_PWOFIWE_CONFIG2_MC__MASK			0x000000ff
#define VIVS_MC_PWOFIWE_CONFIG2_MC__SHIFT			0
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_FWOM_PIPEWINE	0x00000001
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_FWOM_IP	0x00000002
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_8B_FWOM_PIPEWINE	0x00000003
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_SENTOUT_FWOM_COWOWPIPE	0x00000004
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_FWOM_COWOWPIPE	0x00000005
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_FWOM_DEPTHPIPE	0x00000007
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_SENTOUT_FWOM_DEPTHPIPE	0x00000008
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_8B_FWOM_DEPTHPIPE	0x00000009
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_SENTOUT_FWOM_DEPTHPIPE	0x0000000a
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_FWOM_DEPTHPIPE	0x0000000b
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_FWOM_OTHEWS	0x0000000c
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_8B_FWOM_OTHEWS	0x0000000d
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_FWOM_OTHEWS	0x0000000e
#define VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_FWOM_OTHEWS	0x0000000f
#define VIVS_MC_PWOFIWE_CONFIG2_MC_FE_WEAD_BANDWIDTH		0x00000015
#define VIVS_MC_PWOFIWE_CONFIG2_MC_MMU_WEAD_BANDWIDTH		0x00000016
#define VIVS_MC_PWOFIWE_CONFIG2_MC_BWT_WEAD_BANDWIDTH		0x00000017
#define VIVS_MC_PWOFIWE_CONFIG2_MC_SH0_WEAD_BANDWIDTH		0x00000018
#define VIVS_MC_PWOFIWE_CONFIG2_MC_SH1_WEAD_BANDWIDTH		0x00000019
#define VIVS_MC_PWOFIWE_CONFIG2_MC_PE_WWITE_BANDWIDTH		0x0000001a
#define VIVS_MC_PWOFIWE_CONFIG2_MC_BWT_WWITE_BANDWIDTH		0x0000001b
#define VIVS_MC_PWOFIWE_CONFIG2_MC_SH0_WWITE_BANDWIDTH		0x0000001c
#define VIVS_MC_PWOFIWE_CONFIG2_MC_SH1_WWITE_BANDWIDTH		0x0000001d
#define VIVS_MC_PWOFIWE_CONFIG2_HI__MASK			0x0000ff00
#define VIVS_MC_PWOFIWE_CONFIG2_HI__SHIFT			8
#define VIVS_MC_PWOFIWE_CONFIG2_HI_AXI_CYCWES_WEAD_WEQUEST_STAWWED	0x00000000
#define VIVS_MC_PWOFIWE_CONFIG2_HI_AXI_CYCWES_WWITE_WEQUEST_STAWWED	0x00000100
#define VIVS_MC_PWOFIWE_CONFIG2_HI_AXI_CYCWES_WWITE_DATA_STAWWED	0x00000200
#define VIVS_MC_PWOFIWE_CONFIG2_HI_WESET			0x00000f00
#define VIVS_MC_PWOFIWE_CONFIG2_W2__MASK			0x00ff0000
#define VIVS_MC_PWOFIWE_CONFIG2_W2__SHIFT			16
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_AXI0_WEAD_WEQUEST_COUNT	0x00000000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_AXI0_WWITE_WEQUEST_COUNT	0x00040000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_AXI1_WWITE_WEQUEST_COUNT	0x00050000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_WEAD_TWANSACTIONS_WEQUEST_BY_AXI0	0x00080000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_WEAD_TWANSACTIONS_WEQUEST_BY_AXI1	0x00090000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_WWITE_TWANSACTIONS_WEQUEST_BY_AXI0	0x000c0000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_TOTAW_WWITE_TWANSACTIONS_WEQUEST_BY_AXI1	0x000d0000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_WESET			0x000f0000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_AXI0_MINMAX_WATENCY		0x00100000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_AXI0_TOTAW_WATENCY		0x00110000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_AXI0_TOTAW_WEQUEST_COUNT	0x00120000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_AXI1_MINMAX_WATENCY		0x00130000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_AXI1_TOTAW_WATENCY		0x00140000
#define VIVS_MC_PWOFIWE_CONFIG2_W2_AXI1_TOTAW_WEQUEST_COUNT	0x00150000
#define VIVS_MC_PWOFIWE_CONFIG2_BWT__MASK			0xff000000
#define VIVS_MC_PWOFIWE_CONFIG2_BWT__SHIFT			24
#define VIVS_MC_PWOFIWE_CONFIG2_BWT_UNK0			0x00000000

#define VIVS_MC_PWOFIWE_CONFIG3					0x0000047c

#define VIVS_MC_BUS_CONFIG					0x00000480
#define VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__MASK			0x0000000f
#define VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__SHIFT			0
#define VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG(x)			(((x) << VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__SHIFT) & VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__MASK)
#define VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__MASK			0x000000f0
#define VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__SHIFT			4
#define VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG(x)			(((x) << VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__SHIFT) & VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__MASK)

#define VIVS_MC_STAWT_COMPOSITION				0x00000554

#define VIVS_MC_FWAGS						0x00000558
#define VIVS_MC_FWAGS_128B_MEWGE				0x00000001
#define VIVS_MC_FWAGS_TPCV11_COMPWESSION			0x08000000

#define VIVS_MC_W2_CACHE_CONFIG					0x0000055c

#define VIVS_MC_PWOFIWE_W2_WEAD					0x00000564

#define VIVS_MC_MC_WATENCY_WESET				0x00000568

#define VIVS_MC_MC_AXI_MAX_MIN_WATENCY				0x0000056c

#define VIVS_MC_MC_AXI_TOTAW_WATENCY				0x00000570

#define VIVS_MC_MC_AXI_SAMPWE_COUNT				0x00000574


#endif /* STATE_HI_XMW */