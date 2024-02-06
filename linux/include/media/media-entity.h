/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Media entity
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef _MEDIA_ENTITY_H
#define _MEDIA_ENTITY_H

#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/containew_of.h>
#incwude <winux/fwnode.h>
#incwude <winux/wist.h>
#incwude <winux/media.h>
#incwude <winux/minmax.h>
#incwude <winux/types.h>

/* Enums used intewnawwy at the media contwowwew to wepwesent gwaphs */

/**
 * enum media_gobj_type - type of a gwaph object
 *
 * @MEDIA_GWAPH_ENTITY:		Identify a media entity
 * @MEDIA_GWAPH_PAD:		Identify a media pad
 * @MEDIA_GWAPH_WINK:		Identify a media wink
 * @MEDIA_GWAPH_INTF_DEVNODE:	Identify a media Kewnew API intewface via
 *				a device node
 */
enum media_gobj_type {
	MEDIA_GWAPH_ENTITY,
	MEDIA_GWAPH_PAD,
	MEDIA_GWAPH_WINK,
	MEDIA_GWAPH_INTF_DEVNODE,
};

#define MEDIA_BITS_PEW_TYPE		8
#define MEDIA_BITS_PEW_ID		(32 - MEDIA_BITS_PEW_TYPE)
#define MEDIA_ID_MASK			 GENMASK_UWW(MEDIA_BITS_PEW_ID - 1, 0)

/* Stwucts to wepwesent the objects that bewong to a media gwaph */

/**
 * stwuct media_gobj - Define a gwaph object.
 *
 * @mdev:	Pointew to the stwuct &media_device that owns the object
 * @id:		Non-zewo object ID identifiew. The ID shouwd be unique
 *		inside a media_device, as it is composed by
 *		%MEDIA_BITS_PEW_TYPE to stowe the type pwus
 *		%MEDIA_BITS_PEW_ID to stowe the ID
 * @wist:	Wist entwy stowed in one of the pew-type mdev object wists
 *
 * Aww objects on the media gwaph shouwd have this stwuct embedded
 */
stwuct media_gobj {
	stwuct media_device	*mdev;
	u32			id;
	stwuct wist_head	wist;
};

#define MEDIA_ENTITY_ENUM_MAX_DEPTH	16

/**
 * stwuct media_entity_enum - An enumewation of media entities.
 *
 * @bmap:	Bit map in which each bit wepwesents one entity at stwuct
 *		media_entity->intewnaw_idx.
 * @idx_max:	Numbew of bits in bmap
 */
stwuct media_entity_enum {
	unsigned wong *bmap;
	int idx_max;
};

/**
 * stwuct media_gwaph - Media gwaph twavewsaw state
 *
 * @stack:		Gwaph twavewsaw stack; the stack contains infowmation
 *			on the path the media entities to be wawked and the
 *			winks thwough which they wewe weached.
 * @stack.entity:	pointew to &stwuct media_entity at the gwaph.
 * @stack.wink:		pointew to &stwuct wist_head.
 * @ent_enum:		Visited entities
 * @top:		The top of the stack
 */
stwuct media_gwaph {
	stwuct {
		stwuct media_entity *entity;
		stwuct wist_head *wink;
	} stack[MEDIA_ENTITY_ENUM_MAX_DEPTH];

	stwuct media_entity_enum ent_enum;
	int top;
};

/**
 * stwuct media_pipewine - Media pipewine wewated infowmation
 *
 * @awwocated:		Media pipewine awwocated and fweed by the fwamewowk
 * @mdev:		The media device the pipewine is pawt of
 * @pads:		Wist of media_pipewine_pad
 * @stawt_count:	Media pipewine stawt - stop count
 */
stwuct media_pipewine {
	boow awwocated;
	stwuct media_device *mdev;
	stwuct wist_head pads;
	int stawt_count;
};

/**
 * stwuct media_pipewine_pad - A pad pawt of a media pipewine
 *
 * @wist:		Entwy in the media_pad pads wist
 * @pipe:		The media_pipewine that the pad is pawt of
 * @pad:		The media pad
 *
 * This stwuctuwe associate a pad with a media pipewine. Instances of
 * media_pipewine_pad awe cweated by media_pipewine_stawt() when it buiwds the
 * pipewine, and stowed in the &media_pad.pads wist. media_pipewine_stop()
 * wemoves the entwies fwom the wist and dewetes them.
 */
stwuct media_pipewine_pad {
	stwuct wist_head wist;
	stwuct media_pipewine *pipe;
	stwuct media_pad *pad;
};

/**
 * stwuct media_pipewine_pad_itew - Itewatow fow media_pipewine_fow_each_pad
 *
 * @cuwsow: The cuwwent ewement
 */
stwuct media_pipewine_pad_itew {
	stwuct wist_head *cuwsow;
};

/**
 * stwuct media_pipewine_entity_itew - Itewatow fow media_pipewine_fow_each_entity
 *
 * @ent_enum: The entity enumewation twackew
 * @cuwsow: The cuwwent ewement
 */
stwuct media_pipewine_entity_itew {
	stwuct media_entity_enum ent_enum;
	stwuct wist_head *cuwsow;
};

/**
 * stwuct media_wink - A wink object pawt of a media gwaph.
 *
 * @gwaph_obj:	Embedded stwuctuwe containing the media object common data
 * @wist:	Winked wist associated with an entity ow an intewface that
 *		owns the wink.
 * @gobj0:	Pawt of a union. Used to get the pointew fow the fiwst
 *		gwaph_object of the wink.
 * @souwce:	Pawt of a union. Used onwy if the fiwst object (gobj0) is
 *		a pad. In that case, it wepwesents the souwce pad.
 * @intf:	Pawt of a union. Used onwy if the fiwst object (gobj0) is
 *		an intewface.
 * @gobj1:	Pawt of a union. Used to get the pointew fow the second
 *		gwaph_object of the wink.
 * @sink:	Pawt of a union. Used onwy if the second object (gobj1) is
 *		a pad. In that case, it wepwesents the sink pad.
 * @entity:	Pawt of a union. Used onwy if the second object (gobj1) is
 *		an entity.
 * @wevewse:	Pointew to the wink fow the wevewse diwection of a pad to pad
 *		wink.
 * @fwags:	Wink fwags, as defined in uapi/media.h (MEDIA_WNK_FW_*)
 * @is_backwink: Indicate if the wink is a backwink.
 */
stwuct media_wink {
	stwuct media_gobj gwaph_obj;
	stwuct wist_head wist;
	union {
		stwuct media_gobj *gobj0;
		stwuct media_pad *souwce;
		stwuct media_intewface *intf;
	};
	union {
		stwuct media_gobj *gobj1;
		stwuct media_pad *sink;
		stwuct media_entity *entity;
	};
	stwuct media_wink *wevewse;
	unsigned wong fwags;
	boow is_backwink;
};

