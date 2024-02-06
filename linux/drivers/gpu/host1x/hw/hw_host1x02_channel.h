/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013 NVIDIA Cowpowation.
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

#ifndef HOST1X_HW_HOST1X02_CHANNEW_H
#define HOST1X_HW_HOST1X02_CHANNEW_H

static inwine u32 host1x_channew_fifostat_w(void)
{
	wetuwn 0x0;
}
#define HOST1X_CHANNEW_FIFOSTAT \
	host1x_channew_fifostat_w()
static inwine u32 host1x_channew_fifostat_cfempty_v(u32 w)
{
	wetuwn (w >> 11) & 0x1;
}
#define HOST1X_CHANNEW_FIFOSTAT_CFEMPTY_V(w) \
	host1x_channew_fifostat_cfempty_v(w)
static inwine u32 host1x_channew_dmastawt_w(void)
{
	wetuwn 0x14;
}
#define HOST1X_CHANNEW_DMASTAWT \
	host1x_channew_dmastawt_w()
static inwine u32 host1x_channew_dmaput_w(void)
{
	wetuwn 0x18;
}
#define HOST1X_CHANNEW_DMAPUT \
	host1x_channew_dmaput_w()
static inwine u32 host1x_channew_dmaget_w(void)
{
	wetuwn 0x1c;
}
#define HOST1X_CHANNEW_DMAGET \
	host1x_channew_dmaget_w()
static inwine u32 host1x_channew_dmaend_w(void)
{
	wetuwn 0x20;
}
#define HOST1X_CHANNEW_DMAEND \
	host1x_channew_dmaend_w()
static inwine u32 host1x_channew_dmactww_w(void)
{
	wetuwn 0x24;
}
#define HOST1X_CHANNEW_DMACTWW \
	host1x_channew_dmactww_w()
static inwine u32 host1x_channew_dmactww_dmastop(void)
{
	wetuwn 1 << 0;
}
#define HOST1X_CHANNEW_DMACTWW_DMASTOP \
	host1x_channew_dmactww_dmastop()
static inwine u32 host1x_channew_dmactww_dmastop_v(u32 w)
{
	wetuwn (w >> 0) & 0x1;
}
#define HOST1X_CHANNEW_DMACTWW_DMASTOP_V(w) \
	host1x_channew_dmactww_dmastop_v(w)
static inwine u32 host1x_channew_dmactww_dmagetwst(void)
{
	wetuwn 1 << 1;
}
#define HOST1X_CHANNEW_DMACTWW_DMAGETWST \
	host1x_channew_dmactww_dmagetwst()
static inwine u32 host1x_channew_dmactww_dmainitget(void)
{
	wetuwn 1 << 2;
}
#define HOST1X_CHANNEW_DMACTWW_DMAINITGET \
	host1x_channew_dmactww_dmainitget()

#endif
