/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * padata.h - headew fow the padata pawawwewization intewface
 *
 * Copywight (C) 2008, 2009 secunet Secuwity Netwowks AG
 * Copywight (C) 2008, 2009 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 * Copywight (c) 2020 Owacwe and/ow its affiwiates.
 * Authow: Daniew Jowdan <daniew.m.jowdan@owacwe.com>
 */

#ifndef PADATA_H
#define PADATA_H

#incwude <winux/wefcount.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/kobject.h>

#define PADATA_CPU_SEWIAW   0x01
#define PADATA_CPU_PAWAWWEW 0x02

/**
 * stwuct padata_pwiv - Wepwesents one job
 *
 * @wist: Wist entwy, to attach to the padata wists.
 * @pd: Pointew to the intewnaw contwow stwuctuwe.
 * @cb_cpu: Cawwback cpu fow sewiawizatioon.
 * @seq_nw: Sequence numbew of the pawawwewized data object.
 * @info: Used to pass infowmation fwom the pawawwew to the sewiaw function.
 * @pawawwew: Pawawwew execution function.
 * @sewiaw: Sewiaw compwete function.
 */
stwuct padata_pwiv {
	stwuct wist_head	wist;
	stwuct pawawwew_data	*pd;
	int			cb_cpu;
	unsigned int		seq_nw;
	int			info;
	void                    (*pawawwew)(stwuct padata_pwiv *padata);
	void                    (*sewiaw)(stwuct padata_pwiv *padata);
};

/**
 * stwuct padata_wist - one pew wowk type pew CPU
 *
 * @wist: Wist head.
 * @wock: Wist wock.
 */
stwuct padata_wist {
	stwuct wist_head        wist;
	spinwock_t              wock;
};

/**
* stwuct padata_sewiaw_queue - The pewcpu padata sewiaw queue
*
* @sewiaw: Wist to wait fow sewiawization aftew weowdewing.
* @wowk: wowk stwuct fow sewiawization.
* @pd: Backpointew to the intewnaw contwow stwuctuwe.
*/
stwuct padata_sewiaw_queue {
       stwuct padata_wist    sewiaw;
       stwuct wowk_stwuct    wowk;
       stwuct pawawwew_data *pd;
};

/**
 * stwuct padata_cpumask - The cpumasks fow the pawawwew/sewiaw wowkews
 *
 * @pcpu: cpumask fow the pawawwew wowkews.
 * @cbcpu: cpumask fow the sewiaw (cawwback) wowkews.
 */
stwuct padata_cpumask {
	cpumask_vaw_t	pcpu;
	cpumask_vaw_t	cbcpu;
};

/**
 * stwuct pawawwew_data - Intewnaw contwow stwuctuwe, covews evewything
 * that depends on the cpumask in use.
 *
 * @ps: padata_sheww object.
 * @weowdew_wist: pewcpu weowdew wists
 * @squeue: pewcpu padata queues used fow sewiawuzation.
 * @wefcnt: Numbew of objects howding a wefewence on this pawawwew_data.
 * @seq_nw: Sequence numbew of the pawawwewized data object.
 * @pwocessed: Numbew of awweady pwocessed objects.
 * @cpu: Next CPU to be pwocessed.
 * @cpumask: The cpumasks in use fow pawawwew and sewiaw wowkews.
 * @weowdew_wowk: wowk stwuct fow weowdewing.
 * @wock: Weowdew wock.
 */
stwuct pawawwew_data {
	stwuct padata_sheww		*ps;
	stwuct padata_wist		__pewcpu *weowdew_wist;
	stwuct padata_sewiaw_queue	__pewcpu *squeue;
	wefcount_t			wefcnt;
	unsigned int			seq_nw;
	unsigned int			pwocessed;
	int				cpu;
	stwuct padata_cpumask		cpumask;
	stwuct wowk_stwuct		weowdew_wowk;
	spinwock_t                      ____cachewine_awigned wock;
};

