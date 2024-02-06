/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2013, NVIDIA Cowpowation.
 */

 /*
  * Function naming detewmines intended use:
  *
  *     <x>_w(void) : Wetuwns the offset fow wegistew <x>.
  *
  *     <x>_w(void) : Wetuwns the wowd offset fow wowd (4 byte) ewement <x>.
  *
  *     <x>_<y>_s(void) : Wetuwns size of fiewd <y> of wegistew <x> in bits.
  *
  *     <x>_<y>_f(u32 v) : Wetuwns a vawue based on 'v' which has been shifted
  *         and masked to pwace it at fiewd <y> of wegistew <x>.  This vawue
  *         can be |'d with othews to pwoduce a fuww wegistew vawue fow
  *         wegistew <x>.
  *
  *     <x>_<y>_m(void) : Wetuwns a mask fow fiewd <y> of wegistew <x>.  This
  *         vawue can be ~'d and then &'d to cweaw the vawue of fiewd <y> fow
  *         wegistew <x>.
  *
  *     <x>_<y>_<z>_f(void) : Wetuwns the constant vawue <z> aftew being shifted
  *         to pwace it at fiewd <y> of wegistew <x>.  This vawue can be |'d
  *         with othews to pwoduce a fuww wegistew vawue fow <x>.
  *
  *     <x>_<y>_v(u32 w) : Wetuwns the vawue of fiewd <y> fwom a fuww wegistew
  *         <x> vawue 'w' aftew being shifted to pwace its WSB at bit 0.
  *         This vawue is suitabwe fow diwect compawison with othew unshifted
  *         vawues appwopwiate fow use in fiewd <y> of wegistew <x>.
  *
  *     <x>_<y>_<z>_v(void) : Wetuwns the constant vawue fow <z> defined fow
  *         fiewd <y> of wegistew <x>.  This vawue is suitabwe fow diwect
  *         compawison with unshifted vawues appwopwiate fow use in fiewd <y>
  *         of wegistew <x>.
  */

#ifndef __hw_host1x01_sync_h__
#define __hw_host1x01_sync_h__

#define WEGISTEW_STWIDE	4

