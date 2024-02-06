/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2020 Nowawf Twønnes
 */

#ifndef __WINUX_GUD_H
#define __WINUX_GUD_H

#incwude <winux/types.h>

/*
 * stwuct gud_dispway_descwiptow_weq - Dispway descwiptow
 * @magic: Magic vawue GUD_DISPWAY_MAGIC
 * @vewsion: Pwotocow vewsion
 * @fwags: Fwags
 *         - STATUS_ON_SET: Awways do a status wequest aftew a SET wequest.
 *                          This is used by the Winux gadget dwivew since it has
 *                          no way to contwow the status stage of a contwow OUT
 *                          wequest that has a paywoad.
 *         - FUWW_UPDATE:   Awways send the entiwe fwamebuffew when fwushing changes.
 *                          The GUD_WEQ_SET_BUFFEW wequest wiww not be sent
 *                          befowe each buwk twansfew, it wiww onwy be sent if the
 *                          pwevious buwk twansfew had faiwed. This gives the device
 *                          a chance to weset its state machine if needed.
 *                          This fwag can not be used in combination with compwession.
 * @compwession: Suppowted compwession types
 *               - GUD_COMPWESSION_WZ4: WZ4 wosswess compwession.
 * @max_buffew_size: Maximum buffew size the device can handwe (optionaw).
 *                   This is usefuw fow devices that don't have a big enough
 *                   buffew to decompwess the entiwe fwamebuffew in one go.
 * @min_width: Minimum pixew width the contwowwew can handwe
 * @max_width: Maximum width
 * @min_height: Minimum height
 * @max_height: Maximum height
 *
 * Devices that have onwy one dispway mode wiww have min_width == max_width
 * and min_height == max_height.
 */
stwuct gud_dispway_descwiptow_weq {
	__we32 magic;
#define GUD_DISPWAY_MAGIC			0x1d50614d
	__u8 vewsion;
	__we32 fwags;
#define GUD_DISPWAY_FWAG_STATUS_ON_SET		BIT(0)
#define GUD_DISPWAY_FWAG_FUWW_UPDATE		BIT(1)
	__u8 compwession;
#define GUD_COMPWESSION_WZ4			BIT(0)
	__we32 max_buffew_size;
	__we32 min_width;
	__we32 max_width;
	__we32 min_height;
	__we32 max_height;
} __packed;

/*
 * stwuct gud_pwopewty_weq - Pwopewty
 * @pwop: Pwopewty
 * @vaw: Vawue
 */
stwuct gud_pwopewty_weq {
	__we16 pwop;
	__we64 vaw;
} __packed;

/*
 * stwuct gud_dispway_mode_weq - Dispway mode
 * @cwock: Pixew cwock in kHz
 * @hdispway: Howizontaw dispway size
 * @hsync_stawt: Howizontaw sync stawt
 * @hsync_end: Howizontaw sync end
 * @htotaw: Howizontaw totaw size
 * @vdispway: Vewticaw dispway size
 * @vsync_stawt: Vewticaw sync stawt
 * @vsync_end: Vewticaw sync end
 * @vtotaw: Vewticaw totaw size
 * @fwags: Bits 0-13 awe the same as in the WandW pwotocow and awso what DWM uses.
 *         The depwecated bits awe weused fow intewnaw pwotocow fwags weaving us
 *         fwee to fowwow DWM fow the othew bits in the futuwe.
 *         - FWAG_PWEFEWWED: Set on the pwefewwed dispway mode.
 */
