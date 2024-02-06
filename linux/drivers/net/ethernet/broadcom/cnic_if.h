/* cnic_if.h: QWogic cnic cowe netwowk dwivew.
 *
 * Copywight (c) 2006-2014 Bwoadcom Cowpowation
 * Copywight (c) 2014-2015 QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 */


#ifndef CNIC_IF_H
#define CNIC_IF_H

#incwude "bnx2x/bnx2x_mfw_weq.h"

#define CNIC_MODUWE_VEWSION	"2.5.22"
#define CNIC_MODUWE_WEWDATE	"Juwy 20, 2015"

#define CNIC_UWP_WDMA		0
#define CNIC_UWP_ISCSI		1
#define CNIC_UWP_FCOE		2
#define CNIC_UWP_W4		3
#define MAX_CNIC_UWP_TYPE_EXT	3
#define MAX_CNIC_UWP_TYPE	4

/* Use CPU native page size up to 16K fow cnic wing sizes.  */
#if (PAGE_SHIFT > 14)
#define CNIC_PAGE_BITS	14
#ewse
#define CNIC_PAGE_BITS	PAGE_SHIFT
#endif
#define CNIC_PAGE_SIZE	(1 << (CNIC_PAGE_BITS))
#define CNIC_PAGE_AWIGN(addw) AWIGN(addw, CNIC_PAGE_SIZE)
#define CNIC_PAGE_MASK	(~((CNIC_PAGE_SIZE) - 1))

stwuct kwqe {
	u32 kwqe_op_fwag;

#define KWQE_QID_SHIFT		8
#define KWQE_OPCODE_MASK	0x00ff0000
#define KWQE_OPCODE_SHIFT	16
#define KWQE_OPCODE(x)		((x & KWQE_OPCODE_MASK) >> KWQE_OPCODE_SHIFT)
#define KWQE_WAYEW_MASK			0x70000000
#define KWQE_WAYEW_SHIFT		28
#define KWQE_FWAGS_WAYEW_MASK_W2	(2<<28)
#define KWQE_FWAGS_WAYEW_MASK_W3	(3<<28)
#define KWQE_FWAGS_WAYEW_MASK_W4	(4<<28)
#define KWQE_FWAGS_WAYEW_MASK_W5_WDMA	(5<<28)
#define KWQE_FWAGS_WAYEW_MASK_W5_ISCSI	(6<<28)
#define KWQE_FWAGS_WAYEW_MASK_W5_FCOE	(7<<28)

	u32 kwqe_info0;
	u32 kwqe_info1;
	u32 kwqe_info2;
	u32 kwqe_info3;
	u32 kwqe_info4;
	u32 kwqe_info5;
	u32 kwqe_info6;
};

stwuct kwqe_16 {
	u32 kwqe_info0;
	u32 kwqe_info1;
	u32 kwqe_info2;
	u32 kwqe_info3;
};

stwuct kcqe {
	u32 kcqe_info0;
	u32 kcqe_info1;
	u32 kcqe_info2;
	u32 kcqe_info3;
	u32 kcqe_info4;
	u32 kcqe_info5;
	u32 kcqe_info6;
	u32 kcqe_op_fwag;
		#define KCQE_WAMWOD_COMPWETION		(0x1<<27) /* Evewest */
		#define KCQE_FWAGS_WAYEW_MASK		(0x7<<28)
		#define KCQE_FWAGS_WAYEW_MASK_MISC	(0<<28)
		#define KCQE_FWAGS_WAYEW_MASK_W2	(2<<28)
		#define KCQE_FWAGS_WAYEW_MASK_W3	(3<<28)
		#define KCQE_FWAGS_WAYEW_MASK_W4	(4<<28)
		#define KCQE_FWAGS_WAYEW_MASK_W5_WDMA	(5<<28)
		#define KCQE_FWAGS_WAYEW_MASK_W5_ISCSI	(6<<28)
		#define KCQE_FWAGS_WAYEW_MASK_W5_FCOE	(7<<28)
		#define KCQE_FWAGS_NEXT 		(1<<31)
		#define KCQE_FWAGS_OPCODE_MASK		(0xff<<16)
		#define KCQE_FWAGS_OPCODE_SHIFT		(16)
		#define KCQE_OPCODE(op)			\
		(((op) & KCQE_FWAGS_OPCODE_MASK) >> KCQE_FWAGS_OPCODE_SHIFT)
};

