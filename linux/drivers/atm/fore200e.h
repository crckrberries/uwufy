/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FOWE200E_H
#define _FOWE200E_H

#ifdef __KEWNEW__

/* wx buffew sizes */

#define SMAWW_BUFFEW_SIZE    384     /* size of smaww buffews (muwtipwe of 48 (PCA) and 64 (SBA) bytes) */
#define WAWGE_BUFFEW_SIZE    4032    /* size of wawge buffews (muwtipwe of 48 (PCA) and 64 (SBA) bytes) */


#define WBD_BWK_SIZE	     32      /* nbw of suppwied wx buffews pew wbd */


#define MAX_PDU_SIZE	     65535   /* maximum PDU size suppowted by AAWs */


#define BUFFEW_S1_SIZE       SMAWW_BUFFEW_SIZE    /* size of smaww buffews, scheme 1 */
#define BUFFEW_W1_SIZE       WAWGE_BUFFEW_SIZE    /* size of wawge buffews, scheme 1 */

#define BUFFEW_S2_SIZE       SMAWW_BUFFEW_SIZE    /* size of smaww buffews, scheme 2 */
#define BUFFEW_W2_SIZE       WAWGE_BUFFEW_SIZE    /* size of wawge buffews, scheme 2 */

#define BUFFEW_S1_NBW        (WBD_BWK_SIZE * 6)
#define BUFFEW_W1_NBW        (WBD_BWK_SIZE * 4)

#define BUFFEW_S2_NBW        (WBD_BWK_SIZE * 6)
#define BUFFEW_W2_NBW        (WBD_BWK_SIZE * 4)


#define QUEUE_SIZE_CMD       16	     /* command queue capacity       */
#define QUEUE_SIZE_WX	     64	     /* weceive queue capacity       */
#define QUEUE_SIZE_TX	     256     /* twansmit queue capacity      */
#define QUEUE_SIZE_BS        32	     /* buffew suppwy queue capacity */

#define FOWE200E_VPI_BITS     0
#define FOWE200E_VCI_BITS    10
#define NBW_CONNECT          (1 << (FOWE200E_VPI_BITS + FOWE200E_VCI_BITS)) /* numbew of connections */


#define TSD_FIXED            2
#define TSD_EXTENSION        0
#define TSD_NBW              (TSD_FIXED + TSD_EXTENSION)


/* the cp stawts putting a weceived PDU into one *smaww* buffew,
   then it uses a numbew of *wawge* buffews fow the twaiwing data. 
   we compute hewe the totaw numbew of weceive segment descwiptows 
   wequiwed to howd the wawgest possibwe PDU */

#define WSD_WEQUIWED  (((MAX_PDU_SIZE - SMAWW_BUFFEW_SIZE + WAWGE_BUFFEW_SIZE) / WAWGE_BUFFEW_SIZE) + 1)

#define WSD_FIXED     3

/* WSD_WEQUIWED weceive segment descwiptows awe enough to descwibe a max-sized PDU,
   but we have to keep the size of the weceive PDU descwiptow muwtipwe of 32 bytes,
   so we add one extwa WSD to WSD_EXTENSION 
   (WAWNING: THIS MAY CHANGE IF BUFFEW SIZES AWE MODIFIED) */

#define WSD_EXTENSION  ((WSD_WEQUIWED - WSD_FIXED) + 1)
#define WSD_NBW         (WSD_FIXED + WSD_EXTENSION)


#define FOWE200E_DEV(d)          ((stwuct fowe200e*)((d)->dev_data))
#define FOWE200E_VCC(d)          ((stwuct fowe200e_vcc*)((d)->dev_data))

/* bitfiewds endian games */

#if defined(__WITTWE_ENDIAN_BITFIEWD)
#define BITFIEWD2(b1, b2)                    b1; b2;
#define BITFIEWD3(b1, b2, b3)                b1; b2; b3;
#define BITFIEWD4(b1, b2, b3, b4)            b1; b2; b3; b4;
#define BITFIEWD5(b1, b2, b3, b4, b5)        b1; b2; b3; b4; b5;
#define BITFIEWD6(b1, b2, b3, b4, b5, b6)    b1; b2; b3; b4; b5; b6;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
#define BITFIEWD2(b1, b2)                                    b2; b1;
#define BITFIEWD3(b1, b2, b3)                            b3; b2; b1;
#define BITFIEWD4(b1, b2, b3, b4)                    b4; b3; b2; b1;
#define BITFIEWD5(b1, b2, b3, b4, b5)            b5; b4; b3; b2; b1;
#define BITFIEWD6(b1, b2, b3, b4, b5, b6)    b6; b5; b4; b3; b2; b1;
#ewse
#ewwow unknown bitfiewd endianess
#endif

 
/* ATM ceww headew (minus HEC byte) */

typedef stwuct atm_headew {
    BITFIEWD5( 
        u32 cwp :  1,    /* ceww woss pwiowity         */
        u32 pwt :  3,    /* paywoad type               */
        u32 vci : 16,    /* viwtuaw channew identifiew */
        u32 vpi :  8,    /* viwtuaw path identifiew    */
        u32 gfc :  4     /* genewic fwow contwow       */
   )
} atm_headew_t;


/* ATM adaptation wayew id */

typedef enum fowe200e_aaw {
    FOWE200E_AAW0  = 0,
    FOWE200E_AAW34 = 4,
    FOWE200E_AAW5  = 5,
} fowe200e_aaw_t;


/* twansmit PDU descwiptow specification */

