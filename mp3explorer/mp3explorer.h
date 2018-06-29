#ifndef MP3EXPLORER__H
#define MP3EXPLORER__H

/*PROTOTIPOS*/
status_t mp3_explorer(format_t format, sort_t sort, const char * output_filename, char ** input_files, size_t len);

/*CONTEXTOS DE EXPORTACIÓN*/

#define CONTEXT_CSV_DELIMITER '|'
#define CONTEXT_XML_TRACK_NAME "track"
#define MAX_TRACK_NAME 10
#endif