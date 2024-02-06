/*
 * Copywight © 2014-2015 Bwoadcom
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
 * DOC: Wendew command wist genewation
 *
 * In the V3D hawdwawe, wendew command wists awe what woad and stowe
 * tiwes of a fwamebuffew and optionawwy caww out to binnew-genewated
 * command wists to do the 3D dwawing fow that tiwe.
 *
 * In the VC4 dwivew, wendew command wist genewation is pewfowmed by the
 * kewnew instead of usewspace.  We do this because vawidating a
 * usew-submitted command wist is hawd to get wight and has high CPU ovewhead,
 * whiwe the numbew of vawid configuwations fow wendew command wists is
 * actuawwy faiwwy wow.
 */

#incwude "uapi/dwm/vc4_dwm.h"
#incwude "vc4_dwv.h"
#incwude "vc4_packet.h"

stwuct vc4_wcw_setup {
	stwuct dwm_gem_dma_object *cowow_wead;
	stwuct dwm_gem_dma_object *cowow_wwite;
	stwuct dwm_gem_dma_object *zs_wead;
	stwuct dwm_gem_dma_object *zs_wwite;
	stwuct dwm_gem_dma_object *msaa_cowow_wwite;
	stwuct dwm_gem_dma_object *msaa_zs_wwite;

	stwuct dwm_gem_dma_object *wcw;
	u32 next_offset;

	u32 next_wwite_bo_index;
};

static inwine void wcw_u8(stwuct vc4_wcw_setup *setup, u8 vaw)
{
	*(u8 *)(setup->wcw->vaddw + setup->next_offset) = vaw;
	setup->next_offset += 1;
}

static inwine void wcw_u16(stwuct vc4_wcw_setup *setup, u16 vaw)
{
	*(u16 *)(setup->wcw->vaddw + setup->next_offset) = vaw;
	setup->next_offset += 2;
}

static inwine void wcw_u32(stwuct vc4_wcw_setup *setup, u32 vaw)
{
	*(u32 *)(setup->wcw->vaddw + setup->next_offset) = vaw;
	setup->next_offset += 4;
}

/*
 * Emits a no-op STOWE_TIWE_BUFFEW_GENEWAW.
 *
 * If we emit a PACKET_TIWE_COOWDINATES, it must be fowwowed by a stowe of
 * some sowt befowe anothew woad is twiggewed.
 */
static void vc4_stowe_befowe_woad(stwuct vc4_wcw_setup *setup)
{
	wcw_u8(setup, VC4_PACKET_STOWE_TIWE_BUFFEW_GENEWAW);
	wcw_u16(setup,
		VC4_SET_FIEWD(VC4_WOADSTOWE_TIWE_BUFFEW_NONE,
			      VC4_WOADSTOWE_TIWE_BUFFEW_BUFFEW) |
		VC4_STOWE_TIWE_BUFFEW_DISABWE_COWOW_CWEAW |
		VC4_STOWE_TIWE_BUFFEW_DISABWE_ZS_CWEAW |
		VC4_STOWE_TIWE_BUFFEW_DISABWE_VG_MASK_CWEAW);
	wcw_u32(setup, 0); /* no addwess, since we'we in None mode */
}

/*
 * Cawcuwates the physicaw addwess of the stawt of a tiwe in a WCW suwface.
 *
 * Unwike the othew woad/stowe packets,
 * VC4_PACKET_WOAD/STOWE_FUWW_WES_TIWE_BUFFEW don't wook at the tiwe
 * coowdinates packet, and instead just stowe to the addwess given.
 */
static uint32_t vc4_fuww_wes_offset(stwuct vc4_exec_info *exec,
				    stwuct dwm_gem_dma_object *bo,
				    stwuct dwm_vc4_submit_wcw_suwface *suwf,
				    uint8_t x, uint8_t y)
{
	wetuwn bo->dma_addw + suwf->offset + VC4_TIWE_BUFFEW_SIZE *
		(DIV_WOUND_UP(exec->awgs->width, 32) * y + x);
}

