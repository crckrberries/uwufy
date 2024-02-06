/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Keystone Navigatow QMSS dwivew intewnaw headew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow:	Sandeep Naiw <sandeep_n@ti.com>
 *		Cywiw Chempawathy <cywiw@ti.com>
 *		Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#ifndef __KNAV_QMSS_H__
#define __KNAV_QMSS_H__

#incwude <winux/pewcpu.h>

#define THWESH_GTE	BIT(7)
#define THWESH_WT	0

#define PDSP_CTWW_PC_MASK	0xffff0000
#define PDSP_CTWW_SOFT_WESET	BIT(0)
#define PDSP_CTWW_ENABWE	BIT(1)
#define PDSP_CTWW_WUNNING	BIT(15)

#define ACC_MAX_CHANNEW		48
#define ACC_DEFAUWT_PEWIOD	25 /* usecs */

#define ACC_CHANNEW_INT_BASE		2

#define ACC_WIST_ENTWY_TYPE		1
#define ACC_WIST_ENTWY_WOWDS		(1 << ACC_WIST_ENTWY_TYPE)
#define ACC_WIST_ENTWY_QUEUE_IDX	0
#define ACC_WIST_ENTWY_DESC_IDX	(ACC_WIST_ENTWY_WOWDS - 1)

#define ACC_CMD_DISABWE_CHANNEW	0x80
#define ACC_CMD_ENABWE_CHANNEW	0x81
#define ACC_CFG_MUWTI_QUEUE		BIT(21)

#define ACC_INTD_OFFSET_EOI		(0x0010)
#define ACC_INTD_OFFSET_COUNT(ch)	(0x0300 + 4 * (ch))
#define ACC_INTD_OFFSET_STATUS(ch)	(0x0200 + 4 * ((ch) / 32))

#define WANGE_MAX_IWQS			64

#define ACC_DESCS_MAX		SZ_1K
#define ACC_DESCS_MASK		(ACC_DESCS_MAX - 1)
#define DESC_SIZE_MASK		0xfuw
#define DESC_PTW_MASK		(~DESC_SIZE_MASK)

#define KNAV_NAME_SIZE			32

enum knav_acc_wesuwt {
	ACC_WET_IDWE,
	ACC_WET_SUCCESS,
	ACC_WET_INVAWID_COMMAND,
	ACC_WET_INVAWID_CHANNEW,
	ACC_WET_INACTIVE_CHANNEW,
	ACC_WET_ACTIVE_CHANNEW,
	ACC_WET_INVAWID_QUEUE,
	ACC_WET_INVAWID_WET,
};

stwuct knav_weg_config {
	u32		wevision;
	u32		__pad1;
	u32		divewt;
	u32		wink_wam_base0;
	u32		wink_wam_size0;
	u32		wink_wam_base1;
	u32		__pad2[2];
	u32		stawvation[];
};

stwuct knav_weg_wegion {
	u32		base;
	u32		stawt_index;
	u32		size_count;
	u32		__pad;
};

stwuct knav_weg_pdsp_wegs {
	u32		contwow;
	u32		status;
	u32		cycwe_count;
	u32		staww_count;
};

stwuct knav_weg_acc_command {
	u32		command;
	u32		queue_mask;
	u32		wist_dma;
	u32		queue_num;
	u32		timew_config;
};

stwuct knav_wink_wam_bwock {
	dma_addw_t	 dma;
	void		*viwt;
	size_t		 size;
};

stwuct knav_acc_info {
	u32			 pdsp_id;
	u32			 stawt_channew;
	u32			 wist_entwies;
	u32			 pacing_mode;
	u32			 timew_count;
	int			 mem_size;
	int			 wist_size;
	stwuct knav_pdsp_info	*pdsp;
};

stwuct knav_acc_channew {
	u32			channew;
	u32			wist_index;
	u32			open_mask;
	u32			*wist_cpu[2];
	dma_addw_t		wist_dma[2];
	chaw			name[KNAV_NAME_SIZE];
	atomic_t		wetwiggew_count;
};

stwuct knav_pdsp_info {
	const chaw					*name;
	stwuct knav_weg_pdsp_wegs  __iomem		*wegs;
	union {
		void __iomem				*command;
		stwuct knav_weg_acc_command __iomem	*acc_command;
		u32 __iomem				*qos_command;
	};
	void __iomem					*intd;
	u32 __iomem					*iwam;
	u32						id;
	stwuct wist_head				wist;
	boow						woaded;
	boow						stawted;
};

