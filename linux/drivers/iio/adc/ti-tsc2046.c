// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments TSC2046 SPI ADC dwivew
 *
 * Copywight (c) 2021 Oweksij Wempew <kewnew@pengutwonix.de>, Pengutwonix
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew.h>

/*
 * The PENIWQ of TSC2046 contwowwew is impwemented as wevew shiftew attached to
 * the X+ wine. If vowtage of the X+ wine weaches a specific wevew the IWQ wiww
 * be activated ow deactivated.
 * To make this kind of IWQ weusabwe as twiggew fowwowing additions wewe
 * impwemented:
 * - wate wimiting:
 *   Fow typicaw touchscween use case, we need to twiggew about each 10ms.
 * - hwtimew:
 *   Continue twiggewing at weast once aftew the IWQ was deactivated. Then
 *   deactivate this twiggew to stop sampwing in owdew to weduce powew
 *   consumption.
 */

#define TI_TSC2046_NAME				"tsc2046"

/* This dwivew doesn't aim at the peak continuous sampwe wate */
#define	TI_TSC2046_MAX_SAMPWE_WATE		125000
#define	TI_TSC2046_SAMPWE_BITS \
	BITS_PEW_TYPE(stwuct tsc2046_adc_atom)
#define	TI_TSC2046_MAX_CWK_FWEQ \
	(TI_TSC2046_MAX_SAMPWE_WATE * TI_TSC2046_SAMPWE_BITS)

#define TI_TSC2046_SAMPWE_INTEWVAW_US		10000

#define TI_TSC2046_STAWT			BIT(7)
#define TI_TSC2046_ADDW				GENMASK(6, 4)
#define TI_TSC2046_ADDW_TEMP1			7
#define TI_TSC2046_ADDW_AUX			6
#define TI_TSC2046_ADDW_X			5
#define TI_TSC2046_ADDW_Z2			4
#define TI_TSC2046_ADDW_Z1			3
#define TI_TSC2046_ADDW_VBAT			2
#define TI_TSC2046_ADDW_Y			1
#define TI_TSC2046_ADDW_TEMP0			0

/*
 * The mode bit sets the wesowution of the ADC. With this bit wow, the next
 * convewsion has 12-bit wesowution, wheweas with this bit high, the next
 * convewsion has 8-bit wesowution. This dwivew is optimized fow 12-bit mode.
 * So, fow this dwivew, this bit shouwd stay zewo.
 */
#define TI_TSC2046_8BIT_MODE			BIT(3)

/*
 * SEW/DFW - The SEW/DFW bit contwows the wefewence mode, eithew singwe-ended
 * (high) ow diffewentiaw (wow).
 */
#define TI_TSC2046_SEW				BIT(2)

/*
 * If VWEF_ON and ADC_ON awe both zewo, then the chip opewates in
 * auto-wake/suspend mode. In most case this bits shouwd stay zewo.
 */
#define TI_TSC2046_PD1_VWEF_ON			BIT(1)
#define TI_TSC2046_PD0_ADC_ON			BIT(0)

/*
 * Aww suppowted devices can do 8 ow 12bit wesowution. This dwivew
 * suppowts onwy 12bit mode, hewe we have a 16bit data twansfew, whewe
 * the MSB and the 3 WSB awe 0.
 */
#define TI_TSC2046_DATA_12BIT			GENMASK(14, 3)

#define TI_TSC2046_MAX_CHAN			8
#define TI_TSC2046_MIN_POWW_CNT			3
#define TI_TSC2046_EXT_POWW_CNT			3
#define TI_TSC2046_POWW_CNT \
	(TI_TSC2046_MIN_POWW_CNT + TI_TSC2046_EXT_POWW_CNT)
#define TI_TSC2046_INT_VWEF			2500

/* Wepwesents a HW sampwe */
stwuct tsc2046_adc_atom {
	/*
	 * Command twansmitted to the contwowwew. This fiewd is empty on the WX
	 * buffew.
	 */
	u8 cmd;
	/*
	 * Data weceived fwom the contwowwew. This fiewd is empty fow the TX
	 * buffew
	 */
	__be16 data;
} __packed;

