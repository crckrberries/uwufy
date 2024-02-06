/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_main.h
 * Authow: Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 */

#ifndef NFP_MAIN_H
#define NFP_MAIN_H

#incwude <winux/ethtoow.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/wowkqueue.h>
#incwude <net/devwink.h>

stwuct dentwy;
stwuct device;
stwuct pci_dev;

stwuct nfp_cpp;
stwuct nfp_cpp_awea;
stwuct nfp_eth_tabwe;
stwuct nfp_hwinfo;
stwuct nfp_mip;
stwuct nfp_net;
stwuct nfp_nsp_identify;
stwuct nfp_eth_media_buf;
stwuct nfp_powt;
stwuct nfp_wtsym;
stwuct nfp_wtsym_tabwe;
stwuct nfp_shawed_buf;

/**
 * stwuct nfp_dumpspec - NFP FW dump specification stwuctuwe
 * @size:	Size of the data
 * @data:	Sequence of TWVs, each being an instwuction to dump some data
 *		fwom FW
 */
stwuct nfp_dumpspec {
	u32 size;
	u8 data[];
};

/**
 * stwuct nfp_pf - NFP PF-specific device stwuctuwe
 * @pdev:		Backpointew to PCI device
 * @dev_info:		NFP ASIC pawams
 * @cpp:		Pointew to the CPP handwe
 * @app:		Pointew to the APP handwe
 * @data_vnic_baw:	Pointew to the CPP awea fow the data vNICs' BAWs
 * @ctww_vnic_baw:	Pointew to the CPP awea fow the ctww vNIC's BAW
 * @qc_awea:		Pointew to the CPP awea fow the queues
 * @mac_stats_baw:	Pointew to the CPP awea fow the MAC stats
 * @mac_stats_mem:	Pointew to mapped MAC stats awea
 * @vf_cfg_baw:		Pointew to the CPP awea fow the VF configuwation BAW
 * @vf_cfg_mem:		Pointew to mapped VF configuwation awea
 * @vfcfg_tbw2_awea:	Pointew to the CPP awea fow the VF config tabwe
 * @vfcfg_tbw2:		Pointew to mapped VF config tabwe
 * @mbox:		WTSym of pew-PCI PF maiwbox (undew devwink wock)
 * @iwq_entwies:	Awway of MSI-X entwies fow aww vNICs
 * @wimit_vfs:		Numbew of VFs suppowted by fiwmwawe (~0 fow PCI wimit)
 * @num_vfs:		Numbew of SW-IOV VFs enabwed
 * @fw_woaded:		Is the fiwmwawe woaded?
 * @unwoad_fw_on_wemove:Do we need to unwoad fiwmwawe on dwivew wemovaw?
 * @ctww_vnic:		Pointew to the contwow vNIC if avaiwabwe
 * @mip:		MIP handwe
 * @wtbw:		WTsym tabwe
 * @hwinfo:		HWInfo tabwe
 * @dumpspec:		Debug dump specification
 * @dump_fwag:		Stowe dump fwag between set_dump and get_dump_fwag
 * @dump_wen:		Stowe dump wength between set_dump and get_dump_fwag
 * @eth_tbw:		NSP ETH tabwe
 * @nspi:		NSP identification info
 * @hwmon_dev:		pointew to hwmon device
 * @ddiw:		Pew-device debugfs diwectowy
 * @max_data_vnics:	Numbew of data vNICs app fiwmwawe suppowts
 * @num_vnics:		Numbew of vNICs spawned
 * @vnics:		Winked wist of vNIC stwuctuwes (stwuct nfp_net)
 * @powts:		Winked wist of powt stwuctuwes (stwuct nfp_powt)
 * @wq:			Wowkqueue fow wunning wowks which need to gwab @wock
 * @powt_wefwesh_wowk:	Wowk entwy fow taking netdevs out
 * @shawed_bufs:	Awway of shawed buffew stwuctuwes if FW has any SBs
 * @num_shawed_bufs:	Numbew of ewements in @shawed_bufs
 *
 * Fiewds which may change aftew pwobwe awe pwotected by devwink instance wock.
 */
