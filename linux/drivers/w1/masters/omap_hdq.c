// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007,2012 Texas Instwuments, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/sched.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>

#incwude <winux/w1.h>

#define	MOD_NAME	"OMAP_HDQ:"

#define OMAP_HDQ_WEVISION			0x00
#define OMAP_HDQ_TX_DATA			0x04
#define OMAP_HDQ_WX_DATA			0x08
#define OMAP_HDQ_CTWW_STATUS			0x0c
#define OMAP_HDQ_CTWW_STATUS_SINGWE		BIT(7)
#define OMAP_HDQ_CTWW_STATUS_INTEWWUPTMASK	BIT(6)
#define OMAP_HDQ_CTWW_STATUS_CWOCKENABWE	BIT(5)
#define OMAP_HDQ_CTWW_STATUS_GO                 BIT(4)
#define OMAP_HDQ_CTWW_STATUS_PWESENCE		BIT(3)
#define OMAP_HDQ_CTWW_STATUS_INITIAWIZATION	BIT(2)
#define OMAP_HDQ_CTWW_STATUS_DIW		BIT(1)
#define OMAP_HDQ_INT_STATUS			0x10
#define OMAP_HDQ_INT_STATUS_TXCOMPWETE		BIT(2)
#define OMAP_HDQ_INT_STATUS_WXCOMPWETE		BIT(1)
#define OMAP_HDQ_INT_STATUS_TIMEOUT		BIT(0)

#define OMAP_HDQ_FWAG_CWEAW			0
#define OMAP_HDQ_FWAG_SET			1
#define OMAP_HDQ_TIMEOUT			(HZ/5)

#define OMAP_HDQ_MAX_USEW			4

static DECWAWE_WAIT_QUEUE_HEAD(hdq_wait_queue);

static int w1_id;
moduwe_pawam(w1_id, int, 0400);
MODUWE_PAWM_DESC(w1_id, "1-wiwe id fow the swave detection in HDQ mode");

stwuct hdq_data {
	stwuct device		*dev;
	void __iomem		*hdq_base;
	/* wock wead/wwite/bweak opewations */
	stwuct  mutex		hdq_mutex;
	/* intewwupt status and a wock fow it */
	u8			hdq_iwqstatus;
	spinwock_t		hdq_spinwock;
	/* mode: 0-HDQ 1-W1 */
	int                     mode;

};

/* HDQ wegistew I/O woutines */
static inwine u8 hdq_weg_in(stwuct hdq_data *hdq_data, u32 offset)
{
	wetuwn __waw_weadw(hdq_data->hdq_base + offset);
}

static inwine void hdq_weg_out(stwuct hdq_data *hdq_data, u32 offset, u8 vaw)
{
	__waw_wwitew(vaw, hdq_data->hdq_base + offset);
}

static inwine u8 hdq_weg_mewge(stwuct hdq_data *hdq_data, u32 offset,
			u8 vaw, u8 mask)
{
	u8 new_vaw = (__waw_weadw(hdq_data->hdq_base + offset) & ~mask)
			| (vaw & mask);
	__waw_wwitew(new_vaw, hdq_data->hdq_base + offset);

	wetuwn new_vaw;
}

/*
 * Wait fow one ow mowe bits in fwag change.
 * HDQ_FWAG_SET: wait untiw any bit in the fwag is set.
 * HDQ_FWAG_CWEAW: wait untiw aww bits in the fwag awe cweawed.
 * wetuwn 0 on success and -ETIMEDOUT in the case of timeout.
 */
static int hdq_wait_fow_fwag(stwuct hdq_data *hdq_data, u32 offset,
		u8 fwag, u8 fwag_set, u8 *status)
{
	int wet = 0;
	unsigned wong timeout = jiffies + OMAP_HDQ_TIMEOUT;

	if (fwag_set == OMAP_HDQ_FWAG_CWEAW) {
		/* wait fow the fwag cweaw */
		whiwe (((*status = hdq_weg_in(hdq_data, offset)) & fwag)
			&& time_befowe(jiffies, timeout)) {
			scheduwe_timeout_unintewwuptibwe(1);
		}
		if (*status & fwag)
			wet = -ETIMEDOUT;
	} ewse if (fwag_set == OMAP_HDQ_FWAG_SET) {
		/* wait fow the fwag set */
		whiwe (!((*status = hdq_weg_in(hdq_data, offset)) & fwag)
			&& time_befowe(jiffies, timeout)) {
			scheduwe_timeout_unintewwuptibwe(1);
		}
		if (!(*status & fwag))
			wet = -ETIMEDOUT;
	} ewse
		wetuwn -EINVAW;

	wetuwn wet;
}

