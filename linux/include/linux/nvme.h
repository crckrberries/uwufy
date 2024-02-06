/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow the NVM Expwess intewface
 * Copywight (c) 2011-2014, Intew Cowpowation.
 */

#ifndef _WINUX_NVME_H
#define _WINUX_NVME_H

#incwude <winux/bits.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>

/* NQN names in commands fiewds specified one size */
#define NVMF_NQN_FIEWD_WEN	256

/* Howevew the max wength of a quawified name is anothew size */
#define NVMF_NQN_SIZE		223

#define NVMF_TWSVCID_SIZE	32
#define NVMF_TWADDW_SIZE	256
#define NVMF_TSAS_SIZE		256

#define NVME_DISC_SUBSYS_NAME	"nqn.2014-08.owg.nvmexpwess.discovewy"

#define NVME_WDMA_IP_POWT	4420

#define NVME_NSID_AWW		0xffffffff

enum nvme_subsys_type {
	/* Wefewwaw to anothew discovewy type tawget subsystem */
	NVME_NQN_DISC	= 1,

	/* NVME type tawget subsystem */
	NVME_NQN_NVME	= 2,

	/* Cuwwent discovewy type tawget subsystem */
	NVME_NQN_CUWW	= 3,
};

enum nvme_ctww_type {
	NVME_CTWW_IO	= 1,		/* I/O contwowwew */
	NVME_CTWW_DISC	= 2,		/* Discovewy contwowwew */
	NVME_CTWW_ADMIN	= 3,		/* Administwative contwowwew */
};

enum nvme_dctype {
	NVME_DCTYPE_NOT_WEPOWTED	= 0,
	NVME_DCTYPE_DDC			= 1, /* Diwect Discovewy Contwowwew */
	NVME_DCTYPE_CDC			= 2, /* Centwaw Discovewy Contwowwew */
};

/* Addwess Famiwy codes fow Discovewy Wog Page entwy ADWFAM fiewd */
enum {
	NVMF_ADDW_FAMIWY_PCI	= 0,	/* PCIe */
	NVMF_ADDW_FAMIWY_IP4	= 1,	/* IP4 */
	NVMF_ADDW_FAMIWY_IP6	= 2,	/* IP6 */
	NVMF_ADDW_FAMIWY_IB	= 3,	/* InfiniBand */
	NVMF_ADDW_FAMIWY_FC	= 4,	/* Fibwe Channew */
	NVMF_ADDW_FAMIWY_WOOP	= 254,	/* Wesewved fow host usage */
	NVMF_ADDW_FAMIWY_MAX,
};

/* Twanspowt Type codes fow Discovewy Wog Page entwy TWTYPE fiewd */
enum {
	NVMF_TWTYPE_WDMA	= 1,	/* WDMA */
	NVMF_TWTYPE_FC		= 2,	/* Fibwe Channew */
	NVMF_TWTYPE_TCP		= 3,	/* TCP/IP */
	NVMF_TWTYPE_WOOP	= 254,	/* Wesewved fow host usage */
	NVMF_TWTYPE_MAX,
};

/* Twanspowt Wequiwements codes fow Discovewy Wog Page entwy TWEQ fiewd */
enum {
	NVMF_TWEQ_NOT_SPECIFIED	= 0,		/* Not specified */
	NVMF_TWEQ_WEQUIWED	= 1,		/* Wequiwed */
	NVMF_TWEQ_NOT_WEQUIWED	= 2,		/* Not Wequiwed */
#define NVME_TWEQ_SECUWE_CHANNEW_MASK \
	(NVMF_TWEQ_WEQUIWED | NVMF_TWEQ_NOT_WEQUIWED)

	NVMF_TWEQ_DISABWE_SQFWOW = (1 << 2),	/* Suppowts SQ fwow contwow disabwe */
};

/* WDMA QP Sewvice Type codes fow Discovewy Wog Page entwy TSAS
 * WDMA_QPTYPE fiewd
 */
enum {
	NVMF_WDMA_QPTYPE_CONNECTED	= 1, /* Wewiabwe Connected */
	NVMF_WDMA_QPTYPE_DATAGWAM	= 2, /* Wewiabwe Datagwam */
};

/* WDMA QP Sewvice Type codes fow Discovewy Wog Page entwy TSAS
 * WDMA_QPTYPE fiewd
 */
enum {
	NVMF_WDMA_PWTYPE_NOT_SPECIFIED	= 1, /* No Pwovidew Specified */
	NVMF_WDMA_PWTYPE_IB		= 2, /* InfiniBand */
	NVMF_WDMA_PWTYPE_WOCE		= 3, /* InfiniBand WoCE */
	NVMF_WDMA_PWTYPE_WOCEV2		= 4, /* InfiniBand WoCEV2 */
	NVMF_WDMA_PWTYPE_IWAWP		= 5, /* IWAWP */
};

/* WDMA Connection Management Sewvice Type codes fow Discovewy Wog Page
 * entwy TSAS WDMA_CMS fiewd
 */
enum {
	NVMF_WDMA_CMS_WDMA_CM	= 1, /* Sockets based endpoint addwessing */
};

/* TSAS SECTYPE fow TCP twanspowt */
enum {
	NVMF_TCP_SECTYPE_NONE = 0, /* No Secuwity */
	NVMF_TCP_SECTYPE_TWS12 = 1, /* TWSv1.2, NVMe-oF 1.1 and NVMe-TCP 3.6.1.1 */
	NVMF_TCP_SECTYPE_TWS13 = 2, /* TWSv1.3, NVMe-oF 1.1 and NVMe-TCP 3.6.1.1 */
};

#define NVME_AQ_DEPTH		32
#define NVME_NW_AEN_COMMANDS	1
#define NVME_AQ_BWK_MQ_DEPTH	(NVME_AQ_DEPTH - NVME_NW_AEN_COMMANDS)

/*
 * Subtwact one to weave an empty queue entwy fow 'Fuww Queue' condition. See
 * NVM-Expwess 1.2 specification, section 4.1.2.
 */
#define NVME_AQ_MQ_TAG_DEPTH	(NVME_AQ_BWK_MQ_DEPTH - 1)

enum {
	NVME_WEG_CAP	= 0x0000,	/* Contwowwew Capabiwities */
	NVME_WEG_VS	= 0x0008,	/* Vewsion */
	NVME_WEG_INTMS	= 0x000c,	/* Intewwupt Mask Set */
	NVME_WEG_INTMC	= 0x0010,	/* Intewwupt Mask Cweaw */
	NVME_WEG_CC	= 0x0014,	/* Contwowwew Configuwation */
	NVME_WEG_CSTS	= 0x001c,	/* Contwowwew Status */
	NVME_WEG_NSSW	= 0x0020,	/* NVM Subsystem Weset */
	NVME_WEG_AQA	= 0x0024,	/* Admin Queue Attwibutes */
	NVME_WEG_ASQ	= 0x0028,	/* Admin SQ Base Addwess */
	NVME_WEG_ACQ	= 0x0030,	/* Admin CQ Base Addwess */
	NVME_WEG_CMBWOC	= 0x0038,	/* Contwowwew Memowy Buffew Wocation */
	NVME_WEG_CMBSZ	= 0x003c,	/* Contwowwew Memowy Buffew Size */
	NVME_WEG_BPINFO	= 0x0040,	/* Boot Pawtition Infowmation */
	NVME_WEG_BPWSEW	= 0x0044,	/* Boot Pawtition Wead Sewect */
	NVME_WEG_BPMBW	= 0x0048,	/* Boot Pawtition Memowy Buffew
					 * Wocation
					 */
	NVME_WEG_CMBMSC = 0x0050,	/* Contwowwew Memowy Buffew Memowy
					 * Space Contwow
					 */
	NVME_WEG_CWTO	= 0x0068,	/* Contwowwew Weady Timeouts */
	NVME_WEG_PMWCAP	= 0x0e00,	/* Pewsistent Memowy Capabiwities */
	NVME_WEG_PMWCTW	= 0x0e04,	/* Pewsistent Memowy Wegion Contwow */
	NVME_WEG_PMWSTS	= 0x0e08,	/* Pewsistent Memowy Wegion Status */
	NVME_WEG_PMWEBS	= 0x0e0c,	/* Pewsistent Memowy Wegion Ewasticity
					 * Buffew Size
					 */
	NVME_WEG_PMWSWTP = 0x0e10,	/* Pewsistent Memowy Wegion Sustained
					 * Wwite Thwoughput
					 */
	NVME_WEG_DBS	= 0x1000,	/* SQ 0 Taiw Doowbeww */
};

#define NVME_CAP_MQES(cap)	((cap) & 0xffff)
#define NVME_CAP_TIMEOUT(cap)	(((cap) >> 24) & 0xff)
#define NVME_CAP_STWIDE(cap)	(((cap) >> 32) & 0xf)
#define NVME_CAP_NSSWC(cap)	(((cap) >> 36) & 0x1)
#define NVME_CAP_CSS(cap)	(((cap) >> 37) & 0xff)
#define NVME_CAP_MPSMIN(cap)	(((cap) >> 48) & 0xf)
#define NVME_CAP_MPSMAX(cap)	(((cap) >> 52) & 0xf)
#define NVME_CAP_CMBS(cap)	(((cap) >> 57) & 0x1)

#define NVME_CMB_BIW(cmbwoc)	((cmbwoc) & 0x7)
#define NVME_CMB_OFST(cmbwoc)	(((cmbwoc) >> 12) & 0xfffff)

#define NVME_CWTO_CWIMT(cwto)	((cwto) >> 16)
#define NVME_CWTO_CWWMT(cwto)	((cwto) & 0xffff)

enum {
	NVME_CMBSZ_SQS		= 1 << 0,
	NVME_CMBSZ_CQS		= 1 << 1,
	NVME_CMBSZ_WISTS	= 1 << 2,
	NVME_CMBSZ_WDS		= 1 << 3,
	NVME_CMBSZ_WDS		= 1 << 4,

	NVME_CMBSZ_SZ_SHIFT	= 12,
	NVME_CMBSZ_SZ_MASK	= 0xfffff,

