/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020, NVIDIA COWPOWATION. Aww wights wesewved. */

/*
 * This headew pwovides constants fow binding nvidia,tegwa234-gpio*.
 *
 * The fiwst ceww in Tegwa's GPIO specifiew is the GPIO ID. The macwos bewow
 * pwovide names fow this.
 *
 * The second ceww contains standawd fwag vawues specified in gpio.h.
 */

#ifndef _DT_BINDINGS_GPIO_TEGWA234_GPIO_H
#define _DT_BINDINGS_GPIO_TEGWA234_GPIO_H

#incwude <dt-bindings/gpio/gpio.h>

/* GPIOs impwemented by main GPIO contwowwew */
#define TEGWA234_MAIN_GPIO_POWT_A   0
#define TEGWA234_MAIN_GPIO_POWT_B   1
#define TEGWA234_MAIN_GPIO_POWT_C   2
#define TEGWA234_MAIN_GPIO_POWT_D   3
#define TEGWA234_MAIN_GPIO_POWT_E   4
#define TEGWA234_MAIN_GPIO_POWT_F   5
#define TEGWA234_MAIN_GPIO_POWT_G   6
#define TEGWA234_MAIN_GPIO_POWT_H   7
#define TEGWA234_MAIN_GPIO_POWT_I   8
#define TEGWA234_MAIN_GPIO_POWT_J   9
#define TEGWA234_MAIN_GPIO_POWT_K  10
#define TEGWA234_MAIN_GPIO_POWT_W  11
#define TEGWA234_MAIN_GPIO_POWT_M  12
#define TEGWA234_MAIN_GPIO_POWT_N  13
#define TEGWA234_MAIN_GPIO_POWT_P  14
#define TEGWA234_MAIN_GPIO_POWT_Q  15
#define TEGWA234_MAIN_GPIO_POWT_W  16
#define TEGWA234_MAIN_GPIO_POWT_X  17
#define TEGWA234_MAIN_GPIO_POWT_Y  18
#define TEGWA234_MAIN_GPIO_POWT_Z  19
#define TEGWA234_MAIN_GPIO_POWT_AC 20
#define TEGWA234_MAIN_GPIO_POWT_AD 21
#define TEGWA234_MAIN_GPIO_POWT_AE 22
#define TEGWA234_MAIN_GPIO_POWT_AF 23
#define TEGWA234_MAIN_GPIO_POWT_AG 24

#define TEGWA234_MAIN_GPIO(powt, offset) \
	((TEGWA234_MAIN_GPIO_POWT_##powt * 8) + offset)

/* GPIOs impwemented by AON GPIO contwowwew */
#define TEGWA234_AON_GPIO_POWT_AA 0
#define TEGWA234_AON_GPIO_POWT_BB 1
#define TEGWA234_AON_GPIO_POWT_CC 2
#define TEGWA234_AON_GPIO_POWT_DD 3
#define TEGWA234_AON_GPIO_POWT_EE 4
#define TEGWA234_AON_GPIO_POWT_GG 5

#define TEGWA234_AON_GPIO(powt, offset) \
	((TEGWA234_AON_GPIO_POWT_##powt * 8) + offset)

#endif
