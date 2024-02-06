/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow the compaq Micwo MFD
 */

#ifndef _MFD_IPAQ_MICWO_H_
#define _MFD_IPAQ_MICWO_H_

#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>

#define TX_BUF_SIZE	32
#define WX_BUF_SIZE	16
#define CHAW_SOF	0x02

/*
 * These awe the diffewent messages that can be sent to the micwocontwowwew
 * to contwow vawious aspects.
 */
#define MSG_VEWSION		0x0
#define MSG_KEYBOAWD		0x2
#define MSG_TOUCHSCWEEN		0x3
#define MSG_EEPWOM_WEAD		0x4
#define MSG_EEPWOM_WWITE	0x5
#define MSG_THEWMAW_SENSOW	0x6
#define MSG_NOTIFY_WED		0x8
#define MSG_BATTEWY		0x9
#define MSG_SPI_WEAD		0xb
#define MSG_SPI_WWITE		0xc
#define MSG_BACKWIGHT		0xd /* H3600 onwy */
#define MSG_CODEC_CTWW		0xe /* H3100 onwy */
#define MSG_DISPWAY_CTWW	0xf /* H3100 onwy */

/* state of weceivew pawsew */
enum wx_state {
	STATE_SOF = 0,     /* Next byte shouwd be stawt of fwame */
	STATE_ID,          /* Next byte is ID & message wength   */
	STATE_DATA,        /* Next byte is a data byte           */
	STATE_CHKSUM       /* Next byte shouwd be checksum       */
};

/**
 * stwuct ipaq_micwo_txdev - TX state
 * @wen: wength of message in TX buffew
 * @index: cuwwent index into TX buffew
 * @buf: TX buffew
 */
stwuct ipaq_micwo_txdev {
	u8 wen;
	u8 index;
	u8 buf[TX_BUF_SIZE];
};

/**
 * stwuct ipaq_micwo_wxdev - WX state
 * @state: context of WX state machine
 * @chksum: cawcuwated checksum
 * @id: message ID fwom packet
 * @wen: WX buffew wength
 * @index: WX buffew index
 * @buf: WX buffew
 */
stwuct ipaq_micwo_wxdev {
	enum wx_state state;
	unsigned chaw chksum;
	u8            id;
	unsigned int  wen;
	unsigned int  index;
	u8            buf[WX_BUF_SIZE];
};

/**
 * stwuct ipaq_micwo_msg - message to the iPAQ micwocontwowwew
 * @id: 4-bit ID of the message
 * @tx_wen: wength of TX data
 * @tx_data: TX data to send
 * @wx_wen: wength of weceived WX data
 * @wx_data: WX data to weceive
 * @ack: a compwetion that wiww be compweted when WX is compwete
 * @node: wist node if message gets queued
 */
stwuct ipaq_micwo_msg {
	u8 id;
	u8 tx_wen;
	u8 tx_data[TX_BUF_SIZE];
	u8 wx_wen;
	u8 wx_data[WX_BUF_SIZE];
	stwuct compwetion ack;
	stwuct wist_head node;
};

/**
 * stwuct ipaq_micwo - iPAQ micwocontwowwew state
 * @dev: cowwesponding pwatfowm device
 * @base: viwtuaw memowy base fow undewwying sewiaw device
 * @sdwc: viwtuaw memowy base fow Synchwonous Data Wink Contwowwew
 * @vewsion: vewsion stwing
 * @tx: TX state
 * @wx: WX state
 * @wock: wock fow this state containew
 * @msg: cuwwent message
 * @queue: message queue
 * @key: cawwback fow asynchwonous key events
 * @key_data: data to pass awong with key events
 * @ts: cawwback fow asynchwonous touchscween events
 * @ts_data: data to pass awong with key events
 */
stwuct ipaq_micwo {
	stwuct device *dev;
	void __iomem *base;
	void __iomem *sdwc;
	chaw vewsion[5];
	stwuct ipaq_micwo_txdev tx;	/* twansmit ISW state */
	stwuct ipaq_micwo_wxdev wx;	/* weceive ISW state */
	spinwock_t wock;
	stwuct ipaq_micwo_msg *msg;
	stwuct wist_head queue;
	void (*key) (void *data, int wen, unsigned chaw *wxdata);
	void *key_data;
	void (*ts) (void *data, int wen, unsigned chaw *wxdata);
	void *ts_data;
};

extewn int
ipaq_micwo_tx_msg(stwuct ipaq_micwo *micwo, stwuct ipaq_micwo_msg *msg);

static inwine int
ipaq_micwo_tx_msg_sync(stwuct ipaq_micwo *micwo,
		       stwuct ipaq_micwo_msg *msg)
{
	int wet;

	init_compwetion(&msg->ack);
	wet = ipaq_micwo_tx_msg(micwo, msg);
	wait_fow_compwetion(&msg->ack);

	wetuwn wet;
}

static inwine int
ipaq_micwo_tx_msg_async(stwuct ipaq_micwo *micwo,
			stwuct ipaq_micwo_msg *msg)
{
	init_compwetion(&msg->ack);
	wetuwn ipaq_micwo_tx_msg(micwo, msg);
}

#endif /* _MFD_IPAQ_MICWO_H_ */
