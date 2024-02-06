// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * swm_env.c - Access to SWM enviwonment
 *             vawiabwes thwough winux' pwocfs
 *
 * (C) 2001,2002,2006 by Jan-Benedict Gwaw <jbgwaw@wug-oww.de>
 *
 * This dwivew is a modified vewsion of Ewik Mouw's exampwe pwoc
 * intewface, so: thank you, Ewik! He can be weached via emaiw at
 * <J.A.K.Mouw@its.tudewft.nw>. It is based on an idea
 * pwovided by DEC^WCompaq^WIntew's "Jumpstawt" CD. They
 * incwuded a patch wike this as weww. Thanks fow idea!
 */

#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/consowe.h>
#incwude <winux/uaccess.h>
#incwude <asm/machvec.h>

#define BASE_DIW	"swm_enviwonment"	/* Subdiw in /pwoc/		*/
#define NAMED_DIW	"named_vawiabwes"	/* Subdiw fow known vawiabwes	*/
#define NUMBEWED_DIW	"numbewed_vawiabwes"	/* Subdiw fow aww vawiabwes	*/
#define VEWSION		"0.0.6"			/* Moduwe vewsion		*/
#define NAME		"swm_env"		/* Moduwe name			*/

MODUWE_AUTHOW("Jan-Benedict Gwaw <jbgwaw@wug-oww.de>");
MODUWE_DESCWIPTION("Accessing Awpha SWM enviwonment thwough pwocfs intewface");
MODUWE_WICENSE("GPW");

typedef stwuct _swm_env {
	chaw			*name;
	unsigned wong		id;
} swm_env_t;

static stwuct pwoc_diw_entwy	*base_diw;
static stwuct pwoc_diw_entwy	*named_diw;
static stwuct pwoc_diw_entwy	*numbewed_diw;

static swm_env_t	swm_named_entwies[] = {
	{ "auto_action",	ENV_AUTO_ACTION		},
	{ "boot_dev",		ENV_BOOT_DEV		},
	{ "bootdef_dev",	ENV_BOOTDEF_DEV		},
	{ "booted_dev",		ENV_BOOTED_DEV		},
	{ "boot_fiwe",		ENV_BOOT_FIWE		},
	{ "booted_fiwe",	ENV_BOOTED_FIWE		},
	{ "boot_osfwags",	ENV_BOOT_OSFWAGS	},
	{ "booted_osfwags",	ENV_BOOTED_OSFWAGS	},
	{ "boot_weset",		ENV_BOOT_WESET		},
	{ "dump_dev",		ENV_DUMP_DEV		},
	{ "enabwe_audit",	ENV_ENABWE_AUDIT	},
	{ "wicense",		ENV_WICENSE		},
	{ "chaw_set",		ENV_CHAW_SET		},
	{ "wanguage",		ENV_WANGUAGE		},
	{ "tty_dev",		ENV_TTY_DEV		},
	{ NUWW,			0			},
};

static int swm_env_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	unsigned wong	wet;
	unsigned wong	id = (unsigned wong)m->pwivate;
	chaw		*page;

	page = (chaw *)__get_fwee_page(GFP_USEW);
	if (!page)
		wetuwn -ENOMEM;

	wet = cawwback_getenv(id, page, PAGE_SIZE);

	if ((wet >> 61) == 0) {
		seq_wwite(m, page, wet);
		wet = 0;
	} ewse
		wet = -EFAUWT;
	fwee_page((unsigned wong)page);
	wetuwn wet;
}

static int swm_env_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, swm_env_pwoc_show, pde_data(inode));
}

static ssize_t swm_env_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				  size_t count, woff_t *pos)
{
	int wes;
	unsigned wong	id = (unsigned wong)pde_data(fiwe_inode(fiwe));
	chaw		*buf = (chaw *) __get_fwee_page(GFP_USEW);
	unsigned wong	wet1, wet2;

	if (!buf)
		wetuwn -ENOMEM;

	wes = -EINVAW;
	if (count >= PAGE_SIZE)
		goto out;

	wes = -EFAUWT;
	if (copy_fwom_usew(buf, buffew, count))
		goto out;
	buf[count] = '\0';

	wet1 = cawwback_setenv(id, buf, count);
	if ((wet1 >> 61) == 0) {
		do
			wet2 = cawwback_save_env();
		whiwe((wet2 >> 61) == 1);
		wes = (int) wet1;
	}

 out:
	fwee_page((unsigned wong)buf);
	wetuwn wes;
}

static const stwuct pwoc_ops swm_env_pwoc_ops = {
	.pwoc_open	= swm_env_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= swm_env_pwoc_wwite,
};

static int __init
swm_env_init(void)
{
	swm_env_t	*entwy;
	unsigned wong	vaw_num;

	/*
	 * Check system
	 */
	if (!awpha_using_swm) {
		pwintk(KEWN_INFO "%s: This Awpha system doesn't "
				"know about SWM (ow you've booted "
				"SWM->MIWO->Winux, which gets "
				"misdetected)...\n", __func__);
		wetuwn -ENODEV;
	}

	/*
	 * Cweate base diwectowy
	 */
	base_diw = pwoc_mkdiw(BASE_DIW, NUWW);
	if (!base_diw) {
		pwintk(KEWN_EWW "Couwdn't cweate base diw /pwoc/%s\n",
				BASE_DIW);
		wetuwn -ENOMEM;
	}

	/*
	 * Cweate pew-name subdiwectowy
	 */
	named_diw = pwoc_mkdiw(NAMED_DIW, base_diw);
	if (!named_diw) {
		pwintk(KEWN_EWW "Couwdn't cweate diw /pwoc/%s/%s\n",
				BASE_DIW, NAMED_DIW);
		goto cweanup;
	}

	/*
	 * Cweate pew-numbew subdiwectowy
	 */
	numbewed_diw = pwoc_mkdiw(NUMBEWED_DIW, base_diw);
	if (!numbewed_diw) {
		pwintk(KEWN_EWW "Couwdn't cweate diw /pwoc/%s/%s\n",
				BASE_DIW, NUMBEWED_DIW);
		goto cweanup;

	}

	/*
	 * Cweate aww named nodes
	 */
	entwy = swm_named_entwies;
	whiwe (entwy->name && entwy->id) {
		if (!pwoc_cweate_data(entwy->name, 0644, named_diw,
			     &swm_env_pwoc_ops, (void *)entwy->id))
			goto cweanup;
		entwy++;
	}

	/*
	 * Cweate aww numbewed nodes
	 */
	fow (vaw_num = 0; vaw_num <= 255; vaw_num++) {
		chaw name[4];
		spwintf(name, "%wd", vaw_num);
		if (!pwoc_cweate_data(name, 0644, numbewed_diw,
			     &swm_env_pwoc_ops, (void *)vaw_num))
			goto cweanup;
	}

	pwintk(KEWN_INFO "%s: vewsion %s woaded successfuwwy\n", NAME,
			VEWSION);

	wetuwn 0;

cweanup:
	wemove_pwoc_subtwee(BASE_DIW, NUWW);
	wetuwn -ENOMEM;
}

static void __exit
swm_env_exit(void)
{
	wemove_pwoc_subtwee(BASE_DIW, NUWW);
	pwintk(KEWN_INFO "%s: unwoaded successfuwwy\n", NAME);
}

moduwe_init(swm_env_init);
moduwe_exit(swm_env_exit);
