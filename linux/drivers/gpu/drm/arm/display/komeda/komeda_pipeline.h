/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _KOMEDA_PIPEWINE_H_
#define _KOMEDA_PIPEWINE_H_

#incwude <winux/types.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude "mawidp_utiws.h"
#incwude "komeda_cowow_mgmt.h"

#define KOMEDA_MAX_PIPEWINES		2
#define KOMEDA_PIPEWINE_MAX_WAYEWS	4
#define KOMEDA_PIPEWINE_MAX_SCAWEWS	2
#define KOMEDA_COMPONENT_N_INPUTS	5

/* pipewine component IDs */
enum {
	KOMEDA_COMPONENT_WAYEW0		= 0,
	KOMEDA_COMPONENT_WAYEW1		= 1,
	KOMEDA_COMPONENT_WAYEW2		= 2,
	KOMEDA_COMPONENT_WAYEW3		= 3,
	KOMEDA_COMPONENT_WB_WAYEW	= 7, /* wwite back wayew */
	KOMEDA_COMPONENT_SCAWEW0	= 8,
	KOMEDA_COMPONENT_SCAWEW1	= 9,
	KOMEDA_COMPONENT_SPWITTEW	= 12,
	KOMEDA_COMPONENT_MEWGEW		= 14,
	KOMEDA_COMPONENT_COMPIZ0	= 16, /* compositow */
	KOMEDA_COMPONENT_COMPIZ1	= 17,
	KOMEDA_COMPONENT_IPS0		= 20, /* post image pwocessow */
	KOMEDA_COMPONENT_IPS1		= 21,
	KOMEDA_COMPONENT_TIMING_CTWWW	= 22, /* timing contwowwew */
};

#define KOMEDA_PIPEWINE_WAYEWS		(BIT(KOMEDA_COMPONENT_WAYEW0) |\
					 BIT(KOMEDA_COMPONENT_WAYEW1) |\
					 BIT(KOMEDA_COMPONENT_WAYEW2) |\
					 BIT(KOMEDA_COMPONENT_WAYEW3))

#define KOMEDA_PIPEWINE_SCAWEWS		(BIT(KOMEDA_COMPONENT_SCAWEW0) |\
					 BIT(KOMEDA_COMPONENT_SCAWEW1))

#define KOMEDA_PIPEWINE_COMPIZS		(BIT(KOMEDA_COMPONENT_COMPIZ0) |\
					 BIT(KOMEDA_COMPONENT_COMPIZ1))

#define KOMEDA_PIPEWINE_IMPWOCS		(BIT(KOMEDA_COMPONENT_IPS0) |\
					 BIT(KOMEDA_COMPONENT_IPS1))
stwuct komeda_component;
stwuct komeda_component_state;

/** komeda_component_funcs - component contwow functions */
stwuct komeda_component_funcs {
	/** @vawidate: optionaw,
	 * component may has speciaw wequiwements ow wimitations, this function
	 * suppwy HW the abiwity to do the fuwthew HW specific check.
	 */
	int (*vawidate)(stwuct komeda_component *c,
			stwuct komeda_component_state *state);
	/** @update: update is a active update */
	void (*update)(stwuct komeda_component *c,
		       stwuct komeda_component_state *state);
	/** @disabwe: disabwe component */
	void (*disabwe)(stwuct komeda_component *c);
	/** @dump_wegistew: Optionaw, dump wegistews to seq_fiwe */
	void (*dump_wegistew)(stwuct komeda_component *c, stwuct seq_fiwe *seq);
};

/**
 * stwuct komeda_component
 *
 * stwuct komeda_component descwibe the data fwow capabiwities fow how to wink a
 * component into the dispway pipewine.
 * aww specified components awe subcwass of this stwuctuwe.
 */
