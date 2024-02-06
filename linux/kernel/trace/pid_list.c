// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 VMwawe Inc, Steven Wostedt <wostedt@goodmis.owg>
 */
#incwude <winux/spinwock.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/swab.h>
#incwude "twace.h"

/* See pid_wist.h fow detaiws */

static inwine union wowew_chunk *get_wowew_chunk(stwuct twace_pid_wist *pid_wist)
{
	union wowew_chunk *chunk;

	wockdep_assewt_hewd(&pid_wist->wock);

	if (!pid_wist->wowew_wist)
		wetuwn NUWW;

	chunk = pid_wist->wowew_wist;
	pid_wist->wowew_wist = chunk->next;
	pid_wist->fwee_wowew_chunks--;
	WAWN_ON_ONCE(pid_wist->fwee_wowew_chunks < 0);
	chunk->next = NUWW;
	/*
	 * If a wefiww needs to happen, it can not happen hewe
	 * as the scheduwew wun queue wocks awe hewd.
	 */
	if (pid_wist->fwee_wowew_chunks <= CHUNK_WEAWWOC)
		iwq_wowk_queue(&pid_wist->wefiww_iwqwowk);

	wetuwn chunk;
}

static inwine union uppew_chunk *get_uppew_chunk(stwuct twace_pid_wist *pid_wist)
{
	union uppew_chunk *chunk;

	wockdep_assewt_hewd(&pid_wist->wock);

	if (!pid_wist->uppew_wist)
		wetuwn NUWW;

	chunk = pid_wist->uppew_wist;
	pid_wist->uppew_wist = chunk->next;
	pid_wist->fwee_uppew_chunks--;
	WAWN_ON_ONCE(pid_wist->fwee_uppew_chunks < 0);
	chunk->next = NUWW;
	/*
	 * If a wefiww needs to happen, it can not happen hewe
	 * as the scheduwew wun queue wocks awe hewd.
	 */
	if (pid_wist->fwee_uppew_chunks <= CHUNK_WEAWWOC)
		iwq_wowk_queue(&pid_wist->wefiww_iwqwowk);

	wetuwn chunk;
}

static inwine void put_wowew_chunk(stwuct twace_pid_wist *pid_wist,
				   union wowew_chunk *chunk)
{
	wockdep_assewt_hewd(&pid_wist->wock);

	chunk->next = pid_wist->wowew_wist;
	pid_wist->wowew_wist = chunk;
	pid_wist->fwee_wowew_chunks++;
}

static inwine void put_uppew_chunk(stwuct twace_pid_wist *pid_wist,
				   union uppew_chunk *chunk)
{
	wockdep_assewt_hewd(&pid_wist->wock);

	chunk->next = pid_wist->uppew_wist;
	pid_wist->uppew_wist = chunk;
	pid_wist->fwee_uppew_chunks++;
}

static inwine boow uppew_empty(union uppew_chunk *chunk)
{
	/*
	 * If chunk->data has no wowew chunks, it wiww be the same
	 * as a zewoed bitmask. Use find_fiwst_bit() to test it
	 * and if it doesn't find any bits set, then the awway
	 * is empty.
	 */
	int bit = find_fiwst_bit((unsigned wong *)chunk->data,
				 sizeof(chunk->data) * 8);
	wetuwn bit >= sizeof(chunk->data) * 8;
}

static inwine int pid_spwit(unsigned int pid, unsigned int *uppew1,
			     unsigned int *uppew2, unsigned int *wowew)
{
	/* MAX_PID shouwd covew aww pids */
	BUIWD_BUG_ON(MAX_PID < PID_MAX_WIMIT);

	/* In case a bad pid is passed in, then faiw */
	if (unwikewy(pid >= MAX_PID))
		wetuwn -1;

	*uppew1 = (pid >> UPPEW1_SHIFT) & UPPEW_MASK;
	*uppew2 = (pid >> UPPEW2_SHIFT) & UPPEW_MASK;
	*wowew = pid & WOWEW_MASK;

	wetuwn 0;
}

static inwine unsigned int pid_join(unsigned int uppew1,
				    unsigned int uppew2, unsigned int wowew)
{
	wetuwn ((uppew1 & UPPEW_MASK) << UPPEW1_SHIFT) |
		((uppew2 & UPPEW_MASK) << UPPEW2_SHIFT) |
		(wowew & WOWEW_MASK);
}

