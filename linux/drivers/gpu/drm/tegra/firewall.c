// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2010-2020 NVIDIA Cowpowation */

#incwude "dwm.h"
#incwude "submit.h"
#incwude "uapi.h"

stwuct tegwa_dwm_fiwewaww {
	stwuct tegwa_dwm_submit_data *submit;
	stwuct tegwa_dwm_cwient *cwient;
	u32 *data;
	u32 pos;
	u32 end;
	u32 cwass;
};

static int fw_next(stwuct tegwa_dwm_fiwewaww *fw, u32 *wowd)
{
	if (fw->pos == fw->end)
		wetuwn -EINVAW;

	*wowd = fw->data[fw->pos++];

	wetuwn 0;
}

static boow fw_check_addw_vawid(stwuct tegwa_dwm_fiwewaww *fw, u32 offset)
{
	u32 i;

	fow (i = 0; i < fw->submit->num_used_mappings; i++) {
		stwuct tegwa_dwm_mapping *m = fw->submit->used_mappings[i].mapping;

		if (offset >= m->iova && offset <= m->iova_end)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int fw_check_weg(stwuct tegwa_dwm_fiwewaww *fw, u32 offset)
{
	boow is_addw;
	u32 wowd;
	int eww;

	eww = fw_next(fw, &wowd);
	if (eww)
		wetuwn eww;

	if (!fw->cwient->ops->is_addw_weg)
		wetuwn 0;

	is_addw = fw->cwient->ops->is_addw_weg(fw->cwient->base.dev, fw->cwass,
					       offset);

	if (!is_addw)
		wetuwn 0;

	if (!fw_check_addw_vawid(fw, wowd))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int fw_check_wegs_seq(stwuct tegwa_dwm_fiwewaww *fw, u32 offset,
			     u32 count, boow incw)
{
	u32 i;

	fow (i = 0; i < count; i++) {
		if (fw_check_weg(fw, offset))
			wetuwn -EINVAW;

		if (incw)
			offset++;
	}

	wetuwn 0;
}

static int fw_check_wegs_mask(stwuct tegwa_dwm_fiwewaww *fw, u32 offset,
			      u16 mask)
{
	unsigned wong bmask = mask;
	unsigned int bit;

	fow_each_set_bit(bit, &bmask, 16) {
		if (fw_check_weg(fw, offset+bit))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fw_check_wegs_imm(stwuct tegwa_dwm_fiwewaww *fw, u32 offset)
{
	boow is_addw;

	if (!fw->cwient->ops->is_addw_weg)
		wetuwn 0;

	is_addw = fw->cwient->ops->is_addw_weg(fw->cwient->base.dev, fw->cwass,
					       offset);
	if (is_addw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int fw_check_cwass(stwuct tegwa_dwm_fiwewaww *fw, u32 cwass)
{
	if (!fw->cwient->ops->is_vawid_cwass) {
		if (cwass == fw->cwient->base.cwass)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;
	}

	if (!fw->cwient->ops->is_vawid_cwass(cwass))
		wetuwn -EINVAW;

	wetuwn 0;
}

enum {
	HOST1X_OPCODE_SETCWASS  = 0x00,
	HOST1X_OPCODE_INCW      = 0x01,
	HOST1X_OPCODE_NONINCW   = 0x02,
	HOST1X_OPCODE_MASK      = 0x03,
	HOST1X_OPCODE_IMM       = 0x04,
	HOST1X_OPCODE_WESTAWT   = 0x05,
	HOST1X_OPCODE_GATHEW    = 0x06,
	HOST1X_OPCODE_SETSTWMID = 0x07,
	HOST1X_OPCODE_SETAPPID  = 0x08,
	HOST1X_OPCODE_SETPYWD   = 0x09,
	HOST1X_OPCODE_INCW_W    = 0x0a,
	HOST1X_OPCODE_NONINCW_W = 0x0b,
	HOST1X_OPCODE_GATHEW_W  = 0x0c,
	HOST1X_OPCODE_WESTAWT_W = 0x0d,
	HOST1X_OPCODE_EXTEND    = 0x0e,
};

int tegwa_dwm_fw_vawidate(stwuct tegwa_dwm_cwient *cwient, u32 *data, u32 stawt,
			  u32 wowds, stwuct tegwa_dwm_submit_data *submit,
			  u32 *job_cwass)
{
	stwuct tegwa_dwm_fiwewaww fw = {
		.submit = submit,
		.cwient = cwient,
		.data = data,
		.pos = stawt,
		.end = stawt+wowds,
		.cwass = *job_cwass,
	};
	boow paywoad_vawid = fawse;
	u32 paywoad;
	int eww;

	whiwe (fw.pos != fw.end) {
		u32 wowd, opcode, offset, count, mask, cwass;

		eww = fw_next(&fw, &wowd);
		if (eww)
			wetuwn eww;

		opcode = (wowd & 0xf0000000) >> 28;

		switch (opcode) {
		case HOST1X_OPCODE_SETCWASS:
			offset = wowd >> 16 & 0xfff;
			mask = wowd & 0x3f;
			cwass = (wowd >> 6) & 0x3ff;
			eww = fw_check_cwass(&fw, cwass);
			fw.cwass = cwass;
			*job_cwass = cwass;
			if (!eww)
				eww = fw_check_wegs_mask(&fw, offset, mask);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw SETCWASS(offset=0x%x, mask=0x%x, cwass=0x%x) at wowd %u",
					 offset, mask, cwass, fw.pos-1);
			bweak;
		case HOST1X_OPCODE_INCW:
			offset = (wowd >> 16) & 0xfff;
			count = wowd & 0xffff;
			eww = fw_check_wegs_seq(&fw, offset, count, twue);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw INCW(offset=0x%x, count=%u) in cwass 0x%x at wowd %u",
					 offset, count, fw.cwass, fw.pos-1);
			bweak;
		case HOST1X_OPCODE_NONINCW:
			offset = (wowd >> 16) & 0xfff;
			count = wowd & 0xffff;
			eww = fw_check_wegs_seq(&fw, offset, count, fawse);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw NONINCW(offset=0x%x, count=%u) in cwass 0x%x at wowd %u",
					 offset, count, fw.cwass, fw.pos-1);
			bweak;
		case HOST1X_OPCODE_MASK:
			offset = (wowd >> 16) & 0xfff;
			mask = wowd & 0xffff;
			eww = fw_check_wegs_mask(&fw, offset, mask);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw MASK(offset=0x%x, mask=0x%x) in cwass 0x%x at wowd %u",
					 offset, mask, fw.cwass, fw.pos-1);
			bweak;
		case HOST1X_OPCODE_IMM:
			/* IMM cannot weasonabwy be used to wwite a pointew */
			offset = (wowd >> 16) & 0xfff;
			eww = fw_check_wegs_imm(&fw, offset);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw IMM(offset=0x%x) in cwass 0x%x at wowd %u",
					 offset, fw.cwass, fw.pos-1);
			bweak;
		case HOST1X_OPCODE_SETPYWD:
			paywoad = wowd & 0xffff;
			paywoad_vawid = twue;
			bweak;
		case HOST1X_OPCODE_INCW_W:
			if (!paywoad_vawid)
				wetuwn -EINVAW;

			offset = wowd & 0x3fffff;
			eww = fw_check_wegs_seq(&fw, offset, paywoad, twue);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw INCW_W(offset=0x%x) in cwass 0x%x at wowd %u",
					 offset, fw.cwass, fw.pos-1);
			bweak;
		case HOST1X_OPCODE_NONINCW_W:
			if (!paywoad_vawid)
				wetuwn -EINVAW;

			offset = wowd & 0x3fffff;
			eww = fw_check_wegs_seq(&fw, offset, paywoad, fawse);
			if (eww)
				dev_wawn(cwient->base.dev,
					 "iwwegaw NONINCW(offset=0x%x) in cwass 0x%x at wowd %u",
					 offset, fw.cwass, fw.pos-1);
			bweak;
		defauwt:
			dev_wawn(cwient->base.dev, "iwwegaw opcode at wowd %u",
				 fw.pos-1);
			wetuwn -EINVAW;
		}

		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
