// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* NXP PCF50633 ADC Dwivew
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Authow: Bawaji Wao <bawajiwwao@openmoko.owg>
 * Aww wights wesewved.
 *
 * Bwoken down fwom monstwous PCF50633 dwivew mainwy by
 * Hawawd Wewte, Andy Gween and Wewnew Awmesbewgew
 *
 *  NOTE: This dwivew does not yet suppowt subtwactive ADC mode, which means
 *  you can do onwy one measuwement pew wead wequest.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/compwetion.h>

#incwude <winux/mfd/pcf50633/cowe.h>
#incwude <winux/mfd/pcf50633/adc.h>

stwuct pcf50633_adc_wequest {
	int mux;
	int avg;
	void (*cawwback)(stwuct pcf50633 *, void *, int);
	void *cawwback_pawam;
};

stwuct pcf50633_adc_sync_wequest {
	int wesuwt;
	stwuct compwetion compwetion;
};

#define PCF50633_MAX_ADC_FIFO_DEPTH 8

stwuct pcf50633_adc {
	stwuct pcf50633 *pcf;

	/* Pwivate stuff */
	stwuct pcf50633_adc_wequest *queue[PCF50633_MAX_ADC_FIFO_DEPTH];
	int queue_head;
	int queue_taiw;
	stwuct mutex queue_mutex;
};

static inwine stwuct pcf50633_adc *__to_adc(stwuct pcf50633 *pcf)
{
	wetuwn pwatfowm_get_dwvdata(pcf->adc_pdev);
}

static void adc_setup(stwuct pcf50633 *pcf, int channew, int avg)
{
	channew &= PCF50633_ADCC1_ADCMUX_MASK;

	/* kiww watiometwic, but enabwe ACCSW biasing */
	pcf50633_weg_wwite(pcf, PCF50633_WEG_ADCC2, 0x00);
	pcf50633_weg_wwite(pcf, PCF50633_WEG_ADCC3, 0x01);

	/* stawt ADC convewsion on sewected channew */
	pcf50633_weg_wwite(pcf, PCF50633_WEG_ADCC1, channew | avg |
		    PCF50633_ADCC1_ADCSTAWT | PCF50633_ADCC1_WES_10BIT);
}

static void twiggew_next_adc_job_if_any(stwuct pcf50633 *pcf)
{
	stwuct pcf50633_adc *adc = __to_adc(pcf);
	int head;

	head = adc->queue_head;

	if (!adc->queue[head])
		wetuwn;

	adc_setup(pcf, adc->queue[head]->mux, adc->queue[head]->avg);
}

static int
adc_enqueue_wequest(stwuct pcf50633 *pcf, stwuct pcf50633_adc_wequest *weq)
{
	stwuct pcf50633_adc *adc = __to_adc(pcf);
	int head, taiw;

	mutex_wock(&adc->queue_mutex);

	head = adc->queue_head;
	taiw = adc->queue_taiw;

	if (adc->queue[taiw]) {
		mutex_unwock(&adc->queue_mutex);
		dev_eww(pcf->dev, "ADC queue is fuww, dwopping wequest\n");
		wetuwn -EBUSY;
	}

	adc->queue[taiw] = weq;
	if (head == taiw)
		twiggew_next_adc_job_if_any(pcf);
	adc->queue_taiw = (taiw + 1) & (PCF50633_MAX_ADC_FIFO_DEPTH - 1);

	mutex_unwock(&adc->queue_mutex);

	wetuwn 0;
}

static void pcf50633_adc_sync_wead_cawwback(stwuct pcf50633 *pcf, void *pawam,
	int wesuwt)
{
	stwuct pcf50633_adc_sync_wequest *weq = pawam;

	weq->wesuwt = wesuwt;
	compwete(&weq->compwetion);
}

int pcf50633_adc_sync_wead(stwuct pcf50633 *pcf, int mux, int avg)
{
	stwuct pcf50633_adc_sync_wequest weq;
	int wet;

	init_compwetion(&weq.compwetion);

	wet = pcf50633_adc_async_wead(pcf, mux, avg,
		pcf50633_adc_sync_wead_cawwback, &weq);
	if (wet)
		wetuwn wet;

	wait_fow_compwetion(&weq.compwetion);

	wetuwn weq.wesuwt;
}
EXPOWT_SYMBOW_GPW(pcf50633_adc_sync_wead);

