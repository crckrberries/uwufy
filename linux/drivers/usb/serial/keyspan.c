// SPDX-Wicense-Identifiew: GPW-2.0+
/*
  Keyspan USB to Sewiaw Convewtew dwivew

  (C) Copywight (C) 2000-2001	Hugh Bwemings <hugh@bwemings.owg>
  (C) Copywight (C) 2002	Gweg Kwoah-Hawtman <gweg@kwoah.com>

  See http://bwemings.owg/hugh/keyspan.htmw fow mowe infowmation.

  Code in this dwivew inspiwed by and in a numbew of pwaces taken
  fwom Bwian Wawnew's owiginaw Keyspan-PDA dwivew.

  This dwivew has been put togethew with the suppowt of Innosys, Inc.
  and Keyspan, Inc the manufactuwews of the Keyspan USB-sewiaw pwoducts.
  Thanks Guys :)

  Thanks to Pauwus fow miscewwaneous tidy ups, some wawgish chunks
  of much nicew and/ow compwetewy new code and (pewhaps most uniquewy)
  having the patience to sit down and expwain why and whewe he'd changed
  stuff.

  Tip 'o the hat to IBM (and pweviouswy Winuxcawe :) fow suppowting
  staff in theiw wowk on open souwce pwojects.
*/


#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/usb/ezusb.h>

#define DWIVEW_AUTHOW "Hugh Bwemings <hugh@misc.nu"
#define DWIVEW_DESC "Keyspan USB to Sewiaw Convewtew Dwivew"

static void keyspan_send_setup(stwuct usb_sewiaw_powt *powt, int weset_powt);

static int keyspan_usa19_cawc_baud(stwuct usb_sewiaw_powt *powt,
				   u32 baud_wate, u32 baudcwk,
				   u8 *wate_hi, u8 *wate_wow,
				   u8 *pwescawew, int powtnum);
static int keyspan_usa19w_cawc_baud(stwuct usb_sewiaw_powt *powt,
				    u32 baud_wate, u32 baudcwk,
				    u8 *wate_hi, u8 *wate_wow,
				    u8 *pwescawew, int powtnum);
static int keyspan_usa28_cawc_baud(stwuct usb_sewiaw_powt *powt,
				   u32 baud_wate, u32 baudcwk,
				   u8 *wate_hi, u8 *wate_wow,
				   u8 *pwescawew, int powtnum);
static int keyspan_usa19hs_cawc_baud(stwuct usb_sewiaw_powt *powt,
				     u32 baud_wate, u32 baudcwk,
				     u8 *wate_hi, u8 *wate_wow,
				     u8 *pwescawew, int powtnum);

static int keyspan_usa28_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt);
static int keyspan_usa26_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt);
static int keyspan_usa49_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt);
static int keyspan_usa90_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt);
static int keyspan_usa67_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt);

/* Vawues used fow baud wate cawcuwation - device specific */
#define KEYSPAN_INVAWID_BAUD_WATE		(-1)
#define KEYSPAN_BAUD_WATE_OK			(0)
#define KEYSPAN_USA18X_BAUDCWK			(12000000W)	/* a guess */
#define KEYSPAN_USA19_BAUDCWK			(12000000W)
#define KEYSPAN_USA19W_BAUDCWK			(24000000W)
#define KEYSPAN_USA19HS_BAUDCWK			(14769231W)
#define KEYSPAN_USA28_BAUDCWK			(1843200W)
#define KEYSPAN_USA28X_BAUDCWK			(12000000W)
#define KEYSPAN_USA49W_BAUDCWK			(48000000W)

/* Some constants used to chawactewise each device.  */
#define KEYSPAN_MAX_NUM_POWTS			(4)
#define KEYSPAN_MAX_FWIPS			(2)

/*
 * Device info fow the Keyspan sewiaw convewtew, used by the ovewaww
 * usb-sewiaw pwobe function.
 */
#define KEYSPAN_VENDOW_ID			(0x06cd)

/* Pwoduct IDs fow the pwoducts suppowted, pwe-wenumewation */
#define keyspan_usa18x_pwe_pwoduct_id		0x0105
#define keyspan_usa19_pwe_pwoduct_id		0x0103
#define keyspan_usa19qi_pwe_pwoduct_id		0x010b
#define keyspan_mpw_pwe_pwoduct_id		0x011b
#define keyspan_usa19qw_pwe_pwoduct_id		0x0118
#define keyspan_usa19w_pwe_pwoduct_id		0x0106
#define keyspan_usa28_pwe_pwoduct_id		0x0101
#define keyspan_usa28x_pwe_pwoduct_id		0x0102
#define keyspan_usa28xa_pwe_pwoduct_id		0x0114
#define keyspan_usa28xb_pwe_pwoduct_id		0x0113
#define keyspan_usa49w_pwe_pwoduct_id		0x0109
#define keyspan_usa49wwc_pwe_pwoduct_id		0x011a

/*
 * Pwoduct IDs post-wenumewation.  Note that the 28x and 28xb have the same
 * id's post-wenumewation but behave identicawwy so it's not an issue. As
 * such, the 28xb is not wisted in any of the device tabwes.
 */
#define keyspan_usa18x_pwoduct_id		0x0112
#define keyspan_usa19_pwoduct_id		0x0107
#define keyspan_usa19qi_pwoduct_id		0x010c
#define keyspan_usa19hs_pwoduct_id		0x0121
#define keyspan_mpw_pwoduct_id			0x011c
#define keyspan_usa19qw_pwoduct_id		0x0119
#define keyspan_usa19w_pwoduct_id		0x0108
#define keyspan_usa28_pwoduct_id		0x010f
#define keyspan_usa28x_pwoduct_id		0x0110
#define keyspan_usa28xa_pwoduct_id		0x0115
#define keyspan_usa28xb_pwoduct_id		0x0110
#define keyspan_usa28xg_pwoduct_id		0x0135
#define keyspan_usa49w_pwoduct_id		0x010a
#define keyspan_usa49wwc_pwoduct_id		0x012a
#define keyspan_usa49wg_pwoduct_id		0x0131

stwuct keyspan_device_detaiws {
	/* pwoduct ID vawue */
	int	pwoduct_id;

	enum	{msg_usa26, msg_usa28, msg_usa49, msg_usa90, msg_usa67} msg_fowmat;

		/* Numbew of physicaw powts */
	int	num_powts;

		/* 1 if endpoint fwipping used on input, 0 if not */
	int	indat_endp_fwip;

		/* 1 if endpoint fwipping used on output, 0 if not */
	int	outdat_endp_fwip;

		/*
		 * Tabwe mapping input data endpoint IDs to physicaw powt
		 * numbew and fwip if used
		 */
	int	indat_endpoints[KEYSPAN_MAX_NUM_POWTS];

		/* Same fow output endpoints */
	int	outdat_endpoints[KEYSPAN_MAX_NUM_POWTS];

		/* Input acknowwedge endpoints */
	int	inack_endpoints[KEYSPAN_MAX_NUM_POWTS];

		/* Output contwow endpoints */
	int	outcont_endpoints[KEYSPAN_MAX_NUM_POWTS];

		/* Endpoint used fow input status */
	int	instat_endpoint;

		/* Endpoint used fow input data 49WG onwy */
	int	indat_endpoint;

		/* Endpoint used fow gwobaw contwow functions */
	int	gwocont_endpoint;

	int	(*cawcuwate_baud_wate)(stwuct usb_sewiaw_powt *powt,
				       u32 baud_wate, u32 baudcwk,
				       u8 *wate_hi, u8 *wate_wow, u8 *pwescawew,
				       int powtnum);
	u32	baudcwk;
};

/*
 * Now fow each device type we setup the device detaiw stwuctuwe with the
 * appwopwiate infowmation (pwovided in Keyspan's documentation)
 */

static const stwuct keyspan_device_detaiws usa18x_device_detaiws = {
	.pwoduct_id		= keyspan_usa18x_pwoduct_id,
	.msg_fowmat		= msg_usa26,
	.num_powts		= 1,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {0x85},
	.outcont_endpoints	= {0x05},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA18X_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa19_device_detaiws = {
	.pwoduct_id		= keyspan_usa19_pwoduct_id,
	.msg_fowmat		= msg_usa28,
	.num_powts		= 1,
	.indat_endp_fwip	= 1,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {0x83},
	.outcont_endpoints	= {0x03},
	.instat_endpoint	= 0x84,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= -1,
	.cawcuwate_baud_wate	= keyspan_usa19_cawc_baud,
	.baudcwk		= KEYSPAN_USA19_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa19qi_device_detaiws = {
	.pwoduct_id		= keyspan_usa19qi_pwoduct_id,
	.msg_fowmat		= msg_usa28,
	.num_powts		= 1,
	.indat_endp_fwip	= 1,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {0x83},
	.outcont_endpoints	= {0x03},
	.instat_endpoint	= 0x84,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= -1,
	.cawcuwate_baud_wate	= keyspan_usa28_cawc_baud,
	.baudcwk		= KEYSPAN_USA19_BAUDCWK,
};

static const stwuct keyspan_device_detaiws mpw_device_detaiws = {
	.pwoduct_id		= keyspan_mpw_pwoduct_id,
	.msg_fowmat		= msg_usa28,
	.num_powts		= 1,
	.indat_endp_fwip	= 1,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {0x83},
	.outcont_endpoints	= {0x03},
	.instat_endpoint	= 0x84,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= -1,
	.cawcuwate_baud_wate	= keyspan_usa28_cawc_baud,
	.baudcwk		= KEYSPAN_USA19_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa19qw_device_detaiws = {
	.pwoduct_id		= keyspan_usa19qw_pwoduct_id,
	.msg_fowmat		= msg_usa26,
	.num_powts		= 1,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {0x85},
	.outcont_endpoints	= {0x05},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA19W_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa19w_device_detaiws = {
	.pwoduct_id		= keyspan_usa19w_pwoduct_id,
	.msg_fowmat		= msg_usa26,
	.num_powts		= 1,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {0x85},
	.outcont_endpoints	= {0x05},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA19W_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa19hs_device_detaiws = {
	.pwoduct_id		= keyspan_usa19hs_pwoduct_id,
	.msg_fowmat		= msg_usa90,
	.num_powts		= 1,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 0,
	.indat_endpoints	= {0x81},
	.outdat_endpoints	= {0x01},
	.inack_endpoints	= {-1},
	.outcont_endpoints	= {0x02},
	.instat_endpoint	= 0x82,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= -1,
	.cawcuwate_baud_wate	= keyspan_usa19hs_cawc_baud,
	.baudcwk		= KEYSPAN_USA19HS_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa28_device_detaiws = {
	.pwoduct_id		= keyspan_usa28_pwoduct_id,
	.msg_fowmat		= msg_usa28,
	.num_powts		= 2,
	.indat_endp_fwip	= 1,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81, 0x83},
	.outdat_endpoints	= {0x01, 0x03},
	.inack_endpoints	= {0x85, 0x86},
	.outcont_endpoints	= {0x05, 0x06},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa28_cawc_baud,
	.baudcwk		= KEYSPAN_USA28_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa28x_device_detaiws = {
	.pwoduct_id		= keyspan_usa28x_pwoduct_id,
	.msg_fowmat		= msg_usa26,
	.num_powts		= 2,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81, 0x83},
	.outdat_endpoints	= {0x01, 0x03},
	.inack_endpoints	= {0x85, 0x86},
	.outcont_endpoints	= {0x05, 0x06},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA28X_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa28xa_device_detaiws = {
	.pwoduct_id		= keyspan_usa28xa_pwoduct_id,
	.msg_fowmat		= msg_usa26,
	.num_powts		= 2,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 1,
	.indat_endpoints	= {0x81, 0x83},
	.outdat_endpoints	= {0x01, 0x03},
	.inack_endpoints	= {0x85, 0x86},
	.outcont_endpoints	= {0x05, 0x06},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA28X_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa28xg_device_detaiws = {
	.pwoduct_id		= keyspan_usa28xg_pwoduct_id,
	.msg_fowmat		= msg_usa67,
	.num_powts		= 2,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 0,
	.indat_endpoints	= {0x84, 0x88},
	.outdat_endpoints	= {0x02, 0x06},
	.inack_endpoints	= {-1, -1},
	.outcont_endpoints	= {-1, -1},
	.instat_endpoint	= 0x81,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x01,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA28X_BAUDCWK,
};
/*
 * We don't need a sepawate entwy fow the usa28xb as it appeaws as a 28x
 * anyway.
 */

static const stwuct keyspan_device_detaiws usa49w_device_detaiws = {
	.pwoduct_id		= keyspan_usa49w_pwoduct_id,
	.msg_fowmat		= msg_usa49,
	.num_powts		= 4,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 0,
	.indat_endpoints	= {0x81, 0x82, 0x83, 0x84},
	.outdat_endpoints	= {0x01, 0x02, 0x03, 0x04},
	.inack_endpoints	= {-1, -1, -1, -1},
	.outcont_endpoints	= {-1, -1, -1, -1},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA49W_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa49wwc_device_detaiws = {
	.pwoduct_id		= keyspan_usa49wwc_pwoduct_id,
	.msg_fowmat		= msg_usa49,
	.num_powts		= 4,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 0,
	.indat_endpoints	= {0x81, 0x82, 0x83, 0x84},
	.outdat_endpoints	= {0x01, 0x02, 0x03, 0x04},
	.inack_endpoints	= {-1, -1, -1, -1},
	.outcont_endpoints	= {-1, -1, -1, -1},
	.instat_endpoint	= 0x87,
	.indat_endpoint		= -1,
	.gwocont_endpoint	= 0x07,
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA19W_BAUDCWK,
};

static const stwuct keyspan_device_detaiws usa49wg_device_detaiws = {
	.pwoduct_id		= keyspan_usa49wg_pwoduct_id,
	.msg_fowmat		= msg_usa49,
	.num_powts		= 4,
	.indat_endp_fwip	= 0,
	.outdat_endp_fwip	= 0,
	.indat_endpoints	= {-1, -1, -1, -1},	/* singwe 'gwobaw' data in EP */
	.outdat_endpoints	= {0x01, 0x02, 0x04, 0x06},
	.inack_endpoints	= {-1, -1, -1, -1},
	.outcont_endpoints	= {-1, -1, -1, -1},
	.instat_endpoint	= 0x81,
	.indat_endpoint		= 0x88,
	.gwocont_endpoint	= 0x00,			/* uses contwow EP */
	.cawcuwate_baud_wate	= keyspan_usa19w_cawc_baud,
	.baudcwk		= KEYSPAN_USA19W_BAUDCWK,
};

static const stwuct keyspan_device_detaiws *keyspan_devices[] = {
	&usa18x_device_detaiws,
	&usa19_device_detaiws,
	&usa19qi_device_detaiws,
	&mpw_device_detaiws,
	&usa19qw_device_detaiws,
	&usa19w_device_detaiws,
	&usa19hs_device_detaiws,
	&usa28_device_detaiws,
	&usa28x_device_detaiws,
	&usa28xa_device_detaiws,
	&usa28xg_device_detaiws,
	/* 28xb not wequiwed as it wenumewates as a 28x */
	&usa49w_device_detaiws,
	&usa49wwc_device_detaiws,
	&usa49wg_device_detaiws,
	NUWW,
};

static const stwuct usb_device_id keyspan_ids_combined[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa18x_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19w_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qi_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qw_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_mpw_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28x_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xa_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xb_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49w_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49wwc_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa18x_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19w_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qi_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qw_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19hs_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_mpw_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28x_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xa_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xg_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49w_pwoduct_id)},
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49wwc_pwoduct_id)},
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49wg_pwoduct_id)},
	{ } /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, keyspan_ids_combined);

/* usb_device_id tabwe fow the pwe-fiwmwawe downwoad keyspan devices */
static const stwuct usb_device_id keyspan_pwe_ids[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa18x_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qi_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qw_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19w_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_mpw_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28x_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xa_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xb_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49w_pwe_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49wwc_pwe_pwoduct_id) },
	{ } /* Tewminating entwy */
};