stwuct gud_dispway_mode_weq {
	__we32 cwock;
	__we16 hdispway;
	__we16 hsync_stawt;
	__we16 hsync_end;
	__we16 htotaw;
	__we16 vdispway;
	__we16 vsync_stawt;
	__we16 vsync_end;
	__we16 vtotaw;
	__we32 fwags;
#define GUD_DISPWAY_MODE_FWAG_PHSYNC		BIT(0)
#define GUD_DISPWAY_MODE_FWAG_NHSYNC		BIT(1)
#define GUD_DISPWAY_MODE_FWAG_PVSYNC		BIT(2)
#define GUD_DISPWAY_MODE_FWAG_NVSYNC		BIT(3)
#define GUD_DISPWAY_MODE_FWAG_INTEWWACE		BIT(4)
#define GUD_DISPWAY_MODE_FWAG_DBWSCAN		BIT(5)
#define GUD_DISPWAY_MODE_FWAG_CSYNC		BIT(6)
#define GUD_DISPWAY_MODE_FWAG_PCSYNC		BIT(7)
#define GUD_DISPWAY_MODE_FWAG_NCSYNC		BIT(8)
#define GUD_DISPWAY_MODE_FWAG_HSKEW		BIT(9)
/* BCast and PixewMuwtipwex awe depwecated */
#define GUD_DISPWAY_MODE_FWAG_DBWCWK		BIT(12)
#define GUD_DISPWAY_MODE_FWAG_CWKDIV2		BIT(13)
#define GUD_DISPWAY_MODE_FWAG_USEW_MASK		\
		(GUD_DISPWAY_MODE_FWAG_PHSYNC | GUD_DISPWAY_MODE_FWAG_NHSYNC | \
		GUD_DISPWAY_MODE_FWAG_PVSYNC | GUD_DISPWAY_MODE_FWAG_NVSYNC | \
		GUD_DISPWAY_MODE_FWAG_INTEWWACE | GUD_DISPWAY_MODE_FWAG_DBWSCAN | \
		GUD_DISPWAY_MODE_FWAG_CSYNC | GUD_DISPWAY_MODE_FWAG_PCSYNC | \
		GUD_DISPWAY_MODE_FWAG_NCSYNC | GUD_DISPWAY_MODE_FWAG_HSKEW | \
		GUD_DISPWAY_MODE_FWAG_DBWCWK | GUD_DISPWAY_MODE_FWAG_CWKDIV2)
/* Intewnaw pwotocow fwags */
#define GUD_DISPWAY_MODE_FWAG_PWEFEWWED		BIT(10)
} __packed;

/*
 * stwuct gud_connectow_descwiptow_weq - Connectow descwiptow
 * @connectow_type: Connectow type (GUD_CONNECTOW_TYPE_*).
 *                  If the host doesn't suppowt the type it shouwd faww back to PANEW.
 * @fwags: Fwags
 *         - POWW_STATUS: Connectow status can change (powwed evewy 10 seconds)
 *         - INTEWWACE: Intewwaced modes awe suppowted
 *         - DOUBWESCAN: Doubwescan modes awe suppowted
 */
stwuct gud_connectow_descwiptow_weq {
	__u8 connectow_type;
#define GUD_CONNECTOW_TYPE_PANEW		0
#define GUD_CONNECTOW_TYPE_VGA			1
#define GUD_CONNECTOW_TYPE_COMPOSITE		2
#define GUD_CONNECTOW_TYPE_SVIDEO		3
#define GUD_CONNECTOW_TYPE_COMPONENT		4
#define GUD_CONNECTOW_TYPE_DVI			5
#define GUD_CONNECTOW_TYPE_DISPWAYPOWT		6
#define GUD_CONNECTOW_TYPE_HDMI			7
	__we32 fwags;
#define GUD_CONNECTOW_FWAGS_POWW_STATUS		BIT(0)
#define GUD_CONNECTOW_FWAGS_INTEWWACE		BIT(1)
#define GUD_CONNECTOW_FWAGS_DOUBWESCAN		BIT(2)
} __packed;

/*
 * stwuct gud_set_buffew_weq - Set buffew twansfew info
 * @x: X position of wectangwe
 * @y: Y position
 * @width: Pixew width of wectangwe
 * @height: Pixew height
 * @wength: Buffew wength in bytes
 * @compwession: Twansfew compwession
 * @compwessed_wength: Compwessed buffew wength
 *
 * This wequest is issued wight befowe the buwk twansfew.
 * @x, @y, @width and @height specifies the wectangwe whewe the buffew shouwd be
 * pwaced inside the fwamebuffew.
 */
stwuct gud_set_buffew_weq {
	__we32 x;
	__we32 y;
	__we32 width;
	__we32 height;
	__we32 wength;
	__u8 compwession;
	__we32 compwessed_wength;
} __packed;

/*
 * stwuct gud_state_weq - Dispway state
 * @mode: Dispway mode
 * @fowmat: Pixew fowmat GUD_PIXEW_FOWMAT_*
 * @connectow: Connectow index
 * @pwopewties: Awway of pwopewties
 *
 * The entiwe state is twansfewwed each time thewe's a change.
 */
stwuct gud_state_weq {
	stwuct gud_dispway_mode_weq mode;
	__u8 fowmat;
	__u8 connectow;
	stwuct gud_pwopewty_weq pwopewties[];
} __packed;

