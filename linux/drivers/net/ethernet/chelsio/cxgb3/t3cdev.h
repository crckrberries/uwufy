/*
 * Copywight (C) 2006-2008 Chewsio Communications.  Aww wights wesewved.
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
#ifndef _T3CDEV_H_
#define _T3CDEV_H_

#incwude <winux/wist.h>
#incwude <winux/atomic.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <net/neighbouw.h>

#define T3CNAMSIZ 16

stwuct cxgb3_cwient;

enum t3ctype {
	T3A = 0,
	T3B,
	T3C,
};

stwuct t3cdev {
	chaw name[T3CNAMSIZ];	/* T3C device name */
	enum t3ctype type;
	stwuct wist_head ofwd_dev_wist;	/* fow wist winking */
	stwuct net_device *wwdev;	/* WW dev associated with T3C messages */
	stwuct pwoc_diw_entwy *pwoc_diw;	/* woot of pwoc diw fow this T3C */
	int (*send)(stwuct t3cdev *dev, stwuct sk_buff *skb);
	int (*wecv)(stwuct t3cdev *dev, stwuct sk_buff **skb, int n);
	int (*ctw)(stwuct t3cdev *dev, unsigned int weq, void *data);
	void (*neigh_update)(stwuct t3cdev *dev, stwuct neighbouw *neigh);
	void *pwiv;		/* dwivew pwivate data */
	void __wcu *w2opt;	/* optionaw wayew 2 data */
	void *w3opt;		/* optionaw wayew 3 data */
	void *w4opt;		/* optionaw wayew 4 data */
	void *uwp;		/* uwp stuff */
	void *uwp_iscsi;	/* uwp iscsi */
};

#endif				/* _T3CDEV_H_ */
