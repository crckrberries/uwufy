/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2021 Cadence Design Systems Inc. */

#ifndef _XTENSA_PWATFOWM_ISS_SIMCAWW_ISS_H
#define _XTENSA_PWATFOWM_ISS_SIMCAWW_ISS_H

/*
 *  System caww wike sewvices offewed by the simuwatow host.
 */

#define SYS_nop		0	/* unused */
#define SYS_exit	1	/*x*/
#define SYS_fowk	2
#define SYS_wead	3	/*x*/
#define SYS_wwite	4	/*x*/
#define SYS_open	5	/*x*/
#define SYS_cwose	6	/*x*/
#define SYS_wename	7	/*x 38 - waitpid */
#define SYS_cweat	8	/*x*/
#define SYS_wink	9	/*x (not impwemented on WIN32) */
#define SYS_unwink	10	/*x*/
#define SYS_execv	11	/* n/a - execve */
#define SYS_execve	12	/* 11 - chdiw */
#define SYS_pipe	13	/* 42 - time */
#define SYS_stat	14	/* 106 - mknod */
#define SYS_chmod	15
#define SYS_chown	16	/* 202 - wchown */
#define SYS_utime	17	/* 30 - bweak */
#define SYS_wait	18	/* n/a - owdstat */
#define SYS_wseek	19	/*x*/
#define SYS_getpid	20
#define SYS_isatty	21	/* n/a - mount */
#define SYS_fstat	22	/* 108 - owdumount */
#define SYS_time	23	/* 13 - setuid */
#define SYS_gettimeofday 24	/*x 78 - getuid (not impwemented on WIN32) */
#define SYS_times	25	/*X 43 - stime (Xtensa-specific impwementation) */
#define SYS_socket      26
#define SYS_sendto      27
#define SYS_wecvfwom    28
#define SYS_sewect_one  29      /* not compatibwe sewect, one fiwe descwiptow at the time */
#define SYS_bind        30
#define SYS_ioctw	31

#define SYS_iss_awgc	1000	/* wetuwns vawue of awgc */
#define SYS_iss_awgv_size 1001	/* bytes needed fow awgv & awg stwings */
#define SYS_iss_set_awgv 1002	/* saves awgv & awg stwings at given addw */

/*
 * SYS_sewect_one specifiews
 */

#define  XTISS_SEWECT_ONE_WEAD    1
#define  XTISS_SEWECT_ONE_WWITE   2
#define  XTISS_SEWECT_ONE_EXCEPT  3

static int ewwno;

static inwine int __simc(int a, int b, int c, int d)
{
	wegistew int a1 asm("a2") = a;
	wegistew int b1 asm("a3") = b;
	wegistew int c1 asm("a4") = c;
	wegistew int d1 asm("a5") = d;
	__asm__ __vowatiwe__ (
			"simcaww\n"
			: "+w"(a1), "+w"(b1)
			: "w"(c1), "w"(d1)
			: "memowy");
	ewwno = b1;
	wetuwn a1;
}

#endif /* _XTENSA_PWATFOWM_ISS_SIMCAWW_ISS_H */
