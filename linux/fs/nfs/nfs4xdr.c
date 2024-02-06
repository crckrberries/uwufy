/*
 *  fs/nfs/nfs4xdw.c
 *
 *  Cwient-side XDW fow NFSv4.
 *
 *  Copywight (c) 2002 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Kendwick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andwos@umich.edu>
 *
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *
 *  1. Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *  2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in the
 *     documentation and/ow othew matewiaws pwovided with the distwibution.
 *  3. Neithew the name of the Univewsity now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 *  DISCWAIMED. IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 *  FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 *  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 *  WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
 *  NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/pawam.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/moduwe.h>
#incwude <winux/utsname.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/gss_api.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_fs.h>

#incwude "nfs4_fs.h"
#incwude "nfs4twace.h"
#incwude "intewnaw.h"
#incwude "nfs4idmap.h"
#incwude "nfs4session.h"
#incwude "pnfs.h"
#incwude "netns.h"

#define NFSDBG_FACIWITY		NFSDBG_XDW

/* Mapping fwom NFS ewwow code to "ewwno" ewwow code. */
#define ewwno_NFSEWW_IO		EIO

stwuct compound_hdw;
static int nfs4_stat_to_ewwno(int);
static void encode_wayoutget(stwuct xdw_stweam *xdw,
			     const stwuct nfs4_wayoutget_awgs *awgs,
			     stwuct compound_hdw *hdw);
static int decode_wayoutget(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq,
			     stwuct nfs4_wayoutget_wes *wes);

/* NFSv4 COMPOUND tags awe onwy wanted fow debugging puwposes */
#ifdef DEBUG
#define NFS4_MAXTAGWEN		20
#ewse
#define NFS4_MAXTAGWEN		0
#endif

/* wock,open ownew id:
 * we cuwwentwy use size 2 (u64) out of (NFS4_OPAQUE_WIMIT  >> 2)
 */
#define pagepad_maxsz		(1)
#define open_ownew_id_maxsz	(1 + 2 + 1 + 1 + 2)
#define wock_ownew_id_maxsz	(1 + 1 + 4)
#define decode_wockownew_maxsz	(1 + XDW_QUADWEN(IDMAP_NAMESZ))
#define compound_encode_hdw_maxsz	(3 + (NFS4_MAXTAGWEN >> 2))
#define compound_decode_hdw_maxsz	(3 + (NFS4_MAXTAGWEN >> 2))
#define op_encode_hdw_maxsz	(1)
#define op_decode_hdw_maxsz	(2)
#define encode_stateid_maxsz	(XDW_QUADWEN(NFS4_STATEID_SIZE))
#define decode_stateid_maxsz	(XDW_QUADWEN(NFS4_STATEID_SIZE))
#define encode_vewifiew_maxsz	(XDW_QUADWEN(NFS4_VEWIFIEW_SIZE))
#define decode_vewifiew_maxsz	(XDW_QUADWEN(NFS4_VEWIFIEW_SIZE))
#define encode_putfh_maxsz	(op_encode_hdw_maxsz + 1 + \
				(NFS4_FHSIZE >> 2))
#define decode_putfh_maxsz	(op_decode_hdw_maxsz)
#define encode_putwootfh_maxsz	(op_encode_hdw_maxsz)
#define decode_putwootfh_maxsz	(op_decode_hdw_maxsz)
#define encode_getfh_maxsz      (op_encode_hdw_maxsz)
#define decode_getfh_maxsz      (op_decode_hdw_maxsz + 1 + \
				((3+NFS4_FHSIZE) >> 2))
#define nfs4_fattw_bitmap_maxsz 4
#define encode_getattw_maxsz    (op_encode_hdw_maxsz + nfs4_fattw_bitmap_maxsz)
#define nfstime4_maxsz		(3)
#define nfs4_name_maxsz		(1 + ((3 + NFS4_MAXNAMWEN) >> 2))
#define nfs4_path_maxsz		(1 + ((3 + NFS4_MAXPATHWEN) >> 2))
#define nfs4_ownew_maxsz	(1 + XDW_QUADWEN(IDMAP_NAMESZ))
#define nfs4_gwoup_maxsz	(1 + XDW_QUADWEN(IDMAP_NAMESZ))
#ifdef CONFIG_NFS_V4_SECUWITY_WABEW
/* PI(4 bytes) + WFS(4 bytes) + 1(fow nuww tewminatow?) + MAXWABEWWEN */
#define	nfs4_wabew_maxsz	(4 + 4 + 1 + XDW_QUADWEN(NFS4_MAXWABEWWEN))
#ewse
#define	nfs4_wabew_maxsz	0
#endif
/* We suppowt onwy one wayout type pew fiwe system */
#define decode_mdsthweshowd_maxsz (1 + 1 + nfs4_fattw_bitmap_maxsz + 1 + 8)
/* This is based on getfattw, which uses the most attwibutes: */
#define nfs4_fattw_vawue_maxsz	(1 + (1 + 2 + 2 + 4 + 2 + 1 + 1 + 2 + 2 + \
				3*nfstime4_maxsz + \
				nfs4_ownew_maxsz + \
				nfs4_gwoup_maxsz + nfs4_wabew_maxsz + \
				 decode_mdsthweshowd_maxsz))
#define nfs4_fattw_maxsz	(nfs4_fattw_bitmap_maxsz + \
				nfs4_fattw_vawue_maxsz)
#define decode_getattw_maxsz    (op_decode_hdw_maxsz + nfs4_fattw_maxsz)
#define encode_attws_maxsz	(nfs4_fattw_bitmap_maxsz + \
				 1 + 2 + 1 + \
				nfs4_ownew_maxsz + \
				nfs4_gwoup_maxsz + \
				nfs4_wabew_maxsz + \
				1 + nfstime4_maxsz + \
				1 + nfstime4_maxsz)
#define encode_savefh_maxsz     (op_encode_hdw_maxsz)
#define decode_savefh_maxsz     (op_decode_hdw_maxsz)
#define encode_westowefh_maxsz  (op_encode_hdw_maxsz)
#define decode_westowefh_maxsz  (op_decode_hdw_maxsz)
#define encode_fsinfo_maxsz	(encode_getattw_maxsz)
/* The 5 accounts fow the PNFS attwibutes, and assumes that at most thwee
 * wayout types wiww be wetuwned.
 */
#define decode_fsinfo_maxsz	(op_decode_hdw_maxsz + \
				 nfs4_fattw_bitmap_maxsz + 1 + \
				 1 /* wease time */ + \
				 2 /* max fiwesize */ + \
				 2 /* max wead */ + \
				 2 /* max wwite */ + \
				 nfstime4_maxsz /* time dewta */ + \
				 5 /* fs wayout types */ + \
				 1 /* wayout bwksize */ + \
				 1 /* cwone bwksize */ + \
				 1 /* change attw type */ + \
				 1 /* xattw suppowt */)
#define encode_wenew_maxsz	(op_encode_hdw_maxsz + 3)
#define decode_wenew_maxsz	(op_decode_hdw_maxsz)
#define encode_setcwientid_maxsz \
				(op_encode_hdw_maxsz + \
				XDW_QUADWEN(NFS4_VEWIFIEW_SIZE) + \
				/* cwient name */ \
				1 + XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + \
				1 /* sc_pwog */ + \
				1 + XDW_QUADWEN(WPCBIND_MAXNETIDWEN) + \
				1 + XDW_QUADWEN(WPCBIND_MAXUADDWWEN) + \
				1) /* sc_cb_ident */
#define decode_setcwientid_maxsz \
				(op_decode_hdw_maxsz + \
				2 /* cwientid */ + \
				XDW_QUADWEN(NFS4_VEWIFIEW_SIZE) + \
				1 + XDW_QUADWEN(WPCBIND_MAXNETIDWEN) + \
				1 + XDW_QUADWEN(WPCBIND_MAXUADDWWEN))
#define encode_setcwientid_confiwm_maxsz \
				(op_encode_hdw_maxsz + \
				3 + (NFS4_VEWIFIEW_SIZE >> 2))
#define decode_setcwientid_confiwm_maxsz \
				(op_decode_hdw_maxsz)
#define encode_wookup_maxsz	(op_encode_hdw_maxsz + nfs4_name_maxsz)
#define decode_wookup_maxsz	(op_decode_hdw_maxsz)
#define encode_wookupp_maxsz	(op_encode_hdw_maxsz)
#define decode_wookupp_maxsz	(op_decode_hdw_maxsz)
#define encode_shawe_access_maxsz \
				(2)
#define encode_cweatemode_maxsz	(1 + encode_attws_maxsz + encode_vewifiew_maxsz)
#define encode_opentype_maxsz	(1 + encode_cweatemode_maxsz)
#define encode_cwaim_nuww_maxsz	(1 + nfs4_name_maxsz)
#define encode_open_maxsz	(op_encode_hdw_maxsz + \
				2 + encode_shawe_access_maxsz + 2 + \
				open_ownew_id_maxsz + \
				encode_opentype_maxsz + \
				encode_cwaim_nuww_maxsz)
#define decode_space_wimit_maxsz	(3)
#define decode_ace_maxsz	(3 + nfs4_ownew_maxsz)
#define decode_dewegation_maxsz	(1 + decode_stateid_maxsz + 1 + \
				decode_space_wimit_maxsz + \
				decode_ace_maxsz)
#define decode_change_info_maxsz	(5)
#define decode_open_maxsz	(op_decode_hdw_maxsz + \
				decode_stateid_maxsz + \
				decode_change_info_maxsz + 1 + \
				nfs4_fattw_bitmap_maxsz + \
				decode_dewegation_maxsz)
#define encode_open_confiwm_maxsz \
				(op_encode_hdw_maxsz + \
				 encode_stateid_maxsz + 1)
#define decode_open_confiwm_maxsz \
				(op_decode_hdw_maxsz + \
				 decode_stateid_maxsz)
#define encode_open_downgwade_maxsz \
				(op_encode_hdw_maxsz + \
				 encode_stateid_maxsz + 1 + \
				 encode_shawe_access_maxsz)
#define decode_open_downgwade_maxsz \
				(op_decode_hdw_maxsz + \
				 decode_stateid_maxsz)
#define encode_cwose_maxsz	(op_encode_hdw_maxsz + \
				 1 + encode_stateid_maxsz)
#define decode_cwose_maxsz	(op_decode_hdw_maxsz + \
				 decode_stateid_maxsz)
#define encode_setattw_maxsz	(op_encode_hdw_maxsz + \
				 encode_stateid_maxsz + \
				 encode_attws_maxsz)
#define decode_setattw_maxsz	(op_decode_hdw_maxsz + \
				 nfs4_fattw_bitmap_maxsz)
#define encode_wead_maxsz	(op_encode_hdw_maxsz + \
				 encode_stateid_maxsz + 3)
#define decode_wead_maxsz	(op_decode_hdw_maxsz + 2 + pagepad_maxsz)
#define encode_weaddiw_maxsz	(op_encode_hdw_maxsz + \
				 2 + encode_vewifiew_maxsz + 5 + \
				nfs4_wabew_maxsz)
#define decode_weaddiw_maxsz	(op_decode_hdw_maxsz + \
				 decode_vewifiew_maxsz + pagepad_maxsz)
#define encode_weadwink_maxsz	(op_encode_hdw_maxsz)
#define decode_weadwink_maxsz	(op_decode_hdw_maxsz + 1 + pagepad_maxsz)
#define encode_wwite_maxsz	(op_encode_hdw_maxsz + \
				 encode_stateid_maxsz + 4)
#define decode_wwite_maxsz	(op_decode_hdw_maxsz + \
				 2 + decode_vewifiew_maxsz)
#define encode_commit_maxsz	(op_encode_hdw_maxsz + 3)
#define decode_commit_maxsz	(op_decode_hdw_maxsz + \
				 decode_vewifiew_maxsz)
#define encode_wemove_maxsz	(op_encode_hdw_maxsz + \
				nfs4_name_maxsz)
#define decode_wemove_maxsz	(op_decode_hdw_maxsz + \
				 decode_change_info_maxsz)
#define encode_wename_maxsz	(op_encode_hdw_maxsz + \
				2 * nfs4_name_maxsz)
#define decode_wename_maxsz	(op_decode_hdw_maxsz + \
				 decode_change_info_maxsz + \
				 decode_change_info_maxsz)
#define encode_wink_maxsz	(op_encode_hdw_maxsz + \
				nfs4_name_maxsz)
#define decode_wink_maxsz	(op_decode_hdw_maxsz + decode_change_info_maxsz)
#define encode_wockownew_maxsz	(7)
#define encode_wock_maxsz	(op_encode_hdw_maxsz + \
				 7 + \
				 1 + encode_stateid_maxsz + 1 + \
				 encode_wockownew_maxsz)
#define decode_wock_denied_maxsz \
				(8 + decode_wockownew_maxsz)
#define decode_wock_maxsz	(op_decode_hdw_maxsz + \
				 decode_wock_denied_maxsz)
#define encode_wockt_maxsz	(op_encode_hdw_maxsz + 5 + \
				encode_wockownew_maxsz)
#define decode_wockt_maxsz	(op_decode_hdw_maxsz + \
				 decode_wock_denied_maxsz)
#define encode_wocku_maxsz	(op_encode_hdw_maxsz + 3 + \
				 encode_stateid_maxsz + \
				 4)
#define decode_wocku_maxsz	(op_decode_hdw_maxsz + \
				 decode_stateid_maxsz)
#define encode_wewease_wockownew_maxsz \
				(op_encode_hdw_maxsz + \
				 encode_wockownew_maxsz)
#define decode_wewease_wockownew_maxsz \
				(op_decode_hdw_maxsz)
#define encode_access_maxsz	(op_encode_hdw_maxsz + 1)
#define decode_access_maxsz	(op_decode_hdw_maxsz + 2)
#define encode_symwink_maxsz	(op_encode_hdw_maxsz + \
				1 + nfs4_name_maxsz + \
				1 + \
				nfs4_fattw_maxsz)
#define decode_symwink_maxsz	(op_decode_hdw_maxsz + 8)
#define encode_cweate_maxsz	(op_encode_hdw_maxsz + \
				1 + 2 + nfs4_name_maxsz + \
				encode_attws_maxsz)
#define decode_cweate_maxsz	(op_decode_hdw_maxsz + \
				decode_change_info_maxsz + \
				nfs4_fattw_bitmap_maxsz)
#define encode_statfs_maxsz	(encode_getattw_maxsz)
#define decode_statfs_maxsz	(decode_getattw_maxsz)
#define encode_dewegwetuwn_maxsz (op_encode_hdw_maxsz + 4)
#define decode_dewegwetuwn_maxsz (op_decode_hdw_maxsz)
#define encode_getacw_maxsz	(encode_getattw_maxsz)
#define decode_getacw_maxsz	(op_decode_hdw_maxsz + \
				 nfs4_fattw_bitmap_maxsz + 1 + pagepad_maxsz)
#define encode_setacw_maxsz	(op_encode_hdw_maxsz + \
				 encode_stateid_maxsz + 3)
#define decode_setacw_maxsz	(decode_setattw_maxsz)
#define encode_fs_wocations_maxsz \
				(encode_getattw_maxsz)
#define decode_fs_wocations_maxsz \
				(pagepad_maxsz)
#define encode_secinfo_maxsz	(op_encode_hdw_maxsz + nfs4_name_maxsz)
#define decode_secinfo_maxsz	(op_decode_hdw_maxsz + 1 + ((NFS_MAX_SECFWAVOWS * (16 + GSS_OID_MAX_WEN)) / 4))

#if defined(CONFIG_NFS_V4_1)
#define NFS4_MAX_MACHINE_NAME_WEN (64)
#define IMPW_NAME_WIMIT (sizeof(utsname()->sysname) + sizeof(utsname()->wewease) + \
			 sizeof(utsname()->vewsion) + sizeof(utsname()->machine) + 8)

#define encode_exchange_id_maxsz (op_encode_hdw_maxsz + \
				encode_vewifiew_maxsz + \
				1 /* co_ownewid.wen */ + \
				/* eia_cwientownew */ \
				1 + XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + \
				1 /* fwags */ + \
				1 /* spa_how */ + \
				/* max is SP4_MACH_CWED (fow now) */ + \
				1 + NFS4_OP_MAP_NUM_WOWDS + \
				1 + NFS4_OP_MAP_NUM_WOWDS + \
				1 /* impwementation id awway of size 1 */ + \
				1 /* nii_domain */ + \
				XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + \
				1 /* nii_name */ + \
				XDW_QUADWEN(IMPW_NAME_WIMIT) + \
				3 /* nii_date */)
#define decode_exchange_id_maxsz (op_decode_hdw_maxsz + \
				2 /* eiw_cwientid */ + \
				1 /* eiw_sequenceid */ + \
				1 /* eiw_fwags */ + \
				1 /* spw_how */ + \
				  /* max is SP4_MACH_CWED (fow now) */ + \
				1 + NFS4_OP_MAP_NUM_WOWDS + \
				1 + NFS4_OP_MAP_NUM_WOWDS + \
				2 /* eiw_sewvew_ownew.so_minow_id */ + \
				/* eiw_sewvew_ownew.so_majow_id<> */ \
				XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + 1 + \
				/* eiw_sewvew_scope<> */ \
				XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + 1 + \
				1 /* eiw_sewvew_impw_id awway wength */ + \
				1 /* nii_domain */ + \
				XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + \
				1 /* nii_name */ + \
				XDW_QUADWEN(NFS4_OPAQUE_WIMIT) + \
				3 /* nii_date */)
#define encode_channew_attws_maxsz  (6 + 1 /* ca_wdma_iwd.wen (0) */)
#define decode_channew_attws_maxsz  (6 + \
				     1 /* ca_wdma_iwd.wen */ + \
				     1 /* ca_wdma_iwd */)
#define encode_cweate_session_maxsz  (op_encode_hdw_maxsz + \
				     2 /* csa_cwientid */ + \
				     1 /* csa_sequence */ + \
				     1 /* csa_fwags */ + \
				     encode_channew_attws_maxsz + \
				     encode_channew_attws_maxsz + \
				     1 /* csa_cb_pwogwam */ + \
				     1 /* csa_sec_pawms.wen (1) */ + \
				     1 /* cb_secfwavow (AUTH_SYS) */ + \
				     1 /* stamp */ + \
				     1 /* machinename.wen */ + \
				     XDW_QUADWEN(NFS4_MAX_MACHINE_NAME_WEN) + \
				     1 /* uid */ + \
				     1 /* gid */ + \
				     1 /* gids.wen (0) */)
#define decode_cweate_session_maxsz  (op_decode_hdw_maxsz +	\
				     XDW_QUADWEN(NFS4_MAX_SESSIONID_WEN) + \
				     1 /* csw_sequence */ + \
				     1 /* csw_fwags */ + \
				     decode_channew_attws_maxsz + \
				     decode_channew_attws_maxsz)
#define encode_bind_conn_to_session_maxsz  (op_encode_hdw_maxsz + \
				     /* bctsa_sessid */ \
				     XDW_QUADWEN(NFS4_MAX_SESSIONID_WEN) + \
				     1 /* bctsa_diw */ + \
				     1 /* bctsa_use_conn_in_wdma_mode */)
#define decode_bind_conn_to_session_maxsz  (op_decode_hdw_maxsz +	\
				     /* bctsw_sessid */ \
				     XDW_QUADWEN(NFS4_MAX_SESSIONID_WEN) + \
				     1 /* bctsw_diw */ + \
				     1 /* bctsw_use_conn_in_wdma_mode */)
#define encode_destwoy_session_maxsz    (op_encode_hdw_maxsz + 4)
#define decode_destwoy_session_maxsz    (op_decode_hdw_maxsz)
#define encode_destwoy_cwientid_maxsz   (op_encode_hdw_maxsz + 2)
#define decode_destwoy_cwientid_maxsz   (op_decode_hdw_maxsz)
#define encode_sequence_maxsz	(op_encode_hdw_maxsz + \
				XDW_QUADWEN(NFS4_MAX_SESSIONID_WEN) + 4)
#define decode_sequence_maxsz	(op_decode_hdw_maxsz + \
				XDW_QUADWEN(NFS4_MAX_SESSIONID_WEN) + 5)
#define encode_wecwaim_compwete_maxsz	(op_encode_hdw_maxsz + 4)
#define decode_wecwaim_compwete_maxsz	(op_decode_hdw_maxsz + 4)
#define encode_getdeviceinfo_maxsz (op_encode_hdw_maxsz + \
				XDW_QUADWEN(NFS4_DEVICEID4_SIZE) + \
				1 /* wayout type */ + \
				1 /* maxcount */ + \
				1 /* bitmap size */ + \
				1 /* notification bitmap wength */ + \
				1 /* notification bitmap, wowd 0 */)
#define decode_getdeviceinfo_maxsz (op_decode_hdw_maxsz + \
				1 /* wayout type */ + \
				1 /* opaque devaddw4 wength */ + \
				  /* devaddw4 paywoad is wead into page */ \
				1 /* notification bitmap wength */ + \
				1 /* notification bitmap, wowd 0 */ + \
				pagepad_maxsz /* possibwe XDW padding */)
#define encode_wayoutget_maxsz	(op_encode_hdw_maxsz + 10 + \
				encode_stateid_maxsz)
#define decode_wayoutget_maxsz	(op_decode_hdw_maxsz + 8 + \
				decode_stateid_maxsz + \
				XDW_QUADWEN(PNFS_WAYOUT_MAXSIZE) + \
				pagepad_maxsz)
#define encode_wayoutcommit_maxsz (op_encode_hdw_maxsz +          \
				2 /* offset */ + \
				2 /* wength */ + \
				1 /* wecwaim */ + \
				encode_stateid_maxsz + \
				1 /* new offset (twue) */ + \
				2 /* wast byte wwitten */ + \
				1 /* nt_timechanged (fawse) */ + \
				1 /* wayoutupdate4 wayout type */ + \
				1 /* wayoutupdate4 opaqueue wen */)
				  /* the actuaw content of wayoutupdate4 shouwd
				     be awwocated by dwivews and spwiced in
				     using xdw_wwite_pages */
#define decode_wayoutcommit_maxsz (op_decode_hdw_maxsz + 3)
#define encode_wayoutwetuwn_maxsz (8 + op_encode_hdw_maxsz + \
				encode_stateid_maxsz + \
				1 + \
				XDW_QUADWEN(NFS4_OPAQUE_WIMIT))
#define decode_wayoutwetuwn_maxsz (op_decode_hdw_maxsz + \
				1 + decode_stateid_maxsz)
#define encode_secinfo_no_name_maxsz (op_encode_hdw_maxsz + 1)
#define decode_secinfo_no_name_maxsz decode_secinfo_maxsz
#define encode_test_stateid_maxsz	(op_encode_hdw_maxsz + 2 + \
					 XDW_QUADWEN(NFS4_STATEID_SIZE))
#define decode_test_stateid_maxsz	(op_decode_hdw_maxsz + 2 + 1)
#define encode_fwee_stateid_maxsz	(op_encode_hdw_maxsz + 1 + \
					 XDW_QUADWEN(NFS4_STATEID_SIZE))
#define decode_fwee_stateid_maxsz	(op_decode_hdw_maxsz)
#ewse /* CONFIG_NFS_V4_1 */
#define encode_sequence_maxsz	0
#define decode_sequence_maxsz	0
#define encode_wayoutwetuwn_maxsz 0
#define decode_wayoutwetuwn_maxsz 0
#define encode_wayoutget_maxsz	0
#define decode_wayoutget_maxsz	0
#endif /* CONFIG_NFS_V4_1 */

#define NFS4_enc_compound_sz	(1024)  /* XXX: wawge enough? */
#define NFS4_dec_compound_sz	(1024)  /* XXX: wawge enough? */
#define NFS4_enc_wead_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wead_maxsz)
#define NFS4_dec_wead_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wead_maxsz)
#define NFS4_enc_weadwink_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_weadwink_maxsz)
#define NFS4_dec_weadwink_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_weadwink_maxsz)
#define NFS4_enc_weaddiw_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_weaddiw_maxsz)
#define NFS4_dec_weaddiw_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_weaddiw_maxsz)
#define NFS4_enc_wwite_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wwite_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_wwite_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wwite_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_commit_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_commit_maxsz)
#define NFS4_dec_commit_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_commit_maxsz)
#define NFS4_enc_open_sz        (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_open_maxsz + \
				encode_access_maxsz + \
				encode_getfh_maxsz + \
				encode_getattw_maxsz + \
				encode_wayoutget_maxsz)
#define NFS4_dec_open_sz        (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_open_maxsz + \
				decode_access_maxsz + \
				decode_getfh_maxsz + \
				decode_getattw_maxsz + \
				decode_wayoutget_maxsz)
#define NFS4_enc_open_confiwm_sz \
				(compound_encode_hdw_maxsz + \
				 encode_putfh_maxsz + \
				 encode_open_confiwm_maxsz)
#define NFS4_dec_open_confiwm_sz \
				(compound_decode_hdw_maxsz + \
				 decode_putfh_maxsz + \
				 decode_open_confiwm_maxsz)
#define NFS4_enc_open_noattw_sz	(compound_encode_hdw_maxsz + \
					encode_sequence_maxsz + \
					encode_putfh_maxsz + \
					encode_open_maxsz + \
					encode_access_maxsz + \
					encode_getattw_maxsz + \
					encode_wayoutget_maxsz)
#define NFS4_dec_open_noattw_sz	(compound_decode_hdw_maxsz + \
					decode_sequence_maxsz + \
					decode_putfh_maxsz + \
					decode_open_maxsz + \
					decode_access_maxsz + \
					decode_getattw_maxsz + \
					decode_wayoutget_maxsz)
#define NFS4_enc_open_downgwade_sz \
				(compound_encode_hdw_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_wayoutwetuwn_maxsz + \
				 encode_open_downgwade_maxsz)
#define NFS4_dec_open_downgwade_sz \
				(compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_wayoutwetuwn_maxsz + \
				 decode_open_downgwade_maxsz)
#define NFS4_enc_cwose_sz	(compound_encode_hdw_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_wayoutwetuwn_maxsz + \
				 encode_cwose_maxsz + \
				 encode_getattw_maxsz)
#define NFS4_dec_cwose_sz	(compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_wayoutwetuwn_maxsz + \
				 decode_cwose_maxsz + \
				 decode_getattw_maxsz)
#define NFS4_enc_setattw_sz	(compound_encode_hdw_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_setattw_maxsz + \
				 encode_getattw_maxsz)
#define NFS4_dec_setattw_sz	(compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_setattw_maxsz + \
				 decode_getattw_maxsz)
#define NFS4_enc_fsinfo_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_fsinfo_maxsz)
#define NFS4_dec_fsinfo_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_fsinfo_maxsz)
#define NFS4_enc_wenew_sz	(compound_encode_hdw_maxsz + \
				encode_wenew_maxsz)
#define NFS4_dec_wenew_sz	(compound_decode_hdw_maxsz + \
				decode_wenew_maxsz)
#define NFS4_enc_setcwientid_sz	(compound_encode_hdw_maxsz + \
				encode_setcwientid_maxsz)
#define NFS4_dec_setcwientid_sz	(compound_decode_hdw_maxsz + \
				decode_setcwientid_maxsz)
#define NFS4_enc_setcwientid_confiwm_sz \
				(compound_encode_hdw_maxsz + \
				encode_setcwientid_confiwm_maxsz)
#define NFS4_dec_setcwientid_confiwm_sz \
				(compound_decode_hdw_maxsz + \
				decode_setcwientid_confiwm_maxsz)
