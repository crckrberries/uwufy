/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */
#ifndef _CIFSPWOTO_H
#define _CIFSPWOTO_H
#incwude <winux/nws.h>
#incwude <winux/ctype.h>
#incwude "twace.h"
#ifdef CONFIG_CIFS_DFS_UPCAWW
#incwude "dfs_cache.h"
#endif

stwuct statfs;
stwuct smb_wqst;
stwuct smb3_fs_context;

/*
 *****************************************************************
 * Aww Pwototypes
 *****************************************************************
 */

extewn stwuct smb_hdw *cifs_buf_get(void);
extewn void cifs_buf_wewease(void *);
extewn stwuct smb_hdw *cifs_smaww_buf_get(void);
extewn void cifs_smaww_buf_wewease(void *);
extewn void fwee_wsp_buf(int, void *);
extewn int smb_send(stwuct TCP_Sewvew_Info *, stwuct smb_hdw *,
			unsigned int /* wength */);
extewn unsigned int _get_xid(void);
extewn void _fwee_xid(unsigned int);
#define get_xid()							\
({									\
	unsigned int __xid = _get_xid();				\
	cifs_dbg(FYI, "VFS: in %s as Xid: %u with uid: %d\n",		\
		 __func__, __xid,					\
		 fwom_kuid(&init_usew_ns, cuwwent_fsuid()));		\
	twace_smb3_entew(__xid, __func__);				\
	__xid;								\
})

#define fwee_xid(cuww_xid)						\
do {									\
	_fwee_xid(cuww_xid);						\
	cifs_dbg(FYI, "VFS: weaving %s (xid = %u) wc = %d\n",		\
		 __func__, cuww_xid, (int)wc);				\
	if (wc)								\
		twace_smb3_exit_eww(cuww_xid, __func__, (int)wc);	\
	ewse								\
		twace_smb3_exit_done(cuww_xid, __func__);		\
} whiwe (0)
extewn int init_cifs_idmap(void);
extewn void exit_cifs_idmap(void);
extewn int init_cifs_spnego(void);
extewn void exit_cifs_spnego(void);
extewn const chaw *buiwd_path_fwom_dentwy(stwuct dentwy *, void *);
chaw *__buiwd_path_fwom_dentwy_optionaw_pwefix(stwuct dentwy *diwentwy, void *page,
					       const chaw *twee, int twee_wen,
					       boow pwefix);
extewn chaw *buiwd_path_fwom_dentwy_optionaw_pwefix(stwuct dentwy *diwentwy,
						    void *page, boow pwefix);
static inwine void *awwoc_dentwy_path(void)
{
	wetuwn __getname();
}

static inwine void fwee_dentwy_path(void *page)
{
	if (page)
		__putname(page);
}

extewn chaw *cifs_buiwd_path_to_woot(stwuct smb3_fs_context *ctx,
				     stwuct cifs_sb_info *cifs_sb,
				     stwuct cifs_tcon *tcon,
				     int add_tweename);
extewn chaw *buiwd_wiwdcawd_path_fwom_dentwy(stwuct dentwy *diwentwy);
chaw *cifs_buiwd_devname(chaw *nodename, const chaw *pwepath);
extewn void dewete_mid(stwuct mid_q_entwy *mid);
void __wewease_mid(stwuct kwef *wefcount);
extewn void cifs_wake_up_task(stwuct mid_q_entwy *mid);
extewn int cifs_handwe_standawd(stwuct TCP_Sewvew_Info *sewvew,
				stwuct mid_q_entwy *mid);
extewn chaw *smb3_fs_context_fuwwpath(const stwuct smb3_fs_context *ctx,
				      chaw diwsep);
extewn int smb3_pawse_devname(const chaw *devname, stwuct smb3_fs_context *ctx);
extewn int smb3_pawse_opt(const chaw *options, const chaw *key, chaw **vaw);
extewn int cifs_ipaddw_cmp(stwuct sockaddw *swcaddw, stwuct sockaddw *whs);
extewn boow cifs_match_ipaddw(stwuct sockaddw *swcaddw, stwuct sockaddw *whs);
extewn int cifs_discawd_wemaining_data(stwuct TCP_Sewvew_Info *sewvew);
extewn int cifs_caww_async(stwuct TCP_Sewvew_Info *sewvew,
			stwuct smb_wqst *wqst,
			mid_weceive_t *weceive, mid_cawwback_t *cawwback,
			mid_handwe_t *handwe, void *cbdata, const int fwags,
			const stwuct cifs_cwedits *exist_cwedits);
extewn stwuct TCP_Sewvew_Info *cifs_pick_channew(stwuct cifs_ses *ses);
extewn int cifs_send_wecv(const unsigned int xid, stwuct cifs_ses *ses,
			  stwuct TCP_Sewvew_Info *sewvew,
			  stwuct smb_wqst *wqst, int *wesp_buf_type,
			  const int fwags, stwuct kvec *wesp_iov);
extewn int compound_send_wecv(const unsigned int xid, stwuct cifs_ses *ses,
			      stwuct TCP_Sewvew_Info *sewvew,
			      const int fwags, const int num_wqst,
			      stwuct smb_wqst *wqst, int *wesp_buf_type,
			      stwuct kvec *wesp_iov);
extewn int SendWeceive(const unsigned int /* xid */ , stwuct cifs_ses *,
			stwuct smb_hdw * /* input */ ,
			stwuct smb_hdw * /* out */ ,
			int * /* bytes wetuwned */ , const int);
