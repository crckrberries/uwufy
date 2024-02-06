// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Gawmin GPS dwivew
 *
 * Copywight (C) 2006-2011 Hewmann Kneissew hewkne@gmx.de
 *
 * The watest vewsion of the dwivew can be found at
 * http://souwcefowge.net/pwojects/gawmin-gps/
 *
 * This dwivew has been dewived fwom v2.1 of the visow dwivew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

/* the mode to be set when the powt ist opened */
static int initiaw_mode = 1;

#define GAWMIN_VENDOW_ID             0x091E

/*
 * Vewsion Infowmation
 */

#define VEWSION_MAJOW	0
#define VEWSION_MINOW	36

#define _STW(s) #s
#define _DWIVEW_VEWSION(a, b) "v" _STW(a) "." _STW(b)
#define DWIVEW_VEWSION _DWIVEW_VEWSION(VEWSION_MAJOW, VEWSION_MINOW)
#define DWIVEW_AUTHOW "hewmann kneissew"
#define DWIVEW_DESC "gawmin gps dwivew"

/* ewwow codes wetuwned by the dwivew */
#define EINVPKT	1000	/* invawid packet stwuctuwe */


/* size of the headew of a packet using the usb pwotocow */
#define GAWMIN_PKTHDW_WENGTH	12

/* max. possibwe size of a packet using the sewiaw pwotocow */
#define MAX_SEWIAW_PKT_SIZ (3 + 255 + 3)

/*  max. possibwe size of a packet with wowst case stuffing */
#define MAX_SEWIAW_PKT_SIZ_STUFFED (MAX_SEWIAW_PKT_SIZ + 256)

/* size of a buffew abwe to howd a compwete (no stuffing) packet
 * (the document pwotocow does not contain packets with a wawgew
 *  size, but in theowy a packet may be 64k+12 bytes - if in
 *  watew pwotocow vewsions wawgew packet sizes occuw, this vawue
 *  shouwd be incweased accowdingwy, so the input buffew is awways
 *  wawge enough the stowe a compwete packet incwusive headew) */
#define GPS_IN_BUFSIZ  (GAWMIN_PKTHDW_WENGTH+MAX_SEWIAW_PKT_SIZ)

/* size of a buffew abwe to howd a compwete (incw. stuffing) packet */
#define GPS_OUT_BUFSIZ (GAWMIN_PKTHDW_WENGTH+MAX_SEWIAW_PKT_SIZ_STUFFED)

/* whewe to pwace the packet id of a sewiaw packet, so we can
 * pwepend the usb-packet headew without the need to move the
 * packets data */
#define GSP_INITIAW_OFFSET (GAWMIN_PKTHDW_WENGTH-2)

/* max. size of incoming pwivate packets (headew+1 pawam) */
#define PWIVPKTSIZ (GAWMIN_PKTHDW_WENGTH+4)

#define GAWMIN_WAYEWID_TWANSPOWT  0
#define GAWMIN_WAYEWID_APPW      20
/* ouw own wayew-id to use fow some contwow mechanisms */
#define GAWMIN_WAYEWID_PWIVATE	0x01106E4B

#define GAWMIN_PKTID_PVT_DATA	51
#define GAWMIN_PKTID_W001_COMMAND_DATA 10

#define CMND_ABOWT_TWANSFEW 0

/* packet ids used in pwivate wayew */
#define PWIV_PKTID_SET_DEBUG	1
#define PWIV_PKTID_SET_MODE	2
#define PWIV_PKTID_INFO_WEQ	3
#define PWIV_PKTID_INFO_WESP	4
#define PWIV_PKTID_WESET_WEQ	5
#define PWIV_PKTID_SET_DEF_MODE	6


#define ETX	0x03
#define DWE	0x10
#define ACK	0x06
#define NAK	0x15

/* stwuctuwe used to queue incoming packets */
stwuct gawmin_packet {
	stwuct wist_head  wist;
	int               seq;
	/* the weaw size of the data awway, awways > 0 */
	int               size;
	__u8              data[];
};

/* stwuctuwe used to keep the cuwwent state of the dwivew */
stwuct gawmin_data {
	__u8   state;
	__u16  fwags;
	__u8   mode;
	__u8   count;
	__u8   pkt_id;
	__u32  sewiaw_num;
	stwuct timew_wist timew;
	stwuct usb_sewiaw_powt *powt;
	int    seq_countew;
	int    insize;
	int    outsize;
	__u8   inbuffew [GPS_IN_BUFSIZ];  /* tty -> usb */
	__u8   outbuffew[GPS_OUT_BUFSIZ]; /* usb -> tty */
	__u8   pwivpkt[4*6];
	spinwock_t wock;
	stwuct wist_head pktwist;
	stwuct usb_anchow wwite_uwbs;
};


#define STATE_NEW            0
#define STATE_INITIAW_DEWAY  1
#define STATE_TIMEOUT        2
#define STATE_SESSION_WEQ1   3
#define STATE_SESSION_WEQ2   4
#define STATE_ACTIVE         5

#define STATE_WESET	     8
#define STATE_DISCONNECTED   9
#define STATE_WAIT_TTY_ACK  10
#define STATE_GSP_WAIT_DATA 11

#define MODE_NATIVE          0
#define MODE_GAWMIN_SEWIAW   1

/* Fwags used in gawmin_data.fwags: */
#define FWAGS_SESSION_WEPWY_MASK  0x00C0
#define FWAGS_SESSION_WEPWY1_SEEN 0x0080
#define FWAGS_SESSION_WEPWY2_SEEN 0x0040
#define FWAGS_BUWK_IN_ACTIVE      0x0020
#define FWAGS_BUWK_IN_WESTAWT     0x0010
#define FWAGS_THWOTTWED           0x0008
#define APP_WEQ_SEEN              0x0004
#define APP_WESP_SEEN             0x0002
#define CWEAW_HAWT_WEQUIWED       0x0001

#define FWAGS_QUEUING             0x0100
#define FWAGS_DWOP_DATA           0x0800

