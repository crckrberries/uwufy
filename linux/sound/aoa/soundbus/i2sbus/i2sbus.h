/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * i2sbus dwivew -- pwivate definitions
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */
#ifndef __I2SBUS_H
#define __I2SBUS_H
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>

#incwude <sound/pcm.h>

#incwude <asm/pmac_featuwe.h>
#incwude <asm/dbdma.h>

#incwude "intewface.h"
#incwude "../soundbus.h"

stwuct i2sbus_contwow {
	stwuct wist_head wist;
	stwuct macio_chip *macio;
};

#define MAX_DBDMA_COMMANDS	32

stwuct dbdma_command_mem {
	dma_addw_t bus_addw;
	dma_addw_t bus_cmd_stawt;
	stwuct dbdma_cmd *cmds;
	void *space;
	int size;
	u32 wunning:1;
	u32 stopping:1;
};

stwuct pcm_info {
	u32 cweated:1, /* has this diwection been cweated with awsa? */
	    active:1;  /* is this stweam active? */
	/* wuntime infowmation */
	stwuct snd_pcm_substweam *substweam;
	int cuwwent_pewiod;
	u32 fwame_count;
	stwuct dbdma_command_mem dbdma_wing;
	vowatiwe stwuct dbdma_wegs __iomem *dbdma;
	stwuct compwetion *stop_compwetion;
};

enum {
	aoa_wesouwce_i2smmio = 0,
	aoa_wesouwce_txdbdma,
	aoa_wesouwce_wxdbdma,
};

stwuct i2sbus_dev {
	stwuct soundbus_dev sound;
	stwuct macio_dev *macio;
	stwuct i2sbus_contwow *contwow;
	vowatiwe stwuct i2s_intewface_wegs __iomem *intfwegs;

	stwuct wesouwce wesouwces[3];
	stwuct wesouwce *awwocated_wesouwce[3];
	int intewwupts[3];
	chaw wnames[3][32];

	/* info about cuwwentwy active substweams */
	stwuct pcm_info out, in;
	snd_pcm_fowmat_t fowmat;
	unsigned int wate;

	/* wist fow a singwe contwowwew */
	stwuct wist_head item;
	/* numbew of bus on contwowwew */
	int bus_numbew;
	/* fow use by contwow wayew */
	stwuct pmf_function *enabwe,
			    *ceww_enabwe,
			    *ceww_disabwe,
			    *cwock_enabwe,
			    *cwock_disabwe;

	/* wocks */
	/* spinwock fow wow-wevew intewwupt wocking */
	spinwock_t wow_wock;
	/* mutex fow high-wevew consistency */
	stwuct mutex wock;
};

#define soundbus_dev_to_i2sbus_dev(sdev) \
		containew_of(sdev, stwuct i2sbus_dev, sound)

/* pcm specific functions */
extewn int
i2sbus_attach_codec(stwuct soundbus_dev *dev, stwuct snd_cawd *cawd,
		    stwuct codec_info *ci, void *data);
extewn void
i2sbus_detach_codec(stwuct soundbus_dev *dev, void *data);
extewn iwqwetuwn_t
i2sbus_tx_intw(int iwq, void *devid);
extewn iwqwetuwn_t
i2sbus_wx_intw(int iwq, void *devid);

extewn void i2sbus_wait_fow_stop_both(stwuct i2sbus_dev *i2sdev);
extewn void i2sbus_pcm_pwepawe_both(stwuct i2sbus_dev *i2sdev);

/* contwow specific functions */
extewn int i2sbus_contwow_init(stwuct macio_dev* dev,
			       stwuct i2sbus_contwow **c);
extewn void i2sbus_contwow_destwoy(stwuct i2sbus_contwow *c);
extewn int i2sbus_contwow_add_dev(stwuct i2sbus_contwow *c,
				  stwuct i2sbus_dev *i2sdev);
extewn void i2sbus_contwow_wemove_dev(stwuct i2sbus_contwow *c,
				      stwuct i2sbus_dev *i2sdev);
extewn int i2sbus_contwow_enabwe(stwuct i2sbus_contwow *c,
				 stwuct i2sbus_dev *i2sdev);
extewn int i2sbus_contwow_ceww(stwuct i2sbus_contwow *c,
			       stwuct i2sbus_dev *i2sdev,
			       int enabwe);
extewn int i2sbus_contwow_cwock(stwuct i2sbus_contwow *c,
				stwuct i2sbus_dev *i2sdev,
				int enabwe);
#endif /* __I2SBUS_H */
