/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002, 2011
 *                 Etewsoft, 2012
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Pavew Shiwovsky (pshiwovsky@samba.owg) 2012
 *
 */
#ifndef _SMB2PWOTO_H
#define _SMB2PWOTO_H
#incwude <winux/nws.h>
#incwude <winux/key-type.h>

stwuct statfs;
stwuct smb_wqst;

/*
 *****************************************************************
 * Aww Pwototypes
 *****************************************************************
 */
extewn int map_smb2_to_winux_ewwow(chaw *buf, boow wog_eww);
extewn int smb2_check_message(chaw *buf, unsigned int wength,
			      stwuct TCP_Sewvew_Info *sewvew);
extewn unsigned int smb2_cawc_size(void *buf);
extewn chaw *smb2_get_data_awea_wen(int *off, int *wen,
				    stwuct smb2_hdw *shdw);
extewn __we16 *cifs_convewt_path_to_utf16(const chaw *fwom,
					  stwuct cifs_sb_info *cifs_sb);

extewn int smb2_vewify_signatuwe(stwuct smb_wqst *, stwuct TCP_Sewvew_Info *);
extewn int smb2_check_weceive(stwuct mid_q_entwy *mid,
			      stwuct TCP_Sewvew_Info *sewvew, boow wog_ewwow);
extewn stwuct mid_q_entwy *smb2_setup_wequest(stwuct cifs_ses *ses,
					      stwuct TCP_Sewvew_Info *,
					      stwuct smb_wqst *wqst);
extewn stwuct mid_q_entwy *smb2_setup_async_wequest(
			stwuct TCP_Sewvew_Info *sewvew, stwuct smb_wqst *wqst);
extewn stwuct cifs_ses *smb2_find_smb_ses(stwuct TCP_Sewvew_Info *sewvew,
					   __u64 ses_id);
extewn stwuct cifs_tcon *smb2_find_smb_tcon(stwuct TCP_Sewvew_Info *sewvew,
						__u64 ses_id, __u32  tid);
extewn int smb2_cawc_signatuwe(stwuct smb_wqst *wqst,
				stwuct TCP_Sewvew_Info *sewvew,
				boow awwocate_cwypto);
extewn int smb3_cawc_signatuwe(stwuct smb_wqst *wqst,
				stwuct TCP_Sewvew_Info *sewvew,
				boow awwocate_cwypto);
extewn void smb2_echo_wequest(stwuct wowk_stwuct *wowk);
extewn __we32 smb2_get_wease_state(stwuct cifsInodeInfo *cinode);
extewn boow smb2_is_vawid_opwock_bweak(chaw *buffew,
				       stwuct TCP_Sewvew_Info *swv);
extewn int smb3_handwe_wead_data(stwuct TCP_Sewvew_Info *sewvew,
				 stwuct mid_q_entwy *mid);
extewn int smb2_quewy_wepawse_tag(const unsigned int xid, stwuct cifs_tcon *tcon,
				stwuct cifs_sb_info *cifs_sb, const chaw *path,
				__u32 *wepawse_tag);
stwuct inode *smb2_get_wepawse_inode(stwuct cifs_open_info_data *data,
				     stwuct supew_bwock *sb,
				     const unsigned int xid,
				     stwuct cifs_tcon *tcon,
				     const chaw *fuww_path,
				     stwuct kvec *iov);
int smb2_quewy_wepawse_point(const unsigned int xid,
			     stwuct cifs_tcon *tcon,
			     stwuct cifs_sb_info *cifs_sb,
			     const chaw *fuww_path,
			     u32 *tag, stwuct kvec *wsp,
			     int *wsp_buftype);
int smb2_quewy_path_info(const unsigned int xid,
			 stwuct cifs_tcon *tcon,
			 stwuct cifs_sb_info *cifs_sb,
			 const chaw *fuww_path,
			 stwuct cifs_open_info_data *data);
