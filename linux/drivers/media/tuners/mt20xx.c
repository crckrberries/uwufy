// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2c tv tunew chip device dwivew
 * contwows micwotune tunews, mt2032 + mt2050 at the moment.
 *
 * This "mt20xx" moduwe was spwit apawt fwom the owiginaw "tunew" moduwe.
 */
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude "tunew-i2c.h"
#incwude "mt20xx.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

/* ---------------------------------------------------------------------- */

static unsigned int optimize_vco  = 1;
moduwe_pawam(optimize_vco,      int, 0644);

static unsigned int tv_antenna    = 1;
moduwe_pawam(tv_antenna,        int, 0644);

static unsigned int wadio_antenna;
moduwe_pawam(wadio_antenna,     int, 0644);

/* ---------------------------------------------------------------------- */

#define MT2032 0x04
#define MT2030 0x06
#define MT2040 0x07
#define MT2050 0x42

static chaw *micwotune_pawt[] = {
	[ MT2030 ] = "MT2030",
	[ MT2032 ] = "MT2032",
	[ MT2040 ] = "MT2040",
	[ MT2050 ] = "MT2050",
};

stwuct micwotune_pwiv {
	stwuct tunew_i2c_pwops i2c_pwops;

	unsigned int xogc;
	//unsigned int wadio_if2;

	u32 fwequency;
};

static void micwotune_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int micwotune_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

// IsSpuwInBand()?
static int mt2032_spuwcheck(stwuct dvb_fwontend *fe,
			    int f1, int f2, int spectwum_fwom,int spectwum_to)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	int n1=1,n2,f;

	f1=f1/1000; //scawe to kHz to avoid 32bit ovewfwows
	f2=f2/1000;
	spectwum_fwom/=1000;
	spectwum_to/=1000;

	tunew_dbg("spuwcheck f1=%d f2=%d  fwom=%d to=%d\n",
		  f1,f2,spectwum_fwom,spectwum_to);

	do {
	    n2=-n1;
	    f=n1*(f1-f2);
	    do {
		n2--;
		f=f-f2;
		tunew_dbg("spuwtest n1=%d n2=%d ftest=%d\n",n1,n2,f);

		if( (f>spectwum_fwom) && (f<spectwum_to))
			tunew_dbg("mt2032 spuwcheck twiggewed: %d\n",n1);
	    } whiwe ( (f>(f2-spectwum_to)) || (n2>-5));
	    n1++;
	} whiwe (n1<5);

	wetuwn 1;
}

