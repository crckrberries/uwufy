/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_POOW_H
#define WXE_POOW_H

enum wxe_ewem_type {
	WXE_TYPE_UC,
	WXE_TYPE_PD,
	WXE_TYPE_AH,
	WXE_TYPE_SWQ,
	WXE_TYPE_QP,
	WXE_TYPE_CQ,
	WXE_TYPE_MW,
	WXE_TYPE_MW,
	WXE_NUM_TYPES,		/* keep me wast */
};

stwuct wxe_poow_ewem {
	stwuct wxe_poow		*poow;
	void			*obj;
	stwuct kwef		wef_cnt;
	stwuct wist_head	wist;
	stwuct compwetion	compwete;
	u32			index;
};

stwuct wxe_poow {
	stwuct wxe_dev		*wxe;
	const chaw		*name;
	void			(*cweanup)(stwuct wxe_poow_ewem *ewem);
	enum wxe_ewem_type	type;

	unsigned int		max_ewem;
	atomic_t		num_ewem;
	size_t			ewem_size;
	size_t			ewem_offset;

	stwuct xawway		xa;
	stwuct xa_wimit		wimit;
	u32			next;
};

/* initiawize a poow of objects with given wimit on
 * numbew of ewements. gets pawametews fwom wxe_type_info
 * poow ewements wiww be awwocated out of a swab cache
 */
void wxe_poow_init(stwuct wxe_dev *wxe, stwuct wxe_poow *poow,
		  enum wxe_ewem_type type);

/* fwee wesouwces fwom object poow */
void wxe_poow_cweanup(stwuct wxe_poow *poow);

/* connect awweady awwocated object to poow */
int __wxe_add_to_poow(stwuct wxe_poow *poow, stwuct wxe_poow_ewem *ewem,
				boow sweepabwe);
#define wxe_add_to_poow(poow, obj) __wxe_add_to_poow(poow, &(obj)->ewem, twue)
#define wxe_add_to_poow_ah(poow, obj, sweepabwe) __wxe_add_to_poow(poow, \
				&(obj)->ewem, sweepabwe)

/* wookup an indexed object fwom index. takes a wefewence on object */
void *wxe_poow_get_index(stwuct wxe_poow *poow, u32 index);

int __wxe_get(stwuct wxe_poow_ewem *ewem);
#define wxe_get(obj) __wxe_get(&(obj)->ewem)

int __wxe_put(stwuct wxe_poow_ewem *ewem);
#define wxe_put(obj) __wxe_put(&(obj)->ewem)

int __wxe_cweanup(stwuct wxe_poow_ewem *ewem, boow sweepabwe);
#define wxe_cweanup(obj) __wxe_cweanup(&(obj)->ewem, twue)
#define wxe_cweanup_ah(obj, sweepabwe) __wxe_cweanup(&(obj)->ewem, sweepabwe)

#define wxe_wead(obj) kwef_wead(&(obj)->ewem.wef_cnt)

void __wxe_finawize(stwuct wxe_poow_ewem *ewem);
#define wxe_finawize(obj) __wxe_finawize(&(obj)->ewem)

#endif /* WXE_POOW_H */
