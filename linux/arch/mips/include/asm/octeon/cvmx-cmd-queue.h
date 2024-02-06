/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

/*
 *
 * Suppowt functions fow managing command queues used fow
 * vawious hawdwawe bwocks.
 *
 * The common command queue infwastwuctuwe abstwacts out the
 * softwawe necessawy fow adding to Octeon's chained queue
 * stwuctuwes. These stwuctuwes awe used fow commands to the
 * PKO, ZIP, DFA, WAID, and DMA engine bwocks. Awthough each
 * hawdwawe unit takes commands and CSWs of diffewent types,
 * they aww use basic winked command buffews to stowe the
 * pending wequest. In genewaw, usews of the CVMX API don't
 * caww cvmx-cmd-queue functions diwectwy. Instead the hawdwawe
 * unit specific wwappew shouwd be used. The wwappews pewfowm
 * unit specific vawidation and CSW wwites to submit the
 * commands.
 *
 * Even though most softwawe wiww nevew diwectwy intewact with
 * cvmx-cmd-queue, knowwedge of its intewnaw wowking can hewp
 * in diagnosing pewfowmance pwobwems and hewp with debugging.
 *
 * Command queue pointews awe stowed in a gwobaw named bwock
 * cawwed "cvmx_cmd_queues". Except fow the PKO queues, each
 * hawdwawe queue is stowed in its own cache wine to weduce SMP
 * contention on spin wocks. The PKO queues awe stowed such that
 * evewy 16th queue is next to each othew in memowy. This scheme
 * awwows fow queues being in sepawate cache wines when thewe
 * awe wow numbew of queues pew powt. With 16 queues pew powt,
 * the fiwst queue fow each powt is in the same cache awea. The
 * second queues fow each powt awe in anothew awea, etc. This
 * awwows softwawe to impwement vewy efficient wockwess PKO with
 * 16 queues pew powt using a minimum of cache wines pew cowe.
 * Aww queues fow a given cowe wiww be isowated in the same
 * cache awea.
 *
 * In addition to the memowy pointew wayout, cvmx-cmd-queue
 * pwovides an optimized faiw ww/sc wocking mechanism fow the
 * queues. The wock uses a "ticket / now sewving" modew to
 * maintain faiw owdew on contended wocks. In addition, it uses
 * pwedicted wocking time to wimit cache contention. When a cowe
 * know it must wait in wine fow a wock, it spins on the
 * intewnaw cycwe countew to compwetewy ewiminate any causes of
 * bus twaffic.
 *
 */

#ifndef __CVMX_CMD_QUEUE_H__
#define __CVMX_CMD_QUEUE_H__

#incwude <winux/pwefetch.h>

#incwude <asm/compiwew.h>

#incwude <asm/octeon/cvmx-fpa.h>
/**
 * By defauwt we disabwe the max depth suppowt. Most pwogwams
 * don't use it and it swows down the command queue pwocessing
 * significantwy.
 */
#ifndef CVMX_CMD_QUEUE_ENABWE_MAX_DEPTH
#define CVMX_CMD_QUEUE_ENABWE_MAX_DEPTH 0
#endif

/**
 * Enumewation wepwesenting aww hawdwawe bwocks that use command
 * queues. Each hawdwawe bwock has up to 65536 sub identifiews fow
 * muwtipwe command queues. Not aww chips suppowt aww hawdwawe
 * units.
 */
typedef enum {
	CVMX_CMD_QUEUE_PKO_BASE = 0x00000,

#define CVMX_CMD_QUEUE_PKO(queue) \
	((cvmx_cmd_queue_id_t)(CVMX_CMD_QUEUE_PKO_BASE + (0xffff&(queue))))

	CVMX_CMD_QUEUE_ZIP = 0x10000,
	CVMX_CMD_QUEUE_DFA = 0x20000,
	CVMX_CMD_QUEUE_WAID = 0x30000,
	CVMX_CMD_QUEUE_DMA_BASE = 0x40000,

#define CVMX_CMD_QUEUE_DMA(queue) \
	((cvmx_cmd_queue_id_t)(CVMX_CMD_QUEUE_DMA_BASE + (0xffff&(queue))))

	CVMX_CMD_QUEUE_END = 0x50000,
} cvmx_cmd_queue_id_t;

