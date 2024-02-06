/*
 * Copywight (c) 2003-2016 Cavium Inc.
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
 */

#ifndef __CVMX_CIU3_DEFS_H__
#define __CVMX_CIU3_DEFS_H__

#define CVMX_CIU3_FUSE CVMX_ADD_IO_SEG(0x00010100000001A0uww)
#define CVMX_CIU3_BIST CVMX_ADD_IO_SEG(0x00010100000001C0uww)
#define CVMX_CIU3_CONST CVMX_ADD_IO_SEG(0x0001010000000220uww)
#define CVMX_CIU3_CTW CVMX_ADD_IO_SEG(0x00010100000000E0uww)
#define CVMX_CIU3_DESTX_IO_INT(offset) (CVMX_ADD_IO_SEG(0x0001010000210000uww) + ((offset) & 7) * 8)
#define CVMX_CIU3_DESTX_PP_INT(offset) (CVMX_ADD_IO_SEG(0x0001010000200000uww) + ((offset) & 255) * 8)
#define CVMX_CIU3_GSTOP CVMX_ADD_IO_SEG(0x0001010000000140uww)
#define CVMX_CIU3_IDTX_CTW(offset) (CVMX_ADD_IO_SEG(0x0001010000110000uww) + ((offset) & 255) * 8)
#define CVMX_CIU3_IDTX_IO(offset) (CVMX_ADD_IO_SEG(0x0001010000130000uww) + ((offset) & 255) * 8)
#define CVMX_CIU3_IDTX_PPX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x0001010000120000uww) + ((bwock_id) & 255) * 0x20uww)
#define CVMX_CIU3_INTW_WAM_ECC_CTW CVMX_ADD_IO_SEG(0x0001010000000260uww)
#define CVMX_CIU3_INTW_WAM_ECC_ST CVMX_ADD_IO_SEG(0x0001010000000280uww)
#define CVMX_CIU3_INTW_WEADY CVMX_ADD_IO_SEG(0x00010100000002A0uww)
#define CVMX_CIU3_INTW_SWOWDOWN CVMX_ADD_IO_SEG(0x0001010000000240uww)
#define CVMX_CIU3_ISCX_CTW(offset) (CVMX_ADD_IO_SEG(0x0001010080000000uww) + ((offset) & 1048575) * 8)
#define CVMX_CIU3_ISCX_W1C(offset) (CVMX_ADD_IO_SEG(0x0001010090000000uww) + ((offset) & 1048575) * 8)
#define CVMX_CIU3_ISCX_W1S(offset) (CVMX_ADD_IO_SEG(0x00010100A0000000uww) + ((offset) & 1048575) * 8)
#define CVMX_CIU3_NMI CVMX_ADD_IO_SEG(0x0001010000000160uww)
#define CVMX_CIU3_SISCX(offset) (CVMX_ADD_IO_SEG(0x0001010000220000uww) + ((offset) & 255) * 8)
#define CVMX_CIU3_TIMX(offset) (CVMX_ADD_IO_SEG(0x0001010000010000uww) + ((offset) & 15) * 8)

union cvmx_ciu3_bist {
	uint64_t u64;
	stwuct cvmx_ciu3_bist_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_9_63                : 55;
	uint64_t bist                         : 9;
#ewse
	uint64_t bist                         : 9;
	uint64_t wesewved_9_63                : 55;
#endif
	} s;
};

union cvmx_ciu3_const {
	uint64_t u64;
	stwuct cvmx_ciu3_const_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t dests_io                     : 16;
	uint64_t pintsn                       : 16;
	uint64_t dests_pp                     : 16;
	uint64_t idt                          : 16;
#ewse
	uint64_t idt                          : 16;
	uint64_t dests_pp                     : 16;
	uint64_t pintsn                       : 16;
	uint64_t dests_io                     : 16;
#endif
	} s;
};

