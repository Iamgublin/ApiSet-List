#pragma once
#include"stdafx.h"

#ifdef _WIN64
#define PEB_OFFSET 0x60
typedef struct _MY_PEB                                      // 91 elements, 0x380 bytes (sizeof)
{
    ULONG_PTR    Reserved[13];
    UINT64       ApiSetMap;
}MY_PEB, *PMY_PEB;
#else 
#define PEB_OFFSET 0x30
typedef struct _MY_PEB                                      // 91 elements, 0x380 bytes (sizeof)
{
	ULONG_PTR    Reserved[14];
	UINT64       ApiSetMap;
}MY_PEB, *PMY_PEB;
#endif



/////////////////////Win7
#ifdef WIN7 

typedef struct _API_SET_UNKNOWN_ENTRY
{
    int Unknown1;
    int OffsetUnknown;
    int Unknown2;
    int ModuleNameOffset;
    int NameLength;
}API_SET_UNKNOWN_ENTRY,*PAPI_SET_UNKNOWN_ENTRY;

typedef struct _API_SET_VALUE_ENTRY
{ 
    ULONG NameOffset; 
    ULONG NameLength;
    ULONG DataOffset; 
} API_SET_VALUE_ENTRY, *PAPI_SET_VALUE_ENTRY;

typedef struct _API_SET_NAMESPACE
{ 
    ULONG Version; 
    ULONG Count;
    API_SET_VALUE_ENTRY Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;
#endif
//////////////////////////////////////////

#ifdef WIN8
//////////////////////////////////////WIN8
typedef struct _API_SET_UNKNOWN_ENTRY
{
    int Unknown1[5];
    int ModuleNameOffset;
    int NameLength;
}API_SET_UNKNOWN_ENTRY, *PAPI_SET_UNKNOWN_ENTRY;

typedef struct _API_SET_VALUE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG AliasOffset;
    ULONG AliasLength;
    ULONG DataOffset;
} API_SET_VALUE_ENTRY, *PAPI_SET_VALUE_ENTRY;

typedef struct _API_SET_NAMESPACE
{
    ULONG Version; 
    ULONG Size;
    ULONG Flags;
    ULONG Count; 
    API_SET_VALUE_ENTRY Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;
#endif // WIN8


#ifdef WIN10
/////////////////////////////////////////Win10
typedef struct _API_SET_VALUE_ENTRY {
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY, *PAPI_SET_VALUE_ENTRY;

typedef struct _API_SET_NAMESPACE_ENTRY {
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset;
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY, *PAPI_SET_NAMESPACE_ENTRY;

typedef struct _API_SET_NAMESPACE {
    ULONG Version;
    ULONG Size;
    ULONG Flags;
    ULONG Count;
    ULONG EntryOffset;
    ULONG HashOffset;
    ULONG HashFactor;
} API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;
#endif
//////////////////////////////////////////////