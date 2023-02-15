/*
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See COPYING for GPL licensing information.
 */

#ifndef RIKSNMP_COMPAT_H_
#define RIKSNMP_COMPAT_H_

#include "config.h"
#include <stdlib.h>
#include <sys/stat.h>

#ifndef UNUSED
#define UNUSED(x) x __attribute__((unused))
#endif

/* From The Practice of Programming, by Kernighan and Pike */
#ifndef NELEMS
#define NELEMS(array) (sizeof(array) / sizeof(array[0]))
#endif

#ifndef HAVE_GETPROGNAME
static inline char *getprogname(void)
{
	extern char *g_prognm;
	return g_prognm;
}
#endif

#endif /* RIKSNMP_COMPAT_H_ */
