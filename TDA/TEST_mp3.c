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
	char del;
	char track_str[100] = "TRACK";
	del  = '/';


	file = fopen("track.mp3","rb");
	ADT_MP3_Track_load(&alt_track, file);
	fclose(file);

	ADT_MP3_Track_new_from_parameters(&track, "Square Hammer", "Ghost B.C.", "Rock");
	ADT_MP3_Track_set_genre(&track, "Easy Listening");
	file = fopen("salida.tmp", "wt");
	ADT_MP3_Track_export_as_XML(track,track_str,stdout);
	ADT_MP3_Track_export_as_XML(alt_track,track_str,stdout);
	fclose(file);
	ADT_MP3_Track_export_as_CSV(track, &del, stdout);
	ADT_MP3_Track_export_as_CSV(alt_track, &del, stdout);

	printf("%d\n", ADT_MP3_Track_compare_by_title(track, alt_track));
	printf("%d\n", ADT_MP3_Track_compare_by_artist(track, alt_track));
	printf("%d\n", ADT_MP3_Track_compare_by_genre(track, alt_track));
	

	
	printf("%s\n", ADT_MP3_Track_get_genre(track));


	if ((st = ADT_MP3_Track_delete(&track)) != OK)
		return st;

	if ((st = ADT_MP3_Track_delete(&alt_track)) != OK)
		return st;
	

	return 0;
}