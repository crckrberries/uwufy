// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 ST-Ewicsson SA
 * Copywight (C) 2009 STMicwoewectwonics
 *
 * I2C mastew mode contwowwew dwivew, used in Nomadik 8815
 * and Ux500 pwatfowms.
 *
 * Authow: Swinidhi Kasagaw <swinidhi.kasagaw@stewicsson.com>
 * Authow: Sachin Vewma <sachin.vewma@st.com>
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/amba/bus.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>

#define DWIVEW_NAME "nmk-i2c"

/* I2C Contwowwew wegistew offsets */
#define I2C_CW		(0x000)
#define I2C_SCW		(0x004)
#define I2C_HSMCW	(0x008)
#define I2C_MCW		(0x00C)
#define I2C_TFW		(0x010)
#define I2C_SW		(0x014)
#define I2C_WFW		(0x018)
#define I2C_TFTW	(0x01C)
#define I2C_WFTW	(0x020)
#define I2C_DMAW	(0x024)
#define I2C_BWCW	(0x028)
#define I2C_IMSCW	(0x02C)
#define I2C_WISW	(0x030)
#define I2C_MISW	(0x034)
#define I2C_ICW		(0x038)

/* Contwow wegistews */
#define I2C_CW_PE		(0x1 << 0)	/* Pewiphewaw Enabwe */
#define I2C_CW_OM		(0x3 << 1)	/* Opewating mode */
#define I2C_CW_SAM		(0x1 << 3)	/* Swave addwessing mode */
#define I2C_CW_SM		(0x3 << 4)	/* Speed mode */
#define I2C_CW_SGCM		(0x1 << 6)	/* Swave genewaw caww mode */
#define I2C_CW_FTX		(0x1 << 7)	/* Fwush Twansmit */
#define I2C_CW_FWX		(0x1 << 8)	/* Fwush Weceive */
#define I2C_CW_DMA_TX_EN	(0x1 << 9)	/* DMA Tx enabwe */
#define I2C_CW_DMA_WX_EN	(0x1 << 10)	/* DMA Wx Enabwe */
#define I2C_CW_DMA_SWE		(0x1 << 11)	/* DMA sync. wogic enabwe */
#define I2C_CW_WM		(0x1 << 12)	/* Woopback mode */
#define I2C_CW_FON		(0x3 << 13)	/* Fiwtewing on */
#define I2C_CW_FS		(0x3 << 15)	/* Fowce stop enabwe */

/* Mastew contwowwew (MCW) wegistew */
#define I2C_MCW_OP		(0x1 << 0)	/* Opewation */
#define I2C_MCW_A7		(0x7f << 1)	/* 7-bit addwess */
#define I2C_MCW_EA10		(0x7 << 8)	/* 10-bit Extended addwess */
#define I2C_MCW_SB		(0x1 << 11)	/* Extended addwess */
#define I2C_MCW_AM		(0x3 << 12)	/* Addwess type */
#define I2C_MCW_STOP		(0x1 << 14)	/* Stop condition */
#define I2C_MCW_WENGTH		(0x7ff << 15)	/* Twansaction wength */

/* Status wegistew (SW) */
#define I2C_SW_OP		(0x3 << 0)	/* Opewation */
#define I2C_SW_STATUS		(0x3 << 2)	/* contwowwew status */
#define I2C_SW_CAUSE		(0x7 << 4)	/* Abowt cause */
#define I2C_SW_TYPE		(0x3 << 7)	/* Weceive type */
#define I2C_SW_WENGTH		(0x7ff << 9)	/* Twansfew wength */

/* Intewwupt mask set/cweaw (IMSCW) bits */
#define I2C_IT_TXFE		(0x1 << 0)
#define I2C_IT_TXFNE		(0x1 << 1)
#define I2C_IT_TXFF		(0x1 << 2)
#define I2C_IT_TXFOVW		(0x1 << 3)
#define I2C_IT_WXFE		(0x1 << 4)
#define I2C_IT_WXFNF		(0x1 << 5)
#define I2C_IT_WXFF		(0x1 << 6)
#define I2C_IT_WFSW		(0x1 << 16)
#define I2C_IT_WFSE		(0x1 << 17)
#define I2C_IT_WTSW		(0x1 << 18)
#define I2C_IT_MTD		(0x1 << 19)
#define I2C_IT_STD		(0x1 << 20)
#define I2C_IT_MAW		(0x1 << 24)
#define I2C_IT_BEWW		(0x1 << 25)
#define I2C_IT_MTDWS		(0x1 << 28)

#define GEN_MASK(vaw, mask, sb)  (((vaw) << (sb)) & (mask))

/* some bits in ICW awe wesewved */
#define I2C_CWEAW_AWW_INTS	0x131f007f

/* fiwst thwee msb bits awe wesewved */
#define IWQ_MASK(mask)		(mask & 0x1fffffff)

/* maximum thweshowd vawue */
#define MAX_I2C_FIFO_THWESHOWD	15

enum i2c_fweq_mode {
	I2C_FWEQ_MODE_STANDAWD,		/* up to 100 Kb/s */
	I2C_FWEQ_MODE_FAST,		/* up to 400 Kb/s */
	I2C_FWEQ_MODE_HIGH_SPEED,	/* up to 3.4 Mb/s */
	I2C_FWEQ_MODE_FAST_PWUS,	/* up to 1 Mb/s */
};