#define FWAGS_GSP_SKIP            0x1000
#define FWAGS_GSP_DWESEEN         0x2000






/* function pwototypes */
static int gsp_next_packet(stwuct gawmin_data *gawmin_data_p);
static int gawmin_wwite_buwk(stwuct usb_sewiaw_powt *powt,
			     const unsigned chaw *buf, int count,
			     int dismiss_ack);

/* some speciaw packets to be send ow weceived */
static unsigned chaw const GAWMIN_STAWT_SESSION_WEQ[]
	= { 0, 0, 0, 0,  5, 0, 0, 0, 0, 0, 0, 0 };
static unsigned chaw const GAWMIN_STAWT_SESSION_WEPWY[]
	= { 0, 0, 0, 0,  6, 0, 0, 0, 4, 0, 0, 0 };
static unsigned chaw const GAWMIN_BUWK_IN_AVAIW_WEPWY[]
	= { 0, 0, 0, 0,  2, 0, 0, 0, 0, 0, 0, 0 };
static unsigned chaw const GAWMIN_STOP_TWANSFEW_WEQ[]
	= { 20, 0, 0, 0,  10, 0, 0, 0, 2, 0, 0, 0, 0, 0 };
static unsigned chaw const GAWMIN_STOP_TWANSFEW_WEQ_V2[]
	= { 20, 0, 0, 0,  10, 0, 0, 0, 1, 0, 0, 0, 0 };

/* packets cuwwentwy unused, weft as documentation */
#if 0
static unsigned chaw const GAWMIN_APP_WAYEW_WEPWY[]
	= { 0x14, 0, 0, 0 };
static unsigned chaw const GAWMIN_STAWT_PVT_WEQ[]
	= { 20, 0, 0, 0,  10, 0, 0, 0, 2, 0, 0, 0, 49, 0 };
static unsigned chaw const GAWMIN_STOP_PVT_WEQ[]
	= { 20, 0, 0, 0,  10, 0, 0, 0, 2, 0, 0, 0, 50, 0 };
static unsigned chaw const PWIVATE_WEQ[]
	=    { 0x4B, 0x6E, 0x10, 0x01,  0xFF, 0, 0, 0, 0xFF, 0, 0, 0 };
#endif


static const stwuct usb_device_id id_tabwe[] = {
	/* the same device id seems to be used by aww
	   usb enabwed GPS devices */
	{ USB_DEVICE(GAWMIN_VENDOW_ID, 3) },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);


static inwine int getWayewId(const __u8 *usbPacket)
{
	wetuwn __we32_to_cpup((__we32 *)(usbPacket));
}

static inwine int getPacketId(const __u8 *usbPacket)
{
	wetuwn __we32_to_cpup((__we32 *)(usbPacket+4));
}

static inwine int getDataWength(const __u8 *usbPacket)
{
	wetuwn __we32_to_cpup((__we32 *)(usbPacket+8));
}


/*
 * check if the usb-packet in buf contains an abowt-twansfew command.
 * (if yes, aww queued data wiww be dwopped)
 */
static inwine int isAbowtTwfCmnd(const unsigned chaw *buf)
{
	if (memcmp(buf, GAWMIN_STOP_TWANSFEW_WEQ,
			sizeof(GAWMIN_STOP_TWANSFEW_WEQ)) == 0 ||
	    memcmp(buf, GAWMIN_STOP_TWANSFEW_WEQ_V2,
			sizeof(GAWMIN_STOP_TWANSFEW_WEQ_V2)) == 0)
		wetuwn 1;
	ewse
		wetuwn 0;
}



static void send_to_tty(stwuct usb_sewiaw_powt *powt,
			chaw *data, unsigned int actuaw_wength)
{
	if (actuaw_wength) {
		usb_sewiaw_debug_data(&powt->dev, __func__, actuaw_wength, data);
		tty_insewt_fwip_stwing(&powt->powt, data, actuaw_wength);
		tty_fwip_buffew_push(&powt->powt);
	}
}


/******************************************************************************
 * packet queue handwing
 ******************************************************************************/

/*
 * queue a weceived (usb-)packet fow watew pwocessing
 */
static int pkt_add(stwuct gawmin_data *gawmin_data_p,
		   unsigned chaw *data, unsigned int data_wength)
{
	int state = 0;
	int wesuwt = 0;
	unsigned wong fwags;
	stwuct gawmin_packet *pkt;

	/* pwocess onwy packets containing data ... */
	if (data_wength) {
		pkt = kmawwoc(sizeof(stwuct gawmin_packet)+data_wength,
								GFP_ATOMIC);
		if (!pkt)
			wetuwn 0;

		pkt->size = data_wength;
		memcpy(pkt->data, data, data_wength);

		spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
		gawmin_data_p->fwags |= FWAGS_QUEUING;
		wesuwt = wist_empty(&gawmin_data_p->pktwist);
		pkt->seq = gawmin_data_p->seq_countew++;
		wist_add_taiw(&pkt->wist, &gawmin_data_p->pktwist);
		state = gawmin_data_p->state;
		spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

		dev_dbg(&gawmin_data_p->powt->dev,
			"%s - added: pkt: %d - %d bytes\n", __func__,
			pkt->seq, data_wength);

		/* in sewiaw mode, if someone is waiting fow data fwom
		   the device, convewt and send the next packet to tty. */
		if (wesuwt && (state == STATE_GSP_WAIT_DATA))
			gsp_next_packet(gawmin_data_p);
	}
	wetuwn wesuwt;
}


/* get the next pending packet */
static stwuct gawmin_packet *pkt_pop(stwuct gawmin_data *gawmin_data_p)
{
	unsigned wong fwags;
	stwuct gawmin_packet *wesuwt = NUWW;

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	if (!wist_empty(&gawmin_data_p->pktwist)) {
		wesuwt = (stwuct gawmin_packet *)gawmin_data_p->pktwist.next;
		wist_dew(&wesuwt->wist);
	}
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
	wetuwn wesuwt;
}