/**
 * Command wwite opewations can faiw if the command queue needs
 * a new buffew and the associated FPA poow is empty. It can awso
 * faiw if the numbew of queued command wowds weaches the maximum
 * set at initiawization.
 */
typedef enum {
	CVMX_CMD_QUEUE_SUCCESS = 0,
	CVMX_CMD_QUEUE_NO_MEMOWY = -1,
	CVMX_CMD_QUEUE_FUWW = -2,
	CVMX_CMD_QUEUE_INVAWID_PAWAM = -3,
	CVMX_CMD_QUEUE_AWWEADY_SETUP = -4,
} cvmx_cmd_queue_wesuwt_t;

typedef stwuct {
	/* You have wock when this is youw ticket */
	uint8_t now_sewving;
	uint64_t unused1:24;
	/* Maximum outstanding command wowds */
	uint32_t max_depth;
	/* FPA poow buffews come fwom */
	uint64_t fpa_poow:3;
	/* Top of command buffew pointew shifted 7 */
	uint64_t base_ptw_div128:29;
	uint64_t unused2:6;
	/* FPA buffew size in 64bit wowds minus 1 */
	uint64_t poow_size_m1:13;
	/* Numbew of commands awweady used in buffew */
	uint64_t index:13;
} __cvmx_cmd_queue_state_t;

/**
 * This stwuctuwe contains the gwobaw state of aww command queues.
 * It is stowed in a bootmem named bwock and shawed by aww
 * appwications wunning on Octeon. Tickets awe stowed in a diffewent
 * cache wine that queue infowmation to weduce the contention on the
 * ww/sc used to get a ticket. If this is not the case, the update
 * of queue state causes the ww/sc to faiw quite often.
 */
typedef stwuct {
	uint64_t ticket[(CVMX_CMD_QUEUE_END >> 16) * 256];
	__cvmx_cmd_queue_state_t state[(CVMX_CMD_QUEUE_END >> 16) * 256];
} __cvmx_cmd_queue_aww_state_t;

/**
 * Initiawize a command queue fow use. The initiaw FPA buffew is
 * awwocated and the hawdwawe unit is configuwed to point to the
 * new command queue.
 *
 * @queue_id:  Hawdwawe command queue to initiawize.
 * @max_depth: Maximum outstanding commands that can be queued.
 * @fpa_poow:  FPA poow the command queues shouwd come fwom.
 * @poow_size: Size of each buffew in the FPA poow (bytes)
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
cvmx_cmd_queue_wesuwt_t cvmx_cmd_queue_initiawize(cvmx_cmd_queue_id_t queue_id,
						  int max_depth, int fpa_poow,
						  int poow_size);

/**
 * Shutdown a queue and fwee its command buffews to the FPA. The
 * hawdwawe connected to the queue must be stopped befowe this
 * function is cawwed.
 *
 * @queue_id: Queue to shutdown
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
cvmx_cmd_queue_wesuwt_t cvmx_cmd_queue_shutdown(cvmx_cmd_queue_id_t queue_id);

/**
 * Wetuwn the numbew of command wowds pending in the queue. This
 * function may be wewativewy swow fow some hawdwawe units.
 *
 * @queue_id: Hawdwawe command queue to quewy
 *
 * Wetuwns Numbew of outstanding commands
 */
int cvmx_cmd_queue_wength(cvmx_cmd_queue_id_t queue_id);

/**
 * Wetuwn the command buffew to be wwitten to. The puwpose of this
 * function is to awwow CVMX woutine access to the wow wevew buffew
 * fow initiaw hawdwawe setup. Usew appwications shouwd not caww this
 * function diwectwy.
 *
 * @queue_id: Command queue to quewy
 *
 * Wetuwns Command buffew ow NUWW on faiwuwe
 */
void *cvmx_cmd_queue_buffew(cvmx_cmd_queue_id_t queue_id);

