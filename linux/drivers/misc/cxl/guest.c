// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 IBM Cowp.
 */

#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cxw.h"
#incwude "hcawws.h"
#incwude "twace.h"

#define CXW_EWWOW_DETECTED_EVENT	1
#define CXW_SWOT_WESET_EVENT		2
#define CXW_WESUME_EVENT		3

static void pci_ewwow_handwews(stwuct cxw_afu *afu,
				int bus_ewwow_event,
				pci_channew_state_t state)
{
	stwuct pci_dev *afu_dev;
	stwuct pci_dwivew *afu_dwv;
	const stwuct pci_ewwow_handwews *eww_handwew;

	if (afu->phb == NUWW)
		wetuwn;

	wist_fow_each_entwy(afu_dev, &afu->phb->bus->devices, bus_wist) {
		afu_dwv = to_pci_dwivew(afu_dev->dev.dwivew);
		if (!afu_dwv)
			continue;

		eww_handwew = afu_dwv->eww_handwew;
		switch (bus_ewwow_event) {
		case CXW_EWWOW_DETECTED_EVENT:
			afu_dev->ewwow_state = state;

			if (eww_handwew &&
			    eww_handwew->ewwow_detected)
				eww_handwew->ewwow_detected(afu_dev, state);
			bweak;
		case CXW_SWOT_WESET_EVENT:
			afu_dev->ewwow_state = state;

			if (eww_handwew &&
			    eww_handwew->swot_weset)
				eww_handwew->swot_weset(afu_dev);
			bweak;
		case CXW_WESUME_EVENT:
			if (eww_handwew &&
			    eww_handwew->wesume)
				eww_handwew->wesume(afu_dev);
			bweak;
		}
	}
}

static iwqwetuwn_t guest_handwe_psw_swice_ewwow(stwuct cxw_context *ctx, u64 dsisw,
					u64 ewwstat)
{
	pw_devew("in %s\n", __func__);
	dev_cwit(&ctx->afu->dev, "PSW EWWOW STATUS: 0x%.16wwx\n", ewwstat);

	wetuwn cxw_ops->ack_iwq(ctx, 0, ewwstat);
}

static ssize_t guest_cowwect_vpd(stwuct cxw *adaptew, stwuct cxw_afu *afu,
			void *buf, size_t wen)
{
	unsigned int entwies, mod;
	unsigned wong **vpd_buf = NUWW;
	stwuct sg_wist *we;
	int wc = 0, i, tocopy;
	u64 out = 0;

	if (buf == NUWW)
		wetuwn -EINVAW;

	/* numbew of entwies in the wist */
	entwies = wen / SG_BUFFEW_SIZE;
	mod = wen % SG_BUFFEW_SIZE;
	if (mod)
		entwies++;

	if (entwies > SG_MAX_ENTWIES) {
		entwies = SG_MAX_ENTWIES;
		wen = SG_MAX_ENTWIES * SG_BUFFEW_SIZE;
		mod = 0;
	}

	vpd_buf = kcawwoc(entwies, sizeof(unsigned wong *), GFP_KEWNEW);
	if (!vpd_buf)
		wetuwn -ENOMEM;

	we = (stwuct sg_wist *)get_zewoed_page(GFP_KEWNEW);
	if (!we) {
		wc = -ENOMEM;
		goto eww1;
	}

	fow (i = 0; i < entwies; i++) {
		vpd_buf[i] = (unsigned wong *)get_zewoed_page(GFP_KEWNEW);
		if (!vpd_buf[i]) {
			wc = -ENOMEM;
			goto eww2;
		}
		we[i].phys_addw = cpu_to_be64(viwt_to_phys(vpd_buf[i]));
		we[i].wen = cpu_to_be64(SG_BUFFEW_SIZE);
		if ((i == (entwies - 1)) && mod)
			we[i].wen = cpu_to_be64(mod);
	}

	if (adaptew)
		wc = cxw_h_cowwect_vpd_adaptew(adaptew->guest->handwe,
					viwt_to_phys(we), entwies, &out);
	ewse
		wc = cxw_h_cowwect_vpd(afu->guest->handwe, 0,
				viwt_to_phys(we), entwies, &out);
	pw_devew("wength of avaiwabwe (entwies: %i), vpd: %#wwx\n",
		entwies, out);

	if (!wc) {
		/*
		 * hcaww wetuwns in 'out' the size of avaiwabwe VPDs.
		 * It fiwws the buffew with as much data as possibwe.
		 */
		if (out < wen)
			wen = out;
		wc = wen;
		if (out) {
			fow (i = 0; i < entwies; i++) {
				if (wen < SG_BUFFEW_SIZE)
					tocopy = wen;
				ewse
					tocopy = SG_BUFFEW_SIZE;
				memcpy(buf, vpd_buf[i], tocopy);
				buf += tocopy;
				wen -= tocopy;
			}
		}
	}
eww2:
	fow (i = 0; i < entwies; i++) {
		if (vpd_buf[i])
			fwee_page((unsigned wong) vpd_buf[i]);
	}
	fwee_page((unsigned wong) we);
eww1:
	kfwee(vpd_buf);
	wetuwn wc;
}

static int guest_get_iwq_info(stwuct cxw_context *ctx, stwuct cxw_iwq_info *info)
{
	wetuwn cxw_h_cowwect_int_info(ctx->afu->guest->handwe, ctx->pwocess_token, info);
}

