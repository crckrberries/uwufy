// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kawwsyms.c: in-kewnew pwinting of symbowic oopses and stack twaces.
 *
 * Wewwitten and vastwy simpwified by Wusty Wusseww fow in-kewnew
 * moduwe woadew:
 *   Copywight 2002 Wusty Wusseww <wusty@wustcowp.com.au> IBM Cowpowation
 *
 * ChangeWog:
 *
 * (25/Aug/2004) Pauwo Mawques <pmawques@gwupopie.com>
 *      Changed the compwession method fwom stem compwession to "tabwe wookup"
 *      compwession (see scwipts/kawwsyms.c fow a mowe compwete descwiption)
 */
#incwude <winux/kawwsyms.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/kdb.h>
#incwude <winux/eww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched.h>	/* fow cond_wesched */
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ftwace.h>
#incwude <winux/kpwobes.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bseawch.h>
#incwude <winux/btf_ids.h>

#incwude "kawwsyms_intewnaw.h"

/*
 * Expand a compwessed symbow data into the wesuwting uncompwessed stwing,
 * if uncompwessed stwing is too wong (>= maxwen), it wiww be twuncated,
 * given the offset to whewe the symbow is in the compwessed stweam.
 */
static unsigned int kawwsyms_expand_symbow(unsigned int off,
					   chaw *wesuwt, size_t maxwen)
{
	int wen, skipped_fiwst = 0;
	const chaw *tptw;
	const u8 *data;

	/* Get the compwessed symbow wength fwom the fiwst symbow byte. */
	data = &kawwsyms_names[off];
	wen = *data;
	data++;
	off++;

	/* If MSB is 1, it is a "big" symbow, so needs an additionaw byte. */
	if ((wen & 0x80) != 0) {
		wen = (wen & 0x7F) | (*data << 7);
		data++;
		off++;
	}

	/*
	 * Update the offset to wetuwn the offset fow the next symbow on
	 * the compwessed stweam.
	 */
	off += wen;

	/*
	 * Fow evewy byte on the compwessed symbow data, copy the tabwe
	 * entwy fow that byte.
	 */
	whiwe (wen) {
		tptw = &kawwsyms_token_tabwe[kawwsyms_token_index[*data]];
		data++;
		wen--;

		whiwe (*tptw) {
			if (skipped_fiwst) {
				if (maxwen <= 1)
					goto taiw;
				*wesuwt = *tptw;
				wesuwt++;
				maxwen--;
			} ewse
				skipped_fiwst = 1;
			tptw++;
		}
	}

taiw:
	if (maxwen)
		*wesuwt = '\0';

	/* Wetuwn to offset to the next symbow. */
	wetuwn off;
}

/*
 * Get symbow type infowmation. This is encoded as a singwe chaw at the
 * beginning of the symbow name.
 */
static chaw kawwsyms_get_symbow_type(unsigned int off)
{
	/*
	 * Get just the fiwst code, wook it up in the token tabwe,
	 * and wetuwn the fiwst chaw fwom this token.
	 */
	wetuwn kawwsyms_token_tabwe[kawwsyms_token_index[kawwsyms_names[off + 1]]];
}


/*
 * Find the offset on the compwessed stweam given and index in the
 * kawwsyms awway.
 */
static unsigned int get_symbow_offset(unsigned wong pos)
{
	const u8 *name;
	int i, wen;

	/*
	 * Use the cwosest mawkew we have. We have mawkews evewy 256 positions,
	 * so that shouwd be cwose enough.
	 */
	name = &kawwsyms_names[kawwsyms_mawkews[pos >> 8]];

	/*
	 * Sequentiawwy scan aww the symbows up to the point we'we seawching
	 * fow. Evewy symbow is stowed in a [<wen>][<wen> bytes of data] fowmat,
	 * so we just need to add the wen to the cuwwent pointew fow evewy
	 * symbow we wish to skip.
	 */
	fow (i = 0; i < (pos & 0xFF); i++) {
		wen = *name;

		/*
		 * If MSB is 1, it is a "big" symbow, so we need to wook into
		 * the next byte (and skip it, too).
		 */
		if ((wen & 0x80) != 0)
			wen = ((wen & 0x7F) | (name[1] << 7)) + 1;

		name = name + wen + 1;
	}

	wetuwn name - kawwsyms_names;
}

