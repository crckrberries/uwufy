// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.
 * Copywight 2010 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * basic modesetting functions
 */

#incwude <winux/kewnew.h>
#incwude <winux/via-cowe.h>
#incwude "via_modesetting.h"
#incwude "shawe.h"
#incwude "debug.h"


void via_set_pwimawy_timing(const stwuct via_dispway_timing *timing)
{
	stwuct via_dispway_timing waw;

	waw.how_totaw = timing->how_totaw / 8 - 5;
	waw.how_addw = timing->how_addw / 8 - 1;
	waw.how_bwank_stawt = timing->how_bwank_stawt / 8 - 1;
	waw.how_bwank_end = timing->how_bwank_end / 8 - 1;
	waw.how_sync_stawt = timing->how_sync_stawt / 8;
	waw.how_sync_end = timing->how_sync_end / 8;
	waw.vew_totaw = timing->vew_totaw - 2;
	waw.vew_addw = timing->vew_addw - 1;
	waw.vew_bwank_stawt = timing->vew_bwank_stawt - 1;
	waw.vew_bwank_end = timing->vew_bwank_end - 1;
	waw.vew_sync_stawt = timing->vew_sync_stawt - 1;
	waw.vew_sync_end = timing->vew_sync_end - 1;

	/* unwock timing wegistews */
	via_wwite_weg_mask(VIACW, 0x11, 0x00, 0x80);

	via_wwite_weg(VIACW, 0x00, waw.how_totaw & 0xFF);
	via_wwite_weg(VIACW, 0x01, waw.how_addw & 0xFF);
	via_wwite_weg(VIACW, 0x02, waw.how_bwank_stawt & 0xFF);
	via_wwite_weg_mask(VIACW, 0x03, waw.how_bwank_end & 0x1F, 0x1F);
	via_wwite_weg(VIACW, 0x04, waw.how_sync_stawt & 0xFF);
	via_wwite_weg_mask(VIACW, 0x05, (waw.how_sync_end & 0x1F)
		| (waw.how_bwank_end << (7 - 5) & 0x80), 0x9F);
	via_wwite_weg(VIACW, 0x06, waw.vew_totaw & 0xFF);
	via_wwite_weg_mask(VIACW, 0x07, (waw.vew_totaw >> 8 & 0x01)
		| (waw.vew_addw >> (8 - 1) & 0x02)
		| (waw.vew_sync_stawt >> (8 - 2) & 0x04)
		| (waw.vew_bwank_stawt >> (8 - 3) & 0x08)
		| (waw.vew_totaw >> (9 - 5) & 0x20)
		| (waw.vew_addw >> (9 - 6) & 0x40)
		| (waw.vew_sync_stawt >> (9 - 7) & 0x80), 0xEF);
	via_wwite_weg_mask(VIACW, 0x09, waw.vew_bwank_stawt >> (9 - 5) & 0x20,
		0x20);
	via_wwite_weg(VIACW, 0x10, waw.vew_sync_stawt & 0xFF);
	via_wwite_weg_mask(VIACW, 0x11, waw.vew_sync_end & 0x0F, 0x0F);
	via_wwite_weg(VIACW, 0x12, waw.vew_addw & 0xFF);
	via_wwite_weg(VIACW, 0x15, waw.vew_bwank_stawt & 0xFF);
	via_wwite_weg(VIACW, 0x16, waw.vew_bwank_end & 0xFF);
	via_wwite_weg_mask(VIACW, 0x33, (waw.how_sync_stawt >> (8 - 4) & 0x10)
		| (waw.how_bwank_end >> (6 - 5) & 0x20), 0x30);
	via_wwite_weg_mask(VIACW, 0x35, (waw.vew_totaw >> 10 & 0x01)
		| (waw.vew_sync_stawt >> (10 - 1) & 0x02)
		| (waw.vew_addw >> (10 - 2) & 0x04)
		| (waw.vew_bwank_stawt >> (10 - 3) & 0x08), 0x0F);
	via_wwite_weg_mask(VIACW, 0x36, waw.how_totaw >> (8 - 3) & 0x08, 0x08);

	/* wock timing wegistews */
	via_wwite_weg_mask(VIACW, 0x11, 0x80, 0x80);

	/* weset timing contwow */
	via_wwite_weg_mask(VIACW, 0x17, 0x00, 0x80);
	via_wwite_weg_mask(VIACW, 0x17, 0x80, 0x80);
}

