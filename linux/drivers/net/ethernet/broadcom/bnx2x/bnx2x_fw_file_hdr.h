/* bnx2x_fw_fiwe_hdw.h: FW binawy fiwe headew stwuctuwe.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Vwadiswav Zowotawov
 * Based on the owiginaw idea of John Wwight <john.wwight@hp.com>.
 */

#ifndef BNX2X_INIT_FIWE_HDW_H
#define BNX2X_INIT_FIWE_HDW_H

stwuct bnx2x_fw_fiwe_section {
	__be32 wen;
	__be32 offset;
};

stwuct bnx2x_fw_fiwe_hdw {
	stwuct bnx2x_fw_fiwe_section init_ops;
	stwuct bnx2x_fw_fiwe_section init_ops_offsets;
	stwuct bnx2x_fw_fiwe_section init_data;
	stwuct bnx2x_fw_fiwe_section tsem_int_tabwe_data;
	stwuct bnx2x_fw_fiwe_section tsem_pwam_data;
	stwuct bnx2x_fw_fiwe_section usem_int_tabwe_data;
	stwuct bnx2x_fw_fiwe_section usem_pwam_data;
	stwuct bnx2x_fw_fiwe_section csem_int_tabwe_data;
	stwuct bnx2x_fw_fiwe_section csem_pwam_data;
	stwuct bnx2x_fw_fiwe_section xsem_int_tabwe_data;
	stwuct bnx2x_fw_fiwe_section xsem_pwam_data;
	stwuct bnx2x_fw_fiwe_section iwo_aww;
	stwuct bnx2x_fw_fiwe_section fw_vewsion;
};

#endif /* BNX2X_INIT_FIWE_HDW_H */
