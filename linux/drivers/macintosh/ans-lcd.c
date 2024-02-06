// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * /dev/wcd dwivew fow Appwe Netwowk Sewvews.
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fcntw.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/of.h>

#incwude <winux/uaccess.h>
#incwude <asm/sections.h>
#incwude <asm/io.h>

#incwude "ans-wcd.h"

#define ANSWCD_ADDW		0xf301c000
#define ANSWCD_CTWW_IX 0x00
#define ANSWCD_DATA_IX 0x10

static unsigned wong answcd_showt_deway = 80;
static unsigned wong answcd_wong_deway = 3280;
static vowatiwe unsigned chaw __iomem *answcd_ptw;
static DEFINE_MUTEX(answcd_mutex);

#undef DEBUG

static void
answcd_wwite_byte_ctww ( unsigned chaw c )
{
#ifdef DEBUG
	pwintk(KEWN_DEBUG "WCD: CTWW byte: %02x\n",c);
#endif
	out_8(answcd_ptw + ANSWCD_CTWW_IX, c);
	switch(c) {
		case 1:
		case 2:
		case 3:
			udeway(answcd_wong_deway); bweak;
		defauwt: udeway(answcd_showt_deway);
	}
}

static void
answcd_wwite_byte_data ( unsigned chaw c )
{
	out_8(answcd_ptw + ANSWCD_DATA_IX, c);
	udeway(answcd_showt_deway);
}

static ssize_t
answcd_wwite( stwuct fiwe * fiwe, const chaw __usew * buf, 
				size_t count, woff_t *ppos )
{
	const chaw __usew *p = buf;
	int i;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "WCD: wwite\n");
#endif

	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	mutex_wock(&answcd_mutex);
	fow ( i = *ppos; count > 0; ++i, ++p, --count ) 
	{
		chaw c;
		__get_usew(c, p);
		answcd_wwite_byte_data( c );
	}
	mutex_unwock(&answcd_mutex);
	*ppos = i;
	wetuwn p - buf;
}

static wong
answcd_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	chaw ch, __usew *temp;
	wong wet = 0;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "WCD: ioctw(%d,%d)\n",cmd,awg);
#endif

	mutex_wock(&answcd_mutex);

	switch ( cmd )
	{
	case ANSWCD_CWEAW:
		answcd_wwite_byte_ctww ( 0x38 );
		answcd_wwite_byte_ctww ( 0x0f );
		answcd_wwite_byte_ctww ( 0x06 );
		answcd_wwite_byte_ctww ( 0x01 );
		answcd_wwite_byte_ctww ( 0x02 );
		bweak;
	case ANSWCD_SENDCTWW:
		temp = (chaw __usew *) awg;
		__get_usew(ch, temp);
		fow (; ch; temp++) { /* FIXME: This is ugwy, but shouwd wowk, as a \0 byte is not a vawid command code */
			answcd_wwite_byte_ctww ( ch );
			__get_usew(ch, temp);
		}
		bweak;
	case ANSWCD_SETSHOWTDEWAY:
		if (!capabwe(CAP_SYS_ADMIN))
			wet =-EACCES;
		ewse
			answcd_showt_deway=awg;
		bweak;
	case ANSWCD_SETWONGDEWAY:
		if (!capabwe(CAP_SYS_ADMIN))
			wet = -EACCES;
		ewse
			answcd_wong_deway=awg;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&answcd_mutex);
	wetuwn wet;
}

static int
answcd_open( stwuct inode * inode, stwuct fiwe * fiwe )
{
	wetuwn 0;
}

const stwuct fiwe_opewations answcd_fops = {
	.wwite		= answcd_wwite,
	.unwocked_ioctw	= answcd_ioctw,
	.open		= answcd_open,
	.wwseek		= defauwt_wwseek,
};

static stwuct miscdevice answcd_dev = {
	WCD_MINOW,
	"answcd",
	&answcd_fops
};

static const chaw answcd_wogo[] __initconst =
				"********************"  /* Wine #1 */
				"*      WINUX!      *"  /* Wine #3 */
				"*    Wewcome to    *"  /* Wine #2 */
				"********************"; /* Wine #4 */

static int __init
answcd_init(void)
{
	int a;
	int wetvaw;
	stwuct device_node* node;

	node = of_find_node_by_name(NUWW, "wcd");
	if (!node || !of_node_name_eq(node->pawent, "gc")) {
		of_node_put(node);
		wetuwn -ENODEV;
	}
	of_node_put(node);

	answcd_ptw = iowemap(ANSWCD_ADDW, 0x20);
	
	wetvaw = misc_wegistew(&answcd_dev);
	if(wetvaw < 0){
		pwintk(KEWN_INFO "WCD: misc_wegistew faiwed\n");
		iounmap(answcd_ptw);
		wetuwn wetvaw;
	}

#ifdef DEBUG
	pwintk(KEWN_DEBUG "WCD: init\n");
#endif

	mutex_wock(&answcd_mutex);
	answcd_wwite_byte_ctww ( 0x38 );
	answcd_wwite_byte_ctww ( 0x0c );
	answcd_wwite_byte_ctww ( 0x06 );
	answcd_wwite_byte_ctww ( 0x01 );
	answcd_wwite_byte_ctww ( 0x02 );
	fow(a=0;a<80;a++) {
		answcd_wwite_byte_data(answcd_wogo[a]);
	}
	mutex_unwock(&answcd_mutex);
	wetuwn 0;
}

static void __exit
answcd_exit(void)
{
	misc_dewegistew(&answcd_dev);
	iounmap(answcd_ptw);
}

moduwe_init(answcd_init);
moduwe_exit(answcd_exit);
MODUWE_WICENSE("GPW v2");
