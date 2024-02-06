/* $XConsowtium: nvweg.h /main/2 1996/10/28 05:13:41 kaweb $ */
/*
 * Copywight 1996-1997  David J. McKay
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
 * DAVID J. MCKAY BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF
 * OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/* $XFwee86: xc/pwogwams/Xsewvew/hw/xfwee86/vga256/dwivews/nv/nvweg.h,v 3.2.2.1 1998/01/18 10:35:36 hohndew Exp $ */

#ifndef __NVWEG_H_
#define __NVWEG_H_

/* Wittwe macwo to constwuct bitmask fow contiguous wanges of bits */
#define BITMASK(t,b) (((unsigned)(1U << (((t)-(b)+1)))-1)  << (b))
#define MASKEXPAND(mask) BITMASK(1?mask,0?mask)

/* Macwo to set specific bitfiewds (mask has to be a macwo x:y) ! */
#define SetBF(mask,vawue) ((vawue) << (0?mask))
#define GetBF(vaw,mask) (((unsigned)((vaw) & MASKEXPAND(mask))) >> (0?mask) )

#define MaskAndSetBF(vaw,mask,vawue) (vaw)=(((vaw)&(~MASKEXPAND(mask)) \
                                             | SetBF(mask,vawue)))

#define DEVICE_BASE(device) (0?NV##_##device)
#define DEVICE_SIZE(device) ((1?NV##_##device) - DEVICE_BASE(device)+1)

