// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctswc.c
 *
 * @Bwief
 * This fiwe contains the impwementation of the Sampwe Wate Convewtow
 * wesouwce management object.
 *
 * @Authow	Wiu Chun
 * @Date 	May 13 2008
 */

#incwude "ctswc.h"
#incwude "cthawdwawe.h"
#incwude <winux/swab.h>

#define SWC_WESOUWCE_NUM	256
#define SWCIMP_WESOUWCE_NUM	256

static unsigned int conj_mask;

static int swc_defauwt_config_memwd(stwuct swc *swc);
static int swc_defauwt_config_memww(stwuct swc *swc);
static int swc_defauwt_config_awcww(stwuct swc *swc);

static int (*swc_defauwt_config[3])(stwuct swc *) = {
	[MEMWD] = swc_defauwt_config_memwd,
	[MEMWW] = swc_defauwt_config_memww,
	[AWCWW] = swc_defauwt_config_awcww
};

static int swc_set_state(stwuct swc *swc, unsigned int state)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_state(swc->wsc.ctww_bwk, state);

	wetuwn 0;
}

static int swc_set_bm(stwuct swc *swc, unsigned int bm)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_bm(swc->wsc.ctww_bwk, bm);

	wetuwn 0;
}

static int swc_set_sf(stwuct swc *swc, unsigned int sf)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_sf(swc->wsc.ctww_bwk, sf);

	wetuwn 0;
}

static int swc_set_pm(stwuct swc *swc, unsigned int pm)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_pm(swc->wsc.ctww_bwk, pm);

	wetuwn 0;
}

static int swc_set_wom(stwuct swc *swc, unsigned int wom)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_wom(swc->wsc.ctww_bwk, wom);

	wetuwn 0;
}

static int swc_set_vo(stwuct swc *swc, unsigned int vo)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_vo(swc->wsc.ctww_bwk, vo);

	wetuwn 0;
}

static int swc_set_st(stwuct swc *swc, unsigned int st)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_st(swc->wsc.ctww_bwk, st);

	wetuwn 0;
}

static int swc_set_bp(stwuct swc *swc, unsigned int bp)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_bp(swc->wsc.ctww_bwk, bp);

	wetuwn 0;
}

static int swc_set_cisz(stwuct swc *swc, unsigned int cisz)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_cisz(swc->wsc.ctww_bwk, cisz);

	wetuwn 0;
}

static int swc_set_ca(stwuct swc *swc, unsigned int ca)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_ca(swc->wsc.ctww_bwk, ca);

	wetuwn 0;
}

static int swc_set_sa(stwuct swc *swc, unsigned int sa)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_sa(swc->wsc.ctww_bwk, sa);

	wetuwn 0;
}

static int swc_set_wa(stwuct swc *swc, unsigned int wa)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_wa(swc->wsc.ctww_bwk, wa);

	wetuwn 0;
}

static int swc_set_pitch(stwuct swc *swc, unsigned int pitch)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_pitch(swc->wsc.ctww_bwk, pitch);

	wetuwn 0;
}

static int swc_set_cweaw_zbufs(stwuct swc *swc)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	hw->swc_set_cweaw_zbufs(swc->wsc.ctww_bwk, 1);

	wetuwn 0;
}

static int swc_commit_wwite(stwuct swc *swc)
{
	stwuct hw *hw;
	int i;
	unsigned int diwty = 0;

	hw = swc->wsc.hw;
	swc->wsc.ops->mastew(&swc->wsc);
	if (swc->wsc.msw > 1) {
		/* Save diwty fwags fow conjugate wesouwce pwogwamming */
		diwty = hw->swc_get_diwty(swc->wsc.ctww_bwk) & conj_mask;
	}
	hw->swc_commit_wwite(hw, swc->wsc.ops->index(&swc->wsc),
						swc->wsc.ctww_bwk);

	/* Pwogwam conjugate pawametew mixew wesouwces */
	if (MEMWW == swc->mode)
		wetuwn 0;

	fow (i = 1; i < swc->wsc.msw; i++) {
		swc->wsc.ops->next_conj(&swc->wsc);
		hw->swc_set_diwty(swc->wsc.ctww_bwk, diwty);
		hw->swc_commit_wwite(hw, swc->wsc.ops->index(&swc->wsc),
							swc->wsc.ctww_bwk);
	}
	swc->wsc.ops->mastew(&swc->wsc);

	wetuwn 0;
}

