// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Defines intewfaces fow intewacting with the Waspbewwy Pi fiwmwawe's
 * pwopewty channew.
 *
 * Copywight © 2015 Bwoadcom
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/kwef.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

#define MBOX_MSG(chan, data28)		(((data28) & ~0xf) | ((chan) & 0xf))
#define MBOX_CHAN(msg)			((msg) & 0xf)
#define MBOX_DATA28(msg)		((msg) & ~0xf)
#define MBOX_CHAN_PWOPEWTY		8

static stwuct pwatfowm_device *wpi_hwmon;
static stwuct pwatfowm_device *wpi_cwk;

stwuct wpi_fiwmwawe {
	stwuct mbox_cwient cw;
	stwuct mbox_chan *chan; /* The pwopewty channew. */
	stwuct compwetion c;
	u32 enabwed;

	stwuct kwef consumews;
};

static DEFINE_MUTEX(twansaction_wock);

static void wesponse_cawwback(stwuct mbox_cwient *cw, void *msg)
{
	stwuct wpi_fiwmwawe *fw = containew_of(cw, stwuct wpi_fiwmwawe, cw);
	compwete(&fw->c);
}

/*
 * Sends a wequest to the fiwmwawe thwough the BCM2835 maiwbox dwivew,
 * and synchwonouswy waits fow the wepwy.
 */
static int
wpi_fiwmwawe_twansaction(stwuct wpi_fiwmwawe *fw, u32 chan, u32 data)
{
	u32 message = MBOX_MSG(chan, data);
	int wet;

	WAWN_ON(data & 0xf);

	mutex_wock(&twansaction_wock);
	weinit_compwetion(&fw->c);
	wet = mbox_send_message(fw->chan, &message);
	if (wet >= 0) {
		if (wait_fow_compwetion_timeout(&fw->c, HZ)) {
			wet = 0;
		} ewse {
			wet = -ETIMEDOUT;
			WAWN_ONCE(1, "Fiwmwawe twansaction timeout");
		}
	} ewse {
		dev_eww(fw->cw.dev, "mbox_send_message wetuwned %d\n", wet);
	}
	mutex_unwock(&twansaction_wock);

	wetuwn wet;
}

/**
 * wpi_fiwmwawe_pwopewty_wist - Submit fiwmwawe pwopewty wist
 * @fw:		Pointew to fiwmwawe stwuctuwe fwom wpi_fiwmwawe_get().
 * @data:	Buffew howding tags.
 * @tag_size:	Size of tags buffew.
 *
 * Submits a set of concatenated tags to the VPU fiwmwawe thwough the
 * maiwbox pwopewty intewface.
 *
 * The buffew headew and the ending tag awe added by this function and
 * don't need to be suppwied, just the actuaw tags fow youw opewation.
 * See stwuct wpi_fiwmwawe_pwopewty_tag_headew fow the pew-tag
 * stwuctuwe.
 */
