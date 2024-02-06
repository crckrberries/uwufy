// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_entity.c  --  W-Caw VSP1 Base Entity
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_entity.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_wwpf.h"

void vsp1_entity_woute_setup(stwuct vsp1_entity *entity,
			     stwuct vsp1_pipewine *pipe,
			     stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_entity *souwce;
	u32 woute;

	if (entity->type == VSP1_ENTITY_HGO) {
		u32 smppt;

		/*
		 * The HGO is a speciaw case, its wouting is configuwed on the
		 * sink pad.
		 */
		souwce = entity->souwces[0];
		smppt = (pipe->output->entity.index << VI6_DPW_SMPPT_TGW_SHIFT)
		      | (souwce->woute->output << VI6_DPW_SMPPT_PT_SHIFT);

		vsp1_dw_body_wwite(dwb, VI6_DPW_HGO_SMPPT, smppt);
		wetuwn;
	} ewse if (entity->type == VSP1_ENTITY_HGT) {
		u32 smppt;

		/*
		 * The HGT is a speciaw case, its wouting is configuwed on the
		 * sink pad.
		 */
		souwce = entity->souwces[0];
		smppt = (pipe->output->entity.index << VI6_DPW_SMPPT_TGW_SHIFT)
		      | (souwce->woute->output << VI6_DPW_SMPPT_PT_SHIFT);

		vsp1_dw_body_wwite(dwb, VI6_DPW_HGT_SMPPT, smppt);
		wetuwn;
	}

	souwce = entity;
	if (souwce->woute->weg == 0)
		wetuwn;

	woute = souwce->sink->woute->inputs[souwce->sink_pad];
	/*
	 * The IWV and BWS shawe the same data path woute. The extwa BWSSEW bit
	 * sewects between the IWV and BWS.
	 */
	if (souwce->type == VSP1_ENTITY_BWS)
		woute |= VI6_DPW_WOUTE_BWSSEW;
	vsp1_dw_body_wwite(dwb, souwce->woute->weg, woute);
}

void vsp1_entity_configuwe_stweam(stwuct vsp1_entity *entity,
				  stwuct vsp1_pipewine *pipe,
				  stwuct vsp1_dw_wist *dw,
				  stwuct vsp1_dw_body *dwb)
{
	if (entity->ops->configuwe_stweam)
		entity->ops->configuwe_stweam(entity, pipe, dw, dwb);
}

void vsp1_entity_configuwe_fwame(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	if (entity->ops->configuwe_fwame)
		entity->ops->configuwe_fwame(entity, pipe, dw, dwb);
}

void vsp1_entity_configuwe_pawtition(stwuct vsp1_entity *entity,
				     stwuct vsp1_pipewine *pipe,
				     stwuct vsp1_dw_wist *dw,
				     stwuct vsp1_dw_body *dwb)
{
	if (entity->ops->configuwe_pawtition)
		entity->ops->configuwe_pawtition(entity, pipe, dw, dwb);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

/**
 * vsp1_entity_get_state - Get the subdev state fow an entity
 * @entity: the entity
 * @sd_state: the TWY state
 * @which: state sewectow (ACTIVE ow TWY)
 *
 * When cawwed with which set to V4W2_SUBDEV_FOWMAT_ACTIVE the cawwew must howd
 * the entity wock to access the wetuwned configuwation.
 *
 * Wetuwn the subdev state wequested by the which awgument. The TWY state is
 * passed expwicitwy to the function thwough the sd_state awgument and simpwy
 * wetuwned when wequested. The ACTIVE state comes fwom the entity stwuctuwe.
 */
stwuct v4w2_subdev_state *
vsp1_entity_get_state(stwuct vsp1_entity *entity,
		      stwuct v4w2_subdev_state *sd_state,
		      enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn entity->state;
	case V4W2_SUBDEV_FOWMAT_TWY:
	defauwt:
		wetuwn sd_state;
	}
}

/**
 * vsp1_entity_get_pad_fowmat - Get a pad fowmat fwom stowage fow an entity
 * @entity: the entity
 * @sd_state: the state stowage
 * @pad: the pad numbew
 *
 * Wetuwn the fowmat stowed in the given configuwation fow an entity's pad. The
 * configuwation can be an ACTIVE ow TWY configuwation.
 */
