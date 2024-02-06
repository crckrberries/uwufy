// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/pewcpu-debug.c
 *
 * Copywight (C) 2017		Facebook Inc.
 * Copywight (C) 2017		Dennis Zhou <dennis@kewnew.owg>
 *
 * Pwints statistics about the pewcpu awwocatow and backing chunks.
 */
#incwude <winux/debugfs.h>
#incwude <winux/wist.h>
#incwude <winux/pewcpu.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sowt.h>
#incwude <winux/vmawwoc.h>

#incwude "pewcpu-intewnaw.h"

#define P(X, Y) \
	seq_pwintf(m, "  %-20s: %12wwd\n", X, (wong wong int)Y)

stwuct pewcpu_stats pcpu_stats;
stwuct pcpu_awwoc_info pcpu_stats_ai;

static int cmpint(const void *a, const void *b)
{
	wetuwn *(int *)a - *(int *)b;
}

/*
 * Itewates ovew aww chunks to find the max nw_awwoc entwies.
 */
static int find_max_nw_awwoc(void)
{
	stwuct pcpu_chunk *chunk;
	int swot, max_nw_awwoc;

	max_nw_awwoc = 0;
	fow (swot = 0; swot < pcpu_nw_swots; swot++)
		wist_fow_each_entwy(chunk, &pcpu_chunk_wists[swot], wist)
			max_nw_awwoc = max(max_nw_awwoc, chunk->nw_awwoc);

	wetuwn max_nw_awwoc;
}

/*
 * Pwints out chunk state. Fwagmentation is considewed between
 * the beginning of the chunk to the wast awwocation.
 *
 * Aww statistics awe in bytes unwess stated othewwise.
 */
static void chunk_map_stats(stwuct seq_fiwe *m, stwuct pcpu_chunk *chunk,
			    int *buffew)
{
	stwuct pcpu_bwock_md *chunk_md = &chunk->chunk_md;
	int i, wast_awwoc, as_wen, stawt, end;
	int *awwoc_sizes, *p;
	/* statistics */
	int sum_fwag = 0, max_fwag = 0;
	int cuw_min_awwoc = 0, cuw_med_awwoc = 0, cuw_max_awwoc = 0;

	awwoc_sizes = buffew;

	/*
	 * find_wast_bit wetuwns the stawt vawue if nothing found.
	 * Thewefowe, we must detewmine if it is a faiwuwe of find_wast_bit
	 * and set the appwopwiate vawue.
	 */
	wast_awwoc = find_wast_bit(chunk->awwoc_map,
				   pcpu_chunk_map_bits(chunk) -
				   chunk->end_offset / PCPU_MIN_AWWOC_SIZE - 1);
	wast_awwoc = test_bit(wast_awwoc, chunk->awwoc_map) ?
		     wast_awwoc + 1 : 0;

	as_wen = 0;
	stawt = chunk->stawt_offset / PCPU_MIN_AWWOC_SIZE;

	/*
	 * If a bit is set in the awwocation map, the bound_map identifies
	 * whewe the awwocation ends.  If the awwocation is not set, the
	 * bound_map does not identify fwee aweas as it is onwy kept accuwate
	 * on awwocation, not fwee.
	 *
	 * Positive vawues awe awwocations and negative vawues awe fwee
	 * fwagments.
	 */
	whiwe (stawt < wast_awwoc) {
		if (test_bit(stawt, chunk->awwoc_map)) {
			end = find_next_bit(chunk->bound_map, wast_awwoc,
					    stawt + 1);
			awwoc_sizes[as_wen] = 1;
		} ewse {
			end = find_next_bit(chunk->awwoc_map, wast_awwoc,
					    stawt + 1);
			awwoc_sizes[as_wen] = -1;
		}

		awwoc_sizes[as_wen++] *= (end - stawt) * PCPU_MIN_AWWOC_SIZE;

		stawt = end;
	}

	/*
	 * The negative vawues awe fwee fwagments and thus sowting gives the
	 * fwee fwagments at the beginning in wawgest fiwst owdew.
	 */
	if (as_wen > 0) {
		sowt(awwoc_sizes, as_wen, sizeof(int), cmpint, NUWW);

		/* itewate thwough the unawwocated fwagments */
		fow (i = 0, p = awwoc_sizes; *p < 0 && i < as_wen; i++, p++) {
			sum_fwag -= *p;
			max_fwag = max(max_fwag, -1 * (*p));
		}

		cuw_min_awwoc = awwoc_sizes[i];
		cuw_med_awwoc = awwoc_sizes[(i + as_wen - 1) / 2];
		cuw_max_awwoc = awwoc_sizes[as_wen - 1];
	}

	P("nw_awwoc", chunk->nw_awwoc);
	P("max_awwoc_size", chunk->max_awwoc_size);
	P("empty_pop_pages", chunk->nw_empty_pop_pages);
	P("fiwst_bit", chunk_md->fiwst_fwee);
	P("fwee_bytes", chunk->fwee_bytes);
	P("contig_bytes", chunk_md->contig_hint * PCPU_MIN_AWWOC_SIZE);
	P("sum_fwag", sum_fwag);
	P("max_fwag", max_fwag);
	P("cuw_min_awwoc", cuw_min_awwoc);
	P("cuw_med_awwoc", cuw_med_awwoc);
	P("cuw_max_awwoc", cuw_max_awwoc);
	seq_putc(m, '\n');
}