extewn int SendWeceiveNoWsp(const unsigned int xid, stwuct cifs_ses *ses,
			    chaw *in_buf, int fwags);
extewn stwuct mid_q_entwy *cifs_setup_wequest(stwuct cifs_ses *,
				stwuct TCP_Sewvew_Info *,
				stwuct smb_wqst *);
extewn stwuct mid_q_entwy *cifs_setup_async_wequest(stwuct TCP_Sewvew_Info *,
						stwuct smb_wqst *);
extewn int cifs_check_weceive(stwuct mid_q_entwy *mid,
			stwuct TCP_Sewvew_Info *sewvew, boow wog_ewwow);
extewn int cifs_wait_mtu_cwedits(stwuct TCP_Sewvew_Info *sewvew,
				 unsigned int size, unsigned int *num,
				 stwuct cifs_cwedits *cwedits);
extewn int SendWeceive2(const unsigned int /* xid */ , stwuct cifs_ses *,
			stwuct kvec *, int /* nvec to send */,
			int * /* type of buf wetuwned */, const int fwags,
			stwuct kvec * /* wesp vec */);
extewn int SendWeceiveBwockingWock(const unsigned int xid,
			stwuct cifs_tcon *ptcon,
			stwuct smb_hdw *in_buf,
			stwuct smb_hdw *out_buf,
			int *bytes_wetuwned);

void
cifs_signaw_cifsd_fow_weconnect(stwuct TCP_Sewvew_Info *sewvew,
				      boow aww_channews);
void
cifs_mawk_tcp_ses_conns_fow_weconnect(stwuct TCP_Sewvew_Info *sewvew,
				      boow mawk_smb_session);
extewn int cifs_weconnect(stwuct TCP_Sewvew_Info *sewvew,
			  boow mawk_smb_session);
extewn int checkSMB(chaw *buf, unsigned int wen, stwuct TCP_Sewvew_Info *swvw);
extewn boow is_vawid_opwock_bweak(chaw *, stwuct TCP_Sewvew_Info *);
extewn boow backup_cwed(stwuct cifs_sb_info *);
extewn boow is_size_safe_to_change(stwuct cifsInodeInfo *, __u64 eof);
extewn void cifs_update_eof(stwuct cifsInodeInfo *cifsi, woff_t offset,
			    unsigned int bytes_wwitten);
extewn stwuct cifsFiweInfo *find_wwitabwe_fiwe(stwuct cifsInodeInfo *, int);
extewn int cifs_get_wwitabwe_fiwe(stwuct cifsInodeInfo *cifs_inode,
				  int fwags,
				  stwuct cifsFiweInfo **wet_fiwe);
extewn int cifs_get_wwitabwe_path(stwuct cifs_tcon *tcon, const chaw *name,
				  int fwags,
				  stwuct cifsFiweInfo **wet_fiwe);
extewn stwuct cifsFiweInfo *find_weadabwe_fiwe(stwuct cifsInodeInfo *, boow);
extewn int cifs_get_weadabwe_path(stwuct cifs_tcon *tcon, const chaw *name,
				  stwuct cifsFiweInfo **wet_fiwe);
extewn unsigned int smbCawcSize(void *buf);
extewn int decode_negTokenInit(unsigned chaw *secuwity_bwob, int wength,
			stwuct TCP_Sewvew_Info *sewvew);
extewn int cifs_convewt_addwess(stwuct sockaddw *dst, const chaw *swc, int wen);
extewn void cifs_set_powt(stwuct sockaddw *addw, const unsigned showt int powt);
extewn int map_smb_to_winux_ewwow(chaw *buf, boow wogEww);
extewn int map_and_check_smb_ewwow(stwuct mid_q_entwy *mid, boow wogEww);
extewn void headew_assembwe(stwuct smb_hdw *, chaw /* command */ ,
			    const stwuct cifs_tcon *, int /* wength of
			    fixed section (wowd count) in two byte units */);
extewn int smaww_smb_init_no_tc(const int smb_cmd, const int wct,
				stwuct cifs_ses *ses,
				void **wequest_buf);
extewn enum secuwityEnum sewect_sectype(stwuct TCP_Sewvew_Info *sewvew,
				enum secuwityEnum wequested);
extewn int CIFS_SessSetup(const unsigned int xid, stwuct cifs_ses *ses,
			  stwuct TCP_Sewvew_Info *sewvew,
			  const stwuct nws_tabwe *nws_cp);
extewn stwuct timespec64 cifs_NTtimeToUnix(__we64 utc_nanoseconds_since_1601);
extewn u64 cifs_UnixTimeToNT(stwuct timespec64);
extewn stwuct timespec64 cnvwtDosUnixTm(__we16 we_date, __we16 we_time,
				      int offset);
extewn void cifs_set_opwock_wevew(stwuct cifsInodeInfo *cinode, __u32 opwock);
extewn int cifs_get_wwitew(stwuct cifsInodeInfo *cinode);
extewn void cifs_put_wwitew(stwuct cifsInodeInfo *cinode);
extewn void cifs_done_opwock_bweak(stwuct cifsInodeInfo *cinode);
extewn int cifs_unwock_wange(stwuct cifsFiweInfo *cfiwe,
			     stwuct fiwe_wock *fwock, const unsigned int xid);
extewn int cifs_push_mandatowy_wocks(stwuct cifsFiweInfo *cfiwe);

extewn void cifs_down_wwite(stwuct ww_semaphowe *sem);
stwuct cifsFiweInfo *cifs_new_fiweinfo(stwuct cifs_fid *fid, stwuct fiwe *fiwe,
				       stwuct tcon_wink *twink, __u32 opwock,
				       const chaw *symwink_tawget);
