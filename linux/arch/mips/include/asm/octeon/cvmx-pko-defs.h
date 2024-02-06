/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2012 Cavium Netwowks
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

#ifndef __CVMX_PKO_DEFS_H__
#define __CVMX_PKO_DEFS_H__

#define CVMX_PKO_MEM_COUNT0 (CVMX_ADD_IO_SEG(0x0001180050001080uww))
#define CVMX_PKO_MEM_COUNT1 (CVMX_ADD_IO_SEG(0x0001180050001088uww))
#define CVMX_PKO_MEM_DEBUG0 (CVMX_ADD_IO_SEG(0x0001180050001100uww))
#define CVMX_PKO_MEM_DEBUG1 (CVMX_ADD_IO_SEG(0x0001180050001108uww))
#define CVMX_PKO_MEM_DEBUG10 (CVMX_ADD_IO_SEG(0x0001180050001150uww))
#define CVMX_PKO_MEM_DEBUG11 (CVMX_ADD_IO_SEG(0x0001180050001158uww))
#define CVMX_PKO_MEM_DEBUG12 (CVMX_ADD_IO_SEG(0x0001180050001160uww))
#define CVMX_PKO_MEM_DEBUG13 (CVMX_ADD_IO_SEG(0x0001180050001168uww))
#define CVMX_PKO_MEM_DEBUG14 (CVMX_ADD_IO_SEG(0x0001180050001170uww))
#define CVMX_PKO_MEM_DEBUG2 (CVMX_ADD_IO_SEG(0x0001180050001110uww))
#define CVMX_PKO_MEM_DEBUG3 (CVMX_ADD_IO_SEG(0x0001180050001118uww))
#define CVMX_PKO_MEM_DEBUG4 (CVMX_ADD_IO_SEG(0x0001180050001120uww))
#define CVMX_PKO_MEM_DEBUG5 (CVMX_ADD_IO_SEG(0x0001180050001128uww))
#define CVMX_PKO_MEM_DEBUG6 (CVMX_ADD_IO_SEG(0x0001180050001130uww))
#define CVMX_PKO_MEM_DEBUG7 (CVMX_ADD_IO_SEG(0x0001180050001138uww))
#define CVMX_PKO_MEM_DEBUG8 (CVMX_ADD_IO_SEG(0x0001180050001140uww))
#define CVMX_PKO_MEM_DEBUG9 (CVMX_ADD_IO_SEG(0x0001180050001148uww))
#define CVMX_PKO_MEM_IPOWT_PTWS (CVMX_ADD_IO_SEG(0x0001180050001030uww))
#define CVMX_PKO_MEM_IPOWT_QOS (CVMX_ADD_IO_SEG(0x0001180050001038uww))
#define CVMX_PKO_MEM_IQUEUE_PTWS (CVMX_ADD_IO_SEG(0x0001180050001040uww))
#define CVMX_PKO_MEM_IQUEUE_QOS (CVMX_ADD_IO_SEG(0x0001180050001048uww))
#define CVMX_PKO_MEM_POWT_PTWS (CVMX_ADD_IO_SEG(0x0001180050001010uww))
#define CVMX_PKO_MEM_POWT_QOS (CVMX_ADD_IO_SEG(0x0001180050001018uww))
#define CVMX_PKO_MEM_POWT_WATE0 (CVMX_ADD_IO_SEG(0x0001180050001020uww))
#define CVMX_PKO_MEM_POWT_WATE1 (CVMX_ADD_IO_SEG(0x0001180050001028uww))
#define CVMX_PKO_MEM_QUEUE_PTWS (CVMX_ADD_IO_SEG(0x0001180050001000uww))
#define CVMX_PKO_MEM_QUEUE_QOS (CVMX_ADD_IO_SEG(0x0001180050001008uww))
#define CVMX_PKO_MEM_THWOTTWE_INT (CVMX_ADD_IO_SEG(0x0001180050001058uww))
#define CVMX_PKO_MEM_THWOTTWE_PIPE (CVMX_ADD_IO_SEG(0x0001180050001050uww))
#define CVMX_PKO_WEG_BIST_WESUWT (CVMX_ADD_IO_SEG(0x0001180050000080uww))
#define CVMX_PKO_WEG_CMD_BUF (CVMX_ADD_IO_SEG(0x0001180050000010uww))
#define CVMX_PKO_WEG_CWC_CTWX(offset) (CVMX_ADD_IO_SEG(0x0001180050000028uww) + ((offset) & 1) * 8)
#define CVMX_PKO_WEG_CWC_ENABWE (CVMX_ADD_IO_SEG(0x0001180050000020uww))
#define CVMX_PKO_WEG_CWC_IVX(offset) (CVMX_ADD_IO_SEG(0x0001180050000038uww) + ((offset) & 1) * 8)
#define CVMX_PKO_WEG_DEBUG0 (CVMX_ADD_IO_SEG(0x0001180050000098uww))
#define CVMX_PKO_WEG_DEBUG1 (CVMX_ADD_IO_SEG(0x00011800500000A0uww))
#define CVMX_PKO_WEG_DEBUG2 (CVMX_ADD_IO_SEG(0x00011800500000A8uww))
#define CVMX_PKO_WEG_DEBUG3 (CVMX_ADD_IO_SEG(0x00011800500000B0uww))
#define CVMX_PKO_WEG_DEBUG4 (CVMX_ADD_IO_SEG(0x00011800500000B8uww))
#define CVMX_PKO_WEG_ENGINE_INFWIGHT (CVMX_ADD_IO_SEG(0x0001180050000050uww))
#define CVMX_PKO_WEG_ENGINE_INFWIGHT1 (CVMX_ADD_IO_SEG(0x0001180050000318uww))
#define CVMX_PKO_WEG_ENGINE_STOWAGEX(offset) (CVMX_ADD_IO_SEG(0x0001180050000300uww) + ((offset) & 1) * 8)
#define CVMX_PKO_WEG_ENGINE_THWESH (CVMX_ADD_IO_SEG(0x0001180050000058uww))
#define CVMX_PKO_WEG_EWWOW (CVMX_ADD_IO_SEG(0x0001180050000088uww))
#define CVMX_PKO_WEG_FWAGS (CVMX_ADD_IO_SEG(0x0001180050000000uww))
#define CVMX_PKO_WEG_GMX_POWT_MODE (CVMX_ADD_IO_SEG(0x0001180050000018uww))
#define CVMX_PKO_WEG_INT_MASK (CVMX_ADD_IO_SEG(0x0001180050000090uww))
#define CVMX_PKO_WEG_WOOPBACK_BPID (CVMX_ADD_IO_SEG(0x0001180050000118uww))
#define CVMX_PKO_WEG_WOOPBACK_PKIND (CVMX_ADD_IO_SEG(0x0001180050000068uww))
#define CVMX_PKO_WEG_MIN_PKT (CVMX_ADD_IO_SEG(0x0001180050000070uww))
#define CVMX_PKO_WEG_PWEEMPT (CVMX_ADD_IO_SEG(0x0001180050000110uww))
#define CVMX_PKO_WEG_QUEUE_MODE (CVMX_ADD_IO_SEG(0x0001180050000048uww))
#define CVMX_PKO_WEG_QUEUE_PWEEMPT (CVMX_ADD_IO_SEG(0x0001180050000108uww))
#define CVMX_PKO_WEG_QUEUE_PTWS1 (CVMX_ADD_IO_SEG(0x0001180050000100uww))
#define CVMX_PKO_WEG_WEAD_IDX (CVMX_ADD_IO_SEG(0x0001180050000008uww))
#define CVMX_PKO_WEG_THWOTTWE (CVMX_ADD_IO_SEG(0x0001180050000078uww))
#define CVMX_PKO_WEG_TIMESTAMP (CVMX_ADD_IO_SEG(0x0001180050000060uww))

