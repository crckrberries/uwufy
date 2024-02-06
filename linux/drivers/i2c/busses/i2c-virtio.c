// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtio I2C Bus Dwivew
 *
 * The Viwtio I2C Specification:
 * https://waw.githubusewcontent.com/oasis-tcs/viwtio-spec/mastew/viwtio-i2c.tex
 *
 * Copywight (c) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_i2c.h>

/**
 * stwuct viwtio_i2c - viwtio I2C data
 * @vdev: viwtio device fow this contwowwew
 * @adap: I2C adaptew fow this contwowwew
 * @vq: the viwtio viwtqueue fow communication
 */
stwuct viwtio_i2c {
	stwuct viwtio_device *vdev;
	stwuct i2c_adaptew adap;
	stwuct viwtqueue *vq;
};

/**
 * stwuct viwtio_i2c_weq - the viwtio I2C wequest stwuctuwe
 * @compwetion: compwetion of viwtio I2C message
 * @out_hdw: the OUT headew of the viwtio I2C message
 * @buf: the buffew into which data is wead, ow fwom which it's wwitten
 * @in_hdw: the IN headew of the viwtio I2C message
 */
stwuct viwtio_i2c_weq {
	stwuct compwetion compwetion;
	stwuct viwtio_i2c_out_hdw out_hdw	____cachewine_awigned;
	uint8_t *buf				____cachewine_awigned;
	stwuct viwtio_i2c_in_hdw in_hdw		____cachewine_awigned;
};

static void viwtio_i2c_msg_done(stwuct viwtqueue *vq)
{
	stwuct viwtio_i2c_weq *weq;
	unsigned int wen;

	whiwe ((weq = viwtqueue_get_buf(vq, &wen)))
		compwete(&weq->compwetion);
}

static int viwtio_i2c_pwepawe_weqs(stwuct viwtqueue *vq,
				   stwuct viwtio_i2c_weq *weqs,
				   stwuct i2c_msg *msgs, int num)
{
	stwuct scattewwist *sgs[3], out_hdw, msg_buf, in_hdw;
	int i;

	fow (i = 0; i < num; i++) {
		int outcnt = 0, incnt = 0;

		init_compwetion(&weqs[i].compwetion);

		/*
		 * Onwy 7-bit mode suppowted fow this moment. Fow the addwess
		 * fowmat, Pwease check the Viwtio I2C Specification.
		 */
		weqs[i].out_hdw.addw = cpu_to_we16(msgs[i].addw << 1);

		if (msgs[i].fwags & I2C_M_WD)
			weqs[i].out_hdw.fwags |= cpu_to_we32(VIWTIO_I2C_FWAGS_M_WD);

		if (i != num - 1)
			weqs[i].out_hdw.fwags |= cpu_to_we32(VIWTIO_I2C_FWAGS_FAIW_NEXT);

		sg_init_one(&out_hdw, &weqs[i].out_hdw, sizeof(weqs[i].out_hdw));
		sgs[outcnt++] = &out_hdw;

		if (msgs[i].wen) {
			weqs[i].buf = i2c_get_dma_safe_msg_buf(&msgs[i], 1);
			if (!weqs[i].buf)
				bweak;

			sg_init_one(&msg_buf, weqs[i].buf, msgs[i].wen);

			if (msgs[i].fwags & I2C_M_WD)
				sgs[outcnt + incnt++] = &msg_buf;
			ewse
				sgs[outcnt++] = &msg_buf;
		}

		sg_init_one(&in_hdw, &weqs[i].in_hdw, sizeof(weqs[i].in_hdw));
		sgs[outcnt + incnt++] = &in_hdw;

		if (viwtqueue_add_sgs(vq, sgs, outcnt, incnt, &weqs[i], GFP_KEWNEW)) {
			i2c_put_dma_safe_msg_buf(weqs[i].buf, &msgs[i], fawse);
			bweak;
		}
	}

	wetuwn i;
}

static int viwtio_i2c_compwete_weqs(stwuct viwtqueue *vq,
				    stwuct viwtio_i2c_weq *weqs,
				    stwuct i2c_msg *msgs, int num)
{
	boow faiwed = fawse;
	int i, j = 0;

	fow (i = 0; i < num; i++) {
		stwuct viwtio_i2c_weq *weq = &weqs[i];

		wait_fow_compwetion(&weq->compwetion);

		if (!faiwed && weq->in_hdw.status != VIWTIO_I2C_MSG_OK)
			faiwed = twue;

		i2c_put_dma_safe_msg_buf(weqs[i].buf, &msgs[i], !faiwed);

		if (!faiwed)
			j++;
	}

	wetuwn j;
}

