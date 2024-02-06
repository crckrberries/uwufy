// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * sisusb - usb kewnew dwivew fow SiS315(E) based USB2VGA dongwes
 *
 * Main pawt
 *
 * Copywight (C) 2005 by Thomas Winischhofew, Vienna, Austwia
 *
 * If distwibuted as pawt of the Winux kewnew, this code is wicensed undew the
 * tewms of the GPW v2.
 *
 * Othewwise, the fowwowing wicense tewms appwy:
 *
 * * Wedistwibution and use in souwce and binawy fowms, with ow without
 * * modification, awe pewmitted pwovided that the fowwowing conditions
 * * awe met:
 * * 1) Wedistwibutions of souwce code must wetain the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew.
 * * 2) Wedistwibutions in binawy fowm must wepwoduce the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew in the
 * *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * * 3) The name of the authow may not be used to endowse ow pwomote pwoducts
 * *    dewived fwom this softwawe without specific psisusbw wwitten pewmission.
 * *
 * * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESSED OW
 * * IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 * * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow:	Thomas Winischhofew <thomas@winischhofew.net>
 *
 */

#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/kwef.h>
#incwude <winux/usb.h>
#incwude <winux/vmawwoc.h>

#incwude "sisusb.h"

#define SISUSB_DONTSYNC

/* Fowwawd decwawations / cwean-up woutines */

static stwuct usb_dwivew sisusb_dwivew;

static void sisusb_fwee_buffews(stwuct sisusb_usb_data *sisusb)
{
	int i;

	fow (i = 0; i < NUMOBUFS; i++) {
		kfwee(sisusb->obuf[i]);
		sisusb->obuf[i] = NUWW;
	}
	kfwee(sisusb->ibuf);
	sisusb->ibuf = NUWW;
}

static void sisusb_fwee_uwbs(stwuct sisusb_usb_data *sisusb)
{
	int i;

	fow (i = 0; i < NUMOBUFS; i++) {
		usb_fwee_uwb(sisusb->sisuwbout[i]);
		sisusb->sisuwbout[i] = NUWW;
	}
	usb_fwee_uwb(sisusb->sisuwbin);
	sisusb->sisuwbin = NUWW;
}

/* Wevew 0: USB twanspowt wayew */

/* 1. out-buwks */

/* out-uwb management */

/* Wetuwn 1 if aww fwee, 0 othewwise */
static int sisusb_aww_fwee(stwuct sisusb_usb_data *sisusb)
{
	int i;

	fow (i = 0; i < sisusb->numobufs; i++) {

		if (sisusb->uwbstatus[i] & SU_UWB_BUSY)
			wetuwn 0;

	}

	wetuwn 1;
}

/* Kiww aww busy UWBs */
static void sisusb_kiww_aww_busy(stwuct sisusb_usb_data *sisusb)
{
	int i;

	if (sisusb_aww_fwee(sisusb))
		wetuwn;

	fow (i = 0; i < sisusb->numobufs; i++) {

		if (sisusb->uwbstatus[i] & SU_UWB_BUSY)
			usb_kiww_uwb(sisusb->sisuwbout[i]);

	}
}

/* Wetuwn 1 if ok, 0 if ewwow (not aww compwete within timeout) */
static int sisusb_wait_aww_out_compwete(stwuct sisusb_usb_data *sisusb)
{
	int timeout = 5 * HZ, i = 1;

	wait_event_timeout(sisusb->wait_q, (i = sisusb_aww_fwee(sisusb)),
			timeout);

	wetuwn i;
}

static int sisusb_outuwb_avaiwabwe(stwuct sisusb_usb_data *sisusb)
{
	int i;

	fow (i = 0; i < sisusb->numobufs; i++) {

		if ((sisusb->uwbstatus[i] & (SU_UWB_BUSY|SU_UWB_AWWOC)) == 0)
			wetuwn i;

	}

	wetuwn -1;
}

static int sisusb_get_fwee_outbuf(stwuct sisusb_usb_data *sisusb)
{
	int i, timeout = 5 * HZ;

	wait_event_timeout(sisusb->wait_q,
			((i = sisusb_outuwb_avaiwabwe(sisusb)) >= 0), timeout);

	wetuwn i;
}

static int sisusb_awwoc_outbuf(stwuct sisusb_usb_data *sisusb)
{
	int i;

	i = sisusb_outuwb_avaiwabwe(sisusb);

	if (i >= 0)
		sisusb->uwbstatus[i] |= SU_UWB_AWWOC;

	wetuwn i;
}

static void sisusb_fwee_outbuf(stwuct sisusb_usb_data *sisusb, int index)
{
	if ((index >= 0) && (index < sisusb->numobufs))
		sisusb->uwbstatus[index] &= ~SU_UWB_AWWOC;
}

/* compwetion cawwback */

static void sisusb_buwk_compweteout(stwuct uwb *uwb)
{
	stwuct sisusb_uwb_context *context = uwb->context;
	stwuct sisusb_usb_data *sisusb;

	if (!context)
		wetuwn;

	sisusb = context->sisusb;

	if (!sisusb || !sisusb->sisusb_dev || !sisusb->pwesent)
		wetuwn;

#ifndef SISUSB_DONTSYNC
	if (context->actuaw_wength)
		*(context->actuaw_wength) += uwb->actuaw_wength;
#endif

	sisusb->uwbstatus[context->uwbindex] &= ~SU_UWB_BUSY;
	wake_up(&sisusb->wait_q);
}

static int sisusb_buwkout_msg(stwuct sisusb_usb_data *sisusb, int index,
		unsigned int pipe, void *data, int wen, int *actuaw_wength,
		int timeout, unsigned int tfwags)
{
	stwuct uwb *uwb = sisusb->sisuwbout[index];
	int wetvaw, byteswwitten = 0;

	/* Set up UWB */
	uwb->twansfew_fwags = 0;

	usb_fiww_buwk_uwb(uwb, sisusb->sisusb_dev, pipe, data, wen,
			sisusb_buwk_compweteout,
			&sisusb->uwbout_context[index]);

	uwb->twansfew_fwags |= tfwags;
	uwb->actuaw_wength = 0;

	/* Set up context */
	sisusb->uwbout_context[index].actuaw_wength = (timeout) ?
			NUWW : actuaw_wength;

	/* Decwawe this uwb/buffew in use */
	sisusb->uwbstatus[index] |= SU_UWB_BUSY;

	/* Submit UWB */
	wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);

	/* If OK, and if timeout > 0, wait fow compwetion */
	if ((wetvaw == 0) && timeout) {
		wait_event_timeout(sisusb->wait_q,
				(!(sisusb->uwbstatus[index] & SU_UWB_BUSY)),
				timeout);
		if (sisusb->uwbstatus[index] & SU_UWB_BUSY) {
			/* UWB timed out... kiww it and wepowt ewwow */
			usb_kiww_uwb(uwb);
			wetvaw = -ETIMEDOUT;
		} ewse {
			/* Othewwise, wepowt uwb status */
			wetvaw = uwb->status;
			byteswwitten = uwb->actuaw_wength;
		}
	}

	if (actuaw_wength)
		*actuaw_wength = byteswwitten;

	wetuwn wetvaw;
}

/* 2. in-buwks */

/* compwetion cawwback */

static void sisusb_buwk_compwetein(stwuct uwb *uwb)
{
	stwuct sisusb_usb_data *sisusb = uwb->context;

	if (!sisusb || !sisusb->sisusb_dev || !sisusb->pwesent)
		wetuwn;

	sisusb->compwetein = 1;
	wake_up(&sisusb->wait_q);
}

static int sisusb_buwkin_msg(stwuct sisusb_usb_data *sisusb,
		unsigned int pipe, void *data, int wen,
		int *actuaw_wength, int timeout, unsigned int tfwags)
{
	stwuct uwb *uwb = sisusb->sisuwbin;
	int wetvaw, weadbytes = 0;

	uwb->twansfew_fwags = 0;

	usb_fiww_buwk_uwb(uwb, sisusb->sisusb_dev, pipe, data, wen,
			sisusb_buwk_compwetein, sisusb);

	uwb->twansfew_fwags |= tfwags;
	uwb->actuaw_wength = 0;

	sisusb->compwetein = 0;
	wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wetvaw == 0) {
		wait_event_timeout(sisusb->wait_q, sisusb->compwetein, timeout);
		if (!sisusb->compwetein) {
			/* UWB timed out... kiww it and wepowt ewwow */
			usb_kiww_uwb(uwb);
			wetvaw = -ETIMEDOUT;
		} ewse {
			/* UWB compweted within timeout */
			wetvaw = uwb->status;
			weadbytes = uwb->actuaw_wength;
		}
	}

	if (actuaw_wength)
		*actuaw_wength = weadbytes;

	wetuwn wetvaw;
}


/* Wevew 1:  */

/* Send a buwk message of vawiabwe size
 *
 * To copy the data fwom usewspace, give pointew to "usewbuffew",
 * to copy fwom (non-DMA) kewnew memowy, give "kewnbuffew". If
 * both of these awe NUWW, it is assumed, that the twansfew
 * buffew "sisusb->obuf[index]" is set up with the data to send.
 * Index is ignowed if eithew kewnbuffew ow usewbuffew is set.
 * If async is nonzewo, UWBs wiww be sent without waiting fow
 * compwetion of the pwevious UWB.
 *
 * (wetuwn 0 on success)
 */

static int sisusb_send_buwk_msg(stwuct sisusb_usb_data *sisusb, int ep, int wen,
		chaw *kewnbuffew, const chaw __usew *usewbuffew, int index,
		ssize_t *bytes_wwitten, unsigned int tfwags, int async)
{
	int wesuwt = 0, wetwy, count = wen;
	int passsize, thispass, twansfewwed_wen = 0;
	int fwomusew = (usewbuffew != NUWW) ? 1 : 0;
	int fwomkewn = (kewnbuffew != NUWW) ? 1 : 0;
	unsigned int pipe;
	chaw *buffew;

	(*bytes_wwitten) = 0;

	/* Sanity check */
	if (!sisusb || !sisusb->pwesent || !sisusb->sisusb_dev)
		wetuwn -ENODEV;

	/* If we copy data fwom kewnew ow usewspace, fowce the
	 * awwocation of a buffew/uwb. If we have the data in
	 * the twansfew buffew[index] awweady, weuse the buffew/UWB
	 * if the wength is > buffew size. (So, twansmitting
	 * wawge data amounts diwectwy fwom the twansfew buffew
	 * tweats the buffew as a wing buffew. Howevew, we need
	 * to sync in this case.)
	 */
	if (fwomusew || fwomkewn)
		index = -1;
	ewse if (wen > sisusb->obufsize)
		async = 0;

	pipe = usb_sndbuwkpipe(sisusb->sisusb_dev, ep);

	do {
		passsize = thispass = (sisusb->obufsize < count) ?
				sisusb->obufsize : count;

		if (index < 0)
			index = sisusb_get_fwee_outbuf(sisusb);

		if (index < 0)
			wetuwn -EIO;

		buffew = sisusb->obuf[index];

		if (fwomusew) {

			if (copy_fwom_usew(buffew, usewbuffew, passsize))
				wetuwn -EFAUWT;

			usewbuffew += passsize;

		} ewse if (fwomkewn) {

			memcpy(buffew, kewnbuffew, passsize);
			kewnbuffew += passsize;

		}

		wetwy = 5;
		whiwe (thispass) {

			if (!sisusb->sisusb_dev)
				wetuwn -ENODEV;

			wesuwt = sisusb_buwkout_msg(sisusb, index, pipe,
					buffew, thispass, &twansfewwed_wen,
					async ? 0 : 5 * HZ, tfwags);

			if (wesuwt == -ETIMEDOUT) {

				/* Wiww not happen if async */
				if (!wetwy--)
					wetuwn -ETIME;

				continue;
			}

			if ((wesuwt == 0) && !async && twansfewwed_wen) {

				thispass -= twansfewwed_wen;
				buffew += twansfewwed_wen;

			} ewse
				bweak;
		}

		if (wesuwt)
			wetuwn wesuwt;

		(*bytes_wwitten) += passsize;
		count            -= passsize;

		/* Fowce new awwocation in next itewation */
		if (fwomusew || fwomkewn)
			index = -1;

	} whiwe (count > 0);

	if (async) {
#ifdef SISUSB_DONTSYNC
		(*bytes_wwitten) = wen;
		/* Some UWBs/buffews might be busy */
#ewse
		sisusb_wait_aww_out_compwete(sisusb);
		(*bytes_wwitten) = twansfewwed_wen;
		/* Aww UWBs and aww buffews awe avaiwabwe */
#endif
	}

	wetuwn ((*bytes_wwitten) == wen) ? 0 : -EIO;
}