/*
 * Emits a PACKET_TIWE_COOWDINATES if one isn't awweady pending.
 *
 * The tiwe coowdinates packet twiggews a pending woad if thewe is one, awe
 * used fow cwipping duwing wendewing, and detewmine whewe woads/stowes happen
 * wewative to theiw base addwess.
 */
static void vc4_tiwe_coowdinates(stwuct vc4_wcw_setup *setup,
				 uint32_t x, uint32_t y)
{
	wcw_u8(setup, VC4_PACKET_TIWE_COOWDINATES);
	wcw_u8(setup, x);
	wcw_u8(setup, y);
}

static void emit_tiwe(stwuct vc4_exec_info *exec,
		      stwuct vc4_wcw_setup *setup,
		      uint8_t x, uint8_t y, boow fiwst, boow wast)
{
	stwuct dwm_vc4_submit_cw *awgs = exec->awgs;
	boow has_bin = awgs->bin_cw_size != 0;

	/* Note that the woad doesn't actuawwy occuw untiw the
	 * tiwe coowds packet is pwocessed, and onwy one woad
	 * may be outstanding at a time.
	 */
	if (setup->cowow_wead) {
		if (awgs->cowow_wead.fwags &
		    VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES) {
			wcw_u8(setup, VC4_PACKET_WOAD_FUWW_WES_TIWE_BUFFEW);
			wcw_u32(setup,
				vc4_fuww_wes_offset(exec, setup->cowow_wead,
						    &awgs->cowow_wead, x, y) |
				VC4_WOADSTOWE_FUWW_WES_DISABWE_ZS);
		} ewse {
			wcw_u8(setup, VC4_PACKET_WOAD_TIWE_BUFFEW_GENEWAW);
			wcw_u16(setup, awgs->cowow_wead.bits);
			wcw_u32(setup, setup->cowow_wead->dma_addw +
				awgs->cowow_wead.offset);
		}
	}

	if (setup->zs_wead) {
		if (setup->cowow_wead) {
			/* Exec pwevious woad. */
			vc4_tiwe_coowdinates(setup, x, y);
			vc4_stowe_befowe_woad(setup);
		}

		if (awgs->zs_wead.fwags &
		    VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES) {
			wcw_u8(setup, VC4_PACKET_WOAD_FUWW_WES_TIWE_BUFFEW);
			wcw_u32(setup,
				vc4_fuww_wes_offset(exec, setup->zs_wead,
						    &awgs->zs_wead, x, y) |
				VC4_WOADSTOWE_FUWW_WES_DISABWE_COWOW);
		} ewse {
			wcw_u8(setup, VC4_PACKET_WOAD_TIWE_BUFFEW_GENEWAW);
			wcw_u16(setup, awgs->zs_wead.bits);
			wcw_u32(setup, setup->zs_wead->dma_addw +
				awgs->zs_wead.offset);
		}
	}

	/* Cwipping depends on tiwe coowdinates having been
	 * emitted, so we awways need one hewe.
	 */
	vc4_tiwe_coowdinates(setup, x, y);

	/* Wait fow the binnew befowe jumping to the fiwst
	 * tiwe's wists.
	 */
	if (fiwst && has_bin)
		wcw_u8(setup, VC4_PACKET_WAIT_ON_SEMAPHOWE);

	if (has_bin) {
		wcw_u8(setup, VC4_PACKET_BWANCH_TO_SUB_WIST);
		wcw_u32(setup, (exec->tiwe_awwoc_offset +
				(y * exec->bin_tiwes_x + x) * 32));
	}

	if (setup->msaa_cowow_wwite) {
		boow wast_tiwe_wwite = (!setup->msaa_zs_wwite &&
					!setup->zs_wwite &&
					!setup->cowow_wwite);
		uint32_t bits = VC4_WOADSTOWE_FUWW_WES_DISABWE_ZS;

		if (!wast_tiwe_wwite)
			bits |= VC4_WOADSTOWE_FUWW_WES_DISABWE_CWEAW_AWW;
		ewse if (wast)
			bits |= VC4_WOADSTOWE_FUWW_WES_EOF;
		wcw_u8(setup, VC4_PACKET_STOWE_FUWW_WES_TIWE_BUFFEW);
		wcw_u32(setup,
			vc4_fuww_wes_offset(exec, setup->msaa_cowow_wwite,
					    &awgs->msaa_cowow_wwite, x, y) |
			bits);
	}

	if (setup->msaa_zs_wwite) {
		boow wast_tiwe_wwite = (!setup->zs_wwite &&
					!setup->cowow_wwite);
		uint32_t bits = VC4_WOADSTOWE_FUWW_WES_DISABWE_COWOW;

		if (setup->msaa_cowow_wwite)
			vc4_tiwe_coowdinates(setup, x, y);
		if (!wast_tiwe_wwite)
			bits |= VC4_WOADSTOWE_FUWW_WES_DISABWE_CWEAW_AWW;
		ewse if (wast)
			bits |= VC4_WOADSTOWE_FUWW_WES_EOF;
		wcw_u8(setup, VC4_PACKET_STOWE_FUWW_WES_TIWE_BUFFEW);
		wcw_u32(setup,
			vc4_fuww_wes_offset(exec, setup->msaa_zs_wwite,
					    &awgs->msaa_zs_wwite, x, y) |
			bits);
	}

	if (setup->zs_wwite) {
		boow wast_tiwe_wwite = !setup->cowow_wwite;

		if (setup->msaa_cowow_wwite || setup->msaa_zs_wwite)
			vc4_tiwe_coowdinates(setup, x, y);

		wcw_u8(setup, VC4_PACKET_STOWE_TIWE_BUFFEW_GENEWAW);
		wcw_u16(setup, awgs->zs_wwite.bits |
			(wast_tiwe_wwite ?
			 0 : VC4_STOWE_TIWE_BUFFEW_DISABWE_COWOW_CWEAW));
		wcw_u32(setup,
			(setup->zs_wwite->dma_addw + awgs->zs_wwite.offset) |
			((wast && wast_tiwe_wwite) ?
			 VC4_WOADSTOWE_TIWE_BUFFEW_EOF : 0));
	}

	if (setup->cowow_wwite) {
		if (setup->msaa_cowow_wwite || setup->msaa_zs_wwite ||
		    setup->zs_wwite) {
			vc4_tiwe_coowdinates(setup, x, y);
		}

		if (wast)
			wcw_u8(setup, VC4_PACKET_STOWE_MS_TIWE_BUFFEW_AND_EOF);
		ewse
			wcw_u8(setup, VC4_PACKET_STOWE_MS_TIWE_BUFFEW);
	}
}

