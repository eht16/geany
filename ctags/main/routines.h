/*
*   Copyright (c) 2002, Darren Hiebert
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License version 2 or (at your option) any later version.
*
*   External interface to routines.c
*/
#ifndef CTAGS_MAIN_ROUTINES_H
#define CTAGS_MAIN_ROUTINES_H

/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */

#include <stdio.h>

#include "vstring.h"

/*
*   MACROS
*/
#define xMalloc(n,Type)    (Type *)eMalloc((size_t)(n) * sizeof (Type))
#define xCalloc(n,Type)    (Type *)eCalloc((size_t)(n), sizeof (Type))
#define xRealloc(p,n,Type) (Type *)eRealloc((p), (n) * sizeof (Type))

#define ARRAY_SIZE(X)      (sizeof (X) / sizeof (X[0]))

#define STRINGIFY(X) STRINGIFY_(X)
#define STRINGIFY_(X) #X

/*
 *  Portability macros
 */
#ifndef PATH_SEPARATOR
# if defined (MSDOS_STYLE_PATH)
#  define PATH_SEPARATOR '\\'
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
#if defined (MSDOS_STYLE_PATH)
extern const char *const PathDelimiters;
#endif
extern char *CurrentDirectory;
typedef int errorSelection;
enum eErrorTypes { FATAL = 1, WARNING = 2, PERROR = 4 };

typedef struct {
		/* Name of file for which status is valid */
	char* name;

		/* Does file exist? If not, members below do not contain valid data. */
	bool exists;

		/* is file path a symbolic link to another file? */
	bool isSymbolicLink;

		/* Is file (pointed to) a directory? */
	bool isDirectory;

		/* Is file (pointed to) a normal file? */
	bool isNormalFile;

		/* Is file (pointed to) executable? */
	bool isExecutable;

		/* Is file (pointed to) setuid? */
	bool isSetuid;

		/* Is file (pointed to) setgid? */
	bool isSetgid;

		/* Size of file (pointed to) */
	unsigned long size;
} fileStatus; 

/*
*   FUNCTION PROTOTYPES
*/
extern void setExecutableName (const char *const path);
extern const char *getExecutableName (void);
extern void error (const errorSelection selection, const char *const format, ...) CTAGS_ATTR_PRINTF (2, 3);

/* Memory allocation functions */
#ifdef NEED_PROTO_MALLOC
extern void *malloc (size_t);
extern void *realloc (void *ptr, size_t);
#endif
extern void *eMalloc (const size_t size);
extern void *eCalloc (const size_t count, const size_t size);
extern void *eRealloc (void *const ptr, const size_t size);
extern void eFree (void *const ptr);
extern void toLowerString (char* str);
extern void toUpperString (char* str);
extern char* newLowerString (const char* str);
extern char* newUpperString (const char* str);

/* File system functions */
extern fileStatus *eStat (const char *const fileName);
extern void eStatFree (fileStatus *status);
extern bool doesFileExist (const char *const fileName);
extern bool isRecursiveLink (const char* const dirName);
extern bool isSameFile (const char *const name1, const char *const name2);
extern const char *baseFilename (const char *const filePath);
extern bool isAbsolutePath (const char *const path);
extern vString *combinePathAndFile (const char *const path, const char *const file);
extern char* absoluteFilename (const char *file);
extern char* absoluteDirname (char *file);
extern char* relativeFilename (const char *file, const char *dir);
extern FILE *tempFile (const char *const mode, char **const pName);
extern void processExcludeOption (const char *const option, const char *const parameter);
extern const char *fileExtension (const char *const fileName);
extern char* eStrdup (const char* str);

#ifndef HAVE_STRICMP
extern int stricmp (const char *s1, const char *s2);
#endif
#ifndef HAVE_STRNICMP
extern int strnicmp (const char *s1, const char *s2, size_t n);
#endif
#ifndef HAVE_STRSTR
extern char* strstr (const char *str, const char *substr);
#endif

#endif  /* CTAGS_MAIN_ROUTINES_H */