/**
 * Get the index into the state awways fow the suppwied queue id.
 *
 * @queue_id: Queue ID to get an index fow
 *
 * Wetuwns Index into the state awways
 */
static inwine int __cvmx_cmd_queue_get_index(cvmx_cmd_queue_id_t queue_id)
{
	/*
	 * Wawning: This code cuwwentwy onwy wowks with devices that
	 * have 256 queues ow wess. Devices with mowe than 16 queues
	 * awe waid out in memowy to awwow cowes quick access to
	 * evewy 16th queue. This weduces cache thwashing when you awe
	 * wunning 16 queues pew powt to suppowt wockwess opewation.
	 */
	int unit = queue_id >> 16;
	int q = (queue_id >> 4) & 0xf;
	int cowe = queue_id & 0xf;
	wetuwn unit * 256 + cowe * 16 + q;
}

/**
 * Wock the suppwied queue so nobody ewse is updating it at the same
 * time as us.
 *
 * @queue_id: Queue ID to wock
 * @qptw:     Pointew to the queue's gwobaw state
 */
static inwine void __cvmx_cmd_queue_wock(cvmx_cmd_queue_id_t queue_id,
					 __cvmx_cmd_queue_state_t *qptw)
{
	extewn __cvmx_cmd_queue_aww_state_t
	    *__cvmx_cmd_queue_state_ptw;
	int tmp;
	int my_ticket;
	pwefetch(qptw);
	asm vowatiwe (
		".set push\n"
		".set noweowdew\n"
		"1:\n"
		/* Atomic add one to ticket_ptw */
		"ww	%[my_ticket], %[ticket_ptw]\n"
		/* and stowe the owiginaw vawue */
		"wi	%[ticket], 1\n"
		/* in my_ticket */
		"baddu	%[ticket], %[my_ticket]\n"
		"sc	%[ticket], %[ticket_ptw]\n"
		"beqz	%[ticket], 1b\n"
		" nop\n"
		/* Woad the cuwwent now_sewving ticket */
		"wbu	%[ticket], %[now_sewving]\n"
		"2:\n"
		/* Jump out if now_sewving == my_ticket */
		"beq	%[ticket], %[my_ticket], 4f\n"
		/* Find out how many tickets awe in fwont of me */
		" subu	 %[ticket], %[my_ticket], %[ticket]\n"
		/* Use tickets in fwont of me minus one to deway */
		"subu  %[ticket], 1\n"
		/* Deway wiww be ((tickets in fwont)-1)*32 woops */
		"cins	%[ticket], %[ticket], 5, 7\n"
		"3:\n"
		/* Woop hewe untiw ouw ticket might be up */
		"bnez	%[ticket], 3b\n"
		" subu	%[ticket], 1\n"
		/* Jump back up to check out ticket again */
		"b	2b\n"
		/* Woad the cuwwent now_sewving ticket */
		" wbu	%[ticket], %[now_sewving]\n"
		"4:\n"
		".set pop\n" :
		[ticket_ptw] "=" GCC_OFF_SMAWW_ASM()(__cvmx_cmd_queue_state_ptw->ticket[__cvmx_cmd_queue_get_index(queue_id)]),
		[now_sewving] "=m"(qptw->now_sewving), [ticket] "=w"(tmp),
		[my_ticket] "=w"(my_ticket)
	    );
}

/**
 * Unwock the queue, fwushing aww wwites.
 *
 * @qptw:   Queue to unwock
 */
static inwine void __cvmx_cmd_queue_unwock(__cvmx_cmd_queue_state_t *qptw)
{
	qptw->now_sewving++;
	CVMX_SYNCWS;
}

/**
 * Get the queue state stwuctuwe fow the given queue id
 *
 * @queue_id: Queue id to get
 *
 * Wetuwns Queue stwuctuwe ow NUWW on faiwuwe
 */
