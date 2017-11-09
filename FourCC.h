#ifndef FOURCC_H
#define FOURCC_H

#define MKTAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))

#define FOURCC_ftyp MKTAG('f','t','y','p')
#define FOURCC_moov MKTAG('m','o','o','v')
#define FOURCC_mvhd MKTAG('m','v','h','d')
#define FOURCC_trak MKTAG('t','r','a','k')
#define FOURCC_tkhd MKTAG('t','k','h','d')
#define FOURCC_mdia MKTAG('m','d','i','a')
#define FOURCC_mdhd MKTAG('m','d','h','d')
#define FOURCC_hdlr MKTAG('h','d','l','r')
#define FOURCC_minf MKTAG('m','i','n','f')
#define FOURCC_stbl MKTAG('s','t','b','l')
#define FOURCC_stsd MKTAG('s','t','s','d')
#define FOURCC_stts MKTAG('s','t','t','s')
#define FOURCC_stss MKTAG('s','t','s','s')
#define FOURCC_ctts MKTAG('c','t','t','s')
#define FOURCC_stco MKTAG('s','t','c','o')
#define FOURCC_co64 MKTAG('c','o','6','4')
#define FOURCC_stsc MKTAG('s','t','s','c')
#define FOURCC_stsz MKTAG('s','t','s','z')
#define FOURCC_stz2 MKTAG('s','t','z','2')
#define FOURCC_udta MKTAG('u','d','t','a')
#define FOURCC_meta MKTAG('m','e','t','a')
#define FOURCC_dinf MKTAG('d','i','n','f')
#define FOURCC_pitm MKTAG('p','i','t','m')
#define FOURCC_iinf MKTAG('i','i','n','f')
#define FOURCC_iref MKTAG('i','r','e','f')

//heif
#define FOURCC_iprp MKTAG('i','p','r','p')
#define FOURCC_ipco MKTAG('i','p','c','o')


#define HANDLER_VIDEO MKTAG('v','i','d','e')
#define HANDLER_AUDIO MKTAG('s','o','u','n')
#define HANDLER_HINT MKTAG('h','i','n','t')
#define HANDLER_META MKTAG('m','e','t','a')

#endif // FOURCC_H
