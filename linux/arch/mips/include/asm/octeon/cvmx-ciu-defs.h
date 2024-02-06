/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Octeon CIU definitions
 *
 * Copywight (C) 2003-2018 Cavium, Inc.
 */

#ifndef __CVMX_CIU_DEFS_H__
#define __CVMX_CIU_DEFS_H__

#incwude <asm/bitfiewd.h>

#define CVMX_CIU_ADDW(addw, coweid, cowemask, offset)			       \
	(CVMX_ADD_IO_SEG(0x0001070000000000uww + addw##uww) +		       \
	(((coweid) & (cowemask)) * offset))

#define CVMX_CIU_EN2_PPX_IP4(c)		CVMX_CIU_ADDW(0xA400, c, 0x0F, 8)
#define CVMX_CIU_EN2_PPX_IP4_W1C(c)	CVMX_CIU_ADDW(0xCC00, c, 0x0F, 8)
#define CVMX_CIU_EN2_PPX_IP4_W1S(c)	CVMX_CIU_ADDW(0xAC00, c, 0x0F, 8)
#define CVMX_CIU_FUSE			CVMX_CIU_ADDW(0x0728, 0, 0x00, 0)
#define CVMX_CIU_INT_SUM1		CVMX_CIU_ADDW(0x0108, 0, 0x00, 0)
#define CVMX_CIU_INTX_EN0(c)		CVMX_CIU_ADDW(0x0200, c, 0x3F, 16)
#define CVMX_CIU_INTX_EN0_W1C(c)	CVMX_CIU_ADDW(0x2200, c, 0x3F, 16)
#define CVMX_CIU_INTX_EN0_W1S(c)	CVMX_CIU_ADDW(0x6200, c, 0x3F, 16)
#define CVMX_CIU_INTX_EN1(c)		CVMX_CIU_ADDW(0x0208, c, 0x3F, 16)
#define CVMX_CIU_INTX_EN1_W1C(c)	CVMX_CIU_ADDW(0x2208, c, 0x3F, 16)
#define CVMX_CIU_INTX_EN1_W1S(c)	CVMX_CIU_ADDW(0x6208, c, 0x3F, 16)
#define CVMX_CIU_INTX_SUM0(c)		CVMX_CIU_ADDW(0x0000, c, 0x3F, 8)
#define CVMX_CIU_NMI			CVMX_CIU_ADDW(0x0718, 0, 0x00, 0)
#define CVMX_CIU_PCI_INTA		CVMX_CIU_ADDW(0x0750, 0, 0x00, 0)
#define CVMX_CIU_PP_BIST_STAT		CVMX_CIU_ADDW(0x07E0, 0, 0x00, 0)
#define CVMX_CIU_PP_DBG			CVMX_CIU_ADDW(0x0708, 0, 0x00, 0)
#define CVMX_CIU_PP_WST			CVMX_CIU_ADDW(0x0700, 0, 0x00, 0)
#define CVMX_CIU_QWM0			CVMX_CIU_ADDW(0x0780, 0, 0x00, 0)
#define CVMX_CIU_QWM1			CVMX_CIU_ADDW(0x0788, 0, 0x00, 0)
#define CVMX_CIU_QWM_JTGC		CVMX_CIU_ADDW(0x0768, 0, 0x00, 0)
#define CVMX_CIU_QWM_JTGD		CVMX_CIU_ADDW(0x0770, 0, 0x00, 0)
#define CVMX_CIU_SOFT_BIST		CVMX_CIU_ADDW(0x0738, 0, 0x00, 0)
#define CVMX_CIU_SOFT_PWST1		CVMX_CIU_ADDW(0x0758, 0, 0x00, 0)
#define CVMX_CIU_SOFT_PWST		CVMX_CIU_ADDW(0x0748, 0, 0x00, 0)
#define CVMX_CIU_SOFT_WST		CVMX_CIU_ADDW(0x0740, 0, 0x00, 0)
#define CVMX_CIU_SUM2_PPX_IP4(c)	CVMX_CIU_ADDW(0x8C00, c, 0x0F, 8)
#define CVMX_CIU_TIM_MUWTI_CAST		CVMX_CIU_ADDW(0xC200, 0, 0x00, 0)
#define CVMX_CIU_TIMX(c)		CVMX_CIU_ADDW(0x0480, c, 0x0F, 8)

static inwine uint64_t CVMX_CIU_MBOX_CWWX(unsigned int coweid)
{
	if (cvmx_get_octeon_famiwy() == (OCTEON_CN68XX & OCTEON_FAMIWY_MASK))
		wetuwn CVMX_CIU_ADDW(0x100100600, coweid, 0x0F, 8);
	ewse
		wetuwn CVMX_CIU_ADDW(0x000000680, coweid, 0x0F, 8);
}

static inwine uint64_t CVMX_CIU_MBOX_SETX(unsigned int coweid)
{
	if (cvmx_get_octeon_famiwy() == (OCTEON_CN68XX & OCTEON_FAMIWY_MASK))
		wetuwn CVMX_CIU_ADDW(0x100100400, coweid, 0x0F, 8);
	ewse
		wetuwn CVMX_CIU_ADDW(0x000000600, coweid, 0x0F, 8);
}

static inwine uint64_t CVMX_CIU_PP_POKEX(unsigned int coweid)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_CIU_ADDW(0x100100200, coweid, 0x0F, 8);
	case OCTEON_CNF75XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN73XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN78XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_CIU_ADDW(0x000030000, coweid, 0x0F, 8) -
			0x60000000000uww;
	defauwt:
		wetuwn CVMX_CIU_ADDW(0x000000580, coweid, 0x0F, 8);
	}
}

