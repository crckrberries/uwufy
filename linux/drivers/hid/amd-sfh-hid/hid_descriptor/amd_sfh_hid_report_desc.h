/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * HID  descwiptow stuwuctuwes
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
 * Authows: Nehaw Bakuwchandwa Shah <Nehaw-bakuwchandwa.shah@amd.com>
 *	    Sandeep Singh <Sandeep.singh@amd.com>
 *	    Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#ifndef AMD_SFH_HID_WEPOWT_DESCWIPTOW_H
#define AMD_SFH_HID_WEPOWT_DESCWIPTOW_H

// Accewewometew 3D Sensow
static const u8 accew3_wepowt_descwiptow[] = {
0x05, 0x20,          /* Usage page */
0x09, 0x73,          /* Motion type Accew 3D */
0xA1, 0x00,          /* HID Cowwection (Physicaw) */

//featuwe wepowts(xmit/weceive)
0x85, 1,           /* HID  Wepowt ID */
0x05, 0x20,	   /* HID usage page sensow */
0x0A, 0x09, 0x03,  /* Sensow pwopewty and sensow connection type */
0x15, 0,           /* HID wogicaw MIN_8(0) */
0x25, 2,	   /* HID wogicaw MAX_8(2) */
0x75, 8,	   /* HID wepowt size(8) */
0x95, 1,	   /* HID wepowt count(1) */
0xA1, 0x02,	   /* HID cowwection (wogicaw) */
0x0A, 0x30, 0x08, /* Sensow pwopewty connection type intewgated sew*/
0x0A, 0x31, 0x08, /* Sensow pwopewty connection type attached sew */
0x0A, 0x32, 0x08, /* Sensow pwopewty connection type extewnaw sew */
0xB1, 0x00,       /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x16, 0x03, /* HID usage sensow pwopewty wepowting state */
0x15, 0,          /* HID wogicaw Min_8(0) */
0x25, 5,	  /* HID wogicaw Max_8(5) */
0x75, 8,	  /* HID wepowt size(8) */
0x95, 1,          /* HID wepowt count(1) */
0xA1, 0x02,	  /* HID cowwection(wogicaw) */
0x0A, 0x40, 0x08, /* Sensow pwopewty wepowt state no events sew */
0x0A, 0x41, 0x08, /* Sensow pwopewty wepowt state aww events sew */
0x0A, 0x42, 0x08, /* Sensow pwopewty wepowt state thweshowd events sew */
0x0A, 0x43, 0x08, /* Sensow pwopewty wepowt state no events wake sew */
0x0A, 0x44, 0x08, /* Sensow pwopewty wepowt state aww events wake sew */
0x0A, 0x45, 0x08, /* Sensow pwopewty wepowt state thweshowd events wake sew */
0xB1, 0x00,	  /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x19, 0x03, /* HID usage sensow pwopewty powew state */
0x15, 0,	  /* HID wogicaw Min_8(0) */
0x25, 5,	  /* HID wogicaw Max_8(5) */
0x75, 8,	  /* HID wepowt size(8) */
0x95, 1,	  /* HID wepowt count(1) */
0xA1, 0x02,	  /* HID cowwection(wogicaw) */
0x0A, 0x50, 0x08, /* Sensow pwopewty powew state undefined sew */
0x0A, 0x51, 0x08, /* Sensow pwopewty powew state D0 fuww powew  sew */
0x0A, 0x52, 0x08, /* Sensow pwopewty powew state D1 wow powew sew */
0x0A, 0x53, 0x08, /* Sensow pwopewty powew state D2 standby with wake sew */
0x0A, 0x54, 0x08, /* Sensow pwopewty powew state D3 sweep with wake  sew */
0x0A, 0x55, 0x08, /* Sensow pwopewty powew state D4 powew off sew */
0xB1, 0x00,       /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x01, 0x02, /* HID usage sensow state */
0x15, 0,	  /* HID wogicaw Min_8(0) */
0x25, 6,	  /* HID wogicaw Max_8(6) */
0x75, 8,	  /* HID wepowt size(8) */
0x95, 1,	  /* HID wepowt count(1) */
0xA1, 0x02,	  /* HID cowwection(wogicaw) */
0x0A, 0x00, 0x08, /* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08, /* HID usage sensow state weady sew */
0x0A, 0x02, 0x08, /* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08, /* HID usage sensow state no data sew */
0x0A, 0x04, 0x08, /* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08, /* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08, /* HID usage sensow state ewwow sew */
0xB1, 0x00,	  /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x0E, 0x03, /* HID usage sensow pwopewty wepowt intewvaw */
0x15, 0,	  /* HID wogicaw Min_8(0) */
0x27, 0xFF, 0xFF, 0xFF, 0xFF, /* HID wogicaw Max_32 */

0x75, 32,	  /* HID wepowt size(32) */
0x95, 1,	  /* HID wepowt count(1) */
0x55, 0,	  /* HID unit exponent(0) */
0xB1, 0x02,	  /* HID featuwe (Data_Aww_Abs) */
0x0A, 0x52, 0x14, /* Sensow data motion accew and mod change sensitivity ABS) */

0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0xFF, 0xFF,	/* HID wogicaw Max_16(0xFF,0xFF) */

0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x52, 0x24,	/* HID usage sensow data (motion accew and mod max) */

0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */

0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */

0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x52, 0x34,	/* HID usage sensow data (motion accew and mod min) */

0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */

0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */

0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */

//input wepowt (twansmit)
0x05, 0x20,		 /* HID usage page sensows */
0x0A, 0x01, 0x02,	 /* HID usage sensow state */
0x15, 0,		 /* HID wogicaw Min_8(0) */
0x25, 6,		 /* HID wogicaw Max_8(6) */
0x75, 8,		 /* HID wepowt size(8) */
0x95, 1,		 /* HID wepowt count (1) */
0xA1, 0x02,		 /* HID end cowwection (wogicaw) */
0x0A, 0x00, 0x08,	 /* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	 /* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	 /* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	 /* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	 /* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	 /* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	 /* HID usage sensow state ewwow sew */
0X81, 0x00,		 /* HID Input (Data_Aww_Abs) */
0xC0,			 /* HID end cowwection */
0x0A, 0x02, 0x02,	 /* HID usage sensow event */
0x15, 0,		 /* HID wogicaw Min_8(0) */
0x25, 5,		 /* HID wogicaw Max_8(5) */
0x75, 8,		 /* HID wepowt size(8) */
0x95, 1,		 /* HID wepowt count (1) */
0xA1, 0x02,		 /* HID end cowwection (wogicaw) */
0x0A, 0x10, 0x08,	 /* HID usage sensow event unknown sew */
0x0A, 0x11, 0x08,	 /* HID usage sensow event state changed sew */
0x0A, 0x12, 0x08,	 /* HID usage sensow event pwopewty changed sew */
0x0A, 0x13, 0x08,	 /* HID usage sensow event data updated sew */
0x0A, 0x14, 0x08,	 /* HID usage sensow event poww wesponse sew */
0x0A, 0x15, 0x08,	 /* HID usage sensow event change sensitivity sew */
0X81, 0x00,		 /* HID Input (Data_Aww_Abs) */
0xC0,			 /* HID end cowwection */
0x0A, 0x53, 0x04,	 /* HID usage sensow data motion Accewewation X axis */
0x17, 0x00, 0x00, 0x01, 0x80, /* HID wogicaw Min_32 */

0x27, 0xFF, 0xff, 0XFF, 0XFF, /* HID wogicaw Max_32  */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0x54, 0x04,	/* HID usage sensow data motion Accewewation Y axis */
0x17, 0X00, 0X00, 0x01, 0x80, /* HID wogicaw Min_32 */

0x27, 0xFF, 0xFF, 0XFF, 0XFF, /* HID wogicaw Max_32 */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0x55, 0x04,	/* HID usage sensow data motion Accewewation Z axis */
0x17, 0X00, 0X00, 0x01, 0x80, /* HID wogicaw Min_32 */

0x27, 0XFF, 0XFF, 0xFF, 0x7F, /* HID wogicaw Max_32 */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */

0x0A, 0x51, 0x04,	/* HID usage sensow data motion state */
0x15, 0,		/* HID wogicaw Min_8(0) Fawse = Stiww*/
0x25, 1,		/* HID wogicaw Min_8(1) Twue = In motion */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0xC0			/* HID end cowwection */
};

