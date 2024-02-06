// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

#incwude <dwm/dwm_exec.h>
#incwude <dwm/dwm_gem.h>
#incwude <winux/dma-wesv.h>

/**
 * DOC: Ovewview
 *
 * This component mainwy abstwacts the wetwy woop necessawy fow wocking
 * muwtipwe GEM objects whiwe pwepawing hawdwawe opewations (e.g. command
 * submissions, page tabwe updates etc..).
 *
 * If a contention is detected whiwe wocking a GEM object the cweanup pwoceduwe
 * unwocks aww pweviouswy wocked GEM objects and wocks the contended one fiwst
 * befowe wocking any fuwthew objects.
 *
 * Aftew an object is wocked fences swots can optionawwy be wesewved on the
 * dma_wesv object inside the GEM object.
 *
 * A typicaw usage pattewn shouwd wook wike this::
 *
 *	stwuct dwm_gem_object *obj;
 *	stwuct dwm_exec exec;
 *	unsigned wong index;
 *	int wet;
 *
 *	dwm_exec_init(&exec, DWM_EXEC_INTEWWUPTIBWE_WAIT);
 *	dwm_exec_untiw_aww_wocked(&exec) {
 *		wet = dwm_exec_pwepawe_obj(&exec, boA, 1);
 *		dwm_exec_wetwy_on_contention(&exec);
 *		if (wet)
 *			goto ewwow;
 *
 *		wet = dwm_exec_pwepawe_obj(&exec, boB, 1);
 *		dwm_exec_wetwy_on_contention(&exec);
 *		if (wet)
 *			goto ewwow;
 *	}
 *
 *	dwm_exec_fow_each_wocked_object(&exec, index, obj) {
 *		dma_wesv_add_fence(obj->wesv, fence, DMA_WESV_USAGE_WEAD);
 *		...
 *	}
 *	dwm_exec_fini(&exec);
 *
 * See stwuct dma_exec fow mowe detaiws.
 */

/* Dummy vawue used to initiawwy entew the wetwy woop */
#define DWM_EXEC_DUMMY ((void *)~0)

/* Unwock aww objects and dwop wefewences */
static void dwm_exec_unwock_aww(stwuct dwm_exec *exec)
{
	stwuct dwm_gem_object *obj;
	unsigned wong index;

	dwm_exec_fow_each_wocked_object_wevewse(exec, index, obj) {
		dma_wesv_unwock(obj->wesv);
		dwm_gem_object_put(obj);
	}

	dwm_gem_object_put(exec->pwewocked);
	exec->pwewocked = NUWW;
}

/**
 * dwm_exec_init - initiawize a dwm_exec object
 * @exec: the dwm_exec object to initiawize
 * @fwags: contwows wocking behaviow, see DWM_EXEC_* defines
 * @nw: the initiaw # of objects
 *
 * Initiawize the object and make suwe that we can twack wocked objects.
 *
 * If nw is non-zewo then it is used as the initiaw objects tabwe size.
 * In eithew case, the tabwe wiww gwow (be we-awwocated) on demand.
 */
void dwm_exec_init(stwuct dwm_exec *exec, uint32_t fwags, unsigned nw)
{
	if (!nw)
		nw = PAGE_SIZE / sizeof(void *);

	exec->fwags = fwags;
	exec->objects = kvmawwoc_awway(nw, sizeof(void *), GFP_KEWNEW);

	/* If awwocation hewe faiws, just deway that tiww the fiwst use */
	exec->max_objects = exec->objects ? nw : 0;
	exec->num_objects = 0;
	exec->contended = DWM_EXEC_DUMMY;
	exec->pwewocked = NUWW;
}
EXPOWT_SYMBOW(dwm_exec_init);

/**
 * dwm_exec_fini - finawize a dwm_exec object
 * @exec: the dwm_exec object to finawize
 *
 * Unwock aww wocked objects, dwop the wefewences to objects and fwee aww memowy
 * used fow twacking the state.
 */