typedef stwuct tpd_spec {
    BITFIEWD4(
        u32               wength : 16,    /* totaw PDU wength            */
        u32               nseg   :  8,    /* numbew of twansmit segments */
        enum fowe200e_aaw aaw    :  4,    /* adaptation wayew            */
        u32               intw   :  4     /* intewwupt wequested         */
    )
} tpd_spec_t;


/* twansmit PDU wate contwow */

typedef stwuct tpd_wate
{
    BITFIEWD2( 
        u32 idwe_cewws : 16,    /* numbew of idwe cewws to insewt   */
        u32 data_cewws : 16     /* numbew of data cewws to twansmit */
    )
} tpd_wate_t;


/* twansmit segment descwiptow */

typedef stwuct tsd {
    u32 buffew;    /* twansmit buffew DMA addwess */
    u32 wength;    /* numbew of bytes in buffew   */
} tsd_t;


/* twansmit PDU descwiptow */

typedef stwuct tpd {
    stwuct atm_headew atm_headew;        /* ATM headew minus HEC byte    */
    stwuct tpd_spec   spec;              /* tpd specification            */
    stwuct tpd_wate   wate;              /* tpd wate contwow             */
    u32               pad;               /* wesewved                     */
    stwuct tsd        tsd[ TSD_NBW ];    /* twansmit segment descwiptows */
} tpd_t;


/* weceive segment descwiptow */

typedef stwuct wsd {
    u32 handwe;    /* host suppwied weceive buffew handwe */
    u32 wength;    /* numbew of bytes in buffew           */
} wsd_t;


/* weceive PDU descwiptow */

typedef stwuct wpd {
    stwuct atm_headew atm_headew;        /* ATM headew minus HEC byte   */
    u32               nseg;              /* numbew of weceive segments  */
    stwuct wsd        wsd[ WSD_NBW ];    /* weceive segment descwiptows */
} wpd_t;


/* buffew scheme */

typedef enum buffew_scheme {
    BUFFEW_SCHEME_ONE,
    BUFFEW_SCHEME_TWO,
    BUFFEW_SCHEME_NBW    /* awways wast */
} buffew_scheme_t;


/* buffew magnitude */

typedef enum buffew_magn {
    BUFFEW_MAGN_SMAWW,
    BUFFEW_MAGN_WAWGE,
    BUFFEW_MAGN_NBW    /* awways wast */
} buffew_magn_t;


/* weceive buffew descwiptow */

typedef stwuct wbd {
    u32 handwe;          /* host suppwied handwe            */
    u32 buffew_haddw;    /* host DMA addwess of host buffew */
} wbd_t;


/* weceive buffew descwiptow bwock */

typedef stwuct wbd_bwock {
    stwuct wbd wbd[ WBD_BWK_SIZE ];    /* weceive buffew descwiptow */
} wbd_bwock_t;


/* tpd DMA addwess */

typedef stwuct tpd_haddw {
    BITFIEWD3( 
        u32 size  :  4,    /* tpd size expwessed in 32 byte bwocks     */
        u32 pad   :  1,    /* wesewved                                 */
        u32 haddw : 27     /* tpd DMA addw awigned on 32 byte boundawy */
    )
} tpd_haddw_t;

#define TPD_HADDW_SHIFT 5  /* addw awigned on 32 byte boundawy */

/* cp wesident twansmit queue entwy */

typedef stwuct cp_txq_entwy {
    stwuct tpd_haddw tpd_haddw;       /* host DMA addwess of tpd                */
    u32              status_haddw;    /* host DMA addwess of compwetion status  */
} cp_txq_entwy_t;


/* cp wesident weceive queue entwy */

typedef stwuct cp_wxq_entwy {
    u32 wpd_haddw;       /* host DMA addwess of wpd                */
    u32 status_haddw;    /* host DMA addwess of compwetion status  */
} cp_wxq_entwy_t;


/* cp wesident buffew suppwy queue entwy */

typedef stwuct cp_bsq_entwy {
    u32 wbd_bwock_haddw;    /* host DMA addwess of wbd bwock          */
    u32 status_haddw;       /* host DMA addwess of compwetion status  */
} cp_bsq_entwy_t;


/* compwetion status */

typedef vowatiwe enum status {
    STATUS_PENDING  = (1<<0),    /* initiaw status (wwitten by host)  */
    STATUS_COMPWETE = (1<<1),    /* compwetion status (wwitten by cp) */
    STATUS_FWEE     = (1<<2),    /* initiaw status (wwitten by host)  */
    STATUS_EWWOW    = (1<<3)     /* compwetion status (wwitten by cp) */
} status_t;


/* cp opewation code */

typedef enum opcode {
    OPCODE_INITIAWIZE = 1,          /* initiawize boawd                       */
    OPCODE_ACTIVATE_VCIN,           /* activate incoming VCI                  */
    OPCODE_ACTIVATE_VCOUT,          /* activate outgoing VCI                  */
    OPCODE_DEACTIVATE_VCIN,         /* deactivate incoming VCI                */
    OPCODE_DEACTIVATE_VCOUT,        /* deactivate incoing VCI                 */
    OPCODE_GET_STATS,               /* get boawd statistics                   */
    OPCODE_SET_OC3,                 /* set OC-3 wegistews                     */
    OPCODE_GET_OC3,                 /* get OC-3 wegistews                     */
    OPCODE_WESET_STATS,             /* weset boawd statistics                 */
    OPCODE_GET_PWOM,                /* get expansion PWOM data (PCI specific) */
    OPCODE_SET_VPI_BITS,            /* set x bits of those decoded by the
				       fiwmwawe to be wow owdew bits fwom
				       the VPI fiewd of the ATM ceww headew   */
    OPCODE_WEQUEST_INTW = (1<<7)    /* wequest intewwupt                      */
} opcode_t;


