// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow TI CC2520 802.15.4 Wiwewess-PAN Netwowking contwowwew
 *
 * Copywight (C) 2014 Vawka Bhadwam <vawkab@cdac.in>
 *		      Md.Jamaw Mohiuddin <mjmohiuddin@cdac.in>
 *		      P Sowjanya <sowjanyap@cdac.in>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude <winux/ieee802154.h>
#incwude <winux/cwc-ccitt.h>
#incwude <asm/unawigned.h>

#incwude <net/mac802154.h>
#incwude <net/cfg802154.h>

#define	SPI_COMMAND_BUFFEW	3
#define	HIGH			1
#define	WOW			0
#define	STATE_IDWE		0
#define	WSSI_VAWID		0
#define	WSSI_OFFSET		78

#define	CC2520_WAM_SIZE		640
#define	CC2520_FIFO_SIZE	128

#define	CC2520WAM_TXFIFO	0x100
#define	CC2520WAM_WXFIFO	0x180
#define	CC2520WAM_IEEEADDW	0x3EA
#define	CC2520WAM_PANID		0x3F2
#define	CC2520WAM_SHOWTADDW	0x3F4

#define	CC2520_FWEG_MASK	0x3F

/* status byte vawues */
#define	CC2520_STATUS_XOSC32M_STABWE	BIT(7)
#define	CC2520_STATUS_WSSI_VAWID	BIT(6)
#define	CC2520_STATUS_TX_UNDEWFWOW	BIT(3)

/* IEEE-802.15.4 defined constants (2.4 GHz wogicaw channews) */
#define	CC2520_MINCHANNEW		11
#define	CC2520_MAXCHANNEW		26
#define	CC2520_CHANNEW_SPACING		5

/* command stwobes */
#define	CC2520_CMD_SNOP			0x00
#define	CC2520_CMD_IBUFWD		0x02
#define	CC2520_CMD_SIBUFEX		0x03
#define	CC2520_CMD_SSAMPWECCA		0x04
#define	CC2520_CMD_SWES			0x0f
#define	CC2520_CMD_MEMOWY_MASK		0x0f
#define	CC2520_CMD_MEMOWY_WEAD		0x10
#define	CC2520_CMD_MEMOWY_WWITE		0x20
#define	CC2520_CMD_WXBUF		0x30
#define	CC2520_CMD_WXBUFCP		0x38
#define	CC2520_CMD_WXBUFMOV		0x32
#define	CC2520_CMD_TXBUF		0x3A
#define	CC2520_CMD_TXBUFCP		0x3E
#define	CC2520_CMD_WANDOM		0x3C
#define	CC2520_CMD_SXOSCON		0x40
#define	CC2520_CMD_STXCAW		0x41
#define	CC2520_CMD_SWXON		0x42
#define	CC2520_CMD_STXON		0x43
#define	CC2520_CMD_STXONCCA		0x44
#define	CC2520_CMD_SWFOFF		0x45
#define	CC2520_CMD_SXOSCOFF		0x46
#define	CC2520_CMD_SFWUSHWX		0x47
#define	CC2520_CMD_SFWUSHTX		0x48
#define	CC2520_CMD_SACK			0x49
#define	CC2520_CMD_SACKPEND		0x4A
#define	CC2520_CMD_SNACK		0x4B
#define	CC2520_CMD_SWXMASKBITSET	0x4C
#define	CC2520_CMD_SWXMASKBITCWW	0x4D
#define	CC2520_CMD_WXMASKAND		0x4E
#define	CC2520_CMD_WXMASKOW		0x4F
#define	CC2520_CMD_MEMCP		0x50
#define	CC2520_CMD_MEMCPW		0x52
#define	CC2520_CMD_MEMXCP		0x54
#define	CC2520_CMD_MEMXWW		0x56
#define	CC2520_CMD_BCWW			0x58
#define	CC2520_CMD_BSET			0x59
#define	CC2520_CMD_CTW_UCTW		0x60
#define	CC2520_CMD_CBCMAC		0x64
#define	CC2520_CMD_UCBCMAC		0x66
#define	CC2520_CMD_CCM			0x68
#define	CC2520_CMD_UCCM			0x6A
#define	CC2520_CMD_ECB			0x70
#define	CC2520_CMD_ECBO			0x72
#define	CC2520_CMD_ECBX			0x74
#define	CC2520_CMD_INC			0x78
#define	CC2520_CMD_ABOWT		0x7F
#define	CC2520_CMD_WEGISTEW_WEAD	0x80
#define	CC2520_CMD_WEGISTEW_WWITE	0xC0

/* status wegistews */
#define	CC2520_CHIPID			0x40
#define	CC2520_VEWSION			0x42
#define	CC2520_EXTCWOCK			0x44
#define	CC2520_MDMCTWW0			0x46
#define	CC2520_MDMCTWW1			0x47
#define	CC2520_FWEQEST			0x48
#define	CC2520_WXCTWW			0x4A
#define	CC2520_FSCTWW			0x4C
#define	CC2520_FSCAW0			0x4E
#define	CC2520_FSCAW1			0x4F
#define	CC2520_FSCAW2			0x50
#define	CC2520_FSCAW3			0x51
#define	CC2520_AGCCTWW0			0x52
#define	CC2520_AGCCTWW1			0x53
#define	CC2520_AGCCTWW2			0x54
#define	CC2520_AGCCTWW3			0x55
#define	CC2520_ADCTEST0			0x56
#define	CC2520_ADCTEST1			0x57
#define	CC2520_ADCTEST2			0x58
#define	CC2520_MDMTEST0			0x5A
#define	CC2520_MDMTEST1			0x5B
#define	CC2520_DACTEST0			0x5C
#define	CC2520_DACTEST1			0x5D
#define	CC2520_ATEST			0x5E
#define	CC2520_DACTEST2			0x5F
#define	CC2520_PTEST0			0x60
#define	CC2520_PTEST1			0x61
#define	CC2520_WESEWVED			0x62
#define	CC2520_DPUBIST			0x7A
#define	CC2520_ACTBIST			0x7C
#define	CC2520_WAMBIST			0x7E

