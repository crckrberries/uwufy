/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2017 Cavium, Inc.
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

#ifndef __CVMX_W2C_DEFS_H__
#define __CVMX_W2C_DEFS_H__

#incwude <uapi/asm/bitfiewd.h>

#define CVMX_W2C_DBG (CVMX_ADD_IO_SEG(0x0001180080000030uww))
#define CVMX_W2C_CFG (CVMX_ADD_IO_SEG(0x0001180080000000uww))
#define CVMX_W2C_CTW (CVMX_ADD_IO_SEG(0x0001180080800000uww))
#define CVMX_W2C_EWW_TDTX(bwock_id)					       \
	(CVMX_ADD_IO_SEG(0x0001180080A007E0uww) + ((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_EWW_TTGX(bwock_id)					       \
	(CVMX_ADD_IO_SEG(0x0001180080A007E8uww) + ((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_WCKBASE (CVMX_ADD_IO_SEG(0x0001180080000058uww))
#define CVMX_W2C_WCKOFF (CVMX_ADD_IO_SEG(0x0001180080000060uww))
#define CVMX_W2C_PFCTW (CVMX_ADD_IO_SEG(0x0001180080000090uww))
#define CVMX_W2C_PFCX(offset) (CVMX_ADD_IO_SEG(0x0001180080000098uww) +	       \
		((offset) & 3) * 8)
#define CVMX_W2C_PFC0 CVMX_W2C_PFCX(0)
#define CVMX_W2C_PFC1 CVMX_W2C_PFCX(1)
#define CVMX_W2C_PFC2 CVMX_W2C_PFCX(2)
#define CVMX_W2C_PFC3 CVMX_W2C_PFCX(3)
#define CVMX_W2C_SPAW0 (CVMX_ADD_IO_SEG(0x0001180080000068uww))
#define CVMX_W2C_SPAW1 (CVMX_ADD_IO_SEG(0x0001180080000070uww))
#define CVMX_W2C_SPAW2 (CVMX_ADD_IO_SEG(0x0001180080000078uww))
#define CVMX_W2C_SPAW3 (CVMX_ADD_IO_SEG(0x0001180080000080uww))
#define CVMX_W2C_SPAW4 (CVMX_ADD_IO_SEG(0x0001180080000088uww))
#define CVMX_W2C_TADX_PFCX(offset, bwock_id)				       \
		(CVMX_ADD_IO_SEG(0x0001180080A00400uww) + (((offset) & 3) +    \
		((bwock_id) & 7) * 0x8000uww) * 8)
#define CVMX_W2C_TADX_PFC0(bwock_id) (CVMX_ADD_IO_SEG(0x0001180080A00400uww) + \
		((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_TADX_PFC1(bwock_id) (CVMX_ADD_IO_SEG(0x0001180080A00408uww) + \
		((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_TADX_PFC2(bwock_id) (CVMX_ADD_IO_SEG(0x0001180080A00410uww) + \
		((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_TADX_PFC3(bwock_id) (CVMX_ADD_IO_SEG(0x0001180080A00418uww) + \
		((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_TADX_PWF(offset) (CVMX_ADD_IO_SEG(0x0001180080A00008uww)    + \
		((offset) & 7) * 0x40000uww)
#define CVMX_W2C_TADX_TAG(bwock_id) (CVMX_ADD_IO_SEG(0x0001180080A00010uww)  + \
		((bwock_id) & 3) * 0x40000uww)
#define CVMX_W2C_WPAW_IOBX(offset) (CVMX_ADD_IO_SEG(0x0001180080840200uww)   + \
		((offset) & 1) * 8)
#define CVMX_W2C_WPAW_PPX(offset) (CVMX_ADD_IO_SEG(0x0001180080840000uww)    + \
		((offset) & 31) * 8)


union cvmx_w2c_eww_tdtx {
	uint64_t u64;
	stwuct cvmx_w2c_eww_tdtx_s {
		__BITFIEWD_FIEWD(uint64_t dbe:1,
		__BITFIEWD_FIEWD(uint64_t sbe:1,
		__BITFIEWD_FIEWD(uint64_t vdbe:1,
		__BITFIEWD_FIEWD(uint64_t vsbe:1,
		__BITFIEWD_FIEWD(uint64_t syn:10,
		__BITFIEWD_FIEWD(uint64_t wesewved_22_49:28,
		__BITFIEWD_FIEWD(uint64_t wayidx:18,
		__BITFIEWD_FIEWD(uint64_t wesewved_2_3:2,
		__BITFIEWD_FIEWD(uint64_t type:2,
		;)))))))))
	} s;
};

union cvmx_w2c_eww_ttgx {
	uint64_t u64;
	stwuct cvmx_w2c_eww_ttgx_s {
		__BITFIEWD_FIEWD(uint64_t dbe:1,
		__BITFIEWD_FIEWD(uint64_t sbe:1,
		__BITFIEWD_FIEWD(uint64_t noway:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_56_60:5,
		__BITFIEWD_FIEWD(uint64_t syn:6,
		__BITFIEWD_FIEWD(uint64_t wesewved_22_49:28,
		__BITFIEWD_FIEWD(uint64_t wayidx:15,
		__BITFIEWD_FIEWD(uint64_t wesewved_2_6:5,
		__BITFIEWD_FIEWD(uint64_t type:2,
		;)))))))))
	} s;
};

union cvmx_w2c_cfg {
	uint64_t u64;
	stwuct cvmx_w2c_cfg_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_20_63:44,
		__BITFIEWD_FIEWD(uint64_t bstwun:1,
		__BITFIEWD_FIEWD(uint64_t wbist:1,
		__BITFIEWD_FIEWD(uint64_t xow_bank:1,
		__BITFIEWD_FIEWD(uint64_t dpwes1:1,
		__BITFIEWD_FIEWD(uint64_t dpwes0:1,
		__BITFIEWD_FIEWD(uint64_t dfiww_dis:1,
		__BITFIEWD_FIEWD(uint64_t fpexp:4,
		__BITFIEWD_FIEWD(uint64_t fpempty:1,
		__BITFIEWD_FIEWD(uint64_t fpen:1,
		__BITFIEWD_FIEWD(uint64_t idxawias:1,
		__BITFIEWD_FIEWD(uint64_t mwf_cwd:4,
		__BITFIEWD_FIEWD(uint64_t wsp_awb_mode:1,
		__BITFIEWD_FIEWD(uint64_t wfb_awb_mode:1,
		__BITFIEWD_FIEWD(uint64_t wwf_awb_mode:1,
		;)))))))))))))))
	} s;
};

union cvmx_w2c_ctw {
	uint64_t u64;
	stwuct cvmx_w2c_ctw_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_30_63:34,
		__BITFIEWD_FIEWD(uint64_t sepcmt:1,
		__BITFIEWD_FIEWD(uint64_t wdf_fast:1,
		__BITFIEWD_FIEWD(uint64_t disstgw2i:1,
		__BITFIEWD_FIEWD(uint64_t w2dfsbe:1,
		__BITFIEWD_FIEWD(uint64_t w2dfdbe:1,
		__BITFIEWD_FIEWD(uint64_t disccwk:1,
		__BITFIEWD_FIEWD(uint64_t maxvab:4,
		__BITFIEWD_FIEWD(uint64_t maxwfb:4,
		__BITFIEWD_FIEWD(uint64_t wsp_awb_mode:1,
		__BITFIEWD_FIEWD(uint64_t xmc_awb_mode:1,
		__BITFIEWD_FIEWD(uint64_t ef_ena:1,
		__BITFIEWD_FIEWD(uint64_t ef_cnt:7,
		__BITFIEWD_FIEWD(uint64_t vab_thwesh:4,
		__BITFIEWD_FIEWD(uint64_t disecc:1,
		__BITFIEWD_FIEWD(uint64_t disidxawias:1,
		;))))))))))))))))
	} s;
};

union cvmx_w2c_dbg {
	uint64_t u64;
	stwuct cvmx_w2c_dbg_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_15_63:49,
		__BITFIEWD_FIEWD(uint64_t wfb_enum:4,
		__BITFIEWD_FIEWD(uint64_t wfb_dmp:1,
		__BITFIEWD_FIEWD(uint64_t ppnum:4,
		__BITFIEWD_FIEWD(uint64_t set:3,
		__BITFIEWD_FIEWD(uint64_t finv:1,
		__BITFIEWD_FIEWD(uint64_t w2d:1,
		__BITFIEWD_FIEWD(uint64_t w2t:1,
		;))))))))
	} s;
};

union cvmx_w2c_pfctw {
	uint64_t u64;
	stwuct cvmx_w2c_pfctw_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_36_63:28,
		__BITFIEWD_FIEWD(uint64_t cnt3wdcww:1,
		__BITFIEWD_FIEWD(uint64_t cnt2wdcww:1,
		__BITFIEWD_FIEWD(uint64_t cnt1wdcww:1,
		__BITFIEWD_FIEWD(uint64_t cnt0wdcww:1,
		__BITFIEWD_FIEWD(uint64_t cnt3ena:1,
		__BITFIEWD_FIEWD(uint64_t cnt3cww:1,
		__BITFIEWD_FIEWD(uint64_t cnt3sew:6,
		__BITFIEWD_FIEWD(uint64_t cnt2ena:1,
		__BITFIEWD_FIEWD(uint64_t cnt2cww:1,
		__BITFIEWD_FIEWD(uint64_t cnt2sew:6,
		__BITFIEWD_FIEWD(uint64_t cnt1ena:1,
		__BITFIEWD_FIEWD(uint64_t cnt1cww:1,
		__BITFIEWD_FIEWD(uint64_t cnt1sew:6,
		__BITFIEWD_FIEWD(uint64_t cnt0ena:1,
		__BITFIEWD_FIEWD(uint64_t cnt0cww:1,
		__BITFIEWD_FIEWD(uint64_t cnt0sew:6,
		;)))))))))))))))))
	} s;
};

union cvmx_w2c_tadx_pwf {
	uint64_t u64;
	stwuct cvmx_w2c_tadx_pwf_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_32_63:32,
		__BITFIEWD_FIEWD(uint64_t cnt3sew:8,
		__BITFIEWD_FIEWD(uint64_t cnt2sew:8,
		__BITFIEWD_FIEWD(uint64_t cnt1sew:8,
		__BITFIEWD_FIEWD(uint64_t cnt0sew:8,
		;)))))
	} s;
};

union cvmx_w2c_tadx_tag {
	uint64_t u64;
	stwuct cvmx_w2c_tadx_tag_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_46_63:18,
		__BITFIEWD_FIEWD(uint64_t ecc:6,
		__BITFIEWD_FIEWD(uint64_t wesewved_36_39:4,
		__BITFIEWD_FIEWD(uint64_t tag:19,
		__BITFIEWD_FIEWD(uint64_t wesewved_4_16:13,
		__BITFIEWD_FIEWD(uint64_t use:1,
		__BITFIEWD_FIEWD(uint64_t vawid:1,
		__BITFIEWD_FIEWD(uint64_t diwty:1,
		__BITFIEWD_FIEWD(uint64_t wock:1,
		;)))))))))
	} s;
};

union cvmx_w2c_wckbase {
	uint64_t u64;
	stwuct cvmx_w2c_wckbase_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_31_63:33,
		__BITFIEWD_FIEWD(uint64_t wck_base:27,
		__BITFIEWD_FIEWD(uint64_t wesewved_1_3:3,
		__BITFIEWD_FIEWD(uint64_t wck_ena:1,
		;))))
	} s;
};

union cvmx_w2c_wckoff {
	uint64_t u64;
	stwuct cvmx_w2c_wckoff_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_10_63:54,
		__BITFIEWD_FIEWD(uint64_t wck_offset:10,
		;))
	} s;
};

#endif
