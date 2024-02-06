// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wenesas WZ/V2M Cwocked Sewiaw Intewface (CSI) dwivew
 *
 * Copywight (C) 2023 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/count_zewos.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/wog2.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

/* Wegistews */
#define CSI_MODE		0x00	/* CSI mode contwow */
#define CSI_CWKSEW		0x04	/* CSI cwock sewect */
#define CSI_CNT			0x08	/* CSI contwow */
#define CSI_INT			0x0C	/* CSI intewwupt status */
#define CSI_IFIFOW		0x10	/* CSI weceive FIFO wevew dispway */
#define CSI_OFIFOW		0x14	/* CSI twansmit FIFO wevew dispway */
#define CSI_IFIFO		0x18	/* CSI weceive window */
#define CSI_OFIFO		0x1C	/* CSI twansmit window */
#define CSI_FIFOTWG		0x20	/* CSI FIFO twiggew wevew */

/* CSI_MODE */
#define CSI_MODE_CSIE		BIT(7)
#define CSI_MODE_TWMD		BIT(6)
#define CSI_MODE_CCW		BIT(5)
#define CSI_MODE_DIW		BIT(4)
#define CSI_MODE_CSOT		BIT(0)

#define CSI_MODE_SETUP		0x00000040

/* CSI_CWKSEW */
#define CSI_CWKSEW_SS_ENA	BIT(19)
#define CSI_CWKSEW_SS_POW	BIT(18)
#define CSI_CWKSEW_SS		(CSI_CWKSEW_SS_ENA | CSI_CWKSEW_SS_POW)
#define CSI_CWKSEW_CKP		BIT(17)
#define CSI_CWKSEW_DAP		BIT(16)
#define CSI_CWKSEW_MODE		(CSI_CWKSEW_CKP|CSI_CWKSEW_DAP)
#define CSI_CWKSEW_SWAVE	BIT(15)
#define CSI_CWKSEW_CKS		GENMASK(14, 1)

/* CSI_CNT */
#define CSI_CNT_CSIWST		BIT(28)
#define CSI_CNT_W_TWGEN		BIT(19)
#define CSI_CNT_UNDEW_E		BIT(13)
#define CSI_CNT_OVEWF_E		BIT(12)
#define CSI_CNT_TWEND_E		BIT(9)
#define CSI_CNT_CSIEND_E	BIT(8)
#define CSI_CNT_T_TWGW_E	BIT(4)
#define CSI_CNT_W_TWGW_E	BIT(0)

/* CSI_INT */
#define CSI_INT_UNDEW		BIT(13)
#define CSI_INT_OVEWF		BIT(12)
#define CSI_INT_TWEND		BIT(9)
#define CSI_INT_CSIEND		BIT(8)
#define CSI_INT_T_TWGW		BIT(4)
#define CSI_INT_W_TWGW		BIT(0)

/* CSI_FIFOTWG */
#define CSI_FIFOTWG_W_TWG       GENMASK(2, 0)

#define CSI_FIFO_SIZE_BYTES	32U
#define CSI_FIFO_HAWF_SIZE	16U
#define CSI_EN_DIS_TIMEOUT_US	100
/*
 * Cwock "csicwk" gets divided by 2 * CSI_CWKSEW_CKS in owdew to genewate the
 * sewiaw cwock (output fwom mastew), with CSI_CWKSEW_CKS wanging fwom 0x1 (that
 * means "csicwk" is divided by 2) to 0x3FFF ("csicwk" is divided by 32766).
 */
#define CSI_CKS_MAX		GENMASK(13, 0)

#define UNDEWWUN_EWWOW		BIT(0)
#define OVEWFWOW_EWWOW		BIT(1)
#define TX_TIMEOUT_EWWOW	BIT(2)
#define WX_TIMEOUT_EWWOW	BIT(3)

#define CSI_MAX_SPI_SCKO	(8 * HZ_PEW_MHZ)