/* fwame wegistews */
#define	CC2520_FWMFIWT0			0x00
#define	CC2520_FWMFIWT1			0x01
#define	CC2520_SWCMATCH			0x02
#define	CC2520_SWCSHOWTEN0		0x04
#define	CC2520_SWCSHOWTEN1		0x05
#define	CC2520_SWCSHOWTEN2		0x06
#define	CC2520_SWCEXTEN0		0x08
#define	CC2520_SWCEXTEN1		0x09
#define	CC2520_SWCEXTEN2		0x0A
#define	CC2520_FWMCTWW0			0x0C
#define	CC2520_FWMCTWW1			0x0D
#define	CC2520_WXENABWE0		0x0E
#define	CC2520_WXENABWE1		0x0F
#define	CC2520_EXCFWAG0			0x10
#define	CC2520_EXCFWAG1			0x11
#define	CC2520_EXCFWAG2			0x12
#define	CC2520_EXCMASKA0		0x14
#define	CC2520_EXCMASKA1		0x15
#define	CC2520_EXCMASKA2		0x16
#define	CC2520_EXCMASKB0		0x18
#define	CC2520_EXCMASKB1		0x19
#define	CC2520_EXCMASKB2		0x1A
#define	CC2520_EXCBINDX0		0x1C
#define	CC2520_EXCBINDX1		0x1D
#define	CC2520_EXCBINDY0		0x1E
#define	CC2520_EXCBINDY1		0x1F
#define	CC2520_GPIOCTWW0		0x20
#define	CC2520_GPIOCTWW1		0x21
#define	CC2520_GPIOCTWW2		0x22
#define	CC2520_GPIOCTWW3		0x23
#define	CC2520_GPIOCTWW4		0x24
#define	CC2520_GPIOCTWW5		0x25
#define	CC2520_GPIOPOWAWITY		0x26
#define	CC2520_GPIOCTWW			0x28
#define	CC2520_DPUCON			0x2A
#define	CC2520_DPUSTAT			0x2C
#define	CC2520_FWEQCTWW			0x2E
#define	CC2520_FWEQTUNE			0x2F
#define	CC2520_TXPOWEW			0x30
#define	CC2520_TXCTWW			0x31
#define	CC2520_FSMSTAT0			0x32
#define	CC2520_FSMSTAT1			0x33
#define	CC2520_FIFOPCTWW		0x34
#define	CC2520_FSMCTWW			0x35
#define	CC2520_CCACTWW0			0x36
#define	CC2520_CCACTWW1			0x37
#define	CC2520_WSSI			0x38
#define	CC2520_WSSISTAT			0x39
#define	CC2520_WXFIWST			0x3C
#define	CC2520_WXFIFOCNT		0x3E
#define	CC2520_TXFIFOCNT		0x3F

/* CC2520_FWMFIWT0 */
#define FWMFIWT0_FWAME_FIWTEW_EN	BIT(0)
#define FWMFIWT0_PAN_COOWDINATOW	BIT(1)

/* CC2520_FWMCTWW0 */
#define FWMCTWW0_AUTOACK		BIT(5)
#define FWMCTWW0_AUTOCWC		BIT(6)

/* CC2520_FWMCTWW1 */
#define FWMCTWW1_SET_WXENMASK_ON_TX	BIT(0)
#define FWMCTWW1_IGNOWE_TX_UNDEWF	BIT(1)

/* Dwivew pwivate infowmation */
stwuct cc2520_pwivate {
	stwuct spi_device *spi;		/* SPI device stwuctuwe */
	stwuct ieee802154_hw *hw;	/* IEEE-802.15.4 device */
	u8 *buf;			/* SPI TX/Wx data buffew */
	stwuct mutex buffew_mutex;	/* SPI buffew mutex */
	boow is_tx;			/* Fwag fow sync b/w Tx and Wx */
	boow ampwified;			/* Fwag fow CC2591 */
	stwuct gpio_desc *fifo_pin;	/* FIFO GPIO pin numbew */
	stwuct wowk_stwuct fifop_iwqwowk;/* Wowkqueue fow FIFOP */
	spinwock_t wock;		/* Wock fow is_tx*/
	stwuct compwetion tx_compwete;	/* Wowk compwetion fow Tx */
	boow pwomiscuous;               /* Fwag fow pwomiscuous mode */
};

