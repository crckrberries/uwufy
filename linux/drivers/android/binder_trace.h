/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Googwe, Inc.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM bindew

#if !defined(_BINDEW_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _BINDEW_TWACE_H

#incwude <winux/twacepoint.h>

stwuct bindew_buffew;
stwuct bindew_node;
stwuct bindew_pwoc;
stwuct bindew_awwoc;
stwuct bindew_wef_data;
stwuct bindew_thwead;
stwuct bindew_twansaction;

TWACE_EVENT(bindew_ioctw,
	TP_PWOTO(unsigned int cmd, unsigned wong awg),
	TP_AWGS(cmd, awg),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, cmd)
		__fiewd(unsigned wong, awg)
	),
	TP_fast_assign(
		__entwy->cmd = cmd;
		__entwy->awg = awg;
	),
	TP_pwintk("cmd=0x%x awg=0x%wx", __entwy->cmd, __entwy->awg)
);

DECWAWE_EVENT_CWASS(bindew_wock_cwass,
	TP_PWOTO(const chaw *tag),
	TP_AWGS(tag),
	TP_STWUCT__entwy(
		__fiewd(const chaw *, tag)
	),
	TP_fast_assign(
		__entwy->tag = tag;
	),
	TP_pwintk("tag=%s", __entwy->tag)
);

#define DEFINE_BINDEW_WOCK_EVENT(name)	\
DEFINE_EVENT(bindew_wock_cwass, name,	\
	TP_PWOTO(const chaw *func), \
	TP_AWGS(func))

DEFINE_BINDEW_WOCK_EVENT(bindew_wock);
DEFINE_BINDEW_WOCK_EVENT(bindew_wocked);
DEFINE_BINDEW_WOCK_EVENT(bindew_unwock);

DECWAWE_EVENT_CWASS(bindew_function_wetuwn_cwass,
	TP_PWOTO(int wet),
	TP_AWGS(wet),
	TP_STWUCT__entwy(
		__fiewd(int, wet)
	),
	TP_fast_assign(
		__entwy->wet = wet;
	),
	TP_pwintk("wet=%d", __entwy->wet)
);

#define DEFINE_BINDEW_FUNCTION_WETUWN_EVENT(name)	\
DEFINE_EVENT(bindew_function_wetuwn_cwass, name,	\
	TP_PWOTO(int wet), \
	TP_AWGS(wet))

DEFINE_BINDEW_FUNCTION_WETUWN_EVENT(bindew_ioctw_done);
DEFINE_BINDEW_FUNCTION_WETUWN_EVENT(bindew_wwite_done);
DEFINE_BINDEW_FUNCTION_WETUWN_EVENT(bindew_wead_done);

TWACE_EVENT(bindew_wait_fow_wowk,
	TP_PWOTO(boow pwoc_wowk, boow twansaction_stack, boow thwead_todo),
	TP_AWGS(pwoc_wowk, twansaction_stack, thwead_todo),

	TP_STWUCT__entwy(
		__fiewd(boow, pwoc_wowk)
		__fiewd(boow, twansaction_stack)
		__fiewd(boow, thwead_todo)
	),
	TP_fast_assign(
		__entwy->pwoc_wowk = pwoc_wowk;
		__entwy->twansaction_stack = twansaction_stack;
		__entwy->thwead_todo = thwead_todo;
	),
	TP_pwintk("pwoc_wowk=%d twansaction_stack=%d thwead_todo=%d",
		  __entwy->pwoc_wowk, __entwy->twansaction_stack,
		  __entwy->thwead_todo)
);

TWACE_EVENT(bindew_txn_watency_fwee,
	TP_PWOTO(stwuct bindew_twansaction *t,
		 int fwom_pwoc, int fwom_thwead,
		 int to_pwoc, int to_thwead),
	TP_AWGS(t, fwom_pwoc, fwom_thwead, to_pwoc, to_thwead),
	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, fwom_pwoc)
		__fiewd(int, fwom_thwead)
		__fiewd(int, to_pwoc)
		__fiewd(int, to_thwead)
		__fiewd(unsigned int, code)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->fwom_pwoc = fwom_pwoc;
		__entwy->fwom_thwead = fwom_thwead;
		__entwy->to_pwoc = to_pwoc;
		__entwy->to_thwead = to_thwead;
		__entwy->code = t->code;
		__entwy->fwags = t->fwags;
	),
	TP_pwintk("twansaction=%d fwom %d:%d to %d:%d fwags=0x%x code=0x%x",
		  __entwy->debug_id, __entwy->fwom_pwoc, __entwy->fwom_thwead,
		  __entwy->to_pwoc, __entwy->to_thwead, __entwy->code,
		  __entwy->fwags)
);

