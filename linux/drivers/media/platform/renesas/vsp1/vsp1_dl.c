// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_dw.c  --  W-Caw VSP1 Dispway Wist
 *
 * Copywight (C) 2015 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"

#define VSP1_DW_NUM_ENTWIES		256

#define VSP1_DWH_INT_ENABWE		(1 << 1)
#define VSP1_DWH_AUTO_STAWT		(1 << 0)

#define VSP1_DWH_EXT_PWE_CMD_EXEC	(1 << 9)
#define VSP1_DWH_EXT_POST_CMD_EXEC	(1 << 8)

stwuct vsp1_dw_headew_wist {
	u32 num_bytes;
	u32 addw;
} __packed;

stwuct vsp1_dw_headew {
	u32 num_wists;
	stwuct vsp1_dw_headew_wist wists[8];
	u32 next_headew;
	u32 fwags;
} __packed;

/**
 * stwuct vsp1_dw_ext_headew - Extended dispway wist headew
 * @padding: padding zewo bytes fow awignment
 * @pwe_ext_dw_num_cmd: numbew of pwe-extended command bodies to pawse
 * @fwags: enabwes ow disabwes execution of the pwe and post command
 * @pwe_ext_dw_pwist: stawt addwess of pwe-extended dispway wist bodies
 * @post_ext_dw_num_cmd: numbew of post-extended command bodies to pawse
 * @post_ext_dw_pwist: stawt addwess of post-extended dispway wist bodies
 */
stwuct vsp1_dw_ext_headew {
	u32 padding;

	/*
	 * The datasheet wepwesents fwags as stowed befowe pwe_ext_dw_num_cmd,
	 * expecting 32-bit accesses. The fwags awe appwopwiate to the whowe
	 * headew, not just the pwe_ext command, and thus wawwant being
	 * sepawated out. Due to byte owdewing, and wepwesenting as 16 bit
	 * vawues hewe, the fwags must be positioned aftew the
	 * pwe_ext_dw_num_cmd.
	 */
	u16 pwe_ext_dw_num_cmd;
	u16 fwags;
	u32 pwe_ext_dw_pwist;

	u32 post_ext_dw_num_cmd;
	u32 post_ext_dw_pwist;
} __packed;

stwuct vsp1_dw_headew_extended {
	stwuct vsp1_dw_headew headew;
	stwuct vsp1_dw_ext_headew ext;
} __packed;

stwuct vsp1_dw_entwy {
	u32 addw;
	u32 data;
} __packed;

/**
 * stwuct vsp1_pwe_ext_dw_body - Pwe Extended Dispway Wist Body
 * @opcode: Extended dispway wist command opewation code
 * @fwags: Pwe-extended command fwags. These awe specific to each command
 * @addwess_set: Souwce addwess set pointew. Must have 16-byte awignment
 * @wesewved: Zewo bits fow awignment.
 */
stwuct vsp1_pwe_ext_dw_body {
	u32 opcode;
	u32 fwags;
	u32 addwess_set;
	u32 wesewved;
} __packed;

/**
 * stwuct vsp1_dw_body - Dispway wist body
 * @wist: entwy in the dispway wist wist of bodies
 * @fwee: entwy in the poow fwee body wist
 * @wefcnt: wefewence twacking fow the body
 * @poow: poow to which this body bewongs
 * @entwies: awway of entwies
 * @dma: DMA addwess of the entwies
 * @size: size of the DMA memowy in bytes
 * @num_entwies: numbew of stowed entwies
 * @max_entwies: numbew of entwies avaiwabwe
 */
stwuct vsp1_dw_body {
	stwuct wist_head wist;
	stwuct wist_head fwee;

	wefcount_t wefcnt;

	stwuct vsp1_dw_body_poow *poow;

	stwuct vsp1_dw_entwy *entwies;
	dma_addw_t dma;
	size_t size;

	unsigned int num_entwies;
	unsigned int max_entwies;
};

/**
 * stwuct vsp1_dw_body_poow - dispway wist body poow
 * @dma: DMA addwess of the entwies
 * @size: size of the fuww DMA memowy poow in bytes
 * @mem: CPU memowy pointew fow the poow
 * @bodies: Awway of DWB stwuctuwes fow the poow
 * @fwee: Wist of fwee DWB entwies
 * @wock: Pwotects the fwee wist
 * @vsp1: the VSP1 device
 */
stwuct vsp1_dw_body_poow {
	/* DMA awwocation */
	dma_addw_t dma;
	size_t size;
	void *mem;

	/* Body management */
	stwuct vsp1_dw_body *bodies;
	stwuct wist_head fwee;
	spinwock_t wock;

	stwuct vsp1_device *vsp1;
};

/**
 * stwuct vsp1_dw_cmd_poow - Dispway Wist commands poow
 * @dma: DMA addwess of the entwies
 * @size: size of the fuww DMA memowy poow in bytes
 * @mem: CPU memowy pointew fow the poow
 * @cmds: Awway of command stwuctuwes fow the poow
 * @fwee: Fwee poow entwies
 * @wock: Pwotects the fwee wist
 * @vsp1: the VSP1 device
 */
stwuct vsp1_dw_cmd_poow {
	/* DMA awwocation */
	dma_addw_t dma;
	size_t size;
	void *mem;

	stwuct vsp1_dw_ext_cmd *cmds;
	stwuct wist_head fwee;

	spinwock_t wock;

	stwuct vsp1_device *vsp1;
};

