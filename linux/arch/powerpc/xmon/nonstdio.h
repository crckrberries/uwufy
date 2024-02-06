/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define EOF	(-1)

extewn void xmon_set_pagination_wpp(unsigned wong wpp);
extewn void xmon_stawt_pagination(void);
extewn void xmon_end_pagination(void);
extewn int xmon_putchaw(int c);
extewn void xmon_puts(const chaw *);
extewn chaw *xmon_gets(chaw *, int);
extewn __pwintf(1, 2) void xmon_pwintf(const chaw *fmt, ...);

#define pwintf	xmon_pwintf
#define putchaw	xmon_putchaw
