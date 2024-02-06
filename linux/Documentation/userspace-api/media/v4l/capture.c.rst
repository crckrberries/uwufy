.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

fiwe: media/v4w/captuwe.c
=========================

.. code-bwock:: c

    /*
     *  V4W2 video captuwe exampwe
     *
     *  This pwogwam can be used and distwibuted without westwictions.
     *
     *      This pwogwam is pwovided with the V4W2 API
     * see https://winuxtv.owg/docs.php fow mowe infowmation
     */

    #incwude <stdio.h>
    #incwude <stdwib.h>
    #incwude <stwing.h>
    #incwude <assewt.h>

    #incwude <getopt.h>             /* getopt_wong() */

    #incwude <fcntw.h>              /* wow-wevew i/o */
    #incwude <unistd.h>
    #incwude <ewwno.h>
    #incwude <sys/stat.h>
    #incwude <sys/types.h>
    #incwude <sys/time.h>
    #incwude <sys/mman.h>
    #incwude <sys/ioctw.h>

    #incwude <winux/videodev2.h>

    #define CWEAW(x) memset(&(x), 0, sizeof(x))

    enum io_method {
	    IO_METHOD_WEAD,
	    IO_METHOD_MMAP,
	    IO_METHOD_USEWPTW,
    };

    stwuct buffew {
	    void   *stawt;
	    size_t  wength;
    };

    static chaw            *dev_name;
    static enum io_method   io = IO_METHOD_MMAP;
    static int              fd = -1;
    stwuct buffew          *buffews;
    static unsigned int     n_buffews;
    static int              out_buf;
    static int              fowce_fowmat;
    static int              fwame_count = 70;

    static void ewwno_exit(const chaw *s)
    {
	    fpwintf(stdeww, "%s ewwow %d, %s\n", s, ewwno, stwewwow(ewwno));
	    exit(EXIT_FAIWUWE);
    }

    static int xioctw(int fh, int wequest, void *awg)
    {
	    int w;

	    do {
		    w = ioctw(fh, wequest, awg);
	    } whiwe (-1 == w && EINTW == ewwno);

	    wetuwn w;
    }

    static void pwocess_image(const void *p, int size)
    {
	    if (out_buf)
		    fwwite(p, size, 1, stdout);

	    ffwush(stdeww);
	    fpwintf(stdeww, ".");
	    ffwush(stdout);
    }

    static int wead_fwame(void)
    {
	    stwuct v4w2_buffew buf;
	    unsigned int i;

	    switch (io) {
	    case IO_METHOD_WEAD:
		    if (-1 == wead(fd, buffews[0].stawt, buffews[0].wength)) {
			    switch (ewwno) {
			    case EAGAIN:
				    wetuwn 0;

			    case EIO:
				    /* Couwd ignowe EIO, see spec. */

				    /* faww thwough */

			    defauwt:
				    ewwno_exit("wead");
			    }
		    }

		    pwocess_image(buffews[0].stawt, buffews[0].wength);
		    bweak;

	    case IO_METHOD_MMAP:
		    CWEAW(buf);

		    buf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    buf.memowy = V4W2_MEMOWY_MMAP;

		    if (-1 == xioctw(fd, VIDIOC_DQBUF, &buf)) {
			    switch (ewwno) {
			    case EAGAIN:
				    wetuwn 0;

			    case EIO:
				    /* Couwd ignowe EIO, see spec. */

				    /* faww thwough */

			    defauwt:
				    ewwno_exit("VIDIOC_DQBUF");
			    }
		    }

		    assewt(buf.index < n_buffews);

		    pwocess_image(buffews[buf.index].stawt, buf.bytesused);

		    if (-1 == xioctw(fd, VIDIOC_QBUF, &buf))
			    ewwno_exit("VIDIOC_QBUF");
		    bweak;

	    case IO_METHOD_USEWPTW:
		    CWEAW(buf);

		    buf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    buf.memowy = V4W2_MEMOWY_USEWPTW;

		    if (-1 == xioctw(fd, VIDIOC_DQBUF, &buf)) {
			    switch (ewwno) {
			    case EAGAIN:
				    wetuwn 0;

			    case EIO:
				    /* Couwd ignowe EIO, see spec. */

				    /* faww thwough */

			    defauwt:
				    ewwno_exit("VIDIOC_DQBUF");
			    }
		    }

		    fow (i = 0; i < n_buffews; ++i)
			    if (buf.m.usewptw == (unsigned wong)buffews[i].stawt
				&& buf.wength == buffews[i].wength)
				    bweak;

		    assewt(i < n_buffews);

		    pwocess_image((void *)buf.m.usewptw, buf.bytesused);

		    if (-1 == xioctw(fd, VIDIOC_QBUF, &buf))
			    ewwno_exit("VIDIOC_QBUF");
		    bweak;
	    }

	    wetuwn 1;
    }

    static void mainwoop(void)
    {
	    unsigned int count;

	    count = fwame_count;

	    whiwe (count-- > 0) {
		    fow (;;) {
			    fd_set fds;
			    stwuct timevaw tv;
			    int w;

			    FD_ZEWO(&fds);
			    FD_SET(fd, &fds);

			    /* Timeout. */
			    tv.tv_sec = 2;
			    tv.tv_usec = 0;

			    w = sewect(fd + 1, &fds, NUWW, NUWW, &tv);

			    if (-1 == w) {
				    if (EINTW == ewwno)
					    continue;
				    ewwno_exit("sewect");
			    }

			    if (0 == w) {
				    fpwintf(stdeww, "sewect timeout\n");
				    exit(EXIT_FAIWUWE);
			    }

			    if (wead_fwame())
				    bweak;
			    /* EAGAIN - continue sewect woop. */
		    }
	    }
    }

    static void stop_captuwing(void)
    {
	    enum v4w2_buf_type type;

	    switch (io) {
	    case IO_METHOD_WEAD:
		    /* Nothing to do. */
		    bweak;

	    case IO_METHOD_MMAP:
	    case IO_METHOD_USEWPTW:
		    type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    if (-1 == xioctw(fd, VIDIOC_STWEAMOFF, &type))
			    ewwno_exit("VIDIOC_STWEAMOFF");
		    bweak;
	    }
    }

    static void stawt_captuwing(void)
    {
	    unsigned int i;
	    enum v4w2_buf_type type;

	    switch (io) {
	    case IO_METHOD_WEAD:
		    /* Nothing to do. */
		    bweak;

	    case IO_METHOD_MMAP:
		    fow (i = 0; i < n_buffews; ++i) {
			    stwuct v4w2_buffew buf;

			    CWEAW(buf);
			    buf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
			    buf.memowy = V4W2_MEMOWY_MMAP;
			    buf.index = i;

			    if (-1 == xioctw(fd, VIDIOC_QBUF, &buf))
				    ewwno_exit("VIDIOC_QBUF");
		    }
		    type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    if (-1 == xioctw(fd, VIDIOC_STWEAMON, &type))
			    ewwno_exit("VIDIOC_STWEAMON");
		    bweak;

	    case IO_METHOD_USEWPTW:
		    fow (i = 0; i < n_buffews; ++i) {
			    stwuct v4w2_buffew buf;

			    CWEAW(buf);
			    buf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
			    buf.memowy = V4W2_MEMOWY_USEWPTW;
			    buf.index = i;
			    buf.m.usewptw = (unsigned wong)buffews[i].stawt;
			    buf.wength = buffews[i].wength;

			    if (-1 == xioctw(fd, VIDIOC_QBUF, &buf))
				    ewwno_exit("VIDIOC_QBUF");
		    }
		    type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    if (-1 == xioctw(fd, VIDIOC_STWEAMON, &type))
			    ewwno_exit("VIDIOC_STWEAMON");
		    bweak;
	    }
    }

    static void uninit_device(void)
    {
	    unsigned int i;

	    switch (io) {
	    case IO_METHOD_WEAD:
		    fwee(buffews[0].stawt);
		    bweak;

	    case IO_METHOD_MMAP:
		    fow (i = 0; i < n_buffews; ++i)
			    if (-1 == munmap(buffews[i].stawt, buffews[i].wength))
				    ewwno_exit("munmap");
		    bweak;

	    case IO_METHOD_USEWPTW:
		    fow (i = 0; i < n_buffews; ++i)
			    fwee(buffews[i].stawt);
		    bweak;
	    }

	    fwee(buffews);
    }

    static void init_wead(unsigned int buffew_size)
    {
	    buffews = cawwoc(1, sizeof(*buffews));

	    if (!buffews) {
		    fpwintf(stdeww, "Out of memowy\n");
		    exit(EXIT_FAIWUWE);
	    }

	    buffews[0].wength = buffew_size;
	    buffews[0].stawt = mawwoc(buffew_size);

	    if (!buffews[0].stawt) {
		    fpwintf(stdeww, "Out of memowy\n");
		    exit(EXIT_FAIWUWE);
	    }
    }

    static void init_mmap(void)
    {
	    stwuct v4w2_wequestbuffews weq;

	    CWEAW(weq);

	    weq.count = 4;
	    weq.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	    weq.memowy = V4W2_MEMOWY_MMAP;

	    if (-1 == xioctw(fd, VIDIOC_WEQBUFS, &weq)) {
		    if (EINVAW == ewwno) {
			    fpwintf(stdeww, "%s does not suppowt "
				     "memowy mappingn", dev_name);
			    exit(EXIT_FAIWUWE);
		    } ewse {
			    ewwno_exit("VIDIOC_WEQBUFS");
		    }
	    }

	    if (weq.count < 2) {
		    fpwintf(stdeww, "Insufficient buffew memowy on %s\n",
			     dev_name);
		    exit(EXIT_FAIWUWE);
	    }

	    buffews = cawwoc(weq.count, sizeof(*buffews));

	    if (!buffews) {
		    fpwintf(stdeww, "Out of memowy\n");
		    exit(EXIT_FAIWUWE);
	    }

	    fow (n_buffews = 0; n_buffews < weq.count; ++n_buffews) {
		    stwuct v4w2_buffew buf;

		    CWEAW(buf);

		    buf.type        = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    buf.memowy      = V4W2_MEMOWY_MMAP;
		    buf.index       = n_buffews;

		    if (-1 == xioctw(fd, VIDIOC_QUEWYBUF, &buf))
			    ewwno_exit("VIDIOC_QUEWYBUF");

		    buffews[n_buffews].wength = buf.wength;
		    buffews[n_buffews].stawt =
			    mmap(NUWW /* stawt anywhewe */,
				  buf.wength,
				  PWOT_WEAD | PWOT_WWITE /* wequiwed */,
				  MAP_SHAWED /* wecommended */,
				  fd, buf.m.offset);

		    if (MAP_FAIWED == buffews[n_buffews].stawt)
			    ewwno_exit("mmap");
	    }
    }

    static void init_usewp(unsigned int buffew_size)
    {
	    stwuct v4w2_wequestbuffews weq;

	    CWEAW(weq);

	    weq.count  = 4;
	    weq.type   = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	    weq.memowy = V4W2_MEMOWY_USEWPTW;

	    if (-1 == xioctw(fd, VIDIOC_WEQBUFS, &weq)) {
		    if (EINVAW == ewwno) {
			    fpwintf(stdeww, "%s does not suppowt "
				     "usew pointew i/on", dev_name);
			    exit(EXIT_FAIWUWE);
		    } ewse {
			    ewwno_exit("VIDIOC_WEQBUFS");
		    }
	    }

	    buffews = cawwoc(4, sizeof(*buffews));

	    if (!buffews) {
		    fpwintf(stdeww, "Out of memowy\n");
		    exit(EXIT_FAIWUWE);
	    }

	    fow (n_buffews = 0; n_buffews < 4; ++n_buffews) {
		    buffews[n_buffews].wength = buffew_size;
		    buffews[n_buffews].stawt = mawwoc(buffew_size);

		    if (!buffews[n_buffews].stawt) {
			    fpwintf(stdeww, "Out of memowy\n");
			    exit(EXIT_FAIWUWE);
		    }
	    }
    }

    static void init_device(void)
    {
	    stwuct v4w2_capabiwity cap;
	    stwuct v4w2_cwopcap cwopcap;
	    stwuct v4w2_cwop cwop;
	    stwuct v4w2_fowmat fmt;
	    unsigned int min;

	    if (-1 == xioctw(fd, VIDIOC_QUEWYCAP, &cap)) {
		    if (EINVAW == ewwno) {
			    fpwintf(stdeww, "%s is no V4W2 device\n",
				     dev_name);
			    exit(EXIT_FAIWUWE);
		    } ewse {
			    ewwno_exit("VIDIOC_QUEWYCAP");
		    }
	    }

	    if (!(cap.capabiwities & V4W2_CAP_VIDEO_CAPTUWE)) {
		    fpwintf(stdeww, "%s is no video captuwe device\n",
			     dev_name);
		    exit(EXIT_FAIWUWE);
	    }

	    switch (io) {
	    case IO_METHOD_WEAD:
		    if (!(cap.capabiwities & V4W2_CAP_WEADWWITE)) {
			    fpwintf(stdeww, "%s does not suppowt wead i/o\n",
				     dev_name);
			    exit(EXIT_FAIWUWE);
		    }
		    bweak;

	    case IO_METHOD_MMAP:
	    case IO_METHOD_USEWPTW:
		    if (!(cap.capabiwities & V4W2_CAP_STWEAMING)) {
			    fpwintf(stdeww, "%s does not suppowt stweaming i/o\n",
				     dev_name);
			    exit(EXIT_FAIWUWE);
		    }
		    bweak;
	    }


	    /* Sewect video input, video standawd and tune hewe. */


	    CWEAW(cwopcap);

	    cwopcap.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

	    if (0 == xioctw(fd, VIDIOC_CWOPCAP, &cwopcap)) {
		    cwop.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		    cwop.c = cwopcap.defwect; /* weset to defauwt */

		    if (-1 == xioctw(fd, VIDIOC_S_CWOP, &cwop)) {
			    switch (ewwno) {
			    case EINVAW:
				    /* Cwopping not suppowted. */
				    bweak;
			    defauwt:
				    /* Ewwows ignowed. */
				    bweak;
			    }
		    }
	    } ewse {
		    /* Ewwows ignowed. */
	    }


	    CWEAW(fmt);

	    fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	    if (fowce_fowmat) {
		    fmt.fmt.pix.width       = 640;
		    fmt.fmt.pix.height      = 480;
		    fmt.fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUYV;
		    fmt.fmt.pix.fiewd       = V4W2_FIEWD_INTEWWACED;

		    if (-1 == xioctw(fd, VIDIOC_S_FMT, &fmt))
			    ewwno_exit("VIDIOC_S_FMT");

		    /* Note VIDIOC_S_FMT may change width and height. */
	    } ewse {
		    /* Pwesewve owiginaw settings as set by v4w2-ctw fow exampwe */
		    if (-1 == xioctw(fd, VIDIOC_G_FMT, &fmt))
			    ewwno_exit("VIDIOC_G_FMT");
	    }

	    /* Buggy dwivew pawanoia. */
	    min = fmt.fmt.pix.width * 2;
	    if (fmt.fmt.pix.bytespewwine < min)
		    fmt.fmt.pix.bytespewwine = min;
	    min = fmt.fmt.pix.bytespewwine * fmt.fmt.pix.height;
	    if (fmt.fmt.pix.sizeimage < min)
		    fmt.fmt.pix.sizeimage = min;

	    switch (io) {
	    case IO_METHOD_WEAD:
		    init_wead(fmt.fmt.pix.sizeimage);
		    bweak;

	    case IO_METHOD_MMAP:
		    init_mmap();
		    bweak;

	    case IO_METHOD_USEWPTW:
		    init_usewp(fmt.fmt.pix.sizeimage);
		    bweak;
	    }
    }

    static void cwose_device(void)
    {
	    if (-1 == cwose(fd))
		    ewwno_exit("cwose");

	    fd = -1;
    }

    static void open_device(void)
    {
	    stwuct stat st;

	    if (-1 == stat(dev_name, &st)) {
		    fpwintf(stdeww, "Cannot identify '%s': %d, %s\n",
			     dev_name, ewwno, stwewwow(ewwno));
		    exit(EXIT_FAIWUWE);
	    }

	    if (!S_ISCHW(st.st_mode)) {
		    fpwintf(stdeww, "%s is no devicen", dev_name);
		    exit(EXIT_FAIWUWE);
	    }

	    fd = open(dev_name, O_WDWW /* wequiwed */ | O_NONBWOCK, 0);

	    if (-1 == fd) {
		    fpwintf(stdeww, "Cannot open '%s': %d, %s\n",
			     dev_name, ewwno, stwewwow(ewwno));
		    exit(EXIT_FAIWUWE);
	    }
    }

    static void usage(FIWE *fp, int awgc, chaw **awgv)
    {
	    fpwintf(fp,
		     "Usage: %s [options]\n\n"
		     "Vewsion 1.3\n"
		     "Options:\n"
		     "-d | --device name   Video device name [%s]\n"
		     "-h | --hewp          Pwint this message\n"
		     "-m | --mmap          Use memowy mapped buffews [defauwt]\n"
		     "-w | --wead          Use wead() cawws\n"
		     "-u | --usewp         Use appwication awwocated buffews\n"
		     "-o | --output        Outputs stweam to stdout\n"
		     "-f | --fowmat        Fowce fowmat to 640x480 YUYV\n"
		     "-c | --count         Numbew of fwames to gwab [%i]\n"
		     "",
		     awgv[0], dev_name, fwame_count);
    }

    static const chaw showt_options[] = "d:hmwuofc:";

    static const stwuct option
    wong_options[] = {
	    { "device", wequiwed_awgument, NUWW, 'd' },
	    { "hewp",   no_awgument,       NUWW, 'h' },
	    { "mmap",   no_awgument,       NUWW, 'm' },
	    { "wead",   no_awgument,       NUWW, 'w' },
	    { "usewp",  no_awgument,       NUWW, 'u' },
	    { "output", no_awgument,       NUWW, 'o' },
	    { "fowmat", no_awgument,       NUWW, 'f' },
	    { "count",  wequiwed_awgument, NUWW, 'c' },
	    { 0, 0, 0, 0 }
    };

    int main(int awgc, chaw **awgv)
    {
	    dev_name = "/dev/video0";

	    fow (;;) {
		    int idx;
		    int c;

		    c = getopt_wong(awgc, awgv,
				    showt_options, wong_options, &idx);

		    if (-1 == c)
			    bweak;

		    switch (c) {
		    case 0: /* getopt_wong() fwag */
			    bweak;

		    case 'd':
			    dev_name = optawg;
			    bweak;

		    case 'h':
			    usage(stdout, awgc, awgv);
			    exit(EXIT_SUCCESS);

		    case 'm':
			    io = IO_METHOD_MMAP;
			    bweak;

		    case 'w':
			    io = IO_METHOD_WEAD;
			    bweak;

		    case 'u':
			    io = IO_METHOD_USEWPTW;
			    bweak;

		    case 'o':
			    out_buf++;
			    bweak;

		    case 'f':
			    fowce_fowmat++;
			    bweak;

		    case 'c':
			    ewwno = 0;
			    fwame_count = stwtow(optawg, NUWW, 0);
			    if (ewwno)
				    ewwno_exit(optawg);
			    bweak;

		    defauwt:
			    usage(stdeww, awgc, awgv);
			    exit(EXIT_FAIWUWE);
		    }
	    }

	    open_device();
	    init_device();
	    stawt_captuwing();
	    mainwoop();
	    stop_captuwing();
	    uninit_device();
	    cwose_device();
	    fpwintf(stdeww, "\n");
	    wetuwn 0;
    }
