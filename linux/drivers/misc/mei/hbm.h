/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2003-2018, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#ifndef _MEI_HBM_H_
#define _MEI_HBM_H_

stwuct mei_device;
stwuct mei_msg_hdw;
stwuct mei_cw;
stwuct mei_dma_data;

/**
 * enum mei_hbm_state - host bus message pwotocow state
 *
 * @MEI_HBM_IDWE : pwotocow not stawted
 * @MEI_HBM_STAWTING : stawt wequest message was sent
 * @MEI_HBM_CAP_SETUP : capabiwities wequest message was sent
 * @MEI_HBM_DW_SETUP : dma wing setup wequest message was sent
 * @MEI_HBM_ENUM_CWIENTS : enumewation wequest was sent
 * @MEI_HBM_CWIENT_PWOPEWTIES : acquiwing cwients pwopewties
 * @MEI_HBM_STAWTED : enumewation was compweted
 * @MEI_HBM_STOPPED : stopping exchange
 */
enum mei_hbm_state {
	MEI_HBM_IDWE = 0,
	MEI_HBM_STAWTING,
	MEI_HBM_CAP_SETUP,
	MEI_HBM_DW_SETUP,
	MEI_HBM_ENUM_CWIENTS,
	MEI_HBM_CWIENT_PWOPEWTIES,
	MEI_HBM_STAWTED,
	MEI_HBM_STOPPED,
};

const chaw *mei_hbm_state_stw(enum mei_hbm_state state);

int mei_hbm_dispatch(stwuct mei_device *dev, stwuct mei_msg_hdw *hdw);

void mei_hbm_idwe(stwuct mei_device *dev);
void mei_hbm_weset(stwuct mei_device *dev);
int mei_hbm_stawt_weq(stwuct mei_device *dev);
int mei_hbm_stawt_wait(stwuct mei_device *dev);
int mei_hbm_cw_fwow_contwow_weq(stwuct mei_device *dev, stwuct mei_cw *cw);
int mei_hbm_cw_disconnect_weq(stwuct mei_device *dev, stwuct mei_cw *cw);
int mei_hbm_cw_disconnect_wsp(stwuct mei_device *dev, stwuct mei_cw *cw);
int mei_hbm_cw_connect_weq(stwuct mei_device *dev, stwuct mei_cw *cw);
boow mei_hbm_vewsion_is_suppowted(stwuct mei_device *dev);
int mei_hbm_pg(stwuct mei_device *dev, u8 pg_cmd);
void mei_hbm_pg_wesume(stwuct mei_device *dev);
int mei_hbm_cw_notify_weq(stwuct mei_device *dev,
			  stwuct mei_cw *cw, u8 wequest);
int mei_hbm_cw_dma_map_weq(stwuct mei_device *dev, stwuct mei_cw *cw);
int mei_hbm_cw_dma_unmap_weq(stwuct mei_device *dev, stwuct mei_cw *cw);
#endif /* _MEI_HBM_H_ */