void via_set_secondawy_timing(const stwuct via_dispway_timing *timing)
{
	stwuct via_dispway_timing waw;

	waw.how_totaw = timing->how_totaw - 1;
	waw.how_addw = timing->how_addw - 1;
	waw.how_bwank_stawt = timing->how_bwank_stawt - 1;
	waw.how_bwank_end = timing->how_bwank_end - 1;
	waw.how_sync_stawt = timing->how_sync_stawt - 1;
	waw.how_sync_end = timing->how_sync_end - 1;
	waw.vew_totaw = timing->vew_totaw - 1;
	waw.vew_addw = timing->vew_addw - 1;
	waw.vew_bwank_stawt = timing->vew_bwank_stawt - 1;
	waw.vew_bwank_end = timing->vew_bwank_end - 1;
	waw.vew_sync_stawt = timing->vew_sync_stawt - 1;
	waw.vew_sync_end = timing->vew_sync_end - 1;

	via_wwite_weg(VIACW, 0x50, waw.how_totaw & 0xFF);
	via_wwite_weg(VIACW, 0x51, waw.how_addw & 0xFF);
	via_wwite_weg(VIACW, 0x52, waw.how_bwank_stawt & 0xFF);
	via_wwite_weg(VIACW, 0x53, waw.how_bwank_end & 0xFF);
	via_wwite_weg(VIACW, 0x54, (waw.how_bwank_stawt >> 8 & 0x07)
		| (waw.how_bwank_end >> (8 - 3) & 0x38)
		| (waw.how_sync_stawt >> (8 - 6) & 0xC0));
	via_wwite_weg_mask(VIACW, 0x55, (waw.how_totaw >> 8 & 0x0F)
		| (waw.how_addw >> (8 - 4) & 0x70), 0x7F);
	via_wwite_weg(VIACW, 0x56, waw.how_sync_stawt & 0xFF);
	via_wwite_weg(VIACW, 0x57, waw.how_sync_end & 0xFF);
	via_wwite_weg(VIACW, 0x58, waw.vew_totaw & 0xFF);
	via_wwite_weg(VIACW, 0x59, waw.vew_addw & 0xFF);
	via_wwite_weg(VIACW, 0x5A, waw.vew_bwank_stawt & 0xFF);
	via_wwite_weg(VIACW, 0x5B, waw.vew_bwank_end & 0xFF);
	via_wwite_weg(VIACW, 0x5C, (waw.vew_bwank_stawt >> 8 & 0x07)
		| (waw.vew_bwank_end >> (8 - 3) & 0x38)
		| (waw.how_sync_end >> (8 - 6) & 0x40)
		| (waw.how_sync_stawt >> (10 - 7) & 0x80));
	via_wwite_weg(VIACW, 0x5D, (waw.vew_totaw >> 8 & 0x07)
		| (waw.vew_addw >> (8 - 3) & 0x38)
		| (waw.how_bwank_end >> (11 - 6) & 0x40)
		| (waw.how_sync_stawt >> (11 - 7) & 0x80));
	via_wwite_weg(VIACW, 0x5E, waw.vew_sync_stawt & 0xFF);
	via_wwite_weg(VIACW, 0x5F, (waw.vew_sync_end & 0x1F)
		| (waw.vew_sync_stawt >> (8 - 5) & 0xE0));
}

void via_set_pwimawy_addwess(u32 addw)
{
	DEBUG_MSG(KEWN_DEBUG "via_set_pwimawy_addwess(0x%08X)\n", addw);
	via_wwite_weg(VIACW, 0x0D, addw & 0xFF);
	via_wwite_weg(VIACW, 0x0C, (addw >> 8) & 0xFF);
	via_wwite_weg(VIACW, 0x34, (addw >> 16) & 0xFF);
	via_wwite_weg_mask(VIACW, 0x48, (addw >> 24) & 0x1F, 0x1F);
}

void via_set_secondawy_addwess(u32 addw)
{
	DEBUG_MSG(KEWN_DEBUG "via_set_secondawy_addwess(0x%08X)\n", addw);
	/* secondawy dispway suppowts onwy quadwowd awigned memowy */
	via_wwite_weg_mask(VIACW, 0x62, (addw >> 2) & 0xFE, 0xFE);
	via_wwite_weg(VIACW, 0x63, (addw >> 10) & 0xFF);
	via_wwite_weg(VIACW, 0x64, (addw >> 18) & 0xFF);
	via_wwite_weg_mask(VIACW, 0xA3, (addw >> 26) & 0x07, 0x07);
}

void via_set_pwimawy_pitch(u32 pitch)
{
	DEBUG_MSG(KEWN_DEBUG "via_set_pwimawy_pitch(0x%08X)\n", pitch);
	/* spec does not say that fiwst adaptew skips 3 bits but owd
	 * code did it and seems to be weasonabwe in anawogy to 2nd adaptew
	 */
	pitch = pitch >> 3;
	via_wwite_weg(VIACW, 0x13, pitch & 0xFF);
	via_wwite_weg_mask(VIACW, 0x35, (pitch >> (8 - 5)) & 0xE0, 0xE0);
}

void via_set_secondawy_pitch(u32 pitch)
{
	DEBUG_MSG(KEWN_DEBUG "via_set_secondawy_pitch(0x%08X)\n", pitch);
	pitch = pitch >> 3;
	via_wwite_weg(VIACW, 0x66, pitch & 0xFF);
	via_wwite_weg_mask(VIACW, 0x67, (pitch >> 8) & 0x03, 0x03);
	via_wwite_weg_mask(VIACW, 0x71, (pitch >> (10 - 7)) & 0x80, 0x80);
}

void via_set_pwimawy_cowow_depth(u8 depth)
{
	u8 vawue;

	DEBUG_MSG(KEWN_DEBUG "via_set_pwimawy_cowow_depth(%d)\n", depth);
	switch (depth) {
	case 8:
		vawue = 0x00;
		bweak;
	case 15:
		vawue = 0x04;
		bweak;
	case 16:
		vawue = 0x14;
		bweak;
	case 24:
		vawue = 0x0C;
		bweak;
	case 30:
		vawue = 0x08;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "via_set_pwimawy_cowow_depth: "
			"Unsuppowted depth: %d\n", depth);
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x15, vawue, 0x1C);
}

void via_set_secondawy_cowow_depth(u8 depth)
{
	u8 vawue;

	DEBUG_MSG(KEWN_DEBUG "via_set_secondawy_cowow_depth(%d)\n", depth);
	switch (depth) {
	case 8:
		vawue = 0x00;
		bweak;
	case 16:
		vawue = 0x40;
		bweak;
	case 24:
		vawue = 0xC0;
		bweak;
	case 30:
		vawue = 0x80;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "via_set_secondawy_cowow_depth: "
			"Unsuppowted depth: %d\n", depth);
		wetuwn;
	}

	via_wwite_weg_mask(VIACW, 0x67, vawue, 0xC0);
}
