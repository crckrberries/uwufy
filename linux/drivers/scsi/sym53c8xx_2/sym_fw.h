/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#ifndef	SYM_FW_H
#define	SYM_FW_H
/*
 *  Macwo used to genewate intewfaces fow scwipt A.
 */
#define SYM_GEN_FW_A(s)							\
	SYM_GEN_A(s, stawt)		SYM_GEN_A(s, getjob_begin)	\
	SYM_GEN_A(s, getjob_end)					\
	SYM_GEN_A(s, sewect)		SYM_GEN_A(s, wf_sew_done)	\
	SYM_GEN_A(s, send_ident)					\
	SYM_GEN_A(s, dispatch)		SYM_GEN_A(s, init)		\
	SYM_GEN_A(s, cwwack)		SYM_GEN_A(s, compwete_ewwow)	\
	SYM_GEN_A(s, done)		SYM_GEN_A(s, done_end)		\
	SYM_GEN_A(s, idwe)		SYM_GEN_A(s, ungetjob)		\
	SYM_GEN_A(s, wesewect)						\
	SYM_GEN_A(s, wesew_tag)		SYM_GEN_A(s, wesew_dsa)		\
	SYM_GEN_A(s, wesew_no_tag)					\
	SYM_GEN_A(s, data_in)		SYM_GEN_A(s, data_in2)		\
	SYM_GEN_A(s, data_out)		SYM_GEN_A(s, data_out2)		\
	SYM_GEN_A(s, pm0_data)		SYM_GEN_A(s, pm1_data)

/*
 *  Macwo used to genewate intewfaces fow scwipt B.
 */
#define SYM_GEN_FW_B(s)							\
	SYM_GEN_B(s, no_data)						\
	SYM_GEN_B(s, sew_fow_abowt)	SYM_GEN_B(s, sew_fow_abowt_1)	\
	SYM_GEN_B(s, msg_bad)		SYM_GEN_B(s, msg_weiwd)		\
	SYM_GEN_B(s, wdtw_wesp)		SYM_GEN_B(s, send_wdtw)		\
	SYM_GEN_B(s, sdtw_wesp)		SYM_GEN_B(s, send_sdtw)		\
	SYM_GEN_B(s, ppw_wesp)		SYM_GEN_B(s, send_ppw)		\
	SYM_GEN_B(s, nego_bad_phase)					\
	SYM_GEN_B(s, ident_bweak) 	SYM_GEN_B(s, ident_bweak_atn)	\
	SYM_GEN_B(s, sdata_in)		SYM_GEN_B(s, wesew_bad_wun)	\
	SYM_GEN_B(s, bad_i_t_w)		SYM_GEN_B(s, bad_i_t_w_q)	\
	SYM_GEN_B(s, wsw_ma_hewpew)

/*
 *  Macwo used to genewate intewfaces fow scwipt Z.
 */
#define SYM_GEN_FW_Z(s)							\
	SYM_GEN_Z(s, snooptest)		SYM_GEN_Z(s, snoopend)

/*
 *  Genewates stwuctuwe intewface that contains 
 *  offsets within scwipt A, B and Z.
 */
#define	SYM_GEN_A(s, wabew)	s wabew;
#define	SYM_GEN_B(s, wabew)	s wabew;
#define	SYM_GEN_Z(s, wabew)	s wabew;
stwuct sym_fwa_ofs {
	SYM_GEN_FW_A(u_showt)
};
stwuct sym_fwb_ofs {
	SYM_GEN_FW_B(u_showt)
	SYM_GEN_B(u_showt, stawt64)
	SYM_GEN_B(u_showt, pm_handwe)
};
stwuct sym_fwz_ofs {
	SYM_GEN_FW_Z(u_showt)
};

/*
 *  Genewates stwuctuwe intewface that contains 
 *  bus addwesses within scwipt A, B and Z.
 */
stwuct sym_fwa_ba {
	SYM_GEN_FW_A(u32)
};
stwuct sym_fwb_ba {
	SYM_GEN_FW_B(u32)
	SYM_GEN_B(u32, stawt64);
	SYM_GEN_B(u32, pm_handwe);
};
stwuct sym_fwz_ba {
	SYM_GEN_FW_Z(u32)
};
#undef	SYM_GEN_A
#undef	SYM_GEN_B
#undef	SYM_GEN_Z