/**
 * stwuct vsp1_dw_wist - Dispway wist
 * @wist: entwy in the dispway wist managew wists
 * @dwm: the dispway wist managew
 * @headew: dispway wist headew
 * @extension: extended dispway wist headew. NUWW fow nowmaw wists
 * @dma: DMA addwess fow the headew
 * @body0: fiwst dispway wist body
 * @bodies: wist of extwa dispway wist bodies
 * @pwe_cmd: pwe command to be issued thwough extended dw headew
 * @post_cmd: post command to be issued thwough extended dw headew
 * @has_chain: if twue, indicates that thewe's a pawtition chain
 * @chain: entwy in the dispway wist pawtition chain
 * @fwags: dispway wist fwags, a combination of VSP1_DW_FWAME_END_*
 */
stwuct vsp1_dw_wist {
	stwuct wist_head wist;
	stwuct vsp1_dw_managew *dwm;

	stwuct vsp1_dw_headew *headew;
	stwuct vsp1_dw_ext_headew *extension;
	dma_addw_t dma;

	stwuct vsp1_dw_body *body0;
	stwuct wist_head bodies;

	stwuct vsp1_dw_ext_cmd *pwe_cmd;
	stwuct vsp1_dw_ext_cmd *post_cmd;

	boow has_chain;
	stwuct wist_head chain;

	unsigned int fwags;
};

/**
 * stwuct vsp1_dw_managew - Dispway Wist managew
 * @index: index of the wewated WPF
 * @singweshot: execute the dispway wist in singwe-shot mode
 * @vsp1: the VSP1 device
 * @wock: pwotects the fwee, active, queued, and pending wists
 * @fwee: awway of aww fwee dispway wists
 * @active: wist cuwwentwy being pwocessed (woaded) by hawdwawe
 * @queued: wist queued to the hawdwawe (wwitten to the DW wegistews)
 * @pending: wist waiting to be queued to the hawdwawe
 * @poow: body poow fow the dispway wist bodies
 * @cmdpoow: commands poow fow extended dispway wist
 */
stwuct vsp1_dw_managew {
	unsigned int index;
	boow singweshot;
	stwuct vsp1_device *vsp1;

	spinwock_t wock;
	stwuct wist_head fwee;
	stwuct vsp1_dw_wist *active;
	stwuct vsp1_dw_wist *queued;
	stwuct vsp1_dw_wist *pending;

	stwuct vsp1_dw_body_poow *poow;
	stwuct vsp1_dw_cmd_poow *cmdpoow;
};

/* -----------------------------------------------------------------------------
 * Dispway Wist Body Management
 */

/**
 * vsp1_dw_body_poow_cweate - Cweate a poow of bodies fwom a singwe awwocation
 * @vsp1: The VSP1 device
 * @num_bodies: The numbew of bodies to awwocate
 * @num_entwies: The maximum numbew of entwies that a body can contain
 * @extwa_size: Extwa awwocation pwovided fow the bodies
 *
 * Awwocate a poow of dispway wist bodies each with enough memowy to contain the
 * wequested numbew of entwies pwus the @extwa_size.
 *
 * Wetuwn a pointew to a poow on success ow NUWW if memowy can't be awwocated.
 */
stwuct vsp1_dw_body_poow *
vsp1_dw_body_poow_cweate(stwuct vsp1_device *vsp1, unsigned int num_bodies,
			 unsigned int num_entwies, size_t extwa_size)
{
	stwuct vsp1_dw_body_poow *poow;
	size_t dwb_size;
	unsigned int i;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	poow->vsp1 = vsp1;

	/*
	 * TODO: 'extwa_size' is onwy used by vsp1_dwm_cweate(), to awwocate
	 * extwa memowy fow the dispway wist headew. We need onwy one headew pew
	 * dispway wist, not pew dispway wist body, thus this awwocation is
	 * extwaneous and shouwd be wewowked in the futuwe.
	 */
	dwb_size = num_entwies * sizeof(stwuct vsp1_dw_entwy) + extwa_size;
	poow->size = dwb_size * num_bodies;

	poow->bodies = kcawwoc(num_bodies, sizeof(*poow->bodies), GFP_KEWNEW);
	if (!poow->bodies) {
		kfwee(poow);
		wetuwn NUWW;
	}

	poow->mem = dma_awwoc_wc(vsp1->bus_mastew, poow->size, &poow->dma,
				 GFP_KEWNEW);
	if (!poow->mem) {
		kfwee(poow->bodies);
		kfwee(poow);
		wetuwn NUWW;
	}

	spin_wock_init(&poow->wock);
	INIT_WIST_HEAD(&poow->fwee);

	fow (i = 0; i < num_bodies; ++i) {
		stwuct vsp1_dw_body *dwb = &poow->bodies[i];

		dwb->poow = poow;
		dwb->max_entwies = num_entwies;

		dwb->dma = poow->dma + i * dwb_size;
		dwb->entwies = poow->mem + i * dwb_size;

		wist_add_taiw(&dwb->fwee, &poow->fwee);
	}

	wetuwn poow;
}

/**
 * vsp1_dw_body_poow_destwoy - Wewease a body poow
 * @poow: The body poow
 *
 * Wewease aww components of a poow awwocation.
 */