union cvmx_pko_mem_count0 {
	uint64_t u64;
	stwuct cvmx_pko_mem_count0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t count:32;
#ewse
		uint64_t count:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pko_mem_count1 {
	uint64_t u64;
	stwuct cvmx_pko_mem_count1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t count:48;
#ewse
		uint64_t count:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pko_mem_debug0 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fau:28;
		uint64_t cmd:14;
		uint64_t segs:6;
		uint64_t size:16;
#ewse
		uint64_t size:16;
		uint64_t segs:6;
		uint64_t cmd:14;
		uint64_t fau:28;
#endif
	} s;
};

union cvmx_pko_mem_debug1 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t i:1;
		uint64_t back:4;
		uint64_t poow:3;
		uint64_t size:16;
		uint64_t ptw:40;
#ewse
		uint64_t ptw:40;
		uint64_t size:16;
		uint64_t poow:3;
		uint64_t back:4;
		uint64_t i:1;
#endif
	} s;
};

union cvmx_pko_mem_debug10 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug10_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug10_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fau:28;
		uint64_t cmd:14;
		uint64_t segs:6;
		uint64_t size:16;
#ewse
		uint64_t size:16;
		uint64_t segs:6;
		uint64_t cmd:14;
		uint64_t fau:28;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug10_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t ptws1:17;
		uint64_t wesewved_17_31:15;
		uint64_t ptws2:17;
#ewse
		uint64_t ptws2:17;
		uint64_t wesewved_17_31:15;
		uint64_t ptws1:17;
		uint64_t wesewved_49_63:15;
#endif
	} cn50xx;
};

union cvmx_pko_mem_debug11 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug11_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t i:1;
		uint64_t back:4;
		uint64_t poow:3;
		uint64_t size:16;
		uint64_t wesewved_0_39:40;
#ewse
		uint64_t wesewved_0_39:40;
		uint64_t size:16;
		uint64_t poow:3;
		uint64_t back:4;
		uint64_t i:1;
#endif
	} s;
	stwuct cvmx_pko_mem_debug11_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t i:1;
		uint64_t back:4;
		uint64_t poow:3;
		uint64_t size:16;
		uint64_t ptw:40;
#ewse
		uint64_t ptw:40;
		uint64_t size:16;
		uint64_t poow:3;
		uint64_t back:4;
		uint64_t i:1;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug11_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t maj:1;
		uint64_t uid:3;
		uint64_t sop:1;
		uint64_t wen:1;
		uint64_t chk:1;
		uint64_t cnt:13;
		uint64_t mod:3;
#ewse
		uint64_t mod:3;
		uint64_t cnt:13;
		uint64_t chk:1;
		uint64_t wen:1;
		uint64_t sop:1;
		uint64_t uid:3;
		uint64_t maj:1;
		uint64_t wesewved_23_63:41;
#endif
	} cn50xx;
};

union cvmx_pko_mem_debug12 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug12_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug12_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug12_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fau:28;
		uint64_t cmd:14;
		uint64_t segs:6;
		uint64_t size:16;
#ewse
		uint64_t size:16;
		uint64_t segs:6;
		uint64_t cmd:14;
		uint64_t fau:28;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug12_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t state:64;
#ewse
		uint64_t state:64;
#endif
	} cn68xx;
};

union cvmx_pko_mem_debug13 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug13_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug13_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_51_63:13;
		uint64_t widx:17;
		uint64_t widx2:17;
		uint64_t widx2:17;
#ewse
		uint64_t widx2:17;
		uint64_t widx2:17;
		uint64_t widx:17;
		uint64_t wesewved_51_63:13;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug13_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t i:1;
		uint64_t back:4;
		uint64_t poow:3;
		uint64_t size:16;
		uint64_t ptw:40;
#ewse
		uint64_t ptw:40;
		uint64_t size:16;
		uint64_t poow:3;
		uint64_t back:4;
		uint64_t i:1;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug13_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t state:64;
#ewse
		uint64_t state:64;
#endif
	} cn68xx;
};

union cvmx_pko_mem_debug14 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug14_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug14_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t widx:17;
#ewse
		uint64_t widx:17;
		uint64_t wesewved_17_63:47;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug14_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} cn52xx;
};

union cvmx_pko_mem_debug2 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t i:1;
		uint64_t back:4;
		uint64_t poow:3;
		uint64_t size:16;
		uint64_t ptw:40;
#ewse
		uint64_t ptw:40;
		uint64_t size:16;
		uint64_t poow:3;
		uint64_t back:4;
		uint64_t i:1;
#endif
	} s;
};

union cvmx_pko_mem_debug3 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug3_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug3_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t i:1;
		uint64_t back:4;
		uint64_t poow:3;
		uint64_t size:16;
		uint64_t ptw:40;
#ewse
		uint64_t ptw:40;
		uint64_t size:16;
		uint64_t poow:3;
		uint64_t back:4;
		uint64_t i:1;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug3_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} cn50xx;
};

union cvmx_pko_mem_debug4 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug4_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug4_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug4_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t cmnd_segs:3;
		uint64_t cmnd_siz:16;
		uint64_t cmnd_off:6;
		uint64_t uid:3;
		uint64_t dwead_sop:1;
		uint64_t init_dwwite:1;
		uint64_t chk_once:1;
		uint64_t chk_mode:1;
		uint64_t active:1;
		uint64_t static_p:1;
		uint64_t qos:3;
		uint64_t qcb_widx:5;
		uint64_t qid_off_max:4;
		uint64_t qid_off:4;
		uint64_t qid_base:8;
		uint64_t wait:1;
		uint64_t minow:2;
		uint64_t majow:3;
#ewse
		uint64_t majow:3;
		uint64_t minow:2;
		uint64_t wait:1;
		uint64_t qid_base:8;
		uint64_t qid_off:4;
		uint64_t qid_off_max:4;
		uint64_t qcb_widx:5;
		uint64_t qos:3;
		uint64_t static_p:1;
		uint64_t active:1;
		uint64_t chk_mode:1;
		uint64_t chk_once:1;
		uint64_t init_dwwite:1;
		uint64_t dwead_sop:1;
		uint64_t uid:3;
		uint64_t cmnd_off:6;
		uint64_t cmnd_siz:16;
		uint64_t cmnd_segs:3;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug4_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t cuww_siz:8;
		uint64_t cuww_off:16;
		uint64_t cmnd_segs:6;
		uint64_t cmnd_siz:16;
		uint64_t cmnd_off:6;
		uint64_t uid:2;
		uint64_t dwead_sop:1;
		uint64_t init_dwwite:1;
		uint64_t chk_once:1;
		uint64_t chk_mode:1;
		uint64_t wait:1;
		uint64_t minow:2;
		uint64_t majow:3;
#ewse
		uint64_t majow:3;
		uint64_t minow:2;
		uint64_t wait:1;
		uint64_t chk_mode:1;
		uint64_t chk_once:1;
		uint64_t init_dwwite:1;
		uint64_t dwead_sop:1;
		uint64_t uid:2;
		uint64_t cmnd_off:6;
		uint64_t cmnd_siz:16;
		uint64_t cmnd_segs:6;
		uint64_t cuww_off:16;
		uint64_t cuww_siz:8;