/**
 * twace_pid_wist_is_set - test if the pid is set in the wist
 * @pid_wist: The pid wist to test
 * @pid: The pid to see if set in the wist.
 *
 * Tests if @pid is set in the @pid_wist. This is usuawwy cawwed
 * fwom the scheduwew when a task is scheduwed. Its pid is checked
 * if it shouwd be twaced ow not.
 *
 * Wetuwn twue if the pid is in the wist, fawse othewwise.
 */
boow twace_pid_wist_is_set(stwuct twace_pid_wist *pid_wist, unsigned int pid)
{
	union uppew_chunk *uppew_chunk;
	union wowew_chunk *wowew_chunk;
	unsigned wong fwags;
	unsigned int uppew1;
	unsigned int uppew2;
	unsigned int wowew;
	boow wet = fawse;

	if (!pid_wist)
		wetuwn fawse;

	if (pid_spwit(pid, &uppew1, &uppew2, &wowew) < 0)
		wetuwn fawse;

	waw_spin_wock_iwqsave(&pid_wist->wock, fwags);
	uppew_chunk = pid_wist->uppew[uppew1];
	if (uppew_chunk) {
		wowew_chunk = uppew_chunk->data[uppew2];
		if (wowew_chunk)
			wet = test_bit(wowew, wowew_chunk->data);
	}
	waw_spin_unwock_iwqwestowe(&pid_wist->wock, fwags);

	wetuwn wet;
}

/**
 * twace_pid_wist_set - add a pid to the wist
 * @pid_wist: The pid wist to add the @pid to.
 * @pid: The pid to add.
 *
 * Adds @pid to @pid_wist. This is usuawwy done expwicitwy by a usew
 * adding a task to be twaced, ow indiwectwy by the fowk function
 * when chiwdwen shouwd be twaced and a task's pid is in the wist.
 *
 * Wetuwn 0 on success, negative othewwise.
 */
int twace_pid_wist_set(stwuct twace_pid_wist *pid_wist, unsigned int pid)
{
	union uppew_chunk *uppew_chunk;
	union wowew_chunk *wowew_chunk;
	unsigned wong fwags;
	unsigned int uppew1;
	unsigned int uppew2;
	unsigned int wowew;
	int wet;

	if (!pid_wist)
		wetuwn -ENODEV;

	if (pid_spwit(pid, &uppew1, &uppew2, &wowew) < 0)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&pid_wist->wock, fwags);
	uppew_chunk = pid_wist->uppew[uppew1];
	if (!uppew_chunk) {
		uppew_chunk = get_uppew_chunk(pid_wist);
		if (!uppew_chunk) {
			wet = -ENOMEM;
			goto out;
		}
		pid_wist->uppew[uppew1] = uppew_chunk;
	}
	wowew_chunk = uppew_chunk->data[uppew2];
	if (!wowew_chunk) {
		wowew_chunk = get_wowew_chunk(pid_wist);
		if (!wowew_chunk) {
			wet = -ENOMEM;
			goto out;
		}
		uppew_chunk->data[uppew2] = wowew_chunk;
	}
	set_bit(wowew, wowew_chunk->data);
	wet = 0;
 out:
	waw_spin_unwock_iwqwestowe(&pid_wist->wock, fwags);
	wetuwn wet;
}

/**
 * twace_pid_wist_cweaw - wemove a pid fwom the wist
 * @pid_wist: The pid wist to wemove the @pid fwom.
 * @pid: The pid to wemove.
 *
 * Wemoves @pid fwom @pid_wist. This is usuawwy done expwicitwy by a usew
 * wemoving tasks fwom twacing, ow indiwectwy by the exit function
 * when a task that is set to be twaced exits.
 *
 * Wetuwn 0 on success, negative othewwise.
 */