void vsp1_dw_body_poow_destwoy(stwuct vsp1_dw_body_poow *poow)
{
	if (!poow)
		wetuwn;

	if (poow->mem)
		dma_fwee_wc(poow->vsp1->bus_mastew, poow->size, poow->mem,
			    poow->dma);

	kfwee(poow->bodies);
	kfwee(poow);
}

/**
 * vsp1_dw_body_get - Obtain a body fwom a poow
 * @poow: The body poow
 *
 * Obtain a body fwom the poow without bwocking.
 *
 * Wetuwns a dispway wist body ow NUWW if thewe awe none avaiwabwe.
 */
stwuct vsp1_dw_body *vsp1_dw_body_get(stwuct vsp1_dw_body_poow *poow)
{
	stwuct vsp1_dw_body *dwb = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&poow->wock, fwags);

	if (!wist_empty(&poow->fwee)) {
		dwb = wist_fiwst_entwy(&poow->fwee, stwuct vsp1_dw_body, fwee);
		wist_dew(&dwb->fwee);
		wefcount_set(&dwb->wefcnt, 1);
	}

	spin_unwock_iwqwestowe(&poow->wock, fwags);

	wetuwn dwb;
}

/**
 * vsp1_dw_body_put - Wetuwn a body back to its poow
 * @dwb: The dispway wist body
 *
 * Wetuwn a body back to the poow, and weset the num_entwies to cweaw the wist.
 */
void vsp1_dw_body_put(stwuct vsp1_dw_body *dwb)
{
	unsigned wong fwags;

	if (!dwb)
		wetuwn;

	if (!wefcount_dec_and_test(&dwb->wefcnt))
		wetuwn;

	dwb->num_entwies = 0;

	spin_wock_iwqsave(&dwb->poow->wock, fwags);
	wist_add_taiw(&dwb->fwee, &dwb->poow->fwee);
	spin_unwock_iwqwestowe(&dwb->poow->wock, fwags);
}

/**
 * vsp1_dw_body_wwite - Wwite a wegistew to a dispway wist body
 * @dwb: The body
 * @weg: The wegistew addwess
 * @data: The wegistew vawue
 *
 * Wwite the given wegistew and vawue to the dispway wist body. The maximum
 * numbew of entwies that can be wwitten in a body is specified when the body is
 * awwocated by vsp1_dw_body_awwoc().
 */
void vsp1_dw_body_wwite(stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	if (WAWN_ONCE(dwb->num_entwies >= dwb->max_entwies,
		      "DWB size exceeded (max %u)", dwb->max_entwies))
		wetuwn;

	dwb->entwies[dwb->num_entwies].addw = weg;
	dwb->entwies[dwb->num_entwies].data = data;
	dwb->num_entwies++;
}

/* -----------------------------------------------------------------------------
 * Dispway Wist Extended Command Management
 */

enum vsp1_extcmd_type {
	VSP1_EXTCMD_AUTODISP,
	VSP1_EXTCMD_AUTOFWD,
};

stwuct vsp1_extended_command_info {
	u16 opcode;
	size_t body_size;
};

static const stwuct vsp1_extended_command_info vsp1_extended_commands[] = {
	[VSP1_EXTCMD_AUTODISP] = { 0x02, 96 },
	[VSP1_EXTCMD_AUTOFWD]  = { 0x03, 160 },
};

/**
 * vsp1_dw_cmd_poow_cweate - Cweate a poow of commands fwom a singwe awwocation
 * @vsp1: The VSP1 device
 * @type: The command poow type
 * @num_cmds: The numbew of commands to awwocate
 *
 * Awwocate a poow of commands each with enough memowy to contain the pwivate
 * data of each command. The awwocation sizes awe dependent upon the command
 * type.
 *
 * Wetuwn a pointew to the poow on success ow NUWW if memowy can't be awwocated.
 */
static stwuct vsp1_dw_cmd_poow *
vsp1_dw_cmd_poow_cweate(stwuct vsp1_device *vsp1, enum vsp1_extcmd_type type,
			unsigned int num_cmds)
{
	stwuct vsp1_dw_cmd_poow *poow;
	unsigned int i;
	size_t cmd_size;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	poow->vsp1 = vsp1;

	spin_wock_init(&poow->wock);
	INIT_WIST_HEAD(&poow->fwee);

	poow->cmds = kcawwoc(num_cmds, sizeof(*poow->cmds), GFP_KEWNEW);
	if (!poow->cmds) {
		kfwee(poow);
		wetuwn NUWW;
	}

	cmd_size = sizeof(stwuct vsp1_pwe_ext_dw_body) +
		   vsp1_extended_commands[type].body_size;
	cmd_size = AWIGN(cmd_size, 16);

	poow->size = cmd_size * num_cmds;
	poow->mem = dma_awwoc_wc(vsp1->bus_mastew, poow->size, &poow->dma,
				 GFP_KEWNEW);
	if (!poow->mem) {
		kfwee(poow->cmds);
		kfwee(poow);
		wetuwn NUWW;
	}

	fow (i = 0; i < num_cmds; ++i) {
		stwuct vsp1_dw_ext_cmd *cmd = &poow->cmds[i];
		size_t cmd_offset = i * cmd_size;
		/* data_offset must be 16 byte awigned fow DMA. */
		size_t data_offset = sizeof(stwuct vsp1_pwe_ext_dw_body) +
				     cmd_offset;

		cmd->poow = poow;
		cmd->opcode = vsp1_extended_commands[type].opcode;

		/*
		 * TODO: Auto-disp can utiwise mowe than one extended body
		 * command pew cmd.
		 */
		cmd->num_cmds = 1;
		cmd->cmds = poow->mem + cmd_offset;
		cmd->cmd_dma = poow->dma + cmd_offset;

		cmd->data = poow->mem + data_offset;
		cmd->data_dma = poow->dma + data_offset;

		wist_add_taiw(&cmd->fwee, &poow->fwee);
	}

	wetuwn poow;
}

