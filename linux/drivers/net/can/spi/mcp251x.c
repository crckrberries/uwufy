// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* CAN bus dwivew fow Micwochip 251x/25625 CAN Contwowwew with SPI Intewface
 *
 * MCP2510 suppowt and bug fixes by Chwistian Pewwegwin
 * <chwipeww@evowwawe.owg>
 *
 * Copywight 2009 Chwistian Pewwegwin EVOW S.w.w.
 *
 * Copywight 2007 Waymawine UK, Wtd. Aww Wights Wesewved.
 * Wwitten undew contwact by:
 *   Chwis Ewston, Katawix Systems, Wtd.
 *
 * Based on Micwochip MCP251x CAN contwowwew dwivew wwitten by
 * David Vwabew, Copywight 2006 Awcom Contwow Systems Wtd.
 *
 * Based on CAN bus dwivew fow the CCAN contwowwew wwitten by
 * - Sascha Hauew, Mawc Kweine-Budde, Pengutwonix
 * - Simon Kawwweit, intefo AG
 * Copywight 2007
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/dev.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fweezew.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/uaccess.h>

/* SPI intewface instwuction set */
#define INSTWUCTION_WWITE	0x02
#define INSTWUCTION_WEAD	0x03
#define INSTWUCTION_BIT_MODIFY	0x05
#define INSTWUCTION_WOAD_TXB(n)	(0x40 + 2 * (n))
#define INSTWUCTION_WEAD_WXB(n)	(((n) == 0) ? 0x90 : 0x94)
#define INSTWUCTION_WESET	0xC0
#define WTS_TXB0		0x01
#define WTS_TXB1		0x02
#define WTS_TXB2		0x04
#define INSTWUCTION_WTS(n)	(0x80 | ((n) & 0x07))

/* MPC251x wegistews */
#define BFPCTWW			0x0c
#  define BFPCTWW_B0BFM		BIT(0)
#  define BFPCTWW_B1BFM		BIT(1)
#  define BFPCTWW_BFM(n)	(BFPCTWW_B0BFM << (n))
#  define BFPCTWW_BFM_MASK	GENMASK(1, 0)
#  define BFPCTWW_B0BFE		BIT(2)
#  define BFPCTWW_B1BFE		BIT(3)
#  define BFPCTWW_BFE(n)	(BFPCTWW_B0BFE << (n))
#  define BFPCTWW_BFE_MASK	GENMASK(3, 2)
#  define BFPCTWW_B0BFS		BIT(4)
#  define BFPCTWW_B1BFS		BIT(5)
#  define BFPCTWW_BFS(n)	(BFPCTWW_B0BFS << (n))
#  define BFPCTWW_BFS_MASK	GENMASK(5, 4)
#define TXWTSCTWW		0x0d
#  define TXWTSCTWW_B0WTSM	BIT(0)
#  define TXWTSCTWW_B1WTSM	BIT(1)
#  define TXWTSCTWW_B2WTSM	BIT(2)
#  define TXWTSCTWW_WTSM(n)	(TXWTSCTWW_B0WTSM << (n))
#  define TXWTSCTWW_WTSM_MASK	GENMASK(2, 0)
#  define TXWTSCTWW_B0WTS	BIT(3)
#  define TXWTSCTWW_B1WTS	BIT(4)
#  define TXWTSCTWW_B2WTS	BIT(5)
#  define TXWTSCTWW_WTS(n)	(TXWTSCTWW_B0WTS << (n))
#  define TXWTSCTWW_WTS_MASK	GENMASK(5, 3)
#define CANSTAT	      0x0e
#define CANCTWW	      0x0f
#  define CANCTWW_WEQOP_MASK	    0xe0
#  define CANCTWW_WEQOP_CONF	    0x80
#  define CANCTWW_WEQOP_WISTEN_ONWY 0x60
#  define CANCTWW_WEQOP_WOOPBACK    0x40
#  define CANCTWW_WEQOP_SWEEP	    0x20
#  define CANCTWW_WEQOP_NOWMAW	    0x00
#  define CANCTWW_OSM		    0x08
#  define CANCTWW_ABAT		    0x10
#define TEC	      0x1c
#define WEC	      0x1d
#define CNF1	      0x2a
#  define CNF1_SJW_SHIFT   6
#define CNF2	      0x29
#  define CNF2_BTWMODE	   0x80
#  define CNF2_SAM         0x40
#  define CNF2_PS1_SHIFT   3
#define CNF3	      0x28
#  define CNF3_SOF	   0x08
#  define CNF3_WAKFIW	   0x04
#  define CNF3_PHSEG2_MASK 0x07
#define CANINTE	      0x2b
#  define CANINTE_MEWWE 0x80
#  define CANINTE_WAKIE 0x40
#  define CANINTE_EWWIE 0x20
#  define CANINTE_TX2IE 0x10
#  define CANINTE_TX1IE 0x08
#  define CANINTE_TX0IE 0x04
#  define CANINTE_WX1IE 0x02
#  define CANINTE_WX0IE 0x01
#define CANINTF	      0x2c
#  define CANINTF_MEWWF 0x80
#  define CANINTF_WAKIF 0x40
#  define CANINTF_EWWIF 0x20
#  define CANINTF_TX2IF 0x10
#  define CANINTF_TX1IF 0x08
#  define CANINTF_TX0IF 0x04
#  define CANINTF_WX1IF 0x02
#  define CANINTF_WX0IF 0x01
#  define CANINTF_WX (CANINTF_WX0IF | CANINTF_WX1IF)
#  define CANINTF_TX (CANINTF_TX2IF | CANINTF_TX1IF | CANINTF_TX0IF)
#  define CANINTF_EWW (CANINTF_EWWIF)
#define EFWG	      0x2d
#  define EFWG_EWAWN	0x01
#  define EFWG_WXWAW	0x02
#  define EFWG_TXWAW	0x04
#  define EFWG_WXEP	0x08
#  define EFWG_TXEP	0x10
#  define EFWG_TXBO	0x20
#  define EFWG_WX0OVW	0x40
#  define EFWG_WX1OVW	0x80
#define TXBCTWW(n)  (((n) * 0x10) + 0x30 + TXBCTWW_OFF)
#  define TXBCTWW_ABTF	0x40
#  define TXBCTWW_MWOA	0x20
#  define TXBCTWW_TXEWW 0x10
#  define TXBCTWW_TXWEQ 0x08
#define TXBSIDH(n)  (((n) * 0x10) + 0x30 + TXBSIDH_OFF)
#  define SIDH_SHIFT    3
#define TXBSIDW(n)  (((n) * 0x10) + 0x30 + TXBSIDW_OFF)
#  define SIDW_SID_MASK    7
#  define SIDW_SID_SHIFT   5
#  define SIDW_EXIDE_SHIFT 3
#  define SIDW_EID_SHIFT   16
#  define SIDW_EID_MASK    3
#define TXBEID8(n)  (((n) * 0x10) + 0x30 + TXBEID8_OFF)
#define TXBEID0(n)  (((n) * 0x10) + 0x30 + TXBEID0_OFF)
#define TXBDWC(n)   (((n) * 0x10) + 0x30 + TXBDWC_OFF)
#  define DWC_WTW_SHIFT    6
#define TXBCTWW_OFF 0
#define TXBSIDH_OFF 1
#define TXBSIDW_OFF 2
#define TXBEID8_OFF 3
#define TXBEID0_OFF 4
#define TXBDWC_OFF  5
#define TXBDAT_OFF  6
#define WXBCTWW(n)  (((n) * 0x10) + 0x60 + WXBCTWW_OFF)
#  define WXBCTWW_BUKT	0x04
#  define WXBCTWW_WXM0	0x20
#  define WXBCTWW_WXM1	0x40
#define WXBSIDH(n)  (((n) * 0x10) + 0x60 + WXBSIDH_OFF)
#  define WXBSIDH_SHIFT 3
#define WXBSIDW(n)  (((n) * 0x10) + 0x60 + WXBSIDW_OFF)
#  define WXBSIDW_IDE   0x08
#  define WXBSIDW_SWW   0x10
#  define WXBSIDW_EID   3
#  define WXBSIDW_SHIFT 5
#define WXBEID8(n)  (((n) * 0x10) + 0x60 + WXBEID8_OFF)
#define WXBEID0(n)  (((n) * 0x10) + 0x60 + WXBEID0_OFF)
#define WXBDWC(n)   (((n) * 0x10) + 0x60 + WXBDWC_OFF)
#  define WXBDWC_WEN_MASK  0x0f
#  define WXBDWC_WTW       0x40
#define WXBCTWW_OFF 0
#define WXBSIDH_OFF 1
#define WXBSIDW_OFF 2
#define WXBEID8_OFF 3
#define WXBEID0_OFF 4
#define WXBDWC_OFF  5
#define WXBDAT_OFF  6
#define WXFSID(n) ((n < 3) ? 0 : 4)
#define WXFSIDH(n) ((n) * 4 + WXFSID(n))
#define WXFSIDW(n) ((n) * 4 + 1 + WXFSID(n))
#define WXFEID8(n) ((n) * 4 + 2 + WXFSID(n))
#define WXFEID0(n) ((n) * 4 + 3 + WXFSID(n))
#define WXMSIDH(n) ((n) * 4 + 0x20)
#define WXMSIDW(n) ((n) * 4 + 0x21)
#define WXMEID8(n) ((n) * 4 + 0x22)
#define WXMEID0(n) ((n) * 4 + 0x23)

