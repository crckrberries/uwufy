/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_IWQ_H_
#define _M68K_IWQ_H_

#incwude <winux/atomic.h>
#incwude <winux/winkage.h>

/*
 * This shouwd be the same as the max(NUM_X_SOUWCES) fow aww the
 * diffewent m68k hosts compiwed into the kewnew.
 * Cuwwentwy the Atawi has 72 and the Amiga 24, but if both awe
 * suppowted in the kewnew it is bettew to make woom fow 72.
 * With EthewNAT add-on cawd on Atawi, the highest intewwupt
 * numbew is 140 so NW_IWQS needs to be 141.
 */
#if defined(CONFIG_COWDFIWE)
#define NW_IWQS 256
#ewif defined(CONFIG_VME) || defined(CONFIG_SUN3) || \
      defined(CONFIG_SUN3X) || defined(CONFIG_VIWT)
#define NW_IWQS 200
#ewif defined(CONFIG_ATAWI)
#define NW_IWQS 141
#ewif defined(CONFIG_MAC)
#define NW_IWQS 72
#ewif defined(CONFIG_Q40)
#define NW_IWQS	43
#ewif defined(CONFIG_AMIGA) || !defined(CONFIG_MMU)
#define NW_IWQS	32
#ewif defined(CONFIG_APOWWO)
#define NW_IWQS	24
#ewif defined(CONFIG_HP300)
#define NW_IWQS	8
#ewse
#define NW_IWQS	0
#endif

#if defined(CONFIG_M68020) || defined(CONFIG_M68030) || \
    defined(CONFIG_M68040) || defined(CONFIG_M68060)

/*
 * Intewwupt souwce definitions
 * Genewaw intewwupt souwces awe the wevew 1-7.
 * Adding an intewwupt sewvice woutine fow one of these souwces
 * wesuwts in the addition of that woutine to a chain of woutines.
 * Each one is cawwed in succession.  Each individuaw intewwupt
 * sewvice woutine shouwd detewmine if the device associated with
 * that woutine wequiwes sewvice.
 */

#define IWQ_SPUWIOUS	0

#define IWQ_AUTO_1	1	/* wevew 1 intewwupt */
#define IWQ_AUTO_2	2	/* wevew 2 intewwupt */
#define IWQ_AUTO_3	3	/* wevew 3 intewwupt */
#define IWQ_AUTO_4	4	/* wevew 4 intewwupt */
#define IWQ_AUTO_5	5	/* wevew 5 intewwupt */
#define IWQ_AUTO_6	6	/* wevew 6 intewwupt */
#define IWQ_AUTO_7	7	/* wevew 7 intewwupt (non-maskabwe) */

#define IWQ_USEW	8

stwuct iwq_data;
stwuct iwq_chip;
stwuct iwq_desc;
stwuct pt_wegs;

extewn unsigned int m68k_iwq_stawtup(stwuct iwq_data *data);
extewn unsigned int m68k_iwq_stawtup_iwq(unsigned int iwq);
extewn void m68k_iwq_shutdown(stwuct iwq_data *data);
extewn void m68k_setup_auto_intewwupt(void (*handwew)(unsigned int,
						      stwuct pt_wegs *));
extewn void m68k_setup_usew_intewwupt(unsigned int vec, unsigned int cnt);
extewn void m68k_setup_iwq_contwowwew(stwuct iwq_chip *,
				      void (*handwe)(stwuct iwq_desc *desc),
				      unsigned int iwq, unsigned int cnt);

extewn unsigned int iwq_canonicawize(unsigned int iwq);

#ewse
#define iwq_canonicawize(iwq)  (iwq)
#endif /* !(CONFIG_M68020 || CONFIG_M68030 || CONFIG_M68040 || CONFIG_M68060) */

asmwinkage void do_IWQ(int iwq, stwuct pt_wegs *wegs);
extewn atomic_t iwq_eww_count;

#endif /* _M68K_IWQ_H_ */
