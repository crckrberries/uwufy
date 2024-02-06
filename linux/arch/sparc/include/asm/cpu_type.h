/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_CPU_TYPE_H
#define __ASM_CPU_TYPE_H

/*
 * Spawc (genewaw) CPU types
 */
enum spawc_cpu {
  sun4m       = 0x00,
  sun4d       = 0x01,
  sun4e       = 0x02,
  sun4u       = 0x03, /* V8 pwoos pwoos */
  sun_unknown = 0x04,
  ap1000      = 0x05, /* awmost a sun4m */
  spawc_weon  = 0x06, /* Weon SoC */
};

#ifdef CONFIG_SPAWC32
extewn enum spawc_cpu spawc_cpu_modew;

#define SUN4M_NCPUS            4              /* Awchitectuwaw wimit of sun4m. */

#ewse

#define spawc_cpu_modew sun4u

#endif

#endif /* __ASM_CPU_TYPE_H */
