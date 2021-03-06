/*
 * Copyright (C) 2002 - 2004 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __DESKTOP_ENTRIES_H__
#define __DESKTOP_ENTRIES_H__

#include <gio/gdesktopappinfo.h>

G_BEGIN_DECLS

typedef enum
{
  DESKTOP_ENTRY_INVALID = 0,
  DESKTOP_ENTRY_DESKTOP,
  DESKTOP_ENTRY_DIRECTORY
} DesktopEntryType;

typedef enum
{
  DESKTOP_ENTRY_LOAD_FAIL_OTHER = 0,
  DESKTOP_ENTRY_LOAD_FAIL_APPINFO,
  DESKTOP_ENTRY_LOAD_SUCCESS
} DesktopEntryResultCode;

typedef struct DesktopEntry DesktopEntry;

DesktopEntry *desktop_entry_new (const char             *path,
                                 DesktopEntryResultCode *res_code);

DesktopEntry *desktop_entry_ref    (DesktopEntry *entry);
DesktopEntry *desktop_entry_copy   (DesktopEntry *entry);
DesktopEntry *desktop_entry_reload (DesktopEntry *entry);
void          desktop_entry_unref  (DesktopEntry *entry);

DesktopEntryType  desktop_entry_get_type     (DesktopEntry *entry);
const char       *desktop_entry_get_path     (DesktopEntry *entry);
const char       *desktop_entry_get_basename (DesktopEntry *entry);
const char       *desktop_entry_get_name     (DesktopEntry *entry);
const char       *desktop_entry_get_generic_name (DesktopEntry *entry);
const char       *desktop_entry_get_comment  (DesktopEntry *entry);
GIcon            *desktop_entry_get_icon     (DesktopEntry *entry);
gboolean          desktop_entry_get_hidden   (DesktopEntry *entry);
gboolean          desktop_entry_get_no_display (DesktopEntry *entry);
gboolean          desktop_entry_get_show_in  (DesktopEntry *entry);

/* Only valid for DESKTOP_ENTRY_DESKTOP */
GDesktopAppInfo  *desktop_entry_get_app_info (DesktopEntry *entry);
gboolean desktop_entry_has_categories (DesktopEntry *entry);
gboolean desktop_entry_has_category   (DesktopEntry *entry,
                                       const char   *category);


typedef struct DesktopEntrySet DesktopEntrySet;

DesktopEntrySet *desktop_entry_set_new   (void);
DesktopEntrySet *desktop_entry_set_ref   (DesktopEntrySet *set);
void             desktop_entry_set_unref (DesktopEntrySet *set);

void          desktop_entry_set_add_entry (DesktopEntrySet *set,
                                           DesktopEntry    *entry,
                                           const char      *file_id);
DesktopEntry* desktop_entry_set_lookup    (DesktopEntrySet *set,
                                           const char      *file_id);
int           desktop_entry_set_get_count (DesktopEntrySet *set);

void desktop_entry_set_union         (DesktopEntrySet *set,
                                      DesktopEntrySet *with);
void desktop_entry_set_intersection  (DesktopEntrySet *set,
                                      DesktopEntrySet *with);
void desktop_entry_set_subtract      (DesktopEntrySet *set,
                                      DesktopEntrySet *other);
void desktop_entry_set_swap_contents (DesktopEntrySet *a,
                                      DesktopEntrySet *b);

typedef void (*DesktopEntrySetForeachFunc) (const char   *file_id,
                                            DesktopEntry *entry,
                                            gpointer      user_data);

void desktop_entry_set_foreach (DesktopEntrySet            *set,
                                DesktopEntrySetForeachFunc  func,
                                gpointer                    user_data);

G_END_DECLS

#endif /* __DESKTOP_ENTRIES_H__ */