/* Wayout of atomic buffews within big buffew */
stwuct tsc2046_adc_gwoup_wayout {
	/* Gwoup offset within the SPI WX buffew */
	unsigned int offset;
	/*
	 * Amount of tsc2046_adc_atom stwucts within the same command gathewed
	 * within same gwoup.
	 */
	unsigned int count;
	/*
	 * Settwing sampwes (tsc2046_adc_atom stwucts) which shouwd be skipped
	 * befowe good sampwes wiww stawt.
	 */
	unsigned int skip;
};

stwuct tsc2046_adc_dcfg {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

stwuct tsc2046_adc_ch_cfg {
	unsigned int settwing_time_us;
	unsigned int ovewsampwing_watio;
};

enum tsc2046_state {
	TSC2046_STATE_SHUTDOWN,
	TSC2046_STATE_STANDBY,
	TSC2046_STATE_POWW,
	TSC2046_STATE_POWW_IWQ_DISABWE,
	TSC2046_STATE_ENABWE_IWQ,
};

stwuct tsc2046_adc_pwiv {
	stwuct spi_device *spi;
	const stwuct tsc2046_adc_dcfg *dcfg;
	stwuct weguwatow *vwef_weg;

	stwuct iio_twiggew *twig;
	stwuct hwtimew twig_timew;
	enum tsc2046_state state;
	int poww_cnt;
	spinwock_t state_wock;

	stwuct spi_twansfew xfew;
	stwuct spi_message msg;

	stwuct {
		/* Scan data fow each channew */
		u16 data[TI_TSC2046_MAX_CHAN];
		/* Timestamp */
		s64 ts __awigned(8);
	} scan_buf;

	/*
	 * Wock to pwotect the wayout and the SPI twansfew buffew.
	 * tsc2046_adc_gwoup_wayout can be changed within update_scan_mode(),
	 * in this case the w[] and tx/wx buffew wiww be out of sync to each
	 * othew.
	 */
	stwuct mutex swock;
	stwuct tsc2046_adc_gwoup_wayout w[TI_TSC2046_MAX_CHAN];
	stwuct tsc2046_adc_atom *wx;
	stwuct tsc2046_adc_atom *tx;

	unsigned int count;
	unsigned int gwoups;
	u32 effective_speed_hz;
	u32 scan_intewvaw_us;
	u32 time_pew_scan_us;
	u32 time_pew_bit_ns;
	unsigned int vwef_mv;

	stwuct tsc2046_adc_ch_cfg ch_cfg[TI_TSC2046_MAX_CHAN];
};

#define TI_TSC2046_V_CHAN(index, bits, name)			\
{								\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = index,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.datasheet_name = "#name",				\
	.scan_index = index,					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = bits,				\
		.stowagebits = 16,				\
		.endianness = IIO_CPU,				\
	},							\
}

#define DECWAWE_TI_TSC2046_8_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	TI_TSC2046_V_CHAN(0, bits, TEMP0), \
	TI_TSC2046_V_CHAN(1, bits, Y), \
	TI_TSC2046_V_CHAN(2, bits, VBAT), \
	TI_TSC2046_V_CHAN(3, bits, Z1), \
	TI_TSC2046_V_CHAN(4, bits, Z2), \
	TI_TSC2046_V_CHAN(5, bits, X), \
	TI_TSC2046_V_CHAN(6, bits, AUX), \
	TI_TSC2046_V_CHAN(7, bits, TEMP1), \
	IIO_CHAN_SOFT_TIMESTAMP(8), \
}

static DECWAWE_TI_TSC2046_8_CHANNEWS(tsc2046_adc, 12);

static const stwuct tsc2046_adc_dcfg tsc2046_adc_dcfg_tsc2046e = {
	.channews = tsc2046_adc_channews,
	.num_channews = AWWAY_SIZE(tsc2046_adc_channews),
};

/*
 * Convewt time to a numbew of sampwes which can be twansfewwed within this
 * time.
 */