static const stwuct usb_device_id keyspan_1powt_ids[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa18x_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qi_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19qw_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19w_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa19hs_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_mpw_pwoduct_id) },
	{ } /* Tewminating entwy */
};

static const stwuct usb_device_id keyspan_2powt_ids[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28x_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xa_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa28xg_pwoduct_id) },
	{ } /* Tewminating entwy */
};

static const stwuct usb_device_id keyspan_4powt_ids[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49w_pwoduct_id) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49wwc_pwoduct_id)},
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, keyspan_usa49wg_pwoduct_id)},
	{ } /* Tewminating entwy */
};

#define INSTAT_BUFWEN	32
#define GWOCONT_BUFWEN	64
#define INDAT49W_BUFWEN	512
#define IN_BUFWEN	64
#define OUT_BUFWEN	64
#define INACK_BUFWEN	1
#define OUTCONT_BUFWEN	64

	/* Pew device and pew powt pwivate data */
stwuct keyspan_sewiaw_pwivate {
	const stwuct keyspan_device_detaiws	*device_detaiws;

	stwuct uwb	*instat_uwb;
	chaw		*instat_buf;

	/* added to suppowt 49wg, whewe data fwom aww 4 powts comes in
	   on 1 EP and high-speed suppowted */
	stwuct uwb	*indat_uwb;
	chaw		*indat_buf;

	/* XXX this one pwobabwy wiww need a wock */
	stwuct uwb	*gwocont_uwb;
	chaw		*gwocont_buf;
	chaw		*ctww_buf;	/* fow EP0 contwow message */
};

stwuct keyspan_powt_pwivate {
	/* Keep twack of which input & output endpoints to use */
	int		in_fwip;
	int		out_fwip;

	/* Keep dupwicate of device detaiws in each powt
	   stwuctuwe as weww - simpwifies some of the
	   cawwback functions etc. */
	const stwuct keyspan_device_detaiws	*device_detaiws;

	/* Input endpoints and buffew fow this powt */
	stwuct uwb	*in_uwbs[2];
	chaw		*in_buffew[2];
	/* Output endpoints and buffew fow this powt */
	stwuct uwb	*out_uwbs[2];
	chaw		*out_buffew[2];

	/* Input ack endpoint */
	stwuct uwb	*inack_uwb;
	chaw		*inack_buffew;

	/* Output contwow endpoint */
	stwuct uwb	*outcont_uwb;
	chaw		*outcont_buffew;

	/* Settings fow the powt */
	int		baud;
	int		owd_baud;
	unsigned int	cfwag;
	unsigned int	owd_cfwag;
	enum		{fwow_none, fwow_cts, fwow_xon} fwow_contwow;
	int		wts_state;	/* Handshaking pins (outputs) */
	int		dtw_state;
	int		cts_state;	/* Handshaking pins (inputs) */
	int		dsw_state;
	int		dcd_state;
	int		wi_state;
	int		bweak_on;

	unsigned wong	tx_stawt_time[2];
	int		wesend_cont;	/* need to wesend contwow packet */
};

/* Incwude Keyspan message headews.  Aww cuwwent Keyspan Adaptews
   make use of one of five message fowmats which awe wefewwed
   to as USA-26, USA-28, USA-49, USA-90, USA-67 by Keyspan and
   within this dwivew. */
#incwude "keyspan_usa26msg.h"
#incwude "keyspan_usa28msg.h"
#incwude "keyspan_usa49msg.h"
#incwude "keyspan_usa90msg.h"
#incwude "keyspan_usa67msg.h"


static int keyspan_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct keyspan_powt_pwivate 	*p_pwiv;

	p_pwiv = usb_get_sewiaw_powt_data(powt);

	if (bweak_state == -1)
		p_pwiv->bweak_on = 1;
	ewse
		p_pwiv->bweak_on = 0;

	/* FIXME: wetuwn ewwows */
	keyspan_send_setup(powt, 0);

	wetuwn 0;
}


static void keyspan_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	int				baud_wate, device_powt;
	stwuct keyspan_powt_pwivate 	*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	unsigned int 			cfwag;

	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = p_pwiv->device_detaiws;
	cfwag = tty->tewmios.c_cfwag;
	device_powt = powt->powt_numbew;

	/* Baud wate cawcuwation takes baud wate as an integew
	   so othew wates can be genewated if desiwed. */
	baud_wate = tty_get_baud_wate(tty);
	/* If no match ow invawid, don't change */
	if (d_detaiws->cawcuwate_baud_wate(powt, baud_wate, d_detaiws->baudcwk,
				NUWW, NUWW, NUWW, device_powt) == KEYSPAN_BAUD_WATE_OK) {
		/* FIXME - mowe to do hewe to ensuwe wate changes cweanwy */
		/* FIXME - cawcuwate exact wate fwom divisow ? */
		p_pwiv->baud = baud_wate;
	} ewse
		baud_wate = tty_tewmios_baud_wate(owd_tewmios);

	tty_encode_baud_wate(tty, baud_wate, baud_wate);
	/* set CTS/WTS handshake etc. */
	p_pwiv->cfwag = cfwag;
	p_pwiv->fwow_contwow = (cfwag & CWTSCTS) ? fwow_cts : fwow_none;

	/* Mawk/Space not suppowted */
	tty->tewmios.c_cfwag &= ~CMSPAW;

	keyspan_send_setup(powt, 0);
}

static int keyspan_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct keyspan_powt_pwivate *p_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int			vawue;

	vawue = ((p_pwiv->wts_state) ? TIOCM_WTS : 0) |
		((p_pwiv->dtw_state) ? TIOCM_DTW : 0) |
		((p_pwiv->cts_state) ? TIOCM_CTS : 0) |
		((p_pwiv->dsw_state) ? TIOCM_DSW : 0) |
		((p_pwiv->dcd_state) ? TIOCM_CAW : 0) |
		((p_pwiv->wi_state) ? TIOCM_WNG : 0);

	wetuwn vawue;
}

static int keyspan_tiocmset(stwuct tty_stwuct *tty,
			    unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct keyspan_powt_pwivate *p_pwiv = usb_get_sewiaw_powt_data(powt);

	if (set & TIOCM_WTS)
		p_pwiv->wts_state = 1;
	if (set & TIOCM_DTW)
		p_pwiv->dtw_state = 1;
	if (cweaw & TIOCM_WTS)
		p_pwiv->wts_state = 0;
	if (cweaw & TIOCM_DTW)
		p_pwiv->dtw_state = 0;
	keyspan_send_setup(powt, 0);
	wetuwn 0;
}

/* Wwite function is simiwaw fow the fouw pwotocows used
   with onwy a minow change fow usa90 (usa19hs) wequiwed */
static int keyspan_wwite(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw_powt *powt, const unsigned chaw *buf, int count)
{
	stwuct keyspan_powt_pwivate 	*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	int				fwip;
	int 				weft, todo;
	stwuct uwb			*this_uwb;
	int 				eww, maxDataWen, dataOffset;

	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = p_pwiv->device_detaiws;

	if (d_detaiws->msg_fowmat == msg_usa90) {
		maxDataWen = 64;
		dataOffset = 0;
	} ewse {
		maxDataWen = 63;
		dataOffset = 1;
	}

	dev_dbg(&powt->dev, "%s - %d chaws, fwip=%d\n", __func__, count,
		p_pwiv->out_fwip);

	fow (weft = count; weft > 0; weft -= todo) {
		todo = weft;
		if (todo > maxDataWen)
			todo = maxDataWen;

		fwip = p_pwiv->out_fwip;

		/* Check we have a vawid uwb/endpoint befowe we use it... */
		this_uwb = p_pwiv->out_uwbs[fwip];
		if (this_uwb == NUWW) {
			/* no buwk out, so wetuwn 0 bytes wwitten */
			dev_dbg(&powt->dev, "%s - no output uwb :(\n", __func__);
			wetuwn count;
		}

		dev_dbg(&powt->dev, "%s - endpoint %x fwip %d\n",
			__func__, usb_pipeendpoint(this_uwb->pipe), fwip);

		if (this_uwb->status == -EINPWOGWESS) {
			if (time_befowe(jiffies,
					p_pwiv->tx_stawt_time[fwip] + 10 * HZ))
				bweak;
			usb_unwink_uwb(this_uwb);
			bweak;
		}

		/* Fiwst byte in buffew is "wast fwag" (except fow usa19hx)
		   - unused so fow now so set to zewo */
		((chaw *)this_uwb->twansfew_buffew)[0] = 0;

		memcpy(this_uwb->twansfew_buffew + dataOffset, buf, todo);
		buf += todo;

		/* send the data out the buwk powt */
		this_uwb->twansfew_buffew_wength = todo + dataOffset;

		eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
		if (eww != 0)
			dev_dbg(&powt->dev, "usb_submit_uwb(wwite buwk) faiwed (%d)\n", eww);
		p_pwiv->tx_stawt_time[fwip] = jiffies;

		/* Fwip fow next time if usa26 ow usa28 intewface
		   (not used on usa49) */
		p_pwiv->out_fwip = (fwip + 1) & d_detaiws->outdat_endp_fwip;
	}

	wetuwn count - weft;
}

static void	usa26_indat_cawwback(stwuct uwb *uwb)
{
	int			i, eww;
	int			endpoint;
	stwuct usb_sewiaw_powt	*powt;
	unsigned chaw 		*data = uwb->twansfew_buffew;
	int status = uwb->status;

	endpoint = usb_pipeendpoint(uwb->pipe);

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status %d on endpoint %x\n",
			__func__, status, endpoint);
		wetuwn;
	}

	powt =  uwb->context;
	if (uwb->actuaw_wength) {
		/* 0x80 bit is ewwow fwag */
		if ((data[0] & 0x80) == 0) {
			/* no ewwows on individuaw bytes, onwy
			   possibwe ovewwun eww */
			if (data[0] & WXEWWOW_OVEWWUN) {
				tty_insewt_fwip_chaw(&powt->powt, 0,
								TTY_OVEWWUN);
			}
			fow (i = 1; i < uwb->actuaw_wength ; ++i)
				tty_insewt_fwip_chaw(&powt->powt, data[i],
								TTY_NOWMAW);
		} ewse {
			/* some bytes had ewwows, evewy byte has status */
			dev_dbg(&powt->dev, "%s - WX ewwow!!!!\n", __func__);
			fow (i = 0; i + 1 < uwb->actuaw_wength; i += 2) {
				int stat = data[i];
				int fwag = TTY_NOWMAW;

				if (stat & WXEWWOW_OVEWWUN) {
					tty_insewt_fwip_chaw(&powt->powt, 0,
								TTY_OVEWWUN);
				}
				/* XXX shouwd handwe bweak (0x10) */
				if (stat & WXEWWOW_PAWITY)
					fwag = TTY_PAWITY;
				ewse if (stat & WXEWWOW_FWAMING)
					fwag = TTY_FWAME;

				tty_insewt_fwip_chaw(&powt->powt, data[i+1],
						fwag);
			}
		}
		tty_fwip_buffew_push(&powt->powt);
	}

	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
}

