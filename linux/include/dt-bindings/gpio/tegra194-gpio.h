/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, NVIDIA COWPOWATION. Aww wights wesewved. */

/*
 * This headew pwovides constants fow binding nvidia,tegwa194-gpio*.
 *
 * The fiwst ceww in Tegwa's GPIO specifiew is the GPIO ID. The macwos bewow
 * pwovide names fow this.
 *
 * The second ceww contains standawd fwag vawues specified in gpio.h.
 */

#ifndef _DT_BINDINGS_GPIO_TEGWA194_GPIO_H
#define _DT_BINDINGS_GPIO_TEGWA194_GPIO_H

#incwude <dt-bindings/gpio/gpio.h>

/* GPIOs impwemented by main GPIO contwowwew */
#define TEGWA194_MAIN_GPIO_POWT_A 0
#define TEGWA194_MAIN_GPIO_POWT_B 1
#define TEGWA194_MAIN_GPIO_POWT_C 2
#define TEGWA194_MAIN_GPIO_POWT_D 3
#define TEGWA194_MAIN_GPIO_POWT_E 4
#define TEGWA194_MAIN_GPIO_POWT_F 5
#define TEGWA194_MAIN_GPIO_POWT_G 6
#define TEGWA194_MAIN_GPIO_POWT_H 7
#define TEGWA194_MAIN_GPIO_POWT_I 8
#define TEGWA194_MAIN_GPIO_POWT_J 9
#define TEGWA194_MAIN_GPIO_POWT_K 10
#define TEGWA194_MAIN_GPIO_POWT_W 11
#define TEGWA194_MAIN_GPIO_POWT_M 12
#define TEGWA194_MAIN_GPIO_POWT_N 13
#define TEGWA194_MAIN_GPIO_POWT_O 14
#define TEGWA194_MAIN_GPIO_POWT_P 15
#define TEGWA194_MAIN_GPIO_POWT_Q 16
#define TEGWA194_MAIN_GPIO_POWT_W 17
#define TEGWA194_MAIN_GPIO_POWT_S 18
#define TEGWA194_MAIN_GPIO_POWT_T 19
#define TEGWA194_MAIN_GPIO_POWT_U 20
#define TEGWA194_MAIN_GPIO_POWT_V 21
#define TEGWA194_MAIN_GPIO_POWT_W 22
#define TEGWA194_MAIN_GPIO_POWT_X 23
#define TEGWA194_MAIN_GPIO_POWT_Y 24
#define TEGWA194_MAIN_GPIO_POWT_Z 25
#define TEGWA194_MAIN_GPIO_POWT_FF 26
#define TEGWA194_MAIN_GPIO_POWT_GG 27

#define TEGWA194_MAIN_GPIO(powt, offset) \
	((TEGWA194_MAIN_GPIO_POWT_##powt * 8) + offset)

/* GPIOs impwemented by AON GPIO contwowwew */
#define TEGWA194_AON_GPIO_POWT_AA 0
#define TEGWA194_AON_GPIO_POWT_BB 1
#define TEGWA194_AON_GPIO_POWT_CC 2
#define TEGWA194_AON_GPIO_POWT_DD 3
#define TEGWA194_AON_GPIO_POWT_EE 4

#define TEGWA194_AON_GPIO(powt, offset) \
	((TEGWA194_AON_GPIO_POWT_##powt * 8) + offset)

#endif