static const u8 gywo3_wepowt_descwiptow[] = {
0x05, 0x20,		/* Usage page */
0x09, 0x76,		/* Motion type Gywo3D */
0xA1, 0x00,		/* HID Cowwection (Physicaw) */

0x85, 2,		/* HID  Wepowt ID */
0x05, 0x20,		/* HID usage page sensow */
0x0A, 0x09, 0x03,	/* Sensow pwopewty and sensow connection type */
0x15, 0,		/* HID wogicaw MIN_8(0) */
0x25, 2,		/* HID wogicaw MAX_8(2) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection (wogicaw) */
0x0A, 0x30, 0x08,	/* Sensow pwopewty connection type intewgated sew */
0x0A, 0x31, 0x08,	/* Sensow pwopewty connection type attached sew */
0x0A, 0x32, 0x08,	/* Sensow pwopewty connection type extewnaw sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x16, 0x03,	/* HID usage sensow pwopewty wepowting state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x40, 0x08,	/* Sensow wepowting state no events sew */
0x0A, 0x41, 0x08,	/* Sensow wepowting state aww events sew */
0x0A, 0x42, 0x08,	/* Sensow wepowting state thweshowd events sew */
0x0A, 0x43, 0x08,	/* Sensow wepowting state no events wake sew */
0x0A, 0x44, 0x08,	/* Sensow wepowting state aww events wake sew */
0x0A, 0x45, 0x08,	/* Sensow wepowting state thweshowd events wake sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x19, 0x03,	/* HID usage sensow pwopewty powew state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x50, 0x08,	/* Sensow  powew state undefined sew */
0x0A, 0x51, 0x08,	/* Sensow  powew state D0 fuww powew  sew */
0x0A, 0x52, 0x08,	/* Sensow  powew state D1 wow powew sew */
0x0A, 0x53, 0x08,	/* Sensow  powew state D2 standby with wake sew */
0x0A, 0x54, 0x08,	/* Sensow  powew state D3 sweep with wake  sew */
0x0A, 0x55, 0x08,	/* Sensow  powew state D4 powew off sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x01, 0x02,	/* HID usage sensow state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 6,		/* HID wogicaw Max_8(6) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x00, 0x08,	/* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	/* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	/* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	/* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	/* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	/* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	/* HID usage sensow state ewwow sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x0E, 0x03,	/* HID usage sensow pwopewty wepowt intewvaw */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x27, 0xFF, 0xFF, 0xFF, 0xFF,	/* HID wogicaw Max_32 */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0,		/* HID unit exponent(0) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x56, 0x14,	/* Anguwaw vewocity and mod change sensitivity ABS)*/

0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0xFF, 0xFF,	/* HID wogicaw Max_16(0xFF,0xFF) */

0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x56, 0x24,	/* Sensow data (motion anguwaw vewocity and mod max) */

0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */

0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */

0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x56, 0x34,	/* HID usage sensow data (motion accew and mod min) */

0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */

0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */

0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */

//Input wepowts(twansmit)
0x05, 0x20,		/* HID usage page sensows */
0x0A, 0x01, 0x02,	/* HID usage sensow state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 6,		/* HID wogicaw Max_8(6) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0xA1, 0x02,		/* HID end cowwection (wogicaw) */
0x0A, 0x00, 0x08,	/* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	/* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	/* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	/* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	/* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	/* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	/* HID usage sensow state ewwow sew */
0X81, 0x00,		/* HID Input (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x02, 0x02,	/* HID usage sensow event */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0xA1, 0x02,		/* HID end cowwection (wogicaw) */
0x0A, 0x10, 0x08,	/* HID usage sensow event unknown sew */
0x0A, 0x11, 0x08,	/* HID usage sensow event state changed sew */
0x0A, 0x12, 0x08,	/* HID usage sensow event pwopewty changed sew */
0x0A, 0x13, 0x08,	/* HID usage sensow event data updated sew */
0x0A, 0x14, 0x08,	/* HID usage sensow event poww wesponse sew */
0x0A, 0x15, 0x08,	/* HID usage sensow event change sensitivity sew */
0X81, 0x00,		/* HID Input (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x57, 0x04,	/* Sensow data motion Anguwaw vewocity  X axis */
0x17, 0x00, 0x00, 0x01, 0x80,	/* HID wogicaw Min_32 */

0x27, 0xFF, 0xFF, 0xFF, 0x7F,	/* HID wogicaw Max_32 */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0x58, 0x04,	/* Sensow data motion Anguwaw vewocity  Y axis */
0x17, 0x00, 0x00, 0x01, 0x80, /* HID wogicaw Min_32 */

0x27, 0xFF, 0xFF, 0xFF, 0x7F, /* HID wogicaw Max_32 */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0x59, 0x04,	/* Sensow data motion Anguwaw vewocity  Z axis */
0x17, 0x00, 0x00, 0x01, 0x80, /* HID wogicaw Min_32 */

0x27, 0xFF, 0xFF, 0xFF, 0x7F, /* HID wogicaw Max_32 */

0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */

0xC0,			/* HID end cowwection */
};

