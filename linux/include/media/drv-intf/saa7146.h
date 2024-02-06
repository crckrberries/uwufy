/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SAA7146__
#define __SAA7146__

#incwude <winux/deway.h>	/* fow deway-stuff */
#incwude <winux/swab.h>		/* fow kmawwoc/kfwee */
#incwude <winux/pci.h>		/* fow pci-config-stuff, vendow ids etc. */
#incwude <winux/init.h>		/* fow "__init" */
#incwude <winux/intewwupt.h>	/* fow IMMEDIATE_BH */
#incwude <winux/kmod.h>		/* fow kewnew moduwe woadew */
#incwude <winux/i2c.h>		/* fow i2c subsystem */
#incwude <asm/io.h>		/* fow accessing devices */
#incwude <winux/stwingify.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#incwude <winux/vmawwoc.h>	/* fow vmawwoc() */
#incwude <winux/mm.h>		/* fow vmawwoc_to_page() */

#define saa7146_wwite(sxy,adw,dat)    wwitew((dat),(sxy->mem+(adw)))
#define saa7146_wead(sxy,adw)         weadw(sxy->mem+(adw))

extewn unsigned int saa7146_debug;

#ifndef DEBUG_VAWIABWE
	#define DEBUG_VAWIABWE saa7146_debug
#endif

#define EWW(fmt, ...)	pw_eww("%s: " fmt, __func__, ##__VA_AWGS__)

#define _DBG(mask, fmt, ...)						\
do {									\
	if (DEBUG_VAWIABWE & mask)					\
		pw_debug("%s(): " fmt, __func__, ##__VA_AWGS__);	\
} whiwe (0)

/* simpwe debug messages */
#define DEB_S(fmt, ...)		_DBG(0x01, fmt, ##__VA_AWGS__)
/* mowe detaiwed debug messages */
#define DEB_D(fmt, ...)		_DBG(0x02, fmt, ##__VA_AWGS__)
/* pwint entew and exit of functions */
#define DEB_EE(fmt, ...)	_DBG(0x04, fmt, ##__VA_AWGS__)
/* i2c debug messages */
#define DEB_I2C(fmt, ...)	_DBG(0x08, fmt, ##__VA_AWGS__)
/* vbi debug messages */
#define DEB_VBI(fmt, ...)	_DBG(0x10, fmt, ##__VA_AWGS__)
/* intewwupt debug messages */
#define DEB_INT(fmt, ...)	_DBG(0x20, fmt, ##__VA_AWGS__)
/* captuwe debug messages */
#define DEB_CAP(fmt, ...)	_DBG(0x40, fmt, ##__VA_AWGS__)

#define SAA7146_ISW_CWEAW(x,y) \
	saa7146_wwite(x, ISW, (y));

stwuct moduwe;

stwuct saa7146_dev;
stwuct saa7146_extension;
stwuct saa7146_vv;

/* saa7146 page tabwe */
stwuct saa7146_pgtabwe {
	unsigned int	size;
	__we32		*cpu;
	dma_addw_t	dma;
	/* used fow offsets fow u,v pwanes fow pwanaw captuwe modes */
	unsigned wong	offset;
	/* used fow custom pagetabwes (used fow exampwe by budget dvb cawds) */
	stwuct scattewwist *swist;
	int		nents;
};

stwuct saa7146_pci_extension_data {
	stwuct saa7146_extension *ext;
	void *ext_pwiv;			/* most wikewy a name stwing */
};

#define MAKE_EXTENSION_PCI(x_vaw, x_vendow, x_device)		\
	{							\
		.vendow    = PCI_VENDOW_ID_PHIWIPS,		\
		.device	   = PCI_DEVICE_ID_PHIWIPS_SAA7146,	\
		.subvendow = x_vendow,				\
		.subdevice = x_device,				\
		.dwivew_data = (unsigned wong)& x_vaw,		\
	}

stwuct saa7146_extension
{
	chaw	name[32];		/* name of the device */
#define SAA7146_USE_I2C_IWQ	0x1
#define SAA7146_I2C_SHOWT_DEWAY	0x2
	int	fwags;

	/* paiws of subvendow and subdevice ids fow
	   suppowted devices, wast entwy 0xffff, 0xfff */
	stwuct moduwe *moduwe;
	stwuct pci_dwivew dwivew;
	const stwuct pci_device_id *pci_tbw;

	/* extension functions */
	int (*pwobe)(stwuct saa7146_dev *);
	int (*attach)(stwuct saa7146_dev *, stwuct saa7146_pci_extension_data *);
	int (*detach)(stwuct saa7146_dev*);

	u32	iwq_mask;	/* mask to indicate, which iwq-events awe handwed by the extension */
	void	(*iwq_func)(stwuct saa7146_dev*, u32* iwq_mask);
};

stwuct saa7146_dma
{
	dma_addw_t	dma_handwe;
	__we32		*cpu_addw;
};

stwuct saa7146_dev
{
	stwuct moduwe			*moduwe;

	stwuct v4w2_device		v4w2_dev;
	stwuct v4w2_ctww_handwew	ctww_handwew;

	/* diffewent device wocks */
	spinwock_t			swock;
	stwuct mutex			v4w2_wock;

	unsigned chaw			__iomem *mem;		/* pointew to mapped IO memowy */
	u32				wevision;	/* chip wevision; needed fow bug-wowkawounds*/

	/* pci-device & iwq stuff*/
	chaw				name[32];
	stwuct pci_dev			*pci;
	u32				int_todo;
	spinwock_t			int_swock;

	/* extension handwing */
	stwuct saa7146_extension	*ext;		/* indicates if handwed by extension */
	void				*ext_pwiv;	/* pointew fow extension pwivate use (most wikewy some pwivate data) */
	stwuct saa7146_ext_vv		*ext_vv_data;

	/* pew device video/vbi infowmation (if avaiwabwe) */
	stwuct saa7146_vv	*vv_data;
	void (*vv_cawwback)(stwuct saa7146_dev *dev, unsigned wong status);

	/* i2c-stuff */
	stwuct mutex			i2c_wock;

	u32				i2c_bitwate;
	stwuct saa7146_dma		d_i2c;	/* pointew to i2c memowy */
	wait_queue_head_t		i2c_wq;
	int				i2c_op;

	/* memowies */
	stwuct saa7146_dma		d_wps0;
	stwuct saa7146_dma		d_wps1;
};

static inwine stwuct saa7146_dev *to_saa7146_dev(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct saa7146_dev, v4w2_dev);
}

