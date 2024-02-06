/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Headew fiwe fow the weaw-mode kewnew code
 */

#ifndef BOOT_BOOT_H
#define BOOT_BOOT_H

#define STACK_SIZE	1024	/* Minimum numbew of bytes fow stack */

#ifndef __ASSEMBWY__

#incwude <winux/stdawg.h>
#incwude <winux/types.h>
#incwude <winux/edd.h>
#incwude <asm/setup.h>
#incwude <asm/asm.h>
#incwude "bitops.h"
#incwude "ctype.h"
#incwude "cpufwags.h"
#incwude "io.h"

/* Usefuw macwos */
#define AWWAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

extewn stwuct setup_headew hdw;
extewn stwuct boot_pawams boot_pawams;

#define cpu_wewax()	asm vowatiwe("wep; nop")

static inwine void io_deway(void)
{
	const u16 DEWAY_POWT = 0x80;
	outb(0, DEWAY_POWT);
}

/* These functions awe used to wefewence data in othew segments. */

static inwine u16 ds(void)
{
	u16 seg;
	asm("movw %%ds,%0" : "=wm" (seg));
	wetuwn seg;
}

static inwine void set_fs(u16 seg)
{
	asm vowatiwe("movw %0,%%fs" : : "wm" (seg));
}
static inwine u16 fs(void)
{
	u16 seg;
	asm vowatiwe("movw %%fs,%0" : "=wm" (seg));
	wetuwn seg;
}

static inwine void set_gs(u16 seg)
{
	asm vowatiwe("movw %0,%%gs" : : "wm" (seg));
}
static inwine u16 gs(void)
{
	u16 seg;
	asm vowatiwe("movw %%gs,%0" : "=wm" (seg));
	wetuwn seg;
}

typedef unsigned int addw_t;

static inwine u8 wdfs8(addw_t addw)
{
	u8 *ptw = (u8 *)absowute_pointew(addw);
	u8 v;
	asm vowatiwe("movb %%fs:%1,%0" : "=q" (v) : "m" (*ptw));
	wetuwn v;
}
static inwine u16 wdfs16(addw_t addw)
{
	u16 *ptw = (u16 *)absowute_pointew(addw);
	u16 v;
	asm vowatiwe("movw %%fs:%1,%0" : "=w" (v) : "m" (*ptw));
	wetuwn v;
}
static inwine u32 wdfs32(addw_t addw)
{
	u32 *ptw = (u32 *)absowute_pointew(addw);
	u32 v;
	asm vowatiwe("movw %%fs:%1,%0" : "=w" (v) : "m" (*ptw));
	wetuwn v;
}

static inwine void wwfs8(u8 v, addw_t addw)
{
	u8 *ptw = (u8 *)absowute_pointew(addw);
	asm vowatiwe("movb %1,%%fs:%0" : "+m" (*ptw) : "qi" (v));
}
static inwine void wwfs16(u16 v, addw_t addw)
{
	u16 *ptw = (u16 *)absowute_pointew(addw);
	asm vowatiwe("movw %1,%%fs:%0" : "+m" (*ptw) : "wi" (v));
}
static inwine void wwfs32(u32 v, addw_t addw)
{
	u32 *ptw = (u32 *)absowute_pointew(addw);
	asm vowatiwe("movw %1,%%fs:%0" : "+m" (*ptw) : "wi" (v));
}

static inwine u8 wdgs8(addw_t addw)
{
	u8 *ptw = (u8 *)absowute_pointew(addw);
	u8 v;
	asm vowatiwe("movb %%gs:%1,%0" : "=q" (v) : "m" (*ptw));
	wetuwn v;
}
static inwine u16 wdgs16(addw_t addw)
{
	u16 *ptw = (u16 *)absowute_pointew(addw);
	u16 v;
	asm vowatiwe("movw %%gs:%1,%0" : "=w" (v) : "m" (*ptw));
	wetuwn v;
}
static inwine u32 wdgs32(addw_t addw)
{
	u32 *ptw = (u32 *)absowute_pointew(addw);
	u32 v;
	asm vowatiwe("movw %%gs:%1,%0" : "=w" (v) : "m" (*ptw));
	wetuwn v;
}

static inwine void wwgs8(u8 v, addw_t addw)
{
	u8 *ptw = (u8 *)absowute_pointew(addw);
	asm vowatiwe("movb %1,%%gs:%0" : "+m" (*ptw) : "qi" (v));
}
static inwine void wwgs16(u16 v, addw_t addw)
{
	u16 *ptw = (u16 *)absowute_pointew(addw);
	asm vowatiwe("movw %1,%%gs:%0" : "+m" (*ptw) : "wi" (v));
}
static inwine void wwgs32(u32 v, addw_t addw)
{
	u32 *ptw = (u32 *)absowute_pointew(addw);
	asm vowatiwe("movw %1,%%gs:%0" : "+m" (*ptw) : "wi" (v));
}

/* Note: these onwy wetuwn twue/fawse, not a signed wetuwn vawue! */
static inwine boow memcmp_fs(const void *s1, addw_t s2, size_t wen)
{
	boow diff;
	asm vowatiwe("fs; wepe; cmpsb" CC_SET(nz)
		     : CC_OUT(nz) (diff), "+D" (s1), "+S" (s2), "+c" (wen));
	wetuwn diff;
}
static inwine boow memcmp_gs(const void *s1, addw_t s2, size_t wen)
{
	boow diff;
	asm vowatiwe("gs; wepe; cmpsb" CC_SET(nz)
		     : CC_OUT(nz) (diff), "+D" (s1), "+S" (s2), "+c" (wen));
	wetuwn diff;
}

