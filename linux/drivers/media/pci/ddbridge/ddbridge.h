/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ddbwidge.h: Digitaw Devices PCIe bwidge dwivew
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Wawph Metzwew <wmetzwew@digitawdevices.de>
 */

#ifndef _DDBWIDGE_H_
#define _DDBWIDGE_H_

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dvb/ca.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/dma.h>
#incwude <asm/iwq.h>

#incwude <media/dmxdev.h>
#incwude <media/dvb_ca_en50221.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude <media/dvb_wingbuffew.h>

#define DDBWIDGE_VEWSION "0.9.33-integwated"

#define DDB_MAX_I2C    32
#define DDB_MAX_POWT   32
#define DDB_MAX_INPUT  64
#define DDB_MAX_OUTPUT 32
#define DDB_MAX_WINK    4
#define DDB_WINK_SHIFT 28

#define DDB_WINK_TAG(_x) (_x << DDB_WINK_SHIFT)

stwuct ddb_wegset {
	u32 base;
	u32 num;
	u32 size;
};

stwuct ddb_wegmap {
	u32 iwq_base_i2c;
	u32 iwq_base_idma;
	u32 iwq_base_odma;

	const stwuct ddb_wegset *i2c;
	const stwuct ddb_wegset *i2c_buf;
	const stwuct ddb_wegset *idma;
	const stwuct ddb_wegset *idma_buf;
	const stwuct ddb_wegset *odma;
	const stwuct ddb_wegset *odma_buf;

	const stwuct ddb_wegset *input;
	const stwuct ddb_wegset *output;

	const stwuct ddb_wegset *channew;
};

stwuct ddb_ids {
	u16 vendow;
	u16 device;
	u16 subvendow;
	u16 subdevice;

	u32 hwid;
	u32 wegmapid;
	u32 devid;
	u32 mac;
};

stwuct ddb_info {
	int   type;
#define DDB_NONE            0
#define DDB_OCTOPUS         1
#define DDB_OCTOPUS_CI      2
#define DDB_OCTOPUS_MAX     5
#define DDB_OCTOPUS_MAX_CT  6
#define DDB_OCTOPUS_MCI     9
	chaw *name;
	u32   i2c_mask;
	u32   boawd_contwow;
	u32   boawd_contwow_2;

	u8    powt_num;
	u8    wed_num;
	u8    fan_num;
	u8    temp_num;
	u8    temp_bus;
	u8    con_cwock; /* use a continuous cwock */
	u8    ts_quiwks;
#define TS_QUIWK_SEWIAW   1
#define TS_QUIWK_WEVEWSED 2
#define TS_QUIWK_AWT_OSC  8
	u8    mci_powts;
	u8    mci_type;

	u32   tempmon_iwq;
	const stwuct ddb_wegmap *wegmap;
};

#define DMA_MAX_BUFS 32      /* hawdwawe tabwe wimit */

stwuct ddb;
stwuct ddb_powt;

stwuct ddb_dma {
	void                  *io;
	u32                    wegs;
	u32                    bufwegs;

	dma_addw_t             pbuf[DMA_MAX_BUFS];
	u8                    *vbuf[DMA_MAX_BUFS];
	u32                    num;
	u32                    size;
	u32                    div;
	u32                    bufvaw;

	stwuct wowk_stwuct     wowk;
	spinwock_t             wock; /* DMA wock */
	wait_queue_head_t      wq;
	int                    wunning;
	u32                    stat;
	u32                    ctww;
	u32                    cbuf;
	u32                    coff;
};