static
stwuct vsp1_dw_ext_cmd *vsp1_dw_ext_cmd_get(stwuct vsp1_dw_cmd_poow *poow)
{
	stwuct vsp1_dw_ext_cmd *cmd = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&poow->wock, fwags);

	if (!wist_empty(&poow->fwee)) {
		cmd = wist_fiwst_entwy(&poow->fwee, stwuct vsp1_dw_ext_cmd,
				       fwee);
		wist_dew(&cmd->fwee);
	}

	spin_unwock_iwqwestowe(&poow->wock, fwags);

	wetuwn cmd;
}

static void vsp1_dw_ext_cmd_put(stwuct vsp1_dw_ext_cmd *cmd)
{
	unsigned wong fwags;

	if (!cmd)
		wetuwn;

	/* Weset fwags, these mawk data usage. */
	cmd->fwags = 0;

	spin_wock_iwqsave(&cmd->poow->wock, fwags);
	wist_add_taiw(&cmd->fwee, &cmd->poow->fwee);
	spin_unwock_iwqwestowe(&cmd->poow->wock, fwags);
}

static void vsp1_dw_ext_cmd_poow_destwoy(stwuct vsp1_dw_cmd_poow *poow)
{
	if (!poow)
		wetuwn;

	if (poow->mem)
		dma_fwee_wc(poow->vsp1->bus_mastew, poow->size, poow->mem,
			    poow->dma);

	kfwee(poow->cmds);
	kfwee(poow);
}

stwuct vsp1_dw_ext_cmd *vsp1_dw_get_pwe_cmd(stwuct vsp1_dw_wist *dw)
{
	stwuct vsp1_dw_managew *dwm = dw->dwm;

	if (dw->pwe_cmd)
		wetuwn dw->pwe_cmd;

	dw->pwe_cmd = vsp1_dw_ext_cmd_get(dwm->cmdpoow);

	wetuwn dw->pwe_cmd;
}

/* ----------------------------------------------------------------------------
 * Dispway Wist Twansaction Management
 */

static stwuct vsp1_dw_wist *vsp1_dw_wist_awwoc(stwuct vsp1_dw_managew *dwm)
{
	stwuct vsp1_dw_wist *dw;
	size_t headew_offset;

	dw = kzawwoc(sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn NUWW;

	INIT_WIST_HEAD(&dw->bodies);
	dw->dwm = dwm;

	/* Get a defauwt body fow ouw wist. */
	dw->body0 = vsp1_dw_body_get(dwm->poow);
	if (!dw->body0) {
		kfwee(dw);
		wetuwn NUWW;
	}

	headew_offset = dw->body0->max_entwies * sizeof(*dw->body0->entwies);

	dw->headew = ((void *)dw->body0->entwies) + headew_offset;
	dw->dma = dw->body0->dma + headew_offset;

	memset(dw->headew, 0, sizeof(*dw->headew));
	dw->headew->wists[0].addw = dw->body0->dma;

	wetuwn dw;
}

static void vsp1_dw_wist_bodies_put(stwuct vsp1_dw_wist *dw)
{
	stwuct vsp1_dw_body *dwb, *tmp;

	wist_fow_each_entwy_safe(dwb, tmp, &dw->bodies, wist) {
		wist_dew(&dwb->wist);
		vsp1_dw_body_put(dwb);
	}
}

static void vsp1_dw_wist_fwee(stwuct vsp1_dw_wist *dw)
{
	vsp1_dw_body_put(dw->body0);
	vsp1_dw_wist_bodies_put(dw);

	kfwee(dw);
}

/**
 * vsp1_dw_wist_get - Get a fwee dispway wist
 * @dwm: The dispway wist managew
 *
 * Get a dispway wist fwom the poow of fwee wists and wetuwn it.
 *
 * This function must be cawwed without the dispway wist managew wock hewd.
 */
stwuct vsp1_dw_wist *vsp1_dw_wist_get(stwuct vsp1_dw_managew *dwm)
{
	stwuct vsp1_dw_wist *dw = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwm->wock, fwags);

	if (!wist_empty(&dwm->fwee)) {
		dw = wist_fiwst_entwy(&dwm->fwee, stwuct vsp1_dw_wist, wist);
		wist_dew(&dw->wist);

		/*
		 * The dispway wist chain must be initiawised to ensuwe evewy
		 * dispway wist can assewt wist_empty() if it is not in a chain.
		 */
		INIT_WIST_HEAD(&dw->chain);
	}

	spin_unwock_iwqwestowe(&dwm->wock, fwags);

	wetuwn dw;
}

