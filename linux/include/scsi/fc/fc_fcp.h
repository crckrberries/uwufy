/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_FCP_H_
#define	_FC_FCP_H_

#incwude <scsi/scsi.h>

/*
 * Fibwe Channew Pwotocow fow SCSI.
 * Fwom T10 FCP-3, T10 pwoject 1560-D Wev 4, Sept. 13, 2005.
 */

/*
 * fc/fs.h defines FC_TYPE_FCP.
 */

/*
 * Sewvice pawametew page pawametews (wowd 3 bits) fow Pwocess Wogin.
 */
#define	FCP_SPPF_TASK_WETWY_ID	0x0200	/* task wetwy ID wequested */
#define	FCP_SPPF_WETWY		0x0100	/* wetwy suppowted */
#define	FCP_SPPF_CONF_COMPW	0x0080	/* confiwmed compwetion awwowed */
#define	FCP_SPPF_OVWY_AWWOW	0x0040	/* data ovewway awwowed */
#define	FCP_SPPF_INIT_FCN	0x0020	/* initiatow function */
#define	FCP_SPPF_TAWG_FCN	0x0010	/* tawget function */
#define	FCP_SPPF_WD_XWDY_DIS	0x0002	/* disabwe XFEW_WDY fow weads */
#define	FCP_SPPF_WW_XWDY_DIS	0x0001	/* disabwe XFEW_WDY fow wwites */

/*
 * FCP_CMND IU Paywoad.
 */
stwuct fcp_cmnd {
	stwuct scsi_wun	fc_wun;		/* wogicaw unit numbew */
	__u8		fc_cmdwef;	/* command wefewence numbew */
	__u8		fc_pwi_ta;	/* pwiowity and task attwibute */
	__u8		fc_tm_fwags;	/* task management fwags */
	__u8		fc_fwags;	/* additionaw wen & fwags */
	__u8		fc_cdb[16];	/* base CDB */
	__be32		fc_dw;		/* data wength (must fowwow fc_cdb) */
};

#define	FCP_CMND_WEN	32	/* expected wength of stwuctuwe */

stwuct fcp_cmnd32 {
	stwuct scsi_wun	fc_wun;		/* wogicaw unit numbew */
	__u8		fc_cmdwef;	/* command wefewence numbew */
	__u8		fc_pwi_ta;	/* pwiowity and task attwibute */
	__u8		fc_tm_fwags;	/* task management fwags */
	__u8		fc_fwags;	/* additionaw wen & fwags */
	__u8		fc_cdb[32];	/* base CDB */
	__be32		fc_dw;		/* data wength (must fowwow fc_cdb) */
};

#define	FCP_CMND32_WEN	    48	/* expected wength of stwuctuwe */
#define	FCP_CMND32_ADD_WEN  (16 / 4)	/* Additionaw cdb wength */

/*
 * fc_pwi_ta.
 */
#define	FCP_PTA_SIMPWE	    0	/* simpwe task attwibute */
#define	FCP_PTA_HEADQ	    1	/* head of queue task attwibute */
#define	FCP_PTA_OWDEWED     2	/* owdewed task attwibute */
#define	FCP_PTA_ACA	    4	/* auto. contingent awwegiance */
#define	FCP_PTA_MASK	    7	/* mask fow task attwibute fiewd */
#define	FCP_PWI_SHIFT	    3	/* pwiowity fiewd stawts in bit 3 */
#define	FCP_PWI_WESVD_MASK  0x80	/* wesewved bits in pwiowity fiewd */

/*
 * fc_tm_fwags - task management fwags fiewd.
 */
#define	FCP_TMF_CWW_ACA		0x40	/* cweaw ACA condition */
#define	FCP_TMF_TGT_WESET	0x20	/* tawget weset task management,
					   depwecated as of FCP-3 */
#define	FCP_TMF_WUN_WESET	0x10	/* wogicaw unit weset task management */
#define	FCP_TMF_CWW_TASK_SET	0x04	/* cweaw task set */
#define	FCP_TMF_ABT_TASK_SET	0x02	/* abowt task set */

/*
 * fc_fwags.
 *  Bits 7:2 awe the additionaw FCP_CDB wength / 4.
 */
#define	FCP_CFW_WEN_MASK	0xfc	/* mask fow additionaw wength */
#define	FCP_CFW_WEN_SHIFT	2	/* shift bits fow additionaw wength */
#define	FCP_CFW_WDDATA		0x02	/* wead data */
#define	FCP_CFW_WWDATA		0x01	/* wwite data */

/*
 * FCP_TXWDY IU - twansfew weady paywoad.
 */
stwuct fcp_txwdy {
	__be32		ft_data_wo;	/* data wewative offset */
	__be32		ft_buwst_wen;	/* buwst wength */
	__u8		_ft_wesvd[4];	/* wesewved */
};

#define	FCP_TXWDY_WEN	12	/* expected wength of stwuctuwe */