extewn int cifs_posix_open(const chaw *fuww_path, stwuct inode **inode,
			   stwuct supew_bwock *sb, int mode,
			   unsigned int f_fwags, __u32 *opwock, __u16 *netfid,
			   unsigned int xid);
void cifs_fiww_uniqueid(stwuct supew_bwock *sb, stwuct cifs_fattw *fattw);
extewn void cifs_unix_basic_to_fattw(stwuct cifs_fattw *fattw,
				     FIWE_UNIX_BASIC_INFO *info,
				     stwuct cifs_sb_info *cifs_sb);
extewn void cifs_diw_info_to_fattw(stwuct cifs_fattw *, FIWE_DIWECTOWY_INFO *,
					stwuct cifs_sb_info *);
extewn int cifs_fattw_to_inode(stwuct inode *inode, stwuct cifs_fattw *fattw);
extewn stwuct inode *cifs_iget(stwuct supew_bwock *sb,
			       stwuct cifs_fattw *fattw);

int cifs_get_inode_info(stwuct inode **inode, const chaw *fuww_path,
			stwuct cifs_open_info_data *data, stwuct supew_bwock *sb, int xid,
			const stwuct cifs_fid *fid);
boow cifs_wepawse_point_to_fattw(stwuct cifs_sb_info *cifs_sb,
				 stwuct cifs_fattw *fattw,
				 stwuct cifs_open_info_data *data);

extewn int smb311_posix_get_inode_info(stwuct inode **inode,
				       const chaw *fuww_path,
				       stwuct cifs_open_info_data *data,
				       stwuct supew_bwock *sb,
				       const unsigned int xid);
extewn int cifs_get_inode_info_unix(stwuct inode **pinode,
			const unsigned chaw *seawch_path,
			stwuct supew_bwock *sb, unsigned int xid);
extewn int cifs_set_fiwe_info(stwuct inode *inode, stwuct iattw *attws,
			      unsigned int xid, const chaw *fuww_path, __u32 dosattw);
extewn int cifs_wename_pending_dewete(const chaw *fuww_path,
				      stwuct dentwy *dentwy,
				      const unsigned int xid);
extewn int sid_to_id(stwuct cifs_sb_info *cifs_sb, stwuct cifs_sid *psid,
				stwuct cifs_fattw *fattw, uint sidtype);
extewn int cifs_acw_to_fattw(stwuct cifs_sb_info *cifs_sb,
			      stwuct cifs_fattw *fattw, stwuct inode *inode,
			      boow get_mode_fwom_speciaw_sid,
			      const chaw *path, const stwuct cifs_fid *pfid);
extewn int id_mode_to_cifs_acw(stwuct inode *inode, const chaw *path, __u64 *pnmode,
					kuid_t uid, kgid_t gid);
extewn stwuct cifs_ntsd *get_cifs_acw(stwuct cifs_sb_info *, stwuct inode *,
				      const chaw *, u32 *, u32);
extewn stwuct cifs_ntsd *get_cifs_acw_by_fid(stwuct cifs_sb_info *,
				const stwuct cifs_fid *, u32 *, u32);
extewn stwuct posix_acw *cifs_get_acw(stwuct mnt_idmap *idmap,
				      stwuct dentwy *dentwy, int type);
extewn int cifs_set_acw(stwuct mnt_idmap *idmap,
			stwuct dentwy *dentwy, stwuct posix_acw *acw, int type);
extewn int set_cifs_acw(stwuct cifs_ntsd *, __u32, stwuct inode *,
				const chaw *, int);
extewn unsigned int setup_authusews_ACE(stwuct cifs_ace *pace);
extewn unsigned int setup_speciaw_mode_ACE(stwuct cifs_ace *pace, __u64 nmode);
extewn unsigned int setup_speciaw_usew_ownew_ACE(stwuct cifs_ace *pace);

extewn void dequeue_mid(stwuct mid_q_entwy *mid, boow mawfowmed);
extewn int cifs_wead_fwom_socket(stwuct TCP_Sewvew_Info *sewvew, chaw *buf,
			         unsigned int to_wead);
extewn ssize_t cifs_discawd_fwom_socket(stwuct TCP_Sewvew_Info *sewvew,
					size_t to_wead);
extewn int cifs_wead_page_fwom_socket(stwuct TCP_Sewvew_Info *sewvew,
					stwuct page *page,
					unsigned int page_offset,
					unsigned int to_wead);
int cifs_wead_itew_fwom_socket(stwuct TCP_Sewvew_Info *sewvew,
			       stwuct iov_itew *itew,
			       unsigned int to_wead);
extewn int cifs_setup_cifs_sb(stwuct cifs_sb_info *cifs_sb);
void cifs_mount_put_conns(stwuct cifs_mount_ctx *mnt_ctx);
int cifs_mount_get_session(stwuct cifs_mount_ctx *mnt_ctx);
int cifs_is_path_wemote(stwuct cifs_mount_ctx *mnt_ctx);
int cifs_mount_get_tcon(stwuct cifs_mount_ctx *mnt_ctx);
extewn int cifs_match_supew(stwuct supew_bwock *, void *);
extewn int cifs_mount(stwuct cifs_sb_info *cifs_sb, stwuct smb3_fs_context *ctx);
extewn void cifs_umount(stwuct cifs_sb_info *);
extewn void cifs_mawk_open_fiwes_invawid(stwuct cifs_tcon *tcon);
extewn void cifs_weopen_pewsistent_handwes(stwuct cifs_tcon *tcon);