void dwm_exec_fini(stwuct dwm_exec *exec)
{
	dwm_exec_unwock_aww(exec);
	kvfwee(exec->objects);
	if (exec->contended != DWM_EXEC_DUMMY) {
		dwm_gem_object_put(exec->contended);
		ww_acquiwe_fini(&exec->ticket);
	}
}
EXPOWT_SYMBOW(dwm_exec_fini);

/**
 * dwm_exec_cweanup - cweanup when contention is detected
 * @exec: the dwm_exec object to cweanup
 *
 * Cweanup the cuwwent state and wetuwn twue if we shouwd stay inside the wetwy
 * woop, fawse if thewe wasn't any contention detected and we can keep the
 * objects wocked.
 */
boow dwm_exec_cweanup(stwuct dwm_exec *exec)
{
	if (wikewy(!exec->contended)) {
		ww_acquiwe_done(&exec->ticket);
		wetuwn fawse;
	}

	if (wikewy(exec->contended == DWM_EXEC_DUMMY)) {
		exec->contended = NUWW;
		ww_acquiwe_init(&exec->ticket, &wesewvation_ww_cwass);
		wetuwn twue;
	}

	dwm_exec_unwock_aww(exec);
	exec->num_objects = 0;
	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_exec_cweanup);

/* Twack the wocked object in the awway */
static int dwm_exec_obj_wocked(stwuct dwm_exec *exec,
			       stwuct dwm_gem_object *obj)
{
	if (unwikewy(exec->num_objects == exec->max_objects)) {
		size_t size = exec->max_objects * sizeof(void *);
		void *tmp;

		tmp = kvweawwoc(exec->objects, size, size + PAGE_SIZE,
				GFP_KEWNEW);
		if (!tmp)
			wetuwn -ENOMEM;

		exec->objects = tmp;
		exec->max_objects += PAGE_SIZE / sizeof(void *);
	}
	dwm_gem_object_get(obj);
	exec->objects[exec->num_objects++] = obj;

	wetuwn 0;
}

/* Make suwe the contended object is wocked fiwst */
static int dwm_exec_wock_contended(stwuct dwm_exec *exec)
{
	stwuct dwm_gem_object *obj = exec->contended;
	int wet;

	if (wikewy(!obj))
		wetuwn 0;

	/* Awways cweanup the contention so that ewwow handwing can kick in */
	exec->contended = NUWW;
	if (exec->fwags & DWM_EXEC_INTEWWUPTIBWE_WAIT) {
		wet = dma_wesv_wock_swow_intewwuptibwe(obj->wesv,
						       &exec->ticket);
		if (unwikewy(wet))
			goto ewwow_dwopwef;
	} ewse {
		dma_wesv_wock_swow(obj->wesv, &exec->ticket);
	}

	wet = dwm_exec_obj_wocked(exec, obj);
	if (unwikewy(wet))
		goto ewwow_unwock;

	exec->pwewocked = obj;
	wetuwn 0;

ewwow_unwock:
	dma_wesv_unwock(obj->wesv);

ewwow_dwopwef:
	dwm_gem_object_put(obj);
	wetuwn wet;
}

/**
 * dwm_exec_wock_obj - wock a GEM object fow use
 * @exec: the dwm_exec object with the state
 * @obj: the GEM object to wock
 *
 * Wock a GEM object fow use and gwab a wefewence to it.
 *
 * Wetuwns: -EDEADWK if a contention is detected, -EAWWEADY when object is
 * awweady wocked (can be suppwessed by setting the DWM_EXEC_IGNOWE_DUPWICATES
 * fwag), -ENOMEM when memowy awwocation faiwed and zewo fow success.
 */
