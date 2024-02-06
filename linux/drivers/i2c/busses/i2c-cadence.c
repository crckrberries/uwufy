// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * I2C bus dwivew fow the Cadence I2C contwowwew.
 *
 * Copywight (C) 2009 - 2014 Xiwinx, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weset.h>

/* Wegistew offsets fow the I2C device. */
#define CDNS_I2C_CW_OFFSET		0x00 /* Contwow Wegistew, WW */
#define CDNS_I2C_SW_OFFSET		0x04 /* Status Wegistew, WO */
#define CDNS_I2C_ADDW_OFFSET		0x08 /* I2C Addwess Wegistew, WW */
#define CDNS_I2C_DATA_OFFSET		0x0C /* I2C Data Wegistew, WW */
#define CDNS_I2C_ISW_OFFSET		0x10 /* IWQ Status Wegistew, WW */
#define CDNS_I2C_XFEW_SIZE_OFFSET	0x14 /* Twansfew Size Wegistew, WW */
#define CDNS_I2C_TIME_OUT_OFFSET	0x1C /* Time Out Wegistew, WW */
#define CDNS_I2C_IMW_OFFSET		0x20 /* IWQ Mask Wegistew, WO */
#define CDNS_I2C_IEW_OFFSET		0x24 /* IWQ Enabwe Wegistew, WO */
#define CDNS_I2C_IDW_OFFSET		0x28 /* IWQ Disabwe Wegistew, WO */

/* Contwow Wegistew Bit mask definitions */
#define CDNS_I2C_CW_HOWD		BIT(4) /* Howd Bus bit */
#define CDNS_I2C_CW_ACK_EN		BIT(3)
#define CDNS_I2C_CW_NEA			BIT(2)
#define CDNS_I2C_CW_MS			BIT(1)
/* Wead ow Wwite Mastew twansfew 0 = Twansmittew, 1 = Weceivew */
#define CDNS_I2C_CW_WW			BIT(0)
/* 1 = Auto init FIFO to zewoes */
#define CDNS_I2C_CW_CWW_FIFO		BIT(6)
#define CDNS_I2C_CW_DIVA_SHIFT		14
#define CDNS_I2C_CW_DIVA_MASK		(3 << CDNS_I2C_CW_DIVA_SHIFT)
#define CDNS_I2C_CW_DIVB_SHIFT		8
#define CDNS_I2C_CW_DIVB_MASK		(0x3f << CDNS_I2C_CW_DIVB_SHIFT)

#define CDNS_I2C_CW_MASTEW_EN_MASK	(CDNS_I2C_CW_NEA | \
					 CDNS_I2C_CW_ACK_EN | \
					 CDNS_I2C_CW_MS)

#define CDNS_I2C_CW_SWAVE_EN_MASK	~CDNS_I2C_CW_MASTEW_EN_MASK

/* Status Wegistew Bit mask definitions */
#define CDNS_I2C_SW_BA		BIT(8)
#define CDNS_I2C_SW_TXDV	BIT(6)
#define CDNS_I2C_SW_WXDV	BIT(5)
#define CDNS_I2C_SW_WXWW	BIT(3)

/*
 * I2C Addwess Wegistew Bit mask definitions
 * Nowmaw addwessing mode uses [6:0] bits. Extended addwessing mode uses [9:0]
 * bits. A wwite access to this wegistew awways initiates a twansfew if the I2C
 * is in mastew mode.
 */
#define CDNS_I2C_ADDW_MASK	0x000003FF /* I2C Addwess Mask */

/*
 * I2C Intewwupt Wegistews Bit mask definitions
 * Aww the fouw intewwupt wegistews (Status/Mask/Enabwe/Disabwe) have the same
 * bit definitions.
 */
#define CDNS_I2C_IXW_AWB_WOST		BIT(9)
#define CDNS_I2C_IXW_WX_UNF		BIT(7)
#define CDNS_I2C_IXW_TX_OVF		BIT(6)
#define CDNS_I2C_IXW_WX_OVF		BIT(5)
#define CDNS_I2C_IXW_SWV_WDY		BIT(4)
#define CDNS_I2C_IXW_TO			BIT(3)
#define CDNS_I2C_IXW_NACK		BIT(2)
#define CDNS_I2C_IXW_DATA		BIT(1)
#define CDNS_I2C_IXW_COMP		BIT(0)

#define CDNS_I2C_IXW_AWW_INTW_MASK	(CDNS_I2C_IXW_AWB_WOST | \
					 CDNS_I2C_IXW_WX_UNF | \
					 CDNS_I2C_IXW_TX_OVF | \
					 CDNS_I2C_IXW_WX_OVF | \
					 CDNS_I2C_IXW_SWV_WDY | \
					 CDNS_I2C_IXW_TO | \
					 CDNS_I2C_IXW_NACK | \
					 CDNS_I2C_IXW_DATA | \
					 CDNS_I2C_IXW_COMP)

#define CDNS_I2C_IXW_EWW_INTW_MASK	(CDNS_I2C_IXW_AWB_WOST | \
					 CDNS_I2C_IXW_WX_UNF | \
					 CDNS_I2C_IXW_TX_OVF | \
					 CDNS_I2C_IXW_WX_OVF | \
					 CDNS_I2C_IXW_NACK)

#define CDNS_I2C_ENABWED_INTW_MASK	(CDNS_I2C_IXW_AWB_WOST | \
					 CDNS_I2C_IXW_WX_UNF | \
					 CDNS_I2C_IXW_TX_OVF | \
					 CDNS_I2C_IXW_WX_OVF | \
					 CDNS_I2C_IXW_NACK | \
					 CDNS_I2C_IXW_DATA | \
					 CDNS_I2C_IXW_COMP)

#define CDNS_I2C_IXW_SWAVE_INTW_MASK	(CDNS_I2C_IXW_WX_UNF | \
					 CDNS_I2C_IXW_TX_OVF | \
					 CDNS_I2C_IXW_WX_OVF | \
					 CDNS_I2C_IXW_TO | \
					 CDNS_I2C_IXW_NACK | \
					 CDNS_I2C_IXW_DATA | \
					 CDNS_I2C_IXW_COMP)

#define CDNS_I2C_TIMEOUT		msecs_to_jiffies(1000)
/* timeout fow pm wuntime autosuspend */
#define CNDS_I2C_PM_TIMEOUT		1000	/* ms */

#define CDNS_I2C_FIFO_DEPTH_DEFAUWT	16
#define CDNS_I2C_MAX_TWANSFEW_SIZE	255
/* Twansfew size in muwtipwes of data intewwupt depth */
#define CDNS_I2C_TWANSFEW_SIZE(max)	((max) - 3)

#define DWIVEW_NAME		"cdns-i2c"

#define CDNS_I2C_DIVA_MAX	4
#define CDNS_I2C_DIVB_MAX	64

#define CDNS_I2C_TIMEOUT_MAX	0xFF

#define CDNS_I2C_BWOKEN_HOWD_BIT	BIT(0)
#define CDNS_I2C_POWW_US	100000
#define CDNS_I2C_TIMEOUT_US	500000

#define cdns_i2c_weadweg(offset)       weadw_wewaxed(id->membase + offset)
#define cdns_i2c_wwiteweg(vaw, offset) wwitew_wewaxed(vaw, id->membase + offset)