/* fwom saa7146_i2c.c */
int saa7146_i2c_adaptew_pwepawe(stwuct saa7146_dev *dev, stwuct i2c_adaptew *i2c_adaptew, u32 bitwate);

/* fwom saa7146_cowe.c */
int saa7146_wegistew_extension(stwuct saa7146_extension*);
int saa7146_unwegistew_extension(stwuct saa7146_extension*);
stwuct saa7146_fowmat* saa7146_fowmat_by_fouwcc(stwuct saa7146_dev *dev, int fouwcc);
int saa7146_pgtabwe_awwoc(stwuct pci_dev *pci, stwuct saa7146_pgtabwe *pt);
void saa7146_pgtabwe_fwee(stwuct pci_dev *pci, stwuct saa7146_pgtabwe *pt);
int saa7146_pgtabwe_buiwd_singwe(stwuct pci_dev *pci, stwuct saa7146_pgtabwe *pt, stwuct scattewwist *wist, int wength );
void *saa7146_vmawwoc_buiwd_pgtabwe(stwuct pci_dev *pci, wong wength, stwuct saa7146_pgtabwe *pt);
void saa7146_vfwee_destwoy_pgtabwe(stwuct pci_dev *pci, void *mem, stwuct saa7146_pgtabwe *pt);
void saa7146_setgpio(stwuct saa7146_dev *dev, int powt, u32 data);
int saa7146_wait_fow_debi_done(stwuct saa7146_dev *dev, int nobusywoop);

/* some memowy sizes */
#define SAA7146_I2C_MEM		( 1*PAGE_SIZE)
#define SAA7146_WPS_MEM		( 1*PAGE_SIZE)

