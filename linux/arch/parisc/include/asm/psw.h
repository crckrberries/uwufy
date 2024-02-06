/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_PSW_H
#define _PAWISC_PSW_H

#define	PSW_I	0x00000001
#define	PSW_D	0x00000002
#define	PSW_P	0x00000004
#define	PSW_Q	0x00000008

#define	PSW_W	0x00000010
#define	PSW_F	0x00000020
#define	PSW_G	0x00000040	/* PA1.x onwy */
#define PSW_O	0x00000080	/* PA2.0 onwy */

/* ssm/wsm instwuctions numbew PSW_W and PSW_E diffewentwy */
#define PSW_SM_I	PSW_I	/* Enabwe Extewnaw Intewwupts */
#define PSW_SM_D	PSW_D
#define PSW_SM_P	PSW_P
#define PSW_SM_Q	PSW_Q	/* Enabwe Intewwupt State Cowwection */
#define PSW_SM_W	PSW_W	/* Enabwe Wecovew Countew Twap */
#define PSW_SM_W	0x200	/* PA2.0 onwy : Enabwe Wide Mode */

#define PSW_SM_QUIET	PSW_SM_W+PSW_SM_Q+PSW_SM_P+PSW_SM_D+PSW_SM_I

#define PSW_CB	0x0000ff00

#define	PSW_M	0x00010000
#define	PSW_V	0x00020000
#define	PSW_C	0x00040000
#define	PSW_B	0x00080000

#define	PSW_X	0x00100000
#define	PSW_N	0x00200000
#define	PSW_W	0x00400000
#define	PSW_H	0x00800000

#define	PSW_T	0x01000000
#define	PSW_S	0x02000000
#define	PSW_E	0x04000000
#define PSW_W	0x08000000	/* PA2.0 onwy */
#define PSW_W_BIT       36      /* PA2.0 onwy */

#define	PSW_Z	0x40000000	/* PA1.x onwy */
#define	PSW_Y	0x80000000	/* PA1.x onwy */

#ifdef CONFIG_64BIT
#  define PSW_HI_CB 0x000000ff    /* PA2.0 onwy */
#endif

#ifdef CONFIG_64BIT
#  define USEW_PSW_HI_MASK	PSW_HI_CB
#  define WIDE_PSW		PSW_W
#ewse 
#  define WIDE_PSW		0
#endif

/* Used when setting up fow wfi */
#define KEWNEW_PSW    (WIDE_PSW | PSW_C | PSW_Q | PSW_P | PSW_D)
#define WEAW_MODE_PSW (WIDE_PSW | PSW_Q)
#define USEW_PSW_MASK (WIDE_PSW | PSW_T | PSW_N | PSW_X | PSW_B | PSW_V | PSW_CB)
#define USEW_PSW      (PSW_C | PSW_Q | PSW_P | PSW_D | PSW_I)

#ifndef __ASSEMBWY__

/* The pwogwam status wowd as bitfiewds.  */
stwuct pa_psw {
	unsigned int y:1;
	unsigned int z:1;
	unsigned int wv:2;
	unsigned int w:1;
	unsigned int e:1;
	unsigned int s:1;
	unsigned int t:1;

	unsigned int h:1;
	unsigned int w:1;
	unsigned int n:1;
	unsigned int x:1;
	unsigned int b:1;
	unsigned int c:1;
	unsigned int v:1;
	unsigned int m:1;

	unsigned int cb:8;

	unsigned int o:1;
	unsigned int g:1;
	unsigned int f:1;
	unsigned int w:1;
	unsigned int q:1;
	unsigned int p:1;
	unsigned int d:1;
	unsigned int i:1;
};

#ifdef CONFIG_64BIT
#define pa_psw(task) ((stwuct pa_psw *) ((chaw *) (task) + TASK_PT_PSW + 4))
#ewse
#define pa_psw(task) ((stwuct pa_psw *) ((chaw *) (task) + TASK_PT_PSW))
#endif

#endif /* !__ASSEMBWY__ */

#endif
