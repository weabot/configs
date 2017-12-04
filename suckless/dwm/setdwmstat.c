/*
 * Copyright (c) 2017 weabot <xi@nuxi.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>

/* Set the status through X11 */
void set_status(char*, Display*, Window);
/* Format the time into a readable string */
void format_time(struct tm*, char **ftime);

/* Days of the week */
char *doftw[7] = { "Sunday", "Monday", "Tuesday", "Wednesday",
		   "Thursday", "Friday", "Saturday" };

int
main()
{
	/* Find out about the XDisplay and Window */
	Display *d;
	Window w;

	if ((d = XOpenDisplay(NULL)) == NULL)
		err(1, "Couldn't open the display");
	w = DefaultRootWindow(d);

	/* Main time holders */
	struct tm *stime;
	time_t *tloc = malloc(sizeof(time_t));
	char *ftime = malloc(256);

	for (;;)
	{
		time(tloc);
		stime = localtime(tloc);
		format_time(stime, &ftime);
		set_status(ftime, d, w);

		sleep(60 - (time(tloc) % 60));
	}

	return 0;
}

void
set_status(char *ftime, Display *d, Window w)
{
	XStoreName(d, w, ftime);
	XSync(d, 1);
}

void
format_time(struct tm *stime, char **ftime)
{
	snprintf(*ftime, 255, "%s %02d-%02d-%04d %02d:%02d",
		doftw[stime->tm_wday], 		// Day of the week
		stime->tm_mday, 		// Day of the month
		stime->tm_mon + 1,		// Month
		1900 + stime->tm_year,		// Year
		stime->tm_hour,			// Hour
		stime->tm_min);			// Minute
}