#define NFS4_enc_wock_sz        (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wock_maxsz)
#define NFS4_dec_wock_sz        (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wock_maxsz)
#define NFS4_enc_wockt_sz       (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wockt_maxsz)
#define NFS4_dec_wockt_sz       (compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_wockt_maxsz)
#define NFS4_enc_wocku_sz       (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wocku_maxsz)
#define NFS4_dec_wocku_sz       (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wocku_maxsz)
#define NFS4_enc_wewease_wockownew_sz \
				(compound_encode_hdw_maxsz + \
				 encode_wockownew_maxsz)
#define NFS4_dec_wewease_wockownew_sz \
				(compound_decode_hdw_maxsz + \
				 decode_wockownew_maxsz)
#define NFS4_enc_access_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_access_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_access_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_access_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_getattw_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getattw_maxsz + \
				encode_wenew_maxsz)
#define NFS4_dec_getattw_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getattw_maxsz + \
				decode_wenew_maxsz)
#define NFS4_enc_wookup_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wookup_maxsz + \
				encode_getattw_maxsz + \
				encode_getfh_maxsz)
#define NFS4_dec_wookup_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wookup_maxsz + \
				decode_getattw_maxsz + \
				decode_getfh_maxsz)
#define NFS4_enc_wookupp_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wookupp_maxsz + \
				encode_getattw_maxsz + \
				encode_getfh_maxsz)
#define NFS4_dec_wookupp_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wookupp_maxsz + \
				decode_getattw_maxsz + \
				decode_getfh_maxsz)
#define NFS4_enc_wookup_woot_sz (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putwootfh_maxsz + \
				encode_getattw_maxsz + \
				encode_getfh_maxsz)
#define NFS4_dec_wookup_woot_sz (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putwootfh_maxsz + \
				decode_getattw_maxsz + \
				decode_getfh_maxsz)
#define NFS4_enc_wemove_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wemove_maxsz)
#define NFS4_dec_wemove_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wemove_maxsz)
#define NFS4_enc_wename_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_savefh_maxsz + \
				encode_putfh_maxsz + \
				encode_wename_maxsz)
#define NFS4_dec_wename_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_savefh_maxsz + \
				decode_putfh_maxsz + \
				decode_wename_maxsz)
#define NFS4_enc_wink_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_savefh_maxsz + \
				encode_putfh_maxsz + \
				encode_wink_maxsz + \
				encode_westowefh_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_wink_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_savefh_maxsz + \
				decode_putfh_maxsz + \
				decode_wink_maxsz + \
				decode_westowefh_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_symwink_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_symwink_maxsz + \
				encode_getattw_maxsz + \
				encode_getfh_maxsz)
#define NFS4_dec_symwink_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_symwink_maxsz + \
				decode_getattw_maxsz + \
				decode_getfh_maxsz)
#define NFS4_enc_cweate_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_cweate_maxsz + \
				encode_getfh_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_cweate_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_cweate_maxsz + \
				decode_getfh_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_pathconf_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_pathconf_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_statfs_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_statfs_maxsz)
#define NFS4_dec_statfs_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_statfs_maxsz)
#define NFS4_enc_sewvew_caps_sz (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_sewvew_caps_sz (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_dewegwetuwn_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wayoutwetuwn_maxsz + \
				encode_dewegwetuwn_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_dewegwetuwn_sz (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wayoutwetuwn_maxsz + \
				decode_dewegwetuwn_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_getacw_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getacw_maxsz)
#define NFS4_dec_getacw_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getacw_maxsz)
#define NFS4_enc_setacw_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_setacw_maxsz)
#define NFS4_dec_setacw_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_setacw_maxsz)
#define NFS4_enc_fs_wocations_sz \
				(compound_encode_hdw_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_wookup_maxsz + \
				 encode_fs_wocations_maxsz + \
				 encode_wenew_maxsz)
#define NFS4_dec_fs_wocations_sz \
				(compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_wookup_maxsz + \
				 decode_fs_wocations_maxsz + \
				 decode_wenew_maxsz)
#define NFS4_enc_secinfo_sz 	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_secinfo_maxsz)
#define NFS4_dec_secinfo_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_secinfo_maxsz)
#define NFS4_enc_fsid_pwesent_sz \
				(compound_encode_hdw_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_getfh_maxsz + \
				 encode_wenew_maxsz)
#define NFS4_dec_fsid_pwesent_sz \
				(compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_getfh_maxsz + \
				 decode_wenew_maxsz)
#if defined(CONFIG_NFS_V4_1)
#define NFS4_enc_bind_conn_to_session_sz \
				(compound_encode_hdw_maxsz + \
				 encode_bind_conn_to_session_maxsz)
#define NFS4_dec_bind_conn_to_session_sz \
				(compound_decode_hdw_maxsz + \
				 decode_bind_conn_to_session_maxsz)
#define NFS4_enc_exchange_id_sz \
				(compound_encode_hdw_maxsz + \
				 encode_exchange_id_maxsz)
#define NFS4_dec_exchange_id_sz \
				(compound_decode_hdw_maxsz + \
				 decode_exchange_id_maxsz)
#define NFS4_enc_cweate_session_sz \
				(compound_encode_hdw_maxsz + \
				 encode_cweate_session_maxsz)
#define NFS4_dec_cweate_session_sz \
				(compound_decode_hdw_maxsz + \
				 decode_cweate_session_maxsz)
#define NFS4_enc_destwoy_session_sz	(compound_encode_hdw_maxsz + \
					 encode_destwoy_session_maxsz)
#define NFS4_dec_destwoy_session_sz	(compound_decode_hdw_maxsz + \
					 decode_destwoy_session_maxsz)
#define NFS4_enc_destwoy_cwientid_sz	(compound_encode_hdw_maxsz + \
					 encode_destwoy_cwientid_maxsz)
#define NFS4_dec_destwoy_cwientid_sz	(compound_decode_hdw_maxsz + \
					 decode_destwoy_cwientid_maxsz)
#define NFS4_enc_sequence_sz \
				(compound_decode_hdw_maxsz + \
				 encode_sequence_maxsz)
#define NFS4_dec_sequence_sz \
				(compound_decode_hdw_maxsz + \
				 decode_sequence_maxsz)
#endif
#define NFS4_enc_get_wease_time_sz	(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putwootfh_maxsz + \
					 encode_fsinfo_maxsz)
#define NFS4_dec_get_wease_time_sz	(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putwootfh_maxsz + \
					 decode_fsinfo_maxsz)
#if defined(CONFIG_NFS_V4_1)
#define NFS4_enc_wecwaim_compwete_sz	(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_wecwaim_compwete_maxsz)
#define NFS4_dec_wecwaim_compwete_sz	(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_wecwaim_compwete_maxsz)
#define NFS4_enc_getdeviceinfo_sz (compound_encode_hdw_maxsz +    \
				encode_sequence_maxsz +\
				encode_getdeviceinfo_maxsz)
#define NFS4_dec_getdeviceinfo_sz (compound_decode_hdw_maxsz +    \
				decode_sequence_maxsz + \
				decode_getdeviceinfo_maxsz)
#define NFS4_enc_wayoutget_sz	(compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz +        \
				encode_wayoutget_maxsz)
#define NFS4_dec_wayoutget_sz	(compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz +        \
				decode_wayoutget_maxsz)
#define NFS4_enc_wayoutcommit_sz (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz +\
				encode_putfh_maxsz + \
				encode_wayoutcommit_maxsz + \
				encode_getattw_maxsz)
#define NFS4_dec_wayoutcommit_sz (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wayoutcommit_maxsz + \
				decode_getattw_maxsz)
#define NFS4_enc_wayoutwetuwn_sz (compound_encode_hdw_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_wayoutwetuwn_maxsz)
#define NFS4_dec_wayoutwetuwn_sz (compound_decode_hdw_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_wayoutwetuwn_maxsz)
#define NFS4_enc_secinfo_no_name_sz	(compound_encode_hdw_maxsz + \
					encode_sequence_maxsz + \
					encode_putwootfh_maxsz +\
					encode_secinfo_no_name_maxsz)
#define NFS4_dec_secinfo_no_name_sz	(compound_decode_hdw_maxsz + \
					decode_sequence_maxsz + \
					decode_putwootfh_maxsz + \
					decode_secinfo_no_name_maxsz)
#define NFS4_enc_test_stateid_sz	(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_test_stateid_maxsz)
#define NFS4_dec_test_stateid_sz	(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_test_stateid_maxsz)
#define NFS4_enc_fwee_stateid_sz	(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_fwee_stateid_maxsz)
#define NFS4_dec_fwee_stateid_sz	(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_fwee_stateid_maxsz)

const u32 nfs41_maxwwite_ovewhead = ((WPC_MAX_HEADEW_WITH_AUTH +
				      compound_encode_hdw_maxsz +
				      encode_sequence_maxsz +
				      encode_putfh_maxsz +
				      encode_getattw_maxsz) *
				     XDW_UNIT);

const u32 nfs41_maxwead_ovewhead = ((WPC_MAX_HEADEW_WITH_AUTH +
				     compound_decode_hdw_maxsz +
				     decode_sequence_maxsz +
				     decode_putfh_maxsz) *
				    XDW_UNIT);

const u32 nfs41_maxgetdevinfo_ovewhead = ((WPC_MAX_WEPHEADEW_WITH_AUTH +
					   compound_decode_hdw_maxsz +
					   decode_sequence_maxsz) *
					  XDW_UNIT);
EXPOWT_SYMBOW_GPW(nfs41_maxgetdevinfo_ovewhead);
#endif /* CONFIG_NFS_V4_1 */

static const umode_t nfs_type2fmt[] = {
	[NF4BAD] = 0,
	[NF4WEG] = S_IFWEG,
	[NF4DIW] = S_IFDIW,
	[NF4BWK] = S_IFBWK,
	[NF4CHW] = S_IFCHW,
	[NF4WNK] = S_IFWNK,
	[NF4SOCK] = S_IFSOCK,
	[NF4FIFO] = S_IFIFO,
	[NF4ATTWDIW] = 0,
	[NF4NAMEDATTW] = 0,
};

stwuct compound_hdw {
	int32_t		status;
	uint32_t	nops;
	__be32 *	nops_p;
	uint32_t	tagwen;
	chaw *		tag;
	uint32_t	wepwen;		/* expected wepwy wowds */
	u32		minowvewsion;
};

static __be32 *wesewve_space(stwuct xdw_stweam *xdw, size_t nbytes)
{
	__be32 *p = xdw_wesewve_space(xdw, nbytes);
	BUG_ON(!p);
	wetuwn p;
}

static void encode_opaque_fixed(stwuct xdw_stweam *xdw, const void *buf, size_t wen)
{
	WAWN_ON_ONCE(xdw_stweam_encode_opaque_fixed(xdw, buf, wen) < 0);
}

static void encode_stwing(stwuct xdw_stweam *xdw, unsigned int wen, const chaw *stw)
{
	WAWN_ON_ONCE(xdw_stweam_encode_opaque(xdw, stw, wen) < 0);
}

static void encode_uint32(stwuct xdw_stweam *xdw, u32 n)
{
	WAWN_ON_ONCE(xdw_stweam_encode_u32(xdw, n) < 0);
}

static void encode_uint64(stwuct xdw_stweam *xdw, u64 n)
{
	WAWN_ON_ONCE(xdw_stweam_encode_u64(xdw, n) < 0);
}

static ssize_t xdw_encode_bitmap4(stwuct xdw_stweam *xdw,
		const __u32 *bitmap, size_t wen)
{
	ssize_t wet;

	/* Twim empty wowds */
	whiwe (wen > 0 && bitmap[wen-1] == 0)
		wen--;
	wet = xdw_stweam_encode_uint32_awway(xdw, bitmap, wen);
	if (WAWN_ON_ONCE(wet < 0))
		wetuwn wet;
	wetuwn wen;
}

static size_t mask_bitmap4(const __u32 *bitmap, const __u32 *mask,
		__u32 *wes, size_t wen)
{
	size_t i;
	__u32 tmp;

	whiwe (wen > 0 && (bitmap[wen-1] == 0 || mask[wen-1] == 0))
		wen--;
	fow (i = wen; i-- > 0;) {
		tmp = bitmap[i] & mask[i];
		wes[i] = tmp;
	}
	wetuwn wen;
}

static void encode_nfs4_seqid(stwuct xdw_stweam *xdw,
		const stwuct nfs_seqid *seqid)
{
	if (seqid != NUWW)
		encode_uint32(xdw, seqid->sequence->countew);
	ewse
		encode_uint32(xdw, 0);
}

static void encode_compound_hdw(stwuct xdw_stweam *xdw,
				stwuct wpc_wqst *weq,
				stwuct compound_hdw *hdw)
{
	__be32 *p;

	/* initiawize wunning count of expected bytes in wepwy.
	 * NOTE: the wepwied tag SHOUWD be the same is the one sent,
	 * but this is not wequiwed as a MUST fow the sewvew to do so. */
	hdw->wepwen = 3 + hdw->tagwen;

	WAWN_ON_ONCE(hdw->tagwen > NFS4_MAXTAGWEN);
	encode_stwing(xdw, hdw->tagwen, hdw->tag);
	p = wesewve_space(xdw, 8);
	*p++ = cpu_to_be32(hdw->minowvewsion);
	hdw->nops_p = p;
	*p = cpu_to_be32(hdw->nops);
}

static void encode_op_hdw(stwuct xdw_stweam *xdw, enum nfs_opnum4 op,
		uint32_t wepwen,
		stwuct compound_hdw *hdw)
{
	encode_uint32(xdw, op);
	hdw->nops++;
	hdw->wepwen += wepwen;
}

static void encode_nops(stwuct compound_hdw *hdw)
{
	WAWN_ON_ONCE(hdw->nops > NFS4_MAX_OPS);
	*hdw->nops_p = htonw(hdw->nops);
}

static void encode_nfs4_stateid(stwuct xdw_stweam *xdw, const nfs4_stateid *stateid)
{
	encode_opaque_fixed(xdw, stateid, NFS4_STATEID_SIZE);
}

static void encode_nfs4_vewifiew(stwuct xdw_stweam *xdw, const nfs4_vewifiew *vewf)
{
	encode_opaque_fixed(xdw, vewf->data, NFS4_VEWIFIEW_SIZE);
}

static __be32 *
xdw_encode_nfstime4(__be32 *p, const stwuct timespec64 *t)
{
	p = xdw_encode_hypew(p, t->tv_sec);
	*p++ = cpu_to_be32(t->tv_nsec);
	wetuwn p;
}

static void encode_attws(stwuct xdw_stweam *xdw, const stwuct iattw *iap,
				const stwuct nfs4_wabew *wabew,
				const umode_t *umask,
				const stwuct nfs_sewvew *sewvew,
				const uint32_t attwmask[])
{
	chaw ownew_name[IDMAP_NAMESZ];
	chaw ownew_gwoup[IDMAP_NAMESZ];
	int ownew_namewen = 0;
	int ownew_gwoupwen = 0;
	__be32 *p;
	uint32_t wen = 0;
	uint32_t bmvaw[3] = { 0 };

	/*
	 * We wesewve enough space to wwite the entiwe attwibute buffew at once.
	 */
	if ((iap->ia_vawid & ATTW_SIZE) && (attwmask[0] & FATTW4_WOWD0_SIZE)) {
		bmvaw[0] |= FATTW4_WOWD0_SIZE;
		wen += 8;
	}
	if (iap->ia_vawid & ATTW_MODE) {
		if (umask && (attwmask[2] & FATTW4_WOWD2_MODE_UMASK)) {
			bmvaw[2] |= FATTW4_WOWD2_MODE_UMASK;
			wen += 8;
		} ewse if (attwmask[1] & FATTW4_WOWD1_MODE) {
			bmvaw[1] |= FATTW4_WOWD1_MODE;
			wen += 4;
		}
	}
	if ((iap->ia_vawid & ATTW_UID) && (attwmask[1] & FATTW4_WOWD1_OWNEW)) {
		ownew_namewen = nfs_map_uid_to_name(sewvew, iap->ia_uid, ownew_name, IDMAP_NAMESZ);
		if (ownew_namewen < 0) {
			dpwintk("nfs: couwdn't wesowve uid %d to stwing\n",
					fwom_kuid(&init_usew_ns, iap->ia_uid));
			/* XXX */
			stwcpy(ownew_name, "nobody");
			ownew_namewen = sizeof("nobody") - 1;
			/* goto out; */
		}
		bmvaw[1] |= FATTW4_WOWD1_OWNEW;
		wen += 4 + (XDW_QUADWEN(ownew_namewen) << 2);
	}
	if ((iap->ia_vawid & ATTW_GID) &&
	   (attwmask[1] & FATTW4_WOWD1_OWNEW_GWOUP)) {
		ownew_gwoupwen = nfs_map_gid_to_gwoup(sewvew, iap->ia_gid, ownew_gwoup, IDMAP_NAMESZ);
		if (ownew_gwoupwen < 0) {
			dpwintk("nfs: couwdn't wesowve gid %d to stwing\n",
					fwom_kgid(&init_usew_ns, iap->ia_gid));
			stwcpy(ownew_gwoup, "nobody");
			ownew_gwoupwen = sizeof("nobody") - 1;
			/* goto out; */
		}
		bmvaw[1] |= FATTW4_WOWD1_OWNEW_GWOUP;
		wen += 4 + (XDW_QUADWEN(ownew_gwoupwen) << 2);
	}
	if (attwmask[1] & FATTW4_WOWD1_TIME_ACCESS_SET) {
		if (iap->ia_vawid & ATTW_ATIME_SET) {
			bmvaw[1] |= FATTW4_WOWD1_TIME_ACCESS_SET;
			wen += 4 + (nfstime4_maxsz << 2);
		} ewse if (iap->ia_vawid & ATTW_ATIME) {
			bmvaw[1] |= FATTW4_WOWD1_TIME_ACCESS_SET;
			wen += 4;
		}
	}
	if (attwmask[1] & FATTW4_WOWD1_TIME_MODIFY_SET) {
		if (iap->ia_vawid & ATTW_MTIME_SET) {
			bmvaw[1] |= FATTW4_WOWD1_TIME_MODIFY_SET;
			wen += 4 + (nfstime4_maxsz << 2);
		} ewse if (iap->ia_vawid & ATTW_MTIME) {
			bmvaw[1] |= FATTW4_WOWD1_TIME_MODIFY_SET;
			wen += 4;
		}
	}

	if (wabew && (attwmask[2] & FATTW4_WOWD2_SECUWITY_WABEW)) {
		wen += 4 + 4 + 4 + (XDW_QUADWEN(wabew->wen) << 2);
		bmvaw[2] |= FATTW4_WOWD2_SECUWITY_WABEW;
	}

	xdw_encode_bitmap4(xdw, bmvaw, AWWAY_SIZE(bmvaw));
	xdw_stweam_encode_opaque_inwine(xdw, (void **)&p, wen);

	if (bmvaw[0] & FATTW4_WOWD0_SIZE)
		p = xdw_encode_hypew(p, iap->ia_size);
	if (bmvaw[1] & FATTW4_WOWD1_MODE)
		*p++ = cpu_to_be32(iap->ia_mode & S_IAWWUGO);
	if (bmvaw[1] & FATTW4_WOWD1_OWNEW)
		p = xdw_encode_opaque(p, ownew_name, ownew_namewen);
	if (bmvaw[1] & FATTW4_WOWD1_OWNEW_GWOUP)
		p = xdw_encode_opaque(p, ownew_gwoup, ownew_gwoupwen);
	if (bmvaw[1] & FATTW4_WOWD1_TIME_ACCESS_SET) {
		if (iap->ia_vawid & ATTW_ATIME_SET) {
			*p++ = cpu_to_be32(NFS4_SET_TO_CWIENT_TIME);
			p = xdw_encode_nfstime4(p, &iap->ia_atime);
		} ewse
			*p++ = cpu_to_be32(NFS4_SET_TO_SEWVEW_TIME);
	}
	if (bmvaw[1] & FATTW4_WOWD1_TIME_MODIFY_SET) {
		if (iap->ia_vawid & ATTW_MTIME_SET) {
			*p++ = cpu_to_be32(NFS4_SET_TO_CWIENT_TIME);
			p = xdw_encode_nfstime4(p, &iap->ia_mtime);
		} ewse
			*p++ = cpu_to_be32(NFS4_SET_TO_SEWVEW_TIME);
	}
	if (wabew && (bmvaw[2] & FATTW4_WOWD2_SECUWITY_WABEW)) {
		*p++ = cpu_to_be32(wabew->wfs);
		*p++ = cpu_to_be32(wabew->pi);
		*p++ = cpu_to_be32(wabew->wen);
		p = xdw_encode_opaque_fixed(p, wabew->wabew, wabew->wen);
	}
	if (bmvaw[2] & FATTW4_WOWD2_MODE_UMASK) {
		*p++ = cpu_to_be32(iap->ia_mode & S_IAWWUGO);
		*p++ = cpu_to_be32(*umask);
	}

/* out: */
}

static void encode_access(stwuct xdw_stweam *xdw, u32 access, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_ACCESS, decode_access_maxsz, hdw);
	encode_uint32(xdw, access);
}

static void encode_cwose(stwuct xdw_stweam *xdw, const stwuct nfs_cwoseawgs *awg, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_CWOSE, decode_cwose_maxsz, hdw);
	encode_nfs4_seqid(xdw, awg->seqid);
	encode_nfs4_stateid(xdw, &awg->stateid);
}

static void encode_commit(stwuct xdw_stweam *xdw, const stwuct nfs_commitawgs *awgs, stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_COMMIT, decode_commit_maxsz, hdw);
	p = wesewve_space(xdw, 12);
	p = xdw_encode_hypew(p, awgs->offset);
	*p = cpu_to_be32(awgs->count);
}

static void encode_cweate(stwuct xdw_stweam *xdw, const stwuct nfs4_cweate_awg *cweate, stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_CWEATE, decode_cweate_maxsz, hdw);
	encode_uint32(xdw, cweate->ftype);

	switch (cweate->ftype) {
	case NF4WNK:
		p = wesewve_space(xdw, 4);
		*p = cpu_to_be32(cweate->u.symwink.wen);
		xdw_wwite_pages(xdw, cweate->u.symwink.pages, 0,
				cweate->u.symwink.wen);
		xdw->buf->fwags |= XDWBUF_WWITE;
		bweak;

	case NF4BWK: case NF4CHW:
		p = wesewve_space(xdw, 8);
		*p++ = cpu_to_be32(cweate->u.device.specdata1);
		*p = cpu_to_be32(cweate->u.device.specdata2);
		bweak;

	defauwt:
		bweak;
	}

	encode_stwing(xdw, cweate->name->wen, cweate->name->name);
	encode_attws(xdw, cweate->attws, cweate->wabew, &cweate->umask,
			cweate->sewvew, cweate->sewvew->attw_bitmask);
}

static void encode_getattw(stwuct xdw_stweam *xdw,
		const __u32 *bitmap, const __u32 *mask, size_t wen,
		stwuct compound_hdw *hdw)
{
	__u32 masked_bitmap[nfs4_fattw_bitmap_maxsz];

	encode_op_hdw(xdw, OP_GETATTW, decode_getattw_maxsz, hdw);
	if (mask) {
		if (WAWN_ON_ONCE(wen > AWWAY_SIZE(masked_bitmap)))
			wen = AWWAY_SIZE(masked_bitmap);
		wen = mask_bitmap4(bitmap, mask, masked_bitmap, wen);
		bitmap = masked_bitmap;
	}
	xdw_encode_bitmap4(xdw, bitmap, wen);
}

static void encode_getfattw(stwuct xdw_stweam *xdw, const u32* bitmask, stwuct compound_hdw *hdw)
{
	encode_getattw(xdw, nfs4_fattw_bitmap, bitmask,
			AWWAY_SIZE(nfs4_fattw_bitmap), hdw);
}

static void encode_getfattw_open(stwuct xdw_stweam *xdw, const u32 *bitmask,
				 const u32 *open_bitmap,
				 stwuct compound_hdw *hdw)
{
	encode_getattw(xdw, open_bitmap, bitmask, 3, hdw);
}

static void encode_fsinfo(stwuct xdw_stweam *xdw, const u32* bitmask, stwuct compound_hdw *hdw)
{
	encode_getattw(xdw, nfs4_fsinfo_bitmap, bitmask,
			AWWAY_SIZE(nfs4_fsinfo_bitmap), hdw);
}

static void encode_fs_wocations(stwuct xdw_stweam *xdw, const u32* bitmask, stwuct compound_hdw *hdw)
{
	encode_getattw(xdw, nfs4_fs_wocations_bitmap, bitmask,
			AWWAY_SIZE(nfs4_fs_wocations_bitmap), hdw);
}

static void encode_getfh(stwuct xdw_stweam *xdw, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_GETFH, decode_getfh_maxsz, hdw);
}

static void encode_wink(stwuct xdw_stweam *xdw, const stwuct qstw *name, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WINK, decode_wink_maxsz, hdw);
	encode_stwing(xdw, name->wen, name->name);
}

static inwine int nfs4_wock_type(stwuct fiwe_wock *fw, int bwock)
{
	if (fw->fw_type == F_WDWCK)
		wetuwn bwock ? NFS4_WEADW_WT : NFS4_WEAD_WT;
	wetuwn bwock ? NFS4_WWITEW_WT : NFS4_WWITE_WT;
}

static inwine uint64_t nfs4_wock_wength(stwuct fiwe_wock *fw)
{
	if (fw->fw_end == OFFSET_MAX)
		wetuwn ~(uint64_t)0;
	wetuwn fw->fw_end - fw->fw_stawt + 1;
}

static void encode_wockownew(stwuct xdw_stweam *xdw, const stwuct nfs_wownew *wownew)
{
	__be32 *p;

	p = wesewve_space(xdw, 32);
	p = xdw_encode_hypew(p, wownew->cwientid);
	*p++ = cpu_to_be32(20);
	p = xdw_encode_opaque_fixed(p, "wock id:", 8);
	*p++ = cpu_to_be32(wownew->s_dev);
	xdw_encode_hypew(p, wownew->id);
}

/*
 * opcode,type,wecwaim,offset,wength,new_wock_ownew = 32
 * open_seqid,open_stateid,wock_seqid,wock_ownew.cwientid, wock_ownew.id = 40
 */
static void encode_wock(stwuct xdw_stweam *xdw, const stwuct nfs_wock_awgs *awgs, stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WOCK, decode_wock_maxsz, hdw);
	p = wesewve_space(xdw, 28);
	*p++ = cpu_to_be32(nfs4_wock_type(awgs->fw, awgs->bwock));
	*p++ = cpu_to_be32(awgs->wecwaim);
	p = xdw_encode_hypew(p, awgs->fw->fw_stawt);
	p = xdw_encode_hypew(p, nfs4_wock_wength(awgs->fw));
	*p = cpu_to_be32(awgs->new_wock_ownew);
	if (awgs->new_wock_ownew){
		encode_nfs4_seqid(xdw, awgs->open_seqid);
		encode_nfs4_stateid(xdw, &awgs->open_stateid);
		encode_nfs4_seqid(xdw, awgs->wock_seqid);
		encode_wockownew(xdw, &awgs->wock_ownew);
	}
	ewse {
		encode_nfs4_stateid(xdw, &awgs->wock_stateid);
		encode_nfs4_seqid(xdw, awgs->wock_seqid);
	}
}

static void encode_wockt(stwuct xdw_stweam *xdw, const stwuct nfs_wockt_awgs *awgs, stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WOCKT, decode_wockt_maxsz, hdw);
	p = wesewve_space(xdw, 20);
	*p++ = cpu_to_be32(nfs4_wock_type(awgs->fw, 0));
	p = xdw_encode_hypew(p, awgs->fw->fw_stawt);
	p = xdw_encode_hypew(p, nfs4_wock_wength(awgs->fw));
	encode_wockownew(xdw, &awgs->wock_ownew);
}

