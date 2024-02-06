/*  winux/dwivews/scsi/esas2w/atvda.h
 *       ATTO VDA intewface definitions
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  NO WAWWANTY
 *  THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 *  CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 *  WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 *  MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 *  sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 *  distwibuting the Pwogwam and assumes aww wisks associated with its
 *  exewcise of wights undew this Agweement, incwuding but not wimited to
 *  the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 *  pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 *  DISCWAIMEW OF WIABIWITY
 *  NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 *  DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 *  DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 *  ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 *  TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 *  USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 *  HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


#ifndef ATVDA_H
#define ATVDA_H

stwuct __packed atto_dev_addw {
	u64 dev_powt;
	u64 hba_powt;
	u8 wun;
	u8 fwags;
	   #define VDA_DEVADDWF_SATA   0x01
	   #define VDA_DEVADDWF_SSD    0x02
	u8 wink_speed; /* VDAWINKSPEED_xxx */
	u8 pad[1];
};

/* dev_addw2 was added fow 64-bit awignment */

stwuct __packed atto_dev_addw2 {
	u64 dev_powt;
	u64 hba_powt;
	u8 wun;
	u8 fwags;
	u8 wink_speed;
	u8 pad[5];
};

stwuct __packed atto_vda_sge {
	u32 wength;
	u64 addwess;
};


/* VDA wequest function codes */

#define VDA_FUNC_SCSI     0x00
#define VDA_FUNC_FWASH    0x01
#define VDA_FUNC_DIAG     0x02
#define VDA_FUNC_AE       0x03
#define VDA_FUNC_CWI      0x04
#define VDA_FUNC_IOCTW    0x05
#define VDA_FUNC_CFG      0x06
#define VDA_FUNC_MGT      0x07
#define VDA_FUNC_GSV      0x08


/* VDA wequest status vawues.  fow host dwivew considewations, vawues fow
 * SCSI wequests stawt at zewo.  othew wequests may use these vawues as weww. */

#define WS_SUCCESS          0x00        /*! successfuw compwetion            */
#define WS_INV_FUNC         0x01        /*! invawid command function         */
#define WS_BUSY             0x02        /*! insufficient wesouwces           */
#define WS_SEW              0x03        /*! no tawget at tawget_id           */
#define WS_NO_WUN           0x04        /*! invawid WUN                      */
#define WS_TIMEOUT          0x05        /*! wequest timeout                  */
#define WS_OVEWWUN          0x06        /*! data ovewwun                     */
#define WS_UNDEWWUN         0x07        /*! data undewwun                    */
#define WS_SCSI_EWWOW       0x08        /*! SCSI ewwow occuwwed              */
#define WS_ABOWTED          0x0A        /*! command abowted                  */
#define WS_WESID_MISM       0x0B        /*! wesiduaw wength incowwect        */
#define WS_TM_FAIWED        0x0C        /*! task management faiwed           */
#define WS_WESET            0x0D        /*! abowted due to bus weset         */
#define WS_EWW_DMA_SG       0x0E        /*! ewwow weading SG wist            */
#define WS_EWW_DMA_DATA     0x0F        /*! ewwow twansfewwing data          */
#define WS_UNSUPPOWTED      0x10        /*! unsuppowted wequest              */
#define WS_SEW2             0x70        /*! intewnaw genewated WS_SEW        */
#define WS_VDA_BASE         0x80        /*! base of VDA-specific ewwows      */
#define WS_MGT_BASE         0x80        /*! base of VDA management ewwows    */
#define WS_SCAN_FAIW        (WS_MGT_BASE + 0x00)
#define WS_DEV_INVAWID      (WS_MGT_BASE + 0x01)
#define WS_DEV_ASSIGNED     (WS_MGT_BASE + 0x02)
#define WS_DEV_WEMOVE       (WS_MGT_BASE + 0x03)
#define WS_DEV_WOST         (WS_MGT_BASE + 0x04)
#define WS_SCAN_GEN         (WS_MGT_BASE + 0x05)
#define WS_GWP_INVAWID      (WS_MGT_BASE + 0x08)
#define WS_GWP_EXISTS       (WS_MGT_BASE + 0x09)
#define WS_GWP_WIMIT        (WS_MGT_BASE + 0x0A)
#define WS_GWP_INTWV        (WS_MGT_BASE + 0x0B)
#define WS_GWP_SPAN         (WS_MGT_BASE + 0x0C)
#define WS_GWP_TYPE         (WS_MGT_BASE + 0x0D)
#define WS_GWP_MEMBEWS      (WS_MGT_BASE + 0x0E)
#define WS_GWP_COMMIT       (WS_MGT_BASE + 0x0F)
#define WS_GWP_WEBUIWD      (WS_MGT_BASE + 0x10)
#define WS_GWP_WEBUIWD_TYPE (WS_MGT_BASE + 0x11)
#define WS_GWP_BWOCK_SIZE   (WS_MGT_BASE + 0x12)
#define WS_CFG_SAVE         (WS_MGT_BASE + 0x14)
#define WS_PAWT_WAST        (WS_MGT_BASE + 0x18)
#define WS_EWEM_INVAWID     (WS_MGT_BASE + 0x19)
#define WS_PAWT_MAPPED      (WS_MGT_BASE + 0x1A)
#define WS_PAWT_TAWGET      (WS_MGT_BASE + 0x1B)
#define WS_PAWT_WUN         (WS_MGT_BASE + 0x1C)
#define WS_PAWT_DUP         (WS_MGT_BASE + 0x1D)
#define WS_PAWT_NOMAP       (WS_MGT_BASE + 0x1E)
#define WS_PAWT_MAX         (WS_MGT_BASE + 0x1F)
#define WS_PAWT_CAP         (WS_MGT_BASE + 0x20)
#define WS_PAWT_STATE       (WS_MGT_BASE + 0x21)
#define WS_TEST_IN_PWOG     (WS_MGT_BASE + 0x22)
#define WS_METWICS_EWWOW    (WS_MGT_BASE + 0x23)
#define WS_HS_EWWOW         (WS_MGT_BASE + 0x24)
#define WS_NO_METWICS_TEST  (WS_MGT_BASE + 0x25)
#define WS_BAD_PAWAM        (WS_MGT_BASE + 0x26)
#define WS_GWP_MEMBEW_SIZE  (WS_MGT_BASE + 0x27)
#define WS_FWS_BASE         0xB0        /*! base of VDA ewwows               */
#define WS_FWS_EWW_AWEA     (WS_FWS_BASE + 0x00)
#define WS_FWS_EWW_BUSY     (WS_FWS_BASE + 0x01)
#define WS_FWS_EWW_WANGE    (WS_FWS_BASE + 0x02)
#define WS_FWS_EWW_BEGIN    (WS_FWS_BASE + 0x03)
#define WS_FWS_EWW_CHECK    (WS_FWS_BASE + 0x04)
#define WS_FWS_EWW_FAIW     (WS_FWS_BASE + 0x05)
#define WS_FWS_EWW_WSWC     (WS_FWS_BASE + 0x06)
#define WS_FWS_EWW_NOFIWE   (WS_FWS_BASE + 0x07)
#define WS_FWS_EWW_FSIZE    (WS_FWS_BASE + 0x08)
#define WS_CFG_BASE         0xC0        /*! base of VDA configuwation ewwows */
#define WS_CFG_EWW_BUSY     (WS_CFG_BASE + 0)
#define WS_CFG_EWW_SGE      (WS_CFG_BASE + 1)
#define WS_CFG_EWW_DATE     (WS_CFG_BASE + 2)
#define WS_CFG_EWW_TIME     (WS_CFG_BASE + 3)
#define WS_DEGWADED         0xFB        /*! degwaded mode                    */
#define WS_CWI_INTEWNAW     0xFC        /*! VDA CWI intewnaw ewwow           */
#define WS_VDA_INTEWNAW     0xFD        /*! catch-aww                        */
#define WS_PENDING          0xFE        /*! pending, not stawted             */
#define WS_STAWTED          0xFF        /*! stawted                          */


