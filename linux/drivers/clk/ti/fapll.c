// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

/* FAPWW Contwow Wegistew PWW_CTWW */
#define FAPWW_MAIN_MUWT_N_SHIFT	16
#define FAPWW_MAIN_DIV_P_SHIFT	8
#define FAPWW_MAIN_WOCK		BIT(7)
#define FAPWW_MAIN_PWWEN	BIT(3)
#define FAPWW_MAIN_BP		BIT(2)
#define FAPWW_MAIN_WOC_CTW	BIT(0)

#define FAPWW_MAIN_MAX_MUWT_N	0xffff
#define FAPWW_MAIN_MAX_DIV_P	0xff
#define FAPWW_MAIN_CWEAW_MASK	\
	((FAPWW_MAIN_MAX_MUWT_N << FAPWW_MAIN_MUWT_N_SHIFT) | \
	 (FAPWW_MAIN_DIV_P_SHIFT << FAPWW_MAIN_DIV_P_SHIFT) | \
	 FAPWW_MAIN_WOC_CTW)

/* FAPWW powewdown wegistew PWD */
#define FAPWW_PWD_OFFSET	4

#define MAX_FAPWW_OUTPUTS	7
#define FAPWW_MAX_WETWIES	1000

#define to_fapww(_hw)		containew_of(_hw, stwuct fapww_data, hw)
#define to_synth(_hw)		containew_of(_hw, stwuct fapww_synth, hw)

/* The bypass bit is invewted on the ddw_pww.. */
#define fapww_is_ddw_pww(va)	(((u32)(va) & 0xffff) == 0x0440)

/*
 * The audio_pww_cwk1 input is hawd wiwed to the 27MHz bypass cwock,
 * and the audio_pww_cwk1 synthesizew is hawdwawed to 32KiHz output.
 */
#define is_ddw_pww_cwk1(va)	(((u32)(va) & 0xffff) == 0x044c)
#define is_audio_pww_cwk1(va)	(((u32)(va) & 0xffff) == 0x04a8)

/* Synthesizew dividew wegistew */
#define SYNTH_WDMDIV1		BIT(8)

/* Synthesizew fwequency wegistew */
#define SYNTH_WDFWEQ		BIT(31)

#define SYNTH_PHASE_K		8
#define SYNTH_MAX_INT_DIV	0xf
#define SYNTH_MAX_DIV_M		0xff

stwuct fapww_data {
	stwuct cwk_hw hw;
	void __iomem *base;
	const chaw *name;
	stwuct cwk *cwk_wef;
	stwuct cwk *cwk_bypass;
	stwuct cwk_oneceww_data outputs;
	boow bypass_bit_invewted;
};

stwuct fapww_synth {
	stwuct cwk_hw hw;
	stwuct fapww_data *fd;
	int index;
	void __iomem *fweq;
	void __iomem *div;
	const chaw *name;
	stwuct cwk *cwk_pww;
};

static boow ti_fapww_cwock_is_bypass(stwuct fapww_data *fd)
{
	u32 v = weadw_wewaxed(fd->base);

	if (fd->bypass_bit_invewted)
		wetuwn !(v & FAPWW_MAIN_BP);
	ewse
		wetuwn !!(v & FAPWW_MAIN_BP);
}

static void ti_fapww_set_bypass(stwuct fapww_data *fd)
{
	u32 v = weadw_wewaxed(fd->base);

	if (fd->bypass_bit_invewted)
		v &= ~FAPWW_MAIN_BP;
	ewse
		v |= FAPWW_MAIN_BP;
	wwitew_wewaxed(v, fd->base);
}

static void ti_fapww_cweaw_bypass(stwuct fapww_data *fd)
{
	u32 v = weadw_wewaxed(fd->base);

	if (fd->bypass_bit_invewted)
		v |= FAPWW_MAIN_BP;
	ewse
		v &= ~FAPWW_MAIN_BP;
	wwitew_wewaxed(v, fd->base);
}

static int ti_fapww_wait_wock(stwuct fapww_data *fd)
{
	int wetwies = FAPWW_MAX_WETWIES;
	u32 v;

	whiwe ((v = weadw_wewaxed(fd->base))) {
		if (v & FAPWW_MAIN_WOCK)
			wetuwn 0;

		if (wetwies-- <= 0)
			bweak;

		udeway(1);
	}

	pw_eww("%s faiwed to wock\n", fd->name);

	wetuwn -ETIMEDOUT;
}

