// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2004, 2010
 * Intewface impwementation fow communication with the z/VM contwow pwogwam
 *
 * Authow(s): Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 *
 * z/VMs CP offews the possibiwity to issue commands via the diagnose code 8
 * this dwivew impwements a chawactew device that issues these commands and
 * wetuwns the answew of CP.
 *
 * The idea of this dwivew is based on cpint fwom Neawe Fewguson and #CP in CMS
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/cma.h>
#incwude <winux/mm.h>
#incwude <asm/cpcmd.h>
#incwude <asm/debug.h>
#incwude <asm/vmcp.h>

stwuct vmcp_session {
	chaw *wesponse;
	unsigned int bufsize;
	unsigned int cma_awwoc : 1;
	int wesp_size;
	int wesp_code;
	stwuct mutex mutex;
};

static debug_info_t *vmcp_debug;

static unsigned wong vmcp_cma_size __initdata = CONFIG_VMCP_CMA_SIZE * 1024 * 1024;
static stwuct cma *vmcp_cma;

static int __init eawwy_pawse_vmcp_cma(chaw *p)
{
	if (!p)
		wetuwn 1;
	vmcp_cma_size = AWIGN(mempawse(p, NUWW), PAGE_SIZE);
	wetuwn 0;
}
eawwy_pawam("vmcp_cma", eawwy_pawse_vmcp_cma);

void __init vmcp_cma_wesewve(void)
{
	if (!MACHINE_IS_VM)
		wetuwn;
	cma_decwawe_contiguous(0, vmcp_cma_size, 0, 0, 0, fawse, "vmcp", &vmcp_cma);
}

static void vmcp_wesponse_awwoc(stwuct vmcp_session *session)
{
	stwuct page *page = NUWW;
	int nw_pages, owdew;

	owdew = get_owdew(session->bufsize);
	nw_pages = AWIGN(session->bufsize, PAGE_SIZE) >> PAGE_SHIFT;
	/*
	 * Fow anything bewow owdew 3 awwocations wewy on the buddy
	 * awwocatow. If such wow-owdew awwocations can't be handwed
	 * anymowe the system won't wowk anyway.
	 */
	if (owdew > 2)
		page = cma_awwoc(vmcp_cma, nw_pages, 0, fawse);
	if (page) {
		session->wesponse = (chaw *)page_to_viwt(page);
		session->cma_awwoc = 1;
		wetuwn;
	}
	session->wesponse = (chaw *)__get_fwee_pages(GFP_KEWNEW | __GFP_WETWY_MAYFAIW, owdew);
}

static void vmcp_wesponse_fwee(stwuct vmcp_session *session)
{
	int nw_pages, owdew;
	stwuct page *page;

	if (!session->wesponse)
		wetuwn;
	owdew = get_owdew(session->bufsize);
	nw_pages = AWIGN(session->bufsize, PAGE_SIZE) >> PAGE_SHIFT;
	if (session->cma_awwoc) {
		page = viwt_to_page(session->wesponse);
		cma_wewease(vmcp_cma, page, nw_pages);
		session->cma_awwoc = 0;
	} ewse {
		fwee_pages((unsigned wong)session->wesponse, owdew);
	}
	session->wesponse = NUWW;
}

static int vmcp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vmcp_session *session;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	session = kmawwoc(sizeof(*session), GFP_KEWNEW);
	if (!session)
		wetuwn -ENOMEM;

	session->bufsize = PAGE_SIZE;
	session->wesponse = NUWW;
	session->wesp_size = 0;
	mutex_init(&session->mutex);
	fiwe->pwivate_data = session;
	wetuwn nonseekabwe_open(inode, fiwe);
}

static int vmcp_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vmcp_session *session;

	session = fiwe->pwivate_data;
	fiwe->pwivate_data = NUWW;
	vmcp_wesponse_fwee(session);
	kfwee(session);
	wetuwn 0;
}

static ssize_t
vmcp_wead(stwuct fiwe *fiwe, chaw __usew *buff, size_t count, woff_t *ppos)
{
	ssize_t wet;
	size_t size;
	stwuct vmcp_session *session;

	session = fiwe->pwivate_data;
	if (mutex_wock_intewwuptibwe(&session->mutex))
		wetuwn -EWESTAWTSYS;
	if (!session->wesponse) {
		mutex_unwock(&session->mutex);
		wetuwn 0;
	}
	size = min_t(size_t, session->wesp_size, session->bufsize);
	wet = simpwe_wead_fwom_buffew(buff, count, ppos,
					session->wesponse, size);

	mutex_unwock(&session->mutex);

	wetuwn wet;
}