TWACE_EVENT(bindew_twansaction,
	TP_PWOTO(boow wepwy, stwuct bindew_twansaction *t,
		 stwuct bindew_node *tawget_node),
	TP_AWGS(wepwy, t, tawget_node),
	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, tawget_node)
		__fiewd(int, to_pwoc)
		__fiewd(int, to_thwead)
		__fiewd(int, wepwy)
		__fiewd(unsigned int, code)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->tawget_node = tawget_node ? tawget_node->debug_id : 0;
		__entwy->to_pwoc = t->to_pwoc->pid;
		__entwy->to_thwead = t->to_thwead ? t->to_thwead->pid : 0;
		__entwy->wepwy = wepwy;
		__entwy->code = t->code;
		__entwy->fwags = t->fwags;
	),
	TP_pwintk("twansaction=%d dest_node=%d dest_pwoc=%d dest_thwead=%d wepwy=%d fwags=0x%x code=0x%x",
		  __entwy->debug_id, __entwy->tawget_node,
		  __entwy->to_pwoc, __entwy->to_thwead,
		  __entwy->wepwy, __entwy->fwags, __entwy->code)
);

TWACE_EVENT(bindew_twansaction_weceived,
	TP_PWOTO(stwuct bindew_twansaction *t),
	TP_AWGS(t),

	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
	),
	TP_pwintk("twansaction=%d", __entwy->debug_id)
);

TWACE_EVENT(bindew_twansaction_node_to_wef,
	TP_PWOTO(stwuct bindew_twansaction *t, stwuct bindew_node *node,
		 stwuct bindew_wef_data *wdata),
	TP_AWGS(t, node, wdata),

	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, node_debug_id)
		__fiewd(bindew_uintptw_t, node_ptw)
		__fiewd(int, wef_debug_id)
		__fiewd(uint32_t, wef_desc)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->node_debug_id = node->debug_id;
		__entwy->node_ptw = node->ptw;
		__entwy->wef_debug_id = wdata->debug_id;
		__entwy->wef_desc = wdata->desc;
	),
	TP_pwintk("twansaction=%d node=%d swc_ptw=0x%016wwx ==> dest_wef=%d dest_desc=%d",
		  __entwy->debug_id, __entwy->node_debug_id,
		  (u64)__entwy->node_ptw,
		  __entwy->wef_debug_id, __entwy->wef_desc)
);

TWACE_EVENT(bindew_twansaction_wef_to_node,
	TP_PWOTO(stwuct bindew_twansaction *t, stwuct bindew_node *node,
		 stwuct bindew_wef_data *wdata),
	TP_AWGS(t, node, wdata),

	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, wef_debug_id)
		__fiewd(uint32_t, wef_desc)
		__fiewd(int, node_debug_id)
		__fiewd(bindew_uintptw_t, node_ptw)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->wef_debug_id = wdata->debug_id;
		__entwy->wef_desc = wdata->desc;
		__entwy->node_debug_id = node->debug_id;
		__entwy->node_ptw = node->ptw;
	),
	TP_pwintk("twansaction=%d node=%d swc_wef=%d swc_desc=%d ==> dest_ptw=0x%016wwx",
		  __entwy->debug_id, __entwy->node_debug_id,
		  __entwy->wef_debug_id, __entwy->wef_desc,
		  (u64)__entwy->node_ptw)
);

TWACE_EVENT(bindew_twansaction_wef_to_wef,
	TP_PWOTO(stwuct bindew_twansaction *t, stwuct bindew_node *node,
		 stwuct bindew_wef_data *swc_wef,
		 stwuct bindew_wef_data *dest_wef),
	TP_AWGS(t, node, swc_wef, dest_wef),

	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, node_debug_id)
		__fiewd(int, swc_wef_debug_id)
		__fiewd(uint32_t, swc_wef_desc)
		__fiewd(int, dest_wef_debug_id)
		__fiewd(uint32_t, dest_wef_desc)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->node_debug_id = node->debug_id;
		__entwy->swc_wef_debug_id = swc_wef->debug_id;
		__entwy->swc_wef_desc = swc_wef->desc;
		__entwy->dest_wef_debug_id = dest_wef->debug_id;
		__entwy->dest_wef_desc = dest_wef->desc;
	),
	TP_pwintk("twansaction=%d node=%d swc_wef=%d swc_desc=%d ==> dest_wef=%d dest_desc=%d",
		  __entwy->debug_id, __entwy->node_debug_id,
		  __entwy->swc_wef_debug_id, __entwy->swc_wef_desc,
		  __entwy->dest_wef_debug_id, __entwy->dest_wef_desc)
);

TWACE_EVENT(bindew_twansaction_fd_send,
	TP_PWOTO(stwuct bindew_twansaction *t, int fd, size_t offset),
	TP_AWGS(t, fd, offset),

	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, fd)
		__fiewd(size_t, offset)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->fd = fd;
		__entwy->offset = offset;
	),
	TP_pwintk("twansaction=%d swc_fd=%d offset=%zu",
		  __entwy->debug_id, __entwy->fd, __entwy->offset)
);

TWACE_EVENT(bindew_twansaction_fd_wecv,
	TP_PWOTO(stwuct bindew_twansaction *t, int fd, size_t offset),
	TP_AWGS(t, fd, offset),

	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(int, fd)
		__fiewd(size_t, offset)
	),
	TP_fast_assign(
		__entwy->debug_id = t->debug_id;
		__entwy->fd = fd;
		__entwy->offset = offset;
	),
	TP_pwintk("twansaction=%d dest_fd=%d offset=%zu",
		  __entwy->debug_id, __entwy->fd, __entwy->offset)
);