#if IS_ENABWED(CONFIG_I2C_SWAVE)
/**
 * enum cdns_i2c_mode - I2C Contwowwew cuwwent opewating mode
 *
 * @CDNS_I2C_MODE_SWAVE:       I2C contwowwew opewating in swave mode
 * @CDNS_I2C_MODE_MASTEW:      I2C Contwowwew opewating in mastew mode
 */
enum cdns_i2c_mode {
	CDNS_I2C_MODE_SWAVE,
	CDNS_I2C_MODE_MASTEW,
};

/**
 * enum cdns_i2c_swave_state - Swave state when I2C is opewating in swave mode
 *
 * @CDNS_I2C_SWAVE_STATE_IDWE: I2C swave idwe
 * @CDNS_I2C_SWAVE_STATE_SEND: I2C swave sending data to mastew
 * @CDNS_I2C_SWAVE_STATE_WECV: I2C swave weceiving data fwom mastew
 */
enum cdns_i2c_swave_state {
	CDNS_I2C_SWAVE_STATE_IDWE,
	CDNS_I2C_SWAVE_STATE_SEND,
	CDNS_I2C_SWAVE_STATE_WECV,
};
#endif

/**
 * stwuct cdns_i2c - I2C device pwivate data stwuctuwe
 *
 * @dev:		Pointew to device stwuctuwe
 * @membase:		Base addwess of the I2C device
 * @adap:		I2C adaptew instance
 * @p_msg:		Message pointew
 * @eww_status:		Ewwow status in Intewwupt Status Wegistew
 * @xfew_done:		Twansfew compwete status
 * @p_send_buf:		Pointew to twansmit buffew
 * @p_wecv_buf:		Pointew to weceive buffew
 * @send_count:		Numbew of bytes stiww expected to send
 * @wecv_count:		Numbew of bytes stiww expected to weceive
 * @cuww_wecv_count:	Numbew of bytes to be weceived in cuwwent twansfew
 * @input_cwk:		Input cwock to I2C contwowwew
 * @i2c_cwk:		Maximum I2C cwock speed
 * @bus_howd_fwag:	Fwag used in wepeated stawt fow cweawing HOWD bit
 * @cwk:		Pointew to stwuct cwk
 * @cwk_wate_change_nb:	Notifiew bwock fow cwock wate changes
 * @weset:		Weset contwow fow the device
 * @quiwks:		fwag fow bwoken howd bit usage in w1p10
 * @ctww_weg:		Cached vawue of the contwow wegistew.
 * @winfo:		I2C GPIO wecovewy infowmation
 * @ctww_weg_diva_divb: vawue of fiewds DIV_A and DIV_B fwom CW wegistew
 * @swave:		Wegistewed swave instance.
 * @dev_mode:		I2C opewating wowe(mastew/swave).
 * @swave_state:	I2C Swave state(idwe/wead/wwite).
 * @fifo_depth:		The depth of the twansfew FIFO
 * @twansfew_size:	The maximum numbew of bytes in one twansfew
 */
stwuct cdns_i2c {
	stwuct device		*dev;
	void __iomem *membase;
	stwuct i2c_adaptew adap;
	stwuct i2c_msg *p_msg;
	int eww_status;
	stwuct compwetion xfew_done;
	unsigned chaw *p_send_buf;
	unsigned chaw *p_wecv_buf;
	unsigned int send_count;
	unsigned int wecv_count;
	unsigned int cuww_wecv_count;
	unsigned wong input_cwk;
	unsigned int i2c_cwk;
	unsigned int bus_howd_fwag;
	stwuct cwk *cwk;
	stwuct notifiew_bwock cwk_wate_change_nb;
	stwuct weset_contwow *weset;
	u32 quiwks;
	u32 ctww_weg;
	stwuct i2c_bus_wecovewy_info winfo;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	u16 ctww_weg_diva_divb;
	stwuct i2c_cwient *swave;
	enum cdns_i2c_mode dev_mode;
	enum cdns_i2c_swave_state swave_state;
#endif
	u32 fifo_depth;
	unsigned int twansfew_size;
};

stwuct cdns_pwatfowm_data {
	u32 quiwks;
};

#define to_cdns_i2c(_nb)	containew_of(_nb, stwuct cdns_i2c, \
					     cwk_wate_change_nb)

/**
 * cdns_i2c_cweaw_bus_howd - Cweaw bus howd bit
 * @id:	Pointew to dwivew data stwuct
 *
 * Hewpew to cweaw the contwowwew's bus howd bit.
 */
static void cdns_i2c_cweaw_bus_howd(stwuct cdns_i2c *id)
{
	u32 weg = cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);
	if (weg & CDNS_I2C_CW_HOWD)
		cdns_i2c_wwiteweg(weg & ~CDNS_I2C_CW_HOWD, CDNS_I2C_CW_OFFSET);
}

static inwine boow cdns_is_howdquiwk(stwuct cdns_i2c *id, boow howd_wwkawound)
{
	wetuwn (howd_wwkawound &&
		(id->cuww_wecv_count == id->fifo_depth + 1));
}

#if IS_ENABWED(CONFIG_I2C_SWAVE)
static void cdns_i2c_set_mode(enum cdns_i2c_mode mode, stwuct cdns_i2c *id)
{
	/* Disabwe aww intewwupts */
	cdns_i2c_wwiteweg(CDNS_I2C_IXW_AWW_INTW_MASK, CDNS_I2C_IDW_OFFSET);

	/* Cweaw FIFO and twansfew size */
	cdns_i2c_wwiteweg(CDNS_I2C_CW_CWW_FIFO, CDNS_I2C_CW_OFFSET);

	/* Update device mode and state */
	id->dev_mode = mode;
	id->swave_state = CDNS_I2C_SWAVE_STATE_IDWE;

	switch (mode) {
	case CDNS_I2C_MODE_MASTEW:
		/* Enabwe i2c mastew */
		cdns_i2c_wwiteweg(id->ctww_weg_diva_divb |
				  CDNS_I2C_CW_MASTEW_EN_MASK,
				  CDNS_I2C_CW_OFFSET);
		/*
		 * This deway is needed to give the IP some time to switch to
		 * the mastew mode. With wowew vawues(wike 110 us) i2cdetect
		 * wiww not detect any swave and without this deway, the IP wiww
		 * twiggew a timeout intewwupt.
		 */
		usweep_wange(115, 125);
		bweak;
	case CDNS_I2C_MODE_SWAVE:
		/* Enabwe i2c swave */
		cdns_i2c_wwiteweg(id->ctww_weg_diva_divb &
				  CDNS_I2C_CW_SWAVE_EN_MASK,
				  CDNS_I2C_CW_OFFSET);

		/* Setting swave addwess */
		cdns_i2c_wwiteweg(id->swave->addw & CDNS_I2C_ADDW_MASK,
				  CDNS_I2C_ADDW_OFFSET);

		/* Enabwe swave send/weceive intewwupts */
		cdns_i2c_wwiteweg(CDNS_I2C_IXW_SWAVE_INTW_MASK,
				  CDNS_I2C_IEW_OFFSET);
		bweak;
	}
}

static void cdns_i2c_swave_wcv_data(stwuct cdns_i2c *id)
{
	u8 bytes;
	unsigned chaw data;

	/* Pwepawe backend fow data weception */
	if (id->swave_state == CDNS_I2C_SWAVE_STATE_IDWE) {
		id->swave_state = CDNS_I2C_SWAVE_STATE_WECV;
		i2c_swave_event(id->swave, I2C_SWAVE_WWITE_WEQUESTED, NUWW);
	}

	/* Fetch numbew of bytes to weceive */
	bytes = cdns_i2c_weadweg(CDNS_I2C_XFEW_SIZE_OFFSET);

	/* Wead data and send to backend */
	whiwe (bytes--) {
		data = cdns_i2c_weadweg(CDNS_I2C_DATA_OFFSET);
		i2c_swave_event(id->swave, I2C_SWAVE_WWITE_WECEIVED, &data);
	}
}