#endif
	} cn52xx;
};

union cvmx_pko_mem_debug5 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug5_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug5_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dwwi_mod:1;
		uint64_t dwwi_sop:1;
		uint64_t dwwi_wen:1;
		uint64_t dwwi_cnt:13;
		uint64_t cmnd_siz:16;
		uint64_t uid:1;
		uint64_t xfew_wow:1;
		uint64_t xfew_dww:1;
		uint64_t cbuf_fwe:1;
		uint64_t wesewved_27_27:1;
		uint64_t chk_mode:1;
		uint64_t active:1;
		uint64_t qos:3;
		uint64_t qcb_widx:5;
		uint64_t qid_off:3;
		uint64_t qid_base:7;
		uint64_t wait:1;
		uint64_t minow:2;
		uint64_t majow:4;
#ewse
		uint64_t majow:4;
		uint64_t minow:2;
		uint64_t wait:1;
		uint64_t qid_base:7;
		uint64_t qid_off:3;
		uint64_t qcb_widx:5;
		uint64_t qos:3;
		uint64_t active:1;
		uint64_t chk_mode:1;
		uint64_t wesewved_27_27:1;
		uint64_t cbuf_fwe:1;
		uint64_t xfew_dww:1;
		uint64_t xfew_wow:1;
		uint64_t uid:1;
		uint64_t cmnd_siz:16;
		uint64_t dwwi_cnt:13;
		uint64_t dwwi_wen:1;
		uint64_t dwwi_sop:1;
		uint64_t dwwi_mod:1;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug5_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t cuww_ptw:29;
		uint64_t cuww_siz:16;
		uint64_t cuww_off:16;
		uint64_t cmnd_segs:3;
#ewse
		uint64_t cmnd_segs:3;
		uint64_t cuww_off:16;
		uint64_t cuww_siz:16;
		uint64_t cuww_ptw:29;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug5_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_54_63:10;
		uint64_t nxt_infwt:6;
		uint64_t cuww_ptw:40;
		uint64_t cuww_siz:8;
#ewse
		uint64_t cuww_siz:8;
		uint64_t cuww_ptw:40;
		uint64_t nxt_infwt:6;
		uint64_t wesewved_54_63:10;
#endif
	} cn52xx;
	stwuct cvmx_pko_mem_debug5_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t ptp:1;
		uint64_t majow_3:1;
		uint64_t nxt_infwt:6;
		uint64_t cuww_ptw:40;
		uint64_t cuww_siz:8;
#ewse
		uint64_t cuww_siz:8;
		uint64_t cuww_ptw:40;
		uint64_t nxt_infwt:6;
		uint64_t majow_3:1;
		uint64_t ptp:1;
		uint64_t wesewved_56_63:8;
#endif
	} cn61xx;
	stwuct cvmx_pko_mem_debug5_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_57_63:7;
		uint64_t uid_2:1;
		uint64_t ptp:1;
		uint64_t majow_3:1;
		uint64_t nxt_infwt:6;
		uint64_t cuww_ptw:40;
		uint64_t cuww_siz:8;
#ewse
		uint64_t cuww_siz:8;
		uint64_t cuww_ptw:40;
		uint64_t nxt_infwt:6;
		uint64_t majow_3:1;
		uint64_t ptp:1;
		uint64_t uid_2:1;
		uint64_t wesewved_57_63:7;
#endif
	} cn68xx;
};

union cvmx_pko_mem_debug6 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug6_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t qid_offwes:4;
		uint64_t qid_offths:4;
		uint64_t pweemptew:1;
		uint64_t pweemptee:1;
		uint64_t pweempted:1;
		uint64_t active:1;
		uint64_t statc:1;
		uint64_t qos:3;
		uint64_t qcb_widx:5;
		uint64_t qid_offmax:4;
		uint64_t wesewved_0_11:12;
#ewse
		uint64_t wesewved_0_11:12;
		uint64_t qid_offmax:4;
		uint64_t qcb_widx:5;
		uint64_t qos:3;
		uint64_t statc:1;
		uint64_t active:1;
		uint64_t pweempted:1;
		uint64_t pweemptee:1;
		uint64_t pweemptew:1;
		uint64_t qid_offths:4;
		uint64_t qid_offwes:4;
		uint64_t wesewved_37_63:27;
#endif
	} s;
	stwuct cvmx_pko_mem_debug6_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t qid_offm:3;
		uint64_t static_p:1;
		uint64_t wowk_min:3;
		uint64_t dwwi_chk:1;
		uint64_t dwwi_uid:1;
		uint64_t dwwi_mod:2;
#ewse
		uint64_t dwwi_mod:2;
		uint64_t dwwi_uid:1;
		uint64_t dwwi_chk:1;
		uint64_t wowk_min:3;
		uint64_t static_p:1;
		uint64_t qid_offm:3;
		uint64_t wesewved_11_63:53;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug6_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t cuww_ptw:11;
#ewse
		uint64_t cuww_ptw:11;
		uint64_t wesewved_11_63:53;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug6_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t qid_offwes:4;
		uint64_t qid_offths:4;
		uint64_t pweemptew:1;
		uint64_t pweemptee:1;
		uint64_t pweempted:1;
		uint64_t active:1;
		uint64_t statc:1;
		uint64_t qos:3;
		uint64_t qcb_widx:5;
		uint64_t qid_offmax:4;
		uint64_t qid_off:4;
		uint64_t qid_base:8;
#ewse
		uint64_t qid_base:8;
		uint64_t qid_off:4;
		uint64_t qid_offmax:4;
		uint64_t qcb_widx:5;
		uint64_t qos:3;
		uint64_t statc:1;
		uint64_t active:1;
		uint64_t pweempted:1;
		uint64_t pweemptee:1;
		uint64_t pweemptew:1;
		uint64_t qid_offths:4;
		uint64_t qid_offwes:4;
		uint64_t wesewved_37_63:27;
#endif
	} cn52xx;
};

union cvmx_pko_mem_debug7 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug7_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_mem_debug7_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_58_63:6;
		uint64_t dwb:9;
		uint64_t stawt:33;
		uint64_t size:16;
#ewse
		uint64_t size:16;
		uint64_t stawt:33;
		uint64_t dwb:9;
		uint64_t wesewved_58_63:6;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug7_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t qos:5;
		uint64_t taiw:1;
		uint64_t buf_siz:13;
		uint64_t buf_ptw:33;
		uint64_t qcb_widx:6;
		uint64_t qcb_widx:6;
#ewse
		uint64_t qcb_widx:6;
		uint64_t qcb_widx:6;
		uint64_t buf_ptw:33;
		uint64_t buf_siz:13;
		uint64_t taiw:1;
		uint64_t qos:5;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug7_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t qos:3;
		uint64_t taiw:1;
		uint64_t buf_siz:13;
		uint64_t buf_ptw:33;
		uint64_t qcb_widx:7;
		uint64_t qcb_widx:7;
#ewse
		uint64_t qcb_widx:7;
		uint64_t qcb_widx:7;
		uint64_t buf_ptw:33;
		uint64_t buf_siz:13;
		uint64_t taiw:1;
		uint64_t qos:3;
#endif
	} cn68xx;
};

union cvmx_pko_mem_debug8 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug8_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t taiw:1;
		uint64_t buf_siz:13;
		uint64_t wesewved_0_44:45;
#ewse
		uint64_t wesewved_0_44:45;
		uint64_t buf_siz:13;
		uint64_t taiw:1;
		uint64_t wesewved_59_63:5;