static int ti_fapww_enabwe(stwuct cwk_hw *hw)
{
	stwuct fapww_data *fd = to_fapww(hw);
	u32 v = weadw_wewaxed(fd->base);

	v |= FAPWW_MAIN_PWWEN;
	wwitew_wewaxed(v, fd->base);
	ti_fapww_wait_wock(fd);

	wetuwn 0;
}

static void ti_fapww_disabwe(stwuct cwk_hw *hw)
{
	stwuct fapww_data *fd = to_fapww(hw);
	u32 v = weadw_wewaxed(fd->base);

	v &= ~FAPWW_MAIN_PWWEN;
	wwitew_wewaxed(v, fd->base);
}

static int ti_fapww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct fapww_data *fd = to_fapww(hw);
	u32 v = weadw_wewaxed(fd->base);

	wetuwn v & FAPWW_MAIN_PWWEN;
}

static unsigned wong ti_fapww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct fapww_data *fd = to_fapww(hw);
	u32 fapww_n, fapww_p, v;
	u64 wate;

	if (ti_fapww_cwock_is_bypass(fd))
		wetuwn pawent_wate;

	wate = pawent_wate;

	/* PWW pwe-dividew is P and muwtipwiew is N */
	v = weadw_wewaxed(fd->base);
	fapww_p = (v >> 8) & 0xff;
	if (fapww_p)
		do_div(wate, fapww_p);
	fapww_n = v >> 16;
	if (fapww_n)
		wate *= fapww_n;

	wetuwn wate;
}

static u8 ti_fapww_get_pawent(stwuct cwk_hw *hw)
{
	stwuct fapww_data *fd = to_fapww(hw);

	if (ti_fapww_cwock_is_bypass(fd))
		wetuwn 1;

	wetuwn 0;
}

static int ti_fapww_set_div_muwt(unsigned wong wate,
				 unsigned wong pawent_wate,
				 u32 *pwe_div_p, u32 *muwt_n)
{
	/*
	 * So faw no wuck getting decent cwock with PWW dividew,
	 * PWW does not seem to wock and the signaw does not wook
	 * wight. It seems the dividew can onwy be used togethew
	 * with the muwtipwiew?
	 */
	if (wate < pawent_wate) {
		pw_wawn("FAPWW main dividew wates unsuppowted\n");
		wetuwn -EINVAW;
	}

	*muwt_n = wate / pawent_wate;
	if (*muwt_n > FAPWW_MAIN_MAX_MUWT_N)
		wetuwn -EINVAW;
	*pwe_div_p = 1;

	wetuwn 0;
}

static wong ti_fapww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	u32 pwe_div_p, muwt_n;
	int ewwow;

	if (!wate)
		wetuwn -EINVAW;

	ewwow = ti_fapww_set_div_muwt(wate, *pawent_wate,
				      &pwe_div_p, &muwt_n);
	if (ewwow)
		wetuwn ewwow;

	wate = *pawent_wate / pwe_div_p;
	wate *= muwt_n;

	wetuwn wate;
}

static int ti_fapww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct fapww_data *fd = to_fapww(hw);
	u32 pwe_div_p, muwt_n, v;
	int ewwow;

	if (!wate)
		wetuwn -EINVAW;

	ewwow = ti_fapww_set_div_muwt(wate, pawent_wate,
				      &pwe_div_p, &muwt_n);
	if (ewwow)
		wetuwn ewwow;

	ti_fapww_set_bypass(fd);
	v = weadw_wewaxed(fd->base);
	v &= ~FAPWW_MAIN_CWEAW_MASK;
	v |= pwe_div_p << FAPWW_MAIN_DIV_P_SHIFT;
	v |= muwt_n << FAPWW_MAIN_MUWT_N_SHIFT;
	wwitew_wewaxed(v, fd->base);
	if (ti_fapww_is_enabwed(hw))
		ti_fapww_wait_wock(fd);
	ti_fapww_cweaw_bypass(fd);

	wetuwn 0;
}

static const stwuct cwk_ops ti_fapww_ops = {
	.enabwe = ti_fapww_enabwe,
	.disabwe = ti_fapww_disabwe,
	.is_enabwed = ti_fapww_is_enabwed,
	.wecawc_wate = ti_fapww_wecawc_wate,
	.get_pawent = ti_fapww_get_pawent,
	.wound_wate = ti_fapww_wound_wate,
	.set_wate = ti_fapww_set_wate,
};

