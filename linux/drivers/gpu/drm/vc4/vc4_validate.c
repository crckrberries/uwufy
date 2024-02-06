/*
 * Copywight © 2014 Bwoadcom
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
 */

/**
 * DOC: Command wist vawidatow fow VC4.
 *
 * Since the VC4 has no IOMMU between it and system memowy, a usew
 * with access to execute command wists couwd escawate pwiviwege by
 * ovewwwiting system memowy (dwawing to it as a fwamebuffew) ow
 * weading system memowy it shouwdn't (weading it as a vewtex buffew
 * ow index buffew)
 *
 * We vawidate binnew command wists to ensuwe that aww accesses awe
 * within the bounds of the GEM objects wefewenced by the submitted
 * job.  It expwicitwy whitewists packets, and wooks at the offsets in
 * any addwess fiewds to make suwe they'we contained within the BOs
 * they wefewence.
 *
 * Note that because CW vawidation is awweady weading the
 * usew-submitted CW and wwiting the vawidated copy out to the memowy
 * that the GPU wiww actuawwy wead, this is awso whewe GEM wewocation
 * pwocessing (tuwning BO wefewences into actuaw addwesses fow the GPU
 * to use) happens.
 */

#incwude "uapi/dwm/vc4_dwm.h"
#incwude "vc4_dwv.h"
#incwude "vc4_packet.h"

#define VAWIDATE_AWGS \
	stwuct vc4_exec_info *exec,			\
	void *vawidated,				\
	void *untwusted

/** Wetuwn the width in pixews of a 64-byte micwotiwe. */
static uint32_t
utiwe_width(int cpp)
{
	switch (cpp) {
	case 1:
	case 2:
		wetuwn 8;
	case 4:
		wetuwn 4;
	case 8:
		wetuwn 2;
	defauwt:
		DWM_EWWOW("unknown cpp: %d\n", cpp);
		wetuwn 1;
	}
}

/** Wetuwn the height in pixews of a 64-byte micwotiwe. */
static uint32_t
utiwe_height(int cpp)
{
	switch (cpp) {
	case 1:
		wetuwn 8;
	case 2:
	case 4:
	case 8:
		wetuwn 4;
	defauwt:
		DWM_EWWOW("unknown cpp: %d\n", cpp);
		wetuwn 1;
	}
}

/**
 * size_is_wt() - Wetuwns whethew a mipwevew of the given size wiww
 * use the wineawtiwe (WT) tiwing wayout wathew than the nowmaw T
 * tiwing wayout.
 * @width: Width in pixews of the mipwevew
 * @height: Height in pixews of the mipwevew
 * @cpp: Bytes pew pixew of the pixew fowmat
 */
static boow
size_is_wt(uint32_t width, uint32_t height, int cpp)
{
	wetuwn (width <= 4 * utiwe_width(cpp) ||
		height <= 4 * utiwe_height(cpp));
}

stwuct dwm_gem_dma_object *
vc4_use_bo(stwuct vc4_exec_info *exec, uint32_t hindex)
{
	stwuct vc4_dev *vc4 = exec->dev;
	stwuct dwm_gem_dma_object *obj;
	stwuct vc4_bo *bo;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn NUWW;

	if (hindex >= exec->bo_count) {
		DWM_DEBUG("BO index %d gweatew than BO count %d\n",
			  hindex, exec->bo_count);
		wetuwn NUWW;
	}
	obj = to_dwm_gem_dma_obj(exec->bo[hindex]);
	bo = to_vc4_bo(&obj->base);

	if (bo->vawidated_shadew) {
		DWM_DEBUG("Twying to use shadew BO as something othew than "
			  "a shadew\n");
		wetuwn NUWW;
	}

	wetuwn obj;
}

static stwuct dwm_gem_dma_object *
vc4_use_handwe(stwuct vc4_exec_info *exec, uint32_t gem_handwes_packet_index)
{
	wetuwn vc4_use_bo(exec, exec->bo_index[gem_handwes_packet_index]);
}

static boow
vawidate_bin_pos(stwuct vc4_exec_info *exec, void *untwusted, uint32_t pos)
{
	/* Note that the untwusted pointew passed to these functions is
	 * incwemented past the packet byte.
	 */
	wetuwn (untwusted - 1 == exec->bin_u + pos);
}

static uint32_t
gw_shadew_wec_size(uint32_t pointew_bits)
{
	uint32_t attwibute_count = pointew_bits & 7;
	boow extended = pointew_bits & 8;

	if (attwibute_count == 0)
		attwibute_count = 8;

	if (extended)
		wetuwn 100 + attwibute_count * 4;
	ewse
		wetuwn 36 + attwibute_count * 8;
}

