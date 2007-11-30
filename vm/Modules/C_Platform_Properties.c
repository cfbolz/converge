// Copyright (c) 2006 King's College London, created by Laurence Tratt
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.


#include "Config.h"

#include "Core.h"
#include "Memory.h"
#include "Object.h"
#include "Shortcuts.h"
#include "Slots.h"

#include "Builtins/Con_Stack/Atom.h"
#include "Builtins/Func/Atom.h"
#include "Builtins/Int/Atom.h"
#include "Builtins/List/Atom.h"
#include "Builtins/Module/Atom.h"
#include "Builtins/String/Atom.h"
#include "Builtins/Thread/Atom.h"
#include "Builtins/VM/Atom.h"



Con_Obj *Con_Module_C_Platform_Properties_init(Con_Obj *, Con_Obj *);
Con_Obj *Con_Module_C_Platform_Properties_import(Con_Obj *, Con_Obj *);



Con_Obj *Con_Module_C_Platform_Properties_init(Con_Obj *thread, Con_Obj *identifier)
{
	const char* defn_names[] = {"word_bits", "LITTLE_ENDIAN", "BIG_ENDIAN", "endianness", "endianness", "osname", "case_sensitive_filenames", NULL};

	return Con_Builtins_Module_Atom_new_c(thread, identifier, CON_NEW_STRING("C_Platform_Properties"), defn_names, CON_BUILTIN(CON_BUILTIN_NULL_OBJ));
}



Con_Obj *Con_Module_C_Platform_Properties_import(Con_Obj *thread, Con_Obj *properties_mod)
{
	CON_SET_MOD_DEFN(properties_mod, "word_bits", CON_NEW_INT(sizeof(Con_Int) * 8));

	// Endianness

	CON_SET_MOD_DEFN(properties_mod, "LITTLE_ENDIAN", CON_NEW_INT(0));
	CON_SET_MOD_DEFN(properties_mod, "BIG_ENDIAN", CON_NEW_INT(1));
#	if CON_BYTEORDER == CON_LITTLE_ENDIAN
	CON_SET_MOD_DEFN(properties_mod, "endianness", CON_GET_MOD_DEFN(properties_mod, "LITTLE_ENDIAN"));
#	elif CON_BYTEORDER == CON_BIG_ENDIAN
	CON_SET_MOD_DEFN(properties_mod, "endianness", CON_GET_MOD_DEFN(properties_mod, "BIG_ENDIAN"));
#	endif
	CON_SET_MOD_DEFN(properties_mod, "osname", CON_NEW_STRING(CON_OSNAME));
#	if CON_FILENAMES_CASE_SENSITIVE
	CON_SET_MOD_DEFN(properties_mod, "case_sensitive_filenames", CON_NEW_INT(1));
#	else
	CON_SET_MOD_DEFN(properties_mod, "case_sensitive_filenames", CON_NEW_INT(0));
#	endif

	return properties_mod;
}