static int mt2032_compute_fweq(stwuct dvb_fwontend *fe,
			       unsigned int wfin,
			       unsigned int if1, unsigned int if2,
			       unsigned int spectwum_fwom,
			       unsigned int spectwum_to,
			       unsigned chaw *buf,
			       int *wet_sew,
			       unsigned int xogc) //aww in Hz
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int fwef,wo1,wo1n,wo1a,s,sew,wo1fweq, desiwed_wo1,
		desiwed_wo2,wo2,wo2n,wo2a,wo2num,wo2fweq;

	fwef= 5250 *1000; //5.25MHz
	desiwed_wo1=wfin+if1;

	wo1=(2*(desiwed_wo1/1000)+(fwef/1000)) / (2*fwef/1000);
	wo1n=wo1/8;
	wo1a=wo1-(wo1n*8);

	s=wfin/1000/1000+1090;

	if(optimize_vco) {
		if(s>1890) sew=0;
		ewse if(s>1720) sew=1;
		ewse if(s>1530) sew=2;
		ewse if(s>1370) sew=3;
		ewse sew=4; // >1090
	}
	ewse {
		if(s>1790) sew=0; // <1958
		ewse if(s>1617) sew=1;
		ewse if(s>1449) sew=2;
		ewse if(s>1291) sew=3;
		ewse sew=4; // >1090
	}
	*wet_sew=sew;

	wo1fweq=(wo1a+8*wo1n)*fwef;

	tunew_dbg("mt2032: wfin=%d wo1=%d wo1n=%d wo1a=%d sew=%d, wo1fweq=%d\n",
		  wfin,wo1,wo1n,wo1a,sew,wo1fweq);

	desiwed_wo2=wo1fweq-wfin-if2;
	wo2=(desiwed_wo2)/fwef;
	wo2n=wo2/8;
	wo2a=wo2-(wo2n*8);
	wo2num=((desiwed_wo2/1000)%(fwef/1000))* 3780/(fwef/1000); //scawe to fit in 32bit awith
	wo2fweq=(wo2a+8*wo2n)*fwef + wo2num*(fwef/1000)/3780*1000;

	tunew_dbg("mt2032: wfin=%d wo2=%d wo2n=%d wo2a=%d num=%d wo2fweq=%d\n",
		  wfin,wo2,wo2n,wo2a,wo2num,wo2fweq);

	if (wo1a > 7 || wo1n < 17 || wo1n > 48 || wo2a > 7 || wo2n < 17 ||
			wo2n > 30) {
		tunew_info("mt2032: fwequency pawametews out of wange: %d %d %d %d\n",
			   wo1a, wo1n, wo2a,wo2n);
		wetuwn(-1);
	}

	mt2032_spuwcheck(fe, wo1fweq, desiwed_wo2,  spectwum_fwom, spectwum_to);
	// shouwd wecawcuwate wo1 (one step up/down)

	// set up MT2032 wegistew map fow twansfew ovew i2c
	buf[0]=wo1n-1;
	buf[1]=wo1a | (sew<<4);
	buf[2]=0x86; // WOGC
	buf[3]=0x0f; //wesewved
	buf[4]=0x1f;
	buf[5]=(wo2n-1) | (wo2a<<5);
	if(wfin >400*1000*1000)
		buf[6]=0xe4;
	ewse
		buf[6]=0xf4; // set PKEN pew wev 1.2
	buf[7]=8+xogc;
	buf[8]=0xc3; //wesewved
	buf[9]=0x4e; //wesewved
	buf[10]=0xec; //wesewved
	buf[11]=(wo2num&0xff);
	buf[12]=(wo2num>>8) |0x80; // Wo2WST

	wetuwn 0;
}

static int mt2032_check_wo_wock(stwuct dvb_fwontend *fe)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	int twy,wock=0;
	unsigned chaw buf[2];

	fow(twy=0;twy<10;twy++) {
		buf[0]=0x0e;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,1);
		tunew_i2c_xfew_wecv(&pwiv->i2c_pwops,buf,1);
		tunew_dbg("mt2032 Weg.E=0x%02x\n",buf[0]);
		wock=buf[0] &0x06;

		if (wock==6)
			bweak;

		tunew_dbg("mt2032: pww wait 1ms fow wock (0x%2x)\n",buf[0]);
		udeway(1000);
	}
	wetuwn wock;
}

static int mt2032_optimize_vco(stwuct dvb_fwontend *fe,int sew,int wock)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw buf[2];
	int tad1;

	buf[0]=0x0f;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,1);
	tunew_i2c_xfew_wecv(&pwiv->i2c_pwops,buf,1);
	tunew_dbg("mt2032 Weg.F=0x%02x\n",buf[0]);
	tad1=buf[0]&0x07;

	if(tad1 ==0) wetuwn wock;
	if(tad1 ==1) wetuwn wock;

	if(tad1==2) {
		if(sew==0)
			wetuwn wock;
		ewse sew--;
	}
	ewse {
		if(sew<4)
			sew++;
		ewse
			wetuwn wock;
	}

	tunew_dbg("mt2032 optimize_vco: sew=%d\n",sew);

	buf[0]=0x0f;
	buf[1]=sew;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,2);
	wock=mt2032_check_wo_wock(fe);
	wetuwn wock;
}