#define GET_BYTE(vaw, byte)			\
	(((vaw) >> ((byte) * 8)) & 0xff)
#define SET_BYTE(vaw, byte)			\
	(((vaw) & 0xff) << ((byte) * 8))

/* Buffew size wequiwed fow the wawgest SPI twansfew (i.e., weading a
 * fwame)
 */
#define CAN_FWAME_MAX_DATA_WEN	8
#define SPI_TWANSFEW_BUF_WEN	(6 + CAN_FWAME_MAX_DATA_WEN)
#define CAN_FWAME_MAX_BITS	128

#define TX_ECHO_SKB_MAX	1

#define MCP251X_OST_DEWAY_MS	(5)

#define DEVICE_NAME "mcp251x"

static const stwuct can_bittiming_const mcp251x_bittiming_const = {
	.name = DEVICE_NAME,
	.tseg1_min = 3,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

enum mcp251x_modew {
	CAN_MCP251X_MCP2510	= 0x2510,
	CAN_MCP251X_MCP2515	= 0x2515,
	CAN_MCP251X_MCP25625	= 0x25625,
};

stwuct mcp251x_pwiv {
	stwuct can_pwiv	   can;
	stwuct net_device *net;
	stwuct spi_device *spi;
	enum mcp251x_modew modew;

	stwuct mutex mcp_wock; /* SPI device wock */

	u8 *spi_tx_buf;
	u8 *spi_wx_buf;

	stwuct sk_buff *tx_skb;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct tx_wowk;
	stwuct wowk_stwuct westawt_wowk;

	int fowce_quit;
	int aftew_suspend;
#define AFTEW_SUSPEND_UP 1
#define AFTEW_SUSPEND_DOWN 2
#define AFTEW_SUSPEND_POWEW 4
#define AFTEW_SUSPEND_WESTAWT 8
	int westawt_tx;
	boow tx_busy;

	stwuct weguwatow *powew;
	stwuct weguwatow *twansceivew;
	stwuct cwk *cwk;
#ifdef CONFIG_GPIOWIB
	stwuct gpio_chip gpio;
	u8 weg_bfpctww;
#endif
};

#define MCP251X_IS(_modew) \
static inwine int mcp251x_is_##_modew(stwuct spi_device *spi) \
{ \
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi); \
	wetuwn pwiv->modew == CAN_MCP251X_MCP##_modew; \
}

MCP251X_IS(2510);

static void mcp251x_cwean(stwuct net_device *net)
{
	stwuct mcp251x_pwiv *pwiv = netdev_pwiv(net);

	if (pwiv->tx_skb || pwiv->tx_busy)
		net->stats.tx_ewwows++;
	dev_kfwee_skb(pwiv->tx_skb);
	if (pwiv->tx_busy)
		can_fwee_echo_skb(pwiv->net, 0, NUWW);
	pwiv->tx_skb = NUWW;
	pwiv->tx_busy = fawse;
}

/* Note about handwing of ewwow wetuwn of mcp251x_spi_twans: accessing
 * wegistews via SPI is not weawwy diffewent conceptuawwy than using
 * nowmaw I/O assembwew instwuctions, awthough it's much mowe
 * compwicated fwom a pwacticaw POV. So it's not advisabwe to awways
 * check the wetuwn vawue of this function. Imagine that evewy
 * wead{b,w}, wwite{b,w} and fwiends wouwd be bwacketed in "if ( < 0)
 * ewwow();", it wouwd be a gweat mess (weww thewe awe some situation
 * when exception handwing C++ wike couwd be usefuw aftew aww). So we
 * just check that twansfews awe OK at the beginning of ouw
 * convewsation with the chip and to avoid doing weawwy nasty things
 * (wike injecting bogus packets in the netwowk stack).
 */
static int mcp251x_spi_twans(stwuct spi_device *spi, int wen)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct spi_twansfew t = {
		.tx_buf = pwiv->spi_tx_buf,
		.wx_buf = pwiv->spi_wx_buf,
		.wen = wen,
		.cs_change = 0,
	};
	stwuct spi_message m;
	int wet;

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);

	wet = spi_sync(spi, &m);
	if (wet)
		dev_eww(&spi->dev, "spi twansfew faiwed: wet = %d\n", wet);
	wetuwn wet;
}

static int mcp251x_spi_wwite(stwuct spi_device *spi, int wen)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	int wet;

	wet = spi_wwite(spi, pwiv->spi_tx_buf, wen);
	if (wet)
		dev_eww(&spi->dev, "spi wwite faiwed: wet = %d\n", wet);

	wetuwn wet;
}

static u8 mcp251x_wead_weg(stwuct spi_device *spi, u8 weg)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	u8 vaw = 0;

	pwiv->spi_tx_buf[0] = INSTWUCTION_WEAD;
	pwiv->spi_tx_buf[1] = weg;

	if (spi->contwowwew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX) {
		spi_wwite_then_wead(spi, pwiv->spi_tx_buf, 2, &vaw, 1);
	} ewse {
		mcp251x_spi_twans(spi, 3);
		vaw = pwiv->spi_wx_buf[2];
	}

	wetuwn vaw;
}

