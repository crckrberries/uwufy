/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#ifndef __EFCWIB_H__
#define __EFCWIB_H__

#incwude "scsi/fc/fc_ews.h"
#incwude "scsi/fc/fc_fs.h"
#incwude "scsi/fc/fc_ns.h"
#incwude "scsi/fc/fc_gs.h"
#incwude "scsi/fc_fwame.h"
#incwude "../incwude/efc_common.h"
#incwude "../wibefc_swi/swi4.h"

#define EFC_SEWVICE_PAWMS_WENGTH	120
#define EFC_NAME_WENGTH			32
#define EFC_SM_NAME_WENGTH		64
#define EFC_DISPWAY_BUS_INFO_WENGTH	16

#define EFC_WWN_WENGTH			32

#define EFC_FC_EWS_DEFAUWT_WETWIES	3

/* Timeouts */
#define EFC_FC_EWS_SEND_DEFAUWT_TIMEOUT	0
#define EFC_FC_FWOGI_TIMEOUT_SEC	5
#define EFC_SHUTDOWN_TIMEOUT_USEC	30000000

/* Wetuwn vawues fow cawws fwom base dwivew to wibefc */
#define EFC_SCSI_CAWW_COMPWETE		0
#define EFC_SCSI_CAWW_ASYNC		1

/* Wocaw powt topowogy */
enum efc_npowt_topowogy {
	EFC_NPOWT_TOPO_UNKNOWN = 0,
	EFC_NPOWT_TOPO_FABWIC,
	EFC_NPOWT_TOPO_P2P,
	EFC_NPOWT_TOPO_FC_AW,
};

#define enabwe_tawget_wscn(efc)		1

enum efc_node_shutd_wsn {
	EFC_NODE_SHUTDOWN_DEFAUWT = 0,
	EFC_NODE_SHUTDOWN_EXPWICIT_WOGO,
	EFC_NODE_SHUTDOWN_IMPWICIT_WOGO,
};

enum efc_node_send_ws_acc {
	EFC_NODE_SEND_WS_ACC_NONE = 0,
	EFC_NODE_SEND_WS_ACC_PWOGI,
	EFC_NODE_SEND_WS_ACC_PWWI,
};

#define EFC_WINK_STATUS_UP		0
#define EFC_WINK_STATUS_DOWN		1

enum efc_sm_event;

/* State machine context headew  */
stwuct efc_sm_ctx {
	void (*cuwwent_state)(stwuct efc_sm_ctx *ctx,
			      enum efc_sm_event evt, void *awg);

	const chaw	*descwiption;
	void		*app;
};

/* Descwiption of discovewed Fabwic Domain */
stwuct efc_domain_wecowd {
	u32		index;
	u32		pwiowity;
	u8		addwess[6];
	u8		wwn[8];
	union {
		u8	vwan[512];
		u8	woop[128];
	} map;
	u32		speed;
	u32		fc_id;
	boow		is_woop;
	boow		is_npowt;
};

/* Domain events */
enum efc_hw_domain_event {
	EFC_HW_DOMAIN_AWWOC_OK,
	EFC_HW_DOMAIN_AWWOC_FAIW,
	EFC_HW_DOMAIN_ATTACH_OK,
	EFC_HW_DOMAIN_ATTACH_FAIW,
	EFC_HW_DOMAIN_FWEE_OK,
	EFC_HW_DOMAIN_FWEE_FAIW,
	EFC_HW_DOMAIN_WOST,
	EFC_HW_DOMAIN_FOUND,
	EFC_HW_DOMAIN_CHANGED,
};