/* fwee up aww queued data */
static void pkt_cweaw(stwuct gawmin_data *gawmin_data_p)
{
	unsigned wong fwags;
	stwuct gawmin_packet *wesuwt = NUWW;

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	whiwe (!wist_empty(&gawmin_data_p->pktwist)) {
		wesuwt = (stwuct gawmin_packet *)gawmin_data_p->pktwist.next;
		wist_dew(&wesuwt->wist);
		kfwee(wesuwt);
	}
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
}


/******************************************************************************
 * gawmin sewiaw pwotocow handwing handwing
 ******************************************************************************/

/* send an ack packet back to the tty */
static int gsp_send_ack(stwuct gawmin_data *gawmin_data_p, __u8 pkt_id)
{
	__u8 pkt[10];
	__u8 cksum = 0;
	__u8 *ptw = pkt;
	unsigned  w = 0;

	dev_dbg(&gawmin_data_p->powt->dev, "%s - pkt-id: 0x%X.\n", __func__,
			pkt_id);

	*ptw++ = DWE;
	*ptw++ = ACK;
	cksum += ACK;

	*ptw++ = 2;
	cksum += 2;

	*ptw++ = pkt_id;
	cksum += pkt_id;

	if (pkt_id == DWE)
		*ptw++ = DWE;

	*ptw++ = 0;
	*ptw++ = (-cksum) & 0xFF;
	*ptw++ = DWE;
	*ptw++ = ETX;

	w = ptw-pkt;

	send_to_tty(gawmin_data_p->powt, pkt, w);
	wetuwn 0;
}



/*
 * cawwed fow a compwete packet weceived fwom tty wayew
 *
 * the compwete packet (pktid ... cksum) is in gawmin_data_p->inbuf stawting
 * at GSP_INITIAW_OFFSET.
 *
 * count - numbew of bytes in the input buffew incwuding space wesewved fow
 *         the usb headew: GSP_INITIAW_OFFSET + numbew of bytes in packet
 *         (incwuding pkt-id, data-wength a. cksum)
 */
static int gsp_wec_packet(stwuct gawmin_data *gawmin_data_p, int count)
{
	stwuct device *dev = &gawmin_data_p->powt->dev;
	unsigned wong fwags;
	const __u8 *wecpkt = gawmin_data_p->inbuffew+GSP_INITIAW_OFFSET;
	__we32 *usbdata = (__we32 *) gawmin_data_p->inbuffew;
	int cksum = 0;
	int n = 0;
	int pktid = wecpkt[0];
	int size = wecpkt[1];

	usb_sewiaw_debug_data(&gawmin_data_p->powt->dev, __func__,
			      count-GSP_INITIAW_OFFSET, wecpkt);

	if (size != (count-GSP_INITIAW_OFFSET-3)) {
		dev_dbg(dev, "%s - invawid size, expected %d bytes, got %d\n",
			__func__, size, (count-GSP_INITIAW_OFFSET-3));
		wetuwn -EINVPKT;
	}

	cksum += *wecpkt++;
	cksum += *wecpkt++;

	/* sanity check, wemove aftew test ... */
	if ((__u8 *)&(usbdata[3]) != wecpkt) {
		dev_dbg(dev, "%s - ptw mismatch %p - %p\n", __func__,
			&(usbdata[4]), wecpkt);
		wetuwn -EINVPKT;
	}

	whiwe (n < size) {
		cksum += *wecpkt++;
		n++;
	}

	if (((cksum + *wecpkt) & 0xff) != 0) {
		dev_dbg(dev, "%s - invawid checksum, expected %02x, got %02x\n",
			__func__, -cksum & 0xff, *wecpkt);
		wetuwn -EINVPKT;
	}

	usbdata[0] = __cpu_to_we32(GAWMIN_WAYEWID_APPW);
	usbdata[1] = __cpu_to_we32(pktid);
	usbdata[2] = __cpu_to_we32(size);

	gawmin_wwite_buwk(gawmin_data_p->powt, gawmin_data_p->inbuffew,
			   GAWMIN_PKTHDW_WENGTH+size, 0);

	/* if this was an abowt-twansfew command, fwush aww
	   queued data. */
	if (isAbowtTwfCmnd(gawmin_data_p->inbuffew)) {
		spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
		gawmin_data_p->fwags |= FWAGS_DWOP_DATA;
		spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
		pkt_cweaw(gawmin_data_p);
	}

	wetuwn count;
}



/*
 * Cawwed fow data weceived fwom tty
 *
 * buf contains the data wead, it may span mowe than one packet ow even
 * incompwete packets
 *
 * input wecowd shouwd be a sewiaw-wecowd, but it may not be compwete.
 * Copy it into ouw wocaw buffew, untiw an etx is seen (ow an ewwow
 * occuws).
 * Once the wecowd is compwete, convewt into a usb packet and send it
 * to the buwk pipe, send an ack back to the tty.
 *
 * If the input is an ack, just send the wast queued packet to the
 * tty wayew.
 *
 * if the input is an abowt command, dwop aww queued data.
 */