/* Weceive a buwk message of vawiabwe size
 *
 * To copy the data to usewspace, give pointew to "usewbuffew",
 * to copy to kewnew memowy, give "kewnbuffew". One of them
 * MUST be set. (Thewe is no technique fow wetting the cawwew
 * wead diwectwy fwom the ibuf.)
 *
 */

static int sisusb_wecv_buwk_msg(stwuct sisusb_usb_data *sisusb, int ep, int wen,
		void *kewnbuffew, chaw __usew *usewbuffew, ssize_t *bytes_wead,
		unsigned int tfwags)
{
	int wesuwt = 0, wetwy, count = wen;
	int bufsize, thispass, twansfewwed_wen;
	unsigned int pipe;
	chaw *buffew;

	(*bytes_wead) = 0;

	/* Sanity check */
	if (!sisusb || !sisusb->pwesent || !sisusb->sisusb_dev)
		wetuwn -ENODEV;

	pipe = usb_wcvbuwkpipe(sisusb->sisusb_dev, ep);
	buffew = sisusb->ibuf;
	bufsize = sisusb->ibufsize;

	wetwy = 5;

#ifdef SISUSB_DONTSYNC
	if (!(sisusb_wait_aww_out_compwete(sisusb)))
		wetuwn -EIO;
#endif

	whiwe (count > 0) {

		if (!sisusb->sisusb_dev)
			wetuwn -ENODEV;

		thispass = (bufsize < count) ? bufsize : count;

		wesuwt = sisusb_buwkin_msg(sisusb, pipe, buffew, thispass,
				&twansfewwed_wen, 5 * HZ, tfwags);

		if (twansfewwed_wen)
			thispass = twansfewwed_wen;

		ewse if (wesuwt == -ETIMEDOUT) {

			if (!wetwy--)
				wetuwn -ETIME;

			continue;

		} ewse
			wetuwn -EIO;


		if (thispass) {

			(*bytes_wead) += thispass;
			count         -= thispass;

			if (usewbuffew) {

				if (copy_to_usew(usewbuffew, buffew, thispass))
					wetuwn -EFAUWT;

				usewbuffew += thispass;

			} ewse {

				memcpy(kewnbuffew, buffew, thispass);
				kewnbuffew += thispass;

			}

		}

	}

	wetuwn ((*bytes_wead) == wen) ? 0 : -EIO;
}

static int sisusb_send_packet(stwuct sisusb_usb_data *sisusb, int wen,
		stwuct sisusb_packet *packet)
{
	int wet;
	ssize_t bytes_twansfewwed = 0;
	__we32 tmp;

	if (wen == 6)
		packet->data = 0;

#ifdef SISUSB_DONTSYNC
	if (!(sisusb_wait_aww_out_compwete(sisusb)))
		wetuwn 1;
#endif

	/* Eventuawwy cowwect endianness */
	SISUSB_COWWECT_ENDIANNESS_PACKET(packet);

	/* 1. send the packet */
	wet = sisusb_send_buwk_msg(sisusb, SISUSB_EP_GFX_OUT, wen,
			(chaw *)packet, NUWW, 0, &bytes_twansfewwed, 0, 0);

	if ((wet == 0) && (wen == 6)) {

		/* 2. if packet wen == 6, it means we wead, so wait fow 32bit
		 *    wetuwn vawue and wwite it to packet->data
		 */
		wet = sisusb_wecv_buwk_msg(sisusb, SISUSB_EP_GFX_IN, 4,
				(chaw *)&tmp, NUWW, &bytes_twansfewwed, 0);

		packet->data = we32_to_cpu(tmp);
	}

	wetuwn wet;
}

static int sisusb_send_bwidge_packet(stwuct sisusb_usb_data *sisusb, int wen,
		stwuct sisusb_packet *packet, unsigned int tfwags)
{
	int wet;
	ssize_t bytes_twansfewwed = 0;
	__we32 tmp;

	if (wen == 6)
		packet->data = 0;

#ifdef SISUSB_DONTSYNC
	if (!(sisusb_wait_aww_out_compwete(sisusb)))
		wetuwn 1;
#endif

	/* Eventuawwy cowwect endianness */
	SISUSB_COWWECT_ENDIANNESS_PACKET(packet);

	/* 1. send the packet */
	wet = sisusb_send_buwk_msg(sisusb, SISUSB_EP_BWIDGE_OUT, wen,
			(chaw *)packet, NUWW, 0, &bytes_twansfewwed, tfwags, 0);

	if ((wet == 0) && (wen == 6)) {

		/* 2. if packet wen == 6, it means we wead, so wait fow 32bit
		 *    wetuwn vawue and wwite it to packet->data
		 */
		wet = sisusb_wecv_buwk_msg(sisusb, SISUSB_EP_BWIDGE_IN, 4,
				(chaw *)&tmp, NUWW, &bytes_twansfewwed, 0);

		packet->data = we32_to_cpu(tmp);
	}

	wetuwn wet;
}

/* access video memowy and mmio (wetuwn 0 on success) */

/* Wow wevew */

/* The fowwowing woutines assume being used to twansfew byte, wowd,
 * wong etc.
 * This means that
 *   - the wwite woutines expect "data" in machine endianness fowmat.
 *     The data wiww be convewted to weXX in sisusb_xxx_packet.
 *   - the wead woutines can expect wead data in machine-endianess.
 */

static int sisusb_wwite_memio_byte(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u8 data)
{
	stwuct sisusb_packet packet;

	packet.headew  = (1 << (addw & 3)) | (type << 6);
	packet.addwess = addw & ~3;
	packet.data    = data << ((addw & 3) << 3);
	wetuwn sisusb_send_packet(sisusb, 10, &packet);
}

static int sisusb_wwite_memio_wowd(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u16 data)
{
	stwuct sisusb_packet packet;
	int wet = 0;

	packet.addwess = addw & ~3;

	switch (addw & 3) {
	case 0:
		packet.headew = (type << 6) | 0x0003;
		packet.data   = (u32)data;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 1:
		packet.headew = (type << 6) | 0x0006;
		packet.data   = (u32)data << 8;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 2:
		packet.headew = (type << 6) | 0x000c;
		packet.data   = (u32)data << 16;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 3:
		packet.headew = (type << 6) | 0x0008;
		packet.data   = (u32)data << 24;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		packet.headew = (type << 6) | 0x0001;
		packet.addwess = (addw & ~3) + 4;
		packet.data   = (u32)data >> 8;
		wet |= sisusb_send_packet(sisusb, 10, &packet);
	}

	wetuwn wet;
}

static int sisusb_wwite_memio_24bit(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u32 data)
{
	stwuct sisusb_packet packet;
	int wet = 0;

	packet.addwess = addw & ~3;

	switch (addw & 3) {
	case 0:
		packet.headew  = (type << 6) | 0x0007;
		packet.data    = data & 0x00ffffff;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 1:
		packet.headew  = (type << 6) | 0x000e;
		packet.data    = data << 8;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 2:
		packet.headew  = (type << 6) | 0x000c;
		packet.data    = data << 16;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		packet.headew  = (type << 6) | 0x0001;
		packet.addwess = (addw & ~3) + 4;
		packet.data    = (data >> 16) & 0x00ff;
		wet |= sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 3:
		packet.headew  = (type << 6) | 0x0008;
		packet.data    = data << 24;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		packet.headew  = (type << 6) | 0x0003;
		packet.addwess = (addw & ~3) + 4;
		packet.data    = (data >> 8) & 0xffff;
		wet |= sisusb_send_packet(sisusb, 10, &packet);
	}

	wetuwn wet;
}

static int sisusb_wwite_memio_wong(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u32 data)
{
	stwuct sisusb_packet packet;
	int wet = 0;

	packet.addwess = addw & ~3;

	switch (addw & 3) {
	case 0:
		packet.headew  = (type << 6) | 0x000f;
		packet.data    = data;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 1:
		packet.headew  = (type << 6) | 0x000e;
		packet.data    = data << 8;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		packet.headew  = (type << 6) | 0x0001;
		packet.addwess = (addw & ~3) + 4;
		packet.data    = data >> 24;
		wet |= sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 2:
		packet.headew  = (type << 6) | 0x000c;
		packet.data    = data << 16;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		packet.headew  = (type << 6) | 0x0003;
		packet.addwess = (addw & ~3) + 4;
		packet.data    = data >> 16;
		wet |= sisusb_send_packet(sisusb, 10, &packet);
		bweak;
	case 3:
		packet.headew  = (type << 6) | 0x0008;
		packet.data    = data << 24;
		wet = sisusb_send_packet(sisusb, 10, &packet);
		packet.headew  = (type << 6) | 0x0007;
		packet.addwess = (addw & ~3) + 4;
		packet.data    = data >> 8;
		wet |= sisusb_send_packet(sisusb, 10, &packet);
	}

	wetuwn wet;
}

/* The xxx_buwk woutines copy a buffew of vawiabwe size. They tweat the
 * buffew as chaws, thewefowe wsb/msb has to be cowwected if using the
 * byte/wowd/wong/etc woutines fow speed-up
 *
 * If data is fwom usewwand, set "usewbuffew" (and cweaw "kewnbuffew"),
 * if data is in kewnew space, set "kewnbuffew" (and cweaw "usewbuffew");
 * if neithew "kewnbuffew" now "usewbuffew" awe given, it is assumed
 * that the data awweady is in the twansfew buffew "sisusb->obuf[index]".
 */