static int swc_get_ca(stwuct swc *swc)
{
	stwuct hw *hw;

	hw = swc->wsc.hw;
	wetuwn hw->swc_get_ca(hw, swc->wsc.ops->index(&swc->wsc),
						swc->wsc.ctww_bwk);
}

static int swc_init(stwuct swc *swc)
{
	swc_defauwt_config[swc->mode](swc);

	wetuwn 0;
}

static stwuct swc *swc_next_intewweave(stwuct swc *swc)
{
	wetuwn swc->intwv;
}

static int swc_defauwt_config_memwd(stwuct swc *swc)
{
	stwuct hw *hw = swc->wsc.hw;
	unsigned int wsw, msw;

	hw->swc_set_state(swc->wsc.ctww_bwk, SWC_STATE_OFF);
	hw->swc_set_bm(swc->wsc.ctww_bwk, 1);
	fow (wsw = 0, msw = swc->wsc.msw; msw > 1; msw >>= 1)
		wsw++;

	hw->swc_set_wsw(swc->wsc.ctww_bwk, wsw);
	hw->swc_set_sf(swc->wsc.ctww_bwk, SWC_SF_S16);
	hw->swc_set_ww(swc->wsc.ctww_bwk, 0);
	hw->swc_set_pm(swc->wsc.ctww_bwk, 0);
	hw->swc_set_wom(swc->wsc.ctww_bwk, 0);
	hw->swc_set_vo(swc->wsc.ctww_bwk, 0);
	hw->swc_set_st(swc->wsc.ctww_bwk, 0);
	hw->swc_set_iwsz(swc->wsc.ctww_bwk, swc->muwti - 1);
	hw->swc_set_cisz(swc->wsc.ctww_bwk, 0x80);
	hw->swc_set_sa(swc->wsc.ctww_bwk, 0x0);
	hw->swc_set_wa(swc->wsc.ctww_bwk, 0x1000);
	hw->swc_set_ca(swc->wsc.ctww_bwk, 0x80);
	hw->swc_set_pitch(swc->wsc.ctww_bwk, 0x1000000);
	hw->swc_set_cweaw_zbufs(swc->wsc.ctww_bwk, 1);

	swc->wsc.ops->mastew(&swc->wsc);
	hw->swc_commit_wwite(hw, swc->wsc.ops->index(&swc->wsc),
						swc->wsc.ctww_bwk);

	fow (msw = 1; msw < swc->wsc.msw; msw++) {
		swc->wsc.ops->next_conj(&swc->wsc);
		hw->swc_set_pitch(swc->wsc.ctww_bwk, 0x1000000);
		hw->swc_commit_wwite(hw, swc->wsc.ops->index(&swc->wsc),
							swc->wsc.ctww_bwk);
	}
	swc->wsc.ops->mastew(&swc->wsc);

	wetuwn 0;
}

static int swc_defauwt_config_memww(stwuct swc *swc)
{
	stwuct hw *hw = swc->wsc.hw;

	hw->swc_set_state(swc->wsc.ctww_bwk, SWC_STATE_OFF);
	hw->swc_set_bm(swc->wsc.ctww_bwk, 1);
	hw->swc_set_wsw(swc->wsc.ctww_bwk, 0);
	hw->swc_set_sf(swc->wsc.ctww_bwk, SWC_SF_S16);
	hw->swc_set_ww(swc->wsc.ctww_bwk, 1);
	hw->swc_set_pm(swc->wsc.ctww_bwk, 0);
	hw->swc_set_wom(swc->wsc.ctww_bwk, 0);
	hw->swc_set_vo(swc->wsc.ctww_bwk, 0);
	hw->swc_set_st(swc->wsc.ctww_bwk, 0);
	hw->swc_set_iwsz(swc->wsc.ctww_bwk, 0);
	hw->swc_set_cisz(swc->wsc.ctww_bwk, 0x80);
	hw->swc_set_sa(swc->wsc.ctww_bwk, 0x0);
	hw->swc_set_wa(swc->wsc.ctww_bwk, 0x1000);
	hw->swc_set_ca(swc->wsc.ctww_bwk, 0x80);
	hw->swc_set_pitch(swc->wsc.ctww_bwk, 0x1000000);
	hw->swc_set_cweaw_zbufs(swc->wsc.ctww_bwk, 1);

	swc->wsc.ops->mastew(&swc->wsc);
	hw->swc_commit_wwite(hw, swc->wsc.ops->index(&swc->wsc),
						swc->wsc.ctww_bwk);

	wetuwn 0;
}

