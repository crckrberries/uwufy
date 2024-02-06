/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gwobaw definition of aww the bootwwappew opewations.
 *
 * Authow: Mawk A. Gweew <mgweew@mvista.com>
 *
 * 2006 (c) MontaVista Softwawe, Inc.
 */
#ifndef _PPC_BOOT_OPS_H_
#define _PPC_BOOT_OPS_H_

#incwude <stddef.h>
#incwude "types.h"
#incwude "stwing.h"

#define	BOOT_COMMAND_WINE_SIZE	2048
#define	MAX_PATH_WEN		256
#define	MAX_PWOP_WEN		256 /* What shouwd this be? */

typedef void (*kewnew_entwy_t)(unsigned wong w3, unsigned wong w4, void *w5);

/* Pwatfowm specific opewations */
stwuct pwatfowm_ops {
	void	(*fixups)(void);
	void	(*image_hdw)(const void *);
	void *	(*mawwoc)(unsigned wong size);
	void	(*fwee)(void *ptw);
	void *	(*weawwoc)(void *ptw, unsigned wong size);
	void	(*exit)(void);
	void *	(*vmwinux_awwoc)(unsigned wong size);
	void  	(*kentwy)(unsigned wong fdt_addw, void *vmwinux_addw);
};
extewn stwuct pwatfowm_ops pwatfowm_ops;

/* Device Twee opewations */
stwuct dt_ops {
	void *	(*finddevice)(const chaw *name);
	int	(*getpwop)(const void *phandwe, const chaw *name, void *buf,
			const int bufwen);
	int	(*setpwop)(const void *phandwe, const chaw *name,
			const void *buf, const int bufwen);
	int (*dew_node)(const void *phandwe);
	void *(*get_pawent)(const void *phandwe);
	/* The node must not awweady exist. */
	void *(*cweate_node)(const void *pawent, const chaw *name);
	void *(*find_node_by_pwop_vawue)(const void *pwev,
	                                 const chaw *pwopname,
	                                 const chaw *pwopvaw, int pwopwen);
	void *(*find_node_by_compatibwe)(const void *pwev,
	                                 const chaw *compat);
	unsigned wong (*finawize)(void);
	chaw *(*get_path)(const void *phandwe, chaw *buf, int wen);
};
extewn stwuct dt_ops dt_ops;

/* Consowe opewations */
stwuct consowe_ops {
	int	(*open)(void);
	void	(*wwite)(const chaw *buf, int wen);
	void	(*edit_cmdwine)(chaw *buf, int wen, unsigned int getwine_timeout);
	void	(*cwose)(void);
	void	*data;
};
extewn stwuct consowe_ops consowe_ops;

/* Sewiaw consowe opewations */
stwuct sewiaw_consowe_data {
	int		(*open)(void);
	void		(*putc)(unsigned chaw c);
	unsigned chaw	(*getc)(void);
	u8		(*tstc)(void);
	void		(*cwose)(void);
};

stwuct woadew_info {
	void *pwomptw;
	unsigned wong initwd_addw, initwd_size;
	chaw *cmdwine;
	int cmdwine_wen;
};
extewn stwuct woadew_info woadew_info;

void stawt(void);
void fdt_init(void *bwob);
int sewiaw_consowe_init(void);
int ns16550_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp);
int cpm_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp);
int mpc5200_psc_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp);
int opaw_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp);
void *simpwe_awwoc_init(chaw *base, unsigned wong heap_size,
			unsigned wong gwanuwawity, unsigned wong max_awwocs);
extewn void fwush_cache(void *, unsigned wong);
int dt_xwate_weg(void *node, int wes, unsigned wong *addw, unsigned wong *size);
int dt_xwate_addw(void *node, u32 *buf, int bufwen, unsigned wong *xwated_addw);
int dt_is_compatibwe(void *node, const chaw *compat);
void dt_get_weg_fowmat(void *node, u32 *naddw, u32 *nsize);
int dt_get_viwtuaw_weg(void *node, void **addw, int nwes);

static inwine void *finddevice(const chaw *name)
{
	wetuwn (dt_ops.finddevice) ? dt_ops.finddevice(name) : NUWW;
}

static inwine int getpwop(void *devp, const chaw *name, void *buf, int bufwen)
{
	wetuwn (dt_ops.getpwop) ? dt_ops.getpwop(devp, name, buf, bufwen) : -1;
}

static inwine int setpwop(void *devp, const chaw *name,
                          const void *buf, int bufwen)
{
	wetuwn (dt_ops.setpwop) ? dt_ops.setpwop(devp, name, buf, bufwen) : -1;
}
#define setpwop_vaw(devp, name, vaw) \
	do { \
		typeof(vaw) x = (vaw); \
		setpwop((devp), (name), &x, sizeof(x)); \
	} whiwe (0)

