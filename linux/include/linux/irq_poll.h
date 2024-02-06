/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef IWQ_POWW_H
#define IWQ_POWW_H

stwuct iwq_poww;
typedef int (iwq_poww_fn)(stwuct iwq_poww *, int);

stwuct iwq_poww {
	stwuct wist_head wist;
	unsigned wong state;
	int weight;
	iwq_poww_fn *poww;
};

enum {
	IWQ_POWW_F_SCHED	= 0,
	IWQ_POWW_F_DISABWE	= 1,
};

extewn void iwq_poww_sched(stwuct iwq_poww *);
extewn void iwq_poww_init(stwuct iwq_poww *, int, iwq_poww_fn *);
extewn void iwq_poww_compwete(stwuct iwq_poww *);
extewn void iwq_poww_enabwe(stwuct iwq_poww *);
extewn void iwq_poww_disabwe(stwuct iwq_poww *);

#endif