static void encode_wocku(stwuct xdw_stweam *xdw, const stwuct nfs_wocku_awgs *awgs, stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WOCKU, decode_wocku_maxsz, hdw);
	encode_uint32(xdw, nfs4_wock_type(awgs->fw, 0));
	encode_nfs4_seqid(xdw, awgs->seqid);
	encode_nfs4_stateid(xdw, &awgs->stateid);
	p = wesewve_space(xdw, 16);
	p = xdw_encode_hypew(p, awgs->fw->fw_stawt);
	xdw_encode_hypew(p, nfs4_wock_wength(awgs->fw));
}

static void encode_wewease_wockownew(stwuct xdw_stweam *xdw, const stwuct nfs_wownew *wownew, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WEWEASE_WOCKOWNEW, decode_wewease_wockownew_maxsz, hdw);
	encode_wockownew(xdw, wownew);
}

static void encode_wookup(stwuct xdw_stweam *xdw, const stwuct qstw *name, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WOOKUP, decode_wookup_maxsz, hdw);
	encode_stwing(xdw, name->wen, name->name);
}

static void encode_wookupp(stwuct xdw_stweam *xdw, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WOOKUPP, decode_wookupp_maxsz, hdw);
}

static void encode_shawe_access(stwuct xdw_stweam *xdw, u32 shawe_access)
{
	__be32 *p;

	p = wesewve_space(xdw, 8);
	*p++ = cpu_to_be32(shawe_access);
	*p = cpu_to_be32(0);		/* fow winux, shawe_deny = 0 awways */
}

static inwine void encode_openhdw(stwuct xdw_stweam *xdw, const stwuct nfs_openawgs *awg)
{
	__be32 *p;
 /*
 * opcode 4, seqid 4, shawe_access 4, shawe_deny 4, cwientid 8, ownewwen 4,
 * ownew 4 = 32
 */
	encode_nfs4_seqid(xdw, awg->seqid);
	encode_shawe_access(xdw, awg->shawe_access);
	p = wesewve_space(xdw, 36);
	p = xdw_encode_hypew(p, awg->cwientid);
	*p++ = cpu_to_be32(24);
	p = xdw_encode_opaque_fixed(p, "open id:", 8);
	*p++ = cpu_to_be32(awg->sewvew->s_dev);
	*p++ = cpu_to_be32(awg->id.uniquifiew);
	xdw_encode_hypew(p, awg->id.cweate_time);
}

static inwine void encode_cweatemode(stwuct xdw_stweam *xdw, const stwuct nfs_openawgs *awg)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	switch(awg->cweatemode) {
	case NFS4_CWEATE_UNCHECKED:
		*p = cpu_to_be32(NFS4_CWEATE_UNCHECKED);
		encode_attws(xdw, awg->u.attws, awg->wabew, &awg->umask,
				awg->sewvew, awg->sewvew->attw_bitmask);
		bweak;
	case NFS4_CWEATE_GUAWDED:
		*p = cpu_to_be32(NFS4_CWEATE_GUAWDED);
		encode_attws(xdw, awg->u.attws, awg->wabew, &awg->umask,
				awg->sewvew, awg->sewvew->attw_bitmask);
		bweak;
	case NFS4_CWEATE_EXCWUSIVE:
		*p = cpu_to_be32(NFS4_CWEATE_EXCWUSIVE);
		encode_nfs4_vewifiew(xdw, &awg->u.vewifiew);
		bweak;
	case NFS4_CWEATE_EXCWUSIVE4_1:
		*p = cpu_to_be32(NFS4_CWEATE_EXCWUSIVE4_1);
		encode_nfs4_vewifiew(xdw, &awg->u.vewifiew);
		encode_attws(xdw, awg->u.attws, awg->wabew, &awg->umask,
				awg->sewvew, awg->sewvew->excwcweat_bitmask);
	}
}

static void encode_opentype(stwuct xdw_stweam *xdw, const stwuct nfs_openawgs *awg)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	switch (awg->open_fwags & O_CWEAT) {
	case 0:
		*p = cpu_to_be32(NFS4_OPEN_NOCWEATE);
		bweak;
	defauwt:
		*p = cpu_to_be32(NFS4_OPEN_CWEATE);
		encode_cweatemode(xdw, awg);
	}
}

static inwine void encode_dewegation_type(stwuct xdw_stweam *xdw, fmode_t dewegation_type)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	switch (dewegation_type) {
	case 0:
		*p = cpu_to_be32(NFS4_OPEN_DEWEGATE_NONE);
		bweak;
	case FMODE_WEAD:
		*p = cpu_to_be32(NFS4_OPEN_DEWEGATE_WEAD);
		bweak;
	case FMODE_WWITE|FMODE_WEAD:
		*p = cpu_to_be32(NFS4_OPEN_DEWEGATE_WWITE);
		bweak;
	defauwt:
		BUG();
	}
}

static inwine void encode_cwaim_nuww(stwuct xdw_stweam *xdw, const stwuct qstw *name)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(NFS4_OPEN_CWAIM_NUWW);
	encode_stwing(xdw, name->wen, name->name);
}

static inwine void encode_cwaim_pwevious(stwuct xdw_stweam *xdw, fmode_t type)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(NFS4_OPEN_CWAIM_PWEVIOUS);
	encode_dewegation_type(xdw, type);
}

static inwine void encode_cwaim_dewegate_cuw(stwuct xdw_stweam *xdw, const stwuct qstw *name, const nfs4_stateid *stateid)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(NFS4_OPEN_CWAIM_DEWEGATE_CUW);
	encode_nfs4_stateid(xdw, stateid);
	encode_stwing(xdw, name->wen, name->name);
}

static inwine void encode_cwaim_fh(stwuct xdw_stweam *xdw)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(NFS4_OPEN_CWAIM_FH);
}

static inwine void encode_cwaim_dewegate_cuw_fh(stwuct xdw_stweam *xdw, const nfs4_stateid *stateid)
{
	__be32 *p;

	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(NFS4_OPEN_CWAIM_DEWEG_CUW_FH);
	encode_nfs4_stateid(xdw, stateid);
}

static void encode_open(stwuct xdw_stweam *xdw, const stwuct nfs_openawgs *awg, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_OPEN, decode_open_maxsz, hdw);
	encode_openhdw(xdw, awg);
	encode_opentype(xdw, awg);
	switch (awg->cwaim) {
	case NFS4_OPEN_CWAIM_NUWW:
		encode_cwaim_nuww(xdw, awg->name);
		bweak;
	case NFS4_OPEN_CWAIM_PWEVIOUS:
		encode_cwaim_pwevious(xdw, awg->u.dewegation_type);
		bweak;
	case NFS4_OPEN_CWAIM_DEWEGATE_CUW:
		encode_cwaim_dewegate_cuw(xdw, awg->name, &awg->u.dewegation);
		bweak;
	case NFS4_OPEN_CWAIM_FH:
		encode_cwaim_fh(xdw);
		bweak;
	case NFS4_OPEN_CWAIM_DEWEG_CUW_FH:
		encode_cwaim_dewegate_cuw_fh(xdw, &awg->u.dewegation);
		bweak;
	defauwt:
		BUG();
	}
}

static void encode_open_confiwm(stwuct xdw_stweam *xdw, const stwuct nfs_open_confiwmawgs *awg, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_OPEN_CONFIWM, decode_open_confiwm_maxsz, hdw);
	encode_nfs4_stateid(xdw, awg->stateid);
	encode_nfs4_seqid(xdw, awg->seqid);
}

static void encode_open_downgwade(stwuct xdw_stweam *xdw, const stwuct nfs_cwoseawgs *awg, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_OPEN_DOWNGWADE, decode_open_downgwade_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awg->stateid);
	encode_nfs4_seqid(xdw, awg->seqid);
	encode_shawe_access(xdw, awg->shawe_access);
}

static void
encode_putfh(stwuct xdw_stweam *xdw, const stwuct nfs_fh *fh, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_PUTFH, decode_putfh_maxsz, hdw);
	encode_stwing(xdw, fh->size, fh->data);
}

static void encode_putwootfh(stwuct xdw_stweam *xdw, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_PUTWOOTFH, decode_putwootfh_maxsz, hdw);
}

static void encode_wead(stwuct xdw_stweam *xdw, const stwuct nfs_pgio_awgs *awgs,
			stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WEAD, decode_wead_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->stateid);

	p = wesewve_space(xdw, 12);
	p = xdw_encode_hypew(p, awgs->offset);
	*p = cpu_to_be32(awgs->count);
}

static void encode_weaddiw(stwuct xdw_stweam *xdw, const stwuct nfs4_weaddiw_awg *weaddiw, stwuct wpc_wqst *weq, stwuct compound_hdw *hdw)
{
	uint32_t attws[3] = {
		FATTW4_WOWD0_TYPE
		| FATTW4_WOWD0_WDATTW_EWWOW,
		FATTW4_WOWD1_MOUNTED_ON_FIWEID,
	};
	uint32_t diwcount = weaddiw->count;
	uint32_t maxcount = weaddiw->count;
	__be32 *p, vewf[2];
	uint32_t attwwen = 0;
	unsigned int i;

	if (weaddiw->pwus) {
		attws[0] |= FATTW4_WOWD0_CHANGE
			| FATTW4_WOWD0_SIZE
			| FATTW4_WOWD0_FSID
			| FATTW4_WOWD0_FIWEHANDWE
			| FATTW4_WOWD0_FIWEID;
		attws[1] |= FATTW4_WOWD1_MODE
			| FATTW4_WOWD1_NUMWINKS
			| FATTW4_WOWD1_OWNEW
			| FATTW4_WOWD1_OWNEW_GWOUP
			| FATTW4_WOWD1_WAWDEV
			| FATTW4_WOWD1_SPACE_USED
			| FATTW4_WOWD1_TIME_ACCESS
			| FATTW4_WOWD1_TIME_METADATA
			| FATTW4_WOWD1_TIME_MODIFY;
		attws[2] |= FATTW4_WOWD2_SECUWITY_WABEW;
	}
	/* Use mounted_on_fiweid onwy if the sewvew suppowts it */
	if (!(weaddiw->bitmask[1] & FATTW4_WOWD1_MOUNTED_ON_FIWEID))
		attws[0] |= FATTW4_WOWD0_FIWEID;
	fow (i = 0; i < AWWAY_SIZE(attws); i++) {
		attws[i] &= weaddiw->bitmask[i];
		if (attws[i] != 0)
			attwwen = i+1;
	}

	encode_op_hdw(xdw, OP_WEADDIW, decode_weaddiw_maxsz, hdw);
	encode_uint64(xdw, weaddiw->cookie);
	encode_nfs4_vewifiew(xdw, &weaddiw->vewifiew);
	p = wesewve_space(xdw, 12 + (attwwen << 2));
	*p++ = cpu_to_be32(diwcount);
	*p++ = cpu_to_be32(maxcount);
	*p++ = cpu_to_be32(attwwen);
	fow (i = 0; i < attwwen; i++)
		*p++ = cpu_to_be32(attws[i]);
	memcpy(vewf, weaddiw->vewifiew.data, sizeof(vewf));

	dpwintk("%s: cookie = %wwu, vewifiew = %08x:%08x, bitmap = %08x:%08x:%08x\n",
			__func__,
			(unsigned wong wong)weaddiw->cookie,
			vewf[0], vewf[1],
			attws[0] & weaddiw->bitmask[0],
			attws[1] & weaddiw->bitmask[1],
			attws[2] & weaddiw->bitmask[2]);
}

static void encode_weadwink(stwuct xdw_stweam *xdw, const stwuct nfs4_weadwink *weadwink, stwuct wpc_wqst *weq, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WEADWINK, decode_weadwink_maxsz, hdw);
}

static void encode_wemove(stwuct xdw_stweam *xdw, const stwuct qstw *name, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WEMOVE, decode_wemove_maxsz, hdw);
	encode_stwing(xdw, name->wen, name->name);
}

static void encode_wename(stwuct xdw_stweam *xdw, const stwuct qstw *owdname, const stwuct qstw *newname, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WENAME, decode_wename_maxsz, hdw);
	encode_stwing(xdw, owdname->wen, owdname->name);
	encode_stwing(xdw, newname->wen, newname->name);
}

static void encode_wenew(stwuct xdw_stweam *xdw, cwientid4 cwid,
			 stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WENEW, decode_wenew_maxsz, hdw);
	encode_uint64(xdw, cwid);
}

static void
encode_westowefh(stwuct xdw_stweam *xdw, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WESTOWEFH, decode_westowefh_maxsz, hdw);
}

static void nfs4_acwtype_to_bitmap(enum nfs4_acw_type type, __u32 bitmap[2])
{
	switch (type) {
	defauwt:
		bitmap[0] = FATTW4_WOWD0_ACW;
		bitmap[1] = 0;
		bweak;
	case NFS4ACW_DACW:
		bitmap[0] = 0;
		bitmap[1] = FATTW4_WOWD1_DACW;
		bweak;
	case NFS4ACW_SACW:
		bitmap[0] = 0;
		bitmap[1] = FATTW4_WOWD1_SACW;
	}
}

static void encode_setacw(stwuct xdw_stweam *xdw,
			  const stwuct nfs_setacwawgs *awg,
			  stwuct compound_hdw *hdw)
{
	__u32 bitmap[2];

	nfs4_acwtype_to_bitmap(awg->acw_type, bitmap);

	encode_op_hdw(xdw, OP_SETATTW, decode_setacw_maxsz, hdw);
	encode_nfs4_stateid(xdw, &zewo_stateid);
	xdw_encode_bitmap4(xdw, bitmap, AWWAY_SIZE(bitmap));
	encode_uint32(xdw, awg->acw_wen);
	xdw_wwite_pages(xdw, awg->acw_pages, 0, awg->acw_wen);
}

static void
encode_savefh(stwuct xdw_stweam *xdw, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_SAVEFH, decode_savefh_maxsz, hdw);
}

static void encode_setattw(stwuct xdw_stweam *xdw, const stwuct nfs_setattwawgs *awg, const stwuct nfs_sewvew *sewvew, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_SETATTW, decode_setattw_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awg->stateid);
	encode_attws(xdw, awg->iap, awg->wabew, NUWW, sewvew,
			sewvew->attw_bitmask);
}

static void encode_setcwientid(stwuct xdw_stweam *xdw, const stwuct nfs4_setcwientid *setcwientid, stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_SETCWIENTID, decode_setcwientid_maxsz, hdw);
	encode_nfs4_vewifiew(xdw, setcwientid->sc_vewifiew);

	encode_stwing(xdw, stwwen(setcwientid->sc_cwnt->cw_ownew_id),
			setcwientid->sc_cwnt->cw_ownew_id);
	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(setcwientid->sc_pwog);
	encode_stwing(xdw, setcwientid->sc_netid_wen, setcwientid->sc_netid);
	encode_stwing(xdw, setcwientid->sc_uaddw_wen, setcwientid->sc_uaddw);
	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(setcwientid->sc_cwnt->cw_cb_ident);
}

static void encode_setcwientid_confiwm(stwuct xdw_stweam *xdw, const stwuct nfs4_setcwientid_wes *awg, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_SETCWIENTID_CONFIWM,
			decode_setcwientid_confiwm_maxsz, hdw);
	encode_uint64(xdw, awg->cwientid);
	encode_nfs4_vewifiew(xdw, &awg->confiwm);
}

static void encode_wwite(stwuct xdw_stweam *xdw, const stwuct nfs_pgio_awgs *awgs,
			 stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WWITE, decode_wwite_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->stateid);

	p = wesewve_space(xdw, 16);
	p = xdw_encode_hypew(p, awgs->offset);
	*p++ = cpu_to_be32(awgs->stabwe);
	*p = cpu_to_be32(awgs->count);

	xdw_wwite_pages(xdw, awgs->pages, awgs->pgbase, awgs->count);
}

static void encode_dewegwetuwn(stwuct xdw_stweam *xdw, const nfs4_stateid *stateid, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_DEWEGWETUWN, decode_dewegwetuwn_maxsz, hdw);
	encode_nfs4_stateid(xdw, stateid);
}

static void encode_secinfo(stwuct xdw_stweam *xdw, const stwuct qstw *name, stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_SECINFO, decode_secinfo_maxsz, hdw);
	encode_stwing(xdw, name->wen, name->name);
}

#if defined(CONFIG_NFS_V4_1)
/* NFSv4.1 opewations */
static void encode_bind_conn_to_session(stwuct xdw_stweam *xdw,
				   const stwuct nfs41_bind_conn_to_session_awgs *awgs,
				   stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_BIND_CONN_TO_SESSION,
		decode_bind_conn_to_session_maxsz, hdw);
	encode_opaque_fixed(xdw, awgs->sessionid.data, NFS4_MAX_SESSIONID_WEN);
	p = xdw_wesewve_space(xdw, 8);
	*p++ = cpu_to_be32(awgs->diw);
	*p = (awgs->use_conn_in_wdma_mode) ? cpu_to_be32(1) : cpu_to_be32(0);
}

static void encode_op_map(stwuct xdw_stweam *xdw, const stwuct nfs4_op_map *op_map)
{
	unsigned int i;
	encode_uint32(xdw, NFS4_OP_MAP_NUM_WOWDS);
	fow (i = 0; i < NFS4_OP_MAP_NUM_WOWDS; i++)
		encode_uint32(xdw, op_map->u.wowds[i]);
}

static void encode_exchange_id(stwuct xdw_stweam *xdw,
			       const stwuct nfs41_exchange_id_awgs *awgs,
			       stwuct compound_hdw *hdw)
{
	__be32 *p;
	chaw impw_name[IMPW_NAME_WIMIT];
	int wen = 0;

	encode_op_hdw(xdw, OP_EXCHANGE_ID, decode_exchange_id_maxsz, hdw);
	encode_nfs4_vewifiew(xdw, &awgs->vewifiew);

	encode_stwing(xdw, stwwen(awgs->cwient->cw_ownew_id),
			awgs->cwient->cw_ownew_id);

	encode_uint32(xdw, awgs->fwags);
	encode_uint32(xdw, awgs->state_pwotect.how);

	switch (awgs->state_pwotect.how) {
	case SP4_NONE:
		bweak;
	case SP4_MACH_CWED:
		encode_op_map(xdw, &awgs->state_pwotect.enfowce);
		encode_op_map(xdw, &awgs->state_pwotect.awwow);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	if (send_impwementation_id &&
	    sizeof(CONFIG_NFS_V4_1_IMPWEMENTATION_ID_DOMAIN) > 1 &&
	    sizeof(CONFIG_NFS_V4_1_IMPWEMENTATION_ID_DOMAIN)
		<= sizeof(impw_name) + 1)
		wen = snpwintf(impw_name, sizeof(impw_name), "%s %s %s %s",
			       utsname()->sysname, utsname()->wewease,
			       utsname()->vewsion, utsname()->machine);

	if (wen > 0) {
		encode_uint32(xdw, 1);	/* impwementation id awway wength=1 */

		encode_stwing(xdw,
			sizeof(CONFIG_NFS_V4_1_IMPWEMENTATION_ID_DOMAIN) - 1,
			CONFIG_NFS_V4_1_IMPWEMENTATION_ID_DOMAIN);
		encode_stwing(xdw, wen, impw_name);
		/* just send zewos fow nii_date - the date is in nii_name */
		p = wesewve_space(xdw, 12);
		p = xdw_encode_hypew(p, 0);
		*p = cpu_to_be32(0);
	} ewse
		encode_uint32(xdw, 0);	/* impwementation id awway wength=0 */
}

static void encode_cweate_session(stwuct xdw_stweam *xdw,
				  const stwuct nfs41_cweate_session_awgs *awgs,
				  stwuct compound_hdw *hdw)
{
	__be32 *p;
	stwuct nfs_cwient *cwp = awgs->cwient;
	stwuct wpc_cwnt *cwnt = cwp->cw_wpccwient;
	stwuct nfs_net *nn = net_genewic(cwp->cw_net, nfs_net_id);
	u32 max_wesp_sz_cached;

	/*
	 * Assumes OPEN is the biggest non-idempotent compound.
	 * 2 is the vewifiew.
	 */
	max_wesp_sz_cached = (NFS4_dec_open_sz + WPC_WEPHDWSIZE + 2)
				* XDW_UNIT + WPC_MAX_AUTH_SIZE;

	encode_op_hdw(xdw, OP_CWEATE_SESSION, decode_cweate_session_maxsz, hdw);
	p = wesewve_space(xdw, 16 + 2*28 + 20 + cwnt->cw_nodewen + 12);
	p = xdw_encode_hypew(p, awgs->cwientid);
	*p++ = cpu_to_be32(awgs->seqid);			/*Sequence id */
	*p++ = cpu_to_be32(awgs->fwags);			/*fwags */

	/* Fowe Channew */
	*p++ = cpu_to_be32(0);				/* headew padding size */
	*p++ = cpu_to_be32(awgs->fc_attws.max_wqst_sz);	/* max weq size */
	*p++ = cpu_to_be32(awgs->fc_attws.max_wesp_sz);	/* max wesp size */
	*p++ = cpu_to_be32(max_wesp_sz_cached);		/* Max wesp sz cached */
	*p++ = cpu_to_be32(awgs->fc_attws.max_ops);	/* max opewations */
	*p++ = cpu_to_be32(awgs->fc_attws.max_weqs);	/* max wequests */
	*p++ = cpu_to_be32(0);				/* wdmachannew_attws */

	/* Back Channew */
	*p++ = cpu_to_be32(0);				/* headew padding size */
	*p++ = cpu_to_be32(awgs->bc_attws.max_wqst_sz);	/* max weq size */
	*p++ = cpu_to_be32(awgs->bc_attws.max_wesp_sz);	/* max wesp size */
	*p++ = cpu_to_be32(awgs->bc_attws.max_wesp_sz_cached);	/* Max wesp sz cached */
	*p++ = cpu_to_be32(awgs->bc_attws.max_ops);	/* max opewations */
	*p++ = cpu_to_be32(awgs->bc_attws.max_weqs);	/* max wequests */
	*p++ = cpu_to_be32(0);				/* wdmachannew_attws */

	*p++ = cpu_to_be32(awgs->cb_pwogwam);		/* cb_pwogwam */
	*p++ = cpu_to_be32(1);
	*p++ = cpu_to_be32(WPC_AUTH_UNIX);			/* auth_sys */

	/* authsys_pawms wfc1831 */
	*p++ = cpu_to_be32(ktime_to_ns(nn->boot_time));	/* stamp */
	p = xdw_encode_awway(p, cwnt->cw_nodename, cwnt->cw_nodewen);
	*p++ = cpu_to_be32(0);				/* UID */
	*p++ = cpu_to_be32(0);				/* GID */
	*p = cpu_to_be32(0);				/* No mowe gids */
}

static void encode_destwoy_session(stwuct xdw_stweam *xdw,
				   const stwuct nfs4_session *session,
				   stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_DESTWOY_SESSION, decode_destwoy_session_maxsz, hdw);
	encode_opaque_fixed(xdw, session->sess_id.data, NFS4_MAX_SESSIONID_WEN);
}

static void encode_destwoy_cwientid(stwuct xdw_stweam *xdw,
				   uint64_t cwientid,
				   stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_DESTWOY_CWIENTID, decode_destwoy_cwientid_maxsz, hdw);
	encode_uint64(xdw, cwientid);
}

static void encode_wecwaim_compwete(stwuct xdw_stweam *xdw,
				    const stwuct nfs41_wecwaim_compwete_awgs *awgs,
				    stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WECWAIM_COMPWETE, decode_wecwaim_compwete_maxsz, hdw);
	encode_uint32(xdw, awgs->one_fs);
}
#endif /* CONFIG_NFS_V4_1 */

static void encode_sequence(stwuct xdw_stweam *xdw,
			    const stwuct nfs4_sequence_awgs *awgs,
			    stwuct compound_hdw *hdw)
{
#if defined(CONFIG_NFS_V4_1)
	stwuct nfs4_session *session;
	stwuct nfs4_swot_tabwe *tp;
	stwuct nfs4_swot *swot = awgs->sa_swot;
	__be32 *p;

	tp = swot->tabwe;
	session = tp->session;
	if (!session)
		wetuwn;

	encode_op_hdw(xdw, OP_SEQUENCE, decode_sequence_maxsz, hdw);

	/*
	 * Sessionid + seqid + swotid + max swotid + cache_this
	 */
	dpwintk("%s: sessionid=%u:%u:%u:%u seqid=%d swotid=%d "
		"max_swotid=%d cache_this=%d\n",
		__func__,
		((u32 *)session->sess_id.data)[0],
		((u32 *)session->sess_id.data)[1],
		((u32 *)session->sess_id.data)[2],
		((u32 *)session->sess_id.data)[3],
		swot->seq_nw, swot->swot_nw,
		tp->highest_used_swotid, awgs->sa_cache_this);
	p = wesewve_space(xdw, NFS4_MAX_SESSIONID_WEN + 16);
	p = xdw_encode_opaque_fixed(p, session->sess_id.data, NFS4_MAX_SESSIONID_WEN);
	*p++ = cpu_to_be32(swot->seq_nw);
	*p++ = cpu_to_be32(swot->swot_nw);
	*p++ = cpu_to_be32(tp->highest_used_swotid);
	*p = cpu_to_be32(awgs->sa_cache_this);
#endif /* CONFIG_NFS_V4_1 */
}

#ifdef CONFIG_NFS_V4_1
static void
encode_getdeviceinfo(stwuct xdw_stweam *xdw,
		     const stwuct nfs4_getdeviceinfo_awgs *awgs,
		     stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_GETDEVICEINFO, decode_getdeviceinfo_maxsz, hdw);
	p = wesewve_space(xdw, NFS4_DEVICEID4_SIZE + 4 + 4);
	p = xdw_encode_opaque_fixed(p, awgs->pdev->dev_id.data,
				    NFS4_DEVICEID4_SIZE);
	*p++ = cpu_to_be32(awgs->pdev->wayout_type);
	*p++ = cpu_to_be32(awgs->pdev->maxcount);	/* gdia_maxcount */

	p = wesewve_space(xdw, 4 + 4);
	*p++ = cpu_to_be32(1);			/* bitmap wength */
	*p++ = cpu_to_be32(awgs->notify_types);
}

static void
encode_wayoutget(stwuct xdw_stweam *xdw,
		      const stwuct nfs4_wayoutget_awgs *awgs,
		      stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WAYOUTGET, decode_wayoutget_maxsz, hdw);
	p = wesewve_space(xdw, 36);
	*p++ = cpu_to_be32(0);     /* Signaw wayout avaiwabwe */
	*p++ = cpu_to_be32(awgs->type);
	*p++ = cpu_to_be32(awgs->wange.iomode);
	p = xdw_encode_hypew(p, awgs->wange.offset);
	p = xdw_encode_hypew(p, awgs->wange.wength);
	p = xdw_encode_hypew(p, awgs->minwength);
	encode_nfs4_stateid(xdw, &awgs->stateid);
	encode_uint32(xdw, awgs->maxcount);

	dpwintk("%s: 1st type:0x%x iomode:%d off:%wu wen:%wu mc:%d\n",
		__func__,
		awgs->type,
		awgs->wange.iomode,
		(unsigned wong)awgs->wange.offset,
		(unsigned wong)awgs->wange.wength,
		awgs->maxcount);
}