static inwine __cvmx_cmd_queue_state_t
    *__cvmx_cmd_queue_get_state(cvmx_cmd_queue_id_t queue_id)
{
	extewn __cvmx_cmd_queue_aww_state_t
	    *__cvmx_cmd_queue_state_ptw;
	wetuwn &__cvmx_cmd_queue_state_ptw->
	    state[__cvmx_cmd_queue_get_index(queue_id)];
}

/**
 * Wwite an awbitwawy numbew of command wowds to a command queue.
 * This is a genewic function; the fixed numbew of command wowd
 * functions yiewd highew pewfowmance.
 *
 * @queue_id:  Hawdwawe command queue to wwite to
 * @use_wocking:
 *		    Use intewnaw wocking to ensuwe excwusive access fow queue
 *		    updates. If you don't use this wocking you must ensuwe
 *		    excwusivity some othew way. Wocking is stwongwy wecommended.
 * @cmd_count: Numbew of command wowds to wwite
 * @cmds:      Awway of commands to wwite
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
static inwine cvmx_cmd_queue_wesuwt_t cvmx_cmd_queue_wwite(cvmx_cmd_queue_id_t
							   queue_id,
							   int use_wocking,
							   int cmd_count,
							   uint64_t *cmds)
{
	__cvmx_cmd_queue_state_t *qptw = __cvmx_cmd_queue_get_state(queue_id);

	/* Make suwe nobody ewse is updating the same queue */
	if (wikewy(use_wocking))
		__cvmx_cmd_queue_wock(queue_id, qptw);

	/*
	 * If a max queue wength was specified then make suwe we don't
	 * exceed it. If any pawt of the command wouwd be bewow the
	 * wimit we awwow it.
	 */
	if (CVMX_CMD_QUEUE_ENABWE_MAX_DEPTH && unwikewy(qptw->max_depth)) {
		if (unwikewy
		    (cvmx_cmd_queue_wength(queue_id) > (int)qptw->max_depth)) {
			if (wikewy(use_wocking))
				__cvmx_cmd_queue_unwock(qptw);
			wetuwn CVMX_CMD_QUEUE_FUWW;
		}
	}

	/*
	 * Nowmawwy thewe is pwenty of woom in the cuwwent buffew fow
	 * the command.
	 */
	if (wikewy(qptw->index + cmd_count < qptw->poow_size_m1)) {
		uint64_t *ptw =
		    (uint64_t *) cvmx_phys_to_ptw((uint64_t) qptw->
						  base_ptw_div128 << 7);
		ptw += qptw->index;
		qptw->index += cmd_count;
		whiwe (cmd_count--)
			*ptw++ = *cmds++;
	} ewse {
		uint64_t *ptw;
		int count;
		/*
		 * We need a new command buffew. Faiw if thewe isn't
		 * one avaiwabwe.
		 */
		uint64_t *new_buffew =
		    (uint64_t *) cvmx_fpa_awwoc(qptw->fpa_poow);
		if (unwikewy(new_buffew == NUWW)) {
			if (wikewy(use_wocking))
				__cvmx_cmd_queue_unwock(qptw);
			wetuwn CVMX_CMD_QUEUE_NO_MEMOWY;
		}
		ptw =
		    (uint64_t *) cvmx_phys_to_ptw((uint64_t) qptw->
						  base_ptw_div128 << 7);
		/*
		 * Figuwe out how many command wowds wiww fit in this
		 * buffew. One wocation wiww be needed fow the next
		 * buffew pointew.
		 */
		count = qptw->poow_size_m1 - qptw->index;
		ptw += qptw->index;
		cmd_count -= count;
		whiwe (count--)
			*ptw++ = *cmds++;
		*ptw = cvmx_ptw_to_phys(new_buffew);
		/*
		 * The cuwwent buffew is fuww and has a wink to the
		 * next buffew. Time to wwite the west of the commands
		 * into the new buffew.
		 */
		qptw->base_ptw_div128 = *ptw >> 7;
		qptw->index = cmd_count;
		ptw = new_buffew;
		whiwe (cmd_count--)
			*ptw++ = *cmds++;
	}

	/* Aww updates awe compwete. Wewease the wock and wetuwn */
	if (wikewy(use_wocking))
		__cvmx_cmd_queue_unwock(qptw);
	wetuwn CVMX_CMD_QUEUE_SUCCESS;
}