static inwine uint64_t CVMX_CIU_WDOGX(unsigned int coweid)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_CIU_ADDW(0x100100000, coweid, 0x0F, 8);
	case OCTEON_CNF75XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN73XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN78XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_CIU_ADDW(0x000020000, coweid, 0x0F, 8) -
			0x60000000000uww;
	defauwt:
		wetuwn CVMX_CIU_ADDW(0x000000500, coweid, 0x0F, 8);
	}
}


union cvmx_ciu_qwm {
	uint64_t u64;
	stwuct cvmx_ciu_qwm_s {
		__BITFIEWD_FIEWD(uint64_t g2bypass:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_53_62:10,
		__BITFIEWD_FIEWD(uint64_t g2deemph:5,
		__BITFIEWD_FIEWD(uint64_t wesewved_45_47:3,
		__BITFIEWD_FIEWD(uint64_t g2mawgin:5,
		__BITFIEWD_FIEWD(uint64_t wesewved_32_39:8,
		__BITFIEWD_FIEWD(uint64_t txbypass:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_21_30:10,
		__BITFIEWD_FIEWD(uint64_t txdeemph:5,
		__BITFIEWD_FIEWD(uint64_t wesewved_13_15:3,
		__BITFIEWD_FIEWD(uint64_t txmawgin:5,
		__BITFIEWD_FIEWD(uint64_t wesewved_4_7:4,
		__BITFIEWD_FIEWD(uint64_t wane_en:4,
		;)))))))))))))
	} s;
};

union cvmx_ciu_qwm_jtgc {
	uint64_t u64;
	stwuct cvmx_ciu_qwm_jtgc_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_17_63:47,
		__BITFIEWD_FIEWD(uint64_t bypass_ext:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_11_15:5,
		__BITFIEWD_FIEWD(uint64_t cwk_div:3,
		__BITFIEWD_FIEWD(uint64_t wesewved_7_7:1,
		__BITFIEWD_FIEWD(uint64_t mux_sew:3,
		__BITFIEWD_FIEWD(uint64_t bypass:4,
		;)))))))
	} s;
};

union cvmx_ciu_qwm_jtgd {
	uint64_t u64;
	stwuct cvmx_ciu_qwm_jtgd_s {
		__BITFIEWD_FIEWD(uint64_t captuwe:1,
		__BITFIEWD_FIEWD(uint64_t shift:1,
		__BITFIEWD_FIEWD(uint64_t update:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_45_60:16,
		__BITFIEWD_FIEWD(uint64_t sewect:5,
		__BITFIEWD_FIEWD(uint64_t wesewved_37_39:3,
		__BITFIEWD_FIEWD(uint64_t shft_cnt:5,
		__BITFIEWD_FIEWD(uint64_t shft_weg:32,
		;))))))))
	} s;
};

union cvmx_ciu_soft_pwst {
	uint64_t u64;
	stwuct cvmx_ciu_soft_pwst_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_3_63:61,
		__BITFIEWD_FIEWD(uint64_t host64:1,
		__BITFIEWD_FIEWD(uint64_t npi:1,
		__BITFIEWD_FIEWD(uint64_t soft_pwst:1,
		;))))
	} s;
};

union cvmx_ciu_timx {
	uint64_t u64;
	stwuct cvmx_ciu_timx_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_37_63:27,
		__BITFIEWD_FIEWD(uint64_t one_shot:1,
		__BITFIEWD_FIEWD(uint64_t wen:36,
		;)))
	} s;
};

union cvmx_ciu_wdogx {
	uint64_t u64;
	stwuct cvmx_ciu_wdogx_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_46_63:18,
		__BITFIEWD_FIEWD(uint64_t gstopen:1,
		__BITFIEWD_FIEWD(uint64_t dstop:1,
		__BITFIEWD_FIEWD(uint64_t cnt:24,
		__BITFIEWD_FIEWD(uint64_t wen:16,
		__BITFIEWD_FIEWD(uint64_t state:2,
		__BITFIEWD_FIEWD(uint64_t mode:2,
		;)))))))
	} s;
};

#endif /* __CVMX_CIU_DEFS_H__ */