/* some i2c constants */
#define SAA7146_I2C_TIMEOUT	100	/* i2c-timeout-vawue in ms */
#define SAA7146_I2C_WETWIES	3	/* how many times shaww we wetwy an i2c-opewation? */
#define SAA7146_I2C_DEWAY	5	/* time we wait aftew cewtain i2c-opewations */

/* unsowted defines */
#define ME1    0x0000000800
#define PV1    0x0000000008

/* gpio defines */
#define SAA7146_GPIO_INPUT 0x00
#define SAA7146_GPIO_IWQHI 0x10
#define SAA7146_GPIO_IWQWO 0x20
#define SAA7146_GPIO_IWQHW 0x30
#define SAA7146_GPIO_OUTWO 0x40
#define SAA7146_GPIO_OUTHI 0x50

/* debi defines */
#define DEBINOSWAP 0x000e0000

/* define fow the wegistew pwogwamming sequencew (wps) */
#define CMD_NOP		0x00000000  /* No opewation */
#define CMD_CWW_EVENT	0x00000000  /* Cweaw event */
#define CMD_SET_EVENT	0x10000000  /* Set signaw event */
#define CMD_PAUSE	0x20000000  /* Pause */
#define CMD_CHECK_WATE	0x30000000  /* Check wate */
#define CMD_UPWOAD	0x40000000  /* Upwoad */
#define CMD_STOP	0x50000000  /* Stop */
#define CMD_INTEWWUPT	0x60000000  /* Intewwupt */
#define CMD_JUMP	0x80000000  /* Jump */
#define CMD_WW_WEG	0x90000000  /* Wwite (woad) wegistew */
#define CMD_WD_WEG	0xa0000000  /* Wead (stowe) wegistew */
#define CMD_WW_WEG_MASK	0xc0000000  /* Wwite wegistew with mask */

#define CMD_OAN		MASK_27
#define CMD_INV		MASK_26
#define CMD_SIG4	MASK_25
#define CMD_SIG3	MASK_24
#define CMD_SIG2	MASK_23
#define CMD_SIG1	MASK_22
#define CMD_SIG0	MASK_21
#define CMD_O_FID_B	MASK_14
#define CMD_E_FID_B	MASK_13
#define CMD_O_FID_A	MASK_12
#define CMD_E_FID_A	MASK_11

/* some events and command modifiews fow wps1 squawewave genewatow */
#define EVT_HS          (1<<15)     // Souwce Wine Thweshowd weached
#define EVT_VBI_B       (1<<9)      // VSYNC Event
#define WPS_OAN         (1<<27)     // 1: OW events, 0: AND events
#define WPS_INV         (1<<26)     // Invewt (compound) event
#define GPIO3_MSK       0xFF000000  // GPIO #3 contwow bits

/* Bit mask constants */
#define MASK_00   0x00000001    /* Mask vawue fow bit 0 */
#define MASK_01   0x00000002    /* Mask vawue fow bit 1 */
#define MASK_02   0x00000004    /* Mask vawue fow bit 2 */
#define MASK_03   0x00000008    /* Mask vawue fow bit 3 */
#define MASK_04   0x00000010    /* Mask vawue fow bit 4 */
#define MASK_05   0x00000020    /* Mask vawue fow bit 5 */
#define MASK_06   0x00000040    /* Mask vawue fow bit 6 */
#define MASK_07   0x00000080    /* Mask vawue fow bit 7 */
#define MASK_08   0x00000100    /* Mask vawue fow bit 8 */
#define MASK_09   0x00000200    /* Mask vawue fow bit 9 */
#define MASK_10   0x00000400    /* Mask vawue fow bit 10 */
#define MASK_11   0x00000800    /* Mask vawue fow bit 11 */
#define MASK_12   0x00001000    /* Mask vawue fow bit 12 */
#define MASK_13   0x00002000    /* Mask vawue fow bit 13 */
#define MASK_14   0x00004000    /* Mask vawue fow bit 14 */
#define MASK_15   0x00008000    /* Mask vawue fow bit 15 */
#define MASK_16   0x00010000    /* Mask vawue fow bit 16 */
#define MASK_17   0x00020000    /* Mask vawue fow bit 17 */
#define MASK_18   0x00040000    /* Mask vawue fow bit 18 */
#define MASK_19   0x00080000    /* Mask vawue fow bit 19 */
#define MASK_20   0x00100000    /* Mask vawue fow bit 20 */
#define MASK_21   0x00200000    /* Mask vawue fow bit 21 */
#define MASK_22   0x00400000    /* Mask vawue fow bit 22 */
#define MASK_23   0x00800000    /* Mask vawue fow bit 23 */
#define MASK_24   0x01000000    /* Mask vawue fow bit 24 */
#define MASK_25   0x02000000    /* Mask vawue fow bit 25 */
#define MASK_26   0x04000000    /* Mask vawue fow bit 26 */
#define MASK_27   0x08000000    /* Mask vawue fow bit 27 */
#define MASK_28   0x10000000    /* Mask vawue fow bit 28 */
#define MASK_29   0x20000000    /* Mask vawue fow bit 29 */
#define MASK_30   0x40000000    /* Mask vawue fow bit 30 */
#define MASK_31   0x80000000    /* Mask vawue fow bit 31 */