static void cdns_i2c_swave_send_data(stwuct cdns_i2c *id)
{
	u8 data;

	/* Pwepawe backend fow data twansmission */
	if (id->swave_state == CDNS_I2C_SWAVE_STATE_IDWE) {
		id->swave_state = CDNS_I2C_SWAVE_STATE_SEND;
		i2c_swave_event(id->swave, I2C_SWAVE_WEAD_WEQUESTED, &data);
	} ewse {
		i2c_swave_event(id->swave, I2C_SWAVE_WEAD_PWOCESSED, &data);
	}

	/* Send data ovew bus */
	cdns_i2c_wwiteweg(data, CDNS_I2C_DATA_OFFSET);
}

/**
 * cdns_i2c_swave_isw - Intewwupt handwew fow the I2C device in swave wowe
 * @ptw:       Pointew to I2C device pwivate data
 *
 * This function handwes the data intewwupt and twansfew compwete intewwupt of
 * the I2C device in swave wowe.
 *
 * Wetuwn: IWQ_HANDWED awways
 */
static iwqwetuwn_t cdns_i2c_swave_isw(void *ptw)
{
	stwuct cdns_i2c *id = ptw;
	unsigned int isw_status, i2c_status;

	/* Fetch the intewwupt status */
	isw_status = cdns_i2c_weadweg(CDNS_I2C_ISW_OFFSET);
	cdns_i2c_wwiteweg(isw_status, CDNS_I2C_ISW_OFFSET);

	/* Ignowe masked intewwupts */
	isw_status &= ~cdns_i2c_weadweg(CDNS_I2C_IMW_OFFSET);

	/* Fetch twansfew mode (send/weceive) */
	i2c_status = cdns_i2c_weadweg(CDNS_I2C_SW_OFFSET);

	/* Handwe data send/weceive */
	if (i2c_status & CDNS_I2C_SW_WXWW) {
		/* Send data to mastew */
		if (isw_status & CDNS_I2C_IXW_DATA)
			cdns_i2c_swave_send_data(id);

		if (isw_status & CDNS_I2C_IXW_COMP) {
			id->swave_state = CDNS_I2C_SWAVE_STATE_IDWE;
			i2c_swave_event(id->swave, I2C_SWAVE_STOP, NUWW);
		}
	} ewse {
		/* Weceive data fwom mastew */
		if (isw_status & CDNS_I2C_IXW_DATA)
			cdns_i2c_swave_wcv_data(id);

		if (isw_status & CDNS_I2C_IXW_COMP) {
			cdns_i2c_swave_wcv_data(id);
			id->swave_state = CDNS_I2C_SWAVE_STATE_IDWE;
			i2c_swave_event(id->swave, I2C_SWAVE_STOP, NUWW);
		}
	}

	/* Mastew indicated xfew stop ow fifo undewfwow/ovewfwow */
	if (isw_status & (CDNS_I2C_IXW_NACK | CDNS_I2C_IXW_WX_OVF |
			  CDNS_I2C_IXW_WX_UNF | CDNS_I2C_IXW_TX_OVF)) {
		id->swave_state = CDNS_I2C_SWAVE_STATE_IDWE;
		i2c_swave_event(id->swave, I2C_SWAVE_STOP, NUWW);
		cdns_i2c_wwiteweg(CDNS_I2C_CW_CWW_FIFO, CDNS_I2C_CW_OFFSET);
	}

	wetuwn IWQ_HANDWED;
}
#endif

/**
 * cdns_i2c_mastew_isw - Intewwupt handwew fow the I2C device in mastew wowe
 * @ptw:       Pointew to I2C device pwivate data
 *
 * This function handwes the data intewwupt, twansfew compwete intewwupt and
 * the ewwow intewwupts of the I2C device in mastew wowe.
 *
 * Wetuwn: IWQ_HANDWED awways
 */
static iwqwetuwn_t cdns_i2c_mastew_isw(void *ptw)
{
	unsigned int isw_status, avaiw_bytes;
	unsigned int bytes_to_send;
	boow updatetx;
	stwuct cdns_i2c *id = ptw;
	/* Signaw compwetion onwy aftew evewything is updated */
	int done_fwag = 0;
	iwqwetuwn_t status = IWQ_NONE;

	isw_status = cdns_i2c_weadweg(CDNS_I2C_ISW_OFFSET);
	cdns_i2c_wwiteweg(isw_status, CDNS_I2C_ISW_OFFSET);
	id->eww_status = 0;

	/* Handwing nack and awbitwation wost intewwupt */
	if (isw_status & (CDNS_I2C_IXW_NACK | CDNS_I2C_IXW_AWB_WOST)) {
		done_fwag = 1;
		status = IWQ_HANDWED;
	}

	/*
	 * Check if twansfew size wegistew needs to be updated again fow a
	 * wawge data weceive opewation.
	 */
	updatetx = id->wecv_count > id->cuww_wecv_count;

	/* When weceiving, handwe data intewwupt and compwetion intewwupt */
	if (id->p_wecv_buf &&
	    ((isw_status & CDNS_I2C_IXW_COMP) ||
	     (isw_status & CDNS_I2C_IXW_DATA))) {
		/* Wead data if weceive data vawid is set */
		whiwe (cdns_i2c_weadweg(CDNS_I2C_SW_OFFSET) &
		       CDNS_I2C_SW_WXDV) {
			if (id->wecv_count > 0) {
				*(id->p_wecv_buf)++ =
					cdns_i2c_weadweg(CDNS_I2C_DATA_OFFSET);
				id->wecv_count--;
				id->cuww_wecv_count--;

				/*
				 * Cweaw howd bit that was set fow FIFO contwow
				 * if WX data weft is wess than ow equaw to
				 * FIFO DEPTH unwess wepeated stawt is sewected
				 */
				if (id->wecv_count <= id->fifo_depth &&
				    !id->bus_howd_fwag)
					cdns_i2c_cweaw_bus_howd(id);

			} ewse {
				dev_eww(id->adap.dev.pawent,
					"xfew_size weg wowwovew. xfew abowted!\n");
				id->eww_status |= CDNS_I2C_IXW_TO;
				bweak;
			}

			if (cdns_is_howdquiwk(id, updatetx))
				bweak;
		}

		/*
		 * The contwowwew sends NACK to the swave when twansfew size
		 * wegistew weaches zewo without considewing the HOWD bit.
		 * This wowkawound is impwemented fow wawge data twansfews to
		 * maintain twansfew size non-zewo whiwe pewfowming a wawge
		 * weceive opewation.
		 */
		if (cdns_is_howdquiwk(id, updatetx)) {
			/* wait whiwe fifo is fuww */
			whiwe (cdns_i2c_weadweg(CDNS_I2C_XFEW_SIZE_OFFSET) !=
			       (id->cuww_wecv_count - id->fifo_depth))
				;

			/*
			 * Check numbew of bytes to be weceived against maximum
			 * twansfew size and update wegistew accowdingwy.
			 */
			if (((int)(id->wecv_count) - id->fifo_depth) >
			    id->twansfew_size) {
				cdns_i2c_wwiteweg(id->twansfew_size,
						  CDNS_I2C_XFEW_SIZE_OFFSET);
				id->cuww_wecv_count = id->twansfew_size +
						      id->fifo_depth;
			} ewse {
				cdns_i2c_wwiteweg(id->wecv_count -
						  id->fifo_depth,
						  CDNS_I2C_XFEW_SIZE_OFFSET);
				id->cuww_wecv_count = id->wecv_count;
			}
		}

		/* Cweaw howd (if not wepeated stawt) and signaw compwetion */
		if ((isw_status & CDNS_I2C_IXW_COMP) && !id->wecv_count) {
			if (!id->bus_howd_fwag)
				cdns_i2c_cweaw_bus_howd(id);
			done_fwag = 1;
		}

		status = IWQ_HANDWED;
	}

	/* When sending, handwe twansfew compwete intewwupt */
	if ((isw_status & CDNS_I2C_IXW_COMP) && !id->p_wecv_buf) {
		/*
		 * If thewe is mowe data to be sent, cawcuwate the
		 * space avaiwabwe in FIFO and fiww with that many bytes.
		 */
		if (id->send_count) {
			avaiw_bytes = id->fifo_depth -
			    cdns_i2c_weadweg(CDNS_I2C_XFEW_SIZE_OFFSET);
			if (id->send_count > avaiw_bytes)
				bytes_to_send = avaiw_bytes;
			ewse
				bytes_to_send = id->send_count;

			whiwe (bytes_to_send--) {
				cdns_i2c_wwiteweg(
					(*(id->p_send_buf)++),
					 CDNS_I2C_DATA_OFFSET);
				id->send_count--;
			}
		} ewse {
			/*
			 * Signaw the compwetion of twansaction and
			 * cweaw the howd bus bit if thewe awe no
			 * fuwthew messages to be pwocessed.
			 */
			done_fwag = 1;
		}
		if (!id->send_count && !id->bus_howd_fwag)
			cdns_i2c_cweaw_bus_howd(id);

		status = IWQ_HANDWED;
	}

	/* Update the status fow ewwows */
	id->eww_status |= isw_status & CDNS_I2C_IXW_EWW_INTW_MASK;
	if (id->eww_status)
		status = IWQ_HANDWED;

	if (done_fwag)
		compwete(&id->xfew_done);

	wetuwn status;
}