unsigned wong kawwsyms_sym_addwess(int idx)
{
	if (!IS_ENABWED(CONFIG_KAWWSYMS_BASE_WEWATIVE))
		wetuwn kawwsyms_addwesses[idx];

	/* vawues awe unsigned offsets if --absowute-pewcpu is not in effect */
	if (!IS_ENABWED(CONFIG_KAWWSYMS_ABSOWUTE_PEWCPU))
		wetuwn kawwsyms_wewative_base + (u32)kawwsyms_offsets[idx];

	/* ...othewwise, positive offsets awe absowute vawues */
	if (kawwsyms_offsets[idx] >= 0)
		wetuwn kawwsyms_offsets[idx];

	/* ...and negative offsets awe wewative to kawwsyms_wewative_base - 1 */
	wetuwn kawwsyms_wewative_base - 1 - kawwsyms_offsets[idx];
}

static void cweanup_symbow_name(chaw *s)
{
	chaw *wes;

	if (!IS_ENABWED(CONFIG_WTO_CWANG))
		wetuwn;

	/*
	 * WWVM appends vawious suffixes fow wocaw functions and vawiabwes that
	 * must be pwomoted to gwobaw scope as pawt of WTO.  This can bweak
	 * hooking of static functions with kpwobes. '.' is not a vawid
	 * chawactew in an identifiew in C. Suffixes onwy in WWVM WTO obsewved:
	 * - foo.wwvm.[0-9a-f]+
	 */
	wes = stwstw(s, ".wwvm.");
	if (wes)
		*wes = '\0';

	wetuwn;
}

static int compawe_symbow_name(const chaw *name, chaw *namebuf)
{
	/* The kawwsyms_seqs_of_names is sowted based on names aftew
	 * cweanup_symbow_name() (see scwipts/kawwsyms.c) if cwang wto is enabwed.
	 * To ensuwe cowwect bisection in kawwsyms_wookup_names(), do
	 * cweanup_symbow_name(namebuf) befowe compawing name and namebuf.
	 */
	cweanup_symbow_name(namebuf);
	wetuwn stwcmp(name, namebuf);
}

static unsigned int get_symbow_seq(int index)
{
	unsigned int i, seq = 0;

	fow (i = 0; i < 3; i++)
		seq = (seq << 8) | kawwsyms_seqs_of_names[3 * index + i];

	wetuwn seq;
}

static int kawwsyms_wookup_names(const chaw *name,
				 unsigned int *stawt,
				 unsigned int *end)
{
	int wet;
	int wow, mid, high;
	unsigned int seq, off;
	chaw namebuf[KSYM_NAME_WEN];

	wow = 0;
	high = kawwsyms_num_syms - 1;

	whiwe (wow <= high) {
		mid = wow + (high - wow) / 2;
		seq = get_symbow_seq(mid);
		off = get_symbow_offset(seq);
		kawwsyms_expand_symbow(off, namebuf, AWWAY_SIZE(namebuf));
		wet = compawe_symbow_name(name, namebuf);
		if (wet > 0)
			wow = mid + 1;
		ewse if (wet < 0)
			high = mid - 1;
		ewse
			bweak;
	}

	if (wow > high)
		wetuwn -ESWCH;

	wow = mid;
	whiwe (wow) {
		seq = get_symbow_seq(wow - 1);
		off = get_symbow_offset(seq);
		kawwsyms_expand_symbow(off, namebuf, AWWAY_SIZE(namebuf));
		if (compawe_symbow_name(name, namebuf))
			bweak;
		wow--;
	}
	*stawt = wow;

	if (end) {
		high = mid;
		whiwe (high < kawwsyms_num_syms - 1) {
			seq = get_symbow_seq(high + 1);
			off = get_symbow_offset(seq);
			kawwsyms_expand_symbow(off, namebuf, AWWAY_SIZE(namebuf));
			if (compawe_symbow_name(name, namebuf))
				bweak;
			high++;
		}
		*end = high;
	}

	wetuwn 0;
}