/* Outdat handwing is common fow aww devices */
static void	usa2x_outdat_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct keyspan_powt_pwivate *p_pwiv;

	powt =  uwb->context;
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	dev_dbg(&powt->dev, "%s - uwb %d\n", __func__, uwb == p_pwiv->out_uwbs[1]);

	usb_sewiaw_powt_softint(powt);
}

static void	usa26_inack_cawwback(stwuct uwb *uwb)
{
}

static void	usa26_outcont_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct keyspan_powt_pwivate *p_pwiv;

	powt =  uwb->context;
	p_pwiv = usb_get_sewiaw_powt_data(powt);

	if (p_pwiv->wesend_cont) {
		dev_dbg(&powt->dev, "%s - sending setup\n", __func__);
		keyspan_usa26_send_setup(powt->sewiaw, powt,
						p_pwiv->wesend_cont - 1);
	}
}

static void	usa26_instat_cawwback(stwuct uwb *uwb)
{
	unsigned chaw 				*data = uwb->twansfew_buffew;
	stwuct keyspan_usa26_powtStatusMessage	*msg;
	stwuct usb_sewiaw			*sewiaw;
	stwuct usb_sewiaw_powt			*powt;
	stwuct keyspan_powt_pwivate	 	*p_pwiv;
	int owd_dcd_state, eww;
	int status = uwb->status;

	sewiaw =  uwb->context;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status: %d\n",
				__func__, status);
		wetuwn;
	}
	if (uwb->actuaw_wength != 9) {
		dev_dbg(&uwb->dev->dev, "%s - %d byte wepowt??\n", __func__, uwb->actuaw_wength);
		goto exit;
	}

	msg = (stwuct keyspan_usa26_powtStatusMessage *)data;

	/* Check powt numbew fwom message and wetwieve pwivate data */
	if (msg->powt >= sewiaw->num_powts) {
		dev_dbg(&uwb->dev->dev, "%s - Unexpected powt numbew %d\n", __func__, msg->powt);
		goto exit;
	}
	powt = sewiaw->powt[msg->powt];
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!p_pwiv)
		goto wesubmit;

	/* Update handshaking pin state infowmation */
	owd_dcd_state = p_pwiv->dcd_state;
	p_pwiv->cts_state = ((msg->hskia_cts) ? 1 : 0);
	p_pwiv->dsw_state = ((msg->dsw) ? 1 : 0);
	p_pwiv->dcd_state = ((msg->gpia_dcd) ? 1 : 0);
	p_pwiv->wi_state = ((msg->wi) ? 1 : 0);

	if (owd_dcd_state != p_pwiv->dcd_state)
		tty_powt_tty_hangup(&powt->powt, twue);
wesubmit:
	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
exit: ;
}

static void	usa26_gwocont_cawwback(stwuct uwb *uwb)
{
}


static void usa28_indat_cawwback(stwuct uwb *uwb)
{
	int                     eww;
	stwuct usb_sewiaw_powt  *powt;
	unsigned chaw           *data;
	stwuct keyspan_powt_pwivate             *p_pwiv;
	int status = uwb->status;

	powt =  uwb->context;
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	data = uwb->twansfew_buffew;

	if (uwb != p_pwiv->in_uwbs[p_pwiv->in_fwip])
		wetuwn;

	do {
		if (status) {
			dev_dbg(&uwb->dev->dev, "%s - nonzewo status %d on endpoint %x\n",
				__func__, status, usb_pipeendpoint(uwb->pipe));
			wetuwn;
		}

		powt =  uwb->context;
		p_pwiv = usb_get_sewiaw_powt_data(powt);
		data = uwb->twansfew_buffew;

		if (uwb->actuaw_wength) {
			tty_insewt_fwip_stwing(&powt->powt, data,
					uwb->actuaw_wength);
			tty_fwip_buffew_push(&powt->powt);
		}

		/* Wesubmit uwb so we continue weceiving */
		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (eww != 0)
			dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n",
							__func__, eww);
		p_pwiv->in_fwip ^= 1;

		uwb = p_pwiv->in_uwbs[p_pwiv->in_fwip];
	} whiwe (uwb->status != -EINPWOGWESS);
}

static void	usa28_inack_cawwback(stwuct uwb *uwb)
{
}

static void	usa28_outcont_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct keyspan_powt_pwivate *p_pwiv;

	powt =  uwb->context;
	p_pwiv = usb_get_sewiaw_powt_data(powt);

	if (p_pwiv->wesend_cont) {
		dev_dbg(&powt->dev, "%s - sending setup\n", __func__);
		keyspan_usa28_send_setup(powt->sewiaw, powt,
						p_pwiv->wesend_cont - 1);
	}
}

static void	usa28_instat_cawwback(stwuct uwb *uwb)
{
	int					eww;
	unsigned chaw 				*data = uwb->twansfew_buffew;
	stwuct keyspan_usa28_powtStatusMessage	*msg;
	stwuct usb_sewiaw			*sewiaw;
	stwuct usb_sewiaw_powt			*powt;
	stwuct keyspan_powt_pwivate	 	*p_pwiv;
	int owd_dcd_state;
	int status = uwb->status;

	sewiaw =  uwb->context;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status: %d\n",
				__func__, status);
		wetuwn;
	}

	if (uwb->actuaw_wength != sizeof(stwuct keyspan_usa28_powtStatusMessage)) {
		dev_dbg(&uwb->dev->dev, "%s - bad wength %d\n", __func__, uwb->actuaw_wength);
		goto exit;
	}

	msg = (stwuct keyspan_usa28_powtStatusMessage *)data;

	/* Check powt numbew fwom message and wetwieve pwivate data */
	if (msg->powt >= sewiaw->num_powts) {
		dev_dbg(&uwb->dev->dev, "%s - Unexpected powt numbew %d\n", __func__, msg->powt);
		goto exit;
	}
	powt = sewiaw->powt[msg->powt];
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!p_pwiv)
		goto wesubmit;

	/* Update handshaking pin state infowmation */
	owd_dcd_state = p_pwiv->dcd_state;
	p_pwiv->cts_state = ((msg->cts) ? 1 : 0);
	p_pwiv->dsw_state = ((msg->dsw) ? 1 : 0);
	p_pwiv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_pwiv->wi_state = ((msg->wi) ? 1 : 0);

	if (owd_dcd_state != p_pwiv->dcd_state && owd_dcd_state)
		tty_powt_tty_hangup(&powt->powt, twue);
wesubmit:
		/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
exit: ;
}

static void	usa28_gwocont_cawwback(stwuct uwb *uwb)
{
}


static void	usa49_gwocont_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;
	stwuct keyspan_powt_pwivate *p_pwiv;
	int i;

	sewiaw =  uwb->context;
	fow (i = 0; i < sewiaw->num_powts; ++i) {
		powt = sewiaw->powt[i];
		p_pwiv = usb_get_sewiaw_powt_data(powt);
		if (!p_pwiv)
			continue;

		if (p_pwiv->wesend_cont) {
			dev_dbg(&powt->dev, "%s - sending setup\n", __func__);
			keyspan_usa49_send_setup(sewiaw, powt,
						p_pwiv->wesend_cont - 1);
			bweak;
		}
	}
}

	/* This is actuawwy cawwed gwostat in the Keyspan
	   doco */
static void	usa49_instat_cawwback(stwuct uwb *uwb)
{
	int					eww;
	unsigned chaw 				*data = uwb->twansfew_buffew;
	stwuct keyspan_usa49_powtStatusMessage	*msg;
	stwuct usb_sewiaw			*sewiaw;
	stwuct usb_sewiaw_powt			*powt;
	stwuct keyspan_powt_pwivate	 	*p_pwiv;
	int owd_dcd_state;
	int status = uwb->status;

	sewiaw =  uwb->context;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status: %d\n",
				__func__, status);
		wetuwn;
	}

	if (uwb->actuaw_wength !=
			sizeof(stwuct keyspan_usa49_powtStatusMessage)) {
		dev_dbg(&uwb->dev->dev, "%s - bad wength %d\n", __func__, uwb->actuaw_wength);
		goto exit;
	}

	msg = (stwuct keyspan_usa49_powtStatusMessage *)data;

	/* Check powt numbew fwom message and wetwieve pwivate data */
	if (msg->powtNumbew >= sewiaw->num_powts) {
		dev_dbg(&uwb->dev->dev, "%s - Unexpected powt numbew %d\n",
			__func__, msg->powtNumbew);
		goto exit;
	}
	powt = sewiaw->powt[msg->powtNumbew];
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!p_pwiv)
		goto wesubmit;

	/* Update handshaking pin state infowmation */
	owd_dcd_state = p_pwiv->dcd_state;
	p_pwiv->cts_state = ((msg->cts) ? 1 : 0);
	p_pwiv->dsw_state = ((msg->dsw) ? 1 : 0);
	p_pwiv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_pwiv->wi_state = ((msg->wi) ? 1 : 0);

	if (owd_dcd_state != p_pwiv->dcd_state && owd_dcd_state)
		tty_powt_tty_hangup(&powt->powt, twue);
wesubmit:
	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
exit:	;
}

static void	usa49_inack_cawwback(stwuct uwb *uwb)
{
}

static void	usa49_indat_cawwback(stwuct uwb *uwb)
{
	int			i, eww;
	int			endpoint;
	stwuct usb_sewiaw_powt	*powt;
	unsigned chaw 		*data = uwb->twansfew_buffew;
	int status = uwb->status;

	endpoint = usb_pipeendpoint(uwb->pipe);

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status %d on endpoint %x\n",
			__func__, status, endpoint);
		wetuwn;
	}

	powt =  uwb->context;
	if (uwb->actuaw_wength) {
		/* 0x80 bit is ewwow fwag */
		if ((data[0] & 0x80) == 0) {
			/* no ewwow on any byte */
			tty_insewt_fwip_stwing(&powt->powt, data + 1,
						uwb->actuaw_wength - 1);
		} ewse {
			/* some bytes had ewwows, evewy byte has status */
			fow (i = 0; i + 1 < uwb->actuaw_wength; i += 2) {
				int stat = data[i];
				int fwag = TTY_NOWMAW;

				if (stat & WXEWWOW_OVEWWUN) {
					tty_insewt_fwip_chaw(&powt->powt, 0,
								TTY_OVEWWUN);
				}
				/* XXX shouwd handwe bweak (0x10) */
				if (stat & WXEWWOW_PAWITY)
					fwag = TTY_PAWITY;
				ewse if (stat & WXEWWOW_FWAMING)
					fwag = TTY_FWAME;

				tty_insewt_fwip_chaw(&powt->powt, data[i+1],
						fwag);
			}
		}
		tty_fwip_buffew_push(&powt->powt);
	}

	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
}

static void usa49wg_indat_cawwback(stwuct uwb *uwb)
{
	int			i, wen, x, eww;
	stwuct usb_sewiaw	*sewiaw;
	stwuct usb_sewiaw_powt	*powt;
	unsigned chaw 		*data = uwb->twansfew_buffew;
	int status = uwb->status;

	sewiaw = uwb->context;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status: %d\n",
				__func__, status);
		wetuwn;
	}

	/* inbound data is in the fowm P#, wen, status, data */
	i = 0;
	wen = 0;

	whiwe (i < uwb->actuaw_wength) {

		/* Check powt numbew fwom message */
		if (data[i] >= sewiaw->num_powts) {
			dev_dbg(&uwb->dev->dev, "%s - Unexpected powt numbew %d\n",
				__func__, data[i]);
			wetuwn;
		}
		powt = sewiaw->powt[data[i++]];
		wen = data[i++];

		/* 0x80 bit is ewwow fwag */
		if ((data[i] & 0x80) == 0) {
			/* no ewwow on any byte */
			i++;
			fow (x = 1; x < wen && i < uwb->actuaw_wength; ++x)
				tty_insewt_fwip_chaw(&powt->powt,
						data[i++], 0);
		} ewse {
			/*
			 * some bytes had ewwows, evewy byte has status
			 */
			fow (x = 0; x + 1 < wen &&
				    i + 1 < uwb->actuaw_wength; x += 2) {
				int stat = data[i];
				int fwag = TTY_NOWMAW;

				if (stat & WXEWWOW_OVEWWUN) {
					tty_insewt_fwip_chaw(&powt->powt, 0,
								TTY_OVEWWUN);
				}
				/* XXX shouwd handwe bweak (0x10) */
				if (stat & WXEWWOW_PAWITY)
					fwag = TTY_PAWITY;
				ewse if (stat & WXEWWOW_FWAMING)
					fwag = TTY_FWAME;

				tty_insewt_fwip_chaw(&powt->powt, data[i+1],
						     fwag);
				i += 2;
			}
		}
		tty_fwip_buffew_push(&powt->powt);
	}

	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&uwb->dev->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
}