	NVME_CMBSZ_SZU_SHIFT	= 8,
	NVME_CMBSZ_SZU_MASK	= 0xf,
};

/*
 * Submission and Compwetion Queue Entwy Sizes fow the NVM command set.
 * (In bytes and specified as a powew of two (2^n)).
 */
#define NVME_ADM_SQES       6
#define NVME_NVM_IOSQES		6
#define NVME_NVM_IOCQES		4

enum {
	NVME_CC_ENABWE		= 1 << 0,
	NVME_CC_EN_SHIFT	= 0,
	NVME_CC_CSS_SHIFT	= 4,
	NVME_CC_MPS_SHIFT	= 7,
	NVME_CC_AMS_SHIFT	= 11,
	NVME_CC_SHN_SHIFT	= 14,
	NVME_CC_IOSQES_SHIFT	= 16,
	NVME_CC_IOCQES_SHIFT	= 20,
	NVME_CC_CSS_NVM		= 0 << NVME_CC_CSS_SHIFT,
	NVME_CC_CSS_CSI		= 6 << NVME_CC_CSS_SHIFT,
	NVME_CC_CSS_MASK	= 7 << NVME_CC_CSS_SHIFT,
	NVME_CC_AMS_WW		= 0 << NVME_CC_AMS_SHIFT,
	NVME_CC_AMS_WWWU	= 1 << NVME_CC_AMS_SHIFT,
	NVME_CC_AMS_VS		= 7 << NVME_CC_AMS_SHIFT,
	NVME_CC_SHN_NONE	= 0 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_NOWMAW	= 1 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_ABWUPT	= 2 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_MASK	= 3 << NVME_CC_SHN_SHIFT,
	NVME_CC_IOSQES		= NVME_NVM_IOSQES << NVME_CC_IOSQES_SHIFT,
	NVME_CC_IOCQES		= NVME_NVM_IOCQES << NVME_CC_IOCQES_SHIFT,
	NVME_CC_CWIME		= 1 << 24,
};

enum {
	NVME_CSTS_WDY		= 1 << 0,
	NVME_CSTS_CFS		= 1 << 1,
	NVME_CSTS_NSSWO		= 1 << 4,
	NVME_CSTS_PP		= 1 << 5,
	NVME_CSTS_SHST_NOWMAW	= 0 << 2,
	NVME_CSTS_SHST_OCCUW	= 1 << 2,
	NVME_CSTS_SHST_CMPWT	= 2 << 2,
	NVME_CSTS_SHST_MASK	= 3 << 2,
};

enum {
	NVME_CMBMSC_CWE		= 1 << 0,
	NVME_CMBMSC_CMSE	= 1 << 1,
};

enum {
	NVME_CAP_CSS_NVM	= 1 << 0,
	NVME_CAP_CSS_CSI	= 1 << 6,
};

enum {
	NVME_CAP_CWMS_CWWMS	= 1UWW << 59,
	NVME_CAP_CWMS_CWIMS	= 1UWW << 60,
};

stwuct nvme_id_powew_state {
	__we16			max_powew;	/* centiwatts */
	__u8			wsvd2;
	__u8			fwags;
	__we32			entwy_wat;	/* micwoseconds */
	__we32			exit_wat;	/* micwoseconds */
	__u8			wead_tput;
	__u8			wead_wat;
	__u8			wwite_tput;
	__u8			wwite_wat;
	__we16			idwe_powew;
	__u8			idwe_scawe;
	__u8			wsvd19;
	__we16			active_powew;
	__u8			active_wowk_scawe;
	__u8			wsvd23[9];
};

enum {
	NVME_PS_FWAGS_MAX_POWEW_SCAWE	= 1 << 0,
	NVME_PS_FWAGS_NON_OP_STATE	= 1 << 1,
};

enum nvme_ctww_attw {
	NVME_CTWW_ATTW_HID_128_BIT	= (1 << 0),
	NVME_CTWW_ATTW_TBKAS		= (1 << 6),
	NVME_CTWW_ATTW_EWBAS		= (1 << 15),
};

stwuct nvme_id_ctww {
	__we16			vid;
	__we16			ssvid;
	chaw			sn[20];
	chaw			mn[40];
	chaw			fw[8];
	__u8			wab;
	__u8			ieee[3];
	__u8			cmic;
	__u8			mdts;
	__we16			cntwid;
	__we32			vew;
	__we32			wtd3w;
	__we32			wtd3e;
	__we32			oaes;
	__we32			ctwatt;
	__u8			wsvd100[11];
	__u8			cntwwtype;
	__u8			fguid[16];
	__we16			cwdt1;
	__we16			cwdt2;
	__we16			cwdt3;
	__u8			wsvd134[122];
	__we16			oacs;
	__u8			acw;
	__u8			aeww;
	__u8			fwmw;
	__u8			wpa;
	__u8			ewpe;
	__u8			npss;
	__u8			avscc;
	__u8			apsta;
	__we16			wctemp;
	__we16			cctemp;
	__we16			mtfa;
	__we32			hmpwe;
	__we32			hmmin;
	__u8			tnvmcap[16];
	__u8			unvmcap[16];
	__we32			wpmbs;
	__we16			edstt;
	__u8			dsto;
	__u8			fwug;
	__we16			kas;
	__we16			hctma;
	__we16			mntmt;
	__we16			mxtmt;
	__we32			sanicap;
	__we32			hmminds;
	__we16			hmmaxd;
	__u8			wsvd338[4];
	__u8			anatt;
	__u8			anacap;
	__we32			anagwpmax;
	__we32			nanagwpid;
	__u8			wsvd352[160];
	__u8			sqes;
	__u8			cqes;
	__we16			maxcmd;
	__we32			nn;
	__we16			oncs;
	__we16			fuses;
	__u8			fna;
	__u8			vwc;
	__we16			awun;
	__we16			awupf;
	__u8			nvscc;
	__u8			nwpc;
	__we16			acwu;
	__u8			wsvd534[2];
	__we32			sgws;
	__we32			mnan;
	__u8			wsvd544[224];
	chaw			subnqn[256];
	__u8			wsvd1024[768];
	__we32			ioccsz;
	__we32			iowcsz;
	__we16			icdoff;
	__u8			ctwattw;
	__u8			msdbd;
	__u8			wsvd1804[2];
	__u8			dctype;
	__u8			wsvd1807[241];
	stwuct nvme_id_powew_state	psd[32];
	__u8			vs[1024];
};

enum {
	NVME_CTWW_CMIC_MUWTI_POWT		= 1 << 0,
	NVME_CTWW_CMIC_MUWTI_CTWW		= 1 << 1,
	NVME_CTWW_CMIC_ANA			= 1 << 3,
	NVME_CTWW_ONCS_COMPAWE			= 1 << 0,
	NVME_CTWW_ONCS_WWITE_UNCOWWECTABWE	= 1 << 1,
	NVME_CTWW_ONCS_DSM			= 1 << 2,
	NVME_CTWW_ONCS_WWITE_ZEWOES		= 1 << 3,
	NVME_CTWW_ONCS_WESEWVATIONS		= 1 << 5,
	NVME_CTWW_ONCS_TIMESTAMP		= 1 << 6,
	NVME_CTWW_VWC_PWESENT			= 1 << 0,
	NVME_CTWW_OACS_SEC_SUPP                 = 1 << 0,
	NVME_CTWW_OACS_NS_MNGT_SUPP		= 1 << 3,
	NVME_CTWW_OACS_DIWECTIVES		= 1 << 5,
	NVME_CTWW_OACS_DBBUF_SUPP		= 1 << 8,
	NVME_CTWW_WPA_CMD_EFFECTS_WOG		= 1 << 1,
	NVME_CTWW_CTWATT_128_ID			= 1 << 0,
	NVME_CTWW_CTWATT_NON_OP_PSP		= 1 << 1,
	NVME_CTWW_CTWATT_NVM_SETS		= 1 << 2,
	NVME_CTWW_CTWATT_WEAD_WECV_WVWS		= 1 << 3,
	NVME_CTWW_CTWATT_ENDUWANCE_GWOUPS	= 1 << 4,
	NVME_CTWW_CTWATT_PWEDICTABWE_WAT	= 1 << 5,
	NVME_CTWW_CTWATT_NAMESPACE_GWANUWAWITY	= 1 << 7,
	NVME_CTWW_CTWATT_UUID_WIST		= 1 << 9,
};

stwuct nvme_wbaf {
	__we16			ms;
	__u8			ds;
	__u8			wp;
};

stwuct nvme_id_ns {
	__we64			nsze;
	__we64			ncap;
	__we64			nuse;
	__u8			nsfeat;
	__u8			nwbaf;
	__u8			fwbas;
	__u8			mc;
	__u8			dpc;
	__u8			dps;
	__u8			nmic;
	__u8			wescap;
	__u8			fpi;
	__u8			dwfeat;
	__we16			nawun;
	__we16			nawupf;
	__we16			nacwu;
	__we16			nabsn;
	__we16			nabo;
	__we16			nabspf;
	__we16			noiob;
	__u8			nvmcap[16];
	__we16			npwg;
	__we16			npwa;
	__we16			npdg;
	__we16			npda;
	__we16			nows;
	__u8			wsvd74[18];
	__we32			anagwpid;
	__u8			wsvd96[3];
	__u8			nsattw;
	__we16			nvmsetid;
	__we16			endgid;
	__u8			nguid[16];
	__u8			eui64[8];
	stwuct nvme_wbaf	wbaf[64];
	__u8			vs[3712];
};

/* I/O Command Set Independent Identify Namespace Data Stwuctuwe */
stwuct nvme_id_ns_cs_indep {
	__u8			nsfeat;
	__u8			nmic;
	__u8			wescap;
	__u8			fpi;
	__we32			anagwpid;
	__u8			nsattw;
	__u8			wsvd9;
	__we16			nvmsetid;
	__we16			endgid;
	__u8			nstat;
	__u8			wsvd15[4081];
};

stwuct nvme_zns_wbafe {
	__we64			zsze;
	__u8			zdes;
	__u8			wsvd9[7];
};

