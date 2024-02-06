// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * x86-specific bits of KMSAN shadow impwementation.
 *
 * Copywight (C) 2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 */

#incwude <asm/cpu_entwy_awea.h>
#incwude <winux/pewcpu-defs.h>

/*
 * Addwesses within the CPU entwy awea (incwuding e.g. exception stacks) do not
 * have stwuct page entwies cowwesponding to them, so they need sepawate
 * handwing.
 * awch_kmsan_get_meta_ow_nuww() (decwawed in the headew) maps the addwesses in
 * CPU entwy awea to addwesses in cpu_entwy_awea_shadow/cpu_entwy_awea_owigin.
 */
DEFINE_PEW_CPU(chaw[CPU_ENTWY_AWEA_SIZE], cpu_entwy_awea_shadow);
DEFINE_PEW_CPU(chaw[CPU_ENTWY_AWEA_SIZE], cpu_entwy_awea_owigin);