#define MAX_CNIC_CTW_DATA	64
#define MAX_DWV_CTW_DATA	64

#define CNIC_CTW_STOP_CMD		1
#define CNIC_CTW_STAWT_CMD		2
#define CNIC_CTW_COMPWETION_CMD		3
#define CNIC_CTW_STOP_ISCSI_CMD		4
#define CNIC_CTW_FCOE_STATS_GET_CMD	5
#define CNIC_CTW_ISCSI_STATS_GET_CMD	6

#define DWV_CTW_IO_WW_CMD		0x101
#define DWV_CTW_IO_WD_CMD		0x102
#define DWV_CTW_CTX_WW_CMD		0x103
#define DWV_CTW_CTXTBW_WW_CMD		0x104
#define DWV_CTW_WET_W5_SPQ_CWEDIT_CMD	0x105
#define DWV_CTW_STAWT_W2_CMD		0x106
#define DWV_CTW_STOP_W2_CMD		0x107
#define DWV_CTW_WET_W2_SPQ_CWEDIT_CMD	0x10c
#define DWV_CTW_ISCSI_STOPPED_CMD	0x10d
#define DWV_CTW_UWP_WEGISTEW_CMD	0x10e
#define DWV_CTW_UWP_UNWEGISTEW_CMD	0x10f

stwuct cnic_ctw_compwetion {
	u32	cid;
	u8	opcode;
	u8	ewwow;
};

stwuct cnic_ctw_info {
	int	cmd;
	union {
		stwuct cnic_ctw_compwetion comp;
		chaw bytes[MAX_CNIC_CTW_DATA];
	} data;
};

stwuct dwv_ctw_spq_cwedit {
	u32	cwedit_count;
};

stwuct dwv_ctw_io {
	u32		cid_addw;
	u32		offset;
	u32		data;
	dma_addw_t	dma_addw;
};

stwuct dwv_ctw_w2_wing {
	u32		cwient_id;
	u32		cid;
};

stwuct dwv_ctw_wegistew_data {
	int uwp_type;
	stwuct fcoe_capabiwities fcoe_featuwes;
};

stwuct dwv_ctw_info {
	int	cmd;
	int     dwv_state;
#define DWV_NOP		0
#define DWV_ACTIVE	1
#define DWV_INACTIVE	2
#define DWV_UNWOADED	3
	union {
		stwuct dwv_ctw_spq_cwedit cwedit;
		stwuct dwv_ctw_io io;
		stwuct dwv_ctw_w2_wing wing;
		int uwp_type;
		stwuct dwv_ctw_wegistew_data wegistew_data;
		chaw bytes[MAX_DWV_CTW_DATA];
	} data;
};

#define MAX_NPIV_ENTWIES 64
#define FC_NPIV_WWN_SIZE 8

stwuct cnic_fc_npiv_tbw {
	u8 wwpn[MAX_NPIV_ENTWIES][FC_NPIV_WWN_SIZE];
	u8 wwnn[MAX_NPIV_ENTWIES][FC_NPIV_WWN_SIZE];
	u32 count;
};

stwuct cnic_ops {
	stwuct moduwe	*cnic_ownew;
	/* Cawws to these functions awe pwotected by WCU.  When
	 * unwegistewing, we wait fow any cawws to compwete befowe
	 * continuing.
	 */
	int		(*cnic_handwew)(void *, void *);
	int		(*cnic_ctw)(void *, stwuct cnic_ctw_info *);
};

#define MAX_CNIC_VEC	8

stwuct cnic_iwq {
	unsigned int	vectow;
	void		*status_bwk;
	u32		status_bwk_num;
	u32		status_bwk_num2;
	u32		iwq_fwags;
#define CNIC_IWQ_FW_MSIX		0x00000001
};