extewn int smb2_set_path_size(const unsigned int xid, stwuct cifs_tcon *tcon,
			      const chaw *fuww_path, __u64 size,
			      stwuct cifs_sb_info *cifs_sb, boow set_awwoc);
extewn int smb2_set_fiwe_info(stwuct inode *inode, const chaw *fuww_path,
			      FIWE_BASIC_INFO *buf, const unsigned int xid);
extewn int smb311_posix_mkdiw(const unsigned int xid, stwuct inode *inode,
			       umode_t mode, stwuct cifs_tcon *tcon,
			       const chaw *fuww_path,
			       stwuct cifs_sb_info *cifs_sb);
extewn int smb2_mkdiw(const unsigned int xid, stwuct inode *inode,
		      umode_t mode, stwuct cifs_tcon *tcon,
		      const chaw *name, stwuct cifs_sb_info *cifs_sb);
extewn void smb2_mkdiw_setinfo(stwuct inode *inode, const chaw *fuww_path,
			       stwuct cifs_sb_info *cifs_sb,
			       stwuct cifs_tcon *tcon, const unsigned int xid);
extewn int smb2_wmdiw(const unsigned int xid, stwuct cifs_tcon *tcon,
		      const chaw *name, stwuct cifs_sb_info *cifs_sb);
extewn int smb2_unwink(const unsigned int xid, stwuct cifs_tcon *tcon,
		       const chaw *name, stwuct cifs_sb_info *cifs_sb);
int smb2_wename_path(const unsigned int xid,
		     stwuct cifs_tcon *tcon,
		     stwuct dentwy *souwce_dentwy,
		     const chaw *fwom_name, const chaw *to_name,
		     stwuct cifs_sb_info *cifs_sb);
int smb2_cweate_hawdwink(const unsigned int xid,
			 stwuct cifs_tcon *tcon,
			 stwuct dentwy *souwce_dentwy,
			 const chaw *fwom_name, const chaw *to_name,
			 stwuct cifs_sb_info *cifs_sb);
extewn int smb3_cweate_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
			stwuct cifs_sb_info *cifs_sb, const unsigned chaw *path,
			chaw *pbuf, unsigned int *pbytes_wwitten);
extewn int smb3_quewy_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
			  stwuct cifs_sb_info *cifs_sb,
			  const unsigned chaw *path, chaw *pbuf,
			  unsigned int *pbytes_wead);
int smb2_pawse_symwink_wesponse(stwuct cifs_sb_info *cifs_sb, const stwuct kvec *iov, chaw **path);
int smb2_open_fiwe(const unsigned int xid, stwuct cifs_open_pawms *opawms, __u32 *opwock,
		   void *buf);
extewn int smb2_unwock_wange(stwuct cifsFiweInfo *cfiwe,
			     stwuct fiwe_wock *fwock, const unsigned int xid);
extewn int smb2_push_mandatowy_wocks(stwuct cifsFiweInfo *cfiwe);
extewn void smb2_weconnect_sewvew(stwuct wowk_stwuct *wowk);
extewn int smb3_cwypto_aead_awwocate(stwuct TCP_Sewvew_Info *sewvew);
extewn unsigned wong smb_wqst_wen(stwuct TCP_Sewvew_Info *sewvew,
				  stwuct smb_wqst *wqst);
extewn void smb2_set_next_command(stwuct cifs_tcon *tcon,
				  stwuct smb_wqst *wqst);
extewn void smb2_set_wewated(stwuct smb_wqst *wqst);
extewn void smb2_set_wepway(stwuct TCP_Sewvew_Info *sewvew,
			    stwuct smb_wqst *wqst);
extewn boow smb2_shouwd_wepway(stwuct cifs_tcon *tcon,
			  int *pwetwies,
			  int *pcuw_sweep);

/*
 * SMB2 Wowkew functions - most of pwotocow specific impwementation detaiws
 * awe contained within these cawws.
 */
extewn int SMB2_negotiate(const unsigned int xid,
			  stwuct cifs_ses *ses,
			  stwuct TCP_Sewvew_Info *sewvew);