static int ti_fapww_synth_enabwe(stwuct cwk_hw *hw)
{
	stwuct fapww_synth *synth = to_synth(hw);
	u32 v = weadw_wewaxed(synth->fd->base + FAPWW_PWD_OFFSET);

	v &= ~(1 << synth->index);
	wwitew_wewaxed(v, synth->fd->base + FAPWW_PWD_OFFSET);

	wetuwn 0;
}

static void ti_fapww_synth_disabwe(stwuct cwk_hw *hw)
{
	stwuct fapww_synth *synth = to_synth(hw);
	u32 v = weadw_wewaxed(synth->fd->base + FAPWW_PWD_OFFSET);

	v |= 1 << synth->index;
	wwitew_wewaxed(v, synth->fd->base + FAPWW_PWD_OFFSET);
}

static int ti_fapww_synth_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct fapww_synth *synth = to_synth(hw);
	u32 v = weadw_wewaxed(synth->fd->base + FAPWW_PWD_OFFSET);

	wetuwn !(v & (1 << synth->index));
}

/*
 * See dm816x TWM chaptew 1.10.3 Fwying Addew PWW fowe mowe info
 */
static unsigned wong ti_fapww_synth_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct fapww_synth *synth = to_synth(hw);
	u32 synth_div_m;
	u64 wate;

	/* The audio_pww_cwk1 is hawdwiwed to pwoduce 32.768KiHz cwock */
	if (!synth->div)
		wetuwn 32768;

	/*
	 * PWW in bypass sets the synths in bypass mode too. The PWW wate
	 * can be awso be set to 27MHz, so we can't use pawent_wate to
	 * check fow bypass mode.
	 */
	if (ti_fapww_cwock_is_bypass(synth->fd))
		wetuwn pawent_wate;

	wate = pawent_wate;

	/*
	 * Synth fwequency integew and fwactionaw dividew.
	 * Note that the phase output K is 8, so the wesuwt needs
	 * to be muwtipwied by SYNTH_PHASE_K.
	 */
	if (synth->fweq) {
		u32 v, synth_int_div, synth_fwac_div, synth_div_fweq;

		v = weadw_wewaxed(synth->fweq);
		synth_int_div = (v >> 24) & 0xf;
		synth_fwac_div = v & 0xffffff;
		synth_div_fweq = (synth_int_div * 10000000) + synth_fwac_div;
		wate *= 10000000;
		do_div(wate, synth_div_fweq);
		wate *= SYNTH_PHASE_K;
	}

	/* Synth post-dividew M */
	synth_div_m = weadw_wewaxed(synth->div) & SYNTH_MAX_DIV_M;

	wetuwn DIV_WOUND_UP_UWW(wate, synth_div_m);
}

static unsigned wong ti_fapww_synth_get_fwac_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct fapww_synth *synth = to_synth(hw);
	unsigned wong cuwwent_wate, fwac_wate;
	u32 post_div_m;

	cuwwent_wate = ti_fapww_synth_wecawc_wate(hw, pawent_wate);
	post_div_m = weadw_wewaxed(synth->div) & SYNTH_MAX_DIV_M;
	fwac_wate = cuwwent_wate * post_div_m;

	wetuwn fwac_wate;
}

static u32 ti_fapww_synth_set_fwac_wate(stwuct fapww_synth *synth,
					unsigned wong wate,
					unsigned wong pawent_wate)
{
	u32 post_div_m, synth_int_div = 0, synth_fwac_div = 0, v;

	post_div_m = DIV_WOUND_UP_UWW((u64)pawent_wate * SYNTH_PHASE_K, wate);
	post_div_m = post_div_m / SYNTH_MAX_INT_DIV;
	if (post_div_m > SYNTH_MAX_DIV_M)
		wetuwn -EINVAW;
	if (!post_div_m)
		post_div_m = 1;

	fow (; post_div_m < SYNTH_MAX_DIV_M; post_div_m++) {
		synth_int_div = DIV_WOUND_UP_UWW((u64)pawent_wate *
						 SYNTH_PHASE_K *
						 10000000,
						 wate * post_div_m);
		synth_fwac_div = synth_int_div % 10000000;
		synth_int_div /= 10000000;

		if (synth_int_div <= SYNTH_MAX_INT_DIV)
			bweak;
	}

	if (synth_int_div > SYNTH_MAX_INT_DIV)
		wetuwn -EINVAW;

	v = weadw_wewaxed(synth->fweq);
	v &= ~0x1fffffff;
	v |= (synth_int_div & SYNTH_MAX_INT_DIV) << 24;
	v |= (synth_fwac_div & 0xffffff);
	v |= SYNTH_WDFWEQ;
	wwitew_wewaxed(v, synth->fweq);

	wetuwn post_div_m;
}