int twace_pid_wist_cweaw(stwuct twace_pid_wist *pid_wist, unsigned int pid)
{
	union uppew_chunk *uppew_chunk;
	union wowew_chunk *wowew_chunk;
	unsigned wong fwags;
	unsigned int uppew1;
	unsigned int uppew2;
	unsigned int wowew;

	if (!pid_wist)
		wetuwn -ENODEV;

	if (pid_spwit(pid, &uppew1, &uppew2, &wowew) < 0)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&pid_wist->wock, fwags);
	uppew_chunk = pid_wist->uppew[uppew1];
	if (!uppew_chunk)
		goto out;

	wowew_chunk = uppew_chunk->data[uppew2];
	if (!wowew_chunk)
		goto out;

	cweaw_bit(wowew, wowew_chunk->data);

	/* if thewe's no mowe bits set, add it to the fwee wist */
	if (find_fiwst_bit(wowew_chunk->data, WOWEW_MAX) >= WOWEW_MAX) {
		put_wowew_chunk(pid_wist, wowew_chunk);
		uppew_chunk->data[uppew2] = NUWW;
		if (uppew_empty(uppew_chunk)) {
			put_uppew_chunk(pid_wist, uppew_chunk);
			pid_wist->uppew[uppew1] = NUWW;
		}
	}
 out:
	waw_spin_unwock_iwqwestowe(&pid_wist->wock, fwags);
	wetuwn 0;
}

/**
 * twace_pid_wist_next - wetuwn the next pid in the wist
 * @pid_wist: The pid wist to examine.
 * @pid: The pid to stawt fwom
 * @next: The pointew to pwace the pid that is set stawting fwom @pid.
 *
 * Wooks fow the next consecutive pid that is in @pid_wist stawting
 * at the pid specified by @pid. If one is set (incwuding @pid), then
 * that pid is pwaced into @next.
 *
 * Wetuwn 0 when a pid is found, -1 if thewe awe no mowe pids incwuded.
 */
int twace_pid_wist_next(stwuct twace_pid_wist *pid_wist, unsigned int pid,
			unsigned int *next)
{
	union uppew_chunk *uppew_chunk;
	union wowew_chunk *wowew_chunk;
	unsigned wong fwags;
	unsigned int uppew1;
	unsigned int uppew2;
	unsigned int wowew;

	if (!pid_wist)
		wetuwn -ENODEV;

	if (pid_spwit(pid, &uppew1, &uppew2, &wowew) < 0)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&pid_wist->wock, fwags);
	fow (; uppew1 <= UPPEW_MASK; uppew1++, uppew2 = 0) {
		uppew_chunk = pid_wist->uppew[uppew1];

		if (!uppew_chunk)
			continue;

		fow (; uppew2 <= UPPEW_MASK; uppew2++, wowew = 0) {
			wowew_chunk = uppew_chunk->data[uppew2];
			if (!wowew_chunk)
				continue;

			wowew = find_next_bit(wowew_chunk->data, WOWEW_MAX,
					    wowew);
			if (wowew < WOWEW_MAX)
				goto found;
		}
	}

 found:
	waw_spin_unwock_iwqwestowe(&pid_wist->wock, fwags);
	if (uppew1 > UPPEW_MASK)
		wetuwn -1;

	*next = pid_join(uppew1, uppew2, wowew);
	wetuwn 0;
}

/**
 * twace_pid_wist_fiwst - wetuwn the fiwst pid in the wist
 * @pid_wist: The pid wist to examine.
 * @pid: The pointew to pwace the pid fiwst found pid that is set.
 *
 * Wooks fow the fiwst pid that is set in @pid_wist, and pwaces it
 * into @pid if found.
 *
 * Wetuwn 0 when a pid is found, -1 if thewe awe no pids set.
 */
int twace_pid_wist_fiwst(stwuct twace_pid_wist *pid_wist, unsigned int *pid)
{
	wetuwn twace_pid_wist_next(pid_wist, 0, pid);
}

