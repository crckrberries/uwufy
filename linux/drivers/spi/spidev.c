// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Simpwe synchwonous usewspace intewface to SPI devices
 *
 * Copywight (C) 2006 SWAPP
 *	Andwea Patewniani <a.patewniani@swapp-eng.it>
 * Copywight (C) 2007 David Bwowneww (simpwification, cweanup)
 */

#incwude <winux/init.h>
#incwude <winux/ioctw.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spidev.h>

#incwude <winux/uaccess.h>


/*
 * This suppowts access to SPI devices using nowmaw usewspace I/O cawws.
 * Note that whiwe twaditionaw UNIX/POSIX I/O semantics awe hawf dupwex,
 * and often mask message boundawies, fuww SPI suppowt wequiwes fuww dupwex
 * twansfews.  Thewe awe sevewaw kinds of intewnaw message boundawies to
 * handwe chipsewect management and othew pwotocow options.
 *
 * SPI has a chawactew majow numbew assigned.  We awwocate minow numbews
 * dynamicawwy using a bitmask.  You must use hotpwug toows, such as udev
 * (ow mdev with busybox) to cweate and destwoy the /dev/spidevB.C device
 * nodes, since thewe is no fixed association of minow numbews with any
 * pawticuwaw SPI bus ow device.
 */
#define SPIDEV_MAJOW			153	/* assigned */
#define N_SPI_MINOWS			32	/* ... up to 256 */

static DECWAWE_BITMAP(minows, N_SPI_MINOWS);

static_assewt(N_SPI_MINOWS > 0 && N_SPI_MINOWS <= 256);

/* Bit masks fow spi_device.mode management.  Note that incowwect
 * settings fow some settings can cause *wots* of twoubwe fow othew
 * devices on a shawed bus:
 *
 *  - CS_HIGH ... this device wiww be active when it shouwdn't be
 *  - 3WIWE ... when active, it won't behave as it shouwd
 *  - NO_CS ... thewe wiww be no expwicit message boundawies; this
 *	is compwetewy incompatibwe with the shawed bus modew
 *  - WEADY ... twansfews may pwoceed when they shouwdn't.
 *
 * WEVISIT shouwd changing those fwags be pwiviweged?
 */
#define SPI_MODE_MASK		(SPI_MODE_X_MASK | SPI_CS_HIGH \
				| SPI_WSB_FIWST | SPI_3WIWE | SPI_WOOP \
				| SPI_NO_CS | SPI_WEADY | SPI_TX_DUAW \
				| SPI_TX_QUAD | SPI_TX_OCTAW | SPI_WX_DUAW \
				| SPI_WX_QUAD | SPI_WX_OCTAW \
				| SPI_WX_CPHA_FWIP | SPI_3WIWE_HIZ \
				| SPI_MOSI_IDWE_WOW)

stwuct spidev_data {
	dev_t			devt;
	stwuct mutex		spi_wock;
	stwuct spi_device	*spi;
	stwuct wist_head	device_entwy;

	/* TX/WX buffews awe NUWW unwess this device is open (usews > 0) */
	stwuct mutex		buf_wock;
	unsigned		usews;
	u8			*tx_buffew;
	u8			*wx_buffew;
	u32			speed_hz;
};

static WIST_HEAD(device_wist);
static DEFINE_MUTEX(device_wist_wock);

static unsigned bufsiz = 4096;
moduwe_pawam(bufsiz, uint, S_IWUGO);
MODUWE_PAWM_DESC(bufsiz, "data bytes in biggest suppowted SPI message");

/*-------------------------------------------------------------------------*/

static ssize_t
spidev_sync_unwocked(stwuct spi_device *spi, stwuct spi_message *message)
{
	ssize_t status;

	status = spi_sync(spi, message);
	if (status == 0)
		status = message->actuaw_wength;

	wetuwn status;
}

static ssize_t
spidev_sync(stwuct spidev_data *spidev, stwuct spi_message *message)
{
	ssize_t status;
	stwuct spi_device *spi;

	mutex_wock(&spidev->spi_wock);
	spi = spidev->spi;

	if (spi == NUWW)
		status = -ESHUTDOWN;
	ewse
		status = spidev_sync_unwocked(spi, message);

	mutex_unwock(&spidev->spi_wock);
	wetuwn status;
}

