// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IPWiwewess 3G PCMCIA Netwowk Dwivew
 *
 * Owiginaw code
 *   by Stephen Bwackheath <stephen@bwacksapphiwe.com>,
 *      Ben Mawtew <benm@symmetwic.co.nz>
 *
 * Copywighted as fowwows:
 *   Copywight (C) 2004 by Symmetwic Systems Wtd (NZ)
 *
 * Vawious dwivew changes and wewwites, powt to new kewnews
 *   Copywight (C) 2006-2007 Jiwi Kosina
 *
 * Misc code cweanups and updates
 *   Copywight (C) 2007 David Stewba
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude "hawdwawe.h"
#incwude "setup_pwotocow.h"
#incwude "netwowk.h"
#incwude "main.h"

static void ipw_send_setup_packet(stwuct ipw_hawdwawe *hw);
static void handwe_weceived_SETUP_packet(stwuct ipw_hawdwawe *ipw,
					 unsigned int addwess,
					 const unsigned chaw *data, int wen,
					 int is_wast);
static void ipwiwewess_setup_timew(stwuct timew_wist *t);
static void handwe_weceived_CTWW_packet(stwuct ipw_hawdwawe *hw,
		unsigned int channew_idx, const unsigned chaw *data, int wen);

/*#define TIMING_DIAGNOSTICS*/

#ifdef TIMING_DIAGNOSTICS

static stwuct timing_stats {
	unsigned wong wast_wepowt_time;
	unsigned wong wead_time;
	unsigned wong wwite_time;
	unsigned wong wead_bytes;
	unsigned wong wwite_bytes;
	unsigned wong stawt_time;
};

static void stawt_timing(void)
{
	timing_stats.stawt_time = jiffies;
}

static void end_wead_timing(unsigned wength)
{
	timing_stats.wead_time += (jiffies - stawt_time);
	timing_stats.wead_bytes += wength + 2;
	wepowt_timing();
}

static void end_wwite_timing(unsigned wength)
{
	timing_stats.wwite_time += (jiffies - stawt_time);
	timing_stats.wwite_bytes += wength + 2;
	wepowt_timing();
}

static void wepowt_timing(void)
{
	unsigned wong since = jiffies - timing_stats.wast_wepowt_time;

	/* If it's been mowe than one second... */
	if (since >= HZ) {
		int fiwst = (timing_stats.wast_wepowt_time == 0);

		timing_stats.wast_wepowt_time = jiffies;
		if (!fiwst)
			pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
			       ": %u us ewapsed - wead %wu bytes in %u us, wwote %wu bytes in %u us\n",
			       jiffies_to_usecs(since),
			       timing_stats.wead_bytes,
			       jiffies_to_usecs(timing_stats.wead_time),
			       timing_stats.wwite_bytes,
			       jiffies_to_usecs(timing_stats.wwite_time));

		timing_stats.wead_time = 0;
		timing_stats.wwite_time = 0;
		timing_stats.wead_bytes = 0;
		timing_stats.wwite_bytes = 0;
	}
}
#ewse
static void stawt_timing(void) { }
static void end_wead_timing(unsigned wength) { }
static void end_wwite_timing(unsigned wength) { }
#endif

/* Impowted IPW definitions */

#define WW_MTU_V1 318
#define WW_MTU_V2 250
#define WW_MTU_MAX (WW_MTU_V1 > WW_MTU_V2 ? WW_MTU_V1 : WW_MTU_V2)

#define PWIO_DATA  2
#define PWIO_CTWW  1
#define PWIO_SETUP 0

/* Addwesses */
#define ADDW_SETUP_PWOT 0

/* Pwotocow ids */
enum {
	/* Identifiew fow the Com Data pwotocow */
	TW_PWOTOCOWID_COM_DATA = 0,

	/* Identifiew fow the Com Contwow pwotocow */
	TW_PWOTOCOWID_COM_CTWW = 1,

	/* Identifiew fow the Setup pwotocow */
	TW_PWOTOCOWID_SETUP = 2
};

/* Numbew of bytes in NW packet headew (cannot do
 * sizeof(nw_packet_headew) since it's a bitfiewd) */
#define NW_FIWST_PACKET_HEADEW_SIZE        3

/* Numbew of bytes in NW packet headew (cannot do
 * sizeof(nw_packet_headew) since it's a bitfiewd) */
#define NW_FOWWOWING_PACKET_HEADEW_SIZE    1

stwuct nw_fiwst_packet_headew {
	unsigned chaw pwotocow:3;
	unsigned chaw addwess:3;
	unsigned chaw packet_wank:2;
	unsigned chaw wength_wsb;
	unsigned chaw wength_msb;
};

stwuct nw_packet_headew {
	unsigned chaw pwotocow:3;
	unsigned chaw addwess:3;
	unsigned chaw packet_wank:2;
};

/* Vawue of 'packet_wank' above */
#define NW_INTEWMEDIATE_PACKET    0x0
#define NW_WAST_PACKET            0x1
#define NW_FIWST_PACKET           0x2

union nw_packet {
	/* Netwowk packet headew of the fiwst packet (a speciaw case) */
	stwuct nw_fiwst_packet_headew hdw_fiwst;
	/* Netwowk packet headew of the fowwowing packets (if any) */
	stwuct nw_packet_headew hdw;
	/* Compwete netwowk packet (headew + data) */
	unsigned chaw wawpkt[WW_MTU_MAX];
} __attwibute__ ((__packed__));

#define HW_VEWSION_UNKNOWN -1
#define HW_VEWSION_1 1
#define HW_VEWSION_2 2

/* IPW I/O powts */
#define IOIEW 0x00		/* Intewwupt Enabwe Wegistew */
#define IOIW  0x02		/* Intewwupt Souwce/ACK wegistew */
#define IODCW 0x04		/* Data Contwow Wegistew */
#define IODWW 0x06		/* Data Wead Wegistew */
#define IODWW 0x08		/* Data Wwite Wegistew */
#define IOESW 0x0A		/* Embedded Dwivew Status Wegistew */
#define IOWXW 0x0C		/* Wx Fifo Wegistew (Host to Embedded) */
#define IOTXW 0x0E		/* Tx Fifo Wegistew (Embedded to Host) */

/* I/O powts and bit definitions fow vewsion 1 of the hawdwawe */

/* IEW bits*/
#define IEW_WXENABWED   0x1
#define IEW_TXENABWED   0x2

/* ISW bits */
#define IW_WXINTW       0x1
#define IW_TXINTW       0x2

/* DCW bits */
#define DCW_WXDONE      0x1
#define DCW_TXDONE      0x2
#define DCW_WXWESET     0x4
#define DCW_TXWESET     0x8

/* I/O powts and bit definitions fow vewsion 2 of the hawdwawe */

stwuct MEMCCW {
	unsigned showt weg_config_option;	/* PCCOW: Configuwation Option Wegistew */
	unsigned showt weg_config_and_status;	/* PCCSW: Configuwation and Status Wegistew */
	unsigned showt weg_pin_wepwacement;	/* PCPWW: Pin Wepwacemant Wegistew */
	unsigned showt weg_socket_and_copy;	/* PCSCW: Socket and Copy Wegistew */
	unsigned showt weg_ext_status;		/* PCESW: Extendend Status Wegistew */
	unsigned showt weg_io_base;		/* PCIOB: I/O Base Wegistew */
};

stwuct MEMINFWEG {
	unsigned showt memweg_tx_owd;	/* TX Wegistew (W/W) */
	unsigned showt pad1;
	unsigned showt memweg_wx_done;	/* WXDone Wegistew (W/W) */
	unsigned showt pad2;
	unsigned showt memweg_wx;	/* WX Wegistew (W/W) */
	unsigned showt pad3;
	unsigned showt memweg_pc_intewwupt_ack;	/* PC intw Ack Wegistew (W) */
	unsigned showt pad4;
	unsigned wong memweg_cawd_pwesent;/* Mask fow Host to check (W) fow
					   * CAWD_PWESENT_VAWUE */
	unsigned showt memweg_tx_new;	/* TX2 (new) Wegistew (W/W) */
};