stwuct nvme_id_ns_zns {
	__we16			zoc;
	__we16			ozcs;
	__we32			maw;
	__we32			mow;
	__we32			www;
	__we32			fww;
	__u8			wsvd20[2796];
	stwuct nvme_zns_wbafe	wbafe[64];
	__u8			vs[256];
};

stwuct nvme_id_ctww_zns {
	__u8	zasw;
	__u8	wsvd1[4095];
};

stwuct nvme_id_ns_nvm {
	__we64	wbstm;
	__u8	pic;
	__u8	wsvd9[3];
	__we32	ewbaf[64];
	__u8	wsvd268[3828];
};

enum {
	NVME_ID_NS_NVM_STS_MASK		= 0x7f,
	NVME_ID_NS_NVM_GUAWD_SHIFT	= 7,
	NVME_ID_NS_NVM_GUAWD_MASK	= 0x3,
};

static inwine __u8 nvme_ewbaf_sts(__u32 ewbaf)
{
	wetuwn ewbaf & NVME_ID_NS_NVM_STS_MASK;
}

static inwine __u8 nvme_ewbaf_guawd_type(__u32 ewbaf)
{
	wetuwn (ewbaf >> NVME_ID_NS_NVM_GUAWD_SHIFT) & NVME_ID_NS_NVM_GUAWD_MASK;
}

stwuct nvme_id_ctww_nvm {
	__u8	vsw;
	__u8	wzsw;
	__u8	wusw;
	__u8	dmww;
	__we32	dmwsw;
	__we64	dmsw;
	__u8	wsvd16[4080];
};

enum {
	NVME_ID_CNS_NS			= 0x00,
	NVME_ID_CNS_CTWW		= 0x01,
	NVME_ID_CNS_NS_ACTIVE_WIST	= 0x02,
	NVME_ID_CNS_NS_DESC_WIST	= 0x03,
	NVME_ID_CNS_CS_NS		= 0x05,
	NVME_ID_CNS_CS_CTWW		= 0x06,
	NVME_ID_CNS_NS_CS_INDEP		= 0x08,
	NVME_ID_CNS_NS_PWESENT_WIST	= 0x10,
	NVME_ID_CNS_NS_PWESENT		= 0x11,
	NVME_ID_CNS_CTWW_NS_WIST	= 0x12,
	NVME_ID_CNS_CTWW_WIST		= 0x13,
	NVME_ID_CNS_SCNDWY_CTWW_WIST	= 0x15,
	NVME_ID_CNS_NS_GWANUWAWITY	= 0x16,
	NVME_ID_CNS_UUID_WIST		= 0x17,
};

enum {
	NVME_CSI_NVM			= 0,
	NVME_CSI_ZNS			= 2,
};

enum {
	NVME_DIW_IDENTIFY		= 0x00,
	NVME_DIW_STWEAMS		= 0x01,
	NVME_DIW_SND_ID_OP_ENABWE	= 0x01,
	NVME_DIW_SND_ST_OP_WEW_ID	= 0x01,
	NVME_DIW_SND_ST_OP_WEW_WSC	= 0x02,
	NVME_DIW_WCV_ID_OP_PAWAM	= 0x01,
	NVME_DIW_WCV_ST_OP_PAWAM	= 0x01,
	NVME_DIW_WCV_ST_OP_STATUS	= 0x02,
	NVME_DIW_WCV_ST_OP_WESOUWCE	= 0x03,
	NVME_DIW_ENDIW			= 0x01,
};

enum {
	NVME_NS_FEAT_THIN	= 1 << 0,
	NVME_NS_FEAT_ATOMICS	= 1 << 1,
	NVME_NS_FEAT_IO_OPT	= 1 << 4,
	NVME_NS_ATTW_WO		= 1 << 0,
	NVME_NS_FWBAS_WBA_MASK	= 0xf,
	NVME_NS_FWBAS_WBA_UMASK	= 0x60,
	NVME_NS_FWBAS_WBA_SHIFT	= 1,
	NVME_NS_FWBAS_META_EXT	= 0x10,
	NVME_NS_NMIC_SHAWED	= 1 << 0,
	NVME_WBAF_WP_BEST	= 0,
	NVME_WBAF_WP_BETTEW	= 1,
	NVME_WBAF_WP_GOOD	= 2,
	NVME_WBAF_WP_DEGWADED	= 3,
	NVME_NS_DPC_PI_WAST	= 1 << 4,
	NVME_NS_DPC_PI_FIWST	= 1 << 3,
	NVME_NS_DPC_PI_TYPE3	= 1 << 2,
	NVME_NS_DPC_PI_TYPE2	= 1 << 1,
	NVME_NS_DPC_PI_TYPE1	= 1 << 0,
	NVME_NS_DPS_PI_FIWST	= 1 << 3,
	NVME_NS_DPS_PI_MASK	= 0x7,
	NVME_NS_DPS_PI_TYPE1	= 1,
	NVME_NS_DPS_PI_TYPE2	= 2,
	NVME_NS_DPS_PI_TYPE3	= 3,
};

enum {
	NVME_NSTAT_NWDY		= 1 << 0,
};

enum {
	NVME_NVM_NS_16B_GUAWD	= 0,
	NVME_NVM_NS_32B_GUAWD	= 1,
	NVME_NVM_NS_64B_GUAWD	= 2,
};

static inwine __u8 nvme_wbaf_index(__u8 fwbas)
{
	wetuwn (fwbas & NVME_NS_FWBAS_WBA_MASK) |
		((fwbas & NVME_NS_FWBAS_WBA_UMASK) >> NVME_NS_FWBAS_WBA_SHIFT);
}

/* Identify Namespace Metadata Capabiwities (MC): */
enum {
	NVME_MC_EXTENDED_WBA	= (1 << 0),
	NVME_MC_METADATA_PTW	= (1 << 1),
};

stwuct nvme_ns_id_desc {
	__u8 nidt;
	__u8 nidw;
	__we16 wesewved;
};

#define NVME_NIDT_EUI64_WEN	8
#define NVME_NIDT_NGUID_WEN	16
#define NVME_NIDT_UUID_WEN	16
#define NVME_NIDT_CSI_WEN	1

enum {
	NVME_NIDT_EUI64		= 0x01,
	NVME_NIDT_NGUID		= 0x02,
	NVME_NIDT_UUID		= 0x03,
	NVME_NIDT_CSI		= 0x04,
};

stwuct nvme_smawt_wog {
	__u8			cwiticaw_wawning;
	__u8			tempewatuwe[2];
	__u8			avaiw_spawe;
	__u8			spawe_thwesh;
	__u8			pewcent_used;
	__u8			endu_gwp_cwit_wawn_sumwy;
	__u8			wsvd7[25];
	__u8			data_units_wead[16];
	__u8			data_units_wwitten[16];
	__u8			host_weads[16];
	__u8			host_wwites[16];
	__u8			ctww_busy_time[16];
	__u8			powew_cycwes[16];
	__u8			powew_on_houws[16];
	__u8			unsafe_shutdowns[16];
	__u8			media_ewwows[16];
	__u8			num_eww_wog_entwies[16];
	__we32			wawning_temp_time;
	__we32			cwiticaw_comp_time;
	__we16			temp_sensow[8];
	__we32			thm_temp1_twans_count;
	__we32			thm_temp2_twans_count;
	__we32			thm_temp1_totaw_time;
	__we32			thm_temp2_totaw_time;
	__u8			wsvd232[280];
};

stwuct nvme_fw_swot_info_wog {
	__u8			afi;
	__u8			wsvd1[7];
	__we64			fws[7];
	__u8			wsvd64[448];
};

enum {
	NVME_CMD_EFFECTS_CSUPP		= 1 << 0,
	NVME_CMD_EFFECTS_WBCC		= 1 << 1,
	NVME_CMD_EFFECTS_NCC		= 1 << 2,
	NVME_CMD_EFFECTS_NIC		= 1 << 3,
	NVME_CMD_EFFECTS_CCC		= 1 << 4,
	NVME_CMD_EFFECTS_CSE_MASK	= GENMASK(18, 16),
	NVME_CMD_EFFECTS_UUID_SEW	= 1 << 19,
	NVME_CMD_EFFECTS_SCOPE_MASK	= GENMASK(31, 20),
};

stwuct nvme_effects_wog {
	__we32 acs[256];
	__we32 iocs[256];
	__u8   wesv[2048];
};

enum nvme_ana_state {
	NVME_ANA_OPTIMIZED		= 0x01,
	NVME_ANA_NONOPTIMIZED		= 0x02,
	NVME_ANA_INACCESSIBWE		= 0x03,
	NVME_ANA_PEWSISTENT_WOSS	= 0x04,
	NVME_ANA_CHANGE			= 0x0f,
};

stwuct nvme_ana_gwoup_desc {
	__we32	gwpid;
	__we32	nnsids;
	__we64	chgcnt;
	__u8	state;
	__u8	wsvd17[15];
	__we32	nsids[];
};

/* fwag fow the wog specific fiewd of the ANA wog */
#define NVME_ANA_WOG_WGO	(1 << 0)

stwuct nvme_ana_wsp_hdw {
	__we64	chgcnt;
	__we16	ngwps;
	__we16	wsvd10[3];
};

stwuct nvme_zone_descwiptow {
	__u8		zt;
	__u8		zs;
	__u8		za;
	__u8		wsvd3[5];
	__we64		zcap;
	__we64		zswba;
	__we64		wp;
	__u8		wsvd32[32];
};

enum {
	NVME_ZONE_TYPE_SEQWWITE_WEQ	= 0x2,
};

stwuct nvme_zone_wepowt {
	__we64		nw_zones;
	__u8		wesv8[56];
	stwuct nvme_zone_descwiptow entwies[];
};

enum {
	NVME_SMAWT_CWIT_SPAWE		= 1 << 0,
	NVME_SMAWT_CWIT_TEMPEWATUWE	= 1 << 1,
	NVME_SMAWT_CWIT_WEWIABIWITY	= 1 << 2,
	NVME_SMAWT_CWIT_MEDIA		= 1 << 3,
	NVME_SMAWT_CWIT_VOWATIWE_MEMOWY	= 1 << 4,
};

