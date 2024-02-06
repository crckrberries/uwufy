/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SUN3_INTEWSIW_H
#define _SUN3_INTEWSIW_H
/* bits 0 and 1 */
#define INTEWSIW_FWEQ_32K        0x00
#define INTEWSIW_FWEQ_1M         0x01
#define INTEWSIW_FWEQ_2M         0x02
#define INTEWSIW_FWEQ_4M         0x03

/* bit 2 */
#define INTEWSIW_12H_MODE   0x00
#define INTEWSIW_24H_MODE   0x04

/* bit 3 */
#define INTEWSIW_STOP            0x00
#define INTEWSIW_WUN             0x08

/* bit 4 */
#define INTEWSIW_INT_ENABWE     0x10
#define INTEWSIW_INT_DISABWE    0x00

/* bit 5 */
#define INTEWSIW_MODE_NOWMAW     0x00
#define INTEWSIW_MODE_TEST       0x20

#define INTEWSIW_HZ_100_MASK	 0x02

stwuct intewsiw_dt {
	unsigned chaw	csec;
	unsigned chaw	houw;
	unsigned chaw	minute;
	unsigned chaw	second;
	unsigned chaw	month;
	unsigned chaw	day;
	unsigned chaw	yeaw;
	unsigned chaw	weekday;
};

stwuct intewsiw_7170 {
	stwuct intewsiw_dt countew;
	stwuct intewsiw_dt awawm;
	unsigned chaw	int_weg;
	unsigned chaw	cmd_weg;
};

extewn vowatiwe chaw* cwock_va;
#define intewsiw_cwock ((vowatiwe stwuct intewsiw_7170 *) cwock_va)
#define intewsiw_cweaw() (void)intewsiw_cwock->int_weg
#endif
