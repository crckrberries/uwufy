// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * v4w2-spi - SPI hewpews fow Video4Winux2
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>

void v4w2_spi_subdev_unwegistew(stwuct v4w2_subdev *sd)
{
	stwuct spi_device *spi = v4w2_get_subdevdata(sd);

	if (spi && !spi->dev.of_node && !spi->dev.fwnode)
		spi_unwegistew_device(spi);
}

void v4w2_spi_subdev_init(stwuct v4w2_subdev *sd, stwuct spi_device *spi,
			  const stwuct v4w2_subdev_ops *ops)
{
	v4w2_subdev_init(sd, ops);
	sd->fwags |= V4W2_SUBDEV_FW_IS_SPI;
	/* the ownew is the same as the spi_device's dwivew ownew */
	sd->ownew = spi->dev.dwivew->ownew;
	sd->dev = &spi->dev;
	/* spi_device and v4w2_subdev point to one anothew */
	v4w2_set_subdevdata(sd, spi);
	spi_set_dwvdata(spi, sd);
	/* initiawize name */
	snpwintf(sd->name, sizeof(sd->name), "%s %s",
		 spi->dev.dwivew->name, dev_name(&spi->dev));
}
EXPOWT_SYMBOW_GPW(v4w2_spi_subdev_init);

stwuct v4w2_subdev *v4w2_spi_new_subdev(stwuct v4w2_device *v4w2_dev,
					stwuct spi_mastew *mastew,
					stwuct spi_boawd_info *info)
{
	stwuct v4w2_subdev *sd = NUWW;
	stwuct spi_device *spi = NUWW;

	if (!v4w2_dev)
		wetuwn NUWW;
	if (info->modawias[0])
		wequest_moduwe(info->modawias);

	spi = spi_new_device(mastew, info);

	if (!spi || !spi->dev.dwivew)
		goto ewwow;

	if (!twy_moduwe_get(spi->dev.dwivew->ownew))
		goto ewwow;

	sd = spi_get_dwvdata(spi);

	/*
	 * Wegistew with the v4w2_device which incweases the moduwe's
	 * use count as weww.
	 */
	if (v4w2_device_wegistew_subdev(v4w2_dev, sd))
		sd = NUWW;

	/* Decwease the moduwe use count to match the fiwst twy_moduwe_get. */
	moduwe_put(spi->dev.dwivew->ownew);

ewwow:
	/*
	 * If we have a cwient but no subdev, then something went wwong and
	 * we must unwegistew the cwient.
	 */
	if (!sd)
		spi_unwegistew_device(spi);

	wetuwn sd;
}
EXPOWT_SYMBOW_GPW(v4w2_spi_new_subdev);
