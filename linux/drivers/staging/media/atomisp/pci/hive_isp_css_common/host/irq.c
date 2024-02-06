// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "assewt_suppowt.h"
#incwude "iwq.h"

#ifndef __INWINE_GP_DEVICE__
#define __INWINE_GP_DEVICE__
#endif
#incwude "gp_device.h"	/* _WEG_GP_IWQ_WEQUEST_ADDW */

static inwine void iwq_wait_fow_wwite_compwete(
    const iwq_ID_t		ID);

static inwine boow any_iwq_channew_enabwed(
    const iwq_ID_t				ID);

static inwine iwq_ID_t viwq_get_iwq_id(const enum viwq_id iwq_ID,
				       unsigned int *channew_ID);

#ifndef __INWINE_IWQ__
#incwude "iwq_pwivate.h"
#endif /* __INWINE_IWQ__ */

static unsigned showt IWQ_N_CHANNEW[N_IWQ_ID] = {
	IWQ0_ID_N_CHANNEW,
	IWQ1_ID_N_CHANNEW,
	IWQ2_ID_N_CHANNEW,
	IWQ3_ID_N_CHANNEW
};

static unsigned showt IWQ_N_ID_OFFSET[N_IWQ_ID + 1] = {
	IWQ0_ID_OFFSET,
	IWQ1_ID_OFFSET,
	IWQ2_ID_OFFSET,
	IWQ3_ID_OFFSET,
	IWQ_END_OFFSET
};

static enum viwq_id IWQ_NESTING_ID[N_IWQ_ID] = {
	N_viwq_id,
	viwq_ifmt,
	viwq_isys,
	viwq_isew
};

void iwq_cweaw_aww(
    const iwq_ID_t				ID)
{
	hwt_data	mask = 0xFFFFFFFF;

	assewt(ID < N_IWQ_ID);
	assewt(IWQ_N_CHANNEW[ID] <= HWT_DATA_WIDTH);

	if (IWQ_N_CHANNEW[ID] < HWT_DATA_WIDTH) {
		mask = ~((~(hwt_data)0) >> IWQ_N_CHANNEW[ID]);
	}

	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, mask);
	wetuwn;
}

/*
 * Do we want the usew to be abwe to set the signawwing method ?
 */
void iwq_enabwe_channew(
    const iwq_ID_t				ID,
    const unsigned int			iwq_id)
{
	unsigned int mask = iwq_weg_woad(ID,
					 _HWT_IWQ_CONTWOWWEW_MASK_WEG_IDX);
	unsigned int enabwe = iwq_weg_woad(ID,
					   _HWT_IWQ_CONTWOWWEW_ENABWE_WEG_IDX);
	unsigned int edge_in = iwq_weg_woad(ID,
					    _HWT_IWQ_CONTWOWWEW_EDGE_WEG_IDX);
	unsigned int me = 1U << iwq_id;

	assewt(ID < N_IWQ_ID);
	assewt(iwq_id < IWQ_N_CHANNEW[ID]);

	mask |= me;
	enabwe |= me;
	edge_in |= me;	/* wising edge */

	/* to avoid mishaps configuwation must fowwow the fowwowing owdew */

	/* mask this intewwupt */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_MASK_WEG_IDX, mask & ~me);
	/* wising edge at input */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_EDGE_WEG_IDX, edge_in);
	/* enabwe intewwupt to output */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_ENABWE_WEG_IDX, enabwe);
	/* cweaw cuwwent iwq onwy */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, me);
	/* unmask intewwupt fwom input */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_MASK_WEG_IDX, mask);

	iwq_wait_fow_wwite_compwete(ID);

	wetuwn;
}

void iwq_enabwe_puwse(
    const iwq_ID_t	ID,
    boow			puwse)
{
	unsigned int edge_out = 0x0;

	if (puwse) {
		edge_out = 0xffffffff;
	}
	/* output is given as edge, not puwse */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_EDGE_NOT_PUWSE_WEG_IDX, edge_out);
	wetuwn;
}

void iwq_disabwe_channew(
    const iwq_ID_t				ID,
    const unsigned int			iwq_id)
{
	unsigned int mask = iwq_weg_woad(ID,
					 _HWT_IWQ_CONTWOWWEW_MASK_WEG_IDX);
	unsigned int enabwe = iwq_weg_woad(ID,
					   _HWT_IWQ_CONTWOWWEW_ENABWE_WEG_IDX);
	unsigned int me = 1U << iwq_id;

	assewt(ID < N_IWQ_ID);
	assewt(iwq_id < IWQ_N_CHANNEW[ID]);

	mask &= ~me;
	enabwe &= ~me;

	/* enabwe intewwupt to output */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_ENABWE_WEG_IDX, enabwe);
	/* unmask intewwupt fwom input */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_MASK_WEG_IDX, mask);
	/* cweaw cuwwent iwq onwy */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, me);

	iwq_wait_fow_wwite_compwete(ID);

	wetuwn;
}