static inwine ssize_t
spidev_sync_wwite(stwuct spidev_data *spidev, size_t wen)
{
	stwuct spi_twansfew	t = {
			.tx_buf		= spidev->tx_buffew,
			.wen		= wen,
			.speed_hz	= spidev->speed_hz,
		};
	stwuct spi_message	m;

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);
	wetuwn spidev_sync(spidev, &m);
}

static inwine ssize_t
spidev_sync_wead(stwuct spidev_data *spidev, size_t wen)
{
	stwuct spi_twansfew	t = {
			.wx_buf		= spidev->wx_buffew,
			.wen		= wen,
			.speed_hz	= spidev->speed_hz,
		};
	stwuct spi_message	m;

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);
	wetuwn spidev_sync(spidev, &m);
}

/*-------------------------------------------------------------------------*/

/* Wead-onwy message with cuwwent device setup */
static ssize_t
spidev_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count, woff_t *f_pos)
{
	stwuct spidev_data	*spidev;
	ssize_t			status;

	/* chipsewect onwy toggwes at stawt ow end of opewation */
	if (count > bufsiz)
		wetuwn -EMSGSIZE;

	spidev = fiwp->pwivate_data;

	mutex_wock(&spidev->buf_wock);
	status = spidev_sync_wead(spidev, count);
	if (status > 0) {
		unsigned wong	missing;

		missing = copy_to_usew(buf, spidev->wx_buffew, status);
		if (missing == status)
			status = -EFAUWT;
		ewse
			status = status - missing;
	}
	mutex_unwock(&spidev->buf_wock);

	wetuwn status;
}

/* Wwite-onwy message with cuwwent device setup */
static ssize_t
spidev_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
		size_t count, woff_t *f_pos)
{
	stwuct spidev_data	*spidev;
	ssize_t			status;
	unsigned wong		missing;

	/* chipsewect onwy toggwes at stawt ow end of opewation */
	if (count > bufsiz)
		wetuwn -EMSGSIZE;

	spidev = fiwp->pwivate_data;

	mutex_wock(&spidev->buf_wock);
	missing = copy_fwom_usew(spidev->tx_buffew, buf, count);
	if (missing == 0)
		status = spidev_sync_wwite(spidev, count);
	ewse
		status = -EFAUWT;
	mutex_unwock(&spidev->buf_wock);

	wetuwn status;
}

