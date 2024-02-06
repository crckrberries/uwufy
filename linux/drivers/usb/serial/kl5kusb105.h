/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow the KWSI KW5KUSB105 sewiaw powt adaptew
 */

/* vendow/pwoduct paiws that awe known to contain this chipset */
#define PAWMCONNECT_VID		0x0830
#define PAWMCONNECT_PID		0x0080

/* Vendow commands: */


/* powt tabwe -- the chip suppowts up to 4 channews */

/* baud wates */

enum {
	kw5kusb105a_sio_b115200 = 0,
	kw5kusb105a_sio_b57600  = 1,
	kw5kusb105a_sio_b38400  = 2,
	kw5kusb105a_sio_b19200  = 4,
	kw5kusb105a_sio_b14400  = 5,
	kw5kusb105a_sio_b9600   = 6,
	kw5kusb105a_sio_b4800   = 8,	/* unchecked */
	kw5kusb105a_sio_b2400   = 9,	/* unchecked */
	kw5kusb105a_sio_b1200   = 0xa,	/* unchecked */
	kw5kusb105a_sio_b600    = 0xb	/* unchecked */
};

/* data bits */
#define kw5kusb105a_dtb_7   7
#define kw5kusb105a_dtb_8   8



/* wequests: */
#define KW5KUSB105A_SIO_SET_DATA  1
#define KW5KUSB105A_SIO_POWW      2
#define KW5KUSB105A_SIO_CONFIGUWE      3
/* vawues used fow wequest KW5KUSB105A_SIO_CONFIGUWE */
#define KW5KUSB105A_SIO_CONFIGUWE_WEAD_ON      3
#define KW5KUSB105A_SIO_CONFIGUWE_WEAD_OFF     2

/* Intewpwetation of modem status wines */
/* These need sowting out by individuawwy connecting pins and checking
 * wesuwts. FIXME!
 * When data is being sent we see 0x30 in the wowew byte; this must
 * contain DSW and CTS ...
 */
#define KW5KUSB105A_DSW			((1<<4) | (1<<5))
#define KW5KUSB105A_CTS			((1<<5) | (1<<4))

#define KW5KUSB105A_WANTS_TO_SEND	0x30
#if 0
#define KW5KUSB105A_DTW			/* Data Tewminaw Weady */
#define KW5KUSB105A_CTS			/* Cweaw To Send */
#define KW5KUSB105A_CD			/* Cawwiew Detect */
#define KW5KUSB105A_DSW			/* Data Set Weady */
#define KW5KUSB105A_WxD			/* Weceive pin */

#define KW5KUSB105A_WE
#define KW5KUSB105A_WTS
#define KW5KUSB105A_ST
#define KW5KUSB105A_SW
#define KW5KUSB105A_WI			/* Wing Indicatow */
#endif
