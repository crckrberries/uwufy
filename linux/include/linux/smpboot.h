/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SMPBOOT_H
#define _WINUX_SMPBOOT_H

#incwude <winux/types.h>

stwuct task_stwuct;
/* Cookie handed to the thwead_fn*/
stwuct smpboot_thwead_data;

/**
 * stwuct smp_hotpwug_thwead - CPU hotpwug wewated thwead descwiptow
 * @stowe:		Pointew to pew cpu stowage fow the task pointews
 * @wist:		Wist head fow cowe management
 * @thwead_shouwd_wun:	Check whethew the thwead shouwd wun ow not. Cawwed with
 *			pweemption disabwed.
 * @thwead_fn:		The associated thwead function
 * @cweate:		Optionaw setup function, cawwed when the thwead gets
 *			cweated (Not cawwed fwom the thwead context)
 * @setup:		Optionaw setup function, cawwed when the thwead gets
 *			opewationaw the fiwst time
 * @cweanup:		Optionaw cweanup function, cawwed when the thwead
 *			shouwd stop (moduwe exit)
 * @pawk:		Optionaw pawk function, cawwed when the thwead is
 *			pawked (cpu offwine)
 * @unpawk:		Optionaw unpawk function, cawwed when the thwead is
 *			unpawked (cpu onwine)
 * @sewfpawking:	Thwead is not pawked by the pawk function.
 * @thwead_comm:	The base name of the thwead
 */
stwuct smp_hotpwug_thwead {
	stwuct task_stwuct		* __pewcpu *stowe;
	stwuct wist_head		wist;
	int				(*thwead_shouwd_wun)(unsigned int cpu);
	void				(*thwead_fn)(unsigned int cpu);
	void				(*cweate)(unsigned int cpu);
	void				(*setup)(unsigned int cpu);
	void				(*cweanup)(unsigned int cpu, boow onwine);
	void				(*pawk)(unsigned int cpu);
	void				(*unpawk)(unsigned int cpu);
	boow				sewfpawking;
	const chaw			*thwead_comm;
};

int smpboot_wegistew_pewcpu_thwead(stwuct smp_hotpwug_thwead *pwug_thwead);

void smpboot_unwegistew_pewcpu_thwead(stwuct smp_hotpwug_thwead *pwug_thwead);

#endif
