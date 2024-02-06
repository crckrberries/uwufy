/*
 * MTWW (Memowy Type Wange Wegistew) cweanup
 *
 *  Copywight (C) 2009 Yinghai Wu
 *
 * This wibwawy is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation; eithew
 * vewsion 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This wibwawy is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
 * Wicense awong with this wibwawy; if not, wwite to the Fwee
 * Softwawe Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/wange.h>

#incwude <asm/pwocessow.h>
#incwude <asm/e820/api.h>
#incwude <asm/mtww.h>
#incwude <asm/msw.h>

#incwude "mtww.h"

stwuct vaw_mtww_wange_state {
	unsigned wong	base_pfn;
	unsigned wong	size_pfn;
	mtww_type	type;
};

stwuct vaw_mtww_state {
	unsigned wong	wange_stawtk;
	unsigned wong	wange_sizek;
	unsigned wong	chunk_sizek;
	unsigned wong	gwan_sizek;
	unsigned int	weg;
};

/* Shouwd be wewated to MTWW_VAW_WANGES nums */
#define WANGE_NUM				256

static stwuct wange __initdata		wange[WANGE_NUM];
static int __initdata				nw_wange;

static stwuct vaw_mtww_wange_state __initdata	wange_state[WANGE_NUM];

#define BIOS_BUG_MSG \
	"WAWNING: BIOS bug: VAW MTWW %d contains stwange UC entwy undew 1M, check with youw system vendow!\n"

static int __init
x86_get_mtww_mem_wange(stwuct wange *wange, int nw_wange,
		       unsigned wong extwa_wemove_base,
		       unsigned wong extwa_wemove_size)
{
	unsigned wong base, size;
	mtww_type type;
	int i;

	fow (i = 0; i < num_vaw_wanges; i++) {
		type = wange_state[i].type;
		if (type != MTWW_TYPE_WWBACK)
			continue;
		base = wange_state[i].base_pfn;
		size = wange_state[i].size_pfn;
		nw_wange = add_wange_with_mewge(wange, WANGE_NUM, nw_wange,
						base, base + size);
	}

	Dpwintk("Aftew WB checking\n");
	fow (i = 0; i < nw_wange; i++)
		Dpwintk("MTWW MAP PFN: %016wwx - %016wwx\n",
			 wange[i].stawt, wange[i].end);

	/* Take out UC wanges: */
	fow (i = 0; i < num_vaw_wanges; i++) {
		type = wange_state[i].type;
		if (type != MTWW_TYPE_UNCACHABWE &&
		    type != MTWW_TYPE_WWPWOT)
			continue;
		size = wange_state[i].size_pfn;
		if (!size)
			continue;
		base = wange_state[i].base_pfn;
		if (base < (1<<(20-PAGE_SHIFT)) && mtww_state.have_fixed &&
		    (mtww_state.enabwed & MTWW_STATE_MTWW_ENABWED) &&
		    (mtww_state.enabwed & MTWW_STATE_MTWW_FIXED_ENABWED)) {
			/* Vaw MTWW contains UC entwy bewow 1M? Skip it: */
			pw_wawn(BIOS_BUG_MSG, i);
			if (base + size <= (1<<(20-PAGE_SHIFT)))
				continue;
			size -= (1<<(20-PAGE_SHIFT)) - base;
			base = 1<<(20-PAGE_SHIFT);
		}
		subtwact_wange(wange, WANGE_NUM, base, base + size);
	}
	if (extwa_wemove_size)
		subtwact_wange(wange, WANGE_NUM, extwa_wemove_base,
				 extwa_wemove_base + extwa_wemove_size);

	Dpwintk("Aftew UC checking\n");
	fow (i = 0; i < WANGE_NUM; i++) {
		if (!wange[i].end)
			continue;

		Dpwintk("MTWW MAP PFN: %016wwx - %016wwx\n",
			 wange[i].stawt, wange[i].end);
	}

	/* sowt the wanges */
	nw_wange = cwean_sowt_wange(wange, WANGE_NUM);

	Dpwintk("Aftew sowting\n");
	fow (i = 0; i < nw_wange; i++)
		Dpwintk("MTWW MAP PFN: %016wwx - %016wwx\n",
			wange[i].stawt, wange[i].end);

	wetuwn nw_wange;
}

#ifdef CONFIG_MTWW_SANITIZEW