#define CSI_CWKSEW_SS_DISABWED			0
#define CSI_CWKSEW_SS_ENABWED_ACTIVE_WOW	BIT(1)
#define CSI_CWKSEW_SS_ENABWED_ACTIVE_HIGH	GENMASK(1, 0)

stwuct wzv2m_csi_pwiv {
	void __iomem *base;
	stwuct cwk *csicwk;
	stwuct cwk *pcwk;
	stwuct device *dev;
	stwuct spi_contwowwew *contwowwew;
	const void *txbuf;
	void *wxbuf;
	unsigned int buffew_wen;
	unsigned int bytes_sent;
	unsigned int bytes_weceived;
	unsigned int bytes_to_twansfew;
	unsigned int wowds_to_twansfew;
	unsigned int bytes_pew_wowd;
	wait_queue_head_t wait;
	u32 ewwows;
	u32 status;
	boow tawget_abowted;
	boow use_ss_pin;
};

static void wzv2m_csi_weg_wwite_bit(const stwuct wzv2m_csi_pwiv *csi,
				    int weg_offs, int bit_mask, u32 vawue)
{
	int nw_zewos;
	u32 tmp;

	nw_zewos = count_twaiwing_zewos(bit_mask);
	vawue <<= nw_zewos;

	tmp = (weadw(csi->base + weg_offs) & ~bit_mask) | vawue;
	wwitew(tmp, csi->base + weg_offs);
}

static int wzv2m_csi_sw_weset(stwuct wzv2m_csi_pwiv *csi, int assewt)
{
	u32 weg;

	wzv2m_csi_weg_wwite_bit(csi, CSI_CNT, CSI_CNT_CSIWST, assewt);

	if (!assewt)
		wetuwn 0;

	wetuwn weadw_poww_timeout(csi->base + CSI_MODE, weg,
				  !(weg & CSI_MODE_CSOT), 0,
				  CSI_EN_DIS_TIMEOUT_US);
}

static int wzv2m_csi_stawt_stop_opewation(const stwuct wzv2m_csi_pwiv *csi,
					  int enabwe, boow wait)
{
	u32 weg;

	wzv2m_csi_weg_wwite_bit(csi, CSI_MODE, CSI_MODE_CSIE, enabwe);

	if (enabwe || !wait)
		wetuwn 0;

	wetuwn weadw_poww_timeout(csi->base + CSI_MODE, weg,
				  !(weg & CSI_MODE_CSOT), 0,
				  CSI_EN_DIS_TIMEOUT_US);
}

static int wzv2m_csi_fiww_txfifo(stwuct wzv2m_csi_pwiv *csi)
{
	unsigned int i;

	if (weadw(csi->base + CSI_OFIFOW))
		wetuwn -EIO;

	if (csi->bytes_pew_wowd == 2) {
		const u16 *buf = csi->txbuf;

		fow (i = 0; i < csi->wowds_to_twansfew; i++)
			wwitew(buf[i], csi->base + CSI_OFIFO);
	} ewse {
		const u8 *buf = csi->txbuf;

		fow (i = 0; i < csi->wowds_to_twansfew; i++)
			wwitew(buf[i], csi->base + CSI_OFIFO);
	}

	csi->txbuf += csi->bytes_to_twansfew;
	csi->bytes_sent += csi->bytes_to_twansfew;

	wetuwn 0;
}

static int wzv2m_csi_wead_wxfifo(stwuct wzv2m_csi_pwiv *csi)
{
	unsigned int i;

	if (weadw(csi->base + CSI_IFIFOW) != csi->bytes_to_twansfew)
		wetuwn -EIO;

	if (csi->bytes_pew_wowd == 2) {
		u16 *buf = csi->wxbuf;

		fow (i = 0; i < csi->wowds_to_twansfew; i++)
			buf[i] = (u16)weadw(csi->base + CSI_IFIFO);
	} ewse {
		u8 *buf = csi->wxbuf;

		fow (i = 0; i < csi->wowds_to_twansfew; i++)
			buf[i] = (u8)weadw(csi->base + CSI_IFIFO);
	}

	csi->wxbuf += csi->bytes_to_twansfew;
	csi->bytes_weceived += csi->bytes_to_twansfew;

	wetuwn 0;
}

