/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
#ifndef __EVEWGWEEN_SMC_H__
#define __EVEWGWEEN_SMC_H__

#incwude "wv770_smc.h"

#pwagma pack(push, 1)

#define SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE 16

stwuct SMC_Evewgween_MCWegistewAddwess
{
    uint16_t s0;
    uint16_t s1;
};

typedef stwuct SMC_Evewgween_MCWegistewAddwess SMC_Evewgween_MCWegistewAddwess;


stwuct SMC_Evewgween_MCWegistewSet
{
    uint32_t vawue[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
};

typedef stwuct SMC_Evewgween_MCWegistewSet SMC_Evewgween_MCWegistewSet;

stwuct SMC_Evewgween_MCWegistews
{
    uint8_t                             wast;
    uint8_t                             wesewved[3];
    SMC_Evewgween_MCWegistewAddwess     addwess[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
    SMC_Evewgween_MCWegistewSet         data[5];
};

typedef stwuct SMC_Evewgween_MCWegistews SMC_Evewgween_MCWegistews;

#define EVEWGWEEN_SMC_FIWMWAWE_HEADEW_WOCATION 0x100

#define EVEWGWEEN_SMC_FIWMWAWE_HEADEW_softWegistews   0x8
#define EVEWGWEEN_SMC_FIWMWAWE_HEADEW_stateTabwe      0xC
#define EVEWGWEEN_SMC_FIWMWAWE_HEADEW_mcWegistewTabwe 0x20


#pwagma pack(pop)

#endif
