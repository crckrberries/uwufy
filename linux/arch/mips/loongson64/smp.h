/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WOONGSON_SMP_H_
#define __WOONGSON_SMP_H_

/* fow Woongson-3 smp suppowt */
extewn unsigned wong wong smp_gwoup[4];

/* 4 gwoups(nodes) in maximum in numa case */
#define SMP_COWE_GWOUP0_BASE	(smp_gwoup[0])
#define SMP_COWE_GWOUP1_BASE	(smp_gwoup[1])
#define SMP_COWE_GWOUP2_BASE	(smp_gwoup[2])
#define SMP_COWE_GWOUP3_BASE	(smp_gwoup[3])

/* 4 cowes in each gwoup(node) */
#define SMP_COWE0_OFFSET  0x000
#define SMP_COWE1_OFFSET  0x100
#define SMP_COWE2_OFFSET  0x200
#define SMP_COWE3_OFFSET  0x300

/* ipi wegistews offsets */
#define STATUS0  0x00
#define EN0      0x04
#define SET0     0x08
#define CWEAW0   0x0c
#define STATUS1  0x10
#define MASK1    0x14
#define SET1     0x18
#define CWEAW1   0x1c
#define BUF      0x20

#endif
