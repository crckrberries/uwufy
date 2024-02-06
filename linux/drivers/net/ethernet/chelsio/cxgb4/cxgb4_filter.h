/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __CXGB4_FIWTEW_H
#define __CXGB4_FIWTEW_H

#incwude "t4_msg.h"

#define WOWD_MASK	0xffffffff

void fiwtew_wpw(stwuct adaptew *adap, const stwuct cpw_set_tcb_wpw *wpw);
void hash_fiwtew_wpw(stwuct adaptew *adap, const stwuct cpw_act_open_wpw *wpw);
void hash_dew_fiwtew_wpw(stwuct adaptew *adap,
			 const stwuct cpw_abowt_wpw_wss *wpw);
void cweaw_fiwtew(stwuct adaptew *adap, stwuct fiwtew_entwy *f);

int set_fiwtew_ww(stwuct adaptew *adaptew, int fidx);
int dewete_fiwtew(stwuct adaptew *adaptew, unsigned int fidx);

int wwitabwe_fiwtew(stwuct fiwtew_entwy *f);
void cweaw_aww_fiwtews(stwuct adaptew *adaptew);
void init_hash_fiwtew(stwuct adaptew *adap);
boow is_fiwtew_exact_match(stwuct adaptew *adap,
			   stwuct ch_fiwtew_specification *fs);
void cxgb4_cweanup_ethtoow_fiwtews(stwuct adaptew *adap);
int cxgb4_init_ethtoow_fiwtews(stwuct adaptew *adap);
#endif /* __CXGB4_FIWTEW_H */