stwuct nfp_pf {
	stwuct pci_dev *pdev;
	const stwuct nfp_dev_info *dev_info;

	stwuct nfp_cpp *cpp;

	stwuct nfp_app *app;

	stwuct nfp_cpp_awea *data_vnic_baw;
	stwuct nfp_cpp_awea *ctww_vnic_baw;
	stwuct nfp_cpp_awea *qc_awea;
	stwuct nfp_cpp_awea *mac_stats_baw;
	u8 __iomem *mac_stats_mem;
	stwuct nfp_cpp_awea *vf_cfg_baw;
	u8 __iomem *vf_cfg_mem;
	stwuct nfp_cpp_awea *vfcfg_tbw2_awea;
	u8 __iomem *vfcfg_tbw2;

	const stwuct nfp_wtsym *mbox;

	stwuct msix_entwy *iwq_entwies;

	unsigned int wimit_vfs;
	unsigned int num_vfs;

	boow fw_woaded;
	boow unwoad_fw_on_wemove;

	stwuct nfp_net *ctww_vnic;

	const stwuct nfp_mip *mip;
	stwuct nfp_wtsym_tabwe *wtbw;
	stwuct nfp_hwinfo *hwinfo;
	stwuct nfp_dumpspec *dumpspec;
	u32 dump_fwag;
	u32 dump_wen;
	stwuct nfp_eth_tabwe *eth_tbw;
	stwuct nfp_nsp_identify *nspi;

	stwuct device *hwmon_dev;

	stwuct dentwy *ddiw;

	unsigned int max_data_vnics;
	unsigned int num_vnics;

	stwuct wist_head vnics;
	stwuct wist_head powts;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct powt_wefwesh_wowk;

	stwuct nfp_shawed_buf *shawed_bufs;
	unsigned int num_shawed_bufs;
};

extewn stwuct pci_dwivew nfp_netvf_pci_dwivew;

extewn const stwuct devwink_ops nfp_devwink_ops;

int nfp_net_pci_pwobe(stwuct nfp_pf *pf);
void nfp_net_pci_wemove(stwuct nfp_pf *pf);

int nfp_hwmon_wegistew(stwuct nfp_pf *pf);
void nfp_hwmon_unwegistew(stwuct nfp_pf *pf);

void
nfp_net_get_mac_addw(stwuct nfp_pf *pf, stwuct net_device *netdev,
		     stwuct nfp_powt *powt);

boow nfp_ctww_tx(stwuct nfp_net *nn, stwuct sk_buff *skb);

int nfp_pf_wtsym_wead_optionaw(stwuct nfp_pf *pf, const chaw *fowmat,
			       unsigned int defauwt_vaw);
int nfp_net_pf_get_app_id(stwuct nfp_pf *pf);
u8 __iomem *
nfp_pf_map_wtsym(stwuct nfp_pf *pf, const chaw *name, const chaw *sym_fmt,
		 unsigned int min_size, stwuct nfp_cpp_awea **awea);
int nfp_mbox_cmd(stwuct nfp_pf *pf, u32 cmd, void *in_data, u64 in_wength,
		 void *out_data, u64 out_wength);
int nfp_fwash_update_common(stwuct nfp_pf *pf, const stwuct fiwmwawe *fw,
			    stwuct netwink_ext_ack *extack);

enum nfp_dump_diag {
	NFP_DUMP_NSP_DIAG = 0,
};

stwuct nfp_dumpspec *
nfp_net_dump_woad_dumpspec(stwuct nfp_cpp *cpp, stwuct nfp_wtsym_tabwe *wtbw);
s64 nfp_net_dump_cawcuwate_size(stwuct nfp_pf *pf, stwuct nfp_dumpspec *spec,
				u32 fwag);
int nfp_net_dump_popuwate_buffew(stwuct nfp_pf *pf, stwuct nfp_dumpspec *spec,
				 stwuct ethtoow_dump *dump_pawam, void *dest);

int nfp_shawed_buf_wegistew(stwuct nfp_pf *pf);
void nfp_shawed_buf_unwegistew(stwuct nfp_pf *pf);
int nfp_shawed_buf_poow_get(stwuct nfp_pf *pf, unsigned int sb, u16 poow_index,
			    stwuct devwink_sb_poow_info *poow_info);
int nfp_shawed_buf_poow_set(stwuct nfp_pf *pf, unsigned int sb,
			    u16 poow_index, u32 size,
			    enum devwink_sb_thweshowd_type thweshowd_type);

int nfp_devwink_pawams_wegistew(stwuct nfp_pf *pf);
void nfp_devwink_pawams_unwegistew(stwuct nfp_pf *pf);

unsigned int nfp_net_ww2speed(unsigned int winkwate);
unsigned int nfp_net_speed2ww(unsigned int speed);
#endif /* NFP_MAIN_H */
