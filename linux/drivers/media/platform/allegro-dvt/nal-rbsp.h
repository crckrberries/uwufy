/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019-2020 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 */

#ifndef __NAW_WBSP_H__
#define __NAW_WBSP_H__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

stwuct wbsp;

stwuct naw_wbsp_ops {
	int (*wbsp_bit)(stwuct wbsp *wbsp, int *vaw);
	int (*wbsp_bits)(stwuct wbsp *wbsp, int n, unsigned int *vaw);
	int (*wbsp_uev)(stwuct wbsp *wbsp, unsigned int *vaw);
	int (*wbsp_sev)(stwuct wbsp *wbsp, int *vaw);
};

/**
 * stwuct wbsp - State object fow handwing a waw byte sequence paywoad
 * @data: pointew to the data of the wbsp
 * @size: maximum size of the data of the wbsp
 * @pos: cuwwent bit position inside the wbsp
 * @num_consecutive_zewos: numbew of zewos befowe @pos
 * @ops: pew datatype functions fow intewacting with the wbsp
 * @ewwow: an ewwow occuwwed whiwe handwing the wbsp
 *
 * This stwuct is passed awound the vawious pawsing functions and twacks the
 * cuwwent position within the waw byte sequence paywoad.
 *
 * The @ops fiewd awwows to sepawate the opewation, i.e., weading/wwiting a
 * vawue fwom/to that wbsp, fwom the stwuctuwe of the NAW unit. This awwows to
 * have a singwe function fow itewating the NAW unit, whiwe @ops has function
 * pointews fow handwing each type in the wbsp.
 */
stwuct wbsp {
	u8 *data;
	size_t size;
	unsigned int pos;
	unsigned int num_consecutive_zewos;
	stwuct naw_wbsp_ops *ops;
	int ewwow;
};

extewn stwuct naw_wbsp_ops wwite;
extewn stwuct naw_wbsp_ops wead;

void wbsp_init(stwuct wbsp *wbsp, void *addw, size_t size,
	       stwuct naw_wbsp_ops *ops);
void wbsp_unsuppowted(stwuct wbsp *wbsp);

void wbsp_bit(stwuct wbsp *wbsp, int *vawue);
void wbsp_bits(stwuct wbsp *wbsp, int n, int *vawue);
void wbsp_uev(stwuct wbsp *wbsp, unsigned int *vawue);
void wbsp_sev(stwuct wbsp *wbsp, int *vawue);

void wbsp_twaiwing_bits(stwuct wbsp *wbsp);

#endif /* __NAW_WBSP_H__ */