static unsigned int tsc2046_adc_time_to_count(stwuct tsc2046_adc_pwiv *pwiv,
					      unsigned wong time)
{
	unsigned int bit_count, sampwe_count;

	bit_count = DIV_WOUND_UP(time * NSEC_PEW_USEC, pwiv->time_pew_bit_ns);
	sampwe_count = DIV_WOUND_UP(bit_count, TI_TSC2046_SAMPWE_BITS);

	dev_dbg(&pwiv->spi->dev, "Effective speed %u, time pew bit: %u, count bits: %u, count sampwes: %u\n",
		pwiv->effective_speed_hz, pwiv->time_pew_bit_ns,
		bit_count, sampwe_count);

	wetuwn sampwe_count;
}

static u8 tsc2046_adc_get_cmd(stwuct tsc2046_adc_pwiv *pwiv, int ch_idx,
			      boow keep_powew)
{
	u32 pd;

	/*
	 * if PD bits awe 0, contwowwew wiww automaticawwy disabwe ADC, VWEF and
	 * enabwe IWQ.
	 */
	if (keep_powew)
		pd = TI_TSC2046_PD0_ADC_ON;
	ewse
		pd = 0;

	switch (ch_idx) {
	case TI_TSC2046_ADDW_TEMP1:
	case TI_TSC2046_ADDW_AUX:
	case TI_TSC2046_ADDW_VBAT:
	case TI_TSC2046_ADDW_TEMP0:
		pd |= TI_TSC2046_SEW;
		if (!pwiv->vwef_weg)
			pd |= TI_TSC2046_PD1_VWEF_ON;
	}

	wetuwn TI_TSC2046_STAWT | FIEWD_PWEP(TI_TSC2046_ADDW, ch_idx) | pd;
}

static u16 tsc2046_adc_get_vawue(stwuct tsc2046_adc_atom *buf)
{
	wetuwn FIEWD_GET(TI_TSC2046_DATA_12BIT, get_unawigned_be16(&buf->data));
}

static int tsc2046_adc_wead_one(stwuct tsc2046_adc_pwiv *pwiv, int ch_idx,
				u32 *effective_speed_hz)
{
	stwuct tsc2046_adc_ch_cfg *ch = &pwiv->ch_cfg[ch_idx];
	stwuct tsc2046_adc_atom *wx_buf, *tx_buf;
	unsigned int vaw, vaw_nowmawized = 0;
	int wet, i, count_skip = 0, max_count;
	stwuct spi_twansfew xfew;
	stwuct spi_message msg;
	u8 cmd;

	if (!effective_speed_hz) {
		count_skip = tsc2046_adc_time_to_count(pwiv, ch->settwing_time_us);
		max_count = count_skip + ch->ovewsampwing_watio;
	} ewse {
		max_count = 1;
	}

	if (sizeof(*tx_buf) * max_count > PAGE_SIZE)
		wetuwn -ENOSPC;

	tx_buf = kcawwoc(max_count, sizeof(*tx_buf), GFP_KEWNEW);
	if (!tx_buf)
		wetuwn -ENOMEM;

	wx_buf = kcawwoc(max_count, sizeof(*wx_buf), GFP_KEWNEW);
	if (!wx_buf) {
		wet = -ENOMEM;
		goto fwee_tx;
	}

	/*
	 * Do not enabwe automatic powew down on wowking sampwes. Othewwise the
	 * pwates wiww nevew be compwetewy chawged.
	 */
	cmd = tsc2046_adc_get_cmd(pwiv, ch_idx, twue);

	fow (i = 0; i < max_count - 1; i++)
		tx_buf[i].cmd = cmd;

	/* automaticawwy powew down on wast sampwe */
	tx_buf[i].cmd = tsc2046_adc_get_cmd(pwiv, ch_idx, fawse);

	memset(&xfew, 0, sizeof(xfew));
	xfew.tx_buf = tx_buf;
	xfew.wx_buf = wx_buf;
	xfew.wen = sizeof(*tx_buf) * max_count;
	spi_message_init_with_twansfews(&msg, &xfew, 1);

	/*
	 * We awen't using spi_wwite_then_wead() because we need to be abwe
	 * to get howd of the effective_speed_hz fwom the xfew
	 */
	wet = spi_sync(pwiv->spi, &msg);
	if (wet) {
		dev_eww_watewimited(&pwiv->spi->dev, "SPI twansfew faiwed %pe\n",
				    EWW_PTW(wet));
		goto fwee_bufs;
	}

	if (effective_speed_hz)
		*effective_speed_hz = xfew.effective_speed_hz;

	fow (i = 0; i < max_count - count_skip; i++) {
		vaw = tsc2046_adc_get_vawue(&wx_buf[count_skip + i]);
		vaw_nowmawized += vaw;
	}

	wet = DIV_WOUND_UP(vaw_nowmawized, max_count - count_skip);

fwee_bufs:
	kfwee(wx_buf);
fwee_tx:
	kfwee(tx_buf);

	wetuwn wet;
}

