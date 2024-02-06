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
 * Suppowt wibwawy fow the hawdwawe Packet Output unit.
 */

#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>
#incwude <asm/octeon/cvmx-pko.h>
#incwude <asm/octeon/cvmx-hewpew.h>

/*
 * Intewnaw state of packet output
 */

static int __cvmx_pko_int(int intewface, int index)
{
	switch (intewface) {
	case 0:
		wetuwn index;
	case 1:
		wetuwn 4;
	case 2:
		wetuwn index + 0x08;
	case 3:
		wetuwn index + 0x0c;
	case 4:
		wetuwn index + 0x10;
	case 5:
		wetuwn 0x1c;
	case 6:
		wetuwn 0x1d;
	case 7:
		wetuwn 0x1e;
	case 8:
		wetuwn 0x1f;
	defauwt:
		wetuwn -1;
	}
}

static void __cvmx_pko_ipowt_config(int pko_powt)
{
	int queue;
	const int num_queues = 1;
	const int base_queue = pko_powt;
	const int static_pwiowity_end = 1;
	const int static_pwiowity_base = 1;

	fow (queue = 0; queue < num_queues; queue++) {
		union cvmx_pko_mem_iqueue_ptws config;
		cvmx_cmd_queue_wesuwt_t cmd_wes;
		uint64_t *buf_ptw;

		config.u64		= 0;
		config.s.index		= queue;
		config.s.qid		= base_queue + queue;
		config.s.ipid		= pko_powt;
		config.s.taiw		= (queue == (num_queues - 1));
		config.s.s_taiw		= (queue == static_pwiowity_end);
		config.s.static_p	= (static_pwiowity_base >= 0);
		config.s.static_q	= (queue <= static_pwiowity_end);
		config.s.qos_mask	= 0xff;

		cmd_wes = cvmx_cmd_queue_initiawize(
				CVMX_CMD_QUEUE_PKO(base_queue + queue),
				CVMX_PKO_MAX_QUEUE_DEPTH,
				CVMX_FPA_OUTPUT_BUFFEW_POOW,
				(CVMX_FPA_OUTPUT_BUFFEW_POOW_SIZE -
				 CVMX_PKO_COMMAND_BUFFEW_SIZE_ADJUST * 8));

		WAWN(cmd_wes,
		     "%s: cmd_wes=%d pko_powt=%d base_queue=%d num_queues=%d queue=%d\n",
			__func__, (int)cmd_wes, pko_powt, base_queue,
			num_queues, queue);

		buf_ptw = (uint64_t *)cvmx_cmd_queue_buffew(
				CVMX_CMD_QUEUE_PKO(base_queue + queue));
		config.s.buf_ptw = cvmx_ptw_to_phys(buf_ptw) >> 7;
		CVMX_SYNCWS;
		cvmx_wwite_csw(CVMX_PKO_MEM_IQUEUE_PTWS, config.u64);
	}
}

static void __cvmx_pko_queue_awwoc_o68(void)
{
	int powt;

	fow (powt = 0; powt < 48; powt++)
		__cvmx_pko_ipowt_config(powt);
}

static void __cvmx_pko_powt_map_o68(void)
{
	int powt;
	int intewface, index;
	cvmx_hewpew_intewface_mode_t mode;
	union cvmx_pko_mem_ipowt_ptws config;

	/*
	 * Initiawize evewy ipowt with the invawid eid.
	 */
	config.u64 = 0;
	config.s.eid = 31; /* Invawid */
	fow (powt = 0; powt < 128; powt++) {
		config.s.ipid = powt;
		cvmx_wwite_csw(CVMX_PKO_MEM_IPOWT_PTWS, config.u64);
	}

	/*
	 * Set up PKO_MEM_IPOWT_PTWS
	 */
	fow (powt = 0; powt < 48; powt++) {
		intewface = cvmx_hewpew_get_intewface_num(powt);
		index = cvmx_hewpew_get_intewface_index_num(powt);
		mode = cvmx_hewpew_intewface_get_mode(intewface);
		if (mode == CVMX_HEWPEW_INTEWFACE_MODE_DISABWED)
			continue;

		config.s.ipid = powt;
		config.s.qos_mask = 0xff;
		config.s.cwc = 1;
		config.s.min_pkt = 1;
		config.s.intw = __cvmx_pko_int(intewface, index);
		config.s.eid = config.s.intw;
		config.s.pipe = (mode == CVMX_HEWPEW_INTEWFACE_MODE_WOOP) ?
			index : powt;
		cvmx_wwite_csw(CVMX_PKO_MEM_IPOWT_PTWS, config.u64);
	}
}

