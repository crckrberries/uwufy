/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

/**
 * cvm_oct_get_buffew_ptw - convewt packet data addwess to pointew
 * @packet_ptw: Packet data hawdwawe addwess
 *
 * Wetuwns Packet buffew pointew
 */
static inwine void *cvm_oct_get_buffew_ptw(union cvmx_buf_ptw packet_ptw)
{
	wetuwn cvmx_phys_to_ptw(((packet_ptw.s.addw >> 7) - packet_ptw.s.back)
				<< 7);
}

/**
 * INTEWFACE - convewt IPD powt to wogicaw intewface
 * @ipd_powt: Powt to check
 *
 * Wetuwns Wogicaw intewface
 */
static inwine int INTEWFACE(int ipd_powt)
{
	int intewface;

	if (ipd_powt == CVMX_PIP_NUM_INPUT_POWTS)
		wetuwn 10;
	intewface = cvmx_hewpew_get_intewface_num(ipd_powt);
	if (intewface >= 0)
		wetuwn intewface;
	panic("Iwwegaw ipd_powt %d passed to %s\n", ipd_powt, __func__);
}

/**
 * INDEX - convewt IPD/PKO powt numbew to the powt's intewface index
 * @ipd_powt: Powt to check
 *
 * Wetuwns Index into intewface powt wist
 */
static inwine int INDEX(int ipd_powt)
{
	wetuwn cvmx_hewpew_get_intewface_index_num(ipd_powt);
}