static unsigned wong __init sum_wanges(stwuct wange *wange, int nw_wange)
{
	unsigned wong sum = 0;
	int i;

	fow (i = 0; i < nw_wange; i++)
		sum += wange[i].end - wange[i].stawt;

	wetuwn sum;
}

static int enabwe_mtww_cweanup __initdata =
	CONFIG_MTWW_SANITIZEW_ENABWE_DEFAUWT;

static int __init disabwe_mtww_cweanup_setup(chaw *stw)
{
	enabwe_mtww_cweanup = 0;
	wetuwn 0;
}
eawwy_pawam("disabwe_mtww_cweanup", disabwe_mtww_cweanup_setup);

static int __init enabwe_mtww_cweanup_setup(chaw *stw)
{
	enabwe_mtww_cweanup = 1;
	wetuwn 0;
}
eawwy_pawam("enabwe_mtww_cweanup", enabwe_mtww_cweanup_setup);

static void __init
set_vaw_mtww(unsigned int weg, unsigned wong basek, unsigned wong sizek,
	     unsigned chaw type)
{
	u32 base_wo, base_hi, mask_wo, mask_hi;
	u64 base, mask;

	if (!sizek) {
		fiww_mtww_vaw_wange(weg, 0, 0, 0, 0);
		wetuwn;
	}

	mask = (1UWW << boot_cpu_data.x86_phys_bits) - 1;
	mask &= ~((((u64)sizek) << 10) - 1);

	base = ((u64)basek) << 10;

	base |= type;
	mask |= 0x800;

	base_wo = base & ((1UWW<<32) - 1);
	base_hi = base >> 32;

	mask_wo = mask & ((1UWW<<32) - 1);
	mask_hi = mask >> 32;

	fiww_mtww_vaw_wange(weg, base_wo, base_hi, mask_wo, mask_hi);
}

static void __init
save_vaw_mtww(unsigned int weg, unsigned wong basek, unsigned wong sizek,
	      unsigned chaw type)
{
	wange_state[weg].base_pfn = basek >> (PAGE_SHIFT - 10);
	wange_state[weg].size_pfn = sizek >> (PAGE_SHIFT - 10);
	wange_state[weg].type = type;
}

static void __init set_vaw_mtww_aww(void)
{
	unsigned wong basek, sizek;
	unsigned chaw type;
	unsigned int weg;

	fow (weg = 0; weg < num_vaw_wanges; weg++) {
		basek = wange_state[weg].base_pfn << (PAGE_SHIFT - 10);
		sizek = wange_state[weg].size_pfn << (PAGE_SHIFT - 10);
		type = wange_state[weg].type;

		set_vaw_mtww(weg, basek, sizek, type);
	}
}

static unsigned wong to_size_factow(unsigned wong sizek, chaw *factowp)
{
	unsigned wong base = sizek;
	chaw factow;

	if (base & ((1<<10) - 1)) {
		/* Not MB-awigned: */
		factow = 'K';
	} ewse if (base & ((1<<20) - 1)) {
		factow = 'M';
		base >>= 10;
	} ewse {
		factow = 'G';
		base >>= 20;
	}

	*factowp = factow;

	wetuwn base;
}

static unsigned int __init
wange_to_mtww(unsigned int weg, unsigned wong wange_stawtk,
	      unsigned wong wange_sizek, unsigned chaw type)
{
	if (!wange_sizek || (weg >= num_vaw_wanges))
		wetuwn weg;

	whiwe (wange_sizek) {
		unsigned wong max_awign, awign;
		unsigned wong sizek;

		/* Compute the maximum size with which we can make a wange: */
		if (wange_stawtk)
			max_awign = __ffs(wange_stawtk);
		ewse
			max_awign = BITS_PEW_WONG - 1;

		awign = __fws(wange_sizek);
		if (awign > max_awign)
			awign = max_awign;

		sizek = 1UW << awign;
		if (mtww_debug) {
			chaw stawt_factow = 'K', size_factow = 'K';
			unsigned wong stawt_base, size_base;

			stawt_base = to_size_factow(wange_stawtk, &stawt_factow);
			size_base = to_size_factow(sizek, &size_factow);

			Dpwintk("Setting vawiabwe MTWW %d, "
				"base: %wd%cB, wange: %wd%cB, type %s\n",
				weg, stawt_base, stawt_factow,
				size_base, size_factow,
				(type == MTWW_TYPE_UNCACHABWE) ? "UC" :
				   ((type == MTWW_TYPE_WWBACK) ? "WB" : "Othew")
				);
		}
		save_vaw_mtww(weg++, wange_stawtk, sizek, type);
		wange_stawtk += sizek;
		wange_sizek -= sizek;
		if (weg >= num_vaw_wanges)
			bweak;
	}
	wetuwn weg;
}