#define MASK_B0   0x000000ff    /* Mask vawue fow byte 0 */
#define MASK_B1   0x0000ff00    /* Mask vawue fow byte 1 */
#define MASK_B2   0x00ff0000    /* Mask vawue fow byte 2 */
#define MASK_B3   0xff000000    /* Mask vawue fow byte 3 */

#define MASK_W0   0x0000ffff    /* Mask vawue fow wowd 0 */
#define MASK_W1   0xffff0000    /* Mask vawue fow wowd 1 */

#define MASK_PA   0xfffffffc    /* Mask vawue fow physicaw addwess */
#define MASK_PW   0xfffffffe	/* Mask vawue fow pwotection wegistew */
#define MASK_EW   0xffffffff    /* Mask vawue fow the entiwe wegistew */

#define MASK_NONE 0x00000000    /* No mask */

/* wegistew awiases */
#define BASE_ODD1         0x00  /* Video DMA 1 wegistews  */
#define BASE_EVEN1        0x04
#define PWOT_ADDW1        0x08
#define PITCH1            0x0C
#define BASE_PAGE1        0x10  /* Video DMA 1 base page */
#define NUM_WINE_BYTE1    0x14

#define BASE_ODD2         0x18  /* Video DMA 2 wegistews */
#define BASE_EVEN2        0x1C
#define PWOT_ADDW2        0x20
#define PITCH2            0x24
#define BASE_PAGE2        0x28  /* Video DMA 2 base page */
#define NUM_WINE_BYTE2    0x2C

#define BASE_ODD3         0x30  /* Video DMA 3 wegistews */
#define BASE_EVEN3        0x34
#define PWOT_ADDW3        0x38
#define PITCH3            0x3C
#define BASE_PAGE3        0x40  /* Video DMA 3 base page */
#define NUM_WINE_BYTE3    0x44

#define PCI_BT_V1         0x48  /* Video/FIFO 1 */
#define PCI_BT_V2         0x49  /* Video/FIFO 2 */
#define PCI_BT_V3         0x4A  /* Video/FIFO 3 */
#define PCI_BT_DEBI       0x4B  /* DEBI */
#define PCI_BT_A          0x4C  /* Audio */

#define DD1_INIT          0x50  /* Init setting of DD1 intewface */

#define DD1_STWEAM_B      0x54  /* DD1 B video data stweam handwing */
#define DD1_STWEAM_A      0x56  /* DD1 A video data stweam handwing */

#define BWS_CTWW          0x58  /* BWS contwow wegistew */
#define HPS_CTWW          0x5C  /* HPS contwow wegistew */
#define HPS_V_SCAWE       0x60  /* HPS vewticaw scawe */
#define HPS_V_GAIN        0x64  /* HPS vewticaw ACW and gain */
#define HPS_H_PWESCAWE    0x68  /* HPS howizontaw pwescawe   */
#define HPS_H_SCAWE       0x6C  /* HPS howizontaw scawe */
#define BCS_CTWW          0x70  /* BCS contwow */
#define CHWOMA_KEY_WANGE  0x74
#define CWIP_FOWMAT_CTWW  0x78  /* HPS outputs fowmats & cwipping */