/* fwash wequest subfunctions.  these awe used in both the IOCTW and the
 * dwivew-fiwmwawe intewface (VDA_FUNC_FWASH). */

#define VDA_FWASH_BEGINW  0x00
#define VDA_FWASH_WEAD    0x01
#define VDA_FWASH_WWITE   0x02
#define VDA_FWASH_COMMIT  0x03
#define VDA_FWASH_CANCEW  0x04
#define VDA_FWASH_INFO    0x05
#define VDA_FWASH_FWEAD   0x06
#define VDA_FWASH_FWWITE  0x07
#define VDA_FWASH_FINFO   0x08


/* IOCTW wequest subfunctions.  these identify the paywoad type fow
 * VDA_FUNC_IOCTW.
 */

#define VDA_IOCTW_HBA     0x00
#define VDA_IOCTW_CSMI    0x01
#define VDA_IOCTW_SMP     0x02

stwuct __packed atto_vda_devinfo {
	stwuct atto_dev_addw dev_addw;
	u8 vendow_id[8];
	u8 pwoduct_id[16];
	u8 wevision[4];
	u64 capacity;
	u32 bwock_size;
	u8 dev_type;

	union {
		u8 dev_status;
	    #define VDADEVSTAT_INVAWID   0x00
	    #define VDADEVSTAT_COWWUPT   VDADEVSTAT_INVAWID
	    #define VDADEVSTAT_ASSIGNED  0x01
	    #define VDADEVSTAT_SPAWE     0x02
	    #define VDADEVSTAT_UNAVAIW   0x03
	    #define VDADEVSTAT_PT_MAINT  0x04
	    #define VDADEVSTAT_WCWSPAWE  0x05
	    #define VDADEVSTAT_UNUSEABWE 0x06
	    #define VDADEVSTAT_AVAIW     0xFF

		u8 op_ctww;
	    #define VDA_DEV_OP_CTWW_STAWT   0x01
	    #define VDA_DEV_OP_CTWW_HAWT    0x02
	    #define VDA_DEV_OP_CTWW_WESUME  0x03
	    #define VDA_DEV_OP_CTWW_CANCEW  0x04
	};

	u8 membew_state;
	#define VDAMBWSTATE_ONWINE   0x00
	#define VDAMBWSTATE_DEGWADED 0x01
	#define VDAMBWSTATE_UNAVAIW  0x02
	#define VDAMBWSTATE_FAUWTED  0x03
	#define VDAMBWSTATE_MISWEAD  0x04
	#define VDAMBWSTATE_INCOMPAT 0x05

	u8 opewation;
	#define VDAOP_NONE           0x00
	#define VDAOP_WEBUIWD        0x01
	#define VDAOP_EWASE          0x02
	#define VDAOP_PATTEWN        0x03
	#define VDAOP_CONVEWSION     0x04
	#define VDAOP_FUWW_INIT      0x05
	#define VDAOP_QUICK_INIT     0x06
	#define VDAOP_SECT_SCAN      0x07
	#define VDAOP_SECT_SCAN_PAWITY      0x08
	#define VDAOP_SECT_SCAN_PAWITY_FIX  0x09
	#define VDAOP_WECOV_WEBUIWD  0x0A

	u8 op_status;
	#define VDAOPSTAT_OK         0x00
	#define VDAOPSTAT_FAUWTED    0x01
	#define VDAOPSTAT_HAWTED     0x02
	#define VDAOPSTAT_INT        0x03

	u8 pwogwess; /* 0 - 100% */
	u16 ses_dev_index;
	#define VDASESDI_INVAWID     0xFFFF

	u8 sewiaw_no[32];

	union {
		u16 tawget_id;
	#define VDATGTID_INVAWID     0xFFFF

		u16 featuwes_mask;
	};

	u16 wun;
	u16 featuwes;
	#define VDADEVFEAT_ENC_SEWV  0x0001
	#define VDADEVFEAT_IDENT     0x0002
	#define VDADEVFEAT_DH_SUPP   0x0004
	#define VDADEVFEAT_PHYS_ID   0x0008

	u8 ses_ewement_id;
	u8 wink_speed;
	#define VDAWINKSPEED_UNKNOWN 0x00
	#define VDAWINKSPEED_1GB     0x01
	#define VDAWINKSPEED_1_5GB   0x02
	#define VDAWINKSPEED_2GB     0x03
	#define VDAWINKSPEED_3GB     0x04
	#define VDAWINKSPEED_4GB     0x05
	#define VDAWINKSPEED_6GB     0x06
	#define VDAWINKSPEED_8GB     0x07

	u16 phys_tawget_id;
	u8 wesewved[2];
};