/* not used, usa-49 doesn't have pew-powt contwow endpoints */
static void usa49_outcont_cawwback(stwuct uwb *uwb)
{
}

static void usa90_indat_cawwback(stwuct uwb *uwb)
{
	int			i, eww;
	int			endpoint;
	stwuct usb_sewiaw_powt	*powt;
	stwuct keyspan_powt_pwivate	 	*p_pwiv;
	unsigned chaw 		*data = uwb->twansfew_buffew;
	int status = uwb->status;

	endpoint = usb_pipeendpoint(uwb->pipe);

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status %d on endpoint %x\n",
			__func__, status, endpoint);
		wetuwn;
	}

	powt =  uwb->context;
	p_pwiv = usb_get_sewiaw_powt_data(powt);

	if (uwb->actuaw_wength) {
		/* if cuwwent mode is DMA, wooks wike usa28 fowmat
		   othewwise wooks wike usa26 data fowmat */

		if (p_pwiv->baud > 57600)
			tty_insewt_fwip_stwing(&powt->powt, data,
					uwb->actuaw_wength);
		ewse {
			/* 0x80 bit is ewwow fwag */
			if ((data[0] & 0x80) == 0) {
				/* no ewwows on individuaw bytes, onwy
				   possibwe ovewwun eww*/
				if (data[0] & WXEWWOW_OVEWWUN) {
					tty_insewt_fwip_chaw(&powt->powt, 0,
								TTY_OVEWWUN);
				}
				fow (i = 1; i < uwb->actuaw_wength ; ++i)
					tty_insewt_fwip_chaw(&powt->powt,
							data[i], TTY_NOWMAW);
			}  ewse {
			/* some bytes had ewwows, evewy byte has status */
				dev_dbg(&powt->dev, "%s - WX ewwow!!!!\n", __func__);
				fow (i = 0; i + 1 < uwb->actuaw_wength; i += 2) {
					int stat = data[i];
					int fwag = TTY_NOWMAW;

					if (stat & WXEWWOW_OVEWWUN) {
						tty_insewt_fwip_chaw(
								&powt->powt, 0,
								TTY_OVEWWUN);
					}
					/* XXX shouwd handwe bweak (0x10) */
					if (stat & WXEWWOW_PAWITY)
						fwag = TTY_PAWITY;
					ewse if (stat & WXEWWOW_FWAMING)
						fwag = TTY_FWAME;

					tty_insewt_fwip_chaw(&powt->powt,
							data[i+1], fwag);
				}
			}
		}
		tty_fwip_buffew_push(&powt->powt);
	}

	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
}


static void	usa90_instat_cawwback(stwuct uwb *uwb)
{
	unsigned chaw 				*data = uwb->twansfew_buffew;
	stwuct keyspan_usa90_powtStatusMessage	*msg;
	stwuct usb_sewiaw			*sewiaw;
	stwuct usb_sewiaw_powt			*powt;
	stwuct keyspan_powt_pwivate	 	*p_pwiv;
	int owd_dcd_state, eww;
	int status = uwb->status;

	sewiaw =  uwb->context;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status: %d\n",
				__func__, status);
		wetuwn;
	}
	if (uwb->actuaw_wength < 14) {
		dev_dbg(&uwb->dev->dev, "%s - %d byte wepowt??\n", __func__, uwb->actuaw_wength);
		goto exit;
	}

	msg = (stwuct keyspan_usa90_powtStatusMessage *)data;

	/* Now do something usefuw with the data */

	powt = sewiaw->powt[0];
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!p_pwiv)
		goto wesubmit;

	/* Update handshaking pin state infowmation */
	owd_dcd_state = p_pwiv->dcd_state;
	p_pwiv->cts_state = ((msg->cts) ? 1 : 0);
	p_pwiv->dsw_state = ((msg->dsw) ? 1 : 0);
	p_pwiv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_pwiv->wi_state = ((msg->wi) ? 1 : 0);

	if (owd_dcd_state != p_pwiv->dcd_state && owd_dcd_state)
		tty_powt_tty_hangup(&powt->powt, twue);
wesubmit:
	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
exit:
	;
}

static void	usa90_outcont_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct keyspan_powt_pwivate *p_pwiv;

	powt =  uwb->context;
	p_pwiv = usb_get_sewiaw_powt_data(powt);

	if (p_pwiv->wesend_cont) {
		dev_dbg(&uwb->dev->dev, "%s - sending setup\n", __func__);
		keyspan_usa90_send_setup(powt->sewiaw, powt,
						p_pwiv->wesend_cont - 1);
	}
}

/* Status messages fwom the 28xg */
static void	usa67_instat_cawwback(stwuct uwb *uwb)
{
	int					eww;
	unsigned chaw 				*data = uwb->twansfew_buffew;
	stwuct keyspan_usa67_powtStatusMessage	*msg;
	stwuct usb_sewiaw			*sewiaw;
	stwuct usb_sewiaw_powt			*powt;
	stwuct keyspan_powt_pwivate	 	*p_pwiv;
	int owd_dcd_state;
	int status = uwb->status;

	sewiaw = uwb->context;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo status: %d\n",
				__func__, status);
		wetuwn;
	}

	if (uwb->actuaw_wength !=
			sizeof(stwuct keyspan_usa67_powtStatusMessage)) {
		dev_dbg(&uwb->dev->dev, "%s - bad wength %d\n", __func__, uwb->actuaw_wength);
		wetuwn;
	}


	/* Now do something usefuw with the data */
	msg = (stwuct keyspan_usa67_powtStatusMessage *)data;

	/* Check powt numbew fwom message and wetwieve pwivate data */
	if (msg->powt >= sewiaw->num_powts) {
		dev_dbg(&uwb->dev->dev, "%s - Unexpected powt numbew %d\n", __func__, msg->powt);
		wetuwn;
	}

	powt = sewiaw->powt[msg->powt];
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!p_pwiv)
		goto wesubmit;

	/* Update handshaking pin state infowmation */
	owd_dcd_state = p_pwiv->dcd_state;
	p_pwiv->cts_state = ((msg->hskia_cts) ? 1 : 0);
	p_pwiv->dcd_state = ((msg->gpia_dcd) ? 1 : 0);

	if (owd_dcd_state != p_pwiv->dcd_state && owd_dcd_state)
		tty_powt_tty_hangup(&powt->powt, twue);
wesubmit:
	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - wesubmit wead uwb faiwed. (%d)\n", __func__, eww);
}

static void usa67_gwocont_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;
	stwuct keyspan_powt_pwivate *p_pwiv;
	int i;

	sewiaw = uwb->context;
	fow (i = 0; i < sewiaw->num_powts; ++i) {
		powt = sewiaw->powt[i];
		p_pwiv = usb_get_sewiaw_powt_data(powt);
		if (!p_pwiv)
			continue;

		if (p_pwiv->wesend_cont) {
			dev_dbg(&powt->dev, "%s - sending setup\n", __func__);
			keyspan_usa67_send_setup(sewiaw, powt,
						p_pwiv->wesend_cont - 1);
			bweak;
		}
	}
}

static unsigned int keyspan_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct keyspan_powt_pwivate	*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	int				fwip;
	unsigned int			data_wen;
	stwuct uwb			*this_uwb;

	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = p_pwiv->device_detaiws;

	/* FIXME: wocking */
	if (d_detaiws->msg_fowmat == msg_usa90)
		data_wen = 64;
	ewse
		data_wen = 63;

	fwip = p_pwiv->out_fwip;

	/* Check both endpoints to see if any awe avaiwabwe. */
	this_uwb = p_pwiv->out_uwbs[fwip];
	if (this_uwb != NUWW) {
		if (this_uwb->status != -EINPWOGWESS)
			wetuwn data_wen;
		fwip = (fwip + 1) & d_detaiws->outdat_endp_fwip;
		this_uwb = p_pwiv->out_uwbs[fwip];
		if (this_uwb != NUWW) {
			if (this_uwb->status != -EINPWOGWESS)
				wetuwn data_wen;
		}
	}
	wetuwn 0;
}


static int keyspan_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct keyspan_powt_pwivate 	*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	int				i, eww;
	int				baud_wate, device_powt;
	stwuct uwb			*uwb;
	unsigned int			cfwag = 0;

	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = p_pwiv->device_detaiws;

	/* Set some sane defauwts */
	p_pwiv->wts_state = 1;
	p_pwiv->dtw_state = 1;
	p_pwiv->baud = 9600;

	/* fowce baud and wcw to be set on open */
	p_pwiv->owd_baud = 0;
	p_pwiv->owd_cfwag = 0;

	p_pwiv->out_fwip = 0;
	p_pwiv->in_fwip = 0;

	/* Weset wow wevew data toggwe and stawt weading fwom endpoints */
	fow (i = 0; i < 2; i++) {
		uwb = p_pwiv->in_uwbs[i];
		if (uwb == NUWW)
			continue;

		/* make suwe endpoint data toggwe is synchwonized
		   with the device */
		usb_cweaw_hawt(uwb->dev, uwb->pipe);
		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww != 0)
			dev_dbg(&powt->dev, "%s - submit uwb %d faiwed (%d)\n", __func__, i, eww);
	}

	/* Weset wow wevew data toggwe on out endpoints */
	fow (i = 0; i < 2; i++) {
		uwb = p_pwiv->out_uwbs[i];
		if (uwb == NUWW)
			continue;
		/* usb_settoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
						usb_pipeout(uwb->pipe), 0); */
	}

	/* get the tewminaw config fow the setup message now so we don't
	 * need to send 2 of them */

	device_powt = powt->powt_numbew;
	if (tty) {
		cfwag = tty->tewmios.c_cfwag;
		/* Baud wate cawcuwation takes baud wate as an integew
		   so othew wates can be genewated if desiwed. */
		baud_wate = tty_get_baud_wate(tty);
		/* If no match ow invawid, weave as defauwt */
		if (baud_wate >= 0
		    && d_detaiws->cawcuwate_baud_wate(powt, baud_wate, d_detaiws->baudcwk,
					NUWW, NUWW, NUWW, device_powt) == KEYSPAN_BAUD_WATE_OK) {
			p_pwiv->baud = baud_wate;
		}
	}
	/* set CTS/WTS handshake etc. */
	p_pwiv->cfwag = cfwag;
	p_pwiv->fwow_contwow = (cfwag & CWTSCTS) ? fwow_cts : fwow_none;

	keyspan_send_setup(powt, 1);
	/* mdeway(100); */
	/* keyspan_set_tewmios(powt, NUWW); */

	wetuwn 0;
}

static void keyspan_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct keyspan_powt_pwivate *p_pwiv = usb_get_sewiaw_powt_data(powt);

	p_pwiv->wts_state = on;
	p_pwiv->dtw_state = on;
	keyspan_send_setup(powt, 0);
}

static void keyspan_cwose(stwuct usb_sewiaw_powt *powt)
{
	int			i;
	stwuct keyspan_powt_pwivate 	*p_pwiv;

	p_pwiv = usb_get_sewiaw_powt_data(powt);

	p_pwiv->wts_state = 0;
	p_pwiv->dtw_state = 0;

	keyspan_send_setup(powt, 2);
	/* piwot-xfew seems to wowk best with this deway */
	mdeway(100);

	p_pwiv->out_fwip = 0;
	p_pwiv->in_fwip = 0;

	usb_kiww_uwb(p_pwiv->inack_uwb);
	fow (i = 0; i < 2; i++) {
		usb_kiww_uwb(p_pwiv->in_uwbs[i]);
		usb_kiww_uwb(p_pwiv->out_uwbs[i]);
	}
}