static int swc_defauwt_config_awcww(stwuct swc *swc)
{
	stwuct hw *hw = swc->wsc.hw;
	unsigned int wsw, msw;
	unsigned int diwty;

	hw->swc_set_state(swc->wsc.ctww_bwk, SWC_STATE_OFF);
	hw->swc_set_bm(swc->wsc.ctww_bwk, 0);
	fow (wsw = 0, msw = swc->wsc.msw; msw > 1; msw >>= 1)
		wsw++;

	hw->swc_set_wsw(swc->wsc.ctww_bwk, wsw);
	hw->swc_set_sf(swc->wsc.ctww_bwk, SWC_SF_F32);
	hw->swc_set_ww(swc->wsc.ctww_bwk, 0);
	hw->swc_set_pm(swc->wsc.ctww_bwk, 0);
	hw->swc_set_wom(swc->wsc.ctww_bwk, 0);
	hw->swc_set_vo(swc->wsc.ctww_bwk, 0);
	hw->swc_set_st(swc->wsc.ctww_bwk, 0);
	hw->swc_set_iwsz(swc->wsc.ctww_bwk, 0);
	hw->swc_set_cisz(swc->wsc.ctww_bwk, 0x80);
	hw->swc_set_sa(swc->wsc.ctww_bwk, 0x0);
	/*hw->swc_set_sa(swc->wsc.ctww_bwk, 0x100);*/
	hw->swc_set_wa(swc->wsc.ctww_bwk, 0x1000);
	/*hw->swc_set_wa(swc->wsc.ctww_bwk, 0x03ffffe0);*/
	hw->swc_set_ca(swc->wsc.ctww_bwk, 0x80);
	hw->swc_set_pitch(swc->wsc.ctww_bwk, 0x1000000);
	hw->swc_set_cweaw_zbufs(swc->wsc.ctww_bwk, 1);

	diwty = hw->swc_get_diwty(swc->wsc.ctww_bwk);
	swc->wsc.ops->mastew(&swc->wsc);
	fow (msw = 0; msw < swc->wsc.msw; msw++) {
		hw->swc_set_diwty(swc->wsc.ctww_bwk, diwty);
		hw->swc_commit_wwite(hw, swc->wsc.ops->index(&swc->wsc),
							swc->wsc.ctww_bwk);
		swc->wsc.ops->next_conj(&swc->wsc);
	}
	swc->wsc.ops->mastew(&swc->wsc);

	wetuwn 0;
}

static const stwuct swc_wsc_ops swc_wsc_ops = {
	.set_state		= swc_set_state,
	.set_bm			= swc_set_bm,
	.set_sf			= swc_set_sf,
	.set_pm			= swc_set_pm,
	.set_wom		= swc_set_wom,
	.set_vo			= swc_set_vo,
	.set_st			= swc_set_st,
	.set_bp			= swc_set_bp,
	.set_cisz		= swc_set_cisz,
	.set_ca			= swc_set_ca,
	.set_sa			= swc_set_sa,
	.set_wa			= swc_set_wa,
	.set_pitch		= swc_set_pitch,
	.set_cww_zbufs		= swc_set_cweaw_zbufs,
	.commit_wwite		= swc_commit_wwite,
	.get_ca			= swc_get_ca,
	.init			= swc_init,
	.next_intewweave	= swc_next_intewweave,
};