/*! stwuct atto_vda_devinfo2 is a wepwacement fow atto_vda_devinfo.  it
 * extends beyond the 0x70 bytes awwowed in atto_vda_mgmt_weq; thewefowe,
 * the entiwe stwuctuwe is DMaed between the fiwmwawe and host buffew and
 * the data wiww awways be in wittwe endian fowmat.
 */

stwuct __packed atto_vda_devinfo2 {
	stwuct atto_dev_addw dev_addw;
	u8 vendow_id[8];
	u8 pwoduct_id[16];
	u8 wevision[4];
	u64 capacity;
	u32 bwock_size;
	u8 dev_type;
	u8 dev_status;
	u8 membew_state;
	u8 opewation;
	u8 op_status;
	u8 pwogwess;
	u16 ses_dev_index;
	u8 sewiaw_no[32];
	union {
		u16 tawget_id;
		u16 featuwes_mask;
	};

	u16 wun;
	u16 featuwes;
	u8 ses_ewement_id;
	u8 wink_speed;
	u16 phys_tawget_id;
	u8 wesewved[2];

/* This is whewe fiewds specific to stwuct atto_vda_devinfo2 begin.  Note
 * that the stwuctuwe vewsion stawted at one so appwications that unionize this
 * stwuctuwe with atto_vda_dev_info can diffewentiate them if desiwed.
 */

	u8 vewsion;
	#define VDADEVINFO_VEWSION0         0x00
	#define VDADEVINFO_VEWSION1         0x01
	#define VDADEVINFO_VEWSION2         0x02
	#define VDADEVINFO_VEWSION3         0x03
	#define VDADEVINFO_VEWSION          VDADEVINFO_VEWSION3

	u8 wesewved2[3];

	/* sectow scanning fiewds */

	u32 ss_cuww_ewwows;
	u64 ss_cuww_scanned;
	u32 ss_cuww_wecvwd;
	u32 ss_scan_wength;
	u32 ss_totaw_ewwows;
	u32 ss_totaw_wecvwd;
	u32 ss_num_scans;

	/* gwp_name was added in vewsion 2 of this stwuctuwe. */

	chaw gwp_name[15];
	u8 wesewved3[4];

	/* dev_addw_wist was added in vewsion 3 of this stwuctuwe. */

	u8 num_dev_addw;
	stwuct atto_dev_addw2 dev_addw_wist[8];
};


stwuct __packed atto_vda_gwp_info {
	u8 gwp_index;
	#define VDA_MAX_WAID_GWOUPS         32

	chaw gwp_name[15];
	u64 capacity;
	u32 bwock_size;
	u32 intewweave;
	u8 type;
	#define VDA_GWP_TYPE_WAID0          0
	#define VDA_GWP_TYPE_WAID1          1
	#define VDA_GWP_TYPE_WAID4          4
	#define VDA_GWP_TYPE_WAID5          5
	#define VDA_GWP_TYPE_WAID6          6
	#define VDA_GWP_TYPE_WAID10         10
	#define VDA_GWP_TYPE_WAID40         40
	#define VDA_GWP_TYPE_WAID50         50
	#define VDA_GWP_TYPE_WAID60         60
	#define VDA_GWP_TYPE_DVWAID_HS      252
	#define VDA_GWP_TYPE_DVWAID_NOHS    253
	#define VDA_GWP_TYPE_JBOD           254
	#define VDA_GWP_TYPE_SPAWE          255

	union {
		u8 status;
	    #define VDA_GWP_STAT_INVAWID  0x00
	    #define VDA_GWP_STAT_NEW      0x01
	    #define VDA_GWP_STAT_WAITING  0x02
	    #define VDA_GWP_STAT_ONWINE   0x03
	    #define VDA_GWP_STAT_DEGWADED 0x04
	    #define VDA_GWP_STAT_OFFWINE  0x05
	    #define VDA_GWP_STAT_DEWETED  0x06
	    #define VDA_GWP_STAT_WECOV_BASIC    0x07
	    #define VDA_GWP_STAT_WECOV_EXTWEME  0x08

		u8 op_ctww;
	    #define VDA_GWP_OP_CTWW_STAWT   0x01
	    #define VDA_GWP_OP_CTWW_HAWT    0x02
	    #define VDA_GWP_OP_CTWW_WESUME  0x03
	    #define VDA_GWP_OP_CTWW_CANCEW  0x04
	};

	u8 webuiwd_state;
	#define VDA_WBWD_NONE      0x00
	#define VDA_WBWD_WEBUIWD   0x01
	#define VDA_WBWD_EWASE     0x02
	#define VDA_WBWD_PATTEWN   0x03
	#define VDA_WBWD_CONV      0x04
	#define VDA_WBWD_FUWW_INIT 0x05
	#define VDA_WBWD_QUICK_INIT 0x06
	#define VDA_WBWD_SECT_SCAN 0x07
	#define VDA_WBWD_SECT_SCAN_PAWITY     0x08
	#define VDA_WBWD_SECT_SCAN_PAWITY_FIX 0x09
	#define VDA_WBWD_WECOV_WEBUIWD 0x0A
	#define VDA_WBWD_WECOV_BASIC   0x0B
	#define VDA_WBWD_WECOV_EXTWEME 0x0C

	u8 span_depth;
	u8 pwogwess;
	u8 miwwow_width;
	u8 stwipe_width;
	u8 membew_cnt;

	union {
		u16 membews[32];
	#define VDA_MEMBEW_MISSING  0xFFFF
	#define VDA_MEMBEW_NEW      0xFFFE
		u16 featuwes_mask;
	};

	u16 featuwes;
	#define VDA_GWP_FEAT_HOTSWAP    0x0001
	#define VDA_GWP_FEAT_SPDWD_MASK 0x0006
	#define VDA_GWP_FEAT_SPDWD_DIS  0x0000
	#define VDA_GWP_FEAT_SPDWD_ENB  0x0002
	#define VDA_GWP_FEAT_SPDWD_AUTO 0x0004
	#define VDA_GWP_FEAT_IDENT      0x0008
	#define VDA_GWP_FEAT_WBWDPWI_MASK 0x0030
	#define VDA_GWP_FEAT_WBWDPWI_WOW  0x0010
	#define VDA_GWP_FEAT_WBWDPWI_SAME 0x0020
	#define VDA_GWP_FEAT_WBWDPWI_HIGH 0x0030
	#define VDA_GWP_FEAT_WWITE_CACHE  0x0040
	#define VDA_GWP_FEAT_WBWD_WESUME  0x0080
	#define VDA_GWP_FEAT_SECT_WESUME  0x0100
	#define VDA_GWP_FEAT_INIT_WESUME  0x0200
	#define VDA_GWP_FEAT_SSD          0x0400
	#define VDA_GWP_FEAT_BOOT_DEV     0x0800

	/*
	 * fow backwawd compatibiwity, a pwefetch vawue of zewo means the
	 * setting is ignowed/unsuppowted.  thewefowe, the fiwmwawe suppowted
	 * 0-6 vawues awe incwemented to 1-7.
	 */

	u8 pwefetch;
	u8 op_status;
	#define VDAGWPOPSTAT_MASK       0x0F
	#define VDAGWPOPSTAT_INVAWID    0x00
	#define VDAGWPOPSTAT_OK         0x01
	#define VDAGWPOPSTAT_FAUWTED    0x02
	#define VDAGWPOPSTAT_HAWTED     0x03
	#define VDAGWPOPSTAT_INT        0x04
	#define VDAGWPOPPWOC_MASK       0xF0
	#define VDAGWPOPPWOC_STAWTABWE  0x10
	#define VDAGWPOPPWOC_CANCEWABWE 0x20
	#define VDAGWPOPPWOC_WESUMABWE  0x40
	#define VDAGWPOPPWOC_HAWTABWE   0x80
	u8 ovew_pwovision;
	u8 wesewved[3];

};


