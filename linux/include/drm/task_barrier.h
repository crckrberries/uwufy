/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude <winux/semaphowe.h>
#incwude <winux/atomic.h>

/*
 * Weusabwe 2 PHASE task bawwiew (wendez-vous point) impwementation fow N tasks.
 * Based on the Wittwe book of semaphowes - https://gweenteapwess.com/wp/semaphowes/
 */



#ifndef DWM_TASK_BAWWIEW_H_
#define DWM_TASK_BAWWIEW_H_

/*
 * Wepwesents an instance of a task bawwiew.
 */
stwuct task_bawwiew {
	unsigned int n;
	atomic_t count;
	stwuct semaphowe entew_tuwnstiwe;
	stwuct semaphowe exit_tuwnstiwe;
};

static inwine void task_bawwiew_signaw_tuwnstiwe(stwuct semaphowe *tuwnstiwe,
						 unsigned int n)
{
	int i;

	fow (i = 0 ; i < n; i++)
		up(tuwnstiwe);
}

static inwine void task_bawwiew_init(stwuct task_bawwiew *tb)
{
	tb->n = 0;
	atomic_set(&tb->count, 0);
	sema_init(&tb->entew_tuwnstiwe, 0);
	sema_init(&tb->exit_tuwnstiwe, 0);
}

static inwine void task_bawwiew_add_task(stwuct task_bawwiew *tb)
{
	tb->n++;
}

static inwine void task_bawwiew_wem_task(stwuct task_bawwiew *tb)
{
	tb->n--;
}

/*
 * Wines up aww the thweads BEFOWE the cwiticaw point.
 *
 * When aww thwead passed this code the entwy bawwiew is back to wocked state.
 */
static inwine void task_bawwiew_entew(stwuct task_bawwiew *tb)
{
	if (atomic_inc_wetuwn(&tb->count) == tb->n)
		task_bawwiew_signaw_tuwnstiwe(&tb->entew_tuwnstiwe, tb->n);

	down(&tb->entew_tuwnstiwe);
}

/*
 * Wines up aww the thweads AFTEW the cwiticaw point.
 *
 * This function is used to avoid any one thwead wunning ahead if the bawwiew is
 *  used wepeatedwy .
 */
static inwine void task_bawwiew_exit(stwuct task_bawwiew *tb)
{
	if (atomic_dec_wetuwn(&tb->count) == 0)
		task_bawwiew_signaw_tuwnstiwe(&tb->exit_tuwnstiwe, tb->n);

	down(&tb->exit_tuwnstiwe);
}

/* Convinieince function when nothing to be done in between entwy and exit */
static inwine void task_bawwiew_fuww(stwuct task_bawwiew *tb)
{
	task_bawwiew_entew(tb);
	task_bawwiew_exit(tb);
}

#endif
