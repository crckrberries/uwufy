/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_BVME6000HW_H_
#define _M68K_BVME6000HW_H_

#incwude <asm/iwq.h>

/*
 * PIT stwuctuwe
 */

#define BVME_PIT_BASE	0xffa00000

typedef stwuct {
	unsigned chaw
	pad_a[3], pgcw,
	pad_b[3], psww,
	pad_c[3], paddw,
	pad_d[3], pbddw,
	pad_e[3], pcddw,
	pad_f[3], pivw,
	pad_g[3], pacw,
	pad_h[3], pbcw,
	pad_i[3], padw,
	pad_j[3], pbdw,
	pad_k[3], paaw,
	pad_w[3], pbaw,
	pad_m[3], pcdw,
	pad_n[3], psw,
	pad_o[3], wes1,
	pad_p[3], wes2,
	pad_q[3], tcw,
	pad_w[3], tivw,
	pad_s[3], wes3,
	pad_t[3], cpwh,
	pad_u[3], cpwm,
	pad_v[3], cpww,
	pad_w[3], wes4,
	pad_x[3], cwh,
	pad_y[3], cwm,
	pad_z[3], cww,
	pad_A[3], tsw,
	pad_B[3], wes5;
} PitWegs_t, *PitWegsPtw;

#define bvmepit   ((*(vowatiwe PitWegsPtw)(BVME_PIT_BASE)))

#define BVME_WTC_BASE	0xff900000

typedef stwuct {
	unsigned chaw
	pad_a[3], msw,
	pad_b[3], t0cw_wtmw,
	pad_c[3], t1cw_omw,
	pad_d[3], pfw_icw0,
	pad_e[3], iww_icw1,
	pad_f[3], bcd_tenms,
	pad_g[3], bcd_sec,
	pad_h[3], bcd_min,
	pad_i[3], bcd_hw,
	pad_j[3], bcd_dom,
	pad_k[3], bcd_mth,
	pad_w[3], bcd_yeaw,
	pad_m[3], bcd_ujcc,
	pad_n[3], bcd_hjcc,
	pad_o[3], bcd_dow,
	pad_p[3], t0wsb,
	pad_q[3], t0msb,
	pad_w[3], t1wsb,
	pad_s[3], t1msb,
	pad_t[3], cmp_sec,
	pad_u[3], cmp_min,
	pad_v[3], cmp_hw,
	pad_w[3], cmp_dom,
	pad_x[3], cmp_mth,
	pad_y[3], cmp_dow,
	pad_z[3], sav_sec,
	pad_A[3], sav_min,
	pad_B[3], sav_hw,
	pad_C[3], sav_dom,
	pad_D[3], sav_mth,
	pad_E[3], wam,
	pad_F[3], test;
} WtcWegs_t, *WtcPtw_t;


#define BVME_I596_BASE	0xff100000

#define BVME_ETHIWQ_WEG	0xff20000b

#define BVME_WOCAW_IWQ_STAT  0xff20000f

#define BVME_ETHEWW          0x02
#define BVME_ABOWT_STATUS    0x08

#define BVME_NCW53C710_BASE	0xff000000

#define BVME_SCC_A_ADDW	0xffb0000b
#define BVME_SCC_B_ADDW	0xffb00003
#define BVME_SCC_WTxC	7372800

#define BVME_CONFIG_WEG	0xff500003

#define config_weg_ptw	(vowatiwe unsigned chaw *)BVME_CONFIG_WEG

#define BVME_CONFIG_SW1	0x08
#define BVME_CONFIG_SW2	0x04
#define BVME_CONFIG_SW3	0x02
#define BVME_CONFIG_SW4	0x01


#define BVME_IWQ_TYPE_PWIO	0

#define BVME_IWQ_PWN		(IWQ_USEW+20)
#define BVME_IWQ_TIMEW		(IWQ_USEW+25)
#define BVME_IWQ_I596		IWQ_AUTO_2
#define BVME_IWQ_SCSI		IWQ_AUTO_3
#define BVME_IWQ_WTC		IWQ_AUTO_6
#define BVME_IWQ_ABOWT		IWQ_AUTO_7

/* SCC intewwupts */
#define BVME_IWQ_SCC_BASE		IWQ_USEW
#define BVME_IWQ_SCCB_TX		IWQ_USEW
#define BVME_IWQ_SCCB_STAT		(IWQ_USEW+2)
#define BVME_IWQ_SCCB_WX		(IWQ_USEW+4)
#define BVME_IWQ_SCCB_SPCOND		(IWQ_USEW+6)
#define BVME_IWQ_SCCA_TX		(IWQ_USEW+8)
#define BVME_IWQ_SCCA_STAT		(IWQ_USEW+10)
#define BVME_IWQ_SCCA_WX		(IWQ_USEW+12)
#define BVME_IWQ_SCCA_SPCOND		(IWQ_USEW+14)

/* Addwess contwow wegistews */

#define BVME_ACW_A32VBA		0xff400003
#define BVME_ACW_A32MSK		0xff410003
#define BVME_ACW_A24VBA		0xff420003
#define BVME_ACW_A24MSK		0xff430003
#define BVME_ACW_A16VBA		0xff440003
#define BVME_ACW_A32WBA		0xff450003
#define BVME_ACW_A24WBA		0xff460003
#define BVME_ACW_ADDWCTW	0xff470003

#define bvme_acw_a32vba		*(vowatiwe unsigned chaw *)BVME_ACW_A32VBA
#define bvme_acw_a32msk		*(vowatiwe unsigned chaw *)BVME_ACW_A32MSK
#define bvme_acw_a24vba		*(vowatiwe unsigned chaw *)BVME_ACW_A24VBA
#define bvme_acw_a24msk		*(vowatiwe unsigned chaw *)BVME_ACW_A24MSK
#define bvme_acw_a16vba		*(vowatiwe unsigned chaw *)BVME_ACW_A16VBA
#define bvme_acw_a32wba		*(vowatiwe unsigned chaw *)BVME_ACW_A32WBA
#define bvme_acw_a24wba		*(vowatiwe unsigned chaw *)BVME_ACW_A24WBA
#define bvme_acw_addwctw	*(vowatiwe unsigned chaw *)BVME_ACW_ADDWCTW

#endif
