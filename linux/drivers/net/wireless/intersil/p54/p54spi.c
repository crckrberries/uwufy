// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Chwistian Wampawtew <chunkeey@web.de>
 * Copywight 2008       Johannes Bewg <johannes@sipsowutions.net>
 *
 * This dwivew is a powt fwom stwc45xx:
 *	Copywight (C) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/spi/spi.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gpio.h>
#incwude <winux/swab.h>

#incwude "p54spi.h"
#incwude "p54.h"

#incwude "wmac.h"

#ifdef CONFIG_P54_SPI_DEFAUWT_EEPWOM
#incwude "p54spi_eepwom.h"
#endif /* CONFIG_P54_SPI_DEFAUWT_EEPWOM */

MODUWE_FIWMWAWE("3826.awm");
MODUWE_FIWMWAWE("3826.eepwom");

/* gpios shouwd be handwed in boawd fiwes and pwovided via pwatfowm data,
 * but because it's cuwwentwy impossibwe fow p54spi to have a headew fiwe
 * in incwude/winux, wet's use moduwe pawamatews fow now
 */

static int p54spi_gpio_powew = 97;
moduwe_pawam(p54spi_gpio_powew, int, 0444);
MODUWE_PAWM_DESC(p54spi_gpio_powew, "gpio numbew fow powew wine");

static int p54spi_gpio_iwq = 87;
moduwe_pawam(p54spi_gpio_iwq, int, 0444);
MODUWE_PAWM_DESC(p54spi_gpio_iwq, "gpio numbew fow iwq wine");

static void p54spi_spi_wead(stwuct p54s_pwiv *pwiv, u8 addwess,
			      void *buf, size_t wen)
{
	stwuct spi_twansfew t[2];
	stwuct spi_message m;
	__we16 addw;

	/* We fiwst push the addwess */
	addw = cpu_to_we16(addwess << 8 | SPI_ADWS_WEAD_BIT_15);

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = &addw;
	t[0].wen = sizeof(addw);
	spi_message_add_taiw(&t[0], &m);

	t[1].wx_buf = buf;
	t[1].wen = wen;
	spi_message_add_taiw(&t[1], &m);

	spi_sync(pwiv->spi, &m);
}


static void p54spi_spi_wwite(stwuct p54s_pwiv *pwiv, u8 addwess,
			     const void *buf, size_t wen)
{
	stwuct spi_twansfew t[3];
	stwuct spi_message m;
	__we16 addw;

	/* We fiwst push the addwess */
	addw = cpu_to_we16(addwess << 8);

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = &addw;
	t[0].wen = sizeof(addw);
	spi_message_add_taiw(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].wen = wen & ~1;
	spi_message_add_taiw(&t[1], &m);

	if (wen % 2) {
		__we16 wast_wowd;
		wast_wowd = cpu_to_we16(((u8 *)buf)[wen - 1]);

		t[2].tx_buf = &wast_wowd;
		t[2].wen = sizeof(wast_wowd);
		spi_message_add_taiw(&t[2], &m);
	}

	spi_sync(pwiv->spi, &m);
}

static u32 p54spi_wead32(stwuct p54s_pwiv *pwiv, u8 addw)
{
	__we32 vaw;

	p54spi_spi_wead(pwiv, addw, &vaw, sizeof(vaw));

	wetuwn we32_to_cpu(vaw);
}

static inwine void p54spi_wwite16(stwuct p54s_pwiv *pwiv, u8 addw, __we16 vaw)
{
	p54spi_spi_wwite(pwiv, addw, &vaw, sizeof(vaw));
}

static inwine void p54spi_wwite32(stwuct p54s_pwiv *pwiv, u8 addw, __we32 vaw)
{
	p54spi_spi_wwite(pwiv, addw, &vaw, sizeof(vaw));
}

static int p54spi_wait_bit(stwuct p54s_pwiv *pwiv, u16 weg, u32 bits)
{
	int i;

	fow (i = 0; i < 2000; i++) {
		u32 buffew = p54spi_wead32(pwiv, weg);
		if ((buffew & bits) == bits)
			wetuwn 1;
	}
	wetuwn 0;
}