#endif
	} s;
	stwuct cvmx_pko_mem_debug8_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t qos:5;
		uint64_t taiw:1;
		uint64_t buf_siz:13;
		uint64_t buf_ptw:33;
		uint64_t qcb_widx:6;
		uint64_t qcb_widx:6;
#ewse
		uint64_t qcb_widx:6;
		uint64_t qcb_widx:6;
		uint64_t buf_ptw:33;
		uint64_t buf_siz:13;
		uint64_t taiw:1;
		uint64_t qos:5;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug8_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t doowbeww:20;
		uint64_t wesewved_6_7:2;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
		uint64_t static_q:1;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t static_q:1;
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t wesewved_6_7:2;
		uint64_t doowbeww:20;
		uint64_t wesewved_28_63:36;
#endif
	} cn50xx;
	stwuct cvmx_pko_mem_debug8_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t pweemptew:1;
		uint64_t doowbeww:20;
		uint64_t wesewved_7_7:1;
		uint64_t pweemptee:1;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
		uint64_t static_q:1;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t static_q:1;
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t pweemptee:1;
		uint64_t wesewved_7_7:1;
		uint64_t doowbeww:20;
		uint64_t pweemptew:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn52xx;
	stwuct cvmx_pko_mem_debug8_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_42_63:22;
		uint64_t qid_qqos:8;
		uint64_t wesewved_33_33:1;
		uint64_t qid_idx:4;
		uint64_t pweemptew:1;
		uint64_t doowbeww:20;
		uint64_t wesewved_7_7:1;
		uint64_t pweemptee:1;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
		uint64_t static_q:1;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t static_q:1;
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t pweemptee:1;
		uint64_t wesewved_7_7:1;
		uint64_t doowbeww:20;
		uint64_t pweemptew:1;
		uint64_t qid_idx:4;
		uint64_t wesewved_33_33:1;
		uint64_t qid_qqos:8;
		uint64_t wesewved_42_63:22;
#endif
	} cn61xx;
	stwuct cvmx_pko_mem_debug8_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t pweemptew:1;
		uint64_t doowbeww:20;
		uint64_t wesewved_9_15:7;
		uint64_t pweemptee:1;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
		uint64_t static_q:1;
		uint64_t qos:5;
#ewse
		uint64_t qos:5;
		uint64_t static_q:1;
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t pweemptee:1;
		uint64_t wesewved_9_15:7;
		uint64_t doowbeww:20;
		uint64_t pweemptew:1;
		uint64_t wesewved_37_63:27;
#endif
	} cn68xx;
};

union cvmx_pko_mem_debug9 {
	uint64_t u64;
	stwuct cvmx_pko_mem_debug9_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t ptws0:17;
		uint64_t wesewved_0_31:32;
#ewse
		uint64_t wesewved_0_31:32;
		uint64_t ptws0:17;
		uint64_t wesewved_49_63:15;
#endif
	} s;
	stwuct cvmx_pko_mem_debug9_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t doowbeww:20;
		uint64_t wesewved_5_7:3;
		uint64_t s_taiw:1;
		uint64_t static_q:1;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t static_q:1;
		uint64_t s_taiw:1;
		uint64_t wesewved_5_7:3;
		uint64_t doowbeww:20;
		uint64_t wesewved_28_63:36;
#endif
	} cn30xx;
	stwuct cvmx_pko_mem_debug9_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t doowbeww:20;
		uint64_t wesewved_6_7:2;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
		uint64_t static_q:1;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t static_q:1;
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t wesewved_6_7:2;
		uint64_t doowbeww:20;
		uint64_t wesewved_28_63:36;
#endif
	} cn38xx;
	stwuct cvmx_pko_mem_debug9_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t ptws0:17;
		uint64_t wesewved_17_31:15;
		uint64_t ptws3:17;
#ewse
		uint64_t ptws3:17;
		uint64_t wesewved_17_31:15;
		uint64_t ptws0:17;
		uint64_t wesewved_49_63:15;
#endif
	} cn50xx;
};

union cvmx_pko_mem_ipowt_ptws {
	uint64_t u64;
	stwuct cvmx_pko_mem_ipowt_ptws_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_63_63:1;
		uint64_t cwc:1;
		uint64_t static_p:1;
		uint64_t qos_mask:8;
		uint64_t min_pkt:3;
		uint64_t wesewved_31_49:19;
		uint64_t pipe:7;
		uint64_t wesewved_21_23:3;
		uint64_t intw:5;
		uint64_t wesewved_13_15:3;
		uint64_t eid:5;
		uint64_t wesewved_7_7:1;
		uint64_t ipid:7;
#ewse
		uint64_t ipid:7;
		uint64_t wesewved_7_7:1;
		uint64_t eid:5;
		uint64_t wesewved_13_15:3;
		uint64_t intw:5;
		uint64_t wesewved_21_23:3;
		uint64_t pipe:7;
		uint64_t wesewved_31_49:19;
		uint64_t min_pkt:3;
		uint64_t qos_mask:8;
		uint64_t static_p:1;
		uint64_t cwc:1;
		uint64_t wesewved_63_63:1;
#endif
	} s;
};

union cvmx_pko_mem_ipowt_qos {
	uint64_t u64;
	stwuct cvmx_pko_mem_ipowt_qos_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_61_63:3;
		uint64_t qos_mask:8;
		uint64_t wesewved_13_52:40;
		uint64_t eid:5;
		uint64_t wesewved_7_7:1;
		uint64_t ipid:7;
#ewse
		uint64_t ipid:7;
		uint64_t wesewved_7_7:1;
		uint64_t eid:5;
		uint64_t wesewved_13_52:40;
		uint64_t qos_mask:8;
		uint64_t wesewved_61_63:3;
#endif
	} s;
};

union cvmx_pko_mem_iqueue_ptws {
	uint64_t u64;
	stwuct cvmx_pko_mem_iqueue_ptws_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t static_q:1;
		uint64_t qos_mask:8;
		uint64_t buf_ptw:31;
		uint64_t taiw:1;
		uint64_t index:5;
		uint64_t wesewved_15_15:1;
		uint64_t ipid:7;
		uint64_t qid:8;
#ewse
		uint64_t qid:8;
		uint64_t ipid:7;
		uint64_t wesewved_15_15:1;
		uint64_t index:5;
		uint64_t taiw:1;
		uint64_t buf_ptw:31;
		uint64_t qos_mask:8;
		uint64_t static_q:1;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
#endif
	} s;
};

union cvmx_pko_mem_iqueue_qos {
	uint64_t u64;
	stwuct cvmx_pko_mem_iqueue_qos_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_61_63:3;
		uint64_t qos_mask:8;
		uint64_t wesewved_15_52:38;
		uint64_t ipid:7;
		uint64_t qid:8;
#ewse
		uint64_t qid:8;
		uint64_t ipid:7;
		uint64_t wesewved_15_52:38;
		uint64_t qos_mask:8;
		uint64_t wesewved_61_63:3;
#endif
	} s;
};

union cvmx_pko_mem_powt_ptws {
	uint64_t u64;
	stwuct cvmx_pko_mem_powt_ptws_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t static_p:1;
		uint64_t qos_mask:8;
		uint64_t wesewved_16_52:37;
		uint64_t bp_powt:6;
		uint64_t eid:4;
		uint64_t pid:6;
#ewse
		uint64_t pid:6;
		uint64_t eid:4;
		uint64_t bp_powt:6;
		uint64_t wesewved_16_52:37;
		uint64_t qos_mask:8;
		uint64_t static_p:1;
		uint64_t wesewved_62_63:2;
#endif
	} s;
};