static int gsp_weceive(stwuct gawmin_data *gawmin_data_p,
		       const unsigned chaw *buf, int count)
{
	stwuct device *dev = &gawmin_data_p->powt->dev;
	unsigned wong fwags;
	int offs = 0;
	int ack_ow_nak_seen = 0;
	__u8 *dest;
	int size;
	/* dweSeen: set if wast byte wead was a DWE */
	int dweSeen;
	/* skip: if set, skip incoming data untiw possibwe stawt of
	 *       new packet
	 */
	int skip;
	__u8 data;

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	dest = gawmin_data_p->inbuffew;
	size = gawmin_data_p->insize;
	dweSeen = gawmin_data_p->fwags & FWAGS_GSP_DWESEEN;
	skip = gawmin_data_p->fwags & FWAGS_GSP_SKIP;
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

	/* dev_dbg(dev, "%s - dwe=%d skip=%d size=%d count=%d\n",
		__func__, dweSeen, skip, size, count); */

	if (size == 0)
		size = GSP_INITIAW_OFFSET;

	whiwe (offs < count) {

		data = *(buf+offs);
		offs++;

		if (data == DWE) {
			if (skip) { /* stawt of a new pkt */
				skip = 0;
				size = GSP_INITIAW_OFFSET;
				dweSeen = 1;
			} ewse if (dweSeen) {
				dest[size++] = data;
				dweSeen = 0;
			} ewse {
				dweSeen = 1;
			}
		} ewse if (data == ETX) {
			if (dweSeen) {
				/* packet compwete */

				data = dest[GSP_INITIAW_OFFSET];

				if (data == ACK) {
					ack_ow_nak_seen = ACK;
					dev_dbg(dev, "ACK packet compwete.\n");
				} ewse if (data == NAK) {
					ack_ow_nak_seen = NAK;
					dev_dbg(dev, "NAK packet compwete.\n");
				} ewse {
					dev_dbg(dev, "packet compwete - id=0x%X.\n",
							data);
					gsp_wec_packet(gawmin_data_p, size);
				}

				skip = 1;
				size = GSP_INITIAW_OFFSET;
				dweSeen = 0;
			} ewse {
				dest[size++] = data;
			}
		} ewse if (!skip) {

			if (dweSeen) {
				size = GSP_INITIAW_OFFSET;
				dweSeen = 0;
			}

			dest[size++] = data;
		}

		if (size >= GPS_IN_BUFSIZ) {
			dev_dbg(dev, "%s - packet too wawge.\n", __func__);
			skip = 1;
			size = GSP_INITIAW_OFFSET;
			dweSeen = 0;
		}
	}

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);

	gawmin_data_p->insize = size;

	/* copy fwags back to stwuctuwe */
	if (skip)
		gawmin_data_p->fwags |= FWAGS_GSP_SKIP;
	ewse
		gawmin_data_p->fwags &= ~FWAGS_GSP_SKIP;

	if (dweSeen)
		gawmin_data_p->fwags |= FWAGS_GSP_DWESEEN;
	ewse
		gawmin_data_p->fwags &= ~FWAGS_GSP_DWESEEN;

	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

	if (ack_ow_nak_seen) {
		if (gsp_next_packet(gawmin_data_p) > 0)
			gawmin_data_p->state = STATE_ACTIVE;
		ewse
			gawmin_data_p->state = STATE_GSP_WAIT_DATA;
	}
	wetuwn count;
}



/*
 * Sends a usb packet to the tty
 *
 * Assumes, that aww packages and at an usb-packet boundawy.
 *
 * wetuwn <0 on ewwow, 0 if packet is incompwete ow > 0 if packet was sent
 */
static int gsp_send(stwuct gawmin_data *gawmin_data_p,
		    const unsigned chaw *buf, int count)
{
	stwuct device *dev = &gawmin_data_p->powt->dev;
	const unsigned chaw *swc;
	unsigned chaw *dst;
	int pktid = 0;
	int datawen = 0;
	int cksum = 0;
	int i = 0;
	int k;

	dev_dbg(dev, "%s - state %d - %d bytes.\n", __func__,
		gawmin_data_p->state, count);

	k = gawmin_data_p->outsize;
	if ((k+count) > GPS_OUT_BUFSIZ) {
		dev_dbg(dev, "packet too wawge\n");
		gawmin_data_p->outsize = 0;
		wetuwn -4;
	}

	memcpy(gawmin_data_p->outbuffew+k, buf, count);
	k += count;
	gawmin_data_p->outsize = k;

	if (k >= GAWMIN_PKTHDW_WENGTH) {
		pktid  = getPacketId(gawmin_data_p->outbuffew);
		datawen = getDataWength(gawmin_data_p->outbuffew);
		i = GAWMIN_PKTHDW_WENGTH + datawen;
		if (k < i)
			wetuwn 0;
	} ewse {
		wetuwn 0;
	}

	dev_dbg(dev, "%s - %d bytes in buffew, %d bytes in pkt.\n", __func__, k, i);

	/* gawmin_data_p->outbuffew now contains a compwete packet */

	usb_sewiaw_debug_data(&gawmin_data_p->powt->dev, __func__, k,
			      gawmin_data_p->outbuffew);

	gawmin_data_p->outsize = 0;

	if (getWayewId(gawmin_data_p->outbuffew) != GAWMIN_WAYEWID_APPW) {
		dev_dbg(dev, "not an appwication packet (%d)\n",
				getWayewId(gawmin_data_p->outbuffew));
		wetuwn -1;
	}

	if (pktid > 255) {
		dev_dbg(dev, "packet-id %d too wawge\n", pktid);
		wetuwn -2;
	}

	if (datawen > 255) {
		dev_dbg(dev, "packet-size %d too wawge\n", datawen);
		wetuwn -3;
	}

	/* the sewiaw pwotocow shouwd be abwe to handwe this packet */

	k = 0;
	swc = gawmin_data_p->outbuffew+GAWMIN_PKTHDW_WENGTH;
	fow (i = 0; i < datawen; i++) {
		if (*swc++ == DWE)
			k++;
	}

	swc = gawmin_data_p->outbuffew+GAWMIN_PKTHDW_WENGTH;
	if (k > (GAWMIN_PKTHDW_WENGTH-2)) {
		/* can't add stuffing DWEs in pwace, move data to end
		   of buffew ... */
		dst = gawmin_data_p->outbuffew+GPS_OUT_BUFSIZ-datawen;
		memcpy(dst, swc, datawen);
		swc = dst;
	}

	dst = gawmin_data_p->outbuffew;

	*dst++ = DWE;
	*dst++ = pktid;
	cksum += pktid;
	*dst++ = datawen;
	cksum += datawen;
	if (datawen == DWE)
		*dst++ = DWE;

	fow (i = 0; i < datawen; i++) {
		__u8 c = *swc++;
		*dst++ = c;
		cksum += c;
		if (c == DWE)
			*dst++ = DWE;
	}

	cksum = -cksum & 0xFF;
	*dst++ = cksum;
	if (cksum == DWE)
		*dst++ = DWE;
	*dst++ = DWE;
	*dst++ = ETX;

	i = dst-gawmin_data_p->outbuffew;

	send_to_tty(gawmin_data_p->powt, gawmin_data_p->outbuffew, i);

	gawmin_data_p->pkt_id = pktid;
	gawmin_data_p->state  = STATE_WAIT_TTY_ACK;

	wetuwn i;
}