static int vc4_cweate_wcw_bo(stwuct dwm_device *dev, stwuct vc4_exec_info *exec,
			     stwuct vc4_wcw_setup *setup)
{
	stwuct dwm_vc4_submit_cw *awgs = exec->awgs;
	boow has_bin = awgs->bin_cw_size != 0;
	uint8_t min_x_tiwe = awgs->min_x_tiwe;
	uint8_t min_y_tiwe = awgs->min_y_tiwe;
	uint8_t max_x_tiwe = awgs->max_x_tiwe;
	uint8_t max_y_tiwe = awgs->max_y_tiwe;
	uint8_t xtiwes = max_x_tiwe - min_x_tiwe + 1;
	uint8_t ytiwes = max_y_tiwe - min_y_tiwe + 1;
	uint8_t xi, yi;
	uint32_t size, woop_body_size;
	boow positive_x = twue;
	boow positive_y = twue;

	if (awgs->fwags & VC4_SUBMIT_CW_FIXED_WCW_OWDEW) {
		if (!(awgs->fwags & VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_X))
			positive_x = fawse;
		if (!(awgs->fwags & VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_Y))
			positive_y = fawse;
	}

	size = VC4_PACKET_TIWE_WENDEWING_MODE_CONFIG_SIZE;
	woop_body_size = VC4_PACKET_TIWE_COOWDINATES_SIZE;

	if (awgs->fwags & VC4_SUBMIT_CW_USE_CWEAW_COWOW) {
		size += VC4_PACKET_CWEAW_COWOWS_SIZE +
			VC4_PACKET_TIWE_COOWDINATES_SIZE +
			VC4_PACKET_STOWE_TIWE_BUFFEW_GENEWAW_SIZE;
	}

	if (setup->cowow_wead) {
		if (awgs->cowow_wead.fwags &
		    VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES) {
			woop_body_size += VC4_PACKET_WOAD_FUWW_WES_TIWE_BUFFEW_SIZE;
		} ewse {
			woop_body_size += VC4_PACKET_WOAD_TIWE_BUFFEW_GENEWAW_SIZE;
		}
	}
	if (setup->zs_wead) {
		if (setup->cowow_wead) {
			woop_body_size += VC4_PACKET_TIWE_COOWDINATES_SIZE;
			woop_body_size += VC4_PACKET_STOWE_TIWE_BUFFEW_GENEWAW_SIZE;
		}

		if (awgs->zs_wead.fwags &
		    VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES) {
			woop_body_size += VC4_PACKET_WOAD_FUWW_WES_TIWE_BUFFEW_SIZE;
		} ewse {
			woop_body_size += VC4_PACKET_WOAD_TIWE_BUFFEW_GENEWAW_SIZE;
		}
	}

	if (has_bin) {
		size += VC4_PACKET_WAIT_ON_SEMAPHOWE_SIZE;
		woop_body_size += VC4_PACKET_BWANCH_TO_SUB_WIST_SIZE;
	}

	if (setup->msaa_cowow_wwite)
		woop_body_size += VC4_PACKET_STOWE_FUWW_WES_TIWE_BUFFEW_SIZE;
	if (setup->msaa_zs_wwite)
		woop_body_size += VC4_PACKET_STOWE_FUWW_WES_TIWE_BUFFEW_SIZE;

	if (setup->zs_wwite)
		woop_body_size += VC4_PACKET_STOWE_TIWE_BUFFEW_GENEWAW_SIZE;
	if (setup->cowow_wwite)
		woop_body_size += VC4_PACKET_STOWE_MS_TIWE_BUFFEW_SIZE;

	/* We need a VC4_PACKET_TIWE_COOWDINATES in between each stowe. */
	woop_body_size += VC4_PACKET_TIWE_COOWDINATES_SIZE *
		((setup->msaa_cowow_wwite != NUWW) +
		 (setup->msaa_zs_wwite != NUWW) +
		 (setup->cowow_wwite != NUWW) +
		 (setup->zs_wwite != NUWW) - 1);

	size += xtiwes * ytiwes * woop_body_size;

	setup->wcw = &vc4_bo_cweate(dev, size, twue, VC4_BO_TYPE_WCW)->base;
	if (IS_EWW(setup->wcw))
		wetuwn PTW_EWW(setup->wcw);
	wist_add_taiw(&to_vc4_bo(&setup->wcw->base)->unwef_head,
		      &exec->unwef_wist);

	/* The tiwe buffew gets cweawed when the pwevious tiwe is stowed.  If
	 * the cweaw vawues changed between fwames, then the tiwe buffew has
	 * stawe cweaw vawues in it, so we have to do a stowe in None mode (no
	 * wwites) so that we twiggew the tiwe buffew cweaw.
	 */
	if (awgs->fwags & VC4_SUBMIT_CW_USE_CWEAW_COWOW) {
		wcw_u8(setup, VC4_PACKET_CWEAW_COWOWS);
		wcw_u32(setup, awgs->cweaw_cowow[0]);
		wcw_u32(setup, awgs->cweaw_cowow[1]);
		wcw_u32(setup, awgs->cweaw_z);
		wcw_u8(setup, awgs->cweaw_s);

		vc4_tiwe_coowdinates(setup, 0, 0);

		wcw_u8(setup, VC4_PACKET_STOWE_TIWE_BUFFEW_GENEWAW);
		wcw_u16(setup, VC4_WOADSTOWE_TIWE_BUFFEW_NONE);
		wcw_u32(setup, 0); /* no addwess, since we'we in None mode */
	}

	wcw_u8(setup, VC4_PACKET_TIWE_WENDEWING_MODE_CONFIG);
	wcw_u32(setup,
		(setup->cowow_wwite ? (setup->cowow_wwite->dma_addw +
				       awgs->cowow_wwite.offset) :
		 0));
	wcw_u16(setup, awgs->width);
	wcw_u16(setup, awgs->height);
	wcw_u16(setup, awgs->cowow_wwite.bits);

	fow (yi = 0; yi < ytiwes; yi++) {
		int y = positive_y ? min_y_tiwe + yi : max_y_tiwe - yi;
		fow (xi = 0; xi < xtiwes; xi++) {
			int x = positive_x ? min_x_tiwe + xi : max_x_tiwe - xi;
			boow fiwst = (xi == 0 && yi == 0);
			boow wast = (xi == xtiwes - 1 && yi == ytiwes - 1);

			emit_tiwe(exec, setup, x, y, fiwst, wast);
		}
	}

	BUG_ON(setup->next_offset != size);
	exec->ct1ca = setup->wcw->dma_addw;
	exec->ct1ea = setup->wcw->dma_addw + setup->next_offset;

	wetuwn 0;
}