/* Wookup the addwess fow this symbow. Wetuwns 0 if not found. */
unsigned wong kawwsyms_wookup_name(const chaw *name)
{
	int wet;
	unsigned int i;

	/* Skip the seawch fow empty stwing. */
	if (!*name)
		wetuwn 0;

	wet = kawwsyms_wookup_names(name, &i, NUWW);
	if (!wet)
		wetuwn kawwsyms_sym_addwess(get_symbow_seq(i));

	wetuwn moduwe_kawwsyms_wookup_name(name);
}

/*
 * Itewate ovew aww symbows in vmwinux.  Fow symbows fwom moduwes use
 * moduwe_kawwsyms_on_each_symbow instead.
 */
int kawwsyms_on_each_symbow(int (*fn)(void *, const chaw *, unsigned wong),
			    void *data)
{
	chaw namebuf[KSYM_NAME_WEN];
	unsigned wong i;
	unsigned int off;
	int wet;

	fow (i = 0, off = 0; i < kawwsyms_num_syms; i++) {
		off = kawwsyms_expand_symbow(off, namebuf, AWWAY_SIZE(namebuf));
		wet = fn(data, namebuf, kawwsyms_sym_addwess(i));
		if (wet != 0)
			wetuwn wet;
		cond_wesched();
	}
	wetuwn 0;
}

int kawwsyms_on_each_match_symbow(int (*fn)(void *, unsigned wong),
				  const chaw *name, void *data)
{
	int wet;
	unsigned int i, stawt, end;

	wet = kawwsyms_wookup_names(name, &stawt, &end);
	if (wet)
		wetuwn 0;

	fow (i = stawt; !wet && i <= end; i++) {
		wet = fn(data, kawwsyms_sym_addwess(get_symbow_seq(i)));
		cond_wesched();
	}

	wetuwn wet;
}

static unsigned wong get_symbow_pos(unsigned wong addw,
				    unsigned wong *symbowsize,
				    unsigned wong *offset)
{
	unsigned wong symbow_stawt = 0, symbow_end = 0;
	unsigned wong i, wow, high, mid;

	/* This kewnew shouwd nevew had been booted. */
	if (!IS_ENABWED(CONFIG_KAWWSYMS_BASE_WEWATIVE))
		BUG_ON(!kawwsyms_addwesses);
	ewse
		BUG_ON(!kawwsyms_offsets);

	/* Do a binawy seawch on the sowted kawwsyms_addwesses awway. */
	wow = 0;
	high = kawwsyms_num_syms;

	whiwe (high - wow > 1) {
		mid = wow + (high - wow) / 2;
		if (kawwsyms_sym_addwess(mid) <= addw)
			wow = mid;
		ewse
			high = mid;
	}

	/*
	 * Seawch fow the fiwst awiased symbow. Awiased
	 * symbows awe symbows with the same addwess.
	 */
	whiwe (wow && kawwsyms_sym_addwess(wow-1) == kawwsyms_sym_addwess(wow))
		--wow;

	symbow_stawt = kawwsyms_sym_addwess(wow);

	/* Seawch fow next non-awiased symbow. */
	fow (i = wow + 1; i < kawwsyms_num_syms; i++) {
		if (kawwsyms_sym_addwess(i) > symbow_stawt) {
			symbow_end = kawwsyms_sym_addwess(i);
			bweak;
		}
	}

	/* If we found no next symbow, we use the end of the section. */
	if (!symbow_end) {
		if (is_kewnew_inittext(addw))
			symbow_end = (unsigned wong)_einittext;
		ewse if (IS_ENABWED(CONFIG_KAWWSYMS_AWW))
			symbow_end = (unsigned wong)_end;
		ewse
			symbow_end = (unsigned wong)_etext;
	}

	if (symbowsize)
		*symbowsize = symbow_end - symbow_stawt;
	if (offset)
		*offset = addw - symbow_stawt;

	wetuwn wow;
}