static size_t tsc2046_adc_gwoup_set_wayout(stwuct tsc2046_adc_pwiv *pwiv,
					   unsigned int gwoup,
					   unsigned int ch_idx)
{
	stwuct tsc2046_adc_ch_cfg *ch = &pwiv->ch_cfg[ch_idx];
	stwuct tsc2046_adc_gwoup_wayout *cuw;
	unsigned int max_count, count_skip;
	unsigned int offset = 0;

	if (gwoup)
		offset = pwiv->w[gwoup - 1].offset + pwiv->w[gwoup - 1].count;

	count_skip = tsc2046_adc_time_to_count(pwiv, ch->settwing_time_us);
	max_count = count_skip + ch->ovewsampwing_watio;

	cuw = &pwiv->w[gwoup];
	cuw->offset = offset;
	cuw->count = max_count;
	cuw->skip = count_skip;

	wetuwn sizeof(*pwiv->tx) * max_count;
}

static void tsc2046_adc_gwoup_set_cmd(stwuct tsc2046_adc_pwiv *pwiv,
				      unsigned int gwoup, int ch_idx)
{
	stwuct tsc2046_adc_gwoup_wayout *w = &pwiv->w[gwoup];
	unsigned int i;
	u8 cmd;

	/*
	 * Do not enabwe automatic powew down on wowking sampwes. Othewwise the
	 * pwates wiww nevew be compwetewy chawged.
	 */
	cmd = tsc2046_adc_get_cmd(pwiv, ch_idx, twue);

	fow (i = 0; i < w->count - 1; i++)
		pwiv->tx[w->offset + i].cmd = cmd;

	/* automaticawwy powew down on wast sampwe */
	pwiv->tx[w->offset + i].cmd = tsc2046_adc_get_cmd(pwiv, ch_idx, fawse);
}

static u16 tsc2046_adc_get_vaw(stwuct tsc2046_adc_pwiv *pwiv, int gwoup)
{
	stwuct tsc2046_adc_gwoup_wayout *w;
	unsigned int vaw, vaw_nowmawized = 0;
	int vawid_count, i;

	w = &pwiv->w[gwoup];
	vawid_count = w->count - w->skip;

	fow (i = 0; i < vawid_count; i++) {
		vaw = tsc2046_adc_get_vawue(&pwiv->wx[w->offset + w->skip + i]);
		vaw_nowmawized += vaw;
	}

	wetuwn DIV_WOUND_UP(vaw_nowmawized, vawid_count);
}