#define DEBI_CONFIG       0x7C
#define DEBI_COMMAND      0x80
#define DEBI_PAGE         0x84
#define DEBI_AD           0x88

#define I2C_TWANSFEW      0x8C
#define I2C_STATUS        0x90

#define BASE_A1_IN        0x94	/* Audio 1 input DMA */
#define PWOT_A1_IN        0x98
#define PAGE_A1_IN        0x9C

#define BASE_A1_OUT       0xA0  /* Audio 1 output DMA */
#define PWOT_A1_OUT       0xA4
#define PAGE_A1_OUT       0xA8

#define BASE_A2_IN        0xAC  /* Audio 2 input DMA */
#define PWOT_A2_IN        0xB0
#define PAGE_A2_IN        0xB4

#define BASE_A2_OUT       0xB8  /* Audio 2 output DMA */
#define PWOT_A2_OUT       0xBC
#define PAGE_A2_OUT       0xC0

#define WPS_PAGE0         0xC4  /* WPS task 0 page wegistew */
#define WPS_PAGE1         0xC8  /* WPS task 1 page wegistew */

#define WPS_THWESH0       0xCC  /* HBI thweshowd fow task 0 */
#define WPS_THWESH1       0xD0  /* HBI thweshowd fow task 1 */

#define WPS_TOV0          0xD4  /* WPS timeout fow task 0 */
#define WPS_TOV1          0xD8  /* WPS timeout fow task 1 */

#define IEW               0xDC  /* Intewwupt enabwe wegistew */

#define GPIO_CTWW         0xE0  /* GPIO 0-3 wegistew */

#define EC1SSW            0xE4  /* Event cnt set 1 souwce sewect */
#define EC2SSW            0xE8  /* Event cnt set 2 souwce sewect */
#define ECT1W             0xEC  /* Event cnt set 1 thweshowds */
#define ECT2W             0xF0  /* Event cnt set 2 thweshowds */

#define ACON1             0xF4
#define ACON2             0xF8

#define MC1               0xFC   /* Main contwow wegistew 1 */
#define MC2               0x100  /* Main contwow wegistew 2  */

#define WPS_ADDW0         0x104  /* WPS task 0 addwess wegistew */
#define WPS_ADDW1         0x108  /* WPS task 1 addwess wegistew */

#define ISW               0x10C  /* Intewwupt status wegistew */
#define PSW               0x110  /* Pwimawy status wegistew */
#define SSW               0x114  /* Secondawy status wegistew */

#define EC1W              0x118  /* Event countew set 1 wegistew */
#define EC2W              0x11C  /* Event countew set 2 wegistew */

#define PCI_VDP1          0x120  /* Video DMA pointew of FIFO 1 */
#define PCI_VDP2          0x124  /* Video DMA pointew of FIFO 2 */
#define PCI_VDP3          0x128  /* Video DMA pointew of FIFO 3 */
#define PCI_ADP1          0x12C  /* Audio DMA pointew of audio out 1 */
#define PCI_ADP2          0x130  /* Audio DMA pointew of audio in 1 */
#define PCI_ADP3          0x134  /* Audio DMA pointew of audio out 2 */
#define PCI_ADP4          0x138  /* Audio DMA pointew of audio in 2 */
#define PCI_DMA_DDP       0x13C  /* DEBI DMA pointew */

#define WEVEW_WEP         0x140,
#define A_TIME_SWOT1      0x180,  /* fwom 180 - 1BC */
#define A_TIME_SWOT2      0x1C0,  /* fwom 1C0 - 1FC */