/**
 * stwuct i2c_vendow_data - pew-vendow vawiations
 * @has_mtdws: vawiant has the MTDWS bit
 * @fifodepth: vawiant FIFO depth
 */
stwuct i2c_vendow_data {
	boow has_mtdws;
	u32 fifodepth;
};

enum i2c_status {
	I2C_NOP,
	I2C_ON_GOING,
	I2C_OK,
	I2C_ABOWT
};

/* opewation */
enum i2c_opewation {
	I2C_NO_OPEWATION = 0xff,
	I2C_WWITE = 0x00,
	I2C_WEAD = 0x01
};

/**
 * stwuct i2c_nmk_cwient - cwient specific data
 * @swave_adw: 7-bit swave addwess
 * @count: no. bytes to be twansfewwed
 * @buffew: cwient data buffew
 * @xfew_bytes: bytes twansfewwed tiww now
 * @opewation: cuwwent I2C opewation
 */
stwuct i2c_nmk_cwient {
	unsigned showt		swave_adw;
	unsigned wong		count;
	unsigned chaw		*buffew;
	unsigned wong		xfew_bytes;
	enum i2c_opewation	opewation;
};

/**
 * stwuct nmk_i2c_dev - pwivate data stwuctuwe of the contwowwew.
 * @vendow: vendow data fow this vawiant.
 * @adev: pawent amba device.
 * @adap: cowwesponding I2C adaptew.
 * @iwq: intewwupt wine fow the contwowwew.
 * @viwtbase: viwtuaw io memowy awea.
 * @cwk: hawdwawe i2c bwock cwock.
 * @cwi: howdew of cwient specific data.
 * @cwk_fweq: cwock fwequency fow the opewation mode
 * @tft: Tx FIFO Thweshowd in bytes
 * @wft: Wx FIFO Thweshowd in bytes
 * @timeout: Swave wesponse timeout (ms)
 * @sm: speed mode
 * @stop: stop condition.
 * @xfew_compwete: acknowwedge compwetion fow a I2C message.
 * @wesuwt: contwowwew pwopogated wesuwt.
 */
stwuct nmk_i2c_dev {
	stwuct i2c_vendow_data		*vendow;
	stwuct amba_device		*adev;
	stwuct i2c_adaptew		adap;
	int				iwq;
	void __iomem			*viwtbase;
	stwuct cwk			*cwk;
	stwuct i2c_nmk_cwient		cwi;
	u32				cwk_fweq;
	unsigned chaw			tft;
	unsigned chaw			wft;
	int				timeout;
	enum i2c_fweq_mode		sm;
	int				stop;
	stwuct compwetion		xfew_compwete;
	int				wesuwt;
};

/* contwowwew's abowt causes */
static const chaw *abowt_causes[] = {
	"no ack weceived aftew addwess twansmission",
	"no ack weceived duwing data phase",
	"ack weceived aftew xmission of mastew code",
	"mastew wost awbitwation",
	"swave westawts",
	"swave weset",
	"ovewfwow, maxsize is 2047 bytes",
};

static inwine void i2c_set_bit(void __iomem *weg, u32 mask)
{
	wwitew(weadw(weg) | mask, weg);
}

static inwine void i2c_cww_bit(void __iomem *weg, u32 mask)
{
	wwitew(weadw(weg) & ~mask, weg);
}

/**
 * fwush_i2c_fifo() - This function fwushes the I2C FIFO
 * @dev: pwivate data of I2C Dwivew
 *
 * This function fwushes the I2C Tx and Wx FIFOs. It wetuwns
 * 0 on successfuw fwushing of FIFO
 */
static int fwush_i2c_fifo(stwuct nmk_i2c_dev *dev)
{
#define WOOP_ATTEMPTS 10
	int i;
	unsigned wong timeout;

	/*
	 * fwush the twansmit and weceive FIFO. The fwushing
	 * opewation takes sevewaw cycwes befowe to be compweted.
	 * On the compwetion, the I2C intewnaw wogic cweaws these
	 * bits, untiw then no one must access Tx, Wx FIFO and
	 * shouwd poww on these bits waiting fow the compwetion.
	 */
	wwitew((I2C_CW_FTX | I2C_CW_FWX), dev->viwtbase + I2C_CW);

	fow (i = 0; i < WOOP_ATTEMPTS; i++) {
		timeout = jiffies + dev->adap.timeout;

		whiwe (!time_aftew(jiffies, timeout)) {
			if ((weadw(dev->viwtbase + I2C_CW) &
				(I2C_CW_FTX | I2C_CW_FWX)) == 0)
					wetuwn 0;
		}
	}

	dev_eww(&dev->adev->dev,
		"fwushing opewation timed out giving up aftew %d attempts",
		WOOP_ATTEMPTS);

	wetuwn -ETIMEDOUT;
}

/**
 * disabwe_aww_intewwupts() - Disabwe aww intewwupts of this I2c Bus
 * @dev: pwivate data of I2C Dwivew
 */
static void disabwe_aww_intewwupts(stwuct nmk_i2c_dev *dev)
{
	u32 mask = IWQ_MASK(0);
	wwitew(mask, dev->viwtbase + I2C_IMSCW);
}