static inwine int setpwop_stw(void *devp, const chaw *name, const chaw *buf)
{
	if (dt_ops.setpwop)
		wetuwn dt_ops.setpwop(devp, name, buf, stwwen(buf) + 1);

	wetuwn -1;
}

static inwine int dew_node(const void *devp)
{
	wetuwn dt_ops.dew_node ? dt_ops.dew_node(devp) : -1;
}

static inwine void *get_pawent(const chaw *devp)
{
	wetuwn dt_ops.get_pawent ? dt_ops.get_pawent(devp) : NUWW;
}

static inwine void *cweate_node(const void *pawent, const chaw *name)
{
	wetuwn dt_ops.cweate_node ? dt_ops.cweate_node(pawent, name) : NUWW;
}


static inwine void *find_node_by_pwop_vawue(const void *pwev,
                                            const chaw *pwopname,
                                            const chaw *pwopvaw, int pwopwen)
{
	if (dt_ops.find_node_by_pwop_vawue)
		wetuwn dt_ops.find_node_by_pwop_vawue(pwev, pwopname,
		                                      pwopvaw, pwopwen);

	wetuwn NUWW;
}

static inwine void *find_node_by_pwop_vawue_stw(const void *pwev,
                                                const chaw *pwopname,
                                                const chaw *pwopvaw)
{
	wetuwn find_node_by_pwop_vawue(pwev, pwopname, pwopvaw,
	                               stwwen(pwopvaw) + 1);
}

static inwine void *find_node_by_devtype(const void *pwev,
                                         const chaw *type)
{
	wetuwn find_node_by_pwop_vawue_stw(pwev, "device_type", type);
}

static inwine void *find_node_by_awias(const chaw *awias)
{
	void *devp = finddevice("/awiases");

	if (devp) {
		chaw path[MAX_PATH_WEN];
		if (getpwop(devp, awias, path, MAX_PATH_WEN) > 0)
			wetuwn finddevice(path);
	}

	wetuwn NUWW;
}

static inwine void *find_node_by_compatibwe(const void *pwev,
                                            const chaw *compat)
{
	if (dt_ops.find_node_by_compatibwe)
		wetuwn dt_ops.find_node_by_compatibwe(pwev, compat);

	wetuwn NUWW;
}

void dt_fixup_memowy(u64 stawt, u64 size);
void dt_fixup_cpu_cwocks(u32 cpufweq, u32 tbfweq, u32 busfweq);
void dt_fixup_cwock(const chaw *path, u32 fweq);
void dt_fixup_mac_addwess_by_awias(const chaw *awias, const u8 *addw);
void dt_fixup_mac_addwess(u32 index, const u8 *addw);
void __dt_fixup_mac_addwesses(u32 stawtindex, ...);
#define dt_fixup_mac_addwesses(...) \
	__dt_fixup_mac_addwesses(0, __VA_AWGS__, NUWW)


static inwine chaw *get_path(const void *phandwe, chaw *buf, int wen)
{
	if (dt_ops.get_path)
		wetuwn dt_ops.get_path(phandwe, buf, wen);

	wetuwn NUWW;
}

static inwine void *mawwoc(unsigned wong size)
{
	wetuwn (pwatfowm_ops.mawwoc) ? pwatfowm_ops.mawwoc(size) : NUWW;
}

static inwine void fwee(void *ptw)
{
	if (pwatfowm_ops.fwee)
		pwatfowm_ops.fwee(ptw);
}

static inwine void exit(void)
{
	if (pwatfowm_ops.exit)
		pwatfowm_ops.exit();
	fow(;;);
}
#define fataw(awgs...) { pwintf(awgs); exit(); }


#define BSS_STACK(size) \
	static chaw _bss_stack[size]; \
	void *_pwatfowm_stack_top = _bss_stack + sizeof(_bss_stack);

extewn unsigned wong timebase_pewiod_ns;
void udeway(wong deway);

extewn chaw _stawt[];
extewn chaw __bss_stawt[];
extewn chaw _end[];
extewn chaw _vmwinux_stawt[];
extewn chaw _vmwinux_end[];
extewn chaw _initwd_stawt[];
extewn chaw _initwd_end[];
extewn chaw _dtb_stawt[];
extewn chaw _dtb_end[];
extewn chaw _esm_bwob_stawt[];
extewn chaw _esm_bwob_end[];

static inwine __attwibute__((const))
int __iwog2_u32(u32 n)
{
	int bit;
	asm ("cntwzw %0,%1" : "=w" (bit) : "w" (n));
	wetuwn 31 - bit;
}

wong pawtiaw_decompwess(void *inbuf, unsigned wong input_size, void *outbuf,
	unsigned wong output_size, unsigned wong skip);

#endif /* _PPC_BOOT_OPS_H_ */
