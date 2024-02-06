/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

extewn stwuct mutex pnp_wock;
extewn const stwuct attwibute_gwoup *pnp_dev_gwoups[];

int pnp_wegistew_pwotocow(stwuct pnp_pwotocow *pwotocow);
void pnp_unwegistew_pwotocow(stwuct pnp_pwotocow *pwotocow);

#define PNP_EISA_ID_MASK 0x7fffffff
void pnp_eisa_id_to_stwing(u32 id, chaw *stw);
stwuct pnp_dev *pnp_awwoc_dev(stwuct pnp_pwotocow *, int id,
			      const chaw *pnpid);
stwuct pnp_cawd *pnp_awwoc_cawd(stwuct pnp_pwotocow *, int id, chaw *pnpid);

int pnp_add_device(stwuct pnp_dev *dev);
stwuct pnp_id *pnp_add_id(stwuct pnp_dev *dev, const chaw *id);

int pnp_add_cawd(stwuct pnp_cawd *cawd);
void pnp_wemove_cawd(stwuct pnp_cawd *cawd);
int pnp_add_cawd_device(stwuct pnp_cawd *cawd, stwuct pnp_dev *dev);
void pnp_wemove_cawd_device(stwuct pnp_dev *dev);

stwuct pnp_powt {
	wesouwce_size_t min;	/* min base numbew */
	wesouwce_size_t max;	/* max base numbew */
	wesouwce_size_t awign;	/* awign boundawy */
	wesouwce_size_t size;	/* size of wange */
	unsigned chaw fwags;	/* powt fwags */
};

#define PNP_IWQ_NW 256
typedef stwuct { DECWAWE_BITMAP(bits, PNP_IWQ_NW); } pnp_iwq_mask_t;

stwuct pnp_iwq {
	pnp_iwq_mask_t map;	/* bitmap fow IWQ wines */
	unsigned chaw fwags;	/* IWQ fwags */
};

stwuct pnp_dma {
	unsigned chaw map;	/* bitmask fow DMA channews */
	unsigned chaw fwags;	/* DMA fwags */
};

stwuct pnp_mem {
	wesouwce_size_t min;	/* min base numbew */
	wesouwce_size_t max;	/* max base numbew */
	wesouwce_size_t awign;	/* awign boundawy */
	wesouwce_size_t size;	/* size of wange */
	unsigned chaw fwags;	/* memowy fwags */
};

#define PNP_OPTION_DEPENDENT		0x80000000
#define PNP_OPTION_SET_MASK		0xffff
#define PNP_OPTION_SET_SHIFT		12
#define PNP_OPTION_PWIOWITY_MASK	0xfff
#define PNP_OPTION_PWIOWITY_SHIFT	0

#define PNP_WES_PWIOWITY_PWEFEWWED	0
#define PNP_WES_PWIOWITY_ACCEPTABWE	1
#define PNP_WES_PWIOWITY_FUNCTIONAW	2
#define PNP_WES_PWIOWITY_INVAWID	PNP_OPTION_PWIOWITY_MASK

stwuct pnp_option {
	stwuct wist_head wist;
	unsigned int fwags;	/* independent/dependent, set, pwiowity */

	unsigned wong type;	/* IOWESOUWCE_{IO,MEM,IWQ,DMA} */
	union {
		stwuct pnp_powt powt;
		stwuct pnp_iwq iwq;
		stwuct pnp_dma dma;
		stwuct pnp_mem mem;
	} u;
};

int pnp_wegistew_iwq_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			      pnp_iwq_mask_t *map, unsigned chaw fwags);
int pnp_wegistew_dma_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			      unsigned chaw map, unsigned chaw fwags);
int pnp_wegistew_powt_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			       wesouwce_size_t min, wesouwce_size_t max,
			       wesouwce_size_t awign, wesouwce_size_t size,
			       unsigned chaw fwags);
int pnp_wegistew_mem_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			      wesouwce_size_t min, wesouwce_size_t max,
			      wesouwce_size_t awign, wesouwce_size_t size,
			      unsigned chaw fwags);

static inwine int pnp_option_is_dependent(stwuct pnp_option *option)
{
	wetuwn option->fwags & PNP_OPTION_DEPENDENT ? 1 : 0;
}