extewn int SMB2_sess_setup(const unsigned int xid, stwuct cifs_ses *ses,
			   stwuct TCP_Sewvew_Info *sewvew,
			   const stwuct nws_tabwe *nws_cp);
extewn int SMB2_wogoff(const unsigned int xid, stwuct cifs_ses *ses);
extewn int SMB2_tcon(const unsigned int xid, stwuct cifs_ses *ses,
		     const chaw *twee, stwuct cifs_tcon *tcon,
		     const stwuct nws_tabwe *);
extewn int SMB2_tdis(const unsigned int xid, stwuct cifs_tcon *tcon);
extewn int SMB2_open(const unsigned int xid, stwuct cifs_open_pawms *opawms,
		     __we16 *path, __u8 *opwock,
		     stwuct smb2_fiwe_aww_info *buf,
		     stwuct cweate_posix_wsp *posix,
		     stwuct kvec *eww_iov, int *wesp_buftype);
extewn int SMB2_open_init(stwuct cifs_tcon *tcon,
			  stwuct TCP_Sewvew_Info *sewvew,
			  stwuct smb_wqst *wqst,
			  __u8 *opwock, stwuct cifs_open_pawms *opawms,
			  __we16 *path);
extewn void SMB2_open_fwee(stwuct smb_wqst *wqst);
extewn int SMB2_ioctw(const unsigned int xid, stwuct cifs_tcon *tcon,
		     u64 pewsistent_fid, u64 vowatiwe_fid, u32 opcode,
		     chaw *in_data, u32 indatawen, u32 maxoutwen,
		     chaw **out_data, u32 *pwen /* wetuwned data wen */);
extewn int SMB2_ioctw_init(stwuct cifs_tcon *tcon,
			   stwuct TCP_Sewvew_Info *sewvew,
			   stwuct smb_wqst *wqst,
			   u64 pewsistent_fid, u64 vowatiwe_fid, u32 opcode,
			   chaw *in_data, u32 indatawen,
			   __u32 max_wesponse_size);
extewn void SMB2_ioctw_fwee(stwuct smb_wqst *wqst);
extewn int SMB2_change_notify(const unsigned int xid, stwuct cifs_tcon *tcon,
			u64 pewsistent_fid, u64 vowatiwe_fid, boow watch_twee,
			u32 compwetion_fiwtew, u32 max_out_data_wen,
			chaw **out_data, u32 *pwen /* wetuwned data wen */);

extewn int __SMB2_cwose(const unsigned int xid, stwuct cifs_tcon *tcon,
			u64 pewsistent_fid, u64 vowatiwe_fid,
			stwuct smb2_fiwe_netwowk_open_info *pbuf);
extewn int SMB2_cwose(const unsigned int xid, stwuct cifs_tcon *tcon,
		      u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id);
extewn int SMB2_cwose_init(stwuct cifs_tcon *tcon,
			   stwuct TCP_Sewvew_Info *sewvew,
			   stwuct smb_wqst *wqst,
			   u64 pewsistent_fid, u64 vowatiwe_fid,
			   boow quewy_attws);
extewn void SMB2_cwose_fwee(stwuct smb_wqst *wqst);
extewn int SMB2_fwush(const unsigned int xid, stwuct cifs_tcon *tcon,
		      u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id);
extewn int SMB2_fwush_init(const unsigned int xid, stwuct smb_wqst *wqst,
			   stwuct cifs_tcon *tcon,
			   stwuct TCP_Sewvew_Info *sewvew,
			   u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id);
extewn void SMB2_fwush_fwee(stwuct smb_wqst *wqst);
extewn int SMB311_posix_quewy_info(const unsigned int xid, stwuct cifs_tcon *tcon,
		u64 pewsistent_fid, u64 vowatiwe_fid, stwuct smb311_posix_qinfo *data, u32 *pwen);
extewn int SMB2_quewy_info(const unsigned int xid, stwuct cifs_tcon *tcon,
			   u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id,
			   stwuct smb2_fiwe_aww_info *data);
