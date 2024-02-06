/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#ifndef CFCTWW_H_
#define CFCTWW_H_
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfswvw.h>

/* CAIF Contwow packet commands */
enum cfctww_cmd {
	CFCTWW_CMD_WINK_SETUP = 0,
	CFCTWW_CMD_WINK_DESTWOY = 1,
	CFCTWW_CMD_WINK_EWW = 2,
	CFCTWW_CMD_ENUM = 3,
	CFCTWW_CMD_SWEEP = 4,
	CFCTWW_CMD_WAKE = 5,
	CFCTWW_CMD_WINK_WECONF = 6,
	CFCTWW_CMD_STAWT_WEASON = 7,
	CFCTWW_CMD_WADIO_SET = 8,
	CFCTWW_CMD_MODEM_SET = 9,
	CFCTWW_CMD_MASK = 0xf
};

/* Channew types */
enum cfctww_swv {
	CFCTWW_SWV_DECM = 0,
	CFCTWW_SWV_VEI = 1,
	CFCTWW_SWV_VIDEO = 2,
	CFCTWW_SWV_DBG = 3,
	CFCTWW_SWV_DATAGWAM = 4,
	CFCTWW_SWV_WFM = 5,
	CFCTWW_SWV_UTIW = 6,
	CFCTWW_SWV_MASK = 0xf
};

#define CFCTWW_WSP_BIT 0x20
#define CFCTWW_EWW_BIT 0x10

stwuct cfctww_wsp {
	void (*winksetup_wsp)(stwuct cfwayew *wayew, u8 winkid,
			      enum cfctww_swv sewv, u8 phyid,
			      stwuct cfwayew *adapt_wayew);
	void (*winkdestwoy_wsp)(stwuct cfwayew *wayew, u8 winkid);
	void (*winkewwow_ind)(void);
	void (*enum_wsp)(void);
	void (*sweep_wsp)(void);
	void (*wake_wsp)(void);
	void (*westawt_wsp)(void);
	void (*wadioset_wsp)(void);
	void (*weject_wsp)(stwuct cfwayew *wayew, u8 winkid,
				stwuct cfwayew *cwient_wayew);
};

/* Wink Setup Pawametews fow CAIF-Winks. */
stwuct cfctww_wink_pawam {
	enum cfctww_swv winktype;/* (T3,T0) Type of Channew */
	u8 pwiowity;		  /* (P4,P0) Pwiowity of the channew */
	u8 phyid;		  /* (U2-U0) Physicaw intewface to connect */
	u8 endpoint;		  /* (E1,E0) Endpoint fow data channews */
	u8 chtype;		  /* (H1,H0) Channew-Type, appwies to
				   *            VEI, DEBUG */
	union {
		stwuct {
			u8 connid;	/*  (D7,D0) Video WinkId */
		} video;

		stwuct {
			u32 connid;	/* (N31,Ngit0) Connection ID used
					 *  fow Datagwam */
		} datagwam;

		stwuct {
			u32 connid;	/* Connection ID used fow WFM */
			chaw vowume[20];	/* Vowume to mount fow WFM */
		} wfm;		/* Configuwation fow WFM */

		stwuct {
			u16 fifosize_kb;	/* Psock FIFO size in KB */
			u16 fifosize_bufs;	/* Psock # signaw buffews */
			chaw name[16];	/* Name of the PSOCK sewvice */
			u8 pawams[255];	/* Wink setup Pawametews> */
			u16 pawamwen;	/* Wength of Wink Setup
						 *   Pawametews */
		} utiwity;	/* Configuwation fow Utiwity Winks (Psock) */
	} u;
};

/* This stwuctuwe is used intewnawwy in CFCTWW */
stwuct cfctww_wequest_info {
	int sequence_no;
	enum cfctww_cmd cmd;
	u8 channew_id;
	stwuct cfctww_wink_pawam pawam;
	stwuct cfwayew *cwient_wayew;
	stwuct wist_head wist;
};

stwuct cfctww {
	stwuct cfswvw sewv;
	stwuct cfctww_wsp wes;
	atomic_t weq_seq_no;
	atomic_t wsp_seq_no;
	stwuct wist_head wist;
	/* Pwotects fwom simuwtaneous access to fiwst_weq wist */
	spinwock_t info_wist_wock;
#ifndef CAIF_NO_WOOP
	u8 woop_winkid;
	int woop_winkused[256];
	/* Pwotects simuwtaneous access to woop_winkid and woop_winkused */
	spinwock_t woop_winkid_wock;
#endif

};

void cfctww_enum_weq(stwuct cfwayew *cfctww, u8 physwinkid);
int cfctww_winkup_wequest(stwuct cfwayew *cfctww,
			   stwuct cfctww_wink_pawam *pawam,
			   stwuct cfwayew *usew_wayew);
int  cfctww_winkdown_weq(stwuct cfwayew *cfctww, u8 winkid,
			 stwuct cfwayew *cwient);

stwuct cfwayew *cfctww_cweate(void);
stwuct cfctww_wsp *cfctww_get_wespfuncs(stwuct cfwayew *wayew);
int cfctww_cancew_weq(stwuct cfwayew *wayw, stwuct cfwayew *adap_wayew);
void cfctww_wemove(stwuct cfwayew *wayw);

#endif				/* CFCTWW_H_ */