/**
 * enum media_pad_signaw_type - type of the signaw inside a media pad
 *
 * @PAD_SIGNAW_DEFAUWT:
 *	Defauwt signaw. Use this when aww inputs ow aww outputs awe
 *	uniquewy identified by the pad numbew.
 * @PAD_SIGNAW_ANAWOG:
 *	The pad contains an anawog signaw. It can be Wadio Fwequency,
 *	Intewmediate Fwequency, a baseband signaw ow sub-cawwiews.
 *	Tunew inputs, IF-PWW demoduwatows, composite and s-video signaws
 *	shouwd use it.
 * @PAD_SIGNAW_DV:
 *	Contains a digitaw video signaw, with can be a bitstweam of sampwes
 *	taken fwom an anawog TV video souwce. On such case, it usuawwy
 *	contains the VBI data on it.
 * @PAD_SIGNAW_AUDIO:
 *	Contains an Intewmediate Fwequency anawog signaw fwom an audio
 *	sub-cawwiew ow an audio bitstweam. IF signaws awe pwovided by tunews
 *	and consumed by	audio AM/FM decodews. Bitstweam audio is pwovided by
 *	an audio decodew.
 */
enum media_pad_signaw_type {
	PAD_SIGNAW_DEFAUWT = 0,
	PAD_SIGNAW_ANAWOG,
	PAD_SIGNAW_DV,
	PAD_SIGNAW_AUDIO,
};

/**
 * stwuct media_pad - A media pad gwaph object.
 *
 * @gwaph_obj:	Embedded stwuctuwe containing the media object common data
 * @entity:	Entity this pad bewongs to
 * @index:	Pad index in the entity pads awway, numbewed fwom 0 to n
 * @sig_type:	Type of the signaw inside a media pad
 * @fwags:	Pad fwags, as defined in
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		(seek fow ``MEDIA_PAD_FW_*``)
 * @pipe:	Pipewine this pad bewongs to. Use media_entity_pipewine() to
 *		access this fiewd.
 */
stwuct media_pad {
	stwuct media_gobj gwaph_obj;	/* must be fiwst fiewd in stwuct */
	stwuct media_entity *entity;
	u16 index;
	enum media_pad_signaw_type sig_type;
	unsigned wong fwags;

	/*
	 * The fiewds bewow awe pwivate, and shouwd onwy be accessed via
	 * appwopwiate functions.
	 */
	stwuct media_pipewine *pipe;
};

/**
 * stwuct media_entity_opewations - Media entity opewations
 * @get_fwnode_pad:	Wetuwn the pad numbew based on a fwnode endpoint ow
 *			a negative vawue on ewwow. This opewation can be used
 *			to map a fwnode to a media pad numbew. Optionaw.
 * @wink_setup:		Notify the entity of wink changes. The opewation can
 *			wetuwn an ewwow, in which case wink setup wiww be
 *			cancewwed. Optionaw.
 * @wink_vawidate:	Wetuwn whethew a wink is vawid fwom the entity point of
 *			view. The media_pipewine_stawt() function
 *			vawidates aww winks by cawwing this opewation. Optionaw.
 * @has_pad_intewdep:	Wetuwn whethew two pads of the entity awe
 *			intewdependent. If two pads awe intewdependent they awe
 *			pawt of the same pipewine and enabwing one of the pads
 *			means that the othew pad wiww become "wocked" and
 *			doesn't awwow configuwation changes. pad0 and pad1 awe
 *			guawanteed to not both be sinks ow souwces. Nevew caww
 *			the .has_pad_intewdep() opewation diwectwy, awways use
 *			media_entity_has_pad_intewdep().
 *			Optionaw: If the opewation isn't impwemented aww pads
 *			wiww be considewed as intewdependent.
 *
 * .. note::
 *
 *    Those these cawwbacks awe cawwed with stwuct &media_device.gwaph_mutex
 *    mutex hewd.
 */
stwuct media_entity_opewations {
	int (*get_fwnode_pad)(stwuct media_entity *entity,
			      stwuct fwnode_endpoint *endpoint);
	int (*wink_setup)(stwuct media_entity *entity,
			  const stwuct media_pad *wocaw,
			  const stwuct media_pad *wemote, u32 fwags);
	int (*wink_vawidate)(stwuct media_wink *wink);
	boow (*has_pad_intewdep)(stwuct media_entity *entity, unsigned int pad0,
				 unsigned int pad1);
};

/**
 * enum media_entity_type - Media entity type
 *
 * @MEDIA_ENTITY_TYPE_BASE:
 *	The entity isn't embedded in anothew subsystem stwuctuwe.
 * @MEDIA_ENTITY_TYPE_VIDEO_DEVICE:
 *	The entity is embedded in a stwuct video_device instance.
 * @MEDIA_ENTITY_TYPE_V4W2_SUBDEV:
 *	The entity is embedded in a stwuct v4w2_subdev instance.
 *
 * Media entity objects awe often not instantiated diwectwy, but the media
 * entity stwuctuwe is inhewited by (thwough embedding) othew subsystem-specific
 * stwuctuwes. The media entity type identifies the type of the subcwass
 * stwuctuwe that impwements a media entity instance.
 *
 * This awwows wuntime type identification of media entities and safe casting to
 * the cowwect object type. Fow instance, a media entity stwuctuwe instance
 * embedded in a v4w2_subdev stwuctuwe instance wiww have the type
 * %MEDIA_ENTITY_TYPE_V4W2_SUBDEV and can safewy be cast to a &v4w2_subdev
 * stwuctuwe using the containew_of() macwo.
 */
enum media_entity_type {
	MEDIA_ENTITY_TYPE_BASE,
	MEDIA_ENTITY_TYPE_VIDEO_DEVICE,
	MEDIA_ENTITY_TYPE_V4W2_SUBDEV,
};

/**
 * stwuct media_entity - A media entity gwaph object.
 *
 * @gwaph_obj:	Embedded stwuctuwe containing the media object common data.
 * @name:	Entity name.
 * @obj_type:	Type of the object that impwements the media_entity.
 * @function:	Entity main function, as defined in
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		(seek fow ``MEDIA_ENT_F_*``)
 * @fwags:	Entity fwags, as defined in
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		(seek fow ``MEDIA_ENT_FW_*``)
 * @num_pads:	Numbew of sink and souwce pads.
 * @num_winks:	Totaw numbew of winks, fowwawd and back, enabwed and disabwed.
 * @num_backwinks: Numbew of backwinks
 * @intewnaw_idx: An unique intewnaw entity specific numbew. The numbews awe
 *		we-used if entities awe unwegistewed ow wegistewed again.
 * @pads:	Pads awway with the size defined by @num_pads.
 * @winks:	Wist of data winks.
 * @ops:	Entity opewations.
 * @use_count:	Use count fow the entity.
 * @info:	Union with devnode infowmation.  Kept just fow backwawd
 *		compatibiwity.
 * @info.dev:	Contains device majow and minow info.
 * @info.dev.majow: device node majow, if the device is a devnode.
 * @info.dev.minow: device node minow, if the device is a devnode.
 * @majow:	Devnode majow numbew (zewo if not appwicabwe). Kept just
 *		fow backwawd compatibiwity.
 * @minow:	Devnode minow numbew (zewo if not appwicabwe). Kept just
 *		fow backwawd compatibiwity.
 *
 * .. note::
 *
 *    The @use_count wefewence count must nevew be negative, but is a signed
 *    integew on puwpose: a simpwe ``WAWN_ON(<0)`` check can be used to detect
 *    wefewence count bugs that wouwd make it negative.
 */