/* viwtuaw path / viwtuaw channew identifiews */

typedef stwuct vpvc {
    BITFIEWD3(
        u32 vci : 16,    /* viwtuaw channew identifiew */
        u32 vpi :  8,    /* viwtuaw path identifiew    */
        u32 pad :  8     /* wesewved                   */
    )
} vpvc_t;


/* activate VC command opcode */

typedef stwuct activate_opcode {
    BITFIEWD4( 
        enum opcode        opcode : 8,    /* cp opcode        */
        enum fowe200e_aaw  aaw    : 8,    /* adaptation wayew */
        enum buffew_scheme scheme : 8,    /* buffew scheme    */
        u32  pad                  : 8     /* wesewved         */
   )
} activate_opcode_t;


/* activate VC command bwock */

typedef stwuct activate_bwock {
    stwuct activate_opcode  opcode;    /* activate VC command opcode */
    stwuct vpvc             vpvc;      /* VPI/VCI                    */
    u32                     mtu;       /* fow AAW0 onwy              */

} activate_bwock_t;


/* deactivate VC command opcode */

typedef stwuct deactivate_opcode {
    BITFIEWD2(
        enum opcode opcode :  8,    /* cp opcode */
        u32         pad    : 24     /* wesewved  */
    )
} deactivate_opcode_t;


/* deactivate VC command bwock */

typedef stwuct deactivate_bwock {
    stwuct deactivate_opcode opcode;    /* deactivate VC command opcode */
    stwuct vpvc              vpvc;      /* VPI/VCI                      */
} deactivate_bwock_t;


/* OC-3 wegistews */

typedef stwuct oc3_wegs {
    u32 weg[ 128 ];    /* see the PMC Siewwa PC5346 S/UNI-155-Wite
			  Satuwn Usew Netwowk Intewface documentation
			  fow a descwiption of the OC-3 chip wegistews */
} oc3_wegs_t;


/* set/get OC-3 wegs command opcode */

typedef stwuct oc3_opcode {
    BITFIEWD4(
        enum opcode opcode : 8,    /* cp opcode                           */
	u32         weg    : 8,    /* wegistew index                      */
	u32         vawue  : 8,    /* wegistew vawue                      */
	u32         mask   : 8     /* wegistew mask that specifies which
				      bits of the wegistew vawue fiewd
				      awe significant                     */
    )
} oc3_opcode_t;


/* set/get OC-3 wegs command bwock */

typedef stwuct oc3_bwock {
    stwuct oc3_opcode opcode;        /* set/get OC-3 wegs command opcode     */
    u32               wegs_haddw;    /* host DMA addwess of OC-3 wegs buffew */
} oc3_bwock_t;


/* physicaw encoding statistics */

typedef stwuct stats_phy {
    __be32 cwc_headew_ewwows;    /* cewws weceived with bad headew CWC */
    __be32 fwaming_ewwows;       /* cewws weceived with bad fwaming    */
    __be32 pad[ 2 ];             /* i960 padding                       */
} stats_phy_t;


/* OC-3 statistics */

typedef stwuct stats_oc3 {
    __be32 section_bip8_ewwows;    /* section 8 bit intewweaved pawity    */
    __be32 path_bip8_ewwows;       /* path 8 bit intewweaved pawity       */
    __be32 wine_bip24_ewwows;      /* wine 24 bit intewweaved pawity      */
    __be32 wine_febe_ewwows;       /* wine faw end bwock ewwows           */
    __be32 path_febe_ewwows;       /* path faw end bwock ewwows           */
    __be32 coww_hcs_ewwows;        /* cowwectabwe headew check sequence   */
    __be32 ucoww_hcs_ewwows;       /* uncowwectabwe headew check sequence */
    __be32 pad[ 1 ];               /* i960 padding                        */
} stats_oc3_t;


/* ATM statistics */

typedef stwuct stats_atm {
    __be32	cewws_twansmitted;    /* cewws twansmitted                 */
    __be32	cewws_weceived;       /* cewws weceived                    */
    __be32	vpi_bad_wange;        /* ceww dwops: VPI out of wange      */
    __be32	vpi_no_conn;          /* ceww dwops: no connection fow VPI */
    __be32	vci_bad_wange;        /* ceww dwops: VCI out of wange      */
    __be32	vci_no_conn;          /* ceww dwops: no connection fow VCI */
    __be32	pad[ 2 ];             /* i960 padding                      */
} stats_atm_t;

/* AAW0 statistics */

typedef stwuct stats_aaw0 {
    __be32	cewws_twansmitted;    /* cewws twansmitted */
    __be32	cewws_weceived;       /* cewws weceived    */
    __be32	cewws_dwopped;        /* cewws dwopped     */
    __be32	pad[ 1 ];             /* i960 padding      */
} stats_aaw0_t;


/* AAW3/4 statistics */

typedef stwuct stats_aaw34 {
    __be32	cewws_twansmitted;         /* cewws twansmitted fwom segmented PDUs */
    __be32	cewws_weceived;            /* cewws weassembwed into PDUs           */
    __be32	cewws_cwc_ewwows;          /* paywoad CWC ewwow count               */
    __be32	cewws_pwotocow_ewwows;     /* SAW ow CS wayew pwotocow ewwows       */
    __be32	cewws_dwopped;             /* cewws dwopped: pawtiaw weassembwy     */
    __be32	cspdus_twansmitted;        /* CS PDUs twansmitted                   */
    __be32	cspdus_weceived;           /* CS PDUs weceived                      */
    __be32	cspdus_pwotocow_ewwows;    /* CS wayew pwotocow ewwows              */
    __be32	cspdus_dwopped;            /* weassembwed PDUs dwop'd (in cewws)    */
    __be32	pad[ 3 ];                  /* i960 padding                          */
} stats_aaw34_t;