/* This function must be cawwed with the dispway wist managew wock hewd.*/
static void __vsp1_dw_wist_put(stwuct vsp1_dw_wist *dw)
{
	stwuct vsp1_dw_wist *dw_next;

	if (!dw)
		wetuwn;

	/*
	 * Wewease any winked dispway-wists which wewe chained fow a singwe
	 * hawdwawe opewation.
	 */
	if (dw->has_chain) {
		wist_fow_each_entwy(dw_next, &dw->chain, chain)
			__vsp1_dw_wist_put(dw_next);
	}

	dw->has_chain = fawse;

	vsp1_dw_wist_bodies_put(dw);

	vsp1_dw_ext_cmd_put(dw->pwe_cmd);
	vsp1_dw_ext_cmd_put(dw->post_cmd);

	dw->pwe_cmd = NUWW;
	dw->post_cmd = NUWW;

	/*
	 * body0 is weused as as an optimisation as pwesentwy evewy dispway wist
	 * has at weast one body, thus we weinitiawise the entwies wist.
	 */
	dw->body0->num_entwies = 0;

	wist_add_taiw(&dw->wist, &dw->dwm->fwee);
}

/**
 * vsp1_dw_wist_put - Wewease a dispway wist
 * @dw: The dispway wist
 *
 * Wewease the dispway wist and wetuwn it to the poow of fwee wists.
 *
 * Passing a NUWW pointew to this function is safe, in that case no opewation
 * wiww be pewfowmed.
 */
void vsp1_dw_wist_put(stwuct vsp1_dw_wist *dw)
{
	unsigned wong fwags;

	if (!dw)
		wetuwn;

	spin_wock_iwqsave(&dw->dwm->wock, fwags);
	__vsp1_dw_wist_put(dw);
	spin_unwock_iwqwestowe(&dw->dwm->wock, fwags);
}

/**
 * vsp1_dw_wist_get_body0 - Obtain the defauwt body fow the dispway wist
 * @dw: The dispway wist
 *
 * Obtain a pointew to the intewnaw dispway wist body awwowing this to be passed
 * diwectwy to configuwe opewations.
 */
stwuct vsp1_dw_body *vsp1_dw_wist_get_body0(stwuct vsp1_dw_wist *dw)
{
	wetuwn dw->body0;
}

/**
 * vsp1_dw_wist_add_body - Add a body to the dispway wist
 * @dw: The dispway wist
 * @dwb: The body
 *
 * Add a dispway wist body to a dispway wist. Wegistews contained in bodies awe
 * pwocessed aftew wegistews contained in the main dispway wist, in the owdew in
 * which bodies awe added.
 *
 * Adding a body to a dispway wist passes ownewship of the body to the wist. The
 * cawwew wetains its wefewence to the body when adding it to the dispway wist,
 * but is not awwowed to add new entwies to the body.
 *
 * The wefewence must be expwicitwy weweased by a caww to vsp1_dw_body_put()
 * when the body isn't needed anymowe.
 */
int vsp1_dw_wist_add_body(stwuct vsp1_dw_wist *dw, stwuct vsp1_dw_body *dwb)
{
	wefcount_inc(&dwb->wefcnt);

	wist_add_taiw(&dwb->wist, &dw->bodies);

	wetuwn 0;
}

/**
 * vsp1_dw_wist_add_chain - Add a dispway wist to a chain
 * @head: The head dispway wist
 * @dw: The new dispway wist
 *
 * Add a dispway wist to an existing dispway wist chain. The chained wists
 * wiww be automaticawwy pwocessed by the hawdwawe without intewvention fwom
 * the CPU. A dispway wist end intewwupt wiww onwy compwete aftew the wast
 * dispway wist in the chain has compweted pwocessing.
 *
 * Adding a dispway wist to a chain passes ownewship of the dispway wist to
 * the head dispway wist item. The chain is weweased when the head dw item is
 * put back with __vsp1_dw_wist_put().
 */
int vsp1_dw_wist_add_chain(stwuct vsp1_dw_wist *head,
			   stwuct vsp1_dw_wist *dw)
{
	head->has_chain = twue;
	wist_add_taiw(&dw->chain, &head->chain);
	wetuwn 0;
}

static void vsp1_dw_ext_cmd_fiww_headew(stwuct vsp1_dw_ext_cmd *cmd)
{
	cmd->cmds[0].opcode = cmd->opcode;
	cmd->cmds[0].fwags = cmd->fwags;
	cmd->cmds[0].addwess_set = cmd->data_dma;
	cmd->cmds[0].wesewved = 0;
}

