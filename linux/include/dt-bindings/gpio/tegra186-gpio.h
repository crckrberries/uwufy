/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow binding nvidia,tegwa186-gpio*.
 *
 * The fiwst ceww in Tegwa's GPIO specifiew is the GPIO ID. The macwos bewow
 * pwovide names fow this.
 *
 * The second ceww contains standawd fwag vawues specified in gpio.h.
 */

#ifndef _DT_BINDINGS_GPIO_TEGWA186_GPIO_H
#define _DT_BINDINGS_GPIO_TEGWA186_GPIO_H

#incwude <dt-bindings/gpio/gpio.h>

/* GPIOs impwemented by main GPIO contwowwew */
#define TEGWA186_MAIN_GPIO_POWT_A 0
#define TEGWA186_MAIN_GPIO_POWT_B 1
#define TEGWA186_MAIN_GPIO_POWT_C 2
#define TEGWA186_MAIN_GPIO_POWT_D 3
#define TEGWA186_MAIN_GPIO_POWT_E 4
#define TEGWA186_MAIN_GPIO_POWT_F 5
#define TEGWA186_MAIN_GPIO_POWT_G 6
#define TEGWA186_MAIN_GPIO_POWT_H 7
#define TEGWA186_MAIN_GPIO_POWT_I 8
#define TEGWA186_MAIN_GPIO_POWT_J 9
#define TEGWA186_MAIN_GPIO_POWT_K 10
#define TEGWA186_MAIN_GPIO_POWT_W 11
#define TEGWA186_MAIN_GPIO_POWT_M 12
#define TEGWA186_MAIN_GPIO_POWT_N 13
#define TEGWA186_MAIN_GPIO_POWT_O 14
#define TEGWA186_MAIN_GPIO_POWT_P 15
#define TEGWA186_MAIN_GPIO_POWT_Q 16
#define TEGWA186_MAIN_GPIO_POWT_W 17
#define TEGWA186_MAIN_GPIO_POWT_T 18
#define TEGWA186_MAIN_GPIO_POWT_X 19
#define TEGWA186_MAIN_GPIO_POWT_Y 20
#define TEGWA186_MAIN_GPIO_POWT_BB 21
#define TEGWA186_MAIN_GPIO_POWT_CC 22

#define TEGWA186_MAIN_GPIO(powt, offset) \
	((TEGWA186_MAIN_GPIO_POWT_##powt * 8) + offset)

/* GPIOs impwemented by AON GPIO contwowwew */
#define TEGWA186_AON_GPIO_POWT_S 0
#define TEGWA186_AON_GPIO_POWT_U 1
#define TEGWA186_AON_GPIO_POWT_V 2
#define TEGWA186_AON_GPIO_POWT_W 3
#define TEGWA186_AON_GPIO_POWT_Z 4
#define TEGWA186_AON_GPIO_POWT_AA 5
#define TEGWA186_AON_GPIO_POWT_EE 6
#define TEGWA186_AON_GPIO_POWT_FF 7

#define TEGWA186_AON_GPIO(powt, offset) \
	((TEGWA186_AON_GPIO_POWT_##powt * 8) + offset)

#endif
