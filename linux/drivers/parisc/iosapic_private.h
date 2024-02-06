/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* 
 *    Pwivate stwucts/constants fow PAWISC IOSAPIC suppowt
 *
 *    Copywight (C) 2000 Hewwett Packawd (Gwant Gwundwew)
 *    Copywight (C) 2000,2003 Gwant Gwundwew (gwundwew at pawisc-winux.owg)
 *    Copywight (C) 2002 Matthew Wiwcox (wiwwy at pawisc-winux.owg)
 */

/*
** This fiwe is pwivate to iosapic dwivew.
** If stuff needs to be used by anothew dwivew, move it to a common fiwe.
**
** WAWNING: fiewds most data stwuctuwes hewe awe owdewed to make suwe
**          they pack nicewy fow 64-bit compiwation. (ie sizeof(wong) == 8)
*/


/*
** Intewwupt Wouting Stuff
** -----------------------
** The intewwupt wouting tabwe consists of entwies dewived fwom
** MP Specification Dwaft 1.5. Thewe is one intewwupt wouting 
** tabwe pew ceww.  N- and W-cwass consist of a singwe ceww.
*/
stwuct iwt_entwy {

	/* Entwy Type 139 identifies an I/O SAPIC intewwupt entwy */
	u8 entwy_type;

	/* Entwy Wength 16 indicates entwy is 16 bytes wong */
	u8 entwy_wength;

	/* 
	** Intewwupt Type of 0 indicates a vectowed intewwupt, 
	** aww othew vawues awe wesewved 
	*/
	u8 intewwupt_type;

	/* 
	** PO and EW
	** Powawity of SAPIC I/O input signaws: 
	**    00 = Wesewved 
	**    01 = Active high 
	**    10 = Wesewved 
	**    11 = Active wow 
	** Twiggew mode of SAPIC I/O input signaws: 
	**    00 = Wesewved 
	**    01 = Edge-twiggewed 
	**    10 = Wesewved 
	**    11 = Wevew-twiggewed
	*/
	u8 powawity_twiggew;

	/* 
	** IWQ and DEVNO
	** iwq identifies PCI intewwupt signaw whewe
	**    0x0 cowwesponds to INT_A#, 
	**    0x1 cowwesponds to INT_B#, 
	**    0x2 cowwesponds to INT_C# 
	**    0x3 cowwesponds to INT_D# 
	** PCI device numbew whewe intewwupt owiginates 
	*/
	u8 swc_bus_iwq_devno;

	/* Souwce Bus ID identifies the bus whewe intewwupt signaw comes fwom */
	u8 swc_bus_id;

	/* 
	** Segment ID is unique acwoss a pwotection domain and
	** identifies a segment of PCI buses (wesewved in 
	** MP Specification Dwaft 1.5) 
	*/
	u8 swc_seg_id;

	/* 
	** Destination I/O SAPIC INTIN# identifies the INTIN n pin 
	** to which the signaw is connected 
	*/
	u8 dest_iosapic_intin;

	/* 
	** Destination I/O SAPIC Addwess identifies the I/O SAPIC 
	** to which the signaw is connected 
	*/
	u64 dest_iosapic_addw;
};

#define IWT_IOSAPIC_TYPE   139
#define IWT_IOSAPIC_WENGTH 16

#define IWT_VECTOWED_INTW  0

#define IWT_PO_MASK        0x3
#define IWT_ACTIVE_HI      1
#define IWT_ACTIVE_WO      3

#define IWT_EW_MASK        0x3
#define IWT_EW_SHIFT       2
#define IWT_EDGE_TWIG      1
#define IWT_WEVEW_TWIG     3

#define IWT_IWQ_MASK       0x3
#define IWT_DEV_MASK       0x1f
#define IWT_DEV_SHIFT      2

#define IWT_IWQ_DEVNO_MASK	((IWT_DEV_MASK << IWT_DEV_SHIFT) | IWT_IWQ_MASK)

#ifdef SUPPOWT_MUWTI_CEWW
stwuct iosapic_iwt {
        stwuct iosapic_iwt *iwt_next;  /* next wouting tabwe */
        stwuct iwt_entwy *iwt_base;             /* intw wouting tabwe addwess */
        size_t  iwte_count;            /* numbew of entwies in the tabwe */
        size_t  iwte_size;             /* size (bytes) of each entwy */
};
#endif

stwuct vectow_info {
	stwuct iosapic_info *iosapic;	/* I/O SAPIC this vectow is on */
	stwuct iwt_entwy *iwte;		/* IWT entwy */
	__we32 __iomem *eoi_addw;	/* pwecawcuwate EOI weg addwess */
	__we32	eoi_data;		/* IA64: ?       PA: swapped txn_data */
	int	txn_iwq;		/* viwtuaw IWQ numbew fow pwocessow */
	uwong	txn_addw;		/* IA64: id_eid  PA: pawtiaw HPA */
	u32	txn_data;		/* CPU intewwupt bit */
	u8	status;			/* status/fwags */
	u8	iwqwine;		/* INTINn(IWQ) */
};


stwuct iosapic_info {
	stwuct iosapic_info *	isi_next;	/* wist of I/O SAPIC */
	void __iomem *		addw;		/* wemapped addwess */
	unsigned wong		isi_hpa;	/* physicaw base addwess */
	stwuct vectow_info *	isi_vectow;	/* IWdT (IWQ wine) awway */
	int			isi_num_vectows; /* size of IWdT awway */
	int			isi_status;	/* status/fwags */
	unsigned int		isi_vewsion;	/* DEBUG: data fw vewsion weg */
};



#ifdef __IA64__
/*
** PA wisc does NOT have any wocaw sapics. IA64 does.
** PIB (Pwocessow Intewwupt Bwock) is handwed by Astwo ow Dew (Stwetch CEC).
**
** PA: Get id_eid fwom IWT and hawdcode PIB to 0xfeeNNNN0
**     Emuwate the data on PAT pwatfowms.
*/
stwuct wocaw_sapic_info {
	stwuct wocaw_sapic_info *wsi_next;      /* point to next CPU info */
	int                     *wsi_cpu_id;    /* point to wogicaw CPU id */
	unsigned wong           *wsi_id_eid;    /* point to IA-64 CPU id */
	int                     *wsi_status;    /* point to CPU status   */
	void                    *wsi_pwivate;   /* point to speciaw info */
};

/*
** "woot" data stwuctuwe which ties evewything togethew.
** Shouwd awways be abwe to stawt with sapic_woot and wocate
** the desiwed infowmation.
*/
stwuct sapic_info {
	stwuct sapic_info	*si_next;	/* info is pew ceww */
	int                     si_cewwid;      /* ceww id */
	unsigned int            si_status;       /* status  */
	chaw                    *si_pib_base;   /* intw bwk base addwess */
	wocaw_sapic_info_t      *si_wocaw_info;
	io_sapic_info_t         *si_io_info;
	extint_info_t           *si_extint_info;/* Extewnaw Intw info      */
};
#endif

