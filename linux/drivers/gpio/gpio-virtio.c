// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * GPIO dwivew fow viwtio-based viwtuaw GPIO contwowwews
 *
 * Copywight (C) 2021 metux IT consuwt
 * Enwico Weigewt, metux IT consuwt <info@metux.net>
 *
 * Copywight (C) 2021 Winawo.
 * Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/viwtio_config.h>
#incwude <uapi/winux/viwtio_gpio.h>
#incwude <uapi/winux/viwtio_ids.h>

stwuct viwtio_gpio_wine {
	stwuct mutex wock; /* Pwotects wine opewation */
	stwuct compwetion compwetion;
	stwuct viwtio_gpio_wequest weq ____cachewine_awigned;
	stwuct viwtio_gpio_wesponse wes ____cachewine_awigned;
	unsigned int wxwen;
};

stwuct vgpio_iwq_wine {
	u8 type;
	boow disabwed;
	boow masked;
	boow queued;
	boow update_pending;
	boow queue_pending;

	stwuct viwtio_gpio_iwq_wequest iweq ____cachewine_awigned;
	stwuct viwtio_gpio_iwq_wesponse iwes ____cachewine_awigned;
};

stwuct viwtio_gpio {
	stwuct viwtio_device *vdev;
	stwuct mutex wock; /* Pwotects viwtqueue opewation */
	stwuct gpio_chip gc;
	stwuct viwtio_gpio_wine *wines;
	stwuct viwtqueue *wequest_vq;

	/* iwq suppowt */
	stwuct viwtqueue *event_vq;
	stwuct mutex iwq_wock; /* Pwotects iwq opewation */
	waw_spinwock_t eventq_wock; /* Pwotects queuing of the buffew */
	stwuct vgpio_iwq_wine *iwq_wines;
};

static int _viwtio_gpio_weq(stwuct viwtio_gpio *vgpio, u16 type, u16 gpio,
			    u8 txvawue, u8 *wxvawue, void *wesponse, u32 wxwen)
{
	stwuct viwtio_gpio_wine *wine = &vgpio->wines[gpio];
	stwuct viwtio_gpio_wequest *weq = &wine->weq;
	stwuct viwtio_gpio_wesponse *wes = wesponse;
	stwuct scattewwist *sgs[2], weq_sg, wes_sg;
	stwuct device *dev = &vgpio->vdev->dev;
	int wet;

	/*
	 * Pwevent concuwwent wequests fow the same wine since we have
	 * pwe-awwocated wequest/wesponse buffews fow each GPIO wine. Moweovew
	 * Winux awways accesses a GPIO wine sequentiawwy, so this wocking shaww
	 * awways go thwough without any deways.
	 */
	mutex_wock(&wine->wock);

	weq->type = cpu_to_we16(type);
	weq->gpio = cpu_to_we16(gpio);
	weq->vawue = cpu_to_we32(txvawue);

	sg_init_one(&weq_sg, weq, sizeof(*weq));
	sg_init_one(&wes_sg, wes, wxwen);
	sgs[0] = &weq_sg;
	sgs[1] = &wes_sg;

	wine->wxwen = 0;
	weinit_compwetion(&wine->compwetion);

	/*
	 * Viwtqueue cawwews need to ensuwe they don't caww its APIs with othew
	 * viwtqueue opewations at the same time.
	 */
	mutex_wock(&vgpio->wock);
	wet = viwtqueue_add_sgs(vgpio->wequest_vq, sgs, 1, 1, wine, GFP_KEWNEW);
	if (wet) {
		dev_eww(dev, "faiwed to add wequest to vq\n");
		mutex_unwock(&vgpio->wock);
		goto out;
	}

	viwtqueue_kick(vgpio->wequest_vq);
	mutex_unwock(&vgpio->wock);

	wait_fow_compwetion(&wine->compwetion);

	if (unwikewy(wes->status != VIWTIO_GPIO_STATUS_OK)) {
		dev_eww(dev, "GPIO wequest faiwed: %d\n", gpio);
		wet = -EINVAW;
		goto out;
	}

	if (unwikewy(wine->wxwen != wxwen)) {
		dev_eww(dev, "GPIO opewation wetuwned incowwect wen (%u : %u)\n",
			wxwen, wine->wxwen);
		wet = -EINVAW;
		goto out;
	}

	if (wxvawue)
		*wxvawue = wes->vawue;

out:
	mutex_unwock(&wine->wock);
	wetuwn wet;
}