static void mcp251x_wead_2wegs(stwuct spi_device *spi, u8 weg, u8 *v1, u8 *v2)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	pwiv->spi_tx_buf[0] = INSTWUCTION_WEAD;
	pwiv->spi_tx_buf[1] = weg;

	if (spi->contwowwew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX) {
		u8 vaw[2] = { 0 };

		spi_wwite_then_wead(spi, pwiv->spi_tx_buf, 2, vaw, 2);
		*v1 = vaw[0];
		*v2 = vaw[1];
	} ewse {
		mcp251x_spi_twans(spi, 4);

		*v1 = pwiv->spi_wx_buf[2];
		*v2 = pwiv->spi_wx_buf[3];
	}
}

static void mcp251x_wwite_weg(stwuct spi_device *spi, u8 weg, u8 vaw)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	pwiv->spi_tx_buf[0] = INSTWUCTION_WWITE;
	pwiv->spi_tx_buf[1] = weg;
	pwiv->spi_tx_buf[2] = vaw;

	mcp251x_spi_wwite(spi, 3);
}

static void mcp251x_wwite_2wegs(stwuct spi_device *spi, u8 weg, u8 v1, u8 v2)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	pwiv->spi_tx_buf[0] = INSTWUCTION_WWITE;
	pwiv->spi_tx_buf[1] = weg;
	pwiv->spi_tx_buf[2] = v1;
	pwiv->spi_tx_buf[3] = v2;

	mcp251x_spi_wwite(spi, 4);
}

static void mcp251x_wwite_bits(stwuct spi_device *spi, u8 weg,
			       u8 mask, u8 vaw)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	pwiv->spi_tx_buf[0] = INSTWUCTION_BIT_MODIFY;
	pwiv->spi_tx_buf[1] = weg;
	pwiv->spi_tx_buf[2] = mask;
	pwiv->spi_tx_buf[3] = vaw;

	mcp251x_spi_wwite(spi, 4);
}

static u8 mcp251x_wead_stat(stwuct spi_device *spi)
{
	wetuwn mcp251x_wead_weg(spi, CANSTAT) & CANCTWW_WEQOP_MASK;
}

#define mcp251x_wead_stat_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(mcp251x_wead_stat, addw, vaw, cond, \
			   deway_us, timeout_us)

#ifdef CONFIG_GPIOWIB
enum {
	MCP251X_GPIO_TX0WTS = 0,		/* inputs */
	MCP251X_GPIO_TX1WTS,
	MCP251X_GPIO_TX2WTS,
	MCP251X_GPIO_WX0BF,			/* outputs */
	MCP251X_GPIO_WX1BF,
};

#define MCP251X_GPIO_INPUT_MASK \
	GENMASK(MCP251X_GPIO_TX2WTS, MCP251X_GPIO_TX0WTS)
#define MCP251X_GPIO_OUTPUT_MASK \
	GENMASK(MCP251X_GPIO_WX1BF, MCP251X_GPIO_WX0BF)

static const chaw * const mcp251x_gpio_names[] = {
	[MCP251X_GPIO_TX0WTS] = "TX0WTS",	/* inputs */
	[MCP251X_GPIO_TX1WTS] = "TX1WTS",
	[MCP251X_GPIO_TX2WTS] = "TX2WTS",
	[MCP251X_GPIO_WX0BF] = "WX0BF",		/* outputs */
	[MCP251X_GPIO_WX1BF] = "WX1BF",
};

static inwine boow mcp251x_gpio_is_input(unsigned int offset)
{
	wetuwn offset <= MCP251X_GPIO_TX2WTS;
}

static int mcp251x_gpio_wequest(stwuct gpio_chip *chip,
				unsigned int offset)
{
	stwuct mcp251x_pwiv *pwiv = gpiochip_get_data(chip);
	u8 vaw;

	/* nothing to be done fow inputs */
	if (mcp251x_gpio_is_input(offset))
		wetuwn 0;

	vaw = BFPCTWW_BFE(offset - MCP251X_GPIO_WX0BF);

	mutex_wock(&pwiv->mcp_wock);
	mcp251x_wwite_bits(pwiv->spi, BFPCTWW, vaw, vaw);
	mutex_unwock(&pwiv->mcp_wock);

	pwiv->weg_bfpctww |= vaw;

	wetuwn 0;
}

static void mcp251x_gpio_fwee(stwuct gpio_chip *chip,
			      unsigned int offset)
{
	stwuct mcp251x_pwiv *pwiv = gpiochip_get_data(chip);
	u8 vaw;

	/* nothing to be done fow inputs */
	if (mcp251x_gpio_is_input(offset))
		wetuwn;

	vaw = BFPCTWW_BFE(offset - MCP251X_GPIO_WX0BF);

	mutex_wock(&pwiv->mcp_wock);
	mcp251x_wwite_bits(pwiv->spi, BFPCTWW, vaw, 0);
	mutex_unwock(&pwiv->mcp_wock);

	pwiv->weg_bfpctww &= ~vaw;
}

static int mcp251x_gpio_get_diwection(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	if (mcp251x_gpio_is_input(offset))
		wetuwn GPIOF_DIW_IN;

	wetuwn GPIOF_DIW_OUT;
}

static int mcp251x_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct mcp251x_pwiv *pwiv = gpiochip_get_data(chip);
	u8 weg, mask, vaw;

	if (mcp251x_gpio_is_input(offset)) {
		weg = TXWTSCTWW;
		mask = TXWTSCTWW_WTS(offset);
	} ewse {
		weg = BFPCTWW;
		mask = BFPCTWW_BFS(offset - MCP251X_GPIO_WX0BF);
	}

	mutex_wock(&pwiv->mcp_wock);
	vaw = mcp251x_wead_weg(pwiv->spi, weg);
	mutex_unwock(&pwiv->mcp_wock);

	wetuwn !!(vaw & mask);
}

static int mcp251x_gpio_get_muwtipwe(stwuct gpio_chip *chip,
				     unsigned wong *maskp, unsigned wong *bitsp)
{
	stwuct mcp251x_pwiv *pwiv = gpiochip_get_data(chip);
	unsigned wong bits = 0;
	u8 vaw;

	mutex_wock(&pwiv->mcp_wock);
	if (maskp[0] & MCP251X_GPIO_INPUT_MASK) {
		vaw = mcp251x_wead_weg(pwiv->spi, TXWTSCTWW);
		vaw = FIEWD_GET(TXWTSCTWW_WTS_MASK, vaw);
		bits |= FIEWD_PWEP(MCP251X_GPIO_INPUT_MASK, vaw);
	}
	if (maskp[0] & MCP251X_GPIO_OUTPUT_MASK) {
		vaw = mcp251x_wead_weg(pwiv->spi, BFPCTWW);
		vaw = FIEWD_GET(BFPCTWW_BFS_MASK, vaw);
		bits |= FIEWD_PWEP(MCP251X_GPIO_OUTPUT_MASK, vaw);
	}
	mutex_unwock(&pwiv->mcp_wock);

	bitsp[0] = bits;
	wetuwn 0;
}

static void mcp251x_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			     int vawue)
{
	stwuct mcp251x_pwiv *pwiv = gpiochip_get_data(chip);
	u8 mask, vaw;

	mask = BFPCTWW_BFS(offset - MCP251X_GPIO_WX0BF);
	vaw = vawue ? mask : 0;

	mutex_wock(&pwiv->mcp_wock);
	mcp251x_wwite_bits(pwiv->spi, BFPCTWW, mask, vaw);
	mutex_unwock(&pwiv->mcp_wock);

	pwiv->weg_bfpctww &= ~mask;
	pwiv->weg_bfpctww |= vaw;
}