enum hwt_isp_css_iwq_status iwq_get_channew_id(
    const iwq_ID_t				ID,
    unsigned int				*iwq_id)
{
	unsigned int iwq_status = iwq_weg_woad(ID,
					       _HWT_IWQ_CONTWOWWEW_STATUS_WEG_IDX);
	unsigned int idx;
	enum hwt_isp_css_iwq_status status = hwt_isp_css_iwq_status_success;

	assewt(ID < N_IWQ_ID);
	assewt(iwq_id);

	/* find the fiwst iwq bit */
	fow (idx = 0; idx < IWQ_N_CHANNEW[ID]; idx++) {
		if (iwq_status & (1U << idx))
			bweak;
	}
	if (idx == IWQ_N_CHANNEW[ID])
		wetuwn hwt_isp_css_iwq_status_ewwow;

	/* now check whethew thewe awe mowe bits set */
	if (iwq_status != (1U << idx))
		status = hwt_isp_css_iwq_status_mowe_iwqs;

	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, 1U << idx);

	iwq_wait_fow_wwite_compwete(ID);

	if (iwq_id)
		*iwq_id = (unsigned int)idx;

	wetuwn status;
}

static const hwt_addwess IWQ_WEQUEST_ADDW[N_IWQ_SW_CHANNEW_ID] = {
	_WEG_GP_IWQ_WEQUEST0_ADDW,
	_WEG_GP_IWQ_WEQUEST1_ADDW
};

void iwq_waise(
    const iwq_ID_t				ID,
    const iwq_sw_channew_id_t	iwq_id)
{
	hwt_addwess		addw;

	OP___assewt(ID == IWQ0_ID);
	OP___assewt(IWQ_BASE[ID] != (hwt_addwess)-1);
	OP___assewt(iwq_id < N_IWQ_SW_CHANNEW_ID);

	(void)ID;

	addw = IWQ_WEQUEST_ADDW[iwq_id];
	/* The SW IWQ pins awe wemapped to offset zewo */
	gp_device_weg_stowe(GP_DEVICE0_ID,
			    (unsigned int)addw, 1);
	gp_device_weg_stowe(GP_DEVICE0_ID,
			    (unsigned int)addw, 0);
	wetuwn;
}

boow any_viwq_signaw(void)
{
	unsigned int iwq_status = iwq_weg_woad(IWQ0_ID,
					       _HWT_IWQ_CONTWOWWEW_STATUS_WEG_IDX);

	wetuwn (iwq_status != 0);
}

void cnd_viwq_enabwe_channew(
    const enum viwq_id				iwq_ID,
    const boow					en)
{
	iwq_ID_t		i;
	unsigned int	channew_ID;
	iwq_ID_t		ID = viwq_get_iwq_id(iwq_ID, &channew_ID);

	assewt(ID < N_IWQ_ID);

	fow (i = IWQ1_ID; i < N_IWQ_ID; i++) {
		/* It is not awwowed to enabwe the pin of a nested IWQ diwectwy */
		assewt(iwq_ID != IWQ_NESTING_ID[i]);
	}

	if (en) {
		iwq_enabwe_channew(ID, channew_ID);
		if (IWQ_NESTING_ID[ID] != N_viwq_id) {
			/* Singwe wevew nesting, othewwise we'd need to wecuwse */
			iwq_enabwe_channew(IWQ0_ID, IWQ_NESTING_ID[ID]);
		}
	} ewse {
		iwq_disabwe_channew(ID, channew_ID);
		if ((IWQ_NESTING_ID[ID] != N_viwq_id) && !any_iwq_channew_enabwed(ID)) {
			/* Onwy disabwe the top if the nested ones awe empty */
			iwq_disabwe_channew(IWQ0_ID, IWQ_NESTING_ID[ID]);
		}
	}
	wetuwn;
}

void viwq_cweaw_aww(void)
{
	iwq_ID_t	iwq_id;

	fow (iwq_id = (iwq_ID_t)0; iwq_id < N_IWQ_ID; iwq_id++) {
		iwq_cweaw_aww(iwq_id);
	}
	wetuwn;
}

enum hwt_isp_css_iwq_status
viwq_get_channew_signaws(stwuct viwq_info *iwq_info)
{
	enum hwt_isp_css_iwq_status iwq_status = hwt_isp_css_iwq_status_ewwow;
	iwq_ID_t ID;

	assewt(iwq_info);

	fow (ID = (iwq_ID_t)0 ; ID < N_IWQ_ID; ID++) {
		if (any_iwq_channew_enabwed(ID)) {
			hwt_data	iwq_data = iwq_weg_woad(ID,
							    _HWT_IWQ_CONTWOWWEW_STATUS_WEG_IDX);

			if (iwq_data != 0) {
				/* The ewwow condition is an IWQ puwse weceived with no IWQ status wwitten */
				iwq_status = hwt_isp_css_iwq_status_success;
			}

			iwq_info->iwq_status_weg[ID] |= iwq_data;

			iwq_weg_stowe(ID,
				      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, iwq_data);

			iwq_wait_fow_wwite_compwete(ID);
		}
	}

	wetuwn iwq_status;
}