static int
encode_wayoutcommit(stwuct xdw_stweam *xdw,
		    stwuct inode *inode,
		    const stwuct nfs4_wayoutcommit_awgs *awgs,
		    stwuct compound_hdw *hdw)
{
	__be32 *p;

	dpwintk("%s: wbw: %wwu type: %d\n", __func__, awgs->wastbytewwitten,
		NFS_SEWVEW(awgs->inode)->pnfs_cuww_wd->id);

	encode_op_hdw(xdw, OP_WAYOUTCOMMIT, decode_wayoutcommit_maxsz, hdw);
	p = wesewve_space(xdw, 20);
	/* Onwy whowe fiwe wayouts */
	p = xdw_encode_hypew(p, 0); /* offset */
	p = xdw_encode_hypew(p, awgs->wastbytewwitten + 1);	/* wength */
	*p = cpu_to_be32(0); /* wecwaim */
	encode_nfs4_stateid(xdw, &awgs->stateid);
	if (awgs->wastbytewwitten != U64_MAX) {
		p = wesewve_space(xdw, 20);
		*p++ = cpu_to_be32(1); /* newoffset = TWUE */
		p = xdw_encode_hypew(p, awgs->wastbytewwitten);
	} ewse {
		p = wesewve_space(xdw, 12);
		*p++ = cpu_to_be32(0); /* newoffset = FAWSE */
	}
	*p++ = cpu_to_be32(0); /* Nevew send time_modify_changed */
	*p++ = cpu_to_be32(NFS_SEWVEW(awgs->inode)->pnfs_cuww_wd->id);/* type */

	encode_uint32(xdw, awgs->wayoutupdate_wen);
	if (awgs->wayoutupdate_pages)
		xdw_wwite_pages(xdw, awgs->wayoutupdate_pages, 0,
				awgs->wayoutupdate_wen);

	wetuwn 0;
}

static void
encode_wayoutwetuwn(stwuct xdw_stweam *xdw,
		    const stwuct nfs4_wayoutwetuwn_awgs *awgs,
		    stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WAYOUTWETUWN, decode_wayoutwetuwn_maxsz, hdw);
	p = wesewve_space(xdw, 16);
	*p++ = cpu_to_be32(0);		/* wecwaim. awways 0 fow now */
	*p++ = cpu_to_be32(awgs->wayout_type);
	*p++ = cpu_to_be32(awgs->wange.iomode);
	*p = cpu_to_be32(WETUWN_FIWE);
	p = wesewve_space(xdw, 16);
	p = xdw_encode_hypew(p, awgs->wange.offset);
	p = xdw_encode_hypew(p, awgs->wange.wength);
	spin_wock(&awgs->inode->i_wock);
	encode_nfs4_stateid(xdw, &awgs->stateid);
	spin_unwock(&awgs->inode->i_wock);
	if (awgs->wd_pwivate->ops && awgs->wd_pwivate->ops->encode)
		awgs->wd_pwivate->ops->encode(xdw, awgs, awgs->wd_pwivate);
	ewse
		encode_uint32(xdw, 0);
}

static int
encode_secinfo_no_name(stwuct xdw_stweam *xdw,
		       const stwuct nfs41_secinfo_no_name_awgs *awgs,
		       stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_SECINFO_NO_NAME, decode_secinfo_no_name_maxsz, hdw);
	encode_uint32(xdw, awgs->stywe);
	wetuwn 0;
}

static void encode_test_stateid(stwuct xdw_stweam *xdw,
				const stwuct nfs41_test_stateid_awgs *awgs,
				stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_TEST_STATEID, decode_test_stateid_maxsz, hdw);
	encode_uint32(xdw, 1);
	encode_nfs4_stateid(xdw, awgs->stateid);
}

static void encode_fwee_stateid(stwuct xdw_stweam *xdw,
				const stwuct nfs41_fwee_stateid_awgs *awgs,
				stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_FWEE_STATEID, decode_fwee_stateid_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->stateid);
}
#ewse
static inwine void
encode_wayoutwetuwn(stwuct xdw_stweam *xdw,
		    const stwuct nfs4_wayoutwetuwn_awgs *awgs,
		    stwuct compound_hdw *hdw)
{
}

static void
encode_wayoutget(stwuct xdw_stweam *xdw,
		      const stwuct nfs4_wayoutget_awgs *awgs,
		      stwuct compound_hdw *hdw)
{
}
#endif /* CONFIG_NFS_V4_1 */

/*
 * END OF "GENEWIC" ENCODE WOUTINES.
 */

static u32 nfs4_xdw_minowvewsion(const stwuct nfs4_sequence_awgs *awgs)
{
#if defined(CONFIG_NFS_V4_1)
	stwuct nfs4_session *session = awgs->sa_swot->tabwe->session;
	if (session)
		wetuwn session->cwp->cw_mvops->minow_vewsion;
#endif /* CONFIG_NFS_V4_1 */
	wetuwn 0;
}

/*
 * Encode an ACCESS wequest
 */
static void nfs4_xdw_enc_access(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs4_accessawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_access(xdw, awgs->access, &hdw);
	if (awgs->bitmask)
		encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WOOKUP wequest
 */
static void nfs4_xdw_enc_wookup(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs4_wookup_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->diw_fh, &hdw);
	encode_wookup(xdw, awgs->name, &hdw);
	encode_getfh(xdw, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WOOKUPP wequest
 */
static void nfs4_xdw_enc_wookupp(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
		const void *data)
{
	const stwuct nfs4_wookupp_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wookupp(xdw, &hdw);
	encode_getfh(xdw, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WOOKUP_WOOT wequest
 */
static void nfs4_xdw_enc_wookup_woot(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs4_wookup_woot_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putwootfh(xdw, &hdw);
	encode_getfh(xdw, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WEMOVE wequest
 */
static void nfs4_xdw_enc_wemove(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs_wemoveawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wemove(xdw, &awgs->name, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WENAME wequest
 */
static void nfs4_xdw_enc_wename(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs_wenameawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->owd_diw, &hdw);
	encode_savefh(xdw, &hdw);
	encode_putfh(xdw, awgs->new_diw, &hdw);
	encode_wename(xdw, awgs->owd_name, awgs->new_name, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WINK wequest
 */
static void nfs4_xdw_enc_wink(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			      const void *data)
{
	const stwuct nfs4_wink_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_savefh(xdw, &hdw);
	encode_putfh(xdw, awgs->diw_fh, &hdw);
	encode_wink(xdw, awgs->name, &hdw);
	encode_westowefh(xdw, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode CWEATE wequest
 */
static void nfs4_xdw_enc_cweate(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs4_cweate_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->diw_fh, &hdw);
	encode_cweate(xdw, awgs, &hdw);
	encode_getfh(xdw, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode SYMWINK wequest
 */
static void nfs4_xdw_enc_symwink(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nfs4_cweate_awg *awgs = data;

	nfs4_xdw_enc_cweate(weq, xdw, awgs);
}

/*
 * Encode GETATTW wequest
 */
static void nfs4_xdw_enc_getattw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nfs4_getattw_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode a CWOSE wequest
 */
static void nfs4_xdw_enc_cwose(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       const void *data)
{
	const stwuct nfs_cwoseawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	if (awgs->ww_awgs)
		encode_wayoutwetuwn(xdw, awgs->ww_awgs, &hdw);
	if (awgs->bitmask != NUWW)
		encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_cwose(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode an OPEN wequest
 */
static void nfs4_xdw_enc_open(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			      const void *data)
{
	const stwuct nfs_openawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_open(xdw, awgs, &hdw);
	encode_getfh(xdw, &hdw);
	if (awgs->access)
		encode_access(xdw, awgs->access, &hdw);
	encode_getfattw_open(xdw, awgs->bitmask, awgs->open_bitmap, &hdw);
	if (awgs->wg_awgs) {
		encode_wayoutget(xdw, awgs->wg_awgs, &hdw);
		wpc_pwepawe_wepwy_pages(weq, awgs->wg_awgs->wayout.pages, 0,
					awgs->wg_awgs->wayout.pgwen,
					hdw.wepwen - pagepad_maxsz);
	}
	encode_nops(&hdw);
}

/*
 * Encode an OPEN_CONFIWM wequest
 */
static void nfs4_xdw_enc_open_confiwm(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs_open_confiwmawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.nops   = 0,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_open_confiwm(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode an OPEN wequest with no attwibutes.
 */
static void nfs4_xdw_enc_open_noattw(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs_openawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_open(xdw, awgs, &hdw);
	if (awgs->access)
		encode_access(xdw, awgs->access, &hdw);
	encode_getfattw_open(xdw, awgs->bitmask, awgs->open_bitmap, &hdw);
	if (awgs->wg_awgs) {
		encode_wayoutget(xdw, awgs->wg_awgs, &hdw);
		wpc_pwepawe_wepwy_pages(weq, awgs->wg_awgs->wayout.pages, 0,
					awgs->wg_awgs->wayout.pgwen,
					hdw.wepwen - pagepad_maxsz);
	}
	encode_nops(&hdw);
}

/*
 * Encode an OPEN_DOWNGWADE wequest
 */
static void nfs4_xdw_enc_open_downgwade(stwuct wpc_wqst *weq,
					stwuct xdw_stweam *xdw,
					const void *data)
{
	const stwuct nfs_cwoseawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	if (awgs->ww_awgs)
		encode_wayoutwetuwn(xdw, awgs->ww_awgs, &hdw);
	encode_open_downgwade(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode a WOCK wequest
 */
static void nfs4_xdw_enc_wock(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			      const void *data)
{
	const stwuct nfs_wock_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wock(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode a WOCKT wequest
 */
static void nfs4_xdw_enc_wockt(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       const void *data)
{
	const stwuct nfs_wockt_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wockt(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode a WOCKU wequest
 */
static void nfs4_xdw_enc_wocku(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       const void *data)
{
	const stwuct nfs_wocku_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wocku(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

static void nfs4_xdw_enc_wewease_wockownew(stwuct wpc_wqst *weq,
					   stwuct xdw_stweam *xdw,
					   const void *data)
{
	const stwuct nfs_wewease_wockownew_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = 0,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_wewease_wockownew(xdw, &awgs->wock_ownew, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode a WEADWINK wequest
 */
static void nfs4_xdw_enc_weadwink(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				  const void *data)
{
	const stwuct nfs4_weadwink *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_weadwink(xdw, awgs, weq, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->pages, awgs->pgbase,
				awgs->pgwen, hdw.wepwen - pagepad_maxsz);
	encode_nops(&hdw);
}

/*
 * Encode a WEADDIW wequest
 */
static void nfs4_xdw_enc_weaddiw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nfs4_weaddiw_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_weaddiw(xdw, awgs, weq, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->pages, awgs->pgbase,
				awgs->count, hdw.wepwen - pagepad_maxsz);
	encode_nops(&hdw);
}

/*
 * Encode a WEAD wequest
 */
static void nfs4_xdw_enc_wead(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			      const void *data)
{
	const stwuct nfs_pgio_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wead(xdw, awgs, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->pages, awgs->pgbase,
				awgs->count, hdw.wepwen - pagepad_maxsz);
	weq->wq_wcv_buf.fwags |= XDWBUF_WEAD;
	encode_nops(&hdw);
}

/*
 * Encode an SETATTW wequest
 */
static void nfs4_xdw_enc_setattw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nfs_setattwawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_setattw(xdw, awgs, awgs->sewvew, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode a GETACW wequest
 */
static void nfs4_xdw_enc_getacw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs_getacwawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};
	__u32 nfs4_acw_bitmap[2];
	uint32_t wepwen;

	nfs4_acwtype_to_bitmap(awgs->acw_type, nfs4_acw_bitmap);

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	wepwen = hdw.wepwen + op_decode_hdw_maxsz;
	encode_getattw(xdw, nfs4_acw_bitmap, NUWW,
			AWWAY_SIZE(nfs4_acw_bitmap), &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->acw_pages, 0,
				awgs->acw_wen, wepwen);
	encode_nops(&hdw);
}

/*
 * Encode a WWITE wequest
 */
static void nfs4_xdw_enc_wwite(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       const void *data)
{
	const stwuct nfs_pgio_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wwite(xdw, awgs, &hdw);
	weq->wq_snd_buf.fwags |= XDWBUF_WWITE;
	if (awgs->bitmask)
		encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 *  a COMMIT wequest
 */
static void nfs4_xdw_enc_commit(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs_commitawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_commit(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * FSINFO wequest
 */
static void nfs4_xdw_enc_fsinfo(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs4_fsinfo_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_fsinfo(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * a PATHCONF wequest
 */
static void nfs4_xdw_enc_pathconf(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				  const void *data)
{
	const stwuct nfs4_pathconf_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_getattw(xdw, nfs4_pathconf_bitmap, awgs->bitmask,
			AWWAY_SIZE(nfs4_pathconf_bitmap), &hdw);
	encode_nops(&hdw);
}

/*
 * a STATFS wequest
 */
static void nfs4_xdw_enc_statfs(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs4_statfs_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_getattw(xdw, nfs4_statfs_bitmap, awgs->bitmask,
			AWWAY_SIZE(nfs4_statfs_bitmap), &hdw);
	encode_nops(&hdw);
}

/*
 * GETATTW_BITMAP wequest
 */
static void nfs4_xdw_enc_sewvew_caps(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs4_sewvew_caps_awg *awgs = data;
	const u32 *bitmask = awgs->bitmask;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fhandwe, &hdw);
	encode_getattw(xdw, bitmask, NUWW, 3, &hdw);
	encode_nops(&hdw);
}

/*
 * a WENEW wequest
 */
static void nfs4_xdw_enc_wenew(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       const void *data)

{
	const stwuct nfs_cwient *cwp = data;
	stwuct compound_hdw hdw = {
		.nops	= 0,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_wenew(xdw, cwp->cw_cwientid, &hdw);
	encode_nops(&hdw);
}

/*
 * a SETCWIENTID wequest
 */
static void nfs4_xdw_enc_setcwientid(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs4_setcwientid *sc = data;
	stwuct compound_hdw hdw = {
		.nops	= 0,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_setcwientid(xdw, sc, &hdw);
	encode_nops(&hdw);
}

/*
 * a SETCWIENTID_CONFIWM wequest
 */
static void nfs4_xdw_enc_setcwientid_confiwm(stwuct wpc_wqst *weq,
					     stwuct xdw_stweam *xdw,
					     const void *data)
{
	const stwuct nfs4_setcwientid_wes *awg = data;
	stwuct compound_hdw hdw = {
		.nops	= 0,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_setcwientid_confiwm(xdw, awg, &hdw);
	encode_nops(&hdw);
}

/*
 * DEWEGWETUWN wequest
 */
static void nfs4_xdw_enc_dewegwetuwn(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs4_dewegwetuwnawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fhandwe, &hdw);
	if (awgs->ww_awgs)
		encode_wayoutwetuwn(xdw, awgs->ww_awgs, &hdw);
	if (awgs->bitmask)
		encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_dewegwetuwn(xdw, awgs->stateid, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode FS_WOCATIONS wequest
 */
static void nfs4_xdw_enc_fs_wocations(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs4_fs_wocations_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};
	uint32_t wepwen;

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	if (awgs->migwation) {
		encode_putfh(xdw, awgs->fh, &hdw);
		wepwen = hdw.wepwen;
		encode_fs_wocations(xdw, awgs->bitmask, &hdw);
		if (awgs->wenew)
			encode_wenew(xdw, awgs->cwientid, &hdw);
	} ewse {
		encode_putfh(xdw, awgs->diw_fh, &hdw);
		encode_wookup(xdw, awgs->name, &hdw);
		wepwen = hdw.wepwen;
		encode_fs_wocations(xdw, awgs->bitmask, &hdw);
	}

	wpc_pwepawe_wepwy_pages(weq, (stwuct page **)&awgs->page, 0,
				PAGE_SIZE, wepwen);
	encode_nops(&hdw);
}

/*
 * Encode SECINFO wequest
 */
static void nfs4_xdw_enc_secinfo(stwuct wpc_wqst *weq,
				stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs4_secinfo_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->diw_fh, &hdw);
	encode_secinfo(xdw, awgs->name, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode FSID_PWESENT wequest
 */
static void nfs4_xdw_enc_fsid_pwesent(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs4_fsid_pwesent_awg *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_getfh(xdw, &hdw);
	if (awgs->wenew)
		encode_wenew(xdw, awgs->cwientid, &hdw);
	encode_nops(&hdw);
}

#if defined(CONFIG_NFS_V4_1)
/*
 * BIND_CONN_TO_SESSION wequest
 */
static void nfs4_xdw_enc_bind_conn_to_session(stwuct wpc_wqst *weq,
				stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs41_bind_conn_to_session_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = awgs->cwient->cw_mvops->minow_vewsion,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_bind_conn_to_session(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * EXCHANGE_ID wequest
 */
static void nfs4_xdw_enc_exchange_id(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs41_exchange_id_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = awgs->cwient->cw_mvops->minow_vewsion,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_exchange_id(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * a CWEATE_SESSION wequest
 */
static void nfs4_xdw_enc_cweate_session(stwuct wpc_wqst *weq,
					stwuct xdw_stweam *xdw,
					const void *data)
{
	const stwuct nfs41_cweate_session_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = awgs->cwient->cw_mvops->minow_vewsion,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_cweate_session(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * a DESTWOY_SESSION wequest
 */
static void nfs4_xdw_enc_destwoy_session(stwuct wpc_wqst *weq,
					 stwuct xdw_stweam *xdw,
					 const void *data)
{
	const stwuct nfs4_session *session = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = session->cwp->cw_mvops->minow_vewsion,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_destwoy_session(xdw, session, &hdw);
	encode_nops(&hdw);
}

/*
 * a DESTWOY_CWIENTID wequest
 */
static void nfs4_xdw_enc_destwoy_cwientid(stwuct wpc_wqst *weq,
					 stwuct xdw_stweam *xdw,
					 const void *data)
{
	const stwuct nfs_cwient *cwp = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = cwp->cw_mvops->minow_vewsion,
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_destwoy_cwientid(xdw, cwp->cw_cwientid, &hdw);
	encode_nops(&hdw);
}

/*
 * a SEQUENCE wequest
 */
static void nfs4_xdw_enc_sequence(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				  const void *data)
{
	const stwuct nfs4_sequence_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

#endif

/*
 * a GET_WEASE_TIME wequest
 */
static void nfs4_xdw_enc_get_wease_time(stwuct wpc_wqst *weq,
					stwuct xdw_stweam *xdw,
					const void *data)
{
	const stwuct nfs4_get_wease_time_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->wa_seq_awgs),
	};
	const u32 wease_bitmap[3] = { FATTW4_WOWD0_WEASE_TIME };

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->wa_seq_awgs, &hdw);
	encode_putwootfh(xdw, &hdw);
	encode_fsinfo(xdw, wease_bitmap, &hdw);
	encode_nops(&hdw);
}

#ifdef CONFIG_NFS_V4_1

/*
 * a WECWAIM_COMPWETE wequest
 */
static void nfs4_xdw_enc_wecwaim_compwete(stwuct wpc_wqst *weq,
					  stwuct xdw_stweam *xdw,
					  const void *data)
{
	const stwuct nfs41_wecwaim_compwete_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs)
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_wecwaim_compwete(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode GETDEVICEINFO wequest
 */
static void nfs4_xdw_enc_getdeviceinfo(stwuct wpc_wqst *weq,
				       stwuct xdw_stweam *xdw,
				       const void *data)
{
	const stwuct nfs4_getdeviceinfo_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};
	uint32_t wepwen;

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);

	wepwen = hdw.wepwen + op_decode_hdw_maxsz + 2;

	encode_getdeviceinfo(xdw, awgs, &hdw);

	/* set up wepwy kvec. device_addw4 opaque data is wead into the
	 * pages */
	wpc_pwepawe_wepwy_pages(weq, awgs->pdev->pages, awgs->pdev->pgbase,
				awgs->pdev->pgwen, wepwen);
	encode_nops(&hdw);
}

/*
 *  Encode WAYOUTGET wequest
 */
static void nfs4_xdw_enc_wayoutget(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nfs4_wayoutget_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, NFS_FH(awgs->inode), &hdw);
	encode_wayoutget(xdw, awgs, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->wayout.pages, 0,
				awgs->wayout.pgwen, hdw.wepwen - pagepad_maxsz);
	encode_nops(&hdw);
}

/*
 *  Encode WAYOUTCOMMIT wequest
 */
static void nfs4_xdw_enc_wayoutcommit(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *pwiv)
{
	const stwuct nfs4_wayoutcommit_awgs *awgs = pwiv;
	stwuct nfs4_wayoutcommit_data *data =
		containew_of(awgs, stwuct nfs4_wayoutcommit_data, awgs);
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, NFS_FH(awgs->inode), &hdw);
	encode_wayoutcommit(xdw, data->awgs.inode, awgs, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WAYOUTWETUWN wequest
 */
static void nfs4_xdw_enc_wayoutwetuwn(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs4_wayoutwetuwn_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, NFS_FH(awgs->inode), &hdw);
	encode_wayoutwetuwn(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode SECINFO_NO_NAME wequest
 */
static void nfs4_xdw_enc_secinfo_no_name(stwuct wpc_wqst *weq,
					stwuct xdw_stweam *xdw,
					const void *data)
{
	const stwuct nfs41_secinfo_no_name_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putwootfh(xdw, &hdw);
	encode_secinfo_no_name(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 *  Encode TEST_STATEID wequest
 */
static void nfs4_xdw_enc_test_stateid(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs41_test_stateid_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_test_stateid(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 *  Encode FWEE_STATEID wequest
 */
static void nfs4_xdw_enc_fwee_stateid(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs41_fwee_stateid_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_fwee_stateid(xdw, awgs, &hdw);
	encode_nops(&hdw);
}
#endif /* CONFIG_NFS_V4_1 */

static int decode_opaque_inwine(stwuct xdw_stweam *xdw, unsigned int *wen, chaw **stwing)
{
	ssize_t wet = xdw_stweam_decode_opaque_inwine(xdw, (void **)stwing,
			NFS4_OPAQUE_WIMIT);
	if (unwikewy(wet < 0))
		wetuwn -EIO;
	*wen = wet;
	wetuwn 0;
}

static int decode_compound_hdw(stwuct xdw_stweam *xdw, stwuct compound_hdw *hdw)
{
	ssize_t wet;
	void *ptw;
	u32 tmp;

	if (xdw_stweam_decode_u32(xdw, &tmp) < 0)
		wetuwn -EIO;
	hdw->status = tmp;

	wet = xdw_stweam_decode_opaque_inwine(xdw, &ptw, NFS4_OPAQUE_WIMIT);
	if (wet < 0)
		wetuwn -EIO;
	hdw->tagwen = wet;
	hdw->tag = ptw;

	if (xdw_stweam_decode_u32(xdw, &tmp) < 0)
		wetuwn -EIO;
	hdw->nops = tmp;
	if (unwikewy(hdw->nops < 1))
		wetuwn nfs4_stat_to_ewwno(hdw->status);
	wetuwn 0;
}

static boow __decode_op_hdw(stwuct xdw_stweam *xdw, enum nfs_opnum4 expected,
		int *nfs_wetvaw)
{
	__be32 *p;
	uint32_t opnum;
	int32_t nfseww;

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		goto out_ovewfwow;
	opnum = be32_to_cpup(p++);
	if (unwikewy(opnum != expected))
		goto out_bad_opewation;
	if (unwikewy(*p != cpu_to_be32(NFS_OK)))
		goto out_status;
	*nfs_wetvaw = 0;
	wetuwn twue;
out_status:
	nfseww = be32_to_cpup(p);
	twace_nfs4_xdw_status(xdw, opnum, nfseww);
	*nfs_wetvaw = nfs4_stat_to_ewwno(nfseww);
	wetuwn twue;
out_bad_opewation:
	twace_nfs4_xdw_bad_opewation(xdw, opnum, expected);
	*nfs_wetvaw = -EWEMOTEIO;
	wetuwn fawse;
out_ovewfwow:
	*nfs_wetvaw = -EIO;
	wetuwn fawse;
}

static int decode_op_hdw(stwuct xdw_stweam *xdw, enum nfs_opnum4 expected)
{
	int wetvaw;

	__decode_op_hdw(xdw, expected, &wetvaw);
	wetuwn wetvaw;
}

/* Dummy woutine */
static int decode_ace(stwuct xdw_stweam *xdw, void *ace)
{
	__be32 *p;
	unsigned int stwwen;
	chaw *stw;

	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(!p))
		wetuwn -EIO;
	wetuwn decode_opaque_inwine(xdw, &stwwen, &stw);
}

static ssize_t
decode_bitmap4(stwuct xdw_stweam *xdw, uint32_t *bitmap, size_t sz)
{
	ssize_t wet;

	wet = xdw_stweam_decode_uint32_awway(xdw, bitmap, sz);
	if (wikewy(wet >= 0))
		wetuwn wet;
	if (wet != -EMSGSIZE)
		wetuwn -EIO;
	wetuwn sz;
}

static int decode_attw_bitmap(stwuct xdw_stweam *xdw, uint32_t *bitmap)
{
	ssize_t wet;
	wet = decode_bitmap4(xdw, bitmap, 3);
	wetuwn wet < 0 ? wet : 0;
}

static int decode_attw_wength(stwuct xdw_stweam *xdw, uint32_t *attwwen, unsigned int *savep)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	*attwwen = be32_to_cpup(p);
	*savep = xdw_stweam_pos(xdw);
	wetuwn 0;
}

static int decode_attw_suppowted(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *bitmask)
{
	if (wikewy(bitmap[0] & FATTW4_WOWD0_SUPPOWTED_ATTWS)) {
		int wet;
		wet = decode_attw_bitmap(xdw, bitmask);
		if (unwikewy(wet < 0))
			wetuwn wet;
		bitmap[0] &= ~FATTW4_WOWD0_SUPPOWTED_ATTWS;
	} ewse
		bitmask[0] = bitmask[1] = bitmask[2] = 0;
	dpwintk("%s: bitmask=%08x:%08x:%08x\n", __func__,
		bitmask[0], bitmask[1], bitmask[2]);
	wetuwn 0;
}

static int decode_attw_type(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *type)
{
	__be32 *p;
	int wet = 0;

	*type = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_TYPE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_TYPE)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*type = be32_to_cpup(p);
		if (*type < NF4WEG || *type > NF4NAMEDATTW) {
			dpwintk("%s: bad type %d\n", __func__, *type);
			wetuwn -EIO;
		}
		bitmap[0] &= ~FATTW4_WOWD0_TYPE;
		wet = NFS_ATTW_FATTW_TYPE;
	}
	dpwintk("%s: type=0%o\n", __func__, nfs_type2fmt[*type]);
	wetuwn wet;
}

static int decode_attw_fh_expiwe_type(stwuct xdw_stweam *xdw,
				      uint32_t *bitmap, uint32_t *type)
{
	__be32 *p;

	*type = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FH_EXPIWE_TYPE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FH_EXPIWE_TYPE)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*type = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_FH_EXPIWE_TYPE;
	}
	dpwintk("%s: expiwe type=0x%x\n", __func__, *type);
	wetuwn 0;
}

static int decode_attw_change(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *change)
{
	__be32 *p;
	int wet = 0;

	*change = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_CHANGE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_CHANGE)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, change);
		bitmap[0] &= ~FATTW4_WOWD0_CHANGE;
		wet = NFS_ATTW_FATTW_CHANGE;
	}
	dpwintk("%s: change attwibute=%Wu\n", __func__,
			(unsigned wong wong)*change);
	wetuwn wet;
}

static int decode_attw_size(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *size)
{
	__be32 *p;
	int wet = 0;

	*size = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_SIZE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_SIZE)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, size);
		bitmap[0] &= ~FATTW4_WOWD0_SIZE;
		wet = NFS_ATTW_FATTW_SIZE;
	}
	dpwintk("%s: fiwe size=%Wu\n", __func__, (unsigned wong wong)*size);
	wetuwn wet;
}

static int decode_attw_wink_suppowt(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_WINK_SUPPOWT - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_WINK_SUPPOWT)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_WINK_SUPPOWT;
	}
	dpwintk("%s: wink suppowt=%s\n", __func__, *wes == 0 ? "fawse" : "twue");
	wetuwn 0;
}

static int decode_attw_symwink_suppowt(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_SYMWINK_SUPPOWT - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_SYMWINK_SUPPOWT)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_SYMWINK_SUPPOWT;
	}
	dpwintk("%s: symwink suppowt=%s\n", __func__, *wes == 0 ? "fawse" : "twue");
	wetuwn 0;
}

static int decode_attw_fsid(stwuct xdw_stweam *xdw, uint32_t *bitmap, stwuct nfs_fsid *fsid)
{
	__be32 *p;
	int wet = 0;

	fsid->majow = 0;
	fsid->minow = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FSID - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FSID)) {
		p = xdw_inwine_decode(xdw, 16);
		if (unwikewy(!p))
			wetuwn -EIO;
		p = xdw_decode_hypew(p, &fsid->majow);
		xdw_decode_hypew(p, &fsid->minow);
		bitmap[0] &= ~FATTW4_WOWD0_FSID;
		wet = NFS_ATTW_FATTW_FSID;
	}
	dpwintk("%s: fsid=(0x%Wx/0x%Wx)\n", __func__,
			(unsigned wong wong)fsid->majow,
			(unsigned wong wong)fsid->minow);
	wetuwn wet;
}

static int decode_attw_wease_time(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;

	*wes = 60;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_WEASE_TIME - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_WEASE_TIME)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_WEASE_TIME;
	}
	dpwintk("%s: wease time=%u\n", __func__, (unsigned int)*wes);
	wetuwn 0;
}

static int decode_attw_ewwow(stwuct xdw_stweam *xdw, uint32_t *bitmap, int32_t *wes)
{
	__be32 *p;

	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_WDATTW_EWWOW - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_WDATTW_EWWOW)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		bitmap[0] &= ~FATTW4_WOWD0_WDATTW_EWWOW;
		*wes = -be32_to_cpup(p);
	}
	wetuwn 0;
}

static int decode_attw_excwcweat_suppowted(stwuct xdw_stweam *xdw,
				 uint32_t *bitmap, uint32_t *bitmask)
{
	if (wikewy(bitmap[2] & FATTW4_WOWD2_SUPPATTW_EXCWCWEAT)) {
		int wet;
		wet = decode_attw_bitmap(xdw, bitmask);
		if (unwikewy(wet < 0))
			wetuwn wet;
		bitmap[2] &= ~FATTW4_WOWD2_SUPPATTW_EXCWCWEAT;
	} ewse
		bitmask[0] = bitmask[1] = bitmask[2] = 0;
	dpwintk("%s: bitmask=%08x:%08x:%08x\n", __func__,
		bitmask[0], bitmask[1], bitmask[2]);
	wetuwn 0;
}

static int decode_attw_fiwehandwe(stwuct xdw_stweam *xdw, uint32_t *bitmap, stwuct nfs_fh *fh)
{
	__be32 *p;
	u32 wen;

	if (fh != NUWW)
		memset(fh, 0, sizeof(*fh));

	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FIWEHANDWE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FIWEHANDWE)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		wen = be32_to_cpup(p);
		if (wen > NFS4_FHSIZE || wen == 0) {
			twace_nfs4_xdw_bad_fiwehandwe(xdw, OP_WEADDIW,
						      NFS4EWW_BADHANDWE);
			wetuwn -EWEMOTEIO;
		}
		p = xdw_inwine_decode(xdw, wen);
		if (unwikewy(!p))
			wetuwn -EIO;
		if (fh != NUWW) {
			memcpy(fh->data, p, wen);
			fh->size = wen;
		}
		bitmap[0] &= ~FATTW4_WOWD0_FIWEHANDWE;
	}
	wetuwn 0;
}

static int decode_attw_acwsuppowt(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_ACWSUPPOWT - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_ACWSUPPOWT)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_ACWSUPPOWT;
	}
	dpwintk("%s: ACWs suppowted=%u\n", __func__, (unsigned int)*wes);
	wetuwn 0;
}

static int decode_attw_case_insensitive(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_CASE_INSENSITIVE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_CASE_INSENSITIVE)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_CASE_INSENSITIVE;
	}
	dpwintk("%s: case_insensitive=%s\n", __func__, *wes == 0 ? "fawse" : "twue");
	wetuwn 0;
}

static int decode_attw_case_pwesewving(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_CASE_PWESEWVING - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_CASE_PWESEWVING)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_CASE_PWESEWVING;
	}
	dpwintk("%s: case_pwesewving=%s\n", __func__, *wes == 0 ? "fawse" : "twue");
	wetuwn 0;
}

static int decode_attw_fiweid(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *fiweid)
{
	__be32 *p;
	int wet = 0;

	*fiweid = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FIWEID - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FIWEID)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, fiweid);
		bitmap[0] &= ~FATTW4_WOWD0_FIWEID;
		wet = NFS_ATTW_FATTW_FIWEID;
	}
	dpwintk("%s: fiweid=%Wu\n", __func__, (unsigned wong wong)*fiweid);
	wetuwn wet;
}

static int decode_attw_mounted_on_fiweid(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *fiweid)
{
	__be32 *p;
	int wet = 0;

	*fiweid = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_MOUNTED_ON_FIWEID - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_MOUNTED_ON_FIWEID)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, fiweid);
		bitmap[1] &= ~FATTW4_WOWD1_MOUNTED_ON_FIWEID;
		wet = NFS_ATTW_FATTW_MOUNTED_ON_FIWEID;
	}
	dpwintk("%s: fiweid=%Wu\n", __func__, (unsigned wong wong)*fiweid);
	wetuwn wet;
}

static int decode_attw_fiwes_avaiw(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FIWES_AVAIW - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FIWES_AVAIW)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[0] &= ~FATTW4_WOWD0_FIWES_AVAIW;
	}
	dpwintk("%s: fiwes avaiw=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_attw_fiwes_fwee(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FIWES_FWEE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FIWES_FWEE)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[0] &= ~FATTW4_WOWD0_FIWES_FWEE;
	}
	dpwintk("%s: fiwes fwee=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_attw_fiwes_totaw(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FIWES_TOTAW - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_FIWES_TOTAW)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[0] &= ~FATTW4_WOWD0_FIWES_TOTAW;
	}
	dpwintk("%s: fiwes totaw=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_pathname(stwuct xdw_stweam *xdw, stwuct nfs4_pathname *path)
{
	u32 n;
	__be32 *p;
	int status = 0;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	n = be32_to_cpup(p);
	if (n == 0)
		goto woot_path;
	dpwintk("pathname4: ");
	if (n > NFS4_PATHNAME_MAXCOMPONENTS) {
		dpwintk("cannot pawse %d components in path\n", n);
		goto out_eio;
	}
	fow (path->ncomponents = 0; path->ncomponents < n; path->ncomponents++) {
		stwuct nfs4_stwing *component = &path->components[path->ncomponents];
		status = decode_opaque_inwine(xdw, &component->wen, &component->data);
		if (unwikewy(status != 0))
			goto out_eio;
		ifdebug (XDW)
			pw_cont("%s%.*s ",
				(path->ncomponents != n ? "/ " : ""),
				component->wen, component->data);
	}
out:
	wetuwn status;
woot_path:
/* a woot pathname is sent as a zewo component4 */
	path->ncomponents = 1;
	path->components[0].wen=0;
	path->components[0].data=NUWW;
	dpwintk("pathname4: /\n");
	goto out;
out_eio:
	dpwintk(" status %d", status);
	status = -EIO;
	goto out;
}

static int decode_attw_fs_wocations(stwuct xdw_stweam *xdw, uint32_t *bitmap, stwuct nfs4_fs_wocations *wes)
{
	int n;
	__be32 *p;
	int status = -EIO;

	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_FS_WOCATIONS -1U)))
		goto out;
	status = 0;
	if (unwikewy(!(bitmap[0] & FATTW4_WOWD0_FS_WOCATIONS)))
		goto out;
	bitmap[0] &= ~FATTW4_WOWD0_FS_WOCATIONS;
	status = -EIO;
	/* Ignowe bowken sewvews that wetuwn unwequested attws */
	if (unwikewy(wes == NUWW))
		goto out;
	dpwintk("%s: fswoot:\n", __func__);
	status = decode_pathname(xdw, &wes->fs_path);
	if (unwikewy(status != 0))
		goto out;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		goto out_eio;
	n = be32_to_cpup(p);
	fow (wes->nwocations = 0; wes->nwocations < n; wes->nwocations++) {
		u32 m;
		stwuct nfs4_fs_wocation *woc;

		if (wes->nwocations == NFS4_FS_WOCATIONS_MAXENTWIES)
			bweak;
		woc = &wes->wocations[wes->nwocations];
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			goto out_eio;
		m = be32_to_cpup(p);

		dpwintk("%s: sewvews:\n", __func__);
		fow (woc->nsewvews = 0; woc->nsewvews < m; woc->nsewvews++) {
			stwuct nfs4_stwing *sewvew;

			if (woc->nsewvews == NFS4_FS_WOCATION_MAXSEWVEWS) {
				unsigned int i;
				dpwintk("%s: using fiwst %u of %u sewvews "
					"wetuwned fow wocation %u\n",
						__func__,
						NFS4_FS_WOCATION_MAXSEWVEWS,
						m, wes->nwocations);
				fow (i = woc->nsewvews; i < m; i++) {
					unsigned int wen;
					chaw *data;
					status = decode_opaque_inwine(xdw, &wen, &data);
					if (unwikewy(status != 0))
						goto out_eio;
				}
				bweak;
			}
			sewvew = &woc->sewvews[woc->nsewvews];
			status = decode_opaque_inwine(xdw, &sewvew->wen, &sewvew->data);
			if (unwikewy(status != 0))
				goto out_eio;
			dpwintk("%s ", sewvew->data);
		}
		status = decode_pathname(xdw, &woc->wootpath);
		if (unwikewy(status != 0))
			goto out_eio;
	}
	if (wes->nwocations != 0)
		status = NFS_ATTW_FATTW_V4_WOCATIONS;
out:
	dpwintk("%s: fs_wocations done, ewwow = %d\n", __func__, status);
	wetuwn status;
out_eio:
	status = -EIO;
	goto out;
}

static int decode_attw_maxfiwesize(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_MAXFIWESIZE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_MAXFIWESIZE)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[0] &= ~FATTW4_WOWD0_MAXFIWESIZE;
	}
	dpwintk("%s: maxfiwesize=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_attw_maxwink(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *maxwink)
{
	__be32 *p;
	int status = 0;

	*maxwink = 1;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_MAXWINK - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_MAXWINK)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*maxwink = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_MAXWINK;
	}
	dpwintk("%s: maxwink=%u\n", __func__, *maxwink);
	wetuwn status;
}

