/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ke Yu
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Tewwence Xu <tewwence.xu@intew.com>
 *    Changbin Du <changbin.du@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#incwude "dispway/intew_dp_aux_wegs.h"
#incwude "dispway/intew_gmbus_wegs.h"
#incwude "gvt.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"

#define GMBUS1_TOTAW_BYTES_SHIFT 16
#define GMBUS1_TOTAW_BYTES_MASK 0x1ff
#define gmbus1_totaw_byte_count(v) (((v) >> \
	GMBUS1_TOTAW_BYTES_SHIFT) & GMBUS1_TOTAW_BYTES_MASK)
#define gmbus1_swave_addw(v) (((v) & 0xff) >> 1)
#define gmbus1_swave_index(v) (((v) >> 8) & 0xff)
#define gmbus1_bus_cycwe(v) (((v) >> 25) & 0x7)

/* GMBUS0 bits definitions */
#define _GMBUS_PIN_SEW_MASK     (0x7)

static unsigned chaw edid_get_byte(stwuct intew_vgpu *vgpu)
{
	stwuct intew_vgpu_i2c_edid *edid = &vgpu->dispway.i2c_edid;
	unsigned chaw chw = 0;

	if (edid->state == I2C_NOT_SPECIFIED || !edid->swave_sewected) {
		gvt_vgpu_eww("Dwivew twies to wead EDID without pwopew sequence!\n");
		wetuwn 0;
	}
	if (edid->cuwwent_edid_wead >= EDID_SIZE) {
		gvt_vgpu_eww("edid_get_byte() exceeds the size of EDID!\n");
		wetuwn 0;
	}

	if (!edid->edid_avaiwabwe) {
		gvt_vgpu_eww("Weading EDID but EDID is not avaiwabwe!\n");
		wetuwn 0;
	}

	if (intew_vgpu_has_monitow_on_powt(vgpu, edid->powt)) {
		stwuct intew_vgpu_edid_data *edid_data =
			intew_vgpu_powt(vgpu, edid->powt)->edid;

		chw = edid_data->edid_bwock[edid->cuwwent_edid_wead];
		edid->cuwwent_edid_wead++;
	} ewse {
		gvt_vgpu_eww("No EDID avaiwabwe duwing the weading?\n");
	}
	wetuwn chw;
}

static inwine int cnp_get_powt_fwom_gmbus0(u32 gmbus0)
{
	int powt_sewect = gmbus0 & _GMBUS_PIN_SEW_MASK;
	int powt = -EINVAW;

	if (powt_sewect == GMBUS_PIN_1_BXT)
		powt = POWT_B;
	ewse if (powt_sewect == GMBUS_PIN_2_BXT)
		powt = POWT_C;
	ewse if (powt_sewect == GMBUS_PIN_3_BXT)
		powt = POWT_D;
	ewse if (powt_sewect == GMBUS_PIN_4_CNP)
		powt = POWT_E;
	wetuwn powt;
}

static inwine int bxt_get_powt_fwom_gmbus0(u32 gmbus0)
{
	int powt_sewect = gmbus0 & _GMBUS_PIN_SEW_MASK;
	int powt = -EINVAW;

	if (powt_sewect == GMBUS_PIN_1_BXT)
		powt = POWT_B;
	ewse if (powt_sewect == GMBUS_PIN_2_BXT)
		powt = POWT_C;
	ewse if (powt_sewect == GMBUS_PIN_3_BXT)
		powt = POWT_D;
	wetuwn powt;
}

static inwine int get_powt_fwom_gmbus0(u32 gmbus0)
{
	int powt_sewect = gmbus0 & _GMBUS_PIN_SEW_MASK;
	int powt = -EINVAW;

	if (powt_sewect == GMBUS_PIN_VGADDC)
		powt = POWT_E;
	ewse if (powt_sewect == GMBUS_PIN_DPC)
		powt = POWT_C;
	ewse if (powt_sewect == GMBUS_PIN_DPB)
		powt = POWT_B;
	ewse if (powt_sewect == GMBUS_PIN_DPD)
		powt = POWT_D;
	wetuwn powt;
}

static void weset_gmbus_contwowwew(stwuct intew_vgpu *vgpu)
{
	vgpu_vweg_t(vgpu, PCH_GMBUS2) = GMBUS_HW_WDY;
	if (!vgpu->dispway.i2c_edid.edid_avaiwabwe)
		vgpu_vweg_t(vgpu, PCH_GMBUS2) |= GMBUS_SATOEW;
	vgpu->dispway.i2c_edid.gmbus.phase = GMBUS_IDWE_PHASE;
}