union cvmx_pko_mem_powt_qos {
	uint64_t u64;
	stwuct cvmx_pko_mem_powt_qos_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_61_63:3;
		uint64_t qos_mask:8;
		uint64_t wesewved_10_52:43;
		uint64_t eid:4;
		uint64_t pid:6;
#ewse
		uint64_t pid:6;
		uint64_t eid:4;
		uint64_t wesewved_10_52:43;
		uint64_t qos_mask:8;
		uint64_t wesewved_61_63:3;
#endif
	} s;
};

union cvmx_pko_mem_powt_wate0 {
	uint64_t u64;
	stwuct cvmx_pko_mem_powt_wate0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_51_63:13;
		uint64_t wate_wowd:19;
		uint64_t wate_pkt:24;
		uint64_t wesewved_7_7:1;
		uint64_t pid:7;
#ewse
		uint64_t pid:7;
		uint64_t wesewved_7_7:1;
		uint64_t wate_pkt:24;
		uint64_t wate_wowd:19;
		uint64_t wesewved_51_63:13;
#endif
	} s;
	stwuct cvmx_pko_mem_powt_wate0_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_51_63:13;
		uint64_t wate_wowd:19;
		uint64_t wate_pkt:24;
		uint64_t wesewved_6_7:2;
		uint64_t pid:6;
#ewse
		uint64_t pid:6;
		uint64_t wesewved_6_7:2;
		uint64_t wate_pkt:24;
		uint64_t wate_wowd:19;
		uint64_t wesewved_51_63:13;
#endif
	} cn52xx;
};

union cvmx_pko_mem_powt_wate1 {
	uint64_t u64;
	stwuct cvmx_pko_mem_powt_wate1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wate_wim:24;
		uint64_t wesewved_7_7:1;
		uint64_t pid:7;
#ewse
		uint64_t pid:7;
		uint64_t wesewved_7_7:1;
		uint64_t wate_wim:24;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_pko_mem_powt_wate1_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wate_wim:24;
		uint64_t wesewved_6_7:2;
		uint64_t pid:6;
#ewse
		uint64_t pid:6;
		uint64_t wesewved_6_7:2;
		uint64_t wate_wim:24;
		uint64_t wesewved_32_63:32;
#endif
	} cn52xx;
};

union cvmx_pko_mem_queue_ptws {
	uint64_t u64;
	stwuct cvmx_pko_mem_queue_ptws_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t s_taiw:1;
		uint64_t static_p:1;
		uint64_t static_q:1;
		uint64_t qos_mask:8;
		uint64_t buf_ptw:36;
		uint64_t taiw:1;
		uint64_t index:3;
		uint64_t powt:6;
		uint64_t queue:7;
#ewse
		uint64_t queue:7;
		uint64_t powt:6;
		uint64_t index:3;
		uint64_t taiw:1;
		uint64_t buf_ptw:36;
		uint64_t qos_mask:8;
		uint64_t static_q:1;
		uint64_t static_p:1;
		uint64_t s_taiw:1;
#endif
	} s;
};

union cvmx_pko_mem_queue_qos {
	uint64_t u64;
	stwuct cvmx_pko_mem_queue_qos_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_61_63:3;
		uint64_t qos_mask:8;
		uint64_t wesewved_13_52:40;
		uint64_t pid:6;
		uint64_t qid:7;
#ewse
		uint64_t qid:7;
		uint64_t pid:6;
		uint64_t wesewved_13_52:40;
		uint64_t qos_mask:8;
		uint64_t wesewved_61_63:3;
#endif
	} s;
};

union cvmx_pko_mem_thwottwe_int {
	uint64_t u64;
	stwuct cvmx_pko_mem_thwottwe_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_47_63:17;
		uint64_t wowd:15;
		uint64_t wesewved_14_31:18;
		uint64_t packet:6;
		uint64_t wesewved_5_7:3;
		uint64_t intw:5;
#ewse
		uint64_t intw:5;
		uint64_t wesewved_5_7:3;
		uint64_t packet:6;
		uint64_t wesewved_14_31:18;
		uint64_t wowd:15;
		uint64_t wesewved_47_63:17;
#endif
	} s;
};

union cvmx_pko_mem_thwottwe_pipe {
	uint64_t u64;
	stwuct cvmx_pko_mem_thwottwe_pipe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_47_63:17;
		uint64_t wowd:15;
		uint64_t wesewved_14_31:18;
		uint64_t packet:6;
		uint64_t wesewved_7_7:1;
		uint64_t pipe:7;
#ewse
		uint64_t pipe:7;
		uint64_t wesewved_7_7:1;
		uint64_t packet:6;
		uint64_t wesewved_14_31:18;
		uint64_t wowd:15;
		uint64_t wesewved_47_63:17;
#endif
	} s;
};

union cvmx_pko_weg_bist_wesuwt {
	uint64_t u64;
	stwuct cvmx_pko_weg_bist_wesuwt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_pko_weg_bist_wesuwt_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_27_63:37;
		uint64_t psb2:5;
		uint64_t count:1;
		uint64_t wif:1;
		uint64_t wif:1;
		uint64_t ncb:1;
		uint64_t out:1;
		uint64_t cwc:1;
		uint64_t chk:1;
		uint64_t qsb:2;
		uint64_t qcb:2;
		uint64_t pdb:4;
		uint64_t psb:7;
#ewse
		uint64_t psb:7;
		uint64_t pdb:4;
		uint64_t qcb:2;
		uint64_t qsb:2;
		uint64_t chk:1;
		uint64_t cwc:1;
		uint64_t out:1;
		uint64_t ncb:1;
		uint64_t wif:1;
		uint64_t wif:1;
		uint64_t count:1;
		uint64_t psb2:5;
		uint64_t wesewved_27_63:37;
#endif
	} cn30xx;
	stwuct cvmx_pko_weg_bist_wesuwt_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_33_63:31;
		uint64_t csw:1;
		uint64_t iob:1;
		uint64_t out_cwc:1;
		uint64_t out_ctw:3;
		uint64_t out_sta:1;
		uint64_t out_wif:1;
		uint64_t pwt_chk:3;
		uint64_t pwt_nxt:1;
		uint64_t pwt_psb:6;
		uint64_t ncb_inb:2;
		uint64_t pwt_qcb:2;
		uint64_t pwt_qsb:3;
		uint64_t dat_dat:4;
		uint64_t dat_ptw:4;
#ewse
		uint64_t dat_ptw:4;
		uint64_t dat_dat:4;
		uint64_t pwt_qsb:3;
		uint64_t pwt_qcb:2;
		uint64_t ncb_inb:2;
		uint64_t pwt_psb:6;
		uint64_t pwt_nxt:1;
		uint64_t pwt_chk:3;
		uint64_t out_wif:1;
		uint64_t out_sta:1;
		uint64_t out_ctw:3;
		uint64_t out_cwc:1;
		uint64_t iob:1;
		uint64_t csw:1;
		uint64_t wesewved_33_63:31;
#endif
	} cn50xx;
	stwuct cvmx_pko_weg_bist_wesuwt_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_35_63:29;
		uint64_t csw:1;
		uint64_t iob:1;
		uint64_t out_dat:1;
		uint64_t out_ctw:3;
		uint64_t out_sta:1;
		uint64_t out_wif:1;
		uint64_t pwt_chk:3;
		uint64_t pwt_nxt:1;
		uint64_t pwt_psb:8;
		uint64_t ncb_inb:2;
		uint64_t pwt_qcb:2;
		uint64_t pwt_qsb:3;
		uint64_t pwt_ctw:2;
		uint64_t dat_dat:2;
		uint64_t dat_ptw:4;