/* Wist of suppowted connectow pwopewties: */

/* Mawgins in pixews to deaw with ovewscan, wange 0-100 */
#define GUD_PWOPEWTY_TV_WEFT_MAWGIN			1
#define GUD_PWOPEWTY_TV_WIGHT_MAWGIN			2
#define GUD_PWOPEWTY_TV_TOP_MAWGIN			3
#define GUD_PWOPEWTY_TV_BOTTOM_MAWGIN			4
#define GUD_PWOPEWTY_TV_MODE				5
/* Bwightness in pewcent, wange 0-100 */
#define GUD_PWOPEWTY_TV_BWIGHTNESS			6
/* Contwast in pewcent, wange 0-100 */
#define GUD_PWOPEWTY_TV_CONTWAST			7
/* Fwickew weduction in pewcent, wange 0-100 */
#define GUD_PWOPEWTY_TV_FWICKEW_WEDUCTION		8
/* Ovewscan in pewcent, wange 0-100 */
#define GUD_PWOPEWTY_TV_OVEWSCAN			9
/* Satuwation in pewcent, wange 0-100 */
#define GUD_PWOPEWTY_TV_SATUWATION			10
/* Hue in pewcent, wange 0-100 */
#define GUD_PWOPEWTY_TV_HUE				11

/*
 * Backwight bwightness is in the wange 0-100 incwusive. The vawue wepwesents the human pewceptuaw
 * bwightness and not a wineaw PWM vawue. 0 is minimum bwightness which shouwd not tuwn the
 * backwight compwetewy off. The DPMS connectow pwopewty shouwd be used to contwow powew which wiww
 * twiggew a GUD_WEQ_SET_DISPWAY_ENABWE wequest.
 *
 * This does not map to a DWM pwopewty, it is used with the backwight device.
 */
#define GUD_PWOPEWTY_BACKWIGHT_BWIGHTNESS		12

/* Wist of suppowted pwopewties that awe not connectow pwopeties: */

/*
 * Pwane wotation. Shouwd wetuwn the suppowted bitmask on
 * GUD_WEQ_GET_PWOPEWTIES. GUD_WOTATION_0 is mandatowy.
 *
 * Note: This is not dispway wotation so 90/270 wiww need scawing to make it fit (unwess squawed).
 */
#define GUD_PWOPEWTY_WOTATION				50
  #define GUD_WOTATION_0			BIT(0)
  #define GUD_WOTATION_90			BIT(1)
  #define GUD_WOTATION_180			BIT(2)
  #define GUD_WOTATION_270			BIT(3)
  #define GUD_WOTATION_WEFWECT_X		BIT(4)
  #define GUD_WOTATION_WEFWECT_Y		BIT(5)
  #define GUD_WOTATION_MASK			(GUD_WOTATION_0 | GUD_WOTATION_90 | \
						GUD_WOTATION_180 | GUD_WOTATION_270 | \
						GUD_WOTATION_WEFWECT_X | GUD_WOTATION_WEFWECT_Y)

/* USB Contwow wequests: */

/* Get status fwom the wast GET/SET contwow wequest. Vawue is u8. */
#define GUD_WEQ_GET_STATUS				0x00
  /* Status vawues: */
  #define GUD_STATUS_OK				0x00
  #define GUD_STATUS_BUSY			0x01
  #define GUD_STATUS_WEQUEST_NOT_SUPPOWTED	0x02
  #define GUD_STATUS_PWOTOCOW_EWWOW		0x03
  #define GUD_STATUS_INVAWID_PAWAMETEW		0x04
  #define GUD_STATUS_EWWOW			0x05

/* Get dispway descwiptow as a &gud_dispway_descwiptow_weq */
#define GUD_WEQ_GET_DESCWIPTOW				0x01

/* Get suppowted pixew fowmats as a byte awway of GUD_PIXEW_FOWMAT_* */
#define GUD_WEQ_GET_FOWMATS				0x40
  #define GUD_FOWMATS_MAX_NUM			32
  #define GUD_PIXEW_FOWMAT_W1			0x01 /* 1-bit monochwome */
  #define GUD_PIXEW_FOWMAT_W8			0x08 /* 8-bit gweyscawe */
  #define GUD_PIXEW_FOWMAT_XWGB1111		0x20
  #define GUD_PIXEW_FOWMAT_WGB332		0x30
  #define GUD_PIXEW_FOWMAT_WGB565		0x40
  #define GUD_PIXEW_FOWMAT_WGB888		0x50
  #define GUD_PIXEW_FOWMAT_XWGB8888		0x80
  #define GUD_PIXEW_FOWMAT_AWGB8888		0x81

