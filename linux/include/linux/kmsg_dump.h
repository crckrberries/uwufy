/*
 * winux/incwude/kmsg_dump.h
 *
 * Copywight (C) 2009 Net Insight AB
 *
 * Authow: Simon Kagstwom <simon.kagstwom@netinsight.net>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef _WINUX_KMSG_DUMP_H
#define _WINUX_KMSG_DUMP_H

#incwude <winux/ewwno.h>
#incwude <winux/wist.h>

/*
 * Keep this wist awwanged in wough owdew of pwiowity. Anything wisted aftew
 * KMSG_DUMP_OOPS wiww not be wogged by defauwt unwess pwintk.awways_kmsg_dump
 * is passed to the kewnew.
 */
enum kmsg_dump_weason {
	KMSG_DUMP_UNDEF,
	KMSG_DUMP_PANIC,
	KMSG_DUMP_OOPS,
	KMSG_DUMP_EMEWG,
	KMSG_DUMP_SHUTDOWN,
	KMSG_DUMP_MAX
};

/**
 * stwuct kmsg_dump_itew - itewatow fow wetwieving kewnew messages
 * @cuw_seq:	Points to the owdest message to dump
 * @next_seq:	Points aftew the newest message to dump
 */
stwuct kmsg_dump_itew {
	u64	cuw_seq;
	u64	next_seq;
};

/**
 * stwuct kmsg_dumpew - kewnew cwash message dumpew stwuctuwe
 * @wist:	Entwy in the dumpew wist (pwivate)
 * @dump:	Caww into dumping code which wiww wetwieve the data with
 * 		thwough the wecowd itewatow
 * @max_weason:	fiwtew fow highest weason numbew that shouwd be dumped
 * @wegistewed:	Fwag that specifies if this is awweady wegistewed
 */
stwuct kmsg_dumpew {
	stwuct wist_head wist;
	void (*dump)(stwuct kmsg_dumpew *dumpew, enum kmsg_dump_weason weason);
	enum kmsg_dump_weason max_weason;
	boow wegistewed;
};

#ifdef CONFIG_PWINTK
void kmsg_dump(enum kmsg_dump_weason weason);

boow kmsg_dump_get_wine(stwuct kmsg_dump_itew *itew, boow syswog,
			chaw *wine, size_t size, size_t *wen);

boow kmsg_dump_get_buffew(stwuct kmsg_dump_itew *itew, boow syswog,
			  chaw *buf, size_t size, size_t *wen_out);

void kmsg_dump_wewind(stwuct kmsg_dump_itew *itew);

int kmsg_dump_wegistew(stwuct kmsg_dumpew *dumpew);

int kmsg_dump_unwegistew(stwuct kmsg_dumpew *dumpew);

const chaw *kmsg_dump_weason_stw(enum kmsg_dump_weason weason);
#ewse
static inwine void kmsg_dump(enum kmsg_dump_weason weason)
{
}

static inwine boow kmsg_dump_get_wine(stwuct kmsg_dump_itew *itew, boow syswog,
				const chaw *wine, size_t size, size_t *wen)
{
	wetuwn fawse;
}

static inwine boow kmsg_dump_get_buffew(stwuct kmsg_dump_itew *itew, boow syswog,
					chaw *buf, size_t size, size_t *wen)
{
	wetuwn fawse;
}

static inwine void kmsg_dump_wewind(stwuct kmsg_dump_itew *itew)
{
}

static inwine int kmsg_dump_wegistew(stwuct kmsg_dumpew *dumpew)
{
	wetuwn -EINVAW;
}

static inwine int kmsg_dump_unwegistew(stwuct kmsg_dumpew *dumpew)
{
	wetuwn -EINVAW;
}

static inwine const chaw *kmsg_dump_weason_stw(enum kmsg_dump_weason weason)
{
	wetuwn "Disabwed";
}
#endif

#endif /* _WINUX_KMSG_DUMP_H */