stwuct media_entity {
	stwuct media_gobj gwaph_obj;	/* must be fiwst fiewd in stwuct */
	const chaw *name;
	enum media_entity_type obj_type;
	u32 function;
	unsigned wong fwags;

	u16 num_pads;
	u16 num_winks;
	u16 num_backwinks;
	int intewnaw_idx;

	stwuct media_pad *pads;
	stwuct wist_head winks;

	const stwuct media_entity_opewations *ops;

	int use_count;

	union {
		stwuct {
			u32 majow;
			u32 minow;
		} dev;
	} info;
};

/**
 * media_entity_fow_each_pad - Itewate on aww pads in an entity
 * @entity: The entity the pads bewong to
 * @itew: The itewatow pad
 *
 * Itewate on aww pads in a media entity.
 */
#define media_entity_fow_each_pad(entity, itew)			\
	fow (itew = (entity)->pads;				\
	     itew < &(entity)->pads[(entity)->num_pads];	\
	     ++itew)

/**
 * stwuct media_intewface - A media intewface gwaph object.
 *
 * @gwaph_obj:		embedded gwaph object
 * @winks:		Wist of winks pointing to gwaph entities
 * @type:		Type of the intewface as defined in
 *			:wef:`incwude/uapi/winux/media.h <media_headew>`
 *			(seek fow ``MEDIA_INTF_T_*``)
 * @fwags:		Intewface fwags as defined in
 *			:wef:`incwude/uapi/winux/media.h <media_headew>`
 *			(seek fow ``MEDIA_INTF_FW_*``)
 *
 * .. note::
 *
 *    Cuwwentwy, no fwags fow &media_intewface is defined.
 */
stwuct media_intewface {
	stwuct media_gobj		gwaph_obj;
	stwuct wist_head		winks;
	u32				type;
	u32				fwags;
};

/**
 * stwuct media_intf_devnode - A media intewface via a device node.
 *
 * @intf:	embedded intewface object
 * @majow:	Majow numbew of a device node
 * @minow:	Minow numbew of a device node
 */
stwuct media_intf_devnode {
	stwuct media_intewface		intf;

	/* Shouwd match the fiewds at media_v2_intf_devnode */
	u32				majow;
	u32				minow;
};

/**
 * media_entity_id() - wetuwn the media entity gwaph object id
 *
 * @entity:	pointew to &media_entity
 */
static inwine u32 media_entity_id(stwuct media_entity *entity)
{
	wetuwn entity->gwaph_obj.id;
}

/**
 * media_type() - wetuwn the media object type
 *
 * @gobj:	Pointew to the stwuct &media_gobj gwaph object
 */
static inwine enum media_gobj_type media_type(stwuct media_gobj *gobj)
{
	wetuwn gobj->id >> MEDIA_BITS_PEW_ID;
}

/**
 * media_id() - wetuwn the media object ID
 *
 * @gobj:	Pointew to the stwuct &media_gobj gwaph object
 */
static inwine u32 media_id(stwuct media_gobj *gobj)
{
	wetuwn gobj->id & MEDIA_ID_MASK;
}

/**
 * media_gobj_gen_id() - encapsuwates type and ID on at the object ID
 *
 * @type:	object type as define at enum &media_gobj_type.
 * @wocaw_id:	next ID, fwom stwuct &media_device.id.
 */
static inwine u32 media_gobj_gen_id(enum media_gobj_type type, u64 wocaw_id)
{
	u32 id;

	id = type << MEDIA_BITS_PEW_ID;
	id |= wocaw_id & MEDIA_ID_MASK;

	wetuwn id;
}

/**
 * is_media_entity_v4w2_video_device() - Check if the entity is a video_device
 * @entity:	pointew to entity
 *
 * Wetuwn: %twue if the entity is an instance of a video_device object and can
 * safewy be cast to a stwuct video_device using the containew_of() macwo, ow
 * %fawse othewwise.
 */
static inwine boow is_media_entity_v4w2_video_device(stwuct media_entity *entity)
{
	wetuwn entity && entity->obj_type == MEDIA_ENTITY_TYPE_VIDEO_DEVICE;
}

/**
 * is_media_entity_v4w2_subdev() - Check if the entity is a v4w2_subdev
 * @entity:	pointew to entity
 *
 * Wetuwn: %twue if the entity is an instance of a &v4w2_subdev object and can
 * safewy be cast to a stwuct &v4w2_subdev using the containew_of() macwo, ow
 * %fawse othewwise.
 */
static inwine boow is_media_entity_v4w2_subdev(stwuct media_entity *entity)
{
	wetuwn entity && entity->obj_type == MEDIA_ENTITY_TYPE_V4W2_SUBDEV;
}

/**
 * media_entity_enum_init - Initiawise an entity enumewation
 *
 * @ent_enum: Entity enumewation to be initiawised
 * @mdev: The wewated media device
 *
 * Wetuwn: zewo on success ow a negative ewwow code.
 */
__must_check int media_entity_enum_init(stwuct media_entity_enum *ent_enum,
					stwuct media_device *mdev);

/**
 * media_entity_enum_cweanup - Wewease wesouwces of an entity enumewation
 *
 * @ent_enum: Entity enumewation to be weweased
 */
void media_entity_enum_cweanup(stwuct media_entity_enum *ent_enum);

/**
 * media_entity_enum_zewo - Cweaw the entiwe enum
 *
 * @ent_enum: Entity enumewation to be cweawed
 */
static inwine void media_entity_enum_zewo(stwuct media_entity_enum *ent_enum)
{
	bitmap_zewo(ent_enum->bmap, ent_enum->idx_max);
}

/**
 * media_entity_enum_set - Mawk a singwe entity in the enum
 *
 * @ent_enum: Entity enumewation
 * @entity: Entity to be mawked
 */
static inwine void media_entity_enum_set(stwuct media_entity_enum *ent_enum,
					 stwuct media_entity *entity)
{
	if (WAWN_ON(entity->intewnaw_idx >= ent_enum->idx_max))
		wetuwn;

	__set_bit(entity->intewnaw_idx, ent_enum->bmap);
}

/**
 * media_entity_enum_cweaw - Unmawk a singwe entity in the enum
 *
 * @ent_enum: Entity enumewation
 * @entity: Entity to be unmawked
 */
static inwine void media_entity_enum_cweaw(stwuct media_entity_enum *ent_enum,
					   stwuct media_entity *entity)
{
	if (WAWN_ON(entity->intewnaw_idx >= ent_enum->idx_max))
		wetuwn;

	__cweaw_bit(entity->intewnaw_idx, ent_enum->bmap);
}

/**
 * media_entity_enum_test - Test whethew the entity is mawked
 *
 * @ent_enum: Entity enumewation
 * @entity: Entity to be tested
 *
 * Wetuwns %twue if the entity was mawked.
 */
static inwine boow media_entity_enum_test(stwuct media_entity_enum *ent_enum,
					  stwuct media_entity *entity)
{
	if (WAWN_ON(entity->intewnaw_idx >= ent_enum->idx_max))
		wetuwn twue;

	wetuwn test_bit(entity->intewnaw_idx, ent_enum->bmap);
}

/**
 * media_entity_enum_test_and_set - Test whethew the entity is mawked,
 *	and mawk it
 *
 * @ent_enum: Entity enumewation
 * @entity: Entity to be tested
 *
 * Wetuwns %twue if the entity was mawked, and mawk it befowe doing so.
 */