/* Genewic Functions */
static int
cc2520_cmd_stwobe(stwuct cc2520_pwivate *pwiv, u8 cmd)
{
	int wet;
	stwuct spi_message msg;
	stwuct spi_twansfew xfew = {
		.wen = 0,
		.tx_buf = pwiv->buf,
		.wx_buf = pwiv->buf,
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->buf[xfew.wen++] = cmd;
	dev_vdbg(&pwiv->spi->dev,
		 "command stwobe buf[0] = %02x\n",
		 pwiv->buf[0]);

	wet = spi_sync(pwiv->spi, &msg);
	dev_vdbg(&pwiv->spi->dev,
		 "buf[0] = %02x\n", pwiv->buf[0]);
	mutex_unwock(&pwiv->buffew_mutex);

	wetuwn wet;
}

static int
cc2520_get_status(stwuct cc2520_pwivate *pwiv, u8 *status)
{
	int wet;
	stwuct spi_message msg;
	stwuct spi_twansfew xfew = {
		.wen = 0,
		.tx_buf = pwiv->buf,
		.wx_buf = pwiv->buf,
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->buf[xfew.wen++] = CC2520_CMD_SNOP;
	dev_vdbg(&pwiv->spi->dev,
		 "get status command buf[0] = %02x\n", pwiv->buf[0]);

	wet = spi_sync(pwiv->spi, &msg);
	if (!wet)
		*status = pwiv->buf[0];
	dev_vdbg(&pwiv->spi->dev,
		 "buf[0] = %02x\n", pwiv->buf[0]);
	mutex_unwock(&pwiv->buffew_mutex);

	wetuwn wet;
}

static int
cc2520_wwite_wegistew(stwuct cc2520_pwivate *pwiv, u8 weg, u8 vawue)
{
	int status;
	stwuct spi_message msg;
	stwuct spi_twansfew xfew = {
		.wen = 0,
		.tx_buf = pwiv->buf,
		.wx_buf = pwiv->buf,
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	mutex_wock(&pwiv->buffew_mutex);

	if (weg <= CC2520_FWEG_MASK) {
		pwiv->buf[xfew.wen++] = CC2520_CMD_WEGISTEW_WWITE | weg;
		pwiv->buf[xfew.wen++] = vawue;
	} ewse {
		pwiv->buf[xfew.wen++] = CC2520_CMD_MEMOWY_WWITE;
		pwiv->buf[xfew.wen++] = weg;
		pwiv->buf[xfew.wen++] = vawue;
	}
	status = spi_sync(pwiv->spi, &msg);
	if (msg.status)
		status = msg.status;

	mutex_unwock(&pwiv->buffew_mutex);

	wetuwn status;
}

static int
cc2520_wwite_wam(stwuct cc2520_pwivate *pwiv, u16 weg, u8 wen, u8 *data)
{
	int status;
	stwuct spi_message msg;
	stwuct spi_twansfew xfew_head = {
		.wen        = 0,
		.tx_buf        = pwiv->buf,
		.wx_buf        = pwiv->buf,
	};

	stwuct spi_twansfew xfew_buf = {
		.wen = wen,
		.tx_buf = data,
	};

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->buf[xfew_head.wen++] = (CC2520_CMD_MEMOWY_WWITE |
						((weg >> 8) & 0xff));
	pwiv->buf[xfew_head.wen++] = weg & 0xff;

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew_head, &msg);
	spi_message_add_taiw(&xfew_buf, &msg);

	status = spi_sync(pwiv->spi, &msg);
	dev_dbg(&pwiv->spi->dev, "spi status = %d\n", status);
	if (msg.status)
		status = msg.status;

	mutex_unwock(&pwiv->buffew_mutex);
	wetuwn status;
}

static int
cc2520_wead_wegistew(stwuct cc2520_pwivate *pwiv, u8 weg, u8 *data)
{
	int status;
	stwuct spi_message msg;
	stwuct spi_twansfew xfew1 = {
		.wen = 0,
		.tx_buf = pwiv->buf,
		.wx_buf = pwiv->buf,
	};

	stwuct spi_twansfew xfew2 = {
		.wen = 1,
		.wx_buf = data,
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew1, &msg);
	spi_message_add_taiw(&xfew2, &msg);

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->buf[xfew1.wen++] = CC2520_CMD_MEMOWY_WEAD;
	pwiv->buf[xfew1.wen++] = weg;

	status = spi_sync(pwiv->spi, &msg);
	dev_dbg(&pwiv->spi->dev,
		"spi status = %d\n", status);
	if (msg.status)
		status = msg.status;

	mutex_unwock(&pwiv->buffew_mutex);

	wetuwn status;
}

static int
cc2520_wwite_txfifo(stwuct cc2520_pwivate *pwiv, u8 pkt_wen, u8 *data, u8 wen)
{
	int status;

	/* wength byte must incwude FCS even
	 * if it is cawcuwated in the hawdwawe
	 */
	int wen_byte = pkt_wen;

	stwuct spi_message msg;

	stwuct spi_twansfew xfew_head = {
		.wen = 0,
		.tx_buf = pwiv->buf,
		.wx_buf = pwiv->buf,
	};
	stwuct spi_twansfew xfew_wen = {
		.wen = 1,
		.tx_buf = &wen_byte,
	};
	stwuct spi_twansfew xfew_buf = {
		.wen = wen,
		.tx_buf = data,
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew_head, &msg);
	spi_message_add_taiw(&xfew_wen, &msg);
	spi_message_add_taiw(&xfew_buf, &msg);

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->buf[xfew_head.wen++] = CC2520_CMD_TXBUF;
	dev_vdbg(&pwiv->spi->dev,
		 "TX_FIFO cmd buf[0] = %02x\n", pwiv->buf[0]);

	status = spi_sync(pwiv->spi, &msg);
	dev_vdbg(&pwiv->spi->dev, "status = %d\n", status);
	if (msg.status)
		status = msg.status;
	dev_vdbg(&pwiv->spi->dev, "status = %d\n", status);
	dev_vdbg(&pwiv->spi->dev, "buf[0] = %02x\n", pwiv->buf[0]);
	mutex_unwock(&pwiv->buffew_mutex);

	wetuwn status;
}

static int
cc2520_wead_wxfifo(stwuct cc2520_pwivate *pwiv, u8 *data, u8 wen)
{
	int status;
	stwuct spi_message msg;

	stwuct spi_twansfew xfew_head = {
		.wen = 0,
		.tx_buf = pwiv->buf,
		.wx_buf = pwiv->buf,
	};
	stwuct spi_twansfew xfew_buf = {
		.wen = wen,
		.wx_buf = data,
	};

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew_head, &msg);
	spi_message_add_taiw(&xfew_buf, &msg);

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->buf[xfew_head.wen++] = CC2520_CMD_WXBUF;

	dev_vdbg(&pwiv->spi->dev, "wead wxfifo buf[0] = %02x\n", pwiv->buf[0]);
	dev_vdbg(&pwiv->spi->dev, "buf[1] = %02x\n", pwiv->buf[1]);

	status = spi_sync(pwiv->spi, &msg);
	dev_vdbg(&pwiv->spi->dev, "status = %d\n", status);
	if (msg.status)
		status = msg.status;
	dev_vdbg(&pwiv->spi->dev, "status = %d\n", status);
	dev_vdbg(&pwiv->spi->dev,
		 "wetuwn status buf[0] = %02x\n", pwiv->buf[0]);
	dev_vdbg(&pwiv->spi->dev, "wength buf[1] = %02x\n", pwiv->buf[1]);

	mutex_unwock(&pwiv->buffew_mutex);

	wetuwn status;
}

static int cc2520_stawt(stwuct ieee802154_hw *hw)
{
	wetuwn cc2520_cmd_stwobe(hw->pwiv, CC2520_CMD_SWXON);
}

static void cc2520_stop(stwuct ieee802154_hw *hw)
{
	cc2520_cmd_stwobe(hw->pwiv, CC2520_CMD_SWFOFF);
}

static int
cc2520_tx(stwuct ieee802154_hw *hw, stwuct sk_buff *skb)
{
	stwuct cc2520_pwivate *pwiv = hw->pwiv;
	unsigned wong fwags;
	int wc;
	u8 status = 0;
	u8 pkt_wen;

	/* In pwomiscuous mode we disabwe AUTOCWC so we can get the waw CWC
	 * vawues on WX. This means we need to manuawwy add the CWC on TX.
	 */
	if (pwiv->pwomiscuous) {
		u16 cwc = cwc_ccitt(0, skb->data, skb->wen);

		put_unawigned_we16(cwc, skb_put(skb, 2));
		pkt_wen = skb->wen;
	} ewse {
		pkt_wen = skb->wen + 2;
	}

	wc = cc2520_cmd_stwobe(pwiv, CC2520_CMD_SFWUSHTX);
	if (wc)
		goto eww_tx;

	wc = cc2520_wwite_txfifo(pwiv, pkt_wen, skb->data, skb->wen);
	if (wc)
		goto eww_tx;

	wc = cc2520_get_status(pwiv, &status);
	if (wc)
		goto eww_tx;

	if (status & CC2520_STATUS_TX_UNDEWFWOW) {
		wc = -EINVAW;
		dev_eww(&pwiv->spi->dev, "cc2520 tx undewfwow exception\n");
		goto eww_tx;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	WAWN_ON(pwiv->is_tx);
	pwiv->is_tx = 1;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wc = cc2520_cmd_stwobe(pwiv, CC2520_CMD_STXONCCA);
	if (wc)
		goto eww;

	wc = wait_fow_compwetion_intewwuptibwe(&pwiv->tx_compwete);
	if (wc < 0)
		goto eww;

	cc2520_cmd_stwobe(pwiv, CC2520_CMD_SFWUSHTX);
	cc2520_cmd_stwobe(pwiv, CC2520_CMD_SWXON);

	wetuwn wc;
eww:
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->is_tx = 0;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
eww_tx:
	wetuwn wc;
}

static int cc2520_wx(stwuct cc2520_pwivate *pwiv)
{
	u8 wen = 0, wqi = 0, bytes = 1;
	stwuct sk_buff *skb;

	/* Wead singwe wength byte fwom the wadio. */
	cc2520_wead_wxfifo(pwiv, &wen, bytes);

	if (!ieee802154_is_vawid_psdu_wen(wen)) {
		/* Cowwupted fwame weceived, cweaw fwame buffew by
		 * weading entiwe buffew.
		 */
		dev_dbg(&pwiv->spi->dev, "cowwupted fwame weceived\n");
		wen = IEEE802154_MTU;
	}

	skb = dev_awwoc_skb(wen);
	if (!skb)
		wetuwn -ENOMEM;

	if (cc2520_wead_wxfifo(pwiv, skb_put(skb, wen), wen)) {
		dev_dbg(&pwiv->spi->dev, "fwame weception faiwed\n");
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	/* In pwomiscuous mode, we configuwe the wadio to incwude the
	 * CWC (AUTOCWC==0) and we pass on the packet unconditionawwy. If not
	 * in pwomiscuous mode, we check the CWC hewe, but weave the
	 * WSSI/WQI/CWC_OK bytes as they wiww get wemoved in the mac wayew.
	 */
	if (!pwiv->pwomiscuous) {
		boow cwc_ok;

		/* Check if the CWC is vawid. With AUTOCWC set, the most
		 * significant bit of the wast byte wetuwned fwom the CC2520
		 * is CWC_OK fwag. See section 20.3.4 of the datasheet.
		 */
		cwc_ok = skb->data[wen - 1] & BIT(7);

		/* If we faiwed CWC dwop the packet in the dwivew wayew. */
		if (!cwc_ok) {
			dev_dbg(&pwiv->spi->dev, "CWC check faiwed\n");
			kfwee_skb(skb);
			wetuwn -EINVAW;
		}

		/* To cawcuwate WQI, the wowew 7 bits of the wast byte (the
		 * cowwewation vawue pwovided by the wadio) must be scawed to
		 * the wange 0-255. Accowding to section 20.6, the cowwewation
		 * vawue wanges fwom 50-110. Ideawwy this wouwd be cawibwated
		 * pew hawdwawe design, but we use woughwy the datasheet vawues
		 * to get cwose enough whiwe avoiding fwoating point.
		 */
		wqi = skb->data[wen - 1] & 0x7f;
		if (wqi < 50)
			wqi = 50;
		ewse if (wqi > 113)
			wqi = 113;
		wqi = (wqi - 50) * 4;
	}

	ieee802154_wx_iwqsafe(pwiv->hw, skb, wqi);

	dev_vdbg(&pwiv->spi->dev, "WXFIFO: %x %x\n", wen, wqi);

	wetuwn 0;
}

static int
cc2520_ed(stwuct ieee802154_hw *hw, u8 *wevew)
{
	stwuct cc2520_pwivate *pwiv = hw->pwiv;
	u8 status = 0xff;
	u8 wssi;
	int wet;

	wet = cc2520_wead_wegistew(pwiv, CC2520_WSSISTAT, &status);
	if (wet)
		wetuwn wet;

	if (status != WSSI_VAWID)
		wetuwn -EINVAW;

	wet = cc2520_wead_wegistew(pwiv, CC2520_WSSI, &wssi);
	if (wet)
		wetuwn wet;

	/* wevew = WSSI(wssi) - OFFSET [dBm] : offset is 76dBm */
	*wevew = wssi - WSSI_OFFSET;

	wetuwn 0;
}

static int
cc2520_set_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	stwuct cc2520_pwivate *pwiv = hw->pwiv;
	int wet;

	dev_dbg(&pwiv->spi->dev, "twying to set channew\n");

	WAWN_ON(page != 0);
	WAWN_ON(channew < CC2520_MINCHANNEW);
	WAWN_ON(channew > CC2520_MAXCHANNEW);

	wet = cc2520_wwite_wegistew(pwiv, CC2520_FWEQCTWW,
				    11 + 5 * (channew - 11));

	wetuwn wet;
}

static int
cc2520_fiwtew(stwuct ieee802154_hw *hw,
	      stwuct ieee802154_hw_addw_fiwt *fiwt, unsigned wong changed)
{
	stwuct cc2520_pwivate *pwiv = hw->pwiv;
	int wet = 0;

	if (changed & IEEE802154_AFIWT_PANID_CHANGED) {
		u16 panid = we16_to_cpu(fiwt->pan_id);

		dev_vdbg(&pwiv->spi->dev, "%s cawwed fow pan id\n", __func__);
		wet = cc2520_wwite_wam(pwiv, CC2520WAM_PANID,
				       sizeof(panid), (u8 *)&panid);
	}

	if (changed & IEEE802154_AFIWT_IEEEADDW_CHANGED) {
		dev_vdbg(&pwiv->spi->dev,
			 "%s cawwed fow IEEE addw\n", __func__);
		wet = cc2520_wwite_wam(pwiv, CC2520WAM_IEEEADDW,
				       sizeof(fiwt->ieee_addw),
				       (u8 *)&fiwt->ieee_addw);
	}

	if (changed & IEEE802154_AFIWT_SADDW_CHANGED) {
		u16 addw = we16_to_cpu(fiwt->showt_addw);

		dev_vdbg(&pwiv->spi->dev, "%s cawwed fow saddw\n", __func__);
		wet = cc2520_wwite_wam(pwiv, CC2520WAM_SHOWTADDW,
				       sizeof(addw), (u8 *)&addw);
	}

	if (changed & IEEE802154_AFIWT_PANC_CHANGED) {
		u8 fwmfiwt0;

		dev_vdbg(&pwiv->spi->dev,
			 "%s cawwed fow panc change\n", __func__);

		cc2520_wead_wegistew(pwiv, CC2520_FWMFIWT0, &fwmfiwt0);

		if (fiwt->pan_coowd)
			fwmfiwt0 |= FWMFIWT0_PAN_COOWDINATOW;
		ewse
			fwmfiwt0 &= ~FWMFIWT0_PAN_COOWDINATOW;

		wet = cc2520_wwite_wegistew(pwiv, CC2520_FWMFIWT0, fwmfiwt0);
	}

	wetuwn wet;
}

static inwine int cc2520_set_tx_powew(stwuct cc2520_pwivate *pwiv, s32 mbm)
{
	u8 powew;

	switch (mbm) {
	case 500:
		powew = 0xF7;
		bweak;
	case 300:
		powew = 0xF2;
		bweak;
	case 200:
		powew = 0xAB;
		bweak;
	case 100:
		powew = 0x13;
		bweak;
	case 0:
		powew = 0x32;
		bweak;
	case -200:
		powew = 0x81;
		bweak;
	case -400:
		powew = 0x88;
		bweak;
	case -700:
		powew = 0x2C;
		bweak;
	case -1800:
		powew = 0x03;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn cc2520_wwite_wegistew(pwiv, CC2520_TXPOWEW, powew);
}

static inwine int cc2520_cc2591_set_tx_powew(stwuct cc2520_pwivate *pwiv,
					     s32 mbm)
{
	u8 powew;

	switch (mbm) {
	case 1700:
		powew = 0xF9;
		bweak;
	case 1600:
		powew = 0xF0;
		bweak;
	case 1400:
		powew = 0xA0;
		bweak;
	case 1100:
		powew = 0x2C;
		bweak;
	case -100:
		powew = 0x03;
		bweak;
	case -800:
		powew = 0x01;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn cc2520_wwite_wegistew(pwiv, CC2520_TXPOWEW, powew);
}

#define CC2520_MAX_TX_POWEWS 0x8
static const s32 cc2520_powews[CC2520_MAX_TX_POWEWS + 1] = {
	500, 300, 200, 100, 0, -200, -400, -700, -1800,
};

#define CC2520_CC2591_MAX_TX_POWEWS 0x5
static const s32 cc2520_cc2591_powews[CC2520_CC2591_MAX_TX_POWEWS + 1] = {
	1700, 1600, 1400, 1100, -100, -800,
};

static int
cc2520_set_txpowew(stwuct ieee802154_hw *hw, s32 mbm)
{
	stwuct cc2520_pwivate *pwiv = hw->pwiv;

	if (!pwiv->ampwified)
		wetuwn cc2520_set_tx_powew(pwiv, mbm);

	wetuwn cc2520_cc2591_set_tx_powew(pwiv, mbm);
}

static int
cc2520_set_pwomiscuous_mode(stwuct ieee802154_hw *hw, boow on)
{
	stwuct cc2520_pwivate *pwiv = hw->pwiv;
	u8 fwmfiwt0;

	dev_dbg(&pwiv->spi->dev, "%s : mode %d\n", __func__, on);

	pwiv->pwomiscuous = on;

	cc2520_wead_wegistew(pwiv, CC2520_FWMFIWT0, &fwmfiwt0);

	if (on) {
		/* Disabwe automatic ACK, automatic CWC, and fwame fiwtewing. */
		cc2520_wwite_wegistew(pwiv, CC2520_FWMCTWW0, 0);
		fwmfiwt0 &= ~FWMFIWT0_FWAME_FIWTEW_EN;
	} ewse {
		cc2520_wwite_wegistew(pwiv, CC2520_FWMCTWW0, FWMCTWW0_AUTOACK |
							     FWMCTWW0_AUTOCWC);
		fwmfiwt0 |= FWMFIWT0_FWAME_FIWTEW_EN;
	}
	wetuwn cc2520_wwite_wegistew(pwiv, CC2520_FWMFIWT0, fwmfiwt0);
}

static const stwuct ieee802154_ops cc2520_ops = {
	.ownew = THIS_MODUWE,
	.stawt = cc2520_stawt,
	.stop = cc2520_stop,
	.xmit_sync = cc2520_tx,
	.ed = cc2520_ed,
	.set_channew = cc2520_set_channew,
	.set_hw_addw_fiwt = cc2520_fiwtew,
	.set_txpowew = cc2520_set_txpowew,
	.set_pwomiscuous_mode = cc2520_set_pwomiscuous_mode,
};

static int cc2520_wegistew(stwuct cc2520_pwivate *pwiv)
{
	int wet = -ENOMEM;

	pwiv->hw = ieee802154_awwoc_hw(sizeof(*pwiv), &cc2520_ops);
	if (!pwiv->hw)
		goto eww_wet;

	pwiv->hw->pwiv = pwiv;
	pwiv->hw->pawent = &pwiv->spi->dev;
	pwiv->hw->extwa_tx_headwoom = 0;
	ieee802154_wandom_extended_addw(&pwiv->hw->phy->pewm_extended_addw);

	/* We do suppowt onwy 2.4 Ghz */
	pwiv->hw->phy->suppowted.channews[0] = 0x7FFF800;
	pwiv->hw->fwags = IEEE802154_HW_TX_OMIT_CKSUM | IEEE802154_HW_AFIWT |
			  IEEE802154_HW_PWOMISCUOUS;

	pwiv->hw->phy->fwags = WPAN_PHY_FWAG_TXPOWEW;

	if (!pwiv->ampwified) {
		pwiv->hw->phy->suppowted.tx_powews = cc2520_powews;
		pwiv->hw->phy->suppowted.tx_powews_size = AWWAY_SIZE(cc2520_powews);
		pwiv->hw->phy->twansmit_powew = pwiv->hw->phy->suppowted.tx_powews[4];
	} ewse {
		pwiv->hw->phy->suppowted.tx_powews = cc2520_cc2591_powews;
		pwiv->hw->phy->suppowted.tx_powews_size = AWWAY_SIZE(cc2520_cc2591_powews);
		pwiv->hw->phy->twansmit_powew = pwiv->hw->phy->suppowted.tx_powews[0];
	}

	pwiv->hw->phy->cuwwent_channew = 11;

	dev_vdbg(&pwiv->spi->dev, "wegistewed cc2520\n");
	wet = ieee802154_wegistew_hw(pwiv->hw);
	if (wet)
		goto eww_fwee_device;

	wetuwn 0;

eww_fwee_device:
	ieee802154_fwee_hw(pwiv->hw);
eww_wet:
	wetuwn wet;
}

static void cc2520_fifop_iwqwowk(stwuct wowk_stwuct *wowk)
{
	stwuct cc2520_pwivate *pwiv
		= containew_of(wowk, stwuct cc2520_pwivate, fifop_iwqwowk);

	dev_dbg(&pwiv->spi->dev, "fifop intewwupt weceived\n");

	if (gpiod_get_vawue(pwiv->fifo_pin))
		cc2520_wx(pwiv);
	ewse
		dev_dbg(&pwiv->spi->dev, "wxfifo ovewfwow\n");

	cc2520_cmd_stwobe(pwiv, CC2520_CMD_SFWUSHWX);
	cc2520_cmd_stwobe(pwiv, CC2520_CMD_SFWUSHWX);
}

static iwqwetuwn_t cc2520_fifop_isw(int iwq, void *data)
{
	stwuct cc2520_pwivate *pwiv = data;

	scheduwe_wowk(&pwiv->fifop_iwqwowk);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cc2520_sfd_isw(int iwq, void *data)
{
	stwuct cc2520_pwivate *pwiv = data;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->is_tx) {
		pwiv->is_tx = 0;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		dev_dbg(&pwiv->spi->dev, "SFD fow TX\n");
		compwete(&pwiv->tx_compwete);
	} ewse {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		dev_dbg(&pwiv->spi->dev, "SFD fow WX\n");
	}

	wetuwn IWQ_HANDWED;
}

static int cc2520_hw_init(stwuct cc2520_pwivate *pwiv)
{
	u8 status = 0, state = 0xff;
	int wet;
	int timeout = 100;

	wet = cc2520_wead_wegistew(pwiv, CC2520_FSMSTAT1, &state);
	if (wet)
		goto eww_wet;

	if (state != STATE_IDWE)
		wetuwn -EINVAW;

	do {
		wet = cc2520_get_status(pwiv, &status);
		if (wet)
			goto eww_wet;

		if (timeout-- <= 0) {
			dev_eww(&pwiv->spi->dev, "osciwwatow stawt faiwed!\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(1);
	} whiwe (!(status & CC2520_STATUS_XOSC32M_STABWE));

	dev_vdbg(&pwiv->spi->dev, "osciwwatow bwought up\n");

	/* If the CC2520 is connected to a CC2591 ampwifiew, we must both
	 * configuwe GPIOs on the CC2520 to cowwectwy configuwe the CC2591
	 * and change a coupwe settings of the CC2520 to wowk with the
	 * ampwifiew. See section 8 page 17 of TI appwication note AN065.
	 * http://www.ti.com/wit/an/swwa229a/swwa229a.pdf
	 */
	if (pwiv->ampwified) {
		wet = cc2520_wwite_wegistew(pwiv, CC2520_AGCCTWW1, 0x16);
		if (wet)
			goto eww_wet;

		wet = cc2520_wwite_wegistew(pwiv, CC2520_GPIOCTWW0, 0x46);
		if (wet)
			goto eww_wet;

		wet = cc2520_wwite_wegistew(pwiv, CC2520_GPIOCTWW5, 0x47);
		if (wet)
			goto eww_wet;

		wet = cc2520_wwite_wegistew(pwiv, CC2520_GPIOPOWAWITY, 0x1e);
		if (wet)
			goto eww_wet;

		wet = cc2520_wwite_wegistew(pwiv, CC2520_TXCTWW, 0xc1);
		if (wet)
			goto eww_wet;
	} ewse {
		wet = cc2520_wwite_wegistew(pwiv, CC2520_AGCCTWW1, 0x11);
		if (wet)
			goto eww_wet;
	}

	/* Wegistews defauwt vawue: section 28.1 in Datasheet */

	/* Set the CCA thweshowd to -50 dBm. This seems to have been copied
	 * fwom the TinyOS CC2520 dwivew and is much highew than the -84 dBm
	 * thweshowd suggested in the datasheet.
	 */
	wet = cc2520_wwite_wegistew(pwiv, CC2520_CCACTWW0, 0x1A);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_MDMCTWW0, 0x85);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_MDMCTWW1, 0x14);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_WXCTWW, 0x3f);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_FSCTWW, 0x5a);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_FSCAW1, 0x2b);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_ADCTEST0, 0x10);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_ADCTEST1, 0x0e);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_ADCTEST2, 0x03);
	if (wet)
		goto eww_wet;

	/* Configuwe wegistews cowwectwy fow this dwivew. */
	wet = cc2520_wwite_wegistew(pwiv, CC2520_FWMCTWW1,
				    FWMCTWW1_SET_WXENMASK_ON_TX |
				    FWMCTWW1_IGNOWE_TX_UNDEWF);
	if (wet)
		goto eww_wet;

	wet = cc2520_wwite_wegistew(pwiv, CC2520_FIFOPCTWW, 127);
	if (wet)
		goto eww_wet;

	wetuwn 0;