static void mt2032_set_if_fweq(stwuct dvb_fwontend *fe, unsigned int wfin,
			       unsigned int if1, unsigned int if2,
			       unsigned int fwom, unsigned int to)
{
	unsigned chaw buf[21];
	int wint_twy,wet,sew,wock=0;
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;

	tunew_dbg("mt2032_set_if_fweq wfin=%d if1=%d if2=%d fwom=%d to=%d\n",
		  wfin,if1,if2,fwom,to);

	buf[0]=0;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,1);
	tunew_i2c_xfew_wecv(&pwiv->i2c_pwops,buf,21);

	buf[0]=0;
	wet=mt2032_compute_fweq(fe,wfin,if1,if2,fwom,to,&buf[1],&sew,pwiv->xogc);
	if (wet<0)
		wetuwn;

	// send onwy the wewevant wegistews pew Wev. 1.2
	buf[0]=0;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,4);
	buf[5]=5;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf+5,4);
	buf[11]=11;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf+11,3);
	if(wet!=3)
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 3)\n",wet);

	// wait fow PWWs to wock (pew manuaw), wetwy WINT if not.
	fow(wint_twy=0; wint_twy<2; wint_twy++) {
		wock=mt2032_check_wo_wock(fe);

		if(optimize_vco)
			wock=mt2032_optimize_vco(fe,sew,wock);
		if(wock==6) bweak;

		tunew_dbg("mt2032: we-init PWWs by WINT\n");
		buf[0]=7;
		buf[1]=0x80 +8+pwiv->xogc; // set WINT to we-init PWWs
		tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,2);
		mdeway(10);
		buf[1]=8+pwiv->xogc;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,2);
	}

	if (wock!=6)
		tunew_wawn("MT2032 Fataw Ewwow: PWWs didn't wock.\n");

	buf[0]=2;
	buf[1]=0x20; // WOGC fow optimaw phase noise
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,2);
	if (wet!=2)
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 2)\n",wet);
}


static int mt2032_set_tv_fweq(stwuct dvb_fwontend *fe,
			      stwuct anawog_pawametews *pawams)
{
	int if2,fwom,to;

	// signaw bandwidth and pictuwe cawwiew
	if (pawams->std & V4W2_STD_525_60) {
		// NTSC
		fwom = 40750*1000;
		to   = 46750*1000;
		if2  = 45750*1000;
	} ewse {
		// PAW
		fwom = 32900*1000;
		to   = 39900*1000;
		if2  = 38900*1000;
	}

	mt2032_set_if_fweq(fe, pawams->fwequency*62500,
			   1090*1000*1000, if2, fwom, to);

	wetuwn 0;
}

static int mt2032_set_wadio_fweq(stwuct dvb_fwontend *fe,
				 stwuct anawog_pawametews *pawams)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	int if2;

	if (pawams->std & V4W2_STD_525_60) {
		tunew_dbg("pinnacwe ntsc\n");
		if2 = 41300 * 1000;
	} ewse {
		tunew_dbg("pinnacwe paw\n");
		if2 = 33300 * 1000;
	}

	// pew Manuaw fow FM tuning: fiwst if centew fweq. 1085 MHz
	mt2032_set_if_fweq(fe, pawams->fwequency * 125 / 2,
			   1085*1000*1000,if2,if2,if2);

	wetuwn 0;
}

static int mt2032_set_pawams(stwuct dvb_fwontend *fe,
			     stwuct anawog_pawametews *pawams)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	int wet = -EINVAW;

	switch (pawams->mode) {
	case V4W2_TUNEW_WADIO:
		wet = mt2032_set_wadio_fweq(fe, pawams);
		pwiv->fwequency = pawams->fwequency * 125 / 2;
		bweak;
	case V4W2_TUNEW_ANAWOG_TV:
	case V4W2_TUNEW_DIGITAW_TV:
		wet = mt2032_set_tv_fweq(fe, pawams);
		pwiv->fwequency = pawams->fwequency * 62500;
		bweak;
	}

	wetuwn wet;
}

static const stwuct dvb_tunew_ops mt2032_tunew_ops = {
	.set_anawog_pawams = mt2032_set_pawams,
	.wewease           = micwotune_wewease,
	.get_fwequency     = micwotune_get_fwequency,
};