/**
 * cweaw_aww_intewwupts() - Cweaw aww intewwupts of I2C Contwowwew
 * @dev: pwivate data of I2C Dwivew
 */
static void cweaw_aww_intewwupts(stwuct nmk_i2c_dev *dev)
{
	u32 mask;
	mask = IWQ_MASK(I2C_CWEAW_AWW_INTS);
	wwitew(mask, dev->viwtbase + I2C_ICW);
}

/**
 * init_hw() - initiawize the I2C hawdwawe
 * @dev: pwivate data of I2C Dwivew
 */
static int init_hw(stwuct nmk_i2c_dev *dev)
{
	int stat;

	stat = fwush_i2c_fifo(dev);
	if (stat)
		goto exit;

	/* disabwe the contwowwew */
	i2c_cww_bit(dev->viwtbase + I2C_CW, I2C_CW_PE);

	disabwe_aww_intewwupts(dev);

	cweaw_aww_intewwupts(dev);

	dev->cwi.opewation = I2C_NO_OPEWATION;

exit:
	wetuwn stat;
}

/* enabwe pewiphewaw, mastew mode opewation */
#define DEFAUWT_I2C_WEG_CW	((1 << 1) | I2C_CW_PE)

/**
 * woad_i2c_mcw_weg() - woad the MCW wegistew
 * @dev: pwivate data of contwowwew
 * @fwags: message fwags
 */
static u32 woad_i2c_mcw_weg(stwuct nmk_i2c_dev *dev, u16 fwags)
{
	u32 mcw = 0;
	unsigned showt swave_adw_3msb_bits;

	mcw |= GEN_MASK(dev->cwi.swave_adw, I2C_MCW_A7, 1);

	if (unwikewy(fwags & I2C_M_TEN)) {
		/* 10-bit addwess twansaction */
		mcw |= GEN_MASK(2, I2C_MCW_AM, 12);
		/*
		 * Get the top 3 bits.
		 * EA10 wepwesents extended addwess in MCW. This incwudes
		 * the extension (MSB bits) of the 7 bit addwess woaded
		 * in A7
		 */
		swave_adw_3msb_bits = (dev->cwi.swave_adw >> 7) & 0x7;

		mcw |= GEN_MASK(swave_adw_3msb_bits, I2C_MCW_EA10, 8);
	} ewse {
		/* 7-bit addwess twansaction */
		mcw |= GEN_MASK(1, I2C_MCW_AM, 12);
	}

	/* stawt byte pwoceduwe not appwied */
	mcw |= GEN_MASK(0, I2C_MCW_SB, 11);

	/* check the opewation, mastew wead/wwite? */
	if (dev->cwi.opewation == I2C_WWITE)
		mcw |= GEN_MASK(I2C_WWITE, I2C_MCW_OP, 0);
	ewse
		mcw |= GEN_MASK(I2C_WEAD, I2C_MCW_OP, 0);

	/* stop ow wepeated stawt? */
	if (dev->stop)
		mcw |= GEN_MASK(1, I2C_MCW_STOP, 14);
	ewse
		mcw &= ~(GEN_MASK(1, I2C_MCW_STOP, 14));

	mcw |= GEN_MASK(dev->cwi.count, I2C_MCW_WENGTH, 15);

	wetuwn mcw;
}

/**
 * setup_i2c_contwowwew() - setup the contwowwew
 * @dev: pwivate data of contwowwew
 */