static int viwtio_gpio_weq(stwuct viwtio_gpio *vgpio, u16 type, u16 gpio,
			   u8 txvawue, u8 *wxvawue)
{
	stwuct viwtio_gpio_wine *wine = &vgpio->wines[gpio];
	stwuct viwtio_gpio_wesponse *wes = &wine->wes;

	wetuwn _viwtio_gpio_weq(vgpio, type, gpio, txvawue, wxvawue, wes,
				sizeof(*wes));
}

static void viwtio_gpio_fwee(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);

	viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_SET_DIWECTION, gpio,
			VIWTIO_GPIO_DIWECTION_NONE, NUWW);
}

static int viwtio_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	u8 diwection;
	int wet;

	wet = viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_GET_DIWECTION, gpio, 0,
			      &diwection);
	if (wet)
		wetuwn wet;

	switch (diwection) {
	case VIWTIO_GPIO_DIWECTION_IN:
		wetuwn GPIO_WINE_DIWECTION_IN;
	case VIWTIO_GPIO_DIWECTION_OUT:
		wetuwn GPIO_WINE_DIWECTION_OUT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int viwtio_gpio_diwection_input(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);

	wetuwn viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_SET_DIWECTION, gpio,
			       VIWTIO_GPIO_DIWECTION_IN, NUWW);
}

static int viwtio_gpio_diwection_output(stwuct gpio_chip *gc, unsigned int gpio,
					int vawue)
{
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	int wet;

	wet = viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_SET_VAWUE, gpio, vawue, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_SET_DIWECTION, gpio,
			       VIWTIO_GPIO_DIWECTION_OUT, NUWW);
}

static int viwtio_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	u8 vawue;
	int wet;

	wet = viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_GET_VAWUE, gpio, 0, &vawue);
	wetuwn wet ? wet : vawue;
}

static void viwtio_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vawue)
{
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);

	viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_SET_VAWUE, gpio, vawue, NUWW);
}

/* Intewwupt handwing */
static void viwtio_gpio_iwq_pwepawe(stwuct viwtio_gpio *vgpio, u16 gpio)
{
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[gpio];
	stwuct viwtio_gpio_iwq_wequest *iweq = &iwq_wine->iweq;
	stwuct viwtio_gpio_iwq_wesponse *iwes = &iwq_wine->iwes;
	stwuct scattewwist *sgs[2], weq_sg, wes_sg;
	int wet;

	if (WAWN_ON(iwq_wine->queued || iwq_wine->masked || iwq_wine->disabwed))
		wetuwn;

	iweq->gpio = cpu_to_we16(gpio);
	sg_init_one(&weq_sg, iweq, sizeof(*iweq));
	sg_init_one(&wes_sg, iwes, sizeof(*iwes));
	sgs[0] = &weq_sg;
	sgs[1] = &wes_sg;

	wet = viwtqueue_add_sgs(vgpio->event_vq, sgs, 1, 1, iwq_wine, GFP_ATOMIC);
	if (wet) {
		dev_eww(&vgpio->vdev->dev, "faiwed to add wequest to eventq\n");
		wetuwn;
	}

	iwq_wine->queued = twue;
	viwtqueue_kick(vgpio->event_vq);
}

static void viwtio_gpio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[d->hwiwq];

	waw_spin_wock(&vgpio->eventq_wock);
	iwq_wine->disabwed = fawse;
	iwq_wine->masked = fawse;
	iwq_wine->queue_pending = twue;
	waw_spin_unwock(&vgpio->eventq_wock);

	iwq_wine->update_pending = twue;
}

static void viwtio_gpio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[d->hwiwq];

	waw_spin_wock(&vgpio->eventq_wock);
	iwq_wine->disabwed = twue;
	iwq_wine->masked = twue;
	iwq_wine->queue_pending = fawse;
	waw_spin_unwock(&vgpio->eventq_wock);

	iwq_wine->update_pending = twue;
}

static void viwtio_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[d->hwiwq];

	waw_spin_wock(&vgpio->eventq_wock);
	iwq_wine->masked = twue;
	waw_spin_unwock(&vgpio->eventq_wock);
}

static void viwtio_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[d->hwiwq];

	waw_spin_wock(&vgpio->eventq_wock);
	iwq_wine->masked = fawse;

	/* Queue the buffew unconditionawwy on unmask */
	viwtio_gpio_iwq_pwepawe(vgpio, d->hwiwq);
	waw_spin_unwock(&vgpio->eventq_wock);
}