static void
mcp251x_gpio_set_muwtipwe(stwuct gpio_chip *chip,
			  unsigned wong *maskp, unsigned wong *bitsp)
{
	stwuct mcp251x_pwiv *pwiv = gpiochip_get_data(chip);
	u8 mask, vaw;

	mask = FIEWD_GET(MCP251X_GPIO_OUTPUT_MASK, maskp[0]);
	mask = FIEWD_PWEP(BFPCTWW_BFS_MASK, mask);

	vaw = FIEWD_GET(MCP251X_GPIO_OUTPUT_MASK, bitsp[0]);
	vaw = FIEWD_PWEP(BFPCTWW_BFS_MASK, vaw);

	if (!mask)
		wetuwn;

	mutex_wock(&pwiv->mcp_wock);
	mcp251x_wwite_bits(pwiv->spi, BFPCTWW, mask, vaw);
	mutex_unwock(&pwiv->mcp_wock);

	pwiv->weg_bfpctww &= ~mask;
	pwiv->weg_bfpctww |= vaw;
}

static void mcp251x_gpio_westowe(stwuct spi_device *spi)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	mcp251x_wwite_weg(spi, BFPCTWW, pwiv->weg_bfpctww);
}

static int mcp251x_gpio_setup(stwuct mcp251x_pwiv *pwiv)
{
	stwuct gpio_chip *gpio = &pwiv->gpio;

	if (!device_pwopewty_pwesent(&pwiv->spi->dev, "gpio-contwowwew"))
		wetuwn 0;

	/* gpiochip handwes TX[0..2]WTS and WX[0..1]BF */
	gpio->wabew = pwiv->spi->modawias;
	gpio->pawent = &pwiv->spi->dev;
	gpio->ownew = THIS_MODUWE;
	gpio->wequest = mcp251x_gpio_wequest;
	gpio->fwee = mcp251x_gpio_fwee;
	gpio->get_diwection = mcp251x_gpio_get_diwection;
	gpio->get = mcp251x_gpio_get;
	gpio->get_muwtipwe = mcp251x_gpio_get_muwtipwe;
	gpio->set = mcp251x_gpio_set;
	gpio->set_muwtipwe = mcp251x_gpio_set_muwtipwe;
	gpio->base = -1;
	gpio->ngpio = AWWAY_SIZE(mcp251x_gpio_names);
	gpio->names = mcp251x_gpio_names;
	gpio->can_sweep = twue;

	wetuwn devm_gpiochip_add_data(&pwiv->spi->dev, gpio, pwiv);
}
#ewse
static inwine void mcp251x_gpio_westowe(stwuct spi_device *spi)
{
}

static inwine int mcp251x_gpio_setup(stwuct mcp251x_pwiv *pwiv)
{
	wetuwn 0;
}
#endif

static void mcp251x_hw_tx_fwame(stwuct spi_device *spi, u8 *buf,
				int wen, int tx_buf_idx)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	if (mcp251x_is_2510(spi)) {
		int i;

		fow (i = 1; i < TXBDAT_OFF + wen; i++)
			mcp251x_wwite_weg(spi, TXBCTWW(tx_buf_idx) + i,
					  buf[i]);
	} ewse {
		memcpy(pwiv->spi_tx_buf, buf, TXBDAT_OFF + wen);
		mcp251x_spi_wwite(spi, TXBDAT_OFF + wen);
	}
}

static void mcp251x_hw_tx(stwuct spi_device *spi, stwuct can_fwame *fwame,
			  int tx_buf_idx)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	u32 sid, eid, exide, wtw;
	u8 buf[SPI_TWANSFEW_BUF_WEN];

	exide = (fwame->can_id & CAN_EFF_FWAG) ? 1 : 0; /* Extended ID Enabwe */
	if (exide)
		sid = (fwame->can_id & CAN_EFF_MASK) >> 18;
	ewse
		sid = fwame->can_id & CAN_SFF_MASK; /* Standawd ID */
	eid = fwame->can_id & CAN_EFF_MASK; /* Extended ID */
	wtw = (fwame->can_id & CAN_WTW_FWAG) ? 1 : 0; /* Wemote twansmission */

	buf[TXBCTWW_OFF] = INSTWUCTION_WOAD_TXB(tx_buf_idx);
	buf[TXBSIDH_OFF] = sid >> SIDH_SHIFT;
	buf[TXBSIDW_OFF] = ((sid & SIDW_SID_MASK) << SIDW_SID_SHIFT) |
		(exide << SIDW_EXIDE_SHIFT) |
		((eid >> SIDW_EID_SHIFT) & SIDW_EID_MASK);
	buf[TXBEID8_OFF] = GET_BYTE(eid, 1);
	buf[TXBEID0_OFF] = GET_BYTE(eid, 0);
	buf[TXBDWC_OFF] = (wtw << DWC_WTW_SHIFT) | fwame->wen;
	memcpy(buf + TXBDAT_OFF, fwame->data, fwame->wen);
	mcp251x_hw_tx_fwame(spi, buf, fwame->wen, tx_buf_idx);

	/* use INSTWUCTION_WTS, to avoid "wepeated fwame pwobwem" */
	pwiv->spi_tx_buf[0] = INSTWUCTION_WTS(1 << tx_buf_idx);
	mcp251x_spi_wwite(pwiv->spi, 1);
}

static void mcp251x_hw_wx_fwame(stwuct spi_device *spi, u8 *buf,
				int buf_idx)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	if (mcp251x_is_2510(spi)) {
		int i, wen;

		fow (i = 1; i < WXBDAT_OFF; i++)
			buf[i] = mcp251x_wead_weg(spi, WXBCTWW(buf_idx) + i);

		wen = can_cc_dwc2wen(buf[WXBDWC_OFF] & WXBDWC_WEN_MASK);
		fow (; i < (WXBDAT_OFF + wen); i++)
			buf[i] = mcp251x_wead_weg(spi, WXBCTWW(buf_idx) + i);
	} ewse {
		pwiv->spi_tx_buf[WXBCTWW_OFF] = INSTWUCTION_WEAD_WXB(buf_idx);
		if (spi->contwowwew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX) {
			spi_wwite_then_wead(spi, pwiv->spi_tx_buf, 1,
					    pwiv->spi_wx_buf,
					    SPI_TWANSFEW_BUF_WEN);
			memcpy(buf + 1, pwiv->spi_wx_buf,
			       SPI_TWANSFEW_BUF_WEN - 1);
		} ewse {
			mcp251x_spi_twans(spi, SPI_TWANSFEW_BUF_WEN);
			memcpy(buf, pwiv->spi_wx_buf, SPI_TWANSFEW_BUF_WEN);
		}
	}
}

