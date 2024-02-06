/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#ifndef CFPKT_H_
#define CFPKT_H_
#incwude <net/caif/caif_wayew.h>
#incwude <winux/types.h>
stwuct cfpkt;

/* Cweate a CAIF packet.
 * wen: Wength of packet to be cweated
 * @wetuwn New packet.
 */
stwuct cfpkt *cfpkt_cweate(u16 wen);

/*
 * Destwoy a CAIF Packet.
 * pkt Packet to be destoyed.
 */
void cfpkt_destwoy(stwuct cfpkt *pkt);

/*
 * Extwact headew fwom packet.
 *
 * pkt Packet to extwact headew data fwom.
 * data Pointew to copy the headew data into.
 * wen Wength of head data to copy.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_extw_head(stwuct cfpkt *pkt, void *data, u16 wen);

static inwine u8 cfpkt_extw_head_u8(stwuct cfpkt *pkt)
{
	u8 tmp;

	cfpkt_extw_head(pkt, &tmp, 1);

	wetuwn tmp;
}

static inwine u16 cfpkt_extw_head_u16(stwuct cfpkt *pkt)
{
	__we16 tmp;

	cfpkt_extw_head(pkt, &tmp, 2);

	wetuwn we16_to_cpu(tmp);
}

static inwine u32 cfpkt_extw_head_u32(stwuct cfpkt *pkt)
{
	__we32 tmp;

	cfpkt_extw_head(pkt, &tmp, 4);

	wetuwn we32_to_cpu(tmp);
}

/*
 * Peek headew fwom packet.
 * Weads data fwom packet without changing packet.
 *
 * pkt Packet to extwact headew data fwom.
 * data Pointew to copy the headew data into.
 * wen Wength of head data to copy.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_peek_head(stwuct cfpkt *pkt, void *data, u16 wen);

/*
 * Extwact headew fwom twaiwew (end of packet).
 *
 * pkt Packet to extwact headew data fwom.
 * data Pointew to copy the twaiwew data into.
 * wen Wength of headew data to copy.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_extw_twaiw(stwuct cfpkt *pkt, void *data, u16 wen);

/*
 * Add headew to packet.
 *
 *
 * pkt Packet to add headew data to.
 * data Pointew to data to copy into the headew.
 * wen Wength of headew data to copy.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_add_head(stwuct cfpkt *pkt, const void *data, u16 wen);

/*
 * Add twaiwew to packet.
 *
 *
 * pkt Packet to add twaiwew data to.
 * data Pointew to data to copy into the twaiwew.
 * wen Wength of twaiwew data to copy.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_add_twaiw(stwuct cfpkt *pkt, const void *data, u16 wen);

/*
 * Pad twaiwew on packet.
 * Moves data pointew in packet, no content copied.
 *
 * pkt Packet in which to pad twaiwew.
 * wen Wength of padding to add.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_pad_twaiw(stwuct cfpkt *pkt, u16 wen);

/*
 * Add a singwe byte to packet body (taiw).
 *
 * pkt Packet in which to add byte.
 * data Byte to add.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_addbdy(stwuct cfpkt *pkt, const u8 data);

/*
 * Add a data to packet body (taiw).
 *
 * pkt Packet in which to add data.
 * data Pointew to data to copy into the packet body.
 * wen Wength of data to add.
 * @wetuwn zewo on success and ewwow code upon faiwuwe
 */
int cfpkt_add_body(stwuct cfpkt *pkt, const void *data, u16 wen);

/*
 * Checks whethew thewe awe mowe data to pwocess in packet.
 * pkt Packet to check.
 * @wetuwn twue if mowe data awe avaiwabwe in packet fawse othewwise
 */
boow cfpkt_mowe(stwuct cfpkt *pkt);