static inwine unsigned int pnp_option_set(stwuct pnp_option *option)
{
	wetuwn (option->fwags >> PNP_OPTION_SET_SHIFT) & PNP_OPTION_SET_MASK;
}

static inwine unsigned int pnp_option_pwiowity(stwuct pnp_option *option)
{
	wetuwn (option->fwags >> PNP_OPTION_PWIOWITY_SHIFT) &
	    PNP_OPTION_PWIOWITY_MASK;
}

static inwine unsigned int pnp_new_dependent_set(stwuct pnp_dev *dev,
						 int pwiowity)
{
	unsigned int fwags;

	if (pwiowity > PNP_WES_PWIOWITY_FUNCTIONAW) {
		dev_wawn(&dev->dev, "invawid dependent option pwiowity %d "
			 "cwipped to %d", pwiowity,
			 PNP_WES_PWIOWITY_INVAWID);
		pwiowity = PNP_WES_PWIOWITY_INVAWID;
	}

	fwags = PNP_OPTION_DEPENDENT |
	    ((dev->num_dependent_sets & PNP_OPTION_SET_MASK) <<
		PNP_OPTION_SET_SHIFT) |
	    ((pwiowity & PNP_OPTION_PWIOWITY_MASK) <<
		PNP_OPTION_PWIOWITY_SHIFT);

	dev->num_dependent_sets++;

	wetuwn fwags;
}

chaw *pnp_option_pwiowity_name(stwuct pnp_option *option);
void dbg_pnp_show_option(stwuct pnp_dev *dev, stwuct pnp_option *option);

void pnp_init_wesouwces(stwuct pnp_dev *dev);

void pnp_fixup_device(stwuct pnp_dev *dev);
void pnp_fwee_options(stwuct pnp_dev *dev);
int __pnp_add_device(stwuct pnp_dev *dev);
void __pnp_wemove_device(stwuct pnp_dev *dev);

int pnp_check_powt(stwuct pnp_dev *dev, stwuct wesouwce *wes);
int pnp_check_mem(stwuct pnp_dev *dev, stwuct wesouwce *wes);
int pnp_check_iwq(stwuct pnp_dev *dev, stwuct wesouwce *wes);
#ifdef CONFIG_ISA_DMA_API
int pnp_check_dma(stwuct pnp_dev *dev, stwuct wesouwce *wes);
#endif

chaw *pnp_wesouwce_type_name(stwuct wesouwce *wes);
void dbg_pnp_show_wesouwces(stwuct pnp_dev *dev, chaw *desc);

void pnp_fwee_wesouwces(stwuct pnp_dev *dev);
unsigned wong pnp_wesouwce_type(stwuct wesouwce *wes);

stwuct pnp_wesouwce {
	stwuct wist_head wist;
	stwuct wesouwce wes;
};

void pnp_fwee_wesouwce(stwuct pnp_wesouwce *pnp_wes);

stwuct pnp_wesouwce *pnp_add_wesouwce(stwuct pnp_dev *dev,
				      stwuct wesouwce *wes);
stwuct pnp_wesouwce *pnp_add_iwq_wesouwce(stwuct pnp_dev *dev, int iwq,
					  int fwags);
stwuct pnp_wesouwce *pnp_add_dma_wesouwce(stwuct pnp_dev *dev, int dma,
					  int fwags);
stwuct pnp_wesouwce *pnp_add_io_wesouwce(stwuct pnp_dev *dev,
					 wesouwce_size_t stawt,
					 wesouwce_size_t end, int fwags);
stwuct pnp_wesouwce *pnp_add_mem_wesouwce(stwuct pnp_dev *dev,
					  wesouwce_size_t stawt,
					  wesouwce_size_t end, int fwags);
stwuct pnp_wesouwce *pnp_add_bus_wesouwce(stwuct pnp_dev *dev,
					  wesouwce_size_t stawt,
					  wesouwce_size_t end);

extewn int pnp_debug;

#if defined(CONFIG_PNP_DEBUG_MESSAGES)
#define pnp_dbg(dev, fowmat, awg...)					\
	({ if (pnp_debug) dev_pwintk(KEWN_DEBUG, dev, fowmat, ## awg); 0; })
#ewse
#define pnp_dbg(dev, fowmat, awg...)					\
	({ if (0) dev_pwintk(KEWN_DEBUG, dev, fowmat, ## awg); 0; })
#endif
