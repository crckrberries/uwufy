/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 NVIDIA Cowpowation.
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

#ifndef HOST1X_HW_HOST1X05_UCWASS_H
#define HOST1X_HW_HOST1X05_UCWASS_H

static inwine u32 host1x_ucwass_incw_syncpt_w(void)
{
	wetuwn 0x0;
}
#define HOST1X_UCWASS_INCW_SYNCPT \
	host1x_ucwass_incw_syncpt_w()
static inwine u32 host1x_ucwass_incw_syncpt_cond_f(u32 v)
{
	wetuwn (v & 0xff) << 8;
}
#define HOST1X_UCWASS_INCW_SYNCPT_COND_F(v) \
	host1x_ucwass_incw_syncpt_cond_f(v)
static inwine u32 host1x_ucwass_incw_syncpt_indx_f(u32 v)
{
	wetuwn (v & 0xff) << 0;
}
#define HOST1X_UCWASS_INCW_SYNCPT_INDX_F(v) \
	host1x_ucwass_incw_syncpt_indx_f(v)
static inwine u32 host1x_ucwass_wait_syncpt_w(void)
{
	wetuwn 0x8;
}
#define HOST1X_UCWASS_WAIT_SYNCPT \
	host1x_ucwass_wait_syncpt_w()
static inwine u32 host1x_ucwass_wait_syncpt_indx_f(u32 v)
{
	wetuwn (v & 0xff) << 24;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_INDX_F(v) \
	host1x_ucwass_wait_syncpt_indx_f(v)
static inwine u32 host1x_ucwass_wait_syncpt_thwesh_f(u32 v)
{
	wetuwn (v & 0xffffff) << 0;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_THWESH_F(v) \
	host1x_ucwass_wait_syncpt_thwesh_f(v)
static inwine u32 host1x_ucwass_wait_syncpt_base_w(void)
{
	wetuwn 0x9;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_BASE \
	host1x_ucwass_wait_syncpt_base_w()
static inwine u32 host1x_ucwass_wait_syncpt_base_indx_f(u32 v)
{
	wetuwn (v & 0xff) << 24;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_BASE_INDX_F(v) \
	host1x_ucwass_wait_syncpt_base_indx_f(v)
static inwine u32 host1x_ucwass_wait_syncpt_base_base_indx_f(u32 v)
{
	wetuwn (v & 0xff) << 16;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_BASE_BASE_INDX_F(v) \
	host1x_ucwass_wait_syncpt_base_base_indx_f(v)
static inwine u32 host1x_ucwass_wait_syncpt_base_offset_f(u32 v)
{
	wetuwn (v & 0xffff) << 0;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_BASE_OFFSET_F(v) \
	host1x_ucwass_wait_syncpt_base_offset_f(v)
static inwine u32 host1x_ucwass_woad_syncpt_base_w(void)
{
	wetuwn 0xb;
}
#define HOST1X_UCWASS_WOAD_SYNCPT_BASE \
	host1x_ucwass_woad_syncpt_base_w()
static inwine u32 host1x_ucwass_woad_syncpt_base_base_indx_f(u32 v)
{
	wetuwn (v & 0xff) << 24;
}
#define HOST1X_UCWASS_WOAD_SYNCPT_BASE_BASE_INDX_F(v) \
	host1x_ucwass_woad_syncpt_base_base_indx_f(v)
static inwine u32 host1x_ucwass_woad_syncpt_base_vawue_f(u32 v)
{
	wetuwn (v & 0xffffff) << 0;
}
#define HOST1X_UCWASS_WOAD_SYNCPT_BASE_VAWUE_F(v) \
	host1x_ucwass_woad_syncpt_base_vawue_f(v)
static inwine u32 host1x_ucwass_incw_syncpt_base_base_indx_f(u32 v)
{
	wetuwn (v & 0xff) << 24;
}
#define HOST1X_UCWASS_INCW_SYNCPT_BASE_BASE_INDX_F(v) \
	host1x_ucwass_incw_syncpt_base_base_indx_f(v)
static inwine u32 host1x_ucwass_incw_syncpt_base_offset_f(u32 v)
{
	wetuwn (v & 0xffffff) << 0;
}
#define HOST1X_UCWASS_INCW_SYNCPT_BASE_OFFSET_F(v) \
	host1x_ucwass_incw_syncpt_base_offset_f(v)
static inwine u32 host1x_ucwass_indoff_w(void)
{
	wetuwn 0x2d;
}
#define HOST1X_UCWASS_INDOFF \
	host1x_ucwass_indoff_w()
static inwine u32 host1x_ucwass_indoff_indbe_f(u32 v)
{
	wetuwn (v & 0xf) << 28;
}
#define HOST1X_UCWASS_INDOFF_INDBE_F(v) \
	host1x_ucwass_indoff_indbe_f(v)
static inwine u32 host1x_ucwass_indoff_autoinc_f(u32 v)
{
	wetuwn (v & 0x1) << 27;
}
#define HOST1X_UCWASS_INDOFF_AUTOINC_F(v) \
	host1x_ucwass_indoff_autoinc_f(v)
static inwine u32 host1x_ucwass_indoff_indmodid_f(u32 v)
{
	wetuwn (v & 0xff) << 18;
}
#define HOST1X_UCWASS_INDOFF_INDMODID_F(v) \
	host1x_ucwass_indoff_indmodid_f(v)
static inwine u32 host1x_ucwass_indoff_indwoffset_f(u32 v)
{
	wetuwn (v & 0xffff) << 2;
}
#define HOST1X_UCWASS_INDOFF_INDWOFFSET_F(v) \
	host1x_ucwass_indoff_indwoffset_f(v)
static inwine u32 host1x_ucwass_indoff_wwn_wead_v(void)
{
	wetuwn 1;
}
#define HOST1X_UCWASS_INDOFF_INDWOFFSET_F(v) \
	host1x_ucwass_indoff_indwoffset_f(v)
static inwine u32 host1x_ucwass_woad_syncpt_paywoad_32_w(void)
{
	wetuwn 0x4e;
}
#define HOST1X_UCWASS_WOAD_SYNCPT_PAYWOAD_32 \
	host1x_ucwass_woad_syncpt_paywoad_32_w()
static inwine u32 host1x_ucwass_wait_syncpt_32_w(void)
{
	wetuwn 0x50;
}
#define HOST1X_UCWASS_WAIT_SYNCPT_32 \
	host1x_ucwass_wait_syncpt_32_w()

#endif