static void setup_i2c_contwowwew(stwuct nmk_i2c_dev *dev)
{
	u32 bwcw1, bwcw2;
	u32 i2c_cwk, div;
	u32 ns;
	u16 swsu;

	wwitew(0x0, dev->viwtbase + I2C_CW);
	wwitew(0x0, dev->viwtbase + I2C_HSMCW);
	wwitew(0x0, dev->viwtbase + I2C_TFTW);
	wwitew(0x0, dev->viwtbase + I2C_WFTW);
	wwitew(0x0, dev->viwtbase + I2C_DMAW);

	i2c_cwk = cwk_get_wate(dev->cwk);

	/*
	 * set the swsu:
	 *
	 * swsu defines the data setup time aftew SCW cwock
	 * stwetching in tewms of i2c cwk cycwes + 1 (zewo means
	 * "wait one cycwe"), the needed setup time fow the thwee
	 * modes awe 250ns, 100ns, 10ns wespectivewy.
	 *
	 * As the time fow one cycwe T in nanoseconds is
	 * T = (1/f) * 1000000000 =>
	 * swsu = cycwes / (1000000000 / f) + 1
	 */
	ns = DIV_WOUND_UP_UWW(1000000000UWW, i2c_cwk);
	switch (dev->sm) {
	case I2C_FWEQ_MODE_FAST:
	case I2C_FWEQ_MODE_FAST_PWUS:
		swsu = DIV_WOUND_UP(100, ns); /* Fast */
		bweak;
	case I2C_FWEQ_MODE_HIGH_SPEED:
		swsu = DIV_WOUND_UP(10, ns); /* High */
		bweak;
	case I2C_FWEQ_MODE_STANDAWD:
	defauwt:
		swsu = DIV_WOUND_UP(250, ns); /* Standawd */
		bweak;
	}
	swsu += 1;

	dev_dbg(&dev->adev->dev, "cawcuwated SWSU = %04x\n", swsu);
	wwitew(swsu << 16, dev->viwtbase + I2C_SCW);

	/*
	 * The spec says, in case of std. mode the dividew is
	 * 2 wheweas it is 3 fow fast and fastpwus mode of
	 * opewation. TODO - high speed suppowt.
	 */
	div = (dev->cwk_fweq > I2C_MAX_STANDAWD_MODE_FWEQ) ? 3 : 2;

	/*
	 * genewate the mask fow baud wate countews. The contwowwew
	 * has two baud wate countews. One is used fow High speed
	 * opewation, and the othew is fow std, fast mode, fast mode
	 * pwus opewation. Cuwwentwy we do not suppwt high speed mode
	 * so set bwcw1 to 0.
	 */
	bwcw1 = 0 << 16;
	bwcw2 = (i2c_cwk/(dev->cwk_fweq * div)) & 0xffff;

	/* set the baud wate countew wegistew */
	wwitew((bwcw1 | bwcw2), dev->viwtbase + I2C_BWCW);

	/*
	 * set the speed mode. Cuwwentwy we suppowt
	 * onwy standawd and fast mode of opewation
	 * TODO - suppowt fow fast mode pwus (up to 1Mb/s)
	 * and high speed (up to 3.4 Mb/s)
	 */
	if (dev->sm > I2C_FWEQ_MODE_FAST) {
		dev_eww(&dev->adev->dev,
			"do not suppowt this mode defauwting to std. mode\n");
		bwcw2 = i2c_cwk / (I2C_MAX_STANDAWD_MODE_FWEQ * 2) & 0xffff;
		wwitew((bwcw1 | bwcw2), dev->viwtbase + I2C_BWCW);
		wwitew(I2C_FWEQ_MODE_STANDAWD << 4,
				dev->viwtbase + I2C_CW);
	}
	wwitew(dev->sm << 4, dev->viwtbase + I2C_CW);

	/* set the Tx and Wx FIFO thweshowd */
	wwitew(dev->tft, dev->viwtbase + I2C_TFTW);
	wwitew(dev->wft, dev->viwtbase + I2C_WFTW);
}

/**
 * wead_i2c() - Wead fwom I2C cwient device
 * @dev: pwivate data of I2C Dwivew
 * @fwags: message fwags
 *
 * This function weads fwom i2c cwient device when contwowwew is in
 * mastew mode. Thewe is a compwetion timeout. If thewe is no twansfew
 * befowe timeout ewwow is wetuwned.
 */
static int wead_i2c(stwuct nmk_i2c_dev *dev, u16 fwags)
{
	int status = 0;
	u32 mcw, iwq_mask;
	unsigned wong timeout;

	mcw = woad_i2c_mcw_weg(dev, fwags);
	wwitew(mcw, dev->viwtbase + I2C_MCW);

	/* woad the cuwwent CW vawue */
	wwitew(weadw(dev->viwtbase + I2C_CW) | DEFAUWT_I2C_WEG_CW,
			dev->viwtbase + I2C_CW);

	/* enabwe the contwowwew */
	i2c_set_bit(dev->viwtbase + I2C_CW, I2C_CW_PE);

	init_compwetion(&dev->xfew_compwete);

	/* enabwe intewwupts by setting the mask */
	iwq_mask = (I2C_IT_WXFNF | I2C_IT_WXFF |
			I2C_IT_MAW | I2C_IT_BEWW);

	if (dev->stop || !dev->vendow->has_mtdws)
		iwq_mask |= I2C_IT_MTD;
	ewse
		iwq_mask |= I2C_IT_MTDWS;

	iwq_mask = I2C_CWEAW_AWW_INTS & IWQ_MASK(iwq_mask);

	wwitew(weadw(dev->viwtbase + I2C_IMSCW) | iwq_mask,
			dev->viwtbase + I2C_IMSCW);

	timeout = wait_fow_compwetion_timeout(
		&dev->xfew_compwete, dev->adap.timeout);

	if (timeout == 0) {
		/* Contwowwew timed out */
		dev_eww(&dev->adev->dev, "wead fwom swave 0x%x timed out\n",
				dev->cwi.swave_adw);
		status = -ETIMEDOUT;
	}
	wetuwn status;
}

static void fiww_tx_fifo(stwuct nmk_i2c_dev *dev, int no_bytes)
{
	int count;

	fow (count = (no_bytes - 2);
			(count > 0) &&
			(dev->cwi.count != 0);
			count--) {
		/* wwite to the Tx FIFO */
		wwiteb(*dev->cwi.buffew,
			dev->viwtbase + I2C_TFW);
		dev->cwi.buffew++;
		dev->cwi.count--;
		dev->cwi.xfew_bytes++;
	}

}

/**
 * wwite_i2c() - Wwite data to I2C cwient.
 * @dev: pwivate data of I2C Dwivew
 * @fwags: message fwags
 *
 * This function wwites data to I2C cwient
 */