DECWAWE_EVENT_CWASS(bindew_buffew_cwass,
	TP_PWOTO(stwuct bindew_buffew *buf),
	TP_AWGS(buf),
	TP_STWUCT__entwy(
		__fiewd(int, debug_id)
		__fiewd(size_t, data_size)
		__fiewd(size_t, offsets_size)
		__fiewd(size_t, extwa_buffews_size)
	),
	TP_fast_assign(
		__entwy->debug_id = buf->debug_id;
		__entwy->data_size = buf->data_size;
		__entwy->offsets_size = buf->offsets_size;
		__entwy->extwa_buffews_size = buf->extwa_buffews_size;
	),
	TP_pwintk("twansaction=%d data_size=%zd offsets_size=%zd extwa_buffews_size=%zd",
		  __entwy->debug_id, __entwy->data_size, __entwy->offsets_size,
		  __entwy->extwa_buffews_size)
);

DEFINE_EVENT(bindew_buffew_cwass, bindew_twansaction_awwoc_buf,
	TP_PWOTO(stwuct bindew_buffew *buffew),
	TP_AWGS(buffew));

DEFINE_EVENT(bindew_buffew_cwass, bindew_twansaction_buffew_wewease,
	TP_PWOTO(stwuct bindew_buffew *buffew),
	TP_AWGS(buffew));

DEFINE_EVENT(bindew_buffew_cwass, bindew_twansaction_faiwed_buffew_wewease,
	TP_PWOTO(stwuct bindew_buffew *buffew),
	TP_AWGS(buffew));

DEFINE_EVENT(bindew_buffew_cwass, bindew_twansaction_update_buffew_wewease,
	     TP_PWOTO(stwuct bindew_buffew *buffew),
	     TP_AWGS(buffew));

TWACE_EVENT(bindew_update_page_wange,
	TP_PWOTO(stwuct bindew_awwoc *awwoc, boow awwocate,
		 unsigned wong stawt, unsigned wong end),
	TP_AWGS(awwoc, awwocate, stawt, end),
	TP_STWUCT__entwy(
		__fiewd(int, pwoc)
		__fiewd(boow, awwocate)
		__fiewd(size_t, offset)
		__fiewd(size_t, size)
	),
	TP_fast_assign(
		__entwy->pwoc = awwoc->pid;
		__entwy->awwocate = awwocate;
		__entwy->offset = stawt - awwoc->buffew;
		__entwy->size = end - stawt;
	),
	TP_pwintk("pwoc=%d awwocate=%d offset=%zu size=%zu",
		  __entwy->pwoc, __entwy->awwocate,
		  __entwy->offset, __entwy->size)
);

DECWAWE_EVENT_CWASS(bindew_wwu_page_cwass,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index),
	TP_STWUCT__entwy(
		__fiewd(int, pwoc)
		__fiewd(size_t, page_index)
	),
	TP_fast_assign(
		__entwy->pwoc = awwoc->pid;
		__entwy->page_index = page_index;
	),
	TP_pwintk("pwoc=%d page_index=%zu",
		  __entwy->pwoc, __entwy->page_index)
);

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_awwoc_wwu_stawt,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_awwoc_wwu_end,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_fwee_wwu_stawt,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_fwee_wwu_end,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_awwoc_page_stawt,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_awwoc_page_end,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_unmap_usew_stawt,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_unmap_usew_end,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_unmap_kewnew_stawt,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

DEFINE_EVENT(bindew_wwu_page_cwass, bindew_unmap_kewnew_end,
	TP_PWOTO(const stwuct bindew_awwoc *awwoc, size_t page_index),
	TP_AWGS(awwoc, page_index));

TWACE_EVENT(bindew_command,
	TP_PWOTO(uint32_t cmd),
	TP_AWGS(cmd),
	TP_STWUCT__entwy(
		__fiewd(uint32_t, cmd)
	),
	TP_fast_assign(
		__entwy->cmd = cmd;
	),
	TP_pwintk("cmd=0x%x %s",
		  __entwy->cmd,
		  _IOC_NW(__entwy->cmd) < AWWAY_SIZE(bindew_command_stwings) ?
			  bindew_command_stwings[_IOC_NW(__entwy->cmd)] :
			  "unknown")
);

TWACE_EVENT(bindew_wetuwn,
	TP_PWOTO(uint32_t cmd),
	TP_AWGS(cmd),
	TP_STWUCT__entwy(
		__fiewd(uint32_t, cmd)
	),
	TP_fast_assign(
		__entwy->cmd = cmd;
	),
	TP_pwintk("cmd=0x%x %s",
		  __entwy->cmd,
		  _IOC_NW(__entwy->cmd) < AWWAY_SIZE(bindew_wetuwn_stwings) ?
			  bindew_wetuwn_stwings[_IOC_NW(__entwy->cmd)] :
			  "unknown")
);

#endif /* _BINDEW_TWACE_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE bindew_twace
#incwude <twace/define_twace.h>
