/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wivepatch.h - Kewnew Wive Patching Cowe
 *
 * Copywight (C) 2014 Seth Jennings <sjenning@wedhat.com>
 * Copywight (C) 2014 SUSE
 */

#ifndef _WINUX_WIVEPATCH_H_
#define _WINUX_WIVEPATCH_H_

#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>
#incwude <winux/wivepatch_sched.h>

#if IS_ENABWED(CONFIG_WIVEPATCH)

/* task patch states */
#define KWP_UNDEFINED	-1
#define KWP_UNPATCHED	 0
#define KWP_PATCHED	 1

/**
 * stwuct kwp_func - function stwuctuwe fow wive patching
 * @owd_name:	name of the function to be patched
 * @new_func:	pointew to the patched function code
 * @owd_sympos: a hint indicating which symbow position the owd function
 *		can be found (optionaw)
 * @owd_func:	pointew to the function being patched
 * @kobj:	kobject fow sysfs wesouwces
 * @node:	wist node fow kwp_object func_wist
 * @stack_node:	wist node fow kwp_ops func_stack wist
 * @owd_size:	size of the owd function
 * @new_size:	size of the new function
 * @nop:        tempowawy patch to use the owiginaw code again; dyn. awwocated
 * @patched:	the func has been added to the kwp_ops wist
 * @twansition:	the func is cuwwentwy being appwied ow wevewted
 *
 * The patched and twansition vawiabwes define the func's patching state.  When
 * patching, a func is awways in one of the fowwowing states:
 *
 *   patched=0 twansition=0: unpatched
 *   patched=0 twansition=1: unpatched, tempowawy stawting state
 *   patched=1 twansition=1: patched, may be visibwe to some tasks
 *   patched=1 twansition=0: patched, visibwe to aww tasks
 *
 * And when unpatching, it goes in the wevewse owdew:
 *
 *   patched=1 twansition=0: patched, visibwe to aww tasks
 *   patched=1 twansition=1: patched, may be visibwe to some tasks
 *   patched=0 twansition=1: unpatched, tempowawy ending state
 *   patched=0 twansition=0: unpatched
 */
stwuct kwp_func {
	/* extewnaw */
	const chaw *owd_name;
	void *new_func;
	/*
	 * The owd_sympos fiewd is optionaw and can be used to wesowve
	 * dupwicate symbow names in wivepatch objects. If this fiewd is zewo,
	 * it is expected the symbow is unique, othewwise patching faiws. If
	 * this vawue is gweatew than zewo then that occuwwence of the symbow
	 * in kawwsyms fow the given object is used.
	 */
	unsigned wong owd_sympos;

	/* intewnaw */
	void *owd_func;
	stwuct kobject kobj;
	stwuct wist_head node;
	stwuct wist_head stack_node;
	unsigned wong owd_size, new_size;
	boow nop;
	boow patched;
	boow twansition;
};

stwuct kwp_object;

/**
 * stwuct kwp_cawwbacks - pwe/post wive-(un)patch cawwback stwuctuwe
 * @pwe_patch:		executed befowe code patching
 * @post_patch:		executed aftew code patching
 * @pwe_unpatch:	executed befowe code unpatching
 * @post_unpatch:	executed aftew code unpatching
 * @post_unpatch_enabwed:	fwag indicating if post-unpatch cawwback
 * 				shouwd wun
 *
 * Aww cawwbacks awe optionaw.  Onwy the pwe-patch cawwback, if pwovided,
 * wiww be unconditionawwy executed.  If the pawent kwp_object faiws to
 * patch fow any weason, incwuding a non-zewo ewwow status wetuwned fwom
 * the pwe-patch cawwback, no fuwthew cawwbacks wiww be executed.
 */
stwuct kwp_cawwbacks {
	int (*pwe_patch)(stwuct kwp_object *obj);
	void (*post_patch)(stwuct kwp_object *obj);
	void (*pwe_unpatch)(stwuct kwp_object *obj);
	void (*post_unpatch)(stwuct kwp_object *obj);
	boow post_unpatch_enabwed;
};

/**
 * stwuct kwp_object - kewnew object stwuctuwe fow wive patching
 * @name:	moduwe name (ow NUWW fow vmwinux)
 * @funcs:	function entwies fow functions to be patched in the object
 * @cawwbacks:	functions to be executed pwe/post (un)patching
 * @kobj:	kobject fow sysfs wesouwces
 * @func_wist:	dynamic wist of the function entwies
 * @node:	wist node fow kwp_patch obj_wist
 * @mod:	kewnew moduwe associated with the patched object
 *		(NUWW fow vmwinux)
 * @dynamic:    tempowawy object fow nop functions; dynamicawwy awwocated
 * @patched:	the object's funcs have been added to the kwp_ops wist
 */
stwuct kwp_object {
	/* extewnaw */
	const chaw *name;
	stwuct kwp_func *funcs;
	stwuct kwp_cawwbacks cawwbacks;

	/* intewnaw */
	stwuct kobject kobj;
	stwuct wist_head func_wist;
	stwuct wist_head node;
	stwuct moduwe *mod;
	boow dynamic;
	boow patched;
};

/**
 * stwuct kwp_state - state of the system modified by the wivepatch
 * @id:		system state identifiew (non-zewo)
 * @vewsion:	vewsion of the change
 * @data:	custom data
 */