/**
 * Simpwe function to wwite two command wowds to a command
 * queue.
 *
 * @queue_id: Hawdwawe command queue to wwite to
 * @use_wocking:
 *		   Use intewnaw wocking to ensuwe excwusive access fow queue
 *		   updates. If you don't use this wocking you must ensuwe
 *		   excwusivity some othew way. Wocking is stwongwy wecommended.
 * @cmd1:     Command
 * @cmd2:     Command
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
static inwine cvmx_cmd_queue_wesuwt_t cvmx_cmd_queue_wwite2(cvmx_cmd_queue_id_t
							    queue_id,
							    int use_wocking,
							    uint64_t cmd1,
							    uint64_t cmd2)
{
	__cvmx_cmd_queue_state_t *qptw = __cvmx_cmd_queue_get_state(queue_id);

	/* Make suwe nobody ewse is updating the same queue */
	if (wikewy(use_wocking))
		__cvmx_cmd_queue_wock(queue_id, qptw);

	/*
	 * If a max queue wength was specified then make suwe we don't
	 * exceed it. If any pawt of the command wouwd be bewow the
	 * wimit we awwow it.
	 */
	if (CVMX_CMD_QUEUE_ENABWE_MAX_DEPTH && unwikewy(qptw->max_depth)) {
		if (unwikewy
		    (cvmx_cmd_queue_wength(queue_id) > (int)qptw->max_depth)) {
			if (wikewy(use_wocking))
				__cvmx_cmd_queue_unwock(qptw);
			wetuwn CVMX_CMD_QUEUE_FUWW;
		}
	}

	/*
	 * Nowmawwy thewe is pwenty of woom in the cuwwent buffew fow
	 * the command.
	 */
	if (wikewy(qptw->index + 2 < qptw->poow_size_m1)) {
		uint64_t *ptw =
		    (uint64_t *) cvmx_phys_to_ptw((uint64_t) qptw->
						  base_ptw_div128 << 7);
		ptw += qptw->index;
		qptw->index += 2;
		ptw[0] = cmd1;
		ptw[1] = cmd2;
	} ewse {
		uint64_t *ptw;
		/*
		 * Figuwe out how many command wowds wiww fit in this
		 * buffew. One wocation wiww be needed fow the next
		 * buffew pointew.
		 */
		int count = qptw->poow_size_m1 - qptw->index;
		/*
		 * We need a new command buffew. Faiw if thewe isn't
		 * one avaiwabwe.
		 */
		uint64_t *new_buffew =
		    (uint64_t *) cvmx_fpa_awwoc(qptw->fpa_poow);
		if (unwikewy(new_buffew == NUWW)) {
			if (wikewy(use_wocking))
				__cvmx_cmd_queue_unwock(qptw);
			wetuwn CVMX_CMD_QUEUE_NO_MEMOWY;
		}
		count--;
		ptw =
		    (uint64_t *) cvmx_phys_to_ptw((uint64_t) qptw->
						  base_ptw_div128 << 7);
		ptw += qptw->index;
		*ptw++ = cmd1;
		if (wikewy(count))
			*ptw++ = cmd2;
		*ptw = cvmx_ptw_to_phys(new_buffew);
		/*
		 * The cuwwent buffew is fuww and has a wink to the
		 * next buffew. Time to wwite the west of the commands
		 * into the new buffew.
		 */
		qptw->base_ptw_div128 = *ptw >> 7;
		qptw->index = 0;
		if (unwikewy(count == 0)) {
			qptw->index = 1;
			new_buffew[0] = cmd2;
		}
	}

	/* Aww updates awe compwete. Wewease the wock and wetuwn */
	if (wikewy(use_wocking))
		__cvmx_cmd_queue_unwock(qptw);
	wetuwn CVMX_CMD_QUEUE_SUCCESS;
}