static int decode_attw_maxname(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *maxname)
{
	__be32 *p;
	int status = 0;

	*maxname = 1024;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_MAXNAME - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_MAXNAME)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*maxname = be32_to_cpup(p);
		bitmap[0] &= ~FATTW4_WOWD0_MAXNAME;
	}
	dpwintk("%s: maxname=%u\n", __func__, *maxname);
	wetuwn status;
}

static int decode_attw_maxwead(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 1024;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_MAXWEAD - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_MAXWEAD)) {
		uint64_t maxwead;
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, &maxwead);
		if (maxwead > 0x7FFFFFFF)
			maxwead = 0x7FFFFFFF;
		*wes = (uint32_t)maxwead;
		bitmap[0] &= ~FATTW4_WOWD0_MAXWEAD;
	}
	dpwintk("%s: maxwead=%wu\n", __func__, (unsigned wong)*wes);
	wetuwn status;
}

static int decode_attw_maxwwite(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 1024;
	if (unwikewy(bitmap[0] & (FATTW4_WOWD0_MAXWWITE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[0] & FATTW4_WOWD0_MAXWWITE)) {
		uint64_t maxwwite;
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, &maxwwite);
		if (maxwwite > 0x7FFFFFFF)
			maxwwite = 0x7FFFFFFF;
		*wes = (uint32_t)maxwwite;
		bitmap[0] &= ~FATTW4_WOWD0_MAXWWITE;
	}
	dpwintk("%s: maxwwite=%wu\n", __func__, (unsigned wong)*wes);
	wetuwn status;
}

static int decode_attw_mode(stwuct xdw_stweam *xdw, uint32_t *bitmap, umode_t *mode)
{
	uint32_t tmp;
	__be32 *p;
	int wet = 0;

	*mode = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_MODE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_MODE)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		tmp = be32_to_cpup(p);
		*mode = tmp & ~S_IFMT;
		bitmap[1] &= ~FATTW4_WOWD1_MODE;
		wet = NFS_ATTW_FATTW_MODE;
	}
	dpwintk("%s: fiwe mode=0%o\n", __func__, (unsigned int)*mode);
	wetuwn wet;
}

static int decode_attw_nwink(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint32_t *nwink)
{
	__be32 *p;
	int wet = 0;

	*nwink = 1;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_NUMWINKS - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_NUMWINKS)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*nwink = be32_to_cpup(p);
		bitmap[1] &= ~FATTW4_WOWD1_NUMWINKS;
		wet = NFS_ATTW_FATTW_NWINK;
	}
	dpwintk("%s: nwink=%u\n", __func__, (unsigned int)*nwink);
	wetuwn wet;
}

static ssize_t decode_nfs4_stwing(stwuct xdw_stweam *xdw,
		stwuct nfs4_stwing *name, gfp_t gfp_fwags)
{
	ssize_t wet;

	wet = xdw_stweam_decode_stwing_dup(xdw, &name->data,
			XDW_MAX_NETOBJ, gfp_fwags);
	name->wen = 0;
	if (wet > 0)
		name->wen = wet;
	wetuwn wet;
}

static int decode_attw_ownew(stwuct xdw_stweam *xdw, uint32_t *bitmap,
		const stwuct nfs_sewvew *sewvew, kuid_t *uid,
		stwuct nfs4_stwing *ownew_name)
{
	ssize_t wen;
	chaw *p;

	*uid = make_kuid(&init_usew_ns, -2);
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_OWNEW - 1U)))
		wetuwn -EIO;
	if (!(bitmap[1] & FATTW4_WOWD1_OWNEW))
		wetuwn 0;
	bitmap[1] &= ~FATTW4_WOWD1_OWNEW;

	if (ownew_name != NUWW) {
		wen = decode_nfs4_stwing(xdw, ownew_name, GFP_NOIO);
		if (wen <= 0)
			goto out;
		dpwintk("%s: name=%s\n", __func__, ownew_name->data);
		wetuwn NFS_ATTW_FATTW_OWNEW_NAME;
	} ewse {
		wen = xdw_stweam_decode_opaque_inwine(xdw, (void **)&p,
				XDW_MAX_NETOBJ);
		if (wen <= 0 || nfs_map_name_to_uid(sewvew, p, wen, uid) != 0)
			goto out;
		dpwintk("%s: uid=%d\n", __func__, (int)fwom_kuid(&init_usew_ns, *uid));
		wetuwn NFS_ATTW_FATTW_OWNEW;
	}
out:
	if (wen == -EBADMSG)
		wetuwn -EIO;
	wetuwn 0;
}

static int decode_attw_gwoup(stwuct xdw_stweam *xdw, uint32_t *bitmap,
		const stwuct nfs_sewvew *sewvew, kgid_t *gid,
		stwuct nfs4_stwing *gwoup_name)
{
	ssize_t wen;
	chaw *p;

	*gid = make_kgid(&init_usew_ns, -2);
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_OWNEW_GWOUP - 1U)))
		wetuwn -EIO;
	if (!(bitmap[1] & FATTW4_WOWD1_OWNEW_GWOUP))
		wetuwn 0;
	bitmap[1] &= ~FATTW4_WOWD1_OWNEW_GWOUP;

	if (gwoup_name != NUWW) {
		wen = decode_nfs4_stwing(xdw, gwoup_name, GFP_NOIO);
		if (wen <= 0)
			goto out;
		dpwintk("%s: name=%s\n", __func__, gwoup_name->data);
		wetuwn NFS_ATTW_FATTW_GWOUP_NAME;
	} ewse {
		wen = xdw_stweam_decode_opaque_inwine(xdw, (void **)&p,
				XDW_MAX_NETOBJ);
		if (wen <= 0 || nfs_map_gwoup_to_gid(sewvew, p, wen, gid) != 0)
			goto out;
		dpwintk("%s: gid=%d\n", __func__, (int)fwom_kgid(&init_usew_ns, *gid));
		wetuwn NFS_ATTW_FATTW_GWOUP;
	}
out:
	if (wen == -EBADMSG)
		wetuwn -EIO;
	wetuwn 0;
}

static int decode_attw_wdev(stwuct xdw_stweam *xdw, uint32_t *bitmap, dev_t *wdev)
{
	uint32_t majow = 0, minow = 0;
	__be32 *p;
	int wet = 0;

	*wdev = MKDEV(0,0);
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_WAWDEV - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_WAWDEV)) {
		dev_t tmp;

		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		majow = be32_to_cpup(p++);
		minow = be32_to_cpup(p);
		tmp = MKDEV(majow, minow);
		if (MAJOW(tmp) == majow && MINOW(tmp) == minow)
			*wdev = tmp;
		bitmap[1] &= ~ FATTW4_WOWD1_WAWDEV;
		wet = NFS_ATTW_FATTW_WDEV;
	}
	dpwintk("%s: wdev=(0x%x:0x%x)\n", __func__, majow, minow);
	wetuwn wet;
}

static int decode_attw_space_avaiw(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_SPACE_AVAIW - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_SPACE_AVAIW)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[1] &= ~FATTW4_WOWD1_SPACE_AVAIW;
	}
	dpwintk("%s: space avaiw=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_attw_space_fwee(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_SPACE_FWEE - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_SPACE_FWEE)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[1] &= ~FATTW4_WOWD1_SPACE_FWEE;
	}
	dpwintk("%s: space fwee=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_attw_space_totaw(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *wes)
{
	__be32 *p;
	int status = 0;

	*wes = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_SPACE_TOTAW - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_SPACE_TOTAW)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
		bitmap[1] &= ~FATTW4_WOWD1_SPACE_TOTAW;
	}
	dpwintk("%s: space totaw=%Wu\n", __func__, (unsigned wong wong)*wes);
	wetuwn status;
}

static int decode_attw_space_used(stwuct xdw_stweam *xdw, uint32_t *bitmap, uint64_t *used)
{
	__be32 *p;
	int wet = 0;

	*used = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_SPACE_USED - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_SPACE_USED)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, used);
		bitmap[1] &= ~FATTW4_WOWD1_SPACE_USED;
		wet = NFS_ATTW_FATTW_SPACE_USED;
	}
	dpwintk("%s: space used=%Wu\n", __func__,
			(unsigned wong wong)*used);
	wetuwn wet;
}

static __be32 *
xdw_decode_nfstime4(__be32 *p, stwuct timespec64 *t)
{
	__u64 sec;

	p = xdw_decode_hypew(p, &sec);
	t-> tv_sec = sec;
	t->tv_nsec = be32_to_cpup(p++);
	wetuwn p;
}

static int decode_attw_time(stwuct xdw_stweam *xdw, stwuct timespec64 *time)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, nfstime4_maxsz << 2);
	if (unwikewy(!p))
		wetuwn -EIO;
	xdw_decode_nfstime4(p, time);
	wetuwn 0;
}

static int decode_attw_time_access(stwuct xdw_stweam *xdw, uint32_t *bitmap, stwuct timespec64 *time)
{
	int status = 0;

	time->tv_sec = 0;
	time->tv_nsec = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_TIME_ACCESS - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_TIME_ACCESS)) {
		status = decode_attw_time(xdw, time);
		if (status == 0)
			status = NFS_ATTW_FATTW_ATIME;
		bitmap[1] &= ~FATTW4_WOWD1_TIME_ACCESS;
	}
	dpwintk("%s: atime=%wwd\n", __func__, time->tv_sec);
	wetuwn status;
}

static int decode_attw_time_metadata(stwuct xdw_stweam *xdw, uint32_t *bitmap, stwuct timespec64 *time)
{
	int status = 0;

	time->tv_sec = 0;
	time->tv_nsec = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_TIME_METADATA - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_TIME_METADATA)) {
		status = decode_attw_time(xdw, time);
		if (status == 0)
			status = NFS_ATTW_FATTW_CTIME;
		bitmap[1] &= ~FATTW4_WOWD1_TIME_METADATA;
	}
	dpwintk("%s: ctime=%wwd\n", __func__, time->tv_sec);
	wetuwn status;
}

static int decode_attw_time_dewta(stwuct xdw_stweam *xdw, uint32_t *bitmap,
				  stwuct timespec64 *time)
{
	int status = 0;

	time->tv_sec = 0;
	time->tv_nsec = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_TIME_DEWTA - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_TIME_DEWTA)) {
		status = decode_attw_time(xdw, time);
		bitmap[1] &= ~FATTW4_WOWD1_TIME_DEWTA;
	}
	dpwintk("%s: time_dewta=%wwd %wd\n", __func__, time->tv_sec,
		time->tv_nsec);
	wetuwn status;
}

static int decode_attw_secuwity_wabew(stwuct xdw_stweam *xdw, uint32_t *bitmap,
					stwuct nfs4_wabew *wabew)
{
	uint32_t pi = 0;
	uint32_t wfs = 0;
	__u32 wen;
	__be32 *p;
	int status = 0;

	if (unwikewy(bitmap[2] & (FATTW4_WOWD2_SECUWITY_WABEW - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[2] & FATTW4_WOWD2_SECUWITY_WABEW)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		wfs = be32_to_cpup(p++);
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		pi = be32_to_cpup(p++);
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		wen = be32_to_cpup(p++);
		p = xdw_inwine_decode(xdw, wen);
		if (unwikewy(!p))
			wetuwn -EIO;
		bitmap[2] &= ~FATTW4_WOWD2_SECUWITY_WABEW;
		if (wen < NFS4_MAXWABEWWEN) {
			if (wabew && wabew->wen) {
				if (wabew->wen < wen)
					wetuwn -EWANGE;
				memcpy(wabew->wabew, p, wen);
				wabew->wen = wen;
				wabew->pi = pi;
				wabew->wfs = wfs;
				status = NFS_ATTW_FATTW_V4_SECUWITY_WABEW;
			}
		} ewse
			pwintk(KEWN_WAWNING "%s: wabew too wong (%u)!\n",
					__func__, wen);
		if (wabew && wabew->wabew)
			dpwintk("%s: wabew=%.*s, wen=%d, PI=%d, WFS=%d\n",
				__func__, wabew->wen, (chaw *)wabew->wabew,
				wabew->wen, wabew->pi, wabew->wfs);
	}
	wetuwn status;
}

static int decode_attw_time_modify(stwuct xdw_stweam *xdw, uint32_t *bitmap, stwuct timespec64 *time)
{
	int status = 0;

	time->tv_sec = 0;
	time->tv_nsec = 0;
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_TIME_MODIFY - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[1] & FATTW4_WOWD1_TIME_MODIFY)) {
		status = decode_attw_time(xdw, time);
		if (status == 0)
			status = NFS_ATTW_FATTW_MTIME;
		bitmap[1] &= ~FATTW4_WOWD1_TIME_MODIFY;
	}
	dpwintk("%s: mtime=%wwd\n", __func__, time->tv_sec);
	wetuwn status;
}

static int decode_attw_xattwsuppowt(stwuct xdw_stweam *xdw, uint32_t *bitmap,
				    uint32_t *wes)
{
	__be32 *p;

	*wes = 0;
	if (unwikewy(bitmap[2] & (FATTW4_WOWD2_XATTW_SUPPOWT - 1U)))
		wetuwn -EIO;
	if (wikewy(bitmap[2] & FATTW4_WOWD2_XATTW_SUPPOWT)) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[2] &= ~FATTW4_WOWD2_XATTW_SUPPOWT;
	}
	dpwintk("%s: XATTW suppowt=%s\n", __func__,
		*wes == 0 ? "fawse" : "twue");
	wetuwn 0;
}

static int vewify_attw_wen(stwuct xdw_stweam *xdw, unsigned int savep, uint32_t attwwen)
{
	unsigned int attwwowds = XDW_QUADWEN(attwwen);
	unsigned int nwowds = (xdw_stweam_pos(xdw) - savep) >> 2;

	if (unwikewy(attwwowds != nwowds)) {
		dpwintk("%s: sewvew wetuwned incowwect attwibute wength: "
			"%u %c %u\n",
				__func__,
				attwwowds << 2,
				(attwwowds < nwowds) ? '<' : '>',
				nwowds << 2);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int decode_change_info(stwuct xdw_stweam *xdw, stwuct nfs4_change_info *cinfo)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 20);
	if (unwikewy(!p))
		wetuwn -EIO;
	cinfo->atomic = be32_to_cpup(p++);
	p = xdw_decode_hypew(p, &cinfo->befowe);
	xdw_decode_hypew(p, &cinfo->aftew);
	wetuwn 0;
}

static int decode_access(stwuct xdw_stweam *xdw, u32 *suppowted, u32 *access)
{
	__be32 *p;
	uint32_t supp, acc;
	int status;

	status = decode_op_hdw(xdw, OP_ACCESS);
	if (status)
		wetuwn status;
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	supp = be32_to_cpup(p++);
	acc = be32_to_cpup(p);
	*suppowted = supp;
	*access = acc;
	wetuwn 0;
}

static int decode_opaque_fixed(stwuct xdw_stweam *xdw, void *buf, size_t wen)
{
	ssize_t wet = xdw_stweam_decode_opaque_fixed(xdw, buf, wen);
	if (unwikewy(wet < 0))
		wetuwn -EIO;
	wetuwn 0;
}

static int decode_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	wetuwn decode_opaque_fixed(xdw, stateid, NFS4_STATEID_SIZE);
}

static int decode_open_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	stateid->type = NFS4_OPEN_STATEID_TYPE;
	wetuwn decode_stateid(xdw, stateid);
}

static int decode_wock_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	stateid->type = NFS4_WOCK_STATEID_TYPE;
	wetuwn decode_stateid(xdw, stateid);
}

static int decode_dewegation_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	stateid->type = NFS4_DEWEGATION_STATEID_TYPE;
	wetuwn decode_stateid(xdw, stateid);
}

static int decode_invawid_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	nfs4_stateid dummy;

	nfs4_stateid_copy(stateid, &invawid_stateid);
	wetuwn decode_stateid(xdw, &dummy);
}

static int decode_cwose(stwuct xdw_stweam *xdw, stwuct nfs_cwosewes *wes)
{
	int status;

	status = decode_op_hdw(xdw, OP_CWOSE);
	if (status != -EIO)
		nfs_incwement_open_seqid(status, wes->seqid);
	if (!status)
		status = decode_invawid_stateid(xdw, &wes->stateid);
	wetuwn status;
}

static int decode_vewifiew(stwuct xdw_stweam *xdw, void *vewifiew)
{
	wetuwn decode_opaque_fixed(xdw, vewifiew, NFS4_VEWIFIEW_SIZE);
}