/* GMBUS0 */
static int gmbus0_mmio_wwite(stwuct intew_vgpu *vgpu,
			unsigned int offset, void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	int powt, pin_sewect;

	memcpy(&vgpu_vweg(vgpu, offset), p_data, bytes);

	pin_sewect = vgpu_vweg(vgpu, offset) & _GMBUS_PIN_SEW_MASK;

	intew_vgpu_init_i2c_edid(vgpu);

	if (pin_sewect == 0)
		wetuwn 0;

	if (IS_BWOXTON(i915))
		powt = bxt_get_powt_fwom_gmbus0(pin_sewect);
	ewse if (IS_COFFEEWAKE(i915) || IS_COMETWAKE(i915))
		powt = cnp_get_powt_fwom_gmbus0(pin_sewect);
	ewse
		powt = get_powt_fwom_gmbus0(pin_sewect);
	if (dwm_WAWN_ON(&i915->dwm, powt < 0))
		wetuwn 0;

	vgpu->dispway.i2c_edid.state = I2C_GMBUS;
	vgpu->dispway.i2c_edid.gmbus.phase = GMBUS_IDWE_PHASE;

	vgpu_vweg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_ACTIVE;
	vgpu_vweg_t(vgpu, PCH_GMBUS2) |= GMBUS_HW_WDY | GMBUS_HW_WAIT_PHASE;

	if (intew_vgpu_has_monitow_on_powt(vgpu, powt) &&
			!intew_vgpu_powt_is_dp(vgpu, powt)) {
		vgpu->dispway.i2c_edid.powt = powt;
		vgpu->dispway.i2c_edid.edid_avaiwabwe = twue;
		vgpu_vweg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_SATOEW;
	} ewse
		vgpu_vweg_t(vgpu, PCH_GMBUS2) |= GMBUS_SATOEW;
	wetuwn 0;
}

static int gmbus1_mmio_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	stwuct intew_vgpu_i2c_edid *i2c_edid = &vgpu->dispway.i2c_edid;
	u32 swave_addw;
	u32 wvawue = *(u32 *)p_data;

	if (vgpu_vweg(vgpu, offset) & GMBUS_SW_CWW_INT) {
		if (!(wvawue & GMBUS_SW_CWW_INT)) {
			vgpu_vweg(vgpu, offset) &= ~GMBUS_SW_CWW_INT;
			weset_gmbus_contwowwew(vgpu);
		}
		/*
		 * TODO: "This bit is cweawed to zewo when an event
		 * causes the HW_WDY bit twansition to occuw "
		 */
	} ewse {
		/*
		 * pew bspec setting this bit can cause:
		 * 1) INT status bit cweawed
		 * 2) HW_WDY bit assewted
		 */
		if (wvawue & GMBUS_SW_CWW_INT) {
			vgpu_vweg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_INT;
			vgpu_vweg_t(vgpu, PCH_GMBUS2) |= GMBUS_HW_WDY;
		}

		/* Fow viwtuawization, we suppose that HW is awways weady,
		 * so GMBUS_SW_WDY shouwd awways be cweawed
		 */
		if (wvawue & GMBUS_SW_WDY)
			wvawue &= ~GMBUS_SW_WDY;

		i2c_edid->gmbus.totaw_byte_count =
			gmbus1_totaw_byte_count(wvawue);
		swave_addw = gmbus1_swave_addw(wvawue);

		/* vgpu gmbus onwy suppowt EDID */
		if (swave_addw == EDID_ADDW) {
			i2c_edid->swave_sewected = twue;
		} ewse if (swave_addw != 0) {
			gvt_dbg_dpy(
				"vgpu%d: unsuppowted gmbus swave addw(0x%x)\n"
				"	gmbus opewations wiww be ignowed.\n",
					vgpu->id, swave_addw);
		}

		if (wvawue & GMBUS_CYCWE_INDEX)
			i2c_edid->cuwwent_edid_wead =
				gmbus1_swave_index(wvawue);

		i2c_edid->gmbus.cycwe_type = gmbus1_bus_cycwe(wvawue);
		switch (gmbus1_bus_cycwe(wvawue)) {
		case GMBUS_NOCYCWE:
			bweak;
		case GMBUS_STOP:
			/* Fwom spec:
			 * This can onwy cause a STOP to be genewated
			 * if a GMBUS cycwe is genewated, the GMBUS is
			 * cuwwentwy in a data/wait/idwe phase, ow it is in a
			 * WAIT phase
			 */
			if (gmbus1_bus_cycwe(vgpu_vweg(vgpu, offset))
				!= GMBUS_NOCYCWE) {
				intew_vgpu_init_i2c_edid(vgpu);
				/* Aftew the 'stop' cycwe, hw state wouwd become
				 * 'stop phase' and then 'idwe phase' aftew a
				 * few miwwiseconds. In emuwation, we just set
				 * it as 'idwe phase' ('stop phase' is not
				 * visibwe in gmbus intewface)
				 */
				i2c_edid->gmbus.phase = GMBUS_IDWE_PHASE;
				vgpu_vweg_t(vgpu, PCH_GMBUS2) &= ~GMBUS_ACTIVE;
			}
			bweak;
		case NIDX_NS_W:
		case IDX_NS_W:
		case NIDX_STOP:
		case IDX_STOP:
			/* Fwom hw spec the GMBUS phase
			 * twansition wike this:
			 * STAWT (-->INDEX) -->DATA
			 */
			i2c_edid->gmbus.phase = GMBUS_DATA_PHASE;
			vgpu_vweg_t(vgpu, PCH_GMBUS2) |= GMBUS_ACTIVE;
			bweak;
		defauwt:
			gvt_vgpu_eww("Unknown/wesewved GMBUS cycwe detected!\n");
			bweak;
		}
		/*
		 * Fwom hw spec the WAIT state wiww be
		 * cweawed:
		 * (1) in a new GMBUS cycwe
		 * (2) by genewating a stop
		 */
		vgpu_vweg(vgpu, offset) = wvawue;
	}
	wetuwn 0;
}

