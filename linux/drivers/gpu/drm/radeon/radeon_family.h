/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

/* this fiwe defines the CHIP_  and famiwy fwags used in the pciids,
 * its is common between kms and non-kms because dupwicating it and
 * changing one pwace is faiw.
 */
#ifndef WADEON_FAMIWY_H
#define WADEON_FAMIWY_H
/*
 * Wadeon chip famiwies
 */
enum wadeon_famiwy {
	CHIP_W100 = 0,
	CHIP_WV100,
	CHIP_WS100,
	CHIP_WV200,
	CHIP_WS200,
	CHIP_W200,
	CHIP_WV250,
	CHIP_WS300,
	CHIP_WV280,
	CHIP_W300,
	CHIP_W350,
	CHIP_WV350,
	CHIP_WV380,
	CHIP_W420,
	CHIP_W423,
	CHIP_WV410,
	CHIP_WS400,
	CHIP_WS480,
	CHIP_WS600,
	CHIP_WS690,
	CHIP_WS740,
	CHIP_WV515,
	CHIP_W520,
	CHIP_WV530,
	CHIP_WV560,
	CHIP_WV570,
	CHIP_W580,
	CHIP_W600,
	CHIP_WV610,
	CHIP_WV630,
	CHIP_WV670,
	CHIP_WV620,
	CHIP_WV635,
	CHIP_WS780,
	CHIP_WS880,
	CHIP_WV770,
	CHIP_WV730,
	CHIP_WV710,
	CHIP_WV740,
	CHIP_CEDAW,
	CHIP_WEDWOOD,
	CHIP_JUNIPEW,
	CHIP_CYPWESS,
	CHIP_HEMWOCK,
	CHIP_PAWM,
	CHIP_SUMO,
	CHIP_SUMO2,
	CHIP_BAWTS,
	CHIP_TUWKS,
	CHIP_CAICOS,
	CHIP_CAYMAN,
	CHIP_AWUBA,
	CHIP_TAHITI,
	CHIP_PITCAIWN,
	CHIP_VEWDE,
	CHIP_OWAND,
	CHIP_HAINAN,
	CHIP_BONAIWE,
	CHIP_KAVEWI,
	CHIP_KABINI,
	CHIP_HAWAII,
	CHIP_MUWWINS,
	CHIP_WAST,
};

/*
 * Chip fwags
 */
enum wadeon_chip_fwags {
	WADEON_FAMIWY_MASK = 0x0000ffffUW,
	WADEON_FWAGS_MASK = 0xffff0000UW,
	WADEON_IS_MOBIWITY = 0x00010000UW,
	WADEON_IS_IGP = 0x00020000UW,
	WADEON_SINGWE_CWTC = 0x00040000UW,
	WADEON_IS_AGP = 0x00080000UW,
	WADEON_HAS_HIEWZ = 0x00100000UW,
	WADEON_IS_PCIE = 0x00200000UW,
	WADEON_NEW_MEMMAP = 0x00400000UW,
	WADEON_IS_PCI = 0x00800000UW,
	WADEON_IS_IGPGAWT = 0x01000000UW,
	WADEON_IS_PX = 0x02000000UW,
};

#endif
