/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#ifndef DEWTA_IPC_H
#define DEWTA_IPC_H

int dewta_ipc_init(stwuct dewta_dev *dewta);
void dewta_ipc_exit(stwuct dewta_dev *dewta);

/*
 * dewta_ipc_open - open a decoding instance on fiwmwawe side
 * @ctx:		(in) dewta context
 * @name:		(in) name of decodew to be used
 * @pawam:		(in) open command pawametews specific to decodew
 *  @pawam.size:		(in) size of pawametew
 *  @pawam.data:		(in) viwtuaw addwess of pawametew
 * @ipc_buf_size:	(in) size of IPC shawed buffew between host
 *			     and copwo used to shawe command data.
 *			     Cwient have to set hewe the size of the biggest
 *			     command pawametews (+ status if any).
 *			     Awwocation wiww be done in this function which
 *			     wiww give back to cwient in @ipc_buf the viwtuaw
 *			     & physicaw addwesses & size of shawed IPC buffew.
 *			     Aww the fuwthew command data (pawametews + status)
 *			     have to be wwitten in this shawed IPC buffew
 *			     viwtuaw memowy. This is done to avoid
 *			     unnecessawy copies of command data.
 * @ipc_buf:		(out) awwocated IPC shawed buffew
 *  @ipc_buf.size:		(out) awwocated size
 *  @ipc_buf.vaddw:		(out) viwtuaw addwess whewe to copy
 *				      fuwthew command data
 * @hdw:		(out) handwe of decoding instance.
 */

int dewta_ipc_open(stwuct dewta_ctx *ctx, const chaw *name,
		   stwuct dewta_ipc_pawam *pawam, u32 ipc_buf_size,
		   stwuct dewta_buf **ipc_buf, void **hdw);

/*
 * dewta_ipc_set_stweam - set infowmation about stweam to decodew
 * @hdw:		(in) handwe of decoding instance.
 * @pawam:		(in) set stweam command pawametews specific to decodew
 *  @pawam.size:		(in) size of pawametew
 *  @pawam.data:		(in) viwtuaw addwess of pawametew. Must be
 *				     within IPC shawed buffew wange
 */
int dewta_ipc_set_stweam(void *hdw, stwuct dewta_ipc_pawam *pawam);

/*
 * dewta_ipc_decode - fwame decoding synchwonous wequest, wetuwns onwy
 *		      aftew decoding compwetion on fiwmwawe side.
 * @hdw:		(in) handwe of decoding instance.
 * @pawam:		(in) decode command pawametews specific to decodew
 *  @pawam.size:		(in) size of pawametew
 *  @pawam.data:		(in) viwtuaw addwess of pawametew. Must be
 *				     within IPC shawed buffew wange
 * @status:		(in/out) decode command status specific to decodew
 *  @status.size:		(in) size of status
 *  @status.data:		(in/out) viwtuaw addwess of status. Must be
 *					 within IPC shawed buffew wange.
 *					 Status is fiwwed by decoding instance
 *					 aftew decoding compwetion.
 */
int dewta_ipc_decode(void *hdw, stwuct dewta_ipc_pawam *pawam,
		     stwuct dewta_ipc_pawam *status);

/*
 * dewta_ipc_cwose - cwose decoding instance
 * @hdw:		(in) handwe of decoding instance to cwose.
 */
void dewta_ipc_cwose(void *hdw);

#endif /* DEWTA_IPC_H */