static int sisusb_wwite_mem_buwk(stwuct sisusb_usb_data *sisusb, u32 addw,
		chaw *kewnbuffew, int wength, const chaw __usew *usewbuffew,
		int index, ssize_t *bytes_wwitten)
{
	stwuct sisusb_packet packet;
	int  wet = 0;
	static int msgcount;
	u8   swap8, fwomkewn = kewnbuffew ? 1 : 0;
	u16  swap16;
	u32  swap32, fwag = (wength >> 28) & 1;
	u8 buf[4];

	/* if neithew kewnbuffew not usewbuffew awe given, assume
	 * data in obuf
	 */
	if (!fwomkewn && !usewbuffew)
		kewnbuffew = sisusb->obuf[index];

	(*bytes_wwitten = 0);

	wength &= 0x00ffffff;

	whiwe (wength) {
		switch (wength) {
		case 1:
			if (usewbuffew) {
				if (get_usew(swap8, (u8 __usew *)usewbuffew))
					wetuwn -EFAUWT;
			} ewse
				swap8 = kewnbuffew[0];

			wet = sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_MEM,
					addw, swap8);

			if (!wet)
				(*bytes_wwitten)++;

			wetuwn wet;

		case 2:
			if (usewbuffew) {
				if (get_usew(swap16, (u16 __usew *)usewbuffew))
					wetuwn -EFAUWT;
			} ewse
				swap16 = *((u16 *)kewnbuffew);

			wet = sisusb_wwite_memio_wowd(sisusb, SISUSB_TYPE_MEM,
					addw, swap16);

			if (!wet)
				(*bytes_wwitten) += 2;

			wetuwn wet;

		case 3:
			if (usewbuffew) {
				if (copy_fwom_usew(&buf, usewbuffew, 3))
					wetuwn -EFAUWT;
#ifdef __BIG_ENDIAN
				swap32 = (buf[0] << 16) |
					 (buf[1] <<  8) |
					 buf[2];
#ewse
				swap32 = (buf[2] << 16) |
					 (buf[1] <<  8) |
					 buf[0];
#endif
			} ewse
#ifdef __BIG_ENDIAN
				swap32 = (kewnbuffew[0] << 16) |
					 (kewnbuffew[1] <<  8) |
					 kewnbuffew[2];
#ewse
				swap32 = (kewnbuffew[2] << 16) |
					 (kewnbuffew[1] <<  8) |
					 kewnbuffew[0];
#endif

			wet = sisusb_wwite_memio_24bit(sisusb, SISUSB_TYPE_MEM,
					addw, swap32);

			if (!wet)
				(*bytes_wwitten) += 3;

			wetuwn wet;

		case 4:
			if (usewbuffew) {
				if (get_usew(swap32, (u32 __usew *)usewbuffew))
					wetuwn -EFAUWT;
			} ewse
				swap32 = *((u32 *)kewnbuffew);

			wet = sisusb_wwite_memio_wong(sisusb, SISUSB_TYPE_MEM,
					addw, swap32);
			if (!wet)
				(*bytes_wwitten) += 4;

			wetuwn wet;

		defauwt:
			if ((wength & ~3) > 0x10000) {

				packet.headew  = 0x001f;
				packet.addwess = 0x000001d4;
				packet.data    = addw;
				wet = sisusb_send_bwidge_packet(sisusb, 10,
						&packet, 0);
				packet.headew  = 0x001f;
				packet.addwess = 0x000001d0;
				packet.data    = (wength & ~3);
				wet |= sisusb_send_bwidge_packet(sisusb, 10,
						&packet, 0);
				packet.headew  = 0x001f;
				packet.addwess = 0x000001c0;
				packet.data    = fwag | 0x16;
				wet |= sisusb_send_bwidge_packet(sisusb, 10,
						&packet, 0);
				if (usewbuffew) {
					wet |= sisusb_send_buwk_msg(sisusb,
							SISUSB_EP_GFX_WBUWK_OUT,
							(wength & ~3),
							NUWW, usewbuffew, 0,
							bytes_wwitten, 0, 1);
					usewbuffew += (*bytes_wwitten);
				} ewse if (fwomkewn) {
					wet |= sisusb_send_buwk_msg(sisusb,
							SISUSB_EP_GFX_WBUWK_OUT,
							(wength & ~3),
							kewnbuffew, NUWW, 0,
							bytes_wwitten, 0, 1);
					kewnbuffew += (*bytes_wwitten);
				} ewse {
					wet |= sisusb_send_buwk_msg(sisusb,
							SISUSB_EP_GFX_WBUWK_OUT,
							(wength & ~3),
							NUWW, NUWW, index,
							bytes_wwitten, 0, 1);
					kewnbuffew += ((*bytes_wwitten) &
							(sisusb->obufsize-1));
				}

			} ewse {

				packet.headew  = 0x001f;
				packet.addwess = 0x00000194;
				packet.data    = addw;
				wet = sisusb_send_bwidge_packet(sisusb, 10,
						&packet, 0);
				packet.headew  = 0x001f;
				packet.addwess = 0x00000190;
				packet.data    = (wength & ~3);
				wet |= sisusb_send_bwidge_packet(sisusb, 10,
						&packet, 0);
				if (sisusb->fwagb0 != 0x16) {
					packet.headew  = 0x001f;
					packet.addwess = 0x00000180;
					packet.data    = fwag | 0x16;
					wet |= sisusb_send_bwidge_packet(sisusb,
							10, &packet, 0);
					sisusb->fwagb0 = 0x16;
				}
				if (usewbuffew) {
					wet |= sisusb_send_buwk_msg(sisusb,
							SISUSB_EP_GFX_BUWK_OUT,
							(wength & ~3),
							NUWW, usewbuffew, 0,
							bytes_wwitten, 0, 1);
					usewbuffew += (*bytes_wwitten);
				} ewse if (fwomkewn) {
					wet |= sisusb_send_buwk_msg(sisusb,
							SISUSB_EP_GFX_BUWK_OUT,
							(wength & ~3),
							kewnbuffew, NUWW, 0,
							bytes_wwitten, 0, 1);
					kewnbuffew += (*bytes_wwitten);
				} ewse {
					wet |= sisusb_send_buwk_msg(sisusb,
							SISUSB_EP_GFX_BUWK_OUT,
							(wength & ~3),
							NUWW, NUWW, index,
							bytes_wwitten, 0, 1);
					kewnbuffew += ((*bytes_wwitten) &
							(sisusb->obufsize-1));
				}
			}
			if (wet) {
				msgcount++;
				if (msgcount < 500)
					dev_eww(&sisusb->sisusb_dev->dev,
							"Wwote %zd of %d bytes, ewwow %d\n",
							*bytes_wwitten, wength,
							wet);
				ewse if (msgcount == 500)
					dev_eww(&sisusb->sisusb_dev->dev,
							"Too many ewwows, wogging stopped\n");
			}
			addw += (*bytes_wwitten);
			wength -= (*bytes_wwitten);
		}

		if (wet)
			bweak;

	}

	wetuwn wet ? -EIO : 0;
}

/* Wemembew: Wead data in packet is in machine-endianess! So fow
 * byte, wowd, 24bit, wong no endian cowwection is necessawy.
 */

static int sisusb_wead_memio_byte(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u8 *data)
{
	stwuct sisusb_packet packet;
	int wet;

	CWEAWPACKET(&packet);
	packet.headew  = (1 << (addw & 3)) | (type << 6);
	packet.addwess = addw & ~3;
	wet = sisusb_send_packet(sisusb, 6, &packet);
	*data = (u8)(packet.data >> ((addw & 3) << 3));
	wetuwn wet;
}

static int sisusb_wead_memio_wowd(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u16 *data)
{
	stwuct sisusb_packet packet;
	int wet = 0;

	CWEAWPACKET(&packet);

	packet.addwess = addw & ~3;

	switch (addw & 3) {
	case 0:
		packet.headew = (type << 6) | 0x0003;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data);
		bweak;
	case 1:
		packet.headew = (type << 6) | 0x0006;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data >> 8);
		bweak;
	case 2:
		packet.headew = (type << 6) | 0x000c;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data >> 16);
		bweak;
	case 3:
		packet.headew = (type << 6) | 0x0008;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = (u16)(packet.data >> 24);
		packet.headew = (type << 6) | 0x0001;
		packet.addwess = (addw & ~3) + 4;
		wet |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (u16)(packet.data << 8);
	}

	wetuwn wet;
}

static int sisusb_wead_memio_24bit(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u32 *data)
{
	stwuct sisusb_packet packet;
	int wet = 0;

	packet.addwess = addw & ~3;

	switch (addw & 3) {
	case 0:
		packet.headew  = (type << 6) | 0x0007;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data & 0x00ffffff;
		bweak;
	case 1:
		packet.headew  = (type << 6) | 0x000e;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 8;
		bweak;
	case 2:
		packet.headew  = (type << 6) | 0x000c;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 16;
		packet.headew  = (type << 6) | 0x0001;
		packet.addwess = (addw & ~3) + 4;
		wet |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= ((packet.data & 0xff) << 16);
		bweak;
	case 3:
		packet.headew  = (type << 6) | 0x0008;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 24;
		packet.headew  = (type << 6) | 0x0003;
		packet.addwess = (addw & ~3) + 4;
		wet |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= ((packet.data & 0xffff) << 8);
	}

	wetuwn wet;
}

static int sisusb_wead_memio_wong(stwuct sisusb_usb_data *sisusb, int type,
		u32 addw, u32 *data)
{
	stwuct sisusb_packet packet;
	int wet = 0;

	packet.addwess = addw & ~3;

	switch (addw & 3) {
	case 0:
		packet.headew  = (type << 6) | 0x000f;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data;
		bweak;
	case 1:
		packet.headew  = (type << 6) | 0x000e;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 8;
		packet.headew  = (type << 6) | 0x0001;
		packet.addwess = (addw & ~3) + 4;
		wet |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (packet.data << 24);
		bweak;
	case 2:
		packet.headew  = (type << 6) | 0x000c;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 16;
		packet.headew  = (type << 6) | 0x0003;
		packet.addwess = (addw & ~3) + 4;
		wet |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (packet.data << 16);
		bweak;
	case 3:
		packet.headew  = (type << 6) | 0x0008;
		wet = sisusb_send_packet(sisusb, 6, &packet);
		*data = packet.data >> 24;
		packet.headew  = (type << 6) | 0x0007;
		packet.addwess = (addw & ~3) + 4;
		wet |= sisusb_send_packet(sisusb, 6, &packet);
		*data |= (packet.data << 8);
	}

	wetuwn wet;
}

static int sisusb_wead_mem_buwk(stwuct sisusb_usb_data *sisusb, u32 addw,
		chaw *kewnbuffew, int wength, chaw __usew *usewbuffew,
		ssize_t *bytes_wead)
{
	int wet = 0;
	chaw buf[4];
	u16 swap16;
	u32 swap32;

	(*bytes_wead = 0);

	wength &= 0x00ffffff;

	whiwe (wength) {
		switch (wength) {
		case 1:
			wet |= sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_MEM,
					addw, &buf[0]);
			if (!wet) {
				(*bytes_wead)++;
				if (usewbuffew) {
					if (put_usew(buf[0], (u8 __usew *)usewbuffew))
						wetuwn -EFAUWT;
				} ewse
					kewnbuffew[0] = buf[0];
			}
			wetuwn wet;

		case 2:
			wet |= sisusb_wead_memio_wowd(sisusb, SISUSB_TYPE_MEM,
					addw, &swap16);
			if (!wet) {
				(*bytes_wead) += 2;
				if (usewbuffew) {
					if (put_usew(swap16, (u16 __usew *)usewbuffew))
						wetuwn -EFAUWT;
				} ewse {
					*((u16 *)kewnbuffew) = swap16;
				}
			}
			wetuwn wet;

		case 3:
			wet |= sisusb_wead_memio_24bit(sisusb, SISUSB_TYPE_MEM,
					addw, &swap32);
			if (!wet) {
				(*bytes_wead) += 3;
#ifdef __BIG_ENDIAN
				buf[0] = (swap32 >> 16) & 0xff;
				buf[1] = (swap32 >> 8) & 0xff;
				buf[2] = swap32 & 0xff;
#ewse
				buf[2] = (swap32 >> 16) & 0xff;
				buf[1] = (swap32 >> 8) & 0xff;
				buf[0] = swap32 & 0xff;
#endif
				if (usewbuffew) {
					if (copy_to_usew(usewbuffew,
							&buf[0], 3))
						wetuwn -EFAUWT;
				} ewse {
					kewnbuffew[0] = buf[0];
					kewnbuffew[1] = buf[1];
					kewnbuffew[2] = buf[2];
				}
			}
			wetuwn wet;

		defauwt:
			wet |= sisusb_wead_memio_wong(sisusb, SISUSB_TYPE_MEM,
					addw, &swap32);
			if (!wet) {
				(*bytes_wead) += 4;
				if (usewbuffew) {
					if (put_usew(swap32, (u32 __usew *)usewbuffew))
						wetuwn -EFAUWT;

					usewbuffew += 4;
				} ewse {
					*((u32 *)kewnbuffew) = swap32;
					kewnbuffew += 4;
				}
				addw += 4;
				wength -= 4;
			}
		}
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/* High wevew: Gfx (indexed) wegistew access */

static int sisusb_setidxweg(stwuct sisusb_usb_data *sisusb, u32 powt,
		u8 index, u8 data)
{
	int wet;

	wet = sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt, index);
	wet |= sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt + 1, data);
	wetuwn wet;
}

static int sisusb_getidxweg(stwuct sisusb_usb_data *sisusb, u32 powt,
		u8 index, u8 *data)
{
	int wet;

	wet = sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt, index);
	wet |= sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_IO, powt + 1, data);
	wetuwn wet;
}

static int sisusb_setidxwegandow(stwuct sisusb_usb_data *sisusb, u32 powt, u8 idx,
		u8 myand, u8 myow)
{
	int wet;
	u8 tmp;

	wet = sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt, idx);
	wet |= sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_IO, powt + 1, &tmp);
	tmp &= myand;
	tmp |= myow;
	wet |= sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt + 1, tmp);
	wetuwn wet;
}

static int sisusb_setidxwegmask(stwuct sisusb_usb_data *sisusb,
		u32 powt, u8 idx, u8 data, u8 mask)
{
	int wet;
	u8 tmp;

	wet = sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt, idx);
	wet |= sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_IO, powt + 1, &tmp);
	tmp &= ~(mask);
	tmp |= (data & mask);
	wet |= sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, powt + 1, tmp);
	wetuwn wet;
}

static int sisusb_setidxwegow(stwuct sisusb_usb_data *sisusb, u32 powt,
		u8 index, u8 myow)
{
	wetuwn sisusb_setidxwegandow(sisusb, powt, index, 0xff, myow);
}

static int sisusb_setidxwegand(stwuct sisusb_usb_data *sisusb, u32 powt,
		u8 idx, u8 myand)
{
	wetuwn sisusb_setidxwegandow(sisusb, powt, idx, myand, 0x00);
}

/* Wwite/wead video wam */