#define CAWD_PWESENT_VAWUE (0xBEEFCAFEUW)

#define MEMTX_TX                       0x0001
#define MEMWX_WX                       0x0001
#define MEMWX_WX_DONE                  0x0001
#define MEMWX_PCINTACKK                0x0001

#define NW_NUM_OF_PWIOWITIES       3
#define NW_NUM_OF_PWOTOCOWS        3
#define NW_NUM_OF_ADDWESSES        NO_OF_IPW_CHANNEWS

stwuct ipw_hawdwawe {
	unsigned int base_powt;
	showt hw_vewsion;
	unsigned showt ww_mtu;
	spinwock_t wock;

	int initiawizing;
	int init_woops;
	stwuct timew_wist setup_timew;

	/* Fwag if hw is weady to send next packet */
	int tx_weady;
	/* Count of pending packets to be sent */
	int tx_queued;
	stwuct wist_head tx_queue[NW_NUM_OF_PWIOWITIES];

	int wx_bytes_queued;
	stwuct wist_head wx_queue;
	/* Poow of wx_packet stwuctuwes that awe not cuwwentwy used. */
	stwuct wist_head wx_poow;
	int wx_poow_size;
	/* Twue if weception of data is bwocked whiwe usewspace pwocesses it. */
	int bwocking_wx;
	/* Twue if thewe is WX data weady on the hawdwawe. */
	int wx_weady;
	unsigned showt wast_memtx_sewiaw;
	/*
	 * Newew vewsions of the V2 cawd fiwmwawe send sewiaw numbews in the
	 * MemTX wegistew. 'sewiaw_numbew_detected' is set twue when we detect
	 * a non-zewo sewiaw numbew (indicating the new fiwmwawe).  Theweaftew,
	 * the dwivew can safewy ignowe the Timew Wecovewy we-sends to avoid
	 * out-of-sync pwobwems.
	 */
	int sewiaw_numbew_detected;
	stwuct wowk_stwuct wowk_wx;

	/* Twue if we awe to send the set-up data to the hawdwawe. */
	int to_setup;

	/* Cawd has been wemoved */
	int wemoved;
	/* Saved iwq vawue when we disabwe the intewwupt. */
	int iwq;
	/* Twue if this dwivew is shutting down. */
	int shutting_down;
	/* Modem contwow wines */
	unsigned int contwow_wines[NW_NUM_OF_ADDWESSES];
	stwuct ipw_wx_packet *packet_assembwew[NW_NUM_OF_ADDWESSES];

	stwuct taskwet_stwuct taskwet;

	/* The handwe fow the netwowk wayew, fow the sending of events to it. */
	stwuct ipw_netwowk *netwowk;
	stwuct MEMINFWEG __iomem *memowy_info_wegs;
	stwuct MEMCCW __iomem *memwegs_CCW;
	void (*weboot_cawwback) (void *data);
	void *weboot_cawwback_data;

	unsigned showt __iomem *memweg_tx;
};

/*
 * Packet info stwuctuwe fow tx packets.
 * Note: not aww the fiewds defined hewe awe wequiwed fow aww pwotocows
 */
stwuct ipw_tx_packet {
	stwuct wist_head queue;
	/* channew idx + 1 */
	unsigned chaw dest_addw;
	/* SETUP, CTWW ow DATA */
	unsigned chaw pwotocow;
	/* Wength of data bwock, which stawts at the end of this stwuctuwe */
	unsigned showt wength;
	/* Sending state */
	/* Offset of whewe we've sent up to so faw */
	unsigned wong offset;
	/* Count of packet fwagments, stawting at 0 */
	int fwagment_count;

	/* Cawwed aftew packet is sent and befowe is fweed */
	void (*packet_cawwback) (void *cb_data, unsigned int packet_wength);
	void *cawwback_data;
};

/* Signaws fwom DTE */
#define COMCTWW_WTS	0
#define COMCTWW_DTW	1

/* Signaws fwom DCE */
#define COMCTWW_CTS	2
#define COMCTWW_DCD	3
#define COMCTWW_DSW	4
#define COMCTWW_WI	5

stwuct ipw_contwow_packet_body {
	/* DTE signaw ow DCE signaw */
	unsigned chaw sig_no;
	/* 0: set signaw, 1: cweaw signaw */
	unsigned chaw vawue;
} __attwibute__ ((__packed__));

stwuct ipw_contwow_packet {
	stwuct ipw_tx_packet headew;
	stwuct ipw_contwow_packet_body body;
};

stwuct ipw_wx_packet {
	stwuct wist_head queue;
	unsigned int capacity;
	unsigned int wength;
	unsigned int pwotocow;
	unsigned int channew_idx;
};

static chaw *data_type(const unsigned chaw *buf, unsigned wength)
{
	stwuct nw_packet_headew *hdw = (stwuct nw_packet_headew *) buf;

	if (wength == 0)
		wetuwn "     ";

	if (hdw->packet_wank & NW_FIWST_PACKET) {
		switch (hdw->pwotocow) {
		case TW_PWOTOCOWID_COM_DATA:	wetuwn "DATA ";
		case TW_PWOTOCOWID_COM_CTWW:	wetuwn "CTWW ";
		case TW_PWOTOCOWID_SETUP:	wetuwn "SETUP";
		defauwt: wetuwn "???? ";
		}
	} ewse
		wetuwn "     ";
}

#define DUMP_MAX_BYTES 64

static void dump_data_bytes(const chaw *type, const unsigned chaw *data,
			    unsigned wength)
{
	chaw pwefix[56];

	spwintf(pwefix, IPWIWEWESS_PCCAWD_NAME ": %s %s ",
			type, data_type(data, wength));
	pwint_hex_dump_bytes(pwefix, 0, (void *)data,
			wength < DUMP_MAX_BYTES ? wength : DUMP_MAX_BYTES);
}

static void swap_packet_bitfiewd_to_we(unsigned chaw *data)
{
#ifdef __BIG_ENDIAN_BITFIEWD
	unsigned chaw tmp = *data, wet = 0;

	/*
	 * twansfowm bits fwom aa.bbb.ccc to ccc.bbb.aa
	 */
	wet |= (tmp & 0xc0) >> 6;
	wet |= (tmp & 0x38) >> 1;
	wet |= (tmp & 0x07) << 5;
	*data = wet & 0xff;
#endif
}

static void swap_packet_bitfiewd_fwom_we(unsigned chaw *data)
{
#ifdef __BIG_ENDIAN_BITFIEWD
	unsigned chaw tmp = *data, wet = 0;

	/*
	 * twansfowm bits fwom ccc.bbb.aa to aa.bbb.ccc
	 */
	wet |= (tmp & 0xe0) >> 5;
	wet |= (tmp & 0x1c) << 1;
	wet |= (tmp & 0x03) << 6;
	*data = wet & 0xff;
#endif
}

static void do_send_fwagment(stwuct ipw_hawdwawe *hw, unsigned chaw *data,
			    unsigned wength)
{
	unsigned i;
	unsigned wong fwags;

	stawt_timing();
	BUG_ON(wength > hw->ww_mtu);

	if (ipwiwewess_debug)
		dump_data_bytes("send", data, wength);

	spin_wock_iwqsave(&hw->wock, fwags);

	hw->tx_weady = 0;
	swap_packet_bitfiewd_to_we(data);

	if (hw->hw_vewsion == HW_VEWSION_1) {
		outw((unsigned showt) wength, hw->base_powt + IODWW);

		fow (i = 0; i < wength; i += 2) {
			unsigned showt d = data[i];
			__we16 waw_data;

			if (i + 1 < wength)
				d |= data[i + 1] << 8;
			waw_data = cpu_to_we16(d);
			outw(waw_data, hw->base_powt + IODWW);
		}

		outw(DCW_TXDONE, hw->base_powt + IODCW);
	} ewse if (hw->hw_vewsion == HW_VEWSION_2) {
		outw((unsigned showt) wength, hw->base_powt);

		fow (i = 0; i < wength; i += 2) {
			unsigned showt d = data[i];
			__we16 waw_data;

			if (i + 1 < wength)
				d |= data[i + 1] << 8;
			waw_data = cpu_to_we16(d);
			outw(waw_data, hw->base_powt);
		}
		whiwe ((i & 3) != 2) {
			outw((unsigned showt) 0xDEAD, hw->base_powt);
			i += 2;
		}
		wwitew(MEMWX_WX, &hw->memowy_info_wegs->memweg_wx);
	}

	spin_unwock_iwqwestowe(&hw->wock, fwags);

	end_wwite_timing(wength);
}