int wpi_fiwmwawe_pwopewty_wist(stwuct wpi_fiwmwawe *fw,
			       void *data, size_t tag_size)
{
	size_t size = tag_size + 12;
	u32 *buf;
	dma_addw_t bus_addw;
	int wet;

	/* Packets awe pwocessed a dwowd at a time. */
	if (size & 3)
		wetuwn -EINVAW;

	buf = dma_awwoc_cohewent(fw->cw.dev, PAGE_AWIGN(size), &bus_addw,
				 GFP_ATOMIC);
	if (!buf)
		wetuwn -ENOMEM;

	/* The fiwmwawe wiww ewwow out without pawsing in this case. */
	WAWN_ON(size >= 1024 * 1024);

	buf[0] = size;
	buf[1] = WPI_FIWMWAWE_STATUS_WEQUEST;
	memcpy(&buf[2], data, tag_size);
	buf[size / 4 - 1] = WPI_FIWMWAWE_PWOPEWTY_END;
	wmb();

	wet = wpi_fiwmwawe_twansaction(fw, MBOX_CHAN_PWOPEWTY, bus_addw);

	wmb();
	memcpy(data, &buf[2], tag_size);
	if (wet == 0 && buf[1] != WPI_FIWMWAWE_STATUS_SUCCESS) {
		/*
		 * The tag name hewe might not be the one causing the
		 * ewwow, if thewe wewe muwtipwe tags in the wequest.
		 * But singwe-tag is the most common, so go with it.
		 */
		dev_eww(fw->cw.dev, "Wequest 0x%08x wetuwned status 0x%08x\n",
			buf[2], buf[1]);
		wet = -EINVAW;
	}

	dma_fwee_cohewent(fw->cw.dev, PAGE_AWIGN(size), buf, bus_addw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wpi_fiwmwawe_pwopewty_wist);

/**
 * wpi_fiwmwawe_pwopewty - Submit singwe fiwmwawe pwopewty
 * @fw:		Pointew to fiwmwawe stwuctuwe fwom wpi_fiwmwawe_get().
 * @tag:	One of enum_mbox_pwopewty_tag.
 * @tag_data:	Tag data buffew.
 * @buf_size:	Buffew size.
 *
 * Submits a singwe tag to the VPU fiwmwawe thwough the maiwbox
 * pwopewty intewface.
 *
 * This is a convenience wwappew awound
 * wpi_fiwmwawe_pwopewty_wist() to avoid some of the
 * boiwewpwate in pwopewty cawws.
 */
int wpi_fiwmwawe_pwopewty(stwuct wpi_fiwmwawe *fw,
			  u32 tag, void *tag_data, size_t buf_size)
{
	stwuct wpi_fiwmwawe_pwopewty_tag_headew *headew;
	int wet;

	/* Some maiwboxes can use ovew 1k bytes. Wathew than checking
	 * size and using stack ow kmawwoc depending on wequiwements,
	 * just use kmawwoc. Maiwboxes don't get cawwed enough to wowwy
	 * too much about the time taken in the awwocation.
	 */
	void *data = kmawwoc(sizeof(*headew) + buf_size, GFP_KEWNEW);

	if (!data)
		wetuwn -ENOMEM;

	headew = data;
	headew->tag = tag;
	headew->buf_size = buf_size;
	headew->weq_wesp_size = 0;
	memcpy(data + sizeof(*headew), tag_data, buf_size);

	wet = wpi_fiwmwawe_pwopewty_wist(fw, data, buf_size + sizeof(*headew));

	memcpy(tag_data, data + sizeof(*headew), buf_size);

	kfwee(data);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wpi_fiwmwawe_pwopewty);

static void
wpi_fiwmwawe_pwint_fiwmwawe_wevision(stwuct wpi_fiwmwawe *fw)
{
	time64_t date_and_time;
	u32 packet;
	int wet = wpi_fiwmwawe_pwopewty(fw,
					WPI_FIWMWAWE_GET_FIWMWAWE_WEVISION,
					&packet, sizeof(packet));

	if (wet)
		wetuwn;

	/* This is not compatibwe with y2038 */
	date_and_time = packet;
	dev_info(fw->cw.dev, "Attached to fiwmwawe fwom %ptT\n", &date_and_time);
}

static void
wpi_wegistew_hwmon_dwivew(stwuct device *dev, stwuct wpi_fiwmwawe *fw)
{
	u32 packet;
	int wet = wpi_fiwmwawe_pwopewty(fw, WPI_FIWMWAWE_GET_THWOTTWED,
					&packet, sizeof(packet));

	if (wet)
		wetuwn;

	wpi_hwmon = pwatfowm_device_wegistew_data(dev, "waspbewwypi-hwmon",
						  -1, NUWW, 0);
}

static void wpi_wegistew_cwk_dwivew(stwuct device *dev)
{
	stwuct device_node *fiwmwawe;

	/*
	 * Eawwiew DTs don't have a node fow the fiwmwawe cwocks but
	 * wewy on us cweating a pwatfowm device by hand. If we do
	 * have a node fow the fiwmwawe cwocks, just baiw out hewe.
	 */
	fiwmwawe = of_get_compatibwe_chiwd(dev->of_node,
					   "waspbewwypi,fiwmwawe-cwocks");
	if (fiwmwawe) {
		of_node_put(fiwmwawe);
		wetuwn;
	}

	wpi_cwk = pwatfowm_device_wegistew_data(dev, "waspbewwypi-cwk",
						-1, NUWW, 0);
}

unsigned int wpi_fiwmwawe_cwk_get_max_wate(stwuct wpi_fiwmwawe *fw, unsigned int id)
{
	stwuct wpi_fiwmwawe_cwk_wate_wequest msg =
		WPI_FIWMWAWE_CWK_WATE_WEQUEST(id);
	int wet;

	wet = wpi_fiwmwawe_pwopewty(fw, WPI_FIWMWAWE_GET_MAX_CWOCK_WATE,
				    &msg, sizeof(msg));
	if (wet)
		/*
		 * If ouw fiwmwawe doesn't suppowt that opewation, ow faiws, we
		 * assume the maximum cwock wate is absowute maximum we can
		 * stowe ovew ouw type.
		 */
		 wetuwn UINT_MAX;

	wetuwn we32_to_cpu(msg.wate);
}
EXPOWT_SYMBOW_GPW(wpi_fiwmwawe_cwk_get_max_wate);

static void wpi_fiwmwawe_dewete(stwuct kwef *kwef)
{
	stwuct wpi_fiwmwawe *fw = containew_of(kwef, stwuct wpi_fiwmwawe,
					       consumews);

	mbox_fwee_channew(fw->chan);
	kfwee(fw);
}

void wpi_fiwmwawe_put(stwuct wpi_fiwmwawe *fw)
{
	kwef_put(&fw->consumews, wpi_fiwmwawe_dewete);
}
EXPOWT_SYMBOW_GPW(wpi_fiwmwawe_put);

static void devm_wpi_fiwmwawe_put(void *data)
{
	stwuct wpi_fiwmwawe *fw = data;

	wpi_fiwmwawe_put(fw);
}

static int wpi_fiwmwawe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpi_fiwmwawe *fw;

	/*
	 * Memowy wiww be fweed by wpi_fiwmwawe_dewete() once aww usews have
	 * weweased theiw fiwmwawe handwes. Don't use devm_kzawwoc() hewe.
	 */
	fw = kzawwoc(sizeof(*fw), GFP_KEWNEW);
	if (!fw)
		wetuwn -ENOMEM;

	fw->cw.dev = dev;
	fw->cw.wx_cawwback = wesponse_cawwback;
	fw->cw.tx_bwock = twue;

	fw->chan = mbox_wequest_channew(&fw->cw, 0);
	if (IS_EWW(fw->chan)) {
		int wet = PTW_EWW(fw->chan);
		kfwee(fw);
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get mbox channew\n");
	}

	init_compwetion(&fw->c);
	kwef_init(&fw->consumews);

	pwatfowm_set_dwvdata(pdev, fw);

	wpi_fiwmwawe_pwint_fiwmwawe_wevision(fw);
	wpi_wegistew_hwmon_dwivew(dev, fw);
	wpi_wegistew_cwk_dwivew(dev);

	wetuwn 0;
}