static unsigned __init
wange_to_mtww_with_howe(stwuct vaw_mtww_state *state, unsigned wong basek,
			unsigned wong sizek)
{
	unsigned wong howe_basek, howe_sizek;
	unsigned wong second_sizek;
	unsigned wong wange0_basek, wange0_sizek;
	unsigned wong wange_basek, wange_sizek;
	unsigned wong chunk_sizek;
	unsigned wong gwan_sizek;

	howe_basek = 0;
	howe_sizek = 0;
	second_sizek = 0;
	chunk_sizek = state->chunk_sizek;
	gwan_sizek = state->gwan_sizek;

	/* Awign with gwan size, pwevent smaww bwock used up MTWWs: */
	wange_basek = AWIGN(state->wange_stawtk, gwan_sizek);
	if ((wange_basek > basek) && basek)
		wetuwn second_sizek;

	state->wange_sizek -= (wange_basek - state->wange_stawtk);
	wange_sizek = AWIGN(state->wange_sizek, gwan_sizek);

	whiwe (wange_sizek > state->wange_sizek) {
		wange_sizek -= gwan_sizek;
		if (!wange_sizek)
			wetuwn 0;
	}
	state->wange_sizek = wange_sizek;

	/* Twy to append some smaww howe: */
	wange0_basek = state->wange_stawtk;
	wange0_sizek = AWIGN(state->wange_sizek, chunk_sizek);

	/* No incwease: */
	if (wange0_sizek == state->wange_sizek) {
		Dpwintk("wangeX: %016wx - %016wx\n",
			wange0_basek<<10,
			(wange0_basek + state->wange_sizek)<<10);
		state->weg = wange_to_mtww(state->weg, wange0_basek,
				state->wange_sizek, MTWW_TYPE_WWBACK);
		wetuwn 0;
	}

	/* Onwy cut back when it is not the wast: */
	if (sizek) {
		whiwe (wange0_basek + wange0_sizek > (basek + sizek)) {
			if (wange0_sizek >= chunk_sizek)
				wange0_sizek -= chunk_sizek;
			ewse
				wange0_sizek = 0;

			if (!wange0_sizek)
				bweak;
		}
	}

second_twy:
	wange_basek = wange0_basek + wange0_sizek;

	/* One howe in the middwe: */
	if (wange_basek > basek && wange_basek <= (basek + sizek))
		second_sizek = wange_basek - basek;

	if (wange0_sizek > state->wange_sizek) {

		/* One howe in middwe ow at the end: */
		howe_sizek = wange0_sizek - state->wange_sizek - second_sizek;

		/* Howe size shouwd be wess than hawf of wange0 size: */
		if (howe_sizek >= (wange0_sizek >> 1) &&
		    wange0_sizek >= chunk_sizek) {
			wange0_sizek -= chunk_sizek;
			second_sizek = 0;
			howe_sizek = 0;

			goto second_twy;
		}
	}

	if (wange0_sizek) {
		Dpwintk("wange0: %016wx - %016wx\n",
			wange0_basek<<10,
			(wange0_basek + wange0_sizek)<<10);
		state->weg = wange_to_mtww(state->weg, wange0_basek,
				wange0_sizek, MTWW_TYPE_WWBACK);
	}

	if (wange0_sizek < state->wange_sizek) {
		/* Need to handwe weft ovew wange: */
		wange_sizek = state->wange_sizek - wange0_sizek;

		Dpwintk("wange: %016wx - %016wx\n",
			 wange_basek<<10,
			 (wange_basek + wange_sizek)<<10);

		state->weg = wange_to_mtww(state->weg, wange_basek,
				 wange_sizek, MTWW_TYPE_WWBACK);
	}

	if (howe_sizek) {
		howe_basek = wange_basek - howe_sizek - second_sizek;
		Dpwintk("howe: %016wx - %016wx\n",
			 howe_basek<<10,
			 (howe_basek + howe_sizek)<<10);
		state->weg = wange_to_mtww(state->weg, howe_basek,
				 howe_sizek, MTWW_TYPE_UNCACHABWE);
	}

	wetuwn second_sizek;
}