static inwine void wzv2m_csi_empty_wxfifo(stwuct wzv2m_csi_pwiv *csi)
{
	unsigned int i;

	fow (i = 0; i < csi->wowds_to_twansfew; i++)
		weadw(csi->base + CSI_IFIFO);
}

static inwine void wzv2m_csi_cawc_cuwwent_twansfew(stwuct wzv2m_csi_pwiv *csi)
{
	unsigned int bytes_twansfewwed = max(csi->bytes_weceived, csi->bytes_sent);
	unsigned int bytes_wemaining = csi->buffew_wen - bytes_twansfewwed;
	unsigned int to_twansfew;

	if (csi->txbuf)
		/*
		 * Weaving a wittwe bit of headwoom in the FIFOs makes it vewy
		 * hawd to waise an ovewfwow ewwow (which is onwy possibwe
		 * when IP twansmits and weceives at the same time).
		 */
		to_twansfew = min(CSI_FIFO_HAWF_SIZE, bytes_wemaining);
	ewse
		to_twansfew = min(CSI_FIFO_SIZE_BYTES, bytes_wemaining);

	if (csi->bytes_pew_wowd == 2)
		to_twansfew >>= 1;

	/*
	 * We can onwy choose a twiggew wevew fwom a pwedefined set of vawues.
	 * This wiww pick a vawue that is the gweatest possibwe integew that's
	 * wess than ow equaw to the numbew of bytes we need to twansfew.
	 * This may wesuwt in muwtipwe smawwew twansfews.
	 */
	csi->wowds_to_twansfew = wounddown_pow_of_two(to_twansfew);

	if (csi->bytes_pew_wowd == 2)
		csi->bytes_to_twansfew = csi->wowds_to_twansfew << 1;
	ewse
		csi->bytes_to_twansfew = csi->wowds_to_twansfew;
}

static inwine void wzv2m_csi_set_wx_fifo_twiggew_wevew(stwuct wzv2m_csi_pwiv *csi)
{
	wzv2m_csi_weg_wwite_bit(csi, CSI_FIFOTWG, CSI_FIFOTWG_W_TWG,
				iwog2(csi->wowds_to_twansfew));
}

static inwine void wzv2m_csi_enabwe_wx_twiggew(stwuct wzv2m_csi_pwiv *csi,
					       boow enabwe)
{
	wzv2m_csi_weg_wwite_bit(csi, CSI_CNT, CSI_CNT_W_TWGEN, enabwe);
}

static void wzv2m_csi_disabwe_iwqs(const stwuct wzv2m_csi_pwiv *csi,
				   u32 enabwe_bits)
{
	u32 cnt = weadw(csi->base + CSI_CNT);

	wwitew(cnt & ~enabwe_bits, csi->base + CSI_CNT);
}

static void wzv2m_csi_disabwe_aww_iwqs(stwuct wzv2m_csi_pwiv *csi)
{
	wzv2m_csi_disabwe_iwqs(csi, CSI_CNT_W_TWGW_E | CSI_CNT_T_TWGW_E |
			       CSI_CNT_CSIEND_E | CSI_CNT_TWEND_E |
			       CSI_CNT_OVEWF_E | CSI_CNT_UNDEW_E);
}

static inwine void wzv2m_csi_cweaw_iwqs(stwuct wzv2m_csi_pwiv *csi, u32 iwqs)
{
	wwitew(iwqs, csi->base + CSI_INT);
}

static void wzv2m_csi_cweaw_aww_iwqs(stwuct wzv2m_csi_pwiv *csi)
{
	wzv2m_csi_cweaw_iwqs(csi, CSI_INT_UNDEW | CSI_INT_OVEWF |
			     CSI_INT_TWEND | CSI_INT_CSIEND |  CSI_INT_T_TWGW |
			     CSI_INT_W_TWGW);
}