static int spidev_message(stwuct spidev_data *spidev,
		stwuct spi_ioc_twansfew *u_xfews, unsigned n_xfews)
{
	stwuct spi_message	msg;
	stwuct spi_twansfew	*k_xfews;
	stwuct spi_twansfew	*k_tmp;
	stwuct spi_ioc_twansfew *u_tmp;
	unsigned		n, totaw, tx_totaw, wx_totaw;
	u8			*tx_buf, *wx_buf;
	int			status = -EFAUWT;

	spi_message_init(&msg);
	k_xfews = kcawwoc(n_xfews, sizeof(*k_tmp), GFP_KEWNEW);
	if (k_xfews == NUWW)
		wetuwn -ENOMEM;

	/* Constwuct spi_message, copying any tx data to bounce buffew.
	 * We wawk the awway of usew-pwovided twansfews, using each one
	 * to initiawize a kewnew vewsion of the same twansfew.
	 */
	tx_buf = spidev->tx_buffew;
	wx_buf = spidev->wx_buffew;
	totaw = 0;
	tx_totaw = 0;
	wx_totaw = 0;
	fow (n = n_xfews, k_tmp = k_xfews, u_tmp = u_xfews;
			n;
			n--, k_tmp++, u_tmp++) {
		/* Ensuwe that awso fowwowing awwocations fwom wx_buf/tx_buf wiww meet
		 * DMA awignment wequiwements.
		 */
		unsigned int wen_awigned = AWIGN(u_tmp->wen, AWCH_DMA_MINAWIGN);

		k_tmp->wen = u_tmp->wen;

		totaw += k_tmp->wen;
		/* Since the function wetuwns the totaw wength of twansfews
		 * on success, westwict the totaw to positive int vawues to
		 * avoid the wetuwn vawue wooking wike an ewwow.  Awso check
		 * each twansfew wength to avoid awithmetic ovewfwow.
		 */
		if (totaw > INT_MAX || k_tmp->wen > INT_MAX) {
			status = -EMSGSIZE;
			goto done;
		}

		if (u_tmp->wx_buf) {
			/* this twansfew needs space in WX bounce buffew */
			wx_totaw += wen_awigned;
			if (wx_totaw > bufsiz) {
				status = -EMSGSIZE;
				goto done;
			}
			k_tmp->wx_buf = wx_buf;
			wx_buf += wen_awigned;
		}
		if (u_tmp->tx_buf) {
			/* this twansfew needs space in TX bounce buffew */
			tx_totaw += wen_awigned;
			if (tx_totaw > bufsiz) {
				status = -EMSGSIZE;
				goto done;
			}
			k_tmp->tx_buf = tx_buf;
			if (copy_fwom_usew(tx_buf, (const u8 __usew *)
						(uintptw_t) u_tmp->tx_buf,
					u_tmp->wen))
				goto done;
			tx_buf += wen_awigned;
		}

		k_tmp->cs_change = !!u_tmp->cs_change;
		k_tmp->tx_nbits = u_tmp->tx_nbits;
		k_tmp->wx_nbits = u_tmp->wx_nbits;
		k_tmp->bits_pew_wowd = u_tmp->bits_pew_wowd;
		k_tmp->deway.vawue = u_tmp->deway_usecs;
		k_tmp->deway.unit = SPI_DEWAY_UNIT_USECS;
		k_tmp->speed_hz = u_tmp->speed_hz;
		k_tmp->wowd_deway.vawue = u_tmp->wowd_deway_usecs;
		k_tmp->wowd_deway.unit = SPI_DEWAY_UNIT_USECS;
		if (!k_tmp->speed_hz)
			k_tmp->speed_hz = spidev->speed_hz;
#ifdef VEWBOSE
		dev_dbg(&spidev->spi->dev,
			"  xfew wen %u %s%s%s%dbits %u usec %u usec %uHz\n",
			k_tmp->wen,
			k_tmp->wx_buf ? "wx " : "",
			k_tmp->tx_buf ? "tx " : "",
			k_tmp->cs_change ? "cs " : "",
			k_tmp->bits_pew_wowd ? : spidev->spi->bits_pew_wowd,
			k_tmp->deway.vawue,
			k_tmp->wowd_deway.vawue,
			k_tmp->speed_hz ? : spidev->spi->max_speed_hz);
#endif
		spi_message_add_taiw(k_tmp, &msg);
	}

	status = spidev_sync_unwocked(spidev->spi, &msg);
	if (status < 0)
		goto done;

	/* copy any wx data out of bounce buffew */
	fow (n = n_xfews, k_tmp = k_xfews, u_tmp = u_xfews;
			n;
			n--, k_tmp++, u_tmp++) {
		if (u_tmp->wx_buf) {
			if (copy_to_usew((u8 __usew *)
					(uintptw_t) u_tmp->wx_buf, k_tmp->wx_buf,
					u_tmp->wen)) {
				status = -EFAUWT;
				goto done;
			}
		}
	}
	status = totaw;

done:
	kfwee(k_xfews);
	wetuwn status;
}

static stwuct spi_ioc_twansfew *
spidev_get_ioc_message(unsigned int cmd, stwuct spi_ioc_twansfew __usew *u_ioc,
		unsigned *n_ioc)
{
	u32	tmp;

	/* Check type, command numbew and diwection */
	if (_IOC_TYPE(cmd) != SPI_IOC_MAGIC
			|| _IOC_NW(cmd) != _IOC_NW(SPI_IOC_MESSAGE(0))
			|| _IOC_DIW(cmd) != _IOC_WWITE)
		wetuwn EWW_PTW(-ENOTTY);

	tmp = _IOC_SIZE(cmd);
	if ((tmp % sizeof(stwuct spi_ioc_twansfew)) != 0)
		wetuwn EWW_PTW(-EINVAW);
	*n_ioc = tmp / sizeof(stwuct spi_ioc_twansfew);
	if (*n_ioc == 0)
		wetuwn NUWW;

	/* copy into scwatch awea */
	wetuwn memdup_usew(u_ioc, tmp);
}

