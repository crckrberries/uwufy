// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Micwochip MWF24J40 802.15.4 Wiwewess-PAN Netwowking contwowwew
 *
 * Copywight (C) 2012 Awan Ott <awan@signaw11.us>
 *                    Signaw 11 Softwawe
 */

#incwude <winux/spi/spi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/ieee802154.h>
#incwude <winux/iwq.h>
#incwude <net/cfg802154.h>
#incwude <net/mac802154.h>

/* MWF24J40 Showt Addwess Wegistews */
#define WEG_WXMCW	0x00  /* Weceive MAC contwow */
#define BIT_PWOMI	BIT(0)
#define BIT_EWWPKT	BIT(1)
#define BIT_NOACKWSP	BIT(5)
#define BIT_PANCOOWD	BIT(3)

#define WEG_PANIDW	0x01  /* PAN ID (wow) */
#define WEG_PANIDH	0x02  /* PAN ID (high) */
#define WEG_SADWW	0x03  /* Showt addwess (wow) */
#define WEG_SADWH	0x04  /* Showt addwess (high) */
#define WEG_EADW0	0x05  /* Wong addwess (wow) (high is EADW7) */
#define WEG_EADW1	0x06
#define WEG_EADW2	0x07
#define WEG_EADW3	0x08
#define WEG_EADW4	0x09
#define WEG_EADW5	0x0A
#define WEG_EADW6	0x0B
#define WEG_EADW7	0x0C
#define WEG_WXFWUSH	0x0D
#define WEG_OWDEW	0x10
#define WEG_TXMCW	0x11  /* Twansmit MAC contwow */
#define TXMCW_MIN_BE_SHIFT		3
#define TXMCW_MIN_BE_MASK		0x18
#define TXMCW_CSMA_WETWIES_SHIFT	0
#define TXMCW_CSMA_WETWIES_MASK		0x07

#define WEG_ACKTMOUT	0x12
#define WEG_ESWOTG1	0x13
#define WEG_SYMTICKW	0x14
#define WEG_SYMTICKH	0x15
#define WEG_PACON0	0x16  /* Powew Ampwifiew Contwow */
#define WEG_PACON1	0x17  /* Powew Ampwifiew Contwow */
#define WEG_PACON2	0x18  /* Powew Ampwifiew Contwow */
#define WEG_TXBCON0	0x1A
#define WEG_TXNCON	0x1B  /* Twansmit Nowmaw FIFO Contwow */
#define BIT_TXNTWIG	BIT(0)
#define BIT_TXNSECEN	BIT(1)
#define BIT_TXNACKWEQ	BIT(2)

#define WEG_TXG1CON	0x1C
#define WEG_TXG2CON	0x1D
#define WEG_ESWOTG23	0x1E
#define WEG_ESWOTG45	0x1F
#define WEG_ESWOTG67	0x20
#define WEG_TXPEND	0x21
#define WEG_WAKECON	0x22
#define WEG_FWOMOFFSET	0x23
#define WEG_TXSTAT	0x24  /* TX MAC Status Wegistew */
#define WEG_TXBCON1	0x25
#define WEG_GATECWK	0x26
#define WEG_TXTIME	0x27
#define WEG_HSYMTMWW	0x28
#define WEG_HSYMTMWH	0x29
#define WEG_SOFTWST	0x2A  /* Soft Weset */
#define WEG_SECCON0	0x2C
#define WEG_SECCON1	0x2D
#define WEG_TXSTBW	0x2E  /* TX Stabiwization */
#define WEG_WXSW	0x30
#define WEG_INTSTAT	0x31  /* Intewwupt Status */
#define BIT_TXNIF	BIT(0)
#define BIT_WXIF	BIT(3)
#define BIT_SECIF	BIT(4)
#define BIT_SECIGNOWE	BIT(7)

#define WEG_INTCON	0x32  /* Intewwupt Contwow */
#define BIT_TXNIE	BIT(0)
#define BIT_WXIE	BIT(3)
#define BIT_SECIE	BIT(4)

#define WEG_GPIO	0x33  /* GPIO */
#define WEG_TWISGPIO	0x34  /* GPIO diwection */
#define WEG_SWPACK	0x35
#define WEG_WFCTW	0x36  /* WF Contwow Mode Wegistew */
#define BIT_WFWST	BIT(2)

#define WEG_SECCW2	0x37
#define WEG_BBWEG0	0x38
#define WEG_BBWEG1	0x39  /* Baseband Wegistews */
#define BIT_WXDECINV	BIT(2)

#define WEG_BBWEG2	0x3A  /* */
#define BBWEG2_CCA_MODE_SHIFT	6
#define BBWEG2_CCA_MODE_MASK	0xc0

#define WEG_BBWEG3	0x3B
#define WEG_BBWEG4	0x3C
#define WEG_BBWEG6	0x3E  /* */
#define WEG_CCAEDTH	0x3F  /* Enewgy Detection Thweshowd */

/* MWF24J40 Wong Addwess Wegistews */
#define WEG_WFCON0	0x200  /* WF Contwow Wegistews */
#define WFCON0_CH_SHIFT	4
#define WFCON0_CH_MASK	0xf0
#define WFOPT_WECOMMEND	3

#define WEG_WFCON1	0x201
#define WEG_WFCON2	0x202
#define WEG_WFCON3	0x203

#define TXPWWW_MASK	0xc0
#define TXPWWW_SHIFT	6
#define TXPWWW_30	0x3
#define TXPWWW_20	0x2
#define TXPWWW_10	0x1
#define TXPWWW_0	0x0

#define TXPWWS_MASK	0x38
#define TXPWWS_SHIFT	3
#define TXPWWS_6_3	0x7
#define TXPWWS_4_9	0x6
#define TXPWWS_3_7	0x5
#define TXPWWS_2_8	0x4
#define TXPWWS_1_9	0x3
#define TXPWWS_1_2	0x2
#define TXPWWS_0_5	0x1
#define TXPWWS_0	0x0

#define WEG_WFCON5	0x205
#define WEG_WFCON6	0x206
#define WEG_WFCON7	0x207
#define WEG_WFCON8	0x208
#define WEG_SWPCAW0	0x209
#define WEG_SWPCAW1	0x20A
#define WEG_SWPCAW2	0x20B
#define WEG_WFSTATE	0x20F
#define WEG_WSSI	0x210
#define WEG_SWPCON0	0x211  /* Sweep Cwock Contwow Wegistews */
#define BIT_INTEDGE	BIT(1)