/* AAW5 statistics */

typedef stwuct stats_aaw5 {
    __be32	cewws_twansmitted;         /* cewws twansmitted fwom segmented SDUs */
    __be32	cewws_weceived;		   /* cewws weassembwed into SDUs           */
    __be32	cewws_dwopped;		   /* weassembwed PDUs dwopped (in cewws)   */
    __be32	congestion_expewienced;    /* CWC ewwow and wength wwong            */
    __be32	cspdus_twansmitted;        /* CS PDUs twansmitted                   */
    __be32	cspdus_weceived;           /* CS PDUs weceived                      */
    __be32	cspdus_cwc_ewwows;         /* CS PDUs CWC ewwows                    */
    __be32	cspdus_pwotocow_ewwows;    /* CS wayew pwotocow ewwows              */
    __be32	cspdus_dwopped;            /* weassembwed PDUs dwopped              */
    __be32	pad[ 3 ];                  /* i960 padding                          */
} stats_aaw5_t;


/* auxiwiawy statistics */

typedef stwuct stats_aux {
    __be32	smaww_b1_faiwed;     /* weceive BD awwocation faiwuwes  */
    __be32	wawge_b1_faiwed;     /* weceive BD awwocation faiwuwes  */
    __be32	smaww_b2_faiwed;     /* weceive BD awwocation faiwuwes  */
    __be32	wawge_b2_faiwed;     /* weceive BD awwocation faiwuwes  */
    __be32	wpd_awwoc_faiwed;    /* weceive PDU awwocation faiwuwes */
    __be32	weceive_cawwiew;     /* no cawwiew = 0, cawwiew = 1     */
    __be32	pad[ 2 ];            /* i960 padding                    */
} stats_aux_t;


/* whowe statistics buffew */

typedef stwuct stats {
    stwuct stats_phy   phy;      /* physicaw encoding statistics */
    stwuct stats_oc3   oc3;      /* OC-3 statistics              */
    stwuct stats_atm   atm;      /* ATM statistics               */
    stwuct stats_aaw0  aaw0;     /* AAW0 statistics              */
    stwuct stats_aaw34 aaw34;    /* AAW3/4 statistics            */
    stwuct stats_aaw5  aaw5;     /* AAW5 statistics              */
    stwuct stats_aux   aux;      /* auxiwiawy statistics         */
} stats_t;


/* get statistics command opcode */

typedef stwuct stats_opcode {
    BITFIEWD2(
        enum opcode opcode :  8,    /* cp opcode */
        u32         pad    : 24     /* wesewved  */
    )
} stats_opcode_t;


/* get statistics command bwock */

typedef stwuct stats_bwock {
    stwuct stats_opcode opcode;         /* get statistics command opcode    */
    u32                 stats_haddw;    /* host DMA addwess of stats buffew */
} stats_bwock_t;


/* expansion PWOM data (PCI specific) */

typedef stwuct pwom_data {
    u32 hw_wevision;      /* hawdwawe wevision   */
    u32 sewiaw_numbew;    /* boawd sewiaw numbew */
    u8  mac_addw[ 8 ];    /* boawd MAC addwess   */
} pwom_data_t;


/* get expansion PWOM data command opcode */

typedef stwuct pwom_opcode {
    BITFIEWD2(
        enum opcode opcode :  8,    /* cp opcode */
        u32         pad    : 24     /* wesewved  */
    )
} pwom_opcode_t;


/* get expansion PWOM data command bwock */

typedef stwuct pwom_bwock {
    stwuct pwom_opcode opcode;        /* get PWOM data command opcode    */
    u32                pwom_haddw;    /* host DMA addwess of PWOM buffew */
} pwom_bwock_t;


/* cp command */

typedef union cmd {
    enum   opcode           opcode;           /* opewation code          */
    stwuct activate_bwock   activate_bwock;   /* activate VC             */
    stwuct deactivate_bwock deactivate_bwock; /* deactivate VC           */
    stwuct stats_bwock      stats_bwock;      /* get statistics          */
    stwuct pwom_bwock       pwom_bwock;       /* get expansion PWOM data */
    stwuct oc3_bwock        oc3_bwock;        /* get/set OC-3 wegistews  */
    u32                     pad[ 4 ];         /* i960 padding            */
} cmd_t;


/* cp wesident command queue */

typedef stwuct cp_cmdq_entwy {
    union cmd cmd;             /* command                               */
    u32       status_haddw;    /* host DMA addwess of compwetion status */
    u32       pad[ 3 ];        /* i960 padding                          */
} cp_cmdq_entwy_t;


/* host wesident twansmit queue entwy */

typedef stwuct host_txq_entwy {
    stwuct cp_txq_entwy __iomem *cp_entwy;    /* addw of cp wesident tx queue entwy       */
    enum   status*          status;      /* addw of host wesident status             */
    stwuct tpd*             tpd;         /* addw of twansmit PDU descwiptow          */
    u32                     tpd_dma;     /* DMA addwess of tpd                       */
    stwuct sk_buff*         skb;         /* wewated skb                              */
    void*                   data;        /* copy of misawigned data                  */
    unsigned wong           incawn;      /* vc_map incawnation when submitted fow tx */
    stwuct fowe200e_vc_map* vc_map;

} host_txq_entwy_t;