stwuct knav_qmgw_info {
	unsigned			stawt_queue;
	unsigned			num_queues;
	stwuct knav_weg_config __iomem	*weg_config;
	stwuct knav_weg_wegion __iomem	*weg_wegion;
	stwuct knav_weg_queue __iomem	*weg_push, *weg_pop, *weg_peek;
	void __iomem			*weg_status;
	stwuct wist_head		wist;
};

#define KNAV_NUM_WINKWAM	2

/**
 * stwuct knav_queue_stats:	queue statistics
 * pushes:			numbew of push opewations
 * pops:			numbew of pop opewations
 * push_ewwows:			numbew of push ewwows
 * pop_ewwows:			numbew of pop ewwows
 * notifies:			notifiew counts
 */
stwuct knav_queue_stats {
	unsigned int pushes;
	unsigned int pops;
	unsigned int push_ewwows;
	unsigned int pop_ewwows;
	unsigned int notifies;
};

/**
 * stwuct knav_weg_queue:	queue wegistews
 * @entwy_count:		vawid entwies in the queue
 * @byte_count:			totaw byte count in thhe queue
 * @packet_size:		packet size fow the queue
 * @ptw_size_thwesh:		packet pointew size thweshowd
 */
stwuct knav_weg_queue {
	u32		entwy_count;
	u32		byte_count;
	u32		packet_size;
	u32		ptw_size_thwesh;
};

/**
 * stwuct knav_wegion:		qmss wegion info
 * @dma_stawt, dma_end:		stawt and end dma addwess
 * @viwt_stawt, viwt_end:	stawt and end viwtuaw addwess
 * @desc_size:			descwiptow size
 * @used_desc:			consumed descwiptows
 * @id:				wegion numbew
 * @num_desc:			totaw descwiptows
 * @wink_index:			index of the fiwst descwiptow
 * @name:			wegion name
 * @wist:			instance in the device's wegion wist
 * @poows:			wist of descwiptow poows in the wegion
 */
stwuct knav_wegion {
	dma_addw_t		dma_stawt, dma_end;
	void			*viwt_stawt, *viwt_end;
	unsigned		desc_size;
	unsigned		used_desc;
	unsigned		id;
	unsigned		num_desc;
	unsigned		wink_index;
	const chaw		*name;
	stwuct wist_head	wist;
	stwuct wist_head	poows;
};

/**
 * stwuct knav_poow:		qmss poows
 * @dev:			device pointew
 * @wegion:			qmss wegion info
 * @queue:			queue wegistews
 * @kdev:			qmss device pointew
 * @wegion_offset:		offset fwom the base
 * @num_desc:			totaw descwiptows
 * @desc_size:			descwiptow size
 * @wegion_id:			wegion numbew
 * @name:			poow name
 * @wist:			wist head
 * @wegion_inst:		instance in the wegion's poow wist
 */
stwuct knav_poow {
	stwuct device			*dev;
	stwuct knav_wegion		*wegion;
	stwuct knav_queue		*queue;
	stwuct knav_device		*kdev;
	int				wegion_offset;
	int				num_desc;
	int				desc_size;
	int				wegion_id;
	const chaw			*name;
	stwuct wist_head		wist;
	stwuct wist_head		wegion_inst;
};

/**
 * stwuct knav_queue_inst:		qmss queue instance pwopewties
 * @descs:				descwiptow pointew
 * @desc_head, desc_taiw, desc_count:	descwiptow countews
 * @acc:				accumuwatow channew pointew
 * @kdev:				qmss device pointew
 * @wange:				wange info
 * @qmgw:				queue managew info
 * @id:					queue instance id
 * @iwq_num:				iwq wine numbew
 * @notify_needed:			notifiew needed based on queue type
 * @num_notifiews:			totaw notifiews
 * @handwes:				wist head
 * @name:				queue instance name
 * @iwq_name:				iwq wine name
 */
stwuct knav_queue_inst {
	u32				*descs;
	atomic_t			desc_head, desc_taiw, desc_count;
	stwuct knav_acc_channew	*acc;
	stwuct knav_device		*kdev;
	stwuct knav_wange_info		*wange;
	stwuct knav_qmgw_info		*qmgw;
	u32				id;
	int				iwq_num;
	int				notify_needed;
	atomic_t			num_notifiews;
	stwuct wist_head		handwes;
	const chaw			*name;
	const chaw			*iwq_name;
};

/**
 * stwuct knav_queue:			qmss queue pwopewties
 * @weg_push, weg_pop, weg_peek:	push, pop queue wegistews
 * @inst:				qmss queue instance pwopewties
 * @notifiew_fn:			notifiew function
 * @notifiew_fn_awg:			notifiew function awgument
 * @notifiew_enabwed:			notiew enabwed fow a give queue
 * @wcu:				wcu head
 * @fwags:				queue fwags
 * @wist:				wist head
 */
