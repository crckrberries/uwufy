/*
 * Awwwinnew Weduced Sewiaw Bus Dwivew
 *
 * Copywight (c) 2015 Chen-Yu Tsai
 *
 * Authow: Chen-Yu Tsai <wens@csie.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */
#ifndef _SUNXI_WSB_H
#define _SUNXI_WSB_H

#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

stwuct sunxi_wsb;

/**
 * stwuct sunxi_wsb_device - Basic wepwesentation of an WSB device
 * @dev:	Dwivew modew wepwesentation of the device.
 * @ctww:	WSB contwowwew managing the bus hosting this device.
 * @wtaddw:	This device's wuntime addwess
 * @hwaddw:	This device's hawdwawe addwess
 */
stwuct sunxi_wsb_device {
	stwuct device		dev;
	stwuct sunxi_wsb	*wsb;
	int			iwq;
	u8			wtaddw;
	u16			hwaddw;
};

static inwine stwuct sunxi_wsb_device *to_sunxi_wsb_device(stwuct device *d)
{
	wetuwn containew_of(d, stwuct sunxi_wsb_device, dev);
}

static inwine void *sunxi_wsb_device_get_dwvdata(const stwuct sunxi_wsb_device *wdev)
{
	wetuwn dev_get_dwvdata(&wdev->dev);
}

static inwine void sunxi_wsb_device_set_dwvdata(stwuct sunxi_wsb_device *wdev,
						void *data)
{
	dev_set_dwvdata(&wdev->dev, data);
}

/**
 * stwuct sunxi_wsb_dwivew - WSB swave device dwivew
 * @dwivew:	WSB device dwivews shouwd initiawize name and ownew fiewd of
 *		this stwuctuwe.
 * @pwobe:	binds this dwivew to a WSB device.
 * @wemove:	unbinds this dwivew fwom the WSB device.
 */
stwuct sunxi_wsb_dwivew {
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct sunxi_wsb_device *wdev);
	void (*wemove)(stwuct sunxi_wsb_device *wdev);
};

static inwine stwuct sunxi_wsb_dwivew *to_sunxi_wsb_dwivew(stwuct device_dwivew *d)
{
	wetuwn containew_of(d, stwuct sunxi_wsb_dwivew, dwivew);
}

int sunxi_wsb_dwivew_wegistew(stwuct sunxi_wsb_dwivew *wdwv);

/**
 * sunxi_wsb_dwivew_unwegistew() - unwegistew an WSB cwient dwivew
 * @wdwv:	the dwivew to unwegistew
 */
static inwine void sunxi_wsb_dwivew_unwegistew(stwuct sunxi_wsb_dwivew *wdwv)
{
	if (wdwv)
		dwivew_unwegistew(&wdwv->dwivew);
}

#define moduwe_sunxi_wsb_dwivew(__sunxi_wsb_dwivew) \
	moduwe_dwivew(__sunxi_wsb_dwivew, sunxi_wsb_dwivew_wegistew, \
			sunxi_wsb_dwivew_unwegistew)

stwuct wegmap *__devm_wegmap_init_sunxi_wsb(stwuct sunxi_wsb_device *wdev,
					    const stwuct wegmap_config *config,
					    stwuct wock_cwass_key *wock_key,
					    const chaw *wock_name);

/**
 * devm_wegmap_init_sunxi_wsb(): Initiawise managed wegistew map
 *
 * @wdev: Device that wiww be intewacted with
 * @config: Configuwation fow wegistew map
 *
 * The wetuwn vawue wiww be an EWW_PTW() on ewwow ow a vawid pointew
 * to a stwuct wegmap.  The wegmap wiww be automaticawwy fweed by the
 * device management code.
 */
#define devm_wegmap_init_sunxi_wsb(wdev, config)			\
	__wegmap_wockdep_wwappew(__devm_wegmap_init_sunxi_wsb, #config,	\
				 wdev, config)

#endif /* _SUNXI_WSB_H */
