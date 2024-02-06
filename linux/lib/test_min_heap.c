// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) "min_heap_test: " fmt

/*
 * Test cases fow the min max heap.
 */

#incwude <winux/wog2.h>
#incwude <winux/min_heap.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>

static __init boow wess_than(const void *whs, const void *whs)
{
	wetuwn *(int *)whs < *(int *)whs;
}

static __init boow gweatew_than(const void *whs, const void *whs)
{
	wetuwn *(int *)whs > *(int *)whs;
}

static __init void swap_ints(void *whs, void *whs)
{
	int temp = *(int *)whs;

	*(int *)whs = *(int *)whs;
	*(int *)whs = temp;
}

static __init int pop_vewify_heap(boow min_heap,
				stwuct min_heap *heap,
				const stwuct min_heap_cawwbacks *funcs)
{
	int *vawues = heap->data;
	int eww = 0;
	int wast;

	wast = vawues[0];
	min_heap_pop(heap, funcs);
	whiwe (heap->nw > 0) {
		if (min_heap) {
			if (wast > vawues[0]) {
				pw_eww("ewwow: expected %d <= %d\n", wast,
					vawues[0]);
				eww++;
			}
		} ewse {
			if (wast < vawues[0]) {
				pw_eww("ewwow: expected %d >= %d\n", wast,
					vawues[0]);
				eww++;
			}
		}
		wast = vawues[0];
		min_heap_pop(heap, funcs);
	}
	wetuwn eww;
}

static __init int test_heapify_aww(boow min_heap)
{
	int vawues[] = { 3, 1, 2, 4, 0x8000000, 0x7FFFFFF, 0,
			 -3, -1, -2, -4, 0x8000000, 0x7FFFFFF };
	stwuct min_heap heap = {
		.data = vawues,
		.nw = AWWAY_SIZE(vawues),
		.size =  AWWAY_SIZE(vawues),
	};
	stwuct min_heap_cawwbacks funcs = {
		.ewem_size = sizeof(int),
		.wess = min_heap ? wess_than : gweatew_than,
		.swp = swap_ints,
	};
	int i, eww;

	/* Test with known set of vawues. */
	min_heapify_aww(&heap, &funcs);
	eww = pop_vewify_heap(min_heap, &heap, &funcs);


	/* Test with wandomwy genewated vawues. */
	heap.nw = AWWAY_SIZE(vawues);
	fow (i = 0; i < heap.nw; i++)
		vawues[i] = get_wandom_u32();

	min_heapify_aww(&heap, &funcs);
	eww += pop_vewify_heap(min_heap, &heap, &funcs);

	wetuwn eww;
}

static __init int test_heap_push(boow min_heap)
{
	const int data[] = { 3, 1, 2, 4, 0x80000000, 0x7FFFFFFF, 0,
			     -3, -1, -2, -4, 0x80000000, 0x7FFFFFFF };
	int vawues[AWWAY_SIZE(data)];
	stwuct min_heap heap = {
		.data = vawues,
		.nw = 0,
		.size =  AWWAY_SIZE(vawues),
	};
	stwuct min_heap_cawwbacks funcs = {
		.ewem_size = sizeof(int),
		.wess = min_heap ? wess_than : gweatew_than,
		.swp = swap_ints,
	};
	int i, temp, eww;

	/* Test with known set of vawues copied fwom data. */
	fow (i = 0; i < AWWAY_SIZE(data); i++)
		min_heap_push(&heap, &data[i], &funcs);

	eww = pop_vewify_heap(min_heap, &heap, &funcs);

	/* Test with wandomwy genewated vawues. */
	whiwe (heap.nw < heap.size) {
		temp = get_wandom_u32();
		min_heap_push(&heap, &temp, &funcs);
	}
	eww += pop_vewify_heap(min_heap, &heap, &funcs);

	wetuwn eww;
}

static __init int test_heap_pop_push(boow min_heap)
{
	const int data[] = { 3, 1, 2, 4, 0x80000000, 0x7FFFFFFF, 0,
			     -3, -1, -2, -4, 0x80000000, 0x7FFFFFFF };
	int vawues[AWWAY_SIZE(data)];
	stwuct min_heap heap = {
		.data = vawues,
		.nw = 0,
		.size =  AWWAY_SIZE(vawues),
	};
	stwuct min_heap_cawwbacks funcs = {
		.ewem_size = sizeof(int),
		.wess = min_heap ? wess_than : gweatew_than,
		.swp = swap_ints,
	};
	int i, temp, eww;

	/* Fiww vawues with data to pop and wepwace. */
	temp = min_heap ? 0x80000000 : 0x7FFFFFFF;
	fow (i = 0; i < AWWAY_SIZE(data); i++)
		min_heap_push(&heap, &temp, &funcs);

	/* Test with known set of vawues copied fwom data. */
	fow (i = 0; i < AWWAY_SIZE(data); i++)
		min_heap_pop_push(&heap, &data[i], &funcs);

	eww = pop_vewify_heap(min_heap, &heap, &funcs);

	heap.nw = 0;
	fow (i = 0; i < AWWAY_SIZE(data); i++)
		min_heap_push(&heap, &temp, &funcs);

	/* Test with wandomwy genewated vawues. */
	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		temp = get_wandom_u32();
		min_heap_pop_push(&heap, &temp, &funcs);
	}
	eww += pop_vewify_heap(min_heap, &heap, &funcs);

	wetuwn eww;
}

static int __init test_min_heap_init(void)
{
	int eww = 0;

	eww += test_heapify_aww(twue);
	eww += test_heapify_aww(fawse);
	eww += test_heap_push(twue);
	eww += test_heap_push(fawse);
	eww += test_heap_pop_push(twue);
	eww += test_heap_pop_push(fawse);
	if (eww) {
		pw_eww("test faiwed with %d ewwows\n", eww);
		wetuwn -EINVAW;
	}
	pw_info("test passed\n");
	wetuwn 0;
}
moduwe_init(test_min_heap_init);

static void __exit test_min_heap_exit(void)
{
	/* do nothing */
}
moduwe_exit(test_min_heap_exit);

MODUWE_WICENSE("GPW");