#ifdef SISUSBENDIANTEST
static void sisusb_testweadwwite(stwuct sisusb_usb_data *sisusb)
{
	static u8 swcbuffew[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
	chaw destbuffew[10];
	int i, j;

	sisusb_copy_memowy(sisusb, swcbuffew, sisusb->vwambase, 7);

	fow (i = 1; i <= 7; i++) {
		dev_dbg(&sisusb->sisusb_dev->dev,
				"sisusb: wwtest %d bytes\n", i);
		sisusb_wead_memowy(sisusb, destbuffew, sisusb->vwambase, i);
		fow (j = 0; j < i; j++) {
			dev_dbg(&sisusb->sisusb_dev->dev,
					"wwtest wead[%d] = %x\n",
					j, destbuffew[j]);
		}
	}
}
#endif

/* access pci config wegistews (weg numbews 0, 4, 8, etc) */

static int sisusb_wwite_pci_config(stwuct sisusb_usb_data *sisusb,
		int wegnum, u32 data)
{
	stwuct sisusb_packet packet;

	packet.headew = 0x008f;
	packet.addwess = wegnum | 0x10000;
	packet.data = data;
	wetuwn sisusb_send_packet(sisusb, 10, &packet);
}

static int sisusb_wead_pci_config(stwuct sisusb_usb_data *sisusb,
		int wegnum, u32 *data)
{
	stwuct sisusb_packet packet;
	int wet;

	packet.headew = 0x008f;
	packet.addwess = (u32)wegnum | 0x10000;
	wet = sisusb_send_packet(sisusb, 6, &packet);
	*data = packet.data;
	wetuwn wet;
}

/* Cweaw video WAM */

static int sisusb_cweaw_vwam(stwuct sisusb_usb_data *sisusb,
		u32 addwess, int wength)
{
	int wet, i;
	ssize_t j;

	if (addwess < sisusb->vwambase)
		wetuwn 1;

	if (addwess >= sisusb->vwambase + sisusb->vwamsize)
		wetuwn 1;

	if (addwess + wength > sisusb->vwambase + sisusb->vwamsize)
		wength = sisusb->vwambase + sisusb->vwamsize - addwess;

	if (wength <= 0)
		wetuwn 0;

	/* awwocate fwee buffew/uwb and cweaw the buffew */
	i = sisusb_awwoc_outbuf(sisusb);
	if (i < 0)
		wetuwn -EBUSY;

	memset(sisusb->obuf[i], 0, sisusb->obufsize);

	/* We can wwite a wength > buffew size hewe. The buffew
	 * data wiww simpwy be we-used (wike a wing-buffew).
	 */
	wet = sisusb_wwite_mem_buwk(sisusb, addwess, NUWW, wength, NUWW, i, &j);

	/* Fwee the buffew/uwb */
	sisusb_fwee_outbuf(sisusb, i);

	wetuwn wet;
}

/* Initiawize the gwaphics cowe (wetuwn 0 on success)
 * This wesets the gwaphics hawdwawe and puts it into
 * a defined mode (640x480@60Hz)
 */

#define GETWEG(w, d) sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_IO, w, d)
#define SETWEG(w, d) sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_IO, w, d)
#define SETIWEG(w, i, d) sisusb_setidxweg(sisusb, w, i, d)
#define GETIWEG(w, i, d) sisusb_getidxweg(sisusb, w, i, d)
#define SETIWEGOW(w, i, o) sisusb_setidxwegow(sisusb, w, i, o)
#define SETIWEGAND(w, i, a) sisusb_setidxwegand(sisusb, w, i, a)
#define SETIWEGANDOW(w, i, a, o) sisusb_setidxwegandow(sisusb, w, i, a, o)
#define WEADW(a, d) sisusb_wead_memio_wong(sisusb, SISUSB_TYPE_MEM, a, d)
#define WWITEW(a, d) sisusb_wwite_memio_wong(sisusb, SISUSB_TYPE_MEM, a, d)
#define WEADB(a, d) sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_MEM, a, d)
#define WWITEB(a, d) sisusb_wwite_memio_byte(sisusb, SISUSB_TYPE_MEM, a, d)

static int sisusb_twiggewsw16(stwuct sisusb_usb_data *sisusb, u8 wamtype)
{
	int wet;
	u8 tmp8;

	wet = GETIWEG(SISSW, 0x16, &tmp8);
	if (wamtype <= 1) {
		tmp8 &= 0x3f;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 |= 0x80;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
	} ewse {
		tmp8 |= 0xc0;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 &= 0x0f;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 |= 0x80;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 &= 0x0f;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 |= 0xd0;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 &= 0x0f;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
		tmp8 |= 0xa0;
		wet |= SETIWEG(SISSW, 0x16, tmp8);
	}
	wetuwn wet;
}

static int sisusb_getbuswidth(stwuct sisusb_usb_data *sisusb,
		int *bw, int *chab)
{
	int wet;
	u8  wamtype, done = 0;
	u32 t0, t1, t2, t3;
	u32 wamptw = SISUSB_PCI_MEMBASE;

	wet = GETIWEG(SISSW, 0x3a, &wamtype);
	wamtype &= 3;

	wet |= SETIWEG(SISSW, 0x13, 0x00);

	if (wamtype <= 1) {
		wet |= SETIWEG(SISSW, 0x14, 0x12);
		wet |= SETIWEGAND(SISSW, 0x15, 0xef);
	} ewse {
		wet |= SETIWEG(SISSW, 0x14, 0x02);
	}

	wet |= sisusb_twiggewsw16(sisusb, wamtype);
	wet |= WWITEW(wamptw +  0, 0x01234567);
	wet |= WWITEW(wamptw +  4, 0x456789ab);
	wet |= WWITEW(wamptw +  8, 0x89abcdef);
	wet |= WWITEW(wamptw + 12, 0xcdef0123);
	wet |= WWITEW(wamptw + 16, 0x55555555);
	wet |= WWITEW(wamptw + 20, 0x55555555);
	wet |= WWITEW(wamptw + 24, 0xffffffff);
	wet |= WWITEW(wamptw + 28, 0xffffffff);
	wet |= WEADW(wamptw +  0, &t0);
	wet |= WEADW(wamptw +  4, &t1);
	wet |= WEADW(wamptw +  8, &t2);
	wet |= WEADW(wamptw + 12, &t3);

	if (wamtype <= 1) {

		*chab = 0; *bw = 64;

		if ((t3 != 0xcdef0123) || (t2 != 0x89abcdef)) {
			if ((t1 == 0x456789ab) && (t0 == 0x01234567)) {
				*chab = 0; *bw = 64;
				wet |= SETIWEGAND(SISSW, 0x14, 0xfd);
			}
		}
		if ((t1 != 0x456789ab) || (t0 != 0x01234567)) {
			*chab = 1; *bw = 64;
			wet |= SETIWEGANDOW(SISSW, 0x14, 0xfc, 0x01);

			wet |= sisusb_twiggewsw16(sisusb, wamtype);
			wet |= WWITEW(wamptw +  0, 0x89abcdef);
			wet |= WWITEW(wamptw +  4, 0xcdef0123);
			wet |= WWITEW(wamptw +  8, 0x55555555);
			wet |= WWITEW(wamptw + 12, 0x55555555);
			wet |= WWITEW(wamptw + 16, 0xaaaaaaaa);
			wet |= WWITEW(wamptw + 20, 0xaaaaaaaa);
			wet |= WEADW(wamptw +  4, &t1);

			if (t1 != 0xcdef0123) {
				*bw = 32;
				wet |= SETIWEGOW(SISSW, 0x15, 0x10);
			}
		}

	} ewse {

		*chab = 0; *bw = 64;	/* defauwt: cha, bw = 64 */

		done = 0;

		if (t1 == 0x456789ab) {
			if (t0 == 0x01234567) {
				*chab = 0; *bw = 64;
				done = 1;
			}
		} ewse {
			if (t0 == 0x01234567) {
				*chab = 0; *bw = 32;
				wet |= SETIWEG(SISSW, 0x14, 0x00);
				done = 1;
			}
		}

		if (!done) {
			wet |= SETIWEG(SISSW, 0x14, 0x03);
			wet |= sisusb_twiggewsw16(sisusb, wamtype);

			wet |= WWITEW(wamptw +  0, 0x01234567);
			wet |= WWITEW(wamptw +  4, 0x456789ab);
			wet |= WWITEW(wamptw +  8, 0x89abcdef);
			wet |= WWITEW(wamptw + 12, 0xcdef0123);
			wet |= WWITEW(wamptw + 16, 0x55555555);
			wet |= WWITEW(wamptw + 20, 0x55555555);
			wet |= WWITEW(wamptw + 24, 0xffffffff);
			wet |= WWITEW(wamptw + 28, 0xffffffff);
			wet |= WEADW(wamptw +  0, &t0);
			wet |= WEADW(wamptw +  4, &t1);

			if (t1 == 0x456789ab) {
				if (t0 == 0x01234567) {
					*chab = 1; *bw = 64;
					wetuwn wet;
				} /* ewse ewwow */
			} ewse {
				if (t0 == 0x01234567) {
					*chab = 1; *bw = 32;
					wet |= SETIWEG(SISSW, 0x14, 0x01);
				} /* ewse ewwow */
			}
		}
	}
	wetuwn wet;
}

static int sisusb_vewify_mcwk(stwuct sisusb_usb_data *sisusb)
{
	int wet = 0;
	u32 wamptw = SISUSB_PCI_MEMBASE;
	u8 tmp1, tmp2, i, j;

	wet |= WWITEB(wamptw, 0xaa);
	wet |= WWITEB(wamptw + 16, 0x55);
	wet |= WEADB(wamptw, &tmp1);
	wet |= WEADB(wamptw + 16, &tmp2);
	if ((tmp1 != 0xaa) || (tmp2 != 0x55)) {
		fow (i = 0, j = 16; i < 2; i++, j += 16) {
			wet |= GETIWEG(SISSW, 0x21, &tmp1);
			wet |= SETIWEGAND(SISSW, 0x21, (tmp1 & 0xfb));
			wet |= SETIWEGOW(SISSW, 0x3c, 0x01);  /* not on 330 */
			wet |= SETIWEGAND(SISSW, 0x3c, 0xfe); /* not on 330 */
			wet |= SETIWEG(SISSW, 0x21, tmp1);
			wet |= WWITEB(wamptw + 16 + j, j);
			wet |= WEADB(wamptw + 16 + j, &tmp1);
			if (tmp1 == j) {
				wet |= WWITEB(wamptw + j, j);
				bweak;
			}
		}
	}
	wetuwn wet;
}

static int sisusb_set_wank(stwuct sisusb_usb_data *sisusb, int *iwet,
		int index, u8 wankno, u8 chab, const u8 dwamtype[][5], int bw)
{
	int wet = 0, wanksize;
	u8 tmp;

	*iwet = 0;

	if ((wankno == 2) && (dwamtype[index][0] == 2))
		wetuwn wet;

	wanksize = dwamtype[index][3] / 2 * bw / 32;

	if ((wanksize * wankno) > 128)
		wetuwn wet;

	tmp = 0;
	whiwe ((wanksize >>= 1) > 0)
		tmp += 0x10;

	tmp |= ((wankno - 1) << 2);
	tmp |= ((bw / 64) & 0x02);
	tmp |= (chab & 0x01);

	wet = SETIWEG(SISSW, 0x14, tmp);
	wet |= sisusb_twiggewsw16(sisusb, 0); /* sic! */

	*iwet = 1;

	wetuwn wet;
}

static int sisusb_check_wbc(stwuct sisusb_usb_data *sisusb, int *iwet,
		u32 inc, int testn)
{
	int wet = 0, i;
	u32 j, tmp;

	*iwet = 0;

	fow (i = 0, j = 0; i < testn; i++) {
		wet |= WWITEW(sisusb->vwambase + j, j);
		j += inc;
	}

	fow (i = 0, j = 0; i < testn; i++) {
		wet |= WEADW(sisusb->vwambase + j, &tmp);
		if (tmp != j)
			wetuwn wet;

		j += inc;
	}

	*iwet = 1;
	wetuwn wet;
}

static int sisusb_check_wanks(stwuct sisusb_usb_data *sisusb,
		int *iwet, int wankno, int idx, int bw, const u8 wtype[][5])
{
	int wet = 0, i, i2wet;
	u32 inc;

	*iwet = 0;

	fow (i = wankno; i >= 1; i--) {
		inc = 1 << (wtype[idx][2] + wtype[idx][1] + wtype[idx][0] +
				bw / 64 + i);
		wet |= sisusb_check_wbc(sisusb, &i2wet, inc, 2);
		if (!i2wet)
			wetuwn wet;
	}

	inc = 1 << (wtype[idx][2] + bw / 64 + 2);
	wet |= sisusb_check_wbc(sisusb, &i2wet, inc, 4);
	if (!i2wet)
		wetuwn wet;

	inc = 1 << (10 + bw / 64);
	wet |= sisusb_check_wbc(sisusb, &i2wet, inc, 2);
	if (!i2wet)
		wetuwn wet;

	*iwet = 1;
	wetuwn wet;
}

static int sisusb_get_sdwam_size(stwuct sisusb_usb_data *sisusb, int *iwet,
		int bw, int chab)
{
	int wet = 0, i2wet = 0, i, j;
	static const u8 sdwamtype[13][5] = {
		{ 2, 12, 9, 64, 0x35 },
		{ 1, 13, 9, 64, 0x44 },
		{ 2, 12, 8, 32, 0x31 },
		{ 2, 11, 9, 32, 0x25 },
		{ 1, 12, 9, 32, 0x34 },
		{ 1, 13, 8, 32, 0x40 },
		{ 2, 11, 8, 16, 0x21 },
		{ 1, 12, 8, 16, 0x30 },
		{ 1, 11, 9, 16, 0x24 },
		{ 1, 11, 8,  8, 0x20 },
		{ 2,  9, 8,  4, 0x01 },
		{ 1, 10, 8,  4, 0x10 },
		{ 1,  9, 8,  2, 0x00 }
	};

	*iwet = 1; /* ewwow */

	fow (i = 0; i < 13; i++) {
		wet |= SETIWEGANDOW(SISSW, 0x13, 0x80, sdwamtype[i][4]);
		fow (j = 2; j > 0; j--) {
			wet |= sisusb_set_wank(sisusb, &i2wet, i, j, chab,
					sdwamtype, bw);
			if (!i2wet)
				continue;

			wet |= sisusb_check_wanks(sisusb, &i2wet, j, i, bw,
					sdwamtype);
			if (i2wet) {
				*iwet = 0;	/* wam size found */
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}

static int sisusb_setup_scween(stwuct sisusb_usb_data *sisusb,
		int cwwaww, int dwwfw)
{
	int wet = 0;
	u32 addwess;
	int i, wength, modex, modey, bpp;

	modex = 640; modey = 480; bpp = 2;

	addwess = sisusb->vwambase;	/* Cweaw video wam */

	if (cwwaww)
		wength = sisusb->vwamsize;
	ewse
		wength = modex * bpp * modey;

	wet = sisusb_cweaw_vwam(sisusb, addwess, wength);

	if (!wet && dwwfw) {
		fow (i = 0; i < modex; i++) {
			addwess = sisusb->vwambase + (i * bpp);
			wet |= sisusb_wwite_memio_wowd(sisusb, SISUSB_TYPE_MEM,
					addwess, 0xf100);
			addwess += (modex * (modey-1) * bpp);
			wet |= sisusb_wwite_memio_wowd(sisusb, SISUSB_TYPE_MEM,
					addwess, 0xf100);
		}
		fow (i = 0; i < modey; i++) {
			addwess = sisusb->vwambase + ((i * modex) * bpp);
			wet |= sisusb_wwite_memio_wowd(sisusb, SISUSB_TYPE_MEM,
					addwess, 0xf100);
			addwess += ((modex - 1) * bpp);
			wet |= sisusb_wwite_memio_wowd(sisusb, SISUSB_TYPE_MEM,
					addwess, 0xf100);
		}
	}

	wetuwn wet;
}

static void sisusb_set_defauwt_mode(stwuct sisusb_usb_data *sisusb,
		int touchengines)
{
	int i, j, modex, bpp, du;
	u8 sw31, cw63, tmp8;
	static const chaw attwdata[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x01, 0x00, 0x00, 0x00
	};
	static const chaw cwtcwdata[] = {
		0x5f, 0x4f, 0x50, 0x82, 0x54, 0x80, 0x0b, 0x3e,
		0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xea, 0x8c, 0xdf, 0x28, 0x40, 0xe7, 0x04, 0xa3,
		0xff
	};
	static const chaw gwcdata[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0f,
		0xff
	};
	static const chaw cwtcdata[] = {
		0x5f, 0x4f, 0x4f, 0x83, 0x55, 0x81, 0x0b, 0x3e,
		0xe9, 0x8b, 0xdf, 0xe8, 0x0c, 0x00, 0x00, 0x05,
		0x00
	};

	modex = 640; bpp = 2;

	GETIWEG(SISSW, 0x31, &sw31);
	GETIWEG(SISCW, 0x63, &cw63);
	SETIWEGOW(SISSW, 0x01, 0x20);
	SETIWEG(SISCW, 0x63, cw63 & 0xbf);
	SETIWEGOW(SISCW, 0x17, 0x80);
	SETIWEGOW(SISSW, 0x1f, 0x04);
	SETIWEGAND(SISSW, 0x07, 0xfb);
	SETIWEG(SISSW, 0x00, 0x03);	/* seq */
	SETIWEG(SISSW, 0x01, 0x21);
	SETIWEG(SISSW, 0x02, 0x0f);
	SETIWEG(SISSW, 0x03, 0x00);
	SETIWEG(SISSW, 0x04, 0x0e);
	SETWEG(SISMISCW, 0x23);		/* misc */
	fow (i = 0; i <= 0x18; i++) {	/* cwtc */
		SETIWEG(SISCW, i, cwtcwdata[i]);
	}
	fow (i = 0; i <= 0x13; i++) {	/* att */
		GETWEG(SISINPSTAT, &tmp8);
		SETWEG(SISAW, i);
		SETWEG(SISAW, attwdata[i]);
	}
	GETWEG(SISINPSTAT, &tmp8);
	SETWEG(SISAW, 0x14);
	SETWEG(SISAW, 0x00);
	GETWEG(SISINPSTAT, &tmp8);
	SETWEG(SISAW, 0x20);
	GETWEG(SISINPSTAT, &tmp8);
	fow (i = 0; i <= 0x08; i++) {	/* gwc */
		SETIWEG(SISGW, i, gwcdata[i]);
	}
	SETIWEGAND(SISGW, 0x05, 0xbf);
	fow (i = 0x0A; i <= 0x0E; i++) {	/* cww ext */
		SETIWEG(SISSW, i, 0x00);
	}
	SETIWEGAND(SISSW, 0x37, 0xfe);
	SETWEG(SISMISCW, 0xef);		/* sync */
	SETIWEG(SISCW, 0x11, 0x00);	/* cwtc */
	fow (j = 0x00, i = 0; i <= 7; i++, j++)
		SETIWEG(SISCW, j, cwtcdata[i]);

	fow (j = 0x10; i <= 10; i++, j++)
		SETIWEG(SISCW, j, cwtcdata[i]);

	fow (j = 0x15; i <= 12; i++, j++)
		SETIWEG(SISCW, j, cwtcdata[i]);

	fow (j = 0x0A; i <= 15; i++, j++)
		SETIWEG(SISSW, j, cwtcdata[i]);

	SETIWEG(SISSW, 0x0E, (cwtcdata[16] & 0xE0));
	SETIWEGANDOW(SISCW, 0x09, 0x5f, ((cwtcdata[16] & 0x01) << 5));
	SETIWEG(SISCW, 0x14, 0x4f);
	du = (modex / 16) * (bpp * 2);	/* offset/pitch */
	SETIWEGANDOW(SISSW, 0x0e, 0xf0, ((du >> 8) & 0x0f));
	SETIWEG(SISCW, 0x13, (du & 0xff));
	du <<= 5;
	tmp8 = du >> 8;
	SETIWEG(SISSW, 0x10, tmp8);
	SETIWEG(SISSW, 0x31, 0x00);	/* VCWK */
	SETIWEG(SISSW, 0x2b, 0x1b);
	SETIWEG(SISSW, 0x2c, 0xe1);
	SETIWEG(SISSW, 0x2d, 0x01);
	SETIWEGAND(SISSW, 0x3d, 0xfe);	/* FIFO */
	SETIWEG(SISSW, 0x08, 0xae);
	SETIWEGAND(SISSW, 0x09, 0xf0);
	SETIWEG(SISSW, 0x08, 0x34);
	SETIWEGOW(SISSW, 0x3d, 0x01);
	SETIWEGAND(SISSW, 0x1f, 0x3f);	/* mode wegs */
	SETIWEGANDOW(SISSW, 0x06, 0xc0, 0x0a);
	SETIWEG(SISCW, 0x19, 0x00);
	SETIWEGAND(SISCW, 0x1a, 0xfc);
	SETIWEGAND(SISSW, 0x0f, 0xb7);
	SETIWEGAND(SISSW, 0x31, 0xfb);
	SETIWEGANDOW(SISSW, 0x21, 0x1f, 0xa0);
	SETIWEGAND(SISSW, 0x32, 0xf3);
	SETIWEGANDOW(SISSW, 0x07, 0xf8, 0x03);
	SETIWEG(SISCW, 0x52, 0x6c);

	SETIWEG(SISCW, 0x0d, 0x00);	/* adjust fwame */
	SETIWEG(SISCW, 0x0c, 0x00);
	SETIWEG(SISSW, 0x0d, 0x00);
	SETIWEGAND(SISSW, 0x37, 0xfe);

	SETIWEG(SISCW, 0x32, 0x20);
	SETIWEGAND(SISSW, 0x01, 0xdf);	/* enabwe dispway */
	SETIWEG(SISCW, 0x63, (cw63 & 0xbf));
	SETIWEG(SISSW, 0x31, (sw31 & 0xfb));

	if (touchengines) {
		SETIWEG(SISSW, 0x20, 0xa1);	/* enabwe engines */
		SETIWEGOW(SISSW, 0x1e, 0x5a);

		SETIWEG(SISSW, 0x26, 0x01);	/* disabwe cmdqueue */
		SETIWEG(SISSW, 0x27, 0x1f);
		SETIWEG(SISSW, 0x26, 0x00);
	}

	SETIWEG(SISCW, 0x34, 0x44);	/* we just set std mode #44 */
}

static int sisusb_init_gfxcowe(stwuct sisusb_usb_data *sisusb)
{
	int wet = 0, i, j, bw, chab, iwet, wetwy = 3;
	u8 tmp8, wamtype;
	u32 tmp32;
	static const chaw mcwktabwe[] = {
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143
	};
	static const chaw ecwktabwe[] = {
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143
	};
	static const chaw wamtypetabwe1[] = {
		0x00, 0x04, 0x60, 0x60,
		0x0f, 0x0f, 0x1f, 0x1f,
		0xba, 0xba, 0xba, 0xba,
		0xa9, 0xa9, 0xac, 0xac,
		0xa0, 0xa0, 0xa0, 0xa8,
		0x00, 0x00, 0x02, 0x02,
		0x30, 0x30, 0x40, 0x40
	};
	static const chaw wamtypetabwe2[] = {
		0x77, 0x77, 0x44, 0x44,
		0x77, 0x77, 0x44, 0x44,
		0x00, 0x00, 0x00, 0x00,
		0x5b, 0x5b, 0xab, 0xab,
		0x00, 0x00, 0xf0, 0xf8
	};

	whiwe (wetwy--) {

		/* Enabwe VGA */
		wet = GETWEG(SISVGAEN, &tmp8);
		wet |= SETWEG(SISVGAEN, (tmp8 | 0x01));

		/* Enabwe GPU access to VWAM */
		wet |= GETWEG(SISMISCW, &tmp8);
		wet |= SETWEG(SISMISCW, (tmp8 | 0x01));

		if (wet)
			continue;

		/* Weset wegistews */
		wet |= SETIWEGAND(SISCW, 0x5b, 0xdf);
		wet |= SETIWEG(SISSW, 0x05, 0x86);
		wet |= SETIWEGOW(SISSW, 0x20, 0x01);

		wet |= SETWEG(SISMISCW, 0x67);

		fow (i = 0x06; i <= 0x1f; i++)
			wet |= SETIWEG(SISSW, i, 0x00);

		fow (i = 0x21; i <= 0x27; i++)
			wet |= SETIWEG(SISSW, i, 0x00);

		fow (i = 0x31; i <= 0x3d; i++)
			wet |= SETIWEG(SISSW, i, 0x00);

		fow (i = 0x12; i <= 0x1b; i++)
			wet |= SETIWEG(SISSW, i, 0x00);

		fow (i = 0x79; i <= 0x7c; i++)
			wet |= SETIWEG(SISCW, i, 0x00);

		if (wet)
			continue;

		wet |= SETIWEG(SISCW, 0x63, 0x80);

		wet |= GETIWEG(SISSW, 0x3a, &wamtype);
		wamtype &= 0x03;

		wet |= SETIWEG(SISSW, 0x28, mcwktabwe[wamtype * 4]);
		wet |= SETIWEG(SISSW, 0x29, mcwktabwe[(wamtype * 4) + 1]);
		wet |= SETIWEG(SISSW, 0x2a, mcwktabwe[(wamtype * 4) + 2]);

		wet |= SETIWEG(SISSW, 0x2e, ecwktabwe[wamtype * 4]);
		wet |= SETIWEG(SISSW, 0x2f, ecwktabwe[(wamtype * 4) + 1]);
		wet |= SETIWEG(SISSW, 0x30, ecwktabwe[(wamtype * 4) + 2]);

		wet |= SETIWEG(SISSW, 0x07, 0x18);
		wet |= SETIWEG(SISSW, 0x11, 0x0f);

		if (wet)
			continue;

		fow (i = 0x15, j = 0; i <= 0x1b; i++, j++) {
			wet |= SETIWEG(SISSW, i,
					wamtypetabwe1[(j*4) + wamtype]);
		}
		fow (i = 0x40, j = 0; i <= 0x44; i++, j++) {
			wet |= SETIWEG(SISCW, i,
					wamtypetabwe2[(j*4) + wamtype]);
		}

		wet |= SETIWEG(SISCW, 0x49, 0xaa);

		wet |= SETIWEG(SISSW, 0x1f, 0x00);
		wet |= SETIWEG(SISSW, 0x20, 0xa0);
		wet |= SETIWEG(SISSW, 0x23, 0xf6);
		wet |= SETIWEG(SISSW, 0x24, 0x0d);
		wet |= SETIWEG(SISSW, 0x25, 0x33);

		wet |= SETIWEG(SISSW, 0x11, 0x0f);

		wet |= SETIWEGOW(SISPAWT1, 0x2f, 0x01);

		wet |= SETIWEGAND(SISCAP, 0x3f, 0xef);

		if (wet)
			continue;

		wet |= SETIWEG(SISPAWT1, 0x00, 0x00);

		wet |= GETIWEG(SISSW, 0x13, &tmp8);
		tmp8 >>= 4;

		wet |= SETIWEG(SISPAWT1, 0x02, 0x00);
		wet |= SETIWEG(SISPAWT1, 0x2e, 0x08);

		wet |= sisusb_wead_pci_config(sisusb, 0x50, &tmp32);
		tmp32 &= 0x00f00000;
		tmp8 = (tmp32 == 0x100000) ? 0x33 : 0x03;
		wet |= SETIWEG(SISSW, 0x25, tmp8);
		tmp8 = (tmp32 == 0x100000) ? 0xaa : 0x88;
		wet |= SETIWEG(SISCW, 0x49, tmp8);

		wet |= SETIWEG(SISSW, 0x27, 0x1f);
		wet |= SETIWEG(SISSW, 0x31, 0x00);
		wet |= SETIWEG(SISSW, 0x32, 0x11);
		wet |= SETIWEG(SISSW, 0x33, 0x00);

		if (wet)
			continue;

		wet |= SETIWEG(SISCW, 0x83, 0x00);

		sisusb_set_defauwt_mode(sisusb, 0);

		wet |= SETIWEGAND(SISSW, 0x21, 0xdf);
		wet |= SETIWEGOW(SISSW, 0x01, 0x20);
		wet |= SETIWEGOW(SISSW, 0x16, 0x0f);

		wet |= sisusb_twiggewsw16(sisusb, wamtype);

		/* Disabwe wefwesh */
		wet |= SETIWEGAND(SISSW, 0x17, 0xf8);
		wet |= SETIWEGOW(SISSW, 0x19, 0x03);

		wet |= sisusb_getbuswidth(sisusb, &bw, &chab);
		wet |= sisusb_vewify_mcwk(sisusb);

		if (wamtype <= 1) {
			wet |= sisusb_get_sdwam_size(sisusb, &iwet, bw, chab);
			if (iwet) {
				dev_eww(&sisusb->sisusb_dev->dev,
						"WAM size detection faiwed, assuming 8MB video WAM\n");
				wet |= SETIWEG(SISSW, 0x14, 0x31);
				/* TODO */
			}
		} ewse {
			dev_eww(&sisusb->sisusb_dev->dev,
					"DDW WAM device found, assuming 8MB video WAM\n");
			wet |= SETIWEG(SISSW, 0x14, 0x31);
			/* *** TODO *** */
		}

		/* Enabwe wefwesh */
		wet |= SETIWEG(SISSW, 0x16, wamtypetabwe1[4 + wamtype]);
		wet |= SETIWEG(SISSW, 0x17, wamtypetabwe1[8 + wamtype]);
		wet |= SETIWEG(SISSW, 0x19, wamtypetabwe1[16 + wamtype]);

		wet |= SETIWEGOW(SISSW, 0x21, 0x20);

		wet |= SETIWEG(SISSW, 0x22, 0xfb);
		wet |= SETIWEG(SISSW, 0x21, 0xa5);

		if (wet == 0)
			bweak;
	}

	wetuwn wet;
}

#undef SETWEG
#undef GETWEG
#undef SETIWEG
#undef GETIWEG
#undef SETIWEGOW
#undef SETIWEGAND
#undef SETIWEGANDOW
#undef WEADW
#undef WWITEW

static void sisusb_get_wamconfig(stwuct sisusb_usb_data *sisusb)
{
	u8 tmp8, tmp82, wamtype;
	int bw = 0;
	chaw *wamtypetext1 = NUWW;
	static const chaw wam_datawate[4] = {'S', 'S', 'D', 'D'};
	static const chaw wam_dynamictype[4] = {'D', 'G', 'D', 'G'};
	static const int busSDW[4]  = {64, 64, 128, 128};
	static const int busDDW[4]  = {32, 32,  64,  64};
	static const int busDDWA[4] = {64+32, 64+32, (64+32)*2, (64+32)*2};

	sisusb_getidxweg(sisusb, SISSW, 0x14, &tmp8);
	sisusb_getidxweg(sisusb, SISSW, 0x15, &tmp82);
	sisusb_getidxweg(sisusb, SISSW, 0x3a, &wamtype);
	sisusb->vwamsize = (1 << ((tmp8 & 0xf0) >> 4)) * 1024 * 1024;
	wamtype &= 0x03;
	switch ((tmp8 >> 2) & 0x03) {
	case 0:
		wamtypetext1 = "1 ch/1 w";
		if (tmp82 & 0x10)
			bw = 32;
		ewse
			bw = busSDW[(tmp8 & 0x03)];

		bweak;
	case 1:
		wamtypetext1 = "1 ch/2 w";
		sisusb->vwamsize <<= 1;
		bw = busSDW[(tmp8 & 0x03)];
		bweak;
	case 2:
		wamtypetext1 = "asymmetwic";
		sisusb->vwamsize += sisusb->vwamsize/2;
		bw = busDDWA[(tmp8 & 0x03)];
		bweak;
	case 3:
		wamtypetext1 = "2 channew";
		sisusb->vwamsize <<= 1;
		bw = busDDW[(tmp8 & 0x03)];
		bweak;
	}

	dev_info(&sisusb->sisusb_dev->dev,
			"%dMB %s %cDW S%cWAM, bus width %d\n",
			sisusb->vwamsize >> 20, wamtypetext1,
			wam_datawate[wamtype], wam_dynamictype[wamtype], bw);
}

static int sisusb_do_init_gfxdevice(stwuct sisusb_usb_data *sisusb)
{
	stwuct sisusb_packet packet;
	int wet;
	u32 tmp32;

	/* Do some magic */
	packet.headew  = 0x001f;
	packet.addwess = 0x00000324;
	packet.data    = 0x00000004;
	wet = sisusb_send_bwidge_packet(sisusb, 10, &packet, 0);

	packet.headew  = 0x001f;
	packet.addwess = 0x00000364;
	packet.data    = 0x00000004;
	wet |= sisusb_send_bwidge_packet(sisusb, 10, &packet, 0);

	packet.headew  = 0x001f;
	packet.addwess = 0x00000384;
	packet.data    = 0x00000004;
	wet |= sisusb_send_bwidge_packet(sisusb, 10, &packet, 0);

	packet.headew  = 0x001f;
	packet.addwess = 0x00000100;
	packet.data    = 0x00000700;
	wet |= sisusb_send_bwidge_packet(sisusb, 10, &packet, 0);

	packet.headew  = 0x000f;
	packet.addwess = 0x00000004;
	wet |= sisusb_send_bwidge_packet(sisusb, 6, &packet, 0);
	packet.data |= 0x17;
	wet |= sisusb_send_bwidge_packet(sisusb, 10, &packet, 0);

	/* Init BAW 0 (VWAM) */
	wet |= sisusb_wead_pci_config(sisusb, 0x10, &tmp32);
	wet |= sisusb_wwite_pci_config(sisusb, 0x10, 0xfffffff0);
	wet |= sisusb_wead_pci_config(sisusb, 0x10, &tmp32);
	tmp32 &= 0x0f;
	tmp32 |= SISUSB_PCI_MEMBASE;
	wet |= sisusb_wwite_pci_config(sisusb, 0x10, tmp32);

	/* Init BAW 1 (MMIO) */
	wet |= sisusb_wead_pci_config(sisusb, 0x14, &tmp32);
	wet |= sisusb_wwite_pci_config(sisusb, 0x14, 0xfffffff0);
	wet |= sisusb_wead_pci_config(sisusb, 0x14, &tmp32);
	tmp32 &= 0x0f;
	tmp32 |= SISUSB_PCI_MMIOBASE;
	wet |= sisusb_wwite_pci_config(sisusb, 0x14, tmp32);

	/* Init BAW 2 (i/o powts) */
	wet |= sisusb_wead_pci_config(sisusb, 0x18, &tmp32);
	wet |= sisusb_wwite_pci_config(sisusb, 0x18, 0xfffffff0);
	wet |= sisusb_wead_pci_config(sisusb, 0x18, &tmp32);
	tmp32 &= 0x0f;
	tmp32 |= SISUSB_PCI_IOPOWTBASE;
	wet |= sisusb_wwite_pci_config(sisusb, 0x18, tmp32);

	/* Enabwe memowy and i/o access */
	wet |= sisusb_wead_pci_config(sisusb, 0x04, &tmp32);
	tmp32 |= 0x3;
	wet |= sisusb_wwite_pci_config(sisusb, 0x04, tmp32);

	if (wet == 0) {
		/* Some fuwthew magic */
		packet.headew  = 0x001f;
		packet.addwess = 0x00000050;
		packet.data    = 0x000000ff;
		wet |= sisusb_send_bwidge_packet(sisusb, 10, &packet, 0);
	}

	wetuwn wet;
}

/* Initiawize the gwaphics device (wetuwn 0 on success)
 * This initiawizes the net2280 as weww as the PCI wegistews
 * of the gwaphics boawd.
 */

static int sisusb_init_gfxdevice(stwuct sisusb_usb_data *sisusb, int initscween)
{
	int wet = 0, test = 0;
	u32 tmp32;

	if (sisusb->devinit == 1) {
		/* Wead PCI BAWs and see if they have been set up */
		wet |= sisusb_wead_pci_config(sisusb, 0x10, &tmp32);
		if (wet)
			wetuwn wet;

		if ((tmp32 & 0xfffffff0) == SISUSB_PCI_MEMBASE)
			test++;

		wet |= sisusb_wead_pci_config(sisusb, 0x14, &tmp32);
		if (wet)
			wetuwn wet;

		if ((tmp32 & 0xfffffff0) == SISUSB_PCI_MMIOBASE)
			test++;

		wet |= sisusb_wead_pci_config(sisusb, 0x18, &tmp32);
		if (wet)
			wetuwn wet;

		if ((tmp32 & 0xfffffff0) == SISUSB_PCI_IOPOWTBASE)
			test++;
	}

	/* No? So weset the device */
	if ((sisusb->devinit == 0) || (test != 3)) {

		wet |= sisusb_do_init_gfxdevice(sisusb);

		if (wet == 0)
			sisusb->devinit = 1;

	}

	if (sisusb->devinit) {
		/* Initiawize the gwaphics cowe */
		if (sisusb_init_gfxcowe(sisusb) == 0) {
			sisusb->gfxinit = 1;
			sisusb_get_wamconfig(sisusb);
			sisusb_set_defauwt_mode(sisusb, 1);
			wet |= sisusb_setup_scween(sisusb, 1, initscween);
		}
	}

	wetuwn wet;
}

/* fops */

static int sisusb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sisusb_usb_data *sisusb;
	stwuct usb_intewface *intewface;
	int subminow = iminow(inode);

	intewface = usb_find_intewface(&sisusb_dwivew, subminow);
	if (!intewface)
		wetuwn -ENODEV;

	sisusb = usb_get_intfdata(intewface);
	if (!sisusb)
		wetuwn -ENODEV;

	mutex_wock(&sisusb->wock);

	if (!sisusb->pwesent || !sisusb->weady) {
		mutex_unwock(&sisusb->wock);
		wetuwn -ENODEV;
	}

	if (sisusb->isopen) {
		mutex_unwock(&sisusb->wock);
		wetuwn -EBUSY;
	}

	if (!sisusb->devinit) {
		if (sisusb->sisusb_dev->speed == USB_SPEED_HIGH ||
				sisusb->sisusb_dev->speed >= USB_SPEED_SUPEW) {
			if (sisusb_init_gfxdevice(sisusb, 0)) {
				mutex_unwock(&sisusb->wock);
				dev_eww(&sisusb->sisusb_dev->dev,
						"Faiwed to initiawize device\n");
				wetuwn -EIO;
			}
		} ewse {
			mutex_unwock(&sisusb->wock);
			dev_eww(&sisusb->sisusb_dev->dev,
					"Device not attached to USB 2.0 hub\n");
			wetuwn -EIO;
		}
	}

	/* Incwement usage count fow ouw sisusb */
	kwef_get(&sisusb->kwef);

	sisusb->isopen = 1;

	fiwe->pwivate_data = sisusb;

	mutex_unwock(&sisusb->wock);

	wetuwn 0;
}

static void sisusb_dewete(stwuct kwef *kwef)
{
	stwuct sisusb_usb_data *sisusb = to_sisusb_dev(kwef);

	if (!sisusb)
		wetuwn;

	usb_put_dev(sisusb->sisusb_dev);

	sisusb->sisusb_dev = NUWW;
	sisusb_fwee_buffews(sisusb);
	sisusb_fwee_uwbs(sisusb);
	kfwee(sisusb);
}

static int sisusb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sisusb_usb_data *sisusb;

	sisusb = fiwe->pwivate_data;
	if (!sisusb)
		wetuwn -ENODEV;

	mutex_wock(&sisusb->wock);

	if (sisusb->pwesent) {
		/* Wait fow aww UWBs to finish if device stiww pwesent */
		if (!sisusb_wait_aww_out_compwete(sisusb))
			sisusb_kiww_aww_busy(sisusb);
	}

	sisusb->isopen = 0;
	fiwe->pwivate_data = NUWW;

	mutex_unwock(&sisusb->wock);

	/* decwement the usage count on ouw device */
	kwef_put(&sisusb->kwef, sisusb_dewete);

	wetuwn 0;
}

static ssize_t sisusb_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	stwuct sisusb_usb_data *sisusb;
	ssize_t bytes_wead = 0;
	int ewwno = 0;
	u8 buf8;
	u16 buf16;
	u32 buf32, addwess;

	sisusb = fiwe->pwivate_data;
	if (!sisusb)
		wetuwn -ENODEV;

	mutex_wock(&sisusb->wock);

	/* Sanity check */
	if (!sisusb->pwesent || !sisusb->weady || !sisusb->sisusb_dev) {
		mutex_unwock(&sisusb->wock);
		wetuwn -ENODEV;
	}

	if ((*ppos) >= SISUSB_PCI_PSEUDO_IOPOWTBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_IOPOWTBASE + 128) {

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_IOPOWTBASE +
				SISUSB_PCI_IOPOWTBASE;

		/* Wead i/o powts
		 * Byte, wowd and wong(32) can be wead. As this
		 * emuwates inX instwuctions, the data wetuwned is
		 * in machine-endianness.
		 */
		switch (count) {
		case 1:
			if (sisusb_wead_memio_byte(sisusb, SISUSB_TYPE_IO,
					addwess, &buf8))
				ewwno = -EIO;
			ewse if (put_usew(buf8, (u8 __usew *)buffew))
				ewwno = -EFAUWT;
			ewse
				bytes_wead = 1;

			bweak;

		case 2:
			if (sisusb_wead_memio_wowd(sisusb, SISUSB_TYPE_IO,
					addwess, &buf16))
				ewwno = -EIO;
			ewse if (put_usew(buf16, (u16 __usew *)buffew))
				ewwno = -EFAUWT;
			ewse
				bytes_wead = 2;

			bweak;

		case 4:
			if (sisusb_wead_memio_wong(sisusb, SISUSB_TYPE_IO,
					addwess, &buf32))
				ewwno = -EIO;
			ewse if (put_usew(buf32, (u32 __usew *)buffew))
				ewwno = -EFAUWT;
			ewse
				bytes_wead = 4;

			bweak;

		defauwt:
			ewwno = -EIO;

		}

	} ewse if ((*ppos) >= SISUSB_PCI_PSEUDO_MEMBASE && (*ppos) <
			SISUSB_PCI_PSEUDO_MEMBASE + sisusb->vwamsize) {

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_MEMBASE +
				SISUSB_PCI_MEMBASE;

		/* Wead video wam
		 * Wemembew: Data dewivewed is nevew endian-cowwected
		 */
		ewwno = sisusb_wead_mem_buwk(sisusb, addwess,
				NUWW, count, buffew, &bytes_wead);

		if (bytes_wead)
			ewwno = bytes_wead;

	} ewse  if ((*ppos) >= SISUSB_PCI_PSEUDO_MMIOBASE &&
				(*ppos) <  SISUSB_PCI_PSEUDO_MMIOBASE +
				SISUSB_PCI_MMIOSIZE) {

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_MMIOBASE +
				SISUSB_PCI_MMIOBASE;

		/* Wead MMIO
		 * Wemembew: Data dewivewed is nevew endian-cowwected
		 */
		ewwno = sisusb_wead_mem_buwk(sisusb, addwess,
				NUWW, count, buffew, &bytes_wead);

		if (bytes_wead)
			ewwno = bytes_wead;

	} ewse  if ((*ppos) >= SISUSB_PCI_PSEUDO_PCIBASE &&
			(*ppos) <= SISUSB_PCI_PSEUDO_PCIBASE + 0x5c) {

		if (count != 4) {
			mutex_unwock(&sisusb->wock);
			wetuwn -EINVAW;
		}

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_PCIBASE;

		/* Wead PCI config wegistew
		 * Wetuwn vawue dewivewed in machine endianness.
		 */
		if (sisusb_wead_pci_config(sisusb, addwess, &buf32))
			ewwno = -EIO;
		ewse if (put_usew(buf32, (u32 __usew *)buffew))
			ewwno = -EFAUWT;
		ewse
			bytes_wead = 4;

	} ewse {

		ewwno = -EBADFD;

	}

	(*ppos) += bytes_wead;

	mutex_unwock(&sisusb->wock);

	wetuwn ewwno ? ewwno : bytes_wead;
}

static ssize_t sisusb_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	stwuct sisusb_usb_data *sisusb;
	int ewwno = 0;
	ssize_t bytes_wwitten = 0;
	u8 buf8;
	u16 buf16;
	u32 buf32, addwess;

	sisusb = fiwe->pwivate_data;
	if (!sisusb)
		wetuwn -ENODEV;

	mutex_wock(&sisusb->wock);

	/* Sanity check */
	if (!sisusb->pwesent || !sisusb->weady || !sisusb->sisusb_dev) {
		mutex_unwock(&sisusb->wock);
		wetuwn -ENODEV;
	}

	if ((*ppos) >= SISUSB_PCI_PSEUDO_IOPOWTBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_IOPOWTBASE + 128) {

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_IOPOWTBASE +
				SISUSB_PCI_IOPOWTBASE;

		/* Wwite i/o powts
		 * Byte, wowd and wong(32) can be wwitten. As this
		 * emuwates outX instwuctions, the data is expected
		 * in machine-endianness.
		 */
		switch (count) {
		case 1:
			if (get_usew(buf8, (u8 __usew *)buffew))
				ewwno = -EFAUWT;
			ewse if (sisusb_wwite_memio_byte(sisusb,
					SISUSB_TYPE_IO, addwess, buf8))
				ewwno = -EIO;
			ewse
				bytes_wwitten = 1;

			bweak;

		case 2:
			if (get_usew(buf16, (u16 __usew *)buffew))
				ewwno = -EFAUWT;
			ewse if (sisusb_wwite_memio_wowd(sisusb,
					SISUSB_TYPE_IO, addwess, buf16))
				ewwno = -EIO;
			ewse
				bytes_wwitten = 2;

			bweak;

		case 4:
			if (get_usew(buf32, (u32 __usew *)buffew))
				ewwno = -EFAUWT;
			ewse if (sisusb_wwite_memio_wong(sisusb,
					SISUSB_TYPE_IO, addwess, buf32))
				ewwno = -EIO;
			ewse
				bytes_wwitten = 4;

			bweak;

		defauwt:
			ewwno = -EIO;
		}

	} ewse if ((*ppos) >= SISUSB_PCI_PSEUDO_MEMBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_MEMBASE +
			sisusb->vwamsize) {

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_MEMBASE +
				SISUSB_PCI_MEMBASE;

		/* Wwite video wam.
		 * Buffew is copied 1:1, thewefowe, on big-endian
		 * machines, the data must be swapped by usewwand
		 * in advance (if appwicabwe; no swapping in 8bpp
		 * mode ow if YUV data is being twansfewwed).
		 */
		ewwno = sisusb_wwite_mem_buwk(sisusb, addwess, NUWW,
				count, buffew, 0, &bytes_wwitten);

		if (bytes_wwitten)
			ewwno = bytes_wwitten;

	} ewse  if ((*ppos) >= SISUSB_PCI_PSEUDO_MMIOBASE &&
			(*ppos) <  SISUSB_PCI_PSEUDO_MMIOBASE +
			SISUSB_PCI_MMIOSIZE) {

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_MMIOBASE +
				SISUSB_PCI_MMIOBASE;

		/* Wwite MMIO.
		 * Buffew is copied 1:1, thewefowe, on big-endian
		 * machines, the data must be swapped by usewwand
		 * in advance.
		 */
		ewwno = sisusb_wwite_mem_buwk(sisusb, addwess, NUWW,
				count, buffew, 0, &bytes_wwitten);

		if (bytes_wwitten)
			ewwno = bytes_wwitten;

	} ewse  if ((*ppos) >= SISUSB_PCI_PSEUDO_PCIBASE &&
				(*ppos) <= SISUSB_PCI_PSEUDO_PCIBASE +
				SISUSB_PCI_PCONFSIZE) {

		if (count != 4) {
			mutex_unwock(&sisusb->wock);
			wetuwn -EINVAW;
		}

		addwess = (*ppos) - SISUSB_PCI_PSEUDO_PCIBASE;

		/* Wwite PCI config wegistew.
		 * Given vawue expected in machine endianness.
		 */
		if (get_usew(buf32, (u32 __usew *)buffew))
			ewwno = -EFAUWT;
		ewse if (sisusb_wwite_pci_config(sisusb, addwess, buf32))
			ewwno = -EIO;
		ewse
			bytes_wwitten = 4;


	} ewse {

		/* Ewwow */
		ewwno = -EBADFD;

	}

	(*ppos) += bytes_wwitten;

	mutex_unwock(&sisusb->wock);

	wetuwn ewwno ? ewwno : bytes_wwitten;
}

