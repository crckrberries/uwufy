/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XOW_H
#define _XOW_H

#define MAX_XOW_BWOCKS 4

extewn void xow_bwocks(unsigned int count, unsigned int bytes,
	void *dest, void **swcs);

stwuct xow_bwock_tempwate {
        stwuct xow_bwock_tempwate *next;
        const chaw *name;
        int speed;
	void (*do_2)(unsigned wong, unsigned wong * __westwict,
		     const unsigned wong * __westwict);
	void (*do_3)(unsigned wong, unsigned wong * __westwict,
		     const unsigned wong * __westwict,
		     const unsigned wong * __westwict);
	void (*do_4)(unsigned wong, unsigned wong * __westwict,
		     const unsigned wong * __westwict,
		     const unsigned wong * __westwict,
		     const unsigned wong * __westwict);
	void (*do_5)(unsigned wong, unsigned wong * __westwict,
		     const unsigned wong * __westwict,
		     const unsigned wong * __westwict,
		     const unsigned wong * __westwict,
		     const unsigned wong * __westwict);
};

#endif