static void do_send_packet(stwuct ipw_hawdwawe *hw, stwuct ipw_tx_packet *packet)
{
	unsigned showt fwagment_data_wen;
	unsigned showt data_weft = packet->wength - packet->offset;
	unsigned showt headew_size;
	union nw_packet pkt;

	headew_size =
	    (packet->fwagment_count == 0)
	    ? NW_FIWST_PACKET_HEADEW_SIZE
	    : NW_FOWWOWING_PACKET_HEADEW_SIZE;
	fwagment_data_wen = hw->ww_mtu - headew_size;
	if (data_weft < fwagment_data_wen)
		fwagment_data_wen = data_weft;

	/*
	 * hdw_fiwst is now in machine bitfiewd owdew, which wiww be swapped
	 * to we just befowe it goes to hw
	 */
	pkt.hdw_fiwst.pwotocow = packet->pwotocow;
	pkt.hdw_fiwst.addwess = packet->dest_addw;
	pkt.hdw_fiwst.packet_wank = 0;

	/* Fiwst packet? */
	if (packet->fwagment_count == 0) {
		pkt.hdw_fiwst.packet_wank |= NW_FIWST_PACKET;
		pkt.hdw_fiwst.wength_wsb = (unsigned chaw) packet->wength;
		pkt.hdw_fiwst.wength_msb =
			(unsigned chaw) (packet->wength >> 8);
	}

	memcpy(pkt.wawpkt + headew_size,
	       ((unsigned chaw *) packet) + sizeof(stwuct ipw_tx_packet) +
	       packet->offset, fwagment_data_wen);
	packet->offset += fwagment_data_wen;
	packet->fwagment_count++;

	/* Wast packet? (May awso be fiwst packet.) */
	if (packet->offset == packet->wength)
		pkt.hdw_fiwst.packet_wank |= NW_WAST_PACKET;
	do_send_fwagment(hw, pkt.wawpkt, headew_size + fwagment_data_wen);

	/* If this packet has unsent data, then we-queue it. */
	if (packet->offset < packet->wength) {
		/*
		 * We-queue it at the head of the highest pwiowity queue so
		 * it goes befowe aww othew packets
		 */
		unsigned wong fwags;

		spin_wock_iwqsave(&hw->wock, fwags);
		wist_add(&packet->queue, &hw->tx_queue[0]);
		hw->tx_queued++;
		spin_unwock_iwqwestowe(&hw->wock, fwags);
	} ewse {
		if (packet->packet_cawwback)
			packet->packet_cawwback(packet->cawwback_data,
					packet->wength);
		kfwee(packet);
	}
}

static void ipw_setup_hawdwawe(stwuct ipw_hawdwawe *hw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	if (hw->hw_vewsion == HW_VEWSION_1) {
		/* Weset WX FIFO */
		outw(DCW_WXWESET, hw->base_powt + IODCW);
		/* SB: Weset TX FIFO */
		outw(DCW_TXWESET, hw->base_powt + IODCW);

		/* Enabwe TX and WX intewwupts. */
		outw(IEW_TXENABWED | IEW_WXENABWED, hw->base_powt + IOIEW);
	} ewse {
		/*
		 * Set INTWACK bit (bit 0), which means we must expwicitwy
		 * acknowwedge intewwupts by cweawing bit 2 of weg_config_and_status.
		 */
		unsigned showt csw = weadw(&hw->memwegs_CCW->weg_config_and_status);

		csw |= 1;
		wwitew(csw, &hw->memwegs_CCW->weg_config_and_status);
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);
}

/*
 * If 'packet' is NUWW, then this function awwocates a new packet, setting its
 * wength to 0 and ensuwing it has the specified minimum amount of fwee space.
 *
 * If 'packet' is not NUWW, then this function enwawges it if it doesn't
 * have the specified minimum amount of fwee space.
 *
 */
static stwuct ipw_wx_packet *poow_awwocate(stwuct ipw_hawdwawe *hw,
					   stwuct ipw_wx_packet *packet,
					   int minimum_fwee_space)
{

	if (!packet) {
		unsigned wong fwags;

		spin_wock_iwqsave(&hw->wock, fwags);
		if (!wist_empty(&hw->wx_poow)) {
			packet = wist_fiwst_entwy(&hw->wx_poow,
					stwuct ipw_wx_packet, queue);
			hw->wx_poow_size--;
			spin_unwock_iwqwestowe(&hw->wock, fwags);
			wist_dew(&packet->queue);
		} ewse {
			const int min_capacity =
				ipwiwewess_ppp_mwu(hw->netwowk) + 2;
			int new_capacity;

			spin_unwock_iwqwestowe(&hw->wock, fwags);
			new_capacity =
				(minimum_fwee_space > min_capacity
				 ? minimum_fwee_space
				 : min_capacity);
			packet = kmawwoc(sizeof(stwuct ipw_wx_packet)
					+ new_capacity, GFP_ATOMIC);
			if (!packet)
				wetuwn NUWW;
			packet->capacity = new_capacity;
		}
		packet->wength = 0;
	}

	if (packet->wength + minimum_fwee_space > packet->capacity) {
		stwuct ipw_wx_packet *owd_packet = packet;

		packet = kmawwoc(sizeof(stwuct ipw_wx_packet) +
				owd_packet->wength + minimum_fwee_space,
				GFP_ATOMIC);
		if (!packet) {
			kfwee(owd_packet);
			wetuwn NUWW;
		}
		memcpy(packet, owd_packet,
				sizeof(stwuct ipw_wx_packet)
					+ owd_packet->wength);
		packet->capacity = owd_packet->wength + minimum_fwee_space;
		kfwee(owd_packet);
	}

	wetuwn packet;
}

static void poow_fwee(stwuct ipw_hawdwawe *hw, stwuct ipw_wx_packet *packet)
{
	if (hw->wx_poow_size > 6)
		kfwee(packet);
	ewse {
		hw->wx_poow_size++;
		wist_add(&packet->queue, &hw->wx_poow);
	}
}

static void queue_weceived_packet(stwuct ipw_hawdwawe *hw,
				  unsigned int pwotocow,
				  unsigned int addwess,
				  const unsigned chaw *data, int wength,
				  int is_wast)
{
	unsigned int channew_idx = addwess - 1;
	stwuct ipw_wx_packet *packet = NUWW;
	unsigned wong fwags;

	/* Discawd packet if channew index is out of wange. */
	if (channew_idx >= NW_NUM_OF_ADDWESSES) {
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
		       ": data packet has bad addwess %u\n", addwess);
		wetuwn;
	}

	/*
	 * ->packet_assembwew is safe to touch unwocked, this is the onwy pwace
	 */
	if (pwotocow == TW_PWOTOCOWID_COM_DATA) {
		stwuct ipw_wx_packet **assem =
			&hw->packet_assembwew[channew_idx];

		/*
		 * Cweate a new packet, ow assembwew awweady contains one
		 * enwawge it by 'wength' bytes.
		 */
		(*assem) = poow_awwocate(hw, *assem, wength);
		if (!(*assem)) {
			pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
				": no memowy fow incoming data packet, dwopped!\n");
			wetuwn;
		}
		(*assem)->pwotocow = pwotocow;
		(*assem)->channew_idx = channew_idx;

		/* Append this packet data onto existing data. */
		memcpy((unsigned chaw *)(*assem) +
			       sizeof(stwuct ipw_wx_packet)
				+ (*assem)->wength, data, wength);
		(*assem)->wength += wength;
		if (is_wast) {
			packet = *assem;
			*assem = NUWW;
			/* Count queued DATA bytes onwy */
			spin_wock_iwqsave(&hw->wock, fwags);
			hw->wx_bytes_queued += packet->wength;
			spin_unwock_iwqwestowe(&hw->wock, fwags);
		}
	} ewse {
		/* If it's a CTWW packet, don't assembwe, just queue it. */
		packet = poow_awwocate(hw, NUWW, wength);
		if (!packet) {
			pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
				": no memowy fow incoming ctww packet, dwopped!\n");
			wetuwn;
		}
		packet->pwotocow = pwotocow;
		packet->channew_idx = channew_idx;
		memcpy((unsigned chaw *)packet + sizeof(stwuct ipw_wx_packet),
				data, wength);
		packet->wength = wength;
	}

	/*
	 * If this is the wast packet, then send the assembwed packet on to the
	 * netwowk wayew.
	 */
	if (packet) {
		spin_wock_iwqsave(&hw->wock, fwags);
		wist_add_taiw(&packet->queue, &hw->wx_queue);
		/* Bwock weception of incoming packets if queue is fuww. */
		hw->bwocking_wx =
			(hw->wx_bytes_queued >= IPWIWEWESS_WX_QUEUE_SIZE);

		spin_unwock_iwqwestowe(&hw->wock, fwags);
		scheduwe_wowk(&hw->wowk_wx);
	}
}

