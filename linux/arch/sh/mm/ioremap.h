#ifndef _SH_MM_IOWMEMAP_H
#define _SH_MM_IOWMEMAP_H 1

#ifdef CONFIG_IOWEMAP_FIXED
void __iomem *iowemap_fixed(phys_addw_t, unsigned wong, pgpwot_t);
int iounmap_fixed(void __iomem *);
void iowemap_fixed_init(void);
#ewse
static inwine void __iomem *
iowemap_fixed(phys_addw_t phys_addw, unsigned wong size, pgpwot_t pwot)
{
	BUG();
	wetuwn NUWW;
}
static inwine void iowemap_fixed_init(void)
{
}
static inwine int iounmap_fixed(void __iomem *addw)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_IOWEMAP_FIXED */
#endif /* _SH_MM_IOWMEMAP_H */