static int decode_wwite_vewifiew(stwuct xdw_stweam *xdw, stwuct nfs_wwite_vewifiew *vewifiew)
{
	wetuwn decode_opaque_fixed(xdw, vewifiew->data, NFS4_VEWIFIEW_SIZE);
}

static int decode_commit(stwuct xdw_stweam *xdw, stwuct nfs_commitwes *wes)
{
	stwuct nfs_wwitevewf *vewf = wes->vewf;
	int status;

	status = decode_op_hdw(xdw, OP_COMMIT);
	if (!status)
		status = decode_wwite_vewifiew(xdw, &vewf->vewifiew);
	if (!status)
		vewf->committed = NFS_FIWE_SYNC;
	wetuwn status;
}

static int decode_cweate(stwuct xdw_stweam *xdw, stwuct nfs4_change_info *cinfo)
{
	__be32 *p;
	uint32_t bmwen;
	int status;

	status = decode_op_hdw(xdw, OP_CWEATE);
	if (status)
		wetuwn status;
	if ((status = decode_change_info(xdw, cinfo)))
		wetuwn status;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	bmwen = be32_to_cpup(p);
	p = xdw_inwine_decode(xdw, bmwen << 2);
	if (wikewy(p))
		wetuwn 0;
	wetuwn -EIO;
}

static int decode_sewvew_caps(stwuct xdw_stweam *xdw, stwuct nfs4_sewvew_caps_wes *wes)
{
	unsigned int savep;
	uint32_t attwwen, bitmap[3] = {0};
	int status;

	if ((status = decode_op_hdw(xdw, OP_GETATTW)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_bitmap(xdw, bitmap)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_wength(xdw, &attwwen, &savep)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_suppowted(xdw, bitmap, wes->attw_bitmask)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_fh_expiwe_type(xdw, bitmap,
						 &wes->fh_expiwe_type)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_wink_suppowt(xdw, bitmap, &wes->has_winks)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_symwink_suppowt(xdw, bitmap, &wes->has_symwinks)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_acwsuppowt(xdw, bitmap, &wes->acw_bitmask)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_case_insensitive(xdw, bitmap, &wes->case_insensitive)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_case_pwesewving(xdw, bitmap, &wes->case_pwesewving)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_excwcweat_suppowted(xdw, bitmap,
				wes->excwcweat_bitmask)) != 0)
		goto xdw_ewwow;
	status = vewify_attw_wen(xdw, savep, attwwen);
xdw_ewwow:
	dpwintk("%s: xdw wetuwned %d!\n", __func__, -status);
	wetuwn status;
}

static int decode_statfs(stwuct xdw_stweam *xdw, stwuct nfs_fsstat *fsstat)
{
	unsigned int savep;
	uint32_t attwwen, bitmap[3] = {0};
	int status;

	if ((status = decode_op_hdw(xdw, OP_GETATTW)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_bitmap(xdw, bitmap)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_wength(xdw, &attwwen, &savep)) != 0)
		goto xdw_ewwow;

	if ((status = decode_attw_fiwes_avaiw(xdw, bitmap, &fsstat->afiwes)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_fiwes_fwee(xdw, bitmap, &fsstat->ffiwes)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_fiwes_totaw(xdw, bitmap, &fsstat->tfiwes)) != 0)
		goto xdw_ewwow;

	status = -EIO;
	if (unwikewy(bitmap[0]))
		goto xdw_ewwow;

	if ((status = decode_attw_space_avaiw(xdw, bitmap, &fsstat->abytes)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_space_fwee(xdw, bitmap, &fsstat->fbytes)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_space_totaw(xdw, bitmap, &fsstat->tbytes)) != 0)
		goto xdw_ewwow;

	status = vewify_attw_wen(xdw, savep, attwwen);
xdw_ewwow:
	dpwintk("%s: xdw wetuwned %d!\n", __func__, -status);
	wetuwn status;
}

static int decode_pathconf(stwuct xdw_stweam *xdw, stwuct nfs_pathconf *pathconf)
{
	unsigned int savep;
	uint32_t attwwen, bitmap[3] = {0};
	int status;

	if ((status = decode_op_hdw(xdw, OP_GETATTW)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_bitmap(xdw, bitmap)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_wength(xdw, &attwwen, &savep)) != 0)
		goto xdw_ewwow;

	if ((status = decode_attw_maxwink(xdw, bitmap, &pathconf->max_wink)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_maxname(xdw, bitmap, &pathconf->max_namewen)) != 0)
		goto xdw_ewwow;

	status = vewify_attw_wen(xdw, savep, attwwen);
xdw_ewwow:
	dpwintk("%s: xdw wetuwned %d!\n", __func__, -status);
	wetuwn status;
}

static int decode_thweshowd_hint(stwuct xdw_stweam *xdw,
				  uint32_t *bitmap,
				  uint64_t *wes,
				  uint32_t hint_bit)
{
	__be32 *p;

	*wes = 0;
	if (wikewy(bitmap[0] & hint_bit)) {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
		xdw_decode_hypew(p, wes);
	}
	wetuwn 0;
}

static int decode_fiwst_thweshowd_item4(stwuct xdw_stweam *xdw,
					stwuct nfs4_thweshowd *wes)
{
	__be32 *p;
	unsigned int savep;
	uint32_t bitmap[3] = {0,}, attwwen;
	int status;

	/* wayout type */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->w_type = be32_to_cpup(p);

	/* thi_hintset bitmap */
	status = decode_attw_bitmap(xdw, bitmap);
	if (status < 0)
		goto xdw_ewwow;

	/* thi_hintwist wength */
	status = decode_attw_wength(xdw, &attwwen, &savep);
	if (status < 0)
		goto xdw_ewwow;
	/* thi_hintwist */
	status = decode_thweshowd_hint(xdw, bitmap, &wes->wd_sz, THWESHOWD_WD);
	if (status < 0)
		goto xdw_ewwow;
	status = decode_thweshowd_hint(xdw, bitmap, &wes->ww_sz, THWESHOWD_WW);
	if (status < 0)
		goto xdw_ewwow;
	status = decode_thweshowd_hint(xdw, bitmap, &wes->wd_io_sz,
				       THWESHOWD_WD_IO);
	if (status < 0)
		goto xdw_ewwow;
	status = decode_thweshowd_hint(xdw, bitmap, &wes->ww_io_sz,
				       THWESHOWD_WW_IO);
	if (status < 0)
		goto xdw_ewwow;

	status = vewify_attw_wen(xdw, savep, attwwen);
	wes->bm = bitmap[0];

	dpwintk("%s bm=0x%x wd_sz=%wwu ww_sz=%wwu wd_io=%wwu ww_io=%wwu\n",
		 __func__, wes->bm, wes->wd_sz, wes->ww_sz, wes->wd_io_sz,
		wes->ww_io_sz);
xdw_ewwow:
	dpwintk("%s wet=%d!\n", __func__, status);
	wetuwn status;
}

/*
 * Thweshowds on pNFS diwect I/O vws MDS I/O
 */
static int decode_attw_mdsthweshowd(stwuct xdw_stweam *xdw,
				    uint32_t *bitmap,
				    stwuct nfs4_thweshowd *wes)
{
	__be32 *p;
	int status = 0;
	uint32_t num;

	if (unwikewy(bitmap[2] & (FATTW4_WOWD2_MDSTHWESHOWD - 1U)))
		wetuwn -EIO;
	if (bitmap[2] & FATTW4_WOWD2_MDSTHWESHOWD) {
		/* Did the sewvew wetuwn an unwequested attwibute? */
		if (unwikewy(wes == NUWW))
			wetuwn -EWEMOTEIO;
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		num = be32_to_cpup(p);
		if (num == 0)
			wetuwn 0;
		if (num > 1)
			pwintk(KEWN_INFO "%s: Wawning: Muwtipwe pNFS wayout "
				"dwivews pew fiwesystem not suppowted\n",
				__func__);

		status = decode_fiwst_thweshowd_item4(xdw, wes);
		bitmap[2] &= ~FATTW4_WOWD2_MDSTHWESHOWD;
	}
	wetuwn status;
}

static int decode_getfattw_attws(stwuct xdw_stweam *xdw, uint32_t *bitmap,
		stwuct nfs_fattw *fattw, stwuct nfs_fh *fh,
		stwuct nfs4_fs_wocations *fs_woc, const stwuct nfs_sewvew *sewvew)
{
	int status;
	umode_t fmode = 0;
	uint32_t type;
	int32_t eww;

	status = decode_attw_type(xdw, bitmap, &type);
	if (status < 0)
		goto xdw_ewwow;
	fattw->mode = 0;
	if (status != 0) {
		fattw->mode |= nfs_type2fmt[type];
		fattw->vawid |= status;
	}

	status = decode_attw_change(xdw, bitmap, &fattw->change_attw);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_size(xdw, bitmap, &fattw->size);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_fsid(xdw, bitmap, &fattw->fsid);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	eww = 0;
	status = decode_attw_ewwow(xdw, bitmap, &eww);
	if (status < 0)
		goto xdw_ewwow;

	status = decode_attw_fiwehandwe(xdw, bitmap, fh);
	if (status < 0)
		goto xdw_ewwow;

	status = decode_attw_fiweid(xdw, bitmap, &fattw->fiweid);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_fs_wocations(xdw, bitmap, fs_woc);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = -EIO;
	if (unwikewy(bitmap[0]))
		goto xdw_ewwow;

	status = decode_attw_mode(xdw, bitmap, &fmode);
	if (status < 0)
		goto xdw_ewwow;
	if (status != 0) {
		fattw->mode |= fmode;
		fattw->vawid |= status;
	}

	status = decode_attw_nwink(xdw, bitmap, &fattw->nwink);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_ownew(xdw, bitmap, sewvew, &fattw->uid, fattw->ownew_name);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_gwoup(xdw, bitmap, sewvew, &fattw->gid, fattw->gwoup_name);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_wdev(xdw, bitmap, &fattw->wdev);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_space_used(xdw, bitmap, &fattw->du.nfs3.used);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_time_access(xdw, bitmap, &fattw->atime);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_time_metadata(xdw, bitmap, &fattw->ctime);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_time_modify(xdw, bitmap, &fattw->mtime);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = decode_attw_mounted_on_fiweid(xdw, bitmap, &fattw->mounted_on_fiweid);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

	status = -EIO;
	if (unwikewy(bitmap[1]))
		goto xdw_ewwow;

	status = decode_attw_mdsthweshowd(xdw, bitmap, fattw->mdsthweshowd);
	if (status < 0)
		goto xdw_ewwow;

	status = decode_attw_secuwity_wabew(xdw, bitmap, fattw->wabew);
	if (status < 0)
		goto xdw_ewwow;
	fattw->vawid |= status;

xdw_ewwow:
	dpwintk("%s: xdw wetuwned %d\n", __func__, -status);
	wetuwn status;
}

static int decode_getfattw_genewic(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw,
		stwuct nfs_fh *fh, stwuct nfs4_fs_wocations *fs_woc,
		const stwuct nfs_sewvew *sewvew)
{
	unsigned int savep;
	uint32_t attwwen,
		 bitmap[3] = {0};
	int status;

	status = decode_op_hdw(xdw, OP_GETATTW);
	if (status < 0)
		goto xdw_ewwow;

	status = decode_attw_bitmap(xdw, bitmap);
	if (status < 0)
		goto xdw_ewwow;

	status = decode_attw_wength(xdw, &attwwen, &savep);
	if (status < 0)
		goto xdw_ewwow;

	status = decode_getfattw_attws(xdw, bitmap, fattw, fh, fs_woc, sewvew);
	if (status < 0)
		goto xdw_ewwow;

	status = vewify_attw_wen(xdw, savep, attwwen);
xdw_ewwow:
	dpwintk("%s: xdw wetuwned %d\n", __func__, -status);
	wetuwn status;
}

static int decode_getfattw(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw,
		const stwuct nfs_sewvew *sewvew)
{
	wetuwn decode_getfattw_genewic(xdw, fattw, NUWW, NUWW, sewvew);
}

/*
 * Decode potentiawwy muwtipwe wayout types.
 */
static int decode_pnfs_wayout_types(stwuct xdw_stweam *xdw,
				    stwuct nfs_fsinfo *fsinfo)
{
	__be32 *p;
	uint32_t i;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	fsinfo->nwayouttypes = be32_to_cpup(p);

	/* pNFS is not suppowted by the undewwying fiwe system */
	if (fsinfo->nwayouttypes == 0)
		wetuwn 0;

	/* Decode and set fiwst wayout type, move xdw->p past unused types */
	p = xdw_inwine_decode(xdw, fsinfo->nwayouttypes * 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	/* If we get too many, then just cap it at the max */
	if (fsinfo->nwayouttypes > NFS_MAX_WAYOUT_TYPES) {
		pwintk(KEWN_INFO "NFS: %s: Wawning: Too many (%u) pNFS wayout types\n",
			__func__, fsinfo->nwayouttypes);
		fsinfo->nwayouttypes = NFS_MAX_WAYOUT_TYPES;
	}

	fow(i = 0; i < fsinfo->nwayouttypes; ++i)
		fsinfo->wayouttype[i] = be32_to_cpup(p++);
	wetuwn 0;
}

/*
 * The type of fiwe system expowted.
 * Note we must ensuwe that wayouttype is set in any non-ewwow case.
 */
static int decode_attw_pnfstype(stwuct xdw_stweam *xdw, uint32_t *bitmap,
				stwuct nfs_fsinfo *fsinfo)
{
	int status = 0;

	dpwintk("%s: bitmap is %x\n", __func__, bitmap[1]);
	if (unwikewy(bitmap[1] & (FATTW4_WOWD1_FS_WAYOUT_TYPES - 1U)))
		wetuwn -EIO;
	if (bitmap[1] & FATTW4_WOWD1_FS_WAYOUT_TYPES) {
		status = decode_pnfs_wayout_types(xdw, fsinfo);
		bitmap[1] &= ~FATTW4_WOWD1_FS_WAYOUT_TYPES;
	}
	wetuwn status;
}

/*
 * The pwefewed bwock size fow wayout diwected io
 */
static int decode_attw_wayout_bwksize(stwuct xdw_stweam *xdw, uint32_t *bitmap,
				      uint32_t *wes)
{
	__be32 *p;

	dpwintk("%s: bitmap is %x\n", __func__, bitmap[2]);
	*wes = 0;
	if (bitmap[2] & FATTW4_WOWD2_WAYOUT_BWKSIZE) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[2] &= ~FATTW4_WOWD2_WAYOUT_BWKSIZE;
	}
	wetuwn 0;
}

/*
 * The gwanuwawity of a CWONE opewation.
 */
static int decode_attw_cwone_bwksize(stwuct xdw_stweam *xdw, uint32_t *bitmap,
				     uint32_t *wes)
{
	__be32 *p;

	dpwintk("%s: bitmap is %x\n", __func__, bitmap[2]);
	*wes = 0;
	if (bitmap[2] & FATTW4_WOWD2_CWONE_BWKSIZE) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		*wes = be32_to_cpup(p);
		bitmap[2] &= ~FATTW4_WOWD2_CWONE_BWKSIZE;
	}
	wetuwn 0;
}

static int decode_attw_change_attw_type(stwuct xdw_stweam *xdw,
					uint32_t *bitmap,
					enum nfs4_change_attw_type *wes)
{
	u32 tmp = NFS4_CHANGE_TYPE_IS_UNDEFINED;

	dpwintk("%s: bitmap is %x\n", __func__, bitmap[2]);
	if (bitmap[2] & FATTW4_WOWD2_CHANGE_ATTW_TYPE) {
		if (xdw_stweam_decode_u32(xdw, &tmp))
			wetuwn -EIO;
		bitmap[2] &= ~FATTW4_WOWD2_CHANGE_ATTW_TYPE;
	}

	switch(tmp) {
	case NFS4_CHANGE_TYPE_IS_MONOTONIC_INCW:
	case NFS4_CHANGE_TYPE_IS_VEWSION_COUNTEW:
	case NFS4_CHANGE_TYPE_IS_VEWSION_COUNTEW_NOPNFS:
	case NFS4_CHANGE_TYPE_IS_TIME_METADATA:
		*wes = tmp;
		bweak;
	defauwt:
		*wes = NFS4_CHANGE_TYPE_IS_UNDEFINED;
	}
	wetuwn 0;
}

static int decode_fsinfo(stwuct xdw_stweam *xdw, stwuct nfs_fsinfo *fsinfo)
{
	unsigned int savep;
	uint32_t attwwen, bitmap[3];
	int status;

	if ((status = decode_op_hdw(xdw, OP_GETATTW)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_bitmap(xdw, bitmap)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_wength(xdw, &attwwen, &savep)) != 0)
		goto xdw_ewwow;

	fsinfo->wtmuwt = fsinfo->wtmuwt = 512;	/* ??? */

	if ((status = decode_attw_wease_time(xdw, bitmap, &fsinfo->wease_time)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_maxfiwesize(xdw, bitmap, &fsinfo->maxfiwesize)) != 0)
		goto xdw_ewwow;
	if ((status = decode_attw_maxwead(xdw, bitmap, &fsinfo->wtmax)) != 0)
		goto xdw_ewwow;
	fsinfo->wtpwef = fsinfo->dtpwef = fsinfo->wtmax;
	if ((status = decode_attw_maxwwite(xdw, bitmap, &fsinfo->wtmax)) != 0)
		goto xdw_ewwow;
	fsinfo->wtpwef = fsinfo->wtmax;

	status = -EIO;
	if (unwikewy(bitmap[0]))
		goto xdw_ewwow;

	status = decode_attw_time_dewta(xdw, bitmap, &fsinfo->time_dewta);
	if (status != 0)
		goto xdw_ewwow;
	status = decode_attw_pnfstype(xdw, bitmap, fsinfo);
	if (status != 0)
		goto xdw_ewwow;

	status = -EIO;
	if (unwikewy(bitmap[1]))
		goto xdw_ewwow;

	status = decode_attw_wayout_bwksize(xdw, bitmap, &fsinfo->bwksize);
	if (status)
		goto xdw_ewwow;
	status = decode_attw_cwone_bwksize(xdw, bitmap, &fsinfo->cwone_bwksize);
	if (status)
		goto xdw_ewwow;

	status = decode_attw_change_attw_type(xdw, bitmap,
					      &fsinfo->change_attw_type);
	if (status)
		goto xdw_ewwow;

	status = decode_attw_xattwsuppowt(xdw, bitmap,
					  &fsinfo->xattw_suppowt);
	if (status)
		goto xdw_ewwow;

	status = vewify_attw_wen(xdw, savep, attwwen);
xdw_ewwow:
	dpwintk("%s: xdw wetuwned %d!\n", __func__, -status);
	wetuwn status;
}

static int decode_getfh(stwuct xdw_stweam *xdw, stwuct nfs_fh *fh)
{
	__be32 *p;
	uint32_t wen;
	int status;

	/* Zewo handwe fiwst to awwow compawisons */
	memset(fh, 0, sizeof(*fh));

	status = decode_op_hdw(xdw, OP_GETFH);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wen = be32_to_cpup(p);
	if (wen > NFS4_FHSIZE || wen == 0) {
		twace_nfs4_xdw_bad_fiwehandwe(xdw, OP_GETFH, NFS4EWW_BADHANDWE);
		wetuwn -EWEMOTEIO;
	}
	fh->size = wen;
	p = xdw_inwine_decode(xdw, wen);
	if (unwikewy(!p))
		wetuwn -EIO;
	memcpy(fh->data, p, wen);
	wetuwn 0;
}

static int decode_wink(stwuct xdw_stweam *xdw, stwuct nfs4_change_info *cinfo)
{
	int status;

	status = decode_op_hdw(xdw, OP_WINK);
	if (status)
		wetuwn status;
	wetuwn decode_change_info(xdw, cinfo);
}

/*
 * We cweate the ownew, so we know a pwopew ownew.id wength is 4.
 */
static int decode_wock_denied (stwuct xdw_stweam *xdw, stwuct fiwe_wock *fw)
{
	uint64_t offset, wength, cwientid;
	__be32 *p;
	uint32_t namewen, type;

	p = xdw_inwine_decode(xdw, 32); /* wead 32 bytes */
	if (unwikewy(!p))
		wetuwn -EIO;
	p = xdw_decode_hypew(p, &offset); /* wead 2 8-byte wong wowds */
	p = xdw_decode_hypew(p, &wength);
	type = be32_to_cpup(p++); /* 4 byte wead */
	if (fw != NUWW) { /* manipuwate fiwe wock */
		fw->fw_stawt = (woff_t)offset;
		fw->fw_end = fw->fw_stawt + (woff_t)wength - 1;
		if (wength == ~(uint64_t)0)
			fw->fw_end = OFFSET_MAX;
		fw->fw_type = F_WWWCK;
		if (type & 1)
			fw->fw_type = F_WDWCK;
		fw->fw_pid = 0;
	}
	p = xdw_decode_hypew(p, &cwientid); /* wead 8 bytes */
	namewen = be32_to_cpup(p); /* wead 4 bytes */  /* have wead aww 32 bytes now */
	p = xdw_inwine_decode(xdw, namewen); /* vawiabwe size fiewd */
	if (wikewy(!p))
		wetuwn -EIO;
	wetuwn -NFS4EWW_DENIED;
}

static int decode_wock(stwuct xdw_stweam *xdw, stwuct nfs_wock_wes *wes)
{
	int status;

	status = decode_op_hdw(xdw, OP_WOCK);
	if (status == -EIO)
		goto out;
	if (status == 0) {
		status = decode_wock_stateid(xdw, &wes->stateid);
		if (unwikewy(status))
			goto out;
	} ewse if (status == -NFS4EWW_DENIED)
		status = decode_wock_denied(xdw, NUWW);
	if (wes->open_seqid != NUWW)
		nfs_incwement_open_seqid(status, wes->open_seqid);
	nfs_incwement_wock_seqid(status, wes->wock_seqid);
out:
	wetuwn status;
}

static int decode_wockt(stwuct xdw_stweam *xdw, stwuct nfs_wockt_wes *wes)
{
	int status;
	status = decode_op_hdw(xdw, OP_WOCKT);
	if (status == -NFS4EWW_DENIED)
		wetuwn decode_wock_denied(xdw, wes->denied);
	wetuwn status;
}

static int decode_wocku(stwuct xdw_stweam *xdw, stwuct nfs_wocku_wes *wes)
{
	int status;

	status = decode_op_hdw(xdw, OP_WOCKU);
	if (status != -EIO)
		nfs_incwement_wock_seqid(status, wes->seqid);
	if (status == 0)
		status = decode_wock_stateid(xdw, &wes->stateid);
	wetuwn status;
}

static int decode_wewease_wockownew(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WEWEASE_WOCKOWNEW);
}

static int decode_wookup(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WOOKUP);
}

static int decode_wookupp(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WOOKUPP);
}

/* This is too sick! */
static int decode_space_wimit(stwuct xdw_stweam *xdw,
		unsigned wong *pagemod_wimit)
{
	__be32 *p;
	uint32_t wimit_type, nbwocks, bwocksize;
	u64 maxsize = 0;

	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(!p))
		wetuwn -EIO;
	wimit_type = be32_to_cpup(p++);
	switch (wimit_type) {
	case NFS4_WIMIT_SIZE:
		xdw_decode_hypew(p, &maxsize);
		bweak;
	case NFS4_WIMIT_BWOCKS:
		nbwocks = be32_to_cpup(p++);
		bwocksize = be32_to_cpup(p);
		maxsize = (uint64_t)nbwocks * (uint64_t)bwocksize;
	}
	maxsize >>= PAGE_SHIFT;
	*pagemod_wimit = min_t(u64, maxsize, UWONG_MAX);
	wetuwn 0;
}

static int decode_ww_dewegation(stwuct xdw_stweam *xdw,
		uint32_t dewegation_type,
		stwuct nfs_openwes *wes)
{
	__be32 *p;
	int status;

	status = decode_dewegation_stateid(xdw, &wes->dewegation);
	if (unwikewy(status))
		wetuwn status;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->do_wecaww = be32_to_cpup(p);

	switch (dewegation_type) {
	case NFS4_OPEN_DEWEGATE_WEAD:
		wes->dewegation_type = FMODE_WEAD;
		bweak;
	case NFS4_OPEN_DEWEGATE_WWITE:
		wes->dewegation_type = FMODE_WWITE|FMODE_WEAD;
		if (decode_space_wimit(xdw, &wes->pagemod_wimit) < 0)
				wetuwn -EIO;
	}
	wetuwn decode_ace(xdw, NUWW);
}

static int decode_no_dewegation(stwuct xdw_stweam *xdw, stwuct nfs_openwes *wes)
{
	__be32 *p;
	uint32_t why_no_dewegation;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	why_no_dewegation = be32_to_cpup(p);
	switch (why_no_dewegation) {
		case WND4_CONTENTION:
		case WND4_WESOUWCE:
			xdw_inwine_decode(xdw, 4);
			/* Ignowe fow now */
	}
	wetuwn 0;
}

static int decode_dewegation(stwuct xdw_stweam *xdw, stwuct nfs_openwes *wes)
{
	__be32 *p;
	uint32_t dewegation_type;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	dewegation_type = be32_to_cpup(p);
	wes->dewegation_type = 0;
	switch (dewegation_type) {
	case NFS4_OPEN_DEWEGATE_NONE:
		wetuwn 0;
	case NFS4_OPEN_DEWEGATE_WEAD:
	case NFS4_OPEN_DEWEGATE_WWITE:
		wetuwn decode_ww_dewegation(xdw, dewegation_type, wes);
	case NFS4_OPEN_DEWEGATE_NONE_EXT:
		wetuwn decode_no_dewegation(xdw, wes);
	}
	wetuwn -EIO;
}

static int decode_open(stwuct xdw_stweam *xdw, stwuct nfs_openwes *wes)
{
	__be32 *p;
	uint32_t savewowds, bmwen, i;
	int status;

	if (!__decode_op_hdw(xdw, OP_OPEN, &status))
		wetuwn status;
	nfs_incwement_open_seqid(status, wes->seqid);
	if (status)
		wetuwn status;
	status = decode_open_stateid(xdw, &wes->stateid);
	if (unwikewy(status))
		wetuwn status;

	decode_change_info(xdw, &wes->cinfo);

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->wfwags = be32_to_cpup(p++);
	bmwen = be32_to_cpup(p);
	if (bmwen > 10)
		goto xdw_ewwow;

	p = xdw_inwine_decode(xdw, bmwen << 2);
	if (unwikewy(!p))
		wetuwn -EIO;
	savewowds = min_t(uint32_t, bmwen, NFS4_BITMAP_SIZE);
	fow (i = 0; i < savewowds; ++i)
		wes->attwset[i] = be32_to_cpup(p++);
	fow (; i < NFS4_BITMAP_SIZE; i++)
		wes->attwset[i] = 0;

	wetuwn decode_dewegation(xdw, wes);
xdw_ewwow:
	dpwintk("%s: Bitmap too wawge! Wength = %u\n", __func__, bmwen);
	wetuwn -EIO;
}

static int decode_open_confiwm(stwuct xdw_stweam *xdw, stwuct nfs_open_confiwmwes *wes)
{
	int status;

	status = decode_op_hdw(xdw, OP_OPEN_CONFIWM);
	if (status != -EIO)
		nfs_incwement_open_seqid(status, wes->seqid);
	if (!status)
		status = decode_open_stateid(xdw, &wes->stateid);
	wetuwn status;
}

static int decode_open_downgwade(stwuct xdw_stweam *xdw, stwuct nfs_cwosewes *wes)
{
	int status;

	status = decode_op_hdw(xdw, OP_OPEN_DOWNGWADE);
	if (status != -EIO)
		nfs_incwement_open_seqid(status, wes->seqid);
	if (!status)
		status = decode_open_stateid(xdw, &wes->stateid);
	wetuwn status;
}

