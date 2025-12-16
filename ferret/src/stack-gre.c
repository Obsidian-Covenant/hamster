/* Copyright (c) 2007 by Errata Security, All Rights Reserved
 * Programer(s): Robert David Graham [rdg]
 */
/*
*/
#include "stack-parser.h"
#include "stack-netframe.h"
#include "ferret.h"
#include "stack-extract.h"
#include <string.h>


void process_gre_pptp(struct Ferret *ferret, struct NetFrame *frame, const unsigned char *px, unsigned length)
{
	unsigned flags;
	unsigned offset;


	/*
		0                   1                   2                   3
		0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |C|R|K|S|s|Recur|A| Flags | Ver |         Protocol Type         |
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |    Key (HW) Payload Length    |       Key (LW) Call ID        |
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |                  Sequence Number (Optional)                   |
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |               Acknowledgment Number (Optional)                |
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	*/
	flags = ex16be(px);
	(void)ex16be(px+4);
	(void)ex16be(px+6);

	if ((flags&0xE80F) != 0x2001) {
		FRAMERR_UNKNOWN_UNSIGNED(frame, "gre", flags);
		return;
	}

	offset = 8;
	if (flags & 0x1000) {
		(void)ex32be(px+offset);
		offset += 4;
	}
	if (flags & 0x0080) {
		(void)ex32be(px+offset);
		offset += 4;
	}
	if (offset >= length) {
		/*FRAMERR_TRUNCATED(frame, "gre");*/
		return;
	}


	process_pptp(ferret, frame, px+offset, length-offset);


}


void process_gre(struct Ferret *ferret, struct NetFrame *frame, const unsigned char *px, unsigned length)
{
	unsigned version;
	unsigned protocol;
	
/*
      0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |C|R|K|S|s|Recur|  Flags  | Ver |         Protocol Type         |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |      Checksum (optional)      |       Offset (optional)       |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Key (optional)                        |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                    Sequence Number (optional)                 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Routing (optional)
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
	frame->layer4_protocol = LAYER4_GRE;

	if (length < 8) {
		FRAMERR_TRUNCATED(frame, "gre");
		return;
	}

	(void)ex16be(px);
	version = px[1]&0x7;
	protocol = ex16be(px+2);

	if (version == 1 && protocol == 0x880b)
		process_gre_pptp(ferret, frame, px, length);
	else {
		FRAMERR_UNKNOWN_UNSIGNED(frame, "gre", version);
	}


}

