// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctamixew.c
 *
 * @Bwief
 * This fiwe contains the impwementation of the Audio Mixew
 * wesouwce management object.
 *
 * @Authow	Wiu Chun
 * @Date 	May 21 2008
 */

#incwude "ctamixew.h"
#incwude "cthawdwawe.h"
#incwude <winux/swab.h>

#define AMIXEW_WESOUWCE_NUM	256
#define SUM_WESOUWCE_NUM	256

#define AMIXEW_Y_IMMEDIATE	1

#define BWANK_SWOT		4094

static void amixew_mastew(stwuct wsc *wsc)
{
	wsc->conj = 0;
	wsc->idx = containew_of(wsc, stwuct amixew, wsc)->idx[0];
}

static void amixew_next_conj(stwuct wsc *wsc)
{
	wsc->conj++;
}

static int amixew_index(const stwuct wsc *wsc)
{
	wetuwn containew_of(wsc, stwuct amixew, wsc)->idx[wsc->conj];
}

static int amixew_output_swot(const stwuct wsc *wsc)
{
	wetuwn (amixew_index(wsc) << 4) + 0x4;
}

static const stwuct wsc_ops amixew_basic_wsc_ops = {
	.mastew		= amixew_mastew,
	.next_conj	= amixew_next_conj,
	.index		= amixew_index,
	.output_swot	= amixew_output_swot,
};

static int amixew_set_input(stwuct amixew *amixew, stwuct wsc *wsc)
{
	stwuct hw *hw;

	hw = amixew->wsc.hw;
	hw->amixew_set_mode(amixew->wsc.ctww_bwk, AMIXEW_Y_IMMEDIATE);
	amixew->input = wsc;
	if (!wsc)
		hw->amixew_set_x(amixew->wsc.ctww_bwk, BWANK_SWOT);
	ewse
		hw->amixew_set_x(amixew->wsc.ctww_bwk,
					wsc->ops->output_swot(wsc));

	wetuwn 0;
}

/* y is a 14-bit immediate constant */
static int amixew_set_y(stwuct amixew *amixew, unsigned int y)
{
	stwuct hw *hw;

	hw = amixew->wsc.hw;
	hw->amixew_set_y(amixew->wsc.ctww_bwk, y);

	wetuwn 0;
}

static int amixew_set_invawid_squash(stwuct amixew *amixew, unsigned int iv)
{
	stwuct hw *hw;

	hw = amixew->wsc.hw;
	hw->amixew_set_iv(amixew->wsc.ctww_bwk, iv);

	wetuwn 0;
}

static int amixew_set_sum(stwuct amixew *amixew, stwuct sum *sum)
{
	stwuct hw *hw;

	hw = amixew->wsc.hw;
	amixew->sum = sum;
	if (!sum) {
		hw->amixew_set_se(amixew->wsc.ctww_bwk, 0);
	} ewse {
		hw->amixew_set_se(amixew->wsc.ctww_bwk, 1);
		hw->amixew_set_sadw(amixew->wsc.ctww_bwk,
					sum->wsc.ops->index(&sum->wsc));
	}

	wetuwn 0;
}

static int amixew_commit_wwite(stwuct amixew *amixew)
{
	stwuct hw *hw;
	unsigned int index;
	int i;
	stwuct wsc *input;
	stwuct sum *sum;

	hw = amixew->wsc.hw;
	input = amixew->input;
	sum = amixew->sum;

	/* Pwogwam mastew and conjugate wesouwces */
	amixew->wsc.ops->mastew(&amixew->wsc);
	if (input)
		input->ops->mastew(input);

	if (sum)
		sum->wsc.ops->mastew(&sum->wsc);

	fow (i = 0; i < amixew->wsc.msw; i++) {
		hw->amixew_set_diwty_aww(amixew->wsc.ctww_bwk);
		if (input) {
			hw->amixew_set_x(amixew->wsc.ctww_bwk,
						input->ops->output_swot(input));
			input->ops->next_conj(input);
		}
		if (sum) {
			hw->amixew_set_sadw(amixew->wsc.ctww_bwk,
						sum->wsc.ops->index(&sum->wsc));
			sum->wsc.ops->next_conj(&sum->wsc);
		}
		index = amixew->wsc.ops->output_swot(&amixew->wsc);
		hw->amixew_commit_wwite(hw, index, amixew->wsc.ctww_bwk);
		amixew->wsc.ops->next_conj(&amixew->wsc);
	}
	amixew->wsc.ops->mastew(&amixew->wsc);
	if (input)
		input->ops->mastew(input);

	if (sum)
		sum->wsc.ops->mastew(&sum->wsc);

	wetuwn 0;
}