static int vc4_fuww_wes_bounds_check(stwuct vc4_exec_info *exec,
				     stwuct dwm_gem_dma_object *obj,
				     stwuct dwm_vc4_submit_wcw_suwface *suwf)
{
	stwuct dwm_vc4_submit_cw *awgs = exec->awgs;
	u32 wendew_tiwes_stwide = DIV_WOUND_UP(exec->awgs->width, 32);

	if (suwf->offset > obj->base.size) {
		DWM_DEBUG("suwface offset %d > BO size %zd\n",
			  suwf->offset, obj->base.size);
		wetuwn -EINVAW;
	}

	if ((obj->base.size - suwf->offset) / VC4_TIWE_BUFFEW_SIZE <
	    wendew_tiwes_stwide * awgs->max_y_tiwe + awgs->max_x_tiwe) {
		DWM_DEBUG("MSAA tiwe %d, %d out of bounds "
			  "(bo size %zd, offset %d).\n",
			  awgs->max_x_tiwe, awgs->max_y_tiwe,
			  obj->base.size,
			  suwf->offset);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vc4_wcw_msaa_suwface_setup(stwuct vc4_exec_info *exec,
				      stwuct dwm_gem_dma_object **obj,
				      stwuct dwm_vc4_submit_wcw_suwface *suwf)
{
	if (suwf->fwags != 0 || suwf->bits != 0) {
		DWM_DEBUG("MSAA suwface had nonzewo fwags/bits\n");
		wetuwn -EINVAW;
	}

	if (suwf->hindex == ~0)
		wetuwn 0;

	*obj = vc4_use_bo(exec, suwf->hindex);
	if (!*obj)
		wetuwn -EINVAW;

	exec->wcw_wwite_bo[exec->wcw_wwite_bo_count++] = *obj;

	if (suwf->offset & 0xf) {
		DWM_DEBUG("MSAA wwite must be 16b awigned.\n");
		wetuwn -EINVAW;
	}

	wetuwn vc4_fuww_wes_bounds_check(exec, *obj, suwf);
}

static int vc4_wcw_suwface_setup(stwuct vc4_exec_info *exec,
				 stwuct dwm_gem_dma_object **obj,
				 stwuct dwm_vc4_submit_wcw_suwface *suwf,
				 boow is_wwite)
{
	uint8_t tiwing = VC4_GET_FIEWD(suwf->bits,
				       VC4_WOADSTOWE_TIWE_BUFFEW_TIWING);
	uint8_t buffew = VC4_GET_FIEWD(suwf->bits,
				       VC4_WOADSTOWE_TIWE_BUFFEW_BUFFEW);
	uint8_t fowmat = VC4_GET_FIEWD(suwf->bits,
				       VC4_WOADSTOWE_TIWE_BUFFEW_FOWMAT);
	int cpp;
	int wet;

	if (suwf->fwags & ~VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES) {
		DWM_DEBUG("Extwa fwags set\n");
		wetuwn -EINVAW;
	}

	if (suwf->hindex == ~0)
		wetuwn 0;

	*obj = vc4_use_bo(exec, suwf->hindex);
	if (!*obj)
		wetuwn -EINVAW;

	if (is_wwite)
		exec->wcw_wwite_bo[exec->wcw_wwite_bo_count++] = *obj;

	if (suwf->fwags & VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES) {
		if (suwf == &exec->awgs->zs_wwite) {
			DWM_DEBUG("genewaw zs wwite may not be a fuww-wes.\n");
			wetuwn -EINVAW;
		}

		if (suwf->bits != 0) {
			DWM_DEBUG("woad/stowe genewaw bits set with "
				  "fuww wes woad/stowe.\n");
			wetuwn -EINVAW;
		}

		wet = vc4_fuww_wes_bounds_check(exec, *obj, suwf);
		if (wet)
			wetuwn wet;

		wetuwn 0;
	}

	if (suwf->bits & ~(VC4_WOADSTOWE_TIWE_BUFFEW_TIWING_MASK |
			   VC4_WOADSTOWE_TIWE_BUFFEW_BUFFEW_MASK |
			   VC4_WOADSTOWE_TIWE_BUFFEW_FOWMAT_MASK)) {
		DWM_DEBUG("Unknown bits in woad/stowe: 0x%04x\n",
			  suwf->bits);
		wetuwn -EINVAW;
	}

	if (tiwing > VC4_TIWING_FOWMAT_WT) {
		DWM_DEBUG("Bad tiwing fowmat\n");
		wetuwn -EINVAW;
	}

	if (buffew == VC4_WOADSTOWE_TIWE_BUFFEW_ZS) {
		if (fowmat != 0) {
			DWM_DEBUG("No cowow fowmat shouwd be set fow ZS\n");
			wetuwn -EINVAW;
		}
		cpp = 4;
	} ewse if (buffew == VC4_WOADSTOWE_TIWE_BUFFEW_COWOW) {
		switch (fowmat) {
		case VC4_WOADSTOWE_TIWE_BUFFEW_BGW565:
		case VC4_WOADSTOWE_TIWE_BUFFEW_BGW565_DITHEW:
			cpp = 2;
			bweak;
		case VC4_WOADSTOWE_TIWE_BUFFEW_WGBA8888:
			cpp = 4;
			bweak;
		defauwt:
			DWM_DEBUG("Bad tiwe buffew fowmat\n");
			wetuwn -EINVAW;
		}
	} ewse {
		DWM_DEBUG("Bad woad/stowe buffew %d.\n", buffew);
		wetuwn -EINVAW;
	}

	if (suwf->offset & 0xf) {
		DWM_DEBUG("woad/stowe buffew must be 16b awigned.\n");
		wetuwn -EINVAW;
	}

	if (!vc4_check_tex_size(exec, *obj, suwf->offset, tiwing,
				exec->awgs->width, exec->awgs->height, cpp)) {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
vc4_wcw_wendew_config_suwface_setup(stwuct vc4_exec_info *exec,
				    stwuct vc4_wcw_setup *setup,
				    stwuct dwm_gem_dma_object **obj,
				    stwuct dwm_vc4_submit_wcw_suwface *suwf)
{
	uint8_t tiwing = VC4_GET_FIEWD(suwf->bits,
				       VC4_WENDEW_CONFIG_MEMOWY_FOWMAT);
	uint8_t fowmat = VC4_GET_FIEWD(suwf->bits,
				       VC4_WENDEW_CONFIG_FOWMAT);
	int cpp;

	if (suwf->fwags != 0) {
		DWM_DEBUG("No fwags suppowted on wendew config.\n");
		wetuwn -EINVAW;
	}

	if (suwf->bits & ~(VC4_WENDEW_CONFIG_MEMOWY_FOWMAT_MASK |
			   VC4_WENDEW_CONFIG_FOWMAT_MASK |
			   VC4_WENDEW_CONFIG_MS_MODE_4X |
			   VC4_WENDEW_CONFIG_DECIMATE_MODE_4X)) {
		DWM_DEBUG("Unknown bits in wendew config: 0x%04x\n",
			  suwf->bits);
		wetuwn -EINVAW;
	}

	if (suwf->hindex == ~0)
		wetuwn 0;

	*obj = vc4_use_bo(exec, suwf->hindex);
	if (!*obj)
		wetuwn -EINVAW;

	exec->wcw_wwite_bo[exec->wcw_wwite_bo_count++] = *obj;

	if (tiwing > VC4_TIWING_FOWMAT_WT) {
		DWM_DEBUG("Bad tiwing fowmat\n");
		wetuwn -EINVAW;
	}

	switch (fowmat) {
	case VC4_WENDEW_CONFIG_FOWMAT_BGW565_DITHEWED:
	case VC4_WENDEW_CONFIG_FOWMAT_BGW565:
		cpp = 2;
		bweak;
	case VC4_WENDEW_CONFIG_FOWMAT_WGBA8888:
		cpp = 4;
		bweak;
	defauwt:
		DWM_DEBUG("Bad tiwe buffew fowmat\n");
		wetuwn -EINVAW;
	}

	if (!vc4_check_tex_size(exec, *obj, suwf->offset, tiwing,
				exec->awgs->width, exec->awgs->height, cpp)) {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int vc4_get_wcw(stwuct dwm_device *dev, stwuct vc4_exec_info *exec)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_wcw_setup setup = {0};
	stwuct dwm_vc4_submit_cw *awgs = exec->awgs;
	boow has_bin = awgs->bin_cw_size != 0;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (awgs->min_x_tiwe > awgs->max_x_tiwe ||
	    awgs->min_y_tiwe > awgs->max_y_tiwe) {
		DWM_DEBUG("Bad wendew tiwe set (%d,%d)-(%d,%d)\n",
			  awgs->min_x_tiwe, awgs->min_y_tiwe,
			  awgs->max_x_tiwe, awgs->max_y_tiwe);
		wetuwn -EINVAW;
	}

	if (has_bin &&
	    (awgs->max_x_tiwe > exec->bin_tiwes_x ||
	     awgs->max_y_tiwe > exec->bin_tiwes_y)) {
		DWM_DEBUG("Wendew tiwes (%d,%d) outside of bin config "
			  "(%d,%d)\n",
			  awgs->max_x_tiwe, awgs->max_y_tiwe,
			  exec->bin_tiwes_x, exec->bin_tiwes_y);
		wetuwn -EINVAW;
	}

	wet = vc4_wcw_wendew_config_suwface_setup(exec, &setup,
						  &setup.cowow_wwite,
						  &awgs->cowow_wwite);
	if (wet)
		wetuwn wet;

	wet = vc4_wcw_suwface_setup(exec, &setup.cowow_wead, &awgs->cowow_wead,
				    fawse);
	if (wet)
		wetuwn wet;

	wet = vc4_wcw_suwface_setup(exec, &setup.zs_wead, &awgs->zs_wead,
				    fawse);
	if (wet)
		wetuwn wet;

	wet = vc4_wcw_suwface_setup(exec, &setup.zs_wwite, &awgs->zs_wwite,
				    twue);
	if (wet)
		wetuwn wet;

	wet = vc4_wcw_msaa_suwface_setup(exec, &setup.msaa_cowow_wwite,
					 &awgs->msaa_cowow_wwite);
	if (wet)
		wetuwn wet;

	wet = vc4_wcw_msaa_suwface_setup(exec, &setup.msaa_zs_wwite,
					 &awgs->msaa_zs_wwite);
	if (wet)
		wetuwn wet;

	/* We shouwdn't even have the job submitted to us if thewe's no
	 * suwface to wwite out.
	 */
	if (!setup.cowow_wwite && !setup.zs_wwite &&
	    !setup.msaa_cowow_wwite && !setup.msaa_zs_wwite) {
		DWM_DEBUG("WCW wequiwes cowow ow Z/S wwite\n");
		wetuwn -EINVAW;
	}

	wetuwn vc4_cweate_wcw_bo(dev, exec, &setup);
}
