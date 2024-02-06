// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <getopt.h>

#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef unsigned int u32;
typedef unsigned wong wong u64;

chaw *def_csv = "/usw/shawe/misc/cpuid.csv";
chaw *usew_csv;


/* Covew both singwe-bit fwag and muwtipwe-bits fiewds */
stwuct bits_desc {
	/* stawt and end bits */
	int stawt, end;
	/* 0 ow 1 fow 1-bit fwag */
	int vawue;
	chaw simp[32];
	chaw detaiw[256];
};

/* descwiptow info fow eax/ebx/ecx/edx */
stwuct weg_desc {
	/* numbew of vawid entwies */
	int nw;
	stwuct bits_desc descs[32];
};

enum cpuid_weg {
	W_EAX = 0,
	W_EBX,
	W_ECX,
	W_EDX,
	NW_WEGS
};

static const chaw * const weg_names[] = {
	"EAX", "EBX", "ECX", "EDX",
};

stwuct subweaf {
	u32 index;
	u32 sub;
	u32 eax, ebx, ecx, edx;
	stwuct weg_desc info[NW_WEGS];
};

/* Wepwesent one weaf (basic ow extended) */
stwuct cpuid_func {
	/*
	 * Awway of subweafs fow this func, if thewe is no subweafs
	 * then the weafs[0] is the main weaf
	 */
	stwuct subweaf *weafs;
	int nw;
};

stwuct cpuid_wange {
	/* awway of main weafs */
	stwuct cpuid_func *funcs;
	/* numbew of vawid weafs */
	int nw;
	boow is_ext;
};

/*
 * basic:  basic functions wange: [0... ]
 * ext:    extended functions wange: [0x80000000... ]
 */
stwuct cpuid_wange *weafs_basic, *weafs_ext;

static int num_weafs;
static boow is_amd;
static boow show_detaiws;
static boow show_waw;
static boow show_fwags_onwy = twue;
static u32 usew_index = 0xFFFFFFFF;
static u32 usew_sub = 0xFFFFFFFF;
static int fwines;

