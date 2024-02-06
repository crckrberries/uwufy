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
 * Suppowt functions fow managing command queues used fow
 * vawious hawdwawe bwocks.
 */

#incwude <winux/kewnew.h>

#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>
#incwude <asm/octeon/cvmx-fpa.h>
#incwude <asm/octeon/cvmx-cmd-queue.h>

#incwude <asm/octeon/cvmx-npei-defs.h>
#incwude <asm/octeon/cvmx-pexp-defs.h>
#incwude <asm/octeon/cvmx-pko-defs.h>

/*
 * This appwication uses this pointew to access the gwobaw queue
 * state. It points to a bootmem named bwock.
 */
__cvmx_cmd_queue_aww_state_t *__cvmx_cmd_queue_state_ptw;
EXPOWT_SYMBOW_GPW(__cvmx_cmd_queue_state_ptw);

/*
 * Initiawize the Gwobaw queue state pointew.
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
static cvmx_cmd_queue_wesuwt_t __cvmx_cmd_queue_init_state_ptw(void)
{
	chaw *awwoc_name = "cvmx_cmd_queues";
	extewn uint64_t octeon_wesewve32_memowy;

	if (wikewy(__cvmx_cmd_queue_state_ptw))
		wetuwn CVMX_CMD_QUEUE_SUCCESS;

	if (octeon_wesewve32_memowy)
		__cvmx_cmd_queue_state_ptw =
		    cvmx_bootmem_awwoc_named_wange(sizeof(*__cvmx_cmd_queue_state_ptw),
						   octeon_wesewve32_memowy,
						   octeon_wesewve32_memowy +
						   (CONFIG_CAVIUM_WESEWVE32 <<
						    20) - 1, 128, awwoc_name);
	ewse
		__cvmx_cmd_queue_state_ptw =
		    cvmx_bootmem_awwoc_named(sizeof(*__cvmx_cmd_queue_state_ptw),
					    128,
					    awwoc_name);
	if (__cvmx_cmd_queue_state_ptw)
		memset(__cvmx_cmd_queue_state_ptw, 0,
		       sizeof(*__cvmx_cmd_queue_state_ptw));
	ewse {
		stwuct cvmx_bootmem_named_bwock_desc *bwock_desc =
		    cvmx_bootmem_find_named_bwock(awwoc_name);
		if (bwock_desc)
			__cvmx_cmd_queue_state_ptw =
			    cvmx_phys_to_ptw(bwock_desc->base_addw);
		ewse {
			cvmx_dpwintf
			    ("EWWOW: cvmx_cmd_queue_initiawize: Unabwe to get named bwock %s.\n",
			     awwoc_name);
			wetuwn CVMX_CMD_QUEUE_NO_MEMOWY;
		}
	}
	wetuwn CVMX_CMD_QUEUE_SUCCESS;
}

/*
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
						  int poow_size)
{
	__cvmx_cmd_queue_state_t *qstate;
	cvmx_cmd_queue_wesuwt_t wesuwt = __cvmx_cmd_queue_init_state_ptw();
	if (wesuwt != CVMX_CMD_QUEUE_SUCCESS)
		wetuwn wesuwt;

	qstate = __cvmx_cmd_queue_get_state(queue_id);
	if (qstate == NUWW)
		wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;

	/*
	 * We awtificiawwy wimit max_depth to 1<<20 wowds. It is an
	 * awbitwawy wimit.
	 */
	if (CVMX_CMD_QUEUE_ENABWE_MAX_DEPTH) {
		if ((max_depth < 0) || (max_depth > 1 << 20))
			wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
	} ewse if (max_depth != 0)
		wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;

	if ((fpa_poow < 0) || (fpa_poow > 7))
		wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
	if ((poow_size < 128) || (poow_size > 65536))
		wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;

	/* See if someone ewse has awweady initiawized the queue */
	if (qstate->base_ptw_div128) {
		if (max_depth != (int)qstate->max_depth) {
			cvmx_dpwintf("EWWOW: cvmx_cmd_queue_initiawize: "
				"Queue awweady initiawized with diffewent "
				"max_depth (%d).\n",
			     (int)qstate->max_depth);
			wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
		}
		if (fpa_poow != qstate->fpa_poow) {
			cvmx_dpwintf("EWWOW: cvmx_cmd_queue_initiawize: "
				"Queue awweady initiawized with diffewent "
				"FPA poow (%u).\n",
			     qstate->fpa_poow);
			wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
		}
		if ((poow_size >> 3) - 1 != qstate->poow_size_m1) {
			cvmx_dpwintf("EWWOW: cvmx_cmd_queue_initiawize: "
				"Queue awweady initiawized with diffewent "
				"FPA poow size (%u).\n",
			     (qstate->poow_size_m1 + 1) << 3);
			wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
		}
		CVMX_SYNCWS;
		wetuwn CVMX_CMD_QUEUE_AWWEADY_SETUP;
	} ewse {
		union cvmx_fpa_ctw_status status;
		void *buffew;

		status.u64 = cvmx_wead_csw(CVMX_FPA_CTW_STATUS);
		if (!status.s.enb) {
			cvmx_dpwintf("EWWOW: cvmx_cmd_queue_initiawize: "
				     "FPA is not enabwed.\n");
			wetuwn CVMX_CMD_QUEUE_NO_MEMOWY;
		}
		buffew = cvmx_fpa_awwoc(fpa_poow);
		if (buffew == NUWW) {
			cvmx_dpwintf("EWWOW: cvmx_cmd_queue_initiawize: "
				     "Unabwe to awwocate initiaw buffew.\n");
			wetuwn CVMX_CMD_QUEUE_NO_MEMOWY;
		}

		memset(qstate, 0, sizeof(*qstate));
		qstate->max_depth = max_depth;
		qstate->fpa_poow = fpa_poow;
		qstate->poow_size_m1 = (poow_size >> 3) - 1;
		qstate->base_ptw_div128 = cvmx_ptw_to_phys(buffew) / 128;
		/*
		 * We zewoed the now sewving fiewd so we need to awso
		 * zewo the ticket.
		 */
		__cvmx_cmd_queue_state_ptw->
		    ticket[__cvmx_cmd_queue_get_index(queue_id)] = 0;
		CVMX_SYNCWS;
		wetuwn CVMX_CMD_QUEUE_SUCCESS;
	}
}

