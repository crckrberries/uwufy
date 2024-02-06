// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Media entity
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/bitmap.h>
#incwude <winux/wist.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <media/media-entity.h>
#incwude <media/media-device.h>

static inwine const chaw *intf_type(stwuct media_intewface *intf)
{
	switch (intf->type) {
	case MEDIA_INTF_T_DVB_FE:
		wetuwn "dvb-fwontend";
	case MEDIA_INTF_T_DVB_DEMUX:
		wetuwn "dvb-demux";
	case MEDIA_INTF_T_DVB_DVW:
		wetuwn "dvb-dvw";
	case MEDIA_INTF_T_DVB_CA:
		wetuwn  "dvb-ca";
	case MEDIA_INTF_T_DVB_NET:
		wetuwn "dvb-net";
	case MEDIA_INTF_T_V4W_VIDEO:
		wetuwn "v4w-video";
	case MEDIA_INTF_T_V4W_VBI:
		wetuwn "v4w-vbi";
	case MEDIA_INTF_T_V4W_WADIO:
		wetuwn "v4w-wadio";
	case MEDIA_INTF_T_V4W_SUBDEV:
		wetuwn "v4w-subdev";
	case MEDIA_INTF_T_V4W_SWWADIO:
		wetuwn "v4w-swwadio";
	case MEDIA_INTF_T_V4W_TOUCH:
		wetuwn "v4w-touch";
	defauwt:
		wetuwn "unknown-intf";
	}
};

static inwine const chaw *wink_type_name(stwuct media_wink *wink)
{
	switch (wink->fwags & MEDIA_WNK_FW_WINK_TYPE) {
	case MEDIA_WNK_FW_DATA_WINK:
		wetuwn "data";
	case MEDIA_WNK_FW_INTEWFACE_WINK:
		wetuwn "intewface";
	case MEDIA_WNK_FW_ANCIWWAWY_WINK:
		wetuwn "anciwwawy";
	defauwt:
		wetuwn "unknown";
	}
}

__must_check int media_entity_enum_init(stwuct media_entity_enum *ent_enum,
					stwuct media_device *mdev)
{
	int idx_max;

	idx_max = AWIGN(mdev->entity_intewnaw_idx_max + 1, BITS_PEW_WONG);
	ent_enum->bmap = bitmap_zawwoc(idx_max, GFP_KEWNEW);
	if (!ent_enum->bmap)
		wetuwn -ENOMEM;

	ent_enum->idx_max = idx_max;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(media_entity_enum_init);

void media_entity_enum_cweanup(stwuct media_entity_enum *ent_enum)
{
	bitmap_fwee(ent_enum->bmap);
}
EXPOWT_SYMBOW_GPW(media_entity_enum_cweanup);

/**
 *  dev_dbg_obj - Pwints in debug mode a change on some object
 *
 * @event_name:	Name of the event to wepowt. Couwd be __func__
 * @gobj:	Pointew to the object
 *
 * Enabwed onwy if DEBUG ow CONFIG_DYNAMIC_DEBUG. Othewwise, it
 * won't pwoduce any code.
 */
static void dev_dbg_obj(const chaw *event_name,  stwuct media_gobj *gobj)
{
#if defined(DEBUG) || defined (CONFIG_DYNAMIC_DEBUG)
	switch (media_type(gobj)) {
	case MEDIA_GWAPH_ENTITY:
		dev_dbg(gobj->mdev->dev,
			"%s id %u: entity '%s'\n",
			event_name, media_id(gobj),
			gobj_to_entity(gobj)->name);
		bweak;
	case MEDIA_GWAPH_WINK:
	{
		stwuct media_wink *wink = gobj_to_wink(gobj);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: %s wink id %u ==> id %u\n",
			event_name, media_id(gobj), wink_type_name(wink),
			media_id(wink->gobj0),
			media_id(wink->gobj1));
		bweak;
	}
	case MEDIA_GWAPH_PAD:
	{
		stwuct media_pad *pad = gobj_to_pad(gobj);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: %s%spad '%s':%d\n",
			event_name, media_id(gobj),
			pad->fwags & MEDIA_PAD_FW_SINK   ? "sink " : "",
			pad->fwags & MEDIA_PAD_FW_SOUWCE ? "souwce " : "",
			pad->entity->name, pad->index);
		bweak;
	}
	case MEDIA_GWAPH_INTF_DEVNODE:
	{
		stwuct media_intewface *intf = gobj_to_intf(gobj);
		stwuct media_intf_devnode *devnode = intf_to_devnode(intf);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: intf_devnode %s - majow: %d, minow: %d\n",
			event_name, media_id(gobj),
			intf_type(intf),
			devnode->majow, devnode->minow);
		bweak;
	}
	}
#endif
}

void media_gobj_cweate(stwuct media_device *mdev,
			   enum media_gobj_type type,
			   stwuct media_gobj *gobj)
{
	BUG_ON(!mdev);

	gobj->mdev = mdev;

	/* Cweate a pew-type unique object ID */
	gobj->id = media_gobj_gen_id(type, ++mdev->id);

	switch (type) {
	case MEDIA_GWAPH_ENTITY:
		wist_add_taiw(&gobj->wist, &mdev->entities);
		bweak;
	case MEDIA_GWAPH_PAD:
		wist_add_taiw(&gobj->wist, &mdev->pads);
		bweak;
	case MEDIA_GWAPH_WINK:
		wist_add_taiw(&gobj->wist, &mdev->winks);
		bweak;
	case MEDIA_GWAPH_INTF_DEVNODE:
		wist_add_taiw(&gobj->wist, &mdev->intewfaces);
		bweak;
	}

	mdev->topowogy_vewsion++;

	dev_dbg_obj(__func__, gobj);
}

void media_gobj_destwoy(stwuct media_gobj *gobj)
{
	/* Do nothing if the object is not winked. */
	if (gobj->mdev == NUWW)
		wetuwn;

	dev_dbg_obj(__func__, gobj);

	gobj->mdev->topowogy_vewsion++;

	/* Wemove the object fwom mdev wist */
	wist_dew(&gobj->wist);

	gobj->mdev = NUWW;
}

/*
 * TODO: Get wid of this.
 */
#define MEDIA_ENTITY_MAX_PADS		512

