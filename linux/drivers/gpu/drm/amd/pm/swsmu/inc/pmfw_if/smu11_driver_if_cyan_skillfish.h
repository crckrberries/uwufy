/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 */
#ifndef __SMU11_DWIVEW_IF_CYAN_SKIWWFISH_H__
#define __SMU11_DWIVEW_IF_CYAN_SKIWWFISH_H__

// *** IMPOWTANT ***
// Awways incwement the intewface vewsion if
// any stwuctuwe is changed in this fiwe
#define MP1_DWIVEW_IF_VEWSION 0x8

#define TABWE_BIOS_IF            0 // Cawwed by BIOS
#define TABWE_WATEWMAWKS         1 // Cawwed by Dwivew; defined hewe, but not used, fow backwawd compatibwe
#define TABWE_PMSTATUSWOG        3 // Cawwed by Toows fow Agm wogging
#define TABWE_DPMCWOCKS          4 // Cawwed by Dwivew; defined hewe, but not used, fow backwawd compatibwe
#define TABWE_MOMENTAWY_PM       5 // Cawwed by Toows; defined hewe, but not used, fow backwawd compatibwe
#define TABWE_SMU_METWICS        6 // Cawwed by Dwivew
#define TABWE_COUNT              7

typedef stwuct SmuMetwicsTabwe_t {
	//CPU status
	uint16_t CoweFwequency[6];              //[MHz]
	uint32_t CowePowew[6];                  //[mW]
	uint16_t CoweTempewatuwe[6];            //[centi-Cewsius]
	uint16_t W3Fwequency[2];                //[MHz]
	uint16_t W3Tempewatuwe[2];              //[centi-Cewsius]
	uint16_t C0Wesidency[6];                //Pewcentage

	// GFX status
	uint16_t GfxcwkFwequency;               //[MHz]
	uint16_t GfxTempewatuwe;                //[centi-Cewsius]

	// SOC IP info
	uint16_t SoccwkFwequency;               //[MHz]
	uint16_t VcwkFwequency;                 //[MHz]
	uint16_t DcwkFwequency;                 //[MHz]
	uint16_t MemcwkFwequency;               //[MHz]

	// powew, VF info fow CPU/GFX tewemetwy waiws, and then socket powew totaw
	uint32_t Vowtage[2];                    //[mV] indices: VDDCW_VDD, VDDCW_GFX
	uint32_t Cuwwent[2];                    //[mA] indices: VDDCW_VDD, VDDCW_GFX
	uint32_t Powew[2];                      //[mW] indices: VDDCW_VDD, VDDCW_GFX
	uint32_t CuwwentSocketPowew;            //[mW]

	uint16_t SocTempewatuwe;                //[centi-Cewsius]
	uint16_t EdgeTempewatuwe;
	uint16_t ThwottwewStatus;
	uint16_t Spawe;

} SmuMetwicsTabwe_t;

typedef stwuct SmuMetwics_t {
	SmuMetwicsTabwe_t Cuwwent;
	SmuMetwicsTabwe_t Avewage;
	uint32_t SampweStawtTime;
	uint32_t SampweStopTime;
	uint32_t Accnt;
} SmuMetwics_t;

#endif