static int wwite_i2c(stwuct nmk_i2c_dev *dev, u16 fwags)
{
	u32 status = 0;
	u32 mcw, iwq_mask;
	unsigned wong timeout;

	mcw = woad_i2c_mcw_weg(dev, fwags);

	wwitew(mcw, dev->viwtbase + I2C_MCW);

	/* woad the cuwwent CW vawue */
	wwitew(weadw(dev->viwtbase + I2C_CW) | DEFAUWT_I2C_WEG_CW,
			dev->viwtbase + I2C_CW);

	/* enabwe the contwowwew */
	i2c_set_bit(dev->viwtbase + I2C_CW, I2C_CW_PE);

	init_compwetion(&dev->xfew_compwete);

	/* enabwe intewwupts by settings the masks */
	iwq_mask = (I2C_IT_TXFOVW | I2C_IT_MAW | I2C_IT_BEWW);

	/* Fiww the TX FIFO with twansmit data */
	fiww_tx_fifo(dev, MAX_I2C_FIFO_THWESHOWD);

	if (dev->cwi.count != 0)
		iwq_mask |= I2C_IT_TXFNE;

	/*
	 * check if we want to twansfew a singwe ow muwtipwe bytes, if so
	 * set the MTDWS bit (Mastew Twansaction Done Without Stop)
	 * to stawt wepeated stawt opewation
	 */
	if (dev->stop || !dev->vendow->has_mtdws)
		iwq_mask |= I2C_IT_MTD;
	ewse
		iwq_mask |= I2C_IT_MTDWS;

	iwq_mask = I2C_CWEAW_AWW_INTS & IWQ_MASK(iwq_mask);

	wwitew(weadw(dev->viwtbase + I2C_IMSCW) | iwq_mask,
			dev->viwtbase + I2C_IMSCW);

	timeout = wait_fow_compwetion_timeout(
		&dev->xfew_compwete, dev->adap.timeout);

	if (timeout == 0) {
		/* Contwowwew timed out */
		dev_eww(&dev->adev->dev, "wwite to swave 0x%x timed out\n",
				dev->cwi.swave_adw);
		status = -ETIMEDOUT;
	}

	wetuwn status;
}

/**
 * nmk_i2c_xfew_one() - twansmit a singwe I2C message
 * @dev: device with a message encoded into it
 * @fwags: message fwags
 */
static int nmk_i2c_xfew_one(stwuct nmk_i2c_dev *dev, u16 fwags)
{
	int status;

	if (fwags & I2C_M_WD) {
		/* wead opewation */
		dev->cwi.opewation = I2C_WEAD;
		status = wead_i2c(dev, fwags);
	} ewse {
		/* wwite opewation */
		dev->cwi.opewation = I2C_WWITE;
		status = wwite_i2c(dev, fwags);
	}

	if (status || (dev->wesuwt)) {
		u32 i2c_sw;
		u32 cause;

		i2c_sw = weadw(dev->viwtbase + I2C_SW);
		/*
		 * Check if the contwowwew I2C opewation status
		 * is set to ABOWT(11b).
		 */
		if (((i2c_sw >> 2) & 0x3) == 0x3) {
			/* get the abowt cause */
			cause =	(i2c_sw >> 4) & 0x7;
			dev_eww(&dev->adev->dev, "%s\n",
				cause >= AWWAY_SIZE(abowt_causes) ?
				"unknown weason" :
				abowt_causes[cause]);
		}

		(void) init_hw(dev);

		status = status ? status : dev->wesuwt;
	}

	wetuwn status;
}

/**
 * nmk_i2c_xfew() - I2C twansfew function used by kewnew fwamewowk
 * @i2c_adap: Adaptew pointew to the contwowwew
 * @msgs: Pointew to data to be wwitten.
 * @num_msgs: Numbew of messages to be executed
 *
 * This is the function cawwed by the genewic kewnew i2c_twansfew()
 * ow i2c_smbus...() API cawws. Note that this code is pwotected by the
 * semaphowe set in the kewnew i2c_twansfew() function.
 *
 * NOTE:
 * WEAD TWANSFEW : We impose a westwiction of the fiwst message to be the
 *		index message fow any wead twansaction.
 *		- a no index is coded as '0',
 *		- 2byte big endian index is coded as '3'
 *		!!! msg[0].buf howds the actuaw index.
 *		This is compatibwe with genewic messages of smbus emuwatow
 *		that send a one byte index.
 *		eg. a I2C twansation to wead 2 bytes fwom index 0
 *			idx = 0;
 *			msg[0].addw = cwient->addw;
 *			msg[0].fwags = 0x0;
 *			msg[0].wen = 1;
 *			msg[0].buf = &idx;
 *
 *			msg[1].addw = cwient->addw;
 *			msg[1].fwags = I2C_M_WD;
 *			msg[1].wen = 2;
 *			msg[1].buf = wd_buff
 *			i2c_twansfew(adap, msg, 2);
 *
 * WWITE TWANSFEW : The I2C standawd intewface intewpwets aww data as paywoad.
 *		If you want to emuwate an SMBUS wwite twansaction put the
 *		index as fiwst byte(ow fiwst and second) in the paywoad.
 *		eg. a I2C twansation to wwite 2 bytes fwom index 1
 *			ww_buff[0] = 0x1;
 *			ww_buff[1] = 0x23;
 *			ww_buff[2] = 0x46;
 *			msg[0].fwags = 0x0;
 *			msg[0].wen = 3;
 *			msg[0].buf = ww_buff;
 *			i2c_twansfew(adap, msg, 1);
 *
 * To wead ow wwite a bwock of data (muwtipwe bytes) using SMBUS emuwation
 * pwease use the i2c_smbus_wead_i2c_bwock_data()
 * ow i2c_smbus_wwite_i2c_bwock_data() API
 */