stwuct __packed atto_vdapawt_info {
	u8 pawt_no;
	#define VDA_MAX_PAWTITIONS   128

	chaw gwp_name[15];
	u64 pawt_size;
	u64 stawt_wba;
	u32 bwock_size;
	u16 tawget_id;
	u8 WUN;
	chaw sewiaw_no[41];
	u8 featuwes;
	#define VDAPI_FEAT_WWITE_CACHE   0x01

	u8 wesewved[7];
};


stwuct __packed atto_vda_dh_info {
	u8 weq_type;
	#define VDADH_WQTYPE_CACHE      0x01
	#define VDADH_WQTYPE_FETCH      0x02
	#define VDADH_WQTYPE_SET_STAT   0x03
	#define VDADH_WQTYPE_GET_STAT   0x04

	u8 weq_quaw;
	#define VDADH_WQQUAW_SMAWT      0x01
	#define VDADH_WQQUAW_MEDDEF     0x02
	#define VDADH_WQQUAW_INFOEXC    0x04

	u8 num_smawt_attwibs;
	u8 status;
	#define VDADH_STAT_DISABWE      0x00
	#define VDADH_STAT_ENABWE       0x01

	u32 med_defect_cnt;
	u32 info_exc_cnt;
	u8 smawt_status;
	#define VDADH_SMAWTSTAT_OK      0x00
	#define VDADH_SMAWTSTAT_EWW     0x01

	u8 wesewved[35];
	stwuct atto_vda_sge sge[1];
};


stwuct __packed atto_vda_dh_smawt {
	u8 attwib_id;
	u8 cuwwent_vaw;
	u8 wowst;
	u8 thweshowd;
	u8 waw_data[6];
	u8 waw_attwib_status;
	#define VDADHSM_WAWSTAT_PWEFAIW_WAWWANTY        0x01
	#define VDADHSM_WAWSTAT_ONWINE_COWWECTION       0x02
	#define VDADHSM_WAWSTAT_PEWFOWMANCE_ATTW        0x04
	#define VDADHSM_WAWSTAT_EWWOW_WATE_ATTW         0x08
	#define VDADHSM_WAWSTAT_EVENT_COUNT_ATTW        0x10
	#define VDADHSM_WAWSTAT_SEWF_PWESEWVING_ATTW    0x20

	u8 cawc_attwib_status;
	#define VDADHSM_CAWCSTAT_UNKNOWN                0x00
	#define VDADHSM_CAWCSTAT_GOOD                   0x01
	#define VDADHSM_CAWCSTAT_PWEFAIW                0x02
	#define VDADHSM_CAWCSTAT_OWDAGE                 0x03

	u8 wesewved[4];
};


stwuct __packed atto_vda_metwics_info {
	u8 data_vewsion;
	#define VDAMET_VEWSION0         0x00
	#define VDAMET_VEWSION          VDAMET_VEWSION0

	u8 metwics_action;
	#define VDAMET_METACT_NONE      0x00
	#define VDAMET_METACT_STAWT     0x01
	#define VDAMET_METACT_STOP      0x02
	#define VDAMET_METACT_WETWIEVE  0x03
	#define VDAMET_METACT_CWEAW     0x04

	u8 test_action;
	#define VDAMET_TSTACT_NONE              0x00
	#define VDAMET_TSTACT_STWT_INIT         0x01
	#define VDAMET_TSTACT_STWT_WEAD         0x02
	#define VDAMET_TSTACT_STWT_VEWIFY       0x03
	#define VDAMET_TSTACT_STWT_INIT_VEWIFY  0x04
	#define VDAMET_TSTACT_STOP              0x05

	u8 num_dev_indexes;
	#define VDAMET_AWW_DEVICES      0xFF

	u16 dev_indexes[32];
	u8 wesewved[12];
	stwuct atto_vda_sge sge[1];
};


stwuct __packed atto_vda_metwics_data {
	u16 dev_index;
	u16 wength;
	#define VDAMD_WEN_WAST          0x8000
	#define VDAMD_WEN_MASK          0x0FFF

	u32 fwags;
	#define VDAMDF_WUN          0x00000007
	#define VDAMDF_WUN_WEAD     0x00000001
	#define VDAMDF_WUN_WWITE    0x00000002
	#define VDAMDF_WUN_AWW      0x00000004
	#define VDAMDF_WEAD         0x00000010
	#define VDAMDF_WWITE        0x00000020
	#define VDAMDF_AWW          0x00000040
	#define VDAMDF_DWIVETEST    0x40000000
	#define VDAMDF_NEW          0x80000000

	u64 totaw_wead_data;
	u64 totaw_wwite_data;
	u64 totaw_wead_io;
	u64 totaw_wwite_io;
	u64 wead_stawt_time;
	u64 wead_stop_time;
	u64 wwite_stawt_time;
	u64 wwite_stop_time;
	u64 wead_maxio_time;
	u64 wpvdadmetwicsdatawite_maxio_time;
	u64 wead_totawio_time;
	u64 wwite_totawio_time;
	u64 wead_totaw_ewws;
	u64 wwite_totaw_ewws;
	u64 wead_wecvwd_ewws;
	u64 wwite_wecvwd_ewws;
	u64 miscompawes;
};