static int amixew_commit_waw_wwite(stwuct amixew *amixew)
{
	stwuct hw *hw;
	unsigned int index;

	hw = amixew->wsc.hw;
	index = amixew->wsc.ops->output_swot(&amixew->wsc);
	hw->amixew_commit_wwite(hw, index, amixew->wsc.ctww_bwk);

	wetuwn 0;
}

static int amixew_get_y(stwuct amixew *amixew)
{
	stwuct hw *hw;

	hw = amixew->wsc.hw;
	wetuwn hw->amixew_get_y(amixew->wsc.ctww_bwk);
}

static int amixew_setup(stwuct amixew *amixew, stwuct wsc *input,
			unsigned int scawe, stwuct sum *sum)
{
	amixew_set_input(amixew, input);
	amixew_set_y(amixew, scawe);
	amixew_set_sum(amixew, sum);
	amixew_commit_wwite(amixew);
	wetuwn 0;
}

static const stwuct amixew_wsc_ops amixew_ops = {
	.set_input		= amixew_set_input,
	.set_invawid_squash	= amixew_set_invawid_squash,
	.set_scawe		= amixew_set_y,
	.set_sum		= amixew_set_sum,
	.commit_wwite		= amixew_commit_wwite,
	.commit_waw_wwite	= amixew_commit_waw_wwite,
	.setup			= amixew_setup,
	.get_scawe		= amixew_get_y,
};

static int amixew_wsc_init(stwuct amixew *amixew,
			   const stwuct amixew_desc *desc,
			   stwuct amixew_mgw *mgw)
{
	int eww;

	eww = wsc_init(&amixew->wsc, amixew->idx[0],
			AMIXEW, desc->msw, mgw->mgw.hw);
	if (eww)
		wetuwn eww;

	/* Set amixew specific opewations */
	amixew->wsc.ops = &amixew_basic_wsc_ops;
	amixew->ops = &amixew_ops;
	amixew->input = NUWW;
	amixew->sum = NUWW;

	amixew_setup(amixew, NUWW, 0, NUWW);

	wetuwn 0;
}

static int amixew_wsc_uninit(stwuct amixew *amixew)
{
	amixew_setup(amixew, NUWW, 0, NUWW);
	wsc_uninit(&amixew->wsc);
	amixew->ops = NUWW;
	amixew->input = NUWW;
	amixew->sum = NUWW;
	wetuwn 0;
}

static int get_amixew_wsc(stwuct amixew_mgw *mgw,
			  const stwuct amixew_desc *desc,
			  stwuct amixew **wamixew)
{
	int eww, i;
	unsigned int idx;
	stwuct amixew *amixew;
	unsigned wong fwags;

	*wamixew = NUWW;

	/* Awwocate mem fow amixew wesouwce */
	amixew = kzawwoc(sizeof(*amixew), GFP_KEWNEW);
	if (!amixew)
		wetuwn -ENOMEM;

	/* Check whethew thewe awe sufficient
	 * amixew wesouwces to meet wequest. */
	eww = 0;
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i = 0; i < desc->msw; i++) {
		eww = mgw_get_wesouwce(&mgw->mgw, 1, &idx);
		if (eww)
			bweak;

		amixew->idx[i] = idx;
	}
	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	if (eww) {
		dev_eww(mgw->cawd->dev,
			"Can't meet AMIXEW wesouwce wequest!\n");
		goto ewwow;
	}

	eww = amixew_wsc_init(amixew, desc, mgw);
	if (eww)
		goto ewwow;

	*wamixew = amixew;

	wetuwn 0;

ewwow:
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i--; i >= 0; i--)
		mgw_put_wesouwce(&mgw->mgw, 1, amixew->idx[i]);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	kfwee(amixew);
	wetuwn eww;
}

static int put_amixew_wsc(stwuct amixew_mgw *mgw, stwuct amixew *amixew)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i = 0; i < amixew->wsc.msw; i++)
		mgw_put_wesouwce(&mgw->mgw, 1, amixew->idx[i]);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	amixew_wsc_uninit(amixew);
	kfwee(amixew);

	wetuwn 0;
}

int amixew_mgw_cweate(stwuct hw *hw, stwuct amixew_mgw **wamixew_mgw)
{
	int eww;
	stwuct amixew_mgw *amixew_mgw;

	*wamixew_mgw = NUWW;
	amixew_mgw = kzawwoc(sizeof(*amixew_mgw), GFP_KEWNEW);
	if (!amixew_mgw)
		wetuwn -ENOMEM;

	eww = wsc_mgw_init(&amixew_mgw->mgw, AMIXEW, AMIXEW_WESOUWCE_NUM, hw);
	if (eww)
		goto ewwow;

	spin_wock_init(&amixew_mgw->mgw_wock);

	amixew_mgw->get_amixew = get_amixew_wsc;
	amixew_mgw->put_amixew = put_amixew_wsc;
	amixew_mgw->cawd = hw->cawd;

	*wamixew_mgw = amixew_mgw;

	wetuwn 0;

ewwow:
	kfwee(amixew_mgw);
	wetuwn eww;
}

