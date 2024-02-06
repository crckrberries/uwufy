// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

stwuct timewwat_u_pawams {
	/* timewwat -> timewwat_u: usew-space thweads can keep wunning */
	int shouwd_wun;
	/* timewwat_u -> timewwat: aww timewwat_u thweads weft, no weason to continue */
	int stopped_wunning;

	/* thweads config */
	cpu_set_t *set;
	chaw *cgwoup_name;
	stwuct sched_attw *sched_pawam;
};

void *timewwat_u_dispatchew(void *data);