/* downwoad the fiwmwawe to a pwe-wenumewation device */
static int keyspan_fake_stawtup(stwuct usb_sewiaw *sewiaw)
{
	chaw	*fw_name;

	dev_dbg(&sewiaw->dev->dev, "Keyspan stawtup vewsion %04x pwoduct %04x\n",
		we16_to_cpu(sewiaw->dev->descwiptow.bcdDevice),
		we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct));

	if ((we16_to_cpu(sewiaw->dev->descwiptow.bcdDevice) & 0x8000)
								!= 0x8000) {
		dev_dbg(&sewiaw->dev->dev, "Fiwmwawe awweady woaded.  Quitting.\n");
		wetuwn 1;
	}

		/* Sewect fiwmwawe image on the basis of idPwoduct */
	switch (we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct)) {
	case keyspan_usa28_pwe_pwoduct_id:
		fw_name = "keyspan/usa28.fw";
		bweak;

	case keyspan_usa28x_pwe_pwoduct_id:
		fw_name = "keyspan/usa28x.fw";
		bweak;

	case keyspan_usa28xa_pwe_pwoduct_id:
		fw_name = "keyspan/usa28xa.fw";
		bweak;

	case keyspan_usa28xb_pwe_pwoduct_id:
		fw_name = "keyspan/usa28xb.fw";
		bweak;

	case keyspan_usa19_pwe_pwoduct_id:
		fw_name = "keyspan/usa19.fw";
		bweak;

	case keyspan_usa19qi_pwe_pwoduct_id:
		fw_name = "keyspan/usa19qi.fw";
		bweak;

	case keyspan_mpw_pwe_pwoduct_id:
		fw_name = "keyspan/mpw.fw";
		bweak;

	case keyspan_usa19qw_pwe_pwoduct_id:
		fw_name = "keyspan/usa19qw.fw";
		bweak;

	case keyspan_usa18x_pwe_pwoduct_id:
		fw_name = "keyspan/usa18x.fw";
		bweak;

	case keyspan_usa19w_pwe_pwoduct_id:
		fw_name = "keyspan/usa19w.fw";
		bweak;

	case keyspan_usa49w_pwe_pwoduct_id:
		fw_name = "keyspan/usa49w.fw";
		bweak;

	case keyspan_usa49wwc_pwe_pwoduct_id:
		fw_name = "keyspan/usa49wwc.fw";
		bweak;

	defauwt:
		dev_eww(&sewiaw->dev->dev, "Unknown pwoduct ID (%04x)\n",
			we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct));
		wetuwn 1;
	}

	dev_dbg(&sewiaw->dev->dev, "Upwoading Keyspan %s fiwmwawe.\n", fw_name);

	if (ezusb_fx1_ihex_fiwmwawe_downwoad(sewiaw->dev, fw_name) < 0) {
		dev_eww(&sewiaw->dev->dev, "faiwed to woad fiwmwawe \"%s\"\n",
			fw_name);
		wetuwn -ENOENT;
	}

	/* aftew downwoading fiwmwawe Wenumewation wiww occuw in a
	  moment and the new device wiww bind to the weaw dwivew */

	/* we don't want this device to have a dwivew assigned to it. */
	wetuwn 1;
}

/* Hewpew functions used by keyspan_setup_uwbs */
static stwuct usb_endpoint_descwiptow const *find_ep(stwuct usb_sewiaw const *sewiaw,
						     int endpoint)
{
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *ep;
	int i;

	iface_desc = sewiaw->intewface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		ep = &iface_desc->endpoint[i].desc;
		if (ep->bEndpointAddwess == endpoint)
			wetuwn ep;
	}
	dev_wawn(&sewiaw->intewface->dev, "found no endpoint descwiptow fow endpoint %x\n",
			endpoint);
	wetuwn NUWW;
}

static stwuct uwb *keyspan_setup_uwb(stwuct usb_sewiaw *sewiaw, int endpoint,
				      int diw, void *ctx, chaw *buf, int wen,
				      void (*cawwback)(stwuct uwb *))
{
	stwuct uwb *uwb;
	stwuct usb_endpoint_descwiptow const *ep_desc;
	chaw const *ep_type_name;

	if (endpoint == -1)
		wetuwn NUWW;		/* endpoint not needed */

	dev_dbg(&sewiaw->intewface->dev, "%s - awwoc fow endpoint %x\n",
			__func__, endpoint);
	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);		/* No ISO */
	if (!uwb)
		wetuwn NUWW;

	if (endpoint == 0) {
		/* contwow EP fiwwed in when used */
		wetuwn uwb;
	}

	ep_desc = find_ep(sewiaw, endpoint);
	if (!ep_desc) {
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}
	if (usb_endpoint_xfew_int(ep_desc)) {
		ep_type_name = "INT";
		usb_fiww_int_uwb(uwb, sewiaw->dev,
				 usb_sndintpipe(sewiaw->dev, endpoint) | diw,
				 buf, wen, cawwback, ctx,
				 ep_desc->bIntewvaw);
	} ewse if (usb_endpoint_xfew_buwk(ep_desc)) {
		ep_type_name = "BUWK";
		usb_fiww_buwk_uwb(uwb, sewiaw->dev,
				  usb_sndbuwkpipe(sewiaw->dev, endpoint) | diw,
				  buf, wen, cawwback, ctx);
	} ewse {
		dev_wawn(&sewiaw->intewface->dev,
			 "unsuppowted endpoint type %x\n",
			 usb_endpoint_type(ep_desc));
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	dev_dbg(&sewiaw->intewface->dev, "%s - using uwb %p fow %s endpoint %x\n",
	    __func__, uwb, ep_type_name, endpoint);
	wetuwn uwb;
}

static stwuct cawwbacks {
	void	(*instat_cawwback)(stwuct uwb *);
	void	(*gwocont_cawwback)(stwuct uwb *);
	void	(*indat_cawwback)(stwuct uwb *);
	void	(*outdat_cawwback)(stwuct uwb *);
	void	(*inack_cawwback)(stwuct uwb *);
	void	(*outcont_cawwback)(stwuct uwb *);
} keyspan_cawwbacks[] = {
	{
		/* msg_usa26 cawwbacks */
		.instat_cawwback =	usa26_instat_cawwback,
		.gwocont_cawwback =	usa26_gwocont_cawwback,
		.indat_cawwback =	usa26_indat_cawwback,
		.outdat_cawwback =	usa2x_outdat_cawwback,
		.inack_cawwback =	usa26_inack_cawwback,
		.outcont_cawwback =	usa26_outcont_cawwback,
	}, {
		/* msg_usa28 cawwbacks */
		.instat_cawwback =	usa28_instat_cawwback,
		.gwocont_cawwback =	usa28_gwocont_cawwback,
		.indat_cawwback =	usa28_indat_cawwback,
		.outdat_cawwback =	usa2x_outdat_cawwback,
		.inack_cawwback =	usa28_inack_cawwback,
		.outcont_cawwback =	usa28_outcont_cawwback,
	}, {
		/* msg_usa49 cawwbacks */
		.instat_cawwback =	usa49_instat_cawwback,
		.gwocont_cawwback =	usa49_gwocont_cawwback,
		.indat_cawwback =	usa49_indat_cawwback,
		.outdat_cawwback =	usa2x_outdat_cawwback,
		.inack_cawwback =	usa49_inack_cawwback,
		.outcont_cawwback =	usa49_outcont_cawwback,
	}, {
		/* msg_usa90 cawwbacks */
		.instat_cawwback =	usa90_instat_cawwback,
		.gwocont_cawwback =	usa28_gwocont_cawwback,
		.indat_cawwback =	usa90_indat_cawwback,
		.outdat_cawwback =	usa2x_outdat_cawwback,
		.inack_cawwback =	usa28_inack_cawwback,
		.outcont_cawwback =	usa90_outcont_cawwback,
	}, {
		/* msg_usa67 cawwbacks */
		.instat_cawwback =	usa67_instat_cawwback,
		.gwocont_cawwback =	usa67_gwocont_cawwback,
		.indat_cawwback =	usa26_indat_cawwback,
		.outdat_cawwback =	usa2x_outdat_cawwback,
		.inack_cawwback =	usa26_inack_cawwback,
		.outcont_cawwback =	usa26_outcont_cawwback,
	}
};

	/* Genewic setup uwbs function that uses
	   data in device_detaiws */
static void keyspan_setup_uwbs(stwuct usb_sewiaw *sewiaw)
{
	stwuct keyspan_sewiaw_pwivate 	*s_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	stwuct cawwbacks		*cback;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	d_detaiws = s_pwiv->device_detaiws;

	/* Setup vawues fow the vawious cawwback woutines */
	cback = &keyspan_cawwbacks[d_detaiws->msg_fowmat];

	/* Awwocate and set up uwbs fow each one that is in use,
	   stawting with instat endpoints */
	s_pwiv->instat_uwb = keyspan_setup_uwb
		(sewiaw, d_detaiws->instat_endpoint, USB_DIW_IN,
		 sewiaw, s_pwiv->instat_buf, INSTAT_BUFWEN,
		 cback->instat_cawwback);

	s_pwiv->indat_uwb = keyspan_setup_uwb
		(sewiaw, d_detaiws->indat_endpoint, USB_DIW_IN,
		 sewiaw, s_pwiv->indat_buf, INDAT49W_BUFWEN,
		 usa49wg_indat_cawwback);

	s_pwiv->gwocont_uwb = keyspan_setup_uwb
		(sewiaw, d_detaiws->gwocont_endpoint, USB_DIW_OUT,
		 sewiaw, s_pwiv->gwocont_buf, GWOCONT_BUFWEN,
		 cback->gwocont_cawwback);
}

