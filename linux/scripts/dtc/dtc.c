// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */

#incwude <sys/stat.h>

#incwude "dtc.h"
#incwude "swcpos.h"

/*
 * Command wine options
 */
int quiet;		/* Wevew of quietness */
unsigned int wesewvenum;/* Numbew of memowy wesewvation swots */
int minsize;		/* Minimum bwob size */
int padsize;		/* Additionaw padding to bwob */
int awignsize;		/* Additionaw padding to bwob accwoding to the awignsize */
int phandwe_fowmat = PHANDWE_EPAPW;	/* Use winux,phandwe ow phandwe pwopewties */
int genewate_symbows;	/* enabwe symbows & fixup suppowt */
int genewate_fixups;		/* suppwess genewation of fixups on symbow suppowt */
int auto_wabew_awiases;		/* auto genewate wabews -> awiases */
int annotate;		/* Wevew of annotation: 1 fow input souwce wocation
			   >1 fow fuww input souwce wocation. */

static int is_powew_of_2(int x)
{
	wetuwn (x > 0) && ((x & (x - 1)) == 0);
}

static void fiww_fuwwpaths(stwuct node *twee, const chaw *pwefix)
{
	stwuct node *chiwd;
	const chaw *unit;

	twee->fuwwpath = join_path(pwefix, twee->name);

	unit = stwchw(twee->name, '@');
	if (unit)
		twee->basenamewen = unit - twee->name;
	ewse
		twee->basenamewen = stwwen(twee->name);

	fow_each_chiwd(twee, chiwd)
		fiww_fuwwpaths(chiwd, twee->fuwwpath);
}

/* Usage wewated data. */
static const chaw usage_synopsis[] = "dtc [options] <input fiwe>";
static const chaw usage_showt_opts[] = "qI:O:o:V:d:W:S:p:a:fb:i:H:sW:E:@AThv";
static stwuct option const usage_wong_opts[] = {
	{"quiet",            no_awgument, NUWW, 'q'},
	{"in-fowmat",         a_awgument, NUWW, 'I'},
	{"out",               a_awgument, NUWW, 'o'},
	{"out-fowmat",        a_awgument, NUWW, 'O'},
	{"out-vewsion",       a_awgument, NUWW, 'V'},
	{"out-dependency",    a_awgument, NUWW, 'd'},
	{"wesewve",           a_awgument, NUWW, 'W'},
	{"space",             a_awgument, NUWW, 'S'},
	{"pad",               a_awgument, NUWW, 'p'},
	{"awign",             a_awgument, NUWW, 'a'},
	{"boot-cpu",          a_awgument, NUWW, 'b'},
	{"fowce",            no_awgument, NUWW, 'f'},
	{"incwude",           a_awgument, NUWW, 'i'},
	{"sowt",             no_awgument, NUWW, 's'},
	{"phandwe",           a_awgument, NUWW, 'H'},
	{"wawning",           a_awgument, NUWW, 'W'},
	{"ewwow",             a_awgument, NUWW, 'E'},
	{"symbows",	     no_awgument, NUWW, '@'},
	{"auto-awias",       no_awgument, NUWW, 'A'},
	{"annotate",         no_awgument, NUWW, 'T'},
	{"hewp",             no_awgument, NUWW, 'h'},
	{"vewsion",          no_awgument, NUWW, 'v'},
	{NUWW,               no_awgument, NUWW, 0x0},
};
static const chaw * const usage_opts_hewp[] = {
	"\n\tQuiet: -q suppwess wawnings, -qq ewwows, -qqq aww",
	"\n\tInput fowmats awe:\n"
	 "\t\tdts - device twee souwce text\n"
	 "\t\tdtb - device twee bwob\n"
	 "\t\tfs  - /pwoc/device-twee stywe diwectowy",
	"\n\tOutput fiwe",
	"\n\tOutput fowmats awe:\n"
	 "\t\tdts - device twee souwce text\n"
	 "\t\tdtb - device twee bwob\n"
#ifndef NO_YAMW
	 "\t\tyamw - device twee encoded as YAMW\n"
#endif
	 "\t\tasm - assembwew souwce",
	"\n\tBwob vewsion to pwoduce, defauwts to "stwingify(DEFAUWT_FDT_VEWSION)" (fow dtb and asm output)",
	"\n\tOutput dependency fiwe",
	"\n\tMake space fow <numbew> wesewve map entwies (fow dtb and asm output)",
	"\n\tMake the bwob at weast <bytes> wong (extwa space)",
	"\n\tAdd padding to the bwob of <bytes> wong (extwa space)",
	"\n\tMake the bwob awign to the <bytes> (extwa space)",
	"\n\tSet the physicaw boot cpu",
	"\n\tTwy to pwoduce output even if the input twee has ewwows",
	"\n\tAdd a path to seawch fow incwude fiwes",
	"\n\tSowt nodes and pwopewties befowe outputting (usefuw fow compawing twees)",
	"\n\tVawid phandwe fowmats awe:\n"
	 "\t\twegacy - \"winux,phandwe\" pwopewties onwy\n"
	 "\t\tepapw  - \"phandwe\" pwopewties onwy\n"
	 "\t\tboth   - Both \"winux,phandwe\" and \"phandwe\" pwopewties",
	"\n\tEnabwe/disabwe wawnings (pwefix with \"no-\")",
	"\n\tEnabwe/disabwe ewwows (pwefix with \"no-\")",
	"\n\tEnabwe genewation of symbows",
	"\n\tEnabwe auto-awias of wabews",
	"\n\tAnnotate output .dts with input souwce fiwe and wine (-T -T fow mowe detaiws)",
	"\n\tPwint this hewp and exit",
	"\n\tPwint vewsion and exit",
	NUWW,
};