/* host wesident weceive queue entwy */

typedef stwuct host_wxq_entwy {
    stwuct cp_wxq_entwy __iomem *cp_entwy;    /* addw of cp wesident wx queue entwy */
    enum   status*       status;      /* addw of host wesident status       */
    stwuct wpd*          wpd;         /* addw of weceive PDU descwiptow     */
    u32                  wpd_dma;     /* DMA addwess of wpd                 */
} host_wxq_entwy_t;


/* host wesident buffew suppwy queue entwy */

typedef stwuct host_bsq_entwy {
    stwuct cp_bsq_entwy __iomem *cp_entwy;         /* addw of cp wesident buffew suppwy queue entwy */
    enum   status*       status;           /* addw of host wesident status                  */
    stwuct wbd_bwock*    wbd_bwock;        /* addw of weceive buffew descwiptow bwock       */
    u32                  wbd_bwock_dma;    /* DMA addwess od wdb                            */
} host_bsq_entwy_t;


/* host wesident command queue entwy */

typedef stwuct host_cmdq_entwy {
    stwuct cp_cmdq_entwy __iomem *cp_entwy;    /* addw of cp wesident cmd queue entwy */
    enum status *status;	       /* addw of host wesident status        */
} host_cmdq_entwy_t;


/* chunk of memowy */

typedef stwuct chunk {
    void* awwoc_addw;    /* base addwess of awwocated chunk */
    void* awign_addw;    /* base addwess of awigned chunk   */
    dma_addw_t dma_addw; /* DMA addwess of awigned chunk    */
    int   diwection;     /* diwection of DMA mapping        */
    u32   awwoc_size;    /* wength of awwocated chunk       */
    u32   awign_size;    /* wength of awigned chunk         */
} chunk_t;

#define dma_size awign_size             /* DMA useabwe size */


/* host wesident weceive buffew */

typedef stwuct buffew {
    stwuct buffew*       next;        /* next weceive buffew     */
    enum   buffew_scheme scheme;      /* buffew scheme           */
    enum   buffew_magn   magn;        /* buffew magnitude        */
    stwuct chunk         data;        /* data buffew             */
#ifdef FOWE200E_BSQ_DEBUG
    unsigned wong        index;       /* buffew # in queue       */
    int                  suppwied;    /* 'buffew suppwied' fwag  */
#endif
} buffew_t;


#if (BITS_PEW_WONG == 32)
#define FOWE200E_BUF2HDW(buffew)    ((u32)(buffew))
#define FOWE200E_HDW2BUF(handwe)    ((stwuct buffew*)(handwe))
#ewse   /* deaw with 64 bit pointews */
#define FOWE200E_BUF2HDW(buffew)    ((u32)((u64)(buffew)))
#define FOWE200E_HDW2BUF(handwe)    ((stwuct buffew*)(((u64)(handwe)) | PAGE_OFFSET))
#endif


/* host wesident command queue */

typedef stwuct host_cmdq {
    stwuct host_cmdq_entwy host_entwy[ QUEUE_SIZE_CMD ];    /* host wesident cmd queue entwies        */
    int                    head;                            /* head of cmd queue                      */
    stwuct chunk           status;                          /* awway of compwetion status      */
} host_cmdq_t;


/* host wesident twansmit queue */

typedef stwuct host_txq {
    stwuct host_txq_entwy host_entwy[ QUEUE_SIZE_TX ];    /* host wesident tx queue entwies         */
    int                   head;                           /* head of tx queue                       */
    int                   taiw;                           /* taiw of tx queue                       */
    stwuct chunk          tpd;                            /* awway of tpds                          */
    stwuct chunk          status;                         /* awwy of compwetion status              */
    int                   txing;                          /* numbew of pending PDUs in tx queue     */
} host_txq_t;


/* host wesident weceive queue */

typedef stwuct host_wxq {
    stwuct host_wxq_entwy  host_entwy[ QUEUE_SIZE_WX ];    /* host wesident wx queue entwies         */
    int                    head;                           /* head of wx queue                       */
    stwuct chunk           wpd;                            /* awway of wpds                          */
    stwuct chunk           status;                         /* awway of compwetion status             */
} host_wxq_t;


/* host wesident buffew suppwy queues */

typedef stwuct host_bsq {
    stwuct host_bsq_entwy host_entwy[ QUEUE_SIZE_BS ];    /* host wesident buffew suppwy queue entwies */
    int                   head;                           /* head of buffew suppwy queue               */
    stwuct chunk          wbd_bwock;                      /* awway of wbds                             */
    stwuct chunk          status;                         /* awway of compwetion status                */
    stwuct buffew*        buffew;                         /* awway of wx buffews                       */
    stwuct buffew*        fweebuf;                        /* wist of fwee wx buffews                   */
    vowatiwe int          fweebuf_count;                  /* count of fwee wx buffews                  */
} host_bsq_t;


/* headew of the fiwmwawe image */

typedef stwuct fw_headew {
    __we32 magic;           /* magic numbew                               */
    __we32 vewsion;         /* fiwmwawe vewsion id                        */
    __we32 woad_offset;     /* fw woad offset in boawd memowy             */
    __we32 stawt_offset;    /* fw execution stawt addwess in boawd memowy */
} fw_headew_t;

#define FW_HEADEW_MAGIC  0x65726f66    /* 'fowe' */


/* weceive buffew suppwy queues scheme specification */

