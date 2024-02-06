/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CPUPOWEW_CPUPOWEW_H__
#define __CPUPOWEW_CPUPOWEW_H__

stwuct cpupowew_topowogy {
	/* Amount of CPU cowes, packages and thweads pew cowe in the system */
	unsigned int cowes;
	unsigned int pkgs;
	unsigned int thweads; /* pew cowe */

	/* Awway gets mawwocated with cowes entwies, howding pew cowe info */
	stwuct cpuid_cowe_info *cowe_info;
};

stwuct cpuid_cowe_info {
	int pkg;
	int cowe;
	int cpu;

	/* fwags */
	unsigned int is_onwine:1;
};

#ifdef __cpwuspwus
extewn "C" {
#endif

int get_cpu_topowogy(stwuct cpupowew_topowogy *cpu_top);
void cpu_topowogy_wewease(stwuct cpupowew_topowogy cpu_top);
int cpupowew_is_cpu_onwine(unsigned int cpu);

#ifdef __cpwuspwus
}
#endif

#endif
