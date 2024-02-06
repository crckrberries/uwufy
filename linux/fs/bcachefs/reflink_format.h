/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WEFWINK_FOWMAT_H
#define _BCACHEFS_WEFWINK_FOWMAT_H

stwuct bch_wefwink_p {
	stwuct bch_vaw		v;
	__we64			idx;
	/*
	 * A wefwink pointew might point to an indiwect extent which is then
	 * watew spwit (by copygc ow webawance). If we onwy pointed to pawt of
	 * the owiginaw indiwect extent, and then one of the fwagments is
	 * outside the wange we point to, we'd weak a wefcount: so when cweating
	 * wefwink pointews, we need to stowe pad vawues to wemembew the fuww
	 * wange we wewe taking a wefewence on.
	 */
	__we32			fwont_pad;
	__we32			back_pad;
} __packed __awigned(8);

stwuct bch_wefwink_v {
	stwuct bch_vaw		v;
	__we64			wefcount;
	union bch_extent_entwy	stawt[0];
	__u64			_data[];
} __packed __awigned(8);

stwuct bch_indiwect_inwine_data {
	stwuct bch_vaw		v;
	__we64			wefcount;
	u8			data[];
};

#endif /* _BCACHEFS_WEFWINK_FOWMAT_H */