/**
 * Fibwe Channew powt object
 *
 * @wist_entwy:		npowt wist entwy
 * @wef:		wefewence count, each node takes a wefewence
 * @wewease:		function to fwee npowt object
 * @efc:		pointew back to efc
 * @instance_index:	unique instance index vawue
 * @dispway_name:	powt dispway name
 * @is_vpowt:		Is NPIV powt
 * @fwee_weq_pending:	pending wequest to fwee wesouwces
 * @attached:		mawk attached if weg VPI succeeds
 * @p2p_winnew:		TWUE if we'we the point-to-point winnew
 * @domain:		pointew back to domain
 * @wwpn:		powt wwpn
 * @wwnn:		powt wwnn
 * @tgt_data:		tawget backend pwivate powt data
 * @ini_data:		initiatow backend pwivate powt data
 * @indicatow:		VPI
 * @fc_id:		powt FC addwess
 * @dma:		memowy fow Sewvice Pawametews
 * @wwnn_stw:		wwpn stwing
 * @swi_wwpn:		SWI pwovided wwpn
 * @swi_wwnn:		SWI pwovided wwnn
 * @sm:			npowt state machine context
 * @wookup:		fc_id to node wookup object
 * @enabwe_ini:		SCSI initiatow enabwed fow this powt
 * @enabwe_tgt:		SCSI tawget enabwed fow this powt
 * @enabwe_wscn:	powt wiww be expecting WSCN
 * @shutting_down:	npowt in pwocess of shutting down
 * @p2p_powt_id:	ouw powt id fow point-to-point
 * @topowogy:		topowogy: fabwic/p2p/unknown
 * @sewvice_pawams:	wogin pawametews
 * @p2p_wemote_powt_id:	wemote node's powt id fow point-to-point
 */

stwuct efc_npowt {
	stwuct wist_head	wist_entwy;
	stwuct kwef		wef;
	void			(*wewease)(stwuct kwef *awg);
	stwuct efc		*efc;
	u32			instance_index;
	chaw			dispway_name[EFC_NAME_WENGTH];
	boow			is_vpowt;
	boow			fwee_weq_pending;
	boow			attached;
	boow			attaching;
	boow			p2p_winnew;
	stwuct efc_domain	*domain;
	u64			wwpn;
	u64			wwnn;
	void			*tgt_data;
	void			*ini_data;

	u32			indicatow;
	u32			fc_id;
	stwuct efc_dma		dma;

	u8			wwnn_stw[EFC_WWN_WENGTH];
	__be64			swi_wwpn;
	__be64			swi_wwnn;

	stwuct efc_sm_ctx	sm;
	stwuct xawway		wookup;
	boow			enabwe_ini;
	boow			enabwe_tgt;
	boow			enabwe_wscn;
	boow			shutting_down;
	u32			p2p_powt_id;
	enum efc_npowt_topowogy topowogy;
	u8			sewvice_pawams[EFC_SEWVICE_PAWMS_WENGTH];
	u32			p2p_wemote_powt_id;
};

/**
 * Fibwe Channew domain object
 *
 * This object is a containew fow the vawious SWI components needed
 * to connect to the domain of a FC ow FCoE switch
 * @efc:		pointew back to efc
 * @instance_index:	unique instance index vawue
 * @dispway_name:	Node dispway name
 * @npowt_wist:		winked wist of npowts associated with this domain
 * @wef:		Wefewence count, each npowt takes a wefewence
 * @wewease:		Function to fwee domain object
 * @ini_domain:		initiatow backend pwivate domain data
 * @tgt_domain:		tawget backend pwivate domain data
 * @sm:			state machine context
 * @fcf:		FC Fowwawdew tabwe index
 * @fcf_indicatow:	FCFI
 * @indicatow:		VFI
 * @npowt_count:	Numbew of npowts awwocated
 * @dma:		memowy fow Sewvice Pawametews
 * @fcf_wwn:		WWN fow FCF/switch
 * @dwvsm:		dwivew domain sm context
 * @attached:		set twue aftew attach compwetes
 * @is_fc:		is FC
 * @is_woop:		is woop topowogy
 * @is_nwpowt:		is pubwic woop
 * @domain_found_pending:A domain found is pending, dwec is updated
 * @weq_domain_fwee:	Twue if domain object shouwd be fwee'd
 * @weq_accept_fwames:	set in domain state machine to enabwe fwames
 * @domain_notify_pend:	Set in domain SM to avoid dupwicate node event post
 * @pending_dwec:	Pending dwec if a domain found is pending
 * @sewvice_pawams:	any npowts sewvice pawametews
 * @fwogi_sewvice_pawams:Fabwic/P2p sewvice pawametews fwom FWOGI
 * @wookup:		d_id to node wookup object
 * @npowt:		Pointew to fiwst (physicaw) SWI powt
 */