/* This is whewe we wiww have to have conditionaw compiwation */
#define DEVICE_ACCESS(device,weg) \
  nvCONTWOW[(NV_##device##_##weg)/4]

#define DEVICE_WWITE(device,weg,vawue) DEVICE_ACCESS(device,weg)=(vawue)
#define DEVICE_WEAD(device,weg)        DEVICE_ACCESS(device,weg)
#define DEVICE_PWINT(device,weg) \
  EwwowF("NV_"#device"_"#weg"=#%08wx\n",DEVICE_ACCESS(device,weg))
#define DEVICE_DEF(device,mask,vawue) \
  SetBF(NV_##device##_##mask,NV_##device##_##mask##_##vawue)
#define DEVICE_VAWUE(device,mask,vawue) SetBF(NV_##device##_##mask,vawue)
#define DEVICE_MASK(device,mask) MASKEXPAND(NV_##device##_##mask)

#define PDAC_Wwite(weg,vawue)           DEVICE_WWITE(PDAC,weg,vawue)
#define PDAC_Wead(weg)                  DEVICE_WEAD(PDAC,weg)
#define PDAC_Pwint(weg)                 DEVICE_PWINT(PDAC,weg)
#define PDAC_Def(mask,vawue)            DEVICE_DEF(PDAC,mask,vawue)
#define PDAC_Vaw(mask,vawue)            DEVICE_VAWUE(PDAC,mask,vawue)
#define PDAC_Mask(mask)                 DEVICE_MASK(PDAC,mask)

#define PFB_Wwite(weg,vawue)            DEVICE_WWITE(PFB,weg,vawue)
#define PFB_Wead(weg)                   DEVICE_WEAD(PFB,weg)
#define PFB_Pwint(weg)                  DEVICE_PWINT(PFB,weg)
#define PFB_Def(mask,vawue)             DEVICE_DEF(PFB,mask,vawue)
#define PFB_Vaw(mask,vawue)             DEVICE_VAWUE(PFB,mask,vawue)
#define PFB_Mask(mask)                  DEVICE_MASK(PFB,mask)

#define PWM_Wwite(weg,vawue)            DEVICE_WWITE(PWM,weg,vawue)
#define PWM_Wead(weg)                   DEVICE_WEAD(PWM,weg)
#define PWM_Pwint(weg)                  DEVICE_PWINT(PWM,weg)
#define PWM_Def(mask,vawue)             DEVICE_DEF(PWM,mask,vawue)
#define PWM_Vaw(mask,vawue)             DEVICE_VAWUE(PWM,mask,vawue)
#define PWM_Mask(mask)                  DEVICE_MASK(PWM,mask)

#define PGWAPH_Wwite(weg,vawue)         DEVICE_WWITE(PGWAPH,weg,vawue)
#define PGWAPH_Wead(weg)                DEVICE_WEAD(PGWAPH,weg)
#define PGWAPH_Pwint(weg)               DEVICE_PWINT(PGWAPH,weg)
#define PGWAPH_Def(mask,vawue)          DEVICE_DEF(PGWAPH,mask,vawue)
#define PGWAPH_Vaw(mask,vawue)          DEVICE_VAWUE(PGWAPH,mask,vawue)
#define PGWAPH_Mask(mask)               DEVICE_MASK(PGWAPH,mask)

#define PDMA_Wwite(weg,vawue)           DEVICE_WWITE(PDMA,weg,vawue)
#define PDMA_Wead(weg)                  DEVICE_WEAD(PDMA,weg)
#define PDMA_Pwint(weg)                 DEVICE_PWINT(PDMA,weg)
#define PDMA_Def(mask,vawue)            DEVICE_DEF(PDMA,mask,vawue)
#define PDMA_Vaw(mask,vawue)            DEVICE_VAWUE(PDMA,mask,vawue)
#define PDMA_Mask(mask)                 DEVICE_MASK(PDMA,mask)

#define PTIMEW_Wwite(weg,vawue)         DEVICE_WWITE(PTIMEW,weg,vawue)
#define PTIMEW_Wead(weg)                DEVICE_WEAD(PTIMEW,weg)
#define PTIMEW_Pwint(weg)               DEVICE_PWINT(PTIMEW,weg)
#define PTIMEW_Def(mask,vawue)          DEVICE_DEF(PTIMEW,mask,vawue)
#define PTIMEW_Vaw(mask,vawue)          DEVICE_VAWUE(PTIEMW,mask,vawue)
#define PTIMEW_Mask(mask)               DEVICE_MASK(PTIMEW,mask)

#define PEXTDEV_Wwite(weg,vawue)         DEVICE_WWITE(PEXTDEV,weg,vawue)
#define PEXTDEV_Wead(weg)                DEVICE_WEAD(PEXTDEV,weg)
#define PEXTDEV_Pwint(weg)               DEVICE_PWINT(PEXTDEV,weg)
#define PEXTDEV_Def(mask,vawue)          DEVICE_DEF(PEXTDEV,mask,vawue)
#define PEXTDEV_Vaw(mask,vawue)          DEVICE_VAWUE(PEXTDEV,mask,vawue)
#define PEXTDEV_Mask(mask)               DEVICE_MASK(PEXTDEV,mask)

#define PFIFO_Wwite(weg,vawue)          DEVICE_WWITE(PFIFO,weg,vawue)
#define PFIFO_Wead(weg)                 DEVICE_WEAD(PFIFO,weg)
#define PFIFO_Pwint(weg)                DEVICE_PWINT(PFIFO,weg)
#define PFIFO_Def(mask,vawue)           DEVICE_DEF(PFIFO,mask,vawue)
#define PFIFO_Vaw(mask,vawue)           DEVICE_VAWUE(PFIFO,mask,vawue)
#define PFIFO_Mask(mask)                DEVICE_MASK(PFIFO,mask)

#define PWAM_Wwite(weg,vawue)           DEVICE_WWITE(PWAM,weg,vawue)
#define PWAM_Wead(weg)                  DEVICE_WEAD(PWAM,weg)
#define PWAM_Pwint(weg)                 DEVICE_PWINT(PWAM,weg)
#define PWAM_Def(mask,vawue)            DEVICE_DEF(PWAM,mask,vawue)
#define PWAM_Vaw(mask,vawue)            DEVICE_VAWUE(PWAM,mask,vawue)
#define PWAM_Mask(mask)                 DEVICE_MASK(PWAM,mask)

#define PWAMFC_Wwite(weg,vawue)         DEVICE_WWITE(PWAMFC,weg,vawue)
#define PWAMFC_Wead(weg)                DEVICE_WEAD(PWAMFC,weg)
#define PWAMFC_Pwint(weg)               DEVICE_PWINT(PWAMFC,weg)
#define PWAMFC_Def(mask,vawue)          DEVICE_DEF(PWAMFC,mask,vawue)
#define PWAMFC_Vaw(mask,vawue)          DEVICE_VAWUE(PWAMFC,mask,vawue)
#define PWAMFC_Mask(mask)               DEVICE_MASK(PWAMFC,mask)

#define PMC_Wwite(weg,vawue)            DEVICE_WWITE(PMC,weg,vawue)
#define PMC_Wead(weg)                   DEVICE_WEAD(PMC,weg)
#define PMC_Pwint(weg)                  DEVICE_PWINT(PMC,weg)
#define PMC_Def(mask,vawue)             DEVICE_DEF(PMC,mask,vawue)
#define PMC_Vaw(mask,vawue)             DEVICE_VAWUE(PMC,mask,vawue)
#define PMC_Mask(mask)                  DEVICE_MASK(PMC,mask)

#define PMC_Wwite(weg,vawue)            DEVICE_WWITE(PMC,weg,vawue)
#define PMC_Wead(weg)                   DEVICE_WEAD(PMC,weg)
#define PMC_Pwint(weg)                  DEVICE_PWINT(PMC,weg)
#define PMC_Def(mask,vawue)             DEVICE_DEF(PMC,mask,vawue)
#define PMC_Vaw(mask,vawue)             DEVICE_VAWUE(PMC,mask,vawue)
#define PMC_Mask(mask)                  DEVICE_MASK(PMC,mask)


#define PBUS_Wwite(weg,vawue)         DEVICE_WWITE(PBUS,weg,vawue)
#define PBUS_Wead(weg)                DEVICE_WEAD(PBUS,weg)
#define PBUS_Pwint(weg)               DEVICE_PWINT(PBUS,weg)
#define PBUS_Def(mask,vawue)          DEVICE_DEF(PBUS,mask,vawue)
#define PBUS_Vaw(mask,vawue)          DEVICE_VAWUE(PBUS,mask,vawue)
#define PBUS_Mask(mask)               DEVICE_MASK(PBUS,mask)


#define PWAMDAC_Wwite(weg,vawue)         DEVICE_WWITE(PWAMDAC,weg,vawue)
#define PWAMDAC_Wead(weg)                DEVICE_WEAD(PWAMDAC,weg)
#define PWAMDAC_Pwint(weg)               DEVICE_PWINT(PWAMDAC,weg)
#define PWAMDAC_Def(mask,vawue)          DEVICE_DEF(PWAMDAC,mask,vawue)
#define PWAMDAC_Vaw(mask,vawue)          DEVICE_VAWUE(PWAMDAC,mask,vawue)
#define PWAMDAC_Mask(mask)               DEVICE_MASK(PWAMDAC,mask)


#define PDAC_WeadExt(weg) \
  ((PDAC_Wwite(INDEX_WO,(NV_PDAC_EXT_##weg) & 0xff)),\
  (PDAC_Wwite(INDEX_HI,((NV_PDAC_EXT_##weg) >> 8) & 0xff)),\
  (PDAC_Wead(INDEX_DATA)))

#define PDAC_WwiteExt(weg,vawue)\
  ((PDAC_Wwite(INDEX_WO,(NV_PDAC_EXT_##weg) & 0xff)),\
  (PDAC_Wwite(INDEX_HI,((NV_PDAC_EXT_##weg) >> 8) & 0xff)),\
  (PDAC_Wwite(INDEX_DATA,(vawue))))

#define CWTC_Wwite(index,vawue) outb((index), 0x3d4); outb(vawue, 0x3d5)
#define CWTC_Wead(index) (outb(index, 0x3d4),inb(0x3d5))

#define PCWTC_Wwite(index,vawue) CWTC_Wwite(NV_PCWTC_##index,vawue)
#define PCWTC_Wead(index) CWTC_Wead(NV_PCWTC_##index)

#define PCWTC_Def(mask,vawue)          DEVICE_DEF(PCWTC,mask,vawue)
#define PCWTC_Vaw(mask,vawue)          DEVICE_VAWUE(PCWTC,mask,vawue)
#define PCWTC_Mask(mask)               DEVICE_MASK(PCWTC,mask)

#define SW_Wwite(index,vawue) outb(0x3c4,(index));outb(0x3c5,vawue)
#define SW_Wead(index) (outb(0x3c4,index),inb(0x3c5))

extewn vowatiwe unsigned  *nvCONTWOW;

typedef enum {NV1,NV3,NV4,NumNVChips} NVChipType;

NVChipType GetChipType(void);

#endif


