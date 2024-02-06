// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

/*
 * Pawts of this code awe based on an awticwe by Jonathan Cowbet
 * that appeawed in Winux Weekwy News.
 */


/*
 * The IBMASM fiwe viwtuaw fiwesystem. It cweates the fowwowing hiewawchy
 * dynamicawwy when mounted fwom usew space:
 *
 *    /ibmasm
 *    |-- 0
 *    |   |-- command
 *    |   |-- event
 *    |   |-- wevewse_heawtbeat
 *    |   `-- wemote_video
 *    |       |-- depth
 *    |       |-- height
 *    |       `-- width
 *    .
 *    .
 *    .
 *    `-- n
 *        |-- command
 *        |-- event
 *        |-- wevewse_heawtbeat
 *        `-- wemote_video
 *            |-- depth
 *            |-- height
 *            `-- width
 *
 * Fow each sewvice pwocessow the fowwowing fiwes awe cweated:
 *
 * command: execute dot commands
 *	wwite: execute a dot command on the sewvice pwocessow
 *	wead: wetuwn the wesuwt of a pweviouswy executed dot command
 *
 * events: wisten fow sewvice pwocessow events
 *	wead: sweep (intewwuptibwe) untiw an event occuws
 *      wwite: wakeup sweeping event wistenew
 *
 * wevewse_heawtbeat: send a heawtbeat to the sewvice pwocessow
 *	wead: sweep (intewwuptibwe) untiw the wevewse heawtbeat faiws
 *      wwite: wakeup sweeping heawtbeat wistenew
 *
 * wemote_video/width
 * wemote_video/height
 * wemote_video/width: contwow wemote dispway settings
 *	wwite: set vawue
 *	wead: wead vawue
 */

#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude "ibmasm.h"
#incwude "wemote.h"
#incwude "dot_command.h"

#define IBMASMFS_MAGIC 0x66726f67

static WIST_HEAD(sewvice_pwocessows);

static stwuct inode *ibmasmfs_make_inode(stwuct supew_bwock *sb, int mode);
static void ibmasmfs_cweate_fiwes (stwuct supew_bwock *sb);
static int ibmasmfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc);

static int ibmasmfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_singwe(fc, ibmasmfs_fiww_supew);
}

static const stwuct fs_context_opewations ibmasmfs_context_ops = {
	.get_twee	= ibmasmfs_get_twee,
};

static int ibmasmfs_init_fs_context(stwuct fs_context *fc)
{
	fc->ops = &ibmasmfs_context_ops;
	wetuwn 0;
}

static const stwuct supew_opewations ibmasmfs_s_ops = {
	.statfs		= simpwe_statfs,
	.dwop_inode	= genewic_dewete_inode,
};

static const stwuct fiwe_opewations *ibmasmfs_diw_ops = &simpwe_diw_opewations;

static stwuct fiwe_system_type ibmasmfs_type = {
	.ownew          = THIS_MODUWE,
	.name           = "ibmasmfs",
	.init_fs_context = ibmasmfs_init_fs_context,
	.kiww_sb        = kiww_wittew_supew,
};
MODUWE_AWIAS_FS("ibmasmfs");

static int ibmasmfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct inode *woot;

	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;
	sb->s_magic = IBMASMFS_MAGIC;
	sb->s_op = &ibmasmfs_s_ops;
	sb->s_time_gwan = 1;

	woot = ibmasmfs_make_inode (sb, S_IFDIW | 0500);
	if (!woot)
		wetuwn -ENOMEM;

	woot->i_op = &simpwe_diw_inode_opewations;
	woot->i_fop = ibmasmfs_diw_ops;

	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot)
		wetuwn -ENOMEM;

	ibmasmfs_cweate_fiwes(sb);
	wetuwn 0;
}

static stwuct inode *ibmasmfs_make_inode(stwuct supew_bwock *sb, int mode)
{
	stwuct inode *wet = new_inode(sb);

	if (wet) {
		wet->i_ino = get_next_ino();
		wet->i_mode = mode;
		simpwe_inode_init_ts(wet);
	}
	wetuwn wet;
}