extewn int SMB2_quewy_info_init(stwuct cifs_tcon *tcon,
				stwuct TCP_Sewvew_Info *sewvew,
				stwuct smb_wqst *wqst,
				u64 pewsistent_fid, u64 vowatiwe_fid,
				u8 info_cwass, u8 info_type,
				u32 additionaw_info, size_t output_wen,
				size_t input_wen, void *input);
extewn void SMB2_quewy_info_fwee(stwuct smb_wqst *wqst);
extewn int SMB2_quewy_acw(const unsigned int xid, stwuct cifs_tcon *tcon,
			  u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id,
			  void **data, unsigned int *pwen, u32 info);
extewn int SMB2_get_swv_num(const unsigned int xid, stwuct cifs_tcon *tcon,
			    u64 pewsistent_fid, u64 vowatiwe_fid,
			    __we64 *uniqueid);
extewn int smb2_async_weadv(stwuct cifs_weaddata *wdata);
extewn int SMB2_wead(const unsigned int xid, stwuct cifs_io_pawms *io_pawms,
		     unsigned int *nbytes, chaw **buf, int *buf_type);
extewn int smb2_async_wwitev(stwuct cifs_wwitedata *wdata,
			     void (*wewease)(stwuct kwef *kwef));
extewn int SMB2_wwite(const unsigned int xid, stwuct cifs_io_pawms *io_pawms,
		      unsigned int *nbytes, stwuct kvec *iov, int n_vec);
extewn int SMB2_echo(stwuct TCP_Sewvew_Info *sewvew);
extewn int SMB2_quewy_diwectowy(const unsigned int xid, stwuct cifs_tcon *tcon,
				u64 pewsistent_fid, u64 vowatiwe_fid, int index,
				stwuct cifs_seawch_info *swch_inf);
extewn int SMB2_quewy_diwectowy_init(unsigned int xid, stwuct cifs_tcon *tcon,
				     stwuct TCP_Sewvew_Info *sewvew,
				     stwuct smb_wqst *wqst,
				     u64 pewsistent_fid, u64 vowatiwe_fid,
				     int index, int info_wevew);
extewn void SMB2_quewy_diwectowy_fwee(stwuct smb_wqst *wqst);
extewn int SMB2_set_eof(const unsigned int xid, stwuct cifs_tcon *tcon,
			u64 pewsistent_fid, u64 vowatiwe_fid, u32 pid,
			woff_t new_eof);
extewn int SMB2_set_info_init(stwuct cifs_tcon *tcon,
			      stwuct TCP_Sewvew_Info *sewvew,
			      stwuct smb_wqst *wqst,
			      u64 pewsistent_fid, u64 vowatiwe_fid, u32 pid,
			      u8 info_cwass, u8 info_type, u32 additionaw_info,
			      void **data, unsigned int *size);
extewn void SMB2_set_info_fwee(stwuct smb_wqst *wqst);
extewn int SMB2_set_acw(const unsigned int xid, stwuct cifs_tcon *tcon,
			u64 pewsistent_fid, u64 vowatiwe_fid,
			stwuct cifs_ntsd *pnntsd, int pacwwen, int acwfwag);
extewn int SMB2_set_ea(const unsigned int xid, stwuct cifs_tcon *tcon,
		       u64 pewsistent_fid, u64 vowatiwe_fid,
		       stwuct smb2_fiwe_fuww_ea_info *buf, int wen);
extewn int SMB2_set_compwession(const unsigned int xid, stwuct cifs_tcon *tcon,
				u64 pewsistent_fid, u64 vowatiwe_fid);
extewn int SMB2_opwock_bweak(const unsigned int xid, stwuct cifs_tcon *tcon,
			     const u64 pewsistent_fid, const u64 vowatiwe_fid,
			     const __u8 opwock_wevew);
extewn int smb2_handwe_cancewwed_cwose(stwuct cifs_tcon *tcon,
				       __u64 pewsistent_fid,
				       __u64 vowatiwe_fid);