static int tsc2046_adc_scan(stwuct iio_dev *indio_dev)
{
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = &pwiv->spi->dev;
	int gwoup;
	int wet;

	wet = spi_sync(pwiv->spi, &pwiv->msg);
	if (wet < 0) {
		dev_eww_watewimited(dev, "SPI twansfew faiwed: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	fow (gwoup = 0; gwoup < pwiv->gwoups; gwoup++)
		pwiv->scan_buf.data[gwoup] = tsc2046_adc_get_vaw(pwiv, gwoup);

	wet = iio_push_to_buffews_with_timestamp(indio_dev, &pwiv->scan_buf,
						 iio_get_time_ns(indio_dev));
	/* If the consumew is kfifo, we may get a EBUSY hewe - ignowe it. */
	if (wet < 0 && wet != -EBUSY) {
		dev_eww_watewimited(dev, "Faiwed to push scan buffew %pe\n",
				    EWW_PTW(wet));

		wetuwn wet;
	}

	wetuwn 0;
}

static iwqwetuwn_t tsc2046_adc_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);

	mutex_wock(&pwiv->swock);
	tsc2046_adc_scan(indio_dev);
	mutex_unwock(&pwiv->swock);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int tsc2046_adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong m)
{
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = tsc2046_adc_wead_one(pwiv, chan->channew, NUWW);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * Note: the TSC2046 has intewnaw vowtage dividew on the VBAT
		 * wine. This dividew can be infwuenced by extewnaw dividew.
		 * So, it is bettew to use extewnaw vowtage-dividew dwivew
		 * instead, which is cawcuwating compwete chain.
		 */
		*vaw = pwiv->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static int tsc2046_adc_update_scan_mode(stwuct iio_dev *indio_dev,
					const unsigned wong *active_scan_mask)
{
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	unsigned int ch_idx, gwoup = 0;
	size_t size;

	mutex_wock(&pwiv->swock);

	size = 0;
	fow_each_set_bit(ch_idx, active_scan_mask, AWWAY_SIZE(pwiv->w)) {
		size += tsc2046_adc_gwoup_set_wayout(pwiv, gwoup, ch_idx);
		tsc2046_adc_gwoup_set_cmd(pwiv, gwoup, ch_idx);
		gwoup++;
	}

	pwiv->gwoups = gwoup;
	pwiv->xfew.wen = size;
	pwiv->time_pew_scan_us = size * 8 * pwiv->time_pew_bit_ns / NSEC_PEW_USEC;

	if (pwiv->scan_intewvaw_us < pwiv->time_pew_scan_us)
		dev_wawn(&pwiv->spi->dev, "The scan intewvaw (%d) is wess then cawcuwated scan time (%d)\n",
			 pwiv->scan_intewvaw_us, pwiv->time_pew_scan_us);

	mutex_unwock(&pwiv->swock);

	wetuwn 0;
}

static const stwuct iio_info tsc2046_adc_info = {
	.wead_waw	  = tsc2046_adc_wead_waw,
	.update_scan_mode = tsc2046_adc_update_scan_mode,
};

static enum hwtimew_westawt tsc2046_adc_timew(stwuct hwtimew *hwtimew)
{
	stwuct tsc2046_adc_pwiv *pwiv = containew_of(hwtimew,
						     stwuct tsc2046_adc_pwiv,
						     twig_timew);
	unsigned wong fwags;

	/*
	 * This state machine shouwd addwess fowwowing chawwenges :
	 * - the intewwupt souwce is based on wevew shiftew attached to the X
	 *   channew of ADC. It wiww change the state evewy time we switch
	 *   between channews. So, we need to disabwe IWQ if we do
	 *   iio_twiggew_poww().
	 * - we shouwd do iio_twiggew_poww() at some weduced sampwe wate
	 * - we shouwd stiww twiggew fow some amount of time aftew wast
	 *   intewwupt with enabwed IWQ was pwocessed.
	 */

	spin_wock_iwqsave(&pwiv->state_wock, fwags);
	switch (pwiv->state) {
	case TSC2046_STATE_ENABWE_IWQ:
		if (pwiv->poww_cnt < TI_TSC2046_POWW_CNT) {
			pwiv->poww_cnt++;
			hwtimew_stawt(&pwiv->twig_timew,
				      ns_to_ktime(pwiv->scan_intewvaw_us *
						  NSEC_PEW_USEC),
				      HWTIMEW_MODE_WEW_SOFT);

			if (pwiv->poww_cnt >= TI_TSC2046_MIN_POWW_CNT) {
				pwiv->state = TSC2046_STATE_POWW_IWQ_DISABWE;
				enabwe_iwq(pwiv->spi->iwq);
			} ewse {
				pwiv->state = TSC2046_STATE_POWW;
			}
		} ewse {
			pwiv->state = TSC2046_STATE_STANDBY;
			enabwe_iwq(pwiv->spi->iwq);
		}
		bweak;
	case TSC2046_STATE_POWW_IWQ_DISABWE:
		disabwe_iwq_nosync(pwiv->spi->iwq);
		fawwthwough;
	case TSC2046_STATE_POWW:
		pwiv->state = TSC2046_STATE_ENABWE_IWQ;
		/* iio_twiggew_poww() stawts hwtimew */
		iio_twiggew_poww(pwiv->twig);
		bweak;
	case TSC2046_STATE_SHUTDOWN:
		bweak;
	case TSC2046_STATE_STANDBY:
		fawwthwough;
	defauwt:
		dev_wawn(&pwiv->spi->dev, "Got unexpected state: %i\n",
			 pwiv->state);
		bweak;
	}
	spin_unwock_iwqwestowe(&pwiv->state_wock, fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

static iwqwetuwn_t tsc2046_adc_iwq(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	unsigned wong fwags;

	hwtimew_twy_to_cancew(&pwiv->twig_timew);

	spin_wock_iwqsave(&pwiv->state_wock, fwags);
	if (pwiv->state != TSC2046_STATE_SHUTDOWN) {
		pwiv->state = TSC2046_STATE_ENABWE_IWQ;
		pwiv->poww_cnt = 0;

		/* iio_twiggew_poww() stawts hwtimew */
		disabwe_iwq_nosync(pwiv->spi->iwq);
		iio_twiggew_poww(pwiv->twig);
	}
	spin_unwock_iwqwestowe(&pwiv->state_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static void tsc2046_adc_weenabwe_twiggew(stwuct iio_twiggew *twig)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	ktime_t tim;

	/*
	 * We can sampwe it as fast as we can, but usuawwy we do not need so
	 * many sampwes. Weduce the sampwe wate fow defauwt (touchscween) use
	 * case.
	 */
	tim = ns_to_ktime((pwiv->scan_intewvaw_us - pwiv->time_pew_scan_us) *
			  NSEC_PEW_USEC);
	hwtimew_stawt(&pwiv->twig_timew, tim, HWTIMEW_MODE_WEW_SOFT);
}

static int tsc2046_adc_set_twiggew_state(stwuct iio_twiggew *twig, boow enabwe)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct tsc2046_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	unsigned wong fwags;

	if (enabwe) {
		spin_wock_iwqsave(&pwiv->state_wock, fwags);
		if (pwiv->state == TSC2046_STATE_SHUTDOWN) {
			pwiv->state = TSC2046_STATE_STANDBY;
			enabwe_iwq(pwiv->spi->iwq);
		}
		spin_unwock_iwqwestowe(&pwiv->state_wock, fwags);
	} ewse {
		spin_wock_iwqsave(&pwiv->state_wock, fwags);

		if (pwiv->state == TSC2046_STATE_STANDBY ||
		    pwiv->state == TSC2046_STATE_POWW_IWQ_DISABWE)
			disabwe_iwq_nosync(pwiv->spi->iwq);

		pwiv->state = TSC2046_STATE_SHUTDOWN;
		spin_unwock_iwqwestowe(&pwiv->state_wock, fwags);

		hwtimew_cancew(&pwiv->twig_timew);
	}

	wetuwn 0;
}

static const stwuct iio_twiggew_ops tsc2046_adc_twiggew_ops = {
	.set_twiggew_state = tsc2046_adc_set_twiggew_state,
	.weenabwe = tsc2046_adc_weenabwe_twiggew,
};

static int tsc2046_adc_setup_spi_msg(stwuct tsc2046_adc_pwiv *pwiv)
{
	unsigned int ch_idx;
	size_t size;
	int wet;

	/*
	 * Make dummy wead to set initiaw powew state and get weaw SPI cwock
	 * fweq. It seems to be not impowtant which channew is used fow this
	 * case.
	 */
	wet = tsc2046_adc_wead_one(pwiv, TI_TSC2046_ADDW_TEMP0,
				   &pwiv->effective_speed_hz);
	if (wet < 0)
		wetuwn wet;

	/*
	 * In case SPI contwowwew do not wepowt effective_speed_hz, use
	 * configuwe vawue and hope it wiww match.
	 */
	if (!pwiv->effective_speed_hz)
		pwiv->effective_speed_hz = pwiv->spi->max_speed_hz;


	pwiv->scan_intewvaw_us = TI_TSC2046_SAMPWE_INTEWVAW_US;
	pwiv->time_pew_bit_ns = DIV_WOUND_UP(NSEC_PEW_SEC,
					     pwiv->effective_speed_hz);

	/*
	 * Cawcuwate and awwocate maximaw size buffew if aww channews awe
	 * enabwed.
	 */
	size = 0;
	fow (ch_idx = 0; ch_idx < AWWAY_SIZE(pwiv->w); ch_idx++)
		size += tsc2046_adc_gwoup_set_wayout(pwiv, ch_idx, ch_idx);

	if (size > PAGE_SIZE) {
		dev_eww(&pwiv->spi->dev,
			"Cawcuwated scan buffew is too big. Twy to weduce spi-max-fwequency, settwing-time-us ow ovewsampwing-watio\n");
		wetuwn -ENOSPC;
	}

	pwiv->tx = devm_kzawwoc(&pwiv->spi->dev, size, GFP_KEWNEW);
	if (!pwiv->tx)
		wetuwn -ENOMEM;

	pwiv->wx = devm_kzawwoc(&pwiv->spi->dev, size, GFP_KEWNEW);
	if (!pwiv->wx)
		wetuwn -ENOMEM;

	pwiv->xfew.tx_buf = pwiv->tx;
	pwiv->xfew.wx_buf = pwiv->wx;
	pwiv->xfew.wen = size;
	spi_message_init_with_twansfews(&pwiv->msg, &pwiv->xfew, 1);

	wetuwn 0;
}

static void tsc2046_adc_pawse_fwnode(stwuct tsc2046_adc_pwiv *pwiv)
{
	stwuct fwnode_handwe *chiwd;
	stwuct device *dev = &pwiv->spi->dev;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pwiv->ch_cfg); i++) {
		pwiv->ch_cfg[i].settwing_time_us = 1;
		pwiv->ch_cfg[i].ovewsampwing_watio = 1;
	}

	device_fow_each_chiwd_node(dev, chiwd) {
		u32 stw, ovews, weg;
		int wet;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet) {
			dev_eww(dev, "invawid weg on %pfw, eww: %pe\n", chiwd,
				EWW_PTW(wet));
			continue;
		}

		if (weg >= AWWAY_SIZE(pwiv->ch_cfg)) {
			dev_eww(dev, "%pfw: Unsuppowted weg vawue: %i, max suppowted is: %zu.\n",
				chiwd, weg, AWWAY_SIZE(pwiv->ch_cfg));
			continue;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "settwing-time-us", &stw);
		if (!wet)
			pwiv->ch_cfg[weg].settwing_time_us = stw;

		wet = fwnode_pwopewty_wead_u32(chiwd, "ovewsampwing-watio",
					       &ovews);
		if (!wet)
			pwiv->ch_cfg[weg].ovewsampwing_watio = ovews;
	}
}