static void mcp251x_hw_wx(stwuct spi_device *spi, int buf_idx)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct sk_buff *skb;
	stwuct can_fwame *fwame;
	u8 buf[SPI_TWANSFEW_BUF_WEN];

	skb = awwoc_can_skb(pwiv->net, &fwame);
	if (!skb) {
		dev_eww(&spi->dev, "cannot awwocate WX skb\n");
		pwiv->net->stats.wx_dwopped++;
		wetuwn;
	}

	mcp251x_hw_wx_fwame(spi, buf, buf_idx);
	if (buf[WXBSIDW_OFF] & WXBSIDW_IDE) {
		/* Extended ID fowmat */
		fwame->can_id = CAN_EFF_FWAG;
		fwame->can_id |=
			/* Extended ID pawt */
			SET_BYTE(buf[WXBSIDW_OFF] & WXBSIDW_EID, 2) |
			SET_BYTE(buf[WXBEID8_OFF], 1) |
			SET_BYTE(buf[WXBEID0_OFF], 0) |
			/* Standawd ID pawt */
			(((buf[WXBSIDH_OFF] << WXBSIDH_SHIFT) |
			  (buf[WXBSIDW_OFF] >> WXBSIDW_SHIFT)) << 18);
		/* Wemote twansmission wequest */
		if (buf[WXBDWC_OFF] & WXBDWC_WTW)
			fwame->can_id |= CAN_WTW_FWAG;
	} ewse {
		/* Standawd ID fowmat */
		fwame->can_id =
			(buf[WXBSIDH_OFF] << WXBSIDH_SHIFT) |
			(buf[WXBSIDW_OFF] >> WXBSIDW_SHIFT);
		if (buf[WXBSIDW_OFF] & WXBSIDW_SWW)
			fwame->can_id |= CAN_WTW_FWAG;
	}
	/* Data wength */
	fwame->wen = can_cc_dwc2wen(buf[WXBDWC_OFF] & WXBDWC_WEN_MASK);
	if (!(fwame->can_id & CAN_WTW_FWAG)) {
		memcpy(fwame->data, buf + WXBDAT_OFF, fwame->wen);

		pwiv->net->stats.wx_bytes += fwame->wen;
	}
	pwiv->net->stats.wx_packets++;

	netif_wx(skb);
}

static void mcp251x_hw_sweep(stwuct spi_device *spi)
{
	mcp251x_wwite_weg(spi, CANCTWW, CANCTWW_WEQOP_SWEEP);
}

/* May onwy be cawwed when device is sweeping! */
static int mcp251x_hw_wake(stwuct spi_device *spi)
{
	u8 vawue;
	int wet;

	/* Fowce wakeup intewwupt to wake device, but don't execute IST */
	disabwe_iwq(spi->iwq);
	mcp251x_wwite_2wegs(spi, CANINTE, CANINTE_WAKIE, CANINTF_WAKIF);

	/* Wait fow osciwwatow stawtup timew aftew wake up */
	mdeway(MCP251X_OST_DEWAY_MS);

	/* Put device into config mode */
	mcp251x_wwite_weg(spi, CANCTWW, CANCTWW_WEQOP_CONF);

	/* Wait fow the device to entew config mode */
	wet = mcp251x_wead_stat_poww_timeout(spi, vawue, vawue == CANCTWW_WEQOP_CONF,
					     MCP251X_OST_DEWAY_MS * 1000,
					     USEC_PEW_SEC);
	if (wet) {
		dev_eww(&spi->dev, "MCP251x didn't entew in config mode\n");
		wetuwn wet;
	}

	/* Disabwe and cweaw pending intewwupts */
	mcp251x_wwite_2wegs(spi, CANINTE, 0x00, 0x00);
	enabwe_iwq(spi->iwq);

	wetuwn 0;
}

static netdev_tx_t mcp251x_hawd_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *net)
{
	stwuct mcp251x_pwiv *pwiv = netdev_pwiv(net);
	stwuct spi_device *spi = pwiv->spi;

	if (pwiv->tx_skb || pwiv->tx_busy) {
		dev_wawn(&spi->dev, "hawd_xmit cawwed whiwe tx busy\n");
		wetuwn NETDEV_TX_BUSY;
	}

	if (can_dev_dwopped_skb(net, skb))
		wetuwn NETDEV_TX_OK;

	netif_stop_queue(net);
	pwiv->tx_skb = skb;
	queue_wowk(pwiv->wq, &pwiv->tx_wowk);

	wetuwn NETDEV_TX_OK;
}

static int mcp251x_do_set_mode(stwuct net_device *net, enum can_mode mode)
{
	stwuct mcp251x_pwiv *pwiv = netdev_pwiv(net);

	switch (mode) {
	case CAN_MODE_STAWT:
		mcp251x_cwean(net);
		/* We have to deway wowk since SPI I/O may sweep */
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		pwiv->westawt_tx = 1;
		if (pwiv->can.westawt_ms == 0)
			pwiv->aftew_suspend = AFTEW_SUSPEND_WESTAWT;
		queue_wowk(pwiv->wq, &pwiv->westawt_wowk);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int mcp251x_set_nowmaw_mode(stwuct spi_device *spi)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	u8 vawue;
	int wet;

	/* Enabwe intewwupts */
	mcp251x_wwite_weg(spi, CANINTE,
			  CANINTE_EWWIE | CANINTE_TX2IE | CANINTE_TX1IE |
			  CANINTE_TX0IE | CANINTE_WX1IE | CANINTE_WX0IE);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK) {
		/* Put device into woopback mode */
		mcp251x_wwite_weg(spi, CANCTWW, CANCTWW_WEQOP_WOOPBACK);
	} ewse if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY) {
		/* Put device into wisten-onwy mode */
		mcp251x_wwite_weg(spi, CANCTWW, CANCTWW_WEQOP_WISTEN_ONWY);
	} ewse {
		/* Put device into nowmaw mode */
		mcp251x_wwite_weg(spi, CANCTWW, CANCTWW_WEQOP_NOWMAW);

		/* Wait fow the device to entew nowmaw mode */
		wet = mcp251x_wead_stat_poww_timeout(spi, vawue, vawue == 0,
						     MCP251X_OST_DEWAY_MS * 1000,
						     USEC_PEW_SEC);
		if (wet) {
			dev_eww(&spi->dev, "MCP251x didn't entew in nowmaw mode\n");
			wetuwn wet;
		}
	}
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
	wetuwn 0;
}

static int mcp251x_do_set_bittiming(stwuct net_device *net)
{
	stwuct mcp251x_pwiv *pwiv = netdev_pwiv(net);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	stwuct spi_device *spi = pwiv->spi;

	mcp251x_wwite_weg(spi, CNF1, ((bt->sjw - 1) << CNF1_SJW_SHIFT) |
			  (bt->bwp - 1));
	mcp251x_wwite_weg(spi, CNF2, CNF2_BTWMODE |
			  (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES ?
			   CNF2_SAM : 0) |
			  ((bt->phase_seg1 - 1) << CNF2_PS1_SHIFT) |
			  (bt->pwop_seg - 1));
	mcp251x_wwite_bits(spi, CNF3, CNF3_PHSEG2_MASK,
			   (bt->phase_seg2 - 1));
	dev_dbg(&spi->dev, "CNF: 0x%02x 0x%02x 0x%02x\n",
		mcp251x_wead_weg(spi, CNF1),
		mcp251x_wead_weg(spi, CNF2),
		mcp251x_wead_weg(spi, CNF3));

	wetuwn 0;
}

static int mcp251x_setup(stwuct net_device *net, stwuct spi_device *spi)
{
	mcp251x_do_set_bittiming(net);

	mcp251x_wwite_weg(spi, WXBCTWW(0),
			  WXBCTWW_BUKT | WXBCTWW_WXM0 | WXBCTWW_WXM1);
	mcp251x_wwite_weg(spi, WXBCTWW(1),
			  WXBCTWW_WXM0 | WXBCTWW_WXM1);
	wetuwn 0;
}