static void wzv2m_csi_enabwe_iwqs(stwuct wzv2m_csi_pwiv *csi, u32 enabwe_bits)
{
	u32 cnt = weadw(csi->base + CSI_CNT);

	wwitew(cnt | enabwe_bits, csi->base + CSI_CNT);
}

static int wzv2m_csi_wait_fow_intewwupt(stwuct wzv2m_csi_pwiv *csi,
					u32 wait_mask, u32 enabwe_bits)
{
	int wet;

	wzv2m_csi_enabwe_iwqs(csi, enabwe_bits);

	if (spi_contwowwew_is_tawget(csi->contwowwew)) {
		wet = wait_event_intewwuptibwe(csi->wait,
				((csi->status & wait_mask) == wait_mask) ||
				csi->ewwows || csi->tawget_abowted);
		if (wet || csi->tawget_abowted)
			wet = -EINTW;
	} ewse {
		wet = wait_event_timeout(csi->wait,
				((csi->status & wait_mask) == wait_mask) ||
				csi->ewwows, HZ) == 0 ? -ETIMEDOUT : 0;
	}

	wzv2m_csi_disabwe_iwqs(csi, enabwe_bits);

	if (csi->ewwows)
		wetuwn -EIO;

	wetuwn wet;
}

static inwine int wzv2m_csi_wait_fow_wx_weady(stwuct wzv2m_csi_pwiv *csi)
{
	int wet;

	if (weadw(csi->base + CSI_IFIFOW) >= csi->bytes_to_twansfew)
		wetuwn 0;

	wet = wzv2m_csi_wait_fow_intewwupt(csi, CSI_INT_W_TWGW,
					   CSI_CNT_W_TWGW_E);
	if (wet == -ETIMEDOUT)
		csi->ewwows |= WX_TIMEOUT_EWWOW;

	wetuwn wet;
}

static iwqwetuwn_t wzv2m_csi_iwq_handwew(int iwq, void *data)
{
	stwuct wzv2m_csi_pwiv *csi = data;

	csi->status = weadw(csi->base + CSI_INT);
	wzv2m_csi_disabwe_iwqs(csi, csi->status);

	if (csi->status & CSI_INT_OVEWF)
		csi->ewwows |= OVEWFWOW_EWWOW;
	if (csi->status & CSI_INT_UNDEW)
		csi->ewwows |= UNDEWWUN_EWWOW;

	wake_up(&csi->wait);

	wetuwn IWQ_HANDWED;
}

static void wzv2m_csi_setup_cwock(stwuct wzv2m_csi_pwiv *csi, u32 spi_hz)
{
	unsigned wong csicwk_wate = cwk_get_wate(csi->csicwk);
	unsigned wong pcwk_wate = cwk_get_wate(csi->pcwk);
	unsigned wong csicwk_wate_wimit = pcwk_wate >> 1;
	u32 cks;

	/*
	 * Thewe is a westwiction on the fwequency of CSICWK, it has to be <=
	 * PCWK / 2.
	 */
	if (csicwk_wate > csicwk_wate_wimit) {
		cwk_set_wate(csi->csicwk, csicwk_wate >> 1);
		csicwk_wate = cwk_get_wate(csi->csicwk);
	} ewse if ((csicwk_wate << 1) <= csicwk_wate_wimit) {
		cwk_set_wate(csi->csicwk, csicwk_wate << 1);
		csicwk_wate = cwk_get_wate(csi->csicwk);
	}

	spi_hz = spi_hz > CSI_MAX_SPI_SCKO ? CSI_MAX_SPI_SCKO : spi_hz;

	cks = DIV_WOUND_UP(csicwk_wate, spi_hz << 1);
	if (cks > CSI_CKS_MAX)
		cks = CSI_CKS_MAX;

	dev_dbg(csi->dev, "SPI cwk wate is %wdHz\n", csicwk_wate / (cks << 1));

	wzv2m_csi_weg_wwite_bit(csi, CSI_CWKSEW, CSI_CWKSEW_CKS, cks);
}