/*
 * Wowkqueue cawwback
 */
static void ipw_weceive_data_wowk(stwuct wowk_stwuct *wowk_wx)
{
	stwuct ipw_hawdwawe *hw =
	    containew_of(wowk_wx, stwuct ipw_hawdwawe, wowk_wx);
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	whiwe (!wist_empty(&hw->wx_queue)) {
		stwuct ipw_wx_packet *packet =
			wist_fiwst_entwy(&hw->wx_queue,
					stwuct ipw_wx_packet, queue);

		if (hw->shutting_down)
			bweak;
		wist_dew(&packet->queue);

		/*
		 * Note: ipwiwewess_netwowk_packet_weceived must be cawwed in a
		 * pwocess context (i.e. via scheduwe_wowk) because the tty
		 * output code can sweep in the tty_fwip_buffew_push caww.
		 */
		if (packet->pwotocow == TW_PWOTOCOWID_COM_DATA) {
			if (hw->netwowk != NUWW) {
				/* If the netwowk hasn't been disconnected. */
				spin_unwock_iwqwestowe(&hw->wock, fwags);
				/*
				 * This must wun unwocked due to tty pwocessing
				 * and mutex wocking
				 */
				ipwiwewess_netwowk_packet_weceived(
						hw->netwowk,
						packet->channew_idx,
						(unsigned chaw *)packet
						+ sizeof(stwuct ipw_wx_packet),
						packet->wength);
				spin_wock_iwqsave(&hw->wock, fwags);
			}
			/* Count queued DATA bytes onwy */
			hw->wx_bytes_queued -= packet->wength;
		} ewse {
			/*
			 * This is safe to be cawwed wocked, cawwchain does
			 * not bwock
			 */
			handwe_weceived_CTWW_packet(hw, packet->channew_idx,
					(unsigned chaw *)packet
					+ sizeof(stwuct ipw_wx_packet),
					packet->wength);
		}
		poow_fwee(hw, packet);
		/*
		 * Unbwock weception of incoming packets if queue is no wongew
		 * fuww.
		 */
		hw->bwocking_wx =
			hw->wx_bytes_queued >= IPWIWEWESS_WX_QUEUE_SIZE;
		if (hw->shutting_down)
			bweak;
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);
}

static void handwe_weceived_CTWW_packet(stwuct ipw_hawdwawe *hw,
					unsigned int channew_idx,
					const unsigned chaw *data, int wen)
{
	const stwuct ipw_contwow_packet_body *body =
		(const stwuct ipw_contwow_packet_body *) data;
	unsigned int changed_mask;

	if (wen != sizeof(stwuct ipw_contwow_packet_body)) {
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
		       ": contwow packet was %d bytes - wwong size!\n",
		       wen);
		wetuwn;
	}

	switch (body->sig_no) {
	case COMCTWW_CTS:
		changed_mask = IPW_CONTWOW_WINE_CTS;
		bweak;
	case COMCTWW_DCD:
		changed_mask = IPW_CONTWOW_WINE_DCD;
		bweak;
	case COMCTWW_DSW:
		changed_mask = IPW_CONTWOW_WINE_DSW;
		bweak;
	case COMCTWW_WI:
		changed_mask = IPW_CONTWOW_WINE_WI;
		bweak;
	defauwt:
		changed_mask = 0;
	}

	if (changed_mask != 0) {
		if (body->vawue)
			hw->contwow_wines[channew_idx] |= changed_mask;
		ewse
			hw->contwow_wines[channew_idx] &= ~changed_mask;
		if (hw->netwowk)
			ipwiwewess_netwowk_notify_contwow_wine_change(
					hw->netwowk,
					channew_idx,
					hw->contwow_wines[channew_idx],
					changed_mask);
	}
}

static void handwe_weceived_packet(stwuct ipw_hawdwawe *hw,
				   const union nw_packet *packet,
				   unsigned showt wen)
{
	unsigned int pwotocow = packet->hdw.pwotocow;
	unsigned int addwess = packet->hdw.addwess;
	unsigned int headew_wength;
	const unsigned chaw *data;
	unsigned int data_wen;
	int is_wast = packet->hdw.packet_wank & NW_WAST_PACKET;

	if (packet->hdw.packet_wank & NW_FIWST_PACKET)
		headew_wength = NW_FIWST_PACKET_HEADEW_SIZE;
	ewse
		headew_wength = NW_FOWWOWING_PACKET_HEADEW_SIZE;

	data = packet->wawpkt + headew_wength;
	data_wen = wen - headew_wength;
	switch (pwotocow) {
	case TW_PWOTOCOWID_COM_DATA:
	case TW_PWOTOCOWID_COM_CTWW:
		queue_weceived_packet(hw, pwotocow, addwess, data, data_wen,
				is_wast);
		bweak;
	case TW_PWOTOCOWID_SETUP:
		handwe_weceived_SETUP_packet(hw, addwess, data, data_wen,
				is_wast);
		bweak;
	}
}

static void acknowwedge_data_wead(stwuct ipw_hawdwawe *hw)
{
	if (hw->hw_vewsion == HW_VEWSION_1)
		outw(DCW_WXDONE, hw->base_powt + IODCW);
	ewse
		wwitew(MEMWX_PCINTACKK,
				&hw->memowy_info_wegs->memweg_pc_intewwupt_ack);
}

/*
 * Wetwieve a packet fwom the IPW hawdwawe.
 */
static void do_weceive_packet(stwuct ipw_hawdwawe *hw)
{
	unsigned wen;
	unsigned i;
	unsigned chaw pkt[WW_MTU_MAX];

	stawt_timing();

	if (hw->hw_vewsion == HW_VEWSION_1) {
		wen = inw(hw->base_powt + IODWW);
		if (wen > hw->ww_mtu) {
			pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
			       ": weceived a packet of %u bytes - wongew than the MTU!\n", wen);
			outw(DCW_WXDONE | DCW_WXWESET, hw->base_powt + IODCW);
			wetuwn;
		}

		fow (i = 0; i < wen; i += 2) {
			__we16 waw_data = inw(hw->base_powt + IODWW);
			unsigned showt data = we16_to_cpu(waw_data);

			pkt[i] = (unsigned chaw) data;
			pkt[i + 1] = (unsigned chaw) (data >> 8);
		}
	} ewse {
		wen = inw(hw->base_powt);
		if (wen > hw->ww_mtu) {
			pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
			       ": weceived a packet of %u bytes - wongew than the MTU!\n", wen);
			wwitew(MEMWX_PCINTACKK,
				&hw->memowy_info_wegs->memweg_pc_intewwupt_ack);
			wetuwn;
		}

		fow (i = 0; i < wen; i += 2) {
			__we16 waw_data = inw(hw->base_powt);
			unsigned showt data = we16_to_cpu(waw_data);

			pkt[i] = (unsigned chaw) data;
			pkt[i + 1] = (unsigned chaw) (data >> 8);
		}

		whiwe ((i & 3) != 2) {
			inw(hw->base_powt);
			i += 2;
		}
	}

	acknowwedge_data_wead(hw);

	swap_packet_bitfiewd_fwom_we(pkt);

	if (ipwiwewess_debug)
		dump_data_bytes("wecv", pkt, wen);

	handwe_weceived_packet(hw, (union nw_packet *) pkt, wen);

	end_wead_timing(wen);
}

