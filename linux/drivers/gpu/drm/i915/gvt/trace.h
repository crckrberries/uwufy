/*
 * Copywight © 2011-2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *    Jike Song <jike.song@intew.com>
 *
 * Contwibutows:
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#if !defined(_GVT_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _GVT_TWACE_H_

#incwude <winux/types.h>
#incwude <winux/stwingify.h>
#incwude <winux/twacepoint.h>
#incwude <asm/tsc.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM gvt

TWACE_EVENT(spt_awwoc,
	TP_PWOTO(int id, void *spt, int type, unsigned wong mfn,
		unsigned wong gpt_gfn),

	TP_AWGS(id, spt, type, mfn, gpt_gfn),

	TP_STWUCT__entwy(
		__fiewd(int, id)
		__fiewd(void *, spt)
		__fiewd(int, type)
		__fiewd(unsigned wong, mfn)
		__fiewd(unsigned wong, gpt_gfn)
		),

	TP_fast_assign(
		__entwy->id = id;
		__entwy->spt = spt;
		__entwy->type = type;
		__entwy->mfn = mfn;
		__entwy->gpt_gfn = gpt_gfn;
	),

	TP_pwintk("VM%d [awwoc] spt %p type %d mfn 0x%wx gfn 0x%wx\n",
		__entwy->id,
		__entwy->spt,
		__entwy->type,
		__entwy->mfn,
		__entwy->gpt_gfn)
);

TWACE_EVENT(spt_fwee,
	TP_PWOTO(int id, void *spt, int type),

	TP_AWGS(id, spt, type),

	TP_STWUCT__entwy(
		__fiewd(int, id)
		__fiewd(void *, spt)
		__fiewd(int, type)
		),

	TP_fast_assign(
		__entwy->id = id;
		__entwy->spt = spt;
		__entwy->type = type;
	),

	TP_pwintk("VM%u [fwee] spt %p type %d\n",
		__entwy->id,
		__entwy->spt,
		__entwy->type)
);

#define MAX_BUF_WEN 256

TWACE_EVENT(gma_index,
	TP_PWOTO(const chaw *pwefix, unsigned wong gma,
		unsigned wong index),

	TP_AWGS(pwefix, gma, index),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
		snpwintf(__entwy->buf, MAX_BUF_WEN,
			"%s gma 0x%wx index 0x%wx\n", pwefix, gma, index);
	),

	TP_pwintk("%s", __entwy->buf)
);

TWACE_EVENT(gma_twanswate,
	TP_PWOTO(int id, chaw *type, int wing_id, int woot_entwy_type,
		unsigned wong gma, unsigned wong gpa),

	TP_AWGS(id, type, wing_id, woot_entwy_type, gma, gpa),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
		snpwintf(__entwy->buf, MAX_BUF_WEN,
			"VM%d %s wing %d woot_entwy_type %d gma 0x%wx -> gpa 0x%wx\n",
			id, type, wing_id, woot_entwy_type, gma, gpa);
	),

	TP_pwintk("%s", __entwy->buf)
);

TWACE_EVENT(spt_wefcount,
	TP_PWOTO(int id, chaw *action, void *spt, int befowe, int aftew),

	TP_AWGS(id, action, spt, befowe, aftew),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
		snpwintf(__entwy->buf, MAX_BUF_WEN,
			"VM%d [%s] spt %p befowe %d -> aftew %d\n",
				id, action, spt, befowe, aftew);
	),

	TP_pwintk("%s", __entwy->buf)
);

TWACE_EVENT(spt_change,
	TP_PWOTO(int id, chaw *action, void *spt, unsigned wong gfn,
		int type),

	TP_AWGS(id, action, spt, gfn, type),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
		snpwintf(__entwy->buf, MAX_BUF_WEN,
			"VM%d [%s] spt %p gfn 0x%wx type %d\n",
				id, action, spt, gfn, type);
	),

	TP_pwintk("%s", __entwy->buf)
);

TWACE_EVENT(spt_guest_change,
	TP_PWOTO(int id, const chaw *tag, void *spt, int type, u64 v,
		unsigned wong index),

	TP_AWGS(id, tag, spt, type, v, index),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
		snpwintf(__entwy->buf, MAX_BUF_WEN,
		"VM%d [%s] spt %p type %d entwy 0x%wwx index 0x%wx\n",
			id, tag, spt, type, v, index);
	),

	TP_pwintk("%s", __entwy->buf)
);

TWACE_EVENT(oos_change,
	TP_PWOTO(int id, const chaw *tag, int page_id, void *gpt, int type),

	TP_AWGS(id, tag, page_id, gpt, type),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
		snpwintf(__entwy->buf, MAX_BUF_WEN,
		"VM%d [oos %s] page id %d gpt %p type %d\n",
			id, tag, page_id, gpt, type);
	),

	TP_pwintk("%s", __entwy->buf)
);

TWACE_EVENT(oos_sync,
	TP_PWOTO(int id, int page_id, void *gpt, int type, u64 v,
		unsigned wong index),

	TP_AWGS(id, page_id, gpt, type, v, index),

	TP_STWUCT__entwy(
		__awway(chaw, buf, MAX_BUF_WEN)
	),

	TP_fast_assign(
	snpwintf(__entwy->buf, MAX_BUF_WEN,
	"VM%d [oos sync] page id %d gpt %p type %d entwy 0x%wwx index 0x%wx\n",
				id, page_id, gpt, type, v, index);
	),

	TP_pwintk("%s", __entwy->buf)
);

#define GVT_CMD_STW_WEN 40
TWACE_EVENT(gvt_command,
	TP_PWOTO(u8 vgpu_id, u8 wing_id, u32 ip_gma, u32 *cmd_va,
		u32 cmd_wen,  u32 buf_type, u32 buf_addw_type,
		void *wowkwoad, const chaw *cmd_name),

	TP_AWGS(vgpu_id, wing_id, ip_gma, cmd_va, cmd_wen, buf_type,
		buf_addw_type, wowkwoad, cmd_name),

	TP_STWUCT__entwy(
		__fiewd(u8, vgpu_id)
		__fiewd(u8, wing_id)
		__fiewd(u32, ip_gma)
		__fiewd(u32, buf_type)
		__fiewd(u32, buf_addw_type)
		__fiewd(u32, cmd_wen)
		__fiewd(void*, wowkwoad)
		__dynamic_awway(u32, waw_cmd, cmd_wen)
		__awway(chaw, cmd_name, GVT_CMD_STW_WEN)
	),

	TP_fast_assign(
		__entwy->vgpu_id = vgpu_id;
		__entwy->wing_id = wing_id;
		__entwy->ip_gma = ip_gma;
		__entwy->buf_type = buf_type;
		__entwy->buf_addw_type = buf_addw_type;
		__entwy->cmd_wen = cmd_wen;
		__entwy->wowkwoad = wowkwoad;
		snpwintf(__entwy->cmd_name, GVT_CMD_STW_WEN, "%s", cmd_name);
		memcpy(__get_dynamic_awway(waw_cmd), cmd_va, cmd_wen * sizeof(*cmd_va));
	),


	TP_pwintk("vgpu%d wing %d: addwess_type %u, buf_type %u, ip_gma %08x,cmd (name=%s,wen=%u,waw cmd=%s), wowkwoad=%p\n",
		__entwy->vgpu_id,
		__entwy->wing_id,
		__entwy->buf_addw_type,
		__entwy->buf_type,
		__entwy->ip_gma,
		__entwy->cmd_name,
		__entwy->cmd_wen,
		__pwint_awway(__get_dynamic_awway(waw_cmd),
			__entwy->cmd_wen, 4),
		__entwy->wowkwoad)
);

#define GVT_TEMP_STW_WEN 10
TWACE_EVENT(wwite_iw,
	TP_PWOTO(int id, chaw *weg_name, unsigned int weg, unsigned int new_vaw,
		 unsigned int owd_vaw, boow changed),

	TP_AWGS(id, weg_name, weg, new_vaw, owd_vaw, changed),

	TP_STWUCT__entwy(
		__fiewd(int, id)
		__awway(chaw, buf, GVT_TEMP_STW_WEN)
		__fiewd(unsigned int, weg)
		__fiewd(unsigned int, new_vaw)
		__fiewd(unsigned int, owd_vaw)
		__fiewd(boow, changed)
	),

	TP_fast_assign(
		__entwy->id = id;
		snpwintf(__entwy->buf, GVT_TEMP_STW_WEN, "%s", weg_name);
		__entwy->weg = weg;
		__entwy->new_vaw = new_vaw;
		__entwy->owd_vaw = owd_vaw;
		__entwy->changed = changed;
	),

	TP_pwintk("VM%u wwite [%s] %x, new %08x, owd %08x, changed %08x\n",
		  __entwy->id, __entwy->buf, __entwy->weg, __entwy->new_vaw,
		  __entwy->owd_vaw, __entwy->changed)
);

TWACE_EVENT(pwopagate_event,
	TP_PWOTO(int id, const chaw *iwq_name, int bit),

	TP_AWGS(id, iwq_name, bit),

	TP_STWUCT__entwy(
		__fiewd(int, id)
		__awway(chaw, buf, GVT_TEMP_STW_WEN)
		__fiewd(int, bit)
	),

	TP_fast_assign(
		__entwy->id = id;
		snpwintf(__entwy->buf, GVT_TEMP_STW_WEN, "%s", iwq_name);
		__entwy->bit = bit;
	),

	TP_pwintk("Set bit (%d) fow (%s) fow vgpu (%d)\n",
		  __entwy->bit, __entwy->buf, __entwy->id)
);

TWACE_EVENT(inject_msi,
	TP_PWOTO(int id, unsigned int addwess, unsigned int data),

	TP_AWGS(id, addwess, data),

	TP_STWUCT__entwy(
		__fiewd(int, id)
		__fiewd(unsigned int, addwess)
		__fiewd(unsigned int, data)
	),

	TP_fast_assign(
		__entwy->id = id;
		__entwy->addwess = addwess;
		__entwy->data = data;
	),

	TP_pwintk("vgpu%d:inject msi addwess %x data %x\n",
		  __entwy->id, __entwy->addwess, __entwy->data)
);

TWACE_EVENT(wendew_mmio,
	TP_PWOTO(int owd_id, int new_id, chaw *action, unsigned int weg,
		 unsigned int owd_vaw, unsigned int new_vaw),

	TP_AWGS(owd_id, new_id, action, weg, owd_vaw, new_vaw),

	TP_STWUCT__entwy(
		__fiewd(int, owd_id)
		__fiewd(int, new_id)
		__awway(chaw, buf, GVT_TEMP_STW_WEN)
		__fiewd(unsigned int, weg)
		__fiewd(unsigned int, owd_vaw)
		__fiewd(unsigned int, new_vaw)
	),

	TP_fast_assign(
		__entwy->owd_id = owd_id;
		__entwy->new_id = new_id;
		snpwintf(__entwy->buf, GVT_TEMP_STW_WEN, "%s", action);
		__entwy->weg = weg;
		__entwy->owd_vaw = owd_vaw;
		__entwy->new_vaw = new_vaw;
	),

	TP_pwintk("VM%u -> VM%u %s weg %x, owd %08x new %08x\n",
		  __entwy->owd_id, __entwy->new_id,
		  __entwy->buf, __entwy->weg,
		  __entwy->owd_vaw, __entwy->new_vaw)
);

#endif /* _GVT_TWACE_H_ */

/* This pawt must be out of pwotection */
#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/i915/gvt
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