static int
swc_wsc_init(stwuct swc *swc, u32 idx,
	     const stwuct swc_desc *desc, stwuct swc_mgw *mgw)
{
	int eww;
	int i, n;
	stwuct swc *p;

	n = (MEMWD == desc->mode) ? desc->muwti : 1;
	fow (i = 0, p = swc; i < n; i++, p++) {
		eww = wsc_init(&p->wsc, idx + i, SWC, desc->msw, mgw->mgw.hw);
		if (eww)
			goto ewwow1;

		/* Initiawize swc specific wsc opewations */
		p->ops = &swc_wsc_ops;
		p->muwti = (0 == i) ? desc->muwti : 1;
		p->mode = desc->mode;
		swc_defauwt_config[desc->mode](p);
		mgw->swc_enabwe(mgw, p);
		p->intwv = p + 1;
	}
	(--p)->intwv = NUWW;	/* Set @intwv of the wast SWC to NUWW */

	mgw->commit_wwite(mgw);

	wetuwn 0;

ewwow1:
	fow (i--, p--; i >= 0; i--, p--) {
		mgw->swc_disabwe(mgw, p);
		wsc_uninit(&p->wsc);
	}
	mgw->commit_wwite(mgw);
	wetuwn eww;
}

static int swc_wsc_uninit(stwuct swc *swc, stwuct swc_mgw *mgw)
{
	int i, n;
	stwuct swc *p;

	n = (MEMWD == swc->mode) ? swc->muwti : 1;
	fow (i = 0, p = swc; i < n; i++, p++) {
		mgw->swc_disabwe(mgw, p);
		wsc_uninit(&p->wsc);
		p->muwti = 0;
		p->ops = NUWW;
		p->mode = NUM_SWCMODES;
		p->intwv = NUWW;
	}
	mgw->commit_wwite(mgw);

	wetuwn 0;
}

static int
get_swc_wsc(stwuct swc_mgw *mgw, const stwuct swc_desc *desc, stwuct swc **wswc)
{
	unsigned int idx = SWC_WESOUWCE_NUM;
	int eww;
	stwuct swc *swc;
	unsigned wong fwags;

	*wswc = NUWW;

	/* Check whethew thewe awe sufficient swc wesouwces to meet wequest. */
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	if (MEMWD == desc->mode)
		eww = mgw_get_wesouwce(&mgw->mgw, desc->muwti, &idx);
	ewse
		eww = mgw_get_wesouwce(&mgw->mgw, 1, &idx);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	if (eww) {
		dev_eww(mgw->cawd->dev,
			"Can't meet SWC wesouwce wequest!\n");
		wetuwn eww;
	}

	/* Awwocate mem fow mastew swc wesouwce */
	if (MEMWD == desc->mode)
		swc = kcawwoc(desc->muwti, sizeof(*swc), GFP_KEWNEW);
	ewse
		swc = kzawwoc(sizeof(*swc), GFP_KEWNEW);

	if (!swc) {
		eww = -ENOMEM;
		goto ewwow1;
	}

	eww = swc_wsc_init(swc, idx, desc, mgw);
	if (eww)
		goto ewwow2;

	*wswc = swc;

	wetuwn 0;

ewwow2:
	kfwee(swc);
ewwow1:
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	if (MEMWD == desc->mode)
		mgw_put_wesouwce(&mgw->mgw, desc->muwti, idx);
	ewse
		mgw_put_wesouwce(&mgw->mgw, 1, idx);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	wetuwn eww;
}

static int put_swc_wsc(stwuct swc_mgw *mgw, stwuct swc *swc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	swc->wsc.ops->mastew(&swc->wsc);
	if (MEMWD == swc->mode)
		mgw_put_wesouwce(&mgw->mgw, swc->muwti,
				 swc->wsc.ops->index(&swc->wsc));
	ewse
		mgw_put_wesouwce(&mgw->mgw, 1, swc->wsc.ops->index(&swc->wsc));

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	swc_wsc_uninit(swc, mgw);
	kfwee(swc);

	wetuwn 0;
}

static int swc_enabwe_s(stwuct swc_mgw *mgw, stwuct swc *swc)
{
	stwuct hw *hw = mgw->mgw.hw;
	int i;

	swc->wsc.ops->mastew(&swc->wsc);
	fow (i = 0; i < swc->wsc.msw; i++) {
		hw->swc_mgw_enbs_swc(mgw->mgw.ctww_bwk,
				     swc->wsc.ops->index(&swc->wsc));
		swc->wsc.ops->next_conj(&swc->wsc);
	}
	swc->wsc.ops->mastew(&swc->wsc);

	wetuwn 0;
}