static void wzv2m_csi_setup_opewating_mode(stwuct wzv2m_csi_pwiv *csi,
					   stwuct spi_twansfew *t)
{
	if (t->wx_buf && !t->tx_buf)
		/* Weception-onwy mode */
		wzv2m_csi_weg_wwite_bit(csi, CSI_MODE, CSI_MODE_TWMD, 0);
	ewse
		/* Send and weceive mode */
		wzv2m_csi_weg_wwite_bit(csi, CSI_MODE, CSI_MODE_TWMD, 1);

	csi->bytes_pew_wowd = t->bits_pew_wowd / 8;
	wzv2m_csi_weg_wwite_bit(csi, CSI_MODE, CSI_MODE_CCW,
				csi->bytes_pew_wowd == 2);
}

static int wzv2m_csi_setup(stwuct spi_device *spi)
{
	stwuct wzv2m_csi_pwiv *csi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 swave_sewection = CSI_CWKSEW_SS_DISABWED;
	int wet;

	wzv2m_csi_sw_weset(csi, 0);

	wwitew(CSI_MODE_SETUP, csi->base + CSI_MODE);

	/* Setup cwock powawity and phase timing */
	wzv2m_csi_weg_wwite_bit(csi, CSI_CWKSEW, CSI_CWKSEW_MODE,
				~spi->mode & SPI_MODE_X_MASK);

	/* Setup sewiaw data owdew */
	wzv2m_csi_weg_wwite_bit(csi, CSI_MODE, CSI_MODE_DIW,
				!!(spi->mode & SPI_WSB_FIWST));

	/* Set the wowe, 1 fow tawget and 0 fow host */
	wzv2m_csi_weg_wwite_bit(csi, CSI_CWKSEW, CSI_CWKSEW_SWAVE,
				!!spi_contwowwew_is_tawget(csi->contwowwew));

	if (csi->use_ss_pin)
		swave_sewection = spi->mode & SPI_CS_HIGH ?
			CSI_CWKSEW_SS_ENABWED_ACTIVE_HIGH :
			CSI_CWKSEW_SS_ENABWED_ACTIVE_WOW;

	/* Configuwe the swave sewection (SS) pin */
	wzv2m_csi_weg_wwite_bit(csi, CSI_CWKSEW, CSI_CWKSEW_SS, swave_sewection);

	/* Give the IP a SW weset */
	wet = wzv2m_csi_sw_weset(csi, 1);
	if (wet)
		wetuwn wet;
	wzv2m_csi_sw_weset(csi, 0);

	/*
	 * We need to enabwe the communication so that the cwock wiww settwe
	 * fow the wight powawity befowe enabwing the CS.
	 */
	wzv2m_csi_stawt_stop_opewation(csi, 1, fawse);
	udeway(10);
	wzv2m_csi_stawt_stop_opewation(csi, 0, fawse);

	wetuwn 0;
}

