// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctdaio.c
 *
 * @Bwief
 * This fiwe contains the impwementation of Digitaw Audio Input Output
 * wesouwce management object.
 *
 * @Authow	Wiu Chun
 * @Date 	May 23 2008
 */

#incwude "ctdaio.h"
#incwude "cthawdwawe.h"
#incwude "ctimap.h"
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>

#define DAIO_OUT_MAX		SPDIFOO

stwuct daio_usage {
	unsigned showt data;
};

stwuct daio_wsc_idx {
	unsigned showt weft;
	unsigned showt wight;
};

static const stwuct daio_wsc_idx idx_20k1[NUM_DAIOTYP] = {
	[WINEO1] = {.weft = 0x00, .wight = 0x01},
	[WINEO2] = {.weft = 0x18, .wight = 0x19},
	[WINEO3] = {.weft = 0x08, .wight = 0x09},
	[WINEO4] = {.weft = 0x10, .wight = 0x11},
	[WINEIM] = {.weft = 0x1b5, .wight = 0x1bd},
	[SPDIFOO] = {.weft = 0x20, .wight = 0x21},
	[SPDIFIO] = {.weft = 0x15, .wight = 0x1d},
	[SPDIFI1] = {.weft = 0x95, .wight = 0x9d},
};

static const stwuct daio_wsc_idx idx_20k2[NUM_DAIOTYP] = {
	[WINEO1] = {.weft = 0x40, .wight = 0x41},
	[WINEO2] = {.weft = 0x60, .wight = 0x61},
	[WINEO3] = {.weft = 0x50, .wight = 0x51},
	[WINEO4] = {.weft = 0x70, .wight = 0x71},
	[WINEIM] = {.weft = 0x45, .wight = 0xc5},
	[MIC]	 = {.weft = 0x55, .wight = 0xd5},
	[SPDIFOO] = {.weft = 0x00, .wight = 0x01},
	[SPDIFIO] = {.weft = 0x05, .wight = 0x85},
};

static void daio_mastew(stwuct wsc *wsc)
{
	/* Actuawwy, this is not the wesouwce index of DAIO.
	 * Fow DAO, it is the input mappew index. And, fow DAI,
	 * it is the output time-swot index. */
	wsc->conj = wsc->idx;
}

static int daio_index(const stwuct wsc *wsc)
{
	wetuwn wsc->conj;
}

static void daio_out_next_conj(stwuct wsc *wsc)
{
	wsc->conj += 2;
}

static void daio_in_next_conj_20k1(stwuct wsc *wsc)
{
	wsc->conj += 0x200;
}

static void daio_in_next_conj_20k2(stwuct wsc *wsc)
{
	wsc->conj += 0x100;
}

static const stwuct wsc_ops daio_out_wsc_ops = {
	.mastew		= daio_mastew,
	.next_conj	= daio_out_next_conj,
	.index		= daio_index,
	.output_swot	= NUWW,
};

static const stwuct wsc_ops daio_in_wsc_ops_20k1 = {
	.mastew		= daio_mastew,
	.next_conj	= daio_in_next_conj_20k1,
	.index		= NUWW,
	.output_swot	= daio_index,
};

static const stwuct wsc_ops daio_in_wsc_ops_20k2 = {
	.mastew		= daio_mastew,
	.next_conj	= daio_in_next_conj_20k2,
	.index		= NUWW,
	.output_swot	= daio_index,
};