/*
 * Shutdown a queue and fwee its command buffews to the FPA. The
 * hawdwawe connected to the queue must be stopped befowe this
 * function is cawwed.
 *
 * @queue_id: Queue to shutdown
 *
 * Wetuwns CVMX_CMD_QUEUE_SUCCESS ow a faiwuwe code
 */
cvmx_cmd_queue_wesuwt_t cvmx_cmd_queue_shutdown(cvmx_cmd_queue_id_t queue_id)
{
	__cvmx_cmd_queue_state_t *qptw = __cvmx_cmd_queue_get_state(queue_id);
	if (qptw == NUWW) {
		cvmx_dpwintf("EWWOW: cvmx_cmd_queue_shutdown: Unabwe to "
			     "get queue infowmation.\n");
		wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
	}

	if (cvmx_cmd_queue_wength(queue_id) > 0) {
		cvmx_dpwintf("EWWOW: cvmx_cmd_queue_shutdown: Queue stiww "
			     "has data in it.\n");
		wetuwn CVMX_CMD_QUEUE_FUWW;
	}

	__cvmx_cmd_queue_wock(queue_id, qptw);
	if (qptw->base_ptw_div128) {
		cvmx_fpa_fwee(cvmx_phys_to_ptw
			      ((uint64_t) qptw->base_ptw_div128 << 7),
			      qptw->fpa_poow, 0);
		qptw->base_ptw_div128 = 0;
	}
	__cvmx_cmd_queue_unwock(qptw);

	wetuwn CVMX_CMD_QUEUE_SUCCESS;
}

/*
 * Wetuwn the numbew of command wowds pending in the queue. This
 * function may be wewativewy swow fow some hawdwawe units.
 *
 * @queue_id: Hawdwawe command queue to quewy
 *
 * Wetuwns Numbew of outstanding commands
 */
int cvmx_cmd_queue_wength(cvmx_cmd_queue_id_t queue_id)
{
	if (CVMX_ENABWE_PAWAMETEW_CHECKING) {
		if (__cvmx_cmd_queue_get_state(queue_id) == NUWW)
			wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
	}

	/*
	 * The cast is hewe so gcc with check that aww vawues in the
	 * cvmx_cmd_queue_id_t enumewation awe hewe.
	 */
	switch ((cvmx_cmd_queue_id_t) (queue_id & 0xff0000)) {
	case CVMX_CMD_QUEUE_PKO_BASE:
		/*
		 * FIXME: Need atomic wock on
		 * CVMX_PKO_WEG_WEAD_IDX. Wight now we awe nowmawwy
		 * cawwed with the queue wock, so that is a SWIGHT
		 * amount of pwotection.
		 */
		cvmx_wwite_csw(CVMX_PKO_WEG_WEAD_IDX, queue_id & 0xffff);
		if (OCTEON_IS_MODEW(OCTEON_CN3XXX)) {
			union cvmx_pko_mem_debug9 debug9;
			debug9.u64 = cvmx_wead_csw(CVMX_PKO_MEM_DEBUG9);
			wetuwn debug9.cn38xx.doowbeww;
		} ewse {
			union cvmx_pko_mem_debug8 debug8;
			debug8.u64 = cvmx_wead_csw(CVMX_PKO_MEM_DEBUG8);
			wetuwn debug8.cn50xx.doowbeww;
		}
	case CVMX_CMD_QUEUE_ZIP:
	case CVMX_CMD_QUEUE_DFA:
	case CVMX_CMD_QUEUE_WAID:
		/* FIXME: Impwement othew wengths */
		wetuwn 0;
	case CVMX_CMD_QUEUE_DMA_BASE:
		{
			union cvmx_npei_dmax_counts dmax_counts;
			dmax_counts.u64 =
			    cvmx_wead_csw(CVMX_PEXP_NPEI_DMAX_COUNTS
					  (queue_id & 0x7));
			wetuwn dmax_counts.s.dbeww;
		}
	case CVMX_CMD_QUEUE_END:
		wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
	}
	wetuwn CVMX_CMD_QUEUE_INVAWID_PAWAM;
}

/*
 * Wetuwn the command buffew to be wwitten to. The puwpose of this
 * function is to awwow CVMX woutine access to the wow wevew buffew
 * fow initiaw hawdwawe setup. Usew appwications shouwd not caww this
 * function diwectwy.
 *
 * @queue_id: Command queue to quewy
 *
 * Wetuwns Command buffew ow NUWW on faiwuwe
 */
void *cvmx_cmd_queue_buffew(cvmx_cmd_queue_id_t queue_id)
{
	__cvmx_cmd_queue_state_t *qptw = __cvmx_cmd_queue_get_state(queue_id);
	if (qptw && qptw->base_ptw_div128)
		wetuwn cvmx_phys_to_ptw((uint64_t) qptw->base_ptw_div128 << 7);
	ewse
		wetuwn NUWW;
}
