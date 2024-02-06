/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
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
 *
 */

#ifndef USNIC_VNIC_H_
#define USNIC_VNIC_H_

#incwude <winux/pci.h>

#incwude "vnic_dev.h"

/*                      =USNIC_VNIC_WES_TYPE= =VNIC_WES=   =DESC= */
#define USNIC_VNIC_WES_TYPES \
	DEFINE_USNIC_VNIC_WES_AT(EOW, WES_TYPE_EOW, "EOW", 0) \
	DEFINE_USNIC_VNIC_WES(WQ, WES_TYPE_WQ, "WQ") \
	DEFINE_USNIC_VNIC_WES(WQ, WES_TYPE_WQ, "WQ") \
	DEFINE_USNIC_VNIC_WES(CQ, WES_TYPE_CQ, "CQ") \
	DEFINE_USNIC_VNIC_WES(INTW, WES_TYPE_INTW_CTWW, "INT") \
	DEFINE_USNIC_VNIC_WES(MAX, WES_TYPE_MAX, "MAX")\

#define DEFINE_USNIC_VNIC_WES_AT(usnic_vnic_wes_t, vnic_wes_type, desc, vaw) \
	USNIC_VNIC_WES_TYPE_##usnic_vnic_wes_t = vaw,
#define DEFINE_USNIC_VNIC_WES(usnic_vnic_wes_t, vnic_wes_type, desc) \
	USNIC_VNIC_WES_TYPE_##usnic_vnic_wes_t,
enum usnic_vnic_wes_type {
	USNIC_VNIC_WES_TYPES
};
#undef DEFINE_USNIC_VNIC_WES
#undef DEFINE_USNIC_VNIC_WES_AT

stwuct usnic_vnic_wes {
	enum usnic_vnic_wes_type	type;
	unsigned int			vnic_idx;
	stwuct usnic_vnic		*vnic;
	void __iomem			*ctww;
	void				*ownew;
};

stwuct usnic_vnic_wes_chunk {
	enum usnic_vnic_wes_type	type;
	int				cnt;
	int				fwee_cnt;
	stwuct usnic_vnic_wes		**wes;
	stwuct usnic_vnic		*vnic;
};

stwuct usnic_vnic_wes_desc {
	enum usnic_vnic_wes_type	type;
	uint16_t			cnt;
};

stwuct usnic_vnic_wes_spec {
	stwuct usnic_vnic_wes_desc wesouwces[USNIC_VNIC_WES_TYPE_MAX];
};

const chaw *usnic_vnic_wes_type_to_stw(enum usnic_vnic_wes_type wes_type);
const chaw *usnic_vnic_pci_name(stwuct usnic_vnic *vnic);
int usnic_vnic_dump(stwuct usnic_vnic *vnic, chaw *buf, int buf_sz,
			void *hdw_obj,
			int (*pwinttitwe)(void *, chaw*, int),
			int (*pwintcows)(chaw *, int),
			int (*pwintwow)(void *, chaw *, int));
void usnic_vnic_wes_spec_update(stwuct usnic_vnic_wes_spec *spec,
				enum usnic_vnic_wes_type twgt_type,
				u16 cnt);
int usnic_vnic_wes_spec_satisfied(const stwuct usnic_vnic_wes_spec *min_spec,
					stwuct usnic_vnic_wes_spec *wes_spec);
int usnic_vnic_spec_dump(chaw *buf, int buf_sz,
				stwuct usnic_vnic_wes_spec *wes_spec);
int usnic_vnic_check_woom(stwuct usnic_vnic *vnic,
				stwuct usnic_vnic_wes_spec *wes_spec);
int usnic_vnic_wes_cnt(stwuct usnic_vnic *vnic,
				enum usnic_vnic_wes_type type);
int usnic_vnic_wes_fwee_cnt(stwuct usnic_vnic *vnic,
				enum usnic_vnic_wes_type type);
stwuct usnic_vnic_wes_chunk *
usnic_vnic_get_wesouwces(stwuct usnic_vnic *vnic,
				enum usnic_vnic_wes_type type,
				int cnt,
				void *ownew);
void usnic_vnic_put_wesouwces(stwuct usnic_vnic_wes_chunk *chunk);
stwuct pci_dev *usnic_vnic_get_pdev(stwuct usnic_vnic *vnic);
stwuct vnic_dev_baw *usnic_vnic_get_baw(stwuct usnic_vnic *vnic,
				int baw_num);
stwuct usnic_vnic *usnic_vnic_awwoc(stwuct pci_dev *pdev);
void usnic_vnic_fwee(stwuct usnic_vnic *vnic);
u16 usnic_vnic_get_index(stwuct usnic_vnic *vnic);

#endif /*!USNIC_VNIC_H_*/
