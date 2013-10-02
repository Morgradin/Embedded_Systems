#include "config.h"
#include "ipccd.h"
#include <string>
#include "driver.h"
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
#include <stdio.h>
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */

ccd::ccd(char *name) : aipblock(name) {
	this->filename = "capture.bmp";
	this->image = new Image;
	this->pixel_ptr = 0;
	this->regOutput(ACK);
	this->regOutput(DATA);
	this->regOutput(RDY);
	this->ack = false;
	this->rdy = false;
	this->reg_data = false;
	this->update = false;
}
	
ccd::~ccd() {
	delete this->image;
}

void ccd::out_run() {
	this->ioval[ACK]->assignulong(this->ack ? 1 : 0);
	this->ioval[DATA]->assignulong(this->reg_data);
	this->ioval[RDY]->assignulong(this->rdy ? 1 : 0);
	if (!this->ack && !this->rdy) {
		this->update = false;
	}
}

void ccd::run() {
	/* Default values for output control signals, do not touch data signals unless used! */
	this->reg_data = 0;
	
	/* Processing input if requested */
	if (this->ioval[REQ]->toulong() == 1 && !this->rdy && !this->ack) {
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
		printf("IP-BLOCK (CCD): Request received\n");
		fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
		switch (this->ioval[CMD]->toulong()) {
			case CCDCapture:
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (CCD): Capturing image\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				if (!this->image->bmp_open(this->filename)) {
					// An error occured loading the image
					printf("IP-BLOCK (CCD): ERROR, image not loaded (\"%s\").\n", this->filename.c_str());
					fflush(stdout);
				} else {
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
					printf("IP-BLOCK (CCD): Image \"%s\" loaded succesfully.\n", this->filename.c_str());
					fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				}
				ack = true;
				break;
			case CCDReset:
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (CCD): Resetting image pointer\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				this->pixel_ptr = 0;
				this->ack = true;
				break;
			case CCDGetWidth:
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (CCD): Returning image width\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				this->reg_data = this->image->Width();
				// Data is ready
				this->ack = true;
				this->rdy = true;
				break;
			case CCDGetHeight:
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (CCD): Returning image height\n");
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				this->reg_data = this->image->Height();
				// Data is ready
				this->ack = true;
				this->rdy = true;
				break;
			case CCDGetPixel:
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (CCD): Returning image pixel (%d) value (%d)\n", this->pixel_ptr, this->image->Pixel(this->pixel_ptr));
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				this->reg_data = this->image->Pixel(this->pixel_ptr);
				this->pixel_ptr += 1;
				// Data is ready
				this->ack = true;
				this->rdy = true;
				break;
			case CCDGetPixels: {
				unsigned long data = 0;
				data  = this->image->Pixel(this->pixel_ptr+0) << 24;
				data |= this->image->Pixel(this->pixel_ptr+1) << 16;
				data |= this->image->Pixel(this->pixel_ptr+2) <<  8;
				data |= this->image->Pixel(this->pixel_ptr+3) <<  0;
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
				printf("IP-BLOCK (CCD): Returning image pixel (%d-%d) values (%lX=%X,%X,%X,%X)\n", this->pixel_ptr, this->pixel_ptr+3, data, this->image->Pixel(this->pixel_ptr+0), this->image->Pixel(this->pixel_ptr+1), this->image->Pixel(this->pixel_ptr+2), this->image->Pixel(this->pixel_ptr+3));
				fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
				this->reg_data = data;
				this->pixel_ptr += 4;
				// Data is ready
				this->ack = true;
				this->rdy = true;
				break;
			}
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
			default:
				printf("IP-BLOCK (CCD): Unknown command, ignoring request!\n");
				fflush(stdout);
				break;
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
		}
	} else {
		this->ack = false;
		this->rdy = false;
	}
	
	if (this->ack || this->rdy) {
		this->update = true;
	}

#ifdef DEBUG
	if (this->ioval[WAIT]->toulong() == 1 && this->ack) {
		printf("WARNING: you may have forgotten to read the result on the bus in the ARM software!\n");
	}
#endif /* DEBUG */
	
#ifdef DEBUG_CCD
#ifdef DEBUG_IPBLOCK
	printf("IP-BLOCK (CCD): CMD %lX REQ %lu ACK %lu/%u DATA %lX/%X WAIT %lu READY %lu/%u\n"
		, this->ioval[CMD]->toulong()
		, this->ioval[REQ]->toulong()
		, this->ioval[ACK]->toulong()
		, this->ack ? 1 : 0
		, this->ioval[DATA]->toulong()
		, this->reg_data
		, this->ioval[WAIT]->toulong()
		, this->ioval[RDY]->toulong()
		, this->rdy ? 1 : 0
	);
	fflush(stdout);
#endif /* DEBUG_IPBLOCK */
#endif /* DEBUG_CCD */
}

bool ccd::checkterminal(int n, char * tname, aipblock::iodir dir) {
	switch (n) {
		case CMD: return (this->isinput(dir) && this->isname(tname, "command"));
		case REQ: return (this->isinput(dir) && this->isname(tname, "req"));
		case ACK: return (this->isoutput(dir) && this->isname(tname, "ack"));
		case DATA: return (this->isoutput(dir) && this->isname(tname, "data"));
		case WAIT: return (this->isinput(dir) && this->isname(tname, "wait"));
		case RDY: return (this->isoutput(dir) && this->isname(tname, "ready"));
		default: printf("Terminal %d named %s is not a valid terminal!\n", n, tname); break;
	}
	return false;
}

void ccd::setparm(char *_name) {
	char * v = matchparm(_name, "image");
	if (v != NULL) 
		this->filename = v;
	else
		printf("Error: ccd does not recognize parameter %s\n",_name);
}

bool ccd::cannotSleepTest() {
	return false;
}

bool ccd::needsWakeupTest() {
	return this->update;
}

extern "C" aipblock *create_ccd(char *instname) {
	return new ccd(instname);
}