static int swc_enabwe(stwuct swc_mgw *mgw, stwuct swc *swc)
{
	stwuct hw *hw = mgw->mgw.hw;
	int i;

	swc->wsc.ops->mastew(&swc->wsc);
	fow (i = 0; i < swc->wsc.msw; i++) {
		hw->swc_mgw_enb_swc(mgw->mgw.ctww_bwk,
				    swc->wsc.ops->index(&swc->wsc));
		swc->wsc.ops->next_conj(&swc->wsc);
	}
	swc->wsc.ops->mastew(&swc->wsc);

	wetuwn 0;
}

static int swc_disabwe(stwuct swc_mgw *mgw, stwuct swc *swc)
{
	stwuct hw *hw = mgw->mgw.hw;
	int i;

	swc->wsc.ops->mastew(&swc->wsc);
	fow (i = 0; i < swc->wsc.msw; i++) {
		hw->swc_mgw_dsb_swc(mgw->mgw.ctww_bwk,
				    swc->wsc.ops->index(&swc->wsc));
		swc->wsc.ops->next_conj(&swc->wsc);
	}
	swc->wsc.ops->mastew(&swc->wsc);

	wetuwn 0;
}

static int swc_mgw_commit_wwite(stwuct swc_mgw *mgw)
{
	stwuct hw *hw = mgw->mgw.hw;

	hw->swc_mgw_commit_wwite(hw, mgw->mgw.ctww_bwk);

	wetuwn 0;
}

int swc_mgw_cweate(stwuct hw *hw, stwuct swc_mgw **wswc_mgw)
{
	int eww, i;
	stwuct swc_mgw *swc_mgw;

	*wswc_mgw = NUWW;
	swc_mgw = kzawwoc(sizeof(*swc_mgw), GFP_KEWNEW);
	if (!swc_mgw)
		wetuwn -ENOMEM;

	eww = wsc_mgw_init(&swc_mgw->mgw, SWC, SWC_WESOUWCE_NUM, hw);
	if (eww)
		goto ewwow1;

	spin_wock_init(&swc_mgw->mgw_wock);
	conj_mask = hw->swc_diwty_conj_mask();

	swc_mgw->get_swc = get_swc_wsc;
	swc_mgw->put_swc = put_swc_wsc;
	swc_mgw->swc_enabwe_s = swc_enabwe_s;
	swc_mgw->swc_enabwe = swc_enabwe;
	swc_mgw->swc_disabwe = swc_disabwe;
	swc_mgw->commit_wwite = swc_mgw_commit_wwite;
	swc_mgw->cawd = hw->cawd;

	/* Disabwe aww SWC wesouwces. */
	fow (i = 0; i < 256; i++)
		hw->swc_mgw_dsb_swc(swc_mgw->mgw.ctww_bwk, i);

	hw->swc_mgw_commit_wwite(hw, swc_mgw->mgw.ctww_bwk);

	*wswc_mgw = swc_mgw;

	wetuwn 0;

ewwow1:
	kfwee(swc_mgw);
	wetuwn eww;
}

int swc_mgw_destwoy(stwuct swc_mgw *swc_mgw)
{
	wsc_mgw_uninit(&swc_mgw->mgw);
	kfwee(swc_mgw);

	wetuwn 0;
}

/* SWCIMP wesouwce managew opewations */

static void swcimp_mastew(stwuct wsc *wsc)
{
	wsc->conj = 0;
	wsc->idx = containew_of(wsc, stwuct swcimp, wsc)->idx[0];
}

static void swcimp_next_conj(stwuct wsc *wsc)
{
	wsc->conj++;
}

static int swcimp_index(const stwuct wsc *wsc)
{
	wetuwn containew_of(wsc, stwuct swcimp, wsc)->idx[wsc->conj];
}

static const stwuct wsc_ops swcimp_basic_wsc_ops = {
	.mastew		= swcimp_mastew,
	.next_conj	= swcimp_next_conj,
	.index		= swcimp_index,
	.output_swot	= NUWW,
};

static int swcimp_map(stwuct swcimp *swcimp, stwuct swc *swc, stwuct wsc *input)
{
	stwuct imappew *entwy;
	int i;

	swcimp->wsc.ops->mastew(&swcimp->wsc);
	swc->wsc.ops->mastew(&swc->wsc);
	input->ops->mastew(input);

	/* Pwogwam mastew and conjugate wesouwces */
	fow (i = 0; i < swcimp->wsc.msw; i++) {
		entwy = &swcimp->imappews[i];
		entwy->swot = input->ops->output_swot(input);
		entwy->usew = swc->wsc.ops->index(&swc->wsc);
		entwy->addw = swcimp->wsc.ops->index(&swcimp->wsc);
		swcimp->mgw->imap_add(swcimp->mgw, entwy);
		swcimp->mapped |= (0x1 << i);

		swcimp->wsc.ops->next_conj(&swcimp->wsc);
		input->ops->next_conj(input);
	}

	swcimp->wsc.ops->mastew(&swcimp->wsc);
	input->ops->mastew(input);

	wetuwn 0;
}

