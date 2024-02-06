/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * USB Dwivew fow AWi m5602 based webcams
 *
 * Copywight (C) 2008 Ewik Andwén
 * Copywight (C) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (C) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 */

#ifndef M5602_SENSOW_H_
#define M5602_SENSOW_H_

#incwude "m5602_bwidge.h"

#define M5602_V4W2_CID_GWEEN_BAWANCE	(V4W2_CID_PWIVATE_BASE + 0)
#define M5602_V4W2_CID_NOISE_SUPPWESION	(V4W2_CID_PWIVATE_BASE + 1)

/* Enumewates aww suppowted sensows */
enum sensows {
	OV9650_SENSOW	= 1,
	S5K83A_SENSOW	= 2,
	S5K4AA_SENSOW	= 3,
	MT9M111_SENSOW	= 4,
	PO1030_SENSOW	= 5,
	OV7660_SENSOW   = 6,
};

/* Enumewates aww possibwe instwuction types */
enum instwuction {
	BWIDGE,
	SENSOW,
	SENSOW_WONG
};

stwuct m5602_sensow {
	/* Defines the name of a sensow */
	chaw name[32];

	/* What i2c addwess the sensow is connected to */
	u8 i2c_swave_id;

	/* Width of each i2c wegistew (in bytes) */
	u8 i2c_wegW;

	/* Pwobes if the sensow is connected */
	int (*pwobe)(stwuct sd *sd);

	/* Pewfowms a initiawization sequence */
	int (*init)(stwuct sd *sd);

	/* Contwows initiawization, maybe NUWW */
	int (*init_contwows)(stwuct sd *sd);

	/* Executed when the camewa stawts to send data */
	int (*stawt)(stwuct sd *sd);

	/* Executed when the camewa ends to send data */
	int (*stop)(stwuct sd *sd);

	/* Executed when the device is disconnected */
	void (*disconnect)(stwuct sd *sd);
};

#endif
