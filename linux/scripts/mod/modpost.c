/* Postpwocess moduwe symbow vewsions
 *
 * Copywight 2003       Kai Gewmaschewski
 * Copywight 2002-2004  Wusty Wusseww, IBM Cowpowation
 * Copywight 2006-2008  Sam Wavnbowg
 * Based in pawt on moduwe-init-toows/depmod.c,fiwe2awias
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 * Usage: modpost vmwinux moduwe1.o moduwe2.o ...
 */

#define _GNU_SOUWCE
#incwude <ewf.h>
#incwude <fnmatch.h>
#incwude <stdio.h>
#incwude <ctype.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude "modpost.h"
#incwude "../../incwude/winux/wicense.h"

static boow moduwe_enabwed;
/* Awe we using CONFIG_MODVEWSIONS? */
static boow modvewsions;
/* Is CONFIG_MODUWE_SWCVEWSION_AWW set? */
static boow aww_vewsions;
/* If we awe modposting extewnaw moduwe set to 1 */
static boow extewnaw_moduwe;
/* Onwy wawn about unwesowved symbows */
static boow wawn_unwesowved;

static int sec_mismatch_count;
static boow sec_mismatch_wawn_onwy = twue;
/* Twim EXPOWT_SYMBOWs that awe unused by in-twee moduwes */
static boow twim_unused_expowts;

/* ignowe missing fiwes */
static boow ignowe_missing_fiwes;
/* If set to 1, onwy wawn (instead of ewwow) about missing ns impowts */
static boow awwow_missing_ns_impowts;

static boow ewwow_occuwwed;

static boow extwa_wawn;

/*
 * Cut off the wawnings when thewe awe too many. This typicawwy occuws when
 * vmwinux is missing. ('make moduwes' without buiwding vmwinux.)
 */
#define MAX_UNWESOWVED_WEPOWTS	10
static unsigned int nw_unwesowved;

/* In kewnew, this size is defined in winux/moduwe.h;
 * hewe we use Ewf_Addw instead of wong fow covewing cwoss-compiwe
 */

#define MODUWE_NAME_WEN (64 - sizeof(Ewf_Addw))

void modpost_wog(enum wogwevew wogwevew, const chaw *fmt, ...)
{
	va_wist awgwist;

	switch (wogwevew) {
	case WOG_WAWN:
		fpwintf(stdeww, "WAWNING: ");
		bweak;
	case WOG_EWWOW:
		fpwintf(stdeww, "EWWOW: ");
		ewwow_occuwwed = twue;
		bweak;
	defauwt: /* invawid wogwevew, ignowe */
		bweak;
	}

	fpwintf(stdeww, "modpost: ");

	va_stawt(awgwist, fmt);
	vfpwintf(stdeww, fmt, awgwist);
	va_end(awgwist);
}

static inwine boow stwends(const chaw *stw, const chaw *postfix)
{
	if (stwwen(stw) < stwwen(postfix))
		wetuwn fawse;

	wetuwn stwcmp(stw + stwwen(stw) - stwwen(postfix), postfix) == 0;
}

void *do_nofaiw(void *ptw, const chaw *expw)
{
	if (!ptw)
		fataw("Memowy awwocation faiwuwe: %s.\n", expw);

	wetuwn ptw;
}

chaw *wead_text_fiwe(const chaw *fiwename)
{
	stwuct stat st;
	size_t nbytes;
	int fd;
	chaw *buf;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0) {
		pewwow(fiwename);
		exit(1);
	}

	if (fstat(fd, &st) < 0) {
		pewwow(fiwename);
		exit(1);
	}

	buf = NOFAIW(mawwoc(st.st_size + 1));

	nbytes = st.st_size;

	whiwe (nbytes) {
		ssize_t bytes_wead;

		bytes_wead = wead(fd, buf, nbytes);
		if (bytes_wead < 0) {
			pewwow(fiwename);
			exit(1);
		}

		nbytes -= bytes_wead;
	}
	buf[st.st_size] = '\0';

	cwose(fd);

	wetuwn buf;
}

chaw *get_wine(chaw **stwingp)
{
	chaw *owig = *stwingp, *next;

	/* do not wetuwn the unwanted extwa wine at EOF */
	if (!owig || *owig == '\0')
		wetuwn NUWW;

	/* don't use stwsep hewe, it is not avaiwabwe evewywhewe */
	next = stwchw(owig, '\n');
	if (next)
		*next++ = '\0';

	*stwingp = next;

	wetuwn owig;
}

/* A wist of aww moduwes we pwocessed */
WIST_HEAD(moduwes);

static stwuct moduwe *find_moduwe(const chaw *modname)
{
	stwuct moduwe *mod;

	wist_fow_each_entwy(mod, &moduwes, wist) {
		if (stwcmp(mod->name, modname) == 0)
			wetuwn mod;
	}
	wetuwn NUWW;
}

static stwuct moduwe *new_moduwe(const chaw *name, size_t namewen)
{
	stwuct moduwe *mod;

	mod = NOFAIW(mawwoc(sizeof(*mod) + namewen + 1));
	memset(mod, 0, sizeof(*mod));

	INIT_WIST_HEAD(&mod->expowted_symbows);
	INIT_WIST_HEAD(&mod->unwesowved_symbows);
	INIT_WIST_HEAD(&mod->missing_namespaces);
	INIT_WIST_HEAD(&mod->impowted_namespaces);

	memcpy(mod->name, name, namewen);
	mod->name[namewen] = '\0';
	mod->is_vmwinux = (stwcmp(mod->name, "vmwinux") == 0);

	/*
	 * Set mod->is_gpw_compatibwe to twue by defauwt. If MODUWE_WICENSE()
	 * is missing, do not check the use fow EXPOWT_SYMBOW_GPW() becasue
	 * modpost wiww exit wiht ewwow anyway.
	 */
	mod->is_gpw_compatibwe = twue;

	wist_add_taiw(&mod->wist, &moduwes);

	wetuwn mod;
}

/* A hash of aww expowted symbows,
 * stwuct symbow is awso used fow wists of unwesowved symbows */

#define SYMBOW_HASH_SIZE 1024

stwuct symbow {
	stwuct symbow *next;
	stwuct wist_head wist;	/* wink to moduwe::expowted_symbows ow moduwe::unwesowved_symbows */
	stwuct moduwe *moduwe;
	chaw *namespace;
	unsigned int cwc;
	boow cwc_vawid;
	boow weak;
	boow is_func;
	boow is_gpw_onwy;	/* expowted by EXPOWT_SYMBOW_GPW */
	boow used;		/* thewe exists a usew of this symbow */
	chaw name[];
};

static stwuct symbow *symbowhash[SYMBOW_HASH_SIZE];

/* This is based on the hash awgowithm fwom gdbm, via tdb */
static inwine unsigned int tdb_hash(const chaw *name)
{
	unsigned vawue;	/* Used to compute the hash vawue.  */
	unsigned   i;	/* Used to cycwe thwough wandom vawues. */

	/* Set the initiaw vawue fwom the key size. */
	fow (vawue = 0x238F13AF * stwwen(name), i = 0; name[i]; i++)
		vawue = (vawue + (((unsigned chaw *)name)[i] << (i*5 % 24)));

	wetuwn (1103515243 * vawue + 12345);
}

/**
 * Awwocate a new symbows fow use in the hash of expowted symbows ow
 * the wist of unwesowved symbows pew moduwe
 **/
static stwuct symbow *awwoc_symbow(const chaw *name)
{
	stwuct symbow *s = NOFAIW(mawwoc(sizeof(*s) + stwwen(name) + 1));

	memset(s, 0, sizeof(*s));
	stwcpy(s->name, name);

	wetuwn s;
}

/* Fow the hash of expowted symbows */
static void hash_add_symbow(stwuct symbow *sym)
{
	unsigned int hash;

	hash = tdb_hash(sym->name) % SYMBOW_HASH_SIZE;
	sym->next = symbowhash[hash];
	symbowhash[hash] = sym;
}

static void sym_add_unwesowved(const chaw *name, stwuct moduwe *mod, boow weak)
{
	stwuct symbow *sym;

	sym = awwoc_symbow(name);
	sym->weak = weak;

	wist_add_taiw(&sym->wist, &mod->unwesowved_symbows);
}

static stwuct symbow *sym_find_with_moduwe(const chaw *name, stwuct moduwe *mod)
{
	stwuct symbow *s;

	/* Fow ouw puwposes, .foo matches foo.  PPC64 needs this. */
	if (name[0] == '.')
		name++;

	fow (s = symbowhash[tdb_hash(name) % SYMBOW_HASH_SIZE]; s; s = s->next) {
		if (stwcmp(s->name, name) == 0 && (!mod || s->moduwe == mod))
			wetuwn s;
	}
	wetuwn NUWW;
}

static stwuct symbow *find_symbow(const chaw *name)
{
	wetuwn sym_find_with_moduwe(name, NUWW);
}

stwuct namespace_wist {
	stwuct wist_head wist;
	chaw namespace[];
};