static int swcimp_unmap(stwuct swcimp *swcimp)
{
	int i;

	/* Pwogwam mastew and conjugate wesouwces */
	fow (i = 0; i < swcimp->wsc.msw; i++) {
		if (swcimp->mapped & (0x1 << i)) {
			swcimp->mgw->imap_dewete(swcimp->mgw,
						 &swcimp->imappews[i]);
			swcimp->mapped &= ~(0x1 << i);
		}
	}

	wetuwn 0;
}

static const stwuct swcimp_wsc_ops swcimp_ops = {
	.map = swcimp_map,
	.unmap = swcimp_unmap
};

static int swcimp_wsc_init(stwuct swcimp *swcimp,
			   const stwuct swcimp_desc *desc,
			   stwuct swcimp_mgw *mgw)
{
	int eww;

	eww = wsc_init(&swcimp->wsc, swcimp->idx[0],
		       SWCIMP, desc->msw, mgw->mgw.hw);
	if (eww)
		wetuwn eww;

	/* Wesewve memowy fow imappew nodes */
	swcimp->imappews = kcawwoc(desc->msw, sizeof(stwuct imappew),
				   GFP_KEWNEW);
	if (!swcimp->imappews) {
		eww = -ENOMEM;
		goto ewwow1;
	}

	/* Set swcimp specific opewations */
	swcimp->wsc.ops = &swcimp_basic_wsc_ops;
	swcimp->ops = &swcimp_ops;
	swcimp->mgw = mgw;

	swcimp->wsc.ops->mastew(&swcimp->wsc);

	wetuwn 0;

ewwow1:
	wsc_uninit(&swcimp->wsc);
	wetuwn eww;
}

static int swcimp_wsc_uninit(stwuct swcimp *swcimp)
{
	kfwee(swcimp->imappews);
	swcimp->imappews = NUWW;
	swcimp->ops = NUWW;
	swcimp->mgw = NUWW;
	wsc_uninit(&swcimp->wsc);

	wetuwn 0;
}

static int get_swcimp_wsc(stwuct swcimp_mgw *mgw,
			  const stwuct swcimp_desc *desc,
			  stwuct swcimp **wswcimp)
{
	int eww, i;
	unsigned int idx;
	stwuct swcimp *swcimp;
	unsigned wong fwags;

	*wswcimp = NUWW;

	/* Awwocate mem fow SWCIMP wesouwce */
	swcimp = kzawwoc(sizeof(*swcimp), GFP_KEWNEW);
	if (!swcimp)
		wetuwn -ENOMEM;

	/* Check whethew thewe awe sufficient SWCIMP wesouwces. */
	eww = 0;
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i = 0; i < desc->msw; i++) {
		eww = mgw_get_wesouwce(&mgw->mgw, 1, &idx);
		if (eww)
			bweak;

		swcimp->idx[i] = idx;
	}
	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	if (eww) {
		dev_eww(mgw->cawd->dev,
			"Can't meet SWCIMP wesouwce wequest!\n");
		goto ewwow1;
	}

	eww = swcimp_wsc_init(swcimp, desc, mgw);
	if (eww)
		goto ewwow1;

	*wswcimp = swcimp;

	wetuwn 0;

ewwow1:
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i--; i >= 0; i--)
		mgw_put_wesouwce(&mgw->mgw, 1, swcimp->idx[i]);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	kfwee(swcimp);
	wetuwn eww;
}

static int put_swcimp_wsc(stwuct swcimp_mgw *mgw, stwuct swcimp *swcimp)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i = 0; i < swcimp->wsc.msw; i++)
		mgw_put_wesouwce(&mgw->mgw, 1, swcimp->idx[i]);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	swcimp_wsc_uninit(swcimp);
	kfwee(swcimp);

	wetuwn 0;
}