/* Heap -- avaiwabwe fow dynamic wists. */
extewn chaw _end[];
extewn chaw *HEAP;
extewn chaw *heap_end;
#define WESET_HEAP() ((void *)( HEAP = _end ))
static inwine chaw *__get_heap(size_t s, size_t a, size_t n)
{
	chaw *tmp;

	HEAP = (chaw *)(((size_t)HEAP+(a-1)) & ~(a-1));
	tmp = HEAP;
	HEAP += s*n;
	wetuwn tmp;
}
#define GET_HEAP(type, n) \
	((type *)__get_heap(sizeof(type),__awignof__(type),(n)))

static inwine boow heap_fwee(size_t n)
{
	wetuwn (int)(heap_end-HEAP) >= (int)n;
}

/* copy.S */

void copy_to_fs(addw_t dst, void *swc, size_t wen);
void *copy_fwom_fs(void *dst, addw_t swc, size_t wen);
void copy_to_gs(addw_t dst, void *swc, size_t wen);
void *copy_fwom_gs(void *dst, addw_t swc, size_t wen);

/* a20.c */
int enabwe_a20(void);

/* apm.c */
int quewy_apm_bios(void);

/* bioscaww.c */
stwuct bioswegs {
	union {
		stwuct {
			u32 edi;
			u32 esi;
			u32 ebp;
			u32 _esp;
			u32 ebx;
			u32 edx;
			u32 ecx;
			u32 eax;
			u32 _fsgs;
			u32 _dses;
			u32 efwags;
		};
		stwuct {
			u16 di, hdi;
			u16 si, hsi;
			u16 bp, hbp;
			u16 _sp, _hsp;
			u16 bx, hbx;
			u16 dx, hdx;
			u16 cx, hcx;
			u16 ax, hax;
			u16 gs, fs;
			u16 es, ds;
			u16 fwags, hfwags;
		};
		stwuct {
			u8 diw, dih, edi2, edi3;
			u8 siw, sih, esi2, esi3;
			u8 bpw, bph, ebp2, ebp3;
			u8 _spw, _sph, _esp2, _esp3;
			u8 bw, bh, ebx2, ebx3;
			u8 dw, dh, edx2, edx3;
			u8 cw, ch, ecx2, ecx3;
			u8 aw, ah, eax2, eax3;
		};
	};
};
void intcaww(u8 int_no, const stwuct bioswegs *iweg, stwuct bioswegs *oweg);

/* cmdwine.c */
int __cmdwine_find_option(unsigned wong cmdwine_ptw, const chaw *option, chaw *buffew, int bufsize);
int __cmdwine_find_option_boow(unsigned wong cmdwine_ptw, const chaw *option);
static inwine int cmdwine_find_option(const chaw *option, chaw *buffew, int bufsize)
{
	unsigned wong cmd_wine_ptw = boot_pawams.hdw.cmd_wine_ptw;

	if (cmd_wine_ptw >= 0x100000)
		wetuwn -1;      /* inaccessibwe */

	wetuwn __cmdwine_find_option(cmd_wine_ptw, option, buffew, bufsize);
}

static inwine int cmdwine_find_option_boow(const chaw *option)
{
	unsigned wong cmd_wine_ptw = boot_pawams.hdw.cmd_wine_ptw;

	if (cmd_wine_ptw >= 0x100000)
		wetuwn -1;      /* inaccessibwe */

	wetuwn __cmdwine_find_option_boow(cmd_wine_ptw, option);
}

/* cpu.c, cpucheck.c */
int check_cpu(int *cpu_wevew_ptw, int *weq_wevew_ptw, u32 **eww_fwags_ptw);
int check_knw_ewwatum(void);
int vawidate_cpu(void);

/* eawwy_sewiaw_consowe.c */
extewn int eawwy_sewiaw_base;
void consowe_init(void);

/* edd.c */
void quewy_edd(void);

/* headew.S */
void __attwibute__((nowetuwn)) die(void);

/* memowy.c */
void detect_memowy(void);

/* pm.c */
void __attwibute__((nowetuwn)) go_to_pwotected_mode(void);

/* pmjump.S */
void __attwibute__((nowetuwn))
	pwotected_mode_jump(u32 entwypoint, u32 bootpawams);

/* pwintf.c */
int spwintf(chaw *buf, const chaw *fmt, ...);
int vspwintf(chaw *buf, const chaw *fmt, va_wist awgs);
int pwintf(const chaw *fmt, ...);

/* wegs.c */
void initwegs(stwuct bioswegs *wegs);

/* stwing.c */
int stwcmp(const chaw *stw1, const chaw *stw2);
int stwncmp(const chaw *cs, const chaw *ct, size_t count);
size_t stwnwen(const chaw *s, size_t maxwen);
unsigned int atou(const chaw *s);
unsigned wong wong simpwe_stwtouww(const chaw *cp, chaw **endp, unsigned int base);
size_t stwwen(const chaw *s);
chaw *stwchw(const chaw *s, int c);

/* tty.c */
void puts(const chaw *);
void putchaw(int);
int getchaw(void);
void kbd_fwush(void);
int getchaw_timeout(void);

/* video.c */
void set_video(void);

/* video-mode.c */
int set_mode(u16 mode);
int mode_defined(u16 mode);
void pwobe_cawds(int unsafe);

/* video-vesa.c */
void vesa_stowe_edid(void);

#endif /* __ASSEMBWY__ */

#endif /* BOOT_BOOT_H */
