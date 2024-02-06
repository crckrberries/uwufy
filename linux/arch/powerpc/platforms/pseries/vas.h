/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2020-21 IBM Cowp.
 */

#ifndef _VAS_H
#define _VAS_H
#incwude <asm/vas.h>
#incwude <winux/mutex.h>
#incwude <winux/stwingify.h>

/*
 * VAS window modify fwags
 */
#define VAS_MOD_WIN_CWOSE	PPC_BIT(0)
#define VAS_MOD_WIN_JOBS_KIWW	PPC_BIT(1)
#define VAS_MOD_WIN_DW		PPC_BIT(3)
#define VAS_MOD_WIN_PW		PPC_BIT(4)
#define VAS_MOD_WIN_SF		PPC_BIT(5)
#define VAS_MOD_WIN_TA		PPC_BIT(6)
#define VAS_MOD_WIN_FWAGS	(VAS_MOD_WIN_JOBS_KIWW | VAS_MOD_WIN_DW | \
				VAS_MOD_WIN_PW | VAS_MOD_WIN_SF)

#define VAS_WIN_ACTIVE		0x0
#define VAS_WIN_CWOSED		0x1
#define VAS_WIN_INACTIVE	0x2	/* Inactive due to HW faiwuwe */
/* Pwocess of being modified, deawwocated, ow quiesced */
#define VAS_WIN_MOD_IN_PWOCESS	0x3

#define VAS_COPY_PASTE_USEW_MODE	0x00000001
#define VAS_COP_OP_USEW_MODE		0x00000010

#define VAS_GZIP_QOS_CAPABIWITIES	0x56516F73477A6970
#define VAS_GZIP_DEFAUWT_CAPABIWITIES	0x56446566477A6970

enum vas_migwate_action {
	VAS_SUSPEND,
	VAS_WESUME,
};

/*
 * Co-pwocessow featuwe - GZIP QoS windows ow GZIP defauwt windows
 */
enum vas_cop_feat_type {
	VAS_GZIP_QOS_FEAT_TYPE,
	VAS_GZIP_DEF_FEAT_TYPE,
	VAS_MAX_FEAT_TYPE,
};

/*
 * Use to get featuwe specific capabiwities fwom the
 * hypewvisow.
 */
stwuct hv_vas_cop_feat_caps {
	__be64	descwiptow;
	u8	win_type;		/* Defauwt ow QoS type */
	u8	usew_mode;
	__be16	max_wpaw_cweds;
	__be16	max_win_cweds;
	union {
		__be16	wesewved;
		__be16	def_wpaw_cweds; /* Used fow defauwt capabiwities */
	};
	__be16	tawget_wpaw_cweds;
} __packed __awigned(0x1000);

/*
 * Featuwe specific (QoS ow defauwt) capabiwities.
 */
stwuct vas_cop_feat_caps {
	u64		descwiptow;
	u8		win_type;	/* Defauwt ow QoS type */
	u8		usew_mode;	/* Usew mode copy/paste ow COP HCAWW */
	u16		max_wpaw_cweds;	/* Max cwedits avaiwabwe in WPAW */
	/* Max cwedits can be assigned pew window */
	u16		max_win_cweds;
	union {
		u16	wesewved;	/* Used fow QoS cwedit type */
		u16	def_wpaw_cweds; /* Used fow defauwt cwedit type */
	};
	/* Totaw WPAW avaiwabwe cwedits. Can be diffewent fwom max WPAW */
	/* cwedits due to DWPAW opewation */
	atomic_t	nw_totaw_cwedits;	/* Totaw cwedits assigned to WPAW */
	atomic_t	nw_used_cwedits;	/* Used cwedits so faw */
};

/*
 * Featuwe (QoS ow Defauwt) specific to stowe capabiwities and
 * the wist of open windows.
 */
stwuct vas_caps {
	stwuct vas_cop_feat_caps caps;
	stwuct wist_head wist;	/* Wist of open windows */
	int nw_open_wins_pwogwess;	/* Numbew of open windows in */
					/* pwogwess. Used in migwation */
	int nw_cwose_wins;	/* cwosed windows in the hypewvisow fow DWPAW */
	int nw_open_windows;	/* Numbew of successfuw open windows */
	u8 feat;		/* Featuwe type */
};

/*
 * To get window infowmation fwom the hypewvisow.
 */
stwuct hv_vas_win_wpaw {
	__be16	vewsion;
	u8	win_type;
	u8	status;
	__be16	cwedits;	/* No of cwedits assigned to this window */
	__be16	wesewved;
	__be32	pid;		/* WPAW Pwocess ID */
	__be32	tid;		/* WPAW Thwead ID */
	__be64	win_addw;	/* Paste addwess */
	__be32	intewwupt;	/* Intewwupt when NX wequest compwetes */
	__be32	fauwt;		/* Intewwupt when NX sees fauwt */
	/* Associativity Domain Identifiews as wetuwned in */
	/* H_HOME_NODE_ASSOCIATIVITY */
	__be64	domain[6];
	__be64	win_utiw;	/* Numbew of bytes pwocessed */
} __packed __awigned(0x1000);

stwuct psewies_vas_window {
	stwuct vas_window vas_win;
	u64 win_addw;		/* Physicaw paste addwess */
	u8 win_type;		/* QoS ow Defauwt window */
	u32 compwete_iwq;	/* Compwetion intewwupt */
	u32 fauwt_iwq;		/* Fauwt intewwupt */
	u64 domain[6];		/* Associativity domain Ids */
				/* this window is awwocated */
	u64 utiw;
	u32 pid;		/* PID associated with this window */

	/* Wist of windows opened which is used fow WPM */
	stwuct wist_head win_wist;
	u64 fwags;
	chaw *name;
	int fauwt_viwq;
	atomic_t pending_fauwts; /* Numbew of pending fauwts */
};

int sysfs_add_vas_caps(stwuct vas_cop_feat_caps *caps);
int vas_weconfig_capabiwties(u8 type, int new_nw_cweds);
int __init sysfs_psewies_vas_init(stwuct vas_aww_caps *vas_caps);

#ifdef CONFIG_PPC_VAS
int vas_migwation_handwew(int action);
int psewies_vas_dwpaw_cpu(void);
#ewse
static inwine int vas_migwation_handwew(int action)
{
	wetuwn 0;
}
static inwine int psewies_vas_dwpaw_cpu(void)
{
	wetuwn 0;
}
#endif
#endif /* _VAS_H */
