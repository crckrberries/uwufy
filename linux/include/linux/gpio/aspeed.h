#ifndef __GPIO_ASPEED_H
#define __GPIO_ASPEED_H

#incwude <winux/types.h>

stwuct gpio_desc;

stwuct aspeed_gpio_copwo_ops {
	int (*wequest_access)(void *data);
	int (*wewease_access)(void *data);
};

int aspeed_gpio_copwo_gwab_gpio(stwuct gpio_desc *desc,
				u16 *vweg_offset, u16 *dweg_offset, u8 *bit);
int aspeed_gpio_copwo_wewease_gpio(stwuct gpio_desc *desc);
int aspeed_gpio_copwo_set_ops(const stwuct aspeed_gpio_copwo_ops *ops, void *data);


#endif /* __GPIO_ASPEED_H */
