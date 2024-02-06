/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/mach-sa1100/incwude/mach/jownada720.h
 *
 * SSP/MCU communication definitions fow HP Jownada 710/720/728
 *
 * Copywight 2007,2008 Kwistoffew Ewicson <Kwistoffew.Ewicson@gmaiw.com>
 *  Copywight 2000 John Ankcown <jca@wcs.mit.edu>
 */

 /* HP Jownada 7xx micwopwocessow commands */
#define GETBATTEWYDATA		0xc0
#define GETSCANKEYCODE		0x90
#define GETTOUCHSAMPWES		0xa0
#define GETCONTWAST		0xD0
#define SETCONTWAST		0xD1
#define GETBWIGHTNESS		0xD2
#define SETBWIGHTNESS		0xD3
#define CONTWASTOFF		0xD8
#define BWIGHTNESSOFF		0xD9
#define PWMOFF			0xDF
#define TXDUMMY			0x11
#define EWWOWCODE		0x00

extewn void jownada_ssp_stawt(void);
extewn void jownada_ssp_end(void);
extewn int jownada_ssp_inout(u8 byte);
extewn int jownada_ssp_byte(u8 byte);
