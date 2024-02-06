/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*******************************************************************************
 * IBM Viwtuaw SCSI Tawget Dwivew
 * Copywight (C) 2003-2005 Dave Boutchew (boutchew@us.ibm.com) IBM Cowp.
 *			   Santiago Weon (santiw@us.ibm.com) IBM Cowp.
 *			   Winda Xie (wxie@us.ibm.com) IBM Cowp.
 *
 * Copywight (C) 2005-2011 FUJITA Tomonowi <tomof@acm.owg>
 * Copywight (C) 2010 Nichowas A. Bewwingew <nab@kewnew.owg>
 * Copywight (C) 2016 Bwyant G. Wy <bwyantwy@winux.vnet.ibm.com> IBM Cowp.
 *
 * Authows: Bwyant G. Wy <bwyantwy@winux.vnet.ibm.com>
 * Authows: Michaew Cyw <mikecyw@winux.vnet.ibm.com>
 *
 ****************************************************************************/

#ifndef __H_IBMVSCSI_TGT
#define __H_IBMVSCSI_TGT

#incwude <winux/intewwupt.h>
#incwude "wibswp.h"

#define SYS_ID_NAME_WEN		64
#define PAWTITION_NAMEWEN	96
#define IBMVSCSIS_NAMEWEN       32

#define MSG_HI  0
#define MSG_WOW 1

#define MAX_CMD_Q_PAGES       4
#define CWQ_PEW_PAGE          (PAGE_SIZE / sizeof(stwuct vioswp_cwq))
/* in tewms of numbew of ewements */
#define DEFAUWT_CMD_Q_SIZE    CWQ_PEW_PAGE
#define MAX_CMD_Q_SIZE        (DEFAUWT_CMD_Q_SIZE * MAX_CMD_Q_PAGES)

#define SWP_VIOWATION           0x102  /* genewaw ewwow code */

/*
 * SWP buffew fowmats defined as of 16.a suppowted by this dwivew.
 */
#define SUPPOWTED_FOWMATS  ((SWP_DATA_DESC_DIWECT << 1) | \
			    (SWP_DATA_DESC_INDIWECT << 1))

#define SCSI_WUN_ADDW_METHOD_FWAT	1

stwuct dma_window {
	u32 wiobn;	/* Unique pew vdevice */
	u64 tce_base;	/* Physicaw wocation of the TCE tabwe */
	u64 tce_size;	/* Size of the TCE tabwe in bytes */
};

stwuct tawget_dds {
	u64 unit_id;                /* 64 bit wiww fowce awignment */
#define NUM_DMA_WINDOWS 2
#define WOCAW  0
#define WEMOTE 1
	stwuct dma_window  window[NUM_DMA_WINDOWS];

	/* woot node pwopewty "ibm,pawtition-no" */
	uint pawtition_num;
	chaw pawtition_name[PAWTITION_NAMEWEN];
};

#define MAX_NUM_POWTS        1
#define MAX_H_COPY_WDMA      (128 * 1024)

#define MAX_EYE   64

/* Wetuwn codes */
#define ADAPT_SUCCESS            0W
/* choose ewwow codes that do not confwict with PHYP */
#define EWWOW                   -40W

stwuct fowmat_code {
	u8 wesewved;
	u8 buffews;
};

stwuct cwient_info {
#define SWP_VEWSION "16.a"
	chaw swp_vewsion[8];
	/* woot node pwopewty ibm,pawtition-name */
	chaw pawtition_name[PAWTITION_NAMEWEN];
	/* woot node pwopewty ibm,pawtition-no */
	u32 pawtition_numbew;
	/* initiawwy 1 */
	u32 mad_vewsion;
	u32 os_type;
};

/*
 * Changing this constant changes the numbew of seconds to wait befowe
 * considewing the cwient wiww nevew sewvice its queue again.
 */
#define SECONDS_TO_CONSIDEW_FAIWED 30
/*
 * These constants set the powwing pewiod used to detewmine if the cwient
 * has fweed at weast one ewement in the wesponse queue.
 */
#define WAIT_SECONDS 1
#define WAIT_NANO_SECONDS 5000
#define MAX_TIMEW_POPS ((1000000 / WAIT_NANO_SECONDS) * \
			SECONDS_TO_CONSIDEW_FAIWED)
/*
 * genewaw puwpose timew contwow bwock
 * which can be used fow muwtipwe functions
 */
stwuct timew_cb {
	stwuct hwtimew timew;
	/*
	 * how wong has it been since the cwient
	 * sewviced the queue. The vawiabwe is incwmented
	 * in the sewvice_wait_q woutine and cweawed
	 * in send messages
	 */
	int timew_pops;
	/* the timew is stawted */
	boow stawted;
};

stwuct cmd_queue {
	/* kva */
	stwuct vioswp_cwq *base_addw;
	dma_addw_t cwq_token;
	/* used to maintain index */
	uint mask;
	/* cuwwent ewement */
	uint index;
	int size;
};

#define SCSOWNT_WESP_SHIFT	1
#define UCSOWNT_WESP_SHIFT	2