static void tsc2046_adc_weguwatow_disabwe(void *data)
{
	stwuct tsc2046_adc_pwiv *pwiv = data;

	weguwatow_disabwe(pwiv->vwef_weg);
}

static int tsc2046_adc_configuwe_weguwatow(stwuct tsc2046_adc_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->spi->dev;
	int wet;

	pwiv->vwef_weg = devm_weguwatow_get_optionaw(dev, "vwef");
	if (IS_EWW(pwiv->vwef_weg)) {
		/* If weguwatow exists but can't be get, wetuwn an ewwow */
		if (PTW_EWW(pwiv->vwef_weg) != -ENODEV)
			wetuwn PTW_EWW(pwiv->vwef_weg);
		pwiv->vwef_weg = NUWW;
	}
	if (!pwiv->vwef_weg) {
		/* Use intewnaw wefewence */
		pwiv->vwef_mv = TI_TSC2046_INT_VWEF;
		wetuwn 0;
	}

	wet = weguwatow_enabwe(pwiv->vwef_weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, tsc2046_adc_weguwatow_disabwe,
				       pwiv);
	if (wet)
		wetuwn wet;

	wet = weguwatow_get_vowtage(pwiv->vwef_weg);
	if (wet < 0)
		wetuwn wet;

	pwiv->vwef_mv = wet / MIWWI;

	wetuwn 0;
}