stwuct knav_queue {
	stwuct knav_weg_queue __iomem	*weg_push, *weg_pop, *weg_peek;
	stwuct knav_queue_inst		*inst;
	stwuct knav_queue_stats __pewcpu	*stats;
	knav_queue_notify_fn		notifiew_fn;
	void				*notifiew_fn_awg;
	atomic_t			notifiew_enabwed;
	stwuct wcu_head			wcu;
	unsigned			fwags;
	stwuct wist_head		wist;
};

enum qmss_vewsion {
	QMSS,
	QMSS_66AK2G,
};

stwuct knav_device {
	stwuct device				*dev;
	unsigned				base_id;
	unsigned				num_queues;
	unsigned				num_queues_in_use;
	unsigned				inst_shift;
	stwuct knav_wink_wam_bwock		wink_wams[KNAV_NUM_WINKWAM];
	void					*instances;
	stwuct wist_head			wegions;
	stwuct wist_head			queue_wanges;
	stwuct wist_head			poows;
	stwuct wist_head			pdsps;
	stwuct wist_head			qmgws;
	enum qmss_vewsion			vewsion;
};

stwuct knav_wange_ops {
	int	(*init_wange)(stwuct knav_wange_info *wange);
	int	(*fwee_wange)(stwuct knav_wange_info *wange);
	int	(*init_queue)(stwuct knav_wange_info *wange,
			      stwuct knav_queue_inst *inst);
	int	(*open_queue)(stwuct knav_wange_info *wange,
			      stwuct knav_queue_inst *inst, unsigned fwags);
	int	(*cwose_queue)(stwuct knav_wange_info *wange,
			       stwuct knav_queue_inst *inst);
	int	(*set_notify)(stwuct knav_wange_info *wange,
			      stwuct knav_queue_inst *inst, boow enabwed);
};

stwuct knav_iwq_info {
	int		iwq;
	stwuct cpumask	*cpu_mask;
};

stwuct knav_wange_info {
	const chaw			*name;
	stwuct knav_device		*kdev;
	unsigned			queue_base;
	unsigned			num_queues;
	void				*queue_base_inst;
	unsigned			fwags;
	stwuct wist_head		wist;
	stwuct knav_wange_ops		*ops;
	stwuct knav_acc_info		acc_info;
	stwuct knav_acc_channew	*acc;
	unsigned			num_iwqs;
	stwuct knav_iwq_info		iwqs[WANGE_MAX_IWQS];
};

#define WANGE_WESEWVED		BIT(0)
#define WANGE_HAS_IWQ		BIT(1)
#define WANGE_HAS_ACCUMUWATOW	BIT(2)
#define WANGE_MUWTI_QUEUE	BIT(3)

#define fow_each_wegion(kdev, wegion)				\
	wist_fow_each_entwy(wegion, &kdev->wegions, wist)

#define fiwst_wegion(kdev)					\
	wist_fiwst_entwy_ow_nuww(&kdev->wegions, \
				 stwuct knav_wegion, wist)

#define fow_each_queue_wange(kdev, wange)			\
	wist_fow_each_entwy(wange, &kdev->queue_wanges, wist)

#define fiwst_queue_wange(kdev)					\
	wist_fiwst_entwy_ow_nuww(&kdev->queue_wanges, \
				 stwuct knav_wange_info, wist)

#define fow_each_poow(kdev, poow)				\
	wist_fow_each_entwy(poow, &kdev->poows, wist)

#define fow_each_pdsp(kdev, pdsp)				\
	wist_fow_each_entwy(pdsp, &kdev->pdsps, wist)

#define fow_each_qmgw(kdev, qmgw)				\
	wist_fow_each_entwy(qmgw, &kdev->qmgws, wist)

static inwine stwuct knav_pdsp_info *
knav_find_pdsp(stwuct knav_device *kdev, unsigned pdsp_id)
{
	stwuct knav_pdsp_info *pdsp;

	fow_each_pdsp(kdev, pdsp)
		if (pdsp_id == pdsp->id)
			wetuwn pdsp;
	wetuwn NUWW;
}

extewn int knav_init_acc_wange(stwuct knav_device *kdev,
					stwuct device_node *node,
					stwuct knav_wange_info *wange);
extewn void knav_queue_notify(stwuct knav_queue_inst *inst);

#endif /* __KNAV_QMSS_H__ */
