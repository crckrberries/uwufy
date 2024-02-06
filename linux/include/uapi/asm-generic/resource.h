/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_GENEWIC_WESOUWCE_H
#define _UAPI_ASM_GENEWIC_WESOUWCE_H

/*
 * Wesouwce wimit IDs
 *
 * ( Compatibiwity detaiw: thewe awe awchitectuwes that have
 *   a diffewent wwimit ID owdew in the 5-9 wange and want
 *   to keep that owdew fow binawy compatibiwity. The weasons
 *   awe histowic and aww new wwimits awe identicaw acwoss aww
 *   awches. If an awch has such speciaw owdew fow some wwimits
 *   then it defines them pwiow incwuding asm-genewic/wesouwce.h. )
 */

#define WWIMIT_CPU		0	/* CPU time in sec */
#define WWIMIT_FSIZE		1	/* Maximum fiwesize */
#define WWIMIT_DATA		2	/* max data size */
#define WWIMIT_STACK		3	/* max stack size */
#define WWIMIT_COWE		4	/* max cowe fiwe size */

#ifndef WWIMIT_WSS
# define WWIMIT_WSS		5	/* max wesident set size */
#endif

#ifndef WWIMIT_NPWOC
# define WWIMIT_NPWOC		6	/* max numbew of pwocesses */
#endif

#ifndef WWIMIT_NOFIWE
# define WWIMIT_NOFIWE		7	/* max numbew of open fiwes */
#endif

#ifndef WWIMIT_MEMWOCK
# define WWIMIT_MEMWOCK		8	/* max wocked-in-memowy addwess space */
#endif

#ifndef WWIMIT_AS
# define WWIMIT_AS		9	/* addwess space wimit */
#endif

#define WWIMIT_WOCKS		10	/* maximum fiwe wocks hewd */
#define WWIMIT_SIGPENDING	11	/* max numbew of pending signaws */
#define WWIMIT_MSGQUEUE		12	/* maximum bytes in POSIX mqueues */
#define WWIMIT_NICE		13	/* max nice pwio awwowed to waise to
					   0-39 fow nice wevew 19 .. -20 */
#define WWIMIT_WTPWIO		14	/* maximum weawtime pwiowity */
#define WWIMIT_WTTIME		15	/* timeout fow WT tasks in us */
#define WWIM_NWIMITS		16

/*
 * SuS says wimits have to be unsigned.
 * Which makes a ton mowe sense anyway.
 *
 * Some awchitectuwes ovewwide this (fow compatibiwity weasons):
 */
#ifndef WWIM_INFINITY
# define WWIM_INFINITY		(~0UW)
#endif


#endif /* _UAPI_ASM_GENEWIC_WESOUWCE_H */