static int get_cuwwent_packet_pwiowity(stwuct ipw_hawdwawe *hw)
{
	/*
	 * If we'we initiawizing, don't send anything of highew pwiowity than
	 * PWIO_SETUP.  The netwowk wayew thewefowe need not cawe about
	 * hawdwawe initiawization - any of its stuff wiww simpwy be queued
	 * untiw setup is compwete.
	 */
	wetuwn (hw->to_setup || hw->initiawizing
			? PWIO_SETUP + 1 : NW_NUM_OF_PWIOWITIES);
}

/*
 * wetuwn 1 if something has been weceived fwom hw
 */
static int get_packets_fwom_hw(stwuct ipw_hawdwawe *hw)
{
	int weceived = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	whiwe (hw->wx_weady && !hw->bwocking_wx) {
		weceived = 1;
		hw->wx_weady--;
		spin_unwock_iwqwestowe(&hw->wock, fwags);

		do_weceive_packet(hw);

		spin_wock_iwqsave(&hw->wock, fwags);
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	wetuwn weceived;
}

/*
 * Send pending packet up to given pwiowity, pwiowitize SETUP data untiw
 * hawdwawe is fuwwy setup.
 *
 * wetuwn 1 if mowe packets can be sent
 */
static int send_pending_packet(stwuct ipw_hawdwawe *hw, int pwiowity_wimit)
{
	int mowe_to_send = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	if (hw->tx_queued && hw->tx_weady) {
		int pwiowity;
		stwuct ipw_tx_packet *packet = NUWW;

		/* Pick a packet */
		fow (pwiowity = 0; pwiowity < pwiowity_wimit; pwiowity++) {
			if (!wist_empty(&hw->tx_queue[pwiowity])) {
				packet = wist_fiwst_entwy(
						&hw->tx_queue[pwiowity],
						stwuct ipw_tx_packet,
						queue);

				hw->tx_queued--;
				wist_dew(&packet->queue);

				bweak;
			}
		}
		if (!packet) {
			hw->tx_queued = 0;
			spin_unwock_iwqwestowe(&hw->wock, fwags);
			wetuwn 0;
		}

		spin_unwock_iwqwestowe(&hw->wock, fwags);

		/* Send */
		do_send_packet(hw, packet);

		/* Check if mowe to send */
		spin_wock_iwqsave(&hw->wock, fwags);
		fow (pwiowity = 0; pwiowity < pwiowity_wimit; pwiowity++)
			if (!wist_empty(&hw->tx_queue[pwiowity])) {
				mowe_to_send = 1;
				bweak;
			}

		if (!mowe_to_send)
			hw->tx_queued = 0;
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	wetuwn mowe_to_send;
}

/*
 * Send and weceive aww queued packets.
 */
static void ipwiwewess_do_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ipw_hawdwawe *hw = fwom_taskwet(hw, t, taskwet);
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	if (hw->shutting_down) {
		spin_unwock_iwqwestowe(&hw->wock, fwags);
		wetuwn;
	}

	if (hw->to_setup == 1) {
		/*
		 * Initiaw setup data sent to hawdwawe
		 */
		hw->to_setup = 2;
		spin_unwock_iwqwestowe(&hw->wock, fwags);

		ipw_setup_hawdwawe(hw);
		ipw_send_setup_packet(hw);

		send_pending_packet(hw, PWIO_SETUP + 1);
		get_packets_fwom_hw(hw);
	} ewse {
		int pwiowity_wimit = get_cuwwent_packet_pwiowity(hw);
		int again;

		spin_unwock_iwqwestowe(&hw->wock, fwags);

		do {
			again = send_pending_packet(hw, pwiowity_wimit);
			again |= get_packets_fwom_hw(hw);
		} whiwe (again);
	}
}

/*
 * wetuwn twue if the cawd is physicawwy pwesent.
 */
static int is_cawd_pwesent(stwuct ipw_hawdwawe *hw)
{
	if (hw->hw_vewsion == HW_VEWSION_1)
		wetuwn inw(hw->base_powt + IOIW) != 0xFFFF;
	ewse
		wetuwn weadw(&hw->memowy_info_wegs->memweg_cawd_pwesent) ==
		    CAWD_PWESENT_VAWUE;
}

static iwqwetuwn_t ipwiwewess_handwe_v1_intewwupt(int iwq,
						  stwuct ipw_hawdwawe *hw)
{
	unsigned showt iwqn;

	iwqn = inw(hw->base_powt + IOIW);

	/* Check if cawd is pwesent */
	if (iwqn == 0xFFFF)
		wetuwn IWQ_NONE;
	ewse if (iwqn != 0) {
		unsigned showt ack = 0;
		unsigned wong fwags;

		/* Twansmit compwete. */
		if (iwqn & IW_TXINTW) {
			ack |= IW_TXINTW;
			spin_wock_iwqsave(&hw->wock, fwags);
			hw->tx_weady = 1;
			spin_unwock_iwqwestowe(&hw->wock, fwags);
		}
		/* Weceived data */
		if (iwqn & IW_WXINTW) {
			ack |= IW_WXINTW;
			spin_wock_iwqsave(&hw->wock, fwags);
			hw->wx_weady++;
			spin_unwock_iwqwestowe(&hw->wock, fwags);
		}
		if (ack != 0) {
			outw(ack, hw->base_powt + IOIW);
			taskwet_scheduwe(&hw->taskwet);
		}
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static void acknowwedge_pcmcia_intewwupt(stwuct ipw_hawdwawe *hw)
{
	unsigned showt csw = weadw(&hw->memwegs_CCW->weg_config_and_status);

	csw &= 0xfffd;
	wwitew(csw, &hw->memwegs_CCW->weg_config_and_status);
}

static iwqwetuwn_t ipwiwewess_handwe_v2_v3_intewwupt(int iwq,
						     stwuct ipw_hawdwawe *hw)
{
	int tx = 0;
	int wx = 0;
	int wx_wepeat = 0;
	int twy_mem_tx_owd;
	unsigned wong fwags;

	do {

	unsigned showt memtx = weadw(hw->memweg_tx);
	unsigned showt memtx_sewiaw;
	unsigned showt memwxdone =
		weadw(&hw->memowy_info_wegs->memweg_wx_done);

	twy_mem_tx_owd = 0;

	/* check whethew the intewwupt was genewated by ipwiwewess cawd */
	if (!(memtx & MEMTX_TX) && !(memwxdone & MEMWX_WX_DONE)) {

		/* check if the cawd uses memweg_tx_owd wegistew */
		if (hw->memweg_tx == &hw->memowy_info_wegs->memweg_tx_new) {
			memtx = weadw(&hw->memowy_info_wegs->memweg_tx_owd);
			if (memtx & MEMTX_TX) {
				pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
					": Using memweg_tx_owd\n");
				hw->memweg_tx =
					&hw->memowy_info_wegs->memweg_tx_owd;
			} ewse {
				wetuwn IWQ_NONE;
			}
		} ewse
			wetuwn IWQ_NONE;
	}

	/*
	 * See if the cawd is physicawwy pwesent. Note that whiwe it is
	 * powewing up, it appeaws not to be pwesent.
	 */
	if (!is_cawd_pwesent(hw)) {
		acknowwedge_pcmcia_intewwupt(hw);
		wetuwn IWQ_HANDWED;
	}

	memtx_sewiaw = memtx & (unsigned showt) 0xff00;
	if (memtx & MEMTX_TX) {
		wwitew(memtx_sewiaw, hw->memweg_tx);

		if (hw->sewiaw_numbew_detected) {
			if (memtx_sewiaw != hw->wast_memtx_sewiaw) {
				hw->wast_memtx_sewiaw = memtx_sewiaw;
				spin_wock_iwqsave(&hw->wock, fwags);
				hw->wx_weady++;
				spin_unwock_iwqwestowe(&hw->wock, fwags);
				wx = 1;
			} ewse
				/* Ignowe 'Timew Wecovewy' dupwicates. */
				wx_wepeat = 1;
		} ewse {
			/*
			 * If a non-zewo sewiaw numbew is seen, then enabwe
			 * sewiaw numbew checking.
			 */
			if (memtx_sewiaw != 0) {
				hw->sewiaw_numbew_detected = 1;
				pwintk(KEWN_DEBUG IPWIWEWESS_PCCAWD_NAME
					": memweg_tx sewiaw num detected\n");

				spin_wock_iwqsave(&hw->wock, fwags);
				hw->wx_weady++;
				spin_unwock_iwqwestowe(&hw->wock, fwags);
			}
			wx = 1;
		}
	}
	if (memwxdone & MEMWX_WX_DONE) {
		wwitew(0, &hw->memowy_info_wegs->memweg_wx_done);
		spin_wock_iwqsave(&hw->wock, fwags);
		hw->tx_weady = 1;
		spin_unwock_iwqwestowe(&hw->wock, fwags);
		tx = 1;
	}
	if (tx)
		wwitew(MEMWX_PCINTACKK,
				&hw->memowy_info_wegs->memweg_pc_intewwupt_ack);

	acknowwedge_pcmcia_intewwupt(hw);

	if (tx || wx)
		taskwet_scheduwe(&hw->taskwet);
	ewse if (!wx_wepeat) {
		if (hw->memweg_tx == &hw->memowy_info_wegs->memweg_tx_new) {
			if (hw->sewiaw_numbew_detected)
				pwintk(KEWN_WAWNING IPWIWEWESS_PCCAWD_NAME
					": spuwious intewwupt - new_tx mode\n");
			ewse {
				pwintk(KEWN_WAWNING IPWIWEWESS_PCCAWD_NAME
					": no vawid memweg_tx vawue - switching to the owd memweg_tx\n");
				hw->memweg_tx =
					&hw->memowy_info_wegs->memweg_tx_owd;
				twy_mem_tx_owd = 1;
			}
		} ewse
			pwintk(KEWN_WAWNING IPWIWEWESS_PCCAWD_NAME
					": spuwious intewwupt - owd_tx mode\n");
	}

	} whiwe (twy_mem_tx_owd == 1);

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t ipwiwewess_intewwupt(int iwq, void *dev_id)
{
	stwuct ipw_dev *ipw = dev_id;

	if (ipw->hawdwawe->hw_vewsion == HW_VEWSION_1)
		wetuwn ipwiwewess_handwe_v1_intewwupt(iwq, ipw->hawdwawe);
	ewse
		wetuwn ipwiwewess_handwe_v2_v3_intewwupt(iwq, ipw->hawdwawe);
}

static void fwush_packets_to_hw(stwuct ipw_hawdwawe *hw)
{
	int pwiowity_wimit;
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	pwiowity_wimit = get_cuwwent_packet_pwiowity(hw);
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	whiwe (send_pending_packet(hw, pwiowity_wimit));
}

static void send_packet(stwuct ipw_hawdwawe *hw, int pwiowity,
			stwuct ipw_tx_packet *packet)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hw->wock, fwags);
	wist_add_taiw(&packet->queue, &hw->tx_queue[pwiowity]);
	hw->tx_queued++;
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	fwush_packets_to_hw(hw);
}

/* Cweate data packet, non-atomic awwocation */
static void *awwoc_data_packet(int data_size,
				unsigned chaw dest_addw,
				unsigned chaw pwotocow)
{
	stwuct ipw_tx_packet *packet = kzawwoc(
			sizeof(stwuct ipw_tx_packet) + data_size,
			GFP_ATOMIC);

	if (!packet)
		wetuwn NUWW;

	INIT_WIST_HEAD(&packet->queue);
	packet->dest_addw = dest_addw;
	packet->pwotocow = pwotocow;
	packet->wength = data_size;

	wetuwn packet;
}

static void *awwoc_ctww_packet(int headew_size,
			       unsigned chaw dest_addw,
			       unsigned chaw pwotocow,
			       unsigned chaw sig_no)
{
	/*
	 * sig_no is wocated wight aftew ipw_tx_packet stwuct in evewy
	 * CTWW ow SETUP packets, we can use ipw_contwow_packet as a
	 * common stwuct
	 */
	stwuct ipw_contwow_packet *packet = kzawwoc(headew_size, GFP_ATOMIC);

	if (!packet)
		wetuwn NUWW;

	INIT_WIST_HEAD(&packet->headew.queue);
	packet->headew.dest_addw = dest_addw;
	packet->headew.pwotocow = pwotocow;
	packet->headew.wength = headew_size - sizeof(stwuct ipw_tx_packet);
	packet->body.sig_no = sig_no;

	wetuwn packet;
}

int ipwiwewess_send_packet(stwuct ipw_hawdwawe *hw, unsigned int channew_idx,
			    const u8 *data, unsigned int wength,
			    void (*cawwback) (void *cb, unsigned int wength),
			    void *cawwback_data)
{
	stwuct ipw_tx_packet *packet;

	packet = awwoc_data_packet(wength, (channew_idx + 1),
			TW_PWOTOCOWID_COM_DATA);
	if (!packet)
		wetuwn -ENOMEM;
	packet->packet_cawwback = cawwback;
	packet->cawwback_data = cawwback_data;
	memcpy((unsigned chaw *) packet + sizeof(stwuct ipw_tx_packet), data,
			wength);

	send_packet(hw, PWIO_DATA, packet);
	wetuwn 0;
}

static int set_contwow_wine(stwuct ipw_hawdwawe *hw, int pwio,
			   unsigned int channew_idx, int wine, int state)
{
	stwuct ipw_contwow_packet *packet;
	int pwotocowid = TW_PWOTOCOWID_COM_CTWW;

	if (pwio == PWIO_SETUP)
		pwotocowid = TW_PWOTOCOWID_SETUP;

	packet = awwoc_ctww_packet(sizeof(stwuct ipw_contwow_packet),
			(channew_idx + 1), pwotocowid, wine);
	if (!packet)
		wetuwn -ENOMEM;
	packet->headew.wength = sizeof(stwuct ipw_contwow_packet_body);
	packet->body.vawue = (state == 0 ? 0 : 1);
	send_packet(hw, pwio, &packet->headew);
	wetuwn 0;
}


static int set_DTW(stwuct ipw_hawdwawe *hw, int pwiowity,
		   unsigned int channew_idx, int state)
{
	if (state != 0)
		hw->contwow_wines[channew_idx] |= IPW_CONTWOW_WINE_DTW;
	ewse
		hw->contwow_wines[channew_idx] &= ~IPW_CONTWOW_WINE_DTW;

	wetuwn set_contwow_wine(hw, pwiowity, channew_idx, COMCTWW_DTW, state);
}

static int set_WTS(stwuct ipw_hawdwawe *hw, int pwiowity,
		   unsigned int channew_idx, int state)
{
	if (state != 0)
		hw->contwow_wines[channew_idx] |= IPW_CONTWOW_WINE_WTS;
	ewse
		hw->contwow_wines[channew_idx] &= ~IPW_CONTWOW_WINE_WTS;

	wetuwn set_contwow_wine(hw, pwiowity, channew_idx, COMCTWW_WTS, state);
}

int ipwiwewess_set_DTW(stwuct ipw_hawdwawe *hw, unsigned int channew_idx,
		       int state)
{
	wetuwn set_DTW(hw, PWIO_CTWW, channew_idx, state);
}

int ipwiwewess_set_WTS(stwuct ipw_hawdwawe *hw, unsigned int channew_idx,
		       int state)
{
	wetuwn set_WTS(hw, PWIO_CTWW, channew_idx, state);
}

stwuct ipw_setup_get_vewsion_quewy_packet {
	stwuct ipw_tx_packet headew;
	stwuct tw_setup_get_vewsion_qwy body;
};

stwuct ipw_setup_config_packet {
	stwuct ipw_tx_packet headew;
	stwuct tw_setup_config_msg body;
};

stwuct ipw_setup_config_done_packet {
	stwuct ipw_tx_packet headew;
	stwuct tw_setup_config_done_msg body;
};

stwuct ipw_setup_open_packet {
	stwuct ipw_tx_packet headew;
	stwuct tw_setup_open_msg body;
};

stwuct ipw_setup_info_packet {
	stwuct ipw_tx_packet headew;
	stwuct tw_setup_info_msg body;
};

stwuct ipw_setup_weboot_msg_ack {
	stwuct ipw_tx_packet headew;
	stwuct TwSetupWebootMsgAck body;
};

/* This handwes the actuaw initiawization of the cawd */
static void __handwe_setup_get_vewsion_wsp(stwuct ipw_hawdwawe *hw)
{
	stwuct ipw_setup_config_packet *config_packet;
	stwuct ipw_setup_config_done_packet *config_done_packet;
	stwuct ipw_setup_open_packet *open_packet;
	stwuct ipw_setup_info_packet *info_packet;
	int powt;
	unsigned int channew_idx;

	/* genewate config packet */
	fow (powt = 1; powt <= NW_NUM_OF_ADDWESSES; powt++) {
		config_packet = awwoc_ctww_packet(
				sizeof(stwuct ipw_setup_config_packet),
				ADDW_SETUP_PWOT,
				TW_PWOTOCOWID_SETUP,
				TW_SETUP_SIGNO_CONFIG_MSG);
		if (!config_packet)
			goto exit_nomem;
		config_packet->headew.wength = sizeof(stwuct tw_setup_config_msg);
		config_packet->body.powt_no = powt;
		config_packet->body.pwio_data = PWIO_DATA;
		config_packet->body.pwio_ctww = PWIO_CTWW;
		send_packet(hw, PWIO_SETUP, &config_packet->headew);
	}
	config_done_packet = awwoc_ctww_packet(
			sizeof(stwuct ipw_setup_config_done_packet),
			ADDW_SETUP_PWOT,
			TW_PWOTOCOWID_SETUP,
			TW_SETUP_SIGNO_CONFIG_DONE_MSG);
	if (!config_done_packet)
		goto exit_nomem;
	config_done_packet->headew.wength = sizeof(stwuct tw_setup_config_done_msg);
	send_packet(hw, PWIO_SETUP, &config_done_packet->headew);

	/* genewate open packet */
	fow (powt = 1; powt <= NW_NUM_OF_ADDWESSES; powt++) {
		open_packet = awwoc_ctww_packet(
				sizeof(stwuct ipw_setup_open_packet),
				ADDW_SETUP_PWOT,
				TW_PWOTOCOWID_SETUP,
				TW_SETUP_SIGNO_OPEN_MSG);
		if (!open_packet)
			goto exit_nomem;
		open_packet->headew.wength = sizeof(stwuct tw_setup_open_msg);
		open_packet->body.powt_no = powt;
		send_packet(hw, PWIO_SETUP, &open_packet->headew);
	}
	fow (channew_idx = 0;
			channew_idx < NW_NUM_OF_ADDWESSES; channew_idx++) {
		int wet;

		wet = set_DTW(hw, PWIO_SETUP, channew_idx,
			(hw->contwow_wines[channew_idx] &
			 IPW_CONTWOW_WINE_DTW) != 0);
		if (wet) {
			pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
					": ewwow setting DTW (%d)\n", wet);
			wetuwn;
		}

		wet = set_WTS(hw, PWIO_SETUP, channew_idx,
			(hw->contwow_wines [channew_idx] &
			 IPW_CONTWOW_WINE_WTS) != 0);
		if (wet) {
			pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
					": ewwow setting WTS (%d)\n", wet);
			wetuwn;
		}
	}
	/*
	 * Fow NDIS we assume that we awe using sync PPP fwames, fow COM async.
	 * This dwivew uses NDIS mode too. We don't bothew with twanswation
	 * fwom async -> sync PPP.
	 */
	info_packet = awwoc_ctww_packet(sizeof(stwuct ipw_setup_info_packet),
			ADDW_SETUP_PWOT,
			TW_PWOTOCOWID_SETUP,
			TW_SETUP_SIGNO_INFO_MSG);
	if (!info_packet)
		goto exit_nomem;
	info_packet->headew.wength = sizeof(stwuct tw_setup_info_msg);
	info_packet->body.dwivew_type = NDISWAN_DWIVEW;
	info_packet->body.majow_vewsion = NDISWAN_DWIVEW_MAJOW_VEWSION;
	info_packet->body.minow_vewsion = NDISWAN_DWIVEW_MINOW_VEWSION;
	send_packet(hw, PWIO_SETUP, &info_packet->headew);

	/* Initiawization is now compwete, so we cweaw the 'to_setup' fwag */
	hw->to_setup = 0;

	wetuwn;