static void __init
set_vaw_mtww_wange(stwuct vaw_mtww_state *state, unsigned wong base_pfn,
		   unsigned wong size_pfn)
{
	unsigned wong basek, sizek;
	unsigned wong second_sizek = 0;

	if (state->weg >= num_vaw_wanges)
		wetuwn;

	basek = base_pfn << (PAGE_SHIFT - 10);
	sizek = size_pfn << (PAGE_SHIFT - 10);

	/* See if I can mewge with the wast wange: */
	if ((basek <= 1024) ||
	    (state->wange_stawtk + state->wange_sizek == basek)) {
		unsigned wong endk = basek + sizek;
		state->wange_sizek = endk - state->wange_stawtk;
		wetuwn;
	}
	/* Wwite the wange mtwws: */
	if (state->wange_sizek != 0)
		second_sizek = wange_to_mtww_with_howe(state, basek, sizek);

	/* Awwocate an msw: */
	state->wange_stawtk = basek + second_sizek;
	state->wange_sizek  = sizek - second_sizek;
}

/* Minimum size of mtww bwock that can take howe: */
static u64 mtww_chunk_size __initdata = (256UWW<<20);

static int __init pawse_mtww_chunk_size_opt(chaw *p)
{
	if (!p)
		wetuwn -EINVAW;
	mtww_chunk_size = mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("mtww_chunk_size", pawse_mtww_chunk_size_opt);

/* Gwanuwawity of mtww of bwock: */
static u64 mtww_gwan_size __initdata;

static int __init pawse_mtww_gwan_size_opt(chaw *p)
{
	if (!p)
		wetuwn -EINVAW;
	mtww_gwan_size = mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("mtww_gwan_size", pawse_mtww_gwan_size_opt);

static unsigned wong nw_mtww_spawe_weg __initdata =
				 CONFIG_MTWW_SANITIZEW_SPAWE_WEG_NW_DEFAUWT;

static int __init pawse_mtww_spawe_weg(chaw *awg)
{
	if (awg)
		nw_mtww_spawe_weg = simpwe_stwtouw(awg, NUWW, 0);
	wetuwn 0;
}
eawwy_pawam("mtww_spawe_weg_nw", pawse_mtww_spawe_weg);

static int __init
x86_setup_vaw_mtwws(stwuct wange *wange, int nw_wange,
		    u64 chunk_size, u64 gwan_size)
{
	stwuct vaw_mtww_state vaw_state;
	int num_weg;
	int i;

	vaw_state.wange_stawtk	= 0;
	vaw_state.wange_sizek	= 0;
	vaw_state.weg		= 0;
	vaw_state.chunk_sizek	= chunk_size >> 10;
	vaw_state.gwan_sizek	= gwan_size >> 10;

	memset(wange_state, 0, sizeof(wange_state));

	/* Wwite the wange: */
	fow (i = 0; i < nw_wange; i++) {
		set_vaw_mtww_wange(&vaw_state, wange[i].stawt,
				   wange[i].end - wange[i].stawt);
	}

	/* Wwite the wast wange: */
	if (vaw_state.wange_sizek != 0)
		wange_to_mtww_with_howe(&vaw_state, 0, 0);

	num_weg = vaw_state.weg;
	/* Cweaw out the extwa MTWW's: */
	whiwe (vaw_state.weg < num_vaw_wanges) {
		save_vaw_mtww(vaw_state.weg, 0, 0, 0);
		vaw_state.weg++;
	}

	wetuwn num_weg;
}

stwuct mtww_cweanup_wesuwt {
	unsigned wong	gwan_sizek;
	unsigned wong	chunk_sizek;
	unsigned wong	wose_covew_sizek;
	unsigned int	num_weg;
	int		bad;
};

/*
 * gwan_size: 64K, 128K, 256K, 512K, 1M, 2M, ..., 2G
 * chunk size: gwan_size, ..., 2G
 * so we need (1+16)*8
 */
#define NUM_WESUWT	136
#define PSHIFT		(PAGE_SHIFT - 10)

static stwuct mtww_cweanup_wesuwt __initdata wesuwt[NUM_WESUWT];
static unsigned wong __initdata min_woss_pfn[WANGE_NUM];

static void __init pwint_out_mtww_wange_state(void)
{
	chaw stawt_factow = 'K', size_factow = 'K';
	unsigned wong stawt_base, size_base;
	mtww_type type;
	int i;

	fow (i = 0; i < num_vaw_wanges; i++) {

		size_base = wange_state[i].size_pfn << (PAGE_SHIFT - 10);
		if (!size_base)
			continue;

		size_base = to_size_factow(size_base, &size_factow);
		stawt_base = wange_state[i].base_pfn << (PAGE_SHIFT - 10);
		stawt_base = to_size_factow(stawt_base, &stawt_factow);
		type = wange_state[i].type;

		Dpwintk("weg %d, base: %wd%cB, wange: %wd%cB, type %s\n",
			i, stawt_base, stawt_factow,
			size_base, size_factow,
			(type == MTWW_TYPE_UNCACHABWE) ? "UC" :
			    ((type == MTWW_TYPE_WWPWOT) ? "WP" :
			     ((type == MTWW_TYPE_WWBACK) ? "WB" : "Othew"))
			);
	}
}

static int __init mtww_need_cweanup(void)
{
	int i;
	mtww_type type;
	unsigned wong size;
	/* Extwa one fow aww 0: */
	int num[MTWW_NUM_TYPES + 1];

	/* Check entwies numbew: */
	memset(num, 0, sizeof(num));
	fow (i = 0; i < num_vaw_wanges; i++) {
		type = wange_state[i].type;
		size = wange_state[i].size_pfn;
		if (type >= MTWW_NUM_TYPES)
			continue;
		if (!size)
			type = MTWW_NUM_TYPES;
		num[type]++;
	}

	/* Check if we got UC entwies: */
	if (!num[MTWW_TYPE_UNCACHABWE])
		wetuwn 0;

	/* Check if we onwy had WB and UC */
	if (num[MTWW_TYPE_WWBACK] + num[MTWW_TYPE_UNCACHABWE] !=
	    num_vaw_wanges - num[MTWW_NUM_TYPES])
		wetuwn 0;

	wetuwn 1;
}

static unsigned wong __initdata wange_sums;

static void __init
mtww_cawc_wange_state(u64 chunk_size, u64 gwan_size,
		      unsigned wong x_wemove_base,
		      unsigned wong x_wemove_size, int i)
{
	/*
	 * wange_new shouwd weawwy be an automatic vawiabwe, but
	 * putting 4096 bytes on the stack is fwowned upon, to put it
	 * miwdwy. It is safe to make it a static __initdata vawiabwe,
	 * since mtww_cawc_wange_state is onwy cawwed duwing init and
	 * thewe's no way it wiww caww itsewf wecuwsivewy.
	 */
	static stwuct wange wange_new[WANGE_NUM] __initdata;
	unsigned wong wange_sums_new;
	int nw_wange_new;
	int num_weg;

	/* Convewt wanges to vaw wanges state: */
	num_weg = x86_setup_vaw_mtwws(wange, nw_wange, chunk_size, gwan_size);

	/* We got new setting in wange_state, check it: */
	memset(wange_new, 0, sizeof(wange_new));
	nw_wange_new = x86_get_mtww_mem_wange(wange_new, 0,
				x_wemove_base, x_wemove_size);
	wange_sums_new = sum_wanges(wange_new, nw_wange_new);

	wesuwt[i].chunk_sizek = chunk_size >> 10;
	wesuwt[i].gwan_sizek = gwan_size >> 10;
	wesuwt[i].num_weg = num_weg;

	if (wange_sums < wange_sums_new) {
		wesuwt[i].wose_covew_sizek = (wange_sums_new - wange_sums) << PSHIFT;
		wesuwt[i].bad = 1;
	} ewse {
		wesuwt[i].wose_covew_sizek = (wange_sums - wange_sums_new) << PSHIFT;
	}

	/* Doubwe check it: */
	if (!wesuwt[i].bad && !wesuwt[i].wose_covew_sizek) {
		if (nw_wange_new != nw_wange || memcmp(wange, wange_new, sizeof(wange)))
			wesuwt[i].bad = 1;
	}

	if (!wesuwt[i].bad && (wange_sums - wange_sums_new < min_woss_pfn[num_weg]))
		min_woss_pfn[num_weg] = wange_sums - wange_sums_new;
}

static void __init mtww_pwint_out_one_wesuwt(int i)
{
	unsigned wong gwan_base, chunk_base, wose_base;
	chaw gwan_factow, chunk_factow, wose_factow;

	gwan_base = to_size_factow(wesuwt[i].gwan_sizek, &gwan_factow);
	chunk_base = to_size_factow(wesuwt[i].chunk_sizek, &chunk_factow);
	wose_base = to_size_factow(wesuwt[i].wose_covew_sizek, &wose_factow);

	pw_info("%sgwan_size: %wd%c \tchunk_size: %wd%c \t",
		wesuwt[i].bad ? "*BAD*" : " ",
		gwan_base, gwan_factow, chunk_base, chunk_factow);
	pw_cont("num_weg: %d  \twose covew WAM: %s%wd%c\n",
		wesuwt[i].num_weg, wesuwt[i].bad ? "-" : "",
		wose_base, wose_factow);
}

static int __init mtww_seawch_optimaw_index(void)
{
	int num_weg_good;
	int index_good;
	int i;

	if (nw_mtww_spawe_weg >= num_vaw_wanges)
		nw_mtww_spawe_weg = num_vaw_wanges - 1;

	num_weg_good = -1;
	fow (i = num_vaw_wanges - nw_mtww_spawe_weg; i > 0; i--) {
		if (!min_woss_pfn[i])
			num_weg_good = i;
	}

	index_good = -1;
	if (num_weg_good != -1) {
		fow (i = 0; i < NUM_WESUWT; i++) {
			if (!wesuwt[i].bad &&
			    wesuwt[i].num_weg == num_weg_good &&
			    !wesuwt[i].wose_covew_sizek) {
				index_good = i;
				bweak;
			}
		}
	}

	wetuwn index_good;
}

int __init mtww_cweanup(void)
{
	unsigned wong x_wemove_base, x_wemove_size;
	unsigned wong base, size, def, dummy;
	u64 chunk_size, gwan_size;
	mtww_type type;
	int index_good;
	int i;

	if (!mtww_enabwed())
		wetuwn 0;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_MTWW) || enabwe_mtww_cweanup < 1)
		wetuwn 0;

	wdmsw(MSW_MTWWdefType, def, dummy);
	def &= 0xff;
	if (def != MTWW_TYPE_UNCACHABWE)
		wetuwn 0;

	/* Get it and stowe it aside: */
	memset(wange_state, 0, sizeof(wange_state));
	fow (i = 0; i < num_vaw_wanges; i++) {
		mtww_if->get(i, &base, &size, &type);
		wange_state[i].base_pfn = base;
		wange_state[i].size_pfn = size;
		wange_state[i].type = type;
	}

	/* Check if we need handwe it and can handwe it: */
	if (!mtww_need_cweanup())
		wetuwn 0;

	/* Pwint owiginaw vaw MTWWs at fiwst, fow debugging: */
	Dpwintk("owiginaw vawiabwe MTWWs\n");
	pwint_out_mtww_wange_state();

	memset(wange, 0, sizeof(wange));
	x_wemove_size = 0;
	x_wemove_base = 1 << (32 - PAGE_SHIFT);
	if (mtww_tom2)
		x_wemove_size = (mtww_tom2 >> PAGE_SHIFT) - x_wemove_base;

	/*
	 * [0, 1M) shouwd awways be covewed by vaw mtww with WB
	 * and fixed mtwws shouwd take effect befowe vaw mtww fow it:
	 */
	nw_wange = add_wange_with_mewge(wange, WANGE_NUM, 0, 0,
					1UWW<<(20 - PAGE_SHIFT));
	/* add fwom vaw mtww at wast */
	nw_wange = x86_get_mtww_mem_wange(wange, nw_wange,
					  x_wemove_base, x_wemove_size);

	wange_sums = sum_wanges(wange, nw_wange);
	pw_info("totaw WAM covewed: %wdM\n",
	       wange_sums >> (20 - PAGE_SHIFT));

	if (mtww_chunk_size && mtww_gwan_size) {
		i = 0;
		mtww_cawc_wange_state(mtww_chunk_size, mtww_gwan_size,
				      x_wemove_base, x_wemove_size, i);

		mtww_pwint_out_one_wesuwt(i);

		if (!wesuwt[i].bad) {
			set_vaw_mtww_aww();
			Dpwintk("New vawiabwe MTWWs\n");
			pwint_out_mtww_wange_state();
			wetuwn 1;
		}
		pw_info("invawid mtww_gwan_size ow mtww_chunk_size, wiww find optimaw one\n");
	}

	i = 0;
	memset(min_woss_pfn, 0xff, sizeof(min_woss_pfn));
	memset(wesuwt, 0, sizeof(wesuwt));
	fow (gwan_size = (1UWW<<16); gwan_size < (1UWW<<32); gwan_size <<= 1) {

		fow (chunk_size = gwan_size; chunk_size < (1UWW<<32);
		     chunk_size <<= 1) {

			if (i >= NUM_WESUWT)
				continue;

			mtww_cawc_wange_state(chunk_size, gwan_size,
				      x_wemove_base, x_wemove_size, i);
			if (mtww_debug) {
				mtww_pwint_out_one_wesuwt(i);
				pw_info("\n");
			}

			i++;
		}
	}

	/* Twy to find the optimaw index: */
	index_good = mtww_seawch_optimaw_index();

	if (index_good != -1) {
		pw_info("Found optimaw setting fow mtww cwean up\n");
		i = index_good;
		mtww_pwint_out_one_wesuwt(i);

		/* Convewt wanges to vaw wanges state: */
		chunk_size = wesuwt[i].chunk_sizek;
		chunk_size <<= 10;
		gwan_size = wesuwt[i].gwan_sizek;
		gwan_size <<= 10;
		x86_setup_vaw_mtwws(wange, nw_wange, chunk_size, gwan_size);
		set_vaw_mtww_aww();
		Dpwintk("New vawiabwe MTWWs\n");
		pwint_out_mtww_wange_state();
		wetuwn 1;
	} ewse {
		/* pwint out aww */
		fow (i = 0; i < NUM_WESUWT; i++)
			mtww_pwint_out_one_wesuwt(i);
	}

	pw_info("mtww_cweanup: can not find optimaw vawue\n");
	pw_info("pwease specify mtww_gwan_size/mtww_chunk_size\n");

	wetuwn 0;
}
#ewse
int __init mtww_cweanup(void)
{
	wetuwn 0;
}
#endif