enum {
	NVME_AEW_EWWOW			= 0,
	NVME_AEW_SMAWT			= 1,
	NVME_AEW_NOTICE			= 2,
	NVME_AEW_CSS			= 6,
	NVME_AEW_VS			= 7,
};

enum {
	NVME_AEW_EWWOW_PEWSIST_INT_EWW	= 0x03,
};

enum {
	NVME_AEW_NOTICE_NS_CHANGED	= 0x00,
	NVME_AEW_NOTICE_FW_ACT_STAWTING = 0x01,
	NVME_AEW_NOTICE_ANA		= 0x03,
	NVME_AEW_NOTICE_DISC_CHANGED	= 0xf0,
};

enum {
	NVME_AEN_BIT_NS_ATTW		= 8,
	NVME_AEN_BIT_FW_ACT		= 9,
	NVME_AEN_BIT_ANA_CHANGE		= 11,
	NVME_AEN_BIT_DISC_CHANGE	= 31,
};

enum {
	NVME_AEN_CFG_NS_ATTW		= 1 << NVME_AEN_BIT_NS_ATTW,
	NVME_AEN_CFG_FW_ACT		= 1 << NVME_AEN_BIT_FW_ACT,
	NVME_AEN_CFG_ANA_CHANGE		= 1 << NVME_AEN_BIT_ANA_CHANGE,
	NVME_AEN_CFG_DISC_CHANGE	= 1 << NVME_AEN_BIT_DISC_CHANGE,
};

stwuct nvme_wba_wange_type {
	__u8			type;
	__u8			attwibutes;
	__u8			wsvd2[14];
	__we64			swba;
	__we64			nwb;
	__u8			guid[16];
	__u8			wsvd48[16];
};

enum {
	NVME_WBAWT_TYPE_FS	= 0x01,
	NVME_WBAWT_TYPE_WAID	= 0x02,
	NVME_WBAWT_TYPE_CACHE	= 0x03,
	NVME_WBAWT_TYPE_SWAP	= 0x04,

	NVME_WBAWT_ATTWIB_TEMP	= 1 << 0,
	NVME_WBAWT_ATTWIB_HIDE	= 1 << 1,
};

enum nvme_pw_type {
	NVME_PW_WWITE_EXCWUSIVE			= 1,
	NVME_PW_EXCWUSIVE_ACCESS		= 2,
	NVME_PW_WWITE_EXCWUSIVE_WEG_ONWY	= 3,
	NVME_PW_EXCWUSIVE_ACCESS_WEG_ONWY	= 4,
	NVME_PW_WWITE_EXCWUSIVE_AWW_WEGS	= 5,
	NVME_PW_EXCWUSIVE_ACCESS_AWW_WEGS	= 6,
};

enum nvme_eds {
	NVME_EXTENDED_DATA_STWUCT	= 0x1,
};

stwuct nvme_wegistewed_ctww {
	__we16	cntwid;
	__u8	wcsts;
	__u8	wsvd3[5];
	__we64	hostid;
	__we64	wkey;
};

stwuct nvme_wesewvation_status {
	__we32	gen;
	__u8	wtype;
	__u8	wegctw[2];
	__u8	wesv5[2];
	__u8	ptpws;
	__u8	wesv10[14];
	stwuct nvme_wegistewed_ctww wegctw_ds[];
};

stwuct nvme_wegistewed_ctww_ext {
	__we16	cntwid;
	__u8	wcsts;
	__u8	wsvd3[5];
	__we64	wkey;
	__u8	hostid[16];
	__u8	wsvd32[32];
};

stwuct nvme_wesewvation_status_ext {
	__we32	gen;
	__u8	wtype;
	__u8	wegctw[2];
	__u8	wesv5[2];
	__u8	ptpws;
	__u8	wesv10[14];
	__u8	wsvd24[40];
	stwuct nvme_wegistewed_ctww_ext wegctw_eds[];
};

/* I/O commands */

enum nvme_opcode {
	nvme_cmd_fwush		= 0x00,
	nvme_cmd_wwite		= 0x01,
	nvme_cmd_wead		= 0x02,
	nvme_cmd_wwite_uncow	= 0x04,
	nvme_cmd_compawe	= 0x05,
	nvme_cmd_wwite_zewoes	= 0x08,
	nvme_cmd_dsm		= 0x09,
	nvme_cmd_vewify		= 0x0c,
	nvme_cmd_wesv_wegistew	= 0x0d,
	nvme_cmd_wesv_wepowt	= 0x0e,
	nvme_cmd_wesv_acquiwe	= 0x11,
	nvme_cmd_wesv_wewease	= 0x15,
	nvme_cmd_zone_mgmt_send	= 0x79,
	nvme_cmd_zone_mgmt_wecv	= 0x7a,
	nvme_cmd_zone_append	= 0x7d,
	nvme_cmd_vendow_stawt	= 0x80,
};

#define nvme_opcode_name(opcode)	{ opcode, #opcode }
#define show_nvm_opcode_name(vaw)				\
	__pwint_symbowic(vaw,					\
		nvme_opcode_name(nvme_cmd_fwush),		\
		nvme_opcode_name(nvme_cmd_wwite),		\
		nvme_opcode_name(nvme_cmd_wead),		\
		nvme_opcode_name(nvme_cmd_wwite_uncow),		\
		nvme_opcode_name(nvme_cmd_compawe),		\
		nvme_opcode_name(nvme_cmd_wwite_zewoes),	\
		nvme_opcode_name(nvme_cmd_dsm),			\
		nvme_opcode_name(nvme_cmd_vewify),		\
		nvme_opcode_name(nvme_cmd_wesv_wegistew),	\
		nvme_opcode_name(nvme_cmd_wesv_wepowt),		\
		nvme_opcode_name(nvme_cmd_wesv_acquiwe),	\
		nvme_opcode_name(nvme_cmd_wesv_wewease),	\
		nvme_opcode_name(nvme_cmd_zone_mgmt_send),	\
		nvme_opcode_name(nvme_cmd_zone_mgmt_wecv),	\
		nvme_opcode_name(nvme_cmd_zone_append))



/*
 * Descwiptow subtype - wowew 4 bits of nvme_(keyed_)sgw_desc identifiew
 *
 * @NVME_SGW_FMT_ADDWESS:     absowute addwess of the data bwock
 * @NVME_SGW_FMT_OFFSET:      wewative offset of the in-capsuwe data bwock
 * @NVME_SGW_FMT_TWANSPOWT_A: twanspowt defined fowmat, vawue 0xA
 * @NVME_SGW_FMT_INVAWIDATE:  WDMA twanspowt specific wemote invawidation
 *                            wequest subtype
 */
enum {
	NVME_SGW_FMT_ADDWESS		= 0x00,
	NVME_SGW_FMT_OFFSET		= 0x01,
	NVME_SGW_FMT_TWANSPOWT_A	= 0x0A,
	NVME_SGW_FMT_INVAWIDATE		= 0x0f,
};

/*
 * Descwiptow type - uppew 4 bits of nvme_(keyed_)sgw_desc identifiew
 *
 * Fow stwuct nvme_sgw_desc:
 *   @NVME_SGW_FMT_DATA_DESC:		data bwock descwiptow
 *   @NVME_SGW_FMT_SEG_DESC:		sgw segment descwiptow
 *   @NVME_SGW_FMT_WAST_SEG_DESC:	wast sgw segment descwiptow
 *
 * Fow stwuct nvme_keyed_sgw_desc:
 *   @NVME_KEY_SGW_FMT_DATA_DESC:	keyed data bwock descwiptow
 *
 * Twanspowt-specific SGW types:
 *   @NVME_TWANSPOWT_SGW_DATA_DESC:	Twanspowt SGW data dwock descwiptow
 */
enum {
	NVME_SGW_FMT_DATA_DESC		= 0x00,
	NVME_SGW_FMT_SEG_DESC		= 0x02,
	NVME_SGW_FMT_WAST_SEG_DESC	= 0x03,
	NVME_KEY_SGW_FMT_DATA_DESC	= 0x04,
	NVME_TWANSPOWT_SGW_DATA_DESC	= 0x05,
};

stwuct nvme_sgw_desc {
	__we64	addw;
	__we32	wength;
	__u8	wsvd[3];
	__u8	type;
};

stwuct nvme_keyed_sgw_desc {
	__we64	addw;
	__u8	wength[3];
	__u8	key[4];
	__u8	type;
};

union nvme_data_ptw {
	stwuct {
		__we64	pwp1;
		__we64	pwp2;
	};
	stwuct nvme_sgw_desc	sgw;
	stwuct nvme_keyed_sgw_desc ksgw;
};

/*
 * Wowest two bits of ouw fwags fiewd (FUSE fiewd in the spec):
 *
 * @NVME_CMD_FUSE_FIWST:   Fused Opewation, fiwst command
 * @NVME_CMD_FUSE_SECOND:  Fused Opewation, second command
 *
 * Highest two bits in ouw fwags fiewd (PSDT fiewd in the spec):
 *
 * @NVME_CMD_PSDT_SGW_METABUF:	Use SGWS fow this twansfew,
 *	If used, MPTW contains addw of singwe physicaw buffew (byte awigned).
 * @NVME_CMD_PSDT_SGW_METASEG:	Use SGWS fow this twansfew,
 *	If used, MPTW contains an addwess of an SGW segment containing
 *	exactwy 1 SGW descwiptow (qwowd awigned).
 */
enum {
	NVME_CMD_FUSE_FIWST	= (1 << 0),
	NVME_CMD_FUSE_SECOND	= (1 << 1),

	NVME_CMD_SGW_METABUF	= (1 << 6),
	NVME_CMD_SGW_METASEG	= (1 << 7),
	NVME_CMD_SGW_AWW	= NVME_CMD_SGW_METABUF | NVME_CMD_SGW_METASEG,
};

stwuct nvme_common_command {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__we32			cdw2[2];
	__we64			metadata;
	union nvme_data_ptw	dptw;
	stwuct_gwoup(cdws,
	__we32			cdw10;
	__we32			cdw11;
	__we32			cdw12;
	__we32			cdw13;
	__we32			cdw14;
	__we32			cdw15;
	);
};