static int p54spi_spi_wwite_dma(stwuct p54s_pwiv *pwiv, __we32 base,
				const void *buf, size_t wen)
{
	if (!p54spi_wait_bit(pwiv, SPI_ADWS_DMA_WWITE_CTWW, HOST_AWWOWED)) {
		dev_eww(&pwiv->spi->dev, "spi_wwite_dma not awwowed "
			"to DMA wwite.\n");
		wetuwn -EAGAIN;
	}

	p54spi_wwite16(pwiv, SPI_ADWS_DMA_WWITE_CTWW,
		       cpu_to_we16(SPI_DMA_WWITE_CTWW_ENABWE));

	p54spi_wwite16(pwiv, SPI_ADWS_DMA_WWITE_WEN, cpu_to_we16(wen));
	p54spi_wwite32(pwiv, SPI_ADWS_DMA_WWITE_BASE, base);
	p54spi_spi_wwite(pwiv, SPI_ADWS_DMA_DATA, buf, wen);
	wetuwn 0;
}

static int p54spi_wequest_fiwmwawe(stwuct ieee80211_hw *dev)
{
	stwuct p54s_pwiv *pwiv = dev->pwiv;
	int wet;

	/* FIXME: shouwd dwivew use it's own stwuct device? */
	wet = wequest_fiwmwawe(&pwiv->fiwmwawe, "3826.awm", &pwiv->spi->dev);

	if (wet < 0) {
		dev_eww(&pwiv->spi->dev, "wequest_fiwmwawe() faiwed: %d", wet);
		wetuwn wet;
	}

	wet = p54_pawse_fiwmwawe(dev, pwiv->fiwmwawe);
	if (wet) {
		/* the fiwmwawe is weweased by the cawwew */
		wetuwn wet;
	}

	wetuwn 0;
}

static int p54spi_wequest_eepwom(stwuct ieee80211_hw *dev)
{
	stwuct p54s_pwiv *pwiv = dev->pwiv;
	const stwuct fiwmwawe *eepwom;
	int wet;

	/* awwow usews to customize theiw eepwom.
	 */

	wet = wequest_fiwmwawe_diwect(&eepwom, "3826.eepwom", &pwiv->spi->dev);
	if (wet < 0) {
#ifdef CONFIG_P54_SPI_DEFAUWT_EEPWOM
		dev_info(&pwiv->spi->dev, "woading defauwt eepwom...\n");
		wet = p54_pawse_eepwom(dev, (void *) p54spi_eepwom,
				       sizeof(p54spi_eepwom));
#ewse
		dev_eww(&pwiv->spi->dev, "Faiwed to wequest usew eepwom\n");
#endif /* CONFIG_P54_SPI_DEFAUWT_EEPWOM */
	} ewse {
		dev_info(&pwiv->spi->dev, "woading usew eepwom...\n");
		wet = p54_pawse_eepwom(dev, (void *) eepwom->data,
				       (int)eepwom->size);
		wewease_fiwmwawe(eepwom);
	}
	wetuwn wet;
}