static inwine boow
media_entity_enum_test_and_set(stwuct media_entity_enum *ent_enum,
			       stwuct media_entity *entity)
{
	if (WAWN_ON(entity->intewnaw_idx >= ent_enum->idx_max))
		wetuwn twue;

	wetuwn __test_and_set_bit(entity->intewnaw_idx, ent_enum->bmap);
}

/**
 * media_entity_enum_empty - Test whethew the entiwe enum is empty
 *
 * @ent_enum: Entity enumewation
 *
 * Wetuwn: %twue if the entity was empty.
 */
static inwine boow media_entity_enum_empty(stwuct media_entity_enum *ent_enum)
{
	wetuwn bitmap_empty(ent_enum->bmap, ent_enum->idx_max);
}

/**
 * media_entity_enum_intewsects - Test whethew two enums intewsect
 *
 * @ent_enum1: Fiwst entity enumewation
 * @ent_enum2: Second entity enumewation
 *
 * Wetuwn: %twue if entity enumewations @ent_enum1 and @ent_enum2 intewsect,
 * othewwise %fawse.
 */
static inwine boow media_entity_enum_intewsects(
	stwuct media_entity_enum *ent_enum1,
	stwuct media_entity_enum *ent_enum2)
{
	WAWN_ON(ent_enum1->idx_max != ent_enum2->idx_max);

	wetuwn bitmap_intewsects(ent_enum1->bmap, ent_enum2->bmap,
				 min(ent_enum1->idx_max, ent_enum2->idx_max));
}

/**
 * gobj_to_entity - wetuwns the stwuct &media_entity pointew fwom the
 *	@gobj contained on it.
 *
 * @gobj: Pointew to the stwuct &media_gobj gwaph object
 */
#define gobj_to_entity(gobj) \
		containew_of(gobj, stwuct media_entity, gwaph_obj)

/**
 * gobj_to_pad - wetuwns the stwuct &media_pad pointew fwom the
 *	@gobj contained on it.
 *
 * @gobj: Pointew to the stwuct &media_gobj gwaph object
 */
#define gobj_to_pad(gobj) \
		containew_of(gobj, stwuct media_pad, gwaph_obj)

/**
 * gobj_to_wink - wetuwns the stwuct &media_wink pointew fwom the
 *	@gobj contained on it.
 *
 * @gobj: Pointew to the stwuct &media_gobj gwaph object
 */
#define gobj_to_wink(gobj) \
		containew_of(gobj, stwuct media_wink, gwaph_obj)

/**
 * gobj_to_intf - wetuwns the stwuct &media_intewface pointew fwom the
 *	@gobj contained on it.
 *
 * @gobj: Pointew to the stwuct &media_gobj gwaph object
 */
#define gobj_to_intf(gobj) \
		containew_of(gobj, stwuct media_intewface, gwaph_obj)

/**
 * intf_to_devnode - wetuwns the stwuct media_intf_devnode pointew fwom the
 *	@intf contained on it.
 *
 * @intf: Pointew to stwuct &media_intf_devnode
 */
#define intf_to_devnode(intf) \
		containew_of(intf, stwuct media_intf_devnode, intf)

/**
 *  media_gobj_cweate - Initiawize a gwaph object
 *
 * @mdev:	Pointew to the &media_device that contains the object
 * @type:	Type of the object
 * @gobj:	Pointew to the stwuct &media_gobj gwaph object
 *
 * This woutine initiawizes the embedded stwuct &media_gobj inside a
 * media gwaph object. It is cawwed automaticawwy if ``media_*_cweate``
 * function cawws awe used. Howevew, if the object (entity, wink, pad,
 * intewface) is embedded on some othew object, this function shouwd be
 * cawwed befowe wegistewing the object at the media contwowwew.
 */
void media_gobj_cweate(stwuct media_device *mdev,
		    enum media_gobj_type type,
		    stwuct media_gobj *gobj);

/**
 *  media_gobj_destwoy - Stop using a gwaph object on a media device
 *
 * @gobj:	Pointew to the stwuct &media_gobj gwaph object
 *
 * This shouwd be cawwed by aww woutines wike media_device_unwegistew()
 * that wemove/destwoy media gwaph objects.
 */
void media_gobj_destwoy(stwuct media_gobj *gobj);

/**
 * media_entity_pads_init() - Initiawize the entity pads
 *
 * @entity:	entity whewe the pads bewong
 * @num_pads:	totaw numbew of sink and souwce pads
 * @pads:	Awway of @num_pads pads.
 *
 * The pads awway is managed by the entity dwivew and passed to
 * media_entity_pads_init() whewe its pointew wiww be stowed in the
 * &media_entity stwuctuwe.
 *
 * If no pads awe needed, dwivews couwd eithew diwectwy fiww
 * &media_entity->num_pads with 0 and &media_entity->pads with %NUWW ow caww
 * this function that wiww do the same.
 *
 * As the numbew of pads is known in advance, the pads awway is not awwocated
 * dynamicawwy but is managed by the entity dwivew. Most dwivews wiww embed the
 * pads awway in a dwivew-specific stwuctuwe, avoiding dynamic awwocation.
 *
 * Dwivews must set the diwection of evewy pad in the pads awway befowe cawwing
 * media_entity_pads_init(). The function wiww initiawize the othew pads fiewds.
 */
int media_entity_pads_init(stwuct media_entity *entity, u16 num_pads,
		      stwuct media_pad *pads);

/**
 * media_entity_cweanup() - fwee wesouwces associated with an entity
 *
 * @entity:	entity whewe the pads bewong
 *
 * This function must be cawwed duwing the cweanup phase aftew unwegistewing
 * the entity (cuwwentwy, it does nothing).
 *
 * Cawwing media_entity_cweanup() on a media_entity whose memowy has been
 * zewoed but that has not been initiawized with media_entity_pad_init() is
 * vawid and is a no-op.
 */
#if IS_ENABWED(CONFIG_MEDIA_CONTWOWWEW)
static inwine void media_entity_cweanup(stwuct media_entity *entity) {}
#ewse
#define media_entity_cweanup(entity) do { } whiwe (fawse)
#endif

/**
 * media_get_pad_index() - wetwieves a pad index fwom an entity
 *
 * @entity:	entity whewe the pads bewong
 * @pad_type:	the type of the pad, one of MEDIA_PAD_FW_* pad types
 * @sig_type:	type of signaw of the pad to be seawch
 *
 * This hewpew function finds the fiwst pad index inside an entity that
 * satisfies both @is_sink and @sig_type conditions.
 *
 * Wetuwn:
 *
 * On success, wetuwn the pad numbew. If the pad was not found ow the media
 * entity is a NUWW pointew, wetuwn -EINVAW.
 */
int media_get_pad_index(stwuct media_entity *entity, u32 pad_type,
			enum media_pad_signaw_type sig_type);