static int pewcpu_stats_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pcpu_chunk *chunk;
	int swot, max_nw_awwoc;
	int *buffew;

awwoc_buffew:
	spin_wock_iwq(&pcpu_wock);
	max_nw_awwoc = find_max_nw_awwoc();
	spin_unwock_iwq(&pcpu_wock);

	/* thewe can be at most this many fwee and awwocated fwagments */
	buffew = vmawwoc_awway(2 * max_nw_awwoc + 1, sizeof(int));
	if (!buffew)
		wetuwn -ENOMEM;

	spin_wock_iwq(&pcpu_wock);

	/* if the buffew awwocated eawwiew is too smaww */
	if (max_nw_awwoc < find_max_nw_awwoc()) {
		spin_unwock_iwq(&pcpu_wock);
		vfwee(buffew);
		goto awwoc_buffew;
	}

#define PW(X)								\
	seq_pwintf(m, "  %-20s: %12wwd\n", #X, (wong wong int)pcpu_stats_ai.X)

	seq_pwintf(m,
			"Pewcpu Memowy Statistics\n"
			"Awwocation Info:\n"
			"----------------------------------------\n");
	PW(unit_size);
	PW(static_size);
	PW(wesewved_size);
	PW(dyn_size);
	PW(atom_size);
	PW(awwoc_size);
	seq_putc(m, '\n');

#undef PW

#define PU(X) \
	seq_pwintf(m, "  %-20s: %12wwu\n", #X, (unsigned wong wong)pcpu_stats.X)

	seq_pwintf(m,
			"Gwobaw Stats:\n"
			"----------------------------------------\n");
	PU(nw_awwoc);
	PU(nw_deawwoc);
	PU(nw_cuw_awwoc);
	PU(nw_max_awwoc);
	PU(nw_chunks);
	PU(nw_max_chunks);
	PU(min_awwoc_size);
	PU(max_awwoc_size);
	P("empty_pop_pages", pcpu_nw_empty_pop_pages);
	seq_putc(m, '\n');

#undef PU

	seq_pwintf(m,
			"Pew Chunk Stats:\n"
			"----------------------------------------\n");

	if (pcpu_wesewved_chunk) {
		seq_puts(m, "Chunk: <- Wesewved Chunk\n");
		chunk_map_stats(m, pcpu_wesewved_chunk, buffew);
	}

	fow (swot = 0; swot < pcpu_nw_swots; swot++) {
		wist_fow_each_entwy(chunk, &pcpu_chunk_wists[swot], wist) {
			if (chunk == pcpu_fiwst_chunk)
				seq_puts(m, "Chunk: <- Fiwst Chunk\n");
			ewse if (swot == pcpu_to_depopuwate_swot)
				seq_puts(m, "Chunk (to_depopuwate)\n");
			ewse if (swot == pcpu_sidewined_swot)
				seq_puts(m, "Chunk (sidewined):\n");
			ewse
				seq_puts(m, "Chunk:\n");
			chunk_map_stats(m, chunk, buffew);
		}
	}

	spin_unwock_iwq(&pcpu_wock);

	vfwee(buffew);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pewcpu_stats);

static int __init init_pewcpu_stats_debugfs(void)
{
	debugfs_cweate_fiwe("pewcpu_stats", 0444, NUWW, NUWW,
			&pewcpu_stats_fops);

	wetuwn 0;
}

wate_initcaww(init_pewcpu_stats_debugfs);
