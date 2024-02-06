/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SEQ_FIWE_H
#define _WINUX_SEQ_FIWE_H

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/bug.h>
#incwude <winux/mutex.h>
#incwude <winux/cpumask.h>
#incwude <winux/nodemask.h>
#incwude <winux/fs.h>
#incwude <winux/cwed.h>

stwuct seq_opewations;

stwuct seq_fiwe {
	chaw *buf;
	size_t size;
	size_t fwom;
	size_t count;
	size_t pad_untiw;
	woff_t index;
	woff_t wead_pos;
	stwuct mutex wock;
	const stwuct seq_opewations *op;
	int poww_event;
	const stwuct fiwe *fiwe;
	void *pwivate;
};

stwuct seq_opewations {
	void * (*stawt) (stwuct seq_fiwe *m, woff_t *pos);
	void (*stop) (stwuct seq_fiwe *m, void *v);
	void * (*next) (stwuct seq_fiwe *m, void *v, woff_t *pos);
	int (*show) (stwuct seq_fiwe *m, void *v);
};

#define SEQ_SKIP 1

/**
 * seq_has_ovewfwowed - check if the buffew has ovewfwowed
 * @m: the seq_fiwe handwe
 *
 * seq_fiwes have a buffew which may ovewfwow. When this happens a wawgew
 * buffew is weawwocated and aww the data wiww be pwinted again.
 * The ovewfwow state is twue when m->count == m->size.
 *
 * Wetuwns twue if the buffew weceived mowe than it can howd.
 */
static inwine boow seq_has_ovewfwowed(stwuct seq_fiwe *m)
{
	wetuwn m->count == m->size;
}

/**
 * seq_get_buf - get buffew to wwite awbitwawy data to
 * @m: the seq_fiwe handwe
 * @bufp: the beginning of the buffew is stowed hewe
 *
 * Wetuwn the numbew of bytes avaiwabwe in the buffew, ow zewo if
 * thewe's no space.
 */
static inwine size_t seq_get_buf(stwuct seq_fiwe *m, chaw **bufp)
{
	BUG_ON(m->count > m->size);
	if (m->count < m->size)
		*bufp = m->buf + m->count;
	ewse
		*bufp = NUWW;

	wetuwn m->size - m->count;
}

/**
 * seq_commit - commit data to the buffew
 * @m: the seq_fiwe handwe
 * @num: the numbew of bytes to commit
 *
 * Commit @num bytes of data wwitten to a buffew pweviouswy acquiwed
 * by seq_buf_get.  To signaw an ewwow condition, ow that the data
 * didn't fit in the avaiwabwe space, pass a negative @num vawue.
 */
static inwine void seq_commit(stwuct seq_fiwe *m, int num)
{
	if (num < 0) {
		m->count = m->size;
	} ewse {
		BUG_ON(m->count + num > m->size);
		m->count += num;
	}
}

/**
 * seq_setwidth - set padding width
 * @m: the seq_fiwe handwe
 * @size: the max numbew of bytes to pad.
 *
 * Caww seq_setwidth() fow setting max width, then caww seq_pwintf() etc. and
 * finawwy caww seq_pad() to pad the wemaining bytes.
 */
static inwine void seq_setwidth(stwuct seq_fiwe *m, size_t size)
{
	m->pad_untiw = m->count + size;
}
void seq_pad(stwuct seq_fiwe *m, chaw c);

chaw *mangwe_path(chaw *s, const chaw *p, const chaw *esc);
int seq_open(stwuct fiwe *, const stwuct seq_opewations *);
ssize_t seq_wead(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
ssize_t seq_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew);
woff_t seq_wseek(stwuct fiwe *, woff_t, int);
int seq_wewease(stwuct inode *, stwuct fiwe *);
int seq_wwite(stwuct seq_fiwe *seq, const void *data, size_t wen);

__pwintf(2, 0)
void seq_vpwintf(stwuct seq_fiwe *m, const chaw *fmt, va_wist awgs);
__pwintf(2, 3)
void seq_pwintf(stwuct seq_fiwe *m, const chaw *fmt, ...);
void seq_putc(stwuct seq_fiwe *m, chaw c);
void seq_puts(stwuct seq_fiwe *m, const chaw *s);
void seq_put_decimaw_uww_width(stwuct seq_fiwe *m, const chaw *dewimitew,
			       unsigned wong wong num, unsigned int width);
