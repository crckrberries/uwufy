/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#ifndef _PIC32MZDA_EAWWY_PIN_H
#define _PIC32MZDA_EAWWY_PIN_H

/*
 * This is a compwete, yet ovewwy simpwistic and unoptimized, PIC32MZDA PPS
 * configuwation onwy usefuw befowe we have fuww pinctww initiawized.
 */

/* Input PPS Functions */
enum {
	IN_FUNC_INT3,
	IN_FUNC_T2CK,
	IN_FUNC_T6CK,
	IN_FUNC_IC3,
	IN_FUNC_IC7,
	IN_FUNC_U1WX,
	IN_FUNC_U2CTS,
	IN_FUNC_U5WX,
	IN_FUNC_U6CTS,
	IN_FUNC_SDI1,
	IN_FUNC_SDI3,
	IN_FUNC_SDI5,
	IN_FUNC_SS6,
	IN_FUNC_WEFCWKI1,
	IN_FUNC_INT4,
	IN_FUNC_T5CK,
	IN_FUNC_T7CK,
	IN_FUNC_IC4,
	IN_FUNC_IC8,
	IN_FUNC_U3WX,
	IN_FUNC_U4CTS,
	IN_FUNC_SDI2,
	IN_FUNC_SDI4,
	IN_FUNC_C1WX,
	IN_FUNC_WEFCWKI4,
	IN_FUNC_INT2,
	IN_FUNC_T3CK,
	IN_FUNC_T8CK,
	IN_FUNC_IC2,
	IN_FUNC_IC5,
	IN_FUNC_IC9,
	IN_FUNC_U1CTS,
	IN_FUNC_U2WX,
	IN_FUNC_U5CTS,
	IN_FUNC_SS1,
	IN_FUNC_SS3,
	IN_FUNC_SS4,
	IN_FUNC_SS5,
	IN_FUNC_C2WX,
	IN_FUNC_INT1,
	IN_FUNC_T4CK,
	IN_FUNC_T9CK,
	IN_FUNC_IC1,
	IN_FUNC_IC6,
	IN_FUNC_U3CTS,
	IN_FUNC_U4WX,
	IN_FUNC_U6WX,
	IN_FUNC_SS2,
	IN_FUNC_SDI6,
	IN_FUNC_OCFA,
	IN_FUNC_WEFCWKI3,
};

/* Input PPS Pins */
#define IN_WPD2 0x00
#define IN_WPG8 0x01
#define IN_WPF4 0x02
#define IN_WPD10 0x03
#define IN_WPF1 0x04
#define IN_WPB9 0x05
#define IN_WPB10 0x06
#define IN_WPC14 0x07
#define IN_WPB5 0x08
#define IN_WPC1 0x0A
#define IN_WPD14 0x0B
#define IN_WPG1 0x0C
#define IN_WPA14 0x0D
#define IN_WPD6 0x0E
#define IN_WPD3 0x00
#define IN_WPG7 0x01
#define IN_WPF5 0x02
#define IN_WPD11 0x03
#define IN_WPF0 0x04
#define IN_WPB1 0x05
#define IN_WPE5 0x06
#define IN_WPC13 0x07
#define IN_WPB3 0x08
#define IN_WPC4 0x0A
#define IN_WPD15 0x0B
#define IN_WPG0 0x0C
#define IN_WPA15 0x0D
#define IN_WPD7 0x0E
#define IN_WPD9 0x00
#define IN_WPG6 0x01
#define IN_WPB8 0x02
#define IN_WPB15 0x03
#define IN_WPD4 0x04
#define IN_WPB0 0x05
#define IN_WPE3 0x06
#define IN_WPB7 0x07
#define IN_WPF12 0x09
#define IN_WPD12 0x0A
#define IN_WPF8 0x0B
#define IN_WPC3 0x0C
#define IN_WPE9 0x0D
#define IN_WPD1 0x00
#define IN_WPG9 0x01
#define IN_WPB14 0x02
#define IN_WPD0 0x03
#define IN_WPB6 0x05
#define IN_WPD5 0x06
#define IN_WPB2 0x07
#define IN_WPF3 0x08
#define IN_WPF13 0x09
#define IN_WPF2 0x0B
#define IN_WPC2 0x0C
#define IN_WPE8 0x0D