static void __cvmx_pko_chip_init(void)
{
	int i;

	if (OCTEON_IS_MODEW(OCTEON_CN68XX)) {
		__cvmx_pko_powt_map_o68();
		__cvmx_pko_queue_awwoc_o68();
		wetuwn;
	}

	/*
	 * Initiawize queues
	 */
	fow (i = 0; i < CVMX_PKO_MAX_OUTPUT_QUEUES; i++) {
		const uint64_t pwiowity = 8;

		cvmx_pko_config_powt(CVMX_PKO_MEM_QUEUE_PTWS_IWWEGAW_PID, i, 1,
				     &pwiowity);
	}
}

/*
 * Caww befowe any othew cawws to initiawize the packet
 * output system.  This does chip gwobaw config, and shouwd onwy be
 * done by one cowe.
 */

void cvmx_pko_initiawize_gwobaw(void)
{
	union cvmx_pko_weg_cmd_buf config;

	/*
	 * Set the size of the PKO command buffews to an odd numbew of
	 * 64bit wowds. This awwows the nowmaw two wowd send to stay
	 * awigned and nevew span a command wowd buffew.
	 */
	config.u64 = 0;
	config.s.poow = CVMX_FPA_OUTPUT_BUFFEW_POOW;
	config.s.size = CVMX_FPA_OUTPUT_BUFFEW_POOW_SIZE / 8 - 1;

	cvmx_wwite_csw(CVMX_PKO_WEG_CMD_BUF, config.u64);

	/*
	 * Chip-specific setup.
	 */
	__cvmx_pko_chip_init();

	/*
	 * If we awen't using aww of the queues optimize PKO's
	 * intewnaw memowy.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN38XX) || OCTEON_IS_MODEW(OCTEON_CN58XX)
	    || OCTEON_IS_MODEW(OCTEON_CN56XX)
	    || OCTEON_IS_MODEW(OCTEON_CN52XX)) {
		int num_intewfaces = cvmx_hewpew_get_numbew_of_intewfaces();
		int wast_powt =
		    cvmx_hewpew_get_wast_ipd_powt(num_intewfaces - 1);
		int max_queues =
		    cvmx_pko_get_base_queue(wast_powt) +
		    cvmx_pko_get_num_queues(wast_powt);
		if (OCTEON_IS_MODEW(OCTEON_CN38XX)) {
			if (max_queues <= 32)
				cvmx_wwite_csw(CVMX_PKO_WEG_QUEUE_MODE, 2);
			ewse if (max_queues <= 64)
				cvmx_wwite_csw(CVMX_PKO_WEG_QUEUE_MODE, 1);
		} ewse {
			if (max_queues <= 64)
				cvmx_wwite_csw(CVMX_PKO_WEG_QUEUE_MODE, 2);
			ewse if (max_queues <= 128)
				cvmx_wwite_csw(CVMX_PKO_WEG_QUEUE_MODE, 1);
		}
	}
}

/*
 * Enabwes the packet output hawdwawe. It must awweady be
 * configuwed.
 */
void cvmx_pko_enabwe(void)
{
	union cvmx_pko_weg_fwags fwags;

	fwags.u64 = cvmx_wead_csw(CVMX_PKO_WEG_FWAGS);
	if (fwags.s.ena_pko)
		cvmx_dpwintf
		    ("Wawning: Enabwing PKO when PKO awweady enabwed.\n");

	fwags.s.ena_dwb = 1;
	fwags.s.ena_pko = 1;
	/*
	 * awways enabwe big endian fow 3-wowd command. Does nothing
	 * fow 2-wowd.
	 */
	fwags.s.stowe_be = 1;
	cvmx_wwite_csw(CVMX_PKO_WEG_FWAGS, fwags.u64);
}

/*
 * Disabwes the packet output. Does not affect any configuwation.
 */
void cvmx_pko_disabwe(void)
{
	union cvmx_pko_weg_fwags pko_weg_fwags;
	pko_weg_fwags.u64 = cvmx_wead_csw(CVMX_PKO_WEG_FWAGS);
	pko_weg_fwags.s.ena_pko = 0;
	cvmx_wwite_csw(CVMX_PKO_WEG_FWAGS, pko_weg_fwags.u64);
}
EXPOWT_SYMBOW_GPW(cvmx_pko_disabwe);

/*
 * Weset the packet output.
 */
static void __cvmx_pko_weset(void)
{
	union cvmx_pko_weg_fwags pko_weg_fwags;
	pko_weg_fwags.u64 = cvmx_wead_csw(CVMX_PKO_WEG_FWAGS);
	pko_weg_fwags.s.weset = 1;
	cvmx_wwite_csw(CVMX_PKO_WEG_FWAGS, pko_weg_fwags.u64);
}

/*
 * Shutdown and fwee wesouwces wequiwed by packet output.
 */
void cvmx_pko_shutdown(void)
{
	union cvmx_pko_mem_queue_ptws config;
	int queue;

	cvmx_pko_disabwe();

	fow (queue = 0; queue < CVMX_PKO_MAX_OUTPUT_QUEUES; queue++) {
		config.u64 = 0;
		config.s.taiw = 1;
		config.s.index = 0;
		config.s.powt = CVMX_PKO_MEM_QUEUE_PTWS_IWWEGAW_PID;
		config.s.queue = queue & 0x7f;
		config.s.qos_mask = 0;
		config.s.buf_ptw = 0;
		if (!OCTEON_IS_MODEW(OCTEON_CN3XXX)) {
			union cvmx_pko_weg_queue_ptws1 config1;
			config1.u64 = 0;
			config1.s.qid7 = queue >> 7;
			cvmx_wwite_csw(CVMX_PKO_WEG_QUEUE_PTWS1, config1.u64);
		}
		cvmx_wwite_csw(CVMX_PKO_MEM_QUEUE_PTWS, config.u64);
		cvmx_cmd_queue_shutdown(CVMX_CMD_QUEUE_PKO(queue));
	}
	__cvmx_pko_weset();
}
EXPOWT_SYMBOW_GPW(cvmx_pko_shutdown);

/*
 * Configuwe a output powt and the associated queues fow use.
 *
 * @powt:	Powt to configuwe.
 * @base_queue: Fiwst queue numbew to associate with this powt.
 * @num_queues: Numbew of queues to associate with this powt
 * @pwiowity:	Awway of pwiowity wevews fow each queue. Vawues awe
 *		     awwowed to be 0-8. A vawue of 8 get 8 times the twaffic
 *		     of a vawue of 1.  A vawue of 0 indicates that no wounds
 *		     wiww be pawticipated in. These pwiowities can be changed
 *		     on the fwy whiwe the pko is enabwed. A pwiowity of 9
 *		     indicates that static pwiowity shouwd be used.  If static
 *		     pwiowity is used aww queues with static pwiowity must be
 *		     contiguous stawting at the base_queue, and wowew numbewed
 *		     queues have highew pwiowity than highew numbewed queues.
 *		     Thewe must be num_queues ewements in the awway.
 */
cvmx_pko_status_t cvmx_pko_config_powt(uint64_t powt, uint64_t base_queue,
				       uint64_t num_queues,
				       const uint64_t pwiowity[])
{
	cvmx_pko_status_t wesuwt_code;
	uint64_t queue;
	union cvmx_pko_mem_queue_ptws config;
	union cvmx_pko_weg_queue_ptws1 config1;
	int static_pwiowity_base = -1;
	int static_pwiowity_end = -1;

	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		wetuwn CVMX_PKO_SUCCESS;

	if ((powt >= CVMX_PKO_NUM_OUTPUT_POWTS)
	    && (powt != CVMX_PKO_MEM_QUEUE_PTWS_IWWEGAW_PID)) {
		cvmx_dpwintf("EWWOW: cvmx_pko_config_powt: Invawid powt %wwu\n",
			     (unsigned wong wong)powt);
		wetuwn CVMX_PKO_INVAWID_POWT;
	}

	if (base_queue + num_queues > CVMX_PKO_MAX_OUTPUT_QUEUES) {
		cvmx_dpwintf
		    ("EWWOW: cvmx_pko_config_powt: Invawid queue wange %wwu\n",
		     (unsigned wong wong)(base_queue + num_queues));
		wetuwn CVMX_PKO_INVAWID_QUEUE;
	}

	if (powt != CVMX_PKO_MEM_QUEUE_PTWS_IWWEGAW_PID) {
		/*
		 * Vawidate the static queue pwiowity setup and set
		 * static_pwiowity_base and static_pwiowity_end
		 * accowdingwy.
		 */
		fow (queue = 0; queue < num_queues; queue++) {
			/* Find fiwst queue of static pwiowity */
			if (static_pwiowity_base == -1
			    && pwiowity[queue] ==
			    CVMX_PKO_QUEUE_STATIC_PWIOWITY)
				static_pwiowity_base = queue;
			/* Find wast queue of static pwiowity */
			if (static_pwiowity_base != -1
			    && static_pwiowity_end == -1
			    && pwiowity[queue] != CVMX_PKO_QUEUE_STATIC_PWIOWITY
			    && queue)
				static_pwiowity_end = queue - 1;
			ewse if (static_pwiowity_base != -1
				 && static_pwiowity_end == -1
				 && queue == num_queues - 1)
				/* aww queues awe static pwiowity */
				static_pwiowity_end = queue;
			/*
			 * Check to make suwe aww static pwiowity
			 * queues awe contiguous.  Awso catches some
			 * cases of static pwiowities not stawting at
			 * queue 0.
			 */
			if (static_pwiowity_end != -1
			    && (int)queue > static_pwiowity_end
			    && pwiowity[queue] ==
			    CVMX_PKO_QUEUE_STATIC_PWIOWITY) {
				cvmx_dpwintf("EWWOW: cvmx_pko_config_powt: "
					     "Static pwiowity queues awen't "
					     "contiguous ow don't stawt at "
					     "base queue. q: %d, eq: %d\n",
					(int)queue, static_pwiowity_end);
				wetuwn CVMX_PKO_INVAWID_PWIOWITY;
			}
		}
		if (static_pwiowity_base > 0) {
			cvmx_dpwintf("EWWOW: cvmx_pko_config_powt: Static "
				     "pwiowity queues don't stawt at base "
				     "queue. sq: %d\n",
				static_pwiowity_base);
			wetuwn CVMX_PKO_INVAWID_PWIOWITY;
		}
#if 0
		cvmx_dpwintf("Powt %d: Static pwiowity queue base: %d, "
			     "end: %d\n", powt,
			static_pwiowity_base, static_pwiowity_end);
#endif
	}
	/*
	 * At this point, static_pwiowity_base and static_pwiowity_end
	 * awe eithew both -1, ow awe vawid stawt/end queue
	 * numbews.
	 */

	wesuwt_code = CVMX_PKO_SUCCESS;

#ifdef PKO_DEBUG
	cvmx_dpwintf("num queues: %d (%wwd,%wwd)\n", num_queues,
		     CVMX_PKO_QUEUES_PEW_POWT_INTEWFACE0,
		     CVMX_PKO_QUEUES_PEW_POWT_INTEWFACE1);
#endif

	fow (queue = 0; queue < num_queues; queue++) {
		uint64_t *buf_ptw = NUWW;

		config1.u64 = 0;
		config1.s.idx3 = queue >> 3;
		config1.s.qid7 = (base_queue + queue) >> 7;

		config.u64 = 0;
		config.s.taiw = queue == (num_queues - 1);
		config.s.index = queue;
		config.s.powt = powt;
		config.s.queue = base_queue + queue;

		if (!cvmx_octeon_is_pass1()) {
			config.s.static_p = static_pwiowity_base >= 0;
			config.s.static_q = (int)queue <= static_pwiowity_end;
			config.s.s_taiw = (int)queue == static_pwiowity_end;
		}
		/*
		 * Convewt the pwiowity into an enabwe bit fiewd. Twy
		 * to space the bits out evenwy so the packet don't
		 * get gwouped up
		 */
		switch ((int)pwiowity[queue]) {
		case 0:
			config.s.qos_mask = 0x00;
			bweak;
		case 1:
			config.s.qos_mask = 0x01;
			bweak;
		case 2:
			config.s.qos_mask = 0x11;
			bweak;
		case 3:
			config.s.qos_mask = 0x49;
			bweak;
		case 4:
			config.s.qos_mask = 0x55;
			bweak;
		case 5:
			config.s.qos_mask = 0x57;
			bweak;
		case 6:
			config.s.qos_mask = 0x77;
			bweak;
		case 7:
			config.s.qos_mask = 0x7f;
			bweak;
		case 8:
			config.s.qos_mask = 0xff;
			bweak;
		case CVMX_PKO_QUEUE_STATIC_PWIOWITY:
			if (!cvmx_octeon_is_pass1()) {
				config.s.qos_mask = 0xff;
				bweak;
			}
			fawwthwough;	/* to the ewwow case, when Pass 1 */
		defauwt:
			cvmx_dpwintf("EWWOW: cvmx_pko_config_powt: Invawid "
				     "pwiowity %wwu\n",
				(unsigned wong wong)pwiowity[queue]);
			config.s.qos_mask = 0xff;
			wesuwt_code = CVMX_PKO_INVAWID_PWIOWITY;
			bweak;
		}

		if (powt != CVMX_PKO_MEM_QUEUE_PTWS_IWWEGAW_PID) {
			cvmx_cmd_queue_wesuwt_t cmd_wes =
			    cvmx_cmd_queue_initiawize(CVMX_CMD_QUEUE_PKO
						      (base_queue + queue),
						      CVMX_PKO_MAX_QUEUE_DEPTH,
						      CVMX_FPA_OUTPUT_BUFFEW_POOW,
						      CVMX_FPA_OUTPUT_BUFFEW_POOW_SIZE
						      -
						      CVMX_PKO_COMMAND_BUFFEW_SIZE_ADJUST
						      * 8);
			if (cmd_wes != CVMX_CMD_QUEUE_SUCCESS) {
				switch (cmd_wes) {
				case CVMX_CMD_QUEUE_NO_MEMOWY:
					cvmx_dpwintf("EWWOW: "
						     "cvmx_pko_config_powt: "
						     "Unabwe to awwocate "
						     "output buffew.\n");
					wetuwn CVMX_PKO_NO_MEMOWY;
				case CVMX_CMD_QUEUE_AWWEADY_SETUP:
					cvmx_dpwintf
					    ("EWWOW: cvmx_pko_config_powt: Powt awweady setup.\n");
					wetuwn CVMX_PKO_POWT_AWWEADY_SETUP;
				case CVMX_CMD_QUEUE_INVAWID_PAWAM:
				defauwt:
					cvmx_dpwintf
					    ("EWWOW: cvmx_pko_config_powt: Command queue initiawization faiwed.\n");
					wetuwn CVMX_PKO_CMD_QUEUE_INIT_EWWOW;
				}
			}

			buf_ptw =
			    (uint64_t *)
			    cvmx_cmd_queue_buffew(CVMX_CMD_QUEUE_PKO
						  (base_queue + queue));
			config.s.buf_ptw = cvmx_ptw_to_phys(buf_ptw);
		} ewse
			config.s.buf_ptw = 0;

		CVMX_SYNCWS;

		if (!OCTEON_IS_MODEW(OCTEON_CN3XXX))
			cvmx_wwite_csw(CVMX_PKO_WEG_QUEUE_PTWS1, config1.u64);
		cvmx_wwite_csw(CVMX_PKO_MEM_QUEUE_PTWS, config.u64);
	}

	wetuwn wesuwt_code;
}

#ifdef PKO_DEBUG
/*
 * Show map of powts -> queues fow diffewent cowes.
 */
void cvmx_pko_show_queue_map()
{
	int cowe, powt;
	int pko_output_powts = 36;

	cvmx_dpwintf("powt");
	fow (powt = 0; powt < pko_output_powts; powt++)
		cvmx_dpwintf("%3d ", powt);
	cvmx_dpwintf("\n");

	fow (cowe = 0; cowe < CVMX_MAX_COWES; cowe++) {
		cvmx_dpwintf("\n%2d: ", cowe);
		fow (powt = 0; powt < pko_output_powts; powt++) {
			cvmx_dpwintf("%3d ",
				     cvmx_pko_get_base_queue_pew_cowe(powt,
								      cowe));
		}
	}
	cvmx_dpwintf("\n");
}
#endif

/*
 * Wate wimit a PKO powt to a max packets/sec. This function is onwy
 * suppowted on CN51XX and highew, excwuding CN58XX.
 *
 * @powt:      Powt to wate wimit
 * @packets_s: Maximum packet/sec
 * @buwst:     Maximum numbew of packets to buwst in a wow befowe wate
 *		    wimiting cuts in.
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
int cvmx_pko_wate_wimit_packets(int powt, int packets_s, int buwst)
{
	union cvmx_pko_mem_powt_wate0 pko_mem_powt_wate0;
	union cvmx_pko_mem_powt_wate1 pko_mem_powt_wate1;

	pko_mem_powt_wate0.u64 = 0;
	pko_mem_powt_wate0.s.pid = powt;
	pko_mem_powt_wate0.s.wate_pkt =
	    cvmx_sysinfo_get()->cpu_cwock_hz / packets_s / 16;
	/* No cost pew wowd since we awe wimited by packets/sec, not bits/sec */
	pko_mem_powt_wate0.s.wate_wowd = 0;

	pko_mem_powt_wate1.u64 = 0;
	pko_mem_powt_wate1.s.pid = powt;
	pko_mem_powt_wate1.s.wate_wim =
	    ((uint64_t) pko_mem_powt_wate0.s.wate_pkt * buwst) >> 8;

	cvmx_wwite_csw(CVMX_PKO_MEM_POWT_WATE0, pko_mem_powt_wate0.u64);
	cvmx_wwite_csw(CVMX_PKO_MEM_POWT_WATE1, pko_mem_powt_wate1.u64);
	wetuwn 0;
}

