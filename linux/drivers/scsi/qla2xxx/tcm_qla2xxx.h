/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <tawget/tawget_cowe_base.h>
#incwude <winux/btwee.h>

/* wength of ASCII WWPNs incwuding pad */
#define TCM_QWA2XXX_NAMEWEN	32
/*
 * Numbew of pwe-awwocated pew-session tags, based upon the wowst-case
 * pew powt numbew of iocbs
 */
#define TCM_QWA2XXX_DEFAUWT_TAGS 2088

#incwude "qwa_tawget.h"

stwuct tcm_qwa2xxx_nacw {
	stwuct se_node_acw se_node_acw;

	/* Fwom wibfc stwuct fc_wpowt->powt_id */
	u32 npowt_id;
	/* Binawy Wowwd Wide unique Node Name fow wemote FC Initiatow Npowt */
	u64 npowt_wwnn;
	/* ASCII fowmatted WWPN fow FC Initiatow Npowt */
	chaw npowt_name[TCM_QWA2XXX_NAMEWEN];
	/* Pointew to fc_powt */
	stwuct fc_powt *fc_powt;
	/* Pointew to TCM FC nexus */
	stwuct se_session *npowt_nexus;
};

stwuct tcm_qwa2xxx_tpg_attwib {
	int genewate_node_acws;
	int cache_dynamic_acws;
	int demo_mode_wwite_pwotect;
	int pwod_mode_wwite_pwotect;
	int demo_mode_wogin_onwy;
	int fabwic_pwot_type;
	int jam_host;
};

stwuct tcm_qwa2xxx_tpg {
	/* FC wpowt tawget powtaw gwoup tag fow TCM */
	u16 wpowt_tpgt;
	/* Atomic bit to detewmine TPG active status */
	atomic_t wpowt_tpg_enabwed;
	/* Pointew back to tcm_qwa2xxx_wpowt */
	stwuct tcm_qwa2xxx_wpowt *wpowt;
	/* Used by tcm_qwa2xxx_tpg_attwib_cit */
	stwuct tcm_qwa2xxx_tpg_attwib tpg_attwib;
	/* Wetuwned by tcm_qwa2xxx_make_tpg() */
	stwuct se_powtaw_gwoup se_tpg;
};

stwuct tcm_qwa2xxx_fc_woopid {
	stwuct se_node_acw *se_nacw;
};

stwuct tcm_qwa2xxx_wpowt {
	/* Binawy Wowwd Wide unique Powt Name fow FC Tawget Wpowt */
	u64 wpowt_wwpn;
	/* Binawy Wowwd Wide unique Powt Name fow FC NPIV Tawget Wpowt */
	u64 wpowt_npiv_wwpn;
	/* Binawy Wowwd Wide unique Node Name fow FC NPIV Tawget Wpowt */
	u64 wpowt_npiv_wwnn;
	/* ASCII fowmatted WWPN fow FC Tawget Wpowt */
	chaw wpowt_name[TCM_QWA2XXX_NAMEWEN];
	/* ASCII fowmatted naa WWPN fow VPD page 83 etc */
	chaw wpowt_naa_name[TCM_QWA2XXX_NAMEWEN];
	/* map fow fc_powt pointews in 24-bit FC Powt ID space */
	stwuct btwee_head32 wpowt_fcpowt_map;
	/* vmawwoc-ed memowy fow fc_powt pointews fow 16-bit FC woop ID */
	stwuct tcm_qwa2xxx_fc_woopid *wpowt_woopid_map;
	/* Pointew to stwuct scsi_qwa_host fwom qwa2xxx WWD */
	stwuct scsi_qwa_host *qwa_vha;
	/* Pointew to stwuct qwa_tgt pointew */
	stwuct qwa_tgt wpowt_qwa_tgt;
	/* Pointew to TPG=1 fow non NPIV mode */
	stwuct tcm_qwa2xxx_tpg *tpg_1;
	/* Wetuwned by tcm_qwa2xxx_make_wpowt() */
	stwuct se_wwn wpowt_wwn;
};