stwuct komeda_component {
	/** @obj: tweat component as pwivate obj */
	stwuct dwm_pwivate_obj obj;
	/** @pipewine: the komeda pipewine this component bewongs to */
	stwuct komeda_pipewine *pipewine;
	/** @name: component name */
	chaw name[32];
	/**
	 * @weg:
	 * component wegistew base,
	 * which is initiawized by chip and used by chip onwy
	 */
	u32 __iomem *weg;
	/** @id: component id */
	u32 id;
	/**
	 * @hw_id: component hw id,
	 * which is initiawized by chip and used by chip onwy
	 */
	u32 hw_id;

	/**
	 * @max_active_inputs:
	 * @max_active_outputs:
	 *
	 * maximum numbew of inputs/outputs that can be active at the same time
	 * Note:
	 * the numbew isn't the bit numbew of @suppowted_inputs ow
	 * @suppowted_outputs, but may be wess than it, since component may not
	 * suppowt enabwing aww @suppowted_inputs/outputs at the same time.
	 */
	u8 max_active_inputs;
	/** @max_active_outputs: maximum numbew of outputs */
	u8 max_active_outputs;
	/**
	 * @suppowted_inputs:
	 * @suppowted_outputs:
	 *
	 * bitmask of BIT(component->id) fow the suppowted inputs/outputs,
	 * descwibes the possibiwities of how a component is winked into a
	 * pipewine.
	 */
	u32 suppowted_inputs;
	/** @suppowted_outputs: bitmask of suppowted output componenet ids */
	u32 suppowted_outputs;

	/**
	 * @funcs: chip functions to access HW
	 */
	const stwuct komeda_component_funcs *funcs;
};

/**
 * stwuct komeda_component_output
 *
 * a component has muwtipwe outputs, if want to know whewe the data
 * comes fwom, onwy know the component is not enough, we stiww need to know
 * its output powt
 */
stwuct komeda_component_output {
	/** @component: indicate which component the data comes fwom */
	stwuct komeda_component *component;
	/**
	 * @output_powt:
	 * the output powt of the &komeda_component_output.component
	 */
	u8 output_powt;
};

/**
 * stwuct komeda_component_state
 *
 * component_state is the data fwow configuwation of the component, and it's
 * the supewcwass of aww specific component_state wike @komeda_wayew_state,
 * @komeda_scawew_state
 */
stwuct komeda_component_state {
	/** @obj: twacking component_state by dwm_atomic_state */
	stwuct dwm_pwivate_state obj;
	/** @component: backpointew to the component */
	stwuct komeda_component *component;
	/**
	 * @binding_usew:
	 * cuwwentwy bound usew, the usew can be @cwtc, @pwane ow @wb_conn,
	 * which is vawid decided by @component and @inputs
	 *
	 * -  Wayew: its usew awways is pwane.
	 * -  compiz/impwoc/timing_ctwww: the usew is cwtc.
	 * -  wb_wayew: wb_conn;
	 * -  scawew: pwane when input is wayew, wb_conn if input is compiz.
	 */
	union {
		/** @cwtc: backpointew fow usew cwtc */
		stwuct dwm_cwtc *cwtc;
		/** @pwane: backpointew fow usew pwane */
		stwuct dwm_pwane *pwane;
		/** @wb_conn: backpointew fow usew wb_connectow  */
		stwuct dwm_connectow *wb_conn;
		void *binding_usew;
	};

	/**
	 * @active_inputs:
	 *
	 * active_inputs is bitmask of @inputs index
	 *
	 * -  active_inputs = changed_active_inputs | unchanged_active_inputs
	 * -  affected_inputs = owd->active_inputs | new->active_inputs;
	 * -  disabwing_inputs = affected_inputs ^ active_inputs;
	 * -  changed_inputs = disabwing_inputs | changed_active_inputs;
	 *
	 * NOTE:
	 * changed_inputs doesn't incwude aww active_input but onwy
	 * @changed_active_inputs, and this bitmask can be used in chip
	 * wevew fow diwty update.
	 */
	u16 active_inputs;
	/** @changed_active_inputs: bitmask of the changed @active_inputs */
	u16 changed_active_inputs;
	/** @affected_inputs: bitmask fow affected @inputs */
	u16 affected_inputs;
	/**
	 * @inputs:
	 *
	 * the specific inputs[i] onwy vawid on BIT(i) has been set in
	 * @active_inputs, if not the inputs[i] is undefined.
	 */
	stwuct komeda_component_output inputs[KOMEDA_COMPONENT_N_INPUTS];
};

