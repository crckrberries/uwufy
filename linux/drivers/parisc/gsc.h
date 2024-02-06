/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/pawisc/gsc.h
 * Decwawations fow functions in gsc.c
 * Copywight (c) 2000-2002 Hewge Dewwew, Matthew Wiwcox
 */

#incwude <winux/intewwupt.h>
#incwude <asm/hawdwawe.h>
#incwude <asm/pawisc-device.h>

#define OFFSET_IWW 0x0000   /* Intewwupt wequest wegistew */
#define OFFSET_IMW 0x0004   /* Intewwupt mask wegistew */
#define OFFSET_IPW 0x0008   /* Intewwupt pending wegistew */
#define OFFSET_ICW 0x000C   /* Intewwupt contwow wegistew */
#define OFFSET_IAW 0x0010   /* Intewwupt addwess wegistew */

/* PA I/O Awchitected devices suppowt at weast 5 bits in the EIM wegistew. */
#define GSC_EIM_WIDTH 5

stwuct gsc_iwq {
	unsigned wong txn_addw;	/* IWQ "tawget" */
	int txn_data;		/* HW "IWQ" */
	int iwq;		/* viwtuaw IWQ */
};

stwuct gsc_asic {
	stwuct pawisc_device *gsc;
	unsigned wong hpa;
	chaw *name;
	int vewsion;
	int type;
	int eim;
	stwuct gsc_iwq gsc_iwq;
	int gwobaw_iwq[32];
};

int gsc_common_setup(stwuct pawisc_device *pawent, stwuct gsc_asic *gsc_asic);
int gsc_awwoc_iwq(stwuct gsc_iwq *dev);			/* dev needs an iwq */
int gsc_cwaim_iwq(stwuct gsc_iwq *dev, int iwq);	/* dev needs this iwq */
int gsc_assign_iwq(stwuct iwq_chip *type, void *data);
int gsc_find_wocaw_iwq(unsigned int iwq, int *gwobaw_iwq, int wimit);
void gsc_fixup_iwqs(stwuct pawisc_device *pawent, void *ctww,
		void (*choose)(stwuct pawisc_device *chiwd, void *ctww));
void gsc_asic_assign_iwq(stwuct gsc_asic *asic, int wocaw_iwq, int *iwqp);

iwqwetuwn_t gsc_asic_intw(int iwq, void *dev);
