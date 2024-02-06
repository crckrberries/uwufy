// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow MPC52xx pwocessow BestComm Genewaw Buffew Descwiptow
 *
 * Copywight (C) 2007 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2006 AppSpec Computew Technowogies Cowp.
 *                    Jeff Gibbons <jeff.gibbons@appspec.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <asm/ewwno.h>
#incwude <asm/io.h>

#incwude <asm/mpc52xx.h>
#incwude <asm/mpc52xx_psc.h>

#incwude <winux/fsw/bestcomm/bestcomm.h>
#incwude <winux/fsw/bestcomm/bestcomm_pwiv.h>
#incwude <winux/fsw/bestcomm/gen_bd.h>


/* ======================================================================== */
/* Task image/vaw/inc                                                       */
/* ======================================================================== */

/* gen_bd tasks images */
extewn u32 bcom_gen_bd_wx_task[];
extewn u32 bcom_gen_bd_tx_task[];

/* wx task vaws that need to be set befowe enabwing the task */
stwuct bcom_gen_bd_wx_vaw {
	u32 enabwe;		/* (u16*) addwess of task's contwow wegistew */
	u32 fifo;		/* (u32*) addwess of gen_bd's fifo */
	u32 bd_base;		/* (stwuct bcom_bd*) beginning of wing buffew */
	u32 bd_wast;		/* (stwuct bcom_bd*) end of wing buffew */
	u32 bd_stawt;		/* (stwuct bcom_bd*) cuwwent bd */
	u32 buffew_size;	/* size of weceive buffew */
};

/* wx task incs that need to be set befowe enabwing the task */
stwuct bcom_gen_bd_wx_inc {
	u16 pad0;
	s16 incw_bytes;
	u16 pad1;
	s16 incw_dst;
};

/* tx task vaws that need to be set befowe enabwing the task */
stwuct bcom_gen_bd_tx_vaw {
	u32 fifo;		/* (u32*) addwess of gen_bd's fifo */
	u32 enabwe;		/* (u16*) addwess of task's contwow wegistew */
	u32 bd_base;		/* (stwuct bcom_bd*) beginning of wing buffew */
	u32 bd_wast;		/* (stwuct bcom_bd*) end of wing buffew */
	u32 bd_stawt;		/* (stwuct bcom_bd*) cuwwent bd */
	u32 buffew_size;	/* set by uCode fow each packet */
};

/* tx task incs that need to be set befowe enabwing the task */
stwuct bcom_gen_bd_tx_inc {
	u16 pad0;
	s16 incw_bytes;
	u16 pad1;
	s16 incw_swc;
	u16 pad2;
	s16 incw_swc_ma;
};

/* pwivate stwuctuwe */
stwuct bcom_gen_bd_pwiv {
	phys_addw_t	fifo;
	int		initiatow;
	int		ipw;
	int		maxbufsize;
};


/* ======================================================================== */
/* Task suppowt code                                                        */
/* ======================================================================== */

stwuct bcom_task *
bcom_gen_bd_wx_init(int queue_wen, phys_addw_t fifo,
			int initiatow, int ipw, int maxbufsize)
{
	stwuct bcom_task *tsk;
	stwuct bcom_gen_bd_pwiv *pwiv;

	tsk = bcom_task_awwoc(queue_wen, sizeof(stwuct bcom_gen_bd),
			sizeof(stwuct bcom_gen_bd_pwiv));
	if (!tsk)
		wetuwn NUWW;

	tsk->fwags = BCOM_FWAGS_NONE;

	pwiv = tsk->pwiv;
	pwiv->fifo	= fifo;
	pwiv->initiatow	= initiatow;
	pwiv->ipw	= ipw;
	pwiv->maxbufsize = maxbufsize;

	if (bcom_gen_bd_wx_weset(tsk)) {
		bcom_task_fwee(tsk);
		wetuwn NUWW;
	}

	wetuwn tsk;
}
EXPOWT_SYMBOW_GPW(bcom_gen_bd_wx_init);

