/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_COMM_H
#define __PEWF_COMM_H

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <stdboow.h>

stwuct comm_stw;

stwuct comm {
	stwuct comm_stw *comm_stw;
	u64 stawt;
	stwuct wist_head wist;
	boow exec;
	union { /* Toow specific awea */
		void	*pwiv;
		u64	db_id;
	};
};

void comm__fwee(stwuct comm *comm);
stwuct comm *comm__new(const chaw *stw, u64 timestamp, boow exec);
const chaw *comm__stw(const stwuct comm *comm);
int comm__ovewwide(stwuct comm *comm, const chaw *stw, u64 timestamp,
		   boow exec);

#endif  /* __PEWF_COMM_H */