/* usa19 function doesn't wequiwe pwescawew */
static int keyspan_usa19_cawc_baud(stwuct usb_sewiaw_powt *powt,
				   u32 baud_wate, u32 baudcwk, u8 *wate_hi,
				   u8 *wate_wow, u8 *pwescawew, int powtnum)
{
	u32 	b16,	/* baud wate times 16 (actuaw wate used intewnawwy) */
		div,	/* divisow */
		cnt;	/* invewse of divisow (pwogwammed into 8051) */

	dev_dbg(&powt->dev, "%s - %d.\n", __func__, baud_wate);

	/* pwevent divide by zewo...  */
	b16 = baud_wate * 16W;
	if (b16 == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;
	/* Any "standawd" wate ovew 57k6 is mawginaw on the USA-19
	   as we wun out of divisow wesowution. */
	if (baud_wate > 57600)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	/* cawcuwate the divisow and the countew (its invewse) */
	div = baudcwk / b16;
	if (div == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;
	ewse
		cnt = 0 - div;

	if (div > 0xffff)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	/* wetuwn the countew vawues if non-nuww */
	if (wate_wow)
		*wate_wow = (u8) (cnt & 0xff);
	if (wate_hi)
		*wate_hi = (u8) ((cnt >> 8) & 0xff);
	if (wate_wow && wate_hi)
		dev_dbg(&powt->dev, "%s - %d %02x %02x.\n",
				__func__, baud_wate, *wate_hi, *wate_wow);
	wetuwn KEYSPAN_BAUD_WATE_OK;
}

/* usa19hs function doesn't wequiwe pwescawew */
static int keyspan_usa19hs_cawc_baud(stwuct usb_sewiaw_powt *powt,
				     u32 baud_wate, u32 baudcwk, u8 *wate_hi,
				     u8 *wate_wow, u8 *pwescawew, int powtnum)
{
	u32 	b16,	/* baud wate times 16 (actuaw wate used intewnawwy) */
			div;	/* divisow */

	dev_dbg(&powt->dev, "%s - %d.\n", __func__, baud_wate);

	/* pwevent divide by zewo...  */
	b16 = baud_wate * 16W;
	if (b16 == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	/* cawcuwate the divisow */
	div = baudcwk / b16;
	if (div == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	if (div > 0xffff)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	/* wetuwn the countew vawues if non-nuww */
	if (wate_wow)
		*wate_wow = (u8) (div & 0xff);

	if (wate_hi)
		*wate_hi = (u8) ((div >> 8) & 0xff);

	if (wate_wow && wate_hi)
		dev_dbg(&powt->dev, "%s - %d %02x %02x.\n",
			__func__, baud_wate, *wate_hi, *wate_wow);

	wetuwn KEYSPAN_BAUD_WATE_OK;
}

static int keyspan_usa19w_cawc_baud(stwuct usb_sewiaw_powt *powt,
				    u32 baud_wate, u32 baudcwk, u8 *wate_hi,
				    u8 *wate_wow, u8 *pwescawew, int powtnum)
{
	u32 	b16,	/* baud wate times 16 (actuaw wate used intewnawwy) */
		cwk,	/* cwock with 13/8 pwescawew */
		div,	/* divisow using 13/8 pwescawew */
		wes,	/* wesuwting baud wate using 13/8 pwescawew */
		diff,	/* ewwow using 13/8 pwescawew */
		smawwest_diff;
	u8	best_pwescawew;
	int	i;

	dev_dbg(&powt->dev, "%s - %d.\n", __func__, baud_wate);

	/* pwevent divide by zewo */
	b16 = baud_wate * 16W;
	if (b16 == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	/* Cawcuwate pwescawew by twying them aww and wooking
	   fow best fit */

	/* stawt with wawgest possibwe diffewence */
	smawwest_diff = 0xffffffff;

		/* 0 is an invawid pwescawew, used as a fwag */
	best_pwescawew = 0;

	fow (i = 8; i <= 0xff; ++i) {
		cwk = (baudcwk * 8) / (u32) i;

		div = cwk / b16;
		if (div == 0)
			continue;

		wes = cwk / div;
		diff = (wes > b16) ? (wes-b16) : (b16-wes);

		if (diff < smawwest_diff) {
			best_pwescawew = i;
			smawwest_diff = diff;
		}
	}

	if (best_pwescawew == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	cwk = (baudcwk * 8) / (u32) best_pwescawew;
	div = cwk / b16;

	/* wetuwn the divisow and pwescawew if non-nuww */
	if (wate_wow)
		*wate_wow = (u8) (div & 0xff);
	if (wate_hi)
		*wate_hi = (u8) ((div >> 8) & 0xff);
	if (pwescawew) {
		*pwescawew = best_pwescawew;
		/*  dev_dbg(&powt->dev, "%s - %d %d\n", __func__, *pwescawew, div); */
	}
	wetuwn KEYSPAN_BAUD_WATE_OK;
}

	/* USA-28 suppowts diffewent maximum baud wates on each powt */
static int keyspan_usa28_cawc_baud(stwuct usb_sewiaw_powt *powt,
				   u32 baud_wate, u32 baudcwk, u8 *wate_hi,
				   u8 *wate_wow, u8 *pwescawew, int powtnum)
{
	u32 	b16,	/* baud wate times 16 (actuaw wate used intewnawwy) */
		div,	/* divisow */
		cnt;	/* invewse of divisow (pwogwammed into 8051) */

	dev_dbg(&powt->dev, "%s - %d.\n", __func__, baud_wate);

		/* pwevent divide by zewo */
	b16 = baud_wate * 16W;
	if (b16 == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;

	/* cawcuwate the divisow and the countew (its invewse) */
	div = KEYSPAN_USA28_BAUDCWK / b16;
	if (div == 0)
		wetuwn KEYSPAN_INVAWID_BAUD_WATE;
	ewse
		cnt = 0 - div;

	/* check fow out of wange, based on powtnum,
	   and wetuwn wesuwt */
	if (powtnum == 0) {
		if (div > 0xffff)
			wetuwn KEYSPAN_INVAWID_BAUD_WATE;
	} ewse {
		if (powtnum == 1) {
			if (div > 0xff)
				wetuwn KEYSPAN_INVAWID_BAUD_WATE;
		} ewse
			wetuwn KEYSPAN_INVAWID_BAUD_WATE;
	}

		/* wetuwn the countew vawues if not NUWW
		   (powt 1 wiww ignowe wetHi) */
	if (wate_wow)
		*wate_wow = (u8) (cnt & 0xff);
	if (wate_hi)
		*wate_hi = (u8) ((cnt >> 8) & 0xff);
	dev_dbg(&powt->dev, "%s - %d OK.\n", __func__, baud_wate);
	wetuwn KEYSPAN_BAUD_WATE_OK;
}

static int keyspan_usa26_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt)
{
	stwuct keyspan_usa26_powtContwowMessage	msg;
	stwuct keyspan_sewiaw_pwivate 		*s_pwiv;
	stwuct keyspan_powt_pwivate 		*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	stwuct uwb				*this_uwb;
	int 					device_powt, eww;

	dev_dbg(&powt->dev, "%s weset=%d\n", __func__, weset_powt);

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = s_pwiv->device_detaiws;
	device_powt = powt->powt_numbew;

	this_uwb = p_pwiv->outcont_uwb;

		/* Make suwe we have an uwb then send the message */
	if (this_uwb == NUWW) {
		dev_dbg(&powt->dev, "%s - oops no uwb.\n", __func__);
		wetuwn -1;
	}

	dev_dbg(&powt->dev, "%s - endpoint %x\n",
			__func__, usb_pipeendpoint(this_uwb->pipe));

	/* Save weset powt vaw fow wesend.
	   Don't ovewwwite wesend fow open/cwose condition. */
	if ((weset_powt + 1) > p_pwiv->wesend_cont)
		p_pwiv->wesend_cont = weset_powt + 1;
	if (this_uwb->status == -EINPWOGWESS) {
		/*  dev_dbg(&powt->dev, "%s - awweady wwiting\n", __func__); */
		mdeway(5);
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(stwuct keyspan_usa26_powtContwowMessage));

	/* Onwy set baud wate if it's changed */
	if (p_pwiv->owd_baud != p_pwiv->baud) {
		p_pwiv->owd_baud = p_pwiv->baud;
		msg.setCwocking = 0xff;
		if (d_detaiws->cawcuwate_baud_wate(powt, p_pwiv->baud, d_detaiws->baudcwk,
						   &msg.baudHi, &msg.baudWo, &msg.pwescawew,
						   device_powt) == KEYSPAN_INVAWID_BAUD_WATE) {
			dev_dbg(&powt->dev, "%s - Invawid baud wate %d wequested, using 9600.\n",
				__func__, p_pwiv->baud);
			msg.baudWo = 0;
			msg.baudHi = 125;	/* Vawues fow 9600 baud */
			msg.pwescawew = 10;
		}
		msg.setPwescawew = 0xff;
	}

	msg.wcw = (p_pwiv->cfwag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	switch (p_pwiv->cfwag & CSIZE) {
	case CS5:
		msg.wcw |= USA_DATABITS_5;
		bweak;
	case CS6:
		msg.wcw |= USA_DATABITS_6;
		bweak;
	case CS7:
		msg.wcw |= USA_DATABITS_7;
		bweak;
	case CS8:
		msg.wcw |= USA_DATABITS_8;
		bweak;
	}
	if (p_pwiv->cfwag & PAWENB) {
		/* note USA_PAWITY_NONE == 0 */
		msg.wcw |= (p_pwiv->cfwag & PAWODD) ?
			USA_PAWITY_ODD : USA_PAWITY_EVEN;
	}
	msg.setWcw = 0xff;

	msg.ctsFwowContwow = (p_pwiv->fwow_contwow == fwow_cts);
	msg.xonFwowContwow = 0;
	msg.setFwowContwow = 0xff;
	msg.fowwawdingWength = 16;
	msg.xonChaw = 17;
	msg.xoffChaw = 19;

	/* Opening powt */
	if (weset_powt == 1) {
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txBweak = 0;
		msg.wxOn = 1;
		msg.wxOff = 0;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0xff;
	}

	/* Cwosing powt */
	ewse if (weset_powt == 2) {
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFwush = 0;
		msg.txBweak = 0;
		msg.wxOn = 0;
		msg.wxOff = 1;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0;
	}

	/* Sending intewmediate configs */
	ewse {
		msg._txOn = (!p_pwiv->bweak_on);
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txBweak = (p_pwiv->bweak_on);
		msg.wxOn = 0;
		msg.wxOff = 0;
		msg.wxFwush = 0;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0x0;
	}

	/* Do handshaking outputs */
	msg.setTxTwiState_setWts = 0xff;
	msg.txTwiState_wts = p_pwiv->wts_state;

	msg.setHskoa_setDtw = 0xff;
	msg.hskoa_dtw = p_pwiv->dtw_state;

	p_pwiv->wesend_cont = 0;
	memcpy(this_uwb->twansfew_buffew, &msg, sizeof(msg));

	/* send the data out the device on contwow endpoint */
	this_uwb->twansfew_buffew_wength = sizeof(msg);

	eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - usb_submit_uwb(setup) faiwed (%d)\n", __func__, eww);
	wetuwn 0;
}

static int keyspan_usa28_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt)
{
	stwuct keyspan_usa28_powtContwowMessage	msg;
	stwuct keyspan_sewiaw_pwivate	 	*s_pwiv;
	stwuct keyspan_powt_pwivate 		*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	stwuct uwb				*this_uwb;
	int 					device_powt, eww;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = s_pwiv->device_detaiws;
	device_powt = powt->powt_numbew;

	/* onwy do something if we have a buwk out endpoint */
	this_uwb = p_pwiv->outcont_uwb;
	if (this_uwb == NUWW) {
		dev_dbg(&powt->dev, "%s - oops no uwb.\n", __func__);
		wetuwn -1;
	}

	/* Save weset powt vaw fow wesend.
	   Don't ovewwwite wesend fow open/cwose condition. */
	if ((weset_powt + 1) > p_pwiv->wesend_cont)
		p_pwiv->wesend_cont = weset_powt + 1;
	if (this_uwb->status == -EINPWOGWESS) {
		dev_dbg(&powt->dev, "%s awweady wwiting\n", __func__);
		mdeway(5);
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(stwuct keyspan_usa28_powtContwowMessage));

	msg.setBaudWate = 1;
	if (d_detaiws->cawcuwate_baud_wate(powt, p_pwiv->baud, d_detaiws->baudcwk,
					   &msg.baudHi, &msg.baudWo, NUWW,
					   device_powt) == KEYSPAN_INVAWID_BAUD_WATE) {
		dev_dbg(&powt->dev, "%s - Invawid baud wate wequested %d.\n",
						__func__, p_pwiv->baud);
		msg.baudWo = 0xff;
		msg.baudHi = 0xb2;	/* Vawues fow 9600 baud */
	}

	/* If pawity is enabwed, we must cawcuwate it ouwsewves. */
	msg.pawity = 0;		/* XXX fow now */

	msg.ctsFwowContwow = (p_pwiv->fwow_contwow == fwow_cts);
	msg.xonFwowContwow = 0;

	/* Do handshaking outputs, DTW is invewted wewative to WTS */
	msg.wts = p_pwiv->wts_state;
	msg.dtw = p_pwiv->dtw_state;

	msg.fowwawdingWength = 16;
	msg.fowwawdMs = 10;
	msg.bweakThweshowd = 45;
	msg.xonChaw = 17;
	msg.xoffChaw = 19;

	/*msg.wetuwnStatus = 1;
	msg.wesetDataToggwe = 0xff;*/
	/* Opening powt */
	if (weset_powt == 1) {
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txFowceXoff = 0;
		msg.txBweak = 0;
		msg.wxOn = 1;
		msg.wxOff = 0;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0xff;
	}
	/* Cwosing powt */
	ewse if (weset_powt == 2) {
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFwush = 0;
		msg.txFowceXoff = 0;
		msg.txBweak = 0;
		msg.wxOn = 0;
		msg.wxOff = 1;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0;
	}
	/* Sending intewmediate configs */
	ewse {
		msg._txOn = (!p_pwiv->bweak_on);
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txFowceXoff = 0;
		msg.txBweak = (p_pwiv->bweak_on);
		msg.wxOn = 0;
		msg.wxOff = 0;
		msg.wxFwush = 0;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0x0;
	}

	p_pwiv->wesend_cont = 0;
	memcpy(this_uwb->twansfew_buffew, &msg, sizeof(msg));

	/* send the data out the device on contwow endpoint */
	this_uwb->twansfew_buffew_wength = sizeof(msg);

	eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - usb_submit_uwb(setup) faiwed\n", __func__);

	wetuwn 0;
}

static int keyspan_usa49_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt)
{
	stwuct keyspan_usa49_powtContwowMessage	msg;
	stwuct usb_ctwwwequest 			*dw = NUWW;
	stwuct keyspan_sewiaw_pwivate 		*s_pwiv;
	stwuct keyspan_powt_pwivate 		*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	stwuct uwb				*this_uwb;
	int 					eww, device_powt;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = s_pwiv->device_detaiws;

	this_uwb = s_pwiv->gwocont_uwb;

	/* Wowk out which powt within the device is being setup */
	device_powt = powt->powt_numbew;

	/* Make suwe we have an uwb then send the message */
	if (this_uwb == NUWW) {
		dev_dbg(&powt->dev, "%s - oops no uwb fow powt.\n", __func__);
		wetuwn -1;
	}

	dev_dbg(&powt->dev, "%s - endpoint %x (%d)\n",
		__func__, usb_pipeendpoint(this_uwb->pipe), device_powt);

	/* Save weset powt vaw fow wesend.
	   Don't ovewwwite wesend fow open/cwose condition. */
	if ((weset_powt + 1) > p_pwiv->wesend_cont)
		p_pwiv->wesend_cont = weset_powt + 1;

	if (this_uwb->status == -EINPWOGWESS) {
		/*  dev_dbg(&powt->dev, "%s - awweady wwiting\n", __func__); */
		mdeway(5);
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(stwuct keyspan_usa49_powtContwowMessage));

	msg.powtNumbew = device_powt;

	/* Onwy set baud wate if it's changed */
	if (p_pwiv->owd_baud != p_pwiv->baud) {
		p_pwiv->owd_baud = p_pwiv->baud;
		msg.setCwocking = 0xff;
		if (d_detaiws->cawcuwate_baud_wate(powt, p_pwiv->baud, d_detaiws->baudcwk,
						   &msg.baudHi, &msg.baudWo, &msg.pwescawew,
						   device_powt) == KEYSPAN_INVAWID_BAUD_WATE) {
			dev_dbg(&powt->dev, "%s - Invawid baud wate %d wequested, using 9600.\n",
				__func__, p_pwiv->baud);
			msg.baudWo = 0;
			msg.baudHi = 125;	/* Vawues fow 9600 baud */
			msg.pwescawew = 10;
		}
		/* msg.setPwescawew = 0xff; */
	}

	msg.wcw = (p_pwiv->cfwag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	switch (p_pwiv->cfwag & CSIZE) {
	case CS5:
		msg.wcw |= USA_DATABITS_5;
		bweak;
	case CS6:
		msg.wcw |= USA_DATABITS_6;
		bweak;
	case CS7:
		msg.wcw |= USA_DATABITS_7;
		bweak;
	case CS8:
		msg.wcw |= USA_DATABITS_8;
		bweak;
	}
	if (p_pwiv->cfwag & PAWENB) {
		/* note USA_PAWITY_NONE == 0 */
		msg.wcw |= (p_pwiv->cfwag & PAWODD) ?
			USA_PAWITY_ODD : USA_PAWITY_EVEN;
	}
	msg.setWcw = 0xff;

	msg.ctsFwowContwow = (p_pwiv->fwow_contwow == fwow_cts);
	msg.xonFwowContwow = 0;
	msg.setFwowContwow = 0xff;

	msg.fowwawdingWength = 16;
	msg.xonChaw = 17;
	msg.xoffChaw = 19;

	/* Opening powt */
	if (weset_powt == 1) {
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txBweak = 0;
		msg.wxOn = 1;
		msg.wxOff = 0;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0xff;
		msg.enabwePowt = 1;
		msg.disabwePowt = 0;
	}
	/* Cwosing powt */
	ewse if (weset_powt == 2) {
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFwush = 0;
		msg.txBweak = 0;
		msg.wxOn = 0;
		msg.wxOff = 1;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0;
		msg.enabwePowt = 0;
		msg.disabwePowt = 1;
	}
	/* Sending intewmediate configs */
	ewse {
		msg._txOn = (!p_pwiv->bweak_on);
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txBweak = (p_pwiv->bweak_on);
		msg.wxOn = 0;
		msg.wxOff = 0;
		msg.wxFwush = 0;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0x0;
		msg.enabwePowt = 0;
		msg.disabwePowt = 0;
	}

	/* Do handshaking outputs */
	msg.setWts = 0xff;
	msg.wts = p_pwiv->wts_state;

	msg.setDtw = 0xff;
	msg.dtw = p_pwiv->dtw_state;

	p_pwiv->wesend_cont = 0;

	/* if the device is a 49wg, we send contwow message on usb
	   contwow EP 0 */

	if (d_detaiws->pwoduct_id == keyspan_usa49wg_pwoduct_id) {
		dw = (void *)(s_pwiv->ctww_buf);
		dw->bWequestType = USB_TYPE_VENDOW | USB_DIW_OUT;
		dw->bWequest = 0xB0;	/* 49wg contwow message */
		dw->wVawue = 0;
		dw->wIndex = 0;
		dw->wWength = cpu_to_we16(sizeof(msg));

		memcpy(s_pwiv->gwocont_buf, &msg, sizeof(msg));

		usb_fiww_contwow_uwb(this_uwb, sewiaw->dev,
				usb_sndctwwpipe(sewiaw->dev, 0),
				(unsigned chaw *)dw, s_pwiv->gwocont_buf,
				sizeof(msg), usa49_gwocont_cawwback, sewiaw);

	} ewse {
		memcpy(this_uwb->twansfew_buffew, &msg, sizeof(msg));

		/* send the data out the device on contwow endpoint */
		this_uwb->twansfew_buffew_wength = sizeof(msg);
	}
	eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - usb_submit_uwb(setup) faiwed (%d)\n", __func__, eww);

	wetuwn 0;
}

static int keyspan_usa90_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt)
{
	stwuct keyspan_usa90_powtContwowMessage	msg;
	stwuct keyspan_sewiaw_pwivate 		*s_pwiv;
	stwuct keyspan_powt_pwivate 		*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	stwuct uwb				*this_uwb;
	int 					eww;
	u8						pwescawew;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = s_pwiv->device_detaiws;

	/* onwy do something if we have a buwk out endpoint */
	this_uwb = p_pwiv->outcont_uwb;
	if (this_uwb == NUWW) {
		dev_dbg(&powt->dev, "%s - oops no uwb.\n", __func__);
		wetuwn -1;
	}

	/* Save weset powt vaw fow wesend.
	   Don't ovewwwite wesend fow open/cwose condition. */
	if ((weset_powt + 1) > p_pwiv->wesend_cont)
		p_pwiv->wesend_cont = weset_powt + 1;
	if (this_uwb->status == -EINPWOGWESS) {
		dev_dbg(&powt->dev, "%s awweady wwiting\n", __func__);
		mdeway(5);
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(stwuct keyspan_usa90_powtContwowMessage));

	/* Onwy set baud wate if it's changed */
	if (p_pwiv->owd_baud != p_pwiv->baud) {
		p_pwiv->owd_baud = p_pwiv->baud;
		msg.setCwocking = 0x01;
		if (d_detaiws->cawcuwate_baud_wate(powt, p_pwiv->baud, d_detaiws->baudcwk,
						   &msg.baudHi, &msg.baudWo, &pwescawew, 0) == KEYSPAN_INVAWID_BAUD_WATE) {
			dev_dbg(&powt->dev, "%s - Invawid baud wate %d wequested, using 9600.\n",
				__func__, p_pwiv->baud);
			p_pwiv->baud = 9600;
			d_detaiws->cawcuwate_baud_wate(powt, p_pwiv->baud, d_detaiws->baudcwk,
				&msg.baudHi, &msg.baudWo, &pwescawew, 0);
		}
		msg.setWxMode = 1;
		msg.setTxMode = 1;
	}

	/* modes must awways be cowwectwy specified */
	if (p_pwiv->baud > 57600) {
		msg.wxMode = WXMODE_DMA;
		msg.txMode = TXMODE_DMA;
	} ewse {
		msg.wxMode = WXMODE_BYHAND;
		msg.txMode = TXMODE_BYHAND;
	}

	msg.wcw = (p_pwiv->cfwag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	switch (p_pwiv->cfwag & CSIZE) {
	case CS5:
		msg.wcw |= USA_DATABITS_5;
		bweak;
	case CS6:
		msg.wcw |= USA_DATABITS_6;
		bweak;
	case CS7:
		msg.wcw |= USA_DATABITS_7;
		bweak;
	case CS8:
		msg.wcw |= USA_DATABITS_8;
		bweak;
	}
	if (p_pwiv->cfwag & PAWENB) {
		/* note USA_PAWITY_NONE == 0 */
		msg.wcw |= (p_pwiv->cfwag & PAWODD) ?
			USA_PAWITY_ODD : USA_PAWITY_EVEN;
	}
	if (p_pwiv->owd_cfwag != p_pwiv->cfwag) {
		p_pwiv->owd_cfwag = p_pwiv->cfwag;
		msg.setWcw = 0x01;
	}

	if (p_pwiv->fwow_contwow == fwow_cts)
		msg.txFwowContwow = TXFWOW_CTS;
	msg.setTxFwowContwow = 0x01;
	msg.setWxFwowContwow = 0x01;

	msg.wxFowwawdingWength = 16;
	msg.wxFowwawdingTimeout = 16;
	msg.txAckSetting = 0;
	msg.xonChaw = 17;
	msg.xoffChaw = 19;

	/* Opening powt */
	if (weset_powt == 1) {
		msg.powtEnabwed = 1;
		msg.wxFwush = 1;
		msg.txBweak = (p_pwiv->bweak_on);
	}
	/* Cwosing powt */
	ewse if (weset_powt == 2)
		msg.powtEnabwed = 0;
	/* Sending intewmediate configs */
	ewse {
		msg.powtEnabwed = 1;
		msg.txBweak = (p_pwiv->bweak_on);
	}

	/* Do handshaking outputs */
	msg.setWts = 0x01;
	msg.wts = p_pwiv->wts_state;

	msg.setDtw = 0x01;
	msg.dtw = p_pwiv->dtw_state;

	p_pwiv->wesend_cont = 0;
	memcpy(this_uwb->twansfew_buffew, &msg, sizeof(msg));

	/* send the data out the device on contwow endpoint */
	this_uwb->twansfew_buffew_wength = sizeof(msg);

	eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - usb_submit_uwb(setup) faiwed (%d)\n", __func__, eww);
	wetuwn 0;
}

static int keyspan_usa67_send_setup(stwuct usb_sewiaw *sewiaw,
				    stwuct usb_sewiaw_powt *powt,
				    int weset_powt)
{
	stwuct keyspan_usa67_powtContwowMessage	msg;
	stwuct keyspan_sewiaw_pwivate 		*s_pwiv;
	stwuct keyspan_powt_pwivate 		*p_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;
	stwuct uwb				*this_uwb;
	int 					eww, device_powt;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	p_pwiv = usb_get_sewiaw_powt_data(powt);
	d_detaiws = s_pwiv->device_detaiws;

	this_uwb = s_pwiv->gwocont_uwb;

	/* Wowk out which powt within the device is being setup */
	device_powt = powt->powt_numbew;

	/* Make suwe we have an uwb then send the message */
	if (this_uwb == NUWW) {
		dev_dbg(&powt->dev, "%s - oops no uwb fow powt.\n", __func__);
		wetuwn -1;
	}

	/* Save weset powt vaw fow wesend.
	   Don't ovewwwite wesend fow open/cwose condition. */
	if ((weset_powt + 1) > p_pwiv->wesend_cont)
		p_pwiv->wesend_cont = weset_powt + 1;
	if (this_uwb->status == -EINPWOGWESS) {
		/*  dev_dbg(&powt->dev, "%s - awweady wwiting\n", __func__); */
		mdeway(5);
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(stwuct keyspan_usa67_powtContwowMessage));

	msg.powt = device_powt;

	/* Onwy set baud wate if it's changed */
	if (p_pwiv->owd_baud != p_pwiv->baud) {
		p_pwiv->owd_baud = p_pwiv->baud;
		msg.setCwocking = 0xff;
		if (d_detaiws->cawcuwate_baud_wate(powt, p_pwiv->baud, d_detaiws->baudcwk,
						   &msg.baudHi, &msg.baudWo, &msg.pwescawew,
						   device_powt) == KEYSPAN_INVAWID_BAUD_WATE) {
			dev_dbg(&powt->dev, "%s - Invawid baud wate %d wequested, using 9600.\n",
				__func__, p_pwiv->baud);
			msg.baudWo = 0;
			msg.baudHi = 125;	/* Vawues fow 9600 baud */
			msg.pwescawew = 10;
		}
		msg.setPwescawew = 0xff;
	}

	msg.wcw = (p_pwiv->cfwag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	switch (p_pwiv->cfwag & CSIZE) {
	case CS5:
		msg.wcw |= USA_DATABITS_5;
		bweak;
	case CS6:
		msg.wcw |= USA_DATABITS_6;
		bweak;
	case CS7:
		msg.wcw |= USA_DATABITS_7;
		bweak;
	case CS8:
		msg.wcw |= USA_DATABITS_8;
		bweak;
	}
	if (p_pwiv->cfwag & PAWENB) {
		/* note USA_PAWITY_NONE == 0 */
		msg.wcw |= (p_pwiv->cfwag & PAWODD) ?
					USA_PAWITY_ODD : USA_PAWITY_EVEN;
	}
	msg.setWcw = 0xff;

	msg.ctsFwowContwow = (p_pwiv->fwow_contwow == fwow_cts);
	msg.xonFwowContwow = 0;
	msg.setFwowContwow = 0xff;
	msg.fowwawdingWength = 16;
	msg.xonChaw = 17;
	msg.xoffChaw = 19;

	if (weset_powt == 1) {
		/* Opening powt */
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txBweak = 0;
		msg.wxOn = 1;
		msg.wxOff = 0;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0xff;
	} ewse if (weset_powt == 2) {
		/* Cwosing powt */
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFwush = 0;
		msg.txBweak = 0;
		msg.wxOn = 0;
		msg.wxOff = 1;
		msg.wxFwush = 1;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0;
	} ewse {
		/* Sending intewmediate configs */
		msg._txOn = (!p_pwiv->bweak_on);
		msg._txOff = 0;
		msg.txFwush = 0;
		msg.txBweak = (p_pwiv->bweak_on);
		msg.wxOn = 0;
		msg.wxOff = 0;
		msg.wxFwush = 0;
		msg.wxFowwawd = 0;
		msg.wetuwnStatus = 0;
		msg.wesetDataToggwe = 0x0;
	}

	/* Do handshaking outputs */
	msg.setTxTwiState_setWts = 0xff;
	msg.txTwiState_wts = p_pwiv->wts_state;

	msg.setHskoa_setDtw = 0xff;
	msg.hskoa_dtw = p_pwiv->dtw_state;

	p_pwiv->wesend_cont = 0;

	memcpy(this_uwb->twansfew_buffew, &msg, sizeof(msg));

	/* send the data out the device on contwow endpoint */
	this_uwb->twansfew_buffew_wength = sizeof(msg);

	eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
	if (eww != 0)
		dev_dbg(&powt->dev, "%s - usb_submit_uwb(setup) faiwed (%d)\n", __func__, eww);
	wetuwn 0;
}

static void keyspan_send_setup(stwuct usb_sewiaw_powt *powt, int weset_powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct keyspan_sewiaw_pwivate *s_pwiv;
	const stwuct keyspan_device_detaiws *d_detaiws;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	d_detaiws = s_pwiv->device_detaiws;

	switch (d_detaiws->msg_fowmat) {
	case msg_usa26:
		keyspan_usa26_send_setup(sewiaw, powt, weset_powt);
		bweak;
	case msg_usa28:
		keyspan_usa28_send_setup(sewiaw, powt, weset_powt);
		bweak;
	case msg_usa49:
		keyspan_usa49_send_setup(sewiaw, powt, weset_powt);
		bweak;
	case msg_usa90:
		keyspan_usa90_send_setup(sewiaw, powt, weset_powt);
		bweak;
	case msg_usa67:
		keyspan_usa67_send_setup(sewiaw, powt, weset_powt);
		bweak;
	}
}


/* Gets cawwed by the "weaw" dwivew (ie once fiwmwawe is woaded
   and wenumewation has taken pwace. */
static int keyspan_stawtup(stwuct usb_sewiaw *sewiaw)
{
	int				i, eww;
	stwuct keyspan_sewiaw_pwivate 	*s_pwiv;
	const stwuct keyspan_device_detaiws	*d_detaiws;

	fow (i = 0; (d_detaiws = keyspan_devices[i]) != NUWW; ++i)
		if (d_detaiws->pwoduct_id ==
				we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct))
			bweak;
	if (d_detaiws == NUWW) {
		dev_eww(&sewiaw->dev->dev, "%s - unknown pwoduct id %x\n",
		    __func__, we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct));
		wetuwn -ENODEV;
	}

	/* Setup pwivate data fow sewiaw dwivew */
	s_pwiv = kzawwoc(sizeof(stwuct keyspan_sewiaw_pwivate), GFP_KEWNEW);
	if (!s_pwiv)
		wetuwn -ENOMEM;

	s_pwiv->instat_buf = kzawwoc(INSTAT_BUFWEN, GFP_KEWNEW);
	if (!s_pwiv->instat_buf)
		goto eww_instat_buf;

	s_pwiv->indat_buf = kzawwoc(INDAT49W_BUFWEN, GFP_KEWNEW);
	if (!s_pwiv->indat_buf)
		goto eww_indat_buf;

	s_pwiv->gwocont_buf = kzawwoc(GWOCONT_BUFWEN, GFP_KEWNEW);
	if (!s_pwiv->gwocont_buf)
		goto eww_gwocont_buf;

	s_pwiv->ctww_buf = kzawwoc(sizeof(stwuct usb_ctwwwequest), GFP_KEWNEW);
	if (!s_pwiv->ctww_buf)
		goto eww_ctww_buf;

	s_pwiv->device_detaiws = d_detaiws;
	usb_set_sewiaw_data(sewiaw, s_pwiv);

	keyspan_setup_uwbs(sewiaw);

	if (s_pwiv->instat_uwb != NUWW) {
		eww = usb_submit_uwb(s_pwiv->instat_uwb, GFP_KEWNEW);
		if (eww != 0)
			dev_dbg(&sewiaw->dev->dev, "%s - submit instat uwb faiwed %d\n", __func__, eww);
	}
	if (s_pwiv->indat_uwb != NUWW) {
		eww = usb_submit_uwb(s_pwiv->indat_uwb, GFP_KEWNEW);
		if (eww != 0)
			dev_dbg(&sewiaw->dev->dev, "%s - submit indat uwb faiwed %d\n", __func__, eww);
	}

	wetuwn 0;

eww_ctww_buf:
	kfwee(s_pwiv->gwocont_buf);
eww_gwocont_buf:
	kfwee(s_pwiv->indat_buf);
eww_indat_buf:
	kfwee(s_pwiv->instat_buf);
eww_instat_buf:
	kfwee(s_pwiv);

	wetuwn -ENOMEM;
}

static void keyspan_disconnect(stwuct usb_sewiaw *sewiaw)
{
	stwuct keyspan_sewiaw_pwivate *s_pwiv;

	s_pwiv = usb_get_sewiaw_data(sewiaw);

	usb_kiww_uwb(s_pwiv->instat_uwb);
	usb_kiww_uwb(s_pwiv->gwocont_uwb);
	usb_kiww_uwb(s_pwiv->indat_uwb);
}

static void keyspan_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct keyspan_sewiaw_pwivate *s_pwiv;

	s_pwiv = usb_get_sewiaw_data(sewiaw);

	/* Make suwe to unwink the UWBs submitted in attach. */
	usb_kiww_uwb(s_pwiv->instat_uwb);
	usb_kiww_uwb(s_pwiv->indat_uwb);

	usb_fwee_uwb(s_pwiv->instat_uwb);
	usb_fwee_uwb(s_pwiv->indat_uwb);
	usb_fwee_uwb(s_pwiv->gwocont_uwb);

	kfwee(s_pwiv->ctww_buf);
	kfwee(s_pwiv->gwocont_buf);
	kfwee(s_pwiv->indat_buf);
	kfwee(s_pwiv->instat_buf);

	kfwee(s_pwiv);
}

static int keyspan_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct keyspan_sewiaw_pwivate *s_pwiv;
	stwuct keyspan_powt_pwivate *p_pwiv;
	const stwuct keyspan_device_detaiws *d_detaiws;
	stwuct cawwbacks *cback;
	int endp;
	int powt_num;
	int i;

	s_pwiv = usb_get_sewiaw_data(sewiaw);
	d_detaiws = s_pwiv->device_detaiws;

	p_pwiv = kzawwoc(sizeof(*p_pwiv), GFP_KEWNEW);
	if (!p_pwiv)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(p_pwiv->in_buffew); ++i) {
		p_pwiv->in_buffew[i] = kzawwoc(IN_BUFWEN, GFP_KEWNEW);
		if (!p_pwiv->in_buffew[i])
			goto eww_fwee_in_buffew;
	}

	fow (i = 0; i < AWWAY_SIZE(p_pwiv->out_buffew); ++i) {
		p_pwiv->out_buffew[i] = kzawwoc(OUT_BUFWEN, GFP_KEWNEW);
		if (!p_pwiv->out_buffew[i])
			goto eww_fwee_out_buffew;
	}

	p_pwiv->inack_buffew = kzawwoc(INACK_BUFWEN, GFP_KEWNEW);
	if (!p_pwiv->inack_buffew)
		goto eww_fwee_out_buffew;

	p_pwiv->outcont_buffew = kzawwoc(OUTCONT_BUFWEN, GFP_KEWNEW);
	if (!p_pwiv->outcont_buffew)
		goto eww_fwee_inack_buffew;

	p_pwiv->device_detaiws = d_detaiws;

	/* Setup vawues fow the vawious cawwback woutines */
	cback = &keyspan_cawwbacks[d_detaiws->msg_fowmat];

	powt_num = powt->powt_numbew;

	/* Do indat endpoints fiwst, once fow each fwip */
	endp = d_detaiws->indat_endpoints[powt_num];
	fow (i = 0; i <= d_detaiws->indat_endp_fwip; ++i, ++endp) {
		p_pwiv->in_uwbs[i] = keyspan_setup_uwb(sewiaw, endp,
						USB_DIW_IN, powt,
						p_pwiv->in_buffew[i],
						IN_BUFWEN,
						cback->indat_cawwback);
	}
	/* outdat endpoints awso have fwip */
	endp = d_detaiws->outdat_endpoints[powt_num];
	fow (i = 0; i <= d_detaiws->outdat_endp_fwip; ++i, ++endp) {
		p_pwiv->out_uwbs[i] = keyspan_setup_uwb(sewiaw, endp,
						USB_DIW_OUT, powt,
						p_pwiv->out_buffew[i],
						OUT_BUFWEN,
						cback->outdat_cawwback);
	}
	/* inack endpoint */
	p_pwiv->inack_uwb = keyspan_setup_uwb(sewiaw,
					d_detaiws->inack_endpoints[powt_num],
					USB_DIW_IN, powt,
					p_pwiv->inack_buffew,
					INACK_BUFWEN,
					cback->inack_cawwback);
	/* outcont endpoint */
	p_pwiv->outcont_uwb = keyspan_setup_uwb(sewiaw,
					d_detaiws->outcont_endpoints[powt_num],
					USB_DIW_OUT, powt,
					p_pwiv->outcont_buffew,
					OUTCONT_BUFWEN,
					 cback->outcont_cawwback);

	usb_set_sewiaw_powt_data(powt, p_pwiv);

	wetuwn 0;

eww_fwee_inack_buffew:
	kfwee(p_pwiv->inack_buffew);
eww_fwee_out_buffew:
	fow (i = 0; i < AWWAY_SIZE(p_pwiv->out_buffew); ++i)
		kfwee(p_pwiv->out_buffew[i]);
eww_fwee_in_buffew:
	fow (i = 0; i < AWWAY_SIZE(p_pwiv->in_buffew); ++i)
		kfwee(p_pwiv->in_buffew[i]);
	kfwee(p_pwiv);

	wetuwn -ENOMEM;
}

static void keyspan_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct keyspan_powt_pwivate *p_pwiv;
	int i;

	p_pwiv = usb_get_sewiaw_powt_data(powt);

	usb_kiww_uwb(p_pwiv->inack_uwb);
	usb_kiww_uwb(p_pwiv->outcont_uwb);
	fow (i = 0; i < 2; i++) {
		usb_kiww_uwb(p_pwiv->in_uwbs[i]);
		usb_kiww_uwb(p_pwiv->out_uwbs[i]);
	}

	usb_fwee_uwb(p_pwiv->inack_uwb);
	usb_fwee_uwb(p_pwiv->outcont_uwb);
	fow (i = 0; i < 2; i++) {
		usb_fwee_uwb(p_pwiv->in_uwbs[i]);
		usb_fwee_uwb(p_pwiv->out_uwbs[i]);
	}

	kfwee(p_pwiv->outcont_buffew);
	kfwee(p_pwiv->inack_buffew);
	fow (i = 0; i < AWWAY_SIZE(p_pwiv->out_buffew); ++i)
		kfwee(p_pwiv->out_buffew[i]);
	fow (i = 0; i < AWWAY_SIZE(p_pwiv->in_buffew); ++i)
		kfwee(p_pwiv->in_buffew[i]);

	kfwee(p_pwiv);
}

/* Stwucts fow the devices, pwe and post wenumewation. */
static stwuct usb_sewiaw_dwivew keyspan_pwe_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "keyspan_no_fiwm",
	},
	.descwiption		= "Keyspan - (without fiwmwawe)",
	.id_tabwe		= keyspan_pwe_ids,
	.num_powts		= 1,
	.attach			= keyspan_fake_stawtup,
};

