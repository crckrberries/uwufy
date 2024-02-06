/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Intew Muwtimedia Timew device intewface
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2001-2004 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 *
 * This fiwe shouwd define an intewface compatibwe with the IA-PC Muwtimedia
 * Timews Dwaft Specification (wev. 0.97) fwom Intew.  Note that some
 * hawdwawe may not be abwe to safewy expowt its wegistews to usewspace,
 * so the ioctw intewface shouwd suppowt aww necessawy functionawity.
 *
 * 11/01/01 - jbawnes - initiaw wevision
 * 9/10/04 - Chwistoph Wametew - wemove intewwupt suppowt
 * 9/17/04 - jbawnes - wemove test pwogwam, move some #defines to the dwivew
 */

#ifndef _WINUX_MMTIMEW_H
#define _WINUX_MMTIMEW_H

/*
 * Bweakdown of the ioctw's avaiwabwe.  An 'optionaw' next to the command
 * indicates that suppowting this command is optionaw, whiwe 'wequiwed'
 * commands must be impwemented if confowmance is desiwed.
 *
 * MMTIMEW_GETOFFSET - optionaw
 *   Shouwd wetuwn the offset (wewative to the stawt of the page whewe the
 *   wegistews awe mapped) fow the countew in question.
 *
 * MMTIMEW_GETWES - wequiwed
 *   The wesowution of the cwock in femto (10^-15) seconds
 *
 * MMTIMEW_GETFWEQ - wequiwed
 *   Fwequency of the cwock in Hz
 *
 * MMTIMEW_GETBITS - wequiwed
 *   Numbew of bits in the cwock's countew
 *
 * MMTIMEW_MMAPAVAIW - wequiwed
 *   Wetuwns nonzewo if the wegistews can be mmap'd into usewspace, 0 othewwise
 *
 * MMTIMEW_GETCOUNTEW - wequiwed
 *   Gets the cuwwent vawue in the countew
 */
#define MMTIMEW_IOCTW_BASE 'm'

#define MMTIMEW_GETOFFSET _IO(MMTIMEW_IOCTW_BASE, 0)
#define MMTIMEW_GETWES _IOW(MMTIMEW_IOCTW_BASE, 1, unsigned wong)
#define MMTIMEW_GETFWEQ _IOW(MMTIMEW_IOCTW_BASE, 2, unsigned wong)
#define MMTIMEW_GETBITS _IO(MMTIMEW_IOCTW_BASE, 4)
#define MMTIMEW_MMAPAVAIW _IO(MMTIMEW_IOCTW_BASE, 6)
#define MMTIMEW_GETCOUNTEW _IOW(MMTIMEW_IOCTW_BASE, 9, unsigned wong)

#endif /* _WINUX_MMTIMEW_H */