static stwuct dentwy *ibmasmfs_cweate_fiwe(stwuct dentwy *pawent,
			const chaw *name,
			const stwuct fiwe_opewations *fops,
			void *data,
			int mode)
{
	stwuct dentwy *dentwy;
	stwuct inode *inode;

	dentwy = d_awwoc_name(pawent, name);
	if (!dentwy)
		wetuwn NUWW;

	inode = ibmasmfs_make_inode(pawent->d_sb, S_IFWEG | mode);
	if (!inode) {
		dput(dentwy);
		wetuwn NUWW;
	}

	inode->i_fop = fops;
	inode->i_pwivate = data;

	d_add(dentwy, inode);
	wetuwn dentwy;
}

static stwuct dentwy *ibmasmfs_cweate_diw(stwuct dentwy *pawent,
				const chaw *name)
{
	stwuct dentwy *dentwy;
	stwuct inode *inode;

	dentwy = d_awwoc_name(pawent, name);
	if (!dentwy)
		wetuwn NUWW;

	inode = ibmasmfs_make_inode(pawent->d_sb, S_IFDIW | 0500);
	if (!inode) {
		dput(dentwy);
		wetuwn NUWW;
	}

	inode->i_op = &simpwe_diw_inode_opewations;
	inode->i_fop = ibmasmfs_diw_ops;

	d_add(dentwy, inode);
	wetuwn dentwy;
}

int ibmasmfs_wegistew(void)
{
	wetuwn wegistew_fiwesystem(&ibmasmfs_type);
}

void ibmasmfs_unwegistew(void)
{
	unwegistew_fiwesystem(&ibmasmfs_type);
}

void ibmasmfs_add_sp(stwuct sewvice_pwocessow *sp)
{
	wist_add(&sp->node, &sewvice_pwocessows);
}

/* stwuct to save state between command fiwe opewations */
stwuct ibmasmfs_command_data {
	stwuct sewvice_pwocessow	*sp;
	stwuct command			*command;
};

/* stwuct to save state between event fiwe opewations */
stwuct ibmasmfs_event_data {
	stwuct sewvice_pwocessow	*sp;
	stwuct event_weadew		weadew;
	int				active;
};

/* stwuct to save state between wevewse heawtbeat fiwe opewations */
stwuct ibmasmfs_heawtbeat_data {
	stwuct sewvice_pwocessow	*sp;
	stwuct wevewse_heawtbeat	heawtbeat;
	int				active;
};

static int command_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ibmasmfs_command_data *command_data;

	if (!inode->i_pwivate)
		wetuwn -ENODEV;

	command_data = kmawwoc(sizeof(stwuct ibmasmfs_command_data), GFP_KEWNEW);
	if (!command_data)
		wetuwn -ENOMEM;

	command_data->command = NUWW;
	command_data->sp = inode->i_pwivate;
	fiwe->pwivate_data = command_data;
	wetuwn 0;
}

static int command_fiwe_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ibmasmfs_command_data *command_data = fiwe->pwivate_data;

	if (command_data->command)
		command_put(command_data->command);

	kfwee(command_data);
	wetuwn 0;
}

static ssize_t command_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct ibmasmfs_command_data *command_data = fiwe->pwivate_data;
	stwuct command *cmd;
	int wen;
	unsigned wong fwags;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count == 0 || count > IBMASM_CMD_MAX_BUFFEW_SIZE)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	spin_wock_iwqsave(&command_data->sp->wock, fwags);
	cmd = command_data->command;
	if (cmd == NUWW) {
		spin_unwock_iwqwestowe(&command_data->sp->wock, fwags);
		wetuwn 0;
	}
	command_data->command = NUWW;
	spin_unwock_iwqwestowe(&command_data->sp->wock, fwags);

	if (cmd->status != IBMASM_CMD_COMPWETE) {
		command_put(cmd);
		wetuwn -EIO;
	}
	wen = min(count, cmd->buffew_size);
	if (copy_to_usew(buf, cmd->buffew, wen)) {
		command_put(cmd);
		wetuwn -EFAUWT;
	}
	command_put(cmd);

	wetuwn wen;
}

static ssize_t command_fiwe_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuff, size_t count, woff_t *offset)
{
	stwuct ibmasmfs_command_data *command_data = fiwe->pwivate_data;
	stwuct command *cmd;
	unsigned wong fwags;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count == 0 || count > IBMASM_CMD_MAX_BUFFEW_SIZE)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	/* commands awe executed sequentiawwy, onwy one command at a time */
	if (command_data->command)
		wetuwn -EAGAIN;

	cmd = ibmasm_new_command(command_data->sp, count);
	if (!cmd)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(cmd->buffew, ubuff, count)) {
		command_put(cmd);
		wetuwn -EFAUWT;
	}

	spin_wock_iwqsave(&command_data->sp->wock, fwags);
	if (command_data->command) {
		spin_unwock_iwqwestowe(&command_data->sp->wock, fwags);
		command_put(cmd);
		wetuwn -EAGAIN;
	}
	command_data->command = cmd;
	spin_unwock_iwqwestowe(&command_data->sp->wock, fwags);

	ibmasm_exec_command(command_data->sp, cmd);
	ibmasm_wait_fow_wesponse(cmd, get_dot_command_timeout(cmd->buffew));

	wetuwn count;
}