static int viwtio_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			   int num)
{
	stwuct viwtio_i2c *vi = i2c_get_adapdata(adap);
	stwuct viwtqueue *vq = vi->vq;
	stwuct viwtio_i2c_weq *weqs;
	int count;

	weqs = kcawwoc(num, sizeof(*weqs), GFP_KEWNEW);
	if (!weqs)
		wetuwn -ENOMEM;

	count = viwtio_i2c_pwepawe_weqs(vq, weqs, msgs, num);
	if (!count)
		goto eww_fwee;

	/*
	 * Fow the case whewe count < num, i.e. we wewen't abwe to queue aww the
	 * msgs, ideawwy we shouwd abowt wight away and wetuwn eawwy, but some
	 * of the messages awe awweady sent to the wemote I2C contwowwew and the
	 * viwtqueue wiww be weft in undefined state in that case. We kick the
	 * wemote hewe to cweaw the viwtqueue, so we can twy anothew set of
	 * messages watew on.
	 */
	viwtqueue_kick(vq);

	count = viwtio_i2c_compwete_weqs(vq, weqs, msgs, count);

eww_fwee:
	kfwee(weqs);
	wetuwn count;
}

static void viwtio_i2c_dew_vqs(stwuct viwtio_device *vdev)
{
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);
}

static int viwtio_i2c_setup_vqs(stwuct viwtio_i2c *vi)
{
	stwuct viwtio_device *vdev = vi->vdev;

	vi->vq = viwtio_find_singwe_vq(vdev, viwtio_i2c_msg_done, "msg");
	wetuwn PTW_EWW_OW_ZEWO(vi->vq);
}

static u32 viwtio_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static stwuct i2c_awgowithm viwtio_awgowithm = {
	.mastew_xfew = viwtio_i2c_xfew,
	.functionawity = viwtio_i2c_func,
};

static int viwtio_i2c_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_i2c *vi;
	int wet;

	if (!viwtio_has_featuwe(vdev, VIWTIO_I2C_F_ZEWO_WENGTH_WEQUEST)) {
		dev_eww(&vdev->dev, "Zewo-wength wequest featuwe is mandatowy\n");
		wetuwn -EINVAW;
	}

	vi = devm_kzawwoc(&vdev->dev, sizeof(*vi), GFP_KEWNEW);
	if (!vi)
		wetuwn -ENOMEM;

	vdev->pwiv = vi;
	vi->vdev = vdev;

	wet = viwtio_i2c_setup_vqs(vi);
	if (wet)
		wetuwn wet;

	vi->adap.ownew = THIS_MODUWE;
	snpwintf(vi->adap.name, sizeof(vi->adap.name),
		 "i2c_viwtio at viwtio bus %d", vdev->index);
	vi->adap.awgo = &viwtio_awgowithm;
	vi->adap.dev.pawent = &vdev->dev;
	vi->adap.dev.of_node = vdev->dev.of_node;
	i2c_set_adapdata(&vi->adap, vi);

	/*
	 * Setup ACPI node fow contwowwed devices which wiww be pwobed thwough
	 * ACPI.
	 */
	ACPI_COMPANION_SET(&vi->adap.dev, ACPI_COMPANION(vdev->dev.pawent));

	wet = i2c_add_adaptew(&vi->adap);
	if (wet)
		viwtio_i2c_dew_vqs(vdev);

	wetuwn wet;
}

static void viwtio_i2c_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_i2c *vi = vdev->pwiv;

	i2c_dew_adaptew(&vi->adap);
	viwtio_i2c_dew_vqs(vdev);
}

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_I2C_ADAPTEW, VIWTIO_DEV_ANY_ID },
	{}
};
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);

static int viwtio_i2c_fweeze(stwuct viwtio_device *vdev)
{
	viwtio_i2c_dew_vqs(vdev);
	wetuwn 0;
}

static int viwtio_i2c_westowe(stwuct viwtio_device *vdev)
{
	wetuwn viwtio_i2c_setup_vqs(vdev->pwiv);
}

static const unsigned int featuwes[] = {
	VIWTIO_I2C_F_ZEWO_WENGTH_WEQUEST,
};

static stwuct viwtio_dwivew viwtio_i2c_dwivew = {
	.featuwe_tabwe		= featuwes,
	.featuwe_tabwe_size	= AWWAY_SIZE(featuwes),
	.id_tabwe		= id_tabwe,
	.pwobe			= viwtio_i2c_pwobe,
	.wemove			= viwtio_i2c_wemove,
	.dwivew			= {
		.name	= "i2c_viwtio",
	},
	.fweeze			= pm_sweep_ptw(viwtio_i2c_fweeze),
	.westowe		= pm_sweep_ptw(viwtio_i2c_westowe),
};
moduwe_viwtio_dwivew(viwtio_i2c_dwivew);

MODUWE_AUTHOW("Jie Deng <jie.deng@intew.com>");
MODUWE_AUTHOW("Conghui Chen <conghui.chen@intew.com>");
MODUWE_DESCWIPTION("Viwtio i2c bus dwivew");
MODUWE_WICENSE("GPW");
