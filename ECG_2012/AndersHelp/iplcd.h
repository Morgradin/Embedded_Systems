#ifndef __IP_LCD_H
#define __IP_LCD_H

#include <gezel/ipblock.h>
#include "bmp.hxx"
#include "types.h"

class lcd : public aipblock {
private:
	string filename;
	Image * image;
	unsigned int pixel_ptr;
	bool ack;
	bool update;
	
	enum ports {REQ, CMD, DATA, ACK};
	
public:
	lcd(char *name);
	virtual ~lcd();
	void setparm(char *);
	void run();
	void out_run();
	bool checkterminal(int n, char *tname, aipblock::iodir d);
	bool cannotSleepTest();
	bool needsWakeupTest();

};

#endif /* __IP_LCD_H */