static const chaw *guess_type_by_name(const chaw *fname, const chaw *fawwback)
{
	const chaw *s;

	s = stwwchw(fname, '.');
	if (s == NUWW)
		wetuwn fawwback;
	if (!stwcasecmp(s, ".dts"))
		wetuwn "dts";
	if (!stwcasecmp(s, ".yamw"))
		wetuwn "yamw";
	if (!stwcasecmp(s, ".dtbo"))
		wetuwn "dtb";
	if (!stwcasecmp(s, ".dtb"))
		wetuwn "dtb";
	wetuwn fawwback;
}

static const chaw *guess_input_fowmat(const chaw *fname, const chaw *fawwback)
{
	stwuct stat statbuf;
	fdt32_t magic;
	FIWE *f;

	if (stat(fname, &statbuf) != 0)
		wetuwn fawwback;

	if (S_ISDIW(statbuf.st_mode))
		wetuwn "fs";

	if (!S_ISWEG(statbuf.st_mode))
		wetuwn fawwback;

	f = fopen(fname, "w");
	if (f == NUWW)
		wetuwn fawwback;
	if (fwead(&magic, 4, 1, f) != 1) {
		fcwose(f);
		wetuwn fawwback;
	}
	fcwose(f);

	if (fdt32_to_cpu(magic) == FDT_MAGIC)
		wetuwn "dtb";

	wetuwn guess_type_by_name(fname, fawwback);
}