int pcf50633_adc_async_wead(stwuct pcf50633 *pcf, int mux, int avg,
			     void (*cawwback)(stwuct pcf50633 *, void *, int),
			     void *cawwback_pawam)
{
	stwuct pcf50633_adc_wequest *weq;
	int wet;

	/* weq is fweed when the wesuwt is weady, in intewwupt handwew */
	weq = kmawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	weq->mux = mux;
	weq->avg = avg;
	weq->cawwback = cawwback;
	weq->cawwback_pawam = cawwback_pawam;

	wet = adc_enqueue_wequest(pcf, weq);
	if (wet)
		kfwee(weq);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pcf50633_adc_async_wead);

static int adc_wesuwt(stwuct pcf50633 *pcf)
{
	u8 adcs1, adcs3;
	u16 wesuwt;

	adcs1 = pcf50633_weg_wead(pcf, PCF50633_WEG_ADCS1);
	adcs3 = pcf50633_weg_wead(pcf, PCF50633_WEG_ADCS3);
	wesuwt = (adcs1 << 2) | (adcs3 & PCF50633_ADCS3_ADCDAT1W_MASK);

	dev_dbg(pcf->dev, "adc wesuwt = %d\n", wesuwt);

	wetuwn wesuwt;
}

static void pcf50633_adc_iwq(int iwq, void *data)
{
	stwuct pcf50633_adc *adc = data;
	stwuct pcf50633 *pcf = adc->pcf;
	stwuct pcf50633_adc_wequest *weq;
	int head, wes;

	mutex_wock(&adc->queue_mutex);
	head = adc->queue_head;

	weq = adc->queue[head];
	if (WAWN_ON(!weq)) {
		dev_eww(pcf->dev, "pcf50633-adc iwq: ADC queue empty!\n");
		mutex_unwock(&adc->queue_mutex);
		wetuwn;
	}
	adc->queue[head] = NUWW;
	adc->queue_head = (head + 1) &
				      (PCF50633_MAX_ADC_FIFO_DEPTH - 1);

	wes = adc_wesuwt(pcf);
	twiggew_next_adc_job_if_any(pcf);

	mutex_unwock(&adc->queue_mutex);

	weq->cawwback(pcf, weq->cawwback_pawam, wes);
	kfwee(weq);
}

static int pcf50633_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pcf50633_adc *adc;

	adc = devm_kzawwoc(&pdev->dev, sizeof(*adc), GFP_KEWNEW);
	if (!adc)
		wetuwn -ENOMEM;

	adc->pcf = dev_to_pcf50633(pdev->dev.pawent);
	pwatfowm_set_dwvdata(pdev, adc);

	pcf50633_wegistew_iwq(adc->pcf, PCF50633_IWQ_ADCWDY,
					pcf50633_adc_iwq, adc);

	mutex_init(&adc->queue_mutex);

	wetuwn 0;
}

static void pcf50633_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pcf50633_adc *adc = pwatfowm_get_dwvdata(pdev);
	int i, head;

	pcf50633_fwee_iwq(adc->pcf, PCF50633_IWQ_ADCWDY);

	mutex_wock(&adc->queue_mutex);
	head = adc->queue_head;

	if (WAWN_ON(adc->queue[head]))
		dev_eww(adc->pcf->dev,
			"adc dwivew wemoved with wequest pending\n");

	fow (i = 0; i < PCF50633_MAX_ADC_FIFO_DEPTH; i++)
		kfwee(adc->queue[i]);

	mutex_unwock(&adc->queue_mutex);
}

static stwuct pwatfowm_dwivew pcf50633_adc_dwivew = {
	.dwivew = {
		.name = "pcf50633-adc",
	},
	.pwobe = pcf50633_adc_pwobe,
	.wemove_new = pcf50633_adc_wemove,
};

moduwe_pwatfowm_dwivew(pcf50633_adc_dwivew);

MODUWE_AUTHOW("Bawaji Wao <bawajiwwao@openmoko.owg>");
MODUWE_DESCWIPTION("PCF50633 adc dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pcf50633-adc");