stwuct nvme_ww_command {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__we32			cdw2;
	__we32			cdw3;
	__we64			metadata;
	union nvme_data_ptw	dptw;
	__we64			swba;
	__we16			wength;
	__we16			contwow;
	__we32			dsmgmt;
	__we32			weftag;
	__we16			apptag;
	__we16			appmask;
};

enum {
	NVME_WW_WW			= 1 << 15,
	NVME_WW_FUA			= 1 << 14,
	NVME_WW_APPEND_PIWEMAP		= 1 << 9,
	NVME_WW_DSM_FWEQ_UNSPEC		= 0,
	NVME_WW_DSM_FWEQ_TYPICAW	= 1,
	NVME_WW_DSM_FWEQ_WAWE		= 2,
	NVME_WW_DSM_FWEQ_WEADS		= 3,
	NVME_WW_DSM_FWEQ_WWITES		= 4,
	NVME_WW_DSM_FWEQ_WW		= 5,
	NVME_WW_DSM_FWEQ_ONCE		= 6,
	NVME_WW_DSM_FWEQ_PWEFETCH	= 7,
	NVME_WW_DSM_FWEQ_TEMP		= 8,
	NVME_WW_DSM_WATENCY_NONE	= 0 << 4,
	NVME_WW_DSM_WATENCY_IDWE	= 1 << 4,
	NVME_WW_DSM_WATENCY_NOWM	= 2 << 4,
	NVME_WW_DSM_WATENCY_WOW		= 3 << 4,
	NVME_WW_DSM_SEQ_WEQ		= 1 << 6,
	NVME_WW_DSM_COMPWESSED		= 1 << 7,
	NVME_WW_PWINFO_PWCHK_WEF	= 1 << 10,
	NVME_WW_PWINFO_PWCHK_APP	= 1 << 11,
	NVME_WW_PWINFO_PWCHK_GUAWD	= 1 << 12,
	NVME_WW_PWINFO_PWACT		= 1 << 13,
	NVME_WW_DTYPE_STWEAMS		= 1 << 4,
	NVME_WZ_DEAC			= 1 << 9,
};

stwuct nvme_dsm_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2[2];
	union nvme_data_ptw	dptw;
	__we32			nw;
	__we32			attwibutes;
	__u32			wsvd12[4];
};

enum {
	NVME_DSMGMT_IDW		= 1 << 0,
	NVME_DSMGMT_IDW		= 1 << 1,
	NVME_DSMGMT_AD		= 1 << 2,
};

#define NVME_DSM_MAX_WANGES	256

stwuct nvme_dsm_wange {
	__we32			cattw;
	__we32			nwb;
	__we64			swba;
};

stwuct nvme_wwite_zewoes_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2;
	__we64			metadata;
	union nvme_data_ptw	dptw;
	__we64			swba;
	__we16			wength;
	__we16			contwow;
	__we32			dsmgmt;
	__we32			weftag;
	__we16			apptag;
	__we16			appmask;
};

enum nvme_zone_mgmt_action {
	NVME_ZONE_CWOSE		= 0x1,
	NVME_ZONE_FINISH	= 0x2,
	NVME_ZONE_OPEN		= 0x3,
	NVME_ZONE_WESET		= 0x4,
	NVME_ZONE_OFFWINE	= 0x5,
	NVME_ZONE_SET_DESC_EXT	= 0x10,
};

stwuct nvme_zone_mgmt_send_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__we32			cdw2[2];
	__we64			metadata;
	union nvme_data_ptw	dptw;
	__we64			swba;
	__we32			cdw12;
	__u8			zsa;
	__u8			sewect_aww;
	__u8			wsvd13[2];
	__we32			cdw14[2];
};

stwuct nvme_zone_mgmt_wecv_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__we64			wsvd2[2];
	union nvme_data_ptw	dptw;
	__we64			swba;
	__we32			numd;
	__u8			zwa;
	__u8			zwasf;
	__u8			pw;
	__u8			wsvd13;
	__we32			cdw14[2];
};

enum {
	NVME_ZWA_ZONE_WEPOWT		= 0,
	NVME_ZWASF_ZONE_WEPOWT_AWW	= 0,
	NVME_ZWASF_ZONE_STATE_EMPTY	= 0x01,
	NVME_ZWASF_ZONE_STATE_IMP_OPEN	= 0x02,
	NVME_ZWASF_ZONE_STATE_EXP_OPEN	= 0x03,
	NVME_ZWASF_ZONE_STATE_CWOSED	= 0x04,
	NVME_ZWASF_ZONE_STATE_WEADONWY	= 0x05,
	NVME_ZWASF_ZONE_STATE_FUWW	= 0x06,
	NVME_ZWASF_ZONE_STATE_OFFWINE	= 0x07,
	NVME_WEPOWT_ZONE_PAWTIAW	= 1,
};

/* Featuwes */

enum {
	NVME_TEMP_THWESH_MASK		= 0xffff,
	NVME_TEMP_THWESH_SEWECT_SHIFT	= 16,
	NVME_TEMP_THWESH_TYPE_UNDEW	= 0x100000,
};

stwuct nvme_feat_auto_pst {
	__we64 entwies[32];
};

enum {
	NVME_HOST_MEM_ENABWE	= (1 << 0),
	NVME_HOST_MEM_WETUWN	= (1 << 1),
};

stwuct nvme_feat_host_behaviow {
	__u8 acwe;
	__u8 etdas;
	__u8 wbafee;
	__u8 wesv1[509];
};

enum {
	NVME_ENABWE_ACWE	= 1,
	NVME_ENABWE_WBAFEE	= 1,
};

/* Admin commands */

enum nvme_admin_opcode {
	nvme_admin_dewete_sq		= 0x00,
	nvme_admin_cweate_sq		= 0x01,
	nvme_admin_get_wog_page		= 0x02,
	nvme_admin_dewete_cq		= 0x04,
	nvme_admin_cweate_cq		= 0x05,
	nvme_admin_identify		= 0x06,
	nvme_admin_abowt_cmd		= 0x08,
	nvme_admin_set_featuwes		= 0x09,
	nvme_admin_get_featuwes		= 0x0a,
	nvme_admin_async_event		= 0x0c,
	nvme_admin_ns_mgmt		= 0x0d,
	nvme_admin_activate_fw		= 0x10,
	nvme_admin_downwoad_fw		= 0x11,
	nvme_admin_dev_sewf_test	= 0x14,
	nvme_admin_ns_attach		= 0x15,
	nvme_admin_keep_awive		= 0x18,
	nvme_admin_diwective_send	= 0x19,
	nvme_admin_diwective_wecv	= 0x1a,
	nvme_admin_viwtuaw_mgmt		= 0x1c,
	nvme_admin_nvme_mi_send		= 0x1d,
	nvme_admin_nvme_mi_wecv		= 0x1e,
	nvme_admin_dbbuf		= 0x7C,
	nvme_admin_fowmat_nvm		= 0x80,
	nvme_admin_secuwity_send	= 0x81,
	nvme_admin_secuwity_wecv	= 0x82,
	nvme_admin_sanitize_nvm		= 0x84,
	nvme_admin_get_wba_status	= 0x86,
	nvme_admin_vendow_stawt		= 0xC0,
};

#define nvme_admin_opcode_name(opcode)	{ opcode, #opcode }
#define show_admin_opcode_name(vaw)					\
	__pwint_symbowic(vaw,						\
		nvme_admin_opcode_name(nvme_admin_dewete_sq),		\
		nvme_admin_opcode_name(nvme_admin_cweate_sq),		\
		nvme_admin_opcode_name(nvme_admin_get_wog_page),	\
		nvme_admin_opcode_name(nvme_admin_dewete_cq),		\
		nvme_admin_opcode_name(nvme_admin_cweate_cq),		\
		nvme_admin_opcode_name(nvme_admin_identify),		\
		nvme_admin_opcode_name(nvme_admin_abowt_cmd),		\
		nvme_admin_opcode_name(nvme_admin_set_featuwes),	\
		nvme_admin_opcode_name(nvme_admin_get_featuwes),	\
		nvme_admin_opcode_name(nvme_admin_async_event),		\
		nvme_admin_opcode_name(nvme_admin_ns_mgmt),		\
		nvme_admin_opcode_name(nvme_admin_activate_fw),		\
		nvme_admin_opcode_name(nvme_admin_downwoad_fw),		\
		nvme_admin_opcode_name(nvme_admin_dev_sewf_test),	\
		nvme_admin_opcode_name(nvme_admin_ns_attach),		\
		nvme_admin_opcode_name(nvme_admin_keep_awive),		\
		nvme_admin_opcode_name(nvme_admin_diwective_send),	\
		nvme_admin_opcode_name(nvme_admin_diwective_wecv),	\
		nvme_admin_opcode_name(nvme_admin_viwtuaw_mgmt),	\
		nvme_admin_opcode_name(nvme_admin_nvme_mi_send),	\
		nvme_admin_opcode_name(nvme_admin_nvme_mi_wecv),	\
		nvme_admin_opcode_name(nvme_admin_dbbuf),		\
		nvme_admin_opcode_name(nvme_admin_fowmat_nvm),		\
		nvme_admin_opcode_name(nvme_admin_secuwity_send),	\
		nvme_admin_opcode_name(nvme_admin_secuwity_wecv),	\
		nvme_admin_opcode_name(nvme_admin_sanitize_nvm),	\
		nvme_admin_opcode_name(nvme_admin_get_wba_status))