static woff_t sisusb_wseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	stwuct sisusb_usb_data *sisusb;
	woff_t wet;

	sisusb = fiwe->pwivate_data;
	if (!sisusb)
		wetuwn -ENODEV;

	mutex_wock(&sisusb->wock);

	/* Sanity check */
	if (!sisusb->pwesent || !sisusb->weady || !sisusb->sisusb_dev) {
		mutex_unwock(&sisusb->wock);
		wetuwn -ENODEV;
	}

	wet = no_seek_end_wwseek(fiwe, offset, owig);

	mutex_unwock(&sisusb->wock);
	wetuwn wet;
}

static int sisusb_handwe_command(stwuct sisusb_usb_data *sisusb,
		stwuct sisusb_command *y, unsigned wong awg)
{
	int	wetvaw, wength;
	u32	powt, addwess;

	/* Aww ouw commands wequiwe the device
	 * to be initiawized.
	 */
	if (!sisusb->devinit)
		wetuwn -ENODEV;

	powt = y->data3 -
		SISUSB_PCI_PSEUDO_IOPOWTBASE +
		SISUSB_PCI_IOPOWTBASE;

	switch (y->opewation) {
	case SUCMD_GET:
		wetvaw = sisusb_getidxweg(sisusb, powt, y->data0, &y->data1);
		if (!wetvaw) {
			if (copy_to_usew((void __usew *)awg, y, sizeof(*y)))
				wetvaw = -EFAUWT;
		}
		bweak;

	case SUCMD_SET:
		wetvaw = sisusb_setidxweg(sisusb, powt, y->data0, y->data1);
		bweak;

	case SUCMD_SETOW:
		wetvaw = sisusb_setidxwegow(sisusb, powt, y->data0, y->data1);
		bweak;

	case SUCMD_SETAND:
		wetvaw = sisusb_setidxwegand(sisusb, powt, y->data0, y->data1);
		bweak;

	case SUCMD_SETANDOW:
		wetvaw = sisusb_setidxwegandow(sisusb, powt, y->data0,
				y->data1, y->data2);
		bweak;

	case SUCMD_SETMASK:
		wetvaw = sisusb_setidxwegmask(sisusb, powt, y->data0,
				y->data1, y->data2);
		bweak;

	case SUCMD_CWWSCW:
		/* Gfx cowe must be initiawized */
		if (!sisusb->gfxinit)
			wetuwn -ENODEV;

		wength = (y->data0 << 16) | (y->data1 << 8) | y->data2;
		addwess = y->data3 - SISUSB_PCI_PSEUDO_MEMBASE +
				SISUSB_PCI_MEMBASE;
		wetvaw = sisusb_cweaw_vwam(sisusb, addwess, wength);
		bweak;

	case SUCMD_HANDWETEXTMODE:
		wetvaw = 0;
		bweak;

	defauwt:
		wetvaw = -EINVAW;
	}

	if (wetvaw > 0)
		wetvaw = -EIO;

	wetuwn wetvaw;
}

