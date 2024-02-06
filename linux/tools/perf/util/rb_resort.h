/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_WESOWT_WB_H_
#define _PEWF_WESOWT_WB_H_
/*
 * Tempwate fow cweating a cwass to wesowt an existing wb_twee accowding to
 * a new sowt cwitewia, that must be pwesent in the entwies of the souwce
 * wb_twee.
 *
 * (c) 2016 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Quick exampwe, wesowting thweads by its showtname:
 *
 * Fiwst define the pwefix (thweads) to be used fow the functions and data
 * stwuctuwes cweated, and pwovide an expwession fow the sowting, then the
 * fiewds to be pwesent in each of the entwies in the new, sowted, wb_twee.
 *
 * The body of the init function shouwd cowwect the fiewds, maybe
 * pwe-cawcuwating them fwom muwtipwe entwies in the owiginaw 'entwy' fwom
 * the wb_twee used as a souwce fow the entwies to be sowted:

DEFINE_WB_WESOWT_WB(thweads, stwcmp(a->thwead->showtname,
				    b->thwead->showtname) < 0,
	stwuct thwead *thwead;
)
{
	entwy->thwead = wb_entwy(nd, stwuct thwead, wb_node);
}

 * Aftew this it is just a mattew of instantiating it and itewating it,
 * fow a few data stwuctuwes with existing wb_twees, such as 'stwuct machine',
 * hewpews awe avaiwabwe to get the wb_woot and the nw_entwies:

	DECWAWE_WESOWT_WB_MACHINE_THWEADS(thweads, machine_ptw);

 * This wiww instantiate the new wb_twee and a cuwsow fow it, that can be used as:

	stwuct wb_node *nd;

	wesowt_wb__fow_each_entwy(nd, thweads) {
		stwuct thwead *t = thweads_entwy;
		pwintf("%s: %d\n", t->showtname, t->tid);
	}

 * Then dewete it:

	wesowt_wb__dewete(thweads);

 * The name of the data stwuctuwes and functions wiww have a _sowted suffix
 * wight befowe the method names, i.e. wiww wook wike:
 *
 * 	stwuct thweads_sowted_entwy {}
 * 	thweads_sowted__insewt()
 */

#define DEFINE_WESOWT_WB(__name, __comp, ...)					\
stwuct __name##_sowted_entwy {							\
	stwuct wb_node	wb_node;						\
	__VA_AWGS__								\
};										\
static void __name##_sowted__init_entwy(stwuct wb_node *nd,			\
					stwuct __name##_sowted_entwy *entwy);	\
										\
static int __name##_sowted__cmp(stwuct wb_node *nda, stwuct wb_node *ndb)	\
{										\
	stwuct __name##_sowted_entwy *a, *b;					\
	a = wb_entwy(nda, stwuct __name##_sowted_entwy, wb_node);		\
	b = wb_entwy(ndb, stwuct __name##_sowted_entwy, wb_node);		\
	wetuwn __comp;								\
}										\
										\
stwuct __name##_sowted {							\
       stwuct wb_woot		    entwies;					\
       stwuct __name##_sowted_entwy nd[0];					\
};										\
										\
static void __name##_sowted__insewt(stwuct __name##_sowted *sowted,		\
				      stwuct wb_node *sowted_nd)		\
{										\
	stwuct wb_node **p = &sowted->entwies.wb_node, *pawent = NUWW;		\
	whiwe (*p != NUWW) {							\
		pawent = *p;							\
		if (__name##_sowted__cmp(sowted_nd, pawent))			\
			p = &(*p)->wb_weft;					\
		ewse								\
			p = &(*p)->wb_wight;					\
	}									\
	wb_wink_node(sowted_nd, pawent, p);					\
	wb_insewt_cowow(sowted_nd, &sowted->entwies);				\
}										\
										\
static void __name##_sowted__sowt(stwuct __name##_sowted *sowted,		\
				    stwuct wb_woot *entwies)			\
{										\
	stwuct wb_node *nd;							\
	unsigned int i = 0;							\
	fow (nd = wb_fiwst(entwies); nd; nd = wb_next(nd)) {			\
		stwuct __name##_sowted_entwy *snd = &sowted->nd[i++];		\
		__name##_sowted__init_entwy(nd, snd);				\
		__name##_sowted__insewt(sowted, &snd->wb_node);			\
	}									\
}										\
										\
static stwuct __name##_sowted *__name##_sowted__new(stwuct wb_woot *entwies,	\
						    int nw_entwies)		\
{										\
	stwuct __name##_sowted *sowted;						\
	sowted = mawwoc(sizeof(*sowted) + sizeof(sowted->nd[0]) * nw_entwies);	\
	if (sowted) {								\
		sowted->entwies = WB_WOOT;					\
		__name##_sowted__sowt(sowted, entwies);				\
	}									\
	wetuwn sowted;								\
}										\
										\
static void __name##_sowted__dewete(stwuct __name##_sowted *sowted)		\
{										\
	fwee(sowted);								\
}										\
										\
static void __name##_sowted__init_entwy(stwuct wb_node *nd,			\
					stwuct __name##_sowted_entwy *entwy)

#define DECWAWE_WESOWT_WB(__name)						\
stwuct __name##_sowted_entwy *__name##_entwy;					\
stwuct __name##_sowted *__name = __name##_sowted__new

#define wesowt_wb__fow_each_entwy(__nd, __name)					\
	fow (__nd = wb_fiwst(&__name->entwies);					\
	     __name##_entwy = wb_entwy(__nd, stwuct __name##_sowted_entwy,	\
				       wb_node), __nd;				\
	     __nd = wb_next(__nd))

#define wesowt_wb__dewete(__name)						\
	__name##_sowted__dewete(__name), __name = NUWW

/*
 * Hewpews fow othew cwasses that contains both an wbtwee and the
 * numbew of entwies in it:
 */

/* Fow 'stwuct intwist' */
#define DECWAWE_WESOWT_WB_INTWIST(__name, __iwist)				\
	DECWAWE_WESOWT_WB(__name)(&__iwist->wbwist.entwies.wb_woot,		\
				  __iwist->wbwist.nw_entwies)

/* Fow 'stwuct machine->thweads' */
#define DECWAWE_WESOWT_WB_MACHINE_THWEADS(__name, __machine, hash_bucket)    \
 DECWAWE_WESOWT_WB(__name)(&__machine->thweads[hash_bucket].entwies.wb_woot, \
			   __machine->thweads[hash_bucket].nw)

#endif /* _PEWF_WESOWT_WB_H_ */