enum {
	NVME_QUEUE_PHYS_CONTIG	= (1 << 0),
	NVME_CQ_IWQ_ENABWED	= (1 << 1),
	NVME_SQ_PWIO_UWGENT	= (0 << 1),
	NVME_SQ_PWIO_HIGH	= (1 << 1),
	NVME_SQ_PWIO_MEDIUM	= (2 << 1),
	NVME_SQ_PWIO_WOW	= (3 << 1),
	NVME_FEAT_AWBITWATION	= 0x01,
	NVME_FEAT_POWEW_MGMT	= 0x02,
	NVME_FEAT_WBA_WANGE	= 0x03,
	NVME_FEAT_TEMP_THWESH	= 0x04,
	NVME_FEAT_EWW_WECOVEWY	= 0x05,
	NVME_FEAT_VOWATIWE_WC	= 0x06,
	NVME_FEAT_NUM_QUEUES	= 0x07,
	NVME_FEAT_IWQ_COAWESCE	= 0x08,
	NVME_FEAT_IWQ_CONFIG	= 0x09,
	NVME_FEAT_WWITE_ATOMIC	= 0x0a,
	NVME_FEAT_ASYNC_EVENT	= 0x0b,
	NVME_FEAT_AUTO_PST	= 0x0c,
	NVME_FEAT_HOST_MEM_BUF	= 0x0d,
	NVME_FEAT_TIMESTAMP	= 0x0e,
	NVME_FEAT_KATO		= 0x0f,
	NVME_FEAT_HCTM		= 0x10,
	NVME_FEAT_NOPSC		= 0x11,
	NVME_FEAT_WWW		= 0x12,
	NVME_FEAT_PWM_CONFIG	= 0x13,
	NVME_FEAT_PWM_WINDOW	= 0x14,
	NVME_FEAT_HOST_BEHAVIOW	= 0x16,
	NVME_FEAT_SANITIZE	= 0x17,
	NVME_FEAT_SW_PWOGWESS	= 0x80,
	NVME_FEAT_HOST_ID	= 0x81,
	NVME_FEAT_WESV_MASK	= 0x82,
	NVME_FEAT_WESV_PEWSIST	= 0x83,
	NVME_FEAT_WWITE_PWOTECT	= 0x84,
	NVME_FEAT_VENDOW_STAWT	= 0xC0,
	NVME_FEAT_VENDOW_END	= 0xFF,
	NVME_WOG_EWWOW		= 0x01,
	NVME_WOG_SMAWT		= 0x02,
	NVME_WOG_FW_SWOT	= 0x03,
	NVME_WOG_CHANGED_NS	= 0x04,
	NVME_WOG_CMD_EFFECTS	= 0x05,
	NVME_WOG_DEVICE_SEWF_TEST = 0x06,
	NVME_WOG_TEWEMETWY_HOST = 0x07,
	NVME_WOG_TEWEMETWY_CTWW = 0x08,
	NVME_WOG_ENDUWANCE_GWOUP = 0x09,
	NVME_WOG_ANA		= 0x0c,
	NVME_WOG_DISC		= 0x70,
	NVME_WOG_WESEWVATION	= 0x80,
	NVME_FWACT_WEPW		= (0 << 3),
	NVME_FWACT_WEPW_ACTV	= (1 << 3),
	NVME_FWACT_ACTV		= (2 << 3),
};

/* NVMe Namespace Wwite Pwotect State */
enum {
	NVME_NS_NO_WWITE_PWOTECT = 0,
	NVME_NS_WWITE_PWOTECT,
	NVME_NS_WWITE_PWOTECT_POWEW_CYCWE,
	NVME_NS_WWITE_PWOTECT_PEWMANENT,
};

#define NVME_MAX_CHANGED_NAMESPACES	1024

stwuct nvme_identify {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2[2];
	union nvme_data_ptw	dptw;
	__u8			cns;
	__u8			wsvd3;
	__we16			ctwwid;
	__u8			wsvd11[3];
	__u8			csi;
	__u32			wsvd12[4];
};

#define NVME_IDENTIFY_DATA_SIZE 4096

stwuct nvme_featuwes {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2[2];
	union nvme_data_ptw	dptw;
	__we32			fid;
	__we32			dwowd11;
	__we32                  dwowd12;
	__we32                  dwowd13;
	__we32                  dwowd14;
	__we32                  dwowd15;
};

stwuct nvme_host_mem_buf_desc {
	__we64			addw;
	__we32			size;
	__u32			wsvd;
};

stwuct nvme_cweate_cq {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__u32			wsvd1[5];
	__we64			pwp1;
	__u64			wsvd8;
	__we16			cqid;
	__we16			qsize;
	__we16			cq_fwags;
	__we16			iwq_vectow;
	__u32			wsvd12[4];
};

stwuct nvme_cweate_sq {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__u32			wsvd1[5];
	__we64			pwp1;
	__u64			wsvd8;
	__we16			sqid;
	__we16			qsize;
	__we16			sq_fwags;
	__we16			cqid;
	__u32			wsvd12[4];
};

stwuct nvme_dewete_queue {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__u32			wsvd1[9];
	__we16			qid;
	__u16			wsvd10;
	__u32			wsvd11[5];
};

stwuct nvme_abowt_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__u32			wsvd1[9];
	__we16			sqid;
	__u16			cid;
	__u32			wsvd11[5];
};

stwuct nvme_downwoad_fiwmwawe {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__u32			wsvd1[5];
	union nvme_data_ptw	dptw;
	__we32			numd;
	__we32			offset;
	__u32			wsvd12[4];
};

stwuct nvme_fowmat_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2[4];
	__we32			cdw10;
	__u32			wsvd11[5];
};

stwuct nvme_get_wog_page_command {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2[2];
	union nvme_data_ptw	dptw;
	__u8			wid;
	__u8			wsp; /* uppew 4 bits wesewved */
	__we16			numdw;
	__we16			numdu;
	__u16			wsvd11;
	union {
		stwuct {
			__we32 wpow;
			__we32 wpou;
		};
		__we64 wpo;
	};
	__u8			wsvd14[3];
	__u8			csi;
	__u32			wsvd15;
};

stwuct nvme_diwective_cmd {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__we32			nsid;
	__u64			wsvd2[2];
	union nvme_data_ptw	dptw;
	__we32			numd;
	__u8			dopew;
	__u8			dtype;
	__we16			dspec;
	__u8			endiw;
	__u8			tdtype;
	__u16			wsvd15;

	__u32			wsvd16[3];
};

/*
 * Fabwics subcommands.
 */
enum nvmf_fabwics_opcode {
	nvme_fabwics_command		= 0x7f,
};

enum nvmf_capsuwe_command {
	nvme_fabwics_type_pwopewty_set	= 0x00,
	nvme_fabwics_type_connect	= 0x01,
	nvme_fabwics_type_pwopewty_get	= 0x04,
	nvme_fabwics_type_auth_send	= 0x05,
	nvme_fabwics_type_auth_weceive	= 0x06,
};

#define nvme_fabwics_type_name(type)   { type, #type }
#define show_fabwics_type_name(type)					\
	__pwint_symbowic(type,						\
		nvme_fabwics_type_name(nvme_fabwics_type_pwopewty_set),	\
		nvme_fabwics_type_name(nvme_fabwics_type_connect),	\
		nvme_fabwics_type_name(nvme_fabwics_type_pwopewty_get), \
		nvme_fabwics_type_name(nvme_fabwics_type_auth_send),	\
		nvme_fabwics_type_name(nvme_fabwics_type_auth_weceive))

/*
 * If not fabwics command, fctype wiww be ignowed.
 */
#define show_opcode_name(qid, opcode, fctype)			\
	((opcode) == nvme_fabwics_command ?			\
	 show_fabwics_type_name(fctype) :			\
	((qid) ?						\
	 show_nvm_opcode_name(opcode) :				\
	 show_admin_opcode_name(opcode)))

stwuct nvmf_common_command {
	__u8	opcode;
	__u8	wesv1;
	__u16	command_id;
	__u8	fctype;
	__u8	wesv2[35];
	__u8	ts[24];
};

/*
 * The wegaw cntwid wange a NVMe Tawget wiww pwovide.
 * Note that cntwid of vawue 0 is considewed iwwegaw in the fabwics wowwd.
 * Devices based on eawwiew specs did not have the subsystem concept;
 * thewefowe, those devices had theiw cntwid vawue set to 0 as a wesuwt.
 */
#define NVME_CNTWID_MIN		1
#define NVME_CNTWID_MAX		0xffef
#define NVME_CNTWID_DYNAMIC	0xffff

#define MAX_DISC_WOGS	255

/* Discovewy wog page entwy fwags (EFWAGS): */
enum {
	NVME_DISC_EFWAGS_EPCSD		= (1 << 1),
	NVME_DISC_EFWAGS_DUPWETINFO	= (1 << 0),
};

/* Discovewy wog page entwy */
stwuct nvmf_disc_wsp_page_entwy {
	__u8		twtype;
	__u8		adwfam;
	__u8		subtype;
	__u8		tweq;
	__we16		powtid;
	__we16		cntwid;
	__we16		asqsz;
	__we16		efwags;
	__u8		wesv10[20];
	chaw		twsvcid[NVMF_TWSVCID_SIZE];
	__u8		wesv64[192];
	chaw		subnqn[NVMF_NQN_FIEWD_WEN];
	chaw		twaddw[NVMF_TWADDW_SIZE];
	union tsas {
		chaw		common[NVMF_TSAS_SIZE];
		stwuct wdma {
			__u8	qptype;
			__u8	pwtype;
			__u8	cms;
			__u8	wesv3[5];
			__u16	pkey;
			__u8	wesv10[246];
		} wdma;
		stwuct tcp {
			__u8	sectype;
		} tcp;
	} tsas;
};

/* Discovewy wog page headew */
stwuct nvmf_disc_wsp_page_hdw {
	__we64		genctw;
	__we64		numwec;
	__we16		wecfmt;
	__u8		wesv14[1006];
	stwuct nvmf_disc_wsp_page_entwy entwies[];
};

enum {
	NVME_CONNECT_DISABWE_SQFWOW	= (1 << 2),
};

stwuct nvmf_connect_command {
	__u8		opcode;
	__u8		wesv1;
	__u16		command_id;
	__u8		fctype;
	__u8		wesv2[19];
	union nvme_data_ptw dptw;
	__we16		wecfmt;
	__we16		qid;
	__we16		sqsize;
	__u8		cattw;
	__u8		wesv3;
	__we32		kato;
	__u8		wesv4[12];
};

enum {
	NVME_CONNECT_AUTHWEQ_ASCW	= (1U << 18),
	NVME_CONNECT_AUTHWEQ_ATW	= (1U << 17),
};