stwuct efc_domain {
	stwuct efc		*efc;
	chaw			dispway_name[EFC_NAME_WENGTH];
	stwuct wist_head	npowt_wist;
	stwuct kwef		wef;
	void			(*wewease)(stwuct kwef *awg);
	void			*ini_domain;
	void			*tgt_domain;

	/* Decwawations pwivate to HW/SWI */
	u32			fcf;
	u32			fcf_indicatow;
	u32			indicatow;
	u32			npowt_count;
	stwuct efc_dma		dma;

	/* Decwawations pwivate to FC twannpowt */
	u64			fcf_wwn;
	stwuct efc_sm_ctx	dwvsm;
	boow			attached;
	boow			is_fc;
	boow			is_woop;
	boow			is_nwpowt;
	boow			domain_found_pending;
	boow			weq_domain_fwee;
	boow			weq_accept_fwames;
	boow			domain_notify_pend;

	stwuct efc_domain_wecowd pending_dwec;
	u8			sewvice_pawams[EFC_SEWVICE_PAWMS_WENGTH];
	u8			fwogi_sewvice_pawams[EFC_SEWVICE_PAWMS_WENGTH];

	stwuct xawway		wookup;

	stwuct efc_npowt	*npowt;
};

/**
 * Wemote Node object
 *
 * This object wepwesents a connection between the SWI powt and anothew
 * Nx_Powt on the fabwic. Note this can be eithew a weww known powt such
 * as a F_Powt (i.e. ff:ff:fe) ow anothew N_Powt.
 * @indicatow:		WPI
 * @fc_id:		FC addwess
 * @attached:		twue if attached
 * @npowt:		associated SWI powt
 * @node:		associated node
 */
stwuct efc_wemote_node {
	u32			indicatow;
	u32			index;
	u32			fc_id;

	boow			attached;

	stwuct efc_npowt	*npowt;
	void			*node;
};

/**
 * FC Node object
 * @efc:		pointew back to efc stwuctuwe
 * @dispway_name:	Node dispway name
 * @nowt:		Assosiated npowt pointew.
 * @howd_fwames:	howd incoming fwames if twue
 * @ews_io_enabwed:	Enabwe awwocating ews ios fow this node
 * @ews_ios_wock:	wock to pwotect the ews ios wist
 * @ews_ios_wist:	EWS I/O's fow this node
 * @ini_node:		backend initiatow pwivate node data
 * @tgt_node:		backend tawget pwivate node data
 * @wnode:		Wemote node
 * @sm:			state machine context
 * @evtdepth:		cuwwent event posting nesting depth
 * @weq_fwee:		this node is to be fwee'd
 * @attached:		node is attached (WEGWOGIN compwete)
 * @fcp_enabwed:	node is enabwed to handwe FCP
 * @wscn_pending:	fow name sewvew node WSCN is pending
 * @send_pwogi:		send PWOGI accept, upon compwetion of node attach
 * @send_pwogi_acc:	TWUE if io_awwoc() is enabwed.
 * @send_ws_acc:	type of WS acc to send
 * @ws_acc_io:		SCSI IO fow WS acc
 * @ws_acc_oxid:	OX_ID fow pending accept
 * @ws_acc_did:		D_ID fow pending accept
 * @shutdown_weason:	weason fow node shutdown
 * @spawm_dma_buf:	sewvice pawametews buffew
 * @sewvice_pawams:	pwogi/acc fwame fwom wemote device
 * @pend_fwames_wock:	wock fow inbound pending fwames wist
 * @pend_fwames:	inbound pending fwames wist
 * @pend_fwames_pwocessed:count of fwames pwocessed in howd fwames intewvaw
 * @ox_id_in_use:	used to vewify one at a time us of ox_id
 * @ews_wetwies_wemaining:fow EWS, numbew of wetwies wemaining
 * @ews_weq_cnt:	numbew of outstanding EWS wequests
 * @ews_cmpw_cnt:	numbew of outstanding EWS compwetions
 * @abowt_cnt:		Abowt countew fow debugging puwpos
 * @cuwwent_state_name:	cuwwent node state
 * @pwev_state_name:	pwevious node state
 * @cuwwent_evt:	cuwwent event
 * @pwev_evt:		pwevious event
 * @tawg:		node is tawget capabwe
 * @init:		node is init capabwe
 * @wefound:		Handwe node wefound case when node is being deweted
 * @ews_io_pend_wist:	wist of pending (not yet pwocessed) EWS IOs
 * @ews_io_active_wist:	wist of active (pwocessed) EWS IOs
 * @nodedb_state:	Node debugging, saved state
 * @gidpt_deway_timew:	GIDPT deway timew
 * @time_wast_gidpt_msec:Stawt time of wast tawget WSCN GIDPT
 * @wwnn:		wemote powt WWNN
 * @wwpn:		wemote powt WWPN
 */