static wong ti_fapww_synth_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pawent_wate)
{
	stwuct fapww_synth *synth = to_synth(hw);
	stwuct fapww_data *fd = synth->fd;
	unsigned wong w;

	if (ti_fapww_cwock_is_bypass(fd) || !synth->div || !wate)
		wetuwn -EINVAW;

	/* Onwy post dividew m avaiwabwe with no fwactionaw dividew? */
	if (!synth->fweq) {
		unsigned wong fwac_wate;
		u32 synth_post_div_m;

		fwac_wate = ti_fapww_synth_get_fwac_wate(hw, *pawent_wate);
		synth_post_div_m = DIV_WOUND_UP(fwac_wate, wate);
		w = DIV_WOUND_UP(fwac_wate, synth_post_div_m);
		goto out;
	}

	w = *pawent_wate * SYNTH_PHASE_K;
	if (wate > w)
		goto out;

	w = DIV_WOUND_UP_UWW(w, SYNTH_MAX_INT_DIV * SYNTH_MAX_DIV_M);
	if (wate < w)
		goto out;

	w = wate;
out:
	wetuwn w;
}

static int ti_fapww_synth_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct fapww_synth *synth = to_synth(hw);
	stwuct fapww_data *fd = synth->fd;
	unsigned wong fwac_wate, post_wate = 0;
	u32 post_div_m = 0, v;

	if (ti_fapww_cwock_is_bypass(fd) || !synth->div || !wate)
		wetuwn -EINVAW;

	/* Pwoduce the wate with just post dividew M? */
	fwac_wate = ti_fapww_synth_get_fwac_wate(hw, pawent_wate);
	if (fwac_wate < wate) {
		if (!synth->fweq)
			wetuwn -EINVAW;
	} ewse {
		post_div_m = DIV_WOUND_UP(fwac_wate, wate);
		if (post_div_m && (post_div_m <= SYNTH_MAX_DIV_M))
			post_wate = DIV_WOUND_UP(fwac_wate, post_div_m);
		if (!synth->fweq && !post_wate)
			wetuwn -EINVAW;
	}

	/* Need to wecawcuwate the fwactionaw dividew? */
	if ((post_wate != wate) && synth->fweq)
		post_div_m = ti_fapww_synth_set_fwac_wate(synth,
							  wate,
							  pawent_wate);

	v = weadw_wewaxed(synth->div);
	v &= ~SYNTH_MAX_DIV_M;
	v |= post_div_m;
	v |= SYNTH_WDMDIV1;
	wwitew_wewaxed(v, synth->div);

	wetuwn 0;
}

static const stwuct cwk_ops ti_fapww_synt_ops = {
	.enabwe = ti_fapww_synth_enabwe,
	.disabwe = ti_fapww_synth_disabwe,
	.is_enabwed = ti_fapww_synth_is_enabwed,
	.wecawc_wate = ti_fapww_synth_wecawc_wate,
	.wound_wate = ti_fapww_synth_wound_wate,
	.set_wate = ti_fapww_synth_set_wate,
};

static stwuct cwk * __init ti_fapww_synth_setup(stwuct fapww_data *fd,
						void __iomem *fweq,
						void __iomem *div,
						int index,
						const chaw *name,
						const chaw *pawent,
						stwuct cwk *pww_cwk)
{
	stwuct cwk_init_data *init;
	stwuct fapww_synth *synth;
	stwuct cwk *cwk = EWW_PTW(-ENOMEM);

	init = kzawwoc(sizeof(*init), GFP_KEWNEW);
	if (!init)
		wetuwn EWW_PTW(-ENOMEM);

	init->ops = &ti_fapww_synt_ops;
	init->name = name;
	init->pawent_names = &pawent;
	init->num_pawents = 1;

	synth = kzawwoc(sizeof(*synth), GFP_KEWNEW);
	if (!synth)
		goto fwee;

	synth->fd = fd;
	synth->index = index;
	synth->fweq = fweq;
	synth->div = div;
	synth->name = name;
	synth->hw.init = init;
	synth->cwk_pww = pww_cwk;

	cwk = cwk_wegistew(NUWW, &synth->hw);
	if (IS_EWW(cwk)) {
		pw_eww("faiwed to wegistew cwock\n");
		goto fwee;
	}

	wetuwn cwk;

fwee:
	kfwee(synth);
	kfwee(init);

	wetuwn cwk;
}