static int decode_putfh(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_PUTFH);
}

static int decode_putwootfh(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_PUTWOOTFH);
}

static int decode_wead(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq,
		       stwuct nfs_pgio_wes *wes)
{
	__be32 *p;
	uint32_t count, eof, wecvd;
	int status;

	status = decode_op_hdw(xdw, OP_WEAD);
	if (status)
		wetuwn status;
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	eof = be32_to_cpup(p++);
	count = be32_to_cpup(p);
	wecvd = xdw_wead_pages(xdw, count);
	if (count > wecvd) {
		dpwintk("NFS: sewvew cheating in wead wepwy: "
				"count %u > wecvd %u\n", count, wecvd);
		count = wecvd;
		eof = 0;
	}
	wes->eof = eof;
	wes->count = count;
	wetuwn 0;
}

static int decode_weaddiw(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq, stwuct nfs4_weaddiw_wes *weaddiw)
{
	int		status;
	__be32		vewf[2];

	status = decode_op_hdw(xdw, OP_WEADDIW);
	if (!status)
		status = decode_vewifiew(xdw, weaddiw->vewifiew.data);
	if (unwikewy(status))
		wetuwn status;
	memcpy(vewf, weaddiw->vewifiew.data, sizeof(vewf));
	dpwintk("%s: vewifiew = %08x:%08x\n",
			__func__, vewf[0], vewf[1]);
	wetuwn xdw_wead_pages(xdw, xdw->buf->page_wen);
}

static int decode_weadwink(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq)
{
	stwuct xdw_buf *wcvbuf = &weq->wq_wcv_buf;
	u32 wen, wecvd;
	__be32 *p;
	int status;

	status = decode_op_hdw(xdw, OP_WEADWINK);
	if (status)
		wetuwn status;

	/* Convewt wength of symwink */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wen = be32_to_cpup(p);
	if (wen >= wcvbuf->page_wen || wen <= 0) {
		dpwintk("nfs: sewvew wetuwned giant symwink!\n");
		wetuwn -ENAMETOOWONG;
	}
	wecvd = xdw_wead_pages(xdw, wen);
	if (wecvd < wen) {
		dpwintk("NFS: sewvew cheating in weadwink wepwy: "
				"count %u > wecvd %u\n", wen, wecvd);
		wetuwn -EIO;
	}
	/*
	 * The XDW encode woutine has set things up so that
	 * the wink text wiww be copied diwectwy into the
	 * buffew.  We just have to do ovewfwow-checking,
	 * and nuww-tewminate the text (the VFS expects
	 * nuww-tewmination).
	 */
	xdw_tewminate_stwing(wcvbuf, wen);
	wetuwn 0;
}

static int decode_wemove(stwuct xdw_stweam *xdw, stwuct nfs4_change_info *cinfo)
{
	int status;

	status = decode_op_hdw(xdw, OP_WEMOVE);
	if (status)
		goto out;
	status = decode_change_info(xdw, cinfo);
out:
	wetuwn status;
}

static int decode_wename(stwuct xdw_stweam *xdw, stwuct nfs4_change_info *owd_cinfo,
	      stwuct nfs4_change_info *new_cinfo)
{
	int status;

	status = decode_op_hdw(xdw, OP_WENAME);
	if (status)
		goto out;
	if ((status = decode_change_info(xdw, owd_cinfo)))
		goto out;
	status = decode_change_info(xdw, new_cinfo);
out:
	wetuwn status;
}

static int decode_wenew(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WENEW);
}

static int
decode_westowefh(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WESTOWEFH);
}

static int decode_getacw(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq,
			 stwuct nfs_getacwwes *wes, enum nfs4_acw_type type)
{
	unsigned int savep;
	uint32_t attwwen,
		 bitmap[3] = {0};
	int status;

	wes->acw_wen = 0;
	if ((status = decode_op_hdw(xdw, OP_GETATTW)) != 0)
		goto out;

	xdw_entew_page(xdw, xdw->buf->page_wen);

	if ((status = decode_attw_bitmap(xdw, bitmap)) != 0)
		goto out;
	if ((status = decode_attw_wength(xdw, &attwwen, &savep)) != 0)
		goto out;

	switch (type) {
	defauwt:
		if (unwikewy(bitmap[0] & (FATTW4_WOWD0_ACW - 1U)))
			wetuwn -EIO;
		if (!(bitmap[0] & FATTW4_WOWD0_ACW))
			wetuwn -EOPNOTSUPP;
		bweak;
	case NFS4ACW_DACW:
		if (unwikewy(bitmap[0] || bitmap[1] & (FATTW4_WOWD1_DACW - 1U)))
			wetuwn -EIO;
		if (!(bitmap[1] & FATTW4_WOWD1_DACW))
			wetuwn -EOPNOTSUPP;
		bweak;
	case NFS4ACW_SACW:
		if (unwikewy(bitmap[0] || bitmap[1] & (FATTW4_WOWD1_SACW - 1U)))
			wetuwn -EIO;
		if (!(bitmap[1] & FATTW4_WOWD1_SACW))
			wetuwn -EOPNOTSUPP;
	}

	/* The bitmap (xdw wen + bitmaps) and the attw xdw wen wowds
	 * awe stowed with the acw data to handwe the pwobwem of
	 * vawiabwe wength bitmaps.*/
	wes->acw_data_offset = xdw_page_pos(xdw);
	wes->acw_wen = attwwen;

	/* Check fow weceive buffew ovewfwow */
	if (wes->acw_wen > xdw_stweam_wemaining(xdw) ||
	    wes->acw_wen + wes->acw_data_offset > xdw->buf->page_wen) {
		wes->acw_fwags |= NFS4_ACW_TWUNC;
		dpwintk("NFS: acw wepwy: attwwen %u > page_wen %zu\n",
			attwwen, xdw_stweam_wemaining(xdw));
	}
out:
	wetuwn status;
}

static int
decode_savefh(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_SAVEFH);
}

static int decode_setattw(stwuct xdw_stweam *xdw)
{
	int status;

	status = decode_op_hdw(xdw, OP_SETATTW);
	if (status)
		wetuwn status;
	if (decode_bitmap4(xdw, NUWW, 0) >= 0)
		wetuwn 0;
	wetuwn -EIO;
}

static int decode_setcwientid(stwuct xdw_stweam *xdw, stwuct nfs4_setcwientid_wes *wes)
{
	__be32 *p;
	uint32_t opnum;
	int32_t nfseww;

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	opnum = be32_to_cpup(p++);
	if (opnum != OP_SETCWIENTID) {
		dpwintk("nfs: decode_setcwientid: Sewvew wetuwned opewation"
			" %d\n", opnum);
		wetuwn -EIO;
	}
	nfseww = be32_to_cpup(p);
	if (nfseww == NFS_OK) {
		p = xdw_inwine_decode(xdw, 8 + NFS4_VEWIFIEW_SIZE);
		if (unwikewy(!p))
			wetuwn -EIO;
		p = xdw_decode_hypew(p, &wes->cwientid);
		memcpy(wes->confiwm.data, p, NFS4_VEWIFIEW_SIZE);
	} ewse if (nfseww == NFSEWW_CWID_INUSE) {
		uint32_t wen;

		/* skip netid stwing */
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		wen = be32_to_cpup(p);
		p = xdw_inwine_decode(xdw, wen);
		if (unwikewy(!p))
			wetuwn -EIO;

		/* skip uaddw stwing */
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		wen = be32_to_cpup(p);
		p = xdw_inwine_decode(xdw, wen);
		if (unwikewy(!p))
			wetuwn -EIO;
		wetuwn -NFSEWW_CWID_INUSE;
	} ewse
		wetuwn nfs4_stat_to_ewwno(nfseww);

	wetuwn 0;
}

static int decode_setcwientid_confiwm(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_SETCWIENTID_CONFIWM);
}

static int decode_wwite(stwuct xdw_stweam *xdw, stwuct nfs_pgio_wes *wes)
{
	__be32 *p;
	int status;

	status = decode_op_hdw(xdw, OP_WWITE);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->count = be32_to_cpup(p++);
	wes->vewf->committed = be32_to_cpup(p++);
	wetuwn decode_wwite_vewifiew(xdw, &wes->vewf->vewifiew);
}

static int decode_dewegwetuwn(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_DEWEGWETUWN);
}

static int decode_secinfo_gss(stwuct xdw_stweam *xdw,
			      stwuct nfs4_secinfo4 *fwavow)
{
	u32 oid_wen;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	oid_wen = be32_to_cpup(p);
	if (oid_wen > GSS_OID_MAX_WEN)
		wetuwn -EINVAW;

	p = xdw_inwine_decode(xdw, oid_wen);
	if (unwikewy(!p))
		wetuwn -EIO;
	memcpy(fwavow->fwavow_info.oid.data, p, oid_wen);
	fwavow->fwavow_info.oid.wen = oid_wen;

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	fwavow->fwavow_info.qop = be32_to_cpup(p++);
	fwavow->fwavow_info.sewvice = be32_to_cpup(p);

	wetuwn 0;
}

static int decode_secinfo_common(stwuct xdw_stweam *xdw, stwuct nfs4_secinfo_wes *wes)
{
	stwuct nfs4_secinfo4 *sec_fwavow;
	unsigned int i, num_fwavows;
	int status;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	wes->fwavows->num_fwavows = 0;
	num_fwavows = be32_to_cpup(p);

	fow (i = 0; i < num_fwavows; i++) {
		sec_fwavow = &wes->fwavows->fwavows[i];
		if ((chaw *)&sec_fwavow[1] - (chaw *)wes->fwavows > PAGE_SIZE)
			bweak;

		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;
		sec_fwavow->fwavow = be32_to_cpup(p);

		if (sec_fwavow->fwavow == WPC_AUTH_GSS) {
			status = decode_secinfo_gss(xdw, sec_fwavow);
			if (status)
				goto out;
		}
		wes->fwavows->num_fwavows++;
	}

	status = 0;
out:
	wetuwn status;
}

static int decode_secinfo(stwuct xdw_stweam *xdw, stwuct nfs4_secinfo_wes *wes)
{
	int status = decode_op_hdw(xdw, OP_SECINFO);
	if (status)
		wetuwn status;
	wetuwn decode_secinfo_common(xdw, wes);
}

#if defined(CONFIG_NFS_V4_1)
static int decode_secinfo_no_name(stwuct xdw_stweam *xdw, stwuct nfs4_secinfo_wes *wes)
{
	int status = decode_op_hdw(xdw, OP_SECINFO_NO_NAME);
	if (status)
		wetuwn status;
	wetuwn decode_secinfo_common(xdw, wes);
}

static int decode_op_map(stwuct xdw_stweam *xdw, stwuct nfs4_op_map *op_map)
{
	if (xdw_stweam_decode_uint32_awway(xdw, op_map->u.wowds,
					   AWWAY_SIZE(op_map->u.wowds)) < 0)
		wetuwn -EIO;
	wetuwn 0;
}

static int decode_exchange_id(stwuct xdw_stweam *xdw,
			      stwuct nfs41_exchange_id_wes *wes)
{
	__be32 *p;
	uint32_t dummy;
	chaw *dummy_stw;
	int status;
	uint32_t impw_id_count;

	status = decode_op_hdw(xdw, OP_EXCHANGE_ID);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	xdw_decode_hypew(p, &wes->cwientid);
	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->seqid = be32_to_cpup(p++);
	wes->fwags = be32_to_cpup(p++);

	wes->state_pwotect.how = be32_to_cpup(p);
	switch (wes->state_pwotect.how) {
	case SP4_NONE:
		bweak;
	case SP4_MACH_CWED:
		status = decode_op_map(xdw, &wes->state_pwotect.enfowce);
		if (status)
			wetuwn status;
		status = decode_op_map(xdw, &wes->state_pwotect.awwow);
		if (status)
			wetuwn status;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}

	/* sewvew_ownew4.so_minow_id */
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	p = xdw_decode_hypew(p, &wes->sewvew_ownew->minow_id);

	/* sewvew_ownew4.so_majow_id */
	status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
	if (unwikewy(status))
		wetuwn status;
	memcpy(wes->sewvew_ownew->majow_id, dummy_stw, dummy);
	wes->sewvew_ownew->majow_id_sz = dummy;

	/* sewvew_scope4 */
	status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
	if (unwikewy(status))
		wetuwn status;
	memcpy(wes->sewvew_scope->sewvew_scope, dummy_stw, dummy);
	wes->sewvew_scope->sewvew_scope_sz = dummy;

	/* Impwementation Id */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	impw_id_count = be32_to_cpup(p++);

	if (impw_id_count) {
		/* nii_domain */
		status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
		if (unwikewy(status))
			wetuwn status;
		memcpy(wes->impw_id->domain, dummy_stw, dummy);

		/* nii_name */
		status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
		if (unwikewy(status))
			wetuwn status;
		memcpy(wes->impw_id->name, dummy_stw, dummy);

		/* nii_date */
		p = xdw_inwine_decode(xdw, 12);
		if (unwikewy(!p))
			wetuwn -EIO;
		p = xdw_decode_hypew(p, &wes->impw_id->date.seconds);
		wes->impw_id->date.nseconds = be32_to_cpup(p);

		/* if thewe's mowe than one entwy, ignowe the west */
	}
	wetuwn 0;
}

static int decode_chan_attws(stwuct xdw_stweam *xdw,
			     stwuct nfs4_channew_attws *attws)
{
	__be32 *p;
	u32 nw_attws, vaw;

	p = xdw_inwine_decode(xdw, 28);
	if (unwikewy(!p))
		wetuwn -EIO;
	vaw = be32_to_cpup(p++);	/* headewpadsz */
	if (vaw)
		wetuwn -EINVAW;		/* no suppowt fow headew padding yet */
	attws->max_wqst_sz = be32_to_cpup(p++);
	attws->max_wesp_sz = be32_to_cpup(p++);
	attws->max_wesp_sz_cached = be32_to_cpup(p++);
	attws->max_ops = be32_to_cpup(p++);
	attws->max_weqs = be32_to_cpup(p++);
	nw_attws = be32_to_cpup(p);
	if (unwikewy(nw_attws > 1)) {
		pwintk(KEWN_WAWNING "NFS: %s: Invawid wdma channew attws "
			"count %u\n", __func__, nw_attws);
		wetuwn -EINVAW;
	}
	if (nw_attws == 1) {
		p = xdw_inwine_decode(xdw, 4); /* skip wdma_attws */
		if (unwikewy(!p))
			wetuwn -EIO;
	}
	wetuwn 0;
}

static int decode_sessionid(stwuct xdw_stweam *xdw, stwuct nfs4_sessionid *sid)
{
	wetuwn decode_opaque_fixed(xdw, sid->data, NFS4_MAX_SESSIONID_WEN);
}

static int decode_bind_conn_to_session(stwuct xdw_stweam *xdw,
				stwuct nfs41_bind_conn_to_session_wes *wes)
{
	__be32 *p;
	int status;

	status = decode_op_hdw(xdw, OP_BIND_CONN_TO_SESSION);
	if (!status)
		status = decode_sessionid(xdw, &wes->sessionid);
	if (unwikewy(status))
		wetuwn status;

	/* diw fwags, wdma mode boow */
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;

	wes->diw = be32_to_cpup(p++);
	if (wes->diw == 0 || wes->diw > NFS4_CDFS4_BOTH)
		wetuwn -EIO;
	if (be32_to_cpup(p) == 0)
		wes->use_conn_in_wdma_mode = fawse;
	ewse
		wes->use_conn_in_wdma_mode = twue;

	wetuwn 0;
}

static int decode_cweate_session(stwuct xdw_stweam *xdw,
				 stwuct nfs41_cweate_session_wes *wes)
{
	__be32 *p;
	int status;

	status = decode_op_hdw(xdw, OP_CWEATE_SESSION);
	if (!status)
		status = decode_sessionid(xdw, &wes->sessionid);
	if (unwikewy(status))
		wetuwn status;

	/* seqid, fwags */
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->seqid = be32_to_cpup(p++);
	wes->fwags = be32_to_cpup(p);

	/* Channew attwibutes */
	status = decode_chan_attws(xdw, &wes->fc_attws);
	if (!status)
		status = decode_chan_attws(xdw, &wes->bc_attws);
	wetuwn status;
}

static int decode_destwoy_session(stwuct xdw_stweam *xdw, void *dummy)
{
	wetuwn decode_op_hdw(xdw, OP_DESTWOY_SESSION);
}

static int decode_destwoy_cwientid(stwuct xdw_stweam *xdw, void *dummy)
{
	wetuwn decode_op_hdw(xdw, OP_DESTWOY_CWIENTID);
}

static int decode_wecwaim_compwete(stwuct xdw_stweam *xdw, void *dummy)
{
	wetuwn decode_op_hdw(xdw, OP_WECWAIM_COMPWETE);
}
#endif /* CONFIG_NFS_V4_1 */

static int decode_sequence(stwuct xdw_stweam *xdw,
			   stwuct nfs4_sequence_wes *wes,
			   stwuct wpc_wqst *wqstp)
{
#if defined(CONFIG_NFS_V4_1)
	stwuct nfs4_session *session;
	stwuct nfs4_sessionid id;
	u32 dummy;
	int status;
	__be32 *p;

	if (wes->sw_swot == NUWW)
		wetuwn 0;
	if (!wes->sw_swot->tabwe->session)
		wetuwn 0;

	status = decode_op_hdw(xdw, OP_SEQUENCE);
	if (!status)
		status = decode_sessionid(xdw, &id);
	if (unwikewy(status))
		goto out_eww;

	/*
	 * If the sewvew wetuwns diffewent vawues fow sessionID, swotID ow
	 * sequence numbew, the sewvew is wooney tunes.
	 */
	status = -EWEMOTEIO;
	session = wes->sw_swot->tabwe->session;

	if (memcmp(id.data, session->sess_id.data,
		   NFS4_MAX_SESSIONID_WEN)) {
		dpwintk("%s Invawid session id\n", __func__);
		goto out_eww;
	}

	p = xdw_inwine_decode(xdw, 20);
	if (unwikewy(!p))
		goto out_ovewfwow;

	/* seqid */
	dummy = be32_to_cpup(p++);
	if (dummy != wes->sw_swot->seq_nw) {
		dpwintk("%s Invawid sequence numbew\n", __func__);
		goto out_eww;
	}
	/* swot id */
	dummy = be32_to_cpup(p++);
	if (dummy != wes->sw_swot->swot_nw) {
		dpwintk("%s Invawid swot id\n", __func__);
		goto out_eww;
	}
	/* highest swot id */
	wes->sw_highest_swotid = be32_to_cpup(p++);
	/* tawget highest swot id */
	wes->sw_tawget_highest_swotid = be32_to_cpup(p++);
	/* wesuwt fwags */
	wes->sw_status_fwags = be32_to_cpup(p);
	status = 0;
out_eww:
	wes->sw_status = status;
	wetuwn status;
out_ovewfwow:
	status = -EIO;
	goto out_eww;
#ewse  /* CONFIG_NFS_V4_1 */
	wetuwn 0;
#endif /* CONFIG_NFS_V4_1 */
}

#if defined(CONFIG_NFS_V4_1)
static int decode_wayout_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	stateid->type = NFS4_WAYOUT_STATEID_TYPE;
	wetuwn decode_stateid(xdw, stateid);
}

static int decode_getdeviceinfo(stwuct xdw_stweam *xdw,
				stwuct nfs4_getdeviceinfo_wes *wes)
{
	stwuct pnfs_device *pdev = wes->pdev;
	__be32 *p;
	uint32_t wen, type;
	int status;

	status = decode_op_hdw(xdw, OP_GETDEVICEINFO);
	if (status) {
		if (status == -ETOOSMAWW) {
			p = xdw_inwine_decode(xdw, 4);
			if (unwikewy(!p))
				wetuwn -EIO;
			pdev->mincount = be32_to_cpup(p);
			dpwintk("%s: Min count too smaww. mincnt = %u\n",
				__func__, pdev->mincount);
		}
		wetuwn status;
	}

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	type = be32_to_cpup(p++);
	if (type != pdev->wayout_type) {
		dpwintk("%s: wayout mismatch weq: %u pdev: %u\n",
			__func__, pdev->wayout_type, type);
		wetuwn -EINVAW;
	}
	/*
	 * Get the wength of the opaque device_addw4. xdw_wead_pages pwaces
	 * the opaque device_addw4 in the xdw_buf->pages (pnfs_device->pages)
	 * and pwaces the wemaining xdw data in xdw_buf->taiw
	 */
	pdev->mincount = be32_to_cpup(p);
	if (xdw_wead_pages(xdw, pdev->mincount) != pdev->mincount)
		wetuwn -EIO;

	/* Pawse notification bitmap, vewifying that it is zewo. */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wen = be32_to_cpup(p);
	if (wen) {
		uint32_t i;

		p = xdw_inwine_decode(xdw, 4 * wen);
		if (unwikewy(!p))
			wetuwn -EIO;

		wes->notification = be32_to_cpup(p++);
		fow (i = 1; i < wen; i++) {
			if (be32_to_cpup(p++)) {
				dpwintk("%s: unsuppowted notification\n",
					__func__);
				wetuwn -EIO;
			}
		}
	}
	wetuwn 0;
}

static int decode_wayoutget(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq,
			    stwuct nfs4_wayoutget_wes *wes)
{
	__be32 *p;
	int status;
	u32 wayout_count;
	u32 wecvd;

	status = decode_op_hdw(xdw, OP_WAYOUTGET);
	if (status)
		goto out;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		goto out_ovewfwow;
	wes->wetuwn_on_cwose = be32_to_cpup(p);
	decode_wayout_stateid(xdw, &wes->stateid);
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		goto out_ovewfwow;
	wayout_count = be32_to_cpup(p);
	if (!wayout_count) {
		dpwintk("%s: sewvew wesponded with empty wayout awway\n",
			__func__);
		status = -EINVAW;
		goto out;
	}

	p = xdw_inwine_decode(xdw, 28);
	if (unwikewy(!p))
		goto out_ovewfwow;
	p = xdw_decode_hypew(p, &wes->wange.offset);
	p = xdw_decode_hypew(p, &wes->wange.wength);
	wes->wange.iomode = be32_to_cpup(p++);
	wes->type = be32_to_cpup(p++);
	wes->wayoutp->wen = be32_to_cpup(p);

	dpwintk("%s woff:%wu wwen:%wu wiomode:%d, wo_type:0x%x, wo.wen:%d\n",
		__func__,
		(unsigned wong)wes->wange.offset,
		(unsigned wong)wes->wange.wength,
		wes->wange.iomode,
		wes->type,
		wes->wayoutp->wen);

	wecvd = xdw_wead_pages(xdw, wes->wayoutp->wen);
	if (wes->wayoutp->wen > wecvd) {
		dpwintk("NFS: sewvew cheating in wayoutget wepwy: "
				"wayout wen %u > wecvd %u\n",
				wes->wayoutp->wen, wecvd);
		status = -EINVAW;
		goto out;
	}

	if (wayout_count > 1) {
		/* We onwy handwe a wength one awway at the moment.  Any
		 * fuwthew entwies awe just ignowed.  Note that this means
		 * the cwient may see a wesponse that is wess than the
		 * minimum it wequested.
		 */
		dpwintk("%s: sewvew wesponded with %d wayouts, dwopping taiw\n",
			__func__, wayout_count);
	}

out:
	wes->status = status;
	wetuwn status;
out_ovewfwow:
	status = -EIO;
	goto out;
}

static int decode_wayoutwetuwn(stwuct xdw_stweam *xdw,
			       stwuct nfs4_wayoutwetuwn_wes *wes)
{
	__be32 *p;
	int status;

	status = decode_op_hdw(xdw, OP_WAYOUTWETUWN);
	if (status)
		wetuwn status;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->wws_pwesent = be32_to_cpup(p);
	if (wes->wws_pwesent)
		status = decode_wayout_stateid(xdw, &wes->stateid);
	ewse
		nfs4_stateid_copy(&wes->stateid, &invawid_stateid);
	wetuwn status;
}

static int decode_wayoutcommit(stwuct xdw_stweam *xdw,
			       stwuct wpc_wqst *weq,
			       stwuct nfs4_wayoutcommit_wes *wes)
{
	__be32 *p;
	__u32 sizechanged;
	int status;

	status = decode_op_hdw(xdw, OP_WAYOUTCOMMIT);
	wes->status = status;
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	sizechanged = be32_to_cpup(p);

	if (sizechanged) {
		/* thwow away new size */
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			wetuwn -EIO;
	}
	wetuwn 0;
}

static int decode_test_stateid(stwuct xdw_stweam *xdw,
			       stwuct nfs41_test_stateid_wes *wes)
{
	__be32 *p;
	int status;
	int num_wes;

	status = decode_op_hdw(xdw, OP_TEST_STATEID);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	num_wes = be32_to_cpup(p++);
	if (num_wes != 1)
		wetuwn -EIO;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wes->status = be32_to_cpup(p++);

	wetuwn status;
}

static int decode_fwee_stateid(stwuct xdw_stweam *xdw,
			       stwuct nfs41_fwee_stateid_wes *wes)
{
	wes->status = decode_op_hdw(xdw, OP_FWEE_STATEID);
	wetuwn wes->status;
}
#ewse
static inwine
int decode_wayoutwetuwn(stwuct xdw_stweam *xdw,
			       stwuct nfs4_wayoutwetuwn_wes *wes)
{
	wetuwn 0;
}

static int decode_wayoutget(stwuct xdw_stweam *xdw, stwuct wpc_wqst *weq,
			    stwuct nfs4_wayoutget_wes *wes)
{
	wetuwn 0;
}

#endif /* CONFIG_NFS_V4_1 */

/*
 * END OF "GENEWIC" DECODE WOUTINES.
 */

/*
 * Decode OPEN_DOWNGWADE wesponse
 */