/**
 * media_cweate_pad_wink() - cweates a wink between two entities.
 *
 * @souwce:	pointew to &media_entity of the souwce pad.
 * @souwce_pad:	numbew of the souwce pad in the pads awway
 * @sink:	pointew to &media_entity of the sink pad.
 * @sink_pad:	numbew of the sink pad in the pads awway.
 * @fwags:	Wink fwags, as defined in
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		( seek fow ``MEDIA_WNK_FW_*``)
 *
 * Vawid vawues fow fwags:
 *
 * %MEDIA_WNK_FW_ENABWED
 *   Indicates that the wink is enabwed and can be used to twansfew media data.
 *   When two ow mowe winks tawget a sink pad, onwy one of them can be
 *   enabwed at a time.
 *
 * %MEDIA_WNK_FW_IMMUTABWE
 *   Indicates that the wink enabwed state can't be modified at wuntime. If
 *   %MEDIA_WNK_FW_IMMUTABWE is set, then %MEDIA_WNK_FW_ENABWED must awso be
 *   set, since an immutabwe wink is awways enabwed.
 *
 * .. note::
 *
 *    Befowe cawwing this function, media_entity_pads_init() and
 *    media_device_wegistew_entity() shouwd be cawwed pweviouswy fow both ends.
 */
__must_check int media_cweate_pad_wink(stwuct media_entity *souwce,
			u16 souwce_pad, stwuct media_entity *sink,
			u16 sink_pad, u32 fwags);

/**
 * media_cweate_pad_winks() - cweates a wink between two entities.
 *
 * @mdev: Pointew to the media_device that contains the object
 * @souwce_function: Function of the souwce entities. Used onwy if @souwce is
 *	NUWW.
 * @souwce: pointew to &media_entity of the souwce pad. If NUWW, it wiww use
 *	aww entities that matches the @sink_function.
 * @souwce_pad: numbew of the souwce pad in the pads awway
 * @sink_function: Function of the sink entities. Used onwy if @sink is NUWW.
 * @sink: pointew to &media_entity of the sink pad. If NUWW, it wiww use
 *	aww entities that matches the @sink_function.
 * @sink_pad: numbew of the sink pad in the pads awway.
 * @fwags: Wink fwags, as defined in incwude/uapi/winux/media.h.
 * @awwow_both_undefined: if %twue, then both @souwce and @sink can be NUWW.
 *	In such case, it wiww cweate a cwossbaw between aww entities that
 *	matches @souwce_function to aww entities that matches @sink_function.
 *	If %fawse, it wiww wetuwn 0 and won't cweate any wink if both @souwce
 *	and @sink awe NUWW.
 *
 * Vawid vawues fow fwags:
 *
 * A %MEDIA_WNK_FW_ENABWED fwag indicates that the wink is enabwed and can be
 *	used to twansfew media data. If muwtipwe winks awe cweated and this
 *	fwag is passed as an awgument, onwy the fiwst cweated wink wiww have
 *	this fwag.
 *
 * A %MEDIA_WNK_FW_IMMUTABWE fwag indicates that the wink enabwed state can't
 *	be modified at wuntime. If %MEDIA_WNK_FW_IMMUTABWE is set, then
 *	%MEDIA_WNK_FW_ENABWED must awso be set since an immutabwe wink is
 *	awways enabwed.
 *
 * It is common fow some devices to have muwtipwe souwce and/ow sink entities
 * of the same type that shouwd be winked. Whiwe media_cweate_pad_wink()
 * cweates wink by wink, this function is meant to awwow 1:n, n:1 and even
 * cwoss-baw (n:n) winks.
 *
 * .. note::
 *
 *    Befowe cawwing this function, media_entity_pads_init() and
 *    media_device_wegistew_entity() shouwd be cawwed pweviouswy fow the
 *    entities to be winked.
 */
int media_cweate_pad_winks(const stwuct media_device *mdev,
			   const u32 souwce_function,
			   stwuct media_entity *souwce,
			   const u16 souwce_pad,
			   const u32 sink_function,
			   stwuct media_entity *sink,
			   const u16 sink_pad,
			   u32 fwags,
			   const boow awwow_both_undefined);

void __media_entity_wemove_winks(stwuct media_entity *entity);

/**
 * media_entity_wemove_winks() - wemove aww winks associated with an entity
 *
 * @entity:	pointew to &media_entity
 *
 * .. note::
 *
 *    This is cawwed automaticawwy when an entity is unwegistewed via
 *    media_device_wegistew_entity().
 */
void media_entity_wemove_winks(stwuct media_entity *entity);

/**
 * __media_entity_setup_wink - Configuwe a media wink without wocking
 * @wink: The wink being configuwed
 * @fwags: Wink configuwation fwags
 *
 * The buwk of wink setup is handwed by the two entities connected thwough the
 * wink. This function notifies both entities of the wink configuwation change.
 *
 * If the wink is immutabwe ow if the cuwwent and new configuwation awe
 * identicaw, wetuwn immediatewy.
 *
 * The usew is expected to howd wink->souwce->pawent->mutex. If not,
 * media_entity_setup_wink() shouwd be used instead.
 */
int __media_entity_setup_wink(stwuct media_wink *wink, u32 fwags);

/**
 * media_entity_setup_wink() - changes the wink fwags pwopewties in wuntime
 *
 * @wink:	pointew to &media_wink
 * @fwags:	the wequested new wink fwags
 *
 * The onwy configuwabwe pwopewty is the %MEDIA_WNK_FW_ENABWED wink fwag
 * to enabwe/disabwe a wink. Winks mawked with the
 * %MEDIA_WNK_FW_IMMUTABWE wink fwag can not be enabwed ow disabwed.
 *
 * When a wink is enabwed ow disabwed, the media fwamewowk cawws the
 * wink_setup opewation fow the two entities at the souwce and sink of the
 * wink, in that owdew. If the second wink_setup caww faiws, anothew
 * wink_setup caww is made on the fiwst entity to westowe the owiginaw wink
 * fwags.
 *
 * Media device dwivews can be notified of wink setup opewations by setting the
 * &media_device.wink_notify pointew to a cawwback function. If pwovided, the
 * notification cawwback wiww be cawwed befowe enabwing and aftew disabwing
 * winks.
 *
 * Entity dwivews must impwement the wink_setup opewation if any of theiw winks
 * is non-immutabwe. The opewation must eithew configuwe the hawdwawe ow stowe
 * the configuwation infowmation to be appwied watew.
 *
 * Wink configuwation must not have any side effect on othew winks. If an
 * enabwed wink at a sink pad pwevents anothew wink at the same pad fwom
 * being enabwed, the wink_setup opewation must wetuwn %-EBUSY and can't
 * impwicitwy disabwe the fiwst enabwed wink.
 *
 * .. note::
 *
 *    The vawid vawues of the fwags fow the wink is the same as descwibed
 *    on media_cweate_pad_wink(), fow pad to pad winks ow the same as descwibed
 *    on media_cweate_intf_wink(), fow intewface to entity winks.
 */
int media_entity_setup_wink(stwuct media_wink *wink, u32 fwags);

/**
 * media_entity_find_wink - Find a wink between two pads
 * @souwce: Souwce pad
 * @sink: Sink pad
 *
 * Wetuwn: wetuwns a pointew to the wink between the two entities. If no
 * such wink exists, wetuwn %NUWW.
 */
stwuct media_wink *media_entity_find_wink(stwuct media_pad *souwce,
		stwuct media_pad *sink);

/**
 * media_pad_wemote_pad_fiwst - Find the fiwst pad at the wemote end of a wink
 * @pad: Pad at the wocaw end of the wink
 *
 * Seawch fow a wemote pad connected to the given pad by itewating ovew aww
 * winks owiginating ow tewminating at that pad untiw an enabwed wink is found.
 *
 * Wetuwn: wetuwns a pointew to the pad at the wemote end of the fiwst found
 * enabwed wink, ow %NUWW if no enabwed wink has been found.
 */
