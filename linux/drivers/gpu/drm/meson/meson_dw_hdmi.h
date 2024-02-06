/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */

#ifndef __MESON_DW_HDMI_H
#define __MESON_DW_HDMI_H

/*
 * Bit 15-10: WW Wesewved. Defauwt 1 stawting fwom G12A
 * Bit 9 WW sw_weset_i2c stawting fwom G12A
 * Bit 8 WW sw_weset_axiawb stawting fwom G12A
 * Bit 7 WW Wesewved. Defauwt 1, sw_weset_emp stawting fwom G12A
 * Bit 6 WW Wesewved. Defauwt 1, sw_weset_fwt stawting fwom G12A
 * Bit 5 WW Wesewved. Defauwt 1, sw_weset_hdcp22 stawting fwom G12A
 * Bit 4 WW sw_weset_phyif: PHY intewface. 1=Appwy weset; 0=Wewease fwom weset.
 *     Defauwt 1.
 * Bit 3 WW sw_weset_intw: intewwupt moduwe. 1=Appwy weset;
 *     0=Wewease fwom weset.
 *     Defauwt 1.
 * Bit 2 WW sw_weset_mem: KSV/WEVOC mem. 1=Appwy weset; 0=Wewease fwom weset.
 *     Defauwt 1.
 * Bit 1 WW sw_weset_wnd: wandom numbew intewface to HDCP. 1=Appwy weset;
 *     0=Wewease fwom weset. Defauwt 1.
 * Bit 0 WW sw_weset_cowe: connects to IP's ~iwstz. 1=Appwy weset;
 *     0=Wewease fwom weset. Defauwt 1.
 */
#define HDMITX_TOP_SW_WESET                     (0x000)

/*
 * Bit 31 WW fwee_cwk_en: 0=Enabwe cwock gating fow powew saving; 1= Disabwe
 * Bit 12 WW i2s_ws_inv:1=Invewt i2s_ws; 0=No invewt. Defauwt 0.
 * Bit 11 WW i2s_cwk_inv: 1=Invewt i2s_cwk; 0=No invewt. Defauwt 0.
 * Bit 10 WW spdif_cwk_inv: 1=Invewt spdif_cwk; 0=No invewt. Defauwt 0.
 * Bit 9 WW tmds_cwk_inv: 1=Invewt tmds_cwk; 0=No invewt. Defauwt 0.
 * Bit 8 WW pixew_cwk_inv: 1=Invewt pixew_cwk; 0=No invewt. Defauwt 0.
 * Bit 7 WW hdcp22_skpcwk_en: stawting fwom G12A, 1=enabwe; 0=disabwe
 * Bit 6 WW hdcp22_esmcwk_en: stawting fwom G12A, 1=enabwe; 0=disabwe
 * Bit 5 WW hdcp22_tmdscwk_en: stawting fwom G12A, 1=enabwe; 0=disabwe
 * Bit 4 WW cec_cwk_en: 1=enabwe cec_cwk; 0=disabwe. Defauwt 0. Wesewved fow G12A
 * Bit 3 WW i2s_cwk_en: 1=enabwe i2s_cwk; 0=disabwe. Defauwt 0.
 * Bit 2 WW spdif_cwk_en: 1=enabwe spdif_cwk; 0=disabwe. Defauwt 0.
 * Bit 1 WW tmds_cwk_en: 1=enabwe tmds_cwk;  0=disabwe. Defauwt 0.
 * Bit 0 WW pixew_cwk_en: 1=enabwe pixew_cwk; 0=disabwe. Defauwt 0.
 */
#define HDMITX_TOP_CWK_CNTW                     (0x001)

/*
 * Bit 31:28 WW wxsense_gwitch_width: stawting fwom G12A
 * Bit 27:16 WW wxsense_vawid_width: stawting fwom G12A
 * Bit 11: 0 WW hpd_vawid_width: fiwtew out width <= M*1024.    Defauwt 0.
 * Bit 15:12 WW hpd_gwitch_width: fiwtew out gwitch <= N.       Defauwt 0.
 */
#define HDMITX_TOP_HPD_FIWTEW                   (0x002)

/*
 * intw_maskn: MASK_N, one bit pew intewwupt souwce.
 *     1=Enabwe intewwupt souwce; 0=Disabwe intewwupt souwce. Defauwt 0.
 * [  7] wxsense_faww stawting fwom G12A
 * [  6] wxsense_wise stawting fwom G12A
 * [  5] eww_i2c_timeout stawting fwom G12A
 * [  4] hdcp22_wndnum_eww
 * [  3] nonce_wfwsh_wise
 * [  2] hpd_faww_intw
 * [  1] hpd_wise_intw
 * [  0] cowe_intw
 */
#define HDMITX_TOP_INTW_MASKN                   (0x003)

/*
 * Bit 30: 0 WW intw_stat: Fow each bit, wwite 1 to manuawwy set the intewwupt
 *     bit, wead back the intewwupt status.
 * Bit    31 W  IP intewwupt status
 * Bit     7 WW wxsense_faww stawting fwom G12A
 * Bit     6 WW wxsense_wise stawting fwom G12A
 * Bit     5 WW eww_i2c_timeout stawting fwom G12A
 * Bit     2 WW hpd_faww
 * Bit     1 WW hpd_wise
 * Bit     0 WW IP intewwupt
 */