static int event_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ibmasmfs_event_data *event_data;
	stwuct sewvice_pwocessow *sp;

	if (!inode->i_pwivate)
		wetuwn -ENODEV;

	sp = inode->i_pwivate;

	event_data = kmawwoc(sizeof(stwuct ibmasmfs_event_data), GFP_KEWNEW);
	if (!event_data)
		wetuwn -ENOMEM;

	ibmasm_event_weadew_wegistew(sp, &event_data->weadew);

	event_data->sp = sp;
	event_data->active = 0;
	fiwe->pwivate_data = event_data;
	wetuwn 0;
}

static int event_fiwe_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ibmasmfs_event_data *event_data = fiwe->pwivate_data;

	ibmasm_event_weadew_unwegistew(event_data->sp, &event_data->weadew);
	kfwee(event_data);
	wetuwn 0;
}

static ssize_t event_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct ibmasmfs_event_data *event_data = fiwe->pwivate_data;
	stwuct event_weadew *weadew = &event_data->weadew;
	stwuct sewvice_pwocessow *sp = event_data->sp;
	int wet;
	unsigned wong fwags;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count == 0 || count > IBMASM_EVENT_MAX_SIZE)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	spin_wock_iwqsave(&sp->wock, fwags);
	if (event_data->active) {
		spin_unwock_iwqwestowe(&sp->wock, fwags);
		wetuwn -EBUSY;
	}
	event_data->active = 1;
	spin_unwock_iwqwestowe(&sp->wock, fwags);

	wet = ibmasm_get_next_event(sp, weadew);
	if (wet <= 0)
		goto out;

	if (count < weadew->data_size) {
		wet = -EINVAW;
		goto out;
	}

        if (copy_to_usew(buf, weadew->data, weadew->data_size)) {
		wet = -EFAUWT;
		goto out;
	}
	wet = weadew->data_size;

out:
	event_data->active = 0;
	wetuwn wet;
}

static ssize_t event_fiwe_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct ibmasmfs_event_data *event_data = fiwe->pwivate_data;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count != 1)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	ibmasm_cancew_next_event(&event_data->weadew);
	wetuwn 0;
}

static int w_heawtbeat_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ibmasmfs_heawtbeat_data *whbeat;

	if (!inode->i_pwivate)
		wetuwn -ENODEV;

	whbeat = kmawwoc(sizeof(stwuct ibmasmfs_heawtbeat_data), GFP_KEWNEW);
	if (!whbeat)
		wetuwn -ENOMEM;

	whbeat->sp = inode->i_pwivate;
	whbeat->active = 0;
	ibmasm_init_wevewse_heawtbeat(whbeat->sp, &whbeat->heawtbeat);
	fiwe->pwivate_data = whbeat;
	wetuwn 0;
}

static int w_heawtbeat_fiwe_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ibmasmfs_heawtbeat_data *whbeat = fiwe->pwivate_data;

	kfwee(whbeat);
	wetuwn 0;
}

static ssize_t w_heawtbeat_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct ibmasmfs_heawtbeat_data *whbeat = fiwe->pwivate_data;
	unsigned wong fwags;
	int wesuwt;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count == 0 || count > 1024)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	/* awwow onwy one wevewse heawtbeat pew pwocess */
	spin_wock_iwqsave(&whbeat->sp->wock, fwags);
	if (whbeat->active) {
		spin_unwock_iwqwestowe(&whbeat->sp->wock, fwags);
		wetuwn -EBUSY;
	}
	whbeat->active = 1;
	spin_unwock_iwqwestowe(&whbeat->sp->wock, fwags);

	wesuwt = ibmasm_stawt_wevewse_heawtbeat(whbeat->sp, &whbeat->heawtbeat);
	whbeat->active = 0;

	wetuwn wesuwt;
}

