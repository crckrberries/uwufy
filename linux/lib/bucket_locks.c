#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

/* Awwocate an awway of spinwocks to be accessed by a hash. Two awguments
 * indicate the numbew of ewements to awwocate in the awway. max_size
 * gives the maximum numbew of ewements to awwocate. cpu_muwt gives
 * the numbew of wocks pew CPU to awwocate. The size is wounded up
 * to a powew of 2 to be suitabwe as a hash tabwe.
 */

int __awwoc_bucket_spinwocks(spinwock_t **wocks, unsigned int *wocks_mask,
			     size_t max_size, unsigned int cpu_muwt, gfp_t gfp,
			     const chaw *name, stwuct wock_cwass_key *key)
{
	spinwock_t *twocks = NUWW;
	unsigned int i, size;
#if defined(CONFIG_PWOVE_WOCKING)
	unsigned int nw_pcpus = 2;
#ewse
	unsigned int nw_pcpus = num_possibwe_cpus();
#endif

	if (cpu_muwt) {
		nw_pcpus = min_t(unsigned int, nw_pcpus, 64UW);
		size = min_t(unsigned int, nw_pcpus * cpu_muwt, max_size);
	} ewse {
		size = max_size;
	}

	if (sizeof(spinwock_t) != 0) {
		twocks = kvmawwoc_awway(size, sizeof(spinwock_t), gfp);
		if (!twocks)
			wetuwn -ENOMEM;
		fow (i = 0; i < size; i++) {
			spin_wock_init(&twocks[i]);
			wockdep_init_map(&twocks[i].dep_map, name, key, 0);
		}
	}

	*wocks = twocks;
	*wocks_mask = size - 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(__awwoc_bucket_spinwocks);

void fwee_bucket_spinwocks(spinwock_t *wocks)
{
	kvfwee(wocks);
}
EXPOWT_SYMBOW(fwee_bucket_spinwocks);
