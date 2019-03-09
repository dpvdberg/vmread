#ifndef WINTOOLS_H
#define WINTOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
  Provides all utilities and structures for Windows operating systems.
*/

#include "definitions.h"
#include "winstructs.h"

typedef struct WinOffsets
{
	int64_t apl;
	int64_t session;
	int64_t imageFileName;
	int64_t dirBase;
	int64_t peb;
	int64_t peb32;
	int64_t threadListHead;
	int64_t threadListEntry;
	int64_t teb;
} WinOffsets;

typedef struct WinProc
{
	uint64_t process;
	uint64_t physProcess;
	uint64_t dirBase;
	uint64_t pid;
	char name[64];
} WinProc;

typedef struct WinProcList
{
	WinProc* list;
	size_t size;
} WinProcList;

typedef struct WinExport
{
	char* name;
	uint64_t address;
} WinExport;

typedef struct WinExportList
{
	WinExport* list;
	size_t size;
} WinExportList;

typedef struct WinModule
{
	uint64_t baseAddress;
	uint64_t entryPoint;
	uint64_t sizeOfModule;
	char* name;
	short loadCount;
} WinModule;

typedef struct WinModuleList
{
	WinModule* list;
	size_t size;
} WinModuleList;

typedef struct WinCtx
{
	ProcessData process;
	WinOffsets offsets;
	uint64_t ntKernel;
	uint16_t ntVersion;
	uint16_t ntBuild;
	WinExportList ntExports;
	WinProc initialProcess;
} WinCtx;

int InitializeContext(WinCtx* ctx, pid_t pid);
int FreeContext(WinCtx* ctx);
IMAGE_NT_HEADERS* GetNTHeader(WinCtx* ctx, WinProc* process, uint64_t address, uint8_t* header, uint8_t* is64Bit);
int ParseExportTable(WinCtx* ctx, WinProc* process, uint64_t moduleBase, IMAGE_DATA_DIRECTORY* exports, WinExportList* outList);
int GenerateExportList(WinCtx* ctx, WinProc* process, uint64_t moduleBase, WinExportList* outList);
void FreeExportList(WinExportList list);
uint64_t GetProcAddress(WinCtx* ctx, WinProc* process, uint64_t module, const char* procName);
uint64_t FindProcAddress(WinExportList exports, const char* procName);
WinProcList GenerateProcessList(WinCtx* ctx);
WinModuleList GenerateModuleList(WinCtx* ctx, WinProc* process);
void FreeModuleList(WinModuleList list);
WinModule* GetModuleInfo(WinModuleList list, const char* moduleName);
PEB GetPeb(WinCtx* ctx, WinProc* process);
PEB32 GetPeb32(WinCtx* ctx, WinProc* process);

#ifdef __cplusplus
}
#endif

#endif