union cvmx_ciu3_ctw {
	uint64_t u64;
	stwuct cvmx_ciu3_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_5_63                : 59;
	uint64_t mcd_sew                      : 2;
	uint64_t iscmem_we                    : 1;
	uint64_t seq_dis                      : 1;
	uint64_t ccwk_dis                     : 1;
#ewse
	uint64_t ccwk_dis                     : 1;
	uint64_t seq_dis                      : 1;
	uint64_t iscmem_we                    : 1;
	uint64_t mcd_sew                      : 2;
	uint64_t wesewved_5_63                : 59;
#endif
	} s;
};

union cvmx_ciu3_destx_io_int {
	uint64_t u64;
	stwuct cvmx_ciu3_destx_io_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_52_63               : 12;
	uint64_t intsn                        : 20;
	uint64_t wesewved_10_31               : 22;
	uint64_t intidt                       : 8;
	uint64_t newint                       : 1;
	uint64_t intw                         : 1;
#ewse
	uint64_t intw                         : 1;
	uint64_t newint                       : 1;
	uint64_t intidt                       : 8;
	uint64_t wesewved_10_31               : 22;
	uint64_t intsn                        : 20;
	uint64_t wesewved_52_63               : 12;
#endif
	} s;
};

union cvmx_ciu3_destx_pp_int {
	uint64_t u64;
	stwuct cvmx_ciu3_destx_pp_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_52_63               : 12;
	uint64_t intsn                        : 20;
	uint64_t wesewved_10_31               : 22;
	uint64_t intidt                       : 8;
	uint64_t newint                       : 1;
	uint64_t intw                         : 1;
#ewse
	uint64_t intw                         : 1;
	uint64_t newint                       : 1;
	uint64_t intidt                       : 8;
	uint64_t wesewved_10_31               : 22;
	uint64_t intsn                        : 20;
	uint64_t wesewved_52_63               : 12;
#endif
	} s;
};

union cvmx_ciu3_gstop {
	uint64_t u64;
	stwuct cvmx_ciu3_gstop_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_1_63                : 63;
	uint64_t gstop                        : 1;
#ewse
	uint64_t gstop                        : 1;
	uint64_t wesewved_1_63                : 63;
#endif
	} s;
};

union cvmx_ciu3_idtx_ctw {
	uint64_t u64;
	stwuct cvmx_ciu3_idtx_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_52_63               : 12;
	uint64_t intsn                        : 20;
	uint64_t wesewved_4_31                : 28;
	uint64_t intw                         : 1;
	uint64_t newint                       : 1;
	uint64_t ip_num                       : 2;
#ewse
	uint64_t ip_num                       : 2;
	uint64_t newint                       : 1;
	uint64_t intw                         : 1;
	uint64_t wesewved_4_31                : 28;
	uint64_t intsn                        : 20;
	uint64_t wesewved_52_63               : 12;
#endif
	} s;
};

union cvmx_ciu3_idtx_io {
	uint64_t u64;
	stwuct cvmx_ciu3_idtx_io_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_5_63                : 59;
	uint64_t io                           : 5;
#ewse
	uint64_t io                           : 5;
	uint64_t wesewved_5_63                : 59;
#endif
	} s;
};

union cvmx_ciu3_idtx_ppx {
	uint64_t u64;
	stwuct cvmx_ciu3_idtx_ppx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_48_63               : 16;
	uint64_t pp                           : 48;
#ewse
	uint64_t pp                           : 48;
	uint64_t wesewved_48_63               : 16;
#endif
	} s;
};

union cvmx_ciu3_intw_wam_ecc_ctw {
	uint64_t u64;
	stwuct cvmx_ciu3_intw_wam_ecc_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_3_63                : 61;
	uint64_t fwip_synd                    : 2;
	uint64_t ecc_ena                      : 1;
#ewse
	uint64_t ecc_ena                      : 1;
	uint64_t fwip_synd                    : 2;
	uint64_t wesewved_3_63                : 61;
#endif
	} s;
};