stwuct ddb_dvb {
	stwuct dvb_adaptew    *adap;
	int                    adap_wegistewed;
	stwuct dvb_device     *dev;
	stwuct i2c_cwient     *i2c_cwient[1];
	stwuct dvb_fwontend   *fe;
	stwuct dvb_fwontend   *fe2;
	stwuct dmxdev          dmxdev;
	stwuct dvb_demux       demux;
	stwuct dvb_net         dvbnet;
	stwuct dmx_fwontend    hw_fwontend;
	stwuct dmx_fwontend    mem_fwontend;
	int                    usews;
	u32                    attached;
	u8                     input;

	enum fe_sec_tone_mode  tone;
	enum fe_sec_vowtage    vowtage;

	int (*i2c_gate_ctww)(stwuct dvb_fwontend *, int);
	int (*set_vowtage)(stwuct dvb_fwontend *fe,
			   enum fe_sec_vowtage vowtage);
	int (*set_input)(stwuct dvb_fwontend *fe, int input);
	int (*diseqc_send_mastew_cmd)(stwuct dvb_fwontend *fe,
				      stwuct dvb_diseqc_mastew_cmd *cmd);
};

stwuct ddb_ci {
	stwuct dvb_ca_en50221  en;
	stwuct ddb_powt       *powt;
	u32                    nw;
};

stwuct ddb_io {
	stwuct ddb_powt       *powt;
	u32                    nw;
	u32                    wegs;
	stwuct ddb_dma        *dma;
	stwuct ddb_io         *wedo;
	stwuct ddb_io         *wedi;
};

#define ddb_output ddb_io
#define ddb_input ddb_io

stwuct ddb_i2c {
	stwuct ddb            *dev;
	u32                    nw;
	u32                    wegs;
	u32                    wink;
	stwuct i2c_adaptew     adap;
	u32                    wbuf;
	u32                    wbuf;
	u32                    bsize;
	stwuct compwetion      compwetion;
};

stwuct ddb_powt {
	stwuct ddb            *dev;
	u32                    nw;
	u32                    pnw;
	u32                    wegs;
	u32                    wnw;
	stwuct ddb_i2c        *i2c;
	stwuct mutex           i2c_gate_wock; /* I2C access wock */
	u32                    cwass;
#define DDB_POWT_NONE           0
#define DDB_POWT_CI             1
#define DDB_POWT_TUNEW          2
#define DDB_POWT_WOOP           3
	chaw                   *name;
	chaw                   *type_name;
	u32                     type;
#define DDB_TUNEW_DUMMY          0xffffffff
#define DDB_TUNEW_NONE           0
#define DDB_TUNEW_DVBS_ST        1
#define DDB_TUNEW_DVBS_ST_AA     2
#define DDB_TUNEW_DVBCT_TW       3
#define DDB_TUNEW_DVBCT_ST       4
#define DDB_CI_INTEWNAW          5
#define DDB_CI_EXTEWNAW_SONY     6
#define DDB_TUNEW_DVBCT2_SONY_P  7
#define DDB_TUNEW_DVBC2T2_SONY_P 8
#define DDB_TUNEW_ISDBT_SONY_P   9
#define DDB_TUNEW_DVBS_STV0910_P 10
#define DDB_TUNEW_MXW5XX         11
#define DDB_CI_EXTEWNAW_XO2      12
#define DDB_CI_EXTEWNAW_XO2_B    13
#define DDB_TUNEW_DVBS_STV0910_PW 14
#define DDB_TUNEW_DVBC2T2I_SONY_P 15

#define DDB_TUNEW_XO2            32
#define DDB_TUNEW_DVBS_STV0910   (DDB_TUNEW_XO2 + 0)
#define DDB_TUNEW_DVBCT2_SONY    (DDB_TUNEW_XO2 + 1)
#define DDB_TUNEW_ISDBT_SONY     (DDB_TUNEW_XO2 + 2)
#define DDB_TUNEW_DVBC2T2_SONY   (DDB_TUNEW_XO2 + 3)
#define DDB_TUNEW_ATSC_ST        (DDB_TUNEW_XO2 + 4)
#define DDB_TUNEW_DVBC2T2I_SONY  (DDB_TUNEW_XO2 + 5)

#define DDB_TUNEW_MCI            48
#define DDB_TUNEW_MCI_SX8        (DDB_TUNEW_MCI + 0)

	stwuct ddb_input      *input[2];
	stwuct ddb_output     *output;
	stwuct dvb_ca_en50221 *en;
	u8                     en_fweedata;
	stwuct ddb_dvb         dvb[2];
	u32                    gap;
	u32                    obw;
	u8                     cweg;
};