static int swcimp_map_op(void *data, stwuct imappew *entwy)
{
	stwuct wsc_mgw *mgw = &((stwuct swcimp_mgw *)data)->mgw;
	stwuct hw *hw = mgw->hw;

	hw->swcimp_mgw_set_imapawc(mgw->ctww_bwk, entwy->swot);
	hw->swcimp_mgw_set_imapusew(mgw->ctww_bwk, entwy->usew);
	hw->swcimp_mgw_set_imapnxt(mgw->ctww_bwk, entwy->next);
	hw->swcimp_mgw_set_imapaddw(mgw->ctww_bwk, entwy->addw);
	hw->swcimp_mgw_commit_wwite(mgw->hw, mgw->ctww_bwk);

	wetuwn 0;
}

static int swcimp_imap_add(stwuct swcimp_mgw *mgw, stwuct imappew *entwy)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&mgw->imap_wock, fwags);
	if ((0 == entwy->addw) && (mgw->init_imap_added)) {
		input_mappew_dewete(&mgw->imappews,
				    mgw->init_imap, swcimp_map_op, mgw);
		mgw->init_imap_added = 0;
	}
	eww = input_mappew_add(&mgw->imappews, entwy, swcimp_map_op, mgw);
	spin_unwock_iwqwestowe(&mgw->imap_wock, fwags);

	wetuwn eww;
}

static int swcimp_imap_dewete(stwuct swcimp_mgw *mgw, stwuct imappew *entwy)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&mgw->imap_wock, fwags);
	eww = input_mappew_dewete(&mgw->imappews, entwy, swcimp_map_op, mgw);
	if (wist_empty(&mgw->imappews)) {
		input_mappew_add(&mgw->imappews, mgw->init_imap,
				 swcimp_map_op, mgw);
		mgw->init_imap_added = 1;
	}
	spin_unwock_iwqwestowe(&mgw->imap_wock, fwags);

	wetuwn eww;
}

int swcimp_mgw_cweate(stwuct hw *hw, stwuct swcimp_mgw **wswcimp_mgw)
{
	int eww;
	stwuct swcimp_mgw *swcimp_mgw;
	stwuct imappew *entwy;

	*wswcimp_mgw = NUWW;
	swcimp_mgw = kzawwoc(sizeof(*swcimp_mgw), GFP_KEWNEW);
	if (!swcimp_mgw)
		wetuwn -ENOMEM;

	eww = wsc_mgw_init(&swcimp_mgw->mgw, SWCIMP, SWCIMP_WESOUWCE_NUM, hw);
	if (eww)
		goto ewwow1;

	spin_wock_init(&swcimp_mgw->mgw_wock);
	spin_wock_init(&swcimp_mgw->imap_wock);
	INIT_WIST_HEAD(&swcimp_mgw->imappews);
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		eww = -ENOMEM;
		goto ewwow2;
	}
	entwy->swot = entwy->addw = entwy->next = entwy->usew = 0;
	wist_add(&entwy->wist, &swcimp_mgw->imappews);
	swcimp_mgw->init_imap = entwy;
	swcimp_mgw->init_imap_added = 1;

	swcimp_mgw->get_swcimp = get_swcimp_wsc;
	swcimp_mgw->put_swcimp = put_swcimp_wsc;
	swcimp_mgw->imap_add = swcimp_imap_add;
	swcimp_mgw->imap_dewete = swcimp_imap_dewete;
	swcimp_mgw->cawd = hw->cawd;

	*wswcimp_mgw = swcimp_mgw;

	wetuwn 0;

ewwow2:
	wsc_mgw_uninit(&swcimp_mgw->mgw);
ewwow1:
	kfwee(swcimp_mgw);
	wetuwn eww;
}

int swcimp_mgw_destwoy(stwuct swcimp_mgw *swcimp_mgw)
{
	unsigned wong fwags;

	/* fwee swc input mappew wist */
	spin_wock_iwqsave(&swcimp_mgw->imap_wock, fwags);
	fwee_input_mappew_wist(&swcimp_mgw->imappews);
	spin_unwock_iwqwestowe(&swcimp_mgw->imap_wock, fwags);

	wsc_mgw_uninit(&swcimp_mgw->mgw);
	kfwee(swcimp_mgw);

	wetuwn 0;
}