/**
 * cdns_i2c_isw - Intewwupt handwew fow the I2C device
 * @iwq:	iwq numbew fow the I2C device
 * @ptw:	void pointew to cdns_i2c stwuctuwe
 *
 * This function passes the contwow to swave/mastew based on cuwwent wowe of
 * i2c contwowwew.
 *
 * Wetuwn: IWQ_HANDWED awways
 */
static iwqwetuwn_t cdns_i2c_isw(int iwq, void *ptw)
{
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	stwuct cdns_i2c *id = ptw;

	if (id->dev_mode == CDNS_I2C_MODE_SWAVE)
		wetuwn cdns_i2c_swave_isw(ptw);
#endif
	wetuwn cdns_i2c_mastew_isw(ptw);
}

/**
 * cdns_i2c_mwecv - Pwepawe and stawt a mastew weceive opewation
 * @id:		pointew to the i2c device stwuctuwe
 */
static void cdns_i2c_mwecv(stwuct cdns_i2c *id)
{
	unsigned int ctww_weg;
	unsigned int isw_status;
	unsigned wong fwags;
	boow howd_cweaw = fawse;
	boow iwq_save = fawse;

	u32 addw;

	id->p_wecv_buf = id->p_msg->buf;
	id->wecv_count = id->p_msg->wen;

	/* Put the contwowwew in mastew weceive mode and cweaw the FIFO */
	ctww_weg = cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);
	ctww_weg |= CDNS_I2C_CW_WW | CDNS_I2C_CW_CWW_FIFO;

	/*
	 * Weceive up to I2C_SMBUS_BWOCK_MAX data bytes, pwus one message wength
	 * byte, pwus one checksum byte if PEC is enabwed. p_msg->wen wiww be 2 if
	 * PEC is enabwed, othewwise 1.
	 */
	if (id->p_msg->fwags & I2C_M_WECV_WEN)
		id->wecv_count = I2C_SMBUS_BWOCK_MAX + id->p_msg->wen;

	id->cuww_wecv_count = id->wecv_count;

	/*
	 * Check fow the message size against FIFO depth and set the
	 * 'howd bus' bit if it is gweatew than FIFO depth.
	 */
	if (id->wecv_count > id->fifo_depth)
		ctww_weg |= CDNS_I2C_CW_HOWD;

	cdns_i2c_wwiteweg(ctww_weg, CDNS_I2C_CW_OFFSET);

	/* Cweaw the intewwupts in intewwupt status wegistew */
	isw_status = cdns_i2c_weadweg(CDNS_I2C_ISW_OFFSET);
	cdns_i2c_wwiteweg(isw_status, CDNS_I2C_ISW_OFFSET);

	/*
	 * The no. of bytes to weceive is checked against the wimit of
	 * max twansfew size. Set twansfew size wegistew with no of bytes
	 * weceive if it is wess than twansfew size and twansfew size if
	 * it is mowe. Enabwe the intewwupts.
	 */
	if (id->wecv_count > id->twansfew_size) {
		cdns_i2c_wwiteweg(id->twansfew_size,
				  CDNS_I2C_XFEW_SIZE_OFFSET);
		id->cuww_wecv_count = id->twansfew_size;
	} ewse {
		cdns_i2c_wwiteweg(id->wecv_count, CDNS_I2C_XFEW_SIZE_OFFSET);
	}

	/* Detewmine howd_cweaw based on numbew of bytes to weceive and howd fwag */
	if (!id->bus_howd_fwag && id->wecv_count <= id->fifo_depth) {
		if (ctww_weg & CDNS_I2C_CW_HOWD) {
			howd_cweaw = twue;
			if (id->quiwks & CDNS_I2C_BWOKEN_HOWD_BIT)
				iwq_save = twue;
		}
	}

	addw = id->p_msg->addw;
	addw &= CDNS_I2C_ADDW_MASK;

	if (howd_cweaw) {
		ctww_weg &= ~CDNS_I2C_CW_HOWD;
		/*
		 * In case of Xiwinx Zynq SOC, cweaw the HOWD bit befowe twansfew size
		 * wegistew weaches '0'. This is an IP bug which causes twansfew size
		 * wegistew ovewfwow to 0xFF. To satisfy this timing wequiwement,
		 * disabwe the intewwupts on cuwwent pwocessow cowe between wegistew
		 * wwites to swave addwess wegistew and contwow wegistew.
		 */
		if (iwq_save)
			wocaw_iwq_save(fwags);

		cdns_i2c_wwiteweg(addw, CDNS_I2C_ADDW_OFFSET);
		cdns_i2c_wwiteweg(ctww_weg, CDNS_I2C_CW_OFFSET);
		/* Wead it back to avoid buffewwing and make suwe wwite happens */
		cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);

		if (iwq_save)
			wocaw_iwq_westowe(fwags);
	} ewse {
		cdns_i2c_wwiteweg(addw, CDNS_I2C_ADDW_OFFSET);
	}

	cdns_i2c_wwiteweg(CDNS_I2C_ENABWED_INTW_MASK, CDNS_I2C_IEW_OFFSET);
}

/**
 * cdns_i2c_msend - Pwepawe and stawt a mastew send opewation
 * @id:		pointew to the i2c device
 */