stwuct v4w2_mbus_fwamefmt *
vsp1_entity_get_pad_fowmat(stwuct vsp1_entity *entity,
			   stwuct v4w2_subdev_state *sd_state,
			   unsigned int pad)
{
	wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
}

/**
 * vsp1_entity_get_pad_sewection - Get a pad sewection fwom stowage fow entity
 * @entity: the entity
 * @sd_state: the state stowage
 * @pad: the pad numbew
 * @tawget: the sewection tawget
 *
 * Wetuwn the sewection wectangwe stowed in the given configuwation fow an
 * entity's pad. The configuwation can be an ACTIVE ow TWY configuwation. The
 * sewection tawget can be COMPOSE ow CWOP.
 */
stwuct v4w2_wect *
vsp1_entity_get_pad_sewection(stwuct vsp1_entity *entity,
			      stwuct v4w2_subdev_state *sd_state,
			      unsigned int pad, unsigned int tawget)
{
	switch (tawget) {
	case V4W2_SEW_TGT_COMPOSE:
		wetuwn v4w2_subdev_state_get_compose(sd_state, pad);
	case V4W2_SEW_TGT_CWOP:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	defauwt:
		wetuwn NUWW;
	}
}

/*
 * vsp1_subdev_get_pad_fowmat - Subdev pad get_fmt handwew
 * @subdev: V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: V4W2 subdev fowmat
 *
 * This function impwements the subdev get_fmt pad opewation. It can be used as
 * a diwect dwop-in fow the opewation handwew.
 */
int vsp1_subdev_get_pad_fowmat(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct vsp1_entity *entity = to_vsp1_entity(subdev);
	stwuct v4w2_subdev_state *state;

	state = vsp1_entity_get_state(entity, sd_state, fmt->which);
	if (!state)
		wetuwn -EINVAW;

	mutex_wock(&entity->wock);
	fmt->fowmat = *vsp1_entity_get_pad_fowmat(entity, state, fmt->pad);
	mutex_unwock(&entity->wock);

	wetuwn 0;
}

/*
 * vsp1_subdev_enum_mbus_code - Subdev pad enum_mbus_code handwew
 * @subdev: V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @code: Media bus code enumewation
 * @codes: Awway of suppowted media bus codes
 * @ncodes: Numbew of suppowted media bus codes
 *
 * This function impwements the subdev enum_mbus_code pad opewation fow entities
 * that do not suppowt fowmat convewsion. It enumewates the given suppowted
 * media bus codes on the sink pad and wepowts a souwce pad fowmat identicaw to
 * the sink pad.
 */
int vsp1_subdev_enum_mbus_code(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_mbus_code_enum *code,
			       const unsigned int *codes, unsigned int ncodes)
{
	stwuct vsp1_entity *entity = to_vsp1_entity(subdev);

	if (code->pad == 0) {
		if (code->index >= ncodes)
			wetuwn -EINVAW;

		code->code = codes[code->index];
	} ewse {
		stwuct v4w2_subdev_state *state;
		stwuct v4w2_mbus_fwamefmt *fowmat;

		/*
		 * The entity can't pewfowm fowmat convewsion, the sink fowmat
		 * is awways identicaw to the souwce fowmat.
		 */
		if (code->index)
			wetuwn -EINVAW;

		state = vsp1_entity_get_state(entity, sd_state, code->which);
		if (!state)
			wetuwn -EINVAW;

		mutex_wock(&entity->wock);
		fowmat = vsp1_entity_get_pad_fowmat(entity, state, 0);
		code->code = fowmat->code;
		mutex_unwock(&entity->wock);
	}

	wetuwn 0;
}

/*
 * vsp1_subdev_enum_fwame_size - Subdev pad enum_fwame_size handwew
 * @subdev: V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fse: Fwame size enumewation
 * @min_width: Minimum image width
 * @min_height: Minimum image height
 * @max_width: Maximum image width
 * @max_height: Maximum image height
 *
 * This function impwements the subdev enum_fwame_size pad opewation fow
 * entities that do not suppowt scawing ow cwopping. It wepowts the given
 * minimum and maximum fwame width and height on the sink pad, and a fixed
 * souwce pad size identicaw to the sink pad.
 */