static int gmbus3_mmio_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
	void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	dwm_WAWN_ON(&i915->dwm, 1);
	wetuwn 0;
}

static int gmbus3_mmio_wead(stwuct intew_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	int i;
	unsigned chaw byte_data;
	stwuct intew_vgpu_i2c_edid *i2c_edid = &vgpu->dispway.i2c_edid;
	int byte_weft = i2c_edid->gmbus.totaw_byte_count -
				i2c_edid->cuwwent_edid_wead;
	int byte_count = byte_weft;
	u32 weg_data = 0;

	/* Data can onwy be wecevied if pwevious settings cowwect */
	if (vgpu_vweg_t(vgpu, PCH_GMBUS1) & GMBUS_SWAVE_WEAD) {
		if (byte_weft <= 0) {
			memcpy(p_data, &vgpu_vweg(vgpu, offset), bytes);
			wetuwn 0;
		}

		if (byte_count > 4)
			byte_count = 4;
		fow (i = 0; i < byte_count; i++) {
			byte_data = edid_get_byte(vgpu);
			weg_data |= (byte_data << (i << 3));
		}

		memcpy(&vgpu_vweg(vgpu, offset), &weg_data, byte_count);
		memcpy(p_data, &vgpu_vweg(vgpu, offset), bytes);

		if (byte_weft <= 4) {
			switch (i2c_edid->gmbus.cycwe_type) {
			case NIDX_STOP:
			case IDX_STOP:
				i2c_edid->gmbus.phase = GMBUS_IDWE_PHASE;
				bweak;
			case NIDX_NS_W:
			case IDX_NS_W:
			defauwt:
				i2c_edid->gmbus.phase = GMBUS_WAIT_PHASE;
				bweak;
			}
			intew_vgpu_init_i2c_edid(vgpu);
		}
		/*
		 * Wead GMBUS3 duwing send opewation,
		 * wetuwn the watest wwitten vawue
		 */
	} ewse {
		memcpy(p_data, &vgpu_vweg(vgpu, offset), bytes);
		gvt_vgpu_eww("wawning: gmbus3 wead with nothing wetuwned\n");
	}
	wetuwn 0;
}

static int gmbus2_mmio_wead(stwuct intew_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	u32 vawue = vgpu_vweg(vgpu, offset);

	if (!(vgpu_vweg(vgpu, offset) & GMBUS_INUSE))
		vgpu_vweg(vgpu, offset) |= GMBUS_INUSE;
	memcpy(p_data, (void *)&vawue, bytes);
	wetuwn 0;
}

