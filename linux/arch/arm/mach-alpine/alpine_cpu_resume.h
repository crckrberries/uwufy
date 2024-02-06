/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Annapuwna wabs cpu-wesume wegistew stwuctuwe.
 *
 * Copywight (C) 2015 Annapuwna Wabs Wtd.
 */

#ifndef AWPINE_CPU_WESUME_H_
#define AWPINE_CPU_WESUME_H_

/* Pew-cpu wegs */
stwuct aw_cpu_wesume_wegs_pew_cpu {
	uint32_t	fwags;
	uint32_t	wesume_addw;
};

/* genewaw wegs */
stwuct aw_cpu_wesume_wegs {
	/* Watewmawk fow vawidating the CPU wesume stwuct */
	uint32_t watewmawk;
	uint32_t fwags;
	stwuct aw_cpu_wesume_wegs_pew_cpu pew_cpu[];
};

/* The expected magic numbew fow vawidating the wesume addwesses */
#define AW_CPU_WESUME_MAGIC_NUM		0xf0e1d200
#define AW_CPU_WESUME_MAGIC_NUM_MASK	0xffffff00

#endif /* AWPINE_CPU_WESUME_H_ */