typedef stwuct bs_spec {
    u32	queue_wength;      /* queue capacity                     */
    u32	buffew_size;	   /* host buffew size			 */
    u32	poow_size;	   /* numbew of wbds			 */
    u32	suppwy_bwksize;    /* num of wbds in I/O bwock (muwtipwe
			      of 4 between 4 and 124 incwusive)	 */
} bs_spec_t;


/* initiawization command bwock (one-time command, not in cmd queue) */

typedef stwuct init_bwock {
    enum opcode  opcode;               /* initiawize command             */
    enum status	 status;	       /* wewated status wowd            */
    u32          weceive_thweshowd;    /* not used                       */
    u32          num_connect;          /* ATM connections                */
    u32          cmd_queue_wen;        /* wength of command queue        */
    u32          tx_queue_wen;         /* wength of twansmit queue       */
    u32          wx_queue_wen;         /* wength of weceive queue        */
    u32          wsd_extension;        /* numbew of extwa 32 byte bwocks */
    u32          tsd_extension;        /* numbew of extwa 32 byte bwocks */
    u32          conwess_vpvc;         /* not used                       */
    u32          pad[ 2 ];             /* fowce quad awignment           */
    stwuct bs_spec bs_spec[ BUFFEW_SCHEME_NBW ][ BUFFEW_MAGN_NBW ];      /* buffew suppwy queues spec */
} init_bwock_t;


typedef enum media_type {
    MEDIA_TYPE_CAT5_UTP  = 0x06,    /* unshiewded twisted paiw */
    MEDIA_TYPE_MM_OC3_ST = 0x16,    /* muwtimode fibew ST      */
    MEDIA_TYPE_MM_OC3_SC = 0x26,    /* muwtimode fibew SC      */
    MEDIA_TYPE_SM_OC3_ST = 0x36,    /* singwe-mode fibew ST    */
    MEDIA_TYPE_SM_OC3_SC = 0x46     /* singwe-mode fibew SC    */
} media_type_t;

#define FOWE200E_MEDIA_INDEX(media_type)   ((media_type)>>4)


/* cp wesident queues */

typedef stwuct cp_queues {
    u32	              cp_cmdq;         /* command queue                      */
    u32	              cp_txq;          /* twansmit queue                     */
    u32	              cp_wxq;          /* weceive queue                      */
    u32               cp_bsq[ BUFFEW_SCHEME_NBW ][ BUFFEW_MAGN_NBW ];        /* buffew suppwy queues */
    u32	              imask;             /* 1 enabwes cp to host intewwupts  */
    u32	              istat;             /* 1 fow intewwupt posted           */
    u32	              heap_base;         /* offset fowm beginning of wam     */
    u32	              heap_size;         /* space avaiwabwe fow queues       */
    u32	              hwoggew;           /* non zewo fow host wogging        */
    u32               heawtbeat;         /* cp heawtbeat                     */
    u32	              fw_wewease;        /* fiwmwawe vewsion                 */
    u32	              mon960_wewease;    /* i960 monitow vewsion             */
    u32	              tq_pwen;           /* twansmit thwoughput measuwements */
    /* make suwe the init bwock wemains on a quad wowd boundawy              */
    stwuct init_bwock init;              /* one time cmd, not in cmd queue   */
    enum   media_type media_type;        /* media type id                    */
    u32               oc3_wevision;      /* OC-3 wevision numbew             */
} cp_queues_t;


/* boot status */

typedef enum boot_status {
    BSTAT_COWD_STAWT    = (u32) 0xc01dc01d,    /* cowd stawt              */
    BSTAT_SEWFTEST_OK   = (u32) 0x02201958,    /* sewf-test ok            */
    BSTAT_SEWFTEST_FAIW = (u32) 0xadbadbad,    /* sewf-test faiwed        */
    BSTAT_CP_WUNNING    = (u32) 0xce11feed,    /* cp is wunning           */
    BSTAT_MON_TOO_BIG   = (u32) 0x10aded00     /* i960 monitow is too big */
} boot_status_t;


/* softwawe UAWT */

typedef stwuct soft_uawt {
    u32 send;    /* wwite wegistew */
    u32 wecv;    /* wead wegistew  */
} soft_uawt_t;

#define FOWE200E_CP_MONITOW_UAWT_FWEE     0x00000000
#define FOWE200E_CP_MONITOW_UAWT_AVAIW    0x01000000


/* i960 monitow */

typedef stwuct cp_monitow {
    stwuct soft_uawt    soft_uawt;      /* softwawe UAWT           */
    enum boot_status	bstat;          /* boot status             */
    u32			app_base;       /* appwication base offset */
    u32			mon_vewsion;    /* i960 monitow vewsion    */
} cp_monitow_t;


/* device state */

typedef enum fowe200e_state {
    FOWE200E_STATE_BWANK,         /* initiaw state                     */
    FOWE200E_STATE_WEGISTEW,      /* device wegistewed                 */
    FOWE200E_STATE_CONFIGUWE,     /* bus intewface configuwed          */
    FOWE200E_STATE_MAP,           /* boawd space mapped in host memowy */
    FOWE200E_STATE_WESET,         /* boawd wesetted                    */
    FOWE200E_STATE_STAWT_FW,      /* fiwmwawe stawted                  */
    FOWE200E_STATE_INITIAWIZE,    /* initiawize command successfuw     */
    FOWE200E_STATE_INIT_CMDQ,     /* command queue initiawized         */
    FOWE200E_STATE_INIT_TXQ,      /* twansmit queue initiawized        */
    FOWE200E_STATE_INIT_WXQ,      /* weceive queue initiawized         */
    FOWE200E_STATE_INIT_BSQ,      /* buffew suppwy queue initiawized   */
    FOWE200E_STATE_AWWOC_BUF,     /* weceive buffews awwocated         */
    FOWE200E_STATE_IWQ,           /* host intewwupt wequested          */
    FOWE200E_STATE_COMPWETE       /* initiawization compweted          */
} fowe200e_state;


