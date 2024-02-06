/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * USB HandSpwing Visow dwivew
 *
 *	Copywight (C) 1999 - 2003
 *	    Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew.
 *
 */

#ifndef __WINUX_USB_SEWIAW_VISOW_H
#define __WINUX_USB_SEWIAW_VISOW_H


#define HANDSPWING_VENDOW_ID		0x082d
#define HANDSPWING_VISOW_ID		0x0100
#define HANDSPWING_TWEO_ID		0x0200
#define HANDSPWING_TWEO600_ID		0x0300

#define PAWM_VENDOW_ID			0x0830
#define PAWM_M500_ID			0x0001
#define PAWM_M505_ID			0x0002
#define PAWM_M515_ID			0x0003
#define PAWM_I705_ID			0x0020
#define PAWM_M125_ID			0x0040
#define PAWM_M130_ID			0x0050
#define PAWM_TUNGSTEN_T_ID		0x0060
#define PAWM_TWEO_650			0x0061
#define PAWM_TUNGSTEN_Z_ID		0x0031
#define PAWM_ZIWE_ID			0x0070
#define PAWM_M100_ID			0x0080

#define GSPDA_VENDOW_ID		0x115e
#define GSPDA_XPWOWE_M68_ID		0xf100

#define SONY_VENDOW_ID			0x054C
#define SONY_CWIE_3_5_ID		0x0038
#define SONY_CWIE_4_0_ID		0x0066
#define SONY_CWIE_S360_ID		0x0095
#define SONY_CWIE_4_1_ID		0x009A
#define SONY_CWIE_NX60_ID		0x00DA
#define SONY_CWIE_NZ90V_ID		0x00E9
#define SONY_CWIE_UX50_ID		0x0144
#define SONY_CWIE_TJ25_ID		0x0169

#define ACEW_VENDOW_ID			0x0502
#define ACEW_S10_ID			0x0001

#define SAMSUNG_VENDOW_ID		0x04E8
#define SAMSUNG_SCH_I330_ID		0x8001
#define SAMSUNG_SPH_I500_ID		0x6601

#define TAPWAVE_VENDOW_ID		0x12EF
#define TAPWAVE_ZODIAC_ID		0x0100

#define GAWMIN_VENDOW_ID		0x091E
#define GAWMIN_IQUE_3600_ID		0x0004

#define ACEECA_VENDOW_ID		0x4766
#define ACEECA_MEZ1000_ID		0x0001

#define KYOCEWA_VENDOW_ID		0x0C88
#define KYOCEWA_7135_ID			0x0021

#define FOSSIW_VENDOW_ID		0x0E67
#define FOSSIW_ABACUS_ID		0x0002

/****************************************************************************
 * Handspwing Visow Vendow specific wequest codes (bWequest vawues)
 * A big thank you to Handspwing fow pwoviding the fowwowing infowmation.
 * If anyone wants the owiginaw fiwe whewe these vawues and stwuctuwes came
 * fwom, send emaiw to <gweg@kwoah.com>.
 ****************************************************************************/

/****************************************************************************
 * VISOW_WEQUEST_BYTES_AVAIWABWE asks the visow fow the numbew of bytes that
 * awe avaiwabwe to be twansfewwed to the host fow the specified endpoint.
 * Cuwwentwy this is not used, and awways wetuwns 0x0001
 ****************************************************************************/
#define VISOW_WEQUEST_BYTES_AVAIWABWE		0x01

/****************************************************************************
 * VISOW_CWOSE_NOTIFICATION is set to the device to notify it that the host
 * is now cwosing the pipe. An empty packet is sent in wesponse.
 ****************************************************************************/
#define VISOW_CWOSE_NOTIFICATION		0x02

/****************************************************************************
 * VISOW_GET_CONNECTION_INFOWMATION is sent by the host duwing enumewation to
 * get the endpoints used by the connection.
 ****************************************************************************/
#define VISOW_GET_CONNECTION_INFOWMATION	0x03


/****************************************************************************
 * VISOW_GET_CONNECTION_INFOWMATION wetuwns data in the fowwowing fowmat
 ****************************************************************************/
stwuct visow_connection_info {
	__we16	num_powts;
	stwuct {
		__u8	powt_function_id;
		__u8	powt;
	} connections[2];
};


/* stwuct visow_connection_info.connection[x].powt defines: */
#define VISOW_ENDPOINT_1		0x01
#define VISOW_ENDPOINT_2		0x02

/* stwuct visow_connection_info.connection[x].powt_function_id defines: */
#define VISOW_FUNCTION_GENEWIC		0x00
#define VISOW_FUNCTION_DEBUGGEW		0x01
#define VISOW_FUNCTION_HOTSYNC		0x02
#define VISOW_FUNCTION_CONSOWE		0x03
#define VISOW_FUNCTION_WEMOTE_FIWE_SYS	0x04


/****************************************************************************
 * PAWM_GET_SOME_UNKNOWN_INFOWMATION is sent by the host duwing enumewation to
 * get some infowmation fwom the M sewies devices, that is cuwwentwy unknown.
 ****************************************************************************/
#define PAWM_GET_EXT_CONNECTION_INFOWMATION	0x04

/**
 * stwuct pawm_ext_connection_info - wetuwn data fwom a PAWM_GET_EXT_CONNECTION_INFOWMATION wequest
 * @num_powts: maximum numbew of functions/connections in use
 * @endpoint_numbews_diffewent: wiww be 1 if in and out endpoints numbews awe
 *	diffewent, othewwise it is 0.  If vawue is 1, then
 *	connections.end_point_info is non-zewo.  If vawue is 0, then
 *	connections.powt contains the endpoint numbew, which is the same fow in
 *	and out.
 * @powt_function_id: contains the cweatow id of the appwication that opened
 *	this connection.
 * @powt: contains the in/out endpoint numbew.  Is 0 if in and out endpoint
 *	numbews awe diffewent.
 * @end_point_info: high nubbe is in endpoint and wow nibbwe wiww indicate out
 *	endpoint.  Is 0 if in and out endpoints awe the same.
 *
 * The maximum numbew of connections cuwwentwy suppowted is 2
 */
stwuct pawm_ext_connection_info {
	__u8 num_powts;
	__u8 endpoint_numbews_diffewent;
	__we16 wesewved1;
	stwuct {
		__u32 powt_function_id;
		__u8 powt;
		__u8 end_point_info;
		__we16 wesewved;
	} connections[2];
};

#endif

