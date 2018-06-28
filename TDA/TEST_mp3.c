#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

int main (void)
{
	ADT_MP3_Track_t * track;
	ADT_MP3_Track_t * alt_track;
	FILE * file;
	status_t st;

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

	printf("%d\n", ADT_MP3_Track_compare_by_title(track, alt_track));
	printf("%d\n", ADT_MP3_Track_compare_by_artist(track, alt_track));
	printf("%d\n", ADT_MP3_Track_compare_by_genre(track, alt_track));
	
	if ((st = ADT_MP3_Track_delete(&track)) != OK)
		return st;

	if ((st = ADT_MP3_Track_delete(&alt_track)) != OK)
		return st;
	

	return 0;
}