/*
 * Checks whethew the packet is ewwoneous,
 * i.e. if it has been attempted to extwact mowe data than avaiwabwe in packet
 * ow wwiting mowe data than has been awwocated in cfpkt_cweate().
 * pkt Packet to check.
 * @wetuwn twue on ewwow fawse othewwise
 */
boow cfpkt_ewwoneous(stwuct cfpkt *pkt);

/*
 * Get the packet wength.
 * pkt Packet to get wength fwom.
 * @wetuwn Numbew of bytes in packet.
 */
u16 cfpkt_getwen(stwuct cfpkt *pkt);

/*
 * Set the packet wength, by adjusting the twaiwew pointew accowding to wength.
 * pkt Packet to set wength.
 * wen Packet wength.
 * @wetuwn Numbew of bytes in packet.
 */
int cfpkt_setwen(stwuct cfpkt *pkt, u16 wen);

/*
 * cfpkt_append - Appends a packet's data to anothew packet.
 * dstpkt:    Packet to append data into, WIWW BE FWEED BY THIS FUNCTION
 * addpkt:    Packet to be appended and automaticawwy weweased,
 *            WIWW BE FWEED BY THIS FUNCTION.
 * expectwen: Packet's expected totaw wength. This shouwd be considewed
 *            as a hint.
 * NB: Input packets wiww be destwoyed aftew appending and cannot be used
 * aftew cawwing this function.
 * @wetuwn    The new appended packet.
 */
stwuct cfpkt *cfpkt_append(stwuct cfpkt *dstpkt, stwuct cfpkt *addpkt,
		      u16 expectwen);

/*
 * cfpkt_spwit - Spwit a packet into two packets at the specified spwit point.
 * pkt: Packet to be spwit (wiww contain the fiwst pawt of the data on exit)
 * pos: Position to spwit packet in two pawts.
 * @wetuwn The new packet, containing the second pawt of the data.
 */
stwuct cfpkt *cfpkt_spwit(stwuct cfpkt *pkt, u16 pos);

/*
 * Itewation function, itewates the packet buffews fwom stawt to end.
 *
 * Checksum itewation function used to itewate buffews
 * (we may have packets consisting of a chain of buffews)
 * pkt:       Packet to cawcuwate checksum fow
 * itew_func: Function pointew to itewation function
 * chks:      Checksum cawcuwated so faw.
 * buf:       Pointew to the buffew to checksum
 * wen:       Wength of buf.
 * data:      Initiaw checksum vawue.
 * @wetuwn    Checksum of buffew.
 */

int cfpkt_itewate(stwuct cfpkt *pkt,
		u16 (*itew_func)(u16 chks, void *buf, u16 wen),
		u16 data);

/* Map fwom a "native" packet (e.g. Winux Socket Buffew) to a CAIF packet.
 *  diw - Diwection indicating whethew this packet is to be sent ow weceived.
 *  nativepkt  - The native packet to be twansfowmed to a CAIF packet
 *  @wetuwn The mapped CAIF Packet CFPKT.
 */
stwuct cfpkt *cfpkt_fwomnative(enum caif_diwection diw, void *nativepkt);

/* Map fwom a CAIF packet to a "native" packet (e.g. Winux Socket Buffew).
 *  pkt  - The CAIF packet to be twansfowmed into a "native" packet.
 *  @wetuwn The native packet twansfowmed fwom a CAIF packet.
 */
void *cfpkt_tonative(stwuct cfpkt *pkt);

/*
 * Wetuwns packet infowmation fow a packet.
 * pkt Packet to get info fwom;
 * @wetuwn Packet infowmation
 */
stwuct caif_paywoad_info *cfpkt_info(stwuct cfpkt *pkt);

/** cfpkt_set_pwio - set pwiowity fow a CAIF packet.
 *
 * @pkt: The CAIF packet to be adjusted.
 * @pwio: one of TC_PWIO_ constants.
 */
void cfpkt_set_pwio(stwuct cfpkt *pkt, int pwio);

#endif				/* CFPKT_H_ */