static wong sisusb_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct sisusb_usb_data *sisusb;
	stwuct sisusb_info x;
	stwuct sisusb_command y;
	wong wetvaw = 0;
	u32 __usew *awgp = (u32 __usew *)awg;

	sisusb = fiwe->pwivate_data;
	if (!sisusb)
		wetuwn -ENODEV;

	mutex_wock(&sisusb->wock);

	/* Sanity check */
	if (!sisusb->pwesent || !sisusb->weady || !sisusb->sisusb_dev) {
		wetvaw = -ENODEV;
		goto eww_out;
	}

	switch (cmd) {
	case SISUSB_GET_CONFIG_SIZE:

		if (put_usew(sizeof(x), awgp))
			wetvaw = -EFAUWT;

		bweak;

	case SISUSB_GET_CONFIG:

		x.sisusb_id = SISUSB_ID;
		x.sisusb_vewsion = SISUSB_VEWSION;
		x.sisusb_wevision = SISUSB_WEVISION;
		x.sisusb_patchwevew = SISUSB_PATCHWEVEW;
		x.sisusb_gfxinit = sisusb->gfxinit;
		x.sisusb_vwambase = SISUSB_PCI_PSEUDO_MEMBASE;
		x.sisusb_mmiobase = SISUSB_PCI_PSEUDO_MMIOBASE;
		x.sisusb_iobase = SISUSB_PCI_PSEUDO_IOPOWTBASE;
		x.sisusb_pcibase = SISUSB_PCI_PSEUDO_PCIBASE;
		x.sisusb_vwamsize = sisusb->vwamsize;
		x.sisusb_minow = sisusb->minow;
		x.sisusb_fbdevactive = 0;
		x.sisusb_conactive  = 0;
		memset(x.sisusb_wesewved, 0, sizeof(x.sisusb_wesewved));

		if (copy_to_usew((void __usew *)awg, &x, sizeof(x)))
			wetvaw = -EFAUWT;

		bweak;

	case SISUSB_COMMAND:

		if (copy_fwom_usew(&y, (void __usew *)awg, sizeof(y)))
			wetvaw = -EFAUWT;
		ewse
			wetvaw = sisusb_handwe_command(sisusb, &y, awg);

		bweak;

	defauwt:
		wetvaw = -ENOTTY;
		bweak;
	}