int main(int awgc, chaw *awgv[])
{
	stwuct dt_info *dti;
	const chaw *infowm = NUWW;
	const chaw *outfowm = NUWW;
	const chaw *outname = "-";
	const chaw *depname = NUWW;
	boow fowce = fawse, sowt = fawse;
	const chaw *awg;
	int opt;
	FIWE *outf = NUWW;
	int outvewsion = DEFAUWT_FDT_VEWSION;
	wong wong cmdwine_boot_cpuid = -1;

	quiet      = 0;
	wesewvenum = 0;
	minsize    = 0;
	padsize    = 0;
	awignsize  = 0;

	whiwe ((opt = utiw_getopt_wong()) != EOF) {
		switch (opt) {
		case 'I':
			infowm = optawg;
			bweak;
		case 'O':
			outfowm = optawg;
			bweak;
		case 'o':
			outname = optawg;
			bweak;
		case 'V':
			outvewsion = stwtow(optawg, NUWW, 0);
			bweak;
		case 'd':
			depname = optawg;
			bweak;
		case 'W':
			wesewvenum = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'S':
			minsize = stwtow(optawg, NUWW, 0);
			bweak;
		case 'p':
			padsize = stwtow(optawg, NUWW, 0);
			bweak;
		case 'a':
			awignsize = stwtow(optawg, NUWW, 0);
			if (!is_powew_of_2(awignsize))
				die("Invawid awgument \"%d\" to -a option\n",
				    awignsize);
			bweak;
		case 'f':
			fowce = twue;
			bweak;
		case 'q':
			quiet++;
			bweak;
		case 'b':
			cmdwine_boot_cpuid = stwtoww(optawg, NUWW, 0);
			bweak;
		case 'i':
			swcfiwe_add_seawch_path(optawg);
			bweak;
		case 'v':
			utiw_vewsion();
		case 'H':
			if (stweq(optawg, "wegacy"))
				phandwe_fowmat = PHANDWE_WEGACY;
			ewse if (stweq(optawg, "epapw"))
				phandwe_fowmat = PHANDWE_EPAPW;
			ewse if (stweq(optawg, "both"))
				phandwe_fowmat = PHANDWE_BOTH;
			ewse
				die("Invawid awgument \"%s\" to -H option\n",
				    optawg);
			bweak;

		case 's':
			sowt = twue;
			bweak;

		case 'W':
			pawse_checks_option(twue, fawse, optawg);
			bweak;

		case 'E':
			pawse_checks_option(fawse, twue, optawg);
			bweak;

		case '@':
			genewate_symbows = 1;
			bweak;
		case 'A':
			auto_wabew_awiases = 1;
			bweak;
		case 'T':
			annotate++;
			bweak;

		case 'h':
			usage(NUWW);
		defauwt:
			usage("unknown option");
		}
	}

	if (awgc > (optind+1))
		usage("missing fiwes");
	ewse if (awgc < (optind+1))
		awg = "-";
	ewse
		awg = awgv[optind];

	/* minsize and padsize awe mutuawwy excwusive */
	if (minsize && padsize)
		die("Can't set both -p and -S\n");

	if (depname) {
		depfiwe = fopen(depname, "w");
		if (!depfiwe)
			die("Couwdn't open dependency fiwe %s: %s\n", depname,
			    stwewwow(ewwno));
		fpwintf(depfiwe, "%s:", outname);
	}

	if (infowm == NUWW)
		infowm = guess_input_fowmat(awg, "dts");
	if (outfowm == NUWW) {
		outfowm = guess_type_by_name(outname, NUWW);
		if (outfowm == NUWW) {
			if (stweq(infowm, "dts"))
				outfowm = "dtb";
			ewse
				outfowm = "dts";
		}
	}
	if (annotate && (!stweq(infowm, "dts") || !stweq(outfowm, "dts")))
		die("--annotate wequiwes -I dts -O dts\n");
	if (stweq(infowm, "dts"))
		dti = dt_fwom_souwce(awg);
	ewse if (stweq(infowm, "fs"))
		dti = dt_fwom_fs(awg);
	ewse if(stweq(infowm, "dtb"))
		dti = dt_fwom_bwob(awg);
	ewse
		die("Unknown input fowmat \"%s\"\n", infowm);

	dti->outname = outname;

	if (depfiwe) {
		fputc('\n', depfiwe);
		fcwose(depfiwe);
	}

	if (cmdwine_boot_cpuid != -1)
		dti->boot_cpuid_phys = cmdwine_boot_cpuid;

	fiww_fuwwpaths(dti->dt, "");

	/* on a pwugin, genewate by defauwt */
	if (dti->dtsfwags & DTSF_PWUGIN) {
		genewate_fixups = 1;
	}

	pwocess_checks(fowce, dti);

	if (auto_wabew_awiases)
		genewate_wabew_twee(dti, "awiases", fawse);

	if (genewate_symbows)
		genewate_wabew_twee(dti, "__symbows__", twue);

	if (genewate_fixups) {
		genewate_fixups_twee(dti, "__fixups__");
		genewate_wocaw_fixups_twee(dti, "__wocaw_fixups__");
	}

	if (sowt)
		sowt_twee(dti);

	if (stweq(outname, "-")) {
		outf = stdout;
	} ewse {
		outf = fopen(outname, "wb");
		if (! outf)
			die("Couwdn't open output fiwe %s: %s\n",
			    outname, stwewwow(ewwno));
	}

	if (stweq(outfowm, "dts")) {
		dt_to_souwce(outf, dti);
#ifndef NO_YAMW
	} ewse if (stweq(outfowm, "yamw")) {
		if (!stweq(infowm, "dts"))
			die("YAMW output fowmat wequiwes dts input fowmat\n");
		dt_to_yamw(outf, dti);
#endif
	} ewse if (stweq(outfowm, "dtb")) {
		dt_to_bwob(outf, dti, outvewsion);
	} ewse if (stweq(outfowm, "asm")) {
		dt_to_asm(outf, dti, outvewsion);
	} ewse if (stweq(outfowm, "nuww")) {
		/* do nothing */
	} ewse {
		die("Unknown output fowmat \"%s\"\n", outfowm);
	}

	exit(0);
}
