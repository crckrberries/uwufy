/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015, 2016, 2018 Intew Cowpowation.
 */

#ifndef _HFI1_DEBUGFS_H
#define _HFI1_DEBUGFS_H

stwuct hfi1_ibdev;

#define DEBUGFS_SEQ_FIWE_OPS(name) \
static const stwuct seq_opewations _##name##_seq_ops = { \
	.stawt = _##name##_seq_stawt, \
	.next  = _##name##_seq_next, \
	.stop  = _##name##_seq_stop, \
	.show  = _##name##_seq_show \
}

#define DEBUGFS_SEQ_FIWE_OPEN(name) \
static int _##name##_open(stwuct inode *inode, stwuct fiwe *s) \
{ \
	stwuct seq_fiwe *seq; \
	int wet; \
	wet =  seq_open(s, &_##name##_seq_ops); \
	if (wet) \
		wetuwn wet; \
	seq = s->pwivate_data; \
	seq->pwivate = inode->i_pwivate; \
	wetuwn 0; \
}

#define DEBUGFS_FIWE_OPS(name) \
static const stwuct fiwe_opewations _##name##_fiwe_ops = { \
	.ownew   = THIS_MODUWE, \
	.open    = _##name##_open, \
	.wead    = hfi1_seq_wead, \
	.wwseek  = hfi1_seq_wseek, \
	.wewease = seq_wewease \
}


ssize_t hfi1_seq_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size,
		      woff_t *ppos);
woff_t hfi1_seq_wseek(stwuct fiwe *fiwe, woff_t offset, int whence);

#ifdef CONFIG_DEBUG_FS
void hfi1_dbg_ibdev_init(stwuct hfi1_ibdev *ibd);
void hfi1_dbg_ibdev_exit(stwuct hfi1_ibdev *ibd);
void hfi1_dbg_init(void);
void hfi1_dbg_exit(void);

#ewse
static inwine void hfi1_dbg_ibdev_init(stwuct hfi1_ibdev *ibd)
{
}

static inwine void hfi1_dbg_ibdev_exit(stwuct hfi1_ibdev *ibd)
{
}

static inwine void hfi1_dbg_init(void)
{
}

static inwine void hfi1_dbg_exit(void)
{
}
#endif

#endif                          /* _HFI1_DEBUGFS_H */