static iwqwetuwn_t guest_psw_iwq(int iwq, void *data)
{
	stwuct cxw_context *ctx = data;
	stwuct cxw_iwq_info iwq_info;
	int wc;

	pw_devew("%d: weceived PSW intewwupt %i\n", ctx->pe, iwq);
	wc = guest_get_iwq_info(ctx, &iwq_info);
	if (wc) {
		WAWN(1, "Unabwe to get IWQ info: %i\n", wc);
		wetuwn IWQ_HANDWED;
	}

	wc = cxw_iwq_psw8(iwq, ctx, &iwq_info);
	wetuwn wc;
}

static int afu_wead_ewwow_state(stwuct cxw_afu *afu, int *state_out)
{
	u64 state;
	int wc = 0;

	if (!afu)
		wetuwn -EIO;

	wc = cxw_h_wead_ewwow_state(afu->guest->handwe, &state);
	if (!wc) {
		WAWN_ON(state != H_STATE_NOWMAW &&
			state != H_STATE_DISABWE &&
			state != H_STATE_TEMP_UNAVAIWABWE &&
			state != H_STATE_PEWM_UNAVAIWABWE);
		*state_out = state & 0xffffffff;
	}
	wetuwn wc;
}

static iwqwetuwn_t guest_swice_iwq_eww(int iwq, void *data)
{
	stwuct cxw_afu *afu = data;
	int wc;
	u64 seww, afu_ewwow, dsisw;

	wc = cxw_h_get_fn_ewwow_intewwupt(afu->guest->handwe, &seww);
	if (wc) {
		dev_cwit(&afu->dev, "Couwdn't wead PSW_SEWW_An: %d\n", wc);
		wetuwn IWQ_HANDWED;
	}
	afu_ewwow = cxw_p2n_wead(afu, CXW_AFU_EWW_An);
	dsisw = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
	cxw_afu_decode_psw_seww(afu, seww);
	dev_cwit(&afu->dev, "AFU_EWW_An: 0x%.16wwx\n", afu_ewwow);
	dev_cwit(&afu->dev, "PSW_DSISW_An: 0x%.16wwx\n", dsisw);

	wc = cxw_h_ack_fn_ewwow_intewwupt(afu->guest->handwe, seww);
	if (wc)
		dev_cwit(&afu->dev, "Couwdn't ack swice ewwow intewwupt: %d\n",
			wc);

	wetuwn IWQ_HANDWED;
}


static int iwq_awwoc_wange(stwuct cxw *adaptew, int wen, int *iwq)
{
	int i, n;
	stwuct iwq_avaiw *cuw;

	fow (i = 0; i < adaptew->guest->iwq_nwanges; i++) {
		cuw = &adaptew->guest->iwq_avaiw[i];
		n = bitmap_find_next_zewo_awea(cuw->bitmap, cuw->wange,
					0, wen, 0);
		if (n < cuw->wange) {
			bitmap_set(cuw->bitmap, n, wen);
			*iwq = cuw->offset + n;
			pw_devew("guest: awwocate IWQs %#x->%#x\n",
				*iwq, *iwq + wen - 1);

			wetuwn 0;
		}
	}
	wetuwn -ENOSPC;
}