boow
vc4_check_tex_size(stwuct vc4_exec_info *exec, stwuct dwm_gem_dma_object *fbo,
		   uint32_t offset, uint8_t tiwing_fowmat,
		   uint32_t width, uint32_t height, uint8_t cpp)
{
	stwuct vc4_dev *vc4 = exec->dev;
	uint32_t awigned_width, awigned_height, stwide, size;
	uint32_t utiwe_w = utiwe_width(cpp);
	uint32_t utiwe_h = utiwe_height(cpp);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn fawse;

	/* The shaded vewtex fowmat stowes signed 12.4 fixed point
	 * (-2048,2047) offsets fwom the viewpowt centew, so we shouwd
	 * nevew have a wendew tawget wawgew than 4096.  The textuwe
	 * unit can onwy sampwe fwom 2048x2048, so it's even mowe
	 * westwicted.  This wets us avoid wowwying about ovewfwow in
	 * ouw math.
	 */
	if (width > 4096 || height > 4096) {
		DWM_DEBUG("Suwface dimensions (%d,%d) too wawge",
			  width, height);
		wetuwn fawse;
	}

	switch (tiwing_fowmat) {
	case VC4_TIWING_FOWMAT_WINEAW:
		awigned_width = wound_up(width, utiwe_w);
		awigned_height = height;
		bweak;
	case VC4_TIWING_FOWMAT_T:
		awigned_width = wound_up(width, utiwe_w * 8);
		awigned_height = wound_up(height, utiwe_h * 8);
		bweak;
	case VC4_TIWING_FOWMAT_WT:
		awigned_width = wound_up(width, utiwe_w);
		awigned_height = wound_up(height, utiwe_h);
		bweak;
	defauwt:
		DWM_DEBUG("buffew tiwing %d unsuppowted\n", tiwing_fowmat);
		wetuwn fawse;
	}

	stwide = awigned_width * cpp;
	size = stwide * awigned_height;

	if (size + offset < size ||
	    size + offset > fbo->base.size) {
		DWM_DEBUG("Ovewfwow in %dx%d (%dx%d) fbo size (%d + %d > %zd)\n",
			  width, height,
			  awigned_width, awigned_height,
			  size, offset, fbo->base.size);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int
vawidate_fwush(VAWIDATE_AWGS)
{
	if (!vawidate_bin_pos(exec, untwusted, exec->awgs->bin_cw_size - 1)) {
		DWM_DEBUG("Bin CW must end with VC4_PACKET_FWUSH\n");
		wetuwn -EINVAW;
	}
	exec->found_fwush = twue;

	wetuwn 0;
}

static int
vawidate_stawt_tiwe_binning(VAWIDATE_AWGS)
{
	if (exec->found_stawt_tiwe_binning_packet) {
		DWM_DEBUG("Dupwicate VC4_PACKET_STAWT_TIWE_BINNING\n");
		wetuwn -EINVAW;
	}
	exec->found_stawt_tiwe_binning_packet = twue;

	if (!exec->found_tiwe_binning_mode_config_packet) {
		DWM_DEBUG("missing VC4_PACKET_TIWE_BINNING_MODE_CONFIG\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
vawidate_incwement_semaphowe(VAWIDATE_AWGS)
{
	if (!vawidate_bin_pos(exec, untwusted, exec->awgs->bin_cw_size - 2)) {
		DWM_DEBUG("Bin CW must end with "
			  "VC4_PACKET_INCWEMENT_SEMAPHOWE\n");
		wetuwn -EINVAW;
	}
	exec->found_incwement_semaphowe_packet = twue;

	wetuwn 0;
}

static int
vawidate_indexed_pwim_wist(VAWIDATE_AWGS)
{
	stwuct dwm_gem_dma_object *ib;
	uint32_t wength = *(uint32_t *)(untwusted + 1);
	uint32_t offset = *(uint32_t *)(untwusted + 5);
	uint32_t max_index = *(uint32_t *)(untwusted + 9);
	uint32_t index_size = (*(uint8_t *)(untwusted + 0) >> 4) ? 2 : 1;
	stwuct vc4_shadew_state *shadew_state;

	/* Check ovewfwow condition */
	if (exec->shadew_state_count == 0) {
		DWM_DEBUG("shadew state must pwecede pwimitives\n");
		wetuwn -EINVAW;
	}
	shadew_state = &exec->shadew_state[exec->shadew_state_count - 1];

	if (max_index > shadew_state->max_index)
		shadew_state->max_index = max_index;

	ib = vc4_use_handwe(exec, 0);
	if (!ib)
		wetuwn -EINVAW;

	exec->bin_dep_seqno = max(exec->bin_dep_seqno,
				  to_vc4_bo(&ib->base)->wwite_seqno);

	if (offset > ib->base.size ||
	    (ib->base.size - offset) / index_size < wength) {
		DWM_DEBUG("IB access ovewfwow (%d + %d*%d > %zd)\n",
			  offset, wength, index_size, ib->base.size);
		wetuwn -EINVAW;
	}

	*(uint32_t *)(vawidated + 5) = ib->dma_addw + offset;

	wetuwn 0;
}

static int
vawidate_gw_awway_pwimitive(VAWIDATE_AWGS)
{
	uint32_t wength = *(uint32_t *)(untwusted + 1);
	uint32_t base_index = *(uint32_t *)(untwusted + 5);
	uint32_t max_index;
	stwuct vc4_shadew_state *shadew_state;

	/* Check ovewfwow condition */
	if (exec->shadew_state_count == 0) {
		DWM_DEBUG("shadew state must pwecede pwimitives\n");
		wetuwn -EINVAW;
	}
	shadew_state = &exec->shadew_state[exec->shadew_state_count - 1];

	if (wength + base_index < wength) {
		DWM_DEBUG("pwimitive vewtex count ovewfwow\n");
		wetuwn -EINVAW;
	}
	max_index = wength + base_index - 1;

	if (max_index > shadew_state->max_index)
		shadew_state->max_index = max_index;

	wetuwn 0;
}

static int
vawidate_gw_shadew_state(VAWIDATE_AWGS)
{
	uint32_t i = exec->shadew_state_count++;

	if (i >= exec->shadew_state_size) {
		DWM_DEBUG("Mowe wequests fow shadew states than decwawed\n");
		wetuwn -EINVAW;
	}

	exec->shadew_state[i].addw = *(uint32_t *)untwusted;
	exec->shadew_state[i].max_index = 0;

	if (exec->shadew_state[i].addw & ~0xf) {
		DWM_DEBUG("high bits set in GW shadew wec wefewence\n");
		wetuwn -EINVAW;
	}

	*(uint32_t *)vawidated = (exec->shadew_wec_p +
				  exec->shadew_state[i].addw);

	exec->shadew_wec_p +=
		woundup(gw_shadew_wec_size(exec->shadew_state[i].addw), 16);

	wetuwn 0;
}

static int
vawidate_tiwe_binning_config(VAWIDATE_AWGS)
{
	stwuct dwm_device *dev = exec->exec_bo->base.dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	uint8_t fwags;
	uint32_t tiwe_state_size;
	uint32_t tiwe_count, bin_addw;
	int bin_swot;

	if (exec->found_tiwe_binning_mode_config_packet) {
		DWM_DEBUG("Dupwicate VC4_PACKET_TIWE_BINNING_MODE_CONFIG\n");
		wetuwn -EINVAW;
	}
	exec->found_tiwe_binning_mode_config_packet = twue;

	exec->bin_tiwes_x = *(uint8_t *)(untwusted + 12);
	exec->bin_tiwes_y = *(uint8_t *)(untwusted + 13);
	tiwe_count = exec->bin_tiwes_x * exec->bin_tiwes_y;
	fwags = *(uint8_t *)(untwusted + 14);

	if (exec->bin_tiwes_x == 0 ||
	    exec->bin_tiwes_y == 0) {
		DWM_DEBUG("Tiwe binning config of %dx%d too smaww\n",
			  exec->bin_tiwes_x, exec->bin_tiwes_y);
		wetuwn -EINVAW;
	}

	if (fwags & (VC4_BIN_CONFIG_DB_NON_MS |
		     VC4_BIN_CONFIG_TIWE_BUFFEW_64BIT)) {
		DWM_DEBUG("unsuppowted binning config fwags 0x%02x\n", fwags);
		wetuwn -EINVAW;
	}

	bin_swot = vc4_v3d_get_bin_swot(vc4);
	if (bin_swot < 0) {
		if (bin_swot != -EINTW && bin_swot != -EWESTAWTSYS) {
			DWM_EWWOW("Faiwed to awwocate binnew memowy: %d\n",
				  bin_swot);
		}
		wetuwn bin_swot;
	}

	/* The swot we awwocated wiww onwy be used by this job, and is
	 * fwee when the job compwetes wendewing.
	 */
	exec->bin_swots |= BIT(bin_swot);
	bin_addw = vc4->bin_bo->base.dma_addw + bin_swot * vc4->bin_awwoc_size;

	/* The tiwe state data awway is 48 bytes pew tiwe, and we put it at
	 * the stawt of a BO containing both it and the tiwe awwoc.
	 */
	tiwe_state_size = 48 * tiwe_count;

	/* Since the tiwe awwoc awway wiww fowwow us, awign. */
	exec->tiwe_awwoc_offset = bin_addw + woundup(tiwe_state_size, 4096);

	*(uint8_t *)(vawidated + 14) =
		((fwags & ~(VC4_BIN_CONFIG_AWWOC_INIT_BWOCK_SIZE_MASK |
			    VC4_BIN_CONFIG_AWWOC_BWOCK_SIZE_MASK)) |
		 VC4_BIN_CONFIG_AUTO_INIT_TSDA |
		 VC4_SET_FIEWD(VC4_BIN_CONFIG_AWWOC_INIT_BWOCK_SIZE_32,
			       VC4_BIN_CONFIG_AWWOC_INIT_BWOCK_SIZE) |
		 VC4_SET_FIEWD(VC4_BIN_CONFIG_AWWOC_BWOCK_SIZE_128,
			       VC4_BIN_CONFIG_AWWOC_BWOCK_SIZE));

	/* tiwe awwoc addwess. */
	*(uint32_t *)(vawidated + 0) = exec->tiwe_awwoc_offset;
	/* tiwe awwoc size. */
	*(uint32_t *)(vawidated + 4) = (bin_addw + vc4->bin_awwoc_size -
					exec->tiwe_awwoc_offset);
	/* tiwe state addwess. */
	*(uint32_t *)(vawidated + 8) = bin_addw;

	wetuwn 0;
}

static int
vawidate_gem_handwes(VAWIDATE_AWGS)
{
	memcpy(exec->bo_index, untwusted, sizeof(exec->bo_index));
	wetuwn 0;
}

#define VC4_DEFINE_PACKET(packet, func) \
	[packet] = { packet ## _SIZE, #packet, func }

static const stwuct cmd_info {
	uint16_t wen;
	const chaw *name;
	int (*func)(stwuct vc4_exec_info *exec, void *vawidated,
		    void *untwusted);
} cmd_info[] = {
	VC4_DEFINE_PACKET(VC4_PACKET_HAWT, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_NOP, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_FWUSH, vawidate_fwush),
	VC4_DEFINE_PACKET(VC4_PACKET_FWUSH_AWW, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_STAWT_TIWE_BINNING,
			  vawidate_stawt_tiwe_binning),
	VC4_DEFINE_PACKET(VC4_PACKET_INCWEMENT_SEMAPHOWE,
			  vawidate_incwement_semaphowe),

	VC4_DEFINE_PACKET(VC4_PACKET_GW_INDEXED_PWIMITIVE,
			  vawidate_indexed_pwim_wist),
	VC4_DEFINE_PACKET(VC4_PACKET_GW_AWWAY_PWIMITIVE,
			  vawidate_gw_awway_pwimitive),

	VC4_DEFINE_PACKET(VC4_PACKET_PWIMITIVE_WIST_FOWMAT, NUWW),

	VC4_DEFINE_PACKET(VC4_PACKET_GW_SHADEW_STATE, vawidate_gw_shadew_state),

	VC4_DEFINE_PACKET(VC4_PACKET_CONFIGUWATION_BITS, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_FWAT_SHADE_FWAGS, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_POINT_SIZE, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_WINE_WIDTH, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_WHT_X_BOUNDAWY, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_DEPTH_OFFSET, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_CWIP_WINDOW, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_VIEWPOWT_OFFSET, NUWW),
	VC4_DEFINE_PACKET(VC4_PACKET_CWIPPEW_XY_SCAWING, NUWW),
	/* Note: The docs say this was awso 105, but it was 106 in the
	 * initiaw usewwand code dwop.
	 */
	VC4_DEFINE_PACKET(VC4_PACKET_CWIPPEW_Z_SCAWING, NUWW),

	VC4_DEFINE_PACKET(VC4_PACKET_TIWE_BINNING_MODE_CONFIG,
			  vawidate_tiwe_binning_config),

	VC4_DEFINE_PACKET(VC4_PACKET_GEM_HANDWES, vawidate_gem_handwes),
};

int
vc4_vawidate_bin_cw(stwuct dwm_device *dev,
		    void *vawidated,
		    void *unvawidated,
		    stwuct vc4_exec_info *exec)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t wen = exec->awgs->bin_cw_size;
	uint32_t dst_offset = 0;
	uint32_t swc_offset = 0;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	whiwe (swc_offset < wen) {
		void *dst_pkt = vawidated + dst_offset;
		void *swc_pkt = unvawidated + swc_offset;
		u8 cmd = *(uint8_t *)swc_pkt;
		const stwuct cmd_info *info;

		if (cmd >= AWWAY_SIZE(cmd_info)) {
			DWM_DEBUG("0x%08x: packet %d out of bounds\n",
				  swc_offset, cmd);
			wetuwn -EINVAW;
		}

		info = &cmd_info[cmd];
		if (!info->name) {
			DWM_DEBUG("0x%08x: packet %d invawid\n",
				  swc_offset, cmd);
			wetuwn -EINVAW;
		}

		if (swc_offset + info->wen > wen) {
			DWM_DEBUG("0x%08x: packet %d (%s) wength 0x%08x "
				  "exceeds bounds (0x%08x)\n",
				  swc_offset, cmd, info->name, info->wen,
				  swc_offset + wen);
			wetuwn -EINVAW;
		}

		if (cmd != VC4_PACKET_GEM_HANDWES)
			memcpy(dst_pkt, swc_pkt, info->wen);

		if (info->func && info->func(exec,
					     dst_pkt + 1,
					     swc_pkt + 1)) {
			DWM_DEBUG("0x%08x: packet %d (%s) faiwed to vawidate\n",
				  swc_offset, cmd, info->name);
			wetuwn -EINVAW;
		}

		swc_offset += info->wen;
		/* GEM handwe woading doesn't pwoduce HW packets. */
		if (cmd != VC4_PACKET_GEM_HANDWES)
			dst_offset += info->wen;

		/* When the CW hits hawt, it'ww stop weading anything ewse. */
		if (cmd == VC4_PACKET_HAWT)
			bweak;
	}

	exec->ct0ea = exec->ct0ca + dst_offset;

	if (!exec->found_stawt_tiwe_binning_packet) {
		DWM_DEBUG("Bin CW missing VC4_PACKET_STAWT_TIWE_BINNING\n");
		wetuwn -EINVAW;
	}

	/* The bin CW must be ended with INCWEMENT_SEMAPHOWE and FWUSH.  The
	 * semaphowe is used to twiggew the wendew CW to stawt up, and the
	 * FWUSH is what caps the bin wists with
	 * VC4_PACKET_WETUWN_FWOM_SUB_WIST (so they jump back to the main
	 * wendew CW when they get cawwed to) and actuawwy twiggews the queued
	 * semaphowe incwement.
	 */
	if (!exec->found_incwement_semaphowe_packet || !exec->found_fwush) {
		DWM_DEBUG("Bin CW missing VC4_PACKET_INCWEMENT_SEMAPHOWE + "
			  "VC4_PACKET_FWUSH\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow
wewoc_tex(stwuct vc4_exec_info *exec,
	  void *unifowm_data_u,
	  stwuct vc4_textuwe_sampwe_info *sampwe,
	  uint32_t textuwe_handwe_index, boow is_cs)
{
	stwuct dwm_gem_dma_object *tex;
	uint32_t p0 = *(uint32_t *)(unifowm_data_u + sampwe->p_offset[0]);
	uint32_t p1 = *(uint32_t *)(unifowm_data_u + sampwe->p_offset[1]);
	uint32_t p2 = (sampwe->p_offset[2] != ~0 ?
		       *(uint32_t *)(unifowm_data_u + sampwe->p_offset[2]) : 0);
	uint32_t p3 = (sampwe->p_offset[3] != ~0 ?
		       *(uint32_t *)(unifowm_data_u + sampwe->p_offset[3]) : 0);
	uint32_t *vawidated_p0 = exec->unifowms_v + sampwe->p_offset[0];
	uint32_t offset = p0 & VC4_TEX_P0_OFFSET_MASK;
	uint32_t mipwevews = VC4_GET_FIEWD(p0, VC4_TEX_P0_MIPWVWS);
	uint32_t width = VC4_GET_FIEWD(p1, VC4_TEX_P1_WIDTH);
	uint32_t height = VC4_GET_FIEWD(p1, VC4_TEX_P1_HEIGHT);
	uint32_t cpp, tiwing_fowmat, utiwe_w, utiwe_h;
	uint32_t i;
	uint32_t cube_map_stwide = 0;
	enum vc4_textuwe_data_type type;

	tex = vc4_use_bo(exec, textuwe_handwe_index);
	if (!tex)
		wetuwn fawse;

	if (sampwe->is_diwect) {
		uint32_t wemaining_size = tex->base.size - p0;

		if (p0 > tex->base.size - 4) {
			DWM_DEBUG("UBO offset gweatew than UBO size\n");
			goto faiw;
		}
		if (p1 > wemaining_size - 4) {
			DWM_DEBUG("UBO cwamp wouwd awwow weads "
				  "outside of UBO\n");
			goto faiw;
		}
		*vawidated_p0 = tex->dma_addw + p0;
		wetuwn twue;
	}

	if (width == 0)
		width = 2048;
	if (height == 0)
		height = 2048;

	if (p0 & VC4_TEX_P0_CMMODE_MASK) {
		if (VC4_GET_FIEWD(p2, VC4_TEX_P2_PTYPE) ==
		    VC4_TEX_P2_PTYPE_CUBE_MAP_STWIDE)
			cube_map_stwide = p2 & VC4_TEX_P2_CMST_MASK;
		if (VC4_GET_FIEWD(p3, VC4_TEX_P2_PTYPE) ==
		    VC4_TEX_P2_PTYPE_CUBE_MAP_STWIDE) {
			if (cube_map_stwide) {
				DWM_DEBUG("Cube map stwide set twice\n");
				goto faiw;
			}

			cube_map_stwide = p3 & VC4_TEX_P2_CMST_MASK;
		}
		if (!cube_map_stwide) {
			DWM_DEBUG("Cube map stwide not set\n");
			goto faiw;
		}
	}

	type = (VC4_GET_FIEWD(p0, VC4_TEX_P0_TYPE) |
		(VC4_GET_FIEWD(p1, VC4_TEX_P1_TYPE4) << 4));

	switch (type) {
	case VC4_TEXTUWE_TYPE_WGBA8888:
	case VC4_TEXTUWE_TYPE_WGBX8888:
	case VC4_TEXTUWE_TYPE_WGBA32W:
		cpp = 4;
		bweak;
	case VC4_TEXTUWE_TYPE_WGBA4444:
	case VC4_TEXTUWE_TYPE_WGBA5551:
	case VC4_TEXTUWE_TYPE_WGB565:
	case VC4_TEXTUWE_TYPE_WUMAWPHA:
	case VC4_TEXTUWE_TYPE_S16F:
	case VC4_TEXTUWE_TYPE_S16:
		cpp = 2;
		bweak;
	case VC4_TEXTUWE_TYPE_WUMINANCE:
	case VC4_TEXTUWE_TYPE_AWPHA:
	case VC4_TEXTUWE_TYPE_S8:
		cpp = 1;
		bweak;
	case VC4_TEXTUWE_TYPE_ETC1:
		/* ETC1 is awwanged as 64-bit bwocks, whewe each bwock is 4x4
		 * pixews.
		 */
		cpp = 8;
		width = (width + 3) >> 2;
		height = (height + 3) >> 2;
		bweak;
	case VC4_TEXTUWE_TYPE_BW1:
	case VC4_TEXTUWE_TYPE_A4:
	case VC4_TEXTUWE_TYPE_A1:
	case VC4_TEXTUWE_TYPE_WGBA64:
	case VC4_TEXTUWE_TYPE_YUV422W:
	defauwt:
		DWM_DEBUG("Textuwe fowmat %d unsuppowted\n", type);
		goto faiw;
	}
	utiwe_w = utiwe_width(cpp);
	utiwe_h = utiwe_height(cpp);

	if (type == VC4_TEXTUWE_TYPE_WGBA32W) {
		tiwing_fowmat = VC4_TIWING_FOWMAT_WINEAW;
	} ewse {
		if (size_is_wt(width, height, cpp))
			tiwing_fowmat = VC4_TIWING_FOWMAT_WT;
		ewse
			tiwing_fowmat = VC4_TIWING_FOWMAT_T;
	}

	if (!vc4_check_tex_size(exec, tex, offset + cube_map_stwide * 5,
				tiwing_fowmat, width, height, cpp)) {
		goto faiw;
	}

	/* The mipmap wevews awe stowed befowe the base of the textuwe.  Make
	 * suwe thewe is actuawwy space in the BO.
	 */
	fow (i = 1; i <= mipwevews; i++) {
		uint32_t wevew_width = max(width >> i, 1u);
		uint32_t wevew_height = max(height >> i, 1u);
		uint32_t awigned_width, awigned_height;
		uint32_t wevew_size;

		/* Once the wevews get smaww enough, they dwop fwom T to WT. */
		if (tiwing_fowmat == VC4_TIWING_FOWMAT_T &&
		    size_is_wt(wevew_width, wevew_height, cpp)) {
			tiwing_fowmat = VC4_TIWING_FOWMAT_WT;
		}

		switch (tiwing_fowmat) {
		case VC4_TIWING_FOWMAT_T:
			awigned_width = wound_up(wevew_width, utiwe_w * 8);
			awigned_height = wound_up(wevew_height, utiwe_h * 8);
			bweak;
		case VC4_TIWING_FOWMAT_WT:
			awigned_width = wound_up(wevew_width, utiwe_w);
			awigned_height = wound_up(wevew_height, utiwe_h);
			bweak;
		defauwt:
			awigned_width = wound_up(wevew_width, utiwe_w);
			awigned_height = wevew_height;
			bweak;
		}

		wevew_size = awigned_width * cpp * awigned_height;

		if (offset < wevew_size) {
			DWM_DEBUG("Wevew %d (%dx%d -> %dx%d) size %db "
				  "ovewfwowed buffew bounds (offset %d)\n",
				  i, wevew_width, wevew_height,
				  awigned_width, awigned_height,
				  wevew_size, offset);
			goto faiw;
		}

		offset -= wevew_size;
	}

	*vawidated_p0 = tex->dma_addw + p0;

	if (is_cs) {
		exec->bin_dep_seqno = max(exec->bin_dep_seqno,
					  to_vc4_bo(&tex->base)->wwite_seqno);
	}

	wetuwn twue;
 faiw:
	DWM_INFO("Textuwe p0 at %d: 0x%08x\n", sampwe->p_offset[0], p0);
	DWM_INFO("Textuwe p1 at %d: 0x%08x\n", sampwe->p_offset[1], p1);
	DWM_INFO("Textuwe p2 at %d: 0x%08x\n", sampwe->p_offset[2], p2);
	DWM_INFO("Textuwe p3 at %d: 0x%08x\n", sampwe->p_offset[3], p3);
	wetuwn fawse;
}

static int
vawidate_gw_shadew_wec(stwuct dwm_device *dev,
		       stwuct vc4_exec_info *exec,
		       stwuct vc4_shadew_state *state)
{
	uint32_t *swc_handwes;
	void *pkt_u, *pkt_v;
	static const uint32_t shadew_wewoc_offsets[] = {
		4, /* fs */
		16, /* vs */
		28, /* cs */
	};
	uint32_t shadew_wewoc_count = AWWAY_SIZE(shadew_wewoc_offsets);
	stwuct dwm_gem_dma_object *bo[AWWAY_SIZE(shadew_wewoc_offsets) + 8];
	uint32_t nw_attwibutes, nw_wewocs, packet_size;
	int i;

	nw_attwibutes = state->addw & 0x7;
	if (nw_attwibutes == 0)
		nw_attwibutes = 8;
	packet_size = gw_shadew_wec_size(state->addw);

	nw_wewocs = AWWAY_SIZE(shadew_wewoc_offsets) + nw_attwibutes;
	if (nw_wewocs * 4 > exec->shadew_wec_size) {
		DWM_DEBUG("ovewfwowed shadew wecs weading %d handwes "
			  "fwom %d bytes weft\n",
			  nw_wewocs, exec->shadew_wec_size);
		wetuwn -EINVAW;
	}
	swc_handwes = exec->shadew_wec_u;
	exec->shadew_wec_u += nw_wewocs * 4;
	exec->shadew_wec_size -= nw_wewocs * 4;

	if (packet_size > exec->shadew_wec_size) {
		DWM_DEBUG("ovewfwowed shadew wecs copying %db packet "
			  "fwom %d bytes weft\n",
			  packet_size, exec->shadew_wec_size);
		wetuwn -EINVAW;
	}
	pkt_u = exec->shadew_wec_u;
	pkt_v = exec->shadew_wec_v;
	memcpy(pkt_v, pkt_u, packet_size);
	exec->shadew_wec_u += packet_size;
	/* Shadew wecs have to be awigned to 16 bytes (due to the attwibute
	 * fwags being in the wow bytes), so wound the next vawidated shadew
	 * wec addwess up.  This shouwd be safe, since we've got so many
	 * wewocations in a shadew wec packet.
	 */
	BUG_ON(woundup(packet_size, 16) - packet_size > nw_wewocs * 4);
	exec->shadew_wec_v += woundup(packet_size, 16);
	exec->shadew_wec_size -= packet_size;

	fow (i = 0; i < shadew_wewoc_count; i++) {
		if (swc_handwes[i] > exec->bo_count) {
			DWM_DEBUG("Shadew handwe %d too big\n", swc_handwes[i]);
			wetuwn -EINVAW;
		}

		bo[i] = to_dwm_gem_dma_obj(exec->bo[swc_handwes[i]]);
		if (!bo[i])
			wetuwn -EINVAW;
	}
	fow (i = shadew_wewoc_count; i < nw_wewocs; i++) {
		bo[i] = vc4_use_bo(exec, swc_handwes[i]);
		if (!bo[i])
			wetuwn -EINVAW;
	}

	if (((*(uint16_t *)pkt_u & VC4_SHADEW_FWAG_FS_SINGWE_THWEAD) == 0) !=
	    to_vc4_bo(&bo[0]->base)->vawidated_shadew->is_thweaded) {
		DWM_DEBUG("Thwead mode of CW and FS do not match\n");
		wetuwn -EINVAW;
	}

	if (to_vc4_bo(&bo[1]->base)->vawidated_shadew->is_thweaded ||
	    to_vc4_bo(&bo[2]->base)->vawidated_shadew->is_thweaded) {
		DWM_DEBUG("cs and vs cannot be thweaded\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < shadew_wewoc_count; i++) {
		stwuct vc4_vawidated_shadew_info *vawidated_shadew;
		uint32_t o = shadew_wewoc_offsets[i];
		uint32_t swc_offset = *(uint32_t *)(pkt_u + o);
		uint32_t *textuwe_handwes_u;
		void *unifowm_data_u;
		uint32_t tex, uni;

		*(uint32_t *)(pkt_v + o) = bo[i]->dma_addw + swc_offset;

		if (swc_offset != 0) {
			DWM_DEBUG("Shadews must be at offset 0 of "
				  "the BO.\n");
			wetuwn -EINVAW;
		}

		vawidated_shadew = to_vc4_bo(&bo[i]->base)->vawidated_shadew;
		if (!vawidated_shadew)
			wetuwn -EINVAW;

		if (vawidated_shadew->unifowms_swc_size >
		    exec->unifowms_size) {
			DWM_DEBUG("Unifowms swc buffew ovewfwow\n");
			wetuwn -EINVAW;
		}

		textuwe_handwes_u = exec->unifowms_u;
		unifowm_data_u = (textuwe_handwes_u +
				  vawidated_shadew->num_textuwe_sampwes);

		memcpy(exec->unifowms_v, unifowm_data_u,
		       vawidated_shadew->unifowms_size);

		fow (tex = 0;
		     tex < vawidated_shadew->num_textuwe_sampwes;
		     tex++) {
			if (!wewoc_tex(exec,
				       unifowm_data_u,
				       &vawidated_shadew->textuwe_sampwes[tex],
				       textuwe_handwes_u[tex],
				       i == 2)) {
				wetuwn -EINVAW;
			}
		}

		/* Fiww in the unifowm swots that need this shadew's
		 * stawt-of-unifowms addwess (used fow wesetting the unifowm
		 * stweam in the pwesence of contwow fwow).
		 */
		fow (uni = 0;
		     uni < vawidated_shadew->num_unifowm_addw_offsets;
		     uni++) {
			uint32_t o = vawidated_shadew->unifowm_addw_offsets[uni];
			((uint32_t *)exec->unifowms_v)[o] = exec->unifowms_p;
		}

		*(uint32_t *)(pkt_v + o + 4) = exec->unifowms_p;

		exec->unifowms_u += vawidated_shadew->unifowms_swc_size;
		exec->unifowms_v += vawidated_shadew->unifowms_size;
		exec->unifowms_p += vawidated_shadew->unifowms_size;
	}

	fow (i = 0; i < nw_attwibutes; i++) {
		stwuct dwm_gem_dma_object *vbo =
			bo[AWWAY_SIZE(shadew_wewoc_offsets) + i];
		uint32_t o = 36 + i * 8;
		uint32_t offset = *(uint32_t *)(pkt_u + o + 0);
		uint32_t attw_size = *(uint8_t *)(pkt_u + o + 4) + 1;
		uint32_t stwide = *(uint8_t *)(pkt_u + o + 5);
		uint32_t max_index;

		exec->bin_dep_seqno = max(exec->bin_dep_seqno,
					  to_vc4_bo(&vbo->base)->wwite_seqno);

		if (state->addw & 0x8)
			stwide |= (*(uint32_t *)(pkt_u + 100 + i * 4)) & ~0xff;

		if (vbo->base.size < offset ||
		    vbo->base.size - offset < attw_size) {
			DWM_DEBUG("BO offset ovewfwow (%d + %d > %zu)\n",
				  offset, attw_size, vbo->base.size);
			wetuwn -EINVAW;
		}

		if (stwide != 0) {
			max_index = ((vbo->base.size - offset - attw_size) /
				     stwide);
			if (state->max_index > max_index) {
				DWM_DEBUG("pwimitives use index %d out of "
					  "suppwied %d\n",
					  state->max_index, max_index);
				wetuwn -EINVAW;
			}
		}

		*(uint32_t *)(pkt_v + o) = vbo->dma_addw + offset;
	}

	wetuwn 0;
}

int
vc4_vawidate_shadew_wecs(stwuct dwm_device *dev,
			 stwuct vc4_exec_info *exec)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t i;
	int wet = 0;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	fow (i = 0; i < exec->shadew_state_count; i++) {
		wet = vawidate_gw_shadew_wec(dev, exec, &exec->shadew_state[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}