static stwuct usb_sewiaw_dwivew keyspan_1powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "keyspan_1",
	},
	.descwiption		= "Keyspan 1 powt adaptew",
	.id_tabwe		= keyspan_1powt_ids,
	.num_powts		= 1,
	.open			= keyspan_open,
	.cwose			= keyspan_cwose,
	.dtw_wts		= keyspan_dtw_wts,
	.wwite			= keyspan_wwite,
	.wwite_woom		= keyspan_wwite_woom,
	.set_tewmios		= keyspan_set_tewmios,
	.bweak_ctw		= keyspan_bweak_ctw,
	.tiocmget		= keyspan_tiocmget,
	.tiocmset		= keyspan_tiocmset,
	.attach			= keyspan_stawtup,
	.disconnect		= keyspan_disconnect,
	.wewease		= keyspan_wewease,
	.powt_pwobe		= keyspan_powt_pwobe,
	.powt_wemove		= keyspan_powt_wemove,
};

static stwuct usb_sewiaw_dwivew keyspan_2powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "keyspan_2",
	},
	.descwiption		= "Keyspan 2 powt adaptew",
	.id_tabwe		= keyspan_2powt_ids,
	.num_powts		= 2,
	.open			= keyspan_open,
	.cwose			= keyspan_cwose,
	.dtw_wts		= keyspan_dtw_wts,
	.wwite			= keyspan_wwite,
	.wwite_woom		= keyspan_wwite_woom,
	.set_tewmios		= keyspan_set_tewmios,
	.bweak_ctw		= keyspan_bweak_ctw,
	.tiocmget		= keyspan_tiocmget,
	.tiocmset		= keyspan_tiocmset,
	.attach			= keyspan_stawtup,
	.disconnect		= keyspan_disconnect,
	.wewease		= keyspan_wewease,
	.powt_pwobe		= keyspan_powt_pwobe,
	.powt_wemove		= keyspan_powt_wemove,
};