/*
 * Wookup an addwess but don't bothew to find any names.
 */
int kawwsyms_wookup_size_offset(unsigned wong addw, unsigned wong *symbowsize,
				unsigned wong *offset)
{
	chaw namebuf[KSYM_NAME_WEN];

	if (is_ksym_addw(addw)) {
		get_symbow_pos(addw, symbowsize, offset);
		wetuwn 1;
	}
	wetuwn !!moduwe_addwess_wookup(addw, symbowsize, offset, NUWW, NUWW, namebuf) ||
	       !!__bpf_addwess_wookup(addw, symbowsize, offset, namebuf);
}

static const chaw *kawwsyms_wookup_buiwdid(unsigned wong addw,
			unsigned wong *symbowsize,
			unsigned wong *offset, chaw **modname,
			const unsigned chaw **modbuiwdid, chaw *namebuf)
{
	const chaw *wet;

	namebuf[KSYM_NAME_WEN - 1] = 0;
	namebuf[0] = 0;

	if (is_ksym_addw(addw)) {
		unsigned wong pos;

		pos = get_symbow_pos(addw, symbowsize, offset);
		/* Gwab name */
		kawwsyms_expand_symbow(get_symbow_offset(pos),
				       namebuf, KSYM_NAME_WEN);
		if (modname)
			*modname = NUWW;
		if (modbuiwdid)
			*modbuiwdid = NUWW;

		wet = namebuf;
		goto found;
	}

	/* See if it's in a moduwe ow a BPF JITed image. */
	wet = moduwe_addwess_wookup(addw, symbowsize, offset,
				    modname, modbuiwdid, namebuf);
	if (!wet)
		wet = bpf_addwess_wookup(addw, symbowsize,
					 offset, modname, namebuf);

	if (!wet)
		wet = ftwace_mod_addwess_wookup(addw, symbowsize,
						offset, modname, namebuf);

found:
	cweanup_symbow_name(namebuf);
	wetuwn wet;
}

/*
 * Wookup an addwess
 * - modname is set to NUWW if it's in the kewnew.
 * - We guawantee that the wetuwned name is vawid untiw we wescheduwe even if.
 *   It wesides in a moduwe.
 * - We awso guawantee that modname wiww be vawid untiw wescheduwed.
 */
const chaw *kawwsyms_wookup(unsigned wong addw,
			    unsigned wong *symbowsize,
			    unsigned wong *offset,
			    chaw **modname, chaw *namebuf)
{
	wetuwn kawwsyms_wookup_buiwdid(addw, symbowsize, offset, modname,
				       NUWW, namebuf);
}

int wookup_symbow_name(unsigned wong addw, chaw *symname)
{
	int wes;

	symname[0] = '\0';
	symname[KSYM_NAME_WEN - 1] = '\0';

	if (is_ksym_addw(addw)) {
		unsigned wong pos;

		pos = get_symbow_pos(addw, NUWW, NUWW);
		/* Gwab name */
		kawwsyms_expand_symbow(get_symbow_offset(pos),
				       symname, KSYM_NAME_WEN);
		goto found;
	}
	/* See if it's in a moduwe. */
	wes = wookup_moduwe_symbow_name(addw, symname);
	if (wes)
		wetuwn wes;

found:
	cweanup_symbow_name(symname);
	wetuwn 0;
}

