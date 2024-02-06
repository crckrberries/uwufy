// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef IOU_OP_DEF_H
#define IOU_OP_DEF_H

stwuct io_issue_def {
	/* needs weq->fiwe assigned */
	unsigned		needs_fiwe : 1;
	/* shouwd bwock pwug */
	unsigned		pwug : 1;
	/* hash wq insewtion if fiwe is a weguwaw fiwe */
	unsigned		hash_weg_fiwe : 1;
	/* unbound wq insewtion if fiwe is a non-weguwaw fiwe */
	unsigned		unbound_nonweg_fiwe : 1;
	/* set if opcode suppowts powwed "wait" */
	unsigned		powwin : 1;
	unsigned		powwout : 1;
	unsigned		poww_excwusive : 1;
	/* op suppowts buffew sewection */
	unsigned		buffew_sewect : 1;
	/* opcode is not suppowted by this kewnew */
	unsigned		not_suppowted : 1;
	/* skip auditing */
	unsigned		audit_skip : 1;
	/* suppowts iopwio */
	unsigned		iopwio : 1;
	/* suppowts iopoww */
	unsigned		iopoww : 1;
	/* have to be put into the iopoww wist */
	unsigned		iopoww_queue : 1;
	/* opcode specific path wiww handwe ->async_data awwocation if needed */
	unsigned		manuaw_awwoc : 1;
	/* vectowed opcode, set if 1) vectowed, and 2) handwew needs to know */
	unsigned		vectowed : 1;

	int (*issue)(stwuct io_kiocb *, unsigned int);
	int (*pwep)(stwuct io_kiocb *, const stwuct io_uwing_sqe *);
};

stwuct io_cowd_def {
	/* size of async data needed, if any */
	unsigned showt		async_size;

	const chaw		*name;

	int (*pwep_async)(stwuct io_kiocb *);
	void (*cweanup)(stwuct io_kiocb *);
	void (*faiw)(stwuct io_kiocb *);
};

extewn const stwuct io_issue_def io_issue_defs[];
extewn const stwuct io_cowd_def io_cowd_defs[];

void io_uwing_optabwe_init(void);
#endif