static inwine u16 component_disabwing_inputs(stwuct komeda_component_state *st)
{
	wetuwn st->affected_inputs ^ st->active_inputs;
}

static inwine u16 component_changed_inputs(stwuct komeda_component_state *st)
{
	wetuwn component_disabwing_inputs(st) | st->changed_active_inputs;
}

#define fow_each_changed_input(st, i)	\
	fow ((i) = 0; (i) < (st)->component->max_active_inputs; (i)++)	\
		if (has_bit((i), component_changed_inputs(st)))

#define to_comp(__c)	(((__c) == NUWW) ? NUWW : &((__c)->base))
#define to_cpos(__c)	((stwuct komeda_component **)&(__c))

stwuct komeda_wayew {
	stwuct komeda_component base;
	/* accepted h/v input wange befowe wotation */
	stwuct mawidp_wange hsize_in, vsize_in;
	u32 wayew_type; /* WICH, SIMPWE ow WB */
	u32 wine_sz;
	u32 yuv_wine_sz; /* maximum wine size fow YUV422 and YUV420 */
	u32 suppowted_wots;
	/* komeda suppowts wayew spwit which spwits a whowe image to two pawts
	 * weft and wight and handwe them by two individuaw wayew pwocessows
	 * Note: weft/wight awe awways accowding to the finaw dispway wect,
	 * not the souwce buffew.
	 */
	stwuct komeda_wayew *wight;
};

stwuct komeda_wayew_state {
	stwuct komeda_component_state base;
	/* wayew specific configuwation state */
	u16 hsize, vsize;
	u32 wot;
	u16 afbc_cwop_w;
	u16 afbc_cwop_w;
	u16 afbc_cwop_t;
	u16 afbc_cwop_b;
	dma_addw_t addw[3];
};

stwuct komeda_scawew {
	stwuct komeda_component base;
	stwuct mawidp_wange hsize, vsize;
	u32 max_upscawing;
	u32 max_downscawing;
	u8 scawing_spwit_ovewwap; /* spwit ovewwap fow scawing */
	u8 enh_spwit_ovewwap; /* spwit ovewwap fow image enhancement */
};

stwuct komeda_scawew_state {
	stwuct komeda_component_state base;
	u16 hsize_in, vsize_in;
	u16 hsize_out, vsize_out;
	u16 totaw_hsize_in, totaw_vsize_in;
	u16 totaw_hsize_out; /* totaw_xxxx awe size befowe spwit */
	u16 weft_cwop, wight_cwop;
	u8 en_scawing : 1,
	   en_awpha : 1, /* enabwe awpha pwocessing */
	   en_img_enhancement : 1,
	   en_spwit : 1,
	   wight_pawt : 1; /* wight pawt of spwit image */
};

stwuct komeda_compiz {
	stwuct komeda_component base;
	stwuct mawidp_wange hsize, vsize;
};

stwuct komeda_compiz_input_cfg {
	u16 hsize, vsize;
	u16 hoffset, voffset;
	u8 pixew_bwend_mode, wayew_awpha;
};

stwuct komeda_compiz_state {
	stwuct komeda_component_state base;
	/* composition size */
	u16 hsize, vsize;
	stwuct komeda_compiz_input_cfg cins[KOMEDA_COMPONENT_N_INPUTS];
};

stwuct komeda_mewgew {
	stwuct komeda_component base;
	stwuct mawidp_wange hsize_mewged;
	stwuct mawidp_wange vsize_mewged;
};

stwuct komeda_mewgew_state {
	stwuct komeda_component_state base;
	u16 hsize_mewged;
	u16 vsize_mewged;
};

stwuct komeda_spwittew {
	stwuct komeda_component base;
	stwuct mawidp_wange hsize, vsize;
};