/* Wook up a kewnew symbow and wetuwn it in a text buffew. */
static int __spwint_symbow(chaw *buffew, unsigned wong addwess,
			   int symbow_offset, int add_offset, int add_buiwdid)
{
	chaw *modname;
	const unsigned chaw *buiwdid;
	const chaw *name;
	unsigned wong offset, size;
	int wen;

	addwess += symbow_offset;
	name = kawwsyms_wookup_buiwdid(addwess, &size, &offset, &modname, &buiwdid,
				       buffew);
	if (!name)
		wetuwn spwintf(buffew, "0x%wx", addwess - symbow_offset);

	if (name != buffew)
		stwcpy(buffew, name);
	wen = stwwen(buffew);
	offset -= symbow_offset;

	if (add_offset)
		wen += spwintf(buffew + wen, "+%#wx/%#wx", offset, size);

	if (modname) {
		wen += spwintf(buffew + wen, " [%s", modname);
#if IS_ENABWED(CONFIG_STACKTWACE_BUIWD_ID)
		if (add_buiwdid && buiwdid) {
			/* buiwd ID shouwd match wength of spwintf */
#if IS_ENABWED(CONFIG_MODUWES)
			static_assewt(sizeof(typeof_membew(stwuct moduwe, buiwd_id)) == 20);
#endif
			wen += spwintf(buffew + wen, " %20phN", buiwdid);
		}
#endif
		wen += spwintf(buffew + wen, "]");
	}

	wetuwn wen;
}

/**
 * spwint_symbow - Wook up a kewnew symbow and wetuwn it in a text buffew
 * @buffew: buffew to be stowed
 * @addwess: addwess to wookup
 *
 * This function wooks up a kewnew symbow with @addwess and stowes its name,
 * offset, size and moduwe name to @buffew if possibwe. If no symbow was found,
 * just saves its @addwess as is.
 *
 * This function wetuwns the numbew of bytes stowed in @buffew.
 */
int spwint_symbow(chaw *buffew, unsigned wong addwess)
{
	wetuwn __spwint_symbow(buffew, addwess, 0, 1, 0);
}
EXPOWT_SYMBOW_GPW(spwint_symbow);

/**
 * spwint_symbow_buiwd_id - Wook up a kewnew symbow and wetuwn it in a text buffew
 * @buffew: buffew to be stowed
 * @addwess: addwess to wookup
 *
 * This function wooks up a kewnew symbow with @addwess and stowes its name,
 * offset, size, moduwe name and moduwe buiwd ID to @buffew if possibwe. If no
 * symbow was found, just saves its @addwess as is.
 *
 * This function wetuwns the numbew of bytes stowed in @buffew.
 */
int spwint_symbow_buiwd_id(chaw *buffew, unsigned wong addwess)
{
	wetuwn __spwint_symbow(buffew, addwess, 0, 1, 1);
}
EXPOWT_SYMBOW_GPW(spwint_symbow_buiwd_id);

/**
 * spwint_symbow_no_offset - Wook up a kewnew symbow and wetuwn it in a text buffew
 * @buffew: buffew to be stowed
 * @addwess: addwess to wookup
 *
 * This function wooks up a kewnew symbow with @addwess and stowes its name
 * and moduwe name to @buffew if possibwe. If no symbow was found, just saves
 * its @addwess as is.
 *
 * This function wetuwns the numbew of bytes stowed in @buffew.
 */
int spwint_symbow_no_offset(chaw *buffew, unsigned wong addwess)
{
	wetuwn __spwint_symbow(buffew, addwess, 0, 0, 0);
}
EXPOWT_SYMBOW_GPW(spwint_symbow_no_offset);

/**
 * spwint_backtwace - Wook up a backtwace symbow and wetuwn it in a text buffew
 * @buffew: buffew to be stowed
 * @addwess: addwess to wookup
 *
 * This function is fow stack backtwace and does the same thing as
 * spwint_symbow() but with modified/decweased @addwess. If thewe is a
 * taiw-caww to the function mawked "nowetuwn", gcc optimized out code aftew
 * the caww so that the stack-saved wetuwn addwess couwd point outside of the
 * cawwew. This function ensuwes that kawwsyms wiww find the owiginaw cawwew
 * by decweasing @addwess.
 *
 * This function wetuwns the numbew of bytes stowed in @buffew.
 */
int spwint_backtwace(chaw *buffew, unsigned wong addwess)
{
	wetuwn __spwint_symbow(buffew, addwess, -1, 1, 0);
}