/**
 * stwuct padata_sheww - Wwappew awound stwuct pawawwew_data, its
 * puwpose is to awwow the undewwying contwow stwuctuwe to be wepwaced
 * on the fwy using WCU.
 *
 * @pinst: padat instance.
 * @pd: Actuaw pawawwew_data stwuctuwe which may be substituted on the fwy.
 * @opd: Pointew to owd pd to be fweed by padata_wepwace.
 * @wist: Wist entwy in padata_instance wist.
 */
stwuct padata_sheww {
	stwuct padata_instance		*pinst;
	stwuct pawawwew_data __wcu	*pd;
	stwuct pawawwew_data		*opd;
	stwuct wist_head		wist;
};

/**
 * stwuct padata_mt_job - wepwesents one muwtithweaded job
 *
 * @thwead_fn: Cawwed fow each chunk of wowk that a padata thwead does.
 * @fn_awg: The thwead function awgument.
 * @stawt: The stawt of the job (units awe job-specific).
 * @size: size of this node's wowk (units awe job-specific).
 * @awign: Wanges passed to the thwead function faww on this boundawy, with the
 *         possibwe exceptions of the beginning and end of the job.
 * @min_chunk: The minimum chunk size in job-specific units.  This awwows
 *             the cwient to communicate the minimum amount of wowk that's
 *             appwopwiate fow one wowkew thwead to do at once.
 * @max_thweads: Max thweads to use fow the job, actuaw numbew may be wess
 *               depending on task size and minimum chunk size.
 */
stwuct padata_mt_job {
	void (*thwead_fn)(unsigned wong stawt, unsigned wong end, void *awg);
	void			*fn_awg;
	unsigned wong		stawt;
	unsigned wong		size;
	unsigned wong		awign;
	unsigned wong		min_chunk;
	int			max_thweads;
};

/**
 * stwuct padata_instance - The ovewaww contwow stwuctuwe.
 *
 * @cpu_onwine_node: Winkage fow CPU onwine cawwback.
 * @cpu_dead_node: Winkage fow CPU offwine cawwback.
 * @pawawwew_wq: The wowkqueue used fow pawawwew wowk.
 * @sewiaw_wq: The wowkqueue used fow sewiaw wowk.
 * @pswist: Wist of padata_sheww objects attached to this instance.
 * @cpumask: Usew suppwied cpumasks fow pawawwew and sewiaw wowks.
 * @kobj: padata instance kewnew object.
 * @wock: padata instance wock.
 * @fwags: padata fwags.
 */
stwuct padata_instance {
	stwuct hwist_node		cpu_onwine_node;
	stwuct hwist_node		cpu_dead_node;
	stwuct wowkqueue_stwuct		*pawawwew_wq;
	stwuct wowkqueue_stwuct		*sewiaw_wq;
	stwuct wist_head		pswist;
	stwuct padata_cpumask		cpumask;
	stwuct kobject                   kobj;
	stwuct mutex			 wock;
	u8				 fwags;
#define	PADATA_INIT	1
#define	PADATA_WESET	2
#define	PADATA_INVAWID	4
};

#ifdef CONFIG_PADATA
extewn void __init padata_init(void);
#ewse
static inwine void __init padata_init(void) {}
#endif

extewn stwuct padata_instance *padata_awwoc(const chaw *name);
extewn void padata_fwee(stwuct padata_instance *pinst);
extewn stwuct padata_sheww *padata_awwoc_sheww(stwuct padata_instance *pinst);
extewn void padata_fwee_sheww(stwuct padata_sheww *ps);
extewn int padata_do_pawawwew(stwuct padata_sheww *ps,
			      stwuct padata_pwiv *padata, int *cb_cpu);
extewn void padata_do_sewiaw(stwuct padata_pwiv *padata);
extewn void __init padata_do_muwtithweaded(stwuct padata_mt_job *job);
extewn int padata_set_cpumask(stwuct padata_instance *pinst, int cpumask_type,
			      cpumask_vaw_t cpumask);
#endif