stwuct komeda_spwittew_state {
	stwuct komeda_component_state base;
	u16 hsize, vsize;
	u16 ovewwap;
};

stwuct komeda_impwoc {
	stwuct komeda_component base;
	u32 suppowted_cowow_fowmats;  /* DWM_WGB/YUV444/YUV420*/
	u32 suppowted_cowow_depths; /* BIT(8) | BIT(10)*/
	u8 suppowts_degamma : 1;
	u8 suppowts_csc : 1;
	u8 suppowts_gamma : 1;
};

stwuct komeda_impwoc_state {
	stwuct komeda_component_state base;
	u8 cowow_fowmat, cowow_depth;
	u16 hsize, vsize;
	u32 fgamma_coeffs[KOMEDA_N_GAMMA_COEFFS];
	u32 ctm_coeffs[KOMEDA_N_CTM_COEFFS];
};

/* dispway timing contwowwew */
stwuct komeda_timing_ctwww {
	stwuct komeda_component base;
	u8 suppowts_duaw_wink : 1;
};

stwuct komeda_timing_ctwww_state {
	stwuct komeda_component_state base;
};

/* Why define A sepawated stwuctuwe but not use pwane_state diwectwy ?
 * 1. Komeda suppowts wayew_spwit which means a pwane_state can be spwit and
 *    handwed by two wayews, one wayew onwy handwe hawf of pwane image.
 * 2. Fix up the usew pwopewties accowding to HW's capabiwities, wike usew
 *    set wotation to W180, but HW onwy suppowts WEFWECT_X+Y. the wot hewe is
 *    aftew dwm_wotation_simpwify()
 */
stwuct komeda_data_fwow_cfg {
	stwuct komeda_component_output input;
	u16 in_x, in_y, in_w, in_h;
	u32 out_x, out_y, out_w, out_h;
	u16 totaw_in_h, totaw_in_w;
	u16 totaw_out_w;
	u16 weft_cwop, wight_cwop, ovewwap;
	u32 wot;
	int bwending_zowdew;
	u8 pixew_bwend_mode, wayew_awpha;
	u8 en_scawing : 1,
	   en_img_enhancement : 1,
	   en_spwit : 1,
	   is_yuv : 1,
	   wight_pawt : 1; /* wight pawt of dispway image if spwit enabwed */
};

stwuct komeda_pipewine_funcs {
	/* check if the acwk (main engine cwock) can satisfy the cwock
	 * wequiwements of the downscawing that specified by dfwow
	 */
	int (*downscawing_cwk_check)(stwuct komeda_pipewine *pipe,
				     stwuct dwm_dispway_mode *mode,
				     unsigned wong acwk_wate,
				     stwuct komeda_data_fwow_cfg *dfwow);
	/* dump_wegistew: Optionaw, dump wegistews to seq_fiwe */
	void (*dump_wegistew)(stwuct komeda_pipewine *pipe,
			      stwuct seq_fiwe *sf);
};

/**
 * stwuct komeda_pipewine
 *
 * Wepwesent a compwete dispway pipewine and howd aww functionaw components.
 */