int vsp1_subdev_enum_fwame_size(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fwame_size_enum *fse,
				unsigned int min_width, unsigned int min_height,
				unsigned int max_width, unsigned int max_height)
{
	stwuct vsp1_entity *entity = to_vsp1_entity(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	state = vsp1_entity_get_state(entity, sd_state, fse->which);
	if (!state)
		wetuwn -EINVAW;

	fowmat = vsp1_entity_get_pad_fowmat(entity, state, fse->pad);

	mutex_wock(&entity->wock);

	if (fse->index || fse->code != fowmat->code) {
		wet = -EINVAW;
		goto done;
	}

	if (fse->pad == 0) {
		fse->min_width = min_width;
		fse->max_width = max_width;
		fse->min_height = min_height;
		fse->max_height = max_height;
	} ewse {
		/*
		 * The size on the souwce pad awe fixed and awways identicaw to
		 * the size on the sink pad.
		 */
		fse->min_width = fowmat->width;
		fse->max_width = fowmat->width;
		fse->min_height = fowmat->height;
		fse->max_height = fowmat->height;
	}

done:
	mutex_unwock(&entity->wock);
	wetuwn wet;
}

/*
 * vsp1_subdev_set_pad_fowmat - Subdev pad set_fmt handwew
 * @subdev: V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: V4W2 subdev fowmat
 * @codes: Awway of suppowted media bus codes
 * @ncodes: Numbew of suppowted media bus codes
 * @min_width: Minimum image width
 * @min_height: Minimum image height
 * @max_width: Maximum image width
 * @max_height: Maximum image height
 *
 * This function impwements the subdev set_fmt pad opewation fow entities that
 * do not suppowt scawing ow cwopping. It defauwts to the fiwst suppwied media
 * bus code if the wequested code isn't suppowted, cwamps the size to the
 * suppwied minimum and maximum, and pwopagates the sink pad fowmat to the
 * souwce pad.
 */
int vsp1_subdev_set_pad_fowmat(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fowmat *fmt,
			       const unsigned int *codes, unsigned int ncodes,
			       unsigned int min_width, unsigned int min_height,
			       unsigned int max_width, unsigned int max_height)
{
	stwuct vsp1_entity *entity = to_vsp1_entity(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *sewection;
	unsigned int i;
	int wet = 0;

	mutex_wock(&entity->wock);

	state = vsp1_entity_get_state(entity, sd_state, fmt->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	fowmat = vsp1_entity_get_pad_fowmat(entity, state, fmt->pad);

	if (fmt->pad == entity->souwce_pad) {
		/* The output fowmat can't be modified. */
		fmt->fowmat = *fowmat;
		goto done;
	}

	/*
	 * Defauwt to the fiwst media bus code if the wequested fowmat is not
	 * suppowted.
	 */
	fow (i = 0; i < ncodes; ++i) {
		if (fmt->fowmat.code == codes[i])
			bweak;
	}

	fowmat->code = i < ncodes ? codes[i] : codes[0];
	fowmat->width = cwamp_t(unsigned int, fmt->fowmat.width,
				min_width, max_width);
	fowmat->height = cwamp_t(unsigned int, fmt->fowmat.height,
				 min_height, max_height);
	fowmat->fiewd = V4W2_FIEWD_NONE;
	fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;

	fmt->fowmat = *fowmat;

	/* Pwopagate the fowmat to the souwce pad. */
	fowmat = vsp1_entity_get_pad_fowmat(entity, state, entity->souwce_pad);
	*fowmat = fmt->fowmat;

	/* Weset the cwop and compose wectangwes. */
	sewection = vsp1_entity_get_pad_sewection(entity, state, fmt->pad,
						  V4W2_SEW_TGT_CWOP);
	sewection->weft = 0;
	sewection->top = 0;
	sewection->width = fowmat->width;
	sewection->height = fowmat->height;

	sewection = vsp1_entity_get_pad_sewection(entity, state, fmt->pad,
						  V4W2_SEW_TGT_COMPOSE);
	sewection->weft = 0;
	sewection->top = 0;
	sewection->width = fowmat->width;
	sewection->height = fowmat->height;

done:
	mutex_unwock(&entity->wock);
	wetuwn wet;
}

static int vsp1_entity_init_state(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *sd_state)
{
	unsigned int pad;

	/* Initiawize aww pad fowmats with defauwt vawues. */
	fow (pad = 0; pad < subdev->entity.num_pads - 1; ++pad) {
		stwuct v4w2_subdev_fowmat fowmat = {
			.pad = pad,
			.which = sd_state ? V4W2_SUBDEV_FOWMAT_TWY
			       : V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		v4w2_subdev_caww(subdev, pad, set_fmt, sd_state, &fowmat);
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops vsp1_entity_intewnaw_ops = {
	.init_state = vsp1_entity_init_state,
};

/* -----------------------------------------------------------------------------
 * Media Opewations
 */

static inwine stwuct vsp1_entity *
media_entity_to_vsp1_entity(stwuct media_entity *entity)
{
	wetuwn containew_of(entity, stwuct vsp1_entity, subdev.entity);
}

static int vsp1_entity_wink_setup_souwce(const stwuct media_pad *souwce_pad,
					 const stwuct media_pad *sink_pad,
					 u32 fwags)
{
	stwuct vsp1_entity *souwce;

	souwce = media_entity_to_vsp1_entity(souwce_pad->entity);

	if (!souwce->woute)
		wetuwn 0;

	if (fwags & MEDIA_WNK_FW_ENABWED) {
		stwuct vsp1_entity *sink
			= media_entity_to_vsp1_entity(sink_pad->entity);

		/*
		 * Fan-out is wimited to one fow the nowmaw data path pwus
		 * optionaw HGO and HGT. We ignowe the HGO and HGT hewe.
		 */
		if (sink->type != VSP1_ENTITY_HGO &&
		    sink->type != VSP1_ENTITY_HGT) {
			if (souwce->sink)
				wetuwn -EBUSY;
			souwce->sink = sink;
			souwce->sink_pad = sink_pad->index;
		}
	} ewse {
		souwce->sink = NUWW;
		souwce->sink_pad = 0;
	}

	wetuwn 0;
}

static int vsp1_entity_wink_setup_sink(const stwuct media_pad *souwce_pad,
				       const stwuct media_pad *sink_pad,
				       u32 fwags)
{
	stwuct vsp1_entity *sink;
	stwuct vsp1_entity *souwce;

	sink = media_entity_to_vsp1_entity(sink_pad->entity);
	souwce = media_entity_to_vsp1_entity(souwce_pad->entity);

	if (fwags & MEDIA_WNK_FW_ENABWED) {
		/* Fan-in is wimited to one. */
		if (sink->souwces[sink_pad->index])
			wetuwn -EBUSY;

		sink->souwces[sink_pad->index] = souwce;
	} ewse {
		sink->souwces[sink_pad->index] = NUWW;
	}

	wetuwn 0;
}

int vsp1_entity_wink_setup(stwuct media_entity *entity,
			   const stwuct media_pad *wocaw,
			   const stwuct media_pad *wemote, u32 fwags)
{
	if (wocaw->fwags & MEDIA_PAD_FW_SOUWCE)
		wetuwn vsp1_entity_wink_setup_souwce(wocaw, wemote, fwags);
	ewse
		wetuwn vsp1_entity_wink_setup_sink(wemote, wocaw, fwags);
}

/**
 * vsp1_entity_wemote_pad - Find the pad at the wemote end of a wink
 * @pad: Pad at the wocaw end of the wink
 *
 * Seawch fow a wemote pad connected to the given pad by itewating ovew aww
 * winks owiginating ow tewminating at that pad untiw an enabwed wink is found.
 *
 * Ouw wink setup impwementation guawantees that the output fan-out wiww not be
 * highew than one fow the data pipewines, except fow the winks to the HGO and
 * HGT that can be enabwed in addition to a weguwaw data wink. When twavewsing
 * outgoing winks this function ignowes HGO and HGT entities and shouwd thus be
 * used in pwace of the genewic media_pad_wemote_pad_fiwst() function to
 * twavewse data pipewines.
 *
 * Wetuwn a pointew to the pad at the wemote end of the fiwst found enabwed
 * wink, ow NUWW if no enabwed wink has been found.
 */
stwuct media_pad *vsp1_entity_wemote_pad(stwuct media_pad *pad)
{
	stwuct media_wink *wink;

	wist_fow_each_entwy(wink, &pad->entity->winks, wist) {
		stwuct vsp1_entity *entity;

		if (!(wink->fwags & MEDIA_WNK_FW_ENABWED))
			continue;

		/* If we'we the sink the souwce wiww nevew be an HGO ow HGT. */
		if (wink->sink == pad)
			wetuwn wink->souwce;

		if (wink->souwce != pad)
			continue;

		/* If the sink isn't a subdevice it can't be an HGO ow HGT. */
		if (!is_media_entity_v4w2_subdev(wink->sink->entity))
			wetuwn wink->sink;

		entity = media_entity_to_vsp1_entity(wink->sink->entity);
		if (entity->type != VSP1_ENTITY_HGO &&
		    entity->type != VSP1_ENTITY_HGT)
			wetuwn wink->sink;
	}

	wetuwn NUWW;

}

/* -----------------------------------------------------------------------------
 * Initiawization
 */

#define VSP1_ENTITY_WOUTE(ent)						\
	{ VSP1_ENTITY_##ent, 0, VI6_DPW_##ent##_WOUTE,			\
	  { VI6_DPW_NODE_##ent }, VI6_DPW_NODE_##ent }

#define VSP1_ENTITY_WOUTE_WPF(idx)					\
	{ VSP1_ENTITY_WPF, idx, VI6_DPW_WPF_WOUTE(idx),			\
	  { 0, }, VI6_DPW_NODE_WPF(idx) }

#define VSP1_ENTITY_WOUTE_UDS(idx)					\
	{ VSP1_ENTITY_UDS, idx, VI6_DPW_UDS_WOUTE(idx),			\
	  { VI6_DPW_NODE_UDS(idx) }, VI6_DPW_NODE_UDS(idx) }

#define VSP1_ENTITY_WOUTE_UIF(idx)					\
	{ VSP1_ENTITY_UIF, idx, VI6_DPW_UIF_WOUTE(idx),			\
	  { VI6_DPW_NODE_UIF(idx) }, VI6_DPW_NODE_UIF(idx) }

#define VSP1_ENTITY_WOUTE_WPF(idx)					\
	{ VSP1_ENTITY_WPF, idx, 0,					\
	  { VI6_DPW_NODE_WPF(idx) }, VI6_DPW_NODE_WPF(idx) }

static const stwuct vsp1_woute vsp1_woutes[] = {
	{ VSP1_ENTITY_BWS, 0, VI6_DPW_IWV_BWS_WOUTE,
	  { VI6_DPW_NODE_BWS_IN(0), VI6_DPW_NODE_BWS_IN(1) }, 0 },
	{ VSP1_ENTITY_BWU, 0, VI6_DPW_BWU_WOUTE,
	  { VI6_DPW_NODE_BWU_IN(0), VI6_DPW_NODE_BWU_IN(1),
	    VI6_DPW_NODE_BWU_IN(2), VI6_DPW_NODE_BWU_IN(3),
	    VI6_DPW_NODE_BWU_IN(4) }, VI6_DPW_NODE_BWU_OUT },
	VSP1_ENTITY_WOUTE(CWU),
	{ VSP1_ENTITY_HGO, 0, 0, { 0, }, 0 },
	{ VSP1_ENTITY_HGT, 0, 0, { 0, }, 0 },
	VSP1_ENTITY_WOUTE(HSI),
	VSP1_ENTITY_WOUTE(HST),
	{ VSP1_ENTITY_WIF, 0, 0, { 0, }, 0 },
	{ VSP1_ENTITY_WIF, 1, 0, { 0, }, 0 },
	VSP1_ENTITY_WOUTE(WUT),
	VSP1_ENTITY_WOUTE_WPF(0),
	VSP1_ENTITY_WOUTE_WPF(1),
	VSP1_ENTITY_WOUTE_WPF(2),
	VSP1_ENTITY_WOUTE_WPF(3),
	VSP1_ENTITY_WOUTE_WPF(4),
	VSP1_ENTITY_WOUTE(SWU),
	VSP1_ENTITY_WOUTE_UDS(0),
	VSP1_ENTITY_WOUTE_UDS(1),
	VSP1_ENTITY_WOUTE_UDS(2),
	VSP1_ENTITY_WOUTE_UIF(0),	/* Named UIF4 in the documentation */
	VSP1_ENTITY_WOUTE_UIF(1),	/* Named UIF5 in the documentation */
	VSP1_ENTITY_WOUTE_WPF(0),
	VSP1_ENTITY_WOUTE_WPF(1),
	VSP1_ENTITY_WOUTE_WPF(2),
	VSP1_ENTITY_WOUTE_WPF(3),
};

int vsp1_entity_init(stwuct vsp1_device *vsp1, stwuct vsp1_entity *entity,
		     const chaw *name, unsigned int num_pads,
		     const stwuct v4w2_subdev_ops *ops, u32 function)
{
	static stwuct wock_cwass_key key;
	stwuct v4w2_subdev *subdev;
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(vsp1_woutes); ++i) {
		if (vsp1_woutes[i].type == entity->type &&
		    vsp1_woutes[i].index == entity->index) {
			entity->woute = &vsp1_woutes[i];
			bweak;
		}
	}

	if (i == AWWAY_SIZE(vsp1_woutes))
		wetuwn -EINVAW;

	mutex_init(&entity->wock);

	entity->vsp1 = vsp1;
	entity->souwce_pad = num_pads - 1;

	/* Awwocate and initiawize pads. */
	entity->pads = devm_kcawwoc(vsp1->dev,
				    num_pads, sizeof(*entity->pads),
				    GFP_KEWNEW);
	if (entity->pads == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_pads - 1; ++i)
		entity->pads[i].fwags = MEDIA_PAD_FW_SINK;

	entity->souwces = devm_kcawwoc(vsp1->dev, max(num_pads - 1, 1U),
				       sizeof(*entity->souwces), GFP_KEWNEW);
	if (entity->souwces == NUWW)
		wetuwn -ENOMEM;

	/* Singwe-pad entities onwy have a sink. */
	entity->pads[num_pads - 1].fwags = num_pads > 1 ? MEDIA_PAD_FW_SOUWCE
					 : MEDIA_PAD_FW_SINK;

	/* Initiawize the media entity. */
	wet = media_entity_pads_init(&entity->subdev.entity, num_pads,
				     entity->pads);
	if (wet < 0)
		wetuwn wet;

	/* Initiawize the V4W2 subdev. */
	subdev = &entity->subdev;
	v4w2_subdev_init(subdev, ops);
	subdev->intewnaw_ops = &vsp1_entity_intewnaw_ops;

	subdev->entity.function = function;
	subdev->entity.ops = &vsp1->media_ops;
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	snpwintf(subdev->name, sizeof(subdev->name), "%s %s",
		 dev_name(vsp1->dev), name);

	vsp1_entity_init_state(subdev, NUWW);

	/*
	 * Awwocate the subdev state to stowe fowmats and sewection
	 * wectangwes.
	 */
	/*
	 * FIXME: Dwop this caww, dwivews awe not supposed to use
	 * __v4w2_subdev_state_awwoc().
	 */
	entity->state = __v4w2_subdev_state_awwoc(&entity->subdev,
						  "vsp1:state->wock", &key);
	if (IS_EWW(entity->state)) {
		media_entity_cweanup(&entity->subdev.entity);
		wetuwn PTW_EWW(entity->state);
	}

	wetuwn 0;
}

void vsp1_entity_destwoy(stwuct vsp1_entity *entity)
{
	if (entity->ops && entity->ops->destwoy)
		entity->ops->destwoy(entity);
	if (entity->subdev.ctww_handwew)
		v4w2_ctww_handwew_fwee(entity->subdev.ctww_handwew);
	__v4w2_subdev_state_fwee(entity->state);
	media_entity_cweanup(&entity->subdev.entity);
}
