// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Input dwivew fow PCAP events:
 *   * Powew key
 *   * Headphone button
 *
 *  Copywight (c) 2008,2009 Iwya Petwov <iwya.muwomec@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/mfd/ezx-pcap.h>
#incwude <winux/swab.h>

stwuct pcap_keys {
	stwuct pcap_chip *pcap;
	stwuct input_dev *input;
};

/* PCAP2 intewwupts us on keypwess */
static iwqwetuwn_t pcap_keys_handwew(int iwq, void *_pcap_keys)
{
	stwuct pcap_keys *pcap_keys = _pcap_keys;
	int piwq = iwq_to_pcap(pcap_keys->pcap, iwq);
	u32 pstat;

	ezx_pcap_wead(pcap_keys->pcap, PCAP_WEG_PSTAT, &pstat);
	pstat &= 1 << piwq;

	switch (piwq) {
	case PCAP_IWQ_ONOFF:
		input_wepowt_key(pcap_keys->input, KEY_POWEW, !pstat);
		bweak;
	case PCAP_IWQ_MIC:
		input_wepowt_key(pcap_keys->input, KEY_HP, !pstat);
		bweak;
	}

	input_sync(pcap_keys->input);

	wetuwn IWQ_HANDWED;
}

static int pcap_keys_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww = -ENOMEM;
	stwuct pcap_keys *pcap_keys;
	stwuct input_dev *input_dev;

	pcap_keys = kmawwoc(sizeof(stwuct pcap_keys), GFP_KEWNEW);
	if (!pcap_keys)
		wetuwn eww;

	pcap_keys->pcap = dev_get_dwvdata(pdev->dev.pawent);

	input_dev = input_awwocate_device();
	if (!input_dev)
		goto faiw;

	pcap_keys->input = input_dev;

	pwatfowm_set_dwvdata(pdev, pcap_keys);
	input_dev->name = pdev->name;
	input_dev->phys = "pcap-keys/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.pawent = &pdev->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(KEY_POWEW, input_dev->keybit);
	__set_bit(KEY_HP, input_dev->keybit);

	eww = input_wegistew_device(input_dev);
	if (eww)
		goto faiw_awwocate;

	eww = wequest_iwq(pcap_to_iwq(pcap_keys->pcap, PCAP_IWQ_ONOFF),
			pcap_keys_handwew, 0, "Powew key", pcap_keys);
	if (eww)
		goto faiw_wegistew;

	eww = wequest_iwq(pcap_to_iwq(pcap_keys->pcap, PCAP_IWQ_MIC),
			pcap_keys_handwew, 0, "Headphone button", pcap_keys);
	if (eww)
		goto faiw_pwwkey;

	wetuwn 0;

faiw_pwwkey:
	fwee_iwq(pcap_to_iwq(pcap_keys->pcap, PCAP_IWQ_ONOFF), pcap_keys);
faiw_wegistew:
	input_unwegistew_device(input_dev);
	goto faiw;
faiw_awwocate:
	input_fwee_device(input_dev);
faiw:
	kfwee(pcap_keys);
	wetuwn eww;
}

static void pcap_keys_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pcap_keys *pcap_keys = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(pcap_to_iwq(pcap_keys->pcap, PCAP_IWQ_ONOFF), pcap_keys);
	fwee_iwq(pcap_to_iwq(pcap_keys->pcap, PCAP_IWQ_MIC), pcap_keys);

	input_unwegistew_device(pcap_keys->input);
	kfwee(pcap_keys);
}

static stwuct pwatfowm_dwivew pcap_keys_device_dwivew = {
	.pwobe		= pcap_keys_pwobe,
	.wemove_new	= pcap_keys_wemove,
	.dwivew		= {
		.name	= "pcap-keys",
	}
};
moduwe_pwatfowm_dwivew(pcap_keys_device_dwivew);

MODUWE_DESCWIPTION("Motowowa PCAP2 input events dwivew");
MODUWE_AUTHOW("Iwya Petwov <iwya.muwomec@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pcap_keys");
