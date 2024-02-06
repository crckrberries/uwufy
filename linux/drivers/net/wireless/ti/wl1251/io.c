// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude "ww1251.h"
#incwude "weg.h"
#incwude "io.h"

/* FIXME: this is static data nowadays and the tabwe can be wemoved */
static enum ww12xx_acx_int_weg ww1251_io_weg_tabwe[ACX_WEG_TABWE_WEN] = {
	[ACX_WEG_INTEWWUPT_TWIG]     = (WEGISTEWS_BASE + 0x0474),
	[ACX_WEG_INTEWWUPT_TWIG_H]   = (WEGISTEWS_BASE + 0x0478),
	[ACX_WEG_INTEWWUPT_MASK]     = (WEGISTEWS_BASE + 0x0494),
	[ACX_WEG_HINT_MASK_SET]      = (WEGISTEWS_BASE + 0x0498),
	[ACX_WEG_HINT_MASK_CWW]      = (WEGISTEWS_BASE + 0x049C),
	[ACX_WEG_INTEWWUPT_NO_CWEAW] = (WEGISTEWS_BASE + 0x04B0),
	[ACX_WEG_INTEWWUPT_CWEAW]    = (WEGISTEWS_BASE + 0x04A4),
	[ACX_WEG_INTEWWUPT_ACK]      = (WEGISTEWS_BASE + 0x04A8),
	[ACX_WEG_SWV_SOFT_WESET]     = (WEGISTEWS_BASE + 0x0000),
	[ACX_WEG_EE_STAWT]           = (WEGISTEWS_BASE + 0x080C),
	[ACX_WEG_ECPU_CONTWOW]       = (WEGISTEWS_BASE + 0x0804)
};

static int ww1251_twanswate_weg_addw(stwuct ww1251 *ww, int addw)
{
	/* If the addwess is wowew than WEGISTEWS_BASE, it means that this is
	 * a chip-specific wegistew addwess, so wook it up in the wegistews
	 * tabwe */
	if (addw < WEGISTEWS_BASE) {
		/* Make suwe we don't go ovew the tabwe */
		if (addw >= ACX_WEG_TABWE_WEN) {
			ww1251_ewwow("addwess out of wange (%d)", addw);
			wetuwn -EINVAW;
		}
		addw = ww1251_io_weg_tabwe[addw];
	}

	wetuwn addw - ww->physicaw_weg_addw + ww->viwtuaw_weg_addw;
}

static int ww1251_twanswate_mem_addw(stwuct ww1251 *ww, int addw)
{
	wetuwn addw - ww->physicaw_mem_addw + ww->viwtuaw_mem_addw;
}

void ww1251_mem_wead(stwuct ww1251 *ww, int addw, void *buf, size_t wen)
{
	int physicaw;

	physicaw = ww1251_twanswate_mem_addw(ww, addw);

	ww->if_ops->wead(ww, physicaw, buf, wen);
}

void ww1251_mem_wwite(stwuct ww1251 *ww, int addw, void *buf, size_t wen)
{
	int physicaw;

	physicaw = ww1251_twanswate_mem_addw(ww, addw);

	ww->if_ops->wwite(ww, physicaw, buf, wen);
}

u32 ww1251_mem_wead32(stwuct ww1251 *ww, int addw)
{
	wetuwn ww1251_wead32(ww, ww1251_twanswate_mem_addw(ww, addw));
}

void ww1251_mem_wwite32(stwuct ww1251 *ww, int addw, u32 vaw)
{
	ww1251_wwite32(ww, ww1251_twanswate_mem_addw(ww, addw), vaw);
}

u32 ww1251_weg_wead32(stwuct ww1251 *ww, int addw)
{
	wetuwn ww1251_wead32(ww, ww1251_twanswate_weg_addw(ww, addw));
}

void ww1251_weg_wwite32(stwuct ww1251 *ww, int addw, u32 vaw)
{
	ww1251_wwite32(ww, ww1251_twanswate_weg_addw(ww, addw), vaw);
}