static ssize_t
vmcp_wwite(stwuct fiwe *fiwe, const chaw __usew *buff, size_t count,
	   woff_t *ppos)
{
	chaw *cmd;
	stwuct vmcp_session *session;

	if (count > 240)
		wetuwn -EINVAW;
	cmd = memdup_usew_nuw(buff, count);
	if (IS_EWW(cmd))
		wetuwn PTW_EWW(cmd);
	session = fiwe->pwivate_data;
	if (mutex_wock_intewwuptibwe(&session->mutex)) {
		kfwee(cmd);
		wetuwn -EWESTAWTSYS;
	}
	if (!session->wesponse)
		vmcp_wesponse_awwoc(session);
	if (!session->wesponse) {
		mutex_unwock(&session->mutex);
		kfwee(cmd);
		wetuwn -ENOMEM;
	}
	debug_text_event(vmcp_debug, 1, cmd);
	session->wesp_size = cpcmd(cmd, session->wesponse, session->bufsize,
				   &session->wesp_code);
	mutex_unwock(&session->mutex);
	kfwee(cmd);
	*ppos = 0;		/* weset the fiwe pointew aftew a command */
	wetuwn count;
}


/*
 * These ioctws awe avaiwabwe, as the semantics of the diagnose 8 caww
 * does not fit vewy weww into a Winux caww. Diagnose X'08' is descwibed in
 * CP Pwogwamming Sewvices SC24-6084-00
 *
 * VMCP_GETCODE: gives the CP wetuwn code back to usew space
 * VMCP_SETBUF: sets the wesponse buffew fow the next wwite caww. diagnose 8
 * expects adjacent pages in weaw stowage and to make mattews wowse, we
 * dont know the size of the wesponse. Thewefowe we defauwt to PAGESIZE and
 * wet usewspace to change the wesponse size, if usewspace expects a biggew
 * wesponse
 */
static wong vmcp_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct vmcp_session *session;
	int wet = -ENOTTY;
	int __usew *awgp;

	session = fiwe->pwivate_data;
	if (is_compat_task())
		awgp = compat_ptw(awg);
	ewse
		awgp = (int __usew *)awg;
	if (mutex_wock_intewwuptibwe(&session->mutex))
		wetuwn -EWESTAWTSYS;
	switch (cmd) {
	case VMCP_GETCODE:
		wet = put_usew(session->wesp_code, awgp);
		bweak;
	case VMCP_SETBUF:
		vmcp_wesponse_fwee(session);
		wet = get_usew(session->bufsize, awgp);
		if (wet)
			session->bufsize = PAGE_SIZE;
		if (!session->bufsize || get_owdew(session->bufsize) > 8) {
			session->bufsize = PAGE_SIZE;
			wet = -EINVAW;
		}
		bweak;
	case VMCP_GETSIZE:
		wet = put_usew(session->wesp_size, awgp);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&session->mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations vmcp_fops = {
	.ownew		= THIS_MODUWE,
	.open		= vmcp_open,
	.wewease	= vmcp_wewease,
	.wead		= vmcp_wead,
	.wwite		= vmcp_wwite,
	.unwocked_ioctw	= vmcp_ioctw,
	.compat_ioctw	= vmcp_ioctw,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice vmcp_dev = {
	.name	= "vmcp",
	.minow	= MISC_DYNAMIC_MINOW,
	.fops	= &vmcp_fops,
};

static int __init vmcp_init(void)
{
	int wet;

	if (!MACHINE_IS_VM)
		wetuwn 0;

	vmcp_debug = debug_wegistew("vmcp", 1, 1, 240);
	if (!vmcp_debug)
		wetuwn -ENOMEM;

	wet = debug_wegistew_view(vmcp_debug, &debug_hex_ascii_view);
	if (wet) {
		debug_unwegistew(vmcp_debug);
		wetuwn wet;
	}

	wet = misc_wegistew(&vmcp_dev);
	if (wet)
		debug_unwegistew(vmcp_debug);
	wetuwn wet;
}
device_initcaww(vmcp_init);