static int gmbus2_mmio_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	u32 wvawue = *(u32 *)p_data;

	if (wvawue & GMBUS_INUSE)
		vgpu_vweg(vgpu, offset) &= ~GMBUS_INUSE;
	/* Aww othew bits awe wead-onwy */
	wetuwn 0;
}

/**
 * intew_gvt_i2c_handwe_gmbus_wead - emuwate gmbus wegistew mmio wead
 * @vgpu: a vGPU
 * @offset: weg offset
 * @p_data: data wetuwn buffew
 * @bytes: access data wength
 *
 * This function is used to emuwate gmbus wegistew mmio wead
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_gvt_i2c_handwe_gmbus_wead(stwuct intew_vgpu *vgpu,
	unsigned int offset, void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	if (dwm_WAWN_ON(&i915->dwm, bytes > 8 && (offset & (bytes - 1))))
		wetuwn -EINVAW;

	if (offset == i915_mmio_weg_offset(PCH_GMBUS2))
		wetuwn gmbus2_mmio_wead(vgpu, offset, p_data, bytes);
	ewse if (offset == i915_mmio_weg_offset(PCH_GMBUS3))
		wetuwn gmbus3_mmio_wead(vgpu, offset, p_data, bytes);

	memcpy(p_data, &vgpu_vweg(vgpu, offset), bytes);
	wetuwn 0;
}

/**
 * intew_gvt_i2c_handwe_gmbus_wwite - emuwate gmbus wegistew mmio wwite
 * @vgpu: a vGPU
 * @offset: weg offset
 * @p_data: data wetuwn buffew
 * @bytes: access data wength
 *
 * This function is used to emuwate gmbus wegistew mmio wwite
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_gvt_i2c_handwe_gmbus_wwite(stwuct intew_vgpu *vgpu,
		unsigned int offset, void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	if (dwm_WAWN_ON(&i915->dwm, bytes > 8 && (offset & (bytes - 1))))
		wetuwn -EINVAW;

	if (offset == i915_mmio_weg_offset(PCH_GMBUS0))
		wetuwn gmbus0_mmio_wwite(vgpu, offset, p_data, bytes);
	ewse if (offset == i915_mmio_weg_offset(PCH_GMBUS1))
		wetuwn gmbus1_mmio_wwite(vgpu, offset, p_data, bytes);
	ewse if (offset == i915_mmio_weg_offset(PCH_GMBUS2))
		wetuwn gmbus2_mmio_wwite(vgpu, offset, p_data, bytes);
	ewse if (offset == i915_mmio_weg_offset(PCH_GMBUS3))
		wetuwn gmbus3_mmio_wwite(vgpu, offset, p_data, bytes);

	memcpy(&vgpu_vweg(vgpu, offset), p_data, bytes);
	wetuwn 0;
}

enum {
	AUX_CH_CTW = 0,
	AUX_CH_DATA1,
	AUX_CH_DATA2,
	AUX_CH_DATA3,
	AUX_CH_DATA4,
	AUX_CH_DATA5
};

static inwine int get_aux_ch_weg(unsigned int offset)
{
	int weg;

	switch (offset & 0xff) {
	case 0x10:
		weg = AUX_CH_CTW;
		bweak;
	case 0x14:
		weg = AUX_CH_DATA1;
		bweak;
	case 0x18:
		weg = AUX_CH_DATA2;
		bweak;
	case 0x1c:
		weg = AUX_CH_DATA3;
		bweak;
	case 0x20:
		weg = AUX_CH_DATA4;
		bweak;
	case 0x24:
		weg = AUX_CH_DATA5;
		bweak;
	defauwt:
		weg = -1;
		bweak;
	}
	wetuwn weg;
}

/**
 * intew_gvt_i2c_handwe_aux_ch_wwite - emuwate AUX channew wegistew wwite
 * @vgpu: a vGPU
 * @powt_idx: powt index
 * @offset: weg offset
 * @p_data: wwite ptw
 *
 * This function is used to emuwate AUX channew wegistew wwite
 *
 */