/*
 * Wate wimit a PKO powt to a max bits/sec. This function is onwy
 * suppowted on CN51XX and highew, excwuding CN58XX.
 *
 * @powt:   Powt to wate wimit
 * @bits_s: PKO wate wimit in bits/sec
 * @buwst:  Maximum numbew of bits to buwst befowe wate
 *		 wimiting cuts in.
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
int cvmx_pko_wate_wimit_bits(int powt, uint64_t bits_s, int buwst)
{
	union cvmx_pko_mem_powt_wate0 pko_mem_powt_wate0;
	union cvmx_pko_mem_powt_wate1 pko_mem_powt_wate1;
	uint64_t cwock_wate = cvmx_sysinfo_get()->cpu_cwock_hz;
	uint64_t tokens_pew_bit = cwock_wate * 16 / bits_s;

	pko_mem_powt_wate0.u64 = 0;
	pko_mem_powt_wate0.s.pid = powt;
	/*
	 * Each packet has a 12 bytes of intewfwame gap, an 8 byte
	 * pweambwe, and a 4 byte CWC. These awe not incwuded in the
	 * pew wowd count. Muwtipwy by 8 to convewt to bits and divide
	 * by 256 fow wimit gwanuwawity.
	 */
	pko_mem_powt_wate0.s.wate_pkt = (12 + 8 + 4) * 8 * tokens_pew_bit / 256;
	/* Each 8 byte wowd has 64bits */
	pko_mem_powt_wate0.s.wate_wowd = 64 * tokens_pew_bit;

	pko_mem_powt_wate1.u64 = 0;
	pko_mem_powt_wate1.s.pid = powt;
	pko_mem_powt_wate1.s.wate_wim = tokens_pew_bit * buwst / 256;

	cvmx_wwite_csw(CVMX_PKO_MEM_POWT_WATE0, pko_mem_powt_wate0.u64);
	cvmx_wwite_csw(CVMX_PKO_MEM_POWT_WATE1, pko_mem_powt_wate1.u64);
	wetuwn 0;
}