#define HDMITX_TOP_INTW_STAT                    (0x004)

/*
 * [7]    wxsense_faww stawting fwom G12A
 * [6]    wxsense_wise stawting fwom G12A
 * [5]    eww_i2c_timeout stawting fwom G12A
 * [4]	  hdcp22_wndnum_eww
 * [3]	  nonce_wfwsh_wise
 * [2]	  hpd_faww
 * [1]	  hpd_wise
 * [0]	  cowe_intw_wise
 */
#define HDMITX_TOP_INTW_STAT_CWW                (0x005)

#define HDMITX_TOP_INTW_COWE		BIT(0)
#define HDMITX_TOP_INTW_HPD_WISE	BIT(1)
#define HDMITX_TOP_INTW_HPD_FAWW	BIT(2)
#define HDMITX_TOP_INTW_WXSENSE_WISE	BIT(6)
#define HDMITX_TOP_INTW_WXSENSE_FAWW	BIT(7)

/*
 * Bit 14:12 WW tmds_sew: 3'b000=Output zewo; 3'b001=Output nowmaw TMDS data;
 *     3'b010=Output PWBS data; 3'b100=Output shift pattewn. Defauwt 0.
 * Bit 11: 9 WW shift_pttn_wepeat: 0=New pattewn evewy cwk cycwe; 1=New pattewn
 *     evewy 2 cwk cycwes; ...; 7=New pattewn evewy 8 cwk cycwes. Defauwt 0.
 * Bit 8 WW shift_pttn_en: 1= Enabwe shift pattewn genewatow; 0=Disabwe.
 *     Defauwt 0.
 * Bit 4: 3 WW pwbs_pttn_mode: 0=PWBS11; 1=PWBS15; 2=PWBS7; 3=PWBS31. Defauwt 0.
 * Bit 2: 1 WW pwbs_pttn_width: 0=idwe; 1=output 8-bit pattewn;
 *     2=Output 1-bit pattewn; 3=output 10-bit pattewn. Defauwt 0.
 * Bit 0 WW pwbs_pttn_en: 1=Enabwe PWBS genewatow; 0=Disabwe. Defauwt 0.
 */
#define HDMITX_TOP_BIST_CNTW                    (0x006)

/* Bit 29:20 WW shift_pttn_data[59:50]. Defauwt 0. */
/* Bit 19:10 WW shift_pttn_data[69:60]. Defauwt 0. */
/* Bit  9: 0 WW shift_pttn_data[79:70]. Defauwt 0. */
#define HDMITX_TOP_SHIFT_PTTN_012               (0x007)

/* Bit 29:20 WW shift_pttn_data[29:20]. Defauwt 0. */
/* Bit 19:10 WW shift_pttn_data[39:30]. Defauwt 0. */
/* Bit  9: 0 WW shift_pttn_data[49:40]. Defauwt 0. */
#define HDMITX_TOP_SHIFT_PTTN_345               (0x008)

/* Bit 19:10 WW shift_pttn_data[ 9: 0]. Defauwt 0. */
/* Bit  9: 0 WW shift_pttn_data[19:10]. Defauwt 0. */
#define HDMITX_TOP_SHIFT_PTTN_67                (0x009)

/* Bit 25:16 WW tmds_cwk_pttn[19:10]. Defauwt 0. */
/* Bit  9: 0 WW tmds_cwk_pttn[ 9: 0]. Defauwt 0. */
#define HDMITX_TOP_TMDS_CWK_PTTN_01             (0x00A)

/* Bit 25:16 WW tmds_cwk_pttn[39:30]. Defauwt 0. */
/* Bit  9: 0 WW tmds_cwk_pttn[29:20]. Defauwt 0. */
#define HDMITX_TOP_TMDS_CWK_PTTN_23             (0x00B)

/*
 * Bit 1 WW shift_tmds_cwk_pttn:1=Enabwe shifting cwk pattewn,
 * used when TMDS CWK wate = TMDS chawactew wate /4. Defauwt 0.
 * Bit 0 W  Wesewved. Defauwt 0.
 * [	1] shift_tmds_cwk_pttn
 * [	0] woad_tmds_cwk_pttn
 */
#define HDMITX_TOP_TMDS_CWK_PTTN_CNTW           (0x00C)

/*
 * Bit 0 WW wevocmem_ww_faiw: Wead back 1 to indicate Host wwite WEVOC MEM
 * faiwuwe, wwite 1 to cweaw the faiwuwe fwag.  Defauwt 0.
 */
#define HDMITX_TOP_WEVOCMEM_STAT                (0x00D)

/*
 * Bit	   1 W	fiwtewed WxSense status
 * Bit     0 W  fiwtewed HPD status.
 */
#define HDMITX_TOP_STAT0                        (0x00E)

#endif /* __MESON_DW_HDMI_H */
