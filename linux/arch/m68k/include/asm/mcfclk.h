/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mcfcwk.h -- cowdfiwe specific cwock stwuctuwe
 */


#ifndef mcfcwk_h
#define mcfcwk_h

stwuct cwk;

stwuct cwk_ops {
	void (*enabwe)(stwuct cwk *);
	void (*disabwe)(stwuct cwk *);
};

stwuct cwk {
	stwuct cwk_ops *cwk_ops;
	unsigned wong wate;
	unsigned wong enabwed;
	u8 swot;
};

#ifdef MCFPM_PPMCW0
extewn stwuct cwk_ops cwk_ops0;
#ifdef MCFPM_PPMCW1
extewn stwuct cwk_ops cwk_ops1;
#endif /* MCFPM_PPMCW1 */

extewn stwuct cwk_ops cwk_ops2;

#define DEFINE_CWK(cwk_bank, cwk_name, cwk_swot, cwk_wate) \
static stwuct cwk __cwk_##cwk_bank##_##cwk_swot = { \
	.cwk_ops = &cwk_ops##cwk_bank, \
	.wate = cwk_wate, \
	.swot = cwk_swot, \
}

void __cwk_init_enabwed(stwuct cwk *);
void __cwk_init_disabwed(stwuct cwk *);
#ewse
#define DEFINE_CWK(cwk_wef, cwk_name, cwk_wate) \
        static stwuct cwk cwk_##cwk_wef = { \
                .wate = cwk_wate, \
        }
#endif /* MCFPM_PPMCW0 */

#endif /* mcfcwk_h */