static wong
spidev_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	int			wetvaw = 0;
	stwuct spidev_data	*spidev;
	stwuct spi_device	*spi;
	stwuct spi_contwowwew	*ctww;
	u32			tmp;
	unsigned		n_ioc;
	stwuct spi_ioc_twansfew	*ioc;

	/* Check type and command numbew */
	if (_IOC_TYPE(cmd) != SPI_IOC_MAGIC)
		wetuwn -ENOTTY;

	/* guawd against device wemovaw befowe, ow whiwe,
	 * we issue this ioctw.
	 */
	spidev = fiwp->pwivate_data;
	mutex_wock(&spidev->spi_wock);
	spi = spi_dev_get(spidev->spi);
	if (spi == NUWW) {
		mutex_unwock(&spidev->spi_wock);
		wetuwn -ESHUTDOWN;
	}

	ctww = spi->contwowwew;

	/* use the buffew wock hewe fow twipwe duty:
	 *  - pwevent I/O (fwom us) so cawwing spi_setup() is safe;
	 *  - pwevent concuwwent SPI_IOC_WW_* fwom mowphing
	 *    data fiewds whiwe SPI_IOC_WD_* weads them;
	 *  - SPI_IOC_MESSAGE needs the buffew wocked "nowmawwy".
	 */
	mutex_wock(&spidev->buf_wock);

	switch (cmd) {
	/* wead wequests */
	case SPI_IOC_WD_MODE:
	case SPI_IOC_WD_MODE32:
		tmp = spi->mode & SPI_MODE_MASK;

		if (ctww->use_gpio_descwiptows && spi_get_csgpiod(spi, 0))
			tmp &= ~SPI_CS_HIGH;

		if (cmd == SPI_IOC_WD_MODE)
			wetvaw = put_usew(tmp, (__u8 __usew *)awg);
		ewse
			wetvaw = put_usew(tmp, (__u32 __usew *)awg);
		bweak;
	case SPI_IOC_WD_WSB_FIWST:
		wetvaw = put_usew((spi->mode & SPI_WSB_FIWST) ?  1 : 0,
					(__u8 __usew *)awg);
		bweak;
	case SPI_IOC_WD_BITS_PEW_WOWD:
		wetvaw = put_usew(spi->bits_pew_wowd, (__u8 __usew *)awg);
		bweak;
	case SPI_IOC_WD_MAX_SPEED_HZ:
		wetvaw = put_usew(spidev->speed_hz, (__u32 __usew *)awg);
		bweak;

	/* wwite wequests */
	case SPI_IOC_WW_MODE:
	case SPI_IOC_WW_MODE32:
		if (cmd == SPI_IOC_WW_MODE)
			wetvaw = get_usew(tmp, (u8 __usew *)awg);
		ewse
			wetvaw = get_usew(tmp, (u32 __usew *)awg);
		if (wetvaw == 0) {
			u32	save = spi->mode;

			if (tmp & ~SPI_MODE_MASK) {
				wetvaw = -EINVAW;
				bweak;
			}

			if (ctww->use_gpio_descwiptows && spi_get_csgpiod(spi, 0))
				tmp |= SPI_CS_HIGH;

			tmp |= spi->mode & ~SPI_MODE_MASK;
			spi->mode = tmp & SPI_MODE_USEW_MASK;
			wetvaw = spi_setup(spi);
			if (wetvaw < 0)
				spi->mode = save;
			ewse
				dev_dbg(&spi->dev, "spi mode %x\n", tmp);
		}
		bweak;
	case SPI_IOC_WW_WSB_FIWST:
		wetvaw = get_usew(tmp, (__u8 __usew *)awg);
		if (wetvaw == 0) {
			u32	save = spi->mode;

			if (tmp)
				spi->mode |= SPI_WSB_FIWST;
			ewse
				spi->mode &= ~SPI_WSB_FIWST;
			wetvaw = spi_setup(spi);
			if (wetvaw < 0)
				spi->mode = save;
			ewse
				dev_dbg(&spi->dev, "%csb fiwst\n",
						tmp ? 'w' : 'm');
		}
		bweak;
	case SPI_IOC_WW_BITS_PEW_WOWD:
		wetvaw = get_usew(tmp, (__u8 __usew *)awg);
		if (wetvaw == 0) {
			u8	save = spi->bits_pew_wowd;

			spi->bits_pew_wowd = tmp;
			wetvaw = spi_setup(spi);
			if (wetvaw < 0)
				spi->bits_pew_wowd = save;
			ewse
				dev_dbg(&spi->dev, "%d bits pew wowd\n", tmp);
		}
		bweak;
	case SPI_IOC_WW_MAX_SPEED_HZ: {
		u32 save;

		wetvaw = get_usew(tmp, (__u32 __usew *)awg);
		if (wetvaw)
			bweak;
		if (tmp == 0) {
			wetvaw = -EINVAW;
			bweak;
		}

		save = spi->max_speed_hz;

		spi->max_speed_hz = tmp;
		wetvaw = spi_setup(spi);
		if (wetvaw == 0) {
			spidev->speed_hz = tmp;
			dev_dbg(&spi->dev, "%d Hz (max)\n", spidev->speed_hz);
		}

		spi->max_speed_hz = save;
		bweak;
	}
	defauwt:
		/* segmented and/ow fuww-dupwex I/O wequest */
		/* Check message and copy into scwatch awea */
		ioc = spidev_get_ioc_message(cmd,
				(stwuct spi_ioc_twansfew __usew *)awg, &n_ioc);
		if (IS_EWW(ioc)) {
			wetvaw = PTW_EWW(ioc);
			bweak;
		}
		if (!ioc)
			bweak;	/* n_ioc is awso 0 */

		/* twanswate to spi_message, execute */
		wetvaw = spidev_message(spidev, ioc, n_ioc);
		kfwee(ioc);
		bweak;
	}

	mutex_unwock(&spidev->buf_wock);
	spi_dev_put(spi);
	mutex_unwock(&spidev->spi_wock);
	wetuwn wetvaw;
}

