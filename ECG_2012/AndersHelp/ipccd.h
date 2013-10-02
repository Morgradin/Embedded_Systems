#ifndef __IP_CCD_H
#define __IP_CCD_H

#include <gezel/ipblock.h>
#include "bmp.hxx"
#include "types.h"

class ccd : public aipblock {
private:
	string filename;
	Image * image;
	unsigned int pixel_ptr;
	bool ack;
	bool rdy;
	WORD reg_data;
	bool update;
	
	enum ports {REQ, CMD, ACK, WAIT, DATA, RDY};
	
public:
	ccd(char *name);
	virtual ~ccd();
	void setparm(char *);
	void run();
	void out_run();
	bool checkterminal(int n, char *tname, aipblock::iodir d);
	bool cannotSleepTest();
	bool needsWakeupTest();
};

#endif /* __IP_CCD_H */