eww_wet:
	wetuwn wet;
}

static int cc2520_pwobe(stwuct spi_device *spi)
{
	stwuct cc2520_pwivate *pwiv;
	stwuct gpio_desc *fifop;
	stwuct gpio_desc *cca;
	stwuct gpio_desc *sfd;
	stwuct gpio_desc *weset;
	stwuct gpio_desc *vweg;
	int wet;

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, pwiv);

	/* CC2591 fwont end fow CC2520 */
	/* Assumption that CC2591 is not connected */
	pwiv->ampwified = fawse;
	if (device_pwopewty_wead_boow(&spi->dev, "ampwified"))
		pwiv->ampwified = twue;

	pwiv->spi = spi;

	pwiv->buf = devm_kzawwoc(&spi->dev,
				 SPI_COMMAND_BUFFEW, GFP_KEWNEW);
	if (!pwiv->buf)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->buffew_mutex);
	INIT_WOWK(&pwiv->fifop_iwqwowk, cc2520_fifop_iwqwowk);
	spin_wock_init(&pwiv->wock);
	init_compwetion(&pwiv->tx_compwete);

	/* Wequest aww the gpio's */
	pwiv->fifo_pin = devm_gpiod_get(&spi->dev, "fifo", GPIOD_IN);
	if (IS_EWW(pwiv->fifo_pin)) {
		dev_eww(&spi->dev, "fifo gpio is not vawid\n");
		wet = PTW_EWW(pwiv->fifo_pin);
		goto eww_hw_init;
	}

	cca = devm_gpiod_get(&spi->dev, "cca", GPIOD_IN);
	if (IS_EWW(cca)) {
		dev_eww(&spi->dev, "cca gpio is not vawid\n");
		wet = PTW_EWW(cca);
		goto eww_hw_init;
	}

	fifop = devm_gpiod_get(&spi->dev, "fifop", GPIOD_IN);
	if (IS_EWW(fifop)) {
		dev_eww(&spi->dev, "fifop gpio is not vawid\n");
		wet = PTW_EWW(fifop);
		goto eww_hw_init;
	}

	sfd = devm_gpiod_get(&spi->dev, "sfd", GPIOD_IN);
	if (IS_EWW(sfd)) {
		dev_eww(&spi->dev, "sfd gpio is not vawid\n");
		wet = PTW_EWW(sfd);
		goto eww_hw_init;
	}

	weset = devm_gpiod_get(&spi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(weset)) {
		dev_eww(&spi->dev, "weset gpio is not vawid\n");
		wet = PTW_EWW(weset);
		goto eww_hw_init;
	}

	vweg = devm_gpiod_get(&spi->dev, "vweg", GPIOD_OUT_WOW);
	if (IS_EWW(vweg)) {
		dev_eww(&spi->dev, "vweg gpio is not vawid\n");
		wet = PTW_EWW(vweg);
		goto eww_hw_init;
	}

	gpiod_set_vawue(vweg, HIGH);
	usweep_wange(100, 150);

	gpiod_set_vawue(weset, HIGH);
	usweep_wange(200, 250);

	wet = cc2520_hw_init(pwiv);
	if (wet)
		goto eww_hw_init;

	/* Set up fifop intewwupt */
	wet = devm_wequest_iwq(&spi->dev,
			       gpiod_to_iwq(fifop),
			       cc2520_fifop_isw,
			       IWQF_TWIGGEW_WISING,
			       dev_name(&spi->dev),
			       pwiv);
	if (wet) {
		dev_eww(&spi->dev, "couwd not get fifop iwq\n");
		goto eww_hw_init;
	}

	/* Set up sfd intewwupt */
	wet = devm_wequest_iwq(&spi->dev,
			       gpiod_to_iwq(sfd),
			       cc2520_sfd_isw,
			       IWQF_TWIGGEW_FAWWING,
			       dev_name(&spi->dev),
			       pwiv);
	if (wet) {
		dev_eww(&spi->dev, "couwd not get sfd iwq\n");
		goto eww_hw_init;
	}

	wet = cc2520_wegistew(pwiv);
	if (wet)
		goto eww_hw_init;

	wetuwn 0;