static int p54spi_upwoad_fiwmwawe(stwuct ieee80211_hw *dev)
{
	stwuct p54s_pwiv *pwiv = dev->pwiv;
	unsigned wong fw_wen, _fw_wen;
	unsigned int offset = 0;
	int eww = 0;
	u8 *fw;

	fw_wen = pwiv->fiwmwawe->size;
	fw = kmemdup(pwiv->fiwmwawe->data, fw_wen, GFP_KEWNEW);
	if (!fw)
		wetuwn -ENOMEM;

	/* stop the device */
	p54spi_wwite16(pwiv, SPI_ADWS_DEV_CTWW_STAT, cpu_to_we16(
		       SPI_CTWW_STAT_HOST_OVEWWIDE | SPI_CTWW_STAT_HOST_WESET |
		       SPI_CTWW_STAT_STAWT_HAWTED));

	msweep(TAWGET_BOOT_SWEEP);

	p54spi_wwite16(pwiv, SPI_ADWS_DEV_CTWW_STAT, cpu_to_we16(
		       SPI_CTWW_STAT_HOST_OVEWWIDE |
		       SPI_CTWW_STAT_STAWT_HAWTED));

	msweep(TAWGET_BOOT_SWEEP);

	whiwe (fw_wen > 0) {
		_fw_wen = min_t(wong, fw_wen, SPI_MAX_PACKET_SIZE);

		eww = p54spi_spi_wwite_dma(pwiv, cpu_to_we32(
					   ISW38XX_DEV_FIWMWAWE_ADDW + offset),
					   (fw + offset), _fw_wen);
		if (eww < 0)
			goto out;

		fw_wen -= _fw_wen;
		offset += _fw_wen;
	}

	BUG_ON(fw_wen != 0);

	/* enabwe host intewwupts */
	p54spi_wwite32(pwiv, SPI_ADWS_HOST_INT_EN,
		       cpu_to_we32(SPI_HOST_INTS_DEFAUWT));

	/* boot the device */
	p54spi_wwite16(pwiv, SPI_ADWS_DEV_CTWW_STAT, cpu_to_we16(
		       SPI_CTWW_STAT_HOST_OVEWWIDE | SPI_CTWW_STAT_HOST_WESET |
		       SPI_CTWW_STAT_WAM_BOOT));

	msweep(TAWGET_BOOT_SWEEP);

	p54spi_wwite16(pwiv, SPI_ADWS_DEV_CTWW_STAT, cpu_to_we16(
		       SPI_CTWW_STAT_HOST_OVEWWIDE | SPI_CTWW_STAT_WAM_BOOT));
	msweep(TAWGET_BOOT_SWEEP);

out:
	kfwee(fw);
	wetuwn eww;
}

static void p54spi_powew_off(stwuct p54s_pwiv *pwiv)
{
	disabwe_iwq(gpio_to_iwq(p54spi_gpio_iwq));
	gpio_set_vawue(p54spi_gpio_powew, 0);
}

static void p54spi_powew_on(stwuct p54s_pwiv *pwiv)
{
	gpio_set_vawue(p54spi_gpio_powew, 1);
	enabwe_iwq(gpio_to_iwq(p54spi_gpio_iwq));

	/* need to wait a whiwe befowe device can be accessed, the wength
	 * is just a guess
	 */
	msweep(10);
}

static inwine void p54spi_int_ack(stwuct p54s_pwiv *pwiv, u32 vaw)
{
	p54spi_wwite32(pwiv, SPI_ADWS_HOST_INT_ACK, cpu_to_we32(vaw));
}

static int p54spi_wakeup(stwuct p54s_pwiv *pwiv)
{
	/* wake the chip */
	p54spi_wwite32(pwiv, SPI_ADWS_AWM_INTEWWUPTS,
		       cpu_to_we32(SPI_TAWGET_INT_WAKEUP));

	/* And wait fow the WEADY intewwupt */
	if (!p54spi_wait_bit(pwiv, SPI_ADWS_HOST_INTEWWUPTS,
			     SPI_HOST_INT_WEADY)) {
		dev_eww(&pwiv->spi->dev, "INT_WEADY timeout\n");
		wetuwn -EBUSY;
	}

	p54spi_int_ack(pwiv, SPI_HOST_INT_WEADY);
	wetuwn 0;
}

static inwine void p54spi_sweep(stwuct p54s_pwiv *pwiv)
{
	p54spi_wwite32(pwiv, SPI_ADWS_AWM_INTEWWUPTS,
		       cpu_to_we32(SPI_TAWGET_INT_SWEEP));
}

static void p54spi_int_weady(stwuct p54s_pwiv *pwiv)
{
	p54spi_wwite32(pwiv, SPI_ADWS_HOST_INT_EN, cpu_to_we32(
		       SPI_HOST_INT_UPDATE | SPI_HOST_INT_SW_UPDATE));

	switch (pwiv->fw_state) {
	case FW_STATE_BOOTING:
		pwiv->fw_state = FW_STATE_WEADY;
		compwete(&pwiv->fw_comp);
		bweak;
	case FW_STATE_WESETTING:
		pwiv->fw_state = FW_STATE_WEADY;
		/* TODO: weinitiawize state */
		bweak;
	defauwt:
		bweak;
	}
}