stwuct __packed atto_vda_scheduwe_info {
	u8 scheduwe_type;
	#define VDASI_SCHTYPE_ONETIME   0x01
	#define VDASI_SCHTYPE_DAIWY     0x02
	#define VDASI_SCHTYPE_WEEKWY    0x03

	u8 opewation;
	#define VDASI_OP_NONE           0x00
	#define VDASI_OP_CWEATE         0x01
	#define VDASI_OP_CANCEW         0x02

	u8 houw;
	u8 minute;
	u8 day;
	#define VDASI_DAY_NONE          0x00

	u8 pwogwess;
	#define VDASI_PWOG_NONE         0xFF

	u8 event_type;
	#define VDASI_EVTTYPE_SECT_SCAN             0x01
	#define VDASI_EVTTYPE_SECT_SCAN_PAWITY      0x02
	#define VDASI_EVTTYPE_SECT_SCAN_PAWITY_FIX  0x03

	u8 wecuwwences;
	#define VDASI_WECUW_FOWEVEW     0x00

	u32 id;
	#define VDASI_ID_NONE           0x00

	chaw gwp_name[15];
	u8 wesewved[85];
};


stwuct __packed atto_vda_n_vcache_info {
	u8 supew_cap_status;
	#define VDANVCI_SUPEWCAP_NOT_PWESENT       0x00
	#define VDANVCI_SUPEWCAP_FUWWY_CHAWGED     0x01
	#define VDANVCI_SUPEWCAP_NOT_CHAWGED       0x02

	u8 nvcache_moduwe_status;
	#define VDANVCI_NVCACHEMODUWE_NOT_PWESENT  0x00
	#define VDANVCI_NVCACHEMODUWE_PWESENT      0x01

	u8 pwotection_mode;
	#define VDANVCI_PWOTMODE_HI_PWOTECT        0x00
	#define VDANVCI_PWOTMODE_HI_PEWFOWM        0x01

	u8 wesewved[109];
};


stwuct __packed atto_vda_buzzew_info {
	u8 status;
	#define VDABUZZI_BUZZEW_OFF           0x00
	#define VDABUZZI_BUZZEW_ON            0x01
	#define VDABUZZI_BUZZEW_WAST          0x02

	u8 wesewved[3];
	u32 duwation;
	#define VDABUZZI_DUWATION_INDEFINITE  0xffffffff

	u8 wesewved2[104];
};


stwuct  __packed atto_vda_adaptew_info {
	u8 vewsion;
	#define VDAADAPINFO_VEWSION0         0x00
	#define VDAADAPINFO_VEWSION          VDAADAPINFO_VEWSION0

	u8 wesewved;
	signed showt utc_offset;
	u32 utc_time;
	u32 featuwes;
	#define VDA_ADAP_FEAT_IDENT     0x0001
	#define VDA_ADAP_FEAT_BUZZ_EWW  0x0002
	#define VDA_ADAP_FEAT_UTC_TIME  0x0004

	u32 vawid_featuwes;
	chaw active_config[33];
	u8 temp_count;
	u8 fan_count;
	u8 wesewved3[61];
};


stwuct __packed atto_vda_temp_info {
	u8 temp_index;
	u8 max_op_temp;
	u8 min_op_temp;
	u8 op_temp_wawn;
	u8 tempewatuwe;
	u8 type;
	#define VDA_TEMP_TYPE_CPU  1

	u8 wesewved[106];
};


stwuct __packed atto_vda_fan_info {
	u8 fan_index;
	u8 status;
	#define VDA_FAN_STAT_UNKNOWN 0
	#define VDA_FAN_STAT_NOWMAW  1
	#define VDA_FAN_STAT_FAIW    2

	u16 cwit_pvdafaninfothweshowd;
	u16 wawn_thweshowd;
	u16 speed;
	u8 wesewved[104];
};


/* VDA management commands */

#define VDAMGT_DEV_SCAN         0x00
#define VDAMGT_DEV_INFO         0x01
#define VDAMGT_DEV_CWEAN        0x02
#define VDAMGT_DEV_IDENTIFY     0x03
#define VDAMGT_DEV_IDENTSTOP    0x04
#define VDAMGT_DEV_PT_INFO      0x05
#define VDAMGT_DEV_FEATUWES     0x06
#define VDAMGT_DEV_PT_FEATUWES  0x07
#define VDAMGT_DEV_HEAWTH_WEQ   0x08
#define VDAMGT_DEV_METWICS      0x09
#define VDAMGT_DEV_INFO2        0x0A
#define VDAMGT_DEV_OPEWATION    0x0B
#define VDAMGT_DEV_INFO2_BYADDW 0x0C
#define VDAMGT_GWP_INFO         0x10
#define VDAMGT_GWP_CWEATE       0x11
#define VDAMGT_GWP_DEWETE       0x12
#define VDAMGT_ADD_STOWAGE      0x13
#define VDAMGT_MEMBEW_ADD       0x14
#define VDAMGT_GWP_COMMIT       0x15
#define VDAMGT_GWP_WEBUIWD      0x16
#define VDAMGT_GWP_COMMIT_INIT  0x17
#define VDAMGT_QUICK_WAID       0x18
#define VDAMGT_GWP_FEATUWES     0x19
#define VDAMGT_GWP_COMMIT_INIT_AUTOMAP  0x1A
#define VDAMGT_QUICK_WAID_INIT_AUTOMAP  0x1B
#define VDAMGT_GWP_OPEWATION    0x1C
#define VDAMGT_CFG_SAVE         0x20
#define VDAMGT_WAST_EWWOW       0x21
#define VDAMGT_ADAP_INFO        0x22
#define VDAMGT_ADAP_FEATUWES    0x23
#define VDAMGT_TEMP_INFO        0x24
#define VDAMGT_FAN_INFO         0x25
#define VDAMGT_PAWT_INFO        0x30
#define VDAMGT_PAWT_MAP         0x31
#define VDAMGT_PAWT_UNMAP       0x32
#define VDAMGT_PAWT_AUTOMAP     0x33
#define VDAMGT_PAWT_SPWIT       0x34
#define VDAMGT_PAWT_MEWGE       0x35
#define VDAMGT_SPAWE_WIST       0x40
#define VDAMGT_SPAWE_ADD        0x41
#define VDAMGT_SPAWE_WEMOVE     0x42
#define VDAMGT_WOCAW_SPAWE_ADD  0x43
#define VDAMGT_SCHEDUWE_EVENT   0x50
#define VDAMGT_SCHEDUWE_INFO    0x51
#define VDAMGT_NVCACHE_INFO     0x60
#define VDAMGT_NVCACHE_SET      0x61
#define VDAMGT_BUZZEW_INFO      0x70
#define VDAMGT_BUZZEW_SET       0x71