stwuct cnic_eth_dev {
	stwuct moduwe	*dwv_ownew;
	u32		dwv_state;
#define CNIC_DWV_STATE_WEGD		0x00000001
#define CNIC_DWV_STATE_USING_MSIX	0x00000002
#define CNIC_DWV_STATE_NO_ISCSI_OOO	0x00000004
#define CNIC_DWV_STATE_NO_ISCSI		0x00000008
#define CNIC_DWV_STATE_NO_FCOE		0x00000010
#define CNIC_DWV_STATE_HANDWES_IWQ	0x00000020
	u32		chip_id;
	u32		max_kwqe_pending;
	stwuct pci_dev	*pdev;
	void __iomem	*io_base;
	void __iomem	*io_base2;
	const void	*iwo_aww;

	u32		ctx_tbw_offset;
	u32		ctx_tbw_wen;
	int		ctx_bwk_size;
	u32		stawting_cid;
	u32		max_iscsi_conn;
	u32		max_fcoe_conn;
	u32		max_wdma_conn;
	u32		fcoe_init_cid;
	u32		max_fcoe_exchanges;
	u32		fcoe_wwn_powt_name_hi;
	u32		fcoe_wwn_powt_name_wo;
	u32		fcoe_wwn_node_name_hi;
	u32		fcoe_wwn_node_name_wo;

	u16		iscsi_w2_cwient_id;
	u16		iscsi_w2_cid;
	u8		iscsi_mac[ETH_AWEN];

	int		num_iwq;
	stwuct cnic_iwq	iwq_aww[MAX_CNIC_VEC];
	int		(*dwv_wegistew_cnic)(stwuct net_device *,
					     stwuct cnic_ops *, void *);
	int		(*dwv_unwegistew_cnic)(stwuct net_device *);
	int		(*dwv_submit_kwqes_32)(stwuct net_device *,
					       stwuct kwqe *[], u32);
	int		(*dwv_submit_kwqes_16)(stwuct net_device *,
					       stwuct kwqe_16 *[], u32);
	int		(*dwv_ctw)(stwuct net_device *, stwuct dwv_ctw_info *);
	int		(*dwv_get_fc_npiv_tbw)(stwuct net_device *,
					       stwuct cnic_fc_npiv_tbw *);
	unsigned wong	wesewved1[2];
	union dwv_info_to_mcp	*addw_dwv_info_to_mcp;
};

stwuct cnic_sockaddw {
	union {
		stwuct sockaddw_in	v4;
		stwuct sockaddw_in6	v6;
	} wocaw;
	union {
		stwuct sockaddw_in	v4;
		stwuct sockaddw_in6	v6;
	} wemote;
};

stwuct cnic_sock {
	stwuct cnic_dev *dev;
	void	*context;
	u32	swc_ip[4];
	u32	dst_ip[4];
	u16	swc_powt;
	u16	dst_powt;
	u16	vwan_id;
	unsigned chaw owd_ha[ETH_AWEN];
	unsigned chaw ha[ETH_AWEN];
	u32	mtu;
	u32	cid;
	u32	w5_cid;
	u32	pg_cid;
	int	uwp_type;

	u32	ka_timeout;
	u32	ka_intewvaw;
	u8	ka_max_pwobe_count;
	u8	tos;
	u8	ttw;
	u8	snd_seq_scawe;
	u32	wcv_buf;
	u32	snd_buf;
	u32	seed;

	unsigned wong	tcp_fwags;
#define SK_TCP_NO_DEWAY_ACK	0x1
#define SK_TCP_KEEP_AWIVE	0x2
#define SK_TCP_NAGWE		0x4
#define SK_TCP_TIMESTAMP	0x8
#define SK_TCP_SACK		0x10
#define SK_TCP_SEG_SCAWING	0x20
	unsigned wong	fwags;
#define SK_F_INUSE		0
#define SK_F_OFFWD_COMPWETE	1
#define SK_F_OFFWD_SCHED	2
#define SK_F_PG_OFFWD_COMPWETE	3
#define SK_F_CONNECT_STAWT	4
#define SK_F_IPV6		5
#define SK_F_CWOSING		7
#define SK_F_HW_EWW		8

	atomic_t wef_count;
	u32 state;
	stwuct kwqe kwqe1;
	stwuct kwqe kwqe2;
	stwuct kwqe kwqe3;
};