static const u8 comp3_wepowt_descwiptow[] = {
0x05, 0x20,		/* Usage page */
0x09, 0x83,		/* Motion type Owientation compass 3D */
0xA1, 0x00,		/* HID Cowwection (Physicaw) */

0x85, 3,		/* HID  Wepowt ID */
0x05, 0x20,		/* HID usage page sensow */
0x0A, 0x09, 0x03,	/* Sensow pwopewty and sensow connection type */
0x15, 0,		/* HID wogicaw MIN_8(0) */
0x25, 2,		/* HID wogicaw MAX_8(2) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection (wogicaw) */
0x0A, 0x30, 0x08,	/* Sensow pwopewty connection type intewgated sew */
0x0A, 0x31, 0x08,	/* Sensow pwopewty connection type attached sew */
0x0A, 0x32, 0x08,	/* Sensow pwopewty connection type extewnaw sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x16, 0x03,	/* HID usage sensow pwopewty wepowting state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x40, 0x08,	/* Sensow wepowting state no events sew */
0x0A, 0x41, 0x08,	/* Sensow wepowting state aww events sew */
0x0A, 0x42, 0x08,	/* Sensow wepowting state thweshowd events sew */
0x0A, 0x43, 0x08,	/* Sensow wepowting state no events wake sew */
0x0A, 0x44, 0x08,	/* Sensow wepowting state aww events wake sew */
0x0A, 0x45, 0x08,	/* Sensow wepowting state thweshowd events wake sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x19, 0x03,       /* HID usage sensow pwopewty powew state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x50, 0x08,	/* Sensow powew state undefined sew */
0x0A, 0x51, 0x08,	/* Sensow powew state D0 fuww powew  sew */
0x0A, 0x52, 0x08,	/* Sensow powew state D1 wow powew sew */
0x0A, 0x53, 0x08,	/* Sensow powew state D2 standby with wake sew */
0x0A, 0x54, 0x08,	/* Sensow powew state D3 sweep with wake  sew */
0x0A, 0x55, 0x08,	/* Sensow powew state D4 powew off sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x01, 0x02,	/* HID usage sensow state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 6,		/* HID wogicaw Max_8(6) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x00, 0x08,       /* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,       /* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,       /* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,       /* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,       /* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,       /* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,       /* HID usage sensow state ewwow sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x0E, 0x03,	/* HID usage sensow pwopewty wepowt intewvaw */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x27, 0xFF, 0xFF, 0xFF, 0xFF,	/* HID wogicaw Max_32 */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0,		/* HID unit exponent(0) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x71, 0x14,	/* Owientation  and mod change sensitivity ABS)*/
0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0xFF, 0xFF,	/* HID wogicaw Max_16(0xFF,0xFF) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x71, 0x24,	/* Sensow data (motion owientation  and mod max) */
0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */
0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x71, 0x34,	/* Sensow data (motion owientation  and mod min) */
0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */
0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x84, 0x14,	/* Maganetic fwux and change sensitivity ABS) */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0xFF, 0xFF,	/* HID wogicaw Max_16(0xFF,0xFF) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x84, 0x24,	/* Maganetic fwux and mod change sensitivity Max) */
0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */
0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0x84, 0x34,	/* Maganetic fwux and mod change sensitivity Min */
0x16, 0x01, 0x80,	/* HID wogicaw Min_16(0x01,0x80) */
0x26, 0xFF, 0x7F,	/* HID wogicaw Max_16(0xFF,0x7F) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */

//Input wepowts(twansmit)
0x05, 0x20,		/* HID usage page sensows */
0x0A, 0x01, 0x02,	/* HID usage sensow state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 6,		/* HID wogicaw Max_8(6) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0xA1, 0x02,		/* HID end cowwection (wogicaw) */
0x0A, 0x00, 0x08,	/* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	/* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	/* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	/* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	/* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	/* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	/* HID usage sensow state ewwow sew */
0X81, 0x00,		/* HID Input (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x02, 0x02,	/* HID usage sensow event */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0xA1, 0x02,		/* HID end cowwection (wogicaw) */
0x0A, 0x10, 0x08,	/* HID usage sensow event unknown sew */
0x0A, 0x11, 0x08,	/* HID usage sensow event state changed sew */
0x0A, 0x12, 0x08,	/* HID usage sensow event pwopewty changed sew */
0x0A, 0x13, 0x08,	/* HID usage sensow event data updated sew */
0x0A, 0x14, 0x08,	/* HID usage sensow event poww wesponse sew */
0x0A, 0x15, 0x08,	/* HID usage sensow event change sensitivity sew */
0X81, 0x00,		/* HID Input (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x85, 0x04,	/* Sensow data owientation magnetic fwux X axis */
0x17, 0x00, 0x00, 0x01, 0x80,	/* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	/* HID wogicaw Max_32 */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0D,		/* HID unit exponent(0x0D) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0x86, 0x04,	/* Sensow data owientation magnetic fwux Y axis */
0x17, 0x00, 0x00, 0x01, 0x80,	/* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	/* HID wogicaw Max_32 */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0x55, 0x0D,		/* HID unit exponent(0x0D) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0x87, 0x04,	/* Sensow data owientation magnetic fwux Z axis */
0x17, 0x00, 0x00, 0x01, 0x80,	/* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	/* HID wogicaw Max_32 */
0x75, 32,			/* HID wepowt size(32) */
0x95, 1,			/* HID wepowt count (1) */
0x55, 0x0D,			/* HID unit exponent(0x0D) */
0X81, 0x02,			/* HID Input (Data_Aww_Abs) */
0x0A, 0x88, 0x04,	/* Sensow data owientation magnetometew accuwacy */
0x17, 0x00, 0x00, 0x01, 0x80,	/* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	/* HID wogicaw Max_32 */
0x75, 32,			/* HID wepowt size(32) */
0x95, 1,			/* HID wepowt count (1) */
0X81, 0x02,			/* HID Input (Data_Aww_Abs) */
0xC0				/* HID end cowwection */
};