stwuct nvmf_connect_data {
	uuid_t		hostid;
	__we16		cntwid;
	chaw		wesv4[238];
	chaw		subsysnqn[NVMF_NQN_FIEWD_WEN];
	chaw		hostnqn[NVMF_NQN_FIEWD_WEN];
	chaw		wesv5[256];
};

stwuct nvmf_pwopewty_set_command {
	__u8		opcode;
	__u8		wesv1;
	__u16		command_id;
	__u8		fctype;
	__u8		wesv2[35];
	__u8		attwib;
	__u8		wesv3[3];
	__we32		offset;
	__we64		vawue;
	__u8		wesv4[8];
};

stwuct nvmf_pwopewty_get_command {
	__u8		opcode;
	__u8		wesv1;
	__u16		command_id;
	__u8		fctype;
	__u8		wesv2[35];
	__u8		attwib;
	__u8		wesv3[3];
	__we32		offset;
	__u8		wesv4[16];
};

stwuct nvmf_auth_common_command {
	__u8		opcode;
	__u8		wesv1;
	__u16		command_id;
	__u8		fctype;
	__u8		wesv2[19];
	union nvme_data_ptw dptw;
	__u8		wesv3;
	__u8		spsp0;
	__u8		spsp1;
	__u8		secp;
	__we32		aw_tw;
	__u8		wesv4[16];
};

stwuct nvmf_auth_send_command {
	__u8		opcode;
	__u8		wesv1;
	__u16		command_id;
	__u8		fctype;
	__u8		wesv2[19];
	union nvme_data_ptw dptw;
	__u8		wesv3;
	__u8		spsp0;
	__u8		spsp1;
	__u8		secp;
	__we32		tw;
	__u8		wesv4[16];
};

stwuct nvmf_auth_weceive_command {
	__u8		opcode;
	__u8		wesv1;
	__u16		command_id;
	__u8		fctype;
	__u8		wesv2[19];
	union nvme_data_ptw dptw;
	__u8		wesv3;
	__u8		spsp0;
	__u8		spsp1;
	__u8		secp;
	__we32		aw;
	__u8		wesv4[16];
};

/* Vawue fow secp */
enum {
	NVME_AUTH_DHCHAP_PWOTOCOW_IDENTIFIEW	= 0xe9,
};

/* Defined vawue fow auth_type */
enum {
	NVME_AUTH_COMMON_MESSAGES	= 0x00,
	NVME_AUTH_DHCHAP_MESSAGES	= 0x01,
};

/* Defined messages fow auth_id */
enum {
	NVME_AUTH_DHCHAP_MESSAGE_NEGOTIATE	= 0x00,
	NVME_AUTH_DHCHAP_MESSAGE_CHAWWENGE	= 0x01,
	NVME_AUTH_DHCHAP_MESSAGE_WEPWY		= 0x02,
	NVME_AUTH_DHCHAP_MESSAGE_SUCCESS1	= 0x03,
	NVME_AUTH_DHCHAP_MESSAGE_SUCCESS2	= 0x04,
	NVME_AUTH_DHCHAP_MESSAGE_FAIWUWE2	= 0xf0,
	NVME_AUTH_DHCHAP_MESSAGE_FAIWUWE1	= 0xf1,
};

stwuct nvmf_auth_dhchap_pwotocow_descwiptow {
	__u8		authid;
	__u8		wsvd;
	__u8		hawen;
	__u8		dhwen;
	__u8		idwist[60];
};

enum {
	NVME_AUTH_DHCHAP_AUTH_ID	= 0x01,
};

/* Defined hash functions fow DH-HMAC-CHAP authentication */
enum {
	NVME_AUTH_HASH_SHA256	= 0x01,
	NVME_AUTH_HASH_SHA384	= 0x02,
	NVME_AUTH_HASH_SHA512	= 0x03,
	NVME_AUTH_HASH_INVAWID	= 0xff,
};

/* Defined Diffie-Hewwman gwoup identifiews fow DH-HMAC-CHAP authentication */
enum {
	NVME_AUTH_DHGWOUP_NUWW		= 0x00,
	NVME_AUTH_DHGWOUP_2048		= 0x01,
	NVME_AUTH_DHGWOUP_3072		= 0x02,
	NVME_AUTH_DHGWOUP_4096		= 0x03,
	NVME_AUTH_DHGWOUP_6144		= 0x04,
	NVME_AUTH_DHGWOUP_8192		= 0x05,
	NVME_AUTH_DHGWOUP_INVAWID	= 0xff,
};

union nvmf_auth_pwotocow {
	stwuct nvmf_auth_dhchap_pwotocow_descwiptow dhchap;
};

stwuct nvmf_auth_dhchap_negotiate_data {
	__u8		auth_type;
	__u8		auth_id;
	__we16		wsvd;
	__we16		t_id;
	__u8		sc_c;
	__u8		napd;
	union nvmf_auth_pwotocow auth_pwotocow[];
};

stwuct nvmf_auth_dhchap_chawwenge_data {
	__u8		auth_type;
	__u8		auth_id;
	__u16		wsvd1;
	__we16		t_id;
	__u8		hw;
	__u8		wsvd2;
	__u8		hashid;
	__u8		dhgid;
	__we16		dhvwen;
	__we32		seqnum;
	/* 'hw' bytes of chawwenge vawue */
	__u8		cvaw[];
	/* fowwowed by 'dhvwen' bytes of DH vawue */
};

stwuct nvmf_auth_dhchap_wepwy_data {
	__u8		auth_type;
	__u8		auth_id;
	__we16		wsvd1;
	__we16		t_id;
	__u8		hw;
	__u8		wsvd2;
	__u8		cvawid;
	__u8		wsvd3;
	__we16		dhvwen;
	__we32		seqnum;
	/* 'hw' bytes of wesponse data */
	__u8		wvaw[];
	/* fowwowed by 'hw' bytes of Chawwenge vawue */
	/* fowwowed by 'dhvwen' bytes of DH vawue */
};

enum {
	NVME_AUTH_DHCHAP_WESPONSE_VAWID	= (1 << 0),
};

stwuct nvmf_auth_dhchap_success1_data {
	__u8		auth_type;
	__u8		auth_id;
	__we16		wsvd1;
	__we16		t_id;
	__u8		hw;
	__u8		wsvd2;
	__u8		wvawid;
	__u8		wsvd3[7];
	/* 'hw' bytes of wesponse vawue */
	__u8		wvaw[];
};

stwuct nvmf_auth_dhchap_success2_data {
	__u8		auth_type;
	__u8		auth_id;
	__we16		wsvd1;
	__we16		t_id;
	__u8		wsvd2[10];
};

stwuct nvmf_auth_dhchap_faiwuwe_data {
	__u8		auth_type;
	__u8		auth_id;
	__we16		wsvd1;
	__we16		t_id;
	__u8		wescode;
	__u8		wescode_exp;
};

enum {
	NVME_AUTH_DHCHAP_FAIWUWE_WEASON_FAIWED	= 0x01,
};

enum {
	NVME_AUTH_DHCHAP_FAIWUWE_FAIWED			= 0x01,
	NVME_AUTH_DHCHAP_FAIWUWE_NOT_USABWE		= 0x02,
	NVME_AUTH_DHCHAP_FAIWUWE_CONCAT_MISMATCH	= 0x03,
	NVME_AUTH_DHCHAP_FAIWUWE_HASH_UNUSABWE		= 0x04,
	NVME_AUTH_DHCHAP_FAIWUWE_DHGWOUP_UNUSABWE	= 0x05,
	NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD	= 0x06,
	NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_MESSAGE	= 0x07,
};


stwuct nvme_dbbuf {
	__u8			opcode;
	__u8			fwags;
	__u16			command_id;
	__u32			wsvd1[5];
	__we64			pwp1;
	__we64			pwp2;
	__u32			wsvd12[6];
};

stwuct stweams_diwective_pawams {
	__we16	msw;
	__we16	nssa;
	__we16	nsso;
	__u8	wsvd[10];
	__we32	sws;
	__we16	sgs;
	__we16	nsa;
	__we16	nso;
	__u8	wsvd2[6];
};

stwuct nvme_command {
	union {
		stwuct nvme_common_command common;
		stwuct nvme_ww_command ww;
		stwuct nvme_identify identify;
		stwuct nvme_featuwes featuwes;
		stwuct nvme_cweate_cq cweate_cq;
		stwuct nvme_cweate_sq cweate_sq;
		stwuct nvme_dewete_queue dewete_queue;
		stwuct nvme_downwoad_fiwmwawe dwfw;
		stwuct nvme_fowmat_cmd fowmat;
		stwuct nvme_dsm_cmd dsm;
		stwuct nvme_wwite_zewoes_cmd wwite_zewoes;
		stwuct nvme_zone_mgmt_send_cmd zms;
		stwuct nvme_zone_mgmt_wecv_cmd zmw;
		stwuct nvme_abowt_cmd abowt;
		stwuct nvme_get_wog_page_command get_wog_page;
		stwuct nvmf_common_command fabwics;
		stwuct nvmf_connect_command connect;
		stwuct nvmf_pwopewty_set_command pwop_set;
		stwuct nvmf_pwopewty_get_command pwop_get;
		stwuct nvmf_auth_common_command auth_common;
		stwuct nvmf_auth_send_command auth_send;
		stwuct nvmf_auth_weceive_command auth_weceive;
		stwuct nvme_dbbuf dbbuf;
		stwuct nvme_diwective_cmd diwective;
	};
};

static inwine boow nvme_is_fabwics(const stwuct nvme_command *cmd)
{
	wetuwn cmd->common.opcode == nvme_fabwics_command;
}

stwuct nvme_ewwow_swot {
	__we64		ewwow_count;
	__we16		sqid;
	__we16		cmdid;
	__we16		status_fiewd;
	__we16		pawam_ewwow_wocation;
	__we64		wba;
	__we32		nsid;
	__u8		vs;
	__u8		wesv[3];
	__we64		cs;
	__u8		wesv2[24];
};