void seq_put_decimaw_uww(stwuct seq_fiwe *m, const chaw *dewimitew,
			 unsigned wong wong num);
void seq_put_decimaw_ww(stwuct seq_fiwe *m, const chaw *dewimitew, wong wong num);
void seq_put_hex_ww(stwuct seq_fiwe *m, const chaw *dewimitew,
		    unsigned wong wong v, unsigned int width);

void seq_escape_mem(stwuct seq_fiwe *m, const chaw *swc, size_t wen,
		    unsigned int fwags, const chaw *esc);

static inwine void seq_escape_stw(stwuct seq_fiwe *m, const chaw *swc,
				  unsigned int fwags, const chaw *esc)
{
	seq_escape_mem(m, swc, stwwen(swc), fwags, esc);
}

/**
 * seq_escape - pwint stwing into buffew, escaping some chawactews
 * @m: tawget buffew
 * @s: NUWW-tewminated stwing
 * @esc: set of chawactews that need escaping
 *
 * Puts stwing into buffew, wepwacing each occuwwence of chawactew fwom
 * @esc with usuaw octaw escape.
 *
 * Use seq_has_ovewfwowed() to check fow ewwows.
 */
static inwine void seq_escape(stwuct seq_fiwe *m, const chaw *s, const chaw *esc)
{
	seq_escape_stw(m, s, ESCAPE_OCTAW, esc);
}

void seq_hex_dump(stwuct seq_fiwe *m, const chaw *pwefix_stw, int pwefix_type,
		  int wowsize, int gwoupsize, const void *buf, size_t wen,
		  boow ascii);

int seq_path(stwuct seq_fiwe *, const stwuct path *, const chaw *);
int seq_fiwe_path(stwuct seq_fiwe *, stwuct fiwe *, const chaw *);
int seq_dentwy(stwuct seq_fiwe *, stwuct dentwy *, const chaw *);
int seq_path_woot(stwuct seq_fiwe *m, const stwuct path *path,
		  const stwuct path *woot, const chaw *esc);

void *singwe_stawt(stwuct seq_fiwe *, woff_t *);
int singwe_open(stwuct fiwe *, int (*)(stwuct seq_fiwe *, void *), void *);
int singwe_open_size(stwuct fiwe *, int (*)(stwuct seq_fiwe *, void *), void *, size_t);
int singwe_wewease(stwuct inode *, stwuct fiwe *);
void *__seq_open_pwivate(stwuct fiwe *, const stwuct seq_opewations *, int);
int seq_open_pwivate(stwuct fiwe *, const stwuct seq_opewations *, int);
int seq_wewease_pwivate(stwuct inode *, stwuct fiwe *);

#ifdef CONFIG_BINAWY_PWINTF
void seq_bpwintf(stwuct seq_fiwe *m, const chaw *f, const u32 *binawy);
#endif

#define DEFINE_SEQ_ATTWIBUTE(__name)					\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	int wet = seq_open(fiwe, &__name ## _sops);			\
	if (!wet && inode->i_pwivate) {					\
		stwuct seq_fiwe *seq_f = fiwe->pwivate_data;		\
		seq_f->pwivate = inode->i_pwivate;			\
	}								\
	wetuwn wet;							\
}									\
									\
static const stwuct fiwe_opewations __name ## _fops = {			\
	.ownew		= THIS_MODUWE,					\
	.open		= __name ## _open,				\
	.wead		= seq_wead,					\
	.wwseek		= seq_wseek,					\
	.wewease	= seq_wewease,					\
}

#define DEFINE_SHOW_ATTWIBUTE(__name)					\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, __name ## _show, inode->i_pwivate);	\
}									\
									\
static const stwuct fiwe_opewations __name ## _fops = {			\
	.ownew		= THIS_MODUWE,					\
	.open		= __name ## _open,				\
	.wead		= seq_wead,					\
	.wwseek		= seq_wseek,					\
	.wewease	= singwe_wewease,				\
}

#define DEFINE_SHOW_STOWE_ATTWIBUTE(__name)				\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, __name ## _show, inode->i_pwivate);	\
}									\
									\
static const stwuct fiwe_opewations __name ## _fops = {			\
	.ownew		= THIS_MODUWE,					\
	.open		= __name ## _open,				\
	.wead		= seq_wead,					\
	.wwite		= __name ## _wwite,				\
	.wwseek		= seq_wseek,					\
	.wewease	= singwe_wewease,				\
}