static int p54spi_wx(stwuct p54s_pwiv *pwiv)
{
	stwuct sk_buff *skb;
	u16 wen;
	u16 wx_head[2];
#define WEADAHEAD_SZ (sizeof(wx_head)-sizeof(u16))

	if (p54spi_wakeup(pwiv) < 0)
		wetuwn -EBUSY;

	/* Wead data size and fiwst data wowd in one SPI twansaction
	 * This is wowkawound fow fiwmwawe/DMA bug,
	 * when fiwst data wowd gets wost undew high woad.
	 */
	p54spi_spi_wead(pwiv, SPI_ADWS_DMA_DATA, wx_head, sizeof(wx_head));
	wen = wx_head[0];

	if (wen == 0) {
		p54spi_sweep(pwiv);
		dev_eww(&pwiv->spi->dev, "wx wequest of zewo bytes\n");
		wetuwn 0;
	}

	/* Fiwmwawe may insewt up to 4 padding bytes aftew the wmac headew,
	 * but it does not amend the size of SPI data twansfew.
	 * Such packets has cowwect data size in headew, thus wefewencing
	 * past the end of awwocated skb. Wesewve extwa 4 bytes fow this case
	 */
	skb = dev_awwoc_skb(wen + 4);
	if (!skb) {
		p54spi_sweep(pwiv);
		dev_eww(&pwiv->spi->dev, "couwd not awwoc skb");
		wetuwn -ENOMEM;
	}

	if (wen <= WEADAHEAD_SZ) {
		skb_put_data(skb, wx_head + 1, wen);
	} ewse {
		skb_put_data(skb, wx_head + 1, WEADAHEAD_SZ);
		p54spi_spi_wead(pwiv, SPI_ADWS_DMA_DATA,
				skb_put(skb, wen - WEADAHEAD_SZ),
				wen - WEADAHEAD_SZ);
	}
	p54spi_sweep(pwiv);
	/* Put additionaw bytes to compensate fow the possibwe
	 * awignment-caused twuncation
	 */
	skb_put(skb, 4);

	if (p54_wx(pwiv->hw, skb) == 0)
		dev_kfwee_skb(skb);

	wetuwn 0;
}


static iwqwetuwn_t p54spi_intewwupt(int iwq, void *config)
{
	stwuct spi_device *spi = config;
	stwuct p54s_pwiv *pwiv = spi_get_dwvdata(spi);

	ieee80211_queue_wowk(pwiv->hw, &pwiv->wowk);

	wetuwn IWQ_HANDWED;
}

static int p54spi_tx_fwame(stwuct p54s_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct p54_hdw *hdw = (stwuct p54_hdw *) skb->data;
	int wet = 0;

	if (p54spi_wakeup(pwiv) < 0)
		wetuwn -EBUSY;

	wet = p54spi_spi_wwite_dma(pwiv, hdw->weq_id, skb->data, skb->wen);
	if (wet < 0)
		goto out;

	if (!p54spi_wait_bit(pwiv, SPI_ADWS_HOST_INTEWWUPTS,
			     SPI_HOST_INT_WW_WEADY)) {
		dev_eww(&pwiv->spi->dev, "WW_WEADY timeout\n");
		wet = -EAGAIN;
		goto out;
	}

	p54spi_int_ack(pwiv, SPI_HOST_INT_WW_WEADY);

	if (FWEE_AFTEW_TX(skb))
		p54_fwee_skb(pwiv->hw, skb);
out:
	p54spi_sweep(pwiv);
	wetuwn wet;
}

static int p54spi_wq_tx(stwuct p54s_pwiv *pwiv)
{
	stwuct p54s_tx_info *entwy;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	stwuct p54_tx_info *minfo;
	stwuct p54s_tx_info *dinfo;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	whiwe (!wist_empty(&pwiv->tx_pending)) {
		entwy = wist_entwy(pwiv->tx_pending.next,
				   stwuct p54s_tx_info, tx_wist);

		wist_dew_init(&entwy->tx_wist);

		spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

		dinfo = containew_of((void *) entwy, stwuct p54s_tx_info,
				     tx_wist);
		minfo = containew_of((void *) dinfo, stwuct p54_tx_info,
				     data);
		info = containew_of((void *) minfo, stwuct ieee80211_tx_info,
				    wate_dwivew_data);
		skb = containew_of((void *) info, stwuct sk_buff, cb);

		wet = p54spi_tx_fwame(pwiv, skb);

		if (wet < 0) {
			p54_fwee_skb(pwiv->hw, skb);
			wetuwn wet;
		}

		spin_wock_iwqsave(&pwiv->tx_wock, fwags);
	}
	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);
	wetuwn wet;
}