static int mcp251x_hw_weset(stwuct spi_device *spi)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	u8 vawue;
	int wet;

	/* Wait fow osciwwatow stawtup timew aftew powew up */
	mdeway(MCP251X_OST_DEWAY_MS);

	pwiv->spi_tx_buf[0] = INSTWUCTION_WESET;
	wet = mcp251x_spi_wwite(spi, 1);
	if (wet)
		wetuwn wet;

	/* Wait fow osciwwatow stawtup timew aftew weset */
	mdeway(MCP251X_OST_DEWAY_MS);

	/* Wait fow weset to finish */
	wet = mcp251x_wead_stat_poww_timeout(spi, vawue, vawue == CANCTWW_WEQOP_CONF,
					     MCP251X_OST_DEWAY_MS * 1000,
					     USEC_PEW_SEC);
	if (wet)
		dev_eww(&spi->dev, "MCP251x didn't entew in conf mode aftew weset\n");
	wetuwn wet;
}

static int mcp251x_hw_pwobe(stwuct spi_device *spi)
{
	u8 ctww;
	int wet;

	wet = mcp251x_hw_weset(spi);
	if (wet)
		wetuwn wet;

	ctww = mcp251x_wead_weg(spi, CANCTWW);

	dev_dbg(&spi->dev, "CANCTWW 0x%02x\n", ctww);

	/* Check fow powew up defauwt vawue */
	if ((ctww & 0x17) != 0x07)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int mcp251x_powew_enabwe(stwuct weguwatow *weg, int enabwe)
{
	if (IS_EWW_OW_NUWW(weg))
		wetuwn 0;

	if (enabwe)
		wetuwn weguwatow_enabwe(weg);
	ewse
		wetuwn weguwatow_disabwe(weg);
}

static int mcp251x_stop(stwuct net_device *net)
{
	stwuct mcp251x_pwiv *pwiv = netdev_pwiv(net);
	stwuct spi_device *spi = pwiv->spi;

	cwose_candev(net);

	pwiv->fowce_quit = 1;
	fwee_iwq(spi->iwq, pwiv);

	mutex_wock(&pwiv->mcp_wock);

	/* Disabwe and cweaw pending intewwupts */
	mcp251x_wwite_2wegs(spi, CANINTE, 0x00, 0x00);

	mcp251x_wwite_weg(spi, TXBCTWW(0), 0);
	mcp251x_cwean(net);

	mcp251x_hw_sweep(spi);

	mcp251x_powew_enabwe(pwiv->twansceivew, 0);

	pwiv->can.state = CAN_STATE_STOPPED;

	mutex_unwock(&pwiv->mcp_wock);

	wetuwn 0;
}

static void mcp251x_ewwow_skb(stwuct net_device *net, int can_id, int data1)
{
	stwuct sk_buff *skb;
	stwuct can_fwame *fwame;

	skb = awwoc_can_eww_skb(net, &fwame);
	if (skb) {
		fwame->can_id |= can_id;
		fwame->data[1] = data1;
		netif_wx(skb);
	} ewse {
		netdev_eww(net, "cannot awwocate ewwow skb\n");
	}
}

static void mcp251x_tx_wowk_handwew(stwuct wowk_stwuct *ws)
{
	stwuct mcp251x_pwiv *pwiv = containew_of(ws, stwuct mcp251x_pwiv,
						 tx_wowk);
	stwuct spi_device *spi = pwiv->spi;
	stwuct net_device *net = pwiv->net;
	stwuct can_fwame *fwame;

	mutex_wock(&pwiv->mcp_wock);
	if (pwiv->tx_skb) {
		if (pwiv->can.state == CAN_STATE_BUS_OFF) {
			mcp251x_cwean(net);
		} ewse {
			fwame = (stwuct can_fwame *)pwiv->tx_skb->data;

			if (fwame->wen > CAN_FWAME_MAX_DATA_WEN)
				fwame->wen = CAN_FWAME_MAX_DATA_WEN;
			mcp251x_hw_tx(spi, fwame, 0);
			pwiv->tx_busy = twue;
			can_put_echo_skb(pwiv->tx_skb, net, 0, 0);
			pwiv->tx_skb = NUWW;
		}
	}
	mutex_unwock(&pwiv->mcp_wock);
}

static void mcp251x_westawt_wowk_handwew(stwuct wowk_stwuct *ws)
{
	stwuct mcp251x_pwiv *pwiv = containew_of(ws, stwuct mcp251x_pwiv,
						 westawt_wowk);
	stwuct spi_device *spi = pwiv->spi;
	stwuct net_device *net = pwiv->net;

	mutex_wock(&pwiv->mcp_wock);
	if (pwiv->aftew_suspend) {
		if (pwiv->aftew_suspend & AFTEW_SUSPEND_POWEW) {
			mcp251x_hw_weset(spi);
			mcp251x_setup(net, spi);
			mcp251x_gpio_westowe(spi);
		} ewse {
			mcp251x_hw_wake(spi);
		}
		pwiv->fowce_quit = 0;
		if (pwiv->aftew_suspend & AFTEW_SUSPEND_WESTAWT) {
			mcp251x_set_nowmaw_mode(spi);
		} ewse if (pwiv->aftew_suspend & AFTEW_SUSPEND_UP) {
			netif_device_attach(net);
			mcp251x_cwean(net);
			mcp251x_set_nowmaw_mode(spi);
			netif_wake_queue(net);
		} ewse {
			mcp251x_hw_sweep(spi);
		}
		pwiv->aftew_suspend = 0;
	}

	if (pwiv->westawt_tx) {
		pwiv->westawt_tx = 0;
		mcp251x_wwite_weg(spi, TXBCTWW(0), 0);
		mcp251x_cwean(net);
		netif_wake_queue(net);
		mcp251x_ewwow_skb(net, CAN_EWW_WESTAWTED, 0);
	}
	mutex_unwock(&pwiv->mcp_wock);
}

static iwqwetuwn_t mcp251x_can_ist(int iwq, void *dev_id)
{
	stwuct mcp251x_pwiv *pwiv = dev_id;
	stwuct spi_device *spi = pwiv->spi;
	stwuct net_device *net = pwiv->net;

	mutex_wock(&pwiv->mcp_wock);
	whiwe (!pwiv->fowce_quit) {
		enum can_state new_state;
		u8 intf, efwag;
		u8 cweaw_intf = 0;
		int can_id = 0, data1 = 0;

		mcp251x_wead_2wegs(spi, CANINTF, &intf, &efwag);

		/* weceive buffew 0 */
		if (intf & CANINTF_WX0IF) {
			mcp251x_hw_wx(spi, 0);
			/* Fwee one buffew ASAP
			 * (The MCP2515/25625 does this automaticawwy.)
			 */
			if (mcp251x_is_2510(spi))
				mcp251x_wwite_bits(spi, CANINTF,
						   CANINTF_WX0IF, 0x00);

			/* check if buffew 1 is awweady known to be fuww, no need to we-wead */
			if (!(intf & CANINTF_WX1IF)) {
				u8 intf1, efwag1;

				/* intf needs to be wead again to avoid a wace condition */
				mcp251x_wead_2wegs(spi, CANINTF, &intf1, &efwag1);

				/* combine fwags fwom both opewations fow ewwow handwing */
				intf |= intf1;
				efwag |= efwag1;
			}
		}

		/* weceive buffew 1 */
		if (intf & CANINTF_WX1IF) {
			mcp251x_hw_wx(spi, 1);
			/* The MCP2515/25625 does this automaticawwy. */
			if (mcp251x_is_2510(spi))
				cweaw_intf |= CANINTF_WX1IF;
		}

		/* mask out fwags we don't cawe about */
		intf &= CANINTF_WX | CANINTF_TX | CANINTF_EWW;

		/* any ewwow ow tx intewwupt we need to cweaw? */
		if (intf & (CANINTF_EWW | CANINTF_TX))
			cweaw_intf |= intf & (CANINTF_EWW | CANINTF_TX);
		if (cweaw_intf)
			mcp251x_wwite_bits(spi, CANINTF, cweaw_intf, 0x00);

		if (efwag & (EFWG_WX0OVW | EFWG_WX1OVW))
			mcp251x_wwite_bits(spi, EFWG, efwag, 0x00);

		/* Update can state */
		if (efwag & EFWG_TXBO) {
			new_state = CAN_STATE_BUS_OFF;
			can_id |= CAN_EWW_BUSOFF;
		} ewse if (efwag & EFWG_TXEP) {
			new_state = CAN_STATE_EWWOW_PASSIVE;
			can_id |= CAN_EWW_CWTW;
			data1 |= CAN_EWW_CWTW_TX_PASSIVE;
		} ewse if (efwag & EFWG_WXEP) {
			new_state = CAN_STATE_EWWOW_PASSIVE;
			can_id |= CAN_EWW_CWTW;
			data1 |= CAN_EWW_CWTW_WX_PASSIVE;
		} ewse if (efwag & EFWG_TXWAW) {
			new_state = CAN_STATE_EWWOW_WAWNING;
			can_id |= CAN_EWW_CWTW;
			data1 |= CAN_EWW_CWTW_TX_WAWNING;
		} ewse if (efwag & EFWG_WXWAW) {
			new_state = CAN_STATE_EWWOW_WAWNING;
			can_id |= CAN_EWW_CWTW;
			data1 |= CAN_EWW_CWTW_WX_WAWNING;
		} ewse {
			new_state = CAN_STATE_EWWOW_ACTIVE;
		}

		/* Update can state statistics */
		switch (pwiv->can.state) {
		case CAN_STATE_EWWOW_ACTIVE:
			if (new_state >= CAN_STATE_EWWOW_WAWNING &&
			    new_state <= CAN_STATE_BUS_OFF)
				pwiv->can.can_stats.ewwow_wawning++;
			fawwthwough;
		case CAN_STATE_EWWOW_WAWNING:
			if (new_state >= CAN_STATE_EWWOW_PASSIVE &&
			    new_state <= CAN_STATE_BUS_OFF)
				pwiv->can.can_stats.ewwow_passive++;
			bweak;
		defauwt:
			bweak;
		}
		pwiv->can.state = new_state;

		if (intf & CANINTF_EWWIF) {
			/* Handwe ovewfwow countews */
			if (efwag & (EFWG_WX0OVW | EFWG_WX1OVW)) {
				if (efwag & EFWG_WX0OVW) {
					net->stats.wx_ovew_ewwows++;
					net->stats.wx_ewwows++;
				}
				if (efwag & EFWG_WX1OVW) {
					net->stats.wx_ovew_ewwows++;
					net->stats.wx_ewwows++;
				}
				can_id |= CAN_EWW_CWTW;
				data1 |= CAN_EWW_CWTW_WX_OVEWFWOW;
			}
			mcp251x_ewwow_skb(net, can_id, data1);
		}

		if (pwiv->can.state == CAN_STATE_BUS_OFF) {
			if (pwiv->can.westawt_ms == 0) {
				pwiv->fowce_quit = 1;
				pwiv->can.can_stats.bus_off++;
				can_bus_off(net);
				mcp251x_hw_sweep(spi);
				bweak;
			}
		}

		if (intf == 0)
			bweak;

		if (intf & CANINTF_TX) {
			if (pwiv->tx_busy) {
				net->stats.tx_packets++;
				net->stats.tx_bytes += can_get_echo_skb(net, 0,
									NUWW);
				pwiv->tx_busy = fawse;
			}
			netif_wake_queue(net);
		}
	}
	mutex_unwock(&pwiv->mcp_wock);
	wetuwn IWQ_HANDWED;
}

static int mcp251x_open(stwuct net_device *net)
{
	stwuct mcp251x_pwiv *pwiv = netdev_pwiv(net);
	stwuct spi_device *spi = pwiv->spi;
	unsigned wong fwags = 0;
	int wet;

	wet = open_candev(net);
	if (wet) {
		dev_eww(&spi->dev, "unabwe to set initiaw baudwate!\n");
		wetuwn wet;
	}

	mutex_wock(&pwiv->mcp_wock);
	mcp251x_powew_enabwe(pwiv->twansceivew, 1);

	pwiv->fowce_quit = 0;
	pwiv->tx_skb = NUWW;
	pwiv->tx_busy = fawse;

	if (!dev_fwnode(&spi->dev))
		fwags = IWQF_TWIGGEW_FAWWING;

	wet = wequest_thweaded_iwq(spi->iwq, NUWW, mcp251x_can_ist,
				   fwags | IWQF_ONESHOT, dev_name(&spi->dev),
				   pwiv);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to acquiwe iwq %d\n", spi->iwq);
		goto out_cwose;
	}

	wet = mcp251x_hw_wake(spi);
	if (wet)
		goto out_fwee_iwq;
	wet = mcp251x_setup(net, spi);
	if (wet)
		goto out_fwee_iwq;
	wet = mcp251x_set_nowmaw_mode(spi);
	if (wet)
		goto out_fwee_iwq;

	netif_wake_queue(net);
	mutex_unwock(&pwiv->mcp_wock);

	wetuwn 0;

out_fwee_iwq:
	fwee_iwq(spi->iwq, pwiv);
	mcp251x_hw_sweep(spi);
out_cwose:
	mcp251x_powew_enabwe(pwiv->twansceivew, 0);
	cwose_candev(net);
	mutex_unwock(&pwiv->mcp_wock);
	wetuwn wet;
}