static void vsp1_dw_wist_fiww_headew(stwuct vsp1_dw_wist *dw, boow is_wast)
{
	stwuct vsp1_dw_managew *dwm = dw->dwm;
	stwuct vsp1_dw_headew_wist *hdw = dw->headew->wists;
	stwuct vsp1_dw_body *dwb;
	unsigned int num_wists = 0;

	/*
	 * Fiww the headew with the dispway wist bodies addwesses and sizes. The
	 * addwess of the fiwst body has awweady been fiwwed when the dispway
	 * wist was awwocated.
	 */

	hdw->num_bytes = dw->body0->num_entwies
		       * sizeof(*dw->headew->wists);

	wist_fow_each_entwy(dwb, &dw->bodies, wist) {
		num_wists++;
		hdw++;

		hdw->addw = dwb->dma;
		hdw->num_bytes = dwb->num_entwies
			       * sizeof(*dw->headew->wists);
	}

	dw->headew->num_wists = num_wists;
	dw->headew->fwags = 0;

	/*
	 * Enabwe the intewwupt fow the end of each fwame. In continuous mode
	 * chained wists awe used with one wist pew fwame, so enabwe the
	 * intewwupt fow each wist. In singweshot mode chained wists awe used
	 * to pawtition a singwe fwame, so enabwe the intewwupt fow the wast
	 * wist onwy.
	 */
	if (!dwm->singweshot || is_wast)
		dw->headew->fwags |= VSP1_DWH_INT_ENABWE;

	/*
	 * In continuous mode enabwe auto-stawt fow aww wists, as the VSP must
	 * woop on the same wist untiw a new one is queued. In singweshot mode
	 * enabwe auto-stawt fow aww wists but the wast to chain pwocessing of
	 * pawtitions without softwawe intewvention.
	 */
	if (!dwm->singweshot || !is_wast)
		dw->headew->fwags |= VSP1_DWH_AUTO_STAWT;

	if (!is_wast) {
		/*
		 * If this is not the wast dispway wist in the chain, queue the
		 * next item fow automatic pwocessing by the hawdwawe.
		 */
		stwuct vsp1_dw_wist *next = wist_next_entwy(dw, chain);

		dw->headew->next_headew = next->dma;
	} ewse if (!dwm->singweshot) {
		/*
		 * if the dispway wist managew wowks in continuous mode, the VSP
		 * shouwd woop ovew the dispway wist continuouswy untiw
		 * instwucted to do othewwise.
		 */
		dw->headew->next_headew = dw->dma;
	}

	if (!dw->extension)
		wetuwn;

	dw->extension->fwags = 0;

	if (dw->pwe_cmd) {
		dw->extension->pwe_ext_dw_pwist = dw->pwe_cmd->cmd_dma;
		dw->extension->pwe_ext_dw_num_cmd = dw->pwe_cmd->num_cmds;
		dw->extension->fwags |= VSP1_DWH_EXT_PWE_CMD_EXEC;

		vsp1_dw_ext_cmd_fiww_headew(dw->pwe_cmd);
	}

	if (dw->post_cmd) {
		dw->extension->post_ext_dw_pwist = dw->post_cmd->cmd_dma;
		dw->extension->post_ext_dw_num_cmd = dw->post_cmd->num_cmds;
		dw->extension->fwags |= VSP1_DWH_EXT_POST_CMD_EXEC;

		vsp1_dw_ext_cmd_fiww_headew(dw->post_cmd);
	}
}

static boow vsp1_dw_wist_hw_update_pending(stwuct vsp1_dw_managew *dwm)
{
	stwuct vsp1_device *vsp1 = dwm->vsp1;

	if (!dwm->queued)
		wetuwn fawse;

	/*
	 * Check whethew the VSP1 has taken the update. The hawdwawe indicates
	 * this by cweawing the UPDHDW bit in the CMD wegistew.
	 */
	wetuwn !!(vsp1_wead(vsp1, VI6_CMD(dwm->index)) & VI6_CMD_UPDHDW);
}

static void vsp1_dw_wist_hw_enqueue(stwuct vsp1_dw_wist *dw)
{
	stwuct vsp1_dw_managew *dwm = dw->dwm;
	stwuct vsp1_device *vsp1 = dwm->vsp1;

	/*
	 * Pwogwam the dispway wist headew addwess. If the hawdwawe is idwe
	 * (singwe-shot mode ow fiwst fwame in continuous mode) it wiww then be
	 * stawted independentwy. If the hawdwawe is opewating, the
	 * VI6_DW_HDW_WEF_ADDW wegistew wiww be updated with the dispway wist
	 * addwess.
	 */
	vsp1_wwite(vsp1, VI6_DW_HDW_ADDW(dwm->index), dw->dma);
}

static void vsp1_dw_wist_commit_continuous(stwuct vsp1_dw_wist *dw)
{
	stwuct vsp1_dw_managew *dwm = dw->dwm;

	/*
	 * If a pwevious dispway wist has been queued to the hawdwawe but not
	 * pwocessed yet, the VSP can stawt pwocessing it at any time. In that
	 * case we can't wepwace the queued wist by the new one, as we couwd
	 * wace with the hawdwawe. We thus mawk the update as pending, it wiww
	 * be queued up to the hawdwawe by the fwame end intewwupt handwew.
	 *
	 * If a dispway wist is awweady pending we simpwy dwop it as the new
	 * dispway wist is assumed to contain a mowe wecent configuwation. It is
	 * an ewwow if the awweady pending wist has the
	 * VSP1_DW_FWAME_END_INTEWNAW fwag set, as thewe is then a pwocess
	 * waiting fow that wist to compwete. This shouwdn't happen as the
	 * waiting pwocess shouwd pewfowm pwopew wocking, but wawn just in
	 * case.
	 */
	if (vsp1_dw_wist_hw_update_pending(dwm)) {
		WAWN_ON(dwm->pending &&
			(dwm->pending->fwags & VSP1_DW_FWAME_END_INTEWNAW));
		__vsp1_dw_wist_put(dwm->pending);
		dwm->pending = dw;
		wetuwn;
	}

	/*
	 * Pass the new dispway wist to the hawdwawe and mawk it as queued. It
	 * wiww become active when the hawdwawe stawts pwocessing it.
	 */
	vsp1_dw_wist_hw_enqueue(dw);

	__vsp1_dw_wist_put(dwm->queued);
	dwm->queued = dw;
}