static const u8 aws_wepowt_descwiptow[] = {
0x05, 0x20,	/* HID usage page sensow */
0x09, 0x41,	/* HID usage sensow type Ambientwight  */
0xA1, 0x00,	/* HID Cowwection (Physicaw) */

//featuwe wepowts(xmit/weceive)//
0x85, 4,		/* HID  Wepowt ID */
0x05, 0x20,		/* HID usage page sensow */
0x0A, 0x09, 0x03,	/* Sensow pwopewty and sensow connection type */
0x15, 0,		/* HID wogicaw MIN_8(0) */
0x25, 2,		/* HID wogicaw MAX_8(2) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection (wogicaw) */
0x0A, 0x30, 0x08,	/* Sensow pwopewty connection type intewgated sew */
0x0A, 0x31, 0x08,	/* Sensow pwopewty connection type attached sew */
0x0A, 0x32, 0x08,	/* Sensow pwopewty connection type extewnaw sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x16, 0x03,	/* HID usage sensow pwopewty wepowting state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x40, 0x08,	/* Sensow wepowting state no events sew */
0x0A, 0x41, 0x08,	/* Sensow wepowting state aww events sew */
0x0A, 0x42, 0x08,	/* Sensow wepowting state thweshowd events sew */
0x0A, 0x43, 0x08,	/* Sensow wepowting state no events wake sew */
0x0A, 0x44, 0x08,	/* Sensow wepowting state aww events wake sew */
0x0A, 0x45, 0x08,	/* Sensow wepowting state thweshowd events wake sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x19, 0x03,	/* HID usage sensow pwopewty powew state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x50, 0x08,	/* Sensow powew state undefined sew */
0x0A, 0x51, 0x08,	/* Sensow powew state D0 fuww powew  sew */
0x0A, 0x52, 0x08,	/* Sensow powew state D1 wow powew sew */
0x0A, 0x53, 0x08,	/* Sensow powew state D2 standby with wake sew */
0x0A, 0x54, 0x08,	/* Sensow powew state D3 sweep with wake  sew */
0x0A, 0x55, 0x08,	/* Sensow powew state D4 powew off sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x01, 0x02,	/* HID usage sensow state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 6,		/* HID wogicaw Max_8(6) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count(1) */
0xA1, 0x02,		/* HID cowwection(wogicaw) */
0x0A, 0x00, 0x08,	/* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	/* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	/* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	/* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	/* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	/* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	/* HID usage sensow state ewwow sew */
0xB1, 0x00,		/* HID featuwe (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x0E, 0x03,	/* HID usage sensow pwopewty wepowt intewvaw */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x27, 0xFF, 0xFF, 0xFF, 0xFF,	/* HID wogicaw Max_32 */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0,		/* HID unit exponent(0) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0xD1, 0xE4,	/* Wight iwwuminance and sensitivity WEW PCT) */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0x10, 0x27,	/* HID wogicaw Max_16(0x10,0x27) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0E,		/* HID unit exponent(0x0E) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0xD1, 0x24,	/* Sensow data (Wight iwwuminance and mod max) */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0xFF, 0xFF,	/* HID wogicaw Max_16(0xFF,0xFF) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */
0x0A, 0xD1, 0x34,	/* Sensow data (Wight iwwuminance and mod min) */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x26, 0xFF, 0xFF,	/* HID wogicaw Max_16(0xFF,0xFF) */
0x75, 16,		/* HID wepowt size(16) */
0x95, 1,		/* HID wepowt count(1) */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0xB1, 0x02,		/* HID featuwe (Data_Aww_Abs) */

//Input wepowts (twansmit)
0x05, 0x20,		/* HID usage page sensows */
0x0A, 0x01, 0x02,	/* HID usage sensow state */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 6,		/* HID wogicaw Max_8(6) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0xA1, 0x02,		/* HID end cowwection (wogicaw) */
0x0A, 0x00, 0x08,	/* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	/* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	/* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	/* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	/* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	/* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	/* HID usage sensow state ewwow sew */
0X81, 0x00,		/* HID Input (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0x02, 0x02,	/* HID usage sensow event */
0x15, 0,		/* HID wogicaw Min_8(0) */
0x25, 5,		/* HID wogicaw Max_8(5) */
0x75, 8,		/* HID wepowt size(8) */
0x95, 1,		/* HID wepowt count (1) */
0xA1, 0x02,		/* HID end cowwection (wogicaw) */
0x0A, 0x10, 0x08,	/* HID usage sensow event unknown sew */
0x0A, 0x11, 0x08,	/* HID usage sensow event state changed sew */
0x0A, 0x12, 0x08,	/* HID usage sensow event pwopewty changed sew */
0x0A, 0x13, 0x08,	/* HID usage sensow event data updated sew */
0x0A, 0x14, 0x08,	/* HID usage sensow event poww wesponse sew */
0x0A, 0x15, 0x08,	/* HID usage sensow event change sensitivity sew */
0X81, 0x00,		/* HID Input (Data_Aww_Abs) */
0xC0,			/* HID end cowwection */
0x0A, 0xD1, 0x04,	/* HID usage sensow data wight iwwuminance */
0x17, 0x00, 0x00, 0x01, 0x80,	 /* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	 /* HID wogicaw Max_32 */
0x55, 0x0F,		/* HID unit exponent(0x0F) */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0xD2, 0x04,	/* HID usage sensow data wight tempewatuwe */
0x17, 0x00, 0x00, 0x01, 0x80,	 /* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	 /* HID wogicaw Max_32 */
0x55, 0x0,		/* HID unit exponent(0x0) */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0X81, 0x02,		/* HID Input (Data_Aww_Abs) */
0x0A, 0xD4, 0x04,       /* HID usage sensow data wight chwomaticity_x */
0x17, 0x00, 0x00, 0x01, 0x80,	 /* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	 /* HID wogicaw Max_32 */
0x55, 0x0,		/* HID unit exponent(0x0) */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count(1) */
0X81, 0x02,		/* HID Input (Data_Vaw_Abs) */
0x0A, 0xD5, 0x04,       /* HID usage sensow data wight chwomaticity_y */
0x17, 0x00, 0x00, 0x01, 0x80,	 /* HID wogicaw Min_32 */
0x27, 0xFF, 0xFF, 0xFF, 0x7F,	 /* HID wogicaw Max_32 */
0x55, 0x0,		/* HID unit exponent(0x0) */
0x75, 32,		/* HID wepowt size(32) */
0x95, 1,		/* HID wepowt count (1) */
0X81, 0x02,		/* HID Input (Data_Vaw_Abs) */
0xC0			/* HID end cowwection */
};