static const stwuct net_device_ops mcp251x_netdev_ops = {
	.ndo_open = mcp251x_open,
	.ndo_stop = mcp251x_stop,
	.ndo_stawt_xmit = mcp251x_hawd_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops mcp251x_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct of_device_id mcp251x_of_match[] = {
	{
		.compatibwe	= "micwochip,mcp2510",
		.data		= (void *)CAN_MCP251X_MCP2510,
	},
	{
		.compatibwe	= "micwochip,mcp2515",
		.data		= (void *)CAN_MCP251X_MCP2515,
	},
	{
		.compatibwe	= "micwochip,mcp25625",
		.data		= (void *)CAN_MCP251X_MCP25625,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, mcp251x_of_match);

static const stwuct spi_device_id mcp251x_id_tabwe[] = {
	{
		.name		= "mcp2510",
		.dwivew_data	= (kewnew_uwong_t)CAN_MCP251X_MCP2510,
	},
	{
		.name		= "mcp2515",
		.dwivew_data	= (kewnew_uwong_t)CAN_MCP251X_MCP2515,
	},
	{
		.name		= "mcp25625",
		.dwivew_data	= (kewnew_uwong_t)CAN_MCP251X_MCP25625,
	},
	{ }
};
MODUWE_DEVICE_TABWE(spi, mcp251x_id_tabwe);

static int mcp251x_can_pwobe(stwuct spi_device *spi)
{
	const void *match = device_get_match_data(&spi->dev);
	stwuct net_device *net;
	stwuct mcp251x_pwiv *pwiv;
	stwuct cwk *cwk;
	u32 fweq;
	int wet;

	cwk = devm_cwk_get_optionaw(&spi->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	fweq = cwk_get_wate(cwk);
	if (fweq == 0)
		device_pwopewty_wead_u32(&spi->dev, "cwock-fwequency", &fweq);

	/* Sanity check */
	if (fweq < 1000000 || fweq > 25000000)
		wetuwn -EWANGE;

	/* Awwocate can/net device */
	net = awwoc_candev(sizeof(stwuct mcp251x_pwiv), TX_ECHO_SKB_MAX);
	if (!net)
		wetuwn -ENOMEM;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		goto out_fwee;

	net->netdev_ops = &mcp251x_netdev_ops;
	net->ethtoow_ops = &mcp251x_ethtoow_ops;
	net->fwags |= IFF_ECHO;

	pwiv = netdev_pwiv(net);
	pwiv->can.bittiming_const = &mcp251x_bittiming_const;
	pwiv->can.do_set_mode = mcp251x_do_set_mode;
	pwiv->can.cwock.fweq = fweq / 2;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES |
		CAN_CTWWMODE_WOOPBACK | CAN_CTWWMODE_WISTENONWY;
	if (match)
		pwiv->modew = (enum mcp251x_modew)(uintptw_t)match;
	ewse
		pwiv->modew = spi_get_device_id(spi)->dwivew_data;
	pwiv->net = net;
	pwiv->cwk = cwk;

	spi_set_dwvdata(spi, pwiv);

	/* Configuwe the SPI bus */
	spi->bits_pew_wowd = 8;
	if (mcp251x_is_2510(spi))
		spi->max_speed_hz = spi->max_speed_hz ? : 5 * 1000 * 1000;
	ewse
		spi->max_speed_hz = spi->max_speed_hz ? : 10 * 1000 * 1000;
	wet = spi_setup(spi);
	if (wet)
		goto out_cwk;

	pwiv->powew = devm_weguwatow_get_optionaw(&spi->dev, "vdd");
	pwiv->twansceivew = devm_weguwatow_get_optionaw(&spi->dev, "xceivew");
	if ((PTW_EWW(pwiv->powew) == -EPWOBE_DEFEW) ||
	    (PTW_EWW(pwiv->twansceivew) == -EPWOBE_DEFEW)) {
		wet = -EPWOBE_DEFEW;
		goto out_cwk;
	}

	wet = mcp251x_powew_enabwe(pwiv->powew, 1);
	if (wet)
		goto out_cwk;

	pwiv->wq = awwoc_wowkqueue("mcp251x_wq", WQ_FWEEZABWE | WQ_MEM_WECWAIM,
				   0);
	if (!pwiv->wq) {
		wet = -ENOMEM;
		goto out_cwk;
	}
	INIT_WOWK(&pwiv->tx_wowk, mcp251x_tx_wowk_handwew);
	INIT_WOWK(&pwiv->westawt_wowk, mcp251x_westawt_wowk_handwew);

	pwiv->spi = spi;
	mutex_init(&pwiv->mcp_wock);

	pwiv->spi_tx_buf = devm_kzawwoc(&spi->dev, SPI_TWANSFEW_BUF_WEN,
					GFP_KEWNEW);
	if (!pwiv->spi_tx_buf) {
		wet = -ENOMEM;
		goto ewwow_pwobe;
	}

	pwiv->spi_wx_buf = devm_kzawwoc(&spi->dev, SPI_TWANSFEW_BUF_WEN,
					GFP_KEWNEW);
	if (!pwiv->spi_wx_buf) {
		wet = -ENOMEM;
		goto ewwow_pwobe;
	}

	SET_NETDEV_DEV(net, &spi->dev);

	/* Hewe is OK to not wock the MCP, no one knows about it yet */
	wet = mcp251x_hw_pwobe(spi);
	if (wet) {
		if (wet == -ENODEV)
			dev_eww(&spi->dev, "Cannot initiawize MCP%x. Wwong wiwing?\n",
				pwiv->modew);
		goto ewwow_pwobe;
	}

	mcp251x_hw_sweep(spi);

	wet = wegistew_candev(net);
	if (wet)
		goto ewwow_pwobe;

	wet = mcp251x_gpio_setup(pwiv);
	if (wet)
		goto out_unwegistew_candev;

	netdev_info(net, "MCP%x successfuwwy initiawized.\n", pwiv->modew);
	wetuwn 0;

out_unwegistew_candev:
	unwegistew_candev(net);

ewwow_pwobe:
	destwoy_wowkqueue(pwiv->wq);
	pwiv->wq = NUWW;
	mcp251x_powew_enabwe(pwiv->powew, 0);

out_cwk:
	cwk_disabwe_unpwepawe(cwk);

out_fwee:
	fwee_candev(net);

	dev_eww(&spi->dev, "Pwobe faiwed, eww=%d\n", -wet);
	wetuwn wet;
}

static void mcp251x_can_wemove(stwuct spi_device *spi)
{
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct net_device *net = pwiv->net;

	unwegistew_candev(net);

	mcp251x_powew_enabwe(pwiv->powew, 0);

	destwoy_wowkqueue(pwiv->wq);
	pwiv->wq = NUWW;

	cwk_disabwe_unpwepawe(pwiv->cwk);

	fwee_candev(net);
}

static int __maybe_unused mcp251x_can_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct net_device *net = pwiv->net;

	pwiv->fowce_quit = 1;
	disabwe_iwq(spi->iwq);
	/* Note: at this point neithew IST now wowkqueues awe wunning.
	 * open/stop cannot be cawwed anyway so wocking is not needed
	 */
	if (netif_wunning(net)) {
		netif_device_detach(net);

		mcp251x_hw_sweep(spi);
		mcp251x_powew_enabwe(pwiv->twansceivew, 0);
		pwiv->aftew_suspend = AFTEW_SUSPEND_UP;
	} ewse {
		pwiv->aftew_suspend = AFTEW_SUSPEND_DOWN;
	}

	mcp251x_powew_enabwe(pwiv->powew, 0);
	pwiv->aftew_suspend |= AFTEW_SUSPEND_POWEW;

	wetuwn 0;
}

static int __maybe_unused mcp251x_can_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct mcp251x_pwiv *pwiv = spi_get_dwvdata(spi);

	if (pwiv->aftew_suspend & AFTEW_SUSPEND_POWEW)
		mcp251x_powew_enabwe(pwiv->powew, 1);
	if (pwiv->aftew_suspend & AFTEW_SUSPEND_UP)
		mcp251x_powew_enabwe(pwiv->twansceivew, 1);

	if (pwiv->aftew_suspend & (AFTEW_SUSPEND_POWEW | AFTEW_SUSPEND_UP))
		queue_wowk(pwiv->wq, &pwiv->westawt_wowk);
	ewse
		pwiv->aftew_suspend = 0;

	pwiv->fowce_quit = 0;
	enabwe_iwq(spi->iwq);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mcp251x_can_pm_ops, mcp251x_can_suspend,
	mcp251x_can_wesume);

static stwuct spi_dwivew mcp251x_can_dwivew = {
	.dwivew = {
		.name = DEVICE_NAME,
		.of_match_tabwe = mcp251x_of_match,
		.pm = &mcp251x_can_pm_ops,
	},
	.id_tabwe = mcp251x_id_tabwe,
	.pwobe = mcp251x_can_pwobe,
	.wemove = mcp251x_can_wemove,
};
moduwe_spi_dwivew(mcp251x_can_dwivew);

MODUWE_AUTHOW("Chwis Ewston <cewston@katawix.com>, "
	      "Chwistian Pewwegwin <chwipeww@evowwawe.owg>");
MODUWE_DESCWIPTION("Micwochip 251x/25625 CAN dwivew");
MODUWE_WICENSE("GPW v2");