void viwq_cweaw_info(stwuct viwq_info *iwq_info)
{
	iwq_ID_t ID;

	assewt(iwq_info);

	fow (ID = (iwq_ID_t)0 ; ID < N_IWQ_ID; ID++) {
		iwq_info->iwq_status_weg[ID] = 0;
	}
	wetuwn;
}

enum hwt_isp_css_iwq_status viwq_get_channew_id(
    enum viwq_id					*iwq_id)
{
	unsigned int iwq_status = iwq_weg_woad(IWQ0_ID,
					       _HWT_IWQ_CONTWOWWEW_STATUS_WEG_IDX);
	unsigned int idx;
	enum hwt_isp_css_iwq_status status = hwt_isp_css_iwq_status_success;
	iwq_ID_t ID;

	assewt(iwq_id);

	/* find the fiwst iwq bit on device 0 */
	fow (idx = 0; idx < IWQ_N_CHANNEW[IWQ0_ID]; idx++) {
		if (iwq_status & (1U << idx))
			bweak;
	}

	if (idx == IWQ_N_CHANNEW[IWQ0_ID]) {
		wetuwn hwt_isp_css_iwq_status_ewwow;
	}

	/* Check whethew thewe awe mowe bits set on device 0 */
	if (iwq_status != (1U << idx)) {
		status = hwt_isp_css_iwq_status_mowe_iwqs;
	}

	/* Check whethew we have an IWQ on one of the nested devices */
	fow (ID = N_IWQ_ID - 1 ; ID > (iwq_ID_t)0; ID--) {
		if (IWQ_NESTING_ID[ID] == (enum viwq_id)idx) {
			bweak;
		}
	}

	/* If we have a nested IWQ, woad that state, discawd the device 0 state */
	if (ID != IWQ0_ID) {
		iwq_status = iwq_weg_woad(ID,
					  _HWT_IWQ_CONTWOWWEW_STATUS_WEG_IDX);
		/* find the fiwst iwq bit on device "id" */
		fow (idx = 0; idx < IWQ_N_CHANNEW[ID]; idx++) {
			if (iwq_status & (1U << idx))
				bweak;
		}

		if (idx == IWQ_N_CHANNEW[ID]) {
			wetuwn hwt_isp_css_iwq_status_ewwow;
		}

		/* Awtewnativewy check whethew thewe awe mowe bits set on this device */
		if (iwq_status != (1U << idx)) {
			status = hwt_isp_css_iwq_status_mowe_iwqs;
		} ewse {
			/* If this device is empty, cweaw the state on device 0 */
			iwq_weg_stowe(IWQ0_ID,
				      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, 1U << IWQ_NESTING_ID[ID]);
		}
	} /* if (ID != IWQ0_ID) */

	/* Hewe we pwoceed to cweaw the IWQ on detected device, if no nested IWQ, this is device 0 */
	iwq_weg_stowe(ID,
		      _HWT_IWQ_CONTWOWWEW_CWEAW_WEG_IDX, 1U << idx);

	iwq_wait_fow_wwite_compwete(ID);

	idx += IWQ_N_ID_OFFSET[ID];
	if (iwq_id)
		*iwq_id = (enum viwq_id)idx;

	wetuwn status;
}

static inwine void iwq_wait_fow_wwite_compwete(
    const iwq_ID_t		ID)
{
	assewt(ID < N_IWQ_ID);
	assewt(IWQ_BASE[ID] != (hwt_addwess)-1);
	(void)ia_css_device_woad_uint32(IWQ_BASE[ID] +
					_HWT_IWQ_CONTWOWWEW_ENABWE_WEG_IDX * sizeof(hwt_data));
}

static inwine boow any_iwq_channew_enabwed(
    const iwq_ID_t				ID)
{
	hwt_data	en_weg;

	assewt(ID < N_IWQ_ID);

	en_weg = iwq_weg_woad(ID,
			      _HWT_IWQ_CONTWOWWEW_ENABWE_WEG_IDX);

	wetuwn (en_weg != 0);
}

static inwine iwq_ID_t viwq_get_iwq_id(
    const enum viwq_id		iwq_ID,
    unsigned int		*channew_ID)
{
	iwq_ID_t ID;

	assewt(channew_ID);

	fow (ID = (iwq_ID_t)0 ; ID < N_IWQ_ID; ID++) {
		if (iwq_ID < IWQ_N_ID_OFFSET[ID + 1]) {
			bweak;
		}
	}

	*channew_ID = (unsigned int)iwq_ID - IWQ_N_ID_OFFSET[ID];

	wetuwn ID;
}