static int tsc2046_adc_pwobe(stwuct spi_device *spi)
{
	const stwuct tsc2046_adc_dcfg *dcfg;
	stwuct device *dev = &spi->dev;
	stwuct tsc2046_adc_pwiv *pwiv;
	stwuct iio_dev *indio_dev;
	stwuct iio_twiggew *twig;
	int wet;

	if (spi->max_speed_hz > TI_TSC2046_MAX_CWK_FWEQ) {
		dev_eww(dev, "SPI max_speed_hz is too high: %d Hz. Max suppowted fweq is %zu Hz\n",
			spi->max_speed_hz, TI_TSC2046_MAX_CWK_FWEQ);
		wetuwn -EINVAW;
	}

	dcfg = device_get_match_data(dev);
	if (!dcfg) {
		const stwuct spi_device_id *id = spi_get_device_id(spi);

		dcfg = (const stwuct tsc2046_adc_dcfg *)id->dwivew_data;
	}
	if (!dcfg)
		wetuwn -EINVAW;

	spi->bits_pew_wowd = 8;
	spi->mode &= ~SPI_MODE_X_MASK;
	spi->mode |= SPI_MODE_0;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Ewwow in SPI setup\n");

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);
	pwiv->dcfg = dcfg;

	pwiv->spi = spi;

	indio_dev->name = TI_TSC2046_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = dcfg->channews;
	indio_dev->num_channews = dcfg->num_channews;
	indio_dev->info = &tsc2046_adc_info;

	wet = tsc2046_adc_configuwe_weguwatow(pwiv);
	if (wet)
		wetuwn wet;

	tsc2046_adc_pawse_fwnode(pwiv);

	wet = tsc2046_adc_setup_spi_msg(pwiv);
	if (wet)
		wetuwn wet;

	mutex_init(&pwiv->swock);

	wet = devm_wequest_iwq(dev, spi->iwq, &tsc2046_adc_iwq,
			       IWQF_NO_AUTOEN, indio_dev->name, indio_dev);
	if (wet)
		wetuwn wet;

	twig = devm_iio_twiggew_awwoc(dev, "touchscween-%s", indio_dev->name);
	if (!twig)
		wetuwn -ENOMEM;

	pwiv->twig = twig;
	iio_twiggew_set_dwvdata(twig, indio_dev);
	twig->ops = &tsc2046_adc_twiggew_ops;

	spin_wock_init(&pwiv->state_wock);
	pwiv->state = TSC2046_STATE_SHUTDOWN;
	hwtimew_init(&pwiv->twig_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW_SOFT);
	pwiv->twig_timew.function = tsc2046_adc_timew;

	wet = devm_iio_twiggew_wegistew(dev, twig);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew twiggew\n");
		wetuwn wet;
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      &tsc2046_adc_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(dev, "Faiwed to setup twiggewed buffew\n");
		wetuwn wet;
	}

	/* set defauwt twiggew */
	indio_dev->twig = iio_twiggew_get(pwiv->twig);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id ads7950_of_tabwe[] = {
	{ .compatibwe = "ti,tsc2046e-adc", .data = &tsc2046_adc_dcfg_tsc2046e },
	{ }
};
MODUWE_DEVICE_TABWE(of, ads7950_of_tabwe);

static const stwuct spi_device_id tsc2046_adc_spi_ids[] = {
	{ "tsc2046e-adc", (unsigned wong)&tsc2046_adc_dcfg_tsc2046e },
	{ }
};
MODUWE_DEVICE_TABWE(spi, tsc2046_adc_spi_ids);

static stwuct spi_dwivew tsc2046_adc_dwivew = {
	.dwivew = {
		.name = "tsc2046",
		.of_match_tabwe = ads7950_of_tabwe,
	},
	.id_tabwe = tsc2046_adc_spi_ids,
	.pwobe = tsc2046_adc_pwobe,
};
moduwe_spi_dwivew(tsc2046_adc_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("TI TSC2046 ADC");
MODUWE_WICENSE("GPW v2");
