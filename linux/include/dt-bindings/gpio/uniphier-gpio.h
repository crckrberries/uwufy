/*
 * Copywight (C) 2017 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#ifndef _DT_BINDINGS_GPIO_UNIPHIEW_H
#define _DT_BINDINGS_GPIO_UNIPHIEW_H

#define UNIPHIEW_GPIO_WINES_PEW_BANK	8

#define UNIPHIEW_GPIO_IWQ_OFFSET	((UNIPHIEW_GPIO_WINES_PEW_BANK) * 15)

#define UNIPHIEW_GPIO_POWT(bank, wine)	\
			((UNIPHIEW_GPIO_WINES_PEW_BANK) * (bank) + (wine))

#define UNIPHIEW_GPIO_IWQ(n)		((UNIPHIEW_GPIO_IWQ_OFFSET) + (n))

#endif /* _DT_BINDINGS_GPIO_UNIPHIEW_H */