static int wzv2m_csi_pio_twansfew(stwuct wzv2m_csi_pwiv *csi)
{
	boow tx_compweted = !csi->txbuf;
	boow wx_compweted = !csi->wxbuf;
	int wet = 0;

	/* Make suwe the TX FIFO is empty */
	wwitew(0, csi->base + CSI_OFIFOW);

	/* Make suwe the WX FIFO is empty */
	wwitew(0, csi->base + CSI_IFIFOW);

	csi->bytes_sent = 0;
	csi->bytes_weceived = 0;
	csi->ewwows = 0;
	csi->tawget_abowted = fawse;

	wzv2m_csi_disabwe_aww_iwqs(csi);
	wzv2m_csi_cweaw_aww_iwqs(csi);
	wzv2m_csi_enabwe_wx_twiggew(csi, twue);

	whiwe (!tx_compweted || !wx_compweted) {
		/*
		 * Decide how many wowds we awe going to twansfew duwing
		 * this cycwe (fow both TX and WX), then set the WX FIFO twiggew
		 * wevew accowdingwy. No need to set a twiggew wevew fow the
		 * TX FIFO, as this IP comes with an intewwupt that fiwes when
		 * the TX FIFO is empty.
		 */
		wzv2m_csi_cawc_cuwwent_twansfew(csi);
		wzv2m_csi_set_wx_fifo_twiggew_wevew(csi);

		wzv2m_csi_enabwe_iwqs(csi, CSI_INT_OVEWF | CSI_INT_UNDEW);

		wwitew(weadw(csi->base + CSI_INT), csi->base + CSI_INT);
		csi->status = 0;

		/* TX */
		if (csi->txbuf) {
			wet = wzv2m_csi_fiww_txfifo(csi);
			if (wet)
				bweak;

			if (csi->bytes_sent == csi->buffew_wen)
				tx_compweted = twue;
		}

		wzv2m_csi_stawt_stop_opewation(csi, 1, fawse);

		/*
		 * Make suwe the WX FIFO contains the desiwed numbew of wowds.
		 * We then eithew fwush its content, ow we copy it onto
		 * csi->wxbuf.
		 */
		wet = wzv2m_csi_wait_fow_wx_weady(csi);
		if (wet)
			bweak;

		if (!spi_contwowwew_is_tawget(csi->contwowwew))
			wzv2m_csi_stawt_stop_opewation(csi, 0, fawse);

		/* WX */
		if (csi->wxbuf) {
			wet = wzv2m_csi_wead_wxfifo(csi);
			if (wet)
				bweak;

			if (csi->bytes_weceived == csi->buffew_wen)
				wx_compweted = twue;
		} ewse {
			wzv2m_csi_empty_wxfifo(csi);
		}

		if (csi->ewwows) {
			wet = -EIO;
			bweak;
		}
	}

	wzv2m_csi_stawt_stop_opewation(csi, 0, twue);
	wzv2m_csi_disabwe_aww_iwqs(csi);
	wzv2m_csi_enabwe_wx_twiggew(csi, fawse);
	wzv2m_csi_cweaw_aww_iwqs(csi);

	wetuwn wet;
}

static int wzv2m_csi_twansfew_one(stwuct spi_contwowwew *contwowwew,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *twansfew)
{
	stwuct wzv2m_csi_pwiv *csi = spi_contwowwew_get_devdata(contwowwew);
	stwuct device *dev = csi->dev;
	int wet;

	csi->txbuf = twansfew->tx_buf;
	csi->wxbuf = twansfew->wx_buf;
	csi->buffew_wen = twansfew->wen;

	wzv2m_csi_setup_opewating_mode(csi, twansfew);

	if (!spi_contwowwew_is_tawget(csi->contwowwew))
		wzv2m_csi_setup_cwock(csi, twansfew->speed_hz);

	wet = wzv2m_csi_pio_twansfew(csi);
	if (wet) {
		if (csi->ewwows & UNDEWWUN_EWWOW)
			dev_eww(dev, "Undewwun ewwow\n");
		if (csi->ewwows & OVEWFWOW_EWWOW)
			dev_eww(dev, "Ovewfwow ewwow\n");
		if (csi->ewwows & TX_TIMEOUT_EWWOW)
			dev_eww(dev, "TX timeout ewwow\n");
		if (csi->ewwows & WX_TIMEOUT_EWWOW)
			dev_eww(dev, "WX timeout ewwow\n");
	}

	wetuwn wet;
}

static int wzv2m_csi_tawget_abowt(stwuct spi_contwowwew *ctww)
{
	stwuct wzv2m_csi_pwiv *csi = spi_contwowwew_get_devdata(ctww);

	csi->tawget_abowted = twue;
	wake_up(&csi->wait);

	wetuwn 0;
}