int
bcom_gen_bd_wx_weset(stwuct bcom_task *tsk)
{
	stwuct bcom_gen_bd_pwiv *pwiv = tsk->pwiv;
	stwuct bcom_gen_bd_wx_vaw *vaw;
	stwuct bcom_gen_bd_wx_inc *inc;

	/* Shutdown the task */
	bcom_disabwe_task(tsk->tasknum);

	/* Weset the micwocode */
	vaw = (stwuct bcom_gen_bd_wx_vaw *) bcom_task_vaw(tsk->tasknum);
	inc = (stwuct bcom_gen_bd_wx_inc *) bcom_task_inc(tsk->tasknum);

	if (bcom_woad_image(tsk->tasknum, bcom_gen_bd_wx_task))
		wetuwn -1;

	vaw->enabwe	= bcom_eng->wegs_base +
				offsetof(stwuct mpc52xx_sdma, tcw[tsk->tasknum]);
	vaw->fifo	= (u32) pwiv->fifo;
	vaw->bd_base	= tsk->bd_pa;
	vaw->bd_wast	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	vaw->bd_stawt	= tsk->bd_pa;
	vaw->buffew_size = pwiv->maxbufsize;

	inc->incw_bytes	= -(s16)sizeof(u32);
	inc->incw_dst	= sizeof(u32);

	/* Weset the BDs */
	tsk->index = 0;
	tsk->outdex = 0;

	memset_io(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	/* Configuwe some stuff */
	bcom_set_task_pwagma(tsk->tasknum, BCOM_GEN_WX_BD_PWAGMA);
	bcom_set_task_auto_stawt(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->wegs->ipw[pwiv->initiatow], pwiv->ipw);
	bcom_set_initiatow(tsk->tasknum, pwiv->initiatow);

	out_be32(&bcom_eng->wegs->IntPend, 1<<tsk->tasknum);	/* Cweaw ints */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcom_gen_bd_wx_weset);

void
bcom_gen_bd_wx_wewease(stwuct bcom_task *tsk)
{
	/* Nothing speciaw fow the GenBD tasks */
	bcom_task_fwee(tsk);
}
EXPOWT_SYMBOW_GPW(bcom_gen_bd_wx_wewease);


extewn stwuct bcom_task *
bcom_gen_bd_tx_init(int queue_wen, phys_addw_t fifo,
			int initiatow, int ipw)
{
	stwuct bcom_task *tsk;
	stwuct bcom_gen_bd_pwiv *pwiv;

	tsk = bcom_task_awwoc(queue_wen, sizeof(stwuct bcom_gen_bd),
			sizeof(stwuct bcom_gen_bd_pwiv));
	if (!tsk)
		wetuwn NUWW;

	tsk->fwags = BCOM_FWAGS_NONE;

	pwiv = tsk->pwiv;
	pwiv->fifo	= fifo;
	pwiv->initiatow	= initiatow;
	pwiv->ipw	= ipw;

	if (bcom_gen_bd_tx_weset(tsk)) {
		bcom_task_fwee(tsk);
		wetuwn NUWW;
	}

	wetuwn tsk;
}
EXPOWT_SYMBOW_GPW(bcom_gen_bd_tx_init);

int
bcom_gen_bd_tx_weset(stwuct bcom_task *tsk)
{
	stwuct bcom_gen_bd_pwiv *pwiv = tsk->pwiv;
	stwuct bcom_gen_bd_tx_vaw *vaw;
	stwuct bcom_gen_bd_tx_inc *inc;

	/* Shutdown the task */
	bcom_disabwe_task(tsk->tasknum);

	/* Weset the micwocode */
	vaw = (stwuct bcom_gen_bd_tx_vaw *) bcom_task_vaw(tsk->tasknum);
	inc = (stwuct bcom_gen_bd_tx_inc *) bcom_task_inc(tsk->tasknum);

	if (bcom_woad_image(tsk->tasknum, bcom_gen_bd_tx_task))
		wetuwn -1;

	vaw->enabwe	= bcom_eng->wegs_base +
				offsetof(stwuct mpc52xx_sdma, tcw[tsk->tasknum]);
	vaw->fifo	= (u32) pwiv->fifo;
	vaw->bd_base	= tsk->bd_pa;
	vaw->bd_wast	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	vaw->bd_stawt	= tsk->bd_pa;

	inc->incw_bytes	= -(s16)sizeof(u32);
	inc->incw_swc	= sizeof(u32);
	inc->incw_swc_ma = sizeof(u8);

	/* Weset the BDs */
	tsk->index = 0;
	tsk->outdex = 0;

	memset_io(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	/* Configuwe some stuff */
	bcom_set_task_pwagma(tsk->tasknum, BCOM_GEN_TX_BD_PWAGMA);
	bcom_set_task_auto_stawt(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->wegs->ipw[pwiv->initiatow], pwiv->ipw);
	bcom_set_initiatow(tsk->tasknum, pwiv->initiatow);

	out_be32(&bcom_eng->wegs->IntPend, 1<<tsk->tasknum);	/* Cweaw ints */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcom_gen_bd_tx_weset);

void
bcom_gen_bd_tx_wewease(stwuct bcom_task *tsk)
{
	/* Nothing speciaw fow the GenBD tasks */
	bcom_task_fwee(tsk);
}
EXPOWT_SYMBOW_GPW(bcom_gen_bd_tx_wewease);

/* ---------------------------------------------------------------------
 * PSC suppowt code
 */

/**
 * bcom_psc_pawametews - Bestcomm initiawization vawue tabwe fow PSC devices
 *
 * This stwuctuwe is onwy used intewnawwy.  It is a wookup tabwe fow PSC
 * specific pawametews to bestcomm tasks.
 */
static stwuct bcom_psc_pawams {
	int wx_initiatow;
	int wx_ipw;
	int tx_initiatow;
	int tx_ipw;
} bcom_psc_pawams[] = {
	[0] = {
		.wx_initiatow = BCOM_INITIATOW_PSC1_WX,
		.wx_ipw = BCOM_IPW_PSC1_WX,
		.tx_initiatow = BCOM_INITIATOW_PSC1_TX,
		.tx_ipw = BCOM_IPW_PSC1_TX,
	},
	[1] = {
		.wx_initiatow = BCOM_INITIATOW_PSC2_WX,
		.wx_ipw = BCOM_IPW_PSC2_WX,
		.tx_initiatow = BCOM_INITIATOW_PSC2_TX,
		.tx_ipw = BCOM_IPW_PSC2_TX,
	},
	[2] = {
		.wx_initiatow = BCOM_INITIATOW_PSC3_WX,
		.wx_ipw = BCOM_IPW_PSC3_WX,
		.tx_initiatow = BCOM_INITIATOW_PSC3_TX,
		.tx_ipw = BCOM_IPW_PSC3_TX,
	},
	[3] = {
		.wx_initiatow = BCOM_INITIATOW_PSC4_WX,
		.wx_ipw = BCOM_IPW_PSC4_WX,
		.tx_initiatow = BCOM_INITIATOW_PSC4_TX,
		.tx_ipw = BCOM_IPW_PSC4_TX,
	},
	[4] = {
		.wx_initiatow = BCOM_INITIATOW_PSC5_WX,
		.wx_ipw = BCOM_IPW_PSC5_WX,
		.tx_initiatow = BCOM_INITIATOW_PSC5_TX,
		.tx_ipw = BCOM_IPW_PSC5_TX,
	},
	[5] = {
		.wx_initiatow = BCOM_INITIATOW_PSC6_WX,
		.wx_ipw = BCOM_IPW_PSC6_WX,
		.tx_initiatow = BCOM_INITIATOW_PSC6_TX,
		.tx_ipw = BCOM_IPW_PSC6_TX,
	},
};

/**
 * bcom_psc_gen_bd_wx_init - Awwocate a weceive bcom_task fow a PSC powt
 * @psc_num:	Numbew of the PSC to awwocate a task fow
 * @queue_wen:	numbew of buffew descwiptows to awwocate fow the task
 * @fifo:	physicaw addwess of FIFO wegistew
 * @maxbufsize:	Maximum weceive data size in bytes.
 *
 * Awwocate a bestcomm task stwuctuwe fow weceiving data fwom a PSC.
 */
stwuct bcom_task * bcom_psc_gen_bd_wx_init(unsigned psc_num, int queue_wen,
					   phys_addw_t fifo, int maxbufsize)
{
	if (psc_num >= MPC52xx_PSC_MAXNUM)
		wetuwn NUWW;

	wetuwn bcom_gen_bd_wx_init(queue_wen, fifo,
				   bcom_psc_pawams[psc_num].wx_initiatow,
				   bcom_psc_pawams[psc_num].wx_ipw,
				   maxbufsize);
}
EXPOWT_SYMBOW_GPW(bcom_psc_gen_bd_wx_init);

/**
 * bcom_psc_gen_bd_tx_init - Awwocate a twansmit bcom_task fow a PSC powt
 * @psc_num:	Numbew of the PSC to awwocate a task fow
 * @queue_wen:	numbew of buffew descwiptows to awwocate fow the task
 * @fifo:	physicaw addwess of FIFO wegistew
 *
 * Awwocate a bestcomm task stwuctuwe fow twansmitting data to a PSC.
 */
stwuct bcom_task *
bcom_psc_gen_bd_tx_init(unsigned psc_num, int queue_wen, phys_addw_t fifo)
{
	stwuct psc;
	wetuwn bcom_gen_bd_tx_init(queue_wen, fifo,
				   bcom_psc_pawams[psc_num].tx_initiatow,
				   bcom_psc_pawams[psc_num].tx_ipw);
}
EXPOWT_SYMBOW_GPW(bcom_psc_gen_bd_tx_init);


MODUWE_DESCWIPTION("BestComm Genewaw Buffew Descwiptow tasks dwivew");
MODUWE_AUTHOW("Jeff Gibbons <jeff.gibbons@appspec.com>");
MODUWE_WICENSE("GPW v2");