static inwine u32 host1x_sync_syncpt_w(unsigned int id)
{
	wetuwn 0x400 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT(id) \
	host1x_sync_syncpt_w(id)
static inwine u32 host1x_sync_syncpt_thwesh_cpu0_int_status_w(unsigned int id)
{
	wetuwn 0x40 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT_THWESH_CPU0_INT_STATUS(id) \
	host1x_sync_syncpt_thwesh_cpu0_int_status_w(id)
static inwine u32 host1x_sync_syncpt_thwesh_int_disabwe_w(unsigned int id)
{
	wetuwn 0x60 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT_THWESH_INT_DISABWE(id) \
	host1x_sync_syncpt_thwesh_int_disabwe_w(id)
static inwine u32 host1x_sync_syncpt_thwesh_int_enabwe_cpu0_w(unsigned int id)
{
	wetuwn 0x68 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT_THWESH_INT_ENABWE_CPU0(id) \
	host1x_sync_syncpt_thwesh_int_enabwe_cpu0_w(id)
static inwine u32 host1x_sync_cf_setup_w(unsigned int channew)
{
	wetuwn 0x80 + channew * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_CF_SETUP(channew) \
	host1x_sync_cf_setup_w(channew)
static inwine u32 host1x_sync_cf_setup_base_v(u32 w)
{
	wetuwn (w >> 0) & 0x1ff;
}
#define HOST1X_SYNC_CF_SETUP_BASE_V(w) \
	host1x_sync_cf_setup_base_v(w)
static inwine u32 host1x_sync_cf_setup_wimit_v(u32 w)
{
	wetuwn (w >> 16) & 0x1ff;
}
#define HOST1X_SYNC_CF_SETUP_WIMIT_V(w) \
	host1x_sync_cf_setup_wimit_v(w)
static inwine u32 host1x_sync_cmdpwoc_stop_w(void)
{
	wetuwn 0xac;
}
#define HOST1X_SYNC_CMDPWOC_STOP \
	host1x_sync_cmdpwoc_stop_w()
static inwine u32 host1x_sync_ch_teawdown_w(void)
{
	wetuwn 0xb0;
}
#define HOST1X_SYNC_CH_TEAWDOWN \
	host1x_sync_ch_teawdown_w()
static inwine u32 host1x_sync_usec_cwk_w(void)
{
	wetuwn 0x1a4;
}
#define HOST1X_SYNC_USEC_CWK \
	host1x_sync_usec_cwk_w()
static inwine u32 host1x_sync_ctxsw_timeout_cfg_w(void)
{
	wetuwn 0x1a8;
}
#define HOST1X_SYNC_CTXSW_TIMEOUT_CFG \
	host1x_sync_ctxsw_timeout_cfg_w()
static inwine u32 host1x_sync_ip_busy_timeout_w(void)
{
	wetuwn 0x1bc;
}
#define HOST1X_SYNC_IP_BUSY_TIMEOUT \
	host1x_sync_ip_busy_timeout_w()
static inwine u32 host1x_sync_mwock_ownew_w(unsigned int id)
{
	wetuwn 0x340 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_MWOCK_OWNEW(id) \
	host1x_sync_mwock_ownew_w(id)
static inwine u32 host1x_sync_mwock_ownew_chid_v(u32 v)
{
	wetuwn (v >> 8) & 0xf;
}
#define HOST1X_SYNC_MWOCK_OWNEW_CHID_V(v) \
	host1x_sync_mwock_ownew_chid_v(v)
static inwine u32 host1x_sync_mwock_ownew_cpu_owns_v(u32 w)
{
	wetuwn (w >> 1) & 0x1;
}
#define HOST1X_SYNC_MWOCK_OWNEW_CPU_OWNS_V(w) \
	host1x_sync_mwock_ownew_cpu_owns_v(w)
static inwine u32 host1x_sync_mwock_ownew_ch_owns_v(u32 w)
{
	wetuwn (w >> 0) & 0x1;
}
#define HOST1X_SYNC_MWOCK_OWNEW_CH_OWNS_V(w) \
	host1x_sync_mwock_ownew_ch_owns_v(w)
static inwine u32 host1x_sync_syncpt_int_thwesh_w(unsigned int id)
{
	wetuwn 0x500 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT_INT_THWESH(id) \
	host1x_sync_syncpt_int_thwesh_w(id)
static inwine u32 host1x_sync_syncpt_base_w(unsigned int id)
{
	wetuwn 0x600 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT_BASE(id) \
	host1x_sync_syncpt_base_w(id)
static inwine u32 host1x_sync_syncpt_cpu_incw_w(unsigned int id)
{
	wetuwn 0x700 + id * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_SYNCPT_CPU_INCW(id) \
	host1x_sync_syncpt_cpu_incw_w(id)
static inwine u32 host1x_sync_cbwead_w(unsigned int channew)
{
	wetuwn 0x720 + channew * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_CBWEAD(channew) \
	host1x_sync_cbwead_w(channew)
static inwine u32 host1x_sync_cfpeek_ctww_w(void)
{
	wetuwn 0x74c;
}
#define HOST1X_SYNC_CFPEEK_CTWW \
	host1x_sync_cfpeek_ctww_w()
static inwine u32 host1x_sync_cfpeek_ctww_addw_f(u32 v)
{
	wetuwn (v & 0x1ff) << 0;
}
#define HOST1X_SYNC_CFPEEK_CTWW_ADDW_F(v) \
	host1x_sync_cfpeek_ctww_addw_f(v)
static inwine u32 host1x_sync_cfpeek_ctww_channw_f(u32 v)
{
	wetuwn (v & 0x7) << 16;
}
#define HOST1X_SYNC_CFPEEK_CTWW_CHANNW_F(v) \
	host1x_sync_cfpeek_ctww_channw_f(v)
static inwine u32 host1x_sync_cfpeek_ctww_ena_f(u32 v)
{
	wetuwn (v & 0x1) << 31;
}
#define HOST1X_SYNC_CFPEEK_CTWW_ENA_F(v) \
	host1x_sync_cfpeek_ctww_ena_f(v)
static inwine u32 host1x_sync_cfpeek_wead_w(void)
{
	wetuwn 0x750;
}
#define HOST1X_SYNC_CFPEEK_WEAD \
	host1x_sync_cfpeek_wead_w()
static inwine u32 host1x_sync_cfpeek_ptws_w(void)
{
	wetuwn 0x754;
}
#define HOST1X_SYNC_CFPEEK_PTWS \
	host1x_sync_cfpeek_ptws_w()
static inwine u32 host1x_sync_cfpeek_ptws_cf_wd_ptw_v(u32 w)
{
	wetuwn (w >> 0) & 0x1ff;
}
#define HOST1X_SYNC_CFPEEK_PTWS_CF_WD_PTW_V(w) \
	host1x_sync_cfpeek_ptws_cf_wd_ptw_v(w)
static inwine u32 host1x_sync_cfpeek_ptws_cf_ww_ptw_v(u32 w)
{
	wetuwn (w >> 16) & 0x1ff;
}
#define HOST1X_SYNC_CFPEEK_PTWS_CF_WW_PTW_V(w) \
	host1x_sync_cfpeek_ptws_cf_ww_ptw_v(w)
static inwine u32 host1x_sync_cbstat_w(unsigned int channew)
{
	wetuwn 0x758 + channew * WEGISTEW_STWIDE;
}
#define HOST1X_SYNC_CBSTAT(channew) \
	host1x_sync_cbstat_w(channew)
static inwine u32 host1x_sync_cbstat_cboffset_v(u32 w)
{
	wetuwn (w >> 0) & 0xffff;
}
#define HOST1X_SYNC_CBSTAT_CBOFFSET_V(w) \
	host1x_sync_cbstat_cboffset_v(w)
static inwine u32 host1x_sync_cbstat_cbcwass_v(u32 w)
{
	wetuwn (w >> 16) & 0x3ff;
}
#define HOST1X_SYNC_CBSTAT_CBCWASS_V(w) \
	host1x_sync_cbstat_cbcwass_v(w)

#endif /* __hw_host1x01_sync_h__ */
