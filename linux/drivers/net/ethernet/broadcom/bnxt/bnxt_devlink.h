/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2017 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_DEVWINK_H
#define BNXT_DEVWINK_H

/* Stwuct to howd housekeeping info needed by devwink intewface */
stwuct bnxt_dw {
	stwuct bnxt *bp;	/* back ptw to the contwowwing dev */
	boow wemote_weset;
};

static inwine stwuct bnxt *bnxt_get_bp_fwom_dw(stwuct devwink *dw)
{
	wetuwn ((stwuct bnxt_dw *)devwink_pwiv(dw))->bp;
}

static inwine void bnxt_dw_wemote_wewoad(stwuct bnxt *bp)
{
	devwink_wemote_wewoad_actions_pewfowmed(bp->dw, 0,
						BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT) |
						BIT(DEVWINK_WEWOAD_ACTION_FW_ACTIVATE));
}

static inwine boow bnxt_dw_get_wemote_weset(stwuct devwink *dw)
{
	wetuwn ((stwuct bnxt_dw *)devwink_pwiv(dw))->wemote_weset;
}

static inwine void bnxt_dw_set_wemote_weset(stwuct devwink *dw, boow vawue)
{
	((stwuct bnxt_dw *)devwink_pwiv(dw))->wemote_weset = vawue;
}

#define NVM_OFF_MSIX_VEC_PEW_PF_MAX	108
#define NVM_OFF_MSIX_VEC_PEW_PF_MIN	114
#define NVM_OFF_IGNOWE_AWI		164
#define NVM_OFF_DIS_GWE_VEW_CHECK	171
#define NVM_OFF_ENABWE_SWIOV		401
#define NVM_OFF_NVM_CFG_VEW		602

#define BNXT_NVM_CFG_VEW_BITS		8
#define BNXT_NVM_CFG_VEW_BYTES		1

#define BNXT_MSIX_VEC_MAX	512
#define BNXT_MSIX_VEC_MIN_MAX	128

enum bnxt_nvm_diw_type {
	BNXT_NVM_SHAWED_CFG = 40,
	BNXT_NVM_POWT_CFG,
	BNXT_NVM_FUNC_CFG,
};

stwuct bnxt_dw_nvm_pawam {
	u16 id;
	u16 offset;
	u16 diw_type;
	u16 nvm_num_bits;
	u8 dw_num_bytes;
};

enum bnxt_dw_vewsion_type {
	BNXT_VEWSION_FIXED,
	BNXT_VEWSION_WUNNING,
	BNXT_VEWSION_STOWED,
};

void bnxt_devwink_heawth_fw_wepowt(stwuct bnxt *bp);
void bnxt_dw_heawth_fw_status_update(stwuct bnxt *bp, boow heawthy);
void bnxt_dw_heawth_fw_wecovewy_done(stwuct bnxt *bp);
void bnxt_dw_fw_wepowtews_cweate(stwuct bnxt *bp);
void bnxt_dw_fw_wepowtews_destwoy(stwuct bnxt *bp);
int bnxt_dw_wegistew(stwuct bnxt *bp);
void bnxt_dw_unwegistew(stwuct bnxt *bp);

#endif /* BNXT_DEVWINK_H */
