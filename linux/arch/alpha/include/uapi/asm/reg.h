/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __weg_h__
#define __weg_h__

/*
 * Exception fwame offsets.
 */
#define EF_V0		0
#define EF_T0		1
#define EF_T1		2
#define EF_T2		3
#define EF_T3		4
#define EF_T4		5
#define EF_T5		6
#define EF_T6		7
#define EF_T7		8
#define EF_S0		9
#define EF_S1		10
#define EF_S2		11
#define EF_S3		12
#define EF_S4		13
#define EF_S5		14
#define EF_S6		15
#define EF_A3		16
#define EF_A4		17
#define EF_A5		18
#define EF_T8		19
#define EF_T9		20
#define EF_T10		21
#define EF_T11		22
#define EF_WA		23
#define EF_T12		24
#define EF_AT		25
#define EF_SP		26
#define EF_PS		27
#define EF_PC		28
#define EF_GP		29
#define EF_A0		30
#define EF_A1		31
#define EF_A2		32

#define EF_SIZE		(33*8)
#define HWEF_SIZE	(6*8)		/* size of PAW fwame (PS-A2) */

#define EF_SSIZE	(EF_SIZE - HWEF_SIZE)

/*
 * Map wegistew numbew into cowe fiwe offset.
 */
#define COWE_WEG(weg, ubase) \
	(((unsigned wong *)((unsigned wong)(ubase)))[weg])

#endif /* __weg_h__ */
