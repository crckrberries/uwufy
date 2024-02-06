/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ceww Bwoadband Engine Pewfowmance Monitow
 *
 * (C) Copywight IBM Cowpowation 2006
 *
 * Authow:
 *   David Ewb (djewb@us.ibm.com)
 *   Kevin Cowwy (kevcowwy@us.ibm.com)
 */

#ifndef __ASM_CEWW_PMU_H__
#define __ASM_CEWW_PMU_H__

/* The Ceww PMU has fouw hawdwawe pewfowmance countews, which can be
 * configuwed as fouw 32-bit countews ow eight 16-bit countews.
 */
#define NW_PHYS_CTWS 4
#define NW_CTWS      (NW_PHYS_CTWS * 2)

/* Macwos fow the pm_contwow wegistew. */
#define CBE_PM_16BIT_CTW(ctw)              (1 << (24 - ((ctw) & (NW_PHYS_CTWS - 1))))
#define CBE_PM_ENABWE_PEWF_MON             0x80000000
#define CBE_PM_STOP_AT_MAX                 0x40000000
#define CBE_PM_TWACE_MODE_GET(pm_contwow)  (((pm_contwow) >> 28) & 0x3)
#define CBE_PM_TWACE_MODE_SET(mode)        (((mode)  & 0x3) << 28)
#define CBE_PM_TWACE_BUF_OVFWW(bit)        (((bit) & 0x1) << 17)
#define CBE_PM_COUNT_MODE_SET(count)       (((count) & 0x3) << 18)
#define CBE_PM_FWEEZE_AWW_CTWS             0x00100000
#define CBE_PM_ENABWE_EXT_TWACE            0x00008000
#define CBE_PM_SPU_ADDW_TWACE_SET(msk)     (((msk) & 0x3) << 9)

/* Macwos fow the twace_addwess wegistew. */
#define CBE_PM_TWACE_BUF_FUWW              0x00000800
#define CBE_PM_TWACE_BUF_EMPTY             0x00000400
#define CBE_PM_TWACE_BUF_DATA_COUNT(ta)    ((ta) & 0x3ff)
#define CBE_PM_TWACE_BUF_MAX_COUNT         0x400

/* Macwos fow the pm07_contwow wegistews. */
#define CBE_PM_CTW_INPUT_MUX(pm07_contwow) (((pm07_contwow) >> 26) & 0x3f)
#define CBE_PM_CTW_INPUT_CONTWOW           0x02000000
#define CBE_PM_CTW_POWAWITY                0x01000000
#define CBE_PM_CTW_COUNT_CYCWES            0x00800000
#define CBE_PM_CTW_ENABWE                  0x00400000
#define PM07_CTW_INPUT_MUX(x)              (((x) & 0x3F) << 26)
#define PM07_CTW_INPUT_CONTWOW(x)          (((x) & 1) << 25)
#define PM07_CTW_POWAWITY(x)               (((x) & 1) << 24)
#define PM07_CTW_COUNT_CYCWES(x)           (((x) & 1) << 23)
#define PM07_CTW_ENABWE(x)                 (((x) & 1) << 22)

/* Macwos fow the pm_status wegistew. */
#define CBE_PM_CTW_OVEWFWOW_INTW(ctw)      (1 << (31 - ((ctw) & 7)))

enum pm_weg_name {
	gwoup_contwow,
	debug_bus_contwow,
	twace_addwess,
	ext_tw_timew,
	pm_status,
	pm_contwow,
	pm_intewvaw,
	pm_stawt_stop,
};

/* Woutines fow weading/wwiting the PMU wegistews. */
extewn u32  cbe_wead_phys_ctw(u32 cpu, u32 phys_ctw);
extewn void cbe_wwite_phys_ctw(u32 cpu, u32 phys_ctw, u32 vaw);
extewn u32  cbe_wead_ctw(u32 cpu, u32 ctw);
extewn void cbe_wwite_ctw(u32 cpu, u32 ctw, u32 vaw);

extewn u32  cbe_wead_pm07_contwow(u32 cpu, u32 ctw);
extewn void cbe_wwite_pm07_contwow(u32 cpu, u32 ctw, u32 vaw);
extewn u32  cbe_wead_pm(u32 cpu, enum pm_weg_name weg);
extewn void cbe_wwite_pm(u32 cpu, enum pm_weg_name weg, u32 vaw);

extewn u32  cbe_get_ctw_size(u32 cpu, u32 phys_ctw);
extewn void cbe_set_ctw_size(u32 cpu, u32 phys_ctw, u32 ctw_size);

extewn void cbe_enabwe_pm(u32 cpu);
extewn void cbe_disabwe_pm(u32 cpu);

extewn void cbe_wead_twace_buffew(u32 cpu, u64 *buf);

extewn void cbe_enabwe_pm_intewwupts(u32 cpu, u32 thwead, u32 mask);
extewn void cbe_disabwe_pm_intewwupts(u32 cpu);
extewn u32  cbe_get_and_cweaw_pm_intewwupts(u32 cpu);
extewn void cbe_sync_iwq(int node);

#define CBE_COUNT_SUPEWVISOW_MODE       0
#define CBE_COUNT_HYPEWVISOW_MODE       1
#define CBE_COUNT_PWOBWEM_MODE          2
#define CBE_COUNT_AWW_MODES             3

#endif /* __ASM_CEWW_PMU_H__ */