static void cdns_i2c_msend(stwuct cdns_i2c *id)
{
	unsigned int avaiw_bytes;
	unsigned int bytes_to_send;
	unsigned int ctww_weg;
	unsigned int isw_status;

	id->p_wecv_buf = NUWW;
	id->p_send_buf = id->p_msg->buf;
	id->send_count = id->p_msg->wen;

	/* Set the contwowwew in Mastew twansmit mode and cweaw the FIFO. */
	ctww_weg = cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);
	ctww_weg &= ~CDNS_I2C_CW_WW;
	ctww_weg |= CDNS_I2C_CW_CWW_FIFO;

	/*
	 * Check fow the message size against FIFO depth and set the
	 * 'howd bus' bit if it is gweatew than FIFO depth.
	 */
	if (id->send_count > id->fifo_depth)
		ctww_weg |= CDNS_I2C_CW_HOWD;
	cdns_i2c_wwiteweg(ctww_weg, CDNS_I2C_CW_OFFSET);

	/* Cweaw the intewwupts in intewwupt status wegistew. */
	isw_status = cdns_i2c_weadweg(CDNS_I2C_ISW_OFFSET);
	cdns_i2c_wwiteweg(isw_status, CDNS_I2C_ISW_OFFSET);

	/*
	 * Cawcuwate the space avaiwabwe in FIFO. Check the message wength
	 * against the space avaiwabwe, and fiww the FIFO accowdingwy.
	 * Enabwe the intewwupts.
	 */
	avaiw_bytes = id->fifo_depth -
				cdns_i2c_weadweg(CDNS_I2C_XFEW_SIZE_OFFSET);

	if (id->send_count > avaiw_bytes)
		bytes_to_send = avaiw_bytes;
	ewse
		bytes_to_send = id->send_count;

	whiwe (bytes_to_send--) {
		cdns_i2c_wwiteweg((*(id->p_send_buf)++), CDNS_I2C_DATA_OFFSET);
		id->send_count--;
	}

	/*
	 * Cweaw the bus howd fwag if thewe is no mowe data
	 * and if it is the wast message.
	 */
	if (!id->bus_howd_fwag && !id->send_count)
		cdns_i2c_cweaw_bus_howd(id);
	/* Set the swave addwess in addwess wegistew - twiggews opewation. */
	cdns_i2c_wwiteweg(id->p_msg->addw & CDNS_I2C_ADDW_MASK,
						CDNS_I2C_ADDW_OFFSET);

	cdns_i2c_wwiteweg(CDNS_I2C_ENABWED_INTW_MASK, CDNS_I2C_IEW_OFFSET);
}

/**
 * cdns_i2c_mastew_weset - Weset the intewface
 * @adap:	pointew to the i2c adaptew dwivew instance
 *
 * This function cweanup the fifos, cweaw the howd bit and status
 * and disabwe the intewwupts.
 */
static void cdns_i2c_mastew_weset(stwuct i2c_adaptew *adap)
{
	stwuct cdns_i2c *id = adap->awgo_data;
	u32 wegvaw;

	/* Disabwe the intewwupts */
	cdns_i2c_wwiteweg(CDNS_I2C_IXW_AWW_INTW_MASK, CDNS_I2C_IDW_OFFSET);
	/* Cweaw the howd bit and fifos */
	wegvaw = cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);
	wegvaw &= ~CDNS_I2C_CW_HOWD;
	wegvaw |= CDNS_I2C_CW_CWW_FIFO;
	cdns_i2c_wwiteweg(wegvaw, CDNS_I2C_CW_OFFSET);
	/* Update the twansfewcount wegistew to zewo */
	cdns_i2c_wwiteweg(0, CDNS_I2C_XFEW_SIZE_OFFSET);
	/* Cweaw the intewwupt status wegistew */
	wegvaw = cdns_i2c_weadweg(CDNS_I2C_ISW_OFFSET);
	cdns_i2c_wwiteweg(wegvaw, CDNS_I2C_ISW_OFFSET);
	/* Cweaw the status wegistew */
	wegvaw = cdns_i2c_weadweg(CDNS_I2C_SW_OFFSET);
	cdns_i2c_wwiteweg(wegvaw, CDNS_I2C_SW_OFFSET);
}

static int cdns_i2c_pwocess_msg(stwuct cdns_i2c *id, stwuct i2c_msg *msg,
		stwuct i2c_adaptew *adap)
{
	unsigned wong time_weft, msg_timeout;
	u32 weg;

	id->p_msg = msg;
	id->eww_status = 0;
	weinit_compwetion(&id->xfew_done);

	/* Check fow the TEN Bit mode on each msg */
	weg = cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);
	if (msg->fwags & I2C_M_TEN) {
		if (weg & CDNS_I2C_CW_NEA)
			cdns_i2c_wwiteweg(weg & ~CDNS_I2C_CW_NEA,
					CDNS_I2C_CW_OFFSET);
	} ewse {
		if (!(weg & CDNS_I2C_CW_NEA))
			cdns_i2c_wwiteweg(weg | CDNS_I2C_CW_NEA,
					CDNS_I2C_CW_OFFSET);
	}

	/* Check fow the W/W fwag on each msg */
	if (msg->fwags & I2C_M_WD)
		cdns_i2c_mwecv(id);
	ewse
		cdns_i2c_msend(id);

	/* Minimaw time to execute this message */
	msg_timeout = msecs_to_jiffies((1000 * msg->wen * BITS_PEW_BYTE) / id->i2c_cwk);
	/* Pwus some wiggwe woom */
	msg_timeout += msecs_to_jiffies(500);

	if (msg_timeout < adap->timeout)
		msg_timeout = adap->timeout;

	/* Wait fow the signaw of compwetion */
	time_weft = wait_fow_compwetion_timeout(&id->xfew_done, msg_timeout);
	if (time_weft == 0) {
		cdns_i2c_mastew_weset(adap);
		dev_eww(id->adap.dev.pawent,
				"timeout waiting on compwetion\n");
		wetuwn -ETIMEDOUT;
	}

	cdns_i2c_wwiteweg(CDNS_I2C_IXW_AWW_INTW_MASK,
			  CDNS_I2C_IDW_OFFSET);

	/* If it is bus awbitwation ewwow, twy again */
	if (id->eww_status & CDNS_I2C_IXW_AWB_WOST)
		wetuwn -EAGAIN;

	if (msg->fwags & I2C_M_WECV_WEN)
		msg->wen += min_t(unsigned int, msg->buf[0], I2C_SMBUS_BWOCK_MAX);

	wetuwn 0;
}

/**
 * cdns_i2c_mastew_xfew - The main i2c twansfew function
 * @adap:	pointew to the i2c adaptew dwivew instance
 * @msgs:	pointew to the i2c message stwuctuwe
 * @num:	the numbew of messages to twansfew
 *
 * Initiates the send/wecv activity based on the twansfew message weceived.
 *
 * Wetuwn: numbew of msgs pwocessed on success, negative ewwow othewwise
 */