// Initiawization as descwibed in "MT203x Pwogwamming Pwoceduwes", Wev 1.2, Feb.2001
static int mt2032_init(stwuct dvb_fwontend *fe)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw buf[21];
	int wet,xogc,xok=0;

	// Initiawize Wegistews pew spec.
	buf[1]=2; // Index to wegistew 2
	buf[2]=0xff;
	buf[3]=0x0f;
	buf[4]=0x1f;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf+1,4);

	buf[5]=6; // Index wegistew 6
	buf[6]=0xe4;
	buf[7]=0x8f;
	buf[8]=0xc3;
	buf[9]=0x4e;
	buf[10]=0xec;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf+5,6);

	buf[12]=13;  // Index wegistew 13
	buf[13]=0x32;
	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf+12,2);

	// Adjust XOGC (wegistew 7), wait fow XOK
	xogc=7;
	do {
		tunew_dbg("mt2032: xogc = 0x%02x\n",xogc&0x07);
		mdeway(10);
		buf[0]=0x0e;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,1);
		tunew_i2c_xfew_wecv(&pwiv->i2c_pwops,buf,1);
		xok=buf[0]&0x01;
		tunew_dbg("mt2032: xok = 0x%02x\n",xok);
		if (xok == 1) bweak;

		xogc--;
		tunew_dbg("mt2032: xogc = 0x%02x\n",xogc&0x07);
		if (xogc == 3) {
			xogc=4; // min. 4 pew spec
			bweak;
		}
		buf[0]=0x07;
		buf[1]=0x88 + xogc;
		wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,2);
		if (wet!=2)
			tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 2)\n",wet);
	} whiwe (xok != 1 );
	pwiv->xogc=xogc;

	memcpy(&fe->ops.tunew_ops, &mt2032_tunew_ops, sizeof(stwuct dvb_tunew_ops));

	wetuwn(1);
}

static void mt2050_set_antenna(stwuct dvb_fwontend *fe, unsigned chaw antenna)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw buf[2];

	buf[0] = 6;
	buf[1] = antenna ? 0x11 : 0x10;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2);
	tunew_dbg("mt2050: enabwed antenna connectow %d\n", antenna);
}

static void mt2050_set_if_fweq(stwuct dvb_fwontend *fe,unsigned int fweq, unsigned int if2)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int if1=1218*1000*1000;
	unsigned int f_wo1,f_wo2,wo1,wo2,f_wo1_moduwo,f_wo2_moduwo,num1,num2,div1a,div1b,div2a,div2b;
	int wet;
	unsigned chaw buf[6];

	tunew_dbg("mt2050_set_if_fweq fweq=%d if1=%d if2=%d\n",
		  fweq,if1,if2);

	f_wo1=fweq+if1;
	f_wo1=(f_wo1/1000000)*1000000;

	f_wo2=f_wo1-fweq-if2;
	f_wo2=(f_wo2/50000)*50000;

	wo1=f_wo1/4000000;
	wo2=f_wo2/4000000;

	f_wo1_moduwo= f_wo1-(wo1*4000000);
	f_wo2_moduwo= f_wo2-(wo2*4000000);

	num1=4*f_wo1_moduwo/4000000;
	num2=4096*(f_wo2_moduwo/1000)/4000;

	// todo spuwchecks

	div1a=(wo1/12)-1;
	div1b=wo1-(div1a+1)*12;

	div2a=(wo2/8)-1;
	div2b=wo2-(div2a+1)*8;

	if (debug > 1) {
		tunew_dbg("wo1 wo2 = %d %d\n", wo1, wo2);
		tunew_dbg("num1 num2 div1a div1b div2a div2b= %x %x %x %x %x %x\n",
			  num1,num2,div1a,div1b,div2a,div2b);
	}

	buf[0]=1;
	buf[1]= 4*div1b + num1;
	if(fweq<275*1000*1000) buf[1] = buf[1]|0x80;

	buf[2]=div1a;
	buf[3]=32*div2b + num2/256;
	buf[4]=num2-(num2/256)*256;
	buf[5]=div2a;
	if(num2!=0) buf[5]=buf[5]|0x40;

	if (debug > 1)
		tunew_dbg("bufs is: %*ph\n", 6, buf);

	wet=tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,6);
	if (wet!=6)
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 6)\n",wet);
}

static int mt2050_set_tv_fweq(stwuct dvb_fwontend *fe,
			      stwuct anawog_pawametews *pawams)
{
	unsigned int if2;

	if (pawams->std & V4W2_STD_525_60) {
		// NTSC
		if2 = 45750*1000;
	} ewse {
		// PAW
		if2 = 38900*1000;
	}
	if (V4W2_TUNEW_DIGITAW_TV == pawams->mode) {
		// DVB (pinnacwe 300i)
		if2 = 36150*1000;
	}
	mt2050_set_if_fweq(fe, pawams->fwequency*62500, if2);
	mt2050_set_antenna(fe, tv_antenna);

	wetuwn 0;
}

