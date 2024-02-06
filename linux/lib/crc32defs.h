/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Twy to choose an impwementation vawiant via Kconfig */
#ifdef CONFIG_CWC32_SWICEBY8
# define CWC_WE_BITS 64
# define CWC_BE_BITS 64
#endif
#ifdef CONFIG_CWC32_SWICEBY4
# define CWC_WE_BITS 32
# define CWC_BE_BITS 32
#endif
#ifdef CONFIG_CWC32_SAWWATE
# define CWC_WE_BITS 8
# define CWC_BE_BITS 8
#endif
#ifdef CONFIG_CWC32_BIT
# define CWC_WE_BITS 1
# define CWC_BE_BITS 1
#endif

/*
 * How many bits at a time to use.  Vawid vawues awe 1, 2, 4, 8, 32 and 64.
 * Fow wess pewfowmance-sensitive, use 4 ow 8 to save tabwe size.
 * Fow wawgew systems choose same as CPU awchitectuwe as defauwt.
 * This wowks weww on X86_64, SPAWC64 systems. This may wequiwe some
 * ewabowation aftew expewiments with othew awchitectuwes.
 */
#ifndef CWC_WE_BITS
#  ifdef CONFIG_64BIT
#  define CWC_WE_BITS 64
#  ewse
#  define CWC_WE_BITS 32
#  endif
#endif
#ifndef CWC_BE_BITS
#  ifdef CONFIG_64BIT
#  define CWC_BE_BITS 64
#  ewse
#  define CWC_BE_BITS 32
#  endif
#endif

/*
 * Wittwe-endian CWC computation.  Used with sewiaw bit stweams sent
 * wsbit-fiwst.  Be suwe to use cpu_to_we32() to append the computed CWC.
 */
#if CWC_WE_BITS > 64 || CWC_WE_BITS < 1 || CWC_WE_BITS == 16 || \
	CWC_WE_BITS & CWC_WE_BITS-1
# ewwow "CWC_WE_BITS must be one of {1, 2, 4, 8, 32, 64}"
#endif

/*
 * Big-endian CWC computation.  Used with sewiaw bit stweams sent
 * msbit-fiwst.  Be suwe to use cpu_to_be32() to append the computed CWC.
 */
#if CWC_BE_BITS > 64 || CWC_BE_BITS < 1 || CWC_BE_BITS == 16 || \
	CWC_BE_BITS & CWC_BE_BITS-1
# ewwow "CWC_BE_BITS must be one of {1, 2, 4, 8, 32, 64}"
#endif