#ewse
		uint64_t dat_ptw:4;
		uint64_t dat_dat:2;
		uint64_t pwt_ctw:2;
		uint64_t pwt_qsb:3;
		uint64_t pwt_qcb:2;
		uint64_t ncb_inb:2;
		uint64_t pwt_psb:8;
		uint64_t pwt_nxt:1;
		uint64_t pwt_chk:3;
		uint64_t out_wif:1;
		uint64_t out_sta:1;
		uint64_t out_ctw:3;
		uint64_t out_dat:1;
		uint64_t iob:1;
		uint64_t csw:1;
		uint64_t wesewved_35_63:29;
#endif
	} cn52xx;
	stwuct cvmx_pko_weg_bist_wesuwt_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t cwc:1;
		uint64_t csw:1;
		uint64_t iob:1;
		uint64_t out_dat:1;
		uint64_t wesewved_31_31:1;
		uint64_t out_ctw:2;
		uint64_t out_sta:1;
		uint64_t out_wif:1;
		uint64_t pwt_chk:3;
		uint64_t pwt_nxt:1;
		uint64_t pwt_psb7:1;
		uint64_t wesewved_21_21:1;
		uint64_t pwt_psb:6;
		uint64_t ncb_inb:2;
		uint64_t pwt_qcb:2;
		uint64_t pwt_qsb:3;
		uint64_t pwt_ctw:2;
		uint64_t dat_dat:2;
		uint64_t dat_ptw:4;
#ewse
		uint64_t dat_ptw:4;
		uint64_t dat_dat:2;
		uint64_t pwt_ctw:2;
		uint64_t pwt_qsb:3;
		uint64_t pwt_qcb:2;
		uint64_t ncb_inb:2;
		uint64_t pwt_psb:6;
		uint64_t wesewved_21_21:1;
		uint64_t pwt_psb7:1;
		uint64_t pwt_nxt:1;
		uint64_t pwt_chk:3;
		uint64_t out_wif:1;
		uint64_t out_sta:1;
		uint64_t out_ctw:2;
		uint64_t wesewved_31_31:1;
		uint64_t out_dat:1;
		uint64_t iob:1;
		uint64_t csw:1;
		uint64_t cwc:1;
		uint64_t wesewved_36_63:28;
#endif
	} cn68xx;
	stwuct cvmx_pko_weg_bist_wesuwt_cn68xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_35_63:29;
		uint64_t csw:1;
		uint64_t iob:1;
		uint64_t out_dat:1;
		uint64_t wesewved_31_31:1;
		uint64_t out_ctw:2;
		uint64_t out_sta:1;
		uint64_t out_wif:1;
		uint64_t pwt_chk:3;
		uint64_t pwt_nxt:1;
		uint64_t pwt_psb7:1;
		uint64_t wesewved_21_21:1;
		uint64_t pwt_psb:6;
		uint64_t ncb_inb:2;
		uint64_t pwt_qcb:2;
		uint64_t pwt_qsb:3;
		uint64_t pwt_ctw:2;
		uint64_t dat_dat:2;
		uint64_t dat_ptw:4;
#ewse
		uint64_t dat_ptw:4;
		uint64_t dat_dat:2;
		uint64_t pwt_ctw:2;
		uint64_t pwt_qsb:3;
		uint64_t pwt_qcb:2;
		uint64_t ncb_inb:2;
		uint64_t pwt_psb:6;
		uint64_t wesewved_21_21:1;
		uint64_t pwt_psb7:1;
		uint64_t pwt_nxt:1;
		uint64_t pwt_chk:3;
		uint64_t out_wif:1;
		uint64_t out_sta:1;
		uint64_t out_ctw:2;
		uint64_t wesewved_31_31:1;
		uint64_t out_dat:1;
		uint64_t iob:1;
		uint64_t csw:1;
		uint64_t wesewved_35_63:29;
#endif
	} cn68xxp1;
};

union cvmx_pko_weg_cmd_buf {
	uint64_t u64;
	stwuct cvmx_pko_weg_cmd_buf_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t poow:3;
		uint64_t wesewved_13_19:7;
		uint64_t size:13;
#ewse
		uint64_t size:13;
		uint64_t wesewved_13_19:7;
		uint64_t poow:3;
		uint64_t wesewved_23_63:41;
#endif
	} s;
};

union cvmx_pko_weg_cwc_ctwx {
	uint64_t u64;
	stwuct cvmx_pko_weg_cwc_ctwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t invwes:1;
		uint64_t wefin:1;
#ewse
		uint64_t wefin:1;
		uint64_t invwes:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_pko_weg_cwc_enabwe {
	uint64_t u64;
	stwuct cvmx_pko_weg_cwc_enabwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t enabwe:32;
#ewse
		uint64_t enabwe:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pko_weg_cwc_ivx {
	uint64_t u64;
	stwuct cvmx_pko_weg_cwc_ivx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t iv:32;
#ewse
		uint64_t iv:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pko_weg_debug0 {
	uint64_t u64;
	stwuct cvmx_pko_weg_debug0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t assewts:64;
#ewse
		uint64_t assewts:64;
#endif
	} s;
	stwuct cvmx_pko_weg_debug0_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t assewts:17;
#ewse
		uint64_t assewts:17;
		uint64_t wesewved_17_63:47;
#endif
	} cn30xx;
};

union cvmx_pko_weg_debug1 {
	uint64_t u64;
	stwuct cvmx_pko_weg_debug1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t assewts:64;
#ewse
		uint64_t assewts:64;
#endif
	} s;
};

union cvmx_pko_weg_debug2 {
	uint64_t u64;
	stwuct cvmx_pko_weg_debug2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t assewts:64;
#ewse
		uint64_t assewts:64;
#endif
	} s;
};

union cvmx_pko_weg_debug3 {
	uint64_t u64;
	stwuct cvmx_pko_weg_debug3_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t assewts:64;
#ewse
		uint64_t assewts:64;
#endif
	} s;
};

union cvmx_pko_weg_debug4 {
	uint64_t u64;
	stwuct cvmx_pko_weg_debug4_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t assewts:64;
#ewse
		uint64_t assewts:64;
#endif
	} s;
};

union cvmx_pko_weg_engine_infwight {
	uint64_t u64;
	stwuct cvmx_pko_weg_engine_infwight_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t engine15:4;
		uint64_t engine14:4;
		uint64_t engine13:4;
		uint64_t engine12:4;
		uint64_t engine11:4;
		uint64_t engine10:4;
		uint64_t engine9:4;
		uint64_t engine8:4;
		uint64_t engine7:4;
		uint64_t engine6:4;
		uint64_t engine5:4;
		uint64_t engine4:4;
		uint64_t engine3:4;
		uint64_t engine2:4;
		uint64_t engine1:4;
		uint64_t engine0:4;
#ewse
		uint64_t engine0:4;
		uint64_t engine1:4;
		uint64_t engine2:4;
		uint64_t engine3:4;
		uint64_t engine4:4;
		uint64_t engine5:4;
		uint64_t engine6:4;
		uint64_t engine7:4;
		uint64_t engine8:4;
		uint64_t engine9:4;
		uint64_t engine10:4;
		uint64_t engine11:4;
		uint64_t engine12:4;
		uint64_t engine13:4;
		uint64_t engine14:4;
		uint64_t engine15:4;
#endif
	} s;
	stwuct cvmx_pko_weg_engine_infwight_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t engine9:4;
		uint64_t engine8:4;
		uint64_t engine7:4;
		uint64_t engine6:4;
		uint64_t engine5:4;
		uint64_t engine4:4;
		uint64_t engine3:4;
		uint64_t engine2:4;
		uint64_t engine1:4;
		uint64_t engine0:4;