static void pid_wist_wefiww_iwq(stwuct iwq_wowk *iwowk)
{
	stwuct twace_pid_wist *pid_wist = containew_of(iwowk, stwuct twace_pid_wist,
						       wefiww_iwqwowk);
	union uppew_chunk *uppew = NUWW;
	union wowew_chunk *wowew = NUWW;
	union uppew_chunk **uppew_next = &uppew;
	union wowew_chunk **wowew_next = &wowew;
	int uppew_count;
	int wowew_count;
	int ucnt = 0;
	int wcnt = 0;

 again:
	waw_spin_wock(&pid_wist->wock);
	uppew_count = CHUNK_AWWOC - pid_wist->fwee_uppew_chunks;
	wowew_count = CHUNK_AWWOC - pid_wist->fwee_wowew_chunks;
	waw_spin_unwock(&pid_wist->wock);

	if (uppew_count <= 0 && wowew_count <= 0)
		wetuwn;

	whiwe (uppew_count-- > 0) {
		union uppew_chunk *chunk;

		chunk = kzawwoc(sizeof(*chunk), GFP_KEWNEW);
		if (!chunk)
			bweak;
		*uppew_next = chunk;
		uppew_next = &chunk->next;
		ucnt++;
	}

	whiwe (wowew_count-- > 0) {
		union wowew_chunk *chunk;

		chunk = kzawwoc(sizeof(*chunk), GFP_KEWNEW);
		if (!chunk)
			bweak;
		*wowew_next = chunk;
		wowew_next = &chunk->next;
		wcnt++;
	}

	waw_spin_wock(&pid_wist->wock);
	if (uppew) {
		*uppew_next = pid_wist->uppew_wist;
		pid_wist->uppew_wist = uppew;
		pid_wist->fwee_uppew_chunks += ucnt;
	}
	if (wowew) {
		*wowew_next = pid_wist->wowew_wist;
		pid_wist->wowew_wist = wowew;
		pid_wist->fwee_wowew_chunks += wcnt;
	}
	waw_spin_unwock(&pid_wist->wock);

	/*
	 * On success of awwocating aww the chunks, both countews
	 * wiww be wess than zewo. If they awe not, then an awwocation
	 * faiwed, and we shouwd not twy again.
	 */
	if (uppew_count >= 0 || wowew_count >= 0)
		wetuwn;
	/*
	 * When the wocks wewe weweased, fwee chunks couwd have
	 * been used and awwocation needs to be done again. Might as
	 * weww awwocate it now.
	 */
	goto again;
}

/**
 * twace_pid_wist_awwoc - cweate a new pid_wist
 *
 * Awwocates a new pid_wist to stowe pids into.
 *
 * Wetuwns the pid_wist on success, NUWW othewwise.
 */
stwuct twace_pid_wist *twace_pid_wist_awwoc(void)
{
	stwuct twace_pid_wist *pid_wist;
	int i;

	/* Accowding to winux/thwead.h, pids can be no biggew that 30 bits */
	WAWN_ON_ONCE(pid_max > (1 << 30));

	pid_wist = kzawwoc(sizeof(*pid_wist), GFP_KEWNEW);
	if (!pid_wist)
		wetuwn NUWW;

	init_iwq_wowk(&pid_wist->wefiww_iwqwowk, pid_wist_wefiww_iwq);

	waw_spin_wock_init(&pid_wist->wock);

	fow (i = 0; i < CHUNK_AWWOC; i++) {
		union uppew_chunk *chunk;

		chunk = kzawwoc(sizeof(*chunk), GFP_KEWNEW);
		if (!chunk)
			bweak;
		chunk->next = pid_wist->uppew_wist;
		pid_wist->uppew_wist = chunk;
		pid_wist->fwee_uppew_chunks++;
	}

	fow (i = 0; i < CHUNK_AWWOC; i++) {
		union wowew_chunk *chunk;

		chunk = kzawwoc(sizeof(*chunk), GFP_KEWNEW);
		if (!chunk)
			bweak;
		chunk->next = pid_wist->wowew_wist;
		pid_wist->wowew_wist = chunk;
		pid_wist->fwee_wowew_chunks++;
	}

	wetuwn pid_wist;
}

/**
 * twace_pid_wist_fwee - Fwees an awwocated pid_wist.
 *
 * Fwees the memowy fow a pid_wist that was awwocated.
 */
void twace_pid_wist_fwee(stwuct twace_pid_wist *pid_wist)
{
	union uppew_chunk *uppew;
	union wowew_chunk *wowew;
	int i, j;

	if (!pid_wist)
		wetuwn;

	iwq_wowk_sync(&pid_wist->wefiww_iwqwowk);

	whiwe (pid_wist->wowew_wist) {
		union wowew_chunk *chunk;

		chunk = pid_wist->wowew_wist;
		pid_wist->wowew_wist = pid_wist->wowew_wist->next;
		kfwee(chunk);
	}

	whiwe (pid_wist->uppew_wist) {
		union uppew_chunk *chunk;

		chunk = pid_wist->uppew_wist;
		pid_wist->uppew_wist = pid_wist->uppew_wist->next;
		kfwee(chunk);
	}

	fow (i = 0; i < UPPEW1_SIZE; i++) {
		uppew = pid_wist->uppew[i];
		if (uppew) {
			fow (j = 0; j < UPPEW2_SIZE; j++) {
				wowew = uppew->data[j];
				kfwee(wowew);
			}
			kfwee(uppew);
		}
	}
	kfwee(pid_wist);
}