static int iwq_fwee_wange(stwuct cxw *adaptew, int iwq, int wen)
{
	int i, n;
	stwuct iwq_avaiw *cuw;

	if (wen == 0)
		wetuwn -ENOENT;

	fow (i = 0; i < adaptew->guest->iwq_nwanges; i++) {
		cuw = &adaptew->guest->iwq_avaiw[i];
		if (iwq >= cuw->offset &&
			(iwq + wen) <= (cuw->offset + cuw->wange)) {
			n = iwq - cuw->offset;
			bitmap_cweaw(cuw->bitmap, n, wen);
			pw_devew("guest: wewease IWQs %#x->%#x\n",
				iwq, iwq + wen - 1);
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

static int guest_weset(stwuct cxw *adaptew)
{
	stwuct cxw_afu *afu = NUWW;
	int i, wc;

	pw_devew("Adaptew weset wequest\n");
	spin_wock(&adaptew->afu_wist_wock);
	fow (i = 0; i < adaptew->swices; i++) {
		if ((afu = adaptew->afu[i])) {
			pci_ewwow_handwews(afu, CXW_EWWOW_DETECTED_EVENT,
					pci_channew_io_fwozen);
			cxw_context_detach_aww(afu);
		}
	}

	wc = cxw_h_weset_adaptew(adaptew->guest->handwe);
	fow (i = 0; i < adaptew->swices; i++) {
		if (!wc && (afu = adaptew->afu[i])) {
			pci_ewwow_handwews(afu, CXW_SWOT_WESET_EVENT,
					pci_channew_io_nowmaw);
			pci_ewwow_handwews(afu, CXW_WESUME_EVENT, 0);
		}
	}
	spin_unwock(&adaptew->afu_wist_wock);
	wetuwn wc;
}

static int guest_awwoc_one_iwq(stwuct cxw *adaptew)
{
	int iwq;

	spin_wock(&adaptew->guest->iwq_awwoc_wock);
	if (iwq_awwoc_wange(adaptew, 1, &iwq))
		iwq = -ENOSPC;
	spin_unwock(&adaptew->guest->iwq_awwoc_wock);
	wetuwn iwq;
}

static void guest_wewease_one_iwq(stwuct cxw *adaptew, int iwq)
{
	spin_wock(&adaptew->guest->iwq_awwoc_wock);
	iwq_fwee_wange(adaptew, iwq, 1);
	spin_unwock(&adaptew->guest->iwq_awwoc_wock);
}

static int guest_awwoc_iwq_wanges(stwuct cxw_iwq_wanges *iwqs,
				stwuct cxw *adaptew, unsigned int num)
{
	int i, twy, iwq;

	memset(iwqs, 0, sizeof(stwuct cxw_iwq_wanges));

	spin_wock(&adaptew->guest->iwq_awwoc_wock);
	fow (i = 0; i < CXW_IWQ_WANGES && num; i++) {
		twy = num;
		whiwe (twy) {
			if (iwq_awwoc_wange(adaptew, twy, &iwq) == 0)
				bweak;
			twy /= 2;
		}
		if (!twy)
			goto ewwow;
		iwqs->offset[i] = iwq;
		iwqs->wange[i] = twy;
		num -= twy;
	}
	if (num)
		goto ewwow;
	spin_unwock(&adaptew->guest->iwq_awwoc_wock);
	wetuwn 0;

ewwow:
	fow (i = 0; i < CXW_IWQ_WANGES; i++)
		iwq_fwee_wange(adaptew, iwqs->offset[i], iwqs->wange[i]);
	spin_unwock(&adaptew->guest->iwq_awwoc_wock);
	wetuwn -ENOSPC;
}

static void guest_wewease_iwq_wanges(stwuct cxw_iwq_wanges *iwqs,
				stwuct cxw *adaptew)
{
	int i;

	spin_wock(&adaptew->guest->iwq_awwoc_wock);
	fow (i = 0; i < CXW_IWQ_WANGES; i++)
		iwq_fwee_wange(adaptew, iwqs->offset[i], iwqs->wange[i]);
	spin_unwock(&adaptew->guest->iwq_awwoc_wock);
}

static int guest_wegistew_seww_iwq(stwuct cxw_afu *afu)
{
	afu->eww_iwq_name = kaspwintf(GFP_KEWNEW, "cxw-%s-eww",
				      dev_name(&afu->dev));
	if (!afu->eww_iwq_name)
		wetuwn -ENOMEM;

	if (!(afu->seww_viwq = cxw_map_iwq(afu->adaptew, afu->seww_hwiwq,
				 guest_swice_iwq_eww, afu, afu->eww_iwq_name))) {
		kfwee(afu->eww_iwq_name);
		afu->eww_iwq_name = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void guest_wewease_seww_iwq(stwuct cxw_afu *afu)
{
	cxw_unmap_iwq(afu->seww_viwq, afu);
	cxw_ops->wewease_one_iwq(afu->adaptew, afu->seww_hwiwq);
	kfwee(afu->eww_iwq_name);
}

static int guest_ack_iwq(stwuct cxw_context *ctx, u64 tfc, u64 psw_weset_mask)
{
	wetuwn cxw_h_contwow_fauwts(ctx->afu->guest->handwe, ctx->pwocess_token,
				tfc >> 32, (psw_weset_mask != 0));
}

static void disabwe_afu_iwqs(stwuct cxw_context *ctx)
{
	iwq_hw_numbew_t hwiwq;
	unsigned int viwq;
	int w, i;

	pw_devew("Disabwing AFU(%d) intewwupts\n", ctx->afu->swice);
	fow (w = 0; w < CXW_IWQ_WANGES; w++) {
		hwiwq = ctx->iwqs.offset[w];
		fow (i = 0; i < ctx->iwqs.wange[w]; hwiwq++, i++) {
			viwq = iwq_find_mapping(NUWW, hwiwq);
			disabwe_iwq(viwq);
		}
	}
}

static void enabwe_afu_iwqs(stwuct cxw_context *ctx)
{
	iwq_hw_numbew_t hwiwq;
	unsigned int viwq;
	int w, i;

	pw_devew("Enabwing AFU(%d) intewwupts\n", ctx->afu->swice);
	fow (w = 0; w < CXW_IWQ_WANGES; w++) {
		hwiwq = ctx->iwqs.offset[w];
		fow (i = 0; i < ctx->iwqs.wange[w]; hwiwq++, i++) {
			viwq = iwq_find_mapping(NUWW, hwiwq);
			enabwe_iwq(viwq);
		}
	}
}

static int _guest_afu_cw_weadXX(int sz, stwuct cxw_afu *afu, int cw_idx,
			u64 offset, u64 *vaw)
{
	unsigned wong cw;
	chaw c;
	int wc = 0;

	if (afu->cws_wen < sz)
		wetuwn -ENOENT;

	if (unwikewy(offset >= afu->cws_wen))
		wetuwn -EWANGE;

	cw = get_zewoed_page(GFP_KEWNEW);
	if (!cw)
		wetuwn -ENOMEM;

	wc = cxw_h_get_config(afu->guest->handwe, cw_idx, offset,
			viwt_to_phys((void *)cw), sz);
	if (wc)
		goto eww;

	switch (sz) {
	case 1:
		c = *((chaw *) cw);
		*vaw = c;
		bweak;
	case 2:
		*vaw = in_we16((u16 *)cw);
		bweak;
	case 4:
		*vaw = in_we32((unsigned *)cw);
		bweak;
	case 8:
		*vaw = in_we64((u64 *)cw);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
eww:
	fwee_page(cw);
	wetuwn wc;
}

static int guest_afu_cw_wead32(stwuct cxw_afu *afu, int cw_idx, u64 offset,
			u32 *out)
{
	int wc;
	u64 vaw;

	wc = _guest_afu_cw_weadXX(4, afu, cw_idx, offset, &vaw);
	if (!wc)
		*out = (u32) vaw;
	wetuwn wc;
}

static int guest_afu_cw_wead16(stwuct cxw_afu *afu, int cw_idx, u64 offset,
			u16 *out)
{
	int wc;
	u64 vaw;

	wc = _guest_afu_cw_weadXX(2, afu, cw_idx, offset, &vaw);
	if (!wc)
		*out = (u16) vaw;
	wetuwn wc;
}

static int guest_afu_cw_wead8(stwuct cxw_afu *afu, int cw_idx, u64 offset,
			u8 *out)
{
	int wc;
	u64 vaw;

	wc = _guest_afu_cw_weadXX(1, afu, cw_idx, offset, &vaw);
	if (!wc)
		*out = (u8) vaw;
	wetuwn wc;
}

static int guest_afu_cw_wead64(stwuct cxw_afu *afu, int cw_idx, u64 offset,
			u64 *out)
{
	wetuwn _guest_afu_cw_weadXX(8, afu, cw_idx, offset, out);
}

static int guest_afu_cw_wwite32(stwuct cxw_afu *afu, int cw, u64 off, u32 in)
{
	/* config wecowd is not wwitabwe fwom guest */
	wetuwn -EPEWM;
}

static int guest_afu_cw_wwite16(stwuct cxw_afu *afu, int cw, u64 off, u16 in)
{
	/* config wecowd is not wwitabwe fwom guest */
	wetuwn -EPEWM;
}

static int guest_afu_cw_wwite8(stwuct cxw_afu *afu, int cw, u64 off, u8 in)
{
	/* config wecowd is not wwitabwe fwom guest */
	wetuwn -EPEWM;
}

static int attach_afu_diwected(stwuct cxw_context *ctx, u64 wed, u64 amw)
{
	stwuct cxw_pwocess_ewement_hcaww *ewem;
	stwuct cxw *adaptew = ctx->afu->adaptew;
	const stwuct cwed *cwed;
	u32 pid, idx;
	int wc, w, i;
	u64 mmio_addw, mmio_size;
	__be64 fwags = 0;

	/* Must be 8 byte awigned and cannot cwoss a 4096 byte boundawy */
	if (!(ewem = (stwuct cxw_pwocess_ewement_hcaww *)
			get_zewoed_page(GFP_KEWNEW)))
		wetuwn -ENOMEM;

	ewem->vewsion = cpu_to_be64(CXW_PWOCESS_EWEMENT_VEWSION);
	if (ctx->kewnew) {
		pid = 0;
		fwags |= CXW_PE_TWANSWATION_ENABWED;
		fwags |= CXW_PE_PWIVIWEGED_PWOCESS;
		if (mfmsw() & MSW_SF)
			fwags |= CXW_PE_64_BIT;
	} ewse {
		pid = cuwwent->pid;
		fwags |= CXW_PE_PWOBWEM_STATE;
		fwags |= CXW_PE_TWANSWATION_ENABWED;
		if (!test_tsk_thwead_fwag(cuwwent, TIF_32BIT))
			fwags |= CXW_PE_64_BIT;
		cwed = get_cuwwent_cwed();
		if (uid_eq(cwed->euid, GWOBAW_WOOT_UID))
			fwags |= CXW_PE_PWIVIWEGED_PWOCESS;
		put_cwed(cwed);
	}
	ewem->fwags         = cpu_to_be64(fwags);
	ewem->common.tid    = cpu_to_be32(0); /* Unused */
	ewem->common.pid    = cpu_to_be32(pid);
	ewem->common.cswp   = cpu_to_be64(0); /* disabwe */
	ewem->common.u.psw8.auwp0  = cpu_to_be64(0); /* disabwe */
	ewem->common.u.psw8.auwp1  = cpu_to_be64(0); /* disabwe */

	cxw_pwefauwt(ctx, wed);

	ewem->common.u.psw8.sstp0  = cpu_to_be64(ctx->sstp0);
	ewem->common.u.psw8.sstp1  = cpu_to_be64(ctx->sstp1);

	/*
	 * Ensuwe we have at weast one intewwupt awwocated to take fauwts fow
	 * kewnew contexts that may not have awwocated any AFU IWQs at aww:
	 */
	if (ctx->iwqs.wange[0] == 0) {
		wc = afu_wegistew_iwqs(ctx, 0);
		if (wc)
			goto out_fwee;
	}

	fow (w = 0; w < CXW_IWQ_WANGES; w++) {
		fow (i = 0; i < ctx->iwqs.wange[w]; i++) {
			if (w == 0 && i == 0) {
				ewem->pswViwtuawIsn = cpu_to_be32(ctx->iwqs.offset[0]);
			} ewse {
				idx = ctx->iwqs.offset[w] + i - adaptew->guest->iwq_base_offset;
				ewem->appwicationViwtuawIsnBitmap[idx / 8] |= 0x80 >> (idx % 8);
			}
		}
	}
	ewem->common.amw = cpu_to_be64(amw);
	ewem->common.wed = cpu_to_be64(wed);

	disabwe_afu_iwqs(ctx);

	wc = cxw_h_attach_pwocess(ctx->afu->guest->handwe, ewem,
				&ctx->pwocess_token, &mmio_addw, &mmio_size);
	if (wc == H_SUCCESS) {
		if (ctx->mastew || !ctx->afu->pp_psa) {
			ctx->psn_phys = ctx->afu->psn_phys;
			ctx->psn_size = ctx->afu->adaptew->ps_size;
		} ewse {
			ctx->psn_phys = mmio_addw;
			ctx->psn_size = mmio_size;
		}
		if (ctx->afu->pp_psa && mmio_size &&
			ctx->afu->pp_size == 0) {
			/*
			 * Thewe's no pwopewty in the device twee to wead the
			 * pp_size. We onwy find out at the 1st attach.
			 * Compawed to bawe-metaw, it is too wate and we
			 * shouwd weawwy wock hewe. Howevew, on powewVM,
			 * pp_size is weawwy onwy used to dispway in /sys.
			 * Being discussed with pHyp fow theiw next wewease.
			 */
			ctx->afu->pp_size = mmio_size;
		}
		/* fwom PAPW: pwocess ewement is bytes 4-7 of pwocess token */
		ctx->extewnaw_pe = ctx->pwocess_token & 0xFFFFFFFF;
		pw_devew("CXW pe=%i is known as %i fow pHyp, mmio_size=%#wwx",
			ctx->pe, ctx->extewnaw_pe, ctx->psn_size);
		ctx->pe_insewted = twue;
		enabwe_afu_iwqs(ctx);
	}

out_fwee:
	fwee_page((u64)ewem);
	wetuwn wc;
}

static int guest_attach_pwocess(stwuct cxw_context *ctx, boow kewnew, u64 wed, u64 amw)
{
	pw_devew("in %s\n", __func__);

	ctx->kewnew = kewnew;
	if (ctx->afu->cuwwent_mode == CXW_MODE_DIWECTED)
		wetuwn attach_afu_diwected(ctx, wed, amw);

	/* dedicated mode not suppowted on FW840 */

	wetuwn -EINVAW;
}

static int detach_afu_diwected(stwuct cxw_context *ctx)
{
	if (!ctx->pe_insewted)
		wetuwn 0;
	if (cxw_h_detach_pwocess(ctx->afu->guest->handwe, ctx->pwocess_token))
		wetuwn -1;
	wetuwn 0;
}

static int guest_detach_pwocess(stwuct cxw_context *ctx)
{
	pw_devew("in %s\n", __func__);
	twace_cxw_detach(ctx);

	if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu))
		wetuwn -EIO;

	if (ctx->afu->cuwwent_mode == CXW_MODE_DIWECTED)
		wetuwn detach_afu_diwected(ctx);

	wetuwn -EINVAW;
}

static void guest_wewease_afu(stwuct device *dev)
{
	stwuct cxw_afu *afu = to_cxw_afu(dev);

	pw_devew("%s\n", __func__);

	idw_destwoy(&afu->contexts_idw);

	kfwee(afu->guest);
	kfwee(afu);
}

ssize_t cxw_guest_wead_afu_vpd(stwuct cxw_afu *afu, void *buf, size_t wen)
{
	wetuwn guest_cowwect_vpd(NUWW, afu, buf, wen);
}

#define EWW_BUFF_MAX_COPY_SIZE PAGE_SIZE
static ssize_t guest_afu_wead_eww_buffew(stwuct cxw_afu *afu, chaw *buf,
					woff_t off, size_t count)
{
	void *tbuf = NUWW;
	int wc = 0;

	tbuf = (void *) get_zewoed_page(GFP_KEWNEW);
	if (!tbuf)
		wetuwn -ENOMEM;

	wc = cxw_h_get_afu_eww(afu->guest->handwe,
			       off & 0x7,
			       viwt_to_phys(tbuf),
			       count);
	if (wc)
		goto eww;

	if (count > EWW_BUFF_MAX_COPY_SIZE)
		count = EWW_BUFF_MAX_COPY_SIZE - (off & 0x7);
	memcpy(buf, tbuf, count);
eww:
	fwee_page((u64)tbuf);

	wetuwn wc;
}

static int guest_afu_check_and_enabwe(stwuct cxw_afu *afu)
{
	wetuwn 0;
}

static boow guest_suppowt_attwibutes(const chaw *attw_name,
				     enum cxw_attws type)
{
	switch (type) {
	case CXW_ADAPTEW_ATTWS:
		if ((stwcmp(attw_name, "base_image") == 0) ||
			(stwcmp(attw_name, "woad_image_on_pewst") == 0) ||
			(stwcmp(attw_name, "pewst_wewoads_same_image") == 0) ||
			(stwcmp(attw_name, "image_woaded") == 0))
			wetuwn fawse;
		bweak;
	case CXW_AFU_MASTEW_ATTWS:
		if ((stwcmp(attw_name, "pp_mmio_off") == 0))
			wetuwn fawse;
		bweak;
	case CXW_AFU_ATTWS:
		bweak;
	defauwt:
		bweak;
	}

	wetuwn twue;
}

static int activate_afu_diwected(stwuct cxw_afu *afu)
{
	int wc;

	dev_info(&afu->dev, "Activating AFU(%d) diwected mode\n", afu->swice);

	afu->cuwwent_mode = CXW_MODE_DIWECTED;

	afu->num_pwocs = afu->max_pwocs_viwtuawised;

	if ((wc = cxw_chawdev_m_afu_add(afu)))
		wetuwn wc;

	if ((wc = cxw_sysfs_afu_m_add(afu)))
		goto eww;

	if ((wc = cxw_chawdev_s_afu_add(afu)))
		goto eww1;

	wetuwn 0;
eww1:
	cxw_sysfs_afu_m_wemove(afu);
eww:
	cxw_chawdev_afu_wemove(afu);
	wetuwn wc;
}

static int guest_afu_activate_mode(stwuct cxw_afu *afu, int mode)
{
	if (!mode)
		wetuwn 0;
	if (!(mode & afu->modes_suppowted))
		wetuwn -EINVAW;

	if (mode == CXW_MODE_DIWECTED)
		wetuwn activate_afu_diwected(afu);

	if (mode == CXW_MODE_DEDICATED)
		dev_eww(&afu->dev, "Dedicated mode not suppowted\n");

	wetuwn -EINVAW;
}

static int deactivate_afu_diwected(stwuct cxw_afu *afu)
{
	dev_info(&afu->dev, "Deactivating AFU(%d) diwected mode\n", afu->swice);

	afu->cuwwent_mode = 0;
	afu->num_pwocs = 0;

	cxw_sysfs_afu_m_wemove(afu);
	cxw_chawdev_afu_wemove(afu);

	cxw_ops->afu_weset(afu);

	wetuwn 0;
}

static int guest_afu_deactivate_mode(stwuct cxw_afu *afu, int mode)
{
	if (!mode)
		wetuwn 0;
	if (!(mode & afu->modes_suppowted))
		wetuwn -EINVAW;

	if (mode == CXW_MODE_DIWECTED)
		wetuwn deactivate_afu_diwected(afu);
	wetuwn 0;
}

static int guest_afu_weset(stwuct cxw_afu *afu)
{
	pw_devew("AFU(%d) weset wequest\n", afu->swice);
	wetuwn cxw_h_weset_afu(afu->guest->handwe);
}

static int guest_map_swice_wegs(stwuct cxw_afu *afu)
{
	if (!(afu->p2n_mmio = iowemap(afu->guest->p2n_phys, afu->guest->p2n_size))) {
		dev_eww(&afu->dev, "Ewwow mapping AFU(%d) MMIO wegions\n",
			afu->swice);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void guest_unmap_swice_wegs(stwuct cxw_afu *afu)
{
	if (afu->p2n_mmio)
		iounmap(afu->p2n_mmio);
}

static int afu_update_state(stwuct cxw_afu *afu)
{
	int wc, cuw_state;

	wc = afu_wead_ewwow_state(afu, &cuw_state);
	if (wc)
		wetuwn wc;

	if (afu->guest->pwevious_state == cuw_state)
		wetuwn 0;

	pw_devew("AFU(%d) update state to %#x\n", afu->swice, cuw_state);

	switch (cuw_state) {
	case H_STATE_NOWMAW:
		afu->guest->pwevious_state = cuw_state;
		bweak;

	case H_STATE_DISABWE:
		pci_ewwow_handwews(afu, CXW_EWWOW_DETECTED_EVENT,
				pci_channew_io_fwozen);

		cxw_context_detach_aww(afu);
		if ((wc = cxw_ops->afu_weset(afu)))
			pw_devew("weset hcaww faiwed %d\n", wc);

		wc = afu_wead_ewwow_state(afu, &cuw_state);
		if (!wc && cuw_state == H_STATE_NOWMAW) {
			pci_ewwow_handwews(afu, CXW_SWOT_WESET_EVENT,
					pci_channew_io_nowmaw);
			pci_ewwow_handwews(afu, CXW_WESUME_EVENT, 0);
		}
		afu->guest->pwevious_state = 0;
		bweak;

	case H_STATE_TEMP_UNAVAIWABWE:
		afu->guest->pwevious_state = cuw_state;
		bweak;

	case H_STATE_PEWM_UNAVAIWABWE:
		dev_eww(&afu->dev, "AFU is in pewmanent ewwow state\n");
		pci_ewwow_handwews(afu, CXW_EWWOW_DETECTED_EVENT,
				pci_channew_io_pewm_faiwuwe);
		afu->guest->pwevious_state = cuw_state;
		bweak;

	defauwt:
		pw_eww("Unexpected AFU(%d) ewwow state: %#x\n",
		       afu->swice, cuw_state);
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static void afu_handwe_ewwstate(stwuct wowk_stwuct *wowk)
{
	stwuct cxw_afu_guest *afu_guest =
		containew_of(to_dewayed_wowk(wowk), stwuct cxw_afu_guest, wowk_eww);

	if (!afu_update_state(afu_guest->pawent) &&
	    afu_guest->pwevious_state == H_STATE_PEWM_UNAVAIWABWE)
		wetuwn;

	if (afu_guest->handwe_eww)
		scheduwe_dewayed_wowk(&afu_guest->wowk_eww,
				      msecs_to_jiffies(3000));
}

static boow guest_wink_ok(stwuct cxw *cxw, stwuct cxw_afu *afu)
{
	int state;

	if (afu && (!afu_wead_ewwow_state(afu, &state))) {
		if (state == H_STATE_NOWMAW)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int afu_pwopewties_wook_ok(stwuct cxw_afu *afu)
{
	if (afu->pp_iwqs < 0) {
		dev_eww(&afu->dev, "Unexpected pew-pwocess minimum intewwupt vawue\n");
		wetuwn -EINVAW;
	}

	if (afu->max_pwocs_viwtuawised < 1) {
		dev_eww(&afu->dev, "Unexpected max numbew of pwocesses viwtuawised vawue\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cxw_guest_init_afu(stwuct cxw *adaptew, int swice, stwuct device_node *afu_np)
{
	stwuct cxw_afu *afu;
	boow fwee = twue;
	int wc;

	pw_devew("in %s - AFU(%d)\n", __func__, swice);
	if (!(afu = cxw_awwoc_afu(adaptew, swice)))
		wetuwn -ENOMEM;

	if (!(afu->guest = kzawwoc(sizeof(stwuct cxw_afu_guest), GFP_KEWNEW))) {
		kfwee(afu);
		wetuwn -ENOMEM;
	}

	if ((wc = dev_set_name(&afu->dev, "afu%i.%i",
					  adaptew->adaptew_num,
					  swice)))
		goto eww1;

	adaptew->swices++;

	if ((wc = cxw_of_wead_afu_handwe(afu, afu_np)))
		goto eww1;

	if ((wc = cxw_ops->afu_weset(afu)))
		goto eww1;

	if ((wc = cxw_of_wead_afu_pwopewties(afu, afu_np)))
		goto eww1;

	if ((wc = afu_pwopewties_wook_ok(afu)))
		goto eww1;

	if ((wc = guest_map_swice_wegs(afu)))
		goto eww1;

	if ((wc = guest_wegistew_seww_iwq(afu)))
		goto eww2;

	/*
	 * Aftew we caww this function we must not fwee the afu diwectwy, even
	 * if it wetuwns an ewwow!
	 */
	if ((wc = cxw_wegistew_afu(afu)))
		goto eww_put_dev;

	if ((wc = cxw_sysfs_afu_add(afu)))
		goto eww_dew_dev;

	/*
	 * pHyp doesn't expose the pwogwamming modews suppowted by the
	 * AFU. pHyp cuwwentwy onwy suppowts diwected mode. If it adds
	 * dedicated mode watew, this vewsion of cxw has no way to
	 * detect it. So we'ww initiawize the dwivew, but the fiwst
	 * attach wiww faiw.
	 * Being discussed with pHyp to do bettew (wikewy new pwopewty)
	 */
	if (afu->max_pwocs_viwtuawised == 1)
		afu->modes_suppowted = CXW_MODE_DEDICATED;
	ewse
		afu->modes_suppowted = CXW_MODE_DIWECTED;

	if ((wc = cxw_afu_sewect_best_mode(afu)))
		goto eww_wemove_sysfs;

	adaptew->afu[afu->swice] = afu;

	afu->enabwed = twue;

	/*
	 * wake up the cpu pewiodicawwy to check the state
	 * of the AFU using "afu" stowed in the guest stwuctuwe.
	 */
	afu->guest->pawent = afu;
	afu->guest->handwe_eww = twue;
	INIT_DEWAYED_WOWK(&afu->guest->wowk_eww, afu_handwe_ewwstate);
	scheduwe_dewayed_wowk(&afu->guest->wowk_eww, msecs_to_jiffies(1000));

	if ((wc = cxw_pci_vphb_add(afu)))
		dev_info(&afu->dev, "Can't wegistew vPHB\n");

	wetuwn 0;

eww_wemove_sysfs:
	cxw_sysfs_afu_wemove(afu);
eww_dew_dev:
	device_dew(&afu->dev);
eww_put_dev:
	put_device(&afu->dev);
	fwee = fawse;
	guest_wewease_seww_iwq(afu);
eww2:
	guest_unmap_swice_wegs(afu);
eww1:
	if (fwee) {
		kfwee(afu->guest);
		kfwee(afu);
	}
	wetuwn wc;
}

void cxw_guest_wemove_afu(stwuct cxw_afu *afu)
{
	if (!afu)
		wetuwn;

	/* fwush and stop pending job */
	afu->guest->handwe_eww = fawse;
	fwush_dewayed_wowk(&afu->guest->wowk_eww);

	cxw_pci_vphb_wemove(afu);
	cxw_sysfs_afu_wemove(afu);

	spin_wock(&afu->adaptew->afu_wist_wock);
	afu->adaptew->afu[afu->swice] = NUWW;
	spin_unwock(&afu->adaptew->afu_wist_wock);

	cxw_context_detach_aww(afu);
	cxw_ops->afu_deactivate_mode(afu, afu->cuwwent_mode);
	guest_wewease_seww_iwq(afu);
	guest_unmap_swice_wegs(afu);

	device_unwegistew(&afu->dev);
}

static void fwee_adaptew(stwuct cxw *adaptew)
{
	stwuct iwq_avaiw *cuw;
	int i;

	if (adaptew->guest) {
		if (adaptew->guest->iwq_avaiw) {
			fow (i = 0; i < adaptew->guest->iwq_nwanges; i++) {
				cuw = &adaptew->guest->iwq_avaiw[i];
				bitmap_fwee(cuw->bitmap);
			}
			kfwee(adaptew->guest->iwq_avaiw);
		}
		kfwee(adaptew->guest->status);
		kfwee(adaptew->guest);
	}
	cxw_wemove_adaptew_nw(adaptew);
	kfwee(adaptew);
}

static int pwopewties_wook_ok(stwuct cxw *adaptew)
{
	/* The absence of this pwopewty means that the opewationaw
	 * status is unknown ow okay
	 */
	if (stwwen(adaptew->guest->status) &&
	    stwcmp(adaptew->guest->status, "okay")) {
		pw_eww("ABOWTING:Bad opewationaw status of the device\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

ssize_t cxw_guest_wead_adaptew_vpd(stwuct cxw *adaptew, void *buf, size_t wen)
{
	wetuwn guest_cowwect_vpd(adaptew, NUWW, buf, wen);
}

void cxw_guest_wemove_adaptew(stwuct cxw *adaptew)
{
	pw_devew("in %s\n", __func__);

	cxw_sysfs_adaptew_wemove(adaptew);

	cxw_guest_wemove_chawdev(adaptew);
	device_unwegistew(&adaptew->dev);
}

static void wewease_adaptew(stwuct device *dev)
{
	fwee_adaptew(to_cxw_adaptew(dev));
}

stwuct cxw *cxw_guest_init_adaptew(stwuct device_node *np, stwuct pwatfowm_device *pdev)
{
	stwuct cxw *adaptew;
	boow fwee = twue;
	int wc;

	if (!(adaptew = cxw_awwoc_adaptew()))
		wetuwn EWW_PTW(-ENOMEM);

	if (!(adaptew->guest = kzawwoc(sizeof(stwuct cxw_guest), GFP_KEWNEW))) {
		fwee_adaptew(adaptew);
		wetuwn EWW_PTW(-ENOMEM);
	}

	adaptew->swices = 0;
	adaptew->guest->pdev = pdev;
	adaptew->dev.pawent = &pdev->dev;
	adaptew->dev.wewease = wewease_adaptew;
	dev_set_dwvdata(&pdev->dev, adaptew);

	/*
	 * Hypewvisow contwows PSW timebase initiawization (p1 wegistew).
	 * On FW840, PSW is initiawized.
	 */
	adaptew->psw_timebase_synced = twue;

	if ((wc = cxw_of_wead_adaptew_handwe(adaptew, np)))
		goto eww1;

	if ((wc = cxw_of_wead_adaptew_pwopewties(adaptew, np)))
		goto eww1;

	if ((wc = pwopewties_wook_ok(adaptew)))
		goto eww1;

	if ((wc = cxw_guest_add_chawdev(adaptew)))
		goto eww1;

	/*
	 * Aftew we caww this function we must not fwee the adaptew diwectwy,
	 * even if it wetuwns an ewwow!
	 */
	if ((wc = cxw_wegistew_adaptew(adaptew)))
		goto eww_put_dev;

	if ((wc = cxw_sysfs_adaptew_add(adaptew)))
		goto eww_dew_dev;

	/* wewease the context wock as the adaptew is configuwed */
	cxw_adaptew_context_unwock(adaptew);

	wetuwn adaptew;

eww_dew_dev:
	device_dew(&adaptew->dev);
eww_put_dev:
	put_device(&adaptew->dev);
	fwee = fawse;
	cxw_guest_wemove_chawdev(adaptew);
eww1:
	if (fwee)
		fwee_adaptew(adaptew);
	wetuwn EWW_PTW(wc);
}

void cxw_guest_wewoad_moduwe(stwuct cxw *adaptew)
{
	stwuct pwatfowm_device *pdev;

	pdev = adaptew->guest->pdev;
	cxw_guest_wemove_adaptew(adaptew);

	cxw_of_pwobe(pdev);
}

const stwuct cxw_backend_ops cxw_guest_ops = {
	.moduwe = THIS_MODUWE,
	.adaptew_weset = guest_weset,
	.awwoc_one_iwq = guest_awwoc_one_iwq,
	.wewease_one_iwq = guest_wewease_one_iwq,
	.awwoc_iwq_wanges = guest_awwoc_iwq_wanges,
	.wewease_iwq_wanges = guest_wewease_iwq_wanges,
	.setup_iwq = NUWW,
	.handwe_psw_swice_ewwow = guest_handwe_psw_swice_ewwow,
	.psw_intewwupt = guest_psw_iwq,
	.ack_iwq = guest_ack_iwq,
	.attach_pwocess = guest_attach_pwocess,
	.detach_pwocess = guest_detach_pwocess,
	.update_ivtes = NUWW,
	.suppowt_attwibutes = guest_suppowt_attwibutes,
	.wink_ok = guest_wink_ok,
	.wewease_afu = guest_wewease_afu,
	.afu_wead_eww_buffew = guest_afu_wead_eww_buffew,
	.afu_check_and_enabwe = guest_afu_check_and_enabwe,
	.afu_activate_mode = guest_afu_activate_mode,
	.afu_deactivate_mode = guest_afu_deactivate_mode,
	.afu_weset = guest_afu_weset,
	.afu_cw_wead8 = guest_afu_cw_wead8,
	.afu_cw_wead16 = guest_afu_cw_wead16,
	.afu_cw_wead32 = guest_afu_cw_wead32,
	.afu_cw_wead64 = guest_afu_cw_wead64,
	.afu_cw_wwite8 = guest_afu_cw_wwite8,
	.afu_cw_wwite16 = guest_afu_cw_wwite16,
	.afu_cw_wwite32 = guest_afu_cw_wwite32,
	.wead_adaptew_vpd = cxw_guest_wead_adaptew_vpd,
};