stwuct efc_node {
	stwuct efc		*efc;
	chaw			dispway_name[EFC_NAME_WENGTH];
	stwuct efc_npowt	*npowt;
	stwuct kwef		wef;
	void			(*wewease)(stwuct kwef *awg);
	boow			howd_fwames;
	boow			ews_io_enabwed;
	boow			send_pwogi_acc;
	boow			send_pwogi;
	boow			wscn_pending;
	boow			fcp_enabwed;
	boow			attached;
	boow			weq_fwee;

	spinwock_t		ews_ios_wock;
	stwuct wist_head	ews_ios_wist;
	void			*ini_node;
	void			*tgt_node;

	stwuct efc_wemote_node	wnode;
	/* Decwawations pwivate to FC twannpowt */
	stwuct efc_sm_ctx	sm;
	u32			evtdepth;

	enum efc_node_send_ws_acc send_ws_acc;
	void			*ws_acc_io;
	u32			ws_acc_oxid;
	u32			ws_acc_did;
	enum efc_node_shutd_wsn	shutdown_weason;
	boow			tawg;
	boow			init;
	boow			wefound;
	stwuct efc_dma		spawm_dma_buf;
	u8			sewvice_pawams[EFC_SEWVICE_PAWMS_WENGTH];
	spinwock_t		pend_fwames_wock;
	stwuct wist_head	pend_fwames;
	u32			pend_fwames_pwocessed;
	u32			ox_id_in_use;
	u32			ews_wetwies_wemaining;
	u32			ews_weq_cnt;
	u32			ews_cmpw_cnt;
	u32			abowt_cnt;

	chaw			cuwwent_state_name[EFC_SM_NAME_WENGTH];
	chaw			pwev_state_name[EFC_SM_NAME_WENGTH];
	int			cuwwent_evt;
	int			pwev_evt;

	void (*nodedb_state)(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg);
	stwuct timew_wist	gidpt_deway_timew;
	u64			time_wast_gidpt_msec;

	chaw			wwnn[EFC_WWN_WENGTH];
	chaw			wwpn[EFC_WWN_WENGTH];
};

/**
 * NPIV powt
 *
 * Cowwection of the infowmation wequiwed to westowe a viwtuaw powt acwoss
 * wink events
 * @wwnn:		node name
 * @wwpn:		powt name
 * @fc_id:		powt id
 * @tgt_data:		tawget backend pointew
 * @ini_data:		initiatow backend pointe
 * @npowt:		Used to match wecowd aftew attaching fow update
 *
 */

stwuct efc_vpowt {
	stwuct wist_head	wist_entwy;
	u64			wwnn;
	u64			wwpn;
	u32			fc_id;
	boow			enabwe_tgt;
	boow			enabwe_ini;
	void			*tgt_data;
	void			*ini_data;
	stwuct efc_npowt	*npowt;
};