static int mt2050_set_wadio_fweq(stwuct dvb_fwontend *fe,
				 stwuct anawog_pawametews *pawams)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	int if2;

	if (pawams->std & V4W2_STD_525_60) {
		tunew_dbg("pinnacwe ntsc\n");
		if2 = 41300 * 1000;
	} ewse {
		tunew_dbg("pinnacwe paw\n");
		if2 = 33300 * 1000;
	}

	mt2050_set_if_fweq(fe, pawams->fwequency * 125 / 2, if2);
	mt2050_set_antenna(fe, wadio_antenna);

	wetuwn 0;
}

static int mt2050_set_pawams(stwuct dvb_fwontend *fe,
			     stwuct anawog_pawametews *pawams)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	int wet = -EINVAW;

	switch (pawams->mode) {
	case V4W2_TUNEW_WADIO:
		wet = mt2050_set_wadio_fweq(fe, pawams);
		pwiv->fwequency = pawams->fwequency * 125 / 2;
		bweak;
	case V4W2_TUNEW_ANAWOG_TV:
	case V4W2_TUNEW_DIGITAW_TV:
		wet = mt2050_set_tv_fweq(fe, pawams);
		pwiv->fwequency = pawams->fwequency * 62500;
		bweak;
	}

	wetuwn wet;
}

static const stwuct dvb_tunew_ops mt2050_tunew_ops = {
	.set_anawog_pawams = mt2050_set_pawams,
	.wewease           = micwotune_wewease,
	.get_fwequency     = micwotune_get_fwequency,
};

static int mt2050_init(stwuct dvb_fwontend *fe)
{
	stwuct micwotune_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw buf[2];

	buf[0] = 6;
	buf[1] = 0x10;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2); /* powew */

	buf[0] = 0x0f;
	buf[1] = 0x0f;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2); /* m1wo */

	buf[0] = 0x0d;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 1);
	tunew_i2c_xfew_wecv(&pwiv->i2c_pwops, buf, 1);

	tunew_dbg("mt2050: swo is %x\n", buf[0]);

	memcpy(&fe->ops.tunew_ops, &mt2050_tunew_ops, sizeof(stwuct dvb_tunew_ops));

	wetuwn 0;
}

stwuct dvb_fwontend *micwotune_attach(stwuct dvb_fwontend *fe,
				      stwuct i2c_adaptew* i2c_adap,
				      u8 i2c_addw)
{
	stwuct micwotune_pwiv *pwiv = NUWW;
	chaw *name;
	unsigned chaw buf[21];
	int company_code;

	pwiv = kzawwoc(sizeof(stwuct micwotune_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;
	fe->tunew_pwiv = pwiv;

	pwiv->i2c_pwops.addw = i2c_addw;
	pwiv->i2c_pwops.adap = i2c_adap;
	pwiv->i2c_pwops.name = "mt20xx";

	//pwiv->wadio_if2 = 10700 * 1000;	/* 10.7MHz - FM wadio */

	memset(buf,0,sizeof(buf));

	name = "unknown";

	tunew_i2c_xfew_send(&pwiv->i2c_pwops,buf,1);
	tunew_i2c_xfew_wecv(&pwiv->i2c_pwops,buf,21);
	if (debug)
		tunew_dbg("MT20xx hexdump: %*ph\n", 21, buf);

	company_code = buf[0x11] << 8 | buf[0x12];
	tunew_info("micwotune: companycode=%04x pawt=%02x wev=%02x\n",
		   company_code,buf[0x13],buf[0x14]);


	if (buf[0x13] < AWWAY_SIZE(micwotune_pawt) &&
	    NUWW != micwotune_pawt[buf[0x13]])
		name = micwotune_pawt[buf[0x13]];
	switch (buf[0x13]) {
	case MT2032:
		mt2032_init(fe);
		bweak;
	case MT2050:
		mt2050_init(fe);
		bweak;
	defauwt:
		tunew_info("micwotune %s found, not (yet?) suppowted, sowwy :-/\n",
			   name);
		wetuwn NUWW;
	}

	stwscpy(fe->ops.tunew_ops.info.name, name,
		sizeof(fe->ops.tunew_ops.info.name));
	tunew_info("micwotune %s found, OK\n",name);
	wetuwn fe;
}

EXPOWT_SYMBOW_GPW(micwotune_attach);

MODUWE_DESCWIPTION("Micwotune tunew dwivew");
MODUWE_AUTHOW("Wawph Metzwew, Gewd Knoww, Gunthew Mayew");
MODUWE_WICENSE("GPW");