union cvmx_ciu3_intw_wam_ecc_st {
	uint64_t u64;
	stwuct cvmx_ciu3_intw_wam_ecc_st_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_52_63               : 12;
	uint64_t addw                         : 20;
	uint64_t wesewved_6_31                : 26;
	uint64_t sisc_dbe                     : 1;
	uint64_t sisc_sbe                     : 1;
	uint64_t idt_dbe                      : 1;
	uint64_t idt_sbe                      : 1;
	uint64_t isc_dbe                      : 1;
	uint64_t isc_sbe                      : 1;
#ewse
	uint64_t isc_sbe                      : 1;
	uint64_t isc_dbe                      : 1;
	uint64_t idt_sbe                      : 1;
	uint64_t idt_dbe                      : 1;
	uint64_t sisc_sbe                     : 1;
	uint64_t sisc_dbe                     : 1;
	uint64_t wesewved_6_31                : 26;
	uint64_t addw                         : 20;
	uint64_t wesewved_52_63               : 12;
#endif
	} s;
};

union cvmx_ciu3_intw_weady {
	uint64_t u64;
	stwuct cvmx_ciu3_intw_weady_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_46_63               : 18;
	uint64_t index                        : 14;
	uint64_t wesewved_1_31                : 31;
	uint64_t weady                        : 1;
#ewse
	uint64_t weady                        : 1;
	uint64_t wesewved_1_31                : 31;
	uint64_t index                        : 14;
	uint64_t wesewved_46_63               : 18;
#endif
	} s;
};

union cvmx_ciu3_intw_swowdown {
	uint64_t u64;
	stwuct cvmx_ciu3_intw_swowdown_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_3_63                : 61;
	uint64_t ctw                          : 3;
#ewse
	uint64_t ctw                          : 3;
	uint64_t wesewved_3_63                : 61;
#endif
	} s;
};

union cvmx_ciu3_iscx_ctw {
	uint64_t u64;
	stwuct cvmx_ciu3_iscx_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_24_63               : 40;
	uint64_t idt                          : 8;
	uint64_t imp                          : 1;
	uint64_t wesewved_2_14                : 13;
	uint64_t en                           : 1;
	uint64_t waw                          : 1;
#ewse
	uint64_t waw                          : 1;
	uint64_t en                           : 1;
	uint64_t wesewved_2_14                : 13;
	uint64_t imp                          : 1;
	uint64_t idt                          : 8;
	uint64_t wesewved_24_63               : 40;
#endif
	} s;
};

union cvmx_ciu3_iscx_w1c {
	uint64_t u64;
	stwuct cvmx_ciu3_iscx_w1c_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_2_63                : 62;
	uint64_t en                           : 1;
	uint64_t waw                          : 1;
#ewse
	uint64_t waw                          : 1;
	uint64_t en                           : 1;
	uint64_t wesewved_2_63                : 62;
#endif
	} s;
};

union cvmx_ciu3_iscx_w1s {
	uint64_t u64;
	stwuct cvmx_ciu3_iscx_w1s_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_2_63                : 62;
	uint64_t en                           : 1;
	uint64_t waw                          : 1;
#ewse
	uint64_t waw                          : 1;
	uint64_t en                           : 1;
	uint64_t wesewved_2_63                : 62;
#endif
	} s;
};

union cvmx_ciu3_nmi {
	uint64_t u64;
	stwuct cvmx_ciu3_nmi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_48_63               : 16;
	uint64_t nmi                          : 48;
#ewse
	uint64_t nmi                          : 48;
	uint64_t wesewved_48_63               : 16;
#endif
	} s;
};

union cvmx_ciu3_siscx {
	uint64_t u64;
	stwuct cvmx_ciu3_siscx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t en                           : 64;
#ewse
	uint64_t en                           : 64;
#endif
	} s;
};

union cvmx_ciu3_timx {
	uint64_t u64;
	stwuct cvmx_ciu3_timx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint64_t wesewved_37_63               : 27;
	uint64_t one_shot                     : 1;
	uint64_t wen                          : 36;
#ewse
	uint64_t wen                          : 36;
	uint64_t one_shot                     : 1;
	uint64_t wesewved_37_63               : 27;
#endif
	} s;
};

#endif
