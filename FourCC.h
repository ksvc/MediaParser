#ifndef FOURCC_H
#define FOURCC_H

#define MKTAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))

#define FOURCC_moov MKTAG('m','o','o','v')
#define FOURCC_trak MKTAG('t','r','a','k')
#define FOURCC_mdia MKTAG('m','d','i','a')
#define FOURCC_minf MKTAG('m','i','n','f')
#define FOURCC_stbl MKTAG('s','t','b','l')



#endif // FOURCC_H