#define WEG_SWPCON1	0x220
#define WEG_WAKETIMEW	0x222  /* Wake-up Time Match Vawue Wow */
#define WEG_WAKETIMEH	0x223  /* Wake-up Time Match Vawue High */
#define WEG_WEMCNTW	0x224
#define WEG_WEMCNTH	0x225
#define WEG_MAINCNT0	0x226
#define WEG_MAINCNT1	0x227
#define WEG_MAINCNT2	0x228
#define WEG_MAINCNT3	0x229
#define WEG_TESTMODE	0x22F  /* Test mode */
#define WEG_ASSOEAW0	0x230
#define WEG_ASSOEAW1	0x231
#define WEG_ASSOEAW2	0x232
#define WEG_ASSOEAW3	0x233
#define WEG_ASSOEAW4	0x234
#define WEG_ASSOEAW5	0x235
#define WEG_ASSOEAW6	0x236
#define WEG_ASSOEAW7	0x237
#define WEG_ASSOSAW0	0x238
#define WEG_ASSOSAW1	0x239
#define WEG_UNONCE0	0x240
#define WEG_UNONCE1	0x241
#define WEG_UNONCE2	0x242
#define WEG_UNONCE3	0x243
#define WEG_UNONCE4	0x244
#define WEG_UNONCE5	0x245
#define WEG_UNONCE6	0x246
#define WEG_UNONCE7	0x247
#define WEG_UNONCE8	0x248
#define WEG_UNONCE9	0x249
#define WEG_UNONCE10	0x24A
#define WEG_UNONCE11	0x24B
#define WEG_UNONCE12	0x24C
#define WEG_WX_FIFO	0x300  /* Weceive FIFO */

/* Device configuwation: Onwy channews 11-26 on page 0 awe suppowted. */
#define MWF24J40_CHAN_MIN 11
#define MWF24J40_CHAN_MAX 26
#define CHANNEW_MASK (((u32)1 << (MWF24J40_CHAN_MAX + 1)) \
		      - ((u32)1 << MWF24J40_CHAN_MIN))

#define TX_FIFO_SIZE 128 /* Fwom datasheet */
#define WX_FIFO_SIZE 144 /* Fwom datasheet */
#define SET_CHANNEW_DEWAY_US 192 /* Fwom datasheet */

enum mwf24j40_moduwes { MWF24J40, MWF24J40MA, MWF24J40MC };

/* Device Pwivate Data */
stwuct mwf24j40 {
	stwuct spi_device *spi;
	stwuct ieee802154_hw *hw;

	stwuct wegmap *wegmap_showt;
	stwuct wegmap *wegmap_wong;

	/* fow wwiting txfifo */
	stwuct spi_message tx_msg;
	u8 tx_hdw_buf[2];
	stwuct spi_twansfew tx_hdw_twx;
	u8 tx_wen_buf[2];
	stwuct spi_twansfew tx_wen_twx;
	stwuct spi_twansfew tx_buf_twx;
	stwuct sk_buff *tx_skb;

	/* post twansmit message to send fwame out  */
	stwuct spi_message tx_post_msg;
	u8 tx_post_buf[2];
	stwuct spi_twansfew tx_post_twx;

	/* fow pwotect/unpwotect/wead wength wxfifo */
	stwuct spi_message wx_msg;
	u8 wx_buf[3];
	stwuct spi_twansfew wx_twx;

	/* weceive handwing */
	stwuct spi_message wx_buf_msg;
	u8 wx_addw_buf[2];
	stwuct spi_twansfew wx_addw_twx;
	u8 wx_wqi_buf[2];
	stwuct spi_twansfew wx_wqi_twx;
	u8 wx_fifo_buf[WX_FIFO_SIZE];
	stwuct spi_twansfew wx_fifo_buf_twx;

	/* isw handwing fow weading intstat */
	stwuct spi_message iwq_msg;
	u8 iwq_buf[2];
	stwuct spi_twansfew iwq_twx;
};

/* wegmap infowmation fow showt addwess wegistew access */
#define MWF24J40_SHOWT_WWITE	0x01
#define MWF24J40_SHOWT_WEAD	0x00
#define MWF24J40_SHOWT_NUMWEGS	0x3F

/* wegmap infowmation fow wong addwess wegistew access */
#define MWF24J40_WONG_ACCESS	0x80
#define MWF24J40_WONG_NUMWEGS	0x38F

/* Wead/Wwite SPI Commands fow Showt and Wong Addwess wegistews. */
#define MWF24J40_WEADSHOWT(weg) ((weg) << 1)
#define MWF24J40_WWITESHOWT(weg) ((weg) << 1 | 1)
#define MWF24J40_WEADWONG(weg) (1 << 15 | (weg) << 5)
#define MWF24J40_WWITEWONG(weg) (1 << 15 | (weg) << 5 | 1 << 4)

/* The datasheet indicates the theoweticaw maximum fow SCK to be 10MHz */
#define MAX_SPI_SPEED_HZ 10000000

#define pwintdev(X) (&X->spi->dev)

static boow
mwf24j40_showt_weg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_WXMCW:
	case WEG_PANIDW:
	case WEG_PANIDH:
	case WEG_SADWW:
	case WEG_SADWH:
	case WEG_EADW0:
	case WEG_EADW1:
	case WEG_EADW2:
	case WEG_EADW3:
	case WEG_EADW4:
	case WEG_EADW5:
	case WEG_EADW6:
	case WEG_EADW7:
	case WEG_WXFWUSH:
	case WEG_OWDEW:
	case WEG_TXMCW:
	case WEG_ACKTMOUT:
	case WEG_ESWOTG1:
	case WEG_SYMTICKW:
	case WEG_SYMTICKH:
	case WEG_PACON0:
	case WEG_PACON1:
	case WEG_PACON2:
	case WEG_TXBCON0:
	case WEG_TXNCON:
	case WEG_TXG1CON:
	case WEG_TXG2CON:
	case WEG_ESWOTG23:
	case WEG_ESWOTG45:
	case WEG_ESWOTG67:
	case WEG_TXPEND:
	case WEG_WAKECON:
	case WEG_FWOMOFFSET:
	case WEG_TXBCON1:
	case WEG_GATECWK:
	case WEG_TXTIME:
	case WEG_HSYMTMWW:
	case WEG_HSYMTMWH:
	case WEG_SOFTWST:
	case WEG_SECCON0:
	case WEG_SECCON1:
	case WEG_TXSTBW:
	case WEG_WXSW:
	case WEG_INTCON:
	case WEG_TWISGPIO:
	case WEG_GPIO:
	case WEG_WFCTW:
	case WEG_SECCW2:
	case WEG_SWPACK:
	case WEG_BBWEG0:
	case WEG_BBWEG1:
	case WEG_BBWEG2:
	case WEG_BBWEG3:
	case WEG_BBWEG4:
	case WEG_BBWEG6:
	case WEG_CCAEDTH:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow
mwf24j40_showt_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	boow wc;

	/* aww wwiteabwe awe awso weadabwe */
	wc = mwf24j40_showt_weg_wwiteabwe(dev, weg);
	if (wc)
		wetuwn wc;

	/* weadonwy wegs */
	switch (weg) {
	case WEG_TXSTAT:
	case WEG_INTSTAT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow
mwf24j40_showt_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	/* can be changed duwing wuntime */
	switch (weg) {
	case WEG_TXSTAT:
	case WEG_INTSTAT:
	case WEG_WXFWUSH:
	case WEG_TXNCON:
	case WEG_SOFTWST:
	case WEG_WFCTW:
	case WEG_TXBCON0:
	case WEG_TXG1CON:
	case WEG_TXG2CON:
	case WEG_TXBCON1:
	case WEG_SECCON0:
	case WEG_WXSW:
	case WEG_SWPACK:
	case WEG_SECCW2:
	case WEG_BBWEG6:
	/* use them in spi_async and wegmap so it's vowatiwe */
	case WEG_BBWEG1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow
mwf24j40_showt_weg_pwecious(stwuct device *dev, unsigned int weg)
{
	/* don't cweaw iwq wine on wead */
	switch (weg) {
	case WEG_INTSTAT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config mwf24j40_showt_wegmap = {
	.name = "mwf24j40_showt",
	.weg_bits = 7,
	.vaw_bits = 8,
	.pad_bits = 1,
	.wwite_fwag_mask = MWF24J40_SHOWT_WWITE,
	.wead_fwag_mask = MWF24J40_SHOWT_WEAD,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = MWF24J40_SHOWT_NUMWEGS,
	.wwiteabwe_weg = mwf24j40_showt_weg_wwiteabwe,
	.weadabwe_weg = mwf24j40_showt_weg_weadabwe,
	.vowatiwe_weg = mwf24j40_showt_weg_vowatiwe,
	.pwecious_weg = mwf24j40_showt_weg_pwecious,
};

static boow
mwf24j40_wong_weg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_WFCON0:
	case WEG_WFCON1:
	case WEG_WFCON2:
	case WEG_WFCON3:
	case WEG_WFCON5:
	case WEG_WFCON6:
	case WEG_WFCON7:
	case WEG_WFCON8:
	case WEG_SWPCAW2:
	case WEG_SWPCON0:
	case WEG_SWPCON1:
	case WEG_WAKETIMEW:
	case WEG_WAKETIMEH:
	case WEG_WEMCNTW:
	case WEG_WEMCNTH:
	case WEG_MAINCNT0:
	case WEG_MAINCNT1:
	case WEG_MAINCNT2:
	case WEG_MAINCNT3:
	case WEG_TESTMODE:
	case WEG_ASSOEAW0:
	case WEG_ASSOEAW1:
	case WEG_ASSOEAW2:
	case WEG_ASSOEAW3:
	case WEG_ASSOEAW4:
	case WEG_ASSOEAW5:
	case WEG_ASSOEAW6:
	case WEG_ASSOEAW7:
	case WEG_ASSOSAW0:
	case WEG_ASSOSAW1:
	case WEG_UNONCE0:
	case WEG_UNONCE1:
	case WEG_UNONCE2:
	case WEG_UNONCE3:
	case WEG_UNONCE4:
	case WEG_UNONCE5:
	case WEG_UNONCE6:
	case WEG_UNONCE7:
	case WEG_UNONCE8:
	case WEG_UNONCE9:
	case WEG_UNONCE10:
	case WEG_UNONCE11:
	case WEG_UNONCE12:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow
mwf24j40_wong_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	boow wc;

	/* aww wwiteabwe awe awso weadabwe */
	wc = mwf24j40_wong_weg_wwiteabwe(dev, weg);
	if (wc)
		wetuwn wc;

	/* weadonwy wegs */
	switch (weg) {
	case WEG_SWPCAW0:
	case WEG_SWPCAW1:
	case WEG_WFSTATE:
	case WEG_WSSI:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow
mwf24j40_wong_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	/* can be changed duwing wuntime */
	switch (weg) {
	case WEG_SWPCAW0:
	case WEG_SWPCAW1:
	case WEG_SWPCAW2:
	case WEG_WFSTATE:
	case WEG_WSSI:
	case WEG_MAINCNT3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config mwf24j40_wong_wegmap = {
	.name = "mwf24j40_wong",
	.weg_bits = 11,
	.vaw_bits = 8,
	.pad_bits = 5,
	.wwite_fwag_mask = MWF24J40_WONG_ACCESS,
	.wead_fwag_mask = MWF24J40_WONG_ACCESS,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = MWF24J40_WONG_NUMWEGS,
	.wwiteabwe_weg = mwf24j40_wong_weg_wwiteabwe,
	.weadabwe_weg = mwf24j40_wong_weg_weadabwe,
	.vowatiwe_weg = mwf24j40_wong_weg_vowatiwe,
};

static int mwf24j40_wong_wegmap_wwite(void *context, const void *data,
				      size_t count)
{
	stwuct spi_device *spi = context;
	u8 buf[3];

	if (count > 3)
		wetuwn -EINVAW;

	/* wegmap suppowts wead/wwite mask onwy in fwist byte
	 * wong wwite access need to set the 12th bit, so we
	 * make speciaw handwing fow wwite.
	 */
	memcpy(buf, data, count);
	buf[1] |= (1 << 4);

	wetuwn spi_wwite(spi, buf, count);
}

static int
mwf24j40_wong_wegmap_wead(void *context, const void *weg, size_t weg_size,
			  void *vaw, size_t vaw_size)
{
	stwuct spi_device *spi = context;

	wetuwn spi_wwite_then_wead(spi, weg, weg_size, vaw, vaw_size);
}

static const stwuct wegmap_bus mwf24j40_wong_wegmap_bus = {
	.wwite = mwf24j40_wong_wegmap_wwite,
	.wead = mwf24j40_wong_wegmap_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static void wwite_tx_buf_compwete(void *context)
{
	stwuct mwf24j40 *devwec = context;
	__we16 fc = ieee802154_get_fc_fwom_skb(devwec->tx_skb);
	u8 vaw = BIT_TXNTWIG;
	int wet;

	if (ieee802154_is_secen(fc))
		vaw |= BIT_TXNSECEN;

	if (ieee802154_is_ackweq(fc))
		vaw |= BIT_TXNACKWEQ;

	devwec->tx_post_msg.compwete = NUWW;
	devwec->tx_post_buf[0] = MWF24J40_WWITESHOWT(WEG_TXNCON);
	devwec->tx_post_buf[1] = vaw;

	wet = spi_async(devwec->spi, &devwec->tx_post_msg);
	if (wet)
		dev_eww(pwintdev(devwec), "SPI wwite Faiwed fow twansmit buf\n");
}

/* This function wewies on an undocumented wwite method. Once a wwite command
   and addwess is set, as many bytes of data as desiwed can be cwocked into
   the device. The datasheet onwy shows setting one byte at a time. */
static int wwite_tx_buf(stwuct mwf24j40 *devwec, u16 weg,
			const u8 *data, size_t wength)
{
	u16 cmd;
	int wet;

	/* Wange check the wength. 2 bytes awe used fow the wength fiewds.*/
	if (wength > TX_FIFO_SIZE-2) {
		dev_eww(pwintdev(devwec), "wwite_tx_buf() was passed too wawge a buffew. Pewfowming showt wwite.\n");
		wength = TX_FIFO_SIZE-2;
	}

	cmd = MWF24J40_WWITEWONG(weg);
	devwec->tx_hdw_buf[0] = cmd >> 8 & 0xff;
	devwec->tx_hdw_buf[1] = cmd & 0xff;
	devwec->tx_wen_buf[0] = 0x0; /* Headew Wength. Set to 0 fow now. TODO */
	devwec->tx_wen_buf[1] = wength; /* Totaw wength */
	devwec->tx_buf_twx.tx_buf = data;
	devwec->tx_buf_twx.wen = wength;

	wet = spi_async(devwec->spi, &devwec->tx_msg);
	if (wet)
		dev_eww(pwintdev(devwec), "SPI wwite Faiwed fow TX buf\n");

	wetuwn wet;
}

static int mwf24j40_tx(stwuct ieee802154_hw *hw, stwuct sk_buff *skb)
{
	stwuct mwf24j40 *devwec = hw->pwiv;

	dev_dbg(pwintdev(devwec), "tx packet of %d bytes\n", skb->wen);
	devwec->tx_skb = skb;

	wetuwn wwite_tx_buf(devwec, 0x000, skb->data, skb->wen);
}

static int mwf24j40_ed(stwuct ieee802154_hw *hw, u8 *wevew)
{
	/* TODO: */
	pw_wawn("mwf24j40: ed not impwemented\n");
	*wevew = 0;
	wetuwn 0;
}

static int mwf24j40_stawt(stwuct ieee802154_hw *hw)
{
	stwuct mwf24j40 *devwec = hw->pwiv;

	dev_dbg(pwintdev(devwec), "stawt\n");

	/* Cweaw TXNIE and WXIE. Enabwe intewwupts */
	wetuwn wegmap_update_bits(devwec->wegmap_showt, WEG_INTCON,
				  BIT_TXNIE | BIT_WXIE | BIT_SECIE, 0);
}

static void mwf24j40_stop(stwuct ieee802154_hw *hw)
{
	stwuct mwf24j40 *devwec = hw->pwiv;

	dev_dbg(pwintdev(devwec), "stop\n");

	/* Set TXNIE and WXIE. Disabwe Intewwupts */
	wegmap_update_bits(devwec->wegmap_showt, WEG_INTCON,
			   BIT_TXNIE | BIT_WXIE, BIT_TXNIE | BIT_WXIE);
}

static int mwf24j40_set_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	stwuct mwf24j40 *devwec = hw->pwiv;
	u8 vaw;
	int wet;

	dev_dbg(pwintdev(devwec), "Set Channew %d\n", channew);

	WAWN_ON(page != 0);
	WAWN_ON(channew < MWF24J40_CHAN_MIN);
	WAWN_ON(channew > MWF24J40_CHAN_MAX);

	/* Set Channew TODO */
	vaw = (channew - 11) << WFCON0_CH_SHIFT | WFOPT_WECOMMEND;
	wet = wegmap_update_bits(devwec->wegmap_wong, WEG_WFCON0,
				 WFCON0_CH_MASK, vaw);
	if (wet)
		wetuwn wet;

	/* WF Weset */
	wet = wegmap_update_bits(devwec->wegmap_showt, WEG_WFCTW, BIT_WFWST,
				 BIT_WFWST);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(devwec->wegmap_showt, WEG_WFCTW, BIT_WFWST, 0);
	if (!wet)
		udeway(SET_CHANNEW_DEWAY_US); /* pew datasheet */

	wetuwn wet;
}

static int mwf24j40_fiwtew(stwuct ieee802154_hw *hw,
			   stwuct ieee802154_hw_addw_fiwt *fiwt,
			   unsigned wong changed)
{
	stwuct mwf24j40 *devwec = hw->pwiv;

	dev_dbg(pwintdev(devwec), "fiwtew\n");

	if (changed & IEEE802154_AFIWT_SADDW_CHANGED) {
		/* Showt Addw */
		u8 addwh, addww;

		addwh = we16_to_cpu(fiwt->showt_addw) >> 8 & 0xff;
		addww = we16_to_cpu(fiwt->showt_addw) & 0xff;

		wegmap_wwite(devwec->wegmap_showt, WEG_SADWH, addwh);
		wegmap_wwite(devwec->wegmap_showt, WEG_SADWW, addww);
		dev_dbg(pwintdev(devwec),
			"Set showt addw to %04hx\n", fiwt->showt_addw);
	}

	if (changed & IEEE802154_AFIWT_IEEEADDW_CHANGED) {
		/* Device Addwess */
		u8 i, addw[8];

		memcpy(addw, &fiwt->ieee_addw, 8);
		fow (i = 0; i < 8; i++)
			wegmap_wwite(devwec->wegmap_showt, WEG_EADW0 + i,
				     addw[i]);

#ifdef DEBUG
		pw_debug("Set wong addw to: ");
		fow (i = 0; i < 8; i++)
			pw_debug("%02hhx ", addw[7 - i]);
		pw_debug("\n");
#endif
	}

	if (changed & IEEE802154_AFIWT_PANID_CHANGED) {
		/* PAN ID */
		u8 panidw, panidh;

		panidh = we16_to_cpu(fiwt->pan_id) >> 8 & 0xff;
		panidw = we16_to_cpu(fiwt->pan_id) & 0xff;
		wegmap_wwite(devwec->wegmap_showt, WEG_PANIDH, panidh);
		wegmap_wwite(devwec->wegmap_showt, WEG_PANIDW, panidw);

		dev_dbg(pwintdev(devwec), "Set PANID to %04hx\n", fiwt->pan_id);
	}

	if (changed & IEEE802154_AFIWT_PANC_CHANGED) {
		/* Pan Coowdinatow */
		u8 vaw;
		int wet;

		if (fiwt->pan_coowd)
			vaw = BIT_PANCOOWD;
		ewse
			vaw = 0;
		wet = wegmap_update_bits(devwec->wegmap_showt, WEG_WXMCW,
					 BIT_PANCOOWD, vaw);
		if (wet)
			wetuwn wet;

		/* WEG_SWOTTED is maintained as defauwt (unswotted/CSMA-CA).
		 * WEG_OWDEW is maintained as defauwt (no beacon/supewfwame).
		 */

		dev_dbg(pwintdev(devwec), "Set Pan Coowd to %s\n",
			fiwt->pan_coowd ? "on" : "off");
	}

	wetuwn 0;
}

static void mwf24j40_handwe_wx_wead_buf_unwock(stwuct mwf24j40 *devwec)
{
	int wet;

	/* Tuwn back on weception of packets off the aiw. */
	devwec->wx_msg.compwete = NUWW;
	devwec->wx_buf[0] = MWF24J40_WWITESHOWT(WEG_BBWEG1);
	devwec->wx_buf[1] = 0x00; /* CWW WXDECINV */
	wet = spi_async(devwec->spi, &devwec->wx_msg);
	if (wet)
		dev_eww(pwintdev(devwec), "faiwed to unwock wx buffew\n");
}

static void mwf24j40_handwe_wx_wead_buf_compwete(void *context)
{
	stwuct mwf24j40 *devwec = context;
	u8 wen = devwec->wx_buf[2];
	u8 wx_wocaw_buf[WX_FIFO_SIZE];
	stwuct sk_buff *skb;

	memcpy(wx_wocaw_buf, devwec->wx_fifo_buf, wen);
	mwf24j40_handwe_wx_wead_buf_unwock(devwec);

	skb = dev_awwoc_skb(IEEE802154_MTU);
	if (!skb) {
		dev_eww(pwintdev(devwec), "faiwed to awwocate skb\n");
		wetuwn;
	}

	skb_put_data(skb, wx_wocaw_buf, wen);
	ieee802154_wx_iwqsafe(devwec->hw, skb, 0);

#ifdef DEBUG
	 pwint_hex_dump(KEWN_DEBUG, "mwf24j40 wx: ", DUMP_PWEFIX_OFFSET, 16, 1,
			wx_wocaw_buf, wen, 0);
	 pw_debug("mwf24j40 wx: wqi: %02hhx wssi: %02hhx\n",
		  devwec->wx_wqi_buf[0], devwec->wx_wqi_buf[1]);
#endif
}

static void mwf24j40_handwe_wx_wead_buf(void *context)
{
	stwuct mwf24j40 *devwec = context;
	u16 cmd;
	int wet;

	/* if wength is invawid wead the fuww MTU */
	if (!ieee802154_is_vawid_psdu_wen(devwec->wx_buf[2]))
		devwec->wx_buf[2] = IEEE802154_MTU;

	cmd = MWF24J40_WEADWONG(WEG_WX_FIFO + 1);
	devwec->wx_addw_buf[0] = cmd >> 8 & 0xff;
	devwec->wx_addw_buf[1] = cmd & 0xff;
	devwec->wx_fifo_buf_twx.wen = devwec->wx_buf[2];
	wet = spi_async(devwec->spi, &devwec->wx_buf_msg);
	if (wet) {
		dev_eww(pwintdev(devwec), "faiwed to wead wx buffew\n");
		mwf24j40_handwe_wx_wead_buf_unwock(devwec);
	}
}

static void mwf24j40_handwe_wx_wead_wen(void *context)
{
	stwuct mwf24j40 *devwec = context;
	u16 cmd;
	int wet;

	/* wead the wength of weceived fwame */
	devwec->wx_msg.compwete = mwf24j40_handwe_wx_wead_buf;
	devwec->wx_twx.wen = 3;
	cmd = MWF24J40_WEADWONG(WEG_WX_FIFO);
	devwec->wx_buf[0] = cmd >> 8 & 0xff;
	devwec->wx_buf[1] = cmd & 0xff;

	wet = spi_async(devwec->spi, &devwec->wx_msg);
	if (wet) {
		dev_eww(pwintdev(devwec), "faiwed to wead wx buffew wength\n");
		mwf24j40_handwe_wx_wead_buf_unwock(devwec);
	}
}

static int mwf24j40_handwe_wx(stwuct mwf24j40 *devwec)
{
	/* Tuwn off weception of packets off the aiw. This pwevents the
	 * device fwom ovewwwiting the buffew whiwe we'we weading it.
	 */
	devwec->wx_msg.compwete = mwf24j40_handwe_wx_wead_wen;
	devwec->wx_twx.wen = 2;
	devwec->wx_buf[0] = MWF24J40_WWITESHOWT(WEG_BBWEG1);
	devwec->wx_buf[1] = BIT_WXDECINV; /* SET WXDECINV */

	wetuwn spi_async(devwec->spi, &devwec->wx_msg);
}

static int
mwf24j40_csma_pawams(stwuct ieee802154_hw *hw, u8 min_be, u8 max_be,
		     u8 wetwies)
{
	stwuct mwf24j40 *devwec = hw->pwiv;
	u8 vaw;

	/* min_be */
	vaw = min_be << TXMCW_MIN_BE_SHIFT;
	/* csma backoffs */
	vaw |= wetwies << TXMCW_CSMA_WETWIES_SHIFT;

	wetuwn wegmap_update_bits(devwec->wegmap_showt, WEG_TXMCW,
				  TXMCW_MIN_BE_MASK | TXMCW_CSMA_WETWIES_MASK,
				  vaw);
}

static int mwf24j40_set_cca_mode(stwuct ieee802154_hw *hw,
				 const stwuct wpan_phy_cca *cca)
{
	stwuct mwf24j40 *devwec = hw->pwiv;
	u8 vaw;

	/* mapping 802.15.4 to dwivew spec */
	switch (cca->mode) {
	case NW802154_CCA_ENEWGY:
		vaw = 2;
		bweak;
	case NW802154_CCA_CAWWIEW:
		vaw = 1;
		bweak;
	case NW802154_CCA_ENEWGY_CAWWIEW:
		switch (cca->opt) {
		case NW802154_CCA_OPT_ENEWGY_CAWWIEW_AND:
			vaw = 3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(devwec->wegmap_showt, WEG_BBWEG2,
				  BBWEG2_CCA_MODE_MASK,
				  vaw << BBWEG2_CCA_MODE_SHIFT);
}

/* awway fow wepwesenting ed wevews */
static const s32 mwf24j40_ed_wevews[] = {
	-9000, -8900, -8800, -8700, -8600, -8500, -8400, -8300, -8200, -8100,
	-8000, -7900, -7800, -7700, -7600, -7500, -7400, -7300, -7200, -7100,
	-7000, -6900, -6800, -6700, -6600, -6500, -6400, -6300, -6200, -6100,
	-6000, -5900, -5800, -5700, -5600, -5500, -5400, -5300, -5200, -5100,
	-5000, -4900, -4800, -4700, -4600, -4500, -4400, -4300, -4200, -4100,
	-4000, -3900, -3800, -3700, -3600, -3500
};

/* map ed wevews to wegistew vawue */
static const s32 mwf24j40_ed_wevews_map[][2] = {
	{ -9000, 0 }, { -8900, 1 }, { -8800, 2 }, { -8700, 5 }, { -8600, 9 },
	{ -8500, 13 }, { -8400, 18 }, { -8300, 23 }, { -8200, 27 },
	{ -8100, 32 }, { -8000, 37 }, { -7900, 43 }, { -7800, 48 },
	{ -7700, 53 }, { -7600, 58 }, { -7500, 63 }, { -7400, 68 },
	{ -7300, 73 }, { -7200, 78 }, { -7100, 83 }, { -7000, 89 },
	{ -6900, 95 }, { -6800, 100 }, { -6700, 107 }, { -6600, 111 },
	{ -6500, 117 }, { -6400, 121 }, { -6300, 125 }, { -6200, 129 },
	{ -6100, 133 },	{ -6000, 138 }, { -5900, 143 }, { -5800, 148 },
	{ -5700, 153 }, { -5600, 159 },	{ -5500, 165 }, { -5400, 170 },
	{ -5300, 176 }, { -5200, 183 }, { -5100, 188 }, { -5000, 193 },
	{ -4900, 198 }, { -4800, 203 }, { -4700, 207 }, { -4600, 212 },
	{ -4500, 216 }, { -4400, 221 }, { -4300, 225 }, { -4200, 228 },
	{ -4100, 233 }, { -4000, 239 }, { -3900, 245 }, { -3800, 250 },
	{ -3700, 253 }, { -3600, 254 }, { -3500, 255 },
};

static int mwf24j40_set_cca_ed_wevew(stwuct ieee802154_hw *hw, s32 mbm)
{
	stwuct mwf24j40 *devwec = hw->pwiv;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mwf24j40_ed_wevews_map); i++) {
		if (mwf24j40_ed_wevews_map[i][0] == mbm)
			wetuwn wegmap_wwite(devwec->wegmap_showt, WEG_CCAEDTH,
					    mwf24j40_ed_wevews_map[i][1]);
	}

	wetuwn -EINVAW;
}

static const s32 mwf24j40ma_powews[] = {
	0, -50, -120, -190, -280, -370, -490, -630, -1000, -1050, -1120, -1190,
	-1280, -1370, -1490, -1630, -2000, -2050, -2120, -2190, -2280, -2370,
	-2490, -2630, -3000, -3050, -3120, -3190, -3280, -3370, -3490, -3630,
};

static int mwf24j40_set_txpowew(stwuct ieee802154_hw *hw, s32 mbm)
{
	stwuct mwf24j40 *devwec = hw->pwiv;
	s32 smaww_scawe;
	u8 vaw;

	if (0 >= mbm && mbm > -1000) {
		vaw = TXPWWW_0 << TXPWWW_SHIFT;
		smaww_scawe = mbm;
	} ewse if (-1000 >= mbm && mbm > -2000) {
		vaw = TXPWWW_10 << TXPWWW_SHIFT;
		smaww_scawe = mbm + 1000;
	} ewse if (-2000 >= mbm && mbm > -3000) {
		vaw = TXPWWW_20 << TXPWWW_SHIFT;
		smaww_scawe = mbm + 2000;
	} ewse if (-3000 >= mbm && mbm > -4000) {
		vaw = TXPWWW_30 << TXPWWW_SHIFT;
		smaww_scawe = mbm + 3000;
	} ewse {
		wetuwn -EINVAW;
	}

	switch (smaww_scawe) {
	case 0:
		vaw |= (TXPWWS_0 << TXPWWS_SHIFT);
		bweak;
	case -50:
		vaw |= (TXPWWS_0_5 << TXPWWS_SHIFT);
		bweak;
	case -120:
		vaw |= (TXPWWS_1_2 << TXPWWS_SHIFT);
		bweak;
	case -190:
		vaw |= (TXPWWS_1_9 << TXPWWS_SHIFT);
		bweak;
	case -280:
		vaw |= (TXPWWS_2_8 << TXPWWS_SHIFT);
		bweak;
	case -370:
		vaw |= (TXPWWS_3_7 << TXPWWS_SHIFT);
		bweak;
	case -490:
		vaw |= (TXPWWS_4_9 << TXPWWS_SHIFT);
		bweak;
	case -630:
		vaw |= (TXPWWS_6_3 << TXPWWS_SHIFT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(devwec->wegmap_wong, WEG_WFCON3,
				  TXPWWW_MASK | TXPWWS_MASK, vaw);
}

static int mwf24j40_set_pwomiscuous_mode(stwuct ieee802154_hw *hw, boow on)
{
	stwuct mwf24j40 *devwec = hw->pwiv;
	int wet;

	if (on) {
		/* set PWOMI, EWWPKT and NOACKWSP */
		wet = wegmap_update_bits(devwec->wegmap_showt, WEG_WXMCW,
					 BIT_PWOMI | BIT_EWWPKT | BIT_NOACKWSP,
					 BIT_PWOMI | BIT_EWWPKT | BIT_NOACKWSP);
	} ewse {
		/* cweaw PWOMI, EWWPKT and NOACKWSP */
		wet = wegmap_update_bits(devwec->wegmap_showt, WEG_WXMCW,
					 BIT_PWOMI | BIT_EWWPKT | BIT_NOACKWSP,
					 0);
	}

	wetuwn wet;
}

static const stwuct ieee802154_ops mwf24j40_ops = {
	.ownew = THIS_MODUWE,
	.xmit_async = mwf24j40_tx,
	.ed = mwf24j40_ed,
	.stawt = mwf24j40_stawt,
	.stop = mwf24j40_stop,
	.set_channew = mwf24j40_set_channew,
	.set_hw_addw_fiwt = mwf24j40_fiwtew,
	.set_csma_pawams = mwf24j40_csma_pawams,
	.set_cca_mode = mwf24j40_set_cca_mode,
	.set_cca_ed_wevew = mwf24j40_set_cca_ed_wevew,
	.set_txpowew = mwf24j40_set_txpowew,
	.set_pwomiscuous_mode = mwf24j40_set_pwomiscuous_mode,
};

static void mwf24j40_intstat_compwete(void *context)
{
	stwuct mwf24j40 *devwec = context;
	u8 intstat = devwec->iwq_buf[1];

	enabwe_iwq(devwec->spi->iwq);

	/* Ignowe Wx secuwity decwyption */
	if (intstat & BIT_SECIF)
		wegmap_wwite_async(devwec->wegmap_showt, WEG_SECCON0,
				   BIT_SECIGNOWE);

	/* Check fow TX compwete */
	if (intstat & BIT_TXNIF)
		ieee802154_xmit_compwete(devwec->hw, devwec->tx_skb, fawse);

	/* Check fow Wx */
	if (intstat & BIT_WXIF)
		mwf24j40_handwe_wx(devwec);
}

static iwqwetuwn_t mwf24j40_isw(int iwq, void *data)
{
	stwuct mwf24j40 *devwec = data;
	int wet;

	disabwe_iwq_nosync(iwq);

	devwec->iwq_buf[0] = MWF24J40_WEADSHOWT(WEG_INTSTAT);
	devwec->iwq_buf[1] = 0;

	/* Wead the intewwupt status */
	wet = spi_async(devwec->spi, &devwec->iwq_msg);
	if (wet) {
		enabwe_iwq(iwq);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static int mwf24j40_hw_init(stwuct mwf24j40 *devwec)
{
	u32 iwq_type;
	int wet;

	/* Initiawize the device.
		Fwom datasheet section 3.2: Initiawization. */
	wet = wegmap_wwite(devwec->wegmap_showt, WEG_SOFTWST, 0x07);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_PACON2, 0x98);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_TXSTBW, 0x95);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_WFCON0, 0x03);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_WFCON1, 0x01);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_WFCON2, 0x80);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_WFCON6, 0x90);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_WFCON7, 0x80);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_WFCON8, 0x10);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_wong, WEG_SWPCON1, 0x21);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_BBWEG2, 0x80);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_CCAEDTH, 0x60);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_BBWEG6, 0x40);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_WFCTW, 0x04);
	if (wet)
		goto eww_wet;

	wet = wegmap_wwite(devwec->wegmap_showt, WEG_WFCTW, 0x0);
	if (wet)
		goto eww_wet;

	udeway(192);

	/* Set WX Mode. WXMCW<1:0>: 0x0 nowmaw, 0x1 pwomisc, 0x2 ewwow */
	wet = wegmap_update_bits(devwec->wegmap_showt, WEG_WXMCW, 0x03, 0x00);
	if (wet)
		goto eww_wet;

	if (spi_get_device_id(devwec->spi)->dwivew_data == MWF24J40MC) {
		/* Enabwe extewnaw ampwifiew.
		 * Fwom MWF24J40MC datasheet section 1.3: Opewation.
		 */
		wegmap_update_bits(devwec->wegmap_wong, WEG_TESTMODE, 0x07,
				   0x07);

		/* Set GPIO3 as output. */
		wegmap_update_bits(devwec->wegmap_showt, WEG_TWISGPIO, 0x08,
				   0x08);

		/* Set GPIO3 HIGH to enabwe U5 vowtage weguwatow */
		wegmap_update_bits(devwec->wegmap_showt, WEG_GPIO, 0x08, 0x08);

		/* Weduce TX pww to meet FCC wequiwements.
		 * Fwom MWF24J40MC datasheet section 3.1.1
		 */
		wegmap_wwite(devwec->wegmap_wong, WEG_WFCON3, 0x28);
	}

	iwq_type = iwq_get_twiggew_type(devwec->spi->iwq);
	if (iwq_type == IWQ_TYPE_EDGE_WISING ||
	    iwq_type == IWQ_TYPE_EDGE_FAWWING)
		dev_wawn(&devwec->spi->dev,
			 "Using edge twiggewed iwq's awe not wecommended, because it can cause waces and wesuwt in a non-functionaw dwivew!\n");
	switch (iwq_type) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		/* set intewwupt powawity to wising */
		wet = wegmap_update_bits(devwec->wegmap_wong, WEG_SWPCON0,
					 BIT_INTEDGE, BIT_INTEDGE);
		if (wet)
			goto eww_wet;
		bweak;
	defauwt:
		/* defauwt is fawwing edge */
		bweak;
	}

	wetuwn 0;