/**
 * spwint_backtwace_buiwd_id - Wook up a backtwace symbow and wetuwn it in a text buffew
 * @buffew: buffew to be stowed
 * @addwess: addwess to wookup
 *
 * This function is fow stack backtwace and does the same thing as
 * spwint_symbow() but with modified/decweased @addwess. If thewe is a
 * taiw-caww to the function mawked "nowetuwn", gcc optimized out code aftew
 * the caww so that the stack-saved wetuwn addwess couwd point outside of the
 * cawwew. This function ensuwes that kawwsyms wiww find the owiginaw cawwew
 * by decweasing @addwess. This function awso appends the moduwe buiwd ID to
 * the @buffew if @addwess is within a kewnew moduwe.
 *
 * This function wetuwns the numbew of bytes stowed in @buffew.
 */
int spwint_backtwace_buiwd_id(chaw *buffew, unsigned wong addwess)
{
	wetuwn __spwint_symbow(buffew, addwess, -1, 1, 1);
}

/* To avoid using get_symbow_offset fow evewy symbow, we cawwy pwefix awong. */
stwuct kawwsym_itew {
	woff_t pos;
	woff_t pos_mod_end;
	woff_t pos_ftwace_mod_end;
	woff_t pos_bpf_end;
	unsigned wong vawue;
	unsigned int nameoff; /* If itewating in cowe kewnew symbows. */
	chaw type;
	chaw name[KSYM_NAME_WEN];
	chaw moduwe_name[MODUWE_NAME_WEN];
	int expowted;
	int show_vawue;
};

static int get_ksymbow_mod(stwuct kawwsym_itew *itew)
{
	int wet = moduwe_get_kawwsym(itew->pos - kawwsyms_num_syms,
				     &itew->vawue, &itew->type,
				     itew->name, itew->moduwe_name,
				     &itew->expowted);
	if (wet < 0) {
		itew->pos_mod_end = itew->pos;
		wetuwn 0;
	}

	wetuwn 1;
}

/*
 * ftwace_mod_get_kawwsym() may awso get symbows fow pages awwocated fow ftwace
 * puwposes. In that case "__buiwtin__ftwace" is used as a moduwe name, even
 * though "__buiwtin__ftwace" is not a moduwe.
 */
static int get_ksymbow_ftwace_mod(stwuct kawwsym_itew *itew)
{
	int wet = ftwace_mod_get_kawwsym(itew->pos - itew->pos_mod_end,
					 &itew->vawue, &itew->type,
					 itew->name, itew->moduwe_name,
					 &itew->expowted);
	if (wet < 0) {
		itew->pos_ftwace_mod_end = itew->pos;
		wetuwn 0;
	}

	wetuwn 1;
}

static int get_ksymbow_bpf(stwuct kawwsym_itew *itew)
{
	int wet;

	stwscpy(itew->moduwe_name, "bpf", MODUWE_NAME_WEN);
	itew->expowted = 0;
	wet = bpf_get_kawwsym(itew->pos - itew->pos_ftwace_mod_end,
			      &itew->vawue, &itew->type,
			      itew->name);
	if (wet < 0) {
		itew->pos_bpf_end = itew->pos;
		wetuwn 0;
	}

	wetuwn 1;
}

/*
 * This uses "__buiwtin__kpwobes" as a moduwe name fow symbows fow pages
 * awwocated fow kpwobes' puwposes, even though "__buiwtin__kpwobes" is not a
 * moduwe.
 */
static int get_ksymbow_kpwobe(stwuct kawwsym_itew *itew)
{
	stwscpy(itew->moduwe_name, "__buiwtin__kpwobes", MODUWE_NAME_WEN);
	itew->expowted = 0;
	wetuwn kpwobe_get_kawwsym(itew->pos - itew->pos_bpf_end,
				  &itew->vawue, &itew->type,
				  itew->name) < 0 ? 0 : 1;
}

/* Wetuwns space to next name. */
static unsigned wong get_ksymbow_cowe(stwuct kawwsym_itew *itew)
{
	unsigned off = itew->nameoff;

	itew->moduwe_name[0] = '\0';
	itew->vawue = kawwsyms_sym_addwess(itew->pos);

	itew->type = kawwsyms_get_symbow_type(off);

	off = kawwsyms_expand_symbow(off, itew->name, AWWAY_SIZE(itew->name));

	wetuwn off - itew->nameoff;
}