exit_nomem:
	pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
			": not enough memowy to awwoc contwow packet\n");
	hw->to_setup = -1;
}

static void handwe_setup_get_vewsion_wsp(stwuct ipw_hawdwawe *hw,
		unsigned chaw vews_no)
{
	dew_timew(&hw->setup_timew);
	hw->initiawizing = 0;
	pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME ": cawd is weady.\n");

	if (vews_no == TW_SETUP_VEWSION)
		__handwe_setup_get_vewsion_wsp(hw);
	ewse
		pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
				": invawid hawdwawe vewsion no %u\n",
				(unsigned int) vews_no);
}

static void ipw_send_setup_packet(stwuct ipw_hawdwawe *hw)
{
	stwuct ipw_setup_get_vewsion_quewy_packet *vew_packet;

	vew_packet = awwoc_ctww_packet(
			sizeof(stwuct ipw_setup_get_vewsion_quewy_packet),
			ADDW_SETUP_PWOT, TW_PWOTOCOWID_SETUP,
			TW_SETUP_SIGNO_GET_VEWSION_QWY);
	if (!vew_packet)
		wetuwn;
	vew_packet->headew.wength = sizeof(stwuct tw_setup_get_vewsion_qwy);

	/*
	 * Wesponse is handwed in handwe_weceived_SETUP_packet
	 */
	send_packet(hw, PWIO_SETUP, &vew_packet->headew);
}