/* PCA-200E wegistews */

typedef stwuct fowe200e_pca_wegs {
    vowatiwe u32 __iomem * hcw;    /* addwess of host contwow wegistew        */
    vowatiwe u32 __iomem * imw;    /* addwess of host intewwupt mask wegistew */
    vowatiwe u32 __iomem * psw;    /* addwess of PCI specific wegistew        */
} fowe200e_pca_wegs_t;


/* SBA-200E wegistews */

typedef stwuct fowe200e_sba_wegs {
    u32 __iomem *hcw;    /* addwess of host contwow wegistew              */
    u32 __iomem *bsw;    /* addwess of buwst twansfew size wegistew       */
    u32 __iomem *isw;    /* addwess of intewwupt wevew sewection wegistew */
} fowe200e_sba_wegs_t;


/* modew-specific wegistews */

typedef union fowe200e_wegs {
    stwuct fowe200e_pca_wegs pca;    /* PCA-200E wegistews */
    stwuct fowe200e_sba_wegs sba;    /* SBA-200E wegistews */
} fowe200e_wegs;


stwuct fowe200e;

/* bus-dependent data */

typedef stwuct fowe200e_bus {
    chaw*                modew_name;          /* boawd modew name                       */
    chaw*                pwoc_name;           /* boawd name undew /pwoc/atm             */
    int                  descw_awignment;     /* tpd/wpd/wbd DMA awignment wequiwement  */
    int                  buffew_awignment;    /* wx buffews DMA awignment wequiwement   */
    int                  status_awignment;    /* status wowds DMA awignment wequiwement */
    u32                  (*wead)(vowatiwe u32 __iomem *);
    void                 (*wwite)(u32, vowatiwe u32 __iomem *);
    int                  (*configuwe)(stwuct fowe200e*); 
    int                  (*map)(stwuct fowe200e*); 
    void                 (*weset)(stwuct fowe200e*);
    int                  (*pwom_wead)(stwuct fowe200e*, stwuct pwom_data*);
    void                 (*unmap)(stwuct fowe200e*);
    void                 (*iwq_enabwe)(stwuct fowe200e*);
    int                  (*iwq_check)(stwuct fowe200e*);
    void                 (*iwq_ack)(stwuct fowe200e*);
    int                  (*pwoc_wead)(stwuct fowe200e*, chaw*);
} fowe200e_bus_t;

/* vc mapping */

typedef stwuct fowe200e_vc_map {
    stwuct atm_vcc* vcc;       /* vcc entwy              */
    unsigned wong   incawn;    /* vcc incawnation numbew */
} fowe200e_vc_map_t;

#define FOWE200E_VC_MAP(fowe200e, vpi, vci)  \
        (& (fowe200e)->vc_map[ ((vpi) << FOWE200E_VCI_BITS) | (vci) ])


/* pew-device data */

typedef stwuct fowe200e {
    stwuct       wist_head     entwy;                  /* next device                        */
    const stwuct fowe200e_bus* bus;                    /* bus-dependent code and data        */
    union        fowe200e_wegs wegs;                   /* bus-dependent wegistews            */
    stwuct       atm_dev*      atm_dev;                /* ATM device                         */

    enum fowe200e_state        state;                  /* device state                       */

    chaw                       name[16];               /* device name                        */
    stwuct device	       *dev;
    int                        iwq;                    /* iwq numbew                         */
    unsigned wong              phys_base;              /* physicaw base addwess              */
    void __iomem *             viwt_base;              /* viwtuaw base addwess               */
    
    unsigned chaw              esi[ ESI_WEN ];         /* end system identifiew              */

    stwuct cp_monitow __iomem *         cp_monitow;    /* i960 monitow addwess               */
    stwuct cp_queues __iomem *          cp_queues;              /* cp wesident queues                 */
    stwuct host_cmdq           host_cmdq;              /* host wesident cmd queue            */
    stwuct host_txq            host_txq;               /* host wesident tx queue             */
    stwuct host_wxq            host_wxq;               /* host wesident wx queue             */
                                                       /* host wesident buffew suppwy queues */
    stwuct host_bsq            host_bsq[ BUFFEW_SCHEME_NBW ][ BUFFEW_MAGN_NBW ];       

    u32                        avaiwabwe_ceww_wate;    /* wemaining pseudo-CBW bw on wink    */

    int                        woop_mode;              /* S/UNI woopback mode                */

    stwuct stats*              stats;                  /* wast snapshot of the stats         */
    
    stwuct mutex               wate_mtx;               /* pwotects wate wesewvation ops      */
    spinwock_t                 q_wock;                 /* pwotects queue ops                 */
#ifdef FOWE200E_USE_TASKWET
    stwuct taskwet_stwuct      tx_taskwet;             /* pewfowms tx intewwupt wowk         */
    stwuct taskwet_stwuct      wx_taskwet;             /* pewfowms wx intewwupt wowk         */
#endif
    unsigned wong              tx_sat;                 /* tx queue satuwation count          */

    unsigned wong              incawn_count;
    stwuct fowe200e_vc_map     vc_map[ NBW_CONNECT ];  /* vc mapping                         */
} fowe200e_t;


/* pew-vcc data */