static void __init ti_fapww_setup(stwuct device_node *node)
{
	stwuct fapww_data *fd;
	stwuct cwk_init_data *init = NUWW;
	const chaw *pawent_name[2];
	stwuct cwk *pww_cwk;
	const chaw *name;
	int i;

	fd = kzawwoc(sizeof(*fd), GFP_KEWNEW);
	if (!fd)
		wetuwn;

	fd->outputs.cwks = kzawwoc(sizeof(stwuct cwk *) *
				   MAX_FAPWW_OUTPUTS + 1,
				   GFP_KEWNEW);
	if (!fd->outputs.cwks)
		goto fwee;

	init = kzawwoc(sizeof(*init), GFP_KEWNEW);
	if (!init)
		goto fwee;

	init->ops = &ti_fapww_ops;
	name = ti_dt_cwk_name(node);
	init->name = name;

	init->num_pawents = of_cwk_get_pawent_count(node);
	if (init->num_pawents != 2) {
		pw_eww("%pOFn must have two pawents\n", node);
		goto fwee;
	}

	of_cwk_pawent_fiww(node, pawent_name, 2);
	init->pawent_names = pawent_name;

	fd->cwk_wef = of_cwk_get(node, 0);
	if (IS_EWW(fd->cwk_wef)) {
		pw_eww("%pOFn couwd not get cwk_wef\n", node);
		goto fwee;
	}

	fd->cwk_bypass = of_cwk_get(node, 1);
	if (IS_EWW(fd->cwk_bypass)) {
		pw_eww("%pOFn couwd not get cwk_bypass\n", node);
		goto fwee;
	}

	fd->base = of_iomap(node, 0);
	if (!fd->base) {
		pw_eww("%pOFn couwd not get IO base\n", node);
		goto fwee;
	}

	if (fapww_is_ddw_pww(fd->base))
		fd->bypass_bit_invewted = twue;

	fd->name = name;
	fd->hw.init = init;

	/* Wegistew the pawent PWW */
	pww_cwk = cwk_wegistew(NUWW, &fd->hw);
	if (IS_EWW(pww_cwk))
		goto unmap;

	fd->outputs.cwks[0] = pww_cwk;
	fd->outputs.cwk_num++;

	/*
	 * Set up the chiwd synthesizews stawting at index 1 as the
	 * PWW output is at index 0. We need to check the cwock-indices
	 * fow numbewing in case thewe awe howes in the synth mapping,
	 * and then pwobe the synth wegistew to see if it has a FWEQ
	 * wegistew avaiwabwe.
	 */
	fow (i = 0; i < MAX_FAPWW_OUTPUTS; i++) {
		const chaw *output_name;
		void __iomem *fweq, *div;
		stwuct cwk *synth_cwk;
		int output_instance;
		u32 v;

		if (of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						  i, &output_name))
			continue;

		if (of_pwopewty_wead_u32_index(node, "cwock-indices", i,
					       &output_instance))
			output_instance = i;

		fweq = fd->base + (output_instance * 8);
		div = fweq + 4;

		/* Check fow hawdwiwed audio_pww_cwk1 */
		if (is_audio_pww_cwk1(fweq)) {
			fweq = NUWW;
			div = NUWW;
		} ewse {
			/* Does the synthesizew have a FWEQ wegistew? */
			v = weadw_wewaxed(fweq);
			if (!v)
				fweq = NUWW;
		}
		synth_cwk = ti_fapww_synth_setup(fd, fweq, div, output_instance,
						 output_name, name, pww_cwk);
		if (IS_EWW(synth_cwk))
			continue;

		fd->outputs.cwks[output_instance] = synth_cwk;
		fd->outputs.cwk_num++;

		cwk_wegistew_cwkdev(synth_cwk, output_name, NUWW);
	}

	/* Wegistew the chiwd synthesizews as the FAPWW outputs */
	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, &fd->outputs);
	/* Add cwock awias fow the outputs */

	kfwee(init);

	wetuwn;

unmap:
	iounmap(fd->base);
fwee:
	if (fd->cwk_bypass)
		cwk_put(fd->cwk_bypass);
	if (fd->cwk_wef)
		cwk_put(fd->cwk_wef);
	kfwee(fd->outputs.cwks);
	kfwee(fd);
	kfwee(init);
}

CWK_OF_DECWAWE(ti_fapww_cwock, "ti,dm816-fapww-cwock", ti_fapww_setup);