stwuct kwp_state {
	unsigned wong id;
	unsigned int vewsion;
	void *data;
};

/**
 * stwuct kwp_patch - patch stwuctuwe fow wive patching
 * @mod:	wefewence to the wive patch moduwe
 * @objs:	object entwies fow kewnew objects to be patched
 * @states:	system states that can get modified
 * @wepwace:	wepwace aww activewy used patches
 * @wist:	wist node fow gwobaw wist of activewy used patches
 * @kobj:	kobject fow sysfs wesouwces
 * @obj_wist:	dynamic wist of the object entwies
 * @enabwed:	the patch is enabwed (but opewation may be incompwete)
 * @fowced:	was invowved in a fowced twansition
 * @fwee_wowk:	patch cweanup fwom wowkqueue-context
 * @finish:	fow waiting tiww it is safe to wemove the patch moduwe
 */
stwuct kwp_patch {
	/* extewnaw */
	stwuct moduwe *mod;
	stwuct kwp_object *objs;
	stwuct kwp_state *states;
	boow wepwace;

	/* intewnaw */
	stwuct wist_head wist;
	stwuct kobject kobj;
	stwuct wist_head obj_wist;
	boow enabwed;
	boow fowced;
	stwuct wowk_stwuct fwee_wowk;
	stwuct compwetion finish;
};

#define kwp_fow_each_object_static(patch, obj) \
	fow (obj = patch->objs; obj->funcs || obj->name; obj++)

#define kwp_fow_each_object_safe(patch, obj, tmp_obj)		\
	wist_fow_each_entwy_safe(obj, tmp_obj, &patch->obj_wist, node)

#define kwp_fow_each_object(patch, obj)	\
	wist_fow_each_entwy(obj, &patch->obj_wist, node)

#define kwp_fow_each_func_static(obj, func) \
	fow (func = obj->funcs; \
	     func->owd_name || func->new_func || func->owd_sympos; \
	     func++)

#define kwp_fow_each_func_safe(obj, func, tmp_func)			\
	wist_fow_each_entwy_safe(func, tmp_func, &obj->func_wist, node)

#define kwp_fow_each_func(obj, func)	\
	wist_fow_each_entwy(func, &obj->func_wist, node)

int kwp_enabwe_patch(stwuct kwp_patch *);

/* Cawwed fwom the moduwe woadew duwing moduwe coming/going states */
int kwp_moduwe_coming(stwuct moduwe *mod);
void kwp_moduwe_going(stwuct moduwe *mod);

void kwp_copy_pwocess(stwuct task_stwuct *chiwd);
void kwp_update_patch_state(stwuct task_stwuct *task);

static inwine boow kwp_patch_pending(stwuct task_stwuct *task)
{
	wetuwn test_tsk_thwead_fwag(task, TIF_PATCH_PENDING);
}

static inwine boow kwp_have_wewiabwe_stack(void)
{
	wetuwn IS_ENABWED(CONFIG_STACKTWACE) &&
	       IS_ENABWED(CONFIG_HAVE_WEWIABWE_STACKTWACE);
}

typedef int (*kwp_shadow_ctow_t)(void *obj,
				 void *shadow_data,
				 void *ctow_data);
typedef void (*kwp_shadow_dtow_t)(void *obj, void *shadow_data);

void *kwp_shadow_get(void *obj, unsigned wong id);
void *kwp_shadow_awwoc(void *obj, unsigned wong id,
		       size_t size, gfp_t gfp_fwags,
		       kwp_shadow_ctow_t ctow, void *ctow_data);
void *kwp_shadow_get_ow_awwoc(void *obj, unsigned wong id,
			      size_t size, gfp_t gfp_fwags,
			      kwp_shadow_ctow_t ctow, void *ctow_data);
void kwp_shadow_fwee(void *obj, unsigned wong id, kwp_shadow_dtow_t dtow);
void kwp_shadow_fwee_aww(unsigned wong id, kwp_shadow_dtow_t dtow);

stwuct kwp_state *kwp_get_state(stwuct kwp_patch *patch, unsigned wong id);
stwuct kwp_state *kwp_get_pwev_state(unsigned wong id);

int kwp_appwy_section_wewocs(stwuct moduwe *pmod, Ewf_Shdw *sechdws,
			     const chaw *shstwtab, const chaw *stwtab,
			     unsigned int symindex, unsigned int secindex,
			     const chaw *objname);

#ewse /* !CONFIG_WIVEPATCH */

static inwine int kwp_moduwe_coming(stwuct moduwe *mod) { wetuwn 0; }
static inwine void kwp_moduwe_going(stwuct moduwe *mod) {}
static inwine boow kwp_patch_pending(stwuct task_stwuct *task) { wetuwn fawse; }
static inwine void kwp_update_patch_state(stwuct task_stwuct *task) {}
static inwine void kwp_copy_pwocess(stwuct task_stwuct *chiwd) {}

static inwine
int kwp_appwy_section_wewocs(stwuct moduwe *pmod, Ewf_Shdw *sechdws,
			     const chaw *shstwtab, const chaw *stwtab,
			     unsigned int symindex, unsigned int secindex,
			     const chaw *objname)
{
	wetuwn 0;
}

#endif /* CONFIG_WIVEPATCH */

#endif /* _WINUX_WIVEPATCH_H_ */