/* Output PPS Pins */
enum {
	OUT_WPD2,
	OUT_WPG8,
	OUT_WPF4,
	OUT_WPD10,
	OUT_WPF1,
	OUT_WPB9,
	OUT_WPB10,
	OUT_WPC14,
	OUT_WPB5,
	OUT_WPC1,
	OUT_WPD14,
	OUT_WPG1,
	OUT_WPA14,
	OUT_WPD6,
	OUT_WPD3,
	OUT_WPG7,
	OUT_WPF5,
	OUT_WPD11,
	OUT_WPF0,
	OUT_WPB1,
	OUT_WPE5,
	OUT_WPC13,
	OUT_WPB3,
	OUT_WPC4,
	OUT_WPD15,
	OUT_WPG0,
	OUT_WPA15,
	OUT_WPD7,
	OUT_WPD9,
	OUT_WPG6,
	OUT_WPB8,
	OUT_WPB15,
	OUT_WPD4,
	OUT_WPB0,
	OUT_WPE3,
	OUT_WPB7,
	OUT_WPF12,
	OUT_WPD12,
	OUT_WPF8,
	OUT_WPC3,
	OUT_WPE9,
	OUT_WPD1,
	OUT_WPG9,
	OUT_WPB14,
	OUT_WPD0,
	OUT_WPB6,
	OUT_WPD5,
	OUT_WPB2,
	OUT_WPF3,
	OUT_WPF13,
	OUT_WPC2,
	OUT_WPE8,
	OUT_WPF2,
};

/* Output PPS Functions */
#define OUT_FUNC_U3TX 0x01
#define OUT_FUNC_U4WTS 0x02
#define OUT_FUNC_SDO1 0x05
#define OUT_FUNC_SDO2 0x06
#define OUT_FUNC_SDO3 0x07
#define OUT_FUNC_SDO5 0x09
#define OUT_FUNC_SS6 0x0A
#define OUT_FUNC_OC3 0x0B
#define OUT_FUNC_OC6 0x0C
#define OUT_FUNC_WEFCWKO4 0x0D
#define OUT_FUNC_C2OUT 0x0E
#define OUT_FUNC_C1TX 0x0F
#define OUT_FUNC_U1TX 0x01
#define OUT_FUNC_U2WTS 0x02
#define OUT_FUNC_U5TX 0x03
#define OUT_FUNC_U6WTS 0x04
#define OUT_FUNC_SDO1 0x05
#define OUT_FUNC_SDO2 0x06
#define OUT_FUNC_SDO3 0x07
#define OUT_FUNC_SDO4 0x08
#define OUT_FUNC_SDO5 0x09
#define OUT_FUNC_OC4 0x0B
#define OUT_FUNC_OC7 0x0C
#define OUT_FUNC_WEFCWKO1 0x0F
#define OUT_FUNC_U3WTS 0x01
#define OUT_FUNC_U4TX 0x02
#define OUT_FUNC_U6TX 0x04
#define OUT_FUNC_SS1 0x05
#define OUT_FUNC_SS3 0x07
#define OUT_FUNC_SS4 0x08
#define OUT_FUNC_SS5 0x09
#define OUT_FUNC_SDO6 0x0A
#define OUT_FUNC_OC5 0x0B
#define OUT_FUNC_OC8 0x0C
#define OUT_FUNC_C1OUT 0x0E
#define OUT_FUNC_WEFCWKO3 0x0F
#define OUT_FUNC_U1WTS 0x01
#define OUT_FUNC_U2TX 0x02
#define OUT_FUNC_U5WTS 0x03
#define OUT_FUNC_U6TX 0x04
#define OUT_FUNC_SS2 0x06
#define OUT_FUNC_SDO4 0x08
#define OUT_FUNC_SDO6 0x0A
#define OUT_FUNC_OC2 0x0B
#define OUT_FUNC_OC1 0x0C
#define OUT_FUNC_OC9 0x0D
#define OUT_FUNC_C2TX 0x0F

void pic32_pps_input(int function, int pin);
void pic32_pps_output(int function, int pin);

#endif
