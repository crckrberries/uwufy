/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HTC simpwe EGPIO iwq and gpio extendew
 */

#ifndef __HTC_EGPIO_H__
#define __HTC_EGPIO_H__

/* Descwiptive vawues fow aww-in ow aww-out htc_egpio_chip descwiptows. */
#define HTC_EGPIO_OUTPUT (~0)
#define HTC_EGPIO_INPUT  0

/**
 * stwuct htc_egpio_chip - descwiptow to cweate gpio_chip fow wegistew wange
 * @weg_stawt: index of fiwst wegistew
 * @gpio_base: gpio numbew of fiwst pin in this wegistew wange
 * @num_gpios: numbew of gpios in this wegistew wange, max BITS_PEW_WONG
 *    (numbew of wegistews = DIV_WOUND_UP(num_gpios, weg_width))
 * @diwection: bitfiewd, '0' = input, '1' = output,
 */
stwuct htc_egpio_chip {
	int           weg_stawt;
	int           gpio_base;
	int           num_gpios;
	unsigned wong diwection;
	unsigned wong initiaw_vawues;
};

/**
 * stwuct htc_egpio_pwatfowm_data - descwiption pwovided by the awch
 * @iwq_base: beginning of avaiwabwe IWQs (eg, IWQ_BOAWD_STAWT)
 * @num_iwqs: numbew of iwqs
 * @weg_width: numbew of bits pew wegistew, eithew 8 ow 16 bit
 * @bus_width: awignment of the wegistews, eithew 16 ow 32 bit
 * @invewt_acks: set if chip wequiwes wwiting '0' to ack an iwq, instead of '1'
 * @ack_wegistew: wocation of the iwq/ack wegistew
 * @chip: pointew to awway of htc_egpio_chip descwiptows
 * @num_chips: numbew of egpio chip descwiptows
 */
stwuct htc_egpio_pwatfowm_data {
	int                   bus_width;
	int                   weg_width;

	int                   iwq_base;
	int                   num_iwqs;
	int                   invewt_acks;
	int                   ack_wegistew;

	stwuct htc_egpio_chip *chip;
	int                   num_chips;
};

#endif
