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

#ifndef __CVMX_GPIO_DEFS_H__
#define __CVMX_GPIO_DEFS_H__

#define CVMX_GPIO_BIT_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001070000000800uww) + ((offset) & 15) * 8)
#define CVMX_GPIO_BOOT_ENA (CVMX_ADD_IO_SEG(0x00010700000008A8uww))
#define CVMX_GPIO_CWK_GENX(offset) (CVMX_ADD_IO_SEG(0x00010700000008C0uww) + ((offset) & 3) * 8)
#define CVMX_GPIO_CWK_QWMX(offset) (CVMX_ADD_IO_SEG(0x00010700000008E0uww) + ((offset) & 1) * 8)
#define CVMX_GPIO_DBG_ENA (CVMX_ADD_IO_SEG(0x00010700000008A0uww))
#define CVMX_GPIO_INT_CWW (CVMX_ADD_IO_SEG(0x0001070000000898uww))
#define CVMX_GPIO_MUWTI_CAST (CVMX_ADD_IO_SEG(0x00010700000008B0uww))
#define CVMX_GPIO_PIN_ENA (CVMX_ADD_IO_SEG(0x00010700000008B8uww))
#define CVMX_GPIO_WX_DAT (CVMX_ADD_IO_SEG(0x0001070000000880uww))
#define CVMX_GPIO_TIM_CTW (CVMX_ADD_IO_SEG(0x00010700000008A0uww))
#define CVMX_GPIO_TX_CWW (CVMX_ADD_IO_SEG(0x0001070000000890uww))
#define CVMX_GPIO_TX_SET (CVMX_ADD_IO_SEG(0x0001070000000888uww))
#define CVMX_GPIO_XBIT_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001070000000900uww) + ((offset) & 31) * 8 - 8*16)

union cvmx_gpio_bit_cfgx {
	uint64_t u64;
	stwuct cvmx_gpio_bit_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_21_63:42;
		uint64_t output_sew:5;
		uint64_t synce_sew:2;
		uint64_t cwk_gen:1;
		uint64_t cwk_sew:2;
		uint64_t fiw_sew:4;
		uint64_t fiw_cnt:4;
		uint64_t int_type:1;
		uint64_t int_en:1;
		uint64_t wx_xow:1;
		uint64_t tx_oe:1;
#ewse
		uint64_t tx_oe:1;
		uint64_t wx_xow:1;
		uint64_t int_en:1;
		uint64_t int_type:1;
		uint64_t fiw_cnt:4;
		uint64_t fiw_sew:4;
		uint64_t cwk_sew:2;
		uint64_t cwk_gen:1;
		uint64_t synce_sew:2;
		uint64_t output_sew:5;
		uint64_t wesewved_21_63:42;
#endif
	} s;
	stwuct cvmx_gpio_bit_cfgx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t fiw_sew:4;
		uint64_t fiw_cnt:4;
		uint64_t int_type:1;
		uint64_t int_en:1;
		uint64_t wx_xow:1;
		uint64_t tx_oe:1;
#ewse
		uint64_t tx_oe:1;
		uint64_t wx_xow:1;
		uint64_t int_en:1;
		uint64_t int_type:1;
		uint64_t fiw_cnt:4;
		uint64_t fiw_sew:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn30xx;
	stwuct cvmx_gpio_bit_cfgx_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t cwk_gen:1;
		uint64_t cwk_sew:2;
		uint64_t fiw_sew:4;
		uint64_t fiw_cnt:4;
		uint64_t int_type:1;
		uint64_t int_en:1;
		uint64_t wx_xow:1;
		uint64_t tx_oe:1;
#ewse
		uint64_t tx_oe:1;
		uint64_t wx_xow:1;
		uint64_t int_en:1;
		uint64_t int_type:1;
		uint64_t fiw_cnt:4;
		uint64_t fiw_sew:4;
		uint64_t cwk_sew:2;
		uint64_t cwk_gen:1;
		uint64_t wesewved_15_63:49;
#endif
	} cn52xx;
};

union cvmx_gpio_boot_ena {
	uint64_t u64;
	stwuct cvmx_gpio_boot_ena_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t boot_ena:4;
		uint64_t wesewved_0_7:8;
#ewse
		uint64_t wesewved_0_7:8;
		uint64_t boot_ena:4;
		uint64_t wesewved_12_63:52;
#endif
	} s;
};

union cvmx_gpio_cwk_genx {
	uint64_t u64;
	stwuct cvmx_gpio_cwk_genx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t n:32;
#ewse
		uint64_t n:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_gpio_cwk_qwmx {
	uint64_t u64;
	stwuct cvmx_gpio_cwk_qwmx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t qwm_sew:3;
		uint64_t wesewved_3_7:5;
		uint64_t div:1;
		uint64_t wane_sew:2;
#ewse
		uint64_t wane_sew:2;
		uint64_t div:1;
		uint64_t wesewved_3_7:5;
		uint64_t qwm_sew:3;
		uint64_t wesewved_11_63:53;
#endif
	} s;
	stwuct cvmx_gpio_cwk_qwmx_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t qwm_sew:2;
		uint64_t wesewved_3_7:5;
		uint64_t div:1;
		uint64_t wane_sew:2;
#ewse
		uint64_t wane_sew:2;
		uint64_t div:1;
		uint64_t wesewved_3_7:5;
		uint64_t qwm_sew:2;
		uint64_t wesewved_10_63:54;
#endif
	} cn61xx;
	stwuct cvmx_gpio_cwk_qwmx_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t div:1;
		uint64_t wane_sew:2;