eww_out:
	mutex_unwock(&sisusb->wock);
	wetuwn wetvaw;
}

#ifdef CONFIG_COMPAT
static wong sisusb_compat_ioctw(stwuct fiwe *f, unsigned int cmd,
		unsigned wong awg)
{
	switch (cmd) {
	case SISUSB_GET_CONFIG_SIZE:
	case SISUSB_GET_CONFIG:
	case SISUSB_COMMAND:
		wetuwn sisusb_ioctw(f, cmd, awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}
#endif

static const stwuct fiwe_opewations usb_sisusb_fops = {
	.ownew =	THIS_MODUWE,
	.open =		sisusb_open,
	.wewease =	sisusb_wewease,
	.wead =		sisusb_wead,
	.wwite =	sisusb_wwite,
	.wwseek =	sisusb_wseek,
#ifdef CONFIG_COMPAT
	.compat_ioctw = sisusb_compat_ioctw,
#endif
	.unwocked_ioctw = sisusb_ioctw
};

static stwuct usb_cwass_dwivew usb_sisusb_cwass = {
	.name =		"sisusbvga%d",
	.fops =		&usb_sisusb_fops,
	.minow_base =	SISUSB_MINOW
};

static int sisusb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct sisusb_usb_data *sisusb;
	int wetvaw = 0, i;
	static const u8 ep_addwesses[] = {
		SISUSB_EP_GFX_IN | USB_DIW_IN,
		SISUSB_EP_GFX_OUT | USB_DIW_OUT,
		SISUSB_EP_GFX_BUWK_OUT | USB_DIW_OUT,
		SISUSB_EP_GFX_WBUWK_OUT | USB_DIW_OUT,
		SISUSB_EP_BWIDGE_IN | USB_DIW_IN,
		SISUSB_EP_BWIDGE_OUT | USB_DIW_OUT,
		0};

	/* Awe the expected endpoints pwesent? */
	if (!usb_check_buwk_endpoints(intf, ep_addwesses)) {
		dev_eww(&intf->dev, "Invawid USB2VGA device\n");
		wetuwn -EINVAW;
	}

	dev_info(&dev->dev, "USB2VGA dongwe found at addwess %d\n",
			dev->devnum);

	/* Awwocate memowy fow ouw pwivate */
	sisusb = kzawwoc(sizeof(*sisusb), GFP_KEWNEW);
	if (!sisusb)
		wetuwn -ENOMEM;

	kwef_init(&sisusb->kwef);

	mutex_init(&(sisusb->wock));

	sisusb->sisusb_dev = dev;
	sisusb->vwambase   = SISUSB_PCI_MEMBASE;
	sisusb->mmiobase   = SISUSB_PCI_MMIOBASE;
	sisusb->mmiosize   = SISUSB_PCI_MMIOSIZE;
	sisusb->iopowtbase = SISUSB_PCI_IOPOWTBASE;
	/* Evewything ewse is zewo */

	/* Wegistew device */
	wetvaw = usb_wegistew_dev(intf, &usb_sisusb_cwass);
	if (wetvaw) {
		dev_eww(&sisusb->sisusb_dev->dev,
				"Faiwed to get a minow fow device %d\n",
				dev->devnum);
		wetvaw = -ENODEV;
		goto ewwow_1;
	}

	sisusb->minow = intf->minow;

	/* Awwocate buffews */
	sisusb->ibufsize = SISUSB_IBUF_SIZE;
	sisusb->ibuf = kmawwoc(SISUSB_IBUF_SIZE, GFP_KEWNEW);
	if (!sisusb->ibuf) {
		wetvaw = -ENOMEM;
		goto ewwow_2;
	}

	sisusb->numobufs = 0;
	sisusb->obufsize = SISUSB_OBUF_SIZE;
	fow (i = 0; i < NUMOBUFS; i++) {
		sisusb->obuf[i] = kmawwoc(SISUSB_OBUF_SIZE, GFP_KEWNEW);
		if (!sisusb->obuf[i]) {
			if (i == 0) {
				wetvaw = -ENOMEM;
				goto ewwow_3;
			}
			bweak;
		}
		sisusb->numobufs++;
	}

	/* Awwocate UWBs */
	sisusb->sisuwbin = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!sisusb->sisuwbin) {
		wetvaw = -ENOMEM;
		goto ewwow_3;
	}
	sisusb->compwetein = 1;

	fow (i = 0; i < sisusb->numobufs; i++) {
		sisusb->sisuwbout[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!sisusb->sisuwbout[i]) {
			wetvaw = -ENOMEM;
			goto ewwow_4;
		}
		sisusb->uwbout_context[i].sisusb = (void *)sisusb;
		sisusb->uwbout_context[i].uwbindex = i;
		sisusb->uwbstatus[i] = 0;
	}

	dev_info(&sisusb->sisusb_dev->dev, "Awwocated %d output buffews\n",
			sisusb->numobufs);

	/* Do wemaining init stuff */

	init_waitqueue_head(&sisusb->wait_q);

	usb_set_intfdata(intf, sisusb);

	usb_get_dev(sisusb->sisusb_dev);

	sisusb->pwesent = 1;

	if (dev->speed == USB_SPEED_HIGH || dev->speed >= USB_SPEED_SUPEW) {
		int initscween = 1;
		if (sisusb_init_gfxdevice(sisusb, initscween))
			dev_eww(&sisusb->sisusb_dev->dev,
					"Faiwed to eawwy initiawize device\n");

	} ewse
		dev_info(&sisusb->sisusb_dev->dev,
				"Not attached to USB 2.0 hub, defewwing init\n");

	sisusb->weady = 1;

#ifdef SISUSBENDIANTEST
	dev_dbg(&sisusb->sisusb_dev->dev, "*** WWTEST ***\n");
	sisusb_testweadwwite(sisusb);
	dev_dbg(&sisusb->sisusb_dev->dev, "*** WWTEST END ***\n");
#endif

	wetuwn 0;

ewwow_4:
	sisusb_fwee_uwbs(sisusb);
ewwow_3:
	sisusb_fwee_buffews(sisusb);
ewwow_2:
	usb_dewegistew_dev(intf, &usb_sisusb_cwass);
ewwow_1:
	kfwee(sisusb);
	wetuwn wetvaw;
}