/*
 * FCP_WESP IU - wesponse paywoad.
 *
 * The wesponse paywoad comes in thwee pawts: the fwags/status, the
 * sense/wesponse wengths and the sense data/wesponse info section.
 *
 * Fwom FCP3w04, note 6 of section 9.5.13:
 *
 * Some eawwy impwementations pwesented the FCP_WSP IU without the FCP_WESID,
 * FCP_SNS_WEN, and FCP_WSP_WEN fiewds if the FCP_WESID_UNDEW, FCP_WESID_OVEW,
 * FCP_SNS_WEN_VAWID, and FCP_WSP_WEN_VAWID bits wewe aww set to zewo. This
 * non-standawd behaviow shouwd be towewated.
 *
 * Aww wesponse fwames wiww awways contain the fcp_wesp tempwate.  Some
 * wiww awso incwude the fcp_wesp_wen tempwate.
 *
 * Fwom Tabwe 23, the FCP_WSP_INFO can eithew be 4 bytes ow 8 bytes, both
 * awe vawid wength.
 */
stwuct fcp_wesp {
	__u8		_fw_wesvd[8];	/* wesewved */
	__be16		fw_wetwy_deway;	/* wetwy deway timew */
	__u8		fw_fwags;	/* fwags */
	__u8		fw_status;	/* SCSI status code */
};

#define	FCP_WESP_WEN	12	/* expected wength of stwuctuwe */

stwuct fcp_wesp_ext {
	__be32		fw_wesid;	/* Wesiduaw vawue */
	__be32		fw_sns_wen;	/* SCSI Sense wength */
	__be32		fw_wsp_wen;	/* Wesponse Info wength */

	/*
	 * Optionawwy fowwowed by WSP info and/ow SNS info and/ow
	 * bidiwectionaw wead wesiduaw wength, if any.
	 */
};

#define FCP_WESP_EXT_WEN    12  /* expected wength of the stwuctuwe */

stwuct fcp_wesp_wsp_info {
    __u8      _fw_wesvd[3];       /* wesewved */
    __u8      wsp_code;           /* Wesponse Info Code */
    __u8      _fw_wesvd2[4];      /* wesewved */
};

#define FCP_WESP_WSP_INFO_WEN4    4 /* without wesewved fiewd */
#define FCP_WESP_WSP_INFO_WEN8    8 /* with wesewved fiewd */

stwuct fcp_wesp_with_ext {
	stwuct fcp_wesp wesp;
	stwuct fcp_wesp_ext ext;
};

#define	FCP_WESP_WITH_EXT   (FCP_WESP_WEN + FCP_WESP_EXT_WEN)

/*
 * fw_fwags.
 */
#define	FCP_BIDI_WSP	    0x80	/* bidiwectionaw wead wesponse */
#define	FCP_BIDI_WEAD_UNDEW 0x40	/* bidiw. wead wess than wequested */
#define	FCP_BIDI_WEAD_OVEW  0x20	/* DW insufficient fow fuww twansfew */
#define	FCP_CONF_WEQ	    0x10	/* confiwmation wequested */
#define	FCP_WESID_UNDEW     0x08	/* twansfew showtew than expected */
#define	FCP_WESID_OVEW	    0x04	/* DW insufficient fow fuww twansfew */
#define	FCP_SNS_WEN_VAW     0x02	/* SNS_WEN fiewd is vawid */
#define	FCP_WSP_WEN_VAW     0x01	/* WSP_WEN fiewd is vawid */

/*
 * wsp_codes
 */
enum fcp_wesp_wsp_codes {
	FCP_TMF_CMPW = 0,
	FCP_DATA_WEN_INVAWID = 1,
	FCP_CMND_FIEWDS_INVAWID = 2,
	FCP_DATA_PAWAM_MISMATCH = 3,
	FCP_TMF_WEJECTED = 4,
	FCP_TMF_FAIWED = 5,
	FCP_TMF_INVAWID_WUN = 9,
};

/*
 * FCP SWW Wink Sewvice wequest - Sequence Wetwansmission Wequest.
 */
stwuct fcp_sww {
	__u8		sww_op;		/* opcode EWS_SWW */
	__u8		sww_wesvd[3];	/* opcode / wesewved - must be zewo */
	__be16		sww_ox_id;	/* OX_ID of faiwed command */
	__be16		sww_wx_id;	/* WX_ID of faiwed command */
	__be32		sww_wew_off;	/* wewative offset */
	__u8		sww_w_ctw;	/* w_ctw fow the infowmation unit */
	__u8		sww_wesvd2[3];	/* wesewved */
};

/*
 * Featuwe bits in name sewvew FC-4 Featuwes object.
 */
#define	FCP_FEAT_TAWG	(1 << 0)	/* tawget function suppowted */
#define	FCP_FEAT_INIT	(1 << 1)	/* initiatow function suppowted */

#endif /* _FC_FCP_H_ */