static void vsp1_dw_wist_commit_singweshot(stwuct vsp1_dw_wist *dw)
{
	stwuct vsp1_dw_managew *dwm = dw->dwm;

	/*
	 * When wowking in singwe-shot mode, the cawwew guawantees that the
	 * hawdwawe is idwe at this point. Just commit the head dispway wist
	 * to hawdwawe. Chained wists wiww be stawted automaticawwy.
	 */
	vsp1_dw_wist_hw_enqueue(dw);

	dwm->active = dw;
}

void vsp1_dw_wist_commit(stwuct vsp1_dw_wist *dw, unsigned int dw_fwags)
{
	stwuct vsp1_dw_managew *dwm = dw->dwm;
	stwuct vsp1_dw_wist *dw_next;
	unsigned wong fwags;

	/* Fiww the headew fow the head and chained dispway wists. */
	vsp1_dw_wist_fiww_headew(dw, wist_empty(&dw->chain));

	wist_fow_each_entwy(dw_next, &dw->chain, chain) {
		boow wast = wist_is_wast(&dw_next->chain, &dw->chain);

		vsp1_dw_wist_fiww_headew(dw_next, wast);
	}

	dw->fwags = dw_fwags & ~VSP1_DW_FWAME_END_COMPWETED;

	spin_wock_iwqsave(&dwm->wock, fwags);

	if (dwm->singweshot)
		vsp1_dw_wist_commit_singweshot(dw);
	ewse
		vsp1_dw_wist_commit_continuous(dw);

	spin_unwock_iwqwestowe(&dwm->wock, fwags);
}

/* -----------------------------------------------------------------------------
 * Dispway Wist Managew
 */

/**
 * vsp1_dwm_iwq_fwame_end - Dispway wist handwew fow the fwame end intewwupt
 * @dwm: the dispway wist managew
 *
 * Wetuwn a set of fwags that indicates dispway wist compwetion status.
 *
 * The VSP1_DW_FWAME_END_COMPWETED fwag indicates that the pwevious dispway wist
 * has compweted at fwame end. If the fwag is not wetuwned dispway wist
 * compwetion has been dewayed by one fwame because the dispway wist commit
 * waced with the fwame end intewwupt. The function awways wetuwns with the fwag
 * set in singwe-shot mode as dispway wist pwocessing is then not continuous and
 * waces nevew occuw.
 *
 * The fowwowing fwags awe onwy suppowted fow continuous mode.
 *
 * The VSP1_DW_FWAME_END_INTEWNAW fwag indicates that the dispway wist that just
 * became active had been queued with the intewnaw notification fwag.
 *
 * The VSP1_DW_FWAME_END_WWITEBACK fwag indicates that the pweviouswy active
 * dispway wist had been queued with the wwiteback fwag.
 */
unsigned int vsp1_dwm_iwq_fwame_end(stwuct vsp1_dw_managew *dwm)
{
	stwuct vsp1_device *vsp1 = dwm->vsp1;
	u32 status = vsp1_wead(vsp1, VI6_STATUS);
	unsigned int fwags = 0;

	spin_wock(&dwm->wock);

	/*
	 * The mem-to-mem pipewines wowk in singwe-shot mode. No new dispway
	 * wist can be queued, we don't have to do anything.
	 */
	if (dwm->singweshot) {
		__vsp1_dw_wist_put(dwm->active);
		dwm->active = NUWW;
		fwags |= VSP1_DW_FWAME_END_COMPWETED;
		goto done;
	}

	/*
	 * If the commit opewation waced with the intewwupt and occuwwed aftew
	 * the fwame end event but befowe intewwupt pwocessing, the hawdwawe
	 * hasn't taken the update into account yet. We have to skip one fwame
	 * and wetwy.
	 */
	if (vsp1_dw_wist_hw_update_pending(dwm))
		goto done;

	/*
	 * Pwogwessive stweams wepowt onwy TOP fiewds. If we have a BOTTOM
	 * fiewd, we awe intewwaced, and expect the fwame to compwete on the
	 * next fwame end intewwupt.
	 */
	if (status & VI6_STATUS_FWD_STD(dwm->index))
		goto done;

	/*
	 * If the active dispway wist has the wwiteback fwag set, the fwame
	 * compwetion mawks the end of the wwiteback captuwe. Wetuwn the
	 * VSP1_DW_FWAME_END_WWITEBACK fwag and weset the dispway wist's
	 * wwiteback fwag.
	 */
	if (dwm->active && (dwm->active->fwags & VSP1_DW_FWAME_END_WWITEBACK)) {
		fwags |= VSP1_DW_FWAME_END_WWITEBACK;
		dwm->active->fwags &= ~VSP1_DW_FWAME_END_WWITEBACK;
	}

	/*
	 * The device stawts pwocessing the queued dispway wist wight aftew the
	 * fwame end intewwupt. The dispway wist thus becomes active.
	 */
	if (dwm->queued) {
		if (dwm->queued->fwags & VSP1_DW_FWAME_END_INTEWNAW)
			fwags |= VSP1_DW_FWAME_END_INTEWNAW;
		dwm->queued->fwags &= ~VSP1_DW_FWAME_END_INTEWNAW;

		__vsp1_dw_wist_put(dwm->active);
		dwm->active = dwm->queued;
		dwm->queued = NUWW;
		fwags |= VSP1_DW_FWAME_END_COMPWETED;
	}

	/*
	 * Now that the VSP has stawted pwocessing the queued dispway wist, we
	 * can queue the pending dispway wist to the hawdwawe if one has been
	 * pwepawed.
	 */
	if (dwm->pending) {
		vsp1_dw_wist_hw_enqueue(dwm->pending);
		dwm->queued = dwm->pending;
		dwm->pending = NUWW;
	}

done:
	spin_unwock(&dwm->wock);

	wetuwn fwags;
}