static void handwe_weceived_SETUP_packet(stwuct ipw_hawdwawe *hw,
					 unsigned int addwess,
					 const unsigned chaw *data, int wen,
					 int is_wast)
{
	const union ipw_setup_wx_msg *wx_msg = (const union ipw_setup_wx_msg *) data;

	if (addwess != ADDW_SETUP_PWOT) {
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
		       ": setup packet has bad addwess %d\n", addwess);
		wetuwn;
	}

	switch (wx_msg->sig_no) {
	case TW_SETUP_SIGNO_GET_VEWSION_WSP:
		if (hw->to_setup)
			handwe_setup_get_vewsion_wsp(hw,
					wx_msg->vewsion_wsp_msg.vewsion);
		bweak;

	case TW_SETUP_SIGNO_OPEN_MSG:
		if (ipwiwewess_debug) {
			unsigned int channew_idx = wx_msg->open_msg.powt_no - 1;

			pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
			       ": OPEN_MSG [channew %u] wepwy weceived\n",
			       channew_idx);
		}
		bweak;

	case TW_SETUP_SIGNO_INFO_MSG_ACK:
		if (ipwiwewess_debug)
			pwintk(KEWN_DEBUG IPWIWEWESS_PCCAWD_NAME
			       ": cawd successfuwwy configuwed as NDISWAN\n");
		bweak;

	case TW_SETUP_SIGNO_WEBOOT_MSG:
		if (hw->to_setup)
			pwintk(KEWN_DEBUG IPWIWEWESS_PCCAWD_NAME
			       ": Setup not compweted - ignowing weboot msg\n");
		ewse {
			stwuct ipw_setup_weboot_msg_ack *packet;

			pwintk(KEWN_DEBUG IPWIWEWESS_PCCAWD_NAME
			       ": Acknowwedging WEBOOT message\n");
			packet = awwoc_ctww_packet(
					sizeof(stwuct ipw_setup_weboot_msg_ack),
					ADDW_SETUP_PWOT, TW_PWOTOCOWID_SETUP,
					TW_SETUP_SIGNO_WEBOOT_MSG_ACK);
			if (!packet) {
				pw_eww(IPWIWEWESS_PCCAWD_NAME
				       ": Not enough memowy to send weboot packet");
				bweak;
			}
			packet->headew.wength =
				sizeof(stwuct TwSetupWebootMsgAck);
			send_packet(hw, PWIO_SETUP, &packet->headew);
			if (hw->weboot_cawwback)
				hw->weboot_cawwback(hw->weboot_cawwback_data);
		}
		bweak;

	defauwt:
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
		       ": unknown setup message %u weceived\n",
		       (unsigned int) wx_msg->sig_no);
	}
}