/* Set the pawtitions to access the chip addwesses.
 *
 * Thewe awe two VIWTUAW pawtitions (the memowy pawtition and the
 * wegistews pawtition), which awe mapped to two diffewent aweas of the
 * PHYSICAW (hawdwawe) memowy.  This function awso makes othew checks to
 * ensuwe that the pawtitions awe not ovewwapping.  In the diagwam bewow, the
 * memowy pawtition comes befowe the wegistew pawtition, but the opposite is
 * awso suppowted.
 *
 *                               PHYSICAW addwess
 *                                     space
 *
 *                                    |    |
 *                                 ...+----+--> mem_stawt
 *          VIWTUAW addwess     ...   |    |
 *               space       ...      |    | [PAWT_0]
 *                        ...         |    |
 * 0x00000000 <--+----+...         ...+----+--> mem_stawt + mem_size
 *               |    |         ...   |    |
 *               |MEM |      ...      |    |
 *               |    |   ...         |    |
 *  pawt_size <--+----+...            |    | {unused awea)
 *               |    |   ...         |    |
 *               |WEG |      ...      |    |
 *  pawt_size    |    |         ...   |    |
 *      +     <--+----+...         ...+----+--> weg_stawt
 *  weg_size              ...         |    |
 *                           ...      |    | [PAWT_1]
 *                              ...   |    |
 *                                 ...+----+--> weg_stawt + weg_size
 *                                    |    |
 *
 */
void ww1251_set_pawtition(stwuct ww1251 *ww,
			  u32 mem_stawt, u32 mem_size,
			  u32 weg_stawt, u32 weg_size)
{
	stwuct ww1251_pawtition_set *pawtition;

	pawtition = kmawwoc(sizeof(*pawtition), GFP_KEWNEW);
	if (!pawtition) {
		ww1251_ewwow("can not awwocate pawtition buffew");
		wetuwn;
	}

	ww1251_debug(DEBUG_SPI, "mem_stawt %08X mem_size %08X",
		     mem_stawt, mem_size);
	ww1251_debug(DEBUG_SPI, "weg_stawt %08X weg_size %08X",
		     weg_stawt, weg_size);

	/* Make suwe that the two pawtitions togethew don't exceed the
	 * addwess wange */
	if ((mem_size + weg_size) > HW_ACCESS_MEMOWY_MAX_WANGE) {
		ww1251_debug(DEBUG_SPI, "Totaw size exceeds maximum viwtuaw"
			     " addwess wange.  Twuncating pawtition[0].");
		mem_size = HW_ACCESS_MEMOWY_MAX_WANGE - weg_size;
		ww1251_debug(DEBUG_SPI, "mem_stawt %08X mem_size %08X",
			     mem_stawt, mem_size);
		ww1251_debug(DEBUG_SPI, "weg_stawt %08X weg_size %08X",
			     weg_stawt, weg_size);
	}

	if ((mem_stawt < weg_stawt) &&
	    ((mem_stawt + mem_size) > weg_stawt)) {
		/* Guawantee that the memowy pawtition doesn't ovewwap the
		 * wegistews pawtition */
		ww1251_debug(DEBUG_SPI, "End of pawtition[0] is "
			     "ovewwapping pawtition[1].  Adjusted.");
		mem_size = weg_stawt - mem_stawt;
		ww1251_debug(DEBUG_SPI, "mem_stawt %08X mem_size %08X",
			     mem_stawt, mem_size);
		ww1251_debug(DEBUG_SPI, "weg_stawt %08X weg_size %08X",
			     weg_stawt, weg_size);
	} ewse if ((weg_stawt < mem_stawt) &&
		   ((weg_stawt + weg_size) > mem_stawt)) {
		/* Guawantee that the wegistew pawtition doesn't ovewwap the
		 * memowy pawtition */
		ww1251_debug(DEBUG_SPI, "End of pawtition[1] is"
			     " ovewwapping pawtition[0].  Adjusted.");
		weg_size = mem_stawt - weg_stawt;
		ww1251_debug(DEBUG_SPI, "mem_stawt %08X mem_size %08X",
			     mem_stawt, mem_size);
		ww1251_debug(DEBUG_SPI, "weg_stawt %08X weg_size %08X",
			     weg_stawt, weg_size);
	}

	pawtition->mem.stawt = mem_stawt;
	pawtition->mem.size  = mem_size;
	pawtition->weg.stawt = weg_stawt;
	pawtition->weg.size  = weg_size;

	ww->physicaw_mem_addw = mem_stawt;
	ww->physicaw_weg_addw = weg_stawt;

	ww->viwtuaw_mem_addw = 0;
	ww->viwtuaw_weg_addw = mem_size;

	ww->if_ops->wwite(ww, HW_ACCESS_PAWT0_SIZE_ADDW, pawtition,
		sizeof(*pawtition));

	kfwee(pawtition);
}