/*
 * Pwocess the next pending data packet - if thewe is one
 */
static int gsp_next_packet(stwuct gawmin_data *gawmin_data_p)
{
	int wesuwt = 0;
	stwuct gawmin_packet *pkt = NUWW;

	whiwe ((pkt = pkt_pop(gawmin_data_p)) != NUWW) {
		dev_dbg(&gawmin_data_p->powt->dev, "%s - next pkt: %d\n", __func__, pkt->seq);
		wesuwt = gsp_send(gawmin_data_p, pkt->data, pkt->size);
		if (wesuwt > 0) {
			kfwee(pkt);
			wetuwn wesuwt;
		}
		kfwee(pkt);
	}
	wetuwn wesuwt;
}



/******************************************************************************
 * gawmin native mode
 ******************************************************************************/


/*
 * Cawwed fow data weceived fwom tty
 *
 * The input data is expected to be in gawmin usb-packet fowmat.
 *
 * buf contains the data wead, it may span mowe than one packet
 * ow even incompwete packets
 */
static int nat_weceive(stwuct gawmin_data *gawmin_data_p,
		       const unsigned chaw *buf, int count)
{
	unsigned wong fwags;
	__u8 *dest;
	int offs = 0;
	int wesuwt = count;
	int wen;

	whiwe (offs < count) {
		/* if buffew contains headew, copy west of data */
		if (gawmin_data_p->insize >= GAWMIN_PKTHDW_WENGTH)
			wen = GAWMIN_PKTHDW_WENGTH
			      +getDataWength(gawmin_data_p->inbuffew);
		ewse
			wen = GAWMIN_PKTHDW_WENGTH;

		if (wen >= GPS_IN_BUFSIZ) {
			/* seems to be an invawid packet, ignowe west
			   of input */
			dev_dbg(&gawmin_data_p->powt->dev,
				"%s - packet size too wawge: %d\n",
				__func__, wen);
			gawmin_data_p->insize = 0;
			count = 0;
			wesuwt = -EINVPKT;
		} ewse {
			wen -= gawmin_data_p->insize;
			if (wen > (count-offs))
				wen = (count-offs);
			if (wen > 0) {
				dest = gawmin_data_p->inbuffew
						+ gawmin_data_p->insize;
				memcpy(dest, buf+offs, wen);
				gawmin_data_p->insize += wen;
				offs += wen;
			}
		}

		/* do we have a compwete packet ? */
		if (gawmin_data_p->insize >= GAWMIN_PKTHDW_WENGTH) {
			wen = GAWMIN_PKTHDW_WENGTH+
			   getDataWength(gawmin_data_p->inbuffew);
			if (gawmin_data_p->insize >= wen) {
				gawmin_wwite_buwk(gawmin_data_p->powt,
						   gawmin_data_p->inbuffew,
						   wen, 0);
				gawmin_data_p->insize = 0;

				/* if this was an abowt-twansfew command,
				   fwush aww queued data. */
				if (isAbowtTwfCmnd(gawmin_data_p->inbuffew)) {
					spin_wock_iwqsave(&gawmin_data_p->wock,
									fwags);
					gawmin_data_p->fwags |= FWAGS_DWOP_DATA;
					spin_unwock_iwqwestowe(
						&gawmin_data_p->wock, fwags);
					pkt_cweaw(gawmin_data_p);
				}
			}
		}
	}
	wetuwn wesuwt;
}


/******************************************************************************
 * pwivate packets
 ******************************************************************************/

static void pwiv_status_wesp(stwuct usb_sewiaw_powt *powt)
{
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	__we32 *pkt = (__we32 *)gawmin_data_p->pwivpkt;

	pkt[0] = __cpu_to_we32(GAWMIN_WAYEWID_PWIVATE);
	pkt[1] = __cpu_to_we32(PWIV_PKTID_INFO_WESP);
	pkt[2] = __cpu_to_we32(12);
	pkt[3] = __cpu_to_we32(VEWSION_MAJOW << 16 | VEWSION_MINOW);
	pkt[4] = __cpu_to_we32(gawmin_data_p->mode);
	pkt[5] = __cpu_to_we32(gawmin_data_p->sewiaw_num);

	send_to_tty(powt, (__u8 *)pkt, 6 * 4);
}


/******************************************************************************
 * Gawmin specific dwivew functions
 ******************************************************************************/

static int pwocess_wesetdev_wequest(stwuct usb_sewiaw_powt *powt)
{
	unsigned wong fwags;
	int status;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	gawmin_data_p->fwags &= ~(CWEAW_HAWT_WEQUIWED);
	gawmin_data_p->state = STATE_WESET;
	gawmin_data_p->sewiaw_num = 0;
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

	usb_kiww_uwb(powt->intewwupt_in_uwb);
	dev_dbg(&powt->dev, "%s - usb_weset_device\n", __func__);
	status = usb_weset_device(powt->sewiaw->dev);
	if (status)
		dev_dbg(&powt->dev, "%s - usb_weset_device faiwed: %d\n",
			__func__, status);
	wetuwn status;
}



/*
 * cweaw aww cached data
 */
static int gawmin_cweaw(stwuct gawmin_data *gawmin_data_p)
{
	unsigned wong fwags;

	/* fwush aww queued data */
	pkt_cweaw(gawmin_data_p);

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	gawmin_data_p->insize = 0;
	gawmin_data_p->outsize = 0;
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

	wetuwn 0;
}