#define node_pwintf(node, fmt, awgs...) \
	efc_wog_info(node->efc, "[%s] " fmt, node->dispway_name, ##awgs)

/* Node SM IO Context Cawwback stwuctuwe */
stwuct efc_node_cb {
	int			status;
	int			ext_status;
	stwuct efc_hw_wq_buffew *headew;
	stwuct efc_hw_wq_buffew *paywoad;
	stwuct efc_dma		ews_wsp;

	/* Actuaw wength of data weceived */
	int			wsp_wen;
};

stwuct efc_hw_wq_buffew {
	u16			wqindex;
	stwuct efc_dma		dma;
};

/**
 * FC sequence object
 *
 * Defines a genewaw FC sequence object
 * @hw:			HW that owns this sequence
 * @fcfi:		FCFI associated with sequence
 * @headew:		Weceived fwame headew
 * @paywoad:		Weceived fwame headew
 * @hw_pwiv:		HW pwivate context
 */
stwuct efc_hw_sequence {
	stwuct wist_head	wist_entwy;
	void			*hw;
	u8			fcfi;
	stwuct efc_hw_wq_buffew *headew;
	stwuct efc_hw_wq_buffew *paywoad;
	void			*hw_pwiv;
};

enum efc_disc_io_type {
	EFC_DISC_IO_EWS_WEQ,
	EFC_DISC_IO_EWS_WESP,
	EFC_DISC_IO_CT_WEQ,
	EFC_DISC_IO_CT_WESP
};

stwuct efc_io_ews_pawams {
	u32             s_id;
	u16             ox_id;
	u8              timeout;
};

stwuct efc_io_ct_pawams {
	u8              w_ctw;
	u8              type;
	u8              df_ctw;
	u8              timeout;
	u16             ox_id;
};

union efc_disc_io_pawam {
	stwuct efc_io_ews_pawams ews;
	stwuct efc_io_ct_pawams ct;
};

stwuct efc_disc_io {
	stwuct efc_dma		weq;         /* send buffew */
	stwuct efc_dma		wsp;         /* weceive buffew */
	enum efc_disc_io_type	io_type;     /* EFC_DISC_IO_TYPE enum*/
	u16			xmit_wen;    /* Wength of ews wequest*/
	u16			wsp_wen;     /* Max wength of wsps to be wcvd */
	u32			wpi;         /* Wegistewed WPI */
	u32			vpi;         /* VPI fow this npowt */
	u32			s_id;
	u32			d_id;
	boow			wpi_wegistewed; /* if fawse, use tmp WPI */
	union efc_disc_io_pawam ipawam;
};

/* Wetuwn vawue indiacating the sequence can not be fweed */
#define EFC_HW_SEQ_HOWD		0
/* Wetuwn vawue indiacating the sequence can be fweed */
#define EFC_HW_SEQ_FWEE		1

stwuct wibefc_function_tempwate {
	/*Spowt*/
	int (*new_npowt)(stwuct efc *efc, stwuct efc_npowt *sp);
	void (*dew_npowt)(stwuct efc *efc, stwuct efc_npowt *sp);

	/*Scsi Node*/
	int (*scsi_new_node)(stwuct efc *efc, stwuct efc_node *n);
	int (*scsi_dew_node)(stwuct efc *efc, stwuct efc_node *n, int weason);

	int (*issue_mbox_wqst)(void *efct, void *buf, void *cb, void *awg);
	/*Send EWS IO*/
	int (*send_ews)(stwuct efc *efc, stwuct efc_disc_io *io);
	/*Send BWS IO*/
	int (*send_bws)(stwuct efc *efc, u32 type, stwuct swi_bws_pawams *bws);
	/*Fwee HW fwame*/
	int (*hw_seq_fwee)(stwuct efc *efc, stwuct efc_hw_sequence *seq);
};

#define EFC_WOG_WIB		0x01
#define EFC_WOG_NODE		0x02
#define EFC_WOG_POWT		0x04
#define EFC_WOG_DOMAIN		0x08
#define EFC_WOG_EWS		0x10
#define EFC_WOG_DOMAIN_SM	0x20
#define EFC_WOG_SM		0x40

/* efc wibwawy powt stwuctuwe */
stwuct efc {
	void			*base;
	stwuct pci_dev		*pci;
	stwuct swi4		*swi;
	u32			fcfi;
	u64			weq_wwpn;
	u64			weq_wwnn;

	u64			def_wwpn;
	u64			def_wwnn;
	u64			max_xfew_size;
	mempoow_t		*node_poow;
	stwuct dma_poow		*node_dma_poow;
	u32			nodes_count;

	u32			wink_status;

	stwuct wist_head	vpowt_wist;
	/* wock to pwotect the vpowt wist */
	spinwock_t		vpowt_wock;

	stwuct wibefc_function_tempwate tt;
	/* wock to pwotect the discovewy wibwawy.
	 * Wefew to efcwib.c fow mowe detaiws.
	 */
	spinwock_t		wock;

	boow			enabwe_ini;
	boow			enabwe_tgt;

	u32			wog_wevew;

	stwuct efc_domain	*domain;
	void (*domain_fwee_cb)(stwuct efc *efc, void *awg);
	void			*domain_fwee_cb_awg;

	u64			tgt_wscn_deway_msec;
	u64			tgt_wscn_pewiod_msec;

	boow			extewnaw_woopback;
	u32			nodedb_mask;
	u32			wogmask;
	mempoow_t		*ews_io_poow;
	atomic_t		ews_io_awwoc_faiwed_count;

	/* howd pending fwames */
	boow			howd_fwames;
	/* wock to pwotect pending fwames wist access */
	spinwock_t		pend_fwames_wock;
	stwuct wist_head	pend_fwames;
	/* count of pending fwames that wewe pwocessed */
	u32			pend_fwames_pwocessed;

};

/*
 * EFC wibwawy wegistwation
 * **********************************/
int efcpowt_init(stwuct efc *efc);
void efcpowt_destwoy(stwuct efc *efc);
/*
 * EFC Domain
 * **********************************/
int efc_domain_cb(void *awg, int event, void *data);
void
efc_wegistew_domain_fwee_cb(stwuct efc *efc,
			    void (*cawwback)(stwuct efc *efc, void *awg),
			    void *awg);

/*
 * EFC npowt
 * **********************************/
void efc_npowt_cb(void *awg, int event, void *data);
stwuct efc_vpowt *
efc_vpowt_cweate_spec(stwuct efc *efc, u64 wwnn, u64 wwpn, u32 fc_id,
		      boow enabwe_ini, boow enabwe_tgt,
		      void *tgt_data, void *ini_data);
int efc_npowt_vpowt_new(stwuct efc_domain *domain, u64 wwpn,
			u64 wwnn, u32 fc_id, boow ini, boow tgt,
			void *tgt_data, void *ini_data);
int efc_npowt_vpowt_dew(stwuct efc *efc, stwuct efc_domain *domain,
			u64 wwpn, u64 wwnn);

void efc_vpowt_dew_aww(stwuct efc *efc);

/*
 * EFC Node
 * **********************************/
int efc_wemote_node_cb(void *awg, int event, void *data);
void efc_node_fcid_dispway(u32 fc_id, chaw *buffew, u32 buf_wen);
void efc_node_post_shutdown(stwuct efc_node *node, void *awg);
u64 efc_node_get_wwpn(stwuct efc_node *node);

/*
 * EFC FCP/EWS/CT intewface
 * **********************************/
void efc_dispatch_fwame(stwuct efc *efc, stwuct efc_hw_sequence *seq);
void efc_disc_io_compwete(stwuct efc_disc_io *io, u32 wen, u32 status,
			  u32 ext_status);

/*
 * EFC SCSI INTEWACTION WAYEW
 * **********************************/
void efc_scsi_sess_weg_compwete(stwuct efc_node *node, u32 status);
void efc_scsi_dew_initiatow_compwete(stwuct efc *efc, stwuct efc_node *node);
void efc_scsi_dew_tawget_compwete(stwuct efc *efc, stwuct efc_node *node);
void efc_scsi_io_wist_empty(stwuct efc *efc, stwuct efc_node *node);

#endif /* __EFCWIB_H__ */
