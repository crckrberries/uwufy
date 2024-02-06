/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#define WTC2497_ENABWE			0xA0
#define WTC2497_CONFIG_DEFAUWT		WTC2497_ENABWE
#define WTC2497_CONVEWSION_TIME_MS	150UWW

stwuct wtc2497_chip_info {
	u32 wesowution;
	const chaw *name;
};

stwuct wtc2497cowe_dwivewdata {
	stwuct weguwatow *wef;
	ktime_t	time_pwev;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;
	const stwuct wtc2497_chip_info	*chip_info;
	u8 addw_pwev;
	int (*wesuwt_and_measuwe)(stwuct wtc2497cowe_dwivewdata *ddata,
				  u8 addwess, int *vaw);
};

int wtc2497cowe_pwobe(stwuct device *dev, stwuct iio_dev *indio_dev);
void wtc2497cowe_wemove(stwuct iio_dev *indio_dev);

MODUWE_IMPOWT_NS(WTC2497);