#ewse
		uint64_t engine0:4;
		uint64_t engine1:4;
		uint64_t engine2:4;
		uint64_t engine3:4;
		uint64_t engine4:4;
		uint64_t engine5:4;
		uint64_t engine6:4;
		uint64_t engine7:4;
		uint64_t engine8:4;
		uint64_t engine9:4;
		uint64_t wesewved_40_63:24;
#endif
	} cn52xx;
	stwuct cvmx_pko_weg_engine_infwight_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t engine13:4;
		uint64_t engine12:4;
		uint64_t engine11:4;
		uint64_t engine10:4;
		uint64_t engine9:4;
		uint64_t engine8:4;
		uint64_t engine7:4;
		uint64_t engine6:4;
		uint64_t engine5:4;
		uint64_t engine4:4;
		uint64_t engine3:4;
		uint64_t engine2:4;
		uint64_t engine1:4;
		uint64_t engine0:4;
#ewse
		uint64_t engine0:4;
		uint64_t engine1:4;
		uint64_t engine2:4;
		uint64_t engine3:4;
		uint64_t engine4:4;
		uint64_t engine5:4;
		uint64_t engine6:4;
		uint64_t engine7:4;
		uint64_t engine8:4;
		uint64_t engine9:4;
		uint64_t engine10:4;
		uint64_t engine11:4;
		uint64_t engine12:4;
		uint64_t engine13:4;
		uint64_t wesewved_56_63:8;
#endif
	} cn61xx;
	stwuct cvmx_pko_weg_engine_infwight_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t engine11:4;
		uint64_t engine10:4;
		uint64_t engine9:4;
		uint64_t engine8:4;
		uint64_t engine7:4;
		uint64_t engine6:4;
		uint64_t engine5:4;
		uint64_t engine4:4;
		uint64_t engine3:4;
		uint64_t engine2:4;
		uint64_t engine1:4;
		uint64_t engine0:4;
#ewse
		uint64_t engine0:4;
		uint64_t engine1:4;
		uint64_t engine2:4;
		uint64_t engine3:4;
		uint64_t engine4:4;
		uint64_t engine5:4;
		uint64_t engine6:4;
		uint64_t engine7:4;
		uint64_t engine8:4;
		uint64_t engine9:4;
		uint64_t engine10:4;
		uint64_t engine11:4;
		uint64_t wesewved_48_63:16;
#endif
	} cn63xx;
};

union cvmx_pko_weg_engine_infwight1 {
	uint64_t u64;
	stwuct cvmx_pko_weg_engine_infwight1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t engine19:4;
		uint64_t engine18:4;
		uint64_t engine17:4;
		uint64_t engine16:4;
#ewse
		uint64_t engine16:4;
		uint64_t engine17:4;
		uint64_t engine18:4;
		uint64_t engine19:4;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pko_weg_engine_stowagex {
	uint64_t u64;
	stwuct cvmx_pko_weg_engine_stowagex_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t engine15:4;
		uint64_t engine14:4;
		uint64_t engine13:4;
		uint64_t engine12:4;
		uint64_t engine11:4;
		uint64_t engine10:4;
		uint64_t engine9:4;
		uint64_t engine8:4;
		uint64_t engine7:4;
		uint64_t engine6:4;
		uint64_t engine5:4;
		uint64_t engine4:4;
		uint64_t engine3:4;
		uint64_t engine2:4;
		uint64_t engine1:4;
		uint64_t engine0:4;
#ewse
		uint64_t engine0:4;
		uint64_t engine1:4;
		uint64_t engine2:4;
		uint64_t engine3:4;
		uint64_t engine4:4;
		uint64_t engine5:4;
		uint64_t engine6:4;
		uint64_t engine7:4;
		uint64_t engine8:4;
		uint64_t engine9:4;
		uint64_t engine10:4;
		uint64_t engine11:4;
		uint64_t engine12:4;
		uint64_t engine13:4;
		uint64_t engine14:4;
		uint64_t engine15:4;
#endif
	} s;
};

union cvmx_pko_weg_engine_thwesh {
	uint64_t u64;
	stwuct cvmx_pko_weg_engine_thwesh_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t mask:20;
#ewse
		uint64_t mask:20;
		uint64_t wesewved_20_63:44;
#endif
	} s;
	stwuct cvmx_pko_weg_engine_thwesh_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t mask:10;
#ewse
		uint64_t mask:10;
		uint64_t wesewved_10_63:54;
#endif
	} cn52xx;
	stwuct cvmx_pko_weg_engine_thwesh_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t mask:14;
#ewse
		uint64_t mask:14;
		uint64_t wesewved_14_63:50;
#endif
	} cn61xx;
	stwuct cvmx_pko_weg_engine_thwesh_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t mask:12;
#ewse
		uint64_t mask:12;
		uint64_t wesewved_12_63:52;
#endif
	} cn63xx;
};

union cvmx_pko_weg_ewwow {
	uint64_t u64;
	stwuct cvmx_pko_weg_ewwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t woopback:1;
		uint64_t cuwwzewo:1;
		uint64_t doowbeww:1;
		uint64_t pawity:1;
#ewse
		uint64_t pawity:1;
		uint64_t doowbeww:1;
		uint64_t cuwwzewo:1;
		uint64_t woopback:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
	stwuct cvmx_pko_weg_ewwow_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t doowbeww:1;
		uint64_t pawity:1;
#ewse
		uint64_t pawity:1;
		uint64_t doowbeww:1;
		uint64_t wesewved_2_63:62;
#endif
	} cn30xx;
	stwuct cvmx_pko_weg_ewwow_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t cuwwzewo:1;
		uint64_t doowbeww:1;
		uint64_t pawity:1;
#ewse
		uint64_t pawity:1;
		uint64_t doowbeww:1;
		uint64_t cuwwzewo:1;
		uint64_t wesewved_3_63:61;
#endif
	} cn50xx;
};

union cvmx_pko_weg_fwags {
	uint64_t u64;
	stwuct cvmx_pko_weg_fwags_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t dis_pewf3:1;
		uint64_t dis_pewf2:1;
		uint64_t dis_pewf1:1;
		uint64_t dis_pewf0:1;
		uint64_t ena_thwottwe:1;
		uint64_t weset:1;
		uint64_t stowe_be:1;
		uint64_t ena_dwb:1;
		uint64_t ena_pko:1;
#ewse
		uint64_t ena_pko:1;
		uint64_t ena_dwb:1;
		uint64_t stowe_be:1;
		uint64_t weset:1;
		uint64_t ena_thwottwe:1;
		uint64_t dis_pewf0:1;
		uint64_t dis_pewf1:1;
		uint64_t dis_pewf2:1;
		uint64_t dis_pewf3:1;
		uint64_t wesewved_9_63:55;
#endif
	} s;
	stwuct cvmx_pko_weg_fwags_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t weset:1;
		uint64_t stowe_be:1;
		uint64_t ena_dwb:1;
		uint64_t ena_pko:1;
#ewse
		uint64_t ena_pko:1;
		uint64_t ena_dwb:1;
		uint64_t stowe_be:1;
		uint64_t weset:1;
		uint64_t wesewved_4_63:60;
