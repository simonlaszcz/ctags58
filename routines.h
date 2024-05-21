/*
*   $Id: routines.h 536 2007-06-02 06:09:00Z elliotth $
*
*   Copyright (c) 2002, Darren Hiebert
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   External interface to routines.c
*/
#ifndef _ROUTINES_H
#define _ROUTINES_H

/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */

/*
*   MACROS
*/
#define xMalloc(n,Type)    (Type *)eMalloc((size_t)(n) * sizeof (Type))
#define xCalloc(n,Type)    (Type *)eCalloc((size_t)(n), sizeof (Type))
#define xRealloc(p,n,Type) (Type *)eRealloc((p), (n) * sizeof (Type))

/*
 *  Portability macros
 */
#ifndef PATH_SEPARATOR
# if defined (MSDOS_STYLE_PATH)
#  define PATH_SEPARATOR '\\'
# elif defined (QDOS)
#  define PATH_SEPARATOR '_'
# else
#  define PATH_SEPARATOR '/'
# endif
#endif

#if defined (MSDOS_STYLE_PATH) && defined (UNIX_PATH_SEPARATOR)
# define OUTPUT_PATH_SEPARATOR	'/'
#else
# define OUTPUT_PATH_SEPARATOR	PATH_SEPARATOR
#endif

/*
*   DATA DECLARATIONS
*/
#if defined (MSDOS_STYLE_PATH) || defined (VMS)
const char *const PathDelimiters;
#endif
char *CurrentDirectory;
typedef int errorSelection;
enum eErrorTypes { FATAL = 1, WARNING = 2, PERROR = 4 };

typedef struct {
		/* Name of file for which status is valid */
	char* name;

		/* Does file exist? If not, members below do not contain valid data. */
	boolean exists;

		/* is file path a symbolic link to another file? */
	boolean isSymbolicLink;

		/* Is file (pointed to) a directory? */
	boolean isDirectory;

		/* Is file (pointed to) a normal file? */
	boolean isNormalFile;

		/* Is file (pointed to) executable? */
	boolean isExecutable;

		/* Is file (pointed to) setuid? */
	boolean isSetuid;

		/* Size of file (pointed to) */
	unsigned long size;
} fileStatus; 

/*
*   FUNCTION PROTOTYPES
*/
void freeRoutineResources (void);
void setExecutableName (const char *const path);
const char *getExecutableName (void);
const char *getExecutablePath (void);
void error (const errorSelection selection, const char *const format, ...) __printf__ (2, 3);

/* Memory allocation functions */
#ifdef NEED_PROTO_MALLOC
void *malloc (size_t);
void *realloc (void *ptr, size_t);
#endif
void *eMalloc (const size_t size);
void *eCalloc (const size_t count, const size_t size);
void *eRealloc (void *const ptr, const size_t size);
void eFree (void *const ptr);

/* String manipulation functions */
int struppercmp (const char *s1, const char *s2);
int strnuppercmp (const char *s1, const char *s2, size_t n);
#ifndef HAVE_STRSTR
char* strstr (const char *str, const char *substr);
#endif
char* eStrdup (const char* str);
void toLowerString (char* str);
void toUpperString (char* str);
char* newLowerString (const char* str);
char* newUpperString (const char* str);

/* File system functions */
void setCurrentDirectory (void);
fileStatus *eStat (const char *const fileName);
void eStatFree (fileStatus *status);
boolean doesFileExist (const char *const fileName);
boolean isRecursiveLink (const char* const dirName);
boolean isSameFile (const char *const name1, const char *const name2);
#if defined(NEED_PROTO_FGETPOS)
int fgetpos  (FILE *stream, fpos_t *pos);
int fsetpos  (FILE *stream, fpos_t *pos);
#endif
const char *baseFilename (const char *const filePath);
const char *fileExtension (const char *const fileName);
boolean isAbsolutePath (const char *const path);
vString *combinePathAndFile (const char *const path, const char *const file);
char* absoluteFilename (const char *file);
char* absoluteDirname (char *file);
char* relativeFilename (const char *file, const char *dir);
FILE *tempFile (const char *const mode, char **const pName);

#endif  /* _ROUTINES_H */

/* vi:set tabstop=4 shiftwidth=4: */
