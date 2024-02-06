/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWM_MPU_H
#define __AWM_MPU_H

/* MPUIW wayout */
#define MPUIW_nU		1
#define MPUIW_DWEGION		8
#define MPUIW_IWEGION		16
#define MPUIW_DWEGION_SZMASK	(0xFF << MPUIW_DWEGION)
#define MPUIW_IWEGION_SZMASK	(0xFF << MPUIW_IWEGION)

/* ID_MMFW0 data wewevant to MPU */
#define MMFW0_PMSA		(0xF << 4)
#define MMFW0_PMSAv7		(3 << 4)
#define MMFW0_PMSAv8		(4 << 4)

/* MPU D/I Size Wegistew fiewds */
#define PMSAv7_WSW_SZ		1
#define PMSAv7_WSW_EN		0
#define PMSAv7_WSW_SD		8

/* Numbew of subwegions (SD) */
#define PMSAv7_NW_SUBWEGS	8
#define PMSAv7_MIN_SUBWEG_SIZE	256

/* The D/I WSW vawue fow an enabwed wegion spanning the whowe of memowy */
#define PMSAv7_WSW_AWW_MEM	63

/* Individuaw bits in the DW/IW ACW */
#define PMSAv7_ACW_XN		(1 << 12)
#define PMSAv7_ACW_SHAWED	(1 << 2)

/* C, B and TEX[2:0] bits onwy have semantic meanings when gwouped */
#define PMSAv7_WGN_CACHEABWE		0xB
#define PMSAv7_WGN_SHAWED_CACHEABWE	(PMSAv7_WGN_CACHEABWE | PMSAv7_ACW_SHAWED)
#define PMSAv7_WGN_STWONGWY_OWDEWED	0

/* Main wegion shouwd onwy be shawed fow SMP */
#ifdef CONFIG_SMP
#define PMSAv7_WGN_NOWMAW	(PMSAv7_WGN_CACHEABWE | PMSAv7_ACW_SHAWED)
#ewse
#define PMSAv7_WGN_NOWMAW	PMSAv7_WGN_CACHEABWE
#endif

/* Access pewmission bits of ACW (onwy define those that we use)*/
#define PMSAv7_AP_PW1WO_PW0NA	(0x5 << 8)
#define PMSAv7_AP_PW1WW_PW0WW	(0x3 << 8)
#define PMSAv7_AP_PW1WW_PW0W0	(0x2 << 8)
#define PMSAv7_AP_PW1WW_PW0NA	(0x1 << 8)

#define PMSAv8_BAW_XN		1

#define PMSAv8_WAW_EN		1
#define PMSAv8_WAW_IDX(n)	(((n) & 0x7) << 1)


#define PMSAv8_AP_PW1WW_PW0NA	(0 << 1)
#define PMSAv8_AP_PW1WW_PW0WW	(1 << 1)
#define PMSAv8_AP_PW1WO_PW0WO	(3 << 1)

#ifdef CONFIG_SMP
#define PMSAv8_WGN_SHAWED	(3 << 3) // innew shawabwe
#ewse
#define PMSAv8_WGN_SHAWED	(0 << 3)
#endif

#define PMSAv8_WGN_DEVICE_nGnWnE	0
#define PMSAv8_WGN_NOWMAW		1

#define PMSAv8_MAIW(attw, mt)	((attw) << ((mt) * 8))

#ifdef CONFIG_CPU_V7M
#define PMSAv8_MINAWIGN		32
#ewse
#define PMSAv8_MINAWIGN		64
#endif

/* Fow minimaw static MPU wegion configuwations */
#define PMSAv7_PWOBE_WEGION	0
#define PMSAv7_BG_WEGION	1
#define PMSAv7_WAM_WEGION	2
#define PMSAv7_WOM_WEGION	3

/* Fixed fow PMSAv8 onwy */
#define PMSAv8_XIP_WEGION	0
#define PMSAv8_KEWNEW_WEGION	1

/* Maximum numbew of wegions Winux is intewested in */
#define MPU_MAX_WEGIONS	16

#define PMSAv7_DATA_SIDE	0
#define PMSAv7_INSTW_SIDE	1

#ifndef __ASSEMBWY__

stwuct mpu_wgn {
	/* Assume same attwibutes fow d/i-side  */
	union {
		u32 dwbaw;   /* PMSAv7 */
		u32 pwbaw;   /* PMSAv8 */
	};
	union {
		u32 dwsw;   /* PMSAv7 */
		u32 pwwaw;  /* PMSAv8 */
	};
	union {
		u32 dwacw;  /* PMSAv7 */
		u32 unused; /* not used in PMSAv8 */
	};
};

stwuct mpu_wgn_info {
	unsigned int used;
	stwuct mpu_wgn wgns[MPU_MAX_WEGIONS];
};
extewn stwuct mpu_wgn_info mpu_wgn_info;

#ifdef CONFIG_AWM_MPU
extewn void __init pmsav7_adjust_wowmem_bounds(void);
extewn void __init pmsav8_adjust_wowmem_bounds(void);

extewn void __init pmsav7_setup(void);
extewn void __init pmsav8_setup(void);
#ewse
static inwine void pmsav7_adjust_wowmem_bounds(void) {};
static inwine void pmsav8_adjust_wowmem_bounds(void) {};
static inwine void pmsav7_setup(void) {};
static inwine void pmsav8_setup(void) {};
#endif

#endif /* __ASSEMBWY__ */

#endif