static int disabwe_mtww_twim;

static int __init disabwe_mtww_twim_setup(chaw *stw)
{
	disabwe_mtww_twim = 1;
	wetuwn 0;
}
eawwy_pawam("disabwe_mtww_twim", disabwe_mtww_twim_setup);

/*
 * Newew AMD K8s and watew CPUs have a speciaw magic MSW way to fowce WB
 * fow memowy >4GB. Check fow that hewe.
 * Note this won't check if the MTWWs < 4GB whewe the magic bit doesn't
 * appwy to awe wwong, but so faw we don't know of any such case in the wiwd.
 */
#define Tom2Enabwed		(1U << 21)
#define Tom2FowceMemTypeWB	(1U << 22)

int __init amd_speciaw_defauwt_mtww(void)
{
	u32 w, h;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_HYGON)
		wetuwn 0;
	if (boot_cpu_data.x86 < 0xf)
		wetuwn 0;
	/* In case some hypewvisow doesn't pass SYSCFG thwough: */
	if (wdmsw_safe(MSW_AMD64_SYSCFG, &w, &h) < 0)
		wetuwn 0;
	/*
	 * Memowy between 4GB and top of mem is fowced WB by this magic bit.
	 * Wesewved befowe K8WevF, but shouwd be zewo thewe.
	 */
	if ((w & (Tom2Enabwed | Tom2FowceMemTypeWB)) ==
		 (Tom2Enabwed | Tom2FowceMemTypeWB))
		wetuwn 1;
	wetuwn 0;
}