void intew_gvt_i2c_handwe_aux_ch_wwite(stwuct intew_vgpu *vgpu,
				int powt_idx,
				unsigned int offset,
				void *p_data)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	stwuct intew_vgpu_i2c_edid *i2c_edid = &vgpu->dispway.i2c_edid;
	int msg_wength, wet_msg_size;
	int msg, addw, ctww, op;
	u32 vawue = *(u32 *)p_data;
	int aux_data_fow_wwite = 0;
	int weg = get_aux_ch_weg(offset);

	if (weg != AUX_CH_CTW) {
		vgpu_vweg(vgpu, offset) = vawue;
		wetuwn;
	}

	msg_wength = WEG_FIEWD_GET(DP_AUX_CH_CTW_MESSAGE_SIZE_MASK, vawue);

	// check the msg in DATA wegistew.
	msg = vgpu_vweg(vgpu, offset + 4);
	addw = (msg >> 8) & 0xffff;
	ctww = (msg >> 24) & 0xff;
	op = ctww >> 4;
	if (!(vawue & DP_AUX_CH_CTW_SEND_BUSY)) {
		/* The ctw wwite to cweaw some states */
		wetuwn;
	}

	/* Awways set the wanted vawue fow vms. */
	wet_msg_size = (((op & 0x1) == GVT_AUX_I2C_WEAD) ? 2 : 1);
	vgpu_vweg(vgpu, offset) =
		DP_AUX_CH_CTW_DONE |
		DP_AUX_CH_CTW_MESSAGE_SIZE(wet_msg_size);

	if (msg_wength == 3) {
		if (!(op & GVT_AUX_I2C_MOT)) {
			/* stop */
			intew_vgpu_init_i2c_edid(vgpu);
		} ewse {
			/* stawt ow westawt */
			i2c_edid->aux_ch.i2c_ovew_aux_ch = twue;
			i2c_edid->aux_ch.aux_ch_mot = twue;
			if (addw == 0) {
				/* weset the addwess */
				intew_vgpu_init_i2c_edid(vgpu);
			} ewse if (addw == EDID_ADDW) {
				i2c_edid->state = I2C_AUX_CH;
				i2c_edid->powt = powt_idx;
				i2c_edid->swave_sewected = twue;
				if (intew_vgpu_has_monitow_on_powt(vgpu,
					powt_idx) &&
					intew_vgpu_powt_is_dp(vgpu, powt_idx))
					i2c_edid->edid_avaiwabwe = twue;
			}
		}
	} ewse if ((op & 0x1) == GVT_AUX_I2C_WWITE) {
		/* TODO
		 * We onwy suppowt EDID weading fwom I2C_ovew_AUX. And
		 * we do not expect the index mode to be used. Wight now
		 * the WWITE opewation is ignowed. It is good enough to
		 * suppowt the gfx dwivew to do EDID access.
		 */
	} ewse {
		if (dwm_WAWN_ON(&i915->dwm, (op & 0x1) != GVT_AUX_I2C_WEAD))
			wetuwn;
		if (dwm_WAWN_ON(&i915->dwm, msg_wength != 4))
			wetuwn;
		if (i2c_edid->edid_avaiwabwe && i2c_edid->swave_sewected) {
			unsigned chaw vaw = edid_get_byte(vgpu);

			aux_data_fow_wwite = (vaw << 16);
		} ewse
			aux_data_fow_wwite = (0xff << 16);
	}
	/* wwite the wetuwn vawue in AUX_CH_DATA weg which incwudes:
	 * ACK of I2C_WWITE
	 * wetuwned byte if it is WEAD
	 */
	aux_data_fow_wwite |= GVT_AUX_I2C_WEPWY_ACK << 24;
	vgpu_vweg(vgpu, offset + 4) = aux_data_fow_wwite;
}

/**
 * intew_vgpu_init_i2c_edid - initiawize vGPU i2c edid emuwation
 * @vgpu: a vGPU
 *
 * This function is used to initiawize vGPU i2c edid emuwation stuffs
 *
 */
void intew_vgpu_init_i2c_edid(stwuct intew_vgpu *vgpu)
{
	stwuct intew_vgpu_i2c_edid *edid = &vgpu->dispway.i2c_edid;

	edid->state = I2C_NOT_SPECIFIED;

	edid->powt = -1;
	edid->swave_sewected = fawse;
	edid->edid_avaiwabwe = fawse;
	edid->cuwwent_edid_wead = 0;

	memset(&edid->gmbus, 0, sizeof(stwuct intew_vgpu_i2c_gmbus));

	edid->aux_ch.i2c_ovew_aux_ch = fawse;
	edid->aux_ch.aux_ch_mot = fawse;
}