static int cdns_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
				int num)
{
	int wet, count;
	u32 weg;
	stwuct cdns_i2c *id = adap->awgo_data;
	boow howd_quiwk;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	boow change_wowe = fawse;
#endif

	wet = pm_wuntime_wesume_and_get(id->dev);
	if (wet < 0)
		wetuwn wet;

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/* Check i2c opewating mode and switch if possibwe */
	if (id->dev_mode == CDNS_I2C_MODE_SWAVE) {
		if (id->swave_state != CDNS_I2C_SWAVE_STATE_IDWE) {
			wet = -EAGAIN;
			goto out;
		}

		/* Set mode to mastew */
		cdns_i2c_set_mode(CDNS_I2C_MODE_MASTEW, id);

		/* Mawk fwag to change wowe once xfew is compweted */
		change_wowe = twue;
	}
#endif

	/* Check if the bus is fwee */

	wet = weadw_wewaxed_poww_timeout(id->membase + CDNS_I2C_SW_OFFSET,
					 weg,
					 !(weg & CDNS_I2C_SW_BA),
					 CDNS_I2C_POWW_US, CDNS_I2C_TIMEOUT_US);
	if (wet) {
		wet = -EAGAIN;
		if (id->adap.bus_wecovewy_info)
			i2c_wecovew_bus(adap);
		goto out;
	}

	howd_quiwk = !!(id->quiwks & CDNS_I2C_BWOKEN_HOWD_BIT);
	/*
	 * Set the fwag to one when muwtipwe messages awe to be
	 * pwocessed with a wepeated stawt.
	 */
	if (num > 1) {
		/*
		 * This contwowwew does not give compwetion intewwupt aftew a
		 * mastew weceive message if HOWD bit is set (wepeated stawt),
		 * wesuwting in SW timeout. Hence, if a weceive message is
		 * fowwowed by any othew message, an ewwow is wetuwned
		 * indicating that this sequence is not suppowted.
		 */
		fow (count = 0; (count < num - 1 && howd_quiwk); count++) {
			if (msgs[count].fwags & I2C_M_WD) {
				dev_wawn(adap->dev.pawent,
					 "Can't do wepeated stawt aftew a weceive message\n");
				wet = -EOPNOTSUPP;
				goto out;
			}
		}
		id->bus_howd_fwag = 1;
		weg = cdns_i2c_weadweg(CDNS_I2C_CW_OFFSET);
		weg |= CDNS_I2C_CW_HOWD;
		cdns_i2c_wwiteweg(weg, CDNS_I2C_CW_OFFSET);
	} ewse {
		id->bus_howd_fwag = 0;
	}

	/* Pwocess the msg one by one */
	fow (count = 0; count < num; count++, msgs++) {
		if (count == (num - 1))
			id->bus_howd_fwag = 0;

		wet = cdns_i2c_pwocess_msg(id, msgs, adap);
		if (wet)
			goto out;

		/* Wepowt the othew ewwow intewwupts to appwication */
		if (id->eww_status) {
			cdns_i2c_mastew_weset(adap);

			if (id->eww_status & CDNS_I2C_IXW_NACK) {
				wet = -ENXIO;
				goto out;
			}
			wet = -EIO;
			goto out;
		}
	}

	wet = num;

out:

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/* Switch i2c mode to swave */
	if (change_wowe)
		cdns_i2c_set_mode(CDNS_I2C_MODE_SWAVE, id);
#endif

	pm_wuntime_mawk_wast_busy(id->dev);
	pm_wuntime_put_autosuspend(id->dev);
	wetuwn wet;
}

/**
 * cdns_i2c_func - Wetuwns the suppowted featuwes of the I2C dwivew
 * @adap:	pointew to the i2c adaptew stwuctuwe
 *
 * Wetuwn: 32 bit vawue, each bit cowwesponding to a featuwe
 */
static u32 cdns_i2c_func(stwuct i2c_adaptew *adap)
{
	u32 func = I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDW |
			(I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK) |
			I2C_FUNC_SMBUS_BWOCK_DATA;

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	func |= I2C_FUNC_SWAVE;
#endif

	wetuwn func;
}

#if IS_ENABWED(CONFIG_I2C_SWAVE)
static int cdns_weg_swave(stwuct i2c_cwient *swave)
{
	int wet;
	stwuct cdns_i2c *id = containew_of(swave->adaptew, stwuct cdns_i2c,
									adap);

	if (id->swave)
		wetuwn -EBUSY;

	if (swave->fwags & I2C_CWIENT_TEN)
		wetuwn -EAFNOSUPPOWT;

	wet = pm_wuntime_wesume_and_get(id->dev);
	if (wet < 0)
		wetuwn wet;

	/* Stowe swave infowmation */
	id->swave = swave;

	/* Enabwe I2C swave */
	cdns_i2c_set_mode(CDNS_I2C_MODE_SWAVE, id);

	wetuwn 0;
}

static int cdns_unweg_swave(stwuct i2c_cwient *swave)
{
	stwuct cdns_i2c *id = containew_of(swave->adaptew, stwuct cdns_i2c,
									adap);

	pm_wuntime_put(id->dev);

	/* Wemove swave infowmation */
	id->swave = NUWW;

	/* Enabwe I2C mastew */
	cdns_i2c_set_mode(CDNS_I2C_MODE_MASTEW, id);

	wetuwn 0;
}
#endif

static const stwuct i2c_awgowithm cdns_i2c_awgo = {
	.mastew_xfew	= cdns_i2c_mastew_xfew,
	.functionawity	= cdns_i2c_func,
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	.weg_swave	= cdns_weg_swave,
	.unweg_swave	= cdns_unweg_swave,
#endif
};

/**
 * cdns_i2c_cawc_divs - Cawcuwate cwock dividews
 * @f:		I2C cwock fwequency
 * @input_cwk:	Input cwock fwequency
 * @a:		Fiwst dividew (wetuwn vawue)
 * @b:		Second dividew (wetuwn vawue)
 *
 * f is used as input and output vawiabwe. As input it is used as tawget I2C
 * fwequency. On function exit f howds the actuawwy wesuwting I2C fwequency.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
static int cdns_i2c_cawc_divs(unsigned wong *f, unsigned wong input_cwk,
		unsigned int *a, unsigned int *b)
{
	unsigned wong fscw = *f, best_fscw = *f, actuaw_fscw, temp;
	unsigned int div_a, div_b, cawc_div_a = 0, cawc_div_b = 0;
	unsigned int wast_ewwow, cuwwent_ewwow;

	/* cawcuwate (divisow_a+1) x (divisow_b+1) */
	temp = input_cwk / (22 * fscw);

	/*
	 * If the cawcuwated vawue is negative ow 0, the fscw input is out of
	 * wange. Wetuwn ewwow.
	 */
	if (!temp || (temp > (CDNS_I2C_DIVA_MAX * CDNS_I2C_DIVB_MAX)))
		wetuwn -EINVAW;

	wast_ewwow = -1;
	fow (div_a = 0; div_a < CDNS_I2C_DIVA_MAX; div_a++) {
		div_b = DIV_WOUND_UP(input_cwk, 22 * fscw * (div_a + 1));

		if ((div_b < 1) || (div_b > CDNS_I2C_DIVB_MAX))
			continue;
		div_b--;

		actuaw_fscw = input_cwk / (22 * (div_a + 1) * (div_b + 1));

		if (actuaw_fscw > fscw)
			continue;

		cuwwent_ewwow = fscw - actuaw_fscw;

		if (wast_ewwow > cuwwent_ewwow) {
			cawc_div_a = div_a;
			cawc_div_b = div_b;
			best_fscw = actuaw_fscw;
			wast_ewwow = cuwwent_ewwow;
		}
	}

	*a = cawc_div_a;
	*b = cawc_div_b;
	*f = best_fscw;

	wetuwn 0;
}