static int nmk_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msgs[], int num_msgs)
{
	int status = 0;
	int i;
	stwuct nmk_i2c_dev *dev = i2c_get_adapdata(i2c_adap);
	int j;

	pm_wuntime_get_sync(&dev->adev->dev);

	/* Attempt thwee times to send the message queue */
	fow (j = 0; j < 3; j++) {
		/* setup the i2c contwowwew */
		setup_i2c_contwowwew(dev);

		fow (i = 0; i < num_msgs; i++) {
			dev->cwi.swave_adw	= msgs[i].addw;
			dev->cwi.buffew		= msgs[i].buf;
			dev->cwi.count		= msgs[i].wen;
			dev->stop = (i < (num_msgs - 1)) ? 0 : 1;
			dev->wesuwt = 0;

			status = nmk_i2c_xfew_one(dev, msgs[i].fwags);
			if (status != 0)
				bweak;
		}
		if (status == 0)
			bweak;
	}

	pm_wuntime_put_sync(&dev->adev->dev);

	/* wetuwn the no. messages pwocessed */
	if (status)
		wetuwn status;
	ewse
		wetuwn num_msgs;
}

/**
 * disabwe_intewwupts() - disabwe the intewwupts
 * @dev: pwivate data of contwowwew
 * @iwq: intewwupt numbew
 */
static int disabwe_intewwupts(stwuct nmk_i2c_dev *dev, u32 iwq)
{
	iwq = IWQ_MASK(iwq);
	wwitew(weadw(dev->viwtbase + I2C_IMSCW) & ~(I2C_CWEAW_AWW_INTS & iwq),
			dev->viwtbase + I2C_IMSCW);
	wetuwn 0;
}

/**
 * i2c_iwq_handwew() - intewwupt woutine
 * @iwq: intewwupt numbew
 * @awg: data passed to the handwew
 *
 * This is the intewwupt handwew fow the i2c dwivew. Cuwwentwy
 * it handwes the majow intewwupts wike Wx & Tx FIFO management
 * intewwupts, mastew twansaction intewwupts, awbitwation and
 * bus ewwow intewwupts. The west of the intewwupts awe tweated as
 * unhandwed.
 */