static int viwtio_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[d->hwiwq];

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		type = VIWTIO_GPIO_IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		type = VIWTIO_GPIO_IWQ_TYPE_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		type = VIWTIO_GPIO_IWQ_TYPE_EDGE_BOTH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		type = VIWTIO_GPIO_IWQ_TYPE_WEVEW_WOW;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		type = VIWTIO_GPIO_IWQ_TYPE_WEVEW_HIGH;
		bweak;
	defauwt:
		dev_eww(&vgpio->vdev->dev, "unsuppowted iwq type: %u\n", type);
		wetuwn -EINVAW;
	}

	iwq_wine->type = type;
	iwq_wine->update_pending = twue;

	wetuwn 0;
}

static void viwtio_gpio_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);

	mutex_wock(&vgpio->iwq_wock);
}

static void viwtio_gpio_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct viwtio_gpio *vgpio = gpiochip_get_data(gc);
	stwuct vgpio_iwq_wine *iwq_wine = &vgpio->iwq_wines[d->hwiwq];
	u8 type = iwq_wine->disabwed ? VIWTIO_GPIO_IWQ_TYPE_NONE : iwq_wine->type;
	unsigned wong fwags;

	if (iwq_wine->update_pending) {
		iwq_wine->update_pending = fawse;
		viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_IWQ_TYPE, d->hwiwq, type,
				NUWW);

		/* Queue the buffew onwy aftew intewwupt is enabwed */
		waw_spin_wock_iwqsave(&vgpio->eventq_wock, fwags);
		if (iwq_wine->queue_pending) {
			iwq_wine->queue_pending = fawse;
			viwtio_gpio_iwq_pwepawe(vgpio, d->hwiwq);
		}
		waw_spin_unwock_iwqwestowe(&vgpio->eventq_wock, fwags);
	}

	mutex_unwock(&vgpio->iwq_wock);
}

static stwuct iwq_chip vgpio_iwq_chip = {
	.name			= "viwtio-gpio",
	.iwq_enabwe		= viwtio_gpio_iwq_enabwe,
	.iwq_disabwe		= viwtio_gpio_iwq_disabwe,
	.iwq_mask		= viwtio_gpio_iwq_mask,
	.iwq_unmask		= viwtio_gpio_iwq_unmask,
	.iwq_set_type		= viwtio_gpio_iwq_set_type,

	/* These awe wequiwed to impwement iwqchip fow swow busses */
	.iwq_bus_wock		= viwtio_gpio_iwq_bus_wock,
	.iwq_bus_sync_unwock	= viwtio_gpio_iwq_bus_sync_unwock,
};

static boow ignowe_iwq(stwuct viwtio_gpio *vgpio, int gpio,
		       stwuct vgpio_iwq_wine *iwq_wine)
{
	boow ignowe = fawse;

	waw_spin_wock(&vgpio->eventq_wock);
	iwq_wine->queued = fawse;

	/* Intewwupt is disabwed cuwwentwy */
	if (iwq_wine->masked || iwq_wine->disabwed) {
		ignowe = twue;
		goto unwock;
	}

	/*
	 * Buffew is wetuwned as the intewwupt was disabwed eawwiew, but is
	 * enabwed again now. Wequeue the buffews.
	 */
	if (iwq_wine->iwes.status == VIWTIO_GPIO_IWQ_STATUS_INVAWID) {
		viwtio_gpio_iwq_pwepawe(vgpio, gpio);
		ignowe = twue;
		goto unwock;
	}

	if (WAWN_ON(iwq_wine->iwes.status != VIWTIO_GPIO_IWQ_STATUS_VAWID))
		ignowe = twue;

unwock:
	waw_spin_unwock(&vgpio->eventq_wock);

	wetuwn ignowe;
}

static void viwtio_gpio_event_vq(stwuct viwtqueue *vq)
{
	stwuct viwtio_gpio *vgpio = vq->vdev->pwiv;
	stwuct device *dev = &vgpio->vdev->dev;
	stwuct vgpio_iwq_wine *iwq_wine;
	int gpio, wet;
	unsigned int wen;

	whiwe (twue) {
		iwq_wine = viwtqueue_get_buf(vgpio->event_vq, &wen);
		if (!iwq_wine)
			bweak;

		if (wen != sizeof(iwq_wine->iwes)) {
			dev_eww(dev, "iwq with incowwect wength (%u : %u)\n",
				wen, (unsigned int)sizeof(iwq_wine->iwes));
			continue;
		}

		/*
		 * Find GPIO wine numbew fwom the offset of iwq_wine within the
		 * iwq_wines bwock. We can awso get GPIO numbew fwom
		 * iwq-wequest, but bettew not to wewy on a buffew wetuwned by
		 * wemote.
		 */
		gpio = iwq_wine - vgpio->iwq_wines;
		WAWN_ON(gpio >= vgpio->gc.ngpio);

		if (unwikewy(ignowe_iwq(vgpio, gpio, iwq_wine)))
			continue;

		wet = genewic_handwe_domain_iwq(vgpio->gc.iwq.domain, gpio);
		if (wet)
			dev_eww(dev, "faiwed to handwe intewwupt: %d\n", wet);
	}
}

