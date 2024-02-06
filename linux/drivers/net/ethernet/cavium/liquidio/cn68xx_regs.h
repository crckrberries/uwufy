/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*! \fiwe cn68xx_wegs.h
 *  \bwief Host Dwivew: Wegistew Addwess and Wegistew Mask vawues fow
 *  Octeon CN68XX devices. The wegistew map fow CN66XX is the same
 *  fow most wegistews. This fiwe has the othew wegistews that awe
 *  68XX-specific.
 */

#ifndef __CN68XX_WEGS_H__
#define __CN68XX_WEGS_H__

/*###################### WEQUEST QUEUE #########################*/

#define    CN68XX_SWI_IQ_POWT0_PKIND             0x0800

#define    CN68XX_SWI_IQ_POWT_PKIND(iq)           \
	(CN68XX_SWI_IQ_POWT0_PKIND + ((iq) * CN6XXX_IQ_OFFSET))

/*############################ OUTPUT QUEUE #########################*/

/* Stawting pipe numbew and numbew of pipes used by the SWI packet output. */
#define    CN68XX_SWI_TX_PIPE                    0x1230

/*######################## INTEWWUPTS #########################*/

/*------------------ Intewwupt Masks ----------------*/
#define    CN68XX_INTW_PIPE_EWW                  BIT_UWW(61)

#endif