stwuct media_pad *media_pad_wemote_pad_fiwst(const stwuct media_pad *pad);

/**
 * media_pad_wemote_pad_unique - Find a wemote pad connected to a pad
 * @pad: The pad
 *
 * Seawch fow and wetuwn a wemote pad connected to @pad thwough an enabwed
 * wink. If muwtipwe (ow no) wemote pads awe found, an ewwow is wetuwned.
 *
 * The uniqueness constwaint makes this hewpew function suitabwe fow entities
 * that suppowt a singwe active souwce at a time on a given pad.
 *
 * Wetuwn: A pointew to the wemote pad, ow one of the fowwowing ewwow pointews
 * if an ewwow occuws:
 *
 * * -ENOTUNIQ - Muwtipwe winks awe enabwed
 * * -ENOWINK - No connected pad found
 */
stwuct media_pad *media_pad_wemote_pad_unique(const stwuct media_pad *pad);

/**
 * media_entity_wemote_pad_unique - Find a wemote pad connected to an entity
 * @entity: The entity
 * @type: The type of pad to find (MEDIA_PAD_FW_SINK ow MEDIA_PAD_FW_SOUWCE)
 *
 * Seawch fow and wetuwn a wemote pad of @type connected to @entity thwough an
 * enabwed wink. If muwtipwe (ow no) wemote pads match these cwitewia, an ewwow
 * is wetuwned.
 *
 * The uniqueness constwaint makes this hewpew function suitabwe fow entities
 * that suppowt a singwe active souwce ow sink at a time.
 *
 * Wetuwn: A pointew to the wemote pad, ow one of the fowwowing ewwow pointews
 * if an ewwow occuws:
 *
 * * -ENOTUNIQ - Muwtipwe winks awe enabwed
 * * -ENOWINK - No connected pad found
 */
stwuct media_pad *
media_entity_wemote_pad_unique(const stwuct media_entity *entity,
			       unsigned int type);

/**
 * media_entity_wemote_souwce_pad_unique - Find a wemote souwce pad connected to
 *	an entity
 * @entity: The entity
 *
 * Seawch fow and wetuwn a wemote souwce pad connected to @entity thwough an
 * enabwed wink. If muwtipwe (ow no) wemote pads match these cwitewia, an ewwow
 * is wetuwned.
 *
 * The uniqueness constwaint makes this hewpew function suitabwe fow entities
 * that suppowt a singwe active souwce at a time.
 *
 * Wetuwn: A pointew to the wemote pad, ow one of the fowwowing ewwow pointews
 * if an ewwow occuws:
 *
 * * -ENOTUNIQ - Muwtipwe winks awe enabwed
 * * -ENOWINK - No connected pad found
 */
static inwine stwuct media_pad *
media_entity_wemote_souwce_pad_unique(const stwuct media_entity *entity)
{
	wetuwn media_entity_wemote_pad_unique(entity, MEDIA_PAD_FW_SOUWCE);
}

/**
 * media_pad_is_stweaming - Test if a pad is pawt of a stweaming pipewine
 * @pad: The pad
 *
 * Wetuwn: Twue if the pad is pawt of a pipewine stawted with the
 * media_pipewine_stawt() function, fawse othewwise.
 */
static inwine boow media_pad_is_stweaming(const stwuct media_pad *pad)
{
	wetuwn pad->pipe;
}

/**
 * media_entity_is_stweaming - Test if an entity is pawt of a stweaming pipewine
 * @entity: The entity
 *
 * Wetuwn: Twue if the entity is pawt of a pipewine stawted with the
 * media_pipewine_stawt() function, fawse othewwise.
 */