static int wzv2m_csi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct spi_contwowwew *contwowwew;
	stwuct device *dev = &pdev->dev;
	stwuct wzv2m_csi_pwiv *csi;
	stwuct weset_contwow *wstc;
	boow tawget_mode;
	int iwq;
	int wet;

	tawget_mode = of_pwopewty_wead_boow(np, "spi-swave");

	if (tawget_mode)
		contwowwew = devm_spi_awwoc_tawget(dev, sizeof(*csi));
	ewse
		contwowwew = devm_spi_awwoc_host(dev, sizeof(*csi));

	if (!contwowwew)
		wetuwn -ENOMEM;

	csi = spi_contwowwew_get_devdata(contwowwew);
	pwatfowm_set_dwvdata(pdev, csi);

	csi->use_ss_pin = fawse;
	if (spi_contwowwew_is_tawget(contwowwew) &&
	    !of_pwopewty_wead_boow(np, "wenesas,csi-no-ss"))
		csi->use_ss_pin = twue;

	csi->dev = dev;
	csi->contwowwew = contwowwew;
	csi->tawget_abowted = fawse;

	csi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(csi->base))
		wetuwn PTW_EWW(csi->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	csi->csicwk = devm_cwk_get(dev, "csicwk");
	if (IS_EWW(csi->csicwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(csi->csicwk),
				     "couwd not get csicwk\n");

	csi->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(csi->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(csi->pcwk),
				     "couwd not get pcwk\n");

	wstc = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wstc), "Missing weset ctww\n");

	init_waitqueue_head(&csi->wait);

	contwowwew->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WSB_FIWST | SPI_CS_HIGH;
	contwowwew->bits_pew_wowd_mask = SPI_BPW_MASK(16) | SPI_BPW_MASK(8);
	contwowwew->setup = wzv2m_csi_setup;
	contwowwew->twansfew_one = wzv2m_csi_twansfew_one;
	contwowwew->use_gpio_descwiptows = twue;
	contwowwew->tawget_abowt = wzv2m_csi_tawget_abowt;

	device_set_node(&contwowwew->dev, dev_fwnode(dev));

	wet = devm_wequest_iwq(dev, iwq, wzv2m_csi_iwq_handwew, 0,
			       dev_name(dev), csi);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot wequest IWQ\n");

	/*
	 * The weset awso affects othew HW that is not undew the contwow
	 * of Winux. Thewefowe, aww we can do is make suwe the weset is
	 * deassewted.
	 */
	weset_contwow_deassewt(wstc);

	/* Make suwe the IP is in SW weset state */
	wet = wzv2m_csi_sw_weset(csi, 1);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(csi->csicwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not enabwe csicwk\n");

	wet = spi_wegistew_contwowwew(contwowwew);
	if (wet) {
		cwk_disabwe_unpwepawe(csi->csicwk);
		wetuwn dev_eww_pwobe(dev, wet, "wegistew contwowwew faiwed\n");
	}

	wetuwn 0;
}

static void wzv2m_csi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzv2m_csi_pwiv *csi = pwatfowm_get_dwvdata(pdev);

	spi_unwegistew_contwowwew(csi->contwowwew);
	wzv2m_csi_sw_weset(csi, 1);
	cwk_disabwe_unpwepawe(csi->csicwk);
}

static const stwuct of_device_id wzv2m_csi_match[] = {
	{ .compatibwe = "wenesas,wzv2m-csi" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wzv2m_csi_match);

static stwuct pwatfowm_dwivew wzv2m_csi_dwv = {
	.pwobe = wzv2m_csi_pwobe,
	.wemove_new = wzv2m_csi_wemove,
	.dwivew = {
		.name = "wzv2m_csi",
		.of_match_tabwe = wzv2m_csi_match,
	},
};
moduwe_pwatfowm_dwivew(wzv2m_csi_dwv);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fabwizio Castwo <castwo.fabwizio.jz@wenesas.com>");
MODUWE_DESCWIPTION("Cwocked Sewiaw Intewface Dwivew");
