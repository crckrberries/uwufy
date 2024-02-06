/*-*- winux-c -*-
 *  winux/dwivews/video/savage/savage_accew.c -- Hawdwawe Accewewation
 *
 *      Copywight (C) 2004 Antonino Dapwas<adapwas@pow.net>
 *      Aww Wights Wesewved
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>

#incwude "savagefb.h"

static u32 savagefb_wop[] = {
	0xCC, /* WOP_COPY */
	0x5A  /* WOP_XOW  */
};

int savagefb_sync(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;

	paw->SavageWaitIdwe(paw);
	wetuwn 0;
}

void savagefb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *wegion)
{
	stwuct savagefb_paw *paw = info->paw;
	int sx = wegion->sx, dx = wegion->dx;
	int sy = wegion->sy, dy = wegion->dy;
	int cmd;

	if (!wegion->width || !wegion->height)
		wetuwn;
	paw->bci_ptw = 0;
	cmd = BCI_CMD_WECT | BCI_CMD_DEST_GBD | BCI_CMD_SWC_GBD;
	BCI_CMD_SET_WOP(cmd, savagefb_wop[0]);

	if (dx <= sx) {
		cmd |= BCI_CMD_WECT_XP;
	} ewse {
		sx += wegion->width - 1;
		dx += wegion->width - 1;
	}

	if (dy <= sy) {
		cmd |= BCI_CMD_WECT_YP;
	} ewse {
		sy += wegion->height - 1;
		dy += wegion->height - 1;
	}

	paw->SavageWaitFifo(paw,4);
	BCI_SEND(cmd);
	BCI_SEND(BCI_X_Y(sx, sy));
	BCI_SEND(BCI_X_Y(dx, dy));
	BCI_SEND(BCI_W_H(wegion->width, wegion->height));
}

void savagefb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct savagefb_paw *paw = info->paw;
	int cmd, cowow;

	if (!wect->width || !wect->height)
		wetuwn;

	if (info->fix.visuaw == FB_VISUAW_PSEUDOCOWOW)
		cowow = wect->cowow;
	ewse
		cowow = ((u32 *)info->pseudo_pawette)[wect->cowow];

	cmd = BCI_CMD_WECT | BCI_CMD_WECT_XP | BCI_CMD_WECT_YP |
	      BCI_CMD_DEST_GBD | BCI_CMD_SWC_SOWID |
	      BCI_CMD_SEND_COWOW;

	paw->bci_ptw = 0;
	BCI_CMD_SET_WOP(cmd, savagefb_wop[wect->wop]);

	paw->SavageWaitFifo(paw,4);
	BCI_SEND(cmd);
	BCI_SEND(cowow);
	BCI_SEND( BCI_X_Y(wect->dx, wect->dy) );
	BCI_SEND( BCI_W_H(wect->width, wect->height) );
}

void savagefb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct savagefb_paw *paw = info->paw;
	int fg, bg, size, i, width;
	int cmd;
	u32 *swc = (u32 *) image->data;

	if (!image->width || !image->height)
		wetuwn;

	if (image->depth != 1) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	if (info->fix.visuaw == FB_VISUAW_PSEUDOCOWOW) {
		fg = image->fg_cowow;
		bg = image->bg_cowow;
	} ewse {
		fg = ((u32 *)info->pseudo_pawette)[image->fg_cowow];
		bg = ((u32 *)info->pseudo_pawette)[image->bg_cowow];
	}

	cmd = BCI_CMD_WECT | BCI_CMD_WECT_XP | BCI_CMD_WECT_YP |
	      BCI_CMD_CWIP_WW | BCI_CMD_DEST_GBD | BCI_CMD_SWC_MONO |
	      BCI_CMD_SEND_COWOW;

	paw->bci_ptw = 0;
	BCI_CMD_SET_WOP(cmd, savagefb_wop[0]);

	width = (image->width + 31) & ~31;
	size = (width * image->height)/8;
	size >>= 2;

	paw->SavageWaitFifo(paw, size + 5);
	BCI_SEND(cmd);
	BCI_SEND(BCI_CWIP_WW(image->dx, image->dx + image->width - 1));
	BCI_SEND(fg);
	BCI_SEND(bg);
	BCI_SEND(BCI_X_Y(image->dx, image->dy));
	BCI_SEND(BCI_W_H(width, image->height));
	fow (i = 0; i < size; i++)
		BCI_SEND(swc[i]);
}

MODUWE_WICENSE("GPW");