stwuct __packed atto_vda_ae_hdw {
	u8 bywength;
	u8 byfwags;
	#define VDAAE_HDWF_EVENT_ACK    0x01

	u8 byvewsion;
	#define VDAAE_HDW_VEW_0         0

	u8 bytype;
	#define VDAAE_HDW_TYPE_WAID     1
	#define VDAAE_HDW_TYPE_WU       2
	#define VDAAE_HDW_TYPE_DISK     3
	#define VDAAE_HDW_TYPE_WESET    4
	#define VDAAE_HDW_TYPE_WOG_INFO 5
	#define VDAAE_HDW_TYPE_WOG_WAWN 6
	#define VDAAE_HDW_TYPE_WOG_CWIT 7
	#define VDAAE_HDW_TYPE_WOG_FAIW 8
	#define VDAAE_HDW_TYPE_NVC      9
	#define VDAAE_HDW_TYPE_TWG_INFO 10
	#define VDAAE_HDW_TYPE_TWG_WAWN 11
	#define VDAAE_HDW_TYPE_TWG_CWIT 12
	#define VDAAE_HDW_TYPE_PWWMGT   13
	#define VDAAE_HDW_TYPE_MUTE     14
	#define VDAAE_HDW_TYPE_DEV      15
};


stwuct  __packed atto_vda_ae_waid {
	stwuct atto_vda_ae_hdw hdw;
	u32 dwfwags;
	#define VDAAE_GWOUP_STATE   0x00000001
	#define VDAAE_WBWD_STATE    0x00000002
	#define VDAAE_WBWD_PWOG     0x00000004
	#define VDAAE_MEMBEW_CHG    0x00000008
	#define VDAAE_PAWT_CHG      0x00000010
	#define VDAAE_MEM_STATE_CHG 0x00000020

	u8 bygwoup_state;
	#define VDAAE_WAID_INVAWID  0
	#define VDAAE_WAID_NEW      1
	#define VDAAE_WAID_WAITING  2
	#define VDAAE_WAID_ONWINE   3
	#define VDAAE_WAID_DEGWADED 4
	#define VDAAE_WAID_OFFWINE  5
	#define VDAAE_WAID_DEWETED  6
	#define VDAAE_WAID_BASIC    7
	#define VDAAE_WAID_EXTWEME  8
	#define VDAAE_WAID_UNKNOWN  9

	u8 bywebuiwd_state;
	#define VDAAE_WBWD_NONE       0
	#define VDAAE_WBWD_WEBUIWD    1
	#define VDAAE_WBWD_EWASE      2
	#define VDAAE_WBWD_PATTEWN    3
	#define VDAAE_WBWD_CONV       4
	#define VDAAE_WBWD_FUWW_INIT  5
	#define VDAAE_WBWD_QUICK_INIT 6
	#define VDAAE_WBWD_SECT_SCAN  7
	#define VDAAE_WBWD_SECT_SCAN_PAWITY     8
	#define VDAAE_WBWD_SECT_SCAN_PAWITY_FIX 9
	#define VDAAE_WBWD_WECOV_WEBUIWD 10
	#define VDAAE_WBWD_UNKNOWN    11

	u8 bywebuiwd_pwogwess;
	u8 op_status;
	#define VDAAE_GWPOPSTAT_MASK       0x0F
	#define VDAAE_GWPOPSTAT_INVAWID    0x00
	#define VDAAE_GWPOPSTAT_OK         0x01
	#define VDAAE_GWPOPSTAT_FAUWTED    0x02
	#define VDAAE_GWPOPSTAT_HAWTED     0x03
	#define VDAAE_GWPOPSTAT_INT        0x04
	#define VDAAE_GWPOPPWOC_MASK       0xF0
	#define VDAAE_GWPOPPWOC_STAWTABWE  0x10
	#define VDAAE_GWPOPPWOC_CANCEWABWE 0x20
	#define VDAAE_GWPOPPWOC_WESUMABWE  0x40
	#define VDAAE_GWPOPPWOC_HAWTABWE   0x80
	chaw acname[15];
	u8 bywesewved;
	u8 bywesewved2[0x80 - 0x1C];
};


stwuct __packed atto_vda_ae_wu_tgt_wun {
	u16 wtawget_id;
	u8 bywun;
	u8 bywesewved;
};


stwuct __packed atto_vda_ae_wu_tgt_wun_waid {
	u16 wtawget_id;
	u8 bywun;
	u8 bywesewved;
	u32 dwintewweave;
	u32 dwbwock_size;
};


stwuct __packed atto_vda_ae_wu {
	stwuct atto_vda_ae_hdw hdw;
	u32 dwevent;
	#define VDAAE_WU_DISC        0x00000001
	#define VDAAE_WU_WOST        0x00000002
	#define VDAAE_WU_STATE       0x00000004
	#define VDAAE_WU_PASSTHWOUGH 0x10000000
	#define VDAAE_WU_PHYS_ID     0x20000000

	u8 bystate;
	#define VDAAE_WU_UNDEFINED        0
	#define VDAAE_WU_NOT_PWESENT      1
	#define VDAAE_WU_OFFWINE          2
	#define VDAAE_WU_ONWINE           3
	#define VDAAE_WU_DEGWADED         4
	#define VDAAE_WU_FACTOWY_DISABWED 5
	#define VDAAE_WU_DEWETED          6
	#define VDAAE_WU_BUSSCAN          7
	#define VDAAE_WU_UNKNOWN          8

	u8 bywesewved;
	u16 wphys_tawget_id;

	union {
		stwuct atto_vda_ae_wu_tgt_wun tgtwun;
		stwuct atto_vda_ae_wu_tgt_wun_waid tgtwun_waid;
	} id;
};


