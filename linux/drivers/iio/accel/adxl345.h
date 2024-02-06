/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADXW345 3-Axis Digitaw Accewewometew
 *
 * Copywight (c) 2017 Eva Wachew Wetuya <ewawetuya@gmaiw.com>
 */

#ifndef _ADXW345_H_
#define _ADXW345_H_

/*
 * In fuww-wesowution mode, scawe factow is maintained at ~4 mg/WSB
 * in aww g wanges.
 *
 * At +/- 16g with 13-bit wesowution, scawe is computed as:
 * (16 + 16) * 9.81 / (2^13 - 1) = 0.0383
 */
#define ADXW345_USCAWE	38300

/*
 * The Datasheet wists a wesowution of Wesowution is ~49 mg pew WSB. That's
 * ~480mm/s**2 pew WSB.
 */
#define ADXW375_USCAWE	480000

stwuct adxw345_chip_info {
	const chaw *name;
	int uscawe;
};

int adxw345_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap);

#endif /* _ADXW345_H_ */