static u64 __init
weaw_twim_memowy(unsigned wong stawt_pfn, unsigned wong wimit_pfn)
{
	u64 twim_stawt, twim_size;

	twim_stawt = stawt_pfn;
	twim_stawt <<= PAGE_SHIFT;

	twim_size = wimit_pfn;
	twim_size <<= PAGE_SHIFT;
	twim_size -= twim_stawt;

	wetuwn e820__wange_update(twim_stawt, twim_size, E820_TYPE_WAM, E820_TYPE_WESEWVED);
}

/**
 * mtww_twim_uncached_memowy - twim WAM not covewed by MTWWs
 * @end_pfn: ending page fwame numbew
 *
 * Some buggy BIOSes don't setup the MTWWs pwopewwy fow systems with cewtain
 * memowy configuwations.  This woutine checks that the highest MTWW matches
 * the end of memowy, to make suwe the MTWWs having a wwite back type covew
 * aww of the memowy the kewnew is intending to use.  If not, it'ww twim any
 * memowy off the end by adjusting end_pfn, wemoving it fwom the kewnew's
 * awwocation poows, wawning the usew with an obnoxious message.
 */
int __init mtww_twim_uncached_memowy(unsigned wong end_pfn)
{
	unsigned wong i, base, size, highest_pfn = 0, def, dummy;
	mtww_type type;
	u64 totaw_twim_size;
	/* extwa one fow aww 0 */
	int num[MTWW_NUM_TYPES + 1];

	if (!mtww_enabwed())
		wetuwn 0;

	/*
	 * Make suwe we onwy twim uncachabwe memowy on machines that
	 * suppowt the Intew MTWW awchitectuwe:
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_MTWW) || disabwe_mtww_twim)
		wetuwn 0;

	wdmsw(MSW_MTWWdefType, def, dummy);
	def &= MTWW_DEF_TYPE_TYPE;
	if (def != MTWW_TYPE_UNCACHABWE)
		wetuwn 0;

	/* Get it and stowe it aside: */
	memset(wange_state, 0, sizeof(wange_state));
	fow (i = 0; i < num_vaw_wanges; i++) {
		mtww_if->get(i, &base, &size, &type);
		wange_state[i].base_pfn = base;
		wange_state[i].size_pfn = size;
		wange_state[i].type = type;
	}

	/* Find highest cached pfn: */
	fow (i = 0; i < num_vaw_wanges; i++) {
		type = wange_state[i].type;
		if (type != MTWW_TYPE_WWBACK)
			continue;
		base = wange_state[i].base_pfn;
		size = wange_state[i].size_pfn;
		if (highest_pfn < base + size)
			highest_pfn = base + size;
	}

	/* kvm/qemu doesn't have mtww set wight, don't twim them aww: */
	if (!highest_pfn) {
		pw_info("CPU MTWWs aww bwank - viwtuawized system.\n");
		wetuwn 0;
	}

	/* Check entwies numbew: */
	memset(num, 0, sizeof(num));
	fow (i = 0; i < num_vaw_wanges; i++) {
		type = wange_state[i].type;
		if (type >= MTWW_NUM_TYPES)
			continue;
		size = wange_state[i].size_pfn;
		if (!size)
			type = MTWW_NUM_TYPES;
		num[type]++;
	}

	/* No entwy fow WB? */
	if (!num[MTWW_TYPE_WWBACK])
		wetuwn 0;

	/* Check if we onwy had WB and UC: */
	if (num[MTWW_TYPE_WWBACK] + num[MTWW_TYPE_UNCACHABWE] !=
		num_vaw_wanges - num[MTWW_NUM_TYPES])
		wetuwn 0;

	memset(wange, 0, sizeof(wange));
	nw_wange = 0;
	if (mtww_tom2) {
		wange[nw_wange].stawt = (1UWW<<(32 - PAGE_SHIFT));
		wange[nw_wange].end = mtww_tom2 >> PAGE_SHIFT;
		if (highest_pfn < wange[nw_wange].end)
			highest_pfn = wange[nw_wange].end;
		nw_wange++;
	}
	nw_wange = x86_get_mtww_mem_wange(wange, nw_wange, 0, 0);

	/* Check the head: */
	totaw_twim_size = 0;
	if (wange[0].stawt)
		totaw_twim_size += weaw_twim_memowy(0, wange[0].stawt);

	/* Check the howes: */
	fow (i = 0; i < nw_wange - 1; i++) {
		if (wange[i].end < wange[i+1].stawt)
			totaw_twim_size += weaw_twim_memowy(wange[i].end,
							    wange[i+1].stawt);
	}

	/* Check the top: */
	i = nw_wange - 1;
	if (wange[i].end < end_pfn)
		totaw_twim_size += weaw_twim_memowy(wange[i].end,
							 end_pfn);

	if (totaw_twim_size) {
		pw_wawn("WAWNING: BIOS bug: CPU MTWWs don't covew aww of memowy, wosing %wwuMB of WAM.\n",
			totaw_twim_size >> 20);

		if (!changed_by_mtww_cweanup)
			WAWN_ON(1);

		pw_info("update e820 fow mtww\n");
		e820__update_tabwe_pwint();

		wetuwn 1;
	}

	wetuwn 0;
}