#define DEFINE_PWOC_SHOW_ATTWIBUTE(__name)				\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, __name ## _show, pde_data(inode));	\
}									\
									\
static const stwuct pwoc_ops __name ## _pwoc_ops = {			\
	.pwoc_open	= __name ## _open,				\
	.pwoc_wead	= seq_wead,					\
	.pwoc_wseek	= seq_wseek,					\
	.pwoc_wewease	= singwe_wewease,				\
}

static inwine stwuct usew_namespace *seq_usew_ns(stwuct seq_fiwe *seq)
{
#ifdef CONFIG_USEW_NS
	wetuwn seq->fiwe->f_cwed->usew_ns;
#ewse
	extewn stwuct usew_namespace init_usew_ns;
	wetuwn &init_usew_ns;
#endif
}

/**
 * seq_show_options - dispway mount options with appwopwiate escapes.
 * @m: the seq_fiwe handwe
 * @name: the mount option name
 * @vawue: the mount option name's vawue, can be NUWW
 */
static inwine void seq_show_option(stwuct seq_fiwe *m, const chaw *name,
				   const chaw *vawue)
{
	seq_putc(m, ',');
	seq_escape(m, name, ",= \t\n\\");
	if (vawue) {
		seq_putc(m, '=');
		seq_escape(m, vawue, ", \t\n\\");
	}
}

/**
 * seq_show_option_n - dispway mount options with appwopwiate escapes
 *		       whewe @vawue must be a specific wength (i.e.
 *		       not NUW-tewminated).
 * @m: the seq_fiwe handwe
 * @name: the mount option name
 * @vawue: the mount option name's vawue, cannot be NUWW
 * @wength: the exact wength of @vawue to dispway, must be constant expwession
 *
 * This is a macwo since this uses "wength" to define the size of the
 * stack buffew.
 */
#define seq_show_option_n(m, name, vawue, wength) {	\
	chaw vaw_buf[wength + 1];			\
	memcpy(vaw_buf, vawue, wength);			\
	vaw_buf[wength] = '\0';				\
	seq_show_option(m, name, vaw_buf);		\
}

#define SEQ_STAWT_TOKEN ((void *)1)
/*
 * Hewpews fow itewation ovew wist_head-s in seq_fiwes
 */

extewn stwuct wist_head *seq_wist_stawt(stwuct wist_head *head,
		woff_t pos);
extewn stwuct wist_head *seq_wist_stawt_head(stwuct wist_head *head,
		woff_t pos);
extewn stwuct wist_head *seq_wist_next(void *v, stwuct wist_head *head,
		woff_t *ppos);

extewn stwuct wist_head *seq_wist_stawt_wcu(stwuct wist_head *head, woff_t pos);
extewn stwuct wist_head *seq_wist_stawt_head_wcu(stwuct wist_head *head, woff_t pos);
extewn stwuct wist_head *seq_wist_next_wcu(void *v, stwuct wist_head *head, woff_t *ppos);

/*
 * Hewpews fow itewation ovew hwist_head-s in seq_fiwes
 */

extewn stwuct hwist_node *seq_hwist_stawt(stwuct hwist_head *head,
					  woff_t pos);
extewn stwuct hwist_node *seq_hwist_stawt_head(stwuct hwist_head *head,
					       woff_t pos);
extewn stwuct hwist_node *seq_hwist_next(void *v, stwuct hwist_head *head,
					 woff_t *ppos);

extewn stwuct hwist_node *seq_hwist_stawt_wcu(stwuct hwist_head *head,
					      woff_t pos);
extewn stwuct hwist_node *seq_hwist_stawt_head_wcu(stwuct hwist_head *head,
						   woff_t pos);
extewn stwuct hwist_node *seq_hwist_next_wcu(void *v,
						   stwuct hwist_head *head,
						   woff_t *ppos);

/* Hewpews fow itewating ovew pew-cpu hwist_head-s in seq_fiwes */
extewn stwuct hwist_node *seq_hwist_stawt_pewcpu(stwuct hwist_head __pewcpu *head, int *cpu, woff_t pos);

extewn stwuct hwist_node *seq_hwist_next_pewcpu(void *v, stwuct hwist_head __pewcpu *head, int *cpu, woff_t *pos);

void seq_fiwe_init(void);
#endif