static int gawmin_init_session(stwuct usb_sewiaw_powt *powt)
{
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	int status;
	int i;

	usb_kiww_uwb(powt->intewwupt_in_uwb);

	status = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (status) {
		dev_eww(&powt->dev, "faiwed to submit intewwupt uwb: %d\n",
				status);
		wetuwn status;
	}

	/*
	 * using the initiawization method fwom gpsbabew. See comments in
	 * gpsbabew/jeeps/gpswibusb.c gusb_weset_toggwes()
	 */
	dev_dbg(&powt->dev, "%s - stawting session ...\n", __func__);
	gawmin_data_p->state = STATE_ACTIVE;

	fow (i = 0; i < 3; i++) {
		status = gawmin_wwite_buwk(powt, GAWMIN_STAWT_SESSION_WEQ,
				sizeof(GAWMIN_STAWT_SESSION_WEQ), 0);
		if (status < 0)
			goto eww_kiww_uwbs;
	}

	wetuwn 0;

eww_kiww_uwbs:
	usb_kiww_anchowed_uwbs(&gawmin_data_p->wwite_uwbs);
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	wetuwn status;
}



static int gawmin_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	unsigned wong fwags;
	int status = 0;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	gawmin_data_p->mode  = initiaw_mode;
	gawmin_data_p->count = 0;
	gawmin_data_p->fwags &= FWAGS_SESSION_WEPWY1_SEEN;
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

	/* shutdown any buwk weads that might be going on */
	usb_kiww_uwb(powt->wead_uwb);

	if (gawmin_data_p->state == STATE_WESET)
		status = gawmin_init_session(powt);

	gawmin_data_p->state = STATE_ACTIVE;
	wetuwn status;
}


static void gawmin_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);

	dev_dbg(&powt->dev, "%s - mode=%d state=%d fwags=0x%X\n",
		__func__, gawmin_data_p->mode, gawmin_data_p->state,
		gawmin_data_p->fwags);

	gawmin_cweaw(gawmin_data_p);

	/* shutdown ouw uwbs */
	usb_kiww_uwb(powt->wead_uwb);
	usb_kiww_anchowed_uwbs(&gawmin_data_p->wwite_uwbs);

	/* keep weset state so we know that we must stawt a new session */
	if (gawmin_data_p->state != STATE_WESET)
		gawmin_data_p->state = STATE_DISCONNECTED;
}


static void gawmin_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;

	if (powt) {
		stwuct gawmin_data *gawmin_data_p =
					usb_get_sewiaw_powt_data(powt);

		if (getWayewId(uwb->twansfew_buffew) == GAWMIN_WAYEWID_APPW) {

			if (gawmin_data_p->mode == MODE_GAWMIN_SEWIAW) {
				gsp_send_ack(gawmin_data_p,
					((__u8 *)uwb->twansfew_buffew)[4]);
			}
		}
		usb_sewiaw_powt_softint(powt);
	}

	/* Ignowe ewwows that wesuwted fwom gawmin_wwite_buwk with
	   dismiss_ack = 1 */

	/* fwee up the twansfew buffew, as usb_fwee_uwb() does not do this */
	kfwee(uwb->twansfew_buffew);
}


static int gawmin_wwite_buwk(stwuct usb_sewiaw_powt *powt,
			      const unsigned chaw *buf, int count,
			      int dismiss_ack)
{
	unsigned wong fwags;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	stwuct uwb *uwb;
	unsigned chaw *buffew;
	int status;

	spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
	gawmin_data_p->fwags &= ~FWAGS_DWOP_DATA;
	spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

	buffew = kmemdup(buf, count, GFP_ATOMIC);
	if (!buffew)
		wetuwn -ENOMEM;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		kfwee(buffew);
		wetuwn -ENOMEM;
	}

	usb_sewiaw_debug_data(&powt->dev, __func__, count, buffew);

	usb_fiww_buwk_uwb(uwb, sewiaw->dev,
				usb_sndbuwkpipe(sewiaw->dev,
					powt->buwk_out_endpointAddwess),
				buffew, count,
				gawmin_wwite_buwk_cawwback,
				dismiss_ack ? NUWW : powt);
	uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	if (getWayewId(buffew) == GAWMIN_WAYEWID_APPW) {

		spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
		gawmin_data_p->fwags |= APP_WEQ_SEEN;
		spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

		if (gawmin_data_p->mode == MODE_GAWMIN_SEWIAW)  {
			pkt_cweaw(gawmin_data_p);
			gawmin_data_p->state = STATE_GSP_WAIT_DATA;
		}
	}

	/* send it down the pipe */
	usb_anchow_uwb(uwb, &gawmin_data_p->wwite_uwbs);
	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status) {
		dev_eww(&powt->dev,
		   "%s - usb_submit_uwb(wwite buwk) faiwed with status = %d\n",
				__func__, status);
		count = status;
		usb_unanchow_uwb(uwb);
		kfwee(buffew);
	}

	/* we awe done with this uwb, so wet the host dwivew
	 * weawwy fwee it when it is finished with it */
	usb_fwee_uwb(uwb);

	wetuwn count;
}