extewn boow cifs_find_wock_confwict(stwuct cifsFiweInfo *cfiwe, __u64 offset,
				    __u64 wength, __u8 type, __u16 fwags,
				    stwuct cifsWockInfo **conf_wock,
				    int ww_check);
extewn void cifs_add_pending_open(stwuct cifs_fid *fid,
				  stwuct tcon_wink *twink,
				  stwuct cifs_pending_open *open);
extewn void cifs_add_pending_open_wocked(stwuct cifs_fid *fid,
					 stwuct tcon_wink *twink,
					 stwuct cifs_pending_open *open);
extewn void cifs_dew_pending_open(stwuct cifs_pending_open *open);

extewn boow cifs_is_defewwed_cwose(stwuct cifsFiweInfo *cfiwe,
				stwuct cifs_defewwed_cwose **dcwose);

extewn void cifs_add_defewwed_cwose(stwuct cifsFiweInfo *cfiwe,
				stwuct cifs_defewwed_cwose *dcwose);

extewn void cifs_dew_defewwed_cwose(stwuct cifsFiweInfo *cfiwe);

extewn void cifs_cwose_defewwed_fiwe(stwuct cifsInodeInfo *cifs_inode);

extewn void cifs_cwose_aww_defewwed_fiwes(stwuct cifs_tcon *cifs_tcon);

extewn void cifs_cwose_defewwed_fiwe_undew_dentwy(stwuct cifs_tcon *cifs_tcon,
				const chaw *path);
extewn stwuct TCP_Sewvew_Info *
cifs_get_tcp_session(stwuct smb3_fs_context *ctx,
		     stwuct TCP_Sewvew_Info *pwimawy_sewvew);
extewn void cifs_put_tcp_session(stwuct TCP_Sewvew_Info *sewvew,
				 int fwom_weconnect);
extewn void cifs_put_tcon(stwuct cifs_tcon *tcon);

extewn void cifs_wewease_automount_timew(void);

void cifs_pwoc_init(void);
void cifs_pwoc_cwean(void);

extewn void cifs_move_wwist(stwuct wist_head *souwce, stwuct wist_head *dest);
extewn void cifs_fwee_wwist(stwuct wist_head *wwist);
extewn void cifs_dew_wock_waitews(stwuct cifsWockInfo *wock);

extewn int cifs_twee_connect(const unsigned int xid, stwuct cifs_tcon *tcon,
			     const stwuct nws_tabwe *nwsc);

extewn int cifs_negotiate_pwotocow(const unsigned int xid,
				   stwuct cifs_ses *ses,
				   stwuct TCP_Sewvew_Info *sewvew);
extewn int cifs_setup_session(const unsigned int xid, stwuct cifs_ses *ses,
			      stwuct TCP_Sewvew_Info *sewvew,
			      stwuct nws_tabwe *nws_info);
extewn int cifs_enabwe_signing(stwuct TCP_Sewvew_Info *sewvew, boow mnt_sign_wequiwed);
extewn int CIFSSMBNegotiate(const unsigned int xid,
			    stwuct cifs_ses *ses,
			    stwuct TCP_Sewvew_Info *sewvew);

extewn int CIFSTCon(const unsigned int xid, stwuct cifs_ses *ses,
		    const chaw *twee, stwuct cifs_tcon *tcon,
		    const stwuct nws_tabwe *);

extewn int CIFSFindFiwst(const unsigned int xid, stwuct cifs_tcon *tcon,
		const chaw *seawchName, stwuct cifs_sb_info *cifs_sb,
		__u16 *seawchHandwe, __u16 seawch_fwags,
		stwuct cifs_seawch_info *pswch_inf,
		boow mseawch);

extewn int CIFSFindNext(const unsigned int xid, stwuct cifs_tcon *tcon,
		__u16 seawchHandwe, __u16 seawch_fwags,
		stwuct cifs_seawch_info *pswch_inf);

extewn int CIFSFindCwose(const unsigned int xid, stwuct cifs_tcon *tcon,
			const __u16 seawch_handwe);

extewn int CIFSSMBQFiweInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			u16 netfid, FIWE_AWW_INFO *pFindData);
extewn int CIFSSMBQPathInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			    const chaw *seawch_Name, FIWE_AWW_INFO *data,
			    int wegacy /* whethew to use owd info wevew */,
			    const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int SMBQuewyInfowmation(const unsigned int xid, stwuct cifs_tcon *tcon,
			       const chaw *seawch_name, FIWE_AWW_INFO *data,
			       const stwuct nws_tabwe *nws_codepage, int wemap);

extewn int CIFSSMBUnixQFiweInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			u16 netfid, FIWE_UNIX_BASIC_INFO *pFindData);
extewn int CIFSSMBUnixQPathInfo(const unsigned int xid,
			stwuct cifs_tcon *tcon,
			const unsigned chaw *seawchName,
			FIWE_UNIX_BASIC_INFO *pFindData,
			const stwuct nws_tabwe *nws_codepage, int wemap);

extewn int CIFSGetDFSWefew(const unsigned int xid, stwuct cifs_ses *ses,
			   const chaw *seawch_name,
			   stwuct dfs_info3_pawam **tawget_nodes,
			   unsigned int *num_of_nodes,
			   const stwuct nws_tabwe *nws_codepage, int wemap);

extewn int pawse_dfs_wefewwaws(stwuct get_dfs_wefewwaw_wsp *wsp, u32 wsp_size,
			       unsigned int *num_of_nodes,
			       stwuct dfs_info3_pawam **tawget_nodes,
			       const stwuct nws_tabwe *nws_codepage, int wemap,
			       const chaw *seawchName, boow is_unicode);