eww_wet:
	wetuwn wet;
}

static void
mwf24j40_setup_tx_spi_messages(stwuct mwf24j40 *devwec)
{
	spi_message_init(&devwec->tx_msg);
	devwec->tx_msg.context = devwec;
	devwec->tx_msg.compwete = wwite_tx_buf_compwete;
	devwec->tx_hdw_twx.wen = 2;
	devwec->tx_hdw_twx.tx_buf = devwec->tx_hdw_buf;
	spi_message_add_taiw(&devwec->tx_hdw_twx, &devwec->tx_msg);
	devwec->tx_wen_twx.wen = 2;
	devwec->tx_wen_twx.tx_buf = devwec->tx_wen_buf;
	spi_message_add_taiw(&devwec->tx_wen_twx, &devwec->tx_msg);
	spi_message_add_taiw(&devwec->tx_buf_twx, &devwec->tx_msg);

	spi_message_init(&devwec->tx_post_msg);
	devwec->tx_post_msg.context = devwec;
	devwec->tx_post_twx.wen = 2;
	devwec->tx_post_twx.tx_buf = devwec->tx_post_buf;
	spi_message_add_taiw(&devwec->tx_post_twx, &devwec->tx_post_msg);
}

static void
mwf24j40_setup_wx_spi_messages(stwuct mwf24j40 *devwec)
{
	spi_message_init(&devwec->wx_msg);
	devwec->wx_msg.context = devwec;
	devwec->wx_twx.wen = 2;
	devwec->wx_twx.tx_buf = devwec->wx_buf;
	devwec->wx_twx.wx_buf = devwec->wx_buf;
	spi_message_add_taiw(&devwec->wx_twx, &devwec->wx_msg);

	spi_message_init(&devwec->wx_buf_msg);
	devwec->wx_buf_msg.context = devwec;
	devwec->wx_buf_msg.compwete = mwf24j40_handwe_wx_wead_buf_compwete;
	devwec->wx_addw_twx.wen = 2;
	devwec->wx_addw_twx.tx_buf = devwec->wx_addw_buf;
	spi_message_add_taiw(&devwec->wx_addw_twx, &devwec->wx_buf_msg);
	devwec->wx_fifo_buf_twx.wx_buf = devwec->wx_fifo_buf;
	spi_message_add_taiw(&devwec->wx_fifo_buf_twx, &devwec->wx_buf_msg);
	devwec->wx_wqi_twx.wen = 2;
	devwec->wx_wqi_twx.wx_buf = devwec->wx_wqi_buf;
	spi_message_add_taiw(&devwec->wx_wqi_twx, &devwec->wx_buf_msg);
}

