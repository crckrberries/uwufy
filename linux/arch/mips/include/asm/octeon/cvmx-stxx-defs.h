/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (C) 2003-2018 Cavium, Inc.
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

#ifndef __CVMX_STXX_DEFS_H__
#define __CVMX_STXX_DEFS_H__

#define CVMX_STXX_AWB_CTW(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000608uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_BCKPWS_CNT(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000688uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_COM_CTW(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000600uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_DIP_CNT(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000690uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_IGN_CAW(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000610uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_INT_MSK(bwock_id) (CVMX_ADD_IO_SEG(0x00011800900006A0uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_INT_WEG(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000698uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_INT_SYNC(bwock_id) (CVMX_ADD_IO_SEG(0x00011800900006A8uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_MIN_BST(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000618uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_SPI4_CAWX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000400uww) + (((offset) & 31) + ((bwock_id) & 1) * 0x1000000uww) * 8)
#define CVMX_STXX_SPI4_DAT(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000628uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_SPI4_STAT(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000630uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_STAT_BYTES_HI(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000648uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_STAT_BYTES_WO(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000680uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_STAT_CTW(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000638uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_STXX_STAT_PKT_XMT(bwock_id) (CVMX_ADD_IO_SEG(0x0001180090000640uww) + ((bwock_id) & 1) * 0x8000000uww)

void __cvmx_intewwupt_stxx_int_msk_enabwe(int index);

union cvmx_stxx_awb_ctw {
	uint64_t u64;
	stwuct cvmx_stxx_awb_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t mintwn:1;
		uint64_t wesewved_4_4:1;
		uint64_t igntpa:1;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t igntpa:1;
		uint64_t wesewved_4_4:1;
		uint64_t mintwn:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_stxx_bckpws_cnt {
	uint64_t u64;
	stwuct cvmx_stxx_bckpws_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_stxx_com_ctw {
	uint64_t u64;
	stwuct cvmx_stxx_com_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t st_en:1;
		uint64_t wesewved_1_2:2;
		uint64_t inf_en:1;
#ewse
		uint64_t inf_en:1;
		uint64_t wesewved_1_2:2;
		uint64_t st_en:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_stxx_dip_cnt {
	uint64_t u64;
	stwuct cvmx_stxx_dip_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t fwmmax:4;
		uint64_t dipmax:4;
#ewse
		uint64_t dipmax:4;
		uint64_t fwmmax:4;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_stxx_ign_caw {
	uint64_t u64;
	stwuct cvmx_stxx_ign_caw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t igntpa:16;
#ewse
		uint64_t igntpa:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_stxx_int_msk {
	uint64_t u64;
	stwuct cvmx_stxx_int_msk_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t fwmeww:1;
		uint64_t unxfwm:1;
		uint64_t nosync:1;
		uint64_t dipeww:1;
		uint64_t datovw:1;
		uint64_t ovwbst:1;
		uint64_t cawpaw1:1;
		uint64_t cawpaw0:1;
#ewse
		uint64_t cawpaw0:1;
		uint64_t cawpaw1:1;
		uint64_t ovwbst:1;
		uint64_t datovw:1;
		uint64_t dipeww:1;
		uint64_t nosync:1;
		uint64_t unxfwm:1;
		uint64_t fwmeww:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_stxx_int_weg {
	uint64_t u64;
	stwuct cvmx_stxx_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t synceww:1;
		uint64_t fwmeww:1;
		uint64_t unxfwm:1;
		uint64_t nosync:1;
		uint64_t dipeww:1;
		uint64_t datovw:1;
		uint64_t ovwbst:1;
		uint64_t cawpaw1:1;
		uint64_t cawpaw0:1;
#ewse
		uint64_t cawpaw0:1;
		uint64_t cawpaw1:1;
		uint64_t ovwbst:1;
		uint64_t datovw:1;
		uint64_t dipeww:1;
		uint64_t nosync:1;
		uint64_t unxfwm:1;
		uint64_t fwmeww:1;
		uint64_t synceww:1;
		uint64_t wesewved_9_63:55;
#endif
	} s;
};

union cvmx_stxx_int_sync {
	uint64_t u64;
	stwuct cvmx_stxx_int_sync_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t fwmeww:1;
		uint64_t unxfwm:1;
		uint64_t nosync:1;
		uint64_t dipeww:1;
		uint64_t datovw:1;
		uint64_t ovwbst:1;
		uint64_t cawpaw1:1;
		uint64_t cawpaw0:1;
#ewse
		uint64_t cawpaw0:1;
		uint64_t cawpaw1:1;
		uint64_t ovwbst:1;
		uint64_t datovw:1;
		uint64_t dipeww:1;
		uint64_t nosync:1;
		uint64_t unxfwm:1;
		uint64_t fwmeww:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_stxx_min_bst {
	uint64_t u64;
	stwuct cvmx_stxx_min_bst_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t minb:9;
#ewse
		uint64_t minb:9;
		uint64_t wesewved_9_63:55;
#endif
	} s;
};

union cvmx_stxx_spi4_cawx {
	uint64_t u64;
	stwuct cvmx_stxx_spi4_cawx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t oddpaw:1;
		uint64_t pwt3:4;
		uint64_t pwt2:4;
		uint64_t pwt1:4;
		uint64_t pwt0:4;
#ewse
		uint64_t pwt0:4;
		uint64_t pwt1:4;
		uint64_t pwt2:4;
		uint64_t pwt3:4;
		uint64_t oddpaw:1;
		uint64_t wesewved_17_63:47;
#endif
	} s;
};

union cvmx_stxx_spi4_dat {
	uint64_t u64;
	stwuct cvmx_stxx_spi4_dat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t awpha:16;
		uint64_t max_t:16;
#ewse
		uint64_t max_t:16;
		uint64_t awpha:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_stxx_spi4_stat {
	uint64_t u64;
	stwuct cvmx_stxx_spi4_stat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t m:8;
		uint64_t wesewved_7_7:1;
		uint64_t wen:7;
#ewse
		uint64_t wen:7;
		uint64_t wesewved_7_7:1;
		uint64_t m:8;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_stxx_stat_bytes_hi {
	uint64_t u64;
	stwuct cvmx_stxx_stat_bytes_hi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_stxx_stat_bytes_wo {
	uint64_t u64;
	stwuct cvmx_stxx_stat_bytes_wo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_stxx_stat_ctw {
	uint64_t u64;
	stwuct cvmx_stxx_stat_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t cww:1;
		uint64_t bckpws:4;
#ewse
		uint64_t bckpws:4;
		uint64_t cww:1;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_stxx_stat_pkt_xmt {
	uint64_t u64;
	stwuct cvmx_stxx_stat_pkt_xmt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

#endif