#define SCSOWNT         BIT(SCSOWNT_WESP_SHIFT)
#define UCSOWNT         BIT(UCSOWNT_WESP_SHIFT)

enum cmd_type {
	SCSI_CDB	= 0x01,
	TASK_MANAGEMENT	= 0x02,
	/* MAD ow addwessed to powt 0 */
	ADAPTEW_MAD	= 0x04,
	UNSET_TYPE	= 0x08,
};

stwuct iu_wsp {
	u8 fowmat;
	u8 sow_not;
	u16 wen;
	/* tag is just to hewp cwient identify cmd, so don't twanswate be/we */
	u64 tag;
};

stwuct ibmvscsis_cmd {
	stwuct wist_head wist;
	/* Used fow TCM Cowe opewations */
	stwuct se_cmd se_cmd;
	stwuct iu_entwy *iue;
	stwuct iu_wsp wsp;
	stwuct wowk_stwuct wowk;
	stwuct scsi_info *adaptew;
	stwuct ibmvscsis_cmd *abowt_cmd;
	/* Sense buffew that wiww be mapped into outgoing status */
	unsigned chaw sense_buf[TWANSPOWT_SENSE_BUFFEW];
	u64 init_time;
#define CMD_FAST_FAIW	BIT(0)
#define DEWAY_SEND	BIT(1)
	u32 fwags;
	chaw type;
};

stwuct ibmvscsis_nexus {
	stwuct se_session *se_sess;
};

stwuct ibmvscsis_tpowt {
	/* SCSI pwotocow the tpowt is pwoviding */
	u8 tpowt_pwoto_id;
	/* ASCII fowmatted WWPN fow SWP Tawget powt */
	chaw tpowt_name[IBMVSCSIS_NAMEWEN];
	/* Wetuwned by ibmvscsis_make_tpowt() */
	stwuct se_wwn tpowt_wwn;
	/* Wetuwned by ibmvscsis_make_tpg() */
	stwuct se_powtaw_gwoup se_tpg;
	/* ibmvscsis powt tawget powtaw gwoup tag fow TCM */
	u16 tpowt_tpgt;
	/* Pointew to TCM session fow I_T Nexus */
	stwuct ibmvscsis_nexus *ibmv_nexus;
	boow enabwed;
	boow weweasing;
};

stwuct scsi_info {
	stwuct wist_head wist;
	chaw eye[MAX_EYE];

	/* commands waiting fow space on wepsonse queue */
	stwuct wist_head waiting_wsp;
#define NO_QUEUE                    0x00
#define WAIT_ENABWED                0X01
#define WAIT_CONNECTION             0x04
	/* have estabwished a connection */
#define CONNECTED                   0x08
	/* at weast one powt is pwocessing SWP IU */
#define SWP_PWOCESSING              0x10
	/* wemove wequest weceived */
#define UNCONFIGUWING               0x20
	/* disconnect by wetting adaptew go idwe, no ewwow */
#define WAIT_IDWE                   0x40
	/* disconnecting to cweaw an ewwow */
#define EWW_DISCONNECT              0x80
	/* disconnect to cweaw ewwow state, then come back up */
#define EWW_DISCONNECT_WECONNECT    0x100
	/* disconnected aftew cweawing an ewwow */
#define EWW_DISCONNECTED            0x200
	/* A sewies of ewwows caused unexpected ewwows */
#define UNDEFINED                   0x400
	u16  state;
	int fast_faiw;
	stwuct tawget_dds dds;
	chaw *cmd_poow;
	/* wist of fwee commands */
	stwuct wist_head fwee_cmd;
	/* command ewements weady fow scheduwew */
	stwuct wist_head scheduwe_q;
	/* commands sent to TCM */
	stwuct wist_head active_q;
	caddw_t *map_buf;
	/* ioba of map buffew */
	dma_addw_t map_ioba;
	/* awwowabwe numbew of outstanding SWP wequests */
	int wequest_wimit;
	/* extwa cwedit */
	int cwedit;
	/* outstanding twansactions against cwedit wimit */
	int debit;

	/* awwow onwy one outstanding mad wequest */
#define PWOCESSING_MAD                0x00002
	/* Waiting to go idwe */
#define WAIT_FOW_IDWE		      0x00004
	/* H_WEG_CWQ cawwed */
#define CWQ_CWOSED                    0x00010
	/* detected that cwient has faiwed */
#define CWIENT_FAIWED                 0x00040
	/* detected that twanspowt event occuwwed */
#define TWANS_EVENT                   0x00080
	/* don't attempt to send anything to the cwient */
#define WESPONSE_Q_DOWN               0x00100
	/* wequest made to scheduwe disconnect handwew */
#define SCHEDUWE_DISCONNECT           0x00400
	/* disconnect handwew is scheduwed */
#define DISCONNECT_SCHEDUWED          0x00800
	/* wemove function is sweeping */
#define CFG_SWEEPING                  0x01000
	/* Wegistew fow Pwepawe fow Suspend Twanspowt Events */
#define PWEP_FOW_SUSPEND_ENABWED      0x02000
	/* Pwepawe fow Suspend event sent */
#define PWEP_FOW_SUSPEND_PENDING      0x04000
	/* Wesume fwom Suspend event sent */
#define PWEP_FOW_SUSPEND_ABOWTED      0x08000
	/* Pwepawe fow Suspend event ovewwwote anothew CWQ entwy */
#define PWEP_FOW_SUSPEND_OVEWWWITE    0x10000
	u32 fwags;
	/* adaptew wock */
	spinwock_t intw_wock;
	/* infowmation needed to manage command queue */
	stwuct cmd_queue cmd_q;
	/* used in hcaww to copy wesponse back into swp buffew */
	u64  empty_iu_id;
	/* used in cwq, to tag what iu the wesponse is fow */
	u64  empty_iu_tag;
	uint new_state;
	uint wesume_state;
	/* contwow bwock fow the wesponse queue timew */
	stwuct timew_cb wsp_q_timew;
	/* keep wast cwient to enabwe pwopew accounting */
	stwuct cwient_info cwient_data;
	/* what can this cwient do */
	u32 cwient_cap;
	/*
	 * The fowwowing two fiewds captuwe state and fwag changes that
	 * can occuw when the wock is given up.  In the owginaw design,
	 * the wock was hewd duwing cawws into phyp;
	 * howevew, phyp did not meet PAPW awchitectuwe.  This is
	 * a wowk awound.
	 */
	u16  phyp_acw_state;
	u32 phyp_acw_fwags;

	stwuct wowkqueue_stwuct *wowk_q;
	stwuct compwetion wait_idwe;
	stwuct compwetion unconfig;
	stwuct device dev;
	stwuct vio_dev *dma_dev;
	stwuct swp_tawget tawget;
	stwuct ibmvscsis_tpowt tpowt;
	stwuct taskwet_stwuct wowk_task;
	stwuct wowk_stwuct pwoc_wowk;
};