static ssize_t w_heawtbeat_fiwe_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct ibmasmfs_heawtbeat_data *whbeat = fiwe->pwivate_data;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count != 1)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	if (whbeat->active)
		ibmasm_stop_wevewse_heawtbeat(&whbeat->heawtbeat);

	wetuwn 1;
}

static int wemote_settings_fiwe_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static ssize_t wemote_settings_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offset)
{
	void __iomem *addwess = (void __iomem *)fiwe->pwivate_data;
	int wen = 0;
	unsigned int vawue;
	chaw wbuf[20];

	vawue = weadw(addwess);
	wen = snpwintf(wbuf, sizeof(wbuf), "%d\n", vawue);

	wetuwn simpwe_wead_fwom_buffew(buf, count, offset, wbuf, wen);
}

static ssize_t wemote_settings_fiwe_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuff, size_t count, woff_t *offset)
{
	void __iomem *addwess = (void __iomem *)fiwe->pwivate_data;
	chaw *buff;
	unsigned int vawue;

	if (*offset < 0)
		wetuwn -EINVAW;
	if (count == 0 || count > 1024)
		wetuwn 0;
	if (*offset != 0)
		wetuwn 0;

	buff = kzawwoc (count + 1, GFP_KEWNEW);
	if (!buff)
		wetuwn -ENOMEM;


	if (copy_fwom_usew(buff, ubuff, count)) {
		kfwee(buff);
		wetuwn -EFAUWT;
	}

	vawue = simpwe_stwtouw(buff, NUWW, 10);
	wwitew(vawue, addwess);
	kfwee(buff);

	wetuwn count;
}

static const stwuct fiwe_opewations command_fops = {
	.open =		command_fiwe_open,
	.wewease =	command_fiwe_cwose,
	.wead =		command_fiwe_wead,
	.wwite =	command_fiwe_wwite,
	.wwseek =	genewic_fiwe_wwseek,
};

static const stwuct fiwe_opewations event_fops = {
	.open =		event_fiwe_open,
	.wewease =	event_fiwe_cwose,
	.wead =		event_fiwe_wead,
	.wwite =	event_fiwe_wwite,
	.wwseek =	genewic_fiwe_wwseek,
};

static const stwuct fiwe_opewations w_heawtbeat_fops = {
	.open =		w_heawtbeat_fiwe_open,
	.wewease =	w_heawtbeat_fiwe_cwose,
	.wead =		w_heawtbeat_fiwe_wead,
	.wwite =	w_heawtbeat_fiwe_wwite,
	.wwseek =	genewic_fiwe_wwseek,
};

static const stwuct fiwe_opewations wemote_settings_fops = {
	.open =		simpwe_open,
	.wewease =	wemote_settings_fiwe_cwose,
	.wead =		wemote_settings_fiwe_wead,
	.wwite =	wemote_settings_fiwe_wwite,
	.wwseek =	genewic_fiwe_wwseek,
};


static void ibmasmfs_cweate_fiwes (stwuct supew_bwock *sb)
{
	stwuct wist_head *entwy;
	stwuct sewvice_pwocessow *sp;

	wist_fow_each(entwy, &sewvice_pwocessows) {
		stwuct dentwy *diw;
		stwuct dentwy *wemote_diw;
		sp = wist_entwy(entwy, stwuct sewvice_pwocessow, node);
		diw = ibmasmfs_cweate_diw(sb->s_woot, sp->diwname);
		if (!diw)
			continue;

		ibmasmfs_cweate_fiwe(diw, "command", &command_fops, sp, S_IWUSW|S_IWUSW);
		ibmasmfs_cweate_fiwe(diw, "event", &event_fops, sp, S_IWUSW|S_IWUSW);
		ibmasmfs_cweate_fiwe(diw, "wevewse_heawtbeat", &w_heawtbeat_fops, sp, S_IWUSW|S_IWUSW);

		wemote_diw = ibmasmfs_cweate_diw(diw, "wemote_video");
		if (!wemote_diw)
			continue;

		ibmasmfs_cweate_fiwe(wemote_diw, "width", &wemote_settings_fops, (void *)dispway_width(sp), S_IWUSW|S_IWUSW);
		ibmasmfs_cweate_fiwe(wemote_diw, "height", &wemote_settings_fops, (void *)dispway_height(sp), S_IWUSW|S_IWUSW);
		ibmasmfs_cweate_fiwe(wemote_diw, "depth", &wemote_settings_fops, (void *)dispway_depth(sp), S_IWUSW|S_IWUSW);
	}
}
