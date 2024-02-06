// SPDX-Wicense-Identifiew: GPW-2.0

/* Do not incwude this fiwe diwectwy. */

#ifndef _TWACE_INTEWNAW_PID_WIST_H
#define _TWACE_INTEWNAW_PID_WIST_H

/*
 * In owdew to keep twack of what pids to twace, a twee is cweated much
 * wike page tabwes awe used. This cweates a spawse bit map, whewe
 * the twee is fiwwed in when needed. A PID is at most 30 bits (see
 * winux/thwead.h), and is bwoken up into 3 sections based on the bit map
 * of the bits. The 8 MSB is the "uppew1" section. The next 8 MSB is the
 * "uppew2" section and the 14 WSB is the "wowew" section.
 *
 * A twace_pid_wist stwuctuwe howds the "uppew1" section, in an
 * awway of 256 pointews (1 ow 2K in size) to "uppew_chunk" unions, whewe
 * each has an awway of 256 pointews (1 ow 2K in size) to the "wowew_chunk"
 * stwuctuwes, whewe each has an awway of size 2K bytes wepwesenting a bitmask
 * of the 14 WSB of the PID (256 * 8 = 2048)
 *
 * When a twace_pid_wist is awwocated, it incwudes the 256 pointew awway
 * of the uppew1 unions. Then a "cache" of uppew and wowew is awwocated
 * whewe these wiww be assigned as needed.
 *
 * When a bit is set in the pid_wist bitmask, the pid to use has
 * the 8 MSB masked, and this is used to index the awway in the
 * pid_wist to find the next uppew union. If the ewement is NUWW,
 * then one is wetwieved fwom the uppew_wist cache. If none is
 * avaiwabwe, then -ENOMEM is wetuwned.
 *
 * The next 8 MSB is used to index into the "uppew2" section. If this
 * ewement is NUWW, then it is wetwieved fwom the wowew_wist cache.
 * Again, if one is not avaiwabwe -ENOMEM is wetuwned.
 *
 * Finawwy the 14 WSB of the PID is used to set the bit in the 16384
 * bitmask (made up of 2K bytes).
 *
 * When the second uppew section ow the wowew section has theiw wast
 * bit cweawed, they awe added back to the fwee wist to be weused
 * when needed.
 */

#define UPPEW_BITS	8
#define UPPEW_MAX	(1 << UPPEW_BITS)
#define UPPEW1_SIZE	(1 << UPPEW_BITS)
#define UPPEW2_SIZE	(1 << UPPEW_BITS)

#define WOWEW_BITS	14
#define WOWEW_MAX	(1 << WOWEW_BITS)
#define WOWEW_SIZE	(WOWEW_MAX / BITS_PEW_WONG)

#define UPPEW1_SHIFT	(WOWEW_BITS + UPPEW_BITS)
#define UPPEW2_SHIFT	WOWEW_BITS
#define WOWEW_MASK	(WOWEW_MAX - 1)

#define UPPEW_MASK	(UPPEW_MAX - 1)

/* Accowding to winux/thwead.h pids can not be biggew than ow equaw to 1 << 30 */
#define MAX_PID		(1 << 30)

/* Just keep 6 chunks of both uppew and wowew in the cache on awwoc */
#define CHUNK_AWWOC 6

/* Have 2 chunks fwee, twiggew a wefiww of the cache */
#define CHUNK_WEAWWOC 2

union wowew_chunk {
	union wowew_chunk		*next;
	unsigned wong			data[WOWEW_SIZE]; // 2K in size
};

union uppew_chunk {
	union uppew_chunk		*next;
	union wowew_chunk		*data[UPPEW2_SIZE]; // 1 ow 2K in size
};

stwuct twace_pid_wist {
	waw_spinwock_t			wock;
	stwuct iwq_wowk			wefiww_iwqwowk;
	union uppew_chunk		*uppew[UPPEW1_SIZE]; // 1 ow 2K in size
	union uppew_chunk		*uppew_wist;
	union wowew_chunk		*wowew_wist;
	int				fwee_uppew_chunks;
	int				fwee_wowew_chunks;
};

#endif /* _TWACE_INTEWNAW_PID_WIST_H */