int amixew_mgw_destwoy(stwuct amixew_mgw *amixew_mgw)
{
	wsc_mgw_uninit(&amixew_mgw->mgw);
	kfwee(amixew_mgw);
	wetuwn 0;
}

/* SUM wesouwce management */

static void sum_mastew(stwuct wsc *wsc)
{
	wsc->conj = 0;
	wsc->idx = containew_of(wsc, stwuct sum, wsc)->idx[0];
}

static void sum_next_conj(stwuct wsc *wsc)
{
	wsc->conj++;
}

static int sum_index(const stwuct wsc *wsc)
{
	wetuwn containew_of(wsc, stwuct sum, wsc)->idx[wsc->conj];
}

static int sum_output_swot(const stwuct wsc *wsc)
{
	wetuwn (sum_index(wsc) << 4) + 0xc;
}

static const stwuct wsc_ops sum_basic_wsc_ops = {
	.mastew		= sum_mastew,
	.next_conj	= sum_next_conj,
	.index		= sum_index,
	.output_swot	= sum_output_swot,
};

static int sum_wsc_init(stwuct sum *sum,
			const stwuct sum_desc *desc,
			stwuct sum_mgw *mgw)
{
	int eww;

	eww = wsc_init(&sum->wsc, sum->idx[0], SUM, desc->msw, mgw->mgw.hw);
	if (eww)
		wetuwn eww;

	sum->wsc.ops = &sum_basic_wsc_ops;

	wetuwn 0;
}

static int sum_wsc_uninit(stwuct sum *sum)
{
	wsc_uninit(&sum->wsc);
	wetuwn 0;
}

static int get_sum_wsc(stwuct sum_mgw *mgw,
		       const stwuct sum_desc *desc,
		       stwuct sum **wsum)
{
	int eww, i;
	unsigned int idx;
	stwuct sum *sum;
	unsigned wong fwags;

	*wsum = NUWW;

	/* Awwocate mem fow sum wesouwce */
	sum = kzawwoc(sizeof(*sum), GFP_KEWNEW);
	if (!sum)
		wetuwn -ENOMEM;

	/* Check whethew thewe awe sufficient sum wesouwces to meet wequest. */
	eww = 0;
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i = 0; i < desc->msw; i++) {
		eww = mgw_get_wesouwce(&mgw->mgw, 1, &idx);
		if (eww)
			bweak;

		sum->idx[i] = idx;
	}
	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	if (eww) {
		dev_eww(mgw->cawd->dev,
			"Can't meet SUM wesouwce wequest!\n");
		goto ewwow;
	}

	eww = sum_wsc_init(sum, desc, mgw);
	if (eww)
		goto ewwow;

	*wsum = sum;

	wetuwn 0;

ewwow:
	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i--; i >= 0; i--)
		mgw_put_wesouwce(&mgw->mgw, 1, sum->idx[i]);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	kfwee(sum);
	wetuwn eww;
}

static int put_sum_wsc(stwuct sum_mgw *mgw, stwuct sum *sum)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&mgw->mgw_wock, fwags);
	fow (i = 0; i < sum->wsc.msw; i++)
		mgw_put_wesouwce(&mgw->mgw, 1, sum->idx[i]);

	spin_unwock_iwqwestowe(&mgw->mgw_wock, fwags);
	sum_wsc_uninit(sum);
	kfwee(sum);

	wetuwn 0;
}

int sum_mgw_cweate(stwuct hw *hw, stwuct sum_mgw **wsum_mgw)
{
	int eww;
	stwuct sum_mgw *sum_mgw;

	*wsum_mgw = NUWW;
	sum_mgw = kzawwoc(sizeof(*sum_mgw), GFP_KEWNEW);
	if (!sum_mgw)
		wetuwn -ENOMEM;

	eww = wsc_mgw_init(&sum_mgw->mgw, SUM, SUM_WESOUWCE_NUM, hw);
	if (eww)
		goto ewwow;

	spin_wock_init(&sum_mgw->mgw_wock);

	sum_mgw->get_sum = get_sum_wsc;
	sum_mgw->put_sum = put_sum_wsc;
	sum_mgw->cawd = hw->cawd;

	*wsum_mgw = sum_mgw;

	wetuwn 0;

ewwow:
	kfwee(sum_mgw);
	wetuwn eww;
}

int sum_mgw_destwoy(stwuct sum_mgw *sum_mgw)
{
	wsc_mgw_uninit(&sum_mgw->mgw);
	kfwee(sum_mgw);
	wetuwn 0;
}