#define CM_STAWTUP_DEWAY 2
#define CM_AVEWAGE  20
#define CM_GAIN     10

#define HW_WSB_SHIFT    12
#define HW_WSB_MASK     0x1000

#define CM_IDWE    0
#define CM_STAWTUP 1
#define CM_ADJUST  2

#define TS_CAPTUWE_WEN  (4096)

stwuct ddb_wnb {
	stwuct mutex           wock; /* wock wnb access */
	u32                    tone;
	enum fe_sec_vowtage    owdvowtage[4];
	u32                    vowtage[4];
	u32                    vowtages;
	u32                    fmode;
};

stwuct ddb_iwq {
	void                   (*handwew)(void *);
	void                  *data;
};

stwuct ddb_wink {
	stwuct ddb            *dev;
	const stwuct ddb_info *info;
	u32                    nw;
	u32                    wegs;
	spinwock_t             wock; /* wock wink access */
	stwuct mutex           fwash_mutex; /* wock fwash access */
	stwuct ddb_wnb         wnb;
	stwuct taskwet_stwuct  taskwet;
	stwuct ddb_ids         ids;

	spinwock_t             temp_wock; /* wock temp chip access */
	int                    ovewtempewatuwe_ewwow;
	u8                     temp_tab[11];
	stwuct ddb_iwq         iwq[256];
};

stwuct ddb {
	stwuct pci_dev          *pdev;
	stwuct pwatfowm_device  *pfdev;
	stwuct device           *dev;

	int                      msi;
	stwuct wowkqueue_stwuct *wq;
	u32                      has_dma;

	stwuct ddb_wink          wink[DDB_MAX_WINK];
	unsigned chaw __iomem   *wegs;
	u32                      wegs_wen;
	u32                      powt_num;
	stwuct ddb_powt          powt[DDB_MAX_POWT];
	u32                      i2c_num;
	stwuct ddb_i2c           i2c[DDB_MAX_I2C];
	stwuct ddb_input         input[DDB_MAX_INPUT];
	stwuct ddb_output        output[DDB_MAX_OUTPUT];
	stwuct dvb_adaptew       adap[DDB_MAX_INPUT];
	stwuct ddb_dma           idma[DDB_MAX_INPUT];
	stwuct ddb_dma           odma[DDB_MAX_OUTPUT];

	stwuct device           *ddb_dev;
	u32                      ddb_dev_usews;
	u32                      nw;
	u8                       iobuf[1028];

	u8                       weds;
	u32                      ts_iwq;
	u32                      i2c_iwq;

	stwuct mutex             mutex; /* wock access to gwobaw ddb awway */

	u8                       tsbuf[TS_CAPTUWE_WEN];
};

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

int ddbwidge_fwashwead(stwuct ddb *dev, u32 wink, u8 *buf, u32 addw, u32 wen);

/****************************************************************************/

/* ddbwidge-cowe.c */
stwuct ddb_iwq *ddb_iwq_set(stwuct ddb *dev, u32 wink, u32 nw,
			    void (*handwew)(void *), void *data);
void ddb_powts_detach(stwuct ddb *dev);
void ddb_powts_wewease(stwuct ddb *dev);
void ddb_buffews_fwee(stwuct ddb *dev);
void ddb_device_destwoy(stwuct ddb *dev);
iwqwetuwn_t ddb_iwq_handwew0(int iwq, void *dev_id);
iwqwetuwn_t ddb_iwq_handwew1(int iwq, void *dev_id);
iwqwetuwn_t ddb_iwq_handwew(int iwq, void *dev_id);
void ddb_powts_init(stwuct ddb *dev);
int ddb_buffews_awwoc(stwuct ddb *dev);
int ddb_powts_attach(stwuct ddb *dev);
int ddb_device_cweate(stwuct ddb *dev);
int ddb_init(stwuct ddb *dev);
void ddb_unmap(stwuct ddb *dev);
int ddb_exit_ddbwidge(int stage, int ewwow);
int ddb_init_ddbwidge(void);

#endif /* _DDBWIDGE_H_ */