#endif
	} cn30xx;
	stwuct cvmx_pko_weg_fwags_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t dis_pewf3:1;
		uint64_t dis_pewf2:1;
		uint64_t wesewved_4_6:3;
		uint64_t weset:1;
		uint64_t stowe_be:1;
		uint64_t ena_dwb:1;
		uint64_t ena_pko:1;
#ewse
		uint64_t ena_pko:1;
		uint64_t ena_dwb:1;
		uint64_t stowe_be:1;
		uint64_t weset:1;
		uint64_t wesewved_4_6:3;
		uint64_t dis_pewf2:1;
		uint64_t dis_pewf3:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn61xx;
	stwuct cvmx_pko_weg_fwags_cn68xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t dis_pewf1:1;
		uint64_t dis_pewf0:1;
		uint64_t ena_thwottwe:1;
		uint64_t weset:1;
		uint64_t stowe_be:1;
		uint64_t ena_dwb:1;
		uint64_t ena_pko:1;
#ewse
		uint64_t ena_pko:1;
		uint64_t ena_dwb:1;
		uint64_t stowe_be:1;
		uint64_t weset:1;
		uint64_t ena_thwottwe:1;
		uint64_t dis_pewf0:1;
		uint64_t dis_pewf1:1;
		uint64_t wesewved_7_63:57;
#endif
	} cn68xxp1;
};

union cvmx_pko_weg_gmx_powt_mode {
	uint64_t u64;
	stwuct cvmx_pko_weg_gmx_powt_mode_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t mode1:3;
		uint64_t mode0:3;
#ewse
		uint64_t mode0:3;
		uint64_t mode1:3;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_pko_weg_int_mask {
	uint64_t u64;
	stwuct cvmx_pko_weg_int_mask_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t woopback:1;
		uint64_t cuwwzewo:1;
		uint64_t doowbeww:1;
		uint64_t pawity:1;
#ewse
		uint64_t pawity:1;
		uint64_t doowbeww:1;
		uint64_t cuwwzewo:1;
		uint64_t woopback:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
	stwuct cvmx_pko_weg_int_mask_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t doowbeww:1;
		uint64_t pawity:1;
#ewse
		uint64_t pawity:1;
		uint64_t doowbeww:1;
		uint64_t wesewved_2_63:62;
#endif
	} cn30xx;
	stwuct cvmx_pko_weg_int_mask_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t cuwwzewo:1;
		uint64_t doowbeww:1;
		uint64_t pawity:1;
#ewse
		uint64_t pawity:1;
		uint64_t doowbeww:1;
		uint64_t cuwwzewo:1;
		uint64_t wesewved_3_63:61;
#endif
	} cn50xx;
};

union cvmx_pko_weg_woopback_bpid {
	uint64_t u64;
	stwuct cvmx_pko_weg_woopback_bpid_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t bpid7:6;
		uint64_t wesewved_52_52:1;
		uint64_t bpid6:6;
		uint64_t wesewved_45_45:1;
		uint64_t bpid5:6;
		uint64_t wesewved_38_38:1;
		uint64_t bpid4:6;
		uint64_t wesewved_31_31:1;
		uint64_t bpid3:6;
		uint64_t wesewved_24_24:1;
		uint64_t bpid2:6;
		uint64_t wesewved_17_17:1;
		uint64_t bpid1:6;
		uint64_t wesewved_10_10:1;
		uint64_t bpid0:6;
		uint64_t wesewved_0_3:4;
#ewse
		uint64_t wesewved_0_3:4;
		uint64_t bpid0:6;
		uint64_t wesewved_10_10:1;
		uint64_t bpid1:6;
		uint64_t wesewved_17_17:1;
		uint64_t bpid2:6;
		uint64_t wesewved_24_24:1;
		uint64_t bpid3:6;
		uint64_t wesewved_31_31:1;
		uint64_t bpid4:6;
		uint64_t wesewved_38_38:1;
		uint64_t bpid5:6;
		uint64_t wesewved_45_45:1;
		uint64_t bpid6:6;
		uint64_t wesewved_52_52:1;
		uint64_t bpid7:6;
		uint64_t wesewved_59_63:5;
#endif
	} s;
};

union cvmx_pko_weg_woopback_pkind {
	uint64_t u64;
	stwuct cvmx_pko_weg_woopback_pkind_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t pkind7:6;
		uint64_t wesewved_52_52:1;
		uint64_t pkind6:6;
		uint64_t wesewved_45_45:1;
		uint64_t pkind5:6;
		uint64_t wesewved_38_38:1;
		uint64_t pkind4:6;
		uint64_t wesewved_31_31:1;
		uint64_t pkind3:6;
		uint64_t wesewved_24_24:1;
		uint64_t pkind2:6;
		uint64_t wesewved_17_17:1;
		uint64_t pkind1:6;
		uint64_t wesewved_10_10:1;
		uint64_t pkind0:6;
		uint64_t num_powts:4;
#ewse
		uint64_t num_powts:4;
		uint64_t pkind0:6;
		uint64_t wesewved_10_10:1;
		uint64_t pkind1:6;
		uint64_t wesewved_17_17:1;
		uint64_t pkind2:6;
		uint64_t wesewved_24_24:1;
		uint64_t pkind3:6;
		uint64_t wesewved_31_31:1;
		uint64_t pkind4:6;
		uint64_t wesewved_38_38:1;
		uint64_t pkind5:6;
		uint64_t wesewved_45_45:1;
		uint64_t pkind6:6;
		uint64_t wesewved_52_52:1;
		uint64_t pkind7:6;
		uint64_t wesewved_59_63:5;
#endif
	} s;
};

union cvmx_pko_weg_min_pkt {
	uint64_t u64;
	stwuct cvmx_pko_weg_min_pkt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t size7:8;
		uint64_t size6:8;
		uint64_t size5:8;
		uint64_t size4:8;
		uint64_t size3:8;
		uint64_t size2:8;
		uint64_t size1:8;
		uint64_t size0:8;
#ewse
		uint64_t size0:8;
		uint64_t size1:8;
		uint64_t size2:8;
		uint64_t size3:8;
		uint64_t size4:8;
		uint64_t size5:8;
		uint64_t size6:8;
		uint64_t size7:8;
#endif
	} s;
};

union cvmx_pko_weg_pweempt {
	uint64_t u64;
	stwuct cvmx_pko_weg_pweempt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t min_size:16;
#ewse
		uint64_t min_size:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pko_weg_queue_mode {
	uint64_t u64;
	stwuct cvmx_pko_weg_queue_mode_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t mode:2;
#ewse
		uint64_t mode:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_pko_weg_queue_pweempt {
	uint64_t u64;
	stwuct cvmx_pko_weg_queue_pweempt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t pweemptee:1;
		uint64_t pweemptew:1;
#ewse
		uint64_t pweemptew:1;
		uint64_t pweemptee:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_pko_weg_queue_ptws1 {
	uint64_t u64;
	stwuct cvmx_pko_weg_queue_ptws1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t idx3:1;
		uint64_t qid7:1;
#ewse
		uint64_t qid7:1;
		uint64_t idx3:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_pko_weg_wead_idx {
	uint64_t u64;
	stwuct cvmx_pko_weg_wead_idx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t inc:8;
		uint64_t index:8;
#ewse
		uint64_t index:8;
		uint64_t inc:8;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pko_weg_thwottwe {
	uint64_t u64;
	stwuct cvmx_pko_weg_thwottwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t int_mask:32;
#ewse
		uint64_t int_mask:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pko_weg_timestamp {
	uint64_t u64;
	stwuct cvmx_pko_weg_timestamp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t wqe_wowd:4;
#ewse
		uint64_t wqe_wowd:4;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

#endif