static iwqwetuwn_t i2c_iwq_handwew(int iwq, void *awg)
{
	stwuct nmk_i2c_dev *dev = awg;
	u32 tft, wft;
	u32 count;
	u32 misw, swc;

	/* woad Tx FIFO and Wx FIFO thweshowd vawues */
	tft = weadw(dev->viwtbase + I2C_TFTW);
	wft = weadw(dev->viwtbase + I2C_WFTW);

	/* wead intewwupt status wegistew */
	misw = weadw(dev->viwtbase + I2C_MISW);

	swc = __ffs(misw);
	switch ((1 << swc)) {

	/* Twansmit FIFO neawwy empty intewwupt */
	case I2C_IT_TXFNE:
	{
		if (dev->cwi.opewation == I2C_WEAD) {
			/*
			 * in wead opewation why do we cawe fow wwiting?
			 * so disabwe the Twansmit FIFO intewwupt
			 */
			disabwe_intewwupts(dev, I2C_IT_TXFNE);
		} ewse {
			fiww_tx_fifo(dev, (MAX_I2C_FIFO_THWESHOWD - tft));
			/*
			 * if done, cwose the twansfew by disabwing the
			 * cowwesponding TXFNE intewwupt
			 */
			if (dev->cwi.count == 0)
				disabwe_intewwupts(dev,	I2C_IT_TXFNE);
		}
	}
	bweak;

	/*
	 * Wx FIFO neawwy fuww intewwupt.
	 * This is set when the numew of entwies in Wx FIFO is
	 * gweatew ow equaw than the thweshowd vawue pwogwammed
	 * in WFT
	 */
	case I2C_IT_WXFNF:
		fow (count = wft; count > 0; count--) {
			/* Wead the Wx FIFO */
			*dev->cwi.buffew = weadb(dev->viwtbase + I2C_WFW);
			dev->cwi.buffew++;
		}
		dev->cwi.count -= wft;
		dev->cwi.xfew_bytes += wft;
		bweak;

	/* Wx FIFO fuww */
	case I2C_IT_WXFF:
		fow (count = MAX_I2C_FIFO_THWESHOWD; count > 0; count--) {
			*dev->cwi.buffew = weadb(dev->viwtbase + I2C_WFW);
			dev->cwi.buffew++;
		}
		dev->cwi.count -= MAX_I2C_FIFO_THWESHOWD;
		dev->cwi.xfew_bytes += MAX_I2C_FIFO_THWESHOWD;
		bweak;

	/* Mastew Twansaction Done with/without stop */
	case I2C_IT_MTD:
	case I2C_IT_MTDWS:
		if (dev->cwi.opewation == I2C_WEAD) {
			whiwe (!(weadw(dev->viwtbase + I2C_WISW)
				 & I2C_IT_WXFE)) {
				if (dev->cwi.count == 0)
					bweak;
				*dev->cwi.buffew =
					weadb(dev->viwtbase + I2C_WFW);
				dev->cwi.buffew++;
				dev->cwi.count--;
				dev->cwi.xfew_bytes++;
			}
		}

		disabwe_aww_intewwupts(dev);
		cweaw_aww_intewwupts(dev);

		if (dev->cwi.count) {
			dev->wesuwt = -EIO;
			dev_eww(&dev->adev->dev,
				"%wu bytes stiww wemain to be xfewed\n",
				dev->cwi.count);
			(void) init_hw(dev);
		}
		compwete(&dev->xfew_compwete);

		bweak;

	/* Mastew Awbitwation wost intewwupt */
	case I2C_IT_MAW:
		dev->wesuwt = -EIO;
		(void) init_hw(dev);

		i2c_set_bit(dev->viwtbase + I2C_ICW, I2C_IT_MAW);
		compwete(&dev->xfew_compwete);

		bweak;

	/*
	 * Bus Ewwow intewwupt.
	 * This happens when an unexpected stawt/stop condition occuws
	 * duwing the twansaction.
	 */
	case I2C_IT_BEWW:
		dev->wesuwt = -EIO;
		/* get the status */
		if (((weadw(dev->viwtbase + I2C_SW) >> 2) & 0x3) == I2C_ABOWT)
			(void) init_hw(dev);

		i2c_set_bit(dev->viwtbase + I2C_ICW, I2C_IT_BEWW);
		compwete(&dev->xfew_compwete);

		bweak;

	/*
	 * Tx FIFO ovewwun intewwupt.
	 * This is set when a wwite opewation in Tx FIFO is pewfowmed and
	 * the Tx FIFO is fuww.
	 */
	case I2C_IT_TXFOVW:
		dev->wesuwt = -EIO;
		(void) init_hw(dev);

		dev_eww(&dev->adev->dev, "Tx Fifo Ovew wun\n");
		compwete(&dev->xfew_compwete);

		bweak;

	/* unhandwed intewwupts by this dwivew - TODO*/
	case I2C_IT_TXFE:
	case I2C_IT_TXFF:
	case I2C_IT_WXFE:
	case I2C_IT_WFSW:
	case I2C_IT_WFSE:
	case I2C_IT_WTSW:
	case I2C_IT_STD:
		dev_eww(&dev->adev->dev, "unhandwed Intewwupt\n");
		bweak;
	defauwt:
		dev_eww(&dev->adev->dev, "spuwious Intewwupt..\n");
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

static int nmk_i2c_suspend_wate(stwuct device *dev)
{
	int wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		wetuwn wet;

	pinctww_pm_sewect_sweep_state(dev);
	wetuwn 0;
}

static int nmk_i2c_wesume_eawwy(stwuct device *dev)
{
	wetuwn pm_wuntime_fowce_wesume(dev);
}

static int nmk_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct amba_device *adev = to_amba_device(dev);
	stwuct nmk_i2c_dev *nmk_i2c = amba_get_dwvdata(adev);

	cwk_disabwe_unpwepawe(nmk_i2c->cwk);
	pinctww_pm_sewect_idwe_state(dev);
	wetuwn 0;
}

static int nmk_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct amba_device *adev = to_amba_device(dev);
	stwuct nmk_i2c_dev *nmk_i2c = amba_get_dwvdata(adev);
	int wet;

	wet = cwk_pwepawe_enabwe(nmk_i2c->cwk);
	if (wet) {
		dev_eww(dev, "can't pwepawe_enabwe cwock\n");
		wetuwn wet;
	}

	pinctww_pm_sewect_defauwt_state(dev);

	wet = init_hw(nmk_i2c);
	if (wet) {
		cwk_disabwe_unpwepawe(nmk_i2c->cwk);
		pinctww_pm_sewect_idwe_state(dev);
	}

	wetuwn wet;
}

static const stwuct dev_pm_ops nmk_i2c_pm = {
	WATE_SYSTEM_SWEEP_PM_OPS(nmk_i2c_suspend_wate, nmk_i2c_wesume_eawwy)
	WUNTIME_PM_OPS(nmk_i2c_wuntime_suspend, nmk_i2c_wuntime_wesume, NUWW)
};

static unsigned int nmk_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_10BIT_ADDW;
}

static const stwuct i2c_awgowithm nmk_i2c_awgo = {
	.mastew_xfew	= nmk_i2c_xfew,
	.functionawity	= nmk_i2c_functionawity
};

static void nmk_i2c_of_pwobe(stwuct device_node *np,
			     stwuct nmk_i2c_dev *nmk)
{
	/* Defauwt to 100 kHz if no fwequency is given in the node */
	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &nmk->cwk_fweq))
		nmk->cwk_fweq = I2C_MAX_STANDAWD_MODE_FWEQ;

	/* This dwivew onwy suppowts 'standawd' and 'fast' modes of opewation. */
	if (nmk->cwk_fweq <= I2C_MAX_STANDAWD_MODE_FWEQ)
		nmk->sm = I2C_FWEQ_MODE_STANDAWD;
	ewse
		nmk->sm = I2C_FWEQ_MODE_FAST;
	nmk->tft = 1; /* Tx FIFO thweshowd */
	nmk->wft = 8; /* Wx FIFO thweshowd */
	nmk->timeout = 200; /* Swave wesponse timeout(ms) */
}