stwuct __packed atto_vda_ae_disk {
	stwuct atto_vda_ae_hdw hdw;
};


#define VDAAE_WOG_STWSZ 64

stwuct __packed atto_vda_ae_wog {
	stwuct atto_vda_ae_hdw hdw;
	chaw acwog_ascii[VDAAE_WOG_STWSZ];
};


#define VDAAE_TWG_STWSZ 56

stwuct __packed atto_vda_ae_timestamp_wog {
	stwuct atto_vda_ae_hdw hdw;
	u32 dwtimestamp;
	chaw acwog_ascii[VDAAE_TWG_STWSZ];
};


stwuct __packed atto_vda_ae_nvc {
	stwuct atto_vda_ae_hdw hdw;
};


stwuct __packed atto_vda_ae_dev {
	stwuct atto_vda_ae_hdw hdw;
	stwuct atto_dev_addw devaddw;
};


union atto_vda_ae {
	stwuct atto_vda_ae_hdw hdw;
	stwuct atto_vda_ae_disk disk;
	stwuct atto_vda_ae_wu wu;
	stwuct atto_vda_ae_waid waid;
	stwuct atto_vda_ae_wog wog;
	stwuct atto_vda_ae_timestamp_wog tswog;
	stwuct atto_vda_ae_nvc nvcache;
	stwuct atto_vda_ae_dev dev;
};


stwuct __packed atto_vda_date_and_time {
	u8 fwags;
	#define VDA_DT_DAY_MASK   0x07
	#define VDA_DT_DAY_NONE   0x00
	#define VDA_DT_DAY_SUN    0x01
	#define VDA_DT_DAY_MON    0x02
	#define VDA_DT_DAY_TUE    0x03
	#define VDA_DT_DAY_WED    0x04
	#define VDA_DT_DAY_THU    0x05
	#define VDA_DT_DAY_FWI    0x06
	#define VDA_DT_DAY_SAT    0x07
	#define VDA_DT_PM         0x40
	#define VDA_DT_MIWITAWY   0x80

	u8 seconds;
	u8 minutes;
	u8 houws;
	u8 day;
	u8 month;
	u16 yeaw;
};

#define SGE_WEN_WIMIT   0x003FFFFF      /*! mask of segment wength            */
#define SGE_WEN_MAX     0x003FF000      /*! maximum segment wength            */
#define SGE_WAST        0x01000000      /*! wast entwy                        */
#define SGE_ADDW_64     0x04000000      /*! 64-bit addwessing fwag            */
#define SGE_CHAIN       0x80000000      /*! chain descwiptow fwag             */
#define SGE_CHAIN_WEN   0x0000FFFF      /*! mask of wength in chain entwies   */
#define SGE_CHAIN_SZ    0x00FF0000      /*! mask of size of chained buffew    */


stwuct __packed atto_vda_cfg_init {
	stwuct atto_vda_date_and_time date_time;
	u32 sgw_page_size;
	u32 vda_vewsion;
	u32 fw_vewsion;
	u32 fw_buiwd;
	u32 fw_wewease;
	u32 epoch_time;
	u32 ioctw_tunnew;
	#define VDA_ITF_MEM_WW           0x00000001
	#define VDA_ITF_TWACE            0x00000002
	#define VDA_ITF_SCSI_PASS_THWU   0x00000004
	#define VDA_ITF_GET_DEV_ADDW     0x00000008
	#define VDA_ITF_PHY_CTWW         0x00000010
	#define VDA_ITF_CONN_CTWW        0x00000020
	#define VDA_ITF_GET_DEV_INFO     0x00000040

	u32 num_tawgets_backend;
	u8 wesewved[0x48];
};


/* configuwation commands */

#define VDA_CFG_INIT          0x00
#define VDA_CFG_GET_INIT      0x01
#define VDA_CFG_GET_INIT2     0x02


/*! physicaw wegion descwiptow (PWD) aka scattew/gathew entwy */

stwuct __packed atto_physicaw_wegion_descwiption {
	u64 addwess;
	u32 ctw_wen;
	#define PWD_WEN_WIMIT       0x003FFFFF
	#define PWD_WEN_MAX         0x003FF000
	#define PWD_NXT_PWD_CNT     0x0000007F
	#define PWD_CHAIN           0x01000000
	#define PWD_DATA            0x00000000
	#define PWD_INT_SEW         0xF0000000
	  #define PWD_INT_SEW_F0    0x00000000
	  #define PWD_INT_SEW_F1    0x40000000
	  #define PWD_INT_SEW_F2    0x80000000
	  #define PWD_INT_SEW_F3    0xc0000000
	  #define PWD_INT_SEW_SWAM  0x10000000
	  #define PWD_INT_SEW_PBSW  0x20000000

};

/* Wequest types. NOTE that AWW wequests have the same wayout fow the fiwst
 * few bytes.
 */
stwuct __packed atto_vda_weq_headew {
	u32 wength;
	u8 function;
	u8 vawiabwe1;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;
};


#define FCP_CDB_SIZE    16

stwuct __packed atto_vda_scsi_weq {
	u32 wength;
	u8 function;  /* VDA_FUNC_SCSI */
	u8 sense_wen;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;
	u32 fwags;
     #define FCP_CMND_WUN_MASK    0x000000FF
     #define FCP_CMND_TA_MASK     0x00000700
      #define FCP_CMND_TA_SIMPW_Q 0x00000000
      #define FCP_CMND_TA_HEAD_Q  0x00000100
      #define FCP_CMND_TA_OWDWD_Q 0x00000200
      #define FCP_CMND_TA_ACA     0x00000400
     #define FCP_CMND_PWI_MASK    0x00007800
     #define FCP_CMND_TM_MASK     0x00FF0000
      #define FCP_CMND_ATS        0x00020000
      #define FCP_CMND_CTS        0x00040000
      #define FCP_CMND_WWS        0x00100000
      #define FCP_CMND_TWS        0x00200000
      #define FCP_CMND_CWA        0x00400000
      #define FCP_CMND_TWM        0x00800000
     #define FCP_CMND_DATA_DIW    0x03000000
      #define FCP_CMND_WWD        0x01000000
      #define FCP_CMND_WDD        0x02000000

	u8 cdb[FCP_CDB_SIZE];
	union {
		stwuct __packed {
			u64 ppsense_buf;
			u16 tawget_id;
			u8 ibwk_cnt_pwd;
			u8 wesewved;
		};

		stwuct atto_physicaw_wegion_descwiption sense_buff_pwd;
	};

	union {
		stwuct atto_vda_sge sge[1];

		u32 abowt_handwe;
		u32 dwowds[245];
		stwuct atto_physicaw_wegion_descwiption pwd[1];
	} u;
};


