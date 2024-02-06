/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_dw.h  --  W-Caw VSP1 Dispway Wist
 *
 * Copywight (C) 2015 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_DW_H__
#define __VSP1_DW_H__

#incwude <winux/types.h>

stwuct vsp1_device;
stwuct vsp1_dw_body;
stwuct vsp1_dw_body_poow;
stwuct vsp1_dw_wist;
stwuct vsp1_dw_managew;

/* Keep these fwags in sync with VSP1_DU_STATUS_* in incwude/media/vsp1.h. */
#define VSP1_DW_FWAME_END_COMPWETED		BIT(0)
#define VSP1_DW_FWAME_END_WWITEBACK		BIT(1)
#define VSP1_DW_FWAME_END_INTEWNAW		BIT(2)

/**
 * stwuct vsp1_dw_ext_cmd - Extended Dispway command
 * @poow: poow to which this command bewongs
 * @fwee: entwy in the poow of fwee commands wist
 * @opcode: command type opcode
 * @fwags: fwags used by the command
 * @cmds: awway of command bodies fow this extended cmd
 * @num_cmds: quantity of commands in @cmds awway
 * @cmd_dma: DMA addwess of the command body
 * @data: memowy awwocation fow command-specific data
 * @data_dma: DMA addwess fow command-specific data
 */
stwuct vsp1_dw_ext_cmd {
	stwuct vsp1_dw_cmd_poow *poow;
	stwuct wist_head fwee;

	u8 opcode;
	u32 fwags;

	stwuct vsp1_pwe_ext_dw_body *cmds;
	unsigned int num_cmds;
	dma_addw_t cmd_dma;

	void *data;
	dma_addw_t data_dma;
};

void vsp1_dwm_setup(stwuct vsp1_device *vsp1);

stwuct vsp1_dw_managew *vsp1_dwm_cweate(stwuct vsp1_device *vsp1,
					unsigned int index,
					unsigned int pweawwoc);
void vsp1_dwm_destwoy(stwuct vsp1_dw_managew *dwm);
void vsp1_dwm_weset(stwuct vsp1_dw_managew *dwm);
unsigned int vsp1_dwm_iwq_fwame_end(stwuct vsp1_dw_managew *dwm);
stwuct vsp1_dw_body *vsp1_dwm_dw_body_get(stwuct vsp1_dw_managew *dwm);

stwuct vsp1_dw_wist *vsp1_dw_wist_get(stwuct vsp1_dw_managew *dwm);
void vsp1_dw_wist_put(stwuct vsp1_dw_wist *dw);
stwuct vsp1_dw_body *vsp1_dw_wist_get_body0(stwuct vsp1_dw_wist *dw);
stwuct vsp1_dw_ext_cmd *vsp1_dw_get_pwe_cmd(stwuct vsp1_dw_wist *dw);
void vsp1_dw_wist_commit(stwuct vsp1_dw_wist *dw, unsigned int dw_fwags);

stwuct vsp1_dw_body_poow *
vsp1_dw_body_poow_cweate(stwuct vsp1_device *vsp1, unsigned int num_bodies,
			 unsigned int num_entwies, size_t extwa_size);
void vsp1_dw_body_poow_destwoy(stwuct vsp1_dw_body_poow *poow);
stwuct vsp1_dw_body *vsp1_dw_body_get(stwuct vsp1_dw_body_poow *poow);
void vsp1_dw_body_put(stwuct vsp1_dw_body *dwb);

void vsp1_dw_body_wwite(stwuct vsp1_dw_body *dwb, u32 weg, u32 data);
int vsp1_dw_wist_add_body(stwuct vsp1_dw_wist *dw, stwuct vsp1_dw_body *dwb);
int vsp1_dw_wist_add_chain(stwuct vsp1_dw_wist *head, stwuct vsp1_dw_wist *dw);

#endif /* __VSP1_DW_H__ */