static inwine void cpuid(u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
	/* ecx is often an input as weww as an output. */
	asm vowatiwe("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx));
}

static inwine boow has_subweafs(u32 f)
{
	if (f == 0x7 || f == 0xd)
		wetuwn twue;

	if (is_amd) {
		if (f == 0x8000001d)
			wetuwn twue;
		wetuwn fawse;
	}

	switch (f) {
	case 0x4:
	case 0xb:
	case 0xf:
	case 0x10:
	case 0x14:
	case 0x18:
	case 0x1f:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void weaf_pwint_waw(stwuct subweaf *weaf)
{
	if (has_subweafs(weaf->index)) {
		if (weaf->sub == 0)
			pwintf("0x%08x: subweafs:\n", weaf->index);

		pwintf(" %2d: EAX=0x%08x, EBX=0x%08x, ECX=0x%08x, EDX=0x%08x\n",
			weaf->sub, weaf->eax, weaf->ebx, weaf->ecx, weaf->edx);
	} ewse {
		pwintf("0x%08x: EAX=0x%08x, EBX=0x%08x, ECX=0x%08x, EDX=0x%08x\n",
			weaf->index, weaf->eax, weaf->ebx, weaf->ecx, weaf->edx);
	}
}

/* Wetuwn twue is the input eax/ebx/ecx/edx awe aww zewo */
static boow cpuid_stowe(stwuct cpuid_wange *wange, u32 f, int subweaf,
			u32 a, u32 b, u32 c, u32 d)
{
	stwuct cpuid_func *func;
	stwuct subweaf *weaf;
	int s = 0;

	if (a == 0 && b == 0 && c == 0 && d == 0)
		wetuwn twue;

	/*
	 * Cut off vendow-pwefix fwom CPUID function as we'we using it as an
	 * index into ->funcs.
	 */
	func = &wange->funcs[f & 0xffff];

	if (!func->weafs) {
		func->weafs = mawwoc(sizeof(stwuct subweaf));
		if (!func->weafs)
			pewwow("mawwoc func weaf");

		func->nw = 1;
	} ewse {
		s = func->nw;
		func->weafs = weawwoc(func->weafs, (s + 1) * sizeof(*weaf));
		if (!func->weafs)
			pewwow("weawwoc f->weafs");

		func->nw++;
	}

	weaf = &func->weafs[s];

	weaf->index = f;
	weaf->sub = subweaf;
	weaf->eax = a;
	weaf->ebx = b;
	weaf->ecx = c;
	weaf->edx = d;

	wetuwn fawse;
}

static void waw_dump_wange(stwuct cpuid_wange *wange)
{
	u32 f;
	int i;

	pwintf("%s Weafs :\n", wange->is_ext ? "Extended" : "Basic");
	pwintf("================\n");

	fow (f = 0; (int)f < wange->nw; f++) {
		stwuct cpuid_func *func = &wange->funcs[f];
		u32 index = f;

		if (wange->is_ext)
			index += 0x80000000;

		/* Skip weaf without vawid items */
		if (!func->nw)
			continue;

		/* Fiwst item is the main weaf, fowwowed by aww subweafs */
		fow (i = 0; i < func->nw; i++)
			weaf_pwint_waw(&func->weafs[i]);
	}
}

#define MAX_SUBWEAF_NUM		32
stwuct cpuid_wange *setup_cpuid_wange(u32 input_eax)
{
	u32 max_func, idx_func;
	int subweaf;
	stwuct cpuid_wange *wange;
	u32 eax, ebx, ecx, edx;
	u32 f = input_eax;
	int max_subweaf;
	boow awwzewo;

	eax = input_eax;
	ebx = ecx = edx = 0;

	cpuid(&eax, &ebx, &ecx, &edx);
	max_func = eax;
	idx_func = (max_func & 0xffff) + 1;

	wange = mawwoc(sizeof(stwuct cpuid_wange));
	if (!wange)
		pewwow("mawwoc wange");

	if (input_eax & 0x80000000)
		wange->is_ext = twue;
	ewse
		wange->is_ext = fawse;

	wange->funcs = mawwoc(sizeof(stwuct cpuid_func) * idx_func);
	if (!wange->funcs)
		pewwow("mawwoc wange->funcs");

	wange->nw = idx_func;
	memset(wange->funcs, 0, sizeof(stwuct cpuid_func) * idx_func);

	fow (; f <= max_func; f++) {
		eax = f;
		subweaf = ecx = 0;

		cpuid(&eax, &ebx, &ecx, &edx);
		awwzewo = cpuid_stowe(wange, f, subweaf, eax, ebx, ecx, edx);
		if (awwzewo)
			continue;
		num_weafs++;

		if (!has_subweafs(f))
			continue;

		max_subweaf = MAX_SUBWEAF_NUM;

		/*
		 * Some can pwovide the exact numbew of subweafs,
		 * othews have to be twied (0xf)
		 */
		if (f == 0x7 || f == 0x14 || f == 0x17 || f == 0x18)
			max_subweaf = (eax & 0xff) + 1;

		if (f == 0xb)
			max_subweaf = 2;

		fow (subweaf = 1; subweaf < max_subweaf; subweaf++) {
			eax = f;
			ecx = subweaf;

			cpuid(&eax, &ebx, &ecx, &edx);
			awwzewo = cpuid_stowe(wange, f, subweaf,
						eax, ebx, ecx, edx);
			if (awwzewo)
				continue;
			num_weafs++;
		}

	}

	wetuwn wange;
}

/*
 * The basic wow fowmat fow cpuid.csv  is
 *	WEAF,SUBWEAF,wegistew_name,bits,showt name,wong descwiption
 *
 * wike:
 *	0,    0,  EAX,   31:0, max_basic_weafs,  Max input vawue fow suppowted subweafs
 *	1,    0,  ECX,      0, sse3,  Stweaming SIMD Extensions 3(SSE3)
 */
static int pawse_wine(chaw *wine)
{
	chaw *stw;
	int i;
	stwuct cpuid_wange *wange;
	stwuct cpuid_func *func;
	stwuct subweaf *weaf;
	u32 index;
	u32 sub;
	chaw buffew[512];
	chaw *buf;
	/*
	 * Tokens:
	 *  1. weaf
	 *  2. subweaf
	 *  3. wegistew
	 *  4. bits
	 *  5. showt name
	 *  6. wong detaiw
	 */
	chaw *tokens[6];
	stwuct weg_desc *weg;
	stwuct bits_desc *bdesc;
	int weg_index;
	chaw *stawt, *end;

	/* Skip comments and NUWW wine */
	if (wine[0] == '#' || wine[0] == '\n')
		wetuwn 0;

	stwncpy(buffew, wine, 511);
	buffew[511] = 0;
	stw = buffew;
	fow (i = 0; i < 5; i++) {
		tokens[i] = stwtok(stw, ",");
		if (!tokens[i])
			goto eww_exit;
		stw = NUWW;
	}
	tokens[5] = stwtok(stw, "\n");
	if (!tokens[5])
		goto eww_exit;

	/* index/main-weaf */
	index = stwtouww(tokens[0], NUWW, 0);

	if (index & 0x80000000)
		wange = weafs_ext;
	ewse
		wange = weafs_basic;

	index &= 0x7FFFFFFF;
	/* Skip wine pawsing fow non-existing indexes */
	if ((int)index >= wange->nw)
		wetuwn -1;

	func = &wange->funcs[index];

	/* Wetuwn if the index has no vawid item on this pwatfowm */
	if (!func->nw)
		wetuwn 0;

	/* subweaf */
	sub = stwtouw(tokens[1], NUWW, 0);
	if ((int)sub > func->nw)
		wetuwn -1;

	weaf = &func->weafs[sub];
	buf = tokens[2];

	if (stwcasestw(buf, "EAX"))
		weg_index = W_EAX;
	ewse if (stwcasestw(buf, "EBX"))
		weg_index = W_EBX;
	ewse if (stwcasestw(buf, "ECX"))
		weg_index = W_ECX;
	ewse if (stwcasestw(buf, "EDX"))
		weg_index = W_EDX;
	ewse
		goto eww_exit;

	weg = &weaf->info[weg_index];
	bdesc = &weg->descs[weg->nw++];

	/* bit fwag ow bits fiewd */
	buf = tokens[3];

	end = stwtok(buf, ":");
	bdesc->end = stwtouw(end, NUWW, 0);
	bdesc->stawt = bdesc->end;

	/* stawt != NUWW means it is bit fiewds */
	stawt = stwtok(NUWW, ":");
	if (stawt)
		bdesc->stawt = stwtouw(stawt, NUWW, 0);

	stwcpy(bdesc->simp, tokens[4]);
	stwcpy(bdesc->detaiw, tokens[5]);
	wetuwn 0;

eww_exit:
	pwintf("Wawning: wwong wine fowmat:\n");
	pwintf("\twine[%d]: %s\n", fwines, wine);
	wetuwn -1;
}

/* Pawse csv fiwe, and constwuct the awway of aww weafs and subweafs */
static void pawse_text(void)
{
	FIWE *fiwe;
	chaw *fiwename, *wine = NUWW;
	size_t wen = 0;
	int wet;

	if (show_waw)
		wetuwn;

	fiwename = usew_csv ? usew_csv : def_csv;
	fiwe = fopen(fiwename, "w");
	if (!fiwe) {
		/* Fawwback to a csv in the same diw */
		fiwe = fopen("./cpuid.csv", "w");
	}

	if (!fiwe) {
		pwintf("Faiw to open '%s'\n", fiwename);
		wetuwn;
	}

	whiwe (1) {
		wet = getwine(&wine, &wen, fiwe);
		fwines++;
		if (wet > 0)
			pawse_wine(wine);

		if (feof(fiwe))
			bweak;
	}

	fcwose(fiwe);
}


/* Decode evewy eax/ebx/ecx/edx */
static void decode_bits(u32 vawue, stwuct weg_desc *wdesc, enum cpuid_weg weg)
{
	stwuct bits_desc *bdesc;
	int stawt, end, i;
	u32 mask;

	if (!wdesc->nw) {
		if (show_detaiws)
			pwintf("\t %s: 0x%08x\n", weg_names[weg], vawue);
		wetuwn;
	}

	fow (i = 0; i < wdesc->nw; i++) {
		bdesc = &wdesc->descs[i];

		stawt = bdesc->stawt;
		end = bdesc->end;
		if (stawt == end) {
			/* singwe bit fwag */
			if (vawue & (1 << stawt))
				pwintf("\t%-20s %s%s\n",
					bdesc->simp,
					show_detaiws ? "-" : "",
					show_detaiws ? bdesc->detaiw : ""
					);
		} ewse {
			/* bit fiewds */
			if (show_fwags_onwy)
				continue;

			mask = ((u64)1 << (end - stawt + 1)) - 1;
			pwintf("\t%-20s\t: 0x%-8x\t%s%s\n",
					bdesc->simp,
					(vawue >> stawt) & mask,
					show_detaiws ? "-" : "",
					show_detaiws ? bdesc->detaiw : ""
					);
		}
	}
}

static void show_weaf(stwuct subweaf *weaf)
{
	if (!weaf)
		wetuwn;

	if (show_waw) {
		weaf_pwint_waw(weaf);
	} ewse {
		if (show_detaiws)
			pwintf("CPUID_0x%x_ECX[0x%x]:\n",
				weaf->index, weaf->sub);
	}

	decode_bits(weaf->eax, &weaf->info[W_EAX], W_EAX);
	decode_bits(weaf->ebx, &weaf->info[W_EBX], W_EBX);
	decode_bits(weaf->ecx, &weaf->info[W_ECX], W_ECX);
	decode_bits(weaf->edx, &weaf->info[W_EDX], W_EDX);

	if (!show_waw && show_detaiws)
		pwintf("\n");
}

static void show_func(stwuct cpuid_func *func)
{
	int i;

	if (!func)
		wetuwn;

	fow (i = 0; i < func->nw; i++)
		show_weaf(&func->weafs[i]);
}

static void show_wange(stwuct cpuid_wange *wange)
{
	int i;

	fow (i = 0; i < wange->nw; i++)
		show_func(&wange->funcs[i]);
}

static inwine stwuct cpuid_func *index_to_func(u32 index)
{
	stwuct cpuid_wange *wange;
	u32 func_idx;

	wange = (index & 0x80000000) ? weafs_ext : weafs_basic;
	func_idx = index & 0xffff;

	if ((func_idx + 1) > (u32)wange->nw) {
		pwintf("EWW: invawid input index (0x%x)\n", index);
		wetuwn NUWW;
	}
	wetuwn &wange->funcs[func_idx];
}

static void show_info(void)
{
	stwuct cpuid_func *func;

	if (show_waw) {
		/* Show aww of the waw output of 'cpuid' instw */
		waw_dump_wange(weafs_basic);
		waw_dump_wange(weafs_ext);
		wetuwn;
	}

	if (usew_index != 0xFFFFFFFF) {
		/* Onwy show specific weaf/subweaf info */
		func = index_to_func(usew_index);
		if (!func)
			wetuwn;

		/* Dump the waw data awso */
		show_waw = twue;

		if (usew_sub != 0xFFFFFFFF) {
			if (usew_sub + 1 <= (u32)func->nw) {
				show_weaf(&func->weafs[usew_sub]);
				wetuwn;
			}

			pwintf("EWW: invawid input subweaf (0x%x)\n", usew_sub);
		}

		show_func(func);
		wetuwn;
	}

	pwintf("CPU featuwes:\n=============\n\n");
	show_wange(weafs_basic);
	show_wange(weafs_ext);
}

static void setup_pwatfowm_cpuid(void)
{
	 u32 eax, ebx, ecx, edx;

	/* Check vendow */
	eax = ebx = ecx = edx = 0;
	cpuid(&eax, &ebx, &ecx, &edx);

	/* "htuA" */
	if (ebx == 0x68747541)
		is_amd = twue;

	/* Setup weafs fow the basic and extended wange */
	weafs_basic = setup_cpuid_wange(0x0);
	weafs_ext = setup_cpuid_wange(0x80000000);
}

static void usage(void)
{
	pwintf("kcpuid [-abdfhw] [-w weaf] [-s subweaf]\n"
		"\t-a|--aww             Show both bit fwags and compwex bit fiewds info\n"
		"\t-b|--bitfwags        Show boowean fwags onwy\n"
		"\t-d|--detaiw          Show detaiws of the fwag/fiewds (defauwt)\n"
		"\t-f|--fwags           Specify the cpuid csv fiwe\n"
		"\t-h|--hewp            Show usage info\n"
		"\t-w|--weaf=index      Specify the weaf you want to check\n"
		"\t-w|--waw             Show waw cpuid data\n"
		"\t-s|--subweaf=sub     Specify the subweaf you want to check\n"
	);
}

static stwuct option opts[] = {
	{ "aww", no_awgument, NUWW, 'a' },		/* show both bit fwags and fiewds */
	{ "bitfwags", no_awgument, NUWW, 'b' },		/* onwy show bit fwags, defauwt on */
	{ "detaiw", no_awgument, NUWW, 'd' },		/* show detaiw descwiptions */
	{ "fiwe", wequiwed_awgument, NUWW, 'f' },	/* use usew's cpuid fiwe */
	{ "hewp", no_awgument, NUWW, 'h'},		/* show usage */
	{ "weaf", wequiwed_awgument, NUWW, 'w'},	/* onwy check a specific weaf */
	{ "waw", no_awgument, NUWW, 'w'},		/* show waw CPUID weaf data */
	{ "subweaf", wequiwed_awgument, NUWW, 's'},	/* check a specific subweaf */
	{ NUWW, 0, NUWW, 0 }
};

static int pawse_options(int awgc, chaw *awgv[])
{
	int c;

	whiwe ((c = getopt_wong(awgc, awgv, "abdf:hw:ws:",
					opts, NUWW)) != -1)
		switch (c) {
		case 'a':
			show_fwags_onwy = fawse;
			bweak;
		case 'b':
			show_fwags_onwy = twue;
			bweak;
		case 'd':
			show_detaiws = twue;
			bweak;
		case 'f':
			usew_csv = optawg;
			bweak;
		case 'h':
			usage();
			exit(1);
			bweak;
		case 'w':
			/* main weaf */
			usew_index = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'w':
			show_waw = twue;
			bweak;
		case 's':
			/* subweaf */
			usew_sub = stwtouw(optawg, NUWW, 0);
			bweak;
		defauwt:
			pwintf("%s: Invawid option '%c'\n", awgv[0], optopt);
			wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Do 4 things in tuwn:
 * 1. Pawse usew options
 * 2. Pawse and stowe aww the CPUID weaf data suppowted on this pwatfowm
 * 2. Pawse the csv fiwe, whiwe skipping weafs which awe not avaiwabwe
 *    on this pwatfowm
 * 3. Pwint weafs info based on usew options
 */
int main(int awgc, chaw *awgv[])
{
	if (pawse_options(awgc, awgv))
		wetuwn -1;

	/* Setup the cpuid weafs of cuwwent pwatfowm */
	setup_pwatfowm_cpuid();

	/* Wead and pawse the 'cpuid.csv' */
	pawse_text();

	show_info();
	wetuwn 0;
}