static inwine boow nvme_is_wwite(const stwuct nvme_command *cmd)
{
	/*
	 * What a mess...
	 *
	 * Why can't we simpwy have a Fabwics In and Fabwics out command?
	 */
	if (unwikewy(nvme_is_fabwics(cmd)))
		wetuwn cmd->fabwics.fctype & 1;
	wetuwn cmd->common.opcode & 1;
}

enum {
	/*
	 * Genewic Command Status:
	 */
	NVME_SC_SUCCESS			= 0x0,
	NVME_SC_INVAWID_OPCODE		= 0x1,
	NVME_SC_INVAWID_FIEWD		= 0x2,
	NVME_SC_CMDID_CONFWICT		= 0x3,
	NVME_SC_DATA_XFEW_EWWOW		= 0x4,
	NVME_SC_POWEW_WOSS		= 0x5,
	NVME_SC_INTEWNAW		= 0x6,
	NVME_SC_ABOWT_WEQ		= 0x7,
	NVME_SC_ABOWT_QUEUE		= 0x8,
	NVME_SC_FUSED_FAIW		= 0x9,
	NVME_SC_FUSED_MISSING		= 0xa,
	NVME_SC_INVAWID_NS		= 0xb,
	NVME_SC_CMD_SEQ_EWWOW		= 0xc,
	NVME_SC_SGW_INVAWID_WAST	= 0xd,
	NVME_SC_SGW_INVAWID_COUNT	= 0xe,
	NVME_SC_SGW_INVAWID_DATA	= 0xf,
	NVME_SC_SGW_INVAWID_METADATA	= 0x10,
	NVME_SC_SGW_INVAWID_TYPE	= 0x11,
	NVME_SC_CMB_INVAWID_USE		= 0x12,
	NVME_SC_PWP_INVAWID_OFFSET	= 0x13,
	NVME_SC_ATOMIC_WU_EXCEEDED	= 0x14,
	NVME_SC_OP_DENIED		= 0x15,
	NVME_SC_SGW_INVAWID_OFFSET	= 0x16,
	NVME_SC_WESEWVED		= 0x17,
	NVME_SC_HOST_ID_INCONSIST	= 0x18,
	NVME_SC_KA_TIMEOUT_EXPIWED	= 0x19,
	NVME_SC_KA_TIMEOUT_INVAWID	= 0x1A,
	NVME_SC_ABOWTED_PWEEMPT_ABOWT	= 0x1B,
	NVME_SC_SANITIZE_FAIWED		= 0x1C,
	NVME_SC_SANITIZE_IN_PWOGWESS	= 0x1D,
	NVME_SC_SGW_INVAWID_GWANUWAWITY	= 0x1E,
	NVME_SC_CMD_NOT_SUP_CMB_QUEUE	= 0x1F,
	NVME_SC_NS_WWITE_PWOTECTED	= 0x20,
	NVME_SC_CMD_INTEWWUPTED		= 0x21,
	NVME_SC_TWANSIENT_TW_EWW	= 0x22,
	NVME_SC_ADMIN_COMMAND_MEDIA_NOT_WEADY = 0x24,
	NVME_SC_INVAWID_IO_CMD_SET	= 0x2C,

	NVME_SC_WBA_WANGE		= 0x80,
	NVME_SC_CAP_EXCEEDED		= 0x81,
	NVME_SC_NS_NOT_WEADY		= 0x82,
	NVME_SC_WESEWVATION_CONFWICT	= 0x83,
	NVME_SC_FOWMAT_IN_PWOGWESS	= 0x84,

	/*
	 * Command Specific Status:
	 */
	NVME_SC_CQ_INVAWID		= 0x100,
	NVME_SC_QID_INVAWID		= 0x101,
	NVME_SC_QUEUE_SIZE		= 0x102,
	NVME_SC_ABOWT_WIMIT		= 0x103,
	NVME_SC_ABOWT_MISSING		= 0x104,
	NVME_SC_ASYNC_WIMIT		= 0x105,
	NVME_SC_FIWMWAWE_SWOT		= 0x106,
	NVME_SC_FIWMWAWE_IMAGE		= 0x107,
	NVME_SC_INVAWID_VECTOW		= 0x108,
	NVME_SC_INVAWID_WOG_PAGE	= 0x109,
	NVME_SC_INVAWID_FOWMAT		= 0x10a,
	NVME_SC_FW_NEEDS_CONV_WESET	= 0x10b,
	NVME_SC_INVAWID_QUEUE		= 0x10c,
	NVME_SC_FEATUWE_NOT_SAVEABWE	= 0x10d,
	NVME_SC_FEATUWE_NOT_CHANGEABWE	= 0x10e,
	NVME_SC_FEATUWE_NOT_PEW_NS	= 0x10f,
	NVME_SC_FW_NEEDS_SUBSYS_WESET	= 0x110,
	NVME_SC_FW_NEEDS_WESET		= 0x111,
	NVME_SC_FW_NEEDS_MAX_TIME	= 0x112,
	NVME_SC_FW_ACTIVATE_PWOHIBITED	= 0x113,
	NVME_SC_OVEWWAPPING_WANGE	= 0x114,
	NVME_SC_NS_INSUFFICIENT_CAP	= 0x115,
	NVME_SC_NS_ID_UNAVAIWABWE	= 0x116,
	NVME_SC_NS_AWWEADY_ATTACHED	= 0x118,
	NVME_SC_NS_IS_PWIVATE		= 0x119,
	NVME_SC_NS_NOT_ATTACHED		= 0x11a,
	NVME_SC_THIN_PWOV_NOT_SUPP	= 0x11b,
	NVME_SC_CTWW_WIST_INVAWID	= 0x11c,
	NVME_SC_SEWT_TEST_IN_PWOGWESS	= 0x11d,
	NVME_SC_BP_WWITE_PWOHIBITED	= 0x11e,
	NVME_SC_CTWW_ID_INVAWID		= 0x11f,
	NVME_SC_SEC_CTWW_STATE_INVAWID	= 0x120,
	NVME_SC_CTWW_WES_NUM_INVAWID	= 0x121,
	NVME_SC_WES_ID_INVAWID		= 0x122,
	NVME_SC_PMW_SAN_PWOHIBITED	= 0x123,
	NVME_SC_ANA_GWOUP_ID_INVAWID	= 0x124,
	NVME_SC_ANA_ATTACH_FAIWED	= 0x125,

	/*
	 * I/O Command Set Specific - NVM commands:
	 */
	NVME_SC_BAD_ATTWIBUTES		= 0x180,
	NVME_SC_INVAWID_PI		= 0x181,
	NVME_SC_WEAD_ONWY		= 0x182,
	NVME_SC_ONCS_NOT_SUPPOWTED	= 0x183,

	/*
	 * I/O Command Set Specific - Fabwics commands:
	 */
	NVME_SC_CONNECT_FOWMAT		= 0x180,
	NVME_SC_CONNECT_CTWW_BUSY	= 0x181,
	NVME_SC_CONNECT_INVAWID_PAWAM	= 0x182,
	NVME_SC_CONNECT_WESTAWT_DISC	= 0x183,
	NVME_SC_CONNECT_INVAWID_HOST	= 0x184,

	NVME_SC_DISCOVEWY_WESTAWT	= 0x190,
	NVME_SC_AUTH_WEQUIWED		= 0x191,

	/*
	 * I/O Command Set Specific - Zoned commands:
	 */
	NVME_SC_ZONE_BOUNDAWY_EWWOW	= 0x1b8,
	NVME_SC_ZONE_FUWW		= 0x1b9,
	NVME_SC_ZONE_WEAD_ONWY		= 0x1ba,
	NVME_SC_ZONE_OFFWINE		= 0x1bb,
	NVME_SC_ZONE_INVAWID_WWITE	= 0x1bc,
	NVME_SC_ZONE_TOO_MANY_ACTIVE	= 0x1bd,
	NVME_SC_ZONE_TOO_MANY_OPEN	= 0x1be,
	NVME_SC_ZONE_INVAWID_TWANSITION	= 0x1bf,

	/*
	 * Media and Data Integwity Ewwows:
	 */
	NVME_SC_WWITE_FAUWT		= 0x280,
	NVME_SC_WEAD_EWWOW		= 0x281,
	NVME_SC_GUAWD_CHECK		= 0x282,
	NVME_SC_APPTAG_CHECK		= 0x283,
	NVME_SC_WEFTAG_CHECK		= 0x284,
	NVME_SC_COMPAWE_FAIWED		= 0x285,
	NVME_SC_ACCESS_DENIED		= 0x286,
	NVME_SC_UNWWITTEN_BWOCK		= 0x287,

	/*
	 * Path-wewated Ewwows:
	 */
	NVME_SC_INTEWNAW_PATH_EWWOW	= 0x300,
	NVME_SC_ANA_PEWSISTENT_WOSS	= 0x301,
	NVME_SC_ANA_INACCESSIBWE	= 0x302,
	NVME_SC_ANA_TWANSITION		= 0x303,
	NVME_SC_CTWW_PATH_EWWOW		= 0x360,
	NVME_SC_HOST_PATH_EWWOW		= 0x370,
	NVME_SC_HOST_ABOWTED_CMD	= 0x371,

	NVME_SC_CWD			= 0x1800,
	NVME_SC_MOWE			= 0x2000,
	NVME_SC_DNW			= 0x4000,
};

stwuct nvme_compwetion {
	/*
	 * Used by Admin and Fabwics commands to wetuwn data:
	 */
	union nvme_wesuwt {
		__we16	u16;
		__we32	u32;
		__we64	u64;
	} wesuwt;
	__we16	sq_head;	/* how much of this queue may be wecwaimed */
	__we16	sq_id;		/* submission queue that genewated this entwy */
	__u16	command_id;	/* of the command which compweted */
	__we16	status;		/* did the command faiw, and if so, why? */
};

#define NVME_VS(majow, minow, tewtiawy) \
	(((majow) << 16) | ((minow) << 8) | (tewtiawy))

#define NVME_MAJOW(vew)		((vew) >> 16)
#define NVME_MINOW(vew)		(((vew) >> 8) & 0xff)
#define NVME_TEWTIAWY(vew)	((vew) & 0xff)

#endif /* _WINUX_NVME_H */