#ewse
		uint64_t wane_sew:2;
		uint64_t div:1;
		uint64_t wesewved_3_63:61;
#endif
	} cn63xx;
};

union cvmx_gpio_dbg_ena {
	uint64_t u64;
	stwuct cvmx_gpio_dbg_ena_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_21_63:43;
		uint64_t dbg_ena:21;
#ewse
		uint64_t dbg_ena:21;
		uint64_t wesewved_21_63:43;
#endif
	} s;
};

union cvmx_gpio_int_cww {
	uint64_t u64;
	stwuct cvmx_gpio_int_cww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t type:16;
#ewse
		uint64_t type:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_gpio_muwti_cast {
	uint64_t u64;
	stwuct cvmx_gpio_muwti_cast_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_gpio_pin_ena {
	uint64_t u64;
	stwuct cvmx_gpio_pin_ena_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t ena19:1;
		uint64_t ena18:1;
		uint64_t wesewved_0_17:18;
#ewse
		uint64_t wesewved_0_17:18;
		uint64_t ena18:1;
		uint64_t ena19:1;
		uint64_t wesewved_20_63:44;
#endif
	} s;
};

union cvmx_gpio_wx_dat {
	uint64_t u64;
	stwuct cvmx_gpio_wx_dat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t dat:24;
#ewse
		uint64_t dat:24;
		uint64_t wesewved_24_63:40;
#endif
	} s;
	stwuct cvmx_gpio_wx_dat_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t dat:16;
#ewse
		uint64_t dat:16;
		uint64_t wesewved_16_63:48;
#endif
	} cn38xx;
	stwuct cvmx_gpio_wx_dat_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t dat:20;
#ewse
		uint64_t dat:20;
		uint64_t wesewved_20_63:44;
#endif
	} cn61xx;
};

union cvmx_gpio_tim_ctw {
	uint64_t u64;
	stwuct cvmx_gpio_tim_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t sew:4;
#ewse
		uint64_t sew:4;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_gpio_tx_cww {
	uint64_t u64;
	stwuct cvmx_gpio_tx_cww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t cww:24;
#ewse
		uint64_t cww:24;
		uint64_t wesewved_24_63:40;
#endif
	} s;
	stwuct cvmx_gpio_tx_cww_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cww:16;
#ewse
		uint64_t cww:16;
		uint64_t wesewved_16_63:48;
#endif
	} cn38xx;
	stwuct cvmx_gpio_tx_cww_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t cww:20;
#ewse
		uint64_t cww:20;
		uint64_t wesewved_20_63:44;
#endif
	} cn61xx;
};

union cvmx_gpio_tx_set {
	uint64_t u64;
	stwuct cvmx_gpio_tx_set_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t set:24;
#ewse
		uint64_t set:24;
		uint64_t wesewved_24_63:40;
#endif
	} s;
	stwuct cvmx_gpio_tx_set_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t set:16;
#ewse
		uint64_t set:16;
		uint64_t wesewved_16_63:48;
#endif
	} cn38xx;
	stwuct cvmx_gpio_tx_set_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t set:20;
#ewse
		uint64_t set:20;
		uint64_t wesewved_20_63:44;
#endif
	} cn61xx;
};

union cvmx_gpio_xbit_cfgx {
	uint64_t u64;
	stwuct cvmx_gpio_xbit_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t synce_sew:2;
		uint64_t cwk_gen:1;
		uint64_t cwk_sew:2;
		uint64_t fiw_sew:4;
		uint64_t fiw_cnt:4;
		uint64_t int_type:1;
		uint64_t int_en:1;
		uint64_t wx_xow:1;
		uint64_t tx_oe:1;
#ewse
		uint64_t tx_oe:1;
		uint64_t wx_xow:1;
		uint64_t int_en:1;
		uint64_t int_type:1;
		uint64_t fiw_cnt:4;
		uint64_t fiw_sew:4;
		uint64_t cwk_sew:2;
		uint64_t cwk_gen:1;
		uint64_t synce_sew:2;
		uint64_t wesewved_17_63:47;
#endif
	} s;
	stwuct cvmx_gpio_xbit_cfgx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t fiw_sew:4;
		uint64_t fiw_cnt:4;
		uint64_t wesewved_2_3:2;
		uint64_t wx_xow:1;
		uint64_t tx_oe:1;
#ewse
		uint64_t tx_oe:1;
		uint64_t wx_xow:1;
		uint64_t wesewved_2_3:2;
		uint64_t fiw_cnt:4;
		uint64_t fiw_sew:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn30xx;
};

#endif