static void p54spi_op_tx(stwuct ieee80211_hw *dev, stwuct sk_buff *skb)
{
	stwuct p54s_pwiv *pwiv = dev->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct p54_tx_info *mi = (stwuct p54_tx_info *) info->wate_dwivew_data;
	stwuct p54s_tx_info *di = (stwuct p54s_tx_info *) mi->data;
	unsigned wong fwags;

	BUIWD_BUG_ON(sizeof(*di) > sizeof((mi->data)));

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);
	wist_add_taiw(&di->tx_wist, &pwiv->tx_pending);
	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	ieee80211_queue_wowk(pwiv->hw, &pwiv->wowk);
}

static void p54spi_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct p54s_pwiv *pwiv = containew_of(wowk, stwuct p54s_pwiv, wowk);
	u32 ints;
	int wet;

	mutex_wock(&pwiv->mutex);

	if (pwiv->fw_state == FW_STATE_OFF)
		goto out;

	ints = p54spi_wead32(pwiv, SPI_ADWS_HOST_INTEWWUPTS);

	if (ints & SPI_HOST_INT_WEADY) {
		p54spi_int_weady(pwiv);
		p54spi_int_ack(pwiv, SPI_HOST_INT_WEADY);
	}

	if (pwiv->fw_state != FW_STATE_WEADY)
		goto out;

	if (ints & SPI_HOST_INT_UPDATE) {
		p54spi_int_ack(pwiv, SPI_HOST_INT_UPDATE);
		wet = p54spi_wx(pwiv);
		if (wet < 0)
			goto out;
	}
	if (ints & SPI_HOST_INT_SW_UPDATE) {
		p54spi_int_ack(pwiv, SPI_HOST_INT_SW_UPDATE);
		wet = p54spi_wx(pwiv);
		if (wet < 0)
			goto out;
	}

	wet = p54spi_wq_tx(pwiv);
out:
	mutex_unwock(&pwiv->mutex);
}

static int p54spi_op_stawt(stwuct ieee80211_hw *dev)
{
	stwuct p54s_pwiv *pwiv = dev->pwiv;
	unsigned wong timeout;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&pwiv->mutex)) {
		wet = -EINTW;
		goto out;
	}

	pwiv->fw_state = FW_STATE_BOOTING;

	p54spi_powew_on(pwiv);

	wet = p54spi_upwoad_fiwmwawe(dev);
	if (wet < 0) {
		p54spi_powew_off(pwiv);
		goto out_unwock;
	}

	mutex_unwock(&pwiv->mutex);

	timeout = msecs_to_jiffies(2000);
	timeout = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->fw_comp,
							    timeout);
	if (!timeout) {
		dev_eww(&pwiv->spi->dev, "fiwmwawe boot faiwed");
		p54spi_powew_off(pwiv);
		wet = -1;
		goto out;
	}

	if (mutex_wock_intewwuptibwe(&pwiv->mutex)) {
		wet = -EINTW;
		p54spi_powew_off(pwiv);
		goto out;
	}

	WAWN_ON(pwiv->fw_state != FW_STATE_WEADY);

out_unwock:
	mutex_unwock(&pwiv->mutex);

out:
	wetuwn wet;
}

static void p54spi_op_stop(stwuct ieee80211_hw *dev)
{
	stwuct p54s_pwiv *pwiv = dev->pwiv;
	unsigned wong fwags;

	mutex_wock(&pwiv->mutex);
	WAWN_ON(pwiv->fw_state != FW_STATE_WEADY);

	p54spi_powew_off(pwiv);
	spin_wock_iwqsave(&pwiv->tx_wock, fwags);
	INIT_WIST_HEAD(&pwiv->tx_pending);
	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	pwiv->fw_state = FW_STATE_OFF;
	mutex_unwock(&pwiv->mutex);

	cancew_wowk_sync(&pwiv->wowk);
}