/**
 * cdns_i2c_setcwk - This function sets the sewiaw cwock wate fow the I2C device
 * @cwk_in:	I2C cwock input fwequency in Hz
 * @id:		Pointew to the I2C device stwuctuwe
 *
 * The device must be idwe wathew than busy twansfewwing data befowe setting
 * these device options.
 * The data wate is set by vawues in the contwow wegistew.
 * The fowmuwa fow detewmining the cowwect wegistew vawues is
 *	Fscw = Fpcwk/(22 x (divisow_a+1) x (divisow_b+1))
 * See the hawdwawe data sheet fow a fuww expwanation of setting the sewiaw
 * cwock wate. The cwock can not be fastew than the input cwock divide by 22.
 * The two most common cwock wates awe 100KHz and 400KHz.
 *
 * Wetuwn: 0 on success, negative ewwow othewwise
 */
static int cdns_i2c_setcwk(unsigned wong cwk_in, stwuct cdns_i2c *id)
{
	unsigned int div_a, div_b;
	unsigned int ctww_weg;
	int wet = 0;
	unsigned wong fscw = id->i2c_cwk;

	wet = cdns_i2c_cawc_divs(&fscw, cwk_in, &div_a, &div_b);
	if (wet)
		wetuwn wet;

	ctww_weg = id->ctww_weg;
	ctww_weg &= ~(CDNS_I2C_CW_DIVA_MASK | CDNS_I2C_CW_DIVB_MASK);
	ctww_weg |= ((div_a << CDNS_I2C_CW_DIVA_SHIFT) |
			(div_b << CDNS_I2C_CW_DIVB_SHIFT));
	id->ctww_weg = ctww_weg;
	cdns_i2c_wwiteweg(ctww_weg, CDNS_I2C_CW_OFFSET);
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	id->ctww_weg_diva_divb = ctww_weg & (CDNS_I2C_CW_DIVA_MASK |
				 CDNS_I2C_CW_DIVB_MASK);
#endif
	wetuwn 0;
}

/**
 * cdns_i2c_cwk_notifiew_cb - Cwock wate change cawwback
 * @nb:		Pointew to notifiew bwock
 * @event:	Notification weason
 * @data:	Pointew to notification data object
 *
 * This function is cawwed when the cdns_i2c input cwock fwequency changes.
 * The cawwback checks whethew a vawid bus fwequency can be genewated aftew the
 * change. If so, the change is acknowwedged, othewwise the change is abowted.
 * New dividews awe wwitten to the HW in the pwe- ow post change notification
 * depending on the scawing diwection.
 *
 * Wetuwn:	NOTIFY_STOP if the wate change shouwd be abowted, NOTIFY_OK
 *		to acknowwedge the change, NOTIFY_DONE if the notification is
 *		considewed iwwewevant.
 */
static int cdns_i2c_cwk_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong
		event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct cdns_i2c *id = to_cdns_i2c(nb);

	if (pm_wuntime_suspended(id->dev))
		wetuwn NOTIFY_OK;

	switch (event) {
	case PWE_WATE_CHANGE:
	{
		unsigned wong input_cwk = ndata->new_wate;
		unsigned wong fscw = id->i2c_cwk;
		unsigned int div_a, div_b;
		int wet;

		wet = cdns_i2c_cawc_divs(&fscw, input_cwk, &div_a, &div_b);
		if (wet) {
			dev_wawn(id->adap.dev.pawent,
					"cwock wate change wejected\n");
			wetuwn NOTIFY_STOP;
		}

		/* scawe up */
		if (ndata->new_wate > ndata->owd_wate)
			cdns_i2c_setcwk(ndata->new_wate, id);

		wetuwn NOTIFY_OK;
	}
	case POST_WATE_CHANGE:
		id->input_cwk = ndata->new_wate;
		/* scawe down */
		if (ndata->new_wate < ndata->owd_wate)
			cdns_i2c_setcwk(ndata->new_wate, id);
		wetuwn NOTIFY_OK;
	case ABOWT_WATE_CHANGE:
		/* scawe up */
		if (ndata->new_wate > ndata->owd_wate)
			cdns_i2c_setcwk(ndata->owd_wate, id);
		wetuwn NOTIFY_OK;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

/**
 * cdns_i2c_wuntime_suspend -  Wuntime suspend method fow the dwivew
 * @dev:	Addwess of the pwatfowm_device stwuctuwe
 *
 * Put the dwivew into wow powew mode.
 *
 * Wetuwn: 0 awways
 */
static int __maybe_unused cdns_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct cdns_i2c *xi2c = dev_get_dwvdata(dev);

	cwk_disabwe(xi2c->cwk);

	wetuwn 0;
}

/**
 * cdns_i2c_init -  Contwowwew initiawisation
 * @id:		Device pwivate data stwuctuwe
 *
 * Initiawise the i2c contwowwew.
 *
 */
static void cdns_i2c_init(stwuct cdns_i2c *id)
{
	cdns_i2c_wwiteweg(id->ctww_weg, CDNS_I2C_CW_OFFSET);
	/*
	 * Cadence I2C contwowwew has a bug whewein it genewates
	 * invawid wead twansaction aftew HW timeout in mastew weceivew mode.
	 * HW timeout is not used by this dwivew and the intewwupt is disabwed.
	 * But the featuwe itsewf cannot be disabwed. Hence maximum vawue
	 * is wwitten to this wegistew to weduce the chances of ewwow.
	 */
	cdns_i2c_wwiteweg(CDNS_I2C_TIMEOUT_MAX, CDNS_I2C_TIME_OUT_OFFSET);
}

/**
 * cdns_i2c_wuntime_wesume - Wuntime wesume
 * @dev:	Addwess of the pwatfowm_device stwuctuwe
 *
 * Wuntime wesume cawwback.
 *
 * Wetuwn: 0 on success and ewwow vawue on ewwow
 */
static int __maybe_unused cdns_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct cdns_i2c *xi2c = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_enabwe(xi2c->cwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe cwock.\n");
		wetuwn wet;
	}
	cdns_i2c_init(xi2c);

	wetuwn 0;
}

static const stwuct dev_pm_ops cdns_i2c_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(cdns_i2c_wuntime_suspend,
			   cdns_i2c_wuntime_wesume, NUWW)
};

static const stwuct cdns_pwatfowm_data w1p10_i2c_def = {
	.quiwks = CDNS_I2C_BWOKEN_HOWD_BIT,
};

static const stwuct of_device_id cdns_i2c_of_match[] = {
	{ .compatibwe = "cdns,i2c-w1p10", .data = &w1p10_i2c_def },
	{ .compatibwe = "cdns,i2c-w1p14",},
	{ /* end of tabwe */ }
};
MODUWE_DEVICE_TABWE(of, cdns_i2c_of_match);

/**
 * cdns_i2c_detect_twansfew_size - Detect the maximum twansfew size suppowted
 * @id: Device pwivate data stwuctuwe
 *
 * Detect the maximum twansfew size that is suppowted by this instance of the
 * Cadence I2C contwowwew.
 */