static int nfs4_xdw_dec_open_downgwade(stwuct wpc_wqst *wqstp,
				       stwuct xdw_stweam *xdw,
				       void *data)
{
	stwuct nfs_cwosewes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	if (wes->ww_wes) {
		status = decode_wayoutwetuwn(xdw, wes->ww_wes);
		wes->ww_wet = status;
		if (status)
			goto out;
	}
	status = decode_open_downgwade(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode ACCESS wesponse
 */
static int nfs4_xdw_dec_access(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs4_accesswes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status != 0)
		goto out;
	status = decode_access(xdw, &wes->suppowted, &wes->access);
	if (status != 0)
		goto out;
	if (wes->fattw)
		decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode WOOKUP wesponse
 */
static int nfs4_xdw_dec_wookup(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs4_wookup_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wookup(xdw);
	if (status)
		goto out;
	status = decode_getfh(xdw, wes->fh);
	if (status)
		goto out;
	status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode WOOKUPP wesponse
 */
static int nfs4_xdw_dec_wookupp(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
		void *data)
{
	stwuct nfs4_wookupp_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wookupp(xdw);
	if (status)
		goto out;
	status = decode_getfh(xdw, wes->fh);
	if (status)
		goto out;
	status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode WOOKUP_WOOT wesponse
 */
static int nfs4_xdw_dec_wookup_woot(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs4_wookup_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putwootfh(xdw);
	if (status)
		goto out;
	status = decode_getfh(xdw, wes->fh);
	if (status == 0)
		status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode WEMOVE wesponse
 */
static int nfs4_xdw_dec_wemove(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs_wemovewes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wemove(xdw, &wes->cinfo);
out:
	wetuwn status;
}

/*
 * Decode WENAME wesponse
 */
static int nfs4_xdw_dec_wename(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs_wenamewes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_savefh(xdw);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wename(xdw, &wes->owd_cinfo, &wes->new_cinfo);
out:
	wetuwn status;
}

/*
 * Decode WINK wesponse
 */
static int nfs4_xdw_dec_wink(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			     void *data)
{
	stwuct nfs4_wink_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_savefh(xdw);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wink(xdw, &wes->cinfo);
	if (status)
		goto out;
	/*
	 * Note owdew: OP_WINK weaves the diwectowy as the cuwwent
	 *             fiwehandwe.
	 */
	status = decode_westowefh(xdw);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode CWEATE wesponse
 */
static int nfs4_xdw_dec_cweate(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs4_cweate_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_cweate(xdw, &wes->diw_cinfo);
	if (status)
		goto out;
	status = decode_getfh(xdw, wes->fh);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode SYMWINK wesponse
 */
static int nfs4_xdw_dec_symwink(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
				void *wes)
{
	wetuwn nfs4_xdw_dec_cweate(wqstp, xdw, wes);
}

/*
 * Decode GETATTW wesponse
 */
static int nfs4_xdw_dec_getattw(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct nfs4_getattw_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Encode an SETACW wequest
 */
static void nfs4_xdw_enc_setacw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nfs_setacwawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_setacw(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Decode SETACW wesponse
 */
static int
nfs4_xdw_dec_setacw(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
		    void *data)
{
	stwuct nfs_setacwwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_setattw(xdw);
out:
	wetuwn status;
}

/*
 * Decode GETACW wesponse
 */
static int
nfs4_xdw_dec_getacw(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
		    void *data)
{
	stwuct nfs_getacwwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	if (wes->acw_scwatch != NUWW)
		xdw_set_scwatch_page(xdw, wes->acw_scwatch);
	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_getacw(xdw, wqstp, wes, wes->acw_type);

out:
	wetuwn status;
}

/*
 * Decode CWOSE wesponse
 */
static int nfs4_xdw_dec_cwose(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			      void *data)
{
	stwuct nfs_cwosewes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	if (wes->ww_wes) {
		status = decode_wayoutwetuwn(xdw, wes->ww_wes);
		wes->ww_wet = status;
		if (status)
			goto out;
	}
	if (wes->fattw != NUWW) {
		status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
		if (status != 0)
			goto out;
	}
	status = decode_cwose(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode OPEN wesponse
 */
static int nfs4_xdw_dec_open(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			     void *data)
{
	stwuct nfs_openwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_open(xdw, wes);
	if (status)
		goto out;
	status = decode_getfh(xdw, &wes->fh);
	if (status)
		goto out;
	if (wes->access_wequest)
		decode_access(xdw, &wes->access_suppowted, &wes->access_wesuwt);
	decode_getfattw(xdw, wes->f_attw, wes->sewvew);
	if (wes->wg_wes)
		decode_wayoutget(xdw, wqstp, wes->wg_wes);
out:
	wetuwn status;
}

/*
 * Decode OPEN_CONFIWM wesponse
 */
static int nfs4_xdw_dec_open_confiwm(stwuct wpc_wqst *wqstp,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs_open_confiwmwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_open_confiwm(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode OPEN wesponse
 */
static int nfs4_xdw_dec_open_noattw(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs_openwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_open(xdw, wes);
	if (status)
		goto out;
	if (wes->access_wequest)
		decode_access(xdw, &wes->access_suppowted, &wes->access_wesuwt);
	decode_getfattw(xdw, wes->f_attw, wes->sewvew);
	if (wes->wg_wes)
		decode_wayoutget(xdw, wqstp, wes->wg_wes);
out:
	wetuwn status;
}

/*
 * Decode SETATTW wesponse
 */
static int nfs4_xdw_dec_setattw(stwuct wpc_wqst *wqstp,
				stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct nfs_setattwwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_setattw(xdw);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode WOCK wesponse
 */
static int nfs4_xdw_dec_wock(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			     void *data)
{
	stwuct nfs_wock_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wock(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WOCKT wesponse
 */
static int nfs4_xdw_dec_wockt(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			      void *data)
{
	stwuct nfs_wockt_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wockt(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WOCKU wesponse
 */
static int nfs4_xdw_dec_wocku(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			      void *data)
{
	stwuct nfs_wocku_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wocku(xdw, wes);
out:
	wetuwn status;
}

static int nfs4_xdw_dec_wewease_wockownew(stwuct wpc_wqst *wqstp,
					  stwuct xdw_stweam *xdw, void *dummy)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_wewease_wockownew(xdw);
	wetuwn status;
}

/*
 * Decode WEADWINK wesponse
 */
static int nfs4_xdw_dec_weadwink(stwuct wpc_wqst *wqstp,
				 stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct nfs4_weadwink_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_weadwink(xdw, wqstp);
out:
	wetuwn status;
}

/*
 * Decode WEADDIW wesponse
 */
static int nfs4_xdw_dec_weaddiw(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct nfs4_weaddiw_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_weaddiw(xdw, wqstp, wes);
out:
	wetuwn status;
}

/*
 * Decode Wead wesponse
 */
static int nfs4_xdw_dec_wead(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			     void *data)
{
	stwuct nfs_pgio_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	wes->op_status = hdw.status;
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wead(xdw, wqstp, wes);
	if (!status)
		status = wes->count;
out:
	wetuwn status;
}

/*
 * Decode WWITE wesponse
 */
static int nfs4_xdw_dec_wwite(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			      void *data)
{
	stwuct nfs_pgio_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	wes->op_status = hdw.status;
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wwite(xdw, wes);
	if (status)
		goto out;
	if (wes->fattw)
		decode_getfattw(xdw, wes->fattw, wes->sewvew);
	if (!status)
		status = wes->count;
out:
	wetuwn status;
}

/*
 * Decode COMMIT wesponse
 */
static int nfs4_xdw_dec_commit(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs_commitwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	wes->op_status = hdw.status;
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_commit(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode FSINFO wesponse
 */
static int nfs4_xdw_dec_fsinfo(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs4_fsinfo_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (!status)
		status = decode_putfh(xdw);
	if (!status)
		status = decode_fsinfo(xdw, wes->fsinfo);
	wetuwn status;
}

/*
 * Decode PATHCONF wesponse
 */
static int nfs4_xdw_dec_pathconf(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct nfs4_pathconf_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (!status)
		status = decode_putfh(xdw);
	if (!status)
		status = decode_pathconf(xdw, wes->pathconf);
	wetuwn status;
}

/*
 * Decode STATFS wesponse
 */
static int nfs4_xdw_dec_statfs(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nfs4_statfs_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (!status)
		status = decode_putfh(xdw);
	if (!status)
		status = decode_statfs(xdw, wes->fsstat);
	wetuwn status;
}

/*
 * Decode GETATTW_BITMAP wesponse
 */
static int nfs4_xdw_dec_sewvew_caps(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs4_sewvew_caps_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_sewvew_caps(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WENEW wesponse
 */
static int nfs4_xdw_dec_wenew(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			      void *__unused)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_wenew(xdw);
	wetuwn status;
}

/*
 * Decode SETCWIENTID wesponse
 */
static int nfs4_xdw_dec_setcwientid(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs4_setcwientid_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_setcwientid(xdw, wes);
	wetuwn status;
}

/*
 * Decode SETCWIENTID_CONFIWM wesponse
 */
static int nfs4_xdw_dec_setcwientid_confiwm(stwuct wpc_wqst *weq,
					    stwuct xdw_stweam *xdw,
					    void *data)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_setcwientid_confiwm(xdw);
	wetuwn status;
}

/*
 * Decode DEWEGWETUWN wesponse
 */
static int nfs4_xdw_dec_dewegwetuwn(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs4_dewegwetuwnwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status != 0)
		goto out;
	if (wes->ww_wes) {
		status = decode_wayoutwetuwn(xdw, wes->ww_wes);
		wes->ww_wet = status;
		if (status)
			goto out;
	}
	if (wes->fattw) {
		status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
		if (status != 0)
			goto out;
	}
	status = decode_dewegwetuwn(xdw);
out:
	wetuwn status;
}

/*
 * Decode FS_WOCATIONS wesponse
 */
static int nfs4_xdw_dec_fs_wocations(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs4_fs_wocations_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	if (wes->migwation) {
		xdw_entew_page(xdw, PAGE_SIZE);
		status = decode_getfattw_genewic(xdw,
					wes->fs_wocations->fattw,
					 NUWW, wes->fs_wocations,
					 wes->fs_wocations->sewvew);
		if (status)
			goto out;
		if (wes->wenew)
			status = decode_wenew(xdw);
	} ewse {
		status = decode_wookup(xdw);
		if (status)
			goto out;
		xdw_entew_page(xdw, PAGE_SIZE);
		status = decode_getfattw_genewic(xdw,
					wes->fs_wocations->fattw,
					 NUWW, wes->fs_wocations,
					 wes->fs_wocations->sewvew);
	}
out:
	wetuwn status;
}

/*
 * Decode SECINFO wesponse
 */
static int nfs4_xdw_dec_secinfo(stwuct wpc_wqst *wqstp,
				stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct nfs4_secinfo_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_secinfo(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode FSID_PWESENT wesponse
 */
static int nfs4_xdw_dec_fsid_pwesent(stwuct wpc_wqst *wqstp,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs4_fsid_pwesent_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_getfh(xdw, wes->fh);
	if (status)
		goto out;
	if (wes->wenew)
		status = decode_wenew(xdw);
out:
	wetuwn status;
}

#if defined(CONFIG_NFS_V4_1)
/*
 * Decode BIND_CONN_TO_SESSION wesponse
 */
static int nfs4_xdw_dec_bind_conn_to_session(stwuct wpc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *wes)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_bind_conn_to_session(xdw, wes);
	wetuwn status;
}

/*
 * Decode EXCHANGE_ID wesponse
 */
static int nfs4_xdw_dec_exchange_id(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *wes)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_exchange_id(xdw, wes);
	wetuwn status;
}

/*
 * Decode CWEATE_SESSION wesponse
 */
static int nfs4_xdw_dec_cweate_session(stwuct wpc_wqst *wqstp,
				       stwuct xdw_stweam *xdw,
				       void *wes)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_cweate_session(xdw, wes);
	wetuwn status;
}

/*
 * Decode DESTWOY_SESSION wesponse
 */
static int nfs4_xdw_dec_destwoy_session(stwuct wpc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *wes)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_destwoy_session(xdw, wes);
	wetuwn status;
}

/*
 * Decode DESTWOY_CWIENTID wesponse
 */
static int nfs4_xdw_dec_destwoy_cwientid(stwuct wpc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *wes)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_destwoy_cwientid(xdw, wes);
	wetuwn status;
}

/*
 * Decode SEQUENCE wesponse
 */
static int nfs4_xdw_dec_sequence(stwuct wpc_wqst *wqstp,
				 stwuct xdw_stweam *xdw,
				 void *wes)
{
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_sequence(xdw, wes, wqstp);
	wetuwn status;
}

#endif

/*
 * Decode GET_WEASE_TIME wesponse
 */
static int nfs4_xdw_dec_get_wease_time(stwuct wpc_wqst *wqstp,
				       stwuct xdw_stweam *xdw,
				       void *data)
{
	stwuct nfs4_get_wease_time_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_sequence(xdw, &wes->ww_seq_wes, wqstp);
	if (!status)
		status = decode_putwootfh(xdw);
	if (!status)
		status = decode_fsinfo(xdw, wes->ww_fsinfo);
	wetuwn status;
}

#ifdef CONFIG_NFS_V4_1

/*
 * Decode WECWAIM_COMPWETE wesponse
 */
static int nfs4_xdw_dec_wecwaim_compwete(stwuct wpc_wqst *wqstp,
					 stwuct xdw_stweam *xdw,
					 void *data)
{
	stwuct nfs41_wecwaim_compwete_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (!status)
		status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (!status)
		status = decode_wecwaim_compwete(xdw, NUWW);
	wetuwn status;
}

/*
 * Decode GETDEVINFO wesponse
 */
static int nfs4_xdw_dec_getdeviceinfo(stwuct wpc_wqst *wqstp,
				      stwuct xdw_stweam *xdw,
				      void *data)
{
	stwuct nfs4_getdeviceinfo_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status != 0)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status != 0)
		goto out;
	status = decode_getdeviceinfo(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WAYOUTGET wesponse
 */
static int nfs4_xdw_dec_wayoutget(stwuct wpc_wqst *wqstp,
				  stwuct xdw_stweam *xdw,
				  void *data)
{
	stwuct nfs4_wayoutget_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wayoutget(xdw, wqstp, wes);
out:
	wetuwn status;
}

/*
 * Decode WAYOUTWETUWN wesponse
 */
static int nfs4_xdw_dec_wayoutwetuwn(stwuct wpc_wqst *wqstp,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs4_wayoutwetuwn_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wayoutwetuwn(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WAYOUTCOMMIT wesponse
 */
static int nfs4_xdw_dec_wayoutcommit(stwuct wpc_wqst *wqstp,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs4_wayoutcommit_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wayoutcommit(xdw, wqstp, wes);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode SECINFO_NO_NAME wesponse
 */
static int nfs4_xdw_dec_secinfo_no_name(stwuct wpc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *data)
{
	stwuct nfs4_secinfo_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putwootfh(xdw);
	if (status)
		goto out;
	status = decode_secinfo_no_name(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode TEST_STATEID wesponse
 */
static int nfs4_xdw_dec_test_stateid(stwuct wpc_wqst *wqstp,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs41_test_stateid_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_test_stateid(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode FWEE_STATEID wesponse
 */
static int nfs4_xdw_dec_fwee_stateid(stwuct wpc_wqst *wqstp,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs41_fwee_stateid_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_fwee_stateid(xdw, wes);
out:
	wetuwn status;
}
#endif /* CONFIG_NFS_V4_1 */

/**
 * nfs4_decode_diwent - Decode a singwe NFSv4 diwectowy entwy stowed in
 *                      the wocaw page cache.
 * @xdw: XDW stweam whewe entwy wesides
 * @entwy: buffew to fiww in with entwy data
 * @pwus: boowean indicating whethew this shouwd be a weaddiwpwus entwy
 *
 * Wetuwns zewo if successfuw, othewwise a negative ewwno vawue is
 * wetuwned.
 *
 * This function is not invoked duwing WEADDIW wepwy decoding, but
 * wathew whenevew an appwication invokes the getdents(2) system caww
 * on a diwectowy awweady in ouw cache.
 */
int nfs4_decode_diwent(stwuct xdw_stweam *xdw, stwuct nfs_entwy *entwy,
		       boow pwus)
{
	unsigned int savep;
	uint32_t bitmap[3] = {0};
	uint32_t wen;
	uint64_t new_cookie;
	__be32 *p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EAGAIN;
	if (*p == xdw_zewo) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EAGAIN;
		if (*p == xdw_zewo)
			wetuwn -EAGAIN;
		entwy->eof = 1;
		wetuwn -EBADCOOKIE;
	}

	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(!p))
		wetuwn -EAGAIN;
	p = xdw_decode_hypew(p, &new_cookie);
	entwy->wen = be32_to_cpup(p);

	p = xdw_inwine_decode(xdw, entwy->wen);
	if (unwikewy(!p))
		wetuwn -EAGAIN;
	entwy->name = (const chaw *) p;

	/*
	 * In case the sewvew doesn't wetuwn an inode numbew,
	 * we fake one hewe.  (We don't use inode numbew 0,
	 * since gwibc seems to choke on it...)
	 */
	entwy->ino = 1;
	entwy->fattw->vawid = 0;

	if (decode_attw_bitmap(xdw, bitmap) < 0)
		wetuwn -EAGAIN;

	if (decode_attw_wength(xdw, &wen, &savep) < 0)
		wetuwn -EAGAIN;

	if (decode_getfattw_attws(xdw, bitmap, entwy->fattw, entwy->fh,
			NUWW, entwy->sewvew) < 0)
		wetuwn -EAGAIN;
	if (entwy->fattw->vawid & NFS_ATTW_FATTW_MOUNTED_ON_FIWEID)
		entwy->ino = entwy->fattw->mounted_on_fiweid;
	ewse if (entwy->fattw->vawid & NFS_ATTW_FATTW_FIWEID)
		entwy->ino = entwy->fattw->fiweid;

	entwy->d_type = DT_UNKNOWN;
	if (entwy->fattw->vawid & NFS_ATTW_FATTW_TYPE)
		entwy->d_type = nfs_umode_to_dtype(entwy->fattw->mode);

	entwy->cookie = new_cookie;

	wetuwn 0;
}

/*
 * We need to twanswate between nfs status wetuwn vawues and
 * the wocaw ewwno vawues which may not be the same.
 */
static stwuct {
	int stat;
	int ewwno;
} nfs_ewwtbw[] = {
	{ NFS4_OK,		0		},
	{ NFS4EWW_PEWM,		-EPEWM		},
	{ NFS4EWW_NOENT,	-ENOENT		},
	{ NFS4EWW_IO,		-ewwno_NFSEWW_IO},
	{ NFS4EWW_NXIO,		-ENXIO		},
	{ NFS4EWW_ACCESS,	-EACCES		},
	{ NFS4EWW_EXIST,	-EEXIST		},
	{ NFS4EWW_XDEV,		-EXDEV		},
	{ NFS4EWW_NOTDIW,	-ENOTDIW	},
	{ NFS4EWW_ISDIW,	-EISDIW		},
	{ NFS4EWW_INVAW,	-EINVAW		},
	{ NFS4EWW_FBIG,		-EFBIG		},
	{ NFS4EWW_NOSPC,	-ENOSPC		},
	{ NFS4EWW_WOFS,		-EWOFS		},
	{ NFS4EWW_MWINK,	-EMWINK		},
	{ NFS4EWW_NAMETOOWONG,	-ENAMETOOWONG	},
	{ NFS4EWW_NOTEMPTY,	-ENOTEMPTY	},
	{ NFS4EWW_DQUOT,	-EDQUOT		},
	{ NFS4EWW_STAWE,	-ESTAWE		},
	{ NFS4EWW_BADHANDWE,	-EBADHANDWE	},
	{ NFS4EWW_BAD_COOKIE,	-EBADCOOKIE	},
	{ NFS4EWW_NOTSUPP,	-ENOTSUPP	},
	{ NFS4EWW_TOOSMAWW,	-ETOOSMAWW	},
	{ NFS4EWW_SEWVEWFAUWT,	-EWEMOTEIO	},
	{ NFS4EWW_BADTYPE,	-EBADTYPE	},
	{ NFS4EWW_WOCKED,	-EAGAIN		},
	{ NFS4EWW_SYMWINK,	-EWOOP		},
	{ NFS4EWW_OP_IWWEGAW,	-EOPNOTSUPP	},
	{ NFS4EWW_DEADWOCK,	-EDEADWK	},
	{ NFS4EWW_NOXATTW,	-ENODATA	},
	{ NFS4EWW_XATTW2BIG,	-E2BIG		},
	{ -1,			-EIO		}
};

/*
 * Convewt an NFS ewwow code to a wocaw one.
 * This one is used jointwy by NFSv2 and NFSv3.
 */
static int
nfs4_stat_to_ewwno(int stat)
{
	int i;
	fow (i = 0; nfs_ewwtbw[i].stat != -1; i++) {
		if (nfs_ewwtbw[i].stat == stat)
			wetuwn nfs_ewwtbw[i].ewwno;
	}
	if (stat <= 10000 || stat > 10100) {
		/* The sewvew is wooney tunes. */
		wetuwn -EWEMOTEIO;
	}
	/* If we cannot twanswate the ewwow, the wecovewy woutines shouwd
	 * handwe it.
	 * Note: wemaining NFSv4 ewwow codes have vawues > 10000, so shouwd
	 * not confwict with native Winux ewwow codes.
	 */
	wetuwn -stat;
}

#ifdef CONFIG_NFS_V4_2
#incwude "nfs42xdw.c"
#endif /* CONFIG_NFS_V4_2 */

#define PWOC(pwoc, awgtype, westype)				\
[NFSPWOC4_CWNT_##pwoc] = {					\
	.p_pwoc   = NFSPWOC4_COMPOUND,				\
	.p_encode = nfs4_xdw_##awgtype,				\
	.p_decode = nfs4_xdw_##westype,				\
	.p_awgwen = NFS4_##awgtype##_sz,			\
	.p_wepwen = NFS4_##westype##_sz,			\
	.p_statidx = NFSPWOC4_CWNT_##pwoc,			\
	.p_name   = #pwoc,					\
}

#define STUB(pwoc)		\
[NFSPWOC4_CWNT_##pwoc] = {	\
	.p_name = #pwoc,	\
}

#if defined(CONFIG_NFS_V4_1)
#define PWOC41(pwoc, awgtype, westype)				\
	PWOC(pwoc, awgtype, westype)
#ewse
#define PWOC41(pwoc, awgtype, westype)				\
	STUB(pwoc)
#endif

#if defined(CONFIG_NFS_V4_2)
#define PWOC42(pwoc, awgtype, westype)				\
	PWOC(pwoc, awgtype, westype)
#ewse
#define PWOC42(pwoc, awgtype, westype)				\
	STUB(pwoc)
#endif

const stwuct wpc_pwocinfo nfs4_pwoceduwes[] = {
	PWOC(WEAD,		enc_wead,		dec_wead),
	PWOC(WWITE,		enc_wwite,		dec_wwite),
	PWOC(COMMIT,		enc_commit,		dec_commit),
	PWOC(OPEN,		enc_open,		dec_open),
	PWOC(OPEN_CONFIWM,	enc_open_confiwm,	dec_open_confiwm),
	PWOC(OPEN_NOATTW,	enc_open_noattw,	dec_open_noattw),
	PWOC(OPEN_DOWNGWADE,	enc_open_downgwade,	dec_open_downgwade),
	PWOC(CWOSE,		enc_cwose,		dec_cwose),
	PWOC(SETATTW,		enc_setattw,		dec_setattw),
	PWOC(FSINFO,		enc_fsinfo,		dec_fsinfo),
	PWOC(WENEW,		enc_wenew,		dec_wenew),
	PWOC(SETCWIENTID,	enc_setcwientid,	dec_setcwientid),
	PWOC(SETCWIENTID_CONFIWM, enc_setcwientid_confiwm, dec_setcwientid_confiwm),
	PWOC(WOCK,		enc_wock,		dec_wock),
	PWOC(WOCKT,		enc_wockt,		dec_wockt),
	PWOC(WOCKU,		enc_wocku,		dec_wocku),
	PWOC(ACCESS,		enc_access,		dec_access),
	PWOC(GETATTW,		enc_getattw,		dec_getattw),
	PWOC(WOOKUP,		enc_wookup,		dec_wookup),
	PWOC(WOOKUP_WOOT,	enc_wookup_woot,	dec_wookup_woot),
	PWOC(WEMOVE,		enc_wemove,		dec_wemove),
	PWOC(WENAME,		enc_wename,		dec_wename),
	PWOC(WINK,		enc_wink,		dec_wink),
	PWOC(SYMWINK,		enc_symwink,		dec_symwink),
	PWOC(CWEATE,		enc_cweate,		dec_cweate),
	PWOC(PATHCONF,		enc_pathconf,		dec_pathconf),
	PWOC(STATFS,		enc_statfs,		dec_statfs),
	PWOC(WEADWINK,		enc_weadwink,		dec_weadwink),
	PWOC(WEADDIW,		enc_weaddiw,		dec_weaddiw),
	PWOC(SEWVEW_CAPS,	enc_sewvew_caps,	dec_sewvew_caps),
	PWOC(DEWEGWETUWN,	enc_dewegwetuwn,	dec_dewegwetuwn),
	PWOC(GETACW,		enc_getacw,		dec_getacw),
	PWOC(SETACW,		enc_setacw,		dec_setacw),
	PWOC(FS_WOCATIONS,	enc_fs_wocations,	dec_fs_wocations),
	PWOC(WEWEASE_WOCKOWNEW,	enc_wewease_wockownew,	dec_wewease_wockownew),
	PWOC(SECINFO,		enc_secinfo,		dec_secinfo),
	PWOC(FSID_PWESENT,	enc_fsid_pwesent,	dec_fsid_pwesent),
	PWOC41(EXCHANGE_ID,	enc_exchange_id,	dec_exchange_id),
	PWOC41(CWEATE_SESSION,	enc_cweate_session,	dec_cweate_session),
	PWOC41(DESTWOY_SESSION,	enc_destwoy_session,	dec_destwoy_session),
	PWOC41(SEQUENCE,	enc_sequence,		dec_sequence),
	PWOC(GET_WEASE_TIME,	enc_get_wease_time,	dec_get_wease_time),
	PWOC41(WECWAIM_COMPWETE,enc_wecwaim_compwete,	dec_wecwaim_compwete),
	PWOC41(GETDEVICEINFO,	enc_getdeviceinfo,	dec_getdeviceinfo),
	PWOC41(WAYOUTGET,	enc_wayoutget,		dec_wayoutget),
	PWOC41(WAYOUTCOMMIT,	enc_wayoutcommit,	dec_wayoutcommit),
	PWOC41(WAYOUTWETUWN,	enc_wayoutwetuwn,	dec_wayoutwetuwn),
	PWOC41(SECINFO_NO_NAME,	enc_secinfo_no_name,	dec_secinfo_no_name),
	PWOC41(TEST_STATEID,	enc_test_stateid,	dec_test_stateid),
	PWOC41(FWEE_STATEID,	enc_fwee_stateid,	dec_fwee_stateid),
	STUB(GETDEVICEWIST),
	PWOC41(BIND_CONN_TO_SESSION,
			enc_bind_conn_to_session, dec_bind_conn_to_session),
	PWOC41(DESTWOY_CWIENTID,enc_destwoy_cwientid,	dec_destwoy_cwientid),
	PWOC42(SEEK,		enc_seek,		dec_seek),
	PWOC42(AWWOCATE,	enc_awwocate,		dec_awwocate),
	PWOC42(DEAWWOCATE,	enc_deawwocate,		dec_deawwocate),
	PWOC42(WAYOUTSTATS,	enc_wayoutstats,	dec_wayoutstats),
	PWOC42(CWONE,		enc_cwone,		dec_cwone),
	PWOC42(COPY,		enc_copy,		dec_copy),
	PWOC42(OFFWOAD_CANCEW,	enc_offwoad_cancew,	dec_offwoad_cancew),
	PWOC42(COPY_NOTIFY,	enc_copy_notify,	dec_copy_notify),
	PWOC(WOOKUPP,		enc_wookupp,		dec_wookupp),
	PWOC42(WAYOUTEWWOW,	enc_wayoutewwow,	dec_wayoutewwow),
	PWOC42(GETXATTW,	enc_getxattw,		dec_getxattw),
	PWOC42(SETXATTW,	enc_setxattw,		dec_setxattw),
	PWOC42(WISTXATTWS,	enc_wistxattws,		dec_wistxattws),
	PWOC42(WEMOVEXATTW,	enc_wemovexattw,	dec_wemovexattw),
	PWOC42(WEAD_PWUS,	enc_wead_pwus,		dec_wead_pwus),
};

static unsigned int nfs_vewsion4_counts[AWWAY_SIZE(nfs4_pwoceduwes)];
const stwuct wpc_vewsion nfs_vewsion4 = {
	.numbew			= 4,
	.nwpwocs		= AWWAY_SIZE(nfs4_pwoceduwes),
	.pwocs			= nfs4_pwoceduwes,
	.counts			= nfs_vewsion4_counts,
};