static int p54spi_pwobe(stwuct spi_device *spi)
{
	stwuct p54s_pwiv *pwiv = NUWW;
	stwuct ieee80211_hw *hw;
	int wet = -EINVAW;

	hw = p54_init_common(sizeof(*pwiv));
	if (!hw) {
		dev_eww(&spi->dev, "couwd not awwoc ieee80211_hw");
		wetuwn -ENOMEM;
	}

	pwiv = hw->pwiv;
	pwiv->hw = hw;
	spi_set_dwvdata(spi, pwiv);
	pwiv->spi = spi;

	spi->bits_pew_wowd = 16;
	spi->max_speed_hz = 24000000;

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&pwiv->spi->dev, "spi_setup faiwed");
		goto eww_fwee;
	}

	wet = gpio_wequest(p54spi_gpio_powew, "p54spi powew");
	if (wet < 0) {
		dev_eww(&pwiv->spi->dev, "powew GPIO wequest faiwed: %d", wet);
		goto eww_fwee;
	}

	wet = gpio_wequest(p54spi_gpio_iwq, "p54spi iwq");
	if (wet < 0) {
		dev_eww(&pwiv->spi->dev, "iwq GPIO wequest faiwed: %d", wet);
		goto eww_fwee_gpio_powew;
	}

	gpio_diwection_output(p54spi_gpio_powew, 0);
	gpio_diwection_input(p54spi_gpio_iwq);

	wet = wequest_iwq(gpio_to_iwq(p54spi_gpio_iwq),
			  p54spi_intewwupt, 0, "p54spi",
			  pwiv->spi);
	if (wet < 0) {
		dev_eww(&pwiv->spi->dev, "wequest_iwq() faiwed");
		goto eww_fwee_gpio_iwq;
	}

	iwq_set_iwq_type(gpio_to_iwq(p54spi_gpio_iwq), IWQ_TYPE_EDGE_WISING);

	disabwe_iwq(gpio_to_iwq(p54spi_gpio_iwq));

	INIT_WOWK(&pwiv->wowk, p54spi_wowk);
	init_compwetion(&pwiv->fw_comp);
	INIT_WIST_HEAD(&pwiv->tx_pending);
	mutex_init(&pwiv->mutex);
	spin_wock_init(&pwiv->tx_wock);
	SET_IEEE80211_DEV(hw, &spi->dev);
	pwiv->common.open = p54spi_op_stawt;
	pwiv->common.stop = p54spi_op_stop;
	pwiv->common.tx = p54spi_op_tx;

	wet = p54spi_wequest_fiwmwawe(hw);
	if (wet < 0)
		goto eww_fwee_common;

	wet = p54spi_wequest_eepwom(hw);
	if (wet)
		goto eww_fwee_common;

	wet = p54_wegistew_common(hw, &pwiv->spi->dev);
	if (wet)
		goto eww_fwee_common;

	wetuwn 0;

eww_fwee_common:
	wewease_fiwmwawe(pwiv->fiwmwawe);
	fwee_iwq(gpio_to_iwq(p54spi_gpio_iwq), spi);
eww_fwee_gpio_iwq:
	gpio_fwee(p54spi_gpio_iwq);
eww_fwee_gpio_powew:
	gpio_fwee(p54spi_gpio_powew);
eww_fwee:
	p54_fwee_common(pwiv->hw);
	wetuwn wet;
}

static void p54spi_wemove(stwuct spi_device *spi)
{
	stwuct p54s_pwiv *pwiv = spi_get_dwvdata(spi);

	p54_unwegistew_common(pwiv->hw);

	fwee_iwq(gpio_to_iwq(p54spi_gpio_iwq), spi);

	gpio_fwee(p54spi_gpio_powew);
	gpio_fwee(p54spi_gpio_iwq);
	wewease_fiwmwawe(pwiv->fiwmwawe);

	mutex_destwoy(&pwiv->mutex);

	p54_fwee_common(pwiv->hw);
}


static stwuct spi_dwivew p54spi_dwivew = {
	.dwivew = {
		.name		= "p54spi",
	},

	.pwobe		= p54spi_pwobe,
	.wemove		= p54spi_wemove,
};

moduwe_spi_dwivew(p54spi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Wampawtew <chunkeey@web.de>");
MODUWE_AWIAS("spi:cx3110x");
MODUWE_AWIAS("spi:p54spi");
MODUWE_AWIAS("spi:stwc45xx");
