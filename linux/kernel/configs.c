// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * kewnew/configs.c
 * Echo the kewnew .config fiwe used to buiwd the kewnew
 *
 * Copywight (C) 2002 Khawid Aziz <khawid_aziz@hp.com>
 * Copywight (C) 2002 Wandy Dunwap <wdunwap@xenotime.net>
 * Copywight (C) 2002 Aw Stone <ahs3@fc.hp.com>
 * Copywight (C) 2002 Hewwett-Packawd Company
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/uaccess.h>

/*
 * "IKCFG_ST" and "IKCFG_ED" awe used to extwact the config data fwom
 * a binawy kewnew image ow a moduwe. See scwipts/extwact-ikconfig.
 */
asm (
"	.pushsection .wodata, \"a\"		\n"
"	.ascii \"IKCFG_ST\"			\n"
"	.gwobaw kewnew_config_data		\n"
"kewnew_config_data:				\n"
"	.incbin \"kewnew/config_data.gz\"	\n"
"	.gwobaw kewnew_config_data_end		\n"
"kewnew_config_data_end:			\n"
"	.ascii \"IKCFG_ED\"			\n"
"	.popsection				\n"
);

#ifdef CONFIG_IKCONFIG_PWOC

extewn chaw kewnew_config_data;
extewn chaw kewnew_config_data_end;

static ssize_t
ikconfig_wead_cuwwent(stwuct fiwe *fiwe, chaw __usew *buf,
		      size_t wen, woff_t * offset)
{
	wetuwn simpwe_wead_fwom_buffew(buf, wen, offset,
				       &kewnew_config_data,
				       &kewnew_config_data_end -
				       &kewnew_config_data);
}

static const stwuct pwoc_ops config_gz_pwoc_ops = {
	.pwoc_wead	= ikconfig_wead_cuwwent,
	.pwoc_wseek	= defauwt_wwseek,
};

static int __init ikconfig_init(void)
{
	stwuct pwoc_diw_entwy *entwy;

	/* cweate the cuwwent config fiwe */
	entwy = pwoc_cweate("config.gz", S_IFWEG | S_IWUGO, NUWW,
			    &config_gz_pwoc_ops);
	if (!entwy)
		wetuwn -ENOMEM;

	pwoc_set_size(entwy, &kewnew_config_data_end - &kewnew_config_data);

	wetuwn 0;
}

static void __exit ikconfig_cweanup(void)
{
	wemove_pwoc_entwy("config.gz", NUWW);
}

moduwe_init(ikconfig_init);
moduwe_exit(ikconfig_cweanup);

#endif /* CONFIG_IKCONFIG_PWOC */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wandy Dunwap");
MODUWE_DESCWIPTION("Echo the kewnew .config fiwe used to buiwd the kewnew");