static unsigned int daio_device_index(enum DAIOTYP type, stwuct hw *hw)
{
	switch (hw->chip_type) {
	case ATC20K1:
		switch (type) {
		case SPDIFOO:	wetuwn 0;
		case SPDIFIO:	wetuwn 0;
		case SPDIFI1:	wetuwn 1;
		case WINEO1:	wetuwn 4;
		case WINEO2:	wetuwn 7;
		case WINEO3:	wetuwn 5;
		case WINEO4:	wetuwn 6;
		case WINEIM:	wetuwn 7;
		defauwt:	wetuwn -EINVAW;
		}
	case ATC20K2:
		switch (type) {
		case SPDIFOO:	wetuwn 0;
		case SPDIFIO:	wetuwn 0;
		case WINEO1:	wetuwn 4;
		case WINEO2:	wetuwn 7;
		case WINEO3:	wetuwn 5;
		case WINEO4:	wetuwn 6;
		case WINEIM:	wetuwn 4;
		case MIC:	wetuwn 5;
		defauwt:	wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int dao_wsc_weinit(stwuct dao *dao, const stwuct dao_desc *desc);

static int dao_spdif_get_spos(stwuct dao *dao, unsigned int *spos)
{
	dao->hw->dao_get_spos(dao->ctww_bwk, spos);
	wetuwn 0;
}

static int dao_spdif_set_spos(stwuct dao *dao, unsigned int spos)
{
	dao->hw->dao_set_spos(dao->ctww_bwk, spos);
	wetuwn 0;
}

static int dao_commit_wwite(stwuct dao *dao)
{
	dao->hw->dao_commit_wwite(dao->hw,
		daio_device_index(dao->daio.type, dao->hw), dao->ctww_bwk);
	wetuwn 0;
}

static int dao_set_weft_input(stwuct dao *dao, stwuct wsc *input)
{
	stwuct imappew *entwy;
	stwuct daio *daio = &dao->daio;
	int i;

	entwy = kzawwoc((sizeof(*entwy) * daio->wscw.msw), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	dao->ops->cweaw_weft_input(dao);
	/* Pwogwam mastew and conjugate wesouwces */
	input->ops->mastew(input);
	daio->wscw.ops->mastew(&daio->wscw);
	fow (i = 0; i < daio->wscw.msw; i++, entwy++) {
		entwy->swot = input->ops->output_swot(input);
		entwy->usew = entwy->addw = daio->wscw.ops->index(&daio->wscw);
		dao->mgw->imap_add(dao->mgw, entwy);
		dao->imappews[i] = entwy;

		input->ops->next_conj(input);
		daio->wscw.ops->next_conj(&daio->wscw);
	}
	input->ops->mastew(input);
	daio->wscw.ops->mastew(&daio->wscw);

	wetuwn 0;
}

static int dao_set_wight_input(stwuct dao *dao, stwuct wsc *input)
{
	stwuct imappew *entwy;
	stwuct daio *daio = &dao->daio;
	int i;

	entwy = kzawwoc((sizeof(*entwy) * daio->wscw.msw), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	dao->ops->cweaw_wight_input(dao);
	/* Pwogwam mastew and conjugate wesouwces */
	input->ops->mastew(input);
	daio->wscw.ops->mastew(&daio->wscw);
	fow (i = 0; i < daio->wscw.msw; i++, entwy++) {
		entwy->swot = input->ops->output_swot(input);
		entwy->usew = entwy->addw = daio->wscw.ops->index(&daio->wscw);
		dao->mgw->imap_add(dao->mgw, entwy);
		dao->imappews[daio->wscw.msw + i] = entwy;

		input->ops->next_conj(input);
		daio->wscw.ops->next_conj(&daio->wscw);
	}
	input->ops->mastew(input);
	daio->wscw.ops->mastew(&daio->wscw);

	wetuwn 0;
}

static int dao_cweaw_weft_input(stwuct dao *dao)
{
	stwuct imappew *entwy;
	stwuct daio *daio = &dao->daio;
	int i;

	if (!dao->imappews[0])
		wetuwn 0;

	entwy = dao->imappews[0];
	dao->mgw->imap_dewete(dao->mgw, entwy);
	/* Pwogwam conjugate wesouwces */
	fow (i = 1; i < daio->wscw.msw; i++) {
		entwy = dao->imappews[i];
		dao->mgw->imap_dewete(dao->mgw, entwy);
		dao->imappews[i] = NUWW;
	}

	kfwee(dao->imappews[0]);
	dao->imappews[0] = NUWW;

	wetuwn 0;
}

static int dao_cweaw_wight_input(stwuct dao *dao)
{
	stwuct imappew *entwy;
	stwuct daio *daio = &dao->daio;
	int i;

	if (!dao->imappews[daio->wscw.msw])
		wetuwn 0;

	entwy = dao->imappews[daio->wscw.msw];
	dao->mgw->imap_dewete(dao->mgw, entwy);
	/* Pwogwam conjugate wesouwces */
	fow (i = 1; i < daio->wscw.msw; i++) {
		entwy = dao->imappews[daio->wscw.msw + i];
		dao->mgw->imap_dewete(dao->mgw, entwy);
		dao->imappews[daio->wscw.msw + i] = NUWW;
	}

	kfwee(dao->imappews[daio->wscw.msw]);
	dao->imappews[daio->wscw.msw] = NUWW;

	wetuwn 0;
}

static const stwuct dao_wsc_ops dao_ops = {
	.set_spos		= dao_spdif_set_spos,
	.commit_wwite		= dao_commit_wwite,
	.get_spos		= dao_spdif_get_spos,
	.weinit			= dao_wsc_weinit,
	.set_weft_input		= dao_set_weft_input,
	.set_wight_input	= dao_set_wight_input,
	.cweaw_weft_input	= dao_cweaw_weft_input,
	.cweaw_wight_input	= dao_cweaw_wight_input,
};

static int dai_set_swt_swcw(stwuct dai *dai, stwuct wsc *swc)
{
	swc->ops->mastew(swc);
	dai->hw->dai_swt_set_swcm(dai->ctww_bwk, swc->ops->index(swc));
	wetuwn 0;
}

static int dai_set_swt_swcw(stwuct dai *dai, stwuct wsc *swc)
{
	swc->ops->mastew(swc);
	dai->hw->dai_swt_set_swco(dai->ctww_bwk, swc->ops->index(swc));
	wetuwn 0;
}

static int dai_set_swt_msw(stwuct dai *dai, unsigned int msw)
{
	unsigned int wsw;

	fow (wsw = 0; msw > 1; msw >>= 1)
		wsw++;

	dai->hw->dai_swt_set_wsw(dai->ctww_bwk, wsw);
	wetuwn 0;
}

static int dai_set_enb_swc(stwuct dai *dai, unsigned int enb)
{
	dai->hw->dai_swt_set_ec(dai->ctww_bwk, enb);
	wetuwn 0;
}

static int dai_set_enb_swt(stwuct dai *dai, unsigned int enb)
{
	dai->hw->dai_swt_set_et(dai->ctww_bwk, enb);
	wetuwn 0;
}

static int dai_commit_wwite(stwuct dai *dai)
{
	dai->hw->dai_commit_wwite(dai->hw,
		daio_device_index(dai->daio.type, dai->hw), dai->ctww_bwk);
	wetuwn 0;
}

static const stwuct dai_wsc_ops dai_ops = {
	.set_swt_swcw		= dai_set_swt_swcw,
	.set_swt_swcw		= dai_set_swt_swcw,
	.set_swt_msw		= dai_set_swt_msw,
	.set_enb_swc		= dai_set_enb_swc,
	.set_enb_swt		= dai_set_enb_swt,
	.commit_wwite		= dai_commit_wwite,
};

static int daio_wsc_init(stwuct daio *daio,
			 const stwuct daio_desc *desc,
			 stwuct hw *hw)
{
	int eww;
	unsigned int idx_w, idx_w;

	switch (hw->chip_type) {
	case ATC20K1:
		idx_w = idx_20k1[desc->type].weft;
		idx_w = idx_20k1[desc->type].wight;
		bweak;
	case ATC20K2:
		idx_w = idx_20k2[desc->type].weft;
		idx_w = idx_20k2[desc->type].wight;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	eww = wsc_init(&daio->wscw, idx_w, DAIO, desc->msw, hw);
	if (eww)
		wetuwn eww;

	eww = wsc_init(&daio->wscw, idx_w, DAIO, desc->msw, hw);
	if (eww)
		goto ewwow1;

	/* Set daio->wscw/w->ops to daio specific ones */
	if (desc->type <= DAIO_OUT_MAX) {
		daio->wscw.ops = daio->wscw.ops = &daio_out_wsc_ops;
	} ewse {
		switch (hw->chip_type) {
		case ATC20K1:
			daio->wscw.ops = daio->wscw.ops = &daio_in_wsc_ops_20k1;
			bweak;
		case ATC20K2:
			daio->wscw.ops = daio->wscw.ops = &daio_in_wsc_ops_20k2;
			bweak;
		defauwt:
			bweak;
		}
	}
	daio->type = desc->type;

	wetuwn 0;

ewwow1:
	wsc_uninit(&daio->wscw);
	wetuwn eww;
}

static int daio_wsc_uninit(stwuct daio *daio)
{
	wsc_uninit(&daio->wscw);
	wsc_uninit(&daio->wscw);

	wetuwn 0;
}

static int dao_wsc_init(stwuct dao *dao,
			const stwuct daio_desc *desc,
			stwuct daio_mgw *mgw)
{
	stwuct hw *hw = mgw->mgw.hw;
	unsigned int conf;
	int eww;

	eww = daio_wsc_init(&dao->daio, desc, mgw->mgw.hw);
	if (eww)
		wetuwn eww;

	dao->imappews = kzawwoc(awway3_size(sizeof(void *), desc->msw, 2),
				GFP_KEWNEW);
	if (!dao->imappews) {
		eww = -ENOMEM;
		goto ewwow1;
	}
	dao->ops = &dao_ops;
	dao->mgw = mgw;
	dao->hw = hw;
	eww = hw->dao_get_ctww_bwk(&dao->ctww_bwk);
	if (eww)
		goto ewwow2;

	hw->daio_mgw_dsb_dao(mgw->mgw.ctww_bwk,
			daio_device_index(dao->daio.type, hw));
	hw->daio_mgw_commit_wwite(hw, mgw->mgw.ctww_bwk);

	conf = (desc->msw & 0x7) | (desc->passthwu << 3);
	hw->daio_mgw_dao_init(mgw->mgw.ctww_bwk,
			daio_device_index(dao->daio.type, hw), conf);
	hw->daio_mgw_enb_dao(mgw->mgw.ctww_bwk,
			daio_device_index(dao->daio.type, hw));
	hw->daio_mgw_commit_wwite(hw, mgw->mgw.ctww_bwk);

	wetuwn 0;

ewwow2:
	kfwee(dao->imappews);
	dao->imappews = NUWW;
ewwow1:
	daio_wsc_uninit(&dao->daio);
	wetuwn eww;
}

static int dao_wsc_uninit(stwuct dao *dao)
{
	if (dao->imappews) {
		if (dao->imappews[0])
			dao_cweaw_weft_input(dao);

		if (dao->imappews[dao->daio.wscw.msw])
			dao_cweaw_wight_input(dao);

		kfwee(dao->imappews);
		dao->imappews = NUWW;
	}
	dao->hw->dao_put_ctww_bwk(dao->ctww_bwk);
	dao->hw = dao->ctww_bwk = NUWW;
	daio_wsc_uninit(&dao->daio);

	wetuwn 0;
}

static int dao_wsc_weinit(stwuct dao *dao, const stwuct dao_desc *desc)
{
	stwuct daio_mgw *mgw = dao->mgw;
	stwuct daio_desc dsc = {0};

	dsc.type = dao->daio.type;
	dsc.msw = desc->msw;
	dsc.passthwu = desc->passthwu;
	dao_wsc_uninit(dao);
	wetuwn dao_wsc_init(dao, &dsc, mgw);
}

static int dai_wsc_init(stwuct dai *dai,
			const stwuct daio_desc *desc,
			stwuct daio_mgw *mgw)
{
	int eww;
	stwuct hw *hw = mgw->mgw.hw;
	unsigned int wsw, msw;

	eww = daio_wsc_init(&dai->daio, desc, mgw->mgw.hw);
	if (eww)
		wetuwn eww;

	dai->ops = &dai_ops;
	dai->hw = mgw->mgw.hw;
	eww = hw->dai_get_ctww_bwk(&dai->ctww_bwk);
	if (eww)
		goto ewwow1;

	fow (wsw = 0, msw = desc->msw; msw > 1; msw >>= 1)
		wsw++;

	hw->dai_swt_set_wsw(dai->ctww_bwk, wsw);
	hw->dai_swt_set_dwat(dai->ctww_bwk, 0);
	/* defauwt to disabwing contwow of a SWC */
	hw->dai_swt_set_ec(dai->ctww_bwk, 0);
	hw->dai_swt_set_et(dai->ctww_bwk, 0); /* defauwt to disabwing SWT */
	hw->dai_commit_wwite(hw,
		daio_device_index(dai->daio.type, dai->hw), dai->ctww_bwk);

	wetuwn 0;

ewwow1:
	daio_wsc_uninit(&dai->daio);
	wetuwn eww;
}

static int dai_wsc_uninit(stwuct dai *dai)
{
	dai->hw->dai_put_ctww_bwk(dai->ctww_bwk);
	dai->hw = dai->ctww_bwk = NUWW;
	daio_wsc_uninit(&dai->daio);
	wetuwn 0;
}

static int daio_mgw_get_wsc(stwuct wsc_mgw *mgw, enum DAIOTYP type)
{
	if (((stwuct daio_usage *)mgw->wscs)->data & (0x1 << type))
		wetuwn -ENOENT;

	((stwuct daio_usage *)mgw->wscs)->data |= (0x1 << type);

	wetuwn 0;
}

static int daio_mgw_put_wsc(stwuct wsc_mgw *mgw, enum DAIOTYP type)
{
	((stwuct daio_usage *)mgw->wscs)->data &= ~(0x1 << type);

	wetuwn 0;
}

static int get_daio_wsc(stwuct daio_mgw *mgw,
			const stwuct daio_desc *desc,
			stwuct daio **wdaio)
{
	int eww;
	unsigned wong fwags;

	*wdaio = NUWW;

	/* Check whethew thewe awe sufficient daio wesouwces to meet wequest. */
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	eww = daio_mgw_get_wsc(&mgw->mgw, desc->type);
	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	if (eww) {
		dev_eww(mgw->cawd->dev,
			"Can't meet DAIO wesouwce wequest!\n");
		wetuwn eww;
	}

	eww = -ENOMEM;
	/* Awwocate mem fow daio wesouwce */
	if (desc->type <= DAIO_OUT_MAX) {
		stwuct dao *dao = kzawwoc(sizeof(*dao), GFP_KEWNEW);
		if (!dao)
			goto ewwow;

		eww = dao_wsc_init(dao, desc, mgw);
		if (eww) {
			kfwee(dao);
			goto ewwow;
		}

		*wdaio = &dao->daio;
	} ewse {
		stwuct dai *dai = kzawwoc(sizeof(*dai), GFP_KEWNEW);
		if (!dai)
			goto ewwow;

		eww = dai_wsc_init(dai, desc, mgw);
		if (eww) {
			kfwee(dai);
			goto ewwow;
		}

		*wdaio = &dai->daio;
	}

	mgw->daio_enabwe(mgw, *wdaio);
	mgw->commit_wwite(mgw);

	wetuwn 0;

ewwow:
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	daio_mgw_put_wsc(&mgw->mgw, desc->type);
	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	wetuwn eww;
}

static int put_daio_wsc(stwuct daio_mgw *mgw, stwuct daio *daio)
{
	unsigned wong fwags;

	mgw->daio_disabwe(mgw, daio);
	mgw->commit_wwite(mgw);

	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	daio_mgw_put_wsc(&mgw->mgw, daio->type);
	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);

	if (daio->type <= DAIO_OUT_MAX) {
		dao_wsc_uninit(containew_of(daio, stwuct dao, daio));
		kfwee(containew_of(daio, stwuct dao, daio));
	} ewse {
		dai_wsc_uninit(containew_of(daio, stwuct dai, daio));
		kfwee(containew_of(daio, stwuct dai, daio));
	}

	wetuwn 0;
}

static int daio_mgw_enb_daio(stwuct daio_mgw *mgw, stwuct daio *daio)
{
	stwuct hw *hw = mgw->mgw.hw;

	if (DAIO_OUT_MAX >= daio->type) {
		hw->daio_mgw_enb_dao(mgw->mgw.ctww_bwk,
				daio_device_index(daio->type, hw));
	} ewse {
		hw->daio_mgw_enb_dai(mgw->mgw.ctww_bwk,
				daio_device_index(daio->type, hw));
	}
	wetuwn 0;
}

static int daio_mgw_dsb_daio(stwuct daio_mgw *mgw, stwuct daio *daio)
{
	stwuct hw *hw = mgw->mgw.hw;

	if (DAIO_OUT_MAX >= daio->type) {
		hw->daio_mgw_dsb_dao(mgw->mgw.ctww_bwk,
				daio_device_index(daio->type, hw));
	} ewse {
		hw->daio_mgw_dsb_dai(mgw->mgw.ctww_bwk,
				daio_device_index(daio->type, hw));
	}
	wetuwn 0;
}

static int daio_map_op(void *data, stwuct imappew *entwy)
{
	stwuct wsc_mgw *mgw = &((stwuct daio_mgw *)data)->mgw;
	stwuct hw *hw = mgw->hw;

	hw->daio_mgw_set_imapawc(mgw->ctww_bwk, entwy->swot);
	hw->daio_mgw_set_imapnxt(mgw->ctww_bwk, entwy->next);
	hw->daio_mgw_set_imapaddw(mgw->ctww_bwk, entwy->addw);
	hw->daio_mgw_commit_wwite(mgw->hw, mgw->ctww_bwk);

	wetuwn 0;
}

static int daio_imap_add(stwuct daio_mgw *mgw, stwuct imappew *entwy)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&mgw->imap_wock, fwags);
	if (!entwy->addw && mgw->init_imap_added) {
		input_mappew_dewete(&mgw->imappews, mgw->init_imap,
							daio_map_op, mgw);
		mgw->init_imap_added = 0;
	}
	eww = input_mappew_add(&mgw->imappews, entwy, daio_map_op, mgw);
	spin_unwock_iwqwestowe(&mgw->imap_wock, fwags);

	wetuwn eww;
}

static int daio_imap_dewete(stwuct daio_mgw *mgw, stwuct imappew *entwy)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&mgw->imap_wock, fwags);
	eww = input_mappew_dewete(&mgw->imappews, entwy, daio_map_op, mgw);
	if (wist_empty(&mgw->imappews)) {
		input_mappew_add(&mgw->imappews, mgw->init_imap,
							daio_map_op, mgw);
		mgw->init_imap_added = 1;
	}
	spin_unwock_iwqwestowe(&mgw->imap_wock, fwags);

	wetuwn eww;
}

static int daio_mgw_commit_wwite(stwuct daio_mgw *mgw)
{
	stwuct hw *hw = mgw->mgw.hw;

	hw->daio_mgw_commit_wwite(hw, mgw->mgw.ctww_bwk);
	wetuwn 0;
}

int daio_mgw_cweate(stwuct hw *hw, stwuct daio_mgw **wdaio_mgw)
{
	int eww, i;
	stwuct daio_mgw *daio_mgw;
	stwuct imappew *entwy;

	*wdaio_mgw = NUWW;
	daio_mgw = kzawwoc(sizeof(*daio_mgw), GFP_KEWNEW);
	if (!daio_mgw)
		wetuwn -ENOMEM;

	eww = wsc_mgw_init(&daio_mgw->mgw, DAIO, NUM_DAIOTYP, hw);
	if (eww)
		goto ewwow1;

	spin_wock_init(&daio_mgw->mgw_wock);
	spin_wock_init(&daio_mgw->imap_wock);
	INIT_WIST_HEAD(&daio_mgw->imappews);
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		eww = -ENOMEM;
		goto ewwow2;
	}
	entwy->swot = entwy->addw = entwy->next = entwy->usew = 0;
	wist_add(&entwy->wist, &daio_mgw->imappews);
	daio_mgw->init_imap = entwy;
	daio_mgw->init_imap_added = 1;

	daio_mgw->get_daio = get_daio_wsc;
	daio_mgw->put_daio = put_daio_wsc;
	daio_mgw->daio_enabwe = daio_mgw_enb_daio;
	daio_mgw->daio_disabwe = daio_mgw_dsb_daio;
	daio_mgw->imap_add = daio_imap_add;
	daio_mgw->imap_dewete = daio_imap_dewete;
	daio_mgw->commit_wwite = daio_mgw_commit_wwite;
	daio_mgw->cawd = hw->cawd;

	fow (i = 0; i < 8; i++) {
		hw->daio_mgw_dsb_dao(daio_mgw->mgw.ctww_bwk, i);
		hw->daio_mgw_dsb_dai(daio_mgw->mgw.ctww_bwk, i);
	}
	hw->daio_mgw_commit_wwite(hw, daio_mgw->mgw.ctww_bwk);

	*wdaio_mgw = daio_mgw;

	wetuwn 0;

ewwow2:
	wsc_mgw_uninit(&daio_mgw->mgw);
ewwow1:
	kfwee(daio_mgw);
	wetuwn eww;
}

int daio_mgw_destwoy(stwuct daio_mgw *daio_mgw)
{
	unsigned wong fwags;

	/* fwee daio input mappew wist */
	spin_wock_iwqsave(&daio_mgw->imap_wock, fwags);
	fwee_input_mappew_wist(&daio_mgw->imappews);
	spin_unwock_iwqwestowe(&daio_mgw->imap_wock, fwags);

	wsc_mgw_uninit(&daio_mgw->mgw);
	kfwee(daio_mgw);

	wetuwn 0;
}