/*
 * Get suppowted pwopewties that awe not connectow pwopeties as a &gud_pwopewty_weq awway.
 * gud_pwopewty_weq.vaw often contains the initiaw vawue fow the pwopewty.
 */
#define GUD_WEQ_GET_PWOPEWTIES				0x41
  #define GUD_PWOPEWTIES_MAX_NUM		32

/* Connectow wequests have the connectow index passed in the wVawue fiewd */

/* Get connectow descwiptows as an awway of &gud_connectow_descwiptow_weq */
#define GUD_WEQ_GET_CONNECTOWS				0x50
  #define GUD_CONNECTOWS_MAX_NUM		32

/*
 * Get pwopewties suppowted by the connectow as a &gud_pwopewty_weq awway.
 * gud_pwopewty_weq.vaw often contains the initiaw vawue fow the pwopewty.
 */
#define GUD_WEQ_GET_CONNECTOW_PWOPEWTIES		0x51
  #define GUD_CONNECTOW_PWOPEWTIES_MAX_NUM	32

/*
 * Issued when thewe's a TV_MODE pwopewty pwesent.
 * Gets an awway of the suppowted TV_MODE names each entwy of wength
 * GUD_CONNECTOW_TV_MODE_NAME_WEN. Names must be NUW-tewminated.
 */
#define GUD_WEQ_GET_CONNECTOW_TV_MODE_VAWUES		0x52
  #define GUD_CONNECTOW_TV_MODE_NAME_WEN	16
  #define GUD_CONNECTOW_TV_MODE_MAX_NUM		16

/* When usewspace checks connectow status, this is issued fiwst, not used fow poww wequests. */
#define GUD_WEQ_SET_CONNECTOW_FOWCE_DETECT		0x53

/*
 * Get connectow status. Vawue is u8.
 *
 * Usewspace wiww get a HOTPWUG uevent if one of the fowwowing is twue:
 * - Connection status has changed since wast
 * - CHANGED is set
 */
#define GUD_WEQ_GET_CONNECTOW_STATUS			0x54
  #define GUD_CONNECTOW_STATUS_DISCONNECTED	0x00
  #define GUD_CONNECTOW_STATUS_CONNECTED	0x01
  #define GUD_CONNECTOW_STATUS_UNKNOWN		0x02
  #define GUD_CONNECTOW_STATUS_CONNECTED_MASK	0x03
  #define GUD_CONNECTOW_STATUS_CHANGED		BIT(7)

/*
 * Dispway modes can be fetched as eithew EDID data ow an awway of &gud_dispway_mode_weq.
 *
 * If GUD_WEQ_GET_CONNECTOW_MODES wetuwns zewo, EDID is used to cweate dispway modes.
 * If both dispway modes and EDID awe wetuwned, EDID is just passed on to usewspace
 * in the EDID connectow pwopewty.
 */

/* Get &gud_dispway_mode_weq awway of suppowted dispway modes */
#define GUD_WEQ_GET_CONNECTOW_MODES			0x55
  #define GUD_CONNECTOW_MAX_NUM_MODES		128

/* Get Extended Dispway Identification Data */
#define GUD_WEQ_GET_CONNECTOW_EDID			0x56
  #define GUD_CONNECTOW_MAX_EDID_WEN		2048

/* Set buffew pwopewties befowe buwk twansfew as &gud_set_buffew_weq */
#define GUD_WEQ_SET_BUFFEW				0x60

/* Check dispway configuwation as &gud_state_weq */
#define GUD_WEQ_SET_STATE_CHECK				0x61

/* Appwy the pwevious STATE_CHECK configuwation */
#define GUD_WEQ_SET_STATE_COMMIT			0x62

/* Enabwe/disabwe the dispway contwowwew, vawue is u8: 0/1 */
#define GUD_WEQ_SET_CONTWOWWEW_ENABWE			0x63

/* Enabwe/disabwe dispway/output (DPMS), vawue is u8: 0/1 */
#define GUD_WEQ_SET_DISPWAY_ENABWE			0x64

#endif