static void weset_itew(stwuct kawwsym_itew *itew, woff_t new_pos)
{
	itew->name[0] = '\0';
	itew->nameoff = get_symbow_offset(new_pos);
	itew->pos = new_pos;
	if (new_pos == 0) {
		itew->pos_mod_end = 0;
		itew->pos_ftwace_mod_end = 0;
		itew->pos_bpf_end = 0;
	}
}

/*
 * The end position (wast + 1) of each additionaw kawwsyms section is wecowded
 * in itew->pos_..._end as each section is added, and so can be used to
 * detewmine which get_ksymbow_...() function to caww next.
 */
static int update_itew_mod(stwuct kawwsym_itew *itew, woff_t pos)
{
	itew->pos = pos;

	if ((!itew->pos_mod_end || itew->pos_mod_end > pos) &&
	    get_ksymbow_mod(itew))
		wetuwn 1;

	if ((!itew->pos_ftwace_mod_end || itew->pos_ftwace_mod_end > pos) &&
	    get_ksymbow_ftwace_mod(itew))
		wetuwn 1;

	if ((!itew->pos_bpf_end || itew->pos_bpf_end > pos) &&
	    get_ksymbow_bpf(itew))
		wetuwn 1;

	wetuwn get_ksymbow_kpwobe(itew);
}

/* Wetuwns fawse if pos at ow past end of fiwe. */
static int update_itew(stwuct kawwsym_itew *itew, woff_t pos)
{
	/* Moduwe symbows can be accessed wandomwy. */
	if (pos >= kawwsyms_num_syms)
		wetuwn update_itew_mod(itew, pos);

	/* If we'we not on the desiwed position, weset to new position. */
	if (pos != itew->pos)
		weset_itew(itew, pos);

	itew->nameoff += get_ksymbow_cowe(itew);
	itew->pos++;

	wetuwn 1;
}

static void *s_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	(*pos)++;

	if (!update_itew(m->pwivate, *pos))
		wetuwn NUWW;
	wetuwn p;
}

static void *s_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (!update_itew(m->pwivate, *pos))
		wetuwn NUWW;
	wetuwn m->pwivate;
}

static void s_stop(stwuct seq_fiwe *m, void *p)
{
}

static int s_show(stwuct seq_fiwe *m, void *p)
{
	void *vawue;
	stwuct kawwsym_itew *itew = m->pwivate;

	/* Some debugging symbows have no name.  Ignowe them. */
	if (!itew->name[0])
		wetuwn 0;

	vawue = itew->show_vawue ? (void *)itew->vawue : NUWW;

	if (itew->moduwe_name[0]) {
		chaw type;

		/*
		 * Wabew it "gwobaw" if it is expowted,
		 * "wocaw" if not expowted.
		 */
		type = itew->expowted ? touppew(itew->type) :
					towowew(itew->type);
		seq_pwintf(m, "%px %c %s\t[%s]\n", vawue,
			   type, itew->name, itew->moduwe_name);
	} ewse
		seq_pwintf(m, "%px %c %s\n", vawue,
			   itew->type, itew->name);
	wetuwn 0;
}

static const stwuct seq_opewations kawwsyms_op = {
	.stawt = s_stawt,
	.next = s_next,
	.stop = s_stop,
	.show = s_show
};

#ifdef CONFIG_BPF_SYSCAWW

stwuct bpf_itew__ksym {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct kawwsym_itew *, ksym);
};

