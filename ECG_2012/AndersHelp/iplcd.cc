#include "config.h"
#include "iplcd.h"
#include <string>
#include "driver.h"

#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
#include <stdio.h>
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */

lcd::lcd(char *name) : aipblock(name) {
	this->filename = "display.bmp";
	this->image = new Image;
	this->pixel_ptr = 0;
	this->regOutput(ACK);
	this->ack = false;
	this->update = false;
}

lcd::~lcd() {
	delete this->image;
}

void lcd::out_run() {
	this->ioval[ACK]->assignulong(this->ack ? 1 : 0);
	if (!this->ack) {
		this->update = false;
	}
}

void lcd::run() {
	// Processing input if requested
	if (this->ioval[REQ]->toulong() == 1 && !this->ack) {
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
		printf("IP-BLOCK (LCD): Request received\n");
		fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
		switch (this->ioval[CMD]->toulong()) {
			case LCDShow:
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (LCD): Displaying image\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				if (!this->image->bmp_save(this->filename)) {
					// An error occured storing the image
					printf("IP-BLOCK (LCD): ERROR, image not saved (\"%s\").\n", this->filename.c_str());
					fflush(stdout);
				} else {
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
					printf("IP-BLOCK (LCD): Image \"%s\" saved succesfully.\n", this->filename.c_str());
					fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				}
				this->ack = true;
				break;
			case LCDReset:
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (LCD): Resetting image pointer\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				this->pixel_ptr = 0;
				this->ack = true;
				break;
			case LCDSetWidth:
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (LCD): Setting image width\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				this->image->setWidth(this->ioval[DATA]->toulong());
				this->ack = true;
				break;
			case LCDSetHeight:
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (LCD): Setting image height\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				this->image->setHeight(this->ioval[DATA]->toulong());
				this->ack = true;
				break;
			case LCDSetPixel:
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (LCD): Setting image pixel (%d) value (%lu)\n", this->pixel_ptr, this->ioval[DATA]->toulong());
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				this->image->Pixel(this->pixel_ptr, this->ioval[DATA]->toulong());
				this->pixel_ptr++;
				this->ack = true;
				break;
			case LCDSetPixels: {
				unsigned long data = this->ioval[DATA]->toulong();
				this->image->Pixel(this->pixel_ptr + 0, (data & 0xFF000000) >> 24);
				this->image->Pixel(this->pixel_ptr + 1, (data & 0x00FF0000) >> 16);
				this->image->Pixel(this->pixel_ptr + 2, (data & 0x0000FF00) >>  8);
				this->image->Pixel(this->pixel_ptr + 3, (data & 0x000000FF) >>  0);
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (LCD): Setting image pixel (%d-%d) values (%lX=%X,%X,%X,%X)\n", this->pixel_ptr, this->pixel_ptr+3, data, this->image->Pixel(this->pixel_ptr+0), this->image->Pixel(this->pixel_ptr+1), this->image->Pixel(this->pixel_ptr+2), this->image->Pixel(this->pixel_ptr+3));
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
				this->pixel_ptr += 4;
				this->ack = true;
				break;
			}
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
			default:
				printf("IP-BLOCK (LCD): Unknown command, ignoring request!\n");
				fflush(stdout);
				break;
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
		}
	} else {
		this->ack = false;
	}
	
	if (this->ack) {
		this->update = true;
	}
	
#ifdef DEBUG_LCD
#ifdef DEBUG_IPBLOCK
	printf("IP-BLOCK (LCD): CMD %lX REQ %lu DATA %lX ACK %lu\n"// WAIT %lu READY %lu\n"
		, this->ioval[CMD]->toulong()
		, this->ioval[REQ]->toulong()
		, this->ioval[DATA]->toulong()
		, this->ioval[ACK]->toulong()
//			, this->ioval[4]->toulong()
//			, this->ioval[5]->toulong()
	);
	fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_LCD */
}

bool lcd::checkterminal(int n, char *tname, aipblock::iodir dir) {
	switch (n) {
		case CMD: return (this->isinput(dir) && this->isname(tname, "command"));
		case REQ: return (this->isinput(dir) && this->isname(tname, "req"));
		case DATA: return (this->isinput(dir) && this->isname(tname, "data"));
		case ACK: return (this->isoutput(dir) && this->isname(tname, "ack"));
	}
	return false;
}

void lcd::setparm(char *_name) {
	char * v = matchparm(_name, "image");
	if (v != NULL) 
		this->filename = v;
	else
		printf("Error: ccd does not recognize parameter %s\n",_name);
}

bool lcd::cannotSleepTest() {
	return false;
}

bool lcd::needsWakeupTest() {
	return this->update;
}

extern "C" aipblock *create_lcd(char *instname) {
	return new lcd(instname);
}