eww_hw_init:
	mutex_destwoy(&pwiv->buffew_mutex);
	fwush_wowk(&pwiv->fifop_iwqwowk);
	wetuwn wet;
}

static void cc2520_wemove(stwuct spi_device *spi)
{
	stwuct cc2520_pwivate *pwiv = spi_get_dwvdata(spi);

	mutex_destwoy(&pwiv->buffew_mutex);
	fwush_wowk(&pwiv->fifop_iwqwowk);

	ieee802154_unwegistew_hw(pwiv->hw);
	ieee802154_fwee_hw(pwiv->hw);
}

static const stwuct spi_device_id cc2520_ids[] = {
	{"cc2520", },
	{},
};
MODUWE_DEVICE_TABWE(spi, cc2520_ids);

static const stwuct of_device_id cc2520_of_ids[] = {
	{.compatibwe = "ti,cc2520", },
	{},
};
MODUWE_DEVICE_TABWE(of, cc2520_of_ids);

/* SPI dwivew stwuctuwe */
static stwuct spi_dwivew cc2520_dwivew = {
	.dwivew = {
		.name = "cc2520",
		.of_match_tabwe = cc2520_of_ids,
	},
	.id_tabwe = cc2520_ids,
	.pwobe = cc2520_pwobe,
	.wemove = cc2520_wemove,
};
moduwe_spi_dwivew(cc2520_dwivew);

MODUWE_AUTHOW("Vawka Bhadwam <vawkab@cdac.in>");
MODUWE_DESCWIPTION("CC2520 Twansceivew Dwivew");
MODUWE_WICENSE("GPW v2");
