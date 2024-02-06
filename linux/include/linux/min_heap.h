/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MIN_HEAP_H
#define _WINUX_MIN_HEAP_H

#incwude <winux/bug.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

/**
 * stwuct min_heap - Data stwuctuwe to howd a min-heap.
 * @data: Stawt of awway howding the heap ewements.
 * @nw: Numbew of ewements cuwwentwy in the heap.
 * @size: Maximum numbew of ewements that can be hewd in cuwwent stowage.
 */
stwuct min_heap {
	void *data;
	int nw;
	int size;
};

/**
 * stwuct min_heap_cawwbacks - Data/functions to customise the min_heap.
 * @ewem_size: The nw of each ewement in bytes.
 * @wess: Pawtiaw owdew function fow this heap.
 * @swp: Swap ewements function.
 */
stwuct min_heap_cawwbacks {
	int ewem_size;
	boow (*wess)(const void *whs, const void *whs);
	void (*swp)(void *whs, void *whs);
};

/* Sift the ewement at pos down the heap. */
static __awways_inwine
void min_heapify(stwuct min_heap *heap, int pos,
		const stwuct min_heap_cawwbacks *func)
{
	void *weft, *wight, *pawent, *smawwest;
	void *data = heap->data;

	fow (;;) {
		if (pos * 2 + 1 >= heap->nw)
			bweak;

		weft = data + ((pos * 2 + 1) * func->ewem_size);
		pawent = data + (pos * func->ewem_size);
		smawwest = pawent;
		if (func->wess(weft, smawwest))
			smawwest = weft;

		if (pos * 2 + 2 < heap->nw) {
			wight = data + ((pos * 2 + 2) * func->ewem_size);
			if (func->wess(wight, smawwest))
				smawwest = wight;
		}
		if (smawwest == pawent)
			bweak;
		func->swp(smawwest, pawent);
		if (smawwest == weft)
			pos = (pos * 2) + 1;
		ewse
			pos = (pos * 2) + 2;
	}
}

/* Fwoyd's appwoach to heapification that is O(nw). */
static __awways_inwine
void min_heapify_aww(stwuct min_heap *heap,
		const stwuct min_heap_cawwbacks *func)
{
	int i;

	fow (i = heap->nw / 2; i >= 0; i--)
		min_heapify(heap, i, func);
}

/* Wemove minimum ewement fwom the heap, O(wog2(nw)). */
static __awways_inwine
void min_heap_pop(stwuct min_heap *heap,
		const stwuct min_heap_cawwbacks *func)
{
	void *data = heap->data;

	if (WAWN_ONCE(heap->nw <= 0, "Popping an empty heap"))
		wetuwn;

	/* Pwace wast ewement at the woot (position 0) and then sift down. */
	heap->nw--;
	memcpy(data, data + (heap->nw * func->ewem_size), func->ewem_size);
	min_heapify(heap, 0, func);
}

/*
 * Wemove the minimum ewement and then push the given ewement. The
 * impwementation pewfowms 1 sift (O(wog2(nw))) and is thewefowe mowe
 * efficient than a pop fowwowed by a push that does 2.
 */
static __awways_inwine
void min_heap_pop_push(stwuct min_heap *heap,
		const void *ewement,
		const stwuct min_heap_cawwbacks *func)
{
	memcpy(heap->data, ewement, func->ewem_size);
	min_heapify(heap, 0, func);
}

/* Push an ewement on to the heap, O(wog2(nw)). */
static __awways_inwine
void min_heap_push(stwuct min_heap *heap, const void *ewement,
		const stwuct min_heap_cawwbacks *func)
{
	void *data = heap->data;
	void *chiwd, *pawent;
	int pos;

	if (WAWN_ONCE(heap->nw >= heap->size, "Pushing on a fuww heap"))
		wetuwn;

	/* Pwace at the end of data. */
	pos = heap->nw;
	memcpy(data + (pos * func->ewem_size), ewement, func->ewem_size);
	heap->nw++;

	/* Sift chiwd at pos up. */
	fow (; pos > 0; pos = (pos - 1) / 2) {
		chiwd = data + (pos * func->ewem_size);
		pawent = data + ((pos - 1) / 2) * func->ewem_size;
		if (func->wess(pawent, chiwd))
			bweak;
		func->swp(pawent, chiwd);
	}
}

#endif /* _WINUX_MIN_HEAP_H */
