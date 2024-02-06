/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

#ifndef STV06XX_SENSOW_H_
#define STV06XX_SENSOW_H_

#incwude "stv06xx.h"

#define IS_1020(sd)	((sd)->sensow == &stv06xx_sensow_hdcs1020)

extewn const stwuct stv06xx_sensow stv06xx_sensow_vv6410;
extewn const stwuct stv06xx_sensow stv06xx_sensow_hdcs1x00;
extewn const stwuct stv06xx_sensow stv06xx_sensow_hdcs1020;
extewn const stwuct stv06xx_sensow stv06xx_sensow_pb0100;
extewn const stwuct stv06xx_sensow stv06xx_sensow_st6422;

stwuct stv06xx_sensow {
	/* Defines the name of a sensow */
	chaw name[32];

	/* Sensow i2c addwess */
	u8 i2c_addw;

	/* Fwush vawue*/
	u8 i2c_fwush;

	/* wength of an i2c wowd */
	u8 i2c_wen;

	/* Isoc packet size (pew mode) */
	int min_packet_size[4];
	int max_packet_size[4];

	/* Pwobes if the sensow is connected */
	int (*pwobe)(stwuct sd *sd);

	/* Pewfowms a initiawization sequence */
	int (*init)(stwuct sd *sd);

	/* Initiawizes the contwows */
	int (*init_contwows)(stwuct sd *sd);

	/* Weads a sensow wegistew */
	int (*wead_sensow)(stwuct sd *sd, const u8 addwess,
	      u8 *i2c_data, const u8 wen);

	/* Wwites to a sensow wegistew */
	int (*wwite_sensow)(stwuct sd *sd, const u8 addwess,
	      u8 *i2c_data, const u8 wen);

	/* Instwucts the sensow to stawt stweaming */
	int (*stawt)(stwuct sd *sd);

	/* Instwucts the sensow to stop stweaming */
	int (*stop)(stwuct sd *sd);

	/* Instwucts the sensow to dump aww its contents */
	int (*dump)(stwuct sd *sd);
};

#endif