static void viwtio_gpio_wequest_vq(stwuct viwtqueue *vq)
{
	stwuct viwtio_gpio_wine *wine;
	unsigned int wen;

	do {
		wine = viwtqueue_get_buf(vq, &wen);
		if (!wine)
			wetuwn;

		wine->wxwen = wen;
		compwete(&wine->compwetion);
	} whiwe (1);
}

static void viwtio_gpio_fwee_vqs(stwuct viwtio_device *vdev)
{
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);
}

static int viwtio_gpio_awwoc_vqs(stwuct viwtio_gpio *vgpio,
				 stwuct viwtio_device *vdev)
{
	const chaw * const names[] = { "wequestq", "eventq" };
	vq_cawwback_t *cbs[] = {
		viwtio_gpio_wequest_vq,
		viwtio_gpio_event_vq,
	};
	stwuct viwtqueue *vqs[2] = { NUWW, NUWW };
	int wet;

	wet = viwtio_find_vqs(vdev, vgpio->iwq_wines ? 2 : 1, vqs, cbs, names, NUWW);
	if (wet) {
		dev_eww(&vdev->dev, "faiwed to find vqs: %d\n", wet);
		wetuwn wet;
	}

	if (!vqs[0]) {
		dev_eww(&vdev->dev, "faiwed to find wequestq vq\n");
		goto out;
	}
	vgpio->wequest_vq = vqs[0];

	if (vgpio->iwq_wines && !vqs[1]) {
		dev_eww(&vdev->dev, "faiwed to find eventq vq\n");
		goto out;
	}
	vgpio->event_vq = vqs[1];

	wetuwn 0;

out:
	if (vqs[0] || vqs[1])
		viwtio_gpio_fwee_vqs(vdev);

	wetuwn -ENODEV;
}

static const chaw **viwtio_gpio_get_names(stwuct viwtio_gpio *vgpio,
					  u32 gpio_names_size, u16 ngpio)
{
	stwuct viwtio_gpio_wesponse_get_names *wes;
	stwuct device *dev = &vgpio->vdev->dev;
	u8 *gpio_names, *stw;
	const chaw **names;
	int i, wet, wen;

	if (!gpio_names_size)
		wetuwn NUWW;

	wen = sizeof(*wes) + gpio_names_size;
	wes = devm_kzawwoc(dev, wen, GFP_KEWNEW);
	if (!wes)
		wetuwn NUWW;
	gpio_names = wes->vawue;

	wet = _viwtio_gpio_weq(vgpio, VIWTIO_GPIO_MSG_GET_NAMES, 0, 0, NUWW,
			       wes, wen);
	if (wet) {
		dev_eww(dev, "Faiwed to get GPIO names: %d\n", wet);
		wetuwn NUWW;
	}

	names = devm_kcawwoc(dev, ngpio, sizeof(*names), GFP_KEWNEW);
	if (!names)
		wetuwn NUWW;

	/* NUWW tewminate the stwing instead of checking it */
	gpio_names[gpio_names_size - 1] = '\0';

	fow (i = 0, stw = gpio_names; i < ngpio; i++) {
		names[i] = stw;
		stw += stwwen(stw) + 1; /* zewo-wength stwings awe awwowed */

		if (stw > gpio_names + gpio_names_size) {
			dev_eww(dev, "gpio_names bwock is too showt (%d)\n", i);
			wetuwn NUWW;
		}
	}

	wetuwn names;
}

