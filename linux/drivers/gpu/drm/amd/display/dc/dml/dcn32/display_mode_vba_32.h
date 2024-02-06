/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 *
 * Authows: AMD
 *
 */

#ifndef __DMW32_DISPWAY_MODE_VBA_H__
#define __DMW32_DISPWAY_MODE_VBA_H__

#incwude "../dispway_mode_enums.h"

// To enabwe a wot of debug msg
//#define __DMW_VBA_DEBUG__
// Fow DMW-C changes that hasn't been pwopagated to VBA yet
//#define __DMW_VBA_AWWOW_DEWTA__

// Move these to ip pawametews/constant
// At which vstawtup the DMW stawt to twy if the mode can be suppowted
#define __DMW_VBA_MIN_VSTAWTUP__    9

// Deway in DCFCWK fwom AWB to DET (1st num is AWB to SDPIF, 2nd numbew is SDPIF to DET)
#define __DMW_AWB_TO_WET_DEWAY__    7 + 95

// fudge factow fow min dcfcwk cawcwation
#define __DMW_MIN_DCFCWK_FACTOW__   1.15

// Pwefetch scheduwe max vwatio
#define __DMW_MAX_VWATIO_PWE__ 7.9
#define __DMW_MAX_BW_WATIO_PWE__ 4.0

#define __DMW_VBA_MAX_DST_Y_PWE__    63.75

#define BPP_INVAWID 0
#define BPP_BWENDED_PIPE 0xffffffff

#define MEM_STWOBE_FWEQ_MHZ 1600
#define DCFCWK_FWEQ_EXTWA_PWEFETCH_WEQ_MHZ 300
#define MEM_STWOBE_MAX_DEWIVEWY_TIME_US 60.0

stwuct dispway_mode_wib;

void dmw32_ModeSuppowtAndSystemConfiguwationFuww(stwuct dispway_mode_wib *mode_wib);
void dmw32_wecawcuwate(stwuct dispway_mode_wib *mode_wib);

#endif