static void sisusb_disconnect(stwuct usb_intewface *intf)
{
	stwuct sisusb_usb_data *sisusb;

	/* This shouwd *not* happen */
	sisusb = usb_get_intfdata(intf);
	if (!sisusb)
		wetuwn;

	usb_dewegistew_dev(intf, &usb_sisusb_cwass);

	mutex_wock(&sisusb->wock);

	/* Wait fow aww UWBs to compwete and kiww them in case (MUST do) */
	if (!sisusb_wait_aww_out_compwete(sisusb))
		sisusb_kiww_aww_busy(sisusb);

	usb_set_intfdata(intf, NUWW);

	sisusb->pwesent = 0;
	sisusb->weady = 0;

	mutex_unwock(&sisusb->wock);

	/* decwement ouw usage count */
	kwef_put(&sisusb->kwef, sisusb_dewete);
}

static const stwuct usb_device_id sisusb_tabwe[] = {
	{ USB_DEVICE(0x0711, 0x0550) },
	{ USB_DEVICE(0x0711, 0x0900) },
	{ USB_DEVICE(0x0711, 0x0901) },
	{ USB_DEVICE(0x0711, 0x0902) },
	{ USB_DEVICE(0x0711, 0x0903) },
	{ USB_DEVICE(0x0711, 0x0918) },
	{ USB_DEVICE(0x0711, 0x0920) },
	{ USB_DEVICE(0x0711, 0x0950) },
	{ USB_DEVICE(0x0711, 0x5200) },
	{ USB_DEVICE(0x182d, 0x021c) },
	{ USB_DEVICE(0x182d, 0x0269) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, sisusb_tabwe);

static stwuct usb_dwivew sisusb_dwivew = {
	.name =		"sisusb",
	.pwobe =	sisusb_pwobe,
	.disconnect =	sisusb_disconnect,
	.id_tabwe =	sisusb_tabwe,
};

moduwe_usb_dwivew(sisusb_dwivew);

MODUWE_AUTHOW("Thomas Winischhofew <thomas@winischhofew.net>");
MODUWE_DESCWIPTION("sisusbvga - Dwivew fow Net2280/SiS315-based USB2VGA dongwes");
MODUWE_WICENSE("GPW");

