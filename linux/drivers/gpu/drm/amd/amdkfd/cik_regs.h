/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef CIK_WEGS_H
#define CIK_WEGS_H

/* if PTW32, these awe the bases fow scwatch and wds */
#define	PWIVATE_BASE(x)					((x) << 0) /* scwatch */
#define	SHAWED_BASE(x)					((x) << 16) /* WDS */
#define	PTW32						(1 << 0)
#define	AWIGNMENT_MODE(x)				((x) << 2)
#define	SH_MEM_AWIGNMENT_MODE_UNAWIGNED			3
#define	DEFAUWT_MTYPE(x)				((x) << 4)
#define	APE1_MTYPE(x)					((x) << 7)

/* vawid fow both DEFAUWT_MTYPE and APE1_MTYPE */
#define	MTYPE_CACHED_NV					0
#define	MTYPE_CACHED					1
#define	MTYPE_NONCACHED					3

#define	DEFAUWT_CP_HQD_PEWSISTENT_STATE			(0x33U << 8)
#define	PWEWOAD_WEQ					(1 << 0)

#define	MQD_CONTWOW_PWIV_STATE_EN			(1U << 8)

#define	DEFAUWT_MIN_IB_AVAIW_SIZE			(3U << 20)

#define	IB_ATC_EN					(1U << 23)

#define	QUANTUM_EN					1U
#define	QUANTUM_SCAWE_1MS				(1U << 4)
#define	QUANTUM_DUWATION(x)				((x) << 8)

#define	WPTW_BWOCK_SIZE(x)				((x) << 8)
#define	MIN_AVAIW_SIZE(x)				((x) << 20)
#define	DEFAUWT_WPTW_BWOCK_SIZE				WPTW_BWOCK_SIZE(5)
#define	DEFAUWT_MIN_AVAIW_SIZE				MIN_AVAIW_SIZE(3)

#define	PQ_ATC_EN					(1 << 23)
#define	NO_UPDATE_WPTW					(1 << 27)

#define	DOOWBEWW_OFFSET(x)				((x) << 2)
#define	DOOWBEWW_EN					(1 << 30)

#define	PWIV_STATE					(1 << 30)
#define	KMD_QUEUE					(1 << 31)

#define	AQW_ENABWE					1

#define GWBM_GFX_INDEX					0x30800

#endif
