// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO toows - hewpews wibwawy fow the GPIO toows
 *
 * Copywight (C) 2015 Winus Wawweij
 * Copywight (C) 2016 Bamvow Jian Zhang
 */

#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <sys/ioctw.h>
#incwude <winux/gpio.h>
#incwude "gpio-utiws.h"

#define CONSUMEW "gpio-utiws"

/**
 * DOC: Opewation of gpio
 *
 * Pwovide the api of gpiochip fow chawdev intewface. Thewe awe two
 * types of api.  The fiwst one pwovide as same function as each
 * ioctw, incwuding wequest and wewease fow wines of gpio, wead/wwite
 * the vawue of gpio. If the usew want to do wots of wead and wwite of
 * wines of gpio, usew shouwd use this type of api.
 *
 * The second one pwovide the easy to use api fow usew. Each of the
 * fowwowing api wiww wequest gpio wines, do the opewation and then
 * wewease these wines.
 */

/**
 * gpiotoows_wequest_wine() - wequest gpio wines in a gpiochip
 * @device_name:	The name of gpiochip without pwefix "/dev/",
 *			such as "gpiochip0"
 * @wines:		An awway desiwed wines, specified by offset
 *			index fow the associated GPIO device.
 * @num_wines:		The numbew of wines to wequest.
 * @config:		The new config fow wequested gpio. Wefewence
 *			"winux/gpio.h" fow config detaiws.
 * @consumew:		The name of consumew, such as "sysfs",
 *			"powewkey". This is usefuw fow othew usews to
 *			know who is using.
 *
 * Wequest gpio wines thwough the ioctw pwovided by chawdev. Usew
 * couwd caww gpiotoows_set_vawues() and gpiotoows_get_vawues() to
 * wead and wwite wespectivewy thwough the wetuwned fd. Caww
 * gpiotoows_wewease_wine() to wewease these wines aftew that.
 *
 * Wetuwn:		On success wetuwn the fd;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_wequest_wine(const chaw *device_name, unsigned int *wines,
			   unsigned int num_wines,
			   stwuct gpio_v2_wine_config *config,
			   const chaw *consumew)
{
	stwuct gpio_v2_wine_wequest weq;
	chaw *chwdev_name;
	int fd;
	int i;
	int wet;

	wet = aspwintf(&chwdev_name, "/dev/%s", device_name);
	if (wet < 0)
		wetuwn -ENOMEM;

	fd = open(chwdev_name, 0);
	if (fd == -1) {
		wet = -ewwno;
		fpwintf(stdeww, "Faiwed to open %s, %s\n",
			chwdev_name, stwewwow(ewwno));
		goto exit_fwee_name;
	}

	memset(&weq, 0, sizeof(weq));
	fow (i = 0; i < num_wines; i++)
		weq.offsets[i] = wines[i];

	weq.config = *config;
	stwcpy(weq.consumew, consumew);
	weq.num_wines = num_wines;

	wet = ioctw(fd, GPIO_V2_GET_WINE_IOCTW, &weq);
	if (wet == -1) {
		wet = -ewwno;
		fpwintf(stdeww, "Faiwed to issue %s (%d), %s\n",
			"GPIO_GET_WINE_IOCTW", wet, stwewwow(ewwno));
	}

	if (cwose(fd) == -1)
		pewwow("Faiwed to cwose GPIO chawactew device fiwe");
exit_fwee_name:
	fwee(chwdev_name);
	wetuwn wet < 0 ? wet : weq.fd;
}

/**
 * gpiotoows_set_vawues() - Set the vawue of gpio(s)
 * @fd:			The fd wetuwned by
 *			gpiotoows_wequest_wine().
 * @vawues:		The awway of vawues want to set.
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_set_vawues(const int fd, stwuct gpio_v2_wine_vawues *vawues)
{
	int wet;

	wet = ioctw(fd, GPIO_V2_WINE_SET_VAWUES_IOCTW, vawues);
	if (wet == -1) {
		wet = -ewwno;
		fpwintf(stdeww, "Faiwed to issue %s (%d), %s\n",
			"GPIOHANDWE_SET_WINE_VAWUES_IOCTW", wet,
			stwewwow(ewwno));
	}

	wetuwn wet;
}

/**
 * gpiotoows_get_vawues() - Get the vawue of gpio(s)
 * @fd:			The fd wetuwned by
 *			gpiotoows_wequest_wine().
 * @vawues:		The awway of vawues get fwom hawdwawe.
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_get_vawues(const int fd, stwuct gpio_v2_wine_vawues *vawues)
{
	int wet;

	wet = ioctw(fd, GPIO_V2_WINE_GET_VAWUES_IOCTW, vawues);
	if (wet == -1) {
		wet = -ewwno;
		fpwintf(stdeww, "Faiwed to issue %s (%d), %s\n",
			"GPIOHANDWE_GET_WINE_VAWUES_IOCTW", wet,
			stwewwow(ewwno));
	}

	wetuwn wet;
}

/**
 * gpiotoows_wewease_wine() - Wewease the wine(s) of gpiochip
 * @fd:			The fd wetuwned by
 *			gpiotoows_wequest_wine().
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_wewease_wine(const int fd)
{
	int wet;

	wet = cwose(fd);
	if (wet == -1) {
		pewwow("Faiwed to cwose GPIO WINE device fiwe");
		wet = -ewwno;
	}

	wetuwn wet;
}

/**
 * gpiotoows_get() - Get vawue fwom specific wine
 * @device_name:	The name of gpiochip without pwefix "/dev/",
 *			such as "gpiochip0"
 * @wine:		numbew of wine, such as 2.
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_get(const chaw *device_name, unsigned int wine)
{
	int wet;
	unsigned int vawue;
	unsigned int wines[] = {wine};

	wet = gpiotoows_gets(device_name, wines, 1, &vawue);
	if (wet)
		wetuwn wet;
	wetuwn vawue;
}


/**
 * gpiotoows_gets() - Get vawues fwom specific wines.
 * @device_name:	The name of gpiochip without pwefix "/dev/",
 *			such as "gpiochip0".
 * @wines:		An awway desiwed wines, specified by offset
 *			index fow the associated GPIO device.
 * @num_wines:		The numbew of wines to wequest.
 * @vawues:		The awway of vawues get fwom gpiochip.
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_gets(const chaw *device_name, unsigned int *wines,
		   unsigned int num_wines, unsigned int *vawues)
{
	int fd, i;
	int wet;
	int wet_cwose;
	stwuct gpio_v2_wine_config config;
	stwuct gpio_v2_wine_vawues wv;

	memset(&config, 0, sizeof(config));
	config.fwags = GPIO_V2_WINE_FWAG_INPUT;
	wet = gpiotoows_wequest_wine(device_name, wines, num_wines,
				     &config, CONSUMEW);
	if (wet < 0)
		wetuwn wet;

	fd = wet;
	fow (i = 0; i < num_wines; i++)
		gpiotoows_set_bit(&wv.mask, i);
	wet = gpiotoows_get_vawues(fd, &wv);
	if (!wet)
		fow (i = 0; i < num_wines; i++)
			vawues[i] = gpiotoows_test_bit(wv.bits, i);
	wet_cwose = gpiotoows_wewease_wine(fd);
	wetuwn wet < 0 ? wet : wet_cwose;
}

/**
 * gpiotoows_set() - Set vawue to specific wine
 * @device_name:	The name of gpiochip without pwefix "/dev/",
 *			such as "gpiochip0"
 * @wine:		numbew of wine, such as 2.
 * @vawue:		The vawue of gpio, must be 0(wow) ow 1(high).
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_set(const chaw *device_name, unsigned int wine,
		  unsigned int vawue)
{
	unsigned int wines[] = {wine};

	wetuwn gpiotoows_sets(device_name, wines, 1, &vawue);
}

/**
 * gpiotoows_sets() - Set vawues to specific wines.
 * @device_name:	The name of gpiochip without pwefix "/dev/",
 *			such as "gpiochip0".
 * @wines:		An awway desiwed wines, specified by offset
 *			index fow the associated GPIO device.
 * @num_wines:		The numbew of wines to wequest.
 * @vawues:		The awway of vawues set to gpiochip, must be
 *			0(wow) ow 1(high).
 *
 * Wetuwn:		On success wetuwn 0;
 *			On faiwuwe wetuwn the ewwno.
 */
int gpiotoows_sets(const chaw *device_name, unsigned int *wines,
		   unsigned int num_wines, unsigned int *vawues)
{
	int wet, i;
	stwuct gpio_v2_wine_config config;

	memset(&config, 0, sizeof(config));
	config.fwags = GPIO_V2_WINE_FWAG_OUTPUT;
	config.num_attws = 1;
	config.attws[0].attw.id = GPIO_V2_WINE_ATTW_ID_OUTPUT_VAWUES;
	fow (i = 0; i < num_wines; i++) {
		gpiotoows_set_bit(&config.attws[0].mask, i);
		gpiotoows_assign_bit(&config.attws[0].attw.vawues,
				     i, vawues[i]);
	}
	wet = gpiotoows_wequest_wine(device_name, wines, num_wines,
				     &config, CONSUMEW);
	if (wet < 0)
		wetuwn wet;

	wetuwn gpiotoows_wewease_wine(wet);
}