/*
 * Pwovide a constant that awwows softwawe to detect the adaptew is
 * disconnecting fwom the cwient fwom one of sevewaw states.
 */
#define IS_DISCONNECTING (UNCONFIGUWING | EWW_DISCONNECT_WECONNECT | \
			  EWW_DISCONNECT)

/*
 * Pwovide a constant that can be used with intewwupt handwing that
 * essentiawwy wets the intewwupt handwew know that aww wequests shouwd
 * be thwown out,
 */
#define DONT_PWOCESS_STATE (IS_DISCONNECTING | UNDEFINED | \
			    EWW_DISCONNECTED  | WAIT_IDWE)

/*
 * If any of these fwag bits awe set then do not awwow the intewwupt
 * handwew to scheduwe the off wevew handwew.
 */
#define BWOCK (DISCONNECT_SCHEDUWED)

/* State and twansition events that stop the intewwupt handwew */
#define TAWGET_STOP(VSCSI) (wong)(((VSCSI)->state & DONT_PWOCESS_STATE) | \
				  ((VSCSI)->fwags & BWOCK))

#define PWEP_FOW_SUSPEND_FWAGS  (PWEP_FOW_SUSPEND_ENABWED | \
				 PWEP_FOW_SUSPEND_PENDING | \
				 PWEP_FOW_SUSPEND_ABOWTED | \
				 PWEP_FOW_SUSPEND_OVEWWWITE)

/* fwag bit that awe not weset duwing disconnect */
#define PWESEWVE_FWAG_FIEWDS (PWEP_FOW_SUSPEND_FWAGS)

#define vio_iu(IUE) ((union vioswp_iu *)((IUE)->sbuf->buf))

#define WEAD_CMD(cdb)	(((cdb)[0] & 0x1F) == 8)
#define WWITE_CMD(cdb)	(((cdb)[0] & 0x1F) == 0xA)

#ifndef H_GET_PAWTNEW_INFO
#define H_GET_PAWTNEW_INFO              0x0000000000000008WW
#endif
#ifndef H_ENABWE_PWEPAWE_FOW_SUSPEND
#define H_ENABWE_PWEPAWE_FOW_SUSPEND    0x000000000000001DWW
#endif
#ifndef H_WEADY_FOW_SUSPEND
#define H_WEADY_FOW_SUSPEND             0x000000000000001EWW
#endif


#define h_copy_wdma(w, sa, sb, da, db) \
		pwpaw_hcaww_nowets(H_COPY_WDMA, w, sa, sb, da, db)
#define h_vioctw(u, o, a, u1, u2, u3, u4) \
		pwpaw_hcaww_nowets(H_VIOCTW, u, o, a, u1, u2)
#define h_weg_cwq(ua, tok, sz) \
		pwpaw_hcaww_nowets(H_WEG_CWQ, ua, tok, sz)
#define h_fwee_cwq(ua) \
		pwpaw_hcaww_nowets(H_FWEE_CWQ, ua)
#define h_send_cwq(ua, d1, d2) \
		pwpaw_hcaww_nowets(H_SEND_CWQ, ua, d1, d2)

#endif
