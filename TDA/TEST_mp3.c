#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

int main (void)
{
	ADT_MP3_Track_t * track;
	ADT_MP3_Track_t * alt_track;
	FILE * file;

	file = fopen("track.mp3","rb");
	ADT_MP3_Track_load(&alt_track, file);
	fclose(file);

	ADT_MP3_Track_new_from_parameters(&track, "Square Hammer", "Ghost B.C.", 'Z');

	file = fopen("salida.tmp", "wt");
	ADT_MP3_Track_export_as_XML(track,file);
	ADT_MP3_Track_export_as_XML(alt_track,file);
	fclose(file);
	ADT_MP3_Track_export_as_CSV(track, '|', stdout);
	ADT_MP3_Track_export_as_CSV(alt_track, '|', stdout);


	return 0;
}