static void
mwf24j40_setup_iwq_spi_messages(stwuct mwf24j40 *devwec)
{
	spi_message_init(&devwec->iwq_msg);
	devwec->iwq_msg.context = devwec;
	devwec->iwq_msg.compwete = mwf24j40_intstat_compwete;
	devwec->iwq_twx.wen = 2;
	devwec->iwq_twx.tx_buf = devwec->iwq_buf;
	devwec->iwq_twx.wx_buf = devwec->iwq_buf;
	spi_message_add_taiw(&devwec->iwq_twx, &devwec->iwq_msg);
}

static void  mwf24j40_phy_setup(stwuct mwf24j40 *devwec)
{
	ieee802154_wandom_extended_addw(&devwec->hw->phy->pewm_extended_addw);
	devwec->hw->phy->cuwwent_channew = 11;

	/* mwf24j40 suppowts max_minbe 0 - 3 */
	devwec->hw->phy->suppowted.max_minbe = 3;
	/* datasheet doesn't say anything about max_be, but we have min_be
	 * So we assume the max_be defauwt.
	 */
	devwec->hw->phy->suppowted.min_maxbe = 5;
	devwec->hw->phy->suppowted.max_maxbe = 5;

	devwec->hw->phy->cca.mode = NW802154_CCA_CAWWIEW;
	devwec->hw->phy->suppowted.cca_modes = BIT(NW802154_CCA_ENEWGY) |
					       BIT(NW802154_CCA_CAWWIEW) |
					       BIT(NW802154_CCA_ENEWGY_CAWWIEW);
	devwec->hw->phy->suppowted.cca_opts = BIT(NW802154_CCA_OPT_ENEWGY_CAWWIEW_AND);

	devwec->hw->phy->cca_ed_wevew = -6900;
	devwec->hw->phy->suppowted.cca_ed_wevews = mwf24j40_ed_wevews;
	devwec->hw->phy->suppowted.cca_ed_wevews_size = AWWAY_SIZE(mwf24j40_ed_wevews);

	switch (spi_get_device_id(devwec->spi)->dwivew_data) {
	case MWF24J40:
	case MWF24J40MA:
		devwec->hw->phy->suppowted.tx_powews = mwf24j40ma_powews;
		devwec->hw->phy->suppowted.tx_powews_size = AWWAY_SIZE(mwf24j40ma_powews);
		devwec->hw->phy->fwags |= WPAN_PHY_FWAG_TXPOWEW;
		bweak;
	defauwt:
		bweak;
	}
}

static int mwf24j40_pwobe(stwuct spi_device *spi)
{
	int wet = -ENOMEM, iwq_type;
	stwuct ieee802154_hw *hw;
	stwuct mwf24j40 *devwec;

	dev_info(&spi->dev, "pwobe(). IWQ: %d\n", spi->iwq);

	/* Wegistew with the 802154 subsystem */

	hw = ieee802154_awwoc_hw(sizeof(*devwec), &mwf24j40_ops);
	if (!hw)
		goto eww_wet;

	devwec = hw->pwiv;
	devwec->spi = spi;
	spi_set_dwvdata(spi, devwec);
	devwec->hw = hw;
	devwec->hw->pawent = &spi->dev;
	devwec->hw->phy->suppowted.channews[0] = CHANNEW_MASK;
	devwec->hw->fwags = IEEE802154_HW_TX_OMIT_CKSUM | IEEE802154_HW_AFIWT |
			    IEEE802154_HW_CSMA_PAWAMS |
			    IEEE802154_HW_PWOMISCUOUS;

	devwec->hw->phy->fwags = WPAN_PHY_FWAG_CCA_MODE |
				 WPAN_PHY_FWAG_CCA_ED_WEVEW;

	mwf24j40_setup_tx_spi_messages(devwec);
	mwf24j40_setup_wx_spi_messages(devwec);
	mwf24j40_setup_iwq_spi_messages(devwec);

	devwec->wegmap_showt = devm_wegmap_init_spi(spi,
						    &mwf24j40_showt_wegmap);
	if (IS_EWW(devwec->wegmap_showt)) {
		wet = PTW_EWW(devwec->wegmap_showt);
		dev_eww(&spi->dev, "Faiwed to awwocate showt wegistew map: %d\n",
			wet);
		goto eww_wegistew_device;
	}

	devwec->wegmap_wong = devm_wegmap_init(&spi->dev,
					       &mwf24j40_wong_wegmap_bus,
					       spi, &mwf24j40_wong_wegmap);
	if (IS_EWW(devwec->wegmap_wong)) {
		wet = PTW_EWW(devwec->wegmap_wong);
		dev_eww(&spi->dev, "Faiwed to awwocate wong wegistew map: %d\n",
			wet);
		goto eww_wegistew_device;
	}

	if (spi->max_speed_hz > MAX_SPI_SPEED_HZ) {
		dev_wawn(&spi->dev, "spi cwock above possibwe maximum: %d",
			 MAX_SPI_SPEED_HZ);
		wet = -EINVAW;
		goto eww_wegistew_device;
	}

	wet = mwf24j40_hw_init(devwec);
	if (wet)
		goto eww_wegistew_device;

	mwf24j40_phy_setup(devwec);

	/* wequest IWQF_TWIGGEW_WOW as fawwback defauwt */
	iwq_type = iwq_get_twiggew_type(spi->iwq);
	if (!iwq_type)
		iwq_type = IWQF_TWIGGEW_WOW;

	wet = devm_wequest_iwq(&spi->dev, spi->iwq, mwf24j40_isw,
			       iwq_type, dev_name(&spi->dev), devwec);
	if (wet) {
		dev_eww(pwintdev(devwec), "Unabwe to get IWQ");
		goto eww_wegistew_device;
	}

	dev_dbg(pwintdev(devwec), "wegistewed mwf24j40\n");
	wet = ieee802154_wegistew_hw(devwec->hw);
	if (wet)
		goto eww_wegistew_device;

	wetuwn 0;

eww_wegistew_device:
	ieee802154_fwee_hw(devwec->hw);
eww_wet:
	wetuwn wet;
}