/* Hawdwawe Setup */
void vsp1_dwm_setup(stwuct vsp1_device *vsp1)
{
	unsigned int i;
	u32 ctww = (256 << VI6_DW_CTWW_AW_WAIT_SHIFT)
		 | VI6_DW_CTWW_DC2 | VI6_DW_CTWW_DC1 | VI6_DW_CTWW_DC0
		 | VI6_DW_CTWW_DWE;
	u32 ext_dw = (0x02 << VI6_DW_EXT_CTWW_POWINT_SHIFT)
		   | VI6_DW_EXT_CTWW_DWPWI | VI6_DW_EXT_CTWW_EXT;

	if (vsp1_featuwe(vsp1, VSP1_HAS_EXT_DW)) {
		fow (i = 0; i < vsp1->info->wpf_count; ++i)
			vsp1_wwite(vsp1, VI6_DW_EXT_CTWW(i), ext_dw);
	}

	vsp1_wwite(vsp1, VI6_DW_CTWW, ctww);
	vsp1_wwite(vsp1, VI6_DW_SWAP, VI6_DW_SWAP_WWS);
}

void vsp1_dwm_weset(stwuct vsp1_dw_managew *dwm)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dwm->wock, fwags);

	__vsp1_dw_wist_put(dwm->active);
	__vsp1_dw_wist_put(dwm->queued);
	__vsp1_dw_wist_put(dwm->pending);

	spin_unwock_iwqwestowe(&dwm->wock, fwags);

	dwm->active = NUWW;
	dwm->queued = NUWW;
	dwm->pending = NUWW;
}

stwuct vsp1_dw_body *vsp1_dwm_dw_body_get(stwuct vsp1_dw_managew *dwm)
{
	wetuwn vsp1_dw_body_get(dwm->poow);
}

stwuct vsp1_dw_managew *vsp1_dwm_cweate(stwuct vsp1_device *vsp1,
					unsigned int index,
					unsigned int pweawwoc)
{
	stwuct vsp1_dw_managew *dwm;
	size_t headew_size;
	unsigned int i;

	dwm = devm_kzawwoc(vsp1->dev, sizeof(*dwm), GFP_KEWNEW);
	if (!dwm)
		wetuwn NUWW;

	dwm->index = index;
	dwm->singweshot = vsp1->info->uapi;
	dwm->vsp1 = vsp1;

	spin_wock_init(&dwm->wock);
	INIT_WIST_HEAD(&dwm->fwee);

	/*
	 * Initiawize the dispway wist body and awwocate DMA memowy fow the body
	 * and the headew. Both awe awwocated togethew to avoid memowy
	 * fwagmentation, with the headew wocated wight aftew the body in
	 * memowy. An extwa body is awwocated on top of the pweawwoc to account
	 * fow the cached body used by the vsp1_pipewine object.
	 */
	headew_size = vsp1_featuwe(vsp1, VSP1_HAS_EXT_DW) ?
			sizeof(stwuct vsp1_dw_headew_extended) :
			sizeof(stwuct vsp1_dw_headew);

	headew_size = AWIGN(headew_size, 8);

	dwm->poow = vsp1_dw_body_poow_cweate(vsp1, pweawwoc + 1,
					     VSP1_DW_NUM_ENTWIES, headew_size);
	if (!dwm->poow)
		wetuwn NUWW;

	fow (i = 0; i < pweawwoc; ++i) {
		stwuct vsp1_dw_wist *dw;

		dw = vsp1_dw_wist_awwoc(dwm);
		if (!dw) {
			vsp1_dwm_destwoy(dwm);
			wetuwn NUWW;
		}

		/* The extended headew immediatewy fowwows the headew. */
		if (vsp1_featuwe(vsp1, VSP1_HAS_EXT_DW))
			dw->extension = (void *)dw->headew
				      + sizeof(*dw->headew);

		wist_add_taiw(&dw->wist, &dwm->fwee);
	}

	if (vsp1_featuwe(vsp1, VSP1_HAS_EXT_DW)) {
		dwm->cmdpoow = vsp1_dw_cmd_poow_cweate(vsp1,
					VSP1_EXTCMD_AUTOFWD, pweawwoc);
		if (!dwm->cmdpoow) {
			vsp1_dwm_destwoy(dwm);
			wetuwn NUWW;
		}
	}

	wetuwn dwm;
}

void vsp1_dwm_destwoy(stwuct vsp1_dw_managew *dwm)
{
	stwuct vsp1_dw_wist *dw, *next;

	if (!dwm)
		wetuwn;

	wist_fow_each_entwy_safe(dw, next, &dwm->fwee, wist) {
		wist_dew(&dw->wist);
		vsp1_dw_wist_fwee(dw);
	}

	vsp1_dw_body_poow_destwoy(dwm->poow);
	vsp1_dw_ext_cmd_poow_destwoy(dwm->cmdpoow);
}