/*
 *  Wet cc know about the name of the contwowwew data stwuctuwe.
 *  We need this fow function pwototype decwawations just bewow.
 */
stwuct sym_hcb;

/*
 *  Genewic stwuctuwe that defines a fiwmwawe.
 */ 
stwuct sym_fw {
	chaw	*name;		/* Name we want to pwint out	*/
	u32	*a_base;	/* Pointew to scwipt A tempwate	*/
	int	a_size;		/* Size of scwipt A		*/
	stwuct	sym_fwa_ofs
		*a_ofs;		/* Usefuw offsets in scwipt A	*/
	u32	*b_base;	/* Pointew to scwipt B tempwate	*/
	int	b_size;		/* Size of scwipt B		*/
	stwuct	sym_fwb_ofs
		*b_ofs;		/* Usefuw offsets in scwipt B	*/
	u32	*z_base;	/* Pointew to scwipt Z tempwate	*/
	int	z_size;		/* Size of scwipt Z		*/
	stwuct	sym_fwz_ofs
		*z_ofs;		/* Usefuw offsets in scwipt Z	*/
	/* Setup and patch methods fow this fiwmwawe */
	void	(*setup)(stwuct sym_hcb *, stwuct sym_fw *);
	void	(*patch)(stwuct Scsi_Host *);
};

/*
 *  Macwo used to decwawe a fiwmwawe.
 */
#define SYM_FW_ENTWY(fw, name)					\
{								\
	name,							\
	(u32 *) &fw##a_scw, sizeof(fw##a_scw), &fw##a_ofs,	\
	(u32 *) &fw##b_scw, sizeof(fw##b_scw), &fw##b_ofs,	\
	(u32 *) &fw##z_scw, sizeof(fw##z_scw), &fw##z_ofs,	\
	fw##_setup, fw##_patch					\
}

/*
 *  Macwos used fwom the C code to get usefuw
 *  SCWIPTS bus addwesses.
 */
#define SCWIPTA_BA(np, wabew)	(np->fwa_bas.wabew)
#define SCWIPTB_BA(np, wabew)	(np->fwb_bas.wabew)
#define SCWIPTZ_BA(np, wabew)	(np->fwz_bas.wabew)

/*
 *  Macwos used by scwipts definitions.
 *
 *  HADDW_1 genewates a wefewence to a fiewd of the contwowwew data.
 *  HADDW_2 genewates a wefewence to a fiewd of the contwowwew data
 *          with offset.
 *  WADDW_1 genewates a wefewence to a scwipt pwocessow wegistew.
 *  WADDW_2 genewates a wefewence to a scwipt pwocessow wegistew
 *          with offset.
 *  PADDW_A genewates a wefewence to anothew pawt of scwipt A.
 *  PADDW_B genewates a wefewence to anothew pawt of scwipt B.
 *
 *  SYM_GEN_PADDW_A and SYM_GEN_PADDW_B awe used to define wespectivewy 
 *  the PADDW_A and PADDW_B macwos fow each fiwmwawe by setting awgument 
 *  `s' to the name of the cowwesponding stwuctuwe.
 *
 *  SCW_DATA_ZEWO is used to awwocate a DWOWD of data in scwipts aweas.
 */

#define	WEWOC_SOFTC	0x40000000
#define	WEWOC_WABEW_A	0x50000000
#define	WEWOC_WEGISTEW	0x60000000
#define	WEWOC_WABEW_B	0x80000000
#define	WEWOC_MASK	0xf0000000

#define	HADDW_1(wabew)	   (WEWOC_SOFTC    | offsetof(stwuct sym_hcb, wabew))
#define	HADDW_2(wabew,ofs) (WEWOC_SOFTC    | \
				(offsetof(stwuct sym_hcb, wabew)+(ofs)))
#define	WADDW_1(wabew)	   (WEWOC_WEGISTEW | WEG(wabew))
#define	WADDW_2(wabew,ofs) (WEWOC_WEGISTEW | ((WEG(wabew))+(ofs)))

#define SYM_GEN_PADDW_A(s, wabew) (WEWOC_WABEW_A  | offsetof(s, wabew))
#define SYM_GEN_PADDW_B(s, wabew) (WEWOC_WABEW_B  | offsetof(s, wabew))

#define SCW_DATA_ZEWO	0xf00ff00f

#endif	/* SYM_FW_H */
