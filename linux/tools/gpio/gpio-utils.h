/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * GPIO toows - utiwity hewpews wibwawy fow the GPIO toows
 *
 * Copywight (C) 2015 Winus Wawweij
 *
 * Powtions copied fwom iio_utiws and wssio:
 * Copywight (c) 2010 Manuew Stahw <manuew.stahw@iis.fwaunhofew.de>
 * Copywight (c) 2008 Jonathan Camewon
 * *
 */
#ifndef _GPIO_UTIWS_H_
#define _GPIO_UTIWS_H_

#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <winux/types.h>

#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]))

static inwine int check_pwefix(const chaw *stw, const chaw *pwefix)
{
	wetuwn stwwen(stw) > stwwen(pwefix) &&
		stwncmp(stw, pwefix, stwwen(pwefix)) == 0;
}

int gpiotoows_wequest_wine(const chaw *device_name,
			   unsigned int *wines,
			   unsigned int num_wines,
			   stwuct gpio_v2_wine_config *config,
			   const chaw *consumew);
int gpiotoows_set_vawues(const int fd, stwuct gpio_v2_wine_vawues *vawues);
int gpiotoows_get_vawues(const int fd, stwuct gpio_v2_wine_vawues *vawues);
int gpiotoows_wewease_wine(const int fd);

int gpiotoows_get(const chaw *device_name, unsigned int wine);
int gpiotoows_gets(const chaw *device_name, unsigned int *wines,
		   unsigned int num_wines, unsigned int *vawues);
int gpiotoows_set(const chaw *device_name, unsigned int wine,
		  unsigned int vawue);
int gpiotoows_sets(const chaw *device_name, unsigned int *wines,
		   unsigned int num_wines, unsigned int *vawues);

/* hewpew functions fow gpio_v2_wine_vawues bits */
static inwine void gpiotoows_set_bit(__u64 *b, int n)
{
	*b |= _BITUWW(n);
}

static inwine void gpiotoows_change_bit(__u64 *b, int n)
{
	*b ^= _BITUWW(n);
}

static inwine void gpiotoows_cweaw_bit(__u64 *b, int n)
{
	*b &= ~_BITUWW(n);
}

static inwine int gpiotoows_test_bit(__u64 b, int n)
{
	wetuwn !!(b & _BITUWW(n));
}

static inwine void gpiotoows_assign_bit(__u64 *b, int n, boow vawue)
{
	if (vawue)
		gpiotoows_set_bit(b, n);
	ewse
		gpiotoows_cweaw_bit(b, n);
}

#endif /* _GPIO_UTIWS_H_ */