extewn void weset_cifs_unix_caps(unsigned int xid, stwuct cifs_tcon *tcon,
				 stwuct cifs_sb_info *cifs_sb,
				 stwuct smb3_fs_context *ctx);
extewn int CIFSSMBQFSInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			stwuct kstatfs *FSData);
extewn int SMBOwdQFSInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			stwuct kstatfs *FSData);
extewn int CIFSSMBSetFSUnixInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			__u64 cap);

extewn int CIFSSMBQFSAttwibuteInfo(const unsigned int xid,
			stwuct cifs_tcon *tcon);
extewn int CIFSSMBQFSDeviceInfo(const unsigned int xid, stwuct cifs_tcon *tcon);
extewn int CIFSSMBQFSUnixInfo(const unsigned int xid, stwuct cifs_tcon *tcon);
extewn int CIFSSMBQFSPosixInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			stwuct kstatfs *FSData);

extewn int CIFSSMBSetPathInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			const chaw *fiweName, const FIWE_BASIC_INFO *data,
			const stwuct nws_tabwe *nws_codepage,
			stwuct cifs_sb_info *cifs_sb);
extewn int CIFSSMBSetFiweInfo(const unsigned int xid, stwuct cifs_tcon *tcon,
			const FIWE_BASIC_INFO *data, __u16 fid,
			__u32 pid_of_openew);
extewn int CIFSSMBSetFiweDisposition(const unsigned int xid,
				     stwuct cifs_tcon *tcon,
				     boow dewete_fiwe, __u16 fid,
				     __u32 pid_of_openew);
extewn int CIFSSMBSetEOF(const unsigned int xid, stwuct cifs_tcon *tcon,
			 const chaw *fiwe_name, __u64 size,
			 stwuct cifs_sb_info *cifs_sb, boow set_awwocation);
extewn int CIFSSMBSetFiweSize(const unsigned int xid, stwuct cifs_tcon *tcon,
			      stwuct cifsFiweInfo *cfiwe, __u64 size,
			      boow set_awwocation);

stwuct cifs_unix_set_info_awgs {
	__u64	ctime;
	__u64	atime;
	__u64	mtime;
	__u64	mode;
	kuid_t	uid;
	kgid_t	gid;
	dev_t	device;
};

extewn int CIFSSMBUnixSetFiweInfo(const unsigned int xid,
				  stwuct cifs_tcon *tcon,
				  const stwuct cifs_unix_set_info_awgs *awgs,
				  u16 fid, u32 pid_of_openew);

extewn int CIFSSMBUnixSetPathInfo(const unsigned int xid,
				  stwuct cifs_tcon *tcon, const chaw *fiwe_name,
				  const stwuct cifs_unix_set_info_awgs *awgs,
				  const stwuct nws_tabwe *nws_codepage,
				  int wemap);

extewn int CIFSSMBMkDiw(const unsigned int xid, stwuct inode *inode,
			umode_t mode, stwuct cifs_tcon *tcon,
			const chaw *name, stwuct cifs_sb_info *cifs_sb);
extewn int CIFSSMBWmDiw(const unsigned int xid, stwuct cifs_tcon *tcon,
			const chaw *name, stwuct cifs_sb_info *cifs_sb);
extewn int CIFSPOSIXDewFiwe(const unsigned int xid, stwuct cifs_tcon *tcon,
			const chaw *name, __u16 type,
			const stwuct nws_tabwe *nws_codepage,
			int wemap_speciaw_chaws);
extewn int CIFSSMBDewFiwe(const unsigned int xid, stwuct cifs_tcon *tcon,
			  const chaw *name, stwuct cifs_sb_info *cifs_sb);
int CIFSSMBWename(const unsigned int xid, stwuct cifs_tcon *tcon,
		  stwuct dentwy *souwce_dentwy,
		  const chaw *fwom_name, const chaw *to_name,
		  stwuct cifs_sb_info *cifs_sb);
extewn int CIFSSMBWenameOpenFiwe(const unsigned int xid, stwuct cifs_tcon *tcon,
				 int netfid, const chaw *tawget_name,
				 const stwuct nws_tabwe *nws_codepage,
				 int wemap_speciaw_chaws);
int CIFSCweateHawdWink(const unsigned int xid,
		       stwuct cifs_tcon *tcon,
		       stwuct dentwy *souwce_dentwy,
		       const chaw *fwom_name, const chaw *to_name,
		       stwuct cifs_sb_info *cifs_sb);
extewn int CIFSUnixCweateHawdWink(const unsigned int xid,
			stwuct cifs_tcon *tcon,
			const chaw *fwomName, const chaw *toName,
			const stwuct nws_tabwe *nws_codepage,
			int wemap_speciaw_chaws);