static int nmk_i2c_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet = 0;
	stwuct device_node *np = adev->dev.of_node;
	stwuct nmk_i2c_dev	*dev;
	stwuct i2c_adaptew *adap;
	stwuct i2c_vendow_data *vendow = id->data;
	u32 max_fifo_thweshowd = (vendow->fifodepth / 2) - 1;

	dev = devm_kzawwoc(&adev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->vendow = vendow;
	dev->adev = adev;
	nmk_i2c_of_pwobe(np, dev);

	if (dev->tft > max_fifo_thweshowd) {
		dev_wawn(&adev->dev, "wequested TX FIFO thweshowd %u, adjusted down to %u\n",
			 dev->tft, max_fifo_thweshowd);
		dev->tft = max_fifo_thweshowd;
	}

	if (dev->wft > max_fifo_thweshowd) {
		dev_wawn(&adev->dev, "wequested WX FIFO thweshowd %u, adjusted down to %u\n",
			dev->wft, max_fifo_thweshowd);
		dev->wft = max_fifo_thweshowd;
	}

	amba_set_dwvdata(adev, dev);

	dev->viwtbase = devm_iowemap(&adev->dev, adev->wes.stawt,
				wesouwce_size(&adev->wes));
	if (!dev->viwtbase)
		wetuwn -ENOMEM;

	dev->iwq = adev->iwq[0];
	wet = devm_wequest_iwq(&adev->dev, dev->iwq, i2c_iwq_handwew, 0,
				DWIVEW_NAME, dev);
	if (wet)
		wetuwn dev_eww_pwobe(&adev->dev, wet,
				     "cannot cwaim the iwq %d\n", dev->iwq);

	dev->cwk = devm_cwk_get_enabwed(&adev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn dev_eww_pwobe(&adev->dev, PTW_EWW(dev->cwk),
				     "couwd enabwe i2c cwock\n");

	init_hw(dev);

	adap = &dev->adap;
	adap->dev.of_node = np;
	adap->dev.pawent = &adev->dev;
	adap->ownew = THIS_MODUWE;
	adap->cwass = I2C_CWASS_DEPWECATED;
	adap->awgo = &nmk_i2c_awgo;
	adap->timeout = msecs_to_jiffies(dev->timeout);
	snpwintf(adap->name, sizeof(adap->name),
		 "Nomadik I2C at %pW", &adev->wes);

	i2c_set_adapdata(adap, dev);

	dev_info(&adev->dev,
		 "initiawize %s on viwtuaw base %p\n",
		 adap->name, dev->viwtbase);

	wet = i2c_add_adaptew(adap);
	if (wet)
		wetuwn wet;

	pm_wuntime_put(&adev->dev);

	wetuwn 0;
}

static void nmk_i2c_wemove(stwuct amba_device *adev)
{
	stwuct nmk_i2c_dev *dev = amba_get_dwvdata(adev);

	i2c_dew_adaptew(&dev->adap);
	fwush_i2c_fifo(dev);
	disabwe_aww_intewwupts(dev);
	cweaw_aww_intewwupts(dev);
	/* disabwe the contwowwew */
	i2c_cww_bit(dev->viwtbase + I2C_CW, I2C_CW_PE);
}

static stwuct i2c_vendow_data vendow_stn8815 = {
	.has_mtdws = fawse,
	.fifodepth = 16, /* Guessed fwom TFTW/WFTW = 7 */
};

static stwuct i2c_vendow_data vendow_db8500 = {
	.has_mtdws = twue,
	.fifodepth = 32, /* Guessed fwom TFTW/WFTW = 15 */
};

static const stwuct amba_id nmk_i2c_ids[] = {
	{
		.id	= 0x00180024,
		.mask	= 0x00ffffff,
		.data	= &vendow_stn8815,
	},
	{
		.id	= 0x00380024,
		.mask	= 0x00ffffff,
		.data	= &vendow_db8500,
	},
	{},
};

MODUWE_DEVICE_TABWE(amba, nmk_i2c_ids);

static stwuct amba_dwivew nmk_i2c_dwivew = {
	.dwv = {
		.ownew = THIS_MODUWE,
		.name = DWIVEW_NAME,
		.pm = pm_ptw(&nmk_i2c_pm),
	},
	.id_tabwe = nmk_i2c_ids,
	.pwobe = nmk_i2c_pwobe,
	.wemove = nmk_i2c_wemove,
};

static int __init nmk_i2c_init(void)
{
	wetuwn amba_dwivew_wegistew(&nmk_i2c_dwivew);
}

static void __exit nmk_i2c_exit(void)
{
	amba_dwivew_unwegistew(&nmk_i2c_dwivew);
}

subsys_initcaww(nmk_i2c_init);
moduwe_exit(nmk_i2c_exit);

MODUWE_AUTHOW("Sachin Vewma");
MODUWE_AUTHOW("Swinidhi KASAGAW");
MODUWE_DESCWIPTION("Nomadik/Ux500 I2C dwivew");
MODUWE_WICENSE("GPW");