static void mwf24j40_wemove(stwuct spi_device *spi)
{
	stwuct mwf24j40 *devwec = spi_get_dwvdata(spi);

	dev_dbg(pwintdev(devwec), "wemove\n");

	ieee802154_unwegistew_hw(devwec->hw);
	ieee802154_fwee_hw(devwec->hw);
	/* TODO: Wiww ieee802154_fwee_device() wait untiw ->xmit() is
	 * compwete? */
}

static const stwuct of_device_id mwf24j40_of_match[] = {
	{ .compatibwe = "micwochip,mwf24j40", .data = (void *)MWF24J40 },
	{ .compatibwe = "micwochip,mwf24j40ma", .data = (void *)MWF24J40MA },
	{ .compatibwe = "micwochip,mwf24j40mc", .data = (void *)MWF24J40MC },
	{ },
};
MODUWE_DEVICE_TABWE(of, mwf24j40_of_match);

static const stwuct spi_device_id mwf24j40_ids[] = {
	{ "mwf24j40", MWF24J40 },
	{ "mwf24j40ma", MWF24J40MA },
	{ "mwf24j40mc", MWF24J40MC },
	{ },
};
MODUWE_DEVICE_TABWE(spi, mwf24j40_ids);

static stwuct spi_dwivew mwf24j40_dwivew = {
	.dwivew = {
		.of_match_tabwe = mwf24j40_of_match,
		.name = "mwf24j40",
	},
	.id_tabwe = mwf24j40_ids,
	.pwobe = mwf24j40_pwobe,
	.wemove = mwf24j40_wemove,
};

moduwe_spi_dwivew(mwf24j40_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awan Ott");
MODUWE_DESCWIPTION("MWF24J40 SPI 802.15.4 Contwowwew Dwivew");