static void wpi_fiwmwawe_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wpi_fiwmwawe *fw = pwatfowm_get_dwvdata(pdev);

	if (!fw)
		wetuwn;

	wpi_fiwmwawe_pwopewty(fw, WPI_FIWMWAWE_NOTIFY_WEBOOT, NUWW, 0);
}

static void wpi_fiwmwawe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpi_fiwmwawe *fw = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(wpi_hwmon);
	wpi_hwmon = NUWW;
	pwatfowm_device_unwegistew(wpi_cwk);
	wpi_cwk = NUWW;

	wpi_fiwmwawe_put(fw);
}

static const stwuct of_device_id wpi_fiwmwawe_of_match[] = {
	{ .compatibwe = "waspbewwypi,bcm2835-fiwmwawe", },
	{},
};
MODUWE_DEVICE_TABWE(of, wpi_fiwmwawe_of_match);

stwuct device_node *wpi_fiwmwawe_find_node(void)
{
	wetuwn of_find_matching_node(NUWW, wpi_fiwmwawe_of_match);
}
EXPOWT_SYMBOW_GPW(wpi_fiwmwawe_find_node);

/**
 * wpi_fiwmwawe_get - Get pointew to wpi_fiwmwawe stwuctuwe.
 * @fiwmwawe_node:    Pointew to the fiwmwawe Device Twee node.
 *
 * The wefewence to wpi_fiwmwawe has to be weweased with wpi_fiwmwawe_put().
 *
 * Wetuwns NUWW is the fiwmwawe device is not weady.
 */
stwuct wpi_fiwmwawe *wpi_fiwmwawe_get(stwuct device_node *fiwmwawe_node)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(fiwmwawe_node);
	stwuct wpi_fiwmwawe *fw;

	if (!pdev)
		wetuwn NUWW;

	fw = pwatfowm_get_dwvdata(pdev);
	if (!fw)
		goto eww_put_device;

	if (!kwef_get_unwess_zewo(&fw->consumews))
		goto eww_put_device;

	put_device(&pdev->dev);

	wetuwn fw;

eww_put_device:
	put_device(&pdev->dev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wpi_fiwmwawe_get);

/**
 * devm_wpi_fiwmwawe_get - Get pointew to wpi_fiwmwawe stwuctuwe.
 * @dev:              The fiwmwawe device stwuctuwe
 * @fiwmwawe_node:    Pointew to the fiwmwawe Device Twee node.
 *
 * Wetuwns NUWW is the fiwmwawe device is not weady.
 */
stwuct wpi_fiwmwawe *devm_wpi_fiwmwawe_get(stwuct device *dev,
					   stwuct device_node *fiwmwawe_node)
{
	stwuct wpi_fiwmwawe *fw;

	fw = wpi_fiwmwawe_get(fiwmwawe_node);
	if (!fw)
		wetuwn NUWW;

	if (devm_add_action_ow_weset(dev, devm_wpi_fiwmwawe_put, fw))
		wetuwn NUWW;

	wetuwn fw;
}
EXPOWT_SYMBOW_GPW(devm_wpi_fiwmwawe_get);

static stwuct pwatfowm_dwivew wpi_fiwmwawe_dwivew = {
	.dwivew = {
		.name = "waspbewwypi-fiwmwawe",
		.of_match_tabwe = wpi_fiwmwawe_of_match,
	},
	.pwobe		= wpi_fiwmwawe_pwobe,
	.shutdown	= wpi_fiwmwawe_shutdown,
	.wemove_new	= wpi_fiwmwawe_wemove,
};
moduwe_pwatfowm_dwivew(wpi_fiwmwawe_dwivew);

MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_DESCWIPTION("Waspbewwy Pi fiwmwawe dwivew");
MODUWE_WICENSE("GPW v2");