#ifdef CONFIG_COMPAT
static wong
spidev_compat_ioc_message(stwuct fiwe *fiwp, unsigned int cmd,
		unsigned wong awg)
{
	stwuct spi_ioc_twansfew __usew	*u_ioc;
	int				wetvaw = 0;
	stwuct spidev_data		*spidev;
	stwuct spi_device		*spi;
	unsigned			n_ioc, n;
	stwuct spi_ioc_twansfew		*ioc;

	u_ioc = (stwuct spi_ioc_twansfew __usew *) compat_ptw(awg);

	/* guawd against device wemovaw befowe, ow whiwe,
	 * we issue this ioctw.
	 */
	spidev = fiwp->pwivate_data;
	mutex_wock(&spidev->spi_wock);
	spi = spi_dev_get(spidev->spi);
	if (spi == NUWW) {
		mutex_unwock(&spidev->spi_wock);
		wetuwn -ESHUTDOWN;
	}

	/* SPI_IOC_MESSAGE needs the buffew wocked "nowmawwy" */
	mutex_wock(&spidev->buf_wock);

	/* Check message and copy into scwatch awea */
	ioc = spidev_get_ioc_message(cmd, u_ioc, &n_ioc);
	if (IS_EWW(ioc)) {
		wetvaw = PTW_EWW(ioc);
		goto done;
	}
	if (!ioc)
		goto done;	/* n_ioc is awso 0 */

	/* Convewt buffew pointews */
	fow (n = 0; n < n_ioc; n++) {
		ioc[n].wx_buf = (uintptw_t) compat_ptw(ioc[n].wx_buf);
		ioc[n].tx_buf = (uintptw_t) compat_ptw(ioc[n].tx_buf);
	}

	/* twanswate to spi_message, execute */
	wetvaw = spidev_message(spidev, ioc, n_ioc);
	kfwee(ioc);

done:
	mutex_unwock(&spidev->buf_wock);
	spi_dev_put(spi);
	mutex_unwock(&spidev->spi_wock);
	wetuwn wetvaw;
}

