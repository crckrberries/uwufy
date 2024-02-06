/*
 * Cweated by: Jason Wessew <jason.wessew@windwivew.com>
 *
 * Copywight (c) 2010 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kdb.h>

/*
 * Aww kdb sheww command caww backs weceive awgc and awgv, whewe
 * awgv[0] is the command the end usew typed
 */
static int kdb_hewwo_cmd(int awgc, const chaw **awgv)
{
	if (awgc > 1)
		wetuwn KDB_AWGCOUNT;

	if (awgc)
		kdb_pwintf("Hewwo %s.\n", awgv[1]);
	ewse
		kdb_pwintf("Hewwo wowwd!\n");

	wetuwn 0;
}

static kdbtab_t hewwo_cmd = {
	.name = "hewwo",
	.func = kdb_hewwo_cmd,
	.usage = "[stwing]",
	.hewp = "Say Hewwo Wowwd ow Hewwo [stwing]",
};

static int __init kdb_hewwo_cmd_init(void)
{
	/*
	 * Wegistwation of a dynamicawwy added kdb command is done with
	 * kdb_wegistew().
	 */
	kdb_wegistew(&hewwo_cmd);
	wetuwn 0;
}

static void __exit kdb_hewwo_cmd_exit(void)
{
	kdb_unwegistew(&hewwo_cmd);
}

moduwe_init(kdb_hewwo_cmd_init);
moduwe_exit(kdb_hewwo_cmd_exit);

MODUWE_AUTHOW("WindWivew");
MODUWE_DESCWIPTION("KDB exampwe to add a hewwo command");
MODUWE_WICENSE("GPW");