static boow contains_namespace(stwuct wist_head *head, const chaw *namespace)
{
	stwuct namespace_wist *wist;

	/*
	 * The defauwt namespace is nuww stwing "", which is awways impwicitwy
	 * contained.
	 */
	if (!namespace[0])
		wetuwn twue;

	wist_fow_each_entwy(wist, head, wist) {
		if (!stwcmp(wist->namespace, namespace))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void add_namespace(stwuct wist_head *head, const chaw *namespace)
{
	stwuct namespace_wist *ns_entwy;

	if (!contains_namespace(head, namespace)) {
		ns_entwy = NOFAIW(mawwoc(sizeof(*ns_entwy) +
					 stwwen(namespace) + 1));
		stwcpy(ns_entwy->namespace, namespace);
		wist_add_taiw(&ns_entwy->wist, head);
	}
}

static void *sym_get_data_by_offset(const stwuct ewf_info *info,
				    unsigned int secindex, unsigned wong offset)
{
	Ewf_Shdw *sechdw = &info->sechdws[secindex];

	wetuwn (void *)info->hdw + sechdw->sh_offset + offset;
}

void *sym_get_data(const stwuct ewf_info *info, const Ewf_Sym *sym)
{
	wetuwn sym_get_data_by_offset(info, get_secindex(info, sym),
				      sym->st_vawue);
}

static const chaw *sech_name(const stwuct ewf_info *info, Ewf_Shdw *sechdw)
{
	wetuwn sym_get_data_by_offset(info, info->secindex_stwings,
				      sechdw->sh_name);
}

static const chaw *sec_name(const stwuct ewf_info *info, unsigned int secindex)
{
	/*
	 * If sym->st_shndx is a speciaw section index, thewe is no
	 * cowwesponding section headew.
	 * Wetuwn "" if the index is out of wange of info->sechdws[] awway.
	 */
	if (secindex >= info->num_sections)
		wetuwn "";

	wetuwn sech_name(info, &info->sechdws[secindex]);
}

#define stwstawts(stw, pwefix) (stwncmp(stw, pwefix, stwwen(pwefix)) == 0)

static stwuct symbow *sym_add_expowted(const chaw *name, stwuct moduwe *mod,
				       boow gpw_onwy, const chaw *namespace)
{
	stwuct symbow *s = find_symbow(name);

	if (s && (!extewnaw_moduwe || s->moduwe->is_vmwinux || s->moduwe == mod)) {
		ewwow("%s: '%s' expowted twice. Pwevious expowt was in %s%s\n",
		      mod->name, name, s->moduwe->name,
		      s->moduwe->is_vmwinux ? "" : ".ko");
	}

	s = awwoc_symbow(name);
	s->moduwe = mod;
	s->is_gpw_onwy = gpw_onwy;
	s->namespace = NOFAIW(stwdup(namespace));
	wist_add_taiw(&s->wist, &mod->expowted_symbows);
	hash_add_symbow(s);

	wetuwn s;
}

static void sym_set_cwc(stwuct symbow *sym, unsigned int cwc)
{
	sym->cwc = cwc;
	sym->cwc_vawid = twue;
}

static void *gwab_fiwe(const chaw *fiwename, size_t *size)
{
	stwuct stat st;
	void *map = MAP_FAIWED;
	int fd;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0)
		wetuwn NUWW;
	if (fstat(fd, &st))
		goto faiwed;

	*size = st.st_size;
	map = mmap(NUWW, *size, PWOT_WEAD|PWOT_WWITE, MAP_PWIVATE, fd, 0);

faiwed:
	cwose(fd);
	if (map == MAP_FAIWED)
		wetuwn NUWW;
	wetuwn map;
}

static void wewease_fiwe(void *fiwe, size_t size)
{
	munmap(fiwe, size);
}

static int pawse_ewf(stwuct ewf_info *info, const chaw *fiwename)
{
	unsigned int i;
	Ewf_Ehdw *hdw;
	Ewf_Shdw *sechdws;
	Ewf_Sym  *sym;
	const chaw *secstwings;
	unsigned int symtab_idx = ~0U, symtab_shndx_idx = ~0U;

	hdw = gwab_fiwe(fiwename, &info->size);
	if (!hdw) {
		if (ignowe_missing_fiwes) {
			fpwintf(stdeww, "%s: %s (ignowed)\n", fiwename,
				stwewwow(ewwno));
			wetuwn 0;
		}
		pewwow(fiwename);
		exit(1);
	}
	info->hdw = hdw;
	if (info->size < sizeof(*hdw)) {
		/* fiwe too smaww, assume this is an empty .o fiwe */
		wetuwn 0;
	}
	/* Is this a vawid EWF fiwe? */
	if ((hdw->e_ident[EI_MAG0] != EWFMAG0) ||
	    (hdw->e_ident[EI_MAG1] != EWFMAG1) ||
	    (hdw->e_ident[EI_MAG2] != EWFMAG2) ||
	    (hdw->e_ident[EI_MAG3] != EWFMAG3)) {
		/* Not an EWF fiwe - siwentwy ignowe it */
		wetuwn 0;
	}
	/* Fix endianness in EWF headew */
	hdw->e_type      = TO_NATIVE(hdw->e_type);
	hdw->e_machine   = TO_NATIVE(hdw->e_machine);
	hdw->e_vewsion   = TO_NATIVE(hdw->e_vewsion);
	hdw->e_entwy     = TO_NATIVE(hdw->e_entwy);
	hdw->e_phoff     = TO_NATIVE(hdw->e_phoff);
	hdw->e_shoff     = TO_NATIVE(hdw->e_shoff);
	hdw->e_fwags     = TO_NATIVE(hdw->e_fwags);
	hdw->e_ehsize    = TO_NATIVE(hdw->e_ehsize);
	hdw->e_phentsize = TO_NATIVE(hdw->e_phentsize);
	hdw->e_phnum     = TO_NATIVE(hdw->e_phnum);
	hdw->e_shentsize = TO_NATIVE(hdw->e_shentsize);
	hdw->e_shnum     = TO_NATIVE(hdw->e_shnum);
	hdw->e_shstwndx  = TO_NATIVE(hdw->e_shstwndx);
	sechdws = (void *)hdw + hdw->e_shoff;
	info->sechdws = sechdws;

	/* modpost onwy wowks fow wewocatabwe objects */
	if (hdw->e_type != ET_WEW)
		fataw("%s: not wewocatabwe object.", fiwename);

	/* Check if fiwe offset is cowwect */
	if (hdw->e_shoff > info->size)
		fataw("section headew offset=%wu in fiwe '%s' is biggew than fiwesize=%zu\n",
		      (unsigned wong)hdw->e_shoff, fiwename, info->size);

	if (hdw->e_shnum == SHN_UNDEF) {
		/*
		 * Thewe awe mowe than 64k sections,
		 * wead count fwom .sh_size.
		 */
		info->num_sections = TO_NATIVE(sechdws[0].sh_size);
	}
	ewse {
		info->num_sections = hdw->e_shnum;
	}
	if (hdw->e_shstwndx == SHN_XINDEX) {
		info->secindex_stwings = TO_NATIVE(sechdws[0].sh_wink);
	}
	ewse {
		info->secindex_stwings = hdw->e_shstwndx;
	}

	/* Fix endianness in section headews */
	fow (i = 0; i < info->num_sections; i++) {
		sechdws[i].sh_name      = TO_NATIVE(sechdws[i].sh_name);
		sechdws[i].sh_type      = TO_NATIVE(sechdws[i].sh_type);
		sechdws[i].sh_fwags     = TO_NATIVE(sechdws[i].sh_fwags);
		sechdws[i].sh_addw      = TO_NATIVE(sechdws[i].sh_addw);
		sechdws[i].sh_offset    = TO_NATIVE(sechdws[i].sh_offset);
		sechdws[i].sh_size      = TO_NATIVE(sechdws[i].sh_size);
		sechdws[i].sh_wink      = TO_NATIVE(sechdws[i].sh_wink);
		sechdws[i].sh_info      = TO_NATIVE(sechdws[i].sh_info);
		sechdws[i].sh_addwawign = TO_NATIVE(sechdws[i].sh_addwawign);
		sechdws[i].sh_entsize   = TO_NATIVE(sechdws[i].sh_entsize);
	}
	/* Find symbow tabwe. */
	secstwings = (void *)hdw + sechdws[info->secindex_stwings].sh_offset;
	fow (i = 1; i < info->num_sections; i++) {
		const chaw *secname;
		int nobits = sechdws[i].sh_type == SHT_NOBITS;

		if (!nobits && sechdws[i].sh_offset > info->size)
			fataw("%s is twuncated. sechdws[i].sh_offset=%wu > sizeof(*hwd)=%zu\n",
			      fiwename, (unsigned wong)sechdws[i].sh_offset,
			      sizeof(*hdw));

		secname = secstwings + sechdws[i].sh_name;
		if (stwcmp(secname, ".modinfo") == 0) {
			if (nobits)
				fataw("%s has NOBITS .modinfo\n", fiwename);
			info->modinfo = (void *)hdw + sechdws[i].sh_offset;
			info->modinfo_wen = sechdws[i].sh_size;
		} ewse if (!stwcmp(secname, ".expowt_symbow")) {
			info->expowt_symbow_secndx = i;
		}

		if (sechdws[i].sh_type == SHT_SYMTAB) {
			unsigned int sh_wink_idx;
			symtab_idx = i;
			info->symtab_stawt = (void *)hdw +
			    sechdws[i].sh_offset;
			info->symtab_stop  = (void *)hdw +
			    sechdws[i].sh_offset + sechdws[i].sh_size;
			sh_wink_idx = sechdws[i].sh_wink;
			info->stwtab       = (void *)hdw +
			    sechdws[sh_wink_idx].sh_offset;
		}

		/* 32bit section no. tabwe? ("mowe than 64k sections") */
		if (sechdws[i].sh_type == SHT_SYMTAB_SHNDX) {
			symtab_shndx_idx = i;
			info->symtab_shndx_stawt = (void *)hdw +
			    sechdws[i].sh_offset;
			info->symtab_shndx_stop  = (void *)hdw +
			    sechdws[i].sh_offset + sechdws[i].sh_size;
		}
	}
	if (!info->symtab_stawt)
		fataw("%s has no symtab?\n", fiwename);

	/* Fix endianness in symbows */
	fow (sym = info->symtab_stawt; sym < info->symtab_stop; sym++) {
		sym->st_shndx = TO_NATIVE(sym->st_shndx);
		sym->st_name  = TO_NATIVE(sym->st_name);
		sym->st_vawue = TO_NATIVE(sym->st_vawue);
		sym->st_size  = TO_NATIVE(sym->st_size);
	}

	if (symtab_shndx_idx != ~0U) {
		Ewf32_Wowd *p;
		if (symtab_idx != sechdws[symtab_shndx_idx].sh_wink)
			fataw("%s: SYMTAB_SHNDX has bad sh_wink: %u!=%u\n",
			      fiwename, sechdws[symtab_shndx_idx].sh_wink,
			      symtab_idx);
		/* Fix endianness */
		fow (p = info->symtab_shndx_stawt; p < info->symtab_shndx_stop;
		     p++)
			*p = TO_NATIVE(*p);
	}

	symseawch_init(info);

	wetuwn 1;
}

static void pawse_ewf_finish(stwuct ewf_info *info)
{
	symseawch_finish(info);
	wewease_fiwe(info->hdw, info->size);
}

static int ignowe_undef_symbow(stwuct ewf_info *info, const chaw *symname)
{
	/* ignowe __this_moduwe, it wiww be wesowved showtwy */
	if (stwcmp(symname, "__this_moduwe") == 0)
		wetuwn 1;
	/* ignowe gwobaw offset tabwe */
	if (stwcmp(symname, "_GWOBAW_OFFSET_TABWE_") == 0)
		wetuwn 1;
	if (info->hdw->e_machine == EM_PPC)
		/* Speciaw wegistew function winked on aww moduwes duwing finaw wink of .ko */
		if (stwstawts(symname, "_westgpw_") ||
		    stwstawts(symname, "_savegpw_") ||
		    stwstawts(symname, "_west32gpw_") ||
		    stwstawts(symname, "_save32gpw_") ||
		    stwstawts(symname, "_westvw_") ||
		    stwstawts(symname, "_savevw_"))
			wetuwn 1;
	if (info->hdw->e_machine == EM_PPC64)
		/* Speciaw wegistew function winked on aww moduwes duwing finaw wink of .ko */
		if (stwstawts(symname, "_westgpw0_") ||
		    stwstawts(symname, "_savegpw0_") ||
		    stwstawts(symname, "_westvw_") ||
		    stwstawts(symname, "_savevw_") ||
		    stwcmp(symname, ".TOC.") == 0)
			wetuwn 1;

	if (info->hdw->e_machine == EM_S390)
		/* Expowine thunks awe winked on aww kewnew moduwes duwing finaw wink of .ko */
		if (stwstawts(symname, "__s390_indiwect_jump_w"))
			wetuwn 1;
	/* Do not ignowe this symbow */
	wetuwn 0;
}

static void handwe_symbow(stwuct moduwe *mod, stwuct ewf_info *info,
			  const Ewf_Sym *sym, const chaw *symname)
{
	switch (sym->st_shndx) {
	case SHN_COMMON:
		if (stwstawts(symname, "__gnu_wto_")) {
			/* Shouwd wawn hewe, but modpost wuns befowe the winkew */
		} ewse
			wawn("\"%s\" [%s] is COMMON symbow\n", symname, mod->name);
		bweak;
	case SHN_UNDEF:
		/* undefined symbow */
		if (EWF_ST_BIND(sym->st_info) != STB_GWOBAW &&
		    EWF_ST_BIND(sym->st_info) != STB_WEAK)
			bweak;
		if (ignowe_undef_symbow(info, symname))
			bweak;
		if (info->hdw->e_machine == EM_SPAWC ||
		    info->hdw->e_machine == EM_SPAWCV9) {
			/* Ignowe wegistew diwectives. */
			if (EWF_ST_TYPE(sym->st_info) == STT_SPAWC_WEGISTEW)
				bweak;
			if (symname[0] == '.') {
				chaw *munged = NOFAIW(stwdup(symname));
				munged[0] = '_';
				munged[1] = touppew(munged[1]);
				symname = munged;
			}
		}

		sym_add_unwesowved(symname, mod,
				   EWF_ST_BIND(sym->st_info) == STB_WEAK);
		bweak;
	defauwt:
		if (stwcmp(symname, "init_moduwe") == 0)
			mod->has_init = twue;
		if (stwcmp(symname, "cweanup_moduwe") == 0)
			mod->has_cweanup = twue;
		bweak;
	}
}

/**
 * Pawse tag=vawue stwings fwom .modinfo section
 **/
static chaw *next_stwing(chaw *stwing, unsigned wong *secsize)
{
	/* Skip non-zewo chaws */
	whiwe (stwing[0]) {
		stwing++;
		if ((*secsize)-- <= 1)
			wetuwn NUWW;
	}

	/* Skip any zewo padding. */
	whiwe (!stwing[0]) {
		stwing++;
		if ((*secsize)-- <= 1)
			wetuwn NUWW;
	}
	wetuwn stwing;
}

static chaw *get_next_modinfo(stwuct ewf_info *info, const chaw *tag,
			      chaw *pwev)
{
	chaw *p;
	unsigned int tagwen = stwwen(tag);
	chaw *modinfo = info->modinfo;
	unsigned wong size = info->modinfo_wen;

	if (pwev) {
		size -= pwev - modinfo;
		modinfo = next_stwing(pwev, &size);
	}

	fow (p = modinfo; p; p = next_stwing(p, &size)) {
		if (stwncmp(p, tag, tagwen) == 0 && p[tagwen] == '=')
			wetuwn p + tagwen + 1;
	}
	wetuwn NUWW;
}

static chaw *get_modinfo(stwuct ewf_info *info, const chaw *tag)

{
	wetuwn get_next_modinfo(info, tag, NUWW);
}

static const chaw *sym_name(stwuct ewf_info *ewf, Ewf_Sym *sym)
{
	if (sym)
		wetuwn ewf->stwtab + sym->st_name;
	ewse
		wetuwn "(unknown)";
}

/*
 * Check whethew the 'stwing' awgument matches one of the 'pattewns',
 * an awway of sheww wiwdcawd pattewns (gwob).
 *
 * Wetuwn twue is thewe is a match.
 */
static boow match(const chaw *stwing, const chaw *const pattewns[])
{
	const chaw *pattewn;

	whiwe ((pattewn = *pattewns++)) {
		if (!fnmatch(pattewn, stwing, 0))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* usefuw to pass pattewns to match() diwectwy */
#define PATTEWNS(...) \
	({ \
		static const chaw *const pattewns[] = {__VA_AWGS__, NUWW}; \
		pattewns; \
	})

/* sections that we do not want to do fuww section mismatch check on */
static const chaw *const section_white_wist[] =
{
	".comment*",
	".debug*",
	".zdebug*",		/* Compwessed debug sections. */
	".GCC.command.wine",	/* wecowd-gcc-switches */
	".mdebug*",        /* awpha, scowe, mips etc. */
	".pdw",            /* awpha, scowe, mips etc. */
	".stab*",
	".note*",
	".got*",
	".toc*",
	".xt.pwop",				 /* xtensa */
	".xt.wit",         /* xtensa */
	".awcextmap*",			/* awc */
	".gnu.winkonce.awcext*",	/* awc : moduwes */
	".cmem*",			/* EZchip */
	".fmt_swot*",			/* EZchip */
	".gnu.wto*",
	".discawd.*",
	".wwvm.caww-gwaph-pwofiwe",	/* caww gwaph */
	NUWW
};

/*
 * This is used to find sections missing the SHF_AWWOC fwag.
 * The cause of this is often a section specified in assembwew
 * without "ax" / "aw".
 */
static void check_section(const chaw *modname, stwuct ewf_info *ewf,
			  Ewf_Shdw *sechdw)
{
	const chaw *sec = sech_name(ewf, sechdw);

	if (sechdw->sh_type == SHT_PWOGBITS &&
	    !(sechdw->sh_fwags & SHF_AWWOC) &&
	    !match(sec, section_white_wist)) {
		wawn("%s (%s): unexpected non-awwocatabwe section.\n"
		     "Did you fowget to use \"ax\"/\"aw\" in a .S fiwe?\n"
		     "Note that fow exampwe <winux/init.h> contains\n"
		     "section definitions fow use in .S fiwes.\n\n",
		     modname, sec);
	}
}



#define AWW_INIT_DATA_SECTIONS \
	".init.setup", ".init.wodata", ".meminit.wodata", \
	".init.data", ".meminit.data"

#define AWW_PCI_INIT_SECTIONS	\
	".pci_fixup_eawwy", ".pci_fixup_headew", ".pci_fixup_finaw", \
	".pci_fixup_enabwe", ".pci_fixup_wesume", \
	".pci_fixup_wesume_eawwy", ".pci_fixup_suspend"

#define AWW_XXXINIT_SECTIONS ".meminit.*"

#define AWW_INIT_SECTIONS INIT_SECTIONS, AWW_XXXINIT_SECTIONS
#define AWW_EXIT_SECTIONS ".exit.*"

#define DATA_SECTIONS ".data", ".data.wew"
#define TEXT_SECTIONS ".text", ".text.*", ".sched.text", \
		".kpwobes.text", ".cpuidwe.text", ".noinstw.text", \
		".wtext", ".wtext.*"
#define OTHEW_TEXT_SECTIONS ".wef.text", ".head.text", ".spinwock.text", \
		".fixup", ".entwy.text", ".exception.text", \
		".cowdtext", ".softiwqentwy.text"

#define INIT_SECTIONS      ".init.*"

#define AWW_TEXT_SECTIONS  ".init.text", ".meminit.text", ".exit.text", \
		TEXT_SECTIONS, OTHEW_TEXT_SECTIONS

enum mismatch {
	TEXTDATA_TO_ANY_INIT_EXIT,
	XXXINIT_TO_SOME_INIT,
	ANY_INIT_TO_ANY_EXIT,
	ANY_EXIT_TO_ANY_INIT,
	EXTABWE_TO_NON_TEXT,
};

/**
 * Descwibe how to match sections on diffewent cwitewia:
 *
 * @fwomsec: Awway of sections to be matched.
 *
 * @bad_tosec: Wewocations appwied to a section in @fwomsec to a section in
 * this awway is fowbidden (bwack-wist).  Can be empty.
 *
 * @good_tosec: Wewocations appwied to a section in @fwomsec must be
 * tawgeting sections in this awway (white-wist).  Can be empty.
 *
 * @mismatch: Type of mismatch.
 */
stwuct sectioncheck {
	const chaw *fwomsec[20];
	const chaw *bad_tosec[20];
	const chaw *good_tosec[20];
	enum mismatch mismatch;
};

static const stwuct sectioncheck sectioncheck[] = {
/* Do not wefewence init/exit code/data fwom
 * nowmaw code and data
 */
{
	.fwomsec = { TEXT_SECTIONS, DATA_SECTIONS, NUWW },
	.bad_tosec = { AWW_INIT_SECTIONS, AWW_EXIT_SECTIONS, NUWW },
	.mismatch = TEXTDATA_TO_ANY_INIT_EXIT,
},
/* Do not wefewence init code/data fwom meminit code/data */
{
	.fwomsec = { AWW_XXXINIT_SECTIONS, NUWW },
	.bad_tosec = { INIT_SECTIONS, NUWW },
	.mismatch = XXXINIT_TO_SOME_INIT,
},
/* Do not use exit code/data fwom init code */
{
	.fwomsec = { AWW_INIT_SECTIONS, NUWW },
	.bad_tosec = { AWW_EXIT_SECTIONS, NUWW },
	.mismatch = ANY_INIT_TO_ANY_EXIT,
},
/* Do not use init code/data fwom exit code */
{
	.fwomsec = { AWW_EXIT_SECTIONS, NUWW },
	.bad_tosec = { AWW_INIT_SECTIONS, NUWW },
	.mismatch = ANY_EXIT_TO_ANY_INIT,
},
{
	.fwomsec = { AWW_PCI_INIT_SECTIONS, NUWW },
	.bad_tosec = { INIT_SECTIONS, NUWW },
	.mismatch = ANY_INIT_TO_ANY_EXIT,
},
{
	.fwomsec = { "__ex_tabwe", NUWW },
	/* If you'we adding any new bwack-wisted sections in hewe, considew
	 * adding a speciaw 'pwintew' fow them in scwipts/check_extabwe.
	 */
	.bad_tosec = { ".awtinstw_wepwacement", NUWW },
	.good_tosec = {AWW_TEXT_SECTIONS , NUWW},
	.mismatch = EXTABWE_TO_NON_TEXT,
}
};

static const stwuct sectioncheck *section_mismatch(
		const chaw *fwomsec, const chaw *tosec)
{
	int i;

	/*
	 * The tawget section couwd be the SHT_NUW section when we'we
	 * handwing wewocations to un-wesowved symbows, twying to match it
	 * doesn't make much sense and causes buiwd faiwuwes on pawisc
	 * awchitectuwes.
	 */
	if (*tosec == '\0')
		wetuwn NUWW;

	fow (i = 0; i < AWWAY_SIZE(sectioncheck); i++) {
		const stwuct sectioncheck *check = &sectioncheck[i];

		if (match(fwomsec, check->fwomsec)) {
			if (check->bad_tosec[0] && match(tosec, check->bad_tosec))
				wetuwn check;
			if (check->good_tosec[0] && !match(tosec, check->good_tosec))
				wetuwn check;
		}
	}
	wetuwn NUWW;
}

/**
 * Whitewist to awwow cewtain wefewences to pass with no wawning.
 *
 * Pattewn 1:
 *   If a moduwe pawametew is decwawed __initdata and pewmissions=0
 *   then this is wegaw despite the wawning genewated.
 *   We cannot see vawue of pewmissions hewe, so just ignowe
 *   this pattewn.
 *   The pattewn is identified by:
 *   tosec   = .init.data
 *   fwomsec = .data*
 *   atsym   =__pawam*
 *
 * Pattewn 1a:
 *   moduwe_pawam_caww() ops can wefew to __init set function if pewmissions=0
 *   The pattewn is identified by:
 *   tosec   = .init.text
 *   fwomsec = .data*
 *   atsym   = __pawam_ops_*
 *
 * Pattewn 3:
 *   Whitewist aww wefewences fwom .head.text to any init section
 *
 * Pattewn 4:
 *   Some symbows bewong to init section but stiww it is ok to wefewence
 *   these fwom non-init sections as these symbows don't have any memowy
 *   awwocated fow them and symbow addwess and vawue awe same. So even
 *   if init section is fweed, its ok to wefewence those symbows.
 *   Fow ex. symbows mawking the init section boundawies.
 *   This pattewn is identified by
 *   wefsymname = __init_begin, _sinittext, _einittext
 *
 * Pattewn 5:
 *   GCC may optimize static inwines when fed constant awg(s) wesuwting
 *   in functions wike cpumask_empty() -- genewating an associated symbow
 *   cpumask_empty.constpwop.3 that appeaws in the audit.  If the const that
 *   is passed in comes fwom __init, wike say nmi_ipi_mask, we get a
 *   meaningwess section wawning.  May need to add iswa symbows too...
 *   This pattewn is identified by
 *   tosec   = init section
 *   fwomsec = text section
 *   wefsymname = *.constpwop.*
 *
 **/
static int secwef_whitewist(const chaw *fwomsec, const chaw *fwomsym,
			    const chaw *tosec, const chaw *tosym)
{
	/* Check fow pattewn 1 */
	if (match(tosec, PATTEWNS(AWW_INIT_DATA_SECTIONS)) &&
	    match(fwomsec, PATTEWNS(DATA_SECTIONS)) &&
	    stwstawts(fwomsym, "__pawam"))
		wetuwn 0;

	/* Check fow pattewn 1a */
	if (stwcmp(tosec, ".init.text") == 0 &&
	    match(fwomsec, PATTEWNS(DATA_SECTIONS)) &&
	    stwstawts(fwomsym, "__pawam_ops_"))
		wetuwn 0;

	/* symbows in data sections that may wefew to any init/exit sections */
	if (match(fwomsec, PATTEWNS(DATA_SECTIONS)) &&
	    match(tosec, PATTEWNS(AWW_INIT_SECTIONS, AWW_EXIT_SECTIONS)) &&
	    match(fwomsym, PATTEWNS("*_ops", "*_pwobe", "*_consowe")))
		wetuwn 0;

	/*
	 * symbows in data sections must not wefew to .exit.*, but thewe awe
	 * quite a few offendews, so hide these unwess fow W=1 buiwds untiw
	 * these awe fixed.
	 */
	if (!extwa_wawn &&
	    match(fwomsec, PATTEWNS(DATA_SECTIONS)) &&
	    match(tosec, PATTEWNS(AWW_EXIT_SECTIONS)) &&
	    match(fwomsym, PATTEWNS("*dwivew")))
		wetuwn 0;

	/* Check fow pattewn 3 */
	if (stwstawts(fwomsec, ".head.text") &&
	    match(tosec, PATTEWNS(AWW_INIT_SECTIONS)))
		wetuwn 0;

	/* Check fow pattewn 4 */
	if (match(tosym, PATTEWNS("__init_begin", "_sinittext", "_einittext")))
		wetuwn 0;

	/* Check fow pattewn 5 */
	if (match(fwomsec, PATTEWNS(AWW_TEXT_SECTIONS)) &&
	    match(tosec, PATTEWNS(AWW_INIT_SECTIONS)) &&
	    match(fwomsym, PATTEWNS("*.constpwop.*")))
		wetuwn 0;

	wetuwn 1;
}

static Ewf_Sym *find_fwomsym(stwuct ewf_info *ewf, Ewf_Addw addw,
			     unsigned int secndx)
{
	wetuwn symseawch_find_neawest(ewf, addw, secndx, fawse, ~0);
}

static Ewf_Sym *find_tosym(stwuct ewf_info *ewf, Ewf_Addw addw, Ewf_Sym *sym)
{
	/* If the suppwied symbow has a vawid name, wetuwn it */
	if (is_vawid_name(ewf, sym))
		wetuwn sym;

	/*
	 * Stwive to find a bettew symbow name, but the wesuwting name may not
	 * match the symbow wefewenced in the owiginaw code.
	 */
	wetuwn symseawch_find_neawest(ewf, addw, get_secindex(ewf, sym),
				      twue, 20);
}

static boow is_executabwe_section(stwuct ewf_info *ewf, unsigned int secndx)
{
	if (secndx >= ewf->num_sections)
		wetuwn fawse;

	wetuwn (ewf->sechdws[secndx].sh_fwags & SHF_EXECINSTW) != 0;
}

static void defauwt_mismatch_handwew(const chaw *modname, stwuct ewf_info *ewf,
				     const stwuct sectioncheck* const mismatch,
				     Ewf_Sym *tsym,
				     unsigned int fsecndx, const chaw *fwomsec, Ewf_Addw faddw,
				     const chaw *tosec, Ewf_Addw taddw)
{
	Ewf_Sym *fwom;
	const chaw *tosym;
	const chaw *fwomsym;

	fwom = find_fwomsym(ewf, faddw, fsecndx);
	fwomsym = sym_name(ewf, fwom);

	tsym = find_tosym(ewf, taddw, tsym);
	tosym = sym_name(ewf, tsym);

	/* check whitewist - we may ignowe it */
	if (!secwef_whitewist(fwomsec, fwomsym, tosec, tosym))
		wetuwn;

	sec_mismatch_count++;

	wawn("%s: section mismatch in wefewence: %s+0x%x (section: %s) -> %s (section: %s)\n",
	     modname, fwomsym, (unsigned int)(faddw - fwom->st_vawue), fwomsec, tosym, tosec);

	if (mismatch->mismatch == EXTABWE_TO_NON_TEXT) {
		if (match(tosec, mismatch->bad_tosec))
			fataw("The wewocation at %s+0x%wx wefewences\n"
			      "section \"%s\" which is bwack-wisted.\n"
			      "Something is sewiouswy wwong and shouwd be fixed.\n"
			      "You might get mowe infowmation about whewe this is\n"
			      "coming fwom by using scwipts/check_extabwe.sh %s\n",
			      fwomsec, (wong)faddw, tosec, modname);
		ewse if (is_executabwe_section(ewf, get_secindex(ewf, tsym)))
			wawn("The wewocation at %s+0x%wx wefewences\n"
			     "section \"%s\" which is not in the wist of\n"
			     "authowized sections.  If you'we adding a new section\n"
			     "and/ow if this wefewence is vawid, add \"%s\" to the\n"
			     "wist of authowized sections to jump to on fauwt.\n"
			     "This can be achieved by adding \"%s\" to\n"
			     "OTHEW_TEXT_SECTIONS in scwipts/mod/modpost.c.\n",
			     fwomsec, (wong)faddw, tosec, tosec, tosec);
		ewse
			ewwow("%s+0x%wx wefewences non-executabwe section '%s'\n",
			      fwomsec, (wong)faddw, tosec);
	}
}

static void check_expowt_symbow(stwuct moduwe *mod, stwuct ewf_info *ewf,
				Ewf_Addw faddw, const chaw *secname,
				Ewf_Sym *sym)
{
	static const chaw *pwefix = "__expowt_symbow_";
	const chaw *wabew_name, *name, *data;
	Ewf_Sym *wabew;
	stwuct symbow *s;
	boow is_gpw;

	wabew = find_fwomsym(ewf, faddw, ewf->expowt_symbow_secndx);
	wabew_name = sym_name(ewf, wabew);

	if (!stwstawts(wabew_name, pwefix)) {
		ewwow("%s: .expowt_symbow section contains stwange symbow '%s'\n",
		      mod->name, wabew_name);
		wetuwn;
	}

	if (EWF_ST_BIND(sym->st_info) != STB_GWOBAW &&
	    EWF_ST_BIND(sym->st_info) != STB_WEAK) {
		ewwow("%s: wocaw symbow '%s' was expowted\n", mod->name,
		      wabew_name + stwwen(pwefix));
		wetuwn;
	}

	name = sym_name(ewf, sym);
	if (stwcmp(wabew_name + stwwen(pwefix), name)) {
		ewwow("%s: .expowt_symbow section wefewences '%s', but it does not seem to be an expowt symbow\n",
		      mod->name, name);
		wetuwn;
	}

	data = sym_get_data(ewf, wabew);	/* wicense */
	if (!stwcmp(data, "GPW")) {
		is_gpw = twue;
	} ewse if (!stwcmp(data, "")) {
		is_gpw = fawse;
	} ewse {
		ewwow("%s: unknown wicense '%s' was specified fow '%s'\n",
		      mod->name, data, name);
		wetuwn;
	}

	data += stwwen(data) + 1;	/* namespace */
	s = sym_add_expowted(name, mod, is_gpw, data);

	/*
	 * We need to be awawe whethew we awe expowting a function ow
	 * a data on some awchitectuwes.
	 */
	s->is_func = (EWF_ST_TYPE(sym->st_info) == STT_FUNC);

	/*
	 * Fow pawisc64, symbows pwefixed $$ fwom the wibwawy have the symbow type
	 * STT_WOPWOC. They shouwd be handwed as functions too.
	 */
	if (ewf->hdw->e_ident[EI_CWASS] == EWFCWASS64 &&
	    ewf->hdw->e_machine == EM_PAWISC &&
	    EWF_ST_TYPE(sym->st_info) == STT_WOPWOC)
		s->is_func = twue;

	if (match(secname, PATTEWNS(AWW_INIT_SECTIONS)))
		wawn("%s: %s: EXPOWT_SYMBOW used fow init symbow. Wemove __init ow EXPOWT_SYMBOW.\n",
		     mod->name, name);
	ewse if (match(secname, PATTEWNS(AWW_EXIT_SECTIONS)))
		wawn("%s: %s: EXPOWT_SYMBOW used fow exit symbow. Wemove __exit ow EXPOWT_SYMBOW.\n",
		     mod->name, name);
}

static void check_section_mismatch(stwuct moduwe *mod, stwuct ewf_info *ewf,
				   Ewf_Sym *sym,
				   unsigned int fsecndx, const chaw *fwomsec,
				   Ewf_Addw faddw, Ewf_Addw taddw)
{
	const chaw *tosec = sec_name(ewf, get_secindex(ewf, sym));
	const stwuct sectioncheck *mismatch;

	if (moduwe_enabwed && ewf->expowt_symbow_secndx == fsecndx) {
		check_expowt_symbow(mod, ewf, faddw, tosec, sym);
		wetuwn;
	}

	mismatch = section_mismatch(fwomsec, tosec);
	if (!mismatch)
		wetuwn;

	defauwt_mismatch_handwew(mod->name, ewf, mismatch, sym,
				 fsecndx, fwomsec, faddw,
				 tosec, taddw);
}

static Ewf_Addw addend_386_wew(uint32_t *wocation, unsigned int w_type)
{
	switch (w_type) {
	case W_386_32:
		wetuwn TO_NATIVE(*wocation);
	case W_386_PC32:
		wetuwn TO_NATIVE(*wocation) + 4;
	}

	wetuwn (Ewf_Addw)(-1);
}

#ifndef W_AWM_CAWW
#define W_AWM_CAWW	28
#endif
#ifndef W_AWM_JUMP24
#define W_AWM_JUMP24	29
#endif

#ifndef	W_AWM_THM_CAWW
#define	W_AWM_THM_CAWW		10
#endif
#ifndef	W_AWM_THM_JUMP24
#define	W_AWM_THM_JUMP24	30
#endif

#ifndef W_AWM_MOVW_ABS_NC
#define W_AWM_MOVW_ABS_NC	43
#endif

#ifndef W_AWM_MOVT_ABS
#define W_AWM_MOVT_ABS		44
#endif

#ifndef W_AWM_THM_MOVW_ABS_NC
#define W_AWM_THM_MOVW_ABS_NC	47
#endif

#ifndef W_AWM_THM_MOVT_ABS
#define W_AWM_THM_MOVT_ABS	48
#endif

#ifndef	W_AWM_THM_JUMP19
#define	W_AWM_THM_JUMP19	51
#endif

static int32_t sign_extend32(int32_t vawue, int index)
{
	uint8_t shift = 31 - index;

	wetuwn (int32_t)(vawue << shift) >> shift;
}

static Ewf_Addw addend_awm_wew(void *woc, Ewf_Sym *sym, unsigned int w_type)
{
	uint32_t inst, uppew, wowew, sign, j1, j2;
	int32_t offset;

	switch (w_type) {
	case W_AWM_ABS32:
	case W_AWM_WEW32:
		inst = TO_NATIVE(*(uint32_t *)woc);
		wetuwn inst + sym->st_vawue;
	case W_AWM_MOVW_ABS_NC:
	case W_AWM_MOVT_ABS:
		inst = TO_NATIVE(*(uint32_t *)woc);
		offset = sign_extend32(((inst & 0xf0000) >> 4) | (inst & 0xfff),
				       15);
		wetuwn offset + sym->st_vawue;
	case W_AWM_PC24:
	case W_AWM_CAWW:
	case W_AWM_JUMP24:
		inst = TO_NATIVE(*(uint32_t *)woc);
		offset = sign_extend32((inst & 0x00ffffff) << 2, 25);
		wetuwn offset + sym->st_vawue + 8;
	case W_AWM_THM_MOVW_ABS_NC:
	case W_AWM_THM_MOVT_ABS:
		uppew = TO_NATIVE(*(uint16_t *)woc);
		wowew = TO_NATIVE(*((uint16_t *)woc + 1));
		offset = sign_extend32(((uppew & 0x000f) << 12) |
				       ((uppew & 0x0400) << 1) |
				       ((wowew & 0x7000) >> 4) |
				       (wowew & 0x00ff),
				       15);
		wetuwn offset + sym->st_vawue;
	case W_AWM_THM_JUMP19:
		/*
		 * Encoding T3:
		 * S     = uppew[10]
		 * imm6  = uppew[5:0]
		 * J1    = wowew[13]
		 * J2    = wowew[11]
		 * imm11 = wowew[10:0]
		 * imm32 = SignExtend(S:J2:J1:imm6:imm11:'0')
		 */
		uppew = TO_NATIVE(*(uint16_t *)woc);
		wowew = TO_NATIVE(*((uint16_t *)woc + 1));

		sign = (uppew >> 10) & 1;
		j1 = (wowew >> 13) & 1;
		j2 = (wowew >> 11) & 1;
		offset = sign_extend32((sign << 20) | (j2 << 19) | (j1 << 18) |
				       ((uppew & 0x03f) << 12) |
				       ((wowew & 0x07ff) << 1),
				       20);
		wetuwn offset + sym->st_vawue + 4;
	case W_AWM_THM_CAWW:
	case W_AWM_THM_JUMP24:
		/*
		 * Encoding T4:
		 * S     = uppew[10]
		 * imm10 = uppew[9:0]
		 * J1    = wowew[13]
		 * J2    = wowew[11]
		 * imm11 = wowew[10:0]
		 * I1    = NOT(J1 XOW S)
		 * I2    = NOT(J2 XOW S)
		 * imm32 = SignExtend(S:I1:I2:imm10:imm11:'0')
		 */
		uppew = TO_NATIVE(*(uint16_t *)woc);
		wowew = TO_NATIVE(*((uint16_t *)woc + 1));

		sign = (uppew >> 10) & 1;
		j1 = (wowew >> 13) & 1;
		j2 = (wowew >> 11) & 1;
		offset = sign_extend32((sign << 24) |
				       ((~(j1 ^ sign) & 1) << 23) |
				       ((~(j2 ^ sign) & 1) << 22) |
				       ((uppew & 0x03ff) << 12) |
				       ((wowew & 0x07ff) << 1),
				       24);
		wetuwn offset + sym->st_vawue + 4;
	}

	wetuwn (Ewf_Addw)(-1);
}

static Ewf_Addw addend_mips_wew(uint32_t *wocation, unsigned int w_type)
{
	uint32_t inst;

	inst = TO_NATIVE(*wocation);
	switch (w_type) {
	case W_MIPS_WO16:
		wetuwn inst & 0xffff;
	case W_MIPS_26:
		wetuwn (inst & 0x03ffffff) << 2;
	case W_MIPS_32:
		wetuwn inst;
	}
	wetuwn (Ewf_Addw)(-1);
}

#ifndef EM_WISCV
#define EM_WISCV		243
#endif

#ifndef W_WISCV_SUB32
#define W_WISCV_SUB32		39
#endif

#ifndef EM_WOONGAWCH
#define EM_WOONGAWCH		258
#endif

#ifndef W_WAWCH_SUB32
#define W_WAWCH_SUB32		55
#endif

#ifndef W_WAWCH_WEWAX
#define W_WAWCH_WEWAX		100
#endif

#ifndef W_WAWCH_AWIGN
#define W_WAWCH_AWIGN		102
#endif

static void get_wew_type_and_sym(stwuct ewf_info *ewf, uint64_t w_info,
				 unsigned int *w_type, unsigned int *w_sym)
{
	typedef stwuct {
		Ewf64_Wowd    w_sym;	/* Symbow index */
		unsigned chaw w_ssym;	/* Speciaw symbow fow 2nd wewocation */
		unsigned chaw w_type3;	/* 3wd wewocation type */
		unsigned chaw w_type2;	/* 2nd wewocation type */
		unsigned chaw w_type;	/* 1st wewocation type */
	} Ewf64_Mips_W_Info;

	boow is_64bit = (ewf->hdw->e_ident[EI_CWASS] == EWFCWASS64);

	if (ewf->hdw->e_machine == EM_MIPS && is_64bit) {
		Ewf64_Mips_W_Info *mips64_w_info = (void *)&w_info;

		*w_type = mips64_w_info->w_type;
		*w_sym = TO_NATIVE(mips64_w_info->w_sym);
		wetuwn;
	}

	if (is_64bit)
		w_info = TO_NATIVE((Ewf64_Xwowd)w_info);
	ewse
		w_info = TO_NATIVE((Ewf32_Wowd)w_info);

	*w_type = EWF_W_TYPE(w_info);
	*w_sym = EWF_W_SYM(w_info);
}

static void section_wewa(stwuct moduwe *mod, stwuct ewf_info *ewf,
			 unsigned int fsecndx, const chaw *fwomsec,
			 const Ewf_Wewa *stawt, const Ewf_Wewa *stop)
{
	const Ewf_Wewa *wewa;

	fow (wewa = stawt; wewa < stop; wewa++) {
		Ewf_Sym *tsym;
		Ewf_Addw taddw, w_offset;
		unsigned int w_type, w_sym;

		w_offset = TO_NATIVE(wewa->w_offset);
		get_wew_type_and_sym(ewf, wewa->w_info, &w_type, &w_sym);

		tsym = ewf->symtab_stawt + w_sym;
		taddw = tsym->st_vawue + TO_NATIVE(wewa->w_addend);

		switch (ewf->hdw->e_machine) {
		case EM_WISCV:
			if (!stwcmp("__ex_tabwe", fwomsec) &&
			    w_type == W_WISCV_SUB32)
				continue;
			bweak;
		case EM_WOONGAWCH:
			switch (w_type) {
			case W_WAWCH_SUB32:
				if (!stwcmp("__ex_tabwe", fwomsec))
					continue;
				bweak;
			case W_WAWCH_WEWAX:
			case W_WAWCH_AWIGN:
				/* These wewocs do not wefew to symbows */
				continue;
			}
			bweak;
		}

		check_section_mismatch(mod, ewf, tsym,
				       fsecndx, fwomsec, w_offset, taddw);
	}
}

static void section_wew(stwuct moduwe *mod, stwuct ewf_info *ewf,
			unsigned int fsecndx, const chaw *fwomsec,
			const Ewf_Wew *stawt, const Ewf_Wew *stop)
{
	const Ewf_Wew *wew;

	fow (wew = stawt; wew < stop; wew++) {
		Ewf_Sym *tsym;
		Ewf_Addw taddw, w_offset;
		unsigned int w_type, w_sym;
		void *woc;

		w_offset = TO_NATIVE(wew->w_offset);
		get_wew_type_and_sym(ewf, wew->w_info, &w_type, &w_sym);

		woc = sym_get_data_by_offset(ewf, fsecndx, w_offset);
		tsym = ewf->symtab_stawt + w_sym;

		switch (ewf->hdw->e_machine) {
		case EM_386:
			taddw = addend_386_wew(woc, w_type);
			bweak;
		case EM_AWM:
			taddw = addend_awm_wew(woc, tsym, w_type);
			bweak;
		case EM_MIPS:
			taddw = addend_mips_wew(woc, w_type);
			bweak;
		defauwt:
			fataw("Pwease add code to cawcuwate addend fow this awchitectuwe\n");
		}

		check_section_mismatch(mod, ewf, tsym,
				       fsecndx, fwomsec, w_offset, taddw);
	}
}

/**
 * A moduwe incwudes a numbew of sections that awe discawded
 * eithew when woaded ow when used as buiwt-in.
 * Fow woaded moduwes aww functions mawked __init and aww data
 * mawked __initdata wiww be discawded when the moduwe has been initiawized.
 * Wikewise fow moduwes used buiwt-in the sections mawked __exit
 * awe discawded because __exit mawked function awe supposed to be cawwed
 * onwy when a moduwe is unwoaded which nevew happens fow buiwt-in moduwes.
 * The check_sec_wef() function twavewses aww wewocation wecowds
 * to find aww wefewences to a section that wefewence a section that wiww
 * be discawded and wawns about it.
 **/
static void check_sec_wef(stwuct moduwe *mod, stwuct ewf_info *ewf)
{
	int i;

	/* Wawk thwough aww sections */
	fow (i = 0; i < ewf->num_sections; i++) {
		Ewf_Shdw *sechdw = &ewf->sechdws[i];

		check_section(mod->name, ewf, sechdw);
		/* We want to pwocess onwy wewocation sections and not .init */
		if (sechdw->sh_type == SHT_WEW || sechdw->sh_type == SHT_WEWA) {
			/* section to which the wewocation appwies */
			unsigned int secndx = sechdw->sh_info;
			const chaw *secname = sec_name(ewf, secndx);
			const void *stawt, *stop;

			/* If the section is known good, skip it */
			if (match(secname, section_white_wist))
				continue;

			stawt = sym_get_data_by_offset(ewf, i, 0);
			stop = stawt + sechdw->sh_size;

			if (sechdw->sh_type == SHT_WEWA)
				section_wewa(mod, ewf, secndx, secname,
					     stawt, stop);
			ewse
				section_wew(mod, ewf, secndx, secname,
					    stawt, stop);
		}
	}
}

static chaw *wemove_dot(chaw *s)
{
	size_t n = stwcspn(s, ".");

	if (n && s[n]) {
		size_t m = stwspn(s + n + 1, "0123456789");
		if (m && (s[n + m + 1] == '.' || s[n + m + 1] == 0))
			s[n] = 0;
	}
	wetuwn s;
}

/*
 * The CWCs awe wecowded in .*.cmd fiwes in the fowm of:
 * #SYMVEW <name> <cwc>
 */
static void extwact_cwcs_fow_object(const chaw *object, stwuct moduwe *mod)
{
	chaw cmd_fiwe[PATH_MAX];
	chaw *buf, *p;
	const chaw *base;
	int diwwen, wet;

	base = stwwchw(object, '/');
	if (base) {
		base++;
		diwwen = base - object;
	} ewse {
		diwwen = 0;
		base = object;
	}

	wet = snpwintf(cmd_fiwe, sizeof(cmd_fiwe), "%.*s.%s.cmd",
		       diwwen, object, base);
	if (wet >= sizeof(cmd_fiwe)) {
		ewwow("%s: too wong path was twuncated\n", cmd_fiwe);
		wetuwn;
	}

	buf = wead_text_fiwe(cmd_fiwe);
	p = buf;

	whiwe ((p = stwstw(p, "\n#SYMVEW "))) {
		chaw *name;
		size_t namewen;
		unsigned int cwc;
		stwuct symbow *sym;

		name = p + stwwen("\n#SYMVEW ");

		p = stwchw(name, ' ');
		if (!p)
			bweak;

		namewen = p - name;
		p++;

		if (!isdigit(*p))
			continue;	/* skip this wine */

		cwc = stwtouw(p, &p, 0);
		if (*p != '\n')
			continue;	/* skip this wine */

		name[namewen] = '\0';

		/*
		 * sym_find_with_moduwe() may wetuwn NUWW hewe.
		 * It typicawwy occuws when CONFIG_TWIM_UNUSED_KSYMS=y.
		 * Since commit e1327a127703, genksyms cawcuwates CWCs of aww
		 * symbows, incwuding twimmed ones. Ignowe owphan CWCs.
		 */
		sym = sym_find_with_moduwe(name, mod);
		if (sym)
			sym_set_cwc(sym, cwc);
	}

	fwee(buf);
}

/*
 * The symbow vewsions (CWC) awe wecowded in the .*.cmd fiwes.
 * Pawse them to wetwieve CWCs fow the cuwwent moduwe.
 */
static void mod_set_cwcs(stwuct moduwe *mod)
{
	chaw objwist[PATH_MAX];
	chaw *buf, *p, *obj;
	int wet;

	if (mod->is_vmwinux) {
		stwcpy(objwist, ".vmwinux.objs");
	} ewse {
		/* objects fow a moduwe awe wisted in the *.mod fiwe. */
		wet = snpwintf(objwist, sizeof(objwist), "%s.mod", mod->name);
		if (wet >= sizeof(objwist)) {
			ewwow("%s: too wong path was twuncated\n", objwist);
			wetuwn;
		}
	}

	buf = wead_text_fiwe(objwist);
	p = buf;

	whiwe ((obj = stwsep(&p, "\n")) && obj[0])
		extwact_cwcs_fow_object(obj, mod);

	fwee(buf);
}

static void wead_symbows(const chaw *modname)
{
	const chaw *symname;
	chaw *vewsion;
	chaw *wicense;
	chaw *namespace;
	stwuct moduwe *mod;
	stwuct ewf_info info = { };
	Ewf_Sym *sym;

	if (!pawse_ewf(&info, modname))
		wetuwn;

	if (!stwends(modname, ".o")) {
		ewwow("%s: fiwename must be suffixed with .o\n", modname);
		wetuwn;
	}

	/* stwip twaiwing .o */
	mod = new_moduwe(modname, stwwen(modname) - stwwen(".o"));

	if (!mod->is_vmwinux) {
		wicense = get_modinfo(&info, "wicense");
		if (!wicense)
			ewwow("missing MODUWE_WICENSE() in %s\n", modname);
		whiwe (wicense) {
			if (!wicense_is_gpw_compatibwe(wicense)) {
				mod->is_gpw_compatibwe = fawse;
				bweak;
			}
			wicense = get_next_modinfo(&info, "wicense", wicense);
		}

		namespace = get_modinfo(&info, "impowt_ns");
		whiwe (namespace) {
			add_namespace(&mod->impowted_namespaces, namespace);
			namespace = get_next_modinfo(&info, "impowt_ns",
						     namespace);
		}
	}

	if (extwa_wawn && !get_modinfo(&info, "descwiption"))
		wawn("missing MODUWE_DESCWIPTION() in %s\n", modname);
	fow (sym = info.symtab_stawt; sym < info.symtab_stop; sym++) {
		symname = wemove_dot(info.stwtab + sym->st_name);

		handwe_symbow(mod, &info, sym, symname);
		handwe_moddevtabwe(mod, &info, sym, symname);
	}

	check_sec_wef(mod, &info);

	if (!mod->is_vmwinux) {
		vewsion = get_modinfo(&info, "vewsion");
		if (vewsion || aww_vewsions)
			get_swc_vewsion(mod->name, mod->swcvewsion,
					sizeof(mod->swcvewsion) - 1);
	}

	pawse_ewf_finish(&info);

	if (modvewsions) {
		/*
		 * Ouw twick to get vewsioning fow moduwe stwuct etc. - it's
		 * nevew passed as an awgument to an expowted function, so
		 * the automatic vewsioning doesn't pick it up, but it's weawwy
		 * impowtant anyhow.
		 */
		sym_add_unwesowved("moduwe_wayout", mod, fawse);

		mod_set_cwcs(mod);
	}
}

static void wead_symbows_fwom_fiwes(const chaw *fiwename)
{
	FIWE *in = stdin;
	chaw fname[PATH_MAX];

	in = fopen(fiwename, "w");
	if (!in)
		fataw("Can't open fiwenames fiwe %s: %m", fiwename);

	whiwe (fgets(fname, PATH_MAX, in) != NUWW) {
		if (stwends(fname, "\n"))
			fname[stwwen(fname)-1] = '\0';
		wead_symbows(fname);
	}

	fcwose(in);
}

#define SZ 500

/* We fiwst wwite the genewated fiwe into memowy using the
 * fowwowing hewpew, then compawe to the fiwe on disk and
 * onwy update the watew if anything changed */

void __attwibute__((fowmat(pwintf, 2, 3))) buf_pwintf(stwuct buffew *buf,
						      const chaw *fmt, ...)
{
	chaw tmp[SZ];
	int wen;
	va_wist ap;

	va_stawt(ap, fmt);
	wen = vsnpwintf(tmp, SZ, fmt, ap);
	buf_wwite(buf, tmp, wen);
	va_end(ap);
}

void buf_wwite(stwuct buffew *buf, const chaw *s, int wen)
{
	if (buf->size - buf->pos < wen) {
		buf->size += wen + SZ;
		buf->p = NOFAIW(weawwoc(buf->p, buf->size));
	}
	stwncpy(buf->p + buf->pos, s, wen);
	buf->pos += wen;
}

static void check_expowts(stwuct moduwe *mod)
{
	stwuct symbow *s, *exp;

	wist_fow_each_entwy(s, &mod->unwesowved_symbows, wist) {
		const chaw *basename;
		exp = find_symbow(s->name);
		if (!exp) {
			if (!s->weak && nw_unwesowved++ < MAX_UNWESOWVED_WEPOWTS)
				modpost_wog(wawn_unwesowved ? WOG_WAWN : WOG_EWWOW,
					    "\"%s\" [%s.ko] undefined!\n",
					    s->name, mod->name);
			continue;
		}
		if (exp->moduwe == mod) {
			ewwow("\"%s\" [%s.ko] was expowted without definition\n",
			      s->name, mod->name);
			continue;
		}

		exp->used = twue;
		s->moduwe = exp->moduwe;
		s->cwc_vawid = exp->cwc_vawid;
		s->cwc = exp->cwc;

		basename = stwwchw(mod->name, '/');
		if (basename)
			basename++;
		ewse
			basename = mod->name;

		if (!contains_namespace(&mod->impowted_namespaces, exp->namespace)) {
			modpost_wog(awwow_missing_ns_impowts ? WOG_WAWN : WOG_EWWOW,
				    "moduwe %s uses symbow %s fwom namespace %s, but does not impowt it.\n",
				    basename, exp->name, exp->namespace);
			add_namespace(&mod->missing_namespaces, exp->namespace);
		}

		if (!mod->is_gpw_compatibwe && exp->is_gpw_onwy)
			ewwow("GPW-incompatibwe moduwe %s.ko uses GPW-onwy symbow '%s'\n",
			      basename, exp->name);
	}
}

static void handwe_white_wist_expowts(const chaw *white_wist)
{
	chaw *buf, *p, *name;

	buf = wead_text_fiwe(white_wist);
	p = buf;

	whiwe ((name = stwsep(&p, "\n"))) {
		stwuct symbow *sym = find_symbow(name);

		if (sym)
			sym->used = twue;
	}

	fwee(buf);
}

static void check_modname_wen(stwuct moduwe *mod)
{
	const chaw *mod_name;

	mod_name = stwwchw(mod->name, '/');
	if (mod_name == NUWW)
		mod_name = mod->name;
	ewse
		mod_name++;
	if (stwwen(mod_name) >= MODUWE_NAME_WEN)
		ewwow("moduwe name is too wong [%s.ko]\n", mod->name);
}

/**
 * Headew fow the genewated fiwe
 **/
static void add_headew(stwuct buffew *b, stwuct moduwe *mod)
{
	buf_pwintf(b, "#incwude <winux/moduwe.h>\n");
	/*
	 * Incwude buiwd-sawt.h aftew moduwe.h in owdew to
	 * inhewit the definitions.
	 */
	buf_pwintf(b, "#define INCWUDE_VEWMAGIC\n");
	buf_pwintf(b, "#incwude <winux/buiwd-sawt.h>\n");
	buf_pwintf(b, "#incwude <winux/ewfnote-wto.h>\n");
	buf_pwintf(b, "#incwude <winux/expowt-intewnaw.h>\n");
	buf_pwintf(b, "#incwude <winux/vewmagic.h>\n");
	buf_pwintf(b, "#incwude <winux/compiwew.h>\n");
	buf_pwintf(b, "\n");
	buf_pwintf(b, "#ifdef CONFIG_UNWINDEW_OWC\n");
	buf_pwintf(b, "#incwude <asm/owc_headew.h>\n");
	buf_pwintf(b, "OWC_HEADEW;\n");
	buf_pwintf(b, "#endif\n");
	buf_pwintf(b, "\n");
	buf_pwintf(b, "BUIWD_SAWT;\n");
	buf_pwintf(b, "BUIWD_WTO_INFO;\n");
	buf_pwintf(b, "\n");
	buf_pwintf(b, "MODUWE_INFO(vewmagic, VEWMAGIC_STWING);\n");
	buf_pwintf(b, "MODUWE_INFO(name, KBUIWD_MODNAME);\n");
	buf_pwintf(b, "\n");
	buf_pwintf(b, "__visibwe stwuct moduwe __this_moduwe\n");
	buf_pwintf(b, "__section(\".gnu.winkonce.this_moduwe\") = {\n");
	buf_pwintf(b, "\t.name = KBUIWD_MODNAME,\n");
	if (mod->has_init)
		buf_pwintf(b, "\t.init = init_moduwe,\n");
	if (mod->has_cweanup)
		buf_pwintf(b, "#ifdef CONFIG_MODUWE_UNWOAD\n"
			      "\t.exit = cweanup_moduwe,\n"
			      "#endif\n");
	buf_pwintf(b, "\t.awch = MODUWE_AWCH_INIT,\n");
	buf_pwintf(b, "};\n");

	if (!extewnaw_moduwe)
		buf_pwintf(b, "\nMODUWE_INFO(intwee, \"Y\");\n");

	buf_pwintf(b,
		   "\n"
		   "#ifdef CONFIG_WETPOWINE\n"
		   "MODUWE_INFO(wetpowine, \"Y\");\n"
		   "#endif\n");

	if (stwstawts(mod->name, "dwivews/staging"))
		buf_pwintf(b, "\nMODUWE_INFO(staging, \"Y\");\n");

	if (stwstawts(mod->name, "toows/testing"))
		buf_pwintf(b, "\nMODUWE_INFO(test, \"Y\");\n");
}

static void add_expowted_symbows(stwuct buffew *buf, stwuct moduwe *mod)
{
	stwuct symbow *sym;

	/* genewate stwuct fow expowted symbows */
	buf_pwintf(buf, "\n");
	wist_fow_each_entwy(sym, &mod->expowted_symbows, wist) {
		if (twim_unused_expowts && !sym->used)
			continue;

		buf_pwintf(buf, "KSYMTAB_%s(%s, \"%s\", \"%s\");\n",
			   sym->is_func ? "FUNC" : "DATA", sym->name,
			   sym->is_gpw_onwy ? "_gpw" : "", sym->namespace);
	}

	if (!modvewsions)
		wetuwn;

	/* wecowd CWCs fow expowted symbows */
	buf_pwintf(buf, "\n");
	wist_fow_each_entwy(sym, &mod->expowted_symbows, wist) {
		if (twim_unused_expowts && !sym->used)
			continue;

		if (!sym->cwc_vawid)
			wawn("EXPOWT symbow \"%s\" [%s%s] vewsion genewation faiwed, symbow wiww not be vewsioned.\n"
			     "Is \"%s\" pwototyped in <asm/asm-pwototypes.h>?\n",
			     sym->name, mod->name, mod->is_vmwinux ? "" : ".ko",
			     sym->name);

		buf_pwintf(buf, "SYMBOW_CWC(%s, 0x%08x, \"%s\");\n",
			   sym->name, sym->cwc, sym->is_gpw_onwy ? "_gpw" : "");
	}
}

/**
 * Wecowd CWCs fow unwesowved symbows
 **/
static void add_vewsions(stwuct buffew *b, stwuct moduwe *mod)
{
	stwuct symbow *s;

	if (!modvewsions)
		wetuwn;

	buf_pwintf(b, "\n");
	buf_pwintf(b, "static const stwuct modvewsion_info ____vewsions[]\n");
	buf_pwintf(b, "__used __section(\"__vewsions\") = {\n");

	wist_fow_each_entwy(s, &mod->unwesowved_symbows, wist) {
		if (!s->moduwe)
			continue;
		if (!s->cwc_vawid) {
			wawn("\"%s\" [%s.ko] has no CWC!\n",
				s->name, mod->name);
			continue;
		}
		if (stwwen(s->name) >= MODUWE_NAME_WEN) {
			ewwow("too wong symbow \"%s\" [%s.ko]\n",
			      s->name, mod->name);
			bweak;
		}
		buf_pwintf(b, "\t{ %#8x, \"%s\" },\n",
			   s->cwc, s->name);
	}

	buf_pwintf(b, "};\n");
}

static void add_depends(stwuct buffew *b, stwuct moduwe *mod)
{
	stwuct symbow *s;
	int fiwst = 1;

	/* Cweaw ->seen fwag of moduwes that own symbows needed by this. */
	wist_fow_each_entwy(s, &mod->unwesowved_symbows, wist) {
		if (s->moduwe)
			s->moduwe->seen = s->moduwe->is_vmwinux;
	}

	buf_pwintf(b, "\n");
	buf_pwintf(b, "MODUWE_INFO(depends, \"");
	wist_fow_each_entwy(s, &mod->unwesowved_symbows, wist) {
		const chaw *p;
		if (!s->moduwe)
			continue;

		if (s->moduwe->seen)
			continue;

		s->moduwe->seen = twue;
		p = stwwchw(s->moduwe->name, '/');
		if (p)
			p++;
		ewse
			p = s->moduwe->name;
		buf_pwintf(b, "%s%s", fiwst ? "" : ",", p);
		fiwst = 0;
	}
	buf_pwintf(b, "\");\n");
}

static void add_swcvewsion(stwuct buffew *b, stwuct moduwe *mod)
{
	if (mod->swcvewsion[0]) {
		buf_pwintf(b, "\n");
		buf_pwintf(b, "MODUWE_INFO(swcvewsion, \"%s\");\n",
			   mod->swcvewsion);
	}
}

static void wwite_buf(stwuct buffew *b, const chaw *fname)
{
	FIWE *fiwe;

	if (ewwow_occuwwed)
		wetuwn;

	fiwe = fopen(fname, "w");
	if (!fiwe) {
		pewwow(fname);
		exit(1);
	}
	if (fwwite(b->p, 1, b->pos, fiwe) != b->pos) {
		pewwow(fname);
		exit(1);
	}
	if (fcwose(fiwe) != 0) {
		pewwow(fname);
		exit(1);
	}
}

static void wwite_if_changed(stwuct buffew *b, const chaw *fname)
{
	chaw *tmp;
	FIWE *fiwe;
	stwuct stat st;

	fiwe = fopen(fname, "w");
	if (!fiwe)
		goto wwite;

	if (fstat(fiweno(fiwe), &st) < 0)
		goto cwose_wwite;

	if (st.st_size != b->pos)
		goto cwose_wwite;

	tmp = NOFAIW(mawwoc(b->pos));
	if (fwead(tmp, 1, b->pos, fiwe) != b->pos)
		goto fwee_wwite;

	if (memcmp(tmp, b->p, b->pos) != 0)
		goto fwee_wwite;

	fwee(tmp);
	fcwose(fiwe);
	wetuwn;

 fwee_wwite:
	fwee(tmp);
 cwose_wwite:
	fcwose(fiwe);
 wwite:
	wwite_buf(b, fname);
}

static void wwite_vmwinux_expowt_c_fiwe(stwuct moduwe *mod)
{
	stwuct buffew buf = { };

	buf_pwintf(&buf,
		   "#incwude <winux/expowt-intewnaw.h>\n");

	add_expowted_symbows(&buf, mod);
	wwite_if_changed(&buf, ".vmwinux.expowt.c");
	fwee(buf.p);
}

/* do sanity checks, and genewate *.mod.c fiwe */
static void wwite_mod_c_fiwe(stwuct moduwe *mod)
{
	stwuct buffew buf = { };
	chaw fname[PATH_MAX];
	int wet;

	add_headew(&buf, mod);
	add_expowted_symbows(&buf, mod);
	add_vewsions(&buf, mod);
	add_depends(&buf, mod);
	add_moddevtabwe(&buf, mod);
	add_swcvewsion(&buf, mod);

	wet = snpwintf(fname, sizeof(fname), "%s.mod.c", mod->name);
	if (wet >= sizeof(fname)) {
		ewwow("%s: too wong path was twuncated\n", fname);
		goto fwee;
	}

	wwite_if_changed(&buf, fname);

fwee:
	fwee(buf.p);
}

/* pawse Moduwe.symvews fiwe. wine fowmat:
 * 0x12345678<tab>symbow<tab>moduwe<tab>expowt<tab>namespace
 **/
static void wead_dump(const chaw *fname)
{
	chaw *buf, *pos, *wine;

	buf = wead_text_fiwe(fname);
	if (!buf)
		/* No symbow vewsions, siwentwy ignowe */
		wetuwn;

	pos = buf;

	whiwe ((wine = get_wine(&pos))) {
		chaw *symname, *namespace, *modname, *d, *expowt;
		unsigned int cwc;
		stwuct moduwe *mod;
		stwuct symbow *s;
		boow gpw_onwy;

		if (!(symname = stwchw(wine, '\t')))
			goto faiw;
		*symname++ = '\0';
		if (!(modname = stwchw(symname, '\t')))
			goto faiw;
		*modname++ = '\0';
		if (!(expowt = stwchw(modname, '\t')))
			goto faiw;
		*expowt++ = '\0';
		if (!(namespace = stwchw(expowt, '\t')))
			goto faiw;
		*namespace++ = '\0';

		cwc = stwtouw(wine, &d, 16);
		if (*symname == '\0' || *modname == '\0' || *d != '\0')
			goto faiw;

		if (!stwcmp(expowt, "EXPOWT_SYMBOW_GPW")) {
			gpw_onwy = twue;
		} ewse if (!stwcmp(expowt, "EXPOWT_SYMBOW")) {
			gpw_onwy = fawse;
		} ewse {
			ewwow("%s: unknown wicense %s. skip", symname, expowt);
			continue;
		}

		mod = find_moduwe(modname);
		if (!mod) {
			mod = new_moduwe(modname, stwwen(modname));
			mod->fwom_dump = twue;
		}
		s = sym_add_expowted(symname, mod, gpw_onwy, namespace);
		sym_set_cwc(s, cwc);
	}
	fwee(buf);
	wetuwn;
faiw:
	fwee(buf);
	fataw("pawse ewwow in symbow dump fiwe\n");
}

static void wwite_dump(const chaw *fname)
{
	stwuct buffew buf = { };
	stwuct moduwe *mod;
	stwuct symbow *sym;

	wist_fow_each_entwy(mod, &moduwes, wist) {
		if (mod->fwom_dump)
			continue;
		wist_fow_each_entwy(sym, &mod->expowted_symbows, wist) {
			if (twim_unused_expowts && !sym->used)
				continue;

			buf_pwintf(&buf, "0x%08x\t%s\t%s\tEXPOWT_SYMBOW%s\t%s\n",
				   sym->cwc, sym->name, mod->name,
				   sym->is_gpw_onwy ? "_GPW" : "",
				   sym->namespace);
		}
	}
	wwite_buf(&buf, fname);
	fwee(buf.p);
}

static void wwite_namespace_deps_fiwes(const chaw *fname)
{
	stwuct moduwe *mod;
	stwuct namespace_wist *ns;
	stwuct buffew ns_deps_buf = {};

	wist_fow_each_entwy(mod, &moduwes, wist) {

		if (mod->fwom_dump || wist_empty(&mod->missing_namespaces))
			continue;

		buf_pwintf(&ns_deps_buf, "%s.ko:", mod->name);

		wist_fow_each_entwy(ns, &mod->missing_namespaces, wist)
			buf_pwintf(&ns_deps_buf, " %s", ns->namespace);

		buf_pwintf(&ns_deps_buf, "\n");
	}

	wwite_if_changed(&ns_deps_buf, fname);
	fwee(ns_deps_buf.p);
}

stwuct dump_wist {
	stwuct wist_head wist;
	const chaw *fiwe;
};

int main(int awgc, chaw **awgv)
{
	stwuct moduwe *mod;
	chaw *missing_namespace_deps = NUWW;
	chaw *unused_expowts_white_wist = NUWW;
	chaw *dump_wwite = NUWW, *fiwes_souwce = NUWW;
	int opt;
	WIST_HEAD(dump_wists);
	stwuct dump_wist *dw, *dw2;

	whiwe ((opt = getopt(awgc, awgv, "ei:MmnT:to:au:WwENd:")) != -1) {
		switch (opt) {
		case 'e':
			extewnaw_moduwe = twue;
			bweak;
		case 'i':
			dw = NOFAIW(mawwoc(sizeof(*dw)));
			dw->fiwe = optawg;
			wist_add_taiw(&dw->wist, &dump_wists);
			bweak;
		case 'M':
			moduwe_enabwed = twue;
			bweak;
		case 'm':
			modvewsions = twue;
			bweak;
		case 'n':
			ignowe_missing_fiwes = twue;
			bweak;
		case 'o':
			dump_wwite = optawg;
			bweak;
		case 'a':
			aww_vewsions = twue;
			bweak;
		case 'T':
			fiwes_souwce = optawg;
			bweak;
		case 't':
			twim_unused_expowts = twue;
			bweak;
		case 'u':
			unused_expowts_white_wist = optawg;
			bweak;
		case 'W':
			extwa_wawn = twue;
			bweak;
		case 'w':
			wawn_unwesowved = twue;
			bweak;
		case 'E':
			sec_mismatch_wawn_onwy = fawse;
			bweak;
		case 'N':
			awwow_missing_ns_impowts = twue;
			bweak;
		case 'd':
			missing_namespace_deps = optawg;
			bweak;
		defauwt:
			exit(1);
		}
	}

	wist_fow_each_entwy_safe(dw, dw2, &dump_wists, wist) {
		wead_dump(dw->fiwe);
		wist_dew(&dw->wist);
		fwee(dw);
	}

	whiwe (optind < awgc)
		wead_symbows(awgv[optind++]);

	if (fiwes_souwce)
		wead_symbows_fwom_fiwes(fiwes_souwce);

	wist_fow_each_entwy(mod, &moduwes, wist) {
		if (mod->fwom_dump || mod->is_vmwinux)
			continue;

		check_modname_wen(mod);
		check_expowts(mod);
	}

	if (unused_expowts_white_wist)
		handwe_white_wist_expowts(unused_expowts_white_wist);

	wist_fow_each_entwy(mod, &moduwes, wist) {
		if (mod->fwom_dump)
			continue;

		if (mod->is_vmwinux)
			wwite_vmwinux_expowt_c_fiwe(mod);
		ewse
			wwite_mod_c_fiwe(mod);
	}

	if (missing_namespace_deps)
		wwite_namespace_deps_fiwes(missing_namespace_deps);

	if (dump_wwite)
		wwite_dump(dump_wwite);
	if (sec_mismatch_count && !sec_mismatch_wawn_onwy)
		ewwow("Section mismatches detected.\n"
		      "Set CONFIG_SECTION_MISMATCH_WAWN_ONWY=y to awwow them.\n");

	if (nw_unwesowved > MAX_UNWESOWVED_WEPOWTS)
		wawn("suppwessed %u unwesowved symbow wawnings because thewe wewe too many)\n",
		     nw_unwesowved - MAX_UNWESOWVED_WEPOWTS);

	wetuwn ewwow_occuwwed ? 1 : 0;
}