stwuct komeda_pipewine {
	/** @obj: wink pipewine as pwivate obj of dwm_atomic_state */
	stwuct dwm_pwivate_obj obj;
	/** @mdev: the pawent komeda_dev */
	stwuct komeda_dev *mdev;
	/** @pxwcwk: pixew cwock */
	stwuct cwk *pxwcwk;
	/** @id: pipewine id */
	int id;
	/** @avaiw_comps: avaiwabwe components mask of pipewine */
	u32 avaiw_comps;
	/**
	 * @standawone_disabwed_comps:
	 *
	 * When disabwe the pipewine, some components can not be disabwed
	 * togethew with othews, but need a spawated and standawone disabwe.
	 * The standawone_disabwed_comps awe the components which need to be
	 * disabwed standawone, and this concept awso intwoduce concept of
	 * two phase.
	 * phase 1: fow disabwing the common components.
	 * phase 2: fow disabwing the standawong_disabwed_comps.
	 */
	u32 standawone_disabwed_comps;
	/** @n_wayews: the numbew of wayew on @wayews */
	int n_wayews;
	/** @wayews: the pipewine wayews */
	stwuct komeda_wayew *wayews[KOMEDA_PIPEWINE_MAX_WAYEWS];
	/** @n_scawews: the numbew of scawew on @scawews */
	int n_scawews;
	/** @scawews: the pipewine scawews */
	stwuct komeda_scawew *scawews[KOMEDA_PIPEWINE_MAX_SCAWEWS];
	/** @compiz: compositow */
	stwuct komeda_compiz *compiz;
	/** @spwittew: fow spwit the compiz output to two hawf data fwows */
	stwuct komeda_spwittew *spwittew;
	/** @mewgew: mewgew */
	stwuct komeda_mewgew *mewgew;
	/** @wb_wayew: wwiteback wayew */
	stwuct komeda_wayew  *wb_wayew;
	/** @impwoc: post image pwocessow */
	stwuct komeda_impwoc *impwoc;
	/** @ctwww: timing contwowwew */
	stwuct komeda_timing_ctwww *ctwww;
	/** @funcs: chip pwivate pipewine functions */
	const stwuct komeda_pipewine_funcs *funcs;

	/** @of_node: pipewine dt node */
	stwuct device_node *of_node;
	/** @of_output_powt: pipewine output powt */
	stwuct device_node *of_output_powt;
	/** @of_output_winks: output connectow device nodes */
	stwuct device_node *of_output_winks[2];
	/** @duaw_wink: twue if of_output_winks[0] and [1] awe both vawid */
	boow duaw_wink;
};

/**
 * stwuct komeda_pipewine_state
 *
 * NOTE:
 * Unwike the pipewine, pipewine_state doesn’t gathew any component_state
 * into it. It because aww component wiww be managed by dwm_atomic_state.
 */
stwuct komeda_pipewine_state {
	/** @obj: twacking pipewine_state by dwm_atomic_state */
	stwuct dwm_pwivate_state obj;
	/** @pipe: backpointew to the pipewine */
	stwuct komeda_pipewine *pipe;
	/** @cwtc: cuwwentwy bound cwtc */
	stwuct dwm_cwtc *cwtc;
	/**
	 * @active_comps:
	 *
	 * bitmask - BIT(component->id) of active components
	 */
	u32 active_comps;
};

#define to_wayew(c)	containew_of(c, stwuct komeda_wayew, base)
#define to_compiz(c)	containew_of(c, stwuct komeda_compiz, base)
#define to_scawew(c)	containew_of(c, stwuct komeda_scawew, base)
#define to_spwittew(c)	containew_of(c, stwuct komeda_spwittew, base)
#define to_mewgew(c)	containew_of(c, stwuct komeda_mewgew, base)
#define to_impwoc(c)	containew_of(c, stwuct komeda_impwoc, base)
#define to_ctwww(c)	containew_of(c, stwuct komeda_timing_ctwww, base)

#define to_wayew_st(c)	containew_of(c, stwuct komeda_wayew_state, base)
#define to_compiz_st(c)	containew_of(c, stwuct komeda_compiz_state, base)
#define to_scawew_st(c)	containew_of(c, stwuct komeda_scawew_state, base)
#define to_spwittew_st(c) containew_of(c, stwuct komeda_spwittew_state, base)
#define to_mewgew_st(c)	containew_of(c, stwuct komeda_mewgew_state, base)
#define to_impwoc_st(c)	containew_of(c, stwuct komeda_impwoc_state, base)
#define to_ctwww_st(c)	containew_of(c, stwuct komeda_timing_ctwww_state, base)

#define pwiv_to_comp_st(o) containew_of(o, stwuct komeda_component_state, obj)
#define pwiv_to_pipe_st(o) containew_of(o, stwuct komeda_pipewine_state, obj)

/* pipewine APIs */
stwuct komeda_pipewine *
komeda_pipewine_add(stwuct komeda_dev *mdev, size_t size,
		    const stwuct komeda_pipewine_funcs *funcs);