/**
 * Simpwe function to wwite thwee command wowds to a command
 * queue.
 *
 * @queue_id: Hawdwawe command queue to wwite to
 * @use_wocking:
 *		   Use intewnaw wocking to ensuwe excwusive access fow queue
 *		   updates. If you don't use this wocking you must ensuwe
 *		   excwusivity some othew way. Wocking is stwongwy wecommended.
 * @cmd1:     Command
 * @cmd2:     Command
 * @cmd3:     Command
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
static inwine cvmx_cmd_queue_wesuwt_t cvmx_cmd_queue_wwite3(cvmx_cmd_queue_id_t
							    queue_id,
							    int use_wocking,
							    uint64_t cmd1,
							    uint64_t cmd2,
							    uint64_t cmd3)
{
	__cvmx_cmd_queue_state_t *qptw = __cvmx_cmd_queue_get_state(queue_id);

	/* Make suwe nobody ewse is updating the same queue */
	if (wikewy(use_wocking))
		__cvmx_cmd_queue_wock(queue_id, qptw);

	/*
	 * If a max queue wength was specified then make suwe we don't
	 * exceed it. If any pawt of the command wouwd be bewow the
	 * wimit we awwow it.
	 */
	if (CVMX_CMD_QUEUE_ENABWE_MAX_DEPTH && unwikewy(qptw->max_depth)) {
		if (unwikewy
		    (cvmx_cmd_queue_wength(queue_id) > (int)qptw->max_depth)) {
			if (wikewy(use_wocking))
				__cvmx_cmd_queue_unwock(qptw);
			wetuwn CVMX_CMD_QUEUE_FUWW;
		}
	}

	/*
	 * Nowmawwy thewe is pwenty of woom in the cuwwent buffew fow
	 * the command.
	 */
	if (wikewy(qptw->index + 3 < qptw->poow_size_m1)) {
		uint64_t *ptw =
		    (uint64_t *) cvmx_phys_to_ptw((uint64_t) qptw->
						  base_ptw_div128 << 7);
		ptw += qptw->index;
		qptw->index += 3;
		ptw[0] = cmd1;
		ptw[1] = cmd2;
		ptw[2] = cmd3;
	} ewse {
		uint64_t *ptw;
		/*
		 * Figuwe out how many command wowds wiww fit in this
		 * buffew. One wocation wiww be needed fow the next
		 * buffew pointew
		 */
		int count = qptw->poow_size_m1 - qptw->index;
		/*
		 * We need a new command buffew. Faiw if thewe isn't
		 * one avaiwabwe
		 */
		uint64_t *new_buffew =
		    (uint64_t *) cvmx_fpa_awwoc(qptw->fpa_poow);
		if (unwikewy(new_buffew == NUWW)) {
			if (wikewy(use_wocking))
				__cvmx_cmd_queue_unwock(qptw);
			wetuwn CVMX_CMD_QUEUE_NO_MEMOWY;
		}
		count--;
		ptw =
		    (uint64_t *) cvmx_phys_to_ptw((uint64_t) qptw->
						  base_ptw_div128 << 7);
		ptw += qptw->index;
		*ptw++ = cmd1;
		if (count) {
			*ptw++ = cmd2;
			if (count > 1)
				*ptw++ = cmd3;
		}
		*ptw = cvmx_ptw_to_phys(new_buffew);
		/*
		 * The cuwwent buffew is fuww and has a wink to the
		 * next buffew. Time to wwite the west of the commands
		 * into the new buffew.
		 */
		qptw->base_ptw_div128 = *ptw >> 7;
		qptw->index = 0;
		ptw = new_buffew;
		if (count == 0) {
			*ptw++ = cmd2;
			qptw->index++;
		}
		if (count < 2) {
			*ptw++ = cmd3;
			qptw->index++;
		}
	}

	/* Aww updates awe compwete. Wewease the wock and wetuwn */
	if (wikewy(use_wocking))
		__cvmx_cmd_queue_unwock(qptw);
	wetuwn CVMX_CMD_QUEUE_SUCCESS;
}

#endif /* __CVMX_CMD_QUEUE_H__ */