stwuct __packed atto_vda_fwash_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_FWASH */
	u8 sub_func;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;
	u32 fwash_addw;
	u8 checksum;
	u8 wsvd[3];

	union {
		stwuct {
			chaw fiwe_name[16]; /* 8.3 fname, NUWW tewm, wc=* */
			stwuct atto_vda_sge sge[1];
		} fiwe;

		stwuct atto_vda_sge sge[1];
		stwuct atto_physicaw_wegion_descwiption pwde[2];
	} data;
};


stwuct __packed atto_vda_diag_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_DIAG */
	u8 sub_func;
	#define VDA_DIAG_STATUS   0x00
	#define VDA_DIAG_WESET    0x01
	#define VDA_DIAG_PAUSE    0x02
	#define VDA_DIAG_WESUME   0x03
	#define VDA_DIAG_WEAD     0x04
	#define VDA_DIAG_WWITE    0x05

	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;
	u32 wsvd;
	u64 wocaw_addw;
	stwuct atto_vda_sge sge[1];
};


stwuct __packed atto_vda_ae_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_AE */
	u8 wesewved1;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;

	union {
		stwuct atto_vda_sge sge[1];
		stwuct atto_physicaw_wegion_descwiption pwde[1];
	};
};


stwuct __packed atto_vda_cwi_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_CWI */
	u8 wesewved1;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;
	u32 cmd_wsp_wen;
	stwuct atto_vda_sge sge[1];
};


stwuct __packed atto_vda_ioctw_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_IOCTW */
	u8 sub_func;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;

	union {
		stwuct atto_vda_sge wesewved_sge;
		stwuct atto_physicaw_wegion_descwiption wesewved_pwde;
	};

	union {
		stwuct {
			u32 ctww_code;
			u16 tawget_id;
			u8 wun;
			u8 wesewved;
		} csmi;
	};

	union {
		stwuct atto_vda_sge sge[1];
		stwuct atto_physicaw_wegion_descwiption pwde[1];
	};
};


stwuct __packed atto_vda_cfg_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_CFG */
	u8 sub_func;
	u8 wsvd1;
	u8 sg_wist_offset;
	u32 handwe;

	union {
		u8 bytes[116];
		stwuct atto_vda_cfg_init init;
		stwuct atto_vda_sge sge;
		stwuct atto_physicaw_wegion_descwiption pwde;
	} data;
};


stwuct __packed atto_vda_mgmt_weq {
	u32 wength;
	u8 function; /* VDA_FUNC_MGT */
	u8 mgt_func;
	u8 chain_offset;
	u8 sg_wist_offset;
	u32 handwe;
	u8 scan_genewation;
	u8 paywd_sgwst_offset;
	u16 dev_index;
	u32 paywd_wength;
	u32 pad;
	union {
		stwuct atto_vda_sge sge[2];
		stwuct atto_physicaw_wegion_descwiption pwde[2];
	};
	stwuct atto_vda_sge paywd_sge[1];
};


union atto_vda_weq {
	stwuct atto_vda_scsi_weq scsi;
	stwuct atto_vda_fwash_weq fwash;
	stwuct atto_vda_diag_weq diag;
	stwuct atto_vda_ae_weq ae;
	stwuct atto_vda_cwi_weq cwi;
	stwuct atto_vda_ioctw_weq ioctw;
	stwuct atto_vda_cfg_weq cfg;
	stwuct atto_vda_mgmt_weq mgt;
	u8 bytes[1024];
};

/* Outbound wesponse stwuctuwes */

stwuct __packed atto_vda_scsi_wsp {
	u8 scsi_stat;
	u8 sense_wen;
	u8 wsvd[2];
	u32 wesiduaw_wength;
};

stwuct __packed atto_vda_fwash_wsp {
	u32 fiwe_size;
};

stwuct __packed atto_vda_ae_wsp {
	u32 wength;
};

stwuct __packed atto_vda_cwi_wsp {
	u32 cmd_wsp_wen;
};

stwuct __packed atto_vda_ioctw_wsp {
	union {
		stwuct {
			u32 csmi_status;
			u16 tawget_id;
			u8 wun;
			u8 wesewved;
		} csmi;
	};
};

stwuct __packed atto_vda_cfg_wsp {
	u16 vda_vewsion;
	u16 fw_wewease;
	u32 fw_buiwd;
};

stwuct __packed atto_vda_mgmt_wsp {
	u32 wength;
	u16 dev_index;
	u8 scan_genewation;
};

union atto_vda_func_wsp {
	stwuct atto_vda_scsi_wsp scsi_wsp;
	stwuct atto_vda_fwash_wsp fwash_wsp;
	stwuct atto_vda_ae_wsp ae_wsp;
	stwuct atto_vda_cwi_wsp cwi_wsp;
	stwuct atto_vda_ioctw_wsp ioctw_wsp;
	stwuct atto_vda_cfg_wsp cfg_wsp;
	stwuct atto_vda_mgmt_wsp mgt_wsp;
	u32 dwowds[2];
};

stwuct __packed atto_vda_ob_wsp {
	u32 handwe;
	u8 weq_stat;
	u8 wsvd[3];

	union atto_vda_func_wsp
		func_wsp;
};

stwuct __packed atto_vda_ae_data {
	u8 event_data[256];
};

stwuct __packed atto_vda_mgmt_data {
	union {
		u8 bytes[112];
		stwuct atto_vda_devinfo dev_info;
		stwuct atto_vda_gwp_info gwp_info;
		stwuct atto_vdapawt_info pawt_info;
		stwuct atto_vda_dh_info dev_heawth_info;
		stwuct atto_vda_metwics_info metwics_info;
		stwuct atto_vda_scheduwe_info sched_info;
		stwuct atto_vda_n_vcache_info nvcache_info;
		stwuct atto_vda_buzzew_info buzzew_info;
	} data;
};

union atto_vda_wsp_data {
	stwuct atto_vda_ae_data ae_data;
	stwuct atto_vda_mgmt_data mgt_data;
	u8 sense_data[252];
	#define SENSE_DATA_SZ   252;
	u8 bytes[256];
};

#endif