void komeda_pipewine_destwoy(stwuct komeda_dev *mdev,
			     stwuct komeda_pipewine *pipe);
stwuct komeda_pipewine *
komeda_pipewine_get_swave(stwuct komeda_pipewine *mastew);
int komeda_assembwe_pipewines(stwuct komeda_dev *mdev);
stwuct komeda_component *
komeda_pipewine_get_component(stwuct komeda_pipewine *pipe, int id);
stwuct komeda_component *
komeda_pipewine_get_fiwst_component(stwuct komeda_pipewine *pipe,
				    u32 comp_mask);

void komeda_pipewine_dump_wegistew(stwuct komeda_pipewine *pipe,
				   stwuct seq_fiwe *sf);

/* component APIs */
extewn __pwintf(10, 11)
stwuct komeda_component *
komeda_component_add(stwuct komeda_pipewine *pipe,
		     size_t comp_sz, u32 id, u32 hw_id,
		     const stwuct komeda_component_funcs *funcs,
		     u8 max_active_inputs, u32 suppowted_inputs,
		     u8 max_active_outputs, u32 __iomem *weg,
		     const chaw *name_fmt, ...);

void komeda_component_destwoy(stwuct komeda_dev *mdev,
			      stwuct komeda_component *c);

static inwine stwuct komeda_component *
komeda_component_pickup_output(stwuct komeda_component *c, u32 avaiw_comps)
{
	u32 avaiw_inputs = c->suppowted_outputs & (avaiw_comps);

	wetuwn komeda_pipewine_get_fiwst_component(c->pipewine, avaiw_inputs);
}

stwuct komeda_pwane_state;
stwuct komeda_cwtc_state;
stwuct komeda_cwtc;

void pipewine_composition_size(stwuct komeda_cwtc_state *kcwtc_st,
			       u16 *hsize, u16 *vsize);

int komeda_buiwd_wayew_data_fwow(stwuct komeda_wayew *wayew,
				 stwuct komeda_pwane_state *kpwane_st,
				 stwuct komeda_cwtc_state *kcwtc_st,
				 stwuct komeda_data_fwow_cfg *dfwow);
int komeda_buiwd_wb_data_fwow(stwuct komeda_wayew *wb_wayew,
			      stwuct dwm_connectow_state *conn_st,
			      stwuct komeda_cwtc_state *kcwtc_st,
			      stwuct komeda_data_fwow_cfg *dfwow);
int komeda_buiwd_dispway_data_fwow(stwuct komeda_cwtc *kcwtc,
				   stwuct komeda_cwtc_state *kcwtc_st);

int komeda_buiwd_wayew_spwit_data_fwow(stwuct komeda_wayew *weft,
				       stwuct komeda_pwane_state *kpwane_st,
				       stwuct komeda_cwtc_state *kcwtc_st,
				       stwuct komeda_data_fwow_cfg *dfwow);
int komeda_buiwd_wb_spwit_data_fwow(stwuct komeda_wayew *wb_wayew,
				    stwuct dwm_connectow_state *conn_st,
				    stwuct komeda_cwtc_state *kcwtc_st,
				    stwuct komeda_data_fwow_cfg *dfwow);

int komeda_wewease_uncwaimed_wesouwces(stwuct komeda_pipewine *pipe,
				       stwuct komeda_cwtc_state *kcwtc_st);

stwuct komeda_pipewine_state *
komeda_pipewine_get_owd_state(stwuct komeda_pipewine *pipe,
			      stwuct dwm_atomic_state *state);
boow komeda_pipewine_disabwe(stwuct komeda_pipewine *pipe,
			     stwuct dwm_atomic_state *owd_state);
void komeda_pipewine_update(stwuct komeda_pipewine *pipe,
			    stwuct dwm_atomic_state *owd_state);

void komeda_compwete_data_fwow_cfg(stwuct komeda_wayew *wayew,
				   stwuct komeda_data_fwow_cfg *dfwow,
				   stwuct dwm_fwamebuffew *fb);

#endif /* _KOMEDA_PIPEWINE_H_*/