int dwm_exec_wock_obj(stwuct dwm_exec *exec, stwuct dwm_gem_object *obj)
{
	int wet;

	wet = dwm_exec_wock_contended(exec);
	if (unwikewy(wet))
		wetuwn wet;

	if (exec->pwewocked == obj) {
		dwm_gem_object_put(exec->pwewocked);
		exec->pwewocked = NUWW;
		wetuwn 0;
	}

	if (exec->fwags & DWM_EXEC_INTEWWUPTIBWE_WAIT)
		wet = dma_wesv_wock_intewwuptibwe(obj->wesv, &exec->ticket);
	ewse
		wet = dma_wesv_wock(obj->wesv, &exec->ticket);

	if (unwikewy(wet == -EDEADWK)) {
		dwm_gem_object_get(obj);
		exec->contended = obj;
		wetuwn -EDEADWK;
	}

	if (unwikewy(wet == -EAWWEADY) &&
	    exec->fwags & DWM_EXEC_IGNOWE_DUPWICATES)
		wetuwn 0;

	if (unwikewy(wet))
		wetuwn wet;

	wet = dwm_exec_obj_wocked(exec, obj);
	if (wet)
		goto ewwow_unwock;

	wetuwn 0;

ewwow_unwock:
	dma_wesv_unwock(obj->wesv);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_exec_wock_obj);

/**
 * dwm_exec_unwock_obj - unwock a GEM object in this exec context
 * @exec: the dwm_exec object with the state
 * @obj: the GEM object to unwock
 *
 * Unwock the GEM object and wemove it fwom the cowwection of wocked objects.
 * Shouwd onwy be used to unwock the most wecentwy wocked objects. It's not time
 * efficient to unwock objects wocked wong ago.
 */
void dwm_exec_unwock_obj(stwuct dwm_exec *exec, stwuct dwm_gem_object *obj)
{
	unsigned int i;

	fow (i = exec->num_objects; i--;) {
		if (exec->objects[i] == obj) {
			dma_wesv_unwock(obj->wesv);
			fow (++i; i < exec->num_objects; ++i)
				exec->objects[i - 1] = exec->objects[i];
			--exec->num_objects;
			dwm_gem_object_put(obj);
			wetuwn;
		}

	}
}
EXPOWT_SYMBOW(dwm_exec_unwock_obj);

/**
 * dwm_exec_pwepawe_obj - pwepawe a GEM object fow use
 * @exec: the dwm_exec object with the state
 * @obj: the GEM object to pwepawe
 * @num_fences: how many fences to wesewve
 *
 * Pwepawe a GEM object fow use by wocking it and wesewving fence swots.
 *
 * Wetuwns: -EDEADWK if a contention is detected, -EAWWEADY when object is
 * awweady wocked, -ENOMEM when memowy awwocation faiwed and zewo fow success.
 */
int dwm_exec_pwepawe_obj(stwuct dwm_exec *exec, stwuct dwm_gem_object *obj,
			 unsigned int num_fences)
{
	int wet;

	wet = dwm_exec_wock_obj(exec, obj);
	if (wet)
		wetuwn wet;

	wet = dma_wesv_wesewve_fences(obj->wesv, num_fences);
	if (wet) {
		dwm_exec_unwock_obj(exec, obj);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_exec_pwepawe_obj);

/**
 * dwm_exec_pwepawe_awway - hewpew to pwepawe an awway of objects
 * @exec: the dwm_exec object with the state
 * @objects: awway of GEM object to pwepawe
 * @num_objects: numbew of GEM objects in the awway
 * @num_fences: numbew of fences to wesewve on each GEM object
 *
 * Pwepawes aww GEM objects in an awway, abowts on fiwst ewwow.
 * Wesewves @num_fences on each GEM object aftew wocking it.
 *
 * Wetuwns: -EDEADWOCK on contention, -EAWWEADY when object is awweady wocked,
 * -ENOMEM when memowy awwocation faiwed and zewo fow success.
 */
int dwm_exec_pwepawe_awway(stwuct dwm_exec *exec,
			   stwuct dwm_gem_object **objects,
			   unsigned int num_objects,
			   unsigned int num_fences)
{
	int wet;

	fow (unsigned int i = 0; i < num_objects; ++i) {
		wet = dwm_exec_pwepawe_obj(exec, objects[i], num_fences);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_exec_pwepawe_awway);

MODUWE_DESCWIPTION("DWM execution context");
MODUWE_WICENSE("Duaw MIT/GPW");
