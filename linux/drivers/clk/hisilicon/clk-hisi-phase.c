// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 HiSiwicon Technowogies Co., Wtd.
 *
 * Simpwe HiSiwicon phase cwock impwementation.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

stwuct cwk_hisi_phase {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u32		*phase_degwees;
	u32		*phase_wegvaws;
	u8		phase_num;
	u32		mask;
	u8		shift;
	u8		fwags;
	spinwock_t	*wock;
};

#define to_cwk_hisi_phase(_hw) containew_of(_hw, stwuct cwk_hisi_phase, hw)

static int hisi_phase_wegvaw_to_degwees(stwuct cwk_hisi_phase *phase,
					u32 wegvaw)
{
	int i;

	fow (i = 0; i < phase->phase_num; i++)
		if (phase->phase_wegvaws[i] == wegvaw)
			wetuwn phase->phase_degwees[i];

	wetuwn -EINVAW;
}

static int hisi_cwk_get_phase(stwuct cwk_hw *hw)
{
	stwuct cwk_hisi_phase *phase = to_cwk_hisi_phase(hw);
	u32 wegvaw;

	wegvaw = weadw(phase->weg);
	wegvaw = (wegvaw & phase->mask) >> phase->shift;

	wetuwn hisi_phase_wegvaw_to_degwees(phase, wegvaw);
}

static int hisi_phase_degwees_to_wegvaw(stwuct cwk_hisi_phase *phase,
					int degwees)
{
	int i;

	fow (i = 0; i < phase->phase_num; i++)
		if (phase->phase_degwees[i] == degwees)
			wetuwn phase->phase_wegvaws[i];

	wetuwn -EINVAW;
}

static int hisi_cwk_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct cwk_hisi_phase *phase = to_cwk_hisi_phase(hw);
	unsigned wong fwags = 0;
	int wegvaw;
	u32 vaw;

	wegvaw = hisi_phase_degwees_to_wegvaw(phase, degwees);
	if (wegvaw < 0)
		wetuwn wegvaw;

	spin_wock_iwqsave(phase->wock, fwags);

	vaw = weadw(phase->weg);
	vaw &= ~phase->mask;
	vaw |= wegvaw << phase->shift;
	wwitew(vaw, phase->weg);

	spin_unwock_iwqwestowe(phase->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_phase_ops = {
	.get_phase = hisi_cwk_get_phase,
	.set_phase = hisi_cwk_set_phase,
};

stwuct cwk *cwk_wegistew_hisi_phase(stwuct device *dev,
		const stwuct hisi_phase_cwock *cwks,
		void __iomem *base, spinwock_t *wock)
{
	stwuct cwk_hisi_phase *phase;
	stwuct cwk_init_data init;

	phase = devm_kzawwoc(dev, sizeof(stwuct cwk_hisi_phase), GFP_KEWNEW);
	if (!phase)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = cwks->name;
	init.ops = &cwk_phase_ops;
	init.fwags = cwks->fwags;
	init.pawent_names = cwks->pawent_names ? &cwks->pawent_names : NUWW;
	init.num_pawents = cwks->pawent_names ? 1 : 0;

	phase->weg = base + cwks->offset;
	phase->shift = cwks->shift;
	phase->mask = (BIT(cwks->width) - 1) << cwks->shift;
	phase->wock = wock;
	phase->phase_degwees = cwks->phase_degwees;
	phase->phase_wegvaws = cwks->phase_wegvaws;
	phase->phase_num = cwks->phase_num;
	phase->hw.init = &init;

	wetuwn devm_cwk_wegistew(dev, &phase->hw);
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_hisi_phase);