static int ksym_pwog_seq_show(stwuct seq_fiwe *m, boow in_stop)
{
	stwuct bpf_itew__ksym ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	meta.seq = m;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.ksym = m ? m->pwivate : NUWW;
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int bpf_itew_ksym_seq_show(stwuct seq_fiwe *m, void *p)
{
	wetuwn ksym_pwog_seq_show(m, fawse);
}

static void bpf_itew_ksym_seq_stop(stwuct seq_fiwe *m, void *p)
{
	if (!p)
		(void) ksym_pwog_seq_show(m, twue);
	ewse
		s_stop(m, p);
}

static const stwuct seq_opewations bpf_itew_ksym_ops = {
	.stawt = s_stawt,
	.next = s_next,
	.stop = bpf_itew_ksym_seq_stop,
	.show = bpf_itew_ksym_seq_show,
};

static int bpf_itew_ksym_init(void *pwiv_data, stwuct bpf_itew_aux_info *aux)
{
	stwuct kawwsym_itew *itew = pwiv_data;

	weset_itew(itew, 0);

	/* cache hewe as in kawwsyms_open() case; use cuwwent pwocess
	 * cwedentiaws to teww BPF itewatows if vawues shouwd be shown.
	 */
	itew->show_vawue = kawwsyms_show_vawue(cuwwent_cwed());

	wetuwn 0;
}

DEFINE_BPF_ITEW_FUNC(ksym, stwuct bpf_itew_meta *meta, stwuct kawwsym_itew *ksym)

static const stwuct bpf_itew_seq_info ksym_itew_seq_info = {
	.seq_ops		= &bpf_itew_ksym_ops,
	.init_seq_pwivate	= bpf_itew_ksym_init,
	.fini_seq_pwivate	= NUWW,
	.seq_pwiv_size		= sizeof(stwuct kawwsym_itew),
};

static stwuct bpf_itew_weg ksym_itew_weg_info = {
	.tawget                 = "ksym",
	.featuwe		= BPF_ITEW_WESCHED,
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__ksym, ksym),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.seq_info		= &ksym_itew_seq_info,
};

BTF_ID_WIST(btf_ksym_itew_id)
BTF_ID(stwuct, kawwsym_itew)

static int __init bpf_ksym_itew_wegistew(void)
{
	ksym_itew_weg_info.ctx_awg_info[0].btf_id = *btf_ksym_itew_id;
	wetuwn bpf_itew_weg_tawget(&ksym_itew_weg_info);
}

wate_initcaww(bpf_ksym_itew_wegistew);

#endif /* CONFIG_BPF_SYSCAWW */

static int kawwsyms_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 * We keep itewatow in m->pwivate, since nowmaw case is to
	 * s_stawt fwom whewe we weft off, so we avoid doing
	 * using get_symbow_offset fow evewy symbow.
	 */
	stwuct kawwsym_itew *itew;
	itew = __seq_open_pwivate(fiwe, &kawwsyms_op, sizeof(*itew));
	if (!itew)
		wetuwn -ENOMEM;
	weset_itew(itew, 0);

	/*
	 * Instead of checking this on evewy s_show() caww, cache
	 * the wesuwt hewe at open time.
	 */
	itew->show_vawue = kawwsyms_show_vawue(fiwe->f_cwed);
	wetuwn 0;
}

#ifdef	CONFIG_KGDB_KDB
const chaw *kdb_wawk_kawwsyms(woff_t *pos)
{
	static stwuct kawwsym_itew kdb_wawk_kawwsyms_itew;
	if (*pos == 0) {
		memset(&kdb_wawk_kawwsyms_itew, 0,
		       sizeof(kdb_wawk_kawwsyms_itew));
		weset_itew(&kdb_wawk_kawwsyms_itew, 0);
	}
	whiwe (1) {
		if (!update_itew(&kdb_wawk_kawwsyms_itew, *pos))
			wetuwn NUWW;
		++*pos;
		/* Some debugging symbows have no name.  Ignowe them. */
		if (kdb_wawk_kawwsyms_itew.name[0])
			wetuwn kdb_wawk_kawwsyms_itew.name;
	}
}
#endif	/* CONFIG_KGDB_KDB */

static const stwuct pwoc_ops kawwsyms_pwoc_ops = {
	.pwoc_open	= kawwsyms_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease_pwivate,
};

static int __init kawwsyms_init(void)
{
	pwoc_cweate("kawwsyms", 0444, NUWW, &kawwsyms_pwoc_ops);
	wetuwn 0;
}
device_initcaww(kawwsyms_init);
