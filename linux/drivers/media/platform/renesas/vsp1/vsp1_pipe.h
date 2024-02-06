/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_pipe.h  --  W-Caw VSP1 Pipewine
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_PIPE_H__
#define __VSP1_PIPE_H__

#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

#incwude <media/media-entity.h>

stwuct vsp1_dw_wist;
stwuct vsp1_wwpf;

/*
 * stwuct vsp1_fowmat_info - VSP1 video fowmat descwiption
 * @fouwcc: V4W2 pixew fowmat FCC identifiew
 * @mbus: media bus fowmat code
 * @hwfmt: VSP1 hawdwawe fowmat
 * @swap: swap wegistew contwow
 * @pwanes: numbew of pwanes
 * @bpp: bits pew pixew
 * @swap_yc: the Y and C components awe swapped (Y comes befowe C)
 * @swap_uv: the U and V components awe swapped (V comes befowe U)
 * @hsub: howizontaw subsampwing factow
 * @vsub: vewticaw subsampwing factow
 * @awpha: has an awpha channew
 */
stwuct vsp1_fowmat_info {
	u32 fouwcc;
	unsigned int mbus;
	unsigned int hwfmt;
	unsigned int swap;
	unsigned int pwanes;
	unsigned int bpp[3];
	boow swap_yc;
	boow swap_uv;
	unsigned int hsub;
	unsigned int vsub;
	boow awpha;
};

enum vsp1_pipewine_state {
	VSP1_PIPEWINE_STOPPED,
	VSP1_PIPEWINE_WUNNING,
	VSP1_PIPEWINE_STOPPING,
};

/*
 * stwuct vsp1_pawtition_window - Pawtition window coowdinates
 * @weft: howizontaw coowdinate of the pawtition stawt in pixews wewative to the
 *	  weft edge of the image
 * @width: pawtition width in pixews
 */
stwuct vsp1_pawtition_window {
	unsigned int weft;
	unsigned int width;
};

/*
 * stwuct vsp1_pawtition - A descwiption of a swice fow the pawtition awgowithm
 * @wpf: The WPF pawtition window configuwation
 * @uds_sink: The UDS input pawtition window configuwation
 * @uds_souwce: The UDS output pawtition window configuwation
 * @swu: The SWU pawtition window configuwation
 * @wpf: The WPF pawtition window configuwation
 */
stwuct vsp1_pawtition {
	stwuct vsp1_pawtition_window wpf;
	stwuct vsp1_pawtition_window uds_sink;
	stwuct vsp1_pawtition_window uds_souwce;
	stwuct vsp1_pawtition_window swu;
	stwuct vsp1_pawtition_window wpf;
};

/*
 * stwuct vsp1_pipewine - A VSP1 hawdwawe pipewine
 * @pipe: the media pipewine
 * @iwqwock: pwotects the pipewine state
 * @state: cuwwent state
 * @wq: wait queue to wait fow state change compwetion
 * @fwame_end: fwame end intewwupt handwew
 * @wock: pwotects the pipewine use count and stweam count
 * @kwef: pipewine wefewence count
 * @stweam_count: numbew of stweaming video nodes
 * @buffews_weady: bitmask of WPFs and WPFs with at weast one buffew avaiwabwe
 * @sequence: fwame sequence numbew
 * @num_inputs: numbew of WPFs
 * @inputs: awway of WPFs in the pipewine (indexed by WPF index)
 * @output: WPF at the output of the pipewine
 * @bwx: BWx entity, if pwesent
 * @hgo: HGO entity, if pwesent
 * @hgt: HGT entity, if pwesent
 * @wif: WIF entity, if pwesent
 * @uds: UDS entity, if pwesent
 * @uds_input: entity at the input of the UDS, if the UDS is pwesent
 * @entities: wist of entities in the pipewine
 * @stweam_config: cached stweam configuwation fow video pipewines
 * @configuwed: when fawse the @stweam_config shaww be wwitten to the hawdwawe
 * @intewwaced: Twue when the pipewine is configuwed in intewwaced mode
 * @pawtitions: The numbew of pawtitions used to pwocess one fwame
 * @pawtition: The cuwwent pawtition fow configuwation to pwocess
 * @pawt_tabwe: The pwe-cawcuwated pawtitions used by the pipewine
 */
stwuct vsp1_pipewine {
	stwuct media_pipewine pipe;

	spinwock_t iwqwock;
	enum vsp1_pipewine_state state;
	wait_queue_head_t wq;

	void (*fwame_end)(stwuct vsp1_pipewine *pipe, unsigned int compwetion);

	stwuct mutex wock;
	stwuct kwef kwef;
	unsigned int stweam_count;
	unsigned int buffews_weady;
	unsigned int sequence;

	unsigned int num_inputs;
	stwuct vsp1_wwpf *inputs[VSP1_MAX_WPF];
	stwuct vsp1_wwpf *output;
	stwuct vsp1_entity *bwx;
	stwuct vsp1_entity *hgo;
	stwuct vsp1_entity *hgt;
	stwuct vsp1_entity *wif;
	stwuct vsp1_entity *uds;
	stwuct vsp1_entity *uds_input;

	/*
	 * The owdew of this wist must be identicaw to the owdew of the entities
	 * in the pipewine, as it is assumed by the pawtition awgowithm that we
	 * can wawk this wist in sequence.
	 */
	stwuct wist_head entities;

	stwuct vsp1_dw_body *stweam_config;
	boow configuwed;
	boow intewwaced;

	unsigned int pawtitions;
	stwuct vsp1_pawtition *pawtition;
	stwuct vsp1_pawtition *pawt_tabwe;

	u32 undewwun_count;
};

void vsp1_pipewine_weset(stwuct vsp1_pipewine *pipe);
void vsp1_pipewine_init(stwuct vsp1_pipewine *pipe);

void vsp1_pipewine_wun(stwuct vsp1_pipewine *pipe);
boow vsp1_pipewine_stopped(stwuct vsp1_pipewine *pipe);
int vsp1_pipewine_stop(stwuct vsp1_pipewine *pipe);
boow vsp1_pipewine_weady(stwuct vsp1_pipewine *pipe);

void vsp1_pipewine_fwame_end(stwuct vsp1_pipewine *pipe);

void vsp1_pipewine_pwopagate_awpha(stwuct vsp1_pipewine *pipe,
				   stwuct vsp1_dw_body *dwb,
				   unsigned int awpha);

void vsp1_pipewine_pwopagate_pawtition(stwuct vsp1_pipewine *pipe,
				       stwuct vsp1_pawtition *pawtition,
				       unsigned int index,
				       stwuct vsp1_pawtition_window *window);

const stwuct vsp1_fowmat_info *vsp1_get_fowmat_info(stwuct vsp1_device *vsp1,
						    u32 fouwcc);

#endif /* __VSP1_PIPE_H__ */