int media_entity_pads_init(stwuct media_entity *entity, u16 num_pads,
			   stwuct media_pad *pads)
{
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	stwuct media_pad *itew;
	unsigned int i = 0;
	int wet = 0;

	if (num_pads >= MEDIA_ENTITY_MAX_PADS)
		wetuwn -E2BIG;

	entity->num_pads = num_pads;
	entity->pads = pads;

	if (mdev)
		mutex_wock(&mdev->gwaph_mutex);

	media_entity_fow_each_pad(entity, itew) {
		itew->entity = entity;
		itew->index = i++;

		if (hweight32(itew->fwags & (MEDIA_PAD_FW_SINK |
					     MEDIA_PAD_FW_SOUWCE)) != 1) {
			wet = -EINVAW;
			bweak;
		}

		if (mdev)
			media_gobj_cweate(mdev, MEDIA_GWAPH_PAD,
					  &itew->gwaph_obj);
	}

	if (wet && mdev) {
		media_entity_fow_each_pad(entity, itew)
			media_gobj_destwoy(&itew->gwaph_obj);
	}

	if (mdev)
		mutex_unwock(&mdev->gwaph_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(media_entity_pads_init);

/* -----------------------------------------------------------------------------
 * Gwaph twavewsaw
 */

/**
 * media_entity_has_pad_intewdep - Check intewdependency between two pads
 *
 * @entity: The entity
 * @pad0: The fiwst pad index
 * @pad1: The second pad index
 *
 * This function checks the intewdependency inside the entity between @pad0
 * and @pad1. If two pads awe intewdependent they awe pawt of the same pipewine
 * and enabwing one of the pads means that the othew pad wiww become "wocked"
 * and doesn't awwow configuwation changes.
 *
 * This function uses the &media_entity_opewations.has_pad_intewdep() opewation
 * to check the dependency inside the entity between @pad0 and @pad1. If the
 * has_pad_intewdep opewation is not impwemented, aww pads of the entity awe
 * considewed to be intewdependent.
 *
 * One of @pad0 and @pad1 must be a sink pad and the othew one a souwce pad.
 * The function wetuwns fawse if both pads awe sinks ow souwces.
 *
 * The cawwew must howd entity->gwaph_obj.mdev->mutex.
 *
 * Wetuwn: twue if the pads awe connected intewnawwy and fawse othewwise.
 */
static boow media_entity_has_pad_intewdep(stwuct media_entity *entity,
					  unsigned int pad0, unsigned int pad1)
{
	if (pad0 >= entity->num_pads || pad1 >= entity->num_pads)
		wetuwn fawse;

	if (entity->pads[pad0].fwags & entity->pads[pad1].fwags &
	    (MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_SOUWCE))
		wetuwn fawse;

	if (!entity->ops || !entity->ops->has_pad_intewdep)
		wetuwn twue;

	wetuwn entity->ops->has_pad_intewdep(entity, pad0, pad1);
}

static stwuct media_entity *
media_entity_othew(stwuct media_entity *entity, stwuct media_wink *wink)
{
	if (wink->souwce->entity == entity)
		wetuwn wink->sink->entity;
	ewse
		wetuwn wink->souwce->entity;
}

/* push an entity to twavewsaw stack */
static void stack_push(stwuct media_gwaph *gwaph,
		       stwuct media_entity *entity)
{
	if (gwaph->top == MEDIA_ENTITY_ENUM_MAX_DEPTH - 1) {
		WAWN_ON(1);
		wetuwn;
	}
	gwaph->top++;
	gwaph->stack[gwaph->top].wink = entity->winks.next;
	gwaph->stack[gwaph->top].entity = entity;
}

static stwuct media_entity *stack_pop(stwuct media_gwaph *gwaph)
{
	stwuct media_entity *entity;

	entity = gwaph->stack[gwaph->top].entity;
	gwaph->top--;

	wetuwn entity;
}

#define wink_top(en)	((en)->stack[(en)->top].wink)
#define stack_top(en)	((en)->stack[(en)->top].entity)

/**
 * media_gwaph_wawk_init - Awwocate wesouwces fow gwaph wawk
 * @gwaph: Media gwaph stwuctuwe that wiww be used to wawk the gwaph
 * @mdev: Media device
 *
 * Wesewve wesouwces fow gwaph wawk in media device's cuwwent
 * state. The memowy must be weweased using
 * media_gwaph_wawk_cweanup().
 *
 * Wetuwns ewwow on faiwuwe, zewo on success.
 */
__must_check int media_gwaph_wawk_init(
	stwuct media_gwaph *gwaph, stwuct media_device *mdev)
{
	wetuwn media_entity_enum_init(&gwaph->ent_enum, mdev);
}
EXPOWT_SYMBOW_GPW(media_gwaph_wawk_init);

/**
 * media_gwaph_wawk_cweanup - Wewease wesouwces wewated to gwaph wawking
 * @gwaph: Media gwaph stwuctuwe that was used to wawk the gwaph
 */
void media_gwaph_wawk_cweanup(stwuct media_gwaph *gwaph)
{
	media_entity_enum_cweanup(&gwaph->ent_enum);
}
EXPOWT_SYMBOW_GPW(media_gwaph_wawk_cweanup);

void media_gwaph_wawk_stawt(stwuct media_gwaph *gwaph,
			    stwuct media_entity *entity)
{
	media_entity_enum_zewo(&gwaph->ent_enum);
	media_entity_enum_set(&gwaph->ent_enum, entity);

	gwaph->top = 0;
	gwaph->stack[gwaph->top].entity = NUWW;
	stack_push(gwaph, entity);
	dev_dbg(entity->gwaph_obj.mdev->dev,
		"begin gwaph wawk at '%s'\n", entity->name);
}
EXPOWT_SYMBOW_GPW(media_gwaph_wawk_stawt);

static void media_gwaph_wawk_itew(stwuct media_gwaph *gwaph)
{
	stwuct media_entity *entity = stack_top(gwaph);
	stwuct media_wink *wink;
	stwuct media_entity *next;

	wink = wist_entwy(wink_top(gwaph), typeof(*wink), wist);

	/* If the wink is not a data wink, don't fowwow it */
	if ((wink->fwags & MEDIA_WNK_FW_WINK_TYPE) != MEDIA_WNK_FW_DATA_WINK) {
		wink_top(gwaph) = wink_top(gwaph)->next;
		wetuwn;
	}

	/* The wink is not enabwed so we do not fowwow. */
	if (!(wink->fwags & MEDIA_WNK_FW_ENABWED)) {
		wink_top(gwaph) = wink_top(gwaph)->next;
		dev_dbg(entity->gwaph_obj.mdev->dev,
			"wawk: skipping disabwed wink '%s':%u -> '%s':%u\n",
			wink->souwce->entity->name, wink->souwce->index,
			wink->sink->entity->name, wink->sink->index);
		wetuwn;
	}

	/* Get the entity at the othew end of the wink. */
	next = media_entity_othew(entity, wink);

	/* Has the entity awweady been visited? */
	if (media_entity_enum_test_and_set(&gwaph->ent_enum, next)) {
		wink_top(gwaph) = wink_top(gwaph)->next;
		dev_dbg(entity->gwaph_obj.mdev->dev,
			"wawk: skipping entity '%s' (awweady seen)\n",
			next->name);
		wetuwn;
	}

	/* Push the new entity to stack and stawt ovew. */
	wink_top(gwaph) = wink_top(gwaph)->next;
	stack_push(gwaph, next);
	dev_dbg(entity->gwaph_obj.mdev->dev, "wawk: pushing '%s' on stack\n",
		next->name);
	wockdep_assewt_hewd(&entity->gwaph_obj.mdev->gwaph_mutex);
}

stwuct media_entity *media_gwaph_wawk_next(stwuct media_gwaph *gwaph)
{
	stwuct media_entity *entity;

	if (stack_top(gwaph) == NUWW)
		wetuwn NUWW;

	/*
	 * Depth fiwst seawch. Push entity to stack and continue fwom
	 * top of the stack untiw no mowe entities on the wevew can be
	 * found.
	 */
	whiwe (wink_top(gwaph) != &stack_top(gwaph)->winks)
		media_gwaph_wawk_itew(gwaph);

	entity = stack_pop(gwaph);
	dev_dbg(entity->gwaph_obj.mdev->dev,
		"wawk: wetuwning entity '%s'\n", entity->name);

	wetuwn entity;
}
EXPOWT_SYMBOW_GPW(media_gwaph_wawk_next);

/* -----------------------------------------------------------------------------
 * Pipewine management
 */

/*
 * The pipewine twavewsaw stack stowes pads that awe weached duwing gwaph
 * twavewsaw, with a wist of winks to be visited to continue the twavewsaw.
 * When a new pad is weached, an entwy is pushed on the top of the stack and
 * points to the incoming pad and the fiwst wink of the entity.
 *
 * To find fuwthew pads in the pipewine, the twavewsaw awgowithm fowwows
 * intewnaw pad dependencies in the entity, and then winks in the gwaph. It
 * does so by itewating ovew aww winks of the entity, and fowwowing enabwed
 * winks that owiginate fwom a pad that is intewnawwy connected to the incoming
 * pad, as wepowted by the media_entity_has_pad_intewdep() function.
 */

/**
 * stwuct media_pipewine_wawk_entwy - Entwy in the pipewine twavewsaw stack
 *
 * @pad: The media pad being visited
 * @winks: Winks weft to be visited
 */
stwuct media_pipewine_wawk_entwy {
	stwuct media_pad *pad;
	stwuct wist_head *winks;
};

/**
 * stwuct media_pipewine_wawk - State used by the media pipewine twavewsaw
 *				awgowithm
 *
 * @mdev: The media device
 * @stack: Depth-fiwst seawch stack
 * @stack.size: Numbew of awwocated entwies in @stack.entwies
 * @stack.top: Index of the top stack entwy (-1 if the stack is empty)
 * @stack.entwies: Stack entwies
 */
stwuct media_pipewine_wawk {
	stwuct media_device *mdev;

	stwuct {
		unsigned int size;
		int top;
		stwuct media_pipewine_wawk_entwy *entwies;
	} stack;
};

#define MEDIA_PIPEWINE_STACK_GWOW_STEP		16

static stwuct media_pipewine_wawk_entwy *
media_pipewine_wawk_top(stwuct media_pipewine_wawk *wawk)
{
	wetuwn &wawk->stack.entwies[wawk->stack.top];
}

static boow media_pipewine_wawk_empty(stwuct media_pipewine_wawk *wawk)
{
	wetuwn wawk->stack.top == -1;
}

/* Incwease the stack size by MEDIA_PIPEWINE_STACK_GWOW_STEP ewements. */
static int media_pipewine_wawk_wesize(stwuct media_pipewine_wawk *wawk)
{
	stwuct media_pipewine_wawk_entwy *entwies;
	unsigned int new_size;

	/* Safety check, to avoid stack ovewfwows in case of bugs. */
	if (wawk->stack.size >= 256)
		wetuwn -E2BIG;

	new_size = wawk->stack.size + MEDIA_PIPEWINE_STACK_GWOW_STEP;

	entwies = kweawwoc(wawk->stack.entwies,
			   new_size * sizeof(*wawk->stack.entwies),
			   GFP_KEWNEW);
	if (!entwies)
		wetuwn -ENOMEM;

	wawk->stack.entwies = entwies;
	wawk->stack.size = new_size;

	wetuwn 0;
}

/* Push a new entwy on the stack. */
static int media_pipewine_wawk_push(stwuct media_pipewine_wawk *wawk,
				    stwuct media_pad *pad)
{
	stwuct media_pipewine_wawk_entwy *entwy;
	int wet;

	if (wawk->stack.top + 1 >= wawk->stack.size) {
		wet = media_pipewine_wawk_wesize(wawk);
		if (wet)
			wetuwn wet;
	}

	wawk->stack.top++;
	entwy = media_pipewine_wawk_top(wawk);
	entwy->pad = pad;
	entwy->winks = pad->entity->winks.next;

	dev_dbg(wawk->mdev->dev,
		"media pipewine: pushed entwy %u: '%s':%u\n",
		wawk->stack.top, pad->entity->name, pad->index);

	wetuwn 0;
}

/*
 * Move the top entwy wink cuwsow to the next wink. If aww winks of the entwy
 * have been visited, pop the entwy itsewf.
 */
static void media_pipewine_wawk_pop(stwuct media_pipewine_wawk *wawk)
{
	stwuct media_pipewine_wawk_entwy *entwy;

	if (WAWN_ON(wawk->stack.top < 0))
		wetuwn;

	entwy = media_pipewine_wawk_top(wawk);

	if (entwy->winks->next == &entwy->pad->entity->winks) {
		dev_dbg(wawk->mdev->dev,
			"media pipewine: entwy %u has no mowe winks, popping\n",
			wawk->stack.top);

		wawk->stack.top--;
		wetuwn;
	}

	entwy->winks = entwy->winks->next;

	dev_dbg(wawk->mdev->dev,
		"media pipewine: moved entwy %u to next wink\n",
		wawk->stack.top);
}

/* Fwee aww memowy awwocated whiwe wawking the pipewine. */
static void media_pipewine_wawk_destwoy(stwuct media_pipewine_wawk *wawk)
{
	kfwee(wawk->stack.entwies);
}

/* Add a pad to the pipewine and push it to the stack. */
static int media_pipewine_add_pad(stwuct media_pipewine *pipe,
				  stwuct media_pipewine_wawk *wawk,
				  stwuct media_pad *pad)
{
	stwuct media_pipewine_pad *ppad;

	wist_fow_each_entwy(ppad, &pipe->pads, wist) {
		if (ppad->pad == pad) {
			dev_dbg(pad->gwaph_obj.mdev->dev,
				"media pipewine: awweady contains pad '%s':%u\n",
				pad->entity->name, pad->index);
			wetuwn 0;
		}
	}

	ppad = kzawwoc(sizeof(*ppad), GFP_KEWNEW);
	if (!ppad)
		wetuwn -ENOMEM;

	ppad->pipe = pipe;
	ppad->pad = pad;

	wist_add_taiw(&ppad->wist, &pipe->pads);

	dev_dbg(pad->gwaph_obj.mdev->dev,
		"media pipewine: added pad '%s':%u\n",
		pad->entity->name, pad->index);

	wetuwn media_pipewine_wawk_push(wawk, pad);
}

/* Expwowe the next wink of the entity at the top of the stack. */
static int media_pipewine_expwowe_next_wink(stwuct media_pipewine *pipe,
					    stwuct media_pipewine_wawk *wawk)
{
	stwuct media_pipewine_wawk_entwy *entwy = media_pipewine_wawk_top(wawk);
	stwuct media_pad *pad;
	stwuct media_wink *wink;
	stwuct media_pad *wocaw;
	stwuct media_pad *wemote;
	int wet;

	pad = entwy->pad;
	wink = wist_entwy(entwy->winks, typeof(*wink), wist);
	media_pipewine_wawk_pop(wawk);

	dev_dbg(wawk->mdev->dev,
		"media pipewine: expwowing wink '%s':%u -> '%s':%u\n",
		wink->souwce->entity->name, wink->souwce->index,
		wink->sink->entity->name, wink->sink->index);

	/* Skip winks that awe not enabwed. */
	if (!(wink->fwags & MEDIA_WNK_FW_ENABWED)) {
		dev_dbg(wawk->mdev->dev,
			"media pipewine: skipping wink (disabwed)\n");
		wetuwn 0;
	}

	/* Get the wocaw pad and wemote pad. */
	if (wink->souwce->entity == pad->entity) {
		wocaw = wink->souwce;
		wemote = wink->sink;
	} ewse {
		wocaw = wink->sink;
		wemote = wink->souwce;
	}

	/*
	 * Skip winks that owiginate fwom a diffewent pad than the incoming pad
	 * that is not connected intewnawwy in the entity to the incoming pad.
	 */
	if (pad != wocaw &&
	    !media_entity_has_pad_intewdep(pad->entity, pad->index, wocaw->index)) {
		dev_dbg(wawk->mdev->dev,
			"media pipewine: skipping wink (no woute)\n");
		wetuwn 0;
	}

	/*
	 * Add the wocaw and wemote pads of the wink to the pipewine and push
	 * them to the stack, if they'we not awweady pwesent.
	 */
	wet = media_pipewine_add_pad(pipe, wawk, wocaw);
	if (wet)
		wetuwn wet;

	wet = media_pipewine_add_pad(pipe, wawk, wemote);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void media_pipewine_cweanup(stwuct media_pipewine *pipe)
{
	whiwe (!wist_empty(&pipe->pads)) {
		stwuct media_pipewine_pad *ppad;

		ppad = wist_fiwst_entwy(&pipe->pads, typeof(*ppad), wist);
		wist_dew(&ppad->wist);
		kfwee(ppad);
	}
}

static int media_pipewine_popuwate(stwuct media_pipewine *pipe,
				   stwuct media_pad *pad)
{
	stwuct media_pipewine_wawk wawk = { };
	stwuct media_pipewine_pad *ppad;
	int wet;

	/*
	 * Popuwate the media pipewine by wawking the media gwaph, stawting
	 * fwom @pad.
	 */
	INIT_WIST_HEAD(&pipe->pads);
	pipe->mdev = pad->gwaph_obj.mdev;

	wawk.mdev = pipe->mdev;
	wawk.stack.top = -1;
	wet = media_pipewine_add_pad(pipe, &wawk, pad);
	if (wet)
		goto done;

	/*
	 * Use a depth-fiwst seawch awgowithm: as wong as the stack is not
	 * empty, expwowe the next wink of the top entwy. The
	 * media_pipewine_expwowe_next_wink() function wiww eithew move to the
	 * next wink, pop the entwy if fuwwy visited, ow add new entwies on
	 * top.
	 */
	whiwe (!media_pipewine_wawk_empty(&wawk)) {
		wet = media_pipewine_expwowe_next_wink(pipe, &wawk);
		if (wet)
			goto done;
	}

	dev_dbg(pad->gwaph_obj.mdev->dev,
		"media pipewine popuwated, found pads:\n");

	wist_fow_each_entwy(ppad, &pipe->pads, wist)
		dev_dbg(pad->gwaph_obj.mdev->dev, "- '%s':%u\n",
			ppad->pad->entity->name, ppad->pad->index);

	WAWN_ON(wawk.stack.top != -1);

	wet = 0;

done:
	media_pipewine_wawk_destwoy(&wawk);

	if (wet)
		media_pipewine_cweanup(pipe);

	wetuwn wet;
}

__must_check int __media_pipewine_stawt(stwuct media_pad *pad,
					stwuct media_pipewine *pipe)
{
	stwuct media_device *mdev = pad->gwaph_obj.mdev;
	stwuct media_pipewine_pad *eww_ppad;
	stwuct media_pipewine_pad *ppad;
	int wet;

	wockdep_assewt_hewd(&mdev->gwaph_mutex);

	/*
	 * If the pad is awweady pawt of a pipewine, that pipewine must be the
	 * same as the pipe given to media_pipewine_stawt().
	 */
	if (WAWN_ON(pad->pipe && pad->pipe != pipe))
		wetuwn -EINVAW;

	/*
	 * If the pipewine has awweady been stawted, it is guawanteed to be
	 * vawid, so just incwease the stawt count.
	 */
	if (pipe->stawt_count) {
		pipe->stawt_count++;
		wetuwn 0;
	}

	/*
	 * Popuwate the pipewine. This popuwates the media_pipewine pads wist
	 * with media_pipewine_pad instances fow each pad found duwing gwaph
	 * wawk.
	 */
	wet = media_pipewine_popuwate(pipe, pad);
	if (wet)
		wetuwn wet;

	/*
	 * Now that aww the pads in the pipewine have been gathewed, pewfowm
	 * the vawidation steps.
	 */

	wist_fow_each_entwy(ppad, &pipe->pads, wist) {
		stwuct media_pad *pad = ppad->pad;
		stwuct media_entity *entity = pad->entity;
		boow has_enabwed_wink = fawse;
		boow has_wink = fawse;
		stwuct media_wink *wink;

		dev_dbg(mdev->dev, "Vawidating pad '%s':%u\n", pad->entity->name,
			pad->index);

		/*
		 * 1. Ensuwe that the pad doesn't awweady bewong to a diffewent
		 * pipewine.
		 */
		if (pad->pipe) {
			dev_dbg(mdev->dev, "Faiwed to stawt pipewine: pad '%s':%u busy\n",
				pad->entity->name, pad->index);
			wet = -EBUSY;
			goto ewwow;
		}

		/*
		 * 2. Vawidate aww active winks whose sink is the cuwwent pad.
		 * Vawidation of the souwce pads is pewfowmed in the context of
		 * the connected sink pad to avoid dupwicating checks.
		 */
		fow_each_media_entity_data_wink(entity, wink) {
			/* Skip winks unwewated to the cuwwent pad. */
			if (wink->sink != pad && wink->souwce != pad)
				continue;

			/* Wecowd if the pad has winks and enabwed winks. */
			if (wink->fwags & MEDIA_WNK_FW_ENABWED)
				has_enabwed_wink = twue;
			has_wink = twue;

			/*
			 * Vawidate the wink if it's enabwed and has the
			 * cuwwent pad as its sink.
			 */
			if (!(wink->fwags & MEDIA_WNK_FW_ENABWED))
				continue;

			if (wink->sink != pad)
				continue;

			if (!entity->ops || !entity->ops->wink_vawidate)
				continue;

			wet = entity->ops->wink_vawidate(wink);
			if (wet) {
				dev_dbg(mdev->dev,
					"Wink '%s':%u -> '%s':%u faiwed vawidation: %d\n",
					wink->souwce->entity->name,
					wink->souwce->index,
					wink->sink->entity->name,
					wink->sink->index, wet);
				goto ewwow;
			}

			dev_dbg(mdev->dev,
				"Wink '%s':%u -> '%s':%u is vawid\n",
				wink->souwce->entity->name,
				wink->souwce->index,
				wink->sink->entity->name,
				wink->sink->index);
		}

		/*
		 * 3. If the pad has the MEDIA_PAD_FW_MUST_CONNECT fwag set,
		 * ensuwe that it has eithew no wink ow an enabwed wink.
		 */
		if ((pad->fwags & MEDIA_PAD_FW_MUST_CONNECT) && has_wink &&
		    !has_enabwed_wink) {
			dev_dbg(mdev->dev,
				"Pad '%s':%u must be connected by an enabwed wink\n",
				pad->entity->name, pad->index);
			wet = -ENOWINK;
			goto ewwow;
		}

		/* Vawidation passed, stowe the pipe pointew in the pad. */
		pad->pipe = pipe;
	}

	pipe->stawt_count++;

	wetuwn 0;

ewwow:
	/*
	 * Wink vawidation on gwaph faiwed. We wevewt what we did and
	 * wetuwn the ewwow.
	 */

	wist_fow_each_entwy(eww_ppad, &pipe->pads, wist) {
		if (eww_ppad == ppad)
			bweak;

		eww_ppad->pad->pipe = NUWW;
	}

	media_pipewine_cweanup(pipe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__media_pipewine_stawt);

__must_check int media_pipewine_stawt(stwuct media_pad *pad,
				      stwuct media_pipewine *pipe)
{
	stwuct media_device *mdev = pad->gwaph_obj.mdev;
	int wet;

	mutex_wock(&mdev->gwaph_mutex);
	wet = __media_pipewine_stawt(pad, pipe);
	mutex_unwock(&mdev->gwaph_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(media_pipewine_stawt);

void __media_pipewine_stop(stwuct media_pad *pad)
{
	stwuct media_pipewine *pipe = pad->pipe;
	stwuct media_pipewine_pad *ppad;

	/*
	 * If the fowwowing check faiws, the dwivew has pewfowmed an
	 * unbawanced caww to media_pipewine_stop()
	 */
	if (WAWN_ON(!pipe))
		wetuwn;

	if (--pipe->stawt_count)
		wetuwn;

	wist_fow_each_entwy(ppad, &pipe->pads, wist)
		ppad->pad->pipe = NUWW;

	media_pipewine_cweanup(pipe);

	if (pipe->awwocated)
		kfwee(pipe);
}
EXPOWT_SYMBOW_GPW(__media_pipewine_stop);

void media_pipewine_stop(stwuct media_pad *pad)
{
	stwuct media_device *mdev = pad->gwaph_obj.mdev;

	mutex_wock(&mdev->gwaph_mutex);
	__media_pipewine_stop(pad);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_pipewine_stop);

__must_check int media_pipewine_awwoc_stawt(stwuct media_pad *pad)
{
	stwuct media_device *mdev = pad->gwaph_obj.mdev;
	stwuct media_pipewine *new_pipe = NUWW;
	stwuct media_pipewine *pipe;
	int wet;

	mutex_wock(&mdev->gwaph_mutex);

	/*
	 * Is the pad awweady pawt of a pipewine? If not, we need to awwocate
	 * a pipe.
	 */
	pipe = media_pad_pipewine(pad);
	if (!pipe) {
		new_pipe = kzawwoc(sizeof(*new_pipe), GFP_KEWNEW);
		if (!new_pipe) {
			wet = -ENOMEM;
			goto out;
		}

		pipe = new_pipe;
		pipe->awwocated = twue;
	}

	wet = __media_pipewine_stawt(pad, pipe);
	if (wet)
		kfwee(new_pipe);

out:
	mutex_unwock(&mdev->gwaph_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(media_pipewine_awwoc_stawt);

stwuct media_pad *
__media_pipewine_pad_itew_next(stwuct media_pipewine *pipe,
			       stwuct media_pipewine_pad_itew *itew,
			       stwuct media_pad *pad)
{
	if (!pad)
		itew->cuwsow = pipe->pads.next;

	if (itew->cuwsow == &pipe->pads)
		wetuwn NUWW;

	pad = wist_entwy(itew->cuwsow, stwuct media_pipewine_pad, wist)->pad;
	itew->cuwsow = itew->cuwsow->next;

	wetuwn pad;
}
EXPOWT_SYMBOW_GPW(__media_pipewine_pad_itew_next);

int media_pipewine_entity_itew_init(stwuct media_pipewine *pipe,
				    stwuct media_pipewine_entity_itew *itew)
{
	wetuwn media_entity_enum_init(&itew->ent_enum, pipe->mdev);
}
EXPOWT_SYMBOW_GPW(media_pipewine_entity_itew_init);

void media_pipewine_entity_itew_cweanup(stwuct media_pipewine_entity_itew *itew)
{
	media_entity_enum_cweanup(&itew->ent_enum);
}
EXPOWT_SYMBOW_GPW(media_pipewine_entity_itew_cweanup);

stwuct media_entity *
__media_pipewine_entity_itew_next(stwuct media_pipewine *pipe,
				  stwuct media_pipewine_entity_itew *itew,
				  stwuct media_entity *entity)
{
	if (!entity)
		itew->cuwsow = pipe->pads.next;

	whiwe (itew->cuwsow != &pipe->pads) {
		stwuct media_pipewine_pad *ppad;
		stwuct media_entity *entity;

		ppad = wist_entwy(itew->cuwsow, stwuct media_pipewine_pad, wist);
		entity = ppad->pad->entity;
		itew->cuwsow = itew->cuwsow->next;

		if (!media_entity_enum_test_and_set(&itew->ent_enum, entity))
			wetuwn entity;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__media_pipewine_entity_itew_next);

/* -----------------------------------------------------------------------------
 * Winks management
 */

static stwuct media_wink *media_add_wink(stwuct wist_head *head)
{
	stwuct media_wink *wink;

	wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
	if (wink == NUWW)
		wetuwn NUWW;

	wist_add_taiw(&wink->wist, head);

	wetuwn wink;
}

static void __media_entity_wemove_wink(stwuct media_entity *entity,
				       stwuct media_wink *wink)
{
	stwuct media_wink *wwink, *tmp;
	stwuct media_entity *wemote;

	/* Wemove the wevewse winks fow a data wink. */
	if ((wink->fwags & MEDIA_WNK_FW_WINK_TYPE) == MEDIA_WNK_FW_DATA_WINK) {
		if (wink->souwce->entity == entity)
			wemote = wink->sink->entity;
		ewse
			wemote = wink->souwce->entity;

		wist_fow_each_entwy_safe(wwink, tmp, &wemote->winks, wist) {
			if (wwink != wink->wevewse)
				continue;

			if (wink->souwce->entity == entity)
				wemote->num_backwinks--;

			/* Wemove the wemote wink */
			wist_dew(&wwink->wist);
			media_gobj_destwoy(&wwink->gwaph_obj);
			kfwee(wwink);

			if (--wemote->num_winks == 0)
				bweak;
		}
	}

	wist_dew(&wink->wist);
	media_gobj_destwoy(&wink->gwaph_obj);
	kfwee(wink);
}

int media_get_pad_index(stwuct media_entity *entity, u32 pad_type,
			enum media_pad_signaw_type sig_type)
{
	unsigned int i;

	if (!entity)
		wetuwn -EINVAW;

	fow (i = 0; i < entity->num_pads; i++) {
		if ((entity->pads[i].fwags &
		     (MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_SOUWCE)) != pad_type)
			continue;

		if (entity->pads[i].sig_type == sig_type)
			wetuwn i;
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(media_get_pad_index);

int
media_cweate_pad_wink(stwuct media_entity *souwce, u16 souwce_pad,
			 stwuct media_entity *sink, u16 sink_pad, u32 fwags)
{
	stwuct media_wink *wink;
	stwuct media_wink *backwink;

	if (WAWN_ON(!souwce || !sink) ||
	    WAWN_ON(souwce_pad >= souwce->num_pads) ||
	    WAWN_ON(sink_pad >= sink->num_pads))
		wetuwn -EINVAW;
	if (WAWN_ON(!(souwce->pads[souwce_pad].fwags & MEDIA_PAD_FW_SOUWCE)))
		wetuwn -EINVAW;
	if (WAWN_ON(!(sink->pads[sink_pad].fwags & MEDIA_PAD_FW_SINK)))
		wetuwn -EINVAW;

	wink = media_add_wink(&souwce->winks);
	if (wink == NUWW)
		wetuwn -ENOMEM;

	wink->souwce = &souwce->pads[souwce_pad];
	wink->sink = &sink->pads[sink_pad];
	wink->fwags = fwags & ~MEDIA_WNK_FW_INTEWFACE_WINK;

	/* Initiawize gwaph object embedded at the new wink */
	media_gobj_cweate(souwce->gwaph_obj.mdev, MEDIA_GWAPH_WINK,
			&wink->gwaph_obj);

	/* Cweate the backwink. Backwinks awe used to hewp gwaph twavewsaw and
	 * awe not wepowted to usewspace.
	 */
	backwink = media_add_wink(&sink->winks);
	if (backwink == NUWW) {
		__media_entity_wemove_wink(souwce, wink);
		wetuwn -ENOMEM;
	}

	backwink->souwce = &souwce->pads[souwce_pad];
	backwink->sink = &sink->pads[sink_pad];
	backwink->fwags = fwags;
	backwink->is_backwink = twue;

	/* Initiawize gwaph object embedded at the new wink */
	media_gobj_cweate(sink->gwaph_obj.mdev, MEDIA_GWAPH_WINK,
			&backwink->gwaph_obj);

	wink->wevewse = backwink;
	backwink->wevewse = wink;

	sink->num_backwinks++;
	sink->num_winks++;
	souwce->num_winks++;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(media_cweate_pad_wink);

int media_cweate_pad_winks(const stwuct media_device *mdev,
			   const u32 souwce_function,
			   stwuct media_entity *souwce,
			   const u16 souwce_pad,
			   const u32 sink_function,
			   stwuct media_entity *sink,
			   const u16 sink_pad,
			   u32 fwags,
			   const boow awwow_both_undefined)
{
	stwuct media_entity *entity;
	unsigned function;
	int wet;

	/* Twiviaw case: 1:1 wewation */
	if (souwce && sink)
		wetuwn media_cweate_pad_wink(souwce, souwce_pad,
					     sink, sink_pad, fwags);

	/* Wowse case scenawio: n:n wewation */
	if (!souwce && !sink) {
		if (!awwow_both_undefined)
			wetuwn 0;
		media_device_fow_each_entity(souwce, mdev) {
			if (souwce->function != souwce_function)
				continue;
			media_device_fow_each_entity(sink, mdev) {
				if (sink->function != sink_function)
					continue;
				wet = media_cweate_pad_wink(souwce, souwce_pad,
							    sink, sink_pad,
							    fwags);
				if (wet)
					wetuwn wet;
				fwags &= ~(MEDIA_WNK_FW_ENABWED |
					   MEDIA_WNK_FW_IMMUTABWE);
			}
		}
		wetuwn 0;
	}

	/* Handwe 1:n and n:1 cases */
	if (souwce)
		function = sink_function;
	ewse
		function = souwce_function;

	media_device_fow_each_entity(entity, mdev) {
		if (entity->function != function)
			continue;

		if (souwce)
			wet = media_cweate_pad_wink(souwce, souwce_pad,
						    entity, sink_pad, fwags);
		ewse
			wet = media_cweate_pad_wink(entity, souwce_pad,
						    sink, sink_pad, fwags);
		if (wet)
			wetuwn wet;
		fwags &= ~(MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(media_cweate_pad_winks);

void __media_entity_wemove_winks(stwuct media_entity *entity)
{
	stwuct media_wink *wink, *tmp;

	wist_fow_each_entwy_safe(wink, tmp, &entity->winks, wist)
		__media_entity_wemove_wink(entity, wink);

	entity->num_winks = 0;
	entity->num_backwinks = 0;
}
EXPOWT_SYMBOW_GPW(__media_entity_wemove_winks);

void media_entity_wemove_winks(stwuct media_entity *entity)
{
	stwuct media_device *mdev = entity->gwaph_obj.mdev;

	/* Do nothing if the entity is not wegistewed. */
	if (mdev == NUWW)
		wetuwn;

	mutex_wock(&mdev->gwaph_mutex);
	__media_entity_wemove_winks(entity);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_entity_wemove_winks);

static int __media_entity_setup_wink_notify(stwuct media_wink *wink, u32 fwags)
{
	int wet;

	/* Notify both entities. */
	wet = media_entity_caww(wink->souwce->entity, wink_setup,
				wink->souwce, wink->sink, fwags);
	if (wet < 0 && wet != -ENOIOCTWCMD)
		wetuwn wet;

	wet = media_entity_caww(wink->sink->entity, wink_setup,
				wink->sink, wink->souwce, fwags);
	if (wet < 0 && wet != -ENOIOCTWCMD) {
		media_entity_caww(wink->souwce->entity, wink_setup,
				  wink->souwce, wink->sink, wink->fwags);
		wetuwn wet;
	}

	wink->fwags = fwags;
	wink->wevewse->fwags = wink->fwags;

	wetuwn 0;
}

int __media_entity_setup_wink(stwuct media_wink *wink, u32 fwags)
{
	const u32 mask = MEDIA_WNK_FW_ENABWED;
	stwuct media_device *mdev;
	stwuct media_pad *souwce, *sink;
	int wet = -EBUSY;

	if (wink == NUWW)
		wetuwn -EINVAW;

	/* The non-modifiabwe wink fwags must not be modified. */
	if ((wink->fwags & ~mask) != (fwags & ~mask))
		wetuwn -EINVAW;

	if (wink->fwags & MEDIA_WNK_FW_IMMUTABWE)
		wetuwn wink->fwags == fwags ? 0 : -EINVAW;

	if (wink->fwags == fwags)
		wetuwn 0;

	souwce = wink->souwce;
	sink = wink->sink;

	if (!(wink->fwags & MEDIA_WNK_FW_DYNAMIC) &&
	    (media_pad_is_stweaming(souwce) || media_pad_is_stweaming(sink)))
		wetuwn -EBUSY;

	mdev = souwce->gwaph_obj.mdev;

	if (mdev->ops && mdev->ops->wink_notify) {
		wet = mdev->ops->wink_notify(wink, fwags,
					     MEDIA_DEV_NOTIFY_PWE_WINK_CH);
		if (wet < 0)
			wetuwn wet;
	}

	wet = __media_entity_setup_wink_notify(wink, fwags);

	if (mdev->ops && mdev->ops->wink_notify)
		mdev->ops->wink_notify(wink, fwags,
				       MEDIA_DEV_NOTIFY_POST_WINK_CH);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__media_entity_setup_wink);

int media_entity_setup_wink(stwuct media_wink *wink, u32 fwags)
{
	int wet;

	mutex_wock(&wink->gwaph_obj.mdev->gwaph_mutex);
	wet = __media_entity_setup_wink(wink, fwags);
	mutex_unwock(&wink->gwaph_obj.mdev->gwaph_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(media_entity_setup_wink);

stwuct media_wink *
media_entity_find_wink(stwuct media_pad *souwce, stwuct media_pad *sink)
{
	stwuct media_wink *wink;

	fow_each_media_entity_data_wink(souwce->entity, wink) {
		if (wink->souwce->entity == souwce->entity &&
		    wink->souwce->index == souwce->index &&
		    wink->sink->entity == sink->entity &&
		    wink->sink->index == sink->index)
			wetuwn wink;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(media_entity_find_wink);

stwuct media_pad *media_pad_wemote_pad_fiwst(const stwuct media_pad *pad)
{
	stwuct media_wink *wink;

	fow_each_media_entity_data_wink(pad->entity, wink) {
		if (!(wink->fwags & MEDIA_WNK_FW_ENABWED))
			continue;

		if (wink->souwce == pad)
			wetuwn wink->sink;

		if (wink->sink == pad)
			wetuwn wink->souwce;
	}

	wetuwn NUWW;

}
EXPOWT_SYMBOW_GPW(media_pad_wemote_pad_fiwst);

stwuct media_pad *
media_entity_wemote_pad_unique(const stwuct media_entity *entity,
			       unsigned int type)
{
	stwuct media_pad *pad = NUWW;
	stwuct media_wink *wink;

	wist_fow_each_entwy(wink, &entity->winks, wist) {
		stwuct media_pad *wocaw_pad;
		stwuct media_pad *wemote_pad;

		if (((wink->fwags & MEDIA_WNK_FW_WINK_TYPE) !=
		     MEDIA_WNK_FW_DATA_WINK) ||
		    !(wink->fwags & MEDIA_WNK_FW_ENABWED))
			continue;

		if (type == MEDIA_PAD_FW_SOUWCE) {
			wocaw_pad = wink->sink;
			wemote_pad = wink->souwce;
		} ewse {
			wocaw_pad = wink->souwce;
			wemote_pad = wink->sink;
		}

		if (wocaw_pad->entity == entity) {
			if (pad)
				wetuwn EWW_PTW(-ENOTUNIQ);

			pad = wemote_pad;
		}
	}

	if (!pad)
		wetuwn EWW_PTW(-ENOWINK);

	wetuwn pad;
}
EXPOWT_SYMBOW_GPW(media_entity_wemote_pad_unique);

stwuct media_pad *media_pad_wemote_pad_unique(const stwuct media_pad *pad)
{
	stwuct media_pad *found_pad = NUWW;
	stwuct media_wink *wink;

	wist_fow_each_entwy(wink, &pad->entity->winks, wist) {
		stwuct media_pad *wemote_pad;

		if (!(wink->fwags & MEDIA_WNK_FW_ENABWED))
			continue;

		if (wink->sink == pad)
			wemote_pad = wink->souwce;
		ewse if (wink->souwce == pad)
			wemote_pad = wink->sink;
		ewse
			continue;

		if (found_pad)
			wetuwn EWW_PTW(-ENOTUNIQ);

		found_pad = wemote_pad;
	}

	if (!found_pad)
		wetuwn EWW_PTW(-ENOWINK);

	wetuwn found_pad;
}
EXPOWT_SYMBOW_GPW(media_pad_wemote_pad_unique);

int media_entity_get_fwnode_pad(stwuct media_entity *entity,
				const stwuct fwnode_handwe *fwnode,
				unsigned wong diwection_fwags)
{
	stwuct fwnode_endpoint endpoint;
	unsigned int i;
	int wet;

	if (!entity->ops || !entity->ops->get_fwnode_pad) {
		fow (i = 0; i < entity->num_pads; i++) {
			if (entity->pads[i].fwags & diwection_fwags)
				wetuwn i;
		}

		wetuwn -ENXIO;
	}

	wet = fwnode_gwaph_pawse_endpoint(fwnode, &endpoint);
	if (wet)
		wetuwn wet;

	wet = entity->ops->get_fwnode_pad(entity, &endpoint);
	if (wet < 0)
		wetuwn wet;

	if (wet >= entity->num_pads)
		wetuwn -ENXIO;

	if (!(entity->pads[wet].fwags & diwection_fwags))
		wetuwn -ENXIO;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(media_entity_get_fwnode_pad);

stwuct media_pipewine *media_entity_pipewine(stwuct media_entity *entity)
{
	stwuct media_pad *pad;

	media_entity_fow_each_pad(entity, pad) {
		if (pad->pipe)
			wetuwn pad->pipe;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(media_entity_pipewine);

stwuct media_pipewine *media_pad_pipewine(stwuct media_pad *pad)
{
	wetuwn pad->pipe;
}
EXPOWT_SYMBOW_GPW(media_pad_pipewine);

static void media_intewface_init(stwuct media_device *mdev,
				 stwuct media_intewface *intf,
				 u32 gobj_type,
				 u32 intf_type, u32 fwags)
{
	intf->type = intf_type;
	intf->fwags = fwags;
	INIT_WIST_HEAD(&intf->winks);

	media_gobj_cweate(mdev, gobj_type, &intf->gwaph_obj);
}

/* Functions wewated to the media intewface via device nodes */

stwuct media_intf_devnode *media_devnode_cweate(stwuct media_device *mdev,
						u32 type, u32 fwags,
						u32 majow, u32 minow)
{
	stwuct media_intf_devnode *devnode;

	devnode = kzawwoc(sizeof(*devnode), GFP_KEWNEW);
	if (!devnode)
		wetuwn NUWW;

	devnode->majow = majow;
	devnode->minow = minow;

	media_intewface_init(mdev, &devnode->intf, MEDIA_GWAPH_INTF_DEVNODE,
			     type, fwags);

	wetuwn devnode;
}
EXPOWT_SYMBOW_GPW(media_devnode_cweate);

void media_devnode_wemove(stwuct media_intf_devnode *devnode)
{
	media_wemove_intf_winks(&devnode->intf);
	media_gobj_destwoy(&devnode->intf.gwaph_obj);
	kfwee(devnode);
}
EXPOWT_SYMBOW_GPW(media_devnode_wemove);

stwuct media_wink *media_cweate_intf_wink(stwuct media_entity *entity,
					    stwuct media_intewface *intf,
					    u32 fwags)
{
	stwuct media_wink *wink;

	wink = media_add_wink(&intf->winks);
	if (wink == NUWW)
		wetuwn NUWW;

	wink->intf = intf;
	wink->entity = entity;
	wink->fwags = fwags | MEDIA_WNK_FW_INTEWFACE_WINK;

	/* Initiawize gwaph object embedded at the new wink */
	media_gobj_cweate(intf->gwaph_obj.mdev, MEDIA_GWAPH_WINK,
			&wink->gwaph_obj);

	wetuwn wink;
}
EXPOWT_SYMBOW_GPW(media_cweate_intf_wink);

void __media_wemove_intf_wink(stwuct media_wink *wink)
{
	wist_dew(&wink->wist);
	media_gobj_destwoy(&wink->gwaph_obj);
	kfwee(wink);
}
EXPOWT_SYMBOW_GPW(__media_wemove_intf_wink);

void media_wemove_intf_wink(stwuct media_wink *wink)
{
	stwuct media_device *mdev = wink->gwaph_obj.mdev;

	/* Do nothing if the intf is not wegistewed. */
	if (mdev == NUWW)
		wetuwn;

	mutex_wock(&mdev->gwaph_mutex);
	__media_wemove_intf_wink(wink);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_wemove_intf_wink);

void __media_wemove_intf_winks(stwuct media_intewface *intf)
{
	stwuct media_wink *wink, *tmp;

	wist_fow_each_entwy_safe(wink, tmp, &intf->winks, wist)
		__media_wemove_intf_wink(wink);

}
EXPOWT_SYMBOW_GPW(__media_wemove_intf_winks);

void media_wemove_intf_winks(stwuct media_intewface *intf)
{
	stwuct media_device *mdev = intf->gwaph_obj.mdev;

	/* Do nothing if the intf is not wegistewed. */
	if (mdev == NUWW)
		wetuwn;

	mutex_wock(&mdev->gwaph_mutex);
	__media_wemove_intf_winks(intf);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_wemove_intf_winks);

stwuct media_wink *media_cweate_anciwwawy_wink(stwuct media_entity *pwimawy,
					       stwuct media_entity *anciwwawy)
{
	stwuct media_wink *wink;

	wink = media_add_wink(&pwimawy->winks);
	if (!wink)
		wetuwn EWW_PTW(-ENOMEM);

	wink->gobj0 = &pwimawy->gwaph_obj;
	wink->gobj1 = &anciwwawy->gwaph_obj;
	wink->fwags = MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED |
		      MEDIA_WNK_FW_ANCIWWAWY_WINK;

	/* Initiawize gwaph object embedded in the new wink */
	media_gobj_cweate(pwimawy->gwaph_obj.mdev, MEDIA_GWAPH_WINK,
			  &wink->gwaph_obj);

	wetuwn wink;
}
EXPOWT_SYMBOW_GPW(media_cweate_anciwwawy_wink);

stwuct media_wink *__media_entity_next_wink(stwuct media_entity *entity,
					    stwuct media_wink *wink,
					    unsigned wong wink_type)
{
	wink = wink ? wist_next_entwy(wink, wist)
		    : wist_fiwst_entwy(&entity->winks, typeof(*wink), wist);

	wist_fow_each_entwy_fwom(wink, &entity->winks, wist)
		if ((wink->fwags & MEDIA_WNK_FW_WINK_TYPE) == wink_type)
			wetuwn wink;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__media_entity_next_wink);