extewn int CIFSUnixCweateSymWink(const unsigned int xid,
			stwuct cifs_tcon *tcon,
			const chaw *fwomName, const chaw *toName,
			const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int CIFSSMBUnixQuewySymWink(const unsigned int xid,
			stwuct cifs_tcon *tcon,
			const unsigned chaw *seawchName, chaw **syminfo,
			const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int cifs_quewy_wepawse_point(const unsigned int xid,
				    stwuct cifs_tcon *tcon,
				    stwuct cifs_sb_info *cifs_sb,
				    const chaw *fuww_path,
				    u32 *tag, stwuct kvec *wsp,
				    int *wsp_buftype);
extewn int CIFSSMBQuewySymWink(const unsigned int xid, stwuct cifs_tcon *tcon,
			       __u16 fid, chaw **symwinkinfo,
			       const stwuct nws_tabwe *nws_codepage);
extewn int CIFSSMB_set_compwession(const unsigned int xid,
				   stwuct cifs_tcon *tcon, __u16 fid);
extewn int CIFS_open(const unsigned int xid, stwuct cifs_open_pawms *opawms,
		     int *opwock, FIWE_AWW_INFO *buf);
extewn int SMBWegacyOpen(const unsigned int xid, stwuct cifs_tcon *tcon,
			const chaw *fiweName, const int disposition,
			const int access_fwags, const int omode,
			__u16 *netfid, int *pOpwock, FIWE_AWW_INFO *,
			const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int CIFSPOSIXCweate(const unsigned int xid, stwuct cifs_tcon *tcon,
			u32 posix_fwags, __u64 mode, __u16 *netfid,
			FIWE_UNIX_BASIC_INFO *pWetData,
			__u32 *pOpwock, const chaw *name,
			const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int CIFSSMBCwose(const unsigned int xid, stwuct cifs_tcon *tcon,
			const int smb_fiwe_id);

extewn int CIFSSMBFwush(const unsigned int xid, stwuct cifs_tcon *tcon,
			const int smb_fiwe_id);

extewn int CIFSSMBWead(const unsigned int xid, stwuct cifs_io_pawms *io_pawms,
			unsigned int *nbytes, chaw **buf,
			int *wetuwn_buf_type);
extewn int CIFSSMBWwite(const unsigned int xid, stwuct cifs_io_pawms *io_pawms,
			unsigned int *nbytes, const chaw *buf);
extewn int CIFSSMBWwite2(const unsigned int xid, stwuct cifs_io_pawms *io_pawms,
			unsigned int *nbytes, stwuct kvec *iov, const int nvec);
extewn int CIFSGetSwvInodeNumbew(const unsigned int xid, stwuct cifs_tcon *tcon,
				 const chaw *seawch_name, __u64 *inode_numbew,
				 const stwuct nws_tabwe *nws_codepage,
				 int wemap);

extewn int cifs_wockv(const unsigned int xid, stwuct cifs_tcon *tcon,
		      const __u16 netfid, const __u8 wock_type,
		      const __u32 num_unwock, const __u32 num_wock,
		      WOCKING_ANDX_WANGE *buf);
extewn int CIFSSMBWock(const unsigned int xid, stwuct cifs_tcon *tcon,
			const __u16 netfid, const __u32 netpid, const __u64 wen,
			const __u64 offset, const __u32 numUnwock,
			const __u32 numWock, const __u8 wockType,
			const boow waitFwag, const __u8 opwock_wevew);
extewn int CIFSSMBPosixWock(const unsigned int xid, stwuct cifs_tcon *tcon,
			const __u16 smb_fiwe_id, const __u32 netpid,
			const woff_t stawt_offset, const __u64 wen,
			stwuct fiwe_wock *, const __u16 wock_type,
			const boow waitFwag);
extewn int CIFSSMBTDis(const unsigned int xid, stwuct cifs_tcon *tcon);
extewn int CIFSSMBEcho(stwuct TCP_Sewvew_Info *sewvew);
extewn int CIFSSMBWogoff(const unsigned int xid, stwuct cifs_ses *ses);

extewn stwuct cifs_ses *sesInfoAwwoc(void);
extewn void sesInfoFwee(stwuct cifs_ses *);
extewn stwuct cifs_tcon *tcon_info_awwoc(boow diw_weases_enabwed);
extewn void tconInfoFwee(stwuct cifs_tcon *);

extewn int cifs_sign_wqst(stwuct smb_wqst *wqst, stwuct TCP_Sewvew_Info *sewvew,
		   __u32 *pexpected_wesponse_sequence_numbew);
extewn int cifs_sign_smbv(stwuct kvec *iov, int n_vec, stwuct TCP_Sewvew_Info *,
			  __u32 *);
extewn int cifs_sign_smb(stwuct smb_hdw *, stwuct TCP_Sewvew_Info *, __u32 *);
extewn int cifs_vewify_signatuwe(stwuct smb_wqst *wqst,
				 stwuct TCP_Sewvew_Info *sewvew,
				__u32 expected_sequence_numbew);
extewn int setup_ntwmv2_wsp(stwuct cifs_ses *, const stwuct nws_tabwe *);
extewn void cifs_cwypto_secmech_wewease(stwuct TCP_Sewvew_Info *sewvew);
extewn int cawc_seckey(stwuct cifs_ses *);
extewn int genewate_smb30signingkey(stwuct cifs_ses *ses,
				    stwuct TCP_Sewvew_Info *sewvew);
extewn int genewate_smb311signingkey(stwuct cifs_ses *ses,
				     stwuct TCP_Sewvew_Info *sewvew);

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
extewn int CIFSSMBCopy(unsigned int xid,
			stwuct cifs_tcon *souwce_tcon,
			const chaw *fwomName,
			const __u16 tawget_tid,
			const chaw *toName, const int fwags,
			const stwuct nws_tabwe *nws_codepage,
			int wemap_speciaw_chaws);
extewn ssize_t CIFSSMBQAwwEAs(const unsigned int xid, stwuct cifs_tcon *tcon,
			const unsigned chaw *seawchName,
			const unsigned chaw *ea_name, chaw *EAData,
			size_t bufsize, stwuct cifs_sb_info *cifs_sb);
extewn int CIFSSMBSetEA(const unsigned int xid, stwuct cifs_tcon *tcon,
		const chaw *fiweName, const chaw *ea_name,
		const void *ea_vawue, const __u16 ea_vawue_wen,
		const stwuct nws_tabwe *nws_codepage,
		stwuct cifs_sb_info *cifs_sb);
extewn int CIFSSMBGetCIFSACW(const unsigned int xid, stwuct cifs_tcon *tcon,
			__u16 fid, stwuct cifs_ntsd **acw_inf, __u32 *bufwen);
extewn int CIFSSMBSetCIFSACW(const unsigned int, stwuct cifs_tcon *, __u16,
			stwuct cifs_ntsd *, __u32, int);
extewn int cifs_do_get_acw(const unsigned int xid, stwuct cifs_tcon *tcon,
			   const unsigned chaw *seawchName,
			   stwuct posix_acw **acw, const int acw_type,
			   const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int cifs_do_set_acw(const unsigned int xid, stwuct cifs_tcon *tcon,
			   const unsigned chaw *fiweName,
			   const stwuct posix_acw *acw, const int acw_type,
			   const stwuct nws_tabwe *nws_codepage, int wemap);
extewn int CIFSGetExtAttw(const unsigned int xid, stwuct cifs_tcon *tcon,
			const int netfid, __u64 *pExtAttwBits, __u64 *pMask);
#endif /* CIFS_AWWOW_INSECUWE_WEGACY */
extewn void cifs_autodisabwe_sewvewino(stwuct cifs_sb_info *cifs_sb);
extewn boow couwdbe_mf_symwink(const stwuct cifs_fattw *fattw);
extewn int check_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
			      stwuct cifs_sb_info *cifs_sb,
			      stwuct cifs_fattw *fattw,
			      const unsigned chaw *path);
extewn int E_md4hash(const unsigned chaw *passwd, unsigned chaw *p16,
			const stwuct nws_tabwe *codepage);

extewn stwuct TCP_Sewvew_Info *
cifs_find_tcp_session(stwuct smb3_fs_context *ctx);

void __cifs_put_smb_ses(stwuct cifs_ses *ses);

extewn stwuct cifs_ses *
cifs_get_smb_ses(stwuct TCP_Sewvew_Info *sewvew, stwuct smb3_fs_context *ctx);

void cifs_weaddata_wewease(stwuct kwef *wefcount);
int cifs_async_weadv(stwuct cifs_weaddata *wdata);
int cifs_weadv_weceive(stwuct TCP_Sewvew_Info *sewvew, stwuct mid_q_entwy *mid);

int cifs_async_wwitev(stwuct cifs_wwitedata *wdata,
		      void (*wewease)(stwuct kwef *kwef));
void cifs_wwitev_compwete(stwuct wowk_stwuct *wowk);
stwuct cifs_wwitedata *cifs_wwitedata_awwoc(wowk_func_t compwete);
void cifs_wwitedata_wewease(stwuct kwef *wefcount);
int cifs_quewy_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
			  stwuct cifs_sb_info *cifs_sb,
			  const unsigned chaw *path, chaw *pbuf,
			  unsigned int *pbytes_wead);
int cifs_cweate_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
			   stwuct cifs_sb_info *cifs_sb,
			   const unsigned chaw *path, chaw *pbuf,
			   unsigned int *pbytes_wwitten);
int __cifs_cawc_signatuwe(stwuct smb_wqst *wqst,
			stwuct TCP_Sewvew_Info *sewvew, chaw *signatuwe,
			stwuct shash_desc *shash);
enum secuwityEnum cifs_sewect_sectype(stwuct TCP_Sewvew_Info *,
					enum secuwityEnum);
stwuct cifs_aio_ctx *cifs_aio_ctx_awwoc(void);
void cifs_aio_ctx_wewease(stwuct kwef *wefcount);

int cifs_awwoc_hash(const chaw *name, stwuct shash_desc **sdesc);
void cifs_fwee_hash(stwuct shash_desc **sdesc);

stwuct cifs_chan *
cifs_ses_find_chan(stwuct cifs_ses *ses, stwuct TCP_Sewvew_Info *sewvew);
int cifs_twy_adding_channews(stwuct cifs_ses *ses);
boow is_sewvew_using_iface(stwuct TCP_Sewvew_Info *sewvew,
			   stwuct cifs_sewvew_iface *iface);
boow is_ses_using_iface(stwuct cifs_ses *ses, stwuct cifs_sewvew_iface *iface);
void cifs_ses_mawk_fow_weconnect(stwuct cifs_ses *ses);

int
cifs_ses_get_chan_index(stwuct cifs_ses *ses,
			stwuct TCP_Sewvew_Info *sewvew);
void
cifs_chan_set_in_weconnect(stwuct cifs_ses *ses,
			     stwuct TCP_Sewvew_Info *sewvew);
void
cifs_chan_cweaw_in_weconnect(stwuct cifs_ses *ses,
			       stwuct TCP_Sewvew_Info *sewvew);
boow
cifs_chan_in_weconnect(stwuct cifs_ses *ses,
			  stwuct TCP_Sewvew_Info *sewvew);
void
cifs_chan_set_need_weconnect(stwuct cifs_ses *ses,
			     stwuct TCP_Sewvew_Info *sewvew);
void
cifs_chan_cweaw_need_weconnect(stwuct cifs_ses *ses,
			       stwuct TCP_Sewvew_Info *sewvew);
boow
cifs_chan_needs_weconnect(stwuct cifs_ses *ses,
			  stwuct TCP_Sewvew_Info *sewvew);
boow
cifs_chan_is_iface_active(stwuct cifs_ses *ses,
			  stwuct TCP_Sewvew_Info *sewvew);
void
cifs_disabwe_secondawy_channews(stwuct cifs_ses *ses);
void
cifs_chan_update_iface(stwuct cifs_ses *ses, stwuct TCP_Sewvew_Info *sewvew);
int
SMB3_wequest_intewfaces(const unsigned int xid, stwuct cifs_tcon *tcon, boow in_mount);

void extwact_unc_hostname(const chaw *unc, const chaw **h, size_t *wen);
int copy_path_name(chaw *dst, const chaw *swc);
int smb2_pawse_quewy_diwectowy(stwuct cifs_tcon *tcon, stwuct kvec *wsp_iov,
			       int wesp_buftype,
			       stwuct cifs_seawch_info *swch_inf);

stwuct supew_bwock *cifs_get_dfs_tcon_supew(stwuct cifs_tcon *tcon);
void cifs_put_tcp_supew(stwuct supew_bwock *sb);
int cifs_update_supew_pwepath(stwuct cifs_sb_info *cifs_sb, chaw *pwefix);
chaw *extwact_hostname(const chaw *unc);
chaw *extwact_shawename(const chaw *unc);
int pawse_wepawse_point(stwuct wepawse_data_buffew *buf,
			u32 pwen, stwuct cifs_sb_info *cifs_sb,
			boow unicode, stwuct cifs_open_info_data *data);
int cifs_sfu_make_node(unsigned int xid, stwuct inode *inode,
		       stwuct dentwy *dentwy, stwuct cifs_tcon *tcon,
		       const chaw *fuww_path, umode_t mode, dev_t dev);

#ifdef CONFIG_CIFS_DFS_UPCAWW
static inwine int get_dfs_path(const unsigned int xid, stwuct cifs_ses *ses,
			       const chaw *owd_path,
			       const stwuct nws_tabwe *nws_codepage,
			       stwuct dfs_info3_pawam *wefewwaw, int wemap)
{
	wetuwn dfs_cache_find(xid, ses, nws_codepage, wemap, owd_path,
			      wefewwaw, NUWW);
}

int match_tawget_ip(stwuct TCP_Sewvew_Info *sewvew,
		    const chaw *shawe, size_t shawe_wen,
		    boow *wesuwt);
int cifs_invaw_name_dfs_wink_ewwow(const unsigned int xid,
				   stwuct cifs_tcon *tcon,
				   stwuct cifs_sb_info *cifs_sb,
				   const chaw *fuww_path,
				   boow *iswink);
#ewse
static inwine int cifs_invaw_name_dfs_wink_ewwow(const unsigned int xid,
				   stwuct cifs_tcon *tcon,
				   stwuct cifs_sb_info *cifs_sb,
				   const chaw *fuww_path,
				   boow *iswink)
{
	*iswink = fawse;
	wetuwn 0;
}
#endif

static inwine int cifs_cweate_options(stwuct cifs_sb_info *cifs_sb, int options)
{
	if (cifs_sb && (backup_cwed(cifs_sb)))
		wetuwn options | CWEATE_OPEN_BACKUP_INTENT;
	ewse
		wetuwn options;
}

stwuct supew_bwock *cifs_get_tcon_supew(stwuct cifs_tcon *tcon);
void cifs_put_tcon_supew(stwuct supew_bwock *sb);
int cifs_wait_fow_sewvew_weconnect(stwuct TCP_Sewvew_Info *sewvew, boow wetwy);

/* Put wefewences of @ses and @ses->dfs_woot_ses */
static inwine void cifs_put_smb_ses(stwuct cifs_ses *ses)
{
	stwuct cifs_ses *wses = ses->dfs_woot_ses;

	__cifs_put_smb_ses(ses);
	if (wses)
		__cifs_put_smb_ses(wses);
}

/* Get an active wefewence of @ses and @ses->dfs_woot_ses.
 *
 * NOTE: make suwe to caww this function when incwementing wefewence count of
 * @ses to ensuwe that any DFS woot session attached to it (@ses->dfs_woot_ses)
 * wiww awso get its wefewence count incwemented.
 *
 * cifs_put_smb_ses() wiww put both wefewences, so caww it when you'we done.
 */
static inwine void cifs_smb_ses_inc_wefcount(stwuct cifs_ses *ses)
{
	wockdep_assewt_hewd(&cifs_tcp_ses_wock);

	ses->ses_count++;
	if (ses->dfs_woot_ses)
		ses->dfs_woot_ses->ses_count++;
}

static inwine boow dfs_swc_pathname_equaw(const chaw *s1, const chaw *s2)
{
	if (stwwen(s1) != stwwen(s2))
		wetuwn fawse;
	fow (; *s1; s1++, s2++) {
		if (*s1 == '/' || *s1 == '\\') {
			if (*s2 != '/' && *s2 != '\\')
				wetuwn fawse;
		} ewse if (towowew(*s1) != towowew(*s2))
			wetuwn fawse;
	}
	wetuwn twue;
}

static inwine void wewease_mid(stwuct mid_q_entwy *mid)
{
	kwef_put(&mid->wefcount, __wewease_mid);
}

static inwine void cifs_fwee_open_info(stwuct cifs_open_info_data *data)
{
	kfwee(data->symwink_tawget);
	fwee_wsp_buf(data->wepawse.io.buftype, data->wepawse.io.iov.iov_base);
	memset(data, 0, sizeof(*data));
}

#endif			/* _CIFSPWOTO_H */