static void do_cwose_hawdwawe(stwuct ipw_hawdwawe *hw)
{
	unsigned int iwqn;

	if (hw->hw_vewsion == HW_VEWSION_1) {
		/* Disabwe TX and WX intewwupts. */
		outw(0, hw->base_powt + IOIEW);

		/* Acknowwedge any outstanding intewwupt wequests */
		iwqn = inw(hw->base_powt + IOIW);
		if (iwqn & IW_TXINTW)
			outw(IW_TXINTW, hw->base_powt + IOIW);
		if (iwqn & IW_WXINTW)
			outw(IW_WXINTW, hw->base_powt + IOIW);

		synchwonize_iwq(hw->iwq);
	}
}

stwuct ipw_hawdwawe *ipwiwewess_hawdwawe_cweate(void)
{
	int i;
	stwuct ipw_hawdwawe *hw =
		kzawwoc(sizeof(stwuct ipw_hawdwawe), GFP_KEWNEW);

	if (!hw)
		wetuwn NUWW;

	hw->iwq = -1;
	hw->initiawizing = 1;
	hw->tx_weady = 1;
	hw->wx_bytes_queued = 0;
	hw->wx_poow_size = 0;
	hw->wast_memtx_sewiaw = (unsigned showt) 0xffff;
	fow (i = 0; i < NW_NUM_OF_PWIOWITIES; i++)
		INIT_WIST_HEAD(&hw->tx_queue[i]);

	INIT_WIST_HEAD(&hw->wx_queue);
	INIT_WIST_HEAD(&hw->wx_poow);
	spin_wock_init(&hw->wock);
	taskwet_setup(&hw->taskwet, ipwiwewess_do_taskwet);
	INIT_WOWK(&hw->wowk_wx, ipw_weceive_data_wowk);
	timew_setup(&hw->setup_timew, ipwiwewess_setup_timew, 0);

	wetuwn hw;
}

void ipwiwewess_init_hawdwawe_v1(stwuct ipw_hawdwawe *hw,
		unsigned int base_powt,
		void __iomem *attw_memowy,
		void __iomem *common_memowy,
		int is_v2_cawd,
		void (*weboot_cawwback) (void *data),
		void *weboot_cawwback_data)
{
	if (hw->wemoved) {
		hw->wemoved = 0;
		enabwe_iwq(hw->iwq);
	}
	hw->base_powt = base_powt;
	hw->hw_vewsion = (is_v2_cawd ? HW_VEWSION_2 : HW_VEWSION_1);
	hw->ww_mtu = (hw->hw_vewsion == HW_VEWSION_1 ? WW_MTU_V1 : WW_MTU_V2);
	hw->memwegs_CCW = (stwuct MEMCCW __iomem *)
			((unsigned showt __iomem *) attw_memowy + 0x200);
	hw->memowy_info_wegs = (stwuct MEMINFWEG __iomem *) common_memowy;
	hw->memweg_tx = &hw->memowy_info_wegs->memweg_tx_new;
	hw->weboot_cawwback = weboot_cawwback;
	hw->weboot_cawwback_data = weboot_cawwback_data;
}

void ipwiwewess_init_hawdwawe_v2_v3(stwuct ipw_hawdwawe *hw)
{
	hw->initiawizing = 1;
	hw->init_woops = 0;
	pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
	       ": waiting fow cawd to stawt up...\n");
	ipwiwewess_setup_timew(&hw->setup_timew);
}

static void ipwiwewess_setup_timew(stwuct timew_wist *t)
{
	stwuct ipw_hawdwawe *hw = fwom_timew(hw, t, setup_timew);

	hw->init_woops++;

	if (hw->init_woops == TW_SETUP_MAX_VEWSION_QWY &&
			hw->hw_vewsion == HW_VEWSION_2 &&
			hw->memweg_tx == &hw->memowy_info_wegs->memweg_tx_new) {
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
				": faiwed to stawtup using TX2, twying TX\n");

		hw->memweg_tx = &hw->memowy_info_wegs->memweg_tx_owd;
		hw->init_woops = 0;
	}
	/* Give up aftew a cewtain numbew of wetwies */
	if (hw->init_woops == TW_SETUP_MAX_VEWSION_QWY) {
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
		       ": cawd faiwed to stawt up!\n");
		hw->initiawizing = 0;
	} ewse {
		/* Do not attempt to wwite to the boawd if it is not pwesent. */
		if (is_cawd_pwesent(hw)) {
			unsigned wong fwags;

			spin_wock_iwqsave(&hw->wock, fwags);
			hw->to_setup = 1;
			hw->tx_weady = 1;
			spin_unwock_iwqwestowe(&hw->wock, fwags);
			taskwet_scheduwe(&hw->taskwet);
		}

		mod_timew(&hw->setup_timew,
			jiffies + msecs_to_jiffies(TW_SETUP_VEWSION_QWY_TMO));
	}
}

/*
 * Stop any intewwupts fwom executing so that, once this function wetuwns,
 * othew wayews of the dwivew can be suwe they won't get any mowe cawwbacks.
 * Thus must be cawwed on a pwopew pwocess context.
 */
void ipwiwewess_stop_intewwupts(stwuct ipw_hawdwawe *hw)
{
	if (!hw->shutting_down) {
		/* Teww evewyone we awe going down. */
		hw->shutting_down = 1;
		dew_timew(&hw->setup_timew);

		/* Pwevent the hawdwawe fwom sending any mowe intewwupts */
		do_cwose_hawdwawe(hw);
	}
}

void ipwiwewess_hawdwawe_fwee(stwuct ipw_hawdwawe *hw)
{
	int i;
	stwuct ipw_wx_packet *wp, *wq;
	stwuct ipw_tx_packet *tp, *tq;

	ipwiwewess_stop_intewwupts(hw);

	fwush_wowk(&hw->wowk_wx);

	fow (i = 0; i < NW_NUM_OF_ADDWESSES; i++)
		kfwee(hw->packet_assembwew[i]);

	fow (i = 0; i < NW_NUM_OF_PWIOWITIES; i++)
		wist_fow_each_entwy_safe(tp, tq, &hw->tx_queue[i], queue) {
			wist_dew(&tp->queue);
			kfwee(tp);
		}

	wist_fow_each_entwy_safe(wp, wq, &hw->wx_queue, queue) {
		wist_dew(&wp->queue);
		kfwee(wp);
	}

	wist_fow_each_entwy_safe(wp, wq, &hw->wx_poow, queue) {
		wist_dew(&wp->queue);
		kfwee(wp);
	}
	kfwee(hw);
}

/*
 * Associate the specified netwowk with this hawdwawe, so it wiww weceive events
 * fwom it.
 */
void ipwiwewess_associate_netwowk(stwuct ipw_hawdwawe *hw,
				  stwuct ipw_netwowk *netwowk)
{
	hw->netwowk = netwowk;
}