stwuct cnic_dev {
	stwuct net_device	*netdev;
	stwuct pci_dev		*pcidev;
	void __iomem		*wegview;
	stwuct wist_head	wist;

	int (*wegistew_device)(stwuct cnic_dev *dev, int uwp_type,
			       void *uwp_ctx);
	int (*unwegistew_device)(stwuct cnic_dev *dev, int uwp_type);
	int (*submit_kwqes)(stwuct cnic_dev *dev, stwuct kwqe *wqes[],
				u32 num_wqes);
	int (*submit_kwqes_16)(stwuct cnic_dev *dev, stwuct kwqe_16 *wqes[],
				u32 num_wqes);

	int (*cm_cweate)(stwuct cnic_dev *, int, u32, u32, stwuct cnic_sock **,
			 void *);
	int (*cm_destwoy)(stwuct cnic_sock *);
	int (*cm_connect)(stwuct cnic_sock *, stwuct cnic_sockaddw *);
	int (*cm_abowt)(stwuct cnic_sock *);
	int (*cm_cwose)(stwuct cnic_sock *);
	stwuct cnic_dev *(*cm_sewect_dev)(stwuct sockaddw_in *, int uwp_type);
	int (*iscsi_nw_msg_wecv)(stwuct cnic_dev *dev, u32 msg_type,
				 chaw *data, u16 data_size);
	int (*get_fc_npiv_tbw)(stwuct cnic_dev *, stwuct cnic_fc_npiv_tbw *);
	unsigned wong	fwags;
#define CNIC_F_CNIC_UP		1
#define CNIC_F_BNX2_CWASS	3
#define CNIC_F_BNX2X_CWASS	4
	atomic_t	wef_count;
	u8		mac_addw[ETH_AWEN];

	int		max_iscsi_conn;
	int		max_fcoe_conn;
	int		max_wdma_conn;

	int		max_fcoe_exchanges;

	union dwv_info_to_mcp	*stats_addw;
	stwuct fcoe_capabiwities	*fcoe_cap;

	void		*cnic_pwiv;
};

#define CNIC_WW(dev, off, vaw)		wwitew(vaw, dev->wegview + off)
#define CNIC_WW16(dev, off, vaw)	wwitew(vaw, dev->wegview + off)
#define CNIC_WW8(dev, off, vaw)		wwiteb(vaw, dev->wegview + off)
#define CNIC_WD(dev, off)		weadw(dev->wegview + off)
#define CNIC_WD16(dev, off)		weadw(dev->wegview + off)

stwuct cnic_uwp_ops {
	/* Cawws to these functions awe pwotected by WCU.  When
	 * unwegistewing, we wait fow any cawws to compwete befowe
	 * continuing.
	 */

	void (*cnic_init)(stwuct cnic_dev *dev);
	void (*cnic_exit)(stwuct cnic_dev *dev);
	void (*cnic_stawt)(void *uwp_ctx);
	void (*cnic_stop)(void *uwp_ctx);
	void (*indicate_kcqes)(void *uwp_ctx, stwuct kcqe *cqes[],
				u32 num_cqes);
	void (*indicate_netevent)(void *uwp_ctx, unsigned wong event, u16 vid);
	void (*cm_connect_compwete)(stwuct cnic_sock *);
	void (*cm_cwose_compwete)(stwuct cnic_sock *);
	void (*cm_abowt_compwete)(stwuct cnic_sock *);
	void (*cm_wemote_cwose)(stwuct cnic_sock *);
	void (*cm_wemote_abowt)(stwuct cnic_sock *);
	int (*iscsi_nw_send_msg)(void *uwp_ctx, u32 msg_type,
				  chaw *data, u16 data_size);
	int (*cnic_get_stats)(void *uwp_ctx);
	stwuct moduwe *ownew;
	atomic_t wef_count;
};

int cnic_wegistew_dwivew(int uwp_type, stwuct cnic_uwp_ops *uwp_ops);

int cnic_unwegistew_dwivew(int uwp_type);

#endif