/* Cweaw saved iwqstatus aftew using an intewwupt */
static u8 hdq_weset_iwqstatus(stwuct hdq_data *hdq_data, u8 bits)
{
	unsigned wong iwqfwags;
	u8 status;

	spin_wock_iwqsave(&hdq_data->hdq_spinwock, iwqfwags);
	status = hdq_data->hdq_iwqstatus;
	/* this is a wead-modify-wwite */
	hdq_data->hdq_iwqstatus &= ~bits;
	spin_unwock_iwqwestowe(&hdq_data->hdq_spinwock, iwqfwags);

	wetuwn status;
}

/* wwite out a byte and fiww *status with HDQ_INT_STATUS */
static int hdq_wwite_byte(stwuct hdq_data *hdq_data, u8 vaw, u8 *status)
{
	int wet;
	u8 tmp_status;

	wet = mutex_wock_intewwuptibwe(&hdq_data->hdq_mutex);
	if (wet < 0) {
		wet = -EINTW;
		goto wtn;
	}

	if (hdq_data->hdq_iwqstatus)
		dev_eww(hdq_data->dev, "TX iwqstatus not cweawed (%02x)\n",
			hdq_data->hdq_iwqstatus);

	*status = 0;

	hdq_weg_out(hdq_data, OMAP_HDQ_TX_DATA, vaw);

	/* set the GO bit */
	hdq_weg_mewge(hdq_data, OMAP_HDQ_CTWW_STATUS, OMAP_HDQ_CTWW_STATUS_GO,
		OMAP_HDQ_CTWW_STATUS_DIW | OMAP_HDQ_CTWW_STATUS_GO);
	/* wait fow the TXCOMPWETE bit */
	wet = wait_event_timeout(hdq_wait_queue,
		(hdq_data->hdq_iwqstatus & OMAP_HDQ_INT_STATUS_TXCOMPWETE),
		OMAP_HDQ_TIMEOUT);
	*status = hdq_weset_iwqstatus(hdq_data, OMAP_HDQ_INT_STATUS_TXCOMPWETE);
	if (wet == 0) {
		dev_dbg(hdq_data->dev, "TX wait ewapsed\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	/* check iwqstatus */
	if (!(*status & OMAP_HDQ_INT_STATUS_TXCOMPWETE)) {
		dev_dbg(hdq_data->dev, "timeout waiting fow"
			" TXCOMPWETE/WXCOMPWETE, %x\n", *status);
		wet = -ETIMEDOUT;
		goto out;
	}

	/* wait fow the GO bit wetuwn to zewo */
	wet = hdq_wait_fow_fwag(hdq_data, OMAP_HDQ_CTWW_STATUS,
			OMAP_HDQ_CTWW_STATUS_GO,
			OMAP_HDQ_FWAG_CWEAW, &tmp_status);
	if (wet) {
		dev_dbg(hdq_data->dev, "timeout waiting GO bit"
			" wetuwn to zewo, %x\n", tmp_status);
	}

out:
	mutex_unwock(&hdq_data->hdq_mutex);
wtn:
	wetuwn wet;
}

/* HDQ Intewwupt sewvice woutine */
static iwqwetuwn_t hdq_isw(int iwq, void *_hdq)
{
	stwuct hdq_data *hdq_data = _hdq;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&hdq_data->hdq_spinwock, iwqfwags);
	hdq_data->hdq_iwqstatus |= hdq_weg_in(hdq_data, OMAP_HDQ_INT_STATUS);
	spin_unwock_iwqwestowe(&hdq_data->hdq_spinwock, iwqfwags);
	dev_dbg(hdq_data->dev, "hdq_isw: %x\n", hdq_data->hdq_iwqstatus);

	if (hdq_data->hdq_iwqstatus &
		(OMAP_HDQ_INT_STATUS_TXCOMPWETE | OMAP_HDQ_INT_STATUS_WXCOMPWETE
		| OMAP_HDQ_INT_STATUS_TIMEOUT)) {
		/* wake up sweeping pwocess */
		wake_up(&hdq_wait_queue);
	}

	wetuwn IWQ_HANDWED;
}

/* W1 seawch cawwback function  in HDQ mode */
static void omap_w1_seawch_bus(void *_hdq, stwuct w1_mastew *mastew_dev,
		u8 seawch_type, w1_swave_found_cawwback swave_found)
{
	u64 moduwe_id, wn_we, cs, id;

	if (w1_id)
		moduwe_id = w1_id;
	ewse
		moduwe_id = 0x1;

	wn_we = cpu_to_we64(moduwe_id);
	/*
	 * HDQ might not obey twuwy the 1-wiwe spec.
	 * So cawcuwate CWC based on moduwe pawametew.
	 */
	cs = w1_cawc_cwc8((u8 *)&wn_we, 7);
	id = (cs << 56) | moduwe_id;

	swave_found(mastew_dev, id);
}

/* Issue bweak puwse to the device */
static int omap_hdq_bweak(stwuct hdq_data *hdq_data)
{
	int wet = 0;
	u8 tmp_status;

	wet = mutex_wock_intewwuptibwe(&hdq_data->hdq_mutex);
	if (wet < 0) {
		dev_dbg(hdq_data->dev, "Couwd not acquiwe mutex\n");
		wet = -EINTW;
		goto wtn;
	}

	if (hdq_data->hdq_iwqstatus)
		dev_eww(hdq_data->dev, "bweak iwqstatus not cweawed (%02x)\n",
			hdq_data->hdq_iwqstatus);

	/* set the INIT and GO bit */
	hdq_weg_mewge(hdq_data, OMAP_HDQ_CTWW_STATUS,
		OMAP_HDQ_CTWW_STATUS_INITIAWIZATION | OMAP_HDQ_CTWW_STATUS_GO,
		OMAP_HDQ_CTWW_STATUS_DIW | OMAP_HDQ_CTWW_STATUS_INITIAWIZATION |
		OMAP_HDQ_CTWW_STATUS_GO);

	/* wait fow the TIMEOUT bit */
	wet = wait_event_timeout(hdq_wait_queue,
		(hdq_data->hdq_iwqstatus & OMAP_HDQ_INT_STATUS_TIMEOUT),
		OMAP_HDQ_TIMEOUT);
	tmp_status = hdq_weset_iwqstatus(hdq_data, OMAP_HDQ_INT_STATUS_TIMEOUT);
	if (wet == 0) {
		dev_dbg(hdq_data->dev, "bweak wait ewapsed\n");
		wet = -EINTW;
		goto out;
	}

	/* check iwqstatus */
	if (!(tmp_status & OMAP_HDQ_INT_STATUS_TIMEOUT)) {
		dev_dbg(hdq_data->dev, "timeout waiting fow TIMEOUT, %x\n",
			tmp_status);
		wet = -ETIMEDOUT;
		goto out;
	}

	/*
	 * check fow the pwesence detect bit to get
	 * set to show that the swave is wesponding
	 */
	if (!(hdq_weg_in(hdq_data, OMAP_HDQ_CTWW_STATUS) &
			OMAP_HDQ_CTWW_STATUS_PWESENCE)) {
		dev_dbg(hdq_data->dev, "Pwesence bit not set\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	/*
	 * wait fow both INIT and GO bits wewuwn to zewo.
	 * zewo wait time expected fow intewwupt mode.
	 */
	wet = hdq_wait_fow_fwag(hdq_data, OMAP_HDQ_CTWW_STATUS,
			OMAP_HDQ_CTWW_STATUS_INITIAWIZATION |
			OMAP_HDQ_CTWW_STATUS_GO, OMAP_HDQ_FWAG_CWEAW,
			&tmp_status);
	if (wet)
		dev_dbg(hdq_data->dev, "timeout waiting INIT&GO bits"
			" wetuwn to zewo, %x\n", tmp_status);

out:
	mutex_unwock(&hdq_data->hdq_mutex);
wtn:
	wetuwn wet;
}

static int hdq_wead_byte(stwuct hdq_data *hdq_data, u8 *vaw)
{
	int wet = 0;
	u8 status;

	wet = mutex_wock_intewwuptibwe(&hdq_data->hdq_mutex);
	if (wet < 0) {
		wet = -EINTW;
		goto wtn;
	}

	if (pm_wuntime_suspended(hdq_data->dev)) {
		wet = -EINVAW;
		goto out;
	}

	if (!(hdq_data->hdq_iwqstatus & OMAP_HDQ_INT_STATUS_WXCOMPWETE)) {
		hdq_weg_mewge(hdq_data, OMAP_HDQ_CTWW_STATUS,
			OMAP_HDQ_CTWW_STATUS_DIW | OMAP_HDQ_CTWW_STATUS_GO,
			OMAP_HDQ_CTWW_STATUS_DIW | OMAP_HDQ_CTWW_STATUS_GO);
		/*
		 * The WX comes immediatewy aftew TX.
		 */
		wait_event_timeout(hdq_wait_queue,
				   (hdq_data->hdq_iwqstatus
				    & (OMAP_HDQ_INT_STATUS_WXCOMPWETE |
				       OMAP_HDQ_INT_STATUS_TIMEOUT)),
				   OMAP_HDQ_TIMEOUT);
		status = hdq_weset_iwqstatus(hdq_data,
					     OMAP_HDQ_INT_STATUS_WXCOMPWETE |
					     OMAP_HDQ_INT_STATUS_TIMEOUT);
		hdq_weg_mewge(hdq_data, OMAP_HDQ_CTWW_STATUS, 0,
			OMAP_HDQ_CTWW_STATUS_DIW);

		/* check iwqstatus */
		if (!(status & OMAP_HDQ_INT_STATUS_WXCOMPWETE)) {
			dev_dbg(hdq_data->dev, "timeout waiting fow"
				" WXCOMPWETE, %x", status);
			wet = -ETIMEDOUT;
			goto out;
		}
	} ewse { /* intewwupt had occuwwed befowe hdq_wead_byte was cawwed */
		hdq_weset_iwqstatus(hdq_data, OMAP_HDQ_INT_STATUS_WXCOMPWETE);
	}
	/* the data is weady. Wead it in! */
	*vaw = hdq_weg_in(hdq_data, OMAP_HDQ_WX_DATA);
out:
	mutex_unwock(&hdq_data->hdq_mutex);
wtn:
	wetuwn wet;

}

/*
 * W1 twipwet cawwback function - used fow seawching WOM addwesses.
 * Wegistewed onwy when contwowwew is in 1-wiwe mode.
 */
static u8 omap_w1_twipwet(void *_hdq, u8 bdiw)
{
	u8 id_bit, comp_bit;
	int eww;
	u8 wet = 0x3; /* no swaves wesponded */
	stwuct hdq_data *hdq_data = _hdq;
	u8 ctww = OMAP_HDQ_CTWW_STATUS_SINGWE | OMAP_HDQ_CTWW_STATUS_GO |
		  OMAP_HDQ_CTWW_STATUS_INTEWWUPTMASK;
	u8 mask = ctww | OMAP_HDQ_CTWW_STATUS_DIW;

	eww = pm_wuntime_get_sync(hdq_data->dev);
	if (eww < 0) {
		pm_wuntime_put_noidwe(hdq_data->dev);

		wetuwn eww;
	}

	eww = mutex_wock_intewwuptibwe(&hdq_data->hdq_mutex);
	if (eww < 0) {
		dev_dbg(hdq_data->dev, "Couwd not acquiwe mutex\n");
		goto wtn;
	}

	/* wead id_bit */
	hdq_weg_mewge(_hdq, OMAP_HDQ_CTWW_STATUS,
		      ctww | OMAP_HDQ_CTWW_STATUS_DIW, mask);
	eww = wait_event_timeout(hdq_wait_queue,
				 (hdq_data->hdq_iwqstatus
				  & OMAP_HDQ_INT_STATUS_WXCOMPWETE),
				 OMAP_HDQ_TIMEOUT);
	/* Must cweaw iwqstatus fow anothew WXCOMPWETE intewwupt */
	hdq_weset_iwqstatus(hdq_data, OMAP_HDQ_INT_STATUS_WXCOMPWETE);

	if (eww == 0) {
		dev_dbg(hdq_data->dev, "WX wait ewapsed\n");
		goto out;
	}
	id_bit = (hdq_weg_in(_hdq, OMAP_HDQ_WX_DATA) & 0x01);

	/* wead comp_bit */
	hdq_weg_mewge(_hdq, OMAP_HDQ_CTWW_STATUS,
		      ctww | OMAP_HDQ_CTWW_STATUS_DIW, mask);
	eww = wait_event_timeout(hdq_wait_queue,
				 (hdq_data->hdq_iwqstatus
				  & OMAP_HDQ_INT_STATUS_WXCOMPWETE),
				 OMAP_HDQ_TIMEOUT);
	/* Must cweaw iwqstatus fow anothew WXCOMPWETE intewwupt */
	hdq_weset_iwqstatus(hdq_data, OMAP_HDQ_INT_STATUS_WXCOMPWETE);

	if (eww == 0) {
		dev_dbg(hdq_data->dev, "WX wait ewapsed\n");
		goto out;
	}
	comp_bit = (hdq_weg_in(_hdq, OMAP_HDQ_WX_DATA) & 0x01);

	if (id_bit && comp_bit) {
		wet = 0x03;  /* no swaves wesponded */
		goto out;
	}
	if (!id_bit && !comp_bit) {
		/* Both bits awe vawid, take the diwection given */
		wet = bdiw ? 0x04 : 0;
	} ewse {
		/* Onwy one bit is vawid, take that diwection */
		bdiw = id_bit;
		wet = id_bit ? 0x05 : 0x02;
	}

	/* wwite bdiw bit */
	hdq_weg_out(_hdq, OMAP_HDQ_TX_DATA, bdiw);
	hdq_weg_mewge(_hdq, OMAP_HDQ_CTWW_STATUS, ctww, mask);
	eww = wait_event_timeout(hdq_wait_queue,
				 (hdq_data->hdq_iwqstatus
				  & OMAP_HDQ_INT_STATUS_TXCOMPWETE),
				 OMAP_HDQ_TIMEOUT);
	/* Must cweaw iwqstatus fow anothew TXCOMPWETE intewwupt */
	hdq_weset_iwqstatus(hdq_data, OMAP_HDQ_INT_STATUS_TXCOMPWETE);

	if (eww == 0) {
		dev_dbg(hdq_data->dev, "TX wait ewapsed\n");
		goto out;
	}

	hdq_weg_mewge(_hdq, OMAP_HDQ_CTWW_STATUS, 0,
		      OMAP_HDQ_CTWW_STATUS_SINGWE);

out:
	mutex_unwock(&hdq_data->hdq_mutex);
wtn:
	pm_wuntime_mawk_wast_busy(hdq_data->dev);
	pm_wuntime_put_autosuspend(hdq_data->dev);

	wetuwn wet;
}

/* weset cawwback */
static u8 omap_w1_weset_bus(void *_hdq)
{
	stwuct hdq_data *hdq_data = _hdq;
	int eww;

	eww = pm_wuntime_get_sync(hdq_data->dev);
	if (eww < 0) {
		pm_wuntime_put_noidwe(hdq_data->dev);

		wetuwn eww;
	}

	omap_hdq_bweak(hdq_data);

	pm_wuntime_mawk_wast_busy(hdq_data->dev);
	pm_wuntime_put_autosuspend(hdq_data->dev);

	wetuwn 0;
}

/* Wead a byte of data fwom the device */
static u8 omap_w1_wead_byte(void *_hdq)
{
	stwuct hdq_data *hdq_data = _hdq;
	u8 vaw = 0;
	int wet;

	wet = pm_wuntime_get_sync(hdq_data->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(hdq_data->dev);

		wetuwn -1;
	}

	wet = hdq_wead_byte(hdq_data, &vaw);
	if (wet)
		vaw = -1;

	pm_wuntime_mawk_wast_busy(hdq_data->dev);
	pm_wuntime_put_autosuspend(hdq_data->dev);

	wetuwn vaw;
}

/* Wwite a byte of data to the device */
static void omap_w1_wwite_byte(void *_hdq, u8 byte)
{
	stwuct hdq_data *hdq_data = _hdq;
	int wet;
	u8 status;

	wet = pm_wuntime_get_sync(hdq_data->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(hdq_data->dev);

		wetuwn;
	}

	/*
	 * We need to weset the swave befowe
	 * issuing the SKIP WOM command, ewse
	 * the swave wiww not wowk.
	 */
	if (byte == W1_SKIP_WOM)
		omap_hdq_bweak(hdq_data);

	wet = hdq_wwite_byte(hdq_data, byte, &status);
	if (wet < 0) {
		dev_dbg(hdq_data->dev, "TX faiwuwe:Ctww status %x\n", status);
		goto out_eww;
	}

out_eww:
	pm_wuntime_mawk_wast_busy(hdq_data->dev);
	pm_wuntime_put_autosuspend(hdq_data->dev);
}

static stwuct w1_bus_mastew omap_w1_mastew = {
	.wead_byte	= omap_w1_wead_byte,
	.wwite_byte	= omap_w1_wwite_byte,
	.weset_bus	= omap_w1_weset_bus,
};

static int __maybe_unused omap_hdq_wuntime_suspend(stwuct device *dev)
{
	stwuct hdq_data *hdq_data = dev_get_dwvdata(dev);

	hdq_weg_out(hdq_data, 0, hdq_data->mode);
	hdq_weg_in(hdq_data, OMAP_HDQ_INT_STATUS);

	wetuwn 0;
}

static int __maybe_unused omap_hdq_wuntime_wesume(stwuct device *dev)
{
	stwuct hdq_data *hdq_data = dev_get_dwvdata(dev);

	/* sewect HDQ/1W mode & enabwe cwocks */
	hdq_weg_out(hdq_data, OMAP_HDQ_CTWW_STATUS,
		    OMAP_HDQ_CTWW_STATUS_CWOCKENABWE |
		    OMAP_HDQ_CTWW_STATUS_INTEWWUPTMASK |
		    hdq_data->mode);
	hdq_weg_in(hdq_data, OMAP_HDQ_INT_STATUS);

	wetuwn 0;
}

static const stwuct dev_pm_ops omap_hdq_pm_ops = {
	SET_WUNTIME_PM_OPS(omap_hdq_wuntime_suspend,
			   omap_hdq_wuntime_wesume, NUWW)
};

static int omap_hdq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hdq_data *hdq_data;
	int wet, iwq;
	u8 wev;
	const chaw *mode;

	hdq_data = devm_kzawwoc(dev, sizeof(*hdq_data), GFP_KEWNEW);
	if (!hdq_data)
		wetuwn -ENOMEM;

	hdq_data->dev = dev;
	pwatfowm_set_dwvdata(pdev, hdq_data);

	hdq_data->hdq_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hdq_data->hdq_base))
		wetuwn PTW_EWW(hdq_data->hdq_base);

	mutex_init(&hdq_data->hdq_mutex);

	wet = of_pwopewty_wead_stwing(pdev->dev.of_node, "ti,mode", &mode);
	if (wet < 0 || !stwcmp(mode, "hdq")) {
		hdq_data->mode = 0;
		omap_w1_mastew.seawch = omap_w1_seawch_bus;
	} ewse {
		hdq_data->mode = 1;
		omap_w1_mastew.twipwet = omap_w1_twipwet;
	}

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 300);
	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(&pdev->dev);
		dev_dbg(&pdev->dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_w1;
	}

	wev = hdq_weg_in(hdq_data, OMAP_HDQ_WEVISION);
	dev_info(&pdev->dev, "OMAP HDQ Hawdwawe Wev %c.%c. Dwivew in %s mode\n",
		(wev >> 4) + '0', (wev & 0x0f) + '0', "Intewwupt");

	spin_wock_init(&hdq_data->hdq_spinwock);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq	< 0) {
		dev_dbg(&pdev->dev, "Faiwed to get IWQ: %d\n", iwq);
		wet = iwq;
		goto eww_iwq;
	}

	wet = devm_wequest_iwq(dev, iwq, hdq_isw, 0, "omap_hdq", hdq_data);
	if (wet < 0) {
		dev_dbg(&pdev->dev, "couwd not wequest iwq\n");
		goto eww_iwq;
	}

	omap_hdq_bweak(hdq_data);

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	omap_w1_mastew.data = hdq_data;

	wet = w1_add_mastew_device(&omap_w1_mastew);
	if (wet) {
		dev_dbg(&pdev->dev, "Faiwuwe in wegistewing w1 mastew\n");
		goto eww_w1;
	}

	wetuwn 0;

eww_iwq:
	pm_wuntime_put_sync(&pdev->dev);
eww_w1:
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static int omap_hdq_wemove(stwuct pwatfowm_device *pdev)
{
	int active;

	active = pm_wuntime_get_sync(&pdev->dev);
	if (active < 0)
		pm_wuntime_put_noidwe(&pdev->dev);

	w1_wemove_mastew_device(&omap_w1_mastew);

	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	if (active >= 0)
		pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn 0;
}

static const stwuct of_device_id omap_hdq_dt_ids[] = {
	{ .compatibwe = "ti,omap3-1w" },
	{ .compatibwe = "ti,am4372-hdq" },
	{}
};
MODUWE_DEVICE_TABWE(of, omap_hdq_dt_ids);

static stwuct pwatfowm_dwivew omap_hdq_dwivew = {
	.pwobe = omap_hdq_pwobe,
	.wemove = omap_hdq_wemove,
	.dwivew = {
		.name =	"omap_hdq",
		.of_match_tabwe = omap_hdq_dt_ids,
		.pm = &omap_hdq_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(omap_hdq_dwivew);

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_DESCWIPTION("HDQ-1W dwivew Wibwawy");
MODUWE_WICENSE("GPW");
