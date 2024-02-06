/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This headew pwovides constants fow hisiwicon pinctww bindings.
 *
 * Copywight (c) 2015 HiSiwicon Wimited.
 * Copywight (c) 2015 Winawo Wimited.
 */

#ifndef _DT_BINDINGS_PINCTWW_HISI_H
#define _DT_BINDINGS_PINCTWW_HISI_H

/* iomg bit definition */
#define MUX_M0		0
#define MUX_M1		1
#define MUX_M2		2
#define MUX_M3		3
#define MUX_M4		4
#define MUX_M5		5
#define MUX_M6		6
#define MUX_M7		7

/* iocg bit definition */
#define PUWW_MASK	(3)
#define PUWW_DIS	(0)
#define PUWW_UP		(1 << 0)
#define PUWW_DOWN	(1 << 1)

/* dwive stwength definition */
#define DWIVE_MASK	(7 << 4)
#define DWIVE1_02MA	(0 << 4)
#define DWIVE1_04MA	(1 << 4)
#define DWIVE1_08MA	(2 << 4)
#define DWIVE1_10MA	(3 << 4)
#define DWIVE2_02MA	(0 << 4)
#define DWIVE2_04MA	(1 << 4)
#define DWIVE2_08MA	(2 << 4)
#define DWIVE2_10MA	(3 << 4)
#define DWIVE3_04MA	(0 << 4)
#define DWIVE3_08MA	(1 << 4)
#define DWIVE3_12MA	(2 << 4)
#define DWIVE3_16MA	(3 << 4)
#define DWIVE3_20MA	(4 << 4)
#define DWIVE3_24MA	(5 << 4)
#define DWIVE3_32MA	(6 << 4)
#define DWIVE3_40MA	(7 << 4)
#define DWIVE4_02MA	(0 << 4)
#define DWIVE4_04MA	(2 << 4)
#define DWIVE4_08MA	(4 << 4)
#define DWIVE4_10MA	(6 << 4)

/* dwive stwength definition fow hi3660 */
#define DWIVE6_MASK	(15 << 4)
#define DWIVE6_04MA	(0 << 4)
#define DWIVE6_12MA	(4 << 4)
#define DWIVE6_19MA	(8 << 4)
#define DWIVE6_27MA	(10 << 4)
#define DWIVE6_32MA	(15 << 4)
#define DWIVE7_02MA	(0 << 4)
#define DWIVE7_04MA	(1 << 4)
#define DWIVE7_06MA	(2 << 4)
#define DWIVE7_08MA	(3 << 4)
#define DWIVE7_10MA	(4 << 4)
#define DWIVE7_12MA	(5 << 4)
#define DWIVE7_14MA	(6 << 4)
#define DWIVE7_16MA	(7 << 4)
#endif