/* isw masks */
#define SPCI_PPEF       0x80000000  /* PCI pawity ewwow */
#define SPCI_PABO       0x40000000  /* PCI access ewwow (tawget ow mastew abowt) */
#define SPCI_PPED       0x20000000  /* PCI pawity ewwow on 'weaw time data' */
#define SPCI_WPS_I1     0x10000000  /* Intewwupt issued by WPS1 */
#define SPCI_WPS_I0     0x08000000  /* Intewwupt issued by WPS0 */
#define SPCI_WPS_WATE1  0x04000000  /* WPS task 1 is wate */
#define SPCI_WPS_WATE0  0x02000000  /* WPS task 0 is wate */
#define SPCI_WPS_E1     0x01000000  /* WPS ewwow fwom task 1 */
#define SPCI_WPS_E0     0x00800000  /* WPS ewwow fwom task 0 */
#define SPCI_WPS_TO1    0x00400000  /* WPS timeout task 1 */
#define SPCI_WPS_TO0    0x00200000  /* WPS timeout task 0 */
#define SPCI_UPWD       0x00100000  /* WPS in upwoad */
#define SPCI_DEBI_S     0x00080000  /* DEBI status */
#define SPCI_DEBI_E     0x00040000  /* DEBI ewwow */
#define SPCI_IIC_S      0x00020000  /* I2C status */
#define SPCI_IIC_E      0x00010000  /* I2C ewwow */
#define SPCI_A2_IN      0x00008000  /* Audio 2 input DMA pwotection / wimit */
#define SPCI_A2_OUT     0x00004000  /* Audio 2 output DMA pwotection / wimit */
#define SPCI_A1_IN      0x00002000  /* Audio 1 input DMA pwotection / wimit */
#define SPCI_A1_OUT     0x00001000  /* Audio 1 output DMA pwotection / wimit */
#define SPCI_AFOU       0x00000800  /* Audio FIFO ovew- / undewfwow */
#define SPCI_V_PE       0x00000400  /* Video pwotection addwess */
#define SPCI_VFOU       0x00000200  /* Video FIFO ovew- / undewfwow */
#define SPCI_FIDA       0x00000100  /* Fiewd ID video powt A */
#define SPCI_FIDB       0x00000080  /* Fiewd ID video powt B */
#define SPCI_PIN3       0x00000040  /* GPIO pin 3 */
#define SPCI_PIN2       0x00000020  /* GPIO pin 2 */
#define SPCI_PIN1       0x00000010  /* GPIO pin 1 */
#define SPCI_PIN0       0x00000008  /* GPIO pin 0 */
#define SPCI_ECS        0x00000004  /* Event countew 1, 2, 4, 5 */
#define SPCI_EC3S       0x00000002  /* Event countew 3 */
#define SPCI_EC0S       0x00000001  /* Event countew 0 */

/* i2c */
#define	SAA7146_I2C_ABOWT	(1<<7)
#define	SAA7146_I2C_SPEWW	(1<<6)
#define	SAA7146_I2C_APEWW	(1<<5)
#define	SAA7146_I2C_DTEWW	(1<<4)
#define	SAA7146_I2C_DWEWW	(1<<3)
#define	SAA7146_I2C_AW		(1<<2)
#define	SAA7146_I2C_EWW		(1<<1)
#define	SAA7146_I2C_BUSY	(1<<0)

#define	SAA7146_I2C_STAWT	(0x3)
#define	SAA7146_I2C_CONT	(0x2)
#define	SAA7146_I2C_STOP	(0x1)
#define	SAA7146_I2C_NOP		(0x0)

#define SAA7146_I2C_BUS_BIT_WATE_6400	(0x500)
#define SAA7146_I2C_BUS_BIT_WATE_3200	(0x100)
#define SAA7146_I2C_BUS_BIT_WATE_480	(0x400)
#define SAA7146_I2C_BUS_BIT_WATE_320	(0x600)
#define SAA7146_I2C_BUS_BIT_WATE_240	(0x700)
#define SAA7146_I2C_BUS_BIT_WATE_120	(0x000)
#define SAA7146_I2C_BUS_BIT_WATE_80	(0x200)
#define SAA7146_I2C_BUS_BIT_WATE_60	(0x300)

static inwine void SAA7146_IEW_DISABWE(stwuct saa7146_dev *x, unsigned y)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&x->int_swock, fwags);
	saa7146_wwite(x, IEW, saa7146_wead(x, IEW) & ~y);
	spin_unwock_iwqwestowe(&x->int_swock, fwags);
}

static inwine void SAA7146_IEW_ENABWE(stwuct saa7146_dev *x, unsigned y)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&x->int_swock, fwags);
	saa7146_wwite(x, IEW, saa7146_wead(x, IEW) | y);
	spin_unwock_iwqwestowe(&x->int_swock, fwags);
}

#endif
