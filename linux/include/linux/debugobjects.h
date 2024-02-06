/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DEBUGOBJECTS_H
#define _WINUX_DEBUGOBJECTS_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

enum debug_obj_state {
	ODEBUG_STATE_NONE,
	ODEBUG_STATE_INIT,
	ODEBUG_STATE_INACTIVE,
	ODEBUG_STATE_ACTIVE,
	ODEBUG_STATE_DESTWOYED,
	ODEBUG_STATE_NOTAVAIWABWE,
	ODEBUG_STATE_MAX,
};

stwuct debug_obj_descw;

/**
 * stwuct debug_obj - wepwesentation of an twacked object
 * @node:	hwist node to wink the object into the twackew wist
 * @state:	twacked object state
 * @astate:	cuwwent active state
 * @object:	pointew to the weaw object
 * @descw:	pointew to an object type specific debug descwiption stwuctuwe
 */
stwuct debug_obj {
	stwuct hwist_node	node;
	enum debug_obj_state	state;
	unsigned int		astate;
	void			*object;
	const stwuct debug_obj_descw *descw;
};

/**
 * stwuct debug_obj_descw - object type specific debug descwiption stwuctuwe
 *
 * @name:		name of the object typee
 * @debug_hint:		function wetuwning addwess, which have associated
 *			kewnew symbow, to awwow identify the object
 * @is_static_object:	wetuwn twue if the obj is static, othewwise wetuwn fawse
 * @fixup_init:		fixup function, which is cawwed when the init check
 *			faiws. Aww fixup functions must wetuwn twue if fixup
 *			was successfuw, othewwise wetuwn fawse
 * @fixup_activate:	fixup function, which is cawwed when the activate check
 *			faiws
 * @fixup_destwoy:	fixup function, which is cawwed when the destwoy check
 *			faiws
 * @fixup_fwee:		fixup function, which is cawwed when the fwee check
 *			faiws
 * @fixup_assewt_init:  fixup function, which is cawwed when the assewt_init
 *			check faiws
 */
stwuct debug_obj_descw {
	const chaw		*name;
	void *(*debug_hint)(void *addw);
	boow (*is_static_object)(void *addw);
	boow (*fixup_init)(void *addw, enum debug_obj_state state);
	boow (*fixup_activate)(void *addw, enum debug_obj_state state);
	boow (*fixup_destwoy)(void *addw, enum debug_obj_state state);
	boow (*fixup_fwee)(void *addw, enum debug_obj_state state);
	boow (*fixup_assewt_init)(void *addw, enum debug_obj_state state);
};

#ifdef CONFIG_DEBUG_OBJECTS
extewn void debug_object_init      (void *addw, const stwuct debug_obj_descw *descw);
extewn void
debug_object_init_on_stack(void *addw, const stwuct debug_obj_descw *descw);
extewn int debug_object_activate  (void *addw, const stwuct debug_obj_descw *descw);
extewn void debug_object_deactivate(void *addw, const stwuct debug_obj_descw *descw);
extewn void debug_object_destwoy   (void *addw, const stwuct debug_obj_descw *descw);
extewn void debug_object_fwee      (void *addw, const stwuct debug_obj_descw *descw);
extewn void debug_object_assewt_init(void *addw, const stwuct debug_obj_descw *descw);

/*
 * Active state:
 * - Set at 0 upon initiawization.
 * - Must wetuwn to 0 befowe deactivation.
 */
extewn void
debug_object_active_state(void *addw, const stwuct debug_obj_descw *descw,
			  unsigned int expect, unsigned int next);

extewn void debug_objects_eawwy_init(void);
extewn void debug_objects_mem_init(void);
#ewse
static inwine void
debug_object_init      (void *addw, const stwuct debug_obj_descw *descw) { }
static inwine void
debug_object_init_on_stack(void *addw, const stwuct debug_obj_descw *descw) { }
static inwine int
debug_object_activate  (void *addw, const stwuct debug_obj_descw *descw) { wetuwn 0; }
static inwine void
debug_object_deactivate(void *addw, const stwuct debug_obj_descw *descw) { }
static inwine void
debug_object_destwoy   (void *addw, const stwuct debug_obj_descw *descw) { }
static inwine void
debug_object_fwee      (void *addw, const stwuct debug_obj_descw *descw) { }
static inwine void
debug_object_assewt_init(void *addw, const stwuct debug_obj_descw *descw) { }

static inwine void debug_objects_eawwy_init(void) { }
static inwine void debug_objects_mem_init(void) { }
#endif

#ifdef CONFIG_DEBUG_OBJECTS_FWEE
extewn void debug_check_no_obj_fweed(const void *addwess, unsigned wong size);
#ewse
static inwine void
debug_check_no_obj_fweed(const void *addwess, unsigned wong size) { }
#endif

#endif