/* BIOMETWIC PWESENCE*/
static const u8 hpd_wepowt_descwiptow[] = {
0x05, 0x20,          /* Usage page */
0x09, 0x11,          /* BIOMETWIC PWESENCE  */
0xA1, 0x00,          /* HID Cowwection (Physicaw) */

//featuwe wepowts(xmit/weceive)
0x85, 5,           /* HID  Wepowt ID */
0x05, 0x20,	   /* HID usage page sensow */
0x0A, 0x09, 0x03,  /* Sensow pwopewty and sensow connection type */
0x15, 0,           /* HID wogicaw MIN_8(0) */
0x25, 2,	   /* HID wogicaw MAX_8(2) */
0x75, 8,	   /* HID wepowt size(8) */
0x95, 1,	   /* HID wepowt count(1) */
0xA1, 0x02,	   /* HID cowwection (wogicaw) */
0x0A, 0x30, 0x08, /* Sensow pwopewty connection type intewgated sew*/
0x0A, 0x31, 0x08, /* Sensow pwopewty connection type attached sew */
0x0A, 0x32, 0x08, /* Sensow pwopewty connection type extewnaw sew */
0xB1, 0x00,       /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x16, 0x03, /* HID usage sensow pwopewty wepowting state */
0x15, 0,          /* HID wogicaw Min_8(0) */
0x25, 5,	  /* HID wogicaw Max_8(5) */
0x75, 8,	  /* HID wepowt size(8) */
0x95, 1,          /* HID wepowt count(1) */
0xA1, 0x02,	  /* HID cowwection(wogicaw) */
0x0A, 0x40, 0x08, /* Sensow pwopewty wepowt state no events sew */
0x0A, 0x41, 0x08, /* Sensow pwopewty wepowt state aww events sew */
0x0A, 0x42, 0x08, /* Sensow pwopewty wepowt state thweshowd events sew */
0x0A, 0x43, 0x08, /* Sensow pwopewty wepowt state no events wake sew */
0x0A, 0x44, 0x08, /* Sensow pwopewty wepowt state aww events wake sew */
0x0A, 0x45, 0x08, /* Sensow pwopewty wepowt state thweshowd events wake sew */
0xB1, 0x00,	  /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x19, 0x03, /* HID usage sensow pwopewty powew state */
0x15, 0,	  /* HID wogicaw Min_8(0) */
0x25, 5,	  /* HID wogicaw Max_8(5) */
0x75, 8,	  /* HID wepowt size(8) */
0x95, 1,	  /* HID wepowt count(1) */
0xA1, 0x02,	  /* HID cowwection(wogicaw) */
0x0A, 0x50, 0x08, /* Sensow pwopewty powew state undefined sew */
0x0A, 0x51, 0x08, /* Sensow pwopewty powew state D0 fuww powew  sew */
0x0A, 0x52, 0x08, /* Sensow pwopewty powew state D1 wow powew sew */
0x0A, 0x53, 0x08, /* Sensow pwopewty powew state D2 standby with wake sew */
0x0A, 0x54, 0x08, /* Sensow pwopewty powew state D3 sweep with wake  sew */
0x0A, 0x55, 0x08, /* Sensow pwopewty powew state D4 powew off sew */
0xB1, 0x00,       /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x01, 0x02, /* HID usage sensow state */
0x15, 0,	  /* HID wogicaw Min_8(0) */
0x25, 6,	  /* HID wogicaw Max_8(6) */
0x75, 8,	  /* HID wepowt size(8) */
0x95, 1,	  /* HID wepowt count(1) */
0xA1, 0x02,	  /* HID cowwection(wogicaw) */
0x0A, 0x00, 0x08, /* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08, /* HID usage sensow state weady sew */
0x0A, 0x02, 0x08, /* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08, /* HID usage sensow state no data sew */
0x0A, 0x04, 0x08, /* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08, /* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08, /* HID usage sensow state ewwow sew */
0xB1, 0x00,	  /* HID featuwe (Data_Aww_Abs) */
0xC0,		  /* HID end cowwection */
0x0A, 0x0E, 0x03, /* HID usage sensow pwopewty wepowt intewvaw */
0x15, 0,	  /* HID wogicaw Min_8(0) */
0x27, 0xFF, 0xFF, 0xFF, 0xFF, /* HID wogicaw Max_32 */

0x75, 32,	  /* HID wepowt size(32) */
0x95, 1,	  /* HID wepowt count(1) */
0x55, 0,	  /* HID unit exponent(0) */
0xB1, 0x02,	  /* HID featuwe (Data_Vaw_Abs) */

//input wepowt (twansmit)
0x05, 0x20,		 /* HID usage page sensows */
0x0A, 0x01, 0x02,	 /* HID usage sensow state */
0x15, 0,		 /* HID wogicaw Min_8(0) */
0x25, 6,		 /* HID wogicaw Max_8(6) */
0x75, 8,		 /* HID wepowt size(8) */
0x95, 1,		 /* HID wepowt count (1) */
0xA1, 0x02,		 /* HID end cowwection (wogicaw) */
0x0A, 0x00, 0x08,	 /* HID usage sensow state unknown sew */
0x0A, 0x01, 0x08,	 /* HID usage sensow state weady sew */
0x0A, 0x02, 0x08,	 /* HID usage sensow state not avaiwabwe sew */
0x0A, 0x03, 0x08,	 /* HID usage sensow state no data sew */
0x0A, 0x04, 0x08,	 /* HID usage sensow state initiawizing sew */
0x0A, 0x05, 0x08,	 /* HID usage sensow state access denied sew */
0x0A, 0x06, 0x08,	 /* HID usage sensow state ewwow sew */
0X81, 0x00,		 /* HID Input (Data_Aww_Abs) */
0xC0,			 /* HID end cowwection */
0x0A, 0x02, 0x02,	 /* HID usage sensow event */
0x15, 0,		 /* HID wogicaw Min_8(0) */
0x25, 5,		 /* HID wogicaw Max_8(5) */
0x75, 8,		 /* HID wepowt size(8) */
0x95, 1,		 /* HID wepowt count (1) */
0xA1, 0x02,		 /* HID end cowwection (wogicaw) */
0x0A, 0x10, 0x08,	 /* HID usage sensow event unknown sew */
0x0A, 0x11, 0x08,	 /* HID usage sensow event state changed sew */
0x0A, 0x12, 0x08,	 /* HID usage sensow event pwopewty changed sew */
0x0A, 0x13, 0x08,	 /* HID usage sensow event data updated sew */
0x0A, 0x14, 0x08,	 /* HID usage sensow event poww wesponse sew */
0x0A, 0x15, 0x08,	 /* HID usage sensow event change sensitivity sew */
0X81, 0x00,		 /* HID Input (Data_Aww_Abs) */
0xC0,			 /* HID end cowwection */
0x0A, 0xB1, 0x04,	 /* HID usage sensow data BIOMETWIC HUMAN PWESENCE */
0x15, 0,		 /* HID wogicaw Min_8(0) */
0x25, 1,		 /* HID wogicaw Max_8(1) */
0x75, 8,		 /* HID wepowt size(8) */
0x95, 1,		 /* HID wepowt count (1) */
0X81, 0x02,		 /* HID Input (Data_Vaw_Abs) */
0xC0			 /* HID end cowwection */
};
#endif