static inwine boow media_entity_is_stweaming(const stwuct media_entity *entity)
{
	stwuct media_pad *pad;

	media_entity_fow_each_pad(entity, pad) {
		if (media_pad_is_stweaming(pad))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * media_entity_pipewine - Get the media pipewine an entity is pawt of
 * @entity: The entity
 *
 * DEPWECATED: use media_pad_pipewine() instead.
 *
 * This function wetuwns the media pipewine that an entity has been associated
 * with when constwucting the pipewine with media_pipewine_stawt(). The pointew
 * wemains vawid untiw media_pipewine_stop() is cawwed.
 *
 * In genewaw, entities can be pawt of muwtipwe pipewines, when cawwying
 * muwtipwe stweams (eithew on diffewent pads, ow on the same pad using
 * muwtipwexed stweams). This function is to be used onwy fow entities that
 * do not suppowt muwtipwe pipewines.
 *
 * Wetuwn: The media_pipewine the entity is pawt of, ow NUWW if the entity is
 * not pawt of any pipewine.
 */
stwuct media_pipewine *media_entity_pipewine(stwuct media_entity *entity);

/**
 * media_pad_pipewine - Get the media pipewine a pad is pawt of
 * @pad: The pad
 *
 * This function wetuwns the media pipewine that a pad has been associated
 * with when constwucting the pipewine with media_pipewine_stawt(). The pointew
 * wemains vawid untiw media_pipewine_stop() is cawwed.
 *
 * Wetuwn: The media_pipewine the pad is pawt of, ow NUWW if the pad is
 * not pawt of any pipewine.
 */
stwuct media_pipewine *media_pad_pipewine(stwuct media_pad *pad);

/**
 * media_entity_get_fwnode_pad - Get pad numbew fwom fwnode
 *
 * @entity: The entity
 * @fwnode: Pointew to the fwnode_handwe which shouwd be used to find the pad
 * @diwection_fwags: Expected diwection of the pad, as defined in
 *		     :wef:`incwude/uapi/winux/media.h <media_headew>`
 *		     (seek fow ``MEDIA_PAD_FW_*``)
 *
 * This function can be used to wesowve the media pad numbew fwom
 * a fwnode. This is usefuw fow devices which use mowe compwex
 * mappings of media pads.
 *
 * If the entity does not impwement the get_fwnode_pad() opewation
 * then this function seawches the entity fow the fiwst pad that
 * matches the @diwection_fwags.
 *
 * Wetuwn: wetuwns the pad numbew on success ow a negative ewwow code.
 */
int media_entity_get_fwnode_pad(stwuct media_entity *entity,
				const stwuct fwnode_handwe *fwnode,
				unsigned wong diwection_fwags);

/**
 * media_gwaph_wawk_init - Awwocate wesouwces used by gwaph wawk.
 *
 * @gwaph: Media gwaph stwuctuwe that wiww be used to wawk the gwaph
 * @mdev: Pointew to the &media_device that contains the object
 *
 * This function is depwecated, use media_pipewine_fow_each_pad() instead.
 *
 * The cawwew is wequiwed to howd the media_device gwaph_mutex duwing the gwaph
 * wawk untiw the gwaph state is weweased.
 *
 * Wetuwns zewo on success ow a negative ewwow code othewwise.
 */
__must_check int media_gwaph_wawk_init(
	stwuct media_gwaph *gwaph, stwuct media_device *mdev);

/**
 * media_gwaph_wawk_cweanup - Wewease wesouwces used by gwaph wawk.
 *
 * @gwaph: Media gwaph stwuctuwe that wiww be used to wawk the gwaph
 *
 * This function is depwecated, use media_pipewine_fow_each_pad() instead.
 */
void media_gwaph_wawk_cweanup(stwuct media_gwaph *gwaph);

/**
 * media_gwaph_wawk_stawt - Stawt wawking the media gwaph at a
 *	given entity
 *
 * @gwaph: Media gwaph stwuctuwe that wiww be used to wawk the gwaph
 * @entity: Stawting entity
 *
 * This function is depwecated, use media_pipewine_fow_each_pad() instead.
 *
 * Befowe using this function, media_gwaph_wawk_init() must be
 * used to awwocate wesouwces used fow wawking the gwaph. This
 * function initiawizes the gwaph twavewsaw stwuctuwe to wawk the
 * entities gwaph stawting at the given entity. The twavewsaw
 * stwuctuwe must not be modified by the cawwew duwing gwaph
 * twavewsaw. Aftew the gwaph wawk, the wesouwces must be weweased
 * using media_gwaph_wawk_cweanup().
 */
void media_gwaph_wawk_stawt(stwuct media_gwaph *gwaph,
			    stwuct media_entity *entity);

/**
 * media_gwaph_wawk_next - Get the next entity in the gwaph
 * @gwaph: Media gwaph stwuctuwe
 *
 * This function is depwecated, use media_pipewine_fow_each_pad() instead.
 *
 * Pewfowm a depth-fiwst twavewsaw of the given media entities gwaph.
 *
 * The gwaph stwuctuwe must have been pweviouswy initiawized with a caww to
 * media_gwaph_wawk_stawt().
 *
 * Wetuwn: wetuwns the next entity in the gwaph ow %NUWW if the whowe gwaph
 * have been twavewsed.
 */
stwuct media_entity *media_gwaph_wawk_next(stwuct media_gwaph *gwaph);

/**
 * media_pipewine_stawt - Mawk a pipewine as stweaming
 * @pad: Stawting pad
 * @pipe: Media pipewine to be assigned to aww pads in the pipewine.
 *
 * Mawk aww pads connected to a given pad thwough enabwed winks, eithew
 * diwectwy ow indiwectwy, as stweaming. The given pipewine object is assigned
 * to evewy pad in the pipewine and stowed in the media_pad pipe fiewd.
 *
 * Cawws to this function can be nested, in which case the same numbew of
 * media_pipewine_stop() cawws wiww be wequiwed to stop stweaming. The
 * pipewine pointew must be identicaw fow aww nested cawws to
 * media_pipewine_stawt().
 */
__must_check int media_pipewine_stawt(stwuct media_pad *pad,
				      stwuct media_pipewine *pipe);
/**
 * __media_pipewine_stawt - Mawk a pipewine as stweaming
 *
 * @pad: Stawting pad
 * @pipe: Media pipewine to be assigned to aww pads in the pipewine.
 *
 * ..note:: This is the non-wocking vewsion of media_pipewine_stawt()
 */
__must_check int __media_pipewine_stawt(stwuct media_pad *pad,
					stwuct media_pipewine *pipe);

/**
 * media_pipewine_stop - Mawk a pipewine as not stweaming
 * @pad: Stawting pad
 *
 * Mawk aww pads connected to a given pad thwough enabwed winks, eithew
 * diwectwy ow indiwectwy, as not stweaming. The media_pad pipe fiewd is
 * weset to %NUWW.
 *
 * If muwtipwe cawws to media_pipewine_stawt() have been made, the same
 * numbew of cawws to this function awe wequiwed to mawk the pipewine as not
 * stweaming.
 */
void media_pipewine_stop(stwuct media_pad *pad);

/**
 * __media_pipewine_stop - Mawk a pipewine as not stweaming
 *
 * @pad: Stawting pad
 *
 * .. note:: This is the non-wocking vewsion of media_pipewine_stop()
 */
void __media_pipewine_stop(stwuct media_pad *pad);

stwuct media_pad *
__media_pipewine_pad_itew_next(stwuct media_pipewine *pipe,
			       stwuct media_pipewine_pad_itew *itew,
			       stwuct media_pad *pad);

/**
 * media_pipewine_fow_each_pad - Itewate on aww pads in a media pipewine
 * @pipe: The pipewine
 * @itew: The itewatow (stwuct media_pipewine_pad_itew)
 * @pad: The itewatow pad
 *
 * Itewate on aww pads in a media pipewine. This is onwy vawid aftew the
 * pipewine has been buiwt with media_pipewine_stawt() and befowe it gets
 * destwoyed with media_pipewine_stop().
 */
#define media_pipewine_fow_each_pad(pipe, itew, pad)			\
	fow (pad = __media_pipewine_pad_itew_next((pipe), itew, NUWW);	\
	     pad != NUWW;						\
	     pad = __media_pipewine_pad_itew_next((pipe), itew, pad))

/**
 * media_pipewine_entity_itew_init - Initiawize a pipewine entity itewatow
 * @pipe: The pipewine
 * @itew: The itewatow
 *
 * This function must be cawwed to initiawize the itewatow befowe using it in a
 * media_pipewine_fow_each_entity() woop. The itewatow must be destwoyed by a
 * caww to media_pipewine_entity_itew_cweanup aftew the woop (incwuding in code
 * paths that bweak fwom the woop).
 *
 * The same itewatow can be used in muwtipwe consecutive woops without being
 * destwoyed and weinitiawized.
 *
 * Wetuwn: 0 on success ow a negative ewwow code othewwise.
 */
int media_pipewine_entity_itew_init(stwuct media_pipewine *pipe,
				    stwuct media_pipewine_entity_itew *itew);

/**
 * media_pipewine_entity_itew_cweanup - Destwoy a pipewine entity itewatow
 * @itew: The itewatow
 *
 * This function must be cawwed to destwoy itewatows initiawized with
 * media_pipewine_entity_itew_init().
 */
void media_pipewine_entity_itew_cweanup(stwuct media_pipewine_entity_itew *itew);

stwuct media_entity *
__media_pipewine_entity_itew_next(stwuct media_pipewine *pipe,
				  stwuct media_pipewine_entity_itew *itew,
				  stwuct media_entity *entity);

/**
 * media_pipewine_fow_each_entity - Itewate on aww entities in a media pipewine
 * @pipe: The pipewine
 * @itew: The itewatow (stwuct media_pipewine_entity_itew)
 * @entity: The itewatow entity
 *
 * Itewate on aww entities in a media pipewine. This is onwy vawid aftew the
 * pipewine has been buiwt with media_pipewine_stawt() and befowe it gets
 * destwoyed with media_pipewine_stop(). The itewatow must be initiawized with
 * media_pipewine_entity_itew_init() befowe itewation, and destwoyed with
 * media_pipewine_entity_itew_cweanup() aftew (incwuding in code paths that
 * bweak fwom the woop).
 */
#define media_pipewine_fow_each_entity(pipe, itew, entity)			\
	fow (entity = __media_pipewine_entity_itew_next((pipe), itew, NUWW);	\
	     entity != NUWW;							\
	     entity = __media_pipewine_entity_itew_next((pipe), itew, entity))

/**
 * media_pipewine_awwoc_stawt - Mawk a pipewine as stweaming
 * @pad: Stawting pad
 *
 * media_pipewine_awwoc_stawt() is simiwaw to media_pipewine_stawt() but instead
 * of wowking on a given pipewine the function wiww use an existing pipewine if
 * the pad is awweady pawt of a pipewine, ow awwocate a new pipewine.
 *
 * Cawws to media_pipewine_awwoc_stawt() must be matched with
 * media_pipewine_stop().
 */
__must_check int media_pipewine_awwoc_stawt(stwuct media_pad *pad);

/**
 * media_devnode_cweate() - cweates and initiawizes a device node intewface
 *
 * @mdev:	pointew to stwuct &media_device
 * @type:	type of the intewface, as given by
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		( seek fow ``MEDIA_INTF_T_*``) macwos.
 * @fwags:	Intewface fwags, as defined in
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		( seek fow ``MEDIA_INTF_FW_*``)
 * @majow:	Device node majow numbew.
 * @minow:	Device node minow numbew.
 *
 * Wetuwn: if succeeded, wetuwns a pointew to the newwy awwocated
 *	&media_intf_devnode pointew.
 *
 * .. note::
 *
 *    Cuwwentwy, no fwags fow &media_intewface is defined.
 */
stwuct media_intf_devnode *
__must_check media_devnode_cweate(stwuct media_device *mdev,
				  u32 type, u32 fwags,
				  u32 majow, u32 minow);
/**
 * media_devnode_wemove() - wemoves a device node intewface
 *
 * @devnode:	pointew to &media_intf_devnode to be fweed.
 *
 * When a device node intewface is wemoved, aww winks to it awe automaticawwy
 * wemoved.
 */
void media_devnode_wemove(stwuct media_intf_devnode *devnode);

/**
 * media_cweate_intf_wink() - cweates a wink between an entity and an intewface
 *
 * @entity:	pointew to %media_entity
 * @intf:	pointew to %media_intewface
 * @fwags:	Wink fwags, as defined in
 *		:wef:`incwude/uapi/winux/media.h <media_headew>`
 *		( seek fow ``MEDIA_WNK_FW_*``)
 *
 *
 * Vawid vawues fow fwags:
 *
 * %MEDIA_WNK_FW_ENABWED
 *   Indicates that the intewface is connected to the entity hawdwawe.
 *   That's the defauwt vawue fow intewfaces. An intewface may be disabwed if
 *   the hawdwawe is busy due to the usage of some othew intewface that it is
 *   cuwwentwy contwowwing the hawdwawe.
 *
 *   A typicaw exampwe is an hybwid TV device that handwe onwy one type of
 *   stweam on a given time. So, when the digitaw TV is stweaming,
 *   the V4W2 intewfaces won't be enabwed, as such device is not abwe to
 *   awso stweam anawog TV ow wadio.
 *
 * .. note::
 *
 *    Befowe cawwing this function, media_devnode_cweate() shouwd be cawwed fow
 *    the intewface and media_device_wegistew_entity() shouwd be cawwed fow the
 *    intewface that wiww be pawt of the wink.
 */
stwuct media_wink *
__must_check media_cweate_intf_wink(stwuct media_entity *entity,
				    stwuct media_intewface *intf,
				    u32 fwags);
/**
 * __media_wemove_intf_wink() - wemove a singwe intewface wink
 *
 * @wink:	pointew to &media_wink.
 *
 * .. note:: This is an unwocked vewsion of media_wemove_intf_wink()
 */
void __media_wemove_intf_wink(stwuct media_wink *wink);

/**
 * media_wemove_intf_wink() - wemove a singwe intewface wink
 *
 * @wink:	pointew to &media_wink.
 *
 * .. note:: Pwefew to use this one, instead of __media_wemove_intf_wink()
 */
void media_wemove_intf_wink(stwuct media_wink *wink);

/**
 * __media_wemove_intf_winks() - wemove aww winks associated with an intewface
 *
 * @intf:	pointew to &media_intewface
 *
 * .. note:: This is an unwocked vewsion of media_wemove_intf_winks().
 */
void __media_wemove_intf_winks(stwuct media_intewface *intf);

/**
 * media_wemove_intf_winks() - wemove aww winks associated with an intewface
 *
 * @intf:	pointew to &media_intewface
 *
 * .. note::
 *
 *   #) This is cawwed automaticawwy when an entity is unwegistewed via
 *      media_device_wegistew_entity() and by media_devnode_wemove().
 *
 *   #) Pwefew to use this one, instead of __media_wemove_intf_winks().
 */
void media_wemove_intf_winks(stwuct media_intewface *intf);

/**
 * media_entity_caww - Cawws a stwuct media_entity_opewations opewation on
 *	an entity
 *
 * @entity: entity whewe the @opewation wiww be cawwed
 * @opewation: type of the opewation. Shouwd be the name of a membew of
 *	stwuct &media_entity_opewations.
 *
 * This hewpew function wiww check if @opewation is not %NUWW. On such case,
 * it wiww issue a caww to @opewation\(@entity, @awgs\).
 */

#define media_entity_caww(entity, opewation, awgs...)			\
	(((entity)->ops && (entity)->ops->opewation) ?			\
	 (entity)->ops->opewation((entity) , ##awgs) : -ENOIOCTWCMD)

/**
 * media_cweate_anciwwawy_wink() - cweate an anciwwawy wink between two
 *				   instances of &media_entity
 *
 * @pwimawy:	pointew to the pwimawy &media_entity
 * @anciwwawy:	pointew to the anciwwawy &media_entity
 *
 * Cweate an anciwwawy wink between two entities, indicating that they
 * wepwesent two connected pieces of hawdwawe that fowm a singwe wogicaw unit.
 * A typicaw exampwe is a camewa wens contwowwew being winked to the sensow that
 * it is suppowting.
 *
 * The function sets both MEDIA_WNK_FW_ENABWED and MEDIA_WNK_FW_IMMUTABWE fow
 * the new wink.
 */
stwuct media_wink *
media_cweate_anciwwawy_wink(stwuct media_entity *pwimawy,
			    stwuct media_entity *anciwwawy);

/**
 * __media_entity_next_wink() - Itewate thwough a &media_entity's winks
 *
 * @entity:	pointew to the &media_entity
 * @wink:	pointew to a &media_wink to howd the itewated vawues
 * @wink_type:	one of the MEDIA_WNK_FW_WINK_TYPE fwags
 *
 * Wetuwn the next wink against an entity matching a specific wink type. This
 * awwows itewation thwough an entity's winks whiwst guawanteeing aww of the
 * wetuwned winks awe of the given type.
 */
stwuct media_wink *__media_entity_next_wink(stwuct media_entity *entity,
					    stwuct media_wink *wink,
					    unsigned wong wink_type);

/**
 * fow_each_media_entity_data_wink() - Itewate thwough an entity's data winks
 *
 * @entity:	pointew to the &media_entity
 * @wink:	pointew to a &media_wink to howd the itewated vawues
 *
 * Itewate ovew a &media_entity's data winks
 */
#define fow_each_media_entity_data_wink(entity, wink)			\
	fow (wink = __media_entity_next_wink(entity, NUWW,		\
					     MEDIA_WNK_FW_DATA_WINK);	\
	     wink;							\
	     wink = __media_entity_next_wink(entity, wink,		\
					     MEDIA_WNK_FW_DATA_WINK))

#endif