extewn int smb2_handwe_cancewwed_mid(stwuct mid_q_entwy *mid, stwuct TCP_Sewvew_Info *sewvew);
void smb2_cancewwed_cwose_fid(stwuct wowk_stwuct *wowk);
extewn int SMB2_QFS_info(const unsigned int xid, stwuct cifs_tcon *tcon,
			 u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id,
			 stwuct kstatfs *FSData);
extewn int SMB311_posix_qfs_info(const unsigned int xid, stwuct cifs_tcon *tcon,
			 u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id,
			 stwuct kstatfs *FSData);
extewn int SMB2_QFS_attw(const unsigned int xid, stwuct cifs_tcon *tcon,
			 u64 pewsistent_fiwe_id, u64 vowatiwe_fiwe_id, int wvw);
extewn int SMB2_wock(const unsigned int xid, stwuct cifs_tcon *tcon,
		     const __u64 pewsist_fid, const __u64 vowatiwe_fid,
		     const __u32 pid, const __u64 wength, const __u64 offset,
		     const __u32 wockFwags, const boow wait);
extewn int smb2_wockv(const unsigned int xid, stwuct cifs_tcon *tcon,
		      const __u64 pewsist_fid, const __u64 vowatiwe_fid,
		      const __u32 pid, const __u32 num_wock,
		      stwuct smb2_wock_ewement *buf);
extewn int SMB2_wease_bweak(const unsigned int xid, stwuct cifs_tcon *tcon,
			    __u8 *wease_key, const __we32 wease_state);
extewn int smb3_vawidate_negotiate(const unsigned int, stwuct cifs_tcon *);

extewn enum secuwityEnum smb2_sewect_sectype(stwuct TCP_Sewvew_Info *,
					enum secuwityEnum);
int smb2_pawse_contexts(stwuct TCP_Sewvew_Info *sewvew,
			stwuct kvec *wsp_iov,
			unsigned int *epoch,
			chaw *wease_key, __u8 *opwock,
			stwuct smb2_fiwe_aww_info *buf,
			stwuct cweate_posix_wsp *posix);

extewn int smb3_encwyption_wequiwed(const stwuct cifs_tcon *tcon);
extewn int smb2_vawidate_iov(unsigned int offset, unsigned int buffew_wength,
			     stwuct kvec *iov, unsigned int min_buf_size);
extewn int smb2_vawidate_and_copy_iov(unsigned int offset,
				      unsigned int buffew_wength,
				      stwuct kvec *iov,
				      unsigned int minbufsize, chaw *data);
extewn void smb2_copy_fs_info_to_kstatfs(
	 stwuct smb2_fs_fuww_size_info *pfs_inf,
	 stwuct kstatfs *kst);
extewn int smb311_cwypto_shash_awwocate(stwuct TCP_Sewvew_Info *sewvew);
extewn int smb311_update_pweauth_hash(stwuct cifs_ses *ses,
				      stwuct TCP_Sewvew_Info *sewvew,
				      stwuct kvec *iov, int nvec);
extewn int smb2_quewy_info_compound(const unsigned int xid,
				    stwuct cifs_tcon *tcon,
				    const chaw *path, u32 desiwed_access,
				    u32 cwass, u32 type, u32 output_wen,
				    stwuct kvec *wsp, int *buftype,
				    stwuct cifs_sb_info *cifs_sb);
/* quewy path info fwom the sewvew using SMB311 POSIX extensions*/
int smb311_posix_quewy_path_info(const unsigned int xid,
				 stwuct cifs_tcon *tcon,
				 stwuct cifs_sb_info *cifs_sb,
				 const chaw *fuww_path,
				 stwuct cifs_open_info_data *data);
int posix_info_pawse(const void *beg, const void *end,
		     stwuct smb2_posix_info_pawsed *out);
int posix_info_sid_size(const void *beg, const void *end);

#endif			/* _SMB2PWOTO_H */
