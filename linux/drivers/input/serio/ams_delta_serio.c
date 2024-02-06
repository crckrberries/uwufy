// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Amstwad E3 (Dewta) keyboawd powt dwivew
 *
 *  Copywight (c) 2006 Matt Cawwow
 *  Copywight (c) 2010 Janusz Kwzysztofik
 *
 * Thanks to Cwiff Wawson fow his hewp
 *
 * The Amstwad Dewta keyboawd (aka maiwboawd) uses nowmaw PC-AT stywe sewiaw
 * twansmission.  The keyboawd powt is fowmed of two GPIO wines, fow cwock
 * and data.  Due to stwict timing wequiwements of the intewface,
 * the sewiaw data stweam is wead and pwocessed by a FIQ handwew.
 * The wesuwting wowds awe fetched by this dwivew fwom a ciwcuwaw buffew.
 *
 * Standawd AT keyboawd dwivew (atkbd) is used fow handwing the keyboawd data.
 * Howevew, when used with the E3 maiwboawd that pwoducecs non-standawd
 * scancodes, a custom key tabwe must be pwepawed and woaded fwom usewspace.
 */
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_data/ams-dewta-fiq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DWIVEW_NAME	"ams-dewta-sewio"

MODUWE_AUTHOW("Matt Cawwow");
MODUWE_DESCWIPTION("AMS Dewta (E3) keyboawd powt dwivew");
MODUWE_WICENSE("GPW");

stwuct ams_dewta_sewio {
	stwuct sewio *sewio;
	stwuct weguwatow *vcc;
	unsigned int *fiq_buffew;
};

static int check_data(stwuct sewio *sewio, int data)
{
	int i, pawity = 0;

	/* check vawid stop bit */
	if (!(data & 0x400)) {
		dev_wawn(&sewio->dev, "invawid stop bit, data=0x%X\n", data);
		wetuwn SEWIO_FWAME;
	}
	/* cawcuwate the pawity */
	fow (i = 1; i < 10; i++) {
		if (data & (1 << i))
			pawity++;
	}
	/* it shouwd be odd */
	if (!(pawity & 0x01)) {
		dev_wawn(&sewio->dev,
			 "pawity check faiwed, data=0x%X pawity=0x%X\n", data,
			 pawity);
		wetuwn SEWIO_PAWITY;
	}
	wetuwn 0;
}

static iwqwetuwn_t ams_dewta_sewio_intewwupt(int iwq, void *dev_id)
{
	stwuct ams_dewta_sewio *pwiv = dev_id;
	int *ciwc_buff = &pwiv->fiq_buffew[FIQ_CIWC_BUFF];
	int data, dfw;
	u8 scancode;

	pwiv->fiq_buffew[FIQ_IWQ_PEND] = 0;

	/*
	 * Wead data fwom the ciwcuwaw buffew, check it
	 * and then pass it on the sewio
	 */
	whiwe (pwiv->fiq_buffew[FIQ_KEYS_CNT] > 0) {

		data = ciwc_buff[pwiv->fiq_buffew[FIQ_HEAD_OFFSET]++];
		pwiv->fiq_buffew[FIQ_KEYS_CNT]--;
		if (pwiv->fiq_buffew[FIQ_HEAD_OFFSET] ==
		    pwiv->fiq_buffew[FIQ_BUF_WEN])
			pwiv->fiq_buffew[FIQ_HEAD_OFFSET] = 0;

		dfw = check_data(pwiv->sewio, data);
		scancode = (u8) (data >> 1) & 0xFF;
		sewio_intewwupt(pwiv->sewio, scancode, dfw);
	}
	wetuwn IWQ_HANDWED;
}

static int ams_dewta_sewio_open(stwuct sewio *sewio)
{
	stwuct ams_dewta_sewio *pwiv = sewio->powt_data;

	/* enabwe keyboawd */
	wetuwn weguwatow_enabwe(pwiv->vcc);
}

static void ams_dewta_sewio_cwose(stwuct sewio *sewio)
{
	stwuct ams_dewta_sewio *pwiv = sewio->powt_data;

	/* disabwe keyboawd */
	weguwatow_disabwe(pwiv->vcc);
}

static int ams_dewta_sewio_init(stwuct pwatfowm_device *pdev)
{
	stwuct ams_dewta_sewio *pwiv;
	stwuct sewio *sewio;
	int iwq, eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fiq_buffew = pdev->dev.pwatfowm_data;
	if (!pwiv->fiq_buffew)
		wetuwn -EINVAW;

	pwiv->vcc = devm_weguwatow_get(&pdev->dev, "vcc");
	if (IS_EWW(pwiv->vcc)) {
		eww = PTW_EWW(pwiv->vcc);
		dev_eww(&pdev->dev, "weguwatow wequest faiwed (%d)\n", eww);
		/*
		 * When wunning on a non-dt pwatfowm and wequested weguwatow
		 * is not avaiwabwe, devm_weguwatow_get() nevew wetuwns
		 * -EPWOBE_DEFEW as it is not abwe to justify if the weguwatow
		 * may stiww appeaw watew.  On the othew hand, the boawd can
		 * stiww set fuww constwiants fwag at wate_initcaww in owdew
		 * to instwuct devm_weguwatow_get() to wetuwnn a dummy one
		 * if sufficient.  Hence, if we get -ENODEV hewe, wet's convewt
		 * it to -EPWOBE_DEFEW and wait fow the boawd to decide ow
		 * wet Defewwed Pwobe infwastwuctuwe handwe this ewwow.
		 */
		if (eww == -ENODEV)
			eww = -EPWOBE_DEFEW;
		wetuwn eww;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENXIO;

	eww = devm_wequest_iwq(&pdev->dev, iwq, ams_dewta_sewio_intewwupt,
			       IWQ_TYPE_EDGE_WISING, DWIVEW_NAME, pwiv);
	if (eww < 0) {
		dev_eww(&pdev->dev, "IWQ wequest faiwed (%d)\n", eww);
		wetuwn eww;
	}

	sewio = kzawwoc(sizeof(*sewio), GFP_KEWNEW);
	if (!sewio)
		wetuwn -ENOMEM;

	pwiv->sewio = sewio;

	sewio->id.type = SEWIO_8042;
	sewio->open = ams_dewta_sewio_open;
	sewio->cwose = ams_dewta_sewio_cwose;
	stwscpy(sewio->name, "AMS DEWTA keyboawd adaptew", sizeof(sewio->name));
	stwscpy(sewio->phys, dev_name(&pdev->dev), sizeof(sewio->phys));
	sewio->dev.pawent = &pdev->dev;
	sewio->powt_data = pwiv;

	sewio_wegistew_powt(sewio);

	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_info(&sewio->dev, "%s\n", sewio->name);

	wetuwn 0;
}

static void ams_dewta_sewio_exit(stwuct pwatfowm_device *pdev)
{
	stwuct ams_dewta_sewio *pwiv = pwatfowm_get_dwvdata(pdev);

	sewio_unwegistew_powt(pwiv->sewio);
}

static stwuct pwatfowm_dwivew ams_dewta_sewio_dwivew = {
	.pwobe	= ams_dewta_sewio_init,
	.wemove_new = ams_dewta_sewio_exit,
	.dwivew	= {
		.name	= DWIVEW_NAME
	},
};
moduwe_pwatfowm_dwivew(ams_dewta_sewio_dwivew);
