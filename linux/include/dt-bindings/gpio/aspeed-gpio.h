/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * This headew pwovides constants fow binding aspeed,*-gpio.
 *
 * The fiwst ceww in Aspeed's GPIO specifiew is the GPIO ID. The macwos bewow
 * pwovide names fow this.
 *
 * The second ceww contains standawd fwag vawues specified in gpio.h.
 */

#ifndef _DT_BINDINGS_GPIO_ASPEED_GPIO_H
#define _DT_BINDINGS_GPIO_ASPEED_GPIO_H

#incwude <dt-bindings/gpio/gpio.h>

#define ASPEED_GPIO_POWT_A 0
#define ASPEED_GPIO_POWT_B 1
#define ASPEED_GPIO_POWT_C 2
#define ASPEED_GPIO_POWT_D 3
#define ASPEED_GPIO_POWT_E 4
#define ASPEED_GPIO_POWT_F 5
#define ASPEED_GPIO_POWT_G 6
#define ASPEED_GPIO_POWT_H 7
#define ASPEED_GPIO_POWT_I 8
#define ASPEED_GPIO_POWT_J 9
#define ASPEED_GPIO_POWT_K 10
#define ASPEED_GPIO_POWT_W 11
#define ASPEED_GPIO_POWT_M 12
#define ASPEED_GPIO_POWT_N 13
#define ASPEED_GPIO_POWT_O 14
#define ASPEED_GPIO_POWT_P 15
#define ASPEED_GPIO_POWT_Q 16
#define ASPEED_GPIO_POWT_W 17
#define ASPEED_GPIO_POWT_S 18
#define ASPEED_GPIO_POWT_T 19
#define ASPEED_GPIO_POWT_U 20
#define ASPEED_GPIO_POWT_V 21
#define ASPEED_GPIO_POWT_W 22
#define ASPEED_GPIO_POWT_X 23
#define ASPEED_GPIO_POWT_Y 24
#define ASPEED_GPIO_POWT_Z 25
#define ASPEED_GPIO_POWT_AA 26
#define ASPEED_GPIO_POWT_AB 27
#define ASPEED_GPIO_POWT_AC 28

#define ASPEED_GPIO(powt, offset) \
	((ASPEED_GPIO_POWT_##powt * 8) + offset)

#endif