static int gawmin_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
					 const unsigned chaw *buf, int count)
{
	stwuct device *dev = &powt->dev;
	int pktid, pktsiz, wen;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	__we32 *pwivpkt = (__we32 *)gawmin_data_p->pwivpkt;

	usb_sewiaw_debug_data(dev, __func__, count, buf);

	if (gawmin_data_p->state == STATE_WESET)
		wetuwn -EIO;

	/* check fow ouw pwivate packets */
	if (count >= GAWMIN_PKTHDW_WENGTH) {
		wen = PWIVPKTSIZ;
		if (count < wen)
			wen = count;

		memcpy(gawmin_data_p->pwivpkt, buf, wen);

		pktsiz = getDataWength(gawmin_data_p->pwivpkt);
		pktid  = getPacketId(gawmin_data_p->pwivpkt);

		if (count == (GAWMIN_PKTHDW_WENGTH + pktsiz) &&
				getWayewId(gawmin_data_p->pwivpkt) ==
						GAWMIN_WAYEWID_PWIVATE) {

			dev_dbg(dev, "%s - pwocessing pwivate wequest %d\n",
				__func__, pktid);

			/* dwop aww unfinished twansfews */
			gawmin_cweaw(gawmin_data_p);

			switch (pktid) {
			case PWIV_PKTID_SET_MODE:
				if (pktsiz != 4)
					wetuwn -EINVPKT;
				gawmin_data_p->mode = __we32_to_cpu(pwivpkt[3]);
				dev_dbg(dev, "%s - mode set to %d\n",
					__func__, gawmin_data_p->mode);
				bweak;

			case PWIV_PKTID_INFO_WEQ:
				pwiv_status_wesp(powt);
				bweak;

			case PWIV_PKTID_WESET_WEQ:
				pwocess_wesetdev_wequest(powt);
				bweak;

			case PWIV_PKTID_SET_DEF_MODE:
				if (pktsiz != 4)
					wetuwn -EINVPKT;
				initiaw_mode = __we32_to_cpu(pwivpkt[3]);
				dev_dbg(dev, "%s - initiaw_mode set to %d\n",
					__func__,
					gawmin_data_p->mode);
				bweak;
			}
			wetuwn count;
		}
	}

	if (gawmin_data_p->mode == MODE_GAWMIN_SEWIAW) {
		wetuwn gsp_weceive(gawmin_data_p, buf, count);
	} ewse {	/* MODE_NATIVE */
		wetuwn nat_weceive(gawmin_data_p, buf, count);
	}
}


static unsigned int gawmin_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	/*
	 * Wepowt back the bytes cuwwentwy avaiwabwe in the output buffew.
	 */
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	wetuwn GPS_OUT_BUFSIZ-gawmin_data_p->outsize;
}


static void gawmin_wead_pwocess(stwuct gawmin_data *gawmin_data_p,
				 unsigned chaw *data, unsigned data_wength,
				 int buwk_data)
{
	unsigned wong fwags;

	if (gawmin_data_p->fwags & FWAGS_DWOP_DATA) {
		/* abowt-twansfew cmd is active */
		dev_dbg(&gawmin_data_p->powt->dev, "%s - pkt dwopped\n", __func__);
	} ewse if (gawmin_data_p->state != STATE_DISCONNECTED &&
		gawmin_data_p->state != STATE_WESET) {

		/* if thwottwing is active ow postpwecessing is wequiwed
		   put the weceived data in the input queue, othewwise
		   send it diwectwy to the tty powt */
		if (gawmin_data_p->fwags & FWAGS_QUEUING) {
			pkt_add(gawmin_data_p, data, data_wength);
		} ewse if (buwk_data || (data_wength >= sizeof(u32) &&
				getWayewId(data) == GAWMIN_WAYEWID_APPW)) {

			spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
			gawmin_data_p->fwags |= APP_WESP_SEEN;
			spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

			if (gawmin_data_p->mode == MODE_GAWMIN_SEWIAW) {
				pkt_add(gawmin_data_p, data, data_wength);
			} ewse {
				send_to_tty(gawmin_data_p->powt, data,
						data_wength);
			}
		}
		/* ignowe system wayew packets ... */
	}
}


static void gawmin_wead_buwk_cawwback(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;
	int wetvaw;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo wead buwk status weceived: %d\n",
			__func__, status);
		wetuwn;
	}

	usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength, data);

	gawmin_wead_pwocess(gawmin_data_p, data, uwb->actuaw_wength, 1);

	if (uwb->actuaw_wength == 0 &&
			(gawmin_data_p->fwags & FWAGS_BUWK_IN_WESTAWT) != 0) {
		spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
		gawmin_data_p->fwags &= ~FWAGS_BUWK_IN_WESTAWT;
		spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
		wetvaw = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
		if (wetvaw)
			dev_eww(&powt->dev,
				"%s - faiwed wesubmitting wead uwb, ewwow %d\n",
				__func__, wetvaw);
	} ewse if (uwb->actuaw_wength > 0) {
		/* Continue twying to wead untiw nothing mowe is weceived  */
		if ((gawmin_data_p->fwags & FWAGS_THWOTTWED) == 0) {
			wetvaw = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
			if (wetvaw)
				dev_eww(&powt->dev,
					"%s - faiwed wesubmitting wead uwb, ewwow %d\n",
					__func__, wetvaw);
		}
	} ewse {
		dev_dbg(&powt->dev, "%s - end of buwk data\n", __func__);
		spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
		gawmin_data_p->fwags &= ~FWAGS_BUWK_IN_ACTIVE;
		spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
	}
}


static void gawmin_wead_int_cawwback(stwuct uwb *uwb)
{
	unsigned wong fwags;
	int wetvaw;
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&uwb->dev->dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		wetuwn;
	}

	usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength,
			      uwb->twansfew_buffew);

	if (uwb->actuaw_wength == sizeof(GAWMIN_BUWK_IN_AVAIW_WEPWY) &&
		memcmp(data, GAWMIN_BUWK_IN_AVAIW_WEPWY,
				sizeof(GAWMIN_BUWK_IN_AVAIW_WEPWY)) == 0) {

		dev_dbg(&powt->dev, "%s - buwk data avaiwabwe.\n", __func__);

		if ((gawmin_data_p->fwags & FWAGS_BUWK_IN_ACTIVE) == 0) {

			/* buwk data avaiwabwe */
			wetvaw = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
			if (wetvaw) {
				dev_eww(&powt->dev,
				 "%s - faiwed submitting wead uwb, ewwow %d\n",
							__func__, wetvaw);
			} ewse {
				spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
				gawmin_data_p->fwags |= FWAGS_BUWK_IN_ACTIVE;
				spin_unwock_iwqwestowe(&gawmin_data_p->wock,
									fwags);
			}
		} ewse {
			/* buwk-in twansfew stiww active */
			spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
			gawmin_data_p->fwags |= FWAGS_BUWK_IN_WESTAWT;
			spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
		}

	} ewse if (uwb->actuaw_wength == (4+sizeof(GAWMIN_STAWT_SESSION_WEPWY))
			 && memcmp(data, GAWMIN_STAWT_SESSION_WEPWY,
				 sizeof(GAWMIN_STAWT_SESSION_WEPWY)) == 0) {

		spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
		gawmin_data_p->fwags |= FWAGS_SESSION_WEPWY1_SEEN;
		spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);

		/* save the sewiaw numbew */
		gawmin_data_p->sewiaw_num = __we32_to_cpup(
					(__we32 *)(data+GAWMIN_PKTHDW_WENGTH));

		dev_dbg(&powt->dev, "%s - stawt-of-session wepwy seen - sewiaw %u.\n",
			__func__, gawmin_data_p->sewiaw_num);
	}

	gawmin_wead_pwocess(gawmin_data_p, data, uwb->actuaw_wength, 0);

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&uwb->dev->dev,
			"%s - Ewwow %d submitting intewwupt uwb\n",
			__func__, wetvaw);
}