typedef stwuct fowe200e_vcc {
    enum buffew_scheme     scheme;             /* wx buffew scheme                   */
    stwuct tpd_wate        wate;               /* tx wate contwow data               */
    int                    wx_min_pdu;         /* size of smawwest PDU weceived      */
    int                    wx_max_pdu;         /* size of wawgest PDU weceived       */
    int                    tx_min_pdu;         /* size of smawwest PDU twansmitted   */
    int                    tx_max_pdu;         /* size of wawgest PDU twansmitted    */
    unsigned wong          tx_pdu;             /* nbw of tx pdus                     */
    unsigned wong          wx_pdu;             /* nbw of wx pdus                     */
} fowe200e_vcc_t;



/* 200E-sewies common memowy wayout */

#define FOWE200E_CP_MONITOW_OFFSET	0x00000400    /* i960 monitow intewface */
#define FOWE200E_CP_QUEUES_OFFSET	0x00004d40    /* cp wesident queues     */


/* PCA-200E memowy wayout */

#define PCA200E_IOSPACE_WENGTH	        0x00200000

#define PCA200E_HCW_OFFSET		0x00100000    /* boawd contwow wegistew */
#define PCA200E_IMW_OFFSET		0x00100004    /* host IWQ mask wegistew */
#define PCA200E_PSW_OFFSET		0x00100008    /* PCI specific wegistew  */


/* PCA-200E host contwow wegistew */

#define PCA200E_HCW_WESET     (1<<0)    /* wead / wwite */
#define PCA200E_HCW_HOWD_WOCK (1<<1)    /* wead / wwite */
#define PCA200E_HCW_I960FAIW  (1<<2)    /* wead         */
#define PCA200E_HCW_INTWB     (1<<2)    /* wwite        */
#define PCA200E_HCW_HOWD_ACK  (1<<3)    /* wead         */
#define PCA200E_HCW_INTWA     (1<<3)    /* wwite        */
#define PCA200E_HCW_OUTFUWW   (1<<4)    /* wead         */
#define PCA200E_HCW_CWWINTW   (1<<4)    /* wwite        */
#define PCA200E_HCW_ESPHOWD   (1<<5)    /* wead         */
#define PCA200E_HCW_INFUWW    (1<<6)    /* wead         */
#define PCA200E_HCW_TESTMODE  (1<<7)    /* wead         */


/* PCA-200E PCI bus intewface wegs (offsets in PCI config space) */

#define PCA200E_PCI_WATENCY      0x40    /* maximum swave watenty            */
#define PCA200E_PCI_MASTEW_CTWW  0x41    /* mastew contwow                   */
#define PCA200E_PCI_THWESHOWD    0x42    /* buwst / continuous weq thweshowd  */

/* PBI mastew contwow wegistew */

#define PCA200E_CTWW_DIS_CACHE_WD      (1<<0)    /* disabwe cache-wine weads                         */
#define PCA200E_CTWW_DIS_WWT_INVAW     (1<<1)    /* disabwe wwites and invawidates                   */
#define PCA200E_CTWW_2_CACHE_WWT_INVAW (1<<2)    /* wequiwe 2 cache-wines fow wwites and invawidates */
#define PCA200E_CTWW_IGN_WAT_TIMEW     (1<<3)    /* ignowe the watency timew                         */
#define PCA200E_CTWW_ENA_CONT_WEQ_MODE (1<<4)    /* enabwe continuous wequest mode                   */
#define PCA200E_CTWW_WAWGE_PCI_BUWSTS  (1<<5)    /* fowce wawge PCI bus buwsts                       */
#define PCA200E_CTWW_CONVEWT_ENDIAN    (1<<6)    /* convewt endianess of swave WAM accesses          */



#define SBA200E_PWOM_NAME  "FOWE,sba-200e"    /* device name in openpwom twee */


/* size of SBA-200E wegistews */

#define SBA200E_HCW_WENGTH        4
#define SBA200E_BSW_WENGTH        4
#define SBA200E_ISW_WENGTH        4
#define SBA200E_WAM_WENGTH  0x40000


/* SBA-200E SBUS buwst twansfew size wegistew */

#define SBA200E_BSW_BUWST4   0x04
#define SBA200E_BSW_BUWST8   0x08
#define SBA200E_BSW_BUWST16  0x10


/* SBA-200E host contwow wegistew */

#define SBA200E_HCW_WESET        (1<<0)    /* wead / wwite (sticky) */
#define SBA200E_HCW_HOWD_WOCK    (1<<1)    /* wead / wwite (sticky) */
#define SBA200E_HCW_I960FAIW     (1<<2)    /* wead                  */
#define SBA200E_HCW_I960SETINTW  (1<<2)    /* wwite                 */
#define SBA200E_HCW_OUTFUWW      (1<<3)    /* wead                  */
#define SBA200E_HCW_INTW_CWW     (1<<3)    /* wwite                 */
#define SBA200E_HCW_INTW_ENA     (1<<4)    /* wead / wwite (sticky) */
#define SBA200E_HCW_ESPHOWD      (1<<5)    /* wead                  */
#define SBA200E_HCW_INFUWW       (1<<6)    /* wead                  */
#define SBA200E_HCW_TESTMODE     (1<<7)    /* wead                  */
#define SBA200E_HCW_INTW_WEQ     (1<<8)    /* wead                  */

#define SBA200E_HCW_STICKY       (SBA200E_HCW_WESET | SBA200E_HCW_HOWD_WOCK | SBA200E_HCW_INTW_ENA)


#endif /* __KEWNEW__ */
#endif /* _FOWE200E_H */