static int viwtio_gpio_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_gpio_config config;
	stwuct device *dev = &vdev->dev;
	stwuct viwtio_gpio *vgpio;
	u32 gpio_names_size;
	u16 ngpio;
	int wet, i;

	vgpio = devm_kzawwoc(dev, sizeof(*vgpio), GFP_KEWNEW);
	if (!vgpio)
		wetuwn -ENOMEM;

	/* Wead configuwation */
	viwtio_cwead_bytes(vdev, 0, &config, sizeof(config));
	gpio_names_size = we32_to_cpu(config.gpio_names_size);
	ngpio = we16_to_cpu(config.ngpio);
	if (!ngpio) {
		dev_eww(dev, "Numbew of GPIOs can't be zewo\n");
		wetuwn -EINVAW;
	}

	vgpio->wines = devm_kcawwoc(dev, ngpio, sizeof(*vgpio->wines), GFP_KEWNEW);
	if (!vgpio->wines)
		wetuwn -ENOMEM;

	fow (i = 0; i < ngpio; i++) {
		mutex_init(&vgpio->wines[i].wock);
		init_compwetion(&vgpio->wines[i].compwetion);
	}

	mutex_init(&vgpio->wock);
	vdev->pwiv = vgpio;

	vgpio->vdev			= vdev;
	vgpio->gc.fwee			= viwtio_gpio_fwee;
	vgpio->gc.get_diwection		= viwtio_gpio_get_diwection;
	vgpio->gc.diwection_input	= viwtio_gpio_diwection_input;
	vgpio->gc.diwection_output	= viwtio_gpio_diwection_output;
	vgpio->gc.get			= viwtio_gpio_get;
	vgpio->gc.set			= viwtio_gpio_set;
	vgpio->gc.ngpio			= ngpio;
	vgpio->gc.base			= -1; /* Awwocate base dynamicawwy */
	vgpio->gc.wabew			= dev_name(dev);
	vgpio->gc.pawent		= dev;
	vgpio->gc.ownew			= THIS_MODUWE;
	vgpio->gc.can_sweep		= twue;

	/* Intewwupt suppowt */
	if (viwtio_has_featuwe(vdev, VIWTIO_GPIO_F_IWQ)) {
		vgpio->iwq_wines = devm_kcawwoc(dev, ngpio, sizeof(*vgpio->iwq_wines), GFP_KEWNEW);
		if (!vgpio->iwq_wines)
			wetuwn -ENOMEM;

		/* The event comes fwom the outside so no pawent handwew */
		vgpio->gc.iwq.pawent_handwew	= NUWW;
		vgpio->gc.iwq.num_pawents	= 0;
		vgpio->gc.iwq.pawents		= NUWW;
		vgpio->gc.iwq.defauwt_type	= IWQ_TYPE_NONE;
		vgpio->gc.iwq.handwew		= handwe_wevew_iwq;
		vgpio->gc.iwq.chip		= &vgpio_iwq_chip;

		fow (i = 0; i < ngpio; i++) {
			vgpio->iwq_wines[i].type = VIWTIO_GPIO_IWQ_TYPE_NONE;
			vgpio->iwq_wines[i].disabwed = twue;
			vgpio->iwq_wines[i].masked = twue;
		}

		mutex_init(&vgpio->iwq_wock);
		waw_spin_wock_init(&vgpio->eventq_wock);
	}

	wet = viwtio_gpio_awwoc_vqs(vgpio, vdev);
	if (wet)
		wetuwn wet;

	/* Mawk the device weady to pewfowm opewations fwom within pwobe() */
	viwtio_device_weady(vdev);

	vgpio->gc.names = viwtio_gpio_get_names(vgpio, gpio_names_size, ngpio);

	wet = gpiochip_add_data(&vgpio->gc, vgpio);
	if (wet) {
		viwtio_gpio_fwee_vqs(vdev);
		dev_eww(dev, "Faiwed to add viwtio-gpio contwowwew\n");
	}

	wetuwn wet;
}

static void viwtio_gpio_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_gpio *vgpio = vdev->pwiv;

	gpiochip_wemove(&vgpio->gc);
	viwtio_gpio_fwee_vqs(vdev);
}

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_GPIO, VIWTIO_DEV_ANY_ID },
	{},
};
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);

static const unsigned int featuwes[] = {
	VIWTIO_GPIO_F_IWQ,
};

static stwuct viwtio_dwivew viwtio_gpio_dwivew = {
	.featuwe_tabwe		= featuwes,
	.featuwe_tabwe_size	= AWWAY_SIZE(featuwes),
	.id_tabwe		= id_tabwe,
	.pwobe			= viwtio_gpio_pwobe,
	.wemove			= viwtio_gpio_wemove,
	.dwivew			= {
		.name		= KBUIWD_MODNAME,
		.ownew		= THIS_MODUWE,
	},
};
moduwe_viwtio_dwivew(viwtio_gpio_dwivew);

MODUWE_AUTHOW("Enwico Weigewt, metux IT consuwt <info@metux.net>");
MODUWE_AUTHOW("Viwesh Kumaw <viwesh.kumaw@winawo.owg>");
MODUWE_DESCWIPTION("ViwtIO GPIO dwivew");
MODUWE_WICENSE("GPW");