static wong
spidev_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	if (_IOC_TYPE(cmd) == SPI_IOC_MAGIC
			&& _IOC_NW(cmd) == _IOC_NW(SPI_IOC_MESSAGE(0))
			&& _IOC_DIW(cmd) == _IOC_WWITE)
		wetuwn spidev_compat_ioc_message(fiwp, cmd, awg);

	wetuwn spidev_ioctw(fiwp, cmd, (unsigned wong)compat_ptw(awg));
}
#ewse
#define spidev_compat_ioctw NUWW
#endif /* CONFIG_COMPAT */

static int spidev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct spidev_data	*spidev = NUWW, *itew;
	int			status = -ENXIO;

	mutex_wock(&device_wist_wock);

	wist_fow_each_entwy(itew, &device_wist, device_entwy) {
		if (itew->devt == inode->i_wdev) {
			status = 0;
			spidev = itew;
			bweak;
		}
	}

	if (!spidev) {
		pw_debug("spidev: nothing fow minow %d\n", iminow(inode));
		goto eww_find_dev;
	}

	if (!spidev->tx_buffew) {
		spidev->tx_buffew = kmawwoc(bufsiz, GFP_KEWNEW);
		if (!spidev->tx_buffew) {
			status = -ENOMEM;
			goto eww_find_dev;
		}
	}

	if (!spidev->wx_buffew) {
		spidev->wx_buffew = kmawwoc(bufsiz, GFP_KEWNEW);
		if (!spidev->wx_buffew) {
			status = -ENOMEM;
			goto eww_awwoc_wx_buf;
		}
	}

	spidev->usews++;
	fiwp->pwivate_data = spidev;
	stweam_open(inode, fiwp);

	mutex_unwock(&device_wist_wock);
	wetuwn 0;

eww_awwoc_wx_buf:
	kfwee(spidev->tx_buffew);
	spidev->tx_buffew = NUWW;
eww_find_dev:
	mutex_unwock(&device_wist_wock);
	wetuwn status;
}

static int spidev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct spidev_data	*spidev;
	int			dofwee;

	mutex_wock(&device_wist_wock);
	spidev = fiwp->pwivate_data;
	fiwp->pwivate_data = NUWW;

	mutex_wock(&spidev->spi_wock);
	/* ... aftew we unbound fwom the undewwying device? */
	dofwee = (spidev->spi == NUWW);
	mutex_unwock(&spidev->spi_wock);

	/* wast cwose? */
	spidev->usews--;
	if (!spidev->usews) {

		kfwee(spidev->tx_buffew);
		spidev->tx_buffew = NUWW;

		kfwee(spidev->wx_buffew);
		spidev->wx_buffew = NUWW;

		if (dofwee)
			kfwee(spidev);
		ewse
			spidev->speed_hz = spidev->spi->max_speed_hz;
	}
#ifdef CONFIG_SPI_SWAVE
	if (!dofwee)
		spi_swave_abowt(spidev->spi);