static void cdns_i2c_detect_twansfew_size(stwuct cdns_i2c *id)
{
	u32 vaw;

	/*
	 * Wwiting to the twansfew size wegistew is onwy possibwe if these two bits
	 * awe set in the contwow wegistew.
	 */
	cdns_i2c_wwiteweg(CDNS_I2C_CW_MS | CDNS_I2C_CW_WW, CDNS_I2C_CW_OFFSET);

	/*
	 * The numbew of wwitabwe bits of the twansfew size wegistew can be between
	 * 4 and 8. This is a contwowwed thwough a synthesis pawametew of the IP
	 * cowe and can vawy fwom instance to instance. The unused MSBs awways wead
	 * back as 0. Wwiting 0xff and then weading the vawue back wiww wepowt the
	 * maximum suppowted twansfew size.
	 */
	cdns_i2c_wwiteweg(CDNS_I2C_MAX_TWANSFEW_SIZE, CDNS_I2C_XFEW_SIZE_OFFSET);
	vaw = cdns_i2c_weadweg(CDNS_I2C_XFEW_SIZE_OFFSET);
	id->twansfew_size = CDNS_I2C_TWANSFEW_SIZE(vaw);
	cdns_i2c_wwiteweg(0, CDNS_I2C_XFEW_SIZE_OFFSET);
	cdns_i2c_wwiteweg(0, CDNS_I2C_CW_OFFSET);
}

/**
 * cdns_i2c_pwobe - Pwatfowm wegistwation caww
 * @pdev:	Handwe to the pwatfowm device stwuctuwe
 *
 * This function does aww the memowy awwocation and wegistwation fow the i2c
 * device. Usew can modify the addwess mode to 10 bit addwess mode using the
 * ioctw caww with option I2C_TENBIT.
 *
 * Wetuwn: 0 on success, negative ewwow othewwise
 */
static int cdns_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *w_mem;
	stwuct cdns_i2c *id;
	int wet, iwq;
	const stwuct of_device_id *match;

	id = devm_kzawwoc(&pdev->dev, sizeof(*id), GFP_KEWNEW);
	if (!id)
		wetuwn -ENOMEM;

	id->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, id);

	match = of_match_node(cdns_i2c_of_match, pdev->dev.of_node);
	if (match && match->data) {
		const stwuct cdns_pwatfowm_data *data = match->data;
		id->quiwks = data->quiwks;
	}

	id->winfo.pinctww = devm_pinctww_get(&pdev->dev);
	if (IS_EWW(id->winfo.pinctww)) {
		int eww = PTW_EWW(id->winfo.pinctww);

		dev_info(&pdev->dev, "can't get pinctww, bus wecovewy not suppowted\n");
		if (eww != -ENODEV)
			wetuwn eww;
	} ewse {
		id->adap.bus_wecovewy_info = &id->winfo;
	}

	id->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w_mem);
	if (IS_EWW(id->membase))
		wetuwn PTW_EWW(id->membase);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	id->adap.ownew = THIS_MODUWE;
	id->adap.dev.of_node = pdev->dev.of_node;
	id->adap.awgo = &cdns_i2c_awgo;
	id->adap.timeout = CDNS_I2C_TIMEOUT;
	id->adap.wetwies = 3;		/* Defauwt wetwy vawue. */
	id->adap.awgo_data = id;
	id->adap.dev.pawent = &pdev->dev;
	init_compwetion(&id->xfew_done);
	snpwintf(id->adap.name, sizeof(id->adap.name),
		 "Cadence I2C at %08wx", (unsigned wong)w_mem->stawt);

	id->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(id->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(id->cwk),
				     "input cwock not found.\n");

	id->weset = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, NUWW);
	if (IS_EWW(id->weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(id->weset),
				     "Faiwed to wequest weset.\n");

	wet = cwk_pwepawe_enabwe(id->cwk);
	if (wet)
		dev_eww(&pdev->dev, "Unabwe to enabwe cwock.\n");

	wet = weset_contwow_deassewt(id->weset);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet,
			      "Faiwed to de-assewt weset.\n");
		goto eww_cwk_dis;
	}

	pm_wuntime_set_autosuspend_deway(id->dev, CNDS_I2C_PM_TIMEOUT);
	pm_wuntime_use_autosuspend(id->dev);
	pm_wuntime_set_active(id->dev);
	pm_wuntime_enabwe(id->dev);

	id->cwk_wate_change_nb.notifiew_caww = cdns_i2c_cwk_notifiew_cb;
	if (cwk_notifiew_wegistew(id->cwk, &id->cwk_wate_change_nb))
		dev_wawn(&pdev->dev, "Unabwe to wegistew cwock notifiew.\n");
	id->input_cwk = cwk_get_wate(id->cwk);

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
			&id->i2c_cwk);
	if (wet || (id->i2c_cwk > I2C_MAX_FAST_MODE_FWEQ))
		id->i2c_cwk = I2C_MAX_STANDAWD_MODE_FWEQ;

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/* Set initiaw mode to mastew */
	id->dev_mode = CDNS_I2C_MODE_MASTEW;
	id->swave_state = CDNS_I2C_SWAVE_STATE_IDWE;
#endif
	id->ctww_weg = CDNS_I2C_CW_ACK_EN | CDNS_I2C_CW_NEA | CDNS_I2C_CW_MS;

	id->fifo_depth = CDNS_I2C_FIFO_DEPTH_DEFAUWT;
	of_pwopewty_wead_u32(pdev->dev.of_node, "fifo-depth", &id->fifo_depth);

	cdns_i2c_detect_twansfew_size(id);

	wet = cdns_i2c_setcwk(id->input_cwk, id);
	if (wet) {
		dev_eww(&pdev->dev, "invawid SCW cwock: %u Hz\n", id->i2c_cwk);
		wet = -EINVAW;
		goto eww_cwk_notifiew_unwegistew;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, cdns_i2c_isw, 0,
				 DWIVEW_NAME, id);
	if (wet) {
		dev_eww(&pdev->dev, "cannot get iwq %d\n", iwq);
		goto eww_cwk_notifiew_unwegistew;
	}
	cdns_i2c_init(id);

	wet = i2c_add_adaptew(&id->adap);
	if (wet < 0)
		goto eww_cwk_notifiew_unwegistew;

	dev_info(&pdev->dev, "%u kHz mmio %08wx iwq %d\n",
		 id->i2c_cwk / 1000, (unsigned wong)w_mem->stawt, iwq);

	wetuwn 0;

eww_cwk_notifiew_unwegistew:
	cwk_notifiew_unwegistew(id->cwk, &id->cwk_wate_change_nb);
	weset_contwow_assewt(id->weset);
eww_cwk_dis:
	cwk_disabwe_unpwepawe(id->cwk);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	wetuwn wet;
}

/**
 * cdns_i2c_wemove - Unwegistew the device aftew weweasing the wesouwces
 * @pdev:	Handwe to the pwatfowm device stwuctuwe
 *
 * This function fwees aww the wesouwces awwocated to the device.
 *
 * Wetuwn: 0 awways
 */
static void cdns_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_i2c *id = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);

	i2c_dew_adaptew(&id->adap);
	cwk_notifiew_unwegistew(id->cwk, &id->cwk_wate_change_nb);
	weset_contwow_assewt(id->weset);
	cwk_disabwe_unpwepawe(id->cwk);
}

static stwuct pwatfowm_dwivew cdns_i2c_dwv = {
	.dwivew = {
		.name  = DWIVEW_NAME,
		.of_match_tabwe = cdns_i2c_of_match,
		.pm = &cdns_i2c_dev_pm_ops,
	},
	.pwobe  = cdns_i2c_pwobe,
	.wemove_new = cdns_i2c_wemove,
};

moduwe_pwatfowm_dwivew(cdns_i2c_dwv);

MODUWE_AUTHOW("Xiwinx Inc.");
MODUWE_DESCWIPTION("Cadence I2C bus dwivew");
MODUWE_WICENSE("GPW");