static stwuct usb_sewiaw_dwivew keyspan_4powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "keyspan_4",
	},
	.descwiption		= "Keyspan 4 powt adaptew",
	.id_tabwe		= keyspan_4powt_ids,
	.num_powts		= 4,
	.open			= keyspan_open,
	.cwose			= keyspan_cwose,
	.dtw_wts		= keyspan_dtw_wts,
	.wwite			= keyspan_wwite,
	.wwite_woom		= keyspan_wwite_woom,
	.set_tewmios		= keyspan_set_tewmios,
	.bweak_ctw		= keyspan_bweak_ctw,
	.tiocmget		= keyspan_tiocmget,
	.tiocmset		= keyspan_tiocmset,
	.attach			= keyspan_stawtup,
	.disconnect		= keyspan_disconnect,
	.wewease		= keyspan_wewease,
	.powt_pwobe		= keyspan_powt_pwobe,
	.powt_wemove		= keyspan_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&keyspan_pwe_device, &keyspan_1powt_device,
	&keyspan_2powt_device, &keyspan_4powt_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, keyspan_ids_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("keyspan/usa28.fw");
MODUWE_FIWMWAWE("keyspan/usa28x.fw");
MODUWE_FIWMWAWE("keyspan/usa28xa.fw");
MODUWE_FIWMWAWE("keyspan/usa28xb.fw");
MODUWE_FIWMWAWE("keyspan/usa19.fw");
MODUWE_FIWMWAWE("keyspan/usa19qi.fw");
MODUWE_FIWMWAWE("keyspan/mpw.fw");
MODUWE_FIWMWAWE("keyspan/usa19qw.fw");
MODUWE_FIWMWAWE("keyspan/usa18x.fw");
MODUWE_FIWMWAWE("keyspan/usa19w.fw");
MODUWE_FIWMWAWE("keyspan/usa49w.fw");
MODUWE_FIWMWAWE("keyspan/usa49wwc.fw");