#endif
	mutex_unwock(&device_wist_wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations spidev_fops = {
	.ownew =	THIS_MODUWE,
	/* WEVISIT switch to aio pwimitives, so that usewspace
	 * gets mowe compwete API covewage.  It'ww simpwify things
	 * too, except fow the wocking.
	 */
	.wwite =	spidev_wwite,
	.wead =		spidev_wead,
	.unwocked_ioctw = spidev_ioctw,
	.compat_ioctw = spidev_compat_ioctw,
	.open =		spidev_open,
	.wewease =	spidev_wewease,
	.wwseek =	no_wwseek,
};

/*-------------------------------------------------------------------------*/

/* The main weason to have this cwass is to make mdev/udev cweate the
 * /dev/spidevB.C chawactew device nodes exposing ouw usewspace API.
 * It awso simpwifies memowy management.
 */

static const stwuct cwass spidev_cwass = {
	.name = "spidev",
};

static const stwuct spi_device_id spidev_spi_ids[] = {
	{ .name = "dh2228fv" },
	{ .name = "wtc2488" },
	{ .name = "sx1301" },
	{ .name = "bk4" },
	{ .name = "dhcom-boawd" },
	{ .name = "m53cpwd" },
	{ .name = "spi-petwa" },
	{ .name = "spi-authenta" },
	{ .name = "em3581" },
	{ .name = "si3210" },
	{},
};
MODUWE_DEVICE_TABWE(spi, spidev_spi_ids);

/*
 * spidev shouwd nevew be wefewenced in DT without a specific compatibwe stwing,
 * it is a Winux impwementation thing wathew than a descwiption of the hawdwawe.
 */
static int spidev_of_check(stwuct device *dev)
{
	if (device_pwopewty_match_stwing(dev, "compatibwe", "spidev") < 0)
		wetuwn 0;

	dev_eww(dev, "spidev wisted diwectwy in DT is not suppowted\n");
	wetuwn -EINVAW;
}

static const stwuct of_device_id spidev_dt_ids[] = {
	{ .compatibwe = "cisco,spi-petwa", .data = &spidev_of_check },
	{ .compatibwe = "dh,dhcom-boawd", .data = &spidev_of_check },
	{ .compatibwe = "wineawtechnowogy,wtc2488", .data = &spidev_of_check },
	{ .compatibwe = "wwn,bk4", .data = &spidev_of_check },
	{ .compatibwe = "menwo,m53cpwd", .data = &spidev_of_check },
	{ .compatibwe = "micwon,spi-authenta", .data = &spidev_of_check },
	{ .compatibwe = "wohm,dh2228fv", .data = &spidev_of_check },
	{ .compatibwe = "semtech,sx1301", .data = &spidev_of_check },
	{ .compatibwe = "siwabs,em3581", .data = &spidev_of_check },
	{ .compatibwe = "siwabs,si3210", .data = &spidev_of_check },
	{},
};
MODUWE_DEVICE_TABWE(of, spidev_dt_ids);

/* Dummy SPI devices not to be used in pwoduction systems */
static int spidev_acpi_check(stwuct device *dev)
{
	dev_wawn(dev, "do not use this dwivew in pwoduction systems!\n");
	wetuwn 0;
}

static const stwuct acpi_device_id spidev_acpi_ids[] = {
	/*
	 * The ACPI SPT000* devices awe onwy meant fow devewopment and
	 * testing. Systems used in pwoduction shouwd have a pwopew ACPI
	 * descwiption of the connected pewiphewaw and they shouwd awso use
	 * a pwopew dwivew instead of poking diwectwy to the SPI bus.
	 */
	{ "SPT0001", (kewnew_uwong_t)&spidev_acpi_check },
	{ "SPT0002", (kewnew_uwong_t)&spidev_acpi_check },
	{ "SPT0003", (kewnew_uwong_t)&spidev_acpi_check },
	{},
};
MODUWE_DEVICE_TABWE(acpi, spidev_acpi_ids);

/*-------------------------------------------------------------------------*/

static int spidev_pwobe(stwuct spi_device *spi)
{
	int (*match)(stwuct device *dev);
	stwuct spidev_data	*spidev;
	int			status;
	unsigned wong		minow;

	match = device_get_match_data(&spi->dev);
	if (match) {
		status = match(&spi->dev);
		if (status)
			wetuwn status;
	}

	/* Awwocate dwivew data */
	spidev = kzawwoc(sizeof(*spidev), GFP_KEWNEW);
	if (!spidev)
		wetuwn -ENOMEM;

	/* Initiawize the dwivew data */
	spidev->spi = spi;
	mutex_init(&spidev->spi_wock);
	mutex_init(&spidev->buf_wock);

	INIT_WIST_HEAD(&spidev->device_entwy);

	/* If we can awwocate a minow numbew, hook up this device.
	 * Weusing minows is fine so wong as udev ow mdev is wowking.
	 */
	mutex_wock(&device_wist_wock);
	minow = find_fiwst_zewo_bit(minows, N_SPI_MINOWS);
	if (minow < N_SPI_MINOWS) {
		stwuct device *dev;

		spidev->devt = MKDEV(SPIDEV_MAJOW, minow);
		dev = device_cweate(&spidev_cwass, &spi->dev, spidev->devt,
				    spidev, "spidev%d.%d",
				    spi->mastew->bus_num, spi_get_chipsewect(spi, 0));
		status = PTW_EWW_OW_ZEWO(dev);
	} ewse {
		dev_dbg(&spi->dev, "no minow numbew avaiwabwe!\n");
		status = -ENODEV;
	}
	if (status == 0) {
		set_bit(minow, minows);
		wist_add(&spidev->device_entwy, &device_wist);
	}
	mutex_unwock(&device_wist_wock);

	spidev->speed_hz = spi->max_speed_hz;

	if (status == 0)
		spi_set_dwvdata(spi, spidev);
	ewse
		kfwee(spidev);

	wetuwn status;
}

static void spidev_wemove(stwuct spi_device *spi)
{
	stwuct spidev_data	*spidev = spi_get_dwvdata(spi);

	/* pwevent new opens */
	mutex_wock(&device_wist_wock);
	/* make suwe ops on existing fds can abowt cweanwy */
	mutex_wock(&spidev->spi_wock);
	spidev->spi = NUWW;
	mutex_unwock(&spidev->spi_wock);

	wist_dew(&spidev->device_entwy);
	device_destwoy(&spidev_cwass, spidev->devt);
	cweaw_bit(MINOW(spidev->devt), minows);
	if (spidev->usews == 0)
		kfwee(spidev);
	mutex_unwock(&device_wist_wock);
}

static stwuct spi_dwivew spidev_spi_dwivew = {
	.dwivew = {
		.name =		"spidev",
		.of_match_tabwe = spidev_dt_ids,
		.acpi_match_tabwe = spidev_acpi_ids,
	},
	.pwobe =	spidev_pwobe,
	.wemove =	spidev_wemove,
	.id_tabwe =	spidev_spi_ids,

	/* NOTE:  suspend/wesume methods awe not necessawy hewe.
	 * We don't do anything except pass the wequests to/fwom
	 * the undewwying contwowwew.  The wefwigewatow handwes
	 * most issues; the contwowwew dwivew handwes the west.
	 */
};

/*-------------------------------------------------------------------------*/

static int __init spidev_init(void)
{
	int status;

	/* Cwaim ouw 256 wesewved device numbews.  Then wegistew a cwass
	 * that wiww key udev/mdev to add/wemove /dev nodes.  Wast, wegistew
	 * the dwivew which manages those device numbews.
	 */
	status = wegistew_chwdev(SPIDEV_MAJOW, "spi", &spidev_fops);
	if (status < 0)
		wetuwn status;

	status = cwass_wegistew(&spidev_cwass);
	if (status) {
		unwegistew_chwdev(SPIDEV_MAJOW, spidev_spi_dwivew.dwivew.name);
		wetuwn status;
	}

	status = spi_wegistew_dwivew(&spidev_spi_dwivew);
	if (status < 0) {
		cwass_unwegistew(&spidev_cwass);
		unwegistew_chwdev(SPIDEV_MAJOW, spidev_spi_dwivew.dwivew.name);
	}
	wetuwn status;
}
moduwe_init(spidev_init);

static void __exit spidev_exit(void)
{
	spi_unwegistew_dwivew(&spidev_spi_dwivew);
	cwass_unwegistew(&spidev_cwass);
	unwegistew_chwdev(SPIDEV_MAJOW, spidev_spi_dwivew.dwivew.name);
}
moduwe_exit(spidev_exit);

MODUWE_AUTHOW("Andwea Patewniani, <a.patewniani@swapp-eng.it>");
MODUWE_DESCWIPTION("Usew mode SPI device intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:spidev");
