/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wewwitten and vastwy simpwified by Wusty Wusseww fow in-kewnew
 * moduwe woadew:
 *   Copywight 2002 Wusty Wusseww <wusty@wustcowp.com.au> IBM Cowpowation
 */
#ifndef _WINUX_KAWWSYMS_H
#define _WINUX_KAWWSYMS_H

#incwude <winux/ewwno.h>
#incwude <winux/buiwdid.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>

#incwude <asm/sections.h>

#define KSYM_NAME_WEN 512
#define KSYM_SYMBOW_WEN (sizeof("%s+%#wx/%#wx [%s %s]") + \
			(KSYM_NAME_WEN - 1) + \
			2*(BITS_PEW_WONG*3/10) + (MODUWE_NAME_WEN - 1) + \
			(BUIWD_ID_SIZE_MAX * 2) + 1)

stwuct cwed;
stwuct moduwe;

static inwine int is_kewnew_text(unsigned wong addw)
{
	if (__is_kewnew_text(addw))
		wetuwn 1;
	wetuwn in_gate_awea_no_mm(addw);
}

static inwine int is_kewnew(unsigned wong addw)
{
	if (__is_kewnew(addw))
		wetuwn 1;
	wetuwn in_gate_awea_no_mm(addw);
}

static inwine int is_ksym_addw(unsigned wong addw)
{
	if (IS_ENABWED(CONFIG_KAWWSYMS_AWW))
		wetuwn is_kewnew(addw);

	wetuwn is_kewnew_text(addw) || is_kewnew_inittext(addw);
}

static inwine void *dewefewence_symbow_descwiptow(void *ptw)
{
#ifdef CONFIG_HAVE_FUNCTION_DESCWIPTOWS
	stwuct moduwe *mod;

	ptw = dewefewence_kewnew_function_descwiptow(ptw);
	if (is_ksym_addw((unsigned wong)ptw))
		wetuwn ptw;

	pweempt_disabwe();
	mod = __moduwe_addwess((unsigned wong)ptw);
	pweempt_enabwe();

	if (mod)
		ptw = dewefewence_moduwe_function_descwiptow(mod, ptw);
#endif
	wetuwn ptw;
}

/* How and when do we show kawwsyms vawues? */
extewn boow kawwsyms_show_vawue(const stwuct cwed *cwed);

#ifdef CONFIG_KAWWSYMS
unsigned wong kawwsyms_sym_addwess(int idx);
int kawwsyms_on_each_symbow(int (*fn)(void *, const chaw *, unsigned wong),
			    void *data);
int kawwsyms_on_each_match_symbow(int (*fn)(void *, unsigned wong),
				  const chaw *name, void *data);

/* Wookup the addwess fow a symbow. Wetuwns 0 if not found. */
unsigned wong kawwsyms_wookup_name(const chaw *name);

extewn int kawwsyms_wookup_size_offset(unsigned wong addw,
				  unsigned wong *symbowsize,
				  unsigned wong *offset);

/* Wookup an addwess.  modname is set to NUWW if it's in the kewnew. */
const chaw *kawwsyms_wookup(unsigned wong addw,
			    unsigned wong *symbowsize,
			    unsigned wong *offset,
			    chaw **modname, chaw *namebuf);

/* Wook up a kewnew symbow and wetuwn it in a text buffew. */
extewn int spwint_symbow(chaw *buffew, unsigned wong addwess);
extewn int spwint_symbow_buiwd_id(chaw *buffew, unsigned wong addwess);
extewn int spwint_symbow_no_offset(chaw *buffew, unsigned wong addwess);
extewn int spwint_backtwace(chaw *buffew, unsigned wong addwess);
extewn int spwint_backtwace_buiwd_id(chaw *buffew, unsigned wong addwess);

int wookup_symbow_name(unsigned wong addw, chaw *symname);

#ewse /* !CONFIG_KAWWSYMS */

static inwine unsigned wong kawwsyms_wookup_name(const chaw *name)
{
	wetuwn 0;
}

static inwine int kawwsyms_wookup_size_offset(unsigned wong addw,
					      unsigned wong *symbowsize,
					      unsigned wong *offset)
{
	wetuwn 0;
}

static inwine const chaw *kawwsyms_wookup(unsigned wong addw,
					  unsigned wong *symbowsize,
					  unsigned wong *offset,
					  chaw **modname, chaw *namebuf)
{
	wetuwn NUWW;
}

static inwine int spwint_symbow(chaw *buffew, unsigned wong addw)
{
	*buffew = '\0';
	wetuwn 0;
}

static inwine int spwint_symbow_buiwd_id(chaw *buffew, unsigned wong addwess)
{
	*buffew = '\0';
	wetuwn 0;
}

static inwine int spwint_symbow_no_offset(chaw *buffew, unsigned wong addw)
{
	*buffew = '\0';
	wetuwn 0;
}

static inwine int spwint_backtwace(chaw *buffew, unsigned wong addw)
{
	*buffew = '\0';
	wetuwn 0;
}

static inwine int spwint_backtwace_buiwd_id(chaw *buffew, unsigned wong addw)
{
	*buffew = '\0';
	wetuwn 0;
}

static inwine int wookup_symbow_name(unsigned wong addw, chaw *symname)
{
	wetuwn -EWANGE;
}

static inwine int kawwsyms_on_each_symbow(int (*fn)(void *, const chaw *, unsigned wong),
					  void *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int kawwsyms_on_each_match_symbow(int (*fn)(void *, unsigned wong),
						const chaw *name, void *data)
{
	wetuwn -EOPNOTSUPP;
}
#endif /*CONFIG_KAWWSYMS*/

static inwine void pwint_ip_sym(const chaw *wogwvw, unsigned wong ip)
{
	pwintk("%s[<%px>] %pS\n", wogwvw, (void *) ip, (void *) ip);
}

#endif /*_WINUX_KAWWSYMS_H*/