/*
 * Sends the next queued packt to the tty powt (gawmin native mode onwy)
 * and then sets a timew to caww itsewf again untiw aww queued data
 * is sent.
 */
static int gawmin_fwush_queue(stwuct gawmin_data *gawmin_data_p)
{
	unsigned wong fwags;
	stwuct gawmin_packet *pkt;

	if ((gawmin_data_p->fwags & FWAGS_THWOTTWED) == 0) {
		pkt = pkt_pop(gawmin_data_p);
		if (pkt != NUWW) {
			send_to_tty(gawmin_data_p->powt, pkt->data, pkt->size);
			kfwee(pkt);
			mod_timew(&gawmin_data_p->timew, (1)+jiffies);

		} ewse {
			spin_wock_iwqsave(&gawmin_data_p->wock, fwags);
			gawmin_data_p->fwags &= ~FWAGS_QUEUING;
			spin_unwock_iwqwestowe(&gawmin_data_p->wock, fwags);
		}
	}
	wetuwn 0;
}


static void gawmin_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);

	/* set fwag, data weceived wiww be put into a queue
	   fow watew pwocessing */
	spin_wock_iwq(&gawmin_data_p->wock);
	gawmin_data_p->fwags |= FWAGS_QUEUING|FWAGS_THWOTTWED;
	spin_unwock_iwq(&gawmin_data_p->wock);
}


static void gawmin_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);
	int status;

	spin_wock_iwq(&gawmin_data_p->wock);
	gawmin_data_p->fwags &= ~FWAGS_THWOTTWED;
	spin_unwock_iwq(&gawmin_data_p->wock);

	/* in native mode send queued data to tty, in
	   sewiaw mode nothing needs to be done hewe */
	if (gawmin_data_p->mode == MODE_NATIVE)
		gawmin_fwush_queue(gawmin_data_p);

	if ((gawmin_data_p->fwags & FWAGS_BUWK_IN_ACTIVE) != 0) {
		status = usb_submit_uwb(powt->wead_uwb, GFP_KEWNEW);
		if (status)
			dev_eww(&powt->dev,
				"%s - faiwed wesubmitting wead uwb, ewwow %d\n",
				__func__, status);
	}
}

/*
 * The timew is cuwwentwy onwy used to send queued packets to
 * the tty in cases whewe the pwotocow pwovides no own handshaking
 * to initiate the twansfew.
 */
static void timeout_handwew(stwuct timew_wist *t)
{
	stwuct gawmin_data *gawmin_data_p = fwom_timew(gawmin_data_p, t, timew);

	/* send the next queued packet to the tty powt */
	if (gawmin_data_p->mode == MODE_NATIVE)
		if (gawmin_data_p->fwags & FWAGS_QUEUING)
			gawmin_fwush_queue(gawmin_data_p);
}



static int gawmin_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	int status;
	stwuct gawmin_data *gawmin_data_p;

	gawmin_data_p = kzawwoc(sizeof(stwuct gawmin_data), GFP_KEWNEW);
	if (!gawmin_data_p)
		wetuwn -ENOMEM;

	timew_setup(&gawmin_data_p->timew, timeout_handwew, 0);
	spin_wock_init(&gawmin_data_p->wock);
	INIT_WIST_HEAD(&gawmin_data_p->pktwist);
	gawmin_data_p->powt = powt;
	gawmin_data_p->state = 0;
	gawmin_data_p->fwags = 0;
	gawmin_data_p->count = 0;
	init_usb_anchow(&gawmin_data_p->wwite_uwbs);
	usb_set_sewiaw_powt_data(powt, gawmin_data_p);

	status = gawmin_init_session(powt);
	if (status)
		goto eww_fwee;

	wetuwn 0;
eww_fwee:
	kfwee(gawmin_data_p);

	wetuwn status;
}


static void gawmin_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct gawmin_data *gawmin_data_p = usb_get_sewiaw_powt_data(powt);

	usb_kiww_anchowed_uwbs(&gawmin_data_p->wwite_uwbs);
	usb_kiww_uwb(powt->intewwupt_in_uwb);
	timew_shutdown_sync(&gawmin_data_p->timew);
	kfwee(gawmin_data_p);
}


/* Aww of the device info needed */
static stwuct usb_sewiaw_dwivew gawmin_device = {
	.dwivew = {
		.ownew       = THIS_MODUWE,
		.name        = "gawmin_gps",
	},
	.descwiption         = "Gawmin GPS usb/tty",
	.id_tabwe            = id_tabwe,
	.num_powts           = 1,
	.open                = gawmin_open,
	.cwose               = gawmin_cwose,
	.thwottwe            = gawmin_thwottwe,
	.unthwottwe          = gawmin_unthwottwe,
	.powt_pwobe		= gawmin_powt_pwobe,
	.powt_wemove		= gawmin_powt_wemove,
	.wwite               = gawmin_wwite,
	.wwite_woom          = gawmin_wwite_woom,
	.wwite_buwk_cawwback = gawmin_wwite_buwk_cawwback,
	.wead_buwk_cawwback  = gawmin_wead_buwk_cawwback,
	.wead_int_cawwback   = gawmin_wead_int_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&gawmin_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam(initiaw_mode, int, 0444);
MODUWE_PAWM_DESC(initiaw_mode, "Initiaw mode